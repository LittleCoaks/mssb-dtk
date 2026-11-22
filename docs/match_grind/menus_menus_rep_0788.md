# menus/menus/rep_0788 checkpoint (first pass, Sonnet)

Baseline unit fuzzy 32.85 -> S1 66.24 -> S2 (Sonnet, this session) 67.76+; all stubs drafted (see S2 section). .text 98.8%, .data size now 0x1744 = target (match 0% only because jumptable symbol names/relocs)

## Method / findings (session S1)
- Stub callbacks `(void *scene, void *record)` are the dominant shape: `fn_2_53BC8(record)` state override, then a state
  switch driving the UIRecord at `graphicsRelatedArray[scene->firstHandle + record->0xE]`. Header prototypes for stubs were
  `(void)` placeholders; changed to `(void *arg0, void *arg1)` as each was drafted. A `SCENE_RECORD(scene, rec)` macro and two
  `static inline` helpers `setRecordFrame` / `setRecordPlayMode` were added at the top of the .c.
- **Inline helper trick (real finding):** when the first store into the record is a constant/early-computed value
  (`frame = 0`, `frame = 0x50000`, `playMode = 0`), the target hoists the `li` above the record address chain and keeps the
  constant in r7/r6. A plain `obj = SCENE_RECORD(); obj->frame = K;` always puts it in r3. Routing that single store through
  `setRecordFrame(arg0, arg1, K)` / `setRecordPlayMode(...)` reproduces the target. 2835C, 28090, 2AEDC, 30EF8, 31D94 matched this way.
- switch with `case 0x25` (no-op) only emits a 0x26-entry table if `0x25` is grouped into the no-op case label list
  (`case 1: case 3: case 4: case 0x25: break;`); a standalone empty `case 0x25: break;` at the end is dropped.
- Byte flag compared `== 2/1` via `cmpwi` (not `cmplwi`) means the flag is an `s8` (`lbl_2_bss_1A8248->_43C2[]` is s8 already).
- Jump-table-based callbacks (cmplwi 0x25 + jumptable_2_data_*) match instruction-wise; the `jumptable_*` references still
  mismatch only by symbol name until .data tables are owned by the unit (data section is 0%).
- Order of work deviated from "biggest-first": small/medium callbacks first (they reveal helpers), the two giants
  fn_2_1D440 / fn_2_20D08 last.
- `int flag = u8field;` then `flag == 1` -> lbz + cmpwi (no extsb); `s8 flag = u8field` adds an extsb.
- load_Icon arg order: passing a ternary / select as the last argument directly is closer than precomputing a local.
- The `(u32)x << 16` frame value read from W (work area) before the store is only right when the store goes through setRecordFrame.
- Tracker status read `lbl_2_bss_1A8248->characters[idx].inGameMissionTracker[row].starMissionStatus` compiles as
  (c + idx*0x34) + row*2 then lbz 9(..), target computes idx*0x34+9, + row*2, lbzx c: fn_2_2B654 / 2BB34 stay at ~98%.
