# main/Unknown/File_0x8000ba3c  [S1]

Baseline (rep_c20): 23.75% .text, handleUIAction 100% (1/15). Six pre-existing drafts (updateMenuOrBackgroundUI 45.2,
updateHUDRelatedUI 41.5, triggerDefaultHUDAction 58.5, SetSpriteRect 0 (size 740 vs 780), AddVec2iToQuad 40.9) + 9 unowned.
After [S1]: .text 61.89%, extab 95.8%; all 15 functions drafted (sizes equal for every new function).

| function | status | pct |
|---|---|---|
| handleUIAction | matched | 100 |
| updateMenuOrBackgroundUI | pending (pre-existing draft, untouched) | 45.15 |
| updateHUDRelatedUI | pending (pre-existing draft, untouched) | 41.52 |
| fn_8000CC4C | pending | 78.40 |
| fn_8000CEF0 | pending | 56.90 |
| triggerDefaultHUDAction | pending (pre-existing draft, untouched) | 58.46 |
| fn_8000D8A4 | pending | 76.43 |
| fn_8000DC9C | pending | 74.09 |
| fn_8000E030 | pending | 92.77 |
| fn_8000E2D4 | pending | 47.33 |
| fn_8000E764 | pending | 90.91 |
| fn_8000E7BC | pending | 99.75 |
| SetSpriteRect | pending | 87.32 (was 0) |
| fn_8000EC0C | pending | 87.15 |
| AddVec2iToQuad | pending | 56.50 (was 40.9) |

## Findings
- fn_8000CC4C(layout, part, src, off, size) WRITES src bytes into a part's keyframe data (types 0/1 direct, 2 sparse words,
  3 block list); fn_8000CEF0(layout, element, part, frame, out) READS frame `frame` of a part into `out` (inverse).
  Record walk: type word & 0x7FFF: 0 -> +(part.u16@2>>2)*4, 1 -> +slotWords*4, 2/3 -> +u16@6*4.
- fn_8000D8A4 / DC9C / E030 / E2D4 are radial-gauge (pie/ring) renderers: centre (128,128), radius 128, step 0x10000/block.extraH,
  angle unit 2*pi/65536 (0.0000958738), sin/cos via fn_8000E764 (out[0]=sin, out[1]=cos). D8A4/DC9C emit a triangle strip
  ring (DrawNullSprite), E030 a fan (fn_800B12DC), E2D4 an integer-truncated fan (fn_800B13C0). `block` = UIDrawBlock (colors at +0x20,
  extraF +0x30, extraH +0x34, extraB +0x36). The first 8 words of the block are s32 (A3EC/AF1C write s32), though the
  typedef says f32 mtxRows.
- fn_8000E2D4 reads two float locals uninitialised (f26/f27 used as the w factor of the matrix translation column before any
  write); the draft keeps w0/w1 uninitialised (original-game bug, kept).
- fn_8000E7BC / SetSpriteRect / fn_8000EC0C fill the sprite buffer lbl_80366188 (SpriteRectBuf): colours first, then 4 vertex
  positions, uv, base (+0x70), rec ptr (+0x78 for E7BC/EC0C), flags (+0x7C). E7BC draws a unit quad, EC0C a texture rect with
  UIAnimRecord, SetSpriteRect the same for a HUD sprite. Stack-local ordering: locals declared in REVERSE order of their
  stack addresses (first declared = highest) in this compiler.
- skipUIRecord: target does not share one helper; CEF0's walk was expanded by hand with separate case 2 / case 3 blocks.

## Hypothesis log
[S1] SetSpriteRect: use sprite[8] directly (target reloads it) + colour stores before the position stores -> 0 -> 87.3%.
[S1] E7BC: quad store order (0,1,6,7,2..5) -> 99.43 -> 99.75. remaining: flags temp register.
[S1] D8A4: reversed local declaration order (verts, arrB, arrA, out, p, v) and field-wise Vec copies -> 67.6 -> 74.9; do-while loop -> 76.4.
  next: frame is 0x10 bytes larger than target (4140 vs 4130): extra locals sn/cs/colors; target keeps sin/cos in f26/f27.
[S1] CEF0: while(n--) loop gets unrolled x8 by the compiler (target loop is not unrolled, check at the bottom); logic same.
  next: find loop form (do/while with pointer decrement in body).
[S1] E2D4: zero-init loop: pointer do-while (47%); unrolled for-loop gave 26%.
[S1] AddVec2iToQuad: PSMTXCopy moved after the point math -> 40.9 -> 56.5. next: target hoists the 8 lwz of vec2i before the conversions.
[S1] untouched pre-existing drafts: updateMenuOrBackgroundUI, updateHUDRelatedUI, triggerDefaultHUDAction.

## Open questions
- Prototype mismatches (fn_8000A3EC/AF1C declared differently in ba3c.c vs include/Unknown/File_0x8000a0ac.h) are tolerated;
  unify when the record types (UIAnimRecord vs raw u8*) are settled.
- .sdata2 63.6%: pool order depends on function order/first use; compare after function bodies settle.
