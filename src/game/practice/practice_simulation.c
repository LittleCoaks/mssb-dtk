#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_practiceSimulation
#include "game/practice/practice_menu.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/practice/guided_practice.h"
#include "game/practice/batting_fielding_practice.h"
#include "game/practice/practice_scene.h"
#include "game/match_setup/roster_init.h"
#include "game/match_setup/pause_menu.h"
#include "game/sound/m_sound.h"
#include "static/UnknownHomes_Static.h"
#include "stl/stdlib.h"
#include "Dolphin/stl.h"
#include "musyx/musyx.h"
#include "Unknown/File_0x800204cc.h"
#include "Unknown/File_0x80014f40.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x80062a94.h"
#include "text/text.h"

extern u8 hugeAnimStruct[];
extern u8 lbl_80354768[];
#define PRACTICE_PROGRESS_FLAGS ((u8 (*)[4])(&lbl_80354768[0xCF4E]))
extern u8 lbl_803C6CF8[];
extern u8 PracticeScreenFiles[];
extern u8 lbl_80366158[];
extern u8 animRelated[];
extern void pitchingPracticeControl(void);
extern BOOL practice_loadAllGraphics(int arg);
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
extern void fn_800111B4(void* arg);
extern void fn_8000F4B8(int a, int b, int c, int d);
extern BOOL fn_3_90C14(int arg);
extern void* ARAMTransfer(void* file, s32 arg1, s32 arg2, s32 arg3);
extern void SetGameStatus(int status);

#define ANIM_BYTE(offset) (hugeAnimStruct[(offset)])
#define ANIM_HALF(offset) (*(s16*)&animRelated[(offset)])
#define CHAR_STATIC_TRACKER_IDX(charID) characterStaticIndexes[(charID) * 6 + 1]
#define CHAR_STATIC_ROW(charID) characterStaticIndexes[(charID) * 6 + 2]
#define CHAR_STATS(charID) (((CharacterStats*)&Static_Stats_Tables)[(charID)])

// .text:0x000B482C size:0x1A8
void practiceSimulation(void) {
    g_Practice.readyToMoveToNextInstruction = FALSE;
    if (g_Practice.pauseMenuActive != 0) {
        practicePauseRelated();
        adjustBallSoundEffectBasedOnHeight();
        return;
    }

    if (g_Practice.framesInCurrTransitionState < 0xFFFE) {
        g_Practice.framesInCurrTransitionState++;
    } else {
        g_Practice.framesInCurrTransitionState = 0xFFFF;
    }
    if (g_Practice.framesSincePracticeMenuDefaultTransition < 0xFFFE) {
        g_Practice.framesSincePracticeMenuDefaultTransition++;
    } else {
        g_Practice.framesSincePracticeMenuDefaultTransition = 0xFFFF;
    }
    if (g_Practice.totalFrames < 0xFFFE) {
        g_Practice.totalFrames++;
    } else {
        g_Practice.totalFrames = 0xFFFF;
    }

    switch (g_GameLogic.secondaryGameMode) {
    case SECONDARY_GAME_MODE_LOAD_PRACTICE_SCREEN:
        loadPracticeScreen();
        break;
    case SECONDARY_GAME_MODE_PRACTICE_MENU:
        practiceMenu();
        break;
    case SECONDARY_GAME_MODE_PRACTICE_PITCHING:
        pitchingPracticeControl();
        break;
    case SECONDARY_GAME_MODE_PRACTICE_BATTING:
        battingPracticeControl();
        break;
    case SECONDARY_GAME_MODE_PRACTICE_FIELDING:
        fieldingPracticeControl();
        break;
    case SECONDARY_GAME_MODE_PRACTICE_BASERUNNING:
        baseRunningPracticeControl();
        break;
    case SECONDARY_GAME_MODE_FREE_BAT_AND_RUNNING:
    case SECONDARY_GAME_MODE_FREE_FIELDING:
        freeFieldingPracticeControl();
        break;
    case SECONDARY_GAME_MODE_RETURN_TO_MENU:
        g_GameLogic.framesOfExitingToMenu = TRUE;
        break;
    }

    adjustBallSoundEffectBasedOnHeight();
    if (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT || g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL) {
        if (ANIM_HALF(0x9E) >= 0 && loadBatterModelFromDisk(ANIM_HALF(0x9E))) {
            ANIM_HALF(0x9E) = -1;
        }
        if (ANIM_HALF(0xA0) >= 0 && loadSomethingFromDiskAtBeginningOfAB1(ANIM_HALF(0xA0))) {
            ANIM_HALF(0xA0) = -1;
        }
    }
}

