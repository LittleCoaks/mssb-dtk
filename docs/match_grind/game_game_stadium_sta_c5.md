# sta_c5.c (DK Jungle) — match grind checkpoint

Unit: `game/game/stadium/sta_c5`
Module: game (REL)
File name: the unit emits "sta_c5.c" as its OSPanic __FILE__ string, so upstream renamed it
from stadium_dk_jungle.c in 8badc5e (2026-09-21). The stadium is still DK Jungle.
Baseline at session start (2026-09-23): all 73 functions implemented upstream, 38/73 at 100%,
unit fuzzy 93.70%.

## Status

From report.json, updated after every function (2026-09-22 session).

| function                           | status    | pct |
|------------------------------------|-----------|-----|
| loadDKJungle                       | pending   | 83.6976% |
| fn_3_F6FCC                         | matched   | 100.0% |
| updateDKJungleControl              | pending   | 98.379% |
| fn_3_F6A94                         | pending   | 95.6522% |
| maybeBarrelCTRLRel                 | matched   | 100.0% |
| updateDKJungleObjBoundingBoxes     | pending   | 95.8974% |
| fn_3_F65C8                         | matched   | 100.0% |
| fn_3_F6504                         | matched   | 100.0% |
| processJungleObjectCollisions      | pending   | 96.1736% |
| fn_3_F5F4C                         | matched   | 100.0% |
| fn_3_F5F28                         | matched   | 100.0% |
| fn_3_F5EFC                         | matched   | 100.0% |
| fn_3_F5E78                         | matched   | 100.0% |
| fn_3_F5C30                         | matched   | 100.0% |
| dkJungleBarrelCannonUpdate         | pending   | 97.829% |
| handleBarrelFiring                 | pending   | 97.9115% |
| fn_3_F4DAC                         | matched   | 100.0% |
| fn_3_F4D00                         | matched   | 100.0% |
| fn_3_F4C4C                         | pending   | 98.8889% |
| fn_3_F4BA0                         | matched   | 100.0% |
| dkJungleBarrelCannonCutsceneUpdate | pending   | 86.55% |
| fn_3_F469C                         | matched   | 100.0% |
| fn_3_F466C                         | matched   | 100.0% |
| fn_3_F42A0                         | matched   | 100.0% |
| fn_3_F3EFC                         | matched   | 100.0% |
| dkBarrelSmokeUpdate                | matched   | 100.0% |
| fn_3_F3BB0                         | matched   | 100.0% |
| fn_3_F3AE0                         | matched   | 100.0% |
| fn_3_F3A5C                         | matched   | 100.0% |
| fn_3_F3A04                         | matched   | 100.0% |
| initBinomialTable                  | matched   | 100.0% |
| binomialCoefficient                | matched   | 100.0% |
| dkBarrelLaunch                     | pending   | 77.0293% |
| fn_3_F2FFC                         | pending   | 99.4297% |
| dkBarrelAdvanceMotion              | pending   | 82.9931% |
| fn_3_F2724                         | pending   | 99.3985% |
| dkBarrel_collisionWithFielder      | pending   | 99.2896% |
| fn_3_F22FC                         | pending   | 97.4699% |
| dkBarrelSpawnGroundDust            | pending   | 98.8117% |
| handleDKJungleBarrel               | pending   | 98.1614% |
| fn_3_F18A4                         | matched   | 100.0% |
| fn_3_F1750                         | pending   | 97.4% |
| fn_3_F1674                         | matched   | 100.0% |
| maybeGharialCTRLRel                | matched   | 100.0% |
| klaptrapCTRLSetup                  | matched   | 100.0% |
| fn_3_F13F8                         | matched   | 100.0% |
| klaptrapControl                    | pending   | 99.1697% |
| dkKlaptrapRoamUpdate               | pending   | 91.2343% |
| dkKlaptrapChaseUpdate              | pending   | 96.4326% |
| fn_3_F0184                         | matched   | 100.0% |
| fn_3_EFB54                         | pending   | 97.6768% |
| dkKlaptrapLaunchedUpdate           | matched   | 100.0% |
| fn_3_EF890                         | matched   | 100.0% |
| fn_3_EF800                         | matched   | 100.0% |
| fn_3_EF7B4                         | matched   | 100.0% |
| isPosOutsideKlaptrapZone           | pending   | 99.3267% |
| jungleStadiumObjectRelated         | pending   | 97.4118% |
| fn_3_EF3D4                         | matched   | 100.0% |
| fn_3_EF21C                         | matched   | 100.0% |
| fn_3_EF218                         | matched   | 100.0% |
| klaptrapHitAnimation               | pending   | 97.8828% |
| fn_3_EEFD0                         | matched   | 100.0% |
| fn_3_EEFA4                         | matched   | 100.0% |
| fn_3_EEF24                         | matched   | 100.0% |
| fn_3_EEE3C                         | matched   | 100.0% |
| fn_3_EECF4                         | pending   | 95.4146% |
| fn_3_EEB94                         | matched   | 100.0% |
| fn_3_EE96C                         | pending   | 92.7826% |
| fn_3_EE67C                         | pending   | 69.2713% |
| fn_3_EE388                         | pending   | 82.6931% |
| fn_3_EE100                         | matched   | 100.0% |
| fn_3_EE0BC                         | matched   | 100.0% |
| fn_3_EDFAC                         | pending   | 89.1912% |

