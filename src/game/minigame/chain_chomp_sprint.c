#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_chainChompSprint
#include "game/minigame/chain_chomp_sprint.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/math/game_math.h"
#include "game/sound/m_sound.h"
#include "game/match_setup/match_flow.h"
#include "game/match_setup/match_loading.h"
#include "game/match_setup/roster_init.h"
#include "game/baserunning/runner.h"
#include "game/ball/ball_physics.h"
#include "game/batting/at_bat_results.h"
#include "game/minigame/kinoko.h"
#include "game/stadium/sta_c2.h"
#include "game/stadium/stadium_framework.h"
#include "Unknown/File_0x8004c094.h"
#include "Unknown/File_0x800204cc.h"
#include "Unknown/File_0x800348c8.h"
#include "Unknown/File_0x80034220.h"
#include "Unknown/File_0x8003452c.h"
#include "Unknown/sub.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/stl.h"
#include "stl/stdlib.h"
#include "stl/math.h"
#include "musyx/musyx.h"

typedef struct {
    u8 count;
    u8 points;
} CCSGemType;

typedef struct {
    f32 dist;
    u8 direction;
    s8 pos;
} CCSAITarget;

extern BOOL checkForPauses(void);
extern void fn_80011578(void);
extern void fn_800115C8(u8 player);
extern void minigameQueueHudEvent(int a, int b);
extern void fn_3_106EB0(void);
extern void fn_3_DE4FC(void);
extern void fn_3_11F480(void);
extern void fn_3_14C904(void);
extern void fn_3_151798(void);
extern void fn_3_152AB4(u8 coin, u8 runner);
extern void fn_3_1541C4(u8 coin, u8 type, VecXYZ* pos);
extern void fn_3_157DB8(int frames);
extern void fn_3_1578F8(void);
extern void starMissionsMinigamesSpecialAction(int missionType, int points, int barrelsHit);

extern u8 lbl_800EFBA4[];
extern s16 lbl_3_common_bss_37400[];
extern u16 lbl_3_data_81FC[];
extern u8 minigameIntroFrames[2];
extern u8 minigameAIStrengthTable[][5];
extern VecXYZ ccs_chompStartPos;
extern s16 ccs_chompJumpRollWeights[][9];
extern u8 lbl_3_data_21860[][4];
extern u8 ccs_timeLimitSeconds[];
extern u8 ccs_itemWeightsByPhase[][2];
extern CCSGemType ccs_itemGemCounts[];
extern f32 ccs_coinPhysicsConsts[];
extern s16 ccs_coinLifetimeFrames;
extern u8 ccs_chompTargetThresholds[][3];
extern f32 lbl_3_data_218BC[];
extern s16 lbl_3_data_21904[];
extern s16 ccs_powerupTimers[];
extern s8 ccsAI_bPressDelayRanges[][2];
extern f32 ccsAI_targetDistThresholds[];
extern s8 lbl_3_data_21944[][2];
extern s16 lbl_3_data_2194C[][2];
extern s16 lbl_3_data_2195C[][2];
extern s8 lbl_3_data_2196C[][2];
extern s8 lbl_3_data_21974[][2];
extern s8 lbl_3_data_2197C[];
extern s8 lbl_3_data_21980[];

s32 lbl_3_data_265F0 = -1;

static s32 lbl_3_bss_B798;
static f32 lbl_3_bss_B794;
static u8 lbl_3_bss_B791;

static inline f32 ccsBasePathGap(f32 a, f32 b) {
    f32 d = a - b;
    if (d < 0.0f) {
        d += 4.0f;
    }
    if (d > 2.0f) {
        d = 4.0f - d;
    }
    return d;
}

// .text:0x00141A30 size:0x214 mapped:0x80780AC4
void chainChompSprintSwitcher(void) {
    switch (g_GameLogic.gameStatus) {
    case GAME_STATUS_LOAD_GAME:
        chainChompSprintRelated();
        break;
    case GAME_STATUS_TRANSITION_MINIGAME_TO_BATTING:
        fn_3_1413E4();
        break;
    case GAME_STATUS_DEFAULT:
        fn_3_1412BC();
        break;
    case GAME_STATUS_LIVE_BALL:
        chainChompSpringMainFun();
        break;
    case GAME_STATUS_TRANSITION_MINIGAME_POSTGAME:
        mVPRelated();
        break;
    }
}

// .text:0x00141A2C size:0x4 mapped:0x80780AC0
void fn_3_141A2C(void) {
}

// .text:0x001414AC size:0x580 mapped:0x80780540
void chainChompSprintRelated(void) {
    int order[4];
    int runnerIdx;
    int i;
    s32 k;

    if (g_GameLogic._125 == 0) {
        initializeSomethingDuringTransition();
        g_GameLogic.secondaryGameMode = SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT;
        g_Minigame.minigameElapsedFrames = 0;
        g_Minigame.ccs_timePhase = 0;
        g_Minigame.turnOverStatus = 0;
        g_Minigame.winLossResult = 0;
        for (i = 0; i < 4; i++) {
            g_Minigame.miniGameCurrentPoints[i] = 0;
            g_Minigame.miniGameLatestPoints[i] = 0;
            g_Minigame.minigamePoints_current_Latest[i][0] = 0;
            g_Minigame.minigamePoints_current_Latest[i][1] = 0;
            g_Minigame.playerSlots.participantSlot[i] = -1;
            g_Minigame.playerSlots.fielderIndex[i] = -1;
            g_Minigame.playerSlots.runnerPlayerIndex[i] = -1;
            g_Minigame.playerSlots.playerRunnerIndex[i] = -1;
            g_Minigame.playerSlots.batterInd[i] = 1;
        }
        g_Minigame.pointsReqToWin_challenge = 0;
        *(s8*)&g_Minigame.minigamePlayerSelectedOrder = -1;
        g_Minigame.rosterID = -1;
        if (!g_Minigame.multiPlayerInd) {
            u8 strength;
            g_Minigame.minigameFramesRemaining = ccs_timeLimitSeconds[g_Minigame.soloMinigameDifficulty] * 60;
            strength = minigameAIStrengthTable[g_Minigame.GameMode_MiniGame][g_Minigame.soloMinigameDifficulty];
            for (i = 0; i < 4; i++) {
                g_Minigame.playerSlots.aiStrength[i] = strength;
            }
        } else {
            if (g_Minigame.grandPrixInd) {
                u8 strength = minigameAIStrengthTable[7][0];
                for (i = 0; i < 4; i++) {
                    g_Minigame.playerSlots.aiStrength[i] = strength;
                }
            }
            g_Minigame.minigameFramesRemaining = ccs_timeLimitSeconds[4] * 60;
        }
        setDefaultInMemRunner();
        runnerIdx = 0;
        for (i = 0; i < 4; i++) {
            if (g_Minigame.playerSlots.characterIndex[i] >= 0) {
                g_Minigame.playerSlots.runnerPlayerIndex[runnerIdx] = i;
                g_Minigame.playerSlots.playerRunnerIndex[i] = runnerIdx;
                g_Minigame.ccs.runFrames[runnerIdx] = 0;
                g_Minigame.miniGameCurrentPoints[runnerIdx] = 0;
                g_Minigame.ccs.runnerChompHitState[i] = 0;
                g_Runners[runnerIdx].miniGamePlayerNum = i;
                order[i] = runnerIdx;
                initializeInMemRunner(i, runnerIdx);
                g_Runners[runnerIdx].runnerOnFieldOrOutOrScored = 1;
                if (!g_Minigame.playerSlots.aiControlledInd[i]) {
                    g_Runners[runnerIdx].unused_batterHandednessForCCS = 0;
                } else {
                    g_Runners[runnerIdx].unused_batterHandednessForCCS = 1;
                }
                g_Runners[runnerIdx].leadOffStatus = 0;
                runnerIdx++;
            }
        }
        if (g_Minigame.multiPlayerInd) {
            shuffleIntArray(order, g_Minigame.miniGameNumberOfParticipants, FALSE);
            for (i = 0; i < 4; i++) {
                if (g_Minigame.playerSlots.runnerPlayerIndex[i] >= 0) {
                    fn_3_810C4(i, lbl_3_data_21860[4][order[i]]);
                }
            }
        } else {
            for (i = 0; i < 4; i++) {
                if (g_Minigame.playerSlots.runnerPlayerIndex[i] >= 0) {
                    fn_3_810C4(i, lbl_3_data_21860[g_Minigame.soloMinigameDifficulty][i]);
                }
            }
        }
        minigamesSetSomePointers();
        minigamesGXStuff();
        minigamesSetSomePointers2();
        g_Minigame.ccs.chompYaw = 0;
        g_Minigame.ccs.chompState = 0;
        g_Minigame.ccs.chompPos.x = ccs_chompStartPos.x;
        g_Minigame.ccs.chompPos.y = ccs_chompStartPos.y;
        g_Minigame.ccs.chompPos.z = ccs_chompStartPos.z;
        g_Minigame.ccs.chompVelocity.x = 0.0f;
        g_Minigame.ccs.chompVelocity.y = 0.0f;
        g_Minigame.ccs.chompVelocity.z = 0.0f;
        g_Minigame.ccs.chompStateTimer = 0;
        g_Minigame.ccs.chompYaw = 0xE00;
        maybeChainChompSprintCTRLRelated();
        g_Ball.AtBat_Contact_BallPos.z = 0.0f;
        g_Ball.AtBat_Contact_BallPos.y = 0.0f;
        g_Ball.AtBat_Contact_BallPos.x = 0.0f;
        lbl_3_bss_B791 = 0;
        lbl_3_data_265F0 = -1;
        for (k = 0; k < 100; k++) {
            g_Minigame.coinState[k] = 0;
            g_Minigame.coinFrameCounter[k] = 0;
        }
        for (i = 0; i < 6; i++) {
            g_Minigame.ccs.itemState[i] = 0;
            g_Minigame.ccs.itemTimer[i] = 0;
        }
        for (i = 0; i < 4; i++) {
            g_Minigame.ccs.segmentItems[i][0] = -1;
            g_Minigame.ccs.segmentItems[i][1] = -1;
        }
        g_Minigame.ccs.specialItemCount = 0;
        g_Minigame.ccsSpecialItemFrames[0] = RandomInt_Game_Range(lbl_3_data_21904[5], lbl_3_data_21904[6]) * 60;
        g_Minigame.ccsSpecialItemFrames[1] = RandomInt_Game_Range(lbl_3_data_21904[7], lbl_3_data_21904[8]) * 60;
        setDefaultInMemBall();
        g_Minigame.powerup.activeInd = FALSE;
        g_Minigame.powerup.timer = ccs_powerupTimers[0];
        g_Minigame.playerIDWithPowerup[0] = -1;
        fn_3_169600();
        g_GameLogic._125++;
    } else {
        SetGameStatus(GAME_STATUS_GAME_START_MOVIE);
    }
}

