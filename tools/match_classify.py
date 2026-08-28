#!/usr/bin/env python3
"""
Stage 0/1 of the decomp matching pipeline.

IMPORTANT -- objdiff side convention (verified empirically, easy to get
backwards): in `objdiff-cli diff` JSON output,
    left  = the TARGET  (the original game binary, named via config/*/symbols.txt)
    right = OUR BUILD   (compiled from src/, anonymous pool constants appear as @N)
So a fix means changing our source/config until `right` looks like `left`.
symbols.txt names the *target* side, which is why renaming an entry there to
match our source's name is what closes a SYMBOL_NAME gap.

Stage 0 (classify): for every unmatched function, look at *why* it doesn't
match before generating any code. Buckets:

  SYMBOL_NAME     Our compiled output references a differently-named symbol
                  than the target at the same address, but the surrounding
                  code is otherwise identical. Free fix: rename the entry in
                  config/*/symbols.txt. No LLM involved.
  CONST_POOL      Mismatch is a data/rodata relocation where the target's
                  symbol is anonymous (@N) or a per-unit local pool label.
                  Usually a file-wide constant-ordering issue that affects
                  several functions at once -- needs a dedicated
                  cross-function tool (Stage 2), not a per-function fix.
  STRUCT_LAYOUT   Mismatch is a plain immediate (not a relocation) off by a
                  small constant -- usually a wrong struct size/offset.
                  Needs header investigation (Stage 3).
  REGISTER_ALLOC  Same opcodes/shape, only register numbers differ. Needs
                  C-level restructuring (variable order/count), which local
                  models have consistently failed to find unassisted.
  LOGIC           Real instruction differences (inserted/deleted
                  instructions, differing opcodes). The only bucket actually
                  suited to a code-generation loop (Stage 4 / match_loop.py).
  MATCHED         Already 100%.

Stage 1 (fix): for functions classified purely as SYMBOL_NAME, resolve the
target address, rename the config/*/symbols.txt entry, rebuild, and verify
the score actually improved before keeping the change.

Usage:
    python tools/match_classify.py scan                 # report only, whole project
    python tools/match_classify.py scan --unit UNIT      # report only, one unit
    python tools/match_classify.py fix                  # apply SYMBOL_NAME fixes project-wide
    python tools/match_classify.py fix --function NAME   # fix one function only
"""
import argparse
import functools
import json
import os
import re
import shutil
import subprocess
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent


@functools.lru_cache(maxsize=1)
def resolve_objdiff_cli() -> Path:
    """Find objdiff-cli: MSSB_OBJDIFF_CLI env override, then the copy the
    project's own build already downloads to build/tools/, then PATH.
    Resolved lazily (and cached) so e.g. --help works without a build."""
    env = os.environ.get("MSSB_OBJDIFF_CLI")
    if env:
        p = Path(env)
        if not p.is_file():
            raise SystemExit(f"MSSB_OBJDIFF_CLI={env} does not exist")
        return p

    exe = "objdiff-cli.exe" if os.name == "nt" else "objdiff-cli"
    built = REPO / "build" / "tools" / exe
    if built.is_file():
        return built

    found = shutil.which("objdiff-cli")
    if found:
        return Path(found)

    raise SystemExit(
        "objdiff-cli not found. Run `ninja` once (it downloads objdiff-cli to "
        f"{built.relative_to(REPO)} like the rest of the build's tools), or set "
        "MSSB_OBJDIFF_CLI to an existing binary's path."
    )


MODULE_SYMBOLS = {
    "main": REPO / "config" / "GYQE01" / "symbols.txt",
    "game": REPO / "config" / "GYQE01" / "game" / "symbols.txt",
    "menus": REPO / "config" / "GYQE01" / "menus" / "symbols.txt",
    "debug": REPO / "config" / "GYQE01" / "debug" / "symbols.txt",
}

