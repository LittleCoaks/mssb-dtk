#define SQRT2_LINKAGE static
#include "game/practice/practice_modes.h"
#include "game/UnknownHomes_Game.h"
#include "game/match_setup/match_flow.h"
#include "game/match_setup/roster_init.h"
#include "game/ball/ball_physics.h"
#include "game/match_setup/at_bat_setup.h"
#include "game/match_setup/match_loading.h"
#include "game/match_setup/transition_init.h"
#include "game/animation/animation_dispatch.h"
#include "game/fielding/fielder.h"
#include "game/baserunning/runner.h"
#include "game/batting/batter.h"
#include "game/pitching/pitcher.h"
#include "game/pitching/pitcher_stamina.h"
#include "game/practice/guided_practice.h"
#include "Unknown/File_0x800204cc.h"
#define REP_HEADER_DATA_FN getRepHeaderData_practiceModes
#include "header_rep_data.h"

extern u8 animRelated[0x124];
extern u8 hugeAnimStruct[0x3154];
extern u8 highLevelSimulationFlag[4];
extern u8 lbl_80354768[];
extern s16 practiceFrameConsts[];
extern int random_fn_3_9EE24(int max);
extern void practice_loadCharacter(int arg0, int arg1, int arg2, int arg3);
extern void transitionToPlayerControl(void);

extern void setTutorialState(int state);
extern int setUpPlayerTryingSkill(void);
extern void practiceStartGuidedMessage(int arg0, int arg1);
extern void updatePracticeTransitionState(int state);
extern void fn_80011BE4(int arg0);
extern void practiceRelatedReset(void);
extern void practiceRelatedInit(void);
extern int loadRunnerActors(void);
extern BOOL loadPitcherActor(void);
extern int someAnimationIndFunction(void);
extern BOOL practice_relatedToSettingCharacters(void);
extern void practiceLogicRelatedPause(void);
extern int loadGuidedPractice(void);
extern void practice_giveAndDemonstrateInstructions(void);
extern int practice_checkForPause(void);
extern void ballPhysica(void);
extern void fielderMainFunction(void);
extern void practice_fieldingRelated(void);
extern void practiceResetPauseMenuState(void);

void fieldingPracticeControl(void) {
    switch (g_Practice.tutorialState) {
    case TUTORIAL_STATE_0:
        fieldingPracticeRelated();
        break;
    case TUTORIAL_STATE_1:
        fieldingPracticeInitialization();
        break;
    case TUTORIAL_STATE_2:
        if (setUpPlayerTryingSkill() == 0) {
            fieldingPracticeInitialization();
        } else {
            practiceStartGuidedMessage(g_Practice.practiceLevel + 8, 0);
            SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
        }
        break;
    case TUTORIAL_STATE_3:
        fieldingPracticeInitialization();
        break;
    }
}

void fieldingPracticeResetTutorialState(void) {
    g_Practice._1DD = 0;
    g_Practice._1DE = 0;
    g_Practice._1DF = 0;
    g_Practice._1E0 = 0;
    g_Practice._1E2 = 0;
    g_Practice.maybeCommandData[0] = 0;
    setTutorialState(TUTORIAL_STATE_0);
}

void fieldingPracticeRelated(void) {
    int i;

    switch (g_Practice.practiceState) {
    case PRACTICE_STATE_0:
        hugeAnimStruct[0x307D] = 0;
        setPitcherStatsToInMemPitcher(0);
        resetInMemRunners();
        i = 0;
        do {
            setFielderValues(i, i);
            i++;
        } while (i < 9);
        setInMemBatterConstants(0);
        initializeInMemRunner(0, 0);
        g_GameLogic.currentBatterPerTeam[0] = 1;
        g_GameLogic.currentBatterPerTeam[1] = 1;
        animRelated[0x9A] = 0;
        animRelated[0x9C] = 0;
        highLevelSimulationFlag[2] = 0;
        g_Practice.aIEnabled = 1;
        g_Practice.practiceBatterHandedness = 1;
        g_Practice.characterLoadStarted = 0;
        fn_80011BE4(9);
        updatePracticeTransitionState(PRACTICE_STATE_1);
        break;
    case PRACTICE_STATE_1:
        if (loadRunnerActors() != 0) {
            updatePracticeTransitionState(PRACTICE_STATE_2);
        }
        break;
    case PRACTICE_STATE_2:
        if (loadPitcherActor() != 0) {
            updatePracticeTransitionState(PRACTICE_STATE_3);
        }
        break;
    case PRACTICE_STATE_3:
        if (someAnimationIndFunction() != 0) {
            updatePracticeTransitionState(PRACTICE_STATE_4);
        }
        break;
    case PRACTICE_STATE_4:
        if (practice_relatedToSettingCharacters() != 0) {
            updatePracticeTransitionState(PRACTICE_STATE_7);
        }
        break;
    case PRACTICE_STATE_5:
    case PRACTICE_STATE_6:
        break;
    case PRACTICE_STATE_7:
        practiceRelatedReset();
        practiceRelatedInit();
        g_Practice.commandList = practice_instructions_fieldingPtrs[g_Practice.practiceLevel];
        changeScene(1, 6);
        SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
        setTutorialState(TUTORIAL_STATE_1);
        break;
    }
}

