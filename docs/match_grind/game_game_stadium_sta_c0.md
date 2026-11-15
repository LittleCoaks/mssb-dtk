# sta_c0.c (Mario Stadium) — match grind checkpoint

Unit: `game/game/stadium/sta_c0`
Module: game (REL)
Baseline at session start (2026-09-23): every function a bare `return;` stub;
manageMarioStadiumSoundEmmitters (0xC9744, first function in the split) was missing from the .c.

Contents: water sound + seagull emitters, crowd wave (fanAnimationRelated, also registered by
Peach Garden), scoreboard / tree animation callbacks, scrolling indirect-texture water
(same scheme as Peach Garden's fountain, 128x64 noise), and the loader (trees from
marioStadiumTrees, `usedFlag == 4` ends the list).

bss (base lbl_3_bss_9F38, statics declared in reverse address order): 9F38 u32 (unused),
9F3C scrollDelay, 9F40 emitterID, 9F44 seagullEmitterID, 9F48 noiseTex, 9F4C noiseTexObj,
9F6C emitterPaused, 9F70 waterEffect (0x5C), 9FCC 0x10 unreferenced.

Shared changes: randomizeAndLoadSoundEffect returns the emitter ID (int; still 100%);
StadiumCrowdWave.mode -> rowCount.

## Status

From report.json, updated after every function (2026-09-22 session).

| function                           | status    | pct |
|------------------------------------|-----------|-----|
| loadMarioStadium                   | exhausted | 96.8092% |
| sta_c0                             | matched   | 100.0% |
| fn_3_C9B5C                         | matched   | 100.0% |
| fn_3_C9AC8                         | matched   | 100.0% |
| fn_3_C9A60                         | matched   | 100.0% |
| fn_3_C99F8                         | matched   | 100.0% |
| fanAnimationRelated                | matched   | 100.0% |
| manageMarioStadiumSoundEmmitters   | matched   | 100.0% |

7/8 at 100%.

## Log

### first pass: 5/8 (sta_c0, C9B5C, C9AC8, C9A60, C99F8 at 100% using the Peach Garden shapes)
### manageMarioStadiumSoundEmmitters: one nested `if (mode != PRACTICE && status != READY)`
    instead of an early return -> 100%.
### fanAnimationRelated: switch with `default:` first whose replay-active path falls through into
    the shared `pose = 0` cases; `Vec view` declared before `facing`; `state` before `row` -> 100%.
### loadMarioStadium (96.81%): 94.7 -> 96.2 with a MarioStadiumObj* `m` re-synced after every o++,
    fill loop `objectCount > count` + separate counter; 11 declaration orders tried (94.7-96.8).
    Remaining: register numbering, and the target computes slot*0x90 at runtime (mulli) where we
    constant-fold the first tree slot (u16 slot made it worse, 94.67).

## Cross-stadium pass (2026-09-23)

Moved .data 0x17B98-0x17D08 into the unit: .data 100%. Chained _34 alloc: loadMarioStadium 96.81 -> 97.12.

Matched 7/8; .text 98.03%.
