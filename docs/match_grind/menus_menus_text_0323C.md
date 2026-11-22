# menus/menus/text_0323C (src/menus/text_0323C.c) — match grind checkpoint

Baseline (session 1, 2026-11-09): .text 80.708%, 19/67 at 100% (report says 81.54 fuzzy).

| function | status | baseline | pct |
|---|---|---|---|
| fn_2_4970 | pending | 57.71% | 97.22% |
| characterSelectBPress | pending | 65.30% | 94.02% |
| fn_2_3624 | pending | 65.50% | 95.03% |
| fn_2_B920 | pending | 67.11% | 77.41% |
| characterSelectControls | pending | 71.67% | 90.66% |
| fn_2_A288 | matched | 72.53% | 100.00% |
| fn_2_EAE0 | pending | 73.88% | 99.88% |
| cssSortCaptainChemistryOrder (was fn_2_ABC0) | matched | 74.20% | 100.00% |
| characterSelectAPress | pending | 75.20% | 98.73% |
| cssUnloadScreen | pending | 76.63% | 76.63% |
| fn_2_C7DC | pending | 76.64% | 85.55% |
| fn_2_B324 | pending | 76.67% | 92.52% |
| fn_2_8CF8 | pending | 77.61% | 77.61% |
| cssRandomFillRoster | pending | 77.76% | 95.39% |
| fn_2_CA60 | pending | 79.27% | 96.95% |
| fn_2_95D8 | pending | 79.36% | 84.60% |
| fn_2_B66C | pending | 80.69% | 96.50% |
| characterSelectABDirectionInputs | pending | 81.96% | 92.42% |
| fn_2_AEE8 | pending | 82.52% | 99.96% |
| randCharAlgo2 | pending | 82.63% | 82.63% |
| randCharBasedOnClass | pending | 83.19% | 83.19% |
| fn_2_6784 | pending | 85.31% | 97.03% |
| fn_2_52CC | pending | 86.65% | 99.10% |
| cssResetRosterStruct | pending | 86.80% | 86.80% |
| teamReady1 | pending | 87.88% | 89.79% |
| fn_2_9ACC | pending | 88.88% | 88.88% |
| fn_2_A6E0 | pending | 89.42% | 95.61% |
| fn_2_A1A0 | matched | 90.16% | 100.00% |
| randCharacter1 | pending | 90.86% | 90.86% |
| challengeSetRoster | pending | 91.06% | 91.06% |
| fn_2_A040 | pending | 91.65% | 99.03% |
| fn_2_A62C | pending | 91.67% | 97.44% |
| cssLoadingScreenRelated | pending | 92.24% | 92.24% |
| cssTransitionToNewScreen_maybe | pending | 93.11% | 93.11% |
| cssChangeScreens | pending | 93.44% | 93.44% |
| fn_2_57F0 | pending | 93.73% | 93.73% |
| fn_2_CCE0 | matched | 93.93% | 100.00% |
| fn_2_5F80 | matched | 94.14% | 100.00% |
| fn_2_348C | pending | 94.26% | 94.26% |
| fn_2_6AF4 | pending | 94.79% | 94.79% |
| fn_2_5184 | matched | 95.30% | 100.00% |
| fn_2_C484 | pending | 95.49% | 95.49% |
| fn_2_33BC | pending | 97.48% | 97.48% |
| fn_2_9F70 | pending | 97.79% | 97.79% |
| copyInfoToInMemRoster | pending | 98.27% | 98.27% |
| fn_2_A50C | pending | 98.54% | 98.54% |
| fn_2_87A8 | pending | 99.31% | 99.31% |
| teamSelectScreenMain | pending | 99.90% | 99.90% |
| closeZMenu | matched | 100.00% | 100.00% |
| fn_2_57E8 | matched | 100.00% | 100.00% |
| fn_2_6098 | matched | 100.00% | 100.00% |
| fn_2_60D4 | matched | 100.00% | 100.00% |
| fn_2_6138 | matched | 100.00% | 100.00% |
| cssSelectCPUDifficulty | matched | 100.00% | 100.00% |
| characterSelectScreenControlable | matched | 100.00% | 100.00% |
| fn_2_6884 | matched | 100.00% | 100.00% |
| fn_2_7D44 | matched | 100.00% | 100.00% |
| fn_2_86EC | matched | 100.00% | 100.00% |
| fn_2_8780 | matched | 100.00% | 100.00% |
| fn_2_8794 | matched | 100.00% | 100.00% |
| fn_2_893C | matched | 100.00% | 100.00% |
| fn_2_B508 | matched | 100.00% | 100.00% |
| fn_2_C324 | matched | 100.00% | 100.00% |
| fn_2_C698 | matched | 100.00% | 100.00% |
| fn_2_CCBC | matched | 100.00% | 100.00% |
| fn_2_EC34 | matched | 100.00% | 100.00% |
| fn_2_EC54 | matched | 100.00% | 100.00% |

Session 1 end (2026-11-10): .text 86.986% (diff), report fuzzy 87.75%, 19/67 at 100% (report counts 20).
Next session: start with fn_2_57F0 (twin of fn_2_3624 - apply the same CSS_CURSOR / case-order / helper lessons),
then characterSelectControls, characterSelectAPress, fn_2_B920, cssUnloadScreen, fn_2_8CF8.
Cross-function leads: the 9-slot "position == cursor" search appears in many functions; write it as
`for (i...) if ((s8)pos[team][i] == cursor) idx = i;` with a cursor local (no break) unless the target branches out after each hit.
Hand copies of fn_2_C698 (register char) and fn_2_52CC exist elsewhere in the file; call them.
addRemoveCharVariantRelated's real prototype is u8(u8,u8,u8) (include/Unknown/mb_subfunc.h); the local s32 prototype at the
top of the file makes callers emit clrlwi on team (fn_2_4970 diff lines ~175-194) - next lever to try (file-wide, measure all).

## Hypothesis log

fn_2_3624 (lineup/position screen input handler)
  baseline: 65.50%
  [1] UP/DOWN/LEFT/RIGHT: prev-cursor store after the 9/10 checks (prev = F468+8 s32[2]), case order from jump tables (UP 0-6,8,7; DOWN 0,2,4,3,5,7,6,8,1; LEFT 0,1,2,3,7,8,4,10,5,6; RIGHT 0,1,4,5,6,7,2,8,3) -> 66.04 (kept)
  [2] A block: arms were inverted (draft ran the position swap when cursor==9 and stored 9 into 0x61) -> cursor==9 confirms, else 0x5f==0 stores cursor into 0x61 / else swap; challenge copy as a plain 9-loop -> 80.61 (kept, REAL BUG)
  [3] CSS_CURSOR as *(s32*)&F468[slot*4] byte-offset form (vs (s32*)F468)[slot]: +1.7; prev as F468[slot*4+8] -> 82.77 (kept)
  [4] controllerInputs copy field-by-field (target uses 3x lhz/sth, struct copy gives lwz+lhz) -> 83.27; `int team = port` -> 83.31 (kept)
  [5] A block: p2_CPU==0 { slot!=0 / slot==0 } else {100B8} order; CSS_CURSOR(gameSetUpStep[0x59]) = 10 (forwarded store) -> 86.86; int slot -> 87.39 (kept)
  [6] L block rewritten: GameMode==CHALLENGE test at the end was misread as `lIdx == 5`; playerNumberByPort[0]==0 -> team 1 arms were inverted; found-in-roster skips the store; Z block stored 1 into 0x41 instead of 0x45 -> 87.46 (kept, REAL BUGS)
  [7] position search: 9-arm else-if chain 89.82 vs loop with int/u32/s8/u8/s16 counter (87.5/87.5/83.1/82.4/82.6) -> chain kept
  [8] cursor!=9 { ... } else { sound } instead of early-return -> 91.10; challenge arm last (!= CHALLENGE first) -> 92.83; variant (!= -1 && col < 4) first -> 93.42 (kept)
  [9] idx u8 / (s8)idx first use: 93.23 / 93.42 (no gain); row=0 hoisted above 0x50 store: no change
  remaining: r0 kept live for GameModeSelected in target (ours r4); add r7 operand order for prev store; challenge-loop scheduling; rosterCharID base not CSE'd in target.
  [10] slot==0 confirm body is fn_2_52CC (call it; inlines) -> 93.22, then fn_2_52CC's cursor store as CSS_CURSOR(gameSetUpStep[0x59]) = 10 -> fn_2_3624 93.67, fn_2_52CC 86.65 -> 99.10 (kept)
  [11] L-block tail is fn_2_C698(idx, slot) (call it; inlines) -> 95.03 (kept)
fn_2_52CC
  baseline 86.65
  [1] forwarded-store index CSS_CURSOR(gameSetUpStep[0x59]) = 10 -> 99.10 (kept)
  [2] read the taken flag into a u8 local before the stores -> 93.83 (reverted)
  remaining: lis order menuCursors/Static_Stats_Tables/100B8 (registers r4/r5 swap only)
