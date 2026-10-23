#ifndef __GAME_BASERUNNING_RUNNER_H_
#define __GAME_BASERUNNING_RUNNER_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"

// Direction a runner AI asks for (runnerAI_setRunningDirection / runnerAI_requestRunningDirection).
typedef enum _RUNNER_DIRECTION_REQUEST {
    /* -2 */ RUNNER_DIRECTION_REQUEST_NONE = -2, // no decision; leave the runner alone
    /* -1 */ RUNNER_DIRECTION_REQUEST_BACK = -1,
    /*  0 */ RUNNER_DIRECTION_REQUEST_STOP,
    /*  1 */ RUNNER_DIRECTION_REQUEST_ADVANCE,
} RUNNER_DIRECTION_REQUEST;

void ccs_runnerChompHit_recover(int runnerIdx);
void ccs_runnerChompHit_updateKnockback(int runnerIdx);
void ccs_runnerChompHit_initKnockback(int runnerIdx);
void ccs_humanDirectionInput(int runnerIdx);
void ccs_humanDirectionInputIfLive(int runnerIdx);
void ccs_running_main(void);
void running_liveBall_human(void);
void running_atBatSteals_humanInput(void);
void running_sendOutRunnerToDugout(int runnerIdx);
int running_roundBaseDecision(int runnerIdx);
BOOL running_overrun1BIndicator(void);
int running_triggerSlideOrBodyCheck(int runnerIdx);
void running_updateRunner_roundBaseOrDugout(int runnerIdx);
int running_getDirectionOverride(int runnerIdx);
void running_updateRunner_chooseDirection(int runnerIdx);
void running_setDesiredDirection(int runnerIdx, int direction);
void running_basePathPosition(VecXYZ* out, f32 basesRan, f32 percent);
void running_lerpBetweenBases(VecXYZ* out, int fromBase, int toBase, f32 t);
void running_updatePosition(int runnerIdx);
void running_placeRunnerOnBase(int runnerIdx, int base);
void running_updateBaseArrival(int runnerIdx);
void running_stopRunner(int runnerIdx);
void running_updateLeadoff(int runnerIdx);
int running_overrunBaseControl(int runnerIdx);
int running_overrun1BControl(int runnerIdx);
void running_updateActionAndVelocity(int runnerIdx);
void running_calcSpeedVariables(int runnerIdx);
void running_calcFramesToClosestBases(int runnerIdx, s16* framesToPreviousBase, s16* framesToNextBase);
void running_updateDistAndFramesToClosestBases(int runnerIdx);
void running_updateRunner(int runnerIdx);
void running_liveBall_AIMashInput(void);
void running_liveBall_AI(void);
int runnerAI_ballStoppedDecision(int runnerIdx, int fastestFielderFrames);
int runnerAI_ballThrownDecision(int runnerIdx);
int runnerAI_ballHeldDecision(int runnerIdx);
int runnerAI_groundBallDecision(int runnerIdx, int fastestFielderFrames);
int runnerAI_flyBallDecision(int runnerIdx, int dropChanceGrade);
void runnerAI_updateUnusedBaseHoldFlag(int runnerIdx);
int runnerAI_checkRunnerAheadBlocking(int runnerIdx, int dropChanceGrade, int* arg2);
int runnerAI_getRundownDirection(int runnerIdx);
void runnerAI_requestRunningDirection(int runnerIdx, long actionCode);
void runnerAI_startSteals(void);
void runnerAI_setRunningDirection(int runnerIdx, int actionCode);
int runnerAI_getFastestFielderToBall(int* outFielder);
int runnerAI_gradeHitDropChance(void);
void running_updateMovementRestrictions(void);
void running_liveBall_clearStealing(void);
void running_atBatSteals_checkForPerfect(void);
void running_beginFrame_updateTaggedStates(void);
void running_updateStamina(void);
void running_beginFrame_storeRunnerState(void);
void running_beginFrame(void);
void running_updateBasesEarned(void);
void running_updateBatterHoldAndVelocity(void);
void ccs_updateRunnerAngles(void);
void running_updateRunnerAngles(void);
void running_beginFrame_checkForceOut(void);
void running_checkForOuts(void);
void running_updateEligibleToScore(void);
void running_updateForceStatus(void);
void running_endFrame(void);
void running_recordOut(int runnerIdx);
void running_initRunnersOnContact(void);
void running_initLiveBallWithoutContact(void);
void running_cancelLeadoffs(void);
void running_setDefaultRunners(void);
void running_advanceRunnerBases(int runnerIdx, int basesAdvanced);
void running_setRunnerRoster(int runnerIdx, int rosterIdx);
void running_transferRunnerIdentity(int srcIdx, int dstIdx);
void running_transferRunnerToNextIndex(void);
void running_initRunner(void);
void running_resetRunners(void);
void running_setBatterRunnerToBatterPos(void);
void running_resetRunnersAfterFoulBall(void);
void running_resetLeadoffDefaults(void);
void running_liveBall(void);
void running_atBatSteals(void);
void running_main(void);

#endif // !__GAME_BASERUNNING_RUNNER_H_
