"""Print decomp match progress: total repo, then broken down per module
(DOL / game REL / menus REL / unused REL).

Regenerates the objdiff report fresh each run (~0.1s) so the numbers are
always current -- no need to open objdiff or remember another command.

    python tools/progress.py            # human-readable
    python tools/progress.py --json     # machine-readable
"""
import argparse
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from match_classify import REPO, generate_report

# unit name's first path segment -> display label. "debug" was previously
# labeled "challenge" -- that was a repo-invented name from decompress.py's
# hardcoded output filename, not an authoritative disc name. Research has
# since identified it as the game's unused developer debug menu; see
# docs/file_map.md.
MODULE_LABELS = {
    "main": "DOL",
    "game": "game.rel",
    "menus": "menus.rel",
    "debug": "debug.rel",
}
MODULE_ORDER = ["main", "game", "menus", "debug"]


def collect(report):
    modules = {}
    for u in report["units"]:
        mod = u["name"].split("/", 1)[0]
        m = modules.setdefault(mod, {
            "matched_code": 0, "total_code": 0,
            "matched_functions": 0, "total_functions": 0,
            "units": 0, "complete_units": 0,
        })
        meas = u["measures"]
        m["matched_code"] += int(meas.get("matched_code", 0))
        m["total_code"] += int(meas.get("total_code", 0))
        m["matched_functions"] += meas.get("matched_functions", 0)
        m["total_functions"] += meas.get("total_functions", 0)
        m["units"] += 1
        if u.get("metadata", {}).get("complete"):
            m["complete_units"] += 1
    return modules


def pct(num, den):
    return (100.0 * num / den) if den else 0.0


def render(report, modules):
    m = report["measures"]
    print("%-28s%9s   [code %6s/%-6s  fns %5d/%-5d  units %4d, %d complete]"
          % ("TOTAL", "%.2f%%" % m.get("fuzzy_match_percent", 0.0),
             m.get("matched_code", "0"), m.get("total_code", "0"),
             m.get("matched_functions", 0), m.get("total_functions", 0),
             m.get("total_units", 0), m.get("complete_units", 0)))
    print()

    order = MODULE_ORDER + sorted(k for k in modules if k not in MODULE_ORDER)
    for mod in order:
        d = modules.get(mod)
        if d is None:
            continue
        label = MODULE_LABELS.get(mod, mod)
        code_pct = pct(d["matched_code"], d["total_code"])
        print("%-28s%9s   [code %6d/%-6d  fns %5d/%-5d  units %4d, %d complete]"
              % (label, "%.2f%%" % code_pct,
                 d["matched_code"], d["total_code"],
                 d["matched_functions"], d["total_functions"],
                 d["units"], d["complete_units"]))


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                  formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--json", action="store_true", help="machine-readable output")
    args = ap.parse_args()

    tmp = REPO / "build" / "_progress_report.json"
    tmp.parent.mkdir(parents=True, exist_ok=True)
    generate_report(tmp)
    report = json.loads(tmp.read_text())
    tmp.unlink(missing_ok=True)

    modules = collect(report)

    if args.json:
        out = {
            "total": report["measures"],
            "modules": {MODULE_LABELS.get(k, k): v for k, v in modules.items()},
        }
        print(json.dumps(out, indent=1))
    else:
        render(report, modules)


if __name__ == "__main__":
    main()