characterSelectBPress (B press on the lineup screen)
  baseline: 65.30%
  [1] full rewrite from asm, structured (no gotos): draft tested the restored cursor (`count == 0`) where the target tests mismatchCount == 0; p2_CPU==1 path was missing; tail sound is one cursorSndFx(0x200) at the end, early `return`s skip it -> 89.22 (kept, REAL BUG)
  [2] locked-flag neg/or/srwi. idiom: tried !!, ==TRUE, (u32)>0, (x!=0)>0, inline BOOL/bool helpers returning flag / flag!=0 / ?: -> none reproduce it (best 89.43 with ugly (x!=0)>0, not kept)
  [3] gameSetUpStep[0x55+i] as a 2-trip loop in the p2_CPU==1 branch 89.32 (kept); inline cssPortBusy(p) helper 89.22 (reverted)
  [4] p2_CPU==0 branch tests CSS_CURSOR(team) directly instead of a cached local -> 89.96 (kept)
  [5] position searches as `for (i...) if (pos == cur) idx = i;` (no break; MWCC fully unrolls with a walking pointer) -> 90.43 (kept)
  [6] idx s32 (target indexes with it unextended) -> 90.96; second search compares a cursor local loaded once -> 93.93 (kept)
  [7] hand-copied fn_2_C698 body instead of the call -> 93.00 (reverted); 36 pairwise declaration swaps -> +0.005 max (not kept)
  remaining: target keeps GameModeSelected in r0 / p2_CPU in r8 through the inlined fn_2_C698 (ours reloads); team in r31 vs r17; neg/or/srwi idiom
fn_2_4970 (remove the character in the cursor's lineup slot)
  baseline: 57.71%
  [1] rewrite from asm: register-char part is fn_2_C698(idx, team) (draft had the playerNumberByPort[0] arms inverted - REAL BUG, fixed by calling the helper); gotos removed -> 86.96 (kept)
  [2] cursor read once into a local before the slot search (no break, full unroll) -> 96.77 (kept)
  [3] search moved into a static inline helper -> 96.13 (reverted)
  [4] slot char read once into an s8 local for the ==charID / -1 / 0x36 tests -> 96.99 (kept)
  remaining: charID-match path reloads the cursor in the target; prev-store add operand order; clrlwi on team for addRemoveCharVariantRelated (prototype)
teamReady1: 87.88 -> 89.79 as a side effect (not worked)

## Session 2 (Opus, short): 87.75 -> 87.79 (commit fda41b06)
fn_2_A288 72.53 -> 76.30: rows read for m = 1..2 (flags [m-1]), entries compared as s32, captain
  index `s32 found = (u8)i`. remaining: register naming in the captain loop / row walk.
Tried and reverted (logged so they are not repeated):
- addRemoveCharVariantRelated real prototype u8(u8,u8,u8): +0.3..+1.3 in 7 functions (4970 98.31,
  B66C 81.90, challengeSetRoster 91.97, LoadingScreen 92.73, ReturnToCap 94.20, Controls 72.11)
  but drops APress -0.11, B920 -0.35, randCharAlgo2 -0.53, randCharacter1 -0.08, C484 -0.08,
  5184 -0.67. Needs those callers' param types fixed first (5184 port is really u8? making it u8
  dropped 5184 to 85.5, so not that simply). Next session: apply prototype + fix each dropper.
- fn_2_57F0 s32 param + (u8) casts: no change in 57F0 (MWCC CSEs the cast), caller -0.8.
- fn_2_CA60 = { lineup store | fillUnassignedRosterSlot(idx, team); fn_2_C698(idx, team) } (u8 params):
  72.98 (from 79.27) because the target converts the params at every use; B920 calling CA60(i,0)
  doesn't inline it (55.3). The B920/B66C loop bodies are CA60 inlined though.
- fillUnassignedRosterSlot via rosterCharID[][] with s32 id: B920 69.14, B66C 81.02 but A1A0 90.07
  (-0.09) -> reverted; pointer-walk and k+2 offset variants worse.
- fn_2_EAE0 flag test as if/else-empty or ternary: no gain / worse.
REAL BUG FOUND, NOT FIXED (fixing it costs score until the rest of the function matches):
  fn_2_6784 scans the already-picked defaults from `slot` (the current position) instead of
  from the start of the roster (target: ptr = &cursorPositions each retry). Rewrite with the
  target's address-constant `&lbl_8010902C[0xC]` hoisted per else-branch.

