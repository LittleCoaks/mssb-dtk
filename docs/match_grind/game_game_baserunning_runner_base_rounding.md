# runner_base_rounding.c (unit game/game/baserunning/runner_base_rounding)

| function                                    | status    | pct      |
|----------------------------------------------|-----------|----------|
| spline_evaluate (was fn_3_14A4)              | matched   | 100%     |
| spline_computeSecondDerivatives (was fn_3_155C) | matched | 100%     |
| spline2D_evaluate (was fn_3_19B0)            | matched   | 100%     |
| spline2D_build (was fn_3_1B24)               | matched   | 100%     |
| running_roundBasePosition                    | matched   | 100%     |
| spline3D_evaluate (was fn_3_28E4)            | exhausted | 99.76%   |
| fn_3_2D6C                                    | matched   | 100%     |
| spline3D_resample (was fn_3_310C)            | matched   | 100%     |

Renamed: fn_3_14A4->spline_evaluate, fn_3_155C->spline_computeSecondDerivatives, fn_3_1B24->spline2D_build, fn_3_19B0->spline2D_evaluate, fn_3_28E4->spline3D_evaluate, fn_3_310C->spline3D_resample

Sections at session start: .text 56.81%, .rodata 89.39%. Now: .text 99.97%, .rodata 100%. No .data/.bss in unit.

## Notes
- fn_3_19B0 inlines fn_3_14A4 twice; fn_3_1B24 inlines fn_3_155C twice. running_roundBasePosition, fn_3_28E4, fn_3_2D6C, fn_3_310C all call fn_3_1B24 and inline fn_3_19B0.
- Baseline: running_roundBasePosition called nonexistent `fn_3_19B0_` (header typo) instead of fn_3_19B0, so the inline didn't happen. Fixed by renaming the header prototype to `fn_3_19B0` and updating the call site; running_roundBasePosition jumped 52.18% -> 99.77% with no source reordering needed (fn_3_19B0's definition stayed physically after running_roundBasePosition in the file and MWCC still inlined it).
- The four helpers dropped to ~99.6-99.9% as soon as the file was rebuilt: all residuals were relocations to the 2.0f/3.0f pool constants, whose order was swapped vs target (target pools 3.0f first). Fixed by writing spline_evaluate's return as one expression that mentions 3.0f before 2.0f (pool order follows first reference in IR, not load order).
- fn_3_28E4 implemented per the draft in the task (copy loop + fn_3_1B24 + inlined fn_3_19B0 for x/y, second fn_3_1B24 + inlined fn_3_19B0 into a throwaway VecXZ tmp, out->z = tmp.z). Reached 98.52% immediately. Remaining diff (44 instructions): (1) target keeps `count` in r29, ours in r30 (~15 lines, pure register-allocation artifact, no source lever found); (2) target defers the store to out->x until after computing out->y (instruction scheduling in the inliner), ours stores out->x immediately after computing it -- 1 DIFF_INSERT + 1 DIFF_DELETE, same value just reordered; (3) several DIFF_ARG_MISMATCH pairs are actually identical instructions except objdiff shows our unnamed literal-pool labels (`@157`,`@158`) vs target's named `lbl_3_rodata_194`/`lbl_3_rodata_190` -- symbol-naming difference, not a codegen difference, same underlying constants (2.0f, 3.0f).
- Tried variant (a): replace the second fn_3_19B0 inline (VecXZ tmp) with two explicit fn_3_14A4 calls (`tmpx = fn_3_14A4(...); out->z = fn_3_14A4(...);`, tmpx an unused local). Score identical: 98.51724%, same 1160-byte size, same instruction diff. Reverted to the VecXZ-tmp draft (equally good, cleaner code).
- Checked variant (b) (stack-offset reordering) was unnecessary: our build already places xs@0x15c, ys@0x118, zs@0xd4, timings@0x90, curveA@0x4c, curveB@0x8, matching the target's offsets exactly with the declaration order in the draft.
- fn_3_2D6C / spline3D_resample implemented from scratch; hit exact size first try, 100% after the x/y copy-out-via-tmp change (V1). fn_3_80023DFC/fn_80023D98 are a Vec ring-buffer first/next iterator (Ghidra); no struct type exists, so fn_3_2D6C takes void* and reads count at +8.

## Hypothesis log
- shared: #define SQRT2_LINKAGE static -> dropped dolsqrtf2 _half/_three statics, .rodata 89.39->95.16 (kept)
- fn_3_14A4: single-expression return so 3.0f is pooled before 2.0f -> 14A4/155C/19B0/1B24/running_roundBasePosition all 100 (kept)
- fn_3_28E4 [a] explicit 14A4 calls for the z-pair -> no change (reverted)
- fn_3_310C [b] pointer-increment output loop -> 98.84 (reverted)
- fn_3_28E4 [V1] reuse tmp for x/y pair (fn_3_19B0 -> &tmp; out->x=tmp.x; out->y=tmp.z), keep second fn_3_19B0+tmp.z for z -> 99.75862% (kept)
- fn_3_28E4 [V2] separate `xy` temp declared before `tmp` for the x/y pair -> 99.75862% (reverted, tie with V1, V1 simpler)
- fn_3_28E4 [V2 alt] `xy` declared after `tmp` -> 99.75862% (reverted, tie with V1, V1 simpler)
- fn_3_28E4 [V3] explicit f32 x/y via two fn_3_14A4 calls, no fn_3_19B0 for the pair -> 99.75862% (reverted, tie with V1, V1 simpler)
- fn_3_2D6C [V1] reuse tmp for x/y pair (out[i].x=tmp.x; out[i].y=tmp.z), keep second fn_3_19B0+tmp.z for z -> 100% (kept)
- fn_3_310C [V1] reuse tmp for x/y pair (out[i].x=tmp.x; out[i].y=tmp.z), keep second fn_3_19B0+tmp.z for z -> 100% (kept)

spline3D_evaluate (fn_3_28E4) residual: GPR swap only -- target count=r29, CSE'd &curveB[1] (r1+0xc)=r30; ours swapped. r28=out, r31=&timings[1] match.
  [H1] static inline helper wrapping 1B24+19B0 -> did not inline, 43.86% (reverted)
  [H3] int n = count copy -> 99.76 no change (reverted)
  [H4] pointer-walk copy loop -> 82.73 (reverted)
  [H5] move VecXZ tmp declaration first / before arrays -> 99.76 no change (reverted)
  [N1] swap out->y/out->x copy-out order -> 99.07 (reverted)
  [N2] explicit spline_evaluate calls for both pairs into f32 locals -> 99.76 no change (reverted)
  [N3] while-loop copy -> 99.76 no change (reverted)
  [N4] count typed s32 instead of int -> 94.77 (reverted)
  [N5] combined array declarations -> 99.76 no change (reverted)
  => exhausted
</content>
