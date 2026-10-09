#define SQRT2_LINKAGE static
#include "game/match_setup/match_flow.h"
#include "mem.h"
#include "Dolphin/rand.h"
#include "game/match_setup/replay_inputs.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/animation/animation_dispatch.h"
#include "game/animation/scene_effects.h"
#include "game/ball/ball_physics.h"
#include "game/baserunning/play_result_tracking.h"
#include "game/baserunning/runner.h"
#include "game/batting/at_bat_results.h"
#include "game/batting/batter.h"
#include "game/camera/camera.h"
#include "game/fielding/fielder.h"
#include "game/match_setup/ai_defaults.h"
#include "game/match_setup/controller_input.h"
#include "game/match_setup/replay_state.h"
#include "game/match_setup/result_stats.h"
#include "game/match_setup/roster_init.h"
#include "game/match_setup/stat_tracking.h"
#include "game/match_setup/transition_init.h"
#include "game/match_setup/versus_screens.h"
#include "game/math/game_math.h"
#include "game/pitching/pitcher.h"
#include "game/pitching/pitcher_stamina.h"
#include "game/sound/m_sound.h"
#include "game/stadium/stadium_framework.h"
#include "musyx/musyx.h"
#include "Unknown/File_0x8004abd8.h"
#include "Unknown/File_0x8006c7c4.h"
#include "Unknown/File_0x8006c9d8.h"
#include "Unknown/File_0x8001e460.h"
#include "Unknown/File_0x8001f228.h"
#include "Unknown/File_0x800204cc.h"
#include "Unknown/File_0x80035838.h"
#include "Unknown/File_0x80062a50.h"
#include "Unknown/File_0x800a7568.h"
#include "Unknown/File_0x800b0a14.h"
#include "game/match_setup/pause_menu.h"

extern u32 FrameCountOfEntireGame[5];
extern u8 lbl_80366158[0x30];
extern UnkSimulationRelatedStruct g_UnkSimulation_31AC0;
extern u8 highLevelSimulationFlag[2];
extern u8 hugeAnimStruct[0x3154];
extern u8 animRelated[0x124];
extern void* lbl_3_common_bss_1323C[];
extern u8 lbl_3_common_bss_134C4[];
extern struct {
    u8 _00[0x40];
    s16 _40;
    s16 scoutCountdown;
    u8 _44[2];
    u8 scoutMissionID;
    u8 _47;
    u8 scoutFlag;
    u8 _49[5];
} lbl_3_common_bss_37400;
extern s16 challenge_baseCoinsAwarded[16];

extern void QueueTextToDisplay(int code, int arg1);
extern void initializeSomethingDuringTransition(void);
extern int fn_3_59BCC(int arg0);
extern ChallengeSituation lbl_3_data_5FF4[2][4][2];
extern s16 lbl_3_data_6074[4];
extern s8 challengeTransitionPortraitIDs[];
extern u8 lbl_8037169C[];
extern int fn_3_FD9FC(void);
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern int championshipScreenGraphics(void);
extern void recruitWholeTeamAfterMercy(void);
extern void matchTransitionFunction2(void);
extern int loadRunnerActors(void);
extern void challenge_setTransitionScreenCharacterPortrait(int, int);
extern MatchEndFile CommonUIFiles_matchEnd[];
extern int exitMenu(void);
extern void set803c5f77(void);
extern void fn_8004CC4C(int, int, int, int, int);
extern void fn_8004CA48(int, int, int, int);
extern int loadMVPMaybe(void);
extern u8 lbl_803C5F74[];
extern u8 lbl_800EFBA4[];
extern u8 challengeInnings[];
extern void betweenABSetPitcherBatter(void);
extern void someRosterMemoryManagement(void);
extern void setPausedTo0AndOtherStateVars(void);
extern void drawStadium(void);
extern void possiblyTransitionBlackScreen(void);
extern void initializeAIConstants(void);
extern void initializeAnimations(void);
extern void fn_3_AF5A4(void);
extern int loadBatterModelFromDisk(void);
extern int loadSomethingFromDiskAtBeginningOfAB1(void);
extern int loadSomethingFromDiskAtBeginningOfAB2(void);
extern u8 lbl_3_data_60F0;
extern void fn_3_90AB0(int);
extern int fn_3_90C14(int);
extern void fn_8002024C(void);
extern void handleDVDCancelAndARQRemoval(void);
extern int practice_checkForPause(void);
extern void match_checkForPause(void);
extern void transitionToPauseScreen(void);
extern void ballPhysica(void);
extern void fielderMainFunction(void);
extern void challengeModeRelated_checkScoutMissionSuccess(void);
extern void setScoutMissionRelatedToZero(void);
extern int loadFielderActors(int charID);
extern void unkPauseSimulationCheck(void);
extern BOOL checkForButtonPressToSkip(int a, int b);
extern void playOverSounds(int param);
extern void starMissionRelated2(void);
extern void cleanupCharacters(void);
extern void fn_3_90434(void);
extern void unregisterMatchHudObjects(void);
extern void toyFieldInit(void);
extern void minigames_init(void);
extern void clearScoutState(void);
extern void fn_3_1663AC(void);
extern void fn_3_59C2C(void);
extern void fn_3_59F40(void);
extern void fn_3_5A28C(void);
extern void fn_8003BF54(int, int, int, int, int, int, int, int, int);
extern void UpdateRandomInts(void);
extern void practiceSimulation(void);
extern void toyfieldSimulation(void);
extern void minigameSimulation(void);
extern void graphicsFunction_minigames(void);

// .text:0x0006011C size:0x64C mapped:0x8069F1B0
void baseballMatchSimulation(void) {
    s16 v;

    g_GameLogic.hudElementLoadingInd = 0;
    g_GameLogic.hudLoadingRelated = 0;
    if (g_Ball.totalFramesAtPlay < 0x7FFE) {
        g_Ball.totalFramesAtPlay++;
    } else {
        g_Ball.totalFramesAtPlay = 0x7FFF;
    }
    if (g_Strikes.outs >= 3) {
        g_FieldingLogic.framesSince3rdOutWasMade++;
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_DEMO && g_GameLogic.gameStatus != GAME_STATUS_GAME_START_MOVIE) {
        fn_3_5C418();
    }
    switch (g_GameLogic.gameStatus) {
    case GAME_STATUS_DEFAULT:
        newPitch();
        break;
    case GAME_STATUS_AT_BAT:
        atBatScreen();
        break;
    case GAME_STATUS_LIVE_BALL:
        freePracticeSomething();
        break;
    case GAME_STATUS_LOAD_GAME:
        fn_3_5FE88();
        break;
    case GAME_STATUS_GAME_START_MOVIE:
        exhibitionGameTransitionCalculations();
        break;
    case GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY:
        matchTransitionPrepareNextAB();
        break;
    case GAME_STATUS_TRANSITION:
        settingGameStatus();
        break;
    case GAME_STATUS_INNING_TRANSITION:
        inningChange();
        break;
    case GAME_STATUS_END_OF_GAME:
        endOfMatch();
        break;
    case GAME_STATUS_0xA:
        fn_3_5CD24();
        break;
    case GAME_STATUS_PAUSED:
        fn_3_AF5A4();
        break;
    case GAME_STATUS_HOMERUN_END:
        homeRunEnd();
        break;
    case GAME_STATUS_HOMERUN_LAP:
        homeRunTrot();
        break;
    case GAME_STATUS_BATTER_CELEBRATION:
        postReplayBatterCelebration();
        break;
    case GAME_STATUS_STAR_CHANCE_VS:
        starChanceVsScreenProcess();
        break;
    case GAME_STATUS_CHAMPIONSHIP:
        championshipScreen();
        break;
    case GAME_STATUS_0x18:
        fn_3_230D4();
        break;
    case GAME_STATUS_MVP_END_GAME:
        matchEndGameScreenFunction();
        break;
    }
    setAtBatResult();
    soundFxRelated();
    adjustBallSoundEffectBasedOnHeight();
    if (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT || g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL) {
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_DEMO || g_UnkSimulation_31AC0._08 == 0) {
            if (pauseControl._1D5 == 0) {
                v = *(s16*)&animRelated[0x9E];
                if (v >= 0) {
                    if (loadBatterModelFromDisk() != 0) {
                        *(s16*)&animRelated[0x9E] = -1;
                    }
                } else {
                    v = *(s16*)&animRelated[0xA0];
                    if (v >= 0) {
                        if (loadSomethingFromDiskAtBeginningOfAB1() != 0) {
                            *(s16*)&animRelated[0xA0] = -1;
                        }
                    } else {
                        v = *(s16*)&animRelated[0xA2];
                        if (v >= 0) {
                            if (loadSomethingFromDiskAtBeginningOfAB2() != 0) {
                                *(s16*)&animRelated[0xA2] = -1;
                            }
                        }
                    }
                }
            }
        }
    }
}

// .text:0x0005FF10 size:0x20C mapped:0x8069EFA4
void initializeGame(void) {
    s32 i;

    initRosterForMatch();
    g_GameLogic.currentBatterPerTeam[0] = 1;
    g_GameLogic.currentBatterPerTeam[1] = 1;
    g_GameLogic.TeamStars[0] = Static_Stats_Tables.startingChemStars[0];
    g_GameLogic.TeamStars[1] = Static_Stats_Tables.startingChemStars[1];
    if (inningSetting.starSkillsSetting == 0) {
        g_GameLogic.TeamStars[0] = 0;
        g_GameLogic.TeamStars[1] = 0;
    }
    g_GameLogic.IsStarChance = 0;
    g_GameLogic.freeFieldingPracticeInd = 0;
    g_GameLogic.gameOverInd = 0;
    g_GameLogic.scoutFlag_VsScreenInd = 0;
    g_GameLogic.playBatterWalkupAnimation = 0;
    g_Scores.winnerCd = -1;
    g_Scores._AE = 0;
    g_Scores.Inning = 1;
    g_Scores.halfInning = 0;
    g_Scores._C6 = 0;
    for (i = 0; i < 19; i++) {
        (&g_Scores.scores[0].total)[i] = 0;
        (&g_Scores.scores[1].total)[i] = 0;
        (&g_Scores.hits[0].total)[i] = 0;
        (&g_Scores.hits[1].total)[i] = 0;
    }
    g_Scores.stealSuccesses[0] = 0;
    g_Scores._B3[0] = -1;
    g_Scores._B5[0] = -1;
    g_Scores._B7[0] = -1;
    g_Scores._B9[0] = 0;
    g_Scores._AF[0] = g_GameLogic.battingOrderAndPositionMapping[0][0][0];
    g_Scores._BB[0] = 1;
    g_Scores._BD[0] = 1;
    g_Scores.stealSuccesses[1] = 0;
    g_Scores._B3[1] = -1;
    g_Scores._B5[1] = -1;
    g_Scores._B7[1] = -1;
    g_Scores._B9[1] = 0;
    g_Scores._AF[1] = g_GameLogic.battingOrderAndPositionMapping[1][0][0];
    g_Scores._BB[1] = 1;
    g_Scores._BD[1] = 1;
    SetGameStatus(GAME_STATUS_LOAD_GAME);
    setPitchingConstants();
    initializeInMemBatter();
    initBallAndGameStateOnLoad();
    initializeFielderConstants();
    fn_3_8A5A4();
    initializeAIConstants();
    initializeStats();
    initializeInningTrackers();
    initializeReplayVariables();
    initializeSounds();
    initializeAnimations();
    initializeCamera();
    initializeUnknown();
}

// .text:0x0005FE88 size:0x88 mapped:0x8069EF1C
void fn_3_5FE88(void) {
    switch (g_GameLogic._125) {
    case 0:
        insertGraphicDrawingFunction(possiblyTransitionBlackScreen, 2);
        g_GameLogic._125 = 1;
        break;
    case 1:
        insertGraphicDrawingFunction(drawStadium, 4);
        g_GameLogic._125 = 2;
        break;
    default:
        SetGameStatus(GAME_STATUS_GAME_START_MOVIE);
        break;
    }
}

