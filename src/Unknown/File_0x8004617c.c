#include "Unknown/File_0x8004617c.h"
#define AIPOSSWAPINPUTS_LOCAL_VIEW
#include "static/UnknownHomes_Static.h"
#include "Unknown/orderchange.h"
#include "Unknown/File_0x800625a4.h"
#include "Dolphin/pad.h"
#include "Dolphin/stl.h"
#include "musyx/musyx.h"

// Only the team-management state this unit touches; see
// AIPOSSWAPINPUTS_LOCAL_VIEW for why the full-size type is not used.
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
    /* 0xCF43 */ u8 unkCF43;
    /* 0xCF44 */ u8 _CF44[2];
    /* 0xCF46 */ s8 teamManagement_cursorPos[2];
    /* 0xCF48 */ s8 teamManagement_prevCursorPos[2];
    /* 0xCF4A */ u8 onFieldingAlignmentScreen2[2];
    /* 0xCF4C */ u8 unkCF4C[2];
    /* 0xCF4E */ u8 unkCF4E[2];
    /* 0xCF50 */ u8 unkCF50[2];
    /* 0xCF52 */ E(u8, ROSTER_VIEW) rosterView[2];
    /* 0xCF54 */ u8 unkCF54[2];
    /* 0xCF56 */ u8 unkCF56[2];
    /* 0xCF58 */ u8 unkCF58[2];
    /* 0xCF5A */ u8 _CF5A[0xCF61 - 0xCF5A];
    /* 0xCF61 */ u8 unkCF61[2];
    /* 0xCF63 */ u8 unkCF63[2];
    /* 0xCF65 */ u8 unkCF65[2];
    /* 0xCF67 */ u8 unkCF67[2];
    /* 0xCF69 */ u8 _CF69[0xCF6B - 0xCF69];
    /* 0xCF6B */ u8 unkCF6B;
    /* 0xCF6C */ u8 _CF6C[0xCF70 - 0xCF6C];
    /* 0xCF70 */ u8 unkCF70;
    /* 0xCF71 */ u8 unkCF71;
    /* 0xCF72 */ u8 unkCF72;
    /* 0xCF73 */ u8 _CF73;
    /* 0xCF74 */ u8 unkCF74;
    /* 0xCF75 */ u8 unkCF75;
    /* 0xCF76 */ u8 unkCF76;
    /* 0xCF77 */ u8 _CF77;
    /* 0xCF78 */ u16 unkCF78;
    /* 0xCF7A */ u8 _CF7A[0xCF9E - 0xCF7A];
    /* 0xCF9E */ u8 unkCF9E[2];
    /* 0xCFA0 */ u8 _CFA0[2];
    /* 0xCFA2 */ u8 unkCFA2[4];
} aiPosSwapInputs;

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
        if (aiPosSwapInputs.unkCF43 == 0) {
            team = 0;
        } else {
            team = 1;
        }
    }

    memset(&input, 0, sizeof(input));
    if (aiPosSwapInputs.teamThatPaused == -1) {
        input.currentHeldInput = Static_Stats_Tables.controllerInputs[playerIndex].currentHeldInput;
    } else {
        input.currentHeldInput = aiPosSwapInputs.playerInputs[playerIndex].currentHeldInput;
    }
    if (aiPosSwapInputs.teamThatPaused == -1) {
        input.newInput = Static_Stats_Tables.controllerInputs[playerIndex].newInput;
    } else {
        input.newInput = aiPosSwapInputs.playerInputs[playerIndex].newInput;
    }
    if (aiPosSwapInputs.teamThatPaused == -1) {
        input.processedInput = Static_Stats_Tables.controllerInputs[playerIndex].processedInput;
    } else {
        input.processedInput = aiPosSwapInputs.playerInputs[playerIndex].processedInput;
    }
    if (aiPosSwapInputs.unkCF4E[team] != 0) {
        input.currentHeldInput &= PAD_BUTTON_B;
        input.newInput &= PAD_BUTTON_B;
        input.processedInput &= PAD_BUTTON_B;
    }

    if (input.newInput & PAD_TRIGGER_Z) {
        if (aiPosSwapInputs.unkCF61[team] != 0) {
            aiPosSwapInputs.unkCF61[team] = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (aiPosSwapInputs.teamManagement_cursorPos[team] != 0) {
            aiPosSwapInputs.unkCF61[team] = 1;
            aiPosSwapInputs.unkCF65[team] = 1;
            aiPosSwapInputs.unkCF67[team] = 0;
            sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
        }
        return;
    }

    if (input.processedInput & PAD_BUTTON_UP) {
        if (aiPosSwapInputs.unkCF61[team] != 0) {
            return;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE && aiPosSwapInputs.unkCF70 != 0) {
            return;
        }
        if (aiPosSwapInputs.unkCF4E[team] != 0) {
            return;
        }
        swapPosMenu_up_downPress(0, team);
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        return;
    }

    if (input.processedInput & PAD_BUTTON_DOWN) {
        if (aiPosSwapInputs.unkCF61[team] != 0) {
            return;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE && aiPosSwapInputs.unkCF70 != 0) {
            return;
        }
        if (aiPosSwapInputs.unkCF4E[team] != 0) {
            return;
        }
        swapPosMenu_up_downPress(1, team);
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        return;
    }

    if (input.processedInput & PAD_BUTTON_LEFT) {
        if (aiPosSwapInputs.unkCF61[team] != 0) {
            if (aiPosSwapInputs.unkCF67[team] != 1) {
                return;
            }
            aiPosSwapInputs.unkCF67[team] = 0;
            aiPosSwapInputs.unkCF63[team] = 0;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            return;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE && aiPosSwapInputs.unkCF70 != 0) {
            return;
        }
        if (aiPosSwapInputs.unkCF4E[team] != 0) {
            return;
        }
        swapPosMenu_left_rightPress(0, team);
        return;
    }

    if (input.processedInput & PAD_BUTTON_RIGHT) {
        if (aiPosSwapInputs.unkCF61[team] != 0) {
            if (aiPosSwapInputs.unkCF67[team] != 0) {
                return;
            }
            aiPosSwapInputs.unkCF67[team] = 1;
            aiPosSwapInputs.unkCF63[team] = 0;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            return;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE && aiPosSwapInputs.unkCF70 != 0) {
            return;
        }
        if (aiPosSwapInputs.unkCF4E[team] != 0) {
            return;
        }
        swapPosMenu_left_rightPress(1, team);
        return;
    }

    if (input.newInput & PAD_TRIGGER_R) {
        if (aiPosSwapInputs.unkCF61[team] != 0) {
            aiPosSwapInputs.unkCF61[team] = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (aiPosSwapInputs.unkCFA2[team] == 1) {
            return;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE && aiPosSwapInputs.unkCF70 != 0) {
            return;
        }
        if (g_d_GameSettings._06 == 2) {
            return;
        }
        if (aiPosSwapInputs.rosterView[team] == ROSTER_VIEW_DEFENSIVE_ALIGNMENT) {
            return;
        }
        aiPosSwapInputs.unkCF54[team] = aiPosSwapInputs.rosterView[team];
        aiPosSwapInputs.onFieldingAlignmentScreen2[team]++;
        if ((s8)aiPosSwapInputs.onFieldingAlignmentScreen2[team] > 1) {
            aiPosSwapInputs.onFieldingAlignmentScreen2[team] = 1;
        }
        aiPosSwapInputs.rosterView[team] = ROSTER_VIEW_DEFENSIVE_ALIGNMENT;
        updateCharacterSelectProcessCode(team, 0x3C);
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        return;
    }

    if (input.newInput & PAD_TRIGGER_L) {
        if (aiPosSwapInputs.unkCF61[team] != 0) {
            aiPosSwapInputs.unkCF61[team] = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (aiPosSwapInputs.unkCFA2[team] == 1) {
            return;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE && aiPosSwapInputs.unkCF70 != 0) {
            return;
        }
        if (g_d_GameSettings._06 == 2) {
            return;
        }
        if (aiPosSwapInputs.rosterView[team] == ROSTER_VIEW_BATTING_ORDER) {
            return;
        }
        aiPosSwapInputs.unkCF54[team] = aiPosSwapInputs.rosterView[team];
        aiPosSwapInputs.onFieldingAlignmentScreen2[team]--;
        if ((s8)aiPosSwapInputs.onFieldingAlignmentScreen2[team] < 0) {
            aiPosSwapInputs.onFieldingAlignmentScreen2[team] = 0;
        }
        aiPosSwapInputs.rosterView[team] = ROSTER_VIEW_BATTING_ORDER;
        updateCharacterSelectProcessCode(team, 0x3C);
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        return;
    }

    if (input.newInput & PAD_BUTTON_X) {
        if (aiPosSwapInputs.unkCF61[team] != 0) {
            aiPosSwapInputs.unkCF61[team] = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (aiPosSwapInputs.teamManagement_cursorPos[team] == 0) {
            return;
        }
        if (aiPosSwapInputs.unkCFA2[team] == 1) {
            return;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE && aiPosSwapInputs.unkCF70 != 0) {
            return;
        }
        if (g_d_GameSettings._06 == 2) {
            return;
        }
        if (aiPosSwapInputs.unkCF4E[team] != 0) {
            return;
        }
        aiPosSwapInputs.unkCF58[team] = 1;
        return;
    }

    if (input.newInput & PAD_BUTTON_Y) {
        if (aiPosSwapInputs.unkCF61[team] != 0) {
            aiPosSwapInputs.unkCF61[team] = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (aiPosSwapInputs.teamManagement_cursorPos[team] == 0) {
            return;
        }
        if (g_d_GameSettings._06 == 2) {
            return;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            if (aiPosSwapInputs.unkCF71 != 0) {
                return;
            }
            aiPosSwapInputs.unkCF78 = inMemRoster[0][aiPosSwapInputs.teamManagement_cursorPos[0] - 1].stats.CharID;
            aiPosSwapInputs.unkCF71 = 1;
            aiPosSwapInputs.unkCF72 = 1;
            aiPosSwapInputs.unkCF76 = 0;
            aiPosSwapInputs.unkCF75 = 0;
            aiPosSwapInputs.unkCF74 = 1;
            aiPosSwapInputs.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_STAR_MENU_UNUSED;
            sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
            return;
        }
        if (superstarUnlocked[inMemRoster[team][aiPosSwapInputs.teamManagement_cursorPos[team] - 1].stats.CharID] == 0) {
            return;
        }
        if (aiPosSwapInputs.unkCF9E[team] != 0) {
            return;
        }
        aiPosSwapInputs.unkCF9E[team] = 1;
        sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
        return;
    }

    if (input.newInput & PAD_BUTTON_A) {
        if (aiPosSwapInputs.unkCF61[team] != 0) {
            aiPosSwapInputs.unkCF61[team] = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (aiPosSwapInputs.unkCF4E[team] != 0) {
            return;
        }
        if (gameSetUpStep.preventCursorMovement[0] != 0) {
            return;
        }
        if (gameSetUpStep.preventCursorMovement[1] != 0) {
            return;
        }
        if (g_d_GameSettings._06 == 2) {
            if (aiPosSwapInputs.teamManagement_cursorPos[team] != 0 && aiPosSwapInputs.unkCFA2[team] == 1) {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
                return;
            }
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE && aiPosSwapInputs.unkCF70 != 0 &&
            superstarUnlocked[0xE4] == 0) {
            aiPosSwapInputs.unkCF70 = 0;
            aiPosSwapInputs.unkCF6B = 1;
            updateCharacterSelectProcessCode(0, 0x46);
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            return;
        }

        if (aiPosSwapInputs.teamManagement_cursorPos[team] != 0) {
            aiPosSwapInputs.teamManagement_prevCursorPos[team] = aiPosSwapInputs.teamManagement_cursorPos[team];
            if (aiPosSwapInputs.charSelectedToBeSwapped[team] == 0) {
                aiPosSwapInputs.charSelectedToBeSwappedCharID[team] =
                    fn_800471F4(aiPosSwapInputs.charSelectedToBeSwapped[team], team);
                aiPosSwapInputs.charSelectedToBeSwapped[team] = 1;
                updateCharacterSelectProcessCode(team, 0x3B);
                lbl_803CBCC8 = 1;
            } else {
                aiPosSwapInputs.charSelectedToBeSwappedCharID[team] =
                    fn_800471F4(aiPosSwapInputs.charSelectedToBeSwapped[team], team);
                aiPosSwapInputs.charSelectedToBeSwapped[team] = 0;
                updateCharacterSelectProcessCode(team, 0x3B);
                aiPosSwapInputs.unkCF56[team] = 1;
            }
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            return;
        }

        if (aiPosSwapInputs.unkCF4E[0] != 0 && aiPosSwapInputs.unkCF4E[1] != 0) {
            aiPosSwapInputs.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_UNLOAD_MENU_1;
        }
        if (aiPosSwapInputs.teamManagement_cursorPos[team] != 0) {
            sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            return;
        }
        if (g_d_GameSettings._06 == 2) {
            updateCharacterSelectProcessCode(team, 0x43);
            aiPosSwapInputs.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_UNLOAD_MENU_1;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            return;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            updateCharacterSelectProcessCode(0, 0x43);
            aiPosSwapInputs.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_UNLOAD_MENU_1;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            return;
        }
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && aiPosSwapInputs.unkCF4E[0] == 0) {
            if (g_d_GameSettings._06 == 2) {
                aiPosSwapInputs.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_UNLOAD_MENU_2;
                updateCharacterSelectProcessCode(team, 0x33);
            } else {
                aiPosSwapInputs.unkCF40 = 1;
                aiPosSwapInputs.charSelectedToBeSwapped[team] = 0;
                aiPosSwapInputs.unkCF43 = 1;
                aiPosSwapInputs.unkCF4E[0] = 1;
                updateCharacterSelectProcessCode(team, 0x3F);
            }
            aiPosSwapInputs.unkCF4E[0] = 1;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            return;
        }
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
            if (aiPosSwapInputs.unkCF4E[1] == 0) {
                aiPosSwapInputs.unkCF4E[1] = 1;
                if (aiPosSwapInputs.unkCF4E[0] == 0) {
                    sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                    return;
                }
                if (aiPosSwapInputs.unkCF4E[1] == 0) {
                    sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                    return;
                }
                updateCharacterSelectProcessCode(0, 0x43);
                updateCharacterSelectProcessCode(1, 0x43);
                aiPosSwapInputs.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_UNLOAD_MENU_1;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                return;
            }
        }
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_2_PLAYER_GAME) {
            aiPosSwapInputs.unkCF4E[team] = 1;
            if (aiPosSwapInputs.unkCF4E[0] != 0 && aiPosSwapInputs.unkCF4E[1] != 0) {
                if (aiPosSwapInputs.unkCF50[team ^ 1] != 0) {
                    aiPosSwapInputs.unkCF4E[team] = 0;
                    return;
                }
                updateCharacterSelectProcessCode(0, 0x43);
                updateCharacterSelectProcessCode(1, 0x43);
                aiPosSwapInputs.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_UNLOAD_MENU_1;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                return;
            }
            aiPosSwapInputs.unkCF50[team] = 1;
            updateCharacterSelectProcessCode(team, 0x41);
        }
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        return;
    }

    if (input.newInput & PAD_BUTTON_B) {
        if (aiPosSwapInputs.unkCF61[team] != 0) {
            aiPosSwapInputs.unkCF61[team] = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE && aiPosSwapInputs.unkCF70 != 0) {
            aiPosSwapInputs.unkCF70 = 0;
            aiPosSwapInputs.unkCF6B = 1;
            updateCharacterSelectProcessCode(0, 0x46);
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (aiPosSwapInputs.charSelectedToBeSwapped[team] != 0) {
            aiPosSwapInputs.unkCF4E[team] = 0;
            aiPosSwapInputs.charSelectedToBeSwapped[team] = 0;
            if (aiPosSwapInputs.teamManagement_cursorPos[team] == aiPosSwapInputs.teamManagement_prevCursorPos[team]) {
                aiPosSwapInputs.charSelectedToBeSwappedCharID[team] = 0xFF;
            } else {
                updateCharacterSelectProcessCode(team, 0x44);
            }
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (aiPosSwapInputs.teamManagement_cursorPos[team] != 0) {
            aiPosSwapInputs.teamManagement_prevCursorPos[team] = aiPosSwapInputs.teamManagement_cursorPos[team];
            aiPosSwapInputs.teamManagement_cursorPos[team] = 0;
            updateCharacterSelectProcessCode(team, 0x3E);
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && aiPosSwapInputs.unkCF43 != 0) {
            aiPosSwapInputs.unkCF4E[0] = 0;
            aiPosSwapInputs.onFieldingAlignmentScreen2[aiPosSwapInputs.unkCF43] = 0;
            aiPosSwapInputs.teamManagement_cursorPos[aiPosSwapInputs.unkCF43] = 0;
            aiPosSwapInputs.unkCF43 = 0;
            aiPosSwapInputs.unkCF40 = 0;
            aiPosSwapInputs.onFieldingAlignmentScreen2[0] = 0;
            aiPosSwapInputs.teamManagement_cursorPos[0] = 0;
            updateCharacterSelectProcessCode(team, 0x40);
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (aiPosSwapInputs.unkCF4E[team] != 0) {
            updateCharacterSelectProcessCode(team, 0x42);
            aiPosSwapInputs.unkCF4E[team] = 0;
            aiPosSwapInputs.unkCF50[team] = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        aiPosSwapInputs.onFieldingAlignmentScreen2[0] = 0;
        aiPosSwapInputs.teamManagement_cursorPos[0] = 0;
        aiPosSwapInputs.onFieldingAlignmentScreen2[1] = 0;
        aiPosSwapInputs.teamManagement_cursorPos[1] = 0;
        aiPosSwapInputs.unkCF43 = 0;
        if (g_d_GameSettings._06 == 2) {
            updateCharacterSelectProcessCode(team, 0x43);
            aiPosSwapInputs.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_UNLOAD_MENU_1;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        updateCharacterSelectProcessCode(0, 0x3A);
        updateCharacterSelectProcessCode(1, 0x3A);
        aiPosSwapInputs.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_RETURN_TO_CSS_1;
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        return;
    }

    return;
}
