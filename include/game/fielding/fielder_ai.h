#ifndef __GAME_FIELDING_FIELDER_AI_H_
#define __GAME_FIELDING_FIELDER_AI_H_

#include "mssbTypes.h"

void fielderAIDecideWhatRunnerToTarget(int fielderIndex);
int fn_3_A1D04(void);
BOOL fn_3_A1DA0(void);
BOOL fn_3_A1F3C(void);
BOOL fielderAIWeirdSituation(void);
BOOL canThrowOutRunnerWhoNeedsToTagUp(void);
BOOL throwOutRunnerTaggingUpInd(void);
BOOL genericPlayOnRunnerOffBase(void);
BOOL fn_3_A295C(void);
BOOL fn_3_A2B6C(void);
BOOL fn_3_A2C9C(void);
BOOL fn_3_A2DDC(void);
BOOL fn_3_A2FD8(void);
BOOL fn_3_A31E8(void);
BOOL fn_3_A32B8(void);
BOOL fielderAIOutfieldPlayAttemptInd(void);
BOOL fn_3_A36BC(void);
BOOL fn_3_A372C(void);
BOOL fn_3_A3768(void);
BOOL fn_3_A37BC(void);
void fn_3_A384C(void);
void fn_3_A3B30(void);
void fn_3_A3C00(void);
void fielderAIChaseRunner(void);
void fn_3_A4158(int runnerIndex);
void fn_3_A41E8(int base);
int fielderAIMakePlay(int targetRunner);
void fieldingAIPlayStrategy(void);
void throwTimeToBase(int baseCounter);
void fn_3_A53DC(int runnerIdx);
void runnerTimeToCoverBase(int runnerIndex);
void fieldingAIThrowOrChase(int runnerIndex);
int howManyFramesTheRunnerIsOutOfReach(int runnerIndex, BOOL forwards, int* throwStrat, int* runStrat);
void fn_3_A67E8(int i);
int estimatedThrowFramesBetweenTwoPoints(f32 ax, f32 az, f32 bx, f32 bz);
int fn_3_A6ABC(f32 x, f32 z);
void fn_3_A6D48(void);
void tagRelated(int fielderIndex);
void tagOutValues(int fielderIndex);
void fielderHasBall(void);
void checkForBufferedThrow(void);
void fielderControl_classifyControlStickDirection(void);
void setRunnerChasingAfter(int fielderIndex);
void fielderChasingAI(int fielderIndex);
BOOL runnerTagUpOrBatterTo1B(int* outBase, int* outFrames);
void maybeUnused_SetThrowSpeedType2(f32 dist);
void fn_3_A89D4(void);
void knockBallLoose(int fielderIndex, int knockOutCause);
void fielderBodyCheck_setStatus_Pos_Velo(int fielderIndex);
void fielderKnockback(int fielderIndex);
void setFielder215(int fielderIndex);
void autoMovement10_HasBall(int fielderIndex);
void fn_3_AAA3C(int fielderIdx);
BOOL fn_3_AABF8(void);
void fn_3_AAC84(f32* outX, f32* outZ);
void setCutoffThrowTargetLocation(f32* targetX, f32* targetZ);
void fn_3_AB554(void);
void initializeThrowAngle_Speed_Length(int framesForFielderToGetToLoc, f32* throwAngle, f32* throwSpeed);
void makeThrowVariables(int fielderIndex);

#endif // !__GAME_FIELDING_FIELDER_AI_H_
