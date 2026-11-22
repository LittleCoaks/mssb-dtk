# game/game/fielding/fielder checkpoint

## Catch strategy section

Baseline (objdiff diff, 2026-11-02): unit n100 140/231 (diff count).

| function | status | pct |
|---|---|---|
| fielderMovement_findWallBounceInterceptSpot (was fn_3_50898) | matched | 100% |
| fielderMovement_adjustPlaceToStandForBallBouncingOffWall | exhausted | 99.27 (report) |
| fielderMovement_updateWallBounceApproach (was fn_3_50DD8) | matched | 100% |
| setFielderCatchStrategy_calcFramesToGetToDropSpot | exhausted | 97.09 (report) |
| setCatcherCatchStrategy_distToLandingSpot | exhausted | 94.93 (report) |

### fielderMovement_adjustPlaceToStandForBallBouncingOffWall
  baseline 98.78 (only FPR alloc in the two x/d,z/d push-out blocks)
  [1] commute 10+d -> d+10, split decl  -> 98.78 (no change)
  [2] z/d local only, x inline -> 98.42
  [3] dist local for division -> 98.78
  [4] x=pos.x; z=pos.z; x/=d; z/=d inline -> 98.91; z decl first -> 99.09
  [5] same as static inline helper pushOutFromHome(fielder,outX,outZ) -> 99.27 (kept)
  [6] helper with (x,z) params -> 98.78; helper variants z-first / dist local -> <=99.27
  remaining: target loads pos.x into f0 and divides into f4 (not in place), dist f3; ours x in place f3, dist f4.

### fn_3_50DD8
  baseline 96.19
  [1] last block: dx/dz stored into tempX/tempZ (target writes them to the 0x14/0x10 stack slots), tempX*=t -> 99.23 (kept)
  [2] return-1 paths share one exit: if(flag==0){..}else if(!_020E){..}else{..} return 1; -> 100 (kept)
  readability pass: done (FIELDING_POSITION_*). _020E/aiDistToStandFromWallCollision left as-is (latter is both 0/1 flag and a frame counter compared against lbl_3_data_48A4[2]).
  final source: commit "fielder: match fn_3_50DD8 ..."
### fn_3_50898
  readability pass: done (FIELDING_POSITION_*). goto return1 measured: plain return 1 -> 97.59, goto stays (exit threading).

### setFielderCatchStrategy_calcFramesToGetToDropSpot
  baseline 89.98
  [1] LOGIC (real bugs): threshold & resultCode-1 test use hitbox[3] (0xF4), not distanceFromHomePlate; framesToGetToBallLandingSpot = frame (no + framesSinceHit); framesNeeded uninitialised; step=5 at decl; delayFrames int
  [2] three hand copies of the frames-to-reach calc -> fRunningTimeToDestinationPlus7() calls (inlined, no bl)
  [3] found/bestHeight: `if (found && bestHeight < y) {break}` + update; closeEnough as if(2..5 && dist>5+d){if(<frame+10)} else {=1}
      [1]-[3] -> 95.36
  [4] tail: index futureCoordsAndDist[frame] directly, zone `int zone = (u8)setZoneAwayFromHome(..)` (target clrlwi + cmpwi) -> 95.77
  [5] getDifferenceInAngle(angle, playerAngleFromHome) arg order; `int arrival = frames + throwFrames; x-20 > arrival+20` -> 96.30 (kept)
  [6] local CoordAndDist* coords only in landing-dist block -> 96.52 (not kept: artificial); coords for whole tail -> 95.06
  [7] static inline distanceFromLandingSpot(x,z) helper -> 96.29 (reverted)
  open: target keeps &futureCoordsAndDist[0].pos.x / .pos.z as callee-saved bases r28/r29 from the landing-dist block to the end (lfsx with r0=frame<<4); ours folds g_Ball+frame*16 in that block and rebuilds bases in the final block.
  note: knockoutRelated_subFn (outside section) moved 88.09 -> 86.75 from shared float-pool reuse (99.0f/4.5f now pooled like target)
  [8] loop: drop futureCoord pointer, index futureCoordsAndDist[frame] directly (target keeps &..[frame].pos.y in its own reg) -> 96.80 (kept)
  [9] fRunningTimeToDestinationPlus7 helper decl dx before dz -> this fn 96.75, helper 100->99.68, mixed elsewhere (reverted)
  [10] declaration-order random swap walk (40 iters) -> 96.965 (kept: frame, delayFrames, framesNeeded, bestFrame, step, bestHeight, found, closeEnough, lastFramesNeeded, startFrame, resultCode, threshold)
  [11] removing the final block entirely: landing block still folds g_Ball+frame*16 -> the base form is intrinsic to the landing block expression
  [12] `coords = futureCoordsAndDist` pointer for whole tail (assigned after loop) -> 96.93; base now shared to final block but x/z still disp off one reg (reverted)
  [7] more helper-body variants (x via separate local, z in place; shared d local) -> <= 99.27. exhausted.
  readability: FIELDING_POSITION_* done.

### setCatcherCatchStrategy_distToLandingSpot
  baseline 87.16 (diff) / 87.71 (report)
  [1] REAL BUG: framesToGetToBallLandingSpot = frame (no + framesSinceHit) -> 89.16
  [2] fRunningTimeToDestinationPlus7 call instead of hand copy -> 91.33
  [3] loop indexes futureCoordsAndDist[frame] directly (no futureCoord ptr) -> 96.97 (diff)
  [4] REAL BUG: landing-dist block indexes [frame] (target slwi of frame reg), not [framesToGetToBallLandingSpot]; `arrival` local for throw test -> 93.85 (diff numbers shift with alignment)
  [5] `startFrame + t - 5` (vs startFrame + (t - 5)) -> 94.35
  [6] decl-order swap walk -> 94.63 (diff) / 94.93 (report) (kept)
  [7] landing block as inline futureBallDistToLandingSpot(frame) -> 93.84 (rev); (&..[0].pos.x)[frame*4] -> same tree, no change
  [8] hand-written body with function-scope dx/dz/dist reused in landing block -> 92.44 (rev)
  open (shared with calcFramesToGetToDropSpot): target landing block emits addi base+0x354/+0x35c, addi of the 0.0f const, lfsx with frame<<4, and reuses those bases in the throw-check block. Ours folds g_Ball+frame*16 with displacements. Not reproduced by pointer locals, helpers, or tree reshaping.
  readability: TRUE/FALSE flags done. catchStrategy values 1..4 enum-shaped, no enum exists (not invented).

### setFielderCatchStrategy_calcFramesToGetToDropSpot (cont.)
  [13] setZoneAwayFromHome retyped to return u8 (drops the cast) -> this fn same, ball_physics classifyHitTrajectoryOrHitAnimRelated 99.88 -> 99.10 (reverted)
  status: exhausted at 96.965 diff / 97.09 report. readability: BALL_ZONE_*, FIELDING_POSITION_*, TRUE/FALSE done.
  g_RunningLogic offset 0xE read as (&runnersByCurrentBaseMask)[5]: falls in artificial padding after runnerTransferIndex[4]; real field unknown, left as is.

## Going after the hit ball section

Baseline (report rep_v120): setIntendedLocToInterceptBall 89.52, fielderTrackingBall_updateVariables 93.41,
fielderTrackingBall_initialVariableSetting 96.74, decideWhenToLeaveFunction2_16_18 99.99; other 7 at 100.

| function | status | pct |
|---|---|---|
| setIntendedLocToInterceptBall | exhausted | 99.87 |
| fielderTrackingBall_updateVariables | exhausted | 99.98 |
| fielderTrackingBall_initialVariableSetting | matched | 100 |
| decideWhenToLeaveFunction2_16_18 | matched | 100 |

### setIntendedLocToInterceptBall
  baseline 89.52
  [1] loop body = fRunningTimeToDestinationPlus7 call; direct futureCoordsAndDist[] indexing in setFielderAutoCoords args -> 98.99
      (pointer local for the final setFielderAutoCoords -> 96.62, reverted)
      side effect: function goes under inline cap, inlines into fielderAIAssignmentRelated_finish, which then stops
      inlining into fielderAIAssignmentRelated (100 -> 79.6). Fix: #pragma dont_inline on around it.
  [2] goto found instead of `if (frame > 120)` after loop (target has no re-test) -> 99.87 (kept). committed.
  remaining: inlined helper dx in f1, dz in f3 (target dx f3, dz f1) - known cross-section helper issue.
  [3] caller: CoordAndDist* c local for the call args -> 99.36 (rev)
  [4] helper fRunningTimeToDestinationPlus7 body variants, scored across all 7 inlining callers:
      no dxSq/dzSq temps -> all worse; decl order dist-first / dzSq,dxSq-first -> no change anywhere;
      dx=x; dx-=pos.x -> no change; single-exit result var -> no change; speed=jogging; if(0==speed) -> standalone 97.7.
      None moves the inlined dx/dz swap. status: exhausted at 99.87.

### decideWhenToLeaveFunction2_16_18
  baseline 99.99 (one branch target)
  [1] REAL BUG: `fielderIndex >= 6 || dist > holder dist` (was `< 6 &&`) -> 100. matched, committed.
  readability pass: done (FIELDING_POSITION_*, DEAD_BALL_REASON_NONE, BALL_ZONE_*, TRUE). AI_Ind / nonCatchFlyBallStratInd left.
### fn_3_42BD0 -> fielderTrackingBall_checkSwitchToIntercept (medium, applied). readability: FIELDING_POSITION_LEFT_FIELD, 90.

