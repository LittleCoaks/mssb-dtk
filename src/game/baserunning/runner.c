#define SQRT2_LINKAGE static
#include "game/baserunning/runner.h"
#include "header_rep_data.h"
#include "game/baserunning/runner_base_rounding.h"
#include "game/fielding/fielder.h"
#include "game/math/game_math.h"
#include "game/ball/collision_primitives.h"
#include "game/camera/camera.h"
#include "static/UnknownHomes_Static.h"

extern u8 runnerConstants[][5];
extern f32 lbl_3_data_4B44[];
extern s16 lbl_3_data_4B48[];
extern u8 bodyCheckProbabiliities[][5];
extern u8 hugeAnimStruct[0x3154];
extern void fieldingRelatedAnimations(void* anim, int state);
extern void playCharacterSound(int charID, int soundIndex);
extern s16 lbl_3_data_4B40[];
extern s16 lbl_3_data_1C80[];
extern s16 chemThresholds[4];
extern int calculateChemistry(int teamBatting, s16 charIdA, s16 charIdB);
extern int fn_3_A6ABC(f32 x, f32 z);
extern f32 lbl_3_data_218BC[];
extern f32 lbl_3_data_4C44[];
extern s16 lbl_3_data_4C54[];
extern s16 lbl_3_data_1C58[][4];
extern s16 lbl_3_common_bss_37400[0x27];
extern s16 neg20ForRunningAI[];
extern VecXZ base_MoundCoordinates[5];
extern int estimatedThrowFramesBetweenTwoPoints(f32 x1, f32 z1, f32 x2, f32 z2);
extern void starMissionsQuantityBased(int missionType, int rosterLocation);
extern VecXZ lbl_3_data_4B28[];
extern f32 lbl_3_data_4B24;
extern f32 lbl_3_data_4B50;
extern s16 lbl_3_data_4B54[];
extern struct {
    VecXZ team[2];
} dugoutCoordinates[7];
extern f32 baseCoordsForRunning[][2];
extern f32 someRunningAngleArray[][3];
extern s16 lbl_3_data_21904[];
extern VecXZ lbl_3_data_4A54[][13];
extern s16 lbl_3_data_4B90[];
extern void initializeInMemRunner(int rosterID, int runnerIdx);
extern u32 fn_3_107DF8(int port);
extern void QueueTextToDisplay(int code, int arg1);
extern u8 pauseControl[0x264];
extern f32 lbl_3_data_4B88[];
extern f32 lbl_3_data_2191C[];
extern void endOfGameCheck(int arg);
extern void processScoreChanges(int arg);


static inline f32 addScaled(f32 base, f32 delta, f32 scale) {
    f32 scaled = delta * scale;
    return base + scaled;
}

static inline void runner_beginRunToDugout(InMemRunnerType* runner) {
    f32 dx;
    f32 dz;
    f32 dist;

    runner->nextBaseCoordinates.x =
        dugoutCoordinates[g_d_GameSettings.StadiumID].team[g_GameLogic.homeTeamBattingInd_fieldingTeam].x;
    runner->nextBaseCoordinates.z =
        dugoutCoordinates[g_d_GameSettings.StadiumID].team[g_GameLogic.homeTeamBattingInd_fieldingTeam].z;
    dz = runner->nextBaseCoordinates.z - runner->position.z;
    dx = runner->nextBaseCoordinates.x - runner->position.x;
    dist = dolsqrtf2(dx * dx + dz * dz);
    runner->velocity.x = dx / dist * lbl_3_data_4B50;
    runner->velocity.z = dz / dist * lbl_3_data_4B50;
    runner->velocity.y = 0.0f;
    runner->runningToDugoutFrameCounter = 0;
    runner->framesToReachDugout = (int)(dist / lbl_3_data_4B50) + 1;
    runner->runningToDugoutStage = 2;
}

static inline void runner_trackRunToDugout(InMemRunnerType* runner) {
    runner->runningToDugoutFrameCounter++;
    runner->framesToReachDugout--;
    runner->position.x += runner->velocity.x;
    runner->position.y += runner->velocity.y;
    runner->position.z += runner->velocity.z;
    if (runner->framesToReachDugout < 0) {
        runner->velocity.x = 0.0f;
        runner->velocity.y = 0.0f;
        runner->velocity.z = 0.0f;
        runner->runningToDugoutStage = 3;
    }
}

// .text:0x0008A958 size:0x73C mapped:0x806C99EC
void running_MainFunction(void) {
    InMemRunnerType* runner;
    int i;

    running_CheckForForceOuts_UpdateStamina_UpdateTagOutVars();
    running_setRestrictedMovements();
    if (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT) {
        if (g_GameLogic.battingAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam] != 0) {
            running_AIStartSteals();
        } else {
            InputStruct* inputs = &g_Controls[g_GameLogic.teams[g_GameLogic.teamBatting]];

            if (g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_PRE_PITCH ||
                g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_WINDUP ||
                g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_IN_AIR) {
                if (ACTIVE_TUTORIAL()) {
                    inputs = &g_Practice.inputs[g_GameLogic.teamBatting];
                }
                if (inputs->newButtonInput & INPUT_BUTTON_Y) {
                    if (inputs->controlStickAngle < 0) {
                        for (i = 1; i <= 3; i++) {
                            if (g_Runners[i].runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE && g_Runners[i].stealingStatus == 0) {
                                g_Runners[i].stealingStatus = 1;
                            }
                        }
                    } else {
                        if (inputs->controlStickAngle >= 0x1C0 && inputs->controlStickAngle <= 0x640) {
                            g_Runners[1].stealingStatus = 1;
                        }
                        if (inputs->controlStickAngle >= 0x5C0 && inputs->controlStickAngle <= 0xA40) {
                            g_Runners[2].stealingStatus = 1;
                        }
                        if (inputs->controlStickAngle >= 0x9C0 && inputs->controlStickAngle <= 0xE40) {
                            g_Runners[3].stealingStatus = 1;
                        }
                    }
                }
            }
        }
        running_beginSteal_CheckForPerfect();
    } else if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL) {
        if ((g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL || g_GameLogic.FrameCountOfCurrentPitch >= g_RunningLogic.someSituationTrackerFrames ||
             g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_BASERUNNING || g_FieldingLogic.liveBallBcOfPickoffOrStealCd != 0) &&
            g_FieldingLogic.playOverInd == 0) {
            int i;
            InMemRunnerType* runner;

            if (g_GameLogic.battingAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam] == 0) {
                running_LiveBall_Human();
            } else {
                running_LiveBall_AI();
            }
            runner = g_Runners;
            for (i = 0; i < 4; i++, runner++) {
                if (runner->runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE) {
                    if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd == 1 && runner->stealingStatus != 0 && runner->rosterID >= 0) {
                        runner->runningDirectionDesired = RUNNER_MOVEMENT_FORWARDS;
                    }
                    runner->stealingStatus = 0;
                }
            }
        }
    }
    runner = g_Runners;
    for (i = 0; i < 4; i++, runner++) {
        if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_NONE) {
            continue;
        }
        running_updateDistAndFramesToClosestBases(i);
            if (runner->runningToDugoutInd == 0 || runner->runningToDugoutStage == 0) {
                if (runner->actionCode == 0) {
                    if ((runner->framesSinceLastDirectionChange >= lbl_3_data_4C54[3] ||
                         (runner->runningDirectionCode != RUNNER_MOVEMENT_FORWARDS && runner->runningDirectionCode != 3)) &&
                        runner->runningDirectionDesired != 0) {
                        if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
                            if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                                runner->nextDirectionBeingProcessed = runner->runningDirectionDesired;
                            }
                        } else {
                            if ((i != 0 || runner->nextBase != 1) && runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                                runner->nextDirectionBeingProcessed = runner->runningDirectionDesired;
                            }
                            if (runner->nextDirectionBeingProcessed == 3 && runner->tagUpInd != 3 &&
                                runner->baseStandingOn >= 0) {
                                runner->nextDirectionBeingProcessed = 0;
                            }
                        }
                    }
                    {
                        int dir = running_DirectionOverrides(i);
                        if (dir != 0) {
                            runner->nextDirectionBeingProcessed = dir;
                        }
                    }
                }
            }
            if (runner->runningToDugoutInd != 0) {
                runner->baseRoundingState = 0;
                runner->actionCode = 0;
            } else {
                running_roundBaseDecision(i);
                running_triggerSlideOrBodyCheck(i);
                if (g_GameLogic.secondaryGameMode != SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
                    if (i == 0 && runner->nextBase == 1) {
                        running_overrun1stIndicator();
                    } else if (runner->baseRoundingState == 1) {
                        runner->baseRoundingState = 0;
                    }
                    running_sendOutRunnerToDugout(i);
                }
            }
            running_CalculateSpeedVariables(i);
            running_updatePositionTracking_storeRBIs_stopAtNextBase_displaySafe(i);
            running_updatePosition(i);
            running_updateDistAndFramesToClosestBases(i);
        {
            f32 dx = g_Ball.AtBat_Contact_BallPos.x - runner->position.x;
            f32 dz = g_Ball.AtBat_Contact_BallPos.z - runner->position.z;

            dx = dx * dx;
            dz = dz * dz;
            runner->distanceFromBall = dolsqrtf2(dx + dz);
        }
    }
    running_CalcVeloAndIfBatterShouldStayStill();
    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
        running_chainChompSprintRelated();
    } else {
        running_checkForOuts();
        running_ForceOutStateRelated();
        fn_3_889FC();
        setRunnerAngle();
    }
    running_UpdateTrackingValues_BasesEarned();
}


// .text:0x0008A7B4 size:0x1A4 mapped:0x806C9848
void fn_3_8A7B4(void) {
    if (g_GameLogic.battingAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam] != 0) {
        running_AIStartSteals();
    } else {
        InputStruct* inputs = &g_Controls[g_GameLogic.teams[g_GameLogic.teamBatting]];

        if (g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_PRE_PITCH ||
            g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_WINDUP ||
            g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_IN_AIR) {
            if (ACTIVE_TUTORIAL()) {
                inputs = &g_Practice.inputs[g_GameLogic.teamBatting];
            }
            if (inputs->newButtonInput & INPUT_BUTTON_Y) {
                if (inputs->controlStickAngle < 0) {
                    int i;
                    for (i = 1; i <= 3; i++) {
                        if (g_Runners[i].runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE && g_Runners[i].stealingStatus == 0) {
                            g_Runners[i].stealingStatus = 1;
                        }
                    }
                } else {
                    if (inputs->controlStickAngle >= 0x1C0 && inputs->controlStickAngle <= 0x640) {
                        g_Runners[1].stealingStatus = 1;
                    }
                    if (inputs->controlStickAngle >= 0x5C0 && inputs->controlStickAngle <= 0xA40) {
                        g_Runners[2].stealingStatus = 1;
                    }
                    if (inputs->controlStickAngle >= 0x9C0 && inputs->controlStickAngle <= 0xE40) {
                        g_Runners[3].stealingStatus = 1;
                    }
                }
            }
        }
    }
    running_beginSteal_CheckForPerfect();
}

// .text:0x0008A618 size:0x19C mapped:0x806C96AC
void fn_3_8A618(void) {
    if ((g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL || g_GameLogic.FrameCountOfCurrentPitch >= g_RunningLogic.someSituationTrackerFrames ||
         g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_BASERUNNING || g_FieldingLogic.liveBallBcOfPickoffOrStealCd != 0) &&
        g_FieldingLogic.playOverInd == 0) {
        int i;
        InMemRunnerType* runner;
        u8 pickoffOrStealCd;

        if (g_GameLogic.battingAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam] == 0) {
            running_LiveBall_Human();
        } else {
            running_LiveBall_AI();
        }
        pickoffOrStealCd = g_FieldingLogic.liveBallBcOfPickoffOrStealCd;
        runner = g_Runners;
        for (i = 0; i < 4; i++, runner++) {
            if (runner->runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE) {
                if (pickoffOrStealCd == 1 && runner->stealingStatus != 0 && runner->rosterID >= 0) {
                    runner->runningDirectionDesired = RUNNER_MOVEMENT_FORWARDS;
                }
                runner->stealingStatus = 0;
            }
        }
    }
}

// .text:0x0008A5A4 size:0x74 mapped:0x806C9638
void fn_3_8A5A4(void) {
    g_Runners[0].rosterID = -1;
    g_Runners[0]._121 = 10;
    g_Runners[0].delayBeforeStartingToRun = 30;
    g_Runners[0].leadoffDistancePercent = 0.1f;
    g_Runners[0].someCollisionCheck = 0;
    g_Runners[1].rosterID = -1;
    g_Runners[1]._121 = 10;
    g_Runners[1].delayBeforeStartingToRun = 30;
    g_Runners[1].leadoffDistancePercent = 0.1f;
    g_Runners[1].someCollisionCheck = 0;
    g_Runners[2].rosterID = -1;
    g_Runners[2]._121 = 10;
    g_Runners[2].delayBeforeStartingToRun = 30;
    g_Runners[2].leadoffDistancePercent = 0.1f;
    g_Runners[2].someCollisionCheck = 0;
    g_Runners[3].rosterID = -1;
    g_Runners[3]._121 = 10;
    g_Runners[3].delayBeforeStartingToRun = 30;
    g_Runners[3].leadoffDistancePercent = 0.1f;
    g_Runners[3].someCollisionCheck = 0;
}

// .text:0x0008A4E4 size:0xC0 mapped:0x806C9578
void initBaseRunnersAfterFoulBall(void) {
    int i;

    for (i = 0; i < 4; i++) {
        InMemRunnerType* runner = &g_Runners[i];

        runner->position.x = baseCoordsForRunning[i][0];
        runner->position.z = baseCoordsForRunning[i][1];
        runner->velocity.x = 0.0f;
        runner->velocity.y = 0.0f;
        runner->velocity.z = 0.0f;
        runner->startingBase_baseAchieved = i;
        runner->currentBase = i;
        runner->nextBase = (i + 1) & 3;
        runner->baseStandingOn = i;
        runner->baseRunningTowards = 0xFF;
        runner->leadOffStatus = 0;
    }
}

// .text:0x0008A4C8 size:0x1C mapped:0x806C955C
void fn_3_8A4C8(void) {
    g_Runners[0].position.x = g_Batter.batterPos.x;
    g_Runners[0].position.z = g_Batter.batterPos.z;
}

// .text:0x0008A350 size:0x178 mapped:0x806C93E4
void resetInMemRunners(void) {
    int i;

    for (i = 1; i < 4; i++) {
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE || g_d_GameSettings.bJMatchInd != 1 ||
            g_Runners[i].rosterID < 0) {
            g_Runners[i].rosterID = -1;
            g_Runners[i].battingHand = 0;
            g_Runners[i].runnerDidntReachOnError = 0;
            g_Runners[i].pitcherWhoLetRunnerOnBase = -1;
        }
    }
    g_RunningLogic.__0x20padding[0] = 0;
    for (i = 0; i < 4; i++) {
        g_Runners[i].position.x = baseCoordsForRunning[i][0];
        g_Runners[i].position.z = baseCoordsForRunning[i][1];
        g_Runners[i].velocity.x = 0.0f;
        g_Runners[i].velocity.y = 0.0f;
        g_Runners[i].velocity.z = 0.0f;
        g_Runners[i].startingBase_baseAchieved = i;
        g_Runners[i].currentBase = i;
        g_Runners[i].nextBase = (i + 1) & 3;
        g_Runners[i].baseStandingOn = i;
        g_Runners[i].baseRunningTowards = 0xFF;
        g_Runners[i].leadOffStatus = 0;
    }
}

// .text:0x0008A1D8 size:0x178 mapped:0x806C926C
void initializeARunner(void) {
    int i;

    for (i = 0; i < 4; i++) {
        g_Runners[i].position.x = baseCoordsForRunning[i][0];
        g_Runners[i].position.z = baseCoordsForRunning[i][1];
        g_Runners[i].velocity.x = 0.0f;
        g_Runners[i].velocity.y = 0.0f;
        g_Runners[i].velocity.z = 0.0f;
        g_Runners[i].startingBase_baseAchieved = i;
        g_Runners[i].currentBase = i;
        g_Runners[i].nextBase = (i + 1) & 3;
        g_Runners[i].baseStandingOn = i;
        g_Runners[i].baseRunningTowards = 0xFF;
        g_Runners[i].leadOffStatus = 0;
    }
    if (g_GameLogic.secondaryGameMode != SECONDARY_GAME_MODE_PRACTICE_BATTING) {
        for (i = 1; i < 4; i++) {
            if (g_Runners[i].rosterID >= 0) {
                initializeInMemRunner(g_Runners[i].rosterID, i);
            } else {
                g_Runners[i].runnerOnFieldOrOutOrScored = RUNNER_STATUS_NONE;
            }
        }
    }
    initializeInMemRunner(g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.homeTeamBattingInd_fieldingTeam]
                                                                   [g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam]][0],
                          0);
}

// .text:0x000899BC size:0x81C mapped:0x806C8A50
void transferInMemRunnerValuesToNextRunnerIndex(void) {
    int order[4];
    int i;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_Strikes.outs >= 3) {
        g_Runners[0].runnerOnFieldOrOutOrScored = RUNNER_STATUS_NONE;
        g_Runners[0].rosterID = -1;
        g_Runners[1].runnerOnFieldOrOutOrScored = RUNNER_STATUS_NONE;
        g_Runners[1].rosterID = -1;
        g_Runners[2].runnerOnFieldOrOutOrScored = RUNNER_STATUS_NONE;
        g_Runners[2].rosterID = -1;
        g_Runners[3].runnerOnFieldOrOutOrScored = RUNNER_STATUS_NONE;
        g_Runners[3].rosterID = -1;
    }
    order[0] = -1;
    g_RunningLogic.runnerTransferIndex[0] = -1;
    order[1] = -1;
    g_RunningLogic.runnerTransferIndex[1] = -1;
    order[2] = -1;
    g_RunningLogic.runnerTransferIndex[2] = -1;
    order[3] = -1;
    g_RunningLogic.runnerTransferIndex[3] = -1;
    if (g_Pitcher.strikeOutOrWalk == 2 && g_FieldingLogic.liveBallBcOfPickoffOrStealCd != 0) {
        for (i = 3; i >= 1; i--) {
            InMemRunnerType* runner = &g_Runners[i];
            if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD ||
                    runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_WALK_WHILE_STEALING) {
                if (runner->currentBase == i && runner->forcedToAdvanceInd != 0) {
                    order[i + 1] = i;
                } else {
                    order[runner->currentBase] = i;
                }
            }
        }
        order[1] = 0;
        for (i = 3; i >= 0; i--) {
            fn_3_89914(order[i], i);
        }
    } else if (g_Ball.maybebuntOn2Strikes != 0) {
        order[3] = 3;
        fn_3_89914(3, 3);
        order[2] = 2;
        fn_3_89914(2, 2);
        order[1] = 1;
        fn_3_89914(1, 1);
    } else if (g_Pitcher.strikeOutOrWalk == 3) {
        if (g_Runners[1].runnerOnFieldOrOutOrScored == RUNNER_STATUS_NONE) {
            order[3] = 3;
            fn_3_89914(3, 3);
            order[2] = 2;
            g_RunningLogic.runnerTransferIndex[2] = 2;
        } else if (g_Runners[2].runnerOnFieldOrOutOrScored == RUNNER_STATUS_NONE) {
            order[2] = 1;
            fn_3_89914(1, 2);
            order[3] = 3;
            fn_3_89914(3, 3);
        } else {
            order[3] = 2;
            fn_3_89914(2, 3);
            order[2] = 1;
            fn_3_89914(1, 2);
        }
        order[1] = 0;
        fn_3_89914(0, 1);
    } else if (g_Ball.deadBallReason == 3) {
        fn_3_89914(1, 3);
        order[3] = 1;
        order[2] = 0;
        fn_3_89914(0, 2);
        order[1] = -1;
        fn_3_89914(-1, 1);
    } else if (g_Ball.deadBallReason == 4) {
        if (g_Runners[1].baseReachedAtTimeOfThrow >= 0 &&
                g_Runners[1].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
                g_Runners[1].baseReachedAtTimeOfThrow == 1) {
            order[3] = 1;
        }
        if (g_Runners[0].baseReachedAtTimeOfThrow >= 0 &&
                g_Runners[0].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
            int idx = g_Runners[0].baseReachedAtTimeOfThrow + 2;
            if (idx < 4) {
                if (order[3] >= 0 && idx == 3) {
                    idx--;
                }
                order[idx] = 0;
            }
        }
        for (i = 3; i >= 1; i--) {
            fn_3_89914(order[i], i);
        }
    } else {
        for (i = 0; i < 4; i++) {
            InMemRunnerType* runner = &g_Runners[i];
            if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD ||
                    runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_WALK_WHILE_STEALING) {
                order[runner->currentBase] = i;
            }
        }
        for (i = 3; i >= 1; i--) {
            fn_3_89914(order[i], i);
        }
    }
}

// .text:0x00089914 size:0xA8 mapped:0x806C89A8
void fn_3_89914(int srcIdx, int dstIdx) {
    InMemRunnerType* src = &g_Runners[srcIdx];
    InMemRunnerType* dst = &g_Runners[dstIdx];

    if (srcIdx >= 0 && srcIdx <= 3) {
        if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_FREE_BAT_AND_RUNNING && srcIdx == 0) {
            dst->rosterID = g_Practice.rosterID;
        } else {
            dst->rosterID = src->rosterID;
            dst->battingHand = src->battingHand;
            dst->runnerDidntReachOnError = src->runnerDidntReachOnError;
            dst->pitcherWhoLetRunnerOnBase = src->pitcherWhoLetRunnerOnBase;
        }
        g_RunningLogic.runnerTransferIndex[srcIdx] = dstIdx;
    } else {
        dst->rosterID = -1;
        dst->runnerDidntReachOnError = 0;
        dst->pitcherWhoLetRunnerOnBase = -1;
    }
}

// .text:0x000898BC size:0x58 mapped:0x806C8950
void fn_3_898BC(int runnerIdx, int rosterIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];

    runner->rosterID = rosterIdx;
    runner->battingHand = inMemRoster[g_GameLogic.teamBatting][rosterIdx].stats.FieldingArm;
    if (runner->battingHand == 2) {
        runner->battingHand = BATTING_HAND_RIGHT;
    }
}

// .text:0x00089864 size:0x58 mapped:0x806C88F8
void updateRunnerPosition(int runnerIdx, int basesAdvanced) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];

    runner->currentBase += basesAdvanced;
    runner->nextBase = (runner->currentBase + 1) & 3;
    if (runner->currentBase >= 4) {
        runner->runnerOnFieldOrOutOrScored = RUNNER_STATUS_SCORED_DURING_PLAY;
        (*(s16*)&g_Scores._pad_50[0x4C])++;
    }
}

