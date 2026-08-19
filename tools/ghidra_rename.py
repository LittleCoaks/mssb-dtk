#!/usr/bin/env python3
"""
Rename repo placeholder symbols (fn_3_XXXX / lbl_XXXX) to the real names the
Ghidra project already has for the same address.

A rename has to happen on BOTH sides at once:
  * config/*/symbols.txt names the *target* side (what objdiff compares against)
  * src/**.c and include/**.h name our side
Renaming only one side would manufacture SYMBOL_NAME mismatches, so this tool
always rewrites them together, and the result should be byte-identical object
code -- names do not affect codegen. Verify with a full rebuild + objdiff
report diff afterwards; the expected delta is exactly zero.

Ghidra names routinely contain characters that are illegal in C identifiers
(`?`, `/`, `,`, `(`, `)`, `=`, `-`, `.`, `%`), so every name is sanitized. The
rules follow what the repo already did by hand, e.g.
    batterAI,GuessedPitchLocZone?      -> batterAI_GuessedPitchLocZone
    scoreBook_batter/pitcherStatsDisplayed -> scoreBook_batter_pitcherStatsDisplayed

Usage:
    python tools/ghidra_rename.py plan               # dry run, writes a report
    python tools/ghidra_rename.py plan --kind data
    python tools/ghidra_rename.py apply              # rewrite the tree
"""
import argparse
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import ghidra_query as gq  # noqa: E402

REPO = gq.REPO

# Repo-side names that mean "we have no idea what this is".
# Three families: main-DOL `fn_80003458` / `lbl_800E6600` (bare address), REL
# `fn_3_1CE90` / `lbl_3_data_1594` (module + section + offset), and the hybrid
# `fn_8001C67C_animation` where someone appended a hint to a placeholder without
# replacing it -- those are still placeholders and should be upgradable.
REPO_PLACEHOLDER = re.compile(r"^(fn_[0-9A-Fa-f]{8}|fn_\d+_[0-9A-Fa-f]+"
                              r"|lbl_[0-9A-Fa-f]+|lbl_\d+_\w+|jumptable_\w+)"
                              r"(_\w+)?$")

# The decomp is one author with consistent conventions; the Ghidra project is
# several authors with differing ones. So a name the decomp has actually written
# always wins, and Ghidra is only consulted where the decomp still has a
# placeholder. Between the two Ghidra programs, `in_game` (the match REL) is the
# more developed and wins over `AtGameSettingsScreen` (the menu REL).
PROGRAM_PRECEDENCE = ("in_game", "AtGameSettingsScreen")

# Ghidra names that are auto-generated and carry no information.
G_AUTO = re.compile(
    r"^(FUN|DAT|LAB|SUB|UNK|PTR|ARRAY|SST|switchD|caseD|u|s|e)_"
    r"|^[A-Za-z_]\w*_(ARRAY_)?[0-9a-f]{8}$"
    r"|^(const|c)_[-0-9]"
    r"|^_?_?float", re.I)

# Real words, but too generic to be worth adopting as a symbol name.
LOW_INFO = {
    "unreferenced", "unused", "unknown", "pad", "padding", "dummy", "none",
    "null", "empty", "data", "table", "array", "temp", "tmp", "buffer", "misc",
    "unused_", "nothing", "blank", "reserved",
}


# Ghidra allows characters that are illegal in C identifiers. Mapping them all to
# "_" (what the old Ghidra export did) throws away meaning and lets two distinct
# symbols collapse onto one identifier. Translate by meaning instead, longest
# token first. `?` is handled separately: it marks the Ghidra author's
# uncertainty and reads better as a single `_maybe` suffix than in place.
CHAR_RULES = [
    ("<->", "_to_"),   # c_rad<->deg
    ("->",  "_to_"),   # const_degree->radian, processBallInAir->Landed
    ("/",   "_or_"),   # teamWhoWon(A/H), scoreBook_batter/pitcherStatsDisplayed
    ("&",   "_and_"),  # toyfield_hud_turns&diamondMap
    ("+",   "_and_"),  # gfx_cssCharStatBars+sthgElse
    (",",   "_and_"),  # running_UpdateTrackingValues,BasesEarned
    ("'",   ""),       # ...Fielder'sAutoMovement -> ...FieldersAutoMovement
    ('"',   ""),       # the"CoinsX2"Graphic
]
UNCERTAIN_SUFFIX = "_maybe"


def sanitize(name):
    """Ghidra name -> legal C identifier, or None if nothing usable is left.

    Leading underscores are meaningful in C (__start, __osCurrentCtx) and are
    preserved; only trailing ones and runs introduced by substitution collapse.
    """
    # Already a legal identifier: pass through untouched. Rewriting it would
    # strip meaningful trailing underscores and collapse genuinely distinct
    # symbols together (__check_pad3 / __check_pad3_, YUV2RGB / YUV2RGB_).
    if re.fullmatch(r"[A-Za-z_]\w*", name):
        return name

    lead = len(name) - len(name.lstrip("_"))
    s = name
    uncertain = "?" in s
    s = s.replace("?", "")
    for old, new in CHAR_RULES:
        s = s.replace(old, new)
    # anything left over (parentheses, hyphens, dots, '*', '#', ...) is a plain
    # separator with no meaning worth preserving
    s = re.sub(r"[^A-Za-z0-9_]+", "_", s)
    s = re.sub(r"_+", "_", s).strip("_")
    if not s:
        return None
    if uncertain and not s.endswith(UNCERTAIN_SUFFIX):
        s += UNCERTAIN_SUFFIX
    s = "_" * lead + s
    if s[0].isdigit():
        s = "_" + s
    return s


