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
#include "game/ball/ball_physics.h"
#include "game/baserunning/runner.h"
#include "game/batting/batter.h"
#include "game/fielding/fielder.h"
#include "game/pitching/pitcher.h"
#include "game/animation/scene_effects.h"
#include "Unknown/File_0x8004abd8.h"
#include "Unknown/File_0x8003a538.h"
#include "Unknown/File_0x800204cc.h"

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
extern struct {
    f32 _00;
    f32 _04;
    f32 _08;
    f32 _0C;
} lbl_3_data_21438;


typedef struct {
    u8 _00[5];
    u8 _05;
    u8 _06;
    u8 _07[5];
} UnkSimulationStruct_31AC0;
extern UnkSimulationStruct_31AC0 g_UnkSimulation_31AC0;

// .text:0x00110634 size:0x3D0 mapped:0x8074F6C8
void bobOmbDerbyBatterAI(void) {
    return;
}

// .text:0x00110A04 size:0x34 mapped:0x8074FA98
void fn_3_110A04(void) {
    memset(&g_Minigame._1D7C, 0, 0x78);
}

// .text:0x00110A38 size:0x9C mapped:0x8074FACC
s32 fn_3_110A38(void) {
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

// .text:0x00110AD4 size:0x564 mapped:0x8074FB68
void BODScoring(void) {
    return;
}

// .text:0x00111038 size:0x198 mapped:0x807500CC
void unused_BODRelated(void) {
    return;
}

// .text:0x001111D0 size:0x80 mapped:0x80750264
void fn_3_1111D0(void) {
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

// .text:0x00111250 size:0x64 mapped:0x807502E4
void fn_3_111250(void) {
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    g_GameLogic.hudLoadingRelated = 1;
    fn_8003A540(0);

    if (g_Minigame.pointsTargetReachedInd == 1) {
        SetGameStatus(GAME_STATUS_TRANSITION);
    } else {
        SetGameStatus(GAME_STATUS_DEFAULT);
    }
}

// .text:0x001112B4 size:0x484 mapped:0x80750348
void bobOmbDerbyCalculatePoints(void) {
    return;
}

// .text:0x00111738 size:0x17C mapped:0x807507CC
void unusedBODFunction(void) {
    InMemRunnerType *runner = &g_Runners[0];
    s32 angle;
    int i;

    ballPhysica();

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

    if (g_Ball.bODQualifyingHitInd != 0 && g_Ball.deadBallReason == 1) {
        if (g_Ball.ballDistanceFromHome > lbl_3_data_21438._0C || g_Minigame.bODRelated3 != 0) {
            BODScoring();
            g_Minigame.bOD_hitFinishedInd = 1;
        }
    }

    for (i = 0; i < 10; i++) {
        if (g_Minigame.bODRelated5[i] != 0) {
            g_Minigame.bODRelated5[i]--;
            if (g_Minigame.bODRelated5[i] == 0) {
                setCharacterAnimations(g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.rosterID], 0);
            }
        }
    }

    if (g_Ball.deadBallReason == 2) {
        g_Minigame.bOD_hitFinishedInd = 1;
    }

    soundFxRelated();
    bobOmbDerbyCalculatePoints();
}

// .text:0x001118B4 size:0x1D4 mapped:0x80750948
void bOD_bB_Pitcher_waitingForPitch(void) {
    int pitchTiming = lbl_3_data_21448[3];
    u8 starPitch = 1;

    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER) {
        pitchTiming = lbl_3_data_217A4[6];
    }
    if (g_Minigame.GameMode_MiniGame != MINI_GAME_ID_BARREL_BATTER) {
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
                g_Minigame.bOD_KingBombInd = 1;
                speedLevel = RandomIndexFromWeights(&lbl_3_data_213A4[g_Minigame.barrelBatter_BODPitchSelectionType * 5], 5);
                g_Minigame.minigamePitchSpeedAdjustment = minigamePitchSpeeds_base[speedLevel] + rand() % 7 - 3;
            } else {
                g_Pitcher.starPitchInd = 1;
                g_Pitcher.starPitchType = 1;
            }
        }

        pitcherAITransitionFromPrePitchToWindup(2);
    }
}