// .text:0x0008913C size:0x728 mapped:0x806C81D0
void setDefaultInMemRunner(void) {
    f32 zero = 0.0f;
    f32 one = 1.0f;
    f32 slide = 0.03f;
    f32 dx;
    f32 dz;
    int i;

    g_RunningLogic._02 = 0;
    g_RunningLogic._00 = 0;
    g_RunningLogic._10 = 0;
    g_RunningLogic.someSituationTrackerFrames = 0x14;
    *(u8*)&g_RunningLogic.__0x20padding[10] = 0xFF;
    g_Runners[0].position.x = g_Batter.batterPos.x;
    g_Runners[0].position.z = g_Batter.batterPos.z;
    for (i = 0; i < 4; i++) {
        InMemRunnerType* runner = &g_Runners[i];
        if (runner->rosterID >= 0) {
            runner->runnerOnFieldOrOutOrScored = RUNNER_STATUS_ON_FIELD;
            g_RunningLogic._02 |= 1 << (i * 4);
            g_RunningLogic._00 |= 1 << (i * 4);
            g_RunningLogic._10++;
        } else {
            runner->runnerOnFieldOrOutOrScored = RUNNER_STATUS_NONE;
        }
        runner->baseStandingOn = -1;
        runner->currentBase = i;
        runner->nextBase = (i + 1) & 3;
        runner->tagUpInd = TAG_UP_TYPE_NONE;
        runner->restrictedMovementCodes = PREVENT_PASSING_TYPE_NONE;
        runner->relatedToRunnerPos = 0;
        runner->outType = 0;
        runner->forceOutCd = FORCE_OUT_TYPE_NOT_FORCED_TO_ADVANCE;
        runner->isEligibleToScore = 1;
        runner->furthestBaseForcedToGoToOnWalk = 0;
        runner->framesSinceStealStarted = 0;
        runner->batterStayInBattersBoxReason = 0;
        runner->baseOfFailedBodyCheck = -1;
        runner->timeStandingOnBase = 0;
        runner->framesSinceOut = 0;
        runner->baseNumberEarned_NotIncludingFieldersChoice = -1;
        runner->stealingStatus = 0;
        runner->framesSinceStealInput = 0;
        runner->unused_someBaseNum = -1;
        runner->unused_const_1 = 1;
        runner->stamina = lbl_3_data_4C54[9];
        runner->staminaMult = one;
        runner->accelerationStaminaEffect = one;
        runner->accelerationStaminaEffectWhileChangingDirection = one;
        if (i == 0) {
            runner->runningAngle = 3.1415927f;
        }
        if (i >= 1) {
            runner->runningAngle = someRunningAngleArray[i][0];
        }
        dx = g_Ball.AtBat_Contact_BallPos.x - runner->position.x;
        dz = g_Ball.AtBat_Contact_BallPos.z - runner->position.z;
        dx = dx * dx;
        dz = dz * dz;
        runner->distanceFromBall = dolsqrtf2(dx + dz);
        runner->groundVelocity[0] = zero;
        runner->groundVelocity[1] = zero;
        runner->groundVelocity[2] = zero;
        runner->groundVelocity[3] = zero;
        runner->acceleration = zero;
        runner->percentRanPerFrame_slideAdj = zero;
        runner->slidingAdjustment_backwards = slide;
        runner->slidingAdjustment_forwards = slide;
        runner->roundingStrengthPercent = zero;
        runner->mashVeloAdjustment = zero;
        runner->mashPercent = zero;
        runner->actionFrames_countUp = 0;
        runner->actionFrames_countDown = 0;
        runner->_110 = 0;
        runner->framesSinceLastDirectionChange = 0;
        runner->slideHomeFrames_CountDown = 0;
        runner->runningDirectionDesired = 0;
        runner->nextDirectionBeingProcessed = 0;
        runner->runningDirectionCode = 0;
        runner->offsetFromNormalRunningPathInd = 0;
        runner->actionCode = 0;
        runner->actionStage = 0;
        runner->forceOutType_unsed = 0;
        runner->baseRoundingState = 0;
        runner->overrun1st_doneChecking = 0;
        runner->overRun1BStage = 0;
        runner->overrunning1BIndicator = 0;
        runner->overrunBaseStage = 0;
        runner->offsetPositionForRoundingInd = 0;
        runner->roundingInitiaializedInd = 0;
        runner->runningToDugoutInd = 0;
        runner->runningToDugoutStage = 0;
        runner->turnaroundCode = 0;
        runner->turningAroundInd = 0;
        runner->framesSinceLastMash = 0;
        runner->someCountdown_unused = 0;
        runner->_151 = 0;
        runner->scoredOnGRD = 0;
        if (runner->rosterID >= 0) {
            runner->runningDirectionCode = 2;
        }
        runner->runnerDirectionCode_stored = runner->runningDirectionCode;
        if (runner->leadOffStatus == 0) {
            if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_BASERUNNING) {
                runner->leadOffStatus = 0;
            } else {
                runner->leadOffStatus = 1;
            }
            runner->leadoffDurationFrames = 0;
            runner->leadOffTotalFrameCountDown = 45;
            fn_3_810C4(i, i);
        }
    }
    g_AiLogic._77 = 0;
    g_RunningLogic.nOffensivePlayersAtStartOfPlay = g_RunningLogic._10;
    g_AiLogic._44 = lbl_3_data_1C58[g_GameLogic.homeTeamBattingInd_fieldingTeam][1];
    g_RunningLogic.__0x20padding[0] = 0;
    if (g_RunningLogic._02 & 0x1000) {
        g_RunningLogic.__0x20padding[0] = 1;
    }
    if (g_RunningLogic._02 & 0x100) {
        g_RunningLogic.__0x20padding[0]++;
    }
    for (i = 1; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_NONE) {
            g_Runners[i].forcedToAdvanceInd = 0;
        } else if (g_Runners[i - 1].forcedToAdvanceInd == 0) {
            g_Runners[i].forcedToAdvanceInd = 0;
        } else {
            g_Runners[i].forcedToAdvanceInd = 1;
        }
    }
    g_Runners[0].forcedToAdvanceInd = 1;
    g_Runners[0].unused_AIRelated = 1;
    g_Runners[0].battingHand = g_Batter.batterHand;
    g_Runners[0].runnerDidntReachOnError = 1;
    g_Runners[0].pitcherWhoLetRunnerOnBase =
        g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0];
    g_Runners[0].batterStayInBattersBoxReason = 1;
    g_Runners[0].position.x = g_Batter.batterPos.x;
    g_Runners[0].position.y = 0.0f;
    g_Runners[0].position.z = g_Batter.batterPos.z;
    g_Runners[0].positionStored.x = g_Batter.batterPos.x;
    g_Runners[0].positionStored.y = 0.0f;
    g_Runners[0].positionStored.z = g_Batter.batterPos.z;
    g_Runners[1].positionStored.x = g_Runners[1].position.x;
    g_Runners[1].positionStored.y = g_Runners[1].position.y;
    g_Runners[1].positionStored.z = g_Runners[1].position.z;
    g_Runners[2].positionStored.x = g_Runners[2].position.x;
    g_Runners[2].positionStored.y = g_Runners[2].position.y;
    g_Runners[2].positionStored.z = g_Runners[2].position.z;
    g_Runners[3].positionStored.x = g_Runners[3].position.x;
    g_Runners[3].positionStored.y = g_Runners[3].position.y;
    g_Runners[3].positionStored.z = g_Runners[3].position.z;
    if (g_Batter.batterHand == 0) {
        (*(s16*)g_RunningLogic.__0x10padding) = (int)(28.0f / g_Runners[0].maximumBaseVelocity) + 0x23;
    } else {
        (*(s16*)g_RunningLogic.__0x10padding) = (int)(26.5f / g_Runners[0].maximumBaseVelocity) + 0x23;
    }
    (*(s16*)g_RunningLogic.__0x10padding) += 0x14;
    g_Batter.runnersOnBase = 0;
    g_Batter.chemLinksOnBase = 0;
    for (i = 1; i < 4; i++) {
        if (g_Runners[i].rosterID >= 0 &&
            calculateChemistry(g_GameLogic.teamBatting, g_Batter.charID, g_Runners[i].charID) >= chemThresholds[3]) {
            g_Batter.chemLinksOnBase++;
            g_Batter.runnersOnBase |= 1 << (i - 1);
        }
    }
}

// .text:0x0008911C size:0x20 mapped:0x806C81B0
void stealCancelLeadoffs(void) {
    g_Runners[0].leadOffStatus = 0;
    g_Runners[1].leadOffStatus = 0;
    g_Runners[2].leadOffStatus = 0;
    g_Runners[3].leadOffStatus = 0;
}

// .text:0x00089028 size:0xF4 mapped:0x806C80BC
void fn_3_89028(void) {
    InMemRunnerType* runner = &g_Runners[1];
    int i;

    g_Runners[0].leadOffStatus = 0;
    g_Runners[1].leadOffStatus = 0;
    g_Runners[2].leadOffStatus = 0;
    g_Runners[3].leadOffStatus = 0;
    for (i = 1; i < 4; i++, runner++) {
        runner->unused_AIRelated = 0;
        runner->tagUpInd = TAG_UP_TYPE_NONE;
        if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
            runnerAISetRunningDirection(i, 1);
        }
    }
    if (g_Strikes.balls >= 4) {
        g_Runners[0].runnerOnFieldOrOutOrScored = RUNNER_STATUS_WALK_WHILE_STEALING;
    } else if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd == 4) {
        g_Runners[0].runnerOnFieldOrOutOrScored = RUNNER_STATUS_ON_FIELD;
        runnerAISetRunningDirection(0, 1);
    } else {
        g_Runners[0].runnerOnFieldOrOutOrScored = RUNNER_STATUS_SCORED_DEAD_BALL;
    }
}

// .text:0x00088F98 size:0x90 mapped:0x806C802C
void maybeHandleBaserunners(void) {
    int i;

    for (i = 0; i < 4; i++) {
        if (i == 0) {
            runnerAISetRunningDirection(i, 1);
        }
        if (i == 0) {
            g_Runners[i].unused_AIRelated = 1;
        } else {
            g_Runners[i].unused_AIRelated = 0;
            if (g_Strikes.storedOuts < 2) {
                g_Runners[i].tagUpInd = TAG_UP_TYPE_IN_AIR;
            } else {
                g_Runners[i].tagUpInd = TAG_UP_TYPE_NONE;
            }
        }
    }
}

// .text:0x00088D88 size:0x210 mapped:0x806C7E1C
void runnerOut(int runnerIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];
    int i;

    if (g_Strikes.outs < 3 && !g_GameLogic.EventTriggers_EndOfGame &&
        runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
        if (g_GameLogic.freeFieldingPracticeInd == 0) {
            g_Strikes.outs++;
        } else if ((g_Practice.practiceType_2 == PRACTICE_TYPE_FIELDING && g_Practice.practiceLevel == 1) ||
                   g_Practice.practiceLevel == 7 || g_Practice.practiceLevel == 6) {
            g_Strikes.outs++;
        }

        if (g_Ball.maybeBuntInd != 0 && g_Strikes.strikes >= 3) {
            QueueTextToDisplay(0x16, 0);
        } else if (runner->fractionalBasesRan >= 3.8f && g_Ball.baseBallAndFielderAreOn == 0) {
            QueueTextToDisplay(1, 1);
        } else {
            QueueTextToDisplay(1, 0);
        }

        for (i = 0; i < 3; i++) {
            if (g_Strikes.runnerIndexForEachOutThisPitch[i] == -1) {
                g_Strikes.runnerIndexForEachOutThisPitch[i] = runnerIdx;
                break;
            }
        }

        if (g_Strikes.outs == 3) {
            if (runner->forceOutCd == FORCE_OUT_TYPE_FORCED_TO_ADVANCE) {
                g_Strikes.forcedOutToEndInningInd = 1;
            } else {
                processScoreChanges(1);
            }
            endOfGameCheck(0);
            if (g_GameLogic.EventTriggers_EndOfGame != 0) {
                QueueTextToDisplay(0xd, 0);
            } else {
                QueueTextToDisplay(5, 0);
            }
        }
        runner->runnerOnFieldOrOutOrScored = RUNNER_STATUS_OUT_DURING_PLAY;
    }
}

// .text:0x00088C24 size:0x164 mapped:0x806C7CB8
void maybeUpdateRunnerNoRun(void) {
    running_CalcVeloAndIfBatterShouldStayStill();
    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
        running_chainChompSprintRelated();
    } else {
        running_checkForOuts();
        running_ForceOutStateRelated();
        fn_3_889FC();
        setRunnerAngle();
    }
    running_UpdateTrackingValues_BasesEarned();
}

// .text:0x00088B18 size:0x10C mapped:0x806C7BAC
#pragma dont_inline on
void running_ForceOutStateRelated(void) {
    int i;
    int state = 0;

    if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != 0 && g_FieldingLogic.liveBallBcOfPickoffOrStealCd != 4) {
        state = 1;
    }
    for (i = 0; i < 4; i++) {
        InMemRunnerType* runner = &g_Runners[i];
        if (runner->forceOutCd == FORCE_OUT_TYPE_OUT_ON_FORCE) {
            state = 2;
        } else {
            runner->forceOutCd = FORCE_OUT_TYPE_NOT_FORCED_TO_ADVANCE;
            if (g_Ball.AtBat_ContactResult >= 0 && g_FieldingLogic.infieldFlyIndicator == 0) {
                if (state != 0) {
                    if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_NONE) {
                        state = 1;
                    }
                    if (state == 2 && runner->startingBase_baseAchieved == runner->currentBase) {
                        runner->forceOutCd = -1;
                    }
                } else if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                    if ((runner->baseStandingOn < 0 || runner->baseStandingOn != ((runner->startingBase_baseAchieved + 1) & 3)) &&
                        runner->startingBase_baseAchieved == runner->currentBase) {
                        runner->forceOutCd = FORCE_OUT_TYPE_FORCED_TO_ADVANCE;
                    }
                } else {
                    state = 1;
                }
            }
        }
    }
}
#pragma dont_inline reset

// .text:0x000889FC size:0x11C mapped:0x806C7A90
void fn_3_889FC(void) {
    int i;
    int contactResult = g_Ball.AtBat_ContactResult;
    u8 landingZone = g_Ball.landingSpotZoneAwayFromHome;
    u8 ballZone = g_Ball.ballZoneAwayFromHome;
    u8 infieldFly = g_FieldingLogic.infieldFlyIndicator;
    u8 ballState = g_Ball.ballState;
    for (i = 0; i < 4; i++) {
        InMemRunnerType* runner = &g_Runners[i];
        if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
            if ((contactResult == BALL_RESULT_TYPE_CAUGHT || infieldFly == 2) && landingZone <= 1) {
                runner->isEligibleToScore = 0;
            } else if (ballZone <= 1 && ballState != BALL_STATE_HIT && (u16)contactResult > BALL_RESULT_TYPE_LANDED &&
                       runner->currentBase != 0 && runner->currentBase < 3) {
                runner->isEligibleToScore = 0;
            }
        }
    }
}

// .text:0x00088408 size:0x5F4 mapped:0x806C749C
void running_checkForOuts(void) {
    InMemRunnerType* runner;
    int i;

    if (g_Strikes.outs < 3) {
        s16 contact = g_Ball.AtBat_ContactResult;

        if (contact == BALL_RESULT_TYPE_LANDED || contact == BALL_RESULT_TYPE_FOUL || contact == BALL_RESULT_TYPE_FIELDED) {
            g_Runners[0].tagUpInd = TAG_UP_TYPE_NONE;
            g_Runners[1].tagUpInd = TAG_UP_TYPE_NONE;
            g_Runners[2].tagUpInd = TAG_UP_TYPE_NONE;
            g_Runners[3].tagUpInd = TAG_UP_TYPE_NONE;
        }
        if (contact != BALL_RESULT_TYPE_FOUL) {
            if (g_FieldingLogic.runnerBeingTargettedForOut >= 0 && g_FieldingLogic.runnerBeingTargettedForOut <= 3) {
                runner = &g_Runners[g_FieldingLogic.runnerBeingTargettedForOut];
            }

            if (contact == BALL_RESULT_TYPE_CAUGHT || g_FieldingLogic.infieldFlyIndicator == 2) {
                runnerOut(0);
                g_Runners[0].outType = 1;
                if (g_Ball.fielderWhoGotLastOut < 0) {
                    g_Ball.fielderWhoGotLastOut = g_Ball.fielderWBallIndex;
                }
            }

            if (g_FieldingLogic.bodyCheckResult != 0 && g_FieldingLogic.tagAnimationType == 1 && runner->tagUpInd != TAG_UP_TYPE_TAGGED) {
                if (runner->baseOfFailedBodyCheck >= 0) {
                    s16 fielder;

                    runnerOut(g_FieldingLogic.runnerBeingTargettedForOut);
                    runner->outType = 3;
                    g_FieldingLogic.runnerBeingTargettedForOut = -1;
                    g_FieldingLogic.tagAnimationType = 0;
                    if (g_Ball.fielderWhoGotLastOut < 0) {
                        fielder = g_Ball.fielderWithBallIndexStored2;
                        g_Ball.fielderWhoGotLastOut = fielder;
                        if (fielder >= 6 && runner->baseOfFailedBodyCheck == 0 && g_Ball.numberOfThrowsDuringPlay == 2 &&
                            g_Ball.timeSinceBallPickedUp < specialFielderActionConstants._40[7]) {
                            g_UnkSound_32718._08 = 4;
                            g_FieldingLogic.bigPlayFielderIndex = fielder;
                            if (!g_d_GameSettings.exhibitionMatchInd && lbl_3_common_bss_37400[0x20] == g_GameLogic.teamFielding) {
                                starMissionsQuantityBased(2, g_Fielders[fielder].rosterLocation);
                            }
                        }
                    }
                    if (!g_d_GameSettings.exhibitionMatchInd && lbl_3_common_bss_37400[0x20] == g_GameLogic.teamFielding) {
                        if (g_Ball.throwingFielder >= 0 && g_FieldingLogic.laser_2 != 0) {
                            starMissionsQuantityBased(8, g_Fielders[g_Ball.throwingFielder].rosterLocation);
                        }
                    }
                }
            } else if (g_FieldingLogic.tagAnimationType >= 2 && g_FieldingLogic.tagAnimationType <= 5 &&
                       g_FieldingLogic.tagResult_1out_2safe == 2) {
                if (runner->tagUpInd == TAG_UP_TYPE_TAGGED) {
                    runnerOut(g_FieldingLogic.runnerBeingTargettedForOut);
                    runner->outType = 4;
                    g_FieldingLogic.runnerBeingTargettedForOut = -1;
                    if (!g_d_GameSettings.exhibitionMatchInd && lbl_3_common_bss_37400[0x20] == g_GameLogic.teamFielding) {
                        if (g_Ball.throwingFielder >= 0 && g_FieldingLogic.laser_2 != 0) {
                            starMissionsQuantityBased(8, g_Fielders[g_Ball.throwingFielder].rosterLocation);
                        }
                    }
                } else if ((runner->baseStandingOn < 0 || runner->forceOutCd == FORCE_OUT_TYPE_FORCED_TO_ADVANCE) &&
                           (runner->actionStage == 0 || runner->actionFrames_countDown >= 15)) {
                    runnerOut(g_FieldingLogic.runnerBeingTargettedForOut);
                    if (runner->forceOutCd == FORCE_OUT_TYPE_FORCED_TO_ADVANCE) {
                        runner->forceOutCd = FORCE_OUT_TYPE_OUT_ON_FORCE;
                    }
                    runner->outType = 3;
                    g_FieldingLogic.runnerBeingTargettedForOut = -1;
                    if (g_Ball.fielderWhoGotLastOut < 0) {
                        g_Ball.fielderWhoGotLastOut = g_Ball.fielderWithBallIndexStored2;
                    }
                    if (!g_d_GameSettings.exhibitionMatchInd && lbl_3_common_bss_37400[0x20] == g_GameLogic.teamFielding) {
                        if (g_Ball.throwingFielder >= 0 && g_FieldingLogic.laser_2 != 0) {
                            starMissionsQuantityBased(8, g_Fielders[g_Ball.throwingFielder].rosterLocation);
                        }
                    }
                }
                g_FieldingLogic.tagAnimationType = 0;
                g_FieldingLogic.tagResult_1out_2safe = 0;
                g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
            }

            if (g_Ball.baseBallAndFielderAreOn >= 1 && g_Runners[g_Ball.baseBallAndFielderAreOn].tagUpInd == TAG_UP_TYPE_TAGGED) {
                runnerOut(g_Ball.baseBallAndFielderAreOn);
                g_Runners[g_Ball.baseBallAndFielderAreOn].outType = 4;
                if (!g_d_GameSettings.exhibitionMatchInd && lbl_3_common_bss_37400[0x20] == g_GameLogic.teamFielding) {
                    if (g_Ball.throwingFielder >= 0 && g_FieldingLogic.laser_2 != 0) {
                        starMissionsQuantityBased(8, g_Fielders[g_Ball.throwingFielder].rosterLocation);
                    }
                }
            }
        }
    }

    for (i = 0; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_OUT_DURING_PLAY) {
            if (g_Runners[i].framesSinceOut < 0x7FFE) {
                g_Runners[i].framesSinceOut++;
            } else {
                g_Runners[i].framesSinceOut = 0x7FFF;
            }
        }
    }
}

// .text:0x00088228 size:0x1E0 mapped:0x806C72BC
void unused_forceOutSomething(void) {
    if (g_Ball.baseBallAndFielderAreOn >= 0 && g_Ball.AtBat_ContactResult >= 0 &&
        g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_CAUGHT &&
        g_Fielders[g_Ball.fielderWBallIndex].always0_forcePlayRelated == 0) {
        int index = (g_Ball.baseBallAndFielderAreOn + 3) & 3;

        if (g_Runners[index].forceOutCd == FORCE_OUT_TYPE_FORCED_TO_ADVANCE) {
            runnerOut(index);
            g_Runners[index].forceOutCd = FORCE_OUT_TYPE_OUT_ON_FORCE;
            g_Runners[index].outType = 2;
            if (g_Ball.fielderWhoGotLastOut < 0) {
                if (g_Ball.throwingFielder < 0) {
                    g_Ball.fielderWhoGotLastOut = g_Ball.fielderWBallIndex;
                } else {
                    g_Ball.fielderWhoGotLastOut = g_Ball.throwingFielder;
                    if (g_FieldingLogic.laser_2 != 0 && !g_d_GameSettings.exhibitionMatchInd) {
                        if (lbl_3_common_bss_37400[0x20] == g_GameLogic.teamFielding) {
                            starMissionsQuantityBased(8, g_Fielders[g_Ball.throwingFielder].rosterLocation);
                        }
                    }
                    if ((s8)g_FieldingLogic.fielderActionBeingProcessed_prev > 0 && g_FieldingLogic.bigPlayPotential != 0) {
                        g_UnkSound_32718._08 = 4;
                        g_FieldingLogic.bigPlayFielderIndex = g_Ball.fielderWithBallIndexStored2;
                        if (!g_d_GameSettings.exhibitionMatchInd && lbl_3_common_bss_37400[0x20] == g_GameLogic.teamFielding) {
                            starMissionsQuantityBased(2, g_Fielders[g_Ball.fielderWithBallIndexStored2].rosterLocation);
                        }
                    }
                }
            }
        }
    }
}

// .text:0x00087E80 size:0x3A8 mapped:0x806C6F14
void setRunnerAngle(void) {
    int i;

    for (i = 0; i < 4; i++) {
        InMemRunnerType* runner = &g_Runners[i];
        if (runner->runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE) {
            f32 angle = runner->runningAngle;
            f32 velocityAngle = atan2(-runner->velocity.x, -runner->velocity.y);

            if (g_GameLogic.secondaryGameMode != SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
                if (i == 0 && (runner->batterStayInBattersBoxReason == 1 ||
                               (g_Pitcher.strikeOutOrWalk == 1 && g_FieldingLogic.liveBallBcOfPickoffOrStealCd != 4))) {
                    angle = 3.1415927f;
                } else if (i == 0 && g_Batter.hitTrajectory != HIT_TRAJECTORY_0 &&
                           runner->batterStayInBattersBoxReason != 0) {
                    if (runner->groundVelocity[0] >= 0.01f) {
                        angle = velocityAngle;
                    } else {
                        angle = 3.1415927f;
                    }
                } else if (i == 0 &&
                           (g_FieldingLogic.liveBallBcOfPickoffOrStealCd == 1 ||
                            g_FieldingLogic.liveBallBcOfPickoffOrStealCd == 2) &&
                           g_Strikes.outs < 3) {
                    angle = 3.1415927f;
                } else if (runner->actionCode != 0) {
                    if (runner->actionStage == 2 && runner->actionFrames_countDown <= 1) {
                        angle = someRunningAngleArray[runner->baseStandingOn][0];
                    }
                } else if (runner->overRun1BStage >= 2) {
                    angle = atan2(-runner->velocity.x, -runner->velocity.z);
                } else if (runner->baseRoundingState == 2 && runner->baseStandingOn >= 0) {
                    angle = atan2(-runner->velocity.x, -runner->velocity.z);
                } else if (runner->leadOffStatus == 1) {
                    angle = atan2(-runner->velocity.x, -runner->velocity.z);
                } else if (runner->runningToDugoutInd == 0) {
                    goto chainChompAngle;
                } else if (runner->runningToDugoutInd == 2 && runner->slideHomeFrames_CountDown != 0) {
                    angle = runner->runningAngle;
                } else if (0.0f == runner->velocity.x) {
                    angle = runner->runningAngle;
                } else {
                    angle = atan2(-runner->velocity.x, -runner->velocity.z);
                }
            } else {
            chainChompAngle:
                if (runner->runningDirectionCode != 0 && runner->runningDirectionCode != 2) {
                    if (runner->leadOffStatus == 2) {
                        angle = someRunningAngleArray[runner->currentBase][0];
                    } else if (0.0f == runner->velocity.x && 0.0f == runner->velocity.z) {
                        angle = atan2(-runner->velocityStored.x, -runner->velocityStored.z);
                        if (runner->turningAroundInd == 1 && runner->runningDirectionCode == 1 &&
                            runner->acceleration > 0.0f) {
                            angle = radianAngleReduction(3.1415927f + angle);
                        }
                    } else {
                        angle = atan2(-runner->velocity.x, -runner->velocity.z);
                    }
                } else {
                    angle = someRunningAngleArray[runner->currentBase][0];
                }
            }
            runner->runningAngle = angle;
            if (g_Ball.ballZoneAwayFromHome != 0) {
                angle = atan2(-(g_Ball.AtBat_Contact_BallPos.x - runner->position.x),
                              -(g_Ball.AtBat_Contact_BallPos.z - runner->position.z));
            }
            runner->angleToBall = angle;
        }
    }
}

// .text:0x00087CC8 size:0x1B8 mapped:0x806C6D5C
#pragma dont_inline on
void running_chainChompSprintRelated(void) {
    int i;

    for (i = 0; i < 4; i++) {
        InMemRunnerType* runner = &g_Runners[i];
        if (runner->runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE) {
            f32 angle;

            atan2(-runner->velocity.x, -runner->velocity.y);
            if (g_Minigame._1B15[(s8)g_Minigame._18FC[i]] == 1) {
                angle = radianAngleReduction(3.1415927410125732 + atan2(-runner->velocity.x, -runner->velocity.z));
            } else if (runner->runningDirectionCode != 0 && runner->runningDirectionCode != 2) {
                if (0.0f == runner->velocity.x && 0.0f == runner->velocity.z) {
                    angle = atan2(-runner->velocityStored.x, -runner->velocityStored.z);
                    if (runner->turningAroundInd == 1 && runner->runningDirectionCode == 1 &&
                        runner->acceleration > 0.0f) {
                        angle = radianAngleReduction(3.1415927f + angle);
                    }
                } else {
                    angle = atan2(-runner->velocity.x, -runner->velocity.z);
                }
            } else if (0.0f == runner->percentTowardsNextBase) {
                angle = someRunningAngleArray[runner->currentBase][2];
            } else {
                angle = someRunningAngleArray[runner->currentBase][0];
            }
            runner->runningAngle = angle;
            runner->angleToBall = angle;
        }
    }
}
#pragma dont_inline reset

