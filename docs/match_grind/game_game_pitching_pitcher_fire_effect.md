# pitcher_fire_effect checkpoint
| function | status | pct |
|---|---|---|
| fn_3_CB538 | exhausted | 96.16% |
| animatePitchersHandOnFire | pending | 99.78% |

fn_3_CB538 (param mode r29 ours vs r28 target, set r28 vs r29; knock-on scheduling of `cmpwi mode,2` and the texture/table address setup)
  baseline: 96.16%
  [1] declaration-order: 300 random permutations of the 10 locals -> max 96.16 (many orders worse)
  [2] set type s32/u32/BOOL -> same; u8/s8 -> 87.9; i s32 same, u32 95.5
  [3] ternary for set -> 95.2
  [4] for-loop forms of the slot[1..2] loop (pointer+index, &slot[i]) -> 94.9 / 94.6
animatePitchersHandOnFire (slot0/slot1 pointer regs swapped r28/r30; slot2 r29 right)
  baseline: 99.78%
  [1] 120 random decl-order permutations -> max 99.78
  [2] 6 assignment orders of slot0/1/2 -> 99.78 best (original)
  [3] slots + N, slot2 - k, slot0 + 1, &slot0[1] -> 99.78 / 96.2 / 95.8
  [4] no `slots` local (&lbl_3_data_17DC0[N]) -> same; direct lbl[N] in calls -> 95.3; slots[N].field -> 86.1
  [5] chained texture store -> 99.66; u32 tex local (both decl positions) -> same
