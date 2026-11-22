# menus/menus/rep_0AB0 (src/menus/rep_0AB0.c)

Baseline (session 1 start): unit 91.33%.

| function       | status  | pct    |
|----------------|---------|--------|
| fn_2_5AE54     | matched | 100%   |
| fn_2_5DC5C     | matched | 100%   |
| fn_2_5CB5C     | matched | 100%   |
| fn_2_5C5B8     | matched | 100%   |
| fn_2_5D26C     | matched | 100%   |
| fn_2_5AFB0     | matched | 100%   |
| fn_2_5AF24     | matched | 100% (already) |
| fn_2_5B7DC     | pending | 99.52% (untouched) |
| fn_2_5979C     | pending | 99.33% (untouched) |
| fn_2_5A224     | pending | 98.69% (untouched apart from PADW) |
| recordsScreen  | pending | 91.75% |
| fn_2_59CF8     | pending | 86.08% |

Session 1 end: unit 91.33 -> 98.04%.

## Hypothesis log

fn_2_5AE54
  baseline: 93.94%
  [1] `switch (NODE_U16(item = currentDrawingItem, 0x1C))` (assignment inside the switch operand) -> 100%
      (plain init / separate assignment: 92.98; dropping `case 1: break;` 87.1; if-form 86.6)

pad reads (file-wide)
  [1] new macro PADW(i, off) = ((u16 *)((u8 *)&AtBat_ButtonInput1 + off))[i * 16] (u16-indexed) helps
      5A224/5AFB0/5B7DC/5C5B8/5CB5C/5D26C/5DC5C; the byte-offset PADH form must stay for 5979C/59CF8 (they drop 14/8 pts with PADW).

fn_2_5DC5C
  baseline: 96.01%
  [1] re-read the controller index (s8)WB(0x197863) at every pad test instead of caching it; PADW -> 100%
  readability pass: done (INPUT_BUTTON_UP/DOWN/A/B)

menu state machines (5CB5C, 5C5B8, 5D26C, 5AFB0) - shared recipe, all -> 100%
  - no cached `item = currentDrawingItem` (target never loads it at entry); use currentDrawingItem at the use sites
  - UP/DOWN + A/B cursor blocks: re-read PADW((s8)WB(0x197863), off) at every test; `if (WBH(0x1976FE) == k) WCH = a; else WCH = b;` not a ternary
  - L/R/B trigger blocks: pad cached once (`pad = PADW(idx, 2)`), but store order is WBH(0x197730), WCH(0x32), then the WA flags
  - merged `case 0: case 1:` must be split into duplicate bodies (5CB5C)
  - loop bounds `*(u16 *)(lbl_2_bss_340140 + 0x3078)` re-read each iteration (5D26C)
  - modular decrement written `(-1 + n + v) % n` (5AFB0)
  behaviour bugs fixed: 5CB5C state 3 lacked the B-button branch (-> state 7); 5D26C ran the 0x307A==3 refresh
  calls only from state 23 instead of after the switch every frame.
  original quirk kept: 5AFB0 state 12 cursor 3 stores WCH(0x32)=13 and the post-switch reset overwrites it with 0.
  readability pass: INPUT_BUTTON_* / INPUT_TRIGGER_* on every touched pad test.

recordsScreen
  baseline: 91.75%
  [1] global pointer init order sweeps (target emits 824C,8248,8244,8240,823C,8234,8230,340140,3401BC) -> no gain (89.3-90.2 diff view)
  residual: register assignment of the init block (target keeps &lbl_2_bss_1A824C in r27, w in r26).

fn_2_59CF8
  baseline: 86.08%
  [1] fill loops: buf[i + 0xCF18] / lbl_80354768[...] / (buf + 0xCF18)[i] / s32 i -> all worse (73.8 / 68.6 / 73.8 / 78.1 diff view)
  residual: target computes (i + 0xCF18) then adds buf per 8-store chunk; the =0 loop stores eight separate zero registers.
  NOTE: keeps the byte-offset PADH macro; PADW costs it ~8 points.