// .text:0x00087AE8 size:0x1E0 mapped:0x806C6B7C
void running_CalcVeloAndIfBatterShouldStayStill(void) {
    InMemRunnerType* batter = &g_Runners[0];

    batter->batterStayInBattersBoxReason = 0;
    if (g_GameLogic.secondaryGameMode != SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER) {
            batter->batterStayInBattersBoxReason = 1;
        } else if (g_Ball.framesSinceHit < 0) {
            batter->batterStayInBattersBoxReason = 1;
        } else if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd == 1 || g_FieldingLogic.liveBallBcOfPickoffOrStealCd == 2 ||
                   g_FieldingLogic.liveBallBcOfPickoffOrStealCd == 3) {
            if (g_Strikes.outs < 3) {
                batter->batterStayInBattersBoxReason = 1;
            }
        } else if (batter->outType == 0 || batter->runnerOnFieldOrOutOrScored != RUNNER_STATUS_OUT_DURING_PLAY) {
            if (g_Ball.framesSinceHit < batter->delayBeforeStartingToRun) {
                batter->batterStayInBattersBoxReason = 2;
            } else if (g_Batter.hitTrajectory == HIT_TRAJECTORY_4 && g_Ball.framesSinceHit < 90) {
                batter->batterStayInBattersBoxReason = 2;
            } else if (g_Batter.hitTrajectory == HIT_TRAJECTORY_3 || g_Batter.hitTrajectory == HIT_TRAJECTORY_6) {
                batter->batterStayInBattersBoxReason = 3;
            }
        }
    }
    g_Runners[0].velocity.x = g_Runners[0].position.x - g_Runners[0].positionStored.x;
    g_Runners[0].velocity.y = g_Runners[0].position.y - g_Runners[0].positionStored.y;
    g_Runners[0].velocity.z = g_Runners[0].position.z - g_Runners[0].positionStored.z;
    g_Runners[1].velocity.x = g_Runners[1].position.x - g_Runners[1].positionStored.x;
    g_Runners[1].velocity.y = g_Runners[1].position.y - g_Runners[1].positionStored.y;
    g_Runners[1].velocity.z = g_Runners[1].position.z - g_Runners[1].positionStored.z;
    g_Runners[2].velocity.x = g_Runners[2].position.x - g_Runners[2].positionStored.x;
    g_Runners[2].velocity.y = g_Runners[2].position.y - g_Runners[2].positionStored.y;
    g_Runners[2].velocity.z = g_Runners[2].position.z - g_Runners[2].positionStored.z;
    g_Runners[3].velocity.x = g_Runners[3].position.x - g_Runners[3].positionStored.x;
    g_Runners[3].velocity.y = g_Runners[3].position.y - g_Runners[3].positionStored.y;
    g_Runners[3].velocity.z = g_Runners[3].position.z - g_Runners[3].positionStored.z;
}

// .text:0x0008781C size:0x2CC mapped:0x806C68B0
void running_UpdateTrackingValues_BasesEarned(void) {
    InMemRunnerType* runner;
    int i;

    g_RunningLogic._00 = 0;
    g_RunningLogic._04 = 0;
    g_RunningLogic._10 = 0;
    runner = g_Runners;
    for (i = 0; i < 4; i++, runner++) {
        if (runner->percentTowardsNextBase > 0.2f) {
            runner->relatedToRunnerPos = 0;
        }
        if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
            g_RunningLogic._00 |= 1 << (i * 4);
            g_RunningLogic._10++;
            if (runner->currentBase <= 3) {
                g_RunningLogic._04 |= 1 << (runner->currentBase * 4);
            }
        }
        if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FOUL && runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
            runner->runnerOnFieldOrOutOrScored = RUNNER_STATUS_SCORED_DEAD_BALL;
        }
        if (runner->baseStandingOn >= 0) {
            if (runner->timeStandingOnBase < 0x7FFE) {
                runner->timeStandingOnBase++;
            } else {
                runner->timeStandingOnBase = 0x7FFF;
            }
        } else {
            runner->timeStandingOnBase = 0;
        }
        runner->nextBase = (runner->currentBase + 1) & 3;
        if (runner->runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE) {
            VecSrcDst inVec;
            CollisionStruct outCollision;

            inVec.src.x = runner->position.x;
            inVec.src.y = -1.0f;
            inVec.src.z = runner->position.z;
            inVec.dst.x = runner->position.x;
            inVec.dst.y = 1.0f;
            inVec.dst.z = runner->position.z;
            runner->someCollisionCheck = checkCollision(&inVec, &outCollision, 0, 0);
        }
    }
    if (g_Runners[0].baseNumberEarned_NotIncludingFieldersChoice == -1) {
        u8 ballState = g_Ball.ballState;
        u8 ballZone = g_Ball.ballZoneAwayFromHome;
        u32 caughtZone = (u8)g_Ball.ballZoneWhenCaught;
        u8 playOver = g_FieldingLogic.playOverInd;

        for (i = 0; i < 4; i++) {
            runner = &g_Runners[i];
            if ((ballState == BALL_STATE_HELD && ballZone <= 2) || caughtZone <= 1 || playOver != 0) {
                if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_OUT_DURING_PLAY) {
                    runner->baseNumberEarned_NotIncludingFieldersChoice = runner->currentBase;
                } else if (runner->runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE && runner->baseStandingOn >= 0) {
                    runner->baseNumberEarned_NotIncludingFieldersChoice = runner->baseStandingOn;
                }
            } else if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) {
                runner->baseNumberEarned_NotIncludingFieldersChoice = 0;
            }
        }
    }
}

// .text:0x00087424 size:0x3F8 mapped:0x806C64B8
void running_CheckForForceOuts_UpdateStamina_UpdateTagOutVars(void) {
    updateRunnerValues();
    if (g_GameLogic.secondaryGameMode != SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT &&
        g_GameLogic.secondaryGameMode != SECONDARY_GAME_MODE_PRACTICE_BASERUNNING) {
        if (g_Ball.baseBallAndFielderAreOn >= 0 && g_Ball.AtBat_ContactResult >= 0 &&
            g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_CAUGHT &&
            g_Fielders[g_Ball.fielderWBallIndex].always0_forcePlayRelated == 0) {
            int index = (g_Ball.baseBallAndFielderAreOn + 3) & 3;

            if (g_Runners[index].forceOutCd == FORCE_OUT_TYPE_FORCED_TO_ADVANCE) {
                runnerOut(index);
                g_Runners[index].forceOutCd = FORCE_OUT_TYPE_OUT_ON_FORCE;
                g_Runners[index].outType = 2;
                if (g_Ball.fielderWhoGotLastOut < 0) {
                    if (g_Ball.throwingFielder < 0) {
                        g_Ball.fielderWhoGotLastOut = g_Ball.fielderWBallIndex;
                    } else {
                        g_Ball.fielderWhoGotLastOut = g_Ball.throwingFielder;
                        if (g_FieldingLogic.laser_2 != 0 && !g_d_GameSettings.exhibitionMatchInd) {
                            if (lbl_3_common_bss_37400[0x20] == g_GameLogic.teamFielding) {
                                starMissionsQuantityBased(8, g_Fielders[g_Ball.throwingFielder].rosterLocation);
                            }
                        }
                        if ((s8)g_FieldingLogic.fielderActionBeingProcessed_prev > 0 &&
                            g_FieldingLogic.bigPlayPotential != 0) {
                            g_UnkSound_32718._08 = 4;
                            g_FieldingLogic.bigPlayFielderIndex = g_Ball.fielderWithBallIndexStored2;
                            if (!g_d_GameSettings.exhibitionMatchInd &&
                                lbl_3_common_bss_37400[0x20] == g_GameLogic.teamFielding) {
                                starMissionsQuantityBased(2, g_Fielders[g_Ball.fielderWithBallIndexStored2].rosterLocation);
                            }
                        }
                    }
                }
            }
        }

        fn_3_871BC();

        g_Runners[0].tagType = 0;
        g_Runners[1].tagType = 0;
        g_Runners[2].tagType = 0;
        g_Runners[3].tagType = 0;
        if (g_FieldingLogic.tagAnimationType == 2 || g_FieldingLogic.tagAnimationType == 4) {
            s16 targetIdx = g_FieldingLogic.runnerBeingTargettedForOut;
            if (targetIdx >= 0) {
                InMemRunnerType* target = &g_Runners[targetIdx];
                if (target->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                    target->tagType = 1;
                }
                if (g_FieldingLogic.framesRunnerIsOutBy < 5 && target->actionCode != 0) {
                    target->tagType = 2;
                }
                if (!g_d_GameSettings.exhibitionMatchInd && lbl_3_common_bss_37400[0x20] == g_GameLogic.teamFielding) {
                    starMissionsQuantityBased(6, g_Fielders[g_Ball.fielderWBallIndex].rosterLocation);
                }
            }
        }
    }
}

// .text:0x000872CC size:0x158 mapped:0x806C6360
void updateRunnerValues(void) {
    int i;
    for (i = 0; i < 4; i++) {
        InMemRunnerType* runner = &g_Runners[i];
        if (runner->runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE) {
            runner->baseStandingOn_Stored = runner->baseStandingOn;
            runner->positionStored.x = runner->position.x;
            runner->positionStored.y = runner->position.y;
            runner->positionStored.z = runner->position.z;
            runner->velocityStored.x = runner->velocity.x;
            runner->velocityStored.y = runner->velocity.y;
            runner->velocityStored.z = runner->velocity.z;
            runner->fractionalBasesRan_stored = runner->fractionalBasesRan;
            runner->percentTowardsNextBase_stored = runner->percentTowardsNextBase;
            runner->runningDirectionDesired = 0;
            runner->newButtonThisFrame_forMashPurposes = 0;
            if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT && g_Strikes.storedOuts < 2 &&
                runner->tagUpInd == TAG_UP_TYPE_IN_AIR) {
                runner->tagUpInd = TAG_UP_TYPE_TAGGED;
                if (runner->baseStandingOn == runner->startingBase_baseAchieved) {
                    runner->tagUpInd = TAG_UP_TYPE_NONE;
                }
            }
            if (runner->someCountdown_unused != 0) {
                runner->someCountdown_unused--;
                if (runner->someCountdown_unused == 0) {
                    runner->_151 = 0;
                }
            }
            if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL) {
                runner->leadOffStatus = 0;
            }
        }
    }
    if (g_Ball.framesSinceHit != 1) {
        return;
    }
    if (g_Ball.maxYOfHit >= 5.0f) {
        if (g_Ball.landingSpotZoneAwayFromHome >= 2) {
            g_RunningLogic.someSituationTrackerFrames = 10;
        }
    }
}

// .text:0x000871BC size:0x110 mapped:0x806C6250
void fn_3_871BC(void) {
    InMemRunnerType* runner = g_Runners;
    int i;
    int runDrain = lbl_3_data_4C54[10];
    int turnDrain = lbl_3_data_4C54[11];
    int maxStamina = lbl_3_data_4C54[9];
    f32 staminaCoeff = lbl_3_data_4C44[1];
    f32 accelCoeff = lbl_3_data_4C44[2];
    f32 turnAccelCoeff = lbl_3_data_4C44[3];
    for (i = 0; i < 4; i++, runner++) {
        if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
            int drain = 0;
            f32 ratio;
            if (runner->groundVelocity[0] >= 0.1f) {
                drain = runDrain;
            }
            if (runner->turnaroundCode != 0) {
                drain += turnDrain;
            }
            if (drain != 0) {
                runner->stamina -= drain;
                if (runner->stamina < 0) {
                    runner->stamina = 0;
                }
            }
            ratio = 1.0f - (f32)runner->stamina / (f32)maxStamina;
            runner->staminaMult = 1.0f - staminaCoeff * ratio;
            runner->accelerationStaminaEffect = 1.0f - accelCoeff * ratio;
            runner->accelerationStaminaEffectWhileChangingDirection = 1.0f - turnAccelCoeff * ratio;
        }
    }
}

// .text:0x000870AC size:0x110 mapped:0x806C6140
void fn_3_870AC(void) {
    g_Runners[0].tagType = 0;
    g_Runners[1].tagType = 0;
    g_Runners[2].tagType = 0;
    g_Runners[3].tagType = 0;
    if (g_FieldingLogic.tagAnimationType == 2 || g_FieldingLogic.tagAnimationType == 4) {
        s16 targetIdx = g_FieldingLogic.runnerBeingTargettedForOut;
        if (targetIdx >= 0) {
            InMemRunnerType* runner = &g_Runners[targetIdx];
            if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                runner->tagType = 1;
            }
            if (g_FieldingLogic.framesRunnerIsOutBy < 5 && runner->actionCode != 0) {
                runner->tagType = 2;
            }
            if (!g_d_GameSettings.exhibitionMatchInd && lbl_3_common_bss_37400[0x20] == g_GameLogic.teamFielding) {
                starMissionsQuantityBased(6, g_Fielders[g_Ball.fielderWBallIndex].rosterLocation);
            }
        }
    }
}

// .text:0x00086EF8 size:0x1B4 mapped:0x806C5F8C
void running_beginSteal_CheckForPerfect(void) {
    InMemRunnerType* runner;
    int i;

    runner = &g_Runners[1];
    for (i = 1; i < 4; i++, runner++) {
        if (runner->runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE && runner->stealingStatus != 0) {
            if (runner->framesSinceStealInput < 254) {
                runner->framesSinceStealInput++;
            } else {
                runner->framesSinceStealInput = 255;
            }
            if (g_Pitcher.pitchTotalTimeCounter > 0 && runner->stealingStatus == 1) {
                if (g_Pitcher.pitchTotalTimeCounter == lbl_3_data_4B90[2]) {
                    int lo = lbl_3_data_4B90[2] - lbl_3_data_4B90[1];
                    int hi = lbl_3_data_4B90[2] - lbl_3_data_4B90[0];
                    if (runner->framesSinceStealInput >= lo &&
                        runner->framesSinceStealInput <= hi) {
                        runner->stealingStatus = 3;
                        runner->leadOffStatus = 0;
                        if (runner->rosterID >= 0) {
                            runner->runningDirectionDesired = 1;
                        }
                    }
                } else if (g_Pitcher.pitchTotalTimeCounter >= lbl_3_data_4B90[3]) {
                    runner->stealingStatus = 2;
                    runner->leadOffStatus = 0;
                    if (runner->rosterID >= 0) {
                        runner->runningDirectionDesired = 1;
                    }
                }
            }
            if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                if (runner->runningDirectionCode == 1 && runner->furthestBaseForcedToGoToOnWalk == 0) {
                    int k;
                    BOOL allBasesBeforeOccupied = TRUE;

                    for (k = 1; k < i; k++) {
                        if (g_Runners[k].runnerOnFieldOrOutOrScored == RUNNER_STATUS_NONE) {
                            allBasesBeforeOccupied = FALSE;
                        }
                    }
                    if (allBasesBeforeOccupied) {
                        runner->furthestBaseForcedToGoToOnWalk = i + 1;
                    } else {
                        runner->furthestBaseForcedToGoToOnWalk = 1;
                    }
                }
                if (runner->furthestBaseForcedToGoToOnWalk != 0) {
                    if (runner->framesSinceStealStarted < 0x7FFE) {
                        runner->framesSinceStealStarted++;
                    } else {
                        runner->framesSinceStealStarted = 0x7FFF;
                    }
                }
            }
        }
    }
}

// .text:0x00086DFC size:0xFC mapped:0x806C5E90
void fn_3_86DFC(void) {
    int i;

    for (i = 0; i < 4; i++) {
        InMemRunnerType* runner = &g_Runners[i];

        if (runner->runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE) {
            if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd == 1 && runner->stealingStatus != 0 &&
                runner->rosterID >= 0) {
                runner->runningDirectionDesired = 1;
            }
            runner->stealingStatus = 0;
        }
    }
}

// .text:0x0008679C size:0x660 mapped:0x806C5830
void running_setRestrictedMovements(void) {
    int precedingRunnerNum = -1;
    f32 precedingFrac = -1.0f;
    InMemRunnerType* runner;
    int runnerNum;
    int i;

    g_Runners[0].restrictedMovementCodes_stored = g_Runners[0].restrictedMovementCodes;
    g_Runners[0].restrictedMovementCodes = PREVENT_PASSING_TYPE_NONE;
    g_Runners[1].restrictedMovementCodes_stored = g_Runners[1].restrictedMovementCodes;
    g_Runners[1].restrictedMovementCodes = PREVENT_PASSING_TYPE_NONE;
    g_Runners[2].restrictedMovementCodes_stored = g_Runners[2].restrictedMovementCodes;
    g_Runners[2].restrictedMovementCodes = PREVENT_PASSING_TYPE_NONE;
    g_Runners[3].restrictedMovementCodes_stored = g_Runners[3].restrictedMovementCodes;
    g_Runners[3].restrictedMovementCodes = PREVENT_PASSING_TYPE_NONE;

    if (g_Strikes.outs >= 3) {
        return;
    }

    runner = &g_Runners[3];
    for (runnerNum = 3; runnerNum >= 0; runner--, runnerNum--) {
        if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
            if (runnerNum == 1 && g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_CAUGHT && g_FieldingLogic.infieldFlyIndicator == 0 &&
                g_FieldingLogic.liveBallBcOfPickoffOrStealCd == 0 && runner->fractionalBasesRan <= 1.2f &&
                g_Ball.framesSinceHit >= 1) {
                if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR && g_Ball.framesUntilBallHitsGround < 120) {
                    f32 dx = base_MoundCoordinates[1].x - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
                    f32 dz = base_MoundCoordinates[1].z - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
                    f32 sqx;
                    f32 sqz;
                    f32 dist;

                    sqx = dx * dx;
                    sqz = dz * dz;
                    dist = dolsqrtf2(sqx + sqz);
                    if (dist < 10.0f) {
                        goto next;
                    }
                }
                if (g_Batter.hitTrajectory != HIT_TRAJECTORY_3 && g_Runners[0].runnerOnFieldOrOutOrScored != RUNNER_STATUS_OUT_DURING_PLAY) {
                    runner->restrictedMovementCodes |= PREVENT_PASSING_TYPE_PREVENT_BACKWARD;
                    if (runner->runningDirectionCode == 3 && runner->tagUpInd != TAG_UP_TYPE_NONE) {
                        runner->restrictedMovementCodes |= PREVENT_PASSING_TYPE_TAG_UP;
                    }
                }
            } else if (runnerNum == 0 && g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR &&
                       g_Runners[1].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
                       g_Runners[1].fractionalBasesRan < 2.0f && g_Runners[1].runningDirectionCode == 3) {
                runner->restrictedMovementCodes |= PREVENT_PASSING_TYPE_PREVENT_FORWARD;
            } else if (precedingFrac < 0.0f) {
                if (runner->fractionalBasesRan >= 3.75f && g_GameLogic.secondaryGameMode != SECONDARY_GAME_MODE_PRACTICE_BASERUNNING &&
                    g_Strikes.storedOuts < 2) {
                    if (runner->tagUpInd != TAG_UP_TYPE_NONE) {
                        runner->restrictedMovementCodes |= PREVENT_PASSING_TYPE_PREVENT_CROSSINGPLATE;
                    } else if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR || g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FOUL) {
                        runner->restrictedMovementCodes |= PREVENT_PASSING_TYPE_PREVENT_CROSSINGPLATE;
                    }
                }
            } else {
                InMemRunnerType* preceding = &g_Runners[precedingRunnerNum];
                f32 gap = precedingFrac - runner->fractionalBasesRan;

                if (runner->runningDirectionCode == 3) {
                    gap -= 0.15f;
                } else if (runner->runningDirectionCode == 2) {
                    gap -= 0.1f;
                }
                if (preceding->runningDirectionCode == 3) {
                    gap -= 0.05f;
                }
                if (runner->currentBase != preceding->currentBase && preceding->baseStandingOn < 0) {
                    gap -= 0.15f;
                }
                if (gap < 0.3f) {
                    runner->restrictedMovementCodes |= PREVENT_PASSING_TYPE_PREVENT_FORWARD;
                    preceding->restrictedMovementCodes |= PREVENT_PASSING_TYPE_PREVENT_BACKWARD;
                    if (preceding->runningDirectionCode == 3 && preceding->tagUpInd != TAG_UP_TYPE_NONE &&
                        (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR || g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT)) {
                        preceding->restrictedMovementCodes |= PREVENT_PASSING_TYPE_TAG_UP;
                    }
                    if (preceding->percentTowardsNextBase < 0.5f && preceding->baseStandingOn == -1 &&
                        runner->percentTowardsNextBase > 0.5f && runner->baseStandingOn == -1) {
                        if (preceding->distToCurrentBase <= runner->distToNextBase) {
                            if (preceding->runningDirectionCode == 3 && runner->baseStandingOn == -1) {
                                preceding->restrictedMovementCodes &= 0xFF & ~PREVENT_PASSING_TYPE_PREVENT_BACKWARD;
                            } else if (runner->runningDirectionCode == 1 && preceding->baseStandingOn == -1) {
                                runner->restrictedMovementCodes &= 0xFF & ~PREVENT_PASSING_TYPE_PREVENT_FORWARD;
                            } else if (runner->baseStandingOn == -1) {
                                preceding->restrictedMovementCodes &= 0xFF & ~PREVENT_PASSING_TYPE_PREVENT_BACKWARD;
                            } else if (preceding->baseStandingOn == -1) {
                                runner->restrictedMovementCodes &= 0xFF & ~PREVENT_PASSING_TYPE_PREVENT_FORWARD;
                            }
                        } else {
                            if (preceding->tagUpInd != TAG_UP_TYPE_NONE && runner->baseStandingOn == -1) {
                                preceding->restrictedMovementCodes &= 0xFF & ~PREVENT_PASSING_TYPE_PREVENT_BACKWARD;
                            } else if (runner->runningDirectionCode == 1 && preceding->baseStandingOn == -1) {
                                runner->restrictedMovementCodes &= 0xFF & ~PREVENT_PASSING_TYPE_PREVENT_FORWARD;
                            } else if (preceding->runningDirectionCode == 3 && runner->baseStandingOn == -1) {
                                preceding->restrictedMovementCodes &= 0xFF & ~PREVENT_PASSING_TYPE_PREVENT_BACKWARD;
                            } else if (preceding->baseStandingOn == -1) {
                                runner->restrictedMovementCodes &= 0xFF & ~PREVENT_PASSING_TYPE_PREVENT_FORWARD;
                            } else if (runner->baseStandingOn == -1) {
                                preceding->restrictedMovementCodes &= 0xFF & ~PREVENT_PASSING_TYPE_PREVENT_BACKWARD;
                            }
                        }
                    }
                }
            }
        next:
            precedingFrac = runner->fractionalBasesRan;
            precedingRunnerNum = runnerNum;
        }
    }

    runner = &g_Runners[0];
    for (i = 0; i <= 1; i++, runner++) {
        int j;
        s16 nextBase;
        s16 count = 0;

        nextBase = runner->currentBase + 1;

        if (nextBase <= 3 && !(runner->percentTowardsNextBase < 0.75f)) {

            for (j = i + 1; j < 4; j++) {
                if (g_Runners[j].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD && nextBase == g_Runners[j].currentBase) {
                    count++;
                }
            }
            if (count >= 2) {
                runner->restrictedMovementCodes |= PREVENT_PASSING_TYPE_PREVENT_FORWARD;
            }
        }
    }
}

// .text:0x00086118 size:0x684 mapped:0x806C51AC
int runnerAISubfunction(void) {
    int bestTime = 9999;
    int bestFrame = 0;
    int bestFielder = -1;
    int frame;
    int i;
    int j;
    int diff;

    if (g_Ball.landingSpotZoneAwayFromHome <= 1 && g_Ball.maxYOfHit < 3.5f && g_Ball.framesSinceHit <= 45 &&
        g_Ball.Hit_HorizontalPower > 80) {
        for (i = 2; i < 6; i++) {
            if (g_Fielders[i].groundDistanceFromBall < 2.0f &&
                g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > g_Fielders[i].distanceFromHomePlate) {
                return 2;
            }
        }
        return 7;
    }

    if ((g_Ball.physicsSubstruct.velocity.y < 0.0f && g_Ball.AtBat_Contact_BallPos.y < 2.0f) ||
        g_Ball.maxYOfHit < 2.0f) {
        f32 dx = g_Ball.AtBat_Contact_BallPos.x - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
        f32 dz = g_Ball.AtBat_Contact_BallPos.z - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
        f32 sqx;
        f32 sqz;

        sqx = dx * dx;
        sqz = dz * dz;
        dolsqrtf2(sqx + sqz);
        frame = 1;
    } else {
        f32 dx;
        f32 dz;
        f32 sqx;
        f32 sqz;

        for (frame = g_Ball.framesUntilBallHitsGround; frame > 0; frame -= 5) {
            if (g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.y >= 2.0f) {
                frame++;
                for (j = 0; j < 5; j++) {
                    if (g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.y < 2.0f) {
                        break;
                    }
                }
                break;
            }
        }
        if (frame < 1) {
            frame = 1;
        }
        dx = g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.x - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
        dz = g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.z - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
        sqx = dx * dx;
        sqz = dz * dz;
        dolsqrtf2(sqx + sqz);
    }

    i = 1;
    if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome < 25.0f && g_Ball.hangtimeOfHit > 30 &&
        g_Ball.maxYOfHit > 3.0f) {
        i = 0;
    }
    if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome < 18.0f && g_Ball.hangtimeOfHit > 30 &&
        g_Ball.maxYOfHit > 4.0f) {
        i = 0;
    }

    if (g_Ball.maxYOfHit <= 3.0f) {
        int nearFielder = -1;

        for (; i < 6; i++) {
            u8 code = g_FieldingLogic.fielderAutoMovementCode[i];

            if (code == 1 || code == 10 || code == 11) {
                if (g_Fielders[i].groundDistanceFromBall < 3.0f &&
                    g_Ball.physicsSubstruct.hitLandingSpotDistFromHome + 3.0f > g_Fielders[i].distanceFromHomePlate) {
                    if (g_Fielders[i].groundDistanceFromBall < 1.5f * g_Fielders[i].hitbox[0]) {
                        return 1;
                    }
                    if (g_Fielders[i].distanceFromHomePlate >
                        1.5f * g_Fielders[i].groundDistanceFromBall + g_Ball.ballDistanceFromHome) {
                        return 1;
                    }
                }
                if (g_Fielders[i].groundDistanceFromBall < 5.0f &&
                    2.0f + g_Ball.ballDistanceFromHome < g_Fielders[i].distanceFromHomePlate &&
                    5.0f + g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > g_Fielders[i].distanceFromHomePlate) {
                    nearFielder = i;
                }
            }
        }
        if (nearFielder >= 0) {
            return 3;
        }
        return 5;
    }

    for (; i < 9; i++) {
        u8 code = g_FieldingLogic.fielderAutoMovementCode[i];

        if (code == 1 || code == 10 || code == 11) {
            if (g_Fielders[i].groundDistanceFromBall < 3.0f &&
                g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > g_Fielders[i].distanceFromHomePlate) {
                int time = fRunningTimeToDestinationPlus7(i, g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.x,
                                                          g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.z) -
                           10;

                if (bestTime > time) {
                    bestTime = time;
                    bestFrame = frame;
                    if (g_Ball.physicsSubstruct.futureCoordsAndDist[frame].dist > 1.0f + g_Fielders[i].distanceFromHomePlate) {
                        bestTime = time + 15;
                    }
                }
                bestFielder = i;
            } else {
                int landingTime = fRunningTimeToDestinationPlus7(i, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x,
                                                                 g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z) -
                                  10;
                int time = fRunningTimeToDestinationPlus7(i, g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.x,
                                                          g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.z) -
                           10;

                if (landingTime < time) {
                    if (bestTime > landingTime) {
                        bestFrame = g_Ball.framesUntilBallHitsGround;
                        bestTime = landingTime + 3;
                    }
                } else if (bestTime > time) {
                    bestTime = time;
                    bestFrame = frame;
                }
            }
        }
    }

    diff = bestTime - bestFrame;
    if (g_GameLogic.battingAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam] != 0) {
        diff += lbl_3_data_1C80[g_GameLogic.runnerAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam]];
    }

    if (bestTime <= 0) {
        return 0;
    }
    if (g_Ball.someCollisionVariable != 0 && diff < 5) {
        return 3;
    }
    if (diff < -60) {
        return 0;
    }
    if (diff < -30) {
        return 1;
    }
    if (diff < -5) {
        return 2;
    }
    if (diff < 8) {
        if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome < 40.0f) {
            if (diff <= 5) {
                return 3;
            }
        } else {
            return 3;
        }
    }
    if (bestFielder >= 0 && g_Ball.AtBat_Contact_BallPos.y < g_Fielders[bestFielder].hitbox[6]) {
        return 3;
    }
    if (diff < 20) {
        return 4;
    }
    if (diff < 40) {
        return 5;
    }
    return (diff < 90) ? 6 : 7;
}

