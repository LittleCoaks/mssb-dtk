#ifndef __GAME_BALL_BALL_PHYSICS_H_
#define __GAME_BALL_BALL_PHYSICS_H_

#include "mssbTypes.h"

void chompCollision_processStarHitVariables(void);
void ballState_thrown_to_holding(void);
void fn_3_65C8(void);
void setBallInactiveVariables(void);
void setValsForPlantCatches(void);
void checkForBallDead(void);
void ballCollisionLogic(void);
void handleBallBounceAndRoll(void);
void handleBallHitDeadBallOutcome(void);
void fairOrFoulBall(void);
void processLandedBallBouncing(void);
void processBallInAir_Landed(void);
void fn_3_9B74(void);
void ballDistCalculator(void);
void fn_3_9E18(void);
void relatedToGroundRuleDouble(void);
void fn_3_9FA4(void);
void fn_3_A020(void);
void foulBall(void);
void warioWaluStarHit(void);
void updatePastHitBallCoords(void);
void liveBallHitPhysics(void);
void estimateTimeForThrowToReachTarget(void);
void fielding_setHeldBallOffset(void);
void futureFrameForClosestBall(void);
void fn_3_BC54(void);
void setHitClassification3(void);
void classifyHitTrajectoryOrHitAnimRelated(void);
void updateFrameCountersAndBallPastCoordinatesWhenFielderHoldingBall(void);
void estimateAndSetFutureCoords(int);
void fn_3_D9EC(void);
void adjustVeloByAirResistance(void);
void estimateWhereBallWillHitWall(void);
void calculateImplicationsOfTheHitTrajectory(void);
void setLiveBallVariablesAfterContact(void);
void setDefaultInMemBall(void);
void resetBallValuesBetweenBatters(void);
void resetInMemBall(void);
void fn_3_F9F8(void);
void initBallAndGameStateOnLoad(void);

#endif // !__GAME_BALL_BALL_PHYSICS_H_
