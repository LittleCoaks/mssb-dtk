# Checkpoint: src/game/minigame/bobomb_derby.c (unit game/game/minigame/bobomb_derby)

All functions started as bare stubs; implemented from scratch.

## Status (Opus pass 2026-10-01; objdiff-cli strict measure)

| function                        | size  | status  | pct    |
|---------------------------------|-------|---------|--------|
| bobOmbDerbyBatterAI             | 0x3D0 | matched | 100%   |
| fn_3_110A04                     | 0x34  | matched | 100%   |
| fn_3_110A38                     | 0x9C  | matched | 100%   |
| BODScoring                      | 0x564 | exhausted | 99.87% |
| unused_BODRelated               | 0x198 | matched | 100%   |
| fn_3_1111D0                     | 0x80  | matched | 100%   |
| fn_3_111250                     | 0x64  | matched | 100%   |
| bobOmbDerbyCalculatePoints      | 0x484 | matched | 100%   |
| unusedBODFunction               | 0x17C | matched | 100%   |
| bOD_bB_Pitcher_waitingForPitch  | 0x1D4 | matched | 100%   |
| fn_3_111A88                     | 0x3C  | matched | 100%   |
| fn_3_111AC4                     | 0x198 | matched | 100%   |
| fn_3_111C5C                     | 0x324 | exhausted | 99.90% |
| fn_3_111F80                     | 0xF0  | matched | 100%   |
| fn_3_112070                     | 0x70  | matched | 100%   |
| fn_3_1120E0                     | 0x48  | matched | 100%   |
| fn_3_112128                     | 0x7C  | matched | 100%   |
| fn_3_1121A4                     | 0x8C  | matched | 100%   |
| bobOmbDerbyPitchTransition      | 0x220 | matched | 100%   |
| fn_3_112450                     | 0x108 | exhausted | 99.55% |
| fn_3_112558                     | 0x78  | matched | 100%   |
| fn_3_1125D0                     | 0x40  | matched | 100%   |
| bOD_LoadGame                    | 0x2D8 | pending | 98.18% (blocked on s8 retype, see log) |
| fn_3_1128E8                     | 0x4   | matched | 100%   |
| fn_3_1128EC                     | 0x2EC | matched | 100%   |
| bobOmbDerbySimulation           | 0x7C0 | exhausted | 99.90% (only the inlined fn_3_111C5C + fn_3_112450 residuals remain) |