AUTO_LABEL_RE = re.compile(r"^lbl_([0-9A-Fa-f]{8})$")
LOCAL_POOL_RE = re.compile(r"^lbl_\d+_rodata_[0-9A-Fa-f]+$")
ANON_RE = re.compile(r"^@\d+$")

CATEGORIES = (
    "SYMBOL_NAME",
    "CONST_POOL",
    "STRUCT_LAYOUT",
    "REGISTER_ALLOC",
    "LOGIC",
)


def run_ninja():
    r = subprocess.run(["ninja"], cwd=REPO, capture_output=True, text=True)
    return r.returncode == 0, r.stdout + r.stderr


def objdiff_unit(unit: str):
    r = subprocess.run(
        [str(resolve_objdiff_cli()), "diff", "-p", str(REPO), "-u", unit, "-o", "-", "--format", "json"],
        capture_output=True, text=True,
    )
    if r.returncode != 0:
        raise RuntimeError(f"objdiff-cli failed for unit {unit}: {r.stderr}")
    return json.loads(r.stdout)


def find_symbol(data, side, name):
    for s in data.get(side, {}).get("symbols", []):
        if s.get("name") == name:
            return s
    return None


def symbol_name_at(symbols, index):
    if index is None or index < 0 or index >= len(symbols):
        return None
    return symbols[index].get("name")


def classify_instruction_pair(left_ins, right_ins, left_symbols, right_symbols):
    """Classify a single mismatched instruction. Returns a category string."""
    kind = left_ins.get("diff_kind")
    if kind in ("DIFF_INSERT", "DIFF_DELETE"):
        return "LOGIC"

    l_instr = left_ins.get("instruction")
    r_instr = right_ins.get("instruction") if right_ins else None
    if l_instr is None or r_instr is None:
        return "LOGIC"

    l_reloc = l_instr.get("relocation")
    r_reloc = r_instr.get("relocation")

    # R_PPC_NONE is a synthetic "addend" annotation objdiff attaches to plain
    # immediates (e.g. struct offsets) -- not a real symbol reference.
    l_is_real_reloc = l_reloc and l_reloc.get("type_name") != "R_PPC_NONE"
    r_is_real_reloc = r_reloc and r_reloc.get("type_name") != "R_PPC_NONE"

    if l_is_real_reloc and r_is_real_reloc:
        r_name = symbol_name_at(right_symbols, r_reloc.get("target_symbol"))
        if r_name is None or ANON_RE.match(r_name) or LOCAL_POOL_RE.match(r_name):
            return "CONST_POOL"
        return "SYMBOL_NAME"

    if l_reloc and r_reloc and l_reloc.get("type_name") == "R_PPC_NONE" and r_reloc.get("type_name") == "R_PPC_NONE":
        # Plain immediate/addend mismatch (e.g. struct offset, array stride).
        return "STRUCT_LAYOUT"

    # No relocation on one/both sides -> immediate or register operand diff.
    if _differs_in_register(l_instr, r_instr):
        return "REGISTER_ALLOC"
    return "STRUCT_LAYOUT"


def _differs_in_register(l_instr, r_instr):
    l_parts = l_instr.get("parts", [])
    r_parts = r_instr.get("parts", [])
    if len(l_parts) != len(r_parts):
        return False
    for lp, rp in zip(l_parts, r_parts):
        la, ra = lp.get("arg"), rp.get("arg")
        if la != ra and la and ra:
            if "opaque" in la and "opaque" in ra:
                lo, ro = la["opaque"], ra["opaque"]
                if re.match(r"^[rf]\d+$", lo) and re.match(r"^[rf]\d+$", ro):
                    continue  # register difference, keep checking rest
                return False
            return False
    return True


