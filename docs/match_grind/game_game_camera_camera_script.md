# Camera script matching checkpoint

Baseline HEAD 058d3b8; left=target, right=ours.
Sections {'.text': 98.70458, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}

| fn_3_FBD58 | matched | 100.0 |
| fn_3_FBD70 | matched | 100.0 |
| camera_switchScene | matched | 100.0 |
| camera_replay | pending | 99.870964 |
| fn_3_FC2FC | matched | 100.0 |
| fn_3_FC448 | matched | 100.0 |
| fn_3_FC938 | pending | 99.828125 |
| fn_3_FCE38 | pending | 94.13793 |
| fn_3_FCEAC | matched | 100.0 |
| fn_3_FCEB0 | pending | 91.07143 |
| fn_3_FCF20 | matched | 100.0 |
| fn_3_FCF24 | pending | 87.888176 |
| fn_3_FD408 | pending | 98.679245 |
| fn_3_FD4DC | matched | 100.0 |
| fn_3_FD51C | matched | 100.0 |
| fn_3_FD5A8 | matched | 100.0 |
| fn_3_FD670 | pending | 99.86784 |
| fn_3_FD9FC | matched | 100.0 |
| manageDrawingItemState | pending | 98.91304 |
| fn_3_FDB30 | pending | 99.58298 |
| fn_3_100018 | matched | 100.0 |
| fn_3_100038 | matched | 100.0 |
| unkPauseSimulationCheck | matched | 100.0 |
| fn_3_1000D8 | pending | 99.406265 |
| fn_3_101CC4 | pending | 99.462456 |
| camFilterLookAt | matched | 100.0 |
| camFilterAngles | matched | 100.0 |
| camFilterPosition | matched | 100.0 |
| fn_3_104338 | matched | 100.0 |
| fn_3_1045A8 | pending | 99.70588 |
| fn_3_104740 | matched | 100.0 |
| camEvalViewAtTime | matched | 100.0 |
| fn_3_104A3C | matched | 100.0 |
| fn_3_104A88 | matched | 100.0 |
| fn_3_104AD4 | matched | 100.0 |
| fn_3_104B20 | pending | 96.71429 |
| fn_3_104B3C | pending | 97.90523 |
| fn_3_1054CC | matched | 100.0 |
| fn_3_1054D0 | pending | 92.416664 |
| camVecLerp | matched | 100.0 |
| camQuatToMtx | pending | 67.656715 |
| fn_3_105BD8 | matched | 100.0 |
| fn_3_105C28 | pending | 97.608696 |
| camScriptRelocate | matched | 100.0 |
| fn_3_105CDC | matched | 100.0 |
| fn_3_105E00 | pending | 96.353386 |
| fn_3_106014 | matched | 100.0 |
| fn_3_1060D8 | matched | 100.0 |
| fn_3_10617C | pending | 95.409836 |
| fn_3_106270 | pending | 99.50549 |
| camCountTableEntries | matched | 100.0 |
| fn_3_1069B0 | matched | 100.0 |
| camScriptResetState | matched | 100.0 |
| fn_3_106BA0 | matched | 100.0 |
| someAllocFunction | matched | 100.0 |
| loadSomeDataFile | matched | 100.0 |

No preceding camera_script/camera_scene/rep_3090 checkpoint. Git history inspected; preserves prior successful shape changes.

Hypotheses

