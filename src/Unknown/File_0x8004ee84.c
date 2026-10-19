#include "Unknown/File_0x8004ee84.h"
#include "Unknown/File_0x8004e5b4.h"
#include "static/UnknownHomes_Static.h"

BOOL relatedToTransitions(s32 arg) {
    u8 *state = (u8 *)&charSelectStruct;

    if (state[0x7D] == 0) {
        if (arg == 2) {
            state[0x7D] = 4;
            state[0x8F] = 1;
        } else if (arg != 0) {
            state[0x7D] = 3;
        } else {
            state[0x7D] = 1;
        }
    }

    if (state[0x7D] == 2) {
        state[0x7D] = 0;
        return TRUE;
    }
    return FALSE;
}

void fn_8004EEF4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *state = (u8 *)&charSelectStruct;
    s16 *cursorCharID = (s16 *)charSelectStruct.unk20;
    s32 i;

    if (arg4) {
        for (i = 0; i < 4; i++) {
            state[0x78 + i] = 0;
            charSelectStruct.cursorPos[i] = -1;
            state[0x7F + i] = -1;
        }
    } else {
        for (i = 0; i < 4; i++) {
            state[0x78 + i] = 0;
            charSelectStruct.cursorPos[i] = -1;
            state[0x7F + i] = -2;
        }
    }

    for (i = 0; i < 9; i++) {
        state[0x83 + i] = 0;
    }

    if (arg0) {
        charSelectStruct.cursorPos[0] = 0;
    }
    if (arg1) {
        charSelectStruct.cursorPos[1] = 1;
    }
    if (arg2) {
        charSelectStruct.cursorPos[2] = 1;
    }
    if (arg3) {
        charSelectStruct.cursorPos[3] = 1;
    }

    for (i = 0; i < 4; i++) {
        if (charSelectStruct.cursorPos[i] >= 0) {
            cursorCharID[i] = mapCaptainCursorPositionToCharID[charSelectStruct.cursorPos[i]];
        }
    }

    for (i = 0; i < CHAR_SELECT_GRID_SLOTS; i++) {
        charSelectStruct.slotTeam[i] = -1;
    }
}
