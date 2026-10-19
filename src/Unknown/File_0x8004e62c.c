#include "Unknown/File_0x8004e62c.h"
#include "Unknown/File_0x8004e5b4.h"
#include "musyx/musyx.h"

extern u8 lbl_800EFBA4[];
extern u8 mapCaptainCursorPositionToCharID[0x350];
extern u8 variantCharIDs[0x170];

int captainSelect_processCursorMovement_getCharID(int captainIdx, u16 currentHeldInput, u16 newInput, u16 processedInput) {
    s32 slotClaim[12];
    s32 freeSlots;
    s32 i;
    s32 k;
    s32 cur;
    s32 base;
    s32 idx;
    s32 other;
    s32 rnd;
    s32 n;
    s8 *timer;
    s16 *cursorPos;
    s16 *selected;
    u8 *bytes;

    bytes = (u8 *)&charSelectStruct;
    cursorPos = charSelectStruct.cursorPos;
    selected = (s16 *)charSelectStruct.unk20;

    bytes[0x78 + captainIdx] = 3;

    freeSlots = 12;
    for (i = 0; i < 12; i++) {
        slotClaim[i] = -1;
        if (charSelectStruct.slotTeam[i] >= 0) {
            slotClaim[i] = 0;
            freeSlots--;
        } else {
            for (k = 0; k < 4; k++) {
                if (k != captainIdx && cursorPos[k] == i && bytes[0x78 + k] != 0) {
                    slotClaim[i] = k + 1;
                    freeSlots--;
                    break;
                }
            }
        }
    }

    timer = (s8 *)&bytes[0x7F + captainIdx];
    if (*timer >= 0) {
        (*timer)--;
        if (*timer & 1) {
            rnd = rand() % freeSlots;
            for (i = 0; i < 12; i++) {
                if (slotClaim[i] < 0) {
                    if (rnd == 0) {
                        cursorPos[captainIdx] = i;
                        break;
                    }
                    rnd--;
                }
            }
        }
    } else if ((newInput & 0x20) && *timer == -1) {
        *timer = 0x1E;
    } else if (processedInput & 2) {
        cur = cursorPos[captainIdx];
        base = (cur / 6) * 6;
        idx = cur % 6 + 1;
        if (idx >= 6) {
            idx = 0;
        }
        for (n = 0; n < 5 && slotClaim[base + idx] >= 0; n++) {
            idx++;
            if (idx >= 6) {
                idx = 0;
            }
        }
        cursorPos[captainIdx] = base + idx;
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
    } else if (processedInput & 1) {
        cur = cursorPos[captainIdx];
        base = (cur / 6) * 6;
        idx = cur % 6 - 1;
        if (idx < 0) {
            idx = 5;
        }
        for (n = 0; n < 5 && slotClaim[base + idx] >= 0; n++) {
            idx--;
            if (idx < 0) {
                idx = 5;
            }
        }
        cursorPos[captainIdx] = base + idx;
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
    } else if (processedInput & 4) {
        cur = cursorPos[captainIdx];
        other = ((cur / 6 + 1) % 2) * 6;
        for (k = 0; k < 12; k++) {
            if (slotClaim[other + mapCaptainCursorPositionToCharID[0xC + (cur % 6) * 6 + k]] < 0) {
                break;
            }
        }
        if (k < 12) {
            cursorPos[captainIdx] = other + mapCaptainCursorPositionToCharID[0xC + (cur % 6) * 6 + k];
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
        }
    } else if (processedInput & 8) {
        cur = cursorPos[captainIdx];
        other = (cur / 6 - 1) * 6;
        if (other < 0) {
            other = 6;
        }
        for (k = 0; k < 12; k++) {
            if (slotClaim[other + mapCaptainCursorPositionToCharID[0xC + (cur % 6) * 6 + k]] < 0) {
                break;
            }
        }
        if (k < 12) {
            cursorPos[captainIdx] = other + mapCaptainCursorPositionToCharID[0xC + (cur % 6) * 6 + k];
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
        }
    }

    selected[captainIdx] = mapCaptainCursorPositionToCharID[cursorPos[captainIdx]];

    if (newInput & 0x40) {
        for (i = 0; i < 9; i++) {
            if (selected[captainIdx] == variantCharIDs[i * 5]) {
                bytes[0x83 + i] += 1;
                if (bytes[0x83 + i] < 5) {
                    if (variantCharIDs[i * 5 + bytes[0x83 + i]] == 0xFF) {
                        bytes[0x83 + i] = 0;
                    }
                } else {
                    bytes[0x83 + i] = 0;
                }
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
            }
        }
    }

    for (i = 0; i < 9; i++) {
        if (selected[captainIdx] == variantCharIDs[i * 5]) {
            selected[captainIdx] = variantCharIDs[i * 5 + bytes[0x83 + i]];
        }
    }

    return selected[captainIdx];
}
