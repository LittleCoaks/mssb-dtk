#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_practiceMenu
#include "game/practice/practice_menu.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/practice/guided_practice.h"
#include "game/practice/practice_modes.h"
#include "game/practice/practice_scene.h"
#include "game/match_setup/roster_init.h"
#include "game/sound/m_sound.h"
#include "static/UnknownHomes_Static.h"
#include "stl/stdlib.h"
#include "Dolphin/stl.h"
#include "musyx/musyx.h"
#include "Unknown/File_0x800204cc.h"
#include "Unknown/File_0x80014f40.h"
#include "Unknown/File_0x8001594c.h"
#include "Unknown/File_0x800b0a14.h"

extern u8 hugeAnimStruct[];
extern u8 lbl_80354768[];
extern u8 characterStaticIndexes[];
extern u8 constantList[];
extern u8 lineUpInfoStruct[2][9][4];
extern void fn_3_6AEC0(void);
extern void fn_3_90AB0(int character);
extern BOOL fn_3_90B14(int first, int second);
extern void resetInMemFielders(void);
extern void possiblyTransitionBlackScreen(void);
extern void drawStadium(void);
extern void fn_80011BE4(int character);
extern void adjustBallSoundEffectBasedOnHeight(void);
extern void practicePauseRelated(void);
extern void baseRunningPracticeControl(void);
extern void freeFieldingPracticeControl(void);
extern BOOL loadSomethingFromDiskAtBeginningOfAB1(int index);
extern void css_initValues(void);
extern void cssLoadingRelated_1(void);
extern void cssCursorOnBottomControl_maybe(void);
extern void addOrRemoveCharacterToTeam(void);
extern void playPlayerSelectedSound(void);
extern void fn_8004FD64(void);
extern void fn_80062A74(void);
extern void fn_3_5B408(void);
extern void fn_3_5B368(void);
extern void fn_3_5B220(void);
extern void exitMenu_main(void);
extern void fn_8004CC18(void);
extern void fn_800111B4(void);
extern void fn_8000F4B8(void);
extern BOOL fn_3_90C14(void);
extern void ARAMTransfer(void);
extern void SetGameStatus(int status);

#define PRACTICE_BYTE(offset) (*((u8*)&g_Practice + (offset)))
#define GAME_BYTE(offset) (*((u8*)&g_GameLogic + (offset)))
#define ANIM_BYTE(offset) (hugeAnimStruct[(offset)])
#define MINI_BYTE(offset) (*((u8*)&g_Minigame + (offset)))

void practiceRelatedReset(void) {
    g_GameLogic.freeFieldingPracticeInd = FALSE;
    g_Practice.instructionNumber = -1;
    g_Practice.transitioningIndicator = FALSE;
    ANIM_BYTE(0x307E) = TRUE;
    ANIM_BYTE(0x307A) = TRUE;
    fn_3_6AEC0();
    fn_3_8F1C8();
    resetInMemFielders();
}

void baserunningPracticeRelated(void) {
    int i;
    for (i = 0; i < 4; i++) {
        if (g_Practice.baserunningActiveRunners[i] != 0) {
            if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_BASERUNNING) {
                initializeInMemRunner(i - 1, i);
            }
            g_Runners[i].runnerOnFieldOrOutOrScored = RUNNER_STATUS_ON_FIELD;
        } else {
            g_Runners[i].runnerOnFieldOrOutOrScored = RUNNER_STATUS_NONE;
            g_Runners[i].rosterID = -1;
        }
    }
}

void fn_3_B3C64(void) {
    g_GameLogic.framesOfExitingToMenu = TRUE;
}

void setTutorialState(int state) {
    g_Practice.practiceState = PRACTICE_STATE_0;
    g_Practice.tutorialState = state;
    g_Practice.framesSincePracticeMenuDefaultTransition = 0;
}

