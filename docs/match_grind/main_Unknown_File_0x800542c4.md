# main/Unknown/File_0x800542c4

Status: in progress (first pass, partial)

| Function | Size | Before | After | Status |
|---|---|---|---|---|
| fn_800542C4 | 1612 | 0 | 0 | undrafted |
| fn_80054910 | 496 | 0 | 71.75 | pending |
| fn_80054B00 | 2164 | 0 | 0 | undrafted |
| fn_80055374 | 1060 | 0 | 0 | undrafted |
| fn_80055798 | 596 | 0 | 90.57 | pending |
| fn_800559EC | 1844 | 0 | 0 | undrafted |
| newMenuRelated | 2216 | 48.78 | 48.78 | pending |

Unit: 19.79%

## Log
- [S1] drafted fn_80054910 (step flag 8 sequencer, compares selection bytes in gameSettings) -> 71.75%
  next: branch structure near-right; check the sel/other value loads and the expected/result compare ordering.
- [S1] drafted fn_80055798 (starts record playback for menu records) -> 90.57%
  next: likely record-pointer reload/ordering of MENU_REC accesses; g_d_GameSettings._06 accessed via byte offset to keep it as-is.

## Open questions
- The four larger functions are still undrafted; start with fn_80055374 (smallest).
- gameSetUpStep.stepFlags[8] values named SET_UP_STEP_* assumed from game_set_up_step.h usage.
