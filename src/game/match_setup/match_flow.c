#define SQRT2_LINKAGE static
#include "game/match_setup/match_flow.h"
#include "game/match_setup/match_main.h"
#include "game/match_setup/match_end.h"
#include "game/challenge/scout_state.h"
#include "mem.h"
#include "Dolphin/rand.h"
#include "game/replay/replay_inputs.h"
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
#include "game/replay/replay_state.h"
#include "game/stats/result_stats.h"
#include "game/match_setup/roster_init.h"
#include "game/stats/stat_tracking.h"
#include "game/match_setup/transition_init.h"
#include "game/match_setup/versus_screens.h"
#include "game/math/game_math.h"
#include "game/pitching/pitcher.h"
#include "game/pitching/pitcher_stamina.h"
#include "game/sound/m_sound.h"
#include "game/stadium/stadium_framework.h"
#include "musyx/musyx.h"
#include "Unknown/File_0x8004abd8.h"
#include "challenge/challenge_progress.h"
#include "Unknown/File_0x8001e460.h"
#include "Unknown/File_0x8001f228.h"
#include "Unknown/File_0x800204cc.h"
#include "Unknown/File_0x80035838.h"
#include "Unknown/File_0x80062a50.h"
#include "Unknown/File_0x800a7568.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x800203e0.h"
#include "Unknown/File_0x80014d4c.h"
#include "Unknown/File_0x80014e50.h"
#include "Unknown/File_0x80014f40.h"
#include "game/match_setup/pause_menu.h"
#define REP_HEADER_DATA_FN getRepHeaderData_matchFlow
#include "header_rep_data.h"
#include "game/stadium/stadium_draw.h"

extern UnkSimulationRelatedStruct g_UnkSimulation_31AC0;
extern u8 highLevelSimulationFlag[4];
extern u8 hugeAnimStruct[0x3154];
extern u8 animRelated[0x124];
extern void* lbl_3_common_bss_1323C[];

extern void QueueTextToDisplay(int code, int arg1);
extern void initializeSomethingDuringTransition(void);
extern int fn_3_59BCC(int arg0);
extern u8 challengeTransitionPortraitIDs[];
extern u8 lbl_8037169C[];
extern int fn_3_FD9FC(void);
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern int championshipScreenGraphics(void);
extern void recruitWholeTeamAfterMercy(void);
extern void matchTransitionFunction2(void);
extern int loadRunnerActors(void);
extern void betweenABSetPitcherBatter(void);
extern void someRosterMemoryManagement(void);
extern void setPausedTo0AndOtherStateVars(void);
extern void drawStadium(void);
extern void possiblyTransitionBlackScreen(void);
extern void initializeAIConstants(void);
extern void initializeAnimations(void);
extern void fn_3_AF5A4(void);
extern u8 lbl_3_data_60F0;
extern void fn_3_90AB0(int);
extern int fn_3_90C14(int);
extern void fn_8002024C(void);
extern void handleDVDCancelAndARQRemoval(void);
extern int practice_checkForPause(void);
extern void match_checkForPause(void);
extern void transitionToPauseScreen(void);
extern void ballPhysics(void);
extern void fielderMainFunction(void);
extern void scoutFlag_checkMissionSuccess(void);
extern void resetScoutChanceTier(void);
extern int loadFielderActors(int charID);
extern BOOL checkForButtonPressToSkip(int a, int b);
extern void playOverSounds(long frames);
extern void challenge_leftoverTeammatesJoinBowserJr(void);

