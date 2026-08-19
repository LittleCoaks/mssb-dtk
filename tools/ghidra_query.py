#!/usr/bin/env python3
"""
Query the MarioSuperstarBaseballDecomp Ghidra project from the decomp repo.

The Ghidra project is far ahead of this repo on naming: functions, globals,
struct types and enums already carry real names there. This tool resolves a
decomp symbol (or raw address) to its Ghidra name, and can print Ghidra's
decompiler output for it -- useful when writing a function from scratch.

The Ghidra project is a *shared* project whose server is unreachable; headless
still reads the local checkout cache fine (it logs "Server access denied" and
continues read-only). Nothing here ever writes to the Ghidra project.

Programs:
    in_game               RAM snapshot with the game REL loaded  (src/game/*)
    AtGameSettingsScreen  RAM snapshot with the menu REL loaded

Usage:
    python tools/ghidra_query.py refresh                  # rebuild .ghidra_cache
    python tools/ghidra_query.py name fn_3_1CE90 ...      # decomp name -> Ghidra name
    python tools/ghidra_query.py decomp fn_3_1CE90 ...    # Ghidra decompiler C
    python tools/ghidra_query.py file src/game/rep_720.c  # whole-file name table
    python tools/ghidra_query.py data 0x807b2b94          # global/data label lookup
"""
import argparse
import re
import subprocess
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
GHIDRA = Path(r"D:\15165\Documents\Rio Modding Project\Project Rio\Ghidra 11.0.3")
PROJECT = "MarioSuperstarBaseballDecomp"
CACHE = REPO / ".ghidra_cache"
BUILD = "GYQE01"  # retail; the Ghidra snapshots are of this build
SCRIPT_DIR = Path(__file__).resolve().parent / "ghidra_scripts"

# Per-section RAM bases, reused from the existing helper so the two never drift.
sys.path.insert(0, str(Path(__file__).resolve().parent))
from cvt_rel_addr_to_mapped_addr import section_bases  # noqa: E402

PROGRAMS = ("in_game", "AtGameSettingsScreen")


def _rel_bases(rel):
    """Section bases for a REL, or None if its load address is unknown."""
    try:
        return section_bases(rel)
    except KeyError:
        return None


def run_headless(program, mode, targets, outfile):
    cmd = [str(GHIDRA / "support" / "analyzeHeadless.bat"), str(GHIDRA), PROJECT,
           "-process", program, "-noanalysis", "-readOnly",
           "-scriptPath", str(SCRIPT_DIR),
           "-postScript", "MssbDump.py", mode] + list(targets) + [str(outfile)]
    r = subprocess.run(cmd, capture_output=True, text=True)
    if "WROTE" not in r.stdout:
        sys.exit("headless failed:\n" + r.stdout[-3000:] + r.stderr[-2000:])
    return Path(outfile)


def cmd_refresh(_args):
    CACHE.mkdir(exist_ok=True)
    for p in PROGRAMS:
        for m in ("symbols", "data"):
            run_headless(p, m, [], CACHE / (p + "." + m + ".txt"))
            print("  " + p + "." + m + ".txt")


def load_symbols(program="in_game"):
    path = CACHE / (program + ".symbols.txt")
    if not path.exists():
        sys.exit("missing " + str(path) + " -- run: python tools/ghidra_query.py refresh")
    out = {}
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        a, size, name = line.split("\t")
        out[int(a, 16)] = (int(size), name)
    return out


def load_data(program="in_game"):
    path = CACHE / (program + ".data.txt")
    out = {}
    if not path.exists():
        return out
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        a, size, typ, name = line.split("\t", 3)
        out[int(a, 16)] = (int(size), typ, name)
    return out


_MAPPED = None

_MAPPED_PAT = re.compile(
    r"// \.text:0x([0-9A-Fa-f]+) size:0x([0-9A-Fa-f]+) mapped:0x([0-9A-Fa-f]+)\s*\n"
    r"(?:[A-Za-z_][\w \*]*?)\b(\w+)\s*\(")


def mapped_index():
    """{decomp function name: (ram_addr, size, source file)} from the // .text: comments."""
    global _MAPPED
    if _MAPPED is not None:
        return _MAPPED
    idx = {}
    for c in (REPO / "src").rglob("*.c"):
        text = c.read_text(encoding="utf-8", errors="replace")
        for m in _MAPPED_PAT.finditer(text):
            _, size, mapped, name = m.groups()
            idx[name] = (int(mapped, 16), int(size, 16), c.relative_to(REPO).as_posix())
    _MAPPED = idx
    return idx


_CONFIG_RE = re.compile(
    r"^\s*(\w+)\s*=\s*\.(\w+):0x([0-9A-Fa-f]+);(.*)$")