def classify_function(data, name):
    left = find_symbol(data, "left", name)
    right = find_symbol(data, "right", name)
    if left is None:
        return None, {}
    pct = left.get("match_percent")
    if pct is not None and pct >= 100.0:
        return "MATCHED", {"match_percent": pct}

    l_instrs = left.get("instructions", [])
    r_instrs = right.get("instructions", []) if right else []
    l_symbols = data.get("left", {}).get("symbols", [])
    r_symbols = data.get("right", {}).get("symbols", [])
    cats = set()
    details = []
    for i, l_ins in enumerate(l_instrs):
        kind = l_ins.get("diff_kind")
        if not kind or kind == "DIFF_NONE":
            continue
        r_ins = r_instrs[i] if i < len(r_instrs) else None
        cat = classify_instruction_pair(l_ins, r_ins, l_symbols, r_symbols)
        cats.add(cat)
        l_formatted = l_ins.get("instruction", {}).get("formatted", "(gap)") if l_ins.get("instruction") else "(gap)"
        r_formatted = r_ins.get("instruction", {}).get("formatted", "(gap)") if r_ins and r_ins.get("instruction") else "(gap)"
        details.append((cat, l_formatted, r_formatted))

    if not cats:
        overall = "UNSCORABLE"
    elif cats == {"SYMBOL_NAME"}:
        overall = "SYMBOL_NAME"
    elif len(cats) == 1:
        overall = next(iter(cats))
    else:
        overall = "MIXED:" + "+".join(sorted(cats))
    return overall, {"match_percent": pct, "details": details, "categories": cats}


def resolve_symbol_rename(module: str, our_name: str, target_name: str):
    """Find the config/*/symbols.txt line for our_name (or its implied
    address if it's an auto label) and return (path, line_index, old_line)."""
    path = MODULE_SYMBOLS[module]
    lines = path.read_text().splitlines()

    m = AUTO_LABEL_RE.match(our_name)
    if m:
        addr = m.group(1).upper()
        pattern = re.compile(rf"^{re.escape(our_name)}\s*=")
    else:
        addr = None
        pattern = re.compile(rf"^{re.escape(our_name)}\s*=")

    for i, line in enumerate(lines):
        if pattern.match(line):
            return path, i, line

    return None, None, None


def check_collision(path: Path, target_name: str, our_line_idx: int):
    lines = path.read_text().splitlines()
    pattern = re.compile(rf"^{re.escape(target_name)}\s*=")
    for i, line in enumerate(lines):
        if i != our_line_idx and pattern.match(line):
            return line
    return None


def apply_rename(path: Path, line_idx: int, old_line: str, new_name: str):
    lines = path.read_text().splitlines(keepends=False)
    old_name_part, rest = old_line.split("=", 1)
    new_line = f"{new_name} ={rest}"
    lines[line_idx] = new_line
    path.write_text("\n".join(lines) + "\n")


def revert_rename(path: Path, line_idx: int, old_line: str):
    lines = path.read_text().splitlines(keepends=False)
    lines[line_idx] = old_line
    path.write_text("\n".join(lines) + "\n")


def module_for_unit(unit: str) -> str:
    return unit.split("/", 1)[0]


def get_symbol_name_fixes(fn_name: str, data):
    """Collect every resolvable rename implied by SYMBOL_NAME-classified
    mismatches in this function -- there can be more than one distinct rename
    needed, especially in MIXED-category functions.

    Returns (target_name, our_name) pairs: `target_name` is what the symbol is
    currently called in config/*/symbols.txt (the target/left side), and
    `our_name` is what our source calls it (the right side). The fix renames
    the symbols.txt entry from the former to the latter."""
    left = find_symbol(data, "left", fn_name)
    right = find_symbol(data, "right", fn_name)
    l_instrs = left.get("instructions", [])
    r_instrs = right.get("instructions", [])
    l_symbols = data.get("left", {}).get("symbols", [])
    r_symbols = data.get("right", {}).get("symbols", [])
    renames = set()
    for i, l_ins in enumerate(l_instrs):
        kind = l_ins.get("diff_kind")
        if not kind or kind == "DIFF_NONE":
            continue
        r_ins = r_instrs[i] if i < len(r_instrs) else None
        if r_ins is None:
            continue
        l_instr = l_ins.get("instruction")
        r_instr = r_ins.get("instruction")
        if not l_instr or not r_instr:
            continue
        l_reloc = l_instr.get("relocation")
        r_reloc = r_instr.get("relocation")
        if not l_reloc or not r_reloc:
            continue
        if l_reloc.get("type_name") == "R_PPC_NONE" or r_reloc.get("type_name") == "R_PPC_NONE":
            continue
        # left = target (symbols.txt name), right = our build (source name)
        target_name = symbol_name_at(l_symbols, l_reloc.get("target_symbol"))
        our_name = symbol_name_at(r_symbols, r_reloc.get("target_symbol"))
        if target_name and our_name and target_name != our_name:
            if not (ANON_RE.match(our_name) or LOCAL_POOL_RE.match(our_name)):
                renames.add((target_name, our_name))
    return sorted(renames)


