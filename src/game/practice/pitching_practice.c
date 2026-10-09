#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_pitchingPractice
#include "game/practice/pitching_practice.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/practice/guided_practice.h"
#include "game/practice/practice_menu.h"
#include "game/match_setup/match_flow.h"
#include "game/match_setup/transition_init.h"
#include "game/animation/animation_dispatch.h"
#include "game/ball/ball_physics.h"
#include "game/match_setup/at_bat_setup.h"
#include "game/match_setup/match_loading.h"
#include "game/pitching/pitcher.h"
#include "game/pitching/pitcher_stamina.h"
#include "game/batting/batter.h"
#include "game/baserunning/runner.h"
#include "game/fielding/fielder.h"
#include "game/match_setup/roster_init.h"
#include "game/match_setup/player_control_transition.h"
#include "Unknown/File_0x800204cc.h"

extern u8 animRelated[0x124];
extern u8 hugeAnimStruct[0x3154];
extern u8 lbl_80354768[];
#define PRACTICE_PROGRESS_FLAGS ((u8 (*)[4])(&lbl_80354768[0xCF4E]))
extern BOOL practice_loadAllGraphics(int teamFielding);

// .text:0x000B6F6C size:0x110
void fn_3_B6F6C(void) {
    initBaseRunnersAfterFoulBall();
    initializeSomethingDuringTransition2();
    g_Strikes.strikes = 0;
    g_Strikes.balls = 0;
    g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_1;
    g_GameLogic.pre_PostMiniGameInd = TRUE;
    g_GameLogic.minigameLastTurnSuccessInd = TRUE;
    practiceNewBatter();
    g_Strikes.storedOuts = g_Strikes.outs;
    g_Strikes.runnerIndexForEachOutThisPitch[0] = -1;
    g_Strikes.runnerIndexForEachOutThisPitch[1] = -1;
    g_Strikes.runnerIndexForEachOutThisPitch[2] = -1;
    g_Strikes.GameControls_StrikeBallBitVector = g_Strikes.balls + (g_Strikes.strikes << 4);
    g_Strikes.howRunnerReachedBase = 0;
    g_Ball.totalFramesAtPlay = 0;
    g_FieldingLogic.playOverInd = 0;
    g_FieldingLogic.framesSincePlayEnded = 0;
    g_FieldingLogic.unused_always0__ = 0;
    g_FieldingLogic.hasProcessedFoulBall = 0;
    g_FieldingLogic.canEndPlayOnLooseBallInd = 0;
    g_FieldingLogic.always0__ = 0;
    g_RunningLogic._13 = 0;
    g_GameLogic.pre_PostMiniGameInd = 0;
    g_GameLogic.minigameLastTurnSuccessInd = 0;
    g_Practice._1EC = 0;
    g_Practice._1ED = 0;
    changeScene(1, 6);
    SetGameStatus(GAME_STATUS_LIVE_BALL);
    setDefaultPlayTrackingVariables2();
    resetAndRunAnimations(0);
}

// .text:0x000B6E98 size:0xD4
void fn_3_B6E98(void) {
    practiceNewBatter();
    g_Strikes.storedOuts = g_Strikes.outs;
    g_Strikes.runnerIndexForEachOutThisPitch[0] = -1;
    g_Strikes.runnerIndexForEachOutThisPitch[1] = -1;
    g_Strikes.runnerIndexForEachOutThisPitch[2] = -1;
    g_Strikes.GameControls_StrikeBallBitVector = g_Strikes.balls + (g_Strikes.strikes << 4);
    g_Strikes.howRunnerReachedBase = 0;
    g_Ball.totalFramesAtPlay = 0;
    g_FieldingLogic.playOverInd = 0;
    g_FieldingLogic.framesSincePlayEnded = 0;
    g_FieldingLogic.unused_always0__ = 0;
    g_FieldingLogic.hasProcessedFoulBall = 0;
    g_FieldingLogic.canEndPlayOnLooseBallInd = 0;
    g_FieldingLogic.always0__ = 0;
    g_RunningLogic._13 = 0;
    g_GameLogic.pre_PostMiniGameInd = 0;
    g_GameLogic.minigameLastTurnSuccessInd = 0;
    g_Practice._1EC = 0;
    g_Practice._1ED = 0;
    changeScene(1, 6);
    SetGameStatus(GAME_STATUS_LIVE_BALL);
    setDefaultPlayTrackingVariables2();
}

