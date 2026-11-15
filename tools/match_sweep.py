#!/usr/bin/env python3
"""Sweep one function through a library of codegen-relevant rewrites.

Most findings in docs/matching_notes.md come down to "MWCC emits different
code for two spellings of the same thing". This applies those respellings
mechanically, one at a time, builds, scores, and keeps a record, so the cheap
ideas are exhausted by a machine before anyone grinds by hand.

    python tools/match_sweep.py SRC FUNCTION [--apply] [--rounds N] [--max N]
                                [--rules a,b] [--list] [--no-log] [--retry]

    SRC        source file (src/game/fielding/fielder.c, or without src/ / .c)
    FUNCTION   the function to work on

What it does
  1. Generates single-edit variants of FUNCTION from the rules below.
  2. For each: writes the file, builds that one object, diffs the unit.
     A variant counts only if FUNCTION improves and NO other function in the
     unit gets worse.
  3. Takes the best improvement and sweeps again from there (up to --rounds).
  4. Restores the original file, unless --apply was given and something
     improved, in which case the best version is left in place.
  5. Appends every variant and its score to docs/match_grind/<unit>.sweep.md.
     A variant already recorded there for the same function text is skipped,
     so a later session never repeats one (--retry overrides).
  6. Records which rule fixed which kind of mismatch in
     docs/match_grind/sweep_wins.json and tries proven rules first next time.

Rules (--list prints how many variants each yields for FUNCTION)
  abs        hand-written abs / ABS() / abs()  <->  __abs()
  compound   `a = a op b;`  <->  `a op= b;`
  decl       reorder the function's leading local declarations (adjacent swaps, moves)
  perm       EVERY ordering of the locals (opt-in: --perm, --perm-vars a,b,c, --perm-samples N).
             Declaration order is a proven lever for float/int register permutations; use
             --perm-vars to keep it exhaustive (6 names = 720 builds).
  declarator reorder names inside `int i, j;`
  type       int / s32 / u32 on a local; u8, s8, s16, u16 local -> int
  loop       `for` -> `while`, `for` -> `do { } while`
  inline     fold a single-use initialised local into its one use
  deinit     `T x = e;` -> `T x;` plus `x = e;` after the declarations
  cast       `(T*)p[i]`  <->  `((T**)p)[i]`  (value cast vs. address cast)
  ternary    `x = c ? a : b;` -> if / else
  invert     `if (c) {A} else {B}` -> `if (!(c)) {B} else {A}`
  retbool    `return a < b;` -> `if (a < b) return 1; return 0;`

A rewrite here can change behaviour (reordering initialisers reorders calls).
That is deliberate: the target's instructions are the specification, and a
variant that moves away from them scores worse and is discarded. Read the
winning diff before committing it all the same.

`ninja` is found via the NINJA environment variable, then PATH.
"""
import argparse
import datetime
import hashlib
import json
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from match_classify import REPO, objdiff_unit
from match_variants import find_ninja, write_source
from match_survey import classify, bucket as survey_bucket

GRIND = REPO / "docs" / "match_grind"
WINS = GRIND / "sweep_wins.json"
KEYWORDS = {"return", "if", "else", "for", "while", "do", "switch", "case", "goto", "break", "continue",
            "sizeof", "default", "typedef"}
TYPE_SWAPS = {"int": ["s32", "u32"], "s32": ["int", "u32"], "u32": ["s32", "int"],
              "u8": ["int"], "s8": ["int"], "s16": ["int"], "u16": ["int"]}
IDENT = r"[A-Za-z_]\w*"
LVALUE = IDENT + r"(?:\s*(?:\.|->)\s*" + IDENT + r"|\[[^\[\]]*\])*"


# --------------------------------------------------------------------------
# source helpers
# --------------------------------------------------------------------------
def mask(src):
    """Blank out comments, strings and char literals (same length), so that
    searches never match inside them and offsets stay valid."""
    out = list(src)
    for m in re.finditer(r"//[^\n]*|/\*.*?\*/|\"(?:\\.|[^\"\\\n])*\"|'(?:\\.|[^'\\\n])*'", src, re.S):
        for i in range(m.start(), m.end()):
            if out[i] != "\n":
                out[i] = " "
    return "".join(out)


