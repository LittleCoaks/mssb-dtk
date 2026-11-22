#!/usr/bin/env python3
"""Measure several candidate rewrites of one piece of source in a single run.

    python tools/match_variants.py game/minigame/piranha_panic pP_InitAI spec.json

  SRC      source path under src/, without the .c extension
  REGEX    which functions' scores to print (the whole unit is always summed)
  SPEC     JSON: {"old": "<exact text in the file>",
                  "variants": {"name": "<replacement text>", ...}}

For each variant it swaps the text in, builds just that object, diffs the
unit and prints the scores; the original bytes are written back at the end
(in a `finally`, so an interrupted run still restores them). `old` must occur
exactly once. Nothing is kept: copy the winning variant in by hand.

Each line shows `unmatched` (functions under 100% in the unit) and `sum` (the
total of every function's percentage) so a variant that helps one function
while regressing another is visible immediately. Compare against the BASE
line, and check that RESTORED equals BASE.

`ninja` is located via the NINJA environment variable, then PATH.
"""
import argparse
import json
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from match_classify import REPO, objdiff_unit


def write_source(path, data, attempts=40, delay=0.25):
    """Write bytes to a source file, retrying while Windows (an editor, an indexer,
    antivirus) briefly holds it open. Raises only after ~10 seconds of trying."""
    import time
    for i in range(attempts):
        try:
            Path(path).write_bytes(data)
            return
        except PermissionError:
            if i == attempts - 1:
                raise
            time.sleep(delay)


def find_ninja():
    ninja = os.environ.get("NINJA") or shutil.which("ninja")
    if not ninja:
        raise SystemExit("ninja not found: put it on PATH or set NINJA to its full path")
    return ninja


def score(ninja, rel, module, pattern):
    r = subprocess.run([ninja, f"build/GYQE01/src/{rel}.o"], cwd=REPO, capture_output=True, text=True)
    if r.returncode:
        errors = [l.strip() for l in (r.stdout + r.stderr).splitlines() if "rror" in l][:6]
        return "BUILD FAILED: " + " | ".join(errors)
    data = objdiff_unit(f"{module}/{rel}")
    unmatched, total, shown = 0, 0.0, []
    for s in data["left"]["symbols"]:
        if s.get("kind") != "SYMBOL_FUNCTION" or s.get("match_percent") is None:
            continue
        pct = s["match_percent"]
        total += pct
        unmatched += pct < 100
        if re.search(pattern, s["name"]):
            shown.append(f"{s['name']}={pct:.2f}")
    return f"unmatched={unmatched} sum={total:.2f}  " + "  ".join(shown)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("src", help="path under src/ without .c, e.g. game/minigame/piranha_panic")
    ap.add_argument("regex", help="functions whose scores to print")
    ap.add_argument("spec", help="JSON file with 'old' and 'variants'")
    args = ap.parse_args()

    rel = args.src.removeprefix("src/").removesuffix(".c")
    module = rel.split("/")[0]  # objdiff unit names repeat the module folder: game/game/...
    path = REPO / "src" / f"{rel}.c"
    spec = json.loads(Path(args.spec).read_text(encoding="utf-8"))

    original = path.read_bytes().decode("utf-8")
    newline = "\r\n" if "\r\n" in original else "\n"
    old = spec["old"].replace("\r\n", "\n").replace("\n", newline)
    if original.count(old) != 1:
        raise SystemExit(f"'old' occurs {original.count(old)} times in {path.name}; it must occur exactly once")

    ninja = find_ninja()
    try:
        print(f"{'BASE':10s}", score(ninja, rel, module, args.regex))
        for name, new in spec["variants"].items():
            new = new.replace("\r\n", "\n").replace("\n", newline)
            write_source(path, original.replace(old, new).encode("utf-8"))
            print(f"{name:10s}", score(ninja, rel, module, args.regex))
    finally:
        write_source(path, original.encode("utf-8"))
        print(f"{'RESTORED':10s}", score(ninja, rel, module, args.regex))


if __name__ == "__main__":
    main()
