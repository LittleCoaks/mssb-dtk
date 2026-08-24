---
description: Iteratively raise a function's objdiff match percentage, ideally to 100%.
argument-hint: <function-name> [--unit game/pitching/pitcher]
---

## Goal

Raise the objdiff match percentage of the function named in `$ARGUMENTS` as far as
possible. 100% is the target; a smaller verified improvement is an acceptable
outcome if 100% isn't reachable this run. Never leave the function worse than
it started, and never touch other functions' matched status.

This command does **not** rename any symbols. If the function ends this run
matched but its own name (or one it calls) is still a placeholder
(`fn_80008E00`, `fn_3_1CE90`, `lbl_...`), leave it — that is the separate,
optional `/label-symbols` command, and doing it here would burn effort on a
task that can fail independently of matching.

## Tools available

- `tools/match_progress.py NAME [--unit UNIT] [--save-baseline]` — the
  function/unit/repo percentage block. Call once with `--save-baseline` before
  touching anything, and once at the end (with no flag) to report the delta.
- `tools/match_classify.py scan --function NAME [--unit UNIT]` — classifies
  every mismatched instruction into `SYMBOL_NAME` / `CONST_POOL` /
  `STRUCT_LAYOUT` / `REGISTER_ALLOC` / `LOGIC` and prints target-vs-ours per
  instruction. Always run this before editing anything — it tells you which
  playbook below applies, and it's free (no LLM, no guessing).
- `tools/match_classify.py fix --function NAME` — auto-fixes pure
  `SYMBOL_NAME` mismatches by renaming the `config/*/symbols.txt` entry to
  match what the source already calls it, then verifies the score actually
  improved (reverts if not). Always try this before writing any C.
- `objdiff-cli diff -p . -u UNIT NAME -o - --format json` — the raw diff (find
  it via `python -c "from tools.match_classify import resolve_objdiff_cli;
  print(resolve_objdiff_cli())"`, or just call `match_classify.py scan` again
  after each edit, which wraps the same call). Remember the side convention:
  **`left` = target (original game), `right` = our build.** A fix always means
  changing our source/config until `right` matches `left`, never the reverse.
- `ninja` — rebuild. Run it after every source edit before re-diffing.
- `tools/match_loop.py NAME [--attempts N] [--server URL]` — optional,
  free-first-pass driver for a local model (llama.cpp-compatible server) on
  pure `LOGIC` mismatches. Only relevant if the user has a local server
  running; skip it entirely otherwise. It restores the file if it doesn't
  reach 100% (pass `--keep-best` to leave its closest attempt for you to take
  over), so it's safe to try before you start editing by hand.

If `objdiff-cli` can't be found, run `ninja` once first — the project
downloads it to `build/tools/`. `MSSB_OBJDIFF_CLI` can point at an existing
binary instead.

## Procedure

