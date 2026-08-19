#!/usr/bin/env python3
"""
Pair Ghidra enums with the decomp's own enums, and list the ones we lack.

    python tools/ghidra_enums.py                 # summary + pairings
    python tools/ghidra_enums.py --constants     # per-constant mapping
    python tools/ghidra_enums.py --missing       # Ghidra enums with no counterpart

Enums cannot be matched the way symbols are: there is no address to anchor on.
Matching a single constant by value is hopeless -- in this game hundreds of
constants equal 1. So the pairing is done at the level of the whole enum: two
enums correspond when their *value sets* line up, which is a far stronger signal
than any individual member.

Once a pair is established, constants map by value within that pair, which is
exact.

Needs the Ghidra type dump:  ghidra_query.py refresh  +  the `types` mode.
"""
import argparse
import collections
import re
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
TYPES = REPO / ".ghidra_cache" / "in_game.types.txt"

# Ghidra emits the same logical enum at several widths; they are duplicates.
WIDTH_SUFFIX = re.compile(r"_(byte|short|int|word|long)$", re.I)


def ghidra_enums():
    out = {}
    cur = None
    for line in TYPES.read_text(encoding="utf-8", errors="replace").splitlines():
        if line.startswith("ENUM\t"):
            cur = line.split("\t")[1]
            out.setdefault(cur, {})
        elif line.startswith(("STRUCT\t", "UNION\t")):
            cur = None
        elif line.startswith("\t") and cur is not None:
            p = line.split("\t")
            if len(p) >= 3:
                try:
                    out[cur][p[1]] = int(p[2], 16)
                except ValueError:
                    pass
    return {k: v for k, v in out.items() if v}


ENUM_START = re.compile(r"^\s*(typedef\s+)?enum\b")
# The value may be a number OR another constant's name -- the decomp writes
# `INPUT_BUTTON_A = PAD_BUTTON_A`, which a numbers-only pattern silently drops.
MEMBER = re.compile(r"^\s*(\w+)\s*(?:=\s*(-?(?:0[xX])?[0-9A-Fa-f]+|\w+))?\s*,?\s*$")
CLOSE = re.compile(r"^\s*}\s*(\w+)?\s*;")
BLOCK_COMMENT = re.compile(r"/\*.*?\*/")
DEFINE_NUM = re.compile(r"^\s*#\s*define\s+(\w+)\s+\(?(-?(?:0[xX])?[0-9A-Fa-f]+)\)?\s*$")


def _strip(line):
    """Drop comments. Members are written `/* 0 0x00 */ CHAR_ID_MARIO,` -- leaving
    the block comment in place makes the member pattern miss the name entirely."""
    return BLOCK_COMMENT.sub("", line.split("//")[0])


def decomp_enums():
    """{enum name: {member: value}} from the repo's headers."""
    out = {}
    symbolic = []          # (enum, member, referenced-name)
    consts = {}            # numeric #defines, to resolve symbolic values
    for h in (REPO / "include").rglob("*.h"):
        for line in h.read_text(encoding="utf-8", errors="replace").splitlines():
            d = DEFINE_NUM.match(line)
            if d:
                try:
                    consts[d.group(1)] = int(d.group(2), 0)
                except ValueError:
                    pass
    for h in (REPO / "include").rglob("*.h"):
        depth = 0
        in_enum = False
        last = -1
        members = {}
        for line in h.read_text(encoding="utf-8", errors="replace").splitlines():
            s = _strip(line)
            if depth == 0 and ENUM_START.match(s):
                in_enum, last, members = True, -1, {}
            elif in_enum and depth > 0:
                m = MEMBER.match(s)
                if m:
                    raw = m.group(2)
                    if raw is None:
                        v = last + 1
                    else:
                        try:
                            v = int(raw, 0)
                        except ValueError:
                            v = consts.get(raw)          # symbolic: PAD_BUTTON_A
                            if v is None:
                                symbolic.append((m.group(1), raw))
                                v = last + 1
                    members[m.group(1)] = v
                    last = v
            prev = depth
            depth = max(0, depth + s.count("{") - s.count("}"))
            if in_enum and prev > 0 and depth == 0:
                c = CLOSE.match(s)
                name = c.group(1) if c and c.group(1) else "(anon@%s)" % h.name
                if members:
                    out.setdefault(name, {}).update(members)
                in_enum = False
    return out


def _common_prefix(names):
    """Longest shared `word_` prefix among an enum's members."""
    if len(names) < 2:
        return ""
    first = min(names)
    last = max(names)
    i = 0
    while i < min(len(first), len(last)) and first[i] == last[i]:
        i += 1
    cut = first[:i].rfind("_")
    return first[:cut + 1] if cut >= 0 else ""