### fielderTrackingBall_initialVariableSetting
  baseline 96.74
  [1] wall blocks written into targetX/Z (address-taken) -> 94.93 (target keeps targetX/Z in FPRs; rev)
  [2] one function-scope outX/outZ pair for every wall block (incl. the >=2 block's dx/dz) and for the
      default nudge (out = target / target+0.5*norm) + updateWallBounceApproach(&outX,&outZ); wall test inline -> 99.19
  [3] nudge as if (distAlt <= 0.1f) {copy} else {offset} -> 100. matched, committed. No behaviour change.
  readability pass: done (FIELDING_POSITION_*, CAPTAIN_STAR_TYPE_YOSHI/BIRDO, TRUE/FALSE). catchStrategy 1..4 no enum.
  goto tail kept (4 paths join the tail; exit threading).

### fielderTrackingBall_updateVariables
  baseline 93.41 (report)
  [1] final block -> fRunningTimeToDestinationPlus7 call -> 94.19
  [2] function-scope f32 x, z (address-taken) for all blocks; foul/state-0 blocks repeat the full
      futureCoordsAndDist[fielder->framesRemainingToGetToLandingSpot].pos.x/.z expression at every use
      (no CoordAndDist* / cx,cz locals) -> 99.76. THIS gives target's addi +0x354/+0x35c bases + lfsx frame<<4.
      Lead for setFielderCatchStrategy_calcFramesToGetToDropSpot / setCatcherCatchStrategy_distToLandingSpot.
  [3] foul nudge if (x < 0) x += 10 else x -= 10 -> 99.93 (kept, committed)
  remaining: inlined goToFutureBallPos (state 4) x/z FPR swap; inlined fRunning dx/dz swap; n-2 tail regs.
  [4] REAL BUG: framesRemainingToGetToLandingSpot = g_Ball.framesUntilBallHitsGround - 2 (was n - 2) -> 99.95
  [5] goToFutureBallPos: coords passed straight to setFielderAutoCoords (no x/z locals) -> 99.98, standalone stays 100 (committed)
  remaining: only the inlined fRunningTimeToDestinationPlus7 dx/dz swap.
  [6] more fRunningTimeToDestinationPlus7 body variants (scored over all 8 inlining callers): dx/dxSq interleaved,
      dz before dx, dolsqrtf2 instead of fielderSqrt, fielder-pointer decl after dx/dz -> no change anywhere;
      g_Fielders[idx].pos direct -> all worse; inverted early test (if (differs) {...} return 1) -> all worse.
  status: setIntendedLocToInterceptBall 99.87 and fielderTrackingBall_updateVariables 99.98 exhausted; both differ
  only by the inlined fRunningTimeToDestinationPlus7 dx/dz FPR swap (target dx in fx's reg, dz in x's reg).
  section after: 9/11 at 100, ~99.98% (size-weighted), ~2.4 wrong bytes. unit report 98.35%, 137/225.
  readability pass over whole section: done (FIELDING_POSITION_*, DEAD_BALL_REASON_NONE, BALL_ZONE_*, TRUE/FALSE,
  CAPTAIN_STAR_TYPE_*). Left: maybeMovementState 0..5, catchStrategy 1..4, ballBounceState 3 (no enums exist).

## Facing/collisions section

Baseline (report rep_v121): setStandingOnBaseVariables 92.19, setFielderVelocity 94.74, updateSprintPointers 96.70,
minigameFieldingRelated_collisions 97.67, adjustPlayerPosOutsideFoulLine 98.25, fn_3_52084 98.31,
updateFielderDirectionFacing 98.66, fielding_handleCollisionsAndSpecialActions 99.49,
updateFielderPosition_checkFielderCollision 99.72, updateFielderPositionAndVelocityForSpecialActions 99.97; 6 others 100.

### setStandingOnBaseVariables
  baseline 92.19 (report)
  [1] both hand-written release blocks -> releaseCoverAssignment(fielderIndex) / releaseCoverAssignment(assigned[i]);
      first block re-reads fielder->locationResponsibleForCovering (no s16 loc local) -> 94.83 report (committed)
  [2] found block as inline takeOverBaseCoverage(fielderIndex, base) -> no change (rev)
  [3] `int other = assigned[i]` local -> no change; i at function scope -> no change; store order swap -> 94.63;
      if (threshold > dist) {..break;} instead of continue -> no change
  remaining: loop found-block: target keeps addi base+0xd0 + lhax/sthx with i*2 in r0 (needs r31); ours add+lhau.

### setFielderVelocity
  baseline 94.74 (report)
  [1] REAL BUG: tag-chase velocity = dist - 1.2 in both arms (else arm used raw dist); else arm stores divided/undivided separately -> 97.2
  [2] drop redundant `if (code <= 13)` guard around switch (target single bgt). [.data-0] jumptable reloc offsets drop until
      prologue matches (artifact).
  [3] fielder = &g_Fielders[fielderIndex] instead of byte-offset local -> 97.75; stop blocks -> stopFielderAtCurrentPosition() -> 98.82
  [4] g_Runners[idx].position.x/.z directly (no runner ptr) -> 99.81
  [5] if (!(currentVelocity <= 0.0f)) -> 100. matched, committed.
  [6] structured else-if instead of `goto switchSection` -> 99.13 (rev; gotos stay)
  readability pass: done. Left: autoMovementFunctionIndex 0x12 (18, no enum member), maybeMovementState 4/5,
  tagResult_1out_2safe == 1, fielderAutoMovementCode 0xb (no enums).

### updateSprintPointers
  baseline 96.70
  [1] operand order variants (boost*ratio, 1+..., boost local) -> no change; charge*boost/max -> 94.25
  [2] f32 ratio = charge/max local; mult = ratio * boost + 1 -> 100. matched, committed.
  readability pass: done (DASH_STATE_SPRINTING, TRUE). sprintingState 0/1/3/4 have no enum members; practiceLevel 2 left.

### minigameFieldingRelated_collisions
  baseline 97.67
  [1] REAL BUG: star-dash transfer paths `continue` (target b to loop increment), not goto the collision re-checks -> 97.70
  [2] split decls + decl-order swap walk (60 iters) -> 97.77 (not kept)
  [3] VecXZ collisionPoint -> f32 cx, cz -> 97.95
  [4] second dx2/dz2/dist2 reuse dx/dz/dist -> no change
  [5] cx = frac * (inner.x - outer.x) + outer.x directly (no dx = outer; dx = inner - dx) -> 98.36; outer.x + frac*(..) same
  [6] normal divided in place (dx /= dist) instead of nx/nz -> 99.15 (committed 3da1ea0, merged dafaa78)
  [7] decl swap walk (50) on [6] -> no gain
  remaining: target cx/cz in f0/f1, normal in f2/f3, frac f6; ours swapped (normal f0/f1, cx/cz f2/f3, frac f2).
  [8] dx/dz = inner-outer kept as locals for cx/cz -> 98.71; dist2 into frac -> no change; sumRadius inlined -> no change.
  status: exhausted at 99.15 (FPR coloring only).

### adjustPlayerPosOutsideFoulLine
  baseline 98.25
  [1] decl swap walk -> 98.61 (x, negX, moundZ, moundX, z, d)
  [2] gotos -> if (!(d > x) && !(d > (negX = -x))) {..} -> 98.61 same; negX = -x hoisted before if -> 96.27
  [3] no negX local, -x inline everywhere -> 98.61 (kept, committed)
  [4] second block writes moundZ - z into z in place (no d) -> 97.23 (+ decl walk 97.59)
  [5] half temps inlined into expressions -> 91.75
  remaining: z in f5 vs target f2 (target -x temp in f5). status: exhausted at 98.61.

### fn_3_52084 -> fielderPathDistanceToPoint (medium, applied)
  baseline 98.31
  [1] REAL BUG: perpDistSq < 0 -> return 0.0f (draft fell off the end) as early return -> 99.80
      (else-return form 99.07; >= form 98.68)
  [2] standing branch writes x = pos.x - x; z = pos.z - z in place -> 100. matched, committed.
  readability pass: done (nothing enum-shaped). No callers anywhere in game module.

### updateFielderDirectionFacing
  baseline 98.66
  [1] runner pointer local for runnerBeingTargettedForOut atan2 -> 99.09
  [2] dugout test: `0.0f != cv` -> no change; `!(cv == 0.0f)` -> no change; bare `fielder->currentVelocity &&` -> 99.11 (kept, committed)
  [3] body-check base block: ATAN2F inline args, prevBase inline, int/u8 base local, dz-first, dx -= form (99.12, not kept),
      VecXZ* from/to (98.78), fromX local -> none match. Remaining: target loads both .x via lfsx before the
      address adds; ours interleaves. status: exhausted at 99.11.

### fielding_handleCollisionsAndSpecialActions
  baseline 99.49
  [1] block-scope extern order (all 6 permutations) -> no change
  [2] no SND_FXID fid local; stadiumHazardSoundIDs[n] + k passed straight to sndFXStartEx -> 99.74
  [3] decl swap walk -> 100 (vol/val first, int i last). matched, committed.
  readability pass: done (SND_MIDICTRL_REVERB). pan 0x3f, wallJumpStatus 1..4, lbl_3_data_84B8 (toy-field sound table) left.

### updateFielderPosition_checkFielderCollision
  baseline 99.72
  [1] decls one per line, weightedNormalX/Z before unitNormalX/Z -> 99.87
  [2] baseZ before baseX -> 99.97
  [3] ray stores: dst.x/dst.z = base, src = base + off, then dst -= off -> 100. matched, committed.
  original-game quirk kept: out = weightedNormal * weight + collision pos (weight applied twice; target does the same).
  readability pass: done (BALL_COLLISION_TYPE_* already used; 0x7F type mask has no named constant).

### updateFielderPositionAndVelocityForSpecialActions
  baseline 99.97 (only the final `lockoutDuration < framesSinceHit` load registers r4/r0 swapped)
  [1] operand order swapped, int lockout local, s16 frames local, !(<=)/!(>=), if/return 1/0 -> all unchanged
  [2] (u32)(a - b) >> 31 -> 99.16; g_Fielders[idx].lockoutDuration -> 97.90
  status: exhausted at 99.97. readability: MINI_GAME_ID_PIRANHA_PANIC/STAR_DASH applied (committed); autoMovementFunctionIndex 0xc, anim value 0x11..0x1c left.
### setStandingOnBaseVariables (cont.)
  status: exhausted at 94.83 report. Lead: the loop's found-block base addressing (addi base+0xd0 / lhax / sthx
  with i*2 kept in r0, needs r31) - not reproduced by helper wrapping, locals, or loop reshaping.