// .text:0x001413E4 size:0xC8 mapped:0x80780478
void fn_3_1413E4(void) {
    cCSRunningFun();
    switch (g_GameLogic._125) {
    case 0:
        minigameQueueHudEvent(2, minigameIntroFrames[0]);
        changeScene(1, 6);
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125 = 1;
        break;
    case 1:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > minigameIntroFrames[0] + minigameIntroFrames[1]) {
            g_GameLogic._125 = 2;
        }
        break;
    case 2:
        SetGameStatus(GAME_STATUS_DEFAULT);
        break;
    }
}

// .text:0x001412BC size:0x128 mapped:0x80780350
void fn_3_1412BC(void) {
    fn_3_13DEA4();
    changeScene(1, 6);
    SetGameStatus(GAME_STATUS_LIVE_BALL);
}

// .text:0x001410F0 size:0x1CC mapped:0x80780184
void mVPRelated(void) {
    u32 k;

    fn_3_DE4FC();
    SetGameStatus(GAME_STATUS_MVP_END_GAME);
    g_Minigame.ccs.chompYaw = 0;
    g_Minigame.ccs.chompState = 0;
    g_Minigame.ccs.chompPos.x = ccs_chompStartPos.x;
    g_Minigame.ccs.chompPos.y = ccs_chompStartPos.y;
    g_Minigame.ccs.chompPos.z = ccs_chompStartPos.z;
    g_Minigame.ccs.chompVelocity.x = 0.0f;
    g_Minigame.ccs.chompVelocity.y = 0.0f;
    g_Minigame.ccs.chompVelocity.z = 0.0f;
    g_Minigame.ccs.chompStateTimer = 0;
    g_Minigame.ccs.chompYaw = 0xE00;
    for (k = 0; k < 100; k++) {
        g_Minigame.coinState[k] = 0;
        g_Minigame.coinFrameCounter[k] = 0;
    }
    for (k = 0; k < 6; k++) {
        g_Minigame.ccs.itemState[k] = 0;
        g_Minigame.ccs.itemTimer[k] = 0;
    }
    for (k = 0; k < 4; k++) {
        g_Minigame.ccs.segmentItems[k][0] = -1;
        g_Minigame.ccs.segmentItems[k][1] = -1;
    }
    g_Minigame.ccs.specialItemCount = 0;
    g_Minigame.powerup.activeInd = FALSE;
    fn_80011578();
    SetGameStatus(GAME_STATUS_MVP_END_GAME);
}

// .text:0x00140CE0 size:0x410 mapped:0x8077FD74
void chainChompSpringMainFun(void) {
    if (checkForPauses()) {
        return;
    }
    if (lbl_3_bss_B791) {
        lbl_3_bss_B791 = 0;
    }
    if (!g_Minigame.turnOverStatus) {
        if (++g_Minigame.minigameElapsedFrames >= 3600) {
            g_Minigame.ccs_timePhase = 2;
        } else if (g_Minigame.minigameElapsedFrames >= 1800) {
            g_Minigame.ccs_timePhase = 1;
        }
    }
    if (g_Minigame.minigameFramesRemaining != 0 && --g_Minigame.minigameFramesRemaining < 600 &&
        g_Minigame.minigameFramesRemaining != 0 && g_Minigame.minigameFramesRemaining % 60 == 0) {
        callSfx(lbl_3_data_81FC[40]);
    }
    fn_3_13C7BC();
    cCSRunningFun();
    fn_3_13C790();
    fn_3_13F7E4();
    fn_3_13F6C8();
    fn_3_1406F4();
    fn_3_13E670();
    fn_3_140BCC();
}

// .text:0x00140BCC size:0x114 mapped:0x8077FC60
void fn_3_140BCC(void) {
    if (!g_Minigame.turnOverStatus) {
        if (g_Minigame.minigameFramesRemaining == 0) {
            minigameQueueHudEvent(3, 0);
            sndFXStartEx(0x1BE, lbl_800EFBA4[7], 0x3F, 0);
            fn_3_151798();
            fn_3_11F480();
            fn_80011578();
            g_Minigame.powerup.activeInd = FALSE;
            g_Minigame.turnOverStatus = 1;
        }
    } else {
        if (g_Minigame.turnOverStatus == 1) {
            g_Minigame.turnOverStatus = 2;
            g_GameLogic.CountdownUntilFade = lbl_3_data_21904[0];
        }
        if (g_Minigame.ccs.chompState != 3) {
            g_GameLogic.CountdownUntilFade--;
        }
        if (g_GameLogic.CountdownUntilFade == 7) {
            changeScene(3, 6);
            fn_3_1578F8();
        }
        if (g_GameLogic.CountdownUntilFade <= 0) {
            fn_3_1409AC();
        }
    }
}

