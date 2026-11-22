# menus/menus/text_82CF0 checkpoint (first pass, Sonnet)

Baseline unit fuzzy 68.94 -> now 86.21

## Method / findings (session S1)
- Unit was already drafted (no empty stubs); the existing drafts were logic-correct but structurally off. Work was rewriting
  to the target's shapes.
- **Consecutive record accesses are loops.** Target blocks of the form `lhz; addi rN,rN,k; slwi; lwzx` for handles k..k+n
  (unfolded, twice-used) come from `for (i = a; i < b; i++)` which MWCC unrolls; constant-index straight-line code gets the
  base hoisted instead (`addi r9,r6,0x30`). Fixed fn_2_82EC0 (0x61 state), stadiumRandomRelated (6..11 reset), fn_2_84388 (6..11 alpha).
- `3 + scene->firstHandle + cursor` (const first) reproduces the target's `add h,cursor; addi 3` order; helpers
  `stadiumRec`, `stadiumSlotRec`, `stadiumCursorRec` added.
- Globals accessed through a cached local pointer (`u8 *step = lbl_803CBBC4`) lose the target's repeated `lis/addi` and the
  `cntlzw; srwi.` BOOL tests; use the global directly and `stadiumStepIsClear/IsSet` inlines.
- `(count = f(..) != 0) == 1` reproduces the `neg/or/srwi; cmpwi 1` normalisation after maybeCheckAndResetGrapicsElement.
- Compiled `switch` inside `switch` (cardCheck state) fixed fn_2_854B0 (99.85, only the unowned jumptable name differs).
- Real bug fixed: fn_2_84388 wrote `frame = 1` for the cursor record; target stores 0x10000.
- `lbl_2_data_2E2EC` retyped s8 (the -1 store needs it; target `li r0,-1`).
## next: lines (pending)
- stadiumRandomRelated (62%, 1632 B): reset loop (6..11) done; the rest of the draft is structurally off (target saves r25..r31, builds
  `flag = tbl[...]==1 && superstarUnlocked[0xF5]==0` via inline BOOL calls and keeps menuCursors in r31). Rewrite from the asm.
- fn_2_845A8 (68.7%, 2560 B): draft diverges early (missing blocks, many record sequences that are loops); rewrite state by state.
- fn_2_84388 94.6 (register order only), fn_2_851A8 96 (const 0xB4 held in r31 across the call, extra `bge` after the first switch),
  stadiumScreenAnimations_maybe 95.7 (node load order), fn_2_837D8 98.4, loadStadiumScreen_maybe 97.5 (store order r4/r5/r6).
- Real bugs fixed: fn_2_84388 frame 1 -> 0x10000; stadiumScreenAnimations_maybe load_Icon args swapped (element/frame).


## Status table (only functions below 100% at baseline or now)

| function | size | status | before -> now |
|---|---|---|---|
| fn_2_845A8 | 2560 | pending | 68.37 -> 69.12 |
| stadiumRandomRelated | 1632 | pending | 59.62 -> 62.86 |
| fn_2_82EC0 | 1584 | matched | 6.04 -> 100.00 |
| fn_2_84388 | 544 | pending | 80.65 -> 95.32 |
| fn_2_84194 | 500 | matched | 98.67 -> 100.00 |
| fn_2_83974 | 448 | matched | 98.53 -> 100.00 |
| fn_2_85310 | 416 | matched | 87.93 -> 100.00 |
| fn_2_837D8 | 412 | pending | 96.79 -> 98.39 |
| fn_2_854B0 | 396 | matched | 83.74 -> 100.00 |
| fn_2_851A8 | 360 | pending | 82.31 -> 95.94 |
| stadiumScreenAnimations_maybe | 352 | pending | 96.08 -> 96.19 |
| loadStadiumScreen_maybe | 84 | pending | 98.00 -> 98.00 |
| fn_2_85160 | 72 | matched | 98.89 -> 100.00 |

## S3 session (Opus)
NOTE: per-unit `objdiff diff` numbers differ from `report generate` numbers for this unit (report: fn_2_854B0 100, diff 99.85).
- stadiumRandomRelated 62.35 -> 90.90 (diff numbers): redecompiled from asm. Structure: reset loop 6..11; `if (cd[0] != 0) { if ((s8)cd[1] == 0) {...
  arg = (s8)tbl[0x954]; } } else {...}`; both inner selections are `if ((s8)tbl[0x954] == -1) {arg} else {prev}`; s16 icon local;
  stadiumIsLocked(tbl, menuCursors[0x11]) BOOL inline (flag=FALSE; if(..) flag=TRUE); count/need zeroed before the cd[1] check.
- stadiumRandomRelated -> 93.92: icon table read as `(lbl_2_data_2D998 + 0x2EC)[i]` (constant-address base; an `icons` pointer local 91.45,
  `tbl[0x2EC + i]` folds to add+lbz 90.9, inline param also folds); prev-icon select as if/else (no BOOL temp); arg+6 record via
  stadiumCursorRec(scene, 6, arg); `s32 need; s32 count;` order. Left: target CSEs tbl+0x2EC into r28 only inside the cd[0]!=0 branch and
  re-derives `addi r3,r29,0x2ec` per use elsewhere; ours hoists into callee-saved regs.
- fn_2_845A8 68.71 -> 98.38 (pending): redecompiled. Cases in the target's text order (0x27, 0x24, 0x26, 0x25, 0x31, 0x28); 0x27 rgba
  as `for (i = 6; i < 12; i++)`, cursor local read once; 2-term counts as `count = a != 0; if (count + (b != 0) == 2)`; 0x954/0x955
  stores through s8 (li -1); tail: separate `== 0x25` / `== 0x24` returns, cursor read before the screen check, `icons = tbl + 0x2EC`
  local, `(s32)u16 > 0x12C` (cmpwi). Left: callee-saved numbering (scene r28 vs r27; loop i*6/i*100/icons/cursor/label permuted),
  lis order of lbl_2_data_2D998 in the prologue, menuCursors load scheduling in case 0x27.
- loadStadiumScreen_maybe 97.52 -> 100 (matched): `menuNumber[0] = 5;` first (MWCC then emits the [9] store first).
- fn_2_837D8 98.39 -> 100 (matched): two-term count as `count = a != 0; if (count + (b != 0) == 2)`; readability: stadiumRec + UI_PLAY_*.
- fn_2_84388 94.63 -> 100 (matched): cursor local read between the rec0 and rec4 stores; count form. Same placement in 845A8 case 0x27 -> 98.88.
- fn_2_851A8 95.94 -> 100 (matched): inner switch gets an empty `case 3: break;` before `case 4:` (target tree `cmpwi 4; beq; bge; b`); `insertGraphicDrawingFunction(..)->state = 0xB4` directly.
- stadiumScreenAnimations_maybe 95.68 -> 100 (matched): `addGraphicsElementToScene(node = currentDrawingItem, ...)` with node declared last (folded lwz @l into r31).

## Status after S3 (report numbers; unit 86.21 -> 98.83)
| function | status | before -> now |
|---|---|---|
| stadiumRandomRelated | pending | 62.86 -> 94.05 |
| fn_2_845A8 | pending | 69.12 -> 98.95 |
| fn_2_851A8 | matched | 95.94 -> 100.00 |
| loadStadiumScreen_maybe | matched | 98.00 -> 100.00 |
| stadiumScreenAnimations_maybe | matched | 96.19 -> 100.00 |
| fn_2_84388 | matched | 95.32 -> 100.00 |
| fn_2_837D8 | matched | 98.39 -> 100.00 |
