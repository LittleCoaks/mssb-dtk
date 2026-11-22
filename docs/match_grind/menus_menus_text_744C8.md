# menus/menus/text_744C8 checkpoint (Opus pass)

Unit fuzzy 80.46 -> 86.0 (session 1, second commit).

| function                          | status    | pct            |
|-----------------------------------|-----------|----------------|
| fn_2_76650                        | pending   | 97.52          |
| fn_2_7664C                        | matched   | 100            |
| fn_2_7630C                        | pending   | 65.54 -> 75.93 |
| fn_2_760CC                        | pending   | 67.91 -> 77.76 |
| fn_2_7609C                        | matched   | 100            |
| fn_2_76098                        | matched   | 100            |
| teamSelectionSetChemStars         | pending   | 66.68 -> 80.25 |
| fn_2_75B58                        | exhausted | 84.40          |
| gfx_cssCharStatBars_and_sthgElse  | pending   | 83.14 -> 84.64 |
| fn_2_74E14                        | pending   | 70.73 -> 84.93 |
| fn_2_74DB8                        | matched   | 100            |
| fn_2_74D8C                        | matched   | 100            |
| fn_2_74CD8                        | matched   | 91.56 -> 100   |
| fn_2_747FC                        | pending   | 87.26          |
| fn_2_7463C                        | exhausted | 89.15 -> 99.29 |
| fn_2_74564                        | exhausted | 82.96 -> 99.26 |
| fn_2_74518                        | matched   | 91.32 -> 100   |
| fn_2_744C8                        | matched   | 91.75 -> 100   |

readability pass: fn_2_744C8/74518 done (cursorLockStateIs helper; stepFlags[1][0] values 0/1/2 look enum-shaped, no enum).

## Hypothesis log
fn_2_744C8/74518: target materialises (flag == k) with cntlzw/srwi. before branching -> bool helper returning `(x == k) ? TRUE : FALSE` -> 100.
fn_2_760CC / fn_2_7630C: keep the Static_Stats star-ability byte (CharacterStats.stats.CaptainStarHitPitch, +0x34) in locals and
  index lbl_2_data_2B3A4 at each use (target re-reads it after load_Icon) -> +10 each. CHAR_STATS 2D cast form: worse (73).
  REAL BUG fixed: fn_2_7630C stored the star icon into gfx(team+0x8B)+0x68; the target stores 4 (same as fn_2_760CC).
  fn_2_7630C team chosen with if/else on g_d_GameSettings[0x10] (two loads), not slot=arg.
  left: gfx index adds. Target computes (firstHandle + team) + K before the shift (no displacement folding); every helper/macro
  form tried either folds K into the base (0x410) or adds team+K first. teamGfxObject(scene, team, K): worse.
teamSelectionSetChemStars: average computed outside the count guard and the star chain always evaluated; captainSelectedID is s32
  (signed compare); gfx lookups not cached -> 80.1. Index forms swept: direct `firstHandle + i + base + 0x6E` best (80.1);
  gfxObject(i+base+K) 64.7, gfxObject2(i, base+K) 70.2, gfxObject2(i+base, K) 59.2.
fn_2_74E14: gfxObject2(scene, c, a*4 + K) for the c-relative objects, gfxObject(scene, a + K) for the others -> 84.9.
fn_2_75B58: `i + base + 0x6E` argument order no change; declaration-order permutations max 85.7 (not kept).
gfxObject helper body `index + firstHandle` (operand order) -> +1.5 on gfx_cssCharStatBars, neutral elsewhere.
All file-local helpers made static inline (out-of-line copies were being emitted).
next: fn_2_74564 (82.96), fn_2_747FC (1244 B), gfx_cssCharStatBars (inlines fn_2_74E14-like blocks).
fn_2_74564/7463C: menuCursors[0] read into a function-scope local before the lock-state test (target loads it first);
  cursorLockStateIs(k) for the test -> 99.3 each. Left: `add` operand order (firstHandle, i) and IV numbering;
  local order permutations (best ready, hits, i), constant-first index, i at function scope: no further gain.
fn_2_74CD8: `addGraphicsElementToScene(node = currentDrawingItem, ...)` (target loads straight into r31) -> 100;
  a separate `node = currentDrawingItem;` statement or initializer gives lwz+mr (91.6).
gfxObject body operand order (`index + firstHandle`) reverted: no effect once the other changes were in.