// .text:0x001409AC size:0x220 mapped:0x8077FA40
void fn_3_1409AC(void) {
    u32 k;

    fn_3_DE4FC();
    if (g_Minigame.soloMinigameDifficulty <= MINIGAME_DIFFICULTY_MULTIPLAYER_CHALLENGE_HARD && !g_Minigame.multiPlayerInd) {
        if (g_Minigame.playerSlots.rank[g_Minigame.soloPlayerSlot] == 1 &&
            !g_Minigame.challenge_minigame_haven_tWonYetIndicator) {
            g_Minigame.winLossResult = 1;
        } else {
            g_Minigame.winLossResult = 2;
        }
    }
    SetGameStatus(GAME_STATUS_MVP_END_GAME);
    g_Minigame.ccs.chompYaw = 0;
    g_Minigame.ccs.chompState = 0;
    g_Minigame.ccs.chompPos.x = ccs_chompStartPos.x;
    g_Minigame.ccs.chompPos.y = ccs_chompStartPos.y;
    g_Minigame.ccs.chompPos.z = ccs_chompStartPos.z;
    g_Minigame.ccs.chompVelocity.x = 0.0f;
    g_Minigame.ccs.chompVelocity.y = 0.0f;
    g_Minigame.ccs.chompVelocity.z = 0.0f;
    g_Minigame.ccs.chompStateTimer = 0;
    g_Minigame.ccs.chompYaw = 0xE00;
    for (k = 0; k < 100; k++) {
        g_Minigame.coinState[k] = 0;
        g_Minigame.coinFrameCounter[k] = 0;
    }
    for (k = 0; k < 6; k++) {
        g_Minigame.ccs.itemState[k] = 0;
        g_Minigame.ccs.itemTimer[k] = 0;
    }
    for (k = 0; k < 4; k++) {
        g_Minigame.ccs.segmentItems[k][0] = -1;
        g_Minigame.ccs.segmentItems[k][1] = -1;
    }
    g_Minigame.ccs.specialItemCount = 0;
    g_Minigame.powerup.activeInd = FALSE;
}

// .text:0x001406F4 size:0x2B8 mapped:0x8077F788
void fn_3_1406F4(void) {
    if (g_Minigame.ccs.chompStateTimer < 0x7FFE) {
        g_Minigame.ccs.chompStateTimer++;
    } else {
        g_Minigame.ccs.chompStateTimer = 0x7FFF;
    }
    switch (g_Minigame.ccs.chompState) {
    case 0:
        fn_3_1405D8();
        break;
    case 1:
        fn_3_140484();
        break;
    case 2:
        fn_3_140284();
        break;
    case 3:
        fn_3_13FC24();
        break;
    case 4:
        fn_3_13F8C4();
        break;
    }
}

// .text:0x001405D8 size:0x11C mapped:0x8077F66C
void fn_3_1405D8(void) {
    if (g_Minigame.ccs.chompStateTimer <= 1) {
        u8 row;
        s16 roll;
        if (!g_Minigame.multiPlayerInd) {
            row = g_Minigame.soloMinigameDifficulty;
        } else {
            row = 4;
        }
        roll = RandomInt_Game_Range(0, 1000);
        g_Minigame.ccs._26 = 0;
        do {
            roll -= ccs_chompJumpRollWeights[row][g_Minigame.ccs._26++];
            if (roll <= 0) {
                break;
            }
        } while (ccs_chompJumpRollWeights[row][g_Minigame.ccs._26] >= 0);
        g_Minigame.ccs._26 *= 120;
        g_Minigame.ccs._26 -= 48;
        fn_3_157DB8(g_Minigame.ccs._26);
    } else {
        g_Minigame.ccs.chompYaw = 0xE00;
        if (g_Minigame.ccs.chompStateTimer >= g_Minigame.ccs._26) {
            g_Minigame.ccs.chompState = 1;
            g_Minigame.ccs.chompStateTimer = 0;
            g_Minigame.ccs.chompVelocity.y = lbl_3_data_218BC[3];
            fn_3_14C904();
            callSfx(0x2E0);
        }
    }
}

// .text:0x00140484 size:0x154 mapped:0x8077F518
void fn_3_140484(void) {
    int i;

    if (g_Minigame.turnOverStatus) {
        return;
    }
    g_Minigame.ccs.chompPos.y += g_Minigame.ccs.chompVelocity.y;
    if (g_Minigame.ccs.chompPos.y <= 0.0f && g_Minigame.ccs.chompVelocity.y < -lbl_3_data_218BC[6]) {
        g_Minigame.ccs.chompVelocity.y = 0.0f;
        g_Minigame.ccs.chompPos.y = 0.0f;
        spawnDust((Vec*)&g_Minigame.ccs.chompPos);
        callSfx(0x2DF);
        fn_3_13E174(0);
        for (i = 0; i < 4; i++) {
            setCharacterAnimations(i, 1);
        }
    } else if (g_Minigame.ccs.chompPos.y > 0.0f) {
        g_Minigame.ccs.chompVelocity.y -= lbl_3_data_218BC[6];
    }
    if (g_Minigame.ccs.chompStateTimer >= lbl_3_data_21904[9]) {
        g_Minigame.ccs.chompState = 2;
        g_Minigame.ccs.chompStateTimer = 0;
        g_Minigame.ccs.chompVelocity.y = lbl_3_data_218BC[4];
    }
}

// .text:0x00140284 size:0x200 mapped:0x8077F318
void fn_3_140284(void) {
    int target;
    int best;
    int threshold;
    int i;

    g_Minigame.ccs_targetHudPending = 1;
    for (i = 0; i < 4; i++) {
        g_Minigame.ccs.targetInd[i] = -1;
    }
    best = 0;
    target = -1;
    g_Minigame.ccs.targetCount = 0;
    if (!g_Minigame.multiPlayerInd) {
        threshold = ccs_chompTargetThresholds[g_Minigame.soloMinigameDifficulty][g_Minigame.ccs_timePhase];
    } else {
        threshold = ccs_chompTargetThresholds[4][g_Minigame.ccs_timePhase];
    }
    for (i = 0; i < 4; i++) {
        if (g_Minigame.playerSlots.playerRunnerIndex[i] >= 0 && g_Minigame.ccs.runFrames[i] > best) {
            best = g_Minigame.ccs.runFrames[i];
            target = i;
        }
    }
    if (target >= 0 && best * 100 / 60 <= threshold) {
        target = -1;
    }
    if (target < 0) {
        g_Minigame.ccs.chompState = 0;
        g_Minigame.ccs.chompStateTimer = 0;
        return;
    }
    g_Minigame.ccs.targetInd[target] = 1;
    g_Minigame.ccs.targetCount = 1;
    for (i = target + 1; i < 4; i++) {
        if (g_Minigame.playerSlots.playerRunnerIndex[i] >= 0 && g_Minigame.ccs.runFrames[target] == g_Minigame.ccs.runFrames[i]) {
            g_Minigame.ccs.targetInd[i] = 1;
            g_Minigame.ccs.targetCount++;
        }
    }
    g_Minigame.ccs._1C = 0;
    g_Minigame.ccs.chompState = 3;
    g_Minigame.ccs.chompStateTimer = 0;
}