def match_close(masked, i, open_ch="{", close_ch="}"):
    """masked[i] == open_ch -> index of the matching close_ch."""
    depth = 0
    for j in range(i, len(masked)):
        if masked[j] == open_ch:
            depth += 1
        elif masked[j] == close_ch:
            depth -= 1
            if depth == 0:
                return j
    raise ValueError("unbalanced " + open_ch)


def find_function(src, name):
    """(body_start, body_end): offsets just inside the function's braces."""
    masked = mask(src)
    for m in re.finditer(r"\b" + re.escape(name) + r"\s*\(", masked):
        line_start = masked.rfind("\n", 0, m.start()) + 1
        head = masked[line_start:m.start()]
        if not head.strip() or head.strip().startswith(("return", "=")) or any(c in head for c in "=;(,"):
            continue  # a call or a use, not a definition
        close = match_close(masked, m.end() - 1, "(", ")")
        k = close + 1
        while k < len(masked) and masked[k].isspace():
            k += 1
        if k < len(masked) and masked[k] == "{":
            return k + 1, match_close(masked, k)
    raise SystemExit(f"definition of '{name}' not found")


def top_level_split(masked, start, end, sep=";"):
    """Offsets of `sep` between start and end that are not nested in () {} []."""
    depth, out = 0, []
    for i in range(start, end):
        c = masked[i]
        if c in "({[":
            depth += 1
        elif c in ")}]":
            depth -= 1
        elif c == sep and depth == 0:
            out.append(i)
    return out


def leading_declarations(body, mbody):
    """[(start, end)] spans (end exclusive, including the ';') of the local
    declarations that open the function body."""
    decl_re = re.compile(
        r"^\s*(?:(?:const|volatile|register|static|unsigned|signed|struct|union|enum)\s+)*"
        + IDENT + r"(?:\s*\*+\s*|\s+)\**\s*" + IDENT + r"\s*(?:\[[^\]]*\]\s*)*(?:=.*|,.*)?$", re.S)
    spans, pos = [], 0
    for semi in top_level_split(mbody, 0, len(mbody)):
        stmt = mbody[pos:semi]
        words = re.findall(IDENT, stmt)
        if not stmt.strip() or not words or words[0] in KEYWORDS or not decl_re.match(stmt):
            break
        # keep leading whitespace/newline with the declaration it precedes
        spans.append((pos, semi + 1))
        pos = semi + 1
    return spans


class Variant:
    def __init__(self, rule, desc, body):
        self.rule, self.desc, self.body = rule, desc, body


def splice(body, start, end, text):
    return body[:start] + text + body[end:]


def short(text, n=48):
    text = re.sub(r"\s+", " ", text).strip()
    return text if len(text) <= n else text[:n - 3] + "..."


def line_of(body, off):
    return body.count("\n", 0, off) + 1


# --------------------------------------------------------------------------
# rules: each yields Variant objects for a function body
# --------------------------------------------------------------------------
def rule_abs(body, m):
    pat = re.compile(r"\(\s*(" + LVALUE + r")\s*\^\s*\(\s*\1\s*>>\s*31\s*\)\s*\)\s*-\s*\(\s*\1\s*>>\s*31\s*\)")
    for x in pat.finditer(m):
        yield Variant("abs", f"L{line_of(body, x.start())}: xor/shift abs -> __abs({x.group(1)})",
                      splice(body, x.start(), x.end(), f"__abs({body[x.start(1):x.end(1)]})"))
    for name, new in (("ABS", "__abs"), ("abs", "__abs"), ("__abs", "ABS")):
        for x in re.finditer(r"(?<![\w.>])" + re.escape(name) + r"\s*\(", m):
            close = match_close(m, x.end() - 1, "(", ")")
            arg = body[x.end():close]
            yield Variant("abs", f"L{line_of(body, x.start())}: {name}({short(arg, 24)}) -> {new}()",
                          splice(body, x.start(), close + 1, f"{new}({arg})"))


def statements(m):
    """(start, end) of simple `...;` statements: text between ; { } and the next ;"""
    for x in re.finditer(r"(?<=[;{}])[^;{}]*;", m):
        s = x.start() + (len(x.group(0)) - len(x.group(0).lstrip()))
        yield s, x.end()


