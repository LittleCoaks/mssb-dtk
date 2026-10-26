# Matching notes

Durable, cross-file findings promoted out of individual `match` grind
sessions. The per-file checkpoint at
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

**`clrlwi rX, rY, 24` (or `extsb`) immediately after `stb rY, ...` marks
whether the source re-reads a field from memory or keeps a cached/truncated
copy — check which SIDE has the extra instruction before assuming which way
to fix it, the arrow points both directions.** Two confirmed cases:
- *Target has the `clrlwi`, ours doesn't* → the source re-reads the field it
  just stored instead of keeping a cached local; delete the local, read the
  struct field directly at each use. First seen: `src/game/batting/batter.c`,
  `calculateHitVariables` (98.36% → 100%) — a `u32 starPower` local was
  cached instead of re-reading `g_Batter.captainStarSwingActivated` after
  storing it.
- *Ours has the `clrlwi`/reload, target doesn't* → the reverse: the source
  computes the value once, stores the untruncated original, and compares a
  **truncated copy already held in a register** — it does not reload from
  memory. `int t = arr[i] + 1; arr[i] = t; if ((u8)t >= N) ...` (cast at the
  compare, not a fresh read) reproduces this; a naive re-read
  (`arr[i] = arr[i] + 1; if (arr[i] >= N)`) does not. First seen:
  `src/menus/captain_select/captain_select.c`, `loadNewCaptainModelOnCapSelectScreen` (session in
  progress — not yet fully matched, but this sub-fix confirmed regression-
  free).

Same pattern with `frsp` right after `stfs` for `float` fields (direction
not yet confirmed both ways, but check the same way).

**`bool` vs `BOOL` return type is a real, cheap-to-check matching lever for
predicate-returning functions.** `bool` is `typedef u8 bool`; `BOOL` is
`typedef int BOOL` (`include/types.h`). A function returning `bool` emits an
8-bit extract (`extrwi rX, rY, 8, 19`) where one returning `BOOL` emits a
full 32-bit shift (`srwi rX, rY, 5`) — different instructions, not just a
type-checking nicety. If a predicate function's return-path codegen doesn't
match and the function's actual return statements are boolean-shaped, try
swapping which of the two it's declared to return before looking anywhere
else. First seen: `src/menus/captain_select/captain_select.c`,
`onlySetPort1ToActiveOnInitialCapSSLoad` (+5.8% from this alone).

**Ghidra's inferred array sizes are not trustworthy — verify against actual
index arithmetic in the disassembly before trusting a struct/array size it
reports.** Two confirmed wrong sizes in `.ghidra_cache/in_game.types.txt`:
`controllerInputs` typed `[2]` but indexed by port with stride 6 up through
`base + port*6` for 4 ports (needs `[4]`); `captainIDOrderedOnCapSS` typed
`byte[2][6]` but indexed flat `0..11` (i.e. it's really `byte[12]`, or the
nesting is wrong). Cross-check any Ghidra-derived array bound against the
actual bytes touched in the `.s`/disassembly before declaring it, especially
for anything indexed by a loop variable or port/player index.

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

**MWCC `-O4,p` auto-unrolls trivial fixed-trip-count scan loops — write the
plain loop, never hand-unroll.** A plain
`for (i = 0; i < 30; i++) { if (arr[i].byteField == 0) break; }` over 0x38-byte
structs compiled to a 10x-unrolled body under `mtctr 3` (trip count / unroll
factor), with pointer strength reduction checking `0x2a(rX)` then `0x62(rX)`
before the pointer bump — all generated automatically from the plain source
loop, which matched 100% on the first attempt. If target asm shows a long
repeated check/increment body ending in `bdnz`, reconstruct the simple loop
and trust the compiler. First seen: `src/text/text_alloc.c (was Unknown/File_0x8000ff04.c)`,
`initializeTextParameters`.

Second form of the same behavior: a store-only fixed-trip loop
(`for (i = 0; i < 30; i++) arr[i].byteField = 0;` over 0x38-byte structs)
FULLY unrolls — 30 straight `stb`s at increasing displacements off one base
register, no `bdnz` at all — preceded by a vestigial guard
(`li r0, 0x0; cmpwi r0, 0x1e; bgelr`) that compares the constant initial
index against the trip count. The plain loop matched 100% first try; the
early-`break` scan form is what gets the partial (10x + `bdnz`) unroll
instead. First seen: `text_freeAllBlocks` in `src/text/text_block.c`.

**Operand order of a commutative bitwise operator is a real register-allocation
lever — `a | b` and `b | a` do not compile to the same register assignment.**
For a mask-and-merge `x = (x & MASK) | v;` whose diff against the target was a
*pure register-naming* difference (same opcodes, same instruction order, same
operand roles, only the register numbers different), rewriting it as
`x = v | (x & MASK);` matched exactly. Putting the loaded value first gives it a
proper allocatable register and frees the low register for the array base,
reproducing the target's allocation. Nothing else in the source changed. First
seen: `src/menus/rep_0788.c`, the shared post-switch tail block of `fn_2_2749C` /
`fn_2_27660` / `fn_2_325E8` / `fn_2_32A78` — 99.27-99.47% -> 100% on four
functions from the one operand swap, verified regression-free across all 150
functions in the unit. It also silently fixed an adjacent block in the same
allocation region that had the identical symptom.

Try this FIRST on any commutative expression (`|`, `&`, `^`, `+`, `*`) whose block
differs from target only by register naming. It is a trivial source edit and costs
one build, so it should be ruled in or out before any open-ended
declaration-order or local-variable-ordering sweep.

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

**Update (batter.c session 10): the chain has no precedent anywhere else in
the target binary.** A scripted scan of every scannable unit's target-side
objdiff JSON (626 units) for the block's signature pair (`addi rX, rY,
0x18cc` + `lbz rZ, 0x1905(rY)`) found zero instances outside batter.c, so no
matched function exists from which the missing fifth ordering's source shape
could be learned. Together with the six exhausted lever categories from
sessions 1-9, this mismatch class is closed for batter.c absent genuinely new
information.

**Untried as of this writing: commutative-operand-order (see "Operand order of a
commutative bitwise operator" above).** The symptom recorded in this section —
correct instructions, correct order, wrong register names, isolated to a single
shared CSE block — is exactly the symptom that the operand swap resolved in
`src/menus/rep_0788.c`. Worth a pass over the block's commutative expressions
before further declaration-order sweeps.

## Textual statement position as a register-allocation priority lever

**Where a loop-invariant assignment sits in the SOURCE changes MWCC's
register-coloring priorities even when the emitted instruction's final
position is identical (LICM/scheduling hoists it to the same place either
way).** Moving a pointer-load assignment between in-loop, pre-loop, block-top
and use-site positions can re-rank which variables get volatile vs
nonvolatile registers throughout the whole function, shifting dozens of
register assignments at once with zero structural change. Confirmed
repeatedly in `calculateTextBlockWidth` (`main/text/text_width`, still in
progress): hoisting ONLY `bank23 = ...` textually above the loop snapped the
stack frame to the target's size and fixed most of the volatile assignment
order (+1.7%); a block-local `u8 st = text->style` at one branch's top
(instead of reading `text->style` at the use) fixed another +2.3%; yet
hoisting BOTH pointer loads, or placing the same statements one line
earlier/later, regressed. The response is non-monotone and extremely
position-sensitive — sweep one statement at a time, re-measuring each move,
and treat "the compiler hoists it anyway so position can't matter" as a
disproven assumption. Naming/scope/type changes that don't alter live ranges
(u8 vs u32 vs int locals, merging single-use temps, function- vs block-scope
declarations, declaration order) were all byte-identical no-ops in the same
function — position was the only source-level lever that moved the
allocator.

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
mismatch is a genuine allocator artifact). Second data point:
`main/text/text_width` (a GC/2.6-module DOL unit) showed the same plateau —
1.3.2 through 2.7 all byte-identical, only 1.2.5/1.2.5n diverging (far
worse) — so the plateau generalizes beyond batter.c's module.

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

## Project-wide instruction-pattern scan via per-unit objdiff JSON

When a stuck function's last lead is "find a matched function elsewhere that
exhibits the same codegen pattern and read its source", the search is cheap
to run mechanically: loop every unit listed in objdiff.json, run
`build/tools/objdiff-cli.exe diff -p . -u <unit> -o tmp.json --format json`
(skip units whose objects don't exist; do NOT use `report generate`), and
regex the target-side (`left`) symbols' formatted instruction streams for the
pattern's signature instructions. ~626 scannable units complete in minutes.
First used in batter.c session 10 to (a) prove a shared CSE block is unique
to one TU project-wide and (b) find the project's only
freed-FP-register-reuse precedent (GXInitTexObjLOD, src/Dolphin/gx/
GXTexture.c) -- which on source reading turned out to be a forced else-arm
reload rather than the contested fresh-temp-at-join case. Either outcome
closes the lead decisively: a precedent scan can close a lead by *absence* of
evidence. Record a zero-hit result in the checkpoint so it is never re-run.

## rep_3D50 scene node and vector matching

- A byte field read twice through a volatile global pointer can need two distinct local widths: `int` for the first table index emits `slwi`, while `u8` for the second emits `clrlslwi`. This closed `fn_3_160814` from 98.91% to 100%.
- When target code uses `fcmpu f1,f0` against zero after `PSVECMag`, a truth test of the return value can retain that operand order where an explicit `!= 0.0f` comparison reverses it.

## Flipping a 100% unit to Object(Matching) — REL function order is REVERSED

First seen: `menus/yd_step.c` (first REL unit ever flipped, 2026-08). Once a
REL unit reports 100% in objdiff, flip its `configure.py` entry from
`Object(NonMatching, ...)` to `Object(Matching, ...)` so the linker consumes
our compiled object instead of dtk's byte-extracted original. Two traps,
both now solved:

1. **`-inline deferred` (cflags_rel) makes MWCC emit functions in REVERSE
   source order.** objdiff matches per-symbol so it never notices, but the
   linked REL lays the unit's `.text` out backwards and the sha1 check fails
   with hundreds of scattered byte diffs. Verified directly: compiling
   yd_step.c with `-inline auto` emits source order; with `-inline deferred`
   emits exact reverse source order. **Fix: write the function definitions in
   the .c file in reverse address order** (highest `.text` offset first).
   Instruction codegen is unaffected (see previous section), but the
   literal pool is not: MWCC lays out `@N` float/string constants in
   code-generation order, so in a unit with literals the reversal can change
   `.rodata` order (in `debug/rep_7A28` it fixed five 99.x% functions).
   Reverse the order while drafting, not just before the flip, and keep
   `static inline` helpers above their callers when you reorder. This applies to every REL unit (menus/game/
   debug use cflags_rel); DOL-side units don't use `-inline deferred`.

2. **dtk's synthetic string-literal symbols trigger harmless linker
   warnings.** dtk names anonymous string literals (e.g.
   `lbl_2_rodata_250`) and puts every global symbol in the module ldscript's
   FORCEACTIVE block. Our MWCC object pools those strings as *local*
   `@nnn` symbols, so mwld warns `FORCEACTIVE symbol ... doesn't exist.
   Ignored.` The warning is cosmetic — the strings still land at the right
   offsets and the link output is byte-identical. To silence it, add
   `scope:local` to those `data:string` entries in the module's symbols.txt
   (dtk only FORCEACTIVEs global symbols). Do NOT try to "fix" it by naming
   the strings in C.

Checklist when a unit reaches 100%:
1. Reorder the .c file's functions into reverse address order (REL units
   only). Rebuild; confirm still 100% and sha1 still green while NonMatching.
2. Flip to `Object(Matching, ...)` in configure.py. Rebuild (`ninja`).
3. Expect `4 files OK`. If the module's .rel FAILED, binary-diff it against
   `orig/GYQE01/files/<module>.rel` before guessing — reversed function
   order looks like massive corruption but is just layout.
4. Add `scope:local` to any of the unit's `lbl_*_rodata_*` `data:string`
   symbols in `config/GYQE01/<module>/symbols.txt` if FORCEACTIVE warnings
   appear.
5. Confirm objdiff still reports the unit 100% (`build/GYQE01/report.json`),
   since the flip changes what links, not what objdiff compares.

For a local float object that the target references by symbol, put an `extern`
declaration before the function and its `const f32` definition after the
function. In `game/ball/ball_trajectory.c`, defining the float before its use
made MWCC substitute an anonymous `@nnn` constant in the instruction
relocation; moving the definition after the function preserved the named
relocation and matched `.text` and `.rodata`.

Third trap, first seen on `game/game/ball/foul_detection` (2026-09): objdiff scored the unit
100% and the sha1 check passed while NonMatching, but the flipped link produced a `game.rel`
64 bytes short. `include/header_rep_data.h`'s `repHeaderData` is a weak local static named
`repHeaderData$localstatic3$getRepHeaderData` in every unit that includes it, and mwld folds
identically named weak symbols, so once a second unit of the same module (here alongside
`pitcher_ai`) links from our object, one copy disappears. Moving the include does not help;
the name comes from the enclosing function. Fix: `#define REP_HEADER_DATA_FN
getRepHeaderData_<unit>` before `#include "header_rep_data.h"` in every newly flipped unit of
a module that already has a Matching unit using the header. Codegen is unaffected.

## DOL units with extab/extabindex: add `-cpp_exceptions on` per-Object

First seen: `text/text_channel.c (was Unknown/File_0x8000f988.c)` (text engine, 2026-08). Some DOL
functions carry exception-unwind entries (`extab`/`extabindex`) in the
target. A .c unit compiled without exceptions emits neither section, so
objdiff shows them at 0% even with `.text` at 100% — and the unit cannot
be flipped to Matching until they exist. Fix: add
`extra_cflags=["-cpp_exceptions on"]` to that unit's `Object(...)` entry
(precedent already in configure.py: `File_0x800a6304.c`,
`File_0x800a64e0.c`). Check the target asm's header — if the .s file has
`extab`/`extabindex` sections, the flag is needed.

## Shared .sdata2 literal pool across split DOL text-engine units

The DOL text-engine group (0x8000F150-0x80010498+, our text/*.c units) was
one original translation unit: its float/double literal pool lives at
0x803CC490+ inside `auto_12_803CC400_sdata2` and is referenced across our
per-function unit boundaries (e.g. `fn_8000F150` and `drawTransformedSprite`
both load `lbl_803CC490`). Consequences: (1) value constants with real
names (`0.0f` = `lbl_803CC490`, `1.0f` = `lbl_803CC4A8`) CAN be matched by
declaring them `extern f32` and using them in place of the literal -
codegen stays byte-identical, only the reloc name changes; (2) MWCC's
int-to-float conversion bias doubles (`lbl_803CC4A0` unsigned /
`lbl_803CC4B0` signed, the 0x4330 magic) CANNOT - referencing them
explicitly forces the fsub+frsp codegen path, while the implicit conversion
emits the target's `fsubs` but pools the constant as an anonymous local
`@NN`. Those reloc-name diffs are permanent split artifacts, and any unit
emitting them also carries a local .sdata2 copy that has no home in the
link layout - blocking an `Object(Matching)` flip until the text-engine
units are eventually merged/unified. First seen: `text/sprite_draw.c`,
`drawTransformedSprite` (exhausted at 99.33% for exactly this plus one
allocator-quirk register cluster).

## 0x10-stride vector locals and hoisted &local pointers

Two stack-shape levers confirmed in `text/sprite_draw.c`: (1) when target
has vector locals at 0x10 stride (0x8/0x18/0x28/0x38), declare them as a
0x10-sized type (`Quaternion` worked; `Vec` packs at 0xC and shrinks the
frame) - and MWCC assigns stack slots in reverse declaration order here, so
declaring `c3;c2;c1;c0;` put `c0` at the lowest slot as the target wanted.
(2) when target keeps `&local` addresses alive in callee-saved regs across
intervening SDK calls (`PSMTXScale`/`Concat`) and reuses them for later
call arguments, explicit pointer locals (`Vec* p1 = ...` as plain
assignments placed just after the data-setup statements) reproduce it; the
declaration-initializer form was drastically worse (95% vs 99.1%), so
assignment position matters more than the pointers' existence. First seen:
`drawTransformedSprite`.

## Split-merged .bss objects must be addressed through one containing struct

First seen: `screenTextArray` (0x80366B18, size 0x800) in
`text/text_channel.c`. When symbols.txt holds one large object that
the original code treated as adjacent arrays (here: 30 x 0x38 ScreenText
blocks at +0x0 and a 30 x 8-byte channel table at +0x690), the target
bytes encode the base symbol's @ha/@l pair with each region's offset
folded into the load/store displacement (e.g. `lwz r0, 0x690(r3)` off the
base). Splitting the object into two symbols.txt symbols would change the
@l immediates/displacements and can never match. Instead declare a single
containing struct (`ScreenTextPool` in include/text/text_channel.h)
and access every region as a member through the one symbol.

## One base register + `addi rX, base, off` + indexed load = the TU's own STATIC data (pooled)

When a target function reaches several `.data` tables as `lis/addi base` of the FIRST object
followed by `addi rX, base, 0x360; lbzx` (and even a literal `addi r3, r31, 0x0` for the object
at the pool start), the tables are file-local `static` arrays of this TU: MWCC pools static data
and addresses every object as pool + offset (our object shows the reloc as `...data.0`). Functions
touching only one table fold the offset into the reloc, so dtk names them as separate
`lbl_*` symbols there, and that makes the tables look like extern globals. No extern
declaration shape reproduces it: struct view, pointer local, and direct global access all lost
(`fn_3_168704` 56-76%). The fix was to give the unit a `.data` split covering the tables, define
each one `static` with its real initialiser (zero-filled ones as `= { 0 }` so they stay in
`.data`), split dtk's gap-sized symbols at the real object boundaries (`scope:local`), and pull
any un-split neighbouring `.text` that also touches the tables into the unit. `fn_3_168704` went
from 73% to 100% with no other change, `.data` from absent to 100%. First seen:
`game/animation/actor_transform.c` (2026-09). The "Known unsolved" entry above is probably the
same thing and worth retrying with static definitions.

Second data point (2026-10): `data_only/rep_3B70` (92.85% -> Matching) and `rep_3C80`
(82.37% -> Matching) closed the same way. Two link details: (1) end the `.data` split *before*
the trailing zero padding that leads up to the next 0x20-aligned unit (`0x273DC`, not
`0x273E0`), and shrink dtk's gap-sized symbol to match. MWCC does not emit that padding and our
linker does not insert it, so a split covering it leaves `.data` 0x10 short and fails the sha
check. (2) objdiff stays at ~99% after the flip because ours relocates against `...data.0+off`
and the target against `lbl_3_data_*+off`. The bytes are identical, so trust the sha check.

## MWCC 2.x will not register-pool an extern data-symbol base, no matter the source shape

Target DrawText (text/text_draw, DOL) holds lbl_800E8F60's address in callee-saved
r28 from the prologue, function-wide, feeding addi+indexed loads at three branch
sites. Sixteen source-shape attempts failed to reproduce this with the pinned
GC/2.6 (and the whole 2.0-2.7 byte-identical plateau): pointer locals at every
textual position (function top, after struct-ptr init, pre-loop before/after other
pre-loop statements, in-loop top) all get computed-once-then-SPILLED to a stack
slot and reloaded per site, never a register; member-array pointer locals,
in-TU definition (global or static), inline-helper indirection, and in-place
mask forms all compile byte-identical to the plain extern member access
(MWCC canonicalizes them away); a volatile-forced memory home of another local
(diagnostic only) frees a register but the freed register goes to a different
variable, not the symbol base. Meanwhile calculateTextBlockWidth's TARGET (same
original TU, same tables) does NOT pool - it uses per-use lis/addi of separate
table symbols - so the original pooling in DrawText was a per-function allocator
ranking outcome our compiler build hasn't reproduced from any tested source
shape. If a stuck function's remaining diff hinges on a pooled extern-symbol
base in a callee-saved reg, treat it as an allocator artifact class, log it, and
spend effort elsewhere. Also confirmed here: a per-function mw_version sweep is
worth running even inside a known plateau - DrawText IS version-sensitive
(1.3.x differs from the 2.0-2.7 plateau; 3.0a regresses further) even though
sibling text_width was not. First seen: text/text_draw.c DrawText (83.75%,
sessions 1, 2026-08).

## Explicit pointer local vs. compiler strength reduction (extra `addi r0`/`mr rN` at loop setup)

First seen: `text/text_draw_conditional.c` (2026-08). Symptom: LOGIC otherwise
identical, but our loop setup emits `lis r4, sym@ha; addi r0, r4, sym@l;
mr r31, r0` where the target has a single direct `addi r31, r4, sym@l`, and
every later branch offset shifts by 4 as a cascade. Cause: the source
declared an explicit pointer local (`ScreenText* block = arr.blocks;` with
`block++` in the loop) where the original code just indexed the array
(`arr.blocks[i].field`) and let MWCC's strength reduction synthesize the
induction pointer itself. The compiler-generated induction variable gets
initialized directly into its home register; a programmer-declared pointer
initializes through a temp + `mr`. Fix: delete the pointer local and index
the array directly. Related detail from the same function: equality operand
order is observable in `cmpw` (target `cmpw r29(arg), r0(field)` required
writing `group == blocks[i].drawGroup`, not the reverse).

## A stray `addi r0, rX, sym@l` + `mr` for a loop pointer means the loop was index-based

First seen: `text/text_init.c` initTextRendering (2026-08). A copy/scan loop
matched except for one extra `mr rHome, r0` materializing the destination
pointer before the loop, where the target had `addi rHome, rHa, sym@l`
directly. No placement, declaration-order, `register`, cast, or
flag/mw_version permutation of a user-declared walking pointer removes it
(~40 variants tried). The target register was MWCC's own strength-reduction
induction variable: writing the loop with an integer index
(`dst[i] = src[i]; i++;` inside `while (1)` with an early return) and no
user destination pointer lets the compiler synthesize both walking pointers
itself, matching instantly.

## Re-reading a just-stored global forwards the stored register (avoids recompute)

First seen: `text/text_init.c` initTextRendering (2026-08). Target had
`lwz r3, 0x1c(r3)` where r3 still held a value just stored to a global
(`stw r3, 0x7b4(r5)`). Writing the C as a read back through the stored
field (`src = screenTextArray.textBanks[7]->strings[6];` right after the
`textBanks[7] =` store) makes MWCC reuse the stored register directly. A
source-level temp (`strs = bank->strings; ... src = strs[7];`) does NOT
reproduce this — MWCC folds the temp back into base-relative addressing
(`lwz 0x20(bank)`). Relatedly, eliminating the `bank` local entirely
(spelling every access as `screenTextArray.textBanks[0]->...`) was what
fixed the pool-base/bank register coloring in the same function.

## The sha check, not objdiff, catches missing extab — check before flipping to Matching

First seen: `Unknown/File_0x800b0cb8.c` RunDrawScripts_with_stack_variables
(2026-08). The function reached 100% in objdiff, but flipping the unit to
`Matching` broke the `build.sha1` CHECK step: the target object carries
`extab`/`extabindex` sections (this DOL region was compiled with exceptions
on) that a default C compile does not emit, so the linked DOL diverged even
though every instruction matched. objdiff's function score never surfaces
this — its unit view shows extab at 0% but the classify/percent tools look
at .text only. Fix is the established pattern:
`extra_cflags=["-cpp_exceptions on"]` on the Object (see the `text/` units).
Before promoting any DOL unit to Matching, grep `config/GYQE01/splits.txt`
for an `extab` range on that unit.

## A stack scratch buffer's size is invisible except through frame rounding

Same function. Callbacks are invoked with pointers to local scratch buffers;
the `addi rX, r1, off` argument setup pins each buffer's *base* offset, but
nothing in .text pins the topmost buffer's *size* — it only feeds the frame
size via MWCC's rounding. A 0x20 guess produced frame 0x50 vs target 0x40
with every other instruction identical; sweeping the array length found
0x14–0x1C all produce the target frame. When only the prologue/epilogue
frame constants differ, sweep the size of the highest-addressed local
instead of hunting for phantom temps.

## A stored constant that the guard already proves: store the compared register, not the literal

First seen: `menus/captain_select/captain_select.c`, `captainSelectScreenInputs`
(95.96% -> 96.4%, session 17, 2026-08).

Symptom: inside a branch guarded by a comparison like `if (... && field == 1)`, the
target STORES A REGISTER it already loaded and compared, and emits no `li` for the
constant at all:

    lbz    r0, 0x0(r31)      ; the field
    cmplwi r0, 0x1           ; the guard's comparison
    bne    <else>
    stbx   r0, r7, r3        ; stores r0 — the compared register

while we emit an extra `li r0, 0x1` and store that. Cause: the original source did
not write the literal. It wrote the expression the guard just tested —
`tmpCapIdx[idxVal] = gameSetUpStep.portCaptainSlot[0];`, not
`tmpCapIdx[idxVal] = 1;`. The two are behaviourally identical on that path precisely
because the guard proves it, which is what makes the substitution safe.

The cost is never just the one instruction: the extra `li` occupies a register and
cascaded into ~14 rows of register-allocation divergence through the rest of the
block here. Whenever a target stores a constant inside a branch whose condition
proves a nearby expression EQUALS that constant, and it does so without materialising
the constant, write the expression instead of the literal.

## Genuinely dead code is reproducible, and the recipe is "re-test the global"

First seen: `menus/captain_select/captain_select.c` — `captainSelect_handleInputs`
(sessions 15) and `captainSelectScreenInputs` (95.49% -> 95.96%, session 17, 2026-08).

Original builds retain unreachable instructions that the compiler did not eliminate:
a conditional branch immediately after an unconditional one, or a test on a condition
register that provably still holds the opposite result. Two independent instances in
one file have now been reproduced, and one of them also closed a long-standing
frame-size residual — dead code occupies registers and branch slots like any other
code, so do not deprioritise it on the grounds that "it does nothing".

The recipe that worked both times: **re-test the same GLOBAL EXPRESSION.** A cached
local (`u8 dispatch = 0; if (dispatch != 0) ...`) is constant-folded away every time;
re-reading the actual global (`if (lbl_2_bss_100B8[0x4A] != 0) ...`, or a bare
`if (globalArray[idx] != 0) { return; }` placed straight after the block that already
tested it) survives to the object file.

Before writing a dead block off as unreproducible, read the target's ACTUAL layout for
the region — which branch is unconditional, which condition register is reused, and
what sits in the fall-through versus the branch target. Both instances here had
previously been abandoned as "MWCC constant-folds this away", a conclusion drawn from
failed guesses at the source shape rather than from reading the layout.

## One call-argument site can own an entire callee-saved register

First seen: `menus/captain_select/captain_select.c`, `captainSelect_handleInputs`
(97.10% -> 98.60%, session 17, 2026-08); same lever previously in
`captainSelect_APress` and `captainSelect_BPress` in the same file.

When a function takes a wide parameter it uses narrowed (e.g. `int port` used as
`(u8)port`), targets are routinely INCONSISTENT about whether each individual use site
reads a cached narrowed copy or re-narrows from the raw parameter. A blanket rule —
either a named `u8 p = (u8)port;` local used everywhere, or inline casts everywhere —
cannot express that, and blanket edits in both directions regressed here repeatedly.

What works is a site-by-site map: for the parameter, list every use on BOTH sides in
order, note where the target re-masks fresh (`clrlwi r3, rRaw, 24`) versus reads a
cached copy (`mr r3, rCached`), and match that polarity site by site. Building the map
is one worker round trip and is far cheaper than variant-sweeping.

The payoff can be structural, not cosmetic. Here a SINGLE call argument changed from
the cached local `p` back to an inline `(u8)port` eliminated the cached copy's
callee-saved register outright, taking the frame from `stwu r1, -0x40(r1)` /
`stmw r23, 0x1c(r1)` to the target's `stwu r1, -0x30(r1)` / `stmw r24, 0x10(r1)`. If a
function's diff is dominated by ARG_MISMATCH rows cascading off one parameter, and its
callee-saved count is one higher than the target's, suspect exactly one over-cached use
site before trying anything else.

## Re-measure a checkpoint's "closed" claims before building on them

First seen: `menus/captain_select/captain_select.c`, session 17 (2026-08).

A prior session's checkpoint entry declared a function's frame-size residual CLOSED and
quoted both sides as identical. Two independent workers this session, each cross-checking
against the target `.s`, measured our side one callee-saved register HIGHER than the
target — the residual had never been closed, and the earlier session had almost certainly
read the target column twice instead of target-versus-ours. Several later entries in the
same log were written on top of that false premise.

The same file separately lost multiple sessions to an inverted target/base column reading,
and once to a worker parsing a stale JSON left in a shared scratchpad by an earlier worker
(the giveaway was symbol names that had been renamed away sessions earlier).

Cheap, decisive countermeasures, worth applying to any long-running grind:
- Require every diff report to cross-check at least three target-attributed instructions
  against the module's `.s` file and to SAY that it did.
- Never let a worker reuse a pre-existing JSON from a shared temp directory; have it write
  a uniquely-named file and parse only that.
- Keep one known-current symbol name in mind as a staleness canary — if a report mentions a
  symbol that was renamed several sessions ago, the whole reading is stale.
- Treat a "closed"/"exhausted" claim as a hypothesis with an owner and a date, not as fact;
  re-measuring one costs a single round trip.

## From-scratch files: empty stub callees are inlined away (work bottom-up)

First seen: `game/game/fielding/fielder` (223 functions, all `return;`
stubs at session start, 2026-09).

In a file being decompiled from scratch, MWCC (`-O4,p -inline deferred`) inlines
an empty `return;` stub callee and deletes the call site outright. A caller can
therefore never match while any of its in-file callees is still a stub — its
diff will show the target's whole `stwu`/`mflr`/`bl`/epilogue frame against a
bare `blr` on our side, which looks like a catastrophic LOGIC failure but is
purely an artifact of the callee.

Two consequences:
1. Order the work by the call graph, not by function size. Build the leaf
   functions (no in-file `bl` at all) first, then their callers. Ranking the
   still-stubbed callees by how many in-file callers they have identifies the
   highest-leverage next targets cheaply — parse `bl` targets out of the dtk
   `.s` and cross-reference which bodies are still stubs.
2. `#pragma dont_inline on` / `#pragma dont_inline reset` bracketed around the
   *stub callee* preserves the call and lets you validate a caller's source
   shape before its callees exist. Verified:
   `autoMovement0_stayStill_exceptForSpecialActions` read 23.25% with the stub
   inlined and 100% with the pragma applied — i.e. the caller's C was already
   exactly right and the number was measuring the callee, not the caller.
   Treat this strictly as a diagnostic and revert it: the target's callee is a
   real, non-inlinable function, so the pragma is scaffolding that describes our
   incomplete tree, not the original source.

The general lesson is that a low match% on a caller is not evidence about the
caller at all until its callees are real. Check the callee state before opening
a hypothesis log on any function in a from-scratch file.

## An explicit struct-base pointer local is right for repeated fixed-index access (and wrong for loop induction)

First seen: `game/game/fielding/fielder` (2026-09). Note this is the exact
OPPOSITE conclusion to "Explicit pointer local vs. compiler strength reduction"
above, and the two are not in conflict — they cover different cases.

For a function that accesses one array element repeatedly at a FIXED index
(`g_Fielders[fielderIndex].a`, `.b`, `.c` ...), write the explicit pointer local
`InMemFielder* fielder = &g_Fielders[fielderIndex];` when the target
materialises the base into a register (`mulli` + `addi rBase, rHa, sym@l` +
`add rN, rBase, rIdx`) and then uses plain displacement accesses off it.
Measured, from array indexing to pointer local, with no other change:
- 79.71% -> 100% (array indexing emitted an indexed `lfsx` for the offset-0
  member, where the target used `lfs f1, 0x0(rN)`),
- 98.18% -> 100% (array indexing mis-ranked the `mulli` result's register once a
  second global was also live).

Two reliable tells that you need the pointer local: an indexed load/store
(`lfsx`/`lwzx`/`stbx`) on our side where the target has a plain displacement
form, and the base being materialised *before* a branch or a call that it has to
survive (i.e. it lives in a callee-saved register).

By contrast, for a WALKING pointer over a loop, the user-declared pointer is the
wrong shape and the index form is right — see the strength-reduction entry
above. Fixed index: declare the pointer. Moving index: declare the integer.

## Naming a target's local rodata float label: declare it extern, never define it

First seen: `game/game/fielding/fielder` (2026-09); the pattern itself
predates it in `src/menus/rep_1028.c`.

Writing a plain float literal (`x = 0.0f;`) pools an anonymous `@NNN` constant,
which objdiff scores as a CONST_POOL mismatch against the target's dtk-named
`lbl_N_rodata_XXXX` relocation, capping an otherwise-perfect function just below
100%. The fix is the `rep_1028.c` pattern: declare the label
`extern const f32 lbl_3_rodata_B20;` and use the symbol in place of the literal.
Codegen is byte-identical; only the relocation name changes. That alone took one
function from 99.29% to 100%.

Do NOT use the definition form (`const f32 lbl_3_rodata_B20 = 0.0f;`) — tested
and disproven in the same session. It emits an *additional* local `.rodata`
symbol at the wrong offset (0x60 rather than the target's 0), leaves `.text`
worse than the extern form, and inflates the `.rodata` section percentage
spuriously without matching any target byte. If a `.rodata` score moves in the
right direction while `.text` moves in the wrong one, check whether you created
a duplicate symbol before banking the result.

## Ghidra's type cache holds full layouts for globals the project headers stub as padding

First seen: `game/game/fielding/fielder` (2026-09).

`.ghidra_cache/in_game.types.txt` contains complete, offset-annotated `STRUCT`
definitions for game globals that `include/game/UnknownHomes_Game.h` currently
declares as mostly `u8 _pad_NNN[...]`. Expanding one of those in-place —
same offsets, same total size, real member names instead of padding — is
codegen-neutral by construction and is the single cheapest enabler before
starting a from-scratch file that touches that global heavily. Two expanded this
session (`InMemFielder` 0x268, `g_FieldingLogic_s` 0x150), both verified neutral
by stashing the header change, rebuilding, re-diffing, and confirming every
affected unit was byte-identical.

Do this verification rather than assuming it: the expansion touches a shared
header, so the blast radius is every unit that includes it. Grep for which files
reference the struct's members first, and re-diff those specific units before
and after.

Two cautions when translating:
- Sanitize aggressively but do not import Ghidra's enum typedefs — map each
  enum-typed member to the plain integer type of its stated size. Ghidra member
  "names" are frequently value descriptions rather than names (`const_30`,
  `15.0_wjFramesTillContactWWall`) and several collide within one struct; where
  that happens, an honest `_0NNN` offset name is better than a fabricated one.
- Ghidra's array bounds are not trustworthy (see the entry above); its *offsets*
  and total struct sizes, cross-checked against the `size:` field in
  `config/*/symbols.txt`, have held up.

## A constant-returning stub folds away the CALLER's test, not just the call

First seen: `game/game/fielding/fielder` (2026-09, session 2). This
extends "From-scratch files: empty stub callees are inlined away (work
bottom-up)" above — the mechanism there is broader than that entry states.

A `return 0;` stub (not just an empty `return;`) does more than let MWCC
delete the call site: it lets MWCC constant-fold the *caller's* test of the
return value too. A caller written `if (callee(i) == 0) { ...body... }` loses
the call, loses the test, and loses its entire stack frame — the body becomes
unconditional. The caller's diff then shows our bare body against the target's
full `stwu`/`mflr`/`bl`/epilogue, which reads as a catastrophic LOGIC failure
but is entirely an artifact of the callee, not the caller's source.

Measured: `autoMovement19_foulBall` has correct source and is capped at
59.17% purely by this. Its sibling
`autoMovement0_stayStill_exceptForSpecialActions` was separately proven to be
100%-correct source via `#pragma dont_inline` on the callee, and both are
blocked on the same callee `updateFielderPositionAndVelocityForSpecialActions`.

Practical rule: before opening a hypothesis log on any caller in a
from-scratch file, check whether every in-file callee has a non-trivial body
AND, if it returns a value, that the returned value isn't a hardcoded
constant. A percentage on a caller with a stubbed callee measures the callee,
not the caller.

## A hub function does not need to reach 100% to unblock its callers

First seen: `game/game/fielding/fielder` (2026-09, session 2). Corollary
to "A constant-returning stub folds away the CALLER's test, not just the
call" above, and a scheduling insight for from-scratch files.

A caller's codegen depends only on the *call site* — argument setup, the
`bl`, and how the return value is consumed — not on the callee's body,
provided the callee is large enough that the compiler will not inline it. So
giving a large hub function a real, correct, non-trivial body restores the
call site in every one of its callers even while the hub itself sits far
below 100% (typically because the hub is itself blocked on *its* callees).
This makes large dispatchers worth implementing early, even though they
cannot be finished, because they convert many callers from "unmeasurable" to
"measurable and matchable".

Prioritize hubs by **unblock yield** — the number of blocked functions whose
ENTIRE stub-blocker set is that one function — NOT by raw caller count.
These diverge sharply: in `fielder`, `autoMovementDetermineWhatToDo`
had 5 callers and yield 5, while `setInitialFielderMovements_CoverBases` and
`setInitialFielderMovements_cutoffs` had 11 callers each and yield **0**
(every one of their callers was simultaneously blocked on something else
too). Implementing a yield-0 hub buys nothing immediately.

Confirmed prediction: implementing `autoMovementDetermineWhatToDo` (484 B, a
leaf) took itself 0% -> 100% and simultaneously took `fn_3_33D9C` and
`fn_3_40D54` from 7.69% -> 100% each, in one build. Three functions matched
from one change.

## Pointer-local scope of assignment is a separate lever from pointer-vs-array

First seen: `game/game/fielding/fielder` (2026-09, session 2). This
refines "An explicit struct-base pointer local is right for repeated
fixed-index access (and wrong for loop induction)" above. That entry frames
the choice as binary (declare the pointer vs. use the index). There is a
third, finer lever: *where in the function the pointer is assigned*.

Measured on `fn_3_49EA8`, three steps, identical semantics throughout, only
the pointer's declaration/assignment placement changing:
- `InMemFielder* fielder = &g_Fielders[i];` initialized at the top and used
  for every store: **89.86%**
- array indexing for the two tail stores, pointer for the rest: **98.92%**
- `InMemFielder* fielder;` declared uninitialized at the top, array indexing
  for all stores OUTSIDE the main `if` block, and `fielder = &g_Fielders[i];`
  assigned only INSIDE that block: **100%**

The reliable tell for which individual stores want array indexing rather
than the pointer: in the target, that store re-derives the global base into
a fresh register (`lis`/`addi`/`add`) instead of reusing the already-live
base register. Mixing the two forms within one function is often correct and
is what the original source evidently did.

Cross-reference "Textual statement position as a register-allocation
priority lever" above — this is the same underlying phenomenon (source
position re-ranking MWCC's register coloring) showing up specifically for
struct-base pointers.

The same mixed shape independently took `autoMovementDetermineWhatToDo` to
100% on the first try: pointer local for the dense middle blocks, array
indexing for the three trailing single stores.

## `report generate` and per-unit `diff` report different match% for the same build — neither is stale

First seen: `game/game/fielding/fielder` (2026-09, sessions 3-4).

`objdiff-cli report generate` (whole-project) and per-unit `objdiff-cli diff
-p . -u <unit> -o - --format json` report DIFFERENT absolute match
percentages for the exact same build, and both are correct under their own
method: `report generate` resolves relocations with full cross-object
context, so it scores relocation-bearing instructions a per-unit diff cannot
resolve, and its numbers run higher. Worked example: `fn_3_4DB84` in
`fielder` reads 80.00% under `report generate` and 77.08% under
per-unit `diff`, both current, both correct.

Consequence: a session that iterates with per-unit `diff` and then closes
out with `report generate` (or vice versa) will see an apparent jump or
drop that looks like a regression or a win but is purely a change of
measuring instrument. This actually happened — a `fielder` session
"corrected" a figure in its own status table as stale when it was simply
the other method's number.

Rule: pick ONE method as a checkpoint's canonical measure and label every
recorded figure with the method it came from. Iterate with per-unit `diff`
(it is far cheaper — no full-project build needed); reconcile with `report
generate` only at session close-out, and never compare a number from one
method against a number from the other.

## Whole-struct assignment of a float vector lowers to integer word copies

First seen: `game/game/fielding/fielder` (2026-09, sessions 3-4).

Assigning a small all-float struct (e.g. `VecXYZ`) wholesale — `dst.vec =
src.vec;` — makes MWCC lower the copy to integer `lwz`/`stw` word moves.
Targets that were written with per-component assignment emit `lfs`/`stfs`
instead. Symptom: control flow and instruction count match exactly, but the
tail of the function shows integer load/stores where the target has float
ones, often with a different base register as well.

Fix: write the copy component-by-component (`dst.x = src.x; dst.y = src.y;
dst.z = src.z;`). Worked example: `fn_3_27764` in `fielder` went
93.81% -> 100% purely from this change, and it fixed the base-register
choice for free — explicit float loads let the register allocator release
the pointer register the integer-copy form had pinned, matching the
target's register reuse exactly.

Rule: if a target shows `lfs`/`stfs` for a struct copy, never use
whole-struct assignment for it, regardless of how much cleaner the
aggregate assignment reads.

## An "empty block the compiler eliminated" is almost always a misread branch

First seen: `game/game/fielding/fielder` (2026-09, sessions 30-31).

If the target emits real compare/branch instructions where your source has an empty or
apparently-dead conditional, do not conclude the compiler folded an empty `if` away.
**Resolve every branch destination before calling a block dead.** A forward branch that
skips a large region means the block is a live GUARD and the skipped region is its BODY.

Worked example: `autoMovement15_selectedFielderOnLooseBall`. Session 30 recorded seven
instructions at `0003B504`-`0003B51C` as "an empty-bodied `ballState` check that MWCC
eliminates but the target emits anyway", and wrote `if (...) {}` in the source, leaving a
32 B gap on that premise. Session 31 resolved the actual destinations: both `beq`s jump
forward to `0003B5F4`, skipping 53 instructions / 212 bytes. It was a real guard whose body
was the entire following dispatch. Rewritten as
`if (ballState != BALL_STATE_HIT && ballState != BALL_STATE_LOOSE) { ... }` it went
91.9% -> 98.97%, then to 99.82% at exact size once the guard polarity was also fixed.

The misdiagnosis survived a full session and cost one. Treat any apparently-empty
conditional as a red flag to re-check, not as a curiosity to note and move past.

## `ATAN2F`'s `(f32)` cast emits a stray `frsp`

First seen: `game/game/fielding/fielder` (2026-09, session 41).

`ATAN2F(y,x)` is `((f32)atan2((y),(x)))`. Storing its result into an `f32` local, or
using the macro at all, rounds to single precision. If the target feeds the `atan2`
result straight into a further double-precision expression with no `frsp` in between,
call `atan2()` directly instead of the macro. Worth exactly 4 bytes (one instruction)
and took `updateFielderDirectionFacing` from 2076 B to an exact 2072 B match.

## A `static inline` helper is not codegen-neutral at every call site

First seen: `game/game/fielding/fielder` (2026-09, session 41).

Replacing a repeated hand-written block with a `static inline` call was byte-identical
at ~125 sites in `fielder.c` but changed codegen at ~17 others — improving one function
by +3.4 points (`HandleMiddleInfieldSelection` 96.34% -> 99.73%) and regressing others.
Worse, when the expansion changes a function's SIZE, intra-TU `bl` branch immediates
shift and perturb unrelated *calling* functions, so a whole-unit regression check is
mandatory, not just a check of the edited function. Treat each call site as its own
measurable hypothesis rather than assuming the rollout is free.

## An exact size match plus a low score means block ORDERING, not missing logic

First seen: `game/game/fielding/fielder` (2026-09, session 41).

When ours and the target are the same byte count but score in the 80s, stop looking for
absent code and reconstruct the target's physical basic-block order from its branch
labels, then find the source shape that emits that order. On
`updateFielderDirectionFacing` this took 83.7% -> 98.6% in two steps. The lever is
usually which arm of an `if`/`else` is the fall-through, and whether a shared tail block
sits before or after a large cascade.

## Batching Ghidra decompiler output is the main accelerator for a from-scratch file

First seen: `game/game/baserunning/runner` (78 functions, all `return;` stubs at
session start, 2026-09).

`tools/ghidra_query.py decomp <name1> <name2> ...` runs ONE headless Ghidra pass
over every name given (~15 s total), so batching a whole work-batch into a single
call is nearly free. It needs `MSSB_GHIDRA_HOME` pointed at the install that holds
the `.gpr` — on this machine `E:\Project Rio\Ghidra 11.0.3`, NOT the other Ghidra
install present, which has `analyzeHeadless` but no project and fails with
"Could not find project".

Two caveats. Functions that still carry dtk placeholder names (`fn_3_XXXXX`) are
frequently not defined as functions in the Ghidra program at all and come back
`NOT FOUND`; read the `.s` for those. And Ghidra's field names come from an older
struct model, so every member reference has to be re-mapped onto the real header
before use. Treat the output as a strong hint about control flow, never as truth.

Related: `ghidra_query.py name` works with no Ghidra install at all, reading only
`.ghidra_cache/*.symbols.txt`, but those caches can be months stale.

## Constant vs. variable index decides pointer-local vs. array access

First seen: `game/game/baserunning/runner` (2026-09). This completes the pair of
entries above ("An explicit struct-base pointer local is right for repeated
fixed-index access" and "Pointer-local scope of assignment"), which cover the
variable-index case only.

Three distinct shapes, all measured in one file:
- **Several DIFFERENT CONSTANT indices** in one function (`g_Runners[1].a`,
  `g_Runners[2].b`) -> plain array access. MWCC then shares ONE base register and
  emits large displacements (`n*0x154 + fieldOffset`). Declaring a pointer local
  per runner makes it reload `lis`/`addi` each time: 92.43% with pointer locals,
  **100%** with plain array access on `running_beginFrame_checkForceOut`.
- **Repeated access to ONE element at a VARIABLE index** -> explicit pointer local
  `InMemRunnerType* runner = &g_Runners[i];` (the existing entries).
- **A loop over elements where the target bumps a base by the struct stride
  inside the loop** -> walking pointer `for (i=0; i<4; i++, runner++)`. This
  reached 100% on `running_initLiveBallWithoutContact`, and separately made MWCC unroll a copy loop the
  same way the target does (69.4% -> 83.0% on
  `running_transferRunnerToNextIndex`).

The tell for the first case is our side re-materialising the global base
(`lis`/`addi`) where the target reuses an already-live base register.

## Write a sum of two squares as separate statements

First seen: `game/game/baserunning/runner` (2026-09).

`dolsqrtf2(dx*dx + dz*dz)` fuses into an `fmadds` that targets written as
separate statements do not have. Writing `dx = dx*dx; dz = dz*dz;
dolsqrtf2(dx + dz);` removes it. Worth 95.87% -> 98.64% on
`running_updateDistAndFramesToClosestBases`, and the same shape recurs in every
distance calculation in the file.

## A `u8` field compared `>= 0` folds away — the target's `extsb.` means an `s8` cast

First seen: `game/game/baserunning/runner`, `running_checkForOuts` (2026-09).

If a struct field is declared `u8` and the source tests `field >= 0`, MWCC folds
the test away entirely (it is always true). When the target emits `lbz` followed
by `extsb.` and a REAL branch, the original source cast to signed first —
`(s8)runner->baseOfFailedBodyCheck >= 0`. Adding those casts was the last diff
between 99.x% and 100% on `running_checkForOuts`. Note this is a different
situation from a genuinely mis-typed field: the field really is `u8` storage and
`-1`/`0xFF` is being used as a sentinel, so the cast belongs at the comparison,
not in the struct.

## On a large function, invert the outermost conditional before doubting the body

First seen: `game/game/baserunning/runner` (2026-09).

Which arm of the outermost `if`/`else` is the fall-through dominates the whole
function's block layout, and getting it backwards scores near zero even when
every statement is correct. On `running_liveBall_human` the first draft scored
**7.9%**; making the other arm the outer `if`, with no other change, scored
**95.55%**. If a big from-scratch function scores in the single digits, try the
inversion before rewriting the body. Cross-reference "An exact size match plus a
low score means block ORDERING, not missing logic" above — this is the cheapest
instance of that class.

Related, smaller levers measured in the same file: `else if` chains versus nested
`if`s (81.37% nested, 97.20% plain `else if`, 99.07% `else if` with explicit
`(x & FLAG) == 0` guards on the last branches, all on `running_getDirectionOverride`),
and `<= 1` versus `< 2` (the target's `cmplwi 1; bgt` versus our `cmplwi 2; bge`).

It applies to small functions too, and to the early-return polarity specifically:
`fn_3_F6504` (196 B, `game/game/stadium/sta_c5`) went 95.10% -> 100% purely by
rewriting `if (!cond) return NULL; build;` as `if (cond) { build; } else { return NULL; }`.

## When the target inlines an in-file function it also keeps standalone, copy the body

First seen: `game/game/baserunning/runner`, `running_main` and
`ccs_running_main` (2026-09). Compare "Contradictory declaration-order requirements
between an auto-inlined static and its standalone `*_unused` copy" above — same
underlying situation, different remedy.

**Superseded (2026-10-18): calling the helpers does work, built inside-out.** The
earlier finding here was that a dispatcher hub could not be matched by calling
its inlined helpers, because "MWCC declines to inline a function that is also a
real standalone symbol" (`running_main`: calls 75.3%, copied bodies
94.2%). That was the `-inline auto` size budget, not the standalone symbol. MWCC
measures a callee *after* its own inlining, so a helper whose body is still a
pasted copy of its sub-helpers is too big and stays a `bl`, while the same helper
written as calls to those sub-helpers inlines. Fix order is innermost first:

- `running_liveBall` calls `running_liveBall_clearStealing`. That alone took
  `running_liveBall` 97.94% -> 100% (its pasted loop cached `liveBallReason` in
  a local; the target re-reads the field).
- `running_updateRunner` calls `running_updateRunner_chooseDirection` and
  `running_updateRunner_roundBaseOrDugout`; `running_atBatSteals` calls
  `running_atBatSteals_humanInput`.
- Only then does `running_main` match at 100% as
  `running_beginFrame(); ...; running_atBatSteals();` / `running_liveBall();` /
  `running_updateRunner(i);` / `running_endFrame();`. Calling
  `running_atBatSteals()` while its body was still pasted gave 79% with a real
  `bl running_atBatSteals`; marking it `inline` matched the caller but dropped
  the standalone copy (0%), so the keyword is not the fix.

To find these: list functions nothing in the module references (no `bl`, no
`@ha/@l`, no data pointer), then look for their bodies in same-file callers. In
runner.c every such orphan was an inlined helper. Not every one can be called:
in `ccs_running_main` the Chain Chomp stage helpers (`ccs_runnerChompHit_recover`, `ccs_runnerChompHit_updateKnockback`)
either stayed a `bl` or inlined to a worse 97.15%, so keep those pasted.

OPEN QUESTION from the same file, recorded so it is not re-derived: the reverse
also happens. MWCC inlined two fully-implemented small callees
(`ccs_updateRunnerAngles`, `running_updateForceStatus`) into
`running_endFrame` where the target keeps real `bl` calls, forcing that
caller to 0.0% and 1040 bytes against the target's 356. A `#pragma dont_inline
on`/`reset` bracket around the two callees restores the calls and the match. That
pragma is currently in `src/game/baserunning/runner.c` and is almost certainly NOT
the original source shape — it is scaffolding. The real question, unresolved, is
what source property made the original compiler keep those calls.

## MWCC lays `.bss` out in REVERSE declaration order

First seen: `game/game/fielding/fielder_ai` (2026-09), a 59-function from-scratch file.

When a translation unit's file-static (`scope:local`) uninitialized objects must land
at specific `.bss` offsets, declare them in **descending address order** — the reverse
of how they appear in the linker map. Declaring them in ascending address order put
`hexBaserunnerTracker` at `+0xd8` instead of the target's `+0x2c`; simply reversing the
declaration list produced every target offset exactly and took the unit's `.bss` from
0% to **100%** in one edit.

This is the data-side analogue of the known `-inline deferred` function-emission
reversal (see "Flipping a 100% unit to Object(Matching)"), and it is worth doing FIRST
on any from-scratch file with file-static globals: it is one edit, it is free, and
every function that touches those globals is mis-scored until the offsets are right.

## dtk `.bss`/`.data` symbol sizes are gap-derived — a "too big" symbol is often several merged objects

First seen: `game/game/fielding/fielder_ai` (2026-09). Compare "Split-merged .bss
objects must be addressed through one containing struct" above — that entry covers the
opposite case, and the two are distinguished by what the TARGET's addressing looks like.

dtk infers a `.bss` symbol's `size:` from the distance to the next symbol it knows
about, so one named symbol frequently spans SEVERAL distinct original objects. The tell
is in the target's addressing: if the target reaches a location through a *different*
base+displacement pairing than your single declared array would produce — e.g.
`addi r4, rAnchor, 4` then `lbz 3(r4)` for a byte your array would reach as
`((u8*)&arr[1])[3]` — the original source had a separate, smaller object there.

Splitting the symbol in `config/*/symbols.txt` (and declaring the pieces separately in
C) is legitimate and was decisive here. Measured on `fieldingAIThrowOrChase`: named
arrays without the split **64%**, fully opaque anchor indexing **59%**, hybrid **69%**,
after splitting `runningStratToMakePlay[8]` into `framesRunnerIsOutOfReach[4]` +
`runningStratToMakePlay[4]` **94.9%**, and **99.24%** once a `u8[4]` was also split out
of `lbl_3_bss_17F8`. The same splits independently took `fn_3_A2B6C`, `fn_3_A2C9C`,
`fn_3_A2DDC`, `fn_3_A31E8` and `fn_3_A32B8` to 100%.

Two guard rails. The split must PRESERVE every offset — re-measure `.bss` at 100%
afterwards, which is what proves the layout is still byte-identical. And splitting
forces you to name the new pieces; name them from evidence (a corroborating function
name, an observed use) or leave an honest `lbl_*` placeholder, never a guess dressed up
as a fact.

## `do { ... break; ... } while (0)` is the structured form of exit-block threading

First seen: `game/game/fielding/fielder_ai` (2026-09).

When a target reaches one physical exit/tail block from several different conditions,
the usual remedies are a `goto` or a merged boolean chain. A merged `&&`/`||` chain
often cannot reproduce the target at all — it collapses the separate
`li rX, N; b tail` sequences the target emits per branch. Before reaching for `goto`,
try wrapping the region in `do { ... } while (0)` and using `break` as the thread to the
tail. On `genericPlayOnRunnerOffBase` the merged chain scored **97.26%** and the
`do/break/while(0)` form scored **100%**.

Its limit is real and worth knowing: `break` only escapes the innermost loop, so if the
exit sites sit inside nested `for` loops the construct cannot express the control flow
and collapses into a flag variable. Measured on `tagOutValues`, where the five exit
sites are inside nested loops: `goto` **92.78%**, flag variable **89.73%**,
`static inline` tail helper **17.74%** (it got inlined five times), `do/while(0)` not
expressible. That is a case where `goto` is genuinely correct — but note it was only
established by measuring all four, which is the standard to hold.

## The int-to-float conversion bias constant is NOT a scoring floor — rebuild the literal pool instead

First seen: `game/game/fielding/fielder_ai` (2026-09). Corrects this entry's earlier claim, which
was drawn from this same file before the fix below was known.

objdiff scores a `.rodata` reference as matching when it lands at the same pool OFFSET, whatever
the symbol is called — so an anonymous `@NNN` conversion bias matches the target's dtk-named
`lbl_N_rodata_XXXX` once our pool is laid out identically. Three changes applied together took
`fielder_ai`'s `.rodata` from 45.26% to 100% (and `pitcher.c` the same way):
- plain float literals instead of `extern const f32 lbl_N_rodata_XXXX` labels;
- function definitions in reverse address order (REL units: `-inline deferred` emits reversed,
  so the pool fills in the target's first-use order);
- `#define SQRT2_LINKAGE static` before the first include, so dolsqrtf2's `_half`/`_three`
  statics don't sit at the head of the pool.
Six `fielder_ai` functions went to 100% from this alone. The cost: a literal multiplier is
scheduled differently from an extern variable — see the next entry.

## With a float literal, `x = x * lit` puts the literal first — write `x *= lit`

First seen: `game/game/fielding/fielder_ai` (2026-09).

After switching to literals, MWCC emitted `fmuls f0, fConst, fX` (and loaded the constant before
the int->double bias) for `frames = (int)(frames * 1.3f) + 0x1e;` and `speed = speed * 1.3f;`,
where the target has `fmuls f0, fX, fConst`. Compound assignment reproduces the target exactly:
`frames *= 1.3f; frames += 0x1e;` (setThrowSpeedType2 93.78% -> 100%; 28 sites, none
regressed) and `speed *= 1.3f;` in initializeThrowAngle_Speed_Length. `(int)(1.3f * frames)` and
explicit casts compile identically to the original and do not help.

## Index the named `.bss` statics, never past the end of a neighbouring array

First seen: `game/game/fielding/fielder_ai` (2026-09).

Three functions wrote `lbl_3_bss_17F8[12 + i]` / `[16 + i]` / `[20 + i]`, reaching three separate
file-static arrays through a 1-element placeholder. Writing `throwStratToMakePlay[i]`,
`runningStratToMakePlay[i]`, `framesRunnerIsOutOfReach[i]` let MWCC pool the section base into a
callee-saved register exactly as the target does (`addi r30, bss@l` once, then
`addi rX, r30, 0x40; stwx`): +6 to +8 points each.

## A hand-unrolled scan is usually a loop MWCC unrolled

First seen: `game/game/fielding/fielder_ai`, `setRunnerChasingAfter` (77.33% -> 99.27%, 2026-09).

Signature: the same test repeated for fixed indices, a loop-invariant address hoisted before the
first copy (`slwi; addi rA, rI, 0xa8` then `lfsx f1, rBase, rA` in every copy), each copy ending
`li rResult, N; b end`, and a doubled `b end; b end` after the last. `for (i = 0; i < 4; i++) {
if (...) { result = i; break; } }` reproduced it. Related: a `do { ...; runner++; i++; } while (i < 4)`
loop that the target runs with `mtctr`/`bdnz` wanted a `for` (fn_3_A89D4), and the order of the
`for` increment clause (`runner++, i++`) is visible in the output.

## A `u8` field stored from the same register as neighbouring -1 stores is really `s8`

First seen: `game/game/fielding/fielder_ai`, `knockBallLoose` (2026-09).

The target stored `g_FieldingLogic.baseFielderIsOn` with `stb r6` where r6 already held -1 for
halfword stores; ours materialised a separate `li rX, 0xff` because the field was `u8` (4 bytes
too long). `fielder.c` already read it through `(s8)` casts. Retyping it `s8` took knockBallLoose
and fielder.c's handleBodyCheck2 to 100%. Locals copied from it must then be `s8` too (tagRelated
needed `s8 baseOn` with the casts dropped).

## Statement order is the strongest register lever; trace the target's data flow for bugs

First seen: `game/game/fielding/fielder_ai` (2026-09).

Greedy single-statement moves inside straight-line runs (only legal, dependency-preserving moves;
also splitting a declaration initializer into a statement placed later) fixed or improved over a
dozen functions here — e.g. moving `g_FieldingLogic.laser_2 = 0;` from first to last in a prologue
restored 4 bytes and the unit's whole `.data` jump table. Declaration order of float locals
occasionally matters too (estimatedThrowFramesBetweenTwoPoints reached 100% from it) though it was
a no-op in most functions. Separately, following one register in the target from its load to a
later `andi.` exposed a real bug: a test the source applied to `hexMovementsInEachBaseline1for2back4stop`
was on `hexBaserunnerTracker` (fielderAIOutfieldPlayAttemptInd 94.57% -> 99.64%).

## `-inline deferred` auto-inlining of in-file standalone functions is NOT uniform — measure both forms

First seen: `game/game/ball/ball_physics` (40 functions, all `return;` stubs at session
start, 2026-09). This **contradicts the blanket claim** in "When the target inlines an
in-file function it also keeps standalone, copy the body" above, which was written from
`runner.c` and generalised too far.

That entry says MWCC declines to inline a function that is also a real standalone symbol,
so the call survives and you must copy the body in. In `ball_physics.c` the opposite was
usually true: a plain call to a standalone in-file function got auto-inlined and matched
the target's inlined copy exactly. Measured, same unit, same compiler settings:

| caller / callee | call form | copied body |
|---|---|---|
| `ballCollisionLogic` / `foulBall` x6, `fn_3_9FA4` x2 | 99.314% | 99.314% (identical) |
| `calculateImplicationsOfTheHitTrajectory` / `fn_3_D9EC` (0x1E4 B) | 98.984% | 98.973% (identical) |
| `liveBallHitPhysics` / `updatePastHitBallCoords`, `adjustVeloByAirResistance` | 99.429% | 99.429% (identical) |
| `calculateImplicationsOfTheHitTrajectory` / `fn_3_9B74` (0x16C B) | **86.178%, 340 B short** | **98.424%, exact size** |

So it happens, but not predictably — and **callee size does not predict it**: the LARGER
`fn_3_D9EC` (0x1E4) was auto-inlined while the SMALLER `fn_3_9B74` (0x16C) stayed a real
`bl`. The cheap diagnostic is the function's BYTE SIZE: if the call form comes out
hundreds of bytes short of the target, the call survived and the body must be copied in.

Third case, distinct from both: the call form can compile to the RIGHT size and still
underperform. `ballCollisionLogic`'s six inlined `relatedToGroundRuleDouble` copies scored
98.741% as calls and 99.314% via a `static inline` helper — because the target's inlined
copies write `deadballLastLoc` BEFORE `deadBallReason = 3` while the standalone function
writes the reason first. A statement-order difference between the target's inlined copy and
the standalone function means the copy came from a *different* original source function;
match the copy, not the standalone.

Rule: always measure the call form first (it is one build and far cleaner source), and
only copy bodies in when the size or the score says the call survived.

## Verify every `void f(void)` prototype against the target asm before implementing

First seen: `game/game/ball/ball_physics` (2026-09). In a from-scratch file, dtk-derived
prototypes are guesses. SIX of this unit's 40 were wrong, and each would have capped its
function and every caller:

- `futureFrameForClosestBall` -> `int (f32, f32, f32*, int, int)`
- `fairOrFoulBall` -> `void (BALL_COLLISION_TYPE)`
- `handleBallBounceAndRoll` -> `void (f32*, int, u8*, BOOL)`
- `estimateWhereBallWillHitWall` -> `void (BOOL)`
- `liveBallHitPhysics` -> `void (int mode)`
- `estimateAndSetFutureCoords(int)`'s parameter is a 3-VALUED MODE selector, not a flag

The check is cheap and mechanical: read the function's first few instructions for a read of
`r3`-`r10` or `f1`-`f8` BEFORE any write to it, and read the call sites for argument setup.
A first instruction of `cmpwi r3, 0` or `mr rN, r3` is decisive. Three sibling headers
(`foul_detection.h`, `m_sound.h`, `star_swing_peach_daisy.h`) were also found to declare
`(void)` for functions that really take arguments — other units had already worked around
those with local `extern`s rather than fixing the header, so grep for an existing local
extern before trusting a header.

## MWCC does not fold a two-sided range test — write it as one unsigned subtract

First seen: `game/game/ball/ball_physics` (2026-09).

Where the target has `subi r0, rX, lo; cmplwi r0, n` (a single unsigned compare), source
written `x >= lo && x <= hi` does NOT produce it — MWCC emits two compares and two branches.
Write the fold explicitly: `(u32)(x - lo) <= n`, or `(u8)(x - lo) <= n` when the target has a
`clrlwi r0, r0, 24` after the `subi`. Confirmed on collision-kind range checks in
`ballCollisionLogic` and on the Yoshi/Birdo star check in
`classifyHitTrajectoryOrHitAnimRelated` (`(u8)(currentStarSwing - CAPTAIN_STAR_TYPE_YOSHI) > 1`).

Related, same file: a `switch` does NOT reproduce this either. The stadium floor-clamp in
`liveBallHitPhysics` scored 98.25% as a `switch` and 99.43% as an `if`/`||` chain using the
subtract form. And where a target tests an `s16` field with `extsh. r0, r3` before a chain of
`cmpwi`s, assign the field to an `s16` local and write an if-chain — a `switch` does not
produce the `extsh.`.

## Where the truncation sits tells you the local's declared width

First seen: `game/game/ball/ball_physics` (2026-09). A sharper form of the `clrlwi` entry at
the top of this file, for the specific case of a value returned by a call.

- Target has `clrlwi` at the ASSIGNMENT -> the local really is `u8`.
- Target has `mr rN, r3` at the assignment and `clrlwi` at EACH USE -> the local is `int`
  and the source casts `(u8)` at each use site.

Same shape for sign extension: an `int` local holding an `s16`-returning call's result emits
ONE `extsh`; an `s16` local emits an `extsh` at every use. Count them in the target and
declare accordingly. Both were worth ~1 point each in `classifyHitTrajectoryOrHitAnimRelated`.

## `s32 i` vs `int i` decides MWCC's vestigial fixed-trip loop guard

First seen: `game/game/ball/ball_physics` (2026-09). This closes an open question from the
`text_freeAllBlocks` entry above, which noted the guard (`li r0,0; cmpwi r0,0x1e; bgelr`)
without identifying what produces it.

Declaring the counter `s32` emits the guard; declaring it `int` omits it, with no other
source change. Worth 83.2% -> 85.5% on `setDefaultInMemBall`, and it also produced the
target's `li 0; cmpwi 10; bge` on a 10-trip loop in `setLiveBallVariablesAfterContact`. It
is NOT universal — `int` and `s32` tied on the inner loop of `estimateWhereBallWillHitWall`
— so measure rather than applying it blanket.

Second data point: `game/game/match_setup/versus_screens` (2026-09). Switching `int i` to `s32 i`
on the fixed-trip unrolled store loops restored the guard and fixed about seven functions in one
sweep. When a from-scratch file has many such loops, make this the first blanket change.

Third data point (2026-10-09): `at_bat_setup.c` reached 100% by using `s32`
for both counters and indexing the fielding-team field directly. A cached
team local hoisted its load before the guard and stayed at 85.91%; direct
field reads gave 100%. `ARRAY_COUNT` with an `s32` cast removed the guards
again (66.01%); named integer-literal trip counts preserve them. The unused
`header_rep_data.h` include emitted an unowned 80-byte constant table and
failed the linked checksum; removing it preserved 100% and passed all four
checksums.

The same counter change in `stadium_draw.c`'s `copyExtraStadiumEntries`
restored both zero-trip copy blocks that prior passes could not reproduce:
`updateStadiumFileHeaders` 70.68% -> 84.96%, with all siblings unchanged.
The helper count remains `int`; only its loop counter changes to `s32`.

## A search loop's `mtctr` value distinguishes two source shapes

First seen: `game/game/ball/ball_physics` (2026-09).

For a strided scan with an early exit, these two forms compile differently and the target's
`mtctr` immediate tells you which one the original used:
- `for (i = 0; i < N; i += step) { ...; if (cond) break; }` -> `mtctr = trip/5` (5x unrolled)
- `while (i < N) { ...; if (cond) { ...; i += step; } else break; }` -> `mtctr = trip`

When the target shows `mtctr 30` with five unrolled bodies, it is the `while` form. Fixing
this in `calculateImplicationsOfTheHitTrajectory`'s throw-estimate loop was the difference
between a counter of 6 and the target's 30.

## A bare discarded `dolsqrtf2(expr);` statement reproduces a dead `fcmpo`

First seen: `game/game/ball/ball_physics`, `ballCollisionLogic` (2026-09). A concrete
instance of "Genuinely dead code is reproducible" above.

The target computed `vx*vx + vz*vz`, ran an `fcmpo` against 0.0 that nothing consumed, then
reloaded both operands from memory and recomputed the sum for the real sqrt. A statement
that calls `dolsqrtf2(vx*vx + vz*vz);` and discards the result reproduces all of it exactly,
including the reload. The `if (sum <= 0) {}` empty-if form does NOT — MWCC folds it away.

Two related `dolsqrtf2` levers from the same file:
- Never put the argument or the result in an `f32` local first; that forces an extra `frsp`.
  Storing straight to the destination field took `fn_3_D9EC` 96.24% -> 99.34%. (Exception:
  do use a local where the target genuinely keeps the value live across a call.)
- A target `fcmpo f4, 0.0; bge` BEFORE the sqrt body means the caller's own sign check:
  `if (x < 0.0f) return 0.0f;`.

## Adding a `dolsqrtf2` use renumbers the whole TU's anonymous rodata pool

First seen: `game/game/ball/ball_physics` (2026-09). A measurement-hygiene warning.

Each new inlined `dolsqrtf2` adds pooled constants, shifting MWCC's `@NNN` numbering for
every later anonymous constant in the translation unit. Already-matched functions then show
small score DROPS (here 8 functions fell by 0.1-0.4 points at once) whose instruction text is
byte-identical once `@N` names and branch addresses are normalised — the diff is purely
relocation NAMES.

On a from-scratch file this will happen repeatedly as functions land. Before investigating an
apparent regression in a function you did not touch, normalise the pool names and re-compare;
and never compare a mid-session score against a score from before other functions were added.

## Float `>=` emits `fcmpo; cror; bne` — invert it to get the target's plain branch

First seen: `game/game/ball/ball_physics`, `fn_3_BC54` (2026-09).

`a >= b` on floats compiles to `fcmpo` plus a `cror` to merge the greater-than and equal
condition bits. Targets frequently have a plain `bge`/`blt` instead, which comes from writing
`!(a < b)`. Rewriting `offset >= -5.0f && vel >= 0.05f` as
`!(offset < -5.0f) && !(vel < 0.05f)` was the last diff before 100%, and the same swap fixed
`processLandedBallBouncing` and `processBallInAir_Landed`.

Two smaller float idioms measured in the same file: `ABS(a - b)` gives different (and often
correct) float register numbering from `d = a - b; if (d < 0) d = -d;`; and `x *= 0.5f` and
`x = x * 0.5f` compile to different operand orders, with `*=` matching the target.

## `extern const f32 lbl_N_rodata_XXXX` only works for a SINGLE-USE constant

First seen: `game/game/ball/ball_physics` (2026-09). An important limit on the
"Naming a target's local rodata float label" entry above, which presents the trick as
unconditionally free.

A named `extern const f32` gets CSE'd into ONE load. A repeated float literal is
re-materialised at each use, which is what targets usually do. So the swap only helps where
the constant is used ONCE: it was worth 99.655% -> 100% on `setValsForPlantCatches` (single
use) but COST 5 points on `fn_3_9B74` and 3 on `fn_3_D9EC` (repeated use).

Worse, the swap is not local. Removing an anonymous literal from one function shifts pool
matching in OTHER functions of the same TU: on `adjustVeloByAirResistance` it took that one
function 98.83% -> 99.5% while dropping unit `.text` 13.2879 -> 13.2859 and `.rodata`
58.06 -> 54.92 by perturbing three siblings, and in `fairOrFoulBall` it changed float
REGISTER assignment in a loop. Always measure the unit's section totals, never one function's
score.

## Index an array past its declared bound rather than restructuring a shared header

First seen: `game/game/ball/ball_physics` (2026-09).

`InMemBallType` declares `VecXYZ pastCoordinates[27]` at 0x3C and a separate `physicsSubstruct`
at 0x180 whose first member runs to 0x30C — but four functions write the span 0x3C-0x30C as one
contiguous 60-entry array, so the original source evidently had one array there. Rather than
restructure a header included by ten units, the code indexes `g_Ball.pastCoordinates[i]` for
`i` up to 59. It compiles clean and matches.

Critically, the obvious tidy alternative is WORSE: a base-pointer local
(`VecXYZ* coords = g_Ball.pastCoordinates;`) measured 4-10 points below plain array indexing
(`updatePastHitBallCoords` 98.883% vs 100%; `fn_3_F9F8` 85.491% vs 94.806%) because it
materialises an `addi rX, rY, 0x3c` rebase that the target folds into each displacement.
Document the real extent in the checkpoint instead of encoding a guess in the struct.

## A ctr loop's wrong base displacement is an index-OFFSET problem, not a body problem

First seen: `game/game/ball/ball_physics`, `updatePastHitBallCoords` (2026-09).

Two algebraically identical loops produce different base displacements.
`for (i = 9; i >= 1; i--)` with `arr[i+3] = arr[i+2]` gave the target's base 0x6c;
`for (i = 12; i > 3; i--)` with `arr[i] = arr[i-1]` gave 0x84. Hand-unrolling the three-element
body scored 43%. If a `ctr` loop matches except for its base displacement, re-express the index
with a different offset before touching the body.

Exact bounds matter too: in `fielding_setHeldBallOffset`, `for (i = 3; i >= 2; i--)` plus an
explicit trailing `[1] = [0]` scored 100% where the tidier `for (i = 3; i >= 1; i--)` scored
97.4%.

## A reload-after-store of the same field means an unrolled loop

First seen: `game/game/ball/ball_physics`, `warioWaluStarHit` (2026-09).

Where the target stores a field and immediately RELOADS it instead of reusing the register it
just stored from, the source was a fixed-trip loop the compiler unrolled — the reload is the
next iteration's load, not a CSE failure. Writing the same work as straight-line statements
never reproduces it. Expressing a two-element drag update as `for (i = 0; i < 2; i++)` over
`[13+i]`/`[1+i]` took the function 86.1% -> 99.03%.

## A wrong enumerator is invisible in source review and shows as one `cmpwi` immediate

First seen: `game/game/ball/ball_physics` (2026-09).

A named constant is not self-validating. A draft used `BALL_COLLISION_TYPE_CHOMP_HAZARD`
(0xB) where the target's immediate was 3 (`BALL_COLLISION_TYPE_STRUCTURE`); everything else
matched, so the whole defect surfaced as a single wrong `cmpwi` immediate. When using an enum
in place of a literal, check the enumerator's NUMERIC VALUE against the `.s` immediate, not
just that the name reads plausibly.

## A target can contain BOTH a standalone function and a hand-inlined copy of it

First seen: `game/game/pitching/pitcher`, `pitchInAirFunction` (2026-09).

This settles the tension between "When the target inlines an in-file function it also keeps
standalone, copy the body" (from `runner`) and "`-inline deferred` auto-inlining of in-file
standalone functions is NOT uniform — measure both forms" (from `ball_physics`).
`pitchInAirFunction` (5408 B target) contains the body of `fn_3_70B94` (864 B), which also
exists as a real standalone symbol. All four combinations were measured:

- hand-written inline copy + `#pragma dont_inline` on a different callee: 97.62%, 5412 B (kept)
- hand-written inline copy, no pragma: 87.36%, 5832 B
- real call to `fn_3_70B94` + pragma: 82.34%, 4596 B (about 810 B SHORT: MWCC kept the `bl`
  where the target had the body inline)
- real call, no pragma: 75.19%, 4932 B, and `fn_3_70B94` itself dropped to 84.10%

Byte size is the decisive diagnostic, and it points both ways. Hundreds of bytes SHORT means
the call survived where the target inlined (copy the body in). Hundreds of bytes LONG means we
inlined where the target called. Measure the call form first because it is cleaner source, but
let the size, not a prior expectation, decide.

## The `#pragma dont_inline` open question recurs, with numbers

First seen: `game/game/pitching/pitcher`, `estimateXAndFrameAtBatterZ` (2026-09).

Second confirmed instance of the OPEN QUESTION at the end of the `runner` entry (MWCC inlines a
fully-implemented small callee where the target keeps real `bl` calls, so a
`#pragma dont_inline` bracket is needed as scaffolding). `estimateXAndFrameAtBatterZ` (208 B)
is called 3x from `pitchInAirFunction`; MWCC auto-inlines it at all three sites while the
target keeps three `bl`s. The pragma is worth 87.36% -> 97.62% and 424 bytes. Moving the
definition below the caller does NOT stop the inlining (87.7%, reverted).

This case is sharper than `runner`'s: in the SAME function, seven OTHER in-file helpers
(`fn_3_709B4`, `fn_3_70AEC`, `fn_3_70838`, `fn_3_70280`, `fn_3_706B8`, `fn_3_6FFC4`,
`pitchCurve`) were auto-inlined exactly as the target does, with exact sizes and no pragma. So
the inlining decision differs between callees within one caller, and the distinguishing source
property is still unidentified. Still open; the pragma remains logged cleanup debt.

## A dense `switch` synthesizes the `.data` jump table, and it is worth a whole section

First seen: `game/game/pitching/pitcher`, `atBat_Pitcher` (2026-09).

`atBat_Pitcher` dispatches on a `u8` state field; the target does `cmplwi 7; bgt` then
`lwzx r0,r3,r0; mtctr; bctr` against `jumptable_3_data_8088` (0x20, 8 entries). Writing it as
a plain `switch` over the 8 dense enumerators made MWCC emit the table with no extra work,
taking the unit's `.data` from 0% to 100% in one edit, and the function itself to 100%. A
`.data` section that is nothing but a `jumptable_*` symbol needs no C declaration — find the
dispatching function and write the `switch`. This confirms a prediction recorded but not
verified in the `ball_physics` checkpoint.

## Check for duplicated bodies within a file before writing one from scratch

First seen: `game/game/pitching/pitcher` (2026-09).

`pitcher.c` had four: `handleHPBORRunnerAdvance` is byte-identical to `fn_3_7372C`;
`fn_3_6FB98` begins with the whole body of `fn_3_6FA28`; `fn_3_6FFC4` begins with the whole
body of `fn_3_6FDA0`; and `atBat_Pitcher`'s hit-by-pitch switch arm is another copy of
`fn_3_6FA28`'s body. Each copy was free once the original matched. On a from-scratch file,
before writing a large function, grep the already-matched functions for its opening
instruction sequence — a duplicate body converts a large unknown into a paste. Ordering the
work smallest-first surfaces the originals before the functions that embed them.

## `x == a || x == b || x == c` gets folded into a range check

First seen: `game/game/pitching/pitcher`, `pitchingWindUpFunction` (2026-09).

Mirror image of "MWCC does not fold a two-sided range test — write it as one unsigned
subtract". On consecutive values, MWCC merges an equality chain into a single range compare
the target does not have. Rewriting as the negated conjunction with an `else` —
`if (x != a && x != b && x != c) { else-arm } else { shared-arm }` — reproduced the target's
`beq shared; beq shared; fallthrough` layout. The rule is symmetric: the source form that
produces a folded range test and the one that produces separate compares are BOTH reachable,
and which one you need is read off the target, never assumed.

## `extern const f32 lbl_N_rodata_XXXX` is not restricted to single-use constants; measure it per function

First seen: `game/game/pitching/pitcher`, `fn_3_70AEC` and `fn_3_6F6CC` (2026-09).

Refines "`extern const f32 lbl_N_rodata_XXXX` only works for a SINGLE-USE constant" (from
`ball_physics`), which states the limit too absolutely. In `fn_3_70AEC`, replacing three
literals (`0.5f`, `0.0f`, `10000.0f`) with `lbl_3_rodata_1250`/`1258`/`12A8` was worth
78.14% -> 99.76% even though those labels are used repeatedly across the translation unit. In
`fn_3_6F6CC` in the same file the same swap HURT (99.68% with the literal, versus
99.35/99.52/97.58 for three extern variants). Both directions occur within one file, so treat
it as a cheap two-build experiment per function rather than a rule with a precondition.

## Separate `if (...) return;` statements are not interchangeable with a merged `||` chain

First seen: `game/game/pitching/pitcher`, `waitingForPitch` (2026-09).

Three consecutive guard tests on the same array written as one `if (a || b || c) return;`
emitted an extra `b` versus three separate `if (...) return;` statements, which matched (the
function reached 100%). Related lever from the same function: moving a single
`controls = &g_Controls[...]` assignment ahead of an unrelated three-component position copy
was worth 91.4% -> 99.51%, because the source order of a global's first use decides which
callee-saved register its base gets. Cross-reference "Textual statement position as a
register-allocation priority lever".

## Prototype audit on a from-scratch file, second data point

First seen: `game/game/pitching/pitcher` (2026-09).

Reinforces "Verify every `void f(void)` prototype against the target asm before implementing"
(from `ball_physics`, where 6 of 40 were wrong). In `pitcher.c`, 8 of 41 dtk-derived
prototypes were wrong: `fn_3_6F6CC`, `waitingForPitch_checkForPickoffs` and `loadPitcherActor`
return `BOOL`; `fn_3_70680` is `BOOL(f32)`; `fn_3_706B8` is `void(int)`;
`estimateXAndFrameAtBatterZ` is `int(f32*, f32, int)`;
`pitcherAITransitionFromPrePitchToWindup` is `void(u8)`; `resetPitcherValuesBetweenBatters`
is `void(int)`.

Separately, four functions declared `void(void)` in SHARED headers really take arguments and/or
return values (`loadCharacterAnimation`, `setPitcherStatsToInMemPitcher`,
`aiPitchCurveDirection`, `LERPToNewRange_Float`); each was worked around with a local `extern`
in the .c rather than editing the shared header, following existing precedent. The cost of that
precedent: `include/game/pitching/pitcher_ai.h` can no longer be `#include`d from `pitcher.c`
at all, because its `aiPitchCurveDirection` declaration now conflicts with the corrected local
one. Fixing these at the header eventually is cheaper than accumulating conflicting local
externs.

## Dead-code standalone duplicates are the cheapest route into a from-scratch file's big functions

First seen: `game/game/batting/batter_ai` (14 functions, all `return;` stubs at session start,
2026-09). Sharpens "Check for duplicated bodies within a file before writing one from scratch"
(from `pitcher`), which describes duplicated bodies but not this specific, highly exploitable shape.

FIVE of this unit's 14 functions had ZERO callers anywhere in the binary, and each one was a
standalone copy of a body that also appears inlined inside a much larger function in the same unit:

| dead standalone | body also inlined into |
|---|---|
| fn_3_1E4B8 (620 B) | batterAIRNGValueSetting (2108 B) - steal decision |
| batterAIBuntDecision (208 B) | batterAIControlled (444 B) - bunt decision |
| fn_3_1F1CC (388 B) | batterAIMoveBatter (1012 B) - pre-pitch box positioning |
| batterAIGuessPitchLocation (296 B) | batterTrackBallInBox (1312 B) - stage 1 |
| batterAIGuessPitchType (156 B) | batterAIRNGValueSetting - pitch guess |

Implementing the five SMALL dead copies first converted four of the file's five largest functions
from open-ended writes into near-pastes; three of those four then matched 100% on the first or
second attempt. The tell for this shape is a function that dtk named `fn_*`, that a repo-wide `bl`
scan finds no caller for, and whose Ghidra decompilation reads like a fragment of a bigger routine.
Run that caller scan across the whole file BEFORE picking a work order - it is one grep and it can
reorder the entire session.

## Call form vs. copied body is decided PER CALL SITE, and the BOOL return idiom is the tell

First seen: `game/game/batting/batter_ai` (2026-09). This settles the remaining ambiguity between the
`runner` entry ("copy the body"), the `ball_physics` entry ("measure both") and the `pitcher` entry
("byte size decides"): the decision is not per-file and not even per-function, but per call site.

All measured in ONE unit, same compiler settings:
- `batterTrackBallInBox` calling `batterAIGuessPitchLocation()`, and `batterAIMoveBatter` calling `fn_3_1F1CC()`:
  plain call form, auto-inlined by MWCC, EXACT size, **100%** each. No body copy needed.
- `batterAIControlled` calling `batterAIBuntDecision()`: call form **96.58% and 8 bytes SHORT**; the same body
  copied in reached **100%**.
- `batterAIRNGValueSetting` contains TWO inlined bodies and wanted a DIFFERENT form for each: the
  steal block scored 97.63% as a call and **97.79%** copied in, while the pitch-guess block was
  size-exact with zero diffs in that region as a plain call and needed no copy.

The mechanism behind the `batterAIControlled` case is worth knowing because it is invisible in a
size check alone: MWCC's inlined expansion of `return batterAI_buntForPractice() != 0;` emits the
`neg/or/srwi` (`!!x`) idiom, where the target had `cmpwi/beq/li 1/li 0`. Writing the copied body as
`if (f() != 0) v = 1; else v = 0;` reproduced the target exactly. So when the call form is only a
handful of bytes off rather than hundreds, look at the BOOLEAN IDIOM at the join, not at the
inlining decision.

Rule: measure the call form first (it is cleaner source and it won twice here), but re-measure it
independently at every site, including two sites inside one function.

## BOOL return idioms map one-to-one onto source expressions

First seen: `game/game/batting/batter_ai` (2026-09). Extends the `bool` vs `BOOL` entry at the top of
this file, which covers the declared type but not the returned EXPRESSION.

Three distinct PPC idioms, each produced by exactly one source shape:
- `neg r0,r3; or r0,r0,r3; srwi r3,r0,31`      <= `return x != 0;`
- xor / `srawi` / `subf` / `srwi` signed form  <= `return a < b;` (a relational returned directly)
- `cmpwi rX,0; beq; li rN,1; ... li rN,0`      <= `if (cond) v = 1; else v = 0;`

Neither `return (BOOL)x;` nor `if (x) return 1; else return 0;` produces the first form. Reading the
idiom off the target's last few instructions before `blr` tells you which source shape to write, and
it also identifies a wrong prototype: in this unit 3 of 14 dtk-derived `void f(void)` guesses were
really `BOOL f(void)`, and ALL THREE were detected from the `!!x` idiom before the `blr` rather than
from any argument-register read. A prototype audit should look at RETURN paths, not just arguments.

## Declaration order of two float locals can close a float-register permutation by itself

First seen: `game/game/batting/batter_ai`, `trackLastPitchInfo2` (2026-09). The float analogue of
"Textual statement position as a register-allocation priority lever" and of the `0x10`-stride vector
locals entry, both of which cover stack slots and statement position rather than FPR numbering.

The function was byte-exact and at 98.87%, with its remaining diff being purely permuted float
registers in one block (target x=f2, left=f3, step=f0; ours x=f3, left=f2). Declaring the two float
locals in the order `f32 step; f32 edge;` - changing nothing else at all - took it to **100%**.

If a function is at exact size and its only residual is float registers appearing in a different
order than the target's, sweep the declaration order of the float locals before trying anything
structural. It is one build per permutation and there are usually only a handful.

## MWCC reassociates a three-term sum, and the WRITTEN order picks the association

First seen: `game/game/batting/batter_ai` (2026-09).

Three algebraically identical ways of writing one index computation, measured on
`batterAIFrameToSwingAndStickInput`: `idx + desired - 4` scored 98.09%, `desired - 4 + idx` 98.69%,
and `idx - 4 + desired` 98.72% - the last being the only one that emits the target's add-then-subtract
order. The same lever moved `batterAISwingInd` from 98.28% (`arr[..] + frames - c`) to 98.61%
(`frames + arr[..] - c`), while a third association scored 93.35%.

Separately, the COMPOUND form is not free: `frameToStartSwing -= 4` emitted an extra store and scored
94.65% where `x = x - 4` did not. And a chained store `a = b = expr;` is what reproduces a target that
stores one computed value into two fields in a specific order.

When a function is size-exact and the diff sits on an index or offset computation, permute the written
association of the sum before doubting the surrounding logic.

## Never let a scripted replace touch a source file mid-grind

First seen: `game/game/batting/batter_ai` (2026-09). A process note, in the spirit of
"Re-measure a checkpoint's 'closed' claims before building on them".

A `sed`-style scripted edit was used to swap one function body in a 14-function from-scratch file. Its
match string also occurred earlier in the file, so it silently deleted most of an already-100% function
plus the head of another, and the damage was only caught by the next diff. Recovery was possible solely
because a private scratchpad backup happened to exist - the tree held hours of uncommitted work, so
`git checkout` would have destroyed far more than it restored.

Two rules that cost nothing: make every edit a context-anchored single-site edit rather than a pattern
replace, and treat a worker's verbatim paste of any function that reaches 100% as the real backup of
uncommitted work. In a from-scratch file, many functions share near-identical statement sequences by
construction, so "this string is surely unique" is exactly the assumption that fails.

## Bitwise `|` between comparisons, not `||`, when the target computes them as values

First seen: `game/game/stadium/stadium_framework`, `getStadiumHazardTriangles` (2026-09).

An if/else-if chain written with `||` scored 79.02%. The target was not branching between
the two tests at all - it evaluated each comparison to 0/1 and OR'd the results, then made
one branch. Rewriting the conditions as `(x == 11) | (x == 12)` and
`(a >= K) | (x == 11) | (x == 12)` took the function to **100%** with no other change.
`||` is a short-circuiting control-flow operator and compiles to one branch per term;
bitwise `|` forces both operands to be evaluated as values. When the target shows the
comparison results being materialised (`cror`, or a run of compares with no intervening
branch) before a single branch, `|` is the operator the original used. This is the
counterpart to the existing entry "`x == a || x == b || x == c` gets folded into a range
check" - check for the range fold first, then for this.

## Sweep local declaration order mechanically; it is worth whole percentage points

First seen: `game/game/fielding/fielder`; sharpened on `game/game/stadium/stadium_framework`
(2026-09), which generalises the narrower existing entry "Declaration order of two float
locals can close a float-register permutation by itself".

It is not only float pairs, and it is not only the last 0.1%. In ONE file, declaration
order alone was the final lever on five separate functions:

| function | change | gain |
|---|---|---|
| `transformVectorsUpdateBoundingBox` | declare `int count` before the pointer `p` | 99.19 -> **100** |
| `fn_3_B8184` | declare `world` before `local` (stack 0x8 / 0x38) | 99.73 -> 99.84 |
| `fn_3_B8298` | permutation sweep of six locals | 98.95 -> 99.26 |
| `fn_3_B867C` | 200-order sweep | 88.79 -> 96.21 |
| `fn_3_B8C08` | move `Vec v` into the block that uses it | 99.30 -> 99.34 |

Two practical points. Declaration order sets both stack slot assignment and, indirectly,
register allocation, so it can move a score that looks like a pure register problem. And
because the search space is factorial, drive it from a script that rewrites the
declaration block, rebuilds and records the score, rather than by hand - a 24-order sweep
is cheap and a hand sweep of six locals is not.

## A bitfield matches `extrwi` where an explicit mask emits `rlwinm`

First seen: `game/game/stadium/stadium_framework`, `fn_3_B8298` (2026-09).

A flag byte tested with `obj->flags & 0x80` compiled to `rlwinm`, but the target had
`extrwi`. Declaring the field as a bitfield instead - `u8 hasShadow : 1;` as the first
member of the byte - produced `extrwi` and took the function 99.26% -> 99.89%. The same
byte later yielded six more single-bit fields in the same struct, all confirmed by
`extrwi` on the same `lbz`. So `extrwi` on a byte load is positive evidence that the
original declared a bitfield, not that it masked by hand. Note this says nothing about
whether the bits are booleans - see the boolean-evidence rules; name them only from use.

## A `clrlwi` the TARGET emits on a parameter proves the parameter is WIDE

First seen: `game/game/stadium/stadium_framework`, `fn_3_B9534` (2026-09).

The function takes a texture width and height, so `u16` looked obviously right. It is not:
the target truncates them itself with `clrlwi` at the point of use, and a compiler only
emits that if the incoming value is NOT already narrow. Declaring them `int` scored
99.67%; `u16` would have had the truncation already done in the prologue and could never
match. This is the parameter-side mirror of the existing entry "Where the truncation sits
tells you the local's declared width": a truncation at the USE site means the declaration
is wide, and a truncation absent at the use site means it is narrow.

## A `.data` array in our range must be DEFINED with real initialisers, not externed

First seen: `game/game/stadium/stadium_framework` (2026-09). Companion to "A dense
`switch` synthesizes the `.data` jump table".

This unit's whole `.data` was `lbl_3_data_11178` (0x14 = five floats) plus
`jumptable_3_data_1118C` (0x1C). The jump table came free from writing the dispatcher as a
plain `switch`. The five floats did NOT: the first implementation declared them
`extern f32 lbl_3_data_11178[]` and used them, which compiles and links fine but emits
nothing into our `.data`, leaving the section at 0%. Reading the five word values out of
the target's `.data` and writing a real definition
(`f32 lbl_3_data_11178[5] = {18.0f, 90.0f, 162.0f, 234.0f, 306.0f};`) took `.data` to 100%.
The rule: check the unit's `.data`/`.rodata` address range in `splits.txt` first - a symbol
INSIDE our range must be defined by us, and only a symbol outside it should be `extern`.
Note it must not be `const`, or it lands in `.rodata`.

## Reloading a global per derived local can beat sharing one temp

First seen: `game/game/stadium/stadium_framework`, `fn_3_B867C` (2026-09). This is the
counter-case to the usual advice about eliminating redundant temporaries.

Three locals were all initialised from `stadiumObjectCollision.objectCount`. Computing it
once into a temp and deriving the other two looked like the obvious source shape and
scored 95.89% at best. Writing the load out separately for each of the three - so the
global is re-read three times - was the single biggest gain on the function. MWCC's
allocator assigns a different register lifetime to each independent load, and collapsing
them to one temp creates a long live range the target does not have. When several locals
come from the same global and the registers are rotated, try the redundant form.

## Copy a `Vec` per component when the target uses `lfs`/`stfs`

First seen: `game/game/stadium/stadium_framework`, `loadStadiumObjectVisuals` (2026-09).
Narrows the existing entry "Whole-struct assignment of a float vector lowers to integer
word copies".

That entry says a whole-struct `Vec` assignment becomes integer `lwz`/`stw` word copies.
The corollary is the diagnostic: if the target copies a `Vec` with three `lfs`/`stfs`
pairs instead, it was NOT a struct assignment in the original - write the three component
assignments out. Getting this right (together with declaration order and modifying a
`GXColor`'s alpha in place rather than rebuilding the struct) moved this function from
94.2% to 99.6%.

Third data point: `fn_3_F4BA0`/`fn_3_F4D00` in `game/game/stadium/sta_c5` went
90.58% -> 99.77% from this change alone (2026-09).

## Load both float operands into named locals before comparing them

First seen: `game/game/stadium/stadium_framework`, `fn_3_B8658` (2026-09), a 36-byte qsort
comparator.

`if (*a < *b) return -1; return *a > *b;` scored 97.78% with `f0` and `f1` swapped
relative to the target. Introducing `f32 x = *a; f32 y = *b;` and comparing the locals
took it to **100%**. Dereferencing inside the comparison lets MWCC choose the load order;
naming the operands first fixes it. Cheap to try on any small float-comparison function
whose only defect is an FPR permutation.

## `dolsqrtf2`'s local statics add 16 bytes of `.rodata`, and `SQRT2_LINKAGE` alone is not the whole fix

First seen: `game/game/stadium/stadium_framework` (2026-09). Extends the existing
`SQRT2_LINKAGE` practice in `src/game/batting/batter.c` with the measurement.

Any unit that includes `include/game/UnknownHomes_Game.h` picks up the `static inline
dolsqrtf2` in `include/stl/math.h`, which emits two 8-byte local statics into `.rodata`,
`_half$localstatic3$dolsqrtf2` and `_three$localstatic4$dolsqrtf2`. The target has
neither, so the unit's `.rodata` is 16 bytes too large. `#define SQRT2_LINKAGE static`
before the include removes them, and that is the right fix.

The measurement worth recording is that it can LOWER the score on its own. On this unit it
took `.rodata` from 192 bytes to exactly the target's 176, but the match% fell from 63.74%
to 59.77%, because removing 16 bytes re-aligns everything after it and exposes a second,
independent defect: float-vs-double width. The target had 4-byte floats at
`lbl_3_rodata_1DC4`..`1DDC` and 8-byte doubles at `1DE0` and `1DF8`; ours had an 8-byte
double where the target had floats. So treat the two as ONE combined fix - apply
`SQRT2_LINKAGE` and audit every float literal's type in the same pass. Applying it alone
and reading the lower number as "this made it worse" is the trap; the size going exactly
right is the signal that the change was correct.

Second data point, `game/game/ball/foul_detection` (2026-09): without the define, the two
statics sat at the very front of `.rodata`, ahead of `repHeaderData`, so every later literal
was 0x10 off. Three otherwise instruction-identical functions scored 98.9-99.3% on their
float relocs alone; the define took all three and `.rodata` to 100% with no other change.

## Dead standalone copies, second data point: five clusters in one 88-function file

First seen: `game/game/stadium/sta_c2` (88 functions, all `return;` stubs at session
start, 2026-09). Sharpens "Dead-code standalone duplicates are the cheapest route into a
from-scratch file's big functions" (from `batter_ai`) with a much larger sample.

Writing the small zero-caller functions first paid off five separate times in one file, and in
each case the consumer hit its EXACT target byte size on the first build:
`CC1D4`/`CC354`/`CC438`/`mPalaceObjHandling` -> `maybeChainChompSprintCTRLRelated`, `CB8A8`, `CBC18`;
`CDB48`+`CDD90` -> `CDFA4`; `CED40` -> `CEE5C` -> `CEFA8`;
`D278C`/`D36B0`/`someCTRLButNotCalled2` -> `palaceChainChompControl`;
`D62F0` -> `D6514` -> `loadWarioPalace`. Build the in-file call graph from the `bl` targets and
work leaf-to-root; the order is almost free to derive and it decided the whole session.

## Auto-inlining by plain call reached 696 bytes here; size, not expectation, decides

First seen: `game/game/stadium/sta_c2` (2026-09). Third data point for
"`-inline deferred` auto-inlining of in-file standalone functions is NOT uniform" and "A target
can contain BOTH a standalone function and a hand-inlined copy of it".

In this unit the plain CALL form reproduced the target's inlining for nearly every embedded
helper: `fn_3_D6514` (696 B, including `D62F0`) inside `loadWarioPalace`, `fn_3_D36B0` (464 B) and
`someCTRLButNotCalled`/`2` (348/540 B) inside `palaceChainChompControl`, `fn_3_D511C` and
`fn_3_D1110` inside `loadWarioPalace` (bl count matched 98 = 98). The one exception was
`fn_3_D278C` (640 B) inside `palaceChainChompControl`, whose `bl` survived and whose body had
to be pasted into the case. Try the plain call first on every embedded helper regardless of
size, and paste only where the `bl` demonstrably survives.

Fourth data point, `game/game/stadium/sta_c5` (2026-09): across five consecutive
batches the plain CALL form reproduced the target's inlining in EVERY case, and each consumer
hit its exact target byte size on the first build — `fn_3_F2724` (532 B) into
`dkBarrelAdvanceMotion`; `fn_3_F22FC`/`fn_3_F1750`/`fn_3_F18A4` into `handleDKJungleBarrel`;
`fn_3_F4DAC` (528 B) and `fn_3_F4C4C` into `handleBarrelFiring`; `fn_3_F5E78` (x2) and
`fn_3_F5F4C` into `processJungleObjectCollisions`; `fn_3_F6A94` and `maybeBarrelCTRLRel` into
`updateDKJungleControl`; `fn_3_F3BB0`, `fn_3_F5C30` (584 B), `maybeGharialCTRLRel`, `initBinomialTable`
and `fn_3_EECF4` into `loadDKJungle`. Only one case in the whole file needed a hand-pasted body
(`fn_3_F3EFC`/`fn_3_F2FFC` inside `dkBarrelLaunch`, and only because the helpers name a `.bss`
array the caller reaches through a different base). Write the plain call first, always.

## An inlined helper must take the caller's EXACT view type

First seen: `game/game/stadium/sta_c2`, `chomp_attack` (2026-09).

`chomp_attack` works on a `PalaceChompObj*` view; its helpers `fn_3_D255C`/`fn_3_D24E8` took
`StadiumObject*`. Inlined, the mismatched pointer type made the loop hoist `&obj->pos` into an
extra callee-saved register (93.06% first draft; a hand-pasted nested block only reached
96.06%). Retyping the two helpers to `PalaceChompObj*` and going back to plain calls gave
96.60% and the exact size, roughly +3.5 points. If an inlined body shows one register too many
holding a derived address, check the helper's parameter type against the caller's before
restructuring anything.

## Do not give a `Vec`/`Mtx` local an initialiser where the target copies it late

First seen: `game/game/stadium/sta_c2` (2026-09). Cross-reference "Textual
statement position as a register-allocation priority lever".

MWCC hoists an initialised local's copy to function start; the target performs the copy at the
tail, at the point of use. Declaring the locals uninitialised and ASSIGNING at the point of use
(`Vec axis; ... axis = const_axis;`) was worth +20 to +27 points on four consecutive functions:
`fn_3_D36B0` 62.6 -> 99.35, `fn_3_D278C` 72.5 -> 99.19, `chompState0` 65.5 -> 99.24,
`chompState1_awake` 78.5 -> 93.2. The signature is a block of `lfs`/`stfs` copies at the top of
ours that sit near the end of the target.

## A constant loop bound is folded away; round-trip it through a struct field

First seen: `game/game/stadium/sta_c2`, `fn_3_CC438` (2026-09).

`int iterations = 8; dt = 1.0f / iterations;` is constant-folded, so the target's
int-to-float conversion sequence (`xoris`/`lfd`/`fsub` against the bias constant) disappears.
Storing the count into a struct field and reading it back
(`params->solverIterations = 8; dt = 1.0f / params->solverIterations;`, in an invented static
helper `palaceInitChainParams`) reproduces it: 72.9% -> 97.78% on `CC438`, and the same fix
propagated to two callers. The signature is a target with a conversion where ours has a
literal.

## Write a constant-first float comparison when the target has `fcmpo const,val; cror gt,eq`

First seen: `game/game/stadium/sta_c2`, `fn_3_D278C` (2026-09). Sharpens "Float
`>=` emits `fcmpo; cror; bne`".

`5.0f >= PSVECMag(&d)` reproduces `fcmpo 5.0,mag; cror gt,eq`; the reversed spelling
`PSVECMag(&d) <= 5.0f` does not. That entry inverts `>=` to reach the target's plain branch; this
one is the opposite case, where the target keeps the `cror` form and the constant simply has to
be the left operand.

## Chained assignment and compound `+=` on struct float fields each score on their own

First seen: `game/game/stadium/sta_c2` (2026-09).

`a->x = a->y = expr;` instead of two statements took `palaceHazeTextureMaybe` 92.74 -> 99.28.
`p->sizeA += 0.38` instead of `p->sizeA = p->sizeA + 0.38` was worth about +4.5 points twice
(`fn_3_CED40` 95.00 -> 99.44, `fn_3_CEE5C` 94.70 -> 99.28). When a target shows a single value
stored twice with no compute between, or a float-field update that keeps the field as the left
operand of the add, try these before anything structural.

## `.bss` gap symbols that dtk leaves unnamed may be real objects, not padding

First seen: `game/game/stadium/sta_c2` (2026-09). Extends "dtk `.bss`/`.data`
symbol sizes are gap-derived".

Two bytes declared as `pad_A028`/`pad_A029` during `.bss` setup turned out to be the ring
objects' base index and count, discovered only when the last and largest function,
`loadWarioPalace`, was written (the bytes at `0xA026`..`0xA02D` are all base/count pairs). An
unreferenced `pad_` static is a hint that an unwritten function uses it; check the largest
remaining function's `stb rX, off(r30)` offsets before naming pads.

## Known unsolved: float equality as `fcmpu; mfcr; extrwi; xori; cntlzw; srwi.; beq`

First seen: `game/game/stadium/sta_c2` (2026-09). Recorded so it is not
re-derived.

The target computes `mag == 0.0f` through a five-instruction CR-extraction sequence. Plain
`== 0.0f`, `!(x != 0.0f)`, a `BOOL` local, `& 1` and a direct call were all tried; every one
compiles to `fcmpu; bne`. It caps `chompState1_awake` (97.13%) and `fn_3_CE954` (97.27%), each
about 20 bytes short. Contrast "BOOL return idioms map one-to-one onto source expressions",
which does reach the CLZ form when the value is actually returned or stored.

## Known unsolved: `.bss`/`.data` tables addressed through ONE base register

First seen: `game/game/stadium/sta_c2`, `fn_3_D511C`, `loadWarioPalace` (2026-09).
Same allocator-artifact class as "MWCC 2.x will not register-pool an extern data-symbol base,
no matter the source shape"; see that entry rather than a new theory.

The target reaches every table as `lbl_3_bss_A018 + offset` (or `lbl_3_data_182C0 + offset`) off
one base register; ours emits a per-symbol `lis`/`addi`. An explicit `u8* base = &lbl_3_bss_A018`
local measured far WORSE (`fn_3_D511C` 69.44% -> 45.43%, 712 bytes) and was reverted. The checkpoint
attributes the +7 head instructions in `loadWarioPalace` to it; the function is also 68 bytes long.

## A source-level change can keep a helper OUT of line without `#pragma dont_inline`

First seen: `game/game/stadium/sta_c5`, `fn_3_EEB94` / `fn_3_EEF24` (2026-09).
The inverse of the auto-inlining entries above, and a cheaper answer than a pragma.

`fn_3_EEB94` (352 B) matched 100% standalone, but MWCC then auto-inlined it into its caller
`fn_3_EEF24`, where the target has a real `bl` — dropping `EEF24` to 0% and 436 bytes. Moving a
pointer local (`dir = (s8*)lbl_3_bss_AF18;`) from the function top INTO the inner loop was
enough to stop the inlining, and both functions then matched 100%.

So when our object inlines a helper the target calls, try perturbing the callee's source shape
before reaching for `#pragma dont_inline` — the pragma is scaffolding that describes our tree
rather than the original source, and here a one-line move removed the need for it entirely.
Note the symptom is the caller's score collapsing to near zero while the callee is perfect;
check `bl` counts on both sides before concluding the caller's C is wrong.

## `u32` vs `u8` loop counters decide whether MWCC unrolls a fixed-trip-count loop

First seen: `game/game/stadium/sta_c5`, `loadDKJungle` (2026-09). Sharpens "MWCC
`-O4,p` auto-unrolls trivial fixed-trip-count scan loops".

The target unrolled two small placement-table count loops; ours did not, and no restructuring of
the loop body changed that. The deciding factor was the counter's declared width: with `u8`
counters MWCC emitted the rolled form, with `u32` counters it unrolled exactly as the target
did. That one change took `loadDKJungle` from 79.96% to 82.53%. If a target unrolls a scan loop
and ours refuses to, check the induction variable's type before touching the body.

## Pad a `Control`-style stack local to the target's frame size

First seen: `game/game/stadium/sta_c5`, `fn_3_F65C8` (99.88% -> 100%, 2026-09).
Second data point for "A stack scratch buffer's size is invisible except through frame rounding".

A function that builds a transform through a stack-local `Control` matched every instruction but
missed the frame size. The fix was declaring the local as a wrapper struct padding `Control` out
to 0x44 bytes rather than a bare `Control`. As with the scratch-buffer entry, nothing in `.text`
pins the local's size directly — it only reaches the object through MWCC's frame rounding — so
when every instruction matches and only the prologue/epilogue constants differ, sweep the size
of the highest-addressed local.

## Prefer the named `.bss` statics over a struct-view pointer local for a shared base

First seen: `game/game/stadium/sta_c5`, `updateDKJungleControl` (96.13% -> 97.90%,
2026-09). Practical counter-note to "Known unsolved: `.bss`/`.data` tables addressed through ONE
base register".

When a target reaches several `.bss` objects as `<one base symbol> + offset` off a single
register, the tempting fix is to declare a struct view over the whole region and access it
through one pointer local. Measured here, that is the WRONG direction: guarding on the
individual named file-static objects scored higher, because MWCC folds adjacent statics onto a
shared base register by itself, while the explicit view pointer pins an extra register. The same
polarity was already recorded for the sibling file, where a `u8* base` local took `fn_3_D511C`
from 69.44% to 45.43%. Two independent measurements now point the same way: do not hand-build
the base pointer.

Note the opposite case does exist within one function — a `DKJungleBss* bss` local WAS worth
about +5 points on `dkJungleBarrelCannonUpdate` for flag accesses in the same file. So measure
per function rather than applying either form file-wide.

## Two same-size functions can be one body with the local declarations swapped

First seen: `game/game/stadium/sta_c5`, `fn_3_F4BA0` / `fn_3_F4D00` (172 bytes each,
both 99.77%, 2026-09). Extends "Check for duplicated bodies within a file before writing one
from scratch" and "Sweep local declaration order mechanically".

Two adjacent functions with identical target byte sizes turned out to be the same source body;
the only difference in the target was which of two `Vec` locals sat at stack 0x8 and which at
0x14. Writing one and adapting it by swapping the declaration order cost almost nothing and gave
the same score on both. When a file has two functions of exactly equal size, diff their target
bodies against each other BEFORE writing either — and if they differ only in stack slots,
suspect declaration order rather than a different body.

The same file also found that same-size is not sufficient evidence on its own: `maybeGharialCTRLRel`
and `maybeBarrelCTRLRel` are both 348 bytes and share nothing but their size.

## Findings from the sta_c1 / sta_c3 sessions

**A pipelined struct copy (load x, load y, store x, load z, store y, store z) means the source is
a by-value `Vec` parameter.** When the target copies a position field by field with the loads
running ahead of the stores, MWCC knew the source could not alias the destination. A by-value struct
argument (the caller makes a private copy) gives it that guarantee; `Vec* pos` does not. The caller
side shows it too: a word copy of the vector to the stack right before the (possibly inlined) call.
First seen: `fn_3_C48D0(CastleFireballEmitter* handle, Vec pos)` in `sta_c1.c` (98.80% ->
100%). The same fix matched `fn_3_C24A0` via `updateVectorInArray(int, Vec)`.

**MWCC lays out a TU's `.bss` statics in reverse declaration order.** If a function's code is
identical but every static access is at the wrong offset (the last-declared array landing at offset 0),
declare the statics from highest address to lowest. First seen: `sta_c3.c`, `fn_3_E1DB8`
(99.89% -> 100%, and the unit's `.bss` size then matched).

**A still-stubbed callee can be inlined as an empty body and skew its callers' scores.** With
`-inline auto`, a `return;`/`return FALSE;` stub defined earlier in the file gets inlined, so a caller's
score is not meaningful until the callee is written. Implement callees before judging callers.
Seen repeatedly in `sta_c3.c` (`ParkPlantsPopUp` 91.67 -> 100% once
`tryPlantCatchAndBeginSpitAim` was written).

**Callee prototype width shows up at every call site, so fix the prototype, not the calls.**
`clrlwi rN, rX, 24` on an argument means the parameter is `u8`; `cmplwi` on a return value means it
is unsigned; `clrlwi.` testing an inlined helper's result means it returns a byte (`E(u8, BOOL)`).
Adding explicit casts at call sites instead made scores *worse*. Confirmed with repo-wide report diffs:
`allocParticleEffect` arg 5 -> `u8` (4 functions up, none down), `returnsCurrentMode` -> `u32`
(also improved `sta_c2.c`'s `fn_3_CDFA4`).

**MWCC constant-folds a literal float expression, but not the same
arithmetic through locals.** If the target loads several float constants and combines them with
`fmadd` at run time, write the operands into locals first. First seen: `stadiumObjRelated_Castle`
(83.06% -> 93.91%).

**A `cmpwi 2 / ble` loop that starts at 2 and tests before decrementing is `i = 2; while (i-- != 0)`**,
not `for (i = 1; i >= 0; i--)`. First seen: `fn_3_C19C8` / `fn_3_C2644` (+4 and +3.6 points).

## Findings from the pitcher_ai session

**A retry loop that compares, compares, increments and branches back is `for (;;)` with a two-condition
`break`.** Target shape: body; `cmpw desired,loc; bne exit; cmpwi tries,2; bge exit; addi tries,1; b body`.
`do { body } while (desired == loc && tries++ < 2)` came out 8 bytes short (95.67%);
`for (;;) { body; if (desired != loc || tries >= 2) break; tries++; }` is exact (a two-`break` form and an
`if (...) tries++; else break;` form tie with it). First seen: `pitcherAISetCurve`.

**A register copy right after an unrolled search loop means the loop had its own counter.** `mr r5,r6` at the
loop exit is `for (i = 0; i < 7; i++) {...} loc = i;`, not the loop running on `loc` directly
(`pitcherAISetCurve` 95.88 -> 97.47).

**`step = b - a; step /= k;` is not the same as `step = (b - a) / k;`.** In `pitcherAISelectMoundLocation`
(was `fn_3_20EEC`) the split form fixed the load order of `b` and `a` and the FPR permutation of the
following `fmadds` (90.55 -> 100, and the caller that auto-inlines it 96.01 -> 100). Operand orders, separate
min/max locals, a float index local and an integer divisor all had no effect. Same family as the compound
assignment operand-order lever.

**An `s8` field compared with both -1 and a small positive value shows `extsb` only on the -1 compare.** MWCC
skips the sign extension for equality with a non-negative constant, so `lbz; cmpwi r0,1` (a signed compare with
no `extsb`) beside `lbz; extsb; cmpwi r0,-1` identifies an `s8` field; a `u8` field compares with `cmplwi`.
First seen: `AIStruct.aiPitchDirectionInput`.

**A `cmplw` between two computed struct addresses is a pointer comparison in the original source.**
`pitcherAISelectPitch` compares `&g_Scores.scores[a] > &g_Scores.scores[b]` (probably meant `.total`). Written as
the address comparison, it matched first try.

**Moving a store of 0 above the table load that feeds a random roll fixed the register assignment of the
table-index computation** (`pitcherAISetCurve` tail, 99.47 -> 100).

**Character stat-row copy is an inlined helper.** The sequence memcpy(dst,src,0x1E);
CharID/FieldingArm/BattingStance; memcpy 2 @0x28; memcpy 2 @0x2A; bytes 0x2C-0x34; memcpy 2 @0x35;
u32 @0x20; memcpy 4 @0x37; memcpy 0x36 @0x3B (chemistry); byte 0x71; 21 u16 @0x74-0x9C copies a
`CharacterStats` row. It matched first try as a `static inline void
copyCharacterStats(CharacterStats* dst, CharacterStats* src)` in
`src/Unknown/File_0x800426dc.c` (`transferStatsToInMemRoster`), with the source row indexed as
`Static_Stats_Tables.characterStats[charID / 9][charID % 9]` using `u8` row/col temporaries (the
target multiplies by 0x5A0 and 0xA0 separately, so a flat `[54]` index does not match).
`src/menus/text_0323C.c` hand-expands the same sequence with raw offsets in ~7 places; those are
candidates for the same helper (with `CharacterStats` field names).

## MWCC's `__abs()` builtin is distinct from both the ternary and the `if (t < 0) t = -t;` abs

First seen: `game/game/ball/foul_detection`, `outfieldWallProximityZone` (was `fn_3_B7E44`, 2026-09).

All three spellings compile to the same `srawi`/`xor`/`subf` idiom, but they are not
interchangeable. `x < 0 ? -x : x` scored 86.05%, `if (x < 0) x = -x;` 86.40%, and
`__abs(angle - 0x400)` 99.53% (every instruction matching) - the builtin gives the abs
result a fresh register and changes how the surrounding constant loads are scheduled.
`__abs` needs no prototype and never emits a call; `abs()` via the MSL `arith.h` prototype
emits a real `bl abs`. Tell-tale in the target: the abs result lands in a different register
from its operand (`srawi r5,r4,31; xor r6,r5,r4; subf r6,r5,r6`).

## A trailing `return a < b;` and `if (a < b) return 1; return 0;` can differ only in literal-pool order

First seen: `game/game/ball/foul_detection`, `outfieldWallProximityZone` (was `fn_3_B7E44`, 2026-09).

With `__abs` in place the function's instructions matched, but `.rodata` held `55.0f`
before `63.0f` where the target had `63.0f` first. Rewriting the final
`return 55.0f + scaled < dist;` as `if (55.0f + scaled < dist) { return 1; } return 0;` left
the code identical (still `mfcr`/`srwi`) and restored the pool order, taking the function
and `.rodata` to 100%. When a function is instruction-identical but its float relocs still
mismatch, dump both `.rodata` sections before assuming it is naming noise: objdiff matches a
literal reloc by offset, so a reloc mismatch means the pool is laid out differently.

## `if (!(x != a && x != b && ...)) { A } B` gives the `||` block order without the range fold

First seen: `game/game/ball/foul_detection`, `checkFielderCollision` and
`isCoordinateUncatchableTerrain` (2026-09). Extends "`x == a || x == b || x == c` gets folded
into a range check".

Target: `cmplwi/beq T` for each value, `cmplwi last; bne F`, then `T` falls through - the
natural layout of `if (x == a || ... ) { T } F`. The `||` form folded consecutive values
(2..5, 9..10) into `subi; cmplwi; ble`. The negated-conjunction form from the earlier entry,
`if (x != a && ...) { F } T`, stopped the fold but put `F` on the fall-through path (99.2%).
Wrapping the same conjunction in `!( ... )` with the arms swapped reproduced both the
unfolded compares and the target's block order (100%). A `switch` built a binary decision
tree instead and was the worst of the structured forms.

## `do { } while (++i < N)` is neither counted nor unrolled; the equivalent `for` is unrolled

First seen: `game/game/ball/ball_visuals` (2026-09). Complements the `u32` vs `u8` counter entry.

A fixed-trip loop written as `for (i = 0; i < N; i++)` was unrolled by MWCC where the target kept
a plain rolled loop (20% on the function). Rewriting it as `do { ... } while (++i < N);` gave the
rolled, non-`mtctr` form the target has (93%). If the target shows a compare-and-branch loop and
ours turned into `mtctr` or an unrolled body, try the `do`/`while` spelling before touching the body.
A related trick in `versus_screens`, `maybeSetVsIndOrScoutFlagChance`: a deliberate
`if (i == 45) { i = 45; }` inside a search loop stops MWCC converting it to an `mtctr` loop.

## Several `Vec` locals the target re-reads after every store are one array

First seen: `game/game/ball/ball_visuals`, `fn_3_67EF0` (2026-09).

When the target reloads fields after each store, the stack locals alias, which means they sit in
one array. Turning four separate `Vec` locals into `Vec pts[4]` took the function from 92% to 97%.
Separate locals let MWCC forward the stored register instead of reloading.

## A float parameter's position in the list changes the CALLER's argument scheduling

First seen: `game/game/ball/ball_visuals`, `fn_3_678B8` (2026-09).

The calling convention does not depend on where an `f32` parameter sits in the list (floats go in
f1.., ints in r3..), but the order of the declared parameters changes how MWCC schedules the
caller's argument setup. Moving the float to a different position took `fn_3_678B8` from 90.88% to
99.25% with no change to the body. If argument setup is merely reordered, permute the prototype
before reworking the caller.

Second data point: `game/game/batting/star_hit_sprites` (2026-09). The tell is an int argument
(here a `>=` compare into r4) that the target computes AFTER all the float arguments, while ours
computes it before them, whatever the locals or expression shape. MWCC evaluates arguments in
declared order, so the int parameter is really declared after the floats.
`applyChargeAnimationEffect(int, f32 charge, f32 release, BOOL full)` and
`animationRelated(f32 x, f32 y, f32 z, BOOL)` (int flag last, not first) took `fn_3_6A9B0` from
92.67%, `animateChargeSprites` from 98.05% and `animateStarHits_Pitches` from 95.42%, all to 100%.
The callee's own codegen is unchanged by the reorder. Restructuring the caller only moved the
compare into a branchy `if/else` (94.48%).

## Accumulate a vector one component pass at a time when float registers are permuted

First seen: `game/game/ball/ball_visuals` (2026-09). Extends "Copy a `Vec` per component when the
target uses `lfs`/`stfs`".

Writing an average as `avg = h1; avg += h2; avg += h3; avg /= 3` (one whole-vector pass per
statement) fixed a float-register numbering permutation that a single combined expression could not.

## A file-local struct view of a huge global beats both cast spellings of an indexed member

First seen: `game/game/batting/charge_effects` (2026-09).

For an array at a fixed offset inside a large global, `((T**)(g + 0x2C50))[i]` matched one function
but let MWCC hoist `g + 0x2C50` out of another function's loop (83.59%), while
`*(T**)(g + i*4 + 0x2C50)` avoided the hoist but gave the wrong registers elsewhere. Declaring the
global in the file as `extern struct { u8 _pad[0x2C50]; T* actors[N]; } g;` and writing
`g.actors[i]` gave both behaviours at once (100% on both). Array length can be a guess; note that in
a comment. Try this when two files or two functions want different spellings of the same lookup.

## Findings from the versus_screens first pass

First seen: `game/game/match_setup/versus_screens` (2026-09), Sonnet first pass, 12/20 functions
100% and `.text` 0.69% -> 96.10%.

- **Pointer locals at the top of a function make MWCC hoist a global's address** the way the target
  does, e.g. `GameInitVariables *settings = &g_d_GameSettings;`. Use it when the target loads a
  global's base once and indexes off it.
- **Declaration order of function-scope locals controls callee-saved numbering.** `fn_3_24708`
  reached 100% purely by declaring `obj`, `runner`, `i` in that order.
- **A block-local declared after a call, in a nested block, moves where its `lis` lands.** That took
  `championshipScreen` from 96% to 99.97%.
- **`ABS(x)` on an `int` local emits the `srawi` form; on an `s16` struct field it emits the branch
  form.** Pick the operand type to match the target.
- **A single `.data` object with several named sub-symbols needs both spellings.** Functions that
  hoist the base register reference it as a struct (`VsData`); single-use functions reference the
  named sub-symbols. objdiff matches on symbol name, so both must exist.

## Findings from File_0x80024bb4 (LinearInterpolateToNewRange)

First seen: `main/Unknown/File_0x80024bb4` (2026-09), all 3 functions 100%.

- **An if/else-if clamp and a ternary clamp are not interchangeable.** `if (t > 1) t = 1; else if
  (t < 0) t = 0;` keeps the ratio in f1 and adds an `fmr`; `t = t > 1.0f ? 1.0f : t < 0.0f ? 0.0f
  : t;` keeps the ratio in f0 and returns the preloaded 1.0 directly. Try the ternary when the
  target's "too big" arm has no `fmr`.
- **`fmadds` source-operand order follows local variables, not the order you write `a * b`.**
  `(nextMax - nextMin) * t`, `t * (nextMax - nextMin)` and the `nextMin +` forms all emitted
  `fmadds f1, t, span`. Only putting the difference into its own local (`span = nextMax - nextMin;
  return span * t + nextMin;`) gave the target's `fmadds f1, span, t`.
- **Split `.data`/`.sdata2` for a text-only DOL split so its literals get scored.** If the target
  reaches jump tables or float literals through dtk labels outside the unit, objdiff marks every
  such reloc as a mismatch. Adding the unit's `.data`/`.sdata2` ranges to `splits.txt` took this
  file from 99.25%/99.38% to 100%, and the sha1 check stayed green.
- **The Unknown/ DOL splits around 0x80024xxx are finer than the real translation units.**
  `LERPToNewRange_Float` (File_0x80024b00) reads the same 0.0f/1.0f `.sdata2` literals as
  File_0x80024bb4, and the 0x803CC588 double is shared by File_0x80024974, File_0x800249d8,
  File_0x80024b00 and several auto_ splits. MWCC does not share literal pools across TUs, so all
  of these were one file originally. Flipping any one of them to `Matching` alone fails to link
  (`undefined: 'lbl_803CC5A0'`); they can only be flipped once they are merged into one unit.

## Dolphin SDK code sitting in `Unknown/` DOL splits needs `mw_version="GC/1.2.5n"`

First seen: `Unknown/File_0x80091450.c` (2026-09) — `TEXGet`, `DSInitList`,
`DSInsertListObject`, `Strcmp`, `DSInitTree`, `DSInsertBranchBelow`, i.e. the
Dolphin charPipeline texPalette/List/Tree/dolphinString code. Under the default
GC/2.6 the straightforward SDK-shaped source scored 57-82% on three functions:
2.6 schedules `li 0`/`subf` differently in the init functions and folds
`cursor + list->Offset` into `lwzx`/`stwx` indexed addressing where the target
keeps an explicit `add` and 0-offset loads. A per-Object `mw_version` sweep
(1.2.5n / 1.3.2 / 2.0) showed 1.3.2 and 2.0 identical to 2.6 and 1.2.5n (the
`DolphinLib()` compiler) jumping straight to 98%, with the last miss being
ordinary source placement. Lesson: when a placeholder `Unknown/` DOL unit
turns out to hold SDK functions (names in `include/charPipeline/`, `DS*`,
`TEX*`, etc.), try `mw_version="GC/1.2.5n"` before grinding anything.

## A local aggregate initializer's pooled `.sdata2` copy: give the unit the pool range

First seen: `Unknown/File_0x800b07fc.c` (`soundQuit`, 2026-09). `SND_HOOKS hooks =
{SndAlloc, fn_800B0934};` compiles to two `lwz @N@sda21` loads from an anonymous
8-byte `.sdata2` constant, which objdiff scored as a reloc-name mismatch (99.29%)
against dtk's `lbl_803CCF20`/`lbl_803CCF24`. Declaring the label `extern const`
and copying it is NOT equivalent here: the load gets scheduled ahead of the
`stw r0` and drops the score to 85%. Fix: add the constant's range to the unit's
split (`.sdata2 start:0x803CCF20 end:0x803CCF28`) and merge the dtk labels into
one `size:0x8 scope:local` symbol. objdiff then pairs `@N` with it (100%), and the
Matching link is sha-clean. The pool sits after the neighbouring `initSound`'s
constant even though `soundQuit` precedes it in `.text`, so whoever matches
`File_0x800b0834.c` must NOT claim `0x803CCF18` in a separate split (section
order would conflict); merge the sound TU instead.

## Findings from the twelve-small-DOL-files pass (renderSprite ... convertGeometryAndSknHeader)

First seen: 2026-09, 10 of 12 `Unknown/` units matched and flipped to `Matching`.

- **dtk sizes an `.sbss` label by the gap, not the object.** `lbl_803CBBC2` is `size:0xA`, but the
  target stores to it with `@sda21`; `extern u8 lbl_803CBBC2[0xA]` makes MWCC use `lis/@l`
  because the array exceeds `-sdata 8`. Declare the scalar (`extern u8 lbl_803CBBC2;`) when the
  target uses sda21. Same for `lbl_803CB750` (`size:0x10`, used as one `u32` seed).
- **A struct-typed `extern` global schedules differently from a pointer local to it.** In
  `cancelReadCallback2` (File_0x800a7670) a `LoadState *state = (LoadState *)lbl;` local kept
  the `lwz` after the `sth` (or the `cmplwi` before it); declaring `extern LoadState lbl_803C6CF8;`
  in the TU and writing `lbl_803C6CF8.field` gave the target's `lwz; sth; cmplwi` order (100%).
- **Compound assignments into a reused parameter fix both scheduling and operand order.**
  `randRange_FUN_80042bf0`: every single-expression form of
  `rand >> 16 % (max - min + 1) + min` put `subf` (range) before the seed `mullw` and emitted
  `add r3, min, mod`. Only `a = seed >> 16; a %= b - min + 1; a += min; return a;` matched.
  (`GC/3.0a3` also got 99.5% on an intermediate form; not a real option for game code.)
- **`ANIMGetTrackFromSequence` (SDK `ANIMGetTrackFromSeq`) matched under the default 2.6 with a
  `u32` counter;** `u16 i` emits `clrlwi` per iteration and no `ctr` loop, `int i` gives `cmpwi`
  for the trip-count check. Not every charPipeline function needs `GC/1.2.5n` — 1.2.5/1.2.5n/1.1
  scored lower here than 1.3+ and 2.x.
- **Float-literal splits:** `maybeTransformVectorByAnimationMatrix` (0x800B2C44) and `SetFogNone`
  (0x800B9974) are 100% except the `0.0f` `.sdata2` reloc, which is shared with other splits
  (0x800B43A0 etc. / SetFogNoneAgain etc.). Left `NonMatching` with checkpoints. SetFogNone was
  later absorbed into the merged `Unknown/DisplayObject.c` unit, which owns the whole pool (see the
  SetFog and DisplayObject entries below).

## Findings from the SetFog trio (File_0x800b9974 / 99c4 / 9a30)

First seen: `Unknown/File_0x800b9974.c`, `File_0x800b99c4.c`, `File_0x800b9a30.c` (2026-09). All three
were later merged into `Unknown/DisplayObject.c` (2026-10, see "Findings from the DisplayObject.c merge").

- **Superseded: claiming a shared `.sdata2` constant by name.** These splits first matched by
  declaring `extern const f32 lbl_803CCFFC;` (0.0f) at every 0.0f site, because the pool
  `0x803CCFF8..` is shared with `Custom_SetState`/`DODefaultUserTevMode`/... and no split could own it.
  That workaround no longer exists: the merged `DisplayObject.c` unit owns the whole pool and writes
  plain `0.0f`. Prefer merging to the TU that really owns the pool over naming a pooled literal.
- **`frsp` of an `f32` parameter at a call site, while the stores use the unrounded register,
  means an explicit `(f64)` widening in the call.** `SetFog` stores its four `f32` params into a
  global with `stfs fN` and passes `frsp` copies to `GXSetFog` (so it first `fmr`s every param to
  a scratch register). `f64` params, `(f32)` casts, re-reading the stored fields and
  assignment-expression arguments all CSE the rounding into one `frsp` (74%). `f32` params with
  `GXSetFog(type, (f64)startZ, ...)` matched 100% (an inline wrapper with `f64` params also does).
  An `mw_version` / `-O` sweep changed nothing.
- **A dtk symbol can collide with an SDK typedef.** The Ghidra import named the 0x18-byte fog-state
  global at 0x80111700 `GXFogType`, which cannot be referenced from C while `GXEnum.h` is visible.
  Renamed to `fogSettings` (struct `FogSettings`, now in `include/Unknown/DisplayObject.h`).

## Findings from the eleven-small-DOL-files pass (SndFree ... addOrRemoveCharacterToTeam)

First seen: 2026-09, 10 of 11 functions 100% (9 units flipped to `Matching`; SndFree and
SndAlloc merged into one unit). `multBottomBits_asFloat` (File_0x80024974) stays at 98.16%
with a checkpoint.

- **MWCC gives a string-only `.rodata` section 8-byte alignment, so a split cannot start its
  `.rodata` at a 4-aligned address.** SndAlloc's string sits at 0x800E7CEC. As its own unit it
  scored 100% in objdiff, but the `Matching` link placed the section at 0x800E7CF0 and shifted
  everything after it (sha1 failed). SndFree's string at 0x800E7CD8 is 8-aligned and linked fine.
  Merging the two splits into one unit (`File_0x800b0938.c`, `.rodata 0x800E7CD8..0x800E7D10`)
  put both strings in one section at their original 4-byte spacing (`4 files OK`). dtk flags this
  in advance as `Alignment for <unit> .rodata expected 8, but starts at ...`; treat that warning as
  "merge with the previous split".
- **Argument materialisation order can come from an inline helper's parameter order.** In
  `playPlayerSelectedSound` every direct `sndFXStartEx(ids[findCharacterID(c)], vol[0], ...)`
  form (locals, pointer locals, reordered statements) built the ID table's address first (86%).
  A `static inline startMenuVoice(u8* vol, u16 id)` taking the volume table FIRST matched at 100%.
- **`slwi; addi rX, 8; lwzx` against a struct member is raw byte-offset indexing.** Every typed
  form (`table->elems[i]`, `((T**)table)[i + 2]`) folds the +8 into `add; lwz 8(rX)`. Only
  `*(T**)(bytePtr + i * 4 + 8)` with a `u8*` member kept the target's shape (handleUIAction).
- **A typed graphics-slot index may hoist constant handles into extra saved base registers.**
  In `rep_1610`, `graphicsRelatedArray[firstHandle + 1]` created separate `array + 8` and
  `array + 16` bases, shifting the scene and loop registers. Byte-offset indexing through
  `(u8*)graphicsRelatedArray + ((firstHandle + handle) << 3)` kept the target's `addi; slwi; lwzx`
  sequence and reduced saved registers from six to four (76.58% -> 100%).
- **An `int` local for a byte you compare against makes `cmpw`; a `u8` local makes `cmplw`.**
  (add_or_RemoveCharToATeam / addOrRemoveCharacterToTeam: 98% -> 100%.)
- **A pointer local to a stack struct is how the target gets `addi r31, r1, 8` hoisted into a
  saved register** before a null check (spawnDust: `ParticleBurstParams* p = &params;`, 78% -> 100%).
- **Two float-conversion stack slots swapped with otherwise identical code is still unsolved**
  (`multBottomBits_asFloat`; see its checkpoint for ten hypotheses). The same pattern appears in the
  sibling `byteWiseMultiply`, where three of its four bytes have the target's slot order.

## Findings from the twelve-small-DOL-files pass (createTeamManagementScreen_inGame ... ANIMGetSequence)

First seen: 2026-09, 12 `Unknown/` units; 9 matched and flipped to `Matching`, 3 instruction-exact
but left `NonMatching` (DOGet, LITAlloc, AnimateActorBones; see their checkpoints).

- **MWCC 2.6 schedules loads of one global past stores into another only when the stored-to
  object's DECLARED size is >= 0xFFFF bytes.** In `createTeamManagementScreen_inGame` the target
  keeps `lbz g_d_GameSettings._06` after three stores into `g_TeamManagement` (dtk size 0x24C98).
  With the full-size struct every source shape (pointer locals, inline helper, switch, ternary,
  volatile load, unsized array, `-proc`, `mw_version` sweep) hoisted the load (68%); a struct of
  any size up to 0xFFFE gave 100%, 0xFFFF and up did not. `UnknownHomes_Static.h` now lets a unit
  `#define TEAM_MANAGEMENT_LOCAL_VIEW` and declare a smaller file-local view. Suspect this whenever
  stores to a huge `.bss` object and a load from another global come out in the wrong order.
- **A flag written by an async callback is `volatile`.** `handleDVDCancelAndARQRemoval` keeps
  `lbz 0x715` after `stb 0x714`; only a `volatile` view of the cancel bytes (set by the DVD cancel
  callbacks) reproduced that order.
- **MSSB's charPipeline `Control` is 0x44 bytes, not the SDK's 0x34.** Evidence: `LITAlloc`
  allocates a 0xC0 `Light` with `parent`/`animPipe` at 0xB8/0xBC, the actor forward-matrix array
  sits at 0x60, and five stadium units padded `Control` locals to 0x44. `C3/control.h` now has
  `unk3C[8]` (placement of the extra bytes unknown); `Actor` is 0xA0 and `sBone` has a pointer at
  0x18, three Controls (0x1C/0x60/0xA4), `animPipe` 0xE8 and `drawPriorityLink` 0xFC. `ACTSort`
  matched first try on the corrected layout. Every other object was byte-identical outside `.debug`.
- **`Dolphin/stl.h` and `stl/stdarg.h` both defined `__va_list`**, so `C3/geoPalette.h` could not be
  included next to the stadium headers. `stl.h` now includes `stdarg.h` instead; the `DOVARender`/
  `DOVARenderSkin` prototypes come from `geoPalette.h` (`va_list*`).
- **`(&array[2])[i].field` keeps the constant offset after the multiply** (`mulli; add; addi 0x150`)
  where `array[i + 2]` folds it into the index (`setScissorAndProjection`).
- **`extsb` before `subi` on a byte field means `(s8)u8field - 1`**: an `s8` field folds the
  first sign extension away (`maybeLoadsGameSoundFiles`).
- **A string-only `.rodata` split at a 4-aligned address cannot link alone** (confirmed again on
  DOGet, 0x800E7F8C). Giving the split the range gets objdiff to 100%, but the `Matching` flip fails
  the sha1 check until the neighbouring displayObject strings are in the same unit.

## Findings from the twelve-small-DOL-files pass (starMenu ... load_Icon)

First seen: 2026-09, 12 `Unknown/` units (starMenu, setCaptainLocInRoster, SKNInit, the
lbl_803C5F74 setters, fn_80042D38 trio, storeCursorLocOrCharIDs, createTeamManagementScreen_preGame,
stadiumSelect, challengeRelated, AdjustGEOPalettePointers, PrepFilesToBeLoaded, load_Icon); all
100% and flipped to `Matching`.

- **A pointer local to an array member moves the member offset into the store.**
  `rec->textureOverride[part] = t;` emits `addi r0, part*2, 0xAC; sthx`; the target's
  `add r3, rec, part*2; sth 0xAC(r3)` came only from `u16 *overrides = rec->textureOverride;
  overrides[part] = t;` (load_Icon). A plain `(&rec->arr[0])[part]` or byte-offset cast does not.
- **The written order of a constant in an index decides whether it folds into the displacement.**
  `graphicsRelatedArray[scene->firstHandle + i + 12]` folds `12*8` into `lwz 0x60`;
  `[scene->firstHandle + 12 + i]` keeps `add; addi 0xC; slwi; lwzx` with the target's operand
  order (starMenu). `12 + i + first` gets the `addi` but swaps the `add` operands.
- **`li rN, 0` in both arms plus `mr i, count` before a counting loop is an inlined helper with an
  early `return 0`.** challengeRelated: every in-place if/else form left one arm's zero in `r0` or
  numbered the registers wrong; `static inline int count(...) { if (!flag) return 0; count = 0;
  for (...) ... return count; }` used as an array index matched.
- **`&objs[i]` vs a `dispObj++` pointer changes the callee-saved numbering** even though both
  strength-reduce to `addi r30, r30, 0x6C` (AdjustGEOPalettePointers, 84.9% -> 100%).
- **`bne end; lbz; cmplwi; beq body; b end` is `if (a != 0 || b != 0) return;`,** not
  `if (a == 0 && b == 0) { ... }`, which emits one `bne end` (stadiumSelect).
- **An 8-byte struct assignment and two word assignments allocate the copy registers
  differently** (PrepFilesToBeLoaded: struct copy put the value in r4 and the `stwu` base in r5;
  per-word copies matched the target's r5/r4).
- **A sibling with the same store in both arms of a branch is an inlined call with a constant
  argument.** createTeamManagementScreen_preGame stores `r5` (0) on both sides of the `_06 == 2`
  test: it is the `_inGame` body with `player = 0`, reproduced with a `static inline` copy.
- **A `.text`-only split whose strings/path table are referenced by no other function can claim
  them.** PrepFilesToBeLoaded's `"aaaa.dat"`/`"ZZZZ.dat"` path records (`.data 0x800E8EE8`) and
  its OSReport formats (`.rodata 0x800E6550..0x800E6588`, 8-aligned) were added to its split and
  written as C initializers/literals; the `Matching` link stayed `4 files OK`. The next strings
  (0x800E6588+) and the jump table at 0x800E8F08 belong to handleLoadingProcess.

## Comma-initialised `for` loops: read the init order off the target's `li` sequence

First seen: `staminaRelated` (`game/pitching/pitcher_stamina.c`, 2026-09). Two callee-saved
registers (a counter and a whole-function local) were swapped, with logic identical, and about
150 declaration orders could not fix it. The clue was the order of the zero-inits: the target
emitted `li i,0` *before* `li nCand,0`, and ours emitted them the other way round, because the
source had `nCand = 0; for (i = 0; ...)`. Writing `for (i = 0, nCand = 0; ...)` (and the same
change for a second counter loop) fixed the volatile order in the next block. The pair swap then
became fixable by declaration order again: moving `int nCand;` above the initialised locals gave
100%. When two registers swap and declaration order does nothing, check whether the statement
shape changes what the declaration order acts on. Re-sweep declaration order after each shape
change.

## A unit with no target `.rodata` must not include `header_rep_data.h` or an `extern` dolsqrtf2

Same unit. objdiff scores `.text` only, so the unit showed 100% while our object still carried
a 0x60-byte `.rodata` that the target unit does not have: `repHeaderData` from an unused
`#include "header_rep_data.h"` plus `dolsqrtf2`'s `_half`/`_three`. Before flipping to Matching,
compare the section lists of the two objects. If the target has no `.rodata`, drop the unused
include and `#define SQRT2_LINKAGE static`. Codegen does not change.

## Findings from the at_bat_results / stat_tracking / game_math passes

First seen: `game/game/batting/at_bat_results`, `game/game/match_setup/stat_tracking` and
`game/game/math/game_math` (2026-09).

- **The same routine can need two spellings: one for the standalone function, one for its inlined
  copies.** `RandomInt_Game` and `RandomInt_Sim` match with `int orig = max; if (max < 0) max = -max;`,
  but the copies inlined into the `Random*_Range` wrappers match the `ABS()` form. Rewriting the
  shared body helped one side and broke the other. Keeping the old body as a `static inline` helper
  for the wrappers took `game_math.c` from 99.34% to 99.75%. `at_bat_results.c` needed the same pair.
- **Storing to a global and re-reading it** (`g._00 = sum; ret = g._00 % max;`) instead of keeping
  the sum in a local reproduced the target's load/store order in the sim random helper.
- **Steer the load order of two values read at function entry:** declare one as a local, read the
  other field directly in the first expression, then declare its local afterwards. This fixed
  `fn_3_79DD4` and `updatePitcherStatsOnScoreChange`.
- **Pointer locals over global arrays usually cost the match here; write the full global
  expression.** This contradicts the versus_screens note above, so check the target: use a pointer
  local only when the target clearly hoists one base register.
- **A same-file getter called under `-inline deferred` can be the missing inline behind a register
  swap** (`pitcherStats = fn_3_7BBC0();` fixed `postPitchStatUpdating`'s swap).
- **A `lis 1; subi 1` store of `0xFFFF` means the destination field is unsigned 16-bit.**
- **Statement order inside a loop moves register choice:** in `setAtBatResult`, storing
  `fielderIndex` and `outsDuringPossession` before loading the next field gave 100%.
- **A switch jump table in `.data` scores 0% until its function is the exact target size**,
  because every entry points at a case label. Fix the function first.

## A load that stays below independent stores, plus `lhax` next to an `add`, means an unrolled `for` loop

First seen: `game/game/match_setup/replay_state`, `fn_3_7D2E0`/`fn_3_7D39C` (55.40% -> 100%, 2026-09).

Signature: two copies of the same field-copy block where the target reloads the second copy's
index (`lbz 0x40(rStats)`) only after the first copy's stores, although the stores go to a
different global and could not alias it. Two hand-written copies (or a `static inline` helper
called twice) let MWCC hoist that load above the stores. A `for (i = 0; i < 2; i++)` loop that
MWCC unrolls keeps the load in place. It also explains the source-side addressing: offset 0 is
read with `lhax base, idx` and the other fields through a shared `add` + displacement, which is
what `g_Controls[g_Stats.replayPort[i]].field` gives when every field is array-indexed.
Loading the port into a local or through an `InputStruct*` loses the `lhax`. Related: "A
reload-after-store of the same field means an unrolled loop".

## An `(int)` cast on every compare of a `u32` field means the field is signed, and the cast costs a register

Same unit. `g_Stats.playFrameCounter` was declared `u32`, and every signed compare in the tree
used `(int)g_Stats.playFrameCounter`. With the right instructions, the cast still added a
phantom virtual register: the allocator skipped r11 (or r10 when inlined) and moved the
counter and base registers up by one. Declaring the field `s32` and removing the casts gave
100% on three functions, with the stat_tracking and camera units unchanged. If every use of
a field is cast to the same other type, fix the declared type.


## Findings from the result_stats second pass

First seen: `game/game/match_setup/result_stats` (2026-09), .text 93.6% -> 97.3%.

- **A zero-based `k*stride` offset added to a separate row base means the code was inside an inline
  helper.** In `MVPCalculation` the target builds 2D row addresses as `li r11,0; mr r12,r11 ...
  add r20,r9,r11`, where ours stepped one combined element pointer and came out 68 bytes short.
  Moving the repeated `score[k] += weight * stat` lines into a `static inline` helper restored the
  exact size and the target's stack spills (+6.5%). Row-pointer or element-pointer locals do not
  reproduce it.
- **A pointer to a global array element prevents `lbzu`.** `s8* p = &g_Scores._AF[w]; x = *p; ...
  *p = x;` gives the target's `addi; lbz 0(r)` pair instead of `lbzu` (+6% on `winningPitcher`).
- **Keep declaration-order sweeps to 720 permutations or fewer.** A build and score takes about half
  a second, so 5040 permutations runs past the 10-minute command limit.

## Findings from replay_inputs (first pass to 100%, flipped to Matching)

First seen: `game/game/match_setup/replay_inputs` (2026-09).

- **A same-TU callee that the target calls but our build inlines needs `#pragma dont_inline`.**
  `useReplayInputs` (712 bytes, contains an inlined `dolsqrtf2`) was pulled into `CopyMoreStructs`
  regardless of definition order or loop form; `structCopying` (19 memcpys) is legitimately inlined
  there. The pragma around the callee restored 100%. Original reason not found.
- **`dolsqrtf2` that is actually called: use `SQRT2_LINKAGE static`.** The used statics (`_half`,
  `_three`) then land after the pooled `0.0f`, as in the target; with `extern` linkage they sit at the
  head of `.rodata` and shift the pool by 16 bytes (rodata 94.4% -> 100%).
- **`(f32)a * (f32)a + (f32)b * (f32)b` on `s8` fields** gives the target's per-operand
  `extsb/xoris/fsubs`; plain `a*a + b*b` emits an integer `mullw`.
- **Playback mirrors recording**: reading `g_ReplayLogic[g_Stats.playFrameCounter].pad[i].field`
  (full global expression, no `rec` local) gave 88% -> 100% where the hoisted `rec->pad[i]` form
  produced different induction variables.
- **A restore function that re-reads a byte through a saved `g_Stats` pointer after a fresh
  `lis` read of the same global** (`g_Stats.replayReason != 2 && stats->replayReason != 0xD`) is a
  mixed local-pointer / global-access source shape.

## Findings from the match_setup / hud / animation near-miss pass

First seen: `ai_defaults`, `stat_book`, `controller_input`, `hud_scoreboard`, `match_scene`,
`animation_dispatch` (2026-09).

- **A `mr rX, rY` copying a constant already in a register means the code block was an inlined
  function.** `setDefaultAIValues` re-derived `bonus = 1` from the tracker store's hoisted `li 1`.
  The block was the body of `updateHighUrgencySituationTracker` (pitcher_stamina.c). Writing it as a
  `static inline` with early returns gave 100% and removed three `goto`s. Look for a sibling function
  with the same body.
- **`REC(scene, i + K)` versus `REC_AT(scene, K, i)`.** The target's `add rX, firstHandle, i;
  addi K` comes from `firstHandle + K + i`. `firstHandle + (i + K)` gives `add rX, i, firstHandle`,
  and `firstHandle + i + K` folds K into the load displacement. For a 2D index,
  `REC_AT(scene, 7 + j, i * 6)` is the working shape. This matched 3 hud_scoreboard functions and 2
  stat_book loop blocks.
- **Function-scope digit temps shared across branches get permuted callee-saved registers.**
  Declaring `hundreds/tens/ones` inside each branch block that uses them fixed `drawBookNumbers`
  (99.4 -> 100) after all 24 function-scope declaration orders had failed. The reverse also applies:
  reusing one variable (`a`) for two unrelated jobs cost `pauseControlsMenu_update` a register. Giving
  the first job its own variable, declared first, matched it.
- **A hand-expanded copy of an existing same-TU function should just call it.** `-inline deferred`
  inlines `updateRBIScoreDigits` into both callers, which matched the one that was 99.25%.
- **In a float product with two literals, the literal pool order is the reverse of the source order,
  and MWCC puts the constant on the left of `fmuls`.** The target's `lis/addi/lfs 0(r)` constant
  loads plus `r * c1` came from `k = (f32)r / 512.0f; k = k * c2;`. The division by a power of two
  becomes a multiply by the reciprocal.
- **An `extsh` before storing an `s16` result** that the target re-extends means the local was
  `int` with an explicit `(s16)` cast: `int magnitude = (s16)(...)`.
- **`x*x + z*z` versus `z*z + x*x` decides which operand gets `fmuls` and which gets `fmadds`, and
  that choice also decides the load order of the source fields.**
- **Index the loop instead of stepping two pointers.** `InputStruct* c = &g_Controls[i]` and
  `src = base + i * 0x20` inside the loop matched, where comma-initialised pointers that were
  incremented each pass emitted extra `mr` copies.

## `if (PSVECMag(v))` gives `fcmpu f1(mag), f0(0.0)`; `!= 0.0f` in either order gives `fcmpu f0, f1`

First seen: `game/game/pitching/perfect_pitch_gfx` and `pitcher_fire_effect` (2026-09).

MWCC puts the literal first in the `fcmpu` for both `PSVECMag(v) != 0.0f` and `0.0f != PSVECMag(v)`,
and a float local or `== 0.0f {} else` does not change that. The target's `fcmpu cr0, f1, f0` (value
first) comes from the implicit truth test `if (PSVECMag(v))`. Writing `!= 0.0` as a double is worse
because it adds an `lfd` pool entry. The same one-line change fixed three functions in two units.

Findings from the same session:
- **`acos(x) / 2.0` gives `fmul f0, f1(acos), f0(0.5)`.** `0.5 * acos(x)` and `acos(x) * 0.5` both
  put the constant first.
- **A zero register shared between a field store and a loop index init** (`li r4,0; stb r4,..;` then
  r4 used as `i`) came from `node->stop = i = 0; for (; i < N; i++)`. Separate `node->stop = FALSE;`
  and `for (i = 0; ...)` emit two `li`.


## Findings from the scene_effects / actor_transform second pass

- **Static `.bss` is pooled like static `.data`.** A target function reaching several `.bss` objects off one base register (`addi r30, base@l` then offsets up to 0x3AC) means those objects are this TU's statics. Split dtk's gap symbols at the real object boundaries and use the statics directly; declare them in REVERSE address order (MWCC lays `.bss` out reversed). objdiff's `.bss` score stays 100% even with the wrong order -- only the pooled offsets in the code reveal it. First seen: `scene_effects.c` `fn_3_C0134` (52.8 -> 97.5).
- **Dropping a `SceneFx* fx = &global` local** is often the fix when the target re-materialises `lis/addi global` mid-function: the original wrote the global directly. `scene_effects.c`: fn_3_BE1D4 94 -> 98.6, sunRelated 65 -> 82, drawSun 72 -> 79.
- **Value-form `x == 2` (`subfic; cntlzw; srwi.; beq`) in an `if`:** a `static inline BOOL f(...) { return x == 2 ? TRUE : FALSE; }` reproduces it; plain `==`, `!= FALSE`, a BOOL local, `& 1`, int casts all give `cmplwi`. (fn_3_BE1D4.) Worth retrying on the "Known unsolved" float-equality entry.
- **Var-first `fmuls x, 0.5`:** MWCC puts a float literal first in `x * 0.5f` whatever the source order; writing `x / 2` (integer 2) gives the target's `fmuls fX, fvar, f(0.5)` with a fresh destination register. `sunRelated` 93.9 -> 99.5, drawSun +2.7.
- **`ARRAY_SIZE()` is not codegen-neutral** for signed `%` / `<`: it is `size_t`, so `index % ARRAY_SIZE(t)` becomes unsigned (maybeFireworks 100 -> 81.7). Keep the literal or cast.
- **Hoist a pointer load above independent int->float conversions** when the target interleaves it: moving `bone = model->list->bones[idx];` before six conversion stores took fn_3_C0134 80 -> 96 (MWCC won't move the loads above the stack stores itself).
- **`Vec off[2]` instead of two `Vec` locals** when the target keeps `&b` in a callee-saved register across a call (fn_3_C0134).

## Findings from the twelve-small-DOL-files pass (newPitcherEnteringGame ... ANIMGet)

First seen: 2026-10, 12 `Unknown/` units. 8 reached 100%; 6 flipped to `Matching`
(File_0x8004ac00, 80014f40, 800204cc, 800b0724, 800b2160, 800b508c). Checkpoints for the rest.

- **MWCC gives `.data` 8-byte alignment too, so a split whose `.data` starts at a 4-aligned address
  cannot link alone.** Same failure as the string-only `.rodata` note: `stadiumCollisionRelated`
  (jump table at 0x800FBEF4) and File_0x8006c9d8 (float tables at 0x8010B4B4) are 100% in objdiff
  with their `.data` claimed, but either flip fails the sha1 check. The jump table cannot be externed,
  so these wait for a merge with the preceding data's owner.
- **dtk folds a trailing 4-byte `.sdata2` pad into the previous symbol.** `lbl_803CCF10` was
  `size:0x8` (1.0f + pad); our pool is 0xC bytes, so `.sdata2` scored 85.7%. Shrinking the symbol
  to `size:0x4` gave 100%, and the flip linked because the next section is 8-aligned.
- **Per-case `return a; return a+1;` becomes branchless.** In a switch, `if (t == 1) return 1;
  return 0;` (or any pair of returns differing by one) emits `subfic/cntlzw/srwi` and `addi`.
  Assigning a `ret` local in each case, `break`, and one `return ret;` kept the target's
  `cmpwi; bne; li; blr` per case (stadiumCollisionRelated 54% -> 100%). A one-case inner `switch`
  gives `beq; b` instead.
- **`x == 0 ? 0 : v` vs `x != 0 ? v : 0`.** The first emits `cntlzw; extrwi 1,26; neg; andc`,
  the second `neg; or; srawi; and` (updateCharacterSelectProcessCode).
- **Byte-sized locals for the two components of a row index fixed the load registers.**
  challenge_checkRecruitment: `u8 diff = cs->difficulty; u8 cap = cs->captain;` used as
  `table->required[diff][cap]` matched; `int` locals or a single `row = diff * 6 + cap` local did
  not. A per-iteration `ChallengeTrackingStruct* t = &cs->trackers[i];` (not a `t++` walker)
  plus `t++, i++` ordering mattered too.
- **A hoisted index local can be the whole scheduling difference.** loadBatterModelFromDisk's
  target computes `mulli`/`addi` for the file index between the flag load and its compare; a
  block-scope `int file = index * 0x13 + 1;` before the `if` gave 100% where the inline
  expression in the call left the computation after the branch (69.6%).
- **Pointer setup before the header fix-up.** ANIMGet matched only with the three derived
  pointers (`sequences`, `tracks`, `keyFrames`) computed before `animBank->animSequences` is
  relocated, plus index-form loops (`seq[i].x`), which give the target's `mr r4, r7` before the
  last loop.
- **`(u32)(p + 6) - (u32)p` survives as `addi; addi; subf`; the `char*` difference folds to `li 6`.**
  The target computed a sub-record size that way (setIndicatorSlotState).
- **Frame rounding sizes a stack struct, again.** `LayoutFrameInfo` (fn_8000CEF0's out param) was
  0x58 bytes, which gave setIndicatorSlotState a 0x80 frame instead of 0x70. 0x4C..0x54 satisfies both
  it and load_Icon; the header now uses 0x54.

## Findings from the thirteen-small-DOL-files pass (initializeDVDSystem ... updateVectorInArray)

First seen: 2026-10, 13 `Unknown/` units. 8 flipped to `Matching` (File_0x80014e50, 8001c588,
8001cbd4, 800203e0, 80021308, 800219b4, 80042c44, 80062674); 5 are instruction-exact or nearly so
but blocked by shared `.sdata2`/`.bss` and keep checkpoints (800a76bc, 800527c4, 80064344, 800bdc88,
800beb3c).

- **A TU's pooled statics are laid out in FIRST-USE order across the whole TU, not declaration
  order.** `initializeDVDSystem` reaches two thread stacks and a `DVDFileInfo` through one base
  register (`addi r6, r31, 0x0` is the tell: a pooled static at offset 0). Three file statics
  reproduced the pooling (68.9% -> 98.4%), but every declaration order gave the same layout; only
  an earlier function referencing the stacks first changed it. So a split that is a fragment of a
  bigger TU cannot reproduce the pool order on its own; merge with the earlier users.
- **A callee can be int-wide while every caller sees `u8`.** `isWorldPosOnScreen` ends in
  `cntlzw; srwi r3, r0, 5` with no truncation, yet all three callers `clrlwi.` the result. A `u8`
  definition emits `extrwi 8,19`. Defining it `BOOL` in a .c that does not include the `u8`
  header keeps both views.
- **`(u16)param` as a call argument makes MWCC pass the already-truncated copy.** In
  `animateBallRelated` the plain `index` argument added an `mr r9, r4` to keep the raw register;
  `(u16)index` reused the `clrlwi r0` the multiply needed.
- **Truncation deferred to the merge point after an if/else means a `u8` inline parameter.**
  `initStadiumLighting` computes `id + 7` / `id` into one register, stores it untruncated, then
  `clrlwi`s it for the index. An `int` local plus a `static inline loadStadiumLights(u8 stadium)`
  matched; the inline also fixed the loop's callee-saved numbering, which no declaration order
  could. A second inline around the `Vec` copy + by-value call put the copy at the target's stack
  slot.
- **A template struct copy that the target does with `bl memcpy` needs an explicit `memcpy`.**
  Struct assignment of the 0x70-byte template emitted an inline word loop (handleBallRollInWater).
- **Exit-block threading again:** `loadFielderActors` reaches its fail block from a nested guard;
  the early-return form duplicated the block (93%), `do { ... break; ... } while (0)` matched.
- **A routine body copied from a sibling can still differ in store order.** The inlined
  `changeScene(scene, 1)` in `challenge_setTransitionScreenCharacterPortrait` needed
  `currentScene = 7;` before `sceneArg = 1;`, the reverse of `changeScene` itself, so it is a
  hand-written copy rather than an inline of the sibling.

## Findings from the twelve-small-DOL-files pass (gameSettingsRelated ... AnimateCharacter)

First seen: 2026-10, 12 `Unknown/` units (File_0x800b0834 skipped). 6 flipped to `Matching`
(File_0x8004a1bc, 800b4e9c, 80014d4c, 80064430, 800569c8, 8001b918; `4 files OK`). 5 are
instruction-exact but blocked by shared `.sdata2`/`.rodata` labels and keep checkpoints
(8002399c, 800aaee4, 8001b80c, 800b4bc8, 8001f4c0); byteWiseMultiply (800249d8) is at 73.6%.

- **Two words a caller loads from one 8-byte element into r5/r6 are a `u64` parameter.**
  `memoryCardRelatedFunction` stored its "two" params with the callee-saved registers swapped
  whatever the store order; the callers' `lwz r5, 0(rX); lwz r6, 4(rX)` gave it away. A `u64` param
  (register pair r5:r6) and a `u64[2]` table fixed it. Check the callers when two adjacent params
  are stored to adjacent words.
- **A redundant cast on the second use of an index stops MWCC from CSE-ing the address across a
  call.** In `characterAndBallDisplayRelated` the target rebuilds `lbl_8017EBB0[buffer]` after
  `memset`; plain `[buffer]` twice kept base and index in two extra callee-saved registers (83%).
  Writing the second one `[(u16)buffer]` on the `u16` parameter gave 99.85% (instruction-exact).
  Inline helpers and an `mw_version` sweep did not.
- **`bne; b L; li rX, 0; L:` is a ternary with a zero arm.** `i = kf[*cache].time <= time ? *cache : 0;`
  (ANIMGetKeyFrameFromTrack); the `if (!(...)) i = 0;` form emits `mfcr; extrwi.`. Dropping a
  `keyFrames` pointer local (reading `track->keyFrames` each time) then fixed an r10/r11 swap.
- **A second null test right after an early `return` on the same pointer is an inlined getter.**
  `getAnimRelatedCoordinates` has `bne; li r3,0; b exit` then `beq` again: an inline
  `getPartBone(obj, part)` with `if (obj) return obj->bones[part]; return 0xFFFF;`. It returns
  `int`; the target compares the untruncated value (`addis r0, r4, 0; cmplwi 0xffff`).
- **A per-iteration pointer local moved one `li` by one slot** in a store-heavy reset loop
  (`challengeMapMaybe`: `AnimObject* obj = &hugeAnimStruct.pool[i];`, 97.0% -> 99.8%), although
  the addressing stayed relative to the global.
- **MSSB's `ANIMGetKeyFrameFromTrack` takes a fifth `u16* cachedFrame`**: it starts the search at
  the cached key frame and writes the hit back (`C3/anim.h` updated; no C callers yet).
- **`report.json` scores the reloc-name-only misses as 100%; `objdiff-cli diff` does not.**
  The five blocked units above show 100% in the report and 99.x% in the per-unit diff. Use the
  per-unit diff to decide whether a unit can be flipped.

## Findings from the twelve-small-DOL-files pass (ActorObjectInitTable ... startMenuMusic)

First seen: 2026-10. Three blocked groups were closed by merging splits into their real TUs:
`File_0x800bd8c4.c` (fn_800BD8C4 .. ActorObjectInitTable, with the `.sdata2` pool, the sknRelated
jump table and the init-table warning string), `File_0x8006295c.c` (both menu-music voices plus
initializeUnknown/fn_80062A74, sharing the "sound end" string) and `File_0x800b4908.c` (the actor
anim helpers through ACTSetAnimation; one function still at 98%). Matching flips: 8001c920,
80034cec, 80035ca4, 8006c48c, 800bea04, 800bf074, 8006295c, 800bd8c4 (`4 files OK`).

- **Before merging for a shared pool, check the pool's FIRST user.** MWCC orders a TU's pooled
  literals by first use, so the split that first loads the lowest-address constant must be in the
  merged unit. ActorObjectInitTable and animateBallRelated both load 1.0f before 0.0f, but the
  pool holds 0.0f first, which only fn_800BD8C4 (earlier in `.text`) explains.
- **A string that dtk shows in an unrelated auto split is evidence of the TU boundary.**
  `startMenuMusic` matched and claimed "sound end \n" alone, but the Matching link failed with
  `undefined: lbl_800E69A8`: the auto split fn_8006295C uses the same pooled string. Grep the
  linked objects (the `main.elf` inputs in build.ninja) for the label before flipping.
- **An inline helper for one sub-expression can fix a callee-saved rotation no declaration order
  touches.** fn_800BD8C4 had table/m/i/base rotated through r28-r31 until
  `actor->unk98 = (actor->unk98 & 0xFC) | fn_800B3C04(0, actor, m)` moved into a
  `static inline updateDrawFlags(actor, m)`.
- **A hand-inlined copy of a later function.** fn_800BD8C4 contains fn_800BDA24's body, but
  fn_800BDA24 is defined after it, so `-inline auto` cannot inline it. Use a `static inline`
  copy for the caller. The standalone function still needed its own spelling
  (`Control* dst = &entry->actor->worldControl; Actor* actor = entry->actor;` gives the target's
  `lwz r3; mr r31, r3`).
- **`(x & 1) != 0` as a call argument** makes MWCC evaluate that argument before the others
  (`clrlwi r4` ahead of `lwz r3`). Plain `x & 1` loads the first argument first.
- **A second pointer temp for a field that is tested and then read** (`track = pipe->currentTrack`)
  fixed a two-register swap in two sibling scan functions.
- **`(int)u8field == ENUM` gives `cmpwi`; without the cast MWCC emits `cmplwi`.**
  (challengeDrawStarsOnMissionMenu.)
- **`s32 j` restores the vestigial `li r0,0; cmpwi r0,10; bge` guard** on a fully unrolled
  10-store loop (addGraphicsElementToScene, 74% -> 87%), as in the ball_physics note above.
- **`while (1) { x = ...; if (!x) break; ... }` keeps a list walk unrotated** where
  `while ((x = ...) != 0)` is rotated (someGFXRenderingFn 92.9% -> 99.3%).

## Findings from the File_0x8003a688 merge (fn_8003A8A0, charPipeline display-state draw)

First seen: 2026-10. `File_0x8003a688.c` (0x8003A688..0x8003AE54) reached 100% on all seven
functions and flipped to `Matching` (`4 files OK`).

- **An unrolled 13-attribute VCD loop is a 12-trip loop plus a hand-written 13th.** The target
  showed `mtctr 2` with six copies of `type = (bits >> shift) & 3; if (type) {...}`, then a peeled
  copy using the constant `extrwi. rX, r0, 2, 4` (shift 26). A 13-trip loop does not unroll at all
  (`mtctr 13`). `for (attr = GX_VA_POS, shift = 2; attr <= GX_VA_TEX7; attr++, shift += 2)` followed
  by an explicit `(bits >> 26) & 3` block for the last attribute matched. Putting `shift = 2` in the
  `for` initialiser (after `attr`) rather than as a separate statement fixed the `li` order. The same
  shape is open in `sta_c5.c` fn_3_EE67C.
- **Volatile/callee-saved rotations here came from variable reuse, not declaration order.** A full
  720-way declaration-order sweep changed nothing. The fixes were: a separate counter `j` for the
  display-state loop (state pointer then got r31), and reusing the texture loop's `i` as the VCD
  entry count (`vcd[i]`) instead of a fresh `n`. When the permutation sweep is flat, try merging or
  splitting variables between disjoint live ranges.
- **`GXSetArray(attr = GX_VA_TEX0 + i, ...)`** put the attribute computation after the inlined
  component-size switch (the target's `addi r31, r28, 0xd` sits after it) while keeping it in a
  callee-saved register for the second call. A `GXAttr attr = ...` initialiser computes it too early;
  `GX_VA_TEX0 + i` written at both calls loses the callee-saved register.

## Findings from File_0x8001d180 (setHandModelAttached, first pass to 100%, flipped to Matching)

- **`li rN, 0` ... `cmpwi rN, 0; subi rN, rN, 1; bne` with a pointer stepped by -4 is a one-pass
  `do { x = arr[i]; ... } while (i-- != 0);` starting at `i = 0`.** MWCC does not fold it away; index
  the array (`obj->actors[i]`) rather than hand-walking a pointer, which cost a register.
- **A self-contained search loop at the end of a function whose temporaries reuse low registers
  (r3..r6) that every declaration-order permutation misses is a `static inline` helper.** 120
  permutations of the locals topped out at 99.47%; moving the `do { b = *--p; ... } while (n != 0);`
  body into `copyLastDispObj(bone, src)` gave 100% immediately. Declaration order still fixed the
  outer function's registers (`owner` declared before `obj`).

## A dtk-named `.rodata` "global" can be a local aggregate initializer

First seen: `Unknown/File_0x80023b90.c` (`characterLightingRelated`, 2026-10). dtk named two
`.rodata` objects `Vec_XPos`/`Vec_YPos`, but the target's `lis; lwzu; lwz; lwz` + three stack
stores is MWCC's copy of a local initializer (`Vec xAxis = {1.0f, 0.0f, 0.0f};`). When a unit is
the only reader of such objects and of its `.sdata2` literals, claim both ranges in `splits.txt`
and mark the dtk labels `scope:local`; objdiff pairs the anonymous `@N` objects with them and the
`Matching` link stays `4 files OK`. Check the range start is 8-aligned first.

## An `rlwinm` that shifts a halfword by 16 is a mask-then-shift MWCC could not fold

First seen: `Unknown/File_0x800bbf5c.c` (`GetColorFromQuant`, 2026-10). The target's GX_RGBA6
case does `lhz; rlwinm r0,r0,16,24,29` -- an always-zero result for a 16-bit load. Every shift-first
spelling (`v >> 16 & 0xFC`, `(v >> 18) << 2`, casts to `s32`/`u8`) is constant-folded by MWCC to
`li r0,0`, and reading through `u32*` gives `lwz` instead. Only mask-first,
`(*(u16*)src & 0xFC0000) >> 16`, survives to codegen and matches. Pattern: a rotate that provably
produces zero means the source masked before shifting.

## A flag test computed straight into `r3` before a `bctrl` is the callback's argument

Seen in `LoadFile` (`src/Unknown/File_0x800a8cbc.c`) and every jukebox-queue function around it:
`lwz r0,0x8(rN); rlwinm. r3,r0,0,28,28; beq; mtctr r12; bctrl`. Writing the test as a plain
condition (`if (cb && (n->flags & 8)) cb();`) gives the identical sequence but with `rlwinm. r0`,
and no temp/inline variant moves it. The `r3` destination means the masked value is also the
call's first argument: `if (cb && (n->flags & 8)) cb(n->flags & 8);` (CSE folds the two) matches.
Pattern: a dead-looking `rlwinm.`/`clrlwi.` into `r3` right before an indirect call is an argument.

## `li rA, 0` + `mr rB, rA` for two zero-assignments means the code was inlined

First seen: `Unknown/File_0x80025c58.c` (`ACTActorRelated`, 2026-10). The target set two
locals to 0 in the same block as `li r0, 0x0; mr r5, r0` (and `li r6, 0x0; mr r0, r6`). In a
plain function, MWCC 2.6 emits `li; li` for `a = 0; b = 0;` regardless of the locals' types
(u32/int/pointer all tried), and chained assignment (`a = b = 0`) or copying one into the
other (`b = a`) is copy-propagated back to two `li`s. Verified on a scratch testbed: the exact
same body wrapped in a `static inline` and called from a one-line wrapper emits `li; mr`.
The same mechanism explains the existing `count = 0; for (i = 0; ...)` copy in
`File_0x8006cbe4.c`, whose body is an inline. So when you see this pair, put the enclosing
code in a `static inline` called from the real function. Note that inlining also changed how
`p = &base->ptr[12]; v = *p;` compiled (it lost the `lwzu`); writing
`if ((p = base->ptr) != NULL) { p = &p[12]; v = *p; }` brought the `lwzu` back.

What remained after that was register allocation only, and local *declaration order* decided
it. A script that tried random declaration orders and kept any single move or swap that
raised the score went from 96.29% to 100% (one restart). Source statement order for two
bitfield reads from adjacent bytes (`subType` before `type`) also changed which `lbz` got
which register. Expect this kind of declaration-order search to be needed when the
instructions already match but several locals are live across a loop.

## Findings from toy_field_offscreen (second pass to 100%, flipped to Matching)

- **Duplicate `extsb` on one byte (`lbz rA; extsb. r0,rA` for a sign test, later `extsb rA,rA` for an index)**
  means the byte went into an `int` local with no cast, and each use casts it: `slot = u8field; if ((s8)slot < 0) ...;
  arr[(s8)slot]`. MWCC does not CSE the two casts of a register variable. Casting the field directly at both uses, an
  `s8`/`u8`/`int` local assigned with the cast, or an `s8`-returning inline all fold to one `extsb.`.
  `toyfield_offScreenCharacterImage` 97.53 -> 98.41.
- **Load order of a stack var vs a table bound** follows C evaluation order: `p = bound; if (x <= p)` loads the bound
  first; `if (x <= (p = bound))` loads `x` first while still keeping `p` live in the same register. Splitting into
  `if (x <= bound) { p = bound; ...}` fixed one site but broke a sibling site's allocation; the embedded assignment
  fixed both (98.97 -> 100).
- **Declaration order became significant only after the structural fix**: the original log recorded declaration order
  as "no effect", but once the slot `int` local was in place, reordering locals (`alphaX alphaY i dir`) fixed the
  remaining i/dir/alpha register swap (98.41 -> 98.97). Re-sweep declaration order after any structural change.

## Findings from minigame_fielder_anim (second pass to 100%, flipped to Matching)

- **Two strength-reduced walking pointers where the target has one** means one access goes through a raw
  cast while its siblings go through struct fields: `((u8 *)&g_Minigame)[0x18F0 + i]` next to
  `g_Minigame.minigameControlStruct[0].characterIndex[i]` got its own induction register (an extra `mr` in
  the prologue and an extra `addi` in the loop latch). Spelling the byte through the struct
  (`minigameControlStruct[1].battingHandedness[2 + i]`) put all of them on one pointer. 97.21 -> 98.89.
- **Two `extsb` of one loaded byte, one for a `< 0` test and one into a saved register**, is
  `int raw = field[i]; if ((s8)raw < 0) ...; slot = (s8)raw;` with `s8 slot` a separate local. Casting at
  every use instead gives three `extsb`; testing the field and then assigning it CSEs to one.
- **Register pairing across if/else arms follows loop-scope declaration order.** Both arms' locals declared
  in their own blocks never reproduced the target's sharing; hoisting all of them to loop scope and
  sweeping positions did (99.78 -> 99.84). A swapped pair of *volatile* registers (r5/r6) was a CSE'd
  re-read of a global: making it a named loop-scope local assigned in the first test
  (`if ((st = g.gameStatus) == X)`) and declared LAST fixed it (-> 100); declared anywhere earlier, or as
  `int`, it stayed swapped.
- A block-local that shadows (or is replaced by) the loop-scope variable of the same type is not free:
  reusing the loop-scope `obj` in a side branch cost 0.3%; a separately named block-local kept 100%.
- **`extern const f32 lbl_N_rodata_X` blocks the flip** when the label is `scope:local`: our object
  cannot resolve it. Replacing it with the `0.0f` literal kept `.text` at 100% (the target loaded it once
  per store group, so the extern's CSE advantage did not apply) and took `.rodata` to 100%.
- A `cmpwi`+`bge` cascade sorting a small enum into 3+ groups is a real `switch` (case groups + `default`);
  a hand-built `||` range chain with the same values does not reproduce MWCC's sparse-switch lowering.

## Findings from stadium_draw (partial pass)

- **Caller stack copies of `GXColor` can indicate aggregate arguments passed by value.**
  MWCC implements these arguments through hidden pointers; a pointer-looking callee alone
  does not establish a source pointer parameter. Compare callers with the SDK's
  `GXSetTevColor(GXTevRegID, GXColor)` convention. In `stadium_draw`, correcting
  `fn_3_42CC` and `fn_3_4F90` to by-value colors reproduced the caller copies;
  direct aggregate expressions then compiled identically to explicit local copies.
  The glyph caller also needed branch-local height assignments to preserve the target's
  float lifetime. Recheck the whole unit when correcting an ABI.
- **Complete branch-local GX setup sequences can survive separately.** Sharing the common
  tail of two TEV setup branches omitted and reordered target calls. Reproducing all eight
  calls in each branch took `fn_3_42CC` from 88.63% to 96.51%.
- **A stored animation byte can be the subsequent lookup index.** `fn_3_5C68` writes the
  incremented frame as `u8` before reading tile tables, then reloads that stored byte.
  Indexing with the untruncated integer changes behavior for frame counts above 255;
  delaying the store also changes aliasing behavior. Separate stride-4/stride-8 branches
  recovered the target's load paths after preserving these semantics (73.40% to 91.08%).

## Findings from the data_only near-miss pass and hud/rep_3448 first pass (2026-10)

- **`x / C / 2.0f`, not `x / C * 0.5f`.** MWCC turns the trailing `/ 2.0f` into `* 0.5f` late, so
  0.5 lands in the literal pool *after* C (the target's order). Each single-expression conversion
  also gets its own stack scratch slot, which restored `rep_3B70`'s 0x70 frame.
- **`#pragma optimization_level` / `opt_*` brackets do not explain `rep_3E00`'s `li 3; slwi 2`
  and re-read fields.** Measured on `fn_3_166448` (baseline 71.78%, 408 bytes): level 0 31%,
  level 1 35%, level 2 far worse (objdiff reported 0% at the target's exact 412 bytes), level 3
  unchanged, `opt_propagation off` 72.18% (424 bytes), `opt_common_subs off` 56.7%,
  `opt_lifetimes off` unchanged. Don't re-run these.
- **A remove-on-failure tail is `if (ok) { body } else { remove }`.** The structured
  early-return form scored 94.49% against 100% (`hud/rep_3448` `minigameHudEventBannerUpdate`). When several early
  conditions share one remove block, `goto remove` beat the structured form (`minigameHudResultBannerUpdate`
  95.3% vs 86.84%).
- **Child scene nodes:** `node = currentDrawingItem; parent = node->currentDrawingItem;
  scene = (cast)node;` in that order matched 100% (`minigameHudBodStreakBonus`, `minigameHudBodKingBombBonus`).
- **Unsolved in `rep_3448`:** the target loads `&g_Minigame` once at entry and shares it with an
  inlined predicate (ours rematerialises it); `rec->unk69[0] == 2` compiles to
  `subfic; cntlzw; srwi.; beq` in the target (seen right after a store to the same record) but to
  `cmplwi; bne` for us; and `add r,first,i` operand order.
- **`add rA,base,idx; stw v,0(rA)` instead of `stwx` = the address is also a call argument.**
  `rep_3C28` `fn_3_15F574` sat at 93.11% for four passes on exactly this. `fn_8002C2D0` takes a
  third argument, the effect entry (rep_3D50 already declared it that way). The target keeps
  `base + idx*0x40` in r5 because it feeds the call too. Declaring the missing parameter and
  passing `&table[idx]` matched 100%. Before you grind an addressing-mode difference, check
  every callee prototype against the target's argument registers (r5/r6 set up but "unused").
- **Pull in neighbouring un-split `.text` that touches the unit's data.** `0x15F874-0x15FB84`
  sat between `rep_3C80` and `rep_3CE0` and referenced `lbl_3_data_27EC0/27F10`. That range was
  five `rep_3CE0` functions, and one of them (`fn_3_15F874`, no callers) was the depth-clear
  quad that draw had auto-inlined. Calling the real function instead of a hand-written
  `static inline` was codegen-identical.
- **Indexed `counts[i]` / `overlay->markers[i]` over hand-written cursors.** MWCC's induction
  pointers are created after the declared locals, which changes register colouring. In
  `rep_3CE0` setup, `counts[i]` instead of an `int* activeCount` cursor gave +1.7%, and
  scoping `used` after the coord pointers gave +0.4%. In draw, the indexed loops were
  codegen-identical to the cursor form and read far better.
- **Statement order before a varargs `memset`/`va_start` decides addi-form vs direct loads.**
  `rep_3CE0` setup went 90.3% -> 97.0% just by doing `overlay = getOverlay();` *before* the
  `yOffset`/`slot` locals. That reproduced the target's `addi rX,@l; lbz 0(rX)` for
  `drawStadiumRelated`.
- **Unrolled byte-append loop:** `while (count-- != 0)` gives the target's 4x `srwi.`/`andi.`
  unroll, while a `for (i<count)` loop with int or u32 gives an 8x unroll. To get
  `add r,base,idx; stb v,0x473(r)` and not `addi; stbx`, write the store through a *global*
  (`arr[0x473 + n++]`, or `(*(T*)arr).values[n++]`), not through a pointer local.
- **A callback taking `void*` and casting to a struct pointer allocates differently from a typed
  parameter.** `rep_3CE0` draw (`fn_3_15FF28`, installed as an overlay `draw` callback) sat at
  99.12% for three passes with the param in r27 and the target's r28, swapped with a loop-counter
  web. Copying a *typed* param into a local changed nothing. Declaring the param `void* arg` and
  making the first local `Rep3CE0Overlay* overlay = (Rep3CE0Overlay*)arg;` made the code
  byte-identical (99.91%, with only `...data.0` reloc names left). If a callback/drawing function's
  param register is off by one callee-saved slot, try `void*` + cast before you grind decl orders.
- **Folded `lbz sym@l(rA)` vs `addi rB,rA,sym@l; lbz 0(rB)` for the same global is a colouring
  outcome, not a source shape.** In `rep_3CE0` setup, `volatile`, direct vs inline, and index
  locals all left one site in addi form. Even removing every other read of the global left it
  there. Removing unrelated code (memset, a later loop) flipped individual sites. The fold only
  happens when the `lis` and `addi` temporaries get the same register.

## Findings from the orderchange.c merge (swapPosMenu_*, star menus; 9 splits -> 1 unit, flipped to Matching)

First seen: `Unknown/orderchange.c` (2026-10). Nine `Unknown/` splits (0x80042598..0x8004617C) were one
TU: `OSPanic("orderchange.c", 0xD69, ...)` sits in `lineupOrderChangeRelated` and in its inlined copies
inside both `swapPosMenu_*` functions, and their pooled strings and four jump tables could only be owned by
one object. All 11 functions reached 100% and the unit links as `Matching` (`4 files OK`).

- **A non-unrolled `ctr` copy of a function that is fully unrolled everywhere else, with `extsb` on
  `i + 1`, means the function returns `s8`.** The standalone `lineupOrderChangeRelated` (9-trip scan) is
  unrolled, as are 34 inlined copies; the copies searching for position 0 stayed a `mtctr 9` loop with
  `addi r0, i, 1; extsb r0, r0`. Returning `int` unrolled those too (90.2%); returning `s8` reproduced
  both shapes (100%) with the standalone function unchanged.
- **Jump-table entries give the source order of the cases.** Case bodies are emitted in source order,
  so sort the table's targets by address and write the `case` labels in that order (left/right: 98.59 ->
  98.68; up/down needed it too).
- **`TEAM_MANAGEMENT_LOCAL_VIEW` also governs reloads within the same object.** With the 0x24C98-byte
  type MWCC forwarded `prev = cur; cur -= n;` from registers; the target re-reads `cur` after storing
  `prev`. A file-local view under 0xFFFF bytes reproduced the reloads (starMenuCursor 87.1 -> 99.95).
- **`f = f - n` and `f -= n` on an `s8` field differ**: the long form subtracts from the sign-extended
  value the preceding compare produced (`subf r0, n, r0`), the compound form from the raw byte.
- **`srwi` on a `u8` field compared signed is `(s32)(field / 2U)`.** `field >> 1` gives `srawi`,
  `(u32)field >> 1` makes the compare unsigned.
- **A local caching a global byte can cost a register swap that reading the global at every use avoids**
  (`g_d_GameSettings._06` in swapPosMenu_left_rightPress: local 99.95, `int` local 99.82, direct 100).

## Findings from the mcard.c merge (memory-card tasks; 2 units + 21 auto splits -> 1 unit, flipped to Matching)

First seen: `Unknown/mcard.c` (2026-10). `OSPanic("mcard.c", ...)` and a shared string pool tie
0x800A9864..0x800ACF14 together; all 23 functions reached 100% and the unit links as `Matching`.

- **The OSPanic line numbers fall as addresses rise** (0xA6A at the first function, 0xEC at the last):
  the original emitted functions in reverse source order. Writing the source in address order with the
  DOL default `-inline auto` produced identical code to reversed order + `-inline deferred`.
- **A string literal is pooled when the function containing it is code-generated, not when an inline
  is parsed.** Two helpers (`mcardLoadOpeningBnr`, `UnpackTexPalette`) whose strings sit in the middle
  of the pool had to be plain `static` functions defined at that point in the file; as `static inline`
  their strings moved behind later functions' strings. MWCC also emits the plain statics standalone
  (extra `.text` + extab/extabindex entries, so objdiff shows extab 95% / extabindex 0%), but **mwld
  dead-strips unreferenced static functions together with their extab entries**: verified by adding an
  unused static to a Matching unit (`4 files OK`) and by this unit's own flip.
- **An index that becomes a byte offset in place** (`mcardChannelAt(chan *= sizeof(McardChannel))->x`,
  then `mcardChannelAt(chan)->y`) is what makes MWCC keep `chan` and `chan * 0x28` in ONE callee-saved
  register (`lbz r29; ...; mulli r29, r29, 0x28`). Plain array indexing, a pointer local, a fresh
  `offset` local and even a separate `chan *= ...;` statement all gave the index its own register; only
  the compound assignment inside the expression matched (six functions at once).
- **Argument order of an inlined helper decides the parameter registers.** The target's inlined CRC
  loop had data/len in r8/r7; calling the standalone `mcardCrc16(data, len)` (auto-inlined) swapped
  them. A `static inline mcardChecksum(s32 length, u8* data)` with the parameters reversed matched.
- **The SDK `CARDSetIconFormat/CARDSetIconSpeed(stat, i, f)` macros** produce the strength-reduced `2*i`
  shift register the target uses; a hand-written shift variable gives different scheduling.
  `u16 speed` (not `u32`) fixed the remaining callee-saved rotation, and `|= (u8)(x & MASK)` on a `u8`
  field fixed a load scheduled one slot early.
- **A dtk gap symbol spanning several strings scores reloc mismatches** for every `addi rX, base, off`
  into it; split it at the real string boundaries in `symbols.txt` (here `lbl_800E7A38`, 0xF0 -> 7
  strings).
- **Claiming a unit's `.bss` can create a dtk link-order cycle** when an earlier unit claims a range in
  the COMMON region near the end of `.bss` (0x803C4BE0..0x803CB734 holds globals in TU order:
  `AtBat_ButtonInput1`, `mcardState`, `memoryUsedOrStorage`, `DSS_Head1`, ...). mcard's statics at
  0x802EF2C0..0x802F93A0 stay unclaimed (extern) for that reason; File_0x800a6304/File_0x800a64e0's
  `.bss` claims in that region are probably really `common`.
- **`CARDFastDelete` (0x80088698) was really the SDK's `CARDDelete`**: it takes a file name and calls
  `CARDDeleteAsync` + `__CARDSync`. Renamed in `symbols.txt` and `Dolphin/card/CARDDelete.c`.

## Findings from the mb_subfunc.c merge (roster/team setup; 12 units + 9 auto splits -> 1 unit, flipped to Matching)

First seen: `Unknown/mb_subfunc.c` (2026-10). `OSPanic("mb_subfunc.c", ...)` in `findCharacterID` named the
TU; its `.data` (tables + five jump tables in function order) and `.sdata` tie 0x80064754..0x80069A68
together. All 27 functions reached 100% and the unit links as `Matching` (`4 files OK`).

- **A split whose `.data` starts only 4-aligned cannot be flipped on its own.** `findCharacterID` alone
  (jump table at 0x801091F4) was instruction-exact but grew `main.dol` `.data` by 0x20 when flipped: MWCC
  aligns each object's `.data` section to 8. The fix was the merge with the TU that really owned the
  preceding `.data`; the merged unit starts 8-aligned and links byte-identically.
- **A DOL function inlined into an EARLIER-address function means `-inline deferred` + reverse-order
  source**, even on the DOL side. `unknownSettingTeamValues` (0x80068838) contains an inlined
  `setCaptainLocInRoster` (0x80069854); `-inline auto` cannot inline a later definition. The unit uses
  `extra_cflags=["-cpp_exceptions on", "-inline deferred"]` with definitions in reverse address order.
- **A table referenced from another unit must stay global even though this TU addresses it through the
  pool base.** Under these flags MWCC addresses the TU's own globals as `firstObject + off` just like
  statics, so objdiff cannot tell; the link can. Making `captainIDOrderedOnCapSS`/`captainIDMappings`
  `static` broke the menus/game REL imports, `variantPairs` alone `static` broke `fn_800415A8`.
- **A struct-typed global beats every cast view of it.** The header declares
  `g_Challenge` as an array; the target's loops (s32 vestigial guard + CSE'd bases)
  only appeared with the symbol declared as the real block struct. Done file-locally via
  `#define name name_asArray` before the includes, `#undef`, then `extern Block name;`.
- **If every use of a `u8` field is cast `(s8)`, the field is `s8`.** Retyping
  `structCharSelect.rosterCharID` to `E(s8, CHAR_ID)` and dropping the casts fixed volatile-register
  numbering in two loops at once (99.19 -> 99.49): the natural signed load and an explicit cast
  produce the same instructions but different register numbering.
- **Which existing local a loop uses matters even when the declaration order does not.** Two rank-sort
  loops and one placement loop only matched once their counters were written with different existing
  locals (`t`, `i`); moving `int k` to every position in the declaration list never reproduced it.
  When register numbering is off by a swap in one loop, sweep "which variable", not just declaration order.
- **An unrolled row search inside an inline helper: pointer walk vs index.** The target folded the
  start offset into the first load (`lhau r0, 0x124(rBase)`); `variantPairs[row][0]` gave
  `addi; lha`. A block-local row pointer `s16 (*pair)[5] = variantPairs; ... pair++` matched
  (declared at the top of the helper it did not).
- **A separate `int` key local can be needed beside an `s8` one.** The multi-captain rank search wanted
  `int captainKey = roster[j]` while the others' search kept `s8 key`.
- **Redundant self-stores (`x = x;`) reproduce stores the target has after a loop** (`teamCompositionLogos`,
  `characterSelectScreen`, `unsure_FillRosterPositions`); reading the value once into a local does not.

## Findings from the DisplayObject.c merge (charPipeline display objects; 14 splits + auto splits -> 1 unit, flipped to Matching)

First seen: `Unknown/DisplayObject.c` (2026-10). The rodata string "Warning: DisplayObject.c: User TevMode
%d not handled." named the TU; the `.sdata2` pool 0x803CCFF8..0x803CD058 (first use SetFogNone ..
DOVARender) and the 4-aligned DOGet string tie 0x800B993C..0x800BCB44 together. All 21 functions reached
100% and the unit links as `Matching` with `-cpp_exceptions on` (`4 files OK`).

- **A cast argument to an inlined helper is evaluated into its own temporary; a bare variable is
  substituted.** DOVARender's inlined lights loop hoisted its bound `(u32)numLights` into a register that
  was swapped with the light pointer. `DOSetLights(amb, numLights, ...)` (any parameter type) substitutes
  the caller's `u8` and the LICM-created bound is numbered last; `DOSetLights(amb, (u8)numLights, ...)`
  (a cast that is a no-op in C) makes the argument a temp created at the call, which moved the bound to
  the target's register and let the light/state pointers share one. Same mechanism as the literal-pool
  finding below. When an inlined loop bound's register is wrong, try a cast on the argument.
- **After that change, declaration order in the helpers mattered again** (`Light* light` before
  `u32 i`; `u32 i` before `DisplayStateList* state`): orders that were all equal before the cast split
  into 99.65 / 99.89 / 100. Re-sweep declaration order after any change to how a helper is inlined.
- **Literal-pool order follows a pre-order walk of the post-inlining tree.** A `static inline` helper's
  literals are pooled where it is expanded; a plain `static` helper (still auto-inlined) is also compiled
  standalone at its definition, which pools its literals there. DOVARender's pool has `255.0f` (from the
  lights helper) before `0.01f` (computed first in DOVARender); only a plain `static DOSetLights` defined
  before DOVARender reproduced it. The standalone copies cost extab/extabindex rows in objdiff but mwld
  dead-strips them at link (same as mcard.c).
- **An inline returning `u32` from a `u8` local** (`static inline u32 DOGetColorSize(u8 type) { u8 size;
  switch ...; return size; }`) gave the target's `clrlwi` after the switch AND kept the caller's
  parameter registers; returning `u32` from a `u32` local reshuffled every callee-saved parameter.
- **A stack local below struct-copy temporaries means it lives in an inlined helper.** DOVARender's
  `GXColor color` sat at 0x8 under the GXColor argument copies; declaring it in DOVARender (any position or
  block) put it above them, a local of the inlined lights helper put it exactly there.
- **The first `.sdata2` word `{0,0,0,0x80}` was a file-scope `static const GXColor`** defined before
  SetFogNone (so it pools first), copied into a function-scope `GXColor` by Custom_SetState.
- **Switch shape decides compare-tree and block order:** `case 0: default:` first, then `case 1`,
  `case 2` reproduced the target's inner switch; default-first alone or case-1-first did not.
- **Enum fixes:** `GX_TG_MTX3X4`/`GX_TG_MTX2X4` were swapped in `GXEnum.h` (SDK: 3x4 = 0, 2x4 = 1) and
  the `GXTevColorArg` C0..A2 values were wrong (SDK: C0=2, A0=3, C1=4, A1=5, C2=6, A2=7). Codegen of every
  other object was unchanged; check these enums against the SDK when a GX call's constant looks off.

## Findings from practice_modes (full match, flipped to Matching)

- **A two-dimensional byte view can restore index evaluation order.** Four completion
  routines accessed the progress mirror as `base[offset + type * 4 + level]`.
  MWCC loaded `level` first and combined it with the base before shifting `type`;
  the target loaded and shifted `type` first. A four-column view rooted at the
  same offset, indexed `[type][level]`, matched all four. Reordering the scalar
  expression alone had no effect. Keep the observed row width and underlying
  storage unchanged.
- **A cached state can change register allocation throughout a routine.** Removing
  the one-use `state` local in `practice_fieldingRelated` and testing the field
  directly took it from 93.925% to 100%; widening the local or threshold did not.
  The complete 28-function unit and all its sections remained 100% after the
  readability pass and linked with `4 files OK`.

## Findings from the low-match game REL pass (2026-10-09)

- **Restore actual helper calls before tuning macro-expanded locals.** In
  `camera_script.c`, normal definitions of the view evaluator, view setter,
  header fixup, and startup helpers auto-inline under the existing deferred
  inlining settings. Reusing them instead of copying their bodies into macros
  matched `fn_3_1048E0` and `fn_3_FC448` and improved every affected caller.
  The complete `fn_3_FC938` is too large to inline into the two-camera loop;
  its constituent calls still need the small startup macro.
- **Verify the relocation base together with data layout.** An extra camera
  axis object shifted later data by 12 bytes. Equal numeric operands hid two
  wrong vector references. The target's base plus 0x4F44/0x4F50/0x4F5C selects
  the existing Y, Z, and negative-Z vectors. Correcting all three references
  removed the extra object and restored the exact data-section size.
- **A copy between two history loads is significant.** The vector filter
  loads its previous output before copying its current input. Moving that
  copy restored the target's instruction sequence and improved both large
  camera-update routines. By-value helper argument order controls the
  inlined vector slots and register groups too; use the whole-unit diff.
- **A mapped 16-bit ID may still use an int-width parameter.** Reusing the
  bone parameter after reading its ID from the actor table matched the
  sentinel test and output registers in `fn_3_10617C`; a separate `u16` local
  emitted a different comparison.
- **Preserve the stadium pointer-table countdown.**
  `rebaseStadiumPointerTable` processes count + 1 entries and skips negative
  counts. Chaining the output-table assignment with its cursor initializer
  reproduces the target's unrolled loop. Reusing one function-scope index
  for the zero-trip header copies also resolves their register allocation.
- **Scale existing roster parameters before repeated accesses.** In
  `practice_loadCharacter`, scaling team and slot once preserves the
  target's repeated address formation across the flag branches. A cached
  destination pointer produces different code. The typed four-column
  progress view also matches the index order in the practice-loading copy.

## Findings from the Challenge-mode state / star mission data pass

- **`g_Challenge` is one 0x4508-byte `ChallengeState`** (`game/challenge/challenge_state.h`),
  not `ChallengeTrackingStruct[54]`. Converting users from `(u8*)tracker + 0x....` to fields was neutral
  everywhere except where a function kept one base pointer across many accesses: those need a local
  `ChallengeState* cs = &g_Challenge;` (decideScoutFlagMission 92.9 -> 98.3 versus a bare
  global per access). Byte-pointer walks over `savedLineup` in text_0323C (stride 6, odd start offsets)
  stay byte pointers; `CHALLENGE_STATE_OFFSET(member)` names the offsets.
- **Flat byte tables sometimes encode the original indexing.** `characterStaticIndexes[(id) * 6 + 2]` in
  practice_simulation.c fuses the `+ 2` into the base register; `characterStaticIndexes[id].requirementRow`
  and `[id][2]` both lose 8% there, so that TU keeps the flat form.
- **Tables shared by several TUs can be claimed by the neighbouring text TU.** The Challenge tables at
  0x80109420-0x8010B4B4 are referenced from half a dozen units; they sit in File_0x8006c48c.c because the
  previous TU ends at `jumptable_801093C4` and the next one (File_0x8006c9d8) starts its buff tables at
  0x8010B4B4. The trailing 2 bytes after `starRankByMissionCount` are alignment padding (symbol size
  0x70 vs 0x6E of data), which costs .data 0.012%.
- **A symbol rename only needs symbols.txt plus source:** the menus/game asm and relocations regenerate
  from `config/GYQE01/symbols.txt` on the next `ninja`.

## Findings from the last-function sweep (2026-10)

- **dtk splits a small byte/halfword table at the index the code reads.** `u8 x[4]` read as
  `x[0]`/`x[1]` shows up as `lbl_A` (size 1) + `lbl_A+1` (size 3); `s16 x[2]` as two size-2 labels.
  Declared as separate C arrays, MWCC 4-aligns the second one and the unit's `.data` grows by 4 per
  pair (objdiff still says 100% per symbol; the sha1 check fails). Merge the labels in `symbols.txt`
  and declare one array. Fixed `data_428C` (470C, 4710, 4908, 4B40, 5FC0) and `data_8D88`
  (`scoutMissionProgressRowBases`).
- **A data-only split that starts 4-aligned may own a pad that belongs to the previous unit.**
  MWCC always gives `.data` 8-byte alignment, so `data_428C` linked 4 bytes late. Its leading
  `pad_04_0000428C` was the tail of `match_loading`'s range; moving the split to 0x4290 linked
  byte-identically. `match_flow_data` (0x5FF4) cannot be fixed that way: its first object starts at
  0x5FF4, so it was merged into `data_428C` (which now ends at 0x6510).
- **Zero-initialised `gap_*` fillers in a data-only `.c` land in `.bss`.** `u16 gap = 0;` is a
  `.bss` object to MWCC; delete it (array alignment re-creates the gap) or the REL's `.bss` grows.
- **`extern const f32 lbl_*_rodata_*` in a REL unit leaves `.rodata` short.** Replace them with the
  literals, add `#define SQRT2_LINKAGE static`, and put the functions in reverse address order:
  the pool then comes out in the target order (`roster_init`, `hud_gauges`, `stadium_star`,
  `sta_c0`). Check every function afterwards: on `batter_ai` it moved `resetBatterAIBoxPosition`
  (the first function in source) into an `addi`+`lfs 0(r)` load of 0.0f and was backed out.
- **Flipping a unit that uses the default `getRepHeaderData`** shortens the module `.rodata` by 0x50
  when another Matching unit already uses that name. Give it a unique `REP_HEADER_DATA_FN`.
- **A literal-pool operand swap `fmuls f1,f1,f2` vs `f1,f2,f1` can need a constant held in a local.**
  `controller_input`: `k = ((f32)r / 512.0f) * scale;` with `f32 scale = 0.27208483f;` matched where
  every inline-literal form (and `k *= c`) kept the wrong order.
- **`if (cond) { ...; break; }` followed by fallthrough code vs `else { if (x) y; break; }`.** When the
  target reuses a base register from an earlier check, the shared block must only be reachable through
  that check (`baseRunningPracticeRelated`).
- **Unreferenced bytes inside a unit's `.bss` range** (`pad_05_00001900_bss` in `stadium_framework`)
  are an unused static; declaring `static u8 lbl_3_bss_1900;` in the right position fixed `.bss`.
- **Reusing one local for two values can be the match** (`draw_initStarGuageHud`: `next` holds the
  batting-order slot and then the roster index; a second local re-coloured r7/r8).

## Findings from the game_rel_entry full-match pass

- **Pointer scope and declaration order can need to change together.** In
  `maybeProcessTeamData`, removing the block-local `lineup` shadow alone tied
  the baseline, and reordering the other locals while keeping the shadow did
  not fix the register swap. Using the function-scope pointer with locals in
  `lineup, i, slot, team, teams` order took the function from 99.433334% to
  100%. Re-test declaration order after changing a local's scope.
- **A 100% object diff can hide wrong BSS symbol offsets in REL relocations.**
  The first Matching link had identical size and section bytes but 26 differing
  relocation bytes: the three zero-initialized statics were allocated in reverse
  address order. Check symbol offsets as well as the zero-filled `.bss` score;
  declaring these statics in descending target address order restores their
  layout under MWCC.

## Findings from the controller_input full-match pass

- **An inline multiplication helper can preserve operand order where a direct
  expression does not.** `InterpretControllerInputsIntoMagnitude` had one
  remaining `fmuls` operand swap at 99.97151%. Calling
  `static inline f32 scaleStickCorrection(f32 value, f32 scale)` whose body
  returns `value * scale` reproduced the target when invoked with `k` and
  `0.27208483f`. Compound assignment changed the destination register and
  regressed its consumers. All three functions and `.rodata` remained 100%.

## Findings from the baserunning_practice full-match pass

- **Extra global-base loads can be caused by a missing branch exit.** In
  `baseRunningPracticeRelated`, the negative-instruction arm of the live-ball
  case must exit whether or not the runner scored. The prior `else if`
  fell through when the runner had not scored, creating an extra predecessor
  and forcing MWCC to reload `g_Practice`. An `else` with the score check
  inside it and an unconditional `break` restored the target control flow,
  removed eight extra bytes, and matched the whole six-function unit.

## Findings from the defence_animation full-match pass

- **Correcting a narrow return prototype and removing its redundant cast
  can need to happen together.** `angleDifferenceNormalized` already returns
  `s16` in `game_math.h` and its definition; the local extern incorrectly
  declared `int`. In `computeAdjustedFielderOrientation`, changing the result
  local from `s16` to `int`, correcting the extern to `s16`, and dropping the
  explicit `(s16)` result cast took 98.58491% to 100%. Individual changes
  did not match: the redundant cast still created a separate temporary.
- **Separate counters can matter even for a fully unrolled loop.** Sharing
  `i` between the initial hide loop and the later live animation loop swapped
  its saved register with the model pointer in `animateDefence`. Giving the
  hide loop its own block-local `j` matched 100%; pointer scope, declaration
  order and counter width changes alone had tied. The final structured guard
  also removed eight `goto` statements without changing codegen.

## Findings from the Astra at_bat_results follow-up

- **Counter reuse inside a shared helper can fix only its inlined caller.**
  Reusing the initialization counter `i` for the descending loop in
  `shuffleIntArray`, instead of declaring a separate `k`, left its standalone
  copy and every matched sibling at 100% while improving `shuffleU8Array`
  from 99.46429% to 99.89286% (unit `.text` 99.92008% to 99.98402%).
  The remaining six operand differences are in two random-remainder/absolute
  value sequences. Check both reuse and separation of loop counters; the
  successful direction here is the opposite of `animateDefence` above.

## Findings from the second last-function sweep (2026-10)

- **A pointer local to a global can be the match.** `fn_3_219CC` (runner_items) only reached the
  target's `lwzx rD, rGame, rOff` (with `rOff = team*4 + 0xF4` hoisted) once the loop read
  `game->Team_CaptainRosterLoc[settings->humanTeamNumber]` through
  `GameControlsStruct *game = &g_GameLogic;` and `GameInitVariables *settings = &g_d_GameSettings;`
  (80% -> 100%; `i` had to be declared before `count`). Same lever as the "pointer local" entries
  above: try it when a global's base address lands in an unexpected register or the target keeps
  the base and the offset in separate registers.
- **A unit whose target has no `.rodata` must not include `header_rep_data.h`.** `at_bat_setup`
  was 100% in objdiff, but the flip failed the sha1 check: the header's weak `repHeaderData` added
  a 0x50 `.rodata` the original never had. Check `llvm-objdump -h` of both objects before flipping.
- **`s32` instead of `int` again restored a vestigial guard** (`li r0,0; cmpwi r0,N; bge` before a
  fully unrolled loop) in `someRosterMemoryManagement`; the rest was a hoisted `fieldingTeam`
  local that the target reloads inside the guarded block (use the field directly).
- **Moving an assignment can move a base register.** `fn_3_CABF0` (perfect_pitch_gfx): with the
  register order otherwise right, the shared `lbl_3_common_bss_35154` base was `r5` in ours and
  `r10` in the target; assigning `model = (...)(common.trailOwner + 0xC4)` *before* the copy loop
  instead of after it fixed it (also needed: `s32 i`, then `state, handle, i` declaration order).
- **The order of `|` operands in a branchless boolean OR is visible.** `animateScoreBoard`:
  `a | b | c` built `or r0,rB,rC; or. r0,rA,r0` only for the target's order; permuting the three
  operands (six orders, plus the right-nested forms) found it in one batch.
- **Pooled statics can also hide inside a dtk `.data` object.** In `pitcher_fire_effect`, one
  function reaches `lbl_3_data_17DC0` as `addi rX, base, 0x0` / `base+0x48c`, another as its own
  `lis/addi lbl_3_data_17DC0+0x3C0`: the 0x4A8 object is really several statics. Splitting it
  reproduced the pool but was not yet a net win (see that unit's checkpoint).

## Findings from the data-layout pass (pitcher_fire_effect, rep_21F8; 2026-10)

- **The pooled-statics split above is now a net win in both files.** `pitcher_fire_effect`:
  `lbl_3_data_17DC0` -> slots/headers/2 Vecs/zero word (animatePitchersHandOnFire 86.85 -> 99.88,
  fn_3_CB538 95.88 -> 96.16). `rep_21F8`: `lbl_3_data_17898` -> key table, node, HudObj[5], word,
  active byte, f32[5] (fn_3_C937C 97.38 -> 100, unit flipped to Matching). In both cases the split
  alone was not enough; the follow-up source fixes were what turned it into a gain.
- **An `add rX, base, idx; stw 0(rX)` where you would expect `stwx` means the address stays live,
  usually as a call argument.** In fn_3_CB538 the header address was left in r5 for the next
  `bl fn_8002F5F4`, which takes it as a third parameter that the old prototype was missing. Check
  whether the register holding the address is still live at the next call before reaching for
  source-shape tricks.
- **Volatile-register numbering follows IR order, and it limits the scheduler.** Loading a value
  shared by several stores into a local *first* (`tex = burstTexture;` before computing the slot
  and header addresses) reproduced the target's r5/r6/r7 assignment and its late `lis`.
- **`while (tbl[++i * 2] != END)` gives the target's two induction variables** (a pointer IV for
  the body loads, an offset IV + `lhzx` for the condition). The `i++; } while (tbl[i * 2] ...)`
  form merges them into one `lhzu`.
- **Statics in a `.data` split are pooled in BOTH directions:** a `.bss` byte read through a
  neighbour's base register (`lbz 0x14(r31)` off `lbl_3_bss_9F20`) and stored through its own symbol
  in another function means two file statics, declared in reverse (`.bss` reverse-order rule).
  objdiff marks those pooled loads with an `R_PPC_NONE` reloc in the target and diff-cli scores them
  as mismatches until the layout is right; the report does not.

## Findings from the m_sound / practice_simulation data-layout pass (2026-10)

- **A dtk label covering several scalars can stop MWCC pooling the `.bss` base.** In `m_sound`,
  `handleGameSound` reaches the voice ids at 0x1778/0x177C and the flag byte at 0x1760 through one
  base register in the target. With dtk's `lbl_3_bss_1774` declared as `s32[3]` ours addressed it by
  its own symbol each time; splitting it into three `s32` statics (and 0x1760/0x176C into their
  real scalars) gave the target's pooling (91.5 -> 98.6; `fn_3_8C4F0` 83.3 -> 99.2). A function
  touching only two scalars (`fn_3_8C2DC`: 0x1764, 0x176C) is not pooled in the target either.
- **MWCC 4-aligns a `.bss` array even when its elements are `s16`/`u8`.** A dtk label at a
  2-mod-4 offset declared as an array (`camera_script` `s16 lbl_3_bss_B67A[15]`, `scene_effects`
  `u8 lbl_3_bss_9CFE[0x22]`) lands 2 bytes late and grows the section. objdiff still scores
  `.bss` 100%. If only the first element is accessed, split it into the 2-byte scalar plus the
  4-aligned tail; a 2-byte-aligned struct wrapper is 4-aligned too.
- **Unreferenced `.bss` gaps need both a static and a `symbols.txt` name.** In `chain_chomp_sprint`
  declaring the unused statics fixed the layout, but `.bss` stayed at 90% until dtk's
  `gap_05_0000B79C_bss` was replaced by a named `scope:local` symbol that our object could pair with.
- **A target that keeps every store in source order and copies with strict `lbz`/`stb` pairs
  means volatile accesses.** `practiceLoadingRelatedMaybe` (72.0 -> 91.3) only stopped hoisting the
  16 loads once the source *and* destination were volatile, the per-row
  `addis rX,rY,1; addi rY,rY,4` appeared only with a per-row `volatile u8* src` pointer, and the
  leading `hugeAnimStruct` store stayed first only once it was volatile too. `#pragma scheduling off`
  and `optimization_level` did not reproduce it.
- **A `case` that duplicates a whole function body is an inline of that function.** The
  `loadPracticeScreen` default case is `practiceLoadingRelatedMaybe`'s body. A plain call stays a
  `bl` under `#pragma dont_inline on`. A `static inline` helper used by both matched the inline
  (90.7 -> 96.3).
- **`s32` (long) counters stay unfolded where `int` folds** in straight-line code too, not only in
  loop guards: `fn_3_166448` (rep_3E00) keeps its `li r29,0 ... cmpwi r29,0` only with
  `s32 inactive` assigned before the calls.

## General codegen patterns (2026-10, collected from second passes)

Findings from second passes on files that are not fully matched yet (camera_script, the C3
charPipeline units, minigame_effects, animation_dispatch, runner, versus_screens/hud_scoreboard).
They are written down here so they do not depend on those files reaching 100%. Each was confirmed
by a score change in at least one function.

### Control flow and switches
- **The address order of a switch's jump-table targets is the source order of the case blocks.**
  Read dtk's `jumptable_*` entries in address order and lay out the cases the same way
  (camera_script `fn_3_1000D8`/`fn_3_101CC4`: case 6 before case 5). The table also shows cases
  the draft is missing (camera_script `fn_3_FDB30` lacked opcode 76 and fell into default).
- **A pair of `beq` on the same compare means an inlined `x == NULL || ...` check.**
- **A shared exit block may need a `goto`.** When the target branches into the tail of an `else`
  arm (`updateFielderState; return TRUE`), a `goto` into it can be the only form that matches.
  Measure the structured forms first and log them (animation_dispatch
  `fielderBodyCheckAnimation`, `animationsForFielding`).
- **`return FALSE` vs `break` to a shared exit:** where the target has one exit block, use
  `break` plus a single trailing return.

### Inlining
- **Many "macros" and hand-written blocks are small functions MWCC inlined.** If a block repeats
  in several functions, or the stack layout differs only around it, write it as the real function
  (or a `static inline`) and call it. This fixed the camera filter "macros" and script-start block
  (camera_script), the `static inline mg*` helpers whose bodies belonged to named functions
  (minigame_effects, which also fixed the literal-pool order), `ACTSort`/
  `maybeTransformVectorByAnimationMatrix` (C3 act.c), and the base-reset loop in runner's
  `running_initRunner`/`running_resetRunners` (an inlined `running_resetRunnersAfterFoulBall`).
- **Shrinking a function can make MWCC start inlining it into its caller**, which can wreck the
  caller's score (runner `running_calcFramesToClosestBases`). Always re-check callers after
  shortening a function.
- **A `#pragma dont_inline` stub can be needed while a callee is still a stub:** otherwise its
  `return NULL` is inlined into a matched caller (objinit `f_InitActorWithLayout`).

### Types and prototypes
- **If the target re-extends (`extsb`/`extsh`/`clrlwi`) a call argument or return value, the
  prototype is narrower or wider than ours.** Declare file-local prototypes that match:
  animation_dispatch matched with `s16` frame / `u8` handedness arguments to
  `AnimateCharacter`/`QueueCharacterAnimation`, and `int`-returning angle helpers
  (`calculateAngleFromCoordinates`, `angleDifferenceNormalized`, `radToShortAngle`). Leave a
  comment saying why it differs from the shared header.
- **When the target re-extends a value at every use, re-read the field instead of caching it in
  a local** (same idea as the `*(s8*)&field` read macro in pitcher.c).
- **Local types should match the field width** (`s16` for `s16` fields, `u8` for bytes; runner
  `running_getDirectionOverride`).
- **`(u32)` on an array index flips the operand order of the final `add`.**
- **Unsigned constants (`0x10U`) give `cmplwi` on u8 flags.**

### Floating point
- **`fabs` from `stl/math.h` is a macro for the `__fabs` intrinsic, but MSL declares `fabs` as an
  inline function, and the two allocate float registers differently.** Where a function calls
  `fabs`, try the function form:
  `#undef fabs` + `static inline f64 fabs(f64 x) { return __fabs(x); }` file-wide, or a
  differently named helper for only some functions. It matched the whole bobOmbFuseSpark family
  (minigame_effects) and lifted camera_script, scene_effects and five sta_c5 DK barrel functions.
  Two sta_c5 functions match better with the intrinsic, so the header itself is left unchanged.
- **`x / 2.0f` compiles to a multiply with the constant second; `x * 0.5f` puts it first.** A
  constant held in a local (`f32 scale = 0.01f;`) also keeps it second.
- **`if (x)` gives `fcmpu x, 0`; `x == 0.0f` gives `fcmpu 0, x`.**
- **In `a*b + c*d`, MWCC fuses the first product** unless the left side is much more complex.
  Separate locals for the products (`sqx = dx*dx; sqz = dz*dz;`) are distinct from `dx = dx*dx`
  and fixed two runner functions.
- **MWCC keeps a value in f1 across a call when f1 is that call's float return.**
- **A draft that ignores a float return is a real bug, not a codegen detail.** animation_dispatch
  `unsure_updateAnimations` divided `1.0f` instead of the bone time returned by
  `getActorBoneAnimTime`.

### Registers, locals and loops
- **The first-declared local tends to get the highest free callee-saved register.** Reordering
  declarations alone matched C3 `fn_800B4278`. Script declaration-order sweeps are cheap, but when
  120+ orders change nothing the difference is not declaration order: stop sweeping.
- **A walking pointer whose base the target keeps** (`addi rB, g_Runners; mr rP, rB`, base reused
  later) means the source indexes per iteration: `runner = &g_Runners[i]`.
- **Hoisted constant locals can be wrong.** Read table constants where they are used, not into
  locals at the top (runner `running_updateStamina`).
- **A chained assignment stops constant folding:** `for (extra = i = 0; ...)` keeps a never-true
  `extra >= 2` test the target retains; a plain `extra = 0` is folded away.
- **`do {} while (++i < n)` avoids the ctr loop** where the target does not use one.
- **A loop-scoped `int idx = i;`** can be needed for two inlined copies to match
  (animation_dispatch `minigameIdleAnimations`).

### Data and expressions in effect code (minigame_effects)
- `-(rand() % 2 * 2) + 1` for a random sign.
- Two statements (`alpha = p->alphaByte; alpha += step;`) instead of one expression.
- Read a fade's start value into its own local first.
- Write `(n - duration)` inline instead of keeping a `range` local.
- `GXPosition3f32` / `GXColor1u32` / `GXTexCoord2f32` in a plain 4-vertex loop for quads.

### Unit ownership of data
- **A base register cannot be shared across translation units.** If code reaches deep into a
  data-only unit through one pooled base (versus_screens `+0xEB0` off `lbl_3_data_1D28`,
  hud_scoreboard `+0x66A8` off `lbl_3_data_8D88`), that data is the code unit's own `.data`. The
  data-only unit only existed because the units between them have no `.data`. Data reached only by
  symbol from several units can stay in a data-only unit (data_1880's AI tables).

### Diagnostics (do not commit)
- `#pragma opt_propagation off` around a caller shows whether constant/copy propagation is the
  difference (runner `runnerAI_startSteals` 61 -> 89.5 with it). It also changes everything else,
  so treat it as evidence, not a fix.
- `objdiff-cli diff` and the report score pooled `.bss` accesses differently (the target carries
  `R_PPC_NONE` relocs). Use the report for regression checks.

### Uncalled functions and auto-inlining (fielder_ai second pass)
- **A function with no `bl` to it anywhere in the target is inlined somewhere.** List them with a
  grep over `build/GYQE01/*/asm` (no `bl name`, no `.4byte name`), then find the caller whose
  body contains the callee's code and call the real function instead of a hand-expanded copy.
  fielder_ai had 28 such functions; calling them fixed fn_3_A89D4 (setThrowSpeedType2),
  fieldingAIPlayStrategy (fn_3_A53DC), autoMovement10_HasBall (fielderChasingAI, fn_3_A6D48, which
  also removed a `goto`), fielderAIChaseRunner/fielderAIMakePlay (chaseRunnerWithBall) and let two
  hand-written `static inline` duplicates (fn_3_A2FD8/fn_3_A295C) be deleted.
- **If the plain call stays a `bl`, the callee is over MWCC's auto-inline size limit.** Making the
  callee smaller with its own inline helpers brought it under the limit: fn_3_AAC84 inlined into
  makeThrowVariables once its throw-frame code went through a `static inline` helper, and
  setThrowSpeedType2 inlined into fn_3_A89D4 the same way. An explicit `inline` on the
  callee also inlines it, but then MWCC no longer emits the out-of-line copy; a non-inline wrapper
  around a `static inline` body emits it with different code.
- **Shared arithmetic is often a real function that gets inlined.** The fielder_ai throw-time
  estimate is `estimatedThrowFramesFromBallHolder(x, z)`; calling it (after the covering fielder is read) matched
  howManyFramesTheRunnerIsOutOfReach and lifted throwTimeToBase 97.8 -> 99.97. Where it is placed
  matters: before the covering-fielder read it scored 93.
- **Walking table pointers in a loop stop an inlined callee from sharing the loop's induction
  variables.** Rewriting fieldingAIPlayStrategy's loops as `table[i]` / `g_Runners[i]` took it from
  93 to 99.2 once fn_3_A53DC was inlined.
- **A small store helper can be the source of an evaluation order.** fn_3_A53DC's tail
  (`throw[i] = 0; run[i] = -1; out[i] = frames - framesToBase;`) only matched through an inline
  `setThrowStrategy(i, strat, frames, framesToBase)` that subtracts inside, with framesToBase read
  into its own local first. The target computes the difference after the constant stores'
  values.

### Locals and re-reads (fielder_ai)
- **Copying an `s16` local into an `int` local can cost a `mr`.** setRunnerChasingAfter was 4 bytes
  long until `base = fromBase` became `base = g_FieldingLogic.fielderAssignedLocationIndex[6]`
  (re-read the field). Re-reading `g_Fielders[c].numFramesToGetToAutoLocation` at each use instead
  of keeping it in a local matched howManyFramesTheRunnerIsOutOfReach and lifted throwTimeToBase/runnerTimeToCoverBase.
- **`cmpwi rX, 4; bge` then `extsh. r0, rX; blt` on an `lha` value** is an `int` local tested as
  `x >= 4 || (s16)x < 0` (runnerTagUpOrBatterTo1B; makeThrowVariables uses the same idiom).
- **A lone `fcmpo` whose result is never branched on** is a conditional assignment to a dead
  variable: `f32 vel = cur; if (vel + accel > jog) vel = cur;` reproduced it in tagOutValues.
- **A `lead = frames - 10` local can change integer allocation.** Writing `(frames - 10)` at each
  use matched fn_3_AAC84's integer registers.
- **A pointer local for a one-off `g_Fielders[a[b]].field` read** fixed the last registers in
  initializeThrowAngle_Speed_Length.

### Control flow (fielder_ai)
- **`ble body; b exit` right after a range test** is an early-return guard:
  `if (a < 0 || b < 0 || b > 3) return;` (fn_3_AAA3C).
- **A dead `b epilogue` after `b join`** comes from `if (c) { x; } else { return; }` where the
  `return` arm's branch was threaded away (fielderAIDecideWhatRunnerToTarget).
- **A comma expression inside a condition gives `mfcr`/`srwi.`;** read the value twice instead and
  let CSE merge the loads. `!(x < c)` gives a single `blt`; `x >= c` gives `cror` + `bne`.
- **`for (i = 0; i < 4; i++) if (d[i] <= k) { base = i; break; }`** shows up unrolled with a
  walking pointer (`addi r3, rB, 4; lfs f1, off(r3)`), not as an if/else-if chain (tagOutValues).

### Diagnostics
- objdiff does not score the `jumptable_*` vs `@NNN` or `lbl_*_bss_*` vs `...bss.0` relocation-name
  differences that a plain text diff shows; check `diff_kind` in the JSON before chasing them.

### Duplicate-body sweep across the game REL (2026-10)
A pass over every game unit, looking for hand-written copies of functions that MWCC inlined.
- **Search the source as well as the asm.** Comparing instruction sequences flagged many false
  positives: sibling functions with near-identical code (camera views, minigameWinnerStars_*,
  fn_3_E4760/fn_3_E48D0). Checking whether a function's first few statements appear inside
  another function in the same `.c` found the real copies faster.
- **"Called elsewhere" does not mean "not inlined here".** A function that other units reach
  with `bl` can still be inlined inside its own unit: practice_loadCharacterData in
  loadPracticeScreen, warioPalaceSomething in loadWarioPalace, fn_3_1CBCC in cameraControl.
  The no-`bl`-anywhere test finds only some of the candidates.
- **A `#pragma dont_inline` on a callee can be what keeps a copy in place.** Once the pragma
  around practice_loadCharacterData was removed, the call inlined and loadPracticeScreen went from
  96.29 to 97.30. A dont_inline region that contains a never-called function is worth checking
  (fn_3_B3C64 was another).
- **Hand copies can carry real bugs.** pitching_practice's transition case passed
  `GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY` where the callee fn_3_B61C0 passes
  `GAME_STATUS_AT_BAT`. Calling the real function fixed it, and the whole unit reached 100% and
  was flipped to Matching.
- **Inlined helpers nest.** pitchingPractice_BaseballControl's switch was fn_3_B60F0 /
  fn_3_B5F7C / fn_3_B61C0, which in turn inline fn_3_B60F0 and fn_3_B5E7C.
  runnerStealing_TransitionToLiveViewIndicator inlined fn_3_73850, and the three spelled-out
  runner checks were an unrolled `for (i = 1; i < 4; i++)` loop (88.4 -> 100).
- **`blt` straight to an else-arm laid out after the then-arm** came from an early-return
  guard: `if (a >= 0) { if (!b) { x = 0; return; } } else { ...; return; }` followed by
  the shared tail (fn_3_B6C9C, 82 -> 100).
- **The inlined copy shows the callee's parameter type.** fn_3_EE67C's inlined copy of
  fn_3_EE0BC uses `srawi 4; clrlwi 24`, which is `(u8)(x >> 4)` on a `u8` argument. Changing the
  callee to `int fn_3_EE0BC(u8)` let the call match the hand copy. With a `u32` parameter the
  call scored lower.
- **Too big to auto-inline: shrink the callee through another never-called function.**
  fn_3_C4CF4 stayed a `bl` (fn_3_C56E8 dropped to 31.7%) until its GX setup became a call to
  fn_3_C4B80, which the target also inlines.
- **Not every copy should go.** Calling the real function scored lower for
  bobOmbDerby bOD_UpdateBatterAIInputs (96.2 -> 93.5), spriteAnimations/fn_3_BC888 (99.63 -> 99.45),
  starDash_stopAllSparks (93.1 -> 67.5, the `extsb` of the inlined `s8` argument sinks below the
  call) and practice_mainMenu_stateHandling/notReferenced (97.15 -> 96.81). In bobomb_derby and
  barrel_batter, the target keeps `&g_Minigame` in one callee-saved register across several
  inlined helper bodies, while ours rebuilds it in each. That pattern is still unexplained.
- **Two same-size twins: tell them apart by one branch target before converting.** In fielder.c,
  fn_3_308B8 (now setFielderAutoCoords_onlyFlagIfMoving) and setFielderAutoCoords are both 0x1A0 and
  differ only in whether `goingToAutoLocationInd = 1` sits inside the else-arm. A fuzzy body match put
  fn_3_308B8 in 25 hosts. Checking whether the then-arm's `b` lands on `li r0,1; stb r0,0x1d9` or past
  it showed that all 25 inline setFielderAutoCoords, and only fn_3_30A58 and fielding_prePitchAutomovement
  (its address neighbours) inline fn_3_308B8. A function that other units call with `bl` was the main
  inlined helper of its own unit: 27 hosts and 51 copies (32 pasted blocks, plus 19 calls to a
  pointer-form `static inline`). No host lost score (+0.04 .text, 3 new
  100%). A copy whose argument came from a struct field (`out.x`) scored higher with the field first
  copied into a local (`x = out.x; f(i, x, z)`) than with the field passed directly (fn_3_4597C, 99.31 vs 99.54).

### Findings from the minigame_framework second pass (2026-10)
Unit `game/game/minigame/minigame_framework`, 41 -> 49 of 59 functions at 100%.
- **A chained zero init picks MWCC's other unroll form for a variable-trip copy loop.** With
  `offset = 0; ... for (k = 0; k < count; k++) q[offset + k] = order[k].idx;` MWCC unrolls with
  the `cmpwi n,8; subi r,n,8` form and recomputes from `k` in the remainder. The target's
  `srwi. r0,n,3; mtctr; ... andi. r,n,7` form with both pointers carried into the remainder came
  from `offset = k = 0; ... for (; k < count; k++)` (minigameCharLoadQueueUpdate 87.5 -> 96.9).
  `for (idx = j = 0; ...)` did the same kind of thing in minigames_setupChallengeRoster (93.8 -> 97.0).
  Down-counting loops also give the `srwi.` form, but without the strength-reduced indexing.
- **No `i >= N` test after an unrolled search loop: `goto` out of the loop.** When the target's
  unrolled scan falls through to `li r3,0; blr` and the found-handler sits after it,
  `for (...) if (c) goto found; return FALSE; found: ...` matched (checkForPauses 96.8 -> 100).
  Measured first: `break` + `if (i >= 4) return FALSE` 96.8, `if (i < 4) {...}` 96.2, handler
  inside the loop 49.9 (the loop stops being unrolled).
- **MWCC does not move stores across calls, so read the store/call order straight off the
  target.** Four `state = N; sndFXStartEx(...)` pairs in minigameCharSelectUpdate had been drafted
  as call-then-store (97.2 -> 99.4 after reordering them with s32 counters).
- **`(c ? 2 : 1)` and `(c) + 1` compile differently** as a multiplier (minigames_0x26 99.03 -> 100).
- **`s32` vs `int` counters can need to change together.** minigameCharSelectUpdate: `s32 i, j, k`
  98.17; any one of them alone scored lower than all-int. A blanket int->s32 over the whole file
  regressed four 100% functions, so measure per function.
- **One counter for consecutive loops in a small callee** (`i` reused instead of a separate `j`)
  fixed the register swap in every inlined copy of minigameFillGrandPrixScoreInput.
- **S1 `static inline` copies of real functions can often go.** With `-inline deferred`, calling
  minigames_fillRoster, minigameBuildResultEntry and minigames_0x25 from earlier-defined callers
  still auto-inlined them, and the standalone minigames_fillRoster went from 98.3 to 100 once it was
  no longer a wrapper around the inline. minigameAwardCoins (420 bytes) stays a `bl`, so its
  inline copy is still needed.
- **Re-run declaration-order sweeps after structural fixes.** The same 9-local sweep that gave
  +0.2 before the loop fix gave +1.2 after it (minigameCharLoadQueueUpdate, then two store-order
  tweaks reached 100).
- **Inverted test found by a one-instruction diff:** the char-select late-join scan read
  `selectSlotState[i] == 0` where the target has `beq skip` (`!= 0`). A lone `beq`/`bne` swap at
  the same label is worth checking as a draft bug, not just a branch-layout difference.
- Not solved: the qsort comparators (`cmpw; beq; subf; blr; subf; blr`) keep MWCC's
  conditional-return peephole (`subf` hoisted + `bnelr`) in every source form tried, including
  ternary, result variable, index locals and `#pragma peephole off`.

### Findings from the match_flow second pass (2026-10)
Unit `game/game/match_setup/match_flow`, 25 -> 44 of 47 functions at 100% (.text 98.14 -> 99.57).
- **A counter increment written before a constant store.** When the target emits
  `stb rK,const; ...; addi rX,rX,1; sth rX` and ours has the increment's temp in r0 and the
  constant in a numbered register (or the reverse), swap the two statements: write `n++` first.
  MWCC still schedules the constant store first, but the register numbering follows source order
  (uncalledRunnerUpdateRelated 95 -> 100, gameSimulationFunction, exitToMenuControl).
- **`if (x < 0) x = -x;` vs `__abs(x)`.** Both give `srawi; xor; subf`, but the MWCC intrinsic
  puts the result in a fresh register (fn_3_5B41C 99.59 -> 100, newPitch 95.1 -> 99.0).
- **An extern array declared too small changes store scheduling.** `highLevelSimulationFlag` was
  `u8[2]` while code stores `[2]` and `[3]`; with the real size `[4]`, the natural store order matched
  and two other functions moved too (exhibitionGameTransitionCalculations, inningChange). Check the
  declared bound against every constant index before permuting statements.
- **`a == b` operand order is visible** in the `subf` of the CLZ idiom: `winnerCd == humanTeamNumber`
  and `humanTeamNumber == winnerCd` differ, and two functions sharing the test needed different orders.
- **Check every file-local `extern f(void)` against the headers.** The disk loaders take the load
  index (target keeps the loaded value in r3 for the call), exitMenu_main takes the buttons and
  forwards them, and the header prototype `(u8 scene, s8 charID)` with a `u8` table produced the
  target's `lbzx r0; extsb r4,r0`.
- **A walk-off test of `score < base + count`** is strength-reduced into its own induction register;
  a hand-kept `runs++` total allocates differently (handleDeadBall 98.98 -> 100).
- **A function inside a `#pragma dont_inline` block can still be the body the target inlined.**
  configureTeamsForGame_Unused has no `bl` anywhere; moving it out of the region and calling it from
  gameInitRelated fixed that caller (90.5 -> 100 with an unrolled 2-trip clear loop). Its body then
  had to fold the constant argument (`teamBatting = arg1 ^ arg0`, not a re-read of both fields).
- **`inMemRoster[0][i]` and `((CharacterStats*)inMemRoster)[i]` flip the final `add` operands.**
- **Register liveness exposes draft bugs.** A `li r5,0` scheduled before a `bge` whose fall-through
  also reaches the join means the assignment is unconditional (checkIfPlayOver); a value loaded once
  and decremented in each flag block means a running variable, not a recomputation
  (startChallengeModeMatch).
- Not solved: newPitch (one constant takes r3 instead of r8 after the inlined practiceNewBatter),
  processScoreChanges (every temp one register higher; the target's unrolled u64 sum needs r28) and
  startChallengeModeMatch (the target re-materialises `g_Runners` in each runner block).

### Near-miss pattern sweep findings (2026-10)
A bounded retry of twelve game units that were one function short of 100%, using the match_flow
patterns. No unit reached 100%, but five functions moved and two non-target functions matched.
- **Paid off: the value-form `==` predicate.** `subfic; cntlzw; srwi.; beq` on `rec->unk69[0] == 2`
  is a `static inline BOOL f(UIRecord* rec) { return rec->unk69[0] == 2 ? TRUE : FALSE; }`
  (an if/return TRUE/return FALSE body is identical). It lifted draw_ongoingStarGuageHud
  98.45 -> 99.03 and matched ballLandingMarker_update (hud_scoreboard, all three tests needed) and
  practiceInstruction_update (practice_scene, only the second test). The units now share the
  name `hudRecordFinished`. Sweeping each `unk69[0] == 2` site one at a time found them in minutes;
  minigame_hud, toy_field_hud and minigame_models had no further sites that moved.
- **Paid off: unfolded constants mean inlined or multi-def code.** `li rN,K; mulli/slwi` on a value
  that is constant in the source, or `li rA,0; mr rB,rA` for a loop start, means the value reached
  the loop optimiser as a variable, not a literal.
  - rep_3E00 fn_3_166448 (82.9 -> 93.6): `offsets = packed + i++` after the unrolled files loop
    (a post-increment use keeps `i = 3` as `li r0,3; slwi`), and the effect start block as a 1-trip
    `for (j = 0; j < 1; j++) { ...; if (j == 0) effect->active = 1; }`, which keeps `j = 0` and the
    constant 1 in callee-saved registers across the calls like the target.
  - sta_c0 loadMarioStadium (97.12 -> 97.74): `slot = 0; call(slot); slot++; ...; slot++;` instead of
    `slot = 2` gives the target's `li r25,2; mulli r24,r25,0x90`; the light loop and each crowd fill
    as no-argument `static inline` helpers give the `li; mr` loop starts. The same light-loop helper
    on the other six stadium loaders moved each by under 0.25 either way, so it is not a general
    fix there.
- **Loop increment order follows source order.** Moving `slot++` from the for-increment to the end of
  the body (and `cfg++` next to `count++`) fixed the order of the `addi`s at the loop bottom.
- **Did not apply here:** `__abs` (shuffleU8Array's randomIntGameAbs got worse with it), extern sizes
  (all checked against symbols.txt and already right), and local prototypes (none wrong). The
  `highLevelSimulationFlag[4]` fix in pitcher.c and animation_dispatch.c changed nothing (both index
  only [0] or [1]).
- **Still stuck, all pure register swaps with the instructions already right:** calculateChemistry
  (lbz/mulli scheduling), spline3D_evaluate (count vs an array base), maybeProcessTeamData,
  animateOffence, setFielderValues (target keeps `&g_GameLogic` in r30 for one access),
  shuffleU8Array (the inlined shuffleIntArray's k), minigameUpdateResultsScene, and
  wallBallInitializeValues (the coin loop's unfolded start guard). Exhaustive declaration-order
  sweeps (shuffleIntArray 720 orders, animateOffence 24, maybeProcessTeamData 120) found nothing,
  so these are not declaration order either.

### Findings from the m_sound second pass (2026-10)
Unit `game/game/sound/m_sound`, 32 -> 38 of 39 functions at 100% (.text 99.39 -> 99.996).
- **A function that is never called, but whose inlined copies all share the same register swap, may be a
  macro at the call sites.** addToCircularBuffer has no `bl` anywhere; every inlined copy had its queue pointer
  and head index in swapped registers, and no `static inline` form (void/BOOL, nested ifs, early returns,
  block-scoped locals, param types) changed that. A hand expansion with the arguments substituted textually
  did, so the callers now use `ADD_TO_CIRCULAR_BUFFER(a1, a2, a3)` (transitionToReplay and fn_3_8C104 to 100,
  soundControl +0.14). The inliner's parameter copies are what move the colouring.
- **A `long` parameter keeps an inlined constant unfolded; a macro folds it.** soundControl's inlined
  playOverSounds keeps `li rN,-1; cmpwi rN,0`, which only `void playOverSounds(long frames)` reproduces, while
  fn_3_90434 has the folded form. The resolution was a FADE_OUT_MUSIC(frames) macro: playOverSounds' body and
  fn_3_90434/fn_3_903B8 (constant frames) all use it.
- **`x = x * s;` / `x *= s;` vs `x = load * s;` changes the int-to-float stack temp order.** playCharacterSoundScaled had the
  vol/reverb temps mirrored (68%) in every single-expression form. Separate load + compound statements gave
  the right slots (99.6). The last register matched with `static inline int f(int level) { level = level * s;
  return level; }` on both values. The same helper written as `return level * s;` scored 56.
- **Adjacent statement order is still the strongest lever.** soundControl's last 0.19% was
  `_28 = 0; _20 = track; trackId = track;` (the trackId copy last, out of 6 orders). fn_3_8C2DC matched with
  the float division before the flag store. adjustBallSoundEffectBasedOnHeight matched with
  `clamped -= min; ratio = (f32)clamped / (f32)(max - min);` instead of one expression.
- **One local reused for two different fields can be the original.** soundControl's practice block stores
  g_GameLogic.secondaryGameMode into the same u8 `status` local used for gameStatus elsewhere (99.20 -> 99.27).
  Reading g_Stats.replayInd once into a local that a later test reuses fixed which value got r0 (-> 99.64).
- **Split an index that is overwritten by the value it indexes.** fn_3_8C104 used one `int value` as the 0/1
  table index and then as the looked-up volume. The target passes the volume to a `(u8, u8)` callee without
  truncation and tests it with `clrlwi.`, so it is a separate `u8 value` (98.52 -> 99.66).
- **Where the sign extension sits matters.** processSoundReplayQueue: `vol = rec.arg3; vol = (s8)vol;` as two statements and
  `switch ((s8)bytes[...])` with no `cmd` local each kept the target's in-place `extsb` (98.85 -> 99.82).
- **`lwz rD, sym@l(rB)` vs `addi; lwz rD, 0(rA)` for a member at offset 0 is a register-allocation side effect.**
  No source shape moved it; it followed once the surrounding locals coloured like the target.
- Carried over from the first pass: `if (a || b || !c) return;` gives `bne next; b exit` for the last operand;
  `x = cond ? TRUE : FALSE` tested later gives `neg; srwi.` (`cond ? FALSE : TRUE` gives `cntlzw; srwi.`);
  and with `-inline deferred` the pooled `.rodata` follows reverse source order, so write the functions in
  descending address order before judging `.rodata`.

## Logic pass findings (53 structural functions)

Chunk 1 (ball_fielder_collision, collision_primitives, play_result_tracking, runner, charge_effects,
camera, camera_script; 2026-10).

- **A cast at the use site picks indexed addressing; a typed pointer picks add + displacement.**
  `((T*)voidPtr)->arr[i]` and `((T*)bytePtr)->arr[i]` compile to `slwi; addi rT, rI, off; lwzx/stwx`,
  while the same access through a pointer whose *declared* type is `T*` (a struct field or a parameter)
  compiles to `slwi; add rT, base, rI; lwz off(rT)`. When the target shows the add form, type the
  pointer at its declaration instead of casting it. In camera_script this meant
  `unkStructPtr._0000` as `struct CamScript*` (it had been a two-field stub cast by a `CTX` macro)
  and `fn_3_1054D0(CamScriptHdr* script, ...)`: 92.4% -> 99.8%, and it took `camera_replay` to 100%
  as a side effect. It is the converse of the "raw byte-offset indexing" entry above.
- **Two arrays at the same stack offset means a union (or deliberate buffer reuse).** In `fn_3_19FA4`
  the target writes the angle samples to the slot the spline control points occupied, through the
  callee-saved register that held `&points`. Because the stores go through that pointer, the bound is
  re-read every iteration and the loop is not unrolled. Separate arrays (even in disjoint block scopes)
  got their own slots and an unrolled loop; `union { Vec points[5]; f32 anglePoints[4]; }` reproduced
  both (74% -> 96%). Check the target's frame size and array offsets before chasing loop shapes.
- **Interpolation order is behaviour, not shape.** `a + (t / n) * (b - a)` and `t * (b - a) / n + a`
  round differently. The target's instruction order (`fmuls`, then `fdivs`, then `fadds x, a`) shows
  which one was written, so read it off the asm. The operand order of the final `fadds` also follows
  the written order (`x + a` vs `a + x`).
- **Fused vs unfused float updates.** `p.x += (c - p.x) * k;` fuses to `fmadds`. Where the target
  has `fmuls` + `fadds`, and computes both deltas before either store, write the deltas into locals
  first (`dx = ...; dz = ...; p.x += dx; p.z += dz;`). The rounding differs, so this is a correctness
  fix as well as a match fix (gameplay_Camera).
- **A shared view-update inline can hide a per-branch difference.** `fn_3_19FA4`'s draft folded the
  `_0010` frame counter increment into an inline called by two branches; the target only advances it
  on the spline branch. When an inline is used by several callers, check that every statement in it
  appears at every call site in the target.
- **`lbzu` + a reload in a saturating `if (x < 0xFE) x++; else x = 0xFF;` means the field was
  written out directly, not through a `u8* stat` pointer local** (postPlayTrackStats 90.4% -> 95.5%).
  The same function's reload-after-store history shift was an unrolled `for (i = 4; i > 0; i--)`.
- **A `u8` field converted through `xoris 0x8000` was written `(int)field`**: it uses the signed
  bias constant and shares it with a neighbouring int conversion. Our implicit promotion took the
  unsigned path and added a second pool constant (fn_3_16C548, .rodata 95% -> 100%).
- **`cmplwi` on a loop countdown or flag means `u32`, not `int`/`BOOL`** (checkStatiumHazardCollisions).
- **`ble` straight to the exit, where ours has `cror; beq`, is `!(x > t)`**, which also sends NaN down
  the return path as the target does (processBallFielderCollision).
- **Unsolved: a branchy select evaluated after all the other call arguments.** applyChargeAnimationEffect's
  target computes every argument, then `li 0x18; beq; li 0x17` right before the `bl`. Every ternary
  is branchless, and the if/local/inline forms are branchy but evaluated first (6 forms logged in its
  checkpoint).

Chunk 2 (camera_script, star_missions, hud_scoreboard, match_end, match_transitions; 2026-10).

- **`addi rI, rI, N; slwi; add; lwz -8(rX)` is "the record before `first + i + N`".** The target
  never folds the `- 1` into the index. `REC(scene, col - 1 + 6)` folds to `+5` with `lwzx`.
  `(&graphicsRelatedArray[first + col + 6])[-1].object` (a `REC_PREV` macro in hud_scoreboard)
  reproduces the add-then-negative-displacement form. That fixed every inning-column record in
  manageScoreboardGraphic (96.5% -> 99.2%, size exact) and the base markers in
  drawDiamondMiniMap_ongoing. Scratch tests of the same expressions fold differently, so measure
  this in the real unit.
- **A condition MWCC should fold but the target computes as a value is `(a == b) ^ 1`.** In
  decideScoutFlagMission an always-true `else if (!(a == b))` is folded away by every logical form
  (`!`, `== FALSE`, `!= FALSE`, an inline returning `a != b`). Only the explicit xor kept the target's
  `subf; cntlzw; srwi; xori; cmpwi` (98.3% -> 99.4%).
- **Separate induction registers per field mean the source indexed `array[i].field`.** In
  scoutMissionProgress_init the target keeps `&entries[i].max`, `.achieved` and `.amount` in their
  own registers and saves four GPRs. A walking `entry++` pointer collapsed them into one base
  (88.3% -> 99.8% with direct `scoutState.entries[i]` indexing). Also, `base + k + 1` and
  `base + (k + 1)` associate differently.
- **A field reloaded at a fixed displacement inside an unrolled inner loop means a per-iteration
  pointer.** In starMissionsMinigamesTotalPoints, `StarMissionRequirement* r = &req[j];` gave the
  target's `lha 4(r3)` in every unrolled `k` iteration; `req[j].flags` was strength-reduced to a
  separate pointer instead (90.9% -> 98.2%, together with an inlined beat-character helper detected
  from the `li; mr; mr` zero pair).
- **A loop-invariant sum the target computes before the loop was written as its own variable**
  (`outsNeeded = storedOuts + 2`; MWCC did not hoist `outsBefore + 2` out of the fielder loop).
- **Inline-or-pasted is a per-site choice, but a sweep can mislead.** fn_3_FDB30's four captain
  lookups all show the inline `li; mr` zero pair. Making them inlines removes the last structural
  difference, yet scores 99.71 against 99.74 for the pasted loops, purely on register colouring.
  The shape-correct version was kept.
- `s32 i` restored the fixed-trip guard (`li 1; cmpwi 14; bge`) again, in an inline helper
  (setMiniMapAlpha).
- **Not solved: a `(table + 9)` base hoisted for `table[id].field[k]` reads, plus an `extsb` before a
  byte store** (scoutFlag_checkMissionSuccess, 4 forms logged). The target routes the s8 value through
  an int, and an `int` local reproduces the `extsb` at one of the two sites.

- **Pooled static data, third data point (`piranhaPanic_emitFielderHitFire`, 73% -> 100%).** The target
  reached three tables as `addi rX, base, 0x254/0x23C/0x13C` off one `minigameFxData` base. Two
  alternatives were measured and both lose: direct access to separate *global* objects (75.7%; MWCC
  emits a separate `lis/addi` per global, it does not pool them) and one merged global struct (73.4%;
  member offsets fold into the load displacement). Only splitting the block into file-`static` objects
  at the boundaries the target's addressing shows (symbols `scope:local`) reproduces it.

- **A unit whose splits.txt lists `extab`/`extabindex` needs `extra_cflags=["-cpp_exceptions on"]` on its
  `Object(...)`** (DOL `unk` lib; the C3 lib already has it in its group cflags). Without it the object
  emits no exception tables, so `extab` scores 0% and the unit cannot be flipped to Matching even at
  100% `.text`. Adding it changed no `.text` in any of 51 units (2026-10 first-pass follow-ups).

Chunk 3 (match_transitions, versus_screens, chain_chomp_sprint, minigame_effects, minigame_framework, minigame_hud; 2026-10).

- **`frsp f1, fN` just before `bl cos`/`bl sin` on a double angle means `cos((f32)angle)`.** The
  argument is rounded to float and then promoted back. An `f32 angle` local moves the `frsp` to the
  store instead. This is a real rounding difference (piranhaPanic_initBombExplosion).
- **`lha; extsh.` for a `>= 0` test on an s16 field is the `(s16)` cast** written at the test
  (loadRunnerActors). A plain field compare, an s16 local, or `(int)` all give `cmpwi`.
- **`cmplwi` on a game-mode local means `u8`** (loadRunnerActors 95.3% -> 99.4%). It also brings
  back the `clrlwi` after the range fold's `subi`.
- **Unsolved, recorded so nobody re-derives it.** (1) A target that keeps a constant table base in a
  callee-saved register across a `rand()` call, re-materialised at each statement
  (wallBall_placeBounceParticle and its inlined copy). (2) A value-materialised `x == 0` test
  (`cntlzw; srwi.; beq`) that every logical form folds away (minigameHudBodPitchRoulette; compare
  chunk 2's `^ 1` trick, which only covers `!=`). (3) The target re-reading struct fields between two
  identical counts with no store in between (fn_3_22ABC / chooseVsScreenSituation).

Chunk 4 (mm_ParseCommonArchive, star_dash, practice_model_load, practice_scene, sta_c1, sta_c2, sta_c3; 2026-10).

- **Pooled statics, two more cases (sta_c1, sta_c2).** A `static` struct or a `u32[]` blob that the
  target addresses at several unrelated displacements off one pooled base is really several static
  objects. Splitting it into separate `static` objects with matching `symbols.txt` entries
  (`scope:local`) helped loadBowserCastle (90.79% -> 92.49%), loadWarioPalace (+0.84) and
  palaceMinigameObjectLoading (+1.12). `.bss` statics are laid out in **reverse** declaration
  order and `.data` statics in forward order, so declare them to match. In sta_c2 the split alone
  regressed one caller; indexing the new arrays directly in its loops, instead of through a
  pointer into the old blob, recovered it.
- **A materialised `cntlzw; srwi.; beq` test reproduced by an inline returning `cond ? TRUE : FALSE`**
  (fn_3_C3C2C 96.95% -> 98.67%). This did not work for minigameHudBodPitchRoulette (chunk 3), so try
  it but do not rely on it.
- **`addi; slwi; lwzx` record access is a byte-offset macro.** Writing
  `*(T**)((u8*)base + ((first + i) << 3))` reproduces it where `base[first + i].ptr` gives
  `add` plus a displacement (practiceMenu_charSelect_update -> 100%).
- **`cmplwi` on a call result means the callee returns an unsigned type** (sD_AIPathBlocked: `u32`, not `BOOL`).
- **Telling an inline from pasted code by its zero.** If one `li 0` is shared via `mr` between the loop
  index and the stored value, it is an inline helper. If the index and the value each get their own
  `li`, the loop was written out at the call site (sD_UpdateAI's AI input clear).
- **Assign a derived table pointer where it is first used, not in its declaration initialiser.**
  `u8** animTable = (u8**)(hugeAnimStruct + 0x6C);` at the top of the function moves the `addi`
  early and keeps it live. Assigning it just before the store matches the target
  (loadBowserCastle, loadYoshiPark).
- **`s32` vs `int` loop counters are not interchangeable** (`s32` is `long`). loadYoshiPark gained 1.8
  points from `int k` -> `s32 k` alone, so sweep both when a counter's register allocation is off.
- **Unsolved.** (1) mm_ParseCommonArchive: the target folds the post-loop `offsets[i++]` increments
  into constant displacements, and 5 forms did not reproduce it. (2) practiceModel_setup: the target
  re-loads `files[]` after storing it (no store-to-load forwarding); 17 hypotheses are logged in its
  checkpoint. (3) fn_3_D4780: the `fnmsubs` operand order for the amplitude term was not reproduced.

Chunk 5 (sta_c4, sta_c5, sta_c6, stadium_draw; 2026-10).

- **How to read pooled-object addressing in a diff.** When MWCC addresses a static object off the
  unit's pool base, a field at offset 0 folds into the base displacement (`lfs f0, 0x25c(r30)`), and
  every other field goes through `addi rX, base, objOffset` plus the field displacement
  (`lfs f0, 0x4(rX)`). Ours folding all of them (`0x260(r30)`) means our struct spans several real
  objects. Split it at the `addi` offsets. This gave the largest wins in this chunk: sta_c5's
  launch/water statics (cutscene 95.65% -> 98.89%, fn_3_EE388 89.37% -> 97.80%), the
  barrel table and anim banks (loadDKJungle +1.7), and stadium_draw's tables (drawStadiumObjects
  88.17% -> 96.80%). Splitting only part of a block can make things worse: a view-struct access
  to the rest stops the new object from being pooled, so it is addressed by name. Split everything
  the function touches.
- **The pool base's symbol tells you where the unit's `.data` starts.** In stadium_draw the target's
  base was `FrameCountOfEntireGame` (.data 0x228), 0x14 bytes before the split's `.data` start.
  That object belongs to the unit. Moving the splits.txt start to 0x228 and defining it there
  (a `{0}` aggregate goes to `.data`) was what made the table splits work. The auto gap unit
  `auto_04_00000228_data` disappears, so `regchk` reports it MISSING. That is expected; total
  matched data went up by exactly its 20 bytes.
- **`cmpwi 3; bge D; cmpwi 1; bge B; b D` is a `switch` with `case 1: case 2:`**, not an `if` range
  check (an `if (x < 3 && x >= 1)` gives `bge; blt`).
- **`clrlwi 16` on a `GXGetTexObjWidth/Height` result applied late, at the division, means the
  original used the SDK's `u16` return type.** This repo's prototypes say `u32`. `(u16)` casts at the
  uses took fn_3_42CC from 96.69% to 100%; `u16` locals truncate too early and score lower.
- **`?: TRUE/FALSE` inline, second hit:** sta_c4's fn_3_F8E20 (98.28% -> 100%) uses the same
  `scale == 2` finished-animation test as sta_c1's fn_3_C3C2C.
- **Behaviour bugs found by diffing immediates and branch-only paths:** loadDKJungle read `n`
  uninitialised in minigame mode (the target zeroes it on entry). fn_3_4F90 reset the GX line
  width to 18 instead of 6 after the outline.

Chunk 6 (stadium_draw, stat_book, stat_tracking; 2026-10). updateStadiumFileHeaders was already
100% in the baseline. compileStatsForBook and initializeStats stayed stuck.
- **`lis 1; subi` for a 0xFFFF store means the element type is `u16`.** An `s16` store folds the
  constant to `li -1`. In initializeStats a `u16*` store reproduced the target's 18-store unroll,
  but it scored lower on register allocation, so it was not kept (logged in the checkpoint).

### Logic pass summary (all 53 functions)

- **Matched: 7.** fn_3_16C548, runnerAI_startSteals, animateShadows_nonBall,
  piranhaPanic_emitFielderHitFire, practiceMenu_charSelect_update, fn_3_F8E20, fn_3_42CC.
  One more (updateStadiumFileHeaders) was already 100% when reached.
- **Improved: 30.** Typical gains were 1-10 points. The largest: runnerAI_startSteals 60.92 -> 100,
  piranhaPanic_emitFielderHitFire 72.58 -> 100, fn_3_19FA4 72.88 -> 96.49,
  scoutMissionProgress_init 88.34 -> 99.79, drawStadiumObjects 88.17 -> 96.80,
  fn_3_EE388 89.37 -> 97.80.
- **Stuck: 15.** Each has its forms logged in its unit checkpoint. Almost all are pure register
  allocation, CSE or scheduling with identical logic: a base kept live across calls, values re-read
  per iteration with no CSE, a materialised compare, folded post-loop increments, `fnmsubs` operand
  order, and zero registers shared between a vestigial loop guard and a value.
- **Behaviour bugs fixed: 3.** fn_3_19FA4 advanced the spline frame counter on the linear path and
  used the wrong lerp association. loadDKJungle read the pool index `n` uninitialised in minigame
  mode. fn_3_4F90 reset the GX line width to 18 instead of 6 after drawing the outline.
  **Minor numerical differences fixed: 3.** processBallFielderCollision (an inverted compare that
  only differs for NaN), gameplay_Camera (fused multiply-add where the target rounds between the
  multiply and the add), piranhaPanic_initBombExplosion (cos/sin argument not rounded to float).
- **Patterns that paid off most:**
  1. Splitting pooled statics into their real objects. Read the `addi base, off` vs folded-offset
     shape; it was the single biggest lever, across sta_c1, sta_c2, sta_c5, stadium_draw and
     minigame_effects.
  2. Integer widths and signedness read off `clrlwi`/`extsh`/`cmplwi`/`lis;subi`.
  3. `switch` vs `if` range-check shapes.
  4. Inline-helper shapes: `? TRUE : FALSE` and shared vs separate zeros.
  5. Diffing immediates and branch-only paths, which is where every real behaviour bug showed up.

## Last resort: `#pragma opt_dead_assignments off` around one function (batter.c `calculateContactAndHitType`)
**When a whole basic block has identical registers but the load order and `fmadds` operand order are wrong, re-sweep function-scoped pragmas.** In batter.c the unrolled threshold loop loaded `arr[0][i]` before `arr[1][i]` and emitted `fmadds d, frac` under every source spelling (about 30k permuter candidates across sessions 14-16). Wrapping the function in `#pragma push` / `#pragma opt_dead_assignments off` / `#pragma pop` made the loop exact. It also let the plain `inv_lerp` helpers match without the parameter-assignment tricks used earlier. Setting the pragma for the whole file regresses 7 other functions, so it has to stay function-scoped.

**Resolved without the pragma (session 18): reuse an existing local.** The real shape was variable reuse. Writing the loop's difference into a local the function already assigns elsewhere matches with no pragma: `xPosFromPerfect`, renamed `diff`, so `diff = arr[1][i] - arr[0][i]; thr[i] = arr[0][i] + (contactSize / 100.f) * diff;`. A fresh block-local `f32 range` does not match. A variable with more than one definition is not forward-substituted, so `hi - lo` stays its own assignment and `hi` is loaded first. That is what turning off dead-assignment elimination was imitating. **Before reaching for an optimiser pragma, try storing an intermediate in an already-used local of the same type.** batter.c ships pragma-free.
The parallel mini harness that found this is described in the batter checkpoint (session 18). It compiles one function in a standalone translation unit and diffs its instructions against the target asm, which makes about 25k candidates per hour cheap.

**This is a last-resort strategy, not a model of the original source.** No other game file uses an optimiser pragma, and there is no plausible reason a developer would turn off dead-assignment elimination for one function. Treat a match that depends on it as a fakematch: say so in the source comment, keep the checkpoint open, and only reach for it after source-shape levers (inlining, temps, types, prototypes, statement order) have been exhausted. When a real source shape is found that matches without the pragma, remove the pragma.
- **Re-sweep once the other clusters are fixed.** Session 7 swept pragmas while the function was at 97.88%, so a pragma that fixed one cluster but disturbed another scored as a loss. Grid pragma x source shape together.
- **Probe pragma legality by grepping the compiler output for `illegal`.** Grepping for `pragma` also matches the echoed source line, so every pragma looks legal. MWCC 2.6 accepts `opt_dead_assignments`, `opt_lifetimes`, `opt_loop_invariants`, `opt_strength_reduction`, `opt_propagation`, `opt_common_subs`, `opt_unroll_loops`, `ppc_unroll_instructions_limit N`, `ppc_unroll_factor_limit N` and `scheduling 601/603/604/750`, among others.
- **Inline helpers that assign to their own parameters change argument load order.** A parameter that is used once is substituted into the expression; one that is used twice or assigned to is kept as a temp and its load is hoisted. This got the function from 97.88% to 99.77% before the pragma was found.

#### Follow-up leads (after the 53-function pass)

1. **(u16) texture-size casts:** did not apply beyond fn_3_42CC. It is the only stadium_draw
   function that calls `GXGetTexObjWidth/Height`. fn_3_3BE8 and fn_3_3EE8 read sizes from the
   texture record (`lhz`).
2. **`FrameCountOfEntireGame` is a struct, not a scalar.** It is the 0x14-byte first .data object
   of stadium_draw: frame count, a per-frame counter, two ball random-int copies, and the
   loading-done flag at +0x10. Seven files declared it four different ways. It is now one
   `GameFrameCounters` type in `stadium_draw.h`; every unit compiles identically. When
   one symbol is declared differently in several files, look at all the users' offsets before
   picking a type.
3. **A copy struct can have a different element type from its source.** `StatsScreenScores` keeps
   `u16` copies of `g_Scores`' `s16` scores. Retyping the shared `ScoreStruct` regressed about 50
   functions. A separate `u16` type used only by the copy improved initializeStats
   (92.65 -> 93.83), postPlayTrackStats (98.41 -> 98.77) and endOfGameStats_MVP
   (99.88 -> 100). initializeStats needed the total and the 18 innings cleared separately: under
   `u16` the single 19-entry loop scored 84.
4. **Pool-base register numbering (sta_c5):** unsolved. A scratch file reproduces our assignment
   (data base r31, bss base r30). Definition order, first use, globals vs statics, reference
   counts and compiler versions 2.0-2.7 do not change it.

### Four-file pass findings (2026-10)
game_math, bobomb_derby, free_fielding_practice, ball_visuals. 12 functions matched, none of the
units reached 100%.
- **Check `SQRT2_LINKAGE` first in any unit that calls `dolsqrtf2`.** game_math was missing the
  define, so `_half`/`_three` sat at the head of `.rodata`. That one line took `.rodata`
  95.56 -> 100 and matched 14 float functions.
- **`if (x < 0) x = -x;` is not `x = ABS(x)`, and neither is `__abs(x)`.** All three give
  `srawi; xor; subf`. The ternary macro and `__abs` put the result in a new register, and the
  if-form reuses x's register. RandomInt_Sim and RandomInt_Game matched with the if-form;
  `__abs` scored 59.
- **A plain expression macro can beat a `static inline` for a call wrapper.**
  `bOD_launchFireworks(pos, n)` (getCamera, then maybeFireworks) as a static inline left the
  count and `&g_Pitcher` in swapped callee-saved registers. As
  `#define BOD_LAUNCH_FIREWORKS(pos, n) maybeFireworks(pos, &getCamera(0)->eye, n, 1)` it
  matched. A `do { } while (0)` macro with a local scored lower than the inline.
- **A struct pointer local for only SOME accesses decides which base register CSE reuses.** In
  bOD_UpdateBatterAIInputs the target uses the first loop's `&g_Minigame` for the switch's AI fields
  and a separate base for `rosterID`. `MiniGameStruct* mg = &g_Minigame;` used only for those
  three fields matched (96.07 -> 100). Using `mg` for more accesses scored 83-89.
- **Calling the real function fixed a hand copy here, unlike the earlier sweep.** With the `mg`
  fix in place, bOD_AtBat matched by calling bOD_UpdateBatterAIInputs and minigameClearAIControlled
  (both auto-inline) instead of the `bOD_AI`/`bOD_clearAIControlled` copies. The duplicate-body
  sweep had measured the call form lower (96.2 -> 93.5) before the `mg` fix. Re-measure a "copy
  beats call" result after other fixes.
- **A constant-initialised array that the target stores in ascending order, with the bound
  shared with `mtctr`, is a loop.** `for (i = 0; i < 4; i++) slots[i] = i + 1;` (unrolled by
  MWCC) matched practiceRelated. Four explicit stores scored 96.3 in either order.
- **Declaring a block-scoped pointer at function scope moves it to another callee-saved
  register.** freeFieldingPracticeLoadCharacters matched with `MinigameSelectSlot* slots`
  declared first at function scope and assigned inside the branch.
- **`a = b = const` shares the constant's register with the loop counter.** In
  setupBallTrailEffect the target stores the display-list byte from the same `li r5,1` that
  starts `i`. `dl[6] = i = 1;` reproduced it. `i = 1; ... dl[6] = i;` did not, because MWCC
  propagates the constant back in.
- **A store of `-1` from a register shared with `s8` stores means the field is `s8`.**
  bobomb_derby's `minigamePlayerSelectedOrder` is `u8` in the header, but every user casts it to
  `s8` and the target stores it from the shared `li -1`. Retyping it gave the right sharing but
  moved every volatile register (98.18 -> 95.60), so it was reverted. Logged in the checkpoint.
- **Still stuck:** pure colour swaps with the instructions already right. These are
  bOD_PrepareNextBatter (a `TRUE` constant and the `&g_Minigame` temp numbered the other way
  round), freeFieldingPracticeSwitcher (a `team * 0x50` schedule), rotate2DByAngle (f4/f5 between
  the sin result and the inlined sqrt argument), RandomInt_Game_Range/RandomF32_Sim_Range
  (inlined RNG argument copy) and fn_3_67EF0 (parameter copies r15-r21 vs r23-r29). Each
  function's checkpoint lists what was tried.

## Menus pass findings (text_110B0, main_menu)

Second pass on `src/menus/text_110B0.c` (.text 95.12 -> 98.77, 2 -> 5 of 7 functions at 100%)
and `src/menus/main_menu.c` (.text 91.42 -> 99.43, .data 100; 7 -> 12 of 15). Neither unit is at 100%, so
neither is flipped. Checkpoints: `build/.match_grind/menus_menus_{text_110B0,main_menu}.md`.

- **`sym+0x8@ha` in the target means dtk merged several small `.sbss` objects into one symbol.**
  Every menu-REL reference to `lbl_803CBCD0` (0x18) was `+0x8` or `+0x10`, and the DOL reads
  `lbl_803CBCD0` itself through `@sda21`, so it is three 8-byte objects. `lbl_803CBBC2` (0xA) was
  the same: a DOL byte scalar plus an 8-byte object at `+0x2`. Splitting them in
  `config/GYQE01/symbols.txt` and indexing the new symbols from 0 was worth +1 to +2.5 points per
  function. teamselect.c and captain_select.c stayed at 100%.
- **A REL unit with a `switch` cannot reach 100% until it owns its jump tables' `.data`.** Every
  switch function scored about 99.8 with only the `jumptable_2_data_*` relocation wrong. Give the
  unit a `.data` range in `config/GYQE01/menus/splits.txt` that covers just its tables, as
  teamselect.c does at `0x19B4`. main_menu has `0x624-0x71C` and text_110B0 has `0x1594-0x15C8`.
  Two more steps are needed. Put the functions in reverse address order (`-inline deferred` emits
  them reversed), so the tables come out in the target's order. End the range at the last table
  (`0x71C`), not at the next 8-aligned object, or the 4 pad bytes cost the section. dtk's
  alignment warning for the range is expected.
- **The `.data` layout shows where the TU boundaries are.** In this block, each original TU's data
  starts with a copy of a debug-menu string table ("BAT FIRST", "BAT LAST", "SELECT DEBUG MENU",
  ...) and has its jump tables at the end. Two results follow. teamSelectScreenMain's table
  (`0xFDC`) closes the css TU's run (`0xEAC-0xFDC`), so that function belongs with text_0323C. The
  stadium functions from `0x112F4` start a new TU (`0x1000-0x15C7`). main_menu addresses
  `lbl_2_data_180 + 0x2C4..` (MenuCommonTexFiles) from one pooled base, so both are this TU's
  statics.
- **Writing `(s8)` on a field that is already `s8` merges two sign extensions.** The target
  extended one load twice (`extsb` for an index, `extsb.` for the compare). With the redundant
  casts, MWCC CSE'd them into one. Dropping the casts matched fn_2_1216C.
- **A raw `((u8 *)&Global)[off] = x` store blocks CSE of other globals. A struct-field store does
  not.** In stadiumSelectControls the target reuses `GameModeSelected` and the spin flag across a
  `playerNumberByPort[idx]` store. That reuse only appeared once the store went through the field.
- **Re-read a global to defeat CSE when the target re-tests a bit.** fn_2_1578 copies the inputs
  to a local, then tests `processedInput & UP` twice. The target computes the `rlwinm.` again
  for the inner test. Reading `Static_Stats_Tables.controllerInputs[0].processedInput` in the
  inner test matched it, and the load is still forwarded from the first read.
- **The callee's size decides between call and copy, as before.** A plain call to fn_2_1A88
  (0x124) inlined into mainMenuRelated. A call to fn_2_1578 (0x288) stayed a `bl`, so its body is
  copied there.
- **Two independent global byte stores: the `lis` order is the written order, even when the
  stores are swapped.** Writing `Static[0x48B4] = 0;` before `lbl_803CBCE0[0] = 0;` matched
  mainMenuRelated's two copies, although the target stores lbl_803CBCE0 first.
- **Hand-unrolled draft code was often MWCC's own unrolling.** fn_2_1A88 (41 -> 100) was two
  loops, `for (i = 1; i < 4; i++) if (port i present) ports[n++] = i;` and
  `while (n < 4) ports[n++] = -1;`. fn_2_11EA8 and fn_2_2BB8 matched once written as plain
  `[t][i]` indexing of `CharacterStats` / `cursorPositions.roster`, with no walking pointers.
- **Still stuck (colouring only):** stadiumSelectControls 93.66 (the target keeps the spin flag
  in r0 for the whole function), loadDemoMatch 97.14, fn_2_2D1C 96.63, mainMenuScreen 99.72 and
  teamSelectScreenMain 99.83 (jump table at `0xFDC` in the css TU's data, plus one register).

## captain_select pass findings

Second pass on `src/menus/captain_select/captain_select.c` (.text 96.23 -> 98.77, .data now owned
and 100%; 9 -> 12 of 17 functions at 100%). Not flipped: four functions are still short. Checkpoint:
`build/.match_grind/menus_menus_captain_select_captain_select.md`.

- **A pooled `base + 0x418` into another symbol means the unit owns that `.data`.** fn_2_16460 read
  three camera vectors as `lbl_2_data_19E8 + 0x418/0x424/0x430` (first field folded, the others
  through `addi`), i.e. three `static Vec`s pooled off the unit's first `.data` object. Giving the unit
  `.data 0x19E8-0x1E24` in splits.txt, defining the data in C and splitting the gap-sized
  `lbl_2_data_19E8`/`lbl_2_data_1DD4` matched it. Objects the target references by name
  (`lbl_2_data_1DD4`, `lbl_2_data_20EC`) are globals; only statics are pooled.
- **The debug-menu text table is 0x2C4 bytes and opens every TU's `.data` in this block** ("BAT FIRST",
  "BAT LAST", ..., "COM4>", a colour table and three small index tables). captain_select defines it as
  `DebugMenuText` with string initialisers; the copy at 0x1E28 starts the next TU. It most likely comes
  from a shared header, so it can move into one once a second unit owns its copy.
- **Value numbering distinguishes `int` from `u32`/`s32` even for the same bits.** In BPress the target
  keeps `c` (the slot) in a callee-saved register for indexing, but re-derives `clrlwi r3, rIdx, 24`
  from the parameter at each call that takes the slot. `int c = (u8)idx` made MWCC reuse `c` there.
  Declaring the callee's parameter `u32` (fn_2_16A74) or writing the argument as `idx & 0xFF`
  stops the reuse (94.0 -> 96.4). `u32 c`/`s32 c` themselves turned the slot loads into `lbzu` walks.
- **`slwi` on a slot index means a 32-bit variable known to be zero-extended; `clrlslwi` means a
  `u8` variable.** `u8 slot`/`u8 c` locals re-extend at every word index. `int slot = ...` (handleInputs),
  `u32 c = (u8)idx` (APress, which also needs `cmplwi`) or a `(u8)` cast at the use site
  (`menuCursors[4 + (u8)gameSetUpStep.portCaptainSlot[port]]`, screenInputs) reproduce the target.
- **Arguments in `r4`/`r5` that the source never sets are a missing parameter.** APress's target
  loaded `charID` into `r4` and `li r5, 1` before `bl fn_8004D4F0`; the DOL body compares `r4`
  against `challengeCaptainCharIDArray` and branches on `r5`. It is the challenge-mode team
  add/remove `(team, charID, add)`, not a one-argument call (behaviour fix).
- **`stopShowingCaptainProfile` takes the port's captain slot.** captainSelectScreenInputs passed
  the port; the target passes the `portCaptainSlot[port]` load it already CSE'd (behaviour fix).
- **Dropping single-use temporaries fixed most of APress** (94.5 -> 99.7): the two
  `mapCaptainCursorPositionToCharID[...]` reads written into the stores directly, and the challenge
  lookup written `(&table[sup * 6])[cursor]` to get the target's add order.
- **`u8 a = port;` for the two animation calls, with the index written `(u8)port`** matched
  fn_2_14BB8 (the cast CSEs with `a` and gives the target's `mr` copies). A `static inline` with a `u8`
  parameter changed nothing.
- **An `f32` temp updated in place reproduces `fadd` -> `frsp` reusing one register:**
  `f32 t = 320.0f + v; t -= 0.1; return t - 320.0f;` (fn_2_14574).
- **Including `UnknownHomes_Game.h` in a menu unit needs `#define SQRT2_LINKAGE static` first**, or
  the `dolsqrtf2` statics shift `.rodata` (100 -> 95.8).
- **The wait loop in checkForNewPlayer is an inlined `loadNewCaptainModelOnCapSelectScreen`.**
  `while (!loadNewCaptain...(menuCursors[5], prev, 1, 1)) prev = menuCursors[5];` replaces a
  goto-into-do-while at the same score.
- **Still stuck:** checkForNewPlayer 94.35 (the target issues two global byte stores before an
  unrelated `menuCursors` load that ours hoists above them; 11 forms logged), BPress 96.38,
  handleInputs 99.48 (`bne next; beq L` for a `goto`), APress 99.74 (a two-register colour swap).


### Menus character-selection first pass, text_7E380 (2026-10-20)

Resumed from e4f81aee without changing other units. All fourteen functions in
`src/menus/text_7E380.c` are now drafted; ten return-only stubs were replaced.
The typed shared stats/settings/challenge structures cover the existing offsets,
and `include/menus/text_7E380.h` now declares the recovered scene/channel arguments.
Only this source includes that header. Keep the unit NonMatching.

Fresh objdiff `.text`: **9.086067% -> 86.574776%**. Exact target functions:
**0/14 -> 0/14**. No scored data sections and no function regressions.

| Function | Before | After |
|---|---:|---:|
| cssUnready | 0.32051% | 83.40385% |
| fn_2_7E860 | 88.55073% | 88.55073% |
| cssReady | 0.31056% | 77.21429% |
| fn_2_7EE7C | 78.72881% | 78.72881% |
| fn_2_7EF68 | 87.10000% | 87.10000% |
| cssRemoveCharacter2 | 0.61350% | 79.74847% |
| cssRemoveCharacter1 | 0.35971% | 77.53237% |
| fn_2_7F714 | 0.94340% | 83.00944% |
| cssSelectCharacter | 0.69444% | 78.70834% |
| fn_2_7FAFC | 0.27397% | 98.02740% |
| captainSelectUnloadCSSLoadRelated | 0.69930% | 97.09790% |
| fn_2_802EC | 0.75188% | 98.75940% |
| fn_2_80500 | 94.81818% | 94.81818% |
| fn_2_805DC | 0.67568% | 97.93919% |

Next serial pass: start with `fn_2_802EC`, `fn_2_7FAFC`, `fn_2_805DC`, and
`captainSelectUnloadCSSLoadRelated` (97–99%). Their zero-step test commonly emits
a direct compare where the target materializes the predicate with CLZ; an inline
BOOL predicate and an explicit u8 boolean cast did not help. The existing detailed
checkpoint is `build/.match_grind/menus_menus_text_7E380.md`.

The inlined first-match roster-slot search is also called with its result ignored
in `fn_2_7F714`; MWCC preserves the target's otherwise dead comparisons. Avoid
removing that call as redundant without checking the original assembly. Record-index
association is per site: left-associating `firstHandle + selected + channel * 9`
improves `cssSelectCharacter`, but changing the same association across all the
callbacks regresses several. Remaining raw step/process fields and selection
positions 9/10 have no established enum; do not invent names without evidence.

Validation: fresh rebuild before every retained diff; all fourteen functions
compared with the session baseline; full `ninja` build and `git diff --check`
passed. No emulator testing, commit or push. Pre-existing untracked
`docs/menus_second_pass.md` and `text_50898_reference.d` were untouched.


### Menus text_7E380 second matching pass (2026-10-20)

Continued the same uncommitted first-pass source. `.text` rose from **86.574776%
to 89.795490%**, with exact functions **0/14 -> 4/14** and no per-function
regressions. No scored data sections. All functions remain implemented and the
unit stays NonMatching.

| Function | Before second pass | After |
|---|---:|---:|
| cssUnready | 83.40385% | 84.10256% |
| fn_2_7E860 | 88.55073% | 100.00000% |
| cssReady | 77.21429% | 78.29503% |
| fn_2_7EE7C | 78.72881% | 100.00000% |
| fn_2_7EF68 | 87.10000% | 99.40000% |
| cssRemoveCharacter2 | 79.74847% | 86.69939% |
| cssRemoveCharacter1 | 77.53237% | 78.98921% |
| fn_2_7F714 | 83.00944% | 93.05660% |
| cssSelectCharacter | 78.70834% | 81.52084% |
| fn_2_7FAFC | 98.02740% | 98.80822% |
| captainSelectUnloadCSSLoadRelated | 97.09790% | 99.16084% |
| fn_2_802EC | 98.75940% | 100.00000% |
| fn_2_80500 | 94.81818% | 100.00000% |
| fn_2_805DC | 97.93919% | 99.93243% |

The four exact functions (`fn_2_802EC`, `fn_2_80500`, `fn_2_7E860`, and
`fn_2_7EE7C`) passed the mandatory readability review and fresh re-diff.

Useful matching findings:

- **A cached field pointer can erase the value-form inline predicate.** The
  `isStepClear` / `isStepActive` inlines return an explicit `condition ? TRUE : FALSE`.
  Accessing `gameSetUpStep[channel + 0xD]` directly at every caller use retains
  the target CLZ sequence; caching `u8 *step` and reading `*step` lets MWCC collapse
  it to a direct compare. This matched three functions. Merely changing the
  predicate's parameter or return width did not solve the cached-pointer case.
- **Keep the final index increment as a statement when the target uses an indexed
  load.** `handle = scene->firstHandle + position; handle += channel * 9;
  handle += 0x22; graphicsRelatedArray[handle]` matched `fn_2_7EE7C` and raised
  `fn_2_7EF68` to 99.4%. Writing the last increment as `[handle + 0x22]` folded
  it into `lwz 0x110`, despite identical arithmetic. A generic record helper
  did not prevent that fold.
- **Copied zero loop initializers suggest an inline.** A shared
  `resetChemistryStars` helper with explicit handle increments raised
  `fn_2_7F714` from 83.01% to 93.06% and `cssRemoveCharacter2` from 79.75%
  to 86.70%. Passing the star count from the caller helped one but regressed
  the other, so the count remains read inside the helper.

Best continuation targets are `fn_2_805DC` (99.93%, one register choice),
`fn_2_7EF68` (99.4%, intermediate handle register), and
`captainSelectUnloadCSSLoadRelated` (99.16%, commuted add operands). Detailed
tried/reverted variants and current source backups are recorded in
`build/.match_grind/menus_menus_text_7E380.md`.

Final verification: full `ninja` build, fresh all-fourteen-function comparison,
and `git diff --check` passed; no emulator testing. Baseline and final audit files
are `build/_menus_sol7E380_second_baseline.json` and
`build/_menus_sol7E380_second_final.json`, with full build output in
`build/_menus_sol7E380_second_full_build.log`. No commit, push, pull, configuration,
or symbol changes; pre-existing untracked files remain untouched.

### Menus text_7E380 parallel Sol pass (2026-10-20)

Three Sol researchers worked on isolated scratch translation units for near
matches, ready/unready, and selection/removal. The manager integrated the verified
changes serially and rebuilt the real object after each integration.

`.text` **89.795490% -> 98.249250%**, exact functions **4/14 -> 5/14**.
All fourteen functions are at or above the starting score; no scored data
sections. Unit stays NonMatching.

| Function | Before | After |
|---|---:|---:|
| cssUnready | 84.10256% | 99.29487% |
| fn_2_7E860 | 100.00000% | 100.00000% |
| cssReady | 78.29503% | 99.62733% |
| fn_2_7EE7C | 100.00000% | 100.00000% |
| fn_2_7EF68 | 99.40000% | 99.40000% |
| cssRemoveCharacter2 | 86.69939% | 94.00613% |
| cssRemoveCharacter1 | 78.98921% | 93.71942% |
| fn_2_7F714 | 93.05660% | 97.20755% |
| cssSelectCharacter | 81.52084% | 97.70834% |
| fn_2_7FAFC | 98.80822% | 99.26028% |
| captainSelectUnloadCSSLoadRelated | 99.16084% | 99.16084% |
| fn_2_802EC | 100.00000% | 100.00000% |
| fn_2_80500 | 100.00000% | 100.00000% |
| fn_2_805DC | 99.93243% | 100.00000% |

- **Counter type can determine unrolling.** In cssReady, `int i` with
  `(s32)PLAYERS_PER_TEAM` as the natural for-loop bound reproduces the target's
  threefold unrolling and initial runtime guard. `s32` is long here; an s32
  induction variable stays rolled, and a plain-int bound loses the guard.
- **Delay narrow casts to the uses that need them.** Widening the CPU captain
  position until UI use sites lets a natural loop emit the exact nine-slot
  lookup. Explicit signed-byte access to the named challenge opponent field
  removes an extra copy in the captain icon transition.
- **Recover inline boundaries around roster handles and completion checks.**
  Staged firstHandle/position/team/offset additions avoid unwanted address
  folding. Small record, handle, and animation wrappers improved selection and
  removal. A chemistry-count helper plus a local-count wrapper preserves the
  differing caller live ranges without duplicating the loop.
- **A proven 0/1 local may need a narrow width.** fn_2_805DC becomes exact with
  u8 for its first completion result; the target already limits it to one bit,
  so no truncation is added. Readability review and a fresh diff passed.
- **Do not infer a parameter width solely from missing caller masking.** An
  s32 extern for teamSelectionSetChemStars improved some scores, but existing
  callee/header use u8 and the target callee entry cannot distinguish the two.
  The compatible u8 declaration remains. Any correction needs coordinated
  callee/header/caller evidence and dependent verification.

All existing exact functions remain exact; only fourteen target functions are
emitted. Existing roster-size constant cleanup was re-diffed with identical
scores. Full ninja build and git diff --check passed; no emulator test, header,
configuration or symbol changes, commit, push, or pull. Pre-existing untracked
files remain untouched.

Baseline/final evidence: `build/_menus_parallel7E380_baseline.json` and
`build/_menus_parallel7E380_final.json`; full build log:
`build/_menus_parallel7E380_full_build.log`. Complete per-worker hypothesis logs,
remaining differences and status table are in
`build/.match_grind/menus_menus_text_7E380.md`.

Next leads: cssRemoveCharacter1/2 for the largest residual gaps, or cssReady,
fn_2_7EF68, and cssUnready for near matches. Preserve the now-correct loop
structure and avoid replaying logged type/index/inline variants.

### Recovered Sol work before origin merge (2026-10-21)

Recovered and rebuilt the interrupted workers' saved source/header candidates.
All previously measured functions retain or improve their scores; full ninja
passed. text_76874 now implements all four remaining stubs and reaches
86.070885% .text, with fn_2_78034 exact after its readability review and re-diff.
text_7BFF8 now implements both remaining stubs and reaches 81.652150% .text.
text_7E380 improves slightly to 98.257774%, retaining five exact functions.
Per-unit checkpoints preserve experiments and unresolved field/prototype leads.

### Origin merge and best-match audit (2026-10-21)

Merged origin/main ca17037 with the local menus work and recovered Sol drafts.
Kept origin's canonical captain-model/options/reset/challenge/stadium units and
its newer game matches. Removed the overlapping text_16870/text_194BC/rep_0568
units after preserving their stronger implementations in the canonical files.
The local settingValuesTo0 loop/store groups retain 97.65432% in settings_reset,
using origin's typed SettingsResetView rather than raw offsets.

Updated the newer menu units to origin's split lbl_803CBCD8 flag object. This
matched fn_2_83744; its readability pass uses UIRecord.frame/playMode and the
existing UI_PLAY_FORWARD constant, and fresh whole-unit diff remains exact.
A value-form step predicate in stadiumRandomRelated avoids a scheduling regression
from the symbol split (58.22059% local -> 58.605392% merged).

Saved independent pre-merge local, pure-origin and merged object-score snapshots.
All 14,872 named-symbol comparisons meet or exceed their respective side's
baseline, with no unresolved names or loss of exact non-text sections. The sole
name mapping is origin's unusedBattingSomething -> bOD_UpdateBatterAIInputs.
Audit summary and score snapshots are build/_origin_merge_* (ignored).

Full ninja build passed, including all four output hash checks. Project exact
functions: local 4142, pure origin 3897, merged 4182 of 6479 (41.72% code bytes).
Pre-existing untracked docs/menus_second_pass.md and text_50898_reference.d are
preserved and excluded from the commits. No emulator test was performed.

### Post-merge Sol checkpoint: character-selection callbacks (2026-10-21)

Three isolated Sol passes were integrated serially. All 28 function baselines
across these units were checked, with no regressions; fn_2_79634 is newly exact
and passed readability review plus a fresh diff. All four remaining text_78F78
stubs are implemented.

| Unit | Before .text | After .text | Exact functions |
|---|---:|---:|---:|
| text_76874 | 86.07089% | 90.16981% | 1 -> 1 |
| text_78F78 | 36.93814% | 95.11759% | 0 -> 1 |
| text_7BFF8 | 81.65215% | 90.10027% | 0 -> 0 |

- Staged record/handle additions and value-form state predicates reproduce the
  original inline boundaries; delayed signed casts avoid premature narrowing.
  Natural int induction variables with signed-long roster bounds recover
  compiler unrolling without manually grouping source iterations.
- fn_2_7D85C now checks the current-selection animation at frame 10 rather than
  20 (target0x7DA38), and reloads the selection before saving it after callbacks
  (0x7DA60/0x7DA68). The optional threshold4 before the additional completion
  call in fn_2_7E194 was audited at0x7E33C. Logic corrections are retained even
  where the numerical match score ties.
- cssAction_case9 uses native int for its slot argument; its header agrees and
  has no other source include dependents. This preserves the target's native
  integer value numbering; representation and width remain 32-bit signed.
- SQRT2_LINKAGE is static in these units and text_7E380, removing unrelated
  header-generated constant blocks. All target scores are unchanged by this
  cleanup; text_7E380 retains98.257774% and its five exact functions.

Evidence: build/_postmerge_wave1_<unit>_{baseline,final}.json and per-unit
checkpoints. Full build, all four output hashes, and whitespace checks pass.
No emulator playtest was performed. Ongoing private research for text_4D960,
rep_0AB0 and rep_08E8 is checkpointed separately and is excluded until verified.

### Continued checkpoint recovery (2026-10-21)

After pushing82b13e1, recovered additional interrupted Sol work. rep_08E8 now
implements both large stubs: .text50.361355% ->71.630510%, with .rodata unchanged
at79.069770%. fn_2_49DB8 and fn_2_49E5C become exact after the numeric formatter
has its real body; both passed readability review and fresh re-diff. Every one
of45 baseline functions is preserved.

text_4D960 was already fully drafted despite its stale checkpoint. Its glyph
append/copy helper boundary improves .text93.090004% ->94.542360%, keeping21
exact functions and all data scores. The corrected formatter pointer return in
rep_08E8.h was checked in this dependent unit before and after; all22 function
scores are identical. Baseline/final evidence: build/_postmerge_wave2_*.

rep_0AB0 is also fully drafted: fn_2_5A224 reaches95.17308% and fn_2_5B7DC
93.78467%, with all existing functions preserved. The latter's19-state table was
decoded from REL relocations and checked against each target branch. Its record
copy/conversion/permutation block agrees with fn_2_5853C in the neighboring unit.
Reversing target function definitions while lifting inline helpers before callers
improves the unit to82.55906% .text and100% .rodata; data remains nonmatching.
recordsScreen still has a large residual gap and is the next logical target.

### Records initialization and helper checkpoint (2026-10-21)

Completed recordsScreen's seven record copies and five header copies, restoring
its missing stadium initialization and canonical fn_2_904A8 call. The seventh
row uses its own destination offset; header copies preserve the untouched
middle halfwords. Reloading the global menu pointer after callbacks also agrees
with the target. recordsScreen improves41.68455% ->88.770386% against the fully
drafted wave2 baseline; rep_0AB0 reaches86.80810% .text with100% .rodata.

Seven more rep_08E8 helpers now match exactly, after readability review and fresh
whole-unit comparisons. The string comparator uses a structured loop; angle
helpers use existing SANG constants; free helpers clear handles within their
nonnull guards. Further angle-loop/narrowing corrections improve the remaining
near matches. Combined with recovered formatter work, rep_08E8 reaches72.140114%
.text (19/45 exact), compared with50.361355% before this checkpoint. Its .rodata
remains79.069770%. text_4D960 retains94.542360% and21/22 exact.

All79 baseline function scores across these three units are preserved. Full
build, all four output hashes, and whitespace checks pass. Project build report:
4191/6479 matching functions,41.75% code. Evidence: build/_postmerge_wave2_* and
build/_postmerge_wave3_*; detailed private trials and readability snapshots are
in per-unit checkpoints. No emulator playtest was performed.

### Timer, allocation and records-callback audit (2026-10-21)

A further isolated Sol pass raises rep_08E8 .text72.140114% ->81.563160%,
keeping .rodata79.069770%. fn_2_4A6E8 is newly exact after readability review
and fresh comparison. Timer routines fn_2_46D94 and fn_2_472C4 improve to90.39156%
and88.24823%, preserving the original input dispatch, wrap, range, truncation,
and sound paths. fn_2_4906C now copies15 bank pointers as the target does; the
previous draft copied20. Existing ScreenTextPool/TextBank types replace raw views.
The signed16 flags prototype for fn_2_472C4 follows the target's sign extension;
its text_4D960 include dependent was rebuilt and all22 scores remain identical.

Manager's records-callback audit raises rep_0AB0 .text86.808100% ->88.983154%.
fn_2_5979C now reaches99.329445% and fn_2_59CF8 reaches79.305140%. Both run their
conditional update after cancellation as the target does; the editor preserves
its distinct cancellation flags and shoulder/A combinations fall through to
later input tests correctly. fn_2_5AE54 restores the common per-frame update and
cleanup outside initialization, reaching92.980770%.

All57 function baselines in the edited units and22 dependent function baselines
are preserved. Full build, four output hashes and whitespace checks pass;
project report4192/6479 matching functions,41.78% code. Detailed evidence is in
build/_postmerge_wave4_* and per-unit checkpoints. No emulator test was performed.

### Allocation traversal checkpoint (2026-10-21)

Corrected fn_2_477C0 and fn_2_478F4 to scan all54 allocation descriptors; both
drafts had scanned45. Independent target and compiled-source audits confirm six
masked size loads and six0x130-byte steps per trip, over nine trips. Staging the
size reader and allocation cursor also improves the existing fn_2_481F4 scan.
rep_08E8 .text81.563160% ->83.559100%; .rodata79.069770%, all45 function floors
and all20 exact functions are preserved. Existing OSRoundUp32B replaces raw
alignment expressions, with canonical include-path capitalization checked.

Full build, all four hashes and whitespace checks pass. Evidence:
build/_postmerge_wave5_rep_08E8_{baseline,final}.json and the private wave5
semantic_audit.json. No emulator test was performed. The next isolated Sol pass
is drafting the missing challenge dispatcher in text_4B1AC.

### State dispatcher jump-table ownership (2026-10-22)

After pulling origin/main through0d9cad0, rechecked text_50898's current split
before retaining an old dispatcher workaround. Its72-byte jump table is now
owned by this unit, so fn_2_52690 can use a normal18-case switch. An unsigned
halfword read and direct references to the global array remove unnecessary
state/base temporaries. Every case body and out-of-range no-op behavior is
preserved; a reconstruction audit compares the bodies with the prior source.

fn_2_52690 improves42.380512% ->52.589330%, raising .text61.415830% ->64.581290%.
All38 initial function scores,15 exact functions and section scores are
preserved; .data remains0%. The newly generated table's interim pseudo-symbol
scores are not an initial baseline floor. No header or split edits were needed.
Full build, four output hashes and whitespace checks pass. Evidence:
build/_origin_0d9cad0_text_50898.json and build/_postmerge_wave7_text_50898.json.
No emulator test was performed.

### Challenge result recovery and cleanup loops (2026-10-22)

Completed the missing fn_2_4B2D0 dispatcher. Its result classification, menu-kind
branches, state-write order and rollback direction follow the target. Rollback
restores54 scout bytes from backup+7 to live+6, then all54x10 mission pairs
from save+1D..30 to live+9..1C. Typed ChallengeState records and existing count
constants express the copy loops. text_4B1AC .text31.368752% ->63.579300%;
fn_2_4B2D0 reaches78.431310%, and its caller fn_2_4B1AC improves to99.452060%.
All16 initial function floors and two exact functions remain intact.

A private PPC interpreter ran target and compiled dispatcher against a separate
semantic model for4,608 branch-partition combinations. All final persistent
writes agree, including every restored record; this covers input partitions,
not every possible input or runtime environment. Shared compiled instructions
were also checked equal to the audited private final.

In text_53408, ordinary loops and small entry/object helpers replace manual
two-entry duplication in fn_2_53CEC and fn_2_53DF8. The object is resolved again
after its byte store, preserving the target's reload behavior. MWCC naturally
unrolls the loops in pairs. Both functions42.955223% ->95.417910%, raising the
unit .text80.383750% ->85.027084%; all21 function floors, nine exacts and
.data0% are preserved. Target and compiled loops have the same67 instruction
operations, apart from registers, branch destinations and two independent
induction updates; bounds remain864 entries over10/70 rows. TextScene.firstHandle
replaces the raw scene offset in the new helper without changing codegen.

No shared headers or split changes. Full build, four output hashes and
whitespace checks pass. Evidence: build/_postmerge_wave6_text_4B1AC.json,
build/_postmerge_wave9_text_53408.json and private wave6 semantic_audit.py.
No emulator test was performed.

### Text-state widths and callback contract (2026-10-22)

text_5597C improves99.339960% ->99.985450% .text, with16/17 functions exact
(previously12). fn_2_5597C's category assignment and common return preserve its
branch form. Keeping stringIndex as s16 fixes save placement in fn_2_563C0 and
fn_2_5699C; fn_2_57294's selected-index local also matches. fn_2_56688 remains
99.847720%, with only entry arithmetic register operands differing. Named UIRecord
frame/rgba/playMode fields and existing UI visibility/playback symbols replace
raw accesses during the mandatory readability pass, without regressions.
All17 function floors, .data0% and the99.473690% table pseudo-symbol remain intact.

The text_53408 audit found a real callback contract gap: the target passes both
scene and record, while the draft passed only scene. fn_2_53F04/53F88 now pass
the record and reload the global table for each callback, as the target does.
Both improve87.121216% ->99.090910%. fn_2_5389C also lacked the per-frame reset
of13 flag arrays over70 entries. Reusing existing fn_2_53F88 and exact fn_2_54120
recovers the inlined dispatch/reset blocks, bringing44.038460% ->96.846150%.
Callback record arguments,864-entry row bounds,70 rows and13x70 reset stores
were checked against the target.

Its two state selectors fn_2_53AA4/53BC8 now initialize a32-bit result and narrow
once at return. An inline table-row accessor recovers the base load structure;
both81.917810% ->99.726030%, preserving all13 priority tests and default-1.
text_53408 reaches91.800530% .text from the preceding85.027084% checkpoint,
keeping all21 function floors, nine exacts and .data0%. No shared headers or
configuration changes. Full build, four hashes and whitespace checks pass;
report4196/6479 matching functions,41.85% code. Evidence:
build/_postmerge_wave8_text_5597C.json and
build/_postmerge_wave9_text_53408_callbacks.json. No emulator test was performed.

### Challenge shop and save checkpoint (2026-10-22)

text_4B1AC improves from 63.579300% to 83.463990% .text. Three shop setup
callbacks (fn_2_4C81C, fn_2_4CB94 and fn_2_4CD30) now match exactly after
readability review, bringing the unit to five exact functions. A shared inline
helper uses the existing shop-item fields, a flat item index across the 4x5
eligibility table, and signed availability bytes. The other four callbacks
improve to 98.924730%, 94.422420%, 83.369940% and 93.016525%. Existing game-mode,
stadium and boolean symbols replace literals where their meaning is confirmed.

The two save callbacks now copy typed mission pairs and retain target-required
global pointer reloads. They improve to 72.227980% and 73.459460%. Their direction
was checked independently: live scout +6 goes to backup +7, and live mission
+9..1C goes to save +1D..30, opposite the result dispatcher's rollback. All 16
initial function floors remain intact; the earlier dispatcher is unchanged.

A smaller text_50898 cleanup replaces fn_2_51190's manually repeated stores
with an ordinary loop over the same 168 halfwords, improving 43.164383% to
56.356163%. A typed destination pointer improves fn_2_5135C from 27.5% to 37.5%
while preserving its three indexed store locations and period guard. The unit
reaches 65.042810% from 64.581290%, preserving all 38 function floors, 15 exact
functions, .data and table scores. Natural-loop alternatives that lowered the
separate fn_2_50898 baseline were discarded; that function is unchanged.

No shared header or configuration edits. Full build, all four output hashes
and whitespace checks pass. Project report: 4199/6479 matching functions,
41.89% code. Evidence: build/_postmerge_wave10_text_4B1AC.json and
build/_postmerge_wave11_text_50898.json. No emulator test was performed.

### Records-menu controls and typed roster copy (2026-10-22)

text_579B4 improves from 76.504700% to 98.006270% .text, with eight of ten
functions exact (previously two). fn_2_587F8 reaches 98.250750% from 58.191807%:
ordinary 32-element loops replace nested duplication, signed remainder preserves
the toggle behavior, and the recordsScreen copy pattern restores the target's
pointer reloads. The seventh destination retains its 6*0x28 row offset; header
copies preserve the middle halfwords. The shared outer/inner index is retained
because the target intentionally exits the outer loop after those inner scans.
An outer state switch and combined case-zero guard also recover shared blocks.

Six handlers (fn_2_57BF8, fn_2_57F50, fn_2_58098, fn_2_581E0, fn_2_58328 and
fn_2_58470) now match exactly. Their readability pass uses existing UIRecord
fields and visibility/playback constants; the large routine uses INPUT_BUTTON
names. All ten function floors remain intact, .data stays at 0%, and its table
pseudo-symbol improves from 50% to 81.25%. fn_2_5853C remains at 88.2%; a typed
record hypothesis that lowered its score was discarded.

text_50898's fn_2_5163C now uses the existing copyCharacterStats helper pattern
from text_0323C and the canonical CharacterStats type. This preserves the
original field widths, copied ranges and untouched padding while improving
78.248320% to 86%. Typed source/destination pointers retain the same codegen.
The unit reaches 65.458275% from 65.042810%, preserving all 38 function floors,
15 exact functions and data/table scores. A tail-loop alternative changed
inlining in another function and was discarded after the full-unit audit.

No shared header or configuration changes. Full build, four output hashes and
whitespace checks pass. Project report: 4205/6479 matching functions, 41.96% code.
Evidence: build/_postmerge_wave12_text_579B4.json and
build/_postmerge_wave13_text_50898.json. No emulator test was performed.

### Script token and append-source audit (2026-10-22)

Corrected four walkers in text_50898 that tested 0x8000 for the script terminator
instead of the target's 0x4000 control tag. The width readers also had ordinary
and high-bit glyph widths reversed: ordinary glyphs add half width, high-bit
glyphs add full width; control tags 2/3 add half/full width and other control
tags end the measurement. A wide accumulator and explicit tagged-half narrowing
preserve the target's return behavior, including wrap cases. A transient higher
score using a narrow accumulator was rejected when execution exposed different
upper return-register bits.

fn_2_50DB4 and fn_2_50F20 now accept the incoming third source-pointer parameter:
the target uses it when arg1 is -1, while the old draft initialized it to NULL.
Their header was corrected; a repository reference/include audit finds only
text_50898.c dependent, and the full build confirms that scope. Ordinary loops
also replace expanded row clears; the two mode branches remain explicit where
the target retains them.

The unit improves from 65.458275% to 68.075540% .text, preserving all 38 initial
function scores, 15 exact functions, .data 0% and the table score. Independent
target/candidate execution passes 1,539 cases (407,672 PPC instructions), covering
terminators, control tags, odd widths, 16-bit wrap, append count limits, incoming
versus bank-selected pointers and mode branches. Every shared function's
compiled instructions equal the audited private final. Full build, all four
output hashes and whitespace checks pass. Evidence:
build/_postmerge_wave14_text_50898.json and private wave14 walker_audit.py.
No gameplay/emulator test was performed.

### Exact instructions still require jump-table validation (2026-10-22)

The text_5597C data audit found two incorrect aliases despite exact instruction
bodies. State 17 in fn_2_55FD8 and fn_2_56160 entered the shared active block;
the target tables send it to the no-op epilogue. Removing those two case labels
leaves all function instructions unchanged after generated-label normalization
and makes all 190 table relocations match their target function and offset.
The unit's .data improves from 0% to 100%, and the table pseudo-symbol from
99.473690% to 100%; .text stays 99.985450%, with 16/17 functions exact.

A function's code score does not validate the control flow encoded in its
jump table. Resolve each table entry's function and relative destination,
especially when exact bodies coexist with a nearly exact data pseudo-symbol.
A follow-up read-only scan of direct function relocations across 78 menus
units found no other differing destinations into the same exact function.
This scan does not establish the correctness of tables in non-exact functions.

All function/section floors are preserved. Full build, four output hashes and
whitespace checks pass. Evidence: build/_postmerge_wave16_text_5597C.json and
build/.match_grind/exact_table_audit/summary.json. No emulator test was performed.

### Character-selection first pass completed (2026-10-22)

All eight return stubs in text_8082C are now drafted, including cssActions,
maybeBackgroundImagesForCaptain and relatedToTeamSelection3. The unit improves
from 0.3399915% to 90.304290% .text. No functions are exact yet; all eight
initial function floors and section scores are preserved. Its two tables were
decoded before constructing the 21-case and 9-state dispatchers. All 30 first
following-call identities agree, with manual review where distinct cases share
a later call. This is a behavior review, not an exact data-relocation claim:
.data remains 0%, with the newly scored table pseudo-symbol at 65%.

The first six functions take a MenuScene pointer and channel index, confirmed
by their live inputs and dispatcher calls. The header now declares those
parameters; only the unit's own source includes that header or calls the six
functions. Canonical roster/stat/UI types and character/game-mode/CPU enums
replace raw accesses where supported. The state-5D write in fn_2_80C2C remains
inside its flag-55 guard, as required by the target. Removal at the dispatcher
entry still permits subsequent processing and the trailing exit check.

A repository-standard dont_inline region keeps fn_2_808D8 out of line because
the target calls it explicitly; other small readiness functions inline
naturally. No register forcing, artificial loop unrolling or speculative
renames. The full build, all four hashes and whitespace checks pass. Evidence:
build/_postmerge_wave15_text_8082C.json and private wave15 table_decode.txt /
table_semantic_audit.txt. No gameplay/emulator test was performed.

### Selector and lineup behavior recovery (2026-10-23)

text_8782C improves from 48.672398% to 74.287870% .text, preserving all
17 initial function scores, its three exact functions and data/table floors.
Canonical MenuScene.firstHandle is resolved at each UI mutation, matching the
target's pointer lifetime. Signed scout sentinels, selector initialization and
same-frame cleanup, the nine-slot lineup scan, unsigned captain comparisons,
and byte-stride active-player flags now follow the target behavior. A small
rollback from an interim score was accepted for the proven flag-stride fix;
every final score still exceeds or equals its initial floor.

Actual target/candidate execution of fn_2_88250 passes 288 cases (21,504 PPC
instructions), including first-call cleanup. Another 72 isolated target-loop
cases (10,008 instructions) validate nine-slot lineup compaction against an
independent algorithm; these do not execute the complete candidate fn_2_8A008.
The eight switch destinations for states 0x49 through 0x50 were also checked
against target ELF relocations and already agree semantically.

.data remains 0%: owned descriptor/debug data still needs recovery. Its coarse
0xC60-byte symbol contains 93 canonical 32-byte UI descriptors followed by six
32-byte padded debug labels, rather than descriptors throughout. Lists begin
at unit-relative 0x2EC/0xBAC/0xCCC/0xDCC; labels occupy 0xE8C..0xF4C.
This distinction is recorded for the next data pass.

Full build, four output hashes, all-symbol floor audit and whitespace checks
pass. Evidence: build/_postmerge_wave17_text_8782C.json and private wave17
ui_audit.py / data_audit.py. No gameplay/emulator test was performed.

### Character-selection helper recovery (2026-10-23)

text_8082C improves from 90.304290% to 93.046326% .text; fn_2_8082C and
fn_2_80C2C now match exactly. A natural channel-animation helper reproduces
the target inline boundary, while direct access for a zero-offset UI record
removes a redundant helper layer. Pointer lifetimes in the cursor and setup
arrays, a canonical field-offset roster walk, and the full-width roster-slot
index improve the remaining callbacks without altering dispatch labels.

Both exact functions received readability review and a fresh whole-unit diff.
All eight function and section floors hold; the table pseudo-symbol improves
from 65% to 75%. Its 21- and 9-entry dispatch tables retain the 30 reviewed
first-following-call identities. That check is narrower than complete behavior
or relocation equivalence; .data remains 0%. The guarded process-state write
and target-required out-of-line callback boundary remain supported by the
instruction comparison. No header changes were required.

All eight shared function instruction records equal the audited private final.
Full build, four output hashes and whitespace checks pass. Evidence:
build/_postmerge_wave19_text_8082C.json and private wave19 final_audit.txt /
table_semantic_audit.txt. No gameplay/emulator test was performed.

### Shared background cleanup required on both paths (2026-10-23)

A near-exact callback still hid a behavior gap: maybeBackgroundImagesForCaptain
skipped the handle-0xAC visibility clear on its single-player alternate path.
The actual target branch lands at the shared cleanup block, whereas the old
candidate jumped directly to the following cursor-lock call. Moving the clear
outside the else block restores that path. A direct canonical record access
also improves the remaining allocation shape: the callback rises from
99.379310% to 99.954025%, and text_8082C reaches 93.152570% .text.

All eight function floors, two exact functions and data/table scores hold.
Twenty isolated target/candidate cleanup cases (600 PPC instructions) match
an independent visibility-clear model, and the actual branch destination is
checked separately. This does not execute the full call-heavy callback.
Shared instructions equal the private final; full build, four output hashes
and whitespace checks pass. Evidence: build/_postmerge_wave21_text_8082C.json
and private wave21 cleanup_audit.py. No gameplay/emulator test was performed.

### Recover owned data at proven object boundaries (2026-10-23)

text_8782C now defines its owned data using the existing DebugMenuText and
UIRecordDescriptor types: the shared debug prefix and 40-byte lookup tail,
93 descriptors in four end-terminated lists, six padded writable labels, two
file rows and six named character IDs. Splitting coarse symbols at the actual
object boundaries lets all six named objects score 100%; .data improves from
0% to 99.197190%, while .text improves from 74.287870% to 74.296770%.

All 3,988 raw data bytes match the target. Eight generated switch relocations
reach the corresponding logical cases, but their function-relative offsets
still differ in non-exact fn_2_8A824. Raw byte equality therefore does not mean
full relocation equality; those 32 relocated bytes account for the remaining
data mismatch. The descriptor parent references, four terminators and string
boundaries were independently decoded. Integer address arithmetic preserves
the target's base-relative descriptor selection without pointer arithmetic
beyond the now-typed debug object.

The actual rebuilt target reproduces the private boundary preview. All 78
menu units preserve their recorded function, section and pseudo-symbol floors;
all 17 shared function instruction records equal the private final. Full build,
four output hashes and whitespace checks pass. Evidence:
build/_postmerge_wave20_text_8782C.json,
build/.match_grind/wave20_data_floor_audit/summary.json and private wave20
owned_data_audit.txt. Header unchanged; no gameplay/emulator test was performed.

Follow-up readability: ChallengeMapSceneFiles now uses the existing
MatchFileDescriptor type. Its .text/.data bytes and relocation records are
identical to the audited wave20 object; all scores, four hashes and whitespace
checks remain unchanged. Evidence: build/_postmerge_wave25_text_8782C.json.

### Typed reset fields and complete map-state dispatch (2026-10-23)

text_53408 improves from 91.800530% to 98.791940% .text. Natural state and
option dispatch preserve the target's callback/global-reload behavior, and
the inningSetting+0x5A clear now precedes fn_80042D38 as required by the target.
Using the reset entry's proven halfword fields instead of a raw s16 alias
lets the compiler generate the target's eight-entry loop expansion naturally;
fn_2_54474 rises from 86.290985% to 99.651640%, without manual unrolling.

A signed state load in fn_2_549B4 restores all seven exact switch relocations:
.data and its table pseudo-symbol improve from 0%/50% to 100%/100%. All 21
function floors and nine exact functions hold. A bounded model comparison
covers 1,048,576 map-state/guard combinations, and an address/store model
checks 69,120 reset entries. These are model checks, not compiled execution.
All shared function instructions equal the private final; full build, four
hashes and whitespace checks pass. Evidence: build/_postmerge_wave23_text_53408.json
and private wave23 prove.py / data_relocation_proof.txt.

### Branch destinations expose skipped cleanup in near-exact code (2026-10-23)

A read-only scan of near-matching menu functions flagged internal branch
destination differences for review. Two in fn_2_1BFD0 were real scope errors:
the target guards only fn_2_4E7EC, then always resets/frees the sound state;
it also always calls fn_2_4E94C after either cleanup branch. Moving those
shared calls outside their guards and retaining the target's signed load
makes the function exact, from 98.923080% to 100%.

The readability pass replaces raw audio/text offsets with canonical fields.
Including the existing text API also exposed a wrong no-argument declaration
of fn_8000F4B8: fn_2_1B7B4 now supplies the target's (0, -1, -1, -1) arguments.
Constant propagation of the actual compiled call sites confirms that tuple;
the old candidate supplied no established argument values. text_1B1BC reaches
67.238110% .text, preserving all 21 initial floors and adding one exact
function (eight total). Shared instructions equal the private final; full
build, four hashes and whitespace checks pass. Evidence:
build/_postmerge_wave26_text_1B1BC.json and private wave26 call_audit.py.
The scan's other flags remain unproven leads; no gameplay/emulator test was
performed for either checkpoint.

### Explicit no-op states can recover the original compare tree (2026-10-23)

Ten near-exact callbacks in text_5E84C now match exactly after explicitly
retaining state 4 in their existing no-op group. The target and prior source
already dispatch every state to the same action; the explicit case recovers
the target's compare-tree shape. It differs from the previously rejected
state-7 experiment, which made the compiler emit jump tables.

The shared form improves two larger callbacks as well. It regressed two other
functions, so only those additions were discarded. All 18 initial floors are
preserved: .text rises from 76.413475% to 76.994820%, with 12 exact functions
(previously two). The readability pass uses canonical UIRecord fields and
UI_FLAG_VISIBLE, with helper names describing frame/play/visibility operations;
all ten new exact functions remain exact after a fresh whole-unit diff.

Actual target, old-candidate and final-candidate compare trees classify all
65,536 signed states identically in each of the ten functions: 1,966,080
branch-tree checks. This starts after the selector result is applied and does
not execute the complete UI callbacks. All shared instruction records equal
the private final. Full build, four output hashes and whitespace checks pass.
Evidence: build/_postmerge_wave27_text_5E84C.json and private wave27
dispatch_audit.py. No gameplay/emulator test was performed.

### A no-op state completes another record callback (2026-10-23)

fn_2_372AC in text_35EC0 improves from 99.5% to 100% by explicitly retaining
its no-op state0x25. The target, prior candidate and final candidate dispatch
all65536 signed states to identical actions (196608 compiled branch-tree
checks, starting after the selector result is applied). This checks dispatch,
not the complete UI callback.

The readability pass uses UI_FLAG_VISIBLE and descriptive visibility helpers.
All29 function floors and the data/pseudo-symbol floors hold; the unit reaches
90.020340% .text with15 exact functions, previously14. Full build, four output
hashes and whitespace checks pass. Evidence:
build/_postmerge_wave29_text_35EC0.json and private wave29 dispatch_audit.py.

The near-match branch scan also flagged teamselect's manager. Inspection
shows equivalent shared versus duplicated transition-result guards; it is
not evidence of a behavioral defect, and no change was made there.

### Typed model data and callback ownership (2026-10-23)

rep_0DE0 now owns its initialized model-layout, camera rows, file descriptor,
callback nodes and vectors using existing canonical types. All1004 initialized
bytes and both callback relocations match the original. The original section
ends with four alignment bytes; the final vector remains its actual12bytes.
Three proven symbol corrections separate the16byte file descriptor from
the24 camera floats and remove alignment from that vector's size.

After the actual configuration rebuild, .data improves from0% to100%, with
each of the eight objects exact. .text95.3605%, .rodata100% and all17 function
floors/12 exacts hold. Source-only canonical callback declarations replace
the local incompatible prototype; the unused raw extern is removed from
the header. Its dependent text_8782C and all78 menus units preserve their
latest function/section/pseudo-symbol floors. Shared code/data bytes and
normalized relocations equal the private final. Full build, four output
hashes and whitespace checks pass. Evidence:
build/_postmerge_wave24_rep_0DE0.json and
build/.match_grind/wave24_data_floor_audit/summary.json. No gameplay test.

### Recovering the sparse state inventory (2026-10-23)

Five more text_35EC0 callbacks now match exactly. Four share the target's
compare tree: retaining no-op states1/0x25 and removing a redundant explicit
state3 stops the compiler generating unwanted jump tables. Two other
callbacks need their actual0x25 table bound; those no-op cases restore
the original table range and improve the remaining near-match as well.

The unit improves from90.020340% to93.261020% .text, with20 exact functions
(previously15). All29 initial function floors hold, and the table pseudo
improves from42.519917% to58.175343%; .data remains0%. Readability uses
canonical UIRecord fields and UI_PLAY constants. Actual target/old/new
compiled dispatch, including generated table relocations, agrees for all
65536 signed states in six functions:1179648 classifications. This starts
after selector-result application and does not execute the action bodies.

All shared function instructions equal the private final. Full build, four
output hashes and whitespace checks pass. Evidence:
build/_postmerge_wave30_text_35EC0.json and private wave30 dispatch_audit.py.

### Table access and signed animation thresholds finish five callbacks (2026-10-23)

text_35EC0 reaches94.723490% .text and25/29 exact functions, up from
93.261020% and20 exact. Completing the evidenced no-op states fixes two
more dispatch trees. Natural signed-halfword array indexing fixes address
formation in two callbacks. fn_2_36D04 now retains the signed table load
for its comparison with an unsigned frame; the old u16 casts incorrectly
truncated negative limits. All five functions match exactly after the
canonical field/constant readability review and fresh whole-unit diff.

All29 function floors hold; the table pseudo improves from58.175343% to
71.794020%, while .data remains0%. The three changed dispatch trees agree
for every signed16 state across target/old/new code (589824 classifications,
after selector-result application and excluding action bodies). All shared
function instructions equal the private final. Full build, four output
hashes and whitespace checks pass. Evidence:
build/_postmerge_wave31_text_35EC0.json and private wave31 dispatch_audit.py.
Four movie callbacks remain pending; no gameplay/emulator test was performed.

### Restore destination and callback timing (2026-10-23)

text_5E84C improves from 76.99482% to 81.56898% .text, with 13 exact
functions (previously 12). The seventh restored row now reaches its actual
row offset instead of overwriting the first. Per-field global and mapping
reloads follow the target. Focused execution of the compiled copy agrees
on all 115 source/destination/width tuples, both sets of 115 global reloads,
and 90 mapping reads.

fn_2_5EEBC now matches exactly: state 2 stops playback, and state 6 exits
after changing to state 7; hiding happens on the next update. Its compiled
dispatch agrees for all signed states (131,072 classifications). A natural
four-digit helper gives a small additional gain; all 65,536 signed-halfword
inputs agree in old/new value models, without claiming instruction equality.

All 18 function floors and the previous 12 exacts hold. Readability uses
canonical UIRecord fields and playback constants. Shared instructions equal
the private final; full build, four output hashes and whitespace checks pass.
Evidence: build/_postmerge_wave28_text_5E84C.json and private wave28 prove.py.
The focused interpreters/models do not execute the complete game runtime.

### Title screen recovered and linked from C (2026-10-23)

All three stubs in text_8ED4C now match exactly: the unit improves from
1.2820513% to 100%, covering 936 bytes. The title flow starts its prompt,
handles the memory-card check and sound-mode fallback, then selects the main
menu or prepares the demonstration match. Existing canonical settings,
drawing-node and menu types preserve the actual field widths.

The prompt's grouped no-op results 0/1 reproduce the original compare tree;
adding only result 0 adds an unwanted comparison. Ordinary calls to the two
same-unit helpers inline naturally in the title callback. All three remain
exact after the enum/field readability pass and reverse source ordering for
REL deferred emission.

The unit is now Object(Matching). The linked build consumes our C object,
all four original output hashes pass, and report.json marks the unit complete
with 3/3 exact functions. Its entire .text byte sequence and normalized
relocations equal the target. Whitespace checks pass. Evidence:
build/_postmerge_wave33_promoted_text_8ED4C.json. No gameplay test was run.

### No-op table bounds and physical switch-body order (2026-10-23)

text_636A4 improves from 87.93383% to 91.50768% .text, with 13 exact
functions (previously 11). Four target tables include no-op state 0x25;
retaining it restores the table bounds and makes fn_2_63DBC exact.
fn_2_65648 already had the correct dispatch tree. Moving its existing state
0x25 body before state 5 reproduces the original physical layout and raises
it from 30.576923% to 100%, without changing behavior.

Canonical UIRecord fields, visibility/playback constants and record fields
keep all 13 exact after readability review. All 20 function floors hold;
the table pseudo improves from 38.06391% to 63.15789%, while .data remains 0%.
Four compiled dispatch trees agree on action/no-op classification for every
signed16 state across target/old/new code (786,432 checks). This excludes
action bodies and groups the two update states in fn_2_648CC.

Shared instructions equal the private final; full build, four output hashes
and whitespace checks pass. Evidence: build/_postmerge_wave35_text_636A4.json
and private wave35 dispatch_audit.py. No gameplay/emulator test was run.

### Movie callback exits and pointer lifetime (2026-10-23)

text_35EC0 reaches 99.60775% .text, with 27/29 functions exact, up from
94.72349% and 25 exact. Its common movie-exit flag check now runs after every
state. Node scratch writes retain the original node, while child access after
removal resolves the current node again. Focused execution of actual target
and candidate instructions passes 5,106 independently modeled scenarios
(356,580 instructions), including timer wrap and current-node mutation.

The other gains recover signed byte dispatch, per-access global pointer
reloads, 12-byte movie cue records, direct allocation-field ownership and the
clear-color load after the jukebox call. Canonical types/constants preserve
both new exacts after readability review. All 29 function and data/pseudo
floors hold. Data ownership remains incomplete: a typed-definition trial
moved exact generated tables, so it was discarded. The actual color at
0x12270 is zero; 0x11775500 belongs to the preceding object's tail.

The same switch-body ordering evidence also improves text_636A4 from
91.50768% to 93.40410%, with 14 exact functions (previously 13). Its state
0x25 body belongs before state 5 in two further callbacks. All 20 floors
hold; no behavior or header changes were introduced there.

Both shared units' instructions equal their private finals. Full build,
four output hashes and whitespace checks pass. Evidence:
build/_postmerge_wave32_text_35EC0.json,
build/_postmerge_wave36_text_636A4.json and private wave32 movie_audit.py.
The focused audit does not execute the full movie/game runtime.

### Record fade mutations preserve truncation points (2026-10-23)

fn_2_653D4 improves from 94.49045% to 99.617836% by updating its actual
halfword field at each fade step. A local record extension names the proven
fade/channel fields without changing the shared header. The compiled target
and candidate agree with an independent store-trace model for every signed
halfword starting value in both fade arms: 262,144 executions. This excludes
the selector, other states and final color write.

text_636A4 reaches 93.72115% .text. All 20 function floors, 14 exacts and
data/pseudo-symbol floors hold. Shared instructions equal the private final;
full build, four output hashes and whitespace checks pass. Evidence:
build/_postmerge_wave37_text_636A4.json and private wave37 fade_audit.py.
The remaining callback differences concern the color-write tail's registers.

### Record and star-menu flow drafted from four stubs (2026-10-23)

All four text_3A8FC callbacks are now implemented, improving .text from
0.3041825% to 98.904945%, with one exact function. The drafts preserve signed
scratch states, old-value timer tests, input priority, child-node handshake,
global reloads and cancellation cleanup after dispatch. The exact callback
remains exact after canonical type/constant readability review.

All 19 compiler-generated switch entries map to the corresponding original
bodies, without accidental aliases. The 157 direct branch destinations and
42 call sites align; external arguments and state logic were reviewed against
the target. These checks do not execute the complete game runtime. Three
functions remain near-matches; .data remains 0%, with table pseudo 68.42105%.

A wider return-declaration trial for fn_2_44F14 preserved its owner's bytes
but regressed this caller, so the canonical s8 interface was retained. All
four initial function floors hold. Shared instructions equal the private
final; full build, four output hashes and whitespace checks pass. Evidence:
build/_postmerge_wave34_text_3A8FC.json and private wave34 prove.py.

### Challenge bank copies and callback snapshots (2026-10-23)

text_44F14 improves from 71.28488% to 96.35703%, with five new exact
functions (14/27 total). Copying ten typed mission pairs, loading scout
fields through the stored pointer, and resolving the global at each reset
store recover the original loops. Mission visibility captures signed rule
fields before the callback, while later global state reads retain their
original timing. Recruitment compares a sign-extended stored captain with
the unsigned global captain. The public s8 getter interface stays unchanged.

Focused target/candidate PPC checks pass against independent memory and
callback models: 24 whole-bank cases, 256 captain banks and 20 visibility
banks, totaling 964,486 instructions. These do not execute the full game.
All 27 initial function and section floors hold. Full build, four output
hashes and whitespace checks pass. New exacts passed canonical readability.
Evidence: build/_postmerge_wave38_text_44F14.json and private wave38
semantic_audit.py.

### Explicit playback branches recover generated tables (2026-10-23)

text_33E70 improves from 98.59381% to 99.84961%, with four new exact
functions (17/18 total). Calling the playback setter within each branch,
instead of passing a ternary, restores target node resolution and branch
bodies. The canonical ScreenTextBlock.justify field also closes two
callbacks. UIRecord fields and UI_PLAY constants replace raw accesses.

Both generated 38-word switch tables now match: 304 raw bytes and 76
normalized relocations independently checked against the target. Anonymous
compiler labels were not the obstacle. All 18 function, data and pseudo
floors hold, shared/private instructions agree, and full build, four output
hashes and whitespace checks pass. Only fn_2_34F6C remains pending at
95.61972%; prior no-op label trials must not be repeated without new
evidence. No public header or config changes were needed. Evidence:
build/_postmerge_wave39_text_33E70.json and private wave39 snapshots.

### Drawing-node layout and cancellation reloads (2026-10-23)

text_3E38C improves from 85.91016% to 89.62283%, with nine new exact
callbacks. The source-local node's comments had the correct offsets, but
missing priority/scratch fields put timer/frame/phase at 0x12/0x14/0x16
instead of 0x14/0x16/0x28. Correcting the measured fields fixes actual scratch
reads and writes. Cancellation tails then resolve the current global node
after external callbacks; ordinary exit arms keep the cached node where
the target does. Reversing one equivalent sound branch closes the ninth
callback. No public header or config changes were needed.

All 18 initial function floors improve; .data 0% and pseudo 50% hold. The
nine exacts pass individual readability review and a fresh whole-unit diff.
Actual target and candidate PPC agree with independent memory/call models
for 8,160 scenarios (507,168 instructions), including timer/phase boundaries
and active-node mutation by callbacks. This excludes full game/UI runtime.
Full build, four output hashes and whitespace checks pass. Evidence:
build/_postmerge_wave41_text_3E38C.json and private wave41 flow_audit.py.
Nine callbacks remain pending.

### Follow-up challenge state reloads (2026-10-23)

text_3E38C reaches 91.15712% from 89.62283%, preserving all 18 function
floors and nine exacts. Three callbacks now follow the target's global
challenge/node resolution at each use, including after helper calls and
between stores. The parent remains cached only where the target uses it.

Target/candidate PPC agree with independent memory/call models for 2,880
scenarios (191,280 instructions), covering challenge-bank/current-node
changes, timer boundaries and variant reloads. This excludes full game/UI
runtime. Full build, four output hashes, whitespace and private/shared
instruction checks pass. No public header, config or completed-function
status changes were needed. Evidence:
build/_postmerge_wave43_text_3E38C.json and private wave43 flow_audit.py.

### Challenge script interpreter and typed file data (2026-10-23)

text_4078C improves from 23.99914% to 94.006874%, with exact functions
increasing from 6 to 7/13; both stubs are implemented. The script interpreter
covers 110 opcodes, preserving the difference between immediate redispatch
and yielding waits. Its mission helper covers 21 display modes and the
post-switch completion override. The list callback now clears all 20 bytes,
and an existing manually expanded copy is replaced by a natural loop with
the target's pointer reloads.

Thirteen typed owned objects (1,128 bytes) match target bytes/relocations:
file descriptors, Vec constants and drawing callbacks. .data reaches
64.2369%; unknown particle data and generated table layout remain unresolved.
Both actual tables were decoded independently from ELF relocations.

Focused target/candidate instruction checks pass 672 script, 138 mission,
three copy and 12 list scenarios. External callees are deterministic stubs;
their runtime side effects and full game/UI execution are outside this
check. All 13 initial function, section and pseudo floors hold. New exact
fn_2_42388 passes readability, shared/private instructions agree, and full
build, four output hashes and whitespace checks pass. Header/config remain
unchanged. Evidence: build/_postmerge_wave40_text_4078C.json and private
wave40 prove.py/data_relocation_proof.json.

### Challenge list bounds, signed keys and existing inlines (2026-10-23)

text_42BE8 improves from 69.41226% to 74.82986%, with four exact functions
(previously three). The list builder now scans 54 characters, counts actual
successful lineup appends, starts the secondary extraction list at zero,
sorts sign-extended keys, and compacts all 54 records. Petey (0x26) moves to
fixed secondary-list index 2. The helper deliberately counts the first 48
recruits; that helper definition must not replace the builder's 54-slot scan.

Actual target/candidate PPC agrees with an independent stable-sort/list
model for 216 boundary cases (2,826,404 instructions), including signed keys
128/255, 31 recruits plus a last-slot-only append, and entries 36..53.
Another 100 requirement-count cases pass. All 65,536 signed-halfword IDs
preserve the Toad membership predicate, now exact after readability review.
A transient King Boo/Petey enum substitution failed the independent model
and was corrected before integration. These are focused checks, not full
game/UI execution.

Compiled instructions disprove the old missing-inline explanation: target
and candidate already inline the sort in fn_2_44504, and both mission/count
callers already inline their predicates. Explicit inline/wrapper trials
regressed public functions and were reverted. Reverse definition order
restores generated table order, but table destinations still differ with
nonexact code: raw zero bytes and owning symbols alone do not make .data
exact. Its score remains 0%, with pseudo 50%.

All 17 function/section/pseudo floors hold. Shared/private instructions,
full build, four output hashes and whitespace checks pass. No public header
or config changes were needed. Evidence:
build/_postmerge_wave42_text_42BE8.json and private wave42 list_audit.py,
data_audit.py and toad_range_audit.py.

### Separate mission cases preserve inline bodies (2026-10-23)

fn_2_439D0 improves from 66.91749% to 87.66337%, raising text_42BE8 to
77.62239%. Two mission types have distinct target bodies with equal lineup
membership logic. Separate source cases calling the existing public BOOL
predicate restore their natural inline expansions. Ordering case bodies by
their observed target addresses restores the remaining physical layout.

An independent memory model agrees with actual target/candidate PPC for
2,916 scenarios (2,810,081 instructions), using each ELF's real computed
switch destinations. Cases cover every type 60..69 and defaults, signed
requirements, gates, slot counts, membership, captain/difficulty and flags.
There are no external calls in either compiled body. This excludes full
game/UI runtime. All 17 function/section/pseudo floors and four exacts hold;
.data remains 0%. Shared/private instructions, full build, four output hashes
and whitespace checks pass. No header/config changes. Evidence:
build/_postmerge_wave46_text_42BE8.json and private mission_audit.py.

### Map-record reloads and counter division (2026-10-23)

text_3E38C improves from 91.15712% to 97.75391%, with exact functions
increasing from 9 to 11/18. A proven ten-byte record view restores global
reloads during the 51-record scan and retains separate captain arms.
The next-stage value is captured before clearing the selected entry;
records 51..53 remain untouched. Post-callback flag stores now resolve
challenge state again. Two callbacks become exact after readability review.

Both counter callbacks used an incorrect /40 divisor. The target's signed
multiply-high, shift by three and sign correction implement /20. All
131,071 possible differences of two signed halfwords confirm the formula;
for delta 75, the target gives 3 and the old source gave 1. Score-global
reads and work-bank mutations retain their original timing.

The actual ELF's 60 data bytes and all 15 function-relative relocations
match exactly. All phase destinations are distinct; no table initializer
or config change was needed. All 18 function/section/pseudo floors hold.
The unit remains NonMatching because seven functions are still pending.

Earlier callback models and the new list/counter models pass 15,114
scenarios (1,743,326 actual target/candidate instructions), including
callback mutations, signed boundaries, record 50 and excluded records
51..53. External hooks model calls and selected mutations, so this excludes
full game/UI runtime; the large scene receives focused coverage of its
changed phase and frame effects. Shared/private instructions, full build,
four output hashes and whitespace checks pass. Header/config remain
unchanged. Evidence: build/_postmerge_wave45_text_3E38C.json and private
wave45 final_proofs.txt, pending_flow_audit.py and data_math_audit.py.

### Requirement-row pointers retain per-slot reloads (2026-10-23)

text_42BE8 improves from 77.62239% to 80.304756%, with gains in ten mission
callbacks. Holding a pointer to CharStaticIndex.requirementRow across the
slot loop restores the target's field-pointer lifetime. The row byte is
still read each slot, including after calls; capturing its value instead
would change behavior when a helper updates the table. Explicitly promoting
the stored unsigned recruitment byte to s32 restores the target's word
comparison without changing its zero extension or equality test.

fn_2_439D0 also now has separate switch scopes: the previous source legally
nested later case labels inside case 69's condition. Its tracking behavior
passed the earlier model, but that accidental nesting added redundant work.
The corrected scopes preserve the target's physical case order and the
separate membership predicates for cases 67 and 68.

Manager-rerun focused checks pass 11,608 scenarios and 13,418,395 actual
target/candidate PPC instructions. Independent mission/list/count models
cover 6,148 cases; differential checks cover all ten changed callbacks in
5,460 cases. Mode tables use real ELF relocations. External hooks exercise
each helper with signed return boundaries, memory mutations and overwritten
volatile registers. These are focused checks with modeled callees, not full
game/UI runtime or exhaustive aliasing coverage.

All 17 function/section/pseudo floors and four exact functions hold. The
148 raw data bytes and 37 relocation locations/types/owners agree, while
relocation addends still differ: .data remains 0%, pseudo improves to
58.10811%. Shared/private instructions, full build, four output hashes and
whitespace checks pass. Header/config are unchanged. Evidence:
build/_postmerge_wave47_text_42BE8.json and private wave47 final_audit.txt,
callback_audit.py, mission_audit.py, list_audit.py and data_audit.py.

### Self-branches and structure arguments need literal ABI checks (2026-10-23)

text_1B1BC improves from 67.23811% to 68.43051%, preserving all 21 function
floors and eight exact functions. Four apparent unresolved branches in
fn_2_1C33C are actual 0x48000000 self-branches with no relocation. The draft
invented an undefined helper for them; natural assertion loops restore the
observed behavior and improve the function from 55.384617% to 96.15385%.

fn_2_1C504 applies the same captain/variant condition to record states 0 and
1. The old draft reset state 1 unconditionally. Restoring the combined gate
and global reloads improves it from 59.69388% to 82.95918%. It processes 51
records; records 51..53 remain untouched. In the scene dispatcher, replacing
a wrong local GXSetCopyClear(u32, u32) declaration with the canonical
GXColor API fixes the structure argument: the ABI passes a stack object's
address, rather than the color word as a pointer.

Manager-rerun actual target/candidate checks pass 2,560 bounded assertion
classifications, 1,296 record-memory setups and five color values through
each compiled argument block. The record model covers both matching states,
variants, nonmatching records, mask repeats and byte-counter wrap. Graphics
coverage isolates argument construction; the larger dispatcher remains
pending. These checks exclude full game runtime and arbitrary pointer
aliasing. All 176 data bytes and 44 generated relocation entries were
inspected; two exact callbacks have exact table destinations, while the
dispatcher's remaining 24 destinations and bodies are pending. .data stays
0%, pseudo stays 72.72727%. Shared/private instructions, full build, four
output hashes and whitespace checks pass. Header/config are unchanged.
Evidence: build/_postmerge_wave48_text_1B1BC.json and private wave48
focused_proof.py, focused_proof_result.txt and data_reloc_inventory.json.

### Input priority and callback pointer lifetimes (2026-10-23)

text_1B1BC improves from 68.43051% to 77.510635%, with five functions
improved and all 21 floors/eight exacts preserved. Two 51-record helpers
reach 99.39759% after restoring global reloads between state and flag stores.
The texture callback reloads the current bank and table after conversion,
while retaining the original drawing node across removal.

The mission callback must skip Cancel after an accepted action, including
when its selected mission is absent. Cancel applies when the action mask,
completion-count or ownership gate fails. The scout callback gives the left
trigger priority when both triggers are pressed; the old independent
conditions cleared and then filled the flags. Canonical tracking and table
fields plus observed reloads retain these fixes above their original scores.

After helper calls, current work/controller/input may change while the
original tracking-record pointer remains captured. Reloading every pointer
would also be wrong. Focused mutation hooks distinguish these lifetimes.
Both trigger paths execute ten threshold reads per character, confirmed
directly from target/candidate execution; ordinary idempotent stores alone
would not establish the iteration count. A plain loop reproduces the reads
without fabricating the target's unused induction variable.

Manager-rerun independent fixture models pass 2,160 record-helper cases,
72 texture cases, 28 trigger cases, 2,304 action/Cancel cases and 16 scroll
mutation cases: 6,887,083 actual target/candidate PPC instructions. Hooks
capture arguments and overwrite volatile registers. The earlier assertion,
record and graphics-argument checks also pass. Coverage excludes full game
runtime, arbitrary aliasing and exhaustive equivalence of unchanged paths;
remaining mission bulk-loop lifetimes are pending. Data remains 0%, pseudo
72.72727%. Shared/private instructions, full build, four output hashes and
whitespace checks pass. No header/config changes. Evidence:
build/_postmerge_wave49_text_1B1BC.json and private wave49 proof49.py,
proof49.txt and focused_proof.py.

### Typed tracking loops and signed phase switches (2026-10-24)

text_1B1BC improves from 77.510635% to 86.27886%, with exact functions
increasing from eight to ten. Natural signed-phase switches make fn_2_1B52C
and fn_2_1B6CC exact. Each received an individual readability pass, canonical
BOOL comparisons and a fresh whole-unit confirmation.

fn_2_1C860 improves from 52.746204% to 86.342735%. Canonical tracking pairs
replace raw modulo/division offsets. The target captures a tracking record
for each character while resolving its requirement-row byte each mission;
the old draft cached both bank and row too early. Phase 2 walks ten
contiguous slots. A signed phase switch and six separately resolved work
stores restore the remaining initialization structure without artificial
register or loop-induction changes.

Manager-rerun new checks pass 6,902 scenarios and 1,325,920 actual
target/candidate PPC instructions. They cover all 256 phase bytes in both
new exact callbacks, bulk paths across 54 characters and ten missions,
initialization, removal and defaults. Read counts confirm one bank lookup
per character and ten row reads per owning character on the phase-1 bulk
paths. Phase-2 tests document a remaining difference: the target reads a
row byte for skipped owners, while the candidate reads it only for owner 1;
both skip requirement-type reads and writes for those owners.

Earlier callback-mutation models pass another 6,880,003 instructions, and
the assertion/record/graphics-argument checks still pass. These are bounded
ordinary-memory and modeled-callee checks, excluding full game runtime and
arbitrary aliasing. All 21 function/section/pseudo floors hold; .data stays
0%, pseudo 72.72727%, and the unit remains NonMatching. Shared/private
instructions, full build, four output hashes and whitespace checks pass.
No header/config changes. Evidence: build/_postmerge_wave50_text_1B1BC.json
and private wave50 proof50.py, proof50.txt, proof49.py and focused_proof.py.

### A proven record view can restore a natural inline boundary (2026-10-24)

text_1B1BC improves from 86.27886% to 87.806244%, with exact functions
increasing from ten to twelve. The source-only ten-byte map-record view
already established in text_3E38C makes fn_2_1C5C8 and fn_2_1C714 exact.
The helper resolves the current bank for each record access. No public gap,
global boundary or register declaration was changed. Each new exact received
an individual readability pass and fresh whole-unit confirmation; unknown
record codes remain numeric, and the third byte is not treated as a boolean.

The same view plus natural nested captain/record conditions improves
fn_2_1C504 from 82.95918% to 98.87755%. A plain eight-slot initialization
loop replaces inherited explicit stores without changing code. The texture
callback reaches 90.56977% through a signed phase switch, precomputed texture
argument and one-entry reverse relocation loop. Entry 1 remains untouched.
Three separately resolved initialization writes also improve fn_2_1CF94.

Manager-rerun new initialization checks cover 33 cases and 4,362 actual
target/candidate instructions, including callback bank changes, ordered
stores, read counts and boundary sentinels. Expanded inherited models cover
all 256 texture phase bytes and still pass record, input-priority, bulk-loop,
assertion and graphics-argument checks. External callees are modeled; these
checks exclude full runtime and arbitrary aliasing. The previously documented
skipped-owner read difference remains pending.

All 21 function/section/pseudo floors hold. Data remains 0%, pseudo
72.72727%, with the nonexact dispatcher's 24 destinations still pending.
Shared/private instructions, full build, four output hashes and whitespace
checks pass. Header/config are unchanged. Evidence:
build/_postmerge_wave51_text_1B1BC.json and private wave51 proof51.py,
proof49.py, proof50.py and focused_proof.py.

### Dispatcher state must be refreshed after callbacks (2026-10-24)

text_1B1BC improves from 87.806244% to 89.35763%; its dispatcher improves
from 72.35318% to 79.390144%. All 21 function floors and 12 exact functions
hold. Case 0 uses a natural eight-slot initialization loop and independently
resolves work storage after callbacks. Case 4 refreshes challenge state after
the flag store and graphics/scene calls. Case 18 publishes the captain into
the current bank after the selection callback, then reloads the bank before
character lookup and subsequent branching. Canonical captain/difficulty
fields and a BOOL scene-request local improve readability. Header/config
are unchanged. A natural final assertion condition is code-neutral.

Manager-rerun independent models execute 853,512 target/candidate PPC
instructions across 48 initialization, 3,888 case-4, 216 case-18/mode-0 and
576 limited alias/default/other-inner-mode fixtures. They use actual ELF
relocations for dispatch, check callback arguments, mutate current banks,
clobber volatile registers, count work loads and check counter wrapping.
Both objects have 24 dispatcher entries with only cases 16/17 aliased.
Other bodies and full game runtime remain outside this bounded validation.
Earlier initialization, texture, mission, assertion and graphics checks pass.

Data remains 0%; the generated table pseudo-symbol improves from 72.72727%
to 80.681816%. Different destination offsets remain unresolved. Shared and
private instructions agree; full build, four output hashes and whitespace
checks pass. Evidence: build/_postmerge_wave52_text_1B1BC.json and private
wave52 proof52.py, dispatcher_table52.json and inherited proof scripts.

### Preserve distinct dispatcher branches and reuse existing initialization (2026-10-24)

text_1B1BC improves from 89.35763% to 90.06654%, with its dispatcher
rising from 79.390144% to 82.60575%. Case 12 retains a complete insertion
and reset sequence in each branch; inner mode 8 has its own block, as in
the target. Calling the existing initialization helper naturally inlines
without changing its public body. A source-only 24-byte table-entry view
replaces raw scan offsets using the layout already established in text_53408.
All 21 function floors and 12 exact functions hold after readability review.

Manager-rerun actual-PPC checks verify all 26,740 eligible pointer reads in
the zero-table scan, early-exit address prefixes at six-entry and row edges,
and absence of writes. Another 192 case-12 fixtures check both insertion
branches, callback mutation and counter wrapping through actual ELF dispatch.
Inherited behavior checks pass. These are bounded ordinary-memory models
with modeled external calls; full runtime and other dispatcher cases remain
outside coverage. A current-node reload trial was reverted because it
regressed the accepted generated-table floor.

Data remains 0%; the table pseudo-symbol improves to 82.954544%. Shared and
private instructions agree; full build, four output hashes and whitespace
checks pass. No header/config changes. Evidence:
build/_postmerge_wave53_text_1B1BC.json and private wave53 proof53_scan.py,
proof53_dispatch.py and inherited models.

### Script callback cleanup uses both captured and current nodes (2026-10-24)

text_50898 improves from 68.07554% to 68.92482%; fn_2_509A4 improves
from 72.655556% to 98.888885%. Its signed phase switch falls through from
initialization into polling. Separate callback-result cleanup branches
reload the current node's child after callbacks, while the original node
remains captured for its phase reset. The common skip path also reloads
the current child. One dispatch branch remains unmatched.

Manager-rerun actual-PPC models pass 288 callback scenarios and 20,976
instructions, including signed16 return normalization with nonzero upper
register bits, current-node changes during polling/removal, volatile-register
clobbering and full script-copy effects. Earlier token-walker models pass
1,539 scenarios and 407,672 instructions. These bounded checks use ordinary
disjoint memory and modeled external calls, excluding full gameplay.

All 38 function floors and 15 exact functions hold; data remains 0% and
the table pseudo-symbol 50%. Natural initialization/copy loops and a width
simplification regressed and were restored. Shared/private instructions,
full build, four output hashes and whitespace checks pass. No header/config
changes. Evidence: build/_postmerge_wave54_text_50898.json and private
wave54 callback_audit.py, walker_audit.py and manager_verification.md.

### Canonical text banks recover an exact pointer helper (2026-10-24)

text_50898 improves from 68.92482% to 69.4464%, with exact functions
increasing from 15 to 16. Existing ScreenTextPool.textBanks and TextBank.strings
make fn_2_5156C exact and improve both append callbacks to 91.190475%.
Its observed mode branches remain separate. An individual readability pass
and fresh whole-unit confirmation preserve the new exact. Sharing the row
base improves fn_2_50D40 from 49.827587% to 58.793102%; a three-by-two array
view expresses the known prefix of fn_2_5135C without changing instructions.

Manager rebuilt a frozen copy and strengthened the new bank fixtures so
all seven banks have different tables and string pointers/content. The
216 selector/append cases pass 21,200 target/candidate PPC instructions;
1,539 inherited walker cases and 288 callback cases also pass. A prior
fixture reused the same table for different selectors and was replaced
before acceptance. These bounded ordinary-memory checks exclude full
game runtime. The typed width-callback form and alternate row expression
regressed and were restored.

All 38 function/section/pseudo floors hold; data remains 0% and pseudo 50%.
Shared/private instructions, full build, four output hashes and whitespace
checks pass. Header/config are unchanged. Evidence:
build/_postmerge_wave55_text_50898.json and the frozen private wave55
manager bank_audit.py, callback_audit.py and walker_audit.py.

### Two-dimensional row views preserve complete script clears (2026-10-24)

text_50898 improves from 69.4464% to 69.87446%. Three clear helpers now
use natural two-dimensional halfword row pointers, following the existing
MenuScriptWork layout in text_4D960. fn_2_50E5C reaches 88.061226%,
fn_2_50FC8 69.19643%, and fn_2_510A8 78.24561%. Existing symbol boundaries
and declarations remain unchanged.

Manager-rerun actual-PPC models pass 15 cases with real label aliases,
4,638 stores per side and 10,461 total instructions. Every selected row
receives exactly 256 zero halfword stores; counts, flags, adjacent rows
and guards match an independent memory model. The two independent initial
count resets in fn_2_510A8 occur in opposite orders; later stores agree.
Inherited walker, callback and distinct-bank tests pass. These checks cover
ordinary memory and valid row indices, excluding arbitrary aliasing and
full game runtime.

All 38 function floors and 16 exact functions hold; data remains 0%,
pseudo 50%. Shared/private instructions, full build, four output hashes
and whitespace checks pass. Header/config are unchanged. Evidence:
build/_postmerge_wave56_text_50898.json and the frozen private wave56
manager clear_rows_audit.py and inherited models.

### Angle conversion runs on both signs; text width uses logical shifts (2026-10-24)

rep_08E8 improves from 83.5591% to 83.76249%, with exact functions
increasing from 20 to 21. fn_2_4A2C4 previously returned zero for every
nonnegative angle. It now conditionally adds one binary32 2pi constant
for negative inputs, then converts both signs into angle units. It reaches
97.89474%; the remaining difference is constant relocation labels. The
existing SANG_ANG_180 names the scale. Explicit unsigned half-width shifts
make fn_2_49EFC exact after individual readability review and a fresh
whole-unit confirmation. Its exact 0x4000 terminator rule remains intact.

Manager independently checked both objects' ELF constant bits and reran
16 finite angle cases through floating operations, integer conversion,
the stack store/reload and the actual return register. They agree with
an independently rounded expression, including positive/negative zero
and angles beyond a single revolution. The conversion model uses valid
signed32 results and excludes NaNs, exceptions and other rounding modes.
Another 196 actual-PPC width cases pass 218,988 instructions, including
distinct neighboring widths, ignored tags, sums above16bits, exact table
reads and absence of writes. Full game runtime is outside this scope.

All 45 function/section/pseudo floors hold; rodata remains 79.06977%.
Shared/private instructions, full build, four output hashes and whitespace
checks pass. Header/config are unchanged. Evidence:
build/_postmerge_wave58_rep_08E8.json and the frozen private wave58
manager angle_audit.py, angle_proof.json and width_audit.py.

### A direct zero guard restores the angle helper's control flow (2026-10-24)

rep_08E8 improves from 83.76249% to 83.787346%. fn_2_4A1E8 now returns
zero immediately when both inputs compare equal to zero, then calls atan2
otherwise. Its score improves from 93.68421% to 99.47369%; the remaining
difference is the zero constant's relocation label. All 45 function floors
and 21 exact functions hold; rodata remains 79.06977%. Lower-scoring color,
angle-width and nested-loop trials were restored.

Manager-rerun floating-point traces pass 16 cases, checking signed-zero
bits, NaN call routing, argument order, modeled volatile-register clobbering
and rounding of the modeled double return to binary32. Both-zero inputs
return positive zero. atan2 is modeled with host math; exception flags,
NaN payloads and the game library's full behavior are outside coverage.
Earlier angle-conversion and text-width checks also pass. Shared/private
instructions, full build, four output hashes and whitespace checks pass.
Header/config are unchanged. Evidence: build/_postmerge_wave59_rep_08E8.json
and the frozen private wave59 manager zero_angle_proof.py and inherited models.

### Byte-array field indexing can recover dynamic source-address formation (wave60)

In menus/text_579B4, six selected-record halfword reads expressed as `*(s16 *)&source[off + field]` produce the source-plus-dynamic-offset address followed by a fixed field load. The pointer-chain form `*(s16 *)(source + off + field)` emitted indexed loads with separate offsets; a typed entry pointer and source-parameter helper also regressed and were rejected. This small source-expression change raises fn_2_5853C from88.2% to99.65714%, unit98.00627% to99.05382%, preserving all eight exact functions and data pseudo81.25%. Remaining helper differences are commutative add operand order. An indexed character-flags helper in587F8 was code-neutral; a loop-local index regressed and was reverted.

The manager's bounded actual-PPC model passes36 independently specified cases on both sides (12,600 instructions): signed-halfword boundaries, three valid selections, distinct bytes/guards, untouched7419,22/16-byte copies, converter arguments, final permutations, callback work-bank replacement and volatile GPR clobbers. Complete observable memory and ordered stores match. The converter is modeled explicitly; arbitrary aliasing and its game implementation are outside the proof. All13 changed-function ELF relocations compare equal. Full build, four output hashes and whitespace checks pass; the unit remains NonMatching because pending code and data remain.

### Recover the inlined selected-record copy and separate state stores (wave61)

The byte-array halfword indexing from wave60 also improves the inlined `copySelectedRecord` in `menus/rep_0AB0`: fn_2_5B7DC rises from 93.78467% to 95.99662%. Expressing its state7 A-button choice as separate `if/else` state writes before the shared sound call raises it further to 97.78918%, matching the target's branch structure. Whole-unit `.text` increases from 88.983154% to 89.67099%, with every other function, section and pseudo-symbol unchanged, including the one exact function. Swapping the index addition operands was code-neutral and reverted. No headers changed.

The manager's independent actual-PPC model uses each ELF's real 19-entry dispatch table. Its 408 scenarios execute the changed case2 and case7 paths (148,056 total instructions), checking selected record fields and untouched bytes, enabled/disabled records, three controller ports, callback work-bank replacement, volatile GPR clobbers, signed selector boundaries, input priority, state/flag stores, sound arguments and complete observable memory with ordered stores. The converter is an explicit external model; directional cursor input is zero, and other state bodies, arbitrary aliasing and the converter's implementation are outside this proof. Full build, four output hashes, fresh shared/private instruction equality and all score floors pass.

### Retain the controller-field base across a cursor callback (wave62)

In `menus/rep_0AB0`'s shared `updateRecordGridCursor`, a local halfword pointer to controller byte offset4, indexed by `port * 16`, recovers the target's retained input base and indexed loads. The port still reloads from the current work area after a sound callback. The existing input type leaves offset4 unnamed, so no field was invented. Both callers improve; separating fn_2_5A224's state7 selection into two state stores provides another gain. Final `.text` is90.28253% from89.67099%; fn_2_5A224 reaches97.97051%, fn_2_5B7DC98.88952%, and data pseudo55.035973% rises to57.913666%. All other function and section floors, including the existing exact function, hold.

The manager reran5088 distinct actual-PPC path fixtures (1,151,640 target+candidate instructions) using the actual19/26-entry ELF tables. Models cover selected-copy paths, all16 direction masks across36 grid positions, callback work-bank and port replacement, signed selectors and A/B priority, volatile GPR clobbers, complete observable memory, ordered stores, call arguments and the26-state menu's common GX exit. The latter fixes hugeAnimStruct307A to1; its conditional graphics branch and other state bodies are outside this proof. External converter effects are explicit models on ordinary disjoint valid memory. No headers changed; fresh shared/private instruction and score-floor checks, full build, four output hashes and whitespace checks pass.

### Initialize lane flags before aggregation and retain their pointer (wave63)

In `menus/text_5E84C`, fn_2_5EB78 now initializes its four byte flags before scanning and advances a pointer to the current flag. The source global is captured after the separate selector reset, matching the target's ordering. The compiler naturally unrolls the five checks per lane. The function improves from90.56637% to97.61947%, whole `.text`81.56898% to81.886765%, with all13 exact functions and all18 function floors preserved. A zero-initialized array emitted an unwanted constant-pool load and regressed; marking the digit helper inline was code-neutral. Both trials were discarded. The selector33FBF5 stays numeric0 because other code tests values0/1/2; only the actual aggregation flags use FALSE/TRUE.

The manager's independent actual-PPC model passes3000 bounded scenarios on target and candidate (811,500 instructions), checking all20 source reads exactly once, per-lane nonzero aggregation, three distinct nonzero byte values, four mode values, optional record initialization with preserved gaps, and complete observable memory and ordered stores. The proof uses ordinary initialized disjoint memory and covers this routine only. Fresh private/shared instruction equality, every function floor, full build, four output hashes and whitespace checks pass. No headers changed.

### Capture the character table before the selector and index work halfwords (wave64)

In `menus/text_636A4`, moving each character-table local before `fn_2_53BC8` recovers the target lifetime: fn_2_65850 rises72.93519% to78.98148% and fn_2_65C84 rises94.14783% to99.478264%. Byte-array indexing before the signed-halfword cast in `recLevelFromWork` raises fn_2_642F8 from80.35461% to85.17731%. Whole `.text` reaches94.487595% from93.72115%, preserving14 exact functions, every function floor, data0 and pseudo63.15789%. A source-local canonical GameInitVariables include and existing `_12` field replace the raw byte-array declaration without changing generated instructions. Passing a captured settings pointer into the settings helper regressed and was reverted.

The manager's actual-PPC models pass43,200 independently expected cases (3,944,080 target+candidate instructions): full character-flag callbacks, signed selector/timer/level boundaries, callback record/scene/node/work changes, source guards, correct frame-source mapping, volatile GPR clobbers, full observable memory and ordered stores. The work-level model reads the real38-entry dispatch table and covers its changed source paths and0/default exits. These are bounded callback models on initialized disjoint memory, not full gameplay. A fresh baseline rebuild also confirms the other17 function bodies and all114 actual entries in their three dispatch tables are unchanged after resolving local label names. Shared/private instructions, full build, four hashes and whitespace checks pass; no headers changed.

### Complete five scene-flow callbacks and preserve combined input predicates (wave65)

Five remaining stubs in `menus/text_37F04` now implement activation, timer, choice and cleanup behavior. Whole `.text` rises from 30.694714% to 61.336933%; fn_2_38538 becomes exact, increasing six exact functions to seven. Final scores arefn_2_38F48 86.741936%, fn_2_391B4 98.120804%, fn_2_39408 98.79829%, fn_2_397AC 97.89474%. Every prior function floor holds. The large fn_2_399C0 routine remains a stub and owns the still-unmatched 76-byte dispatch table. The old checkpoint's 11-stub count was stale; there were six before this pass.

The manager's independent actual-PPC expectations pass 37,052 fixtures across the four new nonexact callbacks (2,566,668 target+candidate instructions), checking complete observable memory, ordered stores, timer boundaries, byte wrap, simultaneous input priority, three controller ports, exact call arguments/order, volatile GPR clobbers, current-work/current-node replacement and original-node state cleanup. These checks caught and corrected a draft error where LEFT consumed RIGHT despite a failed choice predicate; all three choice routines now retain the target's combined button/value conditions. Callback effects are explicitly modeled on valid disjoint buffers, including overlapping indexed fields within the record table. Full gameplay and arbitrary aliasing are outside this proof.

The newly exact fn_2_38538 has 748 machine bytes and 39 actual relocation records identical to target; its supported flag writes use TRUE after readability review. The worker's 3,600 additional PPC comparisons have a narrower observation/static-removal scope. A static SQRT2_LINKAGE guard prevents unused header math output, and the local sound-ID parameter uses the SDK's underlying u16 width. No headers or fabricated data were added. Fresh private/shared whole-unit instructions and all score floors, full build, four hashes and whitespace checks pass.

### Complete the 19-state scene-flow dispatcher and verify the full scan (wave66)

The final stub in `menus/text_37F04`, fn_2_399C0, now implements all19 states: challenge flag scanning, scene gates, signed timers, grid input, recruitment, graphics callbacks and cleanup. It reaches89.801025%; whole `.text` rises61.336933% to93.89687%. All14 previously published function bodies retain identical raw bytes and function-relative relocation records, preserving seven exact functions. The compiler emits the real76-byte,19-relocation switch table; `.data` remains0% and its pseudo-symbol50%, so the unit remains NonMatching.

Manager checks caught a draft scanning28 entries instead of54 in each flag range. The accepted natural loop visits all54 entries, tests signed-byte value1 and preserves incoming latches. Independent full-entry actual-PPC expectations pass17880 fixtures across every state and default paths (5,040,098 target+candidate instructions), checking real ELF dispatch tables, signed timer/return boundaries, all16 directional masks across36 grid positions, A/B priority, callback changes, volatile GPR clobbers, full observable memory, ordered stores and call arguments. An additional1506 differential callback-replacement fixtures pass. These use initialized disjoint valid buffers and explicit callee models; arbitrary aliasing and full gameplay are outside coverage. The manager strengthened the worker's case-entry checks to execute the real prologue and dispatch. Fresh private/shared whole-unit instructions and all score floors, full build, four output hashes and whitespace checks pass; no headers changed.

### Complete character stat graphics and recover the grouped variant switch (wave67)

`menus/text_744C8` now implements both remaining real stubs. Grouping character cases by return value makes fn_2_74DB8 exact, including92 raw machine bytes and its42 switch relocation records. The graphics routine reaches83.12403%; its stat-bar helper rises64.56% to70.706665% after recovering the renderer's fourth argument and storing its return at record+0x58. Whole `.text` rises45.02146% to74.32457%, preserving every prior floor and increasing three exact functions to four. Named CharacterStats fields, CHAR_ID members, UIRecord frame/rgba/playMode fields and existing UI constants replace raw new accesses. Both42-entry tables are compiler emitted; the still-low fn_2_76650 owns the missing13-entry52-byte table. Candidate data336B versus target388B leaves `.data`0% and pseudo68.05832%; the unit remains NonMatching.

The manager's independent full-entry actual-PPC expectations pass97,637 fixtures (13,253,914 target+candidate instructions): all65,536 low16 mapping inputs plus signed32 boundaries; all54 characters, allfour ports, signed selections and byte-return truncation; every stat byte plus signed boundaries; actual ELF tables, callback changes to settings/scene handles/graphics entries/stats, volatile GPR clobbers, complete observable memory, ordered stores and calls. Review recovered the required selection reload after the variant callback. These checks use initialized valid disjoint buffers and explicit renderer effects; arbitrary aliases and full gameplay are outside scope. A no-cursor-match path leaves a target register uninitialized and is excluded; source defines CHAR_ID_NONE there.

All15 other target bodies and four source-local helpers retain identical raw code and relative relocations. Final readability edits are freshly compiled and machine-byte neutral. Corrected public prototypes rebuild the sole dependent text_78F78 with unchanged code/data/relocations and scores. Fresh shared/private instructions and every score floor, full build, four hashes and whitespace checks pass.

### Recover the mask switch and its bit-zero skip (wave68)

In `menus/text_744C8`, fn_2_76650 now uses a natural13-entry switch and two-word result list. Bit zero advances the loop index inside its case, so bit one is skipped; cases1–12 append literal values and the default appends13. The routine retains the target's exact two-byte memset, decrements both slots, applies negative fallback12 and writes UIRecord frame fields. Natural list indexing improves the function19.459854% to97.51825%; whole `.text`74.32457% to79.00876%, preserving four exact functions and every prior floor. All three compiler-generated tables are present:388bytes97relocations, including13 new entries matching target offsets/types/function-relative addends. Inherited graphics table addresses still differ, leaving `.data`0% and pseudo78.35052%.

The manager's independent full-entry actual-PPC expectations pass15,120 fixtures (5,797,872 target+candidate instructions): all210 low14 masks producing exactlytwo results, ignored high bits, four team slots/upper bits, three handles, actual ELF tables, exact memset arguments, volatile GPR clobbers, full observable memory and ordered frame stores. Another3840 explicitly initialized-stack PPC fixtures pass1,384,608 instructions for zero/one-result masks and signed fallback boundaries; these seed actual local locations before entry and make no C-level defined-behavior claim for uninitialized words. Three-or-more results may overwrite saves and are excluded. No source initialization or guard was invented.

The other17 target bodies and four local helpers retain identical machine bytes/resolved relocations; all84 existing table entries are unchanged, preserving the earlier graphics proofs. An unused counter was removed during review, and natural array indexing replaced byte-offset writes. Header is unchanged; fresh shared/private instructions and all score floors, full build, four output hashes and whitespace checks pass.

### Correct the ignored first argument of a nearly matching callback (wave69)

fn_2_7609C in `menus/text_744C8` now has its actual three-argument ABI: an ignored first word, a byte value in the second slot, and a byte state in the third. The target tests the third slot and passes the second value to fn_2_8794; the prior two-argument draft consumed the wrong slots despite99.166664% instruction similarity. Correcting the source/header makes it exact, with48 raw machine bytes and actual relocation records equal to target. Whole `.text`79.00876% rises79.01314%, four exact functions become five, and all other floors hold. Argument meanings beyond value/state remain unproven.

The manager's independent full-entry PPC model passes70,656 fixtures (1,293,328 target+candidate instructions): all256x256 argument-byte pairs, upper-bit/ignored-first-word variants, all256 states of the adjacent cursor callbacks, exact calls, explicit callback effects/volatile GPR clobbers, complete observable memory and ordered stores. The other17 target bodies, four local helpers and97 data relocations are unchanged, retaining prior graphics/mask proofs. The header's sole dependent text_78F78 rebuilds with unchanged code/data/relocations and scores. Fresh shared/private instructions, full build, four output hashes and whitespace checks pass; data remains0%, pseudo78.35052%.

### Recover chemistry intervals, pointer lifetimes and byte readiness results (wave70)

In `menus/text_744C8`, explicit target upper/lower star intervals, a moving nine-entry selection pointer and an in-loop captain-word read raise teamSelectionSetChemStars58.73422% to66.68439%. A signed32 team argument and documented `E(u8,BOOL)` readiness result raise fn_2_75B58 from70.11429% to84.4%; the target's cntlzw/extrwi return supports that byte width. Whole `.text`79.01314% rises80.280334%, preserving allfive exact functions and every floor; data0% and pseudo78.35052% remain. Loops remain natural source, with unrolling left to the compiler.

The manager's independent full-entry actual-PPC expectations pass19,328 fixtures (14,512,180 target+candidate instructions): all512 nine-slot eligibility patterns, signed captain words, every uniform byte weight and contributor count, star/frame thresholds; every initial count byte, all512 nine-callback truth patterns, four valid teams, callback count replacement, full32 return truth and volatile GPR clobbers. Full observable memory, ordered stores, exact calls and readiness returns agree. Callee effects use initialized disjoint valid buffers; arbitrary aliases/full gameplay and unreachable computed stars abovefive are excluded. All16 other target bodies, four local helpers and97 table relocation shapes are unchanged, retaining prior proofs. The corrected prototype also improves three dependent callers as recorded below. Fresh shared/private instructions, all floors, full build, four output hashes and whitespace checks pass.

### Chemistry argument typing also restores three caller moves (wave70 dependent)

Rebuilding `menus/text_78F78` against the corrected chemistry prototype raises `.text`95.11759% to95.22358%. cssAction_0x19 reaches93.71429%, randomTeamMemberSelection96.08%, fn_2_7AE3C93.6837%. Each change is exactlyone byte truncation replaced by the full-width argument move present at the target chemistry call. Allother instructions/branchdestinations and every function floor, including the exact helper, hold. The source is unchanged; these are valid team-index calls, with the callee behavior independently checked in wave70. Freshshared/private instructions, full build, four hashes and whitespace checks pass.

### Use the canonical chemistry header in the character-action unit (wave71)

`menus/text_76874` includes the canonical text_744C8 header in place of three redundant local declarations. Fresh compilation preserves every machine instruction, data byte, relocation, function floor and exact helper; `.text` remains90.16981%. Shared/private instructions, full build, four output hashes and whitespace checks pass. No headers changed.

### Carry the full chemistry team argument through two more callers (wave71)

Canonical text_744C8 declarations raise `menus/text_7E380` `.text`98.257774% to98.37282%. cssRemoveCharacter1 reaches94.54676%; cssSelectCharacter98.125%. Each change replaces exactlyone byte truncation with the full-width argument move found in the target. The latter move is25 instructions before its call; the manager verified no intervening argument-register definition and the same target lifetime. Allother machine code/data/relocations and allfive exact functions are unchanged. The callee's behavior was independently checked in wave70; this check establishes the bounded caller delta, not full gameplay. Fresh shared/private instructions and every floor, full build, four hashes and whitespace checks pass.

The same canonical declaration trial in text_7BFF8 elided both moves and regressed cssAction_case9; that candidate was discarded and the original source retained. No cast or placeholder was added to force allocation. Its narrow local declaration remains a pending source-shape issue.

## Findings from debug/rep_7920.c (full match, flipped to Matching)

- **An auto-inlined call with an address-expression argument schedules differently from
  the same body written out on a local.** `fn_1_26C2C` inlines `fn_1_26B7C` (an init
  routine). Writing `slot = &arr[idx]; fn_1_26B7C(slot);` or hand-expanding the body on
  `slot` matched the logic but not the float-setup schedule or the hoisted `slot+0x11`
  pointer (91-92%). Passing the expression straight in and dropping the local entirely
  (`fn_1_26B7C(&arr[idx]); ... return &arr[idx];`) gave 100%. The tell: the target
  re-materialises `&arr[idx]` (lis/addi/add) for the later stores, and the inlined body
  shows a pointer hoist the standalone copy does not. If a function inlines a
  same-file helper and the residue is only scheduling around the inlined body, try the
  argument as an expression with no local before grinding registers.
- **A gap-sized `.bss` array can pass objdiff and still break the flip.** dtk sized
  `lbl_1_bss_47052` as 6 bytes (the gap up to the next unit's 8-aligned `.bss`), and
  `u16 [3]` scored 100% in objdiff. After the flip it failed the sha1: once declared in
  the correct reverse order, MWCC 4-aligned the 6-byte array, which moved it to 0x47054.
  Only element 0 was ever referenced. The real object is a plain `u16` (symbols.txt
  size 0x2), and the last 4 bytes are inter-unit padding. If the flip fails because the
  REL relocation addends are off by 2 or 4, suspect an array dtk sized from the gap.


## Findings from the debug REL first passes (rep_7978, rep_7A28, rep_7BA0, rep_7BF0; 2026-10)

`rep_7BA0` was matched and flipped to Matching. The other three are NonMatching with pending
functions. These lessons are not specific to one file:

- **Every flipped debug unit after `rep_7920` needs its own `REP_HEADER_DATA_FN`.** `rep_7920`
  uses the default `getRepHeaderData`. Flipping `rep_7BA0` without the define left `debug.rel`'s
  `.rodata` 0x50 short (see the foul_detection entry above). Use `getRepHeaderData_rep<addr>`.
- **`SQRT2_LINKAGE` works in the debug REL too, so use `INPUT_BUTTON`.** Two first passes used
  `PAD_BUTTON_*` because including `game/UnknownHomes_Game.h` broke `.rodata`. With
  `#define SQRT2_LINKAGE static` before the include, `rep_7BA0` kept 100% and passed the sha1
  check with `INPUT_BUTTON_*` and an `E(u16, INPUT_BUTTON)` local.
- **If the target addresses several `.data` symbols off one base register, define them in the
  file.** For example `addi r7,r31,0x20` and `stw 0x110(r31)` from one `lis/addi`. In
  `rep_7A28`, moving all the data from extern to definitions in the `.c` took `.data` from 0%
  to 100% and made the addressing match exactly. In `rep_7BF0` the boundaries followed the
  addressing: an address-of that gets a fresh `lis/addi` starts a new object, and so does a
  scalar read at a fixed offset (`base+0x120`).
- **A zero-initialised scalar lands in `.bss`, not `.data`.** It shifts every later `.data`
  object by its size. `void *x[1] = {0};` keeps it in `.data` (`rep_7A28`,
  `lbl_1_data_10918`/`1091C`).
- **Use the GX inline helpers, not the raw FIFO macros.** `GXPosition3f32(x, y, z)` plus
  `GXColor1u32(c)` took `rep_7A28`'s `fn_1_27BB8` from 91% to 99.9%, where `GX_WRITE_F32`/
  `GX_WRITE_U32` did not.
- **A helper inlined with stores in between may be two inlines.** `rep_7978`'s camera init runs
  `PSVECAdd` + `C_MTXLookAt`, then some field stores, then the `C_MTXFrustum` math. Two
  `static inline` helpers (view, projection), called on either side of the stores, matched. One
  combined helper did not.
- **Read float constants from their bit pattern.** A limit that looked like `3.1384f` was
  0x4048DD97 (3.1385248f) in the target. The rounded literal produced different `.rodata` bits.

### Second-pass (Opus) findings on the same files

`rep_7978` and `rep_7A28` were matched and flipped. `rep_7BF0`'s bytes match except
`fn_1_29A9C` (91.70%, GPR numbering in the `fn_80037768` argument setup).

- **A power-of-two reciprocal that comes out first in `fmuls` should be written as `x / 2^n`.**
  `x * 0.0078125f` puts the constant first and pools it early. `x / 128.f` is rewritten by
  MWCC into a value-first multiply and pools the reciprocal late. That fixed both the operand
  order and the `.rodata` order (PI, 180, 1/128, 60) in `rep_7978` `fn_1_26D28` and
  `rep_7BF0` `fn_1_2858C`. Keep the grouping, e.g. `x / 128.f / 60.f`. This extends the
  `x / 2` -> `fmuls x, 0.5` note to any 2^-n.
- **`extrwi` + `xoris r0,r0,0x8000` before an int-to-float conversion means a signed int.**
  `(u32 >> n) & 1` converts as unsigned and leaves out the `xoris`. Both
  `(s32)((v >> n) & 1)` and `((v & INPUT_BUTTON_X) != 0)` match, and the second form uses
  the enum.
- **A pool-name mismatch (`@N` vs `lbl_*_rodata_*`) is usually a pool-order problem.**
  objdiff pairs relocations by target address + addend and ignores names and binding.
  `scope:local` doesn't change the score, though it still silences FORCEACTIVE warnings.
  The other side of this: `X+8` vs a separate symbol `Y` at the same address is a mismatch,
  so data symbols have to start where the code's base + offset pattern says.
- **Scheduling can reveal the data shape.** If loads and stores are right but ordered
  differently, check whether the target treats a run of dtk-split `.data` symbols as one
  object. Stores into one known object let MWCC hoist an unrelated load above them. Separate
  objects or a cast pointer don't. `rep_7A28` needed 41 dtk symbols merged into
  `DbgTexEntry lbl_1_data_10908[3]` for `fn_1_27560`/`fn_1_28118`.
- **An extra `addi rX,rBase,0` before a field load means the target pooled the file's
  statics.** MWCC pools behind one base register only when a function references enough
  distinct statics (two weren't enough in `rep_7BF0` `fn_1_28CE8`, four were). Splitting a
  composite static into separate statics can turn pooling on.
- **One `lbz` but two `extsb` means a signed byte field read twice through an `s8 *`.** The
  load is CSE'd but the conversions aren't. A `(s8)x` cast written twice does get CSE'd
  (`rep_7BF0` `fn_1_28AE0`).
- **Arguments set up before a branch that computes another argument** point to a
  `static inline` helper whose parameters were bound first (`rep_7BF0` `fn_1_2948C`).
- **Inputs loaded into volatile registers and copied with `mr` to callee-saved ones** mean the
  source masked the copies in place (`v &= ~m`) and re-read the global, rather than
  `v = in & ~m` from a local.
- **Testing a symbols.txt change without touching the shared file:** copy `config.yml` with the
  module's `symbols:` pointed at an edited copy, run `dtk dol split <copy> <out>`, and score with
  a throwaway `objdiff.json` (`build_target`/`build_base` false). Keep the copy under `build/`:
  from the system temp directory the split failed an unrelated `rep_0010` rodata-size check.

### Debug REL batch 2 first passes (rep_0010, rep_00B0, rep_0250, rep_02A8)

- **objdiff pairs `.data`/`.bss` symbols and relocations by address, not by name, but the
  symbol has to START at the same address.** `rep_7BF0`'s statics had descriptive names
  (`gDebugMenu`, ...) and scored `.data` 0%, with seven byte-identical functions at 99.x%.
  Moving the dtk labels in symbols.txt onto the real object boundaries, while keeping the
  `lbl_1_data_*` names, took `.data` to 100% and the functions to 100%. So if a function is
  byte-identical but scores under 100% on data relocations, fix the label boundaries.
- **dtk labels at odd addresses with size 3 are usually a pad byte plus a 2-byte object.**
  `lbl_1_data_FBD` (rep_0250) and `lbl_1_data_1CA1` (rep_02A8) became `FBE`/`1CA2` size 0x2.
  Defining the pad as a zero object moves it to `.bss` and shifts everything after it.
- **The data pool base is the section's first static, and MWCC pools only when a function
  references about three or more distinct statics.** One big struct, or non-static globals,
  give `lis/addi` per access. A `u32[4]` that forced a second base register had to become
  four scalars (`rep_02A8`).
- **`.bss` statics pack tightly in reverse declaration order with no alignment fill.** Fill
  gaps with `u8`/`u16` pad statics. Pad arrays get 4-byte aligned (`rep_0250`).
- **Loop shapes:**
  - `subic.`/`bne` with no entry test is `do { } while (--n)`.
  - A `ctr` loop unrolled by `(n+1)>>2` behind `cmpwi n,0; blt` is
    `for (i = n; i >= 0; i--)`. The up-counting form unrolls by 8 and was about 450 bytes
    larger (`rep_0010`).
  - A plain `for` with a constant trip count was fully unrolled.
- **Local arrays make MWCC hoist `&arr[k]` into callee-saved registers at entry. Separate
  scalars don't.** `Vec t[3]` instead of three `Vec`s took `rep_00B0` `fn_1_4A24` from 74% to
  91%.
- **Switch shape follows the case labels exactly.** Empty `case` labels reproduce a
  binary-search tree, and a spurious extra case changes it. Stacked `case 1:`...`case 9:`
  give a range test.
- **A `SND_FXID` argument wants a `u16` local:** `u16 id = tbl[i / 13] + i % 13; fn(id);`.
  `s32`, `u32` and a direct expression all missed (`rep_02A8` Voice screens, 92% to 100%).
- **Decrement then signed test of a `u8` static needs two statements:**
  `x--; if ((s8)x < 0) x = N;`. `if ((s8)--x < 0)` puts the `extsb` before the `stb`.
- **Unowned `.text` gaps in the debug REL.** These ranges are in no unit's split:
  0x1538-0x19AC, 0x4DD8-0x4E98, 0x85A8-0x8CD4, 0x9EA0-0xA2E4,
  0x17EFC-0x182C0, 0x1D590-0x1D694 and 0x26AF8-0x26B7C. (0xC2A4-0xC5AC is resolved:
  `fn_1_C2A4` went to `rep_02A8`, and `rep_0610` now starts at 0xC2DC.) Evidence so far:
  - 0x85A8-0x8CD4 only references `rep_0250`'s `.data` (`skyPanoramaFileDescriptorDebug`).
  - 0x9EA0-0xA2E4 uses `rep_02A8`'s data and functions.
  - A static in a unit that a gap function references blocks that unit's flip until the gap
    joins it.

### Debug REL second passes (rep_0250, rep_02A8 flipped to Matching)

- **A merged dtk `.bss` label costs `.text` too, not just `.bss`.** objdiff infers a
  relocation for every pooled `off(rN)` access and compares the symbol it lands in. With
  `lbl_1_bss_2FDF` covering 9 bytes, byte-identical functions scored 97-99%. Splitting
  symbols.txt at the real variables took both units to 100% in every section. Bytes no code
  references need no entry.
- **A small loop repeated in several callers, differing only in its register, is a missed
  call to an existing helper.** Calling `fn_1_A718()` (which MWCC inlines) fixed the loop
  counter in `sndTestSeScreen` and `fn_1_A95C`. Likewise, moving an inline
  `do { a[k + i] = 0; } while (--i);` into a `static inline` helper swapped the
  counter/pointer registers onto the target's r4/r5 (`rep_0250` `fn_1_9AB0`).
- **`switch (item->state)` and `switch (currentDrawingItem->state)` both load once, but
  colour `item` differently** (r28 vs r29). When a cached pointer local is one register off,
  try the global expression.
- **A `clrlwi r3,rX,16` the target keeps on a value it loaded with `lhz`/`lhzx` points to an
  `s16` parameter** on the callee, not `s32`/`u16` (`fn_1_BF34` in `rep_02A8`).
- **`lbz rX; extsb rX,rX` (same register) means the variable itself is `s8`.**
  `lbz r0; extsb rY,r0` is a `u8` read through an `(s8)` cast.
- **Coordinating several agents in one tree:** a symbols.txt/splits.txt/configure.py edit
  while other agents run `ninja` makes every ninja re-run the dtk split at once. They
  corrupt `.ninja_deps`, and ninja then re-splits forever: each manifest restart prints
  `premature end of file; recovering` and truncates away the split's fresh deps record. Fix:
  stop all ninja/dtk processes, run `ninja -t recompact`, then build once. Avoid it by
  applying shared-config changes only when no agent is building.
- **The stack slots of int-to-float temps show the order the compiler created them in,
  which can differ from the order of the instructions.** In `rep_0010` `fn_1_AF4` the
  target schedules the `xoris/stw/lfd` conversions x0, z0, xLen, but they sit at sp+0x10,
  +0x18, +0x08, so xLen's conversion was created first. Reordering the source statements
  to that order took 95.67% to 98.67%. The remaining float-register permutation was then
  pure local declaration order. Declaration order showed "no effect" until the statements
  were right, so re-test it after every structural change.
- **Iterate privately without touching the build tree.** Take the unit's mwcceppc command
  line (`ninja -t commands <obj>`), compile a scratch copy of the `.c`, and compare one
  function's bytes word by word against the target `.o` via the ELF symtab. At about 0.7 s
  per variant, brute-force sweeps (all 120 orders of five stores, every declaration order)
  are cheap and never race other agents (`rep_7BF0`, `rep_0010`).
- **When deleting LATER code changes the entry block's register numbers, the colouring is
  global.** In `rep_7BF0` `fn_1_29A9C`, deleting the inlined helper or a later call moved
  the entry registers, but none of 19 source-equivalent rewrites of either part did,
  including version and flag sweeps. Treat that as a sign to stop.

## Findings from the debug REL second passes (rep_0610, rep_74A0, rep_0138, rep_0010 TU boundary; 2026-10)

- **A float multiply by a power-of-two reciprocal (`x * 0.0009765625f`) puts the constant FIRST
  in the fmul/fmadds; a division (`x / 1024.0f`) puts the converted value first.** MWCC
  strength-reduces the division to the same reciprocal multiply, so the operand order is the
  only tell. `rep_0610` `fn_1_11D00`/`fn_1_11F08` (+2..4 points each, plus the caller
  `fn_1_121D4` that inlines them). The same swap fixed the inlined copies in `rep_7730`
  `fn_1_25064` (`/ 64.0f` vs `* 0.015625f`).
- **A redundant cast of an already-typed pointer (`((T *)p)->e[i].f`) changes how MWCC
  associates the address.** It folds the member offset into the index
  (`addi r0, i*sz, off; lwzx base, r0`) instead of `add; lwz off(r)`. Use it only where the
  target shows that form; applied everywhere it costs elsewhere (`rep_0610` `fn_1_ECF8` +6,
  `fn_1_CDC8` +5).
- **A loop the target enters with `b test` before the body is a `while`/`for`, not a
  do-while,** even when the do-while body is otherwise identical
  (`rep_0610` `fn_1_D7A4` +12, `fn_1_D9B8` +1.5).
- **An unreferenced initialiser in .rodata between two functions' literals is an unused local
  aggregate** (`GXColor c = {...};`): MWCC emits the initialiser at parse time and
  dead-strips the copy.
- **Parse-time .rodata (local aggregate initialisers, and the strings of .data tables) is laid
  out in source order,** so .data tables that own strings must be defined between the right
  functions, not all at the top of the file (`rep_0610` .rodata 99.76 -> 100).
- **Hand-written copies of blocks that the target got by inlining a helper cause callee-saved
  register swaps in the caller.** `rep_74A0` `fn_1_1857C` only lost its p/arr swap once its
  GX setup and depth sort were real functions (`fn_1_18174`, `fn_1_17FF0`,
  `sortParticlesByDepth`) called from it and inlined by `-inline auto`. Unowned functions with
  no callers next to a unit are good candidates for such helpers.
- **A source shape can fail only because a callee's prototype is wrong.** `rep_74A0`
  `fn_1_1A290` (the "entry pointer first, checks still through the array" loop) scored
  98.41 until the callback type was fixed to take the entry, then 100.
- **dtk's gap-sized .bss/.data labels cost points even in instruction-identical functions.**
  objdiff resolves `lbz r0, 0x8(r31)` off a pool base to `lbl_1_bss_3070+8` on the target side
  and to our `lbl_1_bss_3078` on ours. Splitting the labels at the real object boundaries
  took `rep_0610` .bss from 52.5% to 100% and turned several functions into 100s with no
  source change.
- **Jump tables give TU boundaries that rodata doesn't.** MWCC emits a TU's jump tables at the
  end of its .data, in function order. The debug REL's .data block at 0x0 ends with the
  tables for `fn_1_1E0` and `fn_1_16A0`, which showed that the code on both sides of
  `rep_0010` (which has no rodata of its own there) is one TU with it. Likewise a data object
  whose only user sits just before a unit's .text belongs to that unit when the data sits
  after the unit's other data (`fn_1_196C` and `lbl_1_data_298` -> `rep_00B0`).

## Findings from the debug REL gap merges and second passes (rep_0010, rep_0138, rep_0250, rep_02A8; 2026-10)

- **Wrap-around of a small struct field is a pre-increment inside the condition:**
  `if ((s8)++state.field >= N)` / `if (--state.field < 0)`. The `v = field + 1; field = v;
  if ((s8)v >= N)` draft has the right instructions but swaps two scratch registers. Floats too:
  `if (++p->nearZ > 512.0f)` gives the target's `fadds f1, field, one` order (`rep_0138`
  `fn_1_6848`, `fn_1_6E14`, `fn_1_7FF8`).
- **Callee-saved registers, int and float, follow declaration order (first declared = highest
  register) unless compiler temps intervene.** Hoisted loop invariants (`xoris w,0x8000`,
  `lis 0x4330`) and CSE'd global addresses take registers of their own and break the rule. A
  matched sibling with the same locals is the best source for the order (`rep_0138`
  `fn_1_5AC0` read its order off `fn_1_6050` and went to 100). Variable reuse decides coalescing:
  reuse a local where the target shares a register, and drop explicit locals for products MWCC
  hoists itself (`ny * ny`).
- **An inlined callee's registers depend on the variable reuse of its source.** `rep_0138`
  `fn_1_717C` matched standalone with separate locals per half, but its inlined copy in
  `fn_1_6848` only matched once one `set`/`geo` pair was reused for both halves.
- **Switch shapes in the debug REL:** `cmpwi 2; beq; bge; b` came from
  `case 0: case 1: break; case 2: {...}`; a two-value switch testing 2 before 3 needed an empty
  `case 1:`; a "7 cases plus a range" dispatch needs the range spelled out (`case 2:` ...
  `case 18:`) to get the 0/1/range decision tree; `default:` scored 96 (`rep_0010` `fn_1_1E0`).
  A case that falls into the next one but whose guard branches to the end is
  `if (cond != X) break;`, not `if (cond == X) {...}` (`rep_02A8`).
- **`a * 4 + b * 4` in one expression is factored to `(a + b) << 2`.** Two separate shifts in the
  target mean the terms were not one plain sum: either one was written as a shift
  (`(y / 4) * w * 4 + (y % 4 << 2)`), or, as `rep_0138` `fn_1_5924` turned out to be, a term was
  computed in its own statement first (see the division-order note below).
- **Shared stack offsets for three cross products = one reused `Vec` local**, and one
  `sin(half)`/`cos(half)` pair computed up front; drafts that repeat `sin(half)` emit three calls.
- **MWCC fully unrolls a 5-iteration `for` over a `u32` pointer table** into the target's
  "`addi r3,r31,8` + mixed r31/r3 displacements" shape; five hand-written `if`s do not
  (`rep_0010` `fn_1_20`/`fn_1_E8`, 97.4 -> 100).
- **A cached pointer local for a repeated global-array access can hoist a `lis/addi` the target
  lacks;** write the cast expression at each use instead (`rep_02A8`).
- **An unused-result string walk with one extra `mr` is a missed inline:** write it as a
  discarded call to a strlen-style `static inline` helper. Then the remaining register order was
  one specific local declaration order out of 720 (`rep_02A8` `fn_1_A184`, 91.96 -> 100).
- **A unit whose first .rodata object is not the `header_rep_data.h` table needs that first
  object to be a weak local static as well** (a `static const` array inside an `inline` helper
  with a unit-unique name). A plain `static const` makes the first object non-weak, and every
  float-pool function in the unit switches to base-register addressing (`rep_0010`
  `lbl_1_rodata_0`; `fn_1_5EC` fell to 69% without it).
- **A function that is only called from one place can still need `#pragma dont_inline`** when the
  target keeps it out of line: `rep_0138` `fn_1_4DD8` was auto-inlined into `fn_1_717C`
  (717C 100 -> 11.5) until wrapped.
- **Pooled static addressing needs about three distinct static objects in the function.** With one
  or two, MWCC addresses each through its own `@ha/@l`, even when they are static. So a target
  that keeps the section base in a register and reaches several objects as `base + off` had at
  least that many separate statics: split dtk's symbols at those offsets rather than merging them
  (`rep_0010` `fn_1_1538`: three statics `lbl_1_data_70[2]`, `_A0`, `_A4` took it from 62 to
  instruction-identical; one struct or two statics did not pool).
- **Flipping a widened unit: objdiff 100% is not enough, run the sha check.** Two layout faults
  scored 100% in objdiff and still failed the REL: a `.data` split that ran over the padding up to
  the next unit (end it where the last object or jump table ends), and two `.bss` statics declared
  in the wrong order (MWCC lays `.bss` out in reverse declaration order, and objdiff matches by name,
  so only the relocation addends in the linked REL changed). Diff the REL's relocation table when
  the section sizes agree but the sha does not (`rep_0010`).
- **A local array element accessed through a cast to another pointer type (`((f32 *)&v[k])[n]`)
  gets its own address register,** and every offset-0 access and struct copy of that element then
  goes through it; pointer casts on call arguments have no effect at all (`rep_00B0` `fn_1_4A24`,
  diagnostic only). A same-type explicit cast (`((Vec *)&e[2])->x` on a `Vec e[3]`) does the same.
- **With eight or fewer locals, sweep every declaration order instead of hill-climbing.** 8! = 40320
  variants is cheap with a scratch compile; `rep_00B0` `fn_1_25BC`'s earlier hill-climbs had stopped at a
  local optimum below the best order (99.55 -> 99.59).
- **When the target has a function both standalone and inlined, first write the real function and
  call it;** MWCC inlines it into the callers by itself. A `static inline` copy plus a wrapper for the
  standalone symbol changes the standalone function's registers (`rep_0610` `fn_1_D300`; earlier
  `rep_7730` `fn_1_21180`). **If no declaration order matches both copies** (each order fixes one),
  switch to the `static inline` helper with the real function as a one-line wrapper: the helper's
  numbering then applies to both (`rep_0610` `fn_1_126CC` 33 -> 100 and its inlining caller
  `fn_1_179CC` 50 -> 100, helper declared with `f32 z, y, x`).
- **A float literal loaded as `addi rX, lit@l; lfs 0(rX)` instead of `lfs lit@l(rX)` came in
  through an inline function's parameter** (`rep_0610` `fn_1_EA20` -> `dbgSetFrame`).
- **A one-trip loop (`for (i = 0; i < 1; i++)`) explains constant `[0]` indexing combined with
  induction pointers set up before the "loop"** (`rep_0610` `fn_1_17B5C`: per-player code with one
  player).
- **`(T *)((u8 *)p + off)` is CSE'd across calls; `&p->bytes[off]` is not** (`rep_0610`
  `fn_1_121D4`).
- **Splitting `v = (f32)x / 64.0f;` into `v = (f32)x; v /= 64.0f;` moves the constant load after
  the int-to-float conversion** (`rep_7730` `fn_1_24A8C`, 92.7 -> 100).
- **Drafts can be wrong in ways that still score 90%+.** `rep_0610` `fn_1_DF14` processed one
  element too many (a do-while where the target's `while (k-- != 0)` skips k = 5), and `fn_1_12F8C`
  wrote four flags to the wrong struct. Check loop bounds and store targets before treating a
  90-95% function as a register problem.
- **A REL unit can have been built against a narrower prototype than the DOL.**
  `insertGraphicDrawingFunction`'s priority is `u32` in its definition and for the DOL callers:
  with `u16` the definition drops from 100 to 96.5, `sta_c4` `fn_3_F9E78` loses 1.5, and the Matching
  `File_0x800486e0` fails the sha check. But `rep_0610` `fn_1_D13C` only matches when the int argument is
  narrowed by an implicit conversion through a `u16` prototype (`addi; clrlwi r4, r0, 16` scheduled
  after the other argument setup). An explicit `(u16)` cast or a `u16`-parameter `static inline`
  schedules the `clrlwi` elsewhere. MWCC rejects a conflicting redeclaration, so the header declares the
  `u16` form under `#ifdef DRAWING_PRIORITY_U16` and only that unit defines the macro. Test a prototype
  change with a project-wide report diff (header and definition changed together) before applying it.
- **Loop-invariant products as locals before a loop and the same expression inline at each use
  are hoisted to the same place, but colour the conversion temps differently.** If a function
  computes `k * (f32)x` constants up front and the int-to-float temps land in the wrong registers,
  delete the locals and write the expression at every use (`rep_7730` `fn_1_22874` -> 100).
- **Read a callee's prototype off its caller.** `mr r3, rX; bl f` before a callee that never reads
  r3 means it takes an unused parameter; `cmpwi r3, 0` after the call (not `clrlwi. r0, r3, 24`)
  means it returns int, not u8. Fix the prototype even when the callee already matches
  (`rep_7730` `fn_1_21CE8` calling `fn_1_22874`).
- **Repeated `arr[n - 1].field op= ...` updates: hold the base in a pointer local** assigned in the
  same block, after any preceding branchy code, when the target keeps one base register
  (`add rT, base, n<<6; lfs disp(rT)`) and ours turns later updates into `subi; lfsx`. Int-to-float
  conversions whose loads the target hoists above a run of float stores want integer locals converted
  at the use, not float locals (`rep_7730` `fn_1_21408`). For signed bytes, `lbz rA; extsb rB, rA`
  with rA != rB is a `u8` local converted as `(f32)(s8)x`; `s8` locals give `extsb rA, rA`, and
  `s32 x = *(s8 *)p` scored lower (98.47 vs 98.99).
- **`subi rB, &sym, C; lfsx f, rB, idx<<n` (the constant applied to the base register, not to the
  displacement or the index) is `arr[x - 1]` written more than once on a typed array.** MWCC turns
  `arr[x - k]` into `(arr - k*size) + x*size`; when `arr - k*size` occurs twice or more it is CSE'd
  into its own register, with one occurrence it becomes `lfs -C(add)`. Casting a byte buffer
  (`((T *)buf)[x - 1]`) blocks it, and so do locals for the index or the loaded value: declare the
  static as `T arr[N]` and write `arr[item->n - 1].f` at each use (`rep_7730` `fn_1_247A0` 75.7 -> 100,
  its inline copy in `fn_1_25064` -> 100). Worth checking anywhere a static is still a `u8[]` buffer.
- **`add rD, rBase, rOff` gives rD the base's register whenever the base dies at the add,** for every
  pointer form (`p = &arr[n - 1]`, `p = base; p += off`, byte arithmetic, helpers). When the target has
  a fresh rD there, use an index local plus the typed subscript at each use (`s32 last = n - 1;
  x = arr[last].pos.x; ... arr[last]._3C = ...;`) and let MWCC merge the address itself. `int` scores the
  same as `s32`; `u32`/`u8` indices and a struct copy score lower (`rep_7730` `fn_1_21180` -> 100, and its
  inlined copies in `fn_1_22DF4` / `fn_1_22644` with it).
- **When only the float scheduling of a run of independent statements is left, search statement order
  as a whole:** random moves checked against the data dependencies and scored on the whole unit found
  gains that permutation sweeps of sub-groups missed (`rep_7730` `fn_1_23098` 34 -> 24 mismatched
  instructions).
- **A float store of an `frsp`'d register (`frsp f4, f30; stfs f4, off`) is a field-to-field copy of
  an already-stored float** (`base[3].z = base[1].z;`): MWCC forwards the earlier store and rounds the
  forwarded value (`rep_7730` `fn_1_23098`). On its own it scored lower; the callee-saved FP numbering
  only matched once the constant-zero stores also came first in the source.
- **Two signed divisions in the wrong order are not a scheduling problem.** Each `srawi`/`addze` pair
  uses XER[CA], so they stay in codegen order, and MWCC's reassociation of one `+` chain always emits a
  multiply-by-constant term (`(x / 8) * 32`) before a multiply-by-variable term (`(y / 8) * w`), whatever
  the source order. Compute the variable-multiply term in its own statement first. A fresh local is
  substituted back, so reassign the parameter (`w = (y / 8) * w;`). Reusing the other parameters for
  their derived values too (`x %= 8;`) put more temps on the target's registers; a fresh local in
  place of either cost 4-33 points (`rep_0138` `fn_1_5924` 72 -> 97.8, after 480+ single-expression
  term orders that could never have matched).
- **A "missing loop guard" can be an `if` inside the loop body.** When the target's
  `cmplwi i, N; bge` sits at the loop head, the back edge jumps to it, and the branch goes to the middle
  of the body rather than past the loop, it is `if (i < N) { ... }` around part of the body
  (a real vestigial entry guard branches past the loop). `rep_74A0` `fn_1_1C8C0` 96.1 -> 98.8,
  then 100 after a declaration-order hill-climb; two earlier passes had read it as a vestigial guard.
- **A vestigial loop guard that tests the induction register itself** (`li r5, 0; cmpwi r5, 0x18; bge`,
  with r5 then used as the offset) instead of `li r0, 0; cmpwi r0, N` plus a separate `li rX, 0` means
  the same variable was already a loop variable EARLIER in the function. A loop on another variable, a
  later loop, or a loop that folds away doesn't count (a micro TU shows the rule), and the guard itself
  is only kept when the compare mixes types (`s32 i` vs an `int` literal, or `int i` vs `24L`).
  So this guard shape is evidence of an earlier loop on `i`: `rep_0610` `fn_1_135C0`'s five hand-written
  pointer fix-ups were really `for (i = 0; i < 5; i++)` (-> 100), `fn_1_16978` case 26 is a one-trip
  `for (i = 0; i < 1; i++) fn_1_D7A4(i);`, and `rep_74A0` `fn_1_1D110` reuses the previous loop's
  `int i` against `(s32)PARTICLE_SLOT_COUNT`.
- **An instruction-identical function whose frame is 0x10 too big has a local array that is too
  large.** MWCC rounds the end of the local area up to 8 bytes and the frame up to 16, so a 4-byte
  overshoot can cost 0x10. Sweep the array size down (`rep_0610` `fn_1_1540C` `u8 buf[0x28]` ->
  `char buf[32]`, 99.97 -> 100; several sessions had read it as a dead spill slot).
- **A register permutation in a loop whose bound and body index the same nested table can be a getter
  inline used at both sites:** `static inline DbgAnimTrack *dbgGetTrack(anim, track)` took `rep_0610`
  `fn_1_EA20` from 99.20 to 100, where a cached pointer local for the bound left the permutation. The unit
  already had an out-of-line getter of the same shape (`fn_1_16558`), which was the hint.
- **An lr reload after the callee-saved restores** (`lwz r31...; lwz r0, 0x24(r1)`), where the usual
  epilogue reloads lr first, means the original's epilogue was its own basic block. One cause is a
  missing return value: `rep_0610` `fn_1_D300` really returns the `DbgActor *` already in r3 for its
  last store (`(act = actors[i])->model = ...; return act;`), which gives the lr-first epilogue with no
  extra code (99.73 -> 100). Its callers all inline it and ignore the result. `return src` /
  `return NULL` instead add an `mr`/`li`.
- **Switch on the global expression, not on a local copy of it:** `switch (currentDrawingItem->state)`
  where `scene == currentDrawingItem` fixed a three-register rotation (`rep_74A0` `fn_1_1CBE4` -> 100;
  same as `rep_0250` / `rep_02A8`).
- **Int-to-float conversion temps (the 0x43300000 double slots) reuse stack slots last-in-first-out
  across sibling control regions, never within one straight-line run.** Nested control flow between two
  conversions (if inside if, `&&`/`||`, a switch, a loop, or an inlined function call) lets the later one
  reuse the earlier slot, so a rotated set of temp slots is a control-flow clue, not a declaration-order
  one (`rep_74A0` `fn_1_1857C`, found with a micro TU).
- **`fabs` is an inline function in MSL, and `include/stl/math.h` now defines it that way** (it was a
  macro for `__fabs`). Both give the same instructions but different stack-temp and FPR allocation.
  `rep_74A0` `fn_1_1857C` and `star_dash` needed the inline form (1857C also needed `sinf_kludge` /
  `cosf_kludge` for the sin/cos of an f32). The header change took five `minigame_effects` functions to
  100. `sta_c5` `fn_3_EE388` / `fn_3_EE96C` and `camera_script` `fn_3_FDB30` dipped slightly; writing
  `__fabs` at their own call sites did not restore them, so the dip comes from elsewhere in their units.
- **A parameter reassigned in a loop may need to be a local copy** (`DlPrim *p = prim;`): in a micro TU a
  plain parameter always got the lowest callee-saved register, even when reassigned, where the target
  gave it the highest (`rep_00B0` `fn_1_25BC`, together with a declaration-order search).
- **Random-restart hill climbs over declaration order reach the exhaustive 8! optimum much faster,** so
  they are the cheaper way to test each structural variant together with declaration order (`rep_00B0`).
- **A cast that routes offset-0 reads through the address register always schedules that `addi` early**
  (above the parameter copies). If the target has those reads but a late `addi`, the cast wasn't in the
  original (`rep_00B0` `fn_1_4A24`).
- **Score a function's inlined copies with it when choosing its source form.** Most forms of
  `rep_0138` `fn_1_5924` that scored 98+ standalone cost its inlined copies in `fn_1_6050`/`fn_1_5AC0`
  0.2 each; filtering the sweep on "callers stay 100" found the form to keep.
- **Constants held in callee-saved FPRs across the first call are hoisted out of a one-trip loop.**
  `0.0f` (addi form) in f31 and `57.29f` in f30, loaded before `CTRLSetTranslation` and reused by a
  later `speed != 0.0f`, came from `for (k = 0; k < 1; k++) {...}`, the per-player loop with one
  player (`rep_0610` `fn_1_129D0` 92.5 -> 97.3; same family as `fn_1_17B5C`).
- **A loop counter the target copies from a register (`mr r6, r3`), plus a stored zero that reuses
  the register that held an earlier 0, means the loop variable is a register-promoted global:**
  `lbl_1_bss_5F73 = 0; do { a[lbl_1_bss_5F73]...; lbl_1_bss_5F73++; } while (lbl_1_bss_5F73 < 1);`,
  not a local copied into the global afterwards (`rep_0610` `fn_1_1496C` 96.8 -> 97.8).
- **`const` on an inline helper's parameters is not neutral.**
  `static inline void dbgVertex(const f32 x, const f32 y, const f32 z, const u32 c)` around
  `GXPosition3f32` / `GXColor1u32` took `rep_0610` `fn_1_10E2C` to 100, while the same helper with
  plain parameters was byte-identical to open-coded calls. The SDK's own GX inlines mostly take
  `const` parameters.
- **"All pos loads before any store, one store per component" is locals loaded first and then
  updated** (`x = a->pos.x; y = ...; z = ...; x += ...; y += ...; y -= ...;` then the stores), a
  different shape from `x = a->pos.x + ...`. The int-to-float conversion stack slots ascend in source
  order, which reads the original statement order off the target (`rep_0610` `fn_1_126CC`).
- **`int` and `s32` (`signed long`) are not interchangeable for MWCC:** `rep_0610` `fn_1_16978`'s
  counter scores 99.80 as `s32` and 99.61 as `int`. The other way round, `rep_0138` `fn_1_5544`, which
  mostly forwards its parameters to GX calls taking `int`/enum, only matched with `int` parameters: as
  `s32` the two pool-base `lis` temps were coloured differently. For such forwarding functions, try `int`
  parameters first.
- **An extra unreachable `b end` after a `cmpwi N; beq; bge end; b end` switch tree is an empty case
  above the highest handled one** (`case N + 1: break;`). `rep_0138` `fn_1_4E98`:
  `case 0: case 1: break; case 2: {...} case 3: break;` -> 100, after ~30 variants of the 0/1 bodies.
- **Shrink a register puzzle to a micro TU.** Cut the unit down to the one function (no other functions,
  no unused statics) to confirm the effect is local, then rebuild it in a tiny TU with hand-written
  prototypes and swap pieces (headers, typedefs, prototypes) back in until the output flips. For
  `fn_1_5544` the flip was `#include "types.h"`, which led to the `int` parameters.
  **A debug-REL micro TU must include `header_rep_data.h`'s weak inline local static** (or an equivalent
  first `.rodata` object). Without it MWCC addresses the literals off one pooled section base, which
  frees a GPR and changes the colouring: `rep_74A0`'s first micro TU "reproduced the target" only because
  of that, and sent a whole pass after the wrong code. Check that the micro TU reproduces OUR real output
  (0 words different) before trusting what it says about the target.
- **Before grinding a stuck debug-REL function, scan the other modules' target asm for its twin.** Debug
  routines are often copies of game-REL (or DOL) ones, and a matched twin's source is direct evidence of
  the original shape. `rep_00B0` `fn_1_4A24` (99.46 -> 100) is `game/ball/collision_primitives`
  `checkTriangleCollisions`, found by scanning every target `.s` for its distinctive signature (a hoisted
  `addi rN, r1, X` used both as a call argument and as `0x0(rN)`, with `X+4(r1)` also read directly). Port
  the twin's source, then revert one feature at a time to find what mattered.
  The twin can be in the same unit: a scan ranking functions by shared 8-instruction mnemonic runs showed
  `rep_7730` `fn_1_1F618`'s TEV-stage loop is `fn_1_20640`'s body (calling it: 98.47 -> 99.29, all
  registers right). The inlined copy still re-read `entries[i]` where the standalone keeps it in a
  register, so 1F618 needed its own inline copy with the re-read (-> 100). A re-read of a local array
  element is a tell that an inlined copy and its standalone function differ in the source.
  A DOL twin closed `rep_0610` `fn_1_14710` (94.20 -> 100, after ~50 shapes over five sessions): it is
  `initShortsHandleCompressedDiskReads` (`File_0x8001fc4c.c`). Porting its three static inlines (a pair
  swap; a for loop; a do-while with a separate index for the test and pointer for the body,
  `while (pairs[++i][0] != END)`) explained the "two induction variables".
- **When a block's schedule ignores statement order, probe the other statements one at a time.**
  `rep_0610` `fn_1_F37C` (stuck at 91.7 for several passes): 400 random orders of its pos/vel/acc
  stores gave the identical post-call schedule, so the order came from the dependence graph. Deleting
  or rewriting each other statement in a micro TU, one at a time, found the cause: a flag written as
  `(BTN_REPEAT >> 12) & 1` instead of `(BTN_REPEAT & INPUT_BUTTON_START) != 0`. The `!= 0` form gives
  exactly the target's order (-> 100).
- **A byte-offset read of a global (`*((u8 *)&g + 0x70)`) may alias every store; a named member
  (`g._70`) does not.** With the member, MWCC's alias analysis separates the loads from unrelated
  stores, and the scheduler is free to order them as the target does. Adding named controller-4
  stick fields to `lbl_803C77B8_s` took `rep_7730` `fn_1_21CE8` to 100 and `fn_1_21408` to 99.95, with
  no change anywhere else in the project. The same switch through a parameter pointer (`item->_1c` vs
  `*(f32 *)((u8 *)item + 0x1c)`) made no difference.
- **Re-read an already-stored value, then search statement order again.** `ray[3].y = -ray[2].y;` and
  `ray[2].z = nearZ - base[2].z;` (where `base[2].z` and `base[3].z` hold the same value) are nearly
  score-neutral alone, but they free stores to move. From that form a dependency-checked order search
  reached 100 for `rep_7730` `fn_1_23098` after its old plateau had held through 250+ iterations.
- **When the target and ours have the same interference graph, score-only climbs get trapped on ties.**
  Penalise the specific wrong registers in the search objective. That found a `rep_00B0` `fn_1_25BC`
  form with a single wrong choice, which score-only climbs never reached. Address CSE temps such as the
  `&__GDCurrentDL` loads take one register as a group, so one wrong neighbouring web can cost 100+ lines.
- **`rep_00B0` `fn_1_25BC` (the last debug function stuck on one register for six passes) closed
  with:**
  - the [G3] "point C" shape (a separate `DlVertex *v2` for the triangle loop; counters reused across
    the strip and linestrip loops; `left` for the vertex-count loop);
  - declaring `left, vi, v, key, i, cnt, n, p, v2, prev`;
  - merging the duplicate `u8 keyToIdx()` helper into the `u32 keyIdx32()` one at the `dlVertexKey`
    call site.
  An inline helper's return width is one more knob on when its result web is coloured.
- **An induction-variable increment the target emits before another one can sit mid-body in the
  original, not in the for-header.** `rep_7730` `fn_1_22F4C`:
  `j = 0; while (j < m) { s32 t = k++; ...; dst[t] = ... - prev; j++; dst[t] *= damp; }` (99.76 -> 100,
  and `fn_1_23B54`, which inlines it, gained with it). Sessions S5-G3 had not moved that k/j order tie.
- **To find what sets a wrong callee-saved order, cut the function down inside the full unit** (leave
  everything else as is) and add pieces back one at a time. In `rep_7730` `fn_1_23B54` this showed a
  hoisted pool base outranks `item` once it is live across two or more calls; the target keeps `item`
  on top regardless (still open).
- **Store through the global, not a local copy of it:** `currentDrawingItem->func = f;` instead of
  `s->func = f;` with `s == currentDrawingItem` fixed a register rotation across the whole block
  (`rep_0610` `fn_1_E098` case 10, 99.62 -> 99.94), the same family as switching on the global.
- **`while (TRUE)` and `for (;;)` compile differently.** In `fn_1_4A24` the outer loop keyword alone took
  it from 99.46 to 99.90, after a pass had concluded from micro TUs that the pattern was unreachable from
  source. Try the loop keyword before declaring an address-register pattern unreachable.
- **MWCC's register allocator can be observed directly.** A native Windows debugger (Python ctypes,
  no gdb) that breaks GC/2.6 `mwcceppc.exe` at the end of `colorgraph` (0x5089A9; addresses from
  github.com/cadmic/mwcc-debugger) dumps the GPR/FPR priority list, each node's neighbours and coalesced
  flags, and the PCode before register allocation. Re-simulating Chaitin's simplify reproduces every
  function in `rep_0138` exactly: vregs in index order, push a node when it has fewer than 29 remaining
  neighbours, repeat passes, and never remove coalesced nodes. A target colouring can then be
  reverse-engineered into "which node must move to a later pass" before touching source. This is how
  `rep_0138` `fn_1_73B8` went from 99.14 to 100 after five passes. The tools are `regdbg.py`, `sim.py`
  and `col.py`.
- **Callee-saved order is simplify level first, then descending vreg index.** Parameters are the lowest
  vregs, then locals (first declared = highest), then frontend temps (strength reduction, range-split
  pieces, LICM), then backend temps such as a CSE'd global address. A variable outranks a higher-index
  temp only by surviving into a later simplify pass, i.e. by having 29 or more remaining neighbours when
  its turn comes.
- **Coalesced nodes and self-hoisted invariants add neighbours for free.** Writing a loop-invariant
  expression inline (`((DbgDrawNode *)arg0)->world` in the loop body) instead of a local set before the
  loop gives the same instructions, because MWCC hoists it, but adds never-removed nodes. That pushed
  `fn_1_73B8`'s long-lived locals into a later level (-> 100); holding the value in your own local lost 5
  points. A local used twice (`MtxPtr m = geo->mtx; PSMTXConcat(c, m, m);`) also adds a node. Single-use
  locals, inline parameters and constants are always propagated away.
- **Casting a struct-pointer local at every use (`(u8 *)item + off`) makes MWCC CSE the cast into a
  frontend temp that replaces the local.** The initial PCode shows `lwz rT, global; mr rItem, rT`, and
  every use then reads rT, so the "local" is coloured as a temp above every real local and declaration
  order can't move it. Cast once at the initialiser instead, ideally to a typed view struct:
  `View *item = (View *)currentDrawingItem;` with member access. Then the locals rule applies
  (`rep_7730` `fn_1_2004C` -> 100 with `u32 i;` declared above it; `fn_1_23B54`'s item/pool swap fixed by
  declaring `item` after `gr`).
- **Two swapped volatile registers at the same simplify level are decided by vreg index, and frontend
  variables always number below backend temps.** An inlined callee's `val` local lost to a backend address
  temp. Storing the value straight into its destination and reading it back
  (`*(u32 *)(blk + 0x20) = src; ratio = c1 / (f32)*(s32 *)(blk + 0x20);`, which compiles identically
  through store-to-load forwarding) made it a backend temp (`rep_7730` `fn_1_21408` -> 100).
- **Hoisted loop-invariant temps are numbered in descending program order.** When the target colours
  one invariant below the rest, that value was a source local: `rep_0610` `fn_1_E098` needed
  `row = lbl_1_bss_30B6;` as a local, and the held-button test written in the loop through the global
  (`AtBat_ButtonInput1._00 & INPUT_BUTTON_A`) so MWCC hoists it. The `BTN_HELD` cast macro isn't
  hoisted (96.77). -> 100.
- **A local with two definitions is not folded back into its use; one with a single definition is.** To
  make MWCC evaluate an index before its base, build the index in two steps:
  `s32 idx = (s32)u; idx += (s32)(16.0f * v) * 0x80; p->y = rows[ping & 1][idx];`. A single-definition
  local or an inline-helper parameter was folded back, and 38 plain-expression arrangements all built the
  base first (`rep_7730` `fn_1_23B54` -> 100).
- **An if/else assignment followed by `v = c * v` is merged into one conditional expression** (the
  constant gets loaded before the branches). A `static inline` helper that assigns its parameter in each
  branch and ends with `return x;` keeps the target's constant placement. Returning from each branch
  scored lower (95.02 vs 97.02).
- **`*p = old + 1` and `*p += 1` on a u8 can change the post-allocation schedule with identical
  registers:** the first left a dead zero-extend in the block (`fn_1_23B54`'s last two-instruction swap).
- **A float that lands in f1 for no visible reason** (target `fctiwz f0, f1` where ours has
  `fctiwz f0, f0`, with nothing else touching f1) **is a value passed on to a call.** Check whether a
  callee is a dispatcher (`lwzx r12; mtctr; bctrl`, never touching f1) whose real prototype has a float
  parameter: `rep_0610` `fn_8004B208(a, b, c, v)`. `fn_1_D590` itself is byte-identical because `v` is
  already in f1, but its inlined copy in `fn_1_129D0` went f0 -> f1.
- **An inline function's own pointer local (`T *h = &global;`) is fully copy-propagated, even as the base
  of a strength-reduced loop; a caller-scope local used the same way keeps a `mr` copy.** When the target
  shares one register between an address temp, a loop IV's start and a later `base + off`, put the address
  local, the loop and the derived pointer inside one static inline that returns the derived pointer
  (`rep_0610` `fn_1_129D0` 98.02 -> 99.72).
- **`s32 on = boolFn();` stays a real local through the int -> long conversion, where `BOOL on` is
  copy-propagated into its compare temp.** A kept BOOL tested with `cmpwi rX, 0` after other code, when
  every spelling of the callee's own test folds back to the raw byte, is a flag passed in as a parameter
  (`fn_1_129D0` -> 100, flagged: the inline copy of `fn_1_D590`'s body is a guessed shape).
- **A scratch use of a function-scope variable in another switch case changes how later code splits it.**
  `rep_0610` `fn_1_16978`: writing case 4's `f40 * 0x13` term through the function's `i`
  (`i = f40[...] * 0x13; ...[3074 + i + f46]`) fixed case 4. It also gave `i` the earlier live-range piece
  that case 26's guard-zero reuse needed, so case 26 could call `fn_1_D7A4(0)` directly without the
  one-trip loop (-> 100).
- **A truly dead load in the target (its result overwritten on every path) means a volatile lvalue read in
  the original.** Established from GC/2.6 itself (`rep_0610` `fn_1_1496C`, [G8]):
  - the frontend drops unused non-volatile reads;
  - register allocation deletes dead definitions and cascades back through the address computation;
  - a post-allocation peephole deletes a load stored straight back to its own address.
  The only exemption is PCode flag 0x80, which is set only by volatile qualification: on the expression,
  the object, or the element type. So don't spend passes on dead-store, dead-branch, inline or loop tricks.
  A volatile read there is the faithful form, not a hack.
  - **Dead-load scanner:** `dl2.py` (scratch `g8_rep0610\`) finds loads whose result is overwritten on all
    paths. Outside the SDK there are only three in the game.
  - **A narrowing cast around an indexed volatile offset flips the base/offset register order**
    (`((volatile u8 *)arr)[(u16)(i * 0x48 + 0x46)]` gives the target's base r5 / offset r6), at the cost
    of a `clrlwi`. A no-op cast instead lets the frontend fold base and +0x46 into one constant.
- **For an indexed access, MWCC keeps `i * size + off` as "register plus constant" and computes the
  base first,** so the base gets the lower vreg number. A conversion around the offset makes it compute
  the offset first:
  - narrowing (`(u16)`) costs a `clrlwi`;
  - a same-width cast folds base + off into one constant;
  - widening a signed int to 64 bits leaves a dead `srawi`;
  - widening an UNSIGNED 32-bit value to `u64` costs nothing, because its high word is deleted.

  `((volatile u8 *)lbl_1_bss_6940)[(u64)(i * sizeof(DbgSel) + 0x46)];` gave `rep_0610` `fn_1_1496C`'s
  base r5 / offset r6 exactly (97.84 -> 100, the last function of the debug REL). The `u64` spelling is a
  guess at whatever produced that tree in the original; the volatile read itself is evidenced.
- **For a missing dead load, dump the PCode at initial-code first.** If the read is already gone there,
  the frontend dropped it, and no optimiser switch (dead code, dead assignments, lifetimes, -O3) brings it
  back (`rep_0610` `fn_1_1496C`).
- **MWCC's CSE reuses a register already holding a constant for later `li`s of that constant, but never a
  multi-def variable's main register;** a piece the live-range splitter cut off a variable can be reused.
  That is what "zero stores share i's register" means (`rep_0610` `fn_1_15760`), and likely also the
  guard-zero reuse in `fn_1_16978` and the `h` reuse in `fn_1_129D0`.
- **Inlined callee locals are numbered in reverse declaration order** (last declared = highest vreg),
  the opposite of a function's own locals. Frontend temps then follow in pass order: inline locals, block
  locals, strength-reduction temps, LICM copies, CSE temps.
- **The frontend hoists a global load out of an inlined loop only when the stored-through pointer
  parameter is bound to an address expression,** not to a local pointer copy. The hoisted value then
  becomes a low-index frontend temp, coloured late, instead of a backend LICM temp coloured early
  (`rep_7730` `fn_1_23B54` 97.53 -> 98.96).
- **A row offset written as `i * m` in the subscripts compiles like a `rowBase += m` local standalone,**
  but once inlined with a constant `m` the frontend hoists `i << 7` and strength-reduces it late.
- **To map our vregs onto the target's registers, align the pre-RA PCode dump with objdiff's target
  listing** (validate the alignment on our own listing first). Combined with the colouring simulator, that
  turns "which node must move" into a direct search (scratch `g5_rep7730\align.py`, `greedy.py`).
- **`#pragma opt_lifetimes off` turns off MWCC's live-range splitting.** That is what gave
  `w = (y / n) * w` a fresh register in every switch case but the first (`rep_0138` `fn_1_5924`). With
  it off (`#pragma push` / `opt_lifetimes off` / `pop` around one function), every case's product stays
  in `w`. Turning it off for the whole file broke six other functions. Block-scope locals per case stay
  separate variables even with splitting off.
- **`x << k` and `x * (1 << k)` compile to the same instruction but change the order terms are built in
  a sum,** and so the add operand order (`fn_1_5924`'s last add needed `col << k`).
- **The same body can be ordered differently once inlined:** the caller forward-substitutes reassigned
  parameters and evaluates the terms in another order. `fn_1_5924`'s case 0x10 matched standalone only
  with `col << 4`, and in its callers' inlined copies only with `col * 16`, so the callers write the
  index out instead of calling it (flagged).
- **The frontend range splitter keys on the first operand.** `w = (y / n) * w` in several switch cases
  splits `w` into one web per case, and only the first case's web keeps coalescing with the incoming
  r3. `w *= y / n`, `w = w * (y / n)` and `x %= 8` keep one web (`rep_0138` `fn_1_5924`).
- **The order MWCC hands out callee-saved registers (highest first), from micro TUs (`rep_0138`
  `fn_1_73B8`):** a hoisted global address (`&state`); then variables assigned from an inline
  function's result, parameter or local; then compiler loop temps (hidden pointers, entry pointers);
  then function-scope locals in declaration order; then block-scope locals; then parameters. Extra uses
  of a variable do not move it, but one more short-lived temp live across a parameter's range pushed that
  parameter to the top, so interference can override the order. `x = inlineFn(...)` lifts x above the
  loop temps but not above a hoisted global address.
  Variables assigned from static-inline getters are coloured in call order, just below a global-address
  temp and above the strength-reduction temps. A hoisted global address stays on top even through a
  local pointer, a getter inline, or stores through the global: copy propagation folds them back.
- **Read the declaration order off the target even when its top registers are wrong:** strip the
  mismatched top variables from both sides; the rest follows locals in declaration order, then parameters
  (`rep_0138` `fn_1_73B8`: every register below the top four landed with `set, table, cam1, cam2, i,
  end, sel, geo, key`).
- **MWCC never inlines a variadic function** (it emits `bl`), and `va_start` needs the enclosing
  function itself to take an ellipsis, so a loop containing `va_start` cannot move into an inline helper.
- **Then screen single changes in parallel on the exact reproducer.** For `rep_74A0` `fn_1_1D110`
  (99.86, one register inside an inlined callee) the screen found that `fn_1_1A290`'s guard needed one
  test through the `entry` local and one through the array: `if (entry->actor != NULL &&
  table->entries[i].applyControl != 0)`. Same instructions in the standalone function, but the inlined
  copy's colouring changed -> 100.
- **`#pragma scheduling off` shows MWCC's pre-scheduling order**, but it also changes register
  allocation: MWCC schedules before it allocates registers. Single-use locals and single-use parameter
  reassignments are forward-substituted, so source statement order often doesn't reach codegen order
  (`rep_0138` `fn_1_5924`).
- **Tooling: `objdiff-cli diff -1 <target.o> -2 <candidate.o> -o - --format json` scores an object
  compiled anywhere,** so variants can be compiled in parallel into scratch files without touching the
  build tree (about 0.25 s per variant for a 70 KB TU with 16 workers). Rank candidates by objdiff's own
  score; difflib and word-diff metrics mis-rank them.
- **Two same-typed counters whose registers come out wrong may be one variable.** `rep_0610`
  `fn_1_CDC8`'s switch result `k` was really `i` reused: about +10 points, but only together with the
  right statement order (found by a full 2 x 5040 objdiff sweep); alone it scored lower. The same sweep
  also exposed a real bug (`ids[0]`/`ids[1]` swapped). 89.2 -> 99.1.
- **Declaration-order sweeps usually fall into a few score groups;** a pairwise "declared before" test
  across the groups finds the deciding rule quickly (`rep_0610` `fn_1_135C0`: `anim` before
  `geoExtra`).
- **One function-scope counter shared by two loops seeds the second loop's offset as a copy**
  (`mr r6, r9`); two block-scoped counters give a fresh `li r6, 0` (`rep_0610` `fn_1_CDC8` -> 100).
- **Moving block-scope locals to function scope, and where they go in the list, changes callee-saved
  numbering.** Hoisting the loop-body pointers of `rep_0610` `fn_1_12820` to right after `u16 i`
  closed it (99.77 -> 100). Sweep each block local over the possible positions, and re-sweep the whole
  declaration order after any local is added or removed (`fn_1_135C0` +0.9 once `DbgHuge *h` existed).
- **`T *h; ... h = &global;` assigned before first use keeps `&global` in a callee-saved register;**
  `T *h = &global;` at the declaration did not (`rep_0610` `fn_1_135C0`, the target's extra `stmw`
  register; +1.1).
- **A constant index into a global array (`g.actors[0]`) is CSE'd into a callee-saved address** that
  later inlined uses share. Indexing with the one-trip-loop variable (`actors[j]`, `j == 0`) or
  addressing through a byte-offset cast (`(T *)((u8 *)h + 0xC04)` for `&h->slots[0]`) keeps it opaque,
  as the target has it (`rep_0610` `fn_1_135C0` 98.3 -> 99.8, `fn_1_D4BC` inlined into `fn_1_129D0`).
- **`if (f && ...)` and `if (f != 0.0f && ...)` swap the `fcmpu` operands** (the target's
  `fcmpu speed, zero` came from the truthiness form).
- **Check the effective address of every store mismatch.** objdiff showed `rep_0610` `fn_1_135C0`'s
  wrong store target (`&60EC[0x5C]` instead of `60EC + 0`) only as an argument mismatch, because the
  displacement was off a different base register (0x307C off the .bss base vs 0x5C off the pointer).
- **A store whose address sits in the next free argument register and stays live into the following
  `bl` is a missing trailing argument.** `rep_0610` `fn_1_F2F8` (83 -> 100) and `fn_1_F040` (96 -> 100)
  write a texture into word 0 of a parameter table and then call `fn_800324EC` / `fn_8002955C`; the
  table is the callee's last argument (prologues `mr r31, r6` / `mr r6, r5`). Earlier passes had ground
  on it as "argument registers allocated before the store address". Read the callee's prologue before
  grinding register order.
- **The interleaving of a callee's int and float parameters is invisible in its own registers but not
  in an inlining caller.** Ints and floats get argument registers independently, so
  `f(void *, s32, s32 n, f32 a, ...)` and `f(void *, s32, f32 a, ..., s32 n)` compile the callee
  identically. But MWCC generates the argument expressions in source order, which sets the
  virtual-register numbering and so the colouring once the call is inlined into a busier caller.
  `rep_7BF0` `fn_1_29A9C` (inlines `fn_1_2935C`, which calls `fn_80037768`) went 92.01 -> 100 only by
  moving `simNum` after the floats, after 19+ caller-side hypotheses had failed. 34 of the 35
  interleavings match, so the exact original order is not recoverable from the bytes. When an inlined
  call has the right instructions but permuted volatile registers, sweep the parameter interleaving.