// .text:0x0013FC24 size:0x660 mapped:0x8077ECB8
void fn_3_13FC24(void) {
    int i;
    f32 dist;
    f32 dz;
    f32 dx;
    InMemRunnerType* runner;

    if (g_Minigame.ccs._1C < 1) {
        for (i = 0; i < 4; i++) {
            if (g_Minigame.ccs.targetInd[i] == 1) {
                InMemRunnerType* target = &g_Runners[g_Minigame.playerSlots.playerRunnerIndex[i]];
                f32 moveX = target->position.x - target->positionStored.x;
                f32 moveZ = target->position.z - target->positionStored.z;
                if (fabsf(moveX) > 0.01 || fabsf(moveZ) > 0.01) {
                    return;
                }
            }
        }
    }
    if (++g_Minigame.ccs._1C <= 1) {
        for (i = 0; i < 4; i++) {
            if (g_Minigame.ccs.targetInd[i] == 1) {
                g_Minigame.ccs.chasedPlayer = i;
                g_Minigame.ccs.targetInd[i] = 0;
                break;
            }
        }
        runner = &g_Runners[g_Minigame.playerSlots.playerRunnerIndex[i]];
        dx = runner->position.x - g_Minigame.ccs.chompPos.x;
        dz = runner->position.z - g_Minigame.ccs.chompPos.z;
        dist = dolsqrtf2(dx * dx + dz * dz);
        g_Minigame.ccs.chompYaw = calculateAngleFromCoordinates(dx, dz);
        if (dist < lbl_3_data_218BC[0]) {
            g_Minigame.ccs.chompVelocity.x = dx;
            g_Minigame.ccs.chompVelocity.z = dz;
            goto hit;
        }
        g_Minigame.ccs.chompVelocity.x = dx * (lbl_3_data_218BC[1] / dist);
        g_Minigame.ccs.chompVelocity.z = dz * (lbl_3_data_218BC[1] / dist);
    }
    runner = &g_Runners[g_Minigame.playerSlots.playerRunnerIndex[g_Minigame.ccs.chasedPlayer]];
    g_Minigame.ccs.chompPos.x += g_Minigame.ccs.chompVelocity.x;
    g_Minigame.ccs.chompPos.y += g_Minigame.ccs.chompVelocity.y;
    g_Minigame.ccs.chompPos.z += g_Minigame.ccs.chompVelocity.z;
    if (g_Minigame.ccs.chompPos.y <= 0.0f) {
        g_Minigame.ccs.chompPos.y = 0.0f;
        g_Minigame.ccs.chompVelocity.y = lbl_3_data_218BC[4];
        spawnDust((Vec*)&g_Minigame.ccs.chompPos);
        callSfx(0x2DF);
    } else {
        f32 vy = g_Minigame.ccs.chompVelocity.y;
        g_Minigame.ccs.chompVelocity.y = vy - lbl_3_data_218BC[6];
        if (vy > 0.0f && g_Minigame.ccs.chompVelocity.y <= 0.0f) {
            callSfx(0x2DE);
        }
    }
    dz = runner->position.z - g_Minigame.ccs.chompPos.z;
    dx = runner->position.x - g_Minigame.ccs.chompPos.x;
    dist = dolsqrtf2(dx * dx + dz * dz);
    if (!(dist < lbl_3_data_218BC[0])) {
        return;
    }
hit:
    fn_3_13E174(1);
    g_Minigame.ccs.runnerChompHitState[g_Minigame.ccs.chasedPlayer] = 1;
    fn_3_7D9DC(g_Minigame.playerSlots.playerRunnerIndex[g_Minigame.ccs.chasedPlayer]);
    fn_3_13E7D4(g_Minigame.ccs.chasedPlayer);
    if (g_Minigame.playerIDWithPowerup[0] == g_Minigame.ccs.chasedPlayer) {
        fn_800115C8(g_Minigame.playerIDWithPowerup[0]);
        g_Minigame.playerIDWithPowerup[0] = -1;
    }
    g_Minigame.miniGameCurrentPoints[g_Minigame.ccs.chasedPlayer] /= 2;
    g_Minigame.ccs_biteHudPending[g_Minigame.ccs.chasedPlayer] = 1;
    setCharacterAnimations(g_Minigame.ccs.chasedPlayer, 2);
    if (--g_Minigame.ccs.targetCount == 0) {
        g_Minigame.ccs.chompState = 4;
        g_Minigame.ccs.chompStateTimer = 0;
        g_Minigame.ccs.chasedPlayer = -1;
        g_Minigame.ccs.chompVelocity.y = lbl_3_data_218BC[5];
    } else {
        g_Minigame.ccs._1C = 0;
    }
}

// .text:0x0013F8C4 size:0x360 mapped:0x8077E958
void fn_3_13F8C4(void) {
    f32 dx;
    f32 dz;
    f32 dist;

    if (g_Minigame.ccs.chompStateTimer <= 1) {
        dz = ccs_chompStartPos.z - g_Minigame.ccs.chompPos.z;
        dx = ccs_chompStartPos.x - g_Minigame.ccs.chompPos.x;
        dist = dolsqrtf2(dx * dx + dz * dz);
        g_Minigame.ccs.chompVelocity.x = dx * (lbl_3_data_218BC[2] / dist);
        g_Minigame.ccs.chompVelocity.z = dz * (lbl_3_data_218BC[2] / dist);
        g_Minigame.ccs.chompYaw = calculateAngleFromCoordinates(dx, dz);
    }
    dx = ccs_chompStartPos.x - g_Minigame.ccs.chompPos.x;
    dz = ccs_chompStartPos.z - g_Minigame.ccs.chompPos.z;
    dist = dolsqrtf2(dx * dx + dz * dz);
    if (dist <= lbl_3_data_218BC[2]) {
        g_Minigame.ccs.chompPos.x = ccs_chompStartPos.x;
        g_Minigame.ccs.chompPos.y = ccs_chompStartPos.y;
        g_Minigame.ccs.chompPos.z = ccs_chompStartPos.z;
        g_Minigame.ccs.chompState = 0;
        g_Minigame.ccs.chompStateTimer = 0;
    } else {
        g_Minigame.ccs.chompPos.x += g_Minigame.ccs.chompVelocity.x;
        g_Minigame.ccs.chompPos.y += g_Minigame.ccs.chompVelocity.y;
        g_Minigame.ccs.chompPos.z += g_Minigame.ccs.chompVelocity.z;
        if (g_Minigame.ccs.chompPos.y <= 0.0f) {
            g_Minigame.ccs.chompPos.y = 0.0f;
            g_Minigame.ccs.chompVelocity.y = lbl_3_data_218BC[5];
            spawnDust((Vec*)&g_Minigame.ccs.chompPos);
            callSfx(0x2DF);
        } else {
            g_Minigame.ccs.chompVelocity.y -= lbl_3_data_218BC[6];
        }
    }
}

// .text:0x0013F7E4 size:0xE0 mapped:0x8077E878
void fn_3_13F7E4(void) {
    int i;

    if (g_Minigame.ccs.chompState != 1) {
        return;
    }
    if (g_Minigame.ccs.chompStateTimer <= 0) {
        for (i = 0; i < 4; i++) {
            g_Minigame.ccs.runFrames[i] = 0;
        }
    }
    for (i = 0; i < 4; i++) {
        if (g_Minigame.playerSlots.playerRunnerIndex[i] >= 0) {
            InMemRunnerType* runner = &g_Runners[g_Minigame.playerSlots.playerRunnerIndex[i]];
            if (runner->runningDirectionCode == 1 || runner->runningDirectionCode == 3) {
                g_Minigame.ccs.runFrames[i]++;
            }
        }
    }
}

// .text:0x0013F6C8 size:0x11C mapped:0x8077E75C
void fn_3_13F6C8(void) {
    if (g_Minigame.turnOverStatus) {
        return;
    }
    fn_3_13F484();
    chainChompSpringPoints();
    fn_3_13E6D4();
}

