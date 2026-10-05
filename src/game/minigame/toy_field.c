#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_toyField
#include "game/minigame/toy_field.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/math/game_math.h"
#include "game/match_setup/match_flow.h"
#include "game/match_setup/scene_skip.h"
#include "game/match_setup/roster_init.h"
#include "game/match_setup/ai_defaults.h"
#include "game/match_setup/transition_init.h"
#include "game/ball/ball_physics.h"
#include "game/ball/foul_detection.h"
#include "game/pitching/pitcher.h"
#include "game/pitching/pitcher_stamina.h"
#include "game/batting/batter.h"
#include "game/fielding/fielder.h"
#include "game/animation/scene_effects.h"
#include "game/stadium/sta_c6.h"
#include "game/minigame/rep_3880.h"
#include "game/minigame/pitching_machine.h"
#include "musyx/musyx.h"
#include "Dolphin/stl.h"
#include "stl/stdlib.h"
#include "Unknown/File_0x800204cc.h"
#include "Unknown/File_0x8004abd8.h"
#include "Unknown/File_0x8004cc18.h"
#include "Unknown/File_0x80021410.h"

extern struct {
    /*0x000*/ s32 controllerPort;
    /*0x004*/ u16 _04;
    /*0x006*/ u16 _06;
    /*0x008*/ u16 _08;
    /*0x00A*/ u8 _0A[0x0C - 0x0A];
    /*0x00C*/ s16 _0C;
    /*0x00E*/ u8 _0E[0x12 - 0x0E];
    /*0x012*/ s16 _12;
    /*0x014*/ u8 _14[0x1D0 - 0x14];
    /*0x1D0*/ u8 _1D0;
    /*0x1D1*/ u8 _1D1;
    /*0x1D2*/ u8 state;
    /*0x1D3*/ u8 _1D3;
    /*0x1D4*/ u8 _1D4;
    /*0x1D5*/ u8 _1D5;
    /*0x1D6*/ u8 _1D6[0x1D9 - 0x1D6];
    /*0x1D9*/ u8 _1D9;
    /*0x1DA*/ s8 cursor;
    /*0x1DB*/ u8 _1DB[0x220 - 0x1DB];
    /*0x220*/ u8 _220;
    /*0x221*/ u8 _221[0x264 - 0x221];
} pauseControl;

extern u8 lbl_800EFBA4[0x10];
extern u8 lbl_8037169C[0x1C];
extern u8 hugeAnimStruct[0x3154];
extern u8 highLevelSimulationFlag;
extern u16 stadiumHazardSoundIDs[16];
extern u8 stadiumHazardSoundFxRelated[0xB4];
extern u8 lbl_3_data_84B8[0x3C];
extern u8 lbl_3_data_88DC;
extern struct {
    u8 _00[5];
    u8 _05;
    u8 _06;
} g_UnkSimulation_31AC0;

extern void QueueTextToDisplay(int code, int arg1);
extern void ballPhysica(void);
extern void toyFieldRelated(void);
extern void fn_3_D9868(void);
extern void fn_3_D8CD0(void);
extern void fn_3_15F998(void);
extern void fn_3_107E80(void);
extern void fn_3_AFD80(int arg0);
extern void fn_3_FBD58(void);
extern void fn_3_FBD70(void);
extern void initializeMinigameData(void);

u8 lbl_3_data_188E8[20] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x02,
    0x03, 0x04, 0x05, 0x00, 0x00, 0x02, 0x03, 0x05,
    0x00, 0x00, 0x00, 0x00,
};
u8 lbl_3_data_188FC[16] = {
    0x00, 0x02, 0x01, 0x03, 0x04, 0x05, 0x00, 0x01,
    0x03, 0x04, 0x00, 0x01, 0x03, 0x04, 0x00, 0x00,
};
u8 aILevel[4] = {
    0x03, 0x02, 0x01, 0x00,
};
u8 mapping_minigame_Stadium[8] = {
    0x06, 0x00, 0x04, 0x05, 0x02, 0x03, 0x01, 0x00,
};
u8 lbl_3_data_18918[8] = {
    0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00,
};
u8 lbl_3_data_18920[36] = {
    0x04, 0x04, 0x04, 0x04, 0x04, 0x01, 0x01, 0x01,
    0x01, 0x02, 0x04, 0x04, 0x04, 0x01, 0x04, 0x01,
    0x01, 0x01, 0x01, 0x02, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x00,
};
u8 lbl_3_data_18944[8] = {
    0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00,
};
u8 lbl_3_data_1894C[44] = {
    0x03, 0x13, 0x30, 0x32, 0xFF, 0xFF, 0xFF, 0x00,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x04, 0x0C, 0x2A, 0x14,
    0x2B, 0xFF, 0xFF, 0x05, 0x10, 0x2C, 0x2D, 0x2E,
    0x2F, 0xFF, 0x00, 0x00,
};
u8 lbl_3_data_18978[8] = {
    0x00, 0x01, 0x02, 0x03, 0x03, 0x00, 0x00, 0x00,
};
u8 lbl_3_data_18980 = 2;
f32 lbl_3_data_18984[6] = {
    0.0f, 70.0f,
    12.0f, 40.0f,
    -12.0f, 40.0f,
};
s16 lbl_3_data_1899C[4] = {
    120, 90, 20, 0,
};
u8 lbl_3_data_189A4[8] = {
    0x0A, 0x14, 0x1E, 0x28, 0x32, 0x0A, 0x00, 0x00,
};
// panel collision code 0x70..0x78 -> TOY_FIELD_RESULT
u8 lbl_3_data_189AC[12] = {
    0,
    TOY_FIELD_RESULT_CAUGHT,
    TOY_FIELD_RESULT_SINGLE,
    TOY_FIELD_RESULT_GROUND_RULE_DOUBLE,
    TOY_FIELD_RESULT_TRIPLE,
    TOY_FIELD_RESULT_HOMERUN,
    9,
    10,
    11,
};
s16 lbl_3_data_189B8[6] = {
    10, 20, 30, 10, 100, 0,
};
u8 lbl_3_data_189C4[260] = {
    0x00, 0x00, 0x00, 0x02, 0x00, 0x03, 0x00, 0x04, 0x00, 0x05, 0x00, 0x06, 0x00,
    0x07, 0x00, 0x05, 0x00, 0x00, 0x00, 0x03, 0x00, 0x02, 0x00, 0x07, 0x00, 0x04,
    0x00, 0x06, 0x00, 0x04, 0x00, 0x00, 0x00, 0x06, 0x00, 0x03, 0x00, 0x05, 0x00,
    0x07, 0x00, 0x02, 0x00, 0x00, 0x14, 0x00, 0x0D, 0x14, 0x00, 0x02, 0x05, 0x28,
    0x14, 0x00, 0x0F, 0x0F, 0x0C, 0x03, 0x0A, 0x19, 0x1E, 0x00, 0x19, 0x00, 0x14,
    0x05, 0x0A, 0x0A, 0x0A, 0x00, 0x05, 0x0A, 0x00, 0x00, 0x05, 0x46, 0x14, 0x00,
    0x0F, 0x0F, 0x0C, 0x03, 0x0A, 0x19, 0x1E, 0x00, 0x19, 0x00, 0x14, 0x05, 0x0A,
    0x0A, 0x05, 0x00, 0x05, 0x05, 0x00, 0x00, 0x05, 0x50, 0x14, 0x00, 0x0F, 0x0F,
    0x0C, 0x03, 0x0A, 0x19, 0x1E, 0x00, 0x19, 0x00, 0x14, 0x05, 0x0A, 0x0A, 0x14,
    0x00, 0x0D, 0x14, 0x00, 0x02, 0x05, 0x28, 0x14, 0x00, 0x0F, 0x0F, 0x0C, 0x03,
    0x0A, 0x19, 0x1E, 0x00, 0x19, 0x00, 0x14, 0x05, 0x0A, 0x0A, 0x0A, 0x00, 0x05,
    0x0A, 0x00, 0x00, 0x05, 0x46, 0x14, 0x00, 0x0F, 0x0F, 0x0C, 0x03, 0x0A, 0x19,
    0x1E, 0x00, 0x19, 0x00, 0x14, 0x05, 0x0A, 0x0A, 0x05, 0x00, 0x05, 0x05, 0x00,
    0x00, 0x05, 0x50, 0x14, 0x00, 0x0F, 0x0F, 0x0C, 0x03, 0x0A, 0x19, 0x1E, 0x00,
    0x19, 0x00, 0x14, 0x05, 0x0A, 0x0A, 0x14, 0x00, 0x0B, 0x1E, 0x00, 0x00, 0x00,
    0x27, 0x0F, 0x00, 0x0F, 0x1E, 0x1E, 0x00, 0x00, 0x0A, 0x14, 0x00, 0x14, 0x1E,
    0x1E, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x0A, 0x14, 0x00, 0x00, 0x0A, 0x32, 0x0F,
    0x00, 0x05, 0x14, 0x28, 0x00, 0x0A, 0x0A, 0x0A, 0x00, 0x0A, 0x0A, 0x32, 0x0A,
    0x0A, 0x00, 0x0A, 0x00, 0x0A, 0x0F, 0x00, 0x00, 0x05, 0x3C, 0x0F, 0x00, 0x05,
    0x14, 0x1E, 0x05, 0x0A, 0x0A, 0x0A, 0x00, 0x0A, 0x0A, 0x32, 0x0A, 0x0A, 0x00,
};
f32 lbl_3_data_18AC8[10][4] = {
    { 17.7f, 37.1f, 9.0f, 14.0f },
    { 0.0f, 52.0f, 9.0f, 14.0f },
    { -17.7f, 37.1f, 9.0f, 14.0f },
    { 34.2f, 53.6f, 9.0f, 14.0f },
    { 20.0f, 71.0f, 9.0f, 14.0f },
    { 0.0f, 76.8f, 9.0f, 14.0f },
    { -20.0f, 71.0f, 9.0f, 14.0f },
    { -34.2f, 53.6f, 9.0f, 14.0f },
    { 21.0f, 96.5f, 9.0f, 15.0f },
    { -21.0f, 96.5f, 9.0f, 15.0f },
};
u8 lbl_3_data_18B68[32] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
};
f32 lbl_3_data_18B88[5] = {
    0.84f, 0.88f, 0.92f, 0.96f, 1.0f,
};
f32 lbl_3_data_18B9C[5] = {
    0.004f, 0.985f, 0.65f, 0.5f, 1.5f,
};
s16 lbl_3_data_18BB0[4] = {
    240, 180, 180, 150,
};
s16 lbl_3_data_18BB8[72] = {
    10, 0, 0, 20, 0, 0, 30, 0, 0,
    40, 0, -20, 40, -40, 0, 30, -10, -10,
    60, -20, -20, 90, -30, -30, 120, -40, -40,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    200, 0, 0, 50, 0, 0, 100, 0, 0,
    30, 0, 0, 0, 0, 0, 0, 0, 0,
    -90, 30, 30, 0, 0, 0, -50, 0, 50,
    0, 0, 0, -30, 30, 0, 20, -20, 0,
};
s16 lbl_3_data_18C48[10] = {
    100, 180, 600, 279, 3, 1, 60, 70, 2, 0,
};