void fieldingPracticeInitialization(void) {
    int skipRemainder;

    g_GameLogic.hudElementLoadingInd = 0;
    g_GameLogic.hudLoadingRelated = 0;
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
        if (g_Practice.pauseMenuLoading != 0) {
            skipRemainder = 0;
        } else if (g_Practice.guidedPracticeCompletionRelated == 0) {
            skipRemainder = 0;
        } else if (g_UnkSound_32718._07 != 0) {
            skipRemainder = 0;
        } else {
            g_Practice.frames_sincePracticeCompleted++;
            if (g_Practice.frames_sincePracticeCompleted > 0x96) {
                if (g_Practice.levelCompleted[g_Practice.practiceType_2][g_Practice.practiceLevel] == 0) {
                    g_Practice.progressNeedsSave = 1;
                    g_Practice.levelCompleted[g_Practice.practiceType_2][g_Practice.practiceLevel] = 1;
                    lbl_80354768[0xCF4E + g_Practice.practiceType_2 * 4 + g_Practice.practiceLevel] = 1;
                }
                g_Practice.completionMenuActive = 1;
                practiceResetPauseMenuState();
                practiceStartGuidedMessage(g_Practice.practiceLevel + 8, 1);
                skipRemainder = 1;
            } else {
                skipRemainder = 0;
            }
        }
        if (skipRemainder != 0) {
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
        g_Pitcher.handedness = g_Fielders[0].throwingHandedness;
        g_Pitcher.curveBallSpeed = 0x7D;
        g_Pitcher.fastBallSpeed = 0x91;
        g_Pitcher.cursedBallStat = 0x64;
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
        g_Practice.hitVariablesSetIndicator = 0;
        g_Practice.fieldingPlayStatus = 0;
        g_Practice.fieldingSprintMaxed = 0;
        g_Strikes.outs = 0;
        g_Practice.frames_sincePlayStart = 0;
        changeScene(1, 6);
        SetGameStatus(GAME_STATUS_AT_BAT);
        setDefaultPlayTrackingVariables2();
        break;
    case GAME_STATUS_AT_BAT:
        if (g_Practice.instructionNumber < 0) {
            if (practice_checkForPause() != 0) {
                break;
            }
        }
        if (g_Practice.hitVariablesSetIndicator == 0) {
            fieldingPractice_setHitVariables();
        }
        atBat_Pitcher();
        atBat_batter();
        running_MainFunction();
        atBat_Fielders();
        break;
    case GAME_STATUS_LIVE_BALL:
        if (g_Practice.instructionNumber < 0) {
            if (practice_checkForPause() != 0) {
                break;
            }
        }
        ballPhysica();
        fielderMainFunction();
        running_MainFunction();
        practice_fieldingRelated();
        break;
    case GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY:
        resetBallValuesBetweenBatters();
        resetPitcherValuesBetweenBatters(0);
        setBatterContactConstants();
        initializeARunner();
        initializeMiniGameCharacters();
        betweenABSetPitcherBatter();
        initializeSomethingDuringTransition();
        initializeSomethingDuringTransition2();
        g_Strikes.strikes = 0;
        g_Strikes.balls = 0;
        g_GameLogic._125 = 1;
        g_GameLogic.pre_PostMiniGameInd = 1;
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        practiceNewBatter();
        g_Pitcher.handedness = g_Fielders[0].throwingHandedness;
        g_Pitcher.curveBallSpeed = 0x7D;
        g_Pitcher.fastBallSpeed = 0x91;
        g_Pitcher.cursedBallStat = 0x64;
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
        g_Practice.hitVariablesSetIndicator = 0;
        g_Practice.fieldingPlayStatus = 0;
        g_Practice.fieldingSprintMaxed = 0;
        g_Strikes.outs = 0;
        g_Practice.frames_sincePlayStart = 0;
        changeScene(1, 6);
        SetGameStatus(GAME_STATUS_AT_BAT);
        setDefaultPlayTrackingVariables2();
        resetAndRunAnimations(0);
        break;
    default:
        break;
    }

    g_Strikes.strikes = 0;
    g_Strikes.balls = 0;
    g_Strikes.outs = 0;
}

