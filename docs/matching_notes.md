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
value in the block is otherwise correctly allocated. Seen in
`batterInBoxMovement`, `calculateBuntHorizontalAngle`,
`calculateBallHorizontalAngleHit` (all still unmatched as of this writing);
the same inputs-block shape also appears in `calculateVerticalAngle` and
`batterHumanControlled` (both already 100%).

**A `static inline pickBatterInputs(InputStruct*)` wrapper around the shared
chain is confirmed NOT the target's actual source shape — ruled out, not just
untested.** Applying it to only the 3 broken functions looked promising
(regression-free, and +0.05% on `calculateBallHorizontalAngleHit` alone in
isolation), but applying the *same* wrapper to the 2 already-100%-matched
sibling functions sharing the identical block broke both of them
(`batterHumanControlled` 100→89.83%, `calculateVerticalAngle` 100→99.86%). If
the original source had this helper, the two functions we already reproduce
exactly would be indifferent to it — they aren't, so the chain is genuinely
open-coded in all five, and the wrapper is a false lead even though it
produces a real number improvement on one still-broken function. Root
mechanism, per the closest read so far: the target emits three *different*
register orderings of the same `{inputs, gMini, charIdx}` set from one
identical source block depending on register pressure at each call site — we
reproduce the target's ordering exactly on the two large/high-pressure
functions and get a different (but internally consistent) ordering on the
three small/low-pressure ones. Of six possible orderings, our compiler has
been observed producing four; the target's fifth hasn't been reproduced from
any source variant tried across 9 sessions.

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

## Validating a candidate source-shape fix against already-matched siblings

When a candidate change (an inline helper, a restructured expression, a
different declaration grouping) is being tested against a stuck function
that shares a code block with one or more *already 100%-matched* functions,
apply the same candidate to those matched siblings too, not just the broken
target — even though there's no reason to touch them otherwise. If a matched
sibling breaks, the candidate is not the target's actual original source
shape, full stop, regardless of how much it improves the broken function's
own percentage. If every matched sibling survives unchanged, that's real
evidence the candidate could be structurally correct.

This matters because a percentage improvement on a still-broken function is
not, by itself, evidence of anything — MWCC's register allocator has enough
internal degrees of freedom that a "wrong" source restructuring can
coincidentally move a broken function closer to target while being
demonstrably incompatible with the file's already-verified-correct code.
Measuring only the broken function's own number risks banking a lead that
inflates one proxy metric while moving further from the real source. This
technique is cheap (revert-to-baseline between each function tested) and
decisive in a way "does the number go up" alone is not — use it any time a
file has both matched and unmatched functions sharing one candidate fix.
First applied in `src/game/batting/batter.c`: retired a `pickBatterInputs`
helper that looked like a clean, regression-free win on one function in
isolation, by testing it against two matched siblings and watching both break
(see "Shared-block register rotation" above).

## Common-BSS inflation bug: quick disproof checklist

Before spending time reproducing `docs/common_bss.md`'s linker inflation bug
to explain an oversized target `.bss` symbol, check these first — any one of
them alone is close to decisive, and all four together are:

1. **Grep every `splits.txt` in `config/GYQE01/` (and its module
   subdirectories) for the literal string `common`.** If it's used anywhere
   in the project, individual `.bss` ranges are marked with the `common`
   attribute (see `docs/splits.md`). As of this writing it's used **nowhere**
   — this project has never needed common-BSS handling for any file, and
   `config/GYQE01/config.yml` doesn't set `common_start` either (only
   `config.example.yml`'s unused template does).
2. **Check the symbol's `scope:` annotation in the relevant `symbols.txt`.**
   `scope:local` rules the theory out immediately and structurally: common-
   BSS only ever applies to **external/global** tentative definitions (mwcc
   deduplicates them by name across TUs, like weak symbols); a `static`
   (local-linkage) tentative definition can never become `common`, in any
   MWCC version, regardless of the `-common` flag.
