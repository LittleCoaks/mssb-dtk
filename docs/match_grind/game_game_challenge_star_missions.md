# game/game/challenge/star_missions (src/game/challenge/star_missions.c)

Baseline (session 1 start): unit 96.98%.

| function                                     | status  | pct    |
|----------------------------------------------|---------|--------|
| starMissionsOffensive_StarChange_DoublePlay  | pending | 90.66% |
| starMissionsWholeGame                        | pending | 91.86% |
| shouldScoutMissionBeEnabled                  | pending | 95.48% |
| challenge_postPitchStarMissionTracking       | pending | 96.83% |
| scoutFlag_checkMissionSuccess                | pending | 97.75% |
| starMissionsMinigamesTotalPoints             | pending | 98.26% |
| starMissionsQuantityBased                    | pending | 98.35% |
| awardScoutFlagsSequential                    | pending | 98.94% |
| decideScoutFlagMission                       | pending | 99.44% |
| assignScoutFlagRewardRandom                  | pending | 99.69% |
| starMissionsMinigamesSpecialAction           | pending | 99.94% |
(all others 100%)

## Hypothesis log

shouldScoutMissionBeEnabled
  baseline: 95.48%
  [1] remove the `#pragma dont_inline` wrapper -> decideScoutFlagMission 99.44 -> 0 (it inlines shouldScoutMissionBeEnabled;
      the target calls it 10x). The wrapper is REQUIRED; reverted. Helpers inside it are already inlined in both.
  residual: target saves an unused r28 (ghost saved register) and allocates the inlined fillRosterCharIDs loads off one base.

starMissionsOffensive_StarChange_DoublePlay
  baseline: 90.66%
  [1] drop the `mreq = &req[i]` local in the fielder double-play loop -> load order (trackerIdx before requirementRow) fixed but 89.85 diff view (from 89.99)
  [2] `(mreq = &req[i])->type` inside the condition -> 90.06 (+0.07; rejected for readability)
  residual: IV/register naming in the 9x10 fielder loop (ct-tracker IV vs req IV order).

challenge_postPitchStarMissionTracking
  baseline: 96.83%: register-only (r5..r12/r31 permutation); not attempted.
next: starMissionsWholeGame (91.86, 2712 bytes) not yet examined.