// .text:0x0008604C size:0xCC mapped:0x806C50E0
int fn_3_8604C(int* outFielder) {
    int i;
    int best = 9999;

    for (i = 0; i < 9; i++) {
        u8 code = g_FieldingLogic.fielderAutoMovementCode[i];

        if (code == 1 || code == 10 || code == 11) {
            int frame = 1;
            int time;

            do {
                time = fRunningTimeToDestinationPlus7(i, g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.x,
                                                      g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.z);
                if (time < frame + 15) {
                    break;
                }
                frame += 5;
            } while (frame < 120);

            if (frame >= 120) {
                if (best >= 120) {
                    best = 120;
                }
            } else if (best > time) {
                best = time;
                *outFielder = i;
            }
        }
    }
    return best;
}

// .text:0x00085EF4 size:0x158 mapped:0x806C4F88
void runnerAISetRunningDirection(int runnerIdx, int actionCode) {
    s16 baseOn;
    u8 currentBase;
    InMemRunnerType* runner = &g_Runners[runnerIdx];

    if (runner->runnerOnFieldOrOutOrScored != RUNNER_STATUS_ON_FIELD) {
        return;
    }
    if (runner->tagUpInd == TAG_UP_TYPE_TAGGED && actionCode != -1) {
        return;
    }
    if (runner->actionCode != 0 && runner->actionStage != 0) {
        if (runner->actionInForwardDirectionInd == 1) {
            runner->baseRunningTowards = runner->nextBase;
        } else {
            runner->baseRunningTowards = runner->currentBase;
        }
        return;
    }
    if (actionCode == 1) {
        runner->baseRunningTowards = runner->nextBase;
    }
    if (actionCode == -1) {
        currentBase = runner->currentBase;
        if (currentBase == 0) {
            return;
        }
        if (runner->runningDirectionCode == 1 && runner->baseStandingOn >= 0 && runner->tagUpInd == TAG_UP_TYPE_NONE) {
            if (runner->baseRoundingState == 1) {
                return;
            }
            runner->runningDirectionCode = 2;
            return;
        }
        baseOn = runner->baseStandingOn;
        if (baseOn >= 0) {
            if (baseOn == 1) {
                return;
            }
            if (runnerIdx == 0) {
                return;
            }
            if (runner->tagUpInd == TAG_UP_TYPE_NONE) {
                return;
            }
            runner->baseRunningTowards = (baseOn + 3) & 3;
        } else {
            runner->baseRunningTowards = currentBase;
        }
    }
    if (actionCode == 0 && runnerIdx == 0 && runner->currentBase == 0) {
        return;
    }
    if (actionCode == 0) {
        runner->runningDirectionDesired = 2;
        return;
    }
    if (actionCode == 1) {
        runner->runningDirectionDesired = 1;
        return;
    }
    runner->runningDirectionDesired = 3;
}

// .text:0x00085CB0 size:0x244 mapped:0x806C4D44
void running_AIStartSteals(void) {
    InMemRunnerType* runner;
    int i;

    if (g_Ball.pitchHangtimeCounter <= 30 && g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_WINDUP) {
        if (g_Strikes.outs == 2 && g_Strikes.GameControls_StrikeBallBitVector == 0x23) {
            runner = &g_Runners[1];
            for (i = 1; i <= 3; i++, runner++) {
                if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_NONE) {
                    return;
                }
                if (g_Pitcher.pitchTotalTimeCounter >= g_AiLogic.batterAIStealingStartFrame) {
                    fn_3_85C44(i, 1);
                }
            }
        } else if (g_AiLogic.batterAIStealIndicator != 0) {
            runner = &g_Runners[1];
            for (i = 1; i <= 2; i++, runner++) {
                if (g_Pitcher.pitchTotalTimeCounter >= g_AiLogic.batterAIStealingStartFrame) {
                    if (runner->stealingStatus == 0) {
                        if (g_AiLogic.batterAIStealingStartFrame < lbl_3_data_4B90[2]) {
                            runner->stealingStatus = 3;
                        } else {
                            runner->stealingStatus = 2;
                        }
                        runner->leadOffStatus = 0;
                    }
                    fn_3_85C44(i, 1);
                }
            }
        } else if (g_AiLogic._74 == 2 && g_Pitcher.pitchTotalTimeCounter >= g_AiLogic.batterAIStealingStartFrame) {
            fn_3_85C44(3, 1);
        }
    }
}

// .text:0x00085C44 size:0x6C mapped:0x806C4CD8
void fn_3_85C44(int runnerIdx, int actionCode) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];

    if (runner->baseRoundingState != 1 || runner->overRun1BStage < 2 || actionCode == 1) {
        if (actionCode == -1 && runner->startingBase_baseAchieved == runner->baseStandingOn) {
            actionCode = 0;
        }
        runnerAISetRunningDirection(runnerIdx, actionCode);
    }
}

// .text:0x00085A70 size:0x1D4 mapped:0x806C4B04
int fn_3_85A70(int runnerIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];
    int nextBase;
    int currentBase;
    int framesToNext;
    int framesToCurrent;
    u8 direction;
    int base;
    s16 target;
    s16 framesToNextBase;
    s16 framesToPreviousBase;
    int result;

    if (g_FieldingLogic.somethingForTryingTagOutTargetBase == 9 && g_FieldingLogic.runnerChasingAfter != runnerIdx) {
        return -2;
    }
    if (runner->baseStandingOn >= 0) {
        return -2;
    }

    nextBase = runner->nextBase;
    currentBase = runner->currentBase;
    if (nextBase == g_FieldingLogic.fielderAssignedLocationIndex[6] &&
        (g_FieldingLogic.somethingForTryingTagOutTargetBase == currentBase ||
         g_FieldingLogic.somethingForTryingTagOutTargetBase == 9)) {
        return -1;
    }
    if (currentBase == g_FieldingLogic.fielderAssignedLocationIndex[6] &&
        (g_FieldingLogic.somethingForTryingTagOutTargetBase == nextBase ||
         g_FieldingLogic.somethingForTryingTagOutTargetBase == 9)) {
        return 1;
    }

    framesToNext = fRunningTimeToDestinationPlus7(g_Ball.fielderWBallIndex, base_MoundCoordinates[nextBase].x,
                                                  base_MoundCoordinates[nextBase].z);
    framesToCurrent = fRunningTimeToDestinationPlus7(g_Ball.fielderWBallIndex, base_MoundCoordinates[currentBase].x,
                                                     base_MoundCoordinates[currentBase].z);

    target = g_FieldingLogic.somethingForTryingTagOutTargetBase;
    framesToNextBase = runner->framesToNextBase;
    framesToPreviousBase = runner->framesToPreviousBase;
    if (target == 9) {
        if (runner->runningDirectionCode == 1 || runner->runningDirectionCode == 2) {
            if (framesToNextBase < framesToNext) {
                return 1;
            }
            return -1;
        }
        result = 1;
        if (framesToPreviousBase < framesToCurrent) {
            result = -1;
        }
        return result;
    }

    if (runner->distanceFromBall > 20.0f) {
        return -2;
    }
    direction = runner->runningDirectionCode;
    base = runner->currentBase;
    if (direction == 1 || direction == 2) {
        base = runner->nextBase;
    }
    if (base != target) {
        return -2;
    }
    if (direction == 1) {
        result = -1;
        if (framesToNextBase <= framesToNext) {
            result = 1;
        }
        return result;
    }
    result = 1;
    if (framesToPreviousBase <= framesToCurrent) {
        result = -1;
    }
    return result;
}

// .text:0x00085840 size:0x230 mapped:0x806C48D4
int runnerAISubfunction2(int runnerIdx, int arg1, int* arg2) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];
    u8 nextBase = runner->nextBase;
    u8 ballState;
    s16 contact;
    u8 hitClass;
    InMemRunnerType* other;
    int* extra;
    int i;

    if ((int)nextBase == 0) {
        return 0;
    }

    ballState = g_Ball.ballState;
    contact = g_Ball.AtBat_ContactResult;
    hitClass = g_Ball.hitClassification2;
    other = &g_Runners[runnerIdx + 1];
    extra = &arg2[runnerIdx + 1];

    for (i = runnerIdx + 1; i < 4; i++, other++, extra++) {
        if (other->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
            if (other->currentBase == runner->currentBase) {
                if (other->baseRoundingState == 2 && other->overrunBaseStage == 3) {
                    return 1;
                }
                if (other->runningDirectionCode == 3) {
                    return 1;
                }
                if (other->runningDirectionCode == 2 &&
                    other->fractionalBasesRan - runner->fractionalBasesRan < 0.7f) {
                    return 2;
                }
                if (ballState != BALL_STATE_HIT) {
                    return 1;
                }
                if (runnerIdx == 0 && contact == BALL_RESULT_TYPE_IN_AIR &&
                    runner->fractionalBasesRan > 1.0f && arg1 <= 3 &&
                    other->fractionalBasesRan < runner->fractionalBasesRan) {
                    return 2;
                }
            }
            if (other->currentBase == nextBase) {
                if (contact == BALL_RESULT_TYPE_IN_AIR) {
                    if (hitClass <= 4 && other->percentTowardsNextBase < 0.5f) {
                        if (runner->forceOutCd == FORCE_OUT_TYPE_FORCED_TO_ADVANCE && arg1 > 3) {
                            return 0;
                        }
                        if (other->runningDirectionCode == 3 || other->runningDirectionCode == 2) {
                            return 1;
                        }
                    }
                } else if (other->percentTowardsNextBase < 0.5f && *extra <= 0) {
                    if (other->runningDirectionCode == 2 || other->runningDirectionCode == 3 ||
                        (other->runningDirectionCode == 1 && other->nextDirectionBeingProcessed == 3)) {
                        return 1;
                    }
                    if (other->baseRoundingState == 2 && other->overrunBaseStage >= 2) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

// .text:0x00085744 size:0xFC mapped:0x806C47D8
void fn_3_85744(int runnerIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];

    if (runner->fractionalBasesRan > 0.2) {
        return;
    }
    if (runner->distanceFromBall < 20.0f && g_Ball.ballState == BALL_STATE_LOOSE) {
        runner->relatedToRunnerPos = 0;
    }

    if (g_FieldingLogic.locationThrownTo == 5 || g_FieldingLogic.locationThrownTo == 6 ||
        g_FieldingLogic.locationThrownTo == runner->currentBase) {
        if (runner->percentTowardsNextBase >= 0.125f && runner->runningDirectionCode == 1 &&
            g_Ball.ballZoneAwayFromHome <= 3) {
            runner->relatedToRunnerPos = 0;
        }
    }

    if (runner->baseStandingOn < 0) {
        return;
    }
    if (runner->baseRoundingState != 2) {
        return;
    }
    runner->relatedToRunnerPos = 1;
    if (0.0f == runner->groundVelocity[0]) {
        runner->relatedToRunnerPos = 0;
    }
}

// .text:0x00085074 size:0x6D0 mapped:0x806C4108
int runnerAISubfunction3(int runnerIdx, int arg1) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];
    int nextBase = runner->nextBase;
    int currentBase = runner->currentBase;
    int frames;
    int result;

    if (g_Ball.pauseBallMovementWhenInPlant == 0 && g_Ball.hitClassification1 == 0) {
        result = -1;
        if (runner->forceOutCd == FORCE_OUT_TYPE_FORCED_TO_ADVANCE) {
            result = 1;
        }
        return result;
    }

    if (g_Strikes.outs == 2) {
        return 1;
    }

    if (g_Ball.landingSpotZoneAwayFromHome <= 1) {
        if (g_Ball.maxYOfHit >= 5.0f) {
            return -1;
        }
        if (g_Ball.maxYOfHit < 2.0f && runner->forceOutCd == FORCE_OUT_TYPE_FORCED_TO_ADVANCE) {
            return 1;
        }
        if (arg1 <= 2) {
            return -1;
        }
        if (runner->forceOutCd == FORCE_OUT_TYPE_FORCED_TO_ADVANCE) {
            return 1;
        }
        frames = estimatedThrowFramesBetweenTwoPoints(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x,
                                                      g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z,
                                                      base_MoundCoordinates[nextBase].x, base_MoundCoordinates[nextBase].z);
        {
            int landedResult = -1;
            frames = g_Ball.framesUntilBallHitsGround + frames;

            if (frames + 30 > runner->framesToNextBase) {
                landedResult = 1;
            }
            return landedResult;
        }
    }

    if (arg1 >= 6) {
        return 1;
    }
    if (arg1 >= 5 && g_Ball.someCollisionVariable >= 2 && g_Ball.landingSpotZoneAwayFromHome < 3) {
        return 1;
    }

    if (runnerIdx == 3) {
        if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > 63.0f) {
            return -1;
        }
        if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > 55.0f && arg1 <= 5) {
            return -1;
        }
    }

    if (runnerIdx == 2 && arg1 <= 1) {
        f32 dx = base_MoundCoordinates[3].x - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
        f32 dz = base_MoundCoordinates[3].z - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
        f32 sqx;
        f32 sqz;
        f32 dist;

        sqx = dx * dx;
        sqz = dz * dz;
        dist = dolsqrtf2(sqx + sqz);
        if (dist > 70.0f && g_Ball.ballAngleFromHome < 0x48C) {
            return -1;
        }
    }

    if (g_Ball.framesUntilBallHitsGround < 60 && runnerIdx != 0) {
        if (arg1 <= 2 || (arg1 == 3 && g_Ball.landingSpotZoneAwayFromHome <= 2)) {
            frames = estimatedThrowFramesBetweenTwoPoints(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x,
                                                          g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z,
                                                          base_MoundCoordinates[currentBase].x,
                                                          base_MoundCoordinates[currentBase].z);
            frames = g_Ball.framesUntilBallHitsGround + frames;
            if (runner->framesToPreviousBase > frames) {
                return -1;
            }
        }
        if (arg1 >= 4) {
            if (runnerIdx == 3 && arg1 == 4 && g_Ball.landingSpotZoneAwayFromHome >= 4) {
                return -1;
            }
            if (arg1 >= 5) {
                if (runner->forceOutCd != FORCE_OUT_TYPE_NOT_FORCED_TO_ADVANCE) {
                    return 1;
                }
                if (g_Ball.maxYOfHit < 2.5f && g_Ball.ballVelocity > 0.5f) {
                    if (g_Fielders[3].groundDistanceFromBall < g_Fielders[5].groundDistanceFromBall) {
                        if (g_Ball.ballDistanceFromHome - 2.0f > g_Fielders[3].distanceFromHomePlate &&
                            g_Fielders[3].groundDistanceFromBall > 3.0f) {
                            return 1;
                        }
                        if (g_Fielders[3].groundDistanceFromBall > 4.0f &&
                            g_Ball.ballDistanceFromHome + g_Fielders[3].groundDistanceFromBall > g_Fielders[3].distanceFromHomePlate) {
                            return 1;
                        }
                    } else {
                        if (g_Ball.ballDistanceFromHome - 2.0f > g_Fielders[5].distanceFromHomePlate) {
                            return 1;
                        }
                        if (g_Fielders[5].groundDistanceFromBall > 4.0f &&
                            g_Ball.ballDistanceFromHome + g_Fielders[5].groundDistanceFromBall > g_Fielders[5].distanceFromHomePlate) {
                            return 1;
                        }
                    }
                }
                frames = estimatedThrowFramesBetweenTwoPoints(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x,
                                                              g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z,
                                                              base_MoundCoordinates[nextBase].x,
                                                              base_MoundCoordinates[nextBase].z);
                frames = g_Ball.framesUntilBallHitsGround + frames;
                if (frames + 30 > runner->framesToNextBase) {
                    return 1;
                }
            }
        }
    }

    if (runnerIdx != 0) {
        frames = estimatedThrowFramesBetweenTwoPoints(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x,
                                                      g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z,
                                                      base_MoundCoordinates[currentBase].x, base_MoundCoordinates[currentBase].z);
        if (g_Ball.framesUntilBallHitsGround < 45) {
            result = runner->framesToPreviousBase + 30;
        } else {
            result = runner->framesToPreviousBase + 15;
        }
        if (result > frames) {
            return 0;
        }
        if (runner->runningDirectionCode == 2 && result + 5 > frames) {
            return 0;
        }
        if (0.8f + (f32)runner->startingBase_baseAchieved <= runner->fractionalBasesRan) {
            if (arg1 >= 5 && g_Ball.ballDistanceFromHome > 3.0f + g_Fielders[6].distanceFromHomePlate &&
                g_Ball.ballDistanceFromHome > 3.0f + g_Fielders[7].distanceFromHomePlate &&
                g_Ball.ballDistanceFromHome > 3.0f + g_Fielders[8].distanceFromHomePlate) {
                return 1;
            }
            return 0;
        }
        return 1;
    } else {
        frames = estimatedThrowFramesBetweenTwoPoints(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x,
                                                      g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z,
                                                      base_MoundCoordinates[nextBase].x, base_MoundCoordinates[nextBase].z);
        frames = g_Ball.framesUntilBallHitsGround + frames;
        frames += 30;
        if (runner->overRun1BStage != 0) {
            return -2;
        }
        result = -2;
        if (frames > runner->framesToNextBase) {
            result = 1;
        }
        return result;
    }
}

// .text:0x00084AD0 size:0x5A4 mapped:0x806C3B64
int runnerAISubfunction4(int runnerIdx, int someFrames) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];
    int frames;
    int bestFielder;
    f32 bestDist;
    int i;

    if (runner->forceOutCd == FORCE_OUT_TYPE_FORCED_TO_ADVANCE) {
        return 1;
    }
    if (runnerIdx == 3 && g_RunningLogic._02 == 0x1011) {
        runner->unused_someBaseNum = 0;
        return 1;
    }
    if ((g_FieldingLogic.liveBallBcOfPickoffOrStealCd == 3 || g_FieldingLogic.liveBallBcOfPickoffOrStealCd == 4) &&
        runner->currentBase == runner->startingBase_baseAchieved) {
        runner->unused_someBaseNum = runner->nextBase;
        return 1;
    }

    frames = estimatedThrowFramesBetweenTwoPoints(g_Ball.physicsSubstruct.futureCoordsAndDist[someFrames].pos.x,
                                                  g_Ball.physicsSubstruct.futureCoordsAndDist[someFrames].pos.z,
                                                  base_MoundCoordinates[runner->nextBase].x,
                                                  base_MoundCoordinates[runner->nextBase].z);
    frames += someFrames + 20;
    if ((int)g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.awayTeamBattingInd_battingTeam] >= 3) {
        frames -= 30;
    } else {
        frames += neg20ForRunningAI[g_GameLogic.runnerAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam]];
    }

    if (runnerIdx == 2 && g_Ball.framesSinceHit < 100 && g_Runners[3].runnerOnFieldOrOutOrScored == RUNNER_STATUS_NONE) {
        if (g_Ball.Hit_HorizontalAngle > 0x2A8 && g_Ball.Hit_HorizontalAngle < 0x30C) {
            if (frames + 45 > runner->framesToNextBase) {
                runner->unused_someBaseNum = 3;
                return 1;
            }
            if (g_Ball.framesSinceHit < 60 && g_Ball.ballZoneAwayFromHome <= 1) {
                return 0;
            }
        }
        if (g_Ball.Hit_HorizontalAngle > 0x3A0 && g_Ball.Hit_HorizontalAngle < 0x460 && g_Ball.framesSinceHit < 60 && g_Ball.ballZoneAwayFromHome <= 1) {
            return 0;
        }
        if (g_Ball.maybeBuntInd != 0 && g_Ball.framesSinceHit < 60) {
            runner->unused_someBaseNum = 3;
            return 1;
        }
    }

    if (g_Ball.ballZoneAwayFromHome >= 3) {
        if (runner->fractionalBasesRan >= 3.25f && runner->runningDirectionCode == 1) {
            runner->unused_someBaseNum = 0;
            return 1;
        }
        if (runner->currentBase == runner->startingBase_baseAchieved && frames > runner->framesToNextBase - 30) {
            return 1;
        }
        if (frames > runner->framesToNextBase) {
            return 1;
        }
        return -2;
    }

    bestDist = 999.9f;
    bestFielder = -1;
    if (g_Ball.someCollisionInd != 0) {
        for (i = 2; i < 6; i++) {
            if (!(g_Ball.ballDistanceFromHome > 3.0f + g_Fielders[i].distanceFromHomePlate) &&
                g_Fielders[i].groundDistanceFromBall < bestDist) {
                bestDist = g_Fielders[i].groundDistanceFromBall;
                bestFielder = i;
            }
        }
        if (bestDist < 3.0f && g_Fielders[bestFielder].distanceFromHomePlate > g_Ball.ballDistanceFromHome &&
            (runner->runningDirectionCode == 3 || runner->runningDirectionCode == 2)) {
            f32 fielderX = g_Fielders[bestFielder].pos.x;
            int base = runner->currentBase;
            int throwFrames = estimatedThrowFramesBetweenTwoPoints(fielderX, fielderX, base_MoundCoordinates[base].x, base_MoundCoordinates[base].z);

            if (throwFrames < runner->framesToPreviousBase - 20) {
                return -1;
            }
        }
    }

    if (g_Ball.ballZoneAwayFromHome <= 1 && g_Ball.ballVelocity > 0.5f && g_Ball.ballDistanceFromHome > 30.0f) {
        if (bestFielder >= 0) {
            if (g_Fielders[bestFielder].distanceFromHomePlate - g_Ball.ballDistanceFromHome < bestDist) {
                return 1;
            }
        } else {
            return 1;
        }
    }

    if (g_Ball.ballZoneAwayFromHome >= 2 || bestFielder == -1) {
        if (runner->fractionalBasesRan >= 3.325f && runner->runningDirectionCode == 1) {
            runner->unused_someBaseNum = 0;
            return 1;
        }
        if (runner->currentBase == runner->startingBase_baseAchieved && frames > runner->framesToNextBase - 30) {
            return 1;
        }
        if (g_Ball.someCollisionInd != 0) {
            if (frames > runner->framesToNextBase + 30) {
                return 1;
            }
            if (runner->percentTowardsNextBase > 0.5f) {
                return 1;
            }
            return -1;
        }
        if (g_Ball.ballState == BALL_STATE_LOOSE) {
            if (frames > runner->framesToNextBase + 20) {
                return 1;
            }
            if (runner->percentTowardsNextBase > 0.5f) {
                return 1;
            }
            return -1;
        }
    }
    return 0;
}

// .text:0x000846C8 size:0x408 mapped:0x806C375C
int runnerAI_2(int runnerIdx) {
    u8 ballZone = g_Ball.ballZoneAwayFromHome;
    InMemRunnerType* runner = &g_Runners[runnerIdx];
    int nextBase = runner->nextBase;
    int currBase = runner->currentBase;
    u8 direction;
    int result;
    int nextFrames;
    int prevFrames;
    int throwWindup;
    int framesToNext;
    int framesToPrev;

    if (ballZone <= 2 && runner->baseStandingOn >= 0) {
        return 0;
    }
    if (ballZone >= 3 && runner->percentTowardsNextBase >= 3.2f && runner->runningDirectionCode == 1 &&
        runner->baseRoundingState == 2) {
        runner->unused_someBaseNum = 0;
        return 1;
    }
    direction = runner->runningDirectionCode;
    if (direction == 1 && runner->percentTowardsNextBase > 0.8f && runner->baseStandingOn < 0) {
        return -2;
    }
    if (direction == 3 && runner->percentTowardsNextBase < 0.2f && ballZone <= 2) {
        return -2;
    }
    if (g_FieldingLogic.fielderAssignedLocationIndex[nextBase] == g_Ball.fielderWBallIndex) {
        return -1;
    }
    if (g_FieldingLogic.fielderAssignedLocationIndex[currBase] == g_Ball.fielderWBallIndex) {
        return 1;
    }
    if (g_FieldingLogic.somethingForTryingTagOutTargetBase != -1 && ballZone <= 2) {
        result = fn_3_85A70(runnerIdx);
        if (result != -2) {
            return result;
        }
    }
    nextFrames = fn_3_A6ABC(base_MoundCoordinates[nextBase].x, base_MoundCoordinates[nextBase].z);
    prevFrames = fn_3_A6ABC(base_MoundCoordinates[currBase].x, base_MoundCoordinates[currBase].z);
    if ((int)g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.awayTeamBattingInd_battingTeam] >= 3) {
        nextFrames -= 30;
    } else {
        nextFrames += neg20ForRunningAI[g_GameLogic.runnerAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam]];
    }
    if (g_FieldingLogic.locationThrownTo >= 0) {
        throwWindup = 30 - g_FieldingLogic.throwWindupFrames;
        if (throwWindup > 0) {
            nextFrames += throwWindup;
            prevFrames += throwWindup;
        }
    } else {
        nextFrames += 30;
        prevFrames += 30;
    }
    if (runner->runningDirectionCode == 1 && runner->percentTowardsNextBase > 0.5f) {
        nextFrames += 40;
        if (runner->currentBase == 3) {
            nextFrames += 20;
        }
    } else if (runner->runningDirectionCode == 1 && (runner->baseRoundingState != 1 || runner->overrunBaseStage != 2) &&
               runner->percentTowardsNextBase >= 0.15f) {
        nextFrames += 20;
    }
    framesToNext = runner->framesToNextBase;
    if (nextFrames > framesToNext) {
        if (runnerIdx == 3 && g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT &&
            g_Ball.timeSinceBallPickedUp <= 1 && g_Ball.numberOfThrowsDuringPlay == 1) {
            runner->unused_someBaseNum = 0;
        }
        return 1;
    }
    ballZone = g_Ball.ballZoneAwayFromHome;
    if (ballZone >= 3 && runnerIdx >= 1 && runner->currentBase == runner->startingBase_baseAchieved &&
        g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_CAUGHT && nextFrames > framesToNext - 20) {
        return 1;
    }
    if (runner->currentBase == 3 && ballZone >= 3 && g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_CAUGHT) {
        if (nextFrames > framesToNext - 20) {
            return 1;
        }
        if (nextFrames > framesToNext - 30 && g_Strikes.outs >= 2) {
            return 1;
        }
    }
    framesToPrev = runner->framesToPreviousBase;
    if (prevFrames > framesToPrev) {
        if (runner->baseRoundingState == 2 && runner->overrunBaseStage == 2 && prevFrames - 20 > framesToPrev) {
            return -2;
        }
        return -1;
    }
    if (nextFrames - framesToNext > prevFrames - framesToPrev) {
        return 1;
    }
    return -1;
}

