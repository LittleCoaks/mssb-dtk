#define SQRT2_LINKAGE static
#include "game/minigame/barrel_batter.h"
#include "game/UnknownHomes_Game.h"
#include "header_rep_data.h"
#include "musyx/musyx.h"
#include "game/match_setup/roster_init.h"
#include "game/ball/ball_physics.h"
#include "game/pitching/pitcher.h"
#include "game/batting/batter.h"
#include "game/baserunning/runner.h"
#include "game/fielding/fielder.h"
#include "game/animation/scene_effects.h"
#include "Dolphin/stl.h"
#include "game/math/game_math.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x800204cc.h"
#include "game/minigame/toy_field.h"
#include "game/match_setup/match_loading.h"
#include "game/minigame/minigame_effects.h"
#include "Unknown/sub.h"

extern void SetGameStatus(GAME_STATUS status);
extern u8 lbl_800EFBA4[0x10];
extern s16 lbl_3_data_18C48[10];
extern u8 lbl_8037169C[0x1C];
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern BOOL checkForButtonPressToSkip(int a, int b);
extern u8 highLevelSimulationFlag[3];
extern u8 us80893314[8];
extern u8 cost_15_bB_pitchesPerRound_solo[12];
extern u8 animRelated[0x124];
extern void fn_3_10AD48(void);
extern void fn_3_10F550(int a, int b);

typedef struct {
    u8 _00[5];
    u8 _05;
    u8 _06;
    u8 _07[5];
} UnkSimulationStruct_31AC0;
extern UnkSimulationStruct_31AC0 g_UnkSimulation_31AC0;

extern float lbl_3_data_21770[6];
extern void fn_8004C108(VecXYZ *pos, BOOL flag);
extern void callSfx(int soundId);

typedef struct {
    s16 baseBlowUpDelay;
    s16 blowUpDelayIncrement;
    s16 bombBarrelThreshold;
} BB_dropConstsStruct;
extern BB_dropConstsStruct lbl_3_data_21788;
extern VecXYZ barrelBaseCoordinates[15];
extern s16 lbl_3_data_217A4[12];
extern s16 lbl_3_common_bss_37400[0x27];
extern void starMissionsMinigamesSpecialAction(int missionType, int points, int barrelsHit);

extern s8 lbl_3_data_217BC[8];
extern u8 lbl_3_data_217C4[4];
extern s8 lbl_3_data_217C8[4];
extern s8 bBAI_chanceToMissTimeSwing[4];
extern s8 bBAI_framesMistimedBy[4];
extern s8 bBAI_chanceToOverrideVertAngleToMiddleRow[4];

typedef struct {
    s8 barrelIndex;
    s8 barrelsCleared;
    s16 score;
} BB_AICandidate;

extern BOOL checkForPauses(void);
extern void ballPhysica(void);
extern u8 lbl_3_data_2127C[8][5];
extern s16 bB_challengePointsRequired[4];

static inline void bB_shiftBarrelDown(int i) {
    g_Minigame.barrels[i - 1].barrelState = g_Minigame.barrels[i].barrelState;
    g_Minigame.barrels[i - 1].barrelColour = g_Minigame.barrels[i].barrelColour;
    g_Minigame.barrels[i - 1].currentPos.x = g_Minigame.barrels[i].currentPos.x;
    g_Minigame.barrels[i - 1].currentPos.y = g_Minigame.barrels[i].currentPos.y;
    g_Minigame.barrels[i - 1].currentPos.z = g_Minigame.barrels[i].currentPos.z;
    g_Minigame.barrels[i].barrelState = BB_BARREL_STATE_EMPTY;
}

static inline BB_barrelStruct *bB_getBarrel(int barrelIndex) {
    return &g_Minigame.barrels[barrelIndex];
}

// .text:0x001324E8 size:0x9F4 mapped:0x8077157C
void barrelBatterSwitcher(void) {
    switch (g_GameLogic.gameStatus) {
    case GAME_STATUS_LOAD_GAME:
        bB_LoadGame();
        break;
    case GAME_STATUS_TRANSITION_MINIGAME_TO_BATTING:
        fn_3_13207C();
        break;
    case GAME_STATUS_TRANSITION_TO_MINIGAME_START:
        fn_3_131FFC();
        break;
    case GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY:
        fn_3_131EC4();
        break;
    case GAME_STATUS_DEFAULT:
        fn_3_131C88();
        break;
    case GAME_STATUS_AT_BAT:
        bB_AtBat();
        break;
    case GAME_STATUS_LIVE_BALL:
        fn_3_1307D0();
        break;
    case GAME_STATUS_TRANSITION:
        barrelBatterTransitionToMainFunction();
        break;
    case GAME_STATUS_MINIGAME_NEW_ROUND:
        fn_3_13128C();
        break;
    case GAME_STATUS_INNING_TRANSITION:
        fn_3_13119C();
        break;
    case GAME_STATUS_TRANSITION_MINIGAME_POSTGAME:
        fn_3_1312D4();
        break;
    case GAME_STATUS_GAME_START_MOVIE:
    case GAME_STATUS_END_OF_GAME:
    case GAME_STATUS_0xA:
    case GAME_STATUS_PAUSED:
    case GAME_STATUS_0xC:
    case GAME_STATUS_HOW_TO_PLAY_SCREEN:
    case GAME_STATUS_MVP_END_GAME:
    case GAME_STATUS_0x10:
    case GAME_STATUS_0x11:
    case GAME_STATUS_0x12:
    case GAME_STATUS_HOMERUN_END:
    case GAME_STATUS_HOMERUN_LAP:
    case GAME_STATUS_BATTER_CELEBRATION:
    case GAME_STATUS_STAR_CHANCE_VS:
    case GAME_STATUS_CHAMPIONSHIP:
    case GAME_STATUS_0x18:
        break;
    }
}

// .text:0x001323CC size:0x11C mapped:0x80771460
void fn_3_1323CC(void) {
    u32 i;

    for (i = 0; i < 15; i++) {
        if (g_Minigame.barrels[i].barrelState == BB_BARREL_STATE_DROPPING) {
            fn_3_12F9D4(i);
        }
    }
}