def iter_unmatched_units(report_path: Path):
    report = json.loads(report_path.read_text())
    for u in report["units"]:
        if u.get("metadata", {}).get("auto_generated"):
            continue
        if u["measures"].get("matched_functions_percent", 100) < 100:
            yield u["name"]


def unmatched_units_with_measures(report_path: Path):
    report = json.loads(report_path.read_text())
    for u in report["units"]:
        if u.get("metadata", {}).get("auto_generated"):
            continue
        if u["measures"].get("matched_functions_percent", 100) < 100:
            text_size = 0
            text_match_pct = 0.0
            for sec in u.get("sections", []):
                if sec.get("name") == ".text":
                    text_size = int(sec.get("size", 0))
                    text_match_pct = sec.get("match_percent") or 0.0
            yield u["name"], u["measures"], text_size, text_match_pct


def unit_to_source_path(unit: str) -> Path:
    src_relpath = unit.split("/", 1)[1]
    return REPO / "src" / (src_relpath + ".c")


def generate_report(out_path: Path):
    r = subprocess.run(
        [str(resolve_objdiff_cli()), "report", "generate", "-p", str(REPO), "-o", str(out_path), "-f", "json"],
        capture_output=True, text=True,
    )
    if r.returncode != 0:
        raise RuntimeError(f"report generate failed: {r.stderr}")


def find_function_unit(function: str, candidate_units):
    for unit in candidate_units:
        try:
            data = objdiff_unit(unit)
        except RuntimeError:
            continue
        for s in data["left"]["symbols"]:
            if s.get("kind") == "SYMBOL_FUNCTION" and s["name"] == function:
                return unit, data
    return None, None


def cmd_scan(args):
    tmp_report = Path.cwd() / "_match_classify_report.json"
    generate_report(tmp_report)
    units = [args.unit] if args.unit else list(iter_unmatched_units(tmp_report))
    tmp_report.unlink(missing_ok=True)

    if args.function:
        unit, data = find_function_unit(args.function, units)
        if unit is None:
            print(f"'{args.function}' not found in any unmatched unit (already matched, or doesn't exist)")
            return
        cat, details = classify_function(data, args.function)
        pct = details.get("match_percent")
        pct_str = f"{pct:.2f}%" if pct is not None else "n/a"
        print(f"{args.function}  [{unit}]  {pct_str}  -> {cat}")
        for c, l_formatted, r_formatted in details.get("details", []):
            print(f"  [{c:15s}] target: {l_formatted:40s} ours: {r_formatted}")
        return

    tally = {}
    fn_by_cat = {}
    for unit in units:
        try:
            data = objdiff_unit(unit)
        except RuntimeError as e:
            print(f"skip {unit}: {e}")
            continue
        for s in data["left"]["symbols"]:
            if s.get("kind") != "SYMBOL_FUNCTION":
                continue
            fn = s["name"]
            cat, details = classify_function(data, fn)
            if cat is None or cat == "MATCHED":
                continue
            tally[cat] = tally.get(cat, 0) + 1
            fn_by_cat.setdefault(cat, []).append((unit, fn, details.get("match_percent")))

    print("\n=== Classification summary ===")
    for cat, count in sorted(tally.items(), key=lambda kv: -kv[1]):
        print(f"{cat:20s} {count:5d}")
    if args.verbose:
        for cat, fns in fn_by_cat.items():
            print(f"\n--- {cat} ---")
            for unit, fn, pct in sorted(fns, key=lambda x: -(x[2] or 0))[:args.limit]:
                pct_str = f"{pct:6.2f}%" if pct is not None else "  n/a "
                print(f"  {pct_str}  {fn}  [{unit}]")