BOOL practiceRelatedUnused(void) {
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
    if (g_Practice.frames_sincePracticeCompleted > 0x96) {
        if (g_Practice.levelCompleted[g_Practice.practiceType_2][g_Practice.practiceLevel] == 0) {
            g_Practice.progressNeedsSave = 1;
            g_Practice.levelCompleted[g_Practice.practiceType_2][g_Practice.practiceLevel] = 1;
            lbl_80354768[0xCF4E + g_Practice.practiceType_2 * 4 + g_Practice.practiceLevel] = 1;
        }
        g_Practice.completionMenuActive = 1;
        practiceResetPauseMenuState();
        practiceStartGuidedMessage(g_Practice.practiceLevel + 8, 1);
        return TRUE;
    }
    return FALSE;
}

void fieldingPracticePrepareNextPlay(void) {
    resetBallValuesBetweenBatters();
    resetPitcherValuesBetweenBatters(0);
    setBatterContactConstants();
    initializeARunner();
    initializeMiniGameCharacters();
    betweenABSetPitcherBatter();
    initializeSomethingDuringTransition();
    initializeSomethingDuringTransition2();
    g_Strikes.strikes = 0;
    g_Strikes.balls = 0;
    g_GameLogic._125 = 1;
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    practiceNewBatter();
        g_Pitcher.handedness = g_Fielders[0].throwingHandedness;
        g_Pitcher.curveBallSpeed = 0x7D;
        g_Pitcher.fastBallSpeed = 0x91;
        g_Pitcher.cursedBallStat = 0x64;
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
        g_Practice.hitVariablesSetIndicator = 0;
        g_Practice.fieldingPlayStatus = 0;
        g_Practice.fieldingSprintMaxed = 0;
        g_Strikes.outs = 0;
        g_Practice.frames_sincePlayStart = 0;
        changeScene(1, 6);
    SetGameStatus(GAME_STATUS_AT_BAT);
    setDefaultPlayTrackingVariables2();
    resetAndRunAnimations(0);
}

void fieldingPracticeBeginPlay(void) {
    practiceNewBatter();
        g_Pitcher.handedness = g_Fielders[0].throwingHandedness;
        g_Pitcher.curveBallSpeed = 0x7D;
        g_Pitcher.fastBallSpeed = 0x91;
        g_Pitcher.cursedBallStat = 0x64;
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
        g_Practice.hitVariablesSetIndicator = 0;
        g_Practice.fieldingPlayStatus = 0;
        g_Practice.fieldingSprintMaxed = 0;
        g_Strikes.outs = 0;
        g_Practice.frames_sincePlayStart = 0;
    changeScene(1, 6);
    SetGameStatus(GAME_STATUS_AT_BAT);
    setDefaultPlayTrackingVariables2();
}

void fieldingPracticeAtBat(void) {
    if (g_Practice.instructionNumber < 0) {
        if (practice_checkForPause() != 0) {
            return;
        }
    }
    if (g_Practice.hitVariablesSetIndicator == 0) {
        fieldingPractice_setHitVariables();
    }
    atBat_Pitcher();
    atBat_batter();
    running_MainFunction();
    atBat_Fielders();
}

void fieldingPracticeLiveBall(void) {
    if (g_Practice.instructionNumber < 0) {
        if (practice_checkForPause() != 0) {
            return;
        }
    }
    ballPhysica();
    fielderMainFunction();
    running_MainFunction();
    practice_fieldingRelated();
}

