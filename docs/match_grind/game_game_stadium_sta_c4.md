# sta_c4.c (Peach Garden) — match grind checkpoint

Unit: `game/game/stadium/sta_c4`
Module: game (REL)
Baseline at session start (2026-09-23): every function a bare `return;` stub; fn_3_F8444 and
fn_3_F8454 (first two functions in the split) were missing from the .c entirely.

Hazards: brick / note / mystery blocks (hit handlers in lbl_3_data_1BA88.hitFns[type]),
brick debris, a fountain with scrolling indirect-texture water and a spray particle emitter,
and the stadium crowd (first stadium implemented with crowd setup; sta_c0 has none yet).

Ghidra names: F8454=FUN_807374e8, F8524=FUN_807375b8, F85B0=FUN_80737644, F8878=FUN_8073790c,
F8B04=FUN_80737b98, F8B34=FUN_80737bc8, F8BA8=FUN_80737c3c, F8D00=FUN_80737d94,
F8E20=gardenBlockHitFxDraw, F9088=FUN_8073811c, F9164=FUN_807381f8, F92FC=blockPostHitTimerUpdate,
F934C=blockKnockbackUpdate, F963C=FUN_807386d0, F976C=blockOnHit_Note, F99F0=stadiumHitFxOnCollision,
F9B9C=blockOnHit_Mystery, F9D94=blockBreakDebrisUpdate, F9E78=blockOnHit_Brick, FA3C0=FUN_80739454,
loadPeachGarden="loadPeachGarden?" (curl --data-raw), FB3D8=FUN_8073a46c, FBBA0=FUN_8073ac34.
Mapped = text offset + 0x8063F094. F8444 / F8B30 have no Ghidra function.

bss (base lbl_3_bss_B570, statics declared in reverse address order): B570 u8 (unused),
B574 emitterID, B578 fountainEffect (0x5C), B5D4 hitFxTeardown (set by F8444, read by F8E20),
B5D8 hitFxPos[6], B620 hitFxState[6], B628 hitFxScene, B62C nBlockObj (u16, 0xFFFF sentinel),
B630 debrisSlots[9], B63C noiseTex, B640 noiseTexObj, B660 sprayTexture, B664 emitterPaused.

.data: loader addresses lbl_3_data_1BA88 as one table (GardenData: hitFns[4] @0, blocks @0x10,
objTypes @0x3F8); other functions use the `blocks` symbol directly.

Shared changes made for this unit:
- stadium_framework.h: StadiumObjectCollision _08/_0C/_10 -> crowd/crowdAlt/crowdWave (new
  StadiumCrowdAnim / StadiumCrowdWave), _4C -> hitBallPos/hitBallVel, _6B -> hazardHitActive
  (sta_c2's three uses renamed).
- actRelated(file) -> actRelated(file, effect): every call site in the binary passes &effect in r4.

## Status

From report.json, updated after every function (2026-09-22 session).

| function                           | status    | pct |
|------------------------------------|-----------|-----|
| fn_3_FBBA0                         | matched   | 100.0% |
| fn_3_FB3D8                         | exhausted | 97.6767% |
| loadPeachGarden                    | exhausted | 97.9148% |
| fn_3_FA3C0                         | exhausted | 96.6435% |
| fn_3_F9E78                         | exhausted | 98.7278% |
| fn_3_F9D94                         | matched   | 100.0% |
| fn_3_F9B9C                         | matched   | 100.0% |
| fn_3_F99F0                         | matched   | 100.0% |
| fn_3_F976C                         | matched   | 100.0% |
| fn_3_F963C                         | matched   | 100.0% |
| fn_3_F934C                         | exhausted | 98.883% |
| fn_3_F92FC                         | matched   | 100.0% |
| fn_3_F9164                         | matched   | 100.0% |
| fn_3_F9088                         | matched   | 100.0% |
| fn_3_F8E20                         | exhausted | 98.2792% |
| fn_3_F8D00                         | matched   | 100.0% |
| fn_3_F8BA8                         | matched   | 100.0% |
| fn_3_F8B34                         | matched   | 100.0% |
| fn_3_F8B30                         | matched   | 100.0% |
| fn_3_F8B04                         | matched   | 100.0% |
| peachGardenSomething               | matched   | 100.0% |
| fn_3_F8878                         | exhausted | 98.3793% |
| fn_3_F85B0                         | matched   | 100.0% |
| fn_3_F8524                         | matched   | 100.0% |
| fn_3_F8454                         | matched   | 100.0% |
| fn_3_F8444                         | matched   | 100.0% |

19/26 at 100%.

## Log

### first pass (all functions written): 9/26
### fn_3_F9D94: condition is `debrisFrame >= length` with teardown first -> 100%.
### fn_3_F8E20 (98.28%, exhausted after 7 variants)
  per-case block-scoped sx/sy (target uses two stack pairs), START case first, `state++, v++`.
  Remaining: target materializes `scale == 2` (subfic/cntlzw/srwi.) and we emit cmplwi. Tried
  `!(x-2)`, `==TRUE`, `!=FALSE`, `(u8)(..)`, three inline-helper forms: no change. The same
  mismatch exists in sta_c2 fn_3_CE954 and bowser fn_3_C3C2C.
### fn_3_F9164 / F99F0 / F976C: stadiumID declared before sfx, hitFxState store before the
    position stores -> all 100%.
### fn_3_F963C / F9B9C: `(u16)(currentDrawingItem->priority + 1)` at the call (the callee
    insertGraphicDrawingFunction is 100% with a u32 param) -> 100%.