def cmd_units(args):
    """Rank unmatched files (units) from easiest to hardest, for planning
    which file to tackle next. 'Hard' functions are anything left over after
    Stage 1 -- i.e. everything that needs a human/Claude to fix directly."""
    tmp_report = Path.cwd() / "_match_classify_report.json"
    generate_report(tmp_report)
    unit_rows = list(unmatched_units_with_measures(tmp_report))
    tmp_report.unlink(missing_ok=True)

    results = []
    for unit, measures, text_size, text_match_pct in unit_rows:
        try:
            data = objdiff_unit(unit)
        except RuntimeError:
            continue
        total_fns = 0
        hard_fns = 0
        cat_tally = {}
        for s in data["left"]["symbols"]:
            if s.get("kind") != "SYMBOL_FUNCTION":
                continue
            total_fns += 1
            cat, _ = classify_function(data, s["name"])
            if cat in (None, "MATCHED"):
                continue
            if cat != "SYMBOL_NAME":
                hard_fns += 1
            cat_tally[cat] = cat_tally.get(cat, 0) + 1

        remaining_bytes = int(round(text_size * (1 - text_match_pct / 100)))
        src = unit_to_source_path(unit)
        results.append({
            "unit": unit,
            "file": str(src.relative_to(REPO)) if src.exists() else f"(missing: {src.name})",
            "matched_functions_percent": measures.get("matched_functions_percent"),
            "total_functions": total_fns,
            "hard_functions": hard_fns,
            "remaining_bytes": remaining_bytes,
            "categories": cat_tally,
        })

    # Easiest first: fewest functions that actually need manual work, then
    # smallest remaining unmatched code as a tiebreak.
    results.sort(key=lambda r: (r["hard_functions"], r["remaining_bytes"]))

    print(f"{'match%':>7s} {'hard':>5s} {'total':>6s} {'bytes':>7s}  file  [unit]")
    for r in results[:args.limit]:
        pct = r["matched_functions_percent"]
        pct_str = f"{pct:6.2f}%" if pct is not None else "   n/a"
        cats = ", ".join(f"{k}:{v}" for k, v in sorted(r["categories"].items(), key=lambda kv: -kv[1]))
        print(f"{pct_str} {r['hard_functions']:5d} {r['total_functions']:6d} {r['remaining_bytes']:7d}  {r['file']}  [{r['unit']}]")
        if args.verbose and cats:
            print(f"         {cats}")