// .text:0x0013F484 size:0x244 mapped:0x8077E518
void fn_3_13F484(void) {
    int item;
    u8 state;
    int i;

    for (item = 0; item < 6; item++) {
        state = g_Minigame.ccs.itemState[item];
        if (state == 1) {
            g_Minigame.ccs.itemTimer[item]--;
            if (g_Minigame.ccs.itemTimer[item] <= 0) {
                g_Minigame.ccs.itemState[item] = 0;
            }
        } else if (state == 0) {
            fn_3_13EC44(item);
        } else {
            int collectedState = item + 101;
            int collected = 0;
            for (i = 0; i < 15; i++) {
                if (g_Minigame.coinState[i] == collectedState) {
                    collected++;
                }
            }
            if (collected >= ccs_itemGemCounts[state - 2].count) {
                for (i = 0; i < 15; i++) {
                    if (g_Minigame.coinState[i] == collectedState) {
                        g_Minigame.coinState[i] = 0;
                    }
                }
                g_Minigame.ccs.itemState[item] = 1;
                for (i = 0; i < 4; i++) {
                    if (g_Minigame.ccs.segmentItems[i][0] == item) {
                        g_Minigame.ccs.segmentItems[i][0] = -1;
                        break;
                    }
                    if (g_Minigame.ccs.segmentItems[i][1] == item) {
                        g_Minigame.ccs.segmentItems[i][1] = -1;
                        break;
                    }
                }
                g_Minigame.ccs.itemTimer[item] = RandomInt_Game_Range(lbl_3_data_21904[3], lbl_3_data_21904[4]);
            }
        }
    }
}

// .text:0x0013EC44 size:0x840 mapped:0x8077DCD8
void fn_3_13EC44(int item) {
    int i;
    int gem;
    int pos;
    int count;
    int seg;
    int coin;
    int gemCount;
    u8* state;
    int baseCount;
    int runnersOnSeg[4];
    int list[4];
    int powerupOnSeg[4];
    int* next;

    for (i = 0; i < 6; i++) {
        if (g_Minigame.ccs.itemState[i] == 3) {
            break;
        }
    }
    if (g_Minigame.ccs.specialItemCount < 2 &&
        g_Minigame.minigameElapsedFrames > g_Minigame.ccsSpecialItemFrames[g_Minigame.ccs.specialItemCount]) {
        g_Minigame.ccs.itemState[item] = 4;
        gemCount = ccs_itemGemCounts[2].count;
        g_Minigame.ccs.specialItemCount++;
    } else if (i < 6) {
        gemCount = ccs_itemGemCounts[0].count;
        g_Minigame.ccs.itemState[item] = 2;
    } else {
        int phase;
        int k;
        if (g_Minigame.minigameElapsedFrames < 1800) {
            phase = 0;
        } else if (g_Minigame.minigameElapsedFrames < 3600) {
            phase = 1;
        } else {
            phase = 2;
        }
        k = RandomIndexFromWeights(ccs_itemWeightsByPhase[phase], 2);
        g_Minigame.ccs.itemState[item] = k + 2;
        gemCount = ccs_itemGemCounts[k].count;
    }
    state = &g_Minigame.ccs.itemState[item];
    baseCount = ccs_itemGemCounts[0].count;
    while (TRUE) {
        count = 0;
        if (*state == 4) {
            for (i = 0; i < 4; i++) {
                runnersOnSeg[i] = 0;
                powerupOnSeg[i] = 0;
            }
            for (i = 0; i < 4; i++) {
                if (g_Minigame.playerSlots.runnerPlayerIndex[i] >= 0) {
                    InMemRunnerType* runner = &g_Runners[i];
                    if (runner->runningDirectionCode == 1) {
                        runnersOnSeg[runner->nextBase & 3]++;
                    } else if (runner->runningDirectionCode == 3) {
                        runnersOnSeg[runner->currentBase]++;
                    } else if (runner->percentTowardsNextBase < 0.5f) {
                        runnersOnSeg[runner->currentBase]++;
                    } else {
                        runnersOnSeg[runner->currentBase]++;
                    }
                }
            }
            if (g_Minigame.powerup.activeInd) {
                s8 k = (int)g_Minigame.powerup.basePathPos;
                runnersOnSeg[k]++;
                powerupOnSeg[k]++;
            }
            next = list;
            for (i = 0; i < 4; i++) {
                if (runnersOnSeg[i] == 0) {
                    *next++ = i;
                    count++;
                }
            }
            if (count != 0) {
                pos = list[random_fn_3_9EE24(count)] * 10;
            } else {
                next = list;
                for (i = 0; i < 4; i++) {
                    if (powerupOnSeg[i] == 0) {
                        *next++ = i;
                        count++;
                    }
                }
                pos = list[random_fn_3_9EE24(count)] * 10;
            }
            break;
        }
        for (i = 0; i < 4; i++) {
            runnersOnSeg[i] = 0;
            list[i] = -1;
            if (g_Minigame.ccs.segmentItems[i][1] >= 0) {
                runnersOnSeg[i] = 2;
            } else if (g_Minigame.ccs.segmentItems[i][0] >= 0) {
                if (g_Minigame.ccs.itemState[g_Minigame.ccs.segmentItems[i][0]] == 3) {
                    runnersOnSeg[i] = 5;
                } else {
                    runnersOnSeg[i] = 1;
                    if (*state != 3) {
                        list[count++] = i;
                    }
                }
            } else {
                list[count++] = i;
            }
        }
        if (*state == 3) {
            if (count == 0) {
                *state = 2;
                gemCount = baseCount;
                continue;
            }
            seg = list[random_fn_3_9EE24(count)];
            pos = random_fn_3_9EE24(6) + 2 + seg * 10;
        } else {
            seg = list[random_fn_3_9EE24(count)];
            if (runnersOnSeg[seg] == 0) {
                pos = random_fn_3_9EE24(8) + 1 + seg * 10;
            } else {
                int other;
                int skip;
                int k;
                pos = seg * 10;
                other = g_Minigame.ccs.itemValue[g_Minigame.ccs.segmentItems[seg][0]] % 10;
                skip = random_fn_3_9EE24(8) + 1;
                for (k = 0; k < 10; k++) {
                    if (other != k) {
                        if (skip == 0) {
                            pos += k;
                            break;
                        }
                        skip--;
                    }
                }
            }
        }
        break;
    }
    seg = pos / 10;
    if (g_Minigame.ccs.segmentItems[seg][0] < 0) {
        g_Minigame.ccs.segmentItems[seg][0] = item;
    } else {
        g_Minigame.ccs.segmentItems[seg][1] = item;
    }
    g_Minigame.ccs.itemValue[item] = pos;
    pos *= 10;
    coin = 0;
    for (gem = 0; gem < gemCount; gem++, pos += 5) {
        for (; coin < 15; coin++) {
            if (g_Minigame.coinState[coin] == 0) {
                g_Minigame.coinState[coin] = item + 1;
                g_Minigame.coinBasePathPos[coin] = (f32)pos / 100.0f;
                g_Minigame.coinFrameCounter[coin] = 0;
                fn_3_7FED4((VecXYZ*)&g_Minigame.coinPos[coin], g_Minigame.coinBasePathPos[coin], (f32)(pos % 100) / 100.0f);
                fn_3_1541C4(coin, *state, &g_Minigame.coinPos[coin]);
                break;
            }
        }
    }
    if (g_Minigame.ccs.itemState[item] == 4) {
        fn_3_106EB0();
    }
}

// .text:0x0013EA30 size:0x214 mapped:0x8077DAC4
void chainChompSpringPoints(void) {
    int coin;

    for (coin = 0; coin < 15; coin++) {
        u8 state = g_Minigame.coinState[coin];
        if (state >= 1 && state <= 6) {
            int candidates[4];
            int* next = candidates;
            int count = 0;
            int type = g_Minigame.ccs.itemState[state - 1] - 2;
            int i;
            for (i = 0; i < 4; i++) {
                candidates[i] = 0;
                if (g_Minigame.playerSlots.runnerPlayerIndex[i] >= 0) {
                    if (ccsBasePathGap(g_Minigame.coinBasePathPos[coin], g_Runners[i].fractionalBasesRan) <= lbl_3_data_218BC[8 + type]) {
                        *next++ = i;
                        count++;
                    }
                }
            }
            if (count != 0) {
                int who = candidates[RandomInt_Game(count)];
                g_Minigame.miniGameCurrentPoints[g_Minigame.playerSlots.runnerPlayerIndex[who]] += ccs_itemGemCounts[type].points;
                g_Minigame.coinState[coin] += 100;
                fn_3_152AB4(coin, who);
                if (type == 2) {
                    callSfx(0x2EA);
                    playCharacterSound(g_Runners[who].charID, 0);
                } else {
                    callSfx(0x2DD);
                }
                if (!g_d_GameSettings.exhibitionMatchInd && who == lbl_3_common_bss_37400[0x20]) {
                    starMissionsMinigamesSpecialAction(3, type, 0);
                }
            }
        }
    }
}

