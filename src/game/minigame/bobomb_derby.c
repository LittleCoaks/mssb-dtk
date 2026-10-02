#define SQRT2_LINKAGE static
#include "game/minigame/bobomb_derby.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "Dolphin/stl.h"
#include "stl/math.h"
#include "game/minigame/toy_field.h"
#include "game/minigame/rep_3880.h"
#include "Unknown/File_0x80034220.h"
#include "Unknown/File_0x8003452c.h"
#include "Unknown/File_0x800348c8.h"
#include "Dolphin/rand.h"
#include "musyx/musyx.h"
#include "game/sound/m_sound.h"
#include "game/math/game_math.h"
#include "game/match_setup/roster_init.h"
#include "game/match_setup/match_loading.h"
#include "game/ball/ball_physics.h"
#include "game/baserunning/runner.h"
#include "game/batting/batter.h"
#include "game/fielding/fielder.h"
#include "game/pitching/pitcher.h"
#include "game/animation/scene_effects.h"
#include "Unknown/File_0x8004abd8.h"
#include "Unknown/File_0x8003a538.h"
#include "Unknown/File_0x800204cc.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x80052734.h"
#include "Dolphin/mtx.h"

extern void SetGameStatus(GAME_STATUS status);
extern u8 lbl_800EFBA4[0x10];
extern void fn_3_10AD48(void);
extern void fn_3_10F550(int a, int b);
extern u8 animRelated[0x124];
extern u8 lbl_3_common_bss_32220[0x10];
extern s16 lbl_3_data_18C48[10];
extern u8 lbl_8037169C[0x1C];
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern BOOL checkForButtonPressToSkip(int a, int b);
extern u8 highLevelSimulationFlag[3];
extern u8 us80893314[8];
extern void ballPhysica(void);
extern s16 lbl_3_data_21448[10];
extern s16 lbl_3_data_217A4[12];
extern u8 lbl_3_data_213A4[0x30];
extern u8 minigamePitchSpeeds_base[8];
extern u8 lbl_3_data_213DC[8];
extern u8 soloBODPitchSelectionType[8];
extern s16 lbl_3_data_213EC[10];
extern s16 lbl_3_common_bss_37400[0x27];
extern void starMissionsMinigamesSpecialAction(int missionType, int points, int barrelsHit);
extern s16 bOD_challenge_nPitches_Points[4][2];
extern u8 lbl_3_data_2127C[8][5];
extern u8 lbl_3_data_213E4[8];
/* MWCC lays .bss out in reverse declaration order: B698 (never referenced) comes
 * first in the section, then the firework toggle at B699. */
static u8 lbl_3_bss_B699;
static u8 lbl_3_bss_B698;
extern void fn_8003414C(Mtx m);
extern BOOL checkForPauses(void);
extern int RandomIndexFromIntWeights(int *weights, int count);
extern u8 lbl_3_data_21488[8][3];
extern s8 lbl_3_data_214A0[4][6];
extern s8 lbl_3_data_214B8[4][3];
extern s8 lbl_3_data_214C4[4][3];
extern s8 lbl_3_data_214D0[4][3];
extern s8 lbl_3_data_214DC[4][3];
extern s8 lbl_3_data_214E8[4][3];
extern s8 lbl_3_data_214F4[4][3];
extern u8 lbl_3_data_213E0[4];
extern s16 calculateAngleFromCoordinates(f32 x, f32 z);
extern struct {
    f32 _00;
    f32 _04;
    f32 _08;
    f32 _0C;
} lbl_3_data_21438;

/* Never called. The original unit carries this unreferenced vector in .rodata
 * right after repHeaderData, ahead of the float literal pool; an uncalled
 * inline function's local static reproduces that placement. */
inline const Vec *getLbl_3_rodata_3240(void) {
    static const Vec lbl_3_rodata_3240 = { 0.0f, -45.0f, 160.0f };
    return &lbl_3_rodata_3240;
}


typedef struct {
    u8 _00[5];
    u8 _05;
    u8 _06;
    u8 _07[5];
} UnkSimulationStruct_31AC0;
extern UnkSimulationStruct_31AC0 g_UnkSimulation_31AC0;

static inline void bOD_launchFireworks(Vec *pos, int count) {
    camera_803c639c_s *cam = fn_80052768_getCamera(0);
    maybeFireworks((int)pos, (int)&cam->eye, count, 1);
}

static inline void bOD_clearAIControlled(void) {
    s8 i;

    i = 0;
    do {
        g_Minigame.isAIControlled[i] = FALSE;
        i++;
    } while (i < 4);
}

static inline BOOL bOD_isCurrentRoster(s8 i) {
    return i == g_Minigame.rosterID;
}

