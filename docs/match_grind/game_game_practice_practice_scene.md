# practice_scene checkpoint
| function | status | pct |
|---|---|---|
| practiceGoalHud_update | exhausted | 99.87% |

practiceGoalHud_update (inlined practiceGoalHud_updateCounter: count gets r30 ours vs r28 target; standalone + init copy 100)
  baseline: 99.87%
  [1] count/threshold type sweep {int,s32,u32,u8}^2 -> s32/u8 count (or (s32)count cast at call) fixes the register (r28) in update (99.91) but schedules `li r6,0x32` before `li r4/r5` in both standalone (99.79) and update; u32 worse. reverted
  [2] count declared first / block-scoped -> no change
  [3] i/freed decl order, s32 i, entry pointer hoisted to function scope, entry inlined as full array expr -> no change
  [4] read guidedPracticeCounter directly in each call -> 91.6
  [5] pass (PracticeScene*)currentDrawingItem to the inline -> 94.97
  next: the conversion node in [1] is the right lever for the register; something else must restore the li order