// .text:0x0013E7D4 size:0x25C mapped:0x8077D868
void fn_3_13E7D4(int player) {
    InMemRunnerType* runner = &g_Runners[g_Minigame.playerSlots.playerRunnerIndex[player]];
    int drops = g_Minigame.miniGameCurrentPoints[player] / 2;
    u32 i;

    if (drops == 0) {
        return;
    }
    if (drops > 5) {
        drops = 5;
    }
    for (i = 15; i < 35; i++) {
        if (g_Minigame.coinState[i] != 1) {
            Vec dir;
            f32 angle;
            f32 s;
            f32 c;
            f32 speed;
            f32 up;
            g_Minigame.coinState[i] = 1;
            g_Minigame.coinPos[i].x = runner->position.x;
            g_Minigame.coinPos[i].y = runner->position.y;
            g_Minigame.coinPos[i].z = runner->position.z;
            memcpy(&dir, &runner->velocity, sizeof(Vec));
            dir.y = 0.0f;
            if (!PSVECMag(&dir)) {
                dir.z = 1.0f;
            }
            PSVECNormalize(&dir, &dir);
            angle = 45.0 * (2.0 * ((f32)rand() / 32767.0f - 0.5));
            angle *= 0.017453292f;
            s = SINF(angle);
            c = COSF(angle);
            dir.x = dir.x * c + -dir.z * s;
            c = COSF(angle);
            s = SINF(angle);
            dir.z = dir.x * s + dir.z * c;
            speed = RandomF32_Game_Range(ccs_coinPhysicsConsts[2], ccs_coinPhysicsConsts[3]);
            up = RandomF32_Game_Range(ccs_coinPhysicsConsts[0], ccs_coinPhysicsConsts[1]);
            drops--;
            g_Minigame.coinVelocity[i].x = speed * dir.x;
            g_Minigame.coinVelocity[i].y = up;
            g_Minigame.coinVelocity[i].z = speed * dir.z;
            g_Minigame.coinFrameCounter[i] = 0;
            if (drops == 0) {
                return;
            }
        }
    }
}

// .text:0x0013E6D4 size:0x100 mapped:0x8077D768
void fn_3_13E6D4(void) {
    u32 i;

    for (i = 15; i < 35; i++) {
        if (g_Minigame.coinState) {
            PSVECAdd((Vec*)&g_Minigame.coinPos[i], (Vec*)&g_Minigame.coinVelocity[i], (Vec*)&g_Minigame.coinPos[i]);
            g_Minigame.coinVelocity[i].y += ccs_coinPhysicsConsts[4];
            if (g_Minigame.coinPos[i].y < 0.01) {
                g_Minigame.coinPos[i].y = 0.01f;
                g_Minigame.coinVelocity[i].x *= ccs_coinPhysicsConsts[5];
                g_Minigame.coinVelocity[i].z *= ccs_coinPhysicsConsts[5];
                g_Minigame.coinVelocity[i].y *= -ccs_coinPhysicsConsts[6];
            }
            if (++g_Minigame.coinFrameCounter[i] >= ccs_coinLifetimeFrames) {
                g_Minigame.coinState[i] = 0;
            }
        }
    }
}

// .text:0x0013E670 size:0x64 mapped:0x8077D704
void fn_3_13E670(void) {
    if (g_Minigame.turnOverStatus) {
        g_Minigame.playerIDWithPowerup[0] = -1;
        g_Minigame.powerup.activeInd = FALSE;
    } else if (g_Minigame.powerup.activeInd) {
        fn_3_13E21C(&g_Minigame.powerup);
    } else {
        fn_3_13E3A4(&g_Minigame.powerup);
    }
}

// .text:0x0013E3A4 size:0x2CC mapped:0x8077D438
void fn_3_13E3A4(MinigamePowerupStruct* powerup) {
    if (g_Minigame.playerIDWithPowerup[0] != -1) {
        if (g_Minigame.ccs.chompState != 2 && g_Minigame.ccs.chompState != 3) {
            g_Minigame.powerupHoldFrames--;
        }
        if (g_Minigame.powerupHoldFrames <= 0) {
            fn_800115C8(g_Minigame.playerIDWithPowerup[0]);
            g_Minigame.playerIDWithPowerup[0] = -1;
        }
    } else {
        powerup->timer--;
        if (powerup->timer <= 0) {
            int last;
            int i;
            int lap;
            int next;
            int spots[2];
            int* spot;
            InMemRunnerType* runner;
            powerup->activeInd = TRUE;
            last = 0;
            for (i = 1; i < 4; i++) {
                if (g_Minigame.miniGameCurrentPoints[last] > g_Minigame.miniGameCurrentPoints[i]) {
                    last = i;
                }
            }
            runner = &g_Runners[last];
            lap = (int)runner->fractionalBasesRan * 10;
            next = lap + 10;
            if (next >= 40) {
                next = 0;
            }
            if ((f32)((int)(100.0f * runner->fractionalBasesRan) % 100) < 0.5f) {
                spots[0] = lap;
                spots[1] = next;
            } else {
                spots[0] = next;
                spots[1] = lap;
            }
            spot = &spots[0];
            for (i = 0; i < 15; i++) {
                if (g_Minigame.ccs.itemValue[i] == spots[0]) {
                    spot = &spots[1];
                    break;
                }
            }
            powerup->basePathPos = (f32)*spot / 10.0f;
            fn_3_7FED4(&powerup->pos, powerup->basePathPos, 0.0f);
            memset(&powerup->_0C, 0, sizeof(VecXYZ));
            powerup->timer = ccs_powerupTimers[1];
        }
    }
}

// .text:0x0013E21C size:0x188 mapped:0x8077D2B0
#pragma dont_inline on
void fn_3_13E21C(MinigamePowerupStruct* powerup) {
    int candidates[4];
    int* next = candidates;
    int count = 0;
    f32 range = lbl_3_data_218BC[11];
    int i;

    for (i = 0; i < 4; i++) {
        candidates[i] = 0;
        if (g_Minigame.playerSlots.runnerPlayerIndex[i] >= 0) {
            if (ccsBasePathGap(powerup->basePathPos, g_Runners[i].fractionalBasesRan) <= range) {
                *next++ = i;
                count++;
            }
        }
    }
    if (count != 0) {
        int who = candidates[RandomInt_Game(count)];
        g_Minigame.playerIDWithPowerup[0] = who;
        g_Minigame.powerupHoldFrames = ccs_powerupTimers[2];
        powerup->activeInd = FALSE;
        powerup->timer = ccs_powerupTimers[0];
        callSfx(0x2F6);
        fn_3_16C394(who);
    } else {
        if (g_Minigame.ccs.chompState != 2 && g_Minigame.ccs.chompState != 3) {
            powerup->timer--;
        }
        if (powerup->timer <= 0) {
            powerup->activeInd = FALSE;
            powerup->timer = ccs_powerupTimers[0];
        }
    }
}
#pragma dont_inline reset

// .text:0x0013E174 size:0xA8 mapped:0x8077D208
void fn_3_13E174(u8 type) {
    switch (type) {
    case 0:
        lbl_3_bss_B798 = lbl_3_data_218BC[12];
        lbl_3_bss_B794 = lbl_3_data_218BC[14];
        break;
    case 1:
        lbl_3_bss_B798 = lbl_3_data_218BC[13];
        lbl_3_bss_B794 = lbl_3_data_218BC[15];
        break;
    default:
        return;
    }
    fn_800528AC(fn_3_13DFBC);
}

