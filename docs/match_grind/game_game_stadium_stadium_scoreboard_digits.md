# stadium_scoreboard_digits checkpoint
| function | status | pct |
|---|---|---|
| fn_3_16D810 | pending | 93.89% |
| fn_3_16DB6C | pending | 94.62% |

Kept (commit 70a26985): reverse address order + literal position constants; DB6C widths `* 50 / 512.0f`, D810 `* lbl_418C * lbl_4190` (static consts).
  .rodata 84.4 -> 96.9 (remaining: 1/512 is pooled before 50.0 because D810's product commutes the 1/512 operand)
fn_3_16D810
  [1] `width *= k` / `/ 512.0f` forms -> rodata 100 but D810 91.15/91.20 (constants loaded via addi+lfs 0 instead of direct, f31 vs f1 temp)
  [2] 50*digit*k, explicit parens, f32 scale local -> same as baseline
fn_3_16DB6C
  [1] DRAW_SCORE_DIGIT macro as static inline (both param orders) -> no change (D810 nor DB6C)
  [2] call fn_3_16D810 for each digit (inlined) -> 89.29, size 1108 vs 1112, FPRs shift by one
  remaining: r3/r4 swap between lbl_3_data_2A448/2A478 bases and the 0xCC01 FIFO base in both functions
