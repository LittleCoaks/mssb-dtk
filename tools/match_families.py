#!/usr/bin/env python3
"""Group unmatched functions that fail in the SAME way.

When several functions share one mismatching instruction window, the cause is
shared too: an inline helper, an accessor macro, an idiom written the same way
in each place. Grinding them one at a time repeats the same search; solve it
once on the smallest member and apply the fix to the rest.

    python tools/match_survey.py dump [--module game]     # refresh the cache first
    python tools/match_families.py [--module game] [--min 2] [--top 20]
                                   [--loose] [--show FAMILY_NUMBER]

A "window" is a run of differing rows (rows closer than 3 apart are joined).
Windows shorter than --min-window rows (default 3) are ignored: a one-row
difference such as `mr r3, r31` vs `mr r3, r30` recurs everywhere by chance
and says nothing about a shared cause.
Each side is normalised before comparing: registers are renamed by order of
first appearance within the window (rA, rB, fA ...), so two functions with the
same swap in different registers land together; branch targets and stack
offsets are dropped; immediates, opcodes and relocation symbols are kept.

  default   windows must match on BOTH sides (target and ours) exactly
  --loose   match on the target side only: same code wanted, we got it wrong
            in possibly different ways. Bigger families, weaker evidence.

Families are ranked by member count. The member listed first is the smallest
function, the one to work on. `--show N` prints that family's window
(TARGET | OURS) from its smallest member.
"""
import argparse
import collections
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from match_survey import cached_units, function_pairs

REG = re.compile(r"\b([rf])(\d+)\b")
SYM = re.compile(r"[\w$@.]+@(ha|h|l|sda21)\b")


def pool_only(member):
    """True when the two sides differ only in which symbol a relocation names."""
    strip = lambda rows: [SYM.sub(r"SYM@\1", r) for r in rows]
    return strip(member["target"]) == strip(member["ours"])


def normalise(texts):
    """Rename registers by first appearance; drop branch targets and r1 offsets."""
    names, out = {}, []
    for t in texts:
        if not t:
            out.append("")
            continue
        mnemonic = t.split(" ", 1)[0]
        if mnemonic.startswith("b") and mnemonic not in ("bl", "blr", "bctr", "bctrl"):
            t = mnemonic  # conditional/unconditional branch: the target address is noise
        t = re.sub(r"-?0x[0-9a-f]+\(r1\)", "STK(r1)", t)

        def rename(m):
            if m.group(0) in ("r1", "r2", "r13"):
                return m.group(0)
            key = m.group(0)
            if key not in names:
                names[key] = m.group(1) + chr(ord("A") + len([k for k in names if k[0] == m.group(1)]) % 26)
            return names[key]
        out.append(REG.sub(rename, t))
    return tuple(out)


def windows(target, ours, join=3):
    """Yield (start, end) index ranges of differing rows, joined when close."""
    li, ri = target["instructions"], ours.get("instructions", [])
    n = max(len(li), len(ri))
    diff = [k for k in range(n)
            if (li[k] if k < len(li) else {}).get("diff_kind") or (ri[k] if k < len(ri) else {}).get("diff_kind")]
    if not diff:
        return
    start = prev = diff[0]
    for k in diff[1:]:
        if k - prev > join:
            yield start, prev + 1
            start = k
        prev = k
    yield start, prev + 1


def text(rows, k):
    return rows[k].get("instruction", {}).get("formatted", "") if k < len(rows) else ""


