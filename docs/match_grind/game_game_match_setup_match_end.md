# match_end checkpoint
| function | status | pct |
|---|---|---|
| startChallengeModeMatch | exhausted | 93.90% |

startChallengeModeMatch (runner-flag blocks: target re-materialises lis/addi g_Runners in each of the three `if (flags & N)` blocks; ours reuses the base from the `rosterID = -1` stores -> 24 bytes short, regs shifted)
  [1] -1 stores as a loop over i or j -> identical code (unrolled)
  [2] the three flag blocks as a loop over j with (1 << (j-1)*4) / shift-and-mask -> 84.5 / 86.5 (not unrolled)
  related: processScoreChanges (match_flow) shows the same "target does not reuse an available global value/address in a later conditional block" pattern