// .text:0x0013DFBC size:0x1B8 mapped:0x8077D050
void fn_3_13DFBC(camera_803c639c_s* cam) {
    Vec offset;
    Mtx invView;
    int range = 1000.0f * lbl_3_bss_B794;

    offset.x = (rand() % range - range / 2) / 1000.0;
    offset.y = (rand() % range - range / 2) / 1000.0;
    offset.z = 0.0f;
    PSMTXInverse(cam->view, invView);
    PSMTXMultVecSR(invView, &offset, &offset);
    cam->eye.x += offset.x;
    cam->eye.y += offset.y;
    cam->eye.z += offset.z;
    cam->target.x += offset.x;
    cam->target.y += offset.y;
    cam->target.z += offset.z;
    if (--lbl_3_bss_B798 <= 0) {
        lbl_3_bss_B798 = 0;
        lbl_3_bss_B794 = 0.0f;
        fn_800528B4();
    }
}

// .text:0x0013DEA4 size:0x118 mapped:0x8077CF38
void fn_3_13DEA4(void) {
    ChainChompSprintAI* ai = g_Minigame.ccsAI;
    s8 i;

    memset(g_Minigame._1D7C, 0, 0x78);
    i = 0;
    do {
        u8 strength = g_Minigame.playerSlots.aiStrength[i];
        ai->_0 = RandomInt_Game_Range(lbl_3_data_2194C[strength][0], lbl_3_data_2194C[strength][1]);
        if (RandomInt_Game(100) < lbl_3_data_2197C[strength]) {
            if (lbl_3_data_21980[strength] < 8) {
                ai->_6 = RandomInt_Game_Range(lbl_3_data_21980[strength], 8);
            } else {
                ai->_6 = 8;
            }
        } else {
            ai->_6 = 0x7F;
        }
        ai->_5 = 2;
        ai->_7 = RandomInt_Game_Range(lbl_3_data_21944[strength][0], lbl_3_data_21944[strength][1]);
        ai++;
    } while (++i < 4);
}

// .text:0x0013DDE0 size:0xC4 mapped:0x8077CE74
f32 fn_3_13DDE0(u8 forward, f32 from, f32 to) {
    if (from < 0.0f) {
        from += 4.0f;
    } else if (from >= 4.0f) {
        from -= 4.0f;
    }
    if (to < 0.0f) {
        to += 4.0f;
    } else if (to >= 4.0f) {
        to -= 4.0f;
    }
    if (forward == 1) {
        if (from > to) {
            return 4.0f + to - from;
        }
        return to - from;
    }
    if (from < to) {
        return 4.0f + from - to;
    }
    return from - to;
}

// .text:0x0013DC48 size:0x198 mapped:0x8077CCDC
void fn_3_13DC48(s8 runnerIdx, f32 target, f32* forward, f32* backward) {
    *forward = fn_3_13DDE0(1, g_Runners[runnerIdx].fractionalBasesRan, target);
    if (g_Runners[runnerIdx].runningDirectionCode == 3) {
        *forward += 0.15f;
    }
    *backward = fn_3_13DDE0(0, g_Runners[runnerIdx].fractionalBasesRan, target);
    if (g_Runners[runnerIdx].runningDirectionCode == 1) {
        *backward += 0.15f;
    }
}

// .text:0x0013DA50 size:0x1F8 mapped:0x8077CAE4
f32 fn_3_13DA50(f32 target, s8 runnerIdx, u8* direction) {
    f32 forward;
    f32 backward;

    fn_3_13DC48(runnerIdx, target, &forward, &backward);
    if (forward < backward) {
        *direction = 1;
        return forward;
    }
    if (forward > backward) {
        *direction = 3;
        return backward;
    }
    *direction = RandomInt_Game(2) ? 1 : 3;
    return forward;
}

// .text:0x0013DA20 size:0x30 mapped:0x8077CAB4
int fn_3_13DA20(f32* a, f32* b) {
    return 100.0f * *a - 100.0f * *b;
}

// .text:0x0013D618 size:0x408 mapped:0x8077C6AC
f32 fn_3_13D618(f32 target, s8 runnerIdx, u8* direction) {
    f32 dists[4];
    s8 count;
    s8 i;
    f32 dist = fn_3_13DA50(target, runnerIdx, direction);

    count = 0;
    i = 0;
    do {
        s8 c = g_Minigame.playerSlots.characterIndex[i];
        if (c >= 0 && c < 4 && g_Minigame.ccs.runnerChompHitState[i] == 0) {
            f32 forward;
            f32 backward;
            fn_3_13DC48(i, target, &forward, &backward);
            dists[count++] = forward < backward ? forward : backward;
        }
    } while (++i < 4);
    fn_800246D4((int (*)(const void*, const void*))fn_3_13DA20, dists, dists, 4, count);
    return dist - dists[0];
}

// .text:0x0013D5E8 size:0x30 mapped:0x8077C67C
int fn_3_13D5E8(f32* a, f32* b) {
    return 100.0f * *a - 100.0f * *b;
}

// .text:0x0013D578 size:0x70 mapped:0x8077C60C
u8 fn_3_13D578(s8 player) {
    s8 i = 0;

    do {
        s8 c = g_Minigame.playerSlots.characterIndex[i];
        if (c >= 0 && c < 4 && g_Minigame.miniGameCurrentPoints[i] > g_Minigame.miniGameCurrentPoints[player]) {
            return TRUE;
        }
    } while (++i < 4);
    return FALSE;
}

