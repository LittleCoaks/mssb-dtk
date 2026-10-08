#define SQRT2_LINKAGE static
#include "game/practice/practice_scene.h"
#define REP_HEADER_DATA_FN getRepHeaderData_practiceScene
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/hud/hud_gauges.h"
#include "game/hud/hud_scoreboard.h"
#include "game/hud/rep_3448.h"
#include "game/hud/toyfield_score_update.h"
#include "game/match_setup/match_flow.h"
#include "game/match_setup/match_scene.h"
#include "game/minigame/minigame_effects.h"
#include "game/pitching/pitcher.h"
#include "game/baserunning/runner.h"
#include "game/ball/ball_physics.h"
#include "game/fielding/fielder.h"
#include "game/sound/m_sound.h"
#include "text/text_block.h"
#include "text/text_channel.h"
#include "Unknown/File_0x80014d4c.h"
#include "Unknown/File_0x80021410.h"
#include "Unknown/File_0x80033794.h"
#include "Unknown/File_0x80034cec.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x8004cc18.h"
#include "Unknown/File_0x800363d8.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x8004e5b4.h"
#include "game/match_setup/pause_menu.h"

extern u8 animRelated[0x124];
extern u8 menuNumber[0x28];
extern u8 lbl_800FEF70[0x5D0];
extern u8 hugeAnimStruct[0x3154];
extern u8 constantList[0x1C];
extern u8 guidedPracticeThresholds[][4];
extern s16 practiceGoalHud_entries[4][4][4][2];
extern s16 practiceGuidedMessage_textIds[16][2][3];
extern UIRecordDescriptor practiceGoalHud_uiRecords[];
extern UIRecordDescriptor practiceCompleteBanner_uiRecords[];
extern UIRecordDescriptor practiceGuidedMessage_uiRecords[];
extern UIRecordDescriptor practiceMenu_charSelect_uiRecords[];
extern UIRecordDescriptor practiceMenu_subMenu_uiRecords[];
extern UIRecordDescriptor practiceInstruction_uiRecords[];
extern UIRecordDescriptor practiceMenu_typeIcons_uiRecords[];
extern s16 practiceMenu_subMenuTextIds[][4];
extern u16 practiceInstruction_diagramElements[];
extern u16 practiceMenu_typeIconFrames[];
extern u16 practiceMenu_typeTitleElements[];
extern u8 practiceMenu_typeIconOrder[];
extern u8 charSelect_handednessIconFrames[];
extern u8 lbl_3_data_9D50[][5];
extern s16 practiceFrameConsts;

extern void fn_8000F8F4(void* scene);
extern void fn_80011BE4(int arg0);
extern void fn_8004D0F0(void);
extern void fn_80050F78(int arg0);
extern void fn_80051D00(void);
extern void fn_80053FE8(void);
extern void matchTransitionFunction2(void);
extern void practiceRelatedReset(void);
extern void practice_loadCharacter(int arg0, int arg1, int arg2, int arg3);
extern BOOL practice_loadAllGraphics(int team);
extern BOOL practice_relatedToSettingCharacters(void);
extern void setTutorialState(int state);
extern void updatePracticeTransitionState(int state);

/* A drawing-script node created by one of the practice HUD scenes; its
 * records are graphicsRelatedArray[firstHandle + n]. Each scene's func keeps
 * its own state in the words from +0x18 on. */
typedef struct PracticeScene {
    /* 0x00 */ u8 _00[0x14];
    /* 0x14 */ u16 firstHandle;
    /* 0x16 */ u16 handleCount;
    /* 0x18 */ u16 _18;
    /* 0x1A */ u16 _1A;
    union {
        struct {
            /* 0x1C */ u16 _1C;
            /* 0x1E */ u16 _1E;
            /* 0x20 */ u16 _20;
            /* 0x22 */ u16 _22;
        };
        u16 channels[4];
    };
} PracticeScene;

#define PRACTICE_RECORD(scene, i) ((UIRecord*)graphicsRelatedArray[(scene)->firstHandle + (i)].object)
#define PRACTICE_RECORD_PLUS(scene, i, k) ((UIRecord*)graphicsRelatedArray[(scene)->firstHandle + (i) + (k)].object)
#define PRACTICE_RECORD_AT(scene, base, i) ((UIRecord*)graphicsRelatedArray[(scene)->firstHandle + (base) + (i)].object)

void freeFieldingPracticeControl(void) {
    switch (g_Practice.tutorialState) {
    case TUTORIAL_STATE_0:
        freeFieldingPracticeSwitcher();
        break;
    case TUTORIAL_STATE_3:
        unused_matchSimulationRelated();
        break;
    }
}

void freeFieldingPracticeSwitcher(void) {
    switch (g_Practice.practiceState) {
    case PRACTICE_STATE_0:
        hugeAnimStruct[0x2D77] = 0;
        hugeAnimStruct[0x2D7B] = 0;
        hugeAnimStruct[0x2D7C] = 0;
        animRelated[0x9C] = 0;
        g_Practice.characterLoadStarted = 0;
        g_Practice.completionMenuActive = 0;
        hugeAnimStruct[0x307D] = 0;
        freeFieldingPracticeLoadCharacters();
        fieldingPractice_resetMem();
        fn_80011BE4(9);
        updatePracticeTransitionState(PRACTICE_STATE_1);
        break;
    case PRACTICE_STATE_1:
        if (practice_loadAllGraphics(g_GameLogic.teamFielding)) {
            updatePracticeTransitionState(PRACTICE_STATE_2);
        }
        break;
    case PRACTICE_STATE_2:
        if (loadPitcherActor()) {
            updatePracticeTransitionState(PRACTICE_STATE_3);
        }
        break;
    case PRACTICE_STATE_3: {
        int team = g_GameLogic.homeTeamBattingInd_fieldingTeam;
        int batter = g_GameLogic.currentBatterPerTeam[team];

        if (loadSomethingFromDiskAtBeginningOfAB1(
                inMemRoster[g_GameLogic.teamBatting][g_GameLogic.battingOrderAndPositionMapping[team][batter][0]].stats.CharID)) {
            updatePracticeTransitionState(PRACTICE_STATE_4);
        }
        break;
    }
    case PRACTICE_STATE_4:
        if (practice_relatedToSettingCharacters()) {
            updatePracticeTransitionState(PRACTICE_STATE_7);
        }
        break;
    case PRACTICE_STATE_5:
    case PRACTICE_STATE_6:
        break;
    case PRACTICE_STATE_7:
        practiceRelatedReset();
        g_GameLogic.freeFieldingPracticeInd = 1;
        g_GameLogic.TeamStars[0] = 5;
        g_GameLogic.TeamStars[1] = 5;
        SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
        setTutorialState(TUTORIAL_STATE_3);
        break;
    }
}