// .text:0x000842E4 size:0x3E4 mapped:0x806C3378
int runnerAILiveBall(int runnerIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];
    int nextBase;
    int currBase;
    int throwFrames;
    int thrownTo;
    u8 direction;
    int cutoffFrames;
    int threshold;

    if (g_Ball.throwTimeEstimatesCompleteInd == 0) {
        return -2;
    }
    nextBase = runner->nextBase;
    currBase = runner->currentBase;
    throwFrames = g_Ball.framesUntilThrowReachesDest;
    if ((int)g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.awayTeamBattingInd_battingTeam] >= 3) {
        throwFrames -= 30;
    } else {
        throwFrames += neg20ForRunningAI[g_GameLogic.runnerAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam]];
    }
    direction = runner->runningDirectionCode;
    if (direction == 1 && runner->percentTowardsNextBase > 0.8f) {
        runner->baseRunningTowards = nextBase;
        return -2;
    }
    if (direction == 3 && runner->percentTowardsNextBase < 0.2f && g_Ball.ballZoneAwayFromHome <= 3) {
        runner->baseRunningTowards = currBase;
        return -2;
    }
    thrownTo = g_FieldingLogic.locationThrownTo;
    if (runner->baseStandingOn == thrownTo) {
        return -(currBase == thrownTo);
    }
    if (direction == 1 && thrownTo == nextBase) {
        if (runner->percentTowardsNextBase >= 0.4f) {
            throwFrames += 30;
            if (runner->currentBase == 3) {
                throwFrames += 20;
            }
        }
        if (runner->framesToNextBase < throwFrames) {
            return 1;
        }
        if (g_FieldingLogic.setThrowSpeedTypeTo9Ind != 0) {
            if (g_Ball.StaticRandomInt1 % ((int)g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.teamBatting] + 5) != 0) {
                return 1;
            }
        }
        return -1;
    }
    if (direction == 3 && thrownTo == currBase) {
        if (runner->percentTowardsNextBase <= 0.4f) {
            throwFrames += 15;
        }
        if (runner->framesToPreviousBase < throwFrames) {
            return -1;
        }
        if (g_FieldingLogic.setThrowSpeedTypeTo9Ind != 0) {
            if (g_Ball.StaticRandomInt1 % ((int)g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.teamBatting] + 5) != 0) {
                return -1;
            }
        }
        return 1;
    }
    if (thrownTo == 6) {
        cutoffFrames = estimatedThrowFramesBetweenTwoPoints(
            g_Fielders[g_FieldingLogic.cutoffFielderIndex].IntendedLocation.x,
            g_Fielders[g_FieldingLogic.cutoffFielderIndex].IntendedLocation.z, base_MoundCoordinates[nextBase].x,
            base_MoundCoordinates[nextBase].z);
        threshold = throwFrames + cutoffFrames;
        threshold += 30;
        if (nextBase == 0) {
            threshold += 15;
            if (g_Strikes.outs >= 2) {
                threshold += 10;
            }
        }
        if (runner->percentTowardsNextBase >= 0.5f) {
            threshold += 15;
        } else if (runner->percentTowardsNextBase >= 0.15f) {
            threshold += 5;
        }
        if (runner->framesToNextBase < threshold) {
            if (runner->fractionalBasesRan >= 3.15f && g_Ball.ballZoneAwayFromHome >= 3) {
                runner->unused_someBaseNum = 0;
            }
            return 1;
        }
        if (runner->baseRoundingState == 2 && runner->overrunBaseStage == 2) {
            cutoffFrames = estimatedThrowFramesBetweenTwoPoints(
                g_Fielders[g_FieldingLogic.cutoffFielderIndex].IntendedLocation.x,
                g_Fielders[g_FieldingLogic.cutoffFielderIndex].IntendedLocation.z, base_MoundCoordinates[currBase].x,
                base_MoundCoordinates[currBase].z);
            threshold = throwFrames + cutoffFrames;
            threshold += 20;
            return -2 + (runner->framesToPreviousBase < threshold);
        }
        return -1;
    }
    return -2;
}

// .text:0x000841C0 size:0x124 mapped:0x806C3254
int possibleRunnerAIRelated(int runnerIdx, int frame) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];
    int frames;

    if (runner->forceOutCd == FORCE_OUT_TYPE_FORCED_TO_ADVANCE) {
        return 1;
    }
    frames = estimatedThrowFramesBetweenTwoPoints(g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.x,
                                                  g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.z,
                                                  base_MoundCoordinates[runner->nextBase].x,
                                                  base_MoundCoordinates[runner->nextBase].z);
    frames += frame + 0x2D;
    if ((int)g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.awayTeamBattingInd_battingTeam] >= 3) {
        frames -= 0x1E;
    } else {
        frames += neg20ForRunningAI[g_GameLogic.runnerAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam]];
    }
    if (g_Ball.ballZoneAwayFromHome <= 1) {
        if (frames - 0x14 > runner->framesToNextBase) {
            return 1;
        }
    } else if (frames > runner->framesToNextBase) {
        return 1;
    }
    return -1;
}

// .text:0x00083714 size:0xAAC mapped:0x806C27A8
void running_LiveBall_AI(void) {
    int dirs[4];
    int arg = 3;
    int closest = 0;
    s16 contact;
    InMemRunnerType* runner;
    int i;

    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE &&
        (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL ||
         g_GameLogic.FrameCountOfCurrentPitch >= g_RunningLogic.someSituationTrackerFrames) &&
        g_FieldingLogic.playOverInd == 0) {
        if (g_Ball.framesSinceHit >= 0 && g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR) {
            arg = runnerAISubfunction();
        } else if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_LANDED || g_Ball.ballState == BALL_STATE_LOOSE) {
            int fielder;
            closest = fn_3_8604C(&fielder);
        }

        contact = g_Ball.AtBat_ContactResult;
        if (g_Ball.framesSinceHit < 0) {
            contact = -2;
        }
        if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR && g_Ball.hitClassification1 == 0) {
            contact = BALL_RESULT_TYPE_LANDED;
        }

        for (i = 3; i >= 0; i--) {
            runner = &g_Runners[i];
            dirs[i] = -2;
            if (runner->runnerOnFieldOrOutOrScored != RUNNER_STATUS_ON_FIELD || runner->unused_const_1 == 0 ||
                g_Strikes.outs >= 3 || g_FieldingLogic.playOverInd != 0) {
                continue;
            }
            if (i == 0 && g_Ball.framesSinceHit < runner->delayBeforeStartingToRun) {
                dirs[i] = 0;
            } else if (i == 0 && g_Ball.framesSinceHit == runner->delayBeforeStartingToRun) {
                dirs[i] = 1;
            } else if (g_Ball.deadBallReason == 1) {
                dirs[i] = 1;
            } else if (i == 0 && g_Ball.framesSinceHit == -1) {
                dirs[i] = 0;
            } else if (i != 0 || runner->currentBase != 0) {
                if ((g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR || g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_LANDED) &&
                    g_FieldingLogic.infieldFlyIndicator != 0) {
                    dirs[i] = -1;
                } else if (g_Ball.howFoulTheBallWillBe < 2 ||
                           (g_Ball.numFieldersWhoHandledBallDuringPlay != 0 && g_Ball.bobbleLocation_1fair_2foul == 1)) {
                    if (g_Strikes.storedOuts == 2 && g_FieldingLogic.liveBallBcOfPickoffOrStealCd == 0 &&
                        runner->currentBase == runner->startingBase_baseAchieved) {
                        dirs[i] = 1;
                    } else {
                        if (contact == BALL_RESULT_TYPE_CAUGHT) {
                            if (runner->tagUpInd == TAG_UP_TYPE_TAGGED) {
                                runner->relatedToRunnerPos = 0;
                                dirs[i] = -1;
                                runner->unused_someBaseNum = -1;
                                continue;
                            } else {
                                InMemRunnerType* other = &g_Runners[3];
                                int j;

                                for (j = i; j < 3; j++, other--) {
                                    if (other->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD && other->tagUpInd == TAG_UP_TYPE_TAGGED) {
                                        dirs[i] = -1;
                                        runner->unused_someBaseNum = -1;
                                    }
                                }
                            }
                        }
                        if (contact == BALL_RESULT_TYPE_CAUGHT && runner->tagUpInd == TAG_UP_TYPE_TAGGED) {
                            dirs[i] = -1;
                        } else if (runner->forceOutCd == FORCE_OUT_TYPE_FORCED_TO_ADVANCE && contact >= 1 && contact <= 2) {
                            dirs[i] = 1;
                        } else {
                            BOOL found;
                            int j;
                            int res;
                            InMemRunnerType* other;

                            if (runner->unused_someBaseNum >= 0) {
                                if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT && runner->tagUpInd != TAG_UP_TYPE_NONE) {
                                    runner->unused_someBaseNum = -1;
                                } else if (runner->unused_someBaseNum == runner->currentBase) {
                                    runner->unused_someBaseNum = -1;
                                } else if (runner->actionCode != 0) {
                                    runner->unused_someBaseNum = -1;
                                } else {
                                    dirs[i] = 1;
                                    continue;
                                }
                            }
                            found = FALSE;
                            for (j = 0; j < i; j++) {
                                other = &g_Runners[j];
                                if (other->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
                                    runner->currentBase == other->currentBase &&
                                    (j != 0 || (g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_IN_AIR && g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_CAUGHT))) {
                                    found = TRUE;
                                    break;
                                }
                            }
                            if (found) {
                                dirs[i] = 1;
                            } else {
                                fn_3_85744(i);
                                res = runnerAISubfunction2(i, arg, dirs);
                                if (res == 1) {
                                    if (g_Ball.framesSinceHit < 60 || g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR) {
                                        dirs[i] = 0;
                                    } else {
                                        dirs[i] = -1;
                                    }
                                } else if (res == 2) {
                                    dirs[i] = 0;
                                } else if (g_Ball.framesSinceHit != -1 && g_Ball.framesSinceHit >= 10) {
                                    if (contact == BALL_RESULT_TYPE_IN_AIR) {
                                        if (g_Ball.pauseBallMovementWhenInPlant != 0) {
                                            dirs[i] = runnerAISubfunction3(i, 5);
                                        } else if (g_Ball.maxYOfHit <= 1.2f) {
                                            dirs[i] = runnerAISubfunction4(i, closest);
                                        } else {
                                            dirs[i] = runnerAISubfunction3(i, arg);
                                        }
                                    } else if (g_Ball.ballStoppingCode1ReallySlow2Stopped != 0 &&
                                               (g_Ball.ballState == BALL_STATE_LOOSE ||
                                                (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_LANDED && g_Ball.framesSinceHit > 400))) {
                                        dirs[i] = possibleRunnerAIRelated(i, closest);
                                    } else if (g_Ball.numberOfThrowsDuringPlay >= 1 && g_Ball.ballState == BALL_STATE_LOOSE &&
                                               (g_Ball.ballVelocity < 0.1f ||
                                                g_FieldingLogic.ballWontBeControlledByFielderAnytimeSoonInd != 0)) {
                                        dirs[i] = possibleRunnerAIRelated(i, closest);
                                    } else if (contact == BALL_RESULT_TYPE_LANDED || g_Ball.ballState == BALL_STATE_LOOSE) {
                                        dirs[i] = runnerAISubfunction4(i, closest);
                                    } else if (g_Ball.ballState == BALL_STATE_HELD) {
                                        dirs[i] = runnerAI_2(i);
                                    } else {
                                        dirs[i] = runnerAILiveBall(i);
                                    }
                                }
                            }
                        }
                    }
                } else {
                    dirs[i] = -1;
                }
            }
        }

        runner = &g_Runners[3];
        for (i = 3; i >= 0; i--, runner--) {
            int d = dirs[i];

            if (d != -2 && (runner->baseRoundingState != 1 || runner->overRun1BStage < 2 || d == 1)) {
                if (d == -1 && runner->startingBase_baseAchieved == runner->baseStandingOn) {
                    d = 0;
                }
                runnerAISetRunningDirection(i, d);
            }
        }

        if (g_GameLogic.battingAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam] != 0) {
            if (g_GameLogic.teamIsCPU[g_GameLogic.homeTeamBattingInd_fieldingTeam] == 0) {
                InputStruct* input = &g_Controls[g_GameLogic.teams[g_GameLogic.teamBatting]];
                if (input->newButtonInput & (INPUT_BUTTON_A | INPUT_BUTTON_B | INPUT_BUTTON_X | INPUT_BUTTON_Y)) {
                    g_Runners[0].newButtonThisFrame_forMashPurposes = 1;
                    g_Runners[1].newButtonThisFrame_forMashPurposes = 1;
                    g_Runners[2].newButtonThisFrame_forMashPurposes = 1;
                    g_Runners[3].newButtonThisFrame_forMashPurposes = 1;
                }
            } else if (g_AiLogic._44 > 0) {
                u32 difficulty = g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamBattingInd_fieldingTeam];
                if (g_Ball.framesSinceHit >= lbl_3_data_1C58[difficulty][0]) {
                    if (g_AiLogic._77 != 0) {
                        g_AiLogic._77--;
                    } else {
                        if (RandomInt_Game(100) < lbl_3_data_1C58[g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamBattingInd_fieldingTeam]][3]) {
                            g_Runners[0].newButtonThisFrame_forMashPurposes = 1;
                            g_Runners[1].newButtonThisFrame_forMashPurposes = 1;
                            g_Runners[2].newButtonThisFrame_forMashPurposes = 1;
                            g_Runners[3].newButtonThisFrame_forMashPurposes = 1;
                            g_AiLogic._44--;
                        }
                        g_AiLogic._77 = lbl_3_data_1C58[g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamBattingInd_fieldingTeam]][2];
                    }
                }
            }
        }
    }
}

// .text:0x000835B0 size:0x164 mapped:0x806C2644
void fn_3_835B0(void) {
    if (g_GameLogic.teamIsCPU[g_GameLogic.homeTeamBattingInd_fieldingTeam] == 0) {
        InputStruct* input = &g_Controls[g_GameLogic.teams[g_GameLogic.teamBatting]];
        if (input->newButtonInput & (INPUT_BUTTON_A | INPUT_BUTTON_B | INPUT_BUTTON_X | INPUT_BUTTON_Y)) {
            g_Runners[0].newButtonThisFrame_forMashPurposes = 1;
            g_Runners[1].newButtonThisFrame_forMashPurposes = 1;
            g_Runners[2].newButtonThisFrame_forMashPurposes = 1;
            g_Runners[3].newButtonThisFrame_forMashPurposes = 1;
        }
    } else if (g_AiLogic._44 > 0) {
        u32 difficulty = g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamBattingInd_fieldingTeam];
        if (g_Ball.framesSinceHit >= lbl_3_data_1C58[difficulty][0]) {
            if (g_AiLogic._77 != 0) {
                g_AiLogic._77--;
            } else {
                if (RandomInt_Game(100) < lbl_3_data_1C58[g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamBattingInd_fieldingTeam]][3]) {
                    g_Runners[0].newButtonThisFrame_forMashPurposes = 1;
                    g_Runners[1].newButtonThisFrame_forMashPurposes = 1;
                    g_Runners[2].newButtonThisFrame_forMashPurposes = 1;
                    g_Runners[3].newButtonThisFrame_forMashPurposes = 1;
                    g_AiLogic._44--;
                }
                g_AiLogic._77 = lbl_3_data_1C58[g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamBattingInd_fieldingTeam]][2];
            }
        }
    }
}

// .text:0x000833EC size:0x1C4 mapped:0x806C2480
void fn_3_833EC(int runnerIdx) {
    InMemRunnerType* runner;

    running_updateDistAndFramesToClosestBases(runnerIdx);
    runner = &g_Runners[runnerIdx];
    if (runner->runningToDugoutInd == 0 || runner->runningToDugoutStage == 0) {
        if (runner->actionCode == 0) {
            if ((runner->framesSinceLastDirectionChange >= lbl_3_data_4C54[3] ||
                 (runner->runningDirectionCode != RUNNER_MOVEMENT_FORWARDS && runner->runningDirectionCode != 3)) &&
                runner->runningDirectionDesired != 0) {
                if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
                    if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                        runner->nextDirectionBeingProcessed = runner->runningDirectionDesired;
                    }
                } else {
                    if ((runnerIdx != 0 || runner->nextBase != 1) && runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                        runner->nextDirectionBeingProcessed = runner->runningDirectionDesired;
                    }
                    if (runner->nextDirectionBeingProcessed == 3 && runner->tagUpInd != 3 &&
                        runner->baseStandingOn >= 0) {
                        runner->nextDirectionBeingProcessed = 0;
                    }
                }
            }
            {
                int dir = running_DirectionOverrides(runnerIdx);
                if (dir != 0) {
                    runner->nextDirectionBeingProcessed = dir;
                }
            }
        }
    }
    if (runner->runningToDugoutInd != 0) {
        runner->baseRoundingState = 0;
        runner->actionCode = 0;
    } else {
        running_roundBaseDecision(runnerIdx);
        running_triggerSlideOrBodyCheck(runnerIdx);
        if (g_GameLogic.secondaryGameMode != SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
            if (runnerIdx == 0 && runner->nextBase == 1) {
                running_overrun1stIndicator();
            } else if (runner->baseRoundingState == 1) {
                runner->baseRoundingState = 0;
            }
            running_sendOutRunnerToDugout(runnerIdx);
        }
    }
    running_CalculateSpeedVariables(runnerIdx);
    running_updatePositionTracking_storeRBIs_stopAtNextBase_displaySafe(runnerIdx);
    running_updatePosition(runnerIdx);
    running_updateDistAndFramesToClosestBases(runnerIdx);
}

// .text:0x0008307C size:0x370 mapped:0x806C2110
void running_updateDistAndFramesToClosestBases(int runnerIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];

    if ((runner->runningToDugoutInd != 1 || runner->runningToDugoutStage == 0) &&
        g_Pitcher.pitcherActionState != PITCHER_ACTION_STATE_POST_HIT) {
        int baseAchieved = (int)runner->fractionalBasesRan;
        int basesAchieved_1;
        int baseAhead;
        f32 distToPrev;
        f32 distToNext;
        f32 dx;
        f32 dz;

        runner->currentBaseCoordinates.y = 0.0f;
        runner->nextBaseCoordinates.y = 0.0f;
        basesAchieved_1 = baseAchieved + 1;
        baseAhead = basesAchieved_1 % 4;
        if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
            runner->currentBaseCoordinates.x = baseCoordsForRunning[baseAchieved][0];
            runner->currentBaseCoordinates.z = baseCoordsForRunning[baseAchieved][1];
        } else if (basesAchieved_1 == 1) {
            runner->currentBaseCoordinates.x = g_Batter.batterPos.x;
            runner->currentBaseCoordinates.z = g_Batter.batterPos.z;
        } else {
            runner->currentBaseCoordinates.x = baseCoordsForRunning[baseAchieved][0];
            runner->currentBaseCoordinates.z = baseCoordsForRunning[baseAchieved][1];
        }
        runner->nextBaseCoordinates.x = baseCoordsForRunning[baseAhead][0];
        runner->nextBaseCoordinates.z = baseCoordsForRunning[baseAhead][1];
        dx = runner->currentBaseCoordinates.x - runner->position.x;
        dz = runner->currentBaseCoordinates.z - runner->position.z;
        dx = dx * dx;
        dz = dz * dz;
        distToPrev = dolsqrtf2(dx + dz);
        dx = runner->nextBaseCoordinates.x - runner->position.x;
        dz = runner->nextBaseCoordinates.z - runner->position.z;
        dx = dx * dx;
        dz = dz * dz;
        distToNext = dolsqrtf2(dx + dz);
        runner->calculatedLengthOfCurrentBaseline = distToPrev + distToNext;
        runner->fractionOfCalculatedBaselineRan = distToPrev / (distToPrev + distToNext);
        runner->distToCurrentBase = distToPrev;
        runner->distToNextBase = distToNext;
        runner->currentBase = baseAchieved;
        runner->nextBase = baseAhead;
        updateRunnerFramesToClosestBases(runnerIdx, &runner->framesToPreviousBase, &runner->framesToNextBase);
    }
}

// .text:0x00082F80 size:0xFC mapped:0x806C2014
void updateRunnerFramesToClosestBases(int runnerIdx, s16* framesToPreviousBase, s16* framesToNextBase) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];
    int frames = 0;
    f32 remaining = runner->percentTowardsNextBase_slideAdj;

    if (remaining > 0.0f) {
        f32 maxVelocity = runner->velocityPercent_stamAdj;
        f32 velocity;

        if (runner->percentRanPerFrame_slideAdj < maxVelocity) {
            velocity = runner->percentRanPerFrame_slideAdj;
            do {
                velocity += runner->accelerationPercent_stamAdj;
                frames++;
                if (velocity > maxVelocity) {
                    remaining -= maxVelocity;
                    break;
                }
                remaining -= velocity;
            } while (!(remaining < 0.0f));
        }
        frames = (int)(remaining / maxVelocity) + frames;
        frames++;
    }
    *framesToNextBase = frames;

    frames = 0;
    remaining = runner->percentFromCurrentBase_slideAdj;
    if (remaining > 0.0f) {
        f32 maxVelocity = runner->velocityPercent_stamAdj;
        f32 velocity = runner->percentRanPerFrame_slideAdj;

        if (velocity > -maxVelocity) {
            do {
                velocity -= runner->accelerationPercent_stamAdj;
                frames++;
                if (velocity < -maxVelocity) {
                    remaining -= maxVelocity;
                    break;
                }
                remaining -= velocity;
            } while (!(remaining < 0.0f));
        }
        frames = (int)(remaining / maxVelocity) + frames;
        frames++;
    }
    *framesToPreviousBase = frames;
}