### Facing/collisions section status (report rep_f10, after merge with Ball holder)
| function | status | pct |
|---|---|---|
| setFielderVelocity | matched | 100 |
| updateSprintPointers | matched | 100 |
| fielderPathDistanceToPoint (was fn_3_52084) | matched | 100 |
| fielding_handleCollisionsAndSpecialActions | matched | 100 |
| updateFielderPosition_checkFielderCollision | matched | 100 |
| updateFielderPositionAndVelocityForSpecialActions | exhausted | 99.97 |
| minigameFieldingRelated_collisions | exhausted | 99.15 |
| updateFielderDirectionFacing | exhausted | 99.11 |
| adjustPlayerPosOutsideFoulLine | exhausted | 98.61 |
| setStandingOnBaseVariables | exhausted | 94.83 |
  section: 11/16 at 100, 99.14% size-weighted, ~138 wrong bytes (was ~390). unit 98.66%, 144/225.

## Cutoffs section (Auto-movement: cutoffs and relays; Opus pass, 2026-11)

Baseline (rep_v133): autoMovement11 99.84, setInitialFielderMovements_cutoffs 95.07, setCutoffLocationToStandAt 97.43,
checkIfCutoffIsntAtThrowDestination 97.99, updateFielderValuesSubFunction1_cuttoffRelated 91.32, autoMovement25 99.69,
fn_3_4597C 99.54; autoMovement5, fn_3_483CC, fn_3_480B8, fn_3_47628, fn_3_468DC, fn_3_46688 at 100.

| function | status | pct |
|---|---|---|
| updateFielderValuesSubFunction1_cuttoffRelated | matched | 100% |
| setInitialFielderMovements_cutoffs | matched | 100% |
| setCutoffLocationToStandAt | matched | 100% |
| setFielderAutoCoordsOnThrowLine (was fn_3_4597C) | matched | 100% |
| autoMovement25_readyToInterceptThrownBall | matched | 100% |
| autoMovement11_cutoff_setInitialLocation | matched | 100% |
| checkIfCutoffIsntAtThrowDestination | exhausted | 97.99% |

