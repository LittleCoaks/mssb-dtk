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
| fn_800189E4 | pending | 91.88 |
| fn_8001B35C | pending | 83.65 |
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
