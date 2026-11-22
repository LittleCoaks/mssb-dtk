# kinoko.c (ribbon effect) â€” match grind checkpoint

Unit: `game/game/minigame/kinoko` (moved from stadium/ on 2026-09-23)
Module: game (REL)
Baseline at session start (2026-09-23): 9 stubs; fn_3_16917C, fn_3_16943C, fn_3_1695A0,
fn_3_1695A4 and fn_3_16C394 were missing from the .c.

Not a stadium. The unit's own panic string is "kinoko.c" / "Ribbon Effect Pos Data None": six
colour-cycling ribbons trail from a character's bones (both hands, torso, head, both feet), plus
a pulsing 4x4 TEV texture layer (fn_3_16917C, installed on a model via fn_80011604).

Split change: .data start 0x2A330 -> 0x28928. The ribbon state (0x19E0, zero-initialised),
colour table (6 x RGBA) and draw table ({0, fn_3_169984} x2) are this TU's statics: the target
addresses the colour table as ribbon-state base + 0x19E0, which MWCC only does within one TU.
This alone took fn_3_16A07C 80.4 -> 97.1%.

getAnimationCollisionOffset now returns BOOL (callers here test it; still a stub).

## Status

Strict `objdiff-cli diff` numbers (2026-10-02, Opus pass).

| function                           | status    | pct |
|------------------------------------|-----------|-----|
| fn_3_16C394                        | matched   | 100% |
| fn_3_16B884                        | matched   | 100% |
| fn_3_16B5B4                        | exhausted | 96.4444% |
| fn_3_16B488                        | exhausted | 91.8667% |
| fn_3_16A07C                        | exhausted | 98.6321% |
| fn_3_169E70                        | matched   | 100% |
| fn_3_169D00                        | matched   | 100% |
| fn_3_169984                        | exhausted | 99.6413% |
| fn_3_169804                        | matched   | 100% |
| fn_3_169600                        | matched   | 100% |
| fn_3_1695A4                        | matched   | 100% |
| fn_3_1695A0                        | matched   | 100% |
| fn_3_16943C                        | matched   | 100% |
| fn_3_16917C                        | matched   | 100% |

10/14 at 100%. Sections: .text 99.047, .rodata 100, .data 100, .bss 100.

## Log

### fn_3_169D00: re-index ribbonQuads[*count] for every store (no local), u32 i, `cur--, i--` -> 100%.
### fn_3_16A07C (97.06%): per-ribbon colour advance written out (`x++; if (x >= 6) x -= 6;`),
    ribbon state referenced directly (no local pointer).
### fn_3_16B488 / fn_3_16B5B4: switch cases in hand L, hand R, head, foot L, foot R order.
    Remaining: target sign-extends `bone` twice (call and switch); an int param with (s8) casts did not
    reproduce it (reverted).
### fn_3_16B884 (71.43%): running u8 colour index (`colorFrom = c++; colorTo = c;`) 68.5 -> 71.4.
    Target computes the colour offsets at run time; still far off.
### fn_3_16C394: store charID before enabled/frame -> 100%.
### fn_3_169984 (90.54%): inactive branch first, `a->z > b->z` sort compare. Remaining: registers.

## Session 2026-10-01 (Opus pass) — strict `objdiff-cli diff` numbers from here on

Session-start strict baseline: 16917C 98.74, 16943C 97.63, 1695A4 98.70, 169600 95.59, 169984 90.26,
169D00 99.89, 169E70 98.92, 16A07C 96.35, 16B488 91.40, 16B5B4 96.06, 16B884 70.54;
.text 90.66 .rodata 85.79 .data 0 .bss 0.

[file-wide 1] `#define SQRT2_LINKAGE static` (drops unused dolsqrtf2 _half/_three from .rodata) -> rodata 82.4 alone.
[file-wide 2] + functions defined in reverse address order -> .rodata 100, .data 100, every function up
   (169D00 -> 100, 169E70 99.61, 16A07C 96.70, 16B488 91.87, 16B5B4 96.44, 16B884 70.87). kept.
[file-wide 3] symbols.txt: split lbl_3_bss_BA00/BA08/BAE0 into curTex, curTexObj, pulseFrame, texObjB,
   texObjA, texB, texA, ribbonQuads (scope:local, same addresses) -> .bss 100, 1695A4 -> 100,
   169600 96.98, 16917C 98.80. kept.

