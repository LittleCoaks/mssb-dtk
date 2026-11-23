# main/Unknown/model  [S1] -- PARTIAL (small functions only)

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
| fn_8001A3FC | pending | 35.90 |
| fn_8001C234 | pending | 86.23 |
| fn_8001E488 | pending | 97.30 |
| fn_80014A18 | pending | 94.58 |
| fn_80011468 | pending | 85.15 |
| fn_800126EC | pending | 84.18 |
| fn_8001B4D8 | pending | 74.81 |
| fn_80016F7C | pending | 89.54 |
| fn_8001B5EC | pending | 89.87 |

## Findings
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
