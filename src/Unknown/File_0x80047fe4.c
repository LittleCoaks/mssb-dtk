#include "Unknown/File_0x80047fe4.h"
#define TEAM_MANAGEMENT_LOCAL_VIEW
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

// Only the pause/team-management fields this unit touches; see
// TEAM_MANAGEMENT_LOCAL_VIEW for why the full-size type is not used.
extern struct {
    /* 0x0000 */ u8 _0000[0xCF38];
    /* 0xCF38 */ E(u16, TEAM_MANAGEMENT_PROCESS) teamManagementProcessID;
    /* 0xCF3A */ u8 _CF3A;
    /* 0xCF3B */ u8 playerWhoPaused;
    /* 0xCF3C */ u8 charSelectedToBeSwapped[2];
    /* 0xCF3E */ u8 _CF3E[2];
    /* 0xCF40 */ u8 unkCF40;
    /* 0xCF41 */ u8 _CF41;
    /* 0xCF42 */ u8 onMainPauseMenu;
    /* 0xCF43 */ u8 _CF43[2];
    /* 0xCF45 */ u8 removeSceneRequested;
    /* 0xCF46 */ s8 teamManagement_cursorPos[2];
    /* 0xCF48 */ u8 _CF48[2];
    /* 0xCF4A */ u8 onFieldingAlignmentScreen2[2];
    /* 0xCF4C */ u8 _CF4C[2];
    /* 0xCF4E */ u8 teamConfirmed[2];
    /* 0xCF50 */ u8 waitingForOtherTeam[2];
    /* 0xCF52 */ u8 _CF52[0xCF5F - 0xCF52];
    /* 0xCF5F */ u8 loadMatchRelInd;
    /* 0xCF60 */ u8 _CF60;
    /* 0xCF61 */ u8 zMenuOpen[2];
    /* 0xCF63 */ u8 _CF63[0xCF7D - 0xCF63];
    /* 0xCF7D */ E(u8, SCOUT_FLAG_MENU_STATE) scoutFlagMenuState;
    /* 0xCF7E */ u8 _CF7E[0xCFA1 - 0xCF7E];
    /* 0xCFA1 */ u8 challengeLoadingNormalMatchInd;
    /* 0xCFA2 */ E(u8, TEAM_MENU_TYPE) teamMenuType[4];
} g_TeamManagement;

extern u8 gameSetUpStep[0x64];
extern u8 menuNumber[0x28];
extern u8 lbl_803CBCC9;
extern u8 lbl_803CBD24[0xC];
extern u8 lbl_800EFBA4[0x10];
extern menuControlStruct *menuControlVariables;
extern s8 lineUpInfoStruct[2][9][4];
extern CharacterStats inMemRoster[2][9];
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
        if (gameSetUpStep[0x5D] != 0) {
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
            gameSetUpStep[0] = 0;
            memset(&gameSetUpStep[1], 0, 6);
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
                    if (gameSetUpStep[0x55] != 0) {
                        break;
                    }
                    if (gameSetUpStep[0x56] != 0) {
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
        if (gameSetUpStep[0x55] != 0) {
            break;
        }
        if (gameSetUpStep[0x56] != 0) {
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
        if (gameSetUpStep[0x55] == 0 && gameSetUpStep[0x56] == 0) {
            g_TeamManagement.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_UNLOAD_MENU_2;
        }
        break;

    default:
        break;
    }
}
