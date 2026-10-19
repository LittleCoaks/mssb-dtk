#include "Unknown/File_0x8004d93c.h"
#include "Unknown/File_0x8004e5b4.h"

#define CHAR_SELECT_BYTE(off) (((u8 *)&charSelectStruct)[off])

extern u8 challengeCaptainCharIDArray[0xC];

BOOL challengeTransitionRelated(BOOL arg0) {
    if (CHAR_SELECT_BYTE(0x7E) == 0) {
        if (arg0 == 0) {
            CHAR_SELECT_BYTE(0x7E) = 1;
        } else {
            CHAR_SELECT_BYTE(0x7E) = 3;
        }
    }

    if (CHAR_SELECT_BYTE(0x7E) == 2) {
        CHAR_SELECT_BYTE(0x7E) = 0;
        return TRUE;
    }
    return FALSE;
}

void fn_8004D990(u8 arg0, BOOL arg1, u8 arg2) {
    s32 i;

    if (arg1 == 0) {
        for (i = 0; i < 4; i++) {
            CHAR_SELECT_BYTE(0x78 + i) = 0;
            charSelectStruct.cursorPos[i] = -1;
            CHAR_SELECT_BYTE(0x7F + i) = -2;
        }
    } else {
        for (i = 0; i < 4; i++) {
            CHAR_SELECT_BYTE(0x78 + i) = 0;
            charSelectStruct.cursorPos[i] = -1;
            CHAR_SELECT_BYTE(0x7F + i) = -1;
        }
    }

    for (i = 0; i < 9; i++) {
        CHAR_SELECT_BYTE(0x83 + i) = 0;
    }

    charSelectStruct.cursorPos[0] = 0;
    CHAR_SELECT_BYTE(0x8D) = arg0;
    CHAR_SELECT_BYTE(0x8C) = arg2;

    for (i = 0; i < 4; i++) {
        if (charSelectStruct.cursorPos[i] >= 0) {
            ((s16 *)charSelectStruct.unk20)[i] =
                challengeCaptainCharIDArray[CHAR_SELECT_BYTE(0x8C) * 6 + charSelectStruct.cursorPos[i]];
        }
    }

    for (i = 0; i < CHAR_SELECT_GRID_SLOTS; i++) {
        charSelectStruct.slotTeam[i] = -1;
    }
}