// .text:0x000B6D80 size:0x118
void fn_3_B6D80(void) {
    if (g_Practice.instructionNumber < 0) {
        if (practice_checkForPause() != 0) {
            return;
        }
    }
    running_MainFunction();
    if (g_Practice.instructionNumber < 0) {
        if (g_Runners[1].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) {
            g_Practice.guidedPracticeCompletionRelated = TRUE;
        }
    } else if (g_Practice.allowPlayToEndIndicator == FALSE) {
        g_FieldingLogic.playOverCounter = 0;
    } else {
        if (g_FieldingLogic.playOverCounter < 0x7ffe) {
            g_FieldingLogic.playOverCounter++;
        } else {
            g_FieldingLogic.playOverCounter = 0x7fff;
        }
        if (g_FieldingLogic.playOverCounter >= 0x3c) {
            g_Practice.allowPlayToEndIndicator = FALSE;
            g_GameLogic.pre_PostMiniGameInd = TRUE;
            g_GameLogic.minigameLastTurnSuccessInd = TRUE;
            trackLastPitchInfo();
            SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
        } else if (g_FieldingLogic.playOverCounter == 0x36) {
            changeScene(3, 6);
        }
    }
}

// .text:0x000B6C9C size:0xE4
void fn_3_B6C9C(void) {
    if (g_Practice.instructionNumber < 0) {
        if (g_Runners[1].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) {
            g_Practice.guidedPracticeCompletionRelated = TRUE;
        }
    } else if (g_Practice.allowPlayToEndIndicator == FALSE) {
        g_FieldingLogic.playOverCounter = 0;
    } else {
        if (g_FieldingLogic.playOverCounter < 0x7ffe) {
            g_FieldingLogic.playOverCounter++;
        } else {
            g_FieldingLogic.playOverCounter = 0x7fff;
        }
        if (g_FieldingLogic.playOverCounter >= 0x3c) {
            g_Practice.allowPlayToEndIndicator = FALSE;
            g_GameLogic.pre_PostMiniGameInd = TRUE;
            g_GameLogic.minigameLastTurnSuccessInd = TRUE;
            trackLastPitchInfo();
            SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
        } else if (g_FieldingLogic.playOverCounter == 0x36) {
            changeScene(3, 6);
        }
    }
}

// .text:0x000B6C50 size:0x4C
void fn_3_B6C50(void) {
    g_Practice.allowPlayToEndIndicator = FALSE;
    g_GameLogic.pre_PostMiniGameInd = TRUE;
    g_GameLogic.minigameLastTurnSuccessInd = TRUE;
    trackLastPitchInfo();
    SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
}

// .text:0x000B6BA4 size:0xAC
void pitchingPracticeControl(void) {
    switch (g_Practice.tutorialState) {
    case TUTORIAL_STATE_2:
        if (setUpPlayerTryingSkill() == 0) {
            pitchingPractice_BaseballControl();
        } else {
            practiceStartGuidedMessage(g_Practice.practiceLevel, 0);
            SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
        }
        break;
    case TUTORIAL_STATE_0:
        pitchingPracticeRelated();
        break;
    case TUTORIAL_STATE_1:
        pitchingPractice_BaseballControl();
        break;
    case TUTORIAL_STATE_3:
        pitchingPractice_BaseballControl();
        break;
    }
    g_GameLogic.TeamStars[1] = 5;
    g_GameLogic.TeamStars[0] = 5;
}

// .text:0x000B6B70 size:0x34
void fn_3_B6B70(void) {
    g_Practice.pitchingPracticeBatterEnabled = FALSE;
    setTutorialState(TUTORIAL_STATE_0);
}

