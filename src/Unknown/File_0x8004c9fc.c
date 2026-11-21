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
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x80034cec.h"
#include "Unknown/File_0x800363d8.h"
#include "text/text.h"
#include "game/challenge/challenge_state.h"

// 0x8004C9FC-0x80052188: the character-select (CSS) translation unit, one unit by
// its .data/.sdata order (docs/splits.md, 2026-11-21): the former
// File_0x8004ca6c ... File_0x80050fe8 sources in address order, plus unowned
// functions that have no C yet.

#define CHAR_SELECT_BYTE(off) (((u8 *)&charSelectStruct)[off])

extern Unk803C5F74 lbl_803C5F74;
extern u8 lbl_800EFBA4[0x10];
extern u8 lbl_800FCA60[];
extern u8 lbl_800FE924[];
extern u8 lbl_800FE5C8[];
extern u8 superstarUnlocked[];
extern u8 lbl_800FDE60[CHAR_SELECT_GRID_SLOTS];
extern u8 lbl_800E854C[12];
extern s32 lbl_803CB874;
extern s32 lbl_803CB878;
extern u16 lbl_800FEAAC[][3];
extern u16 lbl_803CB870[2];
s32 fn_80036214(void *scene, s32 a, s32 b, s32 c);
extern u8 lbl_80366158[0x30];
extern u8 challengeCaptainCharIDArray[0xC];
extern u8 variantCharIDs[0x170];
extern u8 mapCaptainCursorPositionToCharID[0x350];
extern u8 characterIconsOnCSS[0x744];

void fn_8004C9FC(void) {
    lbl_803CB874 = lbl_803CB878;
}

void fn_8004CA08(s32 frames) {
    lbl_803CB878 = frames;
    lbl_803CB874 = frames;
}

void fn_8004CA14(s32 bankIndex, s32 stringIndex) {
    text_setPtrToWhereCharsAreStored(lbl_803C5F74.unk16, bankIndex, stringIndex);
}

void fn_8004CA48(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    lbl_803C5F74.unk1C = 1;
    lbl_803C5F74.unk0E[0] = arg0;
    lbl_803C5F74.unk0E[1] = arg1;
    lbl_803C5F74.unk0E[2] = arg2;
    lbl_803C5F74.unk0E[3] = arg3;
}

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
#define CSS_TEXT_SCENE_RECORD(n) ((UIRecord *)graphicsRelatedArray[((MenuScene *)item)->firstHandle + (n)].object)

void fn_8004CCC0(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    int flags;
    s32 frame;

    if (lbl_803C5F74.state == 0) {
        lbl_803C5F74.state = 1;
        if (lbl_803C5F74.unk1A >= 0) {
            s32 channel = text_initializeNewChannel((UnkText988Arg *)item, 8, lbl_800FEAAC[lbl_803C5F74.unk01][2],
                                                    lbl_803C5F74.unk1A, lbl_803C5F74.unk18, 0);
            u16 block = channel;
            screenTextArray.blocks[block].justify = 1;
            lbl_803C5F74.unk16 = channel;
            screenTextArray.blocks[block].verticalAlign = 1;
            if (lbl_803C5F74.unk1B != 0) {
                ((void (*)(s32, s16, s16, s16, s16))text_setInsertedValues)(
                    block, lbl_803C5F74.unk06[0], lbl_803C5F74.unk06[1], lbl_803C5F74.unk06[2], lbl_803C5F74.unk06[3]);
            }
            if (lbl_803C5F74.unk1C != 0) {
                text_setSubstringIndices(lbl_803C5F74.unk16, lbl_803C5F74.unk0E[0], lbl_803C5F74.unk0E[1],
                                         lbl_803C5F74.unk0E[2], lbl_803C5F74.unk0E[3]);
            }
        }
    } else if (lbl_803C5F74.state == 1) {
        flags = 0;
        if (lbl_803C5F74.unk01 == 7 || lbl_803C5F74.unk01 == 8 || lbl_803C5F74.unk01 == 10) {
            frame = CSS_TEXT_SCENE_RECORD(1)->frame >> 16;
            if (frame >= 3) {
                flags |= 1;
            }
        } else {
            frame = CSS_TEXT_SCENE_RECORD(3)->frame >> 16;
            if (lbl_803C5F74.unk02 == 0) {
                if (frame >= 5) {
                    flags |= 1;
                    CSS_TEXT_SCENE_RECORD(3)->playMode = 0;
                }
            } else if (frame <= 10) {
                flags |= 1;
                CSS_TEXT_SCENE_RECORD(3)->playMode = 0;
            }
        }
        if (flags == 1) {
            lbl_803C5F74.state = 2;
        }
    } else if (lbl_803C5F74.state == 2) {
        if (lbl_803C5F74.unk01 != 7 && lbl_803C5F74.unk01 != 8 && lbl_803C5F74.unk01 != 10) {
            frame = CSS_TEXT_SCENE_RECORD(3)->frame >> 16;
            if (lbl_803C5F74.unk02 == 0) {
                if (frame <= 5) {
                    CSS_TEXT_SCENE_RECORD(3)->playMode = 0;
                } else {
                    CSS_TEXT_SCENE_RECORD(3)->playMode = 4;
                }
            } else if (frame >= 10) {
                CSS_TEXT_SCENE_RECORD(3)->playMode = 0;
            } else {
                CSS_TEXT_SCENE_RECORD(3)->playMode = 1;
            }
        }
    } else if (lbl_803C5F74.state == 3) {
        if (lbl_803C5F74.unk04 != 0) {
            CSS_TEXT_SCENE_RECORD(0)->playMode = 4;
        }
        CSS_TEXT_SCENE_RECORD(1)->playMode = 4;
        flags = 0;
        if (lbl_803C5F74.unk01 == 7 || lbl_803C5F74.unk01 == 8 || lbl_803C5F74.unk01 == 10 ||
            lbl_803C5F74.unk01 == 9) {
            frame = CSS_TEXT_SCENE_RECORD(1)->frame >> 16;
            if (frame <= 0) {
                flags |= 1;
            }
        } else {
            frame = CSS_TEXT_SCENE_RECORD(3)->frame >> 16;
            if (lbl_803C5F74.unk02 == 0) {
                CSS_TEXT_SCENE_RECORD(3)->playMode = 4;
                if (frame <= 0) {
                    flags |= 1;
                }
            } else {
                CSS_TEXT_SCENE_RECORD(3)->playMode = 1;
                if (frame >= 15) {
                    flags |= 1;
                }
            }
        }
        if (flags == 1) {
            goto remove;
        }
    } else if (lbl_803C5F74.state == 4) {
        goto remove;
    }

    if (lbl_803C5F74.unk1D != 0) {
        CSS_TEXT_SCENE_RECORD(6)->flags |= UI_FLAG_VISIBLE;
        CSS_TEXT_SCENE_RECORD(6)->playMode = 1;
    } else {
        CSS_TEXT_SCENE_RECORD(6)->flags &= ~UI_FLAG_VISIBLE;
    }
    return;

remove:
    if (lbl_803C5F74.unk1A >= 0) {
        text_freeBlock(lbl_803C5F74.unk16);
        fn_8000F8F4(item);
    }
    lbl_803C5F74.state = 4;
    lbl_803C5F74.unk00 = 0;
    removeGraphicsElementFromScene(item);
    removeCurrentDrawingItem();
    lbl_80366158[0x20] = 1;
}

