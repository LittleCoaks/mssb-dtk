# main/Unknown/spani_default  [S1]

Baseline (rep_c20): 39.71% .text; 3/26 at 100% (removeGraphicsElementFromScene, unregisterObjectByID, load_Icon);
18 functions unowned (0%). After [S1]: 92.05% .text, .rodata 100%, 11/26 at 100%, all 26 functions drafted.
Pre-existing drafts (addGraphicsElementToScene 94.6, allocateGraphicsSlot 85.4, maybeProcessUIUpdates 84.2,
diskReadRelated 92.9, setIndicatorSlotState 99.0) were not touched.

| function | status | pct |
|---|---|---|
| fn_80034BCC, fn_800356B8, fn_80035B50, fn_80035DD4, fn_80035ED0, fn_80035EEC, fn_80036214, fn_800369DC | matched | 100 |
| removeGraphicsElementFromScene, unregisterObjectByID, load_Icon | matched | 100 |
| fn_80036270 | pending | 99.94 |
| fn_80036824 | pending | 98.55 |
| fn_800362F0 | pending | 94.83 |
| fn_80035A00 | pending | 91.30 |
| fn_80035F20 | pending | 90.89 |
| fn_80036A3C | pending | 88.29 |
| fn_8003664C | pending | 88.08 |
| fn_80035750 | pending | 88.02 |
| fn_80036134 | pending | 86.38 |
| fn_8003656C | pending | 81.16 |
| addGraphicsElementToScene / allocateGraphicsSlot / maybeProcessUIUpdates / diskReadRelated / setIndicatorSlotState | pending (earlier drafts) | 94.6 / 85.4 / 84.2 / 92.9 / 99.0 |

## Findings
- fn_80034BCC: callback registered via fn_8000A094; copies the parent's matrix into the first-child record whose parent element/anchorSub
  match the query ({elementIndex, anchorSub} at +0x6C) and blends the query rgba (+0x68) with the child's, returning 0.
- fn_80035DD4 is the out-of-line `findTextureContainerSlot` (0x360-entry scan); the inline copy is used by 35A00 (unregister ids 2..24),
  35B50 (unregister + fn_800ACFB0 free), 35F20, 3664C, 36824 (these panic with line 0x31C/0x15E/0x12A when the id is not registered).
- fn_80035750: registers a container: first free slot, buffer/textures/layout(=buffer) + tag, convertTextureHeader, fn_8000B9C8.
- fn_80036214 returns the colour word (+0x1C) of a layout frame; 36270 returns its (x,y) s16 pair; 36134 positions record handle2 from it;
  8003656C writes a colour into a part (offset 0x1C) like setIndicatorSlotState writes a texture (offset 6).
- fn_80035F20 / 3664C / 36824 walk the parts of an element from the last to the first: records are 0x50 bytes; the part-number
  comparison happens INSIDE the record loop (loop-invariant; kept as in the target).
- fn_80036A3C: UI renderer setup: frustum, 23-entry render-pass table, fn_800B2854/27A4/0D38, tag table reset, zero pool.
- Constants for the new functions are literals (the older functions use extern lbl_803CC6xx); .sdata2 pool order is unchecked.

## Hypothesis log
[S1] fn_80035750: slot search as `while(1)` with i>=N tail -> 82.8 -> 88.0; target merges slot=-1 into the common extsb.
[S1] fn_8003656C: mirroring setIndicatorSlotState (element/handle*4+8/sub) -> 81.2; inlining handle*4+8 -> 79.9 (reverted).
  next: register order around the layout pointer reload (r31 slot pointer).
[S1] fn_80035A00: loop with inline find; store order (buffer, textures, tag, layout) copied from the asm; 91.3%.