- Header edit (shared): include/game/challenge/challenge_state.h: `_4483[0x44EF-0x4483]` split into `_4483[0x44B9-0x4483]` + `s8 _44B9[54]`
  (per-CHAR_ID flag array compared with 1 in fn_2_28EA0; `challenge->_44B9[charID]` gives the target's `add c,charID; lbz 0x44b9`).
  No layout change. Dependents rebuilt: no unit changed.
- `fn_2_44F14` prototyped locally as `int` (the shared header says s8; the target has no extsb after the call).
- `starRankTextIDs` is read as signed halfwords (lha) in fn_2_2A77C although the header says u16[34]: casts used.

## Remaining stubs (not drafted this session, all still empty `return;`)
fn_2_1D440 (10956 B), fn_2_20D08 (13412 B), fn_2_24800 (1692 B; scene setup: fn_2_6ACF4 / insertGraphicDrawingFunction(fn_2_71F60) /
fn_2_72054 / fn_2_6ABFC, lbl_2_bss_1A823C->0x30 mode switch), fn_2_29884 (1684 B), fn_2_2926C (1560 B), fn_2_338D4 (1436 B; score-digit
display callback with abs() of four W[0x7766..0x776C] values and 0x2710 sentinel, state arg1[0x10] split into hi/lo nibbles).
Order I would take them: 338D4 (same SET_DIGIT/digit shape as 2EFCC), 2926C, 29884, 24800, then the two giants.

## next: lines for pending near-misses (S1)
- fn_2_30D80 / 2AEDC / 2F544 / 2C698 ...: matched or 99.4+; only jumptable symbol names differ (data section not owned yet).
- fn_2_2B654, 2BB34, 2B884: `characters[idx].inGameMissionTracker[row].starMissionStatus` read; target computes `idx*0x34+9`,
  adds row*2, then lbzx from c (98%). next: find the source form that keeps the +9 in the index expression.
- fn_2_2BF20: register permutation (tracker pointer r8 vs r4), 99.7.
- fn_2_28EA0: charID/flag swap r27/r28 (99.77).
- fn_2_30894: row/idx register order (99.35).
- fn_2_306D8 (88.9): load_Icon argument evaluation order / W pointer reload; fn_2_31538 (96.3) same family.
- fn_2_2A77C (94.4, 4 bytes short): W pointer re-derived as `addi; lwz` instead of single `lwz @l`.
- fn_2_2A338 (96.6): register order of the locals loaded from the rule/requirement tables.
- fn_2_331C8 (95.9, 40 B short): the target refetches the record before the playMode store after `frame =` in cases 3 / 0x25;
  our compiler CSEs it. next: find the form that blocks the CSE (a store through a different type?).
- fn_2_20328 (94.8) / fn_2_207FC (81.8): new-challenge init; hand-unrolled `i += 5` copy loop reproduces the ctr loop; the 20-byte zero
  loop in 207FC keeps its `cmpwi i,0x14` guard in the target (ours folds it). Many ChallengeState offsets are raw (CHALLENGE_BYTE).
- fn_2_26F80 (91.9, pre-existing), fn_2_2C1A8 (89.0, pre-existing), fn_2_24728/20074/200E4: untouched.
## Open questions
- Jump tables (`jumptable_2_data_*`) are not owned by the unit (.data 0%): every table-based callback shows 3-4 mismatching reloc lines.
- ChallengeState._44B9[54] (added) and _4446[5]/[6] (s8, -1 = none) are unnamed.
- `fn_2_44F14` shared-header prototype says s8; target needs int (local extern used).


## Status table (only functions below 100% at baseline or now)

| function | size | status | before -> now |
|---|---|---|---|
| fn_2_20D08 | 13412 | pending | 0.03 -> 98.15 |
| fn_2_1D440 | 10956 | pending | 0.04 -> 98.65 |
| fn_2_24800 | 1692 | pending | 0.24 -> 98.6 |
| fn_2_29884 | 1684 | pending (jumptable names only) | 0.24 -> 99.96 |
| fn_2_2926C | 1560 | pending (jumptable names only) | 0.26 -> 99.96 |
| fn_2_338D4 | 1436 | pending | 0.28 -> 98.2 |
| fn_2_2EFCC | 1400 | pending | 0.29 -> 99.90 |
| fn_2_20328 | 1236 | pending | 0.32 -> 94.85 |
| fn_2_207FC | 1204 | pending | 0.33 -> 88.80 |
| fn_2_331C8 | 1100 | pending | 0.36 -> 95.95 |
| fn_2_2A338 | 1092 | pending | 0.37 -> 96.90 |
| fn_2_2D0D4 | 1076 | matched | 0.37 -> 100.00 |
| fn_2_2E7D0 | 1044 | matched | 0.38 -> 100.00 |
| fn_2_2EBE4 | 1000 | pending | 0.40 -> 98.34 |
| fn_2_28948 | 988 | matched | 0.40 -> 100.00 |
| fn_2_28EA0 | 972 | pending | 0.41 -> 99.84 |
| fn_2_30894 | 952 | pending | 0.42 -> 99.41 |
| fn_2_262D0 | 948 | pending | 99.66 -> 99.66 |
| fn_2_3039C | 828 | matched | 0.48 -> 100.00 |
| fn_2_25A48 | 804 | pending | 99.55 -> 99.55 |
| fn_2_2A77C | 784 | pending | 0.51 -> 94.68 |
| fn_2_26C70 | 784 | matched | 0.51 -> 100.00 |
| fn_2_284B0 | 740 | matched | 0.54 -> 100.00 |
| fn_2_300BC | 736 | matched | 0.54 -> 100.00 |
| fn_2_32F08 | 704 | matched | 0.57 -> 100.00 |
| fn_2_2B884 | 688 | pending | 0.58 -> 98.81 |
| fn_2_2AA8C | 676 | matched | 0.59 -> 100.00 |
| fn_2_26864 | 656 | matched | 0.61 -> 100.00 |
| fn_2_2BF20 | 648 | pending | 0.62 -> 99.81 |
| fn_2_2D640 | 644 | matched | 0.62 -> 100.00 |
| fn_2_2BB34 | 624 | pending | 0.64 -> 98.24 |
| fn_2_2FE50 | 620 | matched | 0.65 -> 100.00 |
| fn_2_2B654 | 560 | pending | 0.71 -> 98.04 |
| fn_2_2B43C | 536 | matched | 0.75 -> 100.00 |
| fn_2_320D8 | 524 | matched | 0.76 -> 100.00 |
| fn_2_2E5C8 | 520 | matched | 0.77 -> 100.00 |
| fn_2_270B8 | 516 | matched | 0.78 -> 100.00 |
| fn_2_2DAA8 | 512 | matched | 0.78 -> 100.00 |
| fn_2_2D8C4 | 484 | matched | 0.83 -> 100.00 |
| fn_2_2F8A4 | 472 | matched | 0.85 -> 100.00 |
| fn_2_2CBCC | 472 | matched | 0.85 -> 100.00 |
| fn_2_2DCA8 | 464 | pending | 99.09 -> 99.09 |
| fn_2_2C860 | 464 | pending | 98.53 -> 98.53 |
| fn_2_2C1A8 | 464 | pending | 88.97 -> 88.97 |
| fn_2_27824 | 464 | pending | 98.66 -> 98.66 |
| fn_2_2F544 | 460 | pending | 0.87 -> 99.70 |
| fn_2_2C698 | 456 | matched | 0.88 -> 100.00 |
| fn_2_31538 | 448 | pending | 0.89 -> 96.29 |
| fn_2_31D94 | 444 | matched | 0.90 -> 100.00 |
| fn_2_306D8 | 444 | pending | 0.90 -> 89.50 |
| fn_2_2AD30 | 428 | matched | 0.93 -> 100.00 |
| fn_2_30EF8 | 420 | matched | 0.95 -> 100.00 |
| fn_2_2CA30 | 412 | matched | 0.97 -> 100.00 |
| fn_2_2F710 | 404 | matched | 0.99 -> 100.00 |
| fn_2_28090 | 404 | matched | 0.99 -> 100.00 |
| fn_2_2AEDC | 392 | matched | 1.02 -> 100.00 |
| fn_2_2E44C | 380 | pending | 99.68 -> 99.68 |
| fn_2_2BDA4 | 380 | pending | 98.89 -> 98.89 |
| fn_2_28D24 | 380 | pending | 98.89 -> 98.89 |
| fn_2_26AF4 | 380 | pending | 96.56 -> 96.56 |
| fn_2_30D80 | 376 | matched | 1.06 -> 100.00 |
| fn_2_2C378 | 364 | matched | 1.10 -> 100.00 |
| fn_2_2835C | 340 | matched | 1.18 -> 100.00 |
| fn_2_28224 | 312 | pending | 99.49 -> 99.49 |
| fn_2_26F80 | 312 | pending | 91.95 -> 91.95 |
| fn_2_200E4 | 256 | pending | 97.81 -> 97.81 |
| fn_2_24728 | 216 | pending | 94.07 -> 94.07 |
| fn_2_20074 | 112 | pending | 96.18 -> 96.18 |


## S2 session (Sonnet): all six stubs drafted
- fn_2_338D4 98.2%: logic clean. Left: digit cases 1/2 emit `beq` skip where target has `bne X; b end; X: add` (empty then-branch for which==3); `(s16)part` arg order of fn_80036270 call (extsh r5 after the lha). next: find the form producing `if (which==3) {} else add` (tried else-if empty, switch, ternary).
- fn_2_29884 / fn_2_2926C 99.96%: only jumptable symbol names differ. Macros RECRUIT_ICON / RECRUIT_BADGE_B (with a decl-order parameter: case 8 needs `flag` declared before `charID`, case 2 the reverse).
- fn_2_24800 98.6%: left: `i + 2` is CSE'd into r25 in loop 1 (target recomputes `addi r3,r26,2` at each call; target frame 0x30 / r26..r31 vs ours 0x40 / r25..), `switch (mode) { case 0: }` tail shape (target beq/blt/b), fn_2_689CC result: target `extsh r4,r3` + `sth r3`.
- fn_2_1D440 98.65%: structure all right (state switch 0..13 with inner `for(i<19) switch(i)` loops, MENU_NAV/CYCLE_PAD/RESET_RECORDS macros). Left: (a) post-loop pad-pointer code (target keeps `&Input+2` base in one reg and reuses `slwi port,5` for the 0x13 stick byte read; our macro re-derives it), (b) case 17 `for(j<0x14)` unrolled store loop keeps a `li r0,0; cmpwi r0,0x14; bge` guard in the target (same quirk as fn_2_207FC; s16 loop var made it worse), (c) RESET_RECORDS blocks: register numbering (our `i` is not in r3 for the L/R block), (d) 0x40F0 compare uses `lbz; cmpwi` (S8 form kept).
- fn_2_20D08 98.15% (13368 B vs 13412): all 132 states drafted in the target's text order (cases are NOT in numeric order; goto labels state18/state19/state38 are real jumps in the asm). `settings = &g_d_GameSettings` and `card = cardCheck` locals reproduce the prologue hoists. #pragma dont_inline on fn_2_2469C/24650/246E0 (and 20074, 201E4): the target calls them, the compiler inlined them. Left: state 12/15 `S=0x12` store sharing (target emits a separate `li r0,0x12; sth` where ours merges), `fn_2_201E4` result extsh (header says s16; target uses r3 directly), `input`/`sel` register numbering in state 18 (target uses r29/r28 and r3 directly), pad pointer reuse (`&Input+2` in r29) in state 18 tail, SCENE_MODE/ITEM macros. .rodata ours 120 B vs target 104 B (check float pool: 0.3f/0.1f/0.0f).
- Shared edits: none in headers. rep_0788.c now includes game/UnknownHomes_Game.h (INPUT_BUTTON); `inMemRoster` now typed by that header (two casts).
- Readability pass not yet done for 29884/2926C (jumptable-only diffs) - they will be 100% once .data is owned.

## S3 session (Opus)
- Shared: g_MenuControl symbol added at 0x800E877C (size 0x38; inningSetting now 0x28), type in include/static/menu_control.h;
  REL users updated. `#define SQRT2_LINKAGE static` at top of rep_0788.c -> .rodata 100%.
- fn_2_20074 96.18 -> 100 (matched): early-return chain -> `int dir; if/else-if chain assigning dir; return dir;`
  (early returns gave `li -1; beqlr` on the last test). readability pass: done (INPUT_BUTTON_UP/DOWN/LEFT/RIGHT).
- fn_2_24728 94.07 -> 100 (matched): `base[0x4431 + entry]` through the `base` local instead of re-casting the global
  (target `lbzx base,(entry+0x4431)`).
- fn_2_200E4 97.03 -> 100 (matched): declare `u8 *entry; s16 *base; int level;` in that order and assign after
  (colouring: base must land in r4 so the first load folds to `lwz @l`). ChallengeState* typing for base stays 97.03.
- fn_2_26F80 91.95 -> 100 (matched): case labels were 0/1/2/5/0x25 (no 3/4); sibling shape with setRecordFrame(captain<<16). readability: done (UI_FLAG_VISIBLE, UI_PLAY_STOP).
- fn_2_28224 99.49 -> 100 (matched): case-2 frame=0 store through setRecordFrame. readability: done.
- fn_2_28D24 / fn_2_2BDA4 98.89 -> 100 (matched): drop the phantom `case 7` (target: 6 is the only label between 5 and 0x25). File-wide: SCENE_RECORD / UI_FLAG_VISIBLE spelled (neutral).
- fn_2_27824 / fn_2_2C860 / fn_2_2DCA8 -> 100 (matched): drop phantom `case 7`, plus setRecordPlayMode / setRecordFrame for
  the first record store (27824 case 6, 2C860 case 2).
- fn_2_26AF4 96.56 -> 97.89 (pending): target compare tree root is 4 (labels 0,1,2,3,4,0x25; >4 subtree is
  `cmpwi 0x25; beq; bge; b end`). Adding an empty `case 6:` to the no-op group gives root 4 (97.89) but leaves `cmpwi 6; beq`.
  Tried: case 5 (merges with 4, root 3), 5+6, 0x24, separate break statements per label, default:, case 6+7, regrouping. 
- fn_2_2C1A8 88.97 -> 100 (matched): drop case 7; case 2 frame via setRecordFrame(Static_Stats_Tables.characterStats[id/9][id%9].stats.CharacterClass << 16) (typed access needed with the helper; raw-offset form 89.4). readability: done.
- fn_2_2E44C 99.68 -> 100 (matched): first record store written without the obj local (`((UIRecord *)SCENE_RECORD(..))->pos.x = 320.0f`), same effect as the setRecord* helpers.
- fn_2_25A48 99.55 -> 99.78 (pending): case 4 without the challenge local. Left: r6/r7 swap (challenge ptr vs graphicsRelatedArray base). Tried: limit local (97.2), table on lhs (99.25), obj assignment forms, (u16) cast, no cast.
- fn_2_262D0 99.66 (pending): r3/r4 swap of the challenge ptr in the two 'special' predicates. Tried: decl order swaps (4 orders), no locals, assign-after-declare (text_37F04 style), difficulty from global directly. All 99.66 or worse.
- fn_2_2B654 / 2BB34 / 2B884 -> 100 (matched): MISSION_TRACKER(idx) = `(starMissionTrackingPair *)((u8 *)&c->characters[idx] + 9)` then [row].starMissionStatus. Raw `((s8*)c)[idx*0x34+9+row*2]` gave 98.3 (reassociated). readability: done.
- fn_2_2BF20 99.81 -> 100 (matched): declare `s16 b; s8 statusA; s16 a; ChallengeTrackingStruct *tracker;` (reverse order) then assign. MISSION_TRACKER form 97.4, work-pointer local 99.5.
- fn_2_28EA0 99.84 -> 100 (matched): in the case-2 recruited branch declare charID before flag (case 8 keeps flag first).
- fn_2_30894 99.41 -> 100 (matched): `_43C2[row + idx]` instead of `(_43C2 + row)[idx]`.
- fn_2_2F544 99.70 (pending): out-pointer / charID value register swap (r5/r7) in the lineup filter loop. Tried: all 24 declaration orders of list/out/i/challenge, id local, out++ split, list[n++] (int 96.1, s16 94.1), slot walker (95.2), global direct (97.7), swapped compare (99.65).
- fn_2_2EFCC 99.90 -> 100 (matched): first record write in case 2 directly on SCENE_RECORD(...) (no obj local).
- fn_2_2EBE4 98.34 -> 100 (matched): load_Icon frame arg `((s8 *)c->_4446)[5]` (a (s8) cast of the u8 element gives lbz+extsb into r0).
- fn_2_306D8 89.05 (pending): target sets up load_Icon args r3-r6 BEFORE the ternary's compare/branch (left-to-right), ours evaluates the ternary first. Tried: work pointer + u8 compare (87.6), int flag local (88.6/89.05), s8 work (88.6), frame=0x14;if(!=2)frame=sum (77.0), duplicated call in if/else (67.7), s16 sum (75.3), fully inlined sum (76.8). Same arg-order family as fn_2_338D4 line ~288.
- fn_2_207FC 81.81 -> 99.67 (pending): `s32 i` (was int) restores the unfolded `cmpwi i,0x14` guard of the 20-store loop. Left: target jump-table entry for CHAR_ID_MARIO is its own `b end` block. Tried: captain = MARIO / captain = captain / =0 in that case, default: before/after. All 99.67.
- fn_2_20328 94.85 -> 97.94 (pending): `s32 i`. Left: the i+=5 copy loop (unrolled x2, ctr 2) lacks the target's `cmpwi i,0x14; bge` guard; Mario-case `b end` block as in 207FC. Tried: plain i++ loop (84.8), while / for-without-step, separate j of s32/int/s16/u8/u32, <=19, 20>i, _43C2[i+k] dst (83.1).
- PAD_NEW2() = `*(u16 *)((u8 *)&AtBat_ButtonInput1._02 + PAD_PORT * 32)` (field-address base -> `addi base,2; lhzx`): greedy
  per-site replacement of PAD_NEW() kept 6 sites in 20D08 and 5 in 1D440 (no drops). `(u8*)&X + 2 + off` is NOT equivalent (no change).
- fn_2_1D440 98.66 -> 100 (matched): s32 j (case-17 guard), PAD_NEW2 sites, `*(f32 *)((u8 *)c + idx * 0xBC + 0x2208)` (lfsx form),
  RESET_RECORDS compare `(s32)CHALLENGE_BYTE(..) == (s32)(type)` (lbz; cmpwi without extsb).
- fn_2_20D08 98.19 -> 99.40 (pending): PAD_NEW2 sites; case 12 sub-switch `case 1:`/`case 2:` and `case 7:`/`case 8:` as separate
  `S = 0x12; break;` statements (target keeps 3+2 separate blocks); fn_2_201E4 returns int (no extsh at callers; body unchanged);
  CHALLENGE_REC2 (`((u8 (*)[10])c->_40EE)[idx][off - 0x40EE]` -> add + lbz off) at the sites the greedy pass kept; state-18
  A-button block: no recIdx local, block 1 via `c`/`rec` locals; `(s32)u8 == 1` gives the target's cmpwi (PORTRAIT_OR_SCENE, 0x789E).
  Left: block 2-5 register numbering (target loads rec[0x40F3] before captain, address reg reused -> re-add); blocks 2+ with locals worse (99.20/99.13).
- fn_2_31538 96.29 -> 100 (matched): pass `((s8 *)&WORK_U8(0x7868))[(s8)WORK_U8(0x7867)]` straight to load_Icon (s8 local / (s8) cast load into r0 + extsb).
- fn_2_2A77C 94.35 (pending): case-2 text-id sum: target reloads W via addi+lwz 0 and keeps rankCol in r8; tried operand order swap (same code), WORK_S16 / s16 work local, u16 textID local (94.10).
- fn_2_2A338 96.65 -> 97.62 (pending): tracker computed after the two display-rule reads; `(s32)shownOnPauseMenu == 1`; declaration
  order textID, tracker, flags, minRow, mode (best of a 120-permutation sweep; declare-then-assign). Left: W base / charRow register
  numbering in the prologue of case 2 (target lis order rules, 869C, 8248).
- fn_2_26AF4: also tried separate case 4/5/6 statement combos (851A8's empty-lower-label trick): no gain.
- fn_2_338D4 98.27 (pending): tried the text_50898 inline-early-return trick for the digit `which == 3` branch: value-returning inline is if-converted to a select (93.6), void inline with pointer (97.7). Reverted.

## Status after S3 (report numbers; unit 98.92 -> 99.65)
| function | status | before -> now |
|---|---|---|
| fn_2_306D8 | pending | 89.50 -> 89.50 |
| fn_2_2A77C | pending | 94.68 -> 94.68 |
| fn_2_331C8 | pending | 95.95 -> 95.95 |
| fn_2_2A338 | pending | 96.90 -> 97.62 |
| fn_2_26AF4 | pending | 96.56 -> 97.89 |
| fn_2_20328 | pending | 94.85 -> 97.94 |
| fn_2_338D4 | pending | 98.27 -> 98.27 |
| fn_2_24800 | pending | 98.65 -> 98.65 |
| fn_2_20D08 | pending | 98.26 -> 99.43 |
| fn_2_262D0 | pending | 99.66 -> 99.66 |
| fn_2_207FC | pending | 88.80 -> 99.67 |
| fn_2_2F544 | pending | 99.70 -> 99.70 |
| fn_2_25A48 | pending | 99.55 -> 99.78 |
| fn_2_31538 | matched | 96.29 -> 100.00 |
| fn_2_30894 | matched | 99.41 -> 100.00 |
| fn_2_2EFCC | matched | 99.90 -> 100.00 |
| fn_2_2EBE4 | matched | 98.34 -> 100.00 |
| fn_2_2E44C | matched | 99.68 -> 100.00 |
| fn_2_2DCA8 | matched | 99.09 -> 100.00 |
| fn_2_2C860 | matched | 98.53 -> 100.00 |
| fn_2_2C1A8 | matched | 88.97 -> 100.00 |
| fn_2_2BF20 | matched | 99.81 -> 100.00 |
| fn_2_2BDA4 | matched | 98.89 -> 100.00 |
| fn_2_2BB34 | matched | 98.24 -> 100.00 |
| fn_2_2B884 | matched | 98.81 -> 100.00 |
| fn_2_2B654 | matched | 98.04 -> 100.00 |
| fn_2_28EA0 | matched | 99.84 -> 100.00 |
| fn_2_28D24 | matched | 98.89 -> 100.00 |
| fn_2_28224 | matched | 99.49 -> 100.00 |
| fn_2_27824 | matched | 98.66 -> 100.00 |
| fn_2_26F80 | matched | 91.95 -> 100.00 |
| fn_2_24728 | matched | 94.07 -> 100.00 |
| fn_2_200E4 | matched | 97.81 -> 100.00 |
| fn_2_20074 | matched | 96.18 -> 100.00 |
| fn_2_1D440 | matched | 98.75 -> 100.00 |