### fn_3_16943C 97.63 -> 100 (matched; also fixes inlined copy in fn_3_16917C)
  [1] final check written `if (value + pulseStep * 2 > 255 || value + pulseStep * 2 < 0) pulseStep *= -1;`
      (no store back to value; `*= -1` gives the target's lbzu/mulli -1) -> 99.83
  [2] `value = curTex[...]; value += pulseStep * 2;` as two statements -> 100. readability pass: done.
### fn_3_16917C 98.80 -> 100 (matched)
  GXSetTexCoordGen2 type arg is 1. NB this repo's GXEnum.h has GX_TG_MTX2X4=0 / GX_TG_MTX3X4=1, swapped vs
  the real SDK (MTX3x4=0, MTX2x4=1); kept the repo header's name GX_TG_MTX3X4 (value 1). readability pass: done.
### fn_3_169600 96.98 -> 100 (matched)
  [1] `u32 row = y` copy in first loop -> no change (copy-propagated).
  [2] first loop uses its own counters (i/j), second keeps x/y -> 99.85 (target's extra saved reg r28).
  [3] `pulseStep = -1;` before `pulseFrame = 0;` -> 100. readability pass: done.
### fn_3_16B488 / fn_3_16B5B4 (inlined copy): bone sign-extended twice in target, once in-place in ours
  [1] u8 param + (s8) casts -> 16B488 91.47 (down), reverted
  [2] int param + (s8) casts -> 91.47, reverted
  [3] BOOL found = call; if (!found) -> no change
  [4] static inline wrapper for the first call -> no change
  [5] switch moved into a static inline helper -> no change
  [6] early `return` when the first call succeeds -> no change
### fn_3_169E70 99.61 -> 100 (matched)
  [1] locals declared forward, prevPos, nextPos, along, side (stack offsets descend in declaration order) -> 99.77
  [2] `0.0f == PSVECMag(..)` / `(f32)PSVECMag(..) == 0.0f` -> no change on fcmpu operand order
  [3] `!= 0.0f` with swapped if/else -> 93.59, reverted
  [4] `!PSVECMag(&v)` -> fcmpu f1,f2 as target -> 100. readability pass: done.
### fn_3_169984 90.31 -> 99.64 (pending)
  Target keeps `order`'s address in r31 for the whole function (CSE of the array base), so array indexing,
  not pointers, is the original shape.
  [1] draw loop `order[i].index` (no pointer a) -> 90.35
  [2] sort loop indexes order[i]/order[j] (pointers a/b removed) -> 95.02
  [3] front/back init moved from declarations to just before loop 1 -> 96.99
  [4] front/back as u32 indices (`order[front]`, `order[back]`) -> 97.29
  [5] back branch stores index before z -> 98.18
  [6] loop 1 `q = &ribbonQuads[i]` per iteration (not q++) -> 99.19 (no q at all: same)
  [7] decl order front, back, i, j, q -> 99.42 (full 120-perm sweep of these five: no better)
  [8] loop 1 counts with j (sort keeps i outer / j inner) -> 99.64. kept.
  no change: draw loop with j/k/front counter, separate `quad` var, ribbonQuads + idx, init order back/front,
    for-init comma form, `back -= 1`, `continue` form. worse: struct assignment swap (93.5), active branch
    first (95.99), post-inc in subscript (89.6), back or front as pointer (99.10 / 97.13), q++ (98.30).
  Remaining: loop 1 back/q in r30/r29 swapped; draw loop i/base r30/r29 vs target r28/r30.
### fn_3_16B884 70.87 -> 100 (matched)
  [1] colour counter `c` typed int (was u8): the inlined fn_3_16B5B4 then reads colorFrom back as
      (u8)c (clrlslwi), as in target -> 99.67 (u32 same)
  [2] shift loop written as `RIBBON_STATE.ribbons[k].points[i]` / `[i - 1]` (no p pointer) -> 100.
  readability pass: done.
### fn_3_16A07C 96.70 -> 98.63 (pending)
  The six inlined fn_3_169D00 calls are the main shape: target tests `active` through a separate pointer.
  [1] fn_3_169D00 `if (ribbon->points[i].active)` keeping the cur-- pointer -> 16A07C 97.68 but 169D00
      93.17, reverted
  [2] caller arg shapes (`ribbons + k`, `(Ribbon*)&...points[0]`), `ribbon->points + 24` init -> no change
  [3] fn_3_169D00 index form: loop on i only, `if (ribbon->points[i].active) { cur = &ribbon->points[i];
      prev = &ribbon->points[i - 1]; ...` -> 16A07C 98.63, 169D00 stays 100. kept.
  [4] decl perms of count/i/alpha: none better; u32 i, `RIBBON_POINTS - 1 - i`: no change;
      `i > 0` 98.63-, int alpha 98.59, alpha after first memcpy 97.45, shift loop in static inline 98.60.
  Remaining: shift loop i/dst/src in r21/r19/r20 vs target r19/r20/r21, and a few register/scheduling
  swaps in the inlined fn_3_169D00 copies 2-6. Register numbering only.
  [7] `char bone` (param + prototype) -> no change
  [8] each case assigns `bone = ..._ALT;` then calls with bone -> no change
  => fn_3_16B488 / fn_3_16B5B4 marked exhausted. The only remaining diff in both is this bone extsb CSE
     (16B5B4's diff is entirely its inlined 16B488 copy). Next lead if reopened: something that makes MWCC
     treat the call's and the switch's (int)bone as different expressions; none of the type/cast/inline/
     block-structure forms above did.

### fn_3_169984 extra: int/s32 front/back -> 97.03, reverted. => exhausted (register numbering only).
### fn_3_16A07C => exhausted (register numbering only, see above).

## Readability pass (2026-10-02)
All matched functions: done. RibbonPoint.active, RibbonQuad.active, RibbonState.enabled retyped
E(u8, BOOL) (only ever set to 1 / tested against 0), stores now TRUE. Left alone:
`(s8)g_Minigame.playerIDWithPowerup[0] == -1` (a player index elsewhere compared with runner/fielder
indices, not a CHAR_ID; no named "none" sentinel exists); RibbonState.charID is passed to
getAnimationCollisionOffset as an animation slot index, so CHAR_ID typing is not evidenced.
GXEnum.h note: GX_TG_MTX2X4/GX_TG_MTX3X4 values are swapped relative to the real SDK; kinoko uses the
repo's GX_TG_MTX3X4 (=1). Header not touched (many users).
