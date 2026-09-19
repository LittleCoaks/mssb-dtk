#ifndef __GAME_BASERUNNING_RUNNER_H_
#define __GAME_BASERUNNING_RUNNER_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"

void fn_3_7D79C(int runnerIdx);
void fn_3_7D920(int runnerIdx);
void fn_3_7D9DC(int runnerIdx);
void runnerChangeDirectionHumanInput(int runnerIdx);
void fn_3_7DD24(int runnerIdx);
void cCSRunningFun(void);
void running_LiveBall_Human(void);
void fn_3_7EA68(void);
void running_sendOutRunnerToDugout(int runnerIdx);
int running_roundBaseDecision(int runnerIdx);
BOOL running_overrun1stIndicator(void);
int running_triggerSlideOrBodyCheck(int runnerIdx);
void fn_3_7F9C4(int runnerIdx);
int running_DirectionOverrides(int runnerIdx);
void fn_3_7FD90(int runnerIdx);
void fn_3_7FEA8(int runnerIdx, int direction);
void fn_3_7FED4(VecXYZ* out, f32 speed, f32 frame);
void fn_3_7FFD0(VecXYZ* out, int fromBase, int toBase, f32 t);
void running_updatePosition(int runnerIdx);
void fn_3_810C4(int runnerIdx, int base);
void running_updatePositionTracking_storeRBIs_stopAtNextBase_displaySafe(int runnerIdx);
void fn_3_81AB8(int runnerIdx);
void fn_3_81AEC(int runnerIdx);
int running_overrunBaseControl(int runnerIdx);
int runnerOverrun1BRelated(int runnerIdx);
void running_ActionControlAndVelocity(int runnerIdx);
void running_CalculateSpeedVariables(int runnerIdx);
void updateRunnerFramesToClosestBases(int runnerIdx, s16* framesToPreviousBase, s16* framesToNextBase);
void running_updateDistAndFramesToClosestBases(int runnerIdx);
void fn_3_833EC(int runnerIdx);
void fn_3_835B0(void);
void running_LiveBall_AI(void);
int possibleRunnerAIRelated(int runnerIdx, int frame);
int runnerAILiveBall(int runnerIdx);
int runnerAI_2(int runnerIdx);
int runnerAISubfunction4(int runnerIdx, int someFrames);
int runnerAISubfunction3(int runnerIdx, int arg1);
void fn_3_85744(int runnerIdx);
int runnerAISubfunction2(int runnerIdx, int arg1, int* arg2);
int fn_3_85A70(int runnerIdx);
void fn_3_85C44(int runnerIdx, int actionCode);
void running_AIStartSteals(void);
void runnerAISetRunningDirection(int runnerIdx, int actionCode);
int fn_3_8604C(int* outFielder);
int runnerAISubfunction(void);
void running_setRestrictedMovements(void);
void fn_3_86DFC(void);
void running_beginSteal_CheckForPerfect(void);
void fn_3_870AC(void);
void fn_3_871BC(void);
void updateRunnerValues(void);
void running_CheckForForceOuts_UpdateStamina_UpdateTagOutVars(void);
void running_UpdateTrackingValues_BasesEarned(void);
void running_CalcVeloAndIfBatterShouldStayStill(void);
void running_chainChompSprintRelated(void);
void setRunnerAngle(void);
void unused_forceOutSomething(void);
void running_checkForOuts(void);
void fn_3_889FC(void);
void running_ForceOutStateRelated(void);
void maybeUpdateRunnerNoRun(void);
void runnerOut(int runnerIdx);
void maybeHandleBaserunners(void);
void fn_3_89028(void);
void stealCancelLeadoffs(void);
void setDefaultInMemRunner(void);
void updateRunnerPosition(int runnerIdx, int basesAdvanced);
void fn_3_898BC(int runnerIdx, int rosterIdx);
void fn_3_89914(int srcIdx, int dstIdx);
void transferInMemRunnerValuesToNextRunnerIndex(void);
void initializeARunner(void);
void resetInMemRunners(void);
void fn_3_8A4C8(void);
void initBaseRunnersAfterFoulBall(void);
void fn_3_8A5A4(void);
void fn_3_8A618(void);
void fn_3_8A7B4(void);
void running_MainFunction(void);

#endif // !__GAME_BASERUNNING_RUNNER_H_
