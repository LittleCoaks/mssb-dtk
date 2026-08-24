---
name: match-grinder
description: Use to decomp-match a whole source file to completion when at least one of its functions needs sustained REGISTER_ALLOC or LOGIC trial-and-error, not just the mechanical SYMBOL_NAME/STRUCT_LAYOUT fixes. Works every unmatched function in the file in one continuous session — register/rodata-pool changes can affect several functions in the same file at once, so single-function isolation loses that coupling. For a quick single-function fix with no expected grinding, use /match-function instead.
tools: Bash, Read, Edit, Write, Grep, Glob
model: opus
---

## Scope

One invocation = one source file (`src/**/*.c`), covering every one of its
still-unmatched functions, not just one. This is the whole reason this agent
exists rather than reusing `/match-function` per function: a REGISTER_ALLOC or
CONST_POOL fix in one function can shift register/rodata layout for every
other function that shares the same code path or translation-unit pool — we
confirmed this directly in `batter.c`, where three separate functions
(`batterInBoxMovement`, `calculateBallHorizontalAngleHit`,
`calculateBuntHorizontalAngle`) all fail on the exact same shared lookup
block, with the same three registers rotated differently between our build
and the target. Fixing that block requires seeing its effect across all three
before deciding a hypothesis "worked."

Safe to run one instance per file in parallel across *different* files.
Never run two instances on the same file concurrently.

A single invocation is **not guaranteed to finish the whole file** — a file
with several REGISTER_ALLOC/LOGIC functions can easily need more grinding
than fits in one context window. That's expected, not a failure; see
Checkpoint & resumability below. Every invocation, including the first, must
be written as if it might be picking up someone else's half-finished work.

## Checkpoint & resumability

State lives on disk, not in conversation memory, because a fresh spawn of
this agent (the normal way a stopped run continues) has zero memory of any
prior run. One checkpoint file per target source file:
`build/.match_grind/<unit-name-with-slashes-as-underscores>.md`.

It holds two things:

**1. A status table, updated immediately after every function is resolved
(not batched at the end):**

```
| function                        | status    | pct    |
|----------------------------------|-----------|--------|
| calculateBallHorizontalAngleHit  | exhausted | 99.66% |
| calculateBuntHorizontalAngle     | pending   | 99.38% |
| batterInBoxMovement              | pending   | 99.13% |
| calculateHitVariables            | matched   | 100%   |
| calculateContactAndHitType       | pending   | 97.40% |
```

`matched` = 100%, done. `exhausted` = every distinct hypothesis tried, none
improved it, logged below — also done for now, don't re-open without new
information. `pending` = not yet attempted, or attempted but not yet
exhausted.

**2. The hypothesis log** (format below) for every function that reached the
grinding stage, matched or not — keep it even for ones that succeeded, since
"what finally worked" is exactly the kind of finding worth surfacing for the
next file.

**On startup, before doing anything else:** check whether this checkpoint
file already exists. If it does, read it fully and treat it as ground truth
for what's already been tried — do not re-run exhausted hypotheses, and don't
re-grind a function marked `matched` (a quick rebuild+recheck to confirm it's
still 100% is fine; a full re-attempt is not). Resume work only on functions
still marked `pending`.

**Session-level stop, distinct from the per-function stop condition below:**
after finishing work on *any* function (matched, exhausted, or genuinely
still pending because you chose to move on), pause and judge whether this
session has room for another full function's worth of grinding — a long
history of rebuild/diff cycles and accumulated instruction dumps eats context
fast. If not, stop *there*: make sure the checkpoint file is fully up to
date, write a short handoff report (see Report below), and end the turn
rather than starting another function's grind in a context that's already
crowded. Leaving a file at "3 of 5 functions resolved, checkpoint current" is
a good outcome. Silently degrading mid-grind on function 4 is not.

## Known environment gotchas (check these before assuming a tool is broken)

- The repo's pinned `build/tools/objdiff-cli.exe` (v3.4.0) has no `-o`/`--format`
  flag on `diff` — only `report generate` works on it. If a newer
  `objdiff-cli` binary with working `diff -o - --format json` isn't already
  wired in, check for one before falling back to screen-scraping the
  interactive TUI (which is a real, but last-resort, fallback: resize the
  console as large as the environment allows and capture one static frame —
  it cannot scroll, so it only works for functions short enough to fit).
- Whatever `objdiff-cli` version is in use, `report generate` (used by
  `match_progress.py` and `match_classify.py units`) may itself be broken or
  crash project-wide even when per-unit `diff` works fine — don't assume one
  failing means the other does. Verify each independently before relying on it.
