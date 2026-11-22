# menus/menus/text_00110 checkpoint (Opus pass)

Unit fuzzy 86.72 -> 94.61.

| function                 | status    | pct            |
|--------------------------|-----------|----------------|
| fn_2_374                 | matched   | 70.63 -> 100   |
| fn_2_4C4 / fn_2_510      | matched   | -> 100         |
| fn_2_328 / bPressOnStadSelectScreen | matched | 93.42 -> 100 |
| fn_2_1A8                 | exhausted | 83.62 -> 99.61 |
| fn_2_794                 | pending   | 82.46 -> 85.70 |
| fn_2_978                 | pending   | 60.77          |
| fn_2_664                 | pending   | 97.51          |
| fn_2_554                 | pending   | 99.12          |

readability pass: done for the matched ones (cursor-queue helpers called by name).

## Hypothesis log
- fn_2_374 / fn_2_328 / bPressOnStadSelectScreen / fn_2_794 were hand copies of fn_2_510 / fn_2_4C4 / fn_2_A14 / fn_2_978:
  plain calls (MWCC inlines them). fn_2_374 needs a `u8 *` node so the inlined queue read keeps add + 0x17 displacement;
  case 1 falls into case 2 when the dequeued value is 2.
- fn_2_510/4C4: `(obj + obj[0x16])[0x17]` displacement form -> 100.
- fn_2_1A8: switch on mode -> 99.6; left: lis order of AtBat in the mode-2 load (index form variants no change).
- fn_2_794: menuControlVariables re-read at every use (no ctl local) -> 85.7.
- fn_2_978 (and its inlined copy in 794): target dispatches through a 10-entry jump table (cases 2-6, 8 -> end);
  ours builds a compare tree. Tried: no default, separate empty cases, u32/s32/u16 switch variable -> no change.
  Unknown what makes MWCC pick the table here.