def normalized(members):
    """{bare member name: value} -- prefix stripped, case and underscores dropped."""
    pre = _common_prefix(list(members))
    out = {}
    for m, v in members.items():
        b = m[len(pre):] if pre and m.startswith(pre) else m
        out[b.lower().replace("_", "")] = v
    return out


def pair(gh, dec, min_overlap=3, min_ratio=0.35):
    """Ghidra enum -> best decomp enum.

    Scored on members whose *name* matches after normalisation AND whose value
    agrees. Value overlap alone is worthless here: STADIUM_ID holds 0..6, so
    every small sequential enum "matches" it perfectly.

    The threshold is deliberately loose. A correct pair often agrees on well
    under half its members: Ghidra and the decomp name the ~30 character
    variants differently (`Toad_B_` vs `CHAR_ID_TOAD_BLUE`), so CHAR_ID matches
    at 43% while still being unambiguously the right answer. The score is
    reported so a human can judge rather than being trusted blindly.
    """
    dnorm = {n: normalized(v) for n, v in dec.items()}
    pairs, unmatched = {}, []
    for gname, gmembers in gh.items():
        gn = normalized(gmembers)
        if len(gn) < min_overlap:
            unmatched.append((gname, None, 0.0))
            continue
        best, score = None, 0.0
        for dname, dn in dnorm.items():
            # A member matches when the values agree AND one normalised name
            # contains the other. Exact equality is too strict: the decomp's
            # INPUT_BUTTON_LEFT reduces to "buttonleft" against Ghidra's "left",
            # because the two sides carry different amounts of prefix.
            agree = 0
            for k, v in gn.items():
                for dk, dv in dn.items():
                    if dv == v and (dk == k or dk.endswith(k) or k.endswith(dk)):
                        agree += 1
                        break
            if agree < min_overlap:
                continue
            r = agree / len(gn)
            if r > score:
                best, score = dname, r
        if best and score >= min_ratio:
            pairs[gname] = (best, score)
        else:
            unmatched.append((gname, best, score))
    return pairs, unmatched


def canonical(name):
    return WIDTH_SUFFIX.sub("", name)


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--constants", action="store_true")
    ap.add_argument("--missing", action="store_true")
    ap.add_argument("--only", help="restrict to Ghidra enums whose name contains this")
    args = ap.parse_args()

    if not TYPES.exists():
        sys.exit("missing %s -- run ghidra_query.py refresh and the types dump" % TYPES)
    gh, dec = ghidra_enums(), decomp_enums()
    if args.only:
        gh = {k: v for k, v in gh.items() if args.only.lower() in k.lower()}
    pairs, unmatched = pair(gh, dec)

    print("ghidra enums: %d   decomp enums: %d" % (len(gh), len(dec)))
    print("paired: %d   unpaired: %d" % (len(pairs), len(unmatched)))

    if args.constants:
        print("\n=== per-constant mapping (by value, within a paired enum) ===")
        for gname, (dname, score) in sorted(pairs.items()):
            if WIDTH_SUFFIX.search(gname) and canonical(gname) in pairs:
                continue  # skip width duplicates
            gn_all = normalized(gh[gname])
            dn_all = normalized(dec[dname])
            byval = collections.defaultdict(list)
            for m, v in dec[dname].items():
                byval[v].append(m)
            print("\n  %s  ->  %s   (%.0f%% of values line up)" % (gname, dname, score * 100))
            pre_g = _common_prefix(list(gh[gname]))
            for m, v in sorted(gh[gname].items(), key=lambda kv: kv[1]):
                bare = m[len(pre_g):] if pre_g and m.startswith(pre_g) else m
                bare = bare.lower().replace("_", "")
                # prefer the same-value decomp constant whose name also lines up
                cands = byval.get(v, [])
                exact = [c for c in cands
                         if (lambda x: x == bare or x.endswith(bare) or bare.endswith(x))(
                             c.lower().replace("_", "").replace(
                                 _common_prefix(list(dec[dname])).lower().replace("_", ""), "", 1))]
                tgt = exact or cands
                print("      %-34s = %-6s -> %s" % (m, v, ", ".join(tgt) if tgt else "(no decomp constant)"))
    elif args.missing:
        print("\n=== Ghidra enums with no decomp counterpart ===")
        seen = set()
        for gname, best, score in sorted(unmatched, key=lambda x: -len(gh[x[0]])):
            c = canonical(gname)
            if c in seen:
                continue
            seen.add(c)
            near = "  (closest: %s at %.0f%%)" % (best, score * 100) if best else ""
            print("  %-38s %3d members%s" % (gname, len(gh[gname]), near))
    else:
        print("\n=== paired ===")
        seen = set()
        for gname, (dname, score) in sorted(pairs.items(), key=lambda kv: -kv[1][1]):
            c = canonical(gname)
            if c in seen:
                continue
            seen.add(c)
            print("  %-34s -> %-30s %.0f%%" % (gname, dname, score * 100))


if __name__ == "__main__":
    main()
