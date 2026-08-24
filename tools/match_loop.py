#!/usr/bin/env python3
"""
Local-model function matcher for the MSSB decomp.

Drives a loop of: ask a local llama.cpp server (Qwen) for a candidate
implementation of one function -> rebuild with ninja -> score it with
objdiff-cli -> feed the exact instruction-level diff back for the next
attempt. Meant as a free/unlimited first pass before escalating a
still-unmatched function to Claude.

Usage:
    python tools/match_loop.py <function_name> [--attempts 8] [--unit main/Musyx/hw_dolphin]
                                [--server http://localhost:8080] [--keep-best]

If --unit is omitted, the source file (and unit name) is resolved by
searching src/**/*.c for the function definition.
"""
import argparse
import json
import re
import subprocess
import sys
import urllib.request
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from match_classify import REPO, resolve_objdiff_cli  # noqa: E402

SRC_DIR = REPO / "src"


class MatchError(Exception):
    pass


def find_function(name: str):
    """Search src/**/*.c for `name(`s definition, return (path, start, end, unit)."""
    pattern = re.compile(
        r"(?:^|\n)([A-Za-z_][\w \*\n]*?\b" + re.escape(name) + r"\s*\([^;{]*?\))\s*\{",
        re.MULTILINE,
    )
    candidates = []
    for path in SRC_DIR.rglob("*.c"):
        text = path.read_text(encoding="utf-8")
        for m in pattern.finditer(text):
            candidates.append((path, text, m))

    if not candidates:
        raise MatchError(f"Couldn't find a definition of `{name}` under src/**/*.c")
    if len(candidates) > 1:
        locs = "\n".join(f"  - {p}" for p, _, _ in candidates)
        raise MatchError(f"Multiple candidates for `{name}`, refusing to guess:\n{locs}")

    path, text, m = candidates[0]
    brace_start = m.end() - 1  # position of the opening '{'
    depth = 0
    i = brace_start
    in_str = in_char = False
    while i < len(text):
        c = text[i]
        if in_str:
            if c == "\\":
                i += 1
            elif c == '"':
                in_str = False
        elif in_char:
            if c == "\\":
                i += 1
            elif c == "'":
                in_char = False
        elif c == '"':
            in_str = True
        elif c == "'":
            in_char = True
        elif c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
            if depth == 0:
                break
        i += 1
    else:
        raise MatchError(f"Unbalanced braces while scanning `{name}` in {path}")

    func_start = m.start(1)
    func_end = i + 1
    unit = derive_unit_name(path)
    return path, text, func_start, func_end, unit


def derive_unit_name(path: Path) -> str:
    rel = path.relative_to(SRC_DIR).with_suffix("").as_posix()
    for module in ("game", "menus", "challenge"):
        if rel == module or rel.startswith(module + "/"):
            return f"{module}/{rel}"
    return f"main/{rel}"


def run_ninja():
    r = subprocess.run(["ninja"], cwd=REPO, capture_output=True, text=True)
    return r.returncode == 0, (r.stdout + r.stderr)


def get_diff(unit: str, symbol: str):
    r = subprocess.run(
        [
            str(resolve_objdiff_cli()),
            "diff",
            "-p", str(REPO),
            "-u", unit,
            symbol,
            "-o", "-",
            "--format", "json",
        ],
        capture_output=True,
        text=True,
    )
    if r.returncode != 0:
        raise MatchError(f"objdiff-cli failed:\n{r.stderr}")
    data = json.loads(r.stdout)

    def find_symbol(side):
        for s in data.get(side, {}).get("symbols", []):
            if s.get("name") == symbol:
                return s
        return None

    left = find_symbol("left")
    right = find_symbol("right")
    if left is None:
        raise MatchError(f"`{symbol}` not found in unit `{unit}` per objdiff")
    return left, right


def render_side(sym):
    lines = []
    for ins in sym.get("instructions", []):
        kind = ins.get("diff_kind")
        tag = f"[{kind.replace('DIFF_', '')}] " if kind and kind != "DIFF_NONE" else "         "
        instr = ins.get("instruction")
        text = instr["formatted"] if instr else "(gap)"
        lines.append(tag + text)
    return "\n".join(lines)


def build_prompt(name: str, current_src: str, left, right, attempt, history):
    match_pct = left.get("match_percent")
    diff_text = render_side(left)
    target_text = render_side(right) if right else "(unavailable)"
    history_text = ""
    if history:
        history_text = "\nPrevious attempts (avoid repeating these mistakes):\n" + "\n".join(
            f"- attempt {i}: {pct:.1f}% match, notes: {note}"
            for i, pct, note in history
        )

    return f"""You are matching a decompiled C function against original PowerPC (Gekko/GameCube, \
CodeWarrior compiler) assembly for the game Mario Superstar Baseball, using objdiff.

Function: `{name}`
Attempt: {attempt}
Current match: {match_pct:.2f}%
{history_text}

Current C source for this function:
```c
{current_src}
```

Current build's instructions (yours), with diff markers relative to the target:
{diff_text}

Target (original game binary) instructions:
{target_text}

Rewrite ONLY this one function so the compiled output matches the target instruction-for-instruction. \
Keep the exact same function signature (return type, name, parameters). Do not add helper functions, \
comments, or explanation. Common CodeWarrior quirks to consider: register allocation order, loop \
structure (do/while vs for), inlining, struct-return conventions, and order of side-effecting expressions.

Respond with ONLY a single ```c fenced code block containing the complete replacement function."""


