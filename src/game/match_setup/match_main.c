#define SQRT2_LINKAGE static
#include "game/match_setup/match_main.h"
#include "game/match_setup/match_flow.h"
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
#define REP_HEADER_DATA_FN getRepHeaderData_matchMain
#include "header_rep_data.h"

extern u32 FrameCountOfEntireGame[5];
extern u8 lbl_80366158[0x30];
extern UnkSimulationRelatedStruct g_UnkSimulation_31AC0;
extern u8 highLevelSimulationFlag[4];
extern u8 hugeAnimStruct[0x3154];
extern u8 animRelated[0x124];
extern void* lbl_3_common_bss_1323C[];
extern u8 lbl_3_common_bss_134C4[];

extern void unkPauseSimulationCheck(void);
extern void cleanupCharacters(void);
extern void fn_3_90434(void);
extern void unregisterMatchHudObjects(void);
extern void toyFieldInit(void);
extern void minigames_init(void);
extern void clearScoutState(void);
extern void practice_postGraphicsUpdate(void);
extern void fn_3_59C2C(void);
extern void fn_3_59F40(void);
extern void fn_3_5A28C(void);
extern void UpdateRandomInts(void);
extern void practiceSimulation(void);
extern void toyfieldSimulation(void);
extern void minigameSimulation(void);
extern void graphicsFunction_minigames(void);

// .text:0x0005B0C4 size:0x15C mapped:0x8069A158
void gameSimulationFunction(void) {
    g_d_GameSettings.FrameCountWhileNotAtMainMenu++;
    lbl_80366158[0x28] = 0;
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
            practice_postGraphicsUpdate();
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
    changeScene(4, 0);
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
    g_GameLogic.logo[0].ID = Static_Stats_Tables.teamName[g_d_GameSettings.home_AwaySetting];
    g_GameLogic.logo[1].ID = Static_Stats_Tables.teamName[g_d_GameSettings.home_AwaySetting ^ 1];
    g_GameLogic.logo[0].variationID = g_GameLogic.logo[0].ID % 4;
    g_GameLogic.logo[1].variationID = g_GameLogic.logo[1].ID % 4;
    g_GameLogic.logo[0].captain = g_GameLogic.logo[0].ID / 4;
    g_GameLogic.logo[1].captain = g_GameLogic.logo[1].ID / 4;
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
    int home;
    u32 mode;
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
    for (i = 0; i < TEAMS_PER_GAME; i++) {
        g_GameLogic.teamIsCPU[i] = 0;
        g_GameLogic.pitcherAIInd[i] = 0;
        g_GameLogic.batterAIInd[i] = 0;
        g_GameLogic.teamAIInd[i] = 0;
        g_GameLogic.autoFielding[i] = 0;
        g_GameLogic.autoRunningInd[i] = 0;
    }
    home = g_d_GameSettings.home_AwaySetting;
    g_GameLogic.AIDifficulty0Special3Weak[0] = inningSetting.aiDifficulty;
    g_GameLogic.AIDifficulty0Special3Weak[1] = inningSetting.aiDifficulty;
    configureTeamsForGame_Unused(0, home, g_d_GameSettings.maybeHomeAway[g_d_GameSettings.home_AwaySetting],
                                 g_d_GameSettings.maybeHomeAway[g_d_GameSettings.home_AwaySetting ^ 1]);
    if (mode == GAME_TYPE_PRACTICE) {
        g_GameLogic.AIDifficulty0Special3Weak[home] = 1;
        g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamInd ^ 1] = 1;
    } else if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
        g_GameLogic.teamIsCPU[1] = 1;
        g_GameLogic.pitcherAIInd[home ^ 1] = 1;
        g_GameLogic.batterAIInd[g_GameLogic.homeTeamInd ^ 1] = 1;
        scoutState.humanTeam = 0;
        g_GameLogic.teamAIInd[g_GameLogic.homeTeamInd ^ 1] = 1;
        g_GameLogic.autoFielding[g_GameLogic.homeTeamInd ^ 1] = 1;
        g_GameLogic.autoRunningInd[g_GameLogic.homeTeamInd ^ 1] = 1;
        g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamInd] = 1;
    } else if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_UNKNOWN_3) {
        g_GameLogic.teamIsCPU[0] = 1;
        g_GameLogic.pitcherAIInd[home] = 1;
        g_GameLogic.batterAIInd[g_GameLogic.homeTeamInd] = 1;
        scoutState.humanTeam = 1;
        g_GameLogic.teamAIInd[g_GameLogic.homeTeamInd] = 1;
        g_GameLogic.autoFielding[g_GameLogic.homeTeamInd] = 1;
        g_GameLogic.autoRunningInd[g_GameLogic.homeTeamInd] = 1;
        g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamInd ^ 1] = 1;
    } else if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_UNKNOWN_2) {
        g_GameLogic.teamIsCPU[1] = 1;
        g_GameLogic.teamIsCPU[0] = 1;
        g_GameLogic.pitcherAIInd[1] = 1;
        g_GameLogic.pitcherAIInd[0] = 1;
        g_GameLogic.batterAIInd[1] = 1;
        g_GameLogic.batterAIInd[0] = 1;
        g_GameLogic.teamAIInd[1] = 1;
        g_GameLogic.teamAIInd[0] = 1;
        g_GameLogic.autoFielding[1] = 1;
        g_GameLogic.autoFielding[0] = 1;
        g_GameLogic.autoRunningInd[1] = 1;
        g_GameLogic.autoRunningInd[0] = 1;
    } else {
        g_GameLogic.AIDifficulty0Special3Weak[0] = 1;
        g_GameLogic.AIDifficulty0Special3Weak[1] = 1;
    }
    for (i = 0; i < TEAMS_PER_GAME; i++) {
        if (g_GameLogic.teamIsCPU[i] == 0) {
            if (inningSetting.controlOptions[g_GameLogic.teams[i]]._0 != 0) {
                g_GameLogic.batterAIInd[g_GameLogic.homeTeamInd ^ i] = 1;
            }
            if (inningSetting.controlOptions[g_GameLogic.teams[i]]._1 != 0) {
                g_GameLogic.pitcherAIInd[g_GameLogic.homeTeamInd ^ i] = 1;
            }
            if (inningSetting.controlOptions[g_GameLogic.teams[i]].autoRunning != 0) {
                g_GameLogic.autoRunningInd[g_GameLogic.homeTeamInd ^ i] = 1;
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
        g_GameLogic.framesOfExitingToMenu++;
        g_d_GameSettings._55 = 1;
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
    g_GameLogic.homeTeamBattingInd_fieldingTeam = arg0;
    g_GameLogic.awayTeamBattingInd_battingTeam = arg0 ^ 1;
    g_GameLogic.homeTeamInd = arg1;
    g_GameLogic.teamBatting = arg1 ^ arg0;
    g_GameLogic.teamFielding = g_GameLogic.teamBatting ^ 1;
    g_GameLogic._1C[0] = arg2;
    g_GameLogic._1C[1] = arg3;
}

// .text:0x0005A684 size:0x1C mapped:0x80699718
void resetCount(void) {
    g_BallsStrikesOuts.strikes = 0;
    g_BallsStrikesOuts.balls = 0;
    g_BallsStrikesOuts.outs = 0;
    g_BallsStrikesOuts.forcedOutToEndInningInd = 0;
}