// .text:0x0005F930 size:0x558 mapped:0x8069E9C4
void exhibitionGameTransitionCalculations(void) {
    s32 i;
    int charID;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_DEMO) {
        if (g_UnkSimulation_31AC0._08 == 0) {
            if (AtBat_ButtonInput1._02 & INPUT_BUTTON_START) {
                g_UnkSimulation_31AC0._08 = 1;
            }
        } else if ((int)((u8*)&lbl_803C6CF8)[0x715] == 1) {
            u32 state = g_GameLogic._125;

            if (state == 1) {
                hugeAnimStruct[0x3082] = 1;
            }
            if (state == 1 || state >= 8 || g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
                changeScene(3, 6);
                if (g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
                    g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                }
                if (lbl_8037169C[0x13] != 0) {
                    g_GameLogic.framesOfExitingToMenu = 1;
                }
                return;
            }
        }
    }
    switch (g_GameLogic._125) {
    case 0:
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            startChallengeModeMatch();
        }
        initNewInning();
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125 = 1;
        changeScene(0xD, 6);
        hugeAnimStruct[0x2D77] = 0;
        hugeAnimStruct[0x2D7B] = 0;
        hugeAnimStruct[0x2D7C] = 0;
        animRelated[0x9A] = 0;
        animRelated[0x9C] = 0;
        highLevelSimulationFlag[2] = 0;
        highLevelSimulationFlag[3] = 0;
        break;
    case 1:
        if (fn_3_59BCC(g_GameLogic.FrameCountOfCurrentAtBat_Copy) != 0) {
            g_GameLogic._125 = 2;
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            hugeAnimStruct[0x2D77] = 0;
            if (animRelated[0xA4] != 0) {
                fn_8002024C();
            }
        }
        break;
    case 2:
        if (loadPitcherActor() != 0) {
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_GameLogic._125 = 5;
        }
        break;
    case 5:
        for (i = 1; i < 10; i++) {
            if (g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][i][1] == 1) {
                charID = inMemRoster[g_GameLogic.teamFielding]
                                        [g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][i][0]]
                                            .stats.CharID;
            }
        }
        if (loadFielderActors(charID) != 0) {
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            hugeAnimStruct[0x3081] = 0;
            g_GameLogic._125 = 6;
        }
        break;
    case 6:
        if (loadRunnerActors() != 0) {
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_GameLogic._125 = 7;
        }
        break;
    case 7:
        if (someAnimationIndFunction() != 0) {
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_GameLogic._125 = 8;
        }
        break;
    case 8:
        if (g_GameLogic.FrameCountOfCurrentPitch >= 0xF0) {
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_DEMO ||
                g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_UNKNOWN_2) {
                g_GameLogic._125 = 9;
            } else if (checkForButtonPressToSkip(1, 0x1300)) {
                g_GameLogic._125 = 9;
            }
        }
        if (fn_3_FD9FC() != 0) {
            g_GameLogic._125 = 9;
        }
        break;
    case 9:
        changeScene(3, 6);
        if (lbl_8037169C[0x13] != 0) {
            g_GameLogic._125 = 10;
        }
        break;
    case 10:
        ((u8*)lbl_3_common_bss_1323C[0])[0x25C] = 1;
        fn_3_FBD70();
        SetGameStatus(GAME_STATUS_STAR_CHANCE_VS);
        break;
    }
    for (i = 0; i < 9; i++) {
    }
}

// .text:0x0005F7A8 size:0x188 mapped:0x8069E83C
void initNewInning(void) {
    inningImportanceAI();
    resetCount();
    resetInMemPitcher();
    resetInMemFielders();
    resetInMemRunners();
    someRosterMemoryManagement();
    setPausedTo0AndOtherStateVars();
    setInningEndingKIndTo0();
    resetGameControlVars_duringNewInning();
    setBatterContactConstants();
    initializeARunner();
    intializeRunnersDuringTransition();
    betweenABSetPitcherBatter();
    initializeSomethingDuringTransition2();
    g_Strikes.strikes = 0;
    g_Strikes.balls = 0;
    g_Strikes._1E = -1;
    g_Strikes.stateRelated = 0;
    g_GameLogic.frameCountdownAtBeginningOfAtBatLockout = 0x5A;
    g_GameLogic._13D = 0;
}

// .text:0x0005F720 size:0x88 mapped:0x8069E7B4
void practiceNewBatter(void) {
    setDefaultInMemBall();
    setDefaultInMemPitcher();
    setDefaultInMemBatter();
    setDefaultInMemRunner();
    setDefaultInMemFielder();
    setDefaultAIValues();
    Set_803cb848(1);
    setPitcherStatsToInMemPitcher(g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]);
    g_FieldingLogic.playOverCounter = 0;
    g_GameLogic.homeRunWordAnimationCompletedInd = 0;
    g_UnkSimulation_31AC0._05 = 0;
    g_UnkSimulation_31AC0._06 = 4;
}

// .text:0x0005F3FC size:0x324 mapped:0x8069E490
void matchTransitionPrepareNextAB(void) {
    switch (g_GameLogic._125) {
    case 0:
        animRelated[0x9A] = 0;
        g_GameLogic.scoutFlag_VsScreenInd = 0;
        g_GameLogic.playBatterWalkupAnimation = 1;
        resetBallValuesBetweenBatters();
        resetPitcherValuesBetweenBatters(0);
        setBatterContactConstants();
        initializeARunner();
        setDefaultInMemRunner();
        initializeMiniGameCharacters();
        betweenABSetPitcherBatter();
        intializeRunnersDuringTransition();
        initializeSomethingDuringTransition();
        initializeSomethingDuringTransition2();
        g_Strikes.strikes = 0;
        g_Strikes.balls = 0;
        g_Strikes._1E = -1;
        g_Strikes.stateRelated = 0;
        g_GameLogic.pre_PostMiniGameInd = 1;
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        g_GameLogic.frameCountdownAtBeginningOfAtBatLockout = 0x5A;
        g_GameLogic._131[2] = 0;
        g_GameLogic._131[3] = 0;
        if (g_Scores._C6 < 0xFE) {
            g_Scores._C6++;
        } else {
            g_Scores._C6 = 0xFF;
        }
        g_GameLogic._125++;
    case 1:
        if (loadRunnerActors() == 0) {
            break;
        }
        highLevelSimulationFlag[2] = 0;
        g_GameLogic._125++;
    case 2:
        if (someAnimationIndFunction() == 0) {
            break;
        }
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125++;
    case 3:
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_Practice.practiceLevel == 7) {
            if (g_GameLogic.FrameCountOfCurrentAtBat_Copy == 0) {
                fn_3_90AB0(g_Practice.someCharID2);
                sound_crowd_EffectsStruct._2C = 0;
                g_Practice.someCharID2 =
                    inMemRoster[g_GameLogic.teamBatting][g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam] - 1]
                        .stats.CharID;
            }
            if (fn_3_90C14(g_Practice.someCharID2) == 0) {
                break;
            }
        }
        g_GameLogic._125++;
    default:
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_DEMO && g_UnkSimulation_31AC0._08 != 0) {
            break;
        }
        if (g_GameLogic.freeFieldingPracticeInd != 0) {
            newPitch();
            break;
        }
        SetGameStatus(GAME_STATUS_STAR_CHANCE_VS);
        versusStarChanceSetPointers();
        g_GameLogic.IsStarChance = 0;
        animRelated[0xAC] = 0;
        if (inningSetting.starSkillsSetting != 0) {
            if (!g_d_GameSettings.exhibitionMatchInd) {
                if (lbl_3_common_bss_37400.scoutMissionID != 0) {
                    break;
                }
            }
            if (g_GameLogic.TeamStars[0] >= 5 && g_GameLogic.TeamStars[1] >= 5) {
                break;
            }
            if ((g_RunningLogic._02 & 0xFFF0) != 0) {
                break;
            }
            if (random_fn_3_9EE24(100) < lbl_3_data_60F0) {
                g_GameLogic.IsStarChance = 1;
                animRelated[0xAC] = 1;
            }
        }
        break;
    }
}

// .text:0x0005F154 size:0x2A8 mapped:0x8069E1E8
void newPitch(void) {
    int diff;

    setDefaultInMemBall();
    setDefaultInMemPitcher();
    setDefaultInMemBatter();
    setDefaultInMemRunner();
    setDefaultInMemFielder();
    setDefaultAIValues();
    Set_803cb848(1);
    setPitcherStatsToInMemPitcher(g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]);
    g_Scores._9C = 0;
    g_Scores._9E = g_Scores.scores[g_Scores.halfInning].byInning[g_Scores.Inning - 1];
    g_Scores._A2 = g_Scores._A0;
    diff = g_Scores.scores[0].total - g_Scores.scores[1].total;
    g_FieldingLogic.playOverCounter = 0;
    g_GameLogic.homeRunWordAnimationCompletedInd = 0;
    g_UnkSimulation_31AC0._05 = 0;
    g_UnkSimulation_31AC0._06 = 4;
    g_GameLogic._12F = 0;
    g_GameLogic.unused_always0 = 0;
    g_GameLogic.CountdownUntilFade = 999;
    g_GameLogic.PauseSimulationFrameCount = 0;
    g_GameLogic.playOver = 0;
    g_GameLogic.walkOffWinInd = 0;
    g_GameLogic.stadiumStarObtained = 0;
    g_Scores._A0 = g_Scores.scores[g_Scores.halfInning].total;
    g_Scores._C2 = 0;
    g_Scores._C4 = 0;
    g_Scores._C5 = 0;
    if (diff < -0x8000) {
        diff = -0x8000;
    }
    if (diff > 0x7FFF) {
        diff = 0x7FFF;
    }
    if (diff < 0) {
        diff = -diff;
    }
    g_Scores._A6 = diff;
    g_Strikes.storedOuts = g_Strikes.outs;
    g_Strikes.runnerIndexForEachOutThisPitch[0] = -1;
    g_Strikes.runnerIndexForEachOutThisPitch[1] = -1;
    g_Strikes.runnerIndexForEachOutThisPitch[2] = -1;
    g_Strikes.GameControls_StrikeBallBitVector = g_Strikes.balls + g_Strikes.strikes * 16;
    g_Strikes.howRunnerReachedBase = 0;
    g_Ball.totalFramesAtPlay = 0;
    g_FieldingLogic.playOverInd = 0;
    g_FieldingLogic.framesSincePlayEnded = 0;
    g_FieldingLogic.unused_always0__ = 0;
    g_FieldingLogic.hasProcessedFoulBall = 0;
    g_FieldingLogic.canEndPlayOnLooseBallInd = 0;
    g_FieldingLogic.always0__ = 0;
    g_FieldingLogic.framesSince3rdOutWasMade = 0;
    g_RunningLogic._13 = 0;
    pauseControl._1D5 = 0;
    g_Practice.homeRunWaitSkipped = 0;
    if (g_GameLogic.pre_PostMiniGameInd != 0) {
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        g_GameLogic.hudElementLoadingInd = 1;
        changeScene(1, 6);
    } else {
        g_GameLogic.minigameLastTurnSuccessInd = 0;
    }
    g_GameLogic.pre_PostMiniGameInd = 0;
    SetGameStatus(GAME_STATUS_AT_BAT);
    if (g_GameLogic.playOverInd != 0) {
        g_GameLogic.playOverInd--;
    }
    if (g_GameLogic.freeFieldingPracticeInd == 0 && g_GameLogic.EventTriggers_GameHasStarted == 0) {
        QueueTextToDisplay(0xC, 0);
        g_GameLogic.EventTriggers_GameHasStarted = 1;
    }
    setRunnerOnBaseIndicators();
    setDefaultPlayTrackingVariables1();
    setDefaultPlayTrackingVariables2();
    setDefaultPlayTrackingVariables3();
    newAtBatPlaySound();
    if (sound_crowd_EffectsStruct._2A != 0) {
        sound_crowd_EffectsStruct._2A = 2;
        sound_crowd_EffectsStruct._24 = 0x78;
    }
}

