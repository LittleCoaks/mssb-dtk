# menus/menus/text_4B1AC checkpoint (Opus pass)

Unit fuzzy 83.56 -> ~95.3.

| function    | status    | pct            |
|-------------|-----------|----------------|
| fn_2_4C314  | matched   | 72.23 -> 100   |
| fn_2_4C36C  | matched   | 94.09 -> 100   |
| fn_2_4CEE0  | matched   | 83.37 -> 100   |
| fn_2_4B2D0  | pending   | 78.45 -> 95.81 |
| fn_2_4D378  | pending   | 72.23 -> 93.89 |
| fn_2_4D67C  | pending   | 73.46 -> 94.11 |
| fn_2_4C3EC  | exhausted | 77.17          |
| fn_2_4C9C4  | pending   | 94.42          |
| fn_2_4D194  | pending   | 93.02          |
| fn_2_4C6A8  | pending   | 98.92          |
| fn_2_4B1AC  | pending   | 99.45          |

fn_2_68690 prototype kept as s8 (see comment in the file).
readability pass: 4C314/4C36C (CAPTAIN_CLEARED macro), 4CEE0 (STADIUM_ID_*). Quirk kept: 4CEE0 compares a (>= 6) with 0..3.

## Hypothesis log
- Per-character copies (_7 <-> scoutFlagsAchieved): use `ChallengeTrackingStruct *record = &characters[i]` per iteration;
  the direct `characters[i].x = characters[i].y` form folds k*0x34 into displacements. Both directions are inline helpers
  (restoreChallengeProgress in 4B2D0, new saveChallengeProgress in 4D378/4D67C). 4D378 alone scored 94.66 with the loops
  written in place; with the shared helper 93.89 (kept for 4D67C's +20).
- 10-byte record table at ChallengeState+0x40EE..: CHALLENGE_REC2(idx, off) (same macro as rep_0788) gives the target's
  add + displacement form; byte-offset forms give addi+lbzx.
- fn_2_4C314: nested captain x difficulty loops (5 x 3; inner unrolled) over CAPTAIN_CLEARED; a flat 15-check body unrolls.
- fn_2_4CEE0: u8 stadium index, `a >= 6` branch first, each branch stores StadiumID then the indicator -> 100.
- fn_2_4C3EC: target addresses superstarUnlocked+0xF8 as one relocation (lis/addi sym+0xF8); `superstarUnlocked + 0xF8`,
  `&superstarUnlocked[0xF8]` give sym then addi 0xF8; direct indexing much worse (51). Probably a struct member in the original.
next: fn_2_4D194, fn_2_4C9C4.
