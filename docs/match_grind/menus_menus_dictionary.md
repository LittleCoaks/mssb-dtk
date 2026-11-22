# menus/menus/dictionary checkpoint (Opus pass)

| function    | status  | pct            |
|-------------|---------|----------------|
| fn_2_54BB0  | pending | 85.61 -> 85.67 |

.rodata 100, .data 0 (jump table; follows .text).

## Hypothesis log
fn_2_54BB0 (one 3.5 KB state machine)
  [1] work-pointer setup stores in the target's emitted order (1A8248, 1A824C, 1A8244, 1A823C, 1A8234, 1A8230) -> +0.06 kept
  [2] port read through lbl_2_bss_1A824C (forwarded store) instead of the local w; (s32) pad-byte compare -> no change
  left: target stores the pointers through addi'd addresses (stw 0(rX)) and reads the port after them; ours folds sym@l
  into the stores and hoists the read. AtBat_ButtonInput1 is the header struct type here (static/UnknownHomes_Static.h),
  so text_3C03C's PadInput-array lever (pad base lis order) needs the cast form, which lost the order there.
  Remaining diffs through the cases are register numbering / scheduling.
