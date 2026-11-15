# stadium_bowser_castle.c — match grind checkpoint

Unit: `game/game/stadium/stadium_bowser_castle`
Module: game (REL)
Baseline at session start: 0.61% .text, 49 functions, 0 at 100%.
All functions started as bare `return;` stubs — phase 1 is writing initial
implementations, not register grinding.

Reference siblings (read these before writing anything):
- `src/game/stadium/stadium_wario_palace.c` (94.98%) — prologue/include set to copy
- `src/game/stadium/stadium_framework.c` (99.40%) — shared framework

## Data sections

| section  | match % (target-relative) | target size | ours size |
|----------|---------------------------|--------------|-----------|
| .text    | 18.34%                    | 31256        | (end of this session, post Step 2/3) |
| .rodata  | 61.76%                    | 544          | — |
| .bss     | 89.76%                    | 416          | — |
| .data    | (no such section in this unit) | — | — |
| .sdata   | (no such section in this unit) | — | — |
| .sdata2  | (no such section in this unit) | — | — |
| .sbss    | (no such section in this unit) | — | — |

Reconciled via `objdiff-cli diff -p . -u game/game/stadium/stadium_bowser_castle
-o - --format json` at the start of this session (Step 1), against the clean
working tree at commit 94559e1. Numbers above supersede the prior session's
9.47/60.80/64.39% figures, which predate the (previously unlogged) batch-4
functions below.

Note (prior session): `.bss` match % had dropped from 36.36% to 15.61% with
no individual symbol regressing. This session (implementing the six
functions below) it recovered to 64.39% simply by adding the bss symbols
those functions actually reference (`lbl_3_bss_9D88`, `_9D90`, `_9D94`,
`_9E50`) — confirming the earlier drop was purely a layout/ordering
artifact of an incomplete symbol set, not a real regression. Expect further
movement (up or down) as more of the file's ~40 remaining stub functions
are implemented and introduce their own bss symbols.

## Status

From report.json, updated after every function (2026-09-22 session).

| function                           | status    | pct |
|------------------------------------|-----------|-----|
| loadBowserCastle                   | pending   | 90.8197% |
| fn_3_C82B4                         | pending   | 95.2987% |
| fn_3_C823C                         | matched   | 100.0% |
| fn_3_C805C                         | exhausted | 99.125% |
| thwomp_slamControl                 | pending   | 97.2772% |
| fn_3_C77AC                         | pending   | 91.3487% |
| thwomp_smokeRelated                | matched   | 100.0% |
| thwomp_bounceOffSoundAndVisualFx   | exhausted | 99.5775% |
| fn_3_C7444                         | matched   | 100.0% |
| stadiumObjRelated_Castle           | pending   | 98.8608% |
| flameControl                       | pending   | 99.7821% |
| fn_3_C625C                         | matched   | 100.0% |
| bowserCastleRelated                | pending   | 98.0486% |
| castleFireballMaybe                | exhausted | 91.5556% |
| fn_3_C597C                         | pending   | 99.2396% |
| fn_3_C56E8                         | pending   | 99.9879% |
| fn_3_C54D0                         | matched   | 100.0% |
| fn_3_C5304                         | matched   | 100.0% |
| fn_3_C4F00                         | matched   | 100.0% |
| fn_3_C4CF4                         | matched   | 100.0% |
| fn_3_C4B80                         | matched   | 100.0% |
| fn_3_C48D0                         | matched   | 100.0% |
| fn_3_C4724                         | matched   | 100.0% |
| fn_3_C444C                         | matched   | 100.0% |
| stadiumObjCollision_Castle         | exhausted | 99.0094% |
| bowserCastleStarPadsContaactFn     | exhausted | 98.7209% |
| fn_3_C40EC                         | matched   | 100.0% |
| fn_3_C4068                         | matched   | 100.0% |
| fn_3_C3F70                         | exhausted | 99.3548% |
| fn_3_C3E94                         | matched   | 100.0% |
| fn_3_C3C2C                         | exhausted | 97.2013% |
| thwomp_screenShake                 | matched   | 100.0% |
| bowserCastleSomething              | matched   | 100.0% |
| fn_3_C366C                         | matched   | 100.0% |
| fn_3_C30F0                         | matched   | 100.0% |
| fn_3_C2EDC                         | matched   | 100.0% |
| fn_3_C2C80                         | matched   | 100.0% |
| fn_3_C2AA0                         | pending   | 93.6333% |
| fn_3_C298C                         | matched   | 100.0% |
| fn_3_C2974                         | matched   | 100.0% |
| fn_3_C2644                         | pending   | 99.598% |
| fn_3_C24A0                         | matched   | 100.0% |
| fn_3_C23E0                         | matched   | 100.0% |
| fn_3_C2310                         | matched   | 100.0% |
| fn_3_C2244                         | matched   | 100.0% |
| fn_3_C1C18                         | pending   | 93.719% |
| fn_3_C19C8                         | pending   | 99.6824% |
| fn_3_C1974                         | matched   | 100.0% |
| fn_3_C1964                         | matched   | 100.0% |

29/49 at 100%.

## Hypothesis log

fn_3_C23E0 (matched, this session)
  baseline: 2.08% (stub)
  [1] initial impl from target asm: `fn_800BF058(fn_3_B8184)` once before the loop,
      then per-iteration `fn_3_B828C((s32)&stadiumObjectCollision.objects[i])`,
      guarded shadow/model/drawFlags update for `i` in [1,0xB), `obj` declared
      *inside* the loop body -> 98.75% (register-only: i/obj got r29/r28, target
      wants r28/r29)
  [2] hoist `StadiumObject* obj;` declaration to the top of the function
      (assigned inside the loop, not re-declared per iteration) -> **100.0%**
      (kept; declaration-order swap alone flipped the register allocation to
      match target exactly, no logic change)
  Required fixing `fn_800BF058`'s prototype (was `void(void)`, an unmatched
  DOL stub) to `void fn_800BF058(void (*func)(StadiumModel*, Mtx))` in
  `include/Unknown/File_0x800bf038.h` / `src/Unknown/File_0x800bf038.c`
  (body stays a stub); that header now includes `stadium_framework.h` for
  `StadiumModel`.

