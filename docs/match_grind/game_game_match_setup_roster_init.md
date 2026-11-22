# roster_init checkpoint
| function | status | pct |
|---|---|---|
| setFielderValues | exhausted | 99.64% |

setFielderValues (captain check: target reuses the long-lived g_GameLogic base r30 for Team_CaptainRosterLoc[] and ++rosterLoc_skippingCap; ours rematerialises lis/addi r6 -> +2 insns)
  [1] operand order swapped / (int) cast / subtraction compare -> 99.58 / same / 99.49
  [2] Team_CaptainRosterLoc retyped int in the header -> same (reverted)
  [3] ++ split into two statements -> same; minigame block without the s8 idx local -> 99.58