3. **The inflation bug needs ≥2 *other* common candidates in the same TU to
   inflate the first one's reported size** — a lone tentative-definition
   global with nothing else common in that file will show `SHN_COMMON` (if
   `-common on` is actually in effect) but its size will NOT change, since
   there's nothing for it to absorb. Don't conclude the mechanism works from
   symbol-binding alone; check whether the TU has other qualifying globals
   too.
4. **Check what `-common` setting the object's actual `cflags` resolve to**
   (`cflags_base`/`cflags_rel` never set it explicitly; only
   `cflags_runtime`, used for Dolphin libs, sets `-common off`) — for
   everything else the compiler's own default applies. Confirmed empirically
   for at least one `cflags_rel` object (`game/batting/batter.c`): with no
   `-common` flag, a tentative definition (`int x;`, no initializer) still
   compiles to a normal `.bss` symbol (`STB_GLOBAL`/`STT_OBJECT`,
   `st_shndx` = the real `.bss` section index, not `SHN_COMMON`) — i.e. this
   project's default is common **off**, not on. `pyelftools`
   (`pip install pyelftools`) is enough to check binding/`st_shndx` directly
   on the built `.o` if `readelf` isn't on PATH.

First run through in full on `game/game/batting/batter`'s `lbl_3_bss_34`
(target reports 0xC bytes at `.bss:0x34`, `scope:local`; our source only had
a 4-byte non-static `int`) — all four checks came back negative, so the
inflation-bug theory was dropped. See
`build/.match_grind/game_game_batting_batter.md` (Session 8) for the full
trace; the true content of the extra 8 bytes remains an open, honestly-
documented gap (no code anywhere in the game touches them, per
`tools/ghidra_query.py data <addr>`), not something this checklist can
resolve on its own.

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

**Function-scoped `#pragma` bracketing is NOT a different lever from
whole-file `extra_cflags` — for MWCC (this project's `mwcceppc.exe`), they
produce the same set of outcomes.** After a whole-file compiler-flag sweep
exhausts a stuck REGISTER_ALLOC/CSE-tiebreak function without effect, it is
tempting to think a pragma scoped tightly around just that function might
create a different optimizer state transition than a global CLI flag. Tested
directly (36 combinations: 4 stuck functions x 9 pragma settings, each
bracketed immediately around the one function and reverted before the next)
in `src/game/batting/batter.c`: every setting that changed any bytes at all
was a regression of the bracketed function itself (never an improvement),
and every setting that didn't regress anything was an exact byte-for-byte tie
— the same binary result as the equivalent whole-file flag from the earlier
sweep. One genuine (but here unhelpful) advantage did hold up empirically: a
pragma-scoped setting never regressed any function outside its bracket,
where the equivalent whole-file flag often did — so pragma scoping is safer
to try, just not more powerful. The real MWCC pragma vocabulary for this
compiler (confirmed via standalone `-w all` compiles, distinct from what
`-help all`/`-help obsolete` document): `optimization_level <n>|reset`,
`peephole on|off|reset`, `scheduling on|off|reset`, `cpp_extensions
on|off|reset`, `global_optimizer on|off|reset`, `push`/`pop`, `dont_inline
on|off|reset`, `fp_contract off|reset`. Notably NOT recognized (rejected as
"illegal #pragma") despite corresponding CLI flags existing: `opt_level`,
`inline_depth`, `inline on|off`, `cse off`, `register_struct_args`.

**MWCC's register allocator / CSE-object numbering is provably local to each
function's own compilation — source-level function definition order within a
TU has zero effect on codegen.** Tested by moving/swapping whole function
bodies (verified byte-identical reverts via `git checkout` between each) in
`src/game/batting/batter.c`: swapping a stuck function with an adjacent
100%-matched "control" function that shares the exact same CSE shape (in
both directions), and moving a stuck function from position #12 in the file
to position #1 (the largest possible displacement), each produced an exact
byte-for-byte tie across all 25 functions in the unit. If a function's
register-allocation tie-break doesn't resolve via source-shape changes within
the function itself, don't bother trying to reorder which functions surround
it in the file — confirmed to be a complete no-op for this compiler.
