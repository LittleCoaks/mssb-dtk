#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_rep_1C68
#include "header_rep_data.h"
#include "game/practice/baserunning_practice.h"
#include "game/UnknownHomes_Game.h"
#include "game/practice/guided_practice.h"
#include "game/practice/practice_menu.h"
#include "game/baserunning/runner.h"
#include "game/match_setup/match_flow.h"
#include "game/match_setup/transition_init.h"
#include "game/animation/animation_dispatch.h"
#include "game/pitching/pitcher_stamina.h"
#include "Unknown/File_0x800204cc.h"

extern u8 lbl_80354768[];
#define PRACTICE_PROGRESS_FLAGS ((u8 (*)[4])(&lbl_80354768[0xCF4E]))
extern u8 baserunningPractice_activeRunners[16];
extern void *practice_instructions_baserunningPtrs[4];
extern u8 animRelated[0x124];
extern u8 hugeAnimStruct[0x3154];
extern u8 highLevelSimulationFlag[4];
extern void practiceLogicRelatedPause(void);
extern int loadGuidedPractice(void);
extern void practice_giveAndDemonstrateInstructions(void);
extern void updatePracticeTransitionState(int state);
extern int loadRunnerActors(void);
extern BOOL practice_relatedToSettingCharacters(void);
extern void practiceRelatedReset(void);
extern void setTutorialState(int state);
extern void initializeSomethingDuringTransition2(void);

BOOL practiceRelatedUnused_maybe(void) {
    if (g_Practice.pauseMenuLoading != 0) {
        return FALSE;
    }
    if (g_Practice.guidedPracticeCompletionRelated == 0) {
        return FALSE;
    }
    if (g_UnkSound_32718._07 != 0) {
        return FALSE;
    }
    g_Practice.frames_sincePracticeCompleted++;
    if (g_Practice.frames_sincePracticeCompleted > 150) {
        if (g_Practice.levelCompleted[g_Practice.practiceType_2][g_Practice.practiceLevel] == 0) {
            g_Practice.progressNeedsSave = TRUE;
            g_Practice.levelCompleted[g_Practice.practiceType_2][g_Practice.practiceLevel] = 1;
            PRACTICE_PROGRESS_FLAGS[g_Practice.practiceType_2][g_Practice.practiceLevel] = 1;
        }
        g_Practice.completionMenuActive = TRUE;
        practiceResetPauseMenuState();
        practiceStartGuidedMessage(g_Practice.practiceLevel + 12, 1);
        return TRUE;
    }
    return FALSE;
}

void baseRunningPracticeRelated(void) {
    BOOL completed;

    g_GameLogic.hudElementLoadingInd = FALSE;
    if (g_Ball.totalFramesAtPlay < 0x7FFE) {
        g_Ball.totalFramesAtPlay++;
    } else {
        g_Ball.totalFramesAtPlay = 0x7FFF;
    }
    if (g_Practice.completionMenuActive != 0) {
        practiceLogicRelatedPause();
        return;
    }
    if (loadGuidedPractice() != 0) {
        running_MainFunction();
        return;
    }
    if (g_Practice.instructionNumber >= 0) {
        practice_giveAndDemonstrateInstructions();
        if (g_Practice.readyToMoveToNextInstruction != 0 || g_Practice.tutorialState == TUTORIAL_STATE_2) {
            return;
        }
    } else {
        if (g_Practice.pauseMenuLoading != 0) {
            completed = FALSE;
        } else if (g_Practice.guidedPracticeCompletionRelated == 0) {
            completed = FALSE;
        } else if (g_UnkSound_32718._07 != 0) {
            completed = FALSE;
        } else {
            g_Practice.frames_sincePracticeCompleted++;
            if (g_Practice.frames_sincePracticeCompleted > 150) {
                if (g_Practice.levelCompleted[g_Practice.practiceType_2][g_Practice.practiceLevel] == 0) {
                    g_Practice.progressNeedsSave = TRUE;
                    g_Practice.levelCompleted[g_Practice.practiceType_2][g_Practice.practiceLevel] = 1;
                    PRACTICE_PROGRESS_FLAGS[g_Practice.practiceType_2][g_Practice.practiceLevel] = 1;
                }
                g_Practice.completionMenuActive = TRUE;
                practiceResetPauseMenuState();
                practiceStartGuidedMessage(g_Practice.practiceLevel + 12, 1);
                completed = TRUE;
            } else {
                completed = FALSE;
            }
        }
        if (completed) {
            return;
        }
    }

    if (g_Practice.frames_sinceMovedToFromMenu < 0xFFFE) {
        g_Practice.frames_sinceMovedToFromMenu++;
    } else {
        g_Practice.frames_sinceMovedToFromMenu = 0xFFFF;
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
        ((u8 *)&g_Practice)[0x1EC] = 0;
        ((u8 *)&g_Practice)[0x1ED] = 0;
        changeScene(SCENE_ID_AT_BAT, 6);
        SetGameStatus(GAME_STATUS_LIVE_BALL);
        setDefaultPlayTrackingVariables2();
        break;
    case GAME_STATUS_LIVE_BALL:
        if (g_Practice.instructionNumber < 0 && practice_checkForPause() != 0) {
            break;
        }
        running_MainFunction();
        if (g_Practice.instructionNumber >= 0) {
            if (g_Practice.allowPlayToEndIndicator == 0) {
                g_FieldingLogic.playOverCounter = 0;
                break;
            }
        } else if (g_Runners[1].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) {
            g_Practice.guidedPracticeCompletionRelated = TRUE;
            break;
        }
        if (g_FieldingLogic.playOverCounter < 0x7FFE) {
            g_FieldingLogic.playOverCounter++;
        } else {
            g_FieldingLogic.playOverCounter = 0x7FFF;
        }
        if (g_FieldingLogic.playOverCounter >= 60) {
            g_Practice.allowPlayToEndIndicator = FALSE;
            g_GameLogic.pre_PostMiniGameInd = TRUE;
            g_GameLogic.minigameLastTurnSuccessInd = TRUE;
            trackLastPitchInfo();
            SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
        } else if (g_FieldingLogic.playOverCounter == 54) {
            changeScene(3, 6);
        }
        break;
    case GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY:
        initBaseRunnersAfterFoulBall();
        initializeSomethingDuringTransition2();
        g_Strikes.strikes = 0;
        g_Strikes.balls = 0;
        g_GameLogic._125 = 1;
        g_GameLogic.pre_PostMiniGameInd = 1;
        g_GameLogic.minigameLastTurnSuccessInd = 1;
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
        ((u8 *)&g_Practice)[0x1EC] = 0;
        ((u8 *)&g_Practice)[0x1ED] = 0;
        changeScene(SCENE_ID_AT_BAT, 6);
        SetGameStatus(GAME_STATUS_LIVE_BALL);
        setDefaultPlayTrackingVariables2();
        resetAndRunAnimations(0);
        break;
    }
    g_Strikes.strikes = 0;
    g_Strikes.balls = 0;
    g_Strikes.outs = 0;
}

