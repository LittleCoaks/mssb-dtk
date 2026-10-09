#include "game/match_setup/rep_0.h"
#include "Dolphin/stl.h"
#include "game/UnknownHomes_Game.h"
#include "header_rep_data.h"
#include "Unknown/File_0x800a70dc.h"
#include "Unknown/File_0x800a7568.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x800bf038.h"
#include "game/animation/scene_effects.h"
#include "game/match_setup/match_flow.h"
#include "game/match_setup/match_loading.h"
#include "static/UnknownHomes_Static.h"

extern s8 lineUpInfoStruct[TEAMS_PER_GAME][PLAYERS_PER_TEAM][4];
extern u8 lbl_3_data_118[0xB8];

MatchFileDescriptor rosterFileDescriptorGame = {0x00000000, 0x000046E0, 0x06CF8800, 0x000046E0};

char lbl_3_data_10[12][22] = {
    "Yokohama Stadium    ",
    "Tokyo Dome          ",
    "Nagoya Dome         ",
    "Kousien Stadium     ",
    "Hirosima Stadium    ",
    "Jingu Stadium       ",
    "Green Stadium Kobe  ",
    "Osaka Dome          ",
    "Seibu Dome          ",
    "Fukuoka Dome        ",
    "Chiba Marine Stadium",
    "Sapporo Dome        ",
};

static u32 lbl_3_bss_0;
static void* lbl_3_bss_4[3];
static struct {
    u8 state;
    u8 step;
    u8 cursor;
    u8 mode;
    u8 _04[4];
} lbl_3_bss_10;

void _prolog(void) {
    insertGraphicDrawingFunction(transferSomeValuesOnMatchLoad, 1);
    fn_3_C0824();
    fn_80036C88(lbl_3_data_118, lbl_3_data_118 + 0x5C);
    fn_800B0D28(lbl_3_data_118 + 0x5C);
    fn_8004B270();
}

void _epilog(void) {
    g_d_GameSettings._55 = 0;
    maybeUpdateFunctionPointer(NULL);
    fn_3_BF20C();
}

void fn_3_258(void) {
    if (lbl_3_bss_10.mode == 0) {
        u16 buttons = ((u16*)&AtBat_ButtonInput1)[2];

        if ((buttons & INPUT_BUTTON_UP) && lbl_3_bss_10.step != 0) {
            lbl_3_bss_10.step--;
        }
        if ((buttons & INPUT_BUTTON_DOWN) && lbl_3_bss_10.step < 1) {
            lbl_3_bss_10.step++;
        }
        if (buttons & INPUT_BUTTON_A) {
            lbl_3_bss_10.mode = 1;
        }
        return;
    }
    if (lbl_3_bss_10.mode == 1 && lbl_3_bss_10.step == 0) {
        u16 buttons = ((u16*)&AtBat_ButtonInput1)[2];

        if ((buttons & INPUT_BUTTON_UP) && lbl_3_bss_10.cursor != 0) {
            lbl_3_bss_10.cursor--;
        }
        if ((buttons & INPUT_BUTTON_DOWN) && lbl_3_bss_10.cursor < 3) {
            lbl_3_bss_10.cursor++;
        }
        if (buttons & INPUT_BUTTON_A) {
            lbl_3_bss_10.mode = 3;
        }
        if (buttons & INPUT_BUTTON_B) {
            lbl_3_bss_10.mode = 0;
        }
        return;
    }
    if (lbl_3_bss_10.mode == 1 && lbl_3_bss_10.step == 1) {
        g_d_GameSettings.GameModeSelected = GAME_TYPE_PRACTICE;
        currentDrawingItem->func = maybeProcessTeamData;
        return;
    }
    if (lbl_3_bss_10.mode == 2) {
        return;
    }
    if (lbl_3_bss_10.mode == 3) {
        u16 buttons = ((u16*)&AtBat_ButtonInput1)[2];

        if ((buttons & INPUT_BUTTON_LEFT) && g_d_GameSettings.StadiumID != 0) {
            g_d_GameSettings.StadiumID--;
        }
        if ((buttons & INPUT_BUTTON_RIGHT) && g_d_GameSettings.StadiumID < 10) {
            g_d_GameSettings.StadiumID++;
        }
        if (buttons & INPUT_BUTTON_A) {
            lbl_3_bss_10.mode = 4;
        }
        if (buttons & INPUT_BUTTON_B) {
            lbl_3_bss_10.mode = 1;
        }
        return;
    }
    if (lbl_3_bss_10.mode == 4) {
        g_d_GameSettings.GameModeSelected = GAME_TYPE_EXHIBITION_GAME;
        g_d_GameSettings.p2_CPU_match_code = lbl_3_bss_10.cursor;
        currentDrawingItem->func = maybeProcessTeamData;
    }
}

void maybeProcessTeamData(void) {
    int team;
    int i;
    int slot;
    int teams[TEAMS_PER_GAME];
    u8* lineup;

    teams[0] = g_d_GameSettings.maybeHomeAway[0];
    teams[1] = g_d_GameSettings.maybeHomeAway[1];

    switch (lbl_3_bss_10.state) {
    case 0:
        lbl_3_bss_4[0] = ARAMTransfer(&rosterFileDescriptorGame, 0, 1, 0);
        lbl_3_bss_10.state++;
        break;
    case 1:
        if (lbl_803C6CF8.cancel.bytes[1] == TRUE) {
            lbl_3_bss_10.state++;
        }
        break;
    case 2:
        memcpy(&inMemRoster[0], (u8*)lbl_3_bss_4[0] + teams[0] * sizeof(inMemRoster[0]), sizeof(inMemRoster[0]));
        memcpy(&inMemRoster[1], (u8*)lbl_3_bss_4[0] + teams[1] * sizeof(inMemRoster[0]), sizeof(inMemRoster[0]));
        lbl_3_bss_10.state++;
        break;
    case 3:
        for (team = 0; team < TEAMS_PER_GAME; team++) {
            u8* lineup = (u8*)lbl_3_bss_4[0] + teams[team] * 0x48 + 0x4380;
            for (i = 0; i < PLAYERS_PER_TEAM; i++) {
                lineUpInfoStruct[team][i][0] = i;
                lineUpInfoStruct[team][i][1] = 0xA;
                lineUpInfoStruct[team][i][2] = 0xA;
                lineUpInfoStruct[team][i][3] = 0;
                for (slot = 0; slot < PLAYERS_PER_TEAM; slot++) {
                    if (lineup[slot] == i) {
                        break;
                    }
                }
                if (slot < PLAYERS_PER_TEAM) {
                    lineUpInfoStruct[team][i][1] = slot;
                    lineUpInfoStruct[team][i][2] = lineup[slot + PLAYERS_PER_TEAM];
                    lineUpInfoStruct[team][i][3] = 1;
                }
            }
        }
        lbl_3_bss_10.state++;
        break;
    }
}