Sections now: .text 99.84, .rodata 100, .data 100, .bss 100.
  .bss: `static u8 lbl_3_bss_B699; static u8 lbl_3_bss_B698;` (MWCC lays .bss out in reverse declaration
  order; B698 is unreferenced but occupies the unit's first byte) + symbols.txt lbl_3_bss_B699 size 0x1F ->
  0x1 (it is a byte toggle; the 0x1E tail is unreferenced/unowned). sha1 check still `4 files OK`.

## Sections (baseline -> current, this session's end)
.text 0.8950086% -> 88.56489% (every stub drafted; remaining gap is register-alloc/const-pool, see Open questions)
.rodata 67.796616% -> 76.54321% (whole-section); `[.rodata-0]` symbol 77.14% -> 78.05%
.data 0.0% -> 0.0% at the whole-section level, but `[.data-0]` (the `bobOmbDerbySimulation` jumptable, the
  only `.data` this unit owns) is now 61.11% byte-agreement -- it only references addresses *inside* that
  function, so it will climb on its own as that function's remaining register-alloc diffs close; no separate
  `.data`-layout fix is needed.
.bss 0.0% -> 0.0% (unreferenced by anything in this unit; nothing to fix)

## Open questions (cross-function, for the Opus pass)

- **File-wide rodata float/double constant-pool reordering.** Every function that uses a float/double literal
  (`unused_BODRelated`, `fn_3_1111D0`, `fn_3_110A38`, `bobOmbDerbyCalculatePoints`, `fn_3_1128EC`,
  `bobOmbDerbyBatterAI`) shows its *values* correct but its rodata relocation as an anonymous `@NNN` pool
  entry instead of the named `lbl_3_rodata_32xx` symbol. This was already flagged in the pre-session
  checkpoint as "expected to resolve once the rest of the file's stubs are implemented" -- that is now true
  (0 stubs left) and the issue is UNCHANGED, still present on every affected function. Worth a dedicated,
  focused pass checking whether function *definition order* in the `.c` file (not just "is it implemented")
  affects MWCC's literal-pool layout, the same lever documented for `barrel_batter.c`
  (`#define SQRT2_LINKAGE static` + reverse-address-order function definitions, see that file's checkpoint
  `[O4]`). Not yet tried here.
- **Two confirmed struct-field width mismatches**, each independently confirmed by 2 different functions
  reading/writing them at a wider size than declared: `g_Minigame.minigameAICountDownTillAction` (header:
  `s16` at 0x1DD0, but `fn_3_111C5C`/`bobOmbDerbySimulation`'s AT_BAT case both access it via a single BYTE)
  and `g_Minigame.ai_wbThrowType_bbVertAngle` (header: `u8` at 0x1DCE, but `fn_3_111C5C` and
  `bobOmbDerbyBatterAI` both access it via 2 bytes). Both are worked around with raw `*(u8*)&field` /
  `*(s16*)&field` casts rather than widening the header, because widening `ai_wbThrowType_bbVertAngle` would
  collide with the very next field (`wallBallAISwitchVar` at 0x1DCF) -- these two offsets are almost
  certainly reused differently per-minigame (wall-ball vs bob-omb derby), and resolving it properly would mean
  checking every OTHER minigame that touches this same byte range, out of scope for this file alone.
- **`bobOmbDerbySimulation` duplicates 9 other functions' bodies inline** (see its hypothesis-log entry for
  the full list and evidence) rather than calling them. This means `fn_3_111C5C`'s/`unusedBODFunction`'s known
  "isAIControlled[] reset loop fully unrolls instead of staying a real loop" register-allocation issue exists
  as **two independent copies** of the same source text (the standalone function and the switch-inlined
  copy) -- a fix discovered in one will very likely need to be re-applied to the other, since they are
  separate compilations of textually-identical code in different contexts.
- **Struct corrections made this session** (all additive/reclassifying, zero offset-shift, confirmed
  zero-regression on every dependent unit rebuilt): `MiniGameControlStruct.aIStrength` `u8[4]`->`u8[6]`;
  `MiniGameStruct.minigamePoints_current_Latest` `s32[4]`->`s16[4][2]`; `MiniGameStruct.bODHistory[4][10]`
  replacing the `_1AA0[3]`/`_1AA3..1AA9`/`pad18[30]` placeholders. Dependents touched and reverified:
  `batter_ai.c`, `fielder.c` (both just a `._14`/`._15` -> `.aIStrength[4]`/`[5]` rename, zero score change).

## Hypothesis log

bobOmbDerbySimulation (formerly stub) -- the file's top-level per-frame dispatcher: `switch (g_GameLogic.gameStatus)`
  via `jumptable_3_data_224E8` (27 entries, `g_GameLogic.gameStatus` bounds-checked `<= 0x1A`, `bgt` ->
  shared epilogue for anything else). KEY FINDING: every non-trivial case is a byte-for-byte DUPLICATE of an
  already-matched standalone function's body in this same file -- confirmed by grepping this function's own
  asm for `bl` instructions to those functions and finding NONE (the logic is inlined at the source level, not
  called) for every case except `GAME_STATUS_LOAD_GAME` (`bl bOD_LoadGame`) and `GAME_STATUS_DEFAULT`
  (`bl bobOmbDerbyPitchTransition`) -- both large enough, and presumably called from elsewhere too, to stay
  as real calls instead of being auto-inlined. Mapping (via the jumptable's 27 relocations against this file's
  label addresses): `GAME_STATUS_AT_BAT`=`fn_3_111C5C`'s full body, `GAME_STATUS_LIVE_BALL`=`unusedBODFunction`'s
  full body, `GAME_STATUS_INNING_TRANSITION`=`fn_3_111F80`'s body, `GAME_STATUS_TRANSITION_TO_MINIGAME_START`=
  `fn_3_112558`'s body, `GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY`=`fn_3_112450`'s body,
  `GAME_STATUS_TRANSITION`=`fn_3_112128`'s body, `GAME_STATUS_TRANSITION_MINIGAME_POSTGAME`=`fn_3_112070`'s
  body, `GAME_STATUS_MINIGAME_NEW_ROUND`=`fn_3_1120E0`'s body, `GAME_STATUS_TRANSITION_MINIGAME_TO_BATTING`=
  `fn_3_1125D0`'s body; everything else (GAME_START_MOVIE, END_OF_GAME, PAUSED, MVP_END_GAME, HOMERUN_*,
  BATTER_CELEBRATION, STAR_CHANCE_VS, CHAMPIONSHIP, and the unnamed 0xA/0xC/0x10/0x11/0x12/0x18 values) jumps
  straight to the shared epilogue with no body. This STRONGLY implies these "helper" functions
  (fn_3_111C5C/unusedBODFunction/fn_3_111F80/fn_3_112558/fn_3_112450/fn_3_112128/fn_3_112070/fn_3_1120E0/
  fn_3_1125D0) exist as separate symbols ONLY because something else in the game (a per-minigame
  function-pointer/vtable callback, outside this file/module) ALSO calls them directly -- this switch is a
  second, independent call path the original developer wrote by hand rather than factoring out.
  baseline: 0.20% (bare stub)
  [1] direct translation: copied each matched function's CURRENT verified source verbatim into its case,
      cases written in increasing `GAME_STATUS` numeric order -> 47.43% (kept as starting point; far lower
      than expected for "just assembled already-matched code", signalling a structural issue, not a logic one)
  [2] FILE-WIDE LESSON APPLIED (same one logged in `barrel_batter.c`'s checkpoint): MWCC jump-table switches
      emit case bodies in SOURCE order, which is NOT the same as case-value numeric order. Recovered the
      target's real physical body order from the jumptable's own relocation addresses (reading each
      `.L_xxxxxxxx` label's address): `LOAD_GAME(4), TRANSITION_MINIGAME_TO_BATTING(26),
      TRANSITION_TO_MINIGAME_START(6), TRANSITION_PREPARE_NEXT_PLAY(7), DEFAULT(0), AT_BAT(1), LIVE_BALL(2),
      TRANSITION(8), MINIGAME_NEW_ROUND(25), INNING_TRANSITION(3), TRANSITION_MINIGAME_POSTGAME(15)` -- NOT
      0,1,2,3,4,6,7,8,15,25,26 as I'd originally assumed from the case-value order. Reordered the switch's
      case blocks (bodies unchanged) to match -> 90.60% (kept, huge jump from a pure reordering with zero
      logic changes -- confirms the lesson generalizes beyond barrel_batter.c).
  Remaining diff at 90.60%: the `AT_BAT` case's two `isAIControlled[i]=0` reset loops fully unroll in our
  build but stay real loops in target -- the SAME unrolling divergence already logged for the standalone
  `fn_3_111C5C` (this is literally the same source text, so the same codegen quirk reproduces here), plus
  ordinary register-letter noise (r24/r25/r26/r28/r29 swaps) cascading from it. `.data` (the jumptable itself)
  is still 0% at the WHOLE-SECTION level only because its 27 entries are absolute addresses into this
  not-yet-100%-matched function -- a `[.data-0]` symbol-level breakdown already shows 61% byte agreement and
  should climb to 100% automatically once `.text` does, no separate data-layout work needed.
  Open question for Opus: given 8 other functions in this file appear to be dead code from this switch's
  perspective (called only via this duplicated-inline path, not via `bl`), consider whether fixing the
  `isAIControlled` unroll divergence in `fn_3_111C5C` alone (the standalone function) would need to be
  separately re-applied here too, since they are now two independent copies of the same source text.

BODScoring (formerly stub) -- fires once per hit, logs the throw into a per-roster history, launches a
  fireworks burst, then (second call onward while a flag is clear) periodically re-launches fireworks on a
  random timer. The hardest function in the file to reverse structurally because Ghidra's own decompile is
  actively misleading here (signed-char pointer-arithmetic overflow in its model produced nonsense constants
  like `-0x7f76994d` and wrong array dimensions) -- trusted the raw asm throughout instead of Ghidra's text.
  MAJOR STRUCT CORRECTION (evidence-backed, not guessed): `MiniGameStruct`'s `_1AA0[3]`/`_1AA3`.._1AA9` (7
  individual bytes)/`pad18[30]` placeholders (0x1AA0-0x1AC7, 40 bytes total) replaced with a single
  `u8 bODHistory[4][10]`. Evidence: the opening loop computes addresses as `&g_Minigame + rosterID*10 + k +
  0x1AA0` for k=1..9, i.e. a real `[rosterID][k]` 2D index with row stride 10 -- 4 rosters * 10 bytes = 40
  bytes, exactly the span those three placeholder declarations covered combined, so this is a pure
  reclassification with zero offset-shift risk (confirmed no other file referenced `_1AA0`/`pad18` before this
  edit). The loop itself is a 9-element right-shift (`row[9]=row[8]; ...; row[1]=row[0];`) that then writes
  `row[0] = bODAngleIndexBasedOnHitPower` -- a "most recent N throws" ring history.
  New externs: `calculateAngleFromCoordinates(f32 x, f32 z)` returning `s16` (an angle-from-2-coords helper,
  not implemented elsewhere in this file -- takes its 2 args directly in f1/f2, no third arg despite Ghidra
  showing doubles; confirmed by the second call site reusing live FPR values with no additional float loads).
  `lbl_3_data_213E0[4]` merges two dtk-split one/three-byte symbols (213E0, 213E1) into the 4 bytes
  `{25,55,15,30}` actually read (same "common-data gap-inflation" pattern as every other merged-array fix in
  this session) -- confirmed via `auto_04_00021268_data.s`. `getComponentsFromSAng`/`fn_80052768_getCamera`/
  `maybeFireworks` were all already declared and used verbatim.
  The position vector passed to `maybeFireworks` is NOT the per-roster history (despite Ghidra's pointer
  confusion suggesting otherwise) -- it is a plain stack `Vec` built from `(g_Ball.AtBat_Contact_BallPos.x,
  -g_Ball.AtBat_Contact_BallPos.y, g_Ball.AtBat_Contact_BallPos.z)` in the first branch, and from two
  `getComponentsFromSAng` angle-to-vector calls (yaw -> x/z, pitch -> a y/x ratio) scaled by
  `lbl_3_data_21438._0C` in the second (periodic-refire) branch.
  baseline: 0.29% (bare stub)
  [1] direct translation from the raw asm (not Ghidra's text) for both branches -> 84.67% (kept, no further
      iteration attempted -- deep in register/stack-layout territory)
  [2] one comparison-canonicalization fix (`bODCharacterHRStreakTracker[rosterID][0] < 2` -> `<= 1`, same
      family as every other `<N`/`<=N-1` fix this session) -> 84.68% (kept, best so far)
  Remaining diff at 84.68%: target allocates the stack `Vec pos` at a different offset than ours (0x1c vs
  0xc), shifting a long tail of STRUCT_LAYOUT-categorized stack-offset noise through the rest of the function;
  logic and data-table identity are correct. Register/stack-layout grinding, left for Opus. Lifted
  `unusedBODFunction` 94.63% -> 95.68% for free.

bobOmbDerbyCalculatePoints (formerly stub) -- the HR-scoring and round-transition driver, called by
  `unusedBODFunction` and `fn_3_111C5C`. Reused THREE already-proven blocks verbatim rather than re-deriving
  them: the HR-points formula is byte-for-byte `unused_BODRelated`'s formula (same `lbl_3_data_213EC[7]`/[8]
  king-bomb/combo-bonus reads, same `starMissionsMinigamesSpecialAction(0, points, bOD_KingBombInd)` guard);
  the countdown/transition tail (`bODControllerInputAllowedInd`/`bODRelated` outer guard, then the
  `pointsTargetReachedInd && (multiPlayerInd==0 || ...) && _1A37==0 && CountdownUntilFade==0x43` compound sndFX
  condition, `==7` changeScene, `<=0` transition) is fn_3_111AC4's proven tail with one new outer guard added;
  the final `fn_8003A540(0); if(pointsTargetReachedInd==1) TRANSITION else DEFAULT;` is fn_3_111250's tail
  verbatim. New enum usage: `DEAD_BALL_REASON_NONE`/`DEAD_BALL_REASON_HOME_RUN` (already defined in
  `mssbTypes.h`, just not previously used against `g_Ball.deadBallReason` in this file).
  `lbl_3_data_21448[1]`/`[2]`/`[9]` are 3 more entries of the already-declared `s16[10]` timing-constant table
  (index 0 used by fn_3_111AC4, now 1/2/9 used here).
  baseline: 0.35% (bare stub)
  [1] direct translation reusing the 3 proven blocks above -> 99.14% (kept)
  [2] two comparison-canonicalization fixes, same pattern as `bOD_LoadGame`/`fn_3_1128EC`: `soloMinigameDifficulty
      < MINIGAME_DIFFICULTY_SOLO_NON_CHALLENGE` -> `<= 2` (target compiles the negation as `cmplwi r0,2;bgt`,
      not `cmplwi r0,3;bge`), and swapped `bODRoundStartingNumPitches <= miniGameTurnCounter` to
      `miniGameTurnCounter >= bODRoundStartingNumPitches` (matches target's read order: turn counter loaded
      before round-starting-pitches) -> 99.46% (kept, best so far)
  Remaining diff at 99.46%: purely the file-wide `doubleConst` rodata const-pool address (same `@473`-style
  anonymous-vs-`lbl_3_rodata_3260` issue as every other function here) plus a handful of register-letter/
  operand-order differences in the early `framesOnGroundUntilPickedUp`/`deadBallReason` checks. Left for Opus.
  Lifted `unusedBODFunction` 93.58% -> 94.63% and `fn_3_111C5C` 82.19% -> 83.40% for free (their calls to this
  function stop inlining away as no-ops).

bobOmbDerbyBatterAI (formerly stub) -- the AI opponent's swing-timing/charge-power decision function, by far
  the most complex in the file. New data-table externs added (byte-dumped shapes, not guessed): `lbl_3_data_21488[8][3]`
  (base weight per AI-difficulty-row, 3 pitch-charge-type columns), `lbl_3_data_214B8/214C4[4][3]` (streak-count
  multiplier, two variants used by the charge-type and pitch-type weight loops respectively), `lbl_3_data_214D0/214DC[4][3]`
  (king-bomb bonus, two variants), `lbl_3_data_214E8/214F4[4][3]` (the `g_Minigame._1DF6[0]`-flag bonus, two
  variants), `lbl_3_data_214A0[4][6]` (per-AI-difficulty swing-timing-offset min/max pairs, 3 pitch types x 2
  bounds). Also `bobOmbDerbyBatterAI2(int *weights, int count)` -- an unimplemented-elsewhere weighted-random-
  index helper (same shape as `RandomIndexFromWeights`, but a distinct symbol, so left as its own extern; not
  this file's function to implement).
  IMPORTANT FINDING: the asm's second weighted-sum loop reads `lbl_3_data_21488[aiDifficulty+1][i]`, i.e. it
  is the SAME 21488 array as the first loop, just at the next row (confirmed via `r11` -- the register walking
  this table -- never getting reset between the two loops, it just keeps incrementing). Ghidra's own decompile
  shows this as a conceptually different `BYTE_ARRAY_ARRAY_ARRAY_807d2a88[1]` array, but that is Ghidra
  mis-inferring the stride; the real behaviour is "index one row past where the first loop's weight came
  from," reproduced here as `lbl_3_data_21488[aiDifficulty + 1][i]` against the SAME 8-row array -- no need
  for a second/merged symbol.
  SECOND WIDTH-MISMATCH CONFIRMATION (see fn_3_111C5C's entry below for the first): this function ALSO writes
  `g_Minigame.ai_wbThrowType_bbVertAngle` (header: u8 at 0x1DCE) via a 2-byte `sth`, and reads it back via
  `lha`, independently confirming it needs raw `*(s16*)&...` casts rather than being genuinely 1 byte --
  two independent functions now agree on this; still not widening the header (would collide with the very
  next field, `wallBallAISwitchVar` at 0x1DCF -- see Open questions).
  The tail's charge-power/swing-frame conversion from `g_Minigame.minigamePitchSpeedAdjustment` is -- byte for
  byte, down to the same 4 rodata float constants (324C/3250/3254/3258) -- `fn_3_110A38`'s body INLINED (no
  `bl` instruction present), not called; written here as a plain call to `fn_3_110A38()` and left to
  `-inline auto` to flatten automatically (consistent with how this file already treats small helpers).
  baseline: 0.41% (bare stub)
  [1] direct translation using the tables/helper above, `switch`-free straight-line charge-type dispatch
      (if/else-if matching the asm's compare order exactly: `==1`, `<1||>2`, else `==2`), re-reading
      `bODCharacterHRStreakTracker[rosterID][0]` into a fresh local between the two weight loops (matches
      target's redundant reload rather than reusing one cached value) -> 58.43% (kept, no further iteration
      attempted -- function is far past the "cheap win" stage, left for Opus)
  Remaining diff at 58.43%: a long tail of SYMBOL_NAME/STRUCT_LAYOUT/REGISTER_ALLOC entries from a different
  register-allocation strategy around the lookup-table address computations (target computes `g_hitShorts`'s
  base and the `framesUntilChargeIsEnabled` field very early and keeps it live in a saved register across both
  loops; ours re-derives it later) and a CONST_POOL entry for the shared rodata float pool (same whole-TU
  pooling issue as every other function in this file). Logic/data-table identity is correct; this is squarely
  register-allocation-strategy grinding.

fn_3_111C5C (formerly stub) -- this IS the file's main per-frame "AtBat" driver, the bob-omb-derby analogue of
  barrel_batter.c's `bB_AtBat` the task hint pointed at. Confirmed the same "g_Minigame base address kept live
  in a saved register across two calls" pattern: r26/r29 (&g_Minigame) stays resident across the whole
  function including both `atBat_Pitcher()`/`atBat_batter()` calls, exactly like bB_AtBat's r25. Its tail
  (`turnOverStatus != 0` branch) is **byte-for-byte the same compound condition already proven correct and
  100%-matched in `fn_3_111AC4`** (pointsTargetReachedInd / multiPlayerInd / turnNumberWithinRound+1>=
  miniGameNumberOfParticipants / Inning>=inningLimit / _1A37==0 / CountdownUntilFade==0x43 sndFXStartEx,
  ==7 changeScene, <=0 SetGameStatus(TRANSITION)) -- copied that proven structure verbatim rather than
  re-deriving it, and the `turnOverStatus==0` branch's NO_CONTACT tail (reset streak + bobOmbDerbyPitching)
  also matches fn_3_111AC4's corresponding block exactly.
  New struct evidence used: `isAIControlled[4]`/`_1D7C[4]` (`InputStruct`, size 0x10) at 0x1DBC/0x1D7C were
  ALREADY in the header from a previous session and line up exactly with this function's per-character AI
  loop (`memset(&g_Minigame._1D7C[slot], 0, sizeof(InputStruct))`, `isAIControlled[slot]=1`).
  `InputStruct.buttonInput |= INPUT_BUTTON_A` (0x100 = `PAD_BUTTON_A`, confirmed via `Dolphin/pad.h`) is the
  AI "press the swing button" idiom.
  Two WIDTH MISMATCHES flagged rather than silently resolved: `minigameAICountDownTillAction` (header: s16 at
  0x1DD0) is read/written here via a single BYTE (`lbz`/`stb`), and `ai_wbThrowType_bbVertAngle` (header: u8 at
  0x1DCE) is read here via a 2-byte `lha`. Both are per-minigame-mode memory reuse (same byte range means
  something different for wall-ball vs bob-omb derby, a pattern already established elsewhere in this struct)
  -- used raw `*(u8*)&field` / `*(s16*)&field` casts rather than changing the header (doing so would need to
  prove the width for EVERY other minigame sharing this region, out of scope here) -- see Open questions.
  baseline: 0.50% (bare stub)
  [1] direct translation using the struct fields above, `switch (pitcherActionState) { case WINDUP: ...; case
      IN_AIR: ...; }` (switch, not if/else-if, per this file's established `-inline auto` switch-ordering
      trick), early `return;` for the `checkForPauses()` guard (matches the asm jumping straight to the
      shared epilogue, skipping even the NO_CONTACT tail) -> 82.14% (kept, no further iteration needed for
      the big-picture structure)
  [2] LOGIC fix: both AI-button comparisons were inverted (`windupCountdownUntilBallReleased <=
      ai_wbChargePower_bbSwingFrame`, not `>=`; `pitchHangtimeCounter < frameWhenUnhittable -
      ai_wbThrowType_bbVertAngle`, not `>=`) -> 82.19% (kept -- real behavioural bug fixed, score barely
      moved since the dominant remaining diff is elsewhere)
  Remaining diff at 82.19%: target keeps the two `isAIControlled[i]=0` reset loops as REAL loops (dynamic
  index, `stb r3,0x1dbc(r5); r5+=1`, branch back); our build fully unrolls both into 4 straight-line stores
  each. This is the same small-constant-trip-count loop-unrolling divergence seen in `bOD_LoadGame`'s
  12-field loop, just more severe here (full unroll vs. MWCC's 2x unroll there) -- a `-O4,p`
  unrolling-heuristic difference, not a logic error; register-allocation/Opus territory. All other remaining
  diffs are register-letter noise (r24-vs-r25, r26-vs-r29/r30) cascading from this unroll difference and
  branch-target addresses shifting because of it.

fn_3_1128EC (formerly stub) -- "camera fireworks-launch" function, fires during the batter-celebration/MVP
  intermission. Fully typed via a known struct: `camera_803c639c_s` (`include/static/UnknownHomes_Static.h`)
  already declares `proj`(Mtx44)/`view`(Mtx)/`eye`(Vec)/`target`(Vec)/`Up`(Vec) at the exact byte offsets this
  function's asm reads/writes (0x00/0x40/0x70/0x7C/0x88) -- `pfVar3[0x1c..0x21]` in Ghidra's untyped-float-array
  view is literally `cam->eye`/`cam->target`. `returnFloatFromModeIndex`/`maybeFireworks`/`PSVEC*`/`PSMTX*` are
  all pre-existing, correctly-signatured declarations; only new extern needed was `fn_8003414C` (unknown
  purpose, takes a `Mtx`) and `lbl_3_bss_B699` (persistent toggle byte, size 0x1F in symbols.txt is the common-
  bss inflation artifact, only byte 0 is used).
  baseline: 0.53% (bare stub)
  [1] direct translation using `cam->eye`/`cam->target` directly as PSVEC call args (no local copies), outer
      test `if (_18A6 < 1) {bigblock} else {_18A6--;}`, separate `Vec diff` distinct from `pos`/`eye` locals,
      literal float constants for the 8 named-but-valueless rodata slots (326C=200, 3270=55, 3274=250,
      3278=100, 327C=0, 3280=-55, 3284=-10, 3288=32767, byte-dumped from the unit's own `.rodata`) -> 72.44%
      (kept as starting point)
  [2] LOGIC/STRUCT fix: target actually copies `cam->eye`/`cam->target` into LOCAL stack Vec3f temporaries
      before the vector math (confirmed by real stack-relative loads/stores the first draft was missing
      entirely), and the outer branch's TRUE/FALSE block physical order was backwards (target falls through
      to the big block and branches AWAY to the short decrement, i.e. source reads `if (_18A6 <= 0) {big}
      else {_18A6--;}`, not `< 1`/`> 0` -- `<=0` is what canonicalizes to the observed `cmpwi r3,0;bgt`) ->
      73.34% then 76.68% after getting both parts right together
  [3] removed the redundant separate `diff` local: target's `PSVECSubtract(&target,&eye,&target)` writes its
      result BACK INTO the same stack slot as the `target`-copy (dst==first operand), i.e. there is no
      separate "diff" in source, just a single `pos` local initialised from `cam->target` and mutated in
      place by every subsequent PSVEC call -> 79.41% (kept, best so far)
  Remaining diff at 79.41%: mostly the same whole-TU rodata float/double constant-pool reordering issue as
  the other functions in this file (`lbl_3_rodata_326C` etc. show as anonymous `@321`-style pool entries on
  our side -- values already verified byte-identical), plus register-allocation/stack-slot-order noise in the
  two rand()%N jitter-component computations (x/y/z declaration order within `jitter` very likely needs to
  match target's real field-write order, which from the asm is x, then z, then y -- not yet tried reordering
  the three `jitter.*` assignment statements to `x; z; y;` source order). Logic and data flow fully correct;
  left remaining register/pool grinding for Opus.

bOD_LoadGame (formerly stub)
  baseline: 0.55% (bare stub)
  Ghidra decompile (address 0x807516A4) gave real structure but Ghidra's own do-while(iVar5=2)-with-3-pointers
  loop representation is misleading for 2 of its 5 "tracks" (see Open questions). Header corrections applied
  (shared with the other new functions, see below): `MiniGameControlStruct.aIStrength` widened `u8[4]`->`u8[6]`
  (absorbs the old placeholder `_14`/`_15`, same total struct size 0x16, zero codegen impact for any existing
  caller since C doesn't bounds-check array literals) -- backed by 3 independent pieces of evidence from
  *other* already-written files: `toy_field_offscreen.c` loops `aIStrength[2+i]` for i<3 (reaches index 4),
  `fielder.c`/`batter_ai.c` already read offsets 0x14/0x15 of this struct directly as `._14`/`._15` in the
  exact same code pattern as their neighbouring `aIStrength[2]`/`aIStrength[3]` reads. Updated those 3 call
  sites (`batter_ai.c:172`, `fielder.c:665`, `fielder.c:672`) from `._14`/`._15` to `.aIStrength[4]`/`[5]` --
  pure rename, confirmed zero score change on `game/game/batting/batter_ai` and `game/game/fielding/fielder`
  after rebuild. Also retyped `MiniGameStruct.minigamePoints_current_Latest` from `s32[4]` to `s16[4][2]`
  (zero prior usages anywhere in the tree, so zero risk): the asm zeroes it with two `sth` per element, not
  one `stw`, which only makes sense for a 2-element s16 row, not a single s32; same total size (16 bytes),
  no later-field offset shift.
  New externs added: `bOD_challenge_nPitches_Points[4][2]` (s16, already a named `.data` symbol, byte-dumped
  from `auto_04_00021268_data.s`: `{{10,1000},{10,1500},{10,2000},{10,0}}`), `lbl_3_data_2127C[8][5]` (u8,
  byte-dumped, row-stride 5 confirmed from `mulli r5,r0,5`), `lbl_3_data_213E4[8]` (u8, byte-dumped: all 3s
  except a trailing zero pad), `initializeSomethingDuringTransition` (via existing
  `game/match_setup/match_loading.h`, already used identically by barrel_batter.c).
  Field `g_GameLogic._121` turned out to be the ALREADY-NAMED `secondaryGameMode` (`E(u8,SECONDARY_GAME_MODE)`)
  -- compile error caught the wrong offset math immediately; fixed to
  `g_GameLogic.secondaryGameMode = SECONDARY_GAME_MODE_BOBOMB_DERBY` (matches Ghidra's own
  `gameControls.SecondaryGameMode = BobOmbDerby` line exactly, and the enum, value 3, was already in the repo).
  [1] direct translation: `if (_125==0) { init; secondaryGameMode=...; _17C0=0; for(i<4) {12 field writes,
      including 2 raw-pointer-cast tracks for the two fields whose byte-run crosses a named-field boundary};
      resets; if(multiPlayerInd==0){solo table lookups} else {multiplayer table lookups}; if(_1A3C!=0){two
      randoms} else if(multiPlayerInd==0){soloDiff==3 ? 9 : random(4,9); _1AD9=1} else {9,1}; _125++; }
      else SetGameStatus(GAME_START_MOVIE);` -> 76.21% (kept as starting point)
  [2] LOGIC fix: the asm's field781/782 block has REAL redundant re-tests of multiPlayerInd/_1A3C baked in
      (not Ghidra's simplified view) -- changed outer test from `if(_1A3C!=0){...}else if(multiPlayerInd==0)`
      to the compound `if(multiPlayerInd==0 && _1A3C==0){soloDiff logic} else if(_1A3C!=0){...} else {9,1}`,
      i.e. literally transcribing the compound `&&` as MWCC compiles it (tests each half separately, every
      arrival at the `else if` re-tests its own condition independently of the preceding compound test) ->
      84.26% (kept)
  [3] reordered the solo-branch statements to compute `bODRoundStartingNumPitches`/`pointsReqToWin_challenge`
      (both from `bOD_challenge_nPitches_Points`) BEFORE `aIStrength[0]` (from `lbl_3_data_2127C`), matching
      which data-table address target loads into a register first -> 87.98% (kept)
  [4] flipped the final if/else polarity (`if(_1A3C!=0){randoms} else {9,1}` instead of
      `else if(_1A3C==0){9,1} else {randoms}`) -- same boolean result, but target emits the two-randoms block
      BEFORE the 9,1 block physically -> 93.59% (kept, best so far)
  Remaining diff at 93.59%: almost entirely register-letter noise (r8/r9/r10 swaps cascading from the base
  pointer being r9 in target vs r10 in ours) through the 12-field unrolled loop, one SYMBOL_NAME pair ordering
  (`g_Scores@ha` load before vs after `li r4,0x1e`), and the two strength-reduced pointers the target keeps as
  dedicated induction variables (`r4`=&_1900-track, `r5`=&battingHandedness[2]-track, each `+=2` per outer
  iteration) where ours uses the shared base+immediate(r12) form -- classic register-allocation/induction-
  variable-choice territory, left for Opus. Not chased past 4 structurally distinct attempts per role.

unused_BODRelated (formerly stub, real asm never implemented before this session)
  baseline: 0.98% (bare stub)
  Ghidra decompile (address 0x807500CC, name `unused,BODRelated` i.e. `unused_BODRelated`) gave real field
  names directly: `inMemBall.Hit_HorizontalPower_bODBasePoints` = `g_Ball.Hit_HorizontalPower` (already has
  a `// bODBasePoints` comment in the header confirming this), `minigamesRosterIDOfCurrentPlayer` =
  `g_Minigame.rosterID`, `bOD_HitPowerOfEachChar`/`bODCharacterHRStreakTracker`/`bOD_KingBombInd`/
  `miniGameLatestPoints`/`miniGameCurrentPoints` all already-named header fields. `someTeamInd` in the
  Ghidra decompile and `doubleConst`/`CONCAT44(0x43300000,x^0x80000000)` are Ghidra's rendering of the
  standard PPC signed-int-to-float conversion bit-trick and of `lbl_3_common_bss_37400[0x20]` (confirmed
  byte-offset 0x40 == s16 index 0x20) -- both already used verbatim as a pattern in
  `src/game/minigame/barrel_batter.c:778` (`if (!g_d_GameSettings.exhibitionMatchInd && g_Minigame.rosterID
  == lbl_3_common_bss_37400[0x20]) starMissionsMinigamesSpecialAction(...)`), so this function reuses that
  exact idiom with `missionType=0`. Added externs `lbl_3_data_213EC[10]` (asm offsets 0x1C/0x10 inside it
  decode as `[7]=200` "king bomb bonus" and `[8]=15` "per-extra-streak combo bonus", byte-dumped from
  `build/GYQE01/game/asm/auto_04_00021268_data.s`), `lbl_3_common_bss_37400[0x27]` (copied from
  barrel_batter.c's existing extern) and `starMissionsMinigamesSpecialAction` prototype (same signature as
  barrel_batter.c), plus `#include "static/UnknownHomes_Static.h"` for `g_d_GameSettings`.
  [1] wrote `g_Minigame.rosterID`/`g_Ball.Hit_HorizontalPower` field accesses directly at every use site (no
  cached rosterID local, matching the repeated `lbz 0x1905` reloads in the asm), one `s16 hitPower` local
  (asm keeps it live in one register across the whole function, consistent with a local), one `f32 points`
  accumulator, and `(s16)points`/`(int)points` cast directly at each of the three use sites (store to
  miniGameLatestPoints, add-in-place to miniGameCurrentPoints, call arg) with no shared int local --
  reproduces the asm's three separate stfd/lwz float->int materializations exactly -> 99.754906% (kept, no
  further iteration needed)
  Remaining diff at 99.75%: purely the file's shared `doubleConst` rodata double (`lbl_3_rodata_3260`,
  scope:local, already in this unit's own .rodata) showing as anonymous `@409` on our side -- same whole-TU
  float/data pool reordering issue already logged under fn_3_110A38/fn_3_1111D0; expected to move once more
  of the file's stubs are implemented (see Open questions).

bOD_bB_Pitcher_waitingForPitch
  baseline: 0.85%
  New enum added (evidence: Ghidra's `.ghidra_cache/in_game.types.txt` `barrelBatterPitchNum_byte`/`barrelBatterPitchNum_int` enums, real named values mushroom/flower/star/king/fire): `BARREL_BATTER_PITCH_NUM`. Two new MiniGameStruct fields added past the memset-cleared region: `_1DF4` (unsure, Ghidra itself uncertain: "starPitchInd?/const_0?") and `bODPitchType` (E(u8,BARREL_BATTER_PITCH_NUM), Ghidra-confident).
  [1] direct translation of Ghidra decompile (`isBarrelBatter`/`pitchTiming`/`starPitch` as `BOOL` locals, `weightedIdx` extra temp, index expression `selType*5 + pitchType*2` in one shot) -> 90.25%/91.75% variants (register swaps from an unnecessary `isBarrelBatter` BOOL local reused across 2 ifs producing a direct `cmplwi` compile instead of target's CLZ boolean idiom at that point, one extra `extsh` from `s16 pitchTiming`, and a pointer-arithmetic addition-order mismatch in the weights-table address)
  [2] removed the `isBarrelBatter` local (compared `g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER` inline in each `if`), changed `starPitch` to `u8` (matches target's `clrlwi.` byte-truncating truthiness test), inlined `weightedIdx` into the `speedLevel` expression -> 92.09% (kept as an incremental step)
  [3] rewrote the weights-table pointer as `&lbl_3_data_213A4[selType * 5] + pitchType * 2` instead of `&lbl_3_data_213A4[selType * 5 + pitchType * 2]` (same address, different C expression) -> 95.98% (kept -- matched target's base+selType*5-then-+pitchType*2 addition order exactly)
  [4] changed `pitchTiming` from `s16` to `int` -> 97.18% (kept -- eliminated a spurious `extsh` from comparing a 16-bit local against `g_Pitcher.currentStateFrameCounter`)
  [5] re-tried a `u8 isBarrelBatter` local (single CLZ-idiom candidate for `flag = a==b`) now that [3]/[4] were in place -> 96.40%/97.18% (worse than direct inline comparisons in both re-tests; reverted, kept the direct-comparison form from [4])
  Remaining diff at 97.18%: the two `g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER` comparisons compile as plain `cmplwi`/branch pairs in ours, but the target compiles the first occurrence via the branchless CLZ equality idiom (`subfic`/`cntlzw`/`srwi.`) and reuses that boolean result for the second (negated) test — i.e. the target genuinely stored this comparison in a boolean local reused twice, but every attempt to reproduce that with an explicit local scored worse overall (variants [1] and [5]), so the direct-comparison form was kept as the best of 5 structurally distinct variants tried. All other remaining diffs are branch-target addresses (expected, other stubs in the file not yet implemented).

fn_3_111AC4
  baseline: 0.98%
  Struct-shape correction backed by evidence: reshaped `bODCharacterHRStreakTracker` from flat `u8[8]` to `u8[4][2]`, since both this function's asm (`(g_Minigame + 0x1ACC + rosterID*2)[0] = 0`) and Ghidra's decompile of the still-unimplemented `bobOmbDerbyBatterAI` independently index it as `[rosterID][0]`.
  [1] direct translation of Ghidra's nested if/else (`turnOverStatus==0` branch with pitcherActionState/miniGameTurnCounter/bODRoundStartingNumPitches/bODCharacterHRStreakTracker/bobOmbDerbyPitching, else branch with CountdownUntilFade decrement, the compound `pointsTargetReachedInd && (multiPlayerInd==0 || (multiPlayerInd!=0 && miniGameNumberOfParticipants<=turnNumberWithinRound+1 && Inning>=inningLimit)) && (_1A37==0 && CountdownUntilFade==0x43)` sndFXStartEx guard, `CountdownUntilFade==7` changeScene, and `CountdownUntilFade<1` transition-out block) -> 99.75% (kept as starting point; two residual diffs: the `miniGameNumberOfParticipants <= turnNumberWithinRound+1` comparison compiled with reversed operands/branch polarity vs target, and `CountdownUntilFade < 1` compiled against immediate 1 with `bge` instead of target's immediate-0-with-`bgt` form)
  [2] rewrote the participant comparison as `turnNumberWithinRound + 1 >= miniGameNumberOfParticipants` (operands swapped, same math) -> fixed that instruction
  [3] rewrote `CountdownUntilFade < 1` as `CountdownUntilFade <= 0` (same math, canonicalized differently by MWCC) -> 100.0% (kept -- both fixes combined reached an exact match)

unusedBODFunction
  baseline: 1.05%
  Struct-shape correction backed by evidence: consolidated MiniGameStruct's separately-named `bODRelated5`/`bODRelated6`/`bODUnusedBytes[8]` (0x1A96-0x1A9F, unused anywhere else in the codebase) into a single `u8 bODRelated5[10]` since this function's target asm iterates that exact 10-byte span as one countdown array indexed 0..9.
  [1] ballPhysica(); if(...)angle-clamp+runner->runningAngle store (pointer local declared up front, like fn_3_1111D0); qualifying-hit-and-score block; `for` loop over bODRelated5[10] using `--bODRelated5[i] == 0`; foul-ball check; soundFxRelated(); bobOmbDerbyCalculatePoints() -> 90.25% (kept as starting point; remaining diff: g_Runners pointer computed lazily instead of eagerly like target, decrement idiom used combined `--x==0` instead of target's decrement-store-reload-compare form, and a rodata struct field one member short, plus expected stub-inlining/branch-address noise)
  [2] extended local `lbl_3_data_21438` extern struct with a 4th `_0C` field (target reads offset 0xC, but the shared 3-float version copied from ball_physics.c/batter.c only covers 0x00-0x0B) and fixed the compare to use `._0C` -> fixed one instruction exactly
  [3] rewrote the countdown as `if (bODRelated5[i]!=0) { bODRelated5[i]--; if (bODRelated5[i]==0) {...} }` instead of `if (x!=0 && --x==0)` -> matched target's decrement/store/reload-from-memory/compare instruction sequence exactly (previously used a register-resident `clrlwi.` compare)
  [4] removed the `InMemRunnerType *runner` pointer local, used `g_Runners[0].runningAngle` directly -> 93.42% (slightly worse than re-adding the pointer local)
  [5] re-added `InMemRunnerType *runner = &g_Runners[0];` declared first (before `angle`/`i`) -> 93.58% (kept -- best variant)
  [5b] tried moving the pointer-local's declaration to last among the locals -> 93.58% (no change, reverted to declaring it first for readability)
  Remaining diff at 93.58%: the two calls to `BODScoring()`/`bobOmbDerbyCalculatePoints()` are absent from our object because both are still `{ return; }` stubs and get inlined away as no-ops under `-inline auto` (expected per task instructions -- will resolve once those functions are implemented); one residual r3/r4 register-letter swap in the `&g_Runners[0]` address computation (2 instructions) that didn't respond to declaration-order changes; and all remaining diffs are branch-target addresses (expected, other stubs in the file not yet implemented).

fn_3_111F80
  baseline: 1.67%
  [1] switch(g_GameLogic._125) over TRANSITION_CALCULATION_TYPE_0..3, case 1's compound condition written as `frameCount>=arr[2] || (frameCount>=arr[1] && checkForButtonPressToSkip(1,0x1100))` -> 100.0% (kept, no iteration needed; verified against Ghidra decompile of FUN_80751014 which matched this control flow exactly)

fn_3_112450
  baseline: 1.52%
  [1] if/else-if with case TRANSITION_CALCULATION_TYPE_1 (someAnimationIndFunction) written FIRST, case TRANSITION_CALCULATION_TYPE_0 (reset* calls) SECOND, matching the asm's comparison test order (target tests `==1` before `==0`) -> 60.08% (test order matched but physical block order didn't: target places case-0's body block first in memory, case-1's body last, whereas an if-first-tested/if-block-emitted-inline compile emitted case-1's body first)
  [2] swapped to natural if/else-if source order (case 0 first, then case 1, then default), matching target's physical block order -> 84.47% (block order fixed; but this changed the compiler's comparison test order away from target's `==1`-first pattern, and reintroduced an r30/r31 register swap)
  [3] same case-0-first/case-1-second/default-third order, but as a `switch` statement instead of if/else-if chain -> 98.79% (kept -- switch let MWCC choose its own comparison-tree order, which reproduced the target's `==1`-first test AND `case0,case1,default` block order simultaneously; register allocation (r30/r31) also matched)
  [4] tried swapping the two statement pairs inside case 0 (`rosterID=...` before `pre_PostMiniGameInd=1`, and `highLevelSimulationFlag[2]=0` before `_125++`) together -> untested combination; tried individually:
      [4a] swap `pre_PostMiniGameInd=1` / `rosterID=...` order -> 93.18% (worse, reverted)
      [4b] swap `_125++` / `highLevelSimulationFlag[2]=0` order -> 99.55% (kept -- fixed a second r3/r4 register swap in the tail of the case-0 block)
      [4c] rewrote the array index as `[4 + turnNumberWithinRound]` instead of `[turnNumberWithinRound + 4]` -> 99.55% (no change, reverted to the more natural `turnNumberWithinRound + 4` form)
  Remaining diff at 99.55%: only branch-target *addresses* (expected -- other stubs in the file aren't implemented yet and shift code layout) and one residual r3/r4 register-letter swap in the `pre_PostMiniGameInd=1; rosterID=...` pair (6 instructions) that did not respond to statement reordering; not chased further after the above variants.

fn_3_1128E8
  baseline: 100% (bare `return;` stub is already byte-identical to target -- target body is a single `blr`). No change made.

fn_3_110A04
  baseline: 7.69%
  [1] `memset((u8 *)&g_Minigame + 0x1D7C, 0, 0x78);` -> 100.0% (kept)

fn_3_111A88
  baseline: 6.67%
  [1] set 3 GameControlsStruct flags + SetGameStatus(GAME_STATUS_TRANSITION) -> 100.0% (kept)

fn_3_1125D0
  baseline: 6.25%
  [1] sndFXStartEx(0x1bd, lbl_800EFBA4[6], 0x3f, 0) (identical line already exists in barrel_batter.c) + SetGameStatus(GAME_STATUS_TRANSITION_TO_MINIGAME_START) -> 100.0% (kept)

bobOmbDerbyPitchTransition
  baseline: 0.74%
  [1] first implementation (calls fn_3_1121A4(), then field resets, 10-iteration bODRelated5 clear loop, pre_PostMiniGameInd if/else, pitch-selection-type chain, scene/status calls) -> 72.29% (kept)

fn_3_1120E0
  baseline: 5.56%
  [1] `if (Inning < inningLimit) A else B` -> 99.61% (branch polarity inverted vs target: target used `blt`, ours used `bge`+swapped-body form)
  [2] `if (Inning >= inningLimit) B else A` -> 100.0% (kept)

fn_3_112558
  baseline: 3.33%
  [1] turnNumberWithinRound=0 written before Inning++ -> 87.17% (register allocation order mismatch, g_Minigame address loaded before g_Scores where target does the opposite)
  [2] swapped statement order (Inning++ first, then turnNumberWithinRound=0) -> 100.0% (kept)

fn_3_112128
  baseline: 3.23%
  [1] `else if (turnNumberWithinRound < miniGameNumberOfParticipants) PREPARE_NEXT_PLAY else NEW_ROUND` -> 99.77% (branch polarity: target `blt`, ours `bge`)
  [2] `else if (turnNumberWithinRound >= miniGameNumberOfParticipants) NEW_ROUND else PREPARE_NEXT_PLAY` -> 100.0% (kept)

fn_3_1111D0
  baseline: 3.13%
  [1] plain sequential clamp (`if (angle<0x200) angle=0x200; if (angle>0x600) angle=0x600;`), g_Runners[0] accessed directly at store site -> 60.28% (g_Scores/g_Runners address computed lazily right before store; target loads &g_Runners[0] into r31 near the top and spills it to the stack)
  [2] same clamp, but introduced `InMemRunnerType *runner = &g_Runners[0];` local computed up front -> 80.16% (fixed the early-address-load issue; remaining diff was register choice (r3 vs r0) in the two clamp comparisons)
  [3] replaced the two sequential ifs with `angle = MAX(hitAngle, 0x200); angle = MIN(angle, 0x600);` (types.h MAX/MIN macros), angle kept as s16 -> 85.59% (kept -- this is the best of the variants tried)
  [4] same MAX/MIN form but angle declared s32 instead of s16 -> 83.13% (worse, reverted to s16)
  Remaining diff at 85.59%: minor register allocation differences in the clamp comparison instructions (r0 vs r3, extra `mr`/`extsh` pair) and a rodata constant-pool address mismatch for `const_pi_2` (see below) -- not chased further after 4 variants.

fn_3_111250
  baseline: 4.0%
  [1] 3 GameControlsStruct flags, fn_8003A540(0) (added an `int` parameter to this previously-void external stub based on the target evidence r3=0 being passed; see header change below), then `if (pointsTargetReachedInd==1) TRANSITION else DEFAULT` -> 100.0% (kept)

fn_3_112070
  baseline: 3.57%
  [1] fn_3_DE4FC(); SetGameStatus(GAME_STATUS_MVP_END_GAME); g_Minigame._18A6 = rand()%30+15; bobOmbDerbyPitching(); minigamesSetSomePointers(); minigamesGXStuff(); minigamesSetSomePointers2(); -> 100.0% (kept, no iteration needed)

fn_3_110A04 / fn_3_1121A4 (memset correction)
  Extended MiniGameStruct (include/game/UnknownHomes_Game.h) additively after the existing `_1D7C` field with Ghidra-evidenced fields spanning 0x1D7C..0x1DF4 (isAIControlled, portOfAIBeingProcessed, ai_wbChargePower_bbSwingFrame, ai_wbThrowType_bbVertAngle, wallBallAISwitchVar, minigameAICountDownTillAction, plus unnamed `_XXXX` gaps), matching src/game/minigame/barrel_batter.c's existing `memset(&g_Minigame._1D7C, 0, 0x78);` idiom. Rewrote both functions' memsets from `memset((u8 *)&g_Minigame + 0x1D7C, 0, 0x78);` to `memset(&g_Minigame._1D7C, 0, 0x78);`. Both stayed 100.0% after rebuild. Full-project report.json fuzzy_match_percent diff (before/after header edit, all 6479 functions): only 1 changed, `game/game/minigame/barrel_batter:fn_3_12EE68` 1.27% -> 89.03%, an improvement caused by the other agent's concurrent edits to barrel_batter.c landing in the same rebuild, not by this header change -- no regressions anywhere.

fn_3_1121A4
  baseline: 2.86%
  [1] setInMemBatterConstants(rosterID); 5x setDefault*(); memset(_1D7C region); pauseAnimations(); Set_803cb848(1) (added `BOOL` parameter to this previously-void external stub, see header change below); g_FieldingLogic.playOverCounter=0; g_UnkSimulation_31AC0._05=0; _06=4 (reused the identical local typedef+extern already present in barrel_batter.c, duplicated locally since it's not in a shared header) -> 100.0% (kept, no iteration needed)

fn_3_110A38
  baseline: 2.56%
  [1] `if (starPitchInd) { if (starPitchType==1) return 20; return 20; } return (s32)(4.712389f*(f32)((f64)field - 3.1415927) - 1.0f);` -> 74.74% (float codegen was single-precision fsubs+fmadds already close, but target keeps the first subtraction as a double `fsub`/needs an explicit `frsp` narrowing later; also the two "return 20" branches were tail-merged by the compiler into one block, while target keeps two separate duplicate blocks)
  [2] reordered to `-1.0f + 4.712389f * (f32)(...)` to steer towards fmadds form -> 76.28%
  [3] wrapped the u8->f64 conversion explicitly as `(f32)(f64)field` before subtracting a f32 PI literal -> 79.23% (closer instruction match, but still an extra double fsub+frsp pair)
  [4] dropped the redundant explicit `(f64)` cast, i.e. `(f32)field - 3.1415927f` -> 83.33% (single-precision `fsubs` matched exactly on both subtractions now; only the branch-merge issue and rodata pool-address issue remained)
  [5] replaced the `if/if` duplicate-return with a `switch (starPitchType) { case 1: return 20; default: return 20; }` to prevent MWCC's tail-block merge -> 98.72% (kept -- this was NOT a `goto`; the structured `switch` form was tried first and it worked, so no `goto` was ever needed here)
  Remaining diff at 98.72%: purely `DIFF_ARG_MISMATCH` on the rodata constant-pool relocations (`lbl_3_rodata_3250`/`3254`/`3258`/`324C` in target vs anonymous `@NNN` pool entries in ours) -- the VALUES are identical (verified via the .rodata byte dump: 4.712389, 3.1415927, -1.0, and a stack-double bias constant), only the pool ADDRESS differs. This is very likely just a byproduct of most of the rest of the file's ~20 other functions still being unimplemented stubs, which shifts where MWCC lays out this TU's float/double constant pool relative to the original binary. Expected to resolve on its own once the remaining stub functions in this file (not in this task's scope) are implemented in address order.
  [6] CORRECTION: [1]-[5] used wrong constants (4.712389/3.1415927/-1 are repHeaderData values, not this function's); rewrote with -0.18867925/138/35 -> 98.71795% (same instruction-level match as before; remaining diff still purely the rodata constant-pool relocation address mismatch, values now confirmed correct against target asm 0x3250/0x3254/0x324C/0x3258)

fn_3_1111D0 (correction, continued)
  [5] CORRECTION: previous const_pi_2 static was 1.0f, wrong; real value 1.5707964f. Removed the static, removed MAX/MIN, wrote target's exact control flow: `angle = g_Ball.Hit_HorizontalAngle; if (angle<0x200) angle=0x200; if (angle>0x600) angle=0x600;` with `angle` as `s16` -> 80.15625% (register allocation used r3 for the clamp instead of target's r0)
  [6] same control flow, `angle` changed to `s32` -> 99.6875% (kept -- fixed the r0/r3 register allocation to match target exactly). Remaining diff at 99.6875%: only branch-target *addresses* differ (expected, since other stubs in the file aren't implemented yet and shift code layout) and the rodata constant-pool label (`const_pi_2` vs anonymous `@205`) -- same known constant-pool-layout artifact as fn_3_110A38, values already verified identical (1.5707964f).

## Verified state at session end (2026-10-01, match-sonnet first pass, objdiff-cli)

The table at the very top of this file is current and authoritative; this section is a dated snapshot for
quick reference. Every function that was still a bare `return;` stub at the start of this session has been
drafted (0 stubs left, down from 8). 12 functions are `matched` (100%); the other 14 are `pending` with real,
evidence-based logic, left for the Opus `match` pass to grind register allocation / stack layout / the
whole-TU float-constant-pool reordering.

| function | status | pct |
|---|---|---|
| bobOmbDerbyBatterAI | pending | 58.43% |
| fn_3_110A04 | matched | 100.0% |
| fn_3_110A38 | pending | 98.72% |
| BODScoring | pending | 84.68% |
| unused_BODRelated | pending | 99.75% |
| fn_3_1111D0 | pending | 99.69% |
| fn_3_111250 | matched | 100.0% |
| bobOmbDerbyCalculatePoints | pending | 99.46% |
| unusedBODFunction | pending | 95.68% |
| bOD_bB_Pitcher_waitingForPitch | pending | 97.18% |
| fn_3_111A88 | matched | 100.0% |
| fn_3_111AC4 | matched | 100.0% |
| fn_3_111C5C | pending | 83.40% |
| fn_3_111F80 | matched | 100.0% |
| fn_3_112070 | matched | 100.0% |
| fn_3_1120E0 | matched | 100.0% |
| fn_3_112128 | matched | 100.0% |
| fn_3_1121A4 | matched | 100.0% |
| bobOmbDerbyPitchTransition | pending | 72.29% |
| fn_3_112450 | pending | 99.55% |
| fn_3_112558 | matched | 100.0% |
| fn_3_1125D0 | matched | 100.0% |
| bOD_LoadGame | pending | 93.59% |
| fn_3_1128E8 | matched | 100.0% |
| fn_3_1128EC | pending | 79.41% |
| bobOmbDerbySimulation | pending | 90.60% |

12/26 matched, 14 pending, 0 stubs. Section scores: `.text` 0.895% (session baseline) -> 88.56%,
`.rodata` 67.80% -> 78.05% (`[.rodata-0]` symbol: 76.35% -> 78.05%), `.data` 0% -> 0% at the whole-section
level but the jumptable symbol itself (`[.data-0]`) is at 61.11% and should climb automatically as
`bobOmbDerbySimulation`'s remaining register-alloc diffs close, `.bss` 0% (unreferenced by anything in this
file apart from `fn_3_1128EC`'s stub, now drafted but not using any `.bss` data).


## Opus pass (2026-10-01) -- session log

Measure: `objdiff-cli diff` (strict reloc compare) is authoritative. report.json's `report generate` relaxes
relocation-target diffs, so it scored fn_3_110A38/fn_3_1111D0/unused_BODRelated 100% while their pool
constants pointed at the wrong .rodata offsets (a real post-link byte difference). Both now agree at 100%.

[O1] FILE-WIDE: `#define SQRT2_LINKAGE static` at top + function definitions reversed into reverse-address
     order (-inline deferred) -> .rodata 76.54 -> 92.11; pool now in target order but shifted 0xC.
[O2] FILE-WIDE: the missing 0xC object at lbl_3_rodata_3240 is an UNREFERENCED Vec {0,-45,160} (no reloc
     anywhere in the target unit). Added an uncalled `inline const Vec *getLbl_3_rodata_3240(void)` with the
     Vec as its local static (same mechanism as header_rep_data.h) -> .rodata 97.44 (remaining = 4-byte
     trailing alignment gap gap_03_0000328C, section-alignment padding), fn_3_110A38/unused_BODRelated/
     fn_3_1111D0 -> 100, +0.1..0.5 on BatterAI/CalculatePoints/unusedBODFunction/fn_3_1128EC/Simulation.
[O3] bobOmbDerbySimulation: replaced the 9 hand-duplicated case bodies with plain calls (fn_3_1125D0, fn_3_112558,
     fn_3_112450, fn_3_111C5C, unusedBODFunction, fn_3_112128, fn_3_1120E0, fn_3_111F80, fn_3_112070) --
     MWCC auto-inlines all of them; only fn_3_111C5C refused (too big) -> see [O4]. (All-calls alone: 59.4
     because 111C5C stayed a bl; `inline` keyword on 111C5C: Simulation 91.2 but no out-of-line copy emitted.)
[O4] fn_3_111C5C restructured from the target asm: `if (turnOverStatus == 0) { pauses; atBat_Pitcher();
     bOD_AI(); atBat_batter(); bOD_clearAIControlled(); fielding; running; } fn_3_111AC4();` -- the target
     RE-TESTS turnOverStatus after the first block, i.e. the tail is fn_3_111AC4 inlined. The AI clear loops
     are `s8 i; i = 0; do { isAIControlled[i] = 0; i++; } while (i < 4);` (for-loops get unrolled; same
     recipe as barrel_batter bB_AtBat [O2]). Moving the AI clear+per-slot loop into `static inline
     bOD_AI()` and the clear loop into `static inline bOD_clearAIControlled()` shrinks 111C5C enough that
     Simulation auto-inlines it, AND reproduces the target's `mr r3,r4` const-0 copy in both clear loops
     (it comes from inlining the helper). Main per-slot loop is also a do-while (target has no entry
     branch). fn_3_111C5C 83.40 -> 99.35, Simulation 90.62 -> 98.87.
     Residual (both copies): target addresses minigameAICountDownTillAction/ai_wbChargePower/
     ai_wbThrowType off the clear-loop's &g_Minigame (r26); ours off the hoisted rosterID base (r29),
     which shifts r24-r27 numbering.
[O5] unusedBODFunction: its clamp/runningAngle block IS fn_3_1111D0 inlined -> `ballPhysica(); fn_3_1111D0(); ...`
     -> 95.79 -> 100 (MATCHED); Simulation 98.87 -> 99.68 (its LIVE_BALL case is unusedBODFunction inlined).
[O6] bobOmbDerbyCalculatePoints: HR block = `bOD_HRStreak++; CountdownUntilFade = ...; unused_BODRelated();` and
     the fade tail = `fn_3_111250();` (both codegen-identical, kept for fidelity). Then statement order:
     `CountdownUntilFade = 21448[2]` BEFORE `bOD_HRStreak++` -> 99.90; `CountdownUntilFade = 21448[1]` BEFORE
     `turnOverStatus = 1` in the framesOnGround branch -> 100 (MATCHED).
LESSON (file-wide): most "duplicated" blocks in this file are already-matched small functions auto-inlined
     (fn_3_1111D0, unused_BODRelated, fn_3_111250, fn_3_111AC4, fn_3_110A38...). Check every pending function
     for a callee body before register-grinding.
[O7] bobOmbDerbyPitchTransition: bODRelated5 clear loop counter `s32` (long) -> MWCC keeps the un-folded
     `li r0,0; cmpwi r0,10; bge` guard before the fully unrolled stores (int: guard folded away); and
     `totalFramesAtPlay = 0; hasProcessedFoulBall = 0; windup = 21448[4];` moved BEFORE the
     pre_PostMiniGameInd if/else -> 72.29 -> 100 (MATCHED).
fn_3_112450 (99.55; also the PREPARE_NEXT_PLAY case of Simulation)
  residual: target `lis r4,g_Minigame; li r3,1` (address r4, const-1 r3); ours swapped.
  [O8a] all 120 permutations of the 5 leading case-0 statements -> current order best (99.55)
  [O8b] index forms: `(&aIStrength[4])[turn]`, `(int)turn + 4`, `*(aIStrength + 4 + turn)` no change;
        `(u8)(turn + 4)` 96.42; `minigameControlStruct[turn].characterIndex[0x14]` 98.03
  [O8c] moving the 4 g_Minigame stores (with/without pre_PostMiniGameInd) into a static inline helper: no change
bOD_LoadGame (93.59 -> 98.18, pending)
  [O9a] HEADER: MiniGameStruct `_1900.._1903` (4 separate u8) -> `u8 _1900[4]`; loop stores now `_1900[i] = -1`
        and `minigameControlStruct[1].battingHandedness[i + 2] = 1` (direct array lvalues fold onto the shared
        r12 induction base like target; pointer-cast forms make extra induction pointers) -> 95.92.
        barrel_batter.c's four `*(s8 *)&g_Minigame._190N` became `_1900[N]` (barrel_batter unit unchanged).
  [O9b] target re-tests `multiPlayerInd == 0 && _1A3C == 0` inside the solo branch:
        `if (multi == 0 && _1A3C == 0) { if (multi == 0 && _1A3C == 0 && soloDiff == NON_CHALLENGE) 9 else
        Random(4,9); _1AD9 = 1; }` -> 98.18 (looks like an inlined predicate helper in the original)
  tried (no gain): `*(s8 *)&arr[i] = -1` casts (91.12, break the induction folding); `((s8 *)arr)[i]` (91.19);
        `s8 none = -1` local stored everywhere (no change -- folded back to 0xFF);
        header experiment: _18FC/_1900/minigameFielderIndex as s8[4] -> 93.15 (needs ALL of them s8,
        including the 0x18F4 store, else two constants).
  BLOCKER (remaining = 1 constant + register renumber): target stores ONE `li r6,-1` into 0x18F4+i,
        _18FC[i], _1900[i], minigameFielderIndex[i], minigamePlayerSelectedOrder and rosterID -- i.e. all
        those lvalues are s8 in the original. 0x18F4 is `minigameControlStruct[1].aIStrength[i+2]` in our
        model, which every other TU already reads through `(s8)` casts (animation_dispatch MINIGAME_SLOT_OF,
        fielder, ball_physics, batter_ai) -- strong evidence the [2]-struct model of 0x18CC..0x18F7 is wrong
        (0x18E0[4] is the per-turn rosterID order, 0x18F0[4] = 1s, 0x18F4[4] = s8 slots). Fix needs a
        cross-TU retype of that region + _18FC/minigameFielderIndex/minigamePlayerSelectedOrder to s8 (some
        users index/pass them uncast, e.g. runner.c:4877, fielder.c:17551) -- out of scope for this pass.
fn_3_1128EC (79.89 -> 100, MATCHED)
  [O10] `pos.y > 55.0f` / `pos.y > -55.0f` (operand order: target loads pos.y first, `ble`); jitter order
        x, y, z (z = 0 store gets scheduled between); `u8 count` with `if (lbl_3_bss_B699 != 0) %5+8 else %4+4`
        -> 98.93 (+ .rodata 97.44 -> 100); pass `count` (not `count & 0xFF`) -> 100.
BODScoring (84.68 -> 99.87, pending)
  [O11a] first branch: `calculateAngleFromCoordinates(pos.x, pos.z)` / `(ballDistanceFromHome, -pos.y)` (target
         reloads pos.y and negates); firework branch order `starPitch / bOD_KingBombInd != 0 (13) / else` -> 90.79
  [O11b] second branch rewritten from asm: single function-scope `Vec pos` (frame 0x40 -> 0x30);
         `_18A6 <= 0`; yaw/pitch are `int` (no extsh until the s16 call arg);
         `getComponentsFromSAng(pitch, &px, &pos.y)` then scale; branch order `starPitch (0,3) / _18A0 & 1
         (4,7) / else (8,12)`, each with its own camera+fireworks call; HEADER: `_18A0` s16 -> u16 (target
         uses lhz; other users only store 0) and dropped the (u16) casts -> 99.12
  [O11c] function-scope `cam`/`count` shared by both branches -> 99.41 (separate per-branch decls: 99.12)
  [O11d] `static inline bOD_launchFireworks(Vec *pos, int count)` { getCamera(0); maybeFireworks(.., 1) }
         used at all 6 sites -> 99.71 (removes the `mr r0,r3; mr r29,r0` copy)
  [O11e] 24 permutations of the scale block: best `x *= s; z *= s; y /= px; y *= -s;` -> 99.87
  tried (no gain): yaw/pitch decl order (99.70), `i`/`px` at function scope (no change), extra helper
         wrapping RandomInt (no change).
  residual: second branch g_Pitcher base r30 vs target r29, count r29 vs r30 (swap only).
bOD_bB_Pitcher_waitingForPitch (97.18 -> 100, MATCHED)
  [O12] `BOOL isBarrelBatter = GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER;` (int, not u8 as [S1] tried)
        used for the first two tests only (third test stays a direct compare) -> 97.56; declaration order
        `pitchTiming, isBarrelBatter, starPitch` (perm of 3) -> 100.
bobOmbDerbyBatterAI (58.56 -> 92.59, pending)
  [O13a] rewrite from asm: both weight loops read lbl_3_data_21488[aiDifficulty][i] (the [S1] "aiDifficulty+1"
         reading was wrong: loop 1 walks a COPY of the r11 row pointer, loop 2 walks r11 itself from the same
         start); `s8 i`; per element `w[i] = base; w[i] += streak * mult;`; flag test order
         `if (_1DF6[0] != 0) +flagTable else if (bOD_KingBombInd) +kingTable`; tail is
         `chargeFrame - (fn_3_110A38() - ai_wbThrowType)` (fn_3_110A38 inlined incl. its starPitch test) -> 77.72
  [O13b] `u8 streak` local at top + reassigned before loop 2; loops as do-while -> 81.52
  [O13c] charge switch `case 0: default: / case 1: / case 2:` (target: ==1, >=3 tree, default body first);
         ai_wbThrowType = swingSoundFrame[1][idx] + RandomInt(...) with no s16 temp -> 84.40
  [O13d] `MiniGameStruct *mg = &g_Minigame;` for all accesses -> 90.82 (target keeps &g_Minigame in r29 from
         the prologue to the final ai_wb* stores); with the two in-loop flag tests (_1DF6/KingBomb) written as
         direct g_Minigame accesses (so they are hoisted out of the loops like target) -> 92.59 (kept).
  tried (no gain): direct g_Minigame for the 2nd streak load (91.69); 7 add-order forms for case 1 (best
         +0.04, not kept); s8 row pointer / swapped operand order for the 214A0 range (92.03 / no change);
         header retype of 0x1DCE s16 / 0x1DD0 u8 (no codegen change anywhere).
  residual: target's 2nd streak load uses a fresh &g_Minigame (ours reuses r29); case1/case2 add order
         `(r + chargeFrame) + table`; `mr r31,r3` scheduling in the 214A0 lookup.
[O14] mw_version sweep (1.3, 1.3.2r, 2.0, 2.6, 2.7, 3.0a3) on the unit: 1.3.2r-2.7 byte-identical plateau;
      1.3 and 3.0a3 far worse. Not the lever for any residual. configure.py restored.
fn_3_111C5C (99.35 -> 99.90) / Simulation (99.68 -> 99.90)
  [O15] `static inline BOOL bOD_isCurrentRoster(s8 i) { return i == g_Minigame.rosterID; }` in the slot test
        and the first clear loop written directly in bOD_AI (not via bOD_clearAIControlled) -> all register
        numbering now identical. Lesson: an inline-helper boundary changes which &g_Minigame CSE/LICM temp a
        load joins.
  residual: the 4 switch accesses (0x1DD0 x2, 0x1DCC, 0x1DCE) use the LICM temp (r29) instead of the clear
        loop's base (r26). Tried (no change): slot-setup helper (isAIControlled[slot]=1 + memset), switch body
        as helper taking slot, `MiniGameStruct *mg` for the switch accesses, mg for clear loop too (93.18).
fn_3_112450 [O16] rosterID expression as inline helper (with/without turn param): no change.
READABILITY BATCH (all codegen-neutral, verified): fn_3_111AC4 tail -> `fn_3_111A88()` call; TRUE/FALSE for
  pre_PostMiniGameInd/minigameLastTurnSuccessInd/hudLoadingRelated/hudElementLoadingInd/bODControllerInputAllowedInd/
  bOD_KingBombInd/bOD_hitFinishedInd/isAIControlled/starPitchInd (only 0/1 ever stored, tested !=0/==0);
  DEAD_BALL_REASON_HOME_RUN/FOUL_BALL in unusedBODFunction; MINIGAME_DIFFICULTY_MULTIPLAYER_CHALLENGE_HARD in
  CalculatePoints; `INPUT_BUTTON_START | INPUT_BUTTON_A` for the 0x1100 skip mask in fn_3_111F80;
  `lbl_3_bss_B699 = !lbl_3_bss_B699`; PitchTransition loop counter moved to function scope; dropped unused local.
  Left alone: pointsTargetReachedInd (barrel_batter stores 2 -> not boolean), turnOverStatus (0/1/2, no enum),
  changeScene(1|3, 6) (first arg also takes 0xD elsewhere; no matching enum), sound IDs 0x1BD/0x1BE.
bobOmbDerbyBatterAI (92.59 -> 100, MATCHED)
  [O17] the seven AI weight tables declared `s8` instead of u8 + (s8) casts (NOT codegen-neutral: +1.25) -> 93.84
  [O18] streak read inline inside BOTH loops as `g_Minigame.bODCharacterHRStreakTracker[g_Minigame.rosterID][0]`
        (no `streak` local; LICM hoists it with a fresh base exactly like target) -> 99.06
  [O19] add order `RandomInt(...) + g_Batter.frameFullyCharged + chargeFrame` (case 1) and
        `RandomInt(...) + g_Batter.frameChargeDownBegins + chargeFrame` (case 2) -> 100.
  Final shape keeps `MiniGameStruct *mg = &g_Minigame;` for the prologue/epilogue accesses (needed: without it
  the base isn't kept in r29 across the calls, 81.5) and direct g_Minigame inside the loops.
BODScoring further tries (no gain): function-/branch-scope `count` var + helper (99.58); reusing pitchAngle/
  yawAngle as the count var (no change); random-sign inline helper for yaw/pitch (96.64); bODRelated5
  slot-fill loop as inline helper (no change, reverted).
fn_3_111C5C further tries (no gain): `MiniGameStruct *mg` in bOD_AI for clear+charIdx+switch (91.03),
  clear+switch (93.18), charIdx+switch (96.36); switch body as `static` (non-inline) or `static inline` helper
  (no change).
fn_3_112450 -> EXHAUSTED: also tried `MiniGameStruct *mg` for all g_Minigame accesses (91.97). Same residual as
  barrel_batter fn_3_131EC4 (const-1 / &g_Minigame register swap).
bOD_LoadGame [O20] EXPERIMENT (reverted): header _18FC/_1900/minigameFielderIndex/minigamePlayerSelectedOrder -> s8
  plus the 0x18F4 store through an s8 lvalue -> one shared `li -1` like target (s8 hypothesis CONFIRMED), but
  every register in the function shifts by one (95.60 < 98.18). Needs a different loop shape on top of the
  retype; not pursued since the retype touches many TUs.

## Readability pass log (Opus 2026-10-01)
- fn_3_110A38, unused_BODRelated, fn_3_1111D0, fn_3_111250, fn_3_111A88, fn_3_111AC4, fn_3_111F80, fn_3_112070,
  fn_3_1120E0, fn_3_112128, fn_3_1121A4, fn_3_112558, fn_3_1125D0, fn_3_110A04, fn_3_1128E8: readability pass: done
  (TRUE/FALSE batch; fn_3_111AC4 tail now calls fn_3_111A88; fn_3_111F80 skip mask named). Left: changeScene
  args, sound IDs 0x1BD/0x1BE, the 0x78 memset size of the 0x1D7C AI block (no named struct yet),
  starPitchType == 1 in fn_3_110A38 (no enum for star pitch types).
- unusedBODFunction: done (DEAD_BALL_REASON_*). lbl_3_common_bss_32220[8] == 4 left raw (unknown meaning).
- bobOmbDerbyCalculatePoints: done (MINIGAME_DIFFICULTY_*); `miniGameTurnCounter < 0x14` left (no constant).
- bOD_bB_Pitcher_waitingForPitch: done (starPitch kept u8: target truncates with clrlwi.; `_1DF4` meaning unknown).
- bobOmbDerbyPitchTransition: done (loop counter hoisted; s32 is required for codegen, see [O7]).
- fn_3_1128EC: done (count is u8 by evidence; fireworks counts/jitter ranges are plain numbers).
- bobOmbDerbyBatterAI: done (s8 tables; `case 0: default:` kept -- the compare tree needs it).
- Enum-shaped but no enum: turnOverStatus (0 playing / 1 just ended / 2 fading), bODPitchType reuse of
  BARREL_BATTER_PITCH_NUM (KING/STAR semantics shared), pointsTargetReachedInd (0/1 here, 2 in barrel_batter).
- Struct notes: bB_bombBarrelHitInd/bB_bombBarrelID are reused by BOD as yaw/pitch angle storage; the
  0x18CC..0x1903 region model (minigameControlStruct[2]) is probably wrong -- see bOD_LoadGame BLOCKER.

## Handoff (end of Opus session 2026-10-01)
21/26 matched. Remaining: bOD_LoadGame 98.18 (pending, blocked on cross-TU s8 retype of the 0x18F4..0x1904
region), fn_3_111C5C 99.90 / bobOmbDerbySimulation 99.90 / BODScoring 99.87 / fn_3_112450 99.55 (exhausted).
A resumed run should start with bOD_LoadGame only if it is prepared to retype the shared header region
(verify every dependent TU), otherwise the file is done for now.