// .text:0x000B6994 size:0x1DC
void pitchingPracticeRelated(void) {
    switch (g_Practice.practiceState) {
    case PRACTICE_STATE_0:
        if (g_Practice.practiceType_2 == PRACTICE_TYPE_FREEPLAY) {
            practice_loadCharacter(0, 0, g_Minigame.selectSlots[g_Practice.homeAway].charID,
                                   g_Minigame.battingHandedness[g_Practice.homeAway]);
            setPitcherStatsToInMemPitcher(0);
            setFielderValues(0, 0);
        } else {
            setPitcherStatsToInMemPitcher(0);
            setFielderValues(0, 0);
        }
        g_GameLogic.currentBatterPerTeam[0] = 1;
        g_GameLogic.currentBatterPerTeam[1] = 1;
        hugeAnimStruct[0x307D] = 1;
        animRelated[0x9C] = 0;
        hugeAnimStruct[0x2D77] = 0;
        hugeAnimStruct[0x2D7B] = 0;
        g_Practice.characterLoadStarted = FALSE;
        if (g_Practice.practiceType_2 == PRACTICE_TYPE_FREEPLAY) {
            updatePracticeTransitionState(PRACTICE_STATE_1);
        } else {
            updatePracticeTransitionState(PRACTICE_STATE_2);
        }
        break;
    case PRACTICE_STATE_1:
        if (practice_loadAllGraphics(g_GameLogic.teamFielding) != FALSE) {
            updatePracticeTransitionState(PRACTICE_STATE_2);
        }
        break;
    case PRACTICE_STATE_2:
        if (loadPitcherActor() != FALSE) {
            updatePracticeTransitionState(PRACTICE_STATE_4);
        }
        break;
    case PRACTICE_STATE_4:
        if (practice_relatedToSettingCharacters() != FALSE) {
            updatePracticeTransitionState(PRACTICE_STATE_7);
        }
        break;
    case PRACTICE_STATE_7:
        practiceRelatedReset();
        if (g_Practice.practiceType_2 == PRACTICE_TYPE_FREEPLAY) {
            transitionToPlayerControl();
            setTutorialState(TUTORIAL_STATE_3);
        } else {
            practiceRelatedInit();
            g_Practice.commandList = practice_instructions_pitchingPtrs[g_Practice.practiceLevel];
            setTutorialState(TUTORIAL_STATE_1);
        }
        changeScene(1, 6);
        SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
        break;
    }
}