void updatePracticeTransitionState(int state) {
    g_Practice.practiceState = state;
    g_Practice.framesInCurrTransitionState = 0;
}

void switchSecondaryGameMode(int mode) {
    g_GameLogic.secondaryGameMode = mode;
    g_Practice.totalFrames = 0;
    g_Practice.framesInCurrTransitionState = 0;
    g_Practice.practiceState = PRACTICE_STATE_0;
}

BOOL practice_relatedToSettingCharacters(void) {
    int primary;
    int secondary = -1;
    int previous;

    if (!g_Practice.characterLoadStarted) {
        g_Practice.characterLoadStarted = TRUE;
        g_Practice.someCharID3 = -1;
        g_Practice.someCharID4 = -1;
        switch (g_Practice.practiceType_2) {
        case PRACTICE_TYPE_BATTING:
        case PRACTICE_TYPE_FIELDING:
            secondary = 1;
            break;
        case PRACTICE_TYPE_FREEPLAY:
            return TRUE;
        case PRACTICE_TYPE_BASERUNNING:
            secondary = (s8)MINI_BYTE(0x19E8 + g_Practice.homeAway * 9);
            break;
        default:
            break;
        }
        if (secondary == 0) secondary = -1;
        primary = -1;
        if (primary < 0) {
            primary = secondary;
            secondary = -1;
        }
        if (primary < 0) return TRUE;
        if (secondary >= 0 && characterStaticIndexes[primary * 6 + 2] == characterStaticIndexes[secondary * 6 + 2]) {
            secondary = -1;
        }
        if (secondary < 0) {
            previous = g_Practice.someCharID1;
            if (previous >= 0 && characterStaticIndexes[previous * 6 + 2] == characterStaticIndexes[primary * 6 + 2]) return TRUE;
            previous = g_Practice.someCharID2;
            if (previous >= 0 && characterStaticIndexes[previous * 6 + 2] == characterStaticIndexes[primary * 6 + 2]) return TRUE;
            if (previous >= 0) fn_3_90AB0(characterStaticIndexes[previous * 6 + 1]);
            if (g_Practice.someCharID1 < 0) g_Practice.someCharID1 = characterStaticIndexes[primary * 6 + 1];
            else g_Practice.someCharID2 = characterStaticIndexes[primary * 6 + 1];
            g_Practice.someCharID3 = characterStaticIndexes[primary * 6 + 1];
        } else {
            previous = g_Practice.someCharID1;
            if (previous >= 0 && characterStaticIndexes[previous * 6 + 1] != characterStaticIndexes[primary * 6 + 1]) {
                fn_3_90AB0(characterStaticIndexes[previous * 6 + 1]);
                g_Practice.someCharID1 = characterStaticIndexes[primary * 6 + 1];
            }
            g_Practice.someCharID3 = characterStaticIndexes[primary * 6 + 1];
            g_Practice.someCharID4 = characterStaticIndexes[secondary * 6 + 1];
        }
    }
    if (g_Practice.someCharID3 >= 0 && !fn_3_90B14(g_Practice.someCharID3, g_Practice.someCharID4)) return FALSE;
    return TRUE;
}

void practiceLoadingRelatedMaybe(void) {
    int i;
    insertGraphicDrawingFunction(possiblyTransitionBlackScreen, 2);
    insertGraphicDrawingFunction(drawStadium, 4);
    ANIM_BYTE(0x307E) = FALSE;
    g_Practice.practiceType = PRACTICE_TYPE_PITCHING;
    g_Practice.baserunningActiveRunners[0] = FALSE;
    g_Practice.baserunningActiveRunners[1] = FALSE;
    g_Practice.baserunningActiveRunners[2] = FALSE;
    PRACTICE_BYTE(0x1A6) = FALSE;
    PRACTICE_BYTE(0x1A8) = FALSE;
    PRACTICE_BYTE(0x1A9) = FALSE;
    g_Practice.pauseMenuActive = FALSE;
    g_Practice.aIEnabled = FALSE;
    g_Practice.practiceBatterHandedness = FALSE;
    g_Practice.freePracticeInd_writeOnly = FALSE;
    g_Practice.freeFieldingInd_writeOnly = FALSE;
    g_Practice.instructionNumber = -1;
    g_Practice.transitioningIndicator = FALSE;
    g_Practice.loadingGuidedPractice = FALSE;
    g_Practice.guidedMessageSceneStarted = FALSE;
    for (i = 0; i < 16; i++) ((u8*)g_Practice.levelCompleted)[i] = lbl_80354768[0xCF4E + i];
}