// .text:0x0006011C size:0x64C mapped:0x8069F1B0
void baseballMatchSimulation(void) {
    s16 loadIndex;

    g_GameLogic.hudElementLoadingInd = 0;
    g_GameLogic.hudLoadingRelated = 0;
    if (g_Ball.totalFramesAtPlay < 0x7FFE) {
        g_Ball.totalFramesAtPlay++;
    } else {
        g_Ball.totalFramesAtPlay = 0x7FFF;
    }
    if (g_BallsStrikesOuts.outs >= 3) {
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
            if (pauseControl.isPaused == 0) {
                loadIndex = *(s16*)&animRelated[0x9E];
                if (loadIndex >= 0) {
                    if (loadBatterModelFromDisk(loadIndex)) {
                        *(s16*)&animRelated[0x9E] = -1;
                    }
                } else {
                    loadIndex = *(s16*)&animRelated[0xA0];
                    if (loadIndex >= 0) {
                        if (loadSomethingFromDiskAtBeginningOfAB1(loadIndex)) {
                            *(s16*)&animRelated[0xA0] = -1;
                        }
                    } else {
                        loadIndex = *(s16*)&animRelated[0xA2];
                        if (loadIndex >= 0) {
                            if (loadSomethingFromDiskAtBeginningOfAB2(loadIndex)) {
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
    running_resetLeadoffDefaults();
    initializeAIConstants();
    initializeStats();
    initializeInningTrackers();
    initializeReplayVariables();
    initializeSounds();
    initializeAnimations();
    initializeSoundEmitters();
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
            if (state == 1 || state >= 8 || g_GameLogic.framesInGameStatus_copy == 1) {
                changeScene(3, 6);
                if (g_GameLogic.framesInGameStatus_copy == 1) {
                    g_GameLogic.framesInGameStatus_copy = 0;
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
        g_GameLogic.framesInGameStatus_copy = 0;
        g_GameLogic._125 = 1;
        changeScene(0xD, 6);
        animRelated[0x9A] = 0;
        animRelated[0x9C] = 0;
        highLevelSimulationFlag[2] = 0;
        highLevelSimulationFlag[3] = 0;
        hugeAnimStruct[0x2D77] = 0;
        hugeAnimStruct[0x2D7B] = 0;
        hugeAnimStruct[0x2D7C] = 0;
        break;
    case 1:
        if (fn_3_59BCC(g_GameLogic.framesInGameStatus_copy) != 0) {
            g_GameLogic._125 = 2;
            g_GameLogic.framesInGameStatus_copy = 0;
            hugeAnimStruct[0x2D77] = 0;
            if (animRelated[0xA4] != 0) {
                fn_8002024C();
            }
        }
        break;
    case 2:
        if (loadPitcherActor() != 0) {
            g_GameLogic.framesInGameStatus_copy = 0;
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
            g_GameLogic.framesInGameStatus_copy = 0;
            hugeAnimStruct[0x3081] = 0;
            g_GameLogic._125 = 6;
        }
        break;
    case 6:
        if (loadRunnerActors() != 0) {
            g_GameLogic.framesInGameStatus_copy = 0;
            g_GameLogic._125 = 7;
        }
        break;
    case 7:
        if (someAnimationIndFunction() != 0) {
            g_GameLogic.framesInGameStatus_copy = 0;
            g_GameLogic._125 = 8;
        }
        break;
    case 8:
        if (g_GameLogic.framesInGameStatus >= 0xF0) {
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_DEMO ||
                g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_CPU_VS_CPU) {
                g_GameLogic._125 = 9;
            } else if (checkForButtonPressToSkip(1, INPUT_BUTTON_START | INPUT_BUTTON_B | INPUT_BUTTON_A)) {
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
    running_resetRunners();
    someRosterMemoryManagement();
    setPausedTo0AndOtherStateVars();
    setInningEndingKIndTo0();
    resetGameControlVars_duringNewInning();
    setBatterContactConstants();
    running_initRunner();
    intializeRunnersDuringTransition();
    betweenABSetPitcherBatter();
    initializeSomethingDuringTransition2();
    g_BallsStrikesOuts.strikes = 0;
    g_BallsStrikesOuts.balls = 0;
    g_BallsStrikesOuts._1E = -1;
    g_BallsStrikesOuts.stateRelated = 0;
    g_GameLogic.frameCountdownAtBeginningOfAtBatLockout = 0x5A;
    g_GameLogic._13D = 0;
}

// .text:0x0005F720 size:0x88 mapped:0x8069E7B4
void practiceNewBatter(void) {
    setDefaultInMemBall();
    setDefaultInMemPitcher();
    setDefaultInMemBatter();
    running_setDefaultRunners();
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
        running_initRunner();
        running_setDefaultRunners();
        initializeMiniGameCharacters();
        betweenABSetPitcherBatter();
        intializeRunnersDuringTransition();
        initializeSomethingDuringTransition();
        initializeSomethingDuringTransition2();
        g_BallsStrikesOuts.strikes = 0;
        g_BallsStrikesOuts.balls = 0;
        g_BallsStrikesOuts._1E = -1;
        g_BallsStrikesOuts.stateRelated = 0;
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
        g_GameLogic.framesInGameStatus_copy = 0;
        g_GameLogic._125++;
    case 3:
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_Practice.practiceLevel == 7) {
            if (g_GameLogic.framesInGameStatus_copy == 0) {
                fn_3_90AB0(g_Practice.someCharID2);
                g_Practice.someCharID2 =
                    inMemRoster[g_GameLogic.teamBatting][g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam] - 1]
                        .stats.CharID;
                sound_crowd_EffectsStruct._2C = 0;
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
        cpuCheckPitcherRelief();
        g_GameLogic.IsStarChance = 0;
        animRelated[0xAC] = 0;
        if (inningSetting.starSkillsSetting != 0) {
            if (!g_d_GameSettings.exhibitionMatchInd) {
                if (scoutState.scoutMissionID != SCOUT_MISSION_NONE) {
                    break;
                }
            }
            if (g_GameLogic.TeamStars[0] >= 5 && g_GameLogic.TeamStars[1] >= 5) {
                break;
            }
            if ((g_RunningLogic.runnersAtStartOfPlayMask & 0xFFF0) != 0) {
                break;
            }
            if (RandomInt_Sim(100) < lbl_3_data_60F0) {
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

    practiceNewBatter();
    g_Scores.rbisWaitingToBeAddedToScore = 0;
    g_Scores._9E = g_Scores.scores[g_Scores.halfInning].byInning[g_Scores.Inning - 1];
    g_Scores._A2 = g_Scores._A0;
    diff = g_Scores.scores[0].total - g_Scores.scores[1].total;
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
    g_Scores._A6 = __abs(diff);
    g_BallsStrikesOuts.storedOuts = g_BallsStrikesOuts.outs;
    g_BallsStrikesOuts.runnerIndexForEachOutThisPitch[0] = -1;
    g_BallsStrikesOuts.runnerIndexForEachOutThisPitch[1] = -1;
    g_BallsStrikesOuts.runnerIndexForEachOutThisPitch[2] = -1;
    g_BallsStrikesOuts.GameControls_StrikeBallBitVector = g_BallsStrikesOuts.balls + g_BallsStrikesOuts.strikes * 16;
    g_BallsStrikesOuts.howRunnerReachedBase = 0;
    g_Ball.totalFramesAtPlay = 0;
    g_FieldingLogic.playOverInd = 0;
    g_FieldingLogic.framesSincePlayEnded = 0;
    g_FieldingLogic.unused_always0__ = 0;
    g_FieldingLogic.hasProcessedFoulBall = 0;
    g_FieldingLogic.canEndPlayOnLooseBallInd = 0;
    g_FieldingLogic.always0__ = 0;
    g_FieldingLogic.framesSince3rdOutWasMade = 0;
    g_RunningLogic._13 = 0;
    pauseControl.isPaused = 0;
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
        if (pauseControl.isPaused != 0) {
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
    running_main();
    processScoreChanges(0);
    if (g_GameLogic.freeFieldingPracticeInd == 0) {
        if (g_BallsStrikesOuts.outs >= 3 || (g_BallsStrikesOuts.storedOuts == 2 && g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT)) {
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
        running_transferRunnerToNextIndex();
        iterateBatter(g_GameLogic.homeTeamBattingInd_fieldingTeam);
    } else if (g_GameLogic.EventTriggers_EndOfGame != 0) {
        if (!g_d_GameSettings.exhibitionMatchInd) {
            if (g_GameLogic.homeTeamInd ^ (g_Scores.winnerCd == g_d_GameSettings.humanTeamNumber)) {
                challenge_checkRecruitment();
            }
        }
    } else if (g_BallsStrikesOuts.outs >= 3) {
        if (g_FieldingLogic.liveBallReason < PICKOFF_STEAL_CODE_PICKOFF ||
            g_FieldingLogic.liveBallReason > PICKOFF_STEAL_CODE_UNUSED_3 || g_BallsStrikesOuts.balls >= 4) {
            iterateBatter(g_GameLogic.homeTeamBattingInd_fieldingTeam);
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
            if (g_Practice.practiceLevel == 7 || g_Practice.practiceLevel == 6) {
                running_transferRunnerToNextIndex();
            }
        }
    } else {
        running_transferRunnerToNextIndex();
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
    ballPhysics();
    fielderMainFunction();
    running_main();
    if (g_Ball.deadBallReason != DEAD_BALL_REASON_NONE) {
        handleDeadBall();
    }
    processScoreChanges(0);
    checkIfPlayOver();
    if (g_GameLogic.freeFieldingPracticeInd == 0) {
        midPlay_trackStats();
        if (g_BallsStrikesOuts.outs >= 3) {
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

    if (g_FieldingLogic.liveBallReason == PICKOFF_STEAL_CODE_NONE &&
        g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR && g_Ball.deadBallReason == DEAD_BALL_REASON_NONE) {
        g_FieldingLogic.playOverCounter = 0;
        return;
    }
    if (g_FieldingLogic.canEndPlayOnLooseBallInd != 0 && animRelated[0xB1] == 0) {
        if (g_BallsStrikesOuts.outs < 3 && g_RunningLogic.runnersOnFieldMask != 0) {
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
        if (g_Runners[i].runnerStatus == RUNNER_STATUS_ON_FIELD) {
            if (g_Runners[i].baseStandingOn < 0) {
                allRunnersDone = 0;
            } else if (g_Runners[i].runningDirectionCode == RUNNER_MOVEMENT_FORWARDS && g_Runners[i].overrun1BStage == OVERRUN_STAGE_NONE) {
                allRunnersDone = 0;
            } else if (g_Runners[i].baseStandingOn != g_Runners[i].currentBase) {
                allRunnersDone = 0;
            }
            if (g_Runners[i].tagUpStatus == TAG_UP_TYPE_MUST_RETURN) {
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
    } else if (g_BallsStrikesOuts.outs >= 3) {
        endFrame = 0x78;
    } else if (count == 0 && g_Ball.deadBallReason != DEAD_BALL_REASON_HOME_RUN && g_Ball.ballInitialHitDoneInd != 0 &&
               g_Ball.ballState != 0) {
        endFrame = 0x78;
    } else if (g_Ball.deadBallReason != DEAD_BALL_REASON_NONE) {
        if (g_Ball.deadBallReason == DEAD_BALL_REASON_GROUND_RULE_DOUBLE || g_Ball.deadBallReason == DEAD_BALL_REASON_BALL_DEAD) {
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
                g_Runners[0].runnerStatus != RUNNER_STATUS_SCORED_DURING_PLAY) {
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
    if (!g_d_GameSettings.exhibitionMatchInd && scoutState.scoutMissionID != SCOUT_MISSION_NONE && g_Stats.replayInd == 0 &&
        g_GameLogic.playOver != 0 && g_Ball.deadBallReason != DEAD_BALL_REASON_HOME_RUN) {
        scoutState.scoutCountdown--;
        if (g_FieldingLogic.playOverCounter >= endFrame || scoutState.scoutCountdown <= 5) {
            lastPlayStats();
        }
        if (scoutState.scoutCountdown == 5 && g_Ball.deadBallReason != DEAD_BALL_REASON_HOME_RUN) {
            g_GameLogic.walkOffWinInd = 1;
            changeScene(3, 6);
            if (scoutState.scoutResult != SCOUT_RESULT_PENDING) {
                playOverSounds(6);
            }
        }
        if (scoutState.scoutCountdown <= 0) {
            playOverTransitionStuff();
        }
        if (g_Ball.deadBallReason != DEAD_BALL_REASON_HOME_RUN && g_Stats.replayPending != 0 &&
            scoutState.scoutCountdown == 0x1E) {
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
        } else if (g_FieldingLogic.liveBallReason != PICKOFF_STEAL_CODE_NONE &&
                   g_FieldingLogic.liveBallReason != PICKOFF_STEAL_CODE_UNUSED_4 && g_Pitcher.strikeOutOrWalk == 0) {
            showReplay = 0;
            if (g_BallsStrikesOuts.outs < g_BallsStrikesOuts.storedOuts) {
                g_GameLogic.playOver = 0;
            }
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

                if (g_BallsStrikesOuts.outs > g_BallsStrikesOuts.storedOuts) {
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
        if (!g_d_GameSettings.exhibitionMatchInd && scoutState.scoutMissionID != SCOUT_MISSION_NONE &&
            g_Stats.replayInd == 0 && g_GameLogic.playOver != 0) {
            scoutFlag_checkMissionSuccess();
            if (g_Ball.deadBallReason != DEAD_BALL_REASON_HOME_RUN) {
                scoutState.scoutCountdown = 0x78;
            }
            if (scoutState.scoutFlag == 0) {
                if (g_FieldingLogic.liveBallReason == PICKOFF_STEAL_CODE_NONE) {
                    animRelated[0xB4] = 1;
                } else if (g_BallsStrikesOuts.outs >= 3 || scoutState.scoutResult != SCOUT_RESULT_PENDING) {
                    animRelated[0xB4] = 1;
                } else {
                    scoutState.scoutCountdown = 8;
                }
            } else if (g_Stats.replayPending != 0) {
                scoutState.scoutCountdown = endFrame - 0x4C;
            } else {
                scoutState.scoutCountdown = 8;
            }
        }
        g_Stats._003B = 1;
    } else if (g_FieldingLogic.playOverCounter - 1 == endFrame - 0x1E) {
        if (scoutState.scoutResult == SCOUT_RESULT_PENDING && g_Ball.deadBallReason != DEAD_BALL_REASON_HOME_RUN &&
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
    if (g_FieldingLogic.liveBallReason != PICKOFF_STEAL_CODE_NONE && g_BallsStrikesOuts.outs < 3 &&
        g_GameLogic.EventTriggers_EndOfGame == 0) {
        didTransition = handleABEndEvent();
    }
    postPlayTrackStats();
    if (!g_d_GameSettings.exhibitionMatchInd && scoutState.scoutResult != SCOUT_RESULT_PENDING) {
        scoutState.scoutMissionID = SCOUT_MISSION_NONE;
        scoutState.scoutResult = SCOUT_RESULT_PENDING;
    }
    if (g_GameLogic.EventTriggers_EndOfGame != 0) {
        SetGameStatus(GAME_STATUS_TRANSITION);
        didTransition = 1;
    } else if (g_BallsStrikesOuts.outs >= 3) {
        SetGameStatus(GAME_STATUS_TRANSITION);
        if (g_FieldingLogic.liveBallReason >= PICKOFF_STEAL_CODE_PICKOFF &&
            g_FieldingLogic.liveBallReason <= PICKOFF_STEAL_CODE_UNUSED_3 && g_BallsStrikesOuts.balls < 4 && g_BallsStrikesOuts.strikes < 3) {
            if (g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam] == 1) {
                storedInningInfo._44[g_GameLogic.homeTeamBattingInd_fieldingTeam]--;
            }
        } else {
            iterateBatter(g_GameLogic.homeTeamBattingInd_fieldingTeam);
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
            if (g_Practice.practiceLevel == 7 || g_Practice.practiceLevel == 6) {
                running_transferRunnerToNextIndex();
            }
        }
        didTransition = 1;
    } else if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FOUL && g_Ball.maybebuntOn2Strikes == 0) {
        running_resetRunnersAfterFoulBall();
        SetGameStatus(GAME_STATUS_DEFAULT);
        didTransition = 1;
    } else if (g_FieldingLogic.liveBallReason != PICKOFF_STEAL_CODE_NONE &&
               g_FieldingLogic.liveBallReason != PICKOFF_STEAL_CODE_UNUSED_4) {
        running_transferRunnerToNextIndex();
        if (didTransition != 0) {
            iterateBatter(g_GameLogic.homeTeamBattingInd_fieldingTeam);
            SetGameStatus(GAME_STATUS_TRANSITION);
            didTransition = 1;
        } else {
            SetGameStatus(GAME_STATUS_0xA);
            didTransition = 1;
        }
    } else {
        running_transferRunnerToNextIndex();
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

    if (g_Ball.deadBallRBIsAddedInd != 0) {
        return;
    }
    if (g_Ball.deadBallReason == DEAD_BALL_REASON_GROUND_RULE_DOUBLE) {
        if (g_Runners[2].runnerStatus != RUNNER_STATUS_NONE) {
            g_Runners[2].scoredOnGRD = 1;
            count = 1;
        }
        if (g_Runners[3].runnerStatus != RUNNER_STATUS_NONE) {
            g_Runners[3].scoredOnGRD = 1;
            count++;
        }
        if (g_Scores.Inning >= g_Scores.inningLimit && g_Scores.halfInning != 0 &&
            g_Scores.scores[0].total == g_Scores._9E && count == 2) {
            g_Runners[2].scoredOnGRD = 0;
            count = 1;
        }
        g_Scores.scores[g_Scores.halfInning].byInning[g_Scores.Inning - 1] = g_Scores._9E;
        g_Ball.deadBallRBIsAddedInd = 1;
        storedInningInfo.rbisWaitingToBeAddedToScore = count;
        g_Scores.rbisWaitingToBeAddedToScore = count;
        if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR) {
            g_Ball.AtBat_ContactResult = BALL_RESULT_TYPE_LANDED;
        }
    } else if (g_Ball.deadBallReason == DEAD_BALL_REASON_BALL_DEAD) {
        for (i = 3; i >= 0; i--) {
            if (g_Runners[i].runnerStatus == RUNNER_STATUS_ON_FIELD &&
                (i >= 2 || g_Runners[i].baseReachedAtTimeOfThrow >= 2)) {
                g_Runners[i].scoredOnGRD = 1;
                count++;
            }
            if (g_Scores.Inning >= g_Scores.inningLimit && g_Scores.halfInning != 0 &&
                g_Scores.scores[0].total < g_Scores.scores[1].total + count) {
                break;
            }
        }
        g_Scores.rbisWaitingToBeAddedToScore = count;
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
            if (g_GameLogic.homeTeamInd ^ (g_Scores.winnerCd == g_d_GameSettings.humanTeamNumber)) {
                if (g_d_GameSettings.bJMatchInd != 1 ||
                    (g_GameLogic.homeTeamInd ^ (g_Scores.winnerCd != g_d_GameSettings.humanTeamNumber)) == 0) {
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
        (FrameCountOfEntireGame.frameCount >= 0x2A30 || g_UnkSimulation_31AC0._08 != 0)) {
        g_GameLogic.framesOfExitingToMenu = 1;
    } else if (g_GameLogic.EventTriggers_EndOfGame != 0) {
        fn_3_5D9F8();
    } else if (g_BallsStrikesOuts.outs >= 3) {
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
        animRelated[0x9B] = 0;
        animRelated[0x9C] = 0;
        highLevelSimulationFlag[3] = 0;
        hugeAnimStruct[0x3087] = 0;
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
        if (g_GameLogic.framesInGameStatus >= 0x78) {
            if (checkForButtonPressToSkip(1, INPUT_BUTTON_START | INPUT_BUTTON_B | INPUT_BUTTON_A)) {
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
    running_resetRunners();
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
    g_RunningLogic.runnersAtStartOfPlayMask = 0;
    g_Scores._pad_AC = evaluateInningCondition(g_Scores.Inning);
    g_Scores._pad_BF[2] = 0;
    g_Scores._C6 = 0;
    scoutState.scoutFlag = 0;
    setInningEndingKIndTo0();
    if (!settings->exhibitionMatchInd) {
        resetScoutChanceTier();
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
            if (g_Scores.halfInning == 0) {
                return;
            }
            if (g_Scores.mercyThreshold == 0) {
                return;
            }
            if (g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total -
                    g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total <
                g_Scores.mercyThreshold) {
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
    challenge_onGameEnd();
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
void challenge_onGameEnd(void) {
    ChallengeState* tracker = &g_Challenge;
    int a = tracker->captain;
    int b = tracker->opponentCaptain;

    if (!g_d_GameSettings.exhibitionMatchInd) {
        if (g_Scores.winnerCd <= 1) {
            if (g_Scores.winnerCd ^ (g_GameLogic.homeTeamInd == scoutState.humanTeam)) {
                if ((tracker->stage >= 4 && b == CHALLENGE_CAPTAIN_BOWSER) ||
                    (tracker->stage >= 5 && (int)tracker->_44EF == 1 && a == CHALLENGE_CAPTAIN_BOWSER)) {
                    g_GameLogic.playOverFadeOutStarted = 0;
                }
                challenge_leftoverTeammatesJoinBowserJr();
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
        if (g_GameLogic.framesInGameStatus >= 0x28) {
            if (checkForButtonPressToSkip(1, INPUT_BUTTON_START | INPUT_BUTTON_B | INPUT_BUTTON_A)) {
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
                0xC, challengeTransitionPortraitIDs[g_Challenge.captain]);
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
        running_initRunner();
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
    s32 i;
    int diff;

    if (!((g_Pitcher.strikeOutOrWalk == AT_BAT_END_WALK || g_Pitcher.strikeOutOrWalk == AT_BAT_END_HIT_BY_PITCH) &&
          g_Scores.rbisWaitingToBeAddedToScore > 0)) {
        if (g_GameLogic.gameStatus != GAME_STATUS_AT_BAT && g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
            return;
        }
        if (g_Scores.rbisWaitingToBeAddedToScore <= 0) {
            return;
        }
        if (g_BallsStrikesOuts.outs >= 3 && arg0 != 1) {
            return;
        }
        if (g_Stats.replayInd != 0 && g_Ball.deadBallReason == DEAD_BALL_REASON_HOME_RUN) {
            return;
        }
        if (g_Scores.Inning >= g_Scores.inningLimit && g_Scores.halfInning != 0 &&
            g_Ball.deadBallReason == DEAD_BALL_REASON_NONE) {
            int homeTotal = g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total;
            int awayTotal = g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total + 1;

            if (homeTotal + g_Scores.rbisWaitingToBeAddedToScore > awayTotal) {
                g_Scores.rbisWaitingToBeAddedToScore = awayTotal - homeTotal;
            }
            if (g_Scores.rbisWaitingToBeAddedToScore < 0) {
                g_Scores.rbisWaitingToBeAddedToScore = 0;
            }
        }
        if (g_FieldingLogic.liveBallReason == PICKOFF_STEAL_CODE_NONE) {
            if (g_Ball.ballInitialHitDoneInd == 0) {
                return;
            }
            if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR || g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FOUL) {
                return;
            }
        }
        for (i = 0; i < 4; i++) {
            if (g_Runners[i].runnerStatus == RUNNER_STATUS_ON_FIELD && g_Runners[i].forceOutCd == 1) {
                runnersOut++;
            }
        }
        if (g_Ball.deadBallReason == DEAD_BALL_REASON_NONE) {
            if (g_BallsStrikesOuts.outs >= 3) {
                if (g_BallsStrikesOuts.forcedOutToEndInningInd == 1) {
                    return;
                }
                if (g_BallsStrikesOuts.storedOuts == 2 && g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT) {
                    return;
                }
            } else if (g_BallsStrikesOuts.outs + runnersOut >= 3) {
                return;
            }
        }
    }
    if (g_Ball.deadBallReason != DEAD_BALL_REASON_GROUND_RULE_DOUBLE) {
        for (i = 0; i < 4; i++) {
            if (g_Runners[i].isEligibleToScore != 0 && g_Runners[i].runnerStatus == RUNNER_STATUS_SCORED_DURING_PLAY) {
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
        g_Scores.scores[g_Scores.halfInning].byInning[g_Scores.Inning - 1] += g_Scores.rbisWaitingToBeAddedToScore;
        g_Scores._C2 += g_Scores.rbisWaitingToBeAddedToScore;
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
    g_Scores.rbisWaitingToBeAddedToScore = 0;
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
    g_FieldingLogic.liveBallReason = arg0 + 1;
    g_FieldingLogic.throwSpeedType = 3;
    SetGameStatus(GAME_STATUS_LIVE_BALL);
    g_FieldingLogic.playOverCounter = 0;
    g_Pitcher.peachDaisyStarAnimationOn = 0;
    stealSetFielders();
    running_cancelLeadoffs();
    if (g_BallsStrikesOuts.balls >= 4) {
        g_Runners[0].runnerStatus = RUNNER_STATUS_WALK_WHILE_STEALING;
    } else {
        g_Runners[0].runnerStatus = RUNNER_STATUS_SCORED_DEAD_BALL;
    }
}

// .text:0x0005C5C8 size:0xD4 mapped:0x8069B65C
void uncalledRunnerUpdateRelated(void) {
    int i;

    for (i = 0; i < 4; i++) {
        if (g_Runners[i].runnerStatus == RUNNER_STATUS_ON_FIELD ||
            g_Runners[i].runnerStatus == RUNNER_STATUS_SCORED_DURING_PLAY ||
            g_Runners[i].runnerStatus == RUNNER_STATUS_SCORED_DEAD_BALL) {
            g_Scores.rbisWaitingToBeAddedToScore++;
            g_Runners[i].runnerStatus = RUNNER_STATUS_SCORED_DURING_PLAY;
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
