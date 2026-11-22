# main/Unknown/File_0x8000a0ac  [S1]

Baseline 4.23% (rep_c20), fn_8000A0AC/A3EC/AF1C unowned (0%), interpolatePointsBezier_Vec2s 52.69%.
After [S1]: .text 87.17%, .sdata2 100%, extab 96.9%. All 4 functions drafted; none at 100%.

| function | status | pct |
|---|---|---|
| fn_8000A0AC | pending | 99.37 |
| interpolatePointsBezier_Vec2s | pending | 52.69 |
| fn_8000A3EC | pending | 88.31 |
| fn_8000AF1C | pending | 91.08 |

## Findings
- fn_8000A0AC(out, t, a, b): cubic Bezier between two keyframe records; control points are a[0x14,0x16], a+0x34 [2,3], b+0x34 [0,1], b[0x14,0x16] as s16.
  Both arms of the `a[4]==2` test compile identically, so the source arms were kept identical.
- fn_8000A3EC / fn_8000AF1C: lerp two UI keyframe records (c,d) at t into an output record + transform matrix
  (translate*scale*rotZYX in A3EC; scale/translate/Y-or-Z-rot or quaternion slerp via fn_8000E764 sin/cos in AF1C).
  Output record layouts are raw offsets (u8*), shared with updateMenuOrBackgroundUI/updateHUDRelatedUI callers.
- A3EC quirk kept: the first colour-field test compares u16@c+0x1C with u8@d+0x28 (target does this).
- Prototypes: A3EC and AF1C declared in the header with the argument roles from the asm
  (AF1C: dest Mtx, out buf, c, d, block table, ctx f32*, t). File_0x8000ba3c.c still has its own older declarations
  (void*, u8*, UIAnimRecord*): differing declarations are tolerated in that file (not touched).

## Hypothesis log
[S1] A3EC/AF1C drafted from asm, sizes exactly match (2864 / 2732). Remaining diffs not examined: register allocation / lerp temp order.
  next: check lerp operand order (fmadds f31*a vs b*t), the PSMTX temp matrix order on the stack, and the unrolled 4-row colour loop.
[S1] fn_8000A0AC: p1/p2 pointers land in r10/r11 instead of r9/r10; next: sequencing of the a[4]==2 branches.
[S1] interpolatePointsBezier_Vec2s (pre-existing draft, not touched): target converts each coordinate sequentially (lha;xoris;stw;lfd;fsubs;stfs)
  with `cmplwi r8` (mode unsigned) and 4 stw saves (no stmw); ours hoists the lha loads. next: mode as u32? helper inline?
