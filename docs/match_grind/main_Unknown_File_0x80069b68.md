# main/Unknown/File_0x80069b68  [S1] (title / boot-sequence scenes)

Baseline (rep_c22): empty source, 0%. After [S1] session 2: .text 89.09%, ALL 14 functions drafted, every size equal to the target.

| function | status | pct |
|---|---|---|
| fn_80069B68, fn_8006AF6C, fn_8006B668, fn_8006C088 | matched | 100 |
| fn_8006AC24 | pending | 98.95 |
| fn_8006A824 | pending | 97.35 |
| fn_8006B230 | pending | 94.66 |
| fn_8006BE00 | pending | 93.25 |
| fn_8006A194 | pending | 88.04 |
| fn_80069BDC | pending | 85.53 |
| fn_8006AF9C | pending | 84.27 |
| fn_8006BB60 | pending | 81.38 |
| fn_8006A500 | pending | 81.47 |
| fn_8006B78C | pending | 78.32 |

next (all): register allocation / store order; the GX draw routines (69BDC/A194/A500/A824) differ in how the colour byte is
converted once vs per vertex (target converts the alpha float with fctiwz per vertex). fn_8006B78C / fn_8006BB60 use a shared
"fade record" macro whose field-store order (target stores +8, +0xC, +0x10, +0x18, +0, +4) is only approximated.

readability pass: done where evidence exists (fn_80069B68/AF6C/B668/C088 keep raw item offsets: the scene node here is a
DrawingSceneStruct with task-private fields at +0x14..+0x3C that no struct names yet). Enum-shaped, left alone: the state
machine values in item+0x34, changeScene(1/3, ...) scene ids, diskReadRelated id 0x16, boot-sequence step numbers.

## Findings
- Title/boot flow: fn_8006BE00 (loads logo textures into ARAM, picks fn_8006BB60 / fn_8006B78C / fn_8006B668 by
  lbl_80366158[0x29]), fn_8006BB60 + fn_8006B78C are the logo fade sequences (they fill a 0x20-byte fade record at item->0x18 +
  drawStadiumRelated*0x20 and hand it to fn_800A7D4C, which draws it with fn_8006AC24), fn_8006B668/fn_8006B230 the title
  screen with fn_8006AF6C/AF9C the intro-movie player (BootSequenceFiles, movie decoder fn_800AD*).
- fn_8006AC24(record) dispatches on record[8]: 0 -> fn_80069BDC (two cross-fading textures), 1 -> A824, 2 -> A500 (centred
  texture), 3 -> A194 (fixed quad), 4 -> a black full-screen fade quad. GX state is set with literal enum values.
- fn_8006AF9C case 3 deliberately falls into case 4 (the target does): only the START button (0x1000) skips to case 5.