#pragma dont_inline on
// .text:0x000B43E8 size:0x444
void loadPracticeScreen(void) {
    int team;
    int slot;
    int row;
    int col;

    switch (g_GameLogic._125) {
    case 0:
        g_GameLogic.battingOrderAndPositionMapping[0][0][0] = constantList[0];
        g_GameLogic.battingOrderAndPositionMapping[1][0][0] = constantList[0];
        for (team = 0; team < TEAMS_PER_GAME; team++) {
            for (slot = 0; slot < PLAYERS_PER_TEAM; slot++) {
                g_GameLogic.battingOrderAndPositionMapping[team][slot + 1][0] = constantList[9 + slot];
                g_GameLogic.battingOrderAndPositionMapping[team][slot + 1][1] = constantList[9 + slot];
                lineUpInfoStruct[team][slot][0] = slot;
                lineUpInfoStruct[team][slot][1] = slot;
                lineUpInfoStruct[team][slot][2] = slot;
            }
        }
        for (team = 0; team < TEAMS_PER_GAME; team++) {
            for (slot = 0; slot < PLAYERS_PER_TEAM; slot++) {
                int character = g_GameLogic.battingOrderAndPositionMapping[team][slot + 1][0];
                memcpy(&inMemRoster[team][slot], &CHAR_STATS(character), sizeof(CharacterStats));
            }
        }
        g_Practice.homeAway = lbl_80366158[0x27];
        g_Practice.homeAwayByte = lbl_80366158[0x27];
        g_GameLogic.homeTeamInd = 0;
        g_GameLogic.teamBatting = 1;
        g_GameLogic.teamFielding = 0;
        g_GameLogic.homeTeamBattingInd_fieldingTeam = 1;
        g_GameLogic.awayTeamBattingInd_battingTeam = 0;
        g_GameLogic.teams[0] = lbl_80366158[0x27];
        g_GameLogic.teams[1] = lbl_80366158[0x27];
        g_GameLogic.Team_CaptainRosterLoc[0] = 0;
        g_GameLogic.Team_CaptainRosterLoc[1] = 0;
        g_GameLogic._125 = g_GameLogic._125 + 1;
        break;
    case 1:
        screenTextArray.textBanks[5] = (TextBank*)ARAMTransfer(PracticeScreenFiles, 0, 1, 0);
        g_GameLogic._125 = g_GameLogic._125 + 1;
        break;
    case 2:
        if ((s8)lbl_803C6CF8[0x715] == 1) {
            fn_800111B4(screenTextArray.textBanks[5]);
            g_GameLogic._125 = g_GameLogic._125 + 1;
            sound_crowd_EffectsStruct._2C = 0;
            fn_8000F4B8(g_Practice.homeAwayByte, -1, -1, -1);
        }
        break;
    case 3:
        if (fn_3_90C14(0)) {
            sound_crowd_EffectsStruct._2C = 0;
            g_GameLogic._125 = g_GameLogic._125 + 1;
        }
        break;
    default:
        g_Practice.menuGraphicsLoaded = FALSE;
        ANIM_BYTE(0x2D77) = FALSE;
        ANIM_BYTE(0x2D7B) = FALSE;
        ANIM_BYTE(0x2D7C) = FALSE;
        practice_loadAllGraphics(g_GameLogic.teamFielding);
        g_Practice.lakituTextIndex = -1;
        g_Practice.returnToPracticeMenuState = 1;
        g_Practice.someCharID1 = -1;
        g_Practice.someCharID2 = -1;
        g_Practice.progressNeedsSave = FALSE;
        g_Practice.showMenuIntro = TRUE;
        SetGameStatus(5);
        g_GameLogic.secondaryGameMode = SECONDARY_GAME_MODE_PRACTICE_MENU;
        g_Practice.totalFrames = 0;
        g_Practice.framesInCurrTransitionState = 0;
        g_Practice.practiceState = PRACTICE_STATE_0;
        practiceMenu_setScreen(0);
        insertGraphicDrawingFunction(possiblyTransitionBlackScreen, 2);
        insertGraphicDrawingFunction(drawStadium, 4);
        ANIM_BYTE(0x307E) = FALSE;
        g_Practice.practiceType = PRACTICE_TYPE_PITCHING;
        g_Practice.baserunningActiveRunners[0] = FALSE;
        g_Practice.baserunningActiveRunners[1] = FALSE;
        g_Practice.baserunningActiveRunners[2] = FALSE;
        g_Practice._1A6 = FALSE;
        g_Practice._1A8 = FALSE;
        g_Practice._1A9 = FALSE;
        g_Practice.pauseMenuActive = FALSE;
        g_Practice.aIEnabled = FALSE;
        g_Practice.practiceBatterHandedness = FALSE;
        g_Practice.freePracticeInd_writeOnly = FALSE;
        g_Practice.freeFieldingInd_writeOnly = FALSE;
        g_Practice.instructionNumber = -1;
        g_Practice.transitioningIndicator = FALSE;
        g_Practice.loadingGuidedPractice = FALSE;
        g_Practice.guidedMessageSceneStarted = FALSE;
        for (row = 0; row < 4; row++) {
            for (col = 0; col < 4; col++) {
                g_Practice.levelCompleted[row][col] = PRACTICE_PROGRESS_FLAGS[row][col];
            }
        }
        break;
    }
}
#pragma dont_inline reset

