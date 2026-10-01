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
   Codegen is unaffected (see previous section — order is a codegen no-op),
   so the match stays 100%. This applies to every REL unit (menus/game/
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
  **100%** with plain array access on `unused_forceOutSomething`.
- **Repeated access to ONE element at a VARIABLE index** -> explicit pointer local
  `InMemRunnerType* runner = &g_Runners[i];` (the existing entries).
- **A loop over elements where the target bumps a base by the struct stride
  inside the loop** -> walking pointer `for (i=0; i<4; i++, runner++)`. This
  reached 100% on `fn_3_89028`, and separately made MWCC unroll a copy loop the
  same way the target does (69.4% -> 83.0% on
  `transferInMemRunnerValuesToNextRunnerIndex`).

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
every statement is correct. On `running_LiveBall_Human` the first draft scored
**7.9%**; making the other arm the outer `if`, with no other change, scored
**95.55%**. If a big from-scratch function scores in the single digits, try the
inversion before rewriting the body. Cross-reference "An exact size match plus a
low score means block ORDERING, not missing logic" above — this is the cheapest
instance of that class.

Related, smaller levers measured in the same file: `else if` chains versus nested
`if`s (81.37% nested, 97.20% plain `else if`, 99.07% `else if` with explicit
`(x & FLAG) == 0` guards on the last branches, all on `running_DirectionOverrides`),
and `<= 1` versus `< 2` (the target's `cmplwi 1; bgt` versus our `cmplwi 2; bge`).

It applies to small functions too, and to the early-return polarity specifically:
`fn_3_F6504` (196 B, `game/game/stadium/sta_c5`) went 95.10% -> 100% purely by
rewriting `if (!cond) return NULL; build;` as `if (cond) { build; } else { return NULL; }`.

## When the target inlines an in-file function it also keeps standalone, copy the body

First seen: `game/game/baserunning/runner`, `running_MainFunction` and
`cCSRunningFun` (2026-09). Compare "Contradictory declaration-order requirements
between an auto-inlined static and its standalone `*_unused` copy" above — same
underlying situation, different remedy.

A dispatcher hub whose target inlines several smaller in-file functions cannot be
matched by CALLING them: MWCC declines to inline a function that is also a real
standalone symbol, so the call survives and every register assignment shifts.
Measured on `running_MainFunction`: calling `fn_3_8A7B4()`/`fn_3_8A618()` gave
**75.3%**, copying their bodies in gave **94.2%**. A `static inline` clone is the
cleaner form of the same fix where the body is small enough to share.

OPEN QUESTION from the same file, recorded so it is not re-derived: the reverse
also happens. MWCC inlined two fully-implemented small callees
(`running_chainChompSprintRelated`, `running_ForceOutStateRelated`) into
`maybeUpdateRunnerNoRun` where the target keeps real `bl` calls, forcing that
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
`frames *= 1.3f; frames += 0x1e;` (maybeUnused_SetThrowSpeedType2 93.78% -> 100%; 28 sites, none
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
  later closed with `extern const f32 lbl_803CCFFC` (see the SetFog entry below).

## Findings from the SetFog trio (File_0x800b9974 / 99c4 / 9a30)

First seen: `Unknown/File_0x800b9974.c`, `File_0x800b99c4.c`, `File_0x800b9a30.c` (2026-09),
all three 100% and `Matching`.

- **A shared `.sdata2` value constant can be claimed by name instead of by merging.**
  `lbl_803CCFFC` (0.0f) is read by SetFogNone, SetFogNoneAgain and five later functions up to
  `Custom_SetState`/`DODefaultUserTevMode`; the pool `0x803CCFF8..0x803CD0E0` starts with a
  constant of `Custom_SetState` (0x800BA848 split), so a merged unit covering only the SetFog
  splits could never own the range. `extern const f32 lbl_803CCFFC;` used at every 0.0f site gave
  the same single `lfs` + `fmr` copies (the constant is loaded once either way here), 100% in
  objdiff, and the `Matching` link resolves the name against dtk's asm split (`4 files OK`). Check
  that the target loads the constant ONCE before doing this (see "`extern const f32
  lbl_N_rodata_XXXX` only works for a SINGLE-USE constant").
- **`frsp` of an `f32` parameter at a call site, while the stores use the unrounded register,
  means an explicit `(f64)` widening in the call.** `SetFog` stores its four `f32` params into a
  global with `stfs fN` and passes `frsp` copies to `GXSetFog` (so it first `fmr`s every param to
  a scratch register). `f64` params, `(f32)` casts, re-reading the stored fields and
  assignment-expression arguments all CSE the rounding into one `frsp` (74%). `f32` params with
  `GXSetFog(type, (f64)startZ, ...)` matched 100% (an inline wrapper with `f64` params also does).
  An `mw_version` / `-O` sweep changed nothing.
- **A dtk symbol can collide with an SDK typedef.** The Ghidra import named the 0x18-byte fog-state
  global at 0x80111700 `GXFogType`, which cannot be referenced from C while `GXEnum.h` is visible.
  Renamed to `fogSettings` (struct `FogSettings` in `include/Unknown/File_0x800b99c4.h`).

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
  keeps `lbz g_d_GameSettings._06` after three stores into `aiPosSwapInputs` (dtk size 0x24C98).
  With the full-size struct every source shape (pointer locals, inline helper, switch, ternary,
  volatile load, unsized array, `-proc`, `mw_version` sweep) hoisted the load (68%); a struct of
  any size up to 0xFFFE gave 100%, 0xFFFF and up did not. `UnknownHomes_Static.h` now lets a unit
  `#define AIPOSSWAPINPUTS_LOCAL_VIEW` and declare a smaller file-local view. Suspect this whenever
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
  copies.** `RandomInt_Game` and `random_fn_3_9EE24` match with `int orig = max; if (max < 0) max = -max;`,
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