// .text:0x0005EFEC size:0x168 mapped:0x8069E080
void atBatScreen(void) {
    if (g_GameLogic.freeFieldingPracticeInd != 0) {
        if (practice_checkForPause() != 0) {
            return;
        }
        if (g_Practice.pauseMenuLoading != 0) {
            return;
        }
    } else {
        match_checkForPause();
        if (pauseControl._1D5 != 0) {
            transitionToPauseScreen();
            return;
        }
    }
    if (g_GameLogic.frameCountdownAtBeginningOfAtBatLockout != 0) {
        g_GameLogic.frameCountdownAtBeginningOfAtBatLockout--;
    }
    atBat_Pitcher();
    atBat_batter();
    atBat_Fielders();
    running_MainFunction();
    processScoreChanges(0);
    if (g_GameLogic.freeFieldingPracticeInd == 0) {
        if (g_Strikes.outs >= 3 || (g_Strikes.storedOuts == 2 && g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT)) {
            if (g_GameLogic.EventTriggers_EndOfGame == 0) {
                endOfGameCheck(0);
                if (g_GameLogic.EventTriggers_EndOfGame != 0) {
                    QueueTextToDisplay(0xD, 0);
                } else if (g_Scores._C3 == 0) {
                    QueueTextToDisplay(5, 0);
                    g_Scores._C3 = 1;
                }
            }
        }
    }
    if (g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_POST_HIT) {
        endBatterTransition();
    }
}

// .text:0x0005EE58 size:0x194 mapped:0x8069DEEC
void endBatterTransition(void) {
    if (g_Stats.replayInd != 0) {
        return;
    }
    lastPlayStats();
    postPlayTrackStats();
    g_GameLogic.playOverInd = 0;
    if (g_GameLogic.freeFieldingPracticeInd != 0) {
        transferInMemRunnerValuesToNextRunnerIndex();
        iterateBatter(g_GameLogic.homeTeamBattingInd_fieldingTeam);
    } else if (g_GameLogic.EventTriggers_EndOfGame != 0) {
        if (!g_d_GameSettings.exhibitionMatchInd) {
            if (g_GameLogic.homeTeamInd ^ (g_d_GameSettings.humanTeamNumber == g_Scores.winnerCd)) {
                challenge_checkRecruitment();
            }
        }
    } else if (g_Strikes.outs >= 3) {
        if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd < PICKOFF_STEAL_CODE_PICKOFF ||
            g_FieldingLogic.liveBallBcOfPickoffOrStealCd > 3 || g_Strikes.balls >= 4) {
            iterateBatter(g_GameLogic.homeTeamBattingInd_fieldingTeam);
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
            if (g_Practice.practiceLevel == 7 || g_Practice.practiceLevel == 6) {
                transferInMemRunnerValuesToNextRunnerIndex();
            }
        }
    } else {
        transferInMemRunnerValuesToNextRunnerIndex();
        iterateBatter(g_GameLogic.homeTeamBattingInd_fieldingTeam);
    }
    SetGameStatus(GAME_STATUS_TRANSITION);
    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_NONE && g_Stats.replayPending == 1) {
        g_Stats.replayPending = 2;
    }
    pauseAnimations();
    pauseStateOnStadiums();
}

// .text:0x0005EDD8 size:0x80 mapped:0x8069DE6C
void freePracticeSomething(void) {
    ballPhysica();
    fielderMainFunction();
    running_MainFunction();
    if (g_Ball.deadBallReason != DEAD_BALL_REASON_NONE) {
        handleDeadBall();
    }
    processScoreChanges(0);
    checkIfPlayOver();
    if (g_GameLogic.freeFieldingPracticeInd == 0) {
        midPlay_trackStats();
        if (g_Strikes.outs >= 3) {
            endOfGameCheck(0);
        }
    }
}

// .text:0x0005ED98 size:0x40 mapped:0x8069DE2C
void switchFromAtBatToLiveBall(void) {
    SetGameStatus(GAME_STATUS_LIVE_BALL);
    g_FieldingLogic.playOverCounter = 0;
    g_Pitcher.peachDaisyStarAnimationOn = 0;
}

// .text:0x0005E2C4 size:0xAD4 mapped:0x8069D358
void checkIfPlayOver(void) {
    int count = 0;
    int allRunnersDone = 1;
    s16 endFrame = 0x78;
    int i;
    int showReplay;

    if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd == PICKOFF_STEAL_CODE_NONE &&
        g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR && g_Ball.deadBallReason == DEAD_BALL_REASON_NONE) {
        g_FieldingLogic.playOverCounter = 0;
        return;
    }
    if (g_FieldingLogic.canEndPlayOnLooseBallInd != 0 && animRelated[0xB1] == 0) {
        if (g_Strikes.outs < 3 && g_RunningLogic._00 != 0) {
            g_FieldingLogic.playOverCounter = 0;
        }
        g_FieldingLogic.canEndPlayOnLooseBallInd = 0;
    }
    if (g_FieldingLogic.framesSincePlayEnded != 0) {
        if (g_FieldingLogic.framesSincePlayEnded < 0x7FFE) {
            g_FieldingLogic.framesSincePlayEnded++;
        } else {
            g_FieldingLogic.framesSincePlayEnded = 0x7FFF;
        }
        if (g_FieldingLogic.framesSincePlayEnded > 0x5A) {
            g_FieldingLogic.framesSincePlayEnded = 0;
        }
    }
    for (i = 0; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
            if (g_Runners[i].baseStandingOn < 0) {
                allRunnersDone = 0;
            } else if (g_Runners[i].runningDirectionCode == 1 && g_Runners[i].overRun1BStage == 0) {
                allRunnersDone = 0;
            } else if (g_Runners[i].baseStandingOn != g_Runners[i].currentBase) {
                allRunnersDone = 0;
            }
            if (g_Runners[i].tagUpInd == TAG_UP_TYPE_TAGGED) {
                allRunnersDone = 0;
            }
            if (g_Runners[i].forceOutCd == 1) {
                allRunnersDone = 0;
            }
            count++;
        }
    }
    if (g_Ball.deadBallReason == DEAD_BALL_REASON_HOME_RUN) {
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_Practice.practiceLevel != 6 &&
            g_Practice.practiceLevel != 7) {
            if (g_Practice.homeRunWaitSkipped == 0) {
                if (g_Controls[g_Practice.homeAway].newButtonInput & (INPUT_BUTTON_A | INPUT_BUTTON_START)) {
                    g_Practice.homeRunWaitSkipped = 1;
                }
                endFrame = 0x12C;
            } else {
                endFrame = 0x2D;
            }
        } else {
            endFrame = 0x78;
            if (g_GameLogic.homeRunWordAnimationCompletedInd == 0 && g_FieldingLogic.playOverCounter == 0x76) {
                g_GameLogic.homeRunWordAnimationCompletedInd = 1;
                uncalledRunnerUpdateRelated();
            }
        }
    } else if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FOUL && g_GameLogic.EventTriggers_EndOfGame == 0) {
        endFrame = 0x3C;
    } else if (g_GameLogic.EventTriggers_EndOfGame != 0 && g_Ball.deadBallReason != DEAD_BALL_REASON_HOME_RUN) {
        endFrame = 0xD2;
        if (g_Scores.Inning >= g_Scores.inningLimit && g_Scores.halfInning != 0) {
            QueueTextToDisplay(0xD, 0);
        }
    } else if (g_Strikes.outs >= 3) {
        endFrame = 0x78;
    } else if (count == 0 && g_Ball.deadBallReason != DEAD_BALL_REASON_HOME_RUN && g_Ball.ballInitialHitDoneInd != 0 &&
               g_Ball.ballState != 0) {
        endFrame = 0x78;
    } else if (g_Ball.deadBallReason != DEAD_BALL_REASON_NONE) {
        if (g_Ball.deadBallReason == 3 || g_Ball.deadBallReason == DEAD_BALL_REASON_BALL_DEAD) {
            endFrame = 0x78;
        } else {
            endFrame = 0x3C;
        }
    } else {
        if (g_GameLogic.playOver == 0 && g_Ball.ballState == BALL_STATE_LOOSE && g_GameLogic.walkOffWinInd == 0) {
            endFrame = 0x12C;
        }
        if (g_GameLogic.walkOffWinInd == 0) {
            if (g_Ball.ballState == BALL_STATE_HIT &&
                g_Runners[0].runnerOnFieldOrOutOrScored != RUNNER_STATUS_SCORED_DURING_PLAY) {
                g_FieldingLogic.playOverCounter = 0;
                return;
            }
            if (allRunnersDone == 0) {
                g_FieldingLogic.playOverCounter = 0;
                return;
            }
        }
    }
    if (g_FieldingLogic.playOverCounter < 0x7FFE) {
        g_FieldingLogic.playOverCounter++;
    } else {
        g_FieldingLogic.playOverCounter = 0x7FFF;
    }
    if (g_GameLogic.framePlayEnd > endFrame) {
        if (g_FieldingLogic.playOverCounter > endFrame - 0x5A) {
            g_FieldingLogic.playOverCounter = 0;
            g_FieldingLogic.framesSincePlayEnded = 0;
        }
    } else if (g_GameLogic.framePlayEnd < endFrame) {
        if (g_FieldingLogic.playOverInd != 0) {
            endFrame = g_GameLogic.framePlayEnd;
        }
    }
    if (g_Ball.deadBallReason == DEAD_BALL_REASON_HOME_RUN && g_Ball.matchFramesAndBallAngle.ballOverWallFrames == 0xB4 &&
        g_Stats.replayInd == 0) {
        lastPlayStats();
    }
    if (!g_d_GameSettings.exhibitionMatchInd && lbl_3_common_bss_37400.scoutMissionID != 0 && g_Stats.replayInd == 0 &&
        g_GameLogic.playOver != 0 && g_Ball.deadBallReason != DEAD_BALL_REASON_HOME_RUN) {
        lbl_3_common_bss_37400.scoutCountdown--;
        if (g_FieldingLogic.playOverCounter >= endFrame || lbl_3_common_bss_37400.scoutCountdown <= 5) {
            lastPlayStats();
        }
        if (lbl_3_common_bss_37400.scoutCountdown == 5 && g_Ball.deadBallReason != DEAD_BALL_REASON_HOME_RUN) {
            g_GameLogic.walkOffWinInd = 1;
            changeScene(3, 6);
            if (lbl_3_common_bss_37400._47 != 0) {
                playOverSounds(6);
            }
        }
        if (lbl_3_common_bss_37400.scoutCountdown <= 0) {
            playOverTransitionStuff();
        }
        if (g_Ball.deadBallReason != DEAD_BALL_REASON_HOME_RUN && g_Stats.replayPending != 0 &&
            lbl_3_common_bss_37400.scoutCountdown == 0x1E) {
            animRelated[0xB1] = 1;
        }
    } else if (g_FieldingLogic.playOverCounter >= endFrame) {
        if (g_Stats.replayInd == 0) {
            lastPlayStats();
        }
        playOverTransitionStuff();
    } else if (g_FieldingLogic.playOverCounter == endFrame - 6) {
        if (g_Stats.replayInd == 0 && animRelated[0xB1] == 0 && g_Ball.deadBallReason != DEAD_BALL_REASON_HOME_RUN) {
            g_GameLogic.walkOffWinInd = 1;
            changeScene(3, 6);
        }
    }
    if (g_FieldingLogic.playOverCounter == endFrame - 0x1E) {
        determineIfReplayShouldPlay();
        showReplay = 1;
        g_GameLogic.playOver = 1;
        if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FOUL && g_Ball.maybebuntOn2Strikes == 0) {
            g_GameLogic.playOver = 0;
            showReplay = 0;
        } else if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != PICKOFF_STEAL_CODE_NONE &&
                   g_FieldingLogic.liveBallBcOfPickoffOrStealCd != 4 && g_Pitcher.strikeOutOrWalk == 0 &&
                   g_Strikes.outs < g_Strikes.storedOuts) {
            showReplay = 0;
            g_GameLogic.playOver = 0;
        }
        if (g_Stats.replayPending != 0) {
            showReplay = 1;
        }
        if (showReplay != 0) {
            sound_crowd_EffectsStruct._2A = 1;
            sound_crowd_EffectsStruct._24 = 0x1D;
        }
        g_FieldingLogic.playOverInd = 1;
        g_FieldingLogic.framesSincePlayEnded = 1;
        if (g_GameLogic.IsStarChance == 1) {
            if (g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_FOUL || g_Ball.maybebuntOn2Strikes != 0) {
                int team;

                if (g_Strikes.outs > g_Strikes.storedOuts) {
                    g_GameLogic.IsStarChance = 2;
                    team = g_GameLogic.teamFielding;
                } else {
                    g_GameLogic.IsStarChance = 3;
                    team = g_GameLogic.teamBatting;
                }
                if (g_GameLogic.TeamStars[team] < 5 && g_GameLogic.EventTriggers_EndOfGame == 0) {
                    g_GameLogic.TeamStars[team]++;
                    if (g_Stats.replayInd == 0) {
                        playSoundEffect(0x19D);
                    }
                }
            }
        }
        if (!g_d_GameSettings.exhibitionMatchInd && lbl_3_common_bss_37400.scoutMissionID != 0 &&
            g_Stats.replayInd == 0 && g_GameLogic.playOver != 0) {
            challengeModeRelated_checkScoutMissionSuccess();
            if (g_Ball.deadBallReason != DEAD_BALL_REASON_HOME_RUN) {
                lbl_3_common_bss_37400.scoutCountdown = 0x78;
            }
            if (lbl_3_common_bss_37400.scoutFlag == 0) {
                if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd == PICKOFF_STEAL_CODE_NONE) {
                    animRelated[0xB4] = 1;
                } else if (g_Strikes.outs >= 3 || lbl_3_common_bss_37400._47 != 0) {
                    animRelated[0xB4] = 1;
                } else {
                    lbl_3_common_bss_37400.scoutCountdown = 8;
                }
            } else if (g_Stats.replayPending != 0) {
                lbl_3_common_bss_37400.scoutCountdown = endFrame - 0x4C;
            } else {
                lbl_3_common_bss_37400.scoutCountdown = 8;
            }
        }
        g_Stats._003B = 1;
    } else if (g_FieldingLogic.playOverCounter - 1 == endFrame - 0x1E) {
        if (lbl_3_common_bss_37400._47 == 0 && g_Ball.deadBallReason != DEAD_BALL_REASON_HOME_RUN &&
            g_Stats.replayPending != 0) {
            animRelated[0xB1] = 1;
        }
    }
    g_GameLogic.framePlayEnd = endFrame;
    g_GameLogic.CountdownUntilFade = endFrame - g_FieldingLogic.playOverCounter;
}

