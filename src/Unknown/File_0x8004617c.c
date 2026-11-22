#define TEAM_MANAGEMENT_LOCAL_VIEW
#include "Unknown/File_0x8004617c.h"
#include "Unknown/File_0x80047ce0.h"
#include "static/UnknownHomes_Static.h"
#include "game/challenge/challenge_state.h"
#include "menus/yd_step.h"
#include "Unknown/mb_subfunc.h"
#include "Unknown/File_0x8006236c.h"
#include "Unknown/File_0x800625a4.h"
#include "Unknown/File_0x80047fe4.h"

// 0x8004617C-0x800486E0: the team-management translation unit, one unit by its
// .sbss and .bss (docs/splits.md, 2026-11-21): the former File_0x8004617c.c,
// File_0x80047ce0.c and File_0x80047fe4.c plus fn_800471F4 (no C yet).

#include "static/UnknownHomes_Static.h"
#include "Unknown/orderchange.h"
#include "Unknown/File_0x800625a4.h"
#include "Dolphin/pad.h"
#include "Dolphin/stl.h"
#include "musyx/musyx.h"

// Only the team-management state this unit touches (the fields of the former
// File_0x8004617c.c and File_0x80047fe4.c views); see TEAM_MANAGEMENT_LOCAL_VIEW
// for why the full-size type is not used.
extern struct {
    /* 0x0000 */ controllerInputStruct playerInputs[4];
    /* 0x0018 */ u8 _0018[0xCF38 - 0x18];
    /* 0xCF38 */ E(u16, TEAM_MANAGEMENT_PROCESS) teamManagementProcessID;
    /* 0xCF3A */ s8 teamThatPaused;
    /* 0xCF3B */ u8 playerWhoPaused;
    /* 0xCF3C */ u8 charSelectedToBeSwapped[2];
    /* 0xCF3E */ u8 charSelectedToBeSwappedCharID[2];
    /* 0xCF40 */ u8 unkCF40;
    /* 0xCF41 */ u8 _CF41;
    /* 0xCF42 */ u8 onMainPauseMenu;
    /* 0xCF43 */ u8 onePlayerEditingTeam;
    /* 0xCF44 */ u8 _CF44;
    /* 0xCF45 */ u8 removeSceneRequested;
    /* 0xCF46 */ s8 teamManagement_cursorPos[2];
    /* 0xCF48 */ s8 teamManagement_prevCursorPos[2];
    /* 0xCF4A */ u8 onFieldingAlignmentScreen2[2];
    /* 0xCF4C */ u8 unkCF4C[2];
    /* 0xCF4E */ u8 teamConfirmed[2];
    /* 0xCF50 */ u8 waitingForOtherTeam[2];
    /* 0xCF52 */ E(u8, ROSTER_VIEW) rosterView[2];
    /* 0xCF54 */ E(u8, ROSTER_VIEW) prevRosterView[2];
    /* 0xCF56 */ u8 swapCompleted[2];
    /* 0xCF58 */ u8 stanceChangeRequested[2];
    /* 0xCF5A */ u8 _CF5A[0xCF5F - 0xCF5A];
    /* 0xCF5F */ u8 loadMatchRelInd;
    /* 0xCF60 */ u8 _CF60;
    /* 0xCF61 */ u8 zMenuOpen[2];
    /* 0xCF63 */ u8 zMenuPageLoaded[2];
    /* 0xCF65 */ u8 zMenuActive[2];
    /* 0xCF67 */ E(u8, Z_MENU_PAGE) zMenuPage[2];
    /* 0xCF69 */ u8 _CF69[0xCF6B - 0xCF69];
    /* 0xCF6B */ u8 unkCF6B;
    /* 0xCF6C */ u8 _CF6C[0xCF70 - 0xCF6C];
    /* 0xCF70 */ u8 unkCF70;
    /* 0xCF71 */ u8 starMenuOpen;
    /* 0xCF72 */ u8 starMenuActive;
    /* 0xCF73 */ u8 starMenuStepStarted;
    /* 0xCF74 */ E(u8, STAR_MENU_DRAW_STEP) starMenuDrawStep;
    /* 0xCF75 */ u8 starMenuCursorPos;
    /* 0xCF76 */ u8 starMenuPrevCursorPos;
    /* 0xCF77 */ u8 _CF77;
    /* 0xCF78 */ u16 starMenuCharID;
    /* 0xCF7A */ u8 _CF7A[0xCF7D - 0xCF7A];
    /* 0xCF7D */ E(u8, SCOUT_FLAG_MENU_STATE) scoutFlagMenuState;
    /* 0xCF7E */ u8 _CF7E[0xCF9E - 0xCF7E];
    /* 0xCF9E */ u8 inProgress_superStarAPlayer[2];
    /* 0xCFA0 */ u8 _CFA0;
    /* 0xCFA1 */ u8 challengeLoadingNormalMatchInd;
    /* 0xCFA2 */ E(u8, TEAM_MENU_TYPE) teamMenuType[4];
} g_TeamManagement;

