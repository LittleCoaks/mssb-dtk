"""Report match progress at three levels: function, unit (file), and whole repo.

Regenerates the objdiff report on every call (~0.1s) and prints the block the
/match-function command ends each run with. Every percentage is objdiff's
fuzzy match percent, so the three lines are directly comparable.

    python tools/match_progress.py NAME [--unit UNIT] --save-baseline   # start of run
    python tools/match_progress.py NAME [--unit UNIT]                   # end of run

The second form prints `before -> after` when a baseline for the same function
is on disk (build/.match_progress_baseline.json, written by --save-baseline).
"""
import argparse
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from match_classify import REPO, generate_report

BASELINE = REPO / "build" / ".match_progress_baseline.json"


def snapshot(function, unit=None):
    tmp = REPO / "build" / "_match_progress_report.json"
    tmp.parent.mkdir(parents=True, exist_ok=True)
    generate_report(tmp)
    report = json.loads(tmp.read_text())
    tmp.unlink(missing_ok=True)

    units = report["units"]
    if unit:
        u = next((x for x in units if x["name"] == unit), None)
        if u is None:
            raise SystemExit("unit not found in report: " + unit)
    else:
        hits = [x for x in units
                if any(f["name"] == function for f in x.get("functions", []))]
        if len(hits) > 1:
            raise SystemExit(
                "%s appears in %d units, pass --unit: %s"
                % (function, len(hits), ", ".join(x["name"] for x in hits[:8]))
            )
        if not hits:
            raise SystemExit(
                "%s not found in any unit; check the spelling or pass --unit" % function
            )
        u = hits[0]

    fn = next((f for f in u.get("functions", []) if f["name"] == function), None)
    if fn is None:
        raise SystemExit("%s is not a function of unit %s" % (function, u["name"]))
    # objdiff omits zero-valued fields, so a missing percent means 0%.
    fn_pct = fn.get("fuzzy_match_percent", 0.0)

    m = report["measures"]
    return {
        "function": function,
        "unit": u["name"],
        "function_percent": fn_pct,
        "unit_percent": u["measures"].get("fuzzy_match_percent", 0.0),
        "repo_percent": m.get("fuzzy_match_percent", 0.0),
        "repo_code_percent": m.get("matched_code_percent", 0.0),
        "matched_functions": m.get("matched_functions", 0),
        "total_functions": m.get("total_functions", 0),
    }


def pct(v):
    return "n/a" if v is None else "%.2f%%" % v


def render(now, before=None):
    def line(label, key, suffix=""):
        cur = pct(now[key])
        if before is not None and before.get(key) is not None:
            body = "%9s -> %9s" % (pct(before[key]), cur)
        else:
            body = "%9s" % cur
        return ("%-38s%s%s" % (label, body, suffix)).rstrip()

    print(line("Function  " + now["function"], "function_percent"))
    print(line("Unit      " + now["unit"], "unit_percent"))
    print(line("Repo      (total)", "repo_percent",
               "   [code %.2f%%, functions %d/%d]"
               % (now["repo_code_percent"], now["matched_functions"],
                  now["total_functions"])))


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("function")
    ap.add_argument("--unit", default=None)
    ap.add_argument("--save-baseline", action="store_true",
                    help="record these numbers as the 'before' side of the run")
    ap.add_argument("--json", action="store_true")
    args = ap.parse_args()

    now = snapshot(args.function, args.unit)

    before = None
    if args.save_baseline:
        BASELINE.parent.mkdir(parents=True, exist_ok=True)
        BASELINE.write_text(json.dumps(now, indent=1))
    elif BASELINE.exists():
        try:
            before = json.loads(BASELINE.read_text())
        except ValueError:
            before = None
        if before is not None and before.get("function") != args.function:
            before = None

    if args.json:
        print(json.dumps(now, indent=1))
    else:
        render(now, before)


if __name__ == "__main__":
    main()
