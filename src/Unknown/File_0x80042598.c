#include "Unknown/File_0x80042598.h"
#include "Dolphin/os.h"
#include "game/UnknownHomes_Game.h"

extern s8 lineUpInfoStruct[TEAMS_PER_GAME][PLAYERS_PER_TEAM][4];

int lineupOrderChangeRelated(u8 team, int rosterID) {
    int i;

    for (i = 0; i < PLAYERS_PER_TEAM; i++) {
        if (rosterID == lineUpInfoStruct[team][i][2]) {
            return i + 1;
        }
    }
    OSPanic("orderchange.c", 0xD69, "//OZ 戻り値がありません\b");
    return 0;
}
