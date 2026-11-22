# main/Unknown/File_0x8003ae64  [S1] (memory card / save scene) -- PARTIAL

Baseline 28.08% .text (sceneDrawingLogic 67.1% pre-existing draft, 0/12 at 100%). After [S1]: 29.67%; four small functions drafted
(fn_8003AE64, fn_8003AE70, fn_8003BF54 at 100%, startMemoryCardCheck 87.0%). Not drafted (link from asm): fn_8003AECC (1764),
fn_8003B5B0 (1504), fn_8003BB90 (964), fn_8003E8D8 (2404), fn_8003F2B8 (4740), fn_8004053C (1752), fn_80040C14 (972).

| function | status | pct |
|---|---|---|
| fn_8003AE64, fn_8003AE70, fn_8003BF54 | matched | 100 |
| startMemoryCardCheck | pending | 86.97 |
| sceneDrawingLogic | pending (earlier draft, untouched) | 67.10 |
| fn_8003AECC, fn_8003B5B0, fn_8003BB90, fn_8003E8D8, fn_8003F2B8, fn_8004053C, fn_80040C14 | pending (not drafted) | 0 |

## Findings
- fn_8003BF54(a..i) spawns the memory-card scene task (sceneDrawingLogic, priority 0x8000) with its 9 byte parameters at item+0x15..0x21
  and clears lbl_802D4AE0[c]; startMemoryCardCheck spawns fn_8003F2B8 the same way (item+0x1B = 7) and clears lbl_802D4AE0[0..3].
- fn_8003AE64 is the ARQ completion callback (clears lbl_803CBCB8); fn_8003AE70(which) reads one of three status bytes of lbl_802D4B00.
- startMemoryCardCheck: remaining diff is store order of the byte stores.
readability pass: pending (item byte offsets 0x14-0x21 need a SceneMcardTask struct).
