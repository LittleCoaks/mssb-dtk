#include "Unknown/File_0x80050fe8.h"
#include "Unknown/sub.h"

extern s8 charSelectStruct[0x94];
extern u8 characterIconsOnCSS[0x744];

void css_initValues(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5) {
    s32 i;

    charSelectStruct[0x91] = a5;

    for (i = 0; i < 0x24; i++) {
        charSelectStruct[0x4C + i] = 0;
    }

    if (a5 != 0) {
        for (i = 0; i < 0x24; i++) {
            if (characterIconsOnCSS[i] != 0xFF && !isCharacterUnlocked(characterIconsOnCSS[i])) {
                charSelectStruct[0x4C + i] = 1;
            }
        }
    }

    if (a4 == 0) {
        for (i = 0; i < 4; i++) {
            charSelectStruct[0x78 + i] = 0;
            ((s16 *)&charSelectStruct[0x18])[i] = -1;
            charSelectStruct[0x74 + i] = 0;
            charSelectStruct[0x7F + i] = -2;
        }
    } else {
        for (i = 0; i < 4; i++) {
            charSelectStruct[0x78 + i] = 0;
            ((s16 *)&charSelectStruct[0x18])[i] = -1;
            charSelectStruct[0x74 + i] = 0;
            charSelectStruct[0x7F + i] = -1;
        }
    }

    for (i = 0; i < 9; i++) {
        charSelectStruct[0x83 + i] = 0;
    }

    if (a0 != 0) {
        ((s16 *)&charSelectStruct[0x18])[0] = 0;
        if (a0 == 2) {
            charSelectStruct[0x74] = 1;
        }
    }
    if (a1 != 0) {
        ((s16 *)&charSelectStruct[0x18])[1] = 1;
        if (a1 == 2) {
            charSelectStruct[0x75] = 1;
        }
    }
    if (a2 != 0) {
        ((s16 *)&charSelectStruct[0x18])[2] = 3;
        if (a2 == 2) {
            charSelectStruct[0x76] = 1;
        }
    }
    if (a3 != 0) {
        ((s16 *)&charSelectStruct[0x18])[3] = 4;
        if (a3 == 2) {
            charSelectStruct[0x77] = 1;
        }
    }

    for (i = 0; i < 4; i++) {
        s16 cursor = ((s16 *)&charSelectStruct[0x18])[i];
        if (cursor >= 0) {
            ((s16 *)&charSelectStruct[0x20])[i] = characterIconsOnCSS[cursor];
        }
    }

    for (i = 0; i < 0x24; i++) {
        charSelectStruct[0x28 + i] = -1;
    }
}