// .text:0x0005DF54 size:0x370 mapped:0x8069CFE8
void playOverTransitionStuff(void) {
    int didTransition = 0;

    if (g_Stats.replayInd != 0) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_DEMO && g_UnkSimulation_31AC0._08 != 0) {
        return;
    }
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    g_GameLogic.hudLoadingRelated = 1;
    g_GameLogic.playBatterWalkupAnimation = 0;
    postPitchStatUpdating(1);
    trackLastPitchInfo();
    if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != PICKOFF_STEAL_CODE_NONE && g_Strikes.outs < 3 &&
        g_GameLogic.EventTriggers_EndOfGame == 0) {
        didTransition = handleABEndEvent();
    }
    postPlayTrackStats();
    if (!g_d_GameSettings.exhibitionMatchInd && lbl_3_common_bss_37400._47 != 0) {
        lbl_3_common_bss_37400.scoutMissionID = 0;
        lbl_3_common_bss_37400._47 = 0;
    }
    if (g_GameLogic.EventTriggers_EndOfGame != 0) {
        SetGameStatus(GAME_STATUS_TRANSITION);
        didTransition = 1;
    } else if (g_Strikes.outs >= 3) {
        SetGameStatus(GAME_STATUS_TRANSITION);
        if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd >= PICKOFF_STEAL_CODE_PICKOFF &&
            g_FieldingLogic.liveBallBcOfPickoffOrStealCd <= 3 && g_Strikes.balls < 4 && g_Strikes.strikes < 3) {
            if (g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam] == 1) {
                storedInningInfo._44[g_GameLogic.homeTeamBattingInd_fieldingTeam]--;
            }
        } else {
            iterateBatter(g_GameLogic.homeTeamBattingInd_fieldingTeam);
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
            if (g_Practice.practiceLevel == 7 || g_Practice.practiceLevel == 6) {
                transferInMemRunnerValuesToNextRunnerIndex();
            }
        }
        didTransition = 1;
    } else if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FOUL && g_Ball.maybebuntOn2Strikes == 0) {
        initBaseRunnersAfterFoulBall();
        SetGameStatus(GAME_STATUS_DEFAULT);
        didTransition = 1;
    } else if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != PICKOFF_STEAL_CODE_NONE &&
               g_FieldingLogic.liveBallBcOfPickoffOrStealCd != 4) {
        transferInMemRunnerValuesToNextRunnerIndex();
        if (didTransition != 0) {
            iterateBatter(g_GameLogic.homeTeamBattingInd_fieldingTeam);
            SetGameStatus(GAME_STATUS_TRANSITION);
            didTransition = 1;
        } else {
            SetGameStatus(GAME_STATUS_0xA);
            didTransition = 1;
        }
    } else {
        transferInMemRunnerValuesToNextRunnerIndex();
        iterateBatter(g_GameLogic.homeTeamBattingInd_fieldingTeam);
        SetGameStatus(GAME_STATUS_TRANSITION);
        didTransition = 1;
    }
    pauseAnimations();
    Set_803cb848(0);
    pauseStateOnStadiums();
    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_NONE && g_Stats.replayPending == 1 && didTransition != 0) {
        if (g_Ball.deadBallReason == DEAD_BALL_REASON_HOME_RUN && g_Stats.replayInd == 0) {
            SetGameStatus(GAME_STATUS_HOMERUN_LAP);
        } else {
            g_Stats.replayPending = 2;
            transitionToReplay();
        }
        Set_803cb848(1);
    }
}

// .text:0x0005DD30 size:0x224 mapped:0x8069CDC4
void handleDeadBall(void) {
    int count = 0;
    int i;
    int runs;

    if (g_Ball.deadBallRBIsAddedInd != 0) {
        return;
    }
    if (g_Ball.deadBallReason == DEAD_BALL_REASON_GROUND_RULE_DOUBLE) {
        if (g_Runners[2].runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE) {
            g_Runners[2].scoredOnGRD = 1;
            count = 1;
        }
        if (g_Runners[3].runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE) {
            g_Runners[3].scoredOnGRD = 1;
            count++;
        }
        if (g_Scores.Inning >= g_Scores.inningLimit && g_Scores.halfInning != 0 &&
            g_Scores.scores[0].total == g_Scores._9E && count == 2) {
            g_Runners[2].scoredOnGRD = 0;
            count = 1;
        }
        g_Ball.deadBallRBIsAddedInd = 1;
        storedInningInfo.rbisWaitingToBeAddedToScore = count;
        g_Scores.scores[g_Scores.halfInning].byInning[g_Scores.Inning - 1] = g_Scores._9E;
        g_Scores._9C = count;
        if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR) {
            g_Ball.AtBat_ContactResult = BALL_RESULT_TYPE_LANDED;
        }
    } else if (g_Ball.deadBallReason == DEAD_BALL_REASON_BALL_DEAD) {
        runs = g_Scores.scores[1].total;
        for (i = 3; i >= 0; i--) {
            if (g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
                (i >= 2 || g_Runners[i].baseReachedAtTimeOfThrow >= 2)) {
                g_Runners[i].scoredOnGRD = 1;
                runs++;
                count++;
            }
            if (g_Scores.Inning >= g_Scores.inningLimit && g_Scores.halfInning != 0 &&
                g_Scores.scores[0].total < runs) {
                break;
            }
        }
        g_Scores._9C = count;
        g_Ball.deadBallRBIsAddedInd = 1;
        storedInningInfo.rbisWaitingToBeAddedToScore = count;
        if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR) {
            g_Ball.AtBat_ContactResult = BALL_RESULT_TYPE_LANDED;
        }
    }
}

// .text:0x0005DCE0 size:0x50 mapped:0x8069CD74
int handleABEndEvent(void) {
    int result = 0;

    if (g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT) {
        resetBatterCount();
        result = 1;
    } else if (g_Pitcher.strikeOutOrWalk == AT_BAT_END_WALK) {
        handleHPBORRunnerAdvance();
        result = 1;
    }
    return result;
}

// .text:0x0005DA9C size:0x244 mapped:0x8069CB30
void settingGameStatus(void) {
    matchTransitionFunction2();
    if (g_GameLogic.EventTriggers_EndOfGame != 0) {
        if (!g_d_GameSettings.exhibitionMatchInd) {
            if (g_GameLogic.homeTeamInd ^ (g_d_GameSettings.humanTeamNumber == g_Scores.winnerCd)) {
                if (g_d_GameSettings.bJMatchInd != 1 ||
                    (g_GameLogic.homeTeamInd ^ (g_d_GameSettings.humanTeamNumber != g_Scores.winnerCd)) == 0) {
                    challenge_checkRecruitment();
                }
            }
        }
        endOfGameStats_MVP();
    }
    g_GameLogic.writeOnly_always0 = 0;
    g_GameLogic.writeOnly_always0_2 = 0;
    g_GameLogic.playOverInd = 0;
    g_Scores._pad_BF[2] = g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total - g_Scores._A0;
    g_Pitcher._15D = 0;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_DEMO &&
        (FrameCountOfEntireGame[0] >= 0x2A30 || g_UnkSimulation_31AC0._08 != 0)) {
        g_GameLogic.framesOfExitingToMenu = 1;
    } else if (g_GameLogic.EventTriggers_EndOfGame != 0) {
        fn_3_5D9F8();
    } else if (g_Strikes.outs >= 3) {
        fn_3_5D9F8();
    } else {
        SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
    }
}

// .text:0x0005D9F8 size:0xA4 mapped:0x8069CA8C
void fn_3_5D9F8(void) {
    if (g_Stats.replayInd == 0) {
        g_Pitcher._15C = 0;
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_DEMO && g_Scores.halfInning == 0) {
            g_GameLogic.framesOfExitingToMenu = 1;
        } else if (g_GameLogic.EventTriggers_EndOfGame != 0) {
            SetGameStatus(GAME_STATUS_END_OF_GAME);
        } else {
            SetGameStatus(GAME_STATUS_INNING_TRANSITION);
        }
    }
}

// .text:0x0005D5E8 size:0x410 mapped:0x8069C67C
void inningChange(void) {
    int i;
    int charID;

    if (g_GameLogic._125 == 0) {
        changeScene(1, 6);
        switchHalfInning();
        inningImportanceAI();
        hugeAnimStruct[0x3087] = 0;
        animRelated[0x9B] = 0;
        animRelated[0x9C] = 0;
        highLevelSimulationFlag[3] = 0;
        g_GameLogic._125 = 1;
    } else if (g_GameLogic._125 == 1) {
        if (championshipScreenGraphics() != 0) {
            hugeAnimStruct[0x3081] = 0;
            g_GameLogic._125 = 2;
        }
    } else if (g_GameLogic._125 == 2) {
        for (i = 1; i < 10; i++) {
            if (g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][i][1] == 1) {
                charID = inMemRoster[g_GameLogic.teamFielding]
                                    [g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][i][0]]
                                        .stats.CharID;
            }
        }
        if (loadFielderActors(charID) != 0) {
            hugeAnimStruct[0x3081] = 0;
            g_GameLogic._125 = 3;
        }
    } else if (g_GameLogic._125 == 3) {
        if (loadPitcherActor() != 0) {
            g_GameLogic._125 = 6;
        }
    } else if (g_GameLogic._125 == 6) {
        if (g_GameLogic.FrameCountOfCurrentPitch >= 0x78) {
            if (checkForButtonPressToSkip(1, 0x1300)) {
                g_GameLogic._125 = 7;
            }
        }
        if (fn_3_FD9FC() != 0) {
            g_GameLogic._125 = 7;
        }
    } else if (g_GameLogic._125 == 7) {
        changeScene(3, 6);
        g_GameLogic._125 = 8;
    } else if (g_GameLogic._125 == 8) {
        if (lbl_8037169C[0x13] != 0) {
            g_GameLogic._125 = 9;
        }
    } else if (g_GameLogic._125 == 9) {
        pauseAnimations();
        pauseStateOnStadiums();
        hugeAnimStruct[0x3087] = 1;
        fn_3_FBD70();
        fn_3_FBD58();
        SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
    }
}