static inline void bOD_AI(void) {
    s8 i;

    i = 0;
    do {
        g_Minigame.isAIControlled[i] = FALSE;
        i++;
    } while (i < 4);

    i = 0;
    do {
        s8 slot = g_Minigame.minigameControlStruct[0].characterIndex[i];

        if (slot >= 0 && slot < 4 && bOD_isCurrentRoster(i) &&
            g_Minigame.minigameControlStruct[0].battingHandedness[i] != 0) {
            g_Minigame.isAIControlled[slot] = TRUE;
            memset(&g_Minigame._1D7C[slot], 0, sizeof(InputStruct));

            switch (g_Pitcher.pitcherActionState) {
            case PITCHER_ACTION_STATE_WINDUP:
                if (*(u8 *)&g_Minigame.minigameAICountDownTillAction == 0) {
                    bOD_BatterAI();
                    *(u8 *)&g_Minigame.minigameAICountDownTillAction = 1;
                }
                if (g_Pitcher.windupCountdownUntilBallReleased <= g_Minigame.ai_wbChargePower_bbSwingFrame) {
                    g_Minigame._1D7C[slot].buttonInput |= INPUT_BUTTON_A;
                }
                break;
            case PITCHER_ACTION_STATE_IN_AIR:
                if (g_Ball.pitchHangtimeCounter < g_Pitcher.frameWhenUnhittable - *(s16 *)&g_Minigame.ai_wbThrowType_bbVertAngle) {
                    g_Minigame._1D7C[slot].buttonInput |= INPUT_BUTTON_A;
                }
                break;
            }
        }
        i++;
    } while (i < 4);
}

// .text:0x00112BD8 size:0x7C0 mapped:0x80751C6C
void bobOmbDerbySwitcher(void) {
    switch (g_GameLogic.gameStatus) {
    case GAME_STATUS_LOAD_GAME:
        bOD_LoadGame();
        break;
    case GAME_STATUS_TRANSITION_MINIGAME_TO_BATTING:
        bOD_TransitionToBatting();
        break;
    case GAME_STATUS_TRANSITION_TO_MINIGAME_START:
        bOD_StartRound();
        break;
    case GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY:
        bOD_PrepareNextBatter();
        break;
    case GAME_STATUS_DEFAULT:
        bOD_PrepareNextPitch();
        break;
    case GAME_STATUS_AT_BAT:
        bOD_AtBat();
        break;
    case GAME_STATUS_LIVE_BALL:
        bOD_LiveBall();
        break;
    case GAME_STATUS_TRANSITION:
        bOD_EndTurn();
        break;
    case GAME_STATUS_MINIGAME_NEW_ROUND:
        bOD_CheckRoundsLeft();
        break;
    case GAME_STATUS_INNING_TRANSITION:
        bOD_RoundIntro();
        break;
    case GAME_STATUS_TRANSITION_MINIGAME_POSTGAME:
        bOD_Postgame();
        break;
    }
}

// .text:0x001128EC size:0x2EC mapped:0x80751980
void bOD_AmbientFireworks(void) {
    camera_803c639c_s *cam = returnFloatFromModeIndex(0);

    if (g_Minigame.bOD_fireworksTimer <= 0) {
        Vec eye = cam->eye;
        Vec pos = cam->target;
        Vec jitter;
        Mtx invView;
        u8 count;

        PSVECSubtract(&pos, &eye, &pos);
        PSVECNormalize(&pos, &pos);
        PSVECScale(&pos, 200.0f, &pos);
        PSVECAdd(&eye, &pos, &pos);

        if (pos.y > 55.0f) {
            pos.y = 55.0f;
        }

        PSMTXInverse(cam->view, invView);

        jitter.x = (f32)((rand() % 10000) - 5000) / 250.0f;
        jitter.y = (f32)((rand() % 1000) - 500) / 100.0f;
        jitter.z = 0.0f;

        PSMTXMultVecSR(invView, &jitter, &jitter);
        PSVECAdd(&pos, &jitter, &pos);

        if (pos.y > -55.0f) {
            pos.y = -10.0f * ((f32)rand() / 32767.0f) + -55.0f;
        }

        if (lbl_3_bss_B699 != 0) {
            count = rand() % 5 + 8;
        } else {
            count = rand() % 4 + 4;
        }

        maybeFireworks((int)&pos, (int)&cam->eye, count, 0);
        lbl_3_bss_B699 = !lbl_3_bss_B699;

        g_Minigame.bOD_fireworksTimer = rand() % 60 + 60;
    } else {
        g_Minigame.bOD_fireworksTimer--;
    }

    fn_8003414C(cam->view);
}

// .text:0x001128E8 size:0x4 mapped:0x8075197C
void bOD_UpdateFieldObjects(void) {
    return;
}