// .text:0x000B6440 size:0x554
void pitchingPractice_BaseballControl(void) {
    g_GameLogic.hudElementLoadingInd = FALSE;
    if (g_Practice.completionMenuActive != FALSE) {
        practiceLogicRelatedPause();
        return;
    }
    if (loadGuidedPractice() != FALSE) {
        return;
    }
    if (g_Practice.instructionNumber >= 0) {
        practice_giveAndDemonstrateInstructions();
        if (g_Practice.readyToMoveToNextInstruction != 0) {
            return;
        }
        if (g_Practice.tutorialState == TUTORIAL_STATE_2) {
            return;
        }
    } else {
        BOOL completionMenuOpened = FALSE;

        if (g_Practice.pauseMenuLoading == 0 && g_Practice.guidedPracticeCompletionRelated != 0 &&
            g_Pitcher.miniGameRelated != 0 && g_UnkSound_32718._07 == 0) {
            g_Practice.frames_sincePracticeCompleted++;
            if (g_Practice.frames_sincePracticeCompleted > 0x5a) {
                if (g_Practice.levelCompleted[g_Practice.practiceType_2][g_Practice.practiceLevel] == 0) {
                    g_Practice.progressNeedsSave = TRUE;
                    g_Practice.levelCompleted[g_Practice.practiceType_2][g_Practice.practiceLevel] = TRUE;
                    PRACTICE_PROGRESS_FLAGS[g_Practice.practiceType_2][g_Practice.practiceLevel] = TRUE;
                }
                g_Practice.completionMenuActive = TRUE;
                practiceResetPauseMenuState();
                practiceStartGuidedMessage(g_Practice.practiceLevel, TRUE);
                completionMenuOpened = TRUE;
            }
        }
        if (completionMenuOpened) {
            return;
        }
    }
    if (g_Ball.totalFramesAtPlay < 0x7ffe) {
        g_Ball.totalFramesAtPlay++;
    } else {
        g_Ball.totalFramesAtPlay = 0x7fff;
    }
    if (g_Practice.frames_sinceMovedToFromMenu < 0xfffe) {
        g_Practice.frames_sinceMovedToFromMenu++;
    } else {
        g_Practice.frames_sinceMovedToFromMenu = 0xffff;
    }
    switch (g_GameLogic.gameStatus) {
    case GAME_STATUS_DEFAULT:
        practiceNewBatter();
        g_Strikes.storedOuts = g_Strikes.outs;
        g_Strikes.runnerIndexForEachOutThisPitch[0] = -1;
        g_Strikes.runnerIndexForEachOutThisPitch[1] = -1;
        g_Strikes.runnerIndexForEachOutThisPitch[2] = -1;
        g_Strikes.GameControls_StrikeBallBitVector = g_Strikes.balls + (g_Strikes.strikes << 4);
        g_Strikes.howRunnerReachedBase = 0;
        g_Ball.totalFramesAtPlay = 0;
        g_FieldingLogic.playOverInd = 0;
        g_FieldingLogic.framesSincePlayEnded = 0;
        g_FieldingLogic.unused_always0__ = 0;
        g_FieldingLogic.hasProcessedFoulBall = 0;
        g_FieldingLogic.canEndPlayOnLooseBallInd = 0;
        g_FieldingLogic.always0__ = 0;
        g_RunningLogic._13 = 0;
        g_GameLogic.pre_PostMiniGameInd = 0;
        g_GameLogic.minigameLastTurnSuccessInd = 0;
        g_Practice.guidedPracticeCompletionRelated2 = 0;
        changeScene(1, 6);
        SetGameStatus(GAME_STATUS_AT_BAT);
        setDefaultPlayTrackingVariables2();
        break;
    case GAME_STATUS_AT_BAT:
        if (g_Practice.instructionNumber < 0) {
            if (practice_checkForPause() != FALSE) {
                break;
            }
        }
        atBat_Pitcher();
        if (g_Practice.pitchingPracticeBatterEnabled != 0) {
            atBat_batter();
            running_MainFunction();
        }
        atBat_Fielders();
        if (g_Practice.instructionNumber >= 0) {
            break;
        }
        if (g_Practice.guidedPracticeCompletionRelated2 != 0) {
            break;
        }
        if (g_Practice.practiceType_2 == PRACTICE_TYPE_FREEPLAY) {
            break;
        }
        if (g_Pitcher.pitcherActionState != PITCHER_ACTION_STATE_NO_CONTACT) {
            break;
        }
        switch (g_Practice.practiceLevel) {
        case 0:
            g_Practice.guidedPracticeCounter++;
            break;
        case 1:
            if (g_Pitcher.ChargePitchType >= 2) {
                g_Practice.guidedPracticeCounter++;
            }
            break;
        case 2:
            if (g_Pitcher.TypeOfPitch == 2) {
                g_Practice.guidedPracticeCounter++;
            }
            break;
        case 3:
            if (g_Pitcher.starPitchType != CAPTAIN_STAR_TYPE_NONE) {
                g_Practice.guidedPracticeCounter++;
            }
            break;
        }
        if (g_Practice.guidedPracticeCounter >=
            guidedPracticeThresholds[g_Practice.practiceType_2][g_Practice.practiceLevel]) {
            g_Practice.guidedPracticeCompletionRelated = TRUE;
        }
        g_Practice.guidedPracticeCompletionRelated2 = TRUE;
        break;
    case GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY:
        resetBallValuesBetweenBatters();
        resetPitcherValuesBetweenBatters(0);
        setBatterContactConstants();
        resetInMemRunners();
        initializeARunner();
        initializeMiniGameCharacters();
        setDefaultInMemFielder();
        betweenABSetPitcherBatter();
        initializeSomethingDuringTransition();
        initializeSomethingDuringTransition2();
        g_Strikes.strikes = 0;
        g_Strikes.balls = 0;
        g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_1;
        if (g_GameLogic.pre_PostMiniGameInd != 0) {
            g_GameLogic.minigameLastTurnSuccessInd = TRUE;
            g_GameLogic.hudElementLoadingInd = TRUE;
        } else {
            g_GameLogic.minigameLastTurnSuccessInd = FALSE;
        }
        g_GameLogic.pre_PostMiniGameInd = FALSE;
        g_GameLogic.minigameLastTurnSuccessInd = FALSE;
        practiceNewBatter();
        g_Strikes.storedOuts = g_Strikes.outs;
        g_Strikes.runnerIndexForEachOutThisPitch[0] = -1;
        g_Strikes.runnerIndexForEachOutThisPitch[1] = -1;
        g_Strikes.runnerIndexForEachOutThisPitch[2] = -1;
        g_Strikes.GameControls_StrikeBallBitVector = g_Strikes.balls + (g_Strikes.strikes << 4);
        g_Strikes.howRunnerReachedBase = 0;
        g_Ball.totalFramesAtPlay = 0;
        g_FieldingLogic.playOverInd = 0;
        g_FieldingLogic.framesSincePlayEnded = 0;
        g_FieldingLogic.unused_always0__ = 0;
        g_FieldingLogic.hasProcessedFoulBall = 0;
        g_FieldingLogic.canEndPlayOnLooseBallInd = 0;
        g_FieldingLogic.always0__ = 0;
        g_RunningLogic._13 = 0;
        g_GameLogic.pre_PostMiniGameInd = 0;
        g_GameLogic.minigameLastTurnSuccessInd = 0;
        g_Practice.guidedPracticeCompletionRelated2 = 0;
        changeScene(1, 6);
        SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
        setDefaultPlayTrackingVariables2();
        resetAndRunAnimations(0);
        break;
    }
    g_Strikes.strikes = 0;
    g_Strikes.balls = 0;
    g_Strikes.outs = 0;
}