void freeFieldingPracticeLoadCharacters(void) {
    int i;
    int j;

    i = 0;
    do {
        practice_loadCharacter(0, i, constantList[i + 9], -1);
        if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_FREE_FIELDING) {
            practice_loadCharacter(1, i, constantList[i + 0x12], -1);
        } else {
            practice_loadCharacter(1, i, constantList[i], -1);
        }
        i++;
    } while (i < 9);

    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_FREE_BAT_AND_RUNNING) {
        MinigameSelectSlot* slots = g_Minigame.selectSlots;

        if (slots[g_Practice.homeAway].charID == CHAR_ID_LUIGI) {
            practice_loadCharacter(0, 0, 0, -1);
        } else {
            practice_loadCharacter(0, 0, 1, -1);
        }
        practice_loadCharacter(1, 0, slots[g_Practice.homeAway].charID, g_Minigame.battingHandedness[g_Practice.homeAway]);
    } else {
        BOOL found;

        practice_loadCharacter(0, 0, g_Minigame.selectSlots[g_Practice.homeAway].charID, g_Minigame.battingHandedness[g_Practice.homeAway]);
        found = FALSE;
        for (j = 1; j < 9; j++) {
            if (g_Minigame.selectSlots[g_Practice.homeAway].charID == inMemRoster[0][j].stats.CharID) {
                practice_loadCharacter(0, j, 0x2E, -1);
                found = TRUE;
                break;
            }
        }
        if (!found) {
            for (j = 0; j < 9; j++) {
                if (inMemRoster[1][j].stats.CharID == g_Minigame.selectSlots[g_Practice.homeAway].charID) {
                    if (j == 0 || j == 1 || j == 8) {
                        practice_loadCharacter(1, j, 3, -1);
                    } else if (j == 2 || j == 3 || j == 4) {
                        practice_loadCharacter(1, j, 0x13, -1);
                    } else {
                        practice_loadCharacter(1, j, 0x11, -1);
                    }
                    break;
                }
            }
        }
    }
}

void fieldingPractice_resetMem(void) {
    g_GameLogic.teamIsCPU[0] = 0;
    g_GameLogic._140[0] = 0;
    g_GameLogic.teamAIInd[0] = 0;
    g_GameLogic.autoFielding[0] = 0;
    g_GameLogic.batterHandedness[0] = 0;
    g_GameLogic.battingAIInd[0] = 0;
    g_GameLogic.teamIsCPU[1] = 0;
    g_GameLogic._140[1] = 0;
    g_GameLogic.teamAIInd[1] = 0;
    g_GameLogic.autoFielding[1] = 0;
    g_GameLogic.batterHandedness[1] = 0;
    g_GameLogic.battingAIInd[1] = 0;
    g_Practice.aIEnabled = 0;
    g_Practice.practiceBatterHandedness = 0;
    g_Practice.freePracticeInd_writeOnly = 0;
    g_Practice.freeFieldingInd_writeOnly = 0;
    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_FREE_BAT_AND_RUNNING) {
        g_Practice.aIEnabled = 1;
        g_GameLogic.teamIsCPU[g_GameLogic.teamFielding] = 1;
        g_Practice.freePracticeInd_writeOnly = 1;
        g_GameLogic._140[g_GameLogic.awayTeamBattingInd_battingTeam] = 1;
        g_Practice.rosterID = 1;
        g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam] = 1;
        g_GameLogic.autoFielding[g_GameLogic.awayTeamBattingInd_battingTeam] = 1;
    } else {
        g_Practice.practiceBatterHandedness = 1;
        g_GameLogic.teamIsCPU[g_GameLogic.teamBatting] = 1;
        g_Practice.freeFieldingInd_writeOnly = 1;
        g_GameLogic.batterHandedness[g_GameLogic.homeTeamBattingInd_fieldingTeam] = 1;
        g_GameLogic.battingAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam] = 1;
    }
    g_Practice.frames_sincePracticeCompleted = 0;
    resetCount();
    resetInMemRunners();
    resetInMemBall();
    resetInMemPitcher();
    resetInMemFielders();
    g_GameLogic.EventTriggers_GameHasStarted = 0;
    g_GameLogic.currentBatterPerTeam[0] = 1;
    g_GameLogic.currentBatterPerTeam[1] = 1;
}

void unused_matchSimulationRelated(void) {
    g_GameLogic.hudElementLoadingInd = 0;
    g_GameLogic.hudLoadingRelated = 0;
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
        newPitch();
        break;
    case GAME_STATUS_AT_BAT:
        atBatScreen();
        break;
    case GAME_STATUS_LIVE_BALL:
        freePracticeSomething();
        break;
    case GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY:
        matchTransitionPrepareNextAB();
        if (g_GameLogic.FrameCountOfCurrentPitch == 1) {
            practiceRelated();
        }
        break;
    case GAME_STATUS_TRANSITION:
        freeFieldingPracticeTransition();
        break;
    case GAME_STATUS_0xA:
        fn_3_5CD24();
        break;
    }
    if (g_Practice.practiceLevel != 7 && g_Practice.practiceLevel != 6) {
        g_Strikes.outs = 0;
    }
}

#pragma dont_inline on
void practiceRelated(void) {
    int slots[4];
    int i;
    int j;

    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_FREE_BAT_AND_RUNNING) {
        slots[0] = 1;
        slots[1] = 2;
        slots[2] = 3;
        slots[3] = 4;
        for (i = 0; i < 4; i++) {
            for (j = 1; j < 4; j++) {
                if (g_Runners[j].rosterID == slots[i]) {
                    slots[i] = -1;
                }
            }
        }
        for (i = 0; i < 4; i++) {
            if (slots[i] >= 0) {
                g_Practice.rosterID = slots[i];
                break;
            }
        }
    }
    if (g_GameLogic.TeamStars[0] == 0) {
        g_GameLogic.TeamStars[0] = 5;
    }
    if (g_GameLogic.TeamStars[1] == 0) {
        g_GameLogic.TeamStars[1] = 5;
    }
    if (g_Strikes.outs >= 3) {
        g_Strikes.outs = 0;
    }
    g_Practice.guidedPracticeCompletionRelated = 0;
}
#pragma dont_inline reset

void freeFieldingPracticeTransition(void) {
    matchTransitionFunction2();
    g_GameLogic.writeOnly_always0 = 0;
    g_GameLogic.writeOnly_always0_2 = 0;
    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_FREE_BAT_AND_RUNNING) {
        if (g_Strikes.outs >= 3) {
            g_Strikes.outs = 0;
        }
    }
    SetGameStatus(GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY);
}

