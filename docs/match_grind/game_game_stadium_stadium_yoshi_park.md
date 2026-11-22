# stadium_yoshi_park.c — match grind checkpoint

Unit: `game/game/stadium/stadium_yoshi_park`
Module: game (REL)
Baseline at session start (2026-09-22): every function a bare `return;` stub; fn_3_E1DB8
(0xE1DB8, size 0x1F0, first function in the split) was missing from the .c entirely.

Reference siblings: `stadium_bowser_castle.c` (same stadium framework, same object-overlay
approach), `sta_c2.c` (loadWarioPalace loader template).

Ghidra names (via get_function_by_address): fn_3_E1FA8=FUN_8072103c, fn_3_E2034=FUN_807210c8,
fn_3_E2118=FUN_807211ac (plant onCollision fn), fn_3_E25D0=FUN_80721664, fn_3_E28DC=FUN_80721970,
fn_3_E29B4=FUN_80721a48, fn_3_E3914=FUN_807229a8, fn_3_E4554..E4EF4 = FUN_807235e8..FUN_80723f88.
fn_3_E22A4 (0x80721338) has no Ghidra function (it's used as a drawFn pointer only).

Address mapping: Ghidra 0x8086BEE0 == lbl_3_bss_AE00. BYTE_8086bef0..bef4 == AE10..AE14.
bss block: AE00 u8, AE01 u8 (use-PSVECScale-instead-of-matrix flag, fn_3_E4A38), AE04 u32 emitter id,
AE10 u8 emitter-active flag, AE11..AE14 u8 counters (loader), AE18 plantAnimationPointers[14].

## Status

From report.json, updated after every function (2026-09-22 session).

| function                           | status    | pct |
|------------------------------------|-----------|-----|
| loadYoshiPark                      | pending   | 84.0824% |
| fn_3_E4EF4                         | pending   | 95.9615% |
| processYoshiParkPlantBoundingBoxes | pending   | 98.9655% |
| fn_3_E4BE8                         | pending   | 94.98% |
| fn_3_E4A38                         | matched   | 100.0% |
| fn_3_E48D0                         | matched   | 100.0% |
| fn_3_E4760                         | matched   | 100.0% |
| fn_3_E4658                         | matched   | 100.0% |
| fn_3_E45F0                         | matched   | 100.0% |
| fn_3_E45A8                         | matched   | 100.0% |
| fn_3_E4554                         | matched   | 100.0% |
| controlYoshiParkPlants             | pending   | 96.2966% |
| fn_3_E3914                         | matched   | 100.0% |
| ParkPlantsPopUp                    | matched   | 100.0% |
| updatePlantAimingOrCatch           | matched   | 100.0% |
| tryPlantCatchAndBeginSpitAim       | pending   | 99.5382% |
| nadoRelated                        | pending   | 92.3125% |
| yoshiParkPlantRelated              | matched   | 100.0% |
| updateStadiumObjStateAndTransform  | matched   | 100.0% |
| updatePlantCatchState              | pending   | 99.2526% |
| fn_3_E29B4                         | pending   | 98.6937% |
| fn_3_E28DC                         | matched   | 100.0% |
| advancePlantInteractionPhase       | pending   | 99.9359% |
| fn_3_E25D0                         | matched   | 100.0% |
| fn_3_E2324                         | pending   | 98.9766% |
| fn_3_E22A4                         | matched   | 100.0% |
| fn_3_E2118                         | matched   | 100.0% |
| fn_3_E2034                         | matched   | 100.0% |
| fn_3_E1FA8                         | matched   | 100.0% |
| fn_3_E1DB8                         | matched   | 100.0% |

19/30 at 100%.

## Hypothesis log

fn_3_E4554 / fn_3_E45A8 / fn_3_E45F0 — MATCHED first attempt (plant anim-bank reset, scale reset to 0.2f,
  rotation reset from parkPlantData). Introduced YoshiPlantObj overlay + YoshiPlantPlacement (stride 0x1C).

fn_3_E1FA8 / fn_3_E22A4 / fn_3_E25D0 — MATCHED first attempt. fn_3_E22A4 = plant preDraw (material
  animState frame from _C4/_C5/_C8); fn_3_E25D0 = set plant animation (curAnim at 0xCB);
  fn_3_E1FA8 = looping idle-anim callback (wrap 900 -> 180).

updateStadiumObjStateAndTransform — MATCHED first attempt (plant shrink step: scale -= 1.0857142857/_C6,
  pos.y = -(1.2*scale), countdown _C5).
fn_3_E4BE8 (plant collision-mesh matrix; mirrors bowser fn_3_C823C) — 94.98%
  [1] initial impl                                  -> 94.98%
  [2] `Mtx joint` declared before the plant local   -> 94.98% (no change)
  [3] no plant local, index objects[offset] at each use -> 86.12% (reverted)
  remaining: r30/r31 swap (offset*0xE8 vs plant ptr).
fn_3_E4EF4 (lazy vertex-array alloc + processYoshiParkPlantBoundingBoxes) — 80.13%; the stubbed
  processYoshiParkPlantBoundingBoxes gets inlined as empty. Re-check after it's implemented.

fn_3_E28DC — MATCHED (ball-within-2.5 check; body is fn_3_E25D0(plant, 6) auto-inlined)
  [1] initial `PSVECMag(&diff) <= 2.5` -> 99.72%; [2] `2.5 >= PSVECMag(&diff)` (target fcmpo const,mag) -> 100%
fn_3_E2034 — MATCHED (turn plant to face ball; acos * 57.29578f, 360-wrap when x < 0)
  [1] -> 99.82%; [2] declare `toBall` before `fwd` (stack slot order) -> 100%

fn_3_E4658 — MATCHED first attempt (reset plant transform; tail is fn_3_E45F0 + fn_3_E45A8 auto-inlined).
  Note: PSVECScale prototype is (src, scale, dst).
yoshiParkPlantRelated — MATCHED (star award when the spit anim crosses frame 20)
  [1] initial -> 81.77%; [2] `frame`/`speed` locals (target loads animSpeed before the first compare) -> 96.53%
  [3] `-rot * k` order -> no change; [4] `ang = -plant->rotation; ang = 0.017453292f * ang;` -> 100%
updatePlantAimingOrCatch — 77.30% (`else fn_3_E2034(plant)` auto-inlined; the still-stubbed
  updatePlantCatchState is being inlined as `return FALSE`). Re-check after updatePlantCatchState is written.

fn_3_E48D0 / fn_3_E4760 — MATCHED first attempt (full plant reset = fn_3_E4658 + fn_3_E4554 inlined,
  clear _C5/_C4/_C7/_C8, release held ball via setBallInactiveVariables; E4760 also clears _C9).
  0xCA named holdingBall (set/cleared around setBallInactiveVariables).

fn_3_E2118 — MATCHED first attempt (plant onCollision: `fn_3_E2118(int idx)`; star-catch path =
  fn_3_E25D0(plant, 8) inlined + standard hazard sound block; then ballState_thrown_to_holding,
  processFielderAutoCatch, g_FieldingLogic.knockoutFinished = 1).
  Named 0xC4 `state` (PLANT_STATE, names from the annotated Ghidra project: IDLE 0, TRACKING 2,
  STAR 4, SHRINK 5; 1 and 3 unnamed), 0xC5 stateFrame, 0xC6 stateDuration.
ParkPlantsPopUp — 91.67% (grow step then catch-or-track). tryPlantCatchAndBeginSpitAim returns
  E(u8, BOOL) (target tests it with clrlwi.). Remaining diff is the stubbed updatePlantCatchState/
  tryPlantCatchAndBeginSpitAim being inlined; re-check after those are written.

fn_3_E4A38 — MATCHED first attempt (local-min/max copy of the framework's transformVectorsUpdateBoundingBox,
  with lbl_3_bss_AE01 selecting PSVECScale(1.0f) instead of PSMTXMultVec; ends with a vestigial
  PSVECScale of the ball position into a dead local, as in the target).
fn_3_E29B4 — 98.69% (eat-range test: radius 5.5*scale, height band 1.5..8.5*scale; low/high catch anim 4/5
  via fn_3_E25D0 inlined; speed from a function-local static const {0.8f, 1.0f, 1.2f})
  [1] initial                                            -> 98.69%
  [2] ACTActor* local for the two speed stores           -> 93.42% (reverted)
  [3] speed staged through a local                       -> 98.69% (no change, reverted)
  remaining: target does not reload plant->actor between the animSpeed and applySpeed stores; ours does.

fn_3_E1DB8 — MATCHED (was missing from the .c entirely; ambient sound driver: emitter start/stop on
  pause, two random 100..999-frame countdowns for sound ids +6/+7)
  [1] initial -> 99.89% (code identical; .bss offsets differed)
  [2] statics declared in REVERSE address order — MWCC lays out this TU's .bss statics in reverse
      declaration order (plantAnimationPointers, declared last, had landed at offset 0). -> 100%
  bss block now: AE00 u8, AE01 u8, AE04 ambientEmitter, AE08 ambientTimerB, AE0C ambientTimerA,
  AE10 ambientActive, AE11..AE14 u8 (loader counters), AE18 plantAnimationPointers[14]. .bss size 80 = target.

processYoshiParkPlantBoundingBoxes — 98.97% (bowser stadiumObjCollision_Castle skeleton; objects indexed by
  *count; two offset collision boxes from a 0x44-byte YoshiObjControl stack copy: (x-4, y, z-4) and
  (4+x, y-10, 4+z)). Added YoshiPlantPlacement.usedFlag (0x10, 2 = end of list) / group (0x12).
  [1] initial (f32 x/y/z locals)                         -> 94.23%
  [2] `Vec pos` + &pos.x/&pos.y/&pos.z (target keeps &y/&z hoisted in regs) -> 98.97%
  remaining: register numbering only (cfg / off*4 / counters), same class as bowser's twin functions.
fn_3_E4EF4 — 95.96% now that processYoshiParkPlantBoundingBoxes is no longer inlined.
  [4] size terms reordered u16,s32,VecSrcDst,f32         -> 95.38% (reverted)
  remaining: size-sum add operand order (2c+4c)+24c then 4c+...

updatePlantCatchState — 99.25% (gatekeeper: ball in play, plantType == 0 (red), not deadBallReason 1/3
  (Ghidra: home run / ground-rule double; no enum in the headers), curAnim 4..6 => already catching;
  then moving-ball test fn_3_E29B4 or stationary test fn_3_E28DC, both auto-inlined)
  [1] initial (stationary branch first)                         -> 52.68%
  [2] `if (0.0f != mag) return fn_3_E29B4(plant); return fn_3_E28DC(plant);` -> 98.04%
  [3] fn_3_E28DC / fn_3_E29B4 return E(u8, BOOL) (no clrlwi on the inlined returns) -> 99.25%
  0xCB curAnim is s8 (target compares it with extsb); 0xC8 renamed plantType (Ghidra activePlantType;
  material frame = plantType + 1 in fn_3_E22A4; only non-red plants award a star in fn_3_E2118).
  remaining: inherited fn_3_E29B4 plant->actor reload.
Side effects: ParkPlantsPopUp 91.67 -> 95.28, updatePlantAimingOrCatch 77.30 -> 95.08 (the stubbed
  tryPlantCatchAndBeginSpitAim is still inlined into both).

tryPlantCatchAndBeginSpitAim — 99.54% (mouth point = head-joint matrix * origin, y negated; catch if
  |calculateBallInterceptDistance(pastCoordinates, ballPos, mouth)| <= 2.2*scale; then state PLANT_SPIT (3,
  Ghidra name), anim 7 via fn_3_E25D0 inlined, holdingBall, random spit angle base + rng(10*range)/10,
  ball velocity zeroed, signed turn angle -> rotationSpeed = -(57.29578 * ang/60), sound ids +0, fx 0/1)
  [1] initial                                                    -> 88.96%
  [2] positive `<= reach` success block; float->u32 (__cvt_fp2unsigned) then (s16) for rng's arg -> 92.10%
  [3] locals declared m, joint, mouth, down, cross, facing, aimDir (reverse) — stack slots now match -> 92.22%
  [4] placement pointer local                                     -> 97.22%
  [5] `ang = spitAngleBase;` then `spitAngle = ang + ...` (target keeps the base in f31, which is also the
      acos result's home later)                                   -> 99.12%
  [6] local acosf wrapper                                         -> no change (reverted)
  [7] ternary for the sign flip                                   -> 99.06% (reverted)
  [8] `if (!(PSVECDotProduct(&cross, &down) > 0.0f))` (target: fcmpo dot,0; bgt skip) -> 99.54%
  remaining: acos result compared in f1 then fmr to f31 (target) vs frsp straight into f31 (ours).
Side effects: ParkPlantsPopUp and updatePlantAimingOrCatch -> 100% once this was no longer an inlined stub.
New: PLANT_SPIT = 3, YoshiPlantObj.spitAngle (0xBC) / rotationSpeed (0xC0), placement spitAngleBase (0x14) /
  spitAngleRange (0x18).

nadoRelated (really the spit handler: rotate toward spitAngle while curAnim == 7, then on the frame-20
  crossing place the ball at the mouth, give it 0.1-scaled velocity along spitAngle, release it, sound +1)
  [1] initial                                                   -> 69.48%
  [2] ang split into two statements + x/z locals written to g_Ball together -> 92.14%
  [3] cos hoisted into a local                                  -> 85.86% (reverted)
  [4] static inline setBallPosition(x, y, z)                    -> 92.21% (reverted: speculative helper for +0.07)
  [5] `frame` declared before `speed`                           -> 92.31% (kept)
  remaining: y/z computed after the x store in the target (arg-evaluation-like order), f0/f2 swap.

advancePlantInteractionPhase — 99.94% (animation state machine: switch on curAnim — case 1 goes idle if the
  plant is SHRINK/IDLE else falls through to 4/5 (wait anim 2 red / 3 yellow); 7 -> face -spitAngle, anim 8;
  8 -> anim 9 + PLANT_SHRINK; default anim 0; then AnimateActorBones and animFrame = fn_800B4C40(actor))
  Outside this file: fn_800B4C40 stub `void(void)` -> `f32 fn_800B4C40(void* actor)` (no other callers).
  [1] initial                                          -> 99.94%
  [2] `0.0f == scanBoneAttachmentData(...)`            -> no change (reverted)
  remaining: fcmpu operand order only.

fn_3_E3914 — MATCHED (pop-up trigger: not already triggered (_C7), ball in play, ball y <= 11, within 12.5 of
  pos+1.4; not star swing 3/4/11/12; => PLANT_POP_UP + anim 1, plantType = rng(100)/70 unless a star was
  already given (_C9), stateDuration from a function-local static const u8[3] {20,20,20}, sound +3 fx 6/7)
  [1] initial -> 99.97%; [2] OR'd compares written 3|4|11|12 (ascending) -> 100%
  New enumerator PLANT_POP_UP = 1 (not in Ghidra's names; evidence: set here with the pop-up anim,
  ParkPlantsPopUp advances it to PLANT_TRACKING).

fn_3_E2324 — 98.98% (plant bite: mouth point via head joint; fielders {2..8} (local u8[7] init) not knocked out,
  within 2.2*scale horizontally => processFielderKnockout(angle), force recoil anim 9 + PLANT_SHRINK unless
  already anim 8 or holding the ball; sound +4 fx 8/9 with the ternaries inline in the call args)
  [1] initial (locals declared joint, m, fielderPos, delta, dir, mouth, fielders — highest address first) -> 94.79%
  [2] InMemFielder* local                                  -> 98.63%
  [3] angle through an `int` local before processFielderKnockout (target extsh's it) -> 98.98%
  remaining: register numbering (stadiumID / loop counters).

controlYoshiParkPlants — 96.30% (plant update callback. Not live: idle plants that had triggered get
  fn_3_E45F0 + fn_3_E4554 + ball release; others the full fn_3_E48D0 reset. Live: pin a held ball to the
  hold joint (root->+0x18->+0x44 worldMtx — a different joint from the head at +0x40; named
  YoshiJointList.holdNode), retract on a fielded ball (anim 9, or setAllBoneEventFlags if still anim 1),
  then switch(state): IDLE fn_3_E3914, POP_UP ParkPlantsPopUp, TRACKING updatePlantAimingOrCatch,
  SPIT nadoRelated, STAR yoshiParkPlantRelated, SHRINK updateStadiumObjStateAndTransform. Common tail:
  advancePlantInteractionPhase (Ghidra's decompile omitted this call) and the bite check fn_3_E2324 for
  red plants in states 1..4.)
  [1] initial                                                    -> 95.44%
  [2] `Vec held = {0}` scoped inside the holdingBall block (target copies the zero vector there) -> 96.30%
  remaining: inherited nadoRelated residual; plant in r31 vs target r30 (target keeps &g_Ball in r31).

loadYoshiPark — 84.08% (flow now matches the target end to end; see the function for the sequence)
  [1] initial                                                   -> 75.00%
  [2] plant-count loop on an int counter, then narrowed to u8 (target fully unrolls it) -> 84.08%
  [3] no ACTActor* local for the idle actor                     -> 83.24% (reverted)
  remaining: register allocation / scheduling across the large body (target keeps a separate
  plant-pointer copy in r16 in the placement loop; our *animTable gets spilled to 0x10(r1)).

## Session summary (2026-09-22/23)
All 30 functions implemented (fn_3_E1DB8 added; it was missing from the .c). 19/30 at 100%.
Near misses: advancePlantInteractionPhase 99.94, tryPlantCatchAndBeginSpitAim 99.54,
updatePlantCatchState 99.25, fn_3_E2324 98.98, processYoshiParkPlantBoundingBoxes 98.97,
fn_3_E29B4 98.69, controlYoshiParkPlants 96.30, fn_3_E4EF4 95.96, fn_3_E4BE8 94.98,
nadoRelated 92.31, loadYoshiPark 84.08. .bss size matches (80 bytes).
Outside this file: fn_800B4C40 -> f32(void* actor).
Next session: fn_3_E4BE8 (r30/r31), nadoRelated (arg-order-like store scheduling), loader registers.

## Cross-stadium pass (2026-09-23)

Moved .data 0x18ED0-0x19018 into the unit: .data 100%, no function change. Chained _34 alloc: loadYoshiPark 84.08 -> 84.55. Remaining: target hoists 180.0f into f30 and keeps parkPlantData base live in r23; frame is 0x10 larger.

Matched 19/30; .text 96.48%.