// .text:0x0013C7BC size:0xDBC mapped:0x8077B850
void fn_3_13C7BC(void) {
    s8 i;
    s8 itemPos[15];
    CCSAITarget targets[15];
    s8 special = -1;
    s8 target = -1;
    s8 count = 0;
    ChainChompSprintAI* ais = g_Minigame.ccsAI;
    s8 p;
    s8 k;
    u8 direction;

    i = 0;
    do {
        g_Minigame.ccs_aiControlledInd[i] = 0;
    } while (++i < 4);
    p = 0;
    do {
        k = 0;
        do {
            s8 item = g_Minigame.ccs.segmentItems[p][k];
            if (item >= 0) {
                switch (g_Minigame.ccs.itemState[item]) {
                case 4:
                    special = g_Minigame.ccs.itemValue[item];
                    break;
                case 3: {
                    s8 c;
                    target = g_Minigame.ccs.itemValue[item] + 1;
                    c = 0;
                    do {
                        if (g_Minigame.coinState[c] - 1 == item) {
                            if ((int)(100.0f * (0.001f + g_Minigame.coinBasePathPos[c])) == target * 10) {
                                break;
                            }
                            itemPos[count++] = 10.0f * (0.001f + g_Minigame.coinBasePathPos[c]);
                        }
                    } while (++c < 15);
                    if (c >= 15) {
                        target = -1;
                    }
                    break;
                }
                case 2:
                    itemPos[count++] = g_Minigame.ccs.itemValue[item];
                    break;
                }
            }
        } while (++k < 2);
    } while (++p < 4);

    i = 0;
    do {
        s8 c = g_Minigame.playerSlots.characterIndex[i];
        ChainChompSprintAI* ai = &ais[i];
        u8 strength;

        if (c < 0 || c >= 4 || !g_Minigame.playerSlots.aiControlledInd[i]) {
            continue;
        }
        g_Minigame.ccs_aiControlledInd[c] = 1;
        memset(&g_Minigame._1D7C[c], 0, sizeof(InputStruct));
        strength = g_Minigame.playerSlots.aiStrength[i];
        if ((ai->state < 10 || ai->state > 13) &&
            (g_Minigame.ccs.chompState == 1 || g_Minigame.ccs._26 - g_Minigame.ccs.chompStateTimer <= ai->_0)) {
            ai->state = 10;
        }
        switch (ai->state) {
        case 0:
            if (g_Minigame.ccs.chompStateTimer / 120 == ai->_6 - 1 && g_Minigame.ccs.chompStateTimer % 120 >= 48) {
                ai->state = 7;
                break;
            }
            if (ai->_4-- <= 0) {
                g_Minigame._1D7C[c].buttonInput = g_Minigame._1D7C[c].newButtonInput |= INPUT_BUTTON_B;
                ai->_4 = RandomInt_Game_Range(ccsAI_bPressDelayRanges[strength][0], ccsAI_bPressDelayRanges[strength][1]);
            }
            if (ai->_7-- > 0) {
                break;
            }
            ai->_7 = RandomInt_Game_Range(lbl_3_data_21944[strength][0], lbl_3_data_21944[strength][1]);
            ai->_5 = 0;
            if (special >= 0) {
                f32 forward;
                f32 backward;
                fn_3_13DC48(i, (f32)special / 10.0f, &forward, &backward);
                if (forward < backward) {
                    ai->state = 1;
                } else if (forward > backward) {
                    ai->state = 4;
                } else if (g_Runners[i].runningDirectionCode == 2 || g_Runners[i].nextDirectionBeingProcessed == 2) {
                    ai->state = RandomInt_Game(2) ? 1 : 4;
                }
                ai->_5 = 4;
            } else if (target >= 0) {
                if (fn_3_13D618((f32)target / 10.0f, i, &direction) <= ccsAI_targetDistThresholds[strength]) {
                    if (direction == 1) {
                        ai->state = 1;
                    } else {
                        ai->state = 4;
                    }
                    ai->_5 = 3;
                }
            }
            if (ai->_5 == 0 && count != 0) {
                k = 0;
                do {
                    targets[k].pos = itemPos[k];
                    targets[k].dist = fn_3_13DA50((f32)targets[k].pos / 10.0f, i, &targets[k].direction);
                } while (++k < count);
                fn_800246D4((int (*)(const void*, const void*))fn_3_13D5E8, targets, targets, sizeof(CCSAITarget), count);
                k = 0;
                do {
                    if (fn_3_13D618((f32)targets[k].pos / 10.0f, i, &direction) <= ccsAI_targetDistThresholds[strength]) {
                        if (direction == 1) {
                            ai->state = 1;
                        } else {
                            ai->state = 4;
                        }
                        ai->_5 = 2;
                        break;
                    }
                } while (++k < count);
            }
            if (ai->_5 == 0 && (g_Runners[i].runningDirectionCode == 2 || g_Runners[i].nextDirectionBeingProcessed == 2)) {
                ai->state = RandomInt_Game(2) ? 1 : 4;
            }
            break;
        case 1:
            if (g_Runners[i].runningDirectionCode == 1 || g_Runners[i].nextDirectionBeingProcessed == 1) {
                ai->state = 0;
            } else {
                g_Minigame._1D7C[c].buttonInput = g_Minigame._1D7C[c].newButtonInput |= INPUT_BUTTON_Y;
                ai->state = 2;
            }
            break;
        case 2:
            ai->state = 3;
            break;
        case 3:
            g_Minigame._1D7C[c].buttonInput = g_Minigame._1D7C[c].newButtonInput |= INPUT_BUTTON_Y;
            ai->state = 0;
            break;
        case 4:
            if (g_Runners[i].runningDirectionCode == 3 || g_Runners[i].nextDirectionBeingProcessed == 3) {
                ai->state = 0;
            } else {
                g_Minigame._1D7C[c].buttonInput = g_Minigame._1D7C[c].newButtonInput |= INPUT_BUTTON_X;
                ai->state = 5;
            }
            break;
        case 5:
            ai->state = 6;
            break;
        case 6:
            g_Minigame._1D7C[c].buttonInput = g_Minigame._1D7C[c].newButtonInput |= INPUT_BUTTON_X;
            ai->state = 0;
            break;
        case 7:
            if (g_Runners[i].runningDirectionCode == 1) {
                g_Minigame._1D7C[c].buttonInput = g_Minigame._1D7C[c].newButtonInput |= INPUT_BUTTON_X;
            } else if (g_Runners[i].runningDirectionCode == 3) {
                g_Minigame._1D7C[c].buttonInput = g_Minigame._1D7C[c].newButtonInput |= INPUT_BUTTON_Y;
            }
            ai->state = 8;
            break;
        case 8:
            if (g_Runners[i].runningDirectionCode == 2 || g_Runners[i].nextDirectionBeingProcessed == 2) {
                ai->state = 9;
            } else {
                ai->state = 7;
            }
            break;
        case 9:
            if (g_Minigame.ccs.chompStateTimer % 120 >= 96) {
                if (RandomInt_Game(100) < lbl_3_data_2197C[strength]) {
                    int lap = g_Minigame.ccs.chompStateTimer / 120 + 2;
                    int lastLap = g_Minigame.ccs._26 / 120 + 1;
                    if (lap < lastLap) {
                        ai->_6 = RandomInt_Game_Range(lap, lastLap);
                    } else {
                        ai->_6 = lastLap;
                    }
                } else {
                    ai->_6 = 0x7F;
                }
                ai->state = 0;
            }
            break;
        case 10:
            if (g_Runners[i].runningDirectionCode == 2 || g_Runners[i].nextDirectionBeingProcessed == 2) {
                ai->state = 13;
                break;
            }
            if (ai->_5 == 4) {
                ai->_3 = RandomInt_Game_Range(lbl_3_data_21974[strength][0], lbl_3_data_21974[strength][1]);
            } else {
                ai->_3 = RandomInt_Game_Range(lbl_3_data_2196C[strength][0], lbl_3_data_2196C[strength][1]);
            }
            ai->state = 11;
        case 11:
            if (ai->_3-- <= 0) {
                if (g_Runners[i].runningDirectionCode == 1) {
                    g_Minigame._1D7C[c].buttonInput = g_Minigame._1D7C[c].newButtonInput |= INPUT_BUTTON_X;
                } else if (g_Runners[i].runningDirectionCode == 3) {
                    g_Minigame._1D7C[c].buttonInput = g_Minigame._1D7C[c].newButtonInput |= INPUT_BUTTON_Y;
                }
                ai->state = 12;
            }
            break;
        case 12:
            if (g_Runners[i].runningDirectionCode == 2 || g_Runners[i].nextDirectionBeingProcessed == 2) {
                ai->state = 13;
            } else {
                ai->_3 = 1;
                ai->state = 11;
            }
            break;
        case 13:
            if (g_Minigame.ccs.chompState == 0 || g_Minigame.ccs.chompState == 4) {
                if (fn_3_13D578(i) || g_Minigame.minigameFramesRemaining <= 1200) {
                    ai->_0 = RandomInt_Game_Range(lbl_3_data_2195C[strength][0], lbl_3_data_2195C[strength][1]);
                } else {
                    ai->_0 = RandomInt_Game_Range(lbl_3_data_2194C[strength][0], lbl_3_data_2194C[strength][1]);
                }
                if (RandomInt_Game(100) < lbl_3_data_2197C[strength]) {
                    if (lbl_3_data_21980[strength] < g_Minigame.ccs._26 / 120 + 1) {
                        ai->_6 = RandomInt_Game_Range(lbl_3_data_21980[strength], g_Minigame.ccs._26 / 120 + 1);
                    } else {
                        ai->_6 = g_Minigame.ccs._26 / 120 + 1;
                    }
                } else {
                    ai->_6 = 0x7F;
                }
                ai->state = 0;
            }
            break;
        }
    } while (++i < 4);
}

// .text:0x0013C790 size:0x2C mapped:0x8077B824
void fn_3_13C790(void) {
    s8 i = 0;

    do {
        g_Minigame.ccs_aiControlledInd[i] = 0;
    } while (++i < 4);
}