def rule_compound(body, m):
    ops = r"(\+|-|\*|/|&|\||\^|<<|>>)"
    for s, e in statements(m):
        stmt = m[s:e]
        a = re.match(r"(" + LVALUE + r")\s*=\s*(.*);$", stmt, re.S)
        if a and "=" not in a.group(1):
            lhs, rhs = a.group(1), a.group(2)
            b = re.match(re.escape(lhs) + r"\s*" + ops + r"(?!=)\s*(.+)$", rhs, re.S)
            if b and not re.match(r"\s*=", rhs):
                rest = body[s:e][b.start(2) + (len(stmt) - len(stmt[a.start(2):])):-1].strip()
                rest_m = b.group(2).strip()
                # only when the remainder is one operand at top level for + and *, or anything for a trailing op
                if not top_level_ops(rest_m):
                    yield Variant("compound", f"L{line_of(body, s)}: {short(lhs, 20)} = {short(lhs, 12)} {b.group(1)} ... -> {b.group(1)}=",
                                  splice(body, s, e, f"{body[s:s + len(lhs)]} {b.group(1)}= {rest};"))
            continue
        c = re.match(r"(" + LVALUE + r")\s*" + ops + r"=\s*(.*);$", stmt, re.S)
        if c:
            lhs_t = body[s:s + len(c.group(1))]
            rhs_t = body[s + c.start(3):e - 1].strip()
            rhs_x = f"({rhs_t})" if top_level_ops(c.group(3)) else rhs_t
            yield Variant("compound", f"L{line_of(body, s)}: {short(lhs_t, 20)} {c.group(2)}= ... -> = {short(lhs_t, 12)} {c.group(2)} ...",
                          splice(body, s, e, f"{lhs_t} = {lhs_t} {c.group(2)} {rhs_x};"))


def top_level_ops(expr):
    depth = 0
    for i, ch in enumerate(expr):
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        elif depth == 0 and ch in "+-*/&|^<>?:%" and i > 0:
            return True
    return False


def rule_decl(body, m):
    spans = leading_declarations(body, m)
    n = len(spans)
    if n < 2:
        return
    texts = [body[a:b] for a, b in spans]
    names = [short(t, 26) for t in texts]
    lo, hi = spans[0][0], spans[-1][1]

    def emit(order, desc):
        if order != list(range(n)):
            yield Variant("decl", desc, splice(body, lo, hi, "".join(texts[i] for i in order)))

    for i in range(n - 1):
        order = list(range(n))
        order[i], order[i + 1] = order[i + 1], order[i]
        yield from emit(order, f"swap declarations `{names[i]}` / `{names[i + 1]}`")
    if n > 2:
        yield from emit(list(reversed(range(n))), "reverse all declarations")
        for i in range(n):
            rest = [k for k in range(n) if k != i]
            if i > 1:
                yield from emit([i] + rest, f"move `{names[i]}` first")
            if i < n - 2:
                yield from emit(rest + [i], f"move `{names[i]}` last")


PERM = {"on": False, "vars": None, "samples": 150}


def rule_perm(body, m):
    """Every ordering of the (selected) leading local declarations. Opt-in: the
    count is factorial, so it is capped by a seeded sample."""
    import itertools
    import random
    spans = leading_declarations(body, m)
    texts = [body[a:b] for a, b in spans]
    names = []
    for a, b in spans:
        d = re.match(r"\s*(?:(?:const|volatile|register|static|unsigned|signed|struct|union|enum)\s+)*"
                     + IDENT + r"(?:\s*\*+\s*|\s+)\**\s*(" + IDENT + r")", m[a:b])
        names.append(d.group(1) if d else None)
    pick = [i for i, n in enumerate(names)
            if n and (PERM["vars"] is None or n in PERM["vars"]) and not top_level_split(m, *spans[i], ",")]
    if len(pick) < 2:
        return
    orders = (p for p in itertools.permutations(pick) if list(p) != pick)
    total = 1
    for k in range(2, len(pick) + 1):
        total *= k
    if total - 1 > PERM["samples"]:
        orders = random.Random(1).sample(list(itertools.islice(itertools.permutations(pick), 200000)), PERM["samples"])
    lo, hi = spans[0][0], spans[-1][1]
    for order in orders:
        placed = list(range(len(spans)))
        for slot, src in zip(pick, order):
            placed[slot] = src
        if placed == list(range(len(spans))):
            continue
        yield Variant("perm", "order " + ",".join(names[i] or "?" for i in placed if i in pick),
                      splice(body, lo, hi, "".join(texts[i] for i in placed)))


