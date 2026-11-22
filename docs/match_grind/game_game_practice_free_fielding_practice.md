# free_fielding_practice checkpoint
| function | status | pct |
|---|---|---|
| freeFieldingPracticeSwitcher | exhausted | 95.37% |

freeFieldingPracticeSwitcher (case 3: target keeps team in r8, `mulli team,0x50` scheduled after the currentBatterPerTeam load; ours computes it early in r4. Jumptable is name-only)
  baseline: 95.37%
  [1] no locals (full expression) -> 94.95; batter local dropped -> same
  [2] s32/u32 locals -> same
  [3] static inline helpers (batter slot, rosterCharID(team,slot), currentBatterCharID(team), (void)) -> all same
  [4] teamBatting local first, slot local, charID local -> same (expression canonicalized)
  next: field types in GameLogic (int vs s32) would be a header-wide change; untested
