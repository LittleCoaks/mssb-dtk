# game/game/minigame/toy_field_offscreen

Unit is fully matched and flipped to Object(Matching) (sha1 "4 files OK").
Findings promoted to docs/matching_notes.md ("Findings from toy_field_offscreen").
This checkpoint can be deleted.

| function                         | status  | pct  |
|----------------------------------|---------|------|
| toyfield_offScreenCharacterImage | matched | 100% |

Sections (strict objdiff-cli diff): .text 100%, .rodata 100% (no .data/.bss in unit).

## Hypothesis log

toyfield_offScreenCharacterImage
  baseline: 77.82% (first draft, 2026-09-23)
  [S1-1] dx/dz as int temporaries before scaling  -> 87.41% (kept)
  [S1-2] separate clamped px/py instead of writing back to sx/sy  -> 91.75% (kept)
  [S1-3] `px = bound; if (sx <= px) ... else { px = far; if (sx >= px) ... else px = sx; }`  -> 95.89% (kept)
  [S1-4] `dir >= 2` branch first in the alpha selection  -> 96.90% (kept)
  [S1-5] `dx *= 0.2f`  -> 97.53% (kept)
  [S1-6] no effect: declaration order, s8/u8/int slot local, wrapping body in `if (slot >= 0)`, if/else visibility, alpha init order
  [S1-7] worse: init after the anim call (96.00), s8* slot pointer (96.62); C89 rejects block-scoped decls after the continue
  [S2-1] static inline helper returning s8 for the slot byte  -> 97.53% (no effect, reverted)
  [S2-2] `int slot = aIStrength[2+i];` (u8 into int, no cast), `(s8)slot` at both uses  -> 98.41% (kept; duplicate extsb matches)
  [S2-3] declaration-order sweep with slot local in place: `i dir alphaX alphaY` 98.41, `dir i alphaY alphaX` 98.41,
         `alphaY alphaX dir i` 98.41, `i alphaX alphaY dir` 98.57, `alphaX alphaY i dir` 98.97 (kept; all regs match)
  [S2-4] `if (sx <= bounds[1]) { px = bounds[1]; ...` for x and y  -> 97.36% (y site broke); x only -> 99.48%
  [S2-5] embedded assignment `if (sy <= (py = bounds[5]))`  -> 100% (kept); same form applied to all four bound
         sites plus `else if` collapse -> still 100%
  readability pass: done. `bounds[0]` in place of `lbl_3_data_D638[0]` regresses (96.85) -- left as is.
  Left alone: `dir` direction codes (-1 none, 2/5 + 1/2) and the `4` arg to getAnimRelatedCoordinates have no enum;
  alpha cap 0xFF is a plain byte max. `aIStrength[2+i]` is used as a roster slot index (s8, <0 = none), which
  contradicts the field name -- part of the 0x18CC-0x1903 retype question, not touched.

Flip: needed `#define REP_HEADER_DATA_FN getRepHeaderData_toyFieldOffscreen` (weak repHeaderData folding trap);
without it game.rel sha1 failed.