// .text:0x000B6320 size:0x120
BOOL practiceRelUnuse(void) {
    if (g_Practice.pauseMenuLoading != 0) {
        return FALSE;
    }
    if (g_Practice.guidedPracticeCompletionRelated == 0) {
        return FALSE;
    }
    if (g_Pitcher.miniGameRelated == 0) {
        return FALSE;
    }
    if (g_UnkSound_32718._07 != 0) {
        return FALSE;
    }
    g_Practice.frames_sincePracticeCompleted++;
    if (g_Practice.frames_sincePracticeCompleted > 0x5a) {
        if (g_Practice.levelCompleted[g_Practice.practiceType_2][g_Practice.practiceLevel] == 0) {
            g_Practice.progressNeedsSave = TRUE;
            g_Practice.levelCompleted[g_Practice.practiceType_2][g_Practice.practiceLevel] = TRUE;
            PRACTICE_PROGRESS_FLAGS[g_Practice.practiceType_2][g_Practice.practiceLevel] = TRUE;
        }
        g_Practice.completionMenuActive = TRUE;
        practiceResetPauseMenuState();
        practiceStartGuidedMessage(g_Practice.practiceLevel, TRUE);
        return TRUE;
    }
    return FALSE;
}

// .text:0x000B61C0 size:0x160
void fn_3_B61C0(void) {
    resetBallValuesBetweenBatters();
    resetPitcherValuesBetweenBatters(0);
    setBatterContactConstants();
    resetInMemRunners();
    initializeARunner();
    initializeMiniGameCharacters();
    setDefaultInMemFielder();
    betweenABSetPitcherBatter();
    initializeSomethingDuringTransition();
    initializeSomethingDuringTransition2();
    g_Strikes.strikes = 0;
    g_Strikes.balls = 0;
    g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_1;
    if (g_GameLogic.pre_PostMiniGameInd != 0) {
        g_GameLogic.minigameLastTurnSuccessInd = TRUE;
        g_GameLogic.hudElementLoadingInd = TRUE;
    } else {
        g_GameLogic.minigameLastTurnSuccessInd = FALSE;
    }
    g_GameLogic.pre_PostMiniGameInd = FALSE;
    g_GameLogic.minigameLastTurnSuccessInd = FALSE;
    practiceNewBatter();
    g_Strikes.storedOuts = g_Strikes.outs;
    g_Strikes.runnerIndexForEachOutThisPitch[0] = -1;
    g_Strikes.runnerIndexForEachOutThisPitch[1] = -1;
    g_Strikes.runnerIndexForEachOutThisPitch[2] = -1;
    g_Strikes.GameControls_StrikeBallBitVector = g_Strikes.balls + (g_Strikes.strikes << 4);
    g_Strikes.howRunnerReachedBase = 0;
    g_Ball.totalFramesAtPlay = 0;
    g_FieldingLogic.playOverInd = 0;
    g_FieldingLogic.framesSincePlayEnded = 0;
    g_FieldingLogic.unused_always0__ = 0;
    g_FieldingLogic.hasProcessedFoulBall = 0;
    g_FieldingLogic.canEndPlayOnLooseBallInd = 0;
    g_FieldingLogic.always0__ = 0;
    g_RunningLogic._13 = 0;
    g_GameLogic.pre_PostMiniGameInd = 0;
    g_GameLogic.minigameLastTurnSuccessInd = 0;
    g_Practice.guidedPracticeCompletionRelated2 = 0;
    changeScene(1, 6);
    SetGameStatus(GAME_STATUS_AT_BAT);
    setDefaultPlayTrackingVariables2();
    resetAndRunAnimations(0);
}

