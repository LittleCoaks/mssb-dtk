#!/usr/bin/env python3
"""Diff a unit's literal pool (.rodata / .sdata2) against the target's.

A function whose code is identical but whose float/double/string literals sit
at different pool offsets scores below 100% on relocations alone. That is not a
codegen problem in that function: MWCC emits pooled literals in the order it
first meets them while generating code, so one missing, extra or reordered
literal anywhere earlier in the file shifts every literal after it. This tool
lines the two pools up and says where they first part and which functions own
the literals involved.

    python tools/match_pool.py UNIT [--section .rodata] [--all] [--context N]

    UNIT   objdiff unit name (game/game/stadium/sta_c1) or source path
           (src/game/stadium/sta_c1.c)

Output, in pool order (TARGET | OURS):
    =   same literal on both sides
    -   only in the target: our source never produces this literal
    +   only in ours: our source produces a literal the target does not
    ~   same position, different bytes (often float vs double, or a typo)
Each row names the functions that reference the literal on that side. By
default only the rows around differences are printed; --all prints the pool.

How to read it:
  * A single `-` or `+` early on, with everything after it matching but
    shifted, is one wrong expression: fix that literal and the rest follows.
  * A block that matches but appears in a different place is an ORDER
    problem: the literals are first used in a different order than in the
    target. In a REL built with `-inline deferred`, functions are emitted in
    reverse source order, so the "first" use is in the LAST function in the
    file; an inlined helper pools its literals where it is expanded.
  * `-` and `+` rows with the same value but different sizes are a float in
    one place and a double in the other (an `f` suffix, or a (f32) cast).

Rebuild first; this reads the .o files on disk. Side convention matches
objdiff: left = target, right = ours.
"""
import argparse
import difflib
import json
import struct
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
SHT_SYMTAB, SHT_RELA, SHT_NOBITS = 2, 4, 8
STT_OBJECT, STT_FUNC, STT_SECTION = 1, 2, 3


