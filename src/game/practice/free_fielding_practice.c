#define SQRT2_LINKAGE static
#include "game/practice/free_fielding_practice.h"
#define REP_HEADER_DATA_FN getRepHeaderData_freeFieldingPractice
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/hud/hud_gauges.h"
#include "game/hud/hud_scoreboard.h"
#include "game/minigame/minigame_hud.h"
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
