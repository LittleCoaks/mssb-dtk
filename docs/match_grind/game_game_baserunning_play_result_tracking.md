# play_result_tracking

storedInningInfo is typed as StoredInningInfo (0x8C, layout from Ghidra's storedGameInfoStruct in .ghidra_cache/in_game.types.txt).
Static_Stats_Tables was split in config/GYQE01/symbols.txt: every reference past 0x4C28 is to exactly +0x4C28/+0x4E44/+0x50F0,
so PitcherStats_P1_P2, BatterStats_P1_P2 and StatsScreenScores are now their own symbols (no other implemented source touched that range).

| function                                                  | status    | pct    |
|-----------------------------------------------------------|-----------|--------|
| fn_3_79338                                                | matched   | 100%   |
| runnerResultCd_bunt                                       | exhausted | 99.36% |
| adjustTotalBasesOnHit                                     | matched   | 100%   |
| pickoff_infieldThrow_related                              | exhausted | 99.05% |
| initialize_runnersBeingTargetedWhileBatterCanBeForcedOut  | matched   | 100%   |
| monitorForErrors                                          | matched   | 100%   |
| update_runnersBeingTargetedWhileBatterCanBeForcedOut      | pending   | 99.12% |
| postPlayTrackStats                                        | pending   | 90.38% |

## Hypothesis log

fn_3_79338
  baseline: 98.09%
  [1] split `storedOuts == 2 || outs >= 3` into two early-return ifs  -> 100% (kept)

runnerResultCd_bunt
  baseline: 91.59%
  [1] loop reads runner[1].field off a g_Runners base pointer  -> 95.77% (kept)
  [2] runner = &g_Runners[1] set before the forced count  -> 98.36% (kept)
  [3] forced count as `for (i = 0; i < 3; i++) if (runner[i].forceOutCd != 0) nForced++`  -> 99.36% (kept)
  [4] declaration order (runner last / middle / i first / nForced first)  -> 98.81-99.36% (reverted)
  [5] main loop as i-up / while(i--)  -> 99.36% (no change)
  [6] advanced = 0 after the count setup  -> 99.26% (reverted)
  left: runner pointer and status byte in r5/r6 swapped.

adjustTotalBasesOnHit
  baseline: 99.12%
  [1] `base` local int instead of u8 (u8 adds a clrlwi after currentBase - 1)  -> 100% (kept)
  notes: byte 0x23 is s8 tentativeBatterBase; `*= -1` gives the mulli -1.

pickoff_infieldThrow_related
  baseline: 98.00%
  [1] g_FieldingLogic.x127_pickoff_0 retyped s8 (target stores li -1)  -> part of [2]
  [2] rest of body wrapped in `if (target <= 3) {...}`  -> 99.05% (kept)
  [3] `locationThrownTo >= 0 && target <= 3` wrap  -> 99.05% (no change)
  [4] `target >= 0 && target <= 3` wrap  -> 98.02% (reverted)
  [5] `else if (target <= 3)`  -> 99.05% (no change)
  [6] `if (late)` moved outside the range block  -> 94.91% (reverted)
  left: target emits `cmpwi 3; ble; blr` for the >3 exit, ours `bgtlr`.

initialize_runnersBeingTargetedWhileBatterCanBeForcedOut
  baseline: 100% on first write. Targets encoded as runner digits (123, 23, 13, ...); 5 = not thrown to a base.

monitorForErrors
  baseline: 95.76%
  [1] index g_Runners[processErrorCode - 3] directly each time, no pointer  -> 99.56% (kept)
  [2] steal tail `if (x >= idx + 2) { set; return; } return;`  -> 100% (kept)

update_runnersBeingTargetedWhileBatterCanBeForcedOut
  baseline: 94.90%
  [1] `targeted` declared before the flag  -> 95.66%
  [2] forced-runner loop over i = 1..3 indexing runnerForcedCd[i - 1]  -> 96.24%
  [3] `% 10` computed inside the second out check (`g_Runners[lo = targeted % 10]`)  -> 96.76%
  [1]+[2]+[3]  -> 98.85% (kept)
  [4] status bytes assigned in the out checks and reused (hundreds + tens branches)  -> 99.12% (kept)
  [5] nested-if form of the tens branch  -> compile error (C89 decl order), not pursued
  left: one extra `b` in the >= 100 chain; scratch-register differences.

postPlayTrackStats
  baseline: 89.51% (first write)
  [1] split Static_Stats_Tables into PitcherStats_P1_P2 / BatterStats_P1_P2 / StatsScreenScores symbols  -> 90.38% (kept)
  [2] saturating increments through an inline `incrementStat(u8*)` helper  -> 90.38% (no change)
  [3] `*stat += 1` / `*stat = *stat + 1` / `stat[0]++`  -> 90.38% (no change)
  [4] replace `goto updatePositions` with a pickoffPlay flag (set TRUE in the pickoff branch)  -> 89.90% (reverted)
  [5] same flag defaulting TRUE, cleared on the non-pickoff paths  -> 89.20% (reverted)
      => goto kept: the target reaches the shared stats tail with one jump from the pickoff branch
         (Ghidra shows the same label), and both structured forms add a flag test.
  left (next ideas):
    - target bumps every stat with `lbzu off(ptr)` then reloads `lbz 0(ptr)`; ours computes the pointer and loads
      with a displacement. Not the increment spelling or an inline helper - try the stat pointer built as
      `(u8*)&BatterStats_P1_P2[t][r] + offsetof(...)`, or a StatisticsBatter* row pointer.
    - result-history shift: target interleaves each load/store (lbz 0x39 -> stb 0x3a, ...); ours batches the loads.
      Try separate named u8 fields instead of atBatResultHistory[5], or a descending loop.
    - score-copy prologue: target loads scores total before the byInning copy and keeps the steals byte for the
      later `< 0xFE` test (ours reloads).
    - `g_Scores.Inning` via lwzu in the hits bump; `base` extsb placement.

## Open naming questions
- runnersTargetedWhileBatterForceable == 4 (update_... sets it when the targeted runner is safe and the batter is safe
  and unforced; postPlayTrackStats then records a fielder's-choice error). Ghidra has no name for 4.
- liveBallBcOfPickoffOrStealCd values 3 and 4 have no enumerators yet (runner.c tests 3/4; this file skips 4).