void practice_fieldingRelated(void) {
    u8 state;
    s16 threshold;

    threshold = 7;
    if (g_Practice.instructionNumber >= 0) {
        if (g_Practice.allowPlayToEndIndicator != 0) {
            threshold = 60;
        } else {
            g_FieldingLogic.playOverCounter = 0;
            return;
        }
    } else if (g_Practice.fieldingPlayStatus != 2) {
        state = g_Practice.fieldingPlayStatus;
        {
            if (g_Practice.practiceLevel == 0) {
                if (g_Ball.numThrowsDuringPlay != 0) {
                    threshold = fieldingPractice_frameThresholds[1];
                    if (state == 0) {
                        g_Practice.fieldingPlayStatus = 1;
                        g_Practice.guidedPracticeCounter++;
                    }
                }
            } else if (g_Practice.practiceLevel == 1) {
                if (g_Strikes.outs != 0 || state == 1) {
                    threshold = fieldingPractice_frameThresholds[2];
                    if (state == 0) {
                        g_Practice.fieldingPlayStatus = 1;
                        g_Practice.guidedPracticeCounter++;
                    }
                }
                if (g_Runners[0].currentBase >= 1) {
                    if (g_Ball.AtBat_ContactResult != 0) {
                        threshold = fieldingPractice_frameThresholds[2];
                        if (state == 0) {
                            g_Practice.fieldingPlayStatus = 1;
                        }
                    }
                }
            } else if (g_Practice.practiceLevel == 2) {
                if (g_Ball.numberOfThrowsDuringPlay != 0) {
                    threshold = fieldingPractice_frameThresholds[3];
                    if (state == 0) {
                        if (g_Practice.fieldingSprintMaxed != 0) {
                            g_Practice.guidedPracticeCounter++;
                        }
                        g_Practice.fieldingPlayStatus = 1;
                    }
                } else if (g_Ball.framesSinceHit >= fieldingPractice_frameThresholds[4]) {
                    g_Practice.fieldingPlayStatus = 2;
                }
            } else if (g_Practice.practiceLevel == 3) {
                if (g_Ball.numberOfThrowsDuringPlay != 0) {
                    threshold = fieldingPractice_frameThresholds[5];
                    if (state == 0) {
                        if (g_FieldingLogic.fielderActionBeingProcessed == 2) {
                            g_Practice.guidedPracticeCounter++;
                        }
                        g_Practice.fieldingPlayStatus = 1;
                    }
                } else if (g_Ball.framesSinceBallHitGroundOrWasCaught >= fieldingPractice_frameThresholds[6]) {
                    g_Practice.fieldingPlayStatus = 2;
                }
            }
            if (g_Practice.guidedPracticeCounter >= guidedPracticeThresholds[g_Practice.practiceType_2][g_Practice.practiceLevel]) {
                g_Practice.guidedPracticeCompletionRelated = 1;
            }
            if (g_Practice.fieldingPlayStatus == 0) {
                return;
            }
        }
    }

    if (g_FieldingLogic.playOverCounter < 0x7FFE) {
        g_FieldingLogic.playOverCounter += 1;
    } else {
        g_FieldingLogic.playOverCounter = 0x7FFF;
    }
    if (g_Practice.guidedPracticeCompletionRelated != 0) {
        return;
    }
    if (g_FieldingLogic.playOverCounter >= threshold) {
        g_Practice.allowPlayToEndIndicator = 0;
        g_GameLogic.pre_PostMiniGameInd = 1;
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        g_GameLogic.hudLoadingRelated = 1;
        trackLastPitchInfo();
        SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
    } else if (g_FieldingLogic.playOverCounter == threshold - 6) {
        changeScene(3, 6);
    }
}

void fieldingPracticeEndPlay(void) {
    g_Practice.allowPlayToEndIndicator = 0;
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    g_GameLogic.hudLoadingRelated = 1;
    trackLastPitchInfo();
    SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
}

void fieldingPracticeSetPitcherConstants(void) {
    g_Pitcher.handedness = g_Fielders[0].throwingHandedness;
    g_Pitcher.curveBallSpeed = 0x7D;
    g_Pitcher.fastBallSpeed = 0x91;
    g_Pitcher.cursedBallStat = 0x64;
}

void fn_3_B0D78(void) {
}

void fieldingPracticeAISwingDecision(void) {
    if (g_Practice.aiBuntIndicator != 0) {
        return;
    }
    if (g_Pitcher.framesUntilUnhittable + 1 != swingSoundFrame[0][1]) {
        return;
    }
    g_AiLogic.batterAISwingInd = 1;
}