// .text:0x001320BC size:0x310 mapped:0x80771150
void bB_LoadGame(void) {
    s8 value;

    if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_0) {
        initializeSomethingDuringTransition();

        g_GameLogic.secondaryGameMode = SECONDARY_GAME_MODE_BARREL_BATTER;

        g_Minigame.miniGameCurrentPoints[0] = 0;
        g_Minigame.miniGameLatestPoints[0] = 0;
        *(s16 *)((u8 *)&g_Minigame + 0x18BC) = 0;
        *(s16 *)((u8 *)&g_Minigame + 0x18BE) = 0;
        *((s8 *)&g_Minigame + 0x18F4) = -1;
        ((s8 *)g_Minigame.minigameFielderIndex)[0] = -1;
        ((s8 *)g_Minigame._18FC)[0] = -1;
        *(s8 *)&g_Minigame._1900[0] = -1;
        *((u8 *)&g_Minigame + 0x18F0) = 1;

        g_Minigame.miniGameCurrentPoints[1] = 0;
        g_Minigame.miniGameLatestPoints[1] = 0;
        *(s16 *)((u8 *)&g_Minigame + 0x18C0) = 0;
        *(s16 *)((u8 *)&g_Minigame + 0x18C2) = 0;
        *((s8 *)&g_Minigame + 0x18F5) = -1;
        ((s8 *)g_Minigame.minigameFielderIndex)[1] = -1;
        ((s8 *)g_Minigame._18FC)[1] = -1;
        *(s8 *)&g_Minigame._1900[1] = -1;
        *((u8 *)&g_Minigame + 0x18F1) = 1;

        g_Minigame.miniGameCurrentPoints[2] = 0;
        g_Minigame.miniGameLatestPoints[2] = 0;
        *(s16 *)((u8 *)&g_Minigame + 0x18C4) = 0;
        *(s16 *)((u8 *)&g_Minigame + 0x18C6) = 0;
        *((s8 *)&g_Minigame + 0x18F6) = -1;
        ((s8 *)g_Minigame.minigameFielderIndex)[2] = -1;
        ((s8 *)g_Minigame._18FC)[2] = -1;
        *(s8 *)&g_Minigame._1900[2] = -1;
        *((u8 *)&g_Minigame + 0x18F2) = 1;

        g_Minigame.miniGameCurrentPoints[3] = 0;
        g_Minigame.miniGameLatestPoints[3] = 0;
        *(s16 *)((u8 *)&g_Minigame + 0x18C8) = 0;
        *(s16 *)((u8 *)&g_Minigame + 0x18CA) = 0;
        *((s8 *)&g_Minigame + 0x18F7) = -1;
        ((s8 *)g_Minigame.minigameFielderIndex)[3] = -1;
        ((s8 *)g_Minigame._18FC)[3] = -1;
        *(s8 *)&g_Minigame._1900[3] = -1;
        *((u8 *)&g_Minigame + 0x18F3) = 1;

        g_Scores.Inning = 0;
        g_Minigame.pointsReqToWin_challenge = 0;
        g_Minigame._1A37 = 0;
        *(s8 *)&g_Minigame.minigamePlayerSelectedOrder = -1;
        g_Minigame.rosterID = -1;
        g_Minigame.minigameElapsedFrames = 0;
        g_Minigame.bB_bombBarrelHitInd_bOD_hrYaw = 0;
        g_Minigame.bB_bombBarrelID_bOD_hrPitch = -1;

        if (g_Minigame.multiPlayerInd == 0) {
            value = lbl_3_data_2127C[g_Minigame.GameMode_MiniGame][g_Minigame.soloMinigameDifficulty];
            g_Scores.inningLimit = 1;
            g_Minigame.minigameControlStruct[0].aIStrength[0] = value;
            g_Minigame.minigameControlStruct[0].aIStrength[1] = value;
            g_Minigame.minigameControlStruct[0].aIStrength[2] = value;
            g_Minigame.minigameControlStruct[0].aIStrength[3] = value;
            if (g_Minigame.soloMinigameDifficulty <= MINIGAME_DIFFICULTY_MULTIPLAYER_CHALLENGE_HARD) {
                g_Minigame.pointsReqToWin_challenge = bB_challengePointsRequired[g_Minigame.soloMinigameDifficulty];
            }
        } else {
            if (g_Minigame._1A3C != 0) {
                value = lbl_3_data_2127C[7][0];
                g_Minigame.minigameControlStruct[0].aIStrength[0] = value;
                g_Minigame.minigameControlStruct[0].aIStrength[1] = value;
                g_Minigame.minigameControlStruct[0].aIStrength[2] = value;
                g_Minigame.minigameControlStruct[0].aIStrength[3] = value;
            }
            g_Scores.inningLimit = cost_15_bB_pitchesPerRound_solo[5];
        }

        fn_3_12FE84();

        g_Minigame.turnNumberWithinRound = 0;
        g_Minigame.barrelBatter_scoreCalculatedInd = 0;
        g_Minigame.barrelBatterChargeMeter = 0;
        g_GameLogic._125++;
    } else {
        SetGameStatus(GAME_STATUS_GAME_START_MOVIE);
    }
}

// .text:0x0013207C size:0x40 mapped:0x80771110
void fn_3_13207C(void) {
    sndFXStartEx(0x1bd, lbl_800EFBA4[6], 0x3f, 0);
    SetGameStatus(GAME_STATUS_TRANSITION_TO_MINIGAME_START);
}

// .text:0x00131FFC size:0x80 mapped:0x80771090
void fn_3_131FFC(void) {
    g_Scores.Inning++;
    g_Minigame.turnNumberWithinRound = 0;

    if (g_Minigame.multiPlayerInd == 0) {
        SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
        return;
    }

    fn_3_10F550(4, 0);
    if (g_Scores.Inning == 1) {
        fn_3_10AD48();
    }
    SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
}

// .text:0x00131EC4 size:0x138 mapped:0x80770F58
void fn_3_131EC4(void) {
    switch (g_GameLogic._125) {
    case TRANSITION_CALCULATION_TYPE_0:
        g_Minigame.rosterID = ((s8 *)g_Minigame.minigameControlStruct[0].aIStrength)[g_Minigame.turnNumberWithinRound + 4];
        g_GameLogic.pre_PostMiniGameInd = TRUE;
        g_Minigame.miniGameTurnCounter = 0;
        g_Minigame.pointsTargetReachedInd = 0;
        if (g_Minigame.multiPlayerInd == 0) {
            g_Minigame.bB_pitchesRemainingInTurn = cost_15_bB_pitchesPerRound_solo[g_Minigame.soloMinigameDifficulty];
        } else {
            g_Minigame.bB_pitchesRemainingInTurn = cost_15_bB_pitchesPerRound_solo[4];
        }
        resetBallValuesBetweenBatters();
        resetPitcherValuesBetweenBatters(0);
        setPitcherStatsToInMemPitcher(-1);
        setBatterContactConstants();
        setInMemBatterConstants(g_Minigame.rosterID);
        highLevelSimulationFlag[2] = 0;
        g_GameLogic._125++;
        break;
    case TRANSITION_CALCULATION_TYPE_1:
        if (someAnimationIndFunction() != 0) {
            us80893314[1] = 1;
            g_GameLogic._125++;
        }
        break;
    default:
        animRelated[0xB6] = 1;
        SetGameStatus(GAME_STATUS_DEFAULT);
        break;
    }
}