// .text:0x000B60F0 size:0xD0
void fn_3_B60F0(void) {
    practiceNewBatter();
    g_Strikes.storedOuts = g_Strikes.outs;
    g_Strikes.runnerIndexForEachOutThisPitch[0] = -1;
    g_Strikes.runnerIndexForEachOutThisPitch[1] = -1;
    g_Strikes.runnerIndexForEachOutThisPitch[2] = -1;
    g_Strikes.GameControls_StrikeBallBitVector = g_Strikes.balls + (g_Strikes.strikes << 4);
    g_Strikes.howRunnerReachedBase = 0;
    g_Ball.totalFramesAtPlay = 0;
    g_FieldingLogic.playOverInd = 0;
    g_FieldingLogic.framesSincePlayEnded = 0;
    g_FieldingLogic.unused_always0__ = 0;
    g_FieldingLogic.hasProcessedFoulBall = 0;
    g_FieldingLogic.canEndPlayOnLooseBallInd = 0;
    g_FieldingLogic.always0__ = 0;
    g_RunningLogic._13 = 0;
    g_GameLogic.pre_PostMiniGameInd = 0;
    g_GameLogic.minigameLastTurnSuccessInd = 0;
    g_Practice.guidedPracticeCompletionRelated2 = 0;
    changeScene(1, 6);
    SetGameStatus(GAME_STATUS_AT_BAT);
    setDefaultPlayTrackingVariables2();
}

// .text:0x000B5F7C size:0x174
void fn_3_B5F7C(void) {
    if (g_Practice.instructionNumber < 0) {
        if (practice_checkForPause() != 0) {
            return;
        }
    }
    atBat_Pitcher();
    if (g_Practice.pitchingPracticeBatterEnabled != 0) {
        atBat_batter();
        running_MainFunction();
    }
    atBat_Fielders();
    if (g_Practice.instructionNumber >= 0) {
        return;
    }
    if (g_Practice.guidedPracticeCompletionRelated2 != 0) {
        return;
    }
    if (g_Practice.practiceType_2 == PRACTICE_TYPE_FREEPLAY) {
        return;
    }
    if (g_Pitcher.pitcherActionState != PITCHER_ACTION_STATE_NO_CONTACT) {
        return;
    }
    switch (g_Practice.practiceLevel) {
    case 0:
        g_Practice.guidedPracticeCounter++;
        break;
    case 1:
        if (g_Pitcher.ChargePitchType >= 2) {
            g_Practice.guidedPracticeCounter++;
        }
        break;
    case 2:
        if (g_Pitcher.TypeOfPitch == 2) {
            g_Practice.guidedPracticeCounter++;
        }
        break;
    case 3:
        if (g_Pitcher.starPitchType != CAPTAIN_STAR_TYPE_NONE) {
            g_Practice.guidedPracticeCounter++;
        }
        break;
    }
    if (g_Practice.guidedPracticeCounter >=
        guidedPracticeThresholds[g_Practice.practiceType_2][g_Practice.practiceLevel]) {
        g_Practice.guidedPracticeCompletionRelated = TRUE;
    }
    g_Practice.guidedPracticeCompletionRelated2 = TRUE;
}

// .text:0x000B5E7C size:0x100
void fn_3_B5E7C(void) {
    if (g_Practice.practiceType_2 == PRACTICE_TYPE_FREEPLAY) {
        return;
    }
    if (g_Pitcher.pitcherActionState != PITCHER_ACTION_STATE_NO_CONTACT) {
        return;
    }
    switch (g_Practice.practiceLevel) {
    case 0:
        g_Practice.guidedPracticeCounter++;
        break;
    case 1:
        if (g_Pitcher.ChargePitchType >= 2) {
            g_Practice.guidedPracticeCounter++;
        }
        break;
    case 2:
        if (g_Pitcher.TypeOfPitch == 2) {
            g_Practice.guidedPracticeCounter++;
        }
        break;
    case 3:
        if (g_Pitcher.starPitchType != CAPTAIN_STAR_TYPE_NONE) {
            g_Practice.guidedPracticeCounter++;
        }
        break;
    }
    if (g_Practice.guidedPracticeCounter >=
        guidedPracticeThresholds[g_Practice.practiceType_2][g_Practice.practiceLevel]) {
        g_Practice.guidedPracticeCompletionRelated = TRUE;
    }
    g_Practice.guidedPracticeCompletionRelated2 = TRUE;
}