1. **Locate.** Find the function's definition under `src/**/*.c`. If it has no
   C definition yet (pure `auto_*`/asm split, 0% because nothing was ever
   attempted), that's still in scope — "0% → something" counts as an
   improvement — but the first step is different: write an initial
   implementation before iterating. Use the target-side disassembly from the
   objdiff diff and, if available, `tools/ghidra_query.py decomp NAME` (the
   Ghidra project's decompiler output) as a starting shape, then treat it like
   any other unmatched function from here on. Confirm which unit/module it
   belongs to (`--unit` in the tools above) if it's ambiguous.

2. **Baseline.** `python tools/match_progress.py NAME [--unit UNIT]
   --save-baseline`.

3. **Classify.** `python tools/match_classify.py scan --function NAME [--unit
   UNIT]`. Read the category and the per-instruction target-vs-ours listing —
   this is the actual evidence for every step that follows, not the function
   in isolation.

4. **Free fixes first.** If any mismatches are `SYMBOL_NAME`, run
   `tools/match_classify.py fix --function NAME`. Re-run `scan` afterward —
   this alone sometimes reaches 100% with no code change at all.

5. **If still short, work the remaining category(ies):**
   - **CONST_POOL** — the target's relocation is anonymous/pool-local. This is
     usually a whole-file rodata *ordering* issue (constant literals emitted
     in a different order than the target), which affects multiple functions
     in the unit at once. Look at what other constants this function's TU
     emits and whether reordering them (not this function's logic) closes the
     gap. If fixing it here would require touching unrelated functions'
     constants, that's expected — do it, but verify with `match_progress.py
     --unit UNIT` that you haven't regressed anything else in the file. If the
     ordering issue is genuinely cross-function and you can't localize it
     confidently, stop, report it as the blocker, and don't guess.
   - **STRUCT_LAYOUT** — a plain immediate (not a relocation) is off by a
     constant, almost always a wrong struct member offset or array stride.
     Check the header for that struct; compare the mismatched immediate
     against the field's actual offset. `tools/ghidra_struct_diff.py` may
     already have relevant struct-layout evidence — check it before guessing
     at a new size/offset by hand.
   - **REGISTER_ALLOC** — same instructions and shape, only register numbers
     differ. This comes from CodeWarrior's allocator, which is sensitive to
     C-level variable order, count, and scope — not logic. Try reordering
     local declarations, splitting or merging temporaries, or changing which
     expressions get an explicit local vs. staying inline. This is the
     category local models have failed at unassisted; expect to need several
     targeted rewrites of the same few lines rather than one clean fix.
   - **LOGIC** — real instruction differences. Rewrite the function so its
     compiled shape matches the target instruction-for-instruction: loop form
     (`do/while` vs `for`), condition sense/negation, inlining, order of
     side-effecting expressions, struct-return convention. This is the
     category `tools/match_loop.py` is meant for as a free first pass; you can
     use its output as a starting point instead of writing this from scratch,
     but verify it yourself with the same classify/diff loop rather than
     trusting its "matched" claim blindly.
   - Mixed categories: fix in the order above — `SYMBOL_NAME` and `LOGIC`
     first (they're least likely to have side effects on other functions),
     `CONST_POOL` last (most likely to touch shared state).

6. **Edit → rebuild → re-diff → repeat.** After every change: `ninja`, then
   `match_classify.py scan --function NAME` again. Keep a short mental (or
   written, if it helps) log of what you tried and its result so you don't
   repeat a failed approach. Only keep an edit if the score improved or
   stayed equal while fixing a real issue (e.g. closing part of a mixed
   category even if the overall percent hasn't moved yet); revert anything
   that regresses.

7. **Stop conditions.** Stop and report when any of these hit:
   - 100% match — done.
   - No improvement across several consecutive attempts on the same
     mismatch — the current bucket needs more investigation or a human, not
     more guessing. Say what's blocking it (category + your best hypothesis).
   - The blocker is structural and out of this function's scope alone (e.g. a
     `CONST_POOL` issue that needs a project-wide constant-pool tool, per the
     `match_classify.py` docstring's "Stage 2" note) — report it as such
     rather than forcing a local hack.
   Never leave the file in a state worse than the baseline: if you can't beat
   the starting score, leave your best verified attempt in place (not a
   regression), not the original.

8. **Report.** End with `python tools/match_progress.py NAME [--unit UNIT]`
   (no `--save-baseline`) to print the before → after block at function, unit,
   and repo level. Summarize: final match %, what category(ies) remain if not
   100%, and whether the function (or anything it now references) still has a
   placeholder name worth a follow-up `/label-symbols NAME` — but don't run
   that yourself.

## Constraints

- Touch only what's needed for this function: its own body, and — only when a
  `STRUCT_LAYOUT`/`CONST_POOL` fix genuinely requires it — the specific
  header/const it's wrong about. Don't refactor unrelated code you notice
  along the way.
- Don't change the function's signature (return type, name, parameters)
  unless the mismatch is specifically that the signature itself is wrong.
- Don't rename any symbol as part of this command.
- Don't disable, skip, or work around the build/objdiff to force a "match" —
  the score has to come from real matching.