// .text:0x00082670 size:0x910 mapped:0x806C1704
void running_CalculateSpeedVariables(int runnerIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];
    int turnaroundCode = runner->turnaroundCode;

    if (pauseControl[0x1d5] != 0) {
        return;
    }
    runner->groundVelocity[3] = runner->groundVelocity[2];
    runner->groundVelocity[2] = runner->groundVelocity[1];
    runner->groundVelocity[1] = runner->groundVelocity[0];
    if (g_GameLogic.secondaryGameMode != SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
        if (runnerIdx == 0 && runner->delayBeforeStartingToRun > g_Ball.framesSinceHit) {
            return;
        }
        if (runner->batterStayInBattersBoxReason == 3) {
            runner->acceleration = 0.0f;
            return;
        }
    }
    if (runner->actionCode != 0) {
        running_ActionControlAndVelocity(runnerIdx);
    } else {
        f32 veloCap;
        int maxedOut;

        if (runner->overRun1BStage != 0 && runnerOverrun1BRelated(runnerIdx) != 0) {
            return;
        }
        if (runner->overrunBaseStage != 0 && running_overrunBaseControl(runnerIdx) != 0) {
            return;
        }
        if (runner->leadOffStatus == 1) {
            fn_3_81AEC(runnerIdx);
            goto finish;
        }
        if (runner->slideHomeFrames_CountDown != 0) {
            return;
        }
        if (runner->fractionalBasesRan >= 4.0f) {
            return;
        }
        runner->acceleration = 0.0f;
        runner->turnaroundCode = 0;
        if (runner->framesSinceLastDirectionChange < 0x7FFE) {
            runner->framesSinceLastDirectionChange++;
        } else {
            runner->framesSinceLastDirectionChange = 0x7FFF;
        }

        if (runner->nextDirectionBeingProcessed == 1) {
            if (runner->runningDirectionCode == 3) {
                runner->acceleration =
                    runner->baseAccelerationWhileChaingingDirection * runner->accelerationStaminaEffectWhileChangingDirection;
            } else {
                runner->acceleration = runner->baseAcceleration * runner->accelerationStaminaEffect;
            }
        } else if (runner->nextDirectionBeingProcessed == 2) {
            if (runner->runningDirectionCode == 1) {
                runner->acceleration =
                    -(runner->baseAccelerationWhileChaingingDirection * runner->accelerationStaminaEffectWhileChangingDirection);
            } else if (runner->runningDirectionCode == 3) {
                runner->acceleration =
                    runner->baseAccelerationWhileChaingingDirection * runner->accelerationStaminaEffectWhileChangingDirection;
            } else if (runner->runningDirectionCode == 2) {
                runner->groundVelocity[0] = 0.0f;
            }
        } else if (runner->nextDirectionBeingProcessed == 3) {
            if (runner->runningDirectionCode == 1) {
                runner->acceleration =
                    -(runner->baseAccelerationWhileChaingingDirection * runner->accelerationStaminaEffectWhileChangingDirection);
            } else {
                runner->acceleration = -(runner->baseAcceleration * runner->accelerationStaminaEffect);
            }
        } else {
            if (runner->runningDirectionCode == 1) {
                runner->acceleration = runner->baseAcceleration * runner->accelerationStaminaEffect;
            } else if (runner->runningDirectionCode == 3) {
                runner->acceleration = -(runner->baseAcceleration * runner->accelerationStaminaEffect);
            } else if (runner->runningDirectionCode == 2) {
                runner->groundVelocity[0] = 0.0f;
            }
        }

        if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
            f32 boost = lbl_3_data_218BC[16] * (f32)g_Minigame.miniGameCurrentPoints[runner->miniGamePlayerNum] + 1.0f;
            if (boost > lbl_3_data_218BC[17]) {
                boost = lbl_3_data_218BC[17];
            }
            if ((s8)g_Minigame.playerIDWithPowerup[0] == runnerIdx) {
                boost *= lbl_3_data_2191C[1];
            }
            veloCap = boost * (runner->maximumBaseVelocity * runner->staminaMult);
        } else if (runner->stealingStatus != 0) {
            veloCap = lbl_3_data_4B88[1] * (runner->maximumBaseVelocity * runner->staminaMult);
        } else {
            veloCap = lbl_3_data_4B88[0] * (runner->maximumBaseVelocity * runner->staminaMult);
        }

        runner->groundVelocity[0] = runner->groundVelocity[0] + runner->acceleration;
        maxedOut = 0;
        if (runner->groundVelocity[0] > veloCap) {
            runner->groundVelocity[0] = veloCap;
            maxedOut = 1;
        }
        if (runner->groundVelocity[0] < -veloCap) {
            runner->groundVelocity[0] = -veloCap;
            maxedOut = -1;
        }

        if (maxedOut != 0) {
            if (runner->newButtonThisFrame_forMashPurposes != 0) {
                runner->framesSinceLastMash = runner->FramesUntilNotSprinting;
                runner->mashPercent += runner->percentAddedPerMash;
                if (runner->mashPercent > 1.0f) {
                    runner->mashPercent = 1.0f;
                }
            } else if (runner->framesSinceLastMash != 0) {
                runner->framesSinceLastMash--;
            } else {
                runner->mashPercent -= runner->stamina_MashPercentTakenAwayPerFrame;
                if (runner->mashPercent < 0.0f) {
                    runner->mashPercent = 0.0f;
                }
            }
            runner->mashVeloAdjustment = runner->mashPercent * runner->maxMashVeloAdjustment;
            if (maxedOut == 1 && runner->acceleration > 0.0f) {
                runner->groundVelocity[0] += runner->mashVeloAdjustment;
            } else if (runner->acceleration < 0.0f) {
                runner->groundVelocity[0] -= runner->mashVeloAdjustment;
            }
        } else {
            runner->mashPercent = 0.0f;
            runner->framesSinceLastMash = 0;
        }

        if (runner->nextDirectionBeingProcessed == 1) {
            if (runner->groundVelocity[0] >= 0.0f) {
                if (runner->runningDirectionCode != 1) {
                    runner->runnerDirectionCode_stored = runner->runningDirectionCode;
                }
                runner->runningDirectionCode = 1;
                runner->nextDirectionBeingProcessed = 0;
                runner->framesSinceLastDirectionChange = 0;
                if (turnaroundCode == 2 || runner->groundVelocity[1] < 0.0f ||
                    runner->groundVelocity[2] < 0.0f || runner->groundVelocity[3] < 0.0f) {
                    runner->turningAroundInd = 1;
                    playSoundEffect(0x174);
                } else {
                    runner->turningAroundInd = 0;
                }
                runner->leadOffStatus = 0;
            } else {
                runner->turnaroundCode = 2;
            }
        } else if (runner->nextDirectionBeingProcessed == 2) {
            u8 dir = runner->runningDirectionCode;
            if ((dir == 1 && runner->groundVelocity[0] < 0.0f) ||
                (dir == 3 && runner->groundVelocity[0] > 0.0f) ||
                runner->groundVelocity[0] == 0.0f) {
                if (dir != 2) {
                    runner->runningDirectionCode = 2;
                    runner->framesSinceLastDirectionChange = 0;
                }
                runner->nextDirectionBeingProcessed = 0;
                runner->groundVelocity[0] = 0.0f;
                runner->turningAroundInd = 0;
            } else {
                runner->turnaroundCode = 1;
            }
        } else if (runner->nextDirectionBeingProcessed == 3) {
            if (runner->groundVelocity[0] <= 0.0f) {
                if (runner->runningDirectionCode != 3) {
                    runner->runnerDirectionCode_stored = runner->runningDirectionCode;
                }
                runner->runningDirectionCode = 3;
                runner->nextDirectionBeingProcessed = 0;
                runner->framesSinceLastDirectionChange = 0;
                if (turnaroundCode == 2 || runner->groundVelocity[1] > 0.0f ||
                    runner->groundVelocity[2] > 0.0f || runner->groundVelocity[3] > 0.0f) {
                    runner->turningAroundInd = 1;
                    playSoundEffect(0x174);
                } else {
                    runner->turningAroundInd = 0;
                }
            } else {
                runner->turnaroundCode = 2;
            }
        }

        if (runner->runningDirectionCode == 1) {
            runner->baseRunningTowards = runner->nextBase;
        } else if (runner->runningDirectionCode == 3) {
            if (runner->baseStandingOn < 0 || runner->startingBase_baseAchieved != runner->baseStandingOn ||
                runner->tagUpInd != TAG_UP_TYPE_TAGGED) {
                runner->baseRunningTowards = runner->currentBase;
            } else {
                runner->baseRunningTowards = (runner->currentBase + 3) & 3;
            }
        }

        {
            f32 inverseLength = 1.0f / runner->calculatedLengthOfCurrentBaseline;
            runner->percentRanPerFrame_slideAdj = runner->groundVelocity[0] * inverseLength;
            runner->velocityPercent_stamAdj = inverseLength * (runner->maximumBaseVelocity * runner->staminaMult);
            runner->accelerationPercent_stamAdj = inverseLength * (runner->baseAcceleration * runner->accelerationStaminaEffect);
        }
    }

    if (runner->percentRanPerFrame_slideAdj != 0.0f) {
        int scaled = (int)(10000.0f * (runner->fractionalBasesRan + runner->percentRanPerFrame_slideAdj));
        runner->fractionalBasesRan = (f32)scaled / 10000.0f;
        runner->percentTowardsNextBase = (f32)(scaled % 10000) / 10000.0f;
    }
finish:
    runner->percentFromCurrentBase_slideAdj = runner->percentTowardsNextBase - runner->slidingAdjustment_backwards;
    runner->percentTowardsNextBase_slideAdj =
        (1.0f - runner->percentTowardsNextBase) - runner->slidingAdjustment_forwards;
    if (runner->overRun1BStage != 0) {
        runnerOverrun1BRelated(runnerIdx);
    }
}

// .text:0x000823B4 size:0x2BC mapped:0x806C1448
void running_ActionControlAndVelocity(int runnerIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];

    runner->actionFrames_countUp++;
    runner->actionFrames_countDown--;
    if (runner->actionStage == 1) {
        if (runner->actionInForwardDirectionInd != 0) {
            f32 excess = (1.0f - runner->slidingAdjustment_forwards) - runner->percentTowardsNextBase;
            if (runner->actionFrames_countDown <= 0) {
                runner->percentRanPerFrame_slideAdj = 0.03f + excess;
            } else {
                runner->percentRanPerFrame_slideAdj = excess / (f32)(runner->actionFrames_countDown + 1);
            }
        } else {
            f32 dist = runner->percentTowardsNextBase - runner->slidingAdjustment_backwards;
            if (runner->actionFrames_countDown <= 0) {
                runner->percentRanPerFrame_slideAdj = -dist - 0.03f;
            } else {
                runner->percentRanPerFrame_slideAdj = -dist / (f32)(runner->actionFrames_countDown + 1);
            }
        }
        if (runner->actionFrames_countDown <= 0) {
            runner->actionFrames_countUp = 0;
            runner->actionFrames_countDown = runnerConstants[runner->charID][3];
            runner->actionStage = 2;
            runner->percentRanPerFrame_slideAdj = 0.0f;
            runner->fractionalBasesRan = (f32)runner->baseRunningTowards;
            runner->percentTowardsNextBase = 0.0f;
            if (runner->baseRunningTowards == 0) {
                runner->fractionalBasesRan = 4.0f;
            }
            if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_OUT_DURING_PLAY) {
                runner->actionStage = 3;
            }
        }
    } else if (runner->actionStage == 2) {
        runner->groundVelocity[0] = 0.0f;
        runner->percentRanPerFrame_slideAdj = 0.0f;
        if (runner->actionFrames_countDown <= 0) {
            runner->actionCode = 0;
            runner->actionStage = 0;
            if (runner->baseStandingOn >= 0) {
                runner->runningDirectionCode = 2;
                runner->nextDirectionBeingProcessed = 2;
                runner->groundVelocity[0] = 0.0f;
                runner->percentRanPerFrame_slideAdj = 0.0f;
                runner->roundingStrengthPercent = 0.0f;
                fn_3_810C4(runnerIdx, runner->baseStandingOn);
                runner->framesSinceLastDirectionChange = 1;
            }
        }
    }
}

// .text:0x00081EAC size:0x508 mapped:0x806C0F40
int runnerOverrun1BRelated(int runnerIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];

    if (runner->fractionalBasesRan < 1.0f) {
        return 0;
    }
    if (runner->nextDirectionBeingProcessed == 1) {
        f32 dx;
        f32 dz;
        f32 dxSq;
        f32 dzSq;
        f32 distTo1B;
        f32 distTo2B;
        f32 proportion;

        runner->overRun1BStage = 0;
        runner->runningDirectionCode = 2;
        runner->overrunning1BIndicator = 1;
        dx = baseCoordsForRunning[1][0] - runner->position.x;
        dz = baseCoordsForRunning[1][1] - runner->position.z;
        dxSq = dx * dx;
        dzSq = dz * dz;
        distTo1B = dolsqrtf2(dxSq + dzSq);
        dx = baseCoordsForRunning[2][0] - runner->position.x;
        dz = baseCoordsForRunning[2][1] - runner->position.z;
        dxSq = dx * dx;
        dzSq = dz * dz;
        distTo2B = dolsqrtf2(dxSq + dzSq);
        proportion = (f32)(int)(10000.0f * (distTo1B / (distTo1B + distTo2B))) / 10000.0f;
        runner->percentTowardsNextBase = proportion;
        runner->fractionalBasesRan = 1.0f + proportion;
        runner->fractionalBasesRan_stored = runner->fractionalBasesRan;
        runner->percentTowardsNextBase_stored = runner->percentTowardsNextBase;
        runner->groundVelocity[0] = 0.0f;
        runner->percentRanPerFrame_slideAdj = 0.0f;
        runner->percentFromCurrentBase_slideAdj = runner->percentTowardsNextBase - runner->slidingAdjustment_backwards;
        runner->percentTowardsNextBase_slideAdj =
            (1.0f - runner->percentTowardsNextBase) - runner->slidingAdjustment_forwards;
        return 1;
    }
    if (runner->overRun1BStage == 1) {
        runner->overRun1BStage = 2;
        runner->overrunBaseFrames_countUp = 0;
        runner->overrunBaseFrames_countDown = lbl_3_data_4B40[0];
        runner->runningDirectionCode = 4;
        runner->overrun1B_someDistConst_proportionPerFrame =
            1.0f /
            (f32)((runner->overrunBaseFrames_countDown + 1) * (runner->overrunBaseFrames_countDown / 2));
        runner->overrun1B_somePositionControl = 0.0f;
    }
    if (runner->overRun1BStage == 2) {
        runner->overrunBaseFrames_countUp++;
        runner->overrunBaseFrames_countDown--;
        if (runner->overrunBaseFrames_countDown == 0) {
            runner->overRun1BStage = 3;
            runner->overrunBaseFrames_countUp = 0;
            runner->overrunBaseFrames_countDown = lbl_3_data_4B40[1];
        } else {
            runner->overrun1B_somePositionControl =
                runner->overrun1B_someDistConst_proportionPerFrame * (f32)runner->overrunBaseFrames_countDown +
                runner->overrun1B_somePositionControl;
        }
    }
    if (runner->overRun1BStage == 3) {
        runner->overrunBaseFrames_countUp++;
        runner->overrunBaseFrames_countDown--;
        if (runner->overrunBaseFrames_countDown == 0) {
            runner->runningDirectionCode = 2;
            runner->overRun1BStage = 0;
            fn_3_810C4(runnerIdx, 1);
            return 1;
        }
    }
    return 1;
}

// .text:0x00081BC8 size:0x2E4 mapped:0x806C0C5C
int running_overrunBaseControl(int runnerIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];

    if (runner->runningDirectionDesired == 1) {
        runner->nextDirectionBeingProcessed = 1;
        runner->overrunBaseStage = 0;
        return 0;
    }
    if (runner->overrunBaseStage == 1) {
        runner->overrunBaseStage = 2;
        runner->overrunBaseFrames_countUp = 0;
        runner->overrunBaseFrames_countDown = lbl_3_data_4B48[0];
        runner->runningDirectionCode = 5;
        {
            f32 denom = (f32)((runner->overrunBaseFrames_countDown + 1) * (runner->overrunBaseFrames_countDown / 2));
            runner->overrun1B_someDistConst_proportionPerFrame = lbl_3_data_4B44[0] / denom;
        }
    }
    if (runner->overrunBaseStage == 2) {
        runner->overrunBaseFrames_countUp++;
        runner->overrunBaseFrames_countDown--;
        if (runner->overrunBaseFrames_countDown < 0) {
            runner->overrunBaseStage = 3;
            runner->overrunBaseFrames_countUp = 0;
            runner->overrunBaseFrames_countDown = lbl_3_data_4B48[1];
            runner->overrun1B_someDistConst_proportionPerFrame =
                (runner->slidingAdjustment_backwards - runner->percentTowardsNextBase) / (f32)runner->overrunBaseFrames_countDown;
        } else {
            runner->percentRanPerFrame_slideAdj =
                runner->overrun1B_someDistConst_proportionPerFrame * (f32)runner->overrunBaseFrames_countDown;
        }
    }
    if (runner->overrunBaseStage == 3) {
        runner->overrunBaseFrames_countUp++;
        runner->overrunBaseFrames_countDown--;
        if (runner->overrunBaseFrames_countDown < 0) {
            runner->overrunBaseStage = 0;
            runner->runningDirectionCode = 2;
            runner->nextDirectionBeingProcessed = 2;
            runner->groundVelocity[0] = 0.0f;
            runner->percentRanPerFrame_slideAdj = 0.0f;
            runner->roundingStrengthPercent = 0.0f;
            fn_3_810C4(runnerIdx, runner->currentBase);
        } else {
            runner->percentRanPerFrame_slideAdj = runner->overrun1B_someDistConst_proportionPerFrame;
            runner->offsetFromNormalRunningPathInd = 0;
        }
    }
    runner->fractionalBasesRan += runner->percentRanPerFrame_slideAdj;
    runner->percentTowardsNextBase += runner->percentRanPerFrame_slideAdj;
    runner->percentFromCurrentBase_slideAdj = runner->percentTowardsNextBase - runner->slidingAdjustment_backwards;
    runner->percentTowardsNextBase_slideAdj =
        (1.0f - runner->percentTowardsNextBase) - runner->slidingAdjustment_forwards;
    return 1;
}

// .text:0x00081AEC size:0xDC mapped:0x806C0B80
void fn_3_81AEC(int runnerIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];

    if (runner->leadoffDurationFrames < 0x7FFE) {
        runner->leadoffDurationFrames++;
    } else {
        runner->leadoffDurationFrames = 0x7FFF;
    }

    if (runner->leadOffTotalFrameCountDown <= 0) {
        runner->leadOffStatus = 2;
        runner->percentRanPerFrame_slideAdj = 0.0f;
    } else {
        f32 step = (runner->leadoffDistancePercent + runner->slidingAdjustment_backwards) -
                   runner->percentTowardsNextBase;
        step /= (f32)runner->leadOffTotalFrameCountDown;

        runner->percentRanPerFrame_slideAdj = step;
        runner->percentTowardsNextBase += step;
        runner->fractionalBasesRan = (f32)runner->startingBase_baseAchieved + runner->percentTowardsNextBase;
        runner->leadOffTotalFrameCountDown--;
    }
}

// .text:0x00081AB8 size:0x34 mapped:0x806C0B4C
void fn_3_81AB8(int runnerIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];

    runner->runningDirectionCode = 2;
    runner->nextDirectionBeingProcessed = 2;
    runner->groundVelocity[0] = 0.0f;
    runner->percentRanPerFrame_slideAdj = 0.0f;
    runner->roundingStrengthPercent = 0.0f;
}

// .text:0x00081190 size:0x928 mapped:0x806C0224
void running_updatePositionTracking_storeRBIs_stopAtNextBase_displaySafe(int runnerIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];
    int newBase = -1;
    s16 baseOnStored = runner->baseStandingOn;
    BOOL wrapAllowed = FALSE;

    if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD ||
        runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_OUT_DURING_PLAY ||
        runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DEAD_BALL) {
        if (runner->groundVelocity[0] > 0.0f) {
            int fracBasesRun = (int)runner->fractionalBasesRan;

            if (fracBasesRun > (int)runner->fractionalBasesRan_stored) {
                if (runner->baseRoundingState == 2) {
                    runner->fractionalBasesRan = (f32)fracBasesRun;
                    runner->percentTowardsNextBase = 0.0f;
                    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
                        if (runner->fractionalBasesRan >= 4.0f) {
                            runner->fractionalBasesRan -= 4.0f;
                        }
                    } else if (runner->runningDirectionDesired != 1) {
                        runner->runningDirectionCode = 2;
                        runner->nextDirectionBeingProcessed = 2;
                        runner->overrunBaseStage = 1;
                    }
                } else if (runner->baseRoundingState == 1) {
                    runner->fractionalBasesRan = (f32)fracBasesRun;
                    runner->percentTowardsNextBase = 0.0f;
                } else if (runner->actionCode != 0) {
                    runner->fractionalBasesRan = (f32)fracBasesRun;
                    runner->percentTowardsNextBase = 0.0f;
                    if (runner->runnerOnFieldOrOutOrScored != RUNNER_STATUS_ON_FIELD) {
                        running_updateDistAndFramesToClosestBases(runnerIdx);
                    }
                } else {
                    newBase = fracBasesRun & 3;
                }
            }

        } else if (runner->groundVelocity[0] < 0.0f) {
            if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
                wrapAllowed = TRUE;
            }

            if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT && runner->tagUpInd == TAG_UP_TYPE_TAGGED &&
                runner->currentBase > runner->startingBase_baseAchieved) {
                wrapAllowed = TRUE;
            }
            if (wrapAllowed) {
                if (runner->fractionalBasesRan < 0.0f) {
                    runner->fractionalBasesRan += 4.0f;
                    runner->percentTowardsNextBase += 1.0f;
                }
            } else if (runner->percentTowardsNextBase <= runner->slidingAdjustment_backwards) {
                if (runner->actionCode != 0) {
                    runner->fractionalBasesRan = (f32)(int)runner->fractionalBasesRan + runner->slidingAdjustment_backwards;
                    runner->percentTowardsNextBase = runner->slidingAdjustment_backwards;
                } else {
                    newBase = runner->currentBase;
                }
            }
        }

        if (newBase >= 0) {
            fn_3_81AB8(runnerIdx);
            fn_3_810C4(runnerIdx, newBase);
        }

        if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD ||
            (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DEAD_BALL &&
             g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FOUL)) {
            s16 base;

            runner->baseStandingOn = -1;
            if (runner->fractionalBasesRan > 0.5f ||
                g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
                if (runner->fractionalBasesRan >= 4.0f) {
                    runner->baseStandingOn = 0;
                } else if (runner->percentTowardsNextBase <= runner->slidingAdjustment_backwards) {
                    runner->baseStandingOn = (int)runner->fractionalBasesRan;
                } else if (runner->percentTowardsNextBase >= 1.0f - runner->slidingAdjustment_forwards) {
                    runner->baseStandingOn = ((int)runner->fractionalBasesRan + 1) & 3;
                }
            }
            base = runner->baseStandingOn;
            if (base >= 0) {
                if (0.0f == runner->groundVelocity[0] && runner->percentTowardsNextBase > 0.5f) {
                    fn_3_810C4(runnerIdx, base);
                }
                if (runner->baseStandingOn == g_Ball.baseBallAndFielderAreOn && baseOnStored == -1) {
                    g_FieldingLogic.baseFielderIsOn = -1;
                    if (g_FieldingLogic.bodyCheckResult == 1) {
                        if (g_Pitcher.strikeOutOrWalk != 2 ||
                            (runner->furthestBaseForcedToGoToOnWalk <= runner->currentBase &&
                             (runner->forcedToAdvanceInd == 0 || runner->currentBase != runner->startingBase_baseAchieved))) {
                            runner->baseOfFailedBodyCheck = runner->baseStandingOn;
                            runner->baseStandingOn = -1;
                            g_FieldingLogic.tagAnimationType = 1;
                            g_FieldingLogic.runnerBeingTargettedForOut = runnerIdx;
                        }
                    } else if (g_Strikes.outs < 3 && (runner->tagUpInd != TAG_UP_TYPE_TAGGED ||
                                                      g_Ball.baseBallAndFielderAreOn == runner->startingBase_baseAchieved)) {
                        QueueTextToDisplay(2, 0);
                    }
                } else if (baseOnStored == -1 && g_Ball.framesSinceHit > 100 && g_Ball.fielderWBallIndex >= 0 &&
                           g_Ball.ballDistanceFromBase[runner->baseStandingOn] < 2.5f) {
                    if (runner->forceOutCd == FORCE_OUT_TYPE_FORCED_TO_ADVANCE) {
                        QueueTextToDisplay(2, 0);
                    } else if (runner->tagUpInd == TAG_UP_TYPE_TAGGED) {
                        QueueTextToDisplay(2, 0);
                    } else if (runner->baseOfFailedBodyCheck < 0 && runner->tagType != 2 &&
                               runner->runnerOnFieldOrOutOrScored != RUNNER_STATUS_OUT_DURING_PLAY &&
                               (g_FieldingLogic.tagAnimationType == 2 || g_FieldingLogic.tagAnimationType == 4)) {
                        QueueTextToDisplay(2, 0);
                    }
                }
                running_updateDistAndFramesToClosestBases(runnerIdx);
                if (runner->baseStandingOn == runner->startingBase_baseAchieved && runner->tagUpInd == TAG_UP_TYPE_TAGGED) {
                    runner->tagUpInd = TAG_UP_TYPE_NONE;
                }
                if (runner->runningDirectionCode == 1) {
                    if (runner->percentTowardsNextBase < 0.5f) {
                        runner->roundingInitiaializedInd = 0;
                        runner->offsetPositionForRoundingInd = 0;
                    }
                } else if (runner->runningDirectionCode == 3) {
                    if (0.5f < runner->percentTowardsNextBase) {
                        runner->roundingInitiaializedInd = 0;
                        runner->offsetPositionForRoundingInd = 0;
                    }
                } else {
                    runner->roundingInitiaializedInd = 0;
                    runner->offsetPositionForRoundingInd = 0;
                }
                runner->overrunning1BIndicator = 0;
            }
            if (runner->baseStandingOn == 0) {
                if (g_Strikes.outs < 3 && g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES &&
                    (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_LANDED ||
                     g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FIELDED ||
                     (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT && runner->tagUpInd == TAG_UP_TYPE_NONE) ||
                     (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR && g_Strikes.storedOuts == 2) ||
                     g_Practice.practiceType_2 == PRACTICE_TYPE_BASERUNNING)) {
                    runner->runningDirectionCode = 0;
                    runner->runnerOnFieldOrOutOrScored = RUNNER_STATUS_SCORED_DURING_PLAY;
                    if (g_GameLogic.EventTriggers_EndOfGame != 0) {
                        runner->runnerOnFieldOrOutOrScored = RUNNER_STATUS_SCORED_DEAD_BALL;
                    } else if (g_Ball.deadBallReason != 0) {
                        runner->runnerOnFieldOrOutOrScored = RUNNER_STATUS_SCORED_DEAD_BALL;
                    } else {
                        (*(s16*)&g_Scores._pad_50[0x4C])++;
                    }
                    if (runner->actionCode != 0) {
                        runner->runningToDugoutInd = 2;
                    } else {
                        runner->runningToDugoutInd = 3;
                    }
                    runner->runningToDugoutStage = 0;
                }
                if (runner->actionCode != 0 && runner->slideHomeFrames_CountDown == 0 &&
                    g_GameLogic.secondaryGameMode != SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
                    runner->slideHomeFrames_CountDown = lbl_3_data_4C54[0];
                }
            } else if (runner->fractionalBasesRan >= 4.0f && g_GameLogic.EventTriggers_EndOfGame != 0 &&
                       runner->actionCode != 0) {
                runner->runningToDugoutInd = 2;
            }
        }
    }
}

// .text:0x000810C4 size:0xCC mapped:0x806C0158
void fn_3_810C4(int runnerIdx, int base) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];
    int nextBase = (base + 1) & 3;

    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
        runner->runningAngle = someRunningAngleArray[base][2];
        runner->percentTowardsNextBase = 0.0f;
    } else {
        runner->percentTowardsNextBase = runner->slidingAdjustment_backwards;
    }
    runner->fractionalBasesRan = runner->percentTowardsNextBase + (f32)base;
    runner->baseStandingOn = base;
    runner->currentBaseCoordinates.x = baseCoordsForRunning[base][0];
    runner->currentBaseCoordinates.z = baseCoordsForRunning[base][1];
    runner->nextBaseCoordinates.x = baseCoordsForRunning[nextBase][0];
    runner->nextBaseCoordinates.z = baseCoordsForRunning[nextBase][1];
}