def rule_declarator(body, m):
    for a, b in leading_declarations(body, m):
        stmt = m[a:b - 1]
        if "=" in stmt:
            continue
        commas = top_level_split(m, a, b - 1, ",")
        if not commas:
            continue
        head = re.match(r"\s*(?:(?:const|volatile|register|static|unsigned|signed|struct|union|enum)\s+)*" + IDENT + r"\s+", stmt)
        if not head:
            continue
        first = a + head.end()
        cuts = [first] + [c + 1 for c in commas] + [b]
        parts = [body[cuts[i]:cuts[i + 1] - 1].strip() for i in range(len(cuts) - 1)]
        for i in range(len(parts) - 1):
            p = list(parts)
            p[i], p[i + 1] = p[i + 1], p[i]
            yield Variant("declarator", f"L{line_of(body, a)}: `{parts[i]}, {parts[i + 1]}` -> `{parts[i + 1]}, {parts[i]}`",
                          splice(body, first, b, ", ".join(p) + ";"))


def rule_type(body, m):
    for a, b in leading_declarations(body, m):
        stmt = m[a:b]
        x = re.match(r"\s*(?:(?:const|volatile|register|static)\s+)*(" + IDENT + r")\b", stmt)
        if not x or x.group(1) not in TYPE_SWAPS or "*" in stmt.split("=")[0]:
            continue
        for new in TYPE_SWAPS[x.group(1)]:
            yield Variant("type", f"L{line_of(body, a)}: `{short(body[a:b], 30)}` {x.group(1)} -> {new}",
                          splice(body, a + x.start(1), a + x.end(1), new))


def rule_loop(body, m):
    for x in re.finditer(r"\bfor\s*\(", m):
        close = match_close(m, x.end() - 1, "(", ")")
        semis = top_level_split(m, x.end(), close)
        if len(semis) != 2:
            continue
        init, cond, inc = (body[x.end():semis[0]].strip(), body[semis[0] + 1:semis[1]].strip(),
                           body[semis[1] + 1:close].strip())
        k = close + 1
        while k < len(m) and m[k].isspace():
            k += 1
        if k >= len(m) or m[k] != "{" or not cond:
            continue
        end = match_close(m, k)
        if re.search(r"\bcontinue\b", m[k:end]):
            continue  # `continue` would skip the increment in the rewritten form
        inner = body[k + 1:end].rstrip()
        indent = re.match(r"[ \t]*", body[body.rfind("\n", 0, x.start()) + 1:]).group(0)
        tail = f"\n{indent}    {inc};" if inc else ""
        pre = f"{init};\n{indent}" if init else ""
        where = f"L{line_of(body, x.start())}: for ({short(init, 14)}; {short(cond, 18)}; ...)"
        yield Variant("loop", where + " -> while",
                      splice(body, x.start(), end + 1, f"{pre}while ({cond}) {{{inner}{tail}\n{indent}}}"))
        yield Variant("loop", where + " -> do/while",
                      splice(body, x.start(), end + 1, f"{pre}do {{{inner}{tail}\n{indent}}} while ({cond});"))


