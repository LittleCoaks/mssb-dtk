#include "Unknown/File_0x80047ce0.h"
#include "static/UnknownHomes_Static.h"
#include "game/challenge/challenge_state.h"
#include "menus/yd_step.h"
#include "Unknown/mb_subfunc.h"
#include "Unknown/File_0x8006236c.h"
#include "Unknown/File_0x800625a4.h"

typedef struct {
    /* 0x00 */ u8 _00[0x55];
    /* 0x55 */ u8 unk55[4];
    /* 0x59 */ u8 portCaptainSlot[4];
} gameSetUpStruct_t;

extern gameSetUpStruct_t gameSetUpStep;
extern menuControlStruct* menuControlVariables;

void initTeamManagementScreen(void) {
    Static_Stats_Tables.unk4720[0] = 0;
    Static_Stats_Tables.unk4720[1] = 0;
    g_TeamManagement.rosterView[0] = g_d_GameSettings.highLevelMenuScene == HIGH_LEVEL_MENU_SCENE_IN_GAME;
    g_TeamManagement.rosterView[1] = g_d_GameSettings.highLevelMenuScene == HIGH_LEVEL_MENU_SCENE_IN_GAME;

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

    if (g_d_GameSettings.highLevelMenuScene != HIGH_LEVEL_MENU_SCENE_IN_GAME) {
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

    if (!(g_d_GameSettings.highLevelMenuScene == HIGH_LEVEL_MENU_SCENE_IN_GAME || menuControlVariables->previousScreen == 0xA ||
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
            if (g_d_GameSettings.highLevelMenuScene == HIGH_LEVEL_MENU_SCENE_IN_GAME) {
                updateCharacterSelectProcessCode(1, CHAR_SELECT_PROCESS_TM_LOAD);
            } else {
                updateCharacterSelectProcessCode(1, CHAR_SELECT_PROCESS_TM_LOAD);
            }
            g_TeamManagement.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_LOAD;
        }
    }
}