void practice_startPitchAfter90Frames(void) {
    if (g_Pitcher.currentStateFrameCounter > practiceFrameConsts) {
        pitcherAITransitionFromPrePitchToWindup(2);
    }
}

void animatePracticeScene(void) {
    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_RETURN_TO_MENU || g_GameLogic.framesOfExitingToMenu != 0) {
        return;
    }
    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_MENU) {
        animRelated[0xA7] = 0;
        animationOrDrawingRelated();
        return;
    }
    if ((g_Practice.practiceType_2 == PRACTICE_TYPE_PITCHING || g_Practice.practiceType_2 == PRACTICE_TYPE_BATTING || g_Practice.practiceType_2 == PRACTICE_TYPE_FIELDING ||
         g_Practice.practiceType_2 == PRACTICE_TYPE_BASERUNNING) &&
        g_Practice.tutorialState == TUTORIAL_STATE_0 && g_Practice.practiceState == PRACTICE_STATE_7) {
        insertGraphicDrawingFunction(practiceInstruction_init, 2);
    }
    if (g_Practice.completionMenuActive != 0) {
        if (g_Practice.frames_onPauseScreen == 1) {
            insertGraphicDrawingFunction(pauseOptionList_init, 2);
        }
    } else if (g_Practice.pauseMenuActive != 0) {
        if (pauseControl.state == 1 && g_Practice.frames_onPauseScreen2 == 1) {
            if (animRelated[0xAA] == 0) {
                insertGraphicDrawingFunction(pauseSubPanel_init, 2);
            }
            insertGraphicDrawingFunction(pauseOptionList_init, 2);
        }
        if (pauseControl.state == 3 && pauseControl._1D3 == 3) {
            insertGraphicDrawingFunction(pausePageIndicator_init, 2);
        }
    }
    if (g_Practice.loadingGuidedPractice != 0 && g_Practice.guidedMessageSceneStarted == 0) {
        insertGraphicDrawingFunction(practiceGuidedMessage_init, 2);
        g_Practice.guidedMessageSceneStarted = 1;
    }
    manageEventStates();
    if (g_Practice.practiceType_2 == PRACTICE_TYPE_FREEPLAY || g_Practice.practiceType_2 == PRACTICE_TYPE_BASERUNNING) {
        if (g_Practice.practiceLevel != 4 && g_Practice.practiceLevel != 5) {
            toyfield_hud_turns_diamondMap();
        }
    }
    practice_drawHud();
    if (g_Practice.practiceLevel == 7 || g_Practice.practiceLevel == 6) {
        hud_ScoreUpdate_ToyFieldOffScreenPlayers();
    }
    practice_insertGoalHudScenes();
}

void practice_drawHud(void) {
    if (g_GameLogic.hudElementLoadingInd != 0 && animRelated[0xA5] == 0 && g_Practice.instructionNumber < 0) {
        u8 level = g_Practice.practiceLevel;

        animRelated[0xA5] = 1;
        animRelated[0xA6] = 0;
        animRelated[0xA7] = 0xFF;
        if (level == 4) {
            insertGraphicDrawingFunction(fn_3_9976C, 2);
        } else if (level == 5) {
            insertGraphicDrawingFunction(fn_3_99BDC, 2);
        } else if (g_Practice.practiceType_2 == PRACTICE_TYPE_FREEPLAY) {
            insertGraphicDrawingFunction(init_BallStrikeOutHud, 2);
            insertGraphicDrawingFunction(draw_initStarGuageHud, 2);
        } else if (g_Practice.practiceType_2 == PRACTICE_TYPE_PITCHING) {
            if (level == 1) {
                insertGraphicDrawingFunction(fn_3_99BDC, 2);
            }
        } else if (g_Practice.practiceType_2 == PRACTICE_TYPE_BATTING) {
            if (level == 1) {
                insertGraphicDrawingFunction(fn_3_9976C, 2);
            }
        }
    }
    if (animRelated[0xA5] != 0 && animRelated[0xA6] < 0xFF) {
        if (animRelated[0xA6] < 0xF0) {
            animRelated[0xA6] += 0x10;
        } else {
            animRelated[0xA6] = 0xFF;
        }
    }
    if (animRelated[0xA7] != 0 && animRelated[0xA7] < 0xFF) {
        if (animRelated[0xA7] <= 0x10) {
            animRelated[0xA7] = 0;
            animRelated[0xA5] = 0;
        } else {
            animRelated[0xA7] -= 0x10;
        }
    } else if (animRelated[0xA5] != 0) {
        if (g_GameLogic.gameStatus != GAME_STATUS_AT_BAT && g_GameLogic.gameStatus != GAME_STATUS_DEFAULT &&
            g_GameLogic.gameStatus != GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY) {
            animRelated[0xA7] = 0xF0;
        }
        if (pauseControl._1D5 != 0) {
            animRelated[0xA7] = 0xF0;
        }
        if (g_Practice.pauseMenuActive != 0) {
            if (pauseControl.state == 7 || pauseControl.state == 9 || pauseControl.state == 0xB) {
                animRelated[0xA7] = 0;
                animRelated[0xA5] = 0;
            }
        }
        if (g_Practice.completionMenuActive != 0) {
            if (pauseControl.state == 5 || pauseControl.state == 0xB || pauseControl.state == 7) {
                animRelated[0xA7] = 0;
                animRelated[0xA5] = 0;
            }
        }
    }
    if (g_GameLogic.gameStatus == GAME_STATUS_TRANSITION) {
        animRelated[0xA7] = 0;
        animRelated[0xA5] = 0;
    }
}