43/73 at 100%.

## Log

### fn_3_F3EFC / fn_3_F42A0 (F42A0 inlines F3EFC)
  [1] chained stores reversed: `_38 = _3C = 10`, `vel.x = vel.z = 0` (target stores the
      right-hand member first) -> both 100%.

### dkKlaptrapLaunchedUpdate: PSVECAdd(&pos, &vel, &pos) and PSVECCrossProduct(&down, &vel, ...) -> 100%.
### fn_3_EF21C: stadiumID u8 -> int (slwi vs clrlslwi) -> 100%.
### fn_3_F5F4C: `0.125f*` operand swap no change; `(depth - nearZ) / 8.0f` -> 100%.

## Paused (2026-09-23) at user request; resume after other stadiums are in shape.
Next: fn_3_F2FFC, fn_3_F2724, isPosOutsideKlaptrapZone, dkBarrel_collisionWithFielder, klaptrapControl, fn_3_F4C4C (all >98.8%).

## Cross-stadium pass (2026-09-23)

Moved .data 0x1B820-0x1BA88 into the unit (DKJungleBarrelLauncherTable/KlaptrapTable/DrawHooks types): .data 100%, loadDKJungle 83.70 -> 87.41. Tried routing lbl_3_bss_B154 slots through DKJungleBss in the loader: worse (86.74, extra spill), reverted. Chained _34 alloc: -0.02, not applied.

Matched 43/73; .text 94.19%.

## Literal-pool pass with tools/match_pool.py (2026-11-15)

.rodata 93.12% -> 100%, .text 97.05% -> 97.56%. No function changed status (the report already scored
the reloc-only ones as matched); the point is the section, which the Matching flip needs.
Pool was 0x2FC bytes vs target 0x308 with 93 of 94 aligned literals shifted. Causes, in the order they were found:
  [P1] fn_3_F5E78 panic text was the wrong sentence (36 bytes, a named static pooled FIRST). Target is the
       28-byte inline literal "//OZ <modori-atai ga arimasen>
" (96 DF 82 E8 92 6C 82 AA 82 A0 82 E8 82 DC 82 B9 82 F1).
       Inlined into the OSPanic call so it pools in use order.
  [P2] dkJungleBarrelCannonCutsceneUpdate: target pools a second Vec {0,1,0} right after `forward`, with no
       user. A dead `Vec up = {0.0f, 1.0f, 0.0f};` local reproduces it (dead locals still pool).
       match_pool.py shows this as one 24-byte target object only because dtk's symbol is gap-sized.
  [P3] fn_3_EFB54: pooled order is offset {0,0,0} then axisX {1,0,0}; declarations swapped to match.
  [P4] two doubles are f-suffixed floats promoted: `0.0005f *` and `2.5e-05f *` (not the double literals).
  [P5] fn_3_EE96C: the target literal is 3e4ccccc, one ulp below 0.2f; written as 0.19999999f.
Every other function still scores as before (project-wide diff, no regressions).
Remaining in this unit is .text only: 27 functions, none reloc-only.

## Sweep (tools/match_sweep.py, 2026-11-15)
Variants are in game_game_stadium_sta_c5.sweep.md; do not repeat them by hand.
  jungleStadiumObjectRelated 97.41 -> 100: folding the single-use local `data` into its one use
      (`jungleKlaptrapData[obj->index].pos.z`). Applied.
  no variant improved: fn_3_F1750, fn_3_F2FFC, fn_3_F2724, isPosOutsideKlaptrapZone, fn_3_EDFAC
      (decl order, int types, abs idioms, compound assignment, casts, loop form and so on all tried).
  These five are now candidates for hand work, not for more sweeping.