// .text:0x0005D51C size:0xCC mapped:0x8069C5B0
void switchHalfInning(void) {
    if (g_Scores.halfInning == 0) {
        g_Scores.halfInning = 1;
    } else {
        g_Scores.halfInning = 0;
        g_Scores.Inning++;
    }
    g_GameLogic.homeTeamBattingInd_fieldingTeam ^= 1;
    g_GameLogic.awayTeamBattingInd_battingTeam ^= 1;
    g_GameLogic.teamBatting ^= 1;
    g_GameLogic.teamFielding ^= 1;
    g_GameLogic._131[0] = 0;
    g_GameLogic._131[1] = 0;
    g_Scores._A0 = g_Scores.scores[g_Scores.halfInning].total;
    resetCount();
    resetInMemRunners();
    resetInMemBall();
    resetInMemPitcher();
    resetInMemFielders();
    resetGameControlVars_duringNewInning();
    resetSomethingRelatedToVersus();
}

// .text:0x0005D3FC size:0x120 mapped:0x8069C490
void inningImportanceAI(void) {
    GameInitVariables* settings = &g_d_GameSettings;

    g_GameLogic.writeOnly_always0 = 0;
    g_GameLogic.writeOnly_always0_2 = 0;
    g_RunningLogic._11 = 0;
    g_RunningLogic._13 = 0;
    g_RunningLogic._02 = 0;
    g_Scores._pad_AC = evaluateInningCondition(g_Scores.Inning);
    g_Scores._pad_BF[2] = 0;
    g_Scores._C6 = 0;
    lbl_3_common_bss_37400.scoutFlag = 0;
    setInningEndingKIndTo0();
    if (!settings->exhibitionMatchInd) {
        setScoutMissionRelatedToZero();
    }
}

// .text:0x0005D094 size:0x368 mapped:0x8069C128
void endOfGameCheck(int arg0) {
    if (g_GameLogic.EventTriggers_EndOfGame != 0) {
        return;
    }
    if (arg0 == 0) {
        if (g_Scores.Inning >= g_Scores.inningLimit) {
            if (g_Scores.halfInning == 0) {
                if (g_Scores.scores[0].total >= g_Scores.scores[1].total) {
                    return;
                }
                g_Scores.winnerCd = 1;
                g_GameLogic.EventTriggers_EndOfGame = 1;
                g_GameLogic.winType = WIN_TYPE_2;
            } else if (g_Scores.scores[0].total < g_Scores.scores[1].total) {
                g_Scores.winnerCd = 1;
                g_GameLogic.EventTriggers_EndOfGame = 1;
                g_GameLogic.winType = WIN_TYPE_2;
            } else if (g_Scores.scores[0].total > g_Scores.scores[1].total) {
                g_Scores.winnerCd = 0;
                g_GameLogic.EventTriggers_EndOfGame = 1;
                g_GameLogic.winType = WIN_TYPE_1;
            } else {
                if (g_Scores.Inning < g_Scores.maxNumberOfExtraInnings) {
                    return;
                }
                g_Scores.winnerCd = 2;
                g_GameLogic.EventTriggers_EndOfGame = 1;
                g_GameLogic.winType = WIN_TYPE_4;
            }
        } else {
            int diff;

            if (g_Scores.mercyThreshold == 0) {
                return;
            }
            if (g_Scores.halfInning == 0) {
                return;
            }
            diff = g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total -
                   g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total;
            if (diff >= g_Scores.mercyThreshold) {
                g_Scores.winnerCd = 1;
                g_GameLogic.EventTriggers_EndOfGame = 1;
                g_GameLogic.winType = WIN_TYPE_6;
                QueueTextToDisplay(0x11, 0);
            } else {
                if (diff > -g_Scores.mercyThreshold) {
                    return;
                }
                g_Scores.winnerCd = 0;
                g_GameLogic.EventTriggers_EndOfGame = 1;
                g_GameLogic.winType = WIN_TYPE_5;
                QueueTextToDisplay(0x11, 0);
            }
        }
    } else if (arg0 == 1) {
        if (g_Scores.Inning >= g_Scores.inningLimit && g_Scores.halfInning == 1) {
            if (g_Scores.scores[0].total >= g_Scores.scores[1].total) {
                return;
            }
            g_Scores.winnerCd = 1;
            g_GameLogic.EventTriggers_EndOfGame = 1;
            g_GameLogic.winType = WIN_TYPE_3;
        } else {
            int diff;

            if (g_Scores.halfInning == 0) {
                return;
            }
            if (g_Scores.mercyThreshold == 0) {
                return;
            }
            diff = g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total -
                   g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total;
            if (diff < g_Scores.mercyThreshold) {
                return;
            }
            g_Scores.winnerCd = 1;
            g_GameLogic.EventTriggers_EndOfGame = 1;
            g_GameLogic.winType = WIN_TYPE_6;
            QueueTextToDisplay(0x11, 0);
        }
    } else {
        return;
    }
    fn_3_5CFD0();
    if (g_GameLogic.winType == WIN_TYPE_5 || g_GameLogic.winType == WIN_TYPE_6) {
        if (!g_d_GameSettings.exhibitionMatchInd) {
            if (g_d_GameSettings.humanTeamNumber == (g_Scores.winnerCd ^ g_GameLogic.homeTeamInd)) {
                recruitWholeTeamAfterMercy();
                g_d_GameSettings.someChallengeModeFlag = 1;
            }
        }
    }
}

// .text:0x0005CFD0 size:0xC4 mapped:0x8069C064
void fn_3_5CFD0(void) {
    u8* tracker = (u8*)starMissionCompletionTracker;
    int a = tracker[0x441C];
    int b = tracker[0x441E];

    if (!g_d_GameSettings.exhibitionMatchInd) {
        if (g_Scores.winnerCd <= 1) {
            if (g_Scores.winnerCd ^ (g_GameLogic.homeTeamInd == lbl_3_common_bss_37400._40)) {
                if ((tracker[0x4422] >= 4 && b == 5) || (tracker[0x4422] >= 5 && (int)tracker[0x44EF] == 1 && a == 5)) {
                    g_GameLogic.playOverFadeOutStarted = 0;
                }
                starMissionRelated2();
            }
        }
    }
}

// .text:0x0005CDB4 size:0x21C mapped:0x8069BE48
void endOfMatch(void) {
    switch (g_GameLogic._125) {
    case 0:
        changeScene(1, 6);
        g_GameLogic.scoreBook_teamDisplayed = 0;
        animRelated[0x9B] = 0;
        animRelated[0x9A] = 0;
        g_GameLogic._125 = 1;
        break;
    case 1:
        if (g_GameLogic.playOverFadeOutStarted >= 0 && g_GameLogic.scoreBook_teamDisplayed == 0) {
            break;
        }
        if (g_GameLogic.FrameCountOfCurrentPitch >= 0x28) {
            if (checkForButtonPressToSkip(1, 0x1300)) {
                g_GameLogic._125 = 2;
            }
        }
        if (fn_3_FD9FC() != 0) {
            g_GameLogic._125 = 2;
        }
        break;
    case 2:
        if (!g_d_GameSettings.exhibitionMatchInd && g_d_GameSettings.bJMatchInd == 1) {
            challenge_setTransitionScreenCharacterPortrait(
                0xC, challengeTransitionPortraitIDs[((u8*)starMissionCompletionTracker)[0x441C]]);
        } else {
            changeScene(3, 6);
        }
        playOverSounds(-1);
        g_GameLogic._125 = 3;
        break;
    case 3:
        if (lbl_8037169C[0x13] != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
            g_GameLogic._125 = 4;
        }
        break;
    case 4:
        if (g_GameLogic.playOverFadeOutStarted >= 0) {
            SetGameStatus(GAME_STATUS_MVP_END_GAME);
            transitionToReplay();
        } else if (!g_d_GameSettings.exhibitionMatchInd && g_d_GameSettings.bJMatchInd == 1) {
            g_GameLogic._125 = 5;
        } else {
            SetGameStatus(GAME_STATUS_MVP_END_GAME);
            transitionToReplay();
        }
        break;
    case 5:
        transitionToReplay();
        g_GameLogic._125 = 6;
        break;
    case 6:
        g_GameLogic.exitingToMenu = 1;
        g_GameLogic.framesOfExitingToMenu = 1;
        break;
    }
    if (g_GameLogic.playOverFadeOutStarted >= 0 && g_GameLogic.scoreBook_teamDisplayed == 0) {
        g_GameLogic.teamFielding = g_GameLogic.playOverFadeOutStarted;
        g_GameLogic.scoreBook_teamDisplayed = championshipScreenGraphics();
    }
}

// .text:0x0005CD24 size:0x90 mapped:0x8069BDB8
void fn_3_5CD24(void) {
    if (g_GameLogic._125 == 0) {
        animRelated[0x9A] = 0;
        initializeARunner();
        initializeSomethingDuringTransition2();
        matchTransitionFunction2();
        g_GameLogic._125++;
    } else if (g_GameLogic._125 == 1) {
        if (loadRunnerActors() != 0) {
            highLevelSimulationFlag[2] = 0;
            SetGameStatus(GAME_STATUS_DEFAULT);
        }
    }
}

// .text:0x0005C74C size:0x5D8 mapped:0x8069B7E0
void processScoreChanges(int arg0) {
    int runnersOut = 0;
    u64 total = 0;
    int i;
    int diff;

    if ((g_Pitcher.strikeOutOrWalk == AT_BAT_END_WALK || g_Pitcher.strikeOutOrWalk == AT_BAT_END_HIT_BY_PITCH) &&
        g_Scores._9C > 0) {
        goto score;
    }
    if (g_GameLogic.gameStatus != GAME_STATUS_AT_BAT && g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
        return;
    }
    if (g_Scores._9C <= 0) {
        return;
    }
    if (g_Strikes.outs >= 3 && arg0 != 1) {
        return;
    }
    if (g_Stats.replayInd != 0 && g_Ball.deadBallReason == DEAD_BALL_REASON_HOME_RUN) {
        return;
    }
    if (g_Scores.Inning >= g_Scores.inningLimit && g_Scores.halfInning != 0 &&
        g_Ball.deadBallReason == DEAD_BALL_REASON_NONE) {
        int homeTotal = g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total;
        int awayTotal = g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total + 1;

        if (homeTotal + g_Scores._9C > awayTotal) {
            g_Scores._9C = awayTotal - homeTotal;
        }
        if (g_Scores._9C < 0) {
            g_Scores._9C = 0;
        }
    }
    if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd == PICKOFF_STEAL_CODE_NONE) {
        if (g_Ball.ballInitialHitDoneInd == 0) {
            return;
        }
        if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR || g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FOUL) {
            return;
        }
    }
    for (i = 0; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD && g_Runners[i].forceOutCd == 1) {
            runnersOut++;
        }
    }
    if (g_Ball.deadBallReason == DEAD_BALL_REASON_NONE) {
        if (g_Strikes.outs >= 3) {
            if (g_Strikes.forcedOutToEndInningInd == 1) {
                return;
            }
            if (g_Strikes.storedOuts == 2 && g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT) {
                return;
            }
        } else if (g_Strikes.outs + runnersOut >= 3) {
            return;
        }
    }
