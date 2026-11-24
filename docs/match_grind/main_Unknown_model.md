# main/Unknown/model  [S1] -- PARTIAL (small functions only)

## Final status after first pass [S2] (unit .text 80.28%, 34/102 functions at 100%)

Every function in the unit is now drafted (no 0% rows). Rows marked pending-WEAK (< 75%) are the ones whose code shape is still far from the target
(wrong loop unrolling / missing inlines); hand them to the Opus pass first. Everything else is a near-miss (register or scheduling differences).

| function | status | % |
|---|---|---|
| fn_80011468 | pending | 85.15 |
| fn_80011570 | matched | 100.00 |
| fn_80011578 | pending-WEAK | 66.10 |
| fn_800115C8 | pending | 99.00 |
| fn_80011604 | pending | 99.00 |
| fn_80011640 | matched | 100.00 |
| fn_800116DC | pending | 99.63 |
| fn_800117CC | pending | 99.61 |
| fn_800118AC | pending | 95.83 |
| fn_8001196C | pending | 91.97 |
| fn_80011A60 | pending | 92.62 |
| fn_80011B64 | pending | 97.69 |
| fn_80011BE4 | pending | 97.96 |
| fn_80011CA8 | pending | 66.51 |
| fn_800126EC | pending | 84.18 |
| LoadModel | pending | 80.22 |
| fn_80012B90 | pending | 88.88 |
| animateModelArmsGlovesBats | pending | 92.08 |
| fn_80014204 | pending | 80.71 |
| fn_800145F8 | pending | 87.85 |
| fn_80014990 | pending | 93.09 |
| fn_80014A18 | pending | 94.58 |
| loadSomethingFromDiskAtBeginningOfAB1 | matched | 100.00 |
| loadSomethingFromDiskAtBeginningOfAB2 | matched | 100.00 |
| loadBatterModelFromDisk | matched | 100.00 |
| fn_8001500C | pending | 88.99 |
| fn_80015468 | pending | 93.57 |
| practice_loadAllGraphics | pending-WEAK | 70.08 |
| fn_80016344 | pending | 77.25 |
| fn_80016710 | pending | 75.07 |
| fn_80016B60 | pending | 75.32 |
| fn_80016F7C | pending | 89.54 |
| fn_80017098 | pending | 78.84 |
| fn_80017340 | pending | 81.76 |
| fn_8001758C | pending | 80.09 |
| fn_800177B4 | pending | 99.00 |
| fn_80017814 | pending | 92.88 |
| fn_80017D28 | pending | 88.11 |
| fn_80017DBC | pending | 90.70 |
| setupAnimationModelMemory | pending-WEAK | 63.93 |
| animationInitializationRunnerRelated | pending-WEAK | 70.75 |
| fn_800188C0 | matched | 100.00 |
| fn_800189B8 | matched | 100.00 |
| fn_800189E4 | pending | 91.88 |
| fn_80018B38 | matched | 100.00 |
| fn_80018B74 | pending | 87.89 |
| fn_80018DEC | pending | 78.59 |
| fn_800196D8 | pending | 86.33 |
| fn_80019A60 | pending | 91.69 |
| fn_80019C00 | pending | 77.59 |
| fn_8001A25C | pending | 91.69 |
| fn_8001A3FC | exhausted | 98.61 |
| challengeMapRelated | pending | 87.45 |
| fn_8001AAA4 | matched | 100.00 |
| fn_8001AAF0 | matched | 100.00 |
| fn_8001AB10 | pending | 93.93 |
| fn_8001AF98 | matched | 100.00 |
| fn_8001B200 | matched | 100.00 |
| fn_8001B214 | matched | 100.00 |
| fn_8001B224 | pending | 97.53 |
| copyAnimationStructures | matched | 100.00 |
| fn_8001B308 | pending | 93.57 |
| fn_8001B35C | pending | 83.65 |
| fn_8001B4D8 | pending-WEAK | 74.81 |
| fn_8001B5EC | pending | 89.87 |
| getAnimationCollisionOffset | matched | 100.00 |
| getAnimRelatedCoordinates | matched | 100.00 |
| QueueCharacterAnimation | matched | 100.00 |
| AnimateCharacter | matched | 100.00 |
| fn_8001BA44 | pending | 79.40 |
| fn_8001BE50 | pending | 81.43 |
| fn_8001C234 | pending | 86.23 |
| fn_8001C528 | pending | 95.62 |
| loadFielderActors | matched | 100.00 |
| loadAndAnimateCharacter | pending | 88.88 |
| loadCharacterAnimation | matched | 100.00 |
| fn_8001CA40 | matched | 100.00 |
| fn_8001CB10 | matched | 100.00 |
| initStadiumLighting | matched | 100.00 |
| fn_8001CCC8 | pending | 84.25 |
| stadiumSetupRelated | pending | 88.20 |
| fn_8001D074 | pending | 91.30 |
| applyUniformScaleToObject | matched | 100.00 |
| applyNonUniformScaleToObject | matched | 100.00 |
| baseballCTRLSetScale | matched | 100.00 |
| setHandModelAttached | matched | 100.00 |
| fn_8001D2D4 | pending | 90.92 |
| fn_8001DB74 | pending | 87.81 |
| fn_8001DD58 | matched | 100.00 |
| fn_8001DEA4 | matched | 100.00 |
| fn_8001E0D8 | pending | 89.80 |
| fn_8001E460 | matched | 100.00 |
| setNullPtrForStadiumObjs | matched | 100.00 |
| fn_8001E488 | pending | 97.30 |
| fn_8001E784 | pending | 75.96 |
| fn_8001F16C | pending | 88.91 |
| resetGameStadiumStateOnExit | pending | 94.06 |
| challengeMapMaybe | matched | 100.00 |
| somethingFileHandlingLoadingRelated | pending | 95.51 |
| fn_8001F8A4 | pending | 86.06 |
| initShortsHandleCompressedDiskReads | matched | 100.00 |
| fn_8001FDD4 | matched | 100.00 |

Weak list, with the likely cause (details in the log below): fn_8001A3FC (constant-folded loop guards), fn_800145F8 / fn_80014204 (loop unrolling of the pool init loops),
somethingFileHandlingLoadingRelated, fn_80017814 (relocation chain and zero stores), animateModelArmsGlovesBats (existing draft), fn_80011CA8 (descriptor write-back),
setupAnimationModelMemory, fn_80011578, practice_loadAllGraphics, animationInitializationRunnerRelated, fn_8001B4D8.

