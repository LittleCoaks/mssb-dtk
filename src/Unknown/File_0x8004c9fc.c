#include "Unknown/File_0x8004ca6c.h"
#include "Unknown/File_0x8004cc18.h"
#include "musyx/musyx.h"
#include "game/UnknownHomes_Game.h"
#include "Unknown/File_0x8004d57c.h"
#include "Unknown/File_0x8004e5b4.h"
#include "Unknown/File_0x8004d93c.h"
#include "Unknown/File_0x8004e504.h"
#include "game/challenge/star_mission_data.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x8004e62c.h"
#include "Unknown/File_0x8004ee84.h"
#include "Unknown/File_0x80050138.h"
#include "Unknown/File_0x800506e8.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/rand.h"
#include "Unknown/File_0x80050760.h"
#include "Unknown/File_0x80050fe8.h"
#include "Unknown/sub.h"

// 0x8004C9FC-0x80052188: the character-select (CSS) translation unit, one unit by
// its .data/.sdata order (docs/splits.md, 2026-11-21): the former
// File_0x8004ca6c ... File_0x80050fe8 sources in address order, plus unowned
// functions that have no C yet.

extern Unk803C5F74 lbl_803C5F74;
extern u8 lbl_800EFBA4[0x10];
extern s32 lbl_803CB874;
extern s32 lbl_803CB878;

int exitMenu(u16 input) {
    if (lbl_803C5F74.state == 4) {
        if (lbl_803C5F74.unk02 == 0) {
            return 3;
        }
        return 4;
    }
    if (lbl_803C5F74.state == 2) {
        int quiet;

        if (input != 0) {
            lbl_803CB874 = lbl_803CB878;
        }
        if (lbl_803CB874 > 0) {
            lbl_803CB874--;
        }
        quiet = lbl_803CB874 == 0;
        if (quiet) {
            input |= INPUT_BUTTON_A;
        }
        if (input & INPUT_BUTTON_A) {
            if (!quiet) {
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, SND_STUDIO_DEFAULT);
            }
            if (lbl_803C5F74.unk02 == 0) {
                return 1;
            }
            return 2;
        }
        if (input & INPUT_BUTTON_B) {
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, SND_STUDIO_DEFAULT);
            if (lbl_803C5F74.unk02 == 0) {
                lbl_803C5F74.unk02 = 1;
            } else {
                return 2;
            }
        } else if ((input & INPUT_BUTTON_LEFT) && lbl_803C5F74.unk02 == 1) {
            lbl_803C5F74.unk02 = 0;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
        } else if (input & INPUT_BUTTON_RIGHT) {
            if (lbl_803C5F74.unk02 == 0) {
                lbl_803C5F74.unk02 = 1;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
            }
        }
    }
    return 0;
}

void fn_8004CC18(void) {
    lbl_803C5F74.state = 4;
}

void set803c5f77(void) {
    if (lbl_803C5F74.state != 4) {
        lbl_803C5F74.state = 3;
    }
}

void fn_8004CC4C(u8 arg0, u8 arg1, u8 arg2, int arg3, u16 arg4) {
    int i;

    if (lbl_803C5F74.unk00 != 0) {
        return;
    }
    lbl_803C5F74.unk01 = arg0;
    lbl_803C5F74.unk02 = arg2;
    lbl_803C5F74.state = 0;
    lbl_803C5F74.unk04 = arg1;
    lbl_803C5F74.unk1E = 0;
    for (i = 0; i < 4; i++) {
        lbl_803C5F74.unk06[i] = 0;
        lbl_803C5F74.unk0E[i] = -1;
    }
    lbl_803C5F74.unk1B = 0;
    lbl_803C5F74.unk1C = 0;
    if (arg3 >= 0) {
        lbl_803C5F74.unk1A = arg3;
        lbl_803C5F74.unk18 = arg4;
    } else {
        lbl_803C5F74.unk1A = -1;
    }
}

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

#define CHAR_SELECT_BYTE(off) (((u8 *)&charSelectStruct)[off])


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

void storeCursorLocOrCharIDs(BOOL isCharID, int port0, int port1, int port2, int port3) {
    int values[4];
    int i;
    int charID;
    int slot;

    values[0] = port0;
    values[1] = port1;
    values[2] = port2;
    values[3] = port3;
    for (i = 0; i < 4; i++) {
        if (charSelectStruct.cursorPos[i] >= 0 && values[i] >= 0) {
            if (!isCharID) {
                charSelectStruct.cursorPos[i] = values[i];
            } else {
                charID = characterStaticIndexes[values[i]].trackerIdx;
                for (slot = 0; slot < CHAR_SELECT_GRID_SLOTS; slot++) {
                    if (charID == mapCaptainCursorPositionToCharID[slot]) {
                        charSelectStruct.cursorPos[i] = slot;
                        break;
                    }
                }
            }
        }
    }
}

void add_or_RemoveCharToATeam(int team, int charID, BOOL add) {
    int i;
    int id = characterStaticIndexes[charID].trackerIdx;

    for (i = 0; i < CHAR_SELECT_GRID_SLOTS; i++) {
        if (mapCaptainCursorPositionToCharID[i] == id) {
            if (add) {
                charSelectStruct.slotTeam[i] = team;
            } else {
                charSelectStruct.slotTeam[i] = -1;
            }
            return;
        }
    }
}

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

