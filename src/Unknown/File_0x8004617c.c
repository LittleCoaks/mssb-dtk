#include "Unknown/File_0x8004617c.h"
#define TEAM_MANAGEMENT_LOCAL_VIEW
#include "static/UnknownHomes_Static.h"
#include "Unknown/orderchange.h"
#include "Unknown/File_0x800625a4.h"
#include "Dolphin/pad.h"
#include "Dolphin/stl.h"
#include "musyx/musyx.h"

// Only the team-management state this unit touches; see
// TEAM_MANAGEMENT_LOCAL_VIEW for why the full-size type is not used.
extern struct {
    /* 0x0000 */ controllerInputStruct playerInputs[4];
    /* 0x0018 */ u8 _0018[0xCF38 - 0x18];
    /* 0xCF38 */ E(u16, TEAM_MANAGEMENT_PROCESS) teamManagementProcessID;
    /* 0xCF3A */ s8 teamThatPaused;
    /* 0xCF3B */ u8 _CF3B;
    /* 0xCF3C */ u8 charSelectedToBeSwapped[2];
    /* 0xCF3E */ u8 charSelectedToBeSwappedCharID[2];
    /* 0xCF40 */ u8 unkCF40;
    /* 0xCF41 */ u8 _CF41[2];
    /* 0xCF43 */ u8 onePlayerEditingTeam;
    /* 0xCF44 */ u8 _CF44[2];
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
    /* 0xCF5A */ u8 _CF5A[0xCF61 - 0xCF5A];
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
    /* 0xCF7A */ u8 _CF7A[0xCF9E - 0xCF7A];
    /* 0xCF9E */ u8 inProgress_superStarAPlayer[2];
    /* 0xCFA0 */ u8 _CFA0[2];
    /* 0xCFA2 */ E(u8, TEAM_MENU_TYPE) teamMenuType[4];
} g_TeamManagement;

extern struct {
    /* 0x00 */ u8 _00[0x55];
    /* 0x55 */ u8 preventCursorMovement[4];
} gameSetUpStep;

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