int batterAI_buntForPractice(void) {
    if (g_Practice.aiBuntIndicator == 0) {
        return 0;
    }
    return g_Ball.pitchHangtimeCounter > 0;
}

void fieldingPractice_setHitVariables(void) {
    int idx;

    if (g_Practice.hitVariablesSetIndicator != 0) {
        return;
    }
    g_Practice.frames_sincePlayStart++;
    if (g_Practice.frames_sincePlayStart < fieldingPractice_frameThresholds[0]) {
        return;
    }
    if (g_Practice.practiceLevel == 0) {
        idx = random_fn_3_9EE24(10);
        g_Ball.Hit_HorizontalPower = hitVarsForFieldingPractice[idx][0];
        g_Ball.Hit_VerticalAngle = hitVarsForFieldingPractice[idx][1];
        g_Ball.Hit_HorizontalAngle = hitVarsForFieldingPractice[idx][2];
    } else if (g_Practice.practiceLevel == 1) {
        idx = random_fn_3_9EE24(10);
        g_Ball.Hit_HorizontalPower = hitVarsForFieldingPractice_level1[idx][0];
        g_Ball.Hit_VerticalAngle = hitVarsForFieldingPractice_level1[idx][1];
        g_Ball.Hit_HorizontalAngle = hitVarsForFieldingPractice_level1[idx][2];
    } else if (g_Practice.practiceLevel == 2) {
        idx = random_fn_3_9EE24(10);
        g_Ball.Hit_HorizontalPower = hitVarsForFieldingPractice_level2[idx][0];
        g_Ball.Hit_VerticalAngle = hitVarsForFieldingPractice_level2[idx][1];
        g_Ball.Hit_HorizontalAngle = hitVarsForFieldingPractice_level2[idx][2];
    } else if (g_Practice.practiceLevel == 3) {
        idx = random_fn_3_9EE24(10);
        g_Ball.Hit_HorizontalPower = hitVarsForFieldingPractice_level3[idx][0];
        g_Ball.Hit_VerticalAngle = hitVarsForFieldingPractice_level3[idx][1];
        g_Ball.Hit_HorizontalAngle = hitVarsForFieldingPractice_level3[idx][2];
    }
    g_Practice.hitVariablesSetIndicator = 1;
    if (g_Practice.maybeCommandData[0] < 0x7FFE) {
        g_Practice.maybeCommandData[0]++;
    } else {
        g_Practice.maybeCommandData[0] = 0x7FFF;
    }
}

void battingPracticeControl(void) {
    switch (g_Practice.tutorialState) {
    case TUTORIAL_STATE_0:
        battingPracticeSwitcher();
        break;
    case TUTORIAL_STATE_1:
        battingPracticeSomething();
        break;
    case TUTORIAL_STATE_2:
        if (setUpPlayerTryingSkill() == 0) {
            battingPracticeSomething();
        } else {
            practiceStartGuidedMessage(g_Practice.practiceLevel + 4, 0);
            SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
        }
        break;
    case TUTORIAL_STATE_3:
        battingPracticeSomething();
        break;
    }
    g_GameLogic.TeamStars[1] = 5;
    g_GameLogic.TeamStars[0] = 5;
}

void battingPracticeResetTutorialState(void) {
    setTutorialState(TUTORIAL_STATE_0);
}