#define CSS_TEXT_LAYOUT_ELEMENTS elements
#define CSS_TEXT_LAYOUT_ANCHORS  anchors

void fn_8004D0F0(void) {
    u8 *data = lbl_800FCA60;
    DrawingSceneStruct *item = currentDrawingItem;
    u16 (*elements)[3];
    u8 *anchors;

    if (lbl_803C5F74.unk00 != 0) {
        removeCurrentDrawingItem();
        return;
    }

    lbl_803C5F74.unk00 = 1;
    addGraphicsElementToScene(item, (const UIRecordDescriptor *)(data + 0x1F0C));
    if (lbl_803C5F74.unk04 == 0) {
        CSS_TEXT_SCENE_RECORD(0)->flags &= ~UI_FLAG_VISIBLE;
    }

    elements = (u16(*)[3])(data + 0x204C);
    anchors = data + 0x2090;
    CSS_TEXT_SCENE_RECORD(1)->elementIndex = CSS_TEXT_LAYOUT_ELEMENTS[lbl_803C5F74.unk01][0];
    CSS_TEXT_SCENE_RECORD(2)->elementIndex = CSS_TEXT_LAYOUT_ELEMENTS[lbl_803C5F74.unk01][1];
    CSS_TEXT_SCENE_RECORD(8)->frame = CSS_TEXT_LAYOUT_ELEMENTS[lbl_803C5F74.unk01][2] << 16;
    CSS_TEXT_SCENE_RECORD(2)->anchorSub = CSS_TEXT_LAYOUT_ANCHORS[lbl_803C5F74.unk01 * 2];
    CSS_TEXT_SCENE_RECORD(3)->anchorSub = CSS_TEXT_LAYOUT_ANCHORS[lbl_803C5F74.unk01 * 2 + 1];
    CSS_TEXT_SCENE_RECORD(8)->anchorSub = CSS_TEXT_LAYOUT_ANCHORS[lbl_803C5F74.unk01 * 2];

    if (lbl_803C5F74.unk1E == 1) {
        CSS_TEXT_SCENE_RECORD(3)->elementIndex = 0xE3;
    }
    if (lbl_803C5F74.unk02 == 1) {
        CSS_TEXT_SCENE_RECORD(3)->frame = 15 << 16;
        CSS_TEXT_SCENE_RECORD(3)->playMode = 4;
    }
    if (lbl_803C5F74.unk01 == 7 || lbl_803C5F74.unk01 == 10) {
        CSS_TEXT_SCENE_RECORD(3)->flags &= ~UI_FLAG_VISIBLE;
    }

    if (lbl_803C5F74.unk01 != 9) {
        CSS_TEXT_SCENE_RECORD(4)->flags &= ~UI_FLAG_VISIBLE;
        CSS_TEXT_SCENE_RECORD(5)->flags &= ~UI_FLAG_VISIBLE;
    } else {
        load_Icon(item, 4, 1, 0xCD, lbl_803C5F74.unk02);
        CSS_TEXT_SCENE_RECORD(3)->flags &= ~UI_FLAG_VISIBLE;
    }

    if (lbl_803C5F74.unk01 != 10) {
        CSS_TEXT_SCENE_RECORD(6)->flags &= ~UI_FLAG_VISIBLE;
        lbl_803C5F74.unk1D = 0;
    } else {
        lbl_803C5F74.unk1D = 1;
    }

    if (lbl_803C5F74.unk1D != 0) {
        sndFXStartEx(0x1C2, lbl_800EFBA4[11], 0x3F, SND_STUDIO_DEFAULT);
    } else if (lbl_803C5F74.unk01 == 0 || (lbl_803C5F74.unk01 >= 1 && lbl_803C5F74.unk01 <= 5) ||
               lbl_803C5F74.unk01 == 6) {
        sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, SND_STUDIO_DEFAULT);
    }

    ((u16 *)((u8 *)item + 0x18))[0] = 0;
    ((u16 *)((u8 *)item + 0x18))[1] = 0;
    currentDrawingItem->func = fn_8004CCC0;
}

#define CHAR_SELECT_HALF(off) (*(s16 *)&CHAR_SELECT_BYTE(off))

extern u8 lbl_800EFBA4[];

void fn_8004D460(BOOL isCharID, int value) {
    int values[4];
    int i;
    int charID;
    int slot;

    values[0] = value;
    for (i = 0; i < 1; i++) {
        if (charSelectStruct.cursorPos[i] >= 0 && values[i] >= 0) {
            if (!isCharID) {
                charSelectStruct.cursorPos[i] = values[i];
            } else {
                charID = characterStaticIndexes[values[i]].trackerIdx;
                for (slot = 0; slot < CHAR_SELECT_GRID_SLOTS; slot++) {
                    if (charID == challengeCaptainCharIDArray[CHAR_SELECT_BYTE(0x8C) * 6 + slot]) {
                        charSelectStruct.cursorPos[i] = slot;
                        break;
                    }
                }
            }
        }
    }
}

