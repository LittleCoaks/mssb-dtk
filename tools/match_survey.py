#!/usr/bin/env python3
"""Module-wide survey of WHY functions do not match, from per-unit objdiff diffs.

`match_classify.py` answers "which bucket is this one function in"; this
answers "what does the whole module's backlog look like", and lets you look at
any function's mismatching rows without loading a unit's diff JSON by hand.

    python tools/match_survey.py dump   [--module game]     # refresh the diff cache
    python tools/match_survey.py scan   [--module game] [--list REGEX]
    python tools/match_survey.py relocs [--module game]     # reloc-only breakdown
    python tools/match_survey.py shapes [--module game]     # localised vs. spread swaps
    python tools/match_survey.py show FUNCTION [--context N]

`dump` runs `objdiff-cli diff` for every unit with an unmatched function and
caches the JSON under build/.match_survey/ (gitignored). The other commands
read that cache, so re-run `dump` after a rebuild. `show` prints TARGET | OURS.

Buckets printed by `scan` (a function lands in the first that applies):

  SIZE_DIFF      our function is a different size: missing/extra instructions,
                 not register allocation, however high the percentage.
  REORDER/OPCODE same size, but inserted/deleted/replaced rows.
  NONREG:reloc   code identical, a relocation resolves to a different symbol
                 (literal pool order, data ownership). No C-level grind needed.
  REG:<classes>  same opcodes in the same order, only registers differ.
                 gv/gs = volatile/callee-saved GPR, fv/fs = the same for FPRs,
                 g_vs/f_vs = a value that is volatile on one side and saved on
                 the other, +stack = r1-relative offsets differ too.
  REG+imm/reloc  a swap mixed with an immediate or relocation difference.

Side convention is objdiff's: left = target, right = ours.
"""
import argparse
import collections
import concurrent.futures as cf
import json
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from match_classify import REPO, resolve_objdiff_cli

CACHE = REPO / "build" / ".match_survey"
REPORT = REPO / "build" / "GYQE01" / "report.json"
STRUCTURAL = {"INSERT", "DELETE", "REPLACE", "OP_MISMATCH"}
REG_KINDS = {"gv", "gs", "fv", "fs", "g_vs", "f_vs", "mix", "cr"}


def cache_path(unit):
    return CACHE / (unit.replace("/", "_") + ".json")


def unmatched_units(module):
    report = json.loads(REPORT.read_text())
    return [
        u["name"] for u in report["units"]
        if u["name"].startswith(module + "/")
        and any(f.get("fuzzy_match_percent", 0) < 100 for f in u.get("functions", []))
    ]


def cmd_dump(args):
    CACHE.mkdir(parents=True, exist_ok=True)
    cli = str(resolve_objdiff_cli())
    units = unmatched_units(args.module)

    def run(unit):
        r = subprocess.run(
            [cli, "diff", "-p", str(REPO), "-u", unit, "-o", str(cache_path(unit)), "--format", "json"],
            capture_output=True, text=True,
        )
        return unit, r.returncode

    with cf.ThreadPoolExecutor(8) as ex:
        failed = [u for u, rc in ex.map(run, units) if rc]
    for u in failed:
        print("FAILED", u)
    print(f"dumped {len(units) - len(failed)} of {len(units)} units to {CACHE.relative_to(REPO)}")


def cached_units(module):
    files = sorted(CACHE.glob(module + "_*.json"))
    if not files:
        raise SystemExit(f"no cached diffs for module '{module}'; run `match_survey.py dump --module {module}` first")
    for f in files:
        yield f.stem, json.loads(f.read_text())


def function_pairs(data):
    """Yield (target_symbol, our_symbol) for every unmatched function in a unit diff."""
    left, right = data["left"]["symbols"], data["right"]["symbols"]
    for s in left:
        if s.get("kind") != "SYMBOL_FUNCTION" or "instructions" not in s:
            continue
        pct = s.get("match_percent")
        if pct is None or pct >= 100 or s.get("target_symbol") is None:
            continue
        yield s, right[s["target_symbol"]]


def ins_args(row):
    out = []
    for p in row["instruction"]["parts"]:
        if "arg" in p:
            a = p["arg"]
            out.append(a.get("opaque") or a.get("signed") or a.get("unsigned") or ("RELOC" if a.get("reloc") else str(a)))
        elif "basic" in p:
            out.append(("B", p["basic"]))
    return out


def reg_class(arg):
    m = re.fullmatch(r"r(\d+)", str(arg))
    if m:
        n = int(m.group(1))
        return "gv" if (n == 0 or 3 <= n <= 12) else ("gs" if n >= 13 else "sp")
    m = re.fullmatch(r"f(\d+)", str(arg))
    if m:
        return "fv" if int(m.group(1)) <= 13 else "fs"
    if re.fullmatch(r"cr(\d+)", str(arg)):
        return "cr"
    return None


