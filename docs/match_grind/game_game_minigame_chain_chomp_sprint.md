# game/game/minigame/chain_chomp_sprint -- match checkpoint

Session 1 (Opus `match`, 2026-10-02). File started as 34 `return;` stubs, no
checkpoint. Baseline: .text 0.644%, .rodata 55.556%, .data 0%, .bss 0%.
Baseline report for regression checks:
scratchpad/baseline_report_main_4cfe045.json (upstream main 4cfe045).

## Phase 1: MiniGameStruct survey and layout decisions

Survey method: heuristic register-tracking scan of every `g_Minigame` access
in all 68 asm files that reference it (offset, opcode width, function,
stride loops). Cross-checked against Ghidra (its `minigameStruct` type is
mostly `fieldN_0xXXXX` placeholders, so it added little).

All offsets verified with a compile-time `offsetof` checker (MWCC, negative
array size on mismatch) -- every anchor below holds, sizeof stays 0x1E2C.
Full rebuild after the change: `4 files OK`, report.json identical to the
baseline (0 drops, 0 ups, 0 missing) -> the change is codegen-neutral.

| offset | old decl | new decl | evidence |
|---|---|---|---|
| 0xCB0..0xCCF | `_CB0.._CC8 f32, _CCC s16, _CCE u8[2]` | `MinigamePowerupStruct powerup` (pos VecXYZ, _0C VecXYZ, basePathPos f32, timer s16, activeInd u8, pad) | CCS `fn_3_13E670` and star_dash pass `&g_Minigame+0xCB0` as a struct pointer to helpers; widths lfs/lha/lbz consistent in star_dash, pitching_machine, CCS. +0x18 compared with runner `fractionalBasesRan` (CCS only). `memset(p+0xC,0,0xC)` after placing. Pickup sets `playerIDWithPowerup[0]` -> "powerup". |
| 0xCD0 | `VecXYZ wallBall_coinCoordinates` + pads/_CE0/_D84 | union { wall-ball scalar; `VecXYZ coinPos[100]` } | stride-12 loops 0..99 (wall_ball, init), CCS indices 0..14 (track gems) and 15..34 (dropped coins); 100*12 == gap to 0x1180 |
| 0x1180 | `VecXYZ wallBall_coinVelocity` + pads/_1234 | union { wall-ball scalar; `VecXYZ coinVelocity[100]` } | same; gap to 0x1630 == 1200 |
| 0x1630 | `f32 _1630` + pad10 | `f32 coinBasePathPos[100]` | CCS stride-4 loops over 15 gems compare it to `fractionalBasesRan`; 400 == gap to 0x17C0 |
| 0x17C8 | `s16 wallBall_coinsVisibleFrameCounter` + `_17CA.._1806` + pad11 | union { wall-ball scalar; `s16 coinFrameCounter[100]` } | init clears [0..99] in a 16x-unrolled loop (sth stride 2), CCS increments [15..34] |
| 0x193A | `u8 wallBall_coinsVisibleInd` + `_193B.._1999` + pad13 | union { wall-ball scalar; `u8 coinState[100]` } | init clears [0..99]; CCS gems store type 1..6 (+100 once collected) |
| 0x18CC..0x18F7 | `MiniGameControlStruct minigameControlStruct[2]` (0x16 stride) | union { legacy; `MinigamePlayerSlots playerSlots` } | every unit indexes this as 11 `[4]` byte arrays (0x18CC,D0,D4,D8,DC,E0,E4,E8,EC,F0,F4); 0x16 stride never appears. 0x18D8 = AI-controlled (batter.c `aiControlledInd = ...[rosterID]`, CCS runs AI only when nonzero); 0x18DC = AI strength (CCS indexes AI tables with it). |
| 0x1AE0..0x1B33 | flat `_1AE0.._1B33` (0x1AFE declared u8[2]) | `ChainChompSprintStruct ccs` | users: CCS, sta_c2 / wario_palace / rep_3880 (chomp pos+yaw+state for the Wario Palace chomp actor), runner.c (velocity, per-player hit state), hud rep_3448. 0x1AFE is s16[4] (lha/sth, unrolled loop over 0x1900[4]); 0x1B08 s16[6] paired with 0x1B1A u8[6]; 0x1B20 u8[6] searched as values; 0x1B26 s8[4][2] (-1 init, nested 4x2 loop). No other minigame touches this range. |
| 0x1DCC..0x1DEB | wall-ball AI scalars | union { legacy wall-ball/bobomb fields (verbatim); `ChainChompSprintAI ccsAI[4]` } | CCS walks 0x1DCC with stride 8 for 4 ports (fn_3_13DEA4, fn_3_1412BC, AI loop); fields +0 lha/sth, +2 state (14-entry jump table), +3/+5 u8, +4/+6/+7 bytes used signed. star_dash uses 0x1DCC as f32, so this is genuinely per-minigame reuse. |
| 0x1DF6.. | `u8 _1DF6[0x36]` | `_1DF6[10]; u8 _1E00; _1E01[...]` | CCS fn_3_140284 sets 0x1E00=1; hud rep_3448 lbz/stb it. bobomb_derby only uses _1DF6[0..2]. |

