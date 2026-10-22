#include "Unknown/File_0x80049878.h"
#include "mssbTypes.h"
#include "static/UnknownHomes_Static.h"
#include "game/challenge/challenge_state.h"
#include "Unknown/File_0x8004a2bc.h"

void possiblyTransferDataBetweenDifferentRels(void) {
    u8* gs = (u8*)&gameSettings;
    int i;
    u8 captain;

    lbl_803C5EF8[0] = 0;
    lbl_803C5EF8[4] = 0;
    lbl_803C5EF8[1] = 0;
    lbl_803C5EF8[5] = 0;
    lbl_803C5EF8[2] = 0;
    lbl_803C5EF8[6] = 0;
    lbl_803C5EF8[3] = 0;
    lbl_803C5EF8[7] = 0;
    gs[0x2E] = 0;

    if (Static_Stats_Tables.unk4704 == 0) {
        gs[0x3B] = 0;
        gs[0x40] = 0;
        gs[0x3C] = 1;
        gs[0x3D] = 1;
        gs[0x3E] = 2;
        gs[0x3F] = 0;
        gs[0x41] = 1;
        gs[0x42] = 1;
        gs[0x43] = 2;
        gs[0x44] = 0;
        gs[0x45] = 0;
        gs[0x46] = 0;
        gs[0x47] = 0;
        gs[0x48] = 1;
        gs[0x55] = 0;
        gs[0x56] = 0;
        gs[0x57] = 0;
        gs[0x58] = 1;
        gs[0x49] = 0;
        gs[0x4A] = 0;
        gs[0x4B] = 0;
        gs[0x4C] = 1;
        gs[0x59] = 0;
        gs[0x5A] = 0;
        gs[0x5B] = 0;
        gs[0x5C] = 1;
        gs[0x4D] = 0;
        gs[0x4E] = 0;
        gs[0x4F] = 0;
        gs[0x50] = 1;
        gs[0x5D] = 0;
        gs[0x5E] = 0;
        gs[0x5F] = 0;
        gs[0x60] = 1;
        gs[0x51] = 0;
        gs[0x52] = 0;
        gs[0x53] = 0;
        gs[0x54] = 1;
        gs[0x61] = 0;
        gs[0x62] = 0;
        gs[0x63] = 0;
        gs[0x64] = 1;
        Static_Stats_Tables.unk4704 = 1;
    } else {
        for (i = 0; i < 2; i++) {
            u8 port = g_d_GameSettings.PlayerPorts[i];
            GameControlOptions* opt;
            if (port < 4) {
                opt = &inningSetting.controlOptions[port];
            } else {
                opt = &inningSetting.controlOptions[i];
            }
            gs[0x45 + i * 4] = opt->easyBatting;
            gs[0x46 + i * 4] = opt->autoFielding;
            gs[0x47 + i * 4] = opt->autoRunning;
            gs[0x48 + i * 4] = opt->dropSpot;
        }

        gs[0x3C] = g_d_GameSettings.home_AwaySetting;
        gs[0x3D] = inningSetting.starSkillsSetting;
        gs[0x3E] = inningSetting.inningCount >> 1;
        if (inningSetting.runsNeededForMercy == 10) {
            gs[0x3F] = 1;
        } else {
            gs[0x3F] = 0;
        }
        inningSetting._pad_6[0] = 0;
    }

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        for (i = 0; i < 2; i++) {
            u8 port = g_d_GameSettings.PlayerPorts[i];
            GameControlOptions* opt;
            if (port < 4) {
                opt = &inningSetting.controlOptions[port];
            } else {
                opt = &inningSetting.controlOptions[i];
            }
            gs[0x45 + i * 4] = opt->easyBatting;
            gs[0x46 + i * 4] = opt->autoFielding;
            gs[0x47 + i * 4] = opt->autoRunning;
            gs[0x48 + i * 4] = opt->dropSpot;
        }

        captain = g_Challenge.captainCharID;
        gs[0x3C] = 0;
        gs[0x3F] = 1;
        gs[0x3D] = 1;
        gs[0x3C] = 0;
        gs[0x41] = 0;
        gs[0x44] = 1;
        gs[0x3F] = 1;

        if (captain == CHAR_ID_BOWSER) {
            if (g_Challenge._16C2 == 0x2A) {
                gs[0x3E] = challengeInnings[g_d_GameSettings.challengeDifficulty].finalBossInningLimit >> 1;
            } else {
                gs[0x3E] = challengeInnings[g_d_GameSettings.challengeDifficulty].inningLimit >> 1;
            }
        } else if (g_Challenge.opponentCaptainCharID == CHAR_ID_BOWSER) {
            gs[0x3E] = challengeInnings[g_d_GameSettings.challengeDifficulty].finalBossInningLimit >> 1;
        } else {
            gs[0x3E] = challengeInnings[g_d_GameSettings.challengeDifficulty].inningLimit >> 1;
        }
    }

    if (g_d_GameSettings.highLevelMenuScene == HIGH_LEVEL_MENU_SCENE_IN_GAME) {
        gs[0x36] = 1;
        gs[0x69] = 0;
        gs[0x65] = 0;
        gs[0x6A] = 0;
        gs[0x66] = 0;
        gs[0x6B] = 0;
        gs[0x67] = 0;
        gs[0x6C] = 0;
        gs[0x68] = 0;
        gameSettings.step = 3;
    } else {
        gs[0x69] = 0;
        gs[0x65] = 0;
        gs[0x36] = 0;
        gameSettings.step = 1;
    }
}