#define TOY_FIELD_COIN_COUNT 100
#define MG_BYTE(offset) (*((u8*)&g_Minigame + (offset)))

#define SATURATING_INCREMENT(counter) \
    if ((counter) < 0x7FFE) {         \
        (counter)++;                  \
    } else {                          \
        (counter) = 0x7FFF;           \
    }

#define TOY_FIELD_COIN_GRAVITY (lbl_3_data_18B9C[0])
#define TOY_FIELD_COIN_DAMPING (lbl_3_data_18B9C[1])
#define TOY_FIELD_COIN_BOUNCE (lbl_3_data_18B9C[2])
#define TOY_FIELD_COIN_FLOOR (lbl_3_data_18B9C[3])
#define TOY_FIELD_COIN_VISIBLE(i) ((&g_Minigame.wallBall_coinsVisibleInd)[i])
#define TOY_FIELD_COIN_POSITION(i) ((&g_Minigame.wallBall_coinCoordinates)[i])
#define TOY_FIELD_COIN_VELOCITY(i) ((&g_Minigame.wallBall_coinVelocity)[i])
#define TOY_FIELD_FIELDER_SLOT(i) (*(s8*)&g_Minigame.minigameControlStruct[1].aIStrength[2 + (i)])
#define TOY_FIELD_FIELDER(slot) g_Fielders[(s8)g_Minigame.minigameFielderIndex[(slot)]]

static inline void toyFieldPlayHazardSound(int idOffset, int fxOffset) {
    int stadium = g_d_GameSettings.StadiumID;
    SND_VOICEID voice = sndFXStartEx(
        stadiumHazardSoundIDs[stadium] + idOffset,
        g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD ? lbl_3_data_84B8[fxOffset]
                                                                 : stadiumHazardSoundFxRelated[stadium * 0x1E + fxOffset],
        0x3F, 0);
    sndFXCtrl(voice, 0x5B,
              g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                  ? lbl_3_data_84B8[fxOffset + 1]
                  : stadiumHazardSoundFxRelated[stadium * 0x1E + fxOffset + 1]);
}

static inline void toyFieldRecordPoints(void) {
    int i;
    for (i = 0; i < 4; i++) {
        if (g_Minigame.miniGameLatestPoints[i] != 0) {
            g_Minigame.minigamePoints_current_Latest[i][0] = g_Minigame.miniGameCurrentPoints[i];
            g_Minigame.minigamePoints_current_Latest[i][1] = g_Minigame.miniGameLatestPoints[i];
        }
    }
}

#define TOY_FIELD_AWARD_POINTS(batterPoints, pitcherPoints, fielderPoints)                                  \
    g_Minigame.miniGameLatestPoints[g_Minigame.rosterID] += g_Minigame.toyField_pointMultiplier * (batterPoints); \
    g_Minigame.miniGameLatestPoints[(s8)g_Minigame.minigamePlayerSelectedOrder] +=                                \
        g_Minigame.toyField_pointMultiplier * (pitcherPoints);                                                    \
    g_Minigame.miniGameLatestPoints[TOY_FIELD_FIELDER_SLOT(1)] +=                                                 \
        g_Minigame.toyField_pointMultiplier * (fielderPoints);                                                    \
    g_Minigame.miniGameLatestPoints[TOY_FIELD_FIELDER_SLOT(2)] +=                                                 \
        g_Minigame.toyField_pointMultiplier * (fielderPoints)

static inline void toyFieldQueueTurnEndText(void) {
    s16 turn = g_Minigame.toyField_turnNumber;
    s16 selectedTurns = g_Minigame.toyField_selectedTurns;
    if (turn >= selectedTurns && MG_BYTE(0x18E8 + g_Minigame.rosterID) == 1) {
        QueueTextToDisplay(13, 0);
    } else if ((u8)g_Minigame.rosterID != (s8)g_Minigame._19C6) {
        if (turn >= selectedTurns) {
            QueueTextToDisplay(13, 0);
        } else {
            QueueTextToDisplay(5, 0);
        }
    }
}

static inline f32 toyFieldCoinDistanceToFielder(int coin, int slot) {
    InMemFielder* fielder = &TOY_FIELD_FIELDER(TOY_FIELD_FIELDER_SLOT(slot));
    return dolsqrtf2(SQ(TOY_FIELD_COIN_POSITION(coin).x - fielder->pos.x) + SQ(TOY_FIELD_COIN_POSITION(coin).z - fielder->pos.z));
}