score:
    if (g_Ball.deadBallReason != DEAD_BALL_REASON_GROUND_RULE_DOUBLE) {
        for (i = 0; i < 4; i++) {
            if (g_Runners[i].isEligibleToScore != 0 && g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) {
                if (g_Stats.replayInd == 0) {
                    storedInningInfo.rbisWaitingToBeAddedToScore++;
                }
                g_Runners[i].isEligibleToScore = 0;
            }
        }
    }
    if (g_Ball.deadBallReason == DEAD_BALL_REASON_HOME_RUN) {
        g_Scores.scores[g_Scores.halfInning].byInning[g_Scores.Inning - 1] =
            g_Scores._9E + g_RunningLogic.nOffensivePlayersAtStartOfPlay;
        g_Scores._C2 = g_RunningLogic.nOffensivePlayersAtStartOfPlay;
    } else {
        g_Scores.scores[g_Scores.halfInning].byInning[g_Scores.Inning - 1] += g_Scores._9C;
        g_Scores._C2 += g_Scores._9C;
    }
    if (g_Scores.scores[g_Scores.halfInning].byInning[g_Scores.Inning - 1] > 99) {
        g_Scores.scores[g_Scores.halfInning].byInning[g_Scores.Inning - 1] = 99;
    }
    for (i = 1; i < 19; i++) {
        total += g_Scores.scores[g_Scores.halfInning].byInning[i - 1];
    }
    if (total > 99) {
        total = 99;
    }
    g_Scores.scores[g_Scores.halfInning].total = total;
    diff = g_Scores.scores[0].total - g_Scores.scores[1].total;
    if (diff < -0x8000) {
        diff = -0x8000;
    }
    if (diff > 0x7FFF) {
        diff = 0x7FFF;
    }
    if (diff < 0) {
        diff = -diff;
    }
    g_Scores._A6 = diff;
    updatePitcherStatsOnScoreChange();
    g_Scores._9C = 0;
    if (g_Pitcher.strikeOutOrWalk != AT_BAT_END_WALK && g_Pitcher.strikeOutOrWalk != AT_BAT_END_HIT_BY_PITCH &&
        g_Ball.deadBallReason != DEAD_BALL_REASON_HOME_RUN) {
        animRelated[0x99] = 1;
    }
    if (g_Stats.replayInd == 0 && g_Pitcher.strikeOutOrWalk != AT_BAT_END_WALK &&
        g_Pitcher.strikeOutOrWalk != AT_BAT_END_HIT_BY_PITCH) {
        playSoundEffect(0x198);
    }
    endOfGameCheck(1);
}

// .text:0x0005C69C size:0xB0 mapped:0x8069B730
void transitionToLiveBallWithoutContact(int arg0) {
    g_Ball.framesSinceHit = 100;
    g_Ball.framesSincePickOff = 0;
    g_FieldingLogic.liveBallBcOfPickoffOrStealCd = arg0 + 1;
    g_FieldingLogic.throwSpeedType = 3;
    SetGameStatus(GAME_STATUS_LIVE_BALL);
    g_FieldingLogic.playOverCounter = 0;
    g_Pitcher.peachDaisyStarAnimationOn = 0;
    stealSetFielders();
    stealCancelLeadoffs();
    if (g_Strikes.balls >= 4) {
        g_Runners[0].runnerOnFieldOrOutOrScored = RUNNER_STATUS_WALK_WHILE_STEALING;
    } else {
        g_Runners[0].runnerOnFieldOrOutOrScored = RUNNER_STATUS_SCORED_DEAD_BALL;
    }
}

// .text:0x0005C5C8 size:0xD4 mapped:0x8069B65C
void uncalledRunnerUpdateRelated(void) {
    int i;

    for (i = 0; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD ||
            g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY ||
            g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DEAD_BALL) {
            g_Runners[i].runnerOnFieldOrOutOrScored = RUNNER_STATUS_SCORED_DURING_PLAY;
            g_Scores._9C++;
        }
    }
}

// .text:0x0005C530 size:0x98 mapped:0x8069B5C4
int evaluateInningCondition(int inning) {
    if (inning > g_Scores.inningLimit) {
        return 5;
    }
    if (g_Scores.inningLimit <= 3) {
        if (g_Scores.inningLimit == inning && g_Scores.halfInning != 0) {
            return 4;
        }
        return 0;
    }
    if (inning == g_Scores.inningLimit) {
        return 4;
    }
    if ((g_Scores.inningLimit == 9 && inning >= 7) || (g_Scores.inningLimit == 7 && inning >= 6)) {
        return 3;
    }
    if (inning >= 4) {
        return 2;
    }
    return 1;
}

// .text:0x0005C418 size:0x118 mapped:0x8069B4AC
void fn_3_5C418(void) {
    int skippable = 0;

    if (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT || g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL ||
        (u8)(g_GameLogic.gameStatus - GAME_STATUS_HOMERUN_END) <= 3 ||
        g_GameLogic.gameStatus == GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY) {
        skippable = 1;
    }
    if (g_UnkSimulation_31AC0._08 == 0) {
        if (AtBat_ButtonInput1._02 & INPUT_BUTTON_START) {
            g_UnkSimulation_31AC0._08 = 1;
        }
    } else {
        if (skippable != 0) {
            changeScene(3, 6);
        }
        if (lbl_8037169C[0x13] != 0 && skippable != 0) {
            if ((int)((u8*)&lbl_803C6CF8)[0x715] == 1) {
                animRelated[0x96] = 1;
                g_GameLogic.framesOfExitingToMenu = 1;
            } else if (g_UnkSimulation_31AC0._09 == 0) {
                handleDVDCancelAndARQRemoval();
                g_UnkSimulation_31AC0._09 = 1;
            }
        }
    }
}

// .text:0x0005BD40 size:0x6D8 mapped:0x8069ADD4
void matchEndGameScreenFunction(void) {
    s8 mvp;
    InputStruct* input = &g_Controls[(u8)lbl_80366158[0x27]];
    u32 stage = g_GameLogic._125;

    if (stage >= 3) {
        if (pauseControl._12 < 0x7FFE) {
            (pauseControl._12)++;
        } else {
            pauseControl._12 = 0x7FFF;
        }
    }
    switch (stage) {
    case 0:
        pauseControl.cursor = 0;
        pauseControl._1DB = 0;
        pauseControl._1D8 = 0;
        pauseControl._12 = 0;
        g_GameLogic.scoreBook_teamDisplayed = 0;
        g_GameLogic.scoreBook_batter_pitcherStatsDisplayed = 0;
        g_GameLogic.scoreBook_scrollIndex = 0;
        g_GameLogic.scoreBook_logoFadeDirectionLeft_Right = 0;
        g_GameLogic._118 = 0;
        g_GameLogic._11A = -1;
        if (!g_d_GameSettings.exhibitionMatchInd) {
            fn_3_5B41C();
        }
        g_GameLogic._125 = 1;
        break;
    case 1:
        if (diskReadRelated(&CommonUIFiles_matchEnd[1], 0xC) != 0) {
            animRelated[0x9A] = 0;
            animRelated[0xD1] = 1;
            g_GameLogic._125 = 2;
        }
        break;
    case 2:
        if (loadMVPMaybe() != 0) {
            fn_3_8C104(-1);
            g_GameLogic._125 = 3;
        }
        break;
    case 3:
        changeScene(1, 6);
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125 = 4;
        break;
    case 4:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0xB4) {
            u8 flag = g_GameLogic._13D;

            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            if (flag != 0) {
                if (!g_d_GameSettings.exhibitionMatchInd) {
                    g_GameLogic._125 = 7;
                } else {
                    g_GameLogic._125 = 6;
                }
            } else {
                g_GameLogic._125 = 7;
            }
        }
        break;
    case 5:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
            fn_8004CC4C(7, 0, 0, 0, 0x8B);
            mvp = StatsScreenScores.mvpRosterLoc[0];
            if (mvp >= 0) {
                fn_8004CA48(((CharacterStats*)inMemRoster)[mvp].stats.CharID, 0, 0, 0);
            } else {
                mvp = StatsScreenScores.mvpRosterLoc[1];
                if (mvp >= 0) {
                    fn_8004CA48(((CharacterStats*)inMemRoster)[mvp].stats.CharID, 0, 0, 0);
                }
            }
        }
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy >= 0x14 && (input->newButtonInput & INPUT_BUTTON_A)) {
            set803c5f77();
        }
        if (lbl_803C5F74[3] == 4) {
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_GameLogic._125 = 6;
        }
        break;
    case 6:
        if (fn_3_5B220(0) != 0) {
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_GameLogic._125 = 7;
        }
        break;
    case 7:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x2D) {
            endOfGame_menuControl();
        }
        break;
    case 8:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x2D) {
            pauseControl._12 = 0;
            pauseControl._1D8 ^= 1;
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_GameLogic._125 = 7;
        }
        break;
    case 9:
        if (g_GameLogic.playOverFadeOutStarted >= 0) {
            changeScene(3, 6);
        } else if (!g_d_GameSettings.exhibitionMatchInd) {
            if (g_d_GameSettings.bJMatchInd == 1) {
                challenge_setTransitionScreenCharacterPortrait(0xC, challengeTransitionPortraitIDs[((u8*)starMissionCompletionTracker)[0x441C]]);
            } else {
                challenge_setTransitionScreenCharacterPortrait(0xC, challengeTransitionPortraitIDs[((u8*)starMissionCompletionTracker)[0x441E]]);
            }
        } else {
            changeScene(4, 6);
        }
        if (lbl_8037169C[0x13] != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
            g_GameLogic._125 = 10;
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        }
        break;
    case 10:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0xA) {
            transitionToReplay();
            g_GameLogic._125 = 11;
            animRelated[0xCD] = 1;
        }
        break;
    case 11:
        if (g_GameLogic.playOverFadeOutStarted >= 0) {
            SetGameStatus(GAME_STATUS_CHAMPIONSHIP);
        } else {
            g_GameLogic.exitingToMenu = 1;
            g_GameLogic.framesOfExitingToMenu = 1;
        }
        break;
    }
}