void animationOrDrawingRelated(void) {
    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_MENU) {
        if (animRelated[0xD9] == 0 && g_GameLogic.framesOfExitingToMenu == 0) {
            insertGraphicDrawingFunction(fn_3_12C3F0, 2);
            insertGraphicDrawingFunction(fn_80053FE8, 2);
            menuNumber[0] = 0x3C;
            menuNumber[9] = menuNumber[8];
            menuNumber[8] = *(u16*)&lbl_800FEF70[0x3C8];
        }
        if (g_Practice.practiceType_1 == 0) {
            if (g_Practice.practiceState == PRACTICE_STATE_2) {
                if (animRelated[0xC0] == 0) {
                    insertGraphicDrawingFunction(practiceMenu_typeIcons_init, 2);
                }
                if (animRelated[0xBC] == 0) {
                    insertGraphicDrawingFunction(fn_3_12BFE8, 2);
                }
                menuNumber[0] = 0x3C;
                menuNumber[9] = menuNumber[8];
                menuNumber[8] = *(u16*)&lbl_800FEF70[0x3C8];
            }
            if (g_Practice.practiceState == PRACTICE_STATE_7 && g_Practice.framesSincePracticeMenuDefaultTransition == 1) {
                fn_8004CC4C(0, 1, 1, 0, 0x89);
                insertGraphicDrawingFunction(fn_8004D0F0, 2);
            }
        }
        if ((g_Practice.practiceType_1 == 1 || g_Practice.practiceType_1 == 2 || g_Practice.practiceType_1 == 3 ||
             g_Practice.practiceType_1 == 4 || g_Practice.practiceType_1 == 5) &&
            g_Practice.practiceState == PRACTICE_STATE_0) {
            if (animRelated[0xC0] == 0) {
                insertGraphicDrawingFunction(practiceMenu_typeIcons_init, 2);
            }
            if (animRelated[0xC1] == 0) {
                insertGraphicDrawingFunction(practiceMenu_subMenu_init, 2);
            }
            if (animRelated[0xBC] == 0) {
                insertGraphicDrawingFunction(fn_3_12BFE8, 2);
            }
            menuNumber[0] = 0x3D;
            menuNumber[9] = menuNumber[8];
            menuNumber[8] = *(u16*)&lbl_800FEF70[0x3D8];
        }
    }
    if (g_Practice.practiceType_1 == 6) {
        if (g_Practice.practiceState == PRACTICE_STATE_1 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
            if (animRelated[0xC1] == 0) {
                animRelated[0xC2] = 1;
                insertGraphicDrawingFunction(practiceMenu_subMenu_init, 2);
            }
            insertGraphicDrawingFunction(fn_80051D00, 2);
            insertGraphicDrawingFunction(practiceMenu_charSelect_init, 2);
            menuNumber[0] = 0x3E;
            menuNumber[9] = menuNumber[8];
            menuNumber[8] = *(u16*)&lbl_800FEF70[0x3E8];
        }
        if (g_Practice.practiceState == PRACTICE_STATE_5) {
            fn_80050F78(0);
        }
        if (g_Practice.practiceState == PRACTICE_STATE_4) {
            fn_80050F78(1);
        }
    }
}

void practiceMenu_typeIcons_init(void) {
    PracticeScene* scene = (PracticeScene*)currentDrawingItem;
    int i;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, practiceMenu_typeIcons_uiRecords);
    for (i = 0; i < 5; i++) {
        PRACTICE_RECORD_PLUS(scene, i, 6)->frame = practiceMenu_typeIconFrames[practiceMenu_typeIconOrder[i]] << 16;
    }
    scene->_1C = 1;
    if (g_Practice.practiceType_1 == 1 || g_Practice.practiceType_1 == 2 || g_Practice.practiceType_1 == 3 ||
        g_Practice.practiceType_1 == 4 || g_Practice.practiceType_1 == 5) {
        PRACTICE_RECORD(scene, 0)->elementIndex = practiceMenu_typeTitleElements[g_Practice.practiceType];
        PRACTICE_RECORD(scene, 0)->frame = 0x32 << 16;
        PRACTICE_RECORD(scene, 0)->playMode = UI_PLAY_BACKWARD;
        PRACTICE_RECORD_AT(scene, 1, g_Practice.practiceType)->frame = 0x69 << 16;
        PRACTICE_RECORD_AT(scene, 0xB, g_Practice.practiceType)->frame = 0x69 << 16;
        scene->_1C = 5;
    }
    animRelated[0xC0] = 1;
    currentDrawingItem->func = practiceMenu_typeIcons_update;
}

void practiceMenu_typeIcons_update(void) {
    PracticeScene* scene = (PracticeScene*)currentDrawingItem;
    int i;

    if (animRelated[0x96] == 0 && g_Practice.practiceType_1 != 6 &&
        g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_MENU) {
        if (scene->_1C == 1) {
            UIRecord* record = PRACTICE_RECORD(scene, 0);

            if ((record->frame >> 16) >= 0x19) {
                record->playMode = UI_PLAY_STOP;
                scene->_1C = 2;
            }
        } else if (scene->_1C == 2) {
            for (i = 0; i < 5; i++) {
                if (g_Practice.practiceType == i) {
                    UIRecord* record = PRACTICE_RECORD_PLUS(scene, i, 1);

                    if ((record->frame >> 16) < 0x5A) {
                        record->playMode = UI_PLAY_FORWARD;
                        PRACTICE_RECORD_PLUS(scene, i, 0xB)->playMode = UI_PLAY_FORWARD;
                    } else {
                        record->frame = 0xA << 16;
                        PRACTICE_RECORD_PLUS(scene, i, 0xB)->frame = 0xA << 16;
                    }
                } else {
                    UIRecord* record = PRACTICE_RECORD_PLUS(scene, i, 1);
                    u32 frame = record->frame >> 16;

                    if (frame > 0xA) {
                        record->frame = 0xA << 16;
                        PRACTICE_RECORD_PLUS(scene, i, 1)->playMode = UI_PLAY_BACKWARD;
                        PRACTICE_RECORD_PLUS(scene, i, 0xB)->frame = 0xA << 16;
                        PRACTICE_RECORD_PLUS(scene, i, 0xB)->playMode = UI_PLAY_BACKWARD;
                    } else if (frame != 0) {
                        record->playMode = UI_PLAY_BACKWARD;
                        PRACTICE_RECORD_PLUS(scene, i, 0xB)->playMode = UI_PLAY_BACKWARD;
                    } else {
                        record->playMode = UI_PLAY_STOP;
                        PRACTICE_RECORD_PLUS(scene, i, 0xB)->playMode = UI_PLAY_STOP;
                    }
                }
            }
            if (g_Practice.practiceState == PRACTICE_STATE_5) {
                PRACTICE_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
                PRACTICE_RECORD(scene, 0)->elementIndex = practiceMenu_typeTitleElements[g_Practice.practiceType];
                PRACTICE_RECORD_AT(scene, 1, g_Practice.practiceType)->playMode = UI_PLAY_FORWARD;
                PRACTICE_RECORD_AT(scene, 1, g_Practice.practiceType)->frame = 0x5A << 16;
                PRACTICE_RECORD_AT(scene, 0xB, g_Practice.practiceType)->playMode = UI_PLAY_FORWARD;
                PRACTICE_RECORD_AT(scene, 0xB, g_Practice.practiceType)->frame = 0x5A << 16;
                scene->_1C = 3;
            }
        } else if (scene->_1C == 3) {
            UIRecord* record = PRACTICE_RECORD(scene, 0);

            if ((record->frame >> 16) >= 0x28) {
                record->playMode = UI_PLAY_STOP;
            }
            if (g_Practice.practiceType_1 == 1 || g_Practice.practiceType_1 == 2 || g_Practice.practiceType_1 == 3 ||
                g_Practice.practiceType_1 == 4 || g_Practice.practiceType_1 == 5) {
                if (g_Practice.practiceState == PRACTICE_STATE_3) {
                    if (g_Practice.practiceType_2 == PRACTICE_TYPE_FREEPLAY) {
                        PRACTICE_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
                        scene->_1C = 9;
                    }
                } else if (g_Practice.practiceState == PRACTICE_STATE_6) {
                    PRACTICE_RECORD(scene, 0)->playMode = UI_PLAY_BACKWARD;
                    PRACTICE_RECORD_AT(scene, 1, g_Practice.practiceType)->playMode = UI_PLAY_BACKWARD;
                    PRACTICE_RECORD_AT(scene, 0xB, g_Practice.practiceType)->playMode = UI_PLAY_BACKWARD;
                    scene->_1C = 4;
                }
            }
        } else if (scene->_1C == 4) {
            UIRecord* record = PRACTICE_RECORD(scene, 0);
            int count = 0;

            if ((record->frame >> 16) <= 0x19) {
                record->playMode = UI_PLAY_STOP;
                count = 1;
            }
            record = PRACTICE_RECORD_AT(scene, 1, g_Practice.practiceType);
            if ((record->frame >> 16) <= 0x5A) {
                record->playMode = UI_PLAY_STOP;
                count++;
                PRACTICE_RECORD_AT(scene, 0xB, g_Practice.practiceType)->playMode = UI_PLAY_STOP;
            }
            if (count >= 2) {
                scene->_1C = 2;
            }
        } else if (scene->_1C == 5) {
            UIRecord* record = PRACTICE_RECORD(scene, 0);

            if ((record->frame >> 16) <= 0x28) {
                record->playMode = UI_PLAY_STOP;
                scene->_1C = 3;
            }
        }
    } else {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        animRelated[0xC0] = 0;
    }
}