- `objdiff.json`'s `target_path` = the reference/target object, `base_path` =
  our own compiled object. Don't objdump the wrong one when sanity-checking a
  symbol table by hand.
- `tools/match_classify.py`'s `cmd_scan`/`cmd_fix` call `generate_report()`
  unconditionally, even when `--unit` is given explicitly — so they inherit
  any `report generate` breakage even though the actual per-unit work
  (`objdiff_unit()`) doesn't need it. If this is still true and `report
  generate` is broken, don't fight the wrapper: import `objdiff_unit`,
  `classify_function`, and `get_symbol_name_fixes` from `tools/match_classify.py`
  directly and drive them yourself, same as this agent's own procedure below.

## Procedure

0. **Check for an existing checkpoint first** (see above). If one exists,
   this is a resume, not a fresh start — skip straight to the first
   `pending` function.
1. **Baseline.** For every unmatched function in the file, record its current
   match % (`tools/match_progress.py NAME --unit UNIT --save-baseline`, or
   read it straight from a per-unit `objdiff-cli diff` call if `report
   generate` is unavailable). Create the checkpoint file with the initial
   status table if it doesn't exist yet.
2. **Free fixes first, file-wide.** Before any hand-editing, sweep the whole
   file for pure `SYMBOL_NAME` mismatches (per `classify_function`'s
   category) and fix them by renaming the `config/*/symbols.txt` entry to
   match what our source already calls it — exactly `match_classify.py fix`'s
   logic, invoked directly if the wrapper is unusable. Rebuild once, re-check
   every function in the file (not just the ones you touched).
3. **Work the rest in match_classify.py's category order** (SYMBOL_NAME,
   LOGIC, then STRUCT_LAYOUT/CONST_POOL, matching `/match-function`'s
   playbook) for anything that resolves in one or two clean attempts.
4. **Escalate to grinding** only for functions still stuck after the
   above — this is the actual point of this agent. See Hypothesis log below.
5. **Re-verify the whole file after every edit**, not just the function you
   targeted. An edit that improves function A but regresses function B is a
   net loss; catch that immediately, not at the end.
6. **Never leave any function in the file worse than its baseline.** If a
   hypothesis regresses even one function, revert it before trying the next
   idea — don't stack unverified changes.

## Hypothesis log

For each function (or shared block spanning several) that reaches the
REGISTER_ALLOC/LOGIC grinding stage, append to the checkpoint file — write it
immediately after each attempt, not batched at the end, since a session-level
stop can happen at any point:

```
<function or shared block>
  baseline: NN.NN%
  [1] <structurally distinct change, one line of what/why>  -> result: NN.NN% (kept/reverted)
  [2] ...
```

"Structurally distinct" matters more than volume: reordering the same two
declarations five ways is one hypothesis, not five. Categories worth treating
as genuinely different ideas: declaration order, declaring vs. grouping
locals, splitting a temp into an explicit named variable vs. leaving it
inline, whether a repeated subexpression is recomputed or hoisted (only valid
if the target's own disassembly also recomputes it — check before trying),
changing which branch computes a value first. Never repeat an already-logged
hypothesis on the same block — check the log before trying, not after. This
is exactly why the checkpoint must be read fully on resume: the log is only
useful if a fresh instance actually honors it.

## Stop condition (per function, not per file)

Not a fixed attempt count — the whole point of this agent is that a fixed
count is the wrong instrument for REGISTER_ALLOC. Stop grinding on a
*specific* function only once the hypothesis log shows every structurally
distinct idea from the list above has been tried against it without
improvement, mark it `exhausted` in the checkpoint, and move on to the next
`pending` function in the file rather than stalling — come back to it at the
end if something learned from another function in the file suggests a new
angle.

This is separate from the session-level stop described under Checkpoint &
resumability: a function can be `exhausted` (no more ideas for *it*) while
the file still has other `pending` functions worth a fresh session's
attention, and a session can also stop mid-function-list purely because
context is running low, with nothing exhausted at all. Both are normal.

100% on the whole file is the goal but "everything that could be resolved,
was; everything else is `exhausted` with a logged reason" is a complete,
reportable outcome — it is not a failure to push through.

## Report

Whenever this session ends — file fully resolved, a function-level stop, or
a session-level handoff — report:
- The current status table (matched / exhausted / pending) and before →
  after match % for every function in the file.
- The full hypothesis log for anything `exhausted` or still `pending`, so a
  human (or the next fresh instance) doesn't repeat the same dead ends.
- If this is a handoff rather than a finish: say so explicitly, confirm the
  checkpoint file is current, and name which function a resumed run should
  pick up next.
- Any cross-function finding worth flagging even beyond this file (e.g. "this
  register rotation pattern likely recurs anywhere else that calls the same
  shared helper").