void practiceRel(void) {
    int i;

    switch (g_Practice.practiceState) {
    case PRACTICE_STATE_0:
        g_GameLogic.currentBatterPerTeam[0] = 1;
        g_GameLogic.currentBatterPerTeam[1] = 1;
        hugeAnimStruct[0x307D] = 0;
        for (i = 0; i < 4; i++) {
            g_Practice.baserunningActiveRunners[i] = baserunningPractice_activeRunners[g_Practice.practiceLevel * 4 + i];
        }
        practiceSetupRunnerStatus();
        animRelated[0x9A] = 0;
        highLevelSimulationFlag[2] = 0;
        g_Practice.characterLoadStarted = 0;
        updatePracticeTransitionState(PRACTICE_STATE_1);
        break;
    case PRACTICE_STATE_1:
        if (loadRunnerActors() != 0) {
            updatePracticeTransitionState(PRACTICE_STATE_4);
        }
        break;
    case PRACTICE_STATE_4:
        if (practice_relatedToSettingCharacters() != 0) {
            updatePracticeTransitionState(PRACTICE_STATE_7);
        }
        break;
    case PRACTICE_STATE_7:
        practiceRelatedReset();
        practiceRelatedInit();
        g_Practice.commandList = practice_instructions_baserunningPtrs[g_Practice.practiceLevel];
        changeScene(SCENE_ID_AT_BAT, 6);
        SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
        setTutorialState(TUTORIAL_STATE_1);
        break;
    }
}

void fn_3_B777C(int value) {
    ((u8 *)&g_Practice)[0x1E5] = value;
    g_Practice.maybeCommandData[2] = 0;
}

void fn_3_B7794(void) {
    ((u8 *)&g_Practice)[0x1E8] = TRUE;
    ((u8 *)&g_Practice)[0x1E9] = TRUE;
    ((u8 *)&g_Practice)[0x1EA] = FALSE;
    ((u8 *)&g_Practice)[0x1EB] = FALSE;
    ((u8 *)&g_Practice)[0x1E7] = FALSE;
    setTutorialState(TUTORIAL_STATE_0);
}

void baseRunningPracticeControl(void) {
    switch (g_Practice.tutorialState) {
    case TUTORIAL_STATE_0:
        switch (g_Practice.practiceState) {
        case PRACTICE_STATE_0:
            g_GameLogic.currentBatterPerTeam[0] = 1;
            g_GameLogic.currentBatterPerTeam[1] = 1;
            hugeAnimStruct[0x307D] = 0;
            g_Practice.baserunningActiveRunners[0] = baserunningPractice_activeRunners[g_Practice.practiceLevel * 4];
            g_Practice.baserunningActiveRunners[1] = baserunningPractice_activeRunners[g_Practice.practiceLevel * 4 + 1];
            g_Practice.baserunningActiveRunners[2] = baserunningPractice_activeRunners[g_Practice.practiceLevel * 4 + 2];
            g_Practice.baserunningActiveRunners[3] = baserunningPractice_activeRunners[g_Practice.practiceLevel * 4 + 3];
            practiceSetupRunnerStatus();
            animRelated[0x9A] = 0;
            highLevelSimulationFlag[2] = 0;
            g_Practice.characterLoadStarted = 0;
            updatePracticeTransitionState(PRACTICE_STATE_1);
            break;
        case PRACTICE_STATE_1:
            if (loadRunnerActors() != 0) {
                updatePracticeTransitionState(PRACTICE_STATE_4);
            }
            break;
        case PRACTICE_STATE_4:
            if (practice_relatedToSettingCharacters() != 0) {
                updatePracticeTransitionState(PRACTICE_STATE_7);
            }
            break;
        case PRACTICE_STATE_7:
            practiceRelatedReset();
            practiceRelatedInit();
            g_Practice.commandList = practice_instructions_baserunningPtrs[g_Practice.practiceLevel];
            changeScene(SCENE_ID_AT_BAT, 6);
            SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
            setTutorialState(TUTORIAL_STATE_1);
            break;
        }
        break;
    case TUTORIAL_STATE_1:
        baseRunningPracticeRelated();
        break;
    case TUTORIAL_STATE_2:
        if (setUpPlayerTryingSkill() == 0) {
            baseRunningPracticeRelated();
        } else {
            practiceStartGuidedMessage(g_Practice.practiceLevel + 12, 0);
            SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
        }
        break;
    case TUTORIAL_STATE_3:
        baseRunningPracticeRelated();
        break;
    }
}
