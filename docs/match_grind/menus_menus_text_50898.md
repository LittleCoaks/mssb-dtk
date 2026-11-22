# menus/menus/text_50898 checkpoint (first pass, Sonnet)

Baseline unit fuzzy 70.76 -> now 70.87

## Session S1 status
No empty stubs existed; all 38 functions were already drafted (raw STATE_BLOCK offsets). Only fn_2_5135C was reshaped this session
(42.3 -> 46.1: three u32 pointers at lbl_2_bss_55E8 +0/+8/+0x10 give the indexed `stwx` form; the target still orders the loads
before the base `addi`s). Everything else is untouched and listed below for the Opus pass; the time went to rep_0788 and text_82CF0.
## next: leads
- fn_2_52690 (3448 B, 53.8) and fn_2_51C58 (1100 B, 54.2) are the big ones.
- fn_2_50898 (268 B, 58.8): target keeps `0x6fe8 + n` bases in separate registers and a 0xA8-iteration guard; draft loops differ (use `for` with
  unrolled constant-offset stores).
- fn_2_50D40 (116 B, 58.8): target uses `lhzx/sthx` with a shared byte offset; draft uses lhzu-style pointer.
- Record accesses written as raw `*(u8 *)(STATE_BLOCK + off)`; apply the loop / helper findings from text_82CF0 and rep_0788
  (consecutive 0x..-stride stores are loops; first constant store in a record needs an inline helper).


## Status table (only functions below 100% at baseline or now)

| function | size | status | before -> now |
|---|---|---|---|
| fn_2_52690 | 3448 | pending | 53.77 -> 53.77 |
| fn_2_51C58 | 1100 | pending | 54.19 -> 54.19 |
| fn_2_52260 | 1000 | pending | 76.61 -> 76.61 |
| fn_2_5163C | 596 | pending | 86.21 -> 86.21 |
| fn_2_51A1C | 572 | pending | 83.29 -> 83.29 |
| fn_2_509A4 | 360 | pending | 98.89 -> 98.89 |
| fn_2_51890 | 352 | pending | 86.44 -> 86.44 |
| fn_2_51190 | 292 | pending | 62.52 -> 62.52 |
| fn_2_50898 | 268 | pending | 58.84 -> 58.84 |
| fn_2_51470 | 248 | pending | 85.24 -> 85.24 |
| fn_2_520A4 | 244 | pending | 69.92 -> 69.92 |
| fn_2_50B0C | 232 | pending | 98.02 -> 98.02 |
| fn_2_510A8 | 228 | pending | 80.16 -> 80.16 |
| fn_2_50FC8 | 224 | pending | 70.36 -> 70.36 |
| fn_2_52198 | 200 | pending | 91.00 -> 91.00 |
| fn_2_50E5C | 196 | pending | 88.06 -> 88.06 |
| fn_2_50F20 | 168 | pending | 91.19 -> 91.19 |
| fn_2_50DB4 | 168 | pending | 91.19 -> 91.19 |
| fn_2_512C0 | 152 | pending | 74.34 -> 74.34 |
| fn_2_513E8 | 132 | pending | 89.09 -> 89.09 |
| fn_2_5135C | 128 | pending | 42.31 -> 51.22 |
| fn_2_50D40 | 116 | pending | 60.69 -> 60.69 |

## S2 (Sonnet)
- fn_2_50898 58.84 -> 88.55: eight separate `*(s16*)(STATE_BLOCK + i*2 + 0x6FE8..0x6FF6) = 0` stores (not a shared `off`). Left: target keeps `cmpwi i,0xa8` unfolded guard before the ctr loop.
- fn_2_50D40: tried plain-global `count` pointer + do/while: 49.8 (worse), reverted. Target uses lhzx with a hoisted `base+0x401C` and a separate `idx<<1`; ours emits lhzu.
- fn_2_52690 (52.6): NOT just register noise. The draft's logic diverges from the asm from state 3 on (asm: state 5 is a sub-switch on B33[2] {0: fn_2_51890 + insertGraphicDrawingFunction(fn_2_89F70,0x3000), B33[0x22]=0x51; 1: if B33[0x22]!=0x51 fn_2_51C58; 2: fn_2_51A1C(?)...; 3: ST=8; 4: exitMenu}, whereas the draft puts fn_2_52260 in case 5). Needs a full redraft from asm (jump table jumptable_2_data_1F8A4: 0->526CC 1->52710 2->52854 3->52930 4->52A48 5->52A9C 6->52AD0 7->52B9C 8->52BA8 9->52CCC 10->52FF8 11->5302C 12->53280 13->531A0 14->5316C 15->532B4 16->532FC 17->53360). State 6 (52AD0) = the B33[2] sub-switch; 5 (52A9C) = the fn_2_52260 gate (draft's case 5 is right, its case 6 is wrong).
- Lead: target addresses `inningSetting+0x28` as a separate object (base +0x28, field +0x30 = scene mode/state); ours emits inningSetting+0x58. Needs a symbol at 0x800E877C in config/GYQE01/symbols.txt (shared, not done). Same lead for rep_0788 fn_2_20D08 and 52690.