// .text:0x00131C88 size:0x23C mapped:0x80770D1C
void fn_3_131C88(void) {
    fn_3_131114();
    fn_3_12FD6C();

    g_Minigame.bOD_fireworkBurstCount = 0;
    g_Minigame.turnOverStatus = 0;
    g_Minigame.barrelBatter_scoreCalculatedInd = 0;
    g_Minigame.barrelBatter_hitBarrelID = -1;
    g_Minigame.barrelBatter_barrelsHit = 0;
    g_Minigame.bB_bombBarrelHitInd_bOD_hrYaw = 0;
    g_Ball.totalFramesAtPlay = 0;
    g_Ball.framesSinceHit = -1;
    g_Batter.swingInd = FALSE;
    g_Batter.framesSinceStartOfSwing = 0;
    g_Pitcher.windupCountdownUntilBallReleased = lbl_3_data_217A4[7];

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

// .text:0x00131540 size:0x748 mapped:0x807705D4
void barrelBatterTransitionToMainFunction(void) {
    switch (g_GameLogic._125) {
    case TRANSITION_CALCULATION_TYPE_0:
        fn_3_12FD6C();
        g_Minigame.turnNumberWithinRound++;
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125++;
        break;
    case TRANSITION_CALCULATION_TYPE_1:
        if (g_Minigame._1A37 == 1) {
            if (g_GameLogic.FrameCountOfCurrentAtBat_Copy >= lbl_3_data_217A4[3]) {
                g_GameLogic._125++;
            }
        } else {
            if (g_GameLogic.FrameCountOfCurrentAtBat_Copy >= lbl_3_data_217A4[2]) {
                g_GameLogic._125++;
            }
        }
        break;
    case TRANSITION_CALCULATION_TYPE_2:
        changeScene(3, 6);
        g_GameLogic._125++;
        break;
    case TRANSITION_CALCULATION_TYPE_3:
        if (lbl_8037169C[0x13] != 0) {
            if (g_Minigame.multiPlayerInd != 0) {
                if (g_Minigame.turnNumberWithinRound < g_Minigame.miniGameNumberOfParticipants) {
                    SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
                } else {
                    SetGameStatus(GAME_STATUS_MINIGAME_NEW_ROUND);
                }
            } else {
                minigameCalculateRankings();
                SetGameStatus(GAME_STATUS_MVP_END_GAME);
                fn_3_12FE84();
                fn_3_12FD6C();
            }
            fn_3_14CA00();
            animRelated[0xB7] = 1;
        }
        break;
    }

    fn_3_12FAC4();
}

// .text:0x001312D4 size:0x26C mapped:0x80770368
void fn_3_1312D4(void) {
    minigameCalculateRankings();
    SetGameStatus(GAME_STATUS_MVP_END_GAME);
    fn_3_12FE84();
    fn_3_12FD6C();
}

// .text:0x0013128C size:0x48 mapped:0x80770320
void fn_3_13128C(void) {
    if (g_Scores.Inning >= g_Scores.inningLimit) {
        SetGameStatus(GAME_STATUS_TRANSITION_MINIGAME_POSTGAME);
    } else {
        SetGameStatus(GAME_STATUS_TRANSITION_TO_MINIGAME_START);
    }
}

// .text:0x0013119C size:0xF0 mapped:0x80770230
void fn_3_13119C(void) {
    switch (g_GameLogic._125) {
    case TRANSITION_CALCULATION_TYPE_0:
        changeScene(1, 6);
        g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_1;
        break;
    case TRANSITION_CALCULATION_TYPE_1:
        if (g_GameLogic.FrameCountOfCurrentPitch >= lbl_3_data_18C48[2] ||
            (g_GameLogic.FrameCountOfCurrentPitch >= lbl_3_data_18C48[1] &&
             checkForButtonPressToSkip(1, 0x1100))) {
            changeScene(3, 6);
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_2;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_2:
        if (lbl_8037169C[0x13] != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_3;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_3:
        SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
        break;
    }
}

// .text:0x00131114 size:0x88 mapped:0x807701A8
void fn_3_131114(void) {
    setInMemBatterConstants(g_Minigame.rosterID);
    setDefaultInMemBall();
    setDefaultInMemPitcher();
    setDefaultInMemBatter();
    setDefaultInMemRunner();
    setDefaultInMemFielder();
    memset(&g_Minigame._1D7C, 0, 0x78);
    pauseAnimations();
    pauseStateOnStadiums();
    g_FieldingLogic.playOverCounter = 0;
    g_UnkSimulation_31AC0._05 = 0;
    g_UnkSimulation_31AC0._06 = 4;
}

// .text:0x00130C6C size:0x4A8 mapped:0x8076FD00
void bB_AtBat(void) {
    if (g_Minigame.turnOverStatus == 0) {
        if (checkForPauses()) {
            return;
        }
        if (g_Minigame.miniGameTurnCounter != 0 || g_GameLogic.FrameCountOfCurrentPitch >= lbl_3_data_217A4[8]) {
            atBat_Pitcher();
        }
        bB_AI();
        atBat_batter();
        bB_clearAIControlled();
        running_MainFunction();
        fn_3_12FAC4();
    }

    if (g_Minigame.turnOverStatus == 0) {
        if (g_Pitcher.pitcherActionState != PITCHER_ACTION_STATE_NO_CONTACT) {
            return;
        }
        if (g_Minigame.bB_pitchesRemainingInTurn == 0) {
            g_Minigame.turnOverStatus = 1;
            g_Minigame.pointsTargetReachedInd = 2;
        }
        g_Minigame.bB_bombBarrelHitInd_bOD_hrYaw = 0;
        g_Minigame.bB_bombBarrelID_bOD_hrPitch = -1;
        return;
    }

    if (g_Minigame.turnOverStatus == 1) {
        g_Minigame.turnOverStatus = 2;
        g_GameLogic.CountdownUntilFade = lbl_3_data_217A4[0];
    }
    g_GameLogic.CountdownUntilFade--;
    if (g_Minigame.pointsTargetReachedInd != 0) {
        if (g_GameLogic.CountdownUntilFade <= 0) {
            g_Minigame.bB_bombBarrelID_bOD_hrPitch = -1;
            g_GameLogic.pre_PostMiniGameInd = 1;
            g_GameLogic.minigameLastTurnSuccessInd = 1;
            g_GameLogic.hudLoadingRelated = 1;
            SetGameStatus(GAME_STATUS_TRANSITION);
        }
    } else if (g_GameLogic.CountdownUntilFade <= 0) {
        SetGameStatus(GAME_STATUS_DEFAULT);
    }
    if (g_Minigame.pointsTargetReachedInd != 0 &&
        (g_Minigame.multiPlayerInd == 0 ||
         (g_Minigame.multiPlayerInd != 0 &&
          g_Minigame.turnNumberWithinRound + 1 >= g_Minigame.miniGameNumberOfParticipants &&
          g_Scores.Inning >= g_Scores.inningLimit)) &&
        g_Minigame._1A37 == 0 && g_GameLogic.CountdownUntilFade == 1) {
        sndFXStartEx(0x1be, lbl_800EFBA4[7], 0x3f, 0);
    }
}

// .text:0x00130ACC size:0x1A0 mapped:0x8076FB60
void bobombDerbyRelated(void) {
    if (g_Minigame.turnOverStatus == 0) {
        if (g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_NO_CONTACT) {
            if (g_Minigame.bB_pitchesRemainingInTurn == 0) {
                g_Minigame.turnOverStatus = 1;
                g_Minigame.pointsTargetReachedInd = 2;
            }
            g_Minigame.bB_bombBarrelHitInd_bOD_hrYaw = 0;
            g_Minigame.bB_bombBarrelID_bOD_hrPitch = -1;
        }
    } else {
        if (g_Minigame.turnOverStatus == 1) {
            g_Minigame.turnOverStatus = 2;
            g_GameLogic.CountdownUntilFade = lbl_3_data_217A4[0];
        }
        g_GameLogic.CountdownUntilFade--;
        if (g_Minigame.pointsTargetReachedInd != 0) {
            if (g_GameLogic.CountdownUntilFade <= 0) {
                g_Minigame.bB_bombBarrelID_bOD_hrPitch = -1;
                g_GameLogic.pre_PostMiniGameInd = 1;
                g_GameLogic.minigameLastTurnSuccessInd = 1;
                g_GameLogic.hudLoadingRelated = 1;
                SetGameStatus(GAME_STATUS_TRANSITION);
            }
        } else if (g_GameLogic.CountdownUntilFade <= 0) {
            SetGameStatus(GAME_STATUS_DEFAULT);
        }
        if (g_Minigame.pointsTargetReachedInd != 0 &&
            (g_Minigame.multiPlayerInd == 0 ||
             (g_Minigame.multiPlayerInd != 0 &&
              g_Minigame.turnNumberWithinRound + 1 >= g_Minigame.miniGameNumberOfParticipants &&
              g_Scores.Inning >= g_Scores.inningLimit)) &&
            g_Minigame._1A37 == 0 && g_GameLogic.CountdownUntilFade == 1) {
            sndFXStartEx(0x1be, lbl_800EFBA4[7], 0x3f, 0);
        }
    }
}

// .text:0x00130A80 size:0x4C mapped:0x8076FB14
void fn_3_130A80(void) {
    g_Minigame.bB_bombBarrelID_bOD_hrPitch = -1;
    g_GameLogic.pre_PostMiniGameInd = TRUE;
    g_GameLogic.minigameLastTurnSuccessInd = TRUE;
    g_GameLogic.hudLoadingRelated = TRUE;
    SetGameStatus(GAME_STATUS_TRANSITION);
}

// .text:0x001307D0 size:0x2B0 mapped:0x8076F864
void fn_3_1307D0(void) {
    ballPhysica();
    fn_3_12FAC4();
    barrelBatterLiveBallSubFun();
}

// .text:0x00130288 size:0x548 mapped:0x8076F31C
void barrelBatterLiveBallSubFun(void) {
    if (g_Minigame.turnOverStatus == 0) {
        if (g_Ball.framesSinceHit >= lbl_3_data_217A4[4]) {
            g_Minigame.turnOverStatus = 1;
            if (g_Minigame.multiPlayerInd == 0 && g_Minigame.soloMinigameDifficulty <= MINIGAME_DIFFICULTY_MULTIPLAYER_CHALLENGE_HARD &&
                g_Minigame.miniGameCurrentPoints[g_Minigame.rosterID] >= g_Minigame.pointsReqToWin_challenge) {
                g_Minigame.pointsTargetReachedInd = 2;
                g_Minigame._1A37 = 1;
                g_Minigame.challenge_minigame_haven_tWonYetIndicator = 0;
                fn_3_10F550(1, lbl_3_data_217A4[10]);
            }

            if (g_Minigame.bB_bombBarrelHitInd_bOD_hrYaw != 0) {
                g_Minigame.bB_pitchesRemainingInTurn += cost_15_bB_pitchesPerRound_solo[g_Minigame.multiPlayerInd + 6];
            }

            if (g_Minigame.bB_pitchesRemainingInTurn == 0) {
                g_Minigame.pointsTargetReachedInd = 2;
            }
        }
    }

    if (g_Minigame.turnOverStatus == 0) {
        return;
    }
    if (g_Minigame.turnOverStatus == 1) {
        g_Minigame.turnOverStatus = 2;
        g_GameLogic.CountdownUntilFade = lbl_3_data_217A4[1];
    }

    g_GameLogic.CountdownUntilFade--;
    if (g_GameLogic.CountdownUntilFade <= 0) {
        if (fn_3_12ED80()) {
            fn_3_12FFD4();
        }
    }

    if (g_Minigame.pointsTargetReachedInd != 0 &&
        (g_Minigame.multiPlayerInd == 0 ||
         (g_Minigame.multiPlayerInd != 0 &&
          g_Minigame.turnNumberWithinRound + 1 >= g_Minigame.miniGameNumberOfParticipants &&
          g_Scores.Inning >= g_Scores.inningLimit)) &&
        g_Minigame._1A37 == 0 && g_GameLogic.CountdownUntilFade == 1) {
        sndFXStartEx(0x1be, lbl_800EFBA4[7], 0x3f, 0);
    }
}

// .text:0x0012FFD4 size:0x2B4 mapped:0x8076F068
void fn_3_12FFD4(void) {
    g_Minigame.bB_bombBarrelID_bOD_hrPitch = -1;
    fn_3_12EB10();

    bB_chooseBombBarrel_dropNewBarrels();
    if (g_Minigame.pointsTargetReachedInd != 0) {
        SetGameStatus(GAME_STATUS_TRANSITION);
    } else {
        SetGameStatus(GAME_STATUS_DEFAULT);
    }
}

// .text:0x0012FE84 size:0x150 mapped:0x8076EF18
void fn_3_12FE84(void) {
    int i;
    for (i = 0; i < 15; i++) {
        g_Minigame.barrels[i].barrelState = BB_BARREL_STATE_DROPPING;
        g_Minigame.barrels[i].animationCounter = 0;
        g_Minigame.barrels[i].replacingBarrelInd = FALSE;
        g_Minigame.barrels[i].desiredPos.x = barrelBaseCoordinates[i].x;
        g_Minigame.barrels[i].desiredPos.y = barrelBaseCoordinates[i].y;
        g_Minigame.barrels[i].desiredPos.z = barrelBaseCoordinates[i].z;
        g_Minigame.barrels[i].currentPos.x = barrelBaseCoordinates[i].x;
        g_Minigame.barrels[i].currentPos.y = barrelBaseCoordinates[i].y;
        g_Minigame.barrels[i].currentPos.z = barrelBaseCoordinates[i].z;
        g_Minigame.barrels[i].currentPos.y += lbl_3_data_21770[0];
        g_Minigame.barrels[i].currentPos.y += (i % 3) * 10 - (random_fn_3_9EE24(0x65) * 5) / 100.0;
        g_Minigame.barrels[i].barrelColour = random_fn_3_9EE24(3);
    }
}

// .text:0x0012FD6C size:0x118 mapped:0x8076EE00
void fn_3_12FD6C(void) {
    int i;
    for (i = 0; i < 15; i++) {
        if (g_Minigame.barrels[i].barrelState != BB_BARREL_STATE_EMPTY) {
            g_Minigame.barrels[i].posAtStartOfTurn.x = g_Minigame.barrels[i].currentPos.x;
            g_Minigame.barrels[i].posAtStartOfTurn.y = g_Minigame.barrels[i].currentPos.y;
            g_Minigame.barrels[i].posAtStartOfTurn.z = g_Minigame.barrels[i].currentPos.z;
            g_Minigame.barrels[i].barrelState = BB_BARREL_STATE_DROPPING;
        }
        g_Minigame.barrels[i].animationCounter = 0;
    }
}

// .text:0x0012FAC4 size:0x2A8 mapped:0x8076EB58
void fn_3_12FAC4(void) {
    BB_barrelStruct *barrel;
    int i;

    bB_checkIfBarrelHitAndCalculateScore();
    for (i = 0; i < 15; i++) {
        barrel = &g_Minigame.barrels[i];

        if (barrel->animationCounter < 0x7ffe) {
            barrel->animationCounter++;
        } else {
            barrel->animationCounter = 0x7fff;
        }

        if (barrel->barrelState == BB_BARREL_STATE_DROPPING) {
            fn_3_12F9D4(i);
        }
        if (barrel->barrelState == BB_BARREL_STATE_READY_TO_BLOW_UP) {
            fn_3_12F28C(i);
        }
        if (barrel->replacingBarrelInd != 0) {
            bB_likelyReplaceBlownUpBarrels(i);
        }
    }
}

// .text:0x0012F9D4 size:0xF0 mapped:0x8076EA68
void fn_3_12F9D4(int barrelIndex) {
    BB_barrelStruct *barrel = &g_Minigame.barrels[barrelIndex];

    barrel->currentPos.y += lbl_3_data_21770[1];
    if (barrel->currentPos.y < barrel->desiredPos.y) {
        barrel->currentPos.y = barrel->desiredPos.y;
        if (barrel->posAtStartOfTurn.y != barrel->desiredPos.y) {
            VecXYZ pos;
            pos.x = barrel->currentPos.x;
            pos.y = barrel->currentPos.y;
            pos.z = barrel->currentPos.z;
            pos.y = -pos.y;
            pos.z -= 1.0f;
            if (barrel->currentPos.y <= 0.0f) {
                fn_8004C108(&pos, TRUE);
                callSfx(0x2e4);
            } else {
                fn_8004C108(&pos, FALSE);
                callSfx(0x2e5);
            }
        }
        barrel->barrelState = BB_BARREL_STATE_NEUTRAL;
    }
}

// .text:0x0012F624 size:0x3B0 mapped:0x8076E6B8
void bB_checkIfBarrelHitAndCalculateScore(void) {
    s32 counter;
    int barrelRow;
    int barrelColumn;
    int barrelID;
    int delayToBlowUp;
    BOOL loopAgainInd;
    int points;
    int barrelHitFlags[15];

    if (g_Ball.framesSinceHit <= 0) {
        return;
    }
    if (g_Minigame.barrelBatter_scoreCalculatedInd != 0) {
        return;
    }
    if (g_Ball.AtBat_Contact_BallPos.z < barrelBaseCoordinates[0].z - lbl_3_data_21770[2]) {
        return;
    }
    if (g_Batter.contactType < HIT_CONTACT_TYPE_RIGHT_NICE || g_Batter.contactType > HIT_CONTACT_TYPE_LEFT_NICE) {
        return;
    }

    for (barrelRow = 0; barrelRow < 3; barrelRow++) {
        if (g_Ball.AtBat_Contact_BallPos.y < barrelBaseCoordinates[barrelRow].y + lbl_3_data_21770[3]) {
            break;
        }
    }

    if (barrelRow < 3 && !(g_Ball.AtBat_Contact_BallPos.x < barrelBaseCoordinates[0].x - lbl_3_data_21770[2])) {
        for (barrelColumn = 0; barrelColumn < 15; barrelColumn += 3) {
            if (g_Ball.AtBat_Contact_BallPos.x < barrelBaseCoordinates[barrelColumn].x + lbl_3_data_21770[2]) {
                break;
            }
        }

        if (barrelColumn < 15) {
            g_Minigame.barrelBatter_hitBarrelID = barrelColumn + barrelRow;
            for (counter = 0; counter < 15; counter++) {
                barrelHitFlags[counter] = FALSE;
            }

            barrelID = g_Minigame.barrelBatter_hitBarrelID;
            g_Minigame.barrels[barrelID].barrelState = BB_BARREL_STATE_READY_TO_BLOW_UP;
            delayToBlowUp = lbl_3_data_21788.baseBlowUpDelay + lbl_3_data_21788.blowUpDelayIncrement;
            g_Minigame.barrels[barrelID].animationCounter = 0;
            g_Minigame.barrels[barrelID].delayUntilBlownUp = lbl_3_data_21788.baseBlowUpDelay;

            if (g_Minigame.bB_bombBarrelID_bOD_hrPitch == barrelID && g_Minigame.barrels[barrelID].barrelColour == BB_BARREL_COLOUR_BROWN) {
                g_Minigame.bB_bombBarrelHitInd_bOD_hrYaw = TRUE;
            }

            while (TRUE) {
                loopAgainInd = FALSE;
                for (counter = 0; counter < 15; counter++) {
                    if (g_Minigame.barrels[counter].barrelState == BB_BARREL_STATE_READY_TO_BLOW_UP &&
                        g_Minigame.barrels[counter].delayUntilBlownUp != delayToBlowUp &&
                        barrelHitFlags[counter] == FALSE) {
                        if (g_Minigame.bB_bombBarrelHitInd_bOD_hrYaw != 0) {
                            bB_connectingBarrels(counter, delayToBlowUp, TRUE);
                        } else {
                            bB_connectingBarrels(counter, delayToBlowUp, FALSE);
                        }
                        barrelHitFlags[counter] = TRUE;
                        loopAgainInd = TRUE;
                        g_Minigame.barrelBatter_barrelsHit++;
                    }
                }
                if (!loopAgainInd) {
                    break;
                }
                delayToBlowUp += lbl_3_data_21788.blowUpDelayIncrement;
            }

            if (g_Minigame.bB_bombBarrelHitInd_bOD_hrYaw == 0 && g_Minigame.barrelBatter_barrelsHit >= 2) {
                g_Minigame.barrelBatterChargeMeter += g_Minigame.barrelBatter_barrelsHit - 1;
            }

            if (g_Minigame.barrelBatter_barrelsHit <= 1) {
                points = lbl_3_data_217A4[5] * g_Minigame.barrelBatter_barrelsHit;
            } else {
                points = g_Minigame.barrelBatter_barrelsHit * ((g_Minigame.barrelBatter_barrelsHit - 1) * lbl_3_data_217A4[5]);
            }

            g_Minigame.miniGameCurrentPoints[g_Minigame.rosterID] += points;
            *(s16 *)((u8 *)&g_Minigame + 0x1DF4) = points;
            if (!g_d_GameSettings.exhibitionMatchInd && g_Minigame.rosterID == lbl_3_common_bss_37400[0x20]) {
                starMissionsMinigamesSpecialAction(2, points, g_Minigame.barrelBatter_barrelsHit);
            }
        }
    }

    g_Minigame.barrelBatter_scoreCalculatedInd = TRUE;
}

// .text:0x0012F424 size:0x200 mapped:0x8076E4B8
void bB_connectingBarrels(int barrelNum, int blowUpDelay, BOOL bombBarrelHitInd) {
    int barrelColour = g_Minigame.barrels[barrelNum].barrelColour;

    if (barrelNum % 3 != 2) {
        int barrelAbove = barrelNum + 1;
        if (g_Minigame.barrels[barrelAbove].barrelState == BB_BARREL_STATE_NEUTRAL &&
            barrelAbove != g_Minigame.bB_bombBarrelID_bOD_hrPitch &&
            (g_Minigame.barrels[barrelAbove].barrelColour == barrelColour || bombBarrelHitInd)) {
            g_Minigame.barrels[barrelAbove].barrelState = BB_BARREL_STATE_READY_TO_BLOW_UP;
            g_Minigame.barrels[barrelAbove].animationCounter = 0;
            g_Minigame.barrels[barrelAbove].delayUntilBlownUp = blowUpDelay;
        }
    }

    if ((s32)barrelNum % 3 != 0) {
        int barrelBelow = barrelNum - 1;
        if (g_Minigame.barrels[barrelBelow].barrelState == BB_BARREL_STATE_NEUTRAL &&
            barrelBelow != g_Minigame.bB_bombBarrelID_bOD_hrPitch &&
            (g_Minigame.barrels[barrelBelow].barrelColour == barrelColour || bombBarrelHitInd)) {
            g_Minigame.barrels[barrelBelow].barrelState = BB_BARREL_STATE_READY_TO_BLOW_UP;
            g_Minigame.barrels[barrelBelow].animationCounter = 0;
            g_Minigame.barrels[barrelBelow].delayUntilBlownUp = blowUpDelay;
        }
    }

    if (barrelNum / 3 > 0) {
        int barrelToLeft = barrelNum - 3;
        if (g_Minigame.barrels[barrelToLeft].barrelState == BB_BARREL_STATE_NEUTRAL &&
            barrelToLeft != g_Minigame.bB_bombBarrelID_bOD_hrPitch &&
            (g_Minigame.barrels[barrelToLeft].barrelColour == barrelColour || bombBarrelHitInd)) {
            g_Minigame.barrels[barrelToLeft].barrelState = BB_BARREL_STATE_READY_TO_BLOW_UP;
            g_Minigame.barrels[barrelToLeft].animationCounter = 0;
            g_Minigame.barrels[barrelToLeft].delayUntilBlownUp = blowUpDelay;
        }
    }

    if (barrelNum / 3 < 4) {
        int barrelToRight = barrelNum + 3;
        if (g_Minigame.barrels[barrelToRight].barrelState == BB_BARREL_STATE_NEUTRAL &&
            barrelToRight != g_Minigame.bB_bombBarrelID_bOD_hrPitch &&
            (g_Minigame.barrels[barrelToRight].barrelColour == barrelColour || bombBarrelHitInd)) {
            g_Minigame.barrels[barrelToRight].barrelState = BB_BARREL_STATE_READY_TO_BLOW_UP;
            g_Minigame.barrels[barrelToRight].animationCounter = 0;
            g_Minigame.barrels[barrelToRight].delayUntilBlownUp = blowUpDelay;
        }
    }
}

// .text:0x0012F28C size:0x198 mapped:0x8076E320
void fn_3_12F28C(int barrelIndex) {
    BB_barrelStruct *barrel = &g_Minigame.barrels[barrelIndex];

    if (barrel->animationCounter >= barrel->delayUntilBlownUp) {
        barrel->barrelState = BB_BARREL_STATE_BLOWN_UP;
        barrel->animationCounter = 0;
        fn_3_12EE68(barrelIndex);
        setCharacterAnimations(g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.rosterID], 0);
    }
}

// .text:0x0012EFA4 size:0x2E8 mapped:0x8076E038
void bB_likelyReplaceBlownUpBarrels(int barrelIndex) {
    BB_barrelStruct *barrel = &g_Minigame.barrels[barrelIndex];

    barrel->currentPos.y += barrel->velo_bounceUpOnBlowUp;
    if (barrel->velo_bounceUpOnBlowUp > 0.0f && barrelIndex % 3 == 1) {
        BB_barrelStruct *next = &g_Minigame.barrels[barrelIndex + 1];

        if (next->barrelState != BB_BARREL_STATE_BLOWN_UP && next->replacingBarrelInd == FALSE) {
            fn_3_12EE68(barrelIndex);
        }
        if (next->currentPos.y - barrel->currentPos.y < lbl_3_data_21770[3]) {
            barrel->velo_bounceUpOnBlowUp -= lbl_3_data_21770[5];
        }
    }

    barrel->velo_bounceUpOnBlowUp -= lbl_3_data_21770[5];
    if (barrel->velo_bounceUpOnBlowUp > 0.0f && barrelIndex % 3 == 2 &&
        barrel->currentPos.y - bB_getBarrel(barrelIndex - 1)->currentPos.y < lbl_3_data_21770[3]) {
        barrel->velo_bounceUpOnBlowUp += lbl_3_data_21770[5];
    }

    if (barrel->currentPos.y < barrel->_28) {
        barrel->currentPos.y = barrel->_28;
        barrel->velo_bounceUpOnBlowUp = 0.0f;
        barrel->replacingBarrelInd = FALSE;
        if (barrel->barrelState != BB_BARREL_STATE_BLOWN_UP) {
            VecXYZ pos;
            pos.x = barrel->currentPos.x;
            pos.y = barrel->currentPos.y;
            pos.z = barrel->currentPos.z;
            pos.z -= 1.0f;
            pos.y = -barrel->_28;
            if (0.0f == barrel->_28) {
                fn_8004C108(&pos, TRUE);
                callSfx(0x2e4);
            } else {
                fn_8004C108(&pos, FALSE);
                callSfx(0x2e5);
            }
        }
    }
}

// .text:0x0012EE68 size:0x13C mapped:0x8076DEFC
void fn_3_12EE68(int barrelIndex) {
    int posInRow = barrelIndex % 3;
    BB_barrelStruct *barrel = &g_Minigame.barrels[barrelIndex];
    BB_barrelStruct *nextBarrel;

    if (posInRow == 2) {
        return;
    }

    nextBarrel = &g_Minigame.barrels[barrelIndex + 1];

    if (nextBarrel->barrelState == BB_BARREL_STATE_BLOWN_UP) {
        return;
    }
    if (nextBarrel->barrelState == BB_BARREL_STATE_READY_TO_BLOW_UP) {
        if (nextBarrel->currentPos.y - barrel->currentPos.y > lbl_3_data_21770[3] + 0.3) {
            return;
        }
    }

    nextBarrel->replacingBarrelInd = TRUE;
    nextBarrel->velo_bounceUpOnBlowUp = lbl_3_data_21770[4];

    if ((barrelIndex + 1) % 3 == 1) {
        nextBarrel->_28 = barrelBaseCoordinates[barrelIndex].y;
    } else {
        u8 neighbourSettled = FALSE;
        neighbourSettled |= g_Minigame.barrels[barrelIndex - 1].barrelState == BB_BARREL_STATE_NEUTRAL;
        neighbourSettled |= g_Minigame.barrels[barrelIndex].barrelState == BB_BARREL_STATE_NEUTRAL;
        nextBarrel->_28 = barrelBaseCoordinates[neighbourSettled].y;
    }
}

// .text:0x0012ED80 size:0xE8 mapped:0x8076DE14
E(u8, BOOL) fn_3_12ED80(void) {
    int i;
    for (i = 1; i < 15; i += 3) {
        if (g_Minigame.barrels[i].replacingBarrelInd) {
            return FALSE;
        }
        if (g_Minigame.barrels[i + 1].replacingBarrelInd) {
            return FALSE;
        }
    }
    return TRUE;
}

// .text:0x0012EB10 size:0x270 mapped:0x8076DBA4
void fn_3_12EB10(void) {
    int row;
    int pos;
    int k;

    for (row = 0; row < 5; row++) {
        for (pos = 0; pos < 2; pos++) {
            for (;;) {
                if (g_Minigame.barrels[row * 3 + pos].barrelState != BB_BARREL_STATE_BLOWN_UP) {
                    break;
                }
                for (k = pos + 1; k < 3; k++) {
                    bB_shiftBarrelDown(row * 3 + k);
                }
            }
        }
    }

    for (row = 0; row < 5; row++) {
        u8 *state = &bB_getBarrel(row * 3 + 2)->barrelState;
        if (*state == BB_BARREL_STATE_BLOWN_UP) {
            *state = BB_BARREL_STATE_EMPTY;
        }
    }
}

// .text:0x0012E8FC size:0x214 mapped:0x8076D990
void bB_chooseBombBarrel_dropNewBarrels(void) {
    BOOL bombBarrelChosen = FALSE;
    int barrelsUntilBomb;
    int i;

    if (g_Minigame.barrelBatterChargeMeter >= lbl_3_data_21788.bombBarrelThreshold) {
        for (i = 0, barrelsUntilBomb = 0; i < 15; i++) {
            if (g_Minigame.barrels[i].barrelState == BB_BARREL_STATE_EMPTY) {
                barrelsUntilBomb++;
            }
        }
        barrelsUntilBomb = random_fn_3_9EE24(barrelsUntilBomb);
        g_Minigame.barrelBatterChargeMeter = 0;
        bombBarrelChosen = TRUE;
    }

    for (i = 0; i < 15; i++) {
        if (g_Minigame.barrels[i].barrelState == BB_BARREL_STATE_EMPTY) {
            g_Minigame.barrels[i].barrelState = BB_BARREL_STATE_DROPPING;
            g_Minigame.barrels[i].animationCounter = 0;
            g_Minigame.barrels[i].currentPos.x = barrelBaseCoordinates[i].x;
            g_Minigame.barrels[i].currentPos.y = barrelBaseCoordinates[i].y;
            g_Minigame.barrels[i].currentPos.z = barrelBaseCoordinates[i].z;
            g_Minigame.barrels[i].currentPos.y += lbl_3_data_21770[0];
            g_Minigame.barrels[i].currentPos.y += (i % 3) * 10 - (random_fn_3_9EE24(0x65) * 5) / 100.0;
            g_Minigame.barrels[i].barrelColour = random_fn_3_9EE24(3);
            if (bombBarrelChosen) {
                if (barrelsUntilBomb == 0) {
                    barrelsUntilBomb = -1;
                    g_Minigame.barrels[i].barrelColour = BB_BARREL_COLOUR_BROWN;
                    g_Minigame.bB_bombBarrelID_bOD_hrPitch = (s16)i;
                } else if (barrelsUntilBomb > 0) {
                    barrelsUntilBomb--;
                }
            }
        }
    }
}

// .text:0x0012E83C size:0xC0 mapped:0x8076D8D0
void unused_BarrelBatterRelated(void) {
    int points;

    if (g_Minigame.barrelBatter_barrelsHit <= 1) {
        points = lbl_3_data_217A4[5] * g_Minigame.barrelBatter_barrelsHit;
    } else {
        points = g_Minigame.barrelBatter_barrelsHit * ((g_Minigame.barrelBatter_barrelsHit - 1) * lbl_3_data_217A4[5]);
    }

    g_Minigame.miniGameCurrentPoints[g_Minigame.rosterID] += points;
    g_Minigame.bB_totalPoints = points;
    if (!g_d_GameSettings.exhibitionMatchInd && g_Minigame.rosterID == lbl_3_common_bss_37400[0x20]) {
        starMissionsMinigamesSpecialAction(2, points, g_Minigame.barrelBatter_barrelsHit);
    }
}

// .text:0x0012E808 size:0x34 mapped:0x8076D89C
void fn_3_12E808(void) {
    memset(&g_Minigame._1D7C, 0, 0x78);
}

// .text:0x0012E384 size:0x484 mapped:0x8076D418
u8 bB_countConnectedBarrels(u8 *barrels, s8 barrelIndex, u8 colour) {
    u8 count;

    if (colour == barrels[barrelIndex * 2 + 1] && barrels[barrelIndex * 2] == BB_BARREL_STATE_NEUTRAL) {
        barrels[barrelIndex * 2] = BB_BARREL_STATE_EMPTY;
        count = 1;
        if (barrelIndex / 3 > 0) {
            count += bB_countConnectedBarrels(barrels, barrelIndex - 3, colour);
        }
        if (barrelIndex / 3 < 4) {
            count += bB_countConnectedBarrels(barrels, barrelIndex + 3, colour);
        }
        if (barrelIndex % 3 > 0) {
            count += bB_countConnectedBarrels(barrels, barrelIndex - 1, colour);
        }
        if (barrelIndex % 3 < 2) {
            count += bB_countConnectedBarrels(barrels, barrelIndex + 1, colour);
        }
        return count;
    }
    return 0;
}

// .text:0x0012E17C size:0x208 mapped:0x8076D210
void bB_scoreEachBarrelChoice(s8 *barrelsCleared, s16 *scores, u8 chainBonusInd) {
    u8 simulated[15][2];
    u8 scratch[15][2];
    s8 i;
    s8 pass;
    s8 col;
    s8 row;
    s8 j;
    s8 k;
    s16 bestFollowUp;
    s16 score;
    int n;

    i = 0;
    do {
        j = 0;
        do {
            simulated[j][0] = g_Minigame.barrels[j].barrelState;
            simulated[j][1] = g_Minigame.barrels[j].barrelColour;
            j++;
        } while (j < 15);
        barrelsCleared[i] = bB_countConnectedBarrels(&simulated[0][0], i, simulated[i][1]);
        n = barrelsCleared[i];
        if (n >= 2) {
            scores[i] = (n - 1) * n;
        } else {
            scores[i] = n;
        }

        if (chainBonusInd) {
            pass = 0;
            do {
                col = 0;
                do {
                    row = 0;
                    do {
                        if (simulated[col + row * 3][0] != BB_BARREL_STATE_NEUTRAL) {
                            memcpy(&simulated[col + row * 3], &simulated[col + 1 + row * 3], 2);
                            simulated[col + 1 + row * 3][0] = BB_BARREL_STATE_EMPTY;
                        }
                        row++;
                    } while (row < 5);
                    col++;
                } while (col < 2);
                pass++;
            } while (pass < 2);

            bestFollowUp = 0;
            j = 0;
            do {
                k = 0;
                do {
                    memcpy(&scratch[k], &simulated[k], 2);
                    k++;
                } while (k < 15);
                n = (s8)bB_countConnectedBarrels(&scratch[0][0], j, scratch[j][1]);
                if (n >= 2) {
                    score = (n - 1) * n;
                } else {
                    score = n;
                }
                if (score > bestFollowUp) {
                    bestFollowUp = score;
                }
                j++;
            } while (j < 15);
            scores[i] += bestFollowUp;
        }
        i++;
    } while (i < 15);
}

// .text:0x0012E084 size:0xF8 mapped:0x8076D118
int bB_AI_compareCandidates(const void *a, const void *b) {
    const BB_AICandidate *x = a;
    const BB_AICandidate *y = b;
    MiniGameStruct *mg = &g_Minigame;
    s8 distX;
    s8 distY;
    int diff;

    if (x->score != y->score) {
        return y->score - x->score;
    }
    if (x->barrelsCleared != y->barrelsCleared) {
        diff = y->barrelsCleared - x->barrelsCleared;
        if (mg->bB_aiPrefersFewestBarrelsInd != 0) {
            diff = x->barrelsCleared - y->barrelsCleared;
        }
        return diff;
    }
    distX = __abs(2 - x->barrelIndex / 3);
    distY = __abs(2 - y->barrelIndex / 3);
    if (distX != distY) {
        return distX - distY;
    }
    distX = __abs(1 - x->barrelIndex % 3);
    distY = __abs(1 - y->barrelIndex % 3);
    return distX - distY;
}

// .text:0x0012DDCC size:0x2B8 mapped:0x8076CE60
void bB_AI_setSwingVariables(void) {
    MiniGameStruct *mg = &g_Minigame;
    u8 aiStrength = mg->playerSlots.aiStrength[mg->rosterID];
    s16 pitch;
    s8 row;
    s8 col;
    u32 prefersFewestBarrels;
    int direction;
    s8 i;
    s8 barrelsCleared[15];
    s16 scores[15];
    BB_AICandidate candidates[15];

    pitch = mg->bB_bombBarrelID_bOD_hrPitch;
    if (pitch >= 0) {
        row = pitch / 3;
        col = pitch % 3;
    } else {
        if (mg->bB_pitchesRemainingInTurn > 2 && lbl_3_data_217C4[aiStrength] != 0) {
            prefersFewestBarrels = RandomInt_Game(100) < lbl_3_data_217C8[aiStrength];
        } else {
            prefersFewestBarrels = FALSE;
        }

        if (prefersFewestBarrels) {
            bB_scoreEachBarrelChoice(barrelsCleared, scores, TRUE);
        } else {
            bB_scoreEachBarrelChoice(barrelsCleared, scores, FALSE);
        }

        i = 0;
        do {
            candidates[i].barrelIndex = i;
            candidates[i].barrelsCleared = barrelsCleared[i];
            candidates[i].score = scores[i];
            i++;
        } while (i < 15);

        if (prefersFewestBarrels) {
            mg->bB_aiPrefersFewestBarrelsInd = TRUE;
        } else {
            mg->bB_aiPrefersFewestBarrelsInd = FALSE;
        }
        fn_800246D4(bB_AI_compareCandidates, candidates, candidates, sizeof(BB_AICandidate), 15);

        row = candidates[0].barrelIndex / 3;
        col = candidates[0].barrelIndex % 3;
    }

    if (g_Batter.batterHand != BATTING_HAND_RIGHT) {
        row = 4 - row;
    }

    mg->bB_aiSwingFrame = swingSoundFrame[0][1] + lbl_3_data_217BC[row];

    switch (col) {
    case 0:
        mg->bB_aiVertButton = INPUT_BUTTON_UP;
        break;
    case 1:
    default:
        mg->bB_aiVertButton = 0;
        break;
    case 2:
        mg->bB_aiVertButton = INPUT_BUTTON_DOWN;
        break;
    }

    if (RandomInt_Game(100) < bBAI_chanceToMissTimeSwing[aiStrength]) {
        if (RandomInt_Game(2) != 0) {
            direction = 1;
        } else {
            direction = -1;
        }
        mg->bB_aiSwingFrame += direction * (RandomInt_Game(bBAI_framesMistimedBy[aiStrength]) + 1);
    }

    if (RandomInt_Game(100) < bBAI_chanceToOverrideVertAngleToMiddleRow[aiStrength]) {
        mg->bB_aiVertButton = 0;
    }
}

// .text:0x0012DD88 size:0x44 mapped:0x8076CE1C
BOOL bB_areAllBarrelsNeutral(void) {
    u32 i;

    i = 0;
    do {
        if (g_Minigame.barrels[i].barrelState != BB_BARREL_STATE_NEUTRAL) {
            break;
        }
        i++;
    } while (i < 15);
    return i >= 15;
}

// .text:0x0012DB80 size:0x208 mapped:0x8076CC14
void bB_AI(void) {
    MiniGameStruct *mg = &g_Minigame;
    s8 i;

    bB_clearAIControlled();

    i = 0;
    do {
        s8 character = g_Minigame.playerSlots.characterIndex[i];

        if (character >= 0 && character < 4 && i == g_Minigame.rosterID && g_Minigame.playerSlots.aiControlledInd[i]) {
            g_Minigame.isAIControlled[character] = 1;
            memset(&g_Minigame._1D7C[character], 0, sizeof(InputStruct));
            switch (g_Pitcher.pitcherActionState) {
            case PITCHER_ACTION_STATE_IN_AIR:
                if (mg->bB_aiSwingChosenInd != 0) {
                    if (g_Pitcher.framesUntilBallReachesBatterZ <= mg->bB_aiSwingFrame) {
                        switch (mg->bB_aiSwingStage) {
                        case 0:
                            g_Minigame._1D7C[character].newButtonInput |= INPUT_BUTTON_A;
                            g_Minigame._1D7C[character].buttonInput |= INPUT_BUTTON_A;
                            mg->bB_aiSwingStage++;
                            break;
                        case 1:
                            g_Minigame._1D7C[character].newButtonInput |= mg->bB_aiVertButton;
                            g_Minigame._1D7C[character].buttonInput |= mg->bB_aiVertButton | INPUT_BUTTON_A;
                            mg->bB_aiSwingStage++;
                            break;
                        case 2:
                            g_Minigame._1D7C[character].buttonInput |= INPUT_BUTTON_A;
                            if (g_Batter.framesSinceStartOfSwing > 0) {
                                g_Minigame._1D7C[character].buttonInput |= mg->bB_aiVertButton;
                            }
                            break;
                        }
                    }
                } else if (bB_areAllBarrelsNeutral()) {
                    bB_AI_setSwingVariables();
                    mg->bB_aiSwingChosenInd = TRUE;
                }
                break;
            }
        }
        i++;
    } while (i < 4);
}

// .text:0x0012DB54 size:0x2C mapped:0x8076CBE8
void bB_clearAIControlled(void) {
    s8 i;

    i = 0;
    do {
        g_Minigame.isAIControlled[i] = 0;
        i++;
    } while (i < 4);
}
