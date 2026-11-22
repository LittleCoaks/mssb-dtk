# menus/menus/text_94854 checkpoint (Opus pass)

Unit fuzzy 84.15 -> ~87.2.

| function    | status  | pct            |
|-------------|---------|----------------|
| fn_2_95604 / 95B28 / 95F3C | matched | -> 100 |
| fn_2_96AD4  | pending | 74.22 -> 92.60 |
| fn_2_94A8C  | pending | 79.31 -> 81.77 |
| fn_2_96698  | pending | 78.99 -> 82.28 |
| fn_2_95E80  | pending | 85.09 -> 90.72 |
| fn_2_9493C  | pending | 83.30 -> 86.45 |
| fn_2_96D20  | pending | 89.41 -> 90.45 |
| fn_2_95FE0 / 96118 / 95B78 / 95654 | pending | 79-98 |

readability pass: stepStateIs helper (gameSetUpStep.stepFlags[13][0] 0/1/2, enum-shaped, no enum).
Quirk kept: fn_2_96AD4 indexes record i + 16 with i left at 3 by the loop (commented).

## Hypothesis log
- stepFlags[13][0] tests: target materialises the bool -> `stepStateIs(k)` ternary helper on the global (+3..+14 on 8 fns).
- fn_2_94A8C: switch on flow->selected read at the switch; the flow pointer set inside the state test (target loads
  lbl_2_bss_1033C after it). Left: (firstHandle + sel) + K not folded (same open question as text_744C8/71EC4).
- fn_2_96AD4: switch(i) for the per-row icons; flag read through the global at the end; record i+16 (i == 3).
  Left: target recomputes i+15/i+21 per call (ours CSEs, one more saved reg); pair helper same, inner part loops worse (85.9).
- fn_2_96D20: menuNumber stores: [0] before [9] in source scores 90.45; no local 89.4. Target stores [9] first.
