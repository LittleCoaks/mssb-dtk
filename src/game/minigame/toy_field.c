#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_toyField
#include "game/minigame/toy_field.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/math/game_math.h"
#include "game/match_setup/pause_menu.h"
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
#include "game/match_setup/at_bat_setup.h"
#include "game/minigame/minigame_fielder_anim.h"
#include "game/hud/stadium_draw.h"
#include "game/minigame/minigame_effects.h"
#include "game/minigame/pitching_machine.h"
#include "musyx/musyx.h"
#include "Dolphin/stl.h"
#include "stl/stdlib.h"
#include "Unknown/File_0x800204cc.h"
#include "Unknown/File_0x8004abd8.h"
#include "Unknown/File_0x8004cc18.h"
#include "Unknown/File_0x80021410.h"
#include "Unknown/File_0x800203e0.h"
#include "Unknown/File_0x80052f98.h"
#include "Unknown/File_0x800b0a14.h"


extern u8 lbl_800EFBA4[0x10];
extern u8 lbl_8037169C[0x1C];
extern u8 hugeAnimStruct[0x3154];
extern u8 highLevelSimulationFlag[3];
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
extern void fn_3_15F998(void);
extern void minigameCharLoadQueueUpdate(void);
extern void toyFieldStadiumLoad(void);
extern void toyFieldCharSelectSwitcher(void);
extern void minigameReadySwitcher(void);
extern void minigameEndSwitcher(void);
extern void minigameResultsSwitcher(void);
extern void howToPlayScreen(void);
extern int fn_3_59AE4(void);
extern void loadToyFieldCharacterFiles(void);
extern int fn_80016F7C(void);
extern int fn_3_90DD8(void);
extern int fn_3_FD9FC(void);
extern u8 lbl_3_data_21270;
extern u8 us80893314[8];
extern u8 animRelated[0x124];
extern void minigamePauseHelpUpdate(void);
extern void minigame_rankPlayers(u8 (*order)[2], int mode);
extern void fn_3_AFD80(int arg0);
extern void starMissionsMinigamesSpecialAction(int missionType, int points, int barrelsHit);
extern struct {
    u8 _00[0x40];
    s16 humanTeam;
} lbl_3_common_bss_37400;
extern void fn_3_FBD58(void);
extern void fn_3_FBD70(void);