def classify(target, ours):
    counts, pairs = collections.Counter(), collections.Counter()
    for a, b in zip(target["instructions"], ours.get("instructions", [])):
        kind = a.get("diff_kind") or b.get("diff_kind")
        if not kind:
            continue
        if kind != "DIFF_ARG_MISMATCH":
            counts[kind.replace("DIFF_", "")] += 1
            continue
        kinds = set()
        text = a["instruction"]["formatted"]
        for x, y in zip(ins_args(a), ins_args(b)):
            if x == y:
                continue
            cx, cy = reg_class(x), reg_class(y)
            if cx and cy:
                if cx == cy:
                    kinds.add(cx)
                elif {cx, cy} == {"gv", "gs"}:
                    kinds.add("g_vs")
                elif {cx, cy} == {"fv", "fs"}:
                    kinds.add("f_vs")
                else:
                    kinds.add("mix")
                pairs[(x, y)] += 1
            elif "(r1)" in text or ", r1, " in text:
                kinds.add("stack")
            elif x == "RELOC" or y == "RELOC":
                kinds.add("reloc")
            else:
                kinds.add("imm")
        for k in kinds or {"reloc"}:  # identical text, different relocation target
            counts[k] += 1
    return counts, pairs


def bucket(row):
    kinds = set(row["counts"])
    if row["size"] != row["our_size"]:
        return "SIZE_DIFF"
    if kinds & STRUCTURAL:
        return "REORDER/OPCODE"
    regs, other = kinds & REG_KINDS, kinds - REG_KINDS
    if not regs:
        return "NONREG:" + "+".join(sorted(other))
    if other - {"stack"}:
        return "REG+" + "+".join(sorted(other))
    return "REG:" + "+".join(sorted(regs)) + ("+stack" if "stack" in other else "")


def survey(module):
    rows = []
    for unit, data in cached_units(module):
        for target, ours in function_pairs(data):
            counts, pairs = classify(target, ours)
            rows.append({
                "unit": unit, "fn": target["name"], "pct": target["match_percent"],
                "size": int(target["size"]), "our_size": int(ours.get("size", 0)),
                "counts": dict(counts), "pairs": pairs.most_common(4),
            })
    return rows


def cmd_scan(args):
    rows = survey(args.module)
    buckets = collections.defaultdict(list)
    for r in rows:
        buckets[bucket(r)].append(r)
    print(f"{len(rows)} unmatched functions in '{args.module}' (per-unit diff; counts reloc-only functions the report scores as matched)")
    for name, fns in sorted(buckets.items(), key=lambda kv: -len(kv[1])):
        print(f"{name:32s} {len(fns):4d} fns {sum(f['size'] for f in fns):8d} bytes  avg {sum(f['pct'] for f in fns) / len(fns):.2f}%")
    if args.list:
        for name, fns in sorted(buckets.items()):
            if not re.search(args.list, name):
                continue
            print(f"\n== {name}")
            for f in sorted(fns, key=lambda f: -f["pct"]):
                print(f"  {f['unit']:40s} {f['fn']:44s} {f['pct']:6.2f} size {f['size']:5d}/{f['our_size']:5d} {f['counts']} {f['pairs']}")


def symbol_kind(name):
    if name is None:
        return "none"
    if name.startswith("@"):
        return "anon@"
    for tag in ("rodata", "data", "bss"):
        if f"_{tag}_" in name:
            return "lbl_" + tag
    if name.startswith("lbl_"):
        return "lbl_other"
    return "named"


def cmd_relocs(args):
    """For functions whose ONLY mismatch is a relocation: what points where."""
    total, per_unit, examples = collections.Counter(), collections.Counter(), collections.defaultdict(list)
    for unit, data in cached_units(args.module):
        left, right = data["left"]["symbols"], data["right"]["symbols"]
        for target, ours in function_pairs(data):
            counts, _ = classify(target, ours)
            if set(counts) != {"reloc"} or target["size"] != ours.get("size"):
                continue
            for a, b in zip(target["instructions"], ours["instructions"]):
                if not (a.get("diff_kind") or b.get("diff_kind")):
                    continue
                ra, rb = a["instruction"].get("relocation"), b["instruction"].get("relocation")
                ln = left[ra["target_symbol"]]["name"] if ra else None
                rn = right[rb["target_symbol"]]["name"] if rb else None
                addend = "addend differs" if (ra or {}).get("addend") != (rb or {}).get("addend") else "same addend"
                key = (f"target {symbol_kind(ln)}", f"ours {symbol_kind(rn)}", addend)
                total[key] += 1
                per_unit[(unit, key)] += 1
                if len(examples[key]) < 3:
                    examples[key].append((unit, target["name"], a["instruction"]["formatted"], b["instruction"]["formatted"]))
    for key, n in total.most_common():
        print(n, key)
        for e in examples[key]:
            print("     ", e)
    print()
    for (unit, key), n in per_unit.most_common(args.top):
        print(f"{n:5d} {unit:40s} {key}")


