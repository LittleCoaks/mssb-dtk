# camera.c — match grind checkpoint

Unit: `game/game/camera/camera`
Module: game (REL)
Started 2026-11-15, from the "cos/sin family" found by `tools/match_families.py`.
Companion log of machine-built variants: `game_game_camera_camera.sweep.md` (do not repeat those by hand).

## The family

Five functions fail on the same four-row window: `radianAngleReduction`/`shortAngleToRad_Capped` -> `cos` -> `sin`
-> `cos` -> `sin`, with the callee-saved FPRs permuted. Instructions and order are identical; only the register
numbers differ. Members: `fn_3_1045A8` (camera_script.c), `cameraRelated`, `gameplay_Camera`, `cameraControl`,
`fn_3_19FA4` (camera.c).

| function | unit | status | pct |
|---|---|---|---|
| fn_3_1045A8 | camera_script | matched | 100% (declaration order, see camera_script checkpoint) |
| cameraRelated | camera | pending | 99.94% |
| gameplay_Camera | camera | pending | 98.4% |
| cameraControl | camera | pending | 99.6% |
| fn_3_19FA4 | camera | pending | 96.5% |

## What is known

* The target allocates the same source pattern DIFFERENTLY per unit (in `camera_script.c` `reach` does not reuse
  `pitch`'s register; in `camera.c`'s `cameraRelated` it does), so the original sources were not identical and one
  fix will not carry across files.
* In `camera.c` the pattern is not written in these five functions directly. It lives in standalone helpers
  (`fn_3_16900`, `fn_3_1785C`, `fn_3_161C0`, `fn_3_16058`, ...) that the compiler also inlines into
  `cameraRelated` (objdiff's source line for those rows is the call line). The standalone copies already score
  100%; only the inlined copies differ. A change to a helper therefore has to keep the helper at 100% and fix the
  host at once.
* `fn_3_1C8AC_inline_2` (camera.c:368) is defined but never called.

## Hypothesis log

fn_3_1785C + cameraRelated (objective = average of the two; baseline 99.97)
  [S2] all 719 declaration orders of `_f31,f30,_f30,_f29,_f28,_f6` (`match_sweep.py --perm --with cameraRelated`)
       -> best 99.97 (same as baseline), the rest worse. No ordering of this helper's float locals helps.
fn_3_16900 + cameraRelated
  [S2] `--perm` produced 0 variants: its float locals are declared inside an `else` block, and the rule only
       permutes the declarations that open the function body.

## Next

1. Teach `match_sweep.py`'s `perm` rule to permute the declarations that open a NESTED block (`fn_3_16900`'s
   `else { f32 _f31; ... }`), then sweep it with `--with cameraRelated`.
2. Try the host side: `cameraRelated` declares only `u8 status; u8 secondaryMode;`. Locals added or reordered in the
   host change the colouring of every inlined copy at once; sweep them with `--perm` once a candidate exists.
3. `gameplay_Camera`, `cameraControl`, `fn_3_19FA4` have not been examined beyond the family match; start with the
   smallest, `gameplay_Camera`, and look at which helper it inlines.