def call_model(server: str, prompt: str, timeout: int, temperature: float) -> str:
    body = json.dumps(
        {
            "messages": [{"role": "user", "content": prompt}],
            "temperature": temperature,
        }
    ).encode()
    req = urllib.request.Request(
        server.rstrip("/") + "/v1/chat/completions",
        data=body,
        headers={"Content-Type": "application/json"},
    )
    with urllib.request.urlopen(req, timeout=timeout) as resp:
        data = json.loads(resp.read())
    msg = data["choices"][0]["message"]
    reasoning = msg.get("reasoning_content")
    if reasoning:
        print(f"  (reasoning: {len(reasoning)} chars)")
    return msg["content"]


def extract_code(reply: str) -> str:
    matches = re.findall(r"```(?:c)?\s*\n(.*?)```", reply, re.DOTALL)
    if not matches:
        raise MatchError("Model reply had no ```c fenced block")
    return matches[-1].strip()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("function")
    ap.add_argument("--attempts", type=int, default=8)
    ap.add_argument("--unit", default=None)
    ap.add_argument("--server", default="http://localhost:8080")
    ap.add_argument("--timeout", type=int, default=180, help="Per-call HTTP timeout in seconds (raise for reasoning models)")
    ap.add_argument("--temperature", type=float, default=0.2, help="Sampling temperature")
    ap.add_argument("--keep-best", action="store_true", help="Leave best attempt in place even if not matched")
    args = ap.parse_args()

    path, original_text, func_start, func_end, auto_unit = find_function(args.function)
    unit = args.unit or auto_unit
    print(f"Located `{args.function}` in {path.relative_to(REPO)} (unit `{unit}`)")

    pristine_text = original_text
    working_text, w_start, w_end = original_text, func_start, func_end

    best_pct = -1.0
    best_text = pristine_text
    history = []

    for attempt in range(1, args.attempts + 1):
        print(f"\n=== Attempt {attempt}/{args.attempts} ===")
        current_src = working_text[w_start:w_end]

        left, right = get_diff(unit, args.function)
        pct = left.get("match_percent") or 0.0
        print(f"Current score: {pct:.2f}%")
        if pct >= 100.0:
            print("Already matched before any edit — nothing to do.")
            return

        prompt = build_prompt(args.function, current_src, left, right, attempt, history)
        try:
            reply = call_model(args.server, prompt, args.timeout, args.temperature)
            new_func = extract_code(reply)
        except Exception as e:
            print(f"Model call failed: {e}")
            history.append((attempt, pct, f"model call failed: {e}"))
            continue

        patched_text = working_text[:w_start] + new_func + working_text[w_end:]
        path.write_text(patched_text, encoding="utf-8")

        ok, log = run_ninja()
        if not ok:
            print("Build failed, feeding error back next attempt.")
            history.append((attempt, pct, f"build failed: {log[-500:]}"))
            path.write_text(working_text, encoding="utf-8")
            run_ninja()
            continue

        left2, _ = get_diff(unit, args.function)
        new_pct = left2.get("match_percent") or 0.0
        print(f"New score: {new_pct:.2f}%")

        if new_pct >= 100.0:
            print(f"\nMATCHED `{args.function}` in {attempt} attempt(s).")
            history.append((attempt, new_pct, "matched"))
            return

        # re-locate function span in the patched file for the next attempt,
        # since the body's length (and thus offsets) likely changed
        _, working_text, w_start, w_end, _ = find_function(args.function)

        if new_pct > best_pct:
            best_pct = new_pct
            best_text = working_text

        history.append((attempt, new_pct, "ok" if new_pct > pct else "no improvement"))

    print(f"\nNot matched after {args.attempts} attempts. Best score: {best_pct:.2f}%")
    if args.keep_best:
        path.write_text(best_text, encoding="utf-8")
        run_ninja()
        print(f"Left best attempt ({best_pct:.2f}%) in {path.relative_to(REPO)} for handoff.")
    else:
        path.write_text(pristine_text, encoding="utf-8")
        run_ninja()
        print(f"Restored {path.relative_to(REPO)} to its original state (pass --keep-best to leave the closest attempt in place).")
    print("Escalate to Claude with this function + the diff above for a stronger attempt.")


if __name__ == "__main__":
    try:
        main()
    except MatchError as e:
        print(f"error: {e}", file=sys.stderr)
        sys.exit(1)
