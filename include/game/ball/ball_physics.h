#ifndef __GAME_BALL_BALL_PHYSICS_H_
#define __GAME_BALL_BALL_PHYSICS_H_

#include "mssbTypes.h"
#include "game/ball/collision_primitives.h"

void chompCollision_processStarHitVariables(void);
void ballState_thrown_to_holding(void);
void fn_3_65C8(void);
void setBallInactiveVariables(void);
void setValsForPlantCatches(void);
void checkForBallDead(void);
void ballCollisionLogic(void);
void handleBallBounceAndRoll(f32* verticalVelocity, int bounceFrameCount, u8* ballIsRolling, BOOL skipStarBounce);
void handleBallHitDeadBallOutcome(void);
void fairOrFoulBall(BALL_COLLISION_TYPE collType);
void processLandedBallBouncing(void);
void processBallInAir_Landed(void);
void fn_3_9B74(void);
f32 ballDistCalculator(f32 x, f32 z);
void fn_3_9E18(void);
void relatedToGroundRuleDouble(void);
void fn_3_9FA4(void);
void fn_3_A020(void);
void foulBall(void);
void warioWaluStarHit(void);
void updatePastHitBallCoords(void);
void liveBallHitPhysics(int mode);
void estimateTimeForThrowToReachTarget(void);
void fielding_setHeldBallOffset(void);
int futureFrameForClosestBall(f32 playerX, f32 playerZ, f32* outPos, int maxFrame, int step);
void fn_3_BC54(void);
void setHitClassification3(void);
void classifyHitTrajectoryOrHitAnimRelated(void);
void updateFrameCountersAndBallPastCoordinatesWhenFielderHoldingBall(void);
void estimateAndSetFutureCoords(int mode);
void fn_3_D9EC(void);
void adjustVeloByAirResistance(void);
void estimateWhereBallWillHitWall(BOOL useBallPitcherStart);
void calculateImplicationsOfTheHitTrajectory(void);
void setLiveBallVariablesAfterContact(void);
void setDefaultInMemBall(void);
void resetBallValuesBetweenBatters(void);
void resetInMemBall(void);
void fn_3_F9F8(void);
void initBallAndGameStateOnLoad(void);

#endif // !__GAME_BALL_BALL_PHYSICS_H_