void practiceMenu_subMenu_init(void) {
    PracticeScene* scene = (PracticeScene*)currentDrawingItem;
    int i;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, practiceMenu_subMenu_uiRecords);
    scene->_1C = 0xFFFF;
    scene->_1E = 0xFFFF;
    scene->_20 = 0xFFFF;
    scene->_22 = 0xFFFF;
    i = 0;
    do {
        load_Icon(scene, i + 2, 1, 0x77, i);
        load_Icon(scene, i + 2, 2, 0x77, i + 4);
        if (g_Practice.practiceType_1 == 5 || g_Practice.practiceType_1 == 6) {
            PRACTICE_RECORD_AT(scene, 0xA, i)->flags &= ~UI_FLAG_VISIBLE;
        } else if (g_Practice.levelCompleted[g_Practice.practiceType_2][i] == 0) {
            PRACTICE_RECORD_AT(scene, 0xA, i)->flags &= ~UI_FLAG_VISIBLE;
        }
        scene->channels[i] = text_initializeNewChannel((UnkText988Arg*)scene, 0xE + i, (u16)i, 5, practiceMenu_subMenuTextIds[g_Practice.practiceType_2][i], 0);
        i++;
    } while (i < 4);
    for (; i < 4; i++) {
        PRACTICE_RECORD_AT(scene, 2, i)->flags &= ~UI_FLAG_VISIBLE;
        PRACTICE_RECORD_AT(scene, 6, i)->flags &= ~UI_FLAG_VISIBLE;
        PRACTICE_RECORD_AT(scene, 0xE, i)->flags &= ~UI_FLAG_VISIBLE;
        PRACTICE_RECORD_AT(scene, 0xA, i)->flags &= ~UI_FLAG_VISIBLE;
    }
    scene->_18 = 0;
    if (animRelated[0xC2] != 0) {
        scene->_18 = 2;
        PRACTICE_RECORD(scene, 0)->frame = 0xF << 16;
    }
    animRelated[0xC1] = 1;
    scene->_1A = 0;
    currentDrawingItem->func = practiceMenu_subMenu_update;
}

void practiceMenu_subMenu_update(void) {
    PracticeScene* scene = (PracticeScene*)currentDrawingItem;
    UIRecord* record;
    int i;

    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_MENU &&
        (g_Practice.practiceType_1 == 1 || g_Practice.practiceType_1 == 2 || g_Practice.practiceType_1 == 3 ||
         g_Practice.practiceType_1 == 4 || g_Practice.practiceType_1 == 5 || g_Practice.practiceType_1 == 6)) {
        if (scene->_18 == 0) {
            scene->_18 = 1;
        } else if (scene->_18 == 1) {
            int frame = PRACTICE_RECORD(scene, 0)->frame >> 16;

            if (frame >= 0xF) {
                scene->_18 = 2;
            }
        } else if (scene->_18 == 2) {
            scene->_1A += 0x20;
            if (scene->_1A > 0xFF) {
                scene->_1A = 0xFF;
            }
            for (i = 0; i < 4; i++) {
                if (g_Practice.subMenuCursor == i) {
                    if (g_Practice.practiceState == PRACTICE_STATE_3 || g_Practice.practiceState == PRACTICE_STATE_4) {
                        PRACTICE_RECORD_AT(scene, 2, i)->playMode = UI_PLAY_FORWARD;
                        PRACTICE_RECORD_AT(scene, 6, i)->playMode = UI_PLAY_FORWARD;
                    } else {
                        int frame = PRACTICE_RECORD_AT(scene, 2, i)->frame >> 16;

                        if (frame < 9) {
                            PRACTICE_RECORD_AT(scene, 2, i)->playMode = UI_PLAY_FORWARD;
                        } else {
                            PRACTICE_RECORD_AT(scene, 2, i)->playMode = UI_PLAY_STOP;
                        }
                        PRACTICE_RECORD_AT(scene, 6, i)->frame = 0x10000;
                        PRACTICE_RECORD_AT(scene, 6, i)->playMode = UI_PLAY_STOP;
                    }
                } else {
                    PRACTICE_RECORD_AT(scene, 2, i)->frame = 0;
                    PRACTICE_RECORD_AT(scene, 2, i)->playMode = UI_PLAY_STOP;
                    PRACTICE_RECORD_AT(scene, 6, i)->frame = 0;
                    PRACTICE_RECORD_AT(scene, 6, i)->playMode = UI_PLAY_STOP;
                }
            }
            if (g_Practice.practiceType_1 != 6 && g_Practice.practiceState == PRACTICE_STATE_6) {
                scene->_18 = 3;
            }
        } else if (scene->_18 == 3) {
            if (scene->_1A >= 0x20) {
                scene->_1A -= 0x20;
            } else {
                scene->_1A = 0;
            }
            PRACTICE_RECORD(scene, 0)->playMode = UI_PLAY_BACKWARD;
            PRACTICE_RECORD(scene, 1)->playMode = UI_PLAY_BACKWARD;
        }
        for (i = 0; i < 4; i++) {
            record = PRACTICE_RECORD_AT(scene, 0xE, i);
            record->rgba = scene->_1A | (record->rgba & ~0xFF);
        }
    } else {
        animRelated[0xC1] = 0;
        animRelated[0xC2] = 0;
        for (i = 0; i < 4; i++) {
            if (scene->channels[i] != 0xFFFF) {
                text_freeBlock(scene->channels[i]);
            }
        }
        fn_8000F8F4(scene);
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    }
}