void fn_8004D4F0(int team, int charID, BOOL add) {
    int i;
    int id = characterStaticIndexes[charID].trackerIdx;

    for (i = 0; i < CHAR_SELECT_GRID_SLOTS; i++) {
        if (id == challengeCaptainCharIDArray[CHAR_SELECT_BYTE(0x8C) * 6 + i]) {
            if (add) {
                charSelectStruct.slotTeam[i] = team;
            } else {
                charSelectStruct.slotTeam[i] = -1;
            }
            return;
        }
    }
}

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
        if (arg0 != 0) {
            CHAR_SELECT_BYTE(0x7E) = 3;
        } else {
            CHAR_SELECT_BYTE(0x7E) = 1;
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

#define CSS_CAPTAIN_SCENE_PHASE (*(u16 *)((u8 *)item + 0x1C))
#define CSS_CAPTAIN_RECORD(n)   CSS_TEXT_SCENE_RECORD(n)

void fn_8004DB90(void) {
    DrawingSceneStruct *item;
    s32 i;
    s32 k;
    s32 frame;
    s32 loopCount;
    u8 *table;

    CHAR_SELECT_BYTE(0x92) = 0;
    item = currentDrawingItem;
    frame = CSS_CAPTAIN_RECORD(2)->frame >> 16;

    if (CSS_CAPTAIN_SCENE_PHASE == 0) {
        if (frame == 30) {
            CSS_CAPTAIN_RECORD(2)->playMode = 0;
            CSS_CAPTAIN_SCENE_PHASE = 1;
        }
    } else if (CSS_CAPTAIN_SCENE_PHASE == 1) {
        CHAR_SELECT_BYTE(0x92) = 1;
        if (CHAR_SELECT_BYTE(0x7E) == 3) {
            goto remove;
        }
        if (CHAR_SELECT_BYTE(0x7E) == 1) {
            CSS_CAPTAIN_RECORD(2)->playMode = UI_PLAY_BACKWARD;
            CSS_CAPTAIN_RECORD(1)->playMode = UI_PLAY_BACKWARD;
            CSS_CAPTAIN_SCENE_PHASE = 2;
        }
    } else if (CSS_CAPTAIN_SCENE_PHASE == 2) {
        if (frame <= 5) {
            goto remove;
        }
    }

    if (CSS_CAPTAIN_SCENE_PHASE != 3) {
        for (i = 0; i < 6; i++) {
            s32 r11 = i + 11;
            s32 r3 = i + 3;
            s32 r17 = i + 17;
            if (CHAR_SELECT_BYTE(0x8C) == 0 && i == 5) {
                break;
            }
            if (CSS_CAPTAIN_SCENE_PHASE == 0) {
                if ((CSS_CAPTAIN_RECORD(r11)->frame >> 16) >= 5) {
                    CSS_CAPTAIN_RECORD(r11)->playMode = 0;
                }
            } else if (charSelectStruct.slotTeam[i] >= 0) {
                CSS_CAPTAIN_RECORD(r11)->playMode = UI_PLAY_FORWARD;
                CSS_CAPTAIN_RECORD(r3)->rgba =
                    (fn_80036214(item, 0, 0, CHAR_SELECT_BYTE(0x8D)) & 0xFFFFFF00) | (CSS_CAPTAIN_RECORD(r3)->rgba & 0xFF);
                CSS_CAPTAIN_RECORD(r3)->playMode = UI_PLAY_FORWARD;
                CSS_CAPTAIN_RECORD(r17)->flags |= UI_FLAG_VISIBLE;
                if ((CSS_CAPTAIN_RECORD(r17)->frame >> 16) <= 12) {
                    CSS_CAPTAIN_RECORD(r17)->frame = 12 << 16;
                    CSS_CAPTAIN_RECORD(r17)->playMode = UI_PLAY_FORWARD;
                    for (k = 0; k < 4; k++) {
                        if (CHAR_SELECT_BYTE(0x78 + CHAR_SELECT_BYTE(0x8D)) != 0 && charSelectStruct.cursorPos[k] == i) {
                            CSS_CAPTAIN_RECORD(23 + k)->frame = 0;
                        }
                    }
                }
                load_Icon(item, r17, 1, 0x1A, charSelectStruct.slotTeam[i]);
            } else {
                if ((CSS_CAPTAIN_RECORD(r17)->frame >> 16) > 12) {
                    CSS_CAPTAIN_RECORD(r17)->playMode = UI_PLAY_BACKWARD;
                } else {
                    CSS_CAPTAIN_RECORD(r17)->flags &= ~UI_FLAG_VISIBLE;
                }
                for (k = 0; k < 4; k++) {
                    if (CHAR_SELECT_BYTE(0x78 + CHAR_SELECT_BYTE(0x8D)) != 0 &&
                        charSelectStruct.cursorPos[CHAR_SELECT_BYTE(0x8D)] == i) {
                        frame = CSS_CAPTAIN_RECORD(r11)->frame >> 16;
                        if (frame < 15) {
                            CSS_CAPTAIN_RECORD(r11)->playMode = UI_PLAY_FORWARD;
                        } else if (frame <= 15) {
                            CSS_CAPTAIN_RECORD(r11)->playMode = 0;
                        } else {
                            CSS_CAPTAIN_RECORD(r11)->playMode = UI_PLAY_BACKWARD;
                        }
                        frame = CSS_CAPTAIN_RECORD(r3)->frame >> 16;
                        if (frame < 10) {
                            CSS_CAPTAIN_RECORD(r3)->playMode = UI_PLAY_FORWARD;
                        } else {
                            CSS_CAPTAIN_RECORD(r3)->playMode = 0;
                        }
                        CSS_CAPTAIN_RECORD(r3)->rgba = 0xFFFFFF00 | (CSS_CAPTAIN_RECORD(r3)->rgba & 0xFF);
                        break;
                    }
                }
                if (k >= 4) {
                    if ((CSS_CAPTAIN_RECORD(r11)->frame >> 16) <= 5) {
                        CSS_CAPTAIN_RECORD(r11)->playMode = 0;
                    } else {
                        CSS_CAPTAIN_RECORD(r11)->playMode = UI_PLAY_BACKWARD;
                    }
                    if ((CSS_CAPTAIN_RECORD(r3)->frame >> 16) != 0) {
                        CSS_CAPTAIN_RECORD(r3)->playMode = UI_PLAY_BACKWARD;
                    } else {
                        CSS_CAPTAIN_RECORD(r3)->playMode = 0;
                    }
                }
            }
        }
    }

    if (CHAR_SELECT_BYTE(0x78 + CHAR_SELECT_BYTE(0x8D)) != 0 && CSS_CAPTAIN_SCENE_PHASE == 1) {
        table = lbl_800FE924;
        CSS_CAPTAIN_RECORD(10)->flags |= UI_FLAG_VISIBLE;
        CSS_CAPTAIN_RECORD(9)->flags |= UI_FLAG_VISIBLE;
        CSS_CAPTAIN_RECORD(23)->flags |= UI_FLAG_VISIBLE;
        CSS_CAPTAIN_RECORD(10)->anchorSub = table[CHAR_SELECT_BYTE(0x8C) * 6 + charSelectStruct.cursorPos[CHAR_SELECT_BYTE(0x8D)]];
        CSS_CAPTAIN_RECORD(9)->anchorSub = table[CHAR_SELECT_BYTE(0x8C) * 6 + charSelectStruct.cursorPos[CHAR_SELECT_BYTE(0x8D)]];
        CSS_CAPTAIN_RECORD(23)->anchorSub = table[CHAR_SELECT_BYTE(0x8C) * 6 + charSelectStruct.cursorPos[CHAR_SELECT_BYTE(0x8D)]];
        if ((CSS_CAPTAIN_RECORD(23)->frame >> 16) < 12) {
            CSS_CAPTAIN_RECORD(23)->playMode = UI_PLAY_FORWARD;
        } else {
            CSS_CAPTAIN_RECORD(23)->playMode = 0;
            CSS_CAPTAIN_RECORD(23)->frame = 12 << 16;
        }
    } else {
        CSS_CAPTAIN_RECORD(10)->flags &= ~UI_FLAG_VISIBLE;
        CSS_CAPTAIN_RECORD(9)->flags &= ~UI_FLAG_VISIBLE;
        CSS_CAPTAIN_RECORD(23)->flags &= ~UI_FLAG_VISIBLE;
        CSS_CAPTAIN_RECORD(23)->frame = 0;
    }

    for (i = 0; i < 4; i++) {
        if (CHAR_SELECT_BYTE(0x78 + i) != 0) {
            CHAR_SELECT_BYTE(0x78 + i)--;
        }
    }
    return;

remove:
    CHAR_SELECT_BYTE(0x7E) = 2;
    removeGraphicsElementFromScene(item);
    removeCurrentDrawingItem();
}

void fn_8004E2EC(void) {
    u8 *data = lbl_800FCA60;
    UIRecordDescriptor *descriptors = (UIRecordDescriptor *)(data + 0x1BA4);
    DrawingSceneStruct *item;
    s32 mode = CHAR_SELECT_BYTE(0x8C);
    u8 *icons;
    u8 *anchors;
    s32 i;

    item = currentDrawingItem;
    descriptors[2].elementIndex = lbl_803CB870[mode];
    addGraphicsElementToScene(item, descriptors);
    icons = data + 0x1ED0 + mode * 6;
    anchors = data + 0x1EC4 + mode * 6;
    for (i = 0; i < 6; i++) {
        if (i == 5 && mode == 0) {
            continue;
        }
        load_Icon(item, 11 + i, 1, 0x19, icons[i]);
        CSS_CAPTAIN_RECORD(11 + i)->anchorSub = anchors[i];
        CSS_CAPTAIN_RECORD(17 + i)->flags &= ~UI_FLAG_VISIBLE;
        CSS_CAPTAIN_RECORD(17 + i)->anchorSub = anchors[i];
        load_Icon(item, 17 + i, 1, 0x1A, CHAR_SELECT_BYTE(0x8D));
        CSS_CAPTAIN_RECORD(3 + i)->anchorSub = anchors[i];
    }
    CSS_CAPTAIN_RECORD(10)->frame = CHAR_SELECT_BYTE(0x8D) << 16;
    load_Icon(item, 23, 1, 0x1A, CHAR_SELECT_BYTE(0x8D));
    if (mode == 0) {
        CSS_CAPTAIN_RECORD(8)->flags &= ~UI_FLAG_VISIBLE;
        CSS_CAPTAIN_RECORD(16)->flags &= ~UI_FLAG_VISIBLE;
        CSS_CAPTAIN_RECORD(22)->flags &= ~UI_FLAG_VISIBLE;
    }
    CHAR_SELECT_BYTE(0x7E) = 0;
    CHAR_SELECT_BYTE(0x92) = 0;
    CSS_CAPTAIN_SCENE_PHASE = 0;
    currentDrawingItem->func = fn_8004DB90;
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

void fn_8004F10C(void) {
    DrawingSceneStruct *item;
    s32 i;
    s32 k;
    s32 frame;
    s32 done;

    CHAR_SELECT_BYTE(0x92) = 0;
    item = currentDrawingItem;
    frame = CSS_CAPTAIN_RECORD(2)->frame >> 16;

    if (CSS_CAPTAIN_SCENE_PHASE == 0) {
        done = 0;
        if (frame == 15) {
            CSS_CAPTAIN_RECORD(2)->playMode = 0;
            done = 1;
        }
        if ((CSS_CAPTAIN_RECORD(1)->frame >> 16) == 15) {
            CSS_CAPTAIN_RECORD(1)->playMode = 0;
            done++;
        }
        if (done == 2) {
            CSS_CAPTAIN_SCENE_PHASE = 1;
            CHAR_SELECT_BYTE(0x90) = 0;
        }
    } else if (CSS_CAPTAIN_SCENE_PHASE == 1) {
        CHAR_SELECT_BYTE(0x92) = 1;
        if (CHAR_SELECT_BYTE(0x7D) == 3) {
            goto remove;
        }
        if (CHAR_SELECT_BYTE(0x7D) == 1) {
            CSS_CAPTAIN_RECORD(2)->playMode = UI_PLAY_BACKWARD;
            CSS_CAPTAIN_RECORD(1)->playMode = UI_PLAY_BACKWARD;
            CSS_CAPTAIN_SCENE_PHASE = 2;
        } else if (CHAR_SELECT_BYTE(0x7D) == 4) {
            CSS_CAPTAIN_RECORD(2)->playMode = UI_PLAY_FORWARD;
            CSS_CAPTAIN_RECORD(1)->playMode = UI_PLAY_FORWARD;
            CSS_CAPTAIN_SCENE_PHASE = 3;
        }
    } else if (CSS_CAPTAIN_SCENE_PHASE == 2) {
        if (frame <= 5) {
            goto remove;
        }
    } else if (CSS_CAPTAIN_SCENE_PHASE == 3) {
        CHAR_SELECT_BYTE(0x7D) = 2;
        if (CHAR_SELECT_BYTE(0x8E) == 2) {
            goto remove;
        }
        done = 0;
        if (frame >= 55) {
            CSS_CAPTAIN_RECORD(2)->playMode = 0;
            done = 1;
        }
        if ((CSS_CAPTAIN_RECORD(1)->frame >> 16) >= 50) {
            CSS_CAPTAIN_RECORD(1)->playMode = 0;
            done++;
        }
        if (done >= 2) {
            CHAR_SELECT_BYTE(0x8E) = 2;
        }
    }

    if (CSS_CAPTAIN_SCENE_PHASE != 3) {
        for (i = 0; i < 12; i++) {
            s32 r23 = i + 23;
            s32 r3 = i + 3;
            s32 r35 = i + 35;
            if (CSS_CAPTAIN_SCENE_PHASE == 0) {
                if ((CSS_CAPTAIN_RECORD(r23)->frame >> 16) >= 5) {
                    CSS_CAPTAIN_RECORD(r23)->playMode = 0;
                }
            } else if (charSelectStruct.slotTeam[i] >= 0) {
                CSS_CAPTAIN_RECORD(r23)->playMode = UI_PLAY_FORWARD;
                CSS_CAPTAIN_RECORD(r3)->playMode = UI_PLAY_FORWARD;
                CSS_CAPTAIN_RECORD(r35)->flags |= UI_FLAG_VISIBLE;
                if ((CSS_CAPTAIN_RECORD(r35)->frame >> 16) <= 12) {
                    CSS_CAPTAIN_RECORD(r35)->frame = 12 << 16;
                    CSS_CAPTAIN_RECORD(r35)->playMode = UI_PLAY_FORWARD;
                    for (k = 0; k < 4; k++) {
                        if (CHAR_SELECT_BYTE(0x78 + k) != 0 && charSelectStruct.cursorPos[k] == i) {
                            CSS_CAPTAIN_RECORD(47 + k)->frame = 0;
                        }
                    }
                }
                if (CHAR_SELECT_BYTE(0x74 + charSelectStruct.slotTeam[i]) != 0) {
                    load_Icon(item, r35, 1, 0x1A, charSelectStruct.slotTeam[i] + 4);
                } else {
                    load_Icon(item, r35, 1, 0x1A, charSelectStruct.slotTeam[i]);
                }
            } else {
                if ((CSS_CAPTAIN_RECORD(r35)->frame >> 16) > 12) {
                    CSS_CAPTAIN_RECORD(r35)->playMode = UI_PLAY_BACKWARD;
                } else {
                    CSS_CAPTAIN_RECORD(r35)->flags &= ~UI_FLAG_VISIBLE;
                }
                for (k = 0; k < 4; k++) {
                    if (CHAR_SELECT_BYTE(0x78 + k) != 0 && charSelectStruct.cursorPos[k] == i) {
                        frame = CSS_CAPTAIN_RECORD(r23)->frame >> 16;
                        if (frame < 15) {
                            CSS_CAPTAIN_RECORD(r23)->playMode = UI_PLAY_FORWARD;
                        } else if (frame <= 15) {
                            CSS_CAPTAIN_RECORD(r23)->playMode = 0;
                        } else {
                            CSS_CAPTAIN_RECORD(r23)->playMode = UI_PLAY_BACKWARD;
                        }
                        frame = CSS_CAPTAIN_RECORD(r3)->frame >> 16;
                        if (frame < 10) {
                            CSS_CAPTAIN_RECORD(r3)->playMode = UI_PLAY_FORWARD;
                        } else {
                            CSS_CAPTAIN_RECORD(r3)->playMode = 0;
                        }
                        CSS_CAPTAIN_RECORD(r3)->rgba = 0xFFFFFF00 | (CSS_CAPTAIN_RECORD(r3)->rgba & 0xFF);
                        break;
                    }
                }
                if (k >= 4) {
                    if ((CSS_CAPTAIN_RECORD(r23)->frame >> 16) <= 5) {
                        CSS_CAPTAIN_RECORD(r23)->playMode = 0;
                    } else {
                        CSS_CAPTAIN_RECORD(r23)->playMode = UI_PLAY_BACKWARD;
                    }
                    if ((CSS_CAPTAIN_RECORD(r3)->frame >> 16) != 0) {
                        CSS_CAPTAIN_RECORD(r3)->playMode = UI_PLAY_BACKWARD;
                    } else {
                        CSS_CAPTAIN_RECORD(r3)->playMode = 0;
                    }
                }
            }
        }
    }

    for (i = 0; i < 4; i++) {
        if (CHAR_SELECT_BYTE(0x78 + i) != 0 && CSS_CAPTAIN_SCENE_PHASE == 1) {
            if (CHAR_SELECT_BYTE(0x74 + i) != 0) {
                load_Icon(item, 47 + i, 1, 0x1A, i + 4);
            } else {
                load_Icon(item, 47 + i, 1, 0x1A, i);
            }
            CSS_CAPTAIN_RECORD(19 + i)->flags |= UI_FLAG_VISIBLE;
            CSS_CAPTAIN_RECORD(15 + i)->flags |= UI_FLAG_VISIBLE;
            CSS_CAPTAIN_RECORD(47 + i)->flags |= UI_FLAG_VISIBLE;
            CSS_CAPTAIN_RECORD(19 + i)->anchorSub = lbl_800FE5C8[charSelectStruct.cursorPos[i]];
            CSS_CAPTAIN_RECORD(15 + i)->anchorSub = lbl_800FE5C8[charSelectStruct.cursorPos[i]];
            CSS_CAPTAIN_RECORD(47 + i)->anchorSub = lbl_800FE5C8[charSelectStruct.cursorPos[i]];
            if ((CSS_CAPTAIN_RECORD(47 + i)->frame >> 16) < 12) {
                CSS_CAPTAIN_RECORD(47 + i)->playMode = UI_PLAY_FORWARD;
            } else {
                CSS_CAPTAIN_RECORD(47 + i)->playMode = 0;
                CSS_CAPTAIN_RECORD(47 + i)->frame = 12 << 16;
            }
        } else {
            CSS_CAPTAIN_RECORD(19 + i)->flags &= ~UI_FLAG_VISIBLE;
            CSS_CAPTAIN_RECORD(15 + i)->flags &= ~UI_FLAG_VISIBLE;
            CSS_CAPTAIN_RECORD(47 + i)->flags &= ~UI_FLAG_VISIBLE;
            CSS_CAPTAIN_RECORD(47 + i)->frame = 0;
        }
    }

    for (i = 0; i < 4; i++) {
        if (CHAR_SELECT_BYTE(0x78 + i) != 0) {
            CHAR_SELECT_BYTE(0x78 + i)--;
        }
    }
    return;

remove:
    CHAR_SELECT_BYTE(0x7D) = 2;
    CHAR_SELECT_BYTE(0x8E) = 0;
    removeGraphicsElementFromScene(item);
    removeCurrentDrawingItem();
}

void fn_8004F964(void) {
    u8 *data = lbl_800FCA60;
    DrawingSceneStruct *item = currentDrawingItem;
    u8 *icons;
    u8 *anchors;
    s32 i;
    s32 j;

    addGraphicsElementToScene(item, (const UIRecordDescriptor *)(data + 0x14E8));
    if (CHAR_SELECT_BYTE(0x90) != 0) {
        CSS_CAPTAIN_RECORD(2)->frame = 55 << 16;
        CSS_CAPTAIN_RECORD(2)->playMode = UI_PLAY_BACKWARD;
    }
    if (CHAR_SELECT_BYTE(0x90) != 0) {
        CSS_CAPTAIN_RECORD(1)->frame = 50 << 16;
        CSS_CAPTAIN_RECORD(1)->playMode = UI_PLAY_BACKWARD;
    } else {
        CSS_CAPTAIN_RECORD(1)->frame = 0;
        CSS_CAPTAIN_RECORD(1)->playMode = UI_PLAY_FORWARD;
    }

    icons = data + 0x1B74;
    anchors = data + 0x1B68;
    for (i = 0; i < 12; i++) {
        load_Icon(item, 23 + i, 1, 0x19, icons[i]);
        CSS_CAPTAIN_RECORD(23 + i)->anchorSub = anchors[i];
        if (CHAR_SELECT_BYTE(0x90) != 0) {
            for (j = 0; j < 12; j++) {
                if (lbl_800E854C[j] == icons[i]) {
                    CSS_CAPTAIN_RECORD(23 + i)->frame = 5 << 16;
                    CSS_CAPTAIN_RECORD(23 + i)->playMode = 0;
                    break;
                }
            }
        }
        CSS_CAPTAIN_RECORD(35 + i)->flags &= ~UI_FLAG_VISIBLE;
        CSS_CAPTAIN_RECORD(35 + i)->anchorSub = anchors[i];
        CSS_CAPTAIN_RECORD(3 + i)->anchorSub = anchors[i];
        if (charSelectStruct.slotTeam[i] >= 0) {
            CSS_CAPTAIN_RECORD(23 + i)->frame = 25 << 16;
            CSS_CAPTAIN_RECORD(23 + i)->playMode = 0;
            CSS_CAPTAIN_RECORD(3 + i)->frame = 25 << 16;
            CSS_CAPTAIN_RECORD(3 + i)->playMode = 0;
            CSS_CAPTAIN_RECORD(35 + i)->flags |= UI_FLAG_VISIBLE;
            CSS_CAPTAIN_RECORD(35 + i)->frame = 25 << 16;
            CSS_CAPTAIN_RECORD(35 + i)->playMode = 0;
            if (CHAR_SELECT_BYTE(0x74 + charSelectStruct.slotTeam[i]) != 0) {
                load_Icon(item, 35 + i, 1, 0x1A, charSelectStruct.slotTeam[i] + 4);
            } else {
                load_Icon(item, 35 + i, 1, 0x1A, charSelectStruct.slotTeam[i]);
            }
        }
    }

    for (i = 0; i < 4; i++) {
        CSS_CAPTAIN_RECORD(19 + i)->frame = i << 16;
        if (CHAR_SELECT_BYTE(0x74 + i) != 0) {
            load_Icon(item, 47 + i, 1, 0x1A, i + 4);
        } else {
            load_Icon(item, 47 + i, 1, 0x1A, i);
        }
    }

    CHAR_SELECT_BYTE(0x7D) = 0;
    CHAR_SELECT_BYTE(0x92) = 0;
    CSS_CAPTAIN_SCENE_PHASE = 0;
    CHAR_SELECT_BYTE(0x8E) = 1;
    currentDrawingItem->func = fn_8004F10C;
}

int fn_8004FD64(int team) {
    int slot = charSelectStruct.cursorPos[team];

    if ((s8)charSelectStruct.unk4C[slot] != 0) {
        return -1;
    }
    return characterIconsOnCSS[slot];
}

void fn_8004FDA0(int charID) {
    int i;

    for (i = 0; i < CHAR_SELECT_GRID_SLOTS; i++) {
        if (characterIconsOnCSS[i] == charID) {
            charSelectStruct.unk4C[i] = 1;
            return;
        }
    }
}

int fn_8004FDE8(int portA, int portB) {
    s32 candidates[8];
    s32 state[CHAR_SELECT_GRID_SLOTS];
    s32 count;
    s32 i;
    s32 cur;

    if (charSelectStruct.cursorPos[portA] != charSelectStruct.cursorPos[portB]) {
        return -2;
    }

    for (i = 0; i < CHAR_SELECT_GRID_SLOTS; i++) {
        state[i] = -1;
        if ((s8)charSelectStruct.unk4C[i] != 0) {
            state[i] = 0;
        } else if (charSelectStruct.slotTeam[i] >= 0) {
            state[i] = 0;
        } else if (characterIconsOnCSS[i] == 0xFF) {
            state[i] = 5;
        } else if (CHAR_SELECT_HALF(0x18) == i && CHAR_SELECT_BYTE(0x78) != 0) {
            state[i] = 1;
        } else if (CHAR_SELECT_HALF(0x1A) == i && CHAR_SELECT_BYTE(0x79) != 0) {
            state[i] = 2;
        } else if (CHAR_SELECT_HALF(0x1C) == i && CHAR_SELECT_BYTE(0x7A) != 0) {
            state[i] = 3;
        } else if (CHAR_SELECT_HALF(0x1E) == i && CHAR_SELECT_BYTE(0x7B) != 0) {
            state[i] = 4;
        }
    }

    cur = charSelectStruct.cursorPos[portA];
    for (i = 0; i < 8; i++) {
        candidates[i] = -1;
    }
    count = 0;
    if (cur - 13 >= 0 && state[cur - 13] < 0) {
        candidates[count++] = cur - 13;
    }
    if (cur - 12 >= 0 && state[cur - 12] < 0) {
        candidates[count++] = cur - 12;
    }
    if (cur - 11 >= 0 && state[cur - 11] < 0) {
        candidates[count++] = cur - 11;
    }
    if (cur - 1 >= 0 && state[cur - 1] < 0) {
        candidates[count++] = cur - 1;
    }
    if (cur + 1 < CHAR_SELECT_GRID_SLOTS && state[cur + 1] < 0) {
        candidates[count++] = cur + 1;
    }
    if (cur + 11 < CHAR_SELECT_GRID_SLOTS && state[cur + 11] < 0) {
        candidates[count++] = cur + 11;
    }
    if (cur + 12 < CHAR_SELECT_GRID_SLOTS && state[cur + 12] < 0) {
        candidates[count++] = cur + 12;
    }
    if (cur + 13 < CHAR_SELECT_GRID_SLOTS && state[cur + 13] < 0) {
        candidates[count++] = cur + 13;
    }

    charSelectStruct.cursorPos[portB] = candidates[rand() % count];
    return characterIconsOnCSS[charSelectStruct.cursorPos[portB]];
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

s32 fn_80050F78(s32 arg) {
    if (CHAR_SELECT_BYTE(0x7C) == 0) {
        if (arg == 2) {
            CHAR_SELECT_BYTE(0x7C) = 4;
            CHAR_SELECT_BYTE(0x90) = 1;
        } else if (arg != 0) {
            CHAR_SELECT_BYTE(0x7C) = 3;
        } else {
            CHAR_SELECT_BYTE(0x7C) = 1;
        }
    }

    if (CHAR_SELECT_BYTE(0x7C) == 2) {
        CHAR_SELECT_BYTE(0x7C) = 0;
        return TRUE;
    }
    return FALSE;
}

/* File_0x80050fe8 viewed charSelectStruct as s8[0x94]. */
#define charSelectStruct (*(s8(*)[0x94])&charSelectStruct)

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

void fn_8005138C(void) {
    DrawingSceneStruct *item;
    s32 i;
    s32 k;
    s32 frame;

    CHAR_SELECT_BYTE(0x92) = 0;
    item = currentDrawingItem;
    frame = CSS_CAPTAIN_RECORD(2)->frame >> 16;

    if (CSS_CAPTAIN_SCENE_PHASE == 0) {
        if (frame >= 20) {
            CSS_CAPTAIN_RECORD(2)->playMode = 0;
            CSS_CAPTAIN_SCENE_PHASE = 1;
        }
    } else if (CSS_CAPTAIN_SCENE_PHASE == 1) {
        CHAR_SELECT_BYTE(0x92) = 1;
        if (CHAR_SELECT_BYTE(0x7C) == 3) {
            goto remove;
        }
        if (CHAR_SELECT_BYTE(0x7C) == 1) {
            CSS_CAPTAIN_RECORD(2)->elementIndex = 0x13;
            CSS_CAPTAIN_RECORD(2)->frame = 20 << 16;
            CSS_CAPTAIN_RECORD(2)->playMode = UI_PLAY_BACKWARD;
            CSS_CAPTAIN_RECORD(1)->playMode = UI_PLAY_FORWARD;
            CSS_CAPTAIN_SCENE_PHASE = 2;
        } else if (CHAR_SELECT_BYTE(0x7C) == 4) {
            CSS_CAPTAIN_RECORD(2)->elementIndex = 0x14;
            CSS_CAPTAIN_RECORD(2)->frame = 20 << 16;
            CSS_CAPTAIN_RECORD(2)->playMode = UI_PLAY_BACKWARD;
            CSS_CAPTAIN_SCENE_PHASE = 3;
        }
    } else if (CSS_CAPTAIN_SCENE_PHASE == 2) {
        if (frame <= 0) {
            goto remove;
        }
    } else if (CSS_CAPTAIN_SCENE_PHASE == 3) {
        if ((CSS_CAPTAIN_RECORD(1)->frame >> 16) >= 50) {
            CSS_CAPTAIN_RECORD(1)->playMode = 0;
        }
        if ((CSS_CAPTAIN_RECORD(2)->frame >> 16) == 0) {
            CHAR_SELECT_BYTE(0x7C) = 2;
        }
        if (CHAR_SELECT_BYTE(0x8E) != 0) {
            goto remove;
        }
    }

    if (CSS_CAPTAIN_SCENE_PHASE != 3) {
        for (i = 0; i < CHAR_SELECT_GRID_SLOTS; i++) {
            s32 r47 = i + 47;
            s32 r3 = i + 3;
            s32 r119 = i + 119;
            if (characterIconsOnCSS[i] == 0xFF) {
                continue;
            }
            if (CSS_CAPTAIN_SCENE_PHASE == 0) {
                if ((CSS_CAPTAIN_RECORD(r47)->frame >> 16) >= 5) {
                    CSS_CAPTAIN_RECORD(r47)->playMode = 0;
                }
            } else if (charSelectStruct.slotTeam[i] >= 0) {
                CSS_CAPTAIN_RECORD(r47)->playMode = UI_PLAY_FORWARD;
                CSS_CAPTAIN_RECORD(r3)->playMode = UI_PLAY_FORWARD;
                CSS_CAPTAIN_RECORD(r119)->flags |= UI_FLAG_VISIBLE;
                if ((CSS_CAPTAIN_RECORD(r119)->frame >> 16) <= 12) {
                    CSS_CAPTAIN_RECORD(r119)->frame = 12 << 16;
                    CSS_CAPTAIN_RECORD(r119)->playMode = UI_PLAY_FORWARD;
                    for (k = 0; k < 4; k++) {
                        if (CHAR_SELECT_BYTE(0x78 + k) != 0 && charSelectStruct.cursorPos[k] == i) {
                            CSS_CAPTAIN_RECORD(155 + k)->frame = 0;
                        }
                    }
                }
                if (CHAR_SELECT_BYTE(0x74 + charSelectStruct.slotTeam[i]) != 0) {
                    load_Icon(item, r119, 1, 0x1A, charSelectStruct.slotTeam[i] + 4);
                } else {
                    load_Icon(item, r119, 1, 0x1A, charSelectStruct.slotTeam[i]);
                }
            } else {
                if ((CSS_CAPTAIN_RECORD(r119)->frame >> 16) > 12) {
                    CSS_CAPTAIN_RECORD(r119)->playMode = UI_PLAY_BACKWARD;
                } else {
                    CSS_CAPTAIN_RECORD(r119)->flags &= ~UI_FLAG_VISIBLE;
                }
                for (k = 0; k < 4; k++) {
                    if (CHAR_SELECT_BYTE(0x78 + k) != 0 && charSelectStruct.cursorPos[k] == i) {
                        frame = CSS_CAPTAIN_RECORD(r47)->frame >> 16;
                        if (frame < 15) {
                            CSS_CAPTAIN_RECORD(r47)->playMode = UI_PLAY_FORWARD;
                        } else if (frame <= 15) {
                            CSS_CAPTAIN_RECORD(r47)->playMode = 0;
                        } else {
                            CSS_CAPTAIN_RECORD(r47)->playMode = UI_PLAY_BACKWARD;
                        }
                        frame = CSS_CAPTAIN_RECORD(r3)->frame >> 16;
                        if (frame < 10) {
                            CSS_CAPTAIN_RECORD(r3)->playMode = UI_PLAY_FORWARD;
                        } else {
                            CSS_CAPTAIN_RECORD(r3)->playMode = 0;
                        }
                        CSS_CAPTAIN_RECORD(r3)->rgba = 0xFFFFFF00 | (CSS_CAPTAIN_RECORD(r3)->rgba & 0xFF);
                        break;
                    }
                }
                if (k >= 4) {
                    if ((CSS_CAPTAIN_RECORD(r47)->frame >> 16) <= 5) {
                        CSS_CAPTAIN_RECORD(r47)->playMode = 0;
                    } else {
                        CSS_CAPTAIN_RECORD(r47)->playMode = UI_PLAY_BACKWARD;
                    }
                    if ((CSS_CAPTAIN_RECORD(r3)->frame >> 16) != 0) {
                        CSS_CAPTAIN_RECORD(r3)->playMode = UI_PLAY_BACKWARD;
                    } else {
                        CSS_CAPTAIN_RECORD(r3)->playMode = 0;
                    }
                }
            }
        }
    } else {
        for (i = 0; i < CHAR_SELECT_GRID_SLOTS; i++) {
            if ((CSS_CAPTAIN_RECORD(47 + i)->frame >> 16) <= 5) {
                CSS_CAPTAIN_RECORD(47 + i)->playMode = 0;
            }
        }
    }

    for (i = 0; i < 4; i++) {
        if (CHAR_SELECT_BYTE(0x78 + i) != 0 && CSS_CAPTAIN_SCENE_PHASE <= 1) {
            if (CHAR_SELECT_BYTE(0x74 + i) != 0) {
                load_Icon(item, 155 + i, 1, 0x1A, i + 4);
            } else {
                load_Icon(item, 155 + i, 1, 0x1A, i);
            }
            CSS_CAPTAIN_RECORD(43 + i)->flags |= UI_FLAG_VISIBLE;
            CSS_CAPTAIN_RECORD(39 + i)->flags |= UI_FLAG_VISIBLE;
            CSS_CAPTAIN_RECORD(155 + i)->flags |= UI_FLAG_VISIBLE;
            CSS_CAPTAIN_RECORD(43 + i)->anchorSub = lbl_800FDE60[charSelectStruct.cursorPos[i]];
            CSS_CAPTAIN_RECORD(39 + i)->anchorSub = lbl_800FDE60[charSelectStruct.cursorPos[i]];
            CSS_CAPTAIN_RECORD(155 + i)->anchorSub = lbl_800FDE60[charSelectStruct.cursorPos[i]];
            if ((CSS_CAPTAIN_RECORD(155 + i)->frame >> 16) < 12) {
                CSS_CAPTAIN_RECORD(155 + i)->playMode = UI_PLAY_FORWARD;
            } else {
                CSS_CAPTAIN_RECORD(155 + i)->playMode = 0;
                CSS_CAPTAIN_RECORD(155 + i)->frame = 12 << 16;
            }
        } else {
            CSS_CAPTAIN_RECORD(43 + i)->flags &= ~UI_FLAG_VISIBLE;
            CSS_CAPTAIN_RECORD(39 + i)->flags &= ~UI_FLAG_VISIBLE;
            CSS_CAPTAIN_RECORD(155 + i)->flags &= ~UI_FLAG_VISIBLE;
            CSS_CAPTAIN_RECORD(155 + i)->frame = 0;
        }
    }

    for (i = 0; i < 4; i++) {
        if (CHAR_SELECT_BYTE(0x78 + i) != 0) {
            CHAR_SELECT_BYTE(0x78 + i)--;
        }
    }
    return;

remove:
    CHAR_SELECT_BYTE(0x8F) = 0;
    CHAR_SELECT_BYTE(0x7C) = 2;
    removeGraphicsElementFromScene(item);
    removeCurrentDrawingItem();
}

void fn_80051D00(void) {
    u8 *data = lbl_800FCA60;
    DrawingSceneStruct *item = currentDrawingItem;
    u8 *icons;
    u8 *anchors;
    s32 i;
    s32 j;
    s32 icon;

    if (CHAR_SELECT_BYTE(0x8E) == 1) {
        return;
    }

    addGraphicsElementToScene(item, (const UIRecordDescriptor *)data);
    if (CHAR_SELECT_BYTE(0x8F) == 1) {
        CSS_CAPTAIN_RECORD(2)->elementIndex = 0x14;
    }
    CSS_CAPTAIN_RECORD(1)->frame = 50 << 16;

    icons = data + 0x1424;
    anchors = data + 0x1400;
    for (i = 0; i < CHAR_SELECT_GRID_SLOTS; i++) {
        if (icons[i] == 0xFF) {
            CSS_CAPTAIN_RECORD(47 + i)->flags &= ~UI_FLAG_VISIBLE;
            CSS_CAPTAIN_RECORD(3 + i)->flags &= ~UI_FLAG_VISIBLE;
            continue;
        }
        icon = icons[i];
        if ((s8)charSelectStruct.unk4C[i] != 0) {
            icon = 0x36;
        }
        load_Icon(item, 47 + i, 1, 0x19, icon);
        CSS_CAPTAIN_RECORD(47 + i)->anchorSub = anchors[i];
        if (CHAR_SELECT_BYTE(0x8F) == 1) {
            for (j = 0; j < 12; j++) {
                if (lbl_800E854C[j] == icon) {
                    CSS_CAPTAIN_RECORD(47 + i)->frame = 5 << 16;
                    CSS_CAPTAIN_RECORD(47 + i)->playMode = 0;
                    break;
                }
            }
        }
        if (icon < 0x36) {
            if (g_d_GameSettings.exhibitionMatchInd == 0) {
                if (g_Challenge.charIsSuperstar[icon] != 0) {
                    CSS_CAPTAIN_RECORD(83 + i)->flags |= UI_FLAG_VISIBLE;
                }
            } else if (superstarUnlocked[icon] != 0) {
                CSS_CAPTAIN_RECORD(83 + i)->flags |= UI_FLAG_VISIBLE;
            }
        }
        CSS_CAPTAIN_RECORD(119 + i)->flags &= ~UI_FLAG_VISIBLE;
        CSS_CAPTAIN_RECORD(119 + i)->anchorSub = anchors[i];
        if (charSelectStruct.slotTeam[i] >= 0) {
            CSS_CAPTAIN_RECORD(47 + i)->frame = 25 << 16;
            CSS_CAPTAIN_RECORD(47 + i)->playMode = 0;
            CSS_CAPTAIN_RECORD(3 + i)->frame = 25 << 16;
            CSS_CAPTAIN_RECORD(3 + i)->playMode = 0;
            CSS_CAPTAIN_RECORD(119 + i)->flags |= UI_FLAG_VISIBLE;
            CSS_CAPTAIN_RECORD(119 + i)->frame = 25 << 16;
            CSS_CAPTAIN_RECORD(119 + i)->playMode = 0;
            if (CHAR_SELECT_BYTE(0x74 + charSelectStruct.slotTeam[i]) != 0) {
                load_Icon(item, 119 + i, 1, 0x1A, charSelectStruct.slotTeam[i] + 4);
            } else {
                load_Icon(item, 119 + i, 1, 0x1A, charSelectStruct.slotTeam[i]);
            }
        }
    }

    for (i = 0; i < 4; i++) {
        CSS_CAPTAIN_RECORD(43 + i)->frame = i << 16;
        if (CHAR_SELECT_BYTE(0x74 + i) != 0) {
            load_Icon(item, 155 + i, 1, 0x1A, i + 4);
        } else {
            load_Icon(item, 155 + i, 1, 0x1A, i);
        }
    }

    CHAR_SELECT_BYTE(0x7C) = 0;
    CHAR_SELECT_BYTE(0x92) = 0;
    CSS_CAPTAIN_SCENE_PHASE = 0;
    currentDrawingItem->func = fn_8005138C;
}
