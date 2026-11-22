# spline checkpoint
| function | status | pct |
|---|---|---|
| spline3D_evaluate | exhausted | 99.76% |

spline3D_evaluate (count param r30 ours vs r29 target; swapped with the &curveB[1] CSE pointer from the inlined spline_evaluate)
  baseline: 99.76%
  [1] s32 count (param + header) -> 94.77 (reverted, header restored)
  [2] s32 i -> 98.69
  [3] points->x with points++ pointer walk -> 97.4-ish/no gain
  [4] call spline_evaluate directly instead of spline2D_evaluate -> 92.90