// .text:0x000DE744 size:0x44C mapped:0x8071D7D8
void initializeToyFieldSomething(void) {
    s32 i;
    initializeStgh2();
    setDefaultPlayTrackingVariables2();
    VEC_COPY(&g_Runners[0].positionStored, &g_Runners[0].position);
    g_Runners[0].unused_AIRelated = 1;
    g_Runners[0].battingHand = g_Batter.batterHand;
    g_Runners[0].batterStayInBattersBoxReason = 1;
    g_Runners[0].position.x = g_Batter.batterPos.x;
    g_Runners[0].position.y = 0.0f;
    g_Runners[0].position.z = g_Batter.batterPos.z;
    g_Runners[0].runningAngle = PI;
    g_GameLogic.CountdownUntilFade = 10000;
    g_Strikes.storedOuts = g_Strikes.outs;
    g_Strikes.outs = 0;
    g_Strikes.storedOuts = 0;
    g_Ball.totalFramesAtPlay = 0;
    pauseControl._1D5 = 0;
    g_Scores._C5 = 0;
    g_Minigame.turnOverStatus = 0;
    g_Minigame.pointsTargetReachedInd = FALSE;
    g_Minigame.toyFieldBallStateResult2 = 0;
    g_Minigame.framesSincePanelHit = 0;
    g_Minigame.toyField_runsScored = 0;
    g_Minigame.toyField_runnerOnHome = 1;
    g_Minigame.toyFieldStateInd_collisionRelated = 0;
    g_Minigame.toyField_coinsRemaining = 0;
    g_Minigame.panelHitInd = FALSE;
    g_Minigame._19A0 = 0;
    g_Minigame._1934 = 0;
    g_Minigame._18BA = 0;
    g_Minigame._19A3 = 0;
    g_Minigame.TF_framesSinceHittingPanel = 0;
    g_Minigame.TF_ballDespawnedInd = FALSE;
    g_Minigame._190E = 0;
    g_Minigame.maybeTFCollisionResultState = 0;
    g_Minigame.toyFieldBallStateResult = 0;
    g_Minigame._19BC = 0;
    g_Minigame._19D0 = 0;
    g_Minigame._19CD = 0;
    g_Minigame._19CF = 0;
    if (g_Minigame._19CE == 3) {
        fn_3_E67F4();
    }
    g_Minigame._19CE = 0;
    for (i = 0; i < 4; i++) {
        g_Minigame.minigamePoints_current_Latest[i][0] = g_Minigame.miniGameCurrentPoints[i];
        g_Minigame.minigamePoints_current_Latest[i][1] = 0;
        (&g_Minigame._1935)[i] = -1;
    }
    for (i = 0; i < TOY_FIELD_COIN_COUNT; i++) {
        (&g_Minigame.wallBall_coinsVisibleInd)[i] = FALSE;
    }
    for (i = 0; i < 4; i++) {
        if ((&g_Minigame.toyField_runnerOnHome)[i] != 0) {
            (&g_Minigame.toyField_runnerBase0)[i] = i;
        } else {
            (&g_Minigame.toyField_runnerBase0)[i] = -1;
        }
        (&g_Minigame._1918)[i] = (&g_Minigame.toyField_runnerOnHome)[i];
    }
    g_FieldingLogic.playOverInd = FALSE;
    g_FieldingLogic.framesSincePlayEnded = 0;
    g_FieldingLogic.unused_always0__ = 0;
    g_FieldingLogic.hasProcessedFoulBall = 0;
    g_FieldingLogic.canEndPlayOnLooseBallInd = FALSE;
    g_FieldingLogic.always0__ = 0;
    g_FieldingLogic.framesSince3rdOutWasMade = 0;
    g_RunningLogic._13 = 0;
    if (g_GameLogic.pre_PostMiniGameInd) {
        g_GameLogic.minigameLastTurnSuccessInd = TRUE;
        g_GameLogic.hudElementLoadingInd = TRUE;
    } else {
        g_GameLogic.minigameLastTurnSuccessInd = FALSE;
    }
    g_GameLogic.pre_PostMiniGameInd = FALSE;
    changeScene(1, 6);
    SetGameStatus(GAME_STATUS_AT_BAT);
}

// .text:0x000DE610 size:0x134 mapped:0x8071D6A4
void toyFieldEndTurn(void) {
    g_Minigame.panelHitInd = FALSE;
    if (g_Minigame._19A6 != 0) {
        g_Minigame._19A6--;
        if (g_Pitcher.strikeOutOrWalk == AT_BAT_END_WALK || g_Pitcher.strikeOutOrWalk == AT_BAT_END_HIT_BY_PITCH) {
            g_Minigame._19A6 = 3;
        }
    }
    g_Strikes.outs = 0;
    g_Strikes.storedOuts = 0;
    g_Minigame._19A5 = 1;
    if (g_Minigame.rosterID != (s8)g_Minigame._19C6 || MG_BYTE(0x18E8 + g_Minigame.rosterID) == 1) {
        if (g_Minigame.toyField_turnNumber >= g_Minigame.toyField_selectedTurns) {
            pauseControl.state = 0;
            SetGameStatus(GAME_STATUS_MVP_END_GAME);
            return;
        }
    }
    if (g_Minigame.toyField_turnNumber < g_Minigame.toyField_selectedTurns &&
        g_Minigame.toyField_turnNumber % 10 == 0) {
        SetGameStatus(GAME_STATUS_INNING_TRANSITION);
    } else {
        SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
    }
}

// .text:0x000DE4FC size:0x114 mapped:0x8071D590
void minigameCalculateRankings(void) {
    int i;
    int j;
    int firstTied;

    for (i = 0; i < 4; i++) {
        MG_BYTE(0x18E8 + i) = 0;
        MG_BYTE(0x18EC + i) = 0;
    }
    for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
        s16 points = g_Minigame.miniGameCurrentPoints[i];
        int rank = 1;
        for (j = 0; j < g_Minigame.miniGameNumberOfParticipants; j++) {
            if (g_Minigame.miniGameCurrentPoints[j] > points) {
                rank++;
            }
        }
        MG_BYTE(0x18E8 + i) = rank;
        MG_BYTE(0x18EC + i) = rank;
    }
    for (firstTied = 0; firstTied < 4; firstTied++) {
        if (MG_BYTE(0x18E8 + firstTied) > 1) {
            break;
        }
    }
    if (firstTied >= 4 && g_Minigame.miniGameNumberOfParticipants > 1) {
        g_Minigame.challenge_minigame_haven_tWonYetIndicator = TRUE;
    } else {
        g_Minigame.challenge_minigame_haven_tWonYetIndicator = FALSE;
    }
}

// .text:0x000DE308 size:0x1F4 mapped:0x8071D39C
void toyFieldAwardPoints(int type) {
    if (type == 20 || type == 21) {
        g_Minigame.miniGameLatestPoints[g_Minigame.rosterID] +=
            g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[type * 3];
        g_Minigame.miniGameLatestPoints[(s8)g_Minigame.minigamePlayerSelectedOrder] +=
            g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[type * 3 + 1];
        g_Minigame.miniGameLatestPoints[g_Fielders[g_Ball.fielderWBallIndex]._020D] +=
            g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[type * 3 + 2];
    } else {
        g_Minigame.miniGameLatestPoints[g_Minigame.rosterID] +=
            g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[type * 3];
        g_Minigame.miniGameLatestPoints[(s8)g_Minigame.minigamePlayerSelectedOrder] +=
            g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[type * 3 + 1];
        g_Minigame.miniGameLatestPoints[TOY_FIELD_FIELDER_SLOT(1)] +=
            g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[type * 3 + 2];
        g_Minigame.miniGameLatestPoints[TOY_FIELD_FIELDER_SLOT(2)] +=
            g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[type * 3 + 2];
    }
    toyFieldRecordPoints();
}

// .text:0x000DDFA0 size:0x368 mapped:0x8071D034
void toyFieldAtBat(void) {
    if (g_Pitcher.pitchTotalTimeCounter <= 0 && pauseControl._1D5 == 0) {
        toyFieldCheckForPause();
    }
    if (pauseControl._1D5 != 0) {
        toyFieldWaitForPause();
    } else {
        atBat_Pitcher();
        atBat_batter();
        miniGameFielding();
        if (g_Minigame.toyFieldBallStateResult2 == 0 && g_Pitcher.strikeOutOrWalk != AT_BAT_END_NONE) {
            if (g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT) {
                g_Minigame.toyFieldBallStateResult2 = TOY_FIELD_RESULT_CAUGHT;
            } else if (g_Pitcher.strikeOutOrWalk == AT_BAT_END_WALK) {
                g_Minigame.toyFieldBallStateResult2 = TOY_FIELD_RESULT_WALK;
            } else {
                g_Minigame.toyFieldBallStateResult2 = TOY_FIELD_RESULT_HIT_BY_PITCH;
            }
        }
        if (g_Minigame.toyFieldBallStateResult2 != 0) {
            toyFieldPoints();
        }
        if (g_Minigame.turnOverStatus != 0) {
            toyFieldAtBatOutcome();
        }
    }
}