def cmd_fix(args):
    tmp_report = Path.cwd() / "_match_classify_report.json"
    generate_report(tmp_report)
    units = [args.unit] if args.unit else list(iter_unmatched_units(tmp_report))
    tmp_report.unlink(missing_ok=True)

    fixed, skipped, failed = [], [], []
    for unit in units:
        module = module_for_unit(unit)

        # Re-fetch after every applied change: a rename can retroactively fix
        # (or otherwise change the score of) other functions sharing the
        # same symbol, so cached diff data can go stale mid-unit.
        seen_this_pass = set()
        while True:
            try:
                data = objdiff_unit(unit)
            except RuntimeError:
                break

            target_fn = None
            for s in data["left"]["symbols"]:
                if s.get("kind") != "SYMBOL_FUNCTION":
                    continue
                fn = s["name"]
                if args.function and fn != args.function:
                    continue
                if fn in seen_this_pass:
                    continue
                cat, details = classify_function(data, fn)
                if cat is None or "SYMBOL_NAME" not in details.get("categories", set()):
                    continue
                target_fn = (fn, cat, details)
                break

            if target_fn is None:
                break
            fn, cat, details = target_fn
            seen_this_pass.add(fn)

            renames = get_symbol_name_fixes(fn, data)
            if not renames:
                skipped.append((fn, "could not resolve any rename"))
                continue

            before_pct = details.get("match_percent")
            applied = []
            resolve_failed = False
            # rename the symbols.txt entry from its current (target) name to
            # the name our source uses
            for cur_name, new_name in renames:
                path, line_idx, old_line = resolve_symbol_rename(module, cur_name, new_name)
                if path is None:
                    skipped.append((fn, f"couldn't find '{cur_name}' in {module} symbols.txt"))
                    resolve_failed = True
                    continue
                collision = check_collision(path, new_name, line_idx)
                if collision:
                    skipped.append((fn, f"'{new_name}' already exists elsewhere: {collision.strip()}"))
                    resolve_failed = True
                    continue
                apply_rename(path, line_idx, old_line, new_name)
                applied.append((path, line_idx, old_line, new_name))

            if not applied:
                continue

            ok, log = run_ninja()
            if not ok:
                for path, line_idx, old_line, _ in applied:
                    revert_rename(path, line_idx, old_line)
                run_ninja()
                all_lines = [l for l in log.splitlines() if l.strip()]
                err_lines = [l for l in all_lines if re.search(r"error|undefined|unresolved|not found", l, re.I)]
                if not err_lines:
                    err_lines = all_lines[-5:]
                failed.append((fn, "build failed after rename: " + " | ".join(err_lines[:5])))
                continue

            data2 = objdiff_unit(unit)
            left2 = find_symbol(data2, "left", fn)
            after_pct = left2.get("match_percent") if left2 else None

            if after_pct is None or (before_pct is not None and after_pct < before_pct):
                for path, line_idx, old_line, _ in applied:
                    revert_rename(path, line_idx, old_line)
                run_ninja()
                failed.append((fn, f"score regressed ({before_pct} -> {after_pct}), reverted"))
                continue

            renamed_str = ", ".join(f"{old_line.split('=')[0].strip()}->{new_name}" for _, _, old_line, new_name in applied)
            before_str = f"{before_pct:.2f}%" if before_pct is not None else "n/a"
            after_str = f"{after_pct:.2f}%" if after_pct is not None else "n/a"
            fixed.append((fn, before_pct, after_pct, applied))
            print(f"FIXED {fn}: {before_str} -> {after_str}  ({renamed_str})")

    print(f"\n=== Done: {len(fixed)} fixed, {len(skipped)} skipped, {len(failed)} failed ===")
    for fn, before, after, applied in fixed:
        before_str = f"{before:.2f}%" if before is not None else "n/a"
        after_str = f"{after:.2f}%" if after is not None else "n/a"
        print(f"  FIXED   {fn}: {before_str} -> {after_str}")
    for fn, reason in skipped:
        print(f"  SKIP    {fn}: {reason}")
    for fn, reason in failed:
        print(f"  FAILED  {fn}: {reason}")


def main():
    ap = argparse.ArgumentParser()
    sub = ap.add_subparsers(dest="cmd", required=True)

    p_scan = sub.add_parser("scan")
    p_scan.add_argument("--unit", default=None)
    p_scan.add_argument("--function", default=None)
    p_scan.add_argument("--verbose", action="store_true")
    p_scan.add_argument("--limit", type=int, default=15)
    p_scan.set_defaults(func=cmd_scan)

    p_fix = sub.add_parser("fix")
    p_fix.add_argument("--unit", default=None)
    p_fix.add_argument("--function", default=None)
    p_fix.set_defaults(func=cmd_fix)

    p_units = sub.add_parser("units")
    p_units.add_argument("--verbose", action="store_true")
    p_units.add_argument("--limit", type=int, default=1000)
    p_units.set_defaults(func=cmd_units)

    args = ap.parse_args()
    args.func(args)


if __name__ == "__main__":
    main()