// .text:0x00080028 size:0x109C mapped:0x806BF0BC
void running_updatePosition(int runnerIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];
    VecXYZ vec;
    f32 xF;
    f32 yF;
    f32 zF;
    f32 a;
    f32 b;
    f32 s;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 tx;
    f32 tz;

    do {
        if (g_GameLogic.secondaryGameMode != SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
            if (g_Ball.framesSinceHit <= 0 && runnerIdx == 0) {
                runner->position.x = g_Batter.batterPos.x;
                runner->position.y = 0.0f;
                runner->position.z = g_Batter.batterPos.z;
                runner->fractionalBasesRan = 0.0f;
                runner->percentTowardsNextBase = 0.0f;
                runner->fractionalBasesRan_stored = 0.0f;
                runner->percentTowardsNextBase_stored = 0.0f;
                runner->groundVelocity[0] = 0.0f;
                runner->runningDirectionCode = 0;
                runner->nextDirectionBeingProcessed = 0;
                break;
            }
            if (runner->overRun1BStage >= 2) {
                if (runner->overRun1BStage == 2) {
                    running_roundBasePosition(runner->overrun1B_somePositionControl, (VecXZ*)&vec, lbl_3_data_4B28, 3);
                    runner->position.x = vec.x;
                    runner->position.z = vec.y;
                } else if (runner->overRun1BStage == 3) {
                    tx = addScaled(baseCoordsForRunning[1][0], baseCoordsForRunning[2][0] - baseCoordsForRunning[1][0],
                                   runner->slidingAdjustment_backwards);
                    tz = addScaled(baseCoordsForRunning[1][1], baseCoordsForRunning[2][1] - baseCoordsForRunning[1][1],
                                   runner->slidingAdjustment_backwards);
                    vec.x = (tx - runner->position.x) / (f32)runner->overrunBaseFrames_countDown;
                    vec.y = (0.0f - runner->position.y) / (f32)runner->overrunBaseFrames_countDown;
                    vec.z = (tz - runner->position.z) / (f32)runner->overrunBaseFrames_countDown;
                    runner->position.x += vec.x;
                    runner->position.y += vec.y;
                    runner->position.z += vec.z;
                }
                break;
            }
            if (runner->slideHomeFrames_CountDown != 0) {
                runner->slideHomeFrames_CountDown--;
                break;
            }
            if (runner->actionCode != 0 && runner->actionStage == 2) {
                if (runner->timeStandingOnBase >= 6) {
                    if ((s8)runner->baseOfFailedBodyCheck >= 0) {
                        int base = (s8)runner->baseOfFailedBodyCheck;

                        tx = addScaled(baseCoordsForRunning[base][0],
                                       baseCoordsForRunning[(base + 1) & 3][0] - baseCoordsForRunning[base][0],
                                       runner->slidingAdjustment_backwards);
                        tz = addScaled(baseCoordsForRunning[base][1],
                                       baseCoordsForRunning[(base + 1) & 3][1] - baseCoordsForRunning[base][1],
                                       runner->slidingAdjustment_backwards);
                    } else {
                        int base = runner->baseStandingOn;

                        tx = addScaled(baseCoordsForRunning[base][0],
                                       baseCoordsForRunning[(base + 1) & 3][0] - baseCoordsForRunning[base][0],
                                       runner->slidingAdjustment_backwards);
                        tz = addScaled(baseCoordsForRunning[base][1],
                                       baseCoordsForRunning[(base + 1) & 3][1] - baseCoordsForRunning[base][1],
                                       runner->slidingAdjustment_backwards);
                    }
                    dy = 0.0f - runner->position.y;
                    vec.x = (tx - runner->position.x) / (f32)runner->actionFrames_countDown;
                    vec.y = dy / (f32)runner->actionFrames_countDown;
                    vec.z = (tz - runner->position.z) / (f32)runner->actionFrames_countDown;
                    runner->position.x += vec.x;
                    runner->position.y += vec.y;
                    runner->position.z += vec.z;
                }
                break;
            }
            if (runner->runningToDugoutInd == 1) {
                if (runner->runningToDugoutStage == 0) {
                    runner_beginRunToDugout(runner);
                }
                if (runner->runningToDugoutStage == 2) {
                    runner_trackRunToDugout(runner);
                }
                break;
            }
            if (runner->runningToDugoutInd == 3) {
                if (runner->runningToDugoutStage == 0) {
                    f32 len;

                    runner->nextBaseCoordinates.x =
                        dugoutCoordinates[g_d_GameSettings.StadiumID].team[g_GameLogic.homeTeamBattingInd_fieldingTeam].x;
                    runner->nextBaseCoordinates.z =
                        dugoutCoordinates[g_d_GameSettings.StadiumID].team[g_GameLogic.homeTeamBattingInd_fieldingTeam].z;
                    dolsqrtf2((runner->nextBaseCoordinates.z - runner->position.z) * (runner->nextBaseCoordinates.z - runner->position.z) +
                              (runner->nextBaseCoordinates.x - runner->position.x) * (runner->nextBaseCoordinates.x - runner->position.x));
                    dx = runner->velocity.x;
                    dz = runner->velocity.z;
                    dx = dx * dx;
                    dz = dz * dz;
                    len = dolsqrtf2(dx + dz);
                    if (len <= 0.0f) {
                        runner->velocity.x = 1.0f;
                        runner->velocity.z = -1.0f;
                    } else {
                        runner->velocity.x = runner->velocity.x / len;
                        runner->velocity.z = runner->velocity.z / len;
                    }
                    runner->velocity.y = 0.0f;
                    runner->velocity.x = runner->velocity.x * runner->maximumBaseVelocity;
                    runner->velocity.z = runner->velocity.z * runner->maximumBaseVelocity;
                    runner->runningToDugoutFrameCounter = 0;
                    runner->framesToReachDugout = lbl_3_data_4B54[0];
                    runner->runningToDugoutStage = 1;
                }
                if (runner->runningToDugoutStage == 1) {
                    runner->framesToReachDugout--;
                    runner->position.x += runner->velocity.x;
                    runner->position.y += runner->velocity.y;
                    runner->position.z += runner->velocity.z;
                    if (runner->framesToReachDugout <= 0) {
                        runner_beginRunToDugout(runner);
                    }
                }
                if (runner->runningToDugoutStage == 2) {
                    runner_trackRunToDugout(runner);
                }
                break;
            }
            if (runner->runningToDugoutInd != 0) {
                if (runner->runningToDugoutStage == 0) {
                    runner_beginRunToDugout(runner);
                }
                if (runner->runningToDugoutStage == 2) {
                    runner_trackRunToDugout(runner);
                }
                break;
            }
        }

        xF = addScaled(runner->currentBaseCoordinates.x, runner->nextBaseCoordinates.x - runner->currentBaseCoordinates.x,
                       runner->percentTowardsNextBase);
        yF = addScaled(runner->currentBaseCoordinates.y, runner->nextBaseCoordinates.y - runner->currentBaseCoordinates.y,
                       runner->percentTowardsNextBase);
        zF = addScaled(runner->currentBaseCoordinates.z, runner->nextBaseCoordinates.z - runner->currentBaseCoordinates.z,
                       runner->percentTowardsNextBase);

        fn_3_7FED4(&vec, runner->fractionalBasesRan, runner->percentTowardsNextBase);

        if (runner->overrunning1BIndicator != 0 && runner->fractionalBasesRan < 2.0f) {
            if (runner->runningDirectionCode == 1) {
                a = 1.0f - runner->percentTowardsNextBase_stored;
                b = 1.0f - runner->percentTowardsNextBase;
                dx = runner->nextBaseCoordinates.x - runner->positionStored.x;
                dy = runner->nextBaseCoordinates.y - runner->positionStored.y;
                dz = runner->nextBaseCoordinates.z - runner->positionStored.z;
            } else {
                a = -runner->percentTowardsNextBase_stored;
                b = -runner->percentTowardsNextBase;
                dx = runner->currentBaseCoordinates.x - runner->positionStored.x;
                dy = runner->currentBaseCoordinates.y - runner->positionStored.y;
                dz = runner->currentBaseCoordinates.z - runner->positionStored.z;
            }
            if (0.0f == a) {
                vec.x = xF;
                vec.y = yF;
                vec.z = zF;
            } else {
                s = 1.0f - b / a;
                vec.x = addScaled(runner->positionStored.x, dx, s);
                vec.y = addScaled(runner->positionStored.y, dy, s);
                vec.z = addScaled(runner->positionStored.z, dz, s);
            }
            runner->position.x = vec.x;
            runner->position.y = vec.y;
            runner->position.z = vec.z;
        } else if (runner->offsetFromNormalRunningPathInd != 0 && runner->roundingInitiaializedInd == 0) {
            if (runner->runningDirectionCode != 2 && runner->nextDirectionBeingProcessed == 0 && runner->turningAroundInd != 1) {
                runner->roundingStrengthPercent += lbl_3_data_4B24;
            }
            if (runner->roundingStrengthPercent < 0.0f) {
                runner->roundingStrengthPercent = 0.0f;
            }
            if (runner->roundingStrengthPercent > 1.0f) {
                runner->roundingStrengthPercent = 1.0f;
            }
            runner->position.x = addScaled(xF, vec.x - xF, runner->roundingStrengthPercent);
            runner->position.y = addScaled(yF, vec.y - yF, runner->roundingStrengthPercent);
            runner->position.z = addScaled(zF, vec.z - zF, runner->roundingStrengthPercent);
            runner->offsetPositionForRoundingInd = 1;
            runner->_110 = 0;
        } else {
            runner->roundingStrengthPercent = 0.0f;
            if (runner->offsetPositionForRoundingInd == 0) {
                runner->position.x = xF;
                runner->position.y = yF;
                runner->position.z = zF;
            } else {
                if (g_GameLogic.secondaryGameMode != SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
                    runner->roundingInitiaializedInd = 1;
                }
                if (runner->runningDirectionCode == 1) {
                    a = 1.0f - runner->percentTowardsNextBase_stored;
                    b = 1.0f - runner->percentTowardsNextBase;
                    if (b > a) {
                        a += 1.0f;
                    }
                    dx = runner->nextBaseCoordinates.x - runner->positionStored.x;
                    dy = runner->nextBaseCoordinates.y - runner->positionStored.y;
                    dz = runner->nextBaseCoordinates.z - runner->positionStored.z;
                } else {
                    a = -runner->percentTowardsNextBase_stored;
                    b = -runner->percentTowardsNextBase;
                    dx = runner->currentBaseCoordinates.x - runner->positionStored.x;
                    dy = runner->currentBaseCoordinates.y - runner->positionStored.y;
                    dz = runner->currentBaseCoordinates.z - runner->positionStored.z;
                }
                if (0.0f == a) {
                    vec.x = xF;
                    vec.y = yF;
                    vec.z = zF;
                } else {
                    s = 1.0f - b / a;
                    vec.x = addScaled(runner->positionStored.x, dx, s);
                    vec.y = addScaled(runner->positionStored.y, dy, s);
                    vec.z = addScaled(runner->positionStored.z, dz, s);
                }
                runner->position.x = vec.x;
                runner->position.y = vec.y;
                runner->position.z = vec.z;
            }
        }
    } while (0);
    runner->position.y = 0.0f;
}

// .text:0x0007FFD0 size:0x58 mapped:0x806BF064
void fn_3_7FFD0(VecXYZ* out, int fromBase, int toBase, f32 t) {
    f32 dx = baseCoordsForRunning[toBase][0] - baseCoordsForRunning[fromBase][0];
    f32 dz = baseCoordsForRunning[toBase][1] - baseCoordsForRunning[fromBase][1];

    dx *= t;
    dz *= t;
    out->x = dx + baseCoordsForRunning[fromBase][0];
    out->z = dz + baseCoordsForRunning[fromBase][1];
    out->y = 0.0f;
}

// .text:0x0007FED4 size:0xFC mapped:0x806BEF68
void fn_3_7FED4(VecXYZ* out, f32 speed, f32 frame) {
    VecXZ result;
    int start;
    int count;

    if (speed < 1.0f) {
        start = 0;
        count = 4;
    } else if (speed < 2.0f) {
        start = 3;
        count = 4;
    } else if (speed < 3.0f) {
        start = 6;
        count = 4;
    } else if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
        start = 9;
        count = 4;
    } else {
        start = 9;
        count = 3;
    }

    running_roundBasePosition(frame, &result,
                              &lbl_3_data_4A54[g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT][start],
                              count);
    out->x = result.x;
    out->z = result.z;
    out->y = 0.0f;
}

// .text:0x0007FEA8 size:0x2C mapped:0x806BEF3C
void fn_3_7FEA8(int runnerIdx, int direction) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];

    if (runner->rosterID < 0) {
        return;
    }
    if (direction == 0) {
        return;
    }
    runner->runningDirectionDesired = direction;
}

// .text:0x0007FD90 size:0x118 mapped:0x806BEE24
void fn_3_7FD90(int runnerIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];
    int override;

    if ((runner->runningToDugoutInd == 0 || runner->runningToDugoutStage == 0) && runner->actionCode == 0) {
        if (runner->framesSinceLastDirectionChange >= lbl_3_data_4C54[3] ||
            (runner->runningDirectionCode != 1 && runner->runningDirectionCode != 3)) {
            u8 desired = runner->runningDirectionDesired;

            if (desired != 0) {
                if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
                    if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                        runner->nextDirectionBeingProcessed = desired;
                    }
                } else {
                    if ((runnerIdx != 0 || runner->nextBase != 1) &&
                        runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                        runner->nextDirectionBeingProcessed = desired;
                    }
                    if (runner->nextDirectionBeingProcessed == 3 && runner->tagUpInd != 3 &&
                        runner->baseStandingOn >= 0) {
                        runner->nextDirectionBeingProcessed = 0;
                    }
                }
            }
        }
        override = running_DirectionOverrides(runnerIdx);
        if (override != 0) {
            runner->nextDirectionBeingProcessed = override;
        }
    }
}

// .text:0x0007FA78 size:0x318 mapped:0x806BEB0C
int running_DirectionOverrides(int runnerIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];
    int prevent;

    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
        if (g_Minigame.turnOverStatus != 0) {
            return 2;
        }
        if (g_Minigame._1B19 == 2 || g_Minigame._1B19 == 3) {
            return 2;
        }
        return 0;
    }
    if (g_GameLogic.secondaryGameMode != SECONDARY_GAME_MODE_PRACTICE_BASERUNNING) {
        u8 stealCode;

        if (g_Ball.framesSinceHit <= 0) {
            return 0;
        }
        stealCode = g_FieldingLogic.liveBallBcOfPickoffOrStealCd;
        if (stealCode == 1) {
            if (runnerIdx != 0 && runner->runningDirectionCode == 2 && runner->runningDirectionDesired == 0 &&
                g_Ball.framesSincePickOff == lbl_3_data_4C54[4]) {
                return 3;
            }
        } else if (stealCode == 2) {
            if (runnerIdx != 0 && runner->runningDirectionCode == 2 && runner->runningDirectionDesired == 0 &&
                g_Ball.framesSincePickOff == lbl_3_data_4C54[4]) {
                return 3;
            }
        }
        if (runnerIdx == 0) {
            if (runner->fractionalBasesRan < 1.0f && runner->forceOutCd == FORCE_OUT_TYPE_FORCED_TO_ADVANCE &&
                g_FieldingLogic.infieldFlyIndicator == 0 && stealCode == 0) {
                return 1;
            }
        } else if (runner->leadOffStatus == 1) {
            return 1;
        }
        if (g_Ball.deadBallReason == 1) {
            return 1;
        }
        if (g_Ball.framesSinceHit == 5) {
            return 1;
        }
    }
    prevent = runner->restrictedMovementCodes;
    if (prevent & PREVENT_PASSING_TYPE_PREVENT_CROSSINGPLATE) {
        if (runner->runningDirectionCode == 1) {
            return 2;
        }
        if (runner->nextDirectionBeingProcessed == 1 && runner->runningDirectionCode == 2) {
            return 2;
        }
    } else if (prevent & PREVENT_PASSING_TYPE_PREVENT_FORWARD) {
        if ((runner->baseRoundingState != 1 || runner->overRun1BStage == 0) && runner->runningDirectionCode == 1) {
            return 2;
        }
        if (runner->nextDirectionBeingProcessed == 1) {
            return 2;
        }
    } else if (prevent & PREVENT_PASSING_TYPE_PREVENT_BACKWARD) {
        if (runner->runningDirectionCode == 3) {
            return 2;
        }
        if (runner->nextDirectionBeingProcessed == 3) {
            return 2;
        }
    } else if (runner->restrictedMovementCodes_stored & PREVENT_PASSING_TYPE_PREVENT_CROSSINGPLATE) {
        if ((prevent & PREVENT_PASSING_TYPE_PREVENT_FORWARD) == 0 && g_Ball.framesSinceHit > 0 &&
            (runner->runningDirectionCode == 2 || runner->nextDirectionBeingProcessed == 2) &&
            runner->tagUpInd == TAG_UP_TYPE_NONE) {
            return 1;
        }
    } else if (runner->restrictedMovementCodes_stored & PREVENT_PASSING_TYPE_TAG_UP) {
        if ((prevent & PREVENT_PASSING_TYPE_PREVENT_BACKWARD) == 0 &&
            (runner->runningDirectionCode == 2 || runner->nextDirectionBeingProcessed == 2)) {
            return 3;
        }
    }
    if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT && runner->tagUpInd == TAG_UP_TYPE_TAGGED) {
        return 3;
    }
    return 0;
}

// .text:0x0007F9C4 size:0xB4 mapped:0x806BEA58
void fn_3_7F9C4(int runnerIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];

    if (runner->runningToDugoutInd != 0) {
        runner->baseRoundingState = 0;
        runner->actionCode = 0;
        return;
    }
    running_roundBaseDecision(runnerIdx);
    running_triggerSlideOrBodyCheck(runnerIdx);
    if (g_GameLogic.secondaryGameMode != SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
        if (runnerIdx == 0 && runner->nextBase == 1) {
            running_overrun1stIndicator();
        } else if (runner->baseRoundingState == 1) {
            runner->baseRoundingState = 0;
        }
        running_sendOutRunnerToDugout(runnerIdx);
    }
}

// .text:0x0007F494 size:0x530 mapped:0x806BE528
int running_triggerSlideOrBodyCheck(int runnerIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];
    int bodyCheckChance = 0;
    u8 direction;
    int framesToBase;
    f32 framesExact;
    int frameDiff;

    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
        return 0;
    }
    if (runner->runnerOnFieldOrOutOrScored != RUNNER_STATUS_ON_FIELD &&
        runner->runnerOnFieldOrOutOrScored != RUNNER_STATUS_OUT_DURING_PLAY) {
        return 0;
    }
    if (runner->baseStandingOn >= 0) {
        return 0;
    }
    direction = runner->runningDirectionCode;
    if (!((direction == 1 && runner->percentRanPerFrame_slideAdj > 0.0f) ||
          (direction == 3 && runner->percentRanPerFrame_slideAdj < 0.0f))) {
        return 0;
    }
    if (runner->actionCode != 0) {
        return 1;
    }
    if (runner->baseRoundingState == 2) {
        return 0;
    }
    if (runner->nextBase == 1) {
        return 0;
    }
    if (direction == 3) {
        if (runner->tagUpInd == TAG_UP_TYPE_TAGGED && runner->currentBase != runner->startingBase_baseAchieved) {
            return 0;
        }
        if (runner->forceOutCd == FORCE_OUT_TYPE_FORCED_TO_ADVANCE && g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_IN_AIR) {
            return 0;
        }
    }
    if (direction == 1) {
        framesExact = runner->percentTowardsNextBase_slideAdj / runner->percentRanPerFrame_slideAdj;
    } else {
        framesExact = runner->percentFromCurrentBase_slideAdj / -runner->percentRanPerFrame_slideAdj;
    }
    framesToBase = (int)framesExact + 1;
    if (g_Ball.ballState == BALL_STATE_THROWN) {
        if (g_FieldingLogic.locationThrownTo == runner->baseRunningTowards) {
            frameDiff = g_Ball.framesUntilThrowReachesDest + 6 - framesToBase;
            if (frameDiff >= lbl_3_data_4C54[1] && frameDiff <= lbl_3_data_4C54[2]) {
                bodyCheckChance = 1;
            }
        }
    } else if (g_Ball.ballState == BALL_STATE_HELD) {
        frameDiff = 6 - g_Ball.timeSinceBallPickedUp - framesToBase;
        if (frameDiff >= lbl_3_data_4C54[1] && frameDiff <= lbl_3_data_4C54[2]) {
            bodyCheckChance = 1;
        }
    }
    if (framesToBase < runnerConstants[runner->charID][0] || framesToBase > runnerConstants[runner->charID][1]) {
        return 0;
    }
    runner->actionCode = 1;
    runner->actionFrames_countUp = 0;
    runner->actionFrames_countDown = framesToBase;
    runner->actionStage = 1;
    if (runner->runningDirectionCode == 1) {
        runner->actionInForwardDirectionInd = 1;
        if (bodyCheckChance && runner->forceOutCd == FORCE_OUT_TYPE_NOT_FORCED_TO_ADVANCE &&
            runner->mashPercent >= lbl_3_data_4C44[0] &&
            checkFieldingStat(g_GameLogic.teamBatting, runner->rosterID, FIELDING_ABILITY_BODY_CHECK) &&
            g_FieldingLogic.baseCoveredInd[runner->baseRunningTowards] != 0 &&
            ((g_Ball.fielderWBallIndex >= 0 &&
              g_Ball.fielderWBallIndex == g_FieldingLogic.fielderAssignedLocationIndex[runner->baseRunningTowards] &&
              g_Ball.timeSinceBallPickedUp <= 9) ||
             (g_FieldingLogic.locationThrownTo == runner->baseRunningTowards &&
              g_Ball.framesUntilThrowReachesDest < 15))) {
            u8 weight = runner->weight;
            s16 fielderIdx = g_FieldingLogic.fielderAssignedLocationIndex[runner->baseRunningTowards];
            u8 baseGoingTo = runner->baseRunningTowards;
            u8 fielderWeight = g_Fielders[fielderIdx].Weight;
            u8 probability;

            g_Fielders[fielderIdx].bodyCheckResult = 1;
            g_Fielders[fielderIdx].bodyCheckBase = baseGoingTo;
            probability = bodyCheckProbabiliities[weight][fielderWeight];
            if (RandomInt_Game(100) < probability) {
                runner->actionCode = 2;
                if (!g_d_GameSettings.exhibitionMatchInd && lbl_3_common_bss_37400[0x20] == g_GameLogic.teamBatting) {
                    starMissionsQuantityBased(12, runner->rosterID);
                }
            } else {
                runner->actionCode = 3;
                if (g_GameLogic.teamIsCPU[g_GameLogic.teamBatting] == 0) {
                    setCharacterAnimations(g_GameLogic.teamBatting, 2);
                }
            }
            fieldingRelatedAnimations(((void**)(hugeAnimStruct + 0x2c50))[runnerIdx + 9], 12);
            playCharacterSound(runner->charID, 10);
            playSoundEffect(0x19C);
            camera_zoomInDuringFielderAction_slide_clamber_wallJump(4, 0, base_MoundCoordinates[runner->baseRunningTowards].x,
                                                                    0.0f,
                                                                    base_MoundCoordinates[runner->baseRunningTowards].z);
        }
    } else {
        runner->actionInForwardDirectionInd = 0;
    }
    if (runner->forceOutCd == FORCE_OUT_TYPE_FORCED_TO_ADVANCE && runner->baseRunningTowards != runner->startingBase_baseAchieved) {
        runner->forceOutType_unsed = 1;
    }
    if (runner->tagUpInd == TAG_UP_TYPE_TAGGED && runner->baseRunningTowards == runner->startingBase_baseAchieved) {
        runner->forceOutType_unsed = 2;
    }
    if (g_Pitcher.strikeOutOrWalk == 2 &&
        (runner->furthestBaseForcedToGoToOnWalk > runner->currentBase ||
         (runner->forcedToAdvanceInd != 0 && runner->currentBase == runner->startingBase_baseAchieved))) {
        runner->forceOutType_unsed = 3;
    }
    return 1;
}

// .text:0x0007F2D8 size:0x1BC mapped:0x806BE36C
BOOL running_overrun1stIndicator(void) {
    InMemRunnerType* runner = &g_Runners[0];

    if (runner->actionCode == 0 && runner->overrun1st_doneChecking == 0) {
        if (runner->overRun1BStage != 0) {
            return 1;
        }
        if (g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_CAUGHT) {
            if (runner->fractionalBasesRan < 0.5f ||
                (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR && runner[1].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
                 (runner[1].baseStandingOn == 1 ||
                  (g_Ball.landingSpotZoneAwayFromHome <= 2 && runner[1].fractionalBasesRan < 1.5f))) ||
                ((g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_IN_AIR || !(g_Ball.maxYOfHit > 15.0f)) &&
                 (g_Ball.ballZoneAwayFromHome <= 1 ||
                  (g_Ball.ballZoneAwayFromHome <= 2 && g_Ball.ballVelocity < 0.2f) ||
                  (g_Ball.fielderWBallIndex >= 0 && g_Ball.ballDistanceFromBase[1] < 25.0f) ||
                  (g_Ball.fielderWBallIndex == 8 && runner->fractionalBasesRan <= 0.75f) ||
                  (g_FieldingLogic.locationThrownTo == 1 && g_Ball.ballState == BALL_STATE_THROWN &&
                   runner->framesToNextBase + 30 > g_Ball.framesUntilThrowReachesDest)))) {
                goto isOverrun1st;
            }
            runner->overrun1st_doneChecking = 1;
        }
    }
    if (runner->baseRoundingState == 1) {
        runner->baseRoundingState = 0;
    }
    return 0;
isOverrun1st:
    runner->baseRoundingState = 1;
    if (runner->fractionalBasesRan > 0.8f) {
        runner->overRun1BStage = 1;
    }
    return 1;
}

