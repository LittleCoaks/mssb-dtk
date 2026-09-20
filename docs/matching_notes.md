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

## The int-to-float conversion bias constant is a permanent scoring floor, not a lead

First seen: `game/game/fielding/fielder_ai` (2026-09). This sharpens the existing
"Shared .sdata2 literal pool across split DOL text-engine units" entry into a general
rule.

Two different kinds of `.rodata` float reference behave oppositely, and it is worth
recognising which one is capping a function before spending attempts on it:
- A plain **value** constant CAN be matched. Declare `extern const f32 lbl_N_rodata_XXXX;`
  and use the symbol in place of the literal — codegen is byte-identical and only the
  relocation name changes. Never use the definition form, which emits a spurious
  duplicate symbol.
- The **int-to-float/double conversion bias** (the 0x4330 magic) CANNOT. Referencing it
  explicitly forces a different `fsub`/`frsp` codegen path. MWCC pools it as an anonymous
  `@NNN` where the target has a dtk-named `lbl_N_rodata_XXXX`, and no source form changes
  that.

So a function whose ONLY residual is a handful of instructions naming a conversion
constant is DONE — it is an artifact of the split, not a source-shape problem. In
`fielder_ai` this capped `fn_3_A1DA0` at 99.85% over 3 instructions, and contributed the
last fractions on `fn_3_A6ABC`, `fn_3_A384C`, `fielderAIMakePlay` and
`fieldingAIThrowOrChase`. Recognise it, record it, and spend the effort elsewhere.

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
| fn_3_1E724 (208 B) | batterAIControlled (444 B) - bunt decision |
| fn_3_1F1CC (388 B) | batterAIMoveBatter (1012 B) - pre-pitch box positioning |
| fn_3_1F350 (296 B) | batterTrackBallInBox (1312 B) - stage 1 |
| fn_3_20188 (156 B) | batterAIRNGValueSetting - pitch guess |

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
- `batterTrackBallInBox` calling `fn_3_1F350()`, and `batterAIMoveBatter` calling `fn_3_1F1CC()`:
  plain call form, auto-inlined by MWCC, EXACT size, **100%** each. No body copy needed.
- `batterAIControlled` calling `fn_3_1E724()`: call form **96.58% and 8 bytes SHORT**; the same body
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
