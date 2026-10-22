#ifndef __GAME_BASERUNNING_RUNNER_H_
#define __GAME_BASERUNNING_RUNNER_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"

void fn_3_7D79C(int runnerIdx);
void fn_3_7D920(int runnerIdx);
void fn_3_7D9DC(int runnerIdx);
void runnerChangeDirectionHumanInput(int runnerIdx);
void running_humanDirectionInputIfLive(int runnerIdx);
void cCSRunningFun(void);
void running_LiveBall_Human(void);
void running_atBatSteals_humanInput(void);
void running_sendOutRunnerToDugout(int runnerIdx);
int running_roundBaseDecision(int runnerIdx);
BOOL running_overrun1stIndicator(void);
int running_triggerSlideOrBodyCheck(int runnerIdx);
void running_updateRunner_roundBaseOrDugout(int runnerIdx);
int running_DirectionOverrides(int runnerIdx);
void running_updateRunner_chooseDirection(int runnerIdx);
void running_setDesiredDirection(int runnerIdx, int direction);
void running_basePathPosition(VecXYZ* out, f32 basesRan, f32 percent);
void lerpBetweenBases(VecXYZ* out, int fromBase, int toBase, f32 t);
void running_updatePosition(int runnerIdx);
void running_placeRunnerOnBase(int runnerIdx, int base);
void running_updatePositionTracking_storeRBIs_stopAtNextBase_displaySafe(int runnerIdx);
void running_stopRunner(int runnerIdx);
void running_updateLeadoff(int runnerIdx);
int running_overrunBaseControl(int runnerIdx);
int runnerOverrun1BRelated(int runnerIdx);
void running_ActionControlAndVelocity(int runnerIdx);
void running_CalculateSpeedVariables(int runnerIdx);
void updateRunnerFramesToClosestBases(int runnerIdx, s16* framesToPreviousBase, s16* framesToNextBase);
void running_updateDistAndFramesToClosestBases(int runnerIdx);
void running_updateRunner(int runnerIdx);
void running_LiveBall_AI_mashInput(void);
void running_LiveBall_AI(void);
int possibleRunnerAIRelated(int runnerIdx, int frame);
int runnerAILiveBall(int runnerIdx);
int runnerAI_2(int runnerIdx);
int runnerAISubfunction4(int runnerIdx, int someFrames);
int runnerAISubfunction3(int runnerIdx, int arg1);
void fn_3_85744(int runnerIdx);
int runnerAISubfunction2(int runnerIdx, int arg1, int* arg2);
int fn_3_85A70(int runnerIdx);
void runnerAI_requestRunningDirection(int runnerIdx, long actionCode);
void running_AIStartSteals(void);
void runnerAISetRunningDirection(int runnerIdx, int actionCode);
int fn_3_8604C(int* outFielder);
int runnerAISubfunction(void);
void running_updateMovementRestrictions(void);
void running_liveBall_clearStealing(void);
void running_beginSteal_CheckForPerfect(void);
void running_beginFrame_updateTaggedStates(void);
void running_updateStamina(void);
void running_beginFrame_storeRunnerState(void);
void running_beginFrame(void);
void running_UpdateTrackingValues_BasesEarned(void);
void running_CalcVeloAndIfBatterShouldStayStill(void);
void running_chainChompSprintRelated(void);
void setRunnerAngle(void);
void running_beginFrame_checkForceOut(void);
void running_checkForOuts(void);
void running_updateEligibleToScore(void);
void running_ForceOutStateRelated(void);
void running_endFrame(void);
void runnerOut(int runnerIdx);
void maybeHandleBaserunners(void);
void fn_3_89028(void);
void stealCancelLeadoffs(void);
void setDefaultInMemRunner(void);
void updateRunnerPosition(int runnerIdx, int basesAdvanced);
void running_setRunnerRoster(int runnerIdx, int rosterIdx);
void running_transferRunnerIdentity(int srcIdx, int dstIdx);
void transferInMemRunnerValuesToNextRunnerIndex(void);
void initializeARunner(void);
void resetInMemRunners(void);
void running_setBatterRunnerToBatterPos(void);
void initBaseRunnersAfterFoulBall(void);
void resetRunnerLeadoffDefaults(void);
void running_liveBall(void);
void running_atBatSteals(void);
void running_MainFunction(void);

#endif // !__GAME_BASERUNNING_RUNNER_H_
