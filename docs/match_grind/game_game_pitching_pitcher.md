# Checkpoint: src/game/pitching/pitcher.c  (unit `game/game/pitching/pitcher`)

Module: game (REL). Target `.text` 25,328 bytes across 41 functions.
Every function started this effort as a bare `return;` stub, so "pending" here
means "not yet implemented", not "implemented but imperfect". Per-function
baseline percentages below are stub noise (accidental prologue/epilogue
alignment), not real progress.

## Environment
- ninja: `%LOCALAPPDATA%\Programs\Python\Python311\Scripts\ninja.exe` (NOT on PATH)
- unit name is `game/game/pitching/pitcher` (doubled `game`), not `game/pitching/pitcher`
- Ghidra decompiler live over HTTP: `curl -s -m 60 -X POST http://127.0.0.1:8080/decompile -d '<functionName>'`
  (`tools/ghidra_query.py decomp` is BROKEN here; `name`/`file`/`data` subcommands work)

## Section status (non-.text)
- `.text`: target 25,328 bytes, match ~3.06% (still mostly stubs; see status table)
- `.rodata`: target 208 bytes, match 59.46% (was 55.56% before `UnknownHomes_Game.h` was added to `pitcher.h`/`pitcher.c`, which dropped it to 36.59%; see hypothesis log entry under "cross-cutting" below -- `#define SQRT2_LINKAGE static` before the header include (placed ahead of `#include "game/pitching/pitcher.h"` itself, since the header transitively includes `UnknownHomes_Game.h`) recovered it to 63.46% pre-sub-task-3, settling at 59.46% once `fn_3_70AEC`'s named rodata labels were also wired in. Confirmed via `config/GYQE01/game/symbols.txt` that `_half$localstatic3$dolsqrtf2`/`_three$localstatic4$dolsqrtf2` are real weak symbols in this module's symbol table but the target's actual `.rodata` layout for this unit starts at `lbl_3_rodata_1250` with no preceding 4-byte float pair, confirming `static` is correct: this TU's real link never materialised the out-of-line `dolsqrtf2()` copy. Remaining gap is unrelated: target still has additional float-constant labels not yet referenced by any implemented function.
- `.data`: target 32 bytes (`jumptable_3_data_8088`), match 0.00% -- our object currently has no `.data` section at all (stub code doesn't reference it)
- `.bss`: target 32 bytes, match 0.00% -- our object currently has no `.bss` section at all (stub code doesn't reference it). Target `.bss` symbols:
  - `pad_05_00001728_bss` -- 4 bytes -- missing in ours
  - `lbl_3_bss_172C` -- 28 bytes -- missing in ours

## Status table
(work order is smallest-first per REL missed-inline discipline)

| function                                  | bytes | status  | pct |
|-------------------------------------------|-------|---------|-----|
| resetCounter                              |    20 | matched | 100% |
| pitcherAITransitionFromPrePitchToWindup   |    24 | matched | 100% |
| fn_3_75090                                |    52 | matched | 100% |
| fn_3_70680                                |    56 | matched | 100% |
| resetPitcherValuesBetweenBatters          |    76 | matched | 100% |
| resetBatterCount                          |    76 | matched | 100% |
| fn_3_740D0                                |    88 | matched | 100% |
| fn_3_73850                                |    88 | matched | 100% |
| fn_3_6F6CC                                |   124 | pending | 3.23% |
| fn_3_73F2C                                |   128 | pending | 3.13% |
| resetInMemPitcher                         |   132 | pending | 3.03% |
| setPitchingConstants                      |   168 | pending | 2.38% |
| fn_3_70AEC                                |   168 | pending | 98.81% (near-miss; permanent constant-pool artifact, see hypothesis log) |
| fn_3_706B8                                |   176 | pending | 2.27% |
| estimateXAndFrameAtBatterZ                |   208 | pending | 1.92% |
| loadPitcherActor                          |   216 | pending | 1.85% |
| fn_3_73FAC                                |   292 | pending | 1.37% |
| fn_3_7372C                                |   292 | pending | 1.37% |
| handleHPBORRunnerAdvance                  |   292 | pending | 1.37% |
| fn_3_709B4                                |   312 | pending | 1.28% |
| fn_3_73DE8                                |   324 | pending | 1.23% |
| fn_3_70280                                |   364 | pending | 1.10% |
| fn_3_6FA28                                |   368 | pending | 1.09% |
| fn_3_70838                                |   380 | pending | 1.05% |
| fn_3_6FB98                                |   520 | pending | 0.77% |
| fn_3_6FDA0                                |   548 | pending | 0.73% |
| setDefaultInMemPitcher                    |   564 | pending | 0.71% |
| pitcherMovementOnMound                    |   584 | pending | 0.68% |
| pitchCall                                 |   660 | pending | 0.61% |
| fn_3_6FFC4                                |   700 | pending | 0.57% |
| waitingForPitch_checkForPickoffs          |   736 | pending | 0.54% |
| pitchCurve                                |   852 | pending | 0.47% |
| fn_3_70B94                                |   864 | pending | 0.46% |
| waitingForPitch                           |   900 | pending | 0.44% |
| atBat_Pitcher                             |  1116 | pending | 0.36% |
| adjustPitchCurveSpeedCursedBall           |  1124 | pending | 0.36% |
| pitchBeingReleased                        |  1180 | pending | 0.34% |
| endAtBatNonHit                            |  1344 | pending | 0.30% |
| pitchSetPhysicsConstants                  |  1344 | pending | 0.30% |
| pitchingWindUpFunction                    |  2460 | pending | 0.16% |
| pitchInAirFunction                        |  5408 | pending | 0.07% |

## Call graph

33 leaf functions; only 8 functions have in-file callees. No cycles. Max
unblock-yield is 1 (no hub function).

```
atBat_Pitcher -> endAtBatNonHit, pitchCall, pitchInAirFunction, pitchingWindUpFunction, waitingForPitch
fn_3_70B94 -> estimateXAndFrameAtBatterZ
fn_3_73DE8 -> pitchCall
fn_3_73F2C -> pitchInAirFunction
pitchBeingReleased -> adjustPitchCurveSpeedCursedBall, pitchInAirFunction, pitchSetPhysicsConstants
pitchInAirFunction -> estimateXAndFrameAtBatterZ, pitchCurve
pitchingWindUpFunction -> pitchBeingReleased
waitingForPitch -> pitcherMovementOnMound, waitingForPitch_checkForPickoffs
```

## Hypothesis log

cross-cutting (header change blast radius / SQRT2_LINKAGE):
  baseline: `.rodata` 55.56% before `#include "game/UnknownHomes_Game.h"` was added
  [1] grepped `src/`+`include/` for `#include.*pitching/pitcher.h` -> only
      `src/game/pitching/pitcher.c` itself includes the header, so the
      header change has zero blast radius on any other TU (kept, no other
      unit affected)
  [2] added `#define SQRT2_LINKAGE static` directly before
      `#include "game/UnknownHomes_Game.h"` in pitcher.c while pitcher.h
      *also* unconditionally included that header first -> compile error
      "macro 'SQRT2_LINKAGE' redefined" (reverted structure, not a score
      result)
  [3] moved `#define SQRT2_LINKAGE static` to before
      `#include "game/pitching/pitcher.h"` (the first transitive include of
      `UnknownHomes_Game.h`) and dropped the now-redundant direct include
      from pitcher.c -> `.rodata` 36.59% -> 63.46%, `.text` unchanged for
      every function (kept)

fn_3_70AEC (baseline 2.38%; prior worker's attempts, from before this task):
  [1] direct algebraic form -> 77.43% (kept, carried into this task)
  [2] algebraic rewrite `frameWhenUnhittable*-0.5f + pitchHangtimeCounter` -> 76.12% (reverted)
This task's attempts (starting from 77.43%, after SQRT2_LINKAGE fix bumped baseline .rodata visibility):
  [3] declared `extern const f32 lbl_3_rodata_1250/1258/12A8;` at file scope
      and substituted them for the `0.5f`/`0.0f`/`10000.0f` literals -> 98.81%
      (kept). Verified label values via `config/GYQE01/game/symbols.txt` line
      numbers 2779 (0.5), 2781 (0.0), 2793 (10000.0) matched against the
      target's disassembly relocations for this function.
  [4] swapped local declaration order (`f32 v; f32 t;` instead of `f32 t; f32
      v;`) to try to flip the f1/f2 register-allocation swap on the
      `horizontalGlobalParabolicVelo`/`horizontalOffsetParabolaMidpoint`
      loads -> 98.81% (no change either way; reverted to original order for
      minimal diff)
  [5] reversed multiplication operand order (`t * g_Pitcher.horizontalGlobalParabolicVelo`
      instead of `g_Pitcher.horizontalGlobalParabolicVelo * t`) -> 98.69%
      (reverted, worse)
  Remaining 1.19% gap is a single `DIFF_ARG_MISMATCH` cluster: the
  compiler-generated `0x4330` int-to-float magic-double bias constant
  (`lbl_3_rodata_1280` in target, pooled as anonymous `@260` in ours) plus
  the register-number swap that rides along with it. Per
  `docs/matching_notes.md` "Shared .sdata2 literal pool..." section, this
  magic double is emitted implicitly by the compiler for the `(f32)s16`
  casts and explicitly declaring/referencing it forces a different codegen
  path (fsub+frsp) instead of matching the target's implicit `fsubs` -- this
  category is a documented permanent split artifact, not fixable by source
  changes alone. Did not attempt to declare `lbl_3_rodata_1280` explicitly
  since the docs precedent already established that backfires.

fn_3_75090 (baseline 7.69%; prior worker's attempts, from before this task):
  [1] direct field-to-field no temps -> 51.46% (reverted)
  [2] whole-struct VecXYZ copy -> 0.00% (reverted, lowers to integer word copies)
  [3] three f32 locals assigned before state writes, stored after -> 52.62% (kept, carried into this task)
  [4] y/z temps but x inline -> 50.69% (reverted)
  [5] statement-order swap of pitcherActionState/currentStateFrameCounter -> 41.92% (reverted)
This task's attempts (starting from 52.62%):
  [6] verified field offsets against the target disassembly before changing
      anything: target's `lfsu f2, g_Pitcher@l(r4)` / `lfs f1, 0x4(r4)` /
      `lfs f0, 0x8(r4)` confirm the source vector fields are at
      `g_Pitcher` offsets 0x0/0x4/0x8, and `stfsu f2, g_Ball@l(r3)` /
      `stfs f1, 0x4(r3)` / `stfs f0, 0x8(r3)` confirm the destination is at
      `g_Ball` offsets 0x0/0x4/0x8. Cross-checked against
      `include/game/UnknownHomes_Game.h`: `ballCurrentPosition` is
      documented at `/*0x000*/` in `InMemPitcherType` and
      `AtBat_Contact_BallPos` at `/*0x0000*/` in `InMemBallType` -- the
      prior worker's field mapping was ALREADY CORRECT; the offset
      hypothesis was a red herring. `pitcherActionState` (0x13E) and
      `currentStateFrameCounter` (0x120) were likewise already correct.
      The only real defect was the addressing-mode shape: our codegen
      emitted a separate `addi r5, r4, g_Pitcher@l` + `lfs f0, 0x0(r5)`
      where the target fuses those into one `lfsu` (update-form load
      folding the base-address materialisation into the first load of a
      struct at offset 0).
  [7] rewrote using explicit struct-base pointer locals per
      `docs/matching_notes.md` "An explicit struct-base pointer local is
      right for repeated fixed-index access": `VecXYZ* src = &g_Pitcher.
      ballCurrentPosition; VecXYZ* dst = &g_Ball.AtBat_Contact_BallPos;`
      then `dst->x = src->x;` etc., keeping the two state-field writes
      between the pointer declarations and the field copies -> **100.00%**
      (kept)
  Did not need to try the "no locals, direct field-to-field" structural
  form separately since the prior worker's attempt [1] already covers that
  shape (51.46%) with the (now-confirmed-correct) field mapping.

## Findings

- `resetBatterCount` and `fn_3_73850` share a "find first unused out-slot"
  3-iteration scan over `g_Strikes.runnerIndexForEachOutThisPitch[3]`;
  `fn_3_73850` just prepends `g_Strikes.outs++`. Worth checking the
  remaining stubs for this same idiom before hand-writing new loop shapes.
- `setPitcherStatsToInMemPitcher` is declared `void(void)` in
  `include/game/match_setup/roster_init.h`, but Ghidra evidence indicates it
  actually takes an `int` roster-index argument. This is a cross-file
  signature correction still outstanding (not made in this task, since it
  is outside `pitcher.c`/`pitcher.h`).
- `strikeZone` (`config/GYQE01/game/symbols.txt:4165`, `.data:0x00005E98`,
  size 0x18 = 6 floats) is used by `setPitchingConstants` but is declared
  nowhere in `include/` or `src/`. Needs a declaration before
  `setPitchingConstants` can be implemented.
- `fn_3_70680` (matched at 100% by the prior worker) confirmed the target
  uses an explicit `if`/two-return-block form rather than the branchless
  `return a && b;` CLZ idiom (68.5%) -- a precedent for preferring explicit
  control flow over branchless boolean idioms when reproducing this file's
  target codegen.
