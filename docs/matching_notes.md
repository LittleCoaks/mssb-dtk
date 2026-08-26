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
   challenge use cflags_rel); DOL-side units don't use `-inline deferred`.

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