## Session 3 (Opus)
Shared block: fn_2_A1A0 / fn_2_CA60 / B920 + B66C loop bodies
  [1] CA60 = initRosterSlot(u8 slot, u8 team) static inline (lineup store | fn_2_A1A0; then mode/addOrRemove/variant);
      fn_2_CA60 is a wrapper; B920 loop = initRosterSlot(i, 0), B66C loop = initRosterSlot(i, 1) -> B920 71.5, B66C 90.4 (kept)
  [2] fill: inner `for (k = 0; k < 2; k++)` over rosterCharID[k][j] (target's r10+9 row pointer is the unrolled k=1) -> CA60 85.2 (kept)
  [3] fill is the real fn_2_A1A0 (non-static, called from initRosterSlot; MWCC still inlines it) instead of a static inline
      + wrapper -> A1A0 98.1; then no locals for taken/p2CPU/flag (read in the conditions, LICM hoists) -> A1A0 100% (kept)
      readability pass: done (CHAR_ID_MARIO candidate, P2_CPU_CODE_1_PLAYER_GAME, FALSE). Behaviour note: only Mario is ever
      tried, so it spins forever if Mario is taken / already rostered (comment in source).
  [4] initRosterSlot: separate `s8 id` (lineup) and `s32 charID` (after the mode test) -> clrlwi for the variant arg; CA60 95.2, B66C 96.4 (kept)
  [5] lineup stores: struct/[9][4]/[0x24] forms CSE the row+slot*4 address; flat `lineUpInfoStruct[team*0x24 + slot*4 + 1]`
      gives target's stbx -> CA60 96.56 / B66C 96.06 (kept; B66C prefers struct form by 0.3)
  remaining (CA60/B66C): target reuses the clrlwi'd slot for slot*4 and the stored value (ours clrlslwi from raw / stores raw i)
Random lineup switch (B66C/B920): `if (result != -1) { switch {case 0; case 1} } else {=3}` reproduces the -1-first compare tree
  and block order exactly (case orders, extra case -2/2/default all tried: none) -> B66C 93.6, B920 75.2 (kept)
fn_2_B920
  [6] memset/taken via Static_Stats_Tables.charOnCharacterGridSelected (address CSE'd into r26), struct fields -> 73.7 (kept)
  [7] challenge loop compares u8 v with g_Challenge fields directly (no locals, no (s8)v) -> 76.5 (kept)
  [8] copy blocks: inline loadDefaultLineup(team, captain); target keeps base = SST + cap*0x48 + sel*0x12 and 0x4380+i as
      displacement; ours always strength-reduces sel*0x12+0x4380+i. Tried raw byte index orders (5 forms), SSTView struct
      with rows[12][4][0x12], cast [4][0x12], pointer-param helper (dst, sel*, cap), 2-iteration t loop (unrolls but
      select on captain) -> best challengeRosters[captain].charID[*sel * 0x12 + i] 77.23 (kept)
  [9] matchIdx `a = b = 0` / separate inits: no change (target li r0,0; mr r24,r0; mr r28,r0)
  remaining: copy-block address shape + store-back of F468[0x14] only in the second block; matchIdx zero via r0
fn_2_EAE0 (73.88)
  [1] port pick as static inline returning early (`if (!active[port]) return port; return pnbp[0]==0;`) -> bne/b empty-then layout (kept)
  [2] do-while cursor skip as static inline taking the cursor pointer, called with `&((s32*)menuCursors)[i+8]` while the
      test reads `((s32*)&menuCursors[0x20])[i]` (different expression => no lwzu CSE, matches target's addi in the branch) -> 86.0
  [3] target saves r27-r31 although the inner loop is infinite: the loop is `do { ...fn_2_1D54 } while (taken[...] || c[8] == c[8])`
      (tautology, MWCC folds it after register allocation). `|| TRUE` / `[i+8]==[i+8]` identical. -> 97.35 (kept, comment in source)
  [4] trip count in a local `count` -> 99.88 (kept)
  remaining: lbz r0/extsb r4 vs lbz r4/extsb r4 for playerNumberByPort[i] (tried s32/s16/s8 port, u8/s8/s32 returns,
      pointer/port params, result var, ternary, caller-side empty-then: none better)
fn_2_6784 (85.31)
  [1] REAL BUG FIXED: duplicate scan restarts from rosterCharID[1][0] on every retry (draft scanned from the current slot);
      struct fields (captainSelectedID, rosterCharID, rosterSpotFilledInd, charOnCharacterGridSelected) -> 92.66 (kept)
  [2] slot 0: roster = captainSelectedID[1]; taken[rosterCharID[1][0]] (store-forwarded; gives the fresh SST base) -> 97.03 (kept)
  remaining: target loads `lbl_8010902C+0xC` as a hoisted address constant (lbzx); ours hoists lbl_8010902C and folds 0xC
      into the displacement. 2D cast, struct cast, ptr arith, pointer local (in branch / at top: 86.0) all fail. Probably
      the 9 char IDs at 0x80109038 are their own array in the original; needs a symbols.txt split of lbl_8010902C
      (data lives in src/Unknown/mb_subfunc.c) - not done (shared file). Same pattern in the function at 0x6FA8 (fn_2_6AF4).
fn_2_B324 (76.67)
  [1] inMemRoster CharID via ((CharacterStats (*)[9])inMemRoster)[team][i].stats.CharID (one pointer, disp 0x24/0x5c4) -> 92.46 (kept)
  [2] -1 stores need s8 element type (target li -1): casting only the -1 stores splits the IVs (72.3); casting every
      lineUpInfoStruct/lbl_80353B98 access to s8* -> 92.47 (kept); b declared before a -> 92.52 (kept)
  [3] no a/b locals (captainSelectedID[x] + i) 88.7; for-init / post-inc in body: no change
  remaining: register naming only (target r3/r4 = a/b, r7 = inMemRoster, r6/r5 = lineup/3B98)
fn_2_A288 (76.30)
  [1] row scan as `for (j = 1; j < 9; j++)` over challengeRosters[found].charID[m * 0x12 + j] (MWCC unrolls it with a
      walking pointer + disp 0x4381) -> 93.19 (kept)
  [2] tail `for (m = 1; m < 3; m++) if (3E0[m] == 0) count++;` (reuses &3E0[1] from the first m loop) -> 100% (kept)
  readability pass: done (captainSelectedID, _470B, CHAR_ID_NONE). Note: the scan writes 3E0[m-1] (0,1) but the count
  reads 3E0[m] (1,2) - kept as compiled. 12 = captain count, no constant exists.
fn_2_C7DC (76.64)
  [1] u8 params (slot, team): target passes team raw to the inlined fn_2_C698 -> 80.30; s32 params + casts 78.78 (u8 kept)
  [2] lineup writes as static inline setLineupSlot(slot, team) (both branches), [9][4] array form -> 85.55 (kept);
      flat byte index (u8/s32 params) 80.3-80.9, [0x24] with slot*4+k 84.80
  remaining: target's [0] stores are stbx(row, slot*4) and slot*4 comes from a fresh clrlslwi of the raw param (ours CSEs
      with the hoisted (u8)slot); scheduling/register naming in the tail.
  [3] initRosterSlot second half replaced by a call to fn_2_C698 (inlined): CA60 86.4, B66C 86.7, B920 71.5 -> reverted
cssRandomFillRoster (77.76)
  [1] random-algorithm switch has only cases 0,1,2 (the draft's empty `case 3` moved the compare-tree root) -> 80.04 (kept)
  [2] outer count loop `for (i = 0; i < 6; i += 2)` to keep target's dead `r5 += 2` IV: MWCC removes it anyway (no change)
  [3] `u8 t = team` local for the F468 indexes: no change (copy-propagated)
  remaining: target re-derives (u8)team in fresh registers (xor otherTeam, r27 for teamLogo/updateCSPC, else branch)
      and saves r27-r31; ours CSEs one clrlwi. Dead r5 IV.
fn_2_ABC0 (74.20)
  [1] captain row/col as locals (col = id % 9 first, then row = id / 9), byte read inside the loop
      ((u8 *)&characterStats[row][col])[i + 0x3B] with the vals store before the order store -> 83.9
  [2] output through Static_Stats_Tables.captainChemistryOrder[(u8)port][i] (disp 0x478d+i) -> 97.4
  [3] `u8 best; u8 t2; u8 t;` declared at the top -> 100% (kept)
  readability pass: done (NUM_CHOOSABLE_CHARACTERS for the 54s; chemistry offset documented). Label proposal (medium):
  fn_2_ABC0 -> cssSortCaptainChemistryOrder (only writer of captainChemistryOrder here) - not applied.
fn_2_AEE8 (82.52) - both-teams twin of fn_2_ABC0
  [1] ABC0 lessons: row/col locals, in-loop read ((u8 *)&characterStats[row][col])[i + 0x3B], captainChemistryOrder output -> 98.14
  [2] here row = id / 9 before col = id % 9, and `u8 best; u8 t2; u8 t;` at the top -> 99.96 (kept)
  [3] decl permutations of captain/row/col: no change; no captain local 99.91; col-first without local 98.23
  remaining: col lands in r29 (target r26). NOTE: a session-3 replace() briefly changed AEE8's decls by accident
  (82.52 -> 82.49 in commit 1f4381da); restored and superseded here.
fn_2_95D8 (79.36) - debug colour table with the draw calls compiled out
  [1] team loop written with array indexing (lim/status if-else with the load in both arms, rosterCharID[team][j],
      captainSelectedID[team], lineUpInfoStruct[team*0x24 + k*4 + 1]); MWCC builds the target's 5 pointer IVs -> 84.69
  [2] picks as s8 picks[2][9], r-loop with taken[r]/picks[team][j]/charOnCharacterGridSelected[r] -> 84.60 (same)
  [3] early `goto tail` replaced by `if (state < 4) {...}` (84.69 -> 84.60, kept for structure)
  [4] tail compare chain (cmplwi 2/4/9/0x13/4 with no body) is dropped by our build. Tried nested ifs, single || chain,
      else-if, no local, empty static inline call, dead stores/self-assign/(void)/while(0)/x!=x bodies: all removed.
      Only a zero-trip `for (i = 0; i < 0; i++) {}` body keeps the compares (86.16) but leaves loop residue - not kept.
      volatile read keeps only the load (85.87) - not kept.
  remaining: opponentCaptainCharID load is hoisted out of the team loop in ours (target reloads per team; 2 more saved regs),
      tail compares.
fn_2_A62C (91.67) / fn_2_A6E0 (89.42, inlines A62C four times and findRosterOverlap twice)
  [1] A62C via rosterCharID[0][i] / [1][j] with `s8 id` declared in the i loop -> A62C 97.44, A6E0 95.61 (kept).
      Note the `id != 0xFF` test on an s8 can never fail (target emits it too: cmpwi 0xff) - kept as compiled.
  [2] j declared before i: A62C 97.78 but A6E0 95.39 (reverted); id at the top: same / worse
  [3] same struct form in findRosterOverlap: A6E0 97.02 but fn_2_A50C 98.54 -> 85.21 (reverted)
  remaining: register naming (val in r8/r3 vs ours)
fn_2_A040 (91.65) - cycle a variant character into roster[team][idx]
  [1] rosterCharID[team][idx] / [i][j] struct stores (base + team*9, then + idx) -> struct + early-return fallback 75.5;
      `if (pair[slot] != NONE && slot < 4) { ...; return; } roster = pair[0];` (fallback block last, no goto) -> 99.03 (kept)
  [2] target/i/j decl orders, s32 target: no gain
  remaining: target (r7) and the row pointer (r8) swapped
characterSelectABDirectionInputs (81.96)
  [1] rewrite from asm: params are (u8 team, u16 held, u16 pressed, u16 repeat) (2nd param is u16, extended lazily);
      the 0x47 left/right toggle is a static inline (cssToggleZMenuPage) used in both branches; port pick reuses
      EAE0's cssCursorPort inline; early `goto buttons` kept (shared exit to the A/B tail); PAD_BUTTON_* via Dolphin/pad.h
      (game/UnknownHomes_Game.h conflicts with this file's local externs, so INPUT_BUTTON is unavailable here) -> 85.90
  [2] cursor pointer as &((s32 *)&menuCursors[0x20])[team] (lwzu disp 0x20) -> 92.42 (kept)
  [3] fn_2_57F0 2nd param u16 (removes our clrlwi before the call): 57F0 unchanged, this -0.07 (reverted);
      option[2] for the 0x49 store in either arm -0.08; s32 team in the toggle helper 90.81; cssCursorPort((u8)team) same
  remaining: toggle arm 2 re-derives F468+team in the target; clrlwi on held before fn_2_57F0; cssCursorPort index uses
      a fresh clrlwi of team in ours; register naming in the CPU-port branch.
  [4] held param typed s32 instead of u16: 92.42 -> 92.13, but the u16 prototype re-allocates registers in the caller
      characterSelectControls (report 72.58 -> 72.46). Kept s32 so no function regresses; revisit u16 together with
      characterSelectControls.
fn_2_5F80 (94.14)
  [1] hand-written pointer walks replaced with plain indexing (lineUpInfoStruct[team*0x24 + k*4 + 2],
      rosterCharID / positionSwapMapping, CharacterStats[team][g]) -> 100% (MWCC derives the target's IVs itself)
  readability pass: done. Lesson for the rest of the file: drafts with manual pointer IVs usually lose to array indexing.
fn_2_9F70 (97.79)
  [1] switch {1,2,3} + `goto retry` rewrite of the goto-chain draft: 78.27 (reverted; the draft's loop shape is closer)

Session 3 end (Opus): report unit fuzzy 87.79 -> 90.12; diff .text 87.03 -> 89.69; 19 -> 23 functions at 100%
  (new: fn_2_A1A0, fn_2_A288, fn_2_ABC0, fn_2_5F80). Commits 4235422f..8811e846.
Cross-function findings (this file):
  - Drafts with hand-written pointer walks lose to plain array/struct indexing; MWCC derives the target's IVs itself
    (5F80 100%, 95D8, A288, B324). Use struct fields (cursorPositions.roster.*, CharacterStats (*)[9] on inMemRoster,
    Static_Stats_Tables.challengeRosters/captainChemistryOrder/charOnCharacterGridSelected) so offsets fold into displacements.
  - A recurring residual: the target re-derives (u8)param with a fresh clrlwi/clrlslwi in later blocks (C7DC, CCE0,
    starHitSetting, CA60/B66C); ours CSEs one conversion. Not an inlining artefact as far as tried; mw 2.5/2.7 builds
    give identical code, 3.0a3 is far worse.
  - Tautological loop conditions (x == x) fold after register allocation and keep extra saved registers (EAE0).
  - Empty-if compare chains survive in the target (95D8 tail) but are dropped in every C form tried.
Next session: characterSelectControls (71.7) and characterSelectAPress (75.2) are the biggest remaining wins; both
  should get the array-indexing treatment (check for hand pointer walks). Then cssUnloadScreen, fn_2_8CF8, randCharAlgo2,
  randCharBasedOnClass, B920 (copy block), C7DC. characterSelectABDirectionInputs' held param should become u16 once
  characterSelectControls is reworked (see its log).
Session 4: renamed fn_2_ABC0 -> cssSortCaptainChemistryOrder (approved); score unchanged 100%.
characterSelectControls (71.67) [S4]
  [1] full rewrite from asm, early returns instead of the goto dispatch; no #pragma dont_inline so closeZMenu,
      fn_2_A040(row, col, team, idx), fn_2_C698(idx, team) and cssCursorPort inline as in the target; slot search as a
      9-trip loop with break; params held/pressed/repeat; PAD_* button names -> 87.83
      REAL BUGS FIXED: Y (0x800) clear loop ran over rosterCharID[team][1..9] (index 9 = next row) - target is 1..8;
      Z (0x10) set F468[team+0x41] where the target sets 0x45 (profile shown), and checked the slot before the cursor 9/10 test.
  [2] cursor 9/10 rejection sound placed after the success path (`if (CSS != 9 && CSS != 10) {...return;} snd`), same as a goto -> 90.23
  [3] decl-order permutations of team/held/pressed/repeat/count: <=+0.01; moving the function before fn_2_A040: no change
  [4] characterSelectABDirectionInputs held typed u16 now helps both (Controls 90.34, ABDir 92.42) - kept
  remaining: register naming (target team r27 / count r28 / held..repeat r29-r31); target recomputes cursorPositions bases
      inside the inlined A040/C698 where ours CSEs a cP+2 base; `held = pressed` zero copy kept as li in ours.
characterSelectAPress (75.20) [S4]
  [1] dont_inline pragma removed so fn_2_60D4, fn_2_5184 and fn_2_C698 inline as in the target; challenge-lock test as
      static inline cssChallengeLocked() (mode == CHALLENGE && F468[0x3f]) -> 76.33
      REAL BUG FIXED: draft locked whenever the mode was Challenge OR F468[0x3f] (target: AND)
  [2] full structured rewrite from asm (s8 filled/freeCount/slot/variantRow locals initialised at the top, slot search loop
      with break, rosterCharID/positionSwapMapping/rosterSpotFilledInd/chemWCaptain fields, fn_2_C698 call in the tail) -> 92.95
      REAL BUGS FIXED: 2P duplicate check read charOnCharacterGridSelected[other] instead of F468[other + 0x41];
      challenge free-slot rejection lacked the "selected slot is occupied" condition.
  [3] simple-remove arm (variant query == 0) placed in the else; picked char read once into newChar -> 96.25
  [4] g_MatchInfo stores before the chemWCaptain store -> 98.27 (kept)
  [5] (u8)port in fn_2_5184's variant call: 5184 95.3 -> 88.3 (reverted); 25 decl permutations: none better;
      raw-offset chem read 96.05
  remaining: register naming only (team r30/captain r27 in target) + the inlined 5184's addRemoveCharVariantRelated arg.
Session 4 end: unit report 90.12 -> 92.17; characterSelectControls 71.67 -> 90.34, characterSelectAPress 75.20 -> 98.27,
  ABDir 92.13 -> 92.42 (held u16). fn_2_ABC0 renamed cssSortCaptainChemistryOrder.
fn_2_5184 (95.30) [S4] - inlined into characterSelectAPress, measured together
  [1] struct-field rewrite of the clear loop (s8/s32/u8 id): 76.6-78.9 (reverted; the raw s8 *cur indexing is what matches)
  [2] addOrRemoveCharacterToTeam gets the roster byte re-read (cur[...]) instead of the charId local -> 97.38 / APress 98.54
  [3] captain compared directly (no local), playerNumberByPort without the (s8) cast -> 99.27 / 98.63
  [4] updateCharacterSelectProcessCode(port & 0xFF, ...) - a fresh conversion instead of CSE with (u8)port -> 100% / APress 98.73
      ((u16)(u8)port: 97.44/99.02; u8 local: no change)
  readability pass: done (CSS_CURSOR, TRUE/FALSE). The rosterSpotFilledInd/chemWCaptain stores stay as raw cur offsets with a
  comment: the struct-field form drops 5184 to 79.2 and APress to 97.5.
  Lead: `x & 0xFF` reproduces the target's fresh clrlwi where `(u8)x` gets CSE'd - try it on C7DC, CCE0, starHitSetting, CA60.
u8 re-conversion pass [S5]
fn_2_CCE0 (93.93)
  [1] `port & 0xFF` on a u8 param: no effect (folded). Param retyped s32 with (u8)port indexes and `port & 0xFF` for the
      updateCharacterSelectProcessCode calls -> 96.74; rosterCharID/positionSwapMapping fields -> 97.30
  [2] previous-cursor store written as ((s32 *)lbl_2_bss_F468)[(u8)port + 2] (target adds base first) -> 100%
      readability pass: done (CSS_CURSOR, CHAR_ID_NONE / NUM_CHOOSABLE_CHARACTERS, TRUE/FALSE).
  Changing the CSS_PREV_CURSOR macro itself to that form: Controls/ReturnToCap/4970 up but fn_2_3624 95.03 -> 94.36 (rejected);
  try it per call site in 3624's siblings later. CSS_CURSOR as an s32 index: worse everywhere.
fn_2_C7DC (85.55) - did not respond
  [1] params u8 -> `& 0xFF` folds away. Params s32 with (u8) uses: 83.40; `& 0xFF` on setLineupSlot args / inMemRoster
      team index / captain index / fn_2_C698 arg: 83.31; setLineupSlot(s32, s32) indexing [team & 0xFF][slot & 0xFF]: 83.75.
      All below the u8-param version; reverted to it.
cssRandomFillRoster (80.04)
  [1] teamLogoDetermination / both updateCharacterSelectProcessCode calls take `team & 0xFF` -> 87.34 (kept);
      also masking the otherTeam xor: 85.60 (not kept); xor alone 80.00
  [2] other team's cursor as ((s32 *)&menuCursors[0x20])[otherTeam] (both reads) -> 95.39 (kept)
  remaining: target's fresh clrlwi before the xor (masking it costs elsewhere), dead r5 IV, register naming
fn_2_CA60 / fn_2_B66C / fn_2_B920 (shared initRosterSlot), scored together
  [1] lineup indexes as (slot & 0xFF) * 4 -> CA60 96.56->96.95, B66C 96.21->96.50, B920 77.29->77.41 (kept)
  [2] also masking the stored value: CA60 96.03 (worse); team & 0xFF in the lineup index: no change; slot & 0xFF in the
      inMemRoster index: CA60 95.63; in the C698-half read: all three drop hard; s32 params (with or without masks): CA60 ~77
  remaining: register naming; B920's copy block (unchanged)
Pass summary [S5]: CCE0 93.93->100, starHit 80.04->95.39, CA60/B66C/B920 small gains, C7DC did not respond.
CSS_PREV_CURSOR_S32 (s32-index form of the previous-cursor slot) [S5]
  New macro next to CSS_PREV_CURSOR; per call site:
  - fn_2_3624: every one of its 7 sites individually loses (93.8-94.4 vs 95.03) -> left on CSS_PREV_CURSOR
  - characterSelectBPress: each of its 6 sites alone loses (92.6-93.5), all 6 together 93.93 -> 94.02 (kept, all)
  - characterSelectControls: each site alone 90.50, both 90.66 (kept)
  - fn_2_4970: 96.99 -> 97.22 (kept)
  - fn_2_CCE0: already used the form (now spelled with the macro; still 100%)
  - fn_2_57F0's oldState pointer (&...[idx*4 + 8]): 93.73 -> 90.03 (not kept)

Naming pass (2026-11-20, no codegen change):
- Renamed: starHitSetting_Unused_maybe -> cssRandomFillRoster, cssReturnToCapSelect_maybe -> characterSelectBPress,
  stopShowingCaptainProfile -> closeZMenu, cssShowCaptainProfile -> cssOpenZMenu, cssToggleBottomOption -> cssToggleZMenuPage,
  cssCursorOnBottomControl_maybe (DOL) -> charGrid_moveCursor.
- The two work areas are now named cssWork (was lbl_2_bss_F468) and capSelectState (was lbl_2_bss_100B8); see
  include/menus/css_work.h. This file still declares them u8[] and uses the CSS_WORK_* / CAP_STATE_* offset defines
  and CSS_CURSOR / CSS_PREV_CURSOR / CSS_PREV_CURSOR_S32 (same bodies as before, now in css_work.h). Functions where
  the cast view compiles the same use CSS_WORK_VIEW.field / CAP_SELECT_STATE_VIEW.field; the rest are marked
  "kept as offset access: struct form changes codegen".
- Lead: declaring them as typed externs for the whole file (extern CssWork cssWork; extern CapSelectState
  capSelectState; cursor macros -> cssWork.lineupCursor[x] / lineupCursorPrev[x]) moved scores both ways:
  gains characterSelectBPress 94.10->96.34, teamReady1 89.92->94.38, characterSelectControls 90.81->91.19,
  fn_2_4970 97.22->97.46, fn_2_3624 95.51->95.54; drops cssRandomFillRoster 95.39->82.82, fn_2_57F0 93.96->87.93,
  fn_2_9F70 97.79->92.21, characterSelectABDirectionInputs 92.87->91.95, fn_2_B920 80.19->79.22. Not applied.
  Every other CSS file (text_76874, text_78F78, text_7BFF8, text_7E380, ...) gained or stayed identical with the
  typed externs. Declaring gameSetUpStep as GameSetUpStep here also nudges characterSelectControls 90.81->90.89.
- Process codes are CHAR_SELECT_PROCESS_* and the step bytes SET_UP_STEP_* (UnknownHomes_Static.h).

---

## Earlier independent pass (from another session, 2026-11-14; superseded by the log above, kept for its experiment notes)

### text_0323C second pass

Current verified state: .text80.51268% (baseline73.60118%). 19/66 matched (15 pre-existing +86EC/6884/B508/C698),42 functions improved; 87A8 exhausted99.30693%,46 pending. All51 initially unmatched functions have assessment/experiment entries, but full-file grind is not complete. Full ninja build and native git diff --check pass. No header/config changes or commits.

Baseline: configured per-unit objdiff, left target / right ours; rebuild succeeded. Source/header saved in text_0323C_second_pass/baseline.c and baseline.h. Full instruction baseline baseline.json.

.text: 73.60118%; no owned .data/.bss/.rodata sections in this split. Compiler GC/2.6 REL flags -O4,p -inline deferred -sdata 0 -sdata2 0. Source is an address-window split; no speculative split/rename.

| Function | Status | Baseline % | Current % |
|---|---|---:|---:|
| cssTransitionToNewScreen_maybe | pending | 87.572914 | 93.114586 |
| fn_2_33BC | pending | 78.34615 | 97.48077 |
| fn_2_348C | pending | 94.25926 | 94.25926 |
| stopShowingCaptainProfile | matched (pre-existing) | 100.0 | 100.0 |
| fn_2_3624 | pending | 62.496357 | 65.49879 |
| fn_2_4970 | pending | 57.669247 | 57.70793 |
| fn_2_5184 | pending | 88.87805 | 95.30488 |
| fn_2_52CC | pending | 86.64893 | 86.64893 |
| teamReady1 | pending | 85.56223 | 87.87983 |
| fn_2_57E8 | matched (pre-existing) | 100.0 | 100.0 |
| fn_2_57F0 | pending | 92.78306 | 93.733475 |
| fn_2_5F80 | pending | 65.11429 | 94.14286 |
| fn_2_6098 | matched (pre-existing) | 100.0 | 100.0 |
| fn_2_60D4 | matched (pre-existing) | 100.0 | 100.0 |
| fn_2_6138 | matched (pre-existing) | 100.0 | 100.0 |
| cssChangeScreens | pending | 90.73514 | 93.437836 |
| cssSelectCPUDifficulty | matched (pre-existing) | 100.0 | 100.0 |
| characterSelectScreenControlable | matched (pre-existing) | 100.0 | 100.0 |
| fn_2_6784 | pending | 85.3125 | 85.3125 |
| fn_2_6884 | matched | 93.24359 | 100.0 |
| fn_2_6AF4 | pending | 91.08219 | 94.79452 |
| cssUnloadScreen | pending | 76.62852 | 76.62852 |
| cssResetRosterStruct | pending | 49.06818 | 86.79735 |
| fn_2_7D44 | matched (pre-existing) | 100.0 | 100.0 |
| cssLoadingScreenRelated | pending | 79.751724 | 92.24138 |
| fn_2_86EC | matched | 91.35135 | 100.0 |
| fn_2_8780 | matched (pre-existing) | 100.0 | 100.0 |
| fn_2_8794 | matched (pre-existing) | 100.0 | 100.0 |
| fn_2_87A8 | exhausted | 98.11881 | 99.30693 |
| fn_2_893C | matched (pre-existing) | 100.0 | 100.0 |
| copyInfoToInMemRoster | pending | 76.10084 | 98.27311 |
| fn_2_8CF8 | pending | 73.52817 | 77.61268 |
| fn_2_95D8 | pending | 78.52051 | 79.36278 |
| fn_2_9ACC | pending | 85.31313 | 88.88216 |
| fn_2_9F70 | pending | 97.78846 | 97.78846 |
| fn_2_A040 | pending | 91.13636 | 91.64773 |
| fn_2_A1A0 | pending | 89.206894 | 90.155174 |
| fn_2_A288 | pending | 72.527954 | 72.534164 |
| fn_2_A50C | pending | 87.638885 | 98.541664 |
| fn_2_A62C | pending | 91.666664 | 91.666664 |
| fn_2_A6E0 | pending | 49.455128 | 89.42308 |
| fn_2_ABC0 | pending | 69.49505 | 74.19802 |
| fn_2_AEE8 | pending | 81.1107 | 82.52399 |
| fn_2_B324 | pending | 71.79339 | 76.66942 |
| fn_2_B508 | matched | 99.10112 | 100.0 |
| fn_2_B66C | pending | 64.17341 | 80.68786 |
| fn_2_B920 | pending | 65.20388 | 67.10922 |
| challengeSetRoster | pending | 85.43668 | 91.05677 |
| fn_2_C324 | matched (pre-existing) | 100.0 | 100.0 |
| fn_2_C484 | pending | 92.06015 | 95.48872 |
| fn_2_C698 | matched | 94.0 | 100.0 |
| fn_2_C7DC | pending | 65.7764 | 76.639755 |
| fn_2_CA60 | pending | 79.27152 | 79.27152 |
| fn_2_CCBC | matched (pre-existing) | 100.0 | 100.0 |
| fn_2_CCE0 | pending | 93.93259 | 93.93259 |
| cssReturnToCapSelect_maybe | pending | 65.29713 | 65.29713 |
| characterSelectAPress | pending | 69.13668 | 75.196655 |
| fn_2_EAE0 | pending | 70.117645 | 73.882355 |
| fn_2_EC34 | matched (pre-existing) | 100.0 | 100.0 |
| fn_2_EC54 | matched (pre-existing) | 100.0 | 100.0 |
| characterSelectABDirectionInputs | pending | 41.113075 | 81.96466 |
| randCharBasedOnClass | pending | 76.94203 | 83.18841 |
| randCharacter1 | pending | 76.51128 | 90.86466 |
| randCharAlgo2 | pending | 68.15167 | 82.63239 |
| starHitSetting_Unused_maybe | pending | 74.82269 | 77.758865 |
| characterSelectControls | pending | 71.2016 | 71.67023 |

## Hypothesis log

No prior checkpoint present at session start. Existing drafts audited against actual 66 target functions; 15 are pre-existing 100%. No return-only missing-logic stub except the actual 4-byte target fn_2_893C.

fn_2_33BC
  baseline: 78.34615%
  [1] Target has eight comparisons; draft skipped slot 3. Restored the complete structured slots 1..8 loop -> 97.48077% kept. Target reuses Challenge base as walking pointer; ours retains separate base and walk; investigate byte view.

fn_2_B508
  [1] Explicit u8 cast on charID argument hoists cached byte outside inner loop -> 97.05618%, reverted.
  [2] Correct local addRemoveCharVariantRelated prototype to existing mb_subfunc.h u8/u8/u8 -> 99.77528%, but regresses 8 siblings, reverted. Target calls narrow ABI. Remaining compare operand order and playerNumber load register.

fn_2_9F70
  [1] s32 input with narrow indexing, s32 xor result -> 94.23077%, reverted. Removes extra extsb but loses shared slot base.
  [2] Named s8 port index -> identical 94.23077%, reverted.
  [3] Named slot-table pointer -> 91.92308%, reverted.
  next: target preserves original incoming r3 for return while narrowing index into r0.

fn_2_A62C
  [1] Load val before inner pointer init -> 91.55556%, reverted.
  [2] Inner scan inline helper -> 73.977776%, reverted; introduces local result tests absent in target.
  [3] Explicit outer pointer walk -> 90.55556%, reverted.
  next: target has same operations but swapped value/inner pointer registers; investigate actual cursor struct fields/view. Note target compares signed s8 against 255, so do not silently change this to -1.

fn_2_33BC continued
  [2] Byte view with unsigned offset arithmetic completely folds walk -> 88.32692%, reverted. Signed offset restores same 97.48077%; named struct-index loop preferred.
  [3] Explicit pointer advance after body -> 96.76923%, reverted; before body -> 91.42308%, reverted.
  [4] Named SavedChallengeSlot array pointer -> 96.76923%, reverted.
  [5] Loop 0..8 skipping slot0 -> 45.673077%, reverted.
  next: retained complete structured loop. Exact target pointer progression unresolved.

fn_2_348C / cssLoadingScreenRelated
  [1] u8 flag -> 91.17284%, reverted (adds bit extraction); flag is BOOL/int.
  [2] Target-before-flag declaration order -> 93.950615%, reverted.
  [3] Top-level locals, target-first comparison and named struct fields -> codegen identical 94.25926%; readability retained.
  [4] cssLoadingScreenRelated calls existing fn_2_348C instead of copied body -> 80.4069%, kept; compiler auto-inlines. Target has no bl to fn_2_348C anywhere in menus.
  [5] Inner availability inline helper -> standalone98.27161%, caller80.31207%; reverted because caller regressed its new best. Swapped helper parameters codegen identical.
  [6] Exhaustive 24 local declaration permutations with helper: standalone98.27161/98.51852, caller80.31207/80.34655. All rejected against caller80.4069 floor. Full results decl_sweep.json.
  next: caller still 248 bytes short; do not accept a standalone gain at its expense.

copyInfoToInMemRoster
  baseline76.10084%
  [1] s8 charId local -> identical, reverted.
  [2] Existing CharacterStats copy helper from mb_subfunc/orderchange, typed fields -> codegen identical; retained readability.
  [3] Target tail contains two separate 9-character copy loops rather than draft's manually expanded merged loads. Restored via copyRosterCharacterIDs helper ->80.2437%, kept; no siblings moved.
  [4] Plain static vs static inline helper, while vs for loop -> identical80.2437%; retain static inline for loop.
  next: target tail has redundant initial count guards, absent in ours; source947? current932 bytes vs target952. Target packed FieldingArm extraction is 8 bits versus ours7, indicating a missing/incorrect packed-byte view. Main remaining register allocation is outer/inner loop live ranges.

fn_2_86EC
  baseline91.35135%
  [1] Correct portrait helper declaration to actual u8 scene/s8 charID prototype ->100%; kept using existing File_0x800203e0.h header.
  readability pass: done. Uses SceneChangeState._12[0] preserving byte width, GAME_TYPE_CHALLENGE. Scene10/menu-state2 have no established enum; unknown _12 and F468 flags retain literal0 because boolean domains unproven.
  final source:
```c
void fn_2_86EC(void) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE && lbl_8037169C._12[0] == 0) {
        challenge_setTransitionScreenCharacterPortrait(10, (s8)lbl_2_data_3CE0[g_Challenge.opponentCaptain]);
    }
    cssLoadingScreenRelated();
    cssResetRosterStruct();
    lbl_2_bss_F468[0x56] = 0;
    menuControlVariables->currentState = 2;
}

```

Current .text73.78949%; 15 pre-existing100s preserved, one newly100. Whole-unit scores and source saved best.json/best.c.

copyInfoToInMemRoster continued
  [5] Widen packed byte local from u8 to int with /2 ->78.4874%, rejected. Arithmetic shift + explicit 0xFF mask matches target extrwi8 (target consumes packed bits1..8) and signed remainder ->80.28571%, kept.
  [6] Hoist inner pointer declarations before outer pointers ->81.54622%; move src declaration after outer pointer declarations ->82.5126%, kept.
  [7] Replace tail helper with ordinary 9-slot for loops using existing player counter ->94.033615%; named reusable match/cursor pointers ->96.55462%; restore enclosing two-team loop ->97.52521%. Target redundant inner guards arise from outer-loop unrolling, not an inline helper. Kept nested loops; helper now unused and to be removed.
  [8] Relocate pointer increments into for clauses ->identical, reverted to simpler body increments.
  [9] Compute dst/lineup via team indexing instead of explicit outer base pointers ->98.231094%; s8 cursor pointer ->98.27311%, kept. CharacterStats destination pointer + field names ->neutral, kept.
  next: target and ours have the same core copy, but register allocation/loop increment scheduling remain. Target's outer bases in r21/r20 vs ours r26/r25; tail pointer increments scheduled in opposite order. Avoid redoing hypotheses above.

fn_2_5F80
  baseline65.11429%
  [1] Restore ordinary nine-slot scan and reload aliased source lineup byte after each possible cursor store (draft cached it across all nine). ->90.6%, kept.
  [2] Hoist pointers and counters to function scope in target access order ->90.88571%; scalar order team/player/g ->90.74286 rejected alone. Compute outer bases from team index with this order ->94.14286%, kept.
  next: register/scheduling only, target280 bytes vs current276; target direct outer pointer bases use extra different registers. Target really reloads each byte because cursor/lineup may alias; do not cache it.

fn_2_A62C continued
  [4] Signed cursor view + pointer/value local reorder ->91.55556%, reverted.

fn_2_6784 / cssUnloadScreen
  [1] Move random table+0xC pointer initialization outside do loop, BOOL flag ->74.84375%; narrow u8 flag ->75.78125%, rejected. Target narrow flag width preserved (do not blindly widen this one).
  [2] Replace cssUnloadScreen's duplicate Bowser roster body with fn_2_6784 call ->68.425705% vs76.62852 baseline, rejected. Compiler does not produce the right inline. Original retained.

fn_2_5184
  baseline88.87805%
  [1] Target stores F468[port+0x43]=1 at completion; draft omitted it. Restore plus CHAR_ID_NONE ->95.04878%, kept.
  [2] Unsigned raw ID temp with signed comparisons/call casts ->94.98781%, rejected.
  [3] Signed cursor byte view ->95.30488%, kept; matches target -1 sentinel load.
  next: target keeps separate raw byte and signed temporary across captain comparison and call; ours collapses it. Saved-register ordering also differs.

fn_2_52CC
  target audited: first constant count store is indexed stwx from unfolded index1; source fixed offset store folds it. No omitted logic found. Pending inline-boundary hypothesis, not exhausted.

cssTransitionToNewScreen_maybe
  baseline87.572914%
  [1] Separate cases1 and2 around case3 (target keeps two physical set803c5f77 calls) ->91.447914%, kept.
  [2] Cached global state pointer ->82.0625%, rejected; local case4 pointer neutral, rejected as unnecessary.
  [3] Use actual controllerInputs[port].newInput field ->93.114586%, kept. Temporary wrong member spelling failed build; no stale diff consumed; corrected from header.
  [4] Use aiPosSwapInputs._CF5F[0] named field ->neutral, kept.
  next: only case4 remaining; target materializes state base with addi and schedules stores before the aiPosSwapInputs access, ours emits direct @l store with different scheduling. No speculative volatile.

randCharacter1
  baseline76.51128%
  [1] Target caches captainSelectedID/chemistry base before roster loop; draft reloaded after external calls. Hoist teamBase ->90.86466%, kept. Declaration position neutral.
  next: remaining differences in preheader scheduling, settings/stats base register swap, u8 call-argument materialisation and signed player load. Target and ours main/tail loop logic now agree.

randCharAlgo2
  baseline68.15167%
  [1] Target reloads aliased roster-order byte after each selected-flag store; draft cached it. Use byte pointer ->75.16196%, kept.
  [2] Target buffer accesses use extsb and -1 sentinel, not unsigned255. Preserve s8 CHAR_ID buffer ->75.344475%, kept.
  [3] Restore nested four-variant loop instead of handwritten conditions; target has lhau iteration ->79.982%, kept.
  [4] Cache u8 port index for all indexing (draft incorrectly used full-width port in roster loop) and initialize empty count before first calls ->82.63239%, kept.
  [5] Cached stats byte-base inside first-loop scope ->79.05656%, rejected.
  next: first-loop global address pooling / source views still differ; target1556 bytes vs ours at current snapshot (see current.json). Remaining tail and sorting structure need audit.

cssLoadingScreenRelated continued
  [7] Whole-unit call audit found one missing addRemoveCharVariantRelated call site. Target asm proves an entire missing Challenge roster reconciliation loop after recruitment flags: mark slot selected, addOrRemove(0,id,1), addRemoveVariant(0,(u8)id,2), then scan all 9x5 pair entries, mark group members until -1 sentinel. Restored structured multi-loop stop flag ->87.89483%, kept as intermediate.
  [8] Five sentinel exits share the physical outer-slot continuation in target; measured structured flag adds tests. Shared continuation label ->92.24138%, kept. Goto justified by three-level exit threading, measured alternative above. Missing-loop fix is semantic, not just allocation.

cssResetRosterStruct
  baseline49.06818%
  [1] Target inlines fn_2_33BC; draft's pasted copy skipped slot3 and read slot9. Replace with existing function call ->51.844696%, kept and auto-inlined; fn_2_33BC sibling remains97.48077.
  [2] Target previousScreen9 loop preserves captain slot0 and clears slots1..8; draft inverted condition. Correct j!=0, CHAR_ID_NONE. Score neutral, semantic fix retained.
  [3] Target's stat-row pack loop unrolls eight iterations. Draft duplicates row indexing twice, exceeding pre-CSE unroll budget. Single typed CharacterStats* row local ->69.195076%, kept.
  [4] Replace nine manual handedness assignments and impossible if(0>=9) guard with ordinary loop. u16 character index ->67.132576 rejected; target uses lha, so correct signed existing charID ->71.429924%, kept.
  [5] Restore target physical branch order: main previousScreen!=9 branch first, reset in else ->82.42424%, kept.
  [6] Restore one-player positive flag branch and zero-arm store order ->82.469696%, kept. Target final no-available-character test is ==0, draft !=0; correct ->82.479164%, kept.
  [7] Target availability loop is6x8=48 (no remainder), draft54. Correct bound48 ->80.916664% intermediate regression; move zeroCharCount initialization to function entry (target keeps it live in r31 across calls) ->86.79735%, kept, all prior best floors preserved.
  next: target and ours now contain correct full branches and signed indices. Remaining register/scheduling mismatches; inspect per-function diff. Literal48 has no established named character subset constant, preserve exact observed bound.

Current verified .text76.71911%; all15 pre-existing100s and new fn_2_86EC100 preserved. 66 target symbols total. Current build succeeded; current/best snapshots retained under text_0323C_second_pass.

characterSelectABDirectionInputs
  baseline41.113075%
  [1] Target handles movement/profile-disabled branch first, source reversed both large regions. Restore equivalent structured if/else in target order ->78%, kept.
  [2] Target tail narrows profile-dismiss result to u8; actual standalone stopShowingCaptainProfile has that exact contract. Replace two handwritten toggle copies with existing call, automatically inlined ->79.024734%, kept; standalone remains100.
  [3] Signed s8 computed port for charSelectStruct, signed playerNumber load before zero comparison ->79.947%, kept.
  [4] Actual cursor helper input arguments are narrow16 (target passes original u16 values without integer extension); correct local prototype ->81.96466%. Initially regresses characterSelectControls, withheld until caller fixes below preserve its baseline. Kept after caller review.
  next: profile-side state pointer lifetimes, cached controller cursor pointer versus indexed store, original four saved registers versus ours six. No repeated tail-toggle/branch reordering experiments.

characterSelectControls
  baseline71.2016%
  [1] Target disables input when gameSetUpStep[team+0x5D] !=0; draft test inverted. Corrected.
  [2] Use existing inlined stopShowingCaptainProfile for trigger dismissal; cursor-helper narrow16 declaration with current s32 input locals ->70.8745%, not accepted alone.
  [3] Preserve actual u16 held/pressed/repeat local widths from lhz loads ->71.67023%, kept, allows AB sibling81.96466% without any best regression.
  next: bulk variant handling source remains pasted in caller; inspect target control flow and lost reloads. Input-disable correction is semantic.

fn_2_A1A0 / fn_2_B66C
  baseline A1A0 89.206894%; B66C64.17341%
  [1] Target B66C empty slot block is A1A0(i,1); draft inverted CPU condition and used wrong second cursor offset9 vs11. Plain function call does not inline (ours536 bytes vs target692), B66C59.404625%, rejected.
  [2] Explicit inline shared body required after measured plain-call refusal; copy existing A1A0 body as fillUnassignedRosterSlot ->B66C71.68208%. Existing standalone delegates to same body ->A1A090.155174%, kept, no extra object symbol emitted.
  [3] Restore switch physical case order0/1/-1, target's two distinct addOrRemove calls rather than collapsed ternary, and valid slot branch before empty branch with u8 index ->B66C80.68786%, kept.
  next: caller source index/pointer lifetime still differs. Shared body now removes duplicate logic; no speculative ABI changes. Actual target wait loop exists, so do not 'fix' infinite wait semantics without evidence.

challengeSetRoster
  baseline85.43668%
  [1] Target initializes missing captain row to signed -1 before memset and truncates only successful assignments. Draft u8 last silently made sentinel255. Correct s32 last=-1 and assignment(u8)i ->91.05677%, kept.
  [2] Shared empty-slot inline helper from A1A0 ->87.187775%, rejected against91.05677 best; original explicit body retained. Same behavior can need different inline/source shape per caller.
  next: remaining pointer/register scheduling; target916 bytes. Preserve correct signed default.

teamReady1
  baseline85.56223%
  [1] Target reuses function-level loop index in Challenge copy and compares CPU mode unsigned. Reuse i instead of block idx, u8 mode ->87.70815%, kept.
  [2] Replace duplicated setup block with existing fn_2_52CC call; compiler auto-inlines ->87.87983%, kept, standalone remains86.64893 baseline.
  next: Challenge pointer/local declaration lifetime and unfolded indexed state-store (shared with52CC) remain. No evidence for omitted calls.

Latest verified whole unit: .text77.88867%. 15 pre-existing100s + fn_2_86EC100 preserved. All functions at or above session baseline and accepted sibling bests. No config/shared-header changes; owned header restored byte-equivalent baseline.


Resume reconciliation: verified .text79.38962%, all accepted bests and sixteen100 functions preserved. The prior latest text score77.88867 above is historical.

randCharBasedOnClass
  [1] Signed CHARACTER_CLASS buffer, switch reload from buffer, E(u8,BOOL) full flags (target truncates), and unsigned grid-byte candidate IDs widened to s16 ->77.978264%, kept.
  [2] Restore physical switch order0/1/2/3 ->78.00543%. Incorrect3/0/1/2 order77.42029 rejected.
  [3] Class counts/flags order1/2/3/0 and delay cursor initialization until after memset ->80.804344%, kept.
  [4] Second-loop walking cursor ->82.672104%; first-loop walking cursor/class pointers ->83.18841%, kept.
  [5] Remove cached narrow port ->80.679344%; shared candidate collection helper ->80.41848%; rejected.
  next: candidate write pointer and register lifetime differ; signed byte-buffer semantics now correct.

characterSelectAPress
  [1] Target has one common cursor sound after auto-inlined fn_2_5184. Replace copied block with actual helper call ->71.26499%, kept.
  [2] Draft compared slot position to captain character ID and chose last match. Target compares to signed current state position and stops at first of nine matches. Restore correct position load and structured loop ->75.196655%, kept.
  [3] Existing fn_2_60D4 getter replaces duplicate three-way captain selection, auto-inlines neutrally, kept.
  next: large variant body still needs flow/alias audit.

fn_2_EAE0
  [1] Draft flag uninitialized on inactive port. Target initializes from signed playerNumberByPort then conditionally substitutes port0-is-team0. Correct ->73.882355%, kept.
  next: repeated global reloads and pointer alias lifetime differ. Target really has the infinite active-port loop; do not invent an exit.

fn_2_A50C / fn_2_A6E0
  [1] Whole-body overlap helper shared by target A50C and two A6E0 expansions. Explicit static inline findRosterOverlap with public tail-return wrapper ->A50C98.541664%, A6E079.753204%, kept. Inner-only helper experiments in A62C were a distinct rejected boundary.
  [2] A6E0 second branch target uses A62C sentinel-aware scan, compares signed byte to255, and loops physical state indices1..2. Replace incorrect pasted -1 tests with existing auto-inlined A62C calls and explicit boolean stores ->88.56731%, kept.
  [3] Initialize count at entry and conditionally increment first slot; state array target uses signed -1 sentinel. Correct owned extern to s8 and sentinel stores to-1 ->A6E089.42308%, kept; A28872.534164% side gain, no sibling loss.
  [4] Swap overlap val/inner initialization ->A50C unchanged, A6E089.39103%, rejected and restored. Whole-unit rebuild confirms best79.38962%.
  next: A50C residual base/value register allocation; A6E0 remaining scheduling and indexed state access. No new emitted helper symbol.

fn_2_C698 / fn_2_C7DC
  [1] C698 target explicitly truncates idx and variant charID, but casts in flattened source shift allocation ->84.07407% vs94 baseline, rejected.
  [2] C7DC existing C698 call for entire duplicate tail auto-inlines but65.72671% vs65.7764 baseline, rejected.
  [3] C7DC target uses one incrementing roster pointer across both team checks. Replace indexed draft loads with explicit pointer walk ->71.82609%, kept. Whole-unit79.45803%, no sibling loss.
  next: C698 needs inline/context boundary rather than independent ABI casting; C7DC preheader register lifetimes and intertwined lineup stores still differ.

fn_2_CCE0
  [1] Whole-body inline boundary ->93.93259% unchanged, removed unnecessary helper. Target duplicates narrow port conversion at outgoing call while ours shares earlier conversion; remaining type/context issue, not missing scan logic.
fn_2_CA60
  [1] Replace duplicate selection tail with existing C698 ->69.80132% vs79.27152 baseline, rejected. Target shares pointer/index from first block across tail, helper hides that lifetime. Preserve original.
fn_2_C484
  [1] Replace duplicate variant search with existing matched fn_2_C324; auto-inline ->95.48872%, kept. Whole-unit79.49006%, no sibling loss.
  next: target raw ID/result lifetimes and register allocation remain.

fn_2_6884
  [1] Existing C324 helper replaces duplicate variant search ->99.63461%, kept. Whole-unit79.56009%. Remaining only two outer base registers swapped (cursor vs lineup).
  [2] Explicit initialized cursor/lineup bases ->91.95513%, rejected. Keep compiler-generated loop induction bases99.63461.

fn_2_6AF4 [1] Typed CharacterStats row pointer with explicit team/slot indexing ->94.79452% vs91.08219. Kept, whole-unit79.59816. Target additive addressing restored; remaining induction-base register scheduling.

fn_2_B324 [1] Target increments two captain IDs across loop, rather than adding i each iteration. Restore induction variables ->76.66942%, kept; whole-unit79.6396. Target intentionally retains unreachable trailing fill loop; preserve it.
  [2] Explicit roster pointer in first loop ->76.264465%, rejected against76.66942. Remaining interleaved store scheduling and shared base lifetimes.

fn_2_ABC0 [1] Target stores value buffer at stack8/order40 and caches u8 current maximum across inner sort. Restore buffer declaration order and cached best ->73.376236%, kept. Whole-unit79.69467; sorting pointer and first copy induction still differ.

fn_2_AEE8 [1] Same target cached u8 current maximum in inner sort ->82.52399%, kept. Whole-unit79.72157. Remaining outer-team addressing and induction scheduling.

fn_2_ABC0 [2] Restored original array declaration order after measured MWCC reverse stack placement; typed CharacterStats indexing ->74.19802%, kept. Prior buffer-order claim was inference corrected by instruction diff.
  [3] Explicit first-loop walking source + byte load before order store ->58.683167%, rejected. Source pointer aliasing changes unroll/scheduling drastically.

fn_2_9ACC [1] Replace two handwritten CharacterStats field-copy blocks with existing typed copyCharacterStats helper; actual auto-inline ->88.88216% vs85.31313, kept. Whole-unit79.807686. Remaining snapshot/lineup store interleaving and outer registers differ.

fn_2_8CF8 [1] Four handwritten stats-copy expansions replaced with existing typed helper, preserving snapshot/lineup writes ->77.61268% vs73.52817, kept. Whole-unit79.97064. Target helper interleaving remains source-context dependent.

fn_2_4970 [1] Restore ordinary nine-slot last-match scan instead of handwritten independent ifs. Narrow slotIndex experiment56.373306 rejected; retain s32 ->57.70793%, kept. Target scan really has no early break (unlike APress). Remaining variant reconciliation and pointer reloads need audit.

fn_2_B920 [1] Shared empty-slot body fillUnassignedRosterSlot(i,0) replaces pasted scan with inverted mode predicate, matching confirmed A1A0 body ->67.10922%, kept. Whole-unit80.02718. Remaining roster state initialization and outer table pointer scheduling.

fn_2_95D8 [1] Target second hover branch writes status[1], default writes both; draft wrote only status[0]. Correct stores, u32 status comparison and u8 mode widths ->79.36278%, kept. Whole-unit80.04594. Tail target contains no calls or stores, but retains state comparisons absent in ours; no fabricated side effects added. First-loop helper/source scope and final empty tail comparisons remain.

fn_2_A288 [1] Restore nested eight-byte scan loop ->66.7205% vs72.534164 current best, rejected. Target bound8 confirmed, no omitted ninth slot. Remaining pointer view/state byte alias scheduling.

starHitSetting_Unused_maybe [1] Restore walking three-by-three cursor scan from indexed hand expansion; preserve target extra counter increment per group ->77.758865%, kept. Whole-unit80.07501. Remaining header scopes and dispatch register assignment.

fn_2_3624 [1] Target checks disabled state after memset before reading controller input. Move input copy after guard ->63.413765%, kept. Whole-unit80.154594. Draft cached global views span large control regions unlike target reloads.

fn_2_3624 [2] Remove cached whole-function state/cursor pointers; direct global views let target-style reloads stay within branches ->65.49879%, kept. Whole-unit80.335464. Further branch/case and inline toggle audit pending.

cssReturnToCapSelect_maybe [1] Extract Challenge lock test to BOOL inline returning normalized comparison ->65.29713 unchanged, removed unnecessary helper. Target normalizes result despite branch use; original helper return type remains uncertain.
  [2] Remove s8 captain comparison cast and shifted pointer ->64.75494%; original pointer only64.81598%; nested3x3 scan65.04398% (outer index stride2 neutral). All below65.29713, rejected. Target compares full captain word, but draft cast removal changes broader allocation; unresolved, retain baseline until combined fix preserves best.

cssChangeScreens [1] Remove cached whole-function state pointer, use direct global state fields after calls ->93.437836% vs90.73514, kept. Whole-unit80.37058. Remaining store address materialization and reset loops.

fn_2_57F0 [1] Target reloads backup state slot at comparisons, draft retained scalar across potential state alias writes. Use pointer to stored backup ->93.733475%, kept. Whole-unit80.40289. Remaining narrow parameter lifetime and physical switch block order.

fn_2_87A8
  [1] Explicit signed player local ->98.11881% unchanged.
  [2] Explicit setting pointer ->98.11881% unchanged. Both removed; target/ours identical opcode/order with register permutation. No omitted logic. Remaining probable local/header inline context; no speculative helper emitted.

fn_2_A040 [1] Eliminate temporary pair pointer, direct variantPairs accesses ->90.85227% vs91.13636, rejected. Main scan opcode/order matches except compare operand/base register permutation; tail index scheduling differs. Full loop/fallback logic audited, no missing operation found.
fn_2_B920 [2] Target switch order0/1/-1 ->67.101944%, rejected against67.10922. s32 row indices plus unsigned table comparison66.72573%, rejected as combination.
fn_2_B920 [3] Unsigned table comparison alone66.68689%, rejected. Full best restored.

Readability cleanup: repaired nesting indentation in Reset/AB direction/class selector; named class enums, TRUE and established CHAR_ID sentinels. Whole-unit rebuild/rediff neutral80.40289, all best floors preserved.

fn_2_B508 [3] New local ABI experiment: function-type cast at this call to authoritative u8(u8,u8,u8), avoiding global-prototype sibling regressions. MWCC still emits direct bl;99.77528%, kept, all sibling floors preserved. Commuting source equality neutral. Remaining compare operand orientation and signed player load register. Cast is transitional readability limitation until all callers support correct global declaration.

fn_2_B508 [4] Preserve signed playerNumber in explicit block-local s8 before team call ->99.88764%, kept. Only compare operand order remains.

fn_2_B508 [5] Explicit signed character ID local before equality preserves target compare operand orientation ->100%. Saved immediately; mandatory readability follows. All sibling bests preserved, whole-unit80.408516.

fn_2_B508 readability pass: done. E(s8,CHAR_ID), named rosterCharID/rosterSpotFilledInd/charOnCharacterGridSelected fields, NUM_CHOOSABLE_CHARACTERS and FALSE replace raw values; whole-unit neutral80.408516 and function100. Lineup slot indices remain numeric (array indices), team1 retained (no proven team enum). Purpose: clear second-team noncaptain slots/variant selection; possible name resetSecondTeamRoster is medium confidence, left unchanged.

fn_2_A040 [2] B508 comparison-local finding applied on new evidence: explicit signed ID local fixes compare operand orientation ->91.64773%, kept. Remaining cursor/target register swap and tail index scheduling.

fn_2_6884 [3] Named cursor roster fields ->99.63461% unchanged, kept for readability; no width or alias change.

fn_2_6884 [4] Store cursor ID before lineup assignment in source; scheduler still emits target lineup store first but now allocates cursor base first ->100%. Saved immediately; mandatory readability follows.

fn_2_6884 readability pass: done. Removed unused copied-search declarations; E(s16/u8,CHAR_ID), TRUE, CHAR_ID_NONE, ARRAY_COUNT with preserved signed bound, named roster/grid fields. Whole-unit rebuild neutral80.41568 and function100. -1 variant-row result remains numeric because it is an index sentinel, not a character ID. Purpose restore saved Challenge lineup and mark variants; suggested restoreSavedChallengeLineup medium confidence only, no rename.

fn_2_A50C / A6E0 continued
  [5] Explicit signed comparison local plus loop-local outer val ->A50C87.638885 (regression), A6E090.0641 (gain), rejected as combination. Retain function-level val; explicit other local alone codegen-neutral. Boolean helper returns named TRUE/FALSE and address annotation moved to public function.

Overlap helper readability cleanup verified neutral80.41568; accepted per-function floors unchanged.

fn_2_C698 [2] New B508 ABI evidence: correct call-site function type only ->94.49383%, kept, all siblings neutral. Existing earlier failed cast experiment also changed idx width; isolated correct ABI now gains.

fn_2_C698 [3] Structured if/else with per-branch narrow ID ->90.27161%, rejected alone. Shared function-level s32 signed ID (target preserves signed full value across calls then truncates variant arg), explicit narrow idx and block-local signed player ->100%, kept. This also removes all draft gotos. Whole-unit80.449814, all sibling floors preserved. Saved before readability.

fn_2_C698 readability pass: done. Structured flow removes gotos; E(s32,CHAR_ID) preserves evidenced signed register width, named roster/grid/player fields, TRUE, GAME_TYPE_CHALLENGE, P2_CPU_CODE_1_PLAYER_GAME. Team numbers retain numeric values without proven enum. Whole-unit neutral80.449814, function100. Purpose mark selected roster slot and variants, candidate markRosterSlotSelected medium confidence, no rename.

fn_2_C7DC [4] Retest existing C698 call on new evidence: its body is now100% with corrected signed register/ABI semantics. Replaces duplicate tail ->76.639755%, kept vs71.82609 best. Whole-unit80.50425; earlier old-body call rejection remains valid history.

fn_2_CA60 [2] New100 C698 tail call71.5894% vs79.27152 baseline, rejected. Shared first-block cursor index still lost; target value must remain in full signed register, testing width separately.
  [3] CA60 signed full-register charId alone78.013245 rejected alone; correct local variant ABI together restores79.27152 baseline exactly, no sibling regressions. Both kept as evidenced signed/ABI correction; header parameter width hypothesis pending coordination.

Latest whole-unit80.50425; corrected C698100 helper raises C7DC76.639755, CA60 width+local ABI combination neutral at original79.27152. All19 matched functions and all accepted floors preserved.

Unused pasted-search/old tail declarations removed from C484/C7DC; rebuilt whole-unit neutral80.50425. Full ninja build succeeded exit0; native git diff --check clean. Owned header/config remain unchanged.

fn_2_87A8 [3] B508-style block-scoped player temp tested on new evidence ->98.11881 unchanged, removed. AtBat header has no +4 input field; raw access remains justified.

fn_2_87A8 [4] After inline/temp/width hypotheses, move initial cursor value declaration after pad and held ->99.0099%, kept. No statement or lifetime semantic change; remaining input registers only.
  [5] Swap pad/held declaration order after value declaration fix ->99.0099 unchanged, removed.
  [6] Commute pointer-add operands ->99.0099 unchanged, discarded.
  [7] Typed u16 input pointer ->99.0099 unchanged, removed.

fn_2_87A8 [8] Widen loaded input local to u32 while preserving lhz access ->99.30693%, kept. Matches target pointer/result register reuse; remaining player/address preheader only.
  [9] Full-register block-local player temp after held width correction ->99.30693 unchanged, removed.
  [10] Inline pointer-getter boundary (common PAD-record chain also present in menus/rep_1028.c and rep_0788.c) ->99.30693 unchanged, removed. Supported stop: same instructions/order/widths, residual player-address preheader register permutation; direct-expression, temp scopes, pointer view, declaration grouping, input width and plausible getter boundary all measured. Mark exhausted until new inline/TU evidence.

Final current checkpoint reconciliation: .text80.51268%,19/66 matched,42/51 initially unmatched improved, no original or accepted-best regression. 87A8 supported exhausted99.30693;46 other functions remain pending, so this is resumable work, not full-file completion. Header parameter-width hypothesis still coordinated with root; no header/config edits.