- 104B20 vector assignment instead of scalar temporary chain: {'fn_3_104B20': (96.71429, 48.57143)}; sections {'.text': 98.67489, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- 104B20 declare reverse scalar order then load xyz: {'fn_3_104B20': (96.71429, 97.42857)}; sections {'.text': 98.705025, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; kept

- 104B20 scalar declaration ('x', 'y', 'z'): {'fn_3_104B20': (97.42857, 96.71429)}; sections {'.text': 98.70458, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- 104B20 scalar declaration ('x', 'z', 'y'): {}; sections {'.text': 98.705025, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- 104B20 scalar declaration ('y', 'x', 'z'): {'fn_3_104B20': (97.42857, 96.71429)}; sections {'.text': 98.70458, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- 104B20 scalar declaration ('y', 'z', 'x'): {'fn_3_104B20': (97.42857, 96.71429)}; sections {'.text': 98.70458, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- 104B20 scalar declaration ('z', 'x', 'y'): {}; sections {'.text': 98.705025, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- 104B20 scalar declaration ('z', 'y', 'x'): {}; sections {'.text': 98.705025, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- 104B20 explicit reverse load order: {'fn_3_104B20': (97.42857, 96.14286)}; sections {'.text': 98.70423, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- 104B20 named vector temporary component copy: {'fn_3_104B20': (97.42857, 96.71429)}; sections {'.text': 98.70458, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- 104B20 direct component copy: {'fn_3_104B20': (97.42857, 41.42857)}; sections {'.text': 98.67049, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- 105C28 move table pointer first and frame later: {'fn_3_FD670': (99.86784, 99.801765), 'fn_3_105C28': (97.608696, 95.21739)}; sections {'.text': 98.69885, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- FCE38 explicit count local: {'fn_3_FCE38': (94.13793, 94.48276)}; sections {'.text': 98.7059, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; kept

- FCEB0 explicit count local: {}; sections {'.text': 98.7059, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- FCEB0 cache count for both comparisons: {'fn_3_FCEB0': (91.07143, 84.46429)}; sections {'.text': 98.689606, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- FCE38 count before context declaration: {'fn_3_FCE38': (94.48276, 94.13793)}; sections {'.text': 98.705025, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- FCE38 distinct array index local: {'fn_3_FCE38': (94.48276, 79.344826)}; sections {'.text': 98.66722, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- FD408 signed array index local: {}; sections {'.text': 98.7059, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- 104B20 inline scalar copy helper: {'fn_3_104B20': (97.42857, 98.28571)}; sections {'.text': 98.70643, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; kept

- 10617C move bone local before actor local: {'fn_3_10617C': (95.409836, 94.83607)}; sections {'.text': 98.70335, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- 104B20 inline argument order ('z', 'y', 'x'): {'fn_3_104B20': (98.28571, 97.42857)}; sections {'.text': 98.7059, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- 104B20 inline argument order ('y', 'z', 'x'): {}; sections {'.text': 98.70643, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- 104B20 inline argument order ('x', 'z', 'y'): {'fn_3_104B20': (98.28571, 97.42857)}; sections {'.text': 98.7059, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- 104B20 inline argument order ('y', 'x', 'z'): {}; sections {'.text': 98.70643, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- 104B20 inline argument order ('z', 'x', 'y'): {'fn_3_104B20': (98.28571, 97.42857)}; sections {'.text': 98.7059, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- fn_3_FCEB0 inline context parameter: {'fn_3_FCEB0': (91.07143, 90.71429)}; sections {'.text': 98.70555, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- fn_3_FCE38 inline context parameter: {'fn_3_FCE38': (94.48276, 94.13793)}; sections {'.text': 98.70555, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- 104B20 double scalar inline parameters: {}; sections {'.text': 98.70643, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- 104B20 double scalar locals: {'fn_3_104B20': (98.28571, 96.71429)}; sections {'.text': 98.70546, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- 104B20 vector-returning getter inline: {'fn_3_104B20': (98.28571, 0.0)}; sections {'.text': 98.64581, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- FD408 inline context parameter: {'fn_3_FD408': (98.679245, 100.0)}; sections {'.text': 98.7126, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; kept
  Newly 100%: fn_3_FD408; source snapshot camera_script_best.c; readability pending.

fn_3_FD408: readability pass done; channel indices 3/4 have no named enum, index/count are numeric. camSampleAt uses true CamScript layout. Final source saved in camera_script_best.c.

- 10617C inline actor parameter: {'fn_3_10617C': (95.409836, 94.83607)}; sections {'.text': 98.70952, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- 105C28 inline keys pointer parameter: {'fn_3_FD670': (99.86784, 99.757706), 'fn_3_105C28': (97.608696, 95.21739)}; sections {'.text': 98.70555, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- 1045A8 sine local before angle locals: {}; sections {'.text': 98.7126, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- camera replay explicit scene temporary for fixed shot: {}; sections {'.text': 98.7126, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- 1045A8 reuse one angle variable: {}; sections {'.text': 98.7126, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- manageDrawingItemState signed full-width actor index: {'manageDrawingItemState': (98.91304, 97.391304)}; sections {'.text': 98.70335, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- 105C28 move last pointer after key counter: {'fn_3_105C28': (97.608696, 96.95652)}; sections {'.text': 98.71128, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- manageDrawingItemState explicit fielder pointer: {'manageDrawingItemState': (98.91304, 100.0)}; sections {'.text': 98.71921, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; kept
  Newly 100%: manageDrawingItemState; source snapshot camera_script_best.c; readability pending.

manageDrawingItemState: readability pass done; _22 is a multi-valued 0/1/2 drawing state, no existing enum, not boolean. Model handle retains its width; final source in camera_script_best.c.

- 104B20 quaternion-size scalar aggregate: {'fn_3_104B20': (98.28571, 96.71429)}; sections {'.text': 98.71824, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- 10617C result pointer alias local: {}; sections {'.text': 98.71921, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted

- camera replay fixed shot context loaded before scene: {'camera_replay': (99.870964, 99.77419)}; sections {'.text': 98.71656, '.rodata': 100.0, '.data': 100.0, '.bss': 100.0}; reverted
