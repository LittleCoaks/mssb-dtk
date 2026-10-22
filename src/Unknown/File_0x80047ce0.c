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
    aiPosSwapInputs.rosterView[0] = g_d_GameSettings._06 == 2;
    aiPosSwapInputs.rosterView[1] = g_d_GameSettings._06 == 2;

    aiPosSwapInputs.charSelectedToBeSwappedCharID[1] = 0xFF;
    aiPosSwapInputs.charSelectedToBeSwappedCharID[0] = 0xFF;
    aiPosSwapInputs.charSelectedToBeSwapped[1] = 0;
    aiPosSwapInputs.charSelectedToBeSwapped[0] = 0;
    aiPosSwapInputs.unkCF40 = 0;
    aiPosSwapInputs.unkCF41 = 0;
    aiPosSwapInputs.onePlayerEditingTeam = 0;
    aiPosSwapInputs.teamManagement_prevCursorPos[1] = 0;
    aiPosSwapInputs.teamManagement_prevCursorPos[0] = 0;
    aiPosSwapInputs.teamManagement_cursorPos[1] = 0;
    aiPosSwapInputs.teamManagement_cursorPos[0] = 0;
    aiPosSwapInputs.unkCF4C[1] = 0;
    aiPosSwapInputs.unkCF4C[0] = 0;
    aiPosSwapInputs.onFieldingAlignmentScreen2[1] = 0;
    aiPosSwapInputs.onFieldingAlignmentScreen2[0] = 0;
    aiPosSwapInputs.prevRosterView[1] = 0;
    aiPosSwapInputs.prevRosterView[0] = 0;
    aiPosSwapInputs.rosterView[1] = 0;
    aiPosSwapInputs.rosterView[0] = 0;
    aiPosSwapInputs.teamConfirmed[1] = 0;
    aiPosSwapInputs.teamConfirmed[0] = 0;
    aiPosSwapInputs.swapCompleted[1] = 0;
    aiPosSwapInputs.swapCompleted[0] = 0;
    aiPosSwapInputs.stanceChangeRequested[1] = 0;
    aiPosSwapInputs.stanceChangeRequested[0] = 0;

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

        aiPosSwapInputs.teamMenuType[1] = 0;
        aiPosSwapInputs.teamMenuType[aiPosSwapInputs.playerWhoPaused] = 0;
        g_MatchInfo.unk36 = 1;
        g_MatchInfo.unk37 = g_MatchInfo.unk38;
        g_MatchInfo.unk38 = 1;
    } else {
        if (aiPosSwapInputs.teamMenuType[aiPosSwapInputs.playerWhoPaused] == 0) {
            aiPosSwapInputs.rosterView[1] = 1;
            aiPosSwapInputs.rosterView[0] = 1;
        } else {
            aiPosSwapInputs.rosterView[1] = 0;
            aiPosSwapInputs.rosterView[0] = 0;
        }
    }

    SetMenuNumber();

    if (!(g_d_GameSettings._06 == 2 || menuControlVariables->previousScreen == 0xA ||
          g_d_GameSettings.p2_CPU_match_code != P2_CPU_CODE_1_PLAYER_GAME || g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE)) {
        aiPosSwapInputs.onePlayerEditingTeam = 1;
        aiPosSwapInputs.teamConfirmed[0] = 1;
        updateCharacterSelectProcessCode(0, 0x39);
        updateCharacterSelectProcessCode(1, 0x39);
        aiPosSwapInputs.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_LOAD;
    } else {
        u8 cfa2 = aiPosSwapInputs.teamMenuType[aiPosSwapInputs.playerWhoPaused];

        if (cfa2 == 2 || cfa2 == 3) {
            if (cfa2 == 2) {
                aiPosSwapInputs.scoutFlagMenuState = 1;
                aiPosSwapInputs.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_SCOUT_FLAGS_MENU;
            } else {
                aiPosSwapInputs.challengeCheckStarsMenuSceneLoadingNumber = CHECK_STARS_SCENE_LOAD;
                aiPosSwapInputs.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_CHALLENGE_STARS_MENU;
            }
        } else {
            updateCharacterSelectProcessCode(0, 0x38);
            if (g_d_GameSettings._06 == 2) {
                updateCharacterSelectProcessCode(1, 0x38);
            } else {
                updateCharacterSelectProcessCode(1, 0x38);
            }
            aiPosSwapInputs.teamManagementProcessID = TEAM_MANAGEMENT_PROCESS_LOAD;
        }
    }
}
