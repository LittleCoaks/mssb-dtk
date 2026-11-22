# practice_simulation checkpoint
| function | status | pct |
|---|---|---|
| practice_loadCharacter | pending | 92.73% |
| loadPracticeScreen | pending | 96.98% |

practice_loadCharacter
  baseline: 90.93%
  [1] inMemRoster[team][slot] + named fields, no in-place rescale of team/slot -> 92.53 (kept)
  [2] + battingOrderAndPositionMapping[team][0][0] for the captain store -> 92.73 (kept)
  [3] mapping[team][slot + 1][0/1] for the 0x44/0x48 stores -> 88.6; lineup u8* local -> 88.4; Static_Stats_Tables.characterStats source -> same
  remaining: target computes team*0x24 before the lis pair and schedules `cmpwi slot,0` later