void cssLoadingRelated_1(BOOL valuesAreCharIDs, int cursor0, int cursor1, int cursor2, int cursor3, BOOL excludeAllCursors) {
    int requests[4];
    int avail[CHAR_SELECT_GRID_SLOTS];
    int count;
    int i;
    int j;
    int p;
    int r;

    requests[0] = cursor0;
    requests[1] = cursor1;
    requests[2] = cursor2;
    requests[3] = cursor3;

    for (i = 0; i < 4; i++) {
        if (charSelectStruct.cursorPos[i] >= 0 && requests[i] >= 0) {
            if (valuesAreCharIDs == FALSE) {
                charSelectStruct.cursorPos[i] = requests[i];
            } else {
                u8 trackerIdx = characterStaticIndexes[requests[i]].trackerIdx;
                for (j = 0; j < CHAR_SELECT_GRID_SLOTS; j++) {
                    if (characterIconsOnCSS[j] == trackerIdx) {
                        charSelectStruct.cursorPos[i] = j;
                        break;
                    }
                }
            }
        }
    }

    if (cursor0 == -3 || cursor1 == -3 || cursor2 == -3 || cursor3 == -3) {
        count = CHAR_SELECT_GRID_SLOTS;
        for (j = 0; j < CHAR_SELECT_GRID_SLOTS; j++) {
            avail[j] = 1;
            if (charSelectStruct.slotTeam[j] >= 0) {
                avail[j] = 0;
                count--;
            } else if (characterIconsOnCSS[j] == 0xFF) {
                avail[j] = 0;
                count--;
            } else if (characterStaticIndexes[characterIconsOnCSS[j]]._4 == 0) {
                avail[j] = 0;
                count--;
            } else {
                for (p = 0; p < 4; p++) {
                    if (charSelectStruct.cursorPos[p] == j &&
                        (charSelectStruct.unk4C[0x2C + p] != 0 || excludeAllCursors)) {
                        avail[j] = 0;
                        count--;
                        break;
                    }
                }
            }
        }

        for (i = 0; i < 4; i++) {
            if (requests[i] == -3) {
                r = rand() % count;
                for (j = 0; j < CHAR_SELECT_GRID_SLOTS; j++) {
                    if (avail[j] != 0) {
                        if (r == 0) {
                            charSelectStruct.cursorPos[i] = j;
                            charSelectStruct.unk4C[0x2C + i] = 3;
                            avail[j] = 0;
                            count--;
                            break;
                        }
                        r--;
                    }
                }
            }
        }
    }

    if (cursor0 <= -2 || cursor1 <= -2 || cursor2 <= -2 || cursor3 <= -2) {
        count = CHAR_SELECT_GRID_SLOTS;
        for (j = 0; j < CHAR_SELECT_GRID_SLOTS; j++) {
            avail[j] = -1;
            if (charSelectStruct.unk4C[j] != 0) {
                avail[j] = 0;
                count--;
            } else if (charSelectStruct.slotTeam[j] >= 0) {
                avail[j] = 0;
                count--;
            } else if (characterIconsOnCSS[j] == 0xFF) {
                avail[j] = 5;
                count--;
            } else if (charSelectStruct.cursorPos[0] == j && charSelectStruct.unk4C[0x2C] != 0) {
                avail[j] = 1;
                count--;
            } else if (charSelectStruct.cursorPos[1] == j && charSelectStruct.unk4C[0x2D] != 0) {
                avail[j] = 2;
                count--;
            } else if (charSelectStruct.cursorPos[2] == j && charSelectStruct.unk4C[0x2E] != 0) {
                avail[j] = 3;
                count--;
            } else if (charSelectStruct.cursorPos[3] == j && charSelectStruct.unk4C[0x2F] != 0) {
                avail[j] = 4;
                count--;
            }
        }

        for (i = 0; i < 4; i++) {
            if (requests[i] == -2) {
                r = rand() % count;
                for (j = 0; j < CHAR_SELECT_GRID_SLOTS; j++) {
                    if (avail[j] < 0) {
                        if (r == 0) {
                            charSelectStruct.cursorPos[i] = j;
                            count--;
                            break;
                        }
                        r--;
                    }
                }
            }
        }
    }
}

void addOrRemoveCharacterToTeam(int team, int charID, BOOL add) {
    int i;
    int id = characterStaticIndexes[charID].trackerIdx;

    for (i = 0; i < CHAR_SELECT_GRID_SLOTS; i++) {
        if (characterIconsOnCSS[i] == id) {
            if (add) {
                charSelectStruct.slotTeam[i] = team;
            } else {
                charSelectStruct.slotTeam[i] = -1;
            }
            return;
        }
    }
}

extern u8 lbl_800FCA60[];

#define CSS_U8(off) (((u8 *)&charSelectStruct)[off])
#define CSS_S8(off) (((s8 *)&charSelectStruct)[off])
#define CSS_S16(off) (*(s16 *)&CSS_U8(off))

#define CSS_CURSOR_SFX() sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0)

/* 12 x 12 neighbour table, indexed [column][k] */
#define CSS_NAV_TABLE (lbl_800FCA60 + 0x1458)
/* 9 rows of 5 bytes: key character, then per-step sequence */
#define CSS_CHAR_TABLE (lbl_800FCA60 + 0x1EDC)

s32 charGrid_moveCursor(s32 port, s32 unused, s32 flags2, s32 flags3, s32 mode) {
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

/* File_0x80050fe8 viewed charSelectStruct as s8[0x94]. */
#define charSelectStruct (*(s8(*)[0x94])&charSelectStruct)
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

#undef charSelectStruct