void battingPracticeSwitcher(void) {
    switch (g_Practice.practiceState) {
    case PRACTICE_STATE_0:
        hugeAnimStruct[0x307D] = 0;
        resetInMemRunners();
        if (g_Practice.practiceType_2 == PRACTICE_TYPE_FREEPLAY) {
            practice_loadCharacter(1, 0, g_Minigame.selectSlots[g_Practice.homeAway].charID,
                                   g_Minigame.battingHandedness[g_Practice.homeAway]);
            setInMemBatterConstants(0);
            initializeInMemRunner(0, 0);
        } else {
            setPitcherStatsToInMemPitcher(0);
            setFielderValues(0, 0);
            setInMemBatterConstants(0);
            initializeInMemRunner(0, 0);
        }
        g_GameLogic.currentBatterPerTeam[0] = 1;
        g_GameLogic.currentBatterPerTeam[1] = 1;
        animRelated[0x9A] = 0;
        animRelated[0x9C] = 0;
        highLevelSimulationFlag[2] = 0;
        g_Practice.characterLoadStarted = 0;
        fn_80011BE4(9);
        updatePracticeTransitionState(PRACTICE_STATE_1);
        break;
    case PRACTICE_STATE_1:
        if (loadRunnerActors() != 0) {
            updatePracticeTransitionState(PRACTICE_STATE_2);
        }
        break;
    case PRACTICE_STATE_2:
        if (g_Practice.practiceType_2 == PRACTICE_TYPE_FREEPLAY) {
            updatePracticeTransitionState(PRACTICE_STATE_3);
        } else if (loadPitcherActor() != 0) {
            updatePracticeTransitionState(PRACTICE_STATE_3);
        }
        break;
    case PRACTICE_STATE_3:
        if (someAnimationIndFunction() != 0) {
            updatePracticeTransitionState(PRACTICE_STATE_4);
        }
        break;
    case PRACTICE_STATE_4:
        if (practice_relatedToSettingCharacters() != 0) {
            updatePracticeTransitionState(PRACTICE_STATE_7);
        }
        break;
    case PRACTICE_STATE_5:
    case PRACTICE_STATE_6:
        break;
    case PRACTICE_STATE_7:
        practiceRelatedReset();
        if (g_Practice.practiceType_2 == PRACTICE_TYPE_FREEPLAY) {
            transitionToPlayerControl();
            setTutorialState(TUTORIAL_STATE_3);
        } else {
            practiceRelatedInit();
            g_Practice.commandList = practice_instructions_battingPtrs[g_Practice.practiceLevel];
            setTutorialState(TUTORIAL_STATE_1);
        }
        changeScene(1, 6);
        SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
        break;
    }
}

void battingPracticeSomething(void) {
    int skipRemainder;

    g_GameLogic.hudElementLoadingInd = 0;
    if (g_Practice.completionMenuActive != 0) {
        practiceLogicRelatedPause();
        return;
    }
    if (loadGuidedPractice() != 0) {
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
        if (g_Practice.pauseMenuLoading != 0) {
            skipRemainder = 0;
        } else if (g_Practice.guidedPracticeCompletionRelated == 0) {
            skipRemainder = 0;
        } else if (g_UnkSound_32718._07 != 0) {
            skipRemainder = 0;
        } else {
            g_Practice.frames_sincePracticeCompleted++;
            if (g_Practice.frames_sincePracticeCompleted > 0x96) {
                if (g_Practice.levelCompleted[g_Practice.practiceType_2][g_Practice.practiceLevel] == 0) {
                    g_Practice.progressNeedsSave = 1;
                    g_Practice.levelCompleted[g_Practice.practiceType_2][g_Practice.practiceLevel] = 1;
                    lbl_80354768[0xCF4E + g_Practice.practiceType_2 * 4 + g_Practice.practiceLevel] = 1;
                }
                g_Practice.completionMenuActive = 1;
                practiceResetPauseMenuState();
                practiceStartGuidedMessage(g_Practice.practiceLevel + 4, 1);
                skipRemainder = 1;
            } else {
                skipRemainder = 0;
            }
        }
        if (skipRemainder != 0) {
            return;
        }
    }

    if (g_Ball.totalFramesAtPlay < 0x7FFE) {
        g_Ball.totalFramesAtPlay++;
    } else {
        g_Ball.totalFramesAtPlay = 0x7FFF;
    }
    if (g_Practice.frames_sinceMovedToFromMenu < 0xFFFE) {
        g_Practice.frames_sinceMovedToFromMenu++;
    } else {
        g_Practice.frames_sinceMovedToFromMenu = 0xFFFF;
    }

    switch (g_GameLogic.gameStatus) {
    case GAME_STATUS_DEFAULT:
        battingPracticeRelated();
        break;
    case GAME_STATUS_AT_BAT:
        if (g_Practice.instructionNumber < 0) {
            if (practice_checkForPause() != 0) {
                break;
            }
        }
        atBat_Pitcher();
        atBat_batter();
        running_MainFunction();
        atBat_Fielders();
        break;
    case GAME_STATUS_LIVE_BALL:
        ballPhysica();
        fielderMainFunction();
        if (g_Ball.framesSinceHit == 0x3C) {
            g_Fielders[0].pos.x = g_Pitcher.pitcherCoord.x;
            g_Fielders[0].pos.z = g_Pitcher.pitcherCoord.z;
        }
        practiceRelatedPostPlay();
        if (g_Practice.instructionNumber < 0) {
            if (g_Practice.guidedPracticeCompletionRelated2 == 0) {
                guidedPracticeRelated();
            }
        }
        break;
    case GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY:
        resetBallValuesBetweenBatters();
        resetPitcherValuesBetweenBatters(0);
        setBatterContactConstants();
        initializeARunner();
        initializeMiniGameCharacters();
        betweenABSetPitcherBatter();
        initializeSomethingDuringTransition();
        initializeSomethingDuringTransition2();
        g_Strikes.strikes = 0;
        g_Strikes.balls = 0;
        g_GameLogic._125 = 1;
        g_GameLogic.pre_PostMiniGameInd = 1;
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        battingPracticeRelated();
        resetAndRunAnimations(0);
        break;
    default:
        break;
    }

    g_Strikes.strikes = 0;
    g_Strikes.balls = 0;
    g_Strikes.outs = 0;
}

