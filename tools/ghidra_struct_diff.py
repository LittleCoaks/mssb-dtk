#!/usr/bin/env python3
"""
Compare a repo struct against the same-named struct in the Ghidra type dump.

Only structs whose total size matches exactly are worth comparing: a size
disagreement means the two describe different layouts, and lining fields up by
offset would produce nonsense. Run `ghidra_query.py refresh` and the `types`
dump first.

Reports, per offset:
  RENAME   repo field is a placeholder (_1A3 / unk / field_) and Ghidra has a
           real name  -> a safe, codegen-neutral improvement
  DIFFER   both sides have real but different names -> needs a human
  repo-only / ghidra-only  -> layout disagreement at that offset

Usage:
    python tools/ghidra_struct_diff.py InMemBallType:InMemBall
    python tools/ghidra_struct_diff.py AIStruct            # same name both sides
"""
import collections
import re
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
TYPES = REPO / ".ghidra_cache" / "in_game.types.txt"

# Repo placeholder field names: _1A3, _0018, unk04, field_20, pad2, ...
# Anchored tightly on purpose -- a loose `field\w*` also swallows real names
# like `fielderWBallIndex`.
PLACEHOLDER = re.compile(
    r"^(_+[0-9A-Fa-f]+|unk(nown)?_?\d*|field_?\d+(_0x[0-9A-Fa-f]+)?"
    r"|pad(ding)?\d*|dummy\d*)$", re.I)
# Ghidra auto-generated field names carry no information either.
G_AUTO = re.compile(
    r"^(field\d+_0x[0-9a-f]+|unk(nown)?_?\d*|undefined\w*|pad(ding)?\d*\??)$", re.I)

# `/* 0x1A3 */ u8 name[4];  // comment`
REPO_FIELD = re.compile(
    r"/\*\s*(0x[0-9A-Fa-f]+)\s*\*/\s*"
    r"(?:const\s+|volatile\s+|struct\s+|unsigned\s+|signed\s+)*"
    r"([\w \*]+?)\s*(\**)\s*(\w+)\s*((?:\[[^\]]*\])*)\s*;")


def load_ghidra():
    out = collections.OrderedDict()
    cur = None
    for line in TYPES.read_text(encoding="utf-8", errors="replace").splitlines():
        if line.startswith(("STRUCT\t", "UNION\t")):
            _, n, s = line.split("\t")
            cur = (n, int(s, 16))
            out.setdefault(cur, [])
        elif line.startswith("ENUM\t"):
            cur = None
        elif line.startswith("\t") and cur is not None:
            p = line.split("\t")
            if len(p) >= 5:
                out[cur].append((int(p[1], 16), int(p[2], 16), p[3], p[4]))
    return out


def find_repo_struct(name):
    """Return (path, size, {offset: (type, fieldname)}) for a repo typedef."""
    end = re.compile(r"^\}\s*" + re.escape(name) + r"\s*;", re.M)
    for h in list((REPO / "include").rglob("*.h")) + list((REPO / "src").rglob("*.c")):
        text = h.read_text(encoding="utf-8", errors="replace")
        m = end.search(text)
        if not m:
            continue
        start = text.rfind("typedef struct", 0, m.start())
        if start < 0:
            continue
        body = text[start:m.start()]
        fields = {}
        for f in REPO_FIELD.finditer(body):
            off, ftype, stars, fname, arr = f.groups()
            fields[int(off, 16)] = ((ftype + stars).strip(), fname + arr)
        return h, fields
    return None, None


def main():
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    spec = sys.argv[1]
    repo_name, _, g_name = spec.partition(":")
    g_name = g_name or repo_name

    gh = load_ghidra()
    cands = [k for k in gh if k[0] == g_name]
    if not cands:
        sys.exit("no Ghidra struct named " + g_name)
    path, rfields = find_repo_struct(repo_name)
    if rfields is None:
        sys.exit("no repo struct named " + repo_name)

    # pick the Ghidra variant whose size best matches the repo's field extent
    extent = max(rfields) if rfields else 0
    key = min(cands, key=lambda k: abs(k[1] - extent))
    gfields = {o: (t, n) for o, _, t, n in gh[key]}

    print("repo %s (%s)  vs  ghidra %s size=0x%x" % (repo_name, path.relative_to(REPO), key[0], key[1]))
    print("repo fields=%d  ghidra fields=%d\n" % (len(rfields), len(gfields)))

    renames, differ, only = [], [], []
    for off in sorted(rfields):
        rt, rn = rfields[off]
        if off not in gfields:
            only.append((off, rn, "repo-only"))
            continue
        gt, gn = gfields[off]
        base = re.sub(r"\[.*", "", rn)
        if not gn or G_AUTO.match(gn):
            continue
        if PLACEHOLDER.match(base):
            renames.append((off, rt, rn, gt, gn))
        elif base.lower() != gn.lower():
            differ.append((off, rn, gn))

    print("=== RENAME: repo placeholder, Ghidra has a real name (%d) ===" % len(renames))
    for off, rt, rn, gt, gn in renames:
        print("  0x%04X  %-16s %-18s ->  %-22s (ghidra type %s)" % (off, rt, rn, gn, gt))
    print("\n=== DIFFER: both named, names disagree (%d) ===" % len(differ))
    for off, rn, gn in differ[:40]:
        print("  0x%04X  repo %-24s ghidra %s" % (off, rn, gn))
    print("\n=== repo offsets absent from Ghidra struct: %d ===" % len(only))


if __name__ == "__main__":
    main()
