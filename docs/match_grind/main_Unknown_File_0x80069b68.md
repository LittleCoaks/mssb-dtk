# main/Unknown/File_0x80069b68  [S1] (title / boot-sequence scenes) -- PARTIAL

Baseline: empty source, 0%. After [S1]: 4 of 14 functions drafted, all four at 100% (.text 5.5%). Link ok.
Not drafted (still link from asm): fn_80069BDC (1464), fn_8006A194 (876), fn_8006A500 (804), fn_8006A824 (1024),
fn_8006AC24 (840), fn_8006AF9C (660), fn_8006B230 (1080), fn_8006B78C (980), fn_8006BB60 (672), fn_8006BE00 (648).

| function | status | pct |
|---|---|---|
| fn_80069B68, fn_8006AF6C, fn_8006B668, fn_8006C088 | matched | 100 |
| the ten functions listed above | pending (not drafted) | 0 |

readability pass: pending for the four matched (enum-shaped: scene ids in changeScene(3,0), item state values 0/4/5/6 of fn_8006B668).

## Findings
- fn_80069B68 loads the title-screen textures (diskReadRelated desc, 0x16), spawns fn_80069B08 + the lbl_80109378 element list.
- fn_8006B668 is the title scene state machine (item+0x34 state: 0 start fn_8006B230 + changeScene(3,0); 5 -> fn_8006AF9C;
  4/6 -> fn_8006AF6C when item+0x3B is set). fn_8006AF9C (BootSequenceFiles) uses ~10 unprototyped helpers (fn_800AD*/fn_800ADB04...,
  _OSAllocFromHeap) so was not drafted.
- fn_8006C088(widescreen) selects lbl_8010928C / lbl_80109250 as the VI render mode and reconfigures VI.