BOOL battingPracticeUpdateCompletion(void) {
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
    if (g_Practice.frames_sincePracticeCompleted > 0x96) {
        if (g_Practice.levelCompleted[g_Practice.practiceType_2][g_Practice.practiceLevel] == 0) {
            g_Practice.progressNeedsSave = 1;
            g_Practice.levelCompleted[g_Practice.practiceType_2][g_Practice.practiceLevel] = 1;
            lbl_80354768[0xCF4E + g_Practice.practiceType_2 * 4 + g_Practice.practiceLevel] = 1;
        }
        g_Practice.completionMenuActive = 1;
        practiceResetPauseMenuState();
        practiceStartGuidedMessage(g_Practice.practiceLevel + 4, 1);
        return TRUE;
    }
    return FALSE;
}

void battingPracticePrepareNextPlay(void) {
    resetBallValuesBetweenBatters();
    resetPitcherValuesBetweenBatters(0);
    setBatterContactConstants();
    initializeARunner();
    initializeMiniGameCharacters();
    betweenABSetPitcherBatter();
    initializeSomethingDuringTransition();
    initializeSomethingDuringTransition2();
    g_Strikes.strikes = 0;
    g_Strikes.balls = 0;
    g_GameLogic._125 = 1;
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    battingPracticeRelated();
    resetAndRunAnimations(0);
}

void battingPracticeRelated(void) {
    practiceNewBatter();
    if (g_Practice.practiceLevel == 4) {
        g_Pitcher.windupCountdownUntilBallReleased = practiceFrameConsts[1];
    }
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
    if (g_GameLogic.pre_PostMiniGameInd != 0) {
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        g_GameLogic.hudElementLoadingInd = 1;
    } else {
        g_GameLogic.minigameLastTurnSuccessInd = 0;
    }
    g_GameLogic.pre_PostMiniGameInd = 0;
    g_GameLogic.minigameLastTurnSuccessInd = 0;
    g_Practice.guidedPracticeCompletionRelated2 = 0;
    g_Practice.homeRunWaitSkipped = 0;
    changeScene(1, 6);
    SetGameStatus(GAME_STATUS_AT_BAT);
    setDefaultPlayTrackingVariables2();
    if (sound_crowd_EffectsStruct._2A != 0) {
        sound_crowd_EffectsStruct._2A = 2;
        sound_crowd_EffectsStruct._24 = 0x78;
    }
}

void someBattingPitchingCallFuns(void) {
    if (g_Practice.instructionNumber < 0) {
        if (practice_checkForPause() != 0) {
            return;
        }
    }
    atBat_Pitcher();
    atBat_batter();
    running_MainFunction();
    atBat_Fielders();
}

void battingPracticeLiveBall(void) {
    ballPhysica();
    fielderMainFunction();
    if (g_Ball.framesSinceHit == 0x3C) {
        g_Fielders[0].pos.x = g_Pitcher.pitcherCoord.x;
        g_Fielders[0].pos.z = g_Pitcher.pitcherCoord.z;
    }
    practiceRelatedPostPlay();
    if (g_Practice.instructionNumber < 0) {
        if (g_Practice.guidedPracticeCompletionRelated2 == 0) {
            guidedPracticeRelated();
        }
    }
}

