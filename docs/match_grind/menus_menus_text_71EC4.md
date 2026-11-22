# menus/menus/text_71EC4 checkpoint (Opus pass)

Unit fuzzy 82.01 -> ~90.0.

| function                          | status    | pct            |
|-----------------------------------|-----------|----------------|
| fn_2_72A58 / 728C0 / 729E0 / 72D60 / 72DDC / 73758 | matched | -> 100 |
| fn_2_7308C                        | pending   | 70.74 -> 95.37 |
| fn_2_72A88                        | pending   | 83.96 -> 94.93 |
| fn_2_72E54                        | pending   | 73.68 -> 90.04 |
| fn_2_72814 / 72CB4 / 7293C        | pending   | 83 -> 89.5-90 (scene/address register swap) |
| fn_2_7207C                        | pending   | 78.79 -> 83.86 |
| fn_2_73CBC                        | pending   | 80.54 -> 82.34 |
| fn_2_73994                        | pending   | 69.51 -> 79.09 |
| fn_2_73EFC                        | pending   | 83.91          |
| fn_2_7302C                        | pending   | 54.58          |
| fn_2_73B94                        | pending   | 91.30          |
| fn_2_72594                        | pending   | 90.26          |
| fn_2_71F60                        | pending   | 92.94          |
| cssCheckSomethingAboutCharacters  | pending   | 96.09          |
| fn_2_73BF0                        | pending   | 96.08          |

readability pass: done for the matched step functions (selectionFlagIs / cursorLockStateIs helpers).
lbl_803CBBC4 = selection step flags ([0] step id 1/2/3/0x47, [2] started, [3] waiting, [4] done) - enum-shaped, no enum.

## Hypothesis log
- Bool tests: the target materialises `flag == k` (cntlzw/srwi.) before branching. Only works when the test reads the
  *global* (lbl_803CBBC4[i] / gameSetUpStep...) through `(x == k) ? TRUE : FALSE` (helper selectionFlagIs/cursorLockStateIs).
  A local `u8 *flags = lbl_803CBBC4` pointer, a plain `!=`, or a helper taking the byte value all fold back to cmplwi.
- fn_2_7308C: the draft's phase helpers were hand copies; the target inlines the real fn_2_72E54+72DDC (step 1),
  728C0+72814 (2), 72A88+72A58 (3), 72D60+72CB4 (0x47). The pairs 728C0/72D60 and 72814/72CB4 are byte-identical,
  so which of each the original called is a guess.
- graphics records: index graphicsRelatedArray[...] directly (GFX_RECORD) so `firstHandle + K` folds K into the base
  (addi base,8 / lwz 0x10). The int-parameter helper gfxRecord blocks the fold; kept only where it scores better
  (fn_2_73994, fn_2_73EFC via rowRecord).
- fn_2_73B94 is inlined into fn_2_73CBC: changing its if/else chain to early returns cost 73CBC (reverted).
- fn_2_7302C: target loop is not a ctr loop (b to the test, cmpw i,bound; blt). for/while/break/bound-inline variants
  all give the ctr form (54-59%). Unknown construct.
- fn_2_73994: Static_Stats table indexed inline (no table local) -> 79; left: (firstHandle + idx) + K not folded,
  same open question as text_744C8 fn_2_7630C.
next: fn_2_7207C (1304 B, 4 cntlzw tests), fn_2_73EFC, fn_2_7302C loop shape.
