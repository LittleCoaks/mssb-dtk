# batter_ai checkpoint
| function | status | pct (objdiff diff) |
|---|---|---|
| resetBatterAIBoxPosition | exhausted | 78.5% (report fuzzy 82.0) |
| batterAIFrameToSwingAndStickInput | exhausted | 99.49% |

Data fix (kept): `#define SQRT2_LINKAGE static`, lbl_3_rodata_918/930/934/938/93C externs replaced by
1.0f/0.0f/5.0f/30.0f/40.0f literals, functions reordered into reverse address order -> .rodata 84.7 -> 100,
fn_3_1E4B8/batterAIRNGValueSetting/... reloc names now match.

resetBatterAIBoxPosition (ours: first float constant loaded via `addi rX,@l; lfs 0(rX)`; target loads 0.0 direct and only initialBoxPosition via addi)
  [1] inline helper for the X/Z pair -> no change
  [2] f32 local for 0.0, initialBoxPosition.x for X (both pairs / one) -> 78.5 / 61.9 / 73.9
  [3] 0.0f/0.0/0 literal sweep for the two X stores -> no change
  [4] second X = self-assign / other field -> no change / 62.5
  finding: in a 2-store probe the FIRST float constant in source order always gets the addi form, whatever it is (0.0, 5.0, 30.0)
batterAIFrameToSwingAndStickInput (else-branch: batterAISwingEarly1OrLate2 value/base regs swapped; `!= 1` index *8 computed before difficulty*2 in ours)
  [1] ternary == 1 ? 0 : 1 -> 98.31; !(x == 1) -> same
  [2] int late / int diff locals (both orders) -> same (copy-propagated)
  [3] s8* range pointer local -> 98.97; min/max locals -> same
