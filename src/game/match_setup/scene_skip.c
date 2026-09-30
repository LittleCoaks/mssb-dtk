#define SQRT2_LINKAGE static
#include "game/match_setup/scene_skip.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

extern u8 lbl_80366158[0x30];
extern u8 lbl_3_data_60E4[];
extern void fn_800A97EC(int arg0, int arg1, int arg2);

// .text:0x0006CC30 size:0x158 mapped:0x806ABCC4
BOOL isSkipButtonPressedForPlayer(int player, int inputKind, int mask) {
    if (g_d_GameSettings.minigamesEnabled) {
        int i;
        for (i = 0; i < 4; i++) {
            if (g_Minigame.minigameControlStruct[0].battingHandedness[i] == 0 &&
                g_Minigame.minigameControlStruct[0].characterIndex[i] == player) {
                goto pressCheck;
            }
        }
        return 0;
    } else {
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && player == 1) {
            return 0;
        }
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_UNKNOWN_3 && player == 0) {
            return 0;
        }
    }
pressCheck:
    if (inputKind == 0) {
        if (g_Controls[player].buttonInput & mask) {
            return 1;
        }
    } else if (inputKind == 1) {
        if (g_Controls[player].newButtonInput & mask) {
            return 1;
        }
    } else {
        if (g_Controls[player]._08 & mask) {
            return 1;
        }
    }
    return 0;
}

// .text:0x0006C938 size:0x2F8 mapped:0x806AB9CC
BOOL checkForButtonPressToSkip(int inputKind, int mask) {
    int i;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_DEMO) {
        return 0;
    }
    if (g_d_GameSettings.minigamesEnabled) {
        for (i = 0; i < 4; i++) {
            if (isSkipButtonPressedForPlayer(i, inputKind, mask)) {
                return i + 1;
            }
        }
    } else {
        for (i = 0; i < 2; i++) {
            if (isSkipButtonPressedForPlayer(g_GameLogic.teams[i], inputKind, mask)) {
                return i + 1;
            }
        }
    }
    return 0;
}

// .text:0x0006C854 size:0xE4 mapped:0x806AB8E8
void setCharacterAnimations(int player, int anim) {
    int i;
    if (lbl_80366158[0x1F] != 0 && g_Stats.replayInd == 0) {
        if (g_d_GameSettings.minigamesEnabled) {
            for (i = 0; i < 4; i++) {
                if (g_Minigame.minigameControlStruct[0].characterIndex[i] == player) {
                    if (g_Minigame.minigameControlStruct[0].battingHandedness[g_Minigame.minigameControlStruct[0].characterIndex[i]] != 0) {
                        return;
                    }
                    break;
                }
            }
        } else {
            player = g_GameLogic.teams[player];
        }
        fn_800A97EC(player, lbl_3_data_60E4[anim * 2], lbl_3_data_60E4[anim * 2 + 1]);
    }
}
