#include "Unknown/File_0x800486e0.h"
#include "Unknown/File_0x80047fe4.h"
#include "Unknown/File_0x800b0a14.h"
#define TEAM_MANAGEMENT_LOCAL_VIEW
#include "static/UnknownHomes_Static.h"

// Only the team-management/pause state this unit touches; see
// TEAM_MANAGEMENT_LOCAL_VIEW for why the full-size type is not used.
extern struct {
    /* 0x0000 */ u8 _0000[0xCF38];
    /* 0xCF38 */ u16 teamManagementProcessID;
    /* 0xCF3A */ s8 teamThatPaused;
    /* 0xCF3B */ u8 playerWhoPaused;
    /* 0xCF3C */ u8 _CF3C[0xCF42 - 0xCF3C];
    /* 0xCF42 */ u8 onMainPauseMenu;
} g_TeamManagement;

void createTeamManagementScreen_inGame(u32 priority, s8 team, u8 player) {
    insertGraphicDrawingFunction(pauseMenuSelection, priority);
    g_TeamManagement.teamManagementProcessID = 0;
    g_TeamManagement.teamThatPaused = team;
    g_TeamManagement.onMainPauseMenu = 0;
    if (g_d_GameSettings.highLevelMenuScene != HIGH_LEVEL_MENU_SCENE_IN_GAME) {
        g_TeamManagement.playerWhoPaused = 0;
    } else {
        g_TeamManagement.playerWhoPaused = player;
    }
}