## S3 session (Opus)
- Shared: `inningSetting + 0x58/0x5A` -> `g_MenuControl.sceneMode/sceneState` (new DOL symbol 0x800E877C, include/static/menu_control.h).
- fn_2_52690 52.69 -> 98.81 (pending): full redraft from the asm. Cases in numeric text order except 14, 13, 12 (target order
  11, 14, 13, 12, 15...). State 6 = sub-switch on B33_U16(2) {0: fn_2_51890 + insert fn_2_89F70, 0x22=0x51, ->1; 1: fn_2_51C58 unless
  0x22==0x51; 2/3: 0x22=0x52, 0xE=1, sub=0, 9E08=0xA/5; 4: fn_2_51A1C}. State 8: exitMenu switch with an empty case 0, cases in order
  1, 3, 2, 4. State 9 reads `s16 choice` (extsh.). Store pairs `9E08 = x; other = y` are emitted in REVERSE source order by MWCC
  (write the target's second store first). Real bugs fixed: old draft called fn_2_520A4 in state 6 (target never calls it) and cleared
  B33 offset 0 instead of the u16 at +2 in state 9 (non-4756 path).
  Left: case-1 menuNumber/lbl_800FEF70 scheduling, state-9 B10/BF/9E08 store order, an extra `b` after the state-11 B[6] switch.
- fn_2_51C58 53.33 -> 100 (matched): redrafted: `switch (state)` 0..5 with one trailing sndFX (not per branch); Static[0x4754] re-read
  each use (no t local); case 3 `B33(0xF) = Static[0x4754]; ...; memcpy(.., B33_S8(0xF) * 0x4508)` and the menuCursors[0x50] counter
  incremented in memory; case 4 order BF, 0x15, u16; cursor wrap `if (--state < 0)` / `if (++state == 6)`. PAD_BUTTON_* names.
  readability: done (PAD_BUTTON_A/B/UP/DOWN, B33 accessors).
- fn_2_52260 76.55 -> 100 (matched): redrafted with `if (--idx < 0)` wraps, A-branch inner test flipped (`if (BF != -1) { if (lbl[idx+0xCF5E] != 0) {0x29} else {save} } else {0x1B}`), s8 stores of -1, u8 mode local. readability: PAD_BUTTON_*.
- fn_2_50D40 58.79 (pending): target keeps count base (0x401C) and idx*2 apart (lhzx/sthx) and treats the count as int (no clrlslwi). Tried: dst[count[idx]++] = v = *src++ forms, do/while, constant-address count array, byte-offset local. All 49-53%.
- fn_2_5163C 86.00 -> 99.93 (pending): index the arrays directly (no walker locals); REAL BUG fixed: captainSelectedID[0] = g_Challenge[0x441D] is a single store before the loop (draft stored walker+0x441D every iteration). Left: lbz r8 vs lbz r0 for the (s8) cursor reread (tried ((s8*)..)[i] 91.8, s8 local 99.93, inline expr 96.4).
- fn_2_51A1C 83.25 -> 100 (matched): switch on B33_U16(0x12), inner exitMenu switch (empty case 0; order 1,3,2,4), ++B33(0x14) == 2, s8 -1 stores.
- fn_2_51890 85.02 -> 100 (matched): first test (s8), inner tests `!= 0` first, table indices re-read (no locals).
- fn_2_520A4 69.84 -> 100 (matched): switch on B33_U16(2); it is the standalone of fn_2_52690's state 6, so 52690 now just calls fn_2_520A4() (inlined, byte-identical).
- fn_2_50DB4 / fn_2_50F20 91.19 -> 100 (matched): `strings` pointer taken up front; `src = pickString(strings, arg1, src)` static inline with an early `return fallback` reproduces the target's `bne X; b end; X:` (empty-then) shape. Plain if / empty-then / ternary all 97.38.
  [S3] also tried the 50DB4 loop shape with ((u16 *)(lbl_2_bss_55E8 + 0x401C))[idx]: 49.8 (compiler folds 0x401C and uses lhzu).
- fn_2_50E5C 88.06 / fn_2_510A8 78.25 / fn_2_50FC8 69.20 -> 100 (matched): index the row arrays through the global cast directly (no
  `rows` local hoisting the lis), 510A8 writes 9604[1] before 9604[0] in source (MWCC emits the pair reversed), 50FC8 flag store as
  `((s16 *)(STATE_BLOCK + 0x6FCA))[idx]`.
- fn_2_512C0 71.42 -> 82.50 (pending): `((u16 **)(STATE_BLOCK + 0x54AC))[idx]` (add + lwz 0x54ac). Left: the 0x7294 counter wants
  base+0x7294 in a reg and idx*2 separate (lhax/sthx); tried 5 address spellings (no gain; the array-cast form gives add+disp, 77.3).
  Switch label orders (4/default/0) all equal; target has an extra dead `b`.
- fn_2_5135C 46.09 -> 55.31 (pending): direct casts instead of three pointer locals. Left: lis/addi scheduling of the three tables.
- fn_2_52198 91.0 -> 91.4 (pending): it is the standalone of fn_2_52690's state-1 prologue; 52690 now calls it (inlined, byte-identical). Left (both): lbl_800FEF70 row address add operand order / old8-vs-nv register swap; 5 address spellings tried, no gain.

## Status after S3 (report numbers; unit 71.58 -> 96.56)
| function | status | before -> now |
|---|---|---|
| fn_2_5135C | pending | 51.22 -> 55.78 |
| fn_2_50D40 | pending | 60.69 -> 60.69 |
| fn_2_51190 | pending | 62.52 -> 62.52 |
| fn_2_51470 | pending | 85.24 -> 85.24 |
| fn_2_512C0 | pending | 74.34 -> 85.39 |
| fn_2_50898 | pending | 88.55 -> 88.55 |
| fn_2_513E8 | pending | 89.09 -> 89.09 |
| fn_2_52198 | pending | 91.00 -> 91.40 |
| fn_2_50B0C | pending | 98.02 -> 98.02 |
| fn_2_52690 | pending | 53.77 -> 98.81 |
| fn_2_509A4 | pending | 98.89 -> 98.89 |
| fn_2_5163C | pending | 86.21 -> 99.93 |
| fn_2_52260 | matched | 76.61 -> 100.00 |
| fn_2_520A4 | matched | 69.92 -> 100.00 |
| fn_2_51C58 | matched | 54.19 -> 100.00 |
| fn_2_51A1C | matched | 83.29 -> 100.00 |
| fn_2_51890 | matched | 86.44 -> 100.00 |
| fn_2_510A8 | matched | 80.16 -> 100.00 |
| fn_2_50FC8 | matched | 70.36 -> 100.00 |
| fn_2_50F20 | matched | 91.19 -> 100.00 |
| fn_2_50E5C | matched | 88.06 -> 100.00 |
| fn_2_50DB4 | matched | 91.19 -> 100.00 |
- fn_2_51470 84 (pending): typed textBanks[..]->strings[idx] in both branches 72.3 (worse; kept the raw form). It inlines fn_2_513E8.
- fn_2_50B0C 98.02 (pending): arg1 register (r7 vs r10); an s32 local copy did not help.
- fn_2_50898 / fn_2_51190: the 0xA8-element clear: a plain `i++` loop gets the target's guard but the wrong per-store
  address association; the hand-unrolled `i += 8` body is right but loses the guard (same as rep_0788 fn_2_20328).
Next for a resumed run: 5135C, 50D40, 51190 (address-shape problems), then 51470/513E8.
