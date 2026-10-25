#include "Unknown/File_0x80020048.h"
#include "Dolphin/rand.h"
#include "static/UnknownHomes_Static.h"

extern u8 lbl_800E86BC[];
extern u8 lbl_8037169C[];

int calledWhenStartingMatch(void) {
    s16 candidates[10][2];
    int count;
    int total;
    int i;
    int r;

    if (g_d_GameSettings._00 == 0) {
        g_d_GameSettings._00 |= 1;
        return 0;
    }

    for (i = 0; i < 10; i++) {
        candidates[i][0] = 0;
        candidates[i][1] = -1;
    }

    count = 0;
    total = 0;
    for (i = 0; i < 0x11; i++) {
        u8 *entry = &lbl_800E86BC[i * 3];
        s8 key = entry[0];

        if ((key < 0 || g_d_GameSettings.StadiumID == key) && lbl_8037169C[0x1B] != i) {
            if (g_d_GameSettings._00 & (1 << i)) {
                candidates[count][0] = (s8)entry[2];
            } else {
                candidates[count][0] = (s8)entry[1];
            }
            total += candidates[count][0];
            count++;
            candidates[count - 1][1] = i;
        }
    }

    r = rand() % total;
    for (i = 0; i < count; i++) {
        r -= candidates[i][0];
        if (r < 0) {
            g_d_GameSettings._00 |= 1 << candidates[i][1];
            return candidates[i][1];
        }
    }
    return 0;
}
