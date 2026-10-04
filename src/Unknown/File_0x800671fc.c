#include "Unknown/File_0x800671fc.h"
#include "Unknown/orderchange.h"
#include "static/UnknownHomes_Static.h"

extern u8 superstarUnlocked[0x130];

void selectRandomStadium(void) {
    u8 stadium;

    if (superstarUnlocked[0xF5]) {
        stadium = randRange_FUN_80042bf0(STADIUM_ID_MARIO_STADIUM, STADIUM_ID_DK_JUNGLE);
    } else {
        do {
            stadium = randRange_FUN_80042bf0(STADIUM_ID_MARIO_STADIUM, STADIUM_ID_DK_JUNGLE);
        } while (stadium == STADIUM_ID_BOWSERS_CASTLE);
    }
    g_d_GameSettings.StadiumID = stadium;
}