extern GameSetUpStep gameSetUpStep;

extern u8 superstarUnlocked[0x130];
extern u8 lbl_800EFBA4[0x10];
extern u8 lbl_803CBCC8;
extern CharacterStats inMemRoster[2][9];

u8 fn_800471F4(u8 charSelected, u8 team);

void teamManagement_takeInputs(s32 playerIndex) {
    s32 team;
    controllerInputStruct input;

    if (gameSetUpStep.preventCursorMovement[0] != 0) {
        return;
    }
    if (gameSetUpStep.preventCursorMovement[1] != 0) {
        return;
    }

    if (g_d_GameSettings._06 == 2) {
        team = playerIndex;
    } else if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_2_PLAYER_GAME) {
        if (playerIndex > 1) {
            return;
        }
        team = playerIndex;
    } else if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
        if (playerIndex != 0) {
            return;
        }
        if (g_TeamManagement.onePlayerEditingTeam == 0) {
            team = 0;
        } else {
            team = 1;
        }
    }

    memset(&input, 0, sizeof(input));
    if (g_TeamManagement.teamThatPaused == -1) {
        input.currentHeldInput = Static_Stats_Tables.controllerInputs[playerIndex].currentHeldInput;
    } else {
        input.currentHeldInput = g_TeamManagement.playerInputs[playerIndex].currentHeldInput;
    }
    if (g_TeamManagement.teamThatPaused == -1) {
        input.newInput = Static_Stats_Tables.controllerInputs[playerIndex].newInput;
    } else {
        input.newInput = g_TeamManagement.playerInputs[playerIndex].newInput;
    }
    if (g_TeamManagement.teamThatPaused == -1) {
        input.processedInput = Static_Stats_Tables.controllerInputs[playerIndex].processedInput;
    } else {
        input.processedInput = g_TeamManagement.playerInputs[playerIndex].processedInput;
    }
    if (g_TeamManagement.teamConfirmed[team] != 0) {
        input.currentHeldInput &= PAD_BUTTON_B;
        input.newInput &= PAD_BUTTON_B;
        input.processedInput &= PAD_BUTTON_B;
    }

    if (input.newInput & PAD_TRIGGER_Z) {
        if (g_TeamManagement.zMenuOpen[team] != 0) {
            g_TeamManagement.zMenuOpen[team] = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (g_TeamManagement.teamManagement_cursorPos[team] != 0) {
            g_TeamManagement.zMenuOpen[team] = 1;
            g_TeamManagement.zMenuActive[team] = 1;
            g_TeamManagement.zMenuPage[team] = Z_MENU_PAGE_MAIN;
            sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
        }
        return;
    }

    if (input.processedInput & PAD_BUTTON_UP) {
        if (g_TeamManagement.zMenuOpen[team] != 0) {
            return;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE && g_TeamManagement.unkCF70 != 0) {
            return;
        }
        if (g_TeamManagement.teamConfirmed[team] != 0) {
            return;
        }
        swapPosMenu_up_downPress(0, team);
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        return;
    }

    if (input.processedInput & PAD_BUTTON_DOWN) {
        if (g_TeamManagement.zMenuOpen[team] != 0) {
            return;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE && g_TeamManagement.unkCF70 != 0) {
            return;
        }
        if (g_TeamManagement.teamConfirmed[team] != 0) {
            return;
        }
        swapPosMenu_up_downPress(1, team);
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        return;
    }

    if (input.processedInput & PAD_BUTTON_LEFT) {
        if (g_TeamManagement.zMenuOpen[team] != 0) {
            if (g_TeamManagement.zMenuPage[team] != Z_MENU_PAGE_STAR_MOVES) {
                return;
            }
            g_TeamManagement.zMenuPage[team] = Z_MENU_PAGE_MAIN;
            g_TeamManagement.zMenuPageLoaded[team] = 0;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            return;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE && g_TeamManagement.unkCF70 != 0) {
            return;
        }
        if (g_TeamManagement.teamConfirmed[team] != 0) {
            return;
        }
        swapPosMenu_left_rightPress(0, team);
        return;
    }

    if (input.processedInput & PAD_BUTTON_RIGHT) {
        if (g_TeamManagement.zMenuOpen[team] != 0) {
            if (g_TeamManagement.zMenuPage[team] != Z_MENU_PAGE_MAIN) {
                return;
            }
            g_TeamManagement.zMenuPage[team] = Z_MENU_PAGE_STAR_MOVES;
            g_TeamManagement.zMenuPageLoaded[team] = 0;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            return;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE && g_TeamManagement.unkCF70 != 0) {
            return;
        }
        if (g_TeamManagement.teamConfirmed[team] != 0) {
            return;
        }
        swapPosMenu_left_rightPress(1, team);
        return;
    }

    if (input.newInput & PAD_TRIGGER_R) {
        if (g_TeamManagement.zMenuOpen[team] != 0) {
            g_TeamManagement.zMenuOpen[team] = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (g_TeamManagement.teamMenuType[team] == TEAM_MENU_TYPE_BATTER_SWAP) {
            return;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE && g_TeamManagement.unkCF70 != 0) {
            return;
        }
        if (g_d_GameSettings._06 == 2) {
            return;
        }
        if (g_TeamManagement.rosterView[team] == ROSTER_VIEW_DEFENSIVE_ALIGNMENT) {
            return;
        }
        g_TeamManagement.prevRosterView[team] = g_TeamManagement.rosterView[team];
        g_TeamManagement.onFieldingAlignmentScreen2[team]++;
        if ((s8)g_TeamManagement.onFieldingAlignmentScreen2[team] > 1) {
            g_TeamManagement.onFieldingAlignmentScreen2[team] = 1;
        }
        g_TeamManagement.rosterView[team] = ROSTER_VIEW_DEFENSIVE_ALIGNMENT;
        updateCharacterSelectProcessCode(team, CHAR_SELECT_PROCESS_TM_CHANGE_ROSTER_VIEW);
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        return;
    }

    if (input.newInput & PAD_TRIGGER_L) {
        if (g_TeamManagement.zMenuOpen[team] != 0) {
            g_TeamManagement.zMenuOpen[team] = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (g_TeamManagement.teamMenuType[team] == TEAM_MENU_TYPE_BATTER_SWAP) {
            return;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE && g_TeamManagement.unkCF70 != 0) {
            return;
        }
        if (g_d_GameSettings._06 == 2) {
            return;
        }
        if (g_TeamManagement.rosterView[team] == ROSTER_VIEW_BATTING_ORDER) {
            return;
        }
        g_TeamManagement.prevRosterView[team] = g_TeamManagement.rosterView[team];
        g_TeamManagement.onFieldingAlignmentScreen2[team]--;
        if ((s8)g_TeamManagement.onFieldingAlignmentScreen2[team] < 0) {
            g_TeamManagement.onFieldingAlignmentScreen2[team] = 0;
        }
        g_TeamManagement.rosterView[team] = ROSTER_VIEW_BATTING_ORDER;
        updateCharacterSelectProcessCode(team, CHAR_SELECT_PROCESS_TM_CHANGE_ROSTER_VIEW);
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        return;
    }

    if (input.newInput & PAD_BUTTON_X) {
        if (g_TeamManagement.zMenuOpen[team] != 0) {
            g_TeamManagement.zMenuOpen[team] = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (g_TeamManagement.teamManagement_cursorPos[team] == 0) {
            return;
        }
        if (g_TeamManagement.teamMenuType[team] == TEAM_MENU_TYPE_BATTER_SWAP) {
            return;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE && g_TeamManagement.unkCF70 != 0) {
            return;
        }
        if (g_d_GameSettings._06 == 2) {
            return;
        }
        if (g_TeamManagement.teamConfirmed[team] != 0) {
            return;
        }
        g_TeamManagement.stanceChangeRequested[team] = 1;
        return;
    }

    if (input.newInput & PAD_BUTTON_Y) {
        if (g_TeamManagement.zMenuOpen[team] != 0) {
            g_TeamManagement.zMenuOpen[team] = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (g_TeamManagement.teamManagement_cursorPos[team] == 0) {
            return;
        }
        if (g_d_GameSettings._06 == 2) {
            return;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            if (g_TeamManagement.starMenuOpen != 0) {
                return;
            }
            g_TeamManagement.starMenuCharID = inMemRoster[0][g_TeamManagement.teamManagement_cursorPos[0] - 1].stats.CharID;
            g_TeamManagement.starMenuOpen = 1;
            g_TeamManagement.starMenuActive = 1;
            g_TeamManagement.starMenuPrevCursorPos = 0;
            g_TeamManagement.starMenuCursorPos = 0;
            g_TeamManagement.starMenuDrawStep = STAR_MENU_DRAW_STEP_OPEN;
            g_TeamManagement.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_STAR_MENU_UNUSED;
            sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
            return;
        }
        if (superstarUnlocked[inMemRoster[team][g_TeamManagement.teamManagement_cursorPos[team] - 1].stats.CharID] == 0) {
            return;
        }
        if (g_TeamManagement.inProgress_superStarAPlayer[team] != 0) {
            return;
        }
        g_TeamManagement.inProgress_superStarAPlayer[team] = 1;
        sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
        return;
    }

    if (input.newInput & PAD_BUTTON_A) {
        if (g_TeamManagement.zMenuOpen[team] != 0) {
            g_TeamManagement.zMenuOpen[team] = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (g_TeamManagement.teamConfirmed[team] != 0) {
            return;
        }
        if (gameSetUpStep.preventCursorMovement[0] != 0) {
            return;
        }
        if (gameSetUpStep.preventCursorMovement[1] != 0) {
            return;
        }
        if (g_d_GameSettings._06 == 2) {
            if (g_TeamManagement.teamManagement_cursorPos[team] != 0 && g_TeamManagement.teamMenuType[team] == TEAM_MENU_TYPE_BATTER_SWAP) {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
                return;
            }
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE && g_TeamManagement.unkCF70 != 0 &&
            superstarUnlocked[0xE4] == 0) {
            g_TeamManagement.unkCF70 = 0;
            g_TeamManagement.unkCF6B = 1;
            updateCharacterSelectProcessCode(0, 0x46);
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            return;
        }

        if (g_TeamManagement.teamManagement_cursorPos[team] != 0) {
            g_TeamManagement.teamManagement_prevCursorPos[team] = g_TeamManagement.teamManagement_cursorPos[team];
            if (g_TeamManagement.charSelectedToBeSwapped[team] == 0) {
                g_TeamManagement.charSelectedToBeSwappedCharID[team] =
                    fn_800471F4(g_TeamManagement.charSelectedToBeSwapped[team], team);
                g_TeamManagement.charSelectedToBeSwapped[team] = 1;
                updateCharacterSelectProcessCode(team, CHAR_SELECT_PROCESS_TM_CURSOR_MOVE);
                lbl_803CBCC8 = 1;
            } else {
                g_TeamManagement.charSelectedToBeSwappedCharID[team] =
                    fn_800471F4(g_TeamManagement.charSelectedToBeSwapped[team], team);
                g_TeamManagement.charSelectedToBeSwapped[team] = 0;
                updateCharacterSelectProcessCode(team, CHAR_SELECT_PROCESS_TM_CURSOR_MOVE);
                g_TeamManagement.swapCompleted[team] = 1;
            }
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            return;
        }

        if (g_TeamManagement.teamConfirmed[0] != 0 && g_TeamManagement.teamConfirmed[1] != 0) {
            g_TeamManagement.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_UNLOAD_MENU_1;
        }
        if (g_TeamManagement.teamManagement_cursorPos[team] != 0) {
            sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            return;
        }
        if (g_d_GameSettings._06 == 2) {
            updateCharacterSelectProcessCode(team, CHAR_SELECT_PROCESS_TM_EXIT);
            g_TeamManagement.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_UNLOAD_MENU_1;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            return;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            updateCharacterSelectProcessCode(0, CHAR_SELECT_PROCESS_TM_EXIT);
            g_TeamManagement.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_UNLOAD_MENU_1;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            return;
        }
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && g_TeamManagement.teamConfirmed[0] == 0) {
            if (g_d_GameSettings._06 == 2) {
                g_TeamManagement.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_UNLOAD_MENU_2;
                updateCharacterSelectProcessCode(team, 0x33);
            } else {
                g_TeamManagement.unkCF40 = 1;
                g_TeamManagement.charSelectedToBeSwapped[team] = 0;
                g_TeamManagement.onePlayerEditingTeam = 1;
                g_TeamManagement.teamConfirmed[0] = 1;
                updateCharacterSelectProcessCode(team, CHAR_SELECT_PROCESS_TM_1P_TO_CPU_TEAM);
            }
            g_TeamManagement.teamConfirmed[0] = 1;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            return;
        }
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
            if (g_TeamManagement.teamConfirmed[1] == 0) {
                g_TeamManagement.teamConfirmed[1] = 1;
                if (g_TeamManagement.teamConfirmed[0] == 0) {
                    sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                    return;
                }
                if (g_TeamManagement.teamConfirmed[1] == 0) {
                    sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                    return;
                }
                updateCharacterSelectProcessCode(0, CHAR_SELECT_PROCESS_TM_EXIT);
                updateCharacterSelectProcessCode(1, CHAR_SELECT_PROCESS_TM_EXIT);
                g_TeamManagement.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_UNLOAD_MENU_1;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                return;
            }
        }
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_2_PLAYER_GAME) {
            g_TeamManagement.teamConfirmed[team] = 1;
            if (g_TeamManagement.teamConfirmed[0] != 0 && g_TeamManagement.teamConfirmed[1] != 0) {
                if (g_TeamManagement.waitingForOtherTeam[team ^ 1] != 0) {
                    g_TeamManagement.teamConfirmed[team] = 0;
                    return;
                }
                updateCharacterSelectProcessCode(0, CHAR_SELECT_PROCESS_TM_EXIT);
                updateCharacterSelectProcessCode(1, CHAR_SELECT_PROCESS_TM_EXIT);
                g_TeamManagement.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_UNLOAD_MENU_1;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                return;
            }
            g_TeamManagement.waitingForOtherTeam[team] = 1;
            updateCharacterSelectProcessCode(team, CHAR_SELECT_PROCESS_TM_WAIT_FOR_OTHER_TEAM);
        }
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        return;
    }

    if (input.newInput & PAD_BUTTON_B) {
        if (g_TeamManagement.zMenuOpen[team] != 0) {
            g_TeamManagement.zMenuOpen[team] = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE && g_TeamManagement.unkCF70 != 0) {
            g_TeamManagement.unkCF70 = 0;
            g_TeamManagement.unkCF6B = 1;
            updateCharacterSelectProcessCode(0, 0x46);
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (g_TeamManagement.charSelectedToBeSwapped[team] != 0) {
            g_TeamManagement.teamConfirmed[team] = 0;
            g_TeamManagement.charSelectedToBeSwapped[team] = 0;
            if (g_TeamManagement.teamManagement_cursorPos[team] == g_TeamManagement.teamManagement_prevCursorPos[team]) {
                g_TeamManagement.charSelectedToBeSwappedCharID[team] = 0xFF;
            } else {
                updateCharacterSelectProcessCode(team, CHAR_SELECT_PROCESS_TM_CANCEL_SWAP);
            }
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (g_TeamManagement.teamManagement_cursorPos[team] != 0) {
            g_TeamManagement.teamManagement_prevCursorPos[team] = g_TeamManagement.teamManagement_cursorPos[team];
            g_TeamManagement.teamManagement_cursorPos[team] = 0;
            updateCharacterSelectProcessCode(team, CHAR_SELECT_PROCESS_TM_CURSOR_TO_CONFIRM);
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && g_TeamManagement.onePlayerEditingTeam != 0) {
            g_TeamManagement.teamConfirmed[0] = 0;
            g_TeamManagement.onFieldingAlignmentScreen2[g_TeamManagement.onePlayerEditingTeam] = 0;
            g_TeamManagement.teamManagement_cursorPos[g_TeamManagement.onePlayerEditingTeam] = 0;
            g_TeamManagement.onePlayerEditingTeam = 0;
            g_TeamManagement.unkCF40 = 0;
            g_TeamManagement.onFieldingAlignmentScreen2[0] = 0;
            g_TeamManagement.teamManagement_cursorPos[0] = 0;
            updateCharacterSelectProcessCode(team, CHAR_SELECT_PROCESS_TM_1P_TO_OWN_TEAM);
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (g_TeamManagement.teamConfirmed[team] != 0) {
            updateCharacterSelectProcessCode(team, CHAR_SELECT_PROCESS_TM_CANCEL_CONFIRM);
            g_TeamManagement.teamConfirmed[team] = 0;
            g_TeamManagement.waitingForOtherTeam[team] = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        g_TeamManagement.onFieldingAlignmentScreen2[0] = 0;
        g_TeamManagement.teamManagement_cursorPos[0] = 0;
        g_TeamManagement.onFieldingAlignmentScreen2[1] = 0;
        g_TeamManagement.teamManagement_cursorPos[1] = 0;
        g_TeamManagement.onePlayerEditingTeam = 0;
        if (g_d_GameSettings._06 == 2) {
            updateCharacterSelectProcessCode(team, CHAR_SELECT_PROCESS_TM_EXIT);
            g_TeamManagement.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_UNLOAD_MENU_1;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        updateCharacterSelectProcessCode(0, CHAR_SELECT_PROCESS_TM_RETURN_TO_CSS);
        updateCharacterSelectProcessCode(1, CHAR_SELECT_PROCESS_TM_RETURN_TO_CSS);
        g_TeamManagement.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_RETURN_TO_CSS_1;
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        return;
    }

    return;
}

extern menuControlStruct* menuControlVariables;

/* File_0x80047ce0.c used the full TeamManagementState_s. */
#define g_TeamManagement (*(TeamManagementState_s*)&g_TeamManagement)

void initTeamManagementScreen(void) {
    Static_Stats_Tables.unk4720[0] = 0;
    Static_Stats_Tables.unk4720[1] = 0;
    g_TeamManagement.rosterView[0] = g_d_GameSettings._06 == 2;
    g_TeamManagement.rosterView[1] = g_d_GameSettings._06 == 2;

    g_TeamManagement.charSelectedToBeSwappedCharID[1] = 0xFF;
    g_TeamManagement.charSelectedToBeSwappedCharID[0] = 0xFF;
    g_TeamManagement.charSelectedToBeSwapped[1] = 0;
    g_TeamManagement.charSelectedToBeSwapped[0] = 0;
    g_TeamManagement.unkCF40 = 0;
    g_TeamManagement.unkCF41 = 0;
    g_TeamManagement.onePlayerEditingTeam = 0;
    g_TeamManagement.teamManagement_prevCursorPos[1] = 0;
    g_TeamManagement.teamManagement_prevCursorPos[0] = 0;
    g_TeamManagement.teamManagement_cursorPos[1] = 0;
    g_TeamManagement.teamManagement_cursorPos[0] = 0;
    g_TeamManagement.unkCF4C[1] = 0;
    g_TeamManagement.unkCF4C[0] = 0;
    g_TeamManagement.onFieldingAlignmentScreen2[1] = 0;
    g_TeamManagement.onFieldingAlignmentScreen2[0] = 0;
    g_TeamManagement.prevRosterView[1] = 0;
    g_TeamManagement.prevRosterView[0] = 0;
    g_TeamManagement.rosterView[1] = 0;
    g_TeamManagement.rosterView[0] = 0;
    g_TeamManagement.teamConfirmed[1] = 0;
    g_TeamManagement.teamConfirmed[0] = 0;
    g_TeamManagement.swapCompleted[1] = 0;
    g_TeamManagement.swapCompleted[0] = 0;
    g_TeamManagement.stanceChangeRequested[1] = 0;
    g_TeamManagement.stanceChangeRequested[0] = 0;

    Static_Stats_Tables._4705[0] = 1;
    gameSetUpStep.portCaptainSlot[0] = 0;
    gameSetUpStep.portCaptainSlot[1] = 1;

    if (g_d_GameSettings._06 != 2) {
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE && menuControlVariables->previousScreen == 0xA) {
            characterSelectScreen(0);
            characterSelectScreen(1);
        } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            if (g_Challenge.resumeSavedTeams == 0) {
                fn_800415A8();
                unsure_FillRosterPositions(1);
                characterSelectScreen(1);
            }
        }

        g_TeamManagement.teamMenuType[1] = TEAM_MENU_TYPE_FIELDER_SWAP;
        g_TeamManagement.teamMenuType[g_TeamManagement.playerWhoPaused] = TEAM_MENU_TYPE_FIELDER_SWAP;
        g_MatchInfo.unk36 = 1;
        g_MatchInfo.unk37 = g_MatchInfo.unk38;
        g_MatchInfo.unk38 = 1;
    } else {
        if (g_TeamManagement.teamMenuType[g_TeamManagement.playerWhoPaused] == TEAM_MENU_TYPE_FIELDER_SWAP) {
            g_TeamManagement.rosterView[1] = 1;
            g_TeamManagement.rosterView[0] = 1;
        } else {
            g_TeamManagement.rosterView[1] = 0;
            g_TeamManagement.rosterView[0] = 0;
        }
    }

    SetMenuNumber();

    if (!(g_d_GameSettings._06 == 2 || menuControlVariables->previousScreen == 0xA ||
          g_d_GameSettings.p2_CPU_match_code != P2_CPU_CODE_1_PLAYER_GAME || g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE)) {
        g_TeamManagement.onePlayerEditingTeam = 1;
        g_TeamManagement.teamConfirmed[0] = 1;
        updateCharacterSelectProcessCode(0, 0x39);
        updateCharacterSelectProcessCode(1, 0x39);
        g_TeamManagement.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_LOAD;
    } else {
        u8 cfa2 = g_TeamManagement.teamMenuType[g_TeamManagement.playerWhoPaused];

        if (cfa2 == TEAM_MENU_TYPE_SCOUT_FLAGS || cfa2 == TEAM_MENU_TYPE_STAR_MISSIONS) {
            if (cfa2 == TEAM_MENU_TYPE_SCOUT_FLAGS) {
                g_TeamManagement.scoutFlagMenuState = SCOUT_FLAG_MENU_STATE_OPEN;
                g_TeamManagement.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_SCOUT_FLAGS_MENU;
            } else {
                g_TeamManagement.challengeCheckStarsMenuSceneLoadingNumber = CHECK_STARS_SCENE_LOAD;
                g_TeamManagement.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_CHALLENGE_STARS_MENU;
            }
        } else {
            updateCharacterSelectProcessCode(0, CHAR_SELECT_PROCESS_TM_LOAD);
            if (g_d_GameSettings._06 == 2) {
                updateCharacterSelectProcessCode(1, CHAR_SELECT_PROCESS_TM_LOAD);
            } else {
                updateCharacterSelectProcessCode(1, CHAR_SELECT_PROCESS_TM_LOAD);
            }
            g_TeamManagement.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_LOAD;
        }
    }
}

#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x80047ce0.h"
#include "Unknown/orderchange.h"
#include "Unknown/File_0x8004ca6c.h"
#include "Unknown/File_0x8004cc18.h"
#include "Unknown/mb_subfunc.h"
#include "Unknown/File_0x800204cc.h"
#include "Unknown/File_0x80021410.h"
#include "Unknown/File_0x80035ca4.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x80062a50.h"
#include "menus/yd_step.h"
#include "game/challenge/challenge_state.h"
#include "musyx/musyx.h"

#undef g_TeamManagement

/* File_0x80047fe4.c's own view of g_TeamManagement is merged into the
 * declaration at the top of this file. */

extern u8 menuNumber[0x28];
extern u8 lbl_803CBCC9;
extern u8 lbl_803CBD24[0xC];
extern menuControlStruct *menuControlVariables;
extern s8 lineUpInfoStruct[2][9][4];
extern void teamManagement_takeInputs(s32 player);
extern void fn_8004D0F0(void);

void pauseMenuSelection(void) {
    s32 i;
    u8 *stats = (u8 *)&Static_Stats_Tables;

    switch (g_TeamManagement.teamManagementProcessID) {
    case TEAM_MANAGEMENT_PROCESS_INITIALIZE:
        initTeamManagementScreen();
        break;

    case TEAM_MANAGEMENT_PROCESS_LOAD:
        g_TeamManagement.teamManagement_cursorPos[1] = 0;
        g_TeamManagement.teamManagement_cursorPos[0] = 0;
        g_TeamManagement.onFieldingAlignmentScreen2[1] = 0;
        g_TeamManagement.onFieldingAlignmentScreen2[0] = 0;
        g_TeamManagement.teamManagementProcessID++;
        break;

    case TEAM_MANAGEMENT_PROCESS_ON_SCREEN:
        i = 0;
        do {
            teamManagement_takeInputs(i);
            i++;
        } while (i < 2);
        break;

    case TEAM_MANAGEMENT_PROCESS_STAR_MENU_UNUSED:
        starMenuCursor();
        break;

    case TEAM_MANAGEMENT_PROCESS_SCOUT_FLAGS_MENU: {
        u16 saved[3];
        u16 *row;
        u16 v0, v1, v2;

        memset(saved, 0, 6);
        if (gameSetUpStep.currentCharacterSelectProcess[0] != 0) {
            break;
        }
        row = (u16 *)((u8 *)&g_TeamManagement + (s8)stats[0x46F8] * 6);
        v0 = row[0];
        v1 = row[1];
        v2 = row[2];
        if ((v1 & 0x200) == 0) {
            break;
        }
        saved[0] = v0;
        saved[1] = v1;
        saved[2] = v2;
        g_TeamManagement.scoutFlagMenuState = SCOUT_FLAG_MENU_STATE_CLOSE;
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, SND_STUDIO_DEFAULT);
        g_TeamManagement.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_UNLOAD_MENU_2;
        break;
    }

    case TEAM_MANAGEMENT_PROCESS_CHALLENGE_STARS_MENU:
        challengeStarMenu();
        break;

    case 6:
        if (lbl_803CBCC9 == 1) {
            s32 res = exitMenu(*(u16 *)(stats + 0x472E + (s8)stats[0x46F8 + lbl_803CBD24[4]] * 6));
            switch (res) {
            case 1:
            case 2:
                set803c5f77();
                break;

            case 3:
                characterSelectScreen(0);
                characterSelectScreen(1);
                selectRandomStadium();
                menuNumber[0x26] = 1;
                changeScene(0xF, 6);
                lbl_803CBD24[4] = 0;
                lbl_803CBCC9 = 0;
                g_TeamManagement.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_UNLOAD_MENU_2;
                break;

            case 4:
                lbl_803CBD24[4] = 0;
                g_TeamManagement.loadMatchRelInd = 0;
                lbl_803CBCC9 = 0;
                g_TeamManagement.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_ON_SCREEN;
                break;

            default:
                break;
            }
        } else if (lbl_803CBCC9 == 0) {
            insertGraphicDrawingFunction(fn_8004D0F0, 0x3000);
            lbl_803CBCC9 = lbl_803CBCC9 + 1;
        }
        break;

    case 10: {
        if (g_TeamManagement.loadMatchRelInd != 0) {
            stats[0x48AD] = 1;
            gameSetUpStep.screen = 0;
            memset(&gameSetUpStep.stepFlags[0][0], 0, 6);
            g_TeamManagement.waitingForOtherTeam[1] = 0;
            g_TeamManagement.waitingForOtherTeam[0] = 0;
            g_TeamManagement.teamConfirmed[1] = 0;
            g_TeamManagement.teamConfirmed[0] = 0;
            fn_80062A74();
            maybeLoadsGameSoundFiles();
            unregisterObjectByID(0xF);
            unregisterObjectByID(0x12);
            unregisterObjectByID(0x9);
            unregisterObjectByID(0x6);
            stats[0x48AF] = 1;
            stats[0x48B1] = 1;
            g_TeamManagement.loadMatchRelInd = 0;
            menuControlVariables->previousScreen = menuControlVariables->currentScreen;
            menuControlVariables->previousState = menuControlVariables->currentState;
            menuControlVariables->currentScreen = 4;
            menuControlVariables->currentState = 0;
        } else {
            u8 port = g_TeamManagement.playerWhoPaused;

            if (menuNumber[0x24] != 0) {
                break;
            }
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                if (g_TeamManagement.teamMenuType[port] != TEAM_MENU_TYPE_SCOUT_FLAGS && g_TeamManagement.teamMenuType[port] != TEAM_MENU_TYPE_STAR_MISSIONS) {
                    u8 *roster = (u8 *)inMemRoster;
                    u8 *lineup = (u8 *)lineUpInfoStruct;
                    u8 *dst = (u8 *)&g_Challenge;

                    for (i = 0; i < 3; i++) {
                        *(s16 *)(dst + 0x40B8) = *(s16 *)(roster + 0x24);
                        dst[0x40BA] = lineup[1];
                        dst[0x40BB] = lineup[2];
                        dst[0x40BC] = roster[0x27] + (roster[0x26] << 1);
                        *(s16 *)(dst + 0x40BE) = *(s16 *)(roster + 0xC4);
                        dst[0x40C0] = lineup[5];
                        dst[0x40C1] = lineup[6];
                        dst[0x40C2] = roster[0xC7] + (roster[0xC6] << 1);
                        *(s16 *)(dst + 0x40C4) = *(s16 *)(roster + 0x164);
                        dst[0x40C6] = lineup[9];
                        dst[0x40C7] = lineup[10];
                        dst[0x40C8] = roster[0x167] + (roster[0x166] << 1);
                        lineup += 0xC;
                        roster += 0x1E0;
                        dst += 0x12;
                    }
                    g_TeamManagement.challengeLoadingNormalMatchInd = 0;
                }
                if (g_d_GameSettings._06 == 2 && g_TeamManagement.teamMenuType[port] == TEAM_MENU_TYPE_SCOUT_FLAGS &&
                    g_TeamManagement.scoutFlagMenuState != 0) {
                    break;
                }
            }

            g_TeamManagement.unkCF40 = 0;
            g_TeamManagement.charSelectedToBeSwapped[1] = 0;
            g_TeamManagement.charSelectedToBeSwapped[0] = 0;
            g_TeamManagement.waitingForOtherTeam[1] = 0;
            g_TeamManagement.waitingForOtherTeam[0] = 0;
            g_TeamManagement.teamConfirmed[1] = 0;
            g_TeamManagement.teamConfirmed[0] = 0;
            setCaptainLocInRoster();

            if (g_d_GameSettings._06 != 2 && g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                menuControlVariables->previousScreen = menuControlVariables->currentScreen;
                menuControlVariables->previousState = menuControlVariables->currentState;
                menuControlVariables->currentScreen = 0xD;
                menuControlVariables->currentState = 0;
            } else if (g_d_GameSettings._06 == 2) {
                if (g_TeamManagement.teamMenuType[port] != TEAM_MENU_TYPE_SCOUT_FLAGS && g_TeamManagement.teamMenuType[port] != TEAM_MENU_TYPE_STAR_MISSIONS) {
                    if (gameSetUpStep.preventCursorMovement[0] != 0) {
                        break;
                    }
                    if (gameSetUpStep.preventCursorMovement[1] != 0) {
                        break;
                    }
                }
                g_TeamManagement.onMainPauseMenu = 1;
                g_TeamManagement.unkCF40 = 0;
            } else {
                menuControlVariables->previousScreen = menuControlVariables->currentScreen;
                menuControlVariables->previousState = menuControlVariables->currentState;
                menuControlVariables->currentScreen = 0xC;
                menuControlVariables->currentState = 0;
            }
        }

        if (g_TeamManagement.teamMenuType[g_TeamManagement.playerWhoPaused] != TEAM_MENU_TYPE_SCOUT_FLAGS &&
            g_TeamManagement.teamMenuType[g_TeamManagement.playerWhoPaused] != TEAM_MENU_TYPE_STAR_MISSIONS) {
            g_TeamManagement.removeSceneRequested = 1;
        }
        g_TeamManagement.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_INITIALIZE;
        removeCurrentDrawingItem();
        break;
    }

    case TEAM_MANAGEMENT_PROCESS_RETURN_TO_CSS_1:
        if (gameSetUpStep.preventCursorMovement[0] != 0) {
            break;
        }
        if (gameSetUpStep.preventCursorMovement[1] != 0) {
            break;
        }
        memset(stats + 0x489B, 0, 0x12);
        g_TeamManagement.teamConfirmed[1] = 0;
        g_TeamManagement.teamConfirmed[0] = 0;
        g_TeamManagement.removeSceneRequested = 1;
        g_TeamManagement.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_RETURN_TO_CSS_2;
        break;

    case TEAM_MANAGEMENT_PROCESS_RETURN_TO_CSS_2:
        g_TeamManagement.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_INITIALIZE;
        g_TeamManagement.zMenuOpen[1] = 0;
        g_TeamManagement.zMenuOpen[0] = 0;
        g_TeamManagement.waitingForOtherTeam[1] = 0;
        g_TeamManagement.waitingForOtherTeam[0] = 0;
        g_TeamManagement.teamConfirmed[1] = 0;
        g_TeamManagement.teamConfirmed[0] = 0;
        {
            u8 tmp = g_MatchInfo.unk38;
            g_MatchInfo.unk36 = 1;
            g_MatchInfo.unk37 = tmp;
            g_MatchInfo.unk38 = 0;
        }
        menuControlVariables->previousScreen = menuControlVariables->currentScreen;
        menuControlVariables->previousState = menuControlVariables->currentState;
        menuControlVariables->currentScreen = 0xA;
        menuControlVariables->currentState = 0;
        removeCurrentDrawingItem();
        break;

    case TEAM_MANAGEMENT_PROCESS_UNLOAD_MENU_1:
        if (gameSetUpStep.preventCursorMovement[0] == 0 && gameSetUpStep.preventCursorMovement[1] == 0) {
            g_TeamManagement.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_UNLOAD_MENU_2;
        }
        break;

    default:
        break;
    }
}