def ghidra_name_at(addr, is_fn, tables):
    """Best Ghidra name for an address, honouring PROGRAM_PRECEDENCE."""
    for prog in PROGRAM_PRECEDENCE:
        hit = tables[prog][0].get(addr) if is_fn else tables[prog][1].get(addr)
        if hit is None:
            continue
        gname = hit[1] if is_fn else hit[2]
        if gname and not G_AUTO.match(gname):
            return gname, prog
    return None, None


def build_plan(kind):
    cs = gq.config_symbols(with_meta=True)
    tables = {p: (gq.load_symbols(p), gq.load_data(p)) for p in PROGRAM_PRECEDENCE}

    # A sanitized name that two different Ghidra symbols both want is ambiguous;
    # taking it for either would be a coin flip, so neither gets it and both are
    # reported for a human to name.
    want = {}
    for name, (addr, section, meta, path) in cs.items():
        if not REPO_PLACEHOLDER.match(name):
            continue
        gname, _prog = ghidra_name_at(addr, "type:function" in meta, tables)
        if not gname:
            continue
        s = sanitize(gname)
        if s:
            want.setdefault(s, set()).add(gname)
    ambiguous = {s for s, srcs in want.items() if len(srcs) > 1}

    plan, skipped = [], []
    taken = set(cs)  # every name already used anywhere in the config
    proposed = {}

    for name, (addr, section, meta, path) in sorted(cs.items(), key=lambda kv: kv[1][0]):
        is_fn = "type:function" in meta
        if kind != "all" and kind != ("func" if is_fn else "data"):
            continue
        # The decomp's own name wins whenever it has actually written one.
        if not REPO_PLACEHOLDER.match(name):
            continue
        gname, _prog = ghidra_name_at(addr, is_fn, tables)
        if not gname:
            continue
        # Ghidra labels float/int literals with the value itself ("-1.0", "7.0").
        # Those sanitize into meaningless names like _1_0, and -1.0 and 1.0 would
        # collapse onto the same identifier.
        if re.fullmatch(r"c?[-+]?[\d.]+([eE][-+]?\d+)?f?", gname):
            skipped.append((name, gname, "numeric literal label"))
            continue
        new = sanitize(gname)
        # compare against LOW_INFO with the uncertainty suffix removed, so
        # `unused?` -> `unused_maybe` is still recognised as saying nothing
        bare = new[:-len(UNCERTAIN_SUFFIX)] if new.endswith(UNCERTAIN_SUFFIX) else new
        if (new is None or new.lower() in LOW_INFO or bare.lower() in LOW_INFO
                or re.fullmatch(r"_?[\d_]+", new)):
            skipped.append((name, gname, "low-information"))
            continue
        if new in ambiguous:
            skipped.append((name, gname,
                            "AMBIGUOUS: %s is also what %s sanitizes to -- name one by hand"
                            % (new, " / ".join(sorted(want[new] - {gname})))))
            continue
        if new in taken:
            skipped.append((name, gname, "name already used in repo: " + new))
            continue
        if new in proposed:
            skipped.append((name, gname, "collides with rename of " + proposed[new]))
            continue
        proposed[new] = name
        taken.add(new)
        plan.append((name, new, gname, addr, "func" if is_fn else "data", path))
    return plan, skipped


def target_files():
    for pat in ("src/**/*.c", "src/**/*.h", "include/**/*.h", "config/**/symbols.txt"):
        for p in REPO.glob(pat):
            yield p


def apply_plan(plan):
    mapping = {old: new for old, new, _, _, _, _ in plan}
    if not mapping:
        return 0, 0
    rx = re.compile(r"\b(" + "|".join(sorted(map(re.escape, mapping), key=len, reverse=True)) + r")\b")
    files = touched = 0
    for p in target_files():
        raw = p.read_bytes()
        text = raw.decode("utf-8", errors="replace")
        new_text, n = rx.subn(lambda m: mapping[m.group(1)], text)
        if n:
            # write bytes: read_text/write_text would flatten the repo's CRLF
            p.write_bytes(new_text.encode("utf-8"))
            files += 1
            touched += n
    return files, touched


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("action", choices=["plan", "apply"])
    ap.add_argument("--kind", choices=["func", "data", "all"], default="all")
    ap.add_argument("--limit", type=int, default=0, help="only the first N renames")
    args = ap.parse_args()

    plan, skipped = build_plan(args.kind)
    if args.limit:
        plan = plan[:args.limit]

    print("%d renames available (%d func, %d data); %d skipped" % (
        len(plan), sum(1 for r in plan if r[4] == "func"),
        sum(1 for r in plan if r[4] == "data"), len(skipped)))

    dirty = [(o, n, g) for o, n, g, _, _, _ in plan if n != g]
    print("%d of them needed sanitizing for illegal C characters\n" % len(dirty))

    out = REPO / ".ghidra_cache" / "rename_plan.txt"
    with out.open("w", encoding="utf-8") as fp:
        for old, new, gname, addr, k, _ in plan:
            fp.write("%-26s -> %-44s 0x%08x %s%s\n" % (
                old, new, addr, k, "   [sanitized from: " + gname + "]" if new != gname else ""))
        fp.write("\n--- skipped ---\n")
        for old, gname, why in skipped:
            fp.write("%-26s    %-44s %s\n" % (old, gname, why))
    print("full plan: " + str(out.relative_to(REPO)))

    print("\n--- sanitized examples ---")
    for old, new, g in dirty[:12]:
        print("  %-22s %-40s <- %s" % (old, new, g))

    if args.action == "apply":
        files, n = apply_plan(plan)
        print("\napplied %d renames across %d files" % (n, files))
        print("NOW REBUILD and diff the objdiff report -- expected delta is zero.")


if __name__ == "__main__":
    main()
