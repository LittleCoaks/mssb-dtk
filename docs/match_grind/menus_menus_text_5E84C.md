# menus/menus/text_5E84C checkpoint (Opus pass)

Unit fuzzy 81.94 -> 99.70.

| function    | status    | pct            |
|-------------|-----------|----------------|
| fn_2_5F458  | matched   | 42.87 -> 100   |
| fn_2_5FDC4  | matched   | 73.15 -> 100   |
| fn_2_6051C  | matched   | 69.47 -> 100   |
| fn_2_5E84C  | pending   | 97.04          |
| fn_2_5EB78  | pending   | 97.62          |
| all others  | matched   | 100            |

readability pass: done for the three (no enums apply: unitIndex, element/frame IDs are icon-sheet indices).
Quirk kept: fn_2_5FDC4 leaves `value` unset for unitIndex outside 0..7 and still draws it (commented).

## Hypothesis log
Digit drawing: the original writes each count explicitly. Blanked forms (drawBlanked3/4) compute every digit, then blank the
  leading ones (`if (value < 100) ...`), then call load_Icon per part; plain forms (fn_2_5F458 cases 1, 2, 5) compute each
  digit in the load_Icon argument with no blanking. The old loop-based drawNumber/drawFourDigits were wrong for all of them.
  Declaring the digit locals `tens, hundreds, (thousands,) ones` fixes the callee-saved order.
Values are s32 holding an s16 load (no repeated extsh); the s16 tables are indexed as ((s16 *)(work + off))[i] (target adds
  i*2 to the base and uses off as the displacement).
fn_2_5F458: inner switch(unitIndex) cases 0..5 in order; outer empty cases must be `1, 3, 4, 0x25` (as in the siblings) to get
  the target's compare tree (root 5). Without 4: root 4 (99.8).
next: fn_2_5E84C / fn_2_5EB78 are register-only (stwx base/index swap in the copy loop).