## fn_80012B90 [S2]
- fn_80012B90 (2800 bytes target, 2808 ours) drafted -> 88.88%: the second-generation hand-item loader (the sibling of animateModelArmsGlovesBats used by fn_80016710 for non-practice modes): phase byte lbl_803CBC04 0..8, three groups of three phases,
  each group working on one ModelOwner (slot*3 + group)*0xD4 + 0x140. Phases 0/3/6 set the owner up (texture, charId, +0xD0/+0xD1 slot bytes, +0xCD/+0xCE from obj+0x25A/+0x25B, +0xCC = 1, blocks' slots = 2g / 2g+1);
  1/2 load the hand item chosen by the owner flag (kind 2/3) and flip the flag; 4/5/7/8 load kinds 1/0/5/4 into block 1 / 0; each load waits on lbl_803C6CF8[0x715] and ends in the same finish routine
  (relocate loaded[0..3], layout/geo/texture fix-ups, fn_800238E0, ACTActorRelated, actRelated), here an inline taking the texture from lbl_803CBC08 (attachHandModelTail uses lbl_803CBC00). Phase 8
  stores the owner base into huge+0x30, resets phase / texture and returns TRUE.
  next: 8 bytes over, register differences; attachHandModelTail may be the same inline parameterised by texture (candidate to unify if both stay at their scores).

Baseline 20.35% .text, 19/102 at 100%. After [S1]: 26.45%, 31/102 at 100% (30 small unowned functions drafted, appended at the end of
src/Unknown/model.c through HA()/HA_OBJ() raw-offset macros over hugeAnimStruct).
Left alone: every function over ~150 bytes that was unowned, and all existing drafts.

| function | status | pct |
|---|---|---|
| fn_80011640, fn_8001CA40, fn_8001CB10, fn_800188C0 | matched | 100 |
| fn_800116DC 99.6, fn_800117CC 99.6, fn_80011BE4 98.0, fn_8001B224 97.5, fn_800118AC 95.8, fn_8001196C 92.0, fn_80011A60 92.6, fn_8001F16C 88.9, fn_80017D28 88.1 | pending | see left |
| fn_80011570, fn_800189B8, fn_80018B38, fn_8001AAA4, fn_8001AAF0, fn_8001B200, fn_8001B214, fn_8001FDD4 | matched | 100 |
| fn_800115C8, fn_80011604, fn_800177B4 | pending | 99.0 |
| fn_80011B64 | pending | 97.69 |
| fn_8001C528 | pending | 95.62 |
| fn_8001B308 | pending | 93.57 |
| fn_80014990 | pending | 93.09 |
| fn_8001D074 | pending | 91.30 |
| fn_80011578 | pending | 66.10 |
| fn_8001DD58 | matched | 100 |
| fn_8001DEA4 | matched | 100 |
| fn_8001AF98 | matched | 100 |
| fn_800189E4 | pending | 91.88 |
| fn_8001B35C | pending | 83.65 |
| fn_80019A60 | pending | 91.69 |
| fn_8001A25C | pending | 91.69 |
| fn_8001CCC8 | pending | 84.25 |
| fn_8001DB74 | pending | 87.81 |
| fn_8001758C | pending | 80.09 |
| fn_80017340 | pending | 81.76 |
| fn_80017DBC | pending | 90.70 |
| fn_80018B74 | pending | 87.89 |
| fn_80017098 | pending | 78.84 |
| fn_8001A3FC | exhausted | 98.61 |
| fn_8001C234 | pending | 86.23 |
| fn_8001E488 | pending | 97.30 |
| fn_80014A18 | pending | 94.58 |
| fn_800196D8 | pending | 86.33 |
| fn_8001E0D8 | pending | 89.80 |
| fn_800145F8 | pending | 39.48 |
| fn_8001F8A4 | pending | 86.06 |
| fn_80016344 | pending | 77.25 |
| fn_8001BE50 | pending | 81.43 |
| fn_80014204 | pending | 49.62 |
| fn_8001BA44 | pending | 79.40 |
| fn_80016B60 | pending | 75.32 |
| fn_80016710 | pending | 75.07 |
| fn_8001500C | pending | 88.99 |
| fn_8001AB10 | pending | 93.93 |
| fn_80015468 | pending | 93.57 |
| fn_80017814 | pending | 56.21 |
| fn_80019C00 | pending | 77.59 |
| fn_8001D2D4 | pending | 90.92 |
| fn_80018DEC | pending | 78.59 |
| fn_8001E784 | pending | 75.96 |
| fn_80011CA8 | pending | 60.01 |
| fn_80011468 | pending | 85.15 |
| fn_800126EC | pending | 84.18 |
| fn_8001B4D8 | pending | 74.81 |
| fn_80016F7C | pending | 89.54 |
| fn_8001B5EC | pending | 89.87 |

## fn_8001A3FC [O1] (692 bytes target, 692 ours; 35.90% -> 98.61% fuzzy, unit 80.28% -> 81.01%)
  baseline: 35.90% (968 bytes)
  [1] one 54-entry scan loop (no hand 3x unroll), struct view for pool/objects/flags, natural 13-loop -> 54.6..63.6% (kept the scan; the 13-loop still unrolled 6x+remainder)
  [2] 13-record loop: s32/u32/s16/u16/s8/u8 index, while/do-while, rec pointer, pointer-walk, two loops (0..9 / 9..13 and 0..9 / ;<13), <=12, !=13 -> best 78.65% (split 9 + 4); MWCC picks the
      known-count factor from the trip count (9 -> 3, 13 -> 6 + dynamic remainder), not from body size
  [3] KEY: `slot = 0; for (k = 0; k < 9; k++, slot++) {...} for (k = 0; k < 4; k++, slot++) {...}` -- a separate counter k with the stored/index variable as a
      secondary induction variable gives the target's incremental `addi r9,r9,1` 3x unroll (ctr 3) and the 4-body tail recomputed from r9 -> 88.4%, then 94.86%
  [4] scan `s32 id = tbl[i]` local (drops extsh.) -> +0.5
  [5] guard sharing the `1`: `count = 1; lbl[4] = count; for (i = count..)` 700 bytes; `lbl_803CBC34[4] = count = i = 1; for (; i < 13; i++)` + `if (count != 0)` -> 692 bytes, 95.66%
      (also `count = i = 1;` before the zero stores: same). Tried/worse: `if (lbl_803CBC34[4])` reload, `if (count)` (folded), count as u8/s8/u32, initModelCache(count) inline
      (96.06, 688), `for (i = 0; i < count; i++)` alloc loop (85..89%), ModelCacheEntry struct + pointer walk (73%)
  [6] separate `slot` variable for the record loops instead of reusing i -> 97.27% (stops NULL being a copy of the index's 0)
  [7] scan moved into a `static inline u32 maxListedFileSize(void)` -> 98.49%; its local declaration order (files, i, v, maxSize, ids of 120 perms) -> 98.60%
  tried, no gain: outer local declaration order (40 perms), scan via ids param / count param / ids++ walk, slot-init inline, 2D7F-loop inline or other counter
  variable, s8 -1 stores, chain zero stores, `maxSize` reused for count.
  remaining (register numbering only, no instruction differences): the `1` lands in r5 instead of r4 at the top; scan ptr/counter r5<->r7 swap;
  tail base/zero r3/r7 vs r4/r3. Same scan block appears in fn_80019C00 (target there also copies maxSize's 0 into the dead counter): try maxListedFileSize there.
  readability: enum-shaped bytes left as literals (lbl_803CBC34[0..4] flags/count, lbl_80118220 0x64-byte cache entries with -2 end / -1 free sentinels at +0x61).

## fn_800145F8 [O1] (920 bytes target, 924 ours; 39.48% -> 87.85% fuzzy, unit 81.01% -> 81.75%)
  baseline: 39.48% (1196 bytes)
  [1] idx as s16 (target `extsh.` test), team counter u32 t (`cmplwi r9,2`), loop index u32 i (`cmplwi r8,13` on the remainder) -> 42.6%
  [2] buffer loop reads the global back (`(u32)lbl_803CBC24 + size * (i * 2)`): matches the target's reload of lbl_803CBC24 in the remainder loop -> 43.2%
  [3] KEY: final 13-record loop kept rolled by walking a pointer (`for (i = 0, rec = HA(0); i < 13; i++, rec += 0xD4)`); `i != 13` and do-while also stay rolled
      (77.4 / 76.8) but the pointer walk scores best -> 77.7%
  [4] six-field max written as a loop over k < 6 indexing `FileTableEntry[idx + k].size` (fully unrolled late, so each step is `addi rT,rIdx16,K; lwzx`);
      explicit six steps / parenthesised offsets all CSE `base + idx*16` into `lwz off(r)` -> 85.4%
  [5] 0x20F/0x211/0x210 stored as s8 -1 (target uses a separate -1 constant from the 0xFF ones) -> size 920 but 84.7 alone; with
      `rec[0x1A0] = i * 2; rec[0x204] = i * 2 + 1` (the zero stores become copies of i's 0 as in the target) -> 85.3%
  [6] six-field loop moved into `static inline u32 maxFileSizeOfSix(u32 maxSize, s32 idx)` and maxSize declared last -> 87.08% (scan regions now identical to target)
  tried, no gain: separate a/b counters or k++/a+=2 in the buffer loop (unrolls differently, 648 bytes), record-relative pointer (HA(0x140)), Rec145 struct view,
  direct HA() stores, `i * 2 * size`, pool local vs global (pool: 920 bytes but 86.48), other counter variables for the final loop, rec declared in block,
  a/b in the final loop header (920 bytes, 86.92).
  remaining: the unrolled 6x buffer loop uses r23..r31 (stmw r23) where the target uses r27..r31 -- same instruction multiset, different scheduling/
  allocation; and the final loop copies the hugeAnimStruct base (`mr r9,r3`, the 4 extra bytes) where the target computes it straight into the pointer register.
  next: buffer-loop expression shape (the target keeps 2(i+k) values in r27..r30 across the body); try a records struct view with both buffer pointers adjacent.

## somethingFileHandlingLoadingRelated [O1] (700 bytes target, 696 ours; 42.34% -> 95.51% fuzzy, unit 81.75% -> 82.38%)
  baseline: 42.34% (656 bytes)
  [1] effect-init loop as `for (i = 0; i < count; i++)` with every field written through `hugeAnimStruct.effects[i].` (no fx local) in the target's order
      pos.x/y/z, rot.x/y/z, visible, update -> the body matches (pointer reloaded per store, stfsx) -> 68.7%
  [2] KEY: `count = hugeAnimStruct.effectCount = 30;` keeps count unfolded (target: `li r31,30` live across the calls, `mulli r4,r31,0x28`, `cmpwi r31,0`
      guard, dynamic 2x unroll with srwi./andi.). `count = 30; effectCount = count;`, `effectCount = count = 30;`, longer chains with i/off, count as
      u16/s16/u8/u32/int, an inline returning 30 all fold -> 94.63%
  [3] model-table loop addressing `modelTable + i * 0x90 + 0x34/0x44` instead of a separate `off` induction variable -> 95.43%
      (`for (i = off = 0; ...)` gives 700 bytes but 94.83; parenthesised offsets / &table[...] 91.96; PMModelEntry struct view, `0x90 * i`: no change)
  remaining: the target reloads sources[0].data/geo/tex from memory after storing them (lwz r27/r28/r30, 0x2da0..0x2da8); ours keeps the stored values
      (mr), 4 bytes and the reg assignment of the three locals. Tried, all forwarded identically: u32-word stores, a 3-iteration store loop, a
      relocateWords inline with a k loop, a PMModelSource* src for stores or loads, raw-offset loads, (void**) loads, a 1-iteration loop.
      Also the target copies the table offset induction variable from i (`mr r28,r27`), ours materialises a second `li 0`.

## fn_80014204 [O1] (1012 bytes target, 1016 ours; 49.62% -> 80.71% fuzzy, unit 82.38% -> 82.90%)
  baseline: 49.62% (1200 bytes)
  [1] fn_800145F8's recipe: k < 6 loop in an inline (signed: maxFileSizeOfSixS32), pool read back through lbl_803CBC24, s8 -1 stores for
      0x210/0x211/0x20F, `i * 2` / `i * 2 + 1` -> 38.3% alone (1352 bytes): the final loop unrolled 8x instead of the target's 4x
  [2] final loop as a pointer walk (`rec += 0xD4`) -> dynamic 4x unroll as in the target -> 75.6%
  [3] KEY for the scan: the helper's index parameter as `int` (s32 is `long` here) -> `slwi` once + `addi K; lwzx` per step like the target;
      with s32/u32 the inner (idx + k) is recomputed or strength-reduced into a +96 induction variable -> 79.9% (s16/u16 idx 79.8/80.0 but 1020/1016)
      tried, worse: `(base + idx)[k]`, byte-offset forms (988/992 bytes, idx*16 strength-reduced), `int i` (78.3)
  [4] final loop with explicit a/b counters in the for header (`a = 0, b = 1 ... a += 2, b += 2`) -> 80.33%
  tried, no gain: local declaration order (30 perms), helper parameter order/types, total as int or inlined `count * 3`, `(u32)pool` in the buffer loop
      (1012 bytes but 78.19), `i = 0` outside the pointer-walk loop, k++/a += 2 counter in the buffer loop (changes the unroll, 804 bytes).
  remaining: same as fn_800145F8 -- the 8x-unrolled buffer loop uses r19..r31 where the target uses r24..r31 (same instructions), so total
      ends up in r24 instead of r7; and the final loop copies the hugeAnimStruct base (`mr`) instead of computing it into the pointer register.
      The scan's maxSize/fileBase/pointer registers are rotated (r4/r7/r5 vs r7/r5/r4).

## fn_80017814 [O1] (1300 bytes target, 1300 ours; 56.21% -> 92.88% fuzzy, unit 82.90% -> 83.70%)
  baseline: 56.21% (1660 bytes)
  [1] KEY: the target calls initShortsHandleCompressedDiskReads (bl); ours inlined it (-inline auto, defined earlier in the file). Moved it and its three
      swapShortPair* static inlines below fn_80017814, matching the target's address order (it sits near the end of the unit) -> 86.51%, 1284 bytes.
      It is its only caller in the file and it stays 100%.
  [2] bone checks on an s32 `bone` (target: `addis r0,rX,0; cmplwi r0,0xffff`) with the flag index cast back `(u16)bone` (clrlslwi), a separate u16
      boneId for the memset loop, and PARAGOOMBA falling through into the MONTY/GOOMBA initSpecialHandBones case -> 89.33%
  [3] the +0x168 check and the three callDSInsertListObject arguments read into `bone` first (target loads the u16 before the actor) -> 91.56%
  [4] `if (layout != 0) { ...four calls... } else { return; }` reproduces the target's `b` + dead `b exit` pair -> 92.34%, size exact
  [5] local declaration order layout, geo, skn, tex (24 perms tried) -> 92.51% (local scorer; report 92.88%)
  tried, no gain: ternary for the anim argument, an s8 local for rec[0x255], `mode >= 9` polarity, header/entry declaration order or statement
      order, array-index forms for the bone table, u16 i (worse), `(u16)-1` / `(s16)bone != -1` compares.
  remaining (registers/scheduling only): prologue order (target loads rec+8 before computing entry), layout loaded into r3 then moved to r26,
      rec[0x255] loaded before the anim branch in ours, and the memset loop's i*4 counter is a fresh `li 0` instead of a copy of i.
  note: fn_80017DBC (90.70%) has the same bone block; the s32 bone / (u16) index form may help it.

## animateModelArmsGlovesBats [O1] (2948 bytes target, 2952 ours; 57.33% -> 92.08% fuzzy, unit 83.70% -> 85.41%)
  baseline: 57.33% (2716 bytes)
  [1] rewrite on the target's shape: u8 record counters (clrlwi/cmplwi 13), the bone link as an inline (linkHandAttachBone) with an int `bone`
      (addis compare, 0xFFFF as lis/subi), the finish routine as an inline taking the texture read before the load request (attachHandModel(tex),
      same shape as fn_80012B90's finishHandItemLoad), the two load phases inside `for (;;)` (phase 1 success loops back to the top), the
      category test as `(part < 9 && r211 < 9) || (part >= 9 && r211 >= 9)` re-reading actor+0x254, PARAGOOMBA-style shared stores -> 78.8%
  [2] linkHandAttachBone: the target loops over obj->actors (counter 0, pointer -4, `while (j-- != 0)`) with the s16 table test inside; a
      `j = 0; do { ... } while (j-- != 0);` keeps that loop (for (j = 0; j >= 0; j--) folds away; s8/s16 j keep it but 84.2) -> 86.3%
  [3] parts walk as `p = arr + count; do { cand = *--p; count--; ... } while (count != 0)` (lwzu -4, no guard) -> 88.6%
  [4] `match = selSet == lowPart` assigned per phase (CLZ idiom instead of compare/branch) and the 0x715 test through (s8*) (cmpwi) -> 89.5%
  [5] attachHandModel with a single exit (`ret = TRUE/FALSE; return ret;`) so the result is a register tested with `clrlwi.` -> 90.8%
  [6] the first-pass match loop indexes `((u8(*)[0xD4])hugeAnimStruct)[i]` (rec) so the matched-record store recomputes the base -> 91.0%
  [7] `sel` as s32 (no clrlwi of the 0x25A/0x25B byte) -> 91.96% (local scorer; report 92.08%)
  tried, no gain: a result variable without the single-exit inline (merged away), RECORD(i) everywhere instead of rec (89.7), the matched
      record through the array form only in the first loop (90.7), u8 match / u8 selSet (91.4), an entry local or ModelEntry90 struct for
      the parts lookup (no change).
  remaining: the parts lookup is `addi 0x34; lwzx` in ours vs `add; lwz 0x34` in the target; the free-slot and replacement stores use the
      kept record pointer where the target recomputes hugeAnimStruct + i*0xD4; `match` is u8 in the target (extrwi 8,19) and computed
      once before the loop for phase 1; register numbering in the first-pass loop.
  not done: unifying attachHandModel with fn_80012B90's finishHandItemLoad -- the two sit under different hugeAnimStruct views (raw byte
      array here, the full struct there) and lbl_803CB7C4/lbl_803716B8 views; the bodies are now the same shape, so a shared inline is
      possible once the views are unified.

## fn_80011CA8 [O1] (2628 bytes target, 2156 ours; 60.01% -> 66.51% fuzzy, unit 85.41% -> 85.70%)
  baseline: 60.01% (2116 bytes)
  [1] copyBankDesc made `static inline` (the target inlines all twelve copies: scalar fields + two memcpy each) -> part of the gain
  [2] linkHandPartNode rewritten like animateModelArmsGlovesBats' linkHandAttachBone: int bone (addis compare), s16 table value tested inside
      a `j = 0; do { ... } while (j-- != 0);` loop over cur->actors, the parts walk as `p = nodes + count; do { *--p; count--; } while (count)`
      -> both link blocks now match the target's shape. Together with [1]: 63.16% local, 66.51% report.
  tried, worse: descriptor pointers in the target's owner form ((slot * 3 + k / 2) * 0xD4 + 0x140, as fn_80012B90 does) for descriptors 2..5
      everywhere (44.5%, 2492 bytes), only in the write-back (52.9%), only as copy-in sources (54.0%), and with `rec` dropped in favour of
      HA(slot * 0x27C) at every use (43.9% / 52.4%, 2532 / 2436 bytes). They get closer in size but misalign the copy-in sequence.
  remaining: 472 bytes short. The target recomputes hugeAnimStruct + slot*0x27C for every copy-in and keeps the descriptor memcpy pointers
      (desc+0x10 / desc+0x34) for descriptors 2..5 live in r18..r25, computed in the owner form; the write-back switch then stores through 28
      precomputed field addresses held on the stack (0x270..0x2C8). Ours folds everything into constant offsets from one record pointer.
      Next idea: give the copy-in and the write-back the same owner-form descriptor pointer expressions but keep the scalar reads through
      a separately recomputed record base (e.g. a typed records view vs. byte arithmetic), so only the memcpy addresses are shared.

## Findings
- [O1] File order decides auto-inlining here (`-inline auto` without deferred): a function the target calls but ours inlines is defined too
  early in model.c. Moving it below its caller (to its address-order spot) stops the inlining without touching its own codegen.
- [O1] Unfolded-constant lever (seen twice now): assigning a constant through a chain into a struct/array field, e.g. `count = field = 30;` or
  `field = count = i = 1;`, keeps MWCC from constant-propagating `count`, so guards, multiplies and loop bounds use the register as in the target.
  Which chain order works differs per function; try every order.
- [O1] Unroll shape lever: a loop whose stored/index value is a secondary induction variable (`for (k = 0; k < N; k++, slot++)`) unrolls with
  incremental `addi rX,rX,1` per copy, and a constant-count follow-on loop from that runtime value comes out as straight copies off a mulli-computed base.
  A plain `for (i = 0; i < N; i++)` gives parallel `addi rA,rI,1 / rI,2` copies instead. Likely relevant to fn_800145F8 / fn_80014204 / fn_80019C00.
- fn_80011578 loops s8 i over 13 object slots calling the bounds-checked `clearObjectField5C` (same inline as fn_800115C8); loop form differs.
- Object slot record at hugeAnimStruct+0x2C50 (+i*4); obj+0x2C / +0x30 hold per-object effect/part records (fn_80011B64 resets them);
  obj+0x255 is the actor slot (s8) indexing hugeAnimStruct.actorTable[slot*0x90]; node+0x98 bit 2 and node+0x68 are toggled by
  fn_8001D074 / fn_8001B308. fn_8001C528 resets 13 records of 0x27C bytes (+0xC64..+0xE73).
- hugeAnimStruct is a typedef + #define view per former unit; the appended block uses the base HugeAnimStruct (after the last #undef).
- Still unowned (0%): fn_800116DC.. (everything in the earlier listing except the 17 above); biggest: fn_80012B90 (2800),
  fn_80011CA8 (2628), fn_8001E784 (2536), fn_80018DEC (2284), fn_8001D2D4 (2208).

## Log
- [S2] fn_80011468 (264 bytes, jump table) drafted: loops 13 object slots, switch on charId (CHAR_ID_*) sets/clears the actor entry
  flag at actor+0x99 or calls fn_8004B6EC / updateSpecialBatAttach / fn_8005240C / processCharacterStateBasedOnGameMode -> 85.15% (size exact)
  next: logic believed right; remaining diff is likely register/scheduling in the switch prologue; not ground.
- [S2] fn_800126EC (268 bytes) drafted: finishes loading one model slot block (block, texPalette, partIndex[4]): relocated parts, actor layout/geo header
  fixups, palette pointers, fn_800238E0, optional ACT parts, then block->_04 -> 84.18% (size exact). It is the body LoadModel inlines in part.
  next: register/schedule; not ground.
- [S2] fn_80011468: CHAR_ID mapping confirmed (jump table based at CHAR_ID_YOSHI); processCharacterStateBasedOnGameMode now comes from
  Unknown/File_0x8004b7f4.h. fn_8004B6EC, updateSpecialBatAttach and fn_8005240C have no owning header, so local externs remain.
- [S2] fn_8001B4D8 (276 bytes) drafted: for object index with apply set and obj+0x268 clear, transforms the actor's root offset vector, records the root bone
  in actor node +0x98/+0x9A, adds the vector to obj position (+0x34..) and sets obj+0x268 -> 74.81% (size exact)
  next: inline getRootBone double null-check and Vec copy ordering likely differ; not ground.
- [S2] fn_80016F7C (284 bytes) drafted: resumable loop over the 4 object records at huge+0xC04 (stride 0x27C) via fn_80016B60 (counter byte +0x2D88,
  init flag +0x2D8E); in GAME_TYPE_TOY_FIELD it copies record words 4..10 into record i+4. Returns FALSE as soon as fn_80016B60 does -> 89.54% (size exact)
  next: loop/inline shape; the +0x2D88 reloads are volatile-like in the asm.
- [S2] fn_8001B5EC (316 bytes) drafted: sibling of fn_8001B4D8; transforms the actor root vector (result unused) and stores bone ids into actor node +0x98/+0x9A:
  mode 0 -> root bone (+0x162) and partBones[4] (+0x16A); mode != 0 -> root bone for both -> 89.87% (size exact)
  next: the two near-identical branches are written out in full; the original probably shares an inline.
- [S2] fn_8001DD58 (332 bytes) drafted -> 100.00% (matched). Variadic variant of ACTRender (src/C3/actor/act.c) without the fn_800B2D5C call, gated on
  actor->unk98 bit (group*3) instead of mask 9. readability pass: done (group index kept as int, no enum evidence).
- [S2] fn_800189E4 (340 bytes) drafted: takes the max of (lbl_803CB790 record +0xF4 & 0x0FFFFFFF) over the 54 character records (stride 0x130), rounds up to 32,
  allocates 4x that from heap 0x20, and carves four buffers (+size each) into hugeAnimStruct 0x2C88/0x2D10/0x2D24/0x2D38 and 0x2CFC; clears four record fields (+0x24 of records 0..3)
  -> 91.88% (size exact)
  next: the original loop is a 6x unroll of 9 records with a spare counter (r5 += 8); try a u8/s8 loop variable or nested 6x9 loop. Not ground.
- [S2] fn_8001B35C (380 bytes) drafted: height-step counter. mode 0/1/2 selects part bone 3/2/1 (else 1); transforms that bone, diff = bone.y - obj.y,
  then counts 0.5-wide steps: diff in [-30,0) -> positive count starting at 1; diff in [0.5,30) -> negative count; else 0. Returns 0 for a missing object
  -> 83.65% (size exact)
  next: float branch layout (the asm tests with cror/bne pairs and has a dead obj==NULL branch from a double-inlined null check); return type may be s16 (callers declare s16).
- [S2] fn_80019A60 (416 bytes) drafted from stadiumSetupRelated's body: registers fn_800196D8 as a drawing task (clears task+0x14 byte and the
  task child's state), then loads the 4 stadium lights for inputParams[g_d_GameSettings._54] (no StadiumID/minigame derivation), normalises light 0's direction,
  applies ambient, allocates/initialises the 4 LIT lights and attaches them to every prop entry via fn_800BD548 -> 72.40% (size exact)
  next: the first light loop in the asm steps source (+0xA) and dest (+0x10) pointers separately; try pointer-walking or a different inline split. Not ground.
- [S2] fn_8001A25C (416 bytes) drafted: twin of fn_80019A60 registering fn_80019C00 as the drawing task instead of fn_800196D8 -> 91.69%.
  Correction: fn_80019A60 never normalises light 0 / calls updateVectorInArray (that was stadiumSetupRelated only); removing it took fn_80019A60 72.40 -> 91.69%.
  next (both): first light loop pointer stepping (+0xA src / +0x10 dst) and prop-entry loop shape; likely one shared inline in the original.
- [S2] fn_8001CCC8 (428 bytes) drafted: stadiumSetupRelated without the prop-entry loop (sets _3085 = 4, derives the stadium, loads/normalises lights,
  ambient, 4 LIT lights) -> 84.25%. Ours is 416 bytes vs target 428.
  next: asm reloads g_d_GameSettings / lbl_80367318 addresses separately (no CSE); likely a separate inline for the stadium derivation / light load.
- [S2] SIZE CHECK (ours vs target, via objdiff diff right/left symbol sizes) -- earlier "size exact" claims were wrong for several:
  fn_80011468 268/264, fn_800126EC 268/268 ok, fn_8001B4D8 296/276, fn_80016F7C 276/284, fn_8001B5EC 292/316, fn_800189E4 348/340,
  fn_8001B35C 376/380, fn_8001DD58 332/332 ok, fn_80019A60 404/416, fn_8001A25C 404/416, stadiumSetupRelated 508/512 (pre-existing).
  Per-function % can be read as logic-correct only where the instruction streams line up; mismatched sizes mean missing/extra instructions.
- [S2] fn_8001DB74 (484 bytes target, 480 ours) drafted: per-frame flush of pending actor-entry state for each object in an ActorObjectTable-sized list:
  applies pending animation/frame/speed/bone param, Set_FUN_800b2b6c, optional fn_800BDA24, then for every scissor/view mode builds camera*translate(obj pos)
  and stores the result of fn_800B3C04 into the 2-bit field (mode*3) of actor->unk98 (or forces 1 when HA(0x307A)==5); finally clears the pending flags -> 87.81%
  next: the loop recomputes (u16)mode into r24/r25 around returnScissorMode(); try s32/u16 loop var variants and the entry pointer arithmetic.
- [S2] fn_8001758C (552 bytes) drafted: two-state loader for a model record (huge+0xC04+b*0x27C). State 0: record the request (charId c, team d, roster e, mode g, h),
  then either memcpy a cached buffer (huge+0x2D54 / 0x2D3C blocks) or start an ARAMTransfer (skipping it when fn_8002204C finds the file loaded), state -> 1.
  State 1 (or a cache hit): once lbl_803716B8[0x1E8]==0 and lbl_803C6CF8[0x715]==1, runs fn_80017814(record, slot, mode, fn_8001FDD4) and returns TRUE -> 80.09%
  next: switch layout / goto-style joins; mode flag stored via (g==9) cntlzw idiom.
- [S2] fn_80017814's real signature is (u8* record, s32 slot, s32 mode, void (*callback)(u8*)); the old one-arg prototype was removed. fn_80017D28 still calls it with
  one argument via a cast (the original leaves r4-r6 as set up earlier; passing real arguments dropped fn_80017D28 from 88.1% to 64.05%). Opus: fix when drafting fn_80017814.
- [S2] fn_8001DEA4 (564 bytes) drafted -> 100% in the report (diff tool shows 99.89%, sizes 564/564). Runs entry->callback, then switch on entry->drawArgCount (0-8)
  forwarding that many entry->drawArgs words to fn_8001DD58(actor, group, camera, count, ...). readability pass: done (fields already named in ActorObjectEntry).
- [S2] added a source comment at the fn_80017D28 -> fn_80017814 cast call explaining the one-argument cast.
- [S2] fn_80017340 (588 bytes target, 592 ours) drafted: batch-slot allocator for a model record's anim bank. If the loaded flag (huge+0x2D8D) is clear it scans the
  4 cached character ids (huge+0x2D89..) against the 4 object slots 9..12; a hit reuses the cached buffer (huge+0x2CB0+j*4) and returns TRUE, otherwise unused
  cache slots are freed (-1), the first free one takes the record's charId, an ARAMTransfer of the character's anim file (+0xB in practice mode, else +3) is started
  and the flag set (returns FALSE). When the flag is set it calls ANIMGet(record+0x14) once lbl_803C6CF8[0x715]==1 -> 81.76%
  next: the asm's inner loop does not hoist the invariant objects[9+i] load (left in the inner loop); the first-free search is the unrolled 4-step compare chain.
- [S2] fn_80017DBC (616 bytes target, 608 ours) drafted: model-setup tail for one object (obj, slot): inserts three DS list objects (+0x188/+0x194/+0x1AA), sets up bones
  (+0x168 gets fn_800B2B54(...,13); +0x168/+0x166/+0x164/+0x1BE also get fn_800B2BA8 plus bone[0x136]=1; +0x1AA only fn_800B2BA8), fn_800B2C08(actor, +0x16A), then a
  charId switch (jump table at 0x800EED00 read directly: DK, MAGIKOOPAx4, BOWSERJR, PARATROOPAx2, PETEY, PARAGOOMBA, MONTY/GOOMBA, BOO/KINGBOO, SHYGUYx5) dispatching
  to the per-character setup functions -> 90.70%
  next: 8 bytes short; the per-bone guard blocks probably come from an inline helper (same fn_800B2BA8 + flag pattern x4).
- [S2] fn_8001AF98 (616 bytes, ours 616) drafted -> 100% in the report. Shadow-pass renderer: bails (DrawShadows(FALSE)) unless huge+0x3087 is set and fn_8003A538()==0;
  saves projection/viewport/scissor, picks the light direction (toy-field mode: normalised eye-target with inverted/scaled y -> updateVectorInArray; else fn_800BD1E8(NULL)),
  builds a ShadowCamera from camera 0, runs fn_800BE09C / fn_800BF058(fn_8001AB10) / fn_800BDFE0, the optional huge+0x308C hook and fn_8003A4C8 or fn_800BDEA0, then runs and clears
  lbl_803CBBF4 and restores GX state. Needed #include "Unknown/File_0x80052734.h" (returnFloatFromModeIndex was implicitly int); fn_8001DB74 unchanged at 87.81%.
  Quirk: the zero test must be written `mag = PSVECMag(&v); if (!(mag == lbl_803CC4B8))` to get the target's fcmpu operand order. readability pass: done (GAME_TYPE_TOY_FIELD, TRUE/FALSE).
- [S2] fn_80018B74 (632 bytes target, 604 ours) drafted: sibling of fn_800189E4 for the character-record buffer pool. Scans the 54 records (stride 0x130) for five maxima
  (fields +0x44/+0xD4 by minigame mode, +0xC4/+0xE4 by toy-field mode, +0x124, +0x24/+0x94 by minigame mode, +0x104; all & 0x0FFFFFFF), rounds each to 32, stores the sizes at
  huge+0x2C90..0x2CA4 and the total at +0x2D60, allocates it, then carves 4 sets of five buffers (stride 0x14 at +0x2CEC; the D buffer is shared from set 0) while zeroing six fields of
  each of the 4 object records, and sets huge s16 +0x2D68 = -1 -> 87.89%
  next: 28 bytes short; the asm unrolls the carve loop 2x with a k==0 compare, and the max scan keeps `mode` compares inside the loop; try an s32 mode / manual unroll.
- [S2] fn_80017098 (680 bytes target, 648 ours) drafted: request a character model load for (team, idx) into object slot d. With f >= 0 it just queues the loader task (fn_800177B4)
  for slot d. Otherwise it first looks for an already-loaded matching record among the 13 (charId/roster bytes, team, c, e): on a hit it re-registers it into object slot d
  (clearing its old object-table entry) and returns TRUE. On a miss it queues the loader task, picks the first free slot (<0 in huge+0x2D6A..; 9-12 only when d >= 9, else 0-12) and fills the
  task bytes (+0x14..+0x1D), marks the slot busy and returns FALSE -> 78.84%
  next: 32 bytes short; the match test (flag then combined test) and the two free-slot searches (the d >= 9 one is unrolled in the asm) probably differ in shape; task writes may go through a struct.
- [S2] fn_8001A3FC (692 bytes target, 968 ours -- WEAK DRAFT, logic believed right, shape wrong) drafted: model/animation system init for a mode. Calls animationInitializationRunnerRelated(mode), clears
  lbl_803CBC34[0..3] and sets [4]=1; sets lbl_80118220[i*0x64+0x61] = -2 for i=1..12; sizes a pool as the max (& 0x0FFFFFFF) of the +4 field of the lbl_803CB794 entries
  named by lbl_800EEB18[0..53] (>= 0), allocates it (32-aligned, heap 0x20) into lbl_80118220[0] / lbl_803CBC30 and sets bytes 0x60/0x61 = 0xFF; then fn_800145F8(mode),
  huge+0x13C = fn_80023AA4(), fn_80018DEC(mode), initActorArray(13); for the 13 records sets rec+0x255 = k, rec+0x257 = -1, objects[k] = NULL, huge[0x2D6A+k] = -1;
  huge[0x2D7F..0x2D87] and [0x2D89..0x2D8C] = -1 -> 35.90%
  next: the target keeps the constant `1` (flags[4]) in r4 as a loop-guard/flag (cmpwi r4,0xd ; cmpwi r4,0) and uses only r31 plus scratch registers (stwu -0x10 frame, no stmw), with the
  13-record loop unrolled 3x3+4 and the 9-byte clear unrolled behind a `cmpwi r7,9` guard. Mine allocates many more registers (stmw r24). The max scan wants to be one inline over the three
  entries per step (lhau stride 2). Try making the guard variables the same object as flags[4] (e.g. a local u8 counter stored to flags[4]) and a single inline helper for the max step.
- [S2] fn_8001C234 (756 bytes target, 804 ours) drafted: per-frame animation state machine over the 13 objects; writes a bitmask of objects whose animation changed into *changedMask.
  Per live object (+0x25D): ticks the frame counter +0x6A (cap 600), derives the current animation step (+0x68) from the actor's bone anim time / +0x4C (or the queued +0x70),
  and when the animation finished (state +0x25E == 1, or state 2 with step 0 and counter > 1, or no current anim +0x62 == -1) promotes the queued anim (+0x64 -> +0x62 -> +0x60; its
  parameter bytes +0x260.. shift down to +0x25F..), starts it through fn_8001BE50 (fn_8001BA44 when gs[0x11] && gs[6] == 2), and promotes a second queued anim (+0x66) if present;
  otherwise it reads fn_800B4C40 for the playing animation. Finally (unless highLevelSimulationFlag) fn_8004B208(obj, anim, stadiumCollisionRelated(gs[9], obj[0x275]), time) -> 86.23%
  next: 48 bytes over; the tail where the promotion `continue`s past the collision call and the two f31 assignments (fn_800B4C40 result vs int-to-float of +0x6C vs lbl_803CC4B8) are likely
  structured as a single `time` variable with different control flow; try if/else restructure or goto-free join.
- [S2] fn_8001E488 (764 bytes, ours 764) drafted -> 97.30%. Overlay pass: sets GX Z/cull/blend state, then for every actor-table entry that has an object, an actor and applyControl set,
  builds a per-object frustum (offsets from the object's x/y divided by lbl_803CC514 plus lbl_803CC518..528), GXSetProjection, runs the entry callback and draws it with the same
  drawArgCount switch as fn_8001DEA4 (group 0, camera 0's view matrix) -- the original has that body inlined.
  next: pure register allocation: target walks hugeAnimStruct+0x2C50 via r30 (mr r30,r31) with separate counters r27/r29, ours uses an addi r27 pointer; try different loop-variable declarations.
- [S2] note for fn_8001E488: the nine-case drawArgCount switch was probably a shared static inline in the original (used by both fn_8001DEA4 and fn_8001E488); try it
  only if fn_8001DEA4 stays at 100%.
- [S2] fn_80014A18 (820 bytes target, 808 ours) drafted: three-state loader (huge+0x2D8E) for the nine fielder-type animation banks. State 0 resets the cache table (huge+0x2D7F x9 = -1).
  State 1 walks objects 0..8 matching each object's charId (+0x252) against the cache; hits take the cached buffer (huge+0x2CC0+j*4) into obj+0x24, the first miss moves to state 2 and
  returns FALSE (all hit: returns TRUE). State 2 picks a free cache slot for the object's record, starts an ARAMTransfer (file charId*0x13+4, or +0x11 when huge+0x2D7C is set) and then
  waits for lbl_803C6CF8[0x715] == 1 before ANIMGet and going back to state 1. The `team` parameter is unused in the asm -> 94.58%
  next: 12 bytes short; the free-slot search is a fully unrolled compare chain in the asm and the invariant objects[i] reload sits inside the inner loop (as in fn_80017340).
- [S2] fn_800196D8 (904 bytes target, 924 ours) drafted: the drawing task registered by fn_80019A60/fn_8001A25C; byte +0x14 of the task is its state.
  0: spawns the fn_800188C0 task (its +0x14/+0x16 cleared, +0x17 = 0xFF) and sets huge+0x307B; 1: waits for huge+0x307B to clear; 2: light direction = normalised -lbl_80367318[0].pos
  (dolsqrtf2, same as challengeMapRelated's case 6), shadows on (fn_8003A540(0), huge 0x3086/0x3087, DrawShadows(1), updateVectorInArray, fn_800BF048/BF058 callbacks), relocates the 80
  offsets at huge+0x2C84 by their own base, fn_8001F8A4(); default (>=3 or negative): challengeMapMaybe(), huge+0x2D7D/0x307C = 1, removeCurrentDrawingItem() -> 86.33%
  Note: this is the same body as challengeMapRelated's state 6 (that one is also pending); the two share a lot and may be one inline/macro in the original.
  next: 20 bytes over; check the relocation loop (target unrolls 8 words with huge+0x2C84 reloaded for every store) and the sqrt inline placement.
- [S2] fn_8001E0D8 (904 bytes target, 896 ours) drafted: lit-object draw pass over an ActorObjectTable-sized object list (table, group, camera). Sets GX Z/cull/blend, then per object
  (skipping obj[0x25D] == 2 and entries without actor/applyControl): switches the ambient light when obj[0x277] changes (0xFF restores the stadium ambient, 0 skips the object, else
  ambient alpha = level; adjustLightingParams), builds camera*translate(obj pos), fn_800B9948(obj+0x5C callback), lbl_803CBC18 = obj, runs the entry callback and the same drawArgCount
  switch as fn_8001DEA4 / fn_8001E488 with the given group; finishes with fn_800B993C() -> 89.80%
  next: 8 bytes short, register allocation around the lightLevel/ambient locals; the shared nine-case switch inline (see fn_8001E488 note) applies here too.
- [S2] fn_800145F8 (920 bytes target, 1196 ours -- WEAK DRAFT, logic believed right, loops unrolled differently) drafted: sizes and carves the per-character model buffer pool. Takes the max
  (& 0x0FFFFFFF) of six consecutive 16-byte file-entry fields (+4,+0x14,..,+0x54) of lbl_803CB7A8 for the files lbl_800EEAAC[charId] of every roster entry (mode 0: 2 teams x 9)
  or of all 54 characters (mode != 0), rounds to 32, allocates 26 x that (heap 0x20) into lbl_803CBC24, gives each of the 13 0xD4-byte records at huge+0 two buffers (+0x140 = pool+size*2k,
  +0x1A4 = pool+size*(2k+1)) and initialises record bytes +0x1A0 = 2k, +0x204 = 2k+1, +0x20C = 0, +0x208 = 0, +0x20D..+0x211 = 0xFF -> 39.48%
  next: the extra ~280 bytes are loop unrolling: the target runs the final 13-record init loop rolled (ctr 13, a += 2 / b += 2 induction variables) and unrolls only the first buffer-assign
  loop (6x2 + remainder); mine unrolls the init loop. Try pointer-walking the record, or keeping the 13-loop body larger/opaque. The six-field max is written as six explicit steps (matches the asm).
- [S2] fn_8001F8A4 (936 bytes target, 920 ours) drafted: the "overlay/ball actor" model setup run from fn_800196D8 state 2. Walks the 24 (layout, geo, tex) triples of the offset table at huge+0x2C84
  (LoadActorLayout, convertGeometryAndSknHeader, haveActLayoutPointToGeoHeader, convertTextureHeader unless set 11, which uses table word 0x20; UpdateTexturePalettePointers), sets up the two
  special actors at huge+0x309C / +0x30F8 (adjustInternalPointers, actRelated, actorRelated), creates a 25-entry ActorObjectTable at huge+0x64 filled via animateBallRelated using
  lbl_800EEA58[i] to pick the layout (sets >= 16 also get the shared anim bank, are started with ACTSetAnimation and flagged pending), lights/translation/rotation per entry, ACTActorRelated for
  entries 5 and 6, and finally allocates and zeroes a 25 x 0x28 byte block at huge+0x2D90 -> 86.06%
  next: 16 bytes short; the final zeroing loop reloads huge+0x2D90 for every store in the asm (kept), the entry accesses probably want a cached entry pointer / different casts; lbl_800EEA58
  is a u8[25] table (declared extern here, owned by this unit's data).
- [S2] correction for fn_8001F8A4: symbols.txt gives lbl_800EEA58 size 0x54 (84 bytes, data:byte), not 25; the loop only reads 25 entries, so the table either holds more than that
  or is shaped differently. symbols.txt left unchanged; the draft declares it `extern u8 lbl_800EEA58[]`.
- [S2] fn_80016344 (972 bytes target, 928 ours) drafted: (charId, slot, c, d) model-load state machine on huge+0x2D77 (6 -> return 1, 1 -> return 0, 0 -> kicks fn_80017098(0, d, 1, slot, 1, charId)).
  2: bind object slot to its record and set +0x25A/+0x25B = c; 3: start (ARAMTransfer/fn_80021BBC, bank chosen by slot: 12 -> +0x11, practice mode or <9 -> fn_80021BBC, >=9 -> +0x10) then wait for
  lbl_803C6CF8[0x715] == 1 and ANIMGet; 4: attach the part effect via lbl_80118220 (fn_80021ADC once, then actRelated) or clear rec+0x2C when the character has no part (lbl_800EEB18 == -1 or part+0x10 == 0);
  5: animateModelArmsGlovesBats, then state 0 and return 1 -> 74.07%
  next: 44 bytes short. A goto-based variant for the "no part" join (jumping into the else) scored 77.25% at 932 bytes; I kept the goto-free form. The two "ready" flag blocks (slot 12 and others) are duplicated
  in the asm and may come from one inline taking the transfer as a callback.
- [S2] fn_80016344: switched to the goto ("no part" join) variant -> 77.25% (972 target / 932 ours); the goto-free form scored 74.07%.
- [S2] fn_8001BE50 (996 bytes target, 948 ours) drafted: (index, anim, boneParam, mode, frame, attach, speedDivisor) starts an animation on an object's actor entry. Blend time = 1/speedDivisor (0 if none).
  Sets bone state through fn_800B2B54 (13 normally; 1 + fn_800B2B4C(lbl_803CC504) when obj[0x26C] != 0). Maps the global anim id to (bank kind, sequence): <45 kind 2, <61 kind 1 (-45), <63 kind 4 (-61),
  <75 kind 3 (-63), <105 kind 0 (-75), else kind 5 (-105); bails out if the sequence is out of range for that bank, otherwise loads it into the entry (anim/seqNum/frame 0/pending flags/blendTime),
  feeds actorRelated for the two effect records, sets boneParam 3 or 2, frame = frame * obj+0x4C, then inlines fn_8001B5EC(index, mode) and fn_8001B308(index, attach) and stores obj[0x268] = mode -> 81.43%
  next: 48 bytes short; the anim-id range chain is a straight if/else ladder in the asm (r26/r27 stay uninitialised for negative ids -- kept), and fn_8001B5EC / fn_8001B308 are probably real inlines
  (calls to the already-drafted functions inlined at their original definitions).
- [S2] fn_80014204 (1012 bytes target, 1200 ours -- WEAK DRAFT, logic believed right) drafted: sibling of fn_800145F8 taking a `count`: same six-field max (signed compare here, s32) over the 54 entries
  of lbl_800EEAAC, but the file base is a running index (+6 per non-negative entry), not lbl_800EEAAC's value (fn_800145F8 uses the value -- the two really differ in the asm). Allocates
  count * size * 6 into lbl_803CBC24, then assigns two buffers (+0x140/+0x1A4) and initialises bytes/words (+0x1A0 = 2i, +0x204 = 2i+1, 0x20C/0x208 = 0, 0x20D..0x211 = -1/0xFF) for count*3 records
  -> 49.62%
  next: 188 bytes over: the target unrolls the buffer-assign loop 8x and the init loop 4x with a remainder loop (runtime trip count count*3); mine unrolls differently. Same structure problem as
  fn_800145F8; whichever of the two gets matched first should transfer.
- [S2] fn_8001BA44 (1036 bytes target, 964 ours) drafted: the alternate animation starter (same signature and structure as fn_8001BE50, called from fn_8001C234 when gs[0x11] && gs[6] == 2).
  Differences from fn_8001BE50: a negative anim id clears the entry instead (anim NULL, seqNum 0, frame 0.0, animPending 1, framePending/speedPending 0, blendTime 0.0) and stops; the second effect
  record is handed to the (still undrafted) fn_80011CA8(obj, kind, seq) whenever obj+0x30 is non-NULL, instead of the two actorRelated calls -> 72.36%
  next: 72 bytes short; the asm keeps the object in r28 and a `valid` flag that merges the negative-id path back into the shared tail check; try restructuring the negative-id handling as the original
  (if/else with a shared join) and compare against fn_8001BE50's chain. The bank ladder, bone setup and inlined fn_8001B5EC / fn_8001B308 tails are identical to fn_8001BE50.
- [S2] fn_8001BA44: switched to the `valid` flag-merge form (negative anim id = valid FALSE, bank logic only when valid) -> 79.40% (was 72.36% with the early return); ours 988 vs target 1036.
- [S2] fn_80016B60 (1052 bytes target, 992 ours) drafted: the per-record animation-bank load state machine (state byte huge+0x2D8D, 0 -> 1 ... 10 -> 0 returning TRUE) called per record by fn_80016F7C.
  Odd states start an ARAMTransfer into a per-record buffer (rec+0x18/0x14/0x1C/0x10/0x24 from huge+slot*0x14+0x2CEC..0x2CFC; the file number is charId*0x13 + an offset picked from the game mode),
  even states wait for lbl_803C6CF8[0x715] == 1 and ANIMGet the buffer. State 6 jumps to 9 (copying huge+0x2CF8 into rec+0x10) so states 7/8 are only reachable if set from outside
  -> 75.32%
  next: 60 bytes short; computing the file offset in an if/else chain with a single ARAMTransfer per state (as the asm does) gained ~5 points vs duplicating the call per branch. Compare state 9 (fixed
  offset 0x10, lwz of lbl_803CB790 before extsb) and the else-if chain structure.
- [S2] fn_80016710 (1104 bytes target, 1028 ours) drafted: (charId, slot) sibling of fn_80016344 for the non-captain path, same huge+0x2D77 state machine (6 -> 1, 1 -> 0, 0 -> fn_80017098(0,0,0,slot,1,charId)).
  Differences: state 2 only binds the object slot (no +0x25A/+0x25B), state 3 has no slot-12 special case, state 4 attaches the part effect through lbl_80118220 itself in practice mode but through a per-slot
  buffer (lbl_80118220 + slot*0x64) otherwise (two copies of the same attach block, each with a "no part" goto join), and state 5 finishes with animateModelArmsGlovesBats (practice) or the undrafted
  fn_80012B90 (otherwise) and returns 1 without resetting the state -> 75.07%
  next: 76 bytes short; as with fn_80016344 the repeated "ready" blocks are probably one inline; the two attach blocks differ only in the effect buffer pointer, which suggests an inline taking it as a parameter.
- [S2] fn_8001500C (1116 bytes target, 1124 ours) drafted: (team, idx, slot) loader for a runner/batter-style extra model, state byte huge+0x2D77 (the asm takes a third argument, slot, that the extern
  declaration in game/match_setup/match_transitions.c omits). 0 -> fn_80017098(team, idx, 1, slot, slot == 9, -1), result saved at huge+0x2D78 (slot 9 goes to state 2, others straight to 5 if the object
  has no +0x30 effect); 2 binds the object slot to the record index huge+0x2D79; 3 waits for fn_80017340 and picks 4 (needs an effect buffer: lbl_803CBC34[3], or [4] with slot 9) or 5; 4 finds or allocates
  a slot of lbl_80118220 (0x64-byte effect buffers, +0x60 charId, +0x61 slot/-1 free/-2 end) for the character and attaches its part effect (lbl_803CBC28 = chosen index, lbl_803CBBF9/FA handshakes);
  5 runs animateModelArmsGlovesBats -> 88.99%
  next: 8 bytes over; the search for an existing/free buffer is two loops with the free-slot index published through lbl_803CBC28; the final return value after the fn_80017098 result path should be checked.
- [S2] note on fn_8001500C: the real function takes a third `slot` argument that callers pass in r5; the two-argument extern in game/match_setup/match_transitions.c is left alone on purpose
  (that REL file's codegen depends on it).
- [S2] fn_8001AB10 (1160 bytes, ours 1160) drafted -> 93.93%. The shadow/overlay draw callback registered with fn_800BF058 (StadiumModel* is really an ActorObjectEntry*; header prototype kept).
  Picks a material colour from the owning record (huge+0xC04+entry->slot*0x27C): kind +0x25D == 3 -> grey level fn_8003AE54() scaled by a height fade ((lbl_803CB7BC - |y|) / lbl_803CB7BC clamped to 0..1),
  kind 1 -> level with alpha rec[0x277] (skipped if 0), otherwise returns; GXSetChanMatColor; translate to the object position; outside toy-field mode draws the actor's bones and skin directly
  (fn_8003A8A0 / DOVARenderSkin) and restores the colour; in toy-field mode applies a lighting colour (lbl_803CB7C1 rgb, lbl_803CB7C0 alpha) and draws the entry through the usual drawArgCount switch.
  next: only scheduling/register differences remain; the two PSMTXTrans calls (one per toy-field branch) are intentionally duplicated as in the asm.
- [S2] fn_80015468 (1252 bytes target, 1244 ours) drafted: the other-side counterpart of fn_80014A18 (same three-state bank loader on huge+0x2D8E for the 9 fielder banks): its state 0 first frees cache entries
  no object 0..8 still uses (a local used[9] marks entries whose charId matches an object; unused ones are set to -1), state 1 stores the cached buffer into obj+0x18 (fn_80014A18 stores obj+0x24),
  and state 2 is identical -> 93.57%
  next: 8 bytes short; the asm's inner match loop is unrolled 3x (ctr 3) with a repeated null check of objects[i]; same invariant-reload quirk as fn_80014A18.
- [S2] fn_80017814 (1300 bytes target, 1660 ours -- WEAK DRAFT) drafted: (record, slot, mode, callback) finish routine for a loaded model record. Relocates the five file-relative pointers of the loaded block
  (rec+8 -> [0..4], each only if the previous is non-zero), convertTextureHeader, then (only if a layout exists) LoadActorLayout / convertGeometryAndSknHeader / haveActLayoutPointToGeoHeader /
  UpdateTexturePalettePointers, characterAndBallDisplayRelated(entry, (s8)rec[0x255], slot, layout, rec+0x18 (mode < 9) or rec+0x14, skn), ACTActorRelated for the extra file, rebuilds the bone->part map
  (memset 0xFF x 0xF0 at rec+0x162, then partBones[boneId] = index), the three DS list inserts, the same bone setup as fn_80017DBC, entry speed 0.5 / pending flag, initShortsHandleCompressedDiskReads(rec),
  entry->callback = callback, clears the per-record animation state (+0x60..0x6E = -1, bytes 0x25D..0x273 = 0, +0x277 = 0xFF) and runs the per-character setup switch (jump table 0x800EEC40: DK, MAGIKOOPAx4,
  BOWSERJR, a flag-only group KOOPA_GREEN/PIANTAx3/KOOPA_RED, a separate identical flag-only group NOKIx3, PARATROOPAx2, PETEY, PARAGOOMBA, MONTY/GOOMBA, BOO/KINGBOO, SHYGUYx5) -> 56.21%
  next: 360 bytes over. Candidates: the five-step relocation chain (the asm reloads rec+8 each time but uses the first-loaded header for the adds), the 22 single-byte zero stores (asm keeps r3 = 0),
  the bone-map loop, and the eight s16 -1 stores (the asm writes them straight-line; I use a loop).
- [S2] fn_80017D28 re-check: passing the real arguments (p, (s8)obj[0x255], obj[0x254], fn_8001FDD4) scores 64.05% vs 88.11% with the one-argument cast, so the cast and its comment stay.
- [S2] fn_80019C00 (1628 bytes target, 1764 ours) drafted: the drawing task registered by fn_8001A25C (twin of fn_800196D8; jump table 0x800EEDC0 maps states 0..6 in order, >= 7 is the exit state).
  0: setupAnimationModelMemory, initActorArray((toyField + 1) * 4), marks effect buffers 4..12 free (lbl_80118220[0x61 + k*0x64] = -1), sizes a pool as the max of the +4 field of the lbl_803CB794 entries
  named by lbl_800EEB18 (same scan as fn_8001A3FC), carves four 0x64-byte effect buffers from it (lbl_803CBC30, lbl_80118220 +0/0x64/0xC8/0x12C), fn_80014204(4), huge+0x13C = fn_80023AA4(),
  initialises the 4 records / object slots / bank caches; 1: spawns the fn_800188C0 task (huge+0x307B = 1); 2: waits for it (toy field -> state 3, otherwise state 5); 3: ARAMTransfer(MinigameCommonFiles) into
  huge+0x2D9C; 4: waits for lbl_803C6CF8[0x715] == 1; 5: the shadow setup identical to fn_800196D8 state 2; 6: challengeMapMaybe (+ somethingFileHandlingLoadingRelated in toy field);
  default: huge+0x2D7D/0x307C = 1, removeCurrentDrawingItem -> 77.59%
  next: 136 bytes over: the pool max scan and the per-record init loops are the likely culprits (same unrolling problems as fn_8001A3FC / fn_800145F8); state 5 is shared with fn_800196D8's state 2 and
  probably one inline in the original.
- [S2] fn_8001D2D4 (2208 bytes target, 2204 ours) drafted -> 90.92%: the per-frame actor/model update for all 13 objects, run only while huge+0x307C && huge+0x307A are set. Steps: fn_8001C234 (animation
  state machine, mask unused here), the per-character special-case switch (same table as fn_80011468), clears applyControl of every actor-table entry, then per object: copies the object's control /
  rotation (lbl_803CC510 scaled) and scale (charSizeMultipliers[charId][mode == 5]) into its actor entry, handles the frozen/paused speed state (speed 0 or obj+0x4C, the bit-7 flag at +0x11 of the
  shadow/effect records obj+0x2C+0x10, obj+0x30+0x10/+0x74), refreshes them with fn_80024DB0; fn_8001DB74(actor table); second pass for visible actors (transform the origin through fn_800B2C88/
  PSMTXTransApply/PSMTXMultVec -> setVectors, fn_80024FA4 for the shadow records and the model-entry pairs chosen by anim 0x3A..0x3C); then, unless mode 2, the extra effect tables at huge+0x2D90/+0x64/+0x2D94/+0x68
  (translation/rotation per entry, fn_800BD8C4 with camera 0's view matrix) and the optional one-shot hook at huge+0x3070.
  next: scheduling/register only (4 bytes short); the three bit-7 flag clears/sets and the three speed copies are written as straight-line null-check blocks as in the asm.
  Added #include "Unknown/File_0x800bd8c4.h" (fn_800BDA24 now comes from it; the local extern was removed).
- [S2] fn_80018DEC (2284 bytes target, 2132 ours) drafted: (mode 0/1/2) sizes and carves the big shared character-animation buffer pool (called from fn_8001A3FC during init). Six running maxima (& 0x0FFFFFFF)
  over the character file table lbl_803CB790 (stride 0x130): mode 2 scans all 54 records for fields +0xA4/+0xB4/+0x124/+0x44 and the eight non-captain roster entries for +0x44/+0x64; mode 0 scans the
  18 roster entries (fields +0x24..+0x64); other modes scan all 54 records (+0x24..+0x64). Each is rounded to 32 and stored at huge+0x2C90..0x2CA0, the total (5 buffer kinds; mode 2 has one fewer 'E' buffer and an
  extra 'D' one) is allocated from heap 0x20 into huge+0x2C88 / +0x2D60, then the buffers are handed out in descending table order (huge+0x2CA8 + 4*i) with the cursor left at +0x2D48 and the A size at +0x2D4C;
  finally six words of each of the 13 object records are cleared and huge s16 +0x2D68 = -1 -> 78.59%
  next: 152 bytes short; the asm's carve loops are unrolled 8x with a running index (my while loops are counted differently) and the max scans use pointer-walking; the three scans are the main size.
- [S2] tidy: fn_8001C234's local extern before fn_8001D2D4 is now a plain forward declaration matching the definition.
- [S2] fn_8001E784 (2536 bytes target, 2576 ours) drafted: the top-level stadium/overlay render pass. GXSetCurrentGXThread; with huge+0x307A == 0 it only runs the stadium hook (lbl_803CB7AC[drawStadiumRelated == 0],
  once with 0 and, if still set, again with 1 then cleared) when +0x3088 && +0x307E and finishes with fn_8003414C / minigamesGXStuff. Otherwise it re-lights the stadium (+0x3085: ambient colour
  through adjustLightingParams, the four LIT lights re-initialised with attenuation / position / colour / normalised direction / camera transform), then for each scissor mode (last to first, setScissorAndProjection)
  switches on +0x307A: 3 = stadium hooks + overlay table (huge+0x68 entries drawn through sknRelated with the per-entry callbacks at huge+0x2D94) + fn_8003414C; 5 = the overlay frustum pass (body of fn_8001E488
  inlined, drawArgCount switch of fn_8001DD58); 2 = GXSetZCompLoc(0) + fn_8001E0D8; 4 = fn_8001E0D8 + overlay table + fn_8003414C; anything else = hook, then (+0x307C) fn_8001E0D8, fn_800BD670, overlay table
  and the one-shot hook at huge+0x3074, then the hook again and fn_8003414C. Ends with GXSetScissor(0,0,640,448) -> 75.96%
  next: 40 bytes over; the repeated hook / overlay-table blocks are macros here (the original probably used static inlines), and fn_8001E488's body is duplicated by hand (it is inlined in the original --
  a shared static inline would also serve fn_8001E488; only try it if fn_8001E488 stays at 97.30%).
- [S2] fn_80011CA8 (2628 bytes target, 2116 ours) drafted: (obj, kind, seq) re-balances an object's six animation-bank descriptors after a new animation kind is chosen. The six descriptors (three 0xD4-byte
  bank records of slot*0x27C, each with buffers at +0x140 and +0x1A4) are first copied into a local table indexed by (desc id % 6); two of them (picked by kind and obj+0x25A / +0x25B: kinds 2..4 use
  {4,1} or {0,3}, others {2,3} or {4,5}) are copied into the object's effect record (obj+0x30 and obj+0x30+0x64); the four remaining ones are written back to descriptors 2..5 in order; then the two
  hand-attach part nodes (handAttachBoneIDs[0] / [1], same block as the tail of LoadModel) get their link from the last part node that has one; finally actorRelated(effect + 4 / + 0x68, kind, seq). Returns TRUE
  (fn_8001BE50 / fn_8001BA44 call it and ignore the result) -> 60.01%.
  Needed: the local `used[6] = {0,...}` initialiser (the target loads it from lbl_803CD308/30C) and writing the six copies out explicitly (BANK_DESC_AT macro) -- a loop was 1256 bytes.
  next: 512 bytes short: the asm keeps the six descriptor pointers live in saved registers / stack slots and expands the 4-way write-back with per-case stores through those pointers; the hand-node link block is
  also two separate non-inlined-looking copies. Candidates: inline copyBankDesc (static inline) and write the used/spare loop with six explicit blocks.
