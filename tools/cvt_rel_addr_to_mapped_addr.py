"""Convert a REL-relative symbol name to the RAM address it lives at when loaded.

    python tools/cvt_rel_addr_to_mapped_addr.py fn_3_1CE90
    python tools/cvt_rel_addr_to_mapped_addr.py lbl_3_data_1594 --rel game

Only two numbers per REL are measured. The rest are derived, because a REL's
image sections are laid out contiguously with 8-byte alignment:

    text_base + text_size  -> align8 -> rodata_base
    rodata_base + rodata_size -> align8 -> data_base

Verified exactly against the game REL's previously hard-coded values
(0x807AD440 rodata, 0x807B1600 data), and the same rule independently
reproduces the menu REL's rodata base found by size-voting against Ghidra.

`.bss` is NOT derivable: it is allocated separately from the image, so the gap
varies (546,360 bytes for the game REL). It has to be measured per REL.

Section sizes come from the repo's own config, so they track the decomp.
"""
import re
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
BUILD = "GYQE01"

# The only measured values. Everything else is computed.
#   text -- REL load address; menus was solved against the AtGameSettingsScreen
#           snapshot (989/1233 exact function-size matches) and is the SAME slot
#           as game: the two RELs are mutually exclusive.
#   bss  -- separately allocated, must be measured; None where unknown.
REL_LOAD = {
    "game":      {"text": 0x8063F094, "bss": 0x808610E0},
    "menus":     {"text": 0x8063F094, "bss": None},
    # Not resident in either Ghidra snapshot, so nothing to solve against yet.
    "unused_rel": {"text": None, "bss": None},
}

_SECTION_ORDER = ("text", "ctors", "dtors", "rodata", "data")

# .ctors/.dtors sit between .text and .rodata but are recorded in the config as
# `type:label` with no size, so their extent cannot be read off. With no static
# constructors each holds a single 4-byte null entry. That is not a guess: it is
# the only value consistent with BOTH known rodata bases --
#   game : 0x8063F094 + 0x16E3A4 + 8 -> 0x807AD440  (matches the measured value)
#   menus: 0x8063F094 + 0x096D94 + 8 -> 0x806D5E30  (matches an independent
#          size-voting solve against Ghidra, 207/276 exact matches)
_LABEL_SECTION_SIZE = {"ctors": 4, "dtors": 4}

_SYM_RE = re.compile(r"^\s*\w+\s*=\s*\.(\w+):0x([0-9A-Fa-f]+);.*?size:0x([0-9A-Fa-f]+)", re.M)
_SPLIT_RE = re.compile(r"\.(\w+)\s+start:0x([0-9A-Fa-f]+)\s+end:0x([0-9A-Fa-f]+)")
_ALIGN_RE = re.compile(r"^\t\.(\w+)\s+type:\w+\s+align:(\d+)", re.M)

# Known-good values, used by --verify to catch drift in the derivation.
_EXPECTED = {"game": {"rodata": 0x807AD440, "data": 0x807B1600}}

_cache = {}


def _cfg(rel, name):
    path = REPO / "config" / BUILD / rel / name
    if not path.exists():
        raise KeyError("no %s for REL %r (%s)" % (name, rel, path))
    return path.read_text(encoding="utf-8", errors="replace")


def section_extents(rel):
    """{section: end offset}. Merged from splits.txt and symbols.txt -- neither is
    complete on its own (menus/splits.txt has no .data block at all)."""
    ext = dict(_LABEL_SECTION_SIZE)
    for sec, _a, b in _SPLIT_RE.findall(_cfg(rel, "splits.txt")):
        ext[sec] = max(ext.get(sec, 0), int(b, 16))
    for m in _SYM_RE.finditer(_cfg(rel, "symbols.txt")):
        sec = m.group(1)
        ext[sec] = max(ext.get(sec, 0), int(m.group(2), 16) + int(m.group(3), 16))
    return ext


def section_aligns(rel):
    return {m.group(1): int(m.group(2)) for m in _ALIGN_RE.finditer(_cfg(rel, "splits.txt"))}


def section_bases(rel):
    """{section: RAM base} for a REL. Raises if the REL's load address is unknown."""
    if rel in _cache:
        return _cache[rel]
    load = REL_LOAD.get(rel)
    if load is None:
        raise KeyError("unknown REL %r; known: %s" % (rel, ", ".join(REL_LOAD)))
    if load["text"] is None:
        raise KeyError(
            "REL %r has no known load address. It is not present in either Ghidra "
            "snapshot, so its base has not been solved. Add it to REL_LOAD once "
            "measured -- do not guess, a wrong base yields plausible but wrong "
            "addresses everywhere." % rel)

    ext = section_extents(rel)
    aligns = section_aligns(rel)
    bases = {"text": load["text"]}
    cur = load["text"]
    for prev, nxt in zip(_SECTION_ORDER, _SECTION_ORDER[1:]):
        cur += ext.get(prev, 0)
        a = aligns.get(nxt, 8)
        cur = (cur + a - 1) & ~(a - 1)
        bases[nxt] = cur
    if load["bss"] is not None:
        bases["bss"] = load["bss"]
    _cache[rel] = bases
    return bases


def verify():
    """Recompute the derived bases and compare against the measured ones."""
    ok = True
    for rel, expect in _EXPECTED.items():
        bases = section_bases(rel)
        for sec, want in expect.items():
            got = bases[sec]
            flag = "OK" if got == want else "MISMATCH"
            ok &= got == want
            print("  %-6s .%-7s computed 0x%08X  measured 0x%08X  %s"
                  % (rel, sec, got, want, flag))
    return ok


def get_curr_offset(name, rel="game"):
    """`fn_3_1CE90` / `lbl_3_data_1594` -> RAM address."""
    parts = name.split("_")
    bases = section_bases(rel)
    if len(parts) == 3 and parts[0] == "fn":
        return bases["text"] + int(parts[2], 16)
    if len(parts) == 4:
        section = parts[2]
        if section not in bases:
            raise KeyError(
                "section .%s of REL %r has no known base (bss must be measured)"
                % (section, rel))
        return bases[section] + int(parts[3], 16)
    raise ValueError("cannot parse symbol name %r" % name)


class _Offsets(dict):
    """Back-compat: `offsets["game"]["data"]` still works, now computed."""

    def __missing__(self, rel):
        value = section_bases(rel)
        self[rel] = value
        return value


offsets = _Offsets()


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    rel = "game"
    if "--rel" in sys.argv:
        rel = sys.argv[sys.argv.index("--rel") + 1]
    if "--verify" in sys.argv:
        sys.exit(0 if verify() else 1)
    if not args:
        for r in REL_LOAD:
            try:
                b = section_bases(r)
                print("%-10s %s" % (r, "  ".join("%s=0x%08X" % (k, v)
                                                 for k, v in sorted(b.items()))))
            except KeyError as e:
                print("%-10s (%s)" % (r, e))
        return
    print("0x%x" % get_curr_offset(args[0], rel))


if __name__ == "__main__":
    main()
