# match_flow checkpoint
| function | status | pct |
|---|---|---|
| newPitch | exhausted | 99.00% |
| processScoreChanges | exhausted | 98.07% |

newPitch (GPR numbering shifted by one in the g_Scores block: base r7 vs r8, li 999 r8 vs r3)
  [1] s32 diff -> same; diff computed just before the clamp -> 99.06 (registers still shifted; not kept)
processScoreChanges (target reloads g_BallsStrikesOuts.outs for `outs + runnersOut >= 3`; ours reuses the earlier load -> 1 insn + one fewer saved reg)
  [1] operand order / += / > 2 / (s32) cast -> same; (u32) -> 97.9
  [2] if (outs < 3) {...} else {...} inverted -> 95.9; runnersOut += outs in a block -> 98.05