// .text:0x0007ECFC size:0x5DC mapped:0x806BDD90
int running_roundBaseDecision(int runnerIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];
    BOOL dontRound = 0;
    f32 effectiveDistance = 100.0f;

    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
        runner->baseRoundingState = 2;
        runner->offsetFromNormalRunningPathInd = 1;
        return 1;
    }

    if (runner->baseRoundingState == 2) {
        runner->baseRoundingState = 0;
    }
    runner->offsetFromNormalRunningPathInd = 0;

    if (g_Ball.framesSinceHit <= 0 && g_Practice.practiceType_2 != PRACTICE_TYPE_BASERUNNING) {
        return 0;
    }
    if (runner->actionCode != 0) {
        return 0;
    }
    if (runner->baseRoundingState == 1) {
        return 0;
    }

    if (runner->runningDirectionCode == 3) {
        dontRound = 1;
    } else {
        if (g_FieldingLogic.locationThrownTo >= 0) {
            f32 dx = base_MoundCoordinates[runner->baseRunningTowards].x - g_Ball.throwTarget.x;
            f32 dz = base_MoundCoordinates[runner->baseRunningTowards].z - g_Ball.throwTarget.z;
            f32 sqx;
            f32 sqz;
            f32 distTargetToBase;
            f32 distContactToTarget;

            sqx = dx * dx;
            sqz = dz * dz;
            distTargetToBase = dolsqrtf2(sqx + sqz);

            dx = g_Ball.AtBat_Contact_BallPos.x - g_Ball.throwTarget.x;
            dz = g_Ball.AtBat_Contact_BallPos.z - g_Ball.throwTarget.z;
            sqx = dx * dx;
            sqz = dz * dz;
            distContactToTarget = dolsqrtf2(sqx + sqz);

            effectiveDistance = distTargetToBase + distContactToTarget;
        }

        if (runner->distanceFromBall < 15.0f) {
            dontRound = 1;
        } else if (effectiveDistance < 20.0f) {
            dontRound = 1;
        } else if (g_Pitcher.strikeOutOrWalk >= 2) {
            dontRound = 1;
        } else if (g_Ball.ballZoneAwayFromHome <= 1 &&
                   (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_LANDED || g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FIELDED) &&
                   runner->percentTowardsNextBase < 0.7f) {
            dontRound = 1;
        } else if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd == 2) {
            dontRound = 1;
        }

        if (g_Practice.practiceType_2 == PRACTICE_TYPE_BASERUNNING) {
            dontRound = 0;
        }

        if (dontRound && g_Ball.ballState == BALL_STATE_HIT && g_Ball.ballZoneAwayFromHome >= 1 &&
            g_Ball.ballVelocity > 0.35f && runner->percentTowardsNextBase >= 0.65f &&
            runner->percentTowardsNextBase <= 0.8f &&
            g_Ball.ballDistanceFromHome > 2.0f + g_Fielders[2].distanceFromHomePlate &&
            g_Ball.ballDistanceFromHome > 2.0f + g_Fielders[4].distanceFromHomePlate) {
            if (g_Ball.ballDistanceFromHome > 2.0f + g_Fielders[3].distanceFromHomePlate &&
                g_Ball.ballDistanceFromHome > 2.0f + g_Fielders[5].distanceFromHomePlate) {
                dontRound = 0;
            } else if (g_Fielders[3].groundDistanceFromBall > g_Fielders[3].distanceFromHomePlate - g_Ball.ballDistanceFromHome &&
                       g_Fielders[5].groundDistanceFromBall > g_Fielders[5].distanceFromHomePlate - g_Ball.ballDistanceFromHome) {
                dontRound = 0;
            }
        }
    }

    if (g_Ball.ballState == BALL_STATE_HELD && g_Ball.ballDistanceFromBase[runner->baseRunningTowards] < 25.0f &&
        runner->percentTowardsNextBase > 0.5f) {
        dontRound = 1;
    }

    if ((runner->runningDirectionCode == 1 || runner->runningDirectionCode == 2) && 0.0f == runner->roundingStrengthPercent &&
        (runner->percentTowardsNextBase < 0.5f || runner->fractionalBasesRan >= 3.0f)) {
        dontRound = 1;
    }

    if (runner->overrunBaseStage != 3 && dontRound) {
        runner->offsetFromNormalRunningPathInd = 0;
        return 0;
    }
    runner->baseRoundingState = 2;
    runner->offsetFromNormalRunningPathInd = 1;
    if (runner->baseStandingOn >= 0) {
        runner->roundingStrengthPercent = 1.0f;
    }
    return 1;
}

// .text:0x0007EBD4 size:0x128 mapped:0x806BDC68
void running_sendOutRunnerToDugout(int runnerIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];

    if (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT) {
        return;
    }
    if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_OUT_DURING_PLAY) {
        if (runner->runningToDugoutInd != 0) {
            return;
        }
        if (runner->actionCode != 0) {
            if (runner->actionStage == 3) {
                runner->actionCode = 0;
                runner->actionStage = 0;
            } else {
                return;
            }
        }
        if (runner->forceOutCd == FORCE_OUT_TYPE_OUT_ON_FORCE) {
            if (runner->overRun1BStage != 0) {
                if (runner->overRun1BStage == 3) {
                    runner->baseRoundingState = 0;
                    runner->overRun1BStage = 0;
                } else {
                    return;
                }
            } else if (!(runner->percentTowardsNextBase < 0.8f)) {
                if (runner->runningDirectionCode != 2) {
                    return;
                }
            }
        }
        runner->runningToDugoutInd = 1;
        runner->runningToDugoutStage = 0;
        runner->overRun1BStage = 0;
    } else {
        if (g_Strikes.outs < 3) {
            return;
        }
        if (runner->actionCode != 0) {
            if (runner->actionStage == 3) {
                runner->actionCode = 0;
                runner->actionStage = 0;
            } else {
                return;
            }
        }
        runner->runningToDugoutInd = 1;
        runner->runningToDugoutStage = 0;
    }
}

// .text:0x0007EA68 size:0x16C mapped:0x806BDAFC
void fn_3_7EA68(void) {
    InputStruct* inputs = &g_Controls[g_GameLogic.teams[g_GameLogic.teamBatting]];

    if (g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_PRE_PITCH ||
        g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_WINDUP ||
        g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_IN_AIR) {
        if (ACTIVE_TUTORIAL()) {
            inputs = &g_Practice.inputs[g_GameLogic.teamBatting];
        }
        if (inputs->newButtonInput & INPUT_BUTTON_Y) {
            if (inputs->controlStickAngle < 0) {
                int i;
                for (i = 1; i <= 3; i++) {
                    if (g_Runners[i].runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE && g_Runners[i].stealingStatus == 0) {
                        g_Runners[i].stealingStatus = 1;
                    }
                }
            } else {
                if (inputs->controlStickAngle >= 0x1C0 && inputs->controlStickAngle <= 0x640) {
                    g_Runners[1].stealingStatus = 1;
                }
                if (inputs->controlStickAngle >= 0x5C0 && inputs->controlStickAngle <= 0xA40) {
                    g_Runners[2].stealingStatus = 1;
                }
                if (inputs->controlStickAngle >= 0x9C0 && inputs->controlStickAngle <= 0xE40) {
                    g_Runners[3].stealingStatus = 1;
                }
            }
        }
    }
}

// .text:0x0007E2BC size:0x7AC mapped:0x806BD350
void running_LiveBall_Human(void) {
    InputStruct* inputs = &g_Controls[g_GameLogic.teams[g_GameLogic.teamBatting]];
    InMemRunnerType* runner;
    InMemRunnerType* scan;
    u16 input;
    int desiredBase;
    int i;
    int extra;
    BOOL stopInput;
    BOOL foundOne;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_Practice.loadingGuidedPractice != 0) {
        return;
    }
    if (ACTIVE_TUTORIAL()) {
        inputs = &g_Practice.inputs[g_GameLogic.teamBatting];
    }
    input = inputs->buttonInput;
    if (g_Ball.framesSinceHit < 30) {
        input = inputs->newButtonInput;
    }

    if (inputs->controlStickAngle < 0) {
        stopInput = FALSE;
        runner = g_Runners;
        scan = runner;
        for (i = 0; i < 4; i++, scan++) {
            if (scan->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                if (scan->runningDirectionCode == 3) {
                    if (scan->nextDirectionBeingProcessed != 2 && scan->nextDirectionBeingProcessed != 1 &&
                        (inputs->newButtonInput & INPUT_BUTTON_Y)) {
                        stopInput = TRUE;
                        break;
                    }
                } else if (scan->runningDirectionCode == 1 && scan->currentBase != 0 &&
                           scan->nextDirectionBeingProcessed != 2 && scan->nextDirectionBeingProcessed != 3 &&
                           (inputs->newButtonInput & INPUT_BUTTON_X)) {
                    stopInput = TRUE;
                    break;
                }
            }
        }
        if (stopInput) {
            for (i = 0; i < 4; i++, runner++) {
                if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD && runner->rosterID >= 0) {
                    runner->runningDirectionDesired = 2;
                }
            }
        } else {
            for (i = 0; i < 4; i++, runner++) {
                if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                    if (runner->runningDirectionCode == 3) {
                        if (runner->nextDirectionBeingProcessed == 2 || runner->nextDirectionBeingProcessed == 1) {
                            if (input & INPUT_BUTTON_X) {
                                if (runner->rosterID >= 0) {
                                    runner->runningDirectionDesired = 3;
                                }
                            } else if ((inputs->newButtonInput & INPUT_BUTTON_Y) && runner->rosterID >= 0) {
                                runner->runningDirectionDesired = 1;
                            }
                        }
                    } else if (runner->runningDirectionCode == 1) {
                        if (runner->nextDirectionBeingProcessed == 2 || runner->nextDirectionBeingProcessed == 3) {
                            if (inputs->newButtonInput & INPUT_BUTTON_X) {
                                if (runner->rosterID >= 0) {
                                    runner->runningDirectionDesired = 3;
                                }
                            } else if ((input & INPUT_BUTTON_Y) && runner->rosterID >= 0) {
                                runner->runningDirectionDesired = 1;
                            }
                        }
                    } else if (runner->runningDirectionCode == 5 && (input & INPUT_BUTTON_Y)) {
                        if (runner->rosterID >= 0) {
                            runner->runningDirectionDesired = 1;
                        }
                    } else if (inputs->newButtonInput & INPUT_BUTTON_Y) {
                        if (runner->rosterID >= 0) {
                            runner->runningDirectionDesired = 1;
                        }
                    } else if (inputs->newButtonInput & INPUT_BUTTON_X) {
                        if (runner->rosterID >= 0) {
                            runner->runningDirectionDesired = 3;
                        }
                    }
                }
            }
        }
        if (inputs->newButtonInput & (INPUT_BUTTON_A | INPUT_BUTTON_B | INPUT_BUTTON_X | INPUT_BUTTON_Y)) {
            g_Runners[0].newButtonThisFrame_forMashPurposes = 1;
            g_Runners[1].newButtonThisFrame_forMashPurposes = 1;
            g_Runners[2].newButtonThisFrame_forMashPurposes = 1;
            g_Runners[3].newButtonThisFrame_forMashPurposes = 1;
        }
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE) {
            return;
        }
        if (g_Practice.instructionNumber < 0) {
            return;
        }
        if (g_Practice.practice_runner_countInputForMashing == 0) {
            return;
        }
        g_Runners[0].newButtonThisFrame_forMashPurposes = 1;
        g_Runners[1].newButtonThisFrame_forMashPurposes = 1;
        g_Runners[2].newButtonThisFrame_forMashPurposes = 1;
        g_Runners[3].newButtonThisFrame_forMashPurposes = 1;
        return;
    }
    if (input & INPUT_BUTTON_Y) {
        desiredBase = -1;
        if (inputs->controlStickAngle >= 0xA00 && inputs->controlStickAngle < 0xE00) {
            desiredBase = 0;
        } else if (inputs->controlStickAngle >= 0x600) {
            desiredBase = 3;
        } else if (inputs->controlStickAngle >= 0x200) {
            desiredBase = 2;
        }
        if (desiredBase < 0) {
            return;
        }
        foundOne = FALSE;
        for (i = 3; i >= 0; i--) {
            runner = &g_Runners[i];
            if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD && runner->nextBase == desiredBase) {
                if (foundOne) {
                    if ((s8)runner->_151 > 0) {
                        runner->_151++;
                    } else {
                        runner->_151 = 1;
                    }
                    runner->someCountdown_unused = lbl_3_data_4C54[5];
                    if ((s8)runner->_151 <= lbl_3_data_4C54[6]) {
                        return;
                    }
                }
                if (runner->runningDirectionCode == 1) {
                    if (runner->nextDirectionBeingProcessed == 2 || runner->nextDirectionBeingProcessed == 3) {
                        if (g_Runners[i].rosterID >= 0) {
                            g_Runners[i].runningDirectionDesired = 1;
                        }
                        return;
                    }
                    if (foundOne) {
                        return;
                    }
                    foundOne = TRUE;
                } else if (runner->runningDirectionCode == 3) {
                    if (runner->nextDirectionBeingProcessed == 2 || runner->nextDirectionBeingProcessed == 1) {
                        if (g_Runners[i].rosterID >= 0) {
                            g_Runners[i].runningDirectionDesired = 1;
                        }
                        return;
                    }
                    if (!(inputs->newButtonInput & INPUT_BUTTON_Y)) {
                        return;
                    }
                    if (g_Runners[i].rosterID >= 0) {
                        g_Runners[i].runningDirectionDesired = 2;
                    }
                    return;
                } else if (runner->runningDirectionCode == 5 && (input & INPUT_BUTTON_Y)) {
                    if (g_Runners[i].rosterID >= 0) {
                        g_Runners[i].runningDirectionDesired = 1;
                    }
                    return;
                } else {
                    if (!(inputs->newButtonInput & INPUT_BUTTON_Y)) {
                        return;
                    }
                    if (g_Runners[i].rosterID >= 0) {
                        g_Runners[i].runningDirectionDesired = 1;
                    }
                    return;
                }
            }
        }
        return;
    }
    if (!(input & INPUT_BUTTON_X)) {
        return;
    }
    desiredBase = -1;
    if (!(inputs->controlStickAngle >= 0xA00 && inputs->controlStickAngle < 0xE00)) {
        if (inputs->controlStickAngle >= 0x600) {
            desiredBase = 3;
        } else if (inputs->controlStickAngle >= 0x200) {
            desiredBase = 2;
        } else {
            desiredBase = 1;
        }
    }
    if (desiredBase < 0) {
        return;
    }
    extra = 0;
    for (i = 0; i < 4; i++) {
        runner = &g_Runners[i];
        if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD && runner->currentBase == desiredBase) {
            if (runner->runningDirectionCode == 1) {
                if (runner->nextDirectionBeingProcessed == 2 || runner->nextDirectionBeingProcessed == 3) {
                    if (g_Runners[i].rosterID >= 0) {
                        g_Runners[i].runningDirectionDesired = 3;
                    }
                    return;
                }
                if (!(inputs->newButtonInput & INPUT_BUTTON_X)) {
                    return;
                }
                if (g_Runners[i].rosterID >= 0) {
                    g_Runners[i].runningDirectionDesired = 2;
                }
                return;
            } else if (runner->runningDirectionCode == 3) {
                if (runner->nextDirectionBeingProcessed == 2 || runner->nextDirectionBeingProcessed == 1) {
                    if (g_Runners[i].rosterID >= 0) {
                        g_Runners[i].runningDirectionDesired = 3;
                    }
                    return;
                }
            } else if (inputs->newButtonInput & INPUT_BUTTON_X) {
                if (g_Runners[i].rosterID >= 0) {
                    g_Runners[i].runningDirectionDesired = 3;
                }
                return;
            }
            if (extra >= 2) {
                return;
            }
        }
    }
    return;
}

// .text:0x0007DD6C size:0x550 mapped:0x806BCE00
void cCSRunningFun(void) {
    int i;
    InMemRunnerType* runner;

    running_CheckForForceOuts_UpdateStamina_UpdateTagOutVars();
    runner = g_Runners;
    for (i = 0; i < 4; i++, runner++) {
        u8* stage;

        if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_NONE) {
            continue;
        }
        g_Minigame.runnerNum = i;
        if (runner->runningDirectionCode == 0) {
            runner->runningDirectionCode = 2;
        }
        stage = &g_Minigame._1B15[(s8)g_Minigame._18FC[i]];
        runner->turningAroundInd = 0;
        if (*stage == 4) {
            continue;
        }
        if (*stage == 1 || *stage == 2) {
            if (*stage == 2) {
                if (g_Minigame._1B19 == 0) {
                    *stage = 3;
                    runner->runningToDugoutFrameCounter = 0;
                }
            } else {
                if (runner->runningToDugoutFrameCounter < lbl_3_data_21904[1]) {
                    runner->position.x += runner->velocity.x;
                    runner->position.z += runner->velocity.z;
                } else {
                    *stage = 2;
                }
                if (runner->runningToDugoutFrameCounter < 0x7FFE) {
                    runner->runningToDugoutFrameCounter++;
                } else {
                    runner->runningToDugoutFrameCounter = 0x7FFF;
                }
            }
        } else if (*stage == 3) {
            VecXZ result;
            int start = 0;
            int count;

            if (runner->runningToDugoutFrameCounter <= 0) {
                f32 basesRan = runner->fractionalBasesRan;
                f32 percent = runner->percentTowardsNextBase;

                if (basesRan < 1.0f) {
                    count = 4;
                } else if (basesRan < 2.0f) {
                    start = 3;
                    count = 4;
                } else if (basesRan < 3.0f) {
                    start = 6;
                    count = 4;
                } else if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
                    start = 9;
                    count = 4;
                } else {
                    start = 9;
                    count = 3;
                }
                running_roundBasePosition(percent, &result,
                                          &lbl_3_data_4A54[g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT][start],
                                          count);
                runner->position.x = result.x;
                runner->position.z = result.z;
                runner->position.y = 0.0f;
                runner->velocity.x = 0.0f;
                runner->velocity.z = 0.0f;
            }
            if (runner->runningToDugoutFrameCounter < 0x7FFE) {
                runner->runningToDugoutFrameCounter++;
            } else {
                runner->runningToDugoutFrameCounter = 0x7FFF;
            }
            if (runner->runningToDugoutFrameCounter >= lbl_3_data_21904[2]) {
                g_Minigame._1B15[(s8)g_Minigame._18FC[i]] = 0;
            }
        } else {
            if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL && g_Minigame.turnOverStatus == 0) {
                runnerChangeDirectionHumanInput(i);
            }
            running_updateDistAndFramesToClosestBases(i);
                if (runner->runningToDugoutInd == 0 || runner->runningToDugoutStage == 0) {
                    if (runner->actionCode == 0) {
                        if ((runner->framesSinceLastDirectionChange >= lbl_3_data_4C54[3] ||
                             (runner->runningDirectionCode != RUNNER_MOVEMENT_FORWARDS && runner->runningDirectionCode != 3)) &&
                            runner->runningDirectionDesired != 0) {
                            if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
                                if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                                    runner->nextDirectionBeingProcessed = runner->runningDirectionDesired;
                                }
                            } else {
                                if ((i != 0 || runner->nextBase != 1) && runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                                    runner->nextDirectionBeingProcessed = runner->runningDirectionDesired;
                                }
                                if (runner->nextDirectionBeingProcessed == 3 && runner->tagUpInd != 3 &&
                                    runner->baseStandingOn >= 0) {
                                    runner->nextDirectionBeingProcessed = 0;
                                }
                            }
                        }
                        {
                            int dir = running_DirectionOverrides(i);
                            if (dir != 0) {
                                runner->nextDirectionBeingProcessed = dir;
                            }
                        }
                    }
                }
                if (runner->runningToDugoutInd != 0) {
                    runner->baseRoundingState = 0;
                    runner->actionCode = 0;
                } else {
                    running_roundBaseDecision(i);
                    running_triggerSlideOrBodyCheck(i);
                    if (g_GameLogic.secondaryGameMode != SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
                        if (i == 0 && runner->nextBase == 1) {
                            running_overrun1stIndicator();
                        } else if (runner->baseRoundingState == 1) {
                            runner->baseRoundingState = 0;
                        }
                        running_sendOutRunnerToDugout(i);
                    }
                }
                running_CalculateSpeedVariables(i);
                running_updatePositionTracking_storeRBIs_stopAtNextBase_displaySafe(i);
                running_updatePosition(i);
                running_updateDistAndFramesToClosestBases(i);
        }
    }
    running_CalcVeloAndIfBatterShouldStayStill();
    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
        running_chainChompSprintRelated();
    } else {
        running_checkForOuts();
        running_ForceOutStateRelated();
        fn_3_889FC();
        setRunnerAngle();
    }
    running_UpdateTrackingValues_BasesEarned();
}

// .text:0x0007DD24 size:0x48 mapped:0x806BCDB8
void fn_3_7DD24(int runnerIdx) {
    if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL && g_Minigame.turnOverStatus == 0) {
        runnerChangeDirectionHumanInput(runnerIdx);
    }
}

// .text:0x0007DB30 size:0x1F4 mapped:0x806BCBC4
void runnerChangeDirectionHumanInput(int runnerIdx) {
    InMemRunnerType* runner;
    InputStruct* inputs = &g_Controls[(s8)g_Minigame._18FC[runnerIdx]];

    runner = &g_Runners[runnerIdx];
    if (fn_3_107DF8(g_Minigame._18FC[runnerIdx])) {
        inputs = &g_Minigame._1D7C[(s8)g_Minigame._18FC[runnerIdx]];
    }

    if (runner->runningDirectionCode == 3) {
        if (runner->nextDirectionBeingProcessed == 2 || runner->nextDirectionBeingProcessed == 1) {
            if (inputs->newButtonInput & INPUT_BUTTON_X) {
                if (runner->rosterID >= 0) {
                    runner->runningDirectionDesired = 3;
                }
            } else if (inputs->newButtonInput & INPUT_BUTTON_Y) {
                if (runner->rosterID >= 0) {
                    runner->runningDirectionDesired = 1;
                }
            }
        } else if (inputs->newButtonInput & INPUT_BUTTON_Y) {
            if (runner->rosterID >= 0) {
                runner->runningDirectionDesired = 2;
            }
        }
    } else if (runner->runningDirectionCode == 1) {
        if (runner->nextDirectionBeingProcessed == 2 || runner->nextDirectionBeingProcessed == 3) {
            if (inputs->newButtonInput & INPUT_BUTTON_X) {
                if (runner->rosterID >= 0) {
                    runner->runningDirectionDesired = 3;
                }
            } else if (inputs->newButtonInput & INPUT_BUTTON_Y) {
                if (runner->rosterID >= 0) {
                    runner->runningDirectionDesired = 1;
                }
            }
        } else if (inputs->newButtonInput & INPUT_BUTTON_X) {
            if (runner->rosterID >= 0) {
                runner->runningDirectionDesired = 2;
            }
        }
    } else {
        if (inputs->buttonInput & INPUT_BUTTON_Y) {
            if (runner->rosterID >= 0) {
                runner->runningDirectionDesired = 1;
            }
        } else if (inputs->buttonInput & INPUT_BUTTON_X) {
            if (runner->rosterID >= 0) {
                runner->runningDirectionDesired = 3;
            }
        }
    }

    if (inputs->newButtonInput & (INPUT_BUTTON_A | INPUT_BUTTON_B | INPUT_BUTTON_X | INPUT_BUTTON_Y)) {
        runner->newButtonThisFrame_forMashPurposes = 1;
    }
}

// .text:0x0007D9DC size:0x154 mapped:0x806BCA70
void fn_3_7D9DC(int runnerIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];
    f32 magnitude = dolsqrtf2(g_Minigame._1AEC * g_Minigame._1AEC + g_Minigame._1AF4 * g_Minigame._1AF4);

    runner->velocity.x = lbl_3_data_218BC[7] * (g_Minigame._1AEC / magnitude);
    runner->velocity.z = lbl_3_data_218BC[7] * (g_Minigame._1AF4 / magnitude);
    runner->runningToDugoutFrameCounter = 0;
}

// .text:0x0007D920 size:0xBC mapped:0x806BC9B4
void fn_3_7D920(int runnerIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];
    int idx = (s8)g_Minigame._18FC[runnerIdx];

    if (g_Minigame._1B15[idx] == 2) {
        if (g_Minigame._1B19 != 0) {
            return;
        }
        g_Minigame._1B15[idx] = 3;
        runner->runningToDugoutFrameCounter = 0;
        return;
    }
    if (runner->runningToDugoutFrameCounter < lbl_3_data_21904[1]) {
        runner->position.x += runner->velocity.x;
        runner->position.z += runner->velocity.z;
    } else {
        g_Minigame._1B15[idx] = 2;
    }
    if (runner->runningToDugoutFrameCounter < 0x7FFE) {
        runner->runningToDugoutFrameCounter++;
    } else {
        runner->runningToDugoutFrameCounter = 0x7FFF;
    }
}

// .text:0x0007D79C size:0x184 mapped:0x806BC830
void fn_3_7D79C(int runnerIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];
    VecXZ result;
    int start;
    int count;

    if (runner->runningToDugoutFrameCounter <= 0) {
        f32 basesRan = runner->fractionalBasesRan;
        f32 percent = runner->percentTowardsNextBase;

        if (basesRan < 1.0f) {
            start = 0;
            count = 4;
        } else if (basesRan < 2.0f) {
            start = 3;
            count = 4;
        } else if (basesRan < 3.0f) {
            start = 6;
            count = 4;
        } else if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT) {
            start = 9;
            count = 4;
        } else {
            start = 9;
            count = 3;
        }

        running_roundBasePosition(percent, &result,
                                  &lbl_3_data_4A54[g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT][start],
                                  count);
        runner->position.x = result.x;
        runner->position.z = result.z;
        runner->position.y = 0.0f;
        runner->velocity.x = 0.0f;
        runner->velocity.z = 0.0f;
    }
    if (runner->runningToDugoutFrameCounter < 0x7FFE) {
        runner->runningToDugoutFrameCounter++;
    } else {
        runner->runningToDugoutFrameCounter = 0x7FFF;
    }
    if (runner->runningToDugoutFrameCounter >= lbl_3_data_21904[2]) {
        g_Minigame._1B15[(s8)g_Minigame._18FC[runnerIdx]] = 0;
    }
}