def rule_inline(body, m):
    for a, b in leading_declarations(body, m):
        stmt = m[a:b - 1]
        x = re.match(r"(\s*(?:(?:const|register)\s+)*" + IDENT + r"(?:\s*\*+\s*|\s+)\**\s*)(" + IDENT + r")\s*=\s*(.+)$", stmt, re.S)
        if not x or top_level_split(m, a, b - 1, ","):
            continue
        name = x.group(2)
        uses = [u for u in re.finditer(r"(?<![\w.>])" + re.escape(name) + r"\b", m) if not a <= u.start() < b]
        if len(uses) != 1:
            continue
        u = uses[0]
        after = m[u.end():u.end() + 3].lstrip()
        before = m[max(0, u.start() - 2):u.start()].rstrip()
        if re.match(r"(=(?!=)|\+\+|--|[-+*/&|^]=)", after) or before.endswith(("&", "++", "--")):
            continue  # written to, or address taken
        expr = body[a + x.start(3):b - 1].strip()
        new = splice(body, u.start(), u.end(), f"({expr})")
        new = splice(new, a, b, "") if u.start() > b else new
        # the fold yields `(&arr[i])->f`; `arr[i].f` is what anyone would write
        new = re.sub(r"\(&(" + IDENT + r"(?:\s*(?:\.|->)\s*" + IDENT + r"|\[[^\[\]]*\])*)\)\s*->", r"\1.", new)
        yield Variant("inline", f"L{line_of(body, a)}: fold single-use local `{name}` into its use", new)


def rule_deinit(body, m):
    spans = leading_declarations(body, m)
    if not spans:
        return
    block_end = spans[-1][1]
    indent = re.match(r"\s*", body[spans[-1][0]:]).group(0).split("\n")[-1]
    for a, b in spans:
        stmt = m[a:b - 1]
        x = re.match(r"(\s*(?:(?:const|register)\s+)*" + IDENT + r"(?:\s*\*+\s*|\s+)\**\s*)(" + IDENT + r")\s*=\s*(.+)$", stmt, re.S)
        if not x or top_level_split(m, a, b - 1, ",") or re.match(r"\s*const\b", stmt) or x.group(3).lstrip().startswith("{"):
            continue
        name, expr = x.group(2), body[a + x.start(3):b - 1].strip()
        new = splice(body, block_end, block_end, f"\n{indent}{name} = {expr};")
        new = splice(new, a + x.end(2), b - 1, "")
        yield Variant("deinit", f"L{line_of(body, a)}: `{name}` initialiser -> assignment after the declarations", new)


def rule_cast(body, m):
    ty = r"(" + IDENT + r"(?:\s+" + IDENT + r")?)"
    path = r"(" + IDENT + r"(?:\s*(?:\.|->)\s*" + IDENT + r")*)"
    for x in re.finditer(r"\(\s*" + ty + r"\s*\*\s*\)\s*" + path + r"\s*\[", m):
        close = match_close(m, x.end() - 1, "[", "]")
        t, p, idx = x.group(1), body[x.start(2):x.end(2)], body[x.end():close]
        yield Variant("cast", f"L{line_of(body, x.start())}: ({t}*){short(p, 22)}[..] -> (({t}**){short(p, 22)})[..]",
                      splice(body, x.start(), close + 1, f"(({t}**){p})[{idx}]"))
    for x in re.finditer(r"\(\s*\(\s*" + ty + r"\s*\*\s*\*\s*\)\s*" + path + r"\s*\)\s*\[", m):
        close = match_close(m, x.end() - 1, "[", "]")
        t, p, idx = x.group(1), body[x.start(2):x.end(2)], body[x.end():close]
        yield Variant("cast", f"L{line_of(body, x.start())}: (({t}**){short(p, 22)})[..] -> (({t}*){short(p, 22)}[..])",
                      splice(body, x.start(), close + 1, f"(({t}*){p}[{idx}])"))


def rule_ternary(body, m):
    for s, e in statements(m):
        stmt = m[s:e]
        a = re.match(r"(" + LVALUE + r")\s*=(?!=)\s*", stmt)
        if not a:
            continue
        rs = s + a.end()
        q = [i for i in top_level_split(m, rs, e - 1, "?")]
        c = [i for i in top_level_split(m, rs, e - 1, ":")]
        if len(q) != 1 or len(c) != 1 or c[0] < q[0]:
            continue
        lhs = body[s:s + len(a.group(1))]
        cond, yes, no = body[rs:q[0]].strip(), body[q[0] + 1:c[0]].strip(), body[c[0] + 1:e - 1].strip()
        indent = re.match(r"[ \t]*", body[body.rfind("\n", 0, s) + 1:]).group(0)
        new = f"if ({cond}) {{\n{indent}    {lhs} = {yes};\n{indent}}} else {{\n{indent}    {lhs} = {no};\n{indent}}}"
        yield Variant("ternary", f"L{line_of(body, s)}: {short(lhs, 18)} = c ? a : b -> if/else", splice(body, s, e, new))


