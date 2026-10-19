#include "Unknown/File_0x80050138.h"
#include "Unknown/File_0x8004e5b4.h"
#include "Unknown/File_0x800506e8.h"
#include "game/challenge/star_mission_data.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/rand.h"

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