// .text:0x0005BA2C size:0x314 mapped:0x8069AAC0
void endOfGame_menuControl(void) {
    InputStruct* input = &g_Controls[lbl_80366158[0x27]];

    if (pauseControl._1D8 == 0) {
        if (input->newButtonInput & INPUT_BUTTON_A) {
            if (pauseControl.cursor == 0) {
                g_GameLogic._125 = 9;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            } else {
                animRelated[0xCE] = 1;
                g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                g_GameLogic._125 = 8;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            }
        } else if (input->newButtonInput & INPUT_BUTTON_RIGHT) {
            if (pauseControl.cursor == 0) {
                pauseControl.cursor = 1;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else if (input->newButtonInput & INPUT_BUTTON_LEFT) {
            if (pauseControl.cursor == 1) {
                pauseControl.cursor = 0;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    } else if (animRelated[0xD2] == 0) {
        if (input->newButtonInput & INPUT_BUTTON_B) {
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_GameLogic._125 = 8;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        } else if ((input->newButtonInput & INPUT_TRIGGER_R) || (input->newButtonInput & INPUT_TRIGGER_L)) {
            if (input->newButtonInput & INPUT_TRIGGER_L) {
                g_GameLogic.scoreBook_logoFadeDirectionLeft_Right = 0;
            } else {
                g_GameLogic.scoreBook_logoFadeDirectionLeft_Right = 1;
            }
            g_GameLogic.scoreBook_teamDisplayed ^= 1;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (input->newButtonInput & INPUT_BUTTON_RIGHT) {
            if (g_GameLogic.scoreBook_batter_pitcherStatsDisplayed == 0) {
                g_GameLogic.scoreBook_batter_pitcherStatsDisplayed = 1;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else if (input->newButtonInput & INPUT_BUTTON_LEFT) {
            if (g_GameLogic.scoreBook_batter_pitcherStatsDisplayed == 1) {
                g_GameLogic.scoreBook_batter_pitcherStatsDisplayed = 0;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else if (input->buttonInput & INPUT_BUTTON_UP) {
            if (g_GameLogic.scoreBook_scrollIndex != 0) {
                g_GameLogic.scoreBook_scrollIndex--;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else if (input->buttonInput & INPUT_BUTTON_DOWN) {
            if (g_GameLogic.scoreBook_scrollIndex < 4) {
                g_GameLogic.scoreBook_scrollIndex++;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    }
}

// .text:0x0005B5A0 size:0x48C mapped:0x8069A634
void startChallengeModeMatch(void) {
    int i;
    int j;

    g_d_GameSettings.challengeMinigame_baseCoinsEarned = 0;
    g_d_GameSettings.bJMatchRelated = 0;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        if (g_GameLogic.teamIsCPU[g_GameLogic.homeTeamInd] != 0) {
            g_GameLogic.AIDifficulty0Special3Weak[0] = lbl_3_data_6074[g_d_GameSettings.challengeDifficulty];
        } else {
            g_GameLogic.AIDifficulty0Special3Weak[1] = lbl_3_data_6074[g_d_GameSettings.challengeDifficulty];
        }
        if (g_d_GameSettings.bJMatchInd == 1) {
            int idx;
            int flags;

            g_Scores.Inning = 9;
            g_Scores.inningLimit = 9;
            g_Scores.maxNumberOfExtraInnings = 9;
            g_Scores.halfInning = 1;
            g_GameLogic.homeTeamBattingInd_fieldingTeam ^= 1;
            g_GameLogic.awayTeamBattingInd_battingTeam ^= 1;
            g_GameLogic.teamBatting ^= 1;
            g_GameLogic.teamFielding ^= 1;
            idx = rand() % 2;
            g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam] =
                lbl_3_data_5FF4[g_d_GameSettings.home_AwaySetting][g_d_GameSettings.challengeDifficulty][idx].currentBatter;
            g_Strikes.storedOuts = lbl_3_data_5FF4[g_d_GameSettings.home_AwaySetting][g_d_GameSettings.challengeDifficulty][idx].outs;
            g_Strikes.outs = lbl_3_data_5FF4[g_d_GameSettings.home_AwaySetting][g_d_GameSettings.challengeDifficulty][idx].outs;
            g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total =
                lbl_3_data_5FF4[g_d_GameSettings.home_AwaySetting][g_d_GameSettings.challengeDifficulty][idx].score;
            if (g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total < 0) {
                g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total =
                    -g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total;
                g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total = 0;
            }
            flags = lbl_3_data_5FF4[g_d_GameSettings.home_AwaySetting][g_d_GameSettings.challengeDifficulty][idx].runnerFlags;
            g_Runners[1].rosterID = -1;
            g_Runners[2].rosterID = -1;
            g_Runners[3].rosterID = -1;
            if (flags & 1) {
                i = g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam] - 1;
                if (i < 1) {
                    i = 9;
                }
                g_Runners[1].rosterID =
                    g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.homeTeamBattingInd_fieldingTeam][i][0];
            }
            if (flags & 0x10) {
                i = g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam] - 1;
                if (i < 1) {
                    i = 9;
                }
                g_Runners[2].rosterID =
                    g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.homeTeamBattingInd_fieldingTeam][i][0];
            }
            if (flags & 0x100) {
                i = g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam] - 1;
                if (i < 1) {
                    i = 9;
                }
                g_Runners[3].rosterID =
                    g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.homeTeamBattingInd_fieldingTeam][i][0];
            }
            setBatterContactConstants();
            initializeARunner();
            g_d_GameSettings.home_AwaySetting ^= 1;
        } else {
            if (Static_Stats_Tables.captainSelectedID[1] == 9 || *(s16*)&((u8*)starMissionCompletionTracker)[0x16C2] == 0x2A) {
                g_Scores.inningLimit = challengeInnings[g_d_GameSettings.challengeDifficulty * 3 + 1];
            } else {
                g_Scores.inningLimit = challengeInnings[g_d_GameSettings.challengeDifficulty * 3];
            }
            g_Scores.maxNumberOfExtraInnings = g_Scores.inningLimit + 3;
        }
        g_Scores.mercyThreshold = challengeInnings[g_d_GameSettings.challengeDifficulty * 3 + 2];
    }
    for (i = 0; i < 54; i++) {
        for (j = 0; j < 10; j++) {
            if ((s8)starMissionCompletionTracker[i].inGameMissionTracker[j].starMissionStatus != -2) {
                starMissionCompletionTracker[i].inGameMissionTracker[j].starMissionStatus = STAR_MISSION_TRACKING_NOT_COMPLETED;
            }
        }
    }
}

// .text:0x0005B41C size:0x184 mapped:0x8069A4B0
void fn_3_5B41C(void) {
    int result = 2;
    int diff;

    if (g_Scores.winnerCd == 2) {
        result = 1;
    } else if (g_Scores.winnerCd == g_GameLogic.homeTeamInd) {
        result = 0;
    }
    if (g_d_GameSettings.bJMatchInd == 0) {
        g_d_GameSettings.challengeMinigame_baseCoinsEarned += challenge_baseCoinsAwarded[result];
        diff = g_Scores.scores[g_GameLogic.homeTeamInd].total - g_Scores.scores[g_GameLogic.homeTeamInd ^ 1].total;
        if (diff < 0) {
            diff = -diff;
        }
        if (result == 0) {
            g_d_GameSettings.challengeMinigame_baseCoinsEarned += diff * challenge_baseCoinsAwarded[3] / 100;
        } else if (result == 2) {
            g_d_GameSettings.challengeMinigame_baseCoinsEarned += diff * challenge_baseCoinsAwarded[4] / 100;
        }
        g_d_GameSettings.challengeMinigame_baseCoinsEarned +=
            g_GameLogic.TeamStars[0] * challenge_baseCoinsAwarded[5] / 100;
    } else {
        g_d_GameSettings.challengeMinigame_baseCoinsEarned += challenge_baseCoinsAwarded[result + 9];
        g_d_GameSettings.bJMatchRelated += challenge_baseCoinsAwarded[result + 12];
    }
}

// .text:0x0005B408 size:0x14 mapped:0x8069A49C
void fn_3_5B408(void) {
    g_GameLogic.frame_exitMenuShowing = 0;
}

// .text:0x0005B380 size:0x88 mapped:0x8069A414
int exitMenu_main(void) {
    if (g_GameLogic.frame_exitMenuShowing < 0x7FFE) {
        g_GameLogic.frame_exitMenuShowing++;
    } else {
        g_GameLogic.frame_exitMenuShowing = 0x7FFF;
    }
    if (g_GameLogic.frame_exitMenuShowing > 0x14) {
        int result = exitMenu();
        if (result == 1) {
            return 1;
        } else if (result == 2) {
            set803c5f77();
        } else if (result == 4) {
            return 2;
        }
    }
    return 0;
}

// .text:0x0005B368 size:0x18 mapped:0x8069A3FC
void fn_3_5B368(void) {
    g_GameLogic.frames_memoryCardWriteOnMVP = 0;
    g_GameLogic.endGameStage = 0;
}

// .text:0x0005B220 size:0x148 mapped:0x8069A2B4
int fn_3_5B220(int arg0) {
    if (g_GameLogic.frames_memoryCardWriteOnMVP < 0x7FFE) {
        g_GameLogic.frames_memoryCardWriteOnMVP++;
    } else {
        g_GameLogic.frames_memoryCardWriteOnMVP = 0x7FFF;
    }
    switch (g_GameLogic.endGameStage) {
    case 0:
        if (arg0 == 1 && g_Minigame.grandPrixInd == 0 && g_Minigame.difficultyUnlockedInd == 0 && g_Minigame.grandPrixUnlockedInd == 0 &&
            g_Minigame.newRecordRank == 0) {
            return 1;
        }
        fn_8003BF54(lbl_80366158[0x27], 0, 0, 1, 0, 4, 5, 0, 0);
        g_GameLogic.endGameStage++;
        break;
    case 1:
        if (currentDrawingItem->state == 1 || (u16)(currentDrawingItem->state - 0xB) <= 1 ||
            currentDrawingItem->state == 7) {
            g_GameLogic.endGameStage++;
        }
        break;
    default:
        return 1;
    }
    return 0;
}

// .text:0x0005B0C4 size:0x15C mapped:0x8069A158
void gameSimulationFunction(void) {
    lbl_80366158[0x28] = 0;
    g_d_GameSettings.FrameCountWhileNotAtMainMenu++;
    lbl_80366158[0x28] = 0;
    unkPauseSimulationCheck();
    if (g_UnkSimulation_31AC0._05 != 0) {
        if (g_UnkSimulation_31AC0._06 == 0) {
            g_UnkSimulation_31AC0._05 = 0;
        } else {
            g_UnkSimulation_31AC0._06--;
            highLevelSimulationFlag[0] = 1;
            goto graphics;
        }
    }
    if (g_GameLogic.PauseSimulationFrameCount != 0) {
        g_GameLogic.PauseSimulationFrameCount--;
        if (g_GameLogic.PauseSimulationFrameCount != 0) {
            lbl_80366158[0x28] = 1;
        } else {
            lbl_80366158[0x28] = 0;
        }
    }
    if (lbl_80366158[0x28] == 0) {
        FrameCountOfEntireGame[0]++;
        simulate1FrameOfTheGame();
    }
graphics:
    if (g_d_GameSettings.minigamesEnabled) {
        graphicsFunction_minigames();
    } else {
        graphicsFunction_nonMiniGame();
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
            fn_3_1663AC();
        }
    }
    cameraControl();
    soundControl();
    FrameCountOfEntireGame[2] = g_Ball.StaticRandomInt1;
    FrameCountOfEntireGame[3] = g_Ball.StaticRandomInt2;
    FrameCountOfEntireGame[1]++;
}

// .text:0x0005AE9C size:0x228 mapped:0x80699F30
void transferSomeValuesOnMatchLoad(void) {
    int teamNameHome;
    int teamNameAway;

    changeScene(4, 0);
    teamNameHome = Static_Stats_Tables.teamName[g_d_GameSettings.home_AwaySetting];
    teamNameAway = Static_Stats_Tables.teamName[g_d_GameSettings.home_AwaySetting ^ 1];
    g_GameLogic.framesOfExitingToMenu = 0;
    g_UnkSimulation_31AC0._04 = 0;
    g_UnkSimulation_31AC0._09 = 0;
    hugeAnimStruct[0x307E] = 0;
    g_d_GameSettings.minigamesEnabled = 0;
    g_d_GameSettings._13 = 0;
    g_d_GameSettings.someChallengeModeFlag = 0;
    hugeAnimStruct[0x307A] = 0;
    *(int*)&hugeAnimStruct[0x6C] = 0;
    hugeAnimStruct[0x307C] = 0;
    hugeAnimStruct[0x307D] = 0;
    animRelated[0xA4] = 0;
    g_d_GameSettings._55 = 0;
    g_d_GameSettings.challengeMinigame_baseCoinsEarned = 0;
    g_d_GameSettings.bJMatchRelated = 0;
    *(s16*)&hugeAnimStruct[0x2D44] = -1;
    *(s16*)&hugeAnimStruct[0x2D50] = -1;
    *(s16*)&hugeAnimStruct[0x2D5C] = -1;
    g_GameLogic.teams[0] = g_d_GameSettings.PlayerPorts[0];
    g_GameLogic.teams[1] = g_d_GameSettings.PlayerPorts[1] % 4;
    g_GameLogic.logo[0].ID = teamNameHome;
    g_GameLogic.logo[1].ID = teamNameAway;
    g_GameLogic.logo[0].variationID = teamNameHome % 4;
    g_GameLogic.logo[1].variationID = teamNameAway % 4;
    g_GameLogic.logo[0].captain = teamNameHome / 4;
    g_GameLogic.logo[1].captain = teamNameAway / 4;
    g_Scores.mercyThreshold = inningSetting.runsNeededForMercy;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD ||
        g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        g_d_GameSettings.minigamesEnabled = 1;
    }
    memset(&g_Minigame, 0, sizeof(g_Minigame));
    g_Minigame.GameMode_MiniGame = 0;
    sndVolume(0x7F, 0xA, 0xFF);
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD ||
        g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        hugeAnimStruct[0x2D7D] = 0;
        animRelated[0xD7] = 0;
        currentDrawingItem->func = fn_3_59F40;
    } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        currentDrawingItem->func = fn_3_59C2C;
    } else {
        currentDrawingItem->func = fn_3_5A28C;
    }
}

// .text:0x0005AE0C size:0x90 mapped:0x80699EA0
void fn_3_5AE0C(void) {
    resetInputTrackers();
    g_UnkSimulation_31AC0._08 = 0;
    g_UnkSimulation_31AC0._07 = 0;
    gameInitRelated();
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        toyFieldInit();
    } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        minigames_init();
    }
    g_Minigame._19AB = 0;
    fn_3_6C150();
    fn_3_8F1C8();
    currentDrawingItem->func = gameSimulationFunction;
}

