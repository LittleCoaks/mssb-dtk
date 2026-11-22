# minigame_fielder_anim checkpoint
| function | status | pct |
|---|---|---|
| minigameUpdateResultsScene | exhausted | 99.66% |

minigameUpdateResultsScene (best-score loop: out pointer r7 vs r5 and i value swapped; later lbz 0x1906 r19 vs r18)
  [1] values[count++] = i indexing -> 98.27
  [2] count++ before *out++ ; for (out = values, i = 0 ...) -> same
  [3] out at function scope (every decl position, shared by both loops) -> 99.56
  [4] s32 for i/k/participants/count -> same