### updateFielderValuesSubFunction1_cuttoffRelated
  baseline 91.32
  [1] fielderAutoMovementCode scan loops moved inside the zone<3 else (target's zone>=3 branch jumps past them);
      bestDist = 0.0f init; bestCandidate = candidates[j]; both hand copies -> setFielderAutoMovementIfValid(.., 11);
      second branch `if (dist < X) {...; return;}` -> 94.67 (kept)
  [2] bestDist = 0.0f hoisted next to count = 0 -> 97.16 (kept); candidates[count++] = pos -> 95.17 (reverted)
  [3] candidates init 2,1,0 order; `cutoffFielderIndex == pos` -> 97.19 (kept)
  [4] drop u8 locals in both scan loops (index directly) -> 97.79 (kept); dropping `code` in candidate loop: no change
  [5] bestDist init after candidates init -> 97.86; drop InMemFielder* cf in j loop -> 98.39 (kept)
  [6] `if (count == 3) break;` outside the if (target's failing test jumps to the count check) -> 100
  readability pass: done (BOOL flag, FIELDING_POSITION_*, BALL_ZONE_*, AUTO_MOVEMENT_* in the movement-index test).
  Left alone: locationThrownTo == 6 / locationResponsibleForCovering == 6 (cover-location index, no enum).

### setInitialFielderMovements_cutoffs
  baseline 95.07
  [1] the two `else if (code != 0) {assign} else {assign; setFielderAutoMovement}` arms are one arm:
      `assign; if (code == 0) setFielderAutoMovement(.., 11);` -> 99.99
  [2] REAL BUG: the pitcher block (location 15, intended spot, auto movement 14) sat outside the
      hitClassification2 in {5,6,8} test; target returns early when the test fails -> 100
  Pointer-form fielderTrackingBall_applyIntendedLocation stays (matches at 100).
  readability pass: done (FIELDING_POSITION_*, FALSE). Left alone: hitClassification2 values 5/6/8 (no enum),
  cover location 6 / 15 / 1 / 3, movement codes 1/10/11.

### setCutoffLocationToStandAt
  baseline 97.43
  [1] `(x - baseX) * 0.5f` / `* 0.25f` -> `/ 2.0f` / `/ 4.0f` (MWCC turns power-of-two division into a multiply
      with the operands in the target's fmadds order; every `*0.5f` spelling gave the swapped order) -> 97.64
  [2] base proximity loop as `for (i = 1; i < 4; i++)` over base_MoundCoordinates[i] (bdnz, no hoisted *outZ) -> 99.50
  [3] baseX/baseZ read straight from base_MoundCoordinates[idx] (lfsx) -> 99.99
  [4] stack-slot order of the three fielderSqrt temps: the human-team branch is an inlined copy of fn_3_46688.
      Plain call: bl survives (72.8, also with inline_max_size 2000 file-wide or push/pop). `inline s32 fn_3_46688`
      (also extern inline/__inline/force_active): inlines, but the standalone symbol disappears.
      fn_3_46688 { return helper(); }: setCutoff 100 but fn_3_46688 99.80 (r7/r8 swap; local-placement variants
      no help). Kept: static inline copy estimateBallSpotForCutoff used only here; fn_3_46688 keeps its body -> 100
  readability pass: done (BOOL found, TRUE/FALSE). Left alone: baseCuttoffIsTargeting 0..4 (base index, no enum).

### fn_3_4597C -> setFielderAutoCoordsOnThrowLine (medium, applied) + autoMovement25 (inlines it)
  baseline 99.54 / 99.69
  [1] a[1].x = throwTarget first: 99.48 (reverted); vx before vz: no change
  [2] vz/vx computed from the filled array (`a[1].z - a[0].z`) after filling it -> 100 / 100
  [3] re-check: passing out.x/out.z directly -> 99.77 (kept x/z locals); `+ -vz` without negVz -> 92.4 (reverted)
  name: computes the intersection of the throw line (ball -> throwTarget) with the perpendicular through the
  fielder, i.e. the nearest point on the throw path, and sets the fielder's auto coords there; only caller is
  autoMovement25_readyToInterceptThrownBall's first frame. Medium: behaviour clear, original name unknown.
  autoMovement25 readability: TRUE/FALSE, FIELDING_POSITION_NONE, `if (idx != -1) setFielderAutoMovement` ->
  setFielderAutoMovementIfValid (still 100). Left alone: auto movement 9, fielderTrackingBallState 0/1.

### autoMovement11_cutoff_setInitialLocation
  baseline 99.84
  [1] both hand-written cover-release blocks -> releaseCoverAssignment(fielderIndex) -> 99.97
  [2] old-cutoff distance read as g_Fielders[oldCutoffIdx].distanceFromAutoLocation (no pointer local) -> 100
  [3] goto removed: `if (dist < old) {...} else {stop}` structured form, all `if (i != -1) setFielderAutoMovement`
      -> setFielderAutoMovementIfValid -> still 100
  readability pass: done. Left alone: locationThrownTo 6, auto movements 5/12, unknown_writeOnly 4,
  isResponsibleForCoveringALocation (takes 0/1/2, so not a BOOL).

### checkIfCutoffIsntAtThrowDestination
  baseline 97.99. Logic identical; only FPR numbering. Target colours predX into the register of the loaded
  AtBat_Contact_BallPos.x (f0) and predZ into t's (f7), so every later FPR is one higher than ours; ours puts
  predX into velocity.x's register. Target sums sqx + sqz (ours sqz + sqx), but switching alone scores 97.82.
  The twin checkIfPlayerNeedsToMoveToCatchBall (outside this section, 97.99) has the identical mismatch.
  [1] sqx + sqz -> 97.82 (reverted)
  [2] all 16 operand orders of `vel * t + pos` for predX/predZ -> 97.75..97.82
  [3] declaration-order permutations incl. t at top (5 perms) -> 97.65..97.82
  [4] no t local / t reused as dist -> 97.82
  [5] predX/predZ as a VecXZ local -> 97.73
  [6] `predX = pos; predX += vel * t;` -> 97.87
  [7] static inline helpers: distance (pointer and index forms) 97.82; prediction via out-pointers 97.82;
      distance+move with predicted point passed as args 97.73; whole frame-5 block with its own fielder 97.75
  [8] dx*dx + dz*dz without sq locals 96.94; no dx/dz locals 97.82/97.88; dist = sum; dist = sqrt(dist) 96.75
  next: only a new idea about MWCC FPR colouring; fixing it here should fix the twin too.

## Per-frame section (Per-frame update and live-ball control; Opus pass, 2026-11)

Baseline: report rep_v135 (unit 98.96%).

| function | status | pct |
|---|---|---|
| fielding_updateAllFieldersPostMovement | matched | 100 (was 93.27) |
| liveBallFielderControlAITeam | matched | 100 (was 98.74; lifted by the above) |

### fielding_updateAllFieldersPostMovement
  [1] g_Fielders[idx].pos.x at first use only -> no change (CSE to pointer)
  [2] all uses g_Fielders[g_Ball.fielderWBallIndex] -> 87.9 (reloads after g_Ball stores)
  [3] x/y/z f32 locals -> stops inlining into callers (size); sqx/sqz locals no
  [4] i = idx; g_Fielders[i] everywhere -> lfsx ok but fmadds; sqrt of landing spot -> 93.97
  [5] mirror ball_physics.c: landing = AtBat_Contact_BallPos, VEC_LENGTH_XZ(&AtBat_Contact_BallPos) -> callers 100, fn 94.74
  [6] loop: g_Fielders[i] direct instead of pointer -> 100 and still inlines (pointer-in-loop form 100 but too big to inline)
  readability pass: done (no constant for 9 fielders exists)
| fn_3_555AC -> updateFielderInBasePath (medium, applied) | matched | 100 (was 98.03) |

### fn_3_555AC / updateFielderInBasePath
  [1] decl-order permutations of posX/posZ/lo/hi -> best 98.65 (posX first)
  [2] no posX/posZ locals (fielder->pos.* direct) -> 100
  [3] caller updateFielder_SpecificValuesEachFrame: call fn_3_555AC -> never inlined (bl), 91.3; even with inline_max_total_size/inline_max_size raised
  [4] static inline helper(InMemFielder*) with lo/hi at function scope -> caller copy exact (98.12->98.34 fn); wrapper fn_3_555AC(idx){helper(&g_Fielders[idx]);} = 93.27, so standalone keeps a copy of the body
  readability pass: done. inBasePath 0..4 is enum-shaped (base path segment) but no enum exists.
| updateFielder_SpecificValuesEachFrame | matched | 100 (was 97.70) |

### updateFielder_SpecificValuesEachFrame
  [1] base-path block -> setInBasePathFromPosition(fielder) static inline -> 98.41
  [2] REAL BUG: framesSinceHit>60 latch is lineDriveThroughPitcherInd (0x1BCE), not deadBallReason; last arm one || chain -> 98.66
  [3] REAL BUG: missing distanceFromEachFielder[fielderIndex] = 0.0f before pair loop; loop via g_Fielders[i] -> 99.90
  [4] zone block: decl orders / block locals / separate dist vars -> no change (stack slots of isnan temps show it's an inline: zone sqrt temps get lowest slots)
  [5] inline getOutfieldZoneCode(x, z), no sqx local (x*x at both uses) -> 100
  readability pass: done (FIELDING_POSITION_*, setFielderAutoMovementIfValid(…, 19)). outFieldZoneCode 0..4 enum-shaped, no enum.
| fielder_endOfInning_deadball_updateCounters | matched | 100 (was 96.12) |

### fielder_endOfInning_deadball_updateCounters
  [1] setFielderAutoMovementIfValid in the 3 loops -> 95.89; + g_Fielders[i] direct -> 99.74
  [2] held-ball block g_Fielders[g_Ball.fielderWBallIndex] direct -> 100 (j loop must stay separate var: reusing i -> 98.72)
  readability pass: done (AUTO_MOVEMENT_GOING_TO_BALL; 17/12/0 have no enum members)
| aITeamFielding_SelectCharWithHand | matched | 100 (was 97.39) |

### aITeamFielding_SelectCharWithHand
  [1] REAL BUG inverted fielderWBallIndex test; pitcher check direct (no u8 local) -> 98.75
  [2] decl order dist,minDist,secondMinDist -> 99.76; chained init (a = b = 999.9f; best = second = -1) -> 100
  readability pass: done (autoMovement 3/4 have no enum members)
| processFielderJumpAI | matched | 100 (was 97.92) |

### processFielderJumpAI (diff was all in inlined startFielderJump, other section)
  [1] jumpCountDown = (apexDiv + 1) + (apexDiv + 1) + frames3 -> 99.76 startFielderJump (a*2, 2*(a+1), reorders worse)
  [2] 0.1f as f32 local horizontalScale -> fmuls operand order; startFielderJump/tryStartFielderJump/moveFielder_CheckForAndSetJump/processFielderJumpAI all 100
  readability pass: done
| updateOutfielderPositionBasedOnBallState | matched | 100 (was 99.78) |

### updateOutfielderPositionBasedOnBallState
  [1] ternary index / if-else index -> 93.31; idx = fielderIndex = sel chain -> 99.78
  [2] int idx = g_FieldingLogic.selectedFielder (second read of the global) -> 100
  gotos kept: six conditions thread to one setFromFutureCoord block plus a shared checkIntercept tail (exit-block threading).
  readability pass: done
| liveBallUpdateFieldingValues | matched | 100 (was 99.50) |

### liveBallUpdateFieldingValues
  [1] loop pointer local -> g_Fielders[i] direct (or pointer assigned inside the loop) -> 100. Same lever as PostMovement: a `for (p = base, i = 0; ...; p++)` pointer gives `addi r0; mr rX, r0`.
  readability pass: done
| updateFielderMovementAndPosition | matched | 100 (was 95.73) |

### updateFielderMovementAndPosition
  [1] dx/dz merged into the address-taken outX/outZ pair -> 99.36; targetX/Z merged too -> 99.81 (all 120 decl orders of dist/sqx/sqz/x/z: max 99.81)
  [2] drop sqx/sqz locals (fielderSqrt(x * x + z * z)) -> 100
  readability pass: done

Per-frame section status (report rep_p11, 2026-11): all 13 functions 100%. Unit 98.96 -> 99.15, 153 -> 168/225 matched.
Outside the section, lifted by shared helpers: fn_3_2EA88, minigameDashUpdateFieldingVals, startFielderJump,
tryStartFielderJump, moveFielder_CheckForAndSetJump -> 100; minigameDashUpdateFieldingVariables 97.09 -> 97.70;
liveBallFielderControlHumanTeam 96.11 -> 96.90.

## Cleanup pass (Opus, 2026-11; baseline rep_v136 unit 99.15%, 168/225)

### Step 1: fRunningTimeToDestination inlined dx/dz swap -> FIXED (rep_c101)
  variants (scored across all callers): direct g_Fielders[idx].pos everywhere (no pointer) -> helper 80.5, all worse;
  same with -(pos - x) -> 82.8; with pointer: -(pos-x) -> 97.6 all worse; pos - x both -> 99.79 all worse;
  pos - x for one only -> 99.89; stmt order dz-first -> no change (scheduler); decl dx,dz -> 99.68 (knockouts +0.1).
  inner inline tdist2(dx,dz) / tdist4(x1,z1,x2,z2) / tdistF(fielder,x,z) with dz,dx decls -> helper 99.68 (inline pattern
  now in standalone too: decl order inside a nested inline is effectively reversed). Same with dx,dz decls -> helper 100,
  all callers fixed in FPRs but isnan stack slots shuffled (sqrt in nested inline).
  WIN: static inline f32 fielderDistSqToPoint(InMemFielder*, x, z) {dx; dz; dxSq; dzSq decls; return dxSq + dzSq;}
  and dist = fielderSqrt(fielderDistSqToPoint(fielder, x, z)) in the helper -> helper 100,
  setIntendedLocToInterceptBall 100, fielderTrackingBall_updateVariables 100, foul 99.97, calcKnockout 99.94,
  FlyBall 99.48, Grounder 99.65, catcher 95.01, calcFrames 97.20, aheadOfBallPath 99.56. committed.

### catch-strategy pair (cleanup)
  setCatcherCatchStrategy_distToLandingSpot 95.01 -> 99.84: throw-check block reads
  `int landingFrame = fielder->framesToGetToBallLandingSpot; f32 lx/lz = futureCoordsAndDist[landingFrame]...` (copied from
  calcKnockoutCatchStrategy, whose identical tail already matched). That alone gives the landing block the target's
  addi +0x354/+0x35c bases + lfsx. (landing block indexed by fielder->framesTo... instead -> 98.45, reverted.)
  remaining: loop element pointer r4/r5 swap; final `runner + 30 > arrival + 60` cmpw operand order (same as calcKnockout).
  setFielderCatchStrategy_calcFramesToGetToDropSpot 97.20 -> 98.82: angle call via `int landingFrame` local, arrival block
  re-reads into its own `int catchFrame` + lx/lz locals (target reloads 0x186 twice, bases r28/r29 shared through the tail).
  Tried: lx/lz only in arrival (98.32), angle+arrival share landingFrame (98.27), lx/lz for angle too (94.5), zone/landing
  indexed via fielder->framesTo (96.0-97.06), arrival full exprs (96.38).
  remaining: loop GPR numbering (frame r10 vs r6 etc.), inlined setZoneAwayFromHome FPRs, final cmp operand order.
  calcKnockoutCatchStrategy final cmp: `arrival + 60 < runner + 30` -> regs right but cmpw/branch reversed (99.955 vs 99.94);
  + 60 folded into arrival / no local / est-only local / `-` forms -> worse. Not kept.
  setIntendedLocationAheadOfBallPath (99.56, `mr r4,r5` + late addi): CoordAndDist* for the in-air block (98.2), &future->pos
  (98.4), z-first assignments/decls, frame local, futureZ = futureX + 2 -> none better.
  decideHowToTrackFoulBall (99.97, abs diff r3/r0): abs split/sign local/__abs/ABS()/no angle local/s16/func-scope diff -> no change or worse.

### Cleanup pass, session 2 (Opus; baseline report r0 = unit 99.225%, 170/225)
updateSomeAutoMovementAssignments 95.55 -> 95.78
  [1] first loop: drop the s16 fielderIndex local, read fielderAssignedLocationIndex[i] at every use (CSE gives the
      target's r11 for the index) -> 95.42 alone; + decl-order walk (problemOutfieldBase, fielder, numAssigned, dists,
      bests, code, i) -> 95.73; first loop now exact.  hoisting fielderIndex/code to function scope, separate `base`
      counter for loop 1 -> no change. `int fielderIndex` -> 91.4; s16 local everywhere -> 95.46.
  [2] float chains `dist8 = dist7 = 999.9f` (both) -> 95.75; decl `f32 dist9, dist7, dist8` -> 95.78 (kept)
  [3] int chain orders / `best7=-1; best8=best7; best9=best7` -> still 3 li (target li+mr+mr), no change.
      best decl order 7,8,9 -> 95.57.
  [4] nested inline fielderDistSqFromBase(fielder, base) for the 3 base distances: plain -> 94.26, dz-first/xz params/
      whole-sqrt -> 94.26, dxSq/dzSq locals -> 95.73 (= no helper). reverted.
  remaining: best9/best7 GPRs swapped (r7/r9); dist8/dist7 sqrt result computed in f6 + fmr at join (target computes
  straight into the var's reg); 3rd/4th blocks (loop with newFielder, inlined releases) GPR numbering.
setStandingOnBaseVariables 94.83 (no change this session)
  [4] loop found-block: `s16* assigned = g_FieldingLogic.fielderAssignedLocationIndex` base pointer, `s16* slot =
      &..[i]` -> no change (MWCC canonicalises, still add+lhau); store via [fielder->locationResponsibleForCovering]
      -> 93.95; fn_3_4B8D0 instead of releaseCoverAssignment (loop/first/both) -> identical code.
divingCatch 98.85 (no change)
  shape: hasSuction gets r16 in target, r27 in ours (r17..r27 all shifted by one); searchBackward loop's 0.07 test:
  target `blt inc; b runningCatch`, ours `bge runningCatch`.
  [1] move `BOOL hasSuction` decl to each of 16 positions -> all identical (decl order is inert here)
  [2] 0.07 test as `if (!(x < 0.07f)) goto runningCatch;` / if-else -> no change; `>= 0.07f` -> 98.77
fn_3_402A8 97.83 (no change)
  [1] mask loop: target increments shiftAmt before i; `shiftAmt += 3, i++` fixes the standalone copy but drops
      aITeamFieldingFirstFrameAfterHit / humanTeamFieldingFirstFrameAfterHit 100 -> 99.94 (their inlined copy wants
      the current order) -> reverted. init order swapped -> 97.82; `1 << (i * 3)` -> 97.87 standalone but unit worse.
  [2] distanceToBallLandingSpot: InMemFielder* local / nested distSq inline / hand-expanded in caller -> no change;
      no sqx/sqz locals -> 95.88.
  remaining: tail setFielderAutoMovement(3|5, 3): target rematerialises g_Fielders, ours reuses dist3's base reg.
wallJumpInitialization 98.60 -> 98.63
  [1] second magnitude: `dz * dz + dx * dx` -> 98.63 (kept). sq locals (expr or stmts, before/after inVec) -> 98.06;
      sum local before inVec stores -> 98.26; magnitude before inVec -> 96.68; fielderDistSqToPoint nested -> 97.94.
      remaining there: target keeps the sum in a fresh FPR (f5) instead of reusing pos.x's (one more live FPR).
  [2] backtrack loops: no j (idx in place) -> 98.42; j after dist -> same; second loop on j -> 98.07.
  [3] ballX/Y/Z/dist load order / decl order -> no gain (FPR numbering in the apex block).
checkIfCutoffIsntAtThrowDestination / checkIfPlayerNeedsToMoveToCatchBall twins 97.99 / 97.99 (no change)
  [9] tip-3 nested inline fielderDistSqFromPoint(fielder, x, z) (dx = pos - x) called as
      fielderSqrt(helper(fielder, predX, predZ)) in both: decls dx,dz + `sqz + sqx` -> identical (97.986/97.991);
      `sqx + sqz` -> 97.82; dz,dx decls -> 97.84; no sq locals -> 97.30. The mismatch is upstream of the distance
      (predX coalesces with vel.x's reg in ours, with the AtBat_Contact_BallPos.x load in target), so a distance
      helper cannot reach it.
determineBestFrameForFielder 95.74 -> 95.88
  [1] the hand-inlined frames-to-reach block is exactly fRunningTimeToDestination's body (incl. `0.0f == joggingSpeed`):
      replaced with `framesNeeded = fRunningTimeToDestination(fielderIndex, fut[frame].pos.x, fut[frame].pos.z)`
      (inlines, no bl) -> 95.74 (same score, 9 locals gone). ballX/ballZ locals as args -> 95.37.
  [2] decl-order walk (120 perms) -> 95.88 (kept)
  remaining: prologue constant loads (target 4.5f via direct lfs @l, ours addi+lfs 0) and GPR numbering
  (fielder r4/r5, reactionFrames r9/r4, lastFramesNeeded r6/r9).
minigameDashUpdateFieldingVariables 97.70 -> 98.37
  [1] statement order at entry: `fielder = &g_Fielders[fielderIndex]` right after reading fielderIndex, before the
      activeFielderSlot / minigameRelatedIndex stores -> 98.37 (kept). activeFielderSlot store first -> 96.02 (and
      another function dropped), fielder after slot store -> 97.70, fielder decl last -> 97.70.
  remaining: scheduler-only: target hoists the GameMode_MiniGame lbz/cmplwi between the 0x148 and 0x14a input stores.
evaluateFlyBallCatch 97.94 (no change): scheduler-only (target does the index slwi before the fielder pos loads).
  fielderDistSqToPoint nested helper / decl swap -> identical; CoordAndDist* local -> 97.30; dz first -> 97.83.
chooseSecondaryFielderFromClosestOutfielder 98.28 (no change): GPR numbering only (other ptr r4 vs r3).
  int frame local shared -> 93.64; frame7/frameO locals -> 96.23; fielderDistSqToPoint helper -> 98.279 (same);
  direct g_Fielders[otherFielderIndex] / g_Fielders[7] instead of the pointers -> 88.4 / 93.3 / 84.5.
bobbleDirection 98.83 (no change): only the two getComponentsFromSAng arg setups (target addi r5 before extsh r3).
  explicit (s16) casts -> same; s16 elevationAngle / both s16 -> 96.9 / 96.8.
ballThrownToEmptyBaseCatchAttempt 98.85 (no change): callee-saved rotation (loc r30/r27, fielder r28/r29, base off r29/r30).
  decl-order walk 80 perms -> inert; VecXZ* base pointer -> 98.77; int locationThrownTo -> 98.03.
knockoutRelated_FlyBall 99.48 / knockoutRelated_Grounder_Liner 99.65 (no change)
  shape: after calcKnockoutCatchStrategy, target's inlined reassign loop stores through the function-entry g_Fielders
  base (r30/r29, callee-saved); ours reuses the freshly built g_Fielders[best] base (r4).
  `fielder = &g_Fielders[best]` for the maybeMovementState store -> 97.5/96.6; inline loop via `InMemFielder* f =
  g_Fielders; f[i]` -> identical; pointer-increment loop -> 90.6/91.8.
setInitialFielderMovements_generalCase 99.83 (no change): GPR numbering in the sf3/sf5 and f2..f5 blocks.
  no avg local / no locals / sf5 first / decl order -> all identical; selectedFielder=0 store moved -> 99.77.
adjustPlayerPosOutsideFoulLine 98.61 -> 99.70
  [6] tip 4 `/ 2.0f` vs `* 0.5f`: all four halves `/ 2.0f` -> 99.34; all 81 combos of {`/ 2.0f`, `0.5f *`, `* 0.5f`}:
      best = first three `* 0.5f` (0.5f* is equivalent) and the last `(-x - d) / 2.0f` -> 99.70 (kept). The divide form
      puts the constant second in the fmuls (diff * 0.5), the multiply form first.
  [7] negX local assigned in the condition (body uses negX or -x) -> same; `d <= x && d <= -x` -> 97.17; decl walk -> inert.
  remaining: CSE'd -x lives in f5 in target, f1 in ours (last block).
fielderAISomething 99.46 -> 100 (MATCHED)
  [1] second loop `for (i = 0, found = 0; ...)` -> 99.51 (fixed code's reg); loop-local code / decl moves -> no change
  [2] second loop reads g_Fielders[i].autoMovementFunctionIndex at each test (no `code` local, tip 2) -> 99.92
  [3] + back to `found = 0;` before the loop -> 100. (`found, i` comma init also 100; found decl first irrelevant)
  readability pass: done (BOOL found / TRUE / FALSE, `!found`, AUTO_MOVEMENT_TRACK_HIT_BALL_PHASE2_AI_TEAM for 2).
  Left as literals: autoMovementFunctionIndex 3/4 and 18 and fielderAutoMovementCode 1/7 (no enum members yet).
  Name left as is (placeholder-ish; evidence only says "re-run AI assignment when nobody is chasing" - low).
  final source: commit "fielder: match fielderAISomething".
updateSomeAutoMovementAssignments (cont.) 95.78 -> 95.82
  [5] (lesson from fielderAISomething) best-candidate loop reads fielderAutoMovementCode[i] at each test instead of a
      u8 code local -> 95.82 (kept; i now r27 like target). newFielder loop same change -> no effect (kept local);
      decl walk after -> inert. remaining in that loop: code r11 vs assigned[4] r26 swapped.
selectFieldersForShallowPopUp 98.96 (no change): GPR numbering from the Hit_HorizontalAngle test on (target g_Ball
  base r7, else-branch g_Fielders base r6; ours r6 / r3). t2/t3/t5 as s16 -> same; t4 as int -> 98.81.
Session 2 end: unit 99.225 -> 99.239, 170 -> 171/225 (report generate). All commits pushed (last ae03ca43).
  Not reached / leads: minigameFieldingRelated_collisions (exhausted before; no new idea), updateFielderDirectionFacing
  (exhausted), setFielderCatchStrategy_calcFramesToGetToDropSpot / setCatcherCatchStrategy remainders (not retried),
  fielderMovement_adjustPlaceToStandForBallBouncingOffWall (not retried). Outside scope: updateVariablesPostCatch has a
  hand-copied fRunningTimeToDestination body (framesEstimate block) - try the call when that section is ground.

## Main entry section

Baseline (report 2026-11-07): setDefaultInMemFielder 85.85, resetInMemFielders 94.02, initFielders 94.21,
fielding_setStartingCoordinates 99.87; other 5 at 100.

### setDefaultInMemFielder
  baseline 85.85
  [1] REAL BUG: minigame block: target is if (sel>=0) { if (ai[sel]) f0 } else if (slot[0]>=0 && ai[slot[0]]) f2;
      old else-if fell through to slot[0] when sel>=0 but not AI. participantSlot[1..3] -> fielders 3..5 is a loop.
      *(s8*)&minigamePlayerSelectedOrder (double extsb like target). baseOn2 / fielderActionBeingProcessed_prev retyped s8
      (target stores the -1 reg, no li 0xff) -> 87.38
  [2] s32 (long) i: MWCC keeps the loop-entry guard (cmpwi r4,0x14; bge) on the unrolled history loop; history loop from 0 -> 96.86
  [3] dash records as for(i<4) loop before dashPtr assignment -> 98.36 (A: dash++ pointer loop 97.95)
  [4] someFrameCounter/FrameCycleCounter_20 order swap -> 98.48 diff but just moves the last store; reverted
  [5] isResponsibleForCoveringALocation before locationResponsibleForCovering -> 98.09 (rev)
  committed 98.43 (report).
  [6] g_FieldingLogic.fielderAutoMovementCode[i] = 0 moved to the top of the per-fielder block -> 99.35 diff / 99.41 report (kept)
      (constant regs follow first appearance: target has the 0 constant defined before -1)
  [7] tail orderings around dash loop (AIControlFlag/jumpDive/dashPtr before or after loop, 4 variants) -> <= 99.29 (rev)
  remaining: only sth 0xc0 (last FL store before the dash loop) scheduled after lis AiLogic/addi/cmpwi instead of before.
  [8] fielder-> to g_Fielders[i]. throughout: no change
  [9] dash loop before someFrameCounterFielderRelated = 0 -> 99.47 (kept). The 0xc0 store now lands after the dash stores
      (target: between the 0x146 store and the dash stores). Any placement of the store after the loop (3 variants) = 99.47;
      separate int j for the dash loop -> 99.35.
  status: exhausted at 99.47 (one store scheduled off by one block).

### fielding_setStartingCoordinates
  baseline 99.87: only mulli r6/r7 vs slwi r7/r6 swap in the holdRunners index.
  [1] holdIndex declared at top (2 orders) -> same; holdRunnersSlot/useBunt decl swap -> 98.09
  [2] holdRunnersSlot as ternary / default-then-if -> 98.09 / 93.42
  [3] extern as f32 [4][3][2] with [..][..][0]/[1] -> same
  [4] if/else tail instead of return-chains (2 shapes) -> same
  [5] batterHand / buntStatus as int -> 99.06; no buntStatus local -> same
  status: exhausted 99.87

### initFielders / resetInMemFielders (shared lockout loop)
  initFielders baseline 94.21: hoisted GL/470C address regs swapped (r4/r5), fmuls f1 vs f0 dest.
  [1] expression variants: no casts, (f32)(hi-lo) one-expr, lo/hi int locals (94.04), mult * diff, f32 mult local, f32 scaled temp,
      value += lo split (89.66) -> none better
  [2] decl order permutations (aiIndex/diff/value/fielder/i), statement order fielder vs aiIndex -> no change
  [3] g_Fielders[i] direct (no pointer) -> 62.79: the pointer store must alias lbl_3_data_470C (u8) or the loads get hoisted
  [4] teamAIInd[team] -> 88.45; if (i<2) value/=2 -> 85.49
  status: initFielders exhausted 94.21.
  resetInMemFielders baseline 94.02. Its middle is initFielders' body.
  [5] call initFielders() (inlines) -> 91.50: fixes the setFielderValues loop r29/r30 swap but loses the shared &g_Fielders base
      (target keeps r7 and mr r6,r7 for the third loop); third loop variants (direct index, pointer++ loop 76.1) don't restore it
  [6] hand copy with separate int j for the setFielderValues loop (4 decl positions) -> 91.47; int i first -> 91.46
      (s32 i needed: keeps the third loop's li r3,0; cmpwi r3,9; bge guard)
  status: resetInMemFielders exhausted 94.02. Lead: target is consistent with inlined initFielders except for the base share.

## Steals/at-bat section

Baseline (report 2026-11-07): fielding_atBat_SetSomeAutomovements_callCollisionFn 81.88, fielderActionsOnSteal 92.86,
fn_3_31678 95.62, fn_3_31A3C 96.77, stealSetFielders 98.05; other 5 at 100.

### fielding_atBat_SetSomeAutomovements_callCollisionFn -> matched 100
  [1] minigame fielder match as for(matchIdx<4) search loop (target unrolls by 2 with addi r3,1 pointer), -pi case as the
      positive && test with atan2 in else, fielder = &g_Fielders[i] per iteration, u8 minigamesEnabled -> 99.63
  [2] u8 minigamesEnabled declared before matchIdx -> 100 (int minigamesEnabled -> 98.72: target cmplwi)
  readability pass: done (FIELDING_POSITION_FIRST_BASE, PLAYERS_PER_TEAM). matchIdx<4 left literal (ARRAY_COUNT is unsigned).
  final source: commit "fielder: match fielding_atBat_SetSomeAutomovements_callCollisionFn"

### fielderActionsOnSteal -> matched 100 ; fn_3_31678 -> matched 100
  [1] REAL BUG (fielderActionsOnSteal): missing g_FieldingLogic.fielderAssignedLocationIndex[3] = 4 (target sth 4,0xd6) -> 96.84
  [2] (f64) compare -> (f32) (target fsubs) ; cover-flag loop g_Fielders[i] direct (no pointer++) -> 97.61 / 97.05
  [3] __abs in one expression: if ((f32)__abs(a3 - 0x400) < (f32)__abs(a5 - 0x400)) -> 100 both
      (d1=__abs() locals -> 96.51; hand abs locals spilled r31)
  readability pass: done (FIELDING_POSITION_*, TRUE, PLAYERS_PER_TEAM, AUTO_MOVEMENT_GOING_TO_BALL for 15).
  Other auto-movement indices (1, 10, 14, 18, 0) and cover locations (0..5) left literal: no enum members exist.

### fn_3_31A3C (now wildPitchSetFielders) -> matched 100
  [1] angle loop: fielder = &g_Fielders[i] per iteration instead of pointer++ -> 100
  readability pass: done (PLAYERS_PER_TEAM, FIELDING_POSITION_CATCHER/NONE).

### stealSetFielders -> matched 100
  [1] same loop change -> 99.87
  [2] REAL BUG: throwWindUpFrames assignment belongs inside the else (pitcher-holds) arm; target's catcher arm b's to the epilogue -> 99.90
  [3] BOOL quickThrow local (copied from setFielder215 in fielder_ai.c) -> 100
  readability pass: done (FIELDING_POSITION_*, NONE for fielderBeingThrownTo). fielderAboutToGetBall_hasBall = 0 left literal
  (fielder-index field but it stays 0 even when the catcher holds the ball). pickOffLoc 5 / 1..3 left literal (no enum).

Renames: fn_3_31A3C -> wildPitchSetFielders, fn_3_31678 -> fielderActionsOnWildPitch (medium; Ghidra: unused, no callers).
  initFielders extra [7]: f32 diff local, product-first sum, mult*diff, lbl_3_data_470C as const u8 / u8[] (no change), s8 (84.65) -> exhausted.

### Status (Main entry section, end of 2026-11-07 session)
| function | status | pct (report) |
|---|---|---|
| setDefaultInMemFielder | exhausted | 99.47 (was 85.85) |
| resetInMemFielders | exhausted | 94.02 |
| initFielders | exhausted | 94.21 |
| fielding_setStartingCoordinates | exhausted | 99.87 |
| other 5 | matched | 100 |

### Status (Steals/at-bat section, end of 2026-11-07 session)
| function | status | pct |
|---|---|---|
| fielding_atBat_SetSomeAutomovements_callCollisionFn | matched | 100 (was 81.88) |
| fielderActionsOnSteal | matched | 100 (was 92.86) |
| fielderActionsOnWildPitch (was fn_3_31678) | matched | 100 (was 95.62) |
| wildPitchSetFielders (was fn_3_31A3C) | matched | 100 (was 96.77) |
| stealSetFielders | matched | 100 (was 98.05) |
| other 5 | matched | 100 |
Unit after: 99.45303, 176/225 (before 99.24596, 171/225).

## Catch animations section (Catch animations, bobbles and post-catch; Opus pass, 2026-11-07, baseline r0 unit 99.453, 176/225)

### updateVariablesPostCatch 96.73 -> 99.99
  [1] REAL BUG: big-play blocks are a chain under `if (caught && throws == 0) { if (anim 4||5) {..} else if (isJump) {..}
      else { bigPlay==1 block; action==2 block } }` (target b's to the star-swing test after blocks 1/2) -> 98.97
  [2] REAL BUG: bigPlay==1 block awards STAR_MISSION_EVENT_BIG_PLAY (li r3,2), not ACTION_CATCH
  [3] Toy Field sound as m_sound.c playStadiumHazardSound shape (int stadiumID, no fid!=0 guard, ternaries as args)
      -> 99.90, frame 0x40 -> 0x30 and one fewer saved GPR
  [4] REAL BUG: location/runner text block nested inside `if (isResponsibleForCoveringALocation == 1)`;
      (&g_hitShorts.fireballStunFrames)[id] -> 99.987
  [5] remaining: lis g_Batter gets r5 (target r6) in the long store block. g_Batter/g_Minigame swap -> 99.91;
      g_Batter store first in block -> 99.49; tagChase first + g_Batter after birdo -> 99.88. Left (exhausted).

## Techniques that worked in the final four sections
- redecompile control flow from target branch targets (else-if chain + nesting) -> updateVariablesPostCatch 96.73 -> 98.97
- copy sibling inline shape (m_sound playStadiumHazardSound) for stadium hazard sound -> updateVariablesPostCatch 98.97 -> 99.90
- nest block under preceding guard per target branch target -> updateVariablesPostCatch 99.90 -> 99.99

### mag_BirdoSlidingCatchSetCoordinates 94.39 -> 99.86
  [1] target has unfused fmuls+fadds: `dx *= ratio` in place -> 95.15; separate offX/offZ locals -> 95.19; same for the
      dive branch -> both dive branches' offsets matched; interpolation offX = (ball - c) * ratio stmts -> 98.47
  [2] dive-branch y store after x/z + chained `total = countDown = const` (target reuses r0) -> 99.09
  [3] interpolation: ratio, then diffs, then `off *= ratio`, then stores -> 99.86 (diffs before ratio 96.91,
      `off = ratio * off` 96.79, ratio*(..) commuted 99.09, lerp inline helper 98.62)
  [4] remaining: coords.x f4 vs f5 / diffX f6 vs f4 in the interpolation. Block-scope decls (6 orders), reuse of
      dx/dist/dz for the diffs -> inert. exhausted.

### fielderMovement_VelocityDuringCatchAnimations 99.03 -> 100 (MATCHED)
  [1] REAL BUG: run-up velocity block + running-catch countdown are the else arm of the magical-catch test, inside
      `if (anim 3||7||8)` (target b's to the end after zeroing) -> 98.54 (then FPR diffs)
  [2] apex branch: `vy` local stored to jumpVelocity.y then `h += vy` (target does not reload 0x164) -> 99.80;
      `vy = apexY - h; vy /= divisor;` -> 99.84 (assignment-expr forms 98.5/99.8, vy + h 99.77)
  [3] same split for the wall-contact branch: `dy = Y - h; dy /= divisor; h += dy;` -> 100
      (`h = h + q` / `q + h` / dy as one expr were inert)
  readability pass: done. catchAnimation 3/4/7/8 left literal (no enum exists).
  final source: commit "fielder: match fielderMovement_VelocityDuringCatchAnimations".
Rename: fn_3_27738 -> setFielderAutoCatch (medium).

### Status (Catch animations section, end)
| function | status | pct |
|---|---|---|
| updateVariablesPostCatch | exhausted | 99.99 (was 96.73) |
| mag_BirdoSlidingCatchSetCoordinates | exhausted | 99.86 (was 94.39) |
| fielderMovement_VelocityDuringCatchAnimations | matched | 100 (was 99.03) |
| other 7 | matched | 100 |
Unit: 99.453 -> 99.541, 176 -> 177/225.

## Pitcher/infield-support section (Auto-movement: pitcher, infield support and running off the field; Opus 2026-11-07)

### runOffBaseOverride 96.41 -> 97.43
  [1] hand copies -> releaseCoverAssignment + setFielderAutoMovementIfValid; assignedIdx/cutoffIdx int (target cmpwi
      not extsh.) -> 97.35
  [2] REAL BUG: `if (fielderIndex != 0 || !(dist < 18) || !(vel < 0.15)) found; if (i==1 && angle in (0x200,0x400))
      {margin 5} else if (i==3 && angle in (0x400,0x600)) {margin 5} else found;` -> 97.40
  [3] separate cutoffIdx for the mound path -> same; mound tests structured (no no_override goto) -> same (kept)
  [4] i decl first 97.32; assignment-in-condition 97.39; wBall on the left of the compare(s) 97.39/97.38;
      int ballHolder local 92.25.
  remaining: target holds one more value across the loop (3 saved GPRs, 0x20 frame; ours 2/0x10): wBall in r9 and the
  scratch lbz in r0, ours puts the hoisted wBall in r0. exhausted.

### autoMovement9_OffBase_coverHome 97.28 -> 100 (MATCHED)
  [1] REAL BUG: outfielder block is fn_3_3CB8C inlined; old hand copy ran setFielderAutoMovement(24) on failure too.
      Calling fn_3_3CB8C -> bl, not inlined (83.5). Moving its body into a forward-declared static inline
      sendOutfielderAfterHitBallIfFree, with the out-of-line function `return helper(i);` -> both 100.
  readability pass: done (FIELDING_POSITION_SHORTSTOP/LEFT_FIELD/PITCHER, setFielderAutoMovementIfValid x2, 11).
  Left: auto movement indices 1/14/24, cover locations 7 (no enum).
  Rename: fn_3_3CB8C -> trySendOutfielderAfterHitBall (medium; auto movement 24 = goTowardsHitBall_humanTeam).

### checkIfPlayerNeedsToMoveToCatchBall 97.99 -> 99.71 ; twin checkIfCutoffIsntAtThrowDestination 97.99 -> 99.71
  [1] REAL BUG (PlayerNeeds only): `if (animationRelatedInd != 0) return;` (target bne -> epilogue) -> 98.01
  [2] 7x7 sweep of predX/predZ forms {vel*t+pos, pos+vel*t, t*vel+pos, pos+t*vel, p=pos;p+=vel*t, p=pos;p+=t*vel,
      p=vel*t;p+=pos}: best = predX `p = pos; p += vel * t;` + predZ `vel * t + pos` -> 99.59 (predX coalesces with the
      ball.x load, predZ with t, as in target). Both `+=` -> 98.07.
  [3] decl-order sweep (40 random perms): every order with dx before dz -> 99.66; same in the twin -> 99.66.
  remaining: ball.x load scheduled before the fdivs (target loads vel.x first; ballVelocity f1 vs f2), and dz computed
  into a dead reg (f3) instead of pos.z's (f1). exhausted for both.
  (commit message of this change lost its two code snippets to shell backtick expansion; content is here.)

### autoMovement14_infieldSupport 99.17 -> 100 (MATCHED)
  [1] chained `offsetX = offsetZ = 2.0f` (target lfs once + fmr) -> 100
  readability pass: done (setFielderAutoMovementIfValid x4, FIELDING_POSITION_CATCHER, TRUE/FALSE for
  playerAtMoundCutoffLocation). Left: locations 5/7/8..13/14/15, auto movement 0, veloAdjust 8/11 (no enums).

### autoMovement17_runningOffField 99.91 -> 100 (MATCHED)
  [1] `x += outX; z += outZ;` (x first; scheduler emits outZ load first) -> 100
  readability pass: done (setFielderAutoMovementIfValid, FIELDING_POSITION_NONE, atDugoutAtEndOfInning = TRUE).

### Status (Pitcher/infield-support section, end)
| function | status | pct |
|---|---|---|
| runOffBaseOverride | exhausted | 97.43 (was 96.41) |
| autoMovement9_OffBase_coverHome | matched | 100 (was 97.28) |
| checkIfPlayerNeedsToMoveToCatchBall | exhausted | 99.71 (was 97.99) |
| autoMovement14_infieldSupport | matched | 100 (was 99.17) |
| autoMovement17_runningOffField | matched | 100 (was 99.91) |
| other 8 (incl. trySendOutfielderAfterHitBall) | matched | 100 |
(outside section: checkIfCutoffIsntAtThrowDestination 97.99 -> 99.71 with the twin fix.)
Unit after: 99.5905, 180/225.

## Human-team control section (Opus 2026-11-07)

### updateFielderMovementIfNoBall 98.82 (no change)
  only diff: last test; target `blt set; b return; set:`, ours `bge return` falling into set (4 bytes short).
  [1] `else if (diff < x) {} else { return; }` / nested `if (diff < x) {} else { return; }` -> same
  [2] `if (diff < x) goto set; return;` + set: label -> same
  [3] whole runAngle test as one `!(runAngle < 0 ? fsh > lock+3 : diff < x)` -> 88.12
  exhausted (lead: maybe an inline BOOL helper for the stick/run-angle test).

### liveBallFielderControlHumanTeam 96.90 -> 100 (MATCHED)
  [1] s32 i (loop-entry guard) + positive stick test with swapped arms -> 99.45
  [2] control = &g_Controls[...] before the selectedFielder_stored copy -> 100
  readability pass: done (FIELDING_POSITION_NONE). currentStickDirection -1, aPressed 2 left literal.

### autoMovement21_23_humanControlInitialSelectedFielders 97.03 -> 100 (MATCHED)
  [1] hand-copied cover release -> releaseCoverAssignment(fielderIndex) -> 97.04
  [2] special-action result as `switch { case 2: return; case 1: break; default: ... }` (target compare tree
      beq/bge/bge/b) + angle kept in a local for both tests -> 98.25; angle as int (no extsh.) -> 98.61
  [3] REAL BUG: fielderTrackingBallState = 1 inside the `== 0` block -> 100
  readability pass: done (setFielderAutoMovementIfValid, FIELDING_POSITION_SHORTSTOP/LEFT/RIGHT/NONE, TRUE/FALSE, 10).
  Left: locations 6, auto movements 11/12, unknown_writeOnly 2/3, sprintingState 3/4 (no enums).
Renames (medium): fn_3_3B99C -> recordFielderAPress, fn_3_3ABF0 -> stopFielderIfSelectedFielderCatching,
  fn_3_3AAF8 -> updateHumanFielderMovementAngle (each is a standalone copy of a block inlined in this section).
  fn_3_3A1FC left (someCountDown2 / lastFrameVelocityUpToBase meaning unclear - low).

### Status (Human-team control section, end)
| function | status | pct |
|---|---|---|
| liveBallFielderControlHumanTeam | matched | 100 (was 96.90) |
| autoMovement21_23_humanControlInitialSelectedFielders | matched | 100 (was 97.03) |
| updateFielderMovementIfNoBall | exhausted | 98.82 |
| other 8 | matched | 100 |
Unit after: 99.6253, 182/225.

## Wall jumps section (Wall jumps, clambers, wall splats and jumps; Opus 2026-11-07)

### clamberJumpOffWall 97.58 -> 100 (MATCHED)
  [1] no u8 status local, re-read fielder->clamberStatus at every test -> 100 (u8 status declared first also 100;
      int status 95.35; no countdown local / status decl between -> 97.58)
  readability pass: done. clamberStatus 3/5 and wallActionFacingAngleInd 1 left literal (no enum; not shown 0/1).

### wallSplat_setPosAndVelo 99.37 -> 100 (MATCHED)
  [1] `dx *= factor; dz *= factor; dy *= factor;` then store / `h += dy` (target multiplies in place) -> 100
  readability pass: done. wallSplatStatus 1..4, animation 2, sound 0xb left literal (no enums).

### setClamberPos 99.56 -> 100 (MATCHED)
  [1] nearDist/farDist locals for the sideways probe: function scope (either order) / block scope -> 99.87;
      `(d - 5) * cos` operand order -> 99.58
  [2] block scope with decls `farDist; nearDist;` then assigned near, far -> 100
  [3] gotos: structured version (status/nextStatus != 0 guards) -> 93.18, +52 bytes; gotos kept.
  readability pass: done (BOOL collided TRUE/FALSE). clamberStatus 3, wjRelated 1..4, `& 0x7F` mask left (no names).

### Status (Wall jumps section, end)
| function | status | pct |
|---|---|---|
| clamberJumpOffWall | matched | 100 (was 97.58) |
| wallSplat_setPosAndVelo | matched | 100 (was 99.37) |
| setClamberPos | matched | 100 (was 99.56) |
| other 5 | matched | 100 |
Unit after: 99.6335, 185/225.

## Techniques that worked in the final four sections (full list; the 3 lines under the Catch section are included)
- redecompile control flow from target branch targets (else-if chain + nesting) -> updateVariablesPostCatch 96.73 -> 98.97
- copy sibling inline shape (m_sound playStadiumHazardSound) for stadium hazard sound -> updateVariablesPostCatch 98.97 -> 99.90
- nest block under preceding guard per target branch target -> updateVariablesPostCatch 99.90 -> 99.99
- separate statements for scaled offsets (unfused fmuls/fadds in target) -> mag_BirdoSlidingCatchSetCoordinates 94.39 -> 99.86
- split 'x = (a-b)/d' into 'x = a-b; x /= d;' via local, store local -> fielderMovement_VelocityDuringCatchAnimations 99.80 -> 100
- read the target's branch targets for || / else-if chains (found vs continue) -> runOffBaseOverride logic
- hand copies -> releaseCoverAssignment/setFielderAutoMovementIfValid + int index locals -> runOffBaseOverride 96.41 -> 97.35
- non-inlining later non-static callee: move body to forward-declared static inline, out-of-line fn returns helper() -> autoMovement9_OffBase_coverHome 97.28 -> 100 (also fixed a real bug)
- mixed forms for two sibling fmadds (p = pos; p += vel*t for x, vel*t + pos for z) + dx-before-dz decls -> checkIfPlayerNeedsToMoveToCatchBall / checkIfCutoffIsntAtThrowDestination 97.99 -> 99.71
- chained init offsetX = offsetZ = 2.0f (lfs + fmr) -> autoMovement14_infieldSupport 99.17 -> 100
- statement order x then z when scheduler reverses -> autoMovement17_runningOffField 99.91 -> 100
- s32 loop index + if/else arm order from target + entry statement order (first lis order) -> liveBallFielderControlHumanTeam 96.90 -> 100
- compare tree beq/bge/bge/b on a call result = switch (case 2 return / case 1 break / default) -> autoMovement21_23 97.04 -> 98.25
- int (not s16) local for a value tested twice (no extsh.) -> autoMovement21_23 98.25 -> 98.61
- re-read field at every test instead of a u8 local -> clamberJumpOffWall 97.58 -> 100
- scale deltas in place (dx *= factor) before storing -> wallSplat_setPosAndVelo 99.37 -> 100
- block-scope locals for two derived radii, declared in reverse of assignment -> setClamberPos 99.56 -> 100

## Playbook pass (Opus 2026-11-07, baseline rep_w0 = unit 99.6335, 185/225)
### setStandingOnBaseVariables 94.83 -> 100 (MATCHED)
  [1] NEW LEVER: loop counter `s32 i` (long) instead of `int i` -> 100. int vs long changes MWCC's address
      folding: int gave add+lhau 0xd0 for assigned[i]; long keeps addi base+0xd0 + lhax/sthx (and the r31 save).
  readability pass: done (TRUE/FALSE for baseCoveredInd, FIELDING_POSITION_PITCHER). isResponsibleForCoveringALocation
  left literal (takes 0/1/2), pitcherHeadingToCover1stOr3rd left literal.
### Sweep: int <-> s32 on every local of every unmatched function (sweep1), and on every static-inline param (psweep1)
  hits: updateSomeAutoMovementAssignments problemOutfieldBase s32 (95.78->96.54), oldFielder s32 (96.55),
        assignFielderToCoverLocation(int, s32 location) (97.26, no other fn changes);
        distanceToBallLandingSpot(s32 fielderIndex) -> fn_3_402A8 97.83 -> 99.96.
  every other local/param flip: no change or worse (setFielderAutoMovement/IfValid/releaseCoverAssignment fielderIndex
  s32 break ~20-35 matched fns each).
### fn_3_402A8 99.96 (remaining: mask-loop increments r5/r6 order)
  [1] `shiftAmt += 3, i++` -> 99.80 now (inlined copies no longer exist: the other loops at 7340/11274 are separate code).
  [2] shiftAmt += 3 in body -> 99.78; shiftAmt=0 before / init order swap -> 99.947; 120 decl orders -> 99.92..99.963.
### updateSomeAutoMovementAssignments 97.26 (after s32 hits)
  remaining: (a) best7/8/9 init: target li r7,-1; mr r8,r7; mr r9,r7 + 999.9f via addi+lfs 0; (b) block 3 re-reads
  assigned[4] (lha 0xd8) in target, ours reuses loop 2's hoisted copy (r26, which also swaps code/assigned[4] regs in
  loop 2); (c) dist8/dist7 sqrt computed in f6 + fmr.
  [6] loop-2 `i == assigned[4]` -> 97.25; block-3 nested ifs / s16 moundFielder local -> 97.26 (same)
  [7] block 3 as static inline assignMoundCoverFielder(best9, best8, best7) -> 97.06 (reload still CSE'd) reverted
  [8] code as u8 local in loop 2 (shares var with loop 1) -> 95.31/95.44
### Sweep 2: int params -> s32 (def + header) for every unmatched fn: all worse. Narrow locals (s16/u8/s8/u16) -> s32/int:
  one hit: determineBestFrameForFielder `int reactionFrames` (was s16) 95.73 -> 99.71.
### determineBestFrameForFielder -> 100 (MATCHED)
  [1] int reactionFrames -> 99.71; [2] 24 orders of the four int locals: lastFramesNeeded first, then fielder,
      bestHeight, framesNeeded, frame, bestFrame, found, reactionFrames -> 100.
  readability pass: done (BOOL found / TRUE / FALSE). 360 (futureCoordsAndDist length) left literal: no named count.
### initFielders 94.21 / resetInMemFielders 94.02 -> 94.42
  [1] s32 i in initFielders + resetInMemFielders calls initFielders() (inlined) -> reset 94.42 (kept, hand copy and
      its unused locals removed); residual diff in both is now exactly initFielders' own (hoisted GL/470C regs r4/r5,
      fmuls dest f1 vs f0). Fix initFielders and both should go to 100.
  [2] initFielders: `(s32)(...) + lo`, `value = lo; value += ...`, no (f32) cast, (int) cast -> all 94.21 (same).
### calculateMinDiveDistAndEndingCoords 98.59 -> 100 (MATCHED)
  [1] REAL BUG: sqrt result went into totalDist (so outDist = |dir| + run); target keeps totalDist = 0 (f31 never
      overwritten before the loop) and uses a separate dirLength for the normalisation -> 99.94
  [2] `numFrames -= i + 1; totalDist += joggingSpeed * (f32)numFrames;` (target subf into r27) -> 100
  readability pass: done (nothing named applies; 0x2A8 angle threshold left literal).
### divingCatch 98.85: runningCatch body moved inside the searchBackward loop -> 97.80 (reverted).
  BOOL hasSuction -> u8/s32 and all int/s32/narrow flips (re-swept with fixed scope): no change.
  NOTE: the first sweeps' function-scope regex matched call sites for wallJumpInitialization, divingCatch,
  catchThrownBallFun, checkIfCatchOccurs, runOffBaseOverride; those five were re-swept (sw3*): no hits.
### Decl-order hill-climb (30 swaps each, drive.sh) on 24 register-only functions: no gains anywhere
  (chooseSecondary, runOffBase, minigameCollisions, adjustPlaceToStand, knockout twins, wallJump, fn_3_2E41C, mag_Birdo,
  checkIfCatchOccurs, fn_3_2DDB4, calcKnockout, catchThrownBallFun, updateFielderPositionAndVelocity, evaluateFlyBall,
  bobble, setCatcher, setIntendedLocationAhead, updateSome). Only setFielderCatchStrategy gained (98.95 -> 99.30, 2 walks).
### Static-inline helper locals int<->s32 / narrow types sweep: no gains (anyBallChaserUnsettled `s32 i` drops
  aISetFielderWithBallIndex 100 -> 91.3; releaseCoverAssignment `loc` s32/int drops 5 fns).
### updateFielderMovementIfNoBall 98.82: duplicated set-block tail in the diff branch (tail-merge hope) -> 95.59 both forms.
### fn_3_2E41C 99.83: ((s8*)minigameFielderIndex)[i] call arg -> 95.75; header retype minigameFielderIndex s8 -> fn
  unchanged, miniGameFielding 100 -> 95.8 and minigame_fielder_anim updateMinigameFielderAnimations 100 -> 97.5 (reverted).
### updateSomeAutoMovementAssignments 97.26 -> 98.13
  [9] playbook A7 (small local arrays): dist9/8/7 -> `f32 dist[3]` -> 98.13 (kept; fixes the f6+fmr sqrt results).
      best9/8/7 -> `int best[3]` too: 96.34..96.57 for every index mapping x init order (gives target's addi+lfs 0 for
      999.9f but wrong chain) -> reverted; best array alone 95.48. Scalar best init orders with dist[] -> all 98.13.
  remaining: best init li/mr/mr chain, block-3 assigned[4] reload (r26), GPR numbering in blocks 3/4.
### Playbook pass status (end; report rep_w7 = unit 99.7725, 188/225)
| function | status | pct |
|---|---|---|
| setStandingOnBaseVariables | matched | 100 (was 94.83) |
| determineBestFrameForFielder | matched | 100 (was 95.88) |
| calculateMinDiveDistAndEndingCoords | matched | 100 (was 98.59) |
| fn_3_402A8 | exhausted | 99.96 (was 97.83) |
| updateSomeAutoMovementAssignments | pending | 98.18 (was 95.82) |
| setFielderCatchStrategy_calcFramesToGetToDropSpot | exhausted | 99.30 (was 98.95) |
| resetInMemFielders | exhausted | 94.42 (was 94.02; tied to initFielders) |
| initFielders | exhausted | 94.21 |
| all other below-100 functions | exhausted | unchanged (type sweeps + 30-swap decl walks, no gain) |
Chooser notes: chooseSecondary ternary/if-else/f7-> forms, pointer per branch, mag[2]/diff[2] arrays -> no gain.
initFielders: no aiIndex local / `if (aiIndex)` -> same.