#pragma dont_inline on
void practice_loadCharacterData(void) {
    int slot, team;

    g_GameLogic.battingOrderAndPositionMapping[0][0][0] = constantList[0];
    g_GameLogic.battingOrderAndPositionMapping[1][0][0] = constantList[0];
    for (team = 0; team < TEAMS_PER_GAME; team++) {
        for (slot = 0; slot < PLAYERS_PER_TEAM; slot++) {
            g_GameLogic.battingOrderAndPositionMapping[team][slot + 1][0] = constantList[9 + slot];
            g_GameLogic.battingOrderAndPositionMapping[team][slot + 1][1] = constantList[9 + slot];
            lineUpInfoStruct[team][slot][0] = slot;
            lineUpInfoStruct[team][slot][1] = slot;
            lineUpInfoStruct[team][slot][2] = slot;
        }
    }
    for (team = 0; team < TEAMS_PER_GAME; team++) {
        for (slot = 0; slot < PLAYERS_PER_TEAM; slot++) {
            int character = g_GameLogic.battingOrderAndPositionMapping[team][slot + 1][0];
            memcpy(&inMemRoster[team][slot], &CHAR_STATS(character), sizeof(CharacterStats));
        }
    }
}
#pragma dont_inline reset

#pragma dont_inline on
void practice_loadCharacter(int team, int slot, int character, int flags) {
    if (team == 0 && slot == 0) {
        g_GameLogic.battingOrderAndPositionMapping[team][0][0] = slot;
    }
    lineUpInfoStruct[team][slot][0] = slot;
    lineUpInfoStruct[team][slot][1] = slot;
    lineUpInfoStruct[team][slot][2] = slot;
    g_GameLogic.battingOrderAndPositionMapping[team][slot + 1][0] = slot;
    g_GameLogic.battingOrderAndPositionMapping[team][slot + 1][1] = slot;
    if (slot >= 0 && slot <= 8) {
        fn_80011BE4(slot);
    }
    memcpy(&inMemRoster[team][slot], &CHAR_STATS(character), sizeof(CharacterStats));
    if (flags >= 0) {
        if (flags == 0 || flags == 1) {
            inMemRoster[team][slot].stats.FieldingArm = 0;
        } else {
            inMemRoster[team][slot].stats.FieldingArm = 1;
        }
        if (flags == 0 || flags == 2) {
            inMemRoster[team][slot].stats.BattingStance = 0;
        } else {
            inMemRoster[team][slot].stats.BattingStance = 1;
        }
    }
}
#pragma dont_inline reset

