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

## Diagnostic techniques worth trying before declaring a function exhausted

**Per-file `mw_version` sweep, for register-allocation/CSE-tiebreak mismatches
that survive both source-shape grinding and a per-file `extra_cflags` sweep.**
`Object(...)` entries in `configure.py` accept an `mw_version="GC/X.Y"`
override (defaults to `config.linker_version`, currently `GC/1.3.2`) that
picks which bundled MWCC point-release compiles just that one file — the
original SDK build sometimes mixed compiler versions across TUs, and a
different point release can change internal register-allocator tie-breaking
with no corresponding flag. It's cheap to test (edit the one kwarg, rebuild
the single object, diff all functions in the unit, revert) and worth running
before marking a function permanently `exhausted`, but the bar for adopting a
result is strict: a version only counts as a win if it improves/holds every
already-matched function in the unit *and* helps the stuck one(s) — a version
that fixes one function while regressing others just proves allocation is
version-sensitive here, it isn't a keeper. Tried on `src/game/batting/batter.c`
across all 17 other GC versions bundled under `build/compilers/GC/`: no
improvement on the 4 still-unmatched functions, but it did confirm
`GC/1.3.2` is very likely the TU's actual original compiler — `1.3.2r`,
`2.0`, `2.0p1`, `2.5`, `2.6`, and `2.7` all produced a byte-for-byte
identical object across all 25 functions, while everything outside that
narrow 1.3.2r–2.7 band regressed 24-25 of 25 functions (different MWCC
front-end generation entirely). That byte-for-byte plateau across six
adjacent releases is itself useful signal on any file: if a version sweep
lands in a similar identical-output plateau, the compiler version isn't the
lever for whatever's left — look elsewhere (source shape, or accept the
mismatch is a genuine allocator artifact).
