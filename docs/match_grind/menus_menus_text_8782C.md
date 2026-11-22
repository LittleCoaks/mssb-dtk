# menus/menus/text_8782C checkpoint

Session 1 end: unit 85.29 (commit 43d18fd3).
Baseline (session 1 start): unit 74.83 fuzzy; .text 74.30, .data 99.20 (jump table 2F96C differs).

| function   | status  | pct (before -> now) |
|------------|---------|---------------------|
| fn_2_8782C | matched | 54.64 -> 100 |
| fn_2_87998 | pending | 74.18 |
| fn_2_87FB0 | pending | 63.86 -> 96.66 |
| fn_2_88250 | pending | 70.94 -> 96.12 |
| fn_2_883C8 | pending | 85.26 |
| fn_2_887F8 | pending | 81.51 |
| fn_2_88D90 | pending | 65.15 -> 91.93 |
| fn_2_89038 | pending | 77.63 |
| fn_2_895F8 | pending | 63.39 -> 94.72 |
| fn_2_8975C | pending | 63.03 -> 93.37 |
| fn_2_89F70 | matched | 94.34 -> 100 |
| fn_2_8A008 | pending | 86.16 |
| fn_2_8A824 | pending | 64.14 |
| fn_2_8ABFC | matched | 88.82 -> 100 |
| fn_2_8AC84 | matched | 100 |
| fn_2_8ACB0 | matched | 100 |
| fn_2_8ACDC | matched | 100 |

## Findings
- 8ABFC: `lwz r31, currentDrawingItem@l(rX)` (direct, folded) = the value was an argument to a
  static inline (setupScene(currentDrawingItem)); a plain local initialiser gives addi+lwz 0.
- 89F70: lbl_2_data_2ECE4 is 4 descriptor lists (END at entries 69/78/86/92); separate static
  arrays get pooled off the .data base (target reloc lbl_2_data_2E9F8+0xDCC). symbols.txt split.
- 8782C: one 15-iteration loop with `int i` (no guard), store via `(u8*)base + 0x2DA0 + i*4`,
  post-loop `i++; tbl[i]` twice.
- 895F8: ret var + per-case assignment gives r3 preloaded/blr returns.

## Hypothesis log
fn_2_895F8
  baseline: 63.39
  [1] add explicit case 0 / case 1 returns, ret var + ternary              -> 78.6
  [2] both loads unconditional (sel = cursor; alt = bss; if (useLocal) sel = alt) -> 85.4
  [3] `return N` -> `ret = N; break;`                                       -> 94.49
  [4] ret = 0 after the if                                                  -> 94.72 (kept)
  [5] s32 types, decl swaps, `!= FALSE`, empty-then if                     -> no gain
  remaining: target schedules `li r3,0` between the loads and the beq, and `lis menuCursors` first.

shared step-callback shape (88250, 87FB0, 88D90; probably also 883C8/887F8/89038/87998)
  [1] static inline sceneRecord(node, idx) -> graphicsRelatedArray[firstHandle + idx]  -> +20-25 pts
      (stops the +7 offset folding into the base)
  [2] static inline isEqual(a,b) { return a == b ? TRUE : FALSE; } for the step-byte tests -> cntlzw form
  [3] idx param as int/u32/s16, idx + firstHandle, ptr arithmetic, handle-arg helper, (slot, off) helper -> all worse or no change
  remaining: target adds `firstHandle + slot`, ours `slot + firstHandle` (register naming).
  87FB0 BUG FIXED: rec(slot+0x42)->flags &= ~2 (draft had ~3).
fn_2_88D90: [1] helpers + `done == TRUE` -> 91.93; [2] i*3 / 0xE + 3*i / +0+1+2 forms -> no change
  remaining: target keeps one 3*i induction var plus offsets; ours keeps three (0xE/0xF/0x10).
next: apply the same helpers to 883C8, 887F8, 89038, 87998, 8A824 (biggest gaps), then 8A008.
Readability: not done for any function in this file yet (8782C/89F70/8ABFC are 100% but still use raw
offsets into lbl_2_bss_33FBCC / menuCursors / lbl_80354768; no struct exists for these).

## Session 2 (Opus): 85.29 -> see table; .data 100 (jump table matches after 8A824 rewrite)
| function   | status  | pct |
|------------|---------|-----|
| fn_2_8A824 | pending | 64.14 -> 97.17 (case 0x4D = fn_2_88250 inlined; residual = add operand order) |
| fn_2_87998 | pending | 74.18 -> 93.84 |
| fn_2_89038 | pending | 77.63 -> 94.04 |
| fn_2_887F8 | pending | 81.51 -> 94.25 |
| fn_2_883C8 | pending | 85.26 -> 99.25 (only fh+i operand order) |
| fn_2_8A008 | pending | 86.16 -> 92.36 |
REAL BUGS fixed: 8A824/8A008 cleared flags with ~3 instead of ~2 (UI_FLAG_VISIBLE) [21 sites];
 89038 partner-icon block belongs inside the "can play" test; 887F8 wait pass checks the partner
 record for the selected slot too (two ifs, not else-if).
Original-game oddities reproduced: 8A008 memsets an unused u8[3], leaves `sel` uninitialised when
 the CHAR_ID is not in lbl_2_data_2F964, and writes table[0x441D] back to itself.
Findings:
- "can play" test is `(s8)b1606 == 0 || ((s8)b1606 != 0 && b441B != 0)` (double extsb.).
- digits: `rem = value - d0 * 100; d1 = rem / 10; d2 = rem - d1 * 10` (887F8/87998, s32/u8 arrays);
  89038 uses `(s8)digits[0]` in d1 and unsigned digits in d2.
Hypothesis log (shared residuals):
- fh + i operand order (target `add rD, fh, i`; ours `add rD, i, fh`): tried REC_OBJ macro vs inline,
  `idx + fh`, (s32)/(u16) casts on fh, `(&arr[fh])[idx]` (-30pts), REC_AT(slot, off) macro (-20pts).
- 3*i + C: target keeps one 3i induction + offsets, ours one induction per constant (8A008, 88D90,
  87998/89038 3i+j): tried i*3, C + 3*i, (3*i+j)+C, j+(3*i+C) (89038 +0.36 only), literal left-assoc.
next: 8A008 j-loop/sel registers; 8975C (93.4), 88D90, 895F8 per session-1 log.

## Session 3 (Opus): 94.80 -> 95.79
| fn_2_8975C | pending | 93.37 -> 99.81 (only the fh + i add-operand-order residual left) |
fn_2_8975C
  [1] no cached `lbl = lbl_2_bss_33FBCC` pointer: the target re-materialises the global's address -> 99.01
  [2] case 0x52's reset test is `isEqual(maybeCheckAndResetGrapicsElement(...) != 0, TRUE)` (neg/or/srwi + cmpwi 1) -> 99.61
  [3] `n` uninitialised (no `= 0`): the switch on lbl[5] covers 0..3 only; original leaves n unset otherwise (quirk kept) -> 99.81
Remaining functions all show the logged fh + i add-order residual; the other per-function diff lines
are the register renaming that follows from it (checked 88250: every other diff line is a renamed register).
