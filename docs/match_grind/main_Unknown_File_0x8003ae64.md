# main/Unknown/File_0x8003ae64  [S1] (memory card / save scene)

Baseline (rep_c22 start of session 2): 29.67% .text. After [S1] session 2: 80.50%; every function drafted, all sizes equal to the target
(sceneDrawingLogic is the earlier draft). Switch statements compile their own jump tables; the unit's .data is linked from asm.

| function | status | pct |
|---|---|---|
| fn_8003AE64, fn_8003AE70, fn_8003BF54 | matched | 100 |
| fn_8003E8D8 | pending | 96.89 |
| fn_8004053C | pending | 92.65 |
| fn_8003BB90 | pending | 92.90 |
| fn_8003AECC | pending | 90.87 |
| fn_8003B5B0 | pending | 87.02 |
| startMemoryCardCheck | pending | 86.97 |
| fn_8003F2B8 | pending | 86.56 |
| fn_80040C14 | pending | 84.50 |
| sceneDrawingLogic | pending (earlier draft, untouched) | 67.10 |

next (all): register allocation / minor ordering; the node-spawn blocks (`insertGraphicDrawingFunction` + field copies) and the
repeated three-way `if (flag1D) { if (flag1E) {A} else {A} } else {A}` bodies in fn_8003BB90 reproduce the target's duplicated
branches. startMemoryCardCheck: remaining diff is the order of the byte stores.

readability pass: done for fn_8003AE64/AE70/BF54 (SceneNode fields for the spawner); fn_8003AE70 reads three status bytes of the
save image (lbl_802D4B00 +0x94/+0x95/+0x96) with no known names. Enum-shaped, left alone: SceneNode.step (per-task state machines),
result1C (the scene result code stored into the parent's state: 1 ok, 2 error, 5/7/8/9/0xA/0xB/0xC/0xD values), mcardState.status codes,
fn_8004A34C message ids.

## Findings
- Every memory-card task is the same shape: map mcardState.chan[chan].probeResult to a status (-1 -> 0xF, 0 -> 0x11, -3 -> 0,
  -2 -> 4, else -1; 4/0x11 set flag1E, 0 sets flag1D), then switch (node->step). Children are spawned with
  insertGraphicDrawingFunction(task, 0x8000) copying slot/arg16/chan/flag18/mode1A/mode1B(/idx20/_21); a child reports through
  currentDrawingItem->state and the final step writes result1C into parent->state, frees text blocks and removes itself.
- Task chain: fn_8003F2B8 (top: probe, load, save-check, banner, delete, copy flows) spawns fn_8004053C (file check) which spawns
  fn_8003BB90 (format); fn_8003AECC / fn_8003E8D8 are the load/save variants and spawn 8004053C and 80040C14 (load); 8003B5B0 saves
  (mcardCheckSpace + processBannerImage + memoryCardRelatedFunction); fn_8003F2B8 also builds the save image in lbl_802D4B00.
- EABI detail: mcardLoad / mcardCheckFile / mcardDelete are called with the u64 serial in r5:r6/r7:r8 (r4 or r6 skipped), so they
  are prototyped here without the extra int that memoryCardRelatedFunction has.