void practiceMenu_charSelect_init(void) {
    PracticeScene* scene = (PracticeScene*)currentDrawingItem;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, practiceMenu_charSelect_uiRecords);
    scene->_18 = 0;
    scene->_1A = 0;
    scene->_1C = 0;
    currentDrawingItem->func = practiceMenu_charSelect_update;
}

void practiceMenu_charSelect_update(void) {
    PracticeScene* scene = (PracticeScene*)currentDrawingItem;
    int i;

    if (scene->_1A < 0xFFFE) {
        scene->_1A++;
    } else {
        scene->_1A = 0xFFFF;
    }
    if (animRelated[0x96] != 0 || g_Practice.practiceType_1 != 6) {
        goto remove;
    }
    if (scene->_1E == 0) {
        scene->_1E = 1;
        scene->_1A = 0;
    } else if (scene->_1E == 1) {
        UIRecord* record = PRACTICE_RECORD(scene, 0);
        int done = 0;

        if ((int)(record->frame >> 16) >= 0xE) {
            record->playMode = UI_PLAY_STOP;
            done |= 0x10;
            PRACTICE_RECORD(scene, 2)->playMode = UI_PLAY_STOP;
        }
        if (done == 0x10) {
            scene->_1E = 2;
        }
    } else if (scene->_1E == 2) {
        int charID = g_Minigame.selectSlots[g_Practice.homeAway].charID;

        PRACTICE_RECORD(scene, 5)->frame = charSelect_handednessIconFrames[g_Minigame.battingHandedness[g_Practice.homeAway]] << 16;
        if (characterStaticIndexes[charID * 6] != 0 &&
            g_Minigame.selectSlots[g_Practice.homeAway].confirmedInd == 0 && g_Minigame.selectSlots[g_Practice.homeAway].onBottomControlInd == 0) {
            PRACTICE_RECORD(scene, 7)->flags |= UI_FLAG_VISIBLE;
        } else {
            PRACTICE_RECORD(scene, 7)->flags &= ~UI_FLAG_VISIBLE;
        }
        if (g_Practice.practiceState == PRACTICE_STATE_4) {
            goto remove;
        }
        if (g_Practice.practiceState == PRACTICE_STATE_5) {
            scene->_1E = 3;
            scene->_1A = 0;
        }
    } else if (scene->_1E == 3) {
        if (scene->_1A == 1) {
            PRACTICE_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
            PRACTICE_RECORD(scene, 2)->playMode = UI_PLAY_FORWARD;
        }
    }

    if (g_Minigame.selectSlotState[0] >= 0) {
        if (g_Minigame.selectSlots[0].charID != (PRACTICE_RECORD(scene, 0xD)->frame >> 16)) {
            for (i = 0; i < 2; i++) {
                PRACTICE_RECORD_AT(scene, 8, i)->frame = 0;
            }
        }
        for (i = 0; i < 2; i++) {
            PRACTICE_RECORD_AT(scene, 8, i)->flags |= UI_FLAG_VISIBLE;
            PRACTICE_RECORD_AT(scene, 8, i)->playMode = UI_PLAY_FORWARD;
        }
        PRACTICE_RECORD(scene, 0xD)->frame = g_Minigame.selectSlots[0].charID << 16;
        PRACTICE_RECORD(scene, 0xB)->flags |= UI_FLAG_VISIBLE;
        PRACTICE_RECORD(scene, 0xB)->playMode = UI_PLAY_FORWARD;
        PRACTICE_RECORD(scene, 0xC)->frame =
            lbl_3_data_9D50[characterStaticIndexes[g_Minigame.selectSlots[0].charID * 6]]
                           [characterStaticIndexes[g_Minigame.selectSlots[0].charID * 6 + 5]] << 16;
    } else {
        for (i = 0; i < 2; i++) {
            PRACTICE_RECORD_AT(scene, 8, i)->frame = 0;
            PRACTICE_RECORD_AT(scene, 8, i)->flags &= ~UI_FLAG_VISIBLE;
        }
        PRACTICE_RECORD(scene, 0xD)->frame = 0x36 << 16;
        PRACTICE_RECORD(scene, 0xB)->frame = 0;
        PRACTICE_RECORD(scene, 0xB)->flags &= ~UI_FLAG_VISIBLE;
    }
    return;

remove:
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
}

void practice_insertInstructionScene(void) {
    if (g_Practice.tutorialState == TUTORIAL_STATE_0 && g_Practice.practiceState == PRACTICE_STATE_7) {
        insertGraphicDrawingFunction(practiceInstruction_init, 2);
    }
}

void practiceInstruction_init(void) {
    PracticeScene* scene = (PracticeScene*)currentDrawingItem;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, practiceInstruction_uiRecords);
    PRACTICE_RECORD(scene, 8)->flags &= ~UI_FLAG_VISIBLE;
    load_Icon(scene, 0xD, 1, 0xE, g_Practice.practiceLevel);
    load_Icon(scene, 0xD, 2, 0xE, g_Practice.practiceLevel);
    g_Practice.laukituTextChannelIndex = -1;
    g_Practice.diagramTextChannelIndex = -1;
    scene->_18 = 0;
    scene->_1A = 0;
    scene->_1C = 0;
    scene->_1E = 0;
    scene->_20 = 0;
    currentDrawingItem->func = practiceInstruction_update;
}