// .text:0x0005ACA0 size:0x16C mapped:0x80699D34
void simulate1FrameOfTheGame(void) {
    if (g_GameLogic.framesOfExitingToMenu != 0) {
        exitToMenuControl();
        return;
    }
    if (g_GameLogic.FrameCountOfCurrentPitch < 0xFFFE) {
        g_GameLogic.FrameCountOfCurrentPitch++;
    } else {
        g_GameLogic.FrameCountOfCurrentPitch = 0xFFFF;
    }
    if (g_GameLogic.FrameCountOfCurrentAtBat_Copy < 0xFFFE) {
        g_GameLogic.FrameCountOfCurrentAtBat_Copy++;
    } else {
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0xFFFF;
    }
    UpdateRandomInts();
    UpdateControllerInputs();
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD &&
        g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES) {
        ReplayRelatedCopying_storeDataBeforePlay();
    }
    unsure_updateAnimations();
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        practiceSimulation();
    } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        toyfieldSimulation();
    } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        minigameSimulation();
    } else if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_NONE) {
        baseballMatchSimulation();
    }
    if (g_d_GameSettings.minigamesEnabled) {
        minigameAnimations();
    } else {
        matchAnimations();
    }
    spriteAnimations();
    if (hugeAnimStruct[0x3088] != 0) {
        hazardSimulationRelated();
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_DEMO && lbl_80366158[0x2A] == 0) {
        lbl_80366158[0x2A] = 1;
    }
}

// .text:0x0005A87C size:0x424 mapped:0x80699910
void gameInitRelated(void) {
    u32 mode;
    int home;
    int i;

    lbl_80366158[0x28] = 0;
    FrameCountOfEntireGame[0] = 0;
    FrameCountOfEntireGame[1] = 0;
    g_UnkSimulation_31AC0._00 = g_d_GameSettings.FrameCountWhileNotAtMainMenu;
    g_UnkSimulation_31AC0._05 = 0;
    g_UnkSimulation_31AC0._06 = 4;
    g_d_GameSettings.humanTeamNumber = 0;
    g_GameLogic._125 = 0;
    g_GameLogic.EventTriggers_EndOfGame = 0;
    g_GameLogic.exitingToMenu = 0;
    g_GameLogic.sceneID = SCENE_ID_0;
    g_GameLogic.EventTriggers_GameHasStarted = 0;
    g_GameLogic._124 = 0;
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    g_GameLogic.winType = WIN_TYPE_0;
    g_GameLogic._131[0] = 0;
    g_GameLogic._131[1] = 0;
    g_GameLogic._131[2] = 0;
    g_GameLogic._131[3] = 0;
    g_GameLogic.someCounter = -1;
    g_GameLogic.bOD_framesInLiveBallScene = -1;
    g_GameLogic.playOverFadeOutStarted = -1;
    g_GameLogic.PauseSimulationFrameCount = 0;
    g_Practice.practiceLevel = 0;
    lbl_3_common_bss_1323C[0] = lbl_3_common_bss_134C4;
    g_GameLogic.secondaryGameMode = SECONDARY_GAME_MODE_NONE;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        g_GameLogic.secondaryGameMode = SECONDARY_GAME_MODE_LOAD_PRACTICE_SCREEN;
    }
    fn_3_1CCC8();
    mode = g_d_GameSettings.GameModeSelected;
    g_Scores.inningLimit = inningSetting.inningCount;
    g_Scores.maxNumberOfExtraInnings = inningSetting.inningCount + 3;
    if (mode == GAME_TYPE_DEMO) {
        g_Scores.maxNumberOfExtraInnings = 5;
        g_Scores.inningLimit = 5;
    }
    home = g_d_GameSettings.home_AwaySetting;
    g_GameLogic.teamIsCPU[0] = 0;
    g_GameLogic._140[0] = 0;
    g_GameLogic.batterHandedness[0] = 0;
    g_GameLogic.teamAIInd[0] = 0;
    g_GameLogic.autoFielding[0] = 0;
    g_GameLogic.battingAIInd[0] = 0;
    g_GameLogic.teamIsCPU[1] = 0;
    g_GameLogic._140[1] = 0;
    g_GameLogic.batterHandedness[1] = 0;
    g_GameLogic.teamAIInd[1] = 0;
    g_GameLogic.autoFielding[1] = 0;
    g_GameLogic.battingAIInd[1] = 0;
    g_GameLogic.AIDifficulty0Special3Weak[0] = inningSetting.aiDifficulty;
    g_GameLogic.AIDifficulty0Special3Weak[1] = inningSetting.aiDifficulty;
    g_GameLogic.homeTeamBattingInd_fieldingTeam = 0;
    g_GameLogic.awayTeamBattingInd_battingTeam = 1;
    g_GameLogic.homeTeamInd = home;
    g_GameLogic.teamBatting = home;
    g_GameLogic.teamFielding = home ^ 1;
    g_GameLogic._1C[0] = g_d_GameSettings.maybeHomeAway[home];
    g_GameLogic._1C[1] = g_d_GameSettings.maybeHomeAway[home ^ 1];
    if (mode == GAME_TYPE_PRACTICE) {
        g_GameLogic.AIDifficulty0Special3Weak[home] = 1;
        g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamInd ^ 1] = 1;
    } else if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
        g_GameLogic.teamIsCPU[1] = 1;
        g_GameLogic._140[home ^ 1] = 1;
        lbl_3_common_bss_37400._40 = 0;
        g_GameLogic.batterHandedness[g_GameLogic.homeTeamInd ^ 1] = 1;
        g_GameLogic.teamAIInd[g_GameLogic.homeTeamInd ^ 1] = 1;
        g_GameLogic.autoFielding[g_GameLogic.homeTeamInd ^ 1] = 1;
        g_GameLogic.battingAIInd[g_GameLogic.homeTeamInd ^ 1] = 1;
        g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamInd] = 1;
    } else if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_UNKNOWN_3) {
        g_GameLogic.teamIsCPU[0] = 1;
        g_GameLogic._140[home] = 1;
        lbl_3_common_bss_37400._40 = 1;
        g_GameLogic.batterHandedness[g_GameLogic.homeTeamInd] = 1;
        g_GameLogic.teamAIInd[g_GameLogic.homeTeamInd] = 1;
        g_GameLogic.autoFielding[g_GameLogic.homeTeamInd] = 1;
        g_GameLogic.battingAIInd[g_GameLogic.homeTeamInd] = 1;
        g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamInd ^ 1] = 1;
    } else if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_UNKNOWN_2) {
        g_GameLogic.teamIsCPU[1] = 1;
        g_GameLogic.teamIsCPU[0] = 1;
        g_GameLogic._140[1] = 1;
        g_GameLogic._140[0] = 1;
        g_GameLogic.batterHandedness[1] = 1;
        g_GameLogic.batterHandedness[0] = 1;
        g_GameLogic.teamAIInd[1] = 1;
        g_GameLogic.teamAIInd[0] = 1;
        g_GameLogic.autoFielding[1] = 1;
        g_GameLogic.autoFielding[0] = 1;
        g_GameLogic.battingAIInd[1] = 1;
        g_GameLogic.battingAIInd[0] = 1;
    } else {
        g_GameLogic.AIDifficulty0Special3Weak[0] = 1;
        g_GameLogic.AIDifficulty0Special3Weak[1] = 1;
    }
    for (i = 0; i < 2; i++) {
        if (g_GameLogic.teamIsCPU[i] == 0) {
            if (inningSetting.controlOptions[g_GameLogic.teams[i]]._0 != 0) {
                g_GameLogic.batterHandedness[g_GameLogic.homeTeamInd ^ i] = 1;
            }
            if (inningSetting.controlOptions[g_GameLogic.teams[i]]._1 != 0) {
                g_GameLogic._140[g_GameLogic.homeTeamInd ^ i] = 1;
            }
            if (inningSetting.controlOptions[g_GameLogic.teams[i]].autoRunning != 0) {
                g_GameLogic.battingAIInd[g_GameLogic.homeTeamInd ^ i] = 1;
            }
            if (inningSetting.controlOptions[g_GameLogic.teams[i]].autoFielding != 0) {
                g_GameLogic.teamAIInd[g_GameLogic.homeTeamInd ^ i] = 1;
                g_GameLogic.autoFielding[g_GameLogic.homeTeamInd ^ i] = 1;
            }
        }
    }
    clearScoutState();
    initializeGame();
}

// .text:0x0005A6FC size:0x180 mapped:0x80699790
void exitToMenuControl(void) {
    switch (g_GameLogic.framesOfExitingToMenu) {
    case 1:
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE && g_d_GameSettings.bJMatchInd == 1) {
            g_d_GameSettings.home_AwaySetting ^= 1;
        }
        pauseAnimations();
        animRelated[0x96] = 1;
        if (g_d_GameSettings.minigamesEnabled) {
            cleanupCharacters();
            if (g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD) {
                cleanupMinigameResources();
            }
        } else {
            cleanupMinigameResources();
        }
        setNullPtrForStadiumObjs();
        fn_3_BC224();
        unregisterMatchHudObjects();
        resetGameStadiumStateOnExit();
        fn_3_902FC();
        transitionToReplay();
        g_d_GameSettings._55 = 1;
        g_GameLogic.framesOfExitingToMenu++;
        break;
    case 2:
        g_GameLogic.framesOfExitingToMenu++;
        break;
    case 0x1D:
        fn_3_90434();
        g_GameLogic.framesOfExitingToMenu++;
        break;
    case 0x1E:
        if (g_GameLogic.exitingToMenu != 0) {
            lbl_80366158[0x1C] = 2;
        } else {
            lbl_80366158[0x1C] = 1;
        }
        g_d_GameSettings.minigamesEnabled = 0;
        break;
    default:
        g_GameLogic.framesOfExitingToMenu++;
        break;
    }
}

#pragma dont_inline on

// .text:0x0005A6D4 size:0x28 mapped:0x80699768
void SetGameStatus(int status) {
    g_GameLogic.gameStatus_prev = g_GameLogic.gameStatus;
    g_GameLogic.FrameCountOfCurrentPitch = 0;
    g_GameLogic.gameStatus = status;
    g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
    g_GameLogic._125 = 0;
}

// .text:0x0005A6A0 size:0x34 mapped:0x80699734
void configureTeamsForGame_Unused(int arg0, int arg1, int arg2, int arg3) {
    int t = arg1 ^ arg0;

    g_GameLogic.homeTeamBattingInd_fieldingTeam = arg0;
    g_GameLogic.awayTeamBattingInd_battingTeam = arg0 ^ 1;
    g_GameLogic.homeTeamInd = arg1;
    g_GameLogic.teamBatting = t;
    g_GameLogic.teamFielding = t ^ 1;
    g_GameLogic._1C[0] = arg2;
    g_GameLogic._1C[1] = arg3;
}

// .text:0x0005A684 size:0x1C mapped:0x80699718
void resetCount(void) {
    g_Strikes.strikes = 0;
    g_Strikes.balls = 0;
    g_Strikes.outs = 0;
    g_Strikes.forcedOutToEndInningInd = 0;
}

#pragma dont_inline reset