Wall-ball names were left untouched (memory note: collaborator owns
wall_ball.c and its fields) -- they now sit inside anonymous unions with the
real arrays, same name/type/offset.

Other files touched (renames only, codegen verified identical):
sta_c2.c, runner.c, animation_dispatch.c, minigame_fielder_anim.c
(`_1AE0..` -> `ccs.chompPos` etc).

Enum-shaped but left as literals (no enum exists, values not fully known):
- `ccs.chompState` (0 idle, 1, 2, 3 = lunge at target set by fn_3_140284)
- `ccs.runnerChompHitState[4]` (0 normal, 1 knocked away, 2 waiting, 3 recovering/blinking, 4 skip) -- from runner.c
- `ccsAI[i].state` (0..13, jump table)
- `ccs.itemState[6]` (2, 3, 4 used by AI)
- Fields at 0x18A2/0x18A4 (`bB_bombBarrelHitInd_bOD_hrYaw`, `bB_bombBarrelID_bOD_hrPitch`) are CCS timers (random*60) but only written here; left with their combined names.

## Status table

| function                  | status  | baseline | pct (draft 1) |
|---------------------------|---------|----------|-----|
| fn_3_13C790 (new, was auto split) | pending | n/a | 54.55 |
| fn_3_13C7BC               | pending | 0.11 | 86.39 |
| fn_3_13D578               | pending | 3.57 | 86.57 |
| fn_3_13D5E8               | pending | 8.33 | 80.75 |
| fn_3_13D618               | pending | 0.39 | 92.00 |
| fn_3_13DA20               | pending | 8.33 | 80.75 |
| fn_3_13DA50               | pending | 0.79 | 99.01 |
| fn_3_13DC48               | pending | 0.98 | 91.37 |
| fn_3_13DDE0               | matched | 2.04 | 100 |
| fn_3_13DEA4               | pending | 1.43 | 84.64 |
| fn_3_13DFBC               | matched | 0.91 | 100 |
| fn_3_13E174               | pending | 2.38 | 97.62 |
| fn_3_13E21C               | pending | 1.02 | 92.12 |
| fn_3_13E3A4               | pending | 0.56 | 98.10 |
| fn_3_13E670               | pending | 4.00 | 99.96 |
| fn_3_13E6D4               | matched | 1.56 | 100 |
| fn_3_13E7D4               | pending | 0.66 | 75.63 |
| chainChompSpringPoints    | pending | 0.75 | 89.95 |
| fn_3_13EC44               | pending | 0.19 | 87.95 |
| fn_3_13F484               | pending | 0.69 | 95.24 |
| fn_3_13F6C8               | pending | 1.41 | 99.44 |
| fn_3_13F7E4               | pending | 1.79 | 96.07 |
| fn_3_13F8C4               | pending | 0.46 | 66.08 |
| fn_3_13FC24               | pending | 0.25 | 82.95 |
| fn_3_140284               | pending | 0.78 | 91.58 |
| fn_3_140484               | pending | 1.18 | 99.41 |
| fn_3_1405D8               | pending | 1.41 | 91.11 |
| fn_3_1406F4               | pending | 0.58 | 96.09 |
| fn_3_1409AC               | pending | 0.74 | 89.69 |
| fn_3_140BCC               | pending | 1.45 | 98.59 |
| chainChompSpringMainFun   | pending | 0.38 | 90.60 |
| mVPRelated                | pending | 0.87 | 87.86 |
| fn_3_1412BC               | pending | 1.35 | 87.43 |
| fn_3_1413E4               | matched | 2.00 | 100 |
| chainChompSprintRelated   | pending | 0.28 | 89.81 |
| fn_3_141A2C (new)         | matched | n/a | 100 |
| chainChompSprintSwitcher (new) | pending | n/a | 92.89 |