void practice_loadCharacter(int team, int slot, int character, int flags) {
    u8* game = (u8*)&g_GameLogic;
    u8* roster = (u8*)inMemRoster;
    u8* statics = (u8*)&Static_Stats_Tables;
    u8* entry;
    if (team == 0 && slot == 0) *(int*)(game + 0x3C) = slot;
    entry = &lineUpInfoStruct[team][slot][0];
    entry[0] = slot;
    entry[1] = slot;
    entry[2] = slot;
    *(int*)(game + team * 0x50 + slot * 8 + 0x44) = slot;
    *(int*)(game + team * 0x50 + slot * 8 + 0x48) = slot;
    if (slot >= 0 && slot <= 8) fn_80011BE4(slot);
    memcpy(roster + team * 0x5A0 + slot * 0xA0, statics + character * 0xA0, 0xA0);
    if (flags >= 0) {
        roster[team * 0x5A0 + slot * 0xA0 + 0x26] = (flags == 0 || flags == 1) ? 0 : 1;
        roster[team * 0x5A0 + slot * 0xA0 + 0x27] = (flags == 0 || flags == 2) ? 0 : 1;
    }
}

void practice_loadCharacterData(void) {
    int team, slot, row;
    u8* game = (u8*)&g_GameLogic;
    u8* statics = (u8*)&Static_Stats_Tables;
    u8* roster = (u8*)inMemRoster;
    for (team = 0; team < 2; team++) {
        *(int*)(game + team * 0x50 + 0x3C) = constantList[0];
        for (row = 0; row < 9; row++) {
            lineUpInfoStruct[team][row][0] = row;
            lineUpInfoStruct[team][row][1] = row;
            lineUpInfoStruct[team][row][2] = row;
            *(int*)(game + team * 0x50 + row * 8 + 0x44) = constantList[row + 9];
            *(int*)(game + team * 0x50 + row * 8 + 0x48) = constantList[row + 9];
        }
        for (slot = 0; slot < 9; slot++) {
            int character = *(int*)(game + team * 0x50 + slot * 8 + 0x44);
            memcpy(roster + team * 0x5A0 + slot * 0xA0, statics + character * 0xA0, 0xA0);
        }
    }
}

// .text:0x000B43E8 size:0x444
void loadPracticeScreen(void) {
    return;
}

// .text:0x000B482C size:0x1A8
void practiceSimulation(void) {
    return;
}

// .text:0x000B49D4 size:0x26C
void fn_3_B49D4(void) {
    return;
}

// .text:0x000B4C40 size:0x450
void practiceRelatedMenu(void) {
    return;
}

// .text:0x000B5090 size:0x154
void unref(void) {
    return;
}

// .text:0x000B51E4 size:0x4B0
void practice_subMenu_stateHandling(void) {
    return;
}

// .text:0x000B5694 size:0x184
void notReferenced(void) {
    return;
}

// .text:0x000B5818 size:0x49C
void practice_mainMenu_stateHandling(void) {
    return;
}

// .text:0x000B5CB4 size:0x98
void unused_MaybePractice(void) {
    return;
}

// .text:0x000B5D4C size:0x2C
void practiceMenu_setScreen(int screen) {
    return;
}

// .text:0x000B5D78 size:0x104
void practiceMenu(void) {
    return;
}