void practiceLoadingRelatedMaybe(void) {
    int row;
    int col;
    insertGraphicDrawingFunction(possiblyTransitionBlackScreen, 2);
    insertGraphicDrawingFunction(drawStadium, 4);
    ANIM_BYTE(0x307E) = FALSE;
    g_Practice.practiceType = PRACTICE_TYPE_PITCHING;
    g_Practice.baserunningActiveRunners[0] = FALSE;
    g_Practice.baserunningActiveRunners[1] = FALSE;
    g_Practice.baserunningActiveRunners[2] = FALSE;
    g_Practice._1A6 = FALSE;
    g_Practice._1A8 = FALSE;
    g_Practice._1A9 = FALSE;
    g_Practice.pauseMenuActive = FALSE;
    g_Practice.aIEnabled = FALSE;
    g_Practice.practiceBatterHandedness = FALSE;
    g_Practice.freePracticeInd_writeOnly = FALSE;
    g_Practice.freeFieldingInd_writeOnly = FALSE;
    g_Practice.instructionNumber = -1;
    g_Practice.transitioningIndicator = FALSE;
    g_Practice.loadingGuidedPractice = FALSE;
    g_Practice.guidedMessageSceneStarted = FALSE;
    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            g_Practice.levelCompleted[row][col] = PRACTICE_PROGRESS_FLAGS[row][col];
        }
    }
}

