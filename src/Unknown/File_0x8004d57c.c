#include "Unknown/File_0x8004d57c.h"
#include "Unknown/File_0x8004e5b4.h"
#include "musyx/musyx.h"

#define CHAR_SELECT_BYTE(off) (((u8 *)&charSelectStruct)[off])
#define CHAR_SELECT_HALF(off) (*(s16 *)&CHAR_SELECT_BYTE(off))

extern u8 challengeCaptainCharIDArray[0xC];
extern u8 variantCharIDs[];
extern u8 lbl_800EFBA4[];

int challengeCaptainSelect_returnsCharID(u16 currentHeldInput, u16 newInput, u16 processedInput) {
    s32 slots[CHAR_SELECT_GRID_SLOTS];
    s32 n;
    s32 i;
    s8 timer;
    s32 rem;

    n = 5;
    if (CHAR_SELECT_BYTE(0x8C) != 0) {
        n = 6;
    }

    CHAR_SELECT_BYTE(0x78) = 3;
    for (i = 0; i < CHAR_SELECT_GRID_SLOTS; i++) {
        slots[i] = -1;
    }

    timer = CHAR_SELECT_BYTE(0x7F);
    if (timer >= 0) {
        timer--;
        CHAR_SELECT_BYTE(0x7F) = timer;
        if (timer & 1) {
            rem = rand() % n;
            for (i = 0; i < 12; i++) {
                if (slots[i] < 0) {
                    if (rem == 0) {
                        charSelectStruct.cursorPos[0] = i;
                        break;
                    }
                    rem--;
                }
            }
        }
    } else if ((newInput & 0x20) && timer == -1) {
        CHAR_SELECT_BYTE(0x7F) = 0x1E;
    } else if (processedInput & 2) {
        do {
            if (charSelectStruct.cursorPos[0] == n - 1) {
                charSelectStruct.cursorPos[0] = 0;
            } else {
                charSelectStruct.cursorPos[0]++;
            }
        } while (slots[charSelectStruct.cursorPos[0]] >= 0);
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (processedInput & 1) {
        do {
            if (charSelectStruct.cursorPos[0] == 0) {
                charSelectStruct.cursorPos[0] = n - 1;
            } else {
                charSelectStruct.cursorPos[0]--;
            }
        } while (slots[charSelectStruct.cursorPos[0]] >= 0);
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }

    CHAR_SELECT_HALF(0x20) = challengeCaptainCharIDArray[CHAR_SELECT_BYTE(0x8C) * 6 + charSelectStruct.cursorPos[0]];

    if (newInput & 0x40) {
        for (i = 0; i < 9; i++) {
            if (CHAR_SELECT_HALF(0x20) == variantCharIDs[i * 5]) {
                CHAR_SELECT_BYTE(0x83 + i)++;
                if (CHAR_SELECT_BYTE(0x83 + i) >= 5) {
                    CHAR_SELECT_BYTE(0x83 + i) = 0;
                } else if (variantCharIDs[i * 5 + CHAR_SELECT_BYTE(0x83 + i)] == 0xFF) {
                    CHAR_SELECT_BYTE(0x83 + i) = 0;
                }
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    }

    for (i = 0; i < 9; i++) {
        if (CHAR_SELECT_HALF(0x20) == variantCharIDs[i * 5]) {
            CHAR_SELECT_HALF(0x20) = variantCharIDs[i * 5 + CHAR_SELECT_BYTE(0x83 + i)];
        }
    }

    return CHAR_SELECT_HALF(0x20);
}