// .text:0x000DDF1C size:0x84 mapped:0x8071CFB0
void initializeStgh2(void) {
    setPitcherStatsToInMemPitcher(*(s8*)&g_Minigame.minigamePlayerSelectedOrder);
    setDefaultInMemBall();
    setDefaultInMemPitcher();
    setDefaultInMemBatter();
    setDefaultInMemFielder();
    setDefaultAIValues();
    pauseAnimations();
    Set_803cb848(TRUE);
    pauseStateOnStadiums();
    g_FieldingLogic.playOverCounter = 0;
    g_GameLogic.homeRunWordAnimationCompletedInd = 0;
    g_UnkSimulation_31AC0._05 = 0;
    g_UnkSimulation_31AC0._06 = 4;
}

// .text:0x000DDD60 size:0x1BC mapped:0x8071CDF4
void toyFieldAtBatOutcome(void) {
    if (g_Minigame.turnOverStatus == 1) {
        g_Minigame.turnOverStatus = 2;
        g_GameLogic.CountdownUntilFade = lbl_3_data_1899C[0];
    }
    g_GameLogic.CountdownUntilFade--;
    if (g_Minigame._19A0 != 0 && g_GameLogic.CountdownUntilFade < lbl_3_data_1899C[1]) {
        g_GameLogic.CountdownUntilFade = lbl_3_data_1899C[1];
    }
    if (g_GameLogic.CountdownUntilFade == lbl_3_data_1899C[1] - 10) {
        toyFieldQueueTurnEndText();
    }
    if (g_GameLogic.CountdownUntilFade == 7) {
        changeScene(3, 6);
    }
    if (g_GameLogic.CountdownUntilFade <= 0) {
        toyFieldFinishTurn();
    }
}

// .text:0x000DD9A4 size:0x3BC mapped:0x8071CA38
void toyFieldLiveBall(void) {
    if (g_Minigame.TF_framesSinceHittingPanel != 0 && g_Ball.fielderWBallIndex < 0) {
        if (g_Minigame.TF_framesSinceHittingPanel < lbl_3_data_18C48[6]) {
            g_Minigame.TF_framesSinceHittingPanel++;
        } else if (g_Minigame.TF_ballDespawnedInd == FALSE) {
            g_Minigame.TF_ballDespawnedInd = TRUE;
            toyFieldPlayHazardSound(0x15, 0x2A);
        }
    }
    ballPhysica();
    miniGameDash();
    if (g_Minigame._19CF != 0) {
        if (g_Minigame._19CE == 0) {
            toyFieldApplyBallResult();
        }
    } else if (g_Minigame.toyFieldBallStateResult != 0 && g_Minigame.toyFieldBallStateResult2 == 0) {
        toyFieldApplyBallResult();
    } else if (g_Minigame.toyFieldBallStateResult2 == 0) {
        processToyFieldBallState();
    }
    if (g_Minigame.toyFieldBallStateResult2 != 0) {
        toyFieldPoints();
    }
    if (g_Minigame.turnOverStatus != 0) {
        toyFieldLiveBallOutcome();
    }
}

// .text:0x000DD3FC size:0x5A8 mapped:0x8071C490
void toyFieldLiveBallOutcome(void) {
    if (g_Minigame.turnOverStatus == 1) {
        g_Minigame.turnOverStatus = 2;
        g_GameLogic.CountdownUntilFade = lbl_3_data_1899C[0];
        if (g_Minigame.toyFieldBallStateResult2 == TOY_FIELD_RESULT_FOUL && g_Ball.maybebuntOn2Strikes == 0) {
            g_GameLogic.CountdownUntilFade = lbl_3_data_1899C[2];
        }
    }
    g_GameLogic.CountdownUntilFade--;
    if (g_Minigame._19A0 != 0 && g_Minigame._19CE == 0 && g_GameLogic.CountdownUntilFade < lbl_3_data_1899C[1]) {
        g_GameLogic.CountdownUntilFade = lbl_3_data_1899C[1];
    }
    if (g_Minigame.toyField_coinsRemaining != 0 && g_GameLogic.CountdownUntilFade < lbl_3_data_1899C[1]) {
        g_GameLogic.CountdownUntilFade = lbl_3_data_1899C[1];
    }

    if (g_Minigame._19CE != 0 && g_Minigame._19CE < 3) {
        int i;
        if (g_GameLogic.CountdownUntilFade <= lbl_3_data_1899C[1] - 10) {
            g_GameLogic.CountdownUntilFade++;
        }
        if (g_Minigame._19CE == 1) {
            TOY_FIELD_AWARD_POINTS(lbl_3_data_18BB8[36], lbl_3_data_18BB8[37], lbl_3_data_18BB8[38]);
            toyFieldRecordPoints();
            g_Minigame._19BA = 0;
            g_Minigame._19CE = 2;
            for (i = 0; i < 4; i++) {
                if ((&g_Minigame._1918)[i] != 0) {
                    (&g_Minigame.toyField_runnerOnHome)[i] = 0;
                }
            }
            if (audioFileDescriptors.enableMusic == TRUE) {
                toyFieldPlayHazardSound(0x1A, 0x34);
            }
        }
        SATURATING_INCREMENT(g_Minigame._19BA);
        if (g_Minigame._19BA > lbl_3_data_18C48[3]) {
            g_Minigame._19CE = 3;
        }
    }

    if (g_Minigame.TF_ballDespawnedInd == FALSE && g_Ball.fielderWBallIndex < 0 && g_Ball.deadBallReason == DEAD_BALL_REASON_NONE &&
        g_Ball.AtBat_ContactResult >= 0) {
        if (g_GameLogic.CountdownUntilFade <=
            lbl_3_data_1899C[1] - 10 + specialFielderActionConstants._00[11]) {
            g_GameLogic.CountdownUntilFade++;
        }
    }
    if (g_GameLogic.CountdownUntilFade == lbl_3_data_1899C[1] - 10) {
        if (g_Minigame._19CD == 1 || g_Minigame._19CD == 2 || (g_Minigame._19CD != 3 && g_Minigame.toyField_runsScored != 0)) {
            g_GameLogic.CountdownUntilFade++;
        } else {
            toyFieldQueueTurnEndText();
        }
        SATURATING_INCREMENT(g_Minigame._19BC);
    }
    if (g_GameLogic.CountdownUntilFade == 7) {
        changeScene(3, 6);
    }
    if (g_GameLogic.CountdownUntilFade <= 0) {
        toyFieldFinishTurn();
    }
}

// .text:0x000DD37C size:0x80 mapped:0x8071C410
void toyFieldFinishTurn(void) {
    if (g_Minigame._19CE != 0) {
        fn_3_FBD70();
        fn_3_FBD58();
    }
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    g_GameLogic.hudLoadingRelated = 1;
    trackLastPitchInfo();
    if (g_Minigame.pointsTargetReachedInd == FALSE) {
        toyfieldRelated();
        SetGameStatus(GAME_STATUS_DEFAULT);
    } else {
        SetGameStatus(GAME_STATUS_TRANSITION);
    }
}

