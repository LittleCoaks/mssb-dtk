#include "game/ball/ball_trajectory.h"
#define REP_HEADER_DATA_FN getRepHeaderData_ballTrajectory
#include "header_rep_data.h"
#define SQRT2_LINKAGE static
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

extern u8 stadiumHitAngleCFOffsets[8];
extern const f32 lbl_3_rodata_1830;

#define BATTER_RUNNER_INDEX 3

// .text:0x0009CAF0 size:0x2A0 mapped:0x806DBB84
void categorizeBallTrajectory(void) {
    if (g_Ball.deadBallReason == DEAD_BALL_REASON_HOME_RUN) {
        if (g_Ball.homeRunInd == TRUE) {
            if (g_Ball.homeRunClassification == 1) {
                storedInningInfo.situation = 4;
                return;
            }
            if (g_Ball.Hit_VerticalAngle < 0x100) {
                storedInningInfo.situation = 8;
                return;
            }
            storedInningInfo.situation = 12;
            return;
        }

        if (g_Ball.ballAngleFromHome < 0x400 - stadiumHitAngleCFOffsets[g_d_GameSettings.StadiumID]) {
            if (g_Ball.homeRunClassification == 1) {
                storedInningInfo.situation = 3;
                return;
            }
            if (g_Ball.Hit_VerticalAngle < 0x100) {
                storedInningInfo.situation = 7;
                return;
            }
            storedInningInfo.situation = 11;
            return;
        }
        if (g_Ball.ballAngleFromHome > stadiumHitAngleCFOffsets[g_d_GameSettings.StadiumID] + 0x400) {
            if (g_Ball.homeRunClassification == 1) {
                storedInningInfo.situation = 1;
                return;
            }
            if (g_Ball.Hit_VerticalAngle < 0x100) {
                storedInningInfo.situation = 5;
                return;
            }
            storedInningInfo.situation = 9;
            return;
        }
        if (g_Ball.homeRunClassification == 1) {
            storedInningInfo.situation = 2;
            return;
        }
        if (g_Ball.Hit_VerticalAngle < 0x100) {
            storedInningInfo.situation = 6;
            return;
        }
        storedInningInfo.situation = 10;
        return;
    }

    if (g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_CAUGHT) {
        return;
    }
    if (g_Runners[BATTER_RUNNER_INDEX].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
        g_Ball.timeSinceBallPickedUp < 60 && g_Ball.framesSinceThrowStarted < 1 &&
        g_Runners[BATTER_RUNNER_INDEX].tagUpInd == TAG_UP_TYPE_NONE &&
        g_Runners[BATTER_RUNNER_INDEX].fractionalBasesRan >= lbl_3_rodata_1830) {
        storedInningInfo.situation = 14;
    }
    if (g_Runners[BATTER_RUNNER_INDEX].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY &&
        storedInningInfo.situation == 14 && g_Ball.framesSinceBallHitGroundOrWasCaught <= 240 &&
        g_Strikes.storedOuts < 2) {
        storedInningInfo.situation = 13;
        storedInningInfo.abResultFinal = 0x11;
    }
    if (storedInningInfo.situation == 14 &&
        (g_Runners[BATTER_RUNNER_INDEX].runningDirectionCode == 2 ||
         g_Runners[BATTER_RUNNER_INDEX].runningDirectionCode == 3)) {
        storedInningInfo.situation = 0;
    }
}

const f32 lbl_3_rodata_1830 = 3.15f;
