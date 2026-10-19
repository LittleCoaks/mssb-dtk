#include "Unknown/File_0x80050760.h"
#include "Unknown/File_0x8004e5b4.h"
#include "Unknown/File_0x800506e8.h"
#include "musyx/musyx.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/rand.h"

extern u8 lbl_800FCA60[];
extern u8 lbl_800EFBA4[0x10];

#define CSS_U8(off) (((u8 *)&charSelectStruct)[off])
#define CSS_S8(off) (((s8 *)&charSelectStruct)[off])
#define CSS_S16(off) (*(s16 *)&CSS_U8(off))

#define CSS_CURSOR_SFX() sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0)

/* 12 x 12 neighbour table, indexed [column][k] */
#define CSS_NAV_TABLE (lbl_800FCA60 + 0x1458)
/* 9 rows of 5 bytes: key character, then per-step sequence */
#define CSS_CHAR_TABLE (lbl_800FCA60 + 0x1EDC)

s32 cssCursorOnBottomControl_maybe(s32 port, s32 unused, s32 flags2, s32 flags3, s32 mode) {
    s32 slotState[CHAR_SELECT_GRID_SLOTS];
    s32 unclaimed;
    s32 i;
    s32 j;
    s32 q;
    s32 cur;
    s32 col;
    s32 base;
    s32 k;
    s32 pick;
    u8 *navRow;
    u8 *charRow;

    CSS_U8(0x78 + port) = 3;

    unclaimed = CHAR_SELECT_GRID_SLOTS;
    for (i = 0; i < CHAR_SELECT_GRID_SLOTS; i++) {
        slotState[i] = -1;
        if (CSS_S8(0x7F + port) >= 0 && (CSS_U8(0x4C + i) != 0 || CSS_S8(0x28 + i) >= 0)) {
            slotState[i] = 0;
            unclaimed--;
        } else if (characterIconsOnCSS[i] == 0xFF) {
            slotState[i] = 5;
            unclaimed--;
        } else if (mode != 1) {
            for (q = 0; q < 4; q++) {
                if (q != port && charSelectStruct.cursorPos[q] == i && CSS_U8(0x78 + q) != 0) {
                    slotState[i] = q + 1;
                    unclaimed--;
                    break;
                }
            }
        }
    }

    if (CSS_S8(0x7F + port) >= 0) {
        CSS_U8(0x7F + port) -= 1;
        if (CSS_U8(0x7F + port) & 1) {
            pick = rand() % unclaimed;
            for (i = 0; i < CHAR_SELECT_GRID_SLOTS; i++) {
                if (slotState[i] < 0) {
                    if (pick == 0) {
                        charSelectStruct.cursorPos[port] = i;
                        break;
                    }
                    pick--;
                }
            }
        }
    } else if ((flags2 & 0x20) && CSS_S8(0x7F + port) == -1) {
        CSS_U8(0x7F + port) = 30;
    } else if (flags3 & 2) {
        cur = charSelectStruct.cursorPos[port];
        base = (cur / 12) * 12;
        col = cur % 12;
        for (k = 0; k < 12; k++) {
            col++;
            if (col >= 12) {
                col = 0;
            }
            if (slotState[base + col] < 0) {
                CSS_CURSOR_SFX();
                break;
            }
        }
        charSelectStruct.cursorPos[port] = base + col;
    } else if (flags3 & 1) {
        cur = charSelectStruct.cursorPos[port];
        base = (cur / 12) * 12;
        col = cur % 12;
        for (k = 0; k < 12; k++) {
            col--;
            if (col < 0) {
                col = 11;
            }
            if (slotState[base + col] < 0) {
                CSS_CURSOR_SFX();
                break;
            }
        }
        charSelectStruct.cursorPos[port] = base + col;
    } else if (flags3 & 4) {
        cur = charSelectStruct.cursorPos[port];
        base = cur / 12;
        col = cur % 12;
        {
            s32 rowNext = ((base + 1) % 3) * 12;
            navRow = CSS_NAV_TABLE + 12 * col;
            for (k = 0; k < 12; k++) {
                s32 idx = rowNext + navRow[k];
                if (slotState[idx] < 0) {
                    charSelectStruct.cursorPos[port] = idx;
                    CSS_CURSOR_SFX();
                    break;
                }
            }
        }
    } else if (flags3 & 8) {
        cur = charSelectStruct.cursorPos[port];
        base = cur / 12;
        col = cur % 12;
        {
            s32 rowPrev = base - 1;
            if (rowPrev < 0) {
                rowPrev = 2;
            }
            navRow = CSS_NAV_TABLE + 12 * col;
            for (k = 0; k < 12; k++) {
                s32 idx = rowPrev * 12 + navRow[k];
                if (slotState[idx] < 0) {
                    charSelectStruct.cursorPos[port] = idx;
                    CSS_CURSOR_SFX();
                    break;
                }
            }
        }
    }

    cur = charSelectStruct.cursorPos[port];
    if (CSS_S8(0x28 + cur) >= 0) {
        return -1;
    }
    if (CSS_U8(0x4C + cur) != 0) {
        return -1;
    }

    CSS_S16(0x20 + port * 2) = characterIconsOnCSS[cur];

    if (flags2 & 0x40) {
        for (j = 0; j < 9; j++) {
            charRow = CSS_CHAR_TABLE + 5 * j;
            if (CSS_S16(0x20 + port * 2) == charRow[0]) {
                CSS_U8(0x83 + j) += 1;
                if (CSS_U8(0x83 + j) >= 5) {
                    CSS_U8(0x83 + j) = 0;
                } else if (charRow[CSS_U8(0x83 + j)] == 0xFF) {
                    CSS_U8(0x83 + j) = 0;
                }
                CSS_CURSOR_SFX();
            }
        }
    }

    for (j = 0; j < 9; j++) {
        charRow = CSS_CHAR_TABLE + 5 * j;
        if (CSS_S16(0x20 + port * 2) == charRow[0]) {
            CSS_S16(0x20 + port * 2) = charRow[CSS_U8(0x83 + j)];
        }
    }

    return CSS_S16(0x20 + port * 2);
}