// .text:0x00111A88 size:0x3C mapped:0x80750B1C
void fn_3_111A88(void) {
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    g_GameLogic.hudLoadingRelated = 1;
    SetGameStatus(GAME_STATUS_TRANSITION);
}

// .text:0x00111AC4 size:0x198 mapped:0x80750B58
void fn_3_111AC4(void) {
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
            g_GameLogic.pre_PostMiniGameInd = 1;
            g_GameLogic.minigameLastTurnSuccessInd = 1;
            g_GameLogic.hudLoadingRelated = 1;
            SetGameStatus(GAME_STATUS_TRANSITION);
        }
    }
}

// .text:0x00111C5C size:0x324 mapped:0x80750CF0
void fn_3_111C5C(void) {
    return;
}

// .text:0x00111F80 size:0xF0 mapped:0x80751014
void fn_3_111F80(void) {
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

// .text:0x00112070 size:0x70 mapped:0x80751104
void fn_3_112070(void) {
    fn_3_DE4FC();
    SetGameStatus(GAME_STATUS_MVP_END_GAME);
    g_Minigame._18A6 = rand() % 30 + 15;
    bobOmbDerbyPitching();
    minigamesSetSomePointers();
    minigamesGXStuff();
    minigamesSetSomePointers2();
}

// .text:0x001120E0 size:0x48 mapped:0x80751174
void fn_3_1120E0(void) {
    if (g_Scores.Inning >= g_Scores.inningLimit) {
        SetGameStatus(GAME_STATUS_TRANSITION_MINIGAME_POSTGAME);
    } else {
        SetGameStatus(GAME_STATUS_TRANSITION_TO_MINIGAME_START);
    }
}

// .text:0x00112128 size:0x7C mapped:0x807511BC
void fn_3_112128(void) {
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

// .text:0x001121A4 size:0x8C mapped:0x80751238
void fn_3_1121A4(void) {
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

// .text:0x00112230 size:0x220 mapped:0x807512C4
void bobOmbDerbyPitchTransition(void) {
    fn_3_1121A4();

    g_Minigame.turnOverStatus = 0;
    g_Minigame.bODRelated2 = 0;
    g_Minigame.bODRelated3 = 0;
    g_Minigame.bODControllerInputAllowedInd = 1;
    g_Minigame.bOD_KingBombInd = 0;
    g_Minigame.bOD_hitFinishedInd = 0;

    {
        int i;
        for (i = 0; i < 10; i++) {
            g_Minigame.bODRelated5[i] = 0;
        }
    }

    if (g_GameLogic.pre_PostMiniGameInd != 0) {
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        g_GameLogic.hudElementLoadingInd = 1;
    } else {
        g_GameLogic.minigameLastTurnSuccessInd = 0;
    }
    g_FieldingLogic.hasProcessedFoulBall = 0;
    g_Ball.totalFramesAtPlay = 0;
    g_Pitcher.windupCountdownUntilBallReleased = lbl_3_data_21448[4];
    g_GameLogic.pre_PostMiniGameInd = 0;

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

// .text:0x00112450 size:0x108 mapped:0x807514E4
void fn_3_112450(void) {
    switch (g_GameLogic._125) {
    case TRANSITION_CALCULATION_TYPE_0:
        g_GameLogic.pre_PostMiniGameInd = 1;
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

// .text:0x00112558 size:0x78 mapped:0x807515EC
void fn_3_112558(void) {
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

// .text:0x001125D0 size:0x40 mapped:0x80751664
void fn_3_1125D0(void) {
    sndFXStartEx(0x1bd, lbl_800EFBA4[6], 0x3f, 0);
    SetGameStatus(GAME_STATUS_TRANSITION_TO_MINIGAME_START);
}

// .text:0x00112610 size:0x2D8 mapped:0x807516A4
void bOD_LoadGame(void) {
    return;
}

// .text:0x001128E8 size:0x4 mapped:0x8075197C
void fn_3_1128E8(void) {
    return;
}

// .text:0x001128EC size:0x2EC mapped:0x80751980
void fn_3_1128EC(void) {
    return;
}

// .text:0x00112BD8 size:0x7C0 mapped:0x80751C6C
void bobOmbDerbySimulation(void) {
    return;
}

