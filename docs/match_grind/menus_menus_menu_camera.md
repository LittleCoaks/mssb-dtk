# menus/menus/menu_camera checkpoint

_Written when the unit was still named `rep_10C0`; it was renamed to `menu_camera` (src/menus/menu_camera.c) with its functions (`menuCamera_*`). Function names below may be the old placeholders._

Baseline (session 1 start): unit 55.39 fuzzy; .text 53.56, .rodata 55.17 (no .data/.bss owned).
Session 1 end: unit 99.89; .rodata 100. Commit fc3b3e3c.

| function   | status    | pct (before -> now) |
|------------|-----------|---------------------|
| fn_2_946DC | matched   | 77.85 -> 100 |
| fn_2_94634 | matched   | 70.12 -> 100 |
| fn_2_9461C | matched   | 100 |
| fn_2_94604 | matched   | 100 |
| fn_2_93C64 | exhausted | 47.88 -> 99.81 |
| fn_2_93BF8 | matched   | 100 |
| fn_2_932DC | exhausted | 55.84 -> 99.80 |
| fn_2_92F2C | matched   | 63.31 -> 100 |
| fn_2_92CB0 | matched   | 37.74 -> 100 |
| fn_2_92A34 | matched   | 46.67 -> 100 |
| fn_2_927C8 | matched   | 45.06 -> 100 |

## Findings
- File-wide: float externs -> literals (rodata 55 -> 100); Vec consts as `{0,1,0}` initialisers.
  Exception: `mag * lbl_2_rodata_1140` (extern) in springStep: literal form puts the constant first in fmuls.
- `x / 1024.0f` (power of two) compiles to a multiply with the VALUE first (fmadds f1(val),f2(const));
  `x * 0.0009765625f` puts the constant first. Fixed 92F2C 97.4 -> 100.
- AtBat_ButtonInput1 must be indexed as a real array (`extern PadInput AtBat_ButtonInput1[4]`);
  casting `(PadInput *)&AtBat_ButtonInput1` gave base-in-r0 codegen (86.8 -> 97.4).
- springStep: static inline Vec helper(Vec target, Vec pos, Vec prev, k, damping, rest), by-value
  param order fixes stack layout; locals toTarget, scaledPrev, prevDir order.
- Callers: copy bss->locals field-by-field (lfs/stfs), not struct assign; decl order result,target,pos,prev.
- 92CB0: pos kept in f31-29 => scalar f32 x,y,z locals, target assigned before pos.
- 927C8: two memcpys from arg1 (one dead local `in`) - reproduced original quirk.
- 94634/946DC: direct `lbl_2_data_3BB0[arg0][i]` indexing (no entry pointer local); scales as locals scaleB then scaleA.
- 932DC/93C64 inline fn_2_927C8(arg0,&lookAt) and fn_2_92CB0 (calls auto-inlined).

## Hypothesis log
932DC + 93C64 shared residue (FPR colouring inside the inlined 927C8/92CB0 blocks: target gives
`dist` f28 and rest/d/k or x/y/z f31..f29; ours gives dist f31 and shifts the others down)
  baseline: 932DC 99.80, 93C64 99.81
  [1] springStep local decl order (dist first / mag before dist)            -> no change
  [2] ratio or dot as separate local                                         -> all spring fns drop (87-91)
  [3] hand-expanding 927C8 body into 932DC (locals in caller)               -> 99.62 (layout off), reverted
  [4] moving 927C8/92CB0 definitions above the callers                       -> pool order breaks siblings, reverted
  [5] 932DC cosY/sinY decl swap                                               -> 99.75, reverted
  next: try a non-inline wrapper shape / different caller arg (e.g. pass a CAM pointer), -inline levels.
93C64 end stores: order 0x58, 0x38, 0x30, 0x32, 0x3C (99.26 -> 99.81).

## Readability
- Not yet done: offsets on the camera object (self+0x30.. / lbl_2_bss_1A81D4) and CAM_F(0x76xx)
  should become struct fields; pending a struct that is codegen-neutral.
