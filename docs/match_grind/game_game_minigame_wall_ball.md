# game/game/minigame/wall_ball -- match checkpoint

Session: match-sonnet first pass, 2026-10-02. File started as 13 `return;`
stubs with no checkpoint. All 13 drafted from target asm + Ghidra decompile
this session; three reached 100% and got the mandatory readability pass.

## Baseline -> current

| section | baseline | current (S1) |
|---|---|---|
| .text   | 0.7258515%  | 46.9877% |
| .rodata | 76.92308%   | 87.5% |
| .data   | 0.0%        | 0.0% (see Open questions -- jump table, likely external) |

(No `.bss` for this unit.)

## Status table

| function                        | status  | baseline | pct (S1) |
|----------------------------------|---------|----------|----------|
| fn_3_11391C                     | matched | 0%       | 100.0%   |
| fn_3_113950                     | matched | 0%       | 100.0%   |
| fn_3_114A2C                     | matched | 0%       | 100.0%   |
| fn_3_1149B8                     | pending | 0%       | 91.69%   |
| wallBallMultiplayer_AIControl    | pending | 0%       | 67.29%   |
| wallBallDropInNewWalls           | pending | 0%       | 67.16%   |
| fn_3_113D20                      | pending | 0%       | 58.53%   |
| fn_3_113EC0                      | pending | 0%       | 54.95%   |
| wallBallAIPitches                | pending | 0%       | 53.21%   |
| wallBallCalc_WallsBroken          | pending | 0%       | 48.38%   |
| wallBallRotatePitchers            | pending | 0%       | 34.35%   |
| wallBallCalculateNewWalls         | pending | 0%       | 31.97%   |
| wallBallSomething2                | pending | 0%       | 20.95%   |

`matched` rows had the mandatory post-100% readability pass applied
(enum/TRUE-FALSE substitution) and were re-diffed to confirm they stayed
100%.

## The real finding this session: g_Minigame's wall-ball data layout was wrong

Before drafting any function, I had to fix `include/game/UnknownHomes_Game.h`
(`MiniGameStruct`). Cross-checking three independent functions' raw asm
against each other proved:

- **`wallBallStruct` (was a single `MaybeWallBallStruct`, 0x44 bytes, at
  0x72C) is really `WallBallWallStruct wallBallWalls[7]`, stride 0x2C.**
  Evidence: `fn_3_113D20`'s loop walks `&g_Minigame + i*0x2C` directly and
  separately indexes `+0x72C` off that; for i=1 that lands at 0x770 (one
  past the old single-struct's end) and for i=6 the walk's last byte lands
  exactly where `barrels[15]` (an *already-matched, already-used-by-
  barrel_batter.c* field) begins at 0x860. 7*0x2C == 0x860-0x72C exactly.
  Field offsets within one 0x2C record, cross-validated from
  `wallBallCalc_WallsBroken`, `fn_3_113950`'s sibling `fn_3_113D20`, and
  `wallBallCalculateNewWalls`'s `coinRelated[idx*0x2C ± k]` arithmetic:
  `xPos(0x0) yPos(0x4) zPositionOfSomeWall(0x8, already named) targetX(0xC)
  targetY(0x10) targetZ(0x14) wobbleAngle(0x18) wobbleAngleVelocity(0x1C)
  wobbleAmplitude(0x20) wallPower:s16(0x24) _26:s16(0x26) wallState:u8(0x28)
  coinGenerationCategory:u8(0x29, already named) setupOrderIndex:u8(0x2A)
  pad(0x2B)`. `setupOrderIndex` is confirmed by raw asm in
  `fn_3_1149B8`/`wallBallCalculateNewWalls`: it's a 0-6 stable-sort
  tiebreak index, rewritten after every `fn_800246D4` sort call.
- **`wallBall_coinCoordinates`/`wallBall_coinVelocity` (single `VecXYZ`
  each) are really `VecXYZ[100]`.** `fn_3_113950` walks both with a 0xC
  stride for 100 (`0x64`) iterations; 100*0xC == the exact byte gap to the
  next already-named field in both cases (0xCD0->0x1180 and
  0x1180->0x1630).
- **`wallBall_coinsVisibleFrameCounter`/`wallBall_coinsVisibleInd` (single
  scalars) are really `[100]` too**, same proof (gap to `miniGameCurrentPoints`
  at 0x1890 and to `panelHitInd`'s block at 0x199E match exactly).
- `wallBallWaitingLocations` retyped `f32[4][2]` (was flat `f32[8]`) --
  Ghidra's own decompile already treated it 2D.

All of this was **unreferenced by any existing `.c` file except one**:
`fielder.c`'s `updateFielderPositionBasedOnBallState` had worked around the
single-`VecXYZ` wrongness with `(&g_Minigame.wallBall_coinCoordinates)[i]`
casts and a (buggy, loop-invariant) `if (g_Minigame.wallBall_coinsVisibleInd)`
test. Fixing the header broke that cast syntax (compile error -- good, it
caught the inconsistency), so I rewrote it as plain `[i]` indexing and fixed
the `[i]` the visible-ind test was missing. That function went from **97.66%
-> 100%** as a side effect, not a regression. Confirmed byte-identical
rebuild of barrel_batter/bobomb_derby/kinoko/toy_field_offscreen/
minigame_fielder_anim/batter_ai (none of them touch this region) and full
project build (`4 files OK`, REPORT/PROGRESS clean) both before and after.

**Opus pass should sanity-check `setupOrderIndex` vs the one remaining
unaccounted byte (0x2B, left as `pad`)** -- I only found evidence for 0x2A:
confirmed via `fn_3_1149B8`'s comparator (`wallA->setupOrderIndex -
wallB->setupOrderIndex`) and `wallBallCalculateNewWalls`'s post-sort
renumbering loop (`stb r5, 0x756(r3)` where 0x756 == 0x72C+0x2A). 0x2B has
no observed access in this file; may be genuine padding, or may be read by
a function outside this unit.

## Key helper/data findings (for the Opus pass)

- **`fn_800246D4(cmp, base, scratch, size, count)`** is a shared in-place
  sort/comparator helper (already used this way by `scene_effects.c`).
  `wallBallCalculateNewWalls` calls it to sort `wallIndexTracker[7]` (1-byte
  elements) using `fn_3_1149B8` as comparator.
- **`fn_3_1149B8`** is *not* a normal call target -- it's only referenced by
  address (`&LAB_80753a4c` in Ghidra's view), passed to `fn_800246D4`. Given
  signature `int(u8*, u8*)`. Declared/defined that way; header updated.
- **`fn_8004C108`/`callSfx`/`setCharacterAnimations`/`RandomInt_Game_Range`**
  reused from barrel_batter.c's/bobomb_derby.c's exact established
  signatures (same minigame-effects helpers).
- **AI throw-type values, confirmed from `wallBallMultiplayer_AIControl`'s
  raw asm (not from Ghidra's decompile, which only names them without
  giving numbers):** `perfect=0, overcharge=1, charge=2, curveBall=3` for
  `ai_wbThrowType_bbVertAngle`. I had drafted `wallBallAIPitches` with a
  *wrong* guessed numbering first (copying Ghidra's case-label order
  blindly); fixing it against the real jump table raised
  `wallBallMultiplayer_AIControl` 25.08% -> 67.29% in one pass. **If you
  see any other file using guessed enum numbers sourced only from Ghidra's
  pseudo-enum names (not raw asm immediates), re-check them.**
- **`wallBallMultiplayer_AIControl`'s `wallBallAISwitchVar`** is a real
  10-value (0-9) jump table (`jumptable_3_data_22558`, this unit's entire
  owned `.data`, 10 `.rel` entries dumped straight from the asm -- see the
  `.c` file's switch, which should be exactly case-complete now). State
  values confirmed from the jump table itself: 0=choose pitch, 1=wait out
  countdown, 2/3=perfect press/hold, 4/5=overcharge press/hold,
  6/7=charge press/hold, 8=curveBall press, 9=idle.
- **`fn_3_113D20` needed `#pragma dont_inline`** -- its only call site
  (`fn_3_114A2C`) is in this same file, and `-inline auto` folded it in
  (frame grew 0x10 -> 0x40, byte-for-byte including the whole callee body).
  Target keeps it a real `bl`. Bracketing the definition with
  `#pragma dont_inline on` / `reset` fixed it immediately (100%). Confirms
  the "small matched functions auto-inline" lever cuts both ways -- a
  *single*-call-site function in the *same file* is exactly the case where
  it bites.
- **`wallBallRotatePitchers`'s manual "1/sqrt + 2 Newton iterations +
  NaN/Inf classification" block is just `dolsqrtf2()`'s own body showing
  through** (same double-precision Newton-Raphson shape documented for
  `dolsqrtf2` elsewhere in the project). Drafted as a plain
  `dolsqrtf2(dx*dx+dz*dz)` call instead of hand-translating the
  classification logic -- **not yet confirmed this scores correctly**,
  flagging for Opus to verify match% on that specific block.

## Open questions / unverified data tables (first-pass draft, not raw-asm-checked)

I ran out of session budget to hand-decode every remaining function's raw
PPC for its constant tables the way I did for `fn_3_113950`/`fn_3_113D20`/
`fn_3_1149B8`/`wallBallCalculateNewWalls`'s sort call. For
`wallBallAIPitches`, `wallBallCalc_WallsBroken`, `wallBallSomething2`,
`wallBallRotatePitchers`, and the rest of `wallBallCalculateNewWalls`, the
following externs are **translated from Ghidra's decompile only** (byte
offsets/shapes are my best guess, not raw-asm-verified):

- `wallBallConstants1_807d2c74` (`wallBreakOffset`, `pitchVeloMult`,
  `rotatePitchersMaxFrames`)
- `wallBallConstants2_807d2c88` (`randomBounds[4][2]`,
  `perfectOverchargeProb[4]`) -- also reused (probably wrongly -- needs a
  real check) for the "const_0_1"/"const_0_3" wobble-reset values in
  `wallBallSomething2`
- `wallBallAIPitches_oddsTable[]` -- Ghidra itself couldn't resolve this
  relocation (showed as raw pointer arithmetic, `aIStrength*7 +
  -0x7f82d36c + cVar5`); I have no real address for it at all.
- `SHORT_ARRAY_807d2c5c/62`, `FLOAT_ARRAY_ARRAY_807d2be0/807d2b08`,
  `FLOAT_807d2b74/78/7c/bc8/b00/04`, `fieldingStartingCoords_regular[6]`
  (this last one has a real symbols.txt address, `.data:0x450C size:0x48`,
  just no header entry yet -- the others don't even have that).

All of these sit **below this unit's own `.data`/`.rodata` start**, so they
belong to a neighbouring minigame TU, most likely bobomb_derby.c or
barrel_batter.c per the task's own hint that the three files are close
relatives -- worth checking those files' still-`pending` functions for
overlapping unidentified tables before inventing fresh names for these.

`lbl_3_data_21634/2167C/219B8/21674/21688` **are** raw-asm-verified (byte
offsets confirmed from `fn_3_113950`/`fn_3_113D20`/`fn_3_113EC0`'s actual
disassembly), just not yet given real names/cross-referenced to any other
file.

## Hypothesis log

**fn_3_114A2C** (100%)
  baseline: 0% (stub)
  [S1] Drafted as `switch` over `wallBallGameState` -> 0%, stack frame
       -0x40 vs target's -0x10; MWCC had inlined `fn_3_113D20` (its only
       call site) into this function wholesale (same byte size difference
       as the callee's own body). -> kept (switch itself wasn't the
       problem)
  [S1] Rewrote the switch as if/else-if (matching_notes' "switch vs
       if-chain lower differently" lever) -> no change, confirmed inlining
       was the real cause, not the switch shape.
  [S1] Added `#pragma dont_inline on/reset` around `fn_3_113D20`'s
       definition -> 100%. (kept)

**fn_3_113950** (100%)
  baseline: 0% (stub)
  [S1] Drafted directly from raw asm (coin gravity/bounce/despawn loop,
       100 iterations) using the newly-fixed `[100]` coin arrays -> 100%
       on the first attempt. (kept)

**fn_3_11391C** (100%)
  baseline: 0% (stub)
  [S1] `memset(&g_Minigame._1D7C, 0, 0x78);` (bulk-clears `_1D7C` through
       just before `_1DF4`, matching the asm's single memset exactly) ->
       100% on the first attempt. (kept)

**fn_3_1149B8** (pending, 91.69%)
  baseline: 0% (stub)
  [S1] Drafted as the sort comparator `fn_800246D4` calls (confirmed by
       address match: `&LAB_80753a4c` == this function's own address) ->
       91.69%. next: likely register-allocation only; logic looks clean
       against the raw asm I traced instruction-by-instruction.

**wallBallMultiplayer_AIControl** (pending, 67.29%)
  baseline: 0% (stub)
  [S1] First draft copied Ghidra's enum case ORDER for
       `ai_wbThrowType_bbVertAngle` literally (treated case order as value
       order: perfect=2,curveBall=1,overcharge=3,charge=0) -> ~25%.
  [S1] Re-derived the real values from this function's own jump-table
       dispatch and the state-transition cmpwi chain in case 1 (traced by
       hand: type==0->state2(perfect), type==1->state4(overcharge),
       type==2->state6(charge), else->state8(curveBall)) -> corrected to
       perfect=0,overcharge=1,charge=2,curveBall=3, also fixed
       `wallBallAIPitches` to match -> 67.29%. (kept)
  next: logic/values now believed correct; remaining gap is likely
  register allocation or the exact if/else branch topology inside case 1
  (I used a flat if/else-if chain; the asm's actual branch tree is a bit
  different -- bge/beq ordering -- worth comparing directly).

**wallBallDropInNewWalls** (pending, 67.16%)
  baseline: 0% (stub)
  [S1] Drafted directly from Ghidra decompile with real field names
       substituted (`targetY`/`targetZ`/`wallState` etc.) -> 67.16%.
       next: not grinded further this session; likely clean logic, check
       register allocation first per the First-look checklist.

**fn_3_113D20** (pending, 58.53%)
  baseline: 0% (stub)
  [S1] Hand-decoded fully from raw asm (not Ghidra -- Ghidra's decompile
       for this one was unusable, lots of `CONCAT44`/bias-constant noise).
       Written as a plain loop with `fabsf`/`cos` and 0.0f literals (per
       "don't use extern rodata labels for target-local floats" lever) ->
       58.53%. next: logic is asm-verified instruction-by-instruction, so
       the gap is almost certainly register allocation / branch-shape
       (my `if (oldAngle < newAngle) {...} else {...}` collapses two
       bge/bgt-selected 4-instruction blocks that may need to stay in the
       asm's own if/else shape rather than my boolean-expression
       simplification -- worth comparing branch-by-branch).

**fn_3_113EC0** (pending, 54.95%)
  baseline: 0% (stub)
  [S1] Hand-decoded from raw asm (ball-velocity decay + set
       `ballStoppedBreakingWallsInd`, same tail as `wallBallSomething2`'s
       low-power branch) -> 54.95%. next: likely register-allocation only;
       logic directly asm-traced.

**wallBallAIPitches** (pending, 53.21%)
  baseline: 0% (stub)
  [S1] Drafted from Ghidra decompile, fixed the throw-type values to match
       `wallBallMultiplayer_AIControl`'s real numbering (see that entry)
       -> 53.21%. next: `wallBallConstants2_807d2c88`/`_oddsTable` shapes
       are unverified (see Open questions) -- likely a real contributor to
       the remaining gap, not just register allocation.

**wallBallCalc_WallsBroken** (pending, 48.38%)
  baseline: 0% (stub)
  [S1] Drafted from Ghidra decompile with real field names
       (`g_Pitcher.ChargePitchType`/`pitchChargeUp`, `wallPower`,
       `coinGenerationCategory`) -> 48.38%. next: the "which byte is
       startingCharge/chargedCaptainStar" threshold (I guessed `> 1`) is
       unverified against raw asm -- check that comparison first.

**wallBallRotatePitchers** (pending, 34.35%)
  baseline: 0% (stub)
  [S1] Drafted from Ghidra decompile; replaced the inline
       Newton-Raphson/NaN-classification block with a plain `dolsqrtf2()`
       call (see Key findings) -> 34.35%. next: verify the dolsqrtf2
       substitution actually reproduces that block byte-for-byte (it's a
       big chunk of the function); if not, may need the literal inline
       form instead. `wallBallConstants1_807d2c74.rotatePitchersMaxFrames`
       shape unverified.

**wallBallCalculateNewWalls** (pending, 31.97%)
  baseline: 0% (stub)
  [S1] Drafted from Ghidra decompile for the bulk of the body, but the
       difficulty-level setup, the `fn_800246D4` sort call, and the
       post-sort `setupOrderIndex` renumbering loop were hand-verified
       against raw asm (see Key findings) -> 31.97%. next: the
       "thin out remaining walls" loop (shifting `candidates[]` after a
       removal) is a straight translation of Ghidra's memmove-shaped
       pseudocode and almost certainly doesn't match the target's actual
       loop shape -- this is the single biggest LOGIC-bucket item left in
       the file and the best candidate for the Opus pass to start on.
       `FLOAT_ARRAY_ARRAY_807d2b08`/`807d2be0` shapes unverified.

**wallBallSomething2** (pending, 20.95%)
  baseline: 0% (stub)
  [S1] Drafted from Ghidra decompile (wall-break detection loop, coin
       spawn loop) -> 20.95%, the lowest of the file. next: the backward
       scan for the "wall closest to the ball that's state==3" (I wrote
       `for (i = 6; i >= 0; i--)` from Ghidra's `while` loop, but the raw
       asm wasn't checked) is the most likely structural mismatch -- check
       it against raw asm before anything else; also depends on the
       unverified `wallBallConstants1/2` tables.

## Names proposed (not applied -- below the match-sonnet confidence bar; propose to Opus/label-symbols once functions are matched)

- `fn_3_1149B8` -> something like `wallBallWallPrioritySort` or
  `wallBallWallCompare` once matched (medium confidence: role is clear --
  sort comparator for `wallIndexTracker` -- but no in-game/official name
  evidence).
- `fn_3_113EC0` -> maybe `wallBallBounceBallOffWall` or similar (medium
  confidence, same velocity-decay tail as `wallBallSomething2`'s
  low-power branch, so it's clearly a "ball bounces back after breaking
  the last wall" helper, but I don't know who calls it -- not called from
  anywhere in this unit, so possibly called from `pitching_machine.c` or
  the gap region between this unit and it, worth an xref check).
- `fn_3_1149B8`'s struct field `setupOrderIndex` and `WallBallWallStruct`
  itself are my working names, not official -- flag as inferred/working
  names, not confirmed.

## Files touched this session

- `include/game/UnknownHomes_Game.h` -- `WallBallWallStruct` (was
  `MaybeWallBallStruct`), `wallBallWalls[7]` (was single `wallBallStruct`
  + ~0x100 bytes of unrelated-looking padding), `wallBall_coinCoordinates`/
  `wallBall_coinVelocity`/`wallBall_coinsVisibleFrameCounter`/
  `wallBall_coinsVisibleInd` retyped to their real `[100]` array sizes,
  `wallBallWaitingLocations` retyped `[4][2]`.
- `src/game/fielding/fielder.c` -- `updateFielderPositionBasedOnBallState`:
  fixed to use plain `[i]` array indexing now that the coin-coordinate
  fields are real arrays, and fixed a latent bug where the visible-ind
  check wasn't indexed by `i` at all. 97.66% -> 100%.
- `src/game/minigame/wall_ball.c` -- all 13 functions drafted (was all
  `return;` stubs).
- `include/game/minigame/wall_ball.h` -- prototypes updated for
  `wallBallRotatePitchers(int)` and `fn_3_1149B8(u8*, u8*)` (both were
  `(void)`, wrong).

Dependents rebuilt and reconfirmed unchanged: barrel_batter (.text
99.5476%), bobomb_derby (99.8358%), kinoko (99.047%), toy_field_offscreen
(100%), minigame_fielder_anim (100%), batter_ai (99.7318%/.rodata
84.7458%) -- all identical before/after. Full project `ninja` build is
clean, sha1 `4 files OK`, REPORT/PROGRESS generate without error.

## Session 2 (Opus) log

Data reality check: every "wallBallConstants*/SHORT_ARRAY_*/FLOAT_*" extern
from S1 was a Ghidra RAM-address guess. Real labels (all in the unowned
auto_04_00021268_data block, so externs are correct; mapping data off ->
Ghidra RAM is +0x807B1600): lbl_3_data_21500 f32[4][2] (pitcher waiting
spots), 21520 VecXYZ[2][7] (wall start offsets: [0]=state2 (z), [1]=state1 (y)),
215C8 VecXYZ[2] (per-frame drop velocity for state2/state1), 215E0 VecXYZ[7]
(wall target position by setupOrderIndex), 21634 f32[5] (coin yvel, coin
xz speed, gravity, bounce, damping), wallBall_nCoinsToGenerate int[3],
21654 s16[12] (0..2 = 30,123,150 charge min/max/perfect; 3 = 10 min power;
4..6 wall power by category; 7..9 points by category; 10,11 = 100,50),
21674 f32[2] (ball vel mult, wall break z offset), 2167C s16[6]
(rotate frames, ..., [4]=coin despawn frames), 21688 f32[3] (wobble
init vel, init amplitude, decay), 21694 s8[4][7] (AI odds), 216B0
s8[4][2] (AI random bounds), 216B8 s8[4] (perfect->overcharge prob).

fn_3_113EC0 -> 100%: `z = -z; x*=m; y*=m; z*=m;` using lbl_3_data_21674[0].
fn_3_1149B8 -> 100%: two flat ifs `(A==3 && B!=3) return -1; (A!=3 && B==3) return 1;`.
wallBallSomething2 20.95 -> 99.81 (rest = rodata label names only):
  [1] forward loop 0..6 (not backward), real labels, setupOrderIndex-indexed
      coin spawn, rand()%180  -> 60.1
  [2] if (power <= 0) {break} else {wobble} order -> 86.8
  [3] outer loop + coin arrays via direct g_Minigame (CSE'd base), block-local
      `MiniGameStruct* mg = &g_Minigame` for the break body, call fn_3_113EC0()
      (inlined) -> 99.71
  [4] threshold expression inline in condition (no local) -> 99.81
  (rejected: separate coin index var 95.6; s16 loop var 93.2)