// .text:0x00112610 size:0x2D8 mapped:0x807516A4
void bOD_LoadGame(void) {
    if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_0) {
        int i;

        initializeSomethingDuringTransition();
        g_GameLogic.secondaryGameMode = SECONDARY_GAME_MODE_BOBOMB_DERBY;
        g_Minigame._17C0 = 0;

        for (i = 0; i < 4; i++) {
            g_Minigame.miniGameCurrentPoints[i] = 0;
            g_Minigame.miniGameLatestPoints[i] = 0;
            g_Minigame.minigamePoints_current_Latest[i][0] = 0;
            g_Minigame.minigamePoints_current_Latest[i][1] = 0;
            g_Minigame.minigameControlStruct[1].aIStrength[i + 2] = -1;
            g_Minigame._18FC[i] = -1;
            g_Minigame._1900[i] = -1;
            g_Minigame.minigameControlStruct[1].battingHandedness[i + 2] = 1;
            g_Minigame.minigameFielderIndex[i] = -1;
            g_Minigame.bOD_HitPowerOfEachChar[i] = 0;
            g_Minigame.bODCharacterHRStreakTracker[i][0] = 0;
            g_Minigame.bODCharacterHRStreakTracker[i][1] = 0;
        }

        g_Scores.Inning = 0;
        g_Minigame.turnNumberWithinRound = 0;
        g_Minigame.pointsReqToWin_challenge = 0;
        g_Minigame._1A37 = 0;
        g_Minigame.minigamePlayerSelectedOrder = -1;
        g_Minigame.rosterID = -1;
        g_Minigame._17C0 = 0;
        g_Minigame.bOD_KingBombInd = FALSE;
        g_Minigame.bODAngleIndexBasedOnHitPower = 0;
        g_Minigame.bOD_fireworkBurstCount = 0;
        g_Minigame.bB_bombBarrelHitInd_bOD_hrYaw = 0;
        g_Minigame.bB_bombBarrelID_bOD_hrPitch = 0;
        g_Minigame.bOD_fireworksTimer = 30;
        g_Minigame.bODControllerInputAllowedInd = FALSE;

        if (g_Minigame.multiPlayerInd == 0) {
            int diff = g_Minigame.soloMinigameDifficulty;

            g_Scores.inningLimit = 1;
            g_Minigame.bODRoundStartingNumPitches = (u8)bOD_challenge_nPitches_Points[diff][0];
            g_Minigame.pointsReqToWin_challenge = bOD_challenge_nPitches_Points[diff][1];
            g_Minigame.minigameControlStruct[0].aIStrength[0] = lbl_3_data_2127C[g_Minigame.GameMode_MiniGame][diff];
            g_Minigame.minigameControlStruct[0].aIStrength[1] = g_Minigame.minigameControlStruct[0].aIStrength[0];
            g_Minigame.minigameControlStruct[0].aIStrength[2] = g_Minigame.minigameControlStruct[0].aIStrength[0];
            g_Minigame.minigameControlStruct[0].aIStrength[3] = g_Minigame.minigameControlStruct[0].aIStrength[0];
        } else {
            if (g_Minigame._1A3C != 0) {
                g_Minigame.minigameControlStruct[0].aIStrength[0] = lbl_3_data_2127C[7][0];
                g_Minigame.minigameControlStruct[0].aIStrength[1] = lbl_3_data_2127C[7][0];
                g_Minigame.minigameControlStruct[0].aIStrength[2] = lbl_3_data_2127C[7][0];
                g_Minigame.minigameControlStruct[0].aIStrength[3] = lbl_3_data_2127C[7][0];
            }
            g_Scores.inningLimit = lbl_3_data_213E4[g_Minigame.miniGameNumberOfParticipants * 2 - 4];
            g_Minigame.bODRoundStartingNumPitches = lbl_3_data_213E4[g_Minigame.miniGameNumberOfParticipants * 2 - 3];
        }

        if (g_Minigame.multiPlayerInd == 0 && g_Minigame._1A3C == 0) {
            if (g_Minigame.multiPlayerInd == 0 && g_Minigame._1A3C == 0 &&
                g_Minigame.soloMinigameDifficulty == MINIGAME_DIFFICULTY_SOLO_NON_CHALLENGE) {
                g_Minigame._1AD8 = 9;
            } else {
                g_Minigame._1AD8 = RandomInt_Game_Range(4, 9);
            }
            g_Minigame._1AD9 = 1;
        } else if (g_Minigame._1A3C != 0) {
            g_Minigame._1AD8 = RandomInt_Game_Range(0, 2);
            g_Minigame._1AD9 = RandomInt_Game_Range(2, 3);
        } else {
            g_Minigame._1AD8 = 9;
            g_Minigame._1AD9 = 1;
        }

        g_GameLogic._125++;
    } else {
        SetGameStatus(GAME_STATUS_GAME_START_MOVIE);
    }
}

// .text:0x001125D0 size:0x40 mapped:0x80751664
void bOD_TransitionToBatting(void) {
    sndFXStartEx(0x1bd, lbl_800EFBA4[6], 0x3f, 0);
    SetGameStatus(GAME_STATUS_TRANSITION_TO_MINIGAME_START);
}

// .text:0x00112558 size:0x78 mapped:0x807515EC
void bOD_StartRound(void) {
    g_Scores.Inning++;
    g_Minigame.turnNumberWithinRound = 0;

    if (g_Minigame.multiPlayerInd == 0) {
        SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
        return;
    }

    if (g_Scores.Inning == 1) {
        fn_3_10AD48();
    }
    SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
    fn_3_10F550(4, 0);
}