### fn_3_F9E78 (98.73%): inline gardenActSetFrame/gardenActSetSpeed helpers (paired stores),
    ACTSetAnimation start frame literal 0.0f, `idx + nBlockObj + 9`, `int i` declared 2nd.
    Remaining: `(nBlockObj + idx) + 9` association of the shadow index.
### fn_3_FBBA0: `tlut != NULL` branch first -> 100% (same fix applied to FB3D8).
### fn_3_F8D00: offset computed before rand(); `(u8)(rand() % 4) + 0x7E` -> 100%.
### fn_3_F8BA8: u8 frame local, s8 prev/cur, one fn_800247E4 call per texel -> 100%.

### fn_3_FA3C0 (96.64%): size terms ordered s32,u16,f32,VecSrcDst (12 orders tried: 93.99-95.99);
    locals ordered group,j,count,off (8 orders tried). Remaining: loop-counter register numbering.
### fn_3_F934C (98.88%): `Vec tmp` before `Vec disp`, cached `vel`/`pos` pointers, reset branch as
    the then-block (`phase != 0 && (fabs <= 1e-6 || !(a<0 || b<0 || c<0))`),
    `shadow = (u16)(nBlockObj + 9); shadow = objIndex + shadow;`.
    Remaining: target loads nBlockObj / objects via addi+lhz/lwz 0 (address materialized).
### fn_3_F85B0: `p->alpha += -2.390625` / `+= -1.59375f` (not `alpha = alpha + c`) -> 100%.
### fn_3_F8878 (98.38%): locals `delay, p, i` (6 orders tried). Remaining: i/delay register swap
    and the angle kept in f31 via a copy (fmr f31, f1).
### loadPeachGarden (97.91%): 92.0 -> 97.4 with `GardenData* data` local, GARDEN_ANIM_TABLE macro
    (no animTable local; target materializes hugeAnimStruct after ActorObjectInitTable), cached
    `wave` pointer; 97.9 with `b` re-synced from `o` in the loop latch (and after o++ in the shadow
    loop). 8 declaration orders tried (96.98-97.94). Remaining: register numbering.

### fn_3_FB3D8 (97.68%): 85.8 -> 92.6 with `j <= 20`, cached `center`, `min > x` / `max < x`
    compares, `maxX = -minX` (target fnegs at runtime), ring vertices as single GX_WRITE_F32
    writes (target reloads strip[0] after each volatile store); 95.8 with inner-loop vertices via
    GXPosition3f32/GXColor1u32/GXTexCoord2f32; 96.8 with GardenView (view->mtx inline, no `m`
    local); stack order delta,step,tlut,tex,ringUV; 97.7 with a separate `out` pointer copied from
    `dst` per spoke (target keeps two grid pointers). Float decl order / init shape: no effect.
    Remaining: register numbering.

## Session summary (2026-09-23)
All 26 functions implemented (fn_3_F8444 / fn_3_F8454 added). 19/26 at 100%, unit .text 98.73%.
.bss (0x108) and .rodata (0x128) sizes match.
Near misses: fn_3_F934C 98.88, fn_3_F9E78 98.73, fn_3_F8878 98.38, fn_3_F8E20 98.28,
loadPeachGarden 97.91, fn_3_FB3D8 97.68, fn_3_FA3C0 96.64 (all register allocation or one
expression association, see the entries above).
Cross-unit effect of actRelated(file, effect): loadWarioPalace +0.11, loadDKJungle +0.30,
loadBowserCastle -0.08, palaceMinigameObjectLoading -0.21 (target builds &effect straight into r4;
ours folds it into a stwu). Kept: the two-argument form is what every call site in the binary does.

## Cross-stadium pass (2026-09-23)

Moved .data 0x1BA88-0x1C0A8 into the unit (GardenBlockTable, GardenCameraSlot) and took fn_3_FBCD0 (.text end -> 0xFBD58): fn_3_FBCD0 100%, .data 99.87% (only the 4-byte section alignment tail). Chained _34 alloc: loadPeachGarden 97.92 -> 98.14.

Matched 20/27; .text 98.80%.