def rule_invert(body, m):
    for x in re.finditer(r"\bif\s*\(", m):
        if re.search(r"\belse\s*$", m[:x.start()]):
            continue  # part of an else-if chain
        close = match_close(m, x.end() - 1, "(", ")")
        k = close + 1
        while k < len(m) and m[k].isspace():
            k += 1
        if k >= len(m) or m[k] != "{":
            continue
        end_a = match_close(m, k)
        e = re.match(r"\s*else\s*\{", m[end_a + 1:])
        if not e:
            continue
        kb = end_a + 1 + e.end() - 1
        end_b = match_close(m, kb)
        cond = body[x.end():close]
        new = f"if (!({cond})) {body[kb:end_b + 1]} else {body[k:end_a + 1]}"
        yield Variant("invert", f"L{line_of(body, x.start())}: invert if ({short(cond, 30)}) / else", splice(body, x.start(), end_b + 1, new))


def rule_retbool(body, m):
    for s, e in statements(m):
        x = re.match(r"return\s+(.+);$", m[s:e], re.S)
        if not x:
            continue
        expr_m = x.group(1)
        if "?" in expr_m or not re.search(r"(==|!=|<=|>=|<|>)", expr_m) or re.search(r"<<|>>", expr_m):
            continue
        expr = body[s + x.start(1):e - 1].strip()
        indent = re.match(r"[ \t]*", body[body.rfind("\n", 0, s) + 1:]).group(0)
        yield Variant("retbool", f"L{line_of(body, s)}: return {short(expr, 30)} -> if/return 1/return 0",
                      splice(body, s, e, f"if ({expr}) {{\n{indent}    return 1;\n{indent}}}\n{indent}return 0;"))


OPT_IN = {"perm"}
RULES = [("perm", rule_perm), ("abs", rule_abs), ("decl", rule_decl), ("type", rule_type), ("compound", rule_compound),
         ("inline", rule_inline), ("deinit", rule_deinit), ("cast", rule_cast), ("declarator", rule_declarator), ("loop", rule_loop),
         ("invert", rule_invert), ("ternary", rule_ternary), ("retbool", rule_retbool)]


def generate(body, only=None):
    m = mask(body)
    out = []
    for name, fn in RULES:
        if only and name not in only:
            continue
        if name in OPT_IN and not (PERM["on"] or (only and name in only)):
            continue
        try:
            out += [v for v in fn(body, m) if v.body != body]
        except (ValueError, IndexError):
            continue  # a rule that cannot parse this function simply offers nothing
    return out


# --------------------------------------------------------------------------
# build / score / log
# --------------------------------------------------------------------------
def resolve(src_arg):
    wanted = src_arg.replace("\\", "/")
    wanted = wanted if wanted.startswith("src/") else "src/" + wanted
    wanted = wanted if wanted.endswith(".c") else wanted + ".c"
    for u in json.loads((REPO / "objdiff.json").read_text())["units"]:
        if (u.get("metadata") or {}).get("source_path") == wanted:
            return u
    raise SystemExit(f"{wanted} is not a unit in objdiff.json")


def measure(ninja, unit):
    """{function: percent}, the raw diff JSON; or (None, None) if the build failed."""
    r = subprocess.run([ninja, unit["base_path"]], cwd=REPO, capture_output=True, text=True)
    if r.returncode:
        return None, None
    data = objdiff_unit(unit["name"])
    return {s["name"]: s["match_percent"] for s in data["left"]["symbols"]
            if s.get("kind") == "SYMBOL_FUNCTION" and s.get("match_percent") is not None}, data


def mismatch_bucket(data, function):
    left, right = data["left"]["symbols"], data["right"]["symbols"]
    for s in left:
        if s.get("name") == function and "instructions" in s and s.get("target_symbol") is not None:
            ours = right[s["target_symbol"]]
            counts, _ = classify(s, ours)
            return survey_bucket({"counts": dict(counts), "size": int(s["size"]), "our_size": int(ours.get("size", 0))})
    return "?"


