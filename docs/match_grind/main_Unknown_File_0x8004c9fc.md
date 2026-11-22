# main/Unknown/File_0x8004c9fc  (CSS TU)  first pass [S1] done

Baseline (rep_c20): 33.45%, 8/34 at 100%.  After [S1]: 86.16% .text, 16/34 at 100%, all 34 functions drafted.
Section: .text 86.16, extab 94.3; .data/.sdata have no C data (externs only; asm links them).
Flags: -cpp_exceptions on (configure.py), -inline auto (not deferred); functions in address order.

| function | status | pct |
|---|---|---|
| fn_8004C9FC, fn_8004CA08, fn_8004CA14, fn_8004CA48, exitMenu, fn_8004CC18, set803c5f77, fn_8004CC4C | matched | 100 |
| challengeTransitionRelated, storeCursorLocOrCharIDs, add_or_RemoveCharToATeam, relatedToTransitions | matched | 100 |
| fn_8004FD64, fn_8004FDA0, addOrRemoveCharacterToTeam, fn_80050F78 | matched | 100 |
| fn_8004CCC0 | pending | 97.11 |
| fn_8004D0F0 | pending | 97.47 |
| fn_8004D460 | pending | 84.44 |
| fn_8004D4F0 | pending | 99.43 |
| challengeCaptainSelect_returnsCharID | pending | 87.93 |
| fn_8004D990 | pending | 79.30 |
| fn_8004DB90 | pending | 87.63 |
| fn_8004E2EC | pending | 90.67 |
| captainSelect_processCursorMovement_getCharID | pending | 68.02 |
| fn_8004EEF4 | pending | 86.65 |
| fn_8004F10C | pending | 87.51 |
| fn_8004F964 | pending | 93.98 |
| fn_8004FDE8 | pending | 92.80 |
| cssLoadingRelated_1 | pending | 78.60 |
| charGrid_moveCursor | pending | 69.88 |
| css_initValues | pending | 90.40 |
| fn_8005138C | pending | 88.43 |
| fn_80051D00 | pending | 93.75 |

## Findings
- Scene tasks (fn_8004CCC0 text popup; fn_8004DB90/E2EC challenge-captain 6 slots; fn_8004F10C/F964 captain 12 slots;
  fn_8005138C/51D00 character-select 36 slots) all use item+0x14 firstHandle -> graphicsRelatedArray records (UIRecord
  frame>>16, playMode, flags bit 2 visible, anchorSub) and item+0x1C u16 phase. CSS_CAPTAIN_RECORD(n) macro.
- Target accesses ALL of lbl_800FCA60's sub-objects (icons table +0x1424, captain map +0x1B74, nav +0x1B80, variants +0x1EDC,
  descriptor lists +0x14E8/+0x1BA4/+0x1F0C/+0x0, layout tables +0x204C/+0x2090) off ONE base register, so the original
  source had them in one object. charGrid_moveCursor and captainSelect_* now use lbl_800FCA60+off macros; other fns in the
  unit (cssLoadingRelated_1, css_initValues, storeCursor..) use separate symbols in the target (characterIconsOnCSS etc).
- `i + const` record indices computed once per iteration (locals r23/r3/r35...) matched better than inline (83 -> 87.5).
- setInsertedValues is called without clrlwi on s16 args in fn_8004CCC0 (cast to s16-proto function pointer; target calls
  an unprototyped/s16 callee). text.c's definition takes u16.
- fn_80051D00 reads g_d_GameSettings.exhibitionMatchInd (byte 8): 0 -> g_Challenge.charIsSuperstar[], else superstarUnlocked[].
- Loops over the 4 ports with an unrolled chain and a `cs[0x78+cs[0x8d]]` fixed index appear in fn_8004DB90 (target re-reads
  0x8D every unrolled step; likely an original-game quirk: wrong index variable). Kept as in target.

## Hypothesis log
[S1] fn_8004D460: target keeps a 0x20 frame with `stw r4,8(r1)`; values[4] array + 1-iteration loop did not reproduce the frame.
  next: probably an inlined 4-port helper called with 3 constant args; arg array address must escape or stay live.
[S1] fn_8004D4F0: 99.43%, only `addi` order (pointer vs index increment) in the search loop.
  next: try a pointer-walk loop (row[i]) or reorder increments.
[S1] fn_8004CCC0 97.11%: state machine ok. next: flags var init placement (r5 vs r9) and lis/addi order after text_initializeNewChannel.
[S1] fn_8004D0F0 97.47%: next: r5/r6 swap (elements/anchors locals), tail `unk01 in [0..6]` test compiled as subi/clrlwi/cmplwi 4 (try (u8)(x-1) <= 4 forms).
[S1] fn_8004DB90 / fn_8005138C / fn_8004F10C: logic identical (sizes equal); remaining diffs are register allocation / hoisting of i+const.
  next: try making per-iteration locals for the 4-port unrolled checks; check -inline deferred effect not needed.
[S1] captainSelect_...: logic verified against asm. Target has the 6-check slot search fully unrolled (while-style n<5) and
  the 12-iteration nav search unrolled x6 x2; ours is a loop in the left/right case. next: find the loop form MWCC unrolls.
[S1] fn_8004D990: target hoists li -1/-2 consts before the arg1 branch; ours loads them per branch. Tried s8 store macro (78.5, reverted).
[S1] charGrid_moveCursor: conditions split per target (cs[0x4C]!=0 && timer>=0 / slotTeam>=0 && timer>=0). next: logic after the
  state loop, register allocation (cs base in r28 vs r31).
[S1] cssLoadingRelated_1, css_initValues, fn_8004EEF4, challengeCaptainSelect_returnsCharID: pre-existing drafts, not re-touched.

## Open questions
- Names: unk01 of Unk803C5F74 is a text-popup type 0-10 (7/8/10 hide parts, 9 loads icon 0xCD); unk1D = shows sound 0x1C2.
- charSelectStruct raw offsets (0x74 team cpu flag, 0x78 per-port cursor state, 0x7C-0x7E scene state bytes, 0x7F port timers,
  0x8C/0x8D mode/port, 0x8E-0x92 scene flags) are CHAR_SELECT_BYTE() views; promote to CharSelectState fields when the menus REL
  side is reconciled (shared header include/Unknown/File_0x8004e5b4.h not touched).
- .data of this unit is not compiled from C (externs only).
