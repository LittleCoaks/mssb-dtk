# menus/menus/text_42BE8 checkpoint (Opus pass)

Unit fuzzy 80.43 -> 97.88. .data 0 -> 100 (objdiff diff).

| function    | status    | pct              |
|-------------|-----------|------------------|
| fn_2_44E2C  | matched   | 94.19 -> 100     |
| fn_2_44504  | exhausted | 42.31 -> 99.01   |
| fn_2_44414  | matched   | 100              |
| fn_2_44368  | matched   | 100              |
| fn_2_442E8  | exhausted | 98.28            |
| fn_2_44238  | matched   | 100              |
| fn_2_44184  | matched   | 100              |
| fn_2_44014  | exhausted | 96.36            |
| fn_2_43E8C  | exhausted | 95.00 -> 97.02   |
| fn_2_439D0  | exhausted | 94.24 -> 98.99   |
| fn_2_4358C  | exhausted | 90.82 -> 94.83   |
| fn_2_43404  | exhausted | 96.07            |
| fn_2_432EC  | exhausted | 98.79            |
| fn_2_430F4  | exhausted | 79.29 -> 92.86   |
| fn_2_42FC8  | exhausted | 98.33 -> 99.13   |
| fn_2_42EB0  | exhausted | 95.07 -> 95.43   |
| fn_2_42BE8  | exhausted | 92.97 -> 99.63   |

readability pass: fn_2_44E2C done (kept the original's unchanged row write-back with a comment).
Enum-shaped left alone: StarMissionDisplayRule.mode values (1, 2, 0x12, 0x15, 22, 24-26), ScoutFlagTable._2/_3.

## Hypothesis log
fn_2_44504 (42.31)
  [1] s16/s32 *array-index* macros (((s16 *)p)[0x1977A2/2 + i]) instead of *(s16 *)(p + off + 2*i) -> 76.4
      (byte-offset forms, &p[off] and 2*i+off all compile alike and hoist the constant; only the typed index form gives addis/addi/sthx)
  [2] phase-8 pairs written to 0x197458 base (SORTED_KEY(m)), `i < k + 1`, non-sentinel branch first, re-read LIST_A(i) for the value -> 99.0
  [3] (s32) casts on the u8 recruitment/scout bytes (target cmpwi) -> kept
  [4] recruitmentStatus displacement form (target add+lbz 0x31; ours addi+lbzx): &tr-> form, raw byte offset (worse), inline isRecruited -> no gain
  left: that addressing in the recruited loop + register numbering.
fn_2_44E2C: pointer to requirementRow, row loaded through it and written back -> 100
Bool helpers (fn_2_44238/44368/442E8): target callers materialise the bool (neg/or/srwi, srawi/adde, cntlzw) and cmpwi 1.
  [1] u8 return + (s32) caller cast -> callers improve but 44368/442E8 standalone regress; s8 return worse.
  [2] `return (cond) ? TRUE : FALSE;` -> callers keep the materialised bool, standalone still 100. KEPT (all three).
fn_2_430F4 (79.29): switch(mode) with case 2 before 0x15; fn_2_44238(minStars) == TRUE (real helper, inlined) -> 93.96
  left: register numbering (DisplayRules base lands in r0 in ours).
fn_2_4358C (90.82): mode-3 is a switch on type (0x49, 0x42); s8 reads of work+0x197843; settings[0x36] tested after 0x197843; int bit mask; target == captain order -> 94.6
  [1] declaration order i/j -> no change. left: register numbering.
Family (42BE8/42EB0/42FC8/430F4/432EC/43404/439D0/43E8C/44014): `type` read before `mode` (+1.7 on 439D0); (s8) shownOnPauseMenu (except 42EB0 where it scores lower);
  `rule->_8` hoisted to a local in 42BE8; req/rule declaration swap no effect; walking cs pointer helps 43E8C only (kept there), hurts all others.
  Remaining is the same IV numbering in all of them (target: cs=r3, i*0x34=r4, i=r5; ours shifted).
