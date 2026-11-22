# offence_animation checkpoint
| function | status | pct |
|---|---|---|
| animateOffence | exhausted | 99.42% |

animateOffence (main loop: i and runnerObj swapped, r23/r24)
  baseline: 99.42%
  [1] reuse function-scope obj for runnerObj; runnerObj at function scope in each decl position; i/obj decl order -> no change
  [2] s32 i -> no change
  [3] runnerObj assigned after runner -> 99.06
  [4] !i instead of i == 0 -> no change
  [5] the three hide loops as static inline helper (with/without reset+AnimBlr) -> 98.66 (helper loop unrolls with a different base reg)
  [6] g_Runners[i].field instead of runner pointer; drop s8 animation local -> no change