Sections after draft 1: .text 89.21, .rodata 94.23, .data 2.38, .bss 57.14.

Split change: `.text` extended from 0x13C7BC..0x141A2C to 0x13C790..0x141C44
(absorbs auto splits fn_3_13C790, fn_3_141A2C, chainChompSprintSwitcher;
the switcher's jump table jumptable_3_data_2662C is in this unit's .data, and
fn_3_13C790's body is inlined at the head of fn_3_13C7BC). Report shows the two
old auto units as "missing" -- expected.

Further header changes during drafting (all re-verified neutral):
- 0x17C0/0x17C4 renamed `minigameElapsedFrames` / `minigameFramesRemaining`, s32 -> u32
  (CCS compares them with cmplwi; frame counter +1/frame, 1800/3600 thresholds;
  time limit = difficulty table * 60, countdown beeps every 60 below 600).
  barrel_batter.c / bobomb_derby.c updated (only `= 0` stores).
- 0x18A2 union { BB/BOD scalars; `s16 ccsSpecialItemFrames[2]` } -- CCS indexes it
  with `ccs.specialItemCount` (lha 0x18A2 + idx*2) and compares with elapsed frames.
- ccs.segmentItems[4][2] (was heldItem): item ids placed on each base path
  (pos/10 picks the segment); ccs._4E -> specialItemCount (<2, ++ per special item).
- 0x1E02 split out of the tail (`_1E02[2]`, indexed by player 0..3 past its bound:
  0x1E04 is a word for other modes).
- ChainChompSprintAI._3 is s8 (decremented with extsb. test).

## Hypothesis log

### Session 1 grind log

fn_3_13C790 / fn_3_13D578
  baseline (draft): 54.55% / 86.57%
  [1] `for` -> `i = 0; do { } while (++i < 4)` (target has no loop-entry branch, not unrolled) -> 100% / 100% (kept). Also lifted SpringMainFun 90.6 -> 96.1 and the AI fn.

fn_3_13D5E8 / fn_3_13DA20 (sort comparators)
  baseline: 80.75%
  [1] body rewrites (temps, explicit int, operand order) -> no change
  [2] params typed `f32*` instead of `const void*` (Ghidra's signature), cast at the fn_800246D4 call -> 99.17% (kept; only a rodata reloc label left)

fn_3_13E7D4 (drop coins on chomp hit)
  baseline: 75.63%
  [1] runner pointer computed once at top; `if (!PSVECMag(&dir))` -> 89.83%
  [2] sin/cos into temps, re-evaluated per line in target call order (`s=SINF;c=COSF;` line 1, `c=COSF;s=SINF;` line 2); vy stored via local after vx -> 99.57% (kept)
  [3] `angle = 45.0*(2.0*(rand/32767 - 0.5)); angle *= 0.017453292f;` (deg2rad last in pool) -> 99.83%, .rodata 94.2 -> 98.1 (kept)
  [4] `angle = angle * lit` / `lit * angle` / lit inside each SINF/COSF -> 99.70 (fmuls operand order fixed but angle f30<->f31 swap); declaration-order sweeps (6 orders) and function-scope float locals: no effect. Left at [3].

fn_3_13DEA4 (AI init)
  baseline: 84.64%
  [1] do-while -> 97.21%; its inlined copies in fn_3_1412BC and chainChompSprintSwitcher -> 100% (kept)
  [2] index form `ccsAI[i].x`, ai assigned after memset, block-local `&ccsAI[i]`, separate aiBase/ai vars, `MiniGameStruct* mg` -> all worse (88-93%), reverted.
  Residual: target standalone has `addi r25,0x1dcc` before memset then `mr r31,r25` (extra copy) and r30/r31, r26/r28 swaps; the inlined copies match exactly.

mVPRelated / fn_3_1409AC / chainChompSprintRelated (shared chomp + item reset block)
  baseline (draft): 87.86 / 89.69 / 89.81
  [1] chomp home position copied per component (target lfs/stfs, not word copy); `chompYaw = 0` first -> part of fix
  [2] static inline helper for the coin/item reset -> mVPRelated and fn_3_1409AC got auto-inlined into their callers (target keeps `bl`); reverted
  [3] coin-clear loop counter `u32` in mVPRelated/1409AC (target cmplwi 0x64) -> 100% / 99.96% (kept)
  [4] init: invert `if (_125 != 0) return` to `if (_125 == 0) {...} else SetGameStatus(5)`; drop `order[i] = 0`; `lbl_3_data_21860[4][order[i]]` (u8[5][4]); `s32 k` for the coin loop (target has the vestigial `cmpwi r7,0x64; bge` guard) -> 95.36
  [5] -1 stores: target stores -1 from ONE register into 0x18F4/0x18F8/0x18FC/0x1900/0x1904 -> those fields are s8. Added s8 views to MinigamePlayerSlots (fielderIndex, runnerPlayerIndex, playerRunnerIndex) -> 97.28.
      Retyping `minigamePlayerSelectedOrder` (0x1904) to s8 in the header: bobomb_derby bOD_LoadGame 98.18 -> 97.52 (its source still writes the u8 views, so it splits into -1/0xff registers). Converting BOD's loop to the s8 views made it structurally identical to its target but reg-renumbered (95.6). Reverted both; CCS writes `*(s8*)&...minigamePlayerSelectedOrder = -1` (barrel_batter's existing precedent). NOTE for a future BOD pass: 0x18F4..0x1904 are s8 there too.
  [6] swap `i`/`runnerIdx` declaration order -> 97.47 (kept)
  [7] `MiniGameStruct* mg` local for the runner/810C4/coin loops (several scopes) -> 85-89, reverted. Residual: target keeps &g_Minigame in r24 from the runner loop to the coin loop (copies via mr into the 810C4 loops); B791=0 shares the coin counter's `li r7,0`.

fn_3_13F8C4 (chomp returns home)
  baseline: 66.08%
  [1] `chompStateTimer <= 1` (target cmpwi 1/bgt), and both float tests written with the TARGET's fallthrough first: `if (dist <= home) {reset} else {move; if (y <= 0) {land} else {fall}}` -> 100% (kept). Same `<= 1` / `<= HARD` fix took fn_3_1409AC to 100.

fn_3_1405D8: `u8 row`; `_26 *= 120; _26 -= 48;` as two statements -> 100%.
fn_3_13E174 / 140484 / 1406F4: store `B798 = (int)tbl[12]` before `B794 = tbl[14]` -> all 100%.

fn_3_13FC24 (chomp chase / hit)
  baseline: 83.21%
  [1] rewrite from asm: `_1C < 1`, `++_1C <= 1`, runner ptr locals, pos x/y/z update order, land-first branch, bark is `if (vy > 0 && new <= 0) callSfx(0x2DE)` (not 0x2E1), `--targetCount == 0`, hit flag at 0x1DFC (not 0x1E02; header tail re-split) -> 95.35
  [2] `if (!(dist < r0)) return;` (target plain bge), playerIDWithPowerup -> s8 (header; li -1), ccs._34 -> `s8 chasedPlayer` -> 99.63
  [3] dx computed before dz (register numbering follows reverse statement order here) -> 99.73
  [4] fabs block: inline-expression forms, split ifs, `__fabsf`, named f64 limit -> no gain / worse; `fabsf()` (the math.h inline wrapper) -> 100% (kept)

chainChompSpringPoints / fn_3_13E21C (runner-in-range candidate lists)
  baseline: 89.95 / 92.12
  [1] write candidates through a pointer (`*next++ = i; count++;`, target `stw; addi r6,4`) -> 94.02 / 88.62
  [2] 13E21C: pickup range read into a local before the loop (target hoists `lfs f3,0x2c`) -> 97.35 (kept)
  [3] shared circular-gap code factored into `static inline ccsBasePathGap()` -> identical code, kept for readability
  [4] declaration-order permutations (120 each, block scope) -> no effect; function-scope locals, no `state` local, `int state` -> no gain / worse
  Residual (both): register numbering of the loop setup (target materialises the table/coin pointers in a different order).

fn_3_140284 (pick the chomp's target)
  baseline: 91.58%
  [1] in the max loop assign `best` before `target` -> 97.83
  [2] init order: `_1E00=1; targetInd[]; best = 0; target = -1; targetCount = 0;` (best/target set before the threshold lookup) -> 99.91; decl initialisers instead -> 71 (bad)
  [3] `targetInd[i] = -1` as a `for` loop (MWCC unrolls it; fixes the li 0 / li 0xff order) -> 100%

fn_3_13EC44 (place an item's gems on a base path)
  baseline (draft): 87.95%
  [1] the four "if (seg[k]==0) list[count++]=k" blocks as `for` loops (MWCC unrolls) -> 93.07
  [2] `runner->nextBase & 3` (target clrlslwi; `% 4` on the promoted int emits signed-mod code) -> 94.25
  [3] state-4 branch writes the list through a pointer (`next = list; *next++ = i; count++`) -> 95.44
  [4] gem position sum written `rand + 2 + seg * 10` (target add r3+r0 then +2) -> 96.19; other associations 96.15 / no change
  [5] `*state` -> direct `itemState[item]` -> identical code
  [6] plain-gem count read into a local before the retry loop (`baseCount`; target keeps it in r0 across the loop-back) -> 97.26
  [7] hill-climbed declaration order (gem/gemCount swap) -> 97.66 (kept)
  [8] `count = 0` re-set at the start of each list build -> 97.59; moving the loop-top `count = 0` into the non-special branch -> 96.16; both reverted
  Residual: callee-saved register numbering (g_Minigame CSE base r31 vs r25, item r28 vs r29, gemCount r29 vs r31) and runner-loop temps shifted by one.

fn_3_13DC48 / fn_3_13DA50 / fn_3_13D618 (base-path distance helpers)
  baseline: 91.37 / 99.01 / 92.00
  [1] 13DC48: no `runner` local -- `g_Runners[runnerIdx].field` each time (target CSEs the field ADDRESS: lfsu/lbzu) -> 100
  [2] 13DA50: written as a call to fn_3_13DC48(&forward, &backward) (auto-inlined; identical to the no-local form) -> 100; also lifted the AI fn
  [3] 13D618: inner loop calls fn_3_13DC48 too -> 92.74; do-while + `count = 0` after the 13DA50 call (count not live across the call) -> 99.17; min as `forward < backward ? forward : backward` -> 100
  [4] variants of fn_3_13DDE0 writing the result into `to` (93.9, worse) or a `dist` local (identical) -- reverted / no change.

fn_3_13C7BC (AI)
  baseline (draft): 86.39%
  [1] every loop as `x = 0; do { } while (++x < N)` (target has no loop-entry branches); sparse switch on item state with case bodies in physical order 4, 3, 2 -> 96.73
  [2] inputs accessed as `g_Minigame._1D7C[c].field` (no InputStruct* local) -> 96.91
  [3] AI array base hoisted into a top-level local `ais = g_Minigame.ccsAI` (target computes `addi r0,r23,0x1dcc` in the prologue), `ai = &ais[i]` per player -> 98.60 (a running `ai++` pointer gave 98.19)
  [4] hill-climbed top-level declaration order (`i` first, `direction` last) -> 98.93
  [5] in the player loop declare `ai` before `runner` -> 99.40; coin/item check written as `100.0f * (0.001f + coinBasePathPos[c])` inline (no `pos` temp) -> 99.47 and .rodata -> 100%
  [6] 13DA50 fix above -> 99.63

fn_3_13F484 (item state update)
  baseline: 95.24%
  [1] `itemTimer[item]--; if (itemTimer[item] <= 0)` as two statements (target reloads after the store) -> part
  [2] `int collectedState = item + 101` local computed once and reused by both scans (target keeps it in r6) -> 98.97; declared before `collected` -> 99.76
  [3] `u8 state` declared at function scope (between item and i) -> 100%

fn_3_13F6C8: body as `if (turnOver) return; 13F484(); SpringPoints(); fn_3_13E6D4();` (call, auto-inlined) -> 100% (the hand-copied loop gave 99.44).

fn_3_140BCC: time-up whistle is `sndFXStartEx(0x1BE, lbl_800EFBA4[7], 0x3F, 0)` (ID immediate, volume table entry) and plain `CountdownUntilFade <= 0` -> 100%.

chainChompSpringMainFun
  baseline (draft): 90.60%; now 97.50 after the callee fixes.
  [1] clear loop written inline instead of the fn_3_13C790 call -> 96.19 (loses the inlined `mr r3,r4` zero copy); inline copy of fn_3_13F7E4's body -> 97.61; both inline -> 96.31. Reverted to calls.
  Residual: target CSEs &g_Minigame from the inlined clear loop (r7) into the inlined 13F7E4 runner loop; ours rematerialises it.