void practiceInstruction_update(void) {
    PracticeScene* scene = (PracticeScene*)currentDrawingItem;
    BOOL flag = FALSE;

    if (animRelated[0x96] == 0 && !(g_Practice.tutorialState == TUTORIAL_STATE_2 && g_Practice.practiceState == PRACTICE_STATE_3)) {
        if (scene->_1C == 0) {
            scene->_1C++;
            g_Practice.laukituTextChannelIndex = text_initializeNewChannel((UnkText988Arg*)scene, 9, 0, 5, 0, 0);
            screenTextArray.blocks[g_Practice.laukituTextChannelIndex].justify = 0;
            screenTextArray.blocks[g_Practice.laukituTextChannelIndex].verticalAlign = 1;
            practiceTextRelated(g_Practice.laukituTextChannelIndex, 2, 0);
            g_Practice.diagramTextChannelIndex = text_initializeNewChannel((UnkText988Arg*)scene, 10, 0, 5, 0, 0);
            screenTextArray.blocks[g_Practice.diagramTextChannelIndex].justify = 1;
            screenTextArray.blocks[g_Practice.diagramTextChannelIndex].verticalAlign = 1;
        }
        if (g_Practice.instructionComplete_readyToAdvance != 0 || g_Practice.allInstructionsComplete != 0) {
            PRACTICE_RECORD(scene, 7)->flags |= UI_FLAG_VISIBLE;
        } else {
            PRACTICE_RECORD(scene, 7)->flags &= ~UI_FLAG_VISIBLE;
        }
        {
            UIRecord* record = PRACTICE_RECORD(scene, 0);
            int frame = record->frame >> 16;

            if (g_Practice.diagramPanelShown != 0) {
                if (frame <= 0xF) {
                    record->playMode = UI_PLAY_FORWARD;
                } else if (record->unk69[0] == 2) {
                    flag = TRUE;
                }
            } else if (frame > 0xF) {
                record->playMode = UI_PLAY_BACKWARD;
            } else if (frame < 0xF) {
                record->playMode = UI_PLAY_FORWARD;
            } else {
                record->playMode = UI_PLAY_STOP;
            }
        }
        if (g_Practice.diagramElement != 0 && flag) {
            PRACTICE_RECORD(scene, 8)->elementIndex = practiceInstruction_diagramElements[g_Practice.diagramElement];
            PRACTICE_RECORD(scene, 8)->flags |= UI_FLAG_VISIBLE;
            PRACTICE_RECORD(scene, 4)->playMode = UI_PLAY_FORWARD;
            PRACTICE_RECORD(scene, 5)->playMode = UI_PLAY_FORWARD;
            if (PRACTICE_RECORD(scene, 4)->unk69[0] == 2) {
                PRACTICE_RECORD(scene, 10)->rgba = (PRACTICE_RECORD(scene, 10)->rgba & ~0xFF) | 0xFF;
            } else {
                PRACTICE_RECORD(scene, 10)->rgba &= ~0xFF;
            }
        } else {
            PRACTICE_RECORD(scene, 8)->flags &= ~UI_FLAG_VISIBLE;
            PRACTICE_RECORD(scene, 4)->playMode = UI_PLAY_BACKWARD;
            PRACTICE_RECORD(scene, 5)->playMode = UI_PLAY_BACKWARD;
            PRACTICE_RECORD(scene, 10)->rgba &= ~0xFF;
        }
        PRACTICE_RECORD(scene, 6)->frame = g_Practice.diagramFrame << 16;
        if (g_Practice.lakituTextIndex >= 0) {
            g_Practice.lakituTextIndex_stored = g_Practice.lakituTextIndex;
            g_Practice.lakituTextIndex = -1;
            text_setPtrToWhereCharsAreStored(g_Practice.laukituTextChannelIndex, 5, g_Practice.lakituTextIndex_stored);
        }
        if (g_Practice.diagramTitleTextIndex >= 0) {
            g_Practice.diagramTitleTextIndex_stored = g_Practice.diagramTitleTextIndex;
            g_Practice.diagramTitleTextIndex = -1;
            text_setPtrToWhereCharsAreStored(g_Practice.diagramTextChannelIndex, 5, g_Practice.diagramTitleTextIndex_stored);
        }
        g_Practice.currentMessageDoneTyping = screenTextArray.blocks[g_Practice.laukituTextChannelIndex].unk34;
    } else {
        g_Practice.currentMessageDoneTyping = 1;
        if (g_Practice.laukituTextChannelIndex >= 0) {
            text_freeBlock(g_Practice.laukituTextChannelIndex);
        }
        if (g_Practice.diagramTextChannelIndex >= 0) {
            text_freeBlock(g_Practice.diagramTextChannelIndex);
        }
        if (g_Practice.laukituTextChannelIndex >= 0 || g_Practice.diagramTextChannelIndex >= 0) {
            fn_8000F8F4(scene);
        }
        menuNumber[0x26] = 1;
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    }
}

void practice_insertGoalHudScenes(void) {
    if (g_Practice.practiceType_2 == PRACTICE_TYPE_PITCHING || g_Practice.practiceType_2 == PRACTICE_TYPE_BATTING || g_Practice.practiceType_2 == PRACTICE_TYPE_FIELDING) {
        if (g_Practice.tutorialState == TUTORIAL_STATE_3 && g_Practice.completionMenuActive == 0) {
            if (animRelated[0xC6] == 0) {
                insertGraphicDrawingFunction(practiceGoalHud_init, 2);
                animRelated[0xC6] = 1;
            }
            if (g_Practice.practiceType_2 == PRACTICE_TYPE_FIELDING && g_Ball.totalFramesAtPlay == 1) {
                insertGraphicDrawingFunction(drawDiamondMiniMap_init, 2);
            }
            if (g_Practice.practiceType_2 == PRACTICE_TYPE_FIELDING) {
                if (g_Practice.frames_sincePracticeCompleted == 0x3C) {
                    insertGraphicDrawingFunction(practiceCompleteBanner_init, 2);
                }
            } else if (g_Practice.frames_sincePracticeCompleted == 1) {
                insertGraphicDrawingFunction(practiceCompleteBanner_init, 2);
            }
        }
    } else if (g_Practice.practiceType_2 == PRACTICE_TYPE_BASERUNNING) {
        if (g_Practice.tutorialState == TUTORIAL_STATE_3 && g_Practice.completionMenuActive == 0) {
            if (animRelated[0xC7] == 0) {
                insertGraphicDrawingFunction(practiceGoalHud_init, 2);
                insertGraphicDrawingFunction(drawDiamondMiniMap_init, 2);
            }
            if (g_Practice.frames_sincePracticeCompleted == 1) {
                insertGraphicDrawingFunction(practiceCompleteBanner_init, 2);
            }
        }
    }
}

void practiceGoalHud_init(void) {
    PracticeScene* scene = (PracticeScene*)currentDrawingItem;
    int i;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, practiceGoalHud_uiRecords);
    if (g_Practice.practiceType_2 == PRACTICE_TYPE_FIELDING || g_Practice.practiceType_2 == PRACTICE_TYPE_BASERUNNING) {
        PRACTICE_RECORD(scene, 0)->elementIndex = 0x3B;
    }
    scene->_1A = g_Practice.guidedPracticeCounter;
    if (g_Practice.practiceType_2 == PRACTICE_TYPE_BASERUNNING) {
        PRACTICE_RECORD(scene, 1)->flags &= ~UI_FLAG_VISIBLE;
    } else {
        practiceGoalHud_updateCounter(scene);
    }
    for (i = 0; i < 4; i++) {
        s16 value = practiceGoalHud_entries[g_Practice.practiceType_2][g_Practice.practiceLevel][i][0];

        if (value == 0) {
            PRACTICE_RECORD_AT(scene, 2, i)->flags &= ~UI_FLAG_VISIBLE;
        } else {
            PRACTICE_RECORD_AT(scene, 0xE, i)->frame = value << 16;
        }
    }
    scene->_18 = 0;
    currentDrawingItem->func = practiceGoalHud_update;
}