// .text:0x00112450 size:0x108 mapped:0x807514E4
void bOD_PrepareNextBatter(void) {
    switch (g_GameLogic._125) {
    case TRANSITION_CALCULATION_TYPE_0:
        g_GameLogic.pre_PostMiniGameInd = TRUE;
        g_Minigame.rosterID = g_Minigame.minigameControlStruct[0].aIStrength[g_Minigame.turnNumberWithinRound + 4];
        g_Minigame.miniGameTurnCounter = 0;
        g_Minigame.pointsTargetReachedInd = 0;
        g_Minigame.bOD_HRStreak = 0;
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

// .text:0x00112230 size:0x220 mapped:0x807512C4
void bOD_PrepareNextPitch(void) {
    s32 i;

    bOD_ResetPlayState();

    g_Minigame.turnOverStatus = 0;
    g_Minigame.bODRelated2 = 0;
    g_Minigame.bOD_hrFireworksLaunchedInd = 0;
    g_Minigame.bODControllerInputAllowedInd = TRUE;
    g_Minigame.bOD_KingBombInd = FALSE;
    g_Minigame.bOD_hitFinishedInd = FALSE;

    for (i = 0; i < 10; i++) {
        g_Minigame.bOD_celebrationAnimTimers[i] = 0;
    }

    g_Ball.totalFramesAtPlay = 0;
    g_FieldingLogic.hasProcessedFoulBall = 0;
    g_Pitcher.windupCountdownUntilBallReleased = lbl_3_data_21448[4];

    if (g_GameLogic.pre_PostMiniGameInd != 0) {
        g_GameLogic.minigameLastTurnSuccessInd = TRUE;
        g_GameLogic.hudElementLoadingInd = TRUE;
    } else {
        g_GameLogic.minigameLastTurnSuccessInd = FALSE;
    }
    g_GameLogic.pre_PostMiniGameInd = FALSE;

    if (g_Minigame.miniGameNumberOfParticipants > 1) {
        g_Minigame.barrelBatter_BODPitchSelectionType = lbl_3_data_213DC[g_Scores.Inning - 1];
    } else if (g_Minigame.soloMinigameDifficulty == MINIGAME_DIFFICULTY_SOLO_NON_CHALLENGE) {
        int speedType = g_Minigame.miniGameTurnCounter / 5;
        if (speedType > 4) {
            speedType = 4;
        }
        g_Minigame.barrelBatter_BODPitchSelectionType = speedType;
    } else if (g_Minigame.miniGameTurnCounter < 5) {
        g_Minigame.barrelBatter_BODPitchSelectionType = soloBODPitchSelectionType[g_Minigame.soloMinigameDifficulty * 2];
    } else {
        g_Minigame.barrelBatter_BODPitchSelectionType = soloBODPitchSelectionType[g_Minigame.soloMinigameDifficulty * 2 + 1];
    }

    minigamesSetSomePointers();
    minigamesGXStuff();
    minigamesSetSomePointers2();
    newAtBatPlaySound();
    changeScene(1, 6);
    SetGameStatus(GAME_STATUS_AT_BAT);
}

// .text:0x001121A4 size:0x8C mapped:0x80751238
void bOD_ResetPlayState(void) {
    setInMemBatterConstants(g_Minigame.rosterID);
    setDefaultInMemBall();
    setDefaultInMemPitcher();
    setDefaultInMemBatter();
    setDefaultInMemRunner();
    setDefaultInMemFielder();
    memset(&g_Minigame._1D7C, 0, 0x78);
    pauseAnimations();
    Set_803cb848(1);

    g_FieldingLogic.playOverCounter = 0;
    g_UnkSimulation_31AC0._05 = 0;
    g_UnkSimulation_31AC0._06 = 4;
}

// .text:0x00112128 size:0x7C mapped:0x807511BC
void bOD_EndTurn(void) {
    g_Minigame.turnNumberWithinRound++;

    if (g_Minigame.multiPlayerInd == 0) {
        SetGameStatus(GAME_STATUS_TRANSITION_MINIGAME_POSTGAME);
    } else if (g_Minigame.turnNumberWithinRound >= g_Minigame.miniGameNumberOfParticipants) {
        SetGameStatus(GAME_STATUS_MINIGAME_NEW_ROUND);
    } else {
        SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
    }

    animRelated[0xB7] = 1;
}

// .text:0x001120E0 size:0x48 mapped:0x80751174
void bOD_CheckRoundsLeft(void) {
    if (g_Scores.Inning >= g_Scores.inningLimit) {
        SetGameStatus(GAME_STATUS_TRANSITION_MINIGAME_POSTGAME);
    } else {
        SetGameStatus(GAME_STATUS_TRANSITION_TO_MINIGAME_START);
    }
}

// .text:0x00112070 size:0x70 mapped:0x80751104
void bOD_Postgame(void) {
    minigameCalculateRankings();
    SetGameStatus(GAME_STATUS_MVP_END_GAME);
    g_Minigame.bOD_fireworksTimer = rand() % 30 + 15;
    bobOmbDerbyPitching();
    minigamesSetSomePointers();
    minigamesGXStuff();
    minigamesSetSomePointers2();
}

// .text:0x00111F80 size:0xF0 mapped:0x80751014
void bOD_RoundIntro(void) {
    switch (g_GameLogic._125) {
    case TRANSITION_CALCULATION_TYPE_0:
        changeScene(1, 6);
        g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_1;
        break;
    case TRANSITION_CALCULATION_TYPE_1:
        if (g_GameLogic.FrameCountOfCurrentPitch >= lbl_3_data_18C48[2] ||
            (g_GameLogic.FrameCountOfCurrentPitch >= lbl_3_data_18C48[1] &&
             checkForButtonPressToSkip(1, INPUT_BUTTON_START | INPUT_BUTTON_A))) {
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

// .text:0x00111C5C size:0x324 mapped:0x80750CF0
void bOD_AtBat(void) {
    if (g_Minigame.turnOverStatus == 0) {
        if (checkForPauses() != 0) {
            return;
        }

        atBat_Pitcher();
        bOD_AI();
        atBat_batter();

        bOD_clearAIControlled();

        miniGameFielding();
        running_MainFunction();
    }

    bOD_AtBatOutcome();
}

// .text:0x00111AC4 size:0x198 mapped:0x80750B58
void bOD_AtBatOutcome(void) {
    if (g_Minigame.turnOverStatus == 0) {
        if (g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_NO_CONTACT) {
            if (g_Minigame.miniGameTurnCounter >= g_Minigame.bODRoundStartingNumPitches) {
                g_Minigame.turnOverStatus = 1;
                g_Minigame.pointsTargetReachedInd = 1;
            }
            g_Minigame.bODCharacterHRStreakTracker[g_Minigame.rosterID][0] = 0;
            bobOmbDerbyPitching();
        }
    } else {
        if (g_Minigame.turnOverStatus == 1) {
            g_Minigame.turnOverStatus = 2;
            g_GameLogic.CountdownUntilFade = lbl_3_data_21448[0];
        }
        g_GameLogic.CountdownUntilFade--;

        if (g_Minigame.pointsTargetReachedInd != 0 &&
            (g_Minigame.multiPlayerInd == 0 ||
             (g_Minigame.multiPlayerInd != 0 &&
              g_Minigame.turnNumberWithinRound + 1 >= g_Minigame.miniGameNumberOfParticipants &&
              g_Scores.Inning >= g_Scores.inningLimit)) &&
            g_Minigame._1A37 == 0 && g_GameLogic.CountdownUntilFade == 0x43) {
            sndFXStartEx(0x1BE, lbl_800EFBA4[7], 0x3F, 0);
        }

        if (g_GameLogic.CountdownUntilFade == 7) {
            changeScene(3, 6);
        }

        if (g_GameLogic.CountdownUntilFade <= 0) {
            bOD_FinishTurn();
        }
    }
}

// .text:0x00111A88 size:0x3C mapped:0x80750B1C
void bOD_FinishTurn(void) {
    g_GameLogic.pre_PostMiniGameInd = TRUE;
    g_GameLogic.minigameLastTurnSuccessInd = TRUE;
    g_GameLogic.hudLoadingRelated = TRUE;
    SetGameStatus(GAME_STATUS_TRANSITION);
}

// .text:0x001118B4 size:0x1D4 mapped:0x80750948
void bOD_bB_Pitcher_waitingForPitch(void) {
    int pitchTiming = lbl_3_data_21448[3];
    BOOL isBarrelBatter = g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER;
    u8 starPitch = TRUE;

    if (isBarrelBatter) {
        pitchTiming = lbl_3_data_217A4[6];
    }
    if (!isBarrelBatter) {
        starPitch = g_Minigame._1DF4;
    }

    if (g_Pitcher.currentStateFrameCounter > pitchTiming && starPitch) {
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER) {
            g_Minigame.minigamePitchSpeedAdjustment = lbl_3_data_217A4[9];
        } else {
            BARREL_BATTER_PITCH_NUM pitchType = g_Minigame.bODPitchType;
            int speedLevel;

            if (pitchType < BARREL_BATTER_PITCH_NUM_KING) {
                if (pitchType < BARREL_BATTER_PITCH_NUM_STAR) {
                    speedLevel = pitchType * 2 + RandomIndexFromWeights(
                        &lbl_3_data_213A4[g_Minigame.barrelBatter_BODPitchSelectionType * 5] + pitchType * 2, 2);
                } else {
                    speedLevel = 4;
                }
                g_Minigame.minigamePitchSpeedAdjustment = minigamePitchSpeeds_base[speedLevel] + rand() % 7 - 3;
            } else if (pitchType == BARREL_BATTER_PITCH_NUM_KING) {
                g_Minigame.bOD_KingBombInd = TRUE;
                speedLevel = RandomIndexFromWeights(&lbl_3_data_213A4[g_Minigame.barrelBatter_BODPitchSelectionType * 5], 5);
                g_Minigame.minigamePitchSpeedAdjustment = minigamePitchSpeeds_base[speedLevel] + rand() % 7 - 3;
            } else {
                g_Pitcher.starPitchInd = TRUE;
                g_Pitcher.starPitchType = 1;
            }
        }

        pitcherAITransitionFromPrePitchToWindup(2);
    }
}

// .text:0x00111738 size:0x17C mapped:0x807507CC
void bOD_LiveBall(void) {
    int i;

    ballPhysica();
    bOD_SetRunnerAngleFromHit();

    if (g_Ball.bODQualifyingHitInd != 0 && g_Ball.deadBallReason == DEAD_BALL_REASON_HOME_RUN) {
        if (g_Ball.ballDistanceFromHome > lbl_3_data_21438._0C || g_Minigame.bOD_hrFireworksLaunchedInd != 0) {
            bOD_HomeRunFireworks();
            g_Minigame.bOD_hitFinishedInd = TRUE;
        }
    }

    for (i = 0; i < 10; i++) {
        if (g_Minigame.bOD_celebrationAnimTimers[i] != 0) {
            g_Minigame.bOD_celebrationAnimTimers[i]--;
            if (g_Minigame.bOD_celebrationAnimTimers[i] == 0) {
                setCharacterAnimations(g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.rosterID], 0);
            }
        }
    }

    if (g_Ball.deadBallReason == DEAD_BALL_REASON_FOUL_BALL) {
        g_Minigame.bOD_hitFinishedInd = TRUE;
    }

    soundFxRelated();
    bOD_LiveBallOutcome();
}

// .text:0x001112B4 size:0x484 mapped:0x80750348
void bOD_LiveBallOutcome(void) {
    if (g_Minigame.turnOverStatus == 0) {
        if (g_Ball.framesOnGroundUntilPickedUp != 0) {
            g_GameLogic.CountdownUntilFade = lbl_3_data_21448[1];
            g_Minigame.turnOverStatus = 1;
            g_Minigame.bODCharacterHRStreakTracker[g_Minigame.rosterID][0] = 0;
        } else if (g_Ball.deadBallReason != DEAD_BALL_REASON_NONE) {
            if (g_Ball.deadBallReason == DEAD_BALL_REASON_HOME_RUN) {
                g_GameLogic.CountdownUntilFade = lbl_3_data_21448[2];
                g_Minigame.bOD_HRStreak++;
                bOD_ScoreHomeRun();
            } else {
                g_GameLogic.CountdownUntilFade = lbl_3_data_21448[2];
                g_Minigame.bODCharacterHRStreakTracker[g_Minigame.rosterID][0] = 0;
            }
            g_Minigame.turnOverStatus = 1;
        }
    } else {
        if (g_Minigame.turnOverStatus == 1) {
            g_Minigame.turnOverStatus = 2;

            if (g_Minigame.multiPlayerInd == 0 &&
                g_Minigame.soloMinigameDifficulty <= MINIGAME_DIFFICULTY_MULTIPLAYER_CHALLENGE_HARD &&
                g_Minigame.miniGameCurrentPoints[g_Minigame.rosterID] >= g_Minigame.pointsReqToWin_challenge) {
                g_Minigame.pointsTargetReachedInd = 1;
                g_Minigame._1A37 = 1;
                g_Minigame.challenge_minigame_haven_tWonYetIndicator = 0;
                fn_3_10F550(1, lbl_3_data_21448[9]);
            } else if (g_Minigame.miniGameTurnCounter >= g_Minigame.bODRoundStartingNumPitches) {
                if (g_Minigame.multiPlayerInd == 0 &&
                    g_Minigame.soloMinigameDifficulty == MINIGAME_DIFFICULTY_SOLO_NON_CHALLENGE &&
                    g_Ball.deadBallReason == DEAD_BALL_REASON_HOME_RUN &&
                    g_Minigame.miniGameTurnCounter < 0x14) {
                    if (g_Minigame.bODCharacterHRStreakTracker[g_Minigame.rosterID][0] < g_Minigame.miniGameTurnCounter) {
                        g_Minigame.pointsTargetReachedInd = 1;
                    }
                } else {
                    g_Minigame.pointsTargetReachedInd = 1;
                }
            }
        }

        if (g_Minigame.bODControllerInputAllowedInd != 0 && g_Minigame.bODRelated == 0) {
            g_GameLogic.CountdownUntilFade--;

            if (g_Minigame.pointsTargetReachedInd != 0 &&
                (g_Minigame.multiPlayerInd == 0 ||
                 (g_Minigame.multiPlayerInd != 0 &&
                  g_Minigame.turnNumberWithinRound + 1 >= g_Minigame.miniGameNumberOfParticipants &&
                  g_Scores.Inning >= g_Scores.inningLimit)) &&
                g_Minigame._1A37 == 0 && g_GameLogic.CountdownUntilFade == 0x43) {
                sndFXStartEx(0x1BE, lbl_800EFBA4[7], 0x3F, 0);
            }

            if (g_GameLogic.CountdownUntilFade == 7) {
                changeScene(3, 6);
            }

            if (g_GameLogic.CountdownUntilFade <= 0) {
                bOD_FinishPitch();
            }
        }
    }
}

// .text:0x00111250 size:0x64 mapped:0x807502E4
void bOD_FinishPitch(void) {
    g_GameLogic.pre_PostMiniGameInd = TRUE;
    g_GameLogic.minigameLastTurnSuccessInd = TRUE;
    g_GameLogic.hudLoadingRelated = TRUE;
    fn_8003A540(0);

    if (g_Minigame.pointsTargetReachedInd == 1) {
        SetGameStatus(GAME_STATUS_TRANSITION);
    } else {
        SetGameStatus(GAME_STATUS_DEFAULT);
    }
}

// .text:0x001111D0 size:0x80 mapped:0x80750264
void bOD_SetRunnerAngleFromHit(void) {
    InMemRunnerType *runner = &g_Runners[0];
    s32 angle;

    if (lbl_3_common_bss_32220[8] == 4) {
        angle = g_Ball.Hit_HorizontalAngle;

        if (angle < 0x200) {
            angle = 0x200;
        }
        if (angle > 0x600) {
            angle = 0x600;
        }

        runner->runningAngle = -shortAngleToRad(angle) - 1.5707964f;
    }
}

// .text:0x00111038 size:0x198 mapped:0x807500CC
void bOD_ScoreHomeRun(void) {
    s16 hitPower = g_Ball.Hit_HorizontalPower;
    u8 streak;
    f32 points;

    g_Minigame.bODCharacterHRStreakTracker[g_Minigame.rosterID][0]++;

    if (g_Minigame.bOD_HitPowerOfEachChar[g_Minigame.rosterID] < hitPower) {
        g_Minigame.bOD_HitPowerOfEachChar[g_Minigame.rosterID] = hitPower;
    }

    points = (f32)hitPower;

    streak = g_Minigame.bODCharacterHRStreakTracker[g_Minigame.rosterID][0];
    if (streak > 1) {
        points += (f32)(lbl_3_data_213EC[8] * streak);
    }

    if (g_Minigame.bOD_KingBombInd != 0) {
        points += (f32)lbl_3_data_213EC[7];
    }

    g_Minigame.miniGameLatestPoints[g_Minigame.rosterID] = (s16)points;
    g_Minigame.miniGameCurrentPoints[g_Minigame.rosterID] += (s16)points;

    if (!g_d_GameSettings.exhibitionMatchInd && g_Minigame.rosterID == lbl_3_common_bss_37400[0x20]) {
        starMissionsMinigamesSpecialAction(0, (int)points, g_Minigame.bOD_KingBombInd);
    }
}

// .text:0x00110AD4 size:0x564 mapped:0x8074FB68
void bOD_HomeRunFireworks(void) {
    Vec pos;

    if (g_Minigame.bOD_hrFireworksLaunchedInd == 0) {
        int i;

        for (i = 9; i > 0; i--) {
            g_Minigame.bODHistory[g_Minigame.rosterID][i] = g_Minigame.bODHistory[g_Minigame.rosterID][i - 1];
        }
        g_Minigame.bODHistory[g_Minigame.rosterID][0] = g_Minigame.bODAngleIndexBasedOnHitPower;

        pos.x = g_Ball.AtBat_Contact_BallPos.x;
        pos.y = -g_Ball.AtBat_Contact_BallPos.y;
        pos.z = g_Ball.AtBat_Contact_BallPos.z;
        g_Minigame.bB_bombBarrelHitInd_bOD_hrYaw = calculateAngleFromCoordinates(pos.x, pos.z);
        g_Minigame.bB_bombBarrelID_bOD_hrPitch = calculateAngleFromCoordinates(g_Ball.ballDistanceFromHome, -pos.y);

        if (g_Pitcher.starPitchInd != 0) {
            bOD_launchFireworks(&pos, RandomInt_Game_Range(0, 3));
        } else if (g_Minigame.bOD_KingBombInd != 0) {
            bOD_launchFireworks(&pos, 13);
        } else {
            bOD_launchFireworks(&pos, RandomInt_Game_Range(8, 12));
        }

        g_Minigame.bOD_hrFireworksLaunchedInd = 1;
        g_Minigame._1DF6[1] = 1;
        g_Minigame.bOD_fireworkBurstCount = 1;
        g_Minigame.bOD_fireworksTimer = RandomInt_Game_Range(lbl_3_data_213E0[0], lbl_3_data_213E0[1]);

        if (g_Pitcher.starPitchInd != 0) {
            g_Minigame.bODControllerInputAllowedInd = FALSE;
        } else if (g_Minigame.bODCharacterHRStreakTracker[g_Minigame.rosterID][0] <= 1 || g_Minigame.bOD_KingBombInd != 0) {
            g_Minigame.bODControllerInputAllowedInd = TRUE;
            g_Minigame._1DF6[2] = 1;
        } else {
            g_Minigame.bODControllerInputAllowedInd = FALSE;
        }

        bobOmbDerbyPitching();

        for (i = 0; i < 10; i++) {
            if (g_Minigame.bOD_celebrationAnimTimers[i] == 0) {
                g_Minigame.bOD_celebrationAnimTimers[i] = lbl_3_data_21448[8];
                return;
            }
        }
    } else if (g_Minigame.bODControllerInputAllowedInd == 0) {
        g_Minigame.bOD_fireworksTimer--;

        if (g_Minigame.bOD_fireworksTimer <= 0) {
            int yawAngle = rand() % lbl_3_data_21448[5];
            int pitchAngle;
            f32 px;
            int i;

            if (rand() & 1) {
                yawAngle = -yawAngle;
            }
            yawAngle += g_Minigame.bB_bombBarrelHitInd_bOD_hrYaw;

            pitchAngle = rand() % lbl_3_data_21448[6];
            if (rand() & 1) {
                pitchAngle = -pitchAngle;
            }
            pitchAngle += g_Minigame.bB_bombBarrelID_bOD_hrPitch;

            getComponentsFromSAng(yawAngle, &pos.x, &pos.z);
            getComponentsFromSAng(pitchAngle, &px, &pos.y);
            pos.x *= lbl_3_data_21438._0C;
            pos.z *= lbl_3_data_21438._0C;
            pos.y /= px;
            pos.y *= -lbl_3_data_21438._0C;

            if (g_Pitcher.starPitchInd != 0) {
                bOD_launchFireworks(&pos, RandomInt_Game_Range(0, 3));
            } else if (g_Minigame.bOD_fireworkBurstCount & 1) {
                bOD_launchFireworks(&pos, RandomInt_Game_Range(4, 7));
            } else {
                bOD_launchFireworks(&pos, RandomInt_Game_Range(8, 12));
            }

            g_Minigame.bOD_fireworksTimer = RandomInt_Game_Range(lbl_3_data_213E0[2], lbl_3_data_213E0[3]);
            g_Minigame.bOD_fireworkBurstCount++;

            if (g_Pitcher.starPitchInd != 0) {
                if (g_Minigame.bOD_fireworkBurstCount >= 10) {
                    g_Minigame.bODControllerInputAllowedInd = TRUE;
                    g_Minigame._1DF6[2] = 1;
                }
            } else if (g_Minigame.bOD_fireworkBurstCount >= g_Minigame.bODCharacterHRStreakTracker[g_Minigame.rosterID][0] ||
                       g_Minigame.bOD_fireworkBurstCount >= lbl_3_data_21448[7]) {
                g_Minigame.bODControllerInputAllowedInd = TRUE;
                g_Minigame._1DF6[2] = 1;
            }

            for (i = 0; i < 10; i++) {
                if (g_Minigame.bOD_celebrationAnimTimers[i] == 0) {
                    g_Minigame.bOD_celebrationAnimTimers[i] = lbl_3_data_21448[8];
                    return;
                }
            }
        }
    }
}

// .text:0x00110A38 size:0x9C mapped:0x8074FACC
s32 bOD_EstimatePitchFrames(void) {
    if (g_Pitcher.starPitchInd != 0) {
        switch (g_Pitcher.starPitchType) {
        case 1:
            return 20;
        default:
            return 20;
        }
    }

    return (s32)(35.0f + -0.18867925f * ((f32)g_Minigame.minigamePitchSpeedAdjustment - 138.0f));
}

// .text:0x00110A04 size:0x34 mapped:0x8074FA98
void bOD_ClearInputs(void) {
    memset(&g_Minigame._1D7C, 0, 0x78);
}

// .text:0x00110634 size:0x3D0 mapped:0x8074F6C8
void bOD_BatterAI(void) {
    MiniGameStruct *mg = &g_Minigame;
    int aiDifficulty = mg->minigameControlStruct[0].aIStrength[mg->rosterID];
    int weights1[3];
    int weights2[3];
    s8 i;
    s16 chargeFrame;
    int pitchTypeIdx;

    i = 0;
    do {
        weights1[i] = lbl_3_data_21488[aiDifficulty][i];
        weights1[i] += g_Minigame.bODCharacterHRStreakTracker[g_Minigame.rosterID][0] * lbl_3_data_214B8[aiDifficulty][i];
        if (g_Minigame._1DF6[0] != 0) {
            weights1[i] += lbl_3_data_214E8[aiDifficulty][i];
        } else if (g_Minigame.bOD_KingBombInd != 0) {
            weights1[i] += lbl_3_data_214D0[aiDifficulty][i];
        }
        if (weights1[i] < 0) {
            weights1[i] = 0;
        }
        i++;
    } while (i < 3);

    i = 0;
    do {
        weights2[i] = lbl_3_data_21488[aiDifficulty][i];
        weights2[i] += g_Minigame.bODCharacterHRStreakTracker[g_Minigame.rosterID][0] * lbl_3_data_214C4[aiDifficulty][i];
        if (g_Minigame._1DF6[0] != 0) {
            weights2[i] += lbl_3_data_214F4[aiDifficulty][i];
        } else if (g_Minigame.bOD_KingBombInd != 0) {
            weights2[i] += lbl_3_data_214DC[aiDifficulty][i];
        }
        if (weights2[i] < 0) {
            weights2[i] = 0;
        }
        i++;
    } while (i < 3);

    chargeFrame = g_hitShorts.framesUntilChargeIsEnabled;
    switch (RandomIndexFromIntWeights(weights1, 3)) {
    case 0:
    default:
        chargeFrame += RandomInt_Game_Range(3, g_Batter.frameFullyCharged - 3);
        break;
    case 1:
        chargeFrame = RandomInt_Game_Range(3, g_Batter.frameChargeDownBegins - g_Batter.frameFullyCharged - 3) + g_Batter.frameFullyCharged + chargeFrame;
        break;
    case 2:
        chargeFrame = RandomInt_Game_Range(3, g_hitShorts.frameChargeDownEnds) + g_Batter.frameChargeDownBegins + chargeFrame;
        break;
    }

    pitchTypeIdx = RandomIndexFromIntWeights(weights2, 3);
    *(s16 *)&mg->ai_wbThrowType_bbVertAngle = swingSoundFrame[1][pitchTypeIdx] +
        RandomInt_Game_Range(lbl_3_data_214A0[aiDifficulty][pitchTypeIdx * 2],
                             lbl_3_data_214A0[aiDifficulty][pitchTypeIdx * 2 + 1]);

    mg->ai_wbChargePower_bbSwingFrame = chargeFrame - (bOD_EstimatePitchFrames() - *(s16 *)&mg->ai_wbThrowType_bbVertAngle);
    if (mg->ai_wbChargePower_bbSwingFrame < g_hitShorts.framesUntilChargeIsEnabled + 1) {
        mg->ai_wbChargePower_bbSwingFrame = g_hitShorts.framesUntilChargeIsEnabled + 1;
    }
}