def config_symbols(with_meta=False):
    """{name: ram addr} from config/*/symbols.txt.

    Main-DOL addresses are already absolute. Game-REL addresses are
    section-relative and get rebased through the per-section RAM bases.
    """
    out = {}
    # Only the retail build. The demo builds' RELs have their own load addresses;
    # rebasing their offsets with GYQE01's bases would yield plausible-looking
    # but wrong addresses.
    for p in (REPO / "config" / BUILD).rglob("symbols.txt"):
        # A config directly under the build dir is the main DOL (absolute
        # addresses); one nested a level deeper is a REL (section-relative).
        rel = p.parent.name if p.parent.name != BUILD else None
        bases = _rel_bases(rel) if rel else None
        if rel and bases is None:
            continue  # REL whose load address has not been solved
        for line in p.read_text(encoding="utf-8", errors="replace").splitlines():
            m = _CONFIG_RE.match(line)
            if not m:
                continue
            name, section, addr, meta = m.groups()
            a = int(addr, 16)
            if rel:
                base = bases.get(section)
                if base is None:
                    continue  # e.g. .bss where it has not been measured
                a += base
            out.setdefault(name, (a, section, meta, p) if with_meta else a)
    return out


def resolve(token):
    """decomp symbol name or 0xADDR -> ram address (or None)"""
    if token.lower().startswith("0x"):
        return int(token, 16)
    mi = mapped_index()
    if token in mi:
        return mi[token][0]
    return config_symbols().get(token)


def lookup(addr):
    for p in PROGRAMS:
        syms = load_symbols(p)
        if addr in syms:
            return p, syms[addr]
    return None, None


def cmd_name(args):
    for t in args.targets:
        a = resolve(t)
        if a is None:
            print("%-24s -> (address unknown; not in src/ mapped comments or config symbols)" % t)
            continue
        prog, hit = lookup(a)
        if hit is None:
            print("%-24s 0x%08x -> (no function at this address in Ghidra)" % (t, a))
        else:
            size, name = hit
            flag = "   [unnamed in Ghidra]" if name.startswith("FUN_") else ""
            print("%-24s 0x%08x size=%-6d -> %s%s   (%s)" % (t, a, size, name, flag, prog))


def cmd_file(args):
    text = (REPO / args.path).read_text(encoding="utf-8", errors="replace")
    syms = load_symbols("in_game")
    rows = list(_MAPPED_PAT.finditer(text))
    named = 0
    for m in rows:
        _, size, mapped, name = m.groups()
        a = int(mapped, 16)
        size = int(size, 16)
        hit = syms.get(a)
        gname = hit[1] if hit else "(not a function in Ghidra)"
        warn = ""
        if hit and hit[0] != size:
            warn = "  !! ghidra size %d != %d" % (hit[0], size)
        if hit and not gname.startswith("FUN_"):
            named += 1
        print("  %-14s 0x%08x %6d  %s%s" % (name, a, size, gname, warn))
    print("\n%d functions, %d named in Ghidra" % (len(rows), named))


def cmd_decomp(args):
    addrs = []
    for t in args.targets:
        a = resolve(t)
        if a is None:
            print("// " + t + ": address unknown", file=sys.stderr)
            continue
        addrs.append("0x%08x" % a)
    if not addrs:
        sys.exit("nothing to decompile")
    prog = args.program
    if prog is None:
        prog = "in_game"
        syms = load_symbols("in_game")
        if not any(int(a, 16) in syms for a in addrs):
            prog = "AtGameSettingsScreen"
    CACHE.mkdir(exist_ok=True)
    out = CACHE / "decomp.out.c"
    run_headless(prog, "decomp", addrs, out)
    print(out.read_text(encoding="utf-8", errors="replace").replace("\r\n", "\n"))


def cmd_data(args):
    for p in PROGRAMS:
        d = load_data(p)
        for t in args.targets:
            a = resolve(t)
            if a is not None and a in d:
                size, typ, name = d[a]
                print("%-20s 0x%08x size=%-6d %-24s %s   (%s)" % (t, a, size, typ, name, p))


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("refresh").set_defaults(func=cmd_refresh)
    p = sub.add_parser("name"); p.add_argument("targets", nargs="+"); p.set_defaults(func=cmd_name)
    p = sub.add_parser("file"); p.add_argument("path"); p.set_defaults(func=cmd_file)
    p = sub.add_parser("decomp"); p.add_argument("targets", nargs="+")
    p.add_argument("--program", choices=PROGRAMS); p.set_defaults(func=cmd_decomp)
    p = sub.add_parser("data"); p.add_argument("targets", nargs="+"); p.set_defaults(func=cmd_data)
    args = ap.parse_args()
    args.func(args)


if __name__ == "__main__":
    main()
