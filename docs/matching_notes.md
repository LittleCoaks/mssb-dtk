# Matching notes

Durable, cross-file findings promoted out of individual `match-grinder-opus`/
`match-grinder-sonnet` grind sessions. The per-file checkpoint at
`build/.match_grind/<unit>.md` is gitignored scratch — it holds a session's
raw hypothesis log and is deleted once that file hits 100%. Anything in it
that's likely to recur in *other* files gets promoted here instead, so it
survives the prune and is visible to the next person (or agent) who runs into
the same shape of problem.

Add a new entry whenever a grind session finds something reusable. Keep
entries short: what the pattern looks like, what it means, and where it was
first seen. This is not a log of every attempt — that's what the per-file
checkpoint is for while it's still alive.

## MWCC codegen signatures

**`clrlwi rX, rY, 24` (or `extsb`) immediately after `stb rY, ...` means the
source re-reads the field it just stored — it is not a redundant cast to
delete.** MWCC emits this when a `u8` struct field is written and then
immediately compared/used again from a local that shadows it; the "obviously
redundant" widening disappears once the local is removed and the comparisons
read the struct field directly instead. Same pattern with `frsp` right after
`stfs` for `float` fields. First seen: `src/game/batting/batter.c`,
`calculateHitVariables` (98.36% → 100%) — a `u32 starPower` local was cached
instead of re-reading `g_Batter.captainStarSwingActivated` after storing it.

**Contradictory declaration-order requirements between an auto-inlined
static and its standalone `*_unused` copy mean the target has two distinct
(near-identical) source copies, not one function serving both call sites.**
If sweeping declaration order to fix the inlined copy breaks the standalone
copy no matter what order is tried (and vice versa), stop trying to unify
them — add a second `static inline` copy with the declaration order the
inlined call site needs, and leave the original `_unused` function
untouched. `static inline` doesn't add a symbol, so this is free. First
seen: `calculateBuntVerticalAngle` / `calculateBuntVerticalAngle_unused` in
`batter.c`.

## Shared-block register rotation

A "left-rotated by one" register assignment relative to target, isolated to
a single CSE, has shown up in more than one function sharing the same
inputs-gathering block: our compile ranks a `&g_Minigame...characterIndex`
common-subexpression first, the target ranks it last, and every other live
value in the block is otherwise correctly allocated. A `static inline`
wrapper around the shared chain (e.g. `pickBatterInputs(InputStruct*)`) puts
the CSE in the right register for all affected functions at once — but only
helps once there's a way to demote *that specific* CSE relative to the
others; applied blind, it was net-negative in testing. Seen in
`batterInBoxMovement`, `calculateBuntHorizontalAngle`,
`calculateBallHorizontalAngleHit` (all still unmatched as of this writing);
the same inputs-block shape also appears in `calculateVerticalAngle` and
`batterHumanControlled` (both already 100%, worth re-checking if this
pattern's fix is ever found — they may reveal what makes the CSE rank
differently there).

## Constant-pool / weak-symbol addressing

**MWCC only uses section-base-relative constant-pool addressing (hoisting
`.rodata`'s base into a callee-saved register, one load instead of one
`lis`/`addi` per constant) if the *first* symbol in the TU's `.rodata` is
stable and non-weak.** A `extern inline` function whose out-of-line copy is
never actually called (e.g. `dolsqrtf2()`) still gets its local statics
(`_half`, `_three`, ...) emitted as weak duplicate symbols at the head of
`.rodata` in any TU that includes the declaring header but never calls the
function — shifting every subsequent constant-pool offset relative to the
linked target (which deduplicated the weak symbols away). Fix: give the
function `static` linkage in TUs that don't call it (guard the linkage macro
with `#ifndef` so individual TUs can opt in), while keeping `extern` in TUs
that do call it. This only helps if some other symbol earlier in the same
TU's `.rodata` is guaranteed non-weak/stable — check that first, or the
"fix" is a no-op (confirmed empirically: applying the same `static` opt-in to
`roster_init.c`/`collision_primitives.c` changed nothing project-wide,
because both already had a stable non-weak symbol ahead of the weak
duplicates for unrelated reasons). First seen and fixed in
`src/game/batting/batter.c` via `include/game/UnknownHomes_Game.h`'s
`SQRT2_LINKAGE` macro and `include/header_rep_data.h`'s `repHeaderData`
accessor.