class Elf:
    """Just enough of a big-endian ELF32 relocatable reader."""

    def __init__(self, path):
        self.data = d = Path(path).read_bytes()
        if d[:4] != b"\x7fELF" or d[4] != 1 or d[5] != 2:
            raise SystemExit(f"{path}: not a big-endian ELF32 object")
        shoff, = struct.unpack_from(">I", d, 0x20)
        shentsize, shnum, shstrndx = struct.unpack_from(">HHH", d, 0x2E)
        raw = [struct.unpack_from(">IIIIIIIIII", d, shoff + i * shentsize) for i in range(shnum)]
        strtab = raw[shstrndx]
        self.sections = []
        for name, typ, flags, addr, off, size, link, info, align, entsize in raw:
            self.sections.append({
                "name": self._str(strtab[4], name), "type": typ, "offset": off, "size": size,
                "link": link, "info": info, "entsize": entsize,
            })
        self.symbols = []
        for sec in self.sections:
            if sec["type"] != SHT_SYMTAB:
                continue
            names = self.sections[sec["link"]]["offset"]
            for i in range(sec["size"] // 16):
                name, value, size, info, other, shndx = struct.unpack_from(">IIIBBH", d, sec["offset"] + i * 16)
                self.symbols.append({"name": self._str(names, name), "value": value, "size": size,
                                     "type": info & 0xF, "bind": info >> 4, "shndx": shndx})

    def _str(self, table_off, idx):
        end = self.data.index(b"\0", table_off + idx)
        return self.data[table_off + idx:end].decode("latin-1")

    def section_index(self, name):
        for i, s in enumerate(self.sections):
            if s["name"] == name:
                return i
        return None

    def section_bytes(self, idx):
        s = self.sections[idx]
        return b"" if s["type"] == SHT_NOBITS else self.data[s["offset"]:s["offset"] + s["size"]]

    def relocations(self, target_idx):
        """(offset, symbol, addend) for every relocation applied to section target_idx."""
        out = []
        for sec in self.sections:
            if sec["type"] != SHT_RELA or sec["info"] != target_idx:
                continue
            for i in range(sec["size"] // 12):
                off, info, addend = struct.unpack_from(">IIi", self.data, sec["offset"] + i * 12)
                out.append((off, self.symbols[info >> 8], addend))
        return out


def resolve_unit(arg):
    units = json.loads((REPO / "objdiff.json").read_text())["units"]
    wanted = arg.replace("\\", "/")
    for u in units:
        src = (u.get("metadata") or {}).get("source_path", "")
        if u["name"] == wanted or src == wanted or src == "src/" + wanted or src == wanted + ".c":
            return u
    raise SystemExit(f"unit '{arg}' not found in objdiff.json (names look like game/game/stadium/sta_c1)")


def pool_entries(elf, section):
    """Split a literal section into entries at symbol boundaries, and name the
    functions that reference each entry."""
    idx = elf.section_index(section)
    if idx is None:
        return []
    data = elf.section_bytes(idx)
    syms = sorted((s for s in elf.symbols if s["shndx"] == idx and s["type"] != STT_SECTION and s["name"]),
                  key=lambda s: (s["value"], -s["size"]))
    bounds = sorted({s["value"] for s in syms} | {0, len(data)})
    names = {}
    for s in syms:
        names.setdefault(s["value"], s["name"])
    entries = []
    for a, b in zip(bounds, bounds[1:]):
        if b > a:
            entries.append({"offset": a, "size": b - a, "bytes": data[a:b], "name": names.get(a, ""), "users": []})

    # who references what: walk .text relocations that land in this section
    text = elf.section_index(".text")
    funcs = sorted((s for s in elf.symbols if s["shndx"] == text and s["type"] == STT_FUNC), key=lambda s: s["value"])

    def func_at(off):
        for f in funcs:
            if f["value"] <= off < f["value"] + f["size"]:
                return f["name"]
        return "?"

    for e in entries:
        e["func_addr"] = {f["name"]: f["value"] for f in funcs}
    by_off = {e["offset"]: e for e in entries}
    starts = [e["offset"] for e in entries]
    if text is not None:
        for off, sym, addend in elf.relocations(text):
            if sym["shndx"] != idx:
                continue
            target = sym["value"] + addend
            # snap to the entry containing the address
            lo = max((s for s in starts if s <= target), default=None)
            if lo is None:
                continue
            fn = func_at(off)
            if fn not in by_off[lo]["users"]:
                by_off[lo]["users"].append(fn)
    return entries


def emission_order(entries):
    """Functions in the order their literals were pooled, judged by literals
    that only one function uses. Returns (names, 'ascending'|'descending'|'mixed'|None)."""
    seen, addr = [], {}
    for e in entries:
        addr = e.get("func_addr", addr)
        if len(e["users"]) == 1 and e["users"][0] not in seen:
            seen.append(e["users"][0])
    if len(seen) < 3:
        return seen, None
    addrs = [addr.get(n, 0) for n in seen]
    up = sum(1 for x, y in zip(addrs, addrs[1:]) if y > x)
    frac = up / (len(addrs) - 1)
    return seen, "ascending" if frac >= 0.8 else ("descending" if frac <= 0.2 else "mixed")


def describe(entry):
    b = entry["bytes"]
    stripped = b.rstrip(b"\0")
    if len(b) == 4:
        return f"f32 {struct.unpack('>f', b)[0]:.9g}  ({b.hex()})"
    if len(b) == 8:
        f = struct.unpack(">d", b)[0]
        two = struct.unpack(">ff", b)
        return f"f64 {f:.17g}  or 2xf32 {two[0]:.6g},{two[1]:.6g}"
    if stripped and all(32 <= c < 127 or c in (9, 10, 13) for c in stripped):
        return "str " + json.dumps(stripped.decode("latin-1"))[:60]
    if len(b) % 4 == 0 and len(b) <= 32:
        return f"{len(b) // 4}xf32 " + ",".join(f"{v:.6g}" for v in struct.unpack(f">{len(b) // 4}f", b))
    return f"{len(b)} bytes {b[:12].hex()}{'...' if len(b) > 12 else ''}"


def side(entry):
    if entry is None:
        return ""
    users = ",".join(entry["users"][:3]) + ("..." if len(entry["users"]) > 3 else "")
    return f"{entry['offset']:5X} {describe(entry)[:44]:44s} {entry['name'][:22]:22s} {users}"


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("unit")
    ap.add_argument("--section", default=".rodata", help=".rodata (default) or .sdata2")
    ap.add_argument("--all", action="store_true", help="print the whole pool, not only the differences")
    ap.add_argument("--context", type=int, default=2)
    args = ap.parse_args()

    unit = resolve_unit(args.unit)
    target = pool_entries(Elf(REPO / unit["target_path"]), args.section)
    ours = pool_entries(Elf(REPO / unit["base_path"]), args.section)
    if not target and not ours:
        raise SystemExit(f"neither object has a {args.section} section")

    key = lambda e: (e["size"], e["bytes"])
    ops = difflib.SequenceMatcher(None, [key(e) for e in target], [key(e) for e in ours], autojunk=False).get_opcodes()
    rows = []  # (mark, target entry, our entry)
    for tag, i1, i2, j1, j2 in ops:
        if tag == "equal":
            rows += [("=", target[i1 + k], ours[j1 + k]) for k in range(i2 - i1)]
        else:
            n = max(i2 - i1, j2 - j1)
            for k in range(n):
                t = target[i1 + k] if i1 + k < i2 else None
                o = ours[j1 + k] if j1 + k < j2 else None
                rows.append(("~" if t and o else ("-" if t else "+"), t, o))

    same = sum(1 for r in rows if r[0] == "=")
    shifted = sum(1 for m, t, o in rows if m == "=" and t["offset"] != o["offset"])
    tsize, osize = sum(e["size"] for e in target), sum(e["size"] for e in ours)
    print(f"{unit['name']} {args.section}: target {len(target)} literals / 0x{tsize:X} bytes, "
          f"ours {len(ours)} literals / 0x{osize:X} bytes")
    print(f"  {same} line up ({shifted} of them at a different offset), "
          f"{sum(1 for r in rows if r[0] == '-')} only in target, {sum(1 for r in rows if r[0] == '+')} only in ours, "
          f"{sum(1 for r in rows if r[0] == '~')} differ in place")

    # the same literal showing up as both '-' and '+' is an ordering problem, not a missing one
    lost = {}
    for m, t, o in rows:
        if m in "-~" and t:
            lost.setdefault(key(t), []).append(t)
    moved = [(o, lost[key(o)][0]) for m, t, o in rows if m in "+~" and o and key(o) in lost]
    if moved:
        print(f"  {len(moved)} literal(s) exist on both sides but in a different ORDER (first use differs):")
        for o, t in moved[:12]:
            print(f"      {describe(o)[:40]:40s} target @{t['offset']:X} ({','.join(t['users'][:2]) or '-'})"
                  f"  ours @{o['offset']:X} ({','.join(o['users'][:2]) or '-'})")

    first = next((k for k, r in enumerate(rows) if r[0] != "="), None)
    if first is None and not shifted:
        print("  pools are identical")
    elif first is not None:
        m, t, o = rows[first]
        e = t or o
        print(f"  first difference: '{m}' at {'target' if t else 'our'} offset 0x{e['offset']:X}, {describe(e)}, "
              f"used by {', '.join(e['users']) or 'nothing'}")

    statics = [o for m, t, o in rows if m != "=" and o and "$localstatic" in o["name"]]
    if statics:
        print(f"  {len(statics)} extra literal(s) are function-local statics ("
              + ", ".join(sorted({o['name'].split('$')[0] for o in statics})) + "):")
        print("     an inline helper with `static const` locals (the sqrt helpers do this) is being expanded here")
        print("     and the target does not have them. See the `dolsqrtf2` / SQRT2_LINKAGE entries in")
        print("     docs/matching_notes.md.")

    t_names, t_dir = emission_order(target)
    o_names, o_dir = emission_order(ours)
    if t_dir and o_dir:
        print(f"  literal order follows function address: target {t_dir}, ours {o_dir}")
        if {t_dir, o_dir} == {"ascending", "descending"}:
            print("  => the two pools are generated in OPPOSITE function order. With `-inline deferred` MWCC emits")
            print("     functions in reverse source order, so the .c file must define its functions in the reverse")
            print("     of the order the target has them (see 'Flipping a 100% unit to Object(Matching)' in")
            print("     docs/matching_notes.md). Reorder the definitions before chasing individual literals.")
        elif t_dir != o_dir:
            print("     target first-use order: " + ", ".join(t_names[:8]))
            print("     our first-use order:    " + ", ".join(o_names[:8]))
    print()

    keep = set(range(len(rows))) if args.all else {
        j for k, r in enumerate(rows) if r[0] != "=" for j in range(k - args.context, k + args.context + 1)}
    last = -1
    print(f"   {'TARGET':>5s}{'':76s} | OURS")
    for k, (m, t, o) in enumerate(rows):
        if k not in keep:
            continue
        if k != last + 1:
            print("   ...")
        last = k
        print(f"{m}  {side(t):98s} | {side(o)}")


if __name__ == "__main__":
    main()