void practiceGoalHud_update(void) {
    PracticeScene* scene = (PracticeScene*)currentDrawingItem;
    int i;
    BOOL freed;

    if (animRelated[0x96] == 0 && (g_Practice.completionMenuActive == 0 || pauseControl.state != 0) &&
        (g_Practice.pauseMenuActive == 0 || (pauseControl.state != 7 && pauseControl.state != 0xB))) {
        if (scene->_18 == 0) {
            for (i = 0; i < 4; i++) {
                s16* entry = practiceGoalHud_entries[g_Practice.practiceType_2][g_Practice.practiceLevel][i];

                if (entry[0] != 0) {
                    scene->channels[i] = text_initializeNewChannel((UnkText988Arg*)scene, 0x12 + i, 0, 5, entry[1], 0);
                    screenTextArray.blocks[scene->channels[i]].justify = 1;
                    screenTextArray.blocks[scene->channels[i]].verticalAlign = 1;
                }
            }
            scene->_18++;
        }
        practiceGoalHud_updateCounter(scene);
    } else {
        freed = FALSE;
        for (i = 0; i < 4; i++) {
            if (practiceGoalHud_entries[g_Practice.practiceType_2][g_Practice.practiceLevel][i][0] > 0) {
                text_freeBlock(scene->channels[i]);
                freed = TRUE;
            }
        }
        if (freed) {
            fn_8000F8F4(scene);
        }
        animRelated[0xC6] = 0;
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    }
}

void practiceGoalHud_updateCounter(PracticeScene* scene) {
    int threshold = guidedPracticeThresholds[g_Practice.practiceType_2][g_Practice.practiceLevel];
    int count;

    load_Icon(scene, 1, 3, 0x32, threshold);
    load_Icon(scene, 1, 4, 0x32, threshold);
    count = g_Practice.guidedPracticeCounter;
    load_Icon(scene, 1, 1, 0x32, count);
    load_Icon(scene, 1, 2, 0x32, count);
    if (count != scene->_1A) {
        UIRecord* record = PRACTICE_RECORD(scene, 1);

        if ((record->frame >> 16) <= 9) {
            record->frame = 0xA << 16;
            PRACTICE_RECORD(scene, 1)->playMode = UI_PLAY_FORWARD;
        }
        record = PRACTICE_RECORD(scene, 1);
        if ((record->frame >> 16) >= 0x13) {
            record->frame = 9 << 16;
            PRACTICE_RECORD(scene, 1)->playMode = UI_PLAY_STOP;
            scene->_1A = count;
        }
    }
}

void practiceCompleteBanner_init(void) {
    addGraphicsElementToScene(currentDrawingItem, practiceCompleteBanner_uiRecords);
    if (audioFileDescriptors.enableMusic == TRUE) {
        playSoundEffect(0x1AD);
    }
    currentDrawingItem->func = practiceCompleteBanner_update;
}

void practiceCompleteBanner_update(void) {
    PracticeScene* scene = (PracticeScene*)currentDrawingItem;
    int limit;

    if (animRelated[0x96] == 0) {
        limit = 0x96;
        if (g_Practice.practiceType_2 == PRACTICE_TYPE_PITCHING) {
            limit = 0x5A;
        }
        if (g_Practice.frames_sincePracticeCompleted < limit - 0x14) {
            UIRecord* record = PRACTICE_RECORD(scene, 0);

            if ((record->frame >> 16) >= 0x21) {
                record->playMode = UI_PLAY_STOP;
            }
        } else {
            PRACTICE_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
        }
        if (g_Practice.completionMenuActive == 0 || pauseControl.state != 0) {
            return;
        }
    }
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
}

void practiceGuidedMessage_init(void) {
    PracticeScene* scene = (PracticeScene*)currentDrawingItem;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, practiceGuidedMessage_uiRecords);
    scene->_1C = 0;
    scene->_1E = 0;
    currentDrawingItem->func = practiceGuidedMessage_update;
}

void practiceGuidedMessage_update(void) {
    PracticeScene* scene = (PracticeScene*)currentDrawingItem;

    if (animRelated[0x96] != 0) {
        goto remove;
    }
    if (scene->_1C == 0) {
        scene->_1E = text_initializeNewChannel((UnkText988Arg*)scene, 4, 0, 5, 0, 0);
        screenTextArray.blocks[scene->_1E].justify = 0;
        screenTextArray.blocks[scene->_1E].verticalAlign = 1;
        practiceTextRelated(scene->_1E, 2, 0);
        scene->_1C++;
    } else if (scene->_1C == 1) {
        UIRecord* record = PRACTICE_RECORD(scene, 0);

        if ((record->frame >> 16) >= 0xF) {
            record->playMode = UI_PLAY_STOP;
        }
        if (g_Practice.loadingGuidedPractice == 0) {
            if (g_Practice.completionMenuActive != 0) {
                goto remove;
            }
            PRACTICE_RECORD(scene, 1)->playMode = UI_PLAY_BACKWARD;
            PRACTICE_RECORD(scene, 2)->playMode = UI_PLAY_BACKWARD;
            PRACTICE_RECORD(scene, 2)->frame = 9 << 16;
            scene->_1C++;
        }
    } else if (scene->_1C == 2) {
        if ((PRACTICE_RECORD(scene, 1)->frame >> 16) == 0) {
            goto remove;
        }
    }

    if (g_Practice.completionMenuActive != 0) {
        PRACTICE_RECORD(scene, 3)->flags &= ~UI_FLAG_VISIBLE;
    } else {
        PRACTICE_RECORD(scene, 3)->flags |= UI_FLAG_VISIBLE;
    }
    if (g_Practice.frames_onGuidedMessage == 1) {
        text_setPtrToWhereCharsAreStored(scene->_1E, 5, practiceGuidedMessage_textIds[g_Practice.guidedMessageSet][g_Practice.guidedMessageVariant][g_Practice.guidedMessageIndex]);
    }
    g_Practice.currentMessageDoneTyping = screenTextArray.blocks[scene->_1E].unk34;
    return;

remove:
    text_freeBlock(scene->_1E);
    fn_8000F8F4(scene);
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
}

