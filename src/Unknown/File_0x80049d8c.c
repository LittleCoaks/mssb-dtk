#include "Unknown/File_0x80049d8c.h"
#include "Unknown/File_0x8004a2bc.h"
#include "Unknown/File_0x800625a4.h"
#include "Unknown/orderchange.h"

void gameSettingsLeftRightPressed(int direction, u8 idx) {
    u8 *gs = (u8 *)&gameSettings;
    s8 value;
    s32 limit;
    u8 *slot;
    u8 *q;
    u8 *table;
    u8 *copy;
    BOOL wantSet;
    BOOL dec;

    gs[idx + 0x69] = gs[idx + 0x65];
    value = (s8)gs[idx + 0x65];
    if (value == 0 && gs[0x36] == 0) {
        return;
    }
    gs[idx + 0x37] = direction;

    if (gs[0x36] != 0) {
        q = gs + (idx << 2);
        table = q + 0x45;
        copy = q + value + 0x55;
        *copy = table[value];
        if (value >= 0 && value < 4) {
            wantSet = ((value == 3) == (direction == 0));
            if (wantSet) {
                if (table[value] == 0) {
                    table[value] = 1;
                }
            } else {
                if (table[value] != 0) {
                    table[value] = 0;
                }
            }
        }
        if ((s8)*copy != (s8)table[value]) {
            updateCharacterSelectProcessCode(idx, 0x30);
            sndFXRelated(0x2);
        }
        return;
    }

    if (value == 3) {
        limit = 5;
    } else if (value == 1 || value == 2 || value == 4) {
        limit = 2;
    } else {
        limit = 0;
    }

    dec = (direction == 0) != (value == 2 || value == 4);
    slot = gs + value;
    slot[0x40] = slot[0x3B];
    if (dec) {
        slot[0x3B]--;
        if ((s8)slot[0x3B] < 0) {
            slot[0x3B] = limit - 1;
        }
    } else {
        slot[0x3B]++;
        if ((s8)slot[0x3B] == limit) {
            slot[0x3B] = 0;
        }
    }

    if ((s8)slot[0x40] != (s8)slot[0x3B]) {
        updateCharacterSelectProcessCode(idx, 0x30);
        sndFXRelated(0x2);
    }
}