BOOL practice_relatedToSettingCharacters(void) {
    int primary = 0;
    int secondary = -1;
    s16 previous;

    if (!g_Practice.characterLoadStarted) {
        g_Practice.characterLoadStarted = TRUE;
        g_Practice.someCharID3 = -1;
        g_Practice.someCharID4 = -1;
        switch (g_Practice.practiceType_2) {
        case PRACTICE_TYPE_BATTING:
            secondary = 1;
            break;
        case PRACTICE_TYPE_FIELDING:
            secondary = 1;
            break;
        case PRACTICE_TYPE_BASERUNNING:
            return TRUE;
        case PRACTICE_TYPE_FREEPLAY:
            primary = g_Minigame.selectSlots[g_Practice.homeAway].charID;
            break;
        case PRACTICE_TYPE_PITCHING:
            break;
        }
        if (primary == 0) primary = -1;
        if (secondary == 0) secondary = -1;
        if (primary < 0) {
            primary = secondary;
            secondary = -1;
        }
        if (primary < 0) return TRUE;
        if (secondary >= 0 && CHAR_STATIC_ROW(primary) == CHAR_STATIC_ROW(secondary)) {
            secondary = -1;
        }
        if (secondary < 0) {
            if ((g_Practice.someCharID1 >= 0 && CHAR_STATIC_ROW(g_Practice.someCharID1) == CHAR_STATIC_ROW(primary)) ||
                (g_Practice.someCharID2 >= 0 && CHAR_STATIC_ROW(g_Practice.someCharID2) == CHAR_STATIC_ROW(primary))) {
                return TRUE;
            }
            previous = g_Practice.someCharID2;
            if (previous >= 0) {
                fn_3_90AB0(CHAR_STATIC_TRACKER_IDX(previous));
                g_Practice.someCharID2 = CHAR_STATIC_TRACKER_IDX(primary);
            } else if (g_Practice.someCharID1 < 0) {
                g_Practice.someCharID1 = CHAR_STATIC_TRACKER_IDX(primary);
            } else {
                g_Practice.someCharID2 = CHAR_STATIC_TRACKER_IDX(primary);
            }
            g_Practice.someCharID3 = CHAR_STATIC_TRACKER_IDX(primary);
        } else if (g_Practice.someCharID1 >= 0) {
            do {
                previous = g_Practice.someCharID1;
                if (CHAR_STATIC_TRACKER_IDX(previous) != CHAR_STATIC_TRACKER_IDX(secondary)) {
                    if (CHAR_STATIC_TRACKER_IDX(previous) == CHAR_STATIC_TRACKER_IDX(primary)) {
                        primary = secondary;
                    } else {
                        fn_3_90AB0(CHAR_STATIC_TRACKER_IDX(previous));
                        fn_3_90AB0(CHAR_STATIC_TRACKER_IDX(g_Practice.someCharID2));
                        g_Practice.someCharID3 = CHAR_STATIC_TRACKER_IDX(primary);
                        g_Practice.someCharID4 = CHAR_STATIC_TRACKER_IDX(secondary);
                        g_Practice.someCharID1 = CHAR_STATIC_TRACKER_IDX(primary);
                        g_Practice.someCharID2 = CHAR_STATIC_TRACKER_IDX(secondary);
                        break;
                    }
                }
                previous = g_Practice.someCharID2;
                if (CHAR_STATIC_TRACKER_IDX(previous) != CHAR_STATIC_TRACKER_IDX(primary)) {
                    fn_3_90AB0(CHAR_STATIC_TRACKER_IDX(previous));
                    g_Practice.someCharID3 = CHAR_STATIC_TRACKER_IDX(primary);
                    g_Practice.someCharID2 = CHAR_STATIC_TRACKER_IDX(primary);
                }
            } while (0);
        }
    }
    if (g_Practice.someCharID3 >= 0 && !fn_3_90B14(g_Practice.someCharID3, g_Practice.someCharID4)) return FALSE;
    return TRUE;
}

#pragma dont_inline on
void switchSecondaryGameMode(int mode) {
    g_GameLogic.secondaryGameMode = mode;
    g_Practice.totalFrames = 0;
    g_Practice.framesInCurrTransitionState = 0;
    g_Practice.practiceState = PRACTICE_STATE_0;
}
#pragma dont_inline reset

#pragma dont_inline on
void updatePracticeTransitionState(int state) {
    g_Practice.practiceState = state;
    g_Practice.framesInCurrTransitionState = 0;
}
#pragma dont_inline reset

#pragma dont_inline on
void setTutorialState(int state) {
    g_Practice.practiceState = PRACTICE_STATE_0;
    g_Practice.tutorialState = state;
    g_Practice.framesSincePracticeMenuDefaultTransition = 0;
}
#pragma dont_inline reset

#pragma dont_inline on
void fn_3_B3C64(void) {
    g_GameLogic.framesOfExitingToMenu = TRUE;
}
#pragma dont_inline reset

void practiceSetupRunnerStatus(void) {
    int i;
    for (i = 0; i < 4; i++) {
        InMemRunnerType* runner = &g_Runners[i];
        if (g_Practice.baserunningActiveRunners[i] != 0) {
            if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_BASERUNNING) {
                initializeInMemRunner(i - 1, i);
            }
            runner->runnerOnFieldOrOutOrScored = RUNNER_STATUS_ON_FIELD;
        } else {
            runner->runnerOnFieldOrOutOrScored = RUNNER_STATUS_NONE;
            runner->rosterID = -1;
        }
    }
}

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