u8 minigamePauseMenuActions[20] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x02,
    0x03, 0x04, 0x05, 0x00, 0x00, 0x02, 0x03, 0x05,
    0x00, 0x00, 0x00, 0x00,
};
u8 postMinigameMenuActions[16] = {
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
u8 minigameParticipantCounts[36] = {
    0x04, 0x04, 0x04, 0x04, 0x04, 0x01, 0x01, 0x01,
    0x01, 0x02, 0x04, 0x04, 0x04, 0x01, 0x04, 0x01,
    0x01, 0x01, 0x01, 0x02, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x00,
};
u8 minigameChallengeOpponentCounts[8] = {
    0x03, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00,
};
u8 minigameChallengeOpponentPools[44] = {
    0x03, 0x13, 0x30, 0x32, 0xFF, 0xFF, 0xFF, 0x00,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x04, 0x0C, 0x2A, 0x14,
    0x2B, 0xFF, 0xFF, 0x05, 0x10, 0x2C, 0x2D, 0x2E,
    0x2F, 0xFF, 0x00, 0x00,
};
u8 minigameChallengeAIStrength[8] = {
    0x00, 0x01, 0x02, 0x03, 0x03, 0x00, 0x00, 0x00,
};
u8 lbl_3_data_18980[4] = {
    2, 0, 0, 0,
};
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
s16 lbl_3_data_189C4[3][7] = {
    { 0, 2, 3, 4, 5, 6, 7 },
    { 5, 0, 3, 2, 7, 4, 6 },
    { 4, 0, 6, 3, 5, 7, 2 },
};
u8 lbl_3_data_189F0[3][3][3][8] = {
    {
        {
            { 20, 0, 13, 20, 0, 2, 5, 40 },
            { 20, 0, 15, 15, 12, 3, 10, 25 },
            { 30, 0, 25, 0, 20, 5, 10, 10 },
        },
        {
            { 10, 0, 5, 10, 0, 0, 5, 70 },
            { 20, 0, 15, 15, 12, 3, 10, 25 },
            { 30, 0, 25, 0, 20, 5, 10, 10 },
        },
        {
            { 5, 0, 5, 5, 0, 0, 5, 80 },
            { 20, 0, 15, 15, 12, 3, 10, 25 },
            { 30, 0, 25, 0, 20, 5, 10, 10 },
        },
    },
    {
        {
            { 20, 0, 13, 20, 0, 2, 5, 40 },
            { 20, 0, 15, 15, 12, 3, 10, 25 },
            { 30, 0, 25, 0, 20, 5, 10, 10 },
        },
        {
            { 10, 0, 5, 10, 0, 0, 5, 70 },
            { 20, 0, 15, 15, 12, 3, 10, 25 },
            { 30, 0, 25, 0, 20, 5, 10, 10 },
        },
        {
            { 5, 0, 5, 5, 0, 0, 5, 80 },
            { 20, 0, 15, 15, 12, 3, 10, 25 },
            { 30, 0, 25, 0, 20, 5, 10, 10 },
        },
    },
    {
        {
            { 20, 0, 11, 30, 0, 0, 0, 39 },
            { 15, 0, 15, 30, 30, 0, 0, 10 },
            { 20, 0, 20, 30, 30, 0, 0, 0 },
        },
        {
            { 10, 0, 10, 20, 0, 0, 10, 50 },
            { 15, 0, 5, 20, 40, 0, 10, 10 },
            { 10, 0, 10, 10, 50, 10, 10, 0 },
        },
        {
            { 10, 0, 10, 15, 0, 0, 5, 60 },
            { 15, 0, 5, 20, 30, 5, 10, 10 },
            { 10, 0, 10, 10, 50, 10, 10, 0 },
        },
    },
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
s16 minigameTuningConstants[10] = {
    100, 180, 600, 279, 3, 1, 60, 70, 2, 0,
};

#define TOY_FIELD_COIN_COUNT 100
#define MG_BYTE(offset) (*((u8*)&g_Minigame + (offset)))
#define MG_SBYTE(offset) (*((s8*)&g_Minigame + (offset)))

#define SATURATING_INCREMENT(counter) \
    if ((counter) < 0x7FFE) {         \
        (counter)++;                  \
    } else {                          \
        (counter) = 0x7FFF;           \
    }

#define SATURATING_BYTE_INCREMENT(counter) \
    if ((counter) < 0xFE) {                 \
        (counter)++;                        \
    } else {                                \
        (counter) = 0xFF;                   \
    }

#define TOY_FIELD_COIN_GRAVITY (lbl_3_data_18B9C[0])
#define TOY_FIELD_COIN_DAMPING (lbl_3_data_18B9C[1])
#define TOY_FIELD_COIN_BOUNCE (lbl_3_data_18B9C[2])
#define TOY_FIELD_COIN_FLOOR (lbl_3_data_18B9C[3])
#define TOY_FIELD_COIN_VISIBLE(i) ((&g_Minigame.wallBall_coinsVisibleInd)[i])
#define TOY_FIELD_COIN_POSITION(i) ((&g_Minigame.wallBall_coinCoordinates)[i])
#define TOY_FIELD_COIN_VELOCITY(i) ((&g_Minigame.wallBall_coinVelocity)[i])
#define TOY_FIELD_FIELDER_SLOT(i) (g_Minigame.playerSlots.participantSlot[(i)])
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
    if (turn >= selectedTurns && g_Minigame.playerSlots.rank[g_Minigame.rosterID] == 1) {
        QueueTextToDisplay(13, 0);
    } else if ((u8)g_Minigame.rosterID != (s8)g_Minigame.toyField_turnPlayer) {
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

#define TOY_FIELD_ROLE_HISTORY(i) (g_Minigame.toyField_roleRecord[(i)][0])
#define TOY_FIELD_ROLE_STREAK(i) (g_Minigame.toyField_roleRecord[(i)][1])

static inline void toyFieldTrackRole(int i, u32 role) {
    if (TOY_FIELD_ROLE_HISTORY(i) == role) {
        SATURATING_BYTE_INCREMENT(TOY_FIELD_ROLE_STREAK(i));
    } else {
        TOY_FIELD_ROLE_HISTORY(i) = role;
        TOY_FIELD_ROLE_STREAK(i) = 1;
    }
}

// .text:0x000DFBAC size:0xABC mapped:0x8071EC40
void toyfieldSimulation(void) {
    int i;
    s16* latest;
    g_GameLogic.hudElementLoadingInd = 0;
    g_GameLogic.hudLoadingRelated = 0;
    latest = (s16*)&MG_BYTE(0x1898);
    g_Minigame._19A1 = 0;
    g_Minigame._1925 = 0;
    latest[0] = 0;
    latest[1] = 0;
    latest[2] = 0;
    latest[3] = 0;
    SATURATING_INCREMENT(g_Ball.totalFramesAtPlay);
    switch (g_GameLogic.gameStatus) {
    case GAME_STATUS_0x1B:
        toyFieldWaitForCharacterLoad();
        break;
    case GAME_STATUS_TOY_STADIUM_LOAD:
        toyFieldStadiumLoad();
        break;
    case GAME_STATUS_TOY_STADIUM_CHARACTER_SELECT:
        toyFieldCharSelectSwitcher();
        break;
    case GAME_STATUS_MINIGAME_READY:
        minigameReadySwitcher();
        break;
    case GAME_STATUS_MINIGAME_POST_MENU:
        toyFieldPostMenu();
        break;
    case GAME_STATUS_0x25:
        toyFieldApplyGameSettings();
        break;
    case GAME_STATUS_DEFAULT:
        initializeToyFieldSomething();
        break;
    case GAME_STATUS_AT_BAT:
        toyFieldAtBat();
        break;
    case GAME_STATUS_LIVE_BALL:
        toyFieldLiveBall();
        break;
    case GAME_STATUS_INNING_TRANSITION:
        toyFieldInningTransition();
        break;
    case GAME_STATUS_GAME_START_MOVIE:
        toyFieldGameStartMovie();
        break;
    case GAME_STATUS_TRANSITION_TO_MINIGAME_START:
        toyFieldTransitionToMinigameStart();
        break;
    case GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY:
        toyFieldTransitionPrepareNextPlay();
        break;
    case GAME_STATUS_TRANSITION:
        toyFieldEndTurn();
        break;
    case GAME_STATUS_END_OF_GAME:
        toyFieldStateTransitionRelated();
        break;
    case GAME_STATUS_MVP_END_GAME:
        minigameEndSwitcher();
        break;
    case GAME_STATUS_0x24:
        minigameResultsSwitcher();
        break;
    case GAME_STATUS_PAUSED:
        toyFieldPause();
        break;
    case GAME_STATUS_HOW_TO_PLAY_SCREEN:
        highLevelSimulationFlag[0] = TRUE;
        SATURATING_INCREMENT(pauseControl._12);
        pauseControl._004[0] = g_Controls[pauseControl.port].buttonInput;
        pauseControl._004[1] = g_Controls[pauseControl.port].newButtonInput;
        pauseControl._004[2] = g_Controls[pauseControl.port]._08;
        howToPlayScreen();
        break;
    }
    if (g_Minigame._19CD == 1) {
        int type = g_Minigame.toyField_runsScored + 4;
        if (type == 20 || type == 21) {
            latest[g_Minigame.rosterID] += g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[type * 3];
            latest[(s8)g_Minigame.minigamePlayerSelectedOrder] +=
                g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[type * 3 + 1];
            g_Minigame.miniGameLatestPoints[g_Fielders[g_Ball.fielderWBallIndex]._020D] +=
                g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[type * 3 + 2];
        } else {
            latest[g_Minigame.rosterID] += g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[type * 3];
            latest[(s8)g_Minigame.minigamePlayerSelectedOrder] +=
                g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[type * 3 + 1];
            latest[TOY_FIELD_FIELDER_SLOT(1)] += g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[type * 3 + 2];
            latest[TOY_FIELD_FIELDER_SLOT(2)] += g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[type * 3 + 2];
        }
        toyFieldRecordPoints();
        g_Minigame._19CD = 2;
    }
    for (i = 0; i < 4; i++) {
        g_Minigame.miniGameCurrentPoints[i] += g_Minigame.miniGameLatestPoints[i];
        if (g_Minigame.miniGameCurrentPoints[i] > 999) {
            g_Minigame.miniGameCurrentPoints[i] = 999;
        }
        if (g_Minigame.miniGameCurrentPoints[i] < 0) {
            g_Minigame.miniGameCurrentPoints[i] = 0;
        }
    }
    if (sound_crowd_EffectsStruct._30 != 0) {
        sound_crowd_EffectsStruct._30--;
    }
    minigameCalculateRankings();
}

// .text:0x000DFA20 size:0x18C mapped:0x8071EAB4
void toyFieldInit(void) {
    int i;
    g_GameLogic.secondaryGameMode = SECONDARY_GAME_MODE_TOY_FIELD;
    insertGraphicDrawingFunction(possiblyTransitionBlackScreen, 2);
    insertGraphicDrawingFunction(drawStadium, 4);
    g_d_GameSettings._33 = 0;
    g_Minigame.GameMode_MiniGame = 0;
    g_Minigame.nextGameStatus = 30;
    g_Minigame.loadedStadiumID = -1;
    g_Minigame.charLoadSlot = -1;
    g_Minigame.targetParticipantCount = 2;
    g_Minigame.joinedPlayerCount = 1;
    g_Minigame.grandPrixInd = 0;
    g_Minigame._19A7 = lbl_3_data_21270;
    g_Minigame.retryInd = 0;
    g_Minigame.nextDifficultyInd = 0;
    g_Minigame.menuMusicStartedInd = 0;
    for (i = 0; i < 4; i++) {
        g_Minigame.selectSlotState[i] = -1;
        g_Minigame.selectSlots[i].charID = -1;
        g_Minigame.selectSlots[i].loadedCharID = -1;
        g_Minigame.selectSlots[i].pendingCharID = -1;
        g_Minigame.charLoadQueue[i] = -1;
        g_Minigame.charChangeFrames[i] = 20;
        g_Minigame.charLoadPending[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        g_Minigame.playerSlots.characterIndex[i] = -1;
        g_Minigame.playerSlots.aiControlledInd[i] = FALSE;
    }
    g_Minigame.miniGameNumberOfParticipants = 0;
    sound_crowd_EffectsStruct._30 = 0;
    initializeMinigameData();
    if (g_d_GameSettings.exhibitionMatchInd == FALSE) {
        g_Minigame.challengeModeInd = 1;
        SetGameStatus(GAME_STATUS_0x25);
    } else {
        SetGameStatus(GAME_STATUS_0x1B);
    }
}

// .text:0x000DF8D4 size:0x14C mapped:0x8071E968
void initializeMinigameData(void) {
    int i;
    for (i = 0; i < 4; i++) {
        g_Minigame.miniGameCurrentPoints[i] = minigameTuningConstants[0];
        g_Minigame.playerSlots.rank[i] = 0;
        g_Minigame.playerSlots.participantSlot[i] = -1;
        g_Minigame.playerSlots.fielderIndex[i] = -1;
        g_Minigame.playerSlots.runnerPlayerIndex[i] = -1;
        g_Minigame.playerSlots.playOrder[i] = -1;
        g_Minigame.playerSlots._18[i] = i;
        TOY_FIELD_ROLE_HISTORY(i) = 0xFF;
    }
    g_Minigame.toyField_runnerOnHome = 0;
    g_Minigame.toyField_runnerOnFirst = 0;
    g_Minigame.toyField_runnerOnSecond = 0;
    g_Minigame.toyField_runnerOnThird = 0;
    g_Minigame.turnNumberWithinRound = 0;
    g_Minigame.toyField_coinsRemaining = 0;
    g_Minigame.toyField_maxOuts = 3;
    g_Minigame._19A6 = 0;
    g_Minigame.challenge_minigame_haven_tWonYetIndicator = TRUE;
    g_Minigame.endSequencePhase = 0;
    g_Minigame._1911 = 0;
    g_Minigame.toyField_pointMultiplier = 1;
    g_Minigame.toyfield_waitFor_CoinsX2_AnimationToEnd = 0;
    g_Minigame._19CD = 0;
    g_Minigame.toyField_turnEndState = 0;
    g_Minigame._19CF = 0;
    g_Minigame.toyField_selectedTurns = lbl_3_data_189A4[g_Minigame.toyField_inningOptions[0]];
    g_Minigame.toyField_turnNumber = 0;
    if (g_d_GameSettings.exhibitionMatchInd == FALSE) {
        g_Minigame.toyField_selectedTurns = lbl_3_data_189A4[5];
    }
    setPitchingConstants();
    initializeInMemBatter();
    initBallAndGameStateOnLoad();
    initializeFielderConstants();
    initializeAIConstants();
}

// .text:0x000DF820 size:0xB4 mapped:0x8071E8B4
void toyFieldWaitForCharacterLoad(void) {
    int i;
    minigameCharLoadQueueUpdate();
    for (i = 0; i < 4; i++) {
        if (g_Minigame.selectSlots[i].charID != g_Minigame.selectSlots[i].loadedCharID) {
            break;
        }
    }
    if (i >= 4) {
        SetGameStatus(GAME_STATUS_TOY_STADIUM_LOAD);
    }
}

// .text:0x000DF6D4 size:0x14C mapped:0x8071E768
void toyFieldApplyGameSettings(void) {
    switch (g_GameLogic._125) {
    case 0:
        toyFieldSetupOpponents();
        g_GameLogic._125++;
        break;
    }
    g_Minigame.challengeModeInd = 1;
    (&g_Minigame._19DA)[g_d_GameSettings._35] = g_d_GameSettings._35;
    lbl_3_common_bss_37400.humanTeam = g_d_GameSettings._35;
    g_Minigame.GameMode_MiniGame = g_d_GameSettings._33;
    g_Minigame.nextGameStatus = 30;
    SetGameStatus(GAME_STATUS_0x1B);
}

// .text:0x000DF608 size:0xCC mapped:0x8071E69C
void toyFieldSetupOpponents(void) {
    int i;
    u8* src = lbl_3_data_18980;
    (&g_Minigame._19DA)[g_d_GameSettings._35] = 0;
    for (i = 0; i < 4; i++) {
        if (g_d_GameSettings._35 != i) {
            g_Minigame.playerSlots.aiStrength[i] = *src++;
        }
    }
    g_Minigame.humanPlayerCount = 1;
    g_Minigame.multiPlayerInd = 1;
    g_Minigame.miniGameNumberOfParticipants = minigameChallengeOpponentCounts[g_Minigame.GameMode_MiniGame] + 1;
    g_Scores.inningLimit = 1;
}

// .text:0x000DF3D8 size:0x230 mapped:0x8071E46C
void toyFieldGameStartMovie(void) {
    switch (g_GameLogic._125) {
    case 0:
        fn_3_E8AC8();
        challenge_setTransitionScreenCharacterPortrait(7, 0);
        g_Minigame.toyField_selectedTurns = lbl_3_data_189A4[g_Minigame.toyField_inningOptions[0]];
        if (g_d_GameSettings.exhibitionMatchInd == FALSE) {
            g_Minigame.toyField_selectedTurns = lbl_3_data_189A4[5];
        }
        hugeAnimStruct[0x307E] = 1;
        hugeAnimStruct[0x2D8E] = 0;
        hugeAnimStruct[0x307A] = 3;
        if (g_Minigame.challengeModeInd != 0) {
            g_GameLogic._125 = 1;
        } else {
            loadToyFieldCharacterFiles();
            g_GameLogic._125 = 2;
        }
        break;
    case 1:
        minigameCharLoadQueueUpdate();
        if ((s8)g_Minigame.charLoadQueue[0] < 0) {
            loadToyFieldCharacterFiles();
            g_GameLogic._125 = 2;
        }
        break;
    case 2:
        if (fn_3_59AE4() == 0) {
            break;
        }
        g_GameLogic._125 = 3;
    case 3:
        if (fn_80016F7C() == 0) {
            break;
        }
        if (g_Minigame.retryInd != 0) {
            g_GameLogic._125 = 6;
        } else {
            g_GameLogic._125 = 4;
        }
        sound_crowd_EffectsStruct._2C = 0;
        break;
    case 4:
        if (fn_3_90DD8() != 0) {
            g_GameLogic._125 = 6;
        }
        break;
    case 6:
        if (lbl_8037169C[0x12] != 0) {
            if (g_GameLogic.FrameCountOfCurrentPitch >= 240 || fn_3_FD9FC() != 0) {
                if (checkForButtonPressToSkip(1, INPUT_BUTTON_A | INPUT_BUTTON_B | INPUT_BUTTON_START) != 0) {
                    g_GameLogic._125 = 7;
                }
            }
        }
        break;
    case 7:
        changeScene(3, 6);
        if (lbl_8037169C[0x13] != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
            g_GameLogic._125 = 8;
        }
        break;
    case 8:
        toyFieldInitCoinModels();
        g_Minigame.retryInd = 0;
        g_Minigame._19A2 = 0;
        hugeAnimStruct[0x307A] = 1;
        SetGameStatus(GAME_STATUS_TRANSITION_TO_MINIGAME_START);
        break;
    }
}

// .text:0x000DF25C size:0x17C mapped:0x8071E2F0
void toyFieldTransitionToMinigameStart(void) {
    int i;
    int j;
    int remaining;
    u8* picked;
    g_Scores.Inning++;
    g_Scores._pad_AC = evaluateInningCondition(g_Scores.Inning);
    g_Strikes.outs = 0;
    g_Strikes.storedOuts = 0;
    animRelated[0xD5] = 1;
    g_Minigame.turnNumberWithinRound = 0;
    g_Minigame.toyField_maxOuts = 3;
    g_Minigame.panelHitInd = FALSE;
    g_Minigame._19A5 = 1;
    g_Minigame._190F = 0;
    g_Minigame.toyField_outsRemaining = 3;
    g_Minigame._1911 = 0;
    g_Minigame.toyField_runnerOnHome = 0;
    g_Minigame.toyField_runnerOnFirst = 0;
    g_Minigame.toyField_runnerOnSecond = 0;
    g_Minigame.toyField_runnerOnThird = 0;
    for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
        g_Minigame.playerSlots._18[i] = i;
    }
    remaining = g_Minigame.miniGameNumberOfParticipants;
    picked = (u8*)&g_Minigame;
    for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
        int skip = random_fn_3_9EE24(remaining);
        for (j = 0; j < g_Minigame.miniGameNumberOfParticipants; j++) {
            if (g_Minigame.playerSlots._18[j] >= 0) {
                if (skip == 0) {
                    picked[0x18E0] = j;
                    g_Minigame.playerSlots._18[j] = -1;
                    remaining--;
                    picked++;
                    break;
                }
                skip--;
            }
        }
    }
    changeScene(1, 6);
    SetGameStatus(GAME_STATUS_INNING_TRANSITION);
}

// .text:0x000DF00C size:0x250 mapped:0x8071E0A0
void toyFieldTransitionPrepareNextPlay(void) {
    switch (g_GameLogic._125) {
    case 0:
        if (g_Minigame._19A6 == 1) {
            if (!(u8)fn_3_E8AC8()) {
                break;
            }
            g_Minigame._19A6 = 0;
        }
        if (g_Minigame._19A2 != 0) {
            g_Minigame._19A2--;
        }
        g_Minigame.playerSlots.fielderIndex[0] = -1;
        g_Minigame.playerSlots.fielderIndex[1] = -1;
        g_Minigame.playerSlots.fielderIndex[2] = -1;
        g_Minigame.playerSlots.fielderIndex[3] = -1;
        toyFieldAssignTurnRoles();
        resetBallValuesBetweenBatters();
        resetPitcherValuesBetweenBatters(0);
        setBatterContactConstants();
        initializeMiniGameCharacters();
        toyfieldRelated();
        betweenABSetPitcherBatter();
        fn_3_E1370(0);
        us80893314[1] = 1;
        g_GameLogic.pre_PostMiniGameInd = 1;
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        g_Strikes.strikes = 0;
        g_Strikes.balls = 0;
        highLevelSimulationFlag[2] = 0;
        g_GameLogic._125++;
        break;
    case 1:
        if (g_Minigame._19C7 != 0) {
            if (someAnimationIndFunction() != 0) {
                us80893314[1] = 1;
                g_GameLogic._125++;
            }
        } else {
            g_GameLogic._125++;
        }
        break;
    default:
        initializeToyFieldSomething();
        g_Minigame._190F++;
        if (g_Minigame._190F == 1) {
            g_Minigame._1911 = 1;
        }
        SATURATING_INCREMENT(g_Minigame.toyField_turnNumber);
        if (g_Minigame.toyField_turnNumber < g_Minigame.toyField_selectedTurns && g_Minigame.toyField_turnNumber % 10 == 1) {
            g_Minigame.toyField_next_CoinsX2_TurnNumber = 4 + random_fn_3_9EE24(6) + g_Minigame.toyField_turnNumber;
        }
        if (g_Minigame.toyField_next_CoinsX2_TurnNumber == g_Minigame.toyField_turnNumber) {
            g_Minigame.toyField_pointMultiplier = 2;
        } else {
            g_Minigame.toyField_pointMultiplier = 1;
        }
        break;
    }
}

// .text:0x000DEB90 size:0x47C mapped:0x8071DC24
void toyFieldAssignTurnRoles(void) {
    u8* slot;
    int i;
    g_Minigame._19C7 = 0;
    if (g_Minigame.toyField_turnNumber == 0) {
        int skip;
        g_Minigame._19C7 = 1;
        skip = random_fn_3_9EE24(3);
        for (i = 0; i < 4; i++) {
            if (g_Minigame.rosterID != i) {
                if (skip == 0) {
                    g_Minigame.minigamePlayerSelectedOrder = i;
                    break;
                }
                skip--;
            }
        }
        slot = (u8*)&g_Minigame + 1;
        for (i = 0; i < 4; i++) {
            if (g_Minigame.rosterID != i && (s8)g_Minigame.minigamePlayerSelectedOrder != i) {
                slot[0x18F4] = i;
                slot++;
            }
        }
    } else {
        if ((u8)g_Minigame.rosterID == (s8)g_Minigame.toyField_turnPlayer) {
            QueueTextToDisplay(0x15, 0);
        } else {
            if (g_Minigame.playerSlots.participantSlot[1] == (s8)g_Minigame.toyField_turnPlayer) {
                g_Minigame.minigamePlayerSelectedOrder = g_Minigame.playerSlots.participantSlot[2];
            } else if (g_Minigame.playerSlots.participantSlot[2] == (s8)g_Minigame.toyField_turnPlayer) {
                g_Minigame.minigamePlayerSelectedOrder = g_Minigame.playerSlots.participantSlot[1];
            } else if (TOY_FIELD_ROLE_STREAK(g_Minigame.playerSlots.participantSlot[1]) < TOY_FIELD_ROLE_STREAK(g_Minigame.playerSlots.participantSlot[2])) {
                g_Minigame.minigamePlayerSelectedOrder = g_Minigame.playerSlots.participantSlot[2];
            } else if (TOY_FIELD_ROLE_STREAK(g_Minigame.playerSlots.participantSlot[1]) > TOY_FIELD_ROLE_STREAK(g_Minigame.playerSlots.participantSlot[2])) {
                g_Minigame.minigamePlayerSelectedOrder = g_Minigame.playerSlots.participantSlot[1];
            } else {
                int pick = random_fn_3_9EE24(2) + 1;
                g_Minigame.minigamePlayerSelectedOrder = g_Minigame.playerSlots.participantSlot[pick];
            }
            g_Minigame._19C7 = 1;
            g_Minigame.rosterID = g_Minigame.toyField_turnPlayer;
        }
        {
            s8 j;
            slot = (u8*)&g_Minigame + 1;
            for (j = 0; j < 4; j++) {
                if (j != (s8)g_Minigame.minigamePlayerSelectedOrder && j != g_Minigame.rosterID) {
                    slot[0x18F4] = j;
                    slot++;
                }
            }
        }
    }
    g_Minigame.playerSlots.batterInd[g_Minigame.rosterID] = 1;
    setInMemBatterConstants(g_Minigame.rosterID);
    g_Minigame.toyField_turnPlayer = g_Minigame.rosterID;
    g_Minigame.playerSlots.participantSlot[0] = g_Minigame.minigamePlayerSelectedOrder;
    g_Minigame.playerSlots.batterInd[(s8)g_Minigame.minigamePlayerSelectedOrder] = 0;
    g_Minigame.playerSlots.fielderIndex[(s8)g_Minigame.minigamePlayerSelectedOrder] = 0;
    g_Fielders[g_Minigame.playerSlots.fielderIndex[(s8)g_Minigame.minigamePlayerSelectedOrder]]._020D = g_Minigame.playerSlots.participantSlot[0];
    g_Minigame.playerSlots.batterInd[g_Minigame.playerSlots.participantSlot[1]] = 0;
    g_Minigame.playerSlots.fielderIndex[g_Minigame.playerSlots.participantSlot[1]] = 3;
    g_Fielders[g_Minigame.playerSlots.fielderIndex[g_Minigame.playerSlots.participantSlot[1]]]._020D = g_Minigame.playerSlots.participantSlot[1];
    g_Minigame.playerSlots.batterInd[g_Minigame.playerSlots.participantSlot[2]] = 0;
    g_Minigame.playerSlots.fielderIndex[g_Minigame.playerSlots.participantSlot[2]] = 4;
    g_Fielders[g_Minigame.playerSlots.fielderIndex[g_Minigame.playerSlots.participantSlot[2]]]._020D = g_Minigame.playerSlots.participantSlot[2];
    for (i = 0; i < 4; i++) {
        if (g_Minigame.playerSlots.participantSlot[0] == i) {
            toyFieldTrackRole(i, 0);
        } else if (g_Minigame.rosterID == i) {
            toyFieldTrackRole(i, 1);
        } else {
            toyFieldTrackRole(i, 2);
        }
    }
    g_Minigame.turnNumberWithinRound = 0;
    g_Minigame.playerSlots.playOrder[0] = g_Minigame.rosterID;
    g_Minigame.playerSlots.playOrder[1] = g_Minigame.minigamePlayerSelectedOrder;
    g_Minigame.playerSlots.playOrder[2] = g_Minigame.playerSlots.participantSlot[1];
    g_Minigame.playerSlots.playOrder[3] = g_Minigame.playerSlots.participantSlot[2];
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
    g_Minigame.toyField_pointsCountingInd = 0;
    g_Minigame.toyField_slotStage = 0;
    g_Minigame.toyField_slotResultFrames = 0;
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
    if (g_Minigame.toyField_turnEndState == 3) {
        fn_3_E67F4();
    }
    g_Minigame.toyField_turnEndState = 0;
    for (i = 0; i < 4; i++) {
        g_Minigame.minigamePoints_current_Latest[i][0] = g_Minigame.miniGameCurrentPoints[i];
        g_Minigame.minigamePoints_current_Latest[i][1] = 0;
        g_Minigame.toyField_eventPlayers[i] = -1;
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
        g_Minigame.toyField_prevRunnerOn[i] = (&g_Minigame.toyField_runnerOnHome)[i];
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
    if (g_Minigame.rosterID != (s8)g_Minigame.toyField_turnPlayer || g_Minigame.playerSlots.rank[g_Minigame.rosterID] == 1) {
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
        g_Minigame.playerSlots.rank[i] = 0;
        g_Minigame.playerSlots.rankCopy[i] = 0;
    }
    for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
        s16 points = g_Minigame.miniGameCurrentPoints[i];
        int rank = 1;
        for (j = 0; j < g_Minigame.miniGameNumberOfParticipants; j++) {
            if (g_Minigame.miniGameCurrentPoints[j] > points) {
                rank++;
            }
        }
        g_Minigame.playerSlots.rank[i] = rank;
        g_Minigame.playerSlots.rankCopy[i] = rank;
    }
    for (firstTied = 0; firstTied < 4; firstTied++) {
        if (g_Minigame.playerSlots.rank[firstTied] > 1) {
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
    if (g_Minigame.toyField_pointsCountingInd != 0 && g_GameLogic.CountdownUntilFade < lbl_3_data_1899C[1]) {
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
        if (g_Minigame.TF_framesSinceHittingPanel < minigameTuningConstants[6]) {
            g_Minigame.TF_framesSinceHittingPanel++;
        } else if (g_Minigame.TF_ballDespawnedInd == FALSE) {
            g_Minigame.TF_ballDespawnedInd = TRUE;
            toyFieldPlayHazardSound(0x15, 0x2A);
        }
    }
    ballPhysica();
    miniGameDash();
    if (g_Minigame._19CF != 0) {
        if (g_Minigame.toyField_turnEndState == 0) {
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
    if (g_Minigame.toyField_pointsCountingInd != 0 && g_Minigame.toyField_turnEndState == 0 && g_GameLogic.CountdownUntilFade < lbl_3_data_1899C[1]) {
        g_GameLogic.CountdownUntilFade = lbl_3_data_1899C[1];
    }
    if (g_Minigame.toyField_coinsRemaining != 0 && g_GameLogic.CountdownUntilFade < lbl_3_data_1899C[1]) {
        g_GameLogic.CountdownUntilFade = lbl_3_data_1899C[1];
    }

    if (g_Minigame.toyField_turnEndState != 0 && g_Minigame.toyField_turnEndState < 3) {
        int i;
        if (g_GameLogic.CountdownUntilFade <= lbl_3_data_1899C[1] - 10) {
            g_GameLogic.CountdownUntilFade++;
        }
        if (g_Minigame.toyField_turnEndState == 1) {
            TOY_FIELD_AWARD_POINTS(lbl_3_data_18BB8[36], lbl_3_data_18BB8[37], lbl_3_data_18BB8[38]);
            toyFieldRecordPoints();
            g_Minigame._19BA = 0;
            g_Minigame.toyField_turnEndState = 2;
            for (i = 0; i < 4; i++) {
                if (g_Minigame.toyField_prevRunnerOn[i] != 0) {
                    (&g_Minigame.toyField_runnerOnHome)[i] = 0;
                }
            }
            if (audioFileDescriptors.enableMusic == TRUE) {
                toyFieldPlayHazardSound(0x1A, 0x34);
            }
        }
        SATURATING_INCREMENT(g_Minigame._19BA);
        if (g_Minigame._19BA > minigameTuningConstants[3]) {
            g_Minigame.toyField_turnEndState = 3;
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
    if (g_Minigame.toyField_turnEndState != 0) {
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
            if (random_fn_3_9EE24(100) < minigameTuningConstants[7] || g_Minigame.humanPlayerCount == 4) {
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
        if (g_GameLogic.FrameCountOfCurrentPitch >= minigameTuningConstants[2]) {
            done = TRUE;
        } else if (g_GameLogic.FrameCountOfCurrentAtBat_Copy >= minigameTuningConstants[1]) {
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
            if (g_Minigame.challengeModeInd != 0) {
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
            g_d_GameSettings._38 = g_Minigame.playerSlots.rank[g_d_GameSettings._35];
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
            pauseControl.port = g_Minigame.minigameControlStruct[0].characterIndex[i];
            fn_3_AFD80(0);
            QueueTextToDisplay(14, 0);
            break;
        }
    }
}

// .text:0x000DCED0 size:0x74 mapped:0x8071BF64
void toyFieldWaitForPause(void) {
    SATURATING_INCREMENT(pauseControl.counter);
    highLevelSimulationFlag[0] = TRUE;
    if (pauseControl.counter > 60) {
        fn_3_AFD80(1);
        SetGameStatus(GAME_STATUS_PAUSED);
    } else {
        miniGameFielding();
    }
}

// .text:0x000DCC80 size:0x250 mapped:0x8071BD14
void toyFieldPause(void) {
    SATURATING_INCREMENT(pauseControl.counter);
    SATURATING_INCREMENT(pauseControl._12);
    highLevelSimulationFlag[0] = TRUE;
    pauseControl._004[0] = g_Controls[pauseControl.port].buttonInput;
    pauseControl._004[1] = g_Controls[pauseControl.port].newButtonInput;
    pauseControl._004[2] = g_Controls[pauseControl.port]._08;
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
        minigamePauseHelpUpdate();
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
    if (((u16*)pauseControl._004)[1] & INPUT_BUTTON_START) {
        pauseControl.state = 4;
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
    } else if (((u16*)pauseControl._004)[1] & INPUT_BUTTON_A) {
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
    } else if (((u16*)pauseControl._004)[1] & INPUT_BUTTON_B) {
        if (pauseControl.cursor != 0) {
            pauseControl.cursor = 0;
        } else {
            pauseControl.state = 4;
        }
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
    } else if (((u16*)pauseControl._004)[2] & INPUT_BUTTON_UP) {
        if (pauseControl.cursor > 0) {
            pauseControl.cursor--;
        } else {
            pauseControl.cursor = 3;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (((u16*)pauseControl._004)[2] & INPUT_BUTTON_DOWN) {
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
            g_Minigame.retryInd = 1;
            start = TRUE;
        } else if (pauseControl.cursor == 1) {
            g_Minigame.nextGameStatus = 30;
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
        switch (((int (*)(u16))exitMenu_main)(g_Controls[pauseControl.port].newButtonInput)) {
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
        pauseControl.port = pressed - 1;
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
            g_Minigame.toyField_turnEndState = 1;
        } else if (g_Minigame._19CF < 0xFE) {
            g_Minigame._19CF++;
        } else {
            g_Minigame._19CF = 0xFF;
        }
    } else if (g_Minigame.toyFieldBallStateResult2 == TOY_FIELD_RESULT_CAUGHT || g_Ball.maybebuntOn2Strikes != 0) {
        if (g_Ball.maybebuntOn2Strikes == 0) {
            QueueTextToDisplay(1, 0);
        }
        g_Minigame.toyField_turnPlayer = g_Minigame.minigamePlayerSelectedOrder;
        if (g_Ball.fielderWBallIndex >= 0) {
            g_Minigame.toyField_turnPlayer = g_Fielders[g_Ball.fielderWBallIndex]._020D;
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
                        g_Minigame.toyField_turnPlayer = g_Fielders[g_Ball.fielderWBallIndex]._020D;
                    } else {
                        g_Minigame.toyField_turnPlayer = g_Minigame.minigamePlayerSelectedOrder;
                    }
                }
            } else if (g_Minigame.toyFieldBallStateResult2 == 0xB) {
                toyFieldRelated();
                toyFieldPickEventTargets();
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
            if (g_Minigame.toyField_slotStage == 0) {
                SATURATING_INCREMENT(g_Minigame.toyField_slotSpinFrames);
                for (i = 0; i < 3; i++) {
                    u8 state = g_Minigame.toyField_reelState[i];
                    if (state == 0) {
                        if (g_Minigame.toyField_slotSpinFrames > lbl_3_data_189B8[i]) {
                            g_Minigame.toyField_reelState[i] = 1;
                        }
                    } else if (state == 1) {
                        if (i == 0) {
                            if (g_Minigame.toyField_slotSpinFrames > lbl_3_data_189B8[3]) {
                                g_Minigame.toyField_reelState[i] = 2;
                            }
                        } else if (i == 2) {
                            if (g_Minigame.toyField_reelHudStage[i - 1] == 3) {
                                g_Minigame.toyField_reelState[i] = 2;
                            }
                        } else {
                            if (g_Minigame.toyField_reelHudStage[i - 1] >= 2) {
                                g_Minigame.toyField_reelState[i] = 2;
                            }
                        }
                    }
                }
            } else if (g_Minigame.toyField_slotStage != 1) {
                if (g_Minigame.toyField_slotStage == 2) {
                    toyFieldApplyPanelEvent();
                    g_Minigame.toyField_slotStage = 3;
                } else {
                    if (g_Minigame.toyField_slotEvent == 6) {
                        g_Minigame._19A6 = 3;
                        if (g_Minigame.toyField_slotResultFrames == 1) {
                            fn_3_E8AC8();
                        }
                    }
                    SATURATING_INCREMENT(g_Minigame.toyField_slotResultFrames);
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
                        minigameTuningConstants[8] * g_Minigame.toyField_pointMultiplier;
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

#define TOY_FIELD_NEXT_PANEL_CODE(dst, code)                 \
    do {                                                     \
        int k;                                               \
        for (k = 0; k < 7; k++) {                            \
            if ((code) == lbl_3_data_189C4[2][k]) {          \
                break;                                       \
            }                                                \
        }                                                    \
        k++;                                                 \
        if (k >= 7) {                                        \
            k = 0;                                           \
        }                                                    \
        (dst) = lbl_3_data_189C4[2][k];                      \
    } while (0)

// .text:0x000D9A30 size:0x470 mapped:0x80718AC4
void toyFieldRelated(void) {
    int stage = 0;
    int rank = 1;
    BOOL special = FALSE;
    int i;
    int third;
    int flags;
    int mine;
    u8 mode;

    third = g_Minigame.toyField_selectedTurns / 3;
    if (third * 2 > g_Minigame.toyField_turnNumber) {
        stage = 2;
    } else if (third > g_Minigame.toyField_turnNumber) {
        stage = 1;
    }

    flags = 0;
    mine = g_Minigame.miniGameCurrentPoints[g_Minigame.rosterID];
    for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
        if (i != g_Minigame.rosterID) {
            s16 other = g_Minigame.miniGameCurrentPoints[i];
            if (mine < other) {
                flags |= 1;
            }
            if (mine > other) {
                flags |= 0x10;
            }
        }
    }
    if (!(flags & 1)) {
        rank = 0;
    } else if (!(flags & 0x10)) {
        rank = 2;
    }

    mode = RandomIndexFromWeights(lbl_3_data_189F0[g_Minigame.miniGameNumberOfParticipants - 2][stage][rank], 8);
    g_Minigame.toyField_slotEvent = mode;
    if (g_d_GameSettings.exhibitionMatchInd == FALSE && g_Minigame.rosterID == lbl_3_common_bss_37400.humanTeam) {
        starMissionsMinigamesSpecialAction(7, mode, 0);
    }

    if (g_Minigame.toyField_slotEvent == 7) {
        if (g_Minigame.toyField_runnerOnFirst == 0 && g_Minigame.toyField_runnerOnSecond == 0 &&
            g_Minigame.toyField_runnerOnThird == 0) {
            g_Minigame.toyField_slotEvent = 8;
        } else if (rand() % 100 < lbl_3_data_189B8[5]) {
            g_Minigame.toyField_slotEvent = 8;
        }
        if (g_Minigame.toyField_slotEvent == 8) {
            if (rand() % 99 < lbl_3_data_189B8[4]) {
                special = TRUE;
            }
        }
    }

    for (i = 0; i < 3; i++) {
        g_Minigame.toyField_reelPos[i] = random_fn_3_9EE24(7);
        g_Minigame.toyField_reelState[i] = 0;
        if (g_Minigame.toyField_slotEvent == 8) {
            if (special) {
                if (i == 0) {
                    g_Minigame.toyField_reelTarget[0] = lbl_3_data_189C4[i][random_fn_3_9EE24(7)];
                } else if (i == 1) {
                    g_Minigame.toyField_reelTarget[1] = g_Minigame.toyField_reelTarget[0];
                } else {
                    TOY_FIELD_NEXT_PANEL_CODE(g_Minigame.toyField_reelTarget[2], g_Minigame.toyField_reelTarget[0]);
                }
            } else {
                g_Minigame.toyField_reelTarget[i] = lbl_3_data_189C4[i][random_fn_3_9EE24(7)];
                if (i == 2 && g_Minigame.toyField_reelTarget[0] == g_Minigame.toyField_reelTarget[1] && g_Minigame.toyField_reelTarget[0] == g_Minigame.toyField_reelTarget[2]) {
                    TOY_FIELD_NEXT_PANEL_CODE(g_Minigame.toyField_reelTarget[2], g_Minigame.toyField_reelTarget[2]);
                }
            }
        } else {
            g_Minigame.toyField_reelTarget[i] = g_Minigame.toyField_slotEvent;
        }
    }
    g_Minigame.toyField_slotSpinFrames = 0;
}

static inline u32 toyFieldCountRank(u8 (*order)[2], u32 rank) {
    u32 count = 0;
    u32 i = 0;
    do {
        if (order[i][1] == rank) {
            count++;
        }
        i++;
    } while (i < g_Minigame.miniGameNumberOfParticipants);
    return count;
}

#pragma dont_inline on
// .text:0x000D9868 size:0x1C8 mapped:0x807188FC
void toyFieldPickEventTargets(void) {
    u8 order[4][2];
    u32 count;
    minigame_rankPlayers(order, 0);
    count = toyFieldCountRank(order, 0);
    switch (g_Minigame.toyField_slotEvent) {
    case 0: {
        u32 j;
        int slot;
        g_Minigame.toyField_eventActor = g_Minigame.rosterID;
        j = 0;
        slot = 1;
        do {
            if (j != g_Minigame.rosterID) {
                g_Minigame.toyField_eventPlayers[slot++] = j;
            }
            j++;
        } while (j < g_Minigame.miniGameNumberOfParticipants);
        break;
    }
    case 3:
        g_Minigame.toyField_eventActor = g_Minigame.rosterID;
        do {
            g_Minigame.toyField_eventVictim = random_fn_3_9EE24(g_Minigame.miniGameNumberOfParticipants);
        } while (g_Minigame.toyField_eventVictim == g_Minigame.toyField_eventActor);
        break;
    case 4:
    case 5:
        g_Minigame.toyField_eventActor = g_Minigame.rosterID;
        if (count == 1 && order[0][0] == g_Minigame.rosterID) {
            u32 tied = toyFieldCountRank(order, 1);
            g_Minigame.toyField_eventVictim = order[1 + random_fn_3_9EE24(tied)][0];
        } else {
            do {
                g_Minigame.toyField_eventVictim = order[random_fn_3_9EE24(count)][0];
            } while (g_Minigame.toyField_eventVictim == g_Minigame.toyField_eventActor);
        }
        break;
    }
}
#pragma dont_inline reset

// .text:0x000D8CD0 size:0xB98 mapped:0x80717D64
void toyFieldApplyPanelEvent(void) {
    s32 i;
    g_Minigame.toyField_slotResultFrames = 0;
    if (g_Minigame.toyField_slotEvent == 0 || g_Minigame.toyField_slotEvent == 3 || g_Minigame.toyField_slotEvent == 4 || g_Minigame.toyField_slotEvent == 5) {
        switch (g_Minigame.toyField_slotEvent) {
        case 0: {
            g_Minigame.miniGameLatestPoints[g_Minigame.toyField_eventActor] = 0;
            i = 1;
            do {
                int points = lbl_3_data_18BB8[45] * g_Minigame.toyField_pointMultiplier;
                if (g_Minigame.miniGameCurrentPoints[g_Minigame.toyField_eventPlayers[i]] < points) {
                    points = g_Minigame.miniGameCurrentPoints[g_Minigame.toyField_eventPlayers[i]];
                }
                g_Minigame.miniGameLatestPoints[g_Minigame.toyField_eventActor] += points;
                g_Minigame.miniGameLatestPoints[g_Minigame.toyField_eventPlayers[i]] = -points;
                i++;
            } while (i < g_Minigame.miniGameNumberOfParticipants);
            toyFieldPlayHazardSound(1, 2);
            break;
        }
        case 3: {
            int points = lbl_3_data_18BB8[39] * g_Minigame.toyField_pointMultiplier;
            if (g_Minigame.miniGameCurrentPoints[g_Minigame.toyField_eventVictim] < points) {
                points = g_Minigame.miniGameCurrentPoints[g_Minigame.toyField_eventVictim];
            }
            g_Minigame.miniGameLatestPoints[g_Minigame.toyField_eventActor] = points;
            g_Minigame.miniGameLatestPoints[g_Minigame.toyField_eventVictim] = -points;
            toyFieldPlayHazardSound(1, 2);
            break;
        }
        case 4: {
            int points = lbl_3_data_18BB8[42] * g_Minigame.toyField_pointMultiplier;
            if (g_Minigame.miniGameCurrentPoints[g_Minigame.toyField_eventVictim] < points) {
                points = g_Minigame.miniGameCurrentPoints[g_Minigame.toyField_eventVictim];
            }
            g_Minigame.miniGameLatestPoints[g_Minigame.toyField_eventActor] = points;
            g_Minigame.miniGameLatestPoints[g_Minigame.toyField_eventVictim] = -points;
            toyFieldPlayHazardSound(1, 2);
            break;
        }
        case 5: {
            s16 temp = g_Minigame.miniGameCurrentPoints[g_Minigame.toyField_eventActor];
            g_Minigame.miniGameCurrentPoints[g_Minigame.toyField_eventActor] = g_Minigame.miniGameCurrentPoints[g_Minigame.toyField_eventVictim];
            g_Minigame.miniGameCurrentPoints[g_Minigame.toyField_eventVictim] = temp;
            toyFieldPlayHazardSound(0xA, 0x14);
            break;
        }
        }
        if (g_Minigame.toyField_slotEvent != 5) {
            toyFieldRecordPoints();
        }
    } else if (g_Minigame.toyField_slotEvent == 7) {
        g_Minigame.toyFieldBallStateResult2 = TOY_FIELD_RESULT_CAUGHT;
        toyFieldPlayHazardSound(9, 0x12);
        TOY_FIELD_AWARD_POINTS(lbl_3_data_18BB8[54], lbl_3_data_18BB8[55], lbl_3_data_18BB8[56]);
        toyFieldRecordPoints();
    } else if (g_Minigame.toyField_slotEvent == 2) {
        g_Minigame._19A2 = 2;
        g_Minigame.toyField_turnPlayer = g_Minigame.rosterID;
        toyFieldPlayHazardSound(5, 0xA);
        TOY_FIELD_AWARD_POINTS(lbl_3_data_18BB8[48], lbl_3_data_18BB8[49], lbl_3_data_18BB8[50]);
        toyFieldRecordPoints();
        g_Minigame.toyField_runnerOnFirst = 1;
        g_Minigame.toyField_runnerOnSecond = 1;
        g_Minigame.toyField_runnerOnThird = 1;
    } else if (g_Minigame.toyField_slotEvent == 6) {
        g_Minigame.toyField_turnPlayer = g_Minigame.rosterID;
        toyFieldPlayHazardSound(0xB, 0x16);
        TOY_FIELD_AWARD_POINTS(lbl_3_data_18BB8[51], lbl_3_data_18BB8[52], lbl_3_data_18BB8[53]);
        toyFieldRecordPoints();
    }
    g_Minigame.turnOverStatus = 1;
    if (g_Minigame.toyField_slotEvent == 7 || g_Minigame.toyField_slotEvent == 8) {
        g_Strikes.outs++;
        QueueTextToDisplay(1, 0);
        if (g_Minigame.rosterID == (s8)g_Minigame.toyField_turnPlayer) {
            g_Minigame.toyField_turnPlayer = g_Minigame.minigamePlayerSelectedOrder;
        }
    }
    if (g_Minigame.toyField_slotEvent == 2) {
        g_Minigame.toyField_outsRemaining = g_Minigame.toyField_maxOuts;
    } else {
        g_Minigame.pointsTargetReachedInd = TRUE;
    }
}

// .text:0x000D8A10 size:0x2C0 mapped:0x80717AA4
void fn_3_D8A10(void) {
    if (g_Minigame.toyField_turnEndState == 1) {
        int i;
        TOY_FIELD_AWARD_POINTS(lbl_3_data_18BB8[36], lbl_3_data_18BB8[37], lbl_3_data_18BB8[38]);
        toyFieldRecordPoints();
        g_Minigame._19BA = 0;
        g_Minigame.toyField_turnEndState = 2;
        for (i = 0; i < 4; i++) {
            if (g_Minigame.toyField_prevRunnerOn[i] != 0) {
                (&g_Minigame.toyField_runnerOnHome)[i] = 0;
            }
        }
        if (audioFileDescriptors.enableMusic == TRUE) {
            toyFieldPlayHazardSound(0x1A, 0x34);
        }
    }
    SATURATING_INCREMENT(g_Minigame._19BA);
    if (g_Minigame._19BA > minigameTuningConstants[3]) {
        g_Minigame.toyField_turnEndState = 3;
    }
}