def cmd_shapes(args):
    """Pure register swaps: is the damage one short window (an expression's
    temporary) or spread over the function (a variable's whole live range)?"""
    out = []
    for unit, data in cached_units(args.module):
        for target, ours in function_pairs(data):
            counts, _ = classify(target, ours)
            if target["size"] != ours.get("size") or not set(counts) <= REG_KINDS | {"stack"}:
                continue
            lt = [i["instruction"]["formatted"] for i in target["instructions"]]
            rt = [i["instruction"]["formatted"] for i in ours["instructions"]]
            idx = [k for k, (a, b) in enumerate(zip(lt, rt)) if a != b and "@" not in a and not a.startswith("b")]
            if not idx:
                continue
            windows = 1 + sum(1 for a, b in zip(idx, idx[1:]) if b - a > 8)
            involved = set()
            for k in idx:
                for x, y in zip(re.findall(r"\b([rf]\d+)\b", lt[k]), re.findall(r"\b([rf]\d+)\b", rt[k])):
                    if x != y:
                        involved |= {x, y}
            saved = {x for x in involved if int(x[1:]) >= (13 if x[0] == "r" else 14)}
            kind = "saved" if saved == involved else ("volatile" if not saved else "cross")
            if kind == "volatile" and "r0" in involved:
                kind = "volatile+r0"
            if windows == 1 and idx[-1] - idx[0] < 40:
                spread = "one window"
            else:
                spread = "few windows" if windows <= 3 else "spread"
            out.append((kind, spread, unit, target["name"], len(idx), sorted(involved), target["match_percent"]))
    for key, n in sorted(collections.Counter((o[0], o[1]) for o in out).items()):
        print(f"{n:4d} {key[0]:12s} {key[1]}")
    print()
    for kind, spread, unit, fn, rows, involved, pct in sorted(out, key=lambda o: (o[0], o[1], o[4])):
        if not args.all and spread != "one window":
            continue
        print(f"{kind:12s} {spread:12s} {unit:40s} {fn:44s} {rows:3d} rows {pct:6.2f}% {' '.join(involved)}")


def cmd_show(args):
    found = False
    for path in sorted(CACHE.glob("*.json")):
        data = json.loads(path.read_text())
        if "left" not in data or "right" not in data:
            continue  # not a diff dump
        left, right = data["left"]["symbols"], data["right"]["symbols"]
        for s in left:
            if s.get("name") != args.function or "instructions" not in s or s.get("target_symbol") is None:
                continue
            found = True
            li, ri = s["instructions"], right[s["target_symbol"]].get("instructions", [])
            n = max(len(li), len(ri))
            row = lambda rows, k: rows[k] if k < len(rows) else {}
            differs = [bool(row(li, k).get("diff_kind") or row(ri, k).get("diff_kind")) for k in range(n)]
            keep = set(range(n)) if args.context < 0 else {
                j for k in range(n) if differs[k] for j in range(k - args.context, k + args.context + 1)
            }
            print(f"## {path.stem} {args.function} {s.get('match_percent')}%   TARGET | OURS (source line)")
            last = -1
            for k in range(n):
                if k not in keep:
                    continue
                if k != last + 1:
                    print("   ...")
                last = k
                a, b = row(li, k).get("instruction", {}), row(ri, k).get("instruction", {})
                print(f"{'!' if differs[k] else ' '} {k:4d}  {a.get('formatted', ''):42s} | {b.get('formatted', ''):42s} {b.get('line_number', '')}")
    if not found:
        raise SystemExit(f"'{args.function}' not found in the cache; run `dump` for its module first")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    for name, fn in (("dump", cmd_dump), ("scan", cmd_scan), ("relocs", cmd_relocs), ("shapes", cmd_shapes)):
        p = sub.add_parser(name)
        p.add_argument("--module", default="game", help="main, game, menus or debug (default: game)")
        p.set_defaults(func=fn)
        if name == "scan":
            p.add_argument("--list", metavar="REGEX", help="also list the functions in buckets matching REGEX")
        if name == "relocs":
            p.add_argument("--top", type=int, default=30)
        if name == "shapes":
            p.add_argument("--all", action="store_true", help="list every swap, not only the one-window ones")
    p = sub.add_parser("show")
    p.add_argument("function")
    p.add_argument("--context", type=int, default=3, help="rows of context around each mismatch; -1 prints everything")
    p.set_defaults(func=cmd_show)
    args = ap.parse_args()
    args.func(args)


if __name__ == "__main__":
    main()