// .text:0x000DD1A8 size:0x1D4 mapped:0x8071C23C
void toyFieldInningTransition(void) {
    BOOL done;
    switch (g_GameLogic._125) {
    case 0:
        if (g_Minigame.toyField_turnNumber == 0) {
            if (random_fn_3_9EE24(100) < lbl_3_data_18C48[7] || g_Minigame._1907 == 4) {
                int attempts = 0;
                do {
                    g_Minigame.rosterID = random_fn_3_9EE24(4);
                    attempts++;
                } while (attempts < 100 && g_Minigame.minigameControlStruct[0].battingHandedness[(s8)g_Minigame.rosterID] != 0);
            } else {
                int attempts = 0;
                do {
                    g_Minigame.rosterID = random_fn_3_9EE24(4);
                    attempts++;
                } while (attempts < 100 && g_Minigame.minigameControlStruct[0].battingHandedness[(s8)g_Minigame.rosterID] == 0);
            }
        }
        changeScene(1, 6);
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125 = 1;
        break;
    case 1:
        done = FALSE;
        if (g_GameLogic.FrameCountOfCurrentPitch >= lbl_3_data_18C48[2]) {
            done = TRUE;
        } else if (g_GameLogic.FrameCountOfCurrentAtBat_Copy >= lbl_3_data_18C48[1]) {
            if (checkForButtonPressToSkip(1, INPUT_BUTTON_A | INPUT_BUTTON_START)) {
                done = TRUE;
            }
        }
        if (done) {
            g_GameLogic._125 = 2;
            changeScene(3, 6);
        }
        break;
    case 2:
        if (lbl_8037169C[0x13] != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
            SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
        }
        break;
    }
}

// .text:0x000DD000 size:0x1A8 mapped:0x8071C094
void toyFieldStateTransitionRelated(void) {
    switch (g_GameLogic._125) {
    case 0:
        changeScene(1, 6);
        g_GameLogic._125 = 1;
        break;
    case 1:
        if (g_GameLogic.FrameCountOfCurrentPitch > 1800) {
            g_GameLogic._125 = 2;
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        } else if (g_GameLogic.FrameCountOfCurrentPitch > 300) {
            if (checkForButtonPressToSkip(1, INPUT_BUTTON_A | INPUT_BUTTON_START)) {
                g_GameLogic._125 = 2;
                g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            }
        }
        break;
    case 2:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 30) {
            if (g_Minigame._190A != 0) {
                g_GameLogic._125 = 4;
            } else {
                g_GameLogic._125 = 3;
            }
        }
        break;
    case 3:
        pauseControl._1D1 = 0;
        pauseControl.state = 0;
        SetGameStatus(GAME_STATUS_MINIGAME_POST_MENU);
        break;
    case 4:
        changeScene(4, 6);
        if (lbl_8037169C[0x13] != 0) {
            g_GameLogic._125 = 10;
        }
        break;
    case 5:
        if (g_Minigame.challenge_minigame_haven_tWonYetIndicator != 0) {
            g_d_GameSettings._38 = 0;
        } else {
            g_d_GameSettings._38 = MG_BYTE(0x18E8 + g_d_GameSettings._35);
        }
        g_GameLogic.framesOfExitingToMenu = 1;
        break;
    }
}

// .text:0x000DCF44 size:0xBC mapped:0x8071BFD8
void toyFieldCheckForPause(void) {
    int i;
    for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
        s8 port = g_Minigame.minigameControlStruct[0].characterIndex[i];
        if (port >= 0 && g_Minigame.minigameControlStruct[0].battingHandedness[i] == 0 &&
            (g_Controls[port].newButtonInput & INPUT_BUTTON_START)) {
            pauseControl._1D5 = 1;
            pauseControl.controllerPort = g_Minigame.minigameControlStruct[0].characterIndex[i];
            fn_3_AFD80(0);
            QueueTextToDisplay(14, 0);
            break;
        }
    }
}

// .text:0x000DCED0 size:0x74 mapped:0x8071BF64
void toyFieldWaitForPause(void) {
    SATURATING_INCREMENT(pauseControl._0C);
    highLevelSimulationFlag = TRUE;
    if (pauseControl._0C > 60) {
        fn_3_AFD80(1);
        SetGameStatus(GAME_STATUS_PAUSED);
    } else {
        miniGameFielding();
    }
}

// .text:0x000DCC80 size:0x250 mapped:0x8071BD14
void toyFieldPause(void) {
    SATURATING_INCREMENT(pauseControl._0C);
    SATURATING_INCREMENT(pauseControl._12);
    highLevelSimulationFlag = TRUE;
    pauseControl._04 = g_Controls[pauseControl.controllerPort].buttonInput;
    pauseControl._06 = g_Controls[pauseControl.controllerPort].newButtonInput;
    pauseControl._08 = g_Controls[pauseControl.controllerPort]._08;
    switch (pauseControl.state) {
    case 0:
        pauseControl.cursor = 0;
        pauseControl._1D5 = 0;
        pauseControl._1D0 = 0x11;
        pauseControl.state = 1;
        break;
    case 1:
        pauseControl._12 = 0;
        pauseControl.state = 2;
        break;
    case 2:
        if (pauseControl._12 >= 20) {
            pauseControl.state = 3;
        }
        break;
    case 3:
        toyFieldPauseMenuInput();
        pauseControl._12 = 0;
        break;
    case 4:
        pauseControl._1D9 = 1;
        pauseControl.state = 5;
        break;
    case 5:
        if (pauseControl._1D9 == 3) {
            SetGameStatus(GAME_STATUS_AT_BAT);
        }
        break;
    case 6:
        pauseControl._1D9 = 1;
        pauseControl.state = 7;
        break;
    case 7:
        if (pauseControl._1D9 == 3) {
            pauseControl._220 = 2;
            pauseControl.state = 0;
            SetGameStatus(GAME_STATUS_HOW_TO_PLAY_SCREEN);
        }
        break;
    case 8:
        fn_3_107E80();
        break;
    case 9:
        switch (exitMenu_main()) {
        case 1:
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            pauseControl.state = 10;
            break;
        case 2:
            pauseControl.state = 3;
            break;
        }
        break;
    case 10:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 45) {
            changeScene(4, 6);
        }
        if (lbl_8037169C[0x13] != 0) {
            pauseControl._1D9 = 2;
            g_d_GameSettings._13 = 1;
            fn_8004CC18();
            g_GameLogic.framesOfExitingToMenu = 1;
        }
        break;
    }
}