def variant_id(function, body):
    return hashlib.sha1((function + "\0" + re.sub(r"\s+", " ", body)).encode()).hexdigest()[:8]


def load_log(path):
    return set(re.findall(r"\[sweep ([0-9a-f]{8})\]", path.read_text(encoding="utf-8"))) if path.exists() else set()


def load_wins():
    try:
        return json.loads(WINS.read_text(encoding="utf-8"))
    except (OSError, ValueError):
        return []


def order_rules(variants, wins, bkt):
    """Rules that have fixed this kind of mismatch before go first."""
    score = {}
    for w in wins:
        score[w["rule"]] = score.get(w["rule"], 0) + (3 if w.get("bucket") == bkt else 1)
    base = {name: i for i, (name, _) in enumerate(RULES)}
    return sorted(variants, key=lambda v: (-score.get(v.rule, 0), base[v.rule]))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("src")
    ap.add_argument("function")
    ap.add_argument("--apply", action="store_true", help="leave the best improving version in the source file")
    ap.add_argument("--rounds", type=int, default=3, help="greedy rounds (default 3)")
    ap.add_argument("--max", type=int, default=120, help="most variants to build per round (default 120)")
    ap.add_argument("--rules", help="comma-separated subset of rules")
    ap.add_argument("--with", dest="with_fns", help="comma-separated functions scored together with FUNCTION "
                    "(for an inline helper: name its host functions). The objective is their average.")
    ap.add_argument("--perm", action="store_true", help="also try every ordering of the local declarations (capped)")
    ap.add_argument("--perm-vars", help="comma-separated locals to permute among their own slots (default: all)")
    ap.add_argument("--perm-samples", type=int, default=150, help="sample size when there are more orderings (default 150)")
    ap.add_argument("--list", action="store_true", help="only list the variants that would be tried")
    ap.add_argument("--no-log", action="store_true", help="do not write the sweep log or the wins file")
    ap.add_argument("--retry", action="store_true", help="re-run variants the log says were already tried")
    args = ap.parse_args()

    unit = resolve(args.src)
    path = REPO / unit["metadata"]["source_path"]
    only = set(args.rules.split(",")) if args.rules else None
    PERM["on"] = args.perm
    PERM["samples"] = args.perm_samples
    PERM["vars"] = set(args.perm_vars.split(",")) if args.perm_vars else None
    unknown = (only or set()) - {n for n, _ in RULES}
    if unknown:
        raise SystemExit(f"unknown rule(s): {', '.join(sorted(unknown))}")
    original = path.read_bytes().decode("utf-8")
    log_path = GRIND / (unit["name"].replace("/", "_") + ".sweep.md")

    if args.list:
        start, end = find_function(original, args.function)
        vs = generate(original[start:end], only)
        for name, _ in RULES:
            mine = [v for v in vs if v.rule == name]
            if mine:
                print(f"{name:10s} {len(mine):3d}")
                for v in mine[:6]:
                    print(f"             {v.desc}")
                if len(mine) > 6:
                    print(f"             ... {len(mine) - 6} more")
        print(f"{len(vs)} variants")
        return

    ninja = find_ninja()
    tried = set() if args.retry else load_log(log_path)
    wins = load_wins()
    current = original
    lines, kept = [], []
    best_overall = None
    try:
        base, data = measure(ninja, unit)
        if base is None:
            raise SystemExit("the unit does not build as it stands; fix that first")
        objset = [args.function] + [f for f in (args.with_fns or "").split(",") if f]
        missing = [f for f in objset if f not in base]
        if missing:
            raise SystemExit(f"not functions objdiff scores in {unit['name']}: {', '.join(missing)}")
        obj = lambda d: sum(d[f] for f in objset) / len(objset)
        start_pct = obj(base)
        bkt = mismatch_bucket(data, args.function)
        print(f"{args.function}" + (f" (+{len(objset) - 1} scored with it)" if len(objset) > 1 else "")
              + f" in {unit['name']}: {start_pct:.2f}%  [{bkt}]")
        lines.append(f"baseline: {start_pct:.2f}% [{bkt}]")
        if start_pct >= 100:
            print("already matching")
            return

        for rnd in range(1, args.rounds + 1):
            start, end = find_function(current, args.function)
            body = current[start:end]
            variants = order_rules(generate(body, only), wins, bkt)
            fresh = [v for v in variants if variant_id(args.function, v.body) not in tried]
            skipped = len(variants) - len(fresh)
            todo = fresh[:args.max]
            print(f"round {rnd}: {len(todo)} variants to build"
                  + (f", {skipped} already in the log" if skipped else "")
                  + (f", {len(fresh) - len(todo)} over --max" if len(fresh) > len(todo) else ""))
            best = None
            for n, v in enumerate(todo, 1):
                vid = variant_id(args.function, v.body)
                tried.add(vid)
                candidate = current[:start] + v.body + current[end:]
                write_source(path, candidate.encode("utf-8"))
                got, _ = measure(ninja, unit)
                if got is None:
                    status, pct = "build failed", None
                else:
                    pct = obj(got)
                    worse = [g for g, p in got.items() if g not in objset and p < base.get(g, 0) - 1e-6]
                    if worse:
                        status = f"regresses {worse[0]}" + (f" +{len(worse) - 1}" if len(worse) > 1 else "")
                    elif pct > obj(base) + 1e-6:
                        status = "better"
                        if best is None or pct > best[0]:
                            best = (pct, v, candidate, got)
                    else:
                        status = "same" if abs(pct - obj(base)) <= 1e-6 else "worse"
                shown = f"{pct:.2f}%" if pct is not None else "-"
                lines.append(f"  [sweep {vid}] {v.rule}: {v.desc} -> {shown} ({status})")
                if status == "better" or pct is None or n % 10 == 0 or n == len(todo):
                    print(f"  {n:3d}/{len(todo)}  {v.rule:10s} {shown:>8s}  {status:14s} {v.desc[:70]}")
                if best and best[0] >= 100:
                    break
            if not best:
                print("  nothing improved")
                break
            pct, v, candidate, got = best
            print(f"  kept: {v.rule}: {v.desc} -> {pct:.2f}%")
            lines.append(f"  kept after round {rnd}: {v.rule}: {v.desc} -> {pct:.2f}%")
            kept.append({"rule": v.rule, "bucket": bkt, "unit": unit["name"], "function": args.function,
                         "from": round(obj(base), 3), "to": round(pct, 3), "desc": v.desc})
            current, base, best_overall = candidate, got, pct
            if pct >= 100:
                break
    finally:
        final = current if (args.apply and best_overall is not None) else original
        write_source(path, final.encode("utf-8"))
        subprocess.run([ninja, unit["base_path"]], cwd=REPO, capture_output=True, text=True) if "ninja" in dir() else None

    if best_overall is None:
        print(f"result: no improvement over {start_pct:.2f}%; source unchanged")
    else:
        print(f"result: {start_pct:.2f}% -> {best_overall:.2f}% with {len(kept)} edit(s); "
              + ("left applied in the source" if args.apply else "source restored (re-run with --apply to keep it)"))
        for k in kept:
            print(f"   {k['rule']}: {k['desc']}")

    if not args.no_log and len(lines) > 1:
        GRIND.mkdir(parents=True, exist_ok=True)
        header = "" if log_path.exists() else (
            f"# Sweep log: {unit['name']}\n\nWritten by tools/match_sweep.py. One line per variant it built; the id in\n"
            "brackets is what stops a later run repeating it. Hand-made attempts belong in\nthe unit's checkpoint, not here.\n")
        stamp = datetime.date.today().isoformat()
        outcome = "no improvement" if best_overall is None else f"{start_pct:.2f}% -> {best_overall:.2f}%" + ("" if args.apply else " (not applied)")
        with log_path.open("a", encoding="utf-8", newline="\n") as f:
            f.write(f"{header}\n## {args.function} ({stamp}): {outcome}\n" + "\n".join(lines) + "\n")
        if kept:
            WINS.write_text(json.dumps(wins + kept, indent=1) + "\n", encoding="utf-8")
        print(f"log: {log_path.relative_to(REPO).as_posix()}")


if __name__ == "__main__":
    main()