def collect(module, loose, min_len, max_len):
    fams = collections.defaultdict(list)
    for unit, data in cached_units(module):
        for target, ours in function_pairs(data):
            li, ri = target["instructions"], ours.get("instructions", [])
            for a, b in windows(target, ours):
                if b - a > max_len or b - a < min_len:
                    continue  # too long: a whole-function problem; too short: coincidence
                tn = normalise([text(li, k) for k in range(a, b)])
                on = normalise([text(ri, k) for k in range(a, b)])
                key = tn if loose else (tn, on)
                fams[key].append({"unit": unit, "fn": target["name"], "size": int(target["size"]),
                                  "pct": target["match_percent"], "range": (a, b),
                                  "target": [text(li, k) for k in range(a, b)],
                                  "ours": [text(ri, k) for k in range(a, b)]})
    out = []
    for key, members in fams.items():
        fns = {}
        for m in members:  # one entry per function, but remember how often the window recurs in it
            fns.setdefault((m["unit"], m["fn"]), dict(m, hits=0))["hits"] += 1
        out.append(sorted(fns.values(), key=lambda m: m["size"]))
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--module", default="game")
    ap.add_argument("--min", type=int, default=2, help="smallest family to report (default 2 functions)")
    ap.add_argument("--top", type=int, default=20)
    ap.add_argument("--loose", action="store_true", help="group on the target side only")
    ap.add_argument("--min-window", type=int, default=3, help="ignore windows shorter than this many rows")
    ap.add_argument("--max-window", type=int, default=24, help="ignore windows longer than this many rows")
    ap.add_argument("--no-pool", action="store_true",
                    help="hide families that differ only in a literal/data symbol (use match_pool.py for those)")
    ap.add_argument("--show", type=int, metavar="N", help="print family N's window")
    args = ap.parse_args()

    fams = [f for f in collect(args.module, args.loose, args.min_window, args.max_window) if len(f) >= args.min]
    if args.no_pool:
        fams = [f for f in fams if not pool_only(f[0])]
    # most members first; among equals, the one that would complete the most code
    fams.sort(key=lambda f: (-len(f), -len(f[0]["target"]), -sum(m["size"] for m in f)))
    if not fams:
        raise SystemExit("no families found; run `match_survey.py dump` after a rebuild")

    if args.show is not None:
        if not 1 <= args.show <= len(fams):
            raise SystemExit(f"family {args.show} does not exist (1..{len(fams)}; numbering depends on the flags used)")
        fam = fams[args.show - 1]
        m = fam[0]
        print(f"family {args.show}: {len(fam)} functions; window from {m['fn']} ({m['unit']}) rows {m['range'][0]}-{m['range'][1] - 1}")
        print(f"   {'TARGET':42s} | OURS")
        for t, o in zip(m["target"], m["ours"]):
            print(f"{'!' if t != o else ' '}  {t:42s} | {o}")
        print()
        for x in fam:
            print(f"   {x['fn']:44s} {x['unit']:40s} {x['size']:5d} bytes {x['pct']:6.2f}%  x{x['hits']}")
        return

    covered = {(m["unit"], m["fn"]) for f in fams for m in f}
    print(f"{len(fams)} families covering {len(covered)} functions in '{args.module}' "
          f"({'target side only' if args.loose else 'both sides identical'}, windows of {args.min_window}-{args.max_window} rows)")
    print("start with the first function listed in each family; `--show N` prints the window\n")
    for n, fam in enumerate(fams[:args.top], 1):
        units = sorted({m["unit"].split("_", 2)[-1] for m in fam})
        sole = sum(1 for m in fam if m["pct"] >= 99.0)
        print(f"#{n:<3d} {len(fam):3d} functions, {sum(m['size'] for m in fam):6d} bytes, {len(fam[0]['target'])} rows, "
              f"{sole} of them >= 99%   units: {', '.join(units)[:70]}")
        if pool_only(fam[0]):
            print("      [pool] differs only in the symbol a relocation names; see match_pool.py")
        print(f"      target: {' ; '.join(t for t in fam[0]['target'] if t)[:110]}")
        print(f"      ours:   {' ; '.join(o for o in fam[0]['ours'] if o)[:110]}")
        print("      " + ", ".join(f"{m['fn']}({m['size']})" for m in fam[:6]) + (" ..." if len(fam) > 6 else ""))


if __name__ == "__main__":
    main()