void guidedPracticeRelated(void) {
    if (g_Practice.practiceType_2 == PRACTICE_TYPE_FREEPLAY) {
        return;
    }
    if (g_Practice.guidedPracticeCompletionRelated2 != 0) {
        return;
    }
    if (g_Ball.deadBallReason != 0) {
        if (g_Ball.framesOnGroundUntilPickedUp == 0 && g_Practice.homeRunWaitSkipped == 0) {
            if (g_Ball.matchFramesAndBallAngle.ballOverWallFrames < battingPractice_resultDelayFrames[0]) {
                return;
            }
        }
    } else {
        if (g_Ball.framesSinceBallHitGroundOrWasCaught < battingPractice_resultDelayFrames[0]) {
            return;
        }
    }

    switch (g_Practice.practiceLevel) {
    case 0:
        if (g_Batter.hitGeneralType != 3) {
            g_Practice.guidedPracticeCounter++;
        }
        break;
    case 1:
        if (g_Batter.hitGeneralType == 1 || (g_Batter.hitGeneralType == 2 && g_Batter.moonShotInd != 0)) {
            g_Practice.guidedPracticeCounter++;
        }
        break;
    case 2:
        if (g_Batter.hitGeneralType == 3) {
            g_Practice.guidedPracticeCounter++;
        }
        break;
    case 3:
        if (g_Batter.hitGeneralType == 2) {
            if (g_Batter.moonShotInd == 0) {
                g_Practice.guidedPracticeCounter++;
            }
        }
        break;
    }
    if (g_Practice.guidedPracticeCounter >= guidedPracticeThresholds[g_Practice.practiceType_2][g_Practice.practiceLevel]) {
        g_Practice.guidedPracticeCompletionRelated = 1;
    }
    g_Practice.guidedPracticeCompletionRelated2 = 1;
}

void practiceRelatedPostPlay(void) {
    InputStruct *controls;
    s16 frames;

    controls = &g_Controls[g_Practice.homeAway];
    frames = 120;
    if (g_Practice.instructionNumber >= 0) {
        if (g_Practice.allowPlayToEndIndicator != 0) {
            frames = 60;
        } else {
            g_FieldingLogic.playOverCounter = 0;
            return;
        }
    } else {
        if (g_Ball.AtBat_ContactResult == 0) {
            g_FieldingLogic.playOverCounter = 0;
            return;
        }
        if (g_Practice.guidedPracticeCompletionRelated != 0) {
            g_FieldingLogic.playOverCounter = 0;
            return;
        }
        if (g_Ball.deadBallReason == 1) {
            if (g_Practice.homeRunWaitSkipped == 0) {
                if ((controls->newButtonInput & (INPUT_BUTTON_A | INPUT_BUTTON_START)) != 0) {
                    g_Practice.homeRunWaitSkipped = 1;
                }
                frames = 300;
            } else {
                frames = 45;
            }
            sound_crowd_EffectsStruct._2A = 1;
            sound_crowd_EffectsStruct._24 = 0x1E;
        } else if (g_Ball.framesSinceHit > 0xB4) {
            frames = 120;
        }
    }

    if (g_FieldingLogic.playOverCounter < 0x7FFE) {
        g_FieldingLogic.playOverCounter += 1;
    } else {
        g_FieldingLogic.playOverCounter = 0x7FFF;
    }
    if (g_GameLogic.framePlayEnd > frames) {
        if (g_FieldingLogic.playOverCounter > frames - 0x5A) {
            g_FieldingLogic.playOverCounter = 0;
            g_FieldingLogic.framesSincePlayEnded = 0;
        }
    }
    if (g_FieldingLogic.playOverCounter >= frames) {
        g_Practice.allowPlayToEndIndicator = 0;
        g_GameLogic.pre_PostMiniGameInd = 1;
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        trackLastPitchInfo();
        SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
    } else if (g_FieldingLogic.playOverCounter >= frames - 6) {
        changeScene(3, 6);
    } else if (g_FieldingLogic.playOverCounter == frames - 0x1E) {
        g_FieldingLogic.playOverInd = 1;
        g_FieldingLogic.framesSincePlayEnded = 1;
    }
    g_GameLogic.framePlayEnd = frames;
    g_GameLogic.CountdownUntilFade = frames - g_FieldingLogic.playOverCounter;
}

void battingPracticeEndPlay(void) {
    g_Practice.allowPlayToEndIndicator = 0;
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    trackLastPitchInfo();
    SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
}