fn_3_C2310 (matched, this session)
  baseline: 1.92% (stub)
  [1] initial impl: literally `fn_3_B8184`'s body (framework.c) minus its
      early-return guard, using a new file-local `lbl_3_bss_9D94` in place of
      `lbl_3_B827C`'s `lbl_3_bss_190C`; declared `Mtx local; Mtx world;` (in
      that order, copying my own reading order rather than the sibling's) ->
      99.88% (register-only: local/world stack slots swapped, 0x8 vs 0x38)
  [2] swap the declaration order to `Mtx world; Mtx local;` (matching
      `fn_3_B8184`'s actual declaration order in stadium_framework.c exactly)
      -> **100.0%** (kept)

fn_3_C3E94 (this session)
  baseline: 1.82% (stub)
  Modeled directly on `stadium_wario_palace.c`'s `fn_3_CEBBC(Vec* p, int idx)`
  (near-identical shape: `fn_800528C0` screen-projection call, then writes
  the result into a `graphicsRelatedArray[...]`-indexed object's `pos`). New
  types `CastleGfxObject` (pos Vec at 0x48, modeled on `PalaceGfxObject`) and
  `CastleGfxScene` (firstHandle u16 at 0x14, modeled on `PalaceGfxScene`).
  [1] single-shot implementation copying `fn_3_CEBBC`'s structure verbatim
      with the new castle types -> 99.64% (kept; not revisited further)
  remaining: only the two `lfd`/`lfs` float-constant relocations (the
  int-to-float bias magic-double pair MWCC emits for `s16 -> f32` conversion,
  plus the `0.0f` literal for `pos.z`) resolve to our anonymous literal pool
  (`@430`/`@432`) instead of target's named `lbl_3_rodata_20C0`/`_213C`. Same
  literal-pool-ordering class already documented on `fn_3_C823C`/`fn_3_C366C`;
  not chaseable from within this one function.

fn_3_C3F70 (this session)
  baseline: 1.61% (stub)
  Walks a per-material-group animation-state list off `obj->model->root`,
  reusing the `lbl_3_bss_9D88++ > 4` / `lbl_3_data_177F0` frame-counter idiom
  already proven in `fn_3_C4068`. New types: `CastleMaterialRoot`
  (groupCount u16 @0x6, groups pointer-array @0x18), `CastleMaterialEntry`
  (kind u8 @0, animState u32 @4, stride 0x10), `CastleMaterialList`
  (entries pointer @4, count u16 @8), `CastleMaterialListHolder` (list
  pointer @0x10), `CastleMaterialGroupNode` (holder pointer @0x14).
  `lbl_3_data_177F0` turned out to be `extern` (defined in another game-REL
  file, `shndx=0`/undefined in our object per ELF symtab dump), not this
  file's own static, despite the naming convention suggesting otherwise —
  confirmed by inspecting the built target `.o`'s symtab directly.
  [1] initial impl: cached `CastleMaterialList* list = holder->list;` local
      reused for both the inner-loop count check and the entries pointer,
      `j++` before `entry++` in the for-loop increment expr, `int i`/`int j`
      -> 94.24% (register-only + one real instruction-order swap)
  [2] drop the `list` local; read `holder->list->count` / `holder->list->entries`
      directly (target re-loads `holder->list` fresh at the loop-check each
      iteration rather than caching it) -> 97.15% (kept; standing-prior
      "extra one-use temp" pattern confirmed again)
  [3] swap the for-loop increment order to `entry = ..., j++` (matching
      target's `addi entry,entry,0x10` before `addi count,count,1`) -> 99.35%
      (kept)
  [4] change `int i` / `int j` loop counters to `u32 i` / `u32 j` (both
      compared against `u16` struct fields; target uses `cmplw`/unsigned
      compares) -> 99.35% (no further change from [3]'s number, but fixed
      the `cmpw`->`cmplw` mismatch cleanly, kept as the more correct match
      of target's instruction *kind*, not just count)
  remaining: pure register swap between the outer-loop counter `i` and the
  `holder` pointer (target r9/r8, ours r8/r9). Tried collapsing the
  intermediate `group` local into `root->groups[i]->holder` directly (no
  effect, kept for the simpler read) and reordering `u32 i` after `root` in
  a couple of arrangements (no effect). Not chased further within the
  ~6-cycle budget; register-only.

fn_3_C2244 (this session)
  baseline: 1.96% (stub)
  Reads `currentDrawingItem`'s scratch byte at +0x2A (no named field exists
  for it in `DrawingSceneStruct`'s documented scratch region; accessed via
  `*((u8*)item + 0x2A)`, matching the header's own guidance that "+0x14.. is
  scratch the node's func owns"). New type `CastleCameraSlot` (8 bytes pad,
  `Mtx mtx` @8, `DrawingSceneStruct* item` @0x38, size 0x3C) for the 2-entry
  `lbl_3_data_17804` array (indexed by `drawStadiumRelated`), matching
  `fn_80052768_getCamera(0)->view` copied into it via `PSMTXCopy`.
  [1] single-shot implementation from the target asm -> 61.35% (all
      structural instructions present and correctly formed — every diff
      entry is `DIFF_ARG_MISMATCH`/`DIFF_REPLACE`/one `DIFF_DELETE`, no
      missing/extra logic)
  remaining: target keeps `lbl_3_bss_9D9C` and `lbl_3_bss_9D90` addressed via
  two *separate* `lis ...@ha` pairs; our build merges them (plus other
  nearby bss vars) under one synthesized anonymous base register (`lis
  r4,...bss.0@ha; addi r30,r4,...bss.0@l`) accessed via offsets 0xd4/0xe0,
  because our file currently only declares ~10 of this file's ~416 bytes of
  target `.bss` (the rest belong to the ~40 still-unimplemented functions in
  this file). This is the same class of issue already flagged in the "Data
  sections" note above (`.bss` match% moved from 15.61% -> 64.39% this
  session purely from declaring the bss vars these six functions touch) —
  expected to resolve on its own as more of the file's bss variables get
  declared by future batches. Not chaseable from within this one function.

castleFireballMaybe (this session)
  baseline: 1.59% (stub)
  New type `CastleFireballTarget` (a Vec `anchorPos` at file offset 0x9C on
  the incoming `StadiumObject*` — this is NOT the already-declared
  `StadiumObject.pos` field at 0xA0; the two are 4 bytes apart and this
  function definitely reads from 0x9C per the target asm, so `pos` at 0xA0
  was left untouched to avoid regressing `stadium_wario_palace.c`'s many
  already-good `->pos` users. What real field(s) occupy 0x94-0x9F on
  `StadiumObject` is still unresolved — flagged for whoever next touches
  that struct).
  `getAnimationCollisionOffset`'s prototype was fixed from `void(void)` to
  `void getAnimationCollisionOffset(int fielderIndex, int bodyPart, Vec* out)`
  in `include/Unknown/File_0x8001b728.h` / `.c` (body stays a stub); the
  `bodyPart` argument is passed as a bare `4` (task hint said "TORSO" but no
  such enum exists anywhere in `include/`, confirmed by grep — left as a
  literal, listed in the report).
  [1] initial impl: `g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL &&
      g_GameLogic.playOver` early-return guard, `int i` loop counter,
      `(Vec*)((u8*)obj + 0x9C)` raw cast for the second `PSVECSubtract`
      operand -> 90.13%
  [2] `int i` -> `u32 i` (loop counter compared against literal `9`; target
      uses `cmplwi`/unsigned) -> 91.00% (kept)
  [3] replaced the raw `(Vec*)((u8*)obj + 0x9C)` cast with a named field via
      the new `CastleFireballTarget` type (`&((CastleFireballTarget*)obj)->anchorPos`)
      -> 91.00% (no change in %, kept anyway for readability per the
      raw-offset-cast guidance)
  remaining: target keeps `obj` itself resident across the whole function
  (`mr r30, r3` once, then `addi r4, r30, 0x9c` recomputed fresh inside the
  loop each iteration); our compiler treats `&obj->anchorPos` as
  loop-invariant and hoists the address computation into its own register
  (`r31`) once before the loop, dropping the `mr r30,r3` entirely. This is a
  pure LICM/register-allocation difference — the computed address is a
  provably-pure pointer add on an unmodified parameter either way, so no
  surface rewrite of the expression changed it (tried the raw-cast form and
  the named-field form, both hoist identically). Also unresolved: the
  `lbl_3_rodata_2080` (zero-`Vec` initializer for `off`) and
  `lbl_3_rodata_2178` (`2.6f` threshold) relocations resolve to our
  anonymous literal pool (`@319`/`@400`), same literal-pool-ordering class
  as elsewhere in this file. Not chased further within the ~6-cycle budget.

fn_3_C823C
  baseline: 4.67% (stub)
  [1] initial impl: cached `obj` local for CTRLBuildMatrix + hazardType==5 check, fresh `stadiumObjectCollision.objects[offset].triangles` for return  -> 99.67% (kept)
  [2] drop `obj` local, re-index objects[offset] at all 3 uses  -> 72.87% (reverted)
  [3] `*(volatile const f32*)&lbl_3_rodata_21F0` to force named load  -> rejected as unnatural hack (reverted)
  [4] (this session) delete named `static const f32 lbl_3_rodata_21F0` global, write `m[1][3] = 0.002f;` inline literal, keep `obj` local -> 99.67% (kept, same as [1])
  [5] (this session) framework-style rewrite with no `obj` local, re-indexing `stadiumObjectCollision.objects[offset]` at all 3 uses (matching stadium_framework.c's fn_3_C7444-adjacent idiom around line 560) -> 72.87% (reverted, matches earlier [2] finding)
  [6] resolved to 100% (rodata literal ordering settled once file state stabilized); current source is the obj-local form with inline 0.002f — CORRECTION after reading current source: this did NOT reach 100% this session. Current source (verified) is still the [1]/[4] form (`obj` local, `CTRLBuildMatrix((Control*)obj, m)`, `if (((CastleHazardObj*)obj)->hazardType == 5) { m[1][3] = 0.002f; }`, fresh `stadiumObjectCollision.objects[offset].triangles` on return) and measures 99.67%, unchanged from [1]/[4]. The remaining gap is still only the named-vs-anonymous rodata pool entry for the 0.002f literal (see [1] remaining note below); it was not rechecked further this session since fn_3_C366C was the assigned target.
  remaining: only reloc name/offset differs: target uses a named rodata symbol for 0.002f, ours is an anonymous pool entry. This is a constant-pool ordering issue, expected to resolve as more of the file's float literals are added; not chased further this session.

fn_3_C4068
  baseline: 3.03% (stub)
  [1] initial impl with `BOOL wrapped = counter > 4;` temp  -> 76.21%
  [2] remove temp, inline `if (counter > 4)` (target keeps compare in CR0)  -> 85.61%
  [3] declare/load `counter` before root/mat (stops addi+lwz fusing into lwzu)  -> 98.94% (kept, prior session)
  [4] split model/root into separate locals  -> 85.61% (reverted)
  [5] (this session) delete the `counter` local entirely, fold into `if (lbl_3_bss_9D84++ > 4)` (post-increment in the condition) -> **100.0% (kept)**
  Root cause confirmed: the leftover `counter` temp was the only thing forcing r3/r5 to differ from target; removing it (variant [5], the "post-increment in condition" hypothesis from the standing prior) fully resolved the register swap. Variant (ii)/(iii) from the task list were not needed since (i) already reached 100%.

fn_3_C7444 (matched)
  plain if/else on hasBounced -> 92.27% (target's two arms both branch out); `switch (hasBounced) { case 0: ...; default: ... }` -> 100% (kept; no goto).

fn_3_C40EC (matched)
  `== 6` with bodies ordered as Ghidra -> 99.71%; flipped to `!= 6` with bodies swapped -> 100%.

fn_3_C1974 (matched)
  needed new bss syms lbl_3_bss_9D98 / lbl_3_bss_9D9C; r4/r5 swap fixed by storing pointer before clearing flag.

fn_3_C366C (this session)
  baseline: 0.47% (stub); `bowserCastleSomething` was 85.71% due to this stub being auto-inlined away (empty body eliminated).
  Ghidra HTTP endpoint was unreachable this session (curl exit 7 / connection refused), so this was implemented purely from the objdiff target instruction stream plus a structural match against `stadium_wario_palace.c`'s `palaceHazeTextureMaybe`/`warioPalaceSomething` (near-identical particle-init idiom: emitter struct with `particles`/`_10`/`origin`/`kind`, looped `PalaceHazeParticle`-shaped struct with velX/velZ/scale/alpha/etc, `allocParticleEffect(cb, 0x80, 0, 0x15, 1, 0)` call site). Float/double rodata constant *values* (not names) were read directly from the built target `.o`'s `.rodata` bytes via a small Python ELF parser (symtab + section offsets), since these are real per-file data (a `Vec[6]` position table and scalar constants), not just literal-pool noise.
  New types added: `CastleFlameParticle` (particle list node, modeled on `PalaceHazeParticle` but with different field values at 0x38/0x3C/0x40-0x43/0x4D, and no `index` field write), `CastleFlameEmitter` (modeled on `PalaceHazeEmitter`).
  New file-local data: `lbl_3_bss_9F0C[5]` (u32 array, only element 0 used), `lbl_3_rodata_2028[3]` (u8 array {0xA0,0x46,0x00}), `lbl_3_rodata_202C[6]` (`const Vec[6]`, the six flame-emitter origin positions), `const_pi_or_180` (0.017453292f, same name/value as `stadium_wario_palace.c`'s file-local constant for the same purpose).
  [1] direct/literal first draft (0xA0/0x46/0x00 as inline literals in the loop, `255.0f` used directly twice instead of through a local, `(u32)(rand()%360)` cast on the angle) -> 72.68% (bowserCastleSomething back to 100% immediately, confirming the auto-inline theory)
  [2] tried `(f32)((f64)((u32)(rand()%360)))` triple-cast on the angle, hoping to force the target's `xoris` unsigned-conversion instruction -> 72.04% (worse, reverted to [1]'s cast form)
  [3] moved `p->_40/_41/_42` from inline literals to reads of a new named `lbl_3_rodata_2028[3]` array (matching the `lbzu`/`lbz` loads target does from a real rodata byte array rather than materializing `li` each iteration) -> 76.95% (kept; this fixed a 3-GPR deficit vs target's saved-register set, confirmed by the prologue `stmw` range now matching r21-r31)
  [4] moved the twice-repeated literal `255.0f` (`p->alpha`/`p->alphaByte`) into a `f32 alpha = 255.0f;` local hoisted above the loop, matching `palaceHazeTextureMaybe`'s `alpha` local -> 88.33% (kept; this was the standing-prior "one-use temp" pattern in reverse — the *removal* of implicit constant-folding by introducing a genuine variable was what let the compiler emit the target's real `fctiwz` float-to-int conversion for `alphaByte` instead of constant-folding `(u8)255.0f` away)
  [5] tried `(u32)rand() % 360` (cast before modulo, matching the `%2500` block's style) instead of `(u32)(rand() % 360)` (cast after) for the angle -> 86.77% (worse, reverted)
  [6] on the `p->_20` (`%101`) block, removed the `(u32)` cast entirely: `(f64)(rand() % 101) / 100.0` matching `stadium_wario_palace.c`'s exact wording (no cast) -> 95.58% (kept; this restored the target's `xoris` unsigned-double-conversion instruction that no `(u32)` cast variant had produced)
  [7] applied the same fix to the angle block: `(f32)(rand() % 360)` with no `(u32)` cast at all -> 98.49% (kept; restored the second `xoris` and closed the FPR-count gap to exactly match target's callee-saved f20-f31 range)
  [8] reordered local declarations (`s16 i` declared before `CastleFlameParticle* p`, matching target's apparent variable-numbering order) -> 99.33% (kept; fixed the last pure register-swap, particle pointer now r22/counter r23 matching target exactly)
  final/kept state: 99.33%. Full instruction-level diff at this state shows every mnemonic, register, and immediate matching target exactly; the ONLY remaining differences are relocation target names on ~20 `lis`/`addi`/`lfd` instructions where target references named symbols (`lbl_3_rodata_2100`, `lbl_3_rodata_2128`, `lbl_3_rodata_20FC`, `lbl_3_rodata_20D4`, `lbl_3_rodata_20C0`, `lbl_3_rodata_2108`, `lbl_3_rodata_20E8`, `lbl_3_rodata_2110`, `lbl_3_rodata_2118`, `lbl_3_rodata_2120`) but ours resolves to anonymous local literal-pool entries (`@372`..`@383`). This is the exact same class of residual already documented on `fn_3_C823C` (constant-pool/literal-ordering — the compiler's float-literal pool numbering depends on the full set/order of float literals across the whole translation unit, not just this function) and is not chaseable from within a single function; expected to improve as more of the file's other functions (which likely reference the same shared constants, e.g. `0.5f`, `2.0`, `100.0`) get implemented.
  Also checked per the task: `fn_3_C30F0` (first arg to `allocParticleEffect`, still a `void fn_3_C30F0(void) { return; }` stub) — no evidence found this session that its prototype is wrong; `bowserCastleSomething` already matches 100% with the current `void fn_3_C30F0(void)` declaration and the existing implicit function-pointer-to-`void*` cast at the call site, so its signature was left untouched (Ghidra unreachable this session to cross-check its real parameter list).

bowserCastleSomething
  verified 100% once fn_3_C366C stopped being an empty stub (see fn_3_C366C entry above): body unchanged from its 100% version. Under module-default `-inline auto`, the empty stub `fn_3_C366C` is defined earlier in the TU and gets auto-inlined, which deletes the call. Fix = implement `fn_3_C366C`. Confirmed resolved this session; no source changes were needed to `bowserCastleSomething` itself.

fn_3_C2244 (follow-up session)
  baseline this session: 61.35% (`static CastleCameraSlot lbl_3_data_17804[2]`, own-.bss declaration bug)
  [1] change `lbl_3_data_17804` declaration from `static CastleCameraSlot
      lbl_3_data_17804[2];` to `extern CastleCameraSlot
      lbl_3_data_17804[2];` (symbols.txt documents it as
      `.data:0x00017804 size:0x78 scope:(global)`, i.e. it is a real
      target `.data` object, not this file's own `.bss` allocation) ->
      98.73% (kept; correctness fix regardless of score per task, and .text
      section % also improved 9.22% -> 9.46%)
  [2] `lbl_3_bss_9D9C` type `u32` -> `s32` (target's early-return guard
      compare on it used signed `cmpwi`, ours emitted unsigned `cmplwi`)
      -> 99.9% (kept; fixed the `cmpwi`/`cmplwi` opcode mismatch)
  [3] flip the early-return guard from `if (lbl_3_bss_9D9C == 0)` to
      `if (lbl_3_bss_9D9C != 0)` (target's `beq`/`bne` branch polarity and
      destination address showed the removeCurrentDrawingItem block is
      actually taken when the flag is *nonzero*, not zero as the original
      one-shot guess had it) -> **100.0% (kept)**
  Net: 61.35% -> 100.0% this session, all three changes kept.

fn_3_C3F70 (follow-up session, readability pass)
  baseline this session: 99.35%
  [1] `entry = (CastleMaterialEntry*)((u8*)entry + 0x10)` -> `entry++`
      (`CastleMaterialEntry` is exactly 0x10 bytes) -> 99.35% (no change,
      kept for readability)
  [2] hoist `u32 j;` to function scope (next to `i`) instead of declaring
      it inside the `if (holder != NULL)` block -> 99.03% (reverted;
      restored the inner-scope declaration)
  [3] remove the `holder` local, re-index `root->groups[i]->holder`
      directly at all 3 uses -> 94.1% (reverted; restored the `holder`
      local)
  final/kept state: 99.35% (only the `entry++` readability change kept;
  the register-only i/holder residual is unchanged and was not further
  chased this session).

castleFireballMaybe (follow-up session)
  baseline this session: 91.00%
  [a] factor the per-fielder test into `static BOOL
      castleFireballInRange(StadiumObject* obj, int i)` (memset +
      getAnimationCollisionOffset + PSVECSubtract + PSVECMag + compare,
      called from the loop) -> 63.87% (reverted; MWCC did NOT inline it
      under this module's `-inline auto` — the helper showed up as its own
      symbol in our object, which also violates the "no extra function
      symbol" requirement, not just a score regression)
  [b] same shape but helper returns only `f32
      castleFireballDist(StadiumObject*, int)` (distance only, compare
      stays in the caller) -> 63.87% (reverted; same non-inlining problem,
      helper again appears as its own symbol)
  [c] compute the address inside the call expression,
      `PSVECSubtract(&off, (Vec*)((u8*)obj + 0x9c), &diff)` instead of the
      named-field cast -> 91.00% (no change from baseline; reverted to the
      named-field `&((CastleFireballTarget*)obj)->anchorPos` form for
      readability, since it scores identically)
  Also confirmed via the target instruction stream: the target genuinely
  has `bl memset` inside the loop (instr 33 in the objdiff dump, right
  after `li r5, 0xc`) — the `memset(&off, 0, sizeof(Vec))` call already in
  our source is correct and was kept unchanged.
  final/kept state: 91.00%, unchanged this session. The `obj`
  residency/hoist mismatch (target keeps `mr r30,r3` once and recomputes
  `addi r4,r30,0x9c` fresh each loop iteration; our compiler hoists
  `&obj->anchorPos` into its own register once before the loop) was not
  resolved by any of (a)/(b)/(c) — none of the standing-prior inlining
  hypotheses applied here because MWCC declined to inline any shape of the
  extracted helper. Not chased further within the task's cycle budget.

fn_3_C298C: batch-4 implementation (interrupted, unlogged) -> 100.0%

thwomp_bounceOffSoundAndVisualFx: batch-4 implementation (interrupted, unlogged) -> 98.73%

bowserCastleStarPadsContaactFn: batch-4 implementation (interrupted, unlogged) -> 98.49%

fn_3_C4B80: batch-4 implementation (interrupted, unlogged) -> 100.0%

fn_3_C625C: batch-4 implementation (interrupted, unlogged) -> 98.92%

stadiumObjCollision_Castle: batch-4 implementation (interrupted, unlogged)
  -> NOT actually implemented; current source (verified by reading it) is
  still the bare `void stadiumObjCollision_Castle(void) { return; }` stub,
  measuring 0.94%. The batch-4 work described in the task handoff did not
  reach this function before being cut off.

castleFireballMaybe: no change this session beyond reconciliation; current
  source (verified) has NO `static inline` helper — it is still the single
  flat function from the prior "follow-up session" entry above (loop over
  `i < 9`, `memset`/`getAnimationCollisionOffset`/`PSVECSubtract`/`PSVECMag`
  inline in the loop body), still measuring 91.00%. The task handoff's
  mention of a "castleFireballMaybe `static inline` helper experiment" left
  no trace in the current working tree — either it was already reverted
  before the cutoff, or it refers to the (a)/(b) attempts already logged
  under "castleFireballMaybe (follow-up session)" above, both of which were
  reverted for not being inlined by MWCC.

fn_3_C24A0 (this session, Step 2)
  baseline: 0.95% (stub)
  Countdown-fade function on `currentDrawingItem->state` (the already-typed
  `DrawingSceneStruct.state` field at +0x10, s16). New types
  `CastleAnimSubStruct` (a self-relative-offset node: `_00[0x14]`, `_14` a
  u32 *byte offset added to the node's own address*, not a pointer -- the
  target does `sthx` at `h + h->_14 + 0x60`) and
  `CastleLightParticleParams` (0x20-byte DOL bss struct at `lbl_803C5090`,
  fields `_00` f32, `_14` s16, `_17`/`_18`/`_19`/`_1D` u8). New file-local
  externs: `hugeAnimStruct` (raw `u8[0x3154]` view, same symbol
  `stadium_framework.c` gives a richer partial view of -- field `+4` here is
  an untyped pointer not covered by that file's own struct), `inputParams`
  (`u8[14][0x2C]`, matches `stadium_framework.c`'s own declaration),
  `lbl_80367318`/`StadiumLightInput` (matches `stadium_framework.c`'s local
  typedef, inlined here since it isn't exposed via a header), `lbl_3_data_177F4`
  (u32), `lbl_3_data_177F8` (`u8[0xC]`). Float constant `lbl_3_rodata_20F0`
  read directly from the built target `.o`'s `.rodata` via a small Python
  ELF parser (symtab+section offsets) = `1.0f`, written inline per the
  float-constant scope ruling. Fixed `updateVectorInArray`'s prototype (an
  unmatched DOL stub, no other caller in the tree) from `void(void)` to
  `void updateVectorInArray(int idx, Vec* v)` in
  `include/Unknown/File_0x800beb3c.h` / `.c` (body stays a stub); also added
  `#include "Unknown/File_0x80023b90.h"` (characterLightingRelated) and
  `#include "Unknown/File_0x800beb3c.h"` to this file's include list.
  [1] initial impl: `if (--currentDrawingItem->state == 0) {...} else {
      s16 remaining = currentDrawingItem->state; ...}` (cached decremented
      value in a local, plain signed `remaining*128/3` division, struct
      writes before the vector negate) -> 65.41% (structurally complete,
      register/instruction-order residuals throughout)
  [2] split the decrement into its own statement
      (`currentDrawingItem->state--；`) and re-read `currentDrawingItem->state`
      fresh at both the `==0` test and inside the else-branch instead of
      caching a `remaining` local -> 65.41% -> 65.50% (kept; matches target's
      own re-read-through-the-global-pointer pattern seen at both branch
      points, closed the `sth`/reload instruction-count gap at the top of
      the function)
  [3] tried moving the vector-negate block before the `lbl_803C5090` field
      writes (guessing target's apparent instruction interleaving) -> no
      net change, reverted back to struct-writes-then-negate (matches
      target's actual block order once re-examined against the full diff)
  [4] `(u8)(currentDrawingItem->state * 128 / 3)` -> `(u8)((u32)currentDrawingItem->state
      * 128 / 3)` (unsigned division) -> 68.56% (kept; target's magic-number
      division-by-3 sequence still differs in exact form -- see remaining
      note -- but the unsigned cast produced a measurably closer match than
      either plain signed form tried)
  final/kept state: 68.56%. remaining: (a) the division-by-3 reciprocal
  constant/instruction sequence still doesn't match target's exact form
  (target: signed `mulhw` with magic `0x2aaaaaab` plus a `srawi`/`srwi`/`add`
  sign-correction sequence; ours: unsigned `mulhwu` with magic `0xaaaaaaab`
  and no correction sequence -- both compute the same result for this
  guaranteed-nonnegative range, but as different instruction sequences, an
  unresolved codegen-selection question, not a logic bug); (b) the
  vector-negate block (rows ~87-108 in the target instruction stream) does
  not appear as a distinct block in our output at all -- it seems to have
  been merged/reordered into the earlier `lbl_803C5090`-adjacent code by the
  compiler once the unsigned-division change landed, not yet isolated to a
  specific statement-order fix. Not chased further within the ~6-cycle
  residual budget (4 substantive attempts made: statement-split, block
  reorder, signed-vs-unsigned division). A compiling, structurally-complete
  best effort per the task's instructions; no regression to any other
  function in the unit (verified via full-unit diff after each attempt).

fn_3_C4724 (this session, Step 2)
  baseline: 0.93% (stub)
  Particle-emitter update loop, structurally close to (but not identical to)
  `stadium_wario_palace.c`'s `fn_3_CDFA4`/`fn_3_CDD90` pair (same three
  callees `fn_80033620`/`fn_8003403C`/`fn_80033CC8` from
  `stadium_wario_palace.h`, same overall shape) -- used as the structural
  model, plus the raw target instruction stream for exact field
  offsets/branch structure (Ghidra unreachable again this session, `curl`
  exit 7). New types `CastleSparkParticle` (`next`@0, `pos` Vec@4, `vel`
  Vec@0x10, `_38`/`_3C` f32 fade-out timers, `_43` u8, `_48`/`_4A` s16 state
  fields) and `CastleSparkEmitter` (`particles`@0xC, `_10` u32 passed
  through to `fn_80033CC8`, `_14` u16 bitfield-like particle-count cap
  (low 12 bits), `_24` s32 running counter). New file-local extern
  `lbl_80366158` (same DOL global `stadium_framework.c` declares its own
  partial view of, `_28` u8 field only, matching that file's declaration
  exactly). Float constants `lbl_3_rodata_2168`=0.275f,
  `lbl_3_rodata_213C`=0.0f read from the built target `.o`'s `.rodata` via
  the same small Python ELF parser used for `fn_3_C24A0`, written inline.
  Added `#include "game/stadium/stadium_wario_palace.h"` for the three
  callee prototypes (already correctly typed, no header fix needed this
  time). Header prototype changed `void fn_3_C4724(void)` ->
  `BOOL fn_3_C4724(struct _CastleSparkEmitter* emitter)` (no other caller in
  the tree).
  [1] initial impl: `do { if (p->_48!=0) {...; i++;} else if (p->_4A!=0)
      {...; i++;} } while (p != NULL && i < (emitter->_14 & 0xFFF));
      emitter->_24 -= (lbl_80366158._28==0); return emitter->_24 == 0;`,
      `int i` counter -> 94.02% (fully structurally correct on first
      attempt -- every remaining diff was either a register/branch-address
      residual or the return-value idiom)
  [2] `int i` -> `u32 i` (compared against a `u16 & 0xFFF` bitfield value;
      target uses `cmplw`) -> no isolated measurement (bundled into [3])
  [3] `return emitter->_24 == 0;` (direct expression, compiled to a
      branchless CLZ-based boolean) -> `if (emitter->_24 != 0) { return
      FALSE; } return TRUE;` (explicit if/else, forces target's real
      branch-based `cmpwi`/`bne`/`li` idiom) -> 98.16% (kept, combined with
      the u32 counter change)
  [4] flip the if/else polarity: `if (emitter->_24 == 0) { return TRUE; }
      return FALSE;` (matching target's actual branch polarity: `bne`
      skips the `li r3,1` fallthrough) -> 98.22% (kept)
  [5] `CastleSparkEmitter._24` type `u32` -> `s32` (target's compare on it
      used signed `cmpwi`, ours emitted unsigned `cmplwi`) -> 98.79% (kept;
      combined with removing a since-reverted `continue`-based
      restructuring attempt, see [6])
  [6] tried restructuring the if/else-if chain to use a shared `i++;
      p = p->next;` tail reached via `else { p = p->next; continue; }` on
      the "neither branch taken" case, hoping to merge the two duplicated
      `addi r29,r29,1` instructions target keeps as ONE shared instruction
      reached by a branch -> 96.26% (worse -- introduced extra branches
      instead of merging anything; reverted back to the duplicated-`i++`
      form from [1]/[3]/[4]/[5])
  final/kept state: 98.79%. remaining: every one of the ~15 residual diff
  rows is either (a) a branch-target address that differs only because our
  code duplicates the loop-counter `i++` inline in both the `p->_48!=0` and
  `p->_4A!=0` branches, where target reaches a single shared `addi
  r29,r29,1` via an unconditional branch (classic tail-merge the compiler
  didn't perform for us; tried once in [6], made things worse, not
  chased further within the ~6-cycle budget), or (b) the
  `lbl_3_rodata_2168`/`lbl_3_rodata_213C` named-vs-anonymous literal-pool
  class already documented elsewhere in this file, not chaseable from
  within a single function. No regression to any other function in the
  unit (verified via full-unit diff after each attempt).

fn_3_C5304 (this session, Step 2)
  baseline: 0.87% (stub)
  A particle-emitter init function directly analogous to `fn_3_C366C`'s
  particle-init loop but simpler: initializes every `CastleFlameParticle`
  in `handle->particles` (reusing that already-defined type verbatim --
  every field offset it touches, 0x38/0x3C/0x40/0x41/0x42/0x43/0x48/0x4A/
  0x4D/0x4E/0x4F and the `origin` Vec@0x4, matched exactly with no new
  fields needed) and, only for the first particle (`_48==0`), seeds its
  position near a target point read through a new pointer field. New type
  `CastleFireballEmitter` (`particles`@0xC like `CastleFlameEmitter`, but
  a *different* struct -- `targetPos` (`Vec*`)@0x18 and `target`
  (`StadiumObject*`)@0x20, which don't line up with `CastleFlameEmitter`'s
  `origin`/`kind` fields at those offsets, so a fresh type was used rather
  than reusing/widening that one). `arg1` (`StadiumObject* obj`) is stored
  both directly (`handle->target = obj`) and as
  `handle->targetPos = &((CastleFireballTarget*)obj)->anchorPos` -- the
  same `StadiumObject`+0x9C field `castleFireballMaybe` already established
  as a real, separate field from `->pos`@0xA0. Float constants
  `lbl_3_rodata_2160`=10.0f (position-jitter divisor),
  `lbl_3_rodata_216C`=2.5f (y-offset constant), `lbl_3_rodata_213C`=0.0f
  read from the built target `.o`'s `.rodata` via the same Python ELF
  parser used for the other two Step-2 functions; `lbl_3_rodata_20C0`
  (a `f64`, the classic int->double bias magic constant `4503601774854144.0`
  paired with an `xoris ...,0x8000`) was NOT written explicitly -- it's the
  compiler's own artifact of writing `(f32)(15 - rand() % 31) / 10.0f`
  naturally and appears in the diff already matching by name. Header
  prototype changed `void fn_3_C5304(void)` ->
  `void fn_3_C5304(struct _CastleFireballEmitter* handle, StadiumObject* obj)`
  (no other caller in the tree).
  [1] single-shot implementation directly from the target instruction
      stream (Ghidra unreachable again this session) -> **99.26%** (kept
      as-is; every remaining diff row is either a branch-target address
      shift from the still-mismatched literal-pool relocation names, or
      the named-vs-anonymous rodata-pool class documented elsewhere in this
      file -- no structural or register residual found, so no further
      cycles spent on this function)
  final/kept state: 99.26%, first attempt. No regression to any other
  function in the unit (verified via full-unit diff).

Step 3 near-miss check (this session)
  fn_3_C625C (98.92%): every remaining diff row is either (a) the
    `lbl_3_rodata_20F4`/`lbl_3_rodata_2178` named-vs-anonymous literal-pool
    class already documented elsewhere in this file (and the branch-address
    shifts that follow from it), or (b) one real instruction-form mismatch:
    target's `slwi r0, r30, 1` vs ours `clrlslwi r0, r30, 24, 1` when
    indexing `stadiumHazardSoundIDs[stadiumID]` -- see the shared note
    below. No source change made; not a rodata-only near miss, but the one
    real instruction difference is the same recurring class found in the
    other two functions checked this session, not unique to this function.
  thwomp_bounceOffSoundAndVisualFx (98.73%): same `stadiumHazardSoundIDs[stadiumID]`
    `slwi`/`clrlslwi` mismatch, plus a pure register swap (r6/r8) in the
    `lbl_3_bss_9DE8[idx]`/`lbl_3_bss_9E48[idx]` index-computation sequence
    (target computes `idx` into r6 and `idx*0xc` into r8; ours does the
    opposite pairing -- same values, swapped registers). Tried: [1] `int
    idx` -> `u32 idx` -> 98.73% (no change, reverted); [2] reorder the
    `lbl_3_bss_9E48[idx]=1;` statement to after the three `.x/.y/.z`
    assignments (guessing target's statement order) -> 88.03% (much worse,
    reverted); [3] `(g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy != 0) + 2`
    -> `2 + (g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy != 0)` (operand
    order swap) -> 98.73% (no change, reverted). All three reverted; final
    state is byte-identical to session start (verified: still 98.73%
    afterward). Not chased further within the 4-cycle budget.
  bowserCastleStarPadsContaactFn (98.49%): same `slwi`/`clrlslwi` class on
    the identical `stadiumHazardSoundIDs`-style index pattern is NOT
    present here (this function doesn't call `sndFXStartEx`), but a
    parallel r5/r6 register swap exists in its own
    `lbl_3_bss_9DE8[idx]`/`lbl_3_bss_9E48[idx]` block (same shape as
    thwomp's, same root cause). Also one real instruction-form residual:
    target's `if (awarded)` test compiles to `clrlwi. r0, r30, 24` (an
    explicit byte-mask-and-test) where ours emits `cmpwi r30, 0x0` (a plain
    word compare) -- per the file's scope rulings, `awarded` must stay
    `BOOL` (never bare `bool`) since it's a local, so this was not chased
    by narrowing its type; no structured alternative was identified that
    would reproduce the byte-masked test without violating that rule. No
    source change made.
  Common finding across all three: the `stadiumHazardSoundIDs[stadiumID]`
    (and analogous `lbl_3_bss_9E48`/`lbl_3_bss_9DE8` array-index)
    "index register the compiler doesn't trust is already zero-extended"
    pattern (`slwi` vs `clrlslwi`, and the r5/r6/r8 pairing swaps) recurs
    across at least 3 functions in this file that all read
    `g_d_GameSettings.StadiumID`/similar u8 locals shortly after a
    preceding ternary or multiply that also uses the same local. This
    looks like a real, shared root cause (not per-function noise), but no
    single-function source change tried in this session's 3 attempts
    resolved it; flagged for whoever next works on any of these three or
    on `g_d_GameSettings.StadiumID`'s other call sites in this file.

## Notes for next batch (fn_3_C2AA0, fn_3_C805C, thwomp_screenShake,
## thwomp_smokeRelated, fn_3_C4CF4, fn_3_C2EDC)

- All six are still bare `return;` stubs (0.75%-0.83%), next in ascending
  size order after this session's three.
- `updateVectorInArray`'s prototype fix required adding `#include
  "Dolphin/vec.h"` to `include/Unknown/File_0x800beb3c.h` (it only had
  `mssbTypes.h`, which doesn't define `Vec`) -- if any of the next six
  functions need another currently-`void(void)` DOL stub fixed to take a
  `Vec*`/`Vec` parameter, check the target header includes `Dolphin/vec.h`
  (or wherever `Vec` comes from) before assuming a plain prototype edit
  will compile.
- `hugeAnimStruct`, `inputParams`, `lbl_80367318`/`StadiumLightInput`,
  `lbl_80366158` are now all declared file-locally in this file (as raw/
  partial extern views matching `stadium_framework.c`'s own partial views
  of the same DOL globals) -- reuse these declarations rather than
  re-declaring if any of the next six touch the same symbols.
- Recurring `slwi`/`clrlslwi` (and paired register-swap) residual pattern
  on `stadiumHazardSoundIDs[stadiumID]`-style array indexing, seen in
  `fn_3_C625C`, `thwomp_bounceOffSoundAndVisualFx`, and
  `bowserCastleStarPadsContaactFn` (all sub-100%, all otherwise
  structurally exact) -- see the "Step 3 near-miss check" entry above for
  what was tried. If a future session identifies the real cause (possibly
  something about how `g_d_GameSettings.StadiumID` is read relative to a
  preceding ternary/multiply use of the same local), it may resolve
  multiple functions in this file at once, including any of these six if
  they touch the same sound-lookup idiom.
- `fn_3_C24A0` (this session, 68.56%) still has an unresolved
  division-by-3 magic-constant codegen mismatch and a vector-negate block
  that isn't isolating cleanly -- see its hypothesis-log entry for what was
  tried. Not one of the next-six, but flagged in case a later session
  revisits it.
- Ghidra's HTTP decompiler endpoint (127.0.0.1:8080) was unreachable this
  entire session (`curl` exit 7, connection refused, tried multiple times
  across all three Step-2 functions) -- all three new functions this
  session were implemented purely from the objdiff target instruction
  stream plus cross-referencing `stadium_wario_palace.c`/
  `stadium_framework.c` structural analogues. Worth checking if it's back
  up before the next batch, since a real decompile would likely have
  resolved `fn_3_C24A0`'s residuals faster.

## Scope rulings

- Unknown externs: file-local `extern` with the repo symbol name from config symbols.txt; never Ghidra FUN_/DAT_ names.
- This unit's own globals: `static` with exact lbl_3_bss/data/rodata name.
- Partial structs: file-local typedef, `_XX` padding, field width from opcode.
- Enum-like values with no repo enum: literal from the asm, listed in the report.
- Float constants: value read from target, written inline.
- Wrong prototype on an unmatched DOL stub may be fixed in its header + stub (never m_sound).
- If Ghidra has no function at a mapped address, the objdiff target symbol is authoritative; write the C from its instructions.

## Session notes / open issues

- `-inline off` was briefly present in `configure.py` for this object from a
  prior session (to defeat stub dead-code-elimination in a callee); it was
  removed this session — all sibling stadium files use the module default
  (`-inline auto`). Only one function's measured percentage changed as a
  result: `bowserCastleSomething` (100% -> 85.71%), and that drop is the
  accepted `fn_3_C366C`-stub-inlining artifact described above.
- fn_3_C1964 / fn_3_C1974 were written by the batch-1 worker; there is no
  concurrent writer.
- Committed baseline 2c9365b: 2.62%, 7/49 at 100%.
- Mapped address = .text offset + 0x8063F094 (used to cross-check Ghidra
  addresses against this file's header comments; did not line up for
  fn_3_C3F70 in a prior session — see STEP-2-era blocker notes below).
- Ghidra's HTTP decompiler endpoint (127.0.0.1:8080) was unreachable this
  session (`curl` connection refused). fn_3_C366C was implemented entirely
  from the objdiff target instruction stream and cross-referencing
  `stadium_wario_palace.c`'s analogous particle-init functions; no Ghidra
  decompile was available or used.
- Readability TODO before accepting as final: literals 0x1FFF (animState
  frame mask), hazardType 5/6, 0x19/0x1A/2 anim frames, 0x3C4 offset,
  fn_3_C366C's 0xA0/0x46 rodata-array bytes, 0x1D (29) particle `_4D`
  constant, 24/0x48 particle timing constants — check headers for
  enums/defines; none identified yet, all left as literals per the scope
  ruling above.
- `.bss` section match % regressed numerically (36.36% -> 15.61%) despite
  no individual symbol regressing and a new 100%-matched symbol
  (`lbl_3_bss_9F0C`) being added — see the Data sections note above.
- Recheck fn_3_C1964..fn_3_C823C is unaffected; only bowserCastleSomething
  depended on fn_3_C366C's body per this session's verification.
- This session implemented all six of the previously-blocked functions
  (`fn_3_C23E0`, `fn_3_C2244`, `fn_3_C2310`, `fn_3_C3E94`, `fn_3_C3F70`,
  `castleFireballMaybe`) directly from the objdiff target instruction
  stream (formatted asm with resolved relocation names) plus
  `stadium_wario_palace.c`/`stadium_framework.c` structural analogues;
  Ghidra's HTTP endpoint was tried once (`curl -s -m 60 -X POST
  http://127.0.0.1:8080/decompile`) and was unreachable again this session,
  so none of the six used a Ghidra decompile. Results: `fn_3_C23E0` 100%,
  `fn_3_C2310` 100%, `fn_3_C3F70` 99.35%, `fn_3_C3E94` 99.64%,
  `castleFireballMaybe` 91.00%, `fn_3_C2244` 61.35%. No regression to any
  previously-matched function (`fn_3_C1964`, `fn_3_C1974`, `fn_3_C2974`,
  `fn_3_C4068`, `fn_3_C40EC`, `fn_3_C7444`, `bowserCastleSomething` all
  still 100%; `fn_3_C366C` still 99.33%, `fn_3_C823C` still 99.67%).
- Two DOL-stub prototypes were corrected (bodies remain stubs) per the
  scope ruling: `fn_800BF058` (`include/Unknown/File_0x800bf038.h` /
  `src/Unknown/File_0x800bf038.c`, now `void fn_800BF058(void
  (*func)(StadiumModel*, Mtx))`, and that header now includes
  `game/stadium/stadium_framework.h`) and `getAnimationCollisionOffset`
  (`include/Unknown/File_0x8001b728.h` / `.c`, now `void
  getAnimationCollisionOffset(int fielderIndex, int bodyPart, Vec* out)`).
  Neither had any other caller in the tree before this session, so no other
  file needed updating.
- `castleFireballMaybe` reads a `Vec` at `StadiumObject` offset 0x9C (new
  file-local `CastleFireballTarget` type), 4 bytes before the already-shared
  `StadiumObject.pos` field at 0xA0 (heavily used and apparently correct in
  `stadium_wario_palace.c`). These are almost certainly two different real
  fields, not the same field misdocumented — flagged for whoever next needs
  to fully resolve `StadiumObject`'s 0x90-0xA0 region.
- Next pending, smallest-first: fn_3_C298C (0x114) .. see the "Notes for
  next batch" list below. `fn_3_C2244`'s only gap is the bss base-register
  merge described in its hypothesis-log entry above, which should be
  rechecked once more of this file's other bss-touching functions land.
- `lbl_3_data_17804` is a global .data object (symbols.txt), so declare it
  extern, never static.
- `lbl_3_bss_9D9C` is 0x44 bytes in symbols.txt but declared u32. Its real
  shape is unknown, so leave it until an access pattern proves the shape
  (don't pad it to force size).
- Follow-up session (this session): fixed `lbl_3_data_17804` from `static`
  to `extern` per symbols.txt (a correctness fix, kept regardless of
  score), which alone took `fn_3_C2244` 61.35% -> 98.73%; a further
  `s32`/branch-polarity fix on `lbl_3_bss_9D9C` and its early-return guard
  took it to 100.0%. `fn_3_C3F70` readability pass (`entry++`) kept at
  99.35% (no score change; the `j` hoist and `holder`-removal alternatives
  both regressed and were reverted). `castleFireballMaybe` stayed at
  91.00% after testing 3 inlining-hypothesis variants, all reverted — MWCC
  declined to inline any shape of an extracted per-fielder helper under
  this module's `-inline auto`, so the standing "register mismatch implies
  inlined helper" prior did not apply here; the `memset` in the loop was
  confirmed present in the target and left unchanged. No regression to any
  previously-matched function (`fn_3_C1964`, `fn_3_C1974`, `fn_3_C2974`,
  `fn_3_C4068`, `fn_3_C40EC`, `fn_3_C7444`, `bowserCastleSomething`,
  `fn_3_C23E0`, `fn_3_C2310` all still 100%; `fn_3_C823C` still 99.67%,
  `fn_3_C366C` still 99.33%, `fn_3_C3E94` still 99.64%). `.text` section
  9.22% -> 9.47%; `.rodata`/`.bss` unchanged (60.80% / 64.39%).

## Session notes (this session, Step 0: metric reconciliation)

Ran full `ninja` (project-wide); confirmed `build/GYQE01/report.json`'s mtime
did NOT update from the ninja invocation alone (ninja only prints the
in-memory progress summary to stdout, it doesn't rewrite report.json on
disk) — regenerated it explicitly via
`build/tools/objdiff-cli.exe report generate -o build/GYQE01/report.json`.

Per-function `report.json` (`fuzzy_match_percent`) vs live `objdiff-cli diff`
(`match_percent`) for every function in this unit:

| function                          | report.json | live diff |
|------------------------------------|------------:|----------:|
| bowserCastleRelated                 | 0.35  | 0.35  |
| bowserCastleSomething                | 100.00 | 100.00 |
| bowserCastleStarPadsContaactFn       | 98.72  | 98.49  |
| castleFireballMaybe                  | 91.56  | 91.00  |
| flameControl                         | 0.11   | 0.11   |
| fn_3_C1964                           | 100.00 | 100.00 |
| fn_3_C1974                           | 100.00 | 100.00 |
| fn_3_C19C8                           | 0.68   | 0.68   |
| fn_3_C1C18                           | 0.25   | 0.25   |
| fn_3_C2244                           | 100.00 | 100.00 |
| fn_3_C2310                           | 100.00 | 100.00 |
| fn_3_C23E0                           | 100.00 | 100.00 |
| fn_3_C24A0                           | 69.23  | 68.56  |
| fn_3_C2644                           | 0.49   | 0.49   |
| fn_3_C2974                           | 100.00 | 100.00 |
| fn_3_C298C                           | 100.00 | 100.00 |
| fn_3_C2AA0                           | 0.83   | 0.83   |
| fn_3_C2C80                           | 0.66   | 0.66   |
| fn_3_C2EDC                           | 0.75   | 0.75   |
| fn_3_C30F0                           | 0.28   | 0.28   |
| fn_3_C366C                           | 100.00 | 99.33  |
| fn_3_C3C2C                           | 0.65   | 0.65   |
| fn_3_C3E94                           | 100.00 | 99.64  |
| fn_3_C3F70                           | 99.35  | 99.35  |
| fn_3_C4068                           | 100.00 | 100.00 |
| fn_3_C40EC                           | 100.00 | 100.00 |
| fn_3_C444C                           | 0.55   | 0.55   |
| fn_3_C4724                           | 99.02  | 98.79  |
| fn_3_C48D0                           | 0.58   | 0.58   |
| fn_3_C4B80                           | 100.00 | 100.00 |
| fn_3_C4CF4                           | 0.76   | 0.76   |
| fn_3_C4F00                           | 0.39   | 0.39   |
| fn_3_C5304                           | 100.00 | 99.26  |
| fn_3_C54D0                           | 0.75   | 0.75   |
| fn_3_C56E8                           | 0.61   | 0.61   |
| fn_3_C597C                           | 0.46   | 0.46   |
| fn_3_C625C                           | 99.19  | 98.92  |
| fn_3_C7444                           | 100.00 | 100.00 |
| fn_3_C77AC                           | 0.66   | 0.66   |
| fn_3_C805C                           | 0.83   | 0.83   |
| fn_3_C823C                           | 100.00 | 99.67  |
| fn_3_C82B4                           | 0.43   | 0.43   |
| loadBowserCastle                     | 0.12   | 0.12   |
| stadiumObjCollision_Castle           | 0.94   | 0.94   |
| stadiumObjRelated_Castle             | 0.63   | 0.63   |
| thwomp_bounceOffSoundAndVisualFx     | 98.73  | 98.73  |
| thwomp_screenShake                   | 0.80   | 0.80   |
| thwomp_slamControl                   | 0.25   | 0.25   |
| thwomp_smokeRelated                  | 0.80   | 0.80   |

**Conclusion**: `report.json`'s `fuzzy_match_percent` treats rodata
literal-pool reloc-*name*-only mismatches (anonymous `@NNN` literal pool
entry vs target's named `lbl_3_rodata_XXXX` symbol, same byte value/same
instruction) as a 100% match — `fn_3_C823C`, `fn_3_C366C`, `fn_3_C3E94`,
`fn_3_C5304` all show 100.00 in report.json but 99.26-99.67 in live diff,
and every one of their hypothesis-log "remaining" notes above says the sole
residual is exactly this reloc-name class. `fuzzy_match_percent` is a
looser/instruction-fuzzy metric than objdiff-cli's byte/reloc-exact
`match_percent`. All other functions agree between the two metrics to
within rounding. Per the task, `report.json` (100.00 = matched) is now the
official metric for this file; live diff is kept as a secondary/diagnostic
number in the table below, and the extra ~4 functions it already credits
as matched are noted explicitly rather than silently recount as "still
pending."

16/49 matched by report.json (added vs the previous 12-count reconciliation:
fn_3_C823C, fn_3_C366C, fn_3_C3E94, fn_3_C5304, plus fn_3_C2244, fn_3_C2310,
fn_3_C23E0, fn_3_C298C already counted): `bowserCastleSomething`,
`fn_3_C1964`, `fn_3_C1974`, `fn_3_C2244`, `fn_3_C2310`, `fn_3_C23E0`,
`fn_3_C2974`, `fn_3_C298C`, `fn_3_C366C`, `fn_3_C3E94`, `fn_3_C4068`,
`fn_3_C40EC`, `fn_3_C4B80`, `fn_3_C5304`, `fn_3_C7444`, `fn_3_C823C`.

## Session notes (this session, Step 1: shared sound-block hypothesis)

Checked wario_palace's two call sites of the shared stadiumID/vol/voice/val
sound block (starHitAnimation line ~1055, palaceNadoLogic line ~1495):
neither function is itself a 100% match in wario_palace (starHitAnimation
99.52% fuzzy/report.json, palaceNadoLogic 97.60%), so the block's own match
status there could not be confirmed as "100%" in isolation -- but the two
sites show two different declaration styles: (1) starHitAnimation declares
`u8 stadiumID;` at function scope, before vol/val/voice; (2) palaceNadoLogic
declares `int stadiumID` (not u8!) inside a new inner block scope, also
before vol/val/voice.

Tested on thwomp_bounceOffSoundAndVisualFx (baseline 98.73% live-diff /
98.73% report.json):
- (c) stadiumID type u8 -> int, no other change -> 99.58% live-diff / 99.58%
  report.json (kept). This alone fully resolved the documented slwi vs
  clrlslwi mismatch on stadiumHazardSoundIDs[stadiumID] -- confirmed by
  re-diffing instruction-by-instruction: the only residual left afterward
  is an unrelated, pre-existing r6/r8 register-pairing swap in the
  lbl_3_bss_9E48[idx]/lbl_3_bss_9DE8[idx] block (not part of the sound
  block at all).
- (a)/(b) static inline helper variants were NOT tried, since (c) alone
  already fully closed the specific residual described in the task (the
  slwi/clrlslwi mismatch); introducing a helper risked the non-inlining
  problem already documented for castleFireballMaybe (MWCC declining to
  inline extracted per-item helpers under this module's -inline auto in
  this file), so was skipped as unnecessary extra risk once (c) succeeded
  outright.
- Further register-only attempts on the remaining r6/r8 swap (both already
  tried in a prior session): u32 idx cast -> no change (99.58%, reverted);
  reordering lbl_3_bss_9E48[idx]=1; to after the .x/.y/.z writes -> 88.87%
  (reverted, much worse). Final kept state: int idx, statement order
  unchanged, 99.58% (report.json and live-diff agree).

Applied the same stadiumID u8->int fix to fn_3_C625C (the other function in
this file with the identical block): 98.92% -> 99.57% live-diff, 99.19% ->
99.84% report.json (kept).

bowserCastleStarPadsContaactFn does NOT contain this sound block at all
(confirmed by reading its source -- it has its own separate
lbl_3_bss_9E48[idx]/lbl_3_bss_9DE8[idx] write block with no sndFXStartEx
call), so no change was made to it; its prior "Step 3 near-miss" residuals
(the r5/r6 swap and the clrlwi./cmpwi awarded test) remain as documented,
still 98.49% live-diff / 98.72% report.json, unchanged this session.

No regression to any other function in the unit (verified via full-unit
diff after each change).

Wario_palace was NOT edited. Whether the same u8->int fix would help
wario_palace's starHitAnimation/palaceNadoLogic was not tested there (out
of scope per the task), but given the identical root-cause pattern (a u8
local read from g_d_GameSettings.StadiumID used as an array index shortly
after a preceding ternary/multiply on the same local), it plausibly would
apply -- flagged for whoever next works on that file. (palaceNadoLogic
already declares int stadiumID, not u8, at its one call site, which is
suggestive that the target consistently prefers int for this local when
it's used as an array index in that idiom.)

## Session notes (this session, Step 2: stadiumObjCollision_Castle, fn_3_C2AA0, fn_3_C805C)

All three implemented from the objdiff target instruction stream (Ghidra
HTTP endpoint unreachable again this session, curl exit 7, tried at both
the start of Step 2 and per-function) plus structural cross-reference
against stadium_wario_palace.c's analogous functions.

stadiumObjCollision_Castle (0x1A8, mapped 0x80703338): near-identical
structurally to stadium_wario_palace.c's stadiumObjCollisionRelated_Palace
(same double-nested-loop shape: outer for (i<5) computing a running off
into stadiumObjectCollision.vertexOffsets/.hazardData, inner for (j<N)
walking a slot-placement config array, testing obj->_90b1, writing
vertexData[off]=k, building/transforming a matrix, then
storeBoundingBoxCoordinates). Real differences from the Palace analog
(confirmed from the target asm, not guessed): (1) an extra second
parameter s32* count incremented once per hit (Palace's version has no
such parameter); (2) the inner loop bound is a fixed 10 here, not a
dynamic lbl_3_bss_A025-style count; (3) cfg->usedFlag != 7 (not != 0xD as
in Palace); (4) no PalaceObjControl-style struct copy -- CTRLBuildMatrix
is called directly on obj both times; (5) only ONE post-build modification
(m[1][3] *= -100.0f; then a second transform), not Palace's two
symmetric-reposition builds. New type CastleSlotPlacement (0x14 bytes,
modeled on Palace's PalaceSlotPlacement but with usedFlag@0x10/group@0x12
and a 0x14 stride, confirmed by the target's addi r29,r29,0x14 / lbz
...,0x10/0x12 -- these offsets and stride genuinely differ from Palace's
0x1C-stride usedFlag@0xC/group@0xE, not a copy-paste error). extern
CastleSlotPlacement lbl_3_data_17704[]; declared as an open array
(symbols.txt lists it .data:0x00017704 size:0xEC, which is NOT an exact
multiple of 0x14 -- 236/0x14=11.8 -- so no fixed element count was
invented, per the "don't invent array sizes" rule; this was independently
corroborated later by thwompStaticValues in fn_3_C805C, whose declared
size 0xDC IS an exact multiple of 0x14 (=11 elements), confirming 0x14 is
the right stride for this shape). extern u8 lbl_3_bss_9DE0; (symbols.txt:
.bss:0x00009DE0 size:0x1 scope:local) added as the slot-index offset. The
literal -100.0f (lbl_3_rodata_2154) was read directly from the target
.o's .rodata via a small Python ELF parser (symtab+section offsets),
written inline per the float-constant scope ruling.
  [1] initial impl, obj reused directly for the second
      &stadiumObjectCollision.objects[k] assignment (cached k local
      reused) -> 93.82%
  [2] two changes together: (a) re-derive the obj assignment as
      &stadiumObjectCollision.objects[j + lbl_3_bss_9DE0] instead of
      reusing the cached k local (target's asm genuinely reloads
      lbl_3_bss_9DE0 and recomputes k*0xE8 fresh at that point rather
      than keeping k live -- the "one-use temp" prior, confirmed again),
      and (b) cast the final loop-continuation guard to
      (u32)stadiumObjectCollision.hazardData[*idx] != 0 (matching
      Palace's exact cast, fixing a cmpwi->cmplwi mismatch) -> 98.87%
      (kept)
  [3] tried reordering the local declarations (off before cfg) hoping to
      flip the remaining r28/r29 register-pairing swap -> no change
      (98.87%, reverted back to original declaration order)
  final/kept state: 98.87% live-diff / 99.01% report.json. remaining: a
  systematic r28/r29 (and paired r7/r8, r3/r4) register-pairing swap
  throughout the inner-loop body (target: r29=cfg, r28=off*4,
  r7=&lbl_3_bss_9DE0, r8=&stadiumObjectCollision; ours: exactly swapped in
  each pair), plus the usual named-vs-anonymous rodata literal-pool class
  on -100.0f. One declaration-order attempt made, no effect; not chased
  further within the ~6-cycle budget for a pure register/scheduling
  residual.

fn_3_C2AA0 (0x1E0, mapped 0x80701B34): a bounding-box-vs-view-frustum test,
essentially identical in structure to stadium_wario_palace.c's
fn_3_CD968(Vec* p, f32 w, f32 h) -- same near/far Z-clip early return, same
half-width/half-height corner computation, same 4-corner clip-code loop
via PSMTX44MultVec(cam->proj, ...), same final combined&-mask pair of
early-return checks. Copied that function's body verbatim with
fn_3_C2AA0's own local camera pointer, confirmed via the target asm.
Rodata constants (-1.0f, -512.0f, 0.5f, 1.0f) read from the built target
.o and found to be byte-identical to Palace's own values for the same
constants -- written inline as the corresponding literals (matching
Palace's own source, which also writes them as literals, not named
constants).
  [1] direct copy of fn_3_CD968's body with new types -> 93.30%
      (structurally exact on first attempt; every residual is
      register-only or the literal-pool-name class)
  [2] swap halfW = w * 0.5f; halfH = h * 0.5f; statement order to halfH
      first -> 93.34% (kept; this also flipped the fmr f29,f1 / fmr f31,f2
      parameter-register assignment to exactly match target -- confirmed
      by re-diffing instruction-by-instruction, that specific swap is now
      gone)
  [3] tried moving halfW/halfH locals to the TOP of the declaration list
      (before left/right/top/bottom/z) -> 92.88% (worse, reverted)
  final/kept state: 93.34% live-diff / 93.63% report.json. remaining: the
  fmuls f5/f6 (halfW*const/halfH*const) register pairing is still swapped
  relative to target despite [2]'s fix upstream, and the four stfs ...z
  stores for the 4 corners are emitted by target in reverse corner order
  (3,2,1,0) before the x/y stores, which our compiler doesn't reproduce --
  this looks like MWCC's own store-scheduling choice on a block of
  otherwise-identical-value stores, not something a source rewrite of the
  assignment order was able to influence (declaration-order and
  statement-order experiments both tried, one kept ([2]), one reverted
  ([3])). Not chased further within the ~6-cycle budget.

fn_3_C805C (0x1E0, mapped 0x807070F0): the same double-nested-loop shape
as stadiumObjCollision_Castle again, but using a DIFFERENT slot-config
array (thwompStaticValues, a real named symbol from symbols.txt --
.data:0x00017514 size:0xDC, exactly 11 CastleSlotPlacement elements at the
same 0x14 stride) and a different bss offset (lbl_3_bss_9DE4, symbols.txt
.bss:0x00009DE4 size:0x1 scope:local). The key structural difference from
stadiumObjCollision_Castle: this one DOES do the Palace-style struct copy
(ctrl = *(CastleObjControl*)obj;, confirmed by an 8-iteration
lwz/lwzu/stw/stwu copy loop copying exactly 0x44 bytes from obj into a
local buffer, plus one trailing word -- matching Palace's PalaceObjControl
size exactly), but ONLY the SECOND CTRLBuildMatrix/transformVectorsUpdateBoundingBox
pair uses the copy (after CTRLSetTranslation(&ctrl.ctrl, cfg->x, -5.0f,
cfg->z) modifies it) -- the FIRST build+transform pair operates directly
on obj, unlike Palace's version which uses the copy for all three of its
builds. New type CastleObjControl (Control ctrl; u8 _3C[0x44 -
sizeof(Control)];, modeled directly on Palace's PalaceObjControl).
CastleSlotPlacement was extended with real f32 x/y/z fields at 0x0/0x4/0x8
(previously raw padding in stadiumObjCollision_Castle's declaration) since
this function reads cfg->x/cfg->z directly, confirmed by the target asm
(lfs f1, 0x0(r29) / lfs f3, 0x8(r29)); this changes NO byte layout (the
padding array already covered those bytes) and does not affect
stadiumObjCollision_Castle's score. The Y constant -5.0f
(lbl_3_rodata_21E0) was read from the target .o's rodata and written
inline.
  [1] single-shot implementation directly from the target asm, modeled on
      stadiumObjCollision_Castle's already-proven [2] state (recomputed
      obj address rather than cached k, (u32) cast on the
      hazardData[*idx] != 0 guard) -> 99.04% (kept as-is; every remaining
      diff row is the same r28/r29/r7/r8 register-pairing-swap class
      already documented on stadiumObjCollision_Castle, plus the
      literal-pool-name class -- no structural residual, so no further
      cycles spent)
  final/kept state: 99.04% live-diff / 99.13% report.json, first attempt.

No regression to any other function in the unit this session (verified via
full-unit diff after every change); fn_3_C366C incidentally improved
99.33% -> 99.40% live-diff (100.0% report.json unchanged) as a side effect
of the file's rodata/literal-pool layout shifting once the three new
functions' float constants were added -- not a source change to
fn_3_C366C itself.

## Status update (this session, report.json = official metric)

| function                          | report.json (before) | report.json (after) | live-diff (before) | live-diff (after) |
|-------------------------------------|---:|---:|---:|---:|
| thwomp_bounceOffSoundAndVisualFx     | 98.73 | 99.58 | 98.73 | 99.58 |
| fn_3_C625C                           | 99.19 | 99.84 | 98.92 | 99.57 |
| bowserCastleStarPadsContaactFn       | 98.72 | 98.72 (unchanged) | 98.49 | 98.49 (unchanged) |
| stadiumObjCollision_Castle           | 0.94 (stub) | 99.01 | 0.94 (stub) | 98.87 |
| fn_3_C2AA0                           | 0.83 (stub) | 93.63 | 0.83 (stub) | 93.34 |
| fn_3_C805C                           | 0.83 (stub) | 99.13 | 0.83 (stub) | 99.04 |
| fn_3_C366C (incidental)              | 100.00 (unchanged) | 100.00 (unchanged) | 99.33 | 99.40 |

16/49 matched by report.json, unchanged in count from Step 0's
reconciliation (none of this session's changes newly reached 100.00 in
report.json -- all remaining gaps are register/scheduling residuals or the
untouched literal-pool-name class, not full matches).

## Notes for next batch (thwomp_screenShake, thwomp_smokeRelated, fn_3_C4CF4, fn_3_C2EDC, fn_3_C54D0, fn_3_C19C8)

- All six still bare return; stubs, next in ascending size order.
- CastleSlotPlacement (0x14 bytes: x/y/z floats @0-0x8, usedFlag@0x10,
  group@0x12) and CastleObjControl (Control ctrl; u8 _3C[8];, 0x44 bytes)
  are now declared file-locally -- reuse them if any of the next six touch
  lbl_3_data_17704, thwompStaticValues, or another slot-placement array of
  the same shape.
- The r28/r29 (paired r7/r8, r3/r4) register-swap residual seen on
  stadiumObjCollision_Castle and fn_3_C805C (both otherwise structurally
  exact, ~99% live-diff) looks like the same systemic class as the file's
  other documented register-swap residuals -- if a future session
  identifies the real cause, it may resolve both at once.
- Ghidra's HTTP decompiler endpoint (127.0.0.1:8080) was unreachable this
  entire session (curl exit 7, tried at Step 1 and for each Step 2
  function) -- everything this session was written from the objdiff
  target instruction stream plus stadium_wario_palace.c structural
  cross-reference. Worth checking if it's back up before the next batch.

## Session notes (this session: Step 1 correctness fixes + Step 2 thwomp_screenShake/thwomp_smokeRelated/fn_3_C4CF4)

Step 0 reconciliation confirmed the checkpoint's last-recorded numbers exactly
(16/49 report.json-100%, .text 22.61% / .rodata 63.53% / .bss 89.76% live-diff
section match%) before any changes this session.

Step 1a (static-bss correctness fix): removed the mid-file `extern u8
lbl_3_bss_9DE0;` / `extern u8 lbl_3_bss_9DE4;` (both this unit's own
scope:local .bss symbols per symbols.txt) and added
`static u8 lbl_3_bss_9DE0; static u8 lbl_3_bss_9DE4;` to the top static-bss
block in address order (between `lbl_3_bss_9D9C` and `lbl_3_bss_9DE7`).
Also moved the mid-file `typedef struct _CastleSlotPlacement`/
`_CastleObjControl` and `extern CastleSlotPlacement lbl_3_data_17704[];` /
`extern CastleSlotPlacement thwompStaticValues[];` up into the top
declaration section (after `CastleSparkEmitter`, before the static-bss
block). Rebuilt: byte-identical to pre-fix state for every function
(confirmed via full diff, zero deltas) -- this was a pure scope-compliance
fix with no measurable effect, as expected for a rename/relocation of
already-correct storage.

Step 1b (fn_3_C2AA0 combined logic): read the target instruction stream
directly -- target's own compiled code is `li r30,0x0` (init) then
`and r30,r30,r0` (AND, not OR) inside the loop, i.e. the target itself
also always leaves `combined` at 0 through the whole function; the
post-loop `combined&3`/`combined&0xC` checks are dead code in the original
game too, not a decompilation bug on our side. No logic change was made
(the existing `combined = 0; ...; combined &= code;` already matches
target exactly). Only the return-value idiom was fixed per the task
(`return 0`/`return 1` -> `return FALSE`/`return TRUE`, since the function
returns BOOL); this is a text-only change and produced no percentage
change (93.63% report.json / 93.34% live-diff, unchanged before/after).
Spent the <=4-cycle residual budget confirming the "remaining" gap in the
already-logged hypothesis entry is a store-scheduling artifact MWCC applies
to a block of 4 same-value stfs ...z stores (target: reverse corner order
3,2,1,0 before x/y stores) -- and cross-checked against
stadium_wario_palace.c's fn_3_CD968, the function this one was modeled
on verbatim: that sibling reference itself only reaches 93.59% fuzzy,
confirming the residual is a shared, non-source-fixable MWCC scheduling
quirk affecting both files identically, not something specific to this
file's variable ordering. No further cycles spent.

Step 2, thwomp_screenShake (0x1F4, mapped 0x80702ACC): implemented from
the objdiff target instruction stream (Ghidra HTTP endpoint unreachable
again this session, curl exit 7/no response, tried at the start of Step 2
and confirmed dead). Parameter is `camera_803c639c_s* cam` (identified via
the target reading/writing offsets 0x70 (eye, a Vec) and 0x7C (target,
a Vec) on it, which are exactly camera_803c639c_s's own field offsets
per include/static/UnknownHomes_Static.h) -- the function applies a
random per-frame screen-shake offset (computed in view space, transformed
to world space via the current camera's inverse view matrix from
fn_80052768_getCamera(0), which may be a different camera than the cam
parameter) rigidly to both cam->eye and cam->target. New file-local
statics added to the existing static-bss block (address-ordered):
startScreenShake (u8, .bss:0x9D81) and thwompScreenShakeTimeRemaining
(u32, .bss:0x9D8C) -- both already had real names in
config/GYQE01/game/symbols.txt, so declared with those exact names per
the scope ruling, not lbl_3_bss_.... Float constants (lbl_3_rodata_213C
= 0.0f, lbl_3_rodata_214C = 17.0f) read directly from the built target
.o's .rodata via a small Python ELF parser (symtab+section offsets) and
written inline, matching this file's established convention for anonymous
literal-pool constants.
  [1] single-shot implementation from the target asm -> 99.36% (kept;
      structurally exact on first attempt)
  [2] swap the startScreenShake-reset block's statement order
      (`thwompScreenShakeTimeRemaining = 60; startScreenShake = FALSE;`
      instead of the reverse) to flip an r0/r4 register-pairing swap on the
      two li/stb/stw immediates -> 99.52% (kept)
  final/kept state: 99.52% live-diff / 100.00% report.json (fuzzy). Every
  remaining live-diff residual is the named-vs-anonymous rodata
  literal-pool class already documented throughout this file (and the
  branch-address shifts that follow from it) -- no structural residual.

Step 2, thwomp_smokeRelated (0x1F4, mapped 0x8070664C): implemented from
the target instruction stream plus structural cross-reference to this
file's own fn_3_C4724/fn_3_C366C (same lbl_80366158._28-gated
particle-update idiom, same CastleFlameParticle field shapes). Parameter
type: new CastleSmokeEmitter (particles@0xC like CastleFlameEmitter,
but _18 is a pointer to an external anchor Vec here, not an
embedded Vec value -- confirmed by the target dereferencing it
(lwz r3,0x18(r28) then lfs f0,0x4(r3)), so a separate type was used
rather than widening CastleFlameEmitter). Reuses the already-declared
CastleFlameParticle fields (origin, velX, velZ, scale, _14,
_38/_3C, alphaByte, _48/_4A) with no new particle fields needed.
`s32 fallCounter = -smoke->_24;` hoisted once before the loop (matches
target computing it once and reusing the same register every iteration for
the pow((f64)fallCounter, 2.0) call inside the particle-falloff Y-position
formula: `p->origin.y = p->_14 + smoke->target->y - 5.0 * pow((f64)fallCounter, 2.0);`).
Float/double constants read from the target .o's .rodata via the same
Python ELF parser: lbl_3_rodata_2118=2.0 (pow exponent),
lbl_3_rodata_2180=5.0 (Y-falloff multiplier), lbl_3_rodata_21A8
=10.928571701049805f (a per-frame alphaByte decay constant, non-integer
so NOT folded into a -= on the u8 field -- written as
`p->alphaByte = (u8)((f32)p->alphaByte - 10.928571701049805f);` matching
the target's float-subtract-then-truncate sequence exactly);
lbl_3_rodata_20C0/lbl_3_rodata_20E8 (both the standard s32->f64 bias
magic doubles) were not written explicitly, same as elsewhere in this file
-- they're the compiler's own artifact of the natural int-to-double/u8
casts already in the source. thwompConstants (a real named
.rodata symbol per symbols.txt, not an anonymous lbl_3_rodata_...) was
declared `static const f32 thwompConstants = 12.0f;` next to
const_pi_or_180, per the scope ruling for this unit's own named globals.
  [1] single-shot implementation from the target asm -> 95.816% live-diff /
      96.296% report.json (kept as-is; every remaining diff row is either
      (a) a narrow r3/r4/f1/f2 register-pairing swap on the two rodata
      constant loads feeding the pow() call, or (b) the epilogue's
      cntlzw/srwi (part of computing the _24==0 return value) being
      scheduled before vs. after the callee-saved-register reloads, or (c)
      the named-vs-anonymous literal-pool class documented elsewhere in
      this file)
  [2] tried combining the trailing decrement+return into one expression,
      `return (smoke->_24 -= (lbl_80366158._28 == 0)) == 0;` (hoping to
      match the target's epilogue instruction placement) -> 94.8% (worse,
      reverted back to the two-statement form from [1])
  final/kept state: 95.816% live-diff / 96.296% report.json. Not chased
  further within the ~6-cycle budget; the residual is a narrow
  register-scheduling artifact on an otherwise fully structurally-correct
  function (confirmed no missing/extra logic in the diff), not a source
  bug.

Step 2, fn_3_C4CF4 (0x20C, mapped 0x80703D88): a GX fixed-function-pipeline
setup (particle-quad draw state) followed by a while(p != NULL) particle
filter/update loop, structurally near-identical to this file's own,
already-100%-matched fn_3_C4B80 for the entire GX-setup block (same
GXSetZMode/GXSetBlendMode/GXClearVtxDesc/GXSetVtxDesc/
GXSetVtxAttrFmt/GXSetChanCtrl/.../GXSetProjection/GXLoadPosMtxImm/
GXSetCurrentMtx sequence, with the same
`cam = returnFloatFromModeIndex(returnsCurrentMode());` call-twice-not-cached
idiom) -- copied that block verbatim (only the GXSetProjection type
argument differs in principle, but both turned out to be GX_PERSPECTIVE).
Parameters: CastleFlameEmitter* emitter (r3, particles@0xC / _10@0x10
reused directly, no new emitter type needed) and u8 group (r4, compared
byte-for-byte against a new particle field CastleFlameParticle._50, added
to the existing typedef -- the struct's last previously-known field was
_4F@0x4F so this is a same-size contiguous extension, no existing field
offsets moved). GX enum arguments cross-referenced against
include/Dolphin/GX/GXEnum.h and this file's own fn_3_C4B80 (identical
block) plus src/debug/rep_7BF0.c's
`GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE)`
call (confirming the same numeric encoding used here).
  [1] single-shot implementation from the target asm, condition written as
      `p->_48 <= 0 && p->_4A > 0 && p->_50 == group` -> 99.92% (kept as
      first draft; every remaining diff row was one cmplw operand-order
      mismatch plus the branch-address shifts that follow from it)
  [2] flip the equality-test operand order to `group == p->_50` -> 100.0%
      (kept)
  final/kept state: 100.0% live-diff / 100.0% report.json (first
  correctness-checked, then register/operand-order-tuned function this
  session to reach a full match).

No regression to any other function in the unit at any point this session
(verified via full-unit diff after every change, including the two
reverted experiments). Section match% (live-diff): .text 22.61% ->
27.37%, .rodata 63.53% -> 63.68%, .bss 89.76% -> 91.46%. 18/49 matched
by report.json (up from 16/49): added thwomp_screenShake and
fn_3_C4CF4 to the matched set (thwomp_smokeRelated remains sub-100% at
96.296% report.json / 95.816% live-diff).

Ghidra's HTTP decompiler endpoint (127.0.0.1:8080) was unreachable this
entire session (curl exit 7, tried before Step 2 and per-function) --
everything this session was written from the objdiff target instruction
stream plus cross-referencing this file's own already-matched functions
(fn_3_C4B80, fn_3_C4724, fn_3_C366C) and
include/Dolphin/GX/GXEnum.h / src/debug/rep_7BF0.c for GX enum values.

## Notes for next batch (fn_3_C2EDC, fn_3_C54D0, fn_3_C19C8, fn_3_C2C80, fn_3_C77AC, fn_3_C3C2C)

- All six still bare `return;` stubs, next in ascending size order after
  this session's three (thwomp_screenShake 100.0%, fn_3_C4CF4 100.0%,
  thwomp_smokeRelated 96.296% report.json / 95.816% live-diff, all report.json).
- CastleFlameParticle was extended with a new `/*0x50*/ u8 _50;` field
  this session (a per-particle "group" tag compared against a caller-passed
  u8 in fn_3_C4CF4) -- struct is now 0x51 bytes; if any of the next six
  read further into a CastleFlameParticle* past 0x50, extend the same way
  (contiguous, no gap).
- CastleSmokeEmitter (particles@0xC, _10@0x10, target (Vec*)@0x18,
  _24 (s32 counter)@0x24) and camera_803c639c_s* cam (via
  returnFloatFromModeIndex(returnsCurrentMode()), already used by
  fn_3_C2AA0/thwomp_screenShake/fn_3_C4B80/fn_3_C4CF4) are both now
  established patterns in this file -- reuse if any of the next six touch
  the same shapes.
- startScreenShake/thwompScreenShakeTimeRemaining are now declared
  file-locally with their real symbols.txt names (not lbl_3_bss_...) --
  check symbols.txt for a real name before declaring any other bss symbol
  the next six touch.
- The recurring narrow register-pairing-swap residual (seen again this
  session on thwomp_smokeRelated's pow()-constant loads) continues to
  appear across many of this file's otherwise-structurally-exact
  functions; no single-function fix has resolved the general pattern yet.
- Ghidra's HTTP decompiler endpoint was unreachable this entire session --
  worth checking if it's back up before the next batch.

## Hypothesis log (continued)

hazard-sound lookup helper (shared block across fn_3_C625C, thwomp_bounceOffSoundAndVisualFx)
  baseline: fn_3_C625C=99.83871 thwomp_bounceOffSoundAndVisualFx=99.57746 (report.json; all other 47 functions unaffected/untouched)
  [V1] macro `HAZARD_SOUND_PARAM(stadiumID, n)` with the existing `stadiumID`
      local kept and passed explicitly -> fn_3_C625C=99.83871,
      thwomp_bounceOffSoundAndVisualFx=99.57746 (byte-identical to baseline
      for all 49 functions; reverted -- no strict improvement anywhere)
  [V2] macro `HAZARD_SOUND_PARAM(n)` reading `g_d_GameSettings.StadiumID`
      directly, `stadiumID` local removed, `stadiumHazardSoundIDs[stadiumID]`
      -> `stadiumHazardSoundIDs[g_d_GameSettings.StadiumID]` -> fn_3_C625C
      dropped to 87.150536, thwomp_bounceOffSoundAndVisualFx dropped to
      84.633804 (reverted -- large regression on both targets)
  [V3] `static inline u8 hazardSoundParam(int stadiumID, int n)` with the
      local kept and passed explicitly -> fn_3_C625C=99.83871,
      thwomp_bounceOffSoundAndVisualFx=99.57746 (byte-identical to baseline;
      no out-of-line `hazardSoundParam` symbol in the built .o -- cleanly
      inlined; reverted -- no strict improvement anywhere)
  [V4] `static inline u8 hazardSoundParam(int n)` reading
      `g_d_GameSettings.StadiumID` directly, local removed as in V2 ->
      fn_3_C625C=87.150536, thwomp_bounceOffSoundAndVisualFx=84.633804
      (byte-identical to V2's regression; no out-of-line symbol; reverted)
  conclusion: none of the four variants meets the keep bar (>= baseline for
  every function, strictly better for at least one) -- V1/V3 are exactly
  neutral (same register allocation MWCC already produces for the inlined
  duplicated-expression form), V2/V4 substantially regress both target
  functions because dropping the `stadiumID` local changes the register
  MWCC assigns for the repeated `g_d_GameSettings.StadiumID` read at the
  `stadiumHazardSoundIDs[...]` site. Source fully reverted to the
  pre-experiment four-site duplicated-ternary form (verified byte-identical
  report.json for all 49 functions after restoration). The recurring
  `slwi`/`clrlslwi` residual on this same lookup, documented in the
  "Step 3 near-miss check" entry above, remains unresolved and was not
  addressed by this experiment.

## Session note

User review checkpoint: stopped after the hazard-sound helper experiment.
Do not continue without user go-ahead. Propagation to wario_palace/fielder
is the user's decision.

## Hypothesis log (approved 3-function batch: fn_3_C2EDC, fn_3_C54D0, fn_3_C19C8)

fn_3_C2EDC (this session)
  baseline: 0.7518797% (stub)
  Per-particle per-frame update on `CastleFlameParticle* p` (r3): advances
  `_38`/`_3C` timers by `p->_20 * (N * p->scale / p->_4F)` (N=3.0/2.0,
  values read from the built target `.o`'s `.rodata` via a small Python
  ELF parser -- `lbl_3_rodata_2130`=3.0/f64, `lbl_3_rodata_2118`=2.0/f64,
  `lbl_3_rodata_2138`=-255.0/f32, `lbl_3_rodata_213C`=0.0/f32,
  `lbl_3_rodata_2140`=255.0/f64; `lbl_3_rodata_20E8`=4503599627370496.0/f64
  is the compiler's own u32->f64 bias-trick artifact, not written
  explicitly, matching this file's established convention), fades `alpha`
  toward 0, truncates to `alphaByte`, rescales the already-existing
  `lbl_3_rodata_2028` base-color byte array (0xA0/0x46/0x00, already used
  verbatim by `fn_3_C366C`) by the current alpha fraction into `_40/_41/_42`,
  advances `origin` by velocity, decrements `_4A`.
  [1] initial impl: `p->alpha -= 255.0f / p->_4F;` (positive constant,
      subtraction) and `p->_40 = (u8)((f64)lbl_3_rodata_2028[0] *
      p->alphaByte / 255.0);` (multiply-then-divide grouping) -> 81.99248%
      (structurally complete; two real op-form mismatches: target uses
      `fadds` with a *negative* embedded rodata constant instead of
      `fsubs`, and divides `alphaByte/255.0` *before* multiplying by the
      color byte, not after)
  [2] flip to `p->alpha += -255.0f / p->_4F;` (matches target's fadds +
      negative-constant idiom) and reorder to
      `(p->alphaByte / 255.0) * lbl_3_rodata_2028[i]` (divide-first
      grouping, matching target's shared-fdiv-per-field structure) ->
      **98.3985%** (kept; both changes independently justified by matching
      target's real instruction opcodes/operand order, not just tuning)
  remaining: the `_40`/`_41`/`_42` block (bias-trick registers r5/r6/r8/r9
  and stack-slot offsets 0x10/0x14/.../0x30/0x34) is a pure
  register/stack-allocation residual -- every operation present and in the
  right order, only the specific registers/stack slots MWCC picked differ.
  Not chased further within the 2-hypothesis budget (this is the same
  register-allocation-residual class already documented elsewhere in this
  file, e.g. `fn_3_C4724`'s remaining note).

fn_3_C54D0 (this session)
  baseline: 0.74626863% (stub)
  A GX-setup-plus-particle-loop function, structurally identical to the
  file's own `fn_3_C4CF4` (same full GX state block, copied verbatim) but
  gated behind a `fn_800339F0(0, key)` lookup instead of taking the emitter
  directly as a parameter, and compares `p->_50` against the constant `1`
  instead of a passed-in `group` parameter. `key` is
  `((CastleHazardObj*)obj)->_A8 + 0x2A` -- a new byte field `_A8` added to
  `CastleHazardObj` (shifted `_00` padding from `u8[0xA9]` to `u8[0xA8]` to
  keep `hazardType` at the same 0xA9 offset, so the struct's total layout
  and every existing user of `hazardType`/`hasBounced` is unaffected).
  Fixed `fn_800339F0`'s prototype (an unmatched DOL stub, no other caller
  in the tree) from `void(void)` to `void* fn_800339F0(int arg0, u8 arg1)`
  in `include/Unknown/File_0x80033794.h` / `src/Unknown/File_0x80033794.c`
  (body stays a stub, now `return NULL;` to match the new return type).
  [1] single-shot implementation from the target asm (Ghidra unreachable
      at the start of this session, but this function's asm was
      unambiguous without it) -> **100.0%** (kept as-is; first attempt,
      no further cycles needed)

fn_3_C19C8 (this session)
  baseline: 0.6756757% (stub)
  Ghidra's HTTP decompiler came back up mid-session (`curl -X POST
  http://127.0.0.1:8080/decompile -d 'FUN_80700a5c'`, found via
  `get_function_by_address?address=0x80700A5C` first to get the Ghidra
  auto-name) -- this function was implemented from a mix of the raw target
  instruction stream (authoritative for register/operand order and exact
  per-iteration offsets) and Ghidra's decompilation (useful for spotting
  the overall division-by-3/-by-20/-by-0x7FFF magic-multiply idioms, which
  it correctly simplifies to plain `/N` even though the raw asm alone would
  have made these much slower to reverse by hand). Lazily creates a
  drawing-list node the first time through (`insertGraphicDrawingFunction
  (fn_3_C2244, 5)`, cached in the already-existing `lbl_3_bss_9D90`),
  optionally plays a hazard sound, then randomizes a new per-node scratch
  descriptor: a position read from a new 4-entry rodata-adjacent `.data`
  table `lbl_3_data_17880` (`CastleSparkTableEntry { s16 x,y,z; }`, indexed
  by `rand()%3`, size matches symbols.txt's `0x18` exactly as 4*6 bytes even
  though only indices 0-2 are ever read), a signed spread-radius byte
  `baseSpread` (`10 - rand()%20`), and a 2-iteration loop computing a
  short `spread[i]` (a randomized magnitude via a `0x1FFF`-based
  range-narrowing formula that includes a genuine per-iteration
  `>> (1 - i)` term straight out of the target asm) plus two per-iteration
  byte arrays `spreadA[i]`/`spreadB[i]` derived from `baseSpread` and
  `rand()%2`. New struct `CastleSparkScene` (another partial view of
  `DrawingSceneStruct`'s shared +0x10.. scratch region, alongside
  `CastleGfxScene`/`CastleCameraSlot`); its `_2A` field is the same byte
  `fn_3_C2244` already reads as `*((u8*)item + 0x2A)`, confirming this
  function's node and `fn_3_C2244`'s node are the same kind of object.
  [1] single-shot implementation from the target asm/Ghidra -> 95.074326%
      report.json / 94.97298% live-diff (structurally complete; one real
      op-form mismatch: target's initial `if (lbl_3_bss_9D90 == 0)` guard
      compiles to `cmplwi` (unsigned) but ours emitted `cmpwi` (signed))
  [2] change `lbl_3_bss_9D90`'s declared type from `s32` to `u32` (it holds
      a `DrawingSceneStruct*` cast through an integer, so unsigned is also
      the more accurate type) -> **95.47973%** report.json / 95.37838%
      live-diff (kept; fixed the `cmpwi`/`cmplwi` mismatch cleanly, no
      other function affected -- `fn_3_C2244`, the only other reader/writer
      of this global, stayed at 100.0%)
  remaining: a handful of register-pairing swaps in the tail-loop's
  byte-array indexing (`spreadA[i]`/`spreadB[i]` address computed as
  `base+immediate` then indexed by `i` via `stbx`, vs target computing
  `i+immediate` first then indexing by `base` via `stbx` -- numerically
  identical addresses, different operand-order-to-registers assignment),
  the same operand-grouping class documented elsewhere in this file as a
  standing residual. Not chased further within the 2-hypothesis budget.

## Session note (this session: approved 3-function batch)

Stopped after the approved 3-function batch (fn_3_C2EDC, fn_3_C54D0,
fn_3_C19C8). No other function in the unit changed (`report.json` values
for all 46 untouched functions verified byte-identical to the session's
starting checkpoint before/after). 19/49 matched (up from 18/49; added
`fn_3_C54D0`). Section match% (live-diff): `.text` 27.37% -> 32.52%,
`.rodata` 63.68% -> 68.04%, `.bss` unchanged at 91.46%. Full `ninja` +
`build/GYQE01/ok` both succeeded (`CHECK config\GYQE01\build.sha1` / `4
files OK`). Await user go-ahead before continuing to the next batch.

## Hypothesis log (approved 3-function batch: fn_3_C2C80, fn_3_C77AC, fn_3_C3C2C)

fn_3_C2C80 (this session)
  baseline: 0.66225165% (stub)
  Ghidra reachable this session (`FUN_80701d14`). Per-particle init on a
  `CastleSparkParticle*` (r3) seeded from a `StadiumLink*` (r4) chain-link's
  `prevPos` (offset 0x18, exact match for the read-only floats copied into
  `p->pos`); reuses `CastleSparkParticle` fields established for
  `fn_3_C4724` (`vel`, `scale`, `_20`, `alpha`, `_38`/`_3C`, `_40`/`_41`/
  `_42`/`_43`, `_48`/`_4A`/`_4F`) -- struct extended in-place from padding
  gaps (`_1C`/`_20`/`_24`/`_28` gap split into `scale`/`_20`/`alpha`/`_28`
  gap; `_40` gap split into `_40`/`_41`/`_42`/`_43`; `_4C` gap split into
  `_4C[3]`/`_4F`), no offset of any existing field moved. Reused the file's
  established `lbl_3_rodata_2028` base-color byte array (0xA0/0x46/0x00)
  and the `f32 alpha = 255.0f; p->alpha = alpha; p->alphaByte-equivalent
  (`_43`) = alpha;` local-hoist idiom (from `fn_3_C366C`'s hypothesis log)
  to force the real `fctiwz` float-to-int conversion instead of constant
  folding. `p->_4A = p->_4F = rand() % 24 + 0x48;` (inner assignment to the
  narrower `_4F` field first, matching the asm's reload-after-truncate
  pattern -- opposite nesting from `fn_3_C366C`'s `_4F = _4A = X`).
  [1] single-shot implementation from Ghidra + raw target asm ->
      **95.72848%** live-diff / 96.68874% report.json (kept as-is; every
      remaining diff row is the named-vs-anonymous rodata literal-pool
      class already documented throughout this file -- confirmed
      instruction-by-instruction, zero structural/register residual)
  final/kept state: 95.72848% live-diff, first attempt, no further cycles
  spent (nothing left to chase within a single function).

fn_3_C77AC (this session)
  baseline: 0.65789473% (stub)
  Ghidra reachable (`FUN_80706840`). Fireball-chain spark-emitter particle
  init, structurally parallel to `fn_3_C5304` (sets `handle->targetPos`/
  `handle->target` from the same `CastleFireballTarget`+0x9C anchor
  established there) but additionally seeds `handle->_10` (from
  `lbl_3_bss_9F0C[0]`, the same value `fn_3_C366C` copies) and a new
  `handle->_24 = 0x1e;` field -- `CastleFireballEmitter` extended: `_10`
  gap split into a named `u32 _10`, and a new `u32 _24` added after
  `target` (struct grows 0x24 -> 0x28 bytes, no existing field moved).
  Walks `handle->particles` as plain `CastleFlameParticle*` (no new
  particle type needed -- every field this function touches, `origin.x/z`,
  `velX`/`_14`/`velZ`, `scale`, `_38`/`_3C`, `_40`/`_41`/`_42`/`alphaByte`,
  `_48`/`_4A`/`_4D`/`_4E`, already exists on that struct). Per-particle
  angle uses `thwompStaticValues[obj->_A8].rotation`, a new named `f32
  rotation` field replacing `CastleSlotPlacement`'s `_0C[0x10-0x0C]` padding
  gap (4 bytes, no other field's offset moved; `lbl_3_data_17704` and
  `thwompStaticValues`, the only two arrays of this type, both gain the
  field for free). Float constants (PI=3.1415927f, 180.0f, scale-base=8.0f,
  radius=0.35(f64)) read from the built target `.o`'s `.rodata` via a small
  Python ELF parser (symtab+section offsets), written inline; the two
  signed-vs-unsigned `s32->f64`/`u32->f64` bias-trick constants
  (`lbl_3_rodata_20C0`/`lbl_3_rodata_20E8`) were NOT written explicitly,
  matching this file's established convention (compiler artifacts of a
  plain signed `rand() % 3` vs the `u32`-counter `idx` cast).
  [1] single-shot implementation from Ghidra + raw target asm ->
      **86.67105%** live-diff / 87.40131% report.json (structurally
      complete -- every store is at the right offset in the right order;
      remaining diff is register swaps (r27/r28 for the particle pointer,
      f25-f31 shifted by one) plus one narrow scheduling difference in
      where the final `radius * sinf_kludge(ang)` multiply is scheduled
      relative to the `_4D`/`_4E`/`_42`/`_41`/`_40`/`alphaByte` immediate
      materializations and the `idx`/`i` increments)
  [2] swap declaration order of `idx`/`i` locals (`idx` before `i` instead
      of `i` before `idx`) -> 86.63816% (very slightly worse, reverted)
  final/kept state: 86.67105% live-diff (variant [1]). Not chased further
  within the 2-hypothesis budget; the residual is the same
  register/scheduling class documented throughout this file, not a logic
  gap (confirmed: every store address/order matches target exactly).

fn_3_C3C2C (this session)
  baseline: 0.64935064% (stub)
  Ghidra reachable (`FUN_80702cc0`). Per-slot (0..7) hazard-hit visual
  state machine over the already-declared `lbl_3_bss_9E48[8]` (pending
  state byte) / `lbl_3_bss_9DE8[8]` (world position) pair -- both already
  existed in this file's bss block, no new globals needed. On
  `lbl_3_bss_9E48[i] == 1`: projects the position via `fn_800528C0`,
  writes the result into `graphicsRelatedArray[lbl_3_bss_9E50.scene->
  firstHandle + i].object`'s `pos` (the already-declared `CastleGfxObject`
  type), then also indexes via `((CastleGfxScene*)currentDrawingItem)->
  firstHandle + i` (a *different* base pointer than the scene one, in the
  same iteration) to reset `frameIndex` and OR in a `flags` bit, then sets
  the pending state to 2. On `lbl_3_bss_9E48[i] == 2`: does the same
  position projection/write via the scene-pointer index, then tests
  `scale == 2` via the currentDrawingItem-pointer index and, if so, clears
  the `flags` bit and resets pending to 0. After the loop, if
  `lbl_3_bss_9DE7` (already declared) is set, calls
  `removeCurrentDrawingItem()` + `removeGraphicsElementFromScene((DrawingSceneStruct*)lbl_3_bss_9E50.scene)`
  and clears it. `CastleGfxObject` extended with three new named fields
  (`flags` u32@0x54, `frameIndex` u32@0x5C, `scale` u8@0x69), all in
  previously-unused padding, no existing field (`pos`@0x48) moved.
  [1] initial impl: `if (state==2) {...} else if (state<2 && state!=0)
      {...}`, source order matching Ghidra's own reconstructed if/else-if
      order, each branch caching a local `CastleGfxObject* gfx` pointer
      reused across its 3-4 field writes -> 20.75974% (far short --
      structurally correct but ~45 instructions shorter than target:
      target re-derives the full `graphicsRelatedArray[...].object` index
      chain fresh at every single field access, never caching the
      pointer, per this file's standing "no cached local" prior)
  [2] drop the cached `gfx` local entirely, re-index
      `graphicsRelatedArray[scene->firstHandle+i].object`/
      `graphicsRelatedArray[item->firstHandle+i].object` fresh at each of
      the 7-8 field accesses per branch (matching `fn_3_C3E94`'s existing
      no-cache style) -> 24.266233% (better, but still far off -- the
      *physical* block order in the target's raw instruction stream turned
      out to have the `state==1` (simple frameIndex/flags/pending=2) body
      placed FIRST in memory even though it's checked *second* in the
      branch-condition chain (`cmpwi state,2; beq faraway-block` skips
      forward past the physically-first `state==1` body); our source had
      the branches in the opposite lexical order)
  [3] swap the lexical if/else-if order to `if (state==1) {simple} else if
      (state==2) {scale-test}` (matching the *physical* body order found
      in the raw target asm, opposite of Ghidra's own reconstructed
      if/else order) -> **92.40909%** live-diff / 92.733765% report.json
      (kept; this was the real structural fix -- MWCC's block-layout
      heuristic apparently doesn't preserve source condition-check order
      for body placement, and matching physical layout required reversing
      the two branches' lexical order from what Ghidra's CFG-based
      reconstruction implied)
  final/kept state: 92.40909% live-diff. Remaining diff is entirely (a) the
  `lbl_3_bss_9D80`-relative bss base-register merge class already
  documented on `fn_3_C2244` (target keeps two separate named `@ha`/`@l`
  pairs for `lbl_3_bss_9D80` itself, `lbl_3_bss_9DE7`, and
  `lbl_3_bss_9E50`; our build merges them into one synthesized anonymous
  `...bss.0` base, since this file still only declares a fraction of its
  target `.bss`), and (b) one real instruction-form residual: target's
  `if (scale == 2)` compiles to the branchless `subfic`/`cntlzw`/`srwi.`
  CLZ idiom (the same recurring class flagged unresolved on
  `bowserCastleStarPadsContaactFn`'s `awarded` test) where ours emits a
  plain `cmplwi`/`bne`; not chased further since this is the third
  hypothesis for this function and the CLZ-vs-cmp class has no known fix
  within a single function per the existing "Step 3 near-miss check" notes.

Section match% (live-diff, this session): `.text` (not independently
re-measured this session; see report.json 100%-count below for the
per-function delta). 19/49 matched by report.json (unchanged from the
prior session -- none of `fn_3_C2C80`/`fn_3_C77AC`/`fn_3_C3C2C` reached
100%). No regression to any of the other 46 functions in the unit
(verified via full `report.json` diff after the batch: every previously-
listed value in the Status table above, aside from the three touched
functions, is unchanged).

## Session note (this session: approved 3-function batch, fn_3_C2C80/fn_3_C77AC/fn_3_C3C2C)

Stopped after the approved 3-function batch (fn_3_C2C80, fn_3_C77AC,
fn_3_C3C2C). Full `ninja` + `build/GYQE01/ok` both succeeded (`CHECK
config\GYQE01\build.sha1` / `4 files OK`). Await user go-ahead.

## Note from main session (after batch 3 hand-back)
fn_3_C2C80 -> 100% (report.json), done by the main session, not a worker. The
real gap was not constant-pool naming but store order: the target does
`sth 0x4a` then `stb 0x4f` from the untruncated value, then later (after the
`_43` store, before `_48`) reloads `_4F` into `_4A`. Fix:
`p->_4F = p->_4A = rand() % 24 + 0x48;` plus `p->_4A = p->_4F;` after
`p->_43 = alpha;`. No other function moved; sha1 4/4 OK. Status table row
for fn_3_C2C80 should read matched / 100%.

## fn_3_C3C2C — main-session grind (6 attempts, user-approved limit), status: exhausted @ 97.20%
  baseline: 92.73% (`state < 2 && state != 0`); 92.80% with plain `state == 1`
  [1] if/else-if -> `switch (state)` { case 1 / case 2 }  -> 97.15% (kept). Target's
      `cmpwi 2; beq; bge; cmpwi 1; bge` is MWCC's switch lowering.
  [2] per-case scoped `s16 sx, sy` inside `case N: { }` blocks -> 97.15% (kept; gives
      each case its own stack pair, slots were right but sx/sy swapped)
  [3] declare `sy` before `sx` in each case -> 97.20% (kept; stack slots now exact)
  [4] `BOOL finished = scale == 2; if (finished)` -> 97.20%, no codegen change (reverted)
  [5] `static inline BOOL castleGfxAnimDone(obj)` helper -> 97.20%, no change (reverted)
  [6] `if (!(scale - 2))` -> 97.17% (reverted)
  Remaining gaps:
  - target materializes `scale == 2` branch-free (subfic/cntlzw/srwi.) before the beq;
    none of [4]-[6] reproduced it. Unexplored: scale's field type (u8 vs s8/int).
  - statics are addressed off one base `lbl_3_bss_9D80` (+0x67 9DE7, +0x68 9DE8,
    +0xc8 9E48, +0xd0 9E50); ours uses different offsets. This is file-wide .bss
    declaration ORDER, not this function — fixing it may lift several functions at
    once. Worth a dedicated experiment.
  No other function moved in any attempt. sha1 4/4 OK.

## Batch: fn_3_C56E8, stadiumObjRelated_Castle, fn_3_C444C, fn_3_C48D0 (this session)

Ghidra reachable for 3 of 4 (`FUN_807034e0`=fn_3_C444C, `FUN_80703964`=fn_3_C48D0,
`flameTrailDrawBehind`=fn_3_C56E8 found via `get_function_by_address`); Ghidra had
no function at fn_3_C56E8's literal name (`FUN_8070477c` -> not found, resolved via
address lookup instead) and `stadiumObjRelated_Castle` was ALREADY a named Ghidra
function (`stadiumObjRelated(Castle?)`, params `currentVertexIndex`/`currentObjectIndex`)
with a full decompile. All four also cross-checked against the raw objdiff target
instruction stream (authoritative for register/instruction order); the fmadd/fmuls
constant-folding finding below was found purely from the instruction stream (Ghidra's
pseudocode showed these as opaque `DOUBLE_`/`FLOAT_` addresses, not helpful for
telling folded-vs-real).

fn_3_C444C (matched, this session)
  baseline: 0.55% (stub); Ghidra: `void FUN_807034e0(int param_1,int param_2)` --
  a per-particle random-direction spark seeding loop on `param_1->particles`(+0xc),
  reading `param_2`'s float triple at +0x9c/+0xa0/+0xa4 (the already-established
  `CastleFireballTarget.anchorPos`).
  [1] initial impl: `CastleFireballEmitter* handle, StadiumObject* obj` params,
      `f32 x,y,z` hoisted locals for `obj`'s anchorPos, `cosf_kludge`/`sinf_kludge`
      (the f32-narrowing trig wrappers already used elsewhere in this file) for the
      two-angle spherical velocity formula -> 91.34% (structurally complete; every
      residual was `fmuls`/`frsp` sequencing -- target keeps the whole
      `mag*cos(ang1)*cos(ang2)` product in DOUBLE precision (`fmul`, no `frsp`)
      until a single narrow right before the `stfs`, ours narrowed after every
      single trig call)
  [2] replace `cosf_kludge`/`sinf_kludge` with plain `cos()`/`sin()` (the raw f64
      libm calls, letting `f32 * f64 * f64` stay double throughout per normal C
      promotion, narrowing only at the `p->velX = ...;` store) -> 98.54% (kept;
      this is a NEW standing prior for this file: use raw `cos()`/`sin()`, not the
      `*_kludge` wrappers, whenever the target keeps multi-trig products in double
      precision with a single deferred `frsp`)
  [3] hoist `CastleFlameParticle* p = handle->particles;` to the declaration
      (instead of `for (p = handle->particles; ...)`), so `p`'s load happens
      textually/really before the three anchorPos component loads -> **100.0%**
      (kept; target loads `handle->particles` before `obj->anchorPos.x/y/z`, ours
      had it backwards)
  final source (verbatim):
```
void fn_3_C444C(CastleFireballEmitter* handle, StadiumObject* obj) {
    CastleFlameParticle* p = handle->particles;
    f32 x = ((CastleFireballTarget*)obj)->anchorPos.x;
    f32 y = ((CastleFireballTarget*)obj)->anchorPos.y;
    f32 z = ((CastleFireballTarget*)obj)->anchorPos.z;
    u32 i = 0;
    f32 ang1;
    f32 ang2;
    f32 mag;

    for (; p != NULL; p = p->next) {
        p->origin.x = x;
        p->origin.y = y;
        p->origin.z = z;
        ang1 = 3.1415927f * (f32)(rand() % 360) / 180.0f;
        ang2 = 3.1415927f * (f32)(rand() % 360) / 180.0f;
        mag = 0.5f - (f32)(rand() % 3) / 10.0f;
        p->velX = mag * cos(ang1) * cos(ang2);
        p->_14 = -mag * sin(ang1);
        p->velZ = mag * sin(ang1) * cos(ang2);
        p->_3C = 4.4f;
        p->_38 = 4.4f;
        p->_48 = i / 6;
        i++;
        p->_4D = 0x1B;
        p->_4E = 0;
        p->alphaByte = 0xFF;
        p->_42 = 0xFF;
        p->_41 = 0xFF;
        p->_40 = 0xFF;
        p->_4A = 1;
    }
}
```
  header prototype changed `void fn_3_C444C(void)` -> `void fn_3_C444C(struct
  _CastleFireballEmitter* handle, StadiumObject* obj)` (no other caller).

fn_3_C48D0 (pending, this session)
  baseline: 0.58% (stub); Ghidra: `void FUN_80703964(int param_1,undefined4
  *param_2)` -- same per-particle spherical-velocity loop as fn_3_C444C, but
  `param_2` is dereferenced directly as a 3-float vector (`*param_2`,
  `param_2[1]`, `param_2[2]`), i.e. a bare `Vec* pos`, not a `StadiumObject*`;
  and the first random angle uses `rand() % 181` (0x2d4279a3 magic constant,
  `srawi ...,5`) instead of `rand() % 360` (target's other angle and
  fn_3_C444C's both angles use the `0xb60b60b7`/`srawi ...,8` mod-360 magic) --
  confirmed from the raw instruction stream, not guessed.
  [1] `CastleFireballEmitter* handle, Vec* pos` params, `p->origin = *pos;`
      (whole-Vec struct assignment) inside the loop, same
      `cosf_kludge`/`sinf_kludge` as fn_3_C444C's first attempt -> 90.52%
  [2] same raw `cos()`/`sin()` fix as fn_3_C444C[2] -> 97.91%
  [3] `p->origin = *pos;` -> field-by-field `p->origin.x = pos->x;` etc.
      (target uses `lfs`/`stfs` float loads/stores for this copy; our whole-Vec
      assignment compiled to a `lwz`/`stw` word-copy on GPRs instead) -> 98.80%
      (kept)
  [4] tried hoisting `pos->x`/`pos->y` into two temp locals before the
      three-field assignment (attempting to reproduce a load-x,load-y-then-
      store-x,load-z,store-y,store-z pipelined pattern target shows) -> 98.77%
      (reverted; slightly worse, restored plain field-by-field form)
  final/kept state: 98.80%, unchanged since [3]. remaining: (a) the
  named-vs-anonymous literal-pool class already documented throughout this
  file (constants shared with fn_3_C444C: 3.1415927f/180.0f/10.0f/0.5f/4.4f,
  plus the bias double), and (b) a 2-instruction load/store scheduling
  residual in the `p->origin = *pos` copy (target pipelines load-x/load-y
  before storing x; ours is fully serial) -- tried one hoisted-temp variant
  in [4], made it slightly worse, reverted; not chased further within the
  4-attempt budget for what is a pure scheduling nuance.
  header prototype changed `void fn_3_C48D0(void)` -> `void fn_3_C48D0(struct
  _CastleFireballEmitter* handle, Vec* pos)` (no other caller).

fn_3_C56E8 (pending, effectively complete, this session)
  baseline: 0.61% (stub); Ghidra `flameTrailDrawBehind(StadiumObject* obj)`
  (found via `get_function_by_address?address=0x8070477c` since the literal
  Ghidra auto-name `FUN_8070477c` returned "Function not found") -- transforms
  `obj`'s anchorPos (`+0x9c`, `CastleFireballTarget`) into view space once,
  looks up a `CastleFireballEmitter*` via `fn_800339F0(0, obj->_A8+0x2A)`
  (same call shape as `fn_3_C54D0`), then for every particle in
  `handle->particles`: transforms the particle's `origin` into view space and
  sets a new `CastleFlameParticle._50` visibility flag by comparing Z depth
  against the anchor's view-space Z, then draws (same GX setup block as
  `fn_3_C4CF4`/`fn_3_C54D0`) every particle where `_48<=0 && _4A>0 &&
  _50==0`.
  [1] initial impl: ternary `p->_50 = (anchorView.z >= pView.z) ? 1 : 0;` ->
      94.83% (structurally complete; target hoists the constants 0/1 into
      persistent callee-saved registers `r30`/`r31` -- kept alive across the
      `bl PSMTXMultVec` calls inside the loop -- because the source uses a
      real if/else on both arms, not a ternary/branchless idiom; ours
      rematerialized `li r0,0/1` fresh at the point of use instead)
  [2] ternary -> explicit `if (anchorView.z >= pView.z) { p->_50 = 1; } else
      { p->_50 = 0; }` -> **99.98788%** (kept; this is the exact same
      "explicit if/else forces target's real branch idiom" standing prior
      already documented elsewhere in this file, e.g. `fn_3_C4724`)
  [3] tried flipping to `if (anchorView.z < pView.z) { p->_50=0; } else {
      p->_50=1; }` (same logical condition, bodies/comparison both flipped)
      -> 99.36% (worse -- reverted to [2]'s exact form)
  final/kept state: 99.98788%. remaining: only a 2-instruction register-value
  swap (target's `li r30,0`/`li r31,1` vs ours `li r30,1`/`li r31,0` -- same
  values, opposite register assignment for the hoisted 0/1 constants); tried
  one polarity-flip variant in [3], made it worse, reverted. Not chased
  further -- this is functionally a 100% structural/logic match with a
  cosmetic register-pairing residual.
  header prototype changed `void fn_3_C56E8(void)` -> `void
  fn_3_C56E8(StadiumObject* obj)` (no other caller).

stadiumObjRelated_Castle (pending, this session)
  baseline: 0.63% (stub); Ghidra already had a full named decompile
  (`stadiumObjRelated(Castle?)`, no `curl` needed beyond the initial
  `FUN_8070477c`-not-found retry) -- confirms this is the third sibling of
  `stadiumObjCollision_Castle`/`fn_3_C805C`'s double-nested-loop
  (spawnerIndex<5, inner objIdx<10) shape, but: (1) params are `s32* idx,
  s32* count` (same pattern as the other two, not the Ghidra-suggested
  `currentVertexIndex/currentObjectIndex` int* names -- kept this file's
  established `idx`/`count` naming for consistency); (2) the per-hit object
  index is `k = *count` directly (not `j + <bss-offset-base>` like the other
  two); (3) it does the `CastleObjControl` struct-copy (like `fn_3_C805C`,
  unlike `stadiumObjCollision_Castle`) but performs THREE
  `CTRLBuildMatrix`/`transformVectorsUpdateBoundingBox` calls per hit (first
  directly on `obj`, then two more on the copied+translated `ctrl`, for a
  symmetric +jitter/-jitter X/Z pair), confirmed from the raw instruction
  stream, not guessed. New type `CastleFireSpawner` (`x`/`y`/`z` floats @0/4/8,
  `usedFlag` u8@0x10, `group` u8@0x12, stride 0x18 -- confirmed exact via
  symbols.txt's `BowserStadFireSpawners` size 0x108 / 0x18 = 11 elements
  exactly). New externs `BowserStadFireSpawners[11]`, `flameXVelos[3]`.
  [1] initial impl: `f32 transY = -0.3 * 84.09091186523438f +
      15.556818962097168f;` and `jitter = flameXVelos[2] *
      168.18182373046875f;` written as PLAIN LITERAL expressions (values
      read from the target `.o`'s `.rodata` via the established Python ELF
      parser) -> 82.02% (structurally complete; every real residual traced
      to ONE root cause: target performs this arithmetic at RUNTIME via a
      genuine `fmadd`/`fmuls` on THREE separately-loaded named rodata
      constants (`lbl_3_rodata_2190`/`_2198`/`_219C`, kept live in
      callee-saved `f29`-`f31` across the whole function), but MWCC fully
      CONSTANT-FOLDED our plain-literal expression into a single embedded
      value at compile time since all three operands were provably
      compile-time constants)
  [2] moved the three constants into named `static const` file-scope
      globals (`lbl_3_rodata_2190`/`_2198`/`_219C`/`_21A0`) instead of
      inline literals -> 82.02% (no change -- MWCC still folds pure
      `static const`-initialized globals exactly like literals, confirming
      `const`-ness, not locality, drives the folding)
  [3] changed the same four globals from `static const` to plain
      (non-const, mutable) `static` -> **84.62%** (kept; a non-const global
      is not assumed compile-time-invariant, forcing MWCC to keep the real
      runtime `fmadd`/loads -- this is a NEW standing prior: for a target
      constant used in real multi-constant runtime arithmetic (not a
      single value read-and-used-as-is), declare it non-const `static`, not
      `static const`)
  final/kept state: 84.62%. remaining: the four new non-const statics
  (`lbl_3_rodata_2190`/`_2198`/`_219C`/`_21A0`) get merged by the linker/
  compiler into ONE anonymous `...data.0`-based blob (accessed via a single
  base register + fixed offsets) instead of target's four independently
  `lis@ha`/`lis@l`-addressed named symbols -- this is the same class of
  ".bss/.data base-register merge, not yet fixable until more of this
  file's real .data layout is declared" residual already flagged on
  `fn_3_C2244`/`fn_3_C3C2C` for `.bss`; not chaseable from within this one
  function. A dedicated pass on this file's `.data` symbol declarations
  (parallel to the existing `.bss` note) may resolve this class across
  multiple functions at once. Also unresolved: `obj` (the per-hit
  `&stadiumObjectCollision.objects[*count]`) sits in `r26` in target vs
  `r21` in ours -- a pure register-pairing swap, not chased given the
  above merge issue dominates the remaining gap.
  header prototype changed `void stadiumObjRelated_Castle(void)` -> `void
  stadiumObjRelated_Castle(s32* idx, s32* count)` (no other caller).

Net this session: 20/49 -> 21/49 matched (report.json), `fn_3_C444C` newly
100%. `fn_3_C56E8`/`fn_3_C48D0`/`stadiumObjRelated_Castle` all raised from
stubs to 99.99%/98.80%/84.62% respectively but did not reach 100%. No other
function in the unit changed (verified via full `report.json` diff before/
after -- every other row matches the prior session's table exactly). Full
`ninja` + `build/GYQE01/ok` both succeeded (`CHECK config\GYQE01\build.sha1`
/ `4 files OK`).

New standing priors for this file (added to the reusable-findings list):
- For a multi-trig-call vector expression (`mag*cos(a)*cos(b)`-style) where
  the target keeps the whole product in double precision with ONE deferred
  `frsp` before the store: use raw `cos()`/`sin()` (f64-returning), NOT the
  `cosf_kludge`/`sinf_kludge` f32-narrowing wrappers.
- For a target constant used in real multi-constant runtime arithmetic
  (visible as a genuine `fmadd`/`fmuls` on multiple separately-loaded rodata
  values, not just a single value read-and-stored): declare the constant(s)
  as plain non-const `static`, not `static const` -- `static const` gets
  fully constant-folded by MWCC just like a literal, erasing the runtime
  arithmetic the target actually performs.

## Session: Step 0/1/2 (correctness fixes + fn_3_C2644/fn_3_C597C/fn_3_C82B4)

Step 0 baseline (report.json, before any change this session): 21/49 matched.
`.text` 46.21871%, `.rodata` 67.333336%, `.bss` 91.46342% (live-diff, from
`objdiff-cli diff` section list). Target (`left`) has NO `.data` section;
our build (`right`) had a `.data` section of size 20 (0% match) coming from
`stadiumObjRelated_Castle`'s four non-const `lbl_3_rodata_2190/_2198/_219C/
_21A0` statics (the previous session's anti-folding workaround) -- this is
exactly the layout problem flagged by the task.

### Step 1a: stadiumObjRelated_Castle fake-rodata statics (correctness fix)

Removed the four non-const statics entirely; wrote the arithmetic with the
file's established inline-literal convention. Section list after: target
`.text` 46.213463%, `.rodata` 66.37555%, `.bss` 91.46342%; our object has
NO `.data` section anymore (confirmed via `objdiff-cli diff` JSON `right`
sections list) -- correctness restored.

Three attempts made (per the tasks 3-attempt budget) at keeping the
multiply-add a real runtime computation without violating the no-`.data`
rule, checked against the raw target instruction stream:
  - target computes `f31 = fmadd f2(lbl_3_rodata_2190, f64), f1(lbl_3_rodata_2198,
    f32), f0(lbl_3_rodata_219C, f32)` ONCE before the outer 5-iteration
    loop and keeps it resident in the callee-saved `f31` for the whole
    function, narrowed to `f30` via a single `frsp` and added to `cfg->y`
    via `fadds` at each of the two `CTRLSetTranslation` call sites inside
    the loop (operand order `f30(transY) + f1(cfg->y)`). All three operands
    are genuine per-file-local `.rodata` symbols (confirmed `scope:local`
    in `config/GYQE01/game/symbols.txt`), not shared externs, yet the
    target compiler did NOT fold them.
  - [a] `f64 transY = -0.3 * 84.09091186523438f + 15.556818962097168f;` used
    as `cfg->y + (f32)transY` -> 81.379745 live-diff match_percent (stadiumObjRelated_Castle;
    report.json fuzzy 83.06329)
  - [b] same but `cfg->y + transY` (no explicit narrow, natural double
    promotion) -> 80.75317 (worse, reverted to [a] narrow-then-add form)
  - [c] `(f32)transY + cfg->y` (operand order flipped to match target's
    `fadds f30(transY), f1(cfg->y)` literally) -> **82.74683** (kept; best
    of the three, matches target's exact fmadd/fadds operand order)
  final/kept state: `f64 transY = -0.3 * 84.09091186523438f +
  15.556818962097168f;` declared once before the outer loop (unchanged
  position from the pre-fix code), used as `(f32)transY + cfg->y` at both
  `CTRLSetTranslation` call sites (`jitter` unchanged, already a real
  literal `flameXVelos[2] * 168.18182373046875f` inside the loop -- that
  one was never part of the folding problem since `flameXVelos[2]` is a
  real array load, not a compile-time constant). stadiumObjRelated_Castle:
  84.62% (prior, `.data`-violating) -> 82.75% live-diff / 83.06329
  report.json (correctness-fixed, no `.data` section). Per the task, this
  drop is the accepted, required cost of the correctness fix; no further
  cycles spent (3/3 attempts used).

### Step 1b: fn_3_C56E8 readability (no correctness/score change expected)

Replaced `(Vec*)((u8*)obj + 0x9C)` with `&((CastleFireballTarget*)obj)->
anchorPos` in the `PSMTXMultVec(cam->view, ..., &anchorView);` call.
Verified: fn_3_C56E8 unchanged at 99.98788 report.json before and after
(byte-identical rebuild, confirmed via report.json).

### Step 2, fn_3_C2644 (0x330, mapped 0x807016D8)

Ghidra reachable (`FUN_807016d8`) -- a large duplicate-body function:
the state machine gates a full inline copy of the ALREADY-IMPLEMENTED
fn_3_C19C8's entire body (confirmed by direct raw-instruction comparison,
byte-for-byte identical mnemonics/operands from the
`insertGraphicDrawingFunction(fn_3_C2244,5)` call onward through the whole
particle-scratch-randomization tail), preceded by a
`g_d_GameSettings.minigamesEnabled`/`g_GameLogic.gameStatus` range guard, a
`GAME_STATUS_CHAMPIONSHIP`-sets-a-flag check, and a `state % 0x708`
countdown identical in shape to fn_3_C24A0's style. Ghidra's own
`INT_8086ae7c`/`INT_8086ae70` pseudo-names resolved via the raw target asm
relocations to this file's own already-declared `lbl_3_bss_9D9C` /
`lbl_3_bss_9D90` (not new DOL globals). Used `GAME_STATUS_0x1B` (defined
enumerator, header comment says "unsure" but it is the correct value) for
the lower bound of the range guard; the upper bound `0x29` has no
enumerator (GAME_STATUS tops out at `0x27`) so it is left as a literal
(listed below). No new types/globals needed.
  baseline: 0.49019608 (stub)
  [1] initial impl: `if (lbl_3_bss_9D9C == 0) { <big body> } else {
      removeCurrentDrawingItem(); }`, `s16 state` local for the mod-0x708
      countdown, `insertGraphicDrawingFunction(fn_3_C24A0,5)->state = 0x10;`
      chained expression -> 93.38235 (structurally complete; every
      residual traced to 3 real issues resolved below)
  [2] flip the if/else polarity to `if (lbl_3_bss_9D9C != 0) {
      removeCurrentDrawingItem(); } else { <big body> }` -- the raw target
      asm beq/fallthrough layout showed the small
      `removeCurrentDrawingItem` block as the FALLTHROUGH (first-emitted)
      side with a forward branch to the big body, i.e. the opposite of
      standard cond-true-fallthrough codegen; matching required writing
      the condition with reversed polarity so the small block becomes the
      textually-first if-body -> 94.12255 (kept)
  [3] introduce `DrawingSceneStruct* item = currentDrawingItem;` and use
      `item->state` for both the countdown store and the immediate
      re-read in the early-return chain (target caches the object pointer
      once in a register and reuses it for the store+immediate-reload,
      rather than re-fetching the currentDrawingItem global a second
      time) -> 96.0098 (kept, combined with a separate `s16 state` local
      for the truncated/sign-extended countdown value, matching target's
      real register split between the raw s16 store value and its
      sign-extended comparison value)
  [4] tried re-ordering the `s16 state;`/`DrawingSceneStruct* item`
      declaration order -> no change (96.0098, reverted to the combined
      declaration form for readability)
  final/kept state: 96.0098. remaining: (a) the file-wide
  named-vs-anonymous `lbl_3_rodata_20C0` (bias double) literal-pool class,
  and (b) the systemic r28/r29 loop-counter register-pairing-swap residual
  already documented as unresolved on fn_3_C19C8 itself (this function's
  tail loop is a literal duplicate of that one, so it inherits the exact
  same residual, confirmed instruction-by-instruction) -- not chaseable
  from within a single function per the existing precedent. 4 substantive
  attempts used within the 6-attempt budget.
  Callee note: fn_3_C1C18 (still `void fn_3_C1C18(void) { return; }`) is
  NOT referenced by this function; no auto-inlining interaction observed.

### Step 2, fn_3_C597C (0x364, mapped 0x80704A10)

Ghidra reachable (`FUN_80704a10`) -- a fireball-chain particle-init
function parallel to this file's own fn_3_C444C/fn_3_C5304/fn_3_C77AC
(same `mag*cos(ang1)*cos(ang2)` / `-mag*sin(ang1)` / `mag*sin(ang1)*
cos(ang2)` spherical-velocity formula, same
`_3C=_38=4.4f; _48=i/6,i++; _4D=0x1B; _4E=0; alphaByte=_42=_41=_40=0xFF;
_4A=1;` store block, confirmed byte-identical to fn_3_C444C's
already-100%-matched instruction sequence via direct asm comparison), but:
(1) takes a raw object INDEX (`s32 objIndex`, not a pointer -- confirmed
`mulli r0,r3,0xe8` on the incoming register) and derives
`obj = &stadiumObjectCollision.objects[objIndex]` itself; (2) calls
`pitchingMachinePitching(((CastleHazardObj*)obj)->_A8 + 0x2A)` first (an
unmatched DOL stub, prototype fixed below); (3) calls `allocParticleEffect
(fn_3_C4724, 0x80, 0, 0x18, TRUE, ((CastleHazardObj*)obj)->_A8 + 0x34)`
itself rather than taking the handle as a parameter; (4) after the loop,
sets `handle->_10 = lbl_3_bss_9F0C[0]; handle->_24 = 0x1E;` (same fields
fn_3_C366C already established) then does 3 final writes directly on
`obj` -- `((CastleHazardObj*)obj)->_BD = 2;` (new field, see below),
`obj->hasShadow = 0;` (confirmed via raw asm: lbz/rlwimi/stb at offset
0x90 is exactly StadiumObject.hasShadow from stadium_framework.h, an
`rlwimi ...,r4(0),7,24,24` bit-insert of a literal 0, not a masked
whole-byte AND), and `obj->pos.x = 10.0f;` (the already-shared
StadiumObject.pos field at 0xA0, confirmed distinct from
CastleFireballTarget.anchorPos's own 0xA0 alias per the existing
checkpoint note on that overlap). CastleHazardObj extended with a new
`/*0xBD*/ u8 _BD;` field (padding `_B1[0xBD-0xB1]` inserted after
hasBounced@0xB0, no existing field offset moved). Fixed
pitchingMachinePitching's prototype (an unmatched DOL stub, confirmed via
raw asm relocation name on the bl target -- Ghidra's own decompile had
misnamed/miswrapped this call as killParticleEmitter, not to be trusted)
from `void(void)` to `void pitchingMachinePitching(u8 arg0)` in
`include/Unknown/File_0x80033794.h` / `src/Unknown/File_0x80033794.c` (body
stays a stub); no other caller in the tree (stadium_wario_palace.c
includes the same header but does not call this function, confirmed by
grep -- full ninja after the fix rebuilt stadium_wario_palace.o but its
match numbers are unaffected since it never calls this symbol).
Float constants (PI=3.1415927f, 180=180.0f, 10.0=10.0f [same named
lbl_3_rodata_2160 value already used by fn_3_C5304], 0.5=lbl_3_rodata_
20D4, 4.4=lbl_3_rodata_2164) read from the built target .o's .rodata
via the established Python ELF parser, written inline; the lbl_3_rodata_
20C0 bias-double artifact was not written explicitly, matching the file's
convention.
  baseline: 0.4608295 (stub)
  [1] initial impl, `u32 i = 0;` declared/initialized at function top
      (unconditionally, before the `handle != NULL` check) -> 96.75115
      (structurally complete; every residual was register-only)
  [2] move `i = 0;` to inside the `if (handle != NULL)` block, right before
      the loop (target's own `li r27,0x0` for the loop counter happens
      AFTER the null-check and rodata-constant setup, not unconditionally
      at function entry) -> 98.75576 (kept; closed a whole cluster of
      register-pairing swaps caused by the compiler hoisting the
      unconditional i=0 into a different register class)
  [3] tried reordering the `x/y/z`/`ang1/ang2/mag` local declarations ->
      no change (98.75576, reverted to the original declaration order)
  final/kept state: 98.75576. remaining: a pure register-naming shift
  (target r25/f22-f26 vs ours r27/f23-f26, consistently off by one/two
  throughout) plus the file-wide named-vs-anonymous rodata literal-pool
  class -- no structural or missing-logic residual (confirmed
  instruction-by-instruction, every store/call/branch present and in the
  right order). Not chased further within the 3-attempt budget for what is
  a pure register-allocation artifact.

### Step 2, fn_3_C82B4 (0x39C, mapped 0x80707348)

Ghidra reachable (`FUN_80707348`) -- the largest function touched this
session (233 target instructions). Lazily allocates and zeroes a single
combined scratch blob the first time it is called
(`stadiumObjectCollision.vertexDataArray == NULL` guard, confirmed via raw
asm: `_OSAllocFromHeap(4, size)` where
`size = objectCount*sizeof(VecSrcDst) + objectCount*sizeof(s32) +
objectCount*sizeof(f32) + objectCount*sizeof(u16)` -- the compiler's own
strength-reduction produces the identical shift/add sequence regardless of
whether the size is written as one `objectCount*0x22` multiply or this
4-term sum, confirmed by rebuilding both ways with byte-identical resulting
instructions; the 4-term sum was kept since it documents where each of the
four sub-region sizes comes from), then re-derives
`hazardData`/`vertexData`/`vertexOffsets` (the SAME three already-declared
StadiumObjectCollision fields used throughout this file, just
pointer-arithmetic'd into sub-regions of the one allocation via plain
typed-pointer `+ objectCount` arithmetic, which naturally scales by each
field's pointee size -- confirmed this is not new struct fields; Ghidra's
`vertexDataArrayEndPtr`/`vertexDataElementEndPtr`/`vertexDataOffset` names
were its own invented labels for values stored right back into
`hazardData`/`vertexData`/`vertexOffsets`). Then memsets the whole blob,
and runs TWO successive copies of already-existing loop bodies from this
file: the first is functionally identical to fn_3_C805C's entire loop
(same thwompStaticValues/lbl_3_bss_9DE4/CastleObjControl/
CTRLSetTranslation(..., -5.0f, ...) shape, confirmed via
instruction-level comparison of the lbl_3_rodata_21E0=-5.0f constant and
call sequence), and the second is functionally identical to
stadiumObjCollision_Castle's entire loop (same lbl_3_data_17704/
lbl_3_bss_9DE0/no-struct-copy/`m[1][3] *= lbl_3_rodata_2154` shape,
confirmed lbl_3_rodata_2154=-100.0f matches that function's own literal
exactly) -- both reused verbatim with a single combined `idx` running
across both loops (continues accumulating from loop 1 into loop 2, matches
target's r31 never resetting between the two loop blocks) instead of the
separate `s32*count`/`s32*idx` out-parameters those two sibling functions
take, since nothing outside this function needs those counts here. Final
`stadiumObjectCollision.boundingBoxCount = idx;` (the same s16 @0x64
field already named in stadium_framework.h, no new field). All types/
externs reused from fn_3_C805C/stadiumObjCollision_Castle, no new ones
needed.
  baseline: 0.43290043 (stub)
  [1] initial impl: `Mtx m;`/`CastleObjControl ctrl;` declared ONCE at
      function scope, shared across both loop bodies; `size` computed as a
      single `objectCount * 0x22` multiply -> 94.5671 (structurally
      complete -- every store/call/branch present and in the right order;
      remaining diff was almost entirely register-pairing swaps PLUS a
      genuinely smaller stack frame than target, 0xc0 vs target's 0xf0)
  [2] two changes together: (a) `size` rewritten as the 4-term sum of
      per-region `objectCount * sizeof(...)` products (matching the raw
      asm's literal decomposition into mulli+slwi+slwi+3xadd rather
      than a single mulli) -- no effect on its own once rebuilt (compiler
      strength-reduces both forms identically), and (b) wrapped each of the
      two loop bodies in its own `{ }` block scope with its OWN
      `CastleSlotPlacement* cfg;`/`int off/i/j/k;`/`StadiumObject* obj;`/
      `Mtx m;` (plus `CastleObjControl ctrl;` only in the first block)
      locals instead of one shared set at function scope -- this closed the
      0x30-byte stack-frame gap exactly (0xc0 -> 0xf0, matching target),
      since target keeps loop 1's Mtx m, CastleObjControl ctrl, and
      loop 2's own separate Mtx m as three non-overlapping stack slots
      rather than reusing one shared m across both loops -> **95.2987**
      (kept; both changes combined, the size-formula change is
      readability-neutral and the block-scoping change is the real fix)
  [3] tried swapping `CastleObjControl ctrl;`/`Mtx m;` declaration order
      within loop 1's block -> no change (95.2987, reverted to
      ctrl-before-m for consistency with fn_3_C805C's own declaration
      order)
  final/kept state: 95.2987 live-diff / report.json. remaining: a broad
  register-pairing-swap residual across nearly the whole function (the
  stadiumObjectCollision base-pointer cache register itself is r28 in
  target vs r29 in ours, cascading through most of the loop-counter
  registers) -- confirmed no missing/extra logic anywhere (every one of the
  132 remaining instruction-level diff rows out of 233 total is an
  ARG_MISMATCH on a register operand, none is a DIFF_INSERT/DELETE of real
  logic once the frame-size fix landed) plus the usual named-vs-anonymous
  rodata literal-pool class. This is the largest function in the file by
  instruction count; not chased further within the 3-attempt budget for a
  systemic register-allocation artifact affecting nearly every instruction
  equally.

### Session summary

21/49 matched by report.json, UNCHANGED in count from session start (none
of the three Step-2 functions or the two Step-1 targets crossed 100%, but
all made large gains from their prior state: fn_3_C2644 stub(0.49%) ->
96.0098%, fn_3_C597C stub(0.46%) -> 98.75576%, fn_3_C82B4
stub(0.43%) -> 95.2987%, fn_3_C56E8 99.98788% unchanged (readability-only
edit), stadiumObjRelated_Castle 84.62%(.data-violating) -> 83.06329%
(correctness-fixed, no regression risk since it was never counted as
matched)). No other function in the unit changed (confirmed via full
report.json diff before/after: every one of the other 44 rows matches
Step 0's recorded baseline exactly). `.text` section (live-diff) 46.21871%
-> 54.222805%; `.rodata` 67.333336% -> 67.03056% (very slightly down, from
the correctness-required removal of stadiumObjRelated_Castle's
non-const-static rodata-lookalikes); `.bss` unchanged 91.46342%. Our
object's `.data` section is now GONE (was size 20 / 0% match at session
start). Full ninja + build/GYQE01/ok both succeeded (CHECK
config\GYQE01\build.sha1 / 4 files OK).

Symbols changed outside this .c/.h this session:
- pitchingMachinePitching: void(void) -> void(u8 arg0) in
  include/Unknown/File_0x80033794.h / src/Unknown/File_0x80033794.c
  (body remains return;). Only caller in the tree is this file's new
  fn_3_C597C; stadium_wario_palace.c includes the same header but does
  not call this symbol (confirmed by grep), so its compiled output is
  unaffected by the signature change (full ninja rebuilt it as a
  dependency-graph side effect, not a functional change).

Literals left un-named this session (per the scope ruling, none had an
existing header enum/define): 0x708/0x136/300/0x4B0 (fn_3_C2644's
state-machine thresholds, matching fn_3_C24A0's and Ghidra's own
un-enumerated magic numbers), 0x29 (fn_3_C2644's upper GAME_STATUS
range bound -- no enumerator exists past GAME_STATUS_0x27), 0x2A/0x34
(fn_3_C597C's _A8-relative particle-key offsets, same class as this
file's existing _A8+0x2A usages), 10/4.4f/3.1415927f/180.0f/
0.5f/10.0f (fn_3_C597C's spherical-velocity constants, identical
values/roles to fn_3_C444C's already-accepted literals), 0x22/
sizeof(...) terms and -5.0f/-100.0f (fn_3_C82B4, all identical in
value and role to fn_3_C805C/stadiumObjCollision_Castle's own
already-accepted literals for the same constants).

## fn_3_C2644 — attempt 5 (this session): inlining hypothesis, exhausted @ 96.0098%

Step 0 this session: confirmed 21/49 matched by report.json, all values
byte-identical to the checkpoint's last-recorded table (verified via full
`report.json` regen before any change).

  baseline (attempt 5 start): 96.0098% (report.json), the duplicated-body
  form logged under "Step 2, fn_3_C2644" above.
  [5] Replaced the duplicated block (from `if (lbl_3_bss_9D90 == 0) {`
      through the end of the `for (i = 1; i >= 0; i--)` spread loop) with a
      single `fn_3_C19C8();` call statement, removing the now-unused `i`/
      `range` locals -> rebuilt and confirmed via the raw objdiff
      instruction stream that `fn_3_C19C8` does NOT appear as a `bl` target
      anywhere in the compiled `fn_3_C2644` (only as the two symbols'
      own name strings) -- MWCC's `-inline auto` fully inlined the call, as
      the standing prior for this file predicts. Score: exactly unchanged,
      96.0098% (report.json) / 95.93627% (live-diff) -- byte-for-byte tie
      with the pre-attempt duplicated-body form, not an improvement.
  Per the task's branching (tie / inlined-but-not-below-baseline falls into
  the "Otherwise" case, not the "make one more attempt" case), reverted to
  the exact prior duplicated-body text with a targeted edit (restored
  `int i; s32 range;` locals and the full inline block). Rebuilt and
  reconfirmed byte-identical to the pre-attempt state: fn_3_C2644 =
  96.0098%, fn_3_C19C8 = 95.47973%, both unchanged.
  Looked at the residual diff for a possible attempt-6 candidate before
  closing out: the remaining gap is NOT the `insertGraphicDrawingFunction`
  line placement (that block already matches target instruction-for-
  instruction) but two small real mismatches — (a) a `subf r3,r0,r4` vs
  `subf r0,r0,r4` register-pairing swap on the `(item->state+1) % 0x708`
  result, and (b) target compiles the last `if (state < 0x136) {...} else
  if (state != 0x4B0) return;` arm as `cmpwi r0,0x4b0; beq body; b return`
  (an extra explicit `b return` after a `beq`-to-body) where ours compiles
  the equivalent `if (state != 0x4B0) return;` as a single `bne return`
  with body falling through — both are the same recurring
  register/branch-scheduling residual class already documented throughout
  this file, not something a single further attempt is likely to resolve
  cleanly. Per the task's explicit instruction for this exact branch (tie,
  inlined, not below 96.01), no attempt-6 was spent chasing it.
  **Status: fn_3_C2644 marked `exhausted` at 96.0098% (report.json) / 95.93627%
  (live-diff), 5 of 6 attempts used.** No regression to any other function
  in the unit (report.json for all other 48 functions verified
  byte-identical before/after this attempt, including a full revert
  round-trip).

## Step 2, fn_3_C4F00 (0x404, mapped 0x80703F94)

Ghidra reachable (`FUN_80703f94`, found via `get_function_by_address` since
the literal name lookup returned the same auto-name). A `CastleFireballEmitter*`
particle-lifetime-and-respawn update loop, structurally a close sibling of
`fn_3_C444C`/`fn_3_C5304`/`fn_3_C597C` (same `handle->particles`/`handle->target`
shapes) but for ongoing per-frame maintenance rather than one-shot init: calls
`fn_80033620(handle)` then `GXSetZMode`/`GXSetBlendMode` only (no full GX
vtx/tev/proj block, confirmed absent from the raw asm -- this function
doesn't draw), then a `do { ... p = p->next; } while (p != NULL);` loop with
two independent branches: (1) if `p->_48 != 0`, decrement it by
`(lbl_80366158._28 == 0)` (the file's established "pause-gated countdown"
idiom) and, when it hits 0, respawn `p->origin` at a random polar offset
(`mag = (f32)(15 - rand()%31)/10.0f`, `ang = 3.1415927f * (f32)(rand()%361)/180.0f`
-- confirmed `rand() % 361`, not 360, from the raw asm's `mulli ...,0x169`
divisor) around `handle->target` via `CTRLBuildMatrix((Control*)handle->target,
m); PSMTXMultVec(m, &off, &p->origin);`; else if `p->_4A != 0 &&
lbl_80366158._28 == 0`, grows or shrinks `p->_38`/`p->_3C`/`p->alphaByte`
(threshold constants read from the target `.o`'s `.rodata`: growth step
0.125f, threshold 2.0f) and flips `p->_4F`/`p->_4A` at the extremes. After
that if/else, unconditionally: if `p->_4A == 0`, resets the particle
(`_3C=_38=0; _4A=1; _4F=0; _48=0;`) and does the SAME random-polar respawn
again (confirmed via the raw asm reusing the identical stack slots for both
call sites, not two independent copies), then `p->alphaByte = 0;`. All
fields/constants reused from already-established types, no new ones needed.
Return type `BOOL` (target's epilogue has an explicit `li r3, 0x0` before
the restore sequence, matching the pattern already used for
`fn_3_C4724`/`castleFireballMaybe`-style particle-update gates in this
file, even though this one always returns `FALSE`).
  baseline: 0.38910505% (stub)
  [1] initial impl: `Vec off; Mtx m; f32 mag; f32 ang;` declared freshly
      *inside each of the two respawn blocks* (matching Ghidra's own
      per-block local reconstruction), `off.x`/`off.y`/`off.z` assigned in
      that field order -> 86.101166% (structurally complete; every real
      residual traced to two issues resolved below, plus the file-wide
      named-vs-anonymous rodata class)
  [2] hoist `Vec off; Mtx m; f32 mag; f32 ang;` to function scope, declared
      ONCE and reused by both respawn call sites (the raw asm confirmed
      both respawns reuse the exact same stack offsets, 0x90-byte frame vs
      my [1]'s 0xC0 -- a real 0x30-byte stack-frame bloat from declaring
      the same 4 locals twice in non-overlapping block scopes) -> 94.12451%
      (kept; closed the frame-size gap exactly, 0xc0 -> 0x90 matching
      target)
  [3] swapped declaration order to `f32 ang; f32 mag;` (was `mag; ang;`) --
      this alone fixed a consistent f30/f31 register-pairing swap between
      the `mag`/`ang` values across both respawn sites -> 94.24124% (kept;
      small gain, but confirmed via instruction-by-instruction re-diff that
      the entire f30/f31 swap class was resolved)
  [4] reordered the `off.x`/`off.y`/`off.z` assignment statements from
      `x; y=2.5f; z;` to `x; z; y=2.5f;` (matching the raw asm's actual
      instruction order: target computes and stores `x` fully, computes
      the RAW (unnarrowed) `z` multiply, THEN loads/stores the constant
      `y=2.5f`, and only after that narrows+stores `z` -- i.e. the `y=2.5f`
      store is scheduled between `z`'s multiply and its narrow, which only
      a `x; z; y;` source order reproduced) -> **99.22179%** (kept; large
      jump, fully resolved the field-store-scheduling residual at both
      respawn call sites)
  Tried declaring `p = handle->particles;` as a combined
  declaration-with-initializer (`CastleFlameParticle* p = handle->particles;`)
  vs. a separate assignment statement placed either before or after the
  three setup calls: all three forms compiled byte-identical (99.22179%,
  no change) -- kept the combined declaration-with-initializer form for
  readability. Target loads `p` from raw `r3` (the parameter register)
  BEFORE the `mr r29,r3`/`fn_80033620`/`GXSetZMode`/`GXSetBlendMode`
  sequence even begins (confirmed: `lwz r30, 0xc(r3)` is the very first
  instruction after the prologue's register saves); ours schedules the
  equivalent load just before the loop's first use, after all three setup
  calls. This is a pure instruction-scheduling choice by MWCC (both
  registers hold provably-identical values either way -- `r3`/`r29` are
  never reassigned in between) that no combination of declaration-order or
  statement-placement reproduced; not chased further within the 4-attempt
  budget used.
  final/kept state: 99.22179% (report.json). remaining: (a) the single
  `p`-load scheduling-position residual just described (2 instruction rows),
  and (b) the file-wide named-vs-anonymous rodata literal-pool class
  (`lbl_3_rodata_20C0`/`_2160`/`_2158`/`_215C`/`_216C`/`_2170`/`_2174`/
  `_213C`, all values confirmed correct via the target `.o`'s `.rodata`
  bytes) and the branch-target-address shifts that follow from it --
  confirmed via full instruction-by-instruction re-diff that no other
  structural or register residual remains. No regression to any other
  function in the unit (report.json for all 48 other functions verified
  byte-identical before/after; 21/49 still at 100.0%).
  header prototype changed `void fn_3_C4F00(void)` -> `BOOL
  fn_3_C4F00(struct _CastleFireballEmitter* handle)` (no other caller in
  the tree; called via a function-pointer table elsewhere, matching the
  `void*` `allocParticleEffect` callback convention already used
  throughout this file).

## Step 2, bowserCastleRelated (0x480, mapped 0x80704E70)

Ghidra reachable, but under a different auto-name (`flameFielderBurnUpdate`
via `get_function_by_address?address=0x80704E70`; the literal name lookup
returned the same function). Kept this file's existing placeholder symbol
name `bowserCastleRelated` unchanged -- renaming a placeholder is the
orchestrator's call, not this task's, so no rename was made even though
Ghidra's guess differs. A per-hazard-object outer loop
(`for (i = 0; i < lbl_3_bss_9DE3; i++)`, both `lbl_3_bss_9DE2`
(a new "flame object base index" u8) and `lbl_3_bss_9DE3` (a new "flame
count" u8) resolved to real addresses inside the existing `lbl_3_bss_9D80`
blob via the raw asm's `lbz r0, 0x62(r23)`/`lbz r0, 0x63(r23)` offsets --
`lbl_3_bss_9D80+0x62`/`+0x63` -- landing in the previously-undeclared gap
between `lbl_3_bss_9DE0` (ends 0x9DE1) and `lbl_3_bss_9DE4` (starts
0x9DE4); declared both `static u8` in address order in the existing
static-bss block) that, for each `CastleHazardObj` with `_BD == 1`, calls
the ALREADY-IMPLEMENTED `castleFireballMaybe(obj)` (confirmed via direct
instruction-level comparison: the raw asm's inlined
`memset`/`getAnimationCollisionOffset(i,4,&off)`/`PSVECSubtract`/
`PSVECMag`/`<= 2.6f`/`maybeCastleFireballBurn(i,1)` sequence is
byte-for-byte the same shape as `castleFireballMaybe`'s own already-written
body, including its exact 2.6f threshold and loop bound of 9 -- this is the
same "duplicate body implies the original called the earlier-defined
function, and `-inline auto` inlined it" standing prior, but this time
using an EXISTING top-level function rather than needing an extraction
experiment) and, if it returns `TRUE`, spawns a `CastleFireballEmitter`
particle burst via `allocParticleEffect(fn_3_C4724, 0x80, 0, 0x18, TRUE,
((CastleHazardObj*)obj)->_A8 + 0x34)` -- a per-particle loop identical in
shape to `fn_3_C597C`'s (same `origin.x/y/z` cache-then-broadcast, same
`_3C=_38=4.4f; _48=i/6,i++; _4D=0x1B; _4E=0; alphaByte=_42=_41=_40=0xFF;
_4A=1;` block, same final `handle->_10 = lbl_3_bss_9F0C[0]; handle->_24 =
0x1E;`), but with a DIFFERENT first-angle random range: `rand() % 181`
(confirmed via the raw asm's `mulli ...,0xb5` divisor, an actual magic
constant for division by 181) instead of `fn_3_C597C`'s `rand() % 360` --
the second angle and `mag` formulas are identical to `fn_3_C597C`'s. After
the particle spawn (whether or not `handle` was non-NULL), sets
`((CastleHazardObj*)obj)->_BD = 2; obj->hasShadow = 0; obj->pos.x = 10.0f;`
-- the exact same trailing three statements, in the same order, that
`fn_3_C597C` already established. No new types needed beyond the two new
`u8` bss globals.
  baseline: 0.3472222% (stub)
  [1] single-shot implementation calling `castleFireballMaybe(obj)`
      directly (rather than re-deriving its logic inline) -> **94.767365%**
      (kept as-is; confirmed via the raw instruction stream that MWCC fully
      inlined the call -- no `bl castleFireballMaybe` appears anywhere in
      the compiled output -- and `castleFireballMaybe` itself is unaffected,
      still 91.55556%)
  [2] tried `castleFireballMaybe(obj) != FALSE` instead of the bare
      truthiness test in the `&&` condition, hoping to change how the
      inlined return value's boolean test is compiled (target's test at
      this point is `clrlwi. r0,r0,24; beq`, a byte-masked test, vs ours'
      plain `cmpwi r0,0x0`) -> 94.767365% (no change, reverted to the
      bare form for readability)
  final/kept state: 94.767365%. remaining: (a) `castleFireballMaybe`'s own
  already-documented, unresolved LICM residual (target keeps `obj`
  resident and recomputes `addi r4,r30,0x9c` fresh at the `PSVECSubtract`
  call site each loop iteration; our compiler hoists `&obj->anchorPos` into
  its own register once) is inherited here verbatim once inlined -- not
  fixable from this caller per the existing precedent that no surface
  rewrite of that expression changed it even in `castleFireballMaybe`
  itself; (b) the file-wide `.bss` base-register-merge class already
  documented on `fn_3_C2244`/`fn_3_C3C2C` (target keeps `lbl_3_bss_9D80`,
  `stadiumObjectCollision`, and `g_GameLogic` as three separately-hoisted,
  loop-invariant registers held across the whole outer loop; ours merges
  several of this file's still-partially-declared `.bss` symbols under one
  synthesized anonymous base, producing a smaller but differently-shaped
  16-byte-smaller stack frame, 0x140 vs target's 0x150) -- not chaseable
  from within this one function; (c) the usual named-vs-anonymous rodata
  literal-pool class. No regression to any other function in the unit
  (report.json for all 48 other functions verified byte-identical
  before/after, including `castleFireballMaybe` itself unchanged at
  91.55556%; 21/49 still at 100.0%).

## Step 2, fn_3_C30F0 (0x57C, mapped 0x80702184)

Ghidra reachable (`FUN_80702184`, no real name -- messy pseudocode with many
opaque `DOUBLE_`/`INT_`/`BYTE_` addresses; used mainly to confirm the
overall control-flow shape, with the raw target instruction stream
authoritative for every field offset/constant). `emitter` (`CastleFlameEmitter*`,
the same type as `fn_3_C4CF4`'s parameter -- this is the callback
`fn_3_C298C`/`bowserCastleSomething` pass to `allocParticleEffect`, per the
task's pointer note). Guarded by a `g_GameLogic.gameStatus` range check
(`< GAME_STATUS_0x1B` or `> GAME_STATUS_MINIGAME_READY` (0x21) both
early-return -- confirmed real enumerator via the raw asm's `cmplwi
r0,0x21`, matching Ghidra's own guessed name "ReadyMinigameScreen"), then,
only during `GAME_STATUS_LIVE_BALL`/`GAME_STATUS_AT_BAT`, a frustum-culling
early return via the ALREADY-IMPLEMENTED `fn_3_C2AA0(&pos, 4.0f, 4.0f)`
(confirmed via the raw asm: `emitter->origin` is first copied into a local
stack `Vec` before the call, not passed by address directly -- a real
difference from a naive `&emitter->origin`). Then the same
`fn_80033620`/`GXSetZMode`/`GXSetBlendMode` setup trio as `fn_3_C4F00`, but
with `GX_BL_ONE, GX_BL_ONE` blend factors (confirmed distinct from every
other GX block in this file, which use `GX_BL_SRCALPHA`/
`GX_BL_INVSRCALPHA`). The per-particle loop's "active" branch
(`p->_48 <= 0 && p->_4A != 0`) calls `fn_8003403C`/`fn_80033CC8` (same
established prototypes) then, gated on `returnsCurrentMode() == 0`, calls
the ALREADY-IMPLEMENTED `fn_3_C2EDC(p)` -- confirmed via direct
instruction-level comparison that this inlined block is byte-for-byte
`fn_3_C2EDC`'s own body (the timer-advance/alpha-fade/color-byte/origin
update block), the same "duplicate body implies the original called the
earlier-defined function" standing prior, this time an existing function
rather than an extraction experiment. After that gated block,
unconditionally: `p->_48 -= (returnsCurrentMode() == 0);` (same
"value -= (cond==0)" idiom as `fn_3_C4F00`), then on `p->_4A == 0`, a
respawn block that is ALSO a near-verbatim copy of `fn_3_C366C`'s
per-particle creation body (same `0.01 * cosf_kludge(ang)`/
`0.01 * sinf_kludge(ang)` velocity, same `0.08f` for `_14`, same
`0.5f + rand()%2500/1000.0` scale-jitter, same `rand()%101/100.0` for
`_20`, same `rand()%24+0x48` for `_4A`/`_4F`, same `lbl_3_rodata_2028`
color-byte array, same `255.0f` alpha/alphaByte pair, same trailing
`p->_4A = p->_4F;` reload already documented on `fn_3_C2C80` as a real,
separate store after the alpha/alphaByte writes) -- differences from
`fn_3_C366C`: `p->_48` is reset to `0` (not staggered by an `i` counter,
since this respawns one already-existing particle rather than
initializing a fresh batch) and `origin` is copied from `emitter->origin`
directly rather than a cached `handle->origin` local (no `_4D`/`_4E`
touched here, matching the raw asm). All float constants
(`lbl_3_rodata_2148`=4.0f, `lbl_3_rodata_2108`=0.08f,
`lbl_3_rodata_2110`=1000.0, `lbl_3_rodata_2120`=100.0,
`lbl_3_rodata_2128`=255.0f, `lbl_3_rodata_20D4`=0.5f -- all cross-checked
against the target `.o`'s `.rodata` bytes via the established Python ELF
parser) reused this file's existing `const_pi_or_180`/`lbl_3_rodata_2100`
(0.01) naming where the value matched an already-declared symbol exactly.
No new types needed. `bowserCastleSomething`'s existing
`allocParticleEffect(fn_3_C30F0, ...)` call site (already 100%) needed no
change since it already implicitly casts the function pointer.
  baseline: 0.28490028% (stub)
  [1] initial impl, `fn_3_C2AA0(&emitter->origin, 4.0f, 4.0f)` (no local
      copy) and a single combined `if (gameStatus < 0x1B || gameStatus >
      GAME_STATUS_MINIGAME_READY) return;` guard -> 95.86894%
      (`bowserCastleSomething` unaffected, still 100%; structurally
      complete on the first attempt -- every residual traced to the two
      issues resolved below, plus the file-wide rodata-name class)
  [2] two changes together: (a) split the combined `||` range guard into
      two separate sequential `if (...) return;` statements (target
      compiles both bounds as independent forward branches to the SAME
      shared early-return target -- a combined `||` expression produced a
      different, mirrored branch-polarity structure), and (b) copy
      `emitter->origin` into a local `Vec pos;` before the `fn_3_C2AA0`
      call instead of passing `&emitter->origin` directly (matching the
      raw asm's actual stack-copy-then-pass sequence) -> **97.61253%**
      (kept; both confirmed via re-diff to close the exact residuals they
      targeted)
  final/kept state: 97.61253%. remaining: (a) the file-wide
  named-vs-anonymous rodata literal-pool class (confirmed via re-diff that
  every remaining `lis`/`lfs`/`lfd` reloc-name mismatch is this class, not
  a value or structural difference); (b) one instance of the
  `clrlwi.`/`cmpwi` branchless-vs-word-compare BOOL-test idiom already
  flagged as unresolved elsewhere in this file (on the `!fn_3_C2AA0(...)`
  test) -- per the file's own BOOL/bare-`bool` scope ruling, `fn_3_C2AA0`
  already correctly returns `BOOL`, and no narrower type is available
  without violating that rule, so this was left as documented; (c) minor
  stack-offset shifts in the respawn block's scratch temporaries, a
  natural side effect of the new `Vec pos` local changing the frame
  layout, not a residual of its own. No regression to any other function
  in the unit (report.json for all 48 other functions verified
  byte-identical before/after, including `fn_3_C2EDC` unchanged at
  98.3985% and `bowserCastleSomething`/`fn_3_C298C` both still 100.0%;
  21/49 still at 100.0%).
  header prototype changed `void fn_3_C30F0(void)` -> `void
  fn_3_C30F0(struct _CastleFlameEmitter* emitter)`; `bowserCastleSomething`
  re-verified still 100.0% after the signature change (its existing
  implicit function-pointer cast at the `allocParticleEffect` call site
  needed no edit).

## Session note

Stopped after the approved 10-function run (fn_3_C56E8,
stadiumObjRelated_Castle, fn_3_C444C, fn_3_C48D0, fn_3_C2644, fn_3_C597C,
fn_3_C82B4, fn_3_C4F00, bowserCastleRelated, fn_3_C30F0). Await user
go-ahead.

## 2026-09-22 session: remaining stubs + retries

### fn_3_C1C18 (0x62C, mapped 0x80700CAC) — spark billboard draw callback
Signature `void fn_3_C1C18(CastleCameraSlot* slot)` (slot->mtx at +8, slot->item at +0x38 is the
CastleSparkScene). GX immediate-mode: one billboard quad (width 512, height 256 scaled by
(100+baseSpread)/100 and -viewZ/1280), then up to 2 chained rotated quads per spreadA/spread[i]
(s16 angle * 2pi/65536). Tail: `_29 -= (_29 != 0); a = _2A - (_29 == 0)*42; _2A = a * (a > 0);`
(branchless; target literally multiplies by the comparisons). New extern `f32 lbl_3_data_1787C`.
Added include `Unknown/File_0x80024404.h` (SetDisplayStateTexture).
  baseline: 0.25% (stub)
  [1] initial impl, `i < 3` texture loop, f32 clamp temp            -> 88.93%
  [2] `i <= 2` (target is `cmpwi 2; ble`) + inline scale into both exprs -> 88.41% (inline reverted, `<=` kept)
  [3] clamp temp is `int alpha` (was accidentally f32 -> float compare) + `0.5f*(d)` operand order -> 93.72% (kept; fmadds order unchanged either way)
  [4] separate u32 local for loop color                               -> 93.44% (reverted)
  [5] dx/dy scoped inside loop                                        -> 93.61% (reverted)
  remaining: pure REGISTER_ALLOC — target keeps i in r25 (reusing first color's reg), loop color r27,
  scene+i in r26; fmadds operand order f3*f25 vs ours f25*f3; first-quad setup float scheduling.

### thwomp_slamControl (0x650, mapped 0x80706AA0; Ghidra `thwompControl`)
Signature `void thwomp_slamControl(CastleThwompObj* thwomp)`. New overlay struct CastleThwompObj
(resetPending 0x99, pos 0x9C, index 0xA8, fallSpeed 0xAC, state 0xB0, framesOnGround 0xB1,
checkForSlam 0xB2) and enum THWOMP_STATE (PERCHED/WINDUP/FALLING/GROUNDED/RETURNING) — names
from Ghidra's annotated decomp. New extern `f32 thompFallingSpeedConstants[3]`.
The FALLING case's smoke-particle init is fn_3_C77AC auto-inlined (confirmed: calling it from the
source reproduces the inline copy).
  baseline: 0.25% (stub)
  [1] initial impl, `if (status == LIVE) {...} else {...}`          -> 77.50%
  [2] fix fn_3_C77AC: `0.35f * cos(ang)` in double (was 0.35 * cosf_kludge), `_48 = i++ >> 2`
      -> thwomp 78.90%, fn_3_C77AC 87.40 -> 91.25%
  [3] not-live branch first with early return (target `beq live`)   -> 96.75%
  [4] fn_3_C77AC decl order: A idx-before-i 96.78/91.35 (kept); B counters-before-p 96.75/91.22;
      C `i = idx = 0` 96.73/91.22
  remaining: all inside the inlined loop — p/i/idx get r25/r26/r27 vs target r26/r27/r25, and
  the pi constant takes f30 (target: f25; target order 0.0,sdbl,8,udbl -> f28..f31, pi/180/0.35 -> f25..f27).

### fn_3_C625C — MATCHED (found while decoding flameControl, which inlines it)
  baseline: 99.84%
  [1] correctness fix: star-swing guard was inverted. Target returns FALSE when
      currentStarSwing2 is 11 or 12 (`or.` then `beq` to continue); source had `!(...)`. -> 99.89%
  [2] `target.y *= -1.0f;` (was `target.y = target.y * -1.0f;`) -> 100%

### flameControl (0xDFC, mapped 0x80705464)
Signature `void flameControl(CastleFireObj* fire)`. New overlay struct CastleFireObj (visible bit
0x90 MSB, resetPending 0x99, pos 0x9C, id 0xA8, velo 0xAC, launchAngleBase u16 0xB8,
launchAngleSpread u16 0xBA, launchTimer 0xBC, state 0xBD), enum FLAME_STATE
(IDLE/FLYING/EXPLODING/ENDED), CastleAnimActor (pos at 0x34; entries 6..8 of the
hugeAnimStruct+0x2C50 table), CastleFireSpawner._0C -> `f32 rotation` (layout unchanged).
Auto-inlined helpers (called from source, MWCC inlines them): fn_3_C5304 (launch trail),
fn_3_C48D0 (ground-hit burst, called on a local copy of pos), fn_3_C444C (ball-hit burst),
fn_3_C625C (ball contact test).
Outside this file: fn_80033928 stub prototype `void(void)` -> `BOOL fn_80033928(u8 id)`
(include/Unknown/File_0x80033794.h + .c; no other callers) — it is isParticleEmitterActive.
  baseline: 0.11% (stub)
  [1] initial impl                                                    -> 98.11%
  [2] `if (launchTimer == 0) {...} else launchTimer--;` + don't cache actor ptr + swap dir/axis
      decl order + `(u32)checkCollision(...)` + fn_3_C625C returns `E(u8, BOOL)` (target tests
      the inlined result with clrlwi.; standalone fn_3_C625C unaffected, still 100%) -> 99.33%
  [3] actor table as `*(CastleAnimActor**)(hugeAnimStruct + i * 4 + 0x2C50)` -> 99.34%
  [4] local order: `hit` first / stadiumID before i -> no change (reverted)
  remaining: REGISTER_ALLOC only — hit r24 vs r25, stadiumID r26 vs r24, FPR assignment inside
  the inlined fn_3_C48D0/fn_3_C444C copies; `clrlwi r8` scheduling before allocParticleEffect.

### loadBowserCastle (0xD2C, mapped 0x807076E4; Ghidra `initBowserCastle`)
Signature `void loadBowserCastle(void** files)`; structure follows sta_c2.c's loadWarioPalace.
Two fixed objects (index 0 callback fn_3_C4068; index 1 callback fn_3_C3F70 + effect), then
(non-minigame only) thwomp / fire / star-pad placement loops, a zero-fill loop, fn_3_C82B4,
6 fn_3_C30F0 emitters, fn_3_C1974(files[ids[0]]) (auto-inlined), fn_3_B97C8(fn_3_C2974).
Supporting changes: CastleSlotPlacement._11 / CastleFireSpawner._11 -> `visible`;
CastleFireSpawner gains u16 launchAngleBase (0x14) / launchAngleSpread (0x16);
CastleGfxSceneHolder._04 -> `CastleActEffect effects[2]` (0x5C records = lbl_3_bss_9E54 / 9EB0,
same shape as sta_c2.c's PalaceActEffect); new statics lbl_3_bss_9DE1 (star-pad count) and
lbl_3_bss_9DE5 (thwomp count); externs lbl_3_data_177E0 (file-type list), lbl_3_data_10C1C
(UIRecordDescriptor[]), fn_80035750 (local extern, as sta_c2.c does).
  baseline: 0.12% (stub)
  [1] initial impl                                                    -> 82.58%
  [2] hazard-loop counters signed (target `cmpwi 0xb`/`cmpwi 0xa`) + `if (n < objectCount)` guard
      around the zero-fill loop                                       -> 90.51%
  [3] zero-fill loop uses its own counter `k = n`                     -> 90.64%
  [4] named `padAnim = idx + 1` (target keeps it live in r14)         -> 90.82%
  remaining: mostly structural — target addresses this TU's .data through one base register
  (thompFallingSpeedConstants+0xC/+0xF4/+0x1FC/+0x2D8) and .bss through lbl_3_bss_9D80+off;
  ours uses separate externs and a differently ordered .bss. Also: target passes &effect in r4
  to actRelated (so the real prototype is likely `actRelated(void* file, void* effect)`; the
  header has one arg and sta_c2.c/sta_c5.c call it that way — not changed, would touch those
  units). Frame 0x70 vs ours 0x60 (target spills &g_d_GameSettings to 0x8(r1)).

### Step 2 retries (2026-09-22)

fn_3_C4724 — MATCHED
  baseline: 99.02%
  [1] loop restructured: `if (_48) {...} else { if (_4A == 0) continue; ... } i++;` inside
      `do {...} while ((p = p->next) != NULL && i < cap);` — target has ONE shared `i++`
      reached from both arms, skipped only when _4A == 0. `continue` in a do-while jumps to the
      condition, which is why the `p = p->next` advance moved into it.  -> 100%

thwomp_smokeRelated — MATCHED
  baseline: 96.30%
  [1] `pow(2.0, (f64)fallCounter)` — target passes 2.0 in f1 and the counter in f2, i.e. the
      arguments were the other way round from the prior source (a real behavior difference, not
      just codegen)                                                    -> 96.66%
  [2] tail `if (smoke->_24 == 0) return TRUE; return FALSE;` (was `return smoke->_24 == 0;`;
      same branchless code, but scheduled after the epilogue loads like the target) -> 100%

fn_3_C30F0
  baseline: 97.61%
  [1] correctness: status guard was inverted — target returns early when gameStatus is INSIDE
      [GAME_STATUS_0x1B, GAME_STATUS_MINIGAME_READY] (`blt`/`bgt` skip past the return);
      function returns BOOL (FALSE on every exit — it's an allocParticleEffect callback);
      fn_3_C2AA0 return type -> `E(u8, BOOL)` (caller tests it with `clrlwi.`; fn_3_C2AA0's own
      score unchanged at 93.63%)                                       -> 99.26%
  remaining: `cmplwi` on returnsCurrentMode() (header says `int`; changing it touches many
  files — not done); stack-temp slot order inside the inlined fn_3_C2EDC.

fn_3_C2EDC — MATCHED
  baseline: 98.40%
  [3] `(u8)(lbl_3_rodata_2028[i] * (p->alphaByte / 255.0))` — color byte first, ratio second
      (target: fmul fD, color, ratio). Prior [1] tried `color * alpha / 255` (different grouping),
      this is the ratio-kept-intact order.                             -> 100%
fn_3_C30F0 — MATCHED
  [2] with fn_3_C2EDC fixed (it's inlined here)                        -> 99.83%
  [3] `returnsCurrentMode()` return type int -> u32 (include/Unknown/File_0x8005268c.h + .c).
      Target compares its result with `cmplwi` here AND in sta_c2.c. Repo-wide report diff:
      only changes were fn_3_C30F0 99.83 -> 100 and sta_c2::fn_3_CDFA4 99.68 -> 99.84.  -> 100%

fn_3_C48D0 — MATCHED
  baseline: 98.80%
  [5] hoist all three pos loads into temps                             -> 98.74% (reverted)
  [6] take the position BY VALUE: `void fn_3_C48D0(CastleFireballEmitter* handle, Vec pos)`.
      Target's per-particle copy is pipelined (lfs x, lfs y, stfs x, lfs z, stfs y, stfs z),
      which MWCC only does when the source can't alias p->origin — a by-value struct param is
      a private caller-made copy. Also explains flameControl's stack copy of fire->pos before
      the inlined call; flameControl now calls `fn_3_C48D0(handle, fire->pos)` (score
      unchanged 99.3352).                                               -> 100%

fn_3_C4F00 — MATCHED
  baseline: 99.22%
  [1] `p = handle->particles;` moved from the declaration to just before the loop (after the GX
      setup calls) — target loads it from the callee-saved handle reg after GXSetBlendMode. -> 100%
castleFireballMaybe — EXHAUSTED @ 91.56% (no new attempt this session: the only residual is the
  LICM hoist of &obj->anchorPos, and prior sessions already logged 6 structurally distinct tries
  [1][2][3][a][b][c]; nothing new to try without a different idea about the original source.)

fn_3_C3F70 — EXHAUSTED @ 99.35% (pure j/holder r8/r9 swap)
  [A] `u32 j` declared before `holder` in the loop scope              -> 99.03% (reverted)
  [B] `for (entry = holder->list->entries, j = 0; ...)`                -> 99.35% (no change, reverted)
  (plus prior sessions' [1]-[4] and [1]-[3])

thwomp_bounceOffSoundAndVisualFx — EXHAUSTED @ 99.58%;
bowserCastleStarPadsContaactFn — EXHAUSTED @ 98.72%  (shared idx/idx*0xC r6/r8 register pairing)
  [4] `int idx = flag != 0; idx += N;` (two statements) -> 78.66% / 93.72% (reverted)
  [5] no idx local, expression repeated in each subscript (thwomp only) -> 85.82% (reverted)
  (plus prior [1] u32 idx, [2] statement reorder, [3] operand swap)

allocParticleEffect: last parameter int -> u8 (include/Unknown/File_0x80033794.h + .c).
  The target truncates the key argument with `clrlwi r8, rX, 24` at every call site that passes a
  computed key; an explicit `(u8)` cast at the call sites instead made fn_3_C597C and
  bowserCastleRelated WORSE (98.76 -> 98.32, 94.77 -> 94.44), while the prototype change produced:
  thwomp_slamControl 96.78 -> 97.28, flameControl 99.34 -> 99.78, bowserCastleRelated 94.77 -> 95.13,
  fn_3_C597C 98.76 -> 99.24. Repo-wide report diff: no other function changed. Removed the now
  redundant `(u8)(...)` casts from flameControl/thwomp_slamControl (scores unchanged).

fn_3_C805C / stadiumObjCollision_Castle — EXHAUSTED @ 99.13% / 99.01% (twin functions; identical
  residual: cfg ptr in r28 vs target r29, `off*4` in r29 vs r28)
  [A] `off` declared before `cfg`           -> no change
  [B] `u16 off`                             -> 96.62% / 95.60% (reverted)
  [C] `cfg` scoped inside the outer loop    -> 98.58% / 98.40% (reverted)

fn_3_C24A0 — MATCHED
  baseline: 69.23%
  [1] three fixes from the target asm:
      (a) correctness: brightness = `state * 0x80 / 0xC` — magic 0x2AAAAAAB + srawi 1 is a signed
          divide by 12, not by 3 (prior source had `(u32)state * 128 / 3`);
      (b) correctness: the negate/normalize/updateVectorInArray tail runs on BOTH paths (it sits
          after the if/else in the target; prior source only ran it in the else);
      (c) `PSVECNormalize(&dir, &dir)` in place, and updateVectorInArray takes the Vec BY VALUE
          (target copies the normalized Vec to a second stack slot and passes that) — prototype
          changed in include/Unknown/File_0x800beb3c.h + .c (only caller is this function). -> 100%

fn_3_C19C8 / fn_3_C2644 (fn_3_C2644 carries a verbatim copy of fn_3_C19C8's body)
  [1] spread loop is `i = 2; while (i-- != 0) {...}` (target: counter starts at 2,
      `cmpwi 0; subi 1; bne`; prior source `for (i = 1; i >= 0; i--)`) applied to BOTH copies
      -> fn_3_C19C8 95.48 -> 99.68%, fn_3_C2644 96.01 -> 99.06%
  [2] `range * rand()` operand swap  -> no change (reverted)
  remaining: scene-ptr/i register pairing in the spreadA/spreadB stores (r27/r28), and in
  fn_3_C2644 the `(state + 1) % 0x708` temp register + a branch-polarity diff on the
  0x136/300/0x4B0 state checks. fn_3_C2644 stays `exhausted` in the table for now but has new
  information; worth one more look at that state-check branch shape.

stadiumObjRelated_Castle
  baseline: 83.06%
  [1] `f32 scale = 84.09091f; f32 base = 15.556819f; f64 transY = -0.3 * scale + base;`
      — target evaluates this at run time (fmadd from three rodata loads: -0.3 double,
      84.09091f, 15.556819f); written as a literal expression MWCC constant-folds it into one
      double, routed through locals it does not.                           -> 93.91%
  [2] `f32 y = transY;` once per object (target frsp's into f30 and reuses it), and the adds
      written `jitter + cfg->x`, `y + cfg->y`, `jitter + cfg->z` (target operand order) -> 98.86%
  remaining: same cfg / `off*4` r27-r28 pairing as fn_3_C805C/stadiumObjCollision_Castle (which
  resisted 3 attempts), plus i/j/obj register numbering.

fn_3_C2644 (re-opened with new information; was exhausted @ 96.01%)
  [3] state checks are a 3-case switch (`case 300: case 0x136: case 0x4B0: break; default: return;`)
      — target's compare tree (cmpwi 0x136 / beq / bge / cmpwi 0x12c ... cmpwi 0x4b0) is MWCC's
      switch lowering, not the prior nested-if chain                   -> 98.74%
  [4] switch on an `s16 state` local (target switches on the computed value, no reload) -> 99.60%
  remaining: `% 0x708` temp register numbering, plus the r27/r28 pairing shared with fn_3_C19C8.

fn_3_C2AA0 — 3 attempts, no gain, stays 93.63% (w/h FPR pairing f29/f31 swapped vs target)
  [1] halfW computed before halfH                     -> 93.59% (reverted)
  [2] `0.5f * w` operand order                        -> 93.59% (reverted)
  [3] no halfW/halfH locals, products inline          -> 93.30% (reverted)

bowserCastleRelated
  baseline: 95.13% (after the allocParticleEffect u8 prototype fix)
  [1] the hand-expanded particle-burst loop is fn_3_C48D0 — replaced with
      `fn_3_C48D0(handle, ((CastleFireballTarget*)obj)->anchorPos);` (by-value Vec; target does
      the lwz/stw copy of anchorPos to the stack that a by-value argument produces) -> 98.05%
  [2] readability only: `_BD`/`hasShadow`/`pos.x` writes expressed via CastleFireObj
      (state = FLAME_EXPLODING, visible = FALSE, pos.y = 10.0f — same offsets 0xBD/0x90/0xA0),
      FLAME_FLYING compare                                   -> 98.05% (unchanged, kept)
  remaining: .bss offsets (structural), castleFireballMaybe inline copy's LICM residual.

## Step 2 summary (2026-09-22)
New 100%: fn_3_C4724, thwomp_smokeRelated, fn_3_C2EDC, fn_3_C30F0, fn_3_C48D0, fn_3_C4F00, fn_3_C24A0.
Big gains: stadiumObjRelated_Castle 83.06->98.86, fn_3_C2644 96.01->99.60, fn_3_C19C8 95.48->99.68,
bowserCastleRelated 94.77->98.05, fn_3_C597C 98.76->99.24, flameControl ->99.78, thwomp_slamControl ->97.28.
Correctness fixes found (behavior differed from the binary): fn_3_C625C star-swing guard inverted,
fn_3_C30F0 status-range guard inverted, thwomp_smokeRelated pow() args swapped, fn_3_C24A0 /3 -> /12
and tail on both paths.
Cross-file prototype fixes: returnsCurrentMode -> u32, allocParticleEffect arg5 -> u8,
updateVectorInArray takes Vec by value, fn_80033928 -> BOOL(u8). Each verified with a repo-wide
report diff (no regressions anywhere).
Untouched in step 2 (no clear lead): fn_3_C82B4 (95.19), fn_3_C56E8 (99.99, prior-exhausted class),
fn_3_C3C2C (exhausted).

## Cross-stadium pass (2026-09-23)

Moved .data 0x17508-0x17898 into the unit (CastlePadTable holds pad entries + object-type list; CastleCameraSlot gets its draw callback): .data 100%, loadBowserCastle 90.82 -> 91.76. Re-declared .bss statics in reverse address order with gap bytes and 9DA0[0x40]: layout now identical to target; small gains (loadBowserCastle 91.78, fn_3_C3C2C 97.27, bowserCastleRelated 98.07). Chained _34 alloc: -0.01, not applied.

Matched 29/49; .text 97.92%.