// .text:0x000DCA68 size:0x218 mapped:0x8071BAFC
void toyFieldPauseMenuInput(void) {
    if (pauseControl._06 & INPUT_BUTTON_START) {
        pauseControl.state = 4;
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
    } else if (pauseControl._06 & INPUT_BUTTON_A) {
        if (pauseControl.cursor == 0) {
            pauseControl.state = 4;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (pauseControl.cursor == 1) {
            pauseControl.state = 8;
            pauseControl._1D4 = 0;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (pauseControl.cursor == 2) {
            pauseControl.state = 6;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (pauseControl.cursor == 3) {
            fn_3_5B408();
            pauseControl.state = 9;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        }
    } else if (pauseControl._06 & INPUT_BUTTON_B) {
        if (pauseControl.cursor != 0) {
            pauseControl.cursor = 0;
        } else {
            pauseControl.state = 4;
        }
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
    } else if (pauseControl._08 & INPUT_BUTTON_UP) {
        if (pauseControl.cursor > 0) {
            pauseControl.cursor--;
        } else {
            pauseControl.cursor = 3;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (pauseControl._08 & INPUT_BUTTON_DOWN) {
        pauseControl.cursor++;
        if (pauseControl.cursor >= 4) {
            pauseControl.cursor = 0;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
}

// .text:0x000DC6E8 size:0x380 mapped:0x8071B77C
void toyFieldPostMenu(void) {
    SATURATING_INCREMENT(pauseControl._12);
    switch (pauseControl.state) {
    case 0:
        pauseControl.cursor = 0;
        pauseControl._1D0 = 0x12;
        pauseControl.state = 1;
        break;
    case 1:
        pauseControl._12 = 0;
        pauseControl.state = 2;
        break;
    case 2:
        if (pauseControl._12 >= 20) {
            pauseControl.state = 3;
        }
        break;
    case 3:
        toyFieldPostMenuInput();
        pauseControl._12 = 0;
        break;
    case 4:
        if (pauseControl._12 >= 20) {
            changeScene(3, 6);
        }
        if (lbl_8037169C[0x13] != 0) {
            pauseControl.state = 5;
        }
        break;
    case 5: {
        BOOL start;
        hugeAnimStruct[0x307A] = 0;
        pauseControl._1D9 = 2;
        start = FALSE;
        if (pauseControl.cursor == 0) {
            SetGameStatus(GAME_STATUS_GAME_START_MOVIE);
            g_Minigame._1A38 = 1;
            start = TRUE;
        } else if (pauseControl.cursor == 1) {
            g_Minigame._19DF = 30;
            SetGameStatus(GAME_STATUS_TOY_STADIUM_LOAD);
            start = TRUE;
        }
        if (start) {
            initializeMinigameData();
            fn_3_15F998();
            fn_3_147DFC();
            if (pauseControl.cursor == 1) {
                mm_UnloadModels();
            }
        }
        break;
    }
    case 9:
        switch (((int (*)(u16))exitMenu_main)(g_Controls[pauseControl.controllerPort].newButtonInput)) {
        case 1:
            fn_3_15F998();
            fn_3_147DFC();
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            pauseControl.state = 10;
            break;
        case 2:
            pauseControl.state = 3;
            break;
        }
        break;
    case 10:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 45) {
            changeScene(4, 6);
        }
        if (lbl_8037169C[0x13] != 0) {
            pauseControl._1D9 = 2;
            fn_8004CC18();
            g_GameLogic.framesOfExitingToMenu = 1;
        }
        break;
    }
}

// .text:0x000DC5A4 size:0x144 mapped:0x8071B638
void toyFieldPostMenuInput(void) {
    int pressed = checkForButtonPressToSkip(1, INPUT_BUTTON_A);
    if (pressed) {
        pauseControl.controllerPort = pressed - 1;
        if (pauseControl.cursor == 2) {
            fn_3_5B408();
            pauseControl.state = 9;
        } else {
            pauseControl.state = 4;
        }
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
    } else if (checkForButtonPressToSkip(1, INPUT_BUTTON_UP)) {
        if (pauseControl.cursor != 0) {
            pauseControl.cursor--;
        } else {
            pauseControl.cursor = 2;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (checkForButtonPressToSkip(1, INPUT_BUTTON_DOWN)) {
        pauseControl.cursor++;
        if (pauseControl.cursor >= 3) {
            pauseControl.cursor = 0;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
}

// .text:0x000DC380 size:0x224 mapped:0x8071B414
void processToyFieldBallState(void) {
    if (g_Ball.framesSinceLastBounce == 0 && g_Ball.ballBounceState != 3) {
        s32 code = g_Ball.collisionCode;
        if (code >= 0x80) {
            code -= 0x80;
        }
        if (code >= 0x70 && code < 0x79) {
            g_Minigame.maybeTFCollisionResultState = (lbl_3_data_189AC - 0x70)[code];
        }
    }

    if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FOUL) {
        g_Minigame.toyFieldBallStateResult = TOY_FIELD_RESULT_FOUL;
    } else if (g_Minigame.toyFieldStateInd_collisionRelated != 0) {
        g_Minigame.toyFieldBallStateResult = (lbl_3_data_189AC - 0x70)[g_Minigame.toyFieldStateInd_collisionRelated];
    } else if (g_Ball.deadBallReason != DEAD_BALL_REASON_NONE) {
        if (g_Ball.deadBallReason == DEAD_BALL_REASON_HOME_RUN) {
            g_Minigame.toyFieldBallStateResult = TOY_FIELD_RESULT_HOMERUN;
        } else if (g_Ball.deadBallReason == DEAD_BALL_REASON_GROUND_RULE_DOUBLE) {
            g_Minigame.toyFieldBallStateResult = TOY_FIELD_RESULT_GROUND_RULE_DOUBLE;
        } else {
            g_Minigame.toyFieldBallStateResult = TOY_FIELD_RESULT_FOUL;
        }
        g_Minigame.turnOverStatus = 1;
    } else if (g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_IN_AIR) {
        if (g_Ball.ballState == BALL_STATE_HELD) {
            InMemFielder* fielder = &g_Fielders[g_Ball.fielderWBallIndex];
            if (fielder->hitKnockbackCountdown != 0 || fielder->animationRelatedInd != 0) {
                return;
            }
        } else if (!(g_Ball.ballVelocity < 0.003f || g_Ball.groundRuleDoubleInd != 0 ||
                     g_Ball.ballStoppingCode1ReallySlow2Stopped == 2)) {
            return;
        }
        if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT) {
            g_Minigame.toyFieldBallStateResult = TOY_FIELD_RESULT_CAUGHT;
        } else {
            if (g_Minigame.maybeTFCollisionResultState == 0) {
                if (foul_checkIfFoul(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z)) {
                    g_Minigame.toyFieldBallStateResult = TOY_FIELD_RESULT_FOUL;
                } else {
                    g_Minigame.toyFieldBallStateResult = TOY_FIELD_RESULT_CAUGHT;
                }
            } else {
                g_Minigame.toyFieldBallStateResult = g_Minigame.maybeTFCollisionResultState;
            }
            g_Minigame.lastKnownBallPosX = g_Ball.AtBat_Contact_BallPos.x;
            g_Minigame.lastKnownBallPosZ = g_Ball.AtBat_Contact_BallPos.z;
            g_Minigame.TF_framesSinceHittingPanel = 1;
        }
    }
}

// .text:0x000DC240 size:0x140 mapped:0x8071B2D4
void toyFieldApplyBallResult(void) {
    g_Minigame.toyFieldBallStateResult2 = g_Minigame.toyFieldBallStateResult;
    if (fn_3_E5924()) {
        if (g_Minigame._19CF == 0) {
            g_Minigame.toyFieldBallStateResult2 = 12;
        }
        if (g_Minigame._19CF > 60) {
            g_Minigame._19CE = 1;
        } else if (g_Minigame._19CF < 0xFE) {
            g_Minigame._19CF++;
        } else {
            g_Minigame._19CF = 0xFF;
        }
    } else if (g_Minigame.toyFieldBallStateResult2 == TOY_FIELD_RESULT_CAUGHT || g_Ball.maybebuntOn2Strikes != 0) {
        if (g_Ball.maybebuntOn2Strikes == 0) {
            QueueTextToDisplay(1, 0);
        }
        g_Minigame._19C6 = g_Minigame.minigamePlayerSelectedOrder;
        if (g_Ball.fielderWBallIndex >= 0) {
            g_Minigame._19C6 = g_Fielders[g_Ball.fielderWBallIndex]._020D;
        }
    } else if (g_Minigame.toyFieldBallStateResult2 == TOY_FIELD_RESULT_FOUL) {
        foulBall();
    } else if (g_Minigame.toyFieldBallStateResult2 == TOY_FIELD_RESULT_HOMERUN) {
        QueueTextToDisplay(15, 0);
    }
}

// .text:0x000DA834 size:0x1A0C mapped:0x807198C8
void toyFieldPoints(void) {
    int i;
    int j;
    SATURATING_INCREMENT(g_Minigame.framesSincePanelHit);
    if (g_Minigame.framesSincePanelHit <= 1) {
        if (g_Minigame.toyFieldBallStateResult2 == TOY_FIELD_RESULT_FOUL && g_Ball.maybebuntOn2Strikes == 0) {
            g_Minigame.turnOverStatus = 1;
            TOY_FIELD_AWARD_POINTS(lbl_3_data_18BB8[33], lbl_3_data_18BB8[34], lbl_3_data_18BB8[35]);
            toyFieldRecordPoints();
        } else {
            g_Minigame.panelHitInd = TRUE;
            if (g_Minigame.toyFieldBallStateResult2 >= TOY_FIELD_RESULT_FOUL && g_Minigame.toyFieldBallStateResult2 <= TOY_FIELD_RESULT_HIT_BY_PITCH) {
                g_Minigame.turnOverStatus = 1;
                switch (g_Minigame.toyFieldBallStateResult2) {
                case TOY_FIELD_RESULT_FOUL:
                    TOY_FIELD_AWARD_POINTS(lbl_3_data_18BB8[66], lbl_3_data_18BB8[67], lbl_3_data_18BB8[68]);
                    toyFieldRecordPoints();
                    break;
                case TOY_FIELD_RESULT_CAUGHT:
                    if (g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT || g_Ball.maybebuntOn2Strikes != 0) {
                        TOY_FIELD_AWARD_POINTS(lbl_3_data_18BB8[66], lbl_3_data_18BB8[67], lbl_3_data_18BB8[68]);
                        toyFieldRecordPoints();
                    } else if (g_Minigame.toyFieldStateInd_collisionRelated == 0x71) {
                        TOY_FIELD_AWARD_POINTS(lbl_3_data_18BB8[27], lbl_3_data_18BB8[28], lbl_3_data_18BB8[29]);
                        toyFieldRecordPoints();
                    } else {
                        TOY_FIELD_AWARD_POINTS(lbl_3_data_18BB8[30], lbl_3_data_18BB8[31], lbl_3_data_18BB8[32]);
                        toyFieldRecordPoints();
                    }
                    break;
                case TOY_FIELD_RESULT_SINGLE:
                    TOY_FIELD_AWARD_POINTS(lbl_3_data_18BB8[0], lbl_3_data_18BB8[1], lbl_3_data_18BB8[2]);
                    toyFieldRecordPoints();
                    break;
                case TOY_FIELD_RESULT_GROUND_RULE_DOUBLE:
                    TOY_FIELD_AWARD_POINTS(lbl_3_data_18BB8[3], lbl_3_data_18BB8[4], lbl_3_data_18BB8[5]);
                    toyFieldRecordPoints();
                    break;
                case TOY_FIELD_RESULT_TRIPLE:
                    TOY_FIELD_AWARD_POINTS(lbl_3_data_18BB8[6], lbl_3_data_18BB8[7], lbl_3_data_18BB8[8]);
                    toyFieldRecordPoints();
                    break;
                case TOY_FIELD_RESULT_HOMERUN:
                    if (g_Ball.deadBallReason == DEAD_BALL_REASON_HOME_RUN) {
                        TOY_FIELD_AWARD_POINTS(lbl_3_data_18BB8[12], lbl_3_data_18BB8[13], lbl_3_data_18BB8[14]);
                        toyFieldRecordPoints();
                    } else {
                        TOY_FIELD_AWARD_POINTS(lbl_3_data_18BB8[9], lbl_3_data_18BB8[10], lbl_3_data_18BB8[11]);
                        toyFieldRecordPoints();
                    }
                    break;
                case TOY_FIELD_RESULT_WALK:
                    TOY_FIELD_AWARD_POINTS(lbl_3_data_18BB8[69], lbl_3_data_18BB8[70], lbl_3_data_18BB8[71]);
                    toyFieldRecordPoints();
                    break;
                case TOY_FIELD_RESULT_HIT_BY_PITCH:
                    TOY_FIELD_AWARD_POINTS(lbl_3_data_18BB8[69], lbl_3_data_18BB8[70], lbl_3_data_18BB8[71]);
                    toyFieldRecordPoints();
                    break;
                }
                if (g_Minigame.toyFieldBallStateResult2 >= TOY_FIELD_RESULT_SINGLE && g_Minigame.toyFieldBallStateResult2 <= TOY_FIELD_RESULT_HOMERUN) {
                    toyFieldPlayHazardSound(0, 0);
                }
                if (g_Minigame.toyFieldBallStateResult2 == TOY_FIELD_RESULT_CAUGHT || g_Ball.maybebuntOn2Strikes != 0) {
                    if (g_Ball.fielderWBallIndex >= 0) {
                        g_Minigame._19C6 = g_Fielders[g_Ball.fielderWBallIndex]._020D;
                    } else {
                        g_Minigame._19C6 = g_Minigame.minigamePlayerSelectedOrder;
                    }
                }
            } else if (g_Minigame.toyFieldBallStateResult2 == 0xB) {
                toyFieldRelated();
                fn_3_D9868();
                g_Minigame.TF_framesSinceHittingPanel = 1;
            } else if (g_Minigame.toyFieldBallStateResult2 == 9 || g_Minigame.toyFieldBallStateResult2 == 10) {
                if (g_Minigame.lastKnownBallPosX < 0.0f) {
                    toyFieldSpawnCoins(30, 6);
                } else {
                    toyFieldSpawnCoins(30, 4);
                }
                g_Minigame.TF_framesSinceHittingPanel = 1;
                g_Minigame._199E = 0;
            } else {
                g_Minigame.turnOverStatus = 1;
            }

            if (g_Minigame.toyFieldBallStateResult2 >= TOY_FIELD_RESULT_SINGLE && g_Minigame.toyFieldBallStateResult2 <= TOY_FIELD_RESULT_HOMERUN) {
                int shift = g_Minigame.toyFieldBallStateResult2 - (TOY_FIELD_RESULT_SINGLE - 1);
                for (i = 0; i < shift; i++) {
                    if (g_Minigame.toyField_runnerOnThird != 0) {
                        g_Minigame.toyField_runsScored++;
                    }
                    for (j = 3; j > 0; j--) {
                        (&g_Minigame.toyField_runnerOnHome)[j] = (&g_Minigame.toyField_runnerOnHome)[j - 1];
                        (&g_Minigame.toyField_runnerOnHome)[j - 1] = 0;
                    }
                }
                for (i = 0; i < 4; i++) {
                    if ((&g_Minigame.toyField_runnerBase0)[i] >= 0) {
                        (&g_Minigame.toyField_runnerBase0)[i] += shift;
                        if ((&g_Minigame.toyField_runnerBase0)[i] >= 4) {
                            (&g_Minigame.toyField_runnerBase0)[i] = 4;
                        }
                    }
                }
            }

            if (g_Minigame.toyFieldBallStateResult2 == TOY_FIELD_RESULT_WALK || g_Minigame.toyFieldBallStateResult2 == TOY_FIELD_RESULT_HIT_BY_PITCH) {
                int count;
                if (g_Minigame.toyField_runnerOnThird != 0) {
                    g_Minigame.toyField_runsScored++;
                }
                for (count = 1; count < 4; count++) {
                    if ((&g_Minigame.toyField_runnerOnHome)[count] == 0) {
                        break;
                    }
                }
                for (j = count; j >= 1; j--) {
                    (&g_Minigame.toyField_runnerOnHome)[j] = (&g_Minigame.toyField_runnerOnHome)[j - 1];
                    (&g_Minigame.toyField_runnerOnHome)[j - 1] = 0;
                }
                for (i = 0; i < 4; i++) {
                    if ((&g_Minigame.toyField_runnerBase0)[i] < 0) {
                        break;
                    }
                    (&g_Minigame.toyField_runnerBase0)[i]++;
                    if ((&g_Minigame.toyField_runnerBase0)[i] >= 4) {
                        (&g_Minigame.toyField_runnerBase0)[i] = 4;
                    }
                }
            }

            for (i = 0; i < 4; i++) {
                if (g_Ball.fielderWBallIndex >= 0 && (s8)g_Minigame.minigameFielderIndex[i] == g_Ball.fielderWBallIndex) {
                    if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT) {
                        g_Minigame.miniGameLatestPoints[g_Minigame.rosterID] +=
                            g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[60];
                        g_Minigame.miniGameLatestPoints[(s8)g_Minigame.minigamePlayerSelectedOrder] +=
                            g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[61];
                        g_Minigame.miniGameLatestPoints[g_Fielders[g_Ball.fielderWBallIndex]._020D] +=
                            g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[62];
                        toyFieldRecordPoints();
                    } else {
                        g_Minigame.miniGameLatestPoints[g_Minigame.rosterID] +=
                            g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[63];
                        g_Minigame.miniGameLatestPoints[(s8)g_Minigame.minigamePlayerSelectedOrder] +=
                            g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[64];
                        g_Minigame.miniGameLatestPoints[g_Fielders[g_Ball.fielderWBallIndex]._020D] +=
                            g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[65];
                        toyFieldRecordPoints();
                    }
                    break;
                }
            }
            g_Minigame.pointsTargetReachedInd = TRUE;
        }
    } else {
        if (g_Minigame.toyFieldBallStateResult2 == 0xB) {
            if (g_Minigame._1934 == 0) {
                SATURATING_INCREMENT(g_Minigame._18B8);
                for (i = 0; i < 3; i++) {
                    u8 state = (&g_Minigame._1927)[i];
                    if (state == 0) {
                        if (g_Minigame._18B8 > lbl_3_data_189B8[i]) {
                            (&g_Minigame._1927)[i] = 1;
                        }
                    } else if (state == 1) {
                        if (i == 0) {
                            if (g_Minigame._18B8 > lbl_3_data_189B8[3]) {
                                (&g_Minigame._1927)[i] = 2;
                            }
                        } else if (i == 2) {
                            if ((&g_Minigame._1930)[i] == 3) {
                                (&g_Minigame._1927)[i] = 2;
                            }
                        } else {
                            if ((&g_Minigame._1930)[i] >= 2) {
                                (&g_Minigame._1927)[i] = 2;
                            }
                        }
                    }
                }
            } else if (g_Minigame._1934 != 1) {
                if (g_Minigame._1934 == 2) {
                    fn_3_D8CD0();
                    g_Minigame._1934 = 3;
                } else {
                    if (MG_BYTE(0x192D) == 6) {
                        g_Minigame._19A6 = 3;
                        if (g_Minigame._18BA == 1) {
                            fn_3_E8AC8();
                        }
                    }
                    SATURATING_INCREMENT(g_Minigame._18BA);
                }
            }
        }
        if (g_Minigame.toyFieldBallStateResult2 == 9 || g_Minigame.toyFieldBallStateResult2 == 10) {
            toyFieldUpdateCoins();
        }
    }
}

// .text:0x000DA640 size:0x1F4 mapped:0x807196D4
void toyFieldSpawnCoins(int count, int type) {
    int i;
    f32 spread;

    g_Minigame.toyField_coinsRemaining = count;
    g_Minigame.panelHitInd = TRUE;
    g_Minigame.wallBall_coinsVisibleFrameCounter = 0;
    spread = lbl_3_data_18AC8[type][2];
    if (count >= 20) {
        spread = lbl_3_data_18AC8[type][3];
    }
    for (i = 0; i < count; i++) {
        int radiusMilli;
        f32 radius;
        f32 cosine;
        f32 sine;
        f32 speed;
        TOY_FIELD_COIN_VISIBLE(i) = TRUE;
        TOY_FIELD_COIN_POSITION(i).y = 0.8f;
        radiusMilli = rand() % (int)(1000.0f * spread);
        radius = radiusMilli * 0.001f;
        getComponentsFromSAng((s16)normalizeAngle(rand() % SANG_MAX_ANGLE), &cosine, &sine);
        TOY_FIELD_COIN_POSITION(i).x = cosine * radius + lbl_3_data_18AC8[type][0];
        TOY_FIELD_COIN_POSITION(i).z = sine * radius + lbl_3_data_18AC8[type][1];
        speed = RandomF32_Game_Range(0.0f, 0.03f);
        TOY_FIELD_COIN_VELOCITY(i).x = cosine * speed;
        TOY_FIELD_COIN_VELOCITY(i).z = sine * speed;
        TOY_FIELD_COIN_VELOCITY(i).y = RandomF32_Game_Range(0.08f, 0.12f);
    }
}

// .text:0x000D9EA0 size:0x7A0 mapped:0x80718F34
void toyFieldUpdateCoins(void) {
    int i;

    if (g_Minigame.toyField_coinsRemaining != 0) {
        SATURATING_INCREMENT(g_Minigame.wallBall_coinsVisibleFrameCounter);
        for (i = 0; i < TOY_FIELD_COIN_COUNT; i++) {
            if (TOY_FIELD_COIN_VISIBLE(i) != 0) {
                if (g_Minigame.wallBall_coinsVisibleFrameCounter > lbl_3_data_18BB0[g_Minigame._199E * 2]) {
                    TOY_FIELD_COIN_VISIBLE(i) = FALSE;
                } else {
                    TOY_FIELD_COIN_VELOCITY(i).y -= TOY_FIELD_COIN_GRAVITY;
                    TOY_FIELD_COIN_VELOCITY(i).x *= TOY_FIELD_COIN_DAMPING;
                    TOY_FIELD_COIN_VELOCITY(i).y *= TOY_FIELD_COIN_DAMPING;
                    TOY_FIELD_COIN_VELOCITY(i).z *= TOY_FIELD_COIN_DAMPING;
                    TOY_FIELD_COIN_POSITION(i).x += TOY_FIELD_COIN_VELOCITY(i).x;
                    TOY_FIELD_COIN_POSITION(i).y += TOY_FIELD_COIN_VELOCITY(i).y;
                    TOY_FIELD_COIN_POSITION(i).z += TOY_FIELD_COIN_VELOCITY(i).z;
                    if (TOY_FIELD_COIN_POSITION(i).y <= TOY_FIELD_COIN_FLOOR) {
                        TOY_FIELD_COIN_POSITION(i).y = TOY_FIELD_COIN_FLOOR;
                        TOY_FIELD_COIN_VELOCITY(i).y = -TOY_FIELD_COIN_VELOCITY(i).y;
                        TOY_FIELD_COIN_VELOCITY(i).x *= TOY_FIELD_COIN_BOUNCE;
                        TOY_FIELD_COIN_VELOCITY(i).y *= TOY_FIELD_COIN_BOUNCE;
                        TOY_FIELD_COIN_VELOCITY(i).z *= TOY_FIELD_COIN_BOUNCE;
                    }
                }
            }
        }

        for (i = 0; i < TOY_FIELD_COIN_COUNT; i++) {
            if (TOY_FIELD_COIN_VISIBLE(i) != 0) {
                f32 nearest0;
                f32 nearest1;
                f32 nearest2;
                f32 distance;
                int slot;
                nearest1 = nearest2 = 999.9f;
                nearest0 = toyFieldCoinDistanceToFielder(i, 0);
                if (TOY_FIELD_FIELDER_SLOT(1) >= 0) {
                    nearest1 = toyFieldCoinDistanceToFielder(i, 1);
                }
                if (TOY_FIELD_FIELDER_SLOT(2) >= 0) {
                    nearest2 = toyFieldCoinDistanceToFielder(i, 2);
                }
                if (nearest0 < nearest2) {
                    if (nearest0 < nearest1) {
                        slot = TOY_FIELD_FIELDER_SLOT(0);
                        distance = nearest0;
                    } else {
                        slot = TOY_FIELD_FIELDER_SLOT(1);
                        distance = nearest1;
                    }
                } else if (nearest1 < nearest2) {
                    slot = TOY_FIELD_FIELDER_SLOT(1);
                    distance = nearest1;
                } else {
                    slot = TOY_FIELD_FIELDER_SLOT(2);
                    distance = nearest2;
                }
                if (distance < lbl_3_data_18B88[TOY_FIELD_FIELDER(slot).Weight]) {
                    TOY_FIELD_COIN_VISIBLE(i) = FALSE;
                    g_Minigame.miniGameCurrentPoints[slot] +=
                        lbl_3_data_18C48[8] * g_Minigame.toyField_pointMultiplier;
                    if (--g_Minigame.toyField_coinsRemaining == 0 && g_Minigame.turnOverStatus == 0) {
                        g_Minigame.turnOverStatus = 1;
                    }
                    if (sound_crowd_EffectsStruct._30 == 0) {
                        toyFieldPlayHazardSound(0xC, 0x18);
                        sound_crowd_EffectsStruct._30 = lbl_3_data_88DC;
                    }
                }
            }
        }

        if (g_Minigame.wallBall_coinsVisibleFrameCounter > lbl_3_data_18BB0[g_Minigame._199E * 2]) {
            if (g_Minigame.turnOverStatus == 0) {
                g_Minigame.turnOverStatus = 1;
            }
            if (g_Minigame.toyField_coinsRemaining != 0) {
                g_Minigame.miniGameLatestPoints[g_Minigame.rosterID] =
                    g_Minigame.toyField_coinsRemaining * g_Minigame.toyField_pointMultiplier;
                g_Minigame.minigamePoints_current_Latest[g_Minigame.rosterID][0] =
                    g_Minigame.miniGameCurrentPoints[g_Minigame.rosterID];
                g_Minigame.minigamePoints_current_Latest[g_Minigame.rosterID][1] =
                    g_Minigame.miniGameLatestPoints[g_Minigame.rosterID];
                g_Minigame.toyField_coinsRemaining = 0;
            }
        }
    }
}
