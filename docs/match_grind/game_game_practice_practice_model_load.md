# practice_model_load checkpoint
| function | status | pct |
|---|---|---|
| practiceModel_setup | exhausted | 93.59% |

practiceModel_setup (target re-loads hugeAnimStruct.files[0..2] after the unrolled store loop; ours forwards the stored values with mr r31/r29/r28 -> 1 insn short)
  baseline: 93.59%
  [1] int i / int i + s32 j -> same
  [2] reads moved before setEffectAnim -> same (scheduled identically)
  [3] *(files + n) reads, *(packed + i) -> same
  [4] store through (u32*) cast / load through (u32*) cast -> same
  [5] loop in a static helper -> 87.70 (still forwarded)
  next: find what blocks MWCC store->load forwarding (volatile-free); maybe a different loop shape or files stored via a pointer walk
