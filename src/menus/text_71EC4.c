#include "menus/text_71EC4.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x800363d8.h"
#include "text/text.h"
#include "game/challenge/challenge_state.h"

extern u8 *lbl_2_bss_1A8248;
extern u8 *lbl_2_bss_1A824C;
extern void (*lbl_2_data_2A1E8[3])(CssSlot *slot);
extern void (*lbl_2_data_2A2EC[21])(CssSlot *slot);
extern UIRecordDescriptor lbl_2_data_2AADC[];
extern u8 lbl_803CBBC4[8];
extern BOOL maybeCheckAndResetGrapicsElement(void *scene, int handle, int frame);
extern void fn_2_82DE8(void);
extern void fn_80051D00(void);
extern u8 g_d_GameSettings[];
extern u8 g_MatchInfo[];
extern u8 superstarUnlocked[0x130];
extern u8 menuNumber[0x28];
extern u8 lbl_800FEF70[0x5D0];
extern u8 lbl_803CB8D0[];
extern int menuCursors[0x16];
extern u8 gameSetUpStep[0x64];
extern u8 Static_Stats_Tables[];
extern u8 challengeCaptainCharIDArray[][6];
extern u8 captainIDOrderedOnCapSS[6];
extern u8 lbl_2_data_2AF08[];
extern u8 mapCaptainCursorPositionToCharID[0x350];
extern u8 cursorPositions[];
extern u8 lbl_2_data_2AF4C[];
extern u8 lbl_803CBCD8[8];
extern int mainMenuCursorShown;
extern u8 *menuControlVariables;
extern void fn_80053FE8(void);
extern void fn_8004E2EC(void);
extern void fn_8004F964(void);
extern void fn_2_7308C(void);
extern u8 lbl_2_data_2B3A4[];
extern s32 lbl_2_bss_A844;
extern void updateCharacterSelectProcessCode(int arg0, int arg1);
extern void makeCursorMovable(int channel);
extern void makeCursorUnmovable(int channel);
extern void removeGraphicsElementFromScene(DrawingSceneStruct *node);

// The CssSlot array sits at this offset inside the ChallengeState block.
#define CSS_SLOT_BASE 0x1610

static int findCaptainOrderIndex(void);

// Record handles for the menu's graphics scene: node->firstHandle + offset.
static u8 *gfxRecord(int index) {
    return (u8 *)graphicsRelatedArray[index].object;
}

static void clearRecordFlagLowByte(int index) {
    u32 *word = (u32 *)(gfxRecord(index) + 0x58);

    *word &= ~0xFF;
}

static void setRecordFlagLowByte(int index) {
    u32 *word = (u32 *)(gfxRecord(index) + 0x58);

    *word = (*word & ~0xFF) | 0xFF;
}

static void markSelectionActive(void) {
    lbl_803CBBC4[3] = TRUE;
}

static void resetSelectionPhase(void) {
    lbl_803CBBC4[2] = FALSE;
    lbl_803CBBC4[0] = 0;
}






// Index of the captain-select order entry matching the challenge captain for
// the current cursor row, or -1 if none does.
static int findCaptainOrderIndex(void) {
    u8 target = challengeCaptainCharIDArray[superstarUnlocked[0xF4]][menuCursors[4]];
    int k;

    for (k = 0; k < 6; k++) {
        if (captainIDOrderedOnCapSS[k] == target) {
            return k;
        }
    }
    return -1;
}








// Phase 1: show the cursor record once the captain order matches.
static void fn_2_7308C_phase1(DrawingSceneStruct *node) {
    u8 *flags = lbl_803CBBC4;
    MenuScene *scene = (MenuScene *)node;
    int idx;

    if (flags[2] == 0) {
        *(u32 *)(gfxRecord(scene->firstHandle) + 0x5C) = 0;
        gfxRecord(scene->firstHandle)[0x68] = 1;
        *(u32 *)(gfxRecord(scene->firstHandle + 1) + 0x5C) = 0;
        gfxRecord(scene->firstHandle + 1)[0x68] = 1;
        idx = findCaptainOrderIndex();
        *(u32 *)(gfxRecord(scene->firstHandle + 2) + 0x5C) = lbl_2_data_2AF08[idx] << 18;
        flags[2] = 1;
        flags[3] = 1;
    }
    if (flags[3] == 1) {
        if (maybeCheckAndResetGrapicsElement(node, 0, 0x19) != FALSE) {
            flags[3] = 0;
            flags[2] = 0;
            flags[0] = 0;
        }
    }
}

// Phases 2 and 0x47: fade both records in, then wait for the two checks.
static void fn_2_7308C_phase2(DrawingSceneStruct *node) {
    u8 *flags = lbl_803CBBC4;
    MenuScene *scene = (MenuScene *)node;
    BOOL first;
    BOOL second;

    if (flags[2] == 0) {
        *(u32 *)(gfxRecord(scene->firstHandle) + 0x5C) = 0x190000;
        gfxRecord(scene->firstHandle)[0x68] = 4;
        *(u32 *)(gfxRecord(scene->firstHandle + 1) + 0x5C) = 0x190000;
        gfxRecord(scene->firstHandle + 1)[0x68] = 4;
        flags[2] = 1;
        flags[3] = 1;
    }
    if (flags[3] == 1) {
        first = maybeCheckAndResetGrapicsElement(node, 0, 0) != FALSE;
        second = maybeCheckAndResetGrapicsElement(node, 1, 0) != FALSE;
        if (first + second == 2) {
            flags[0] = 0;
            flags[3] = 0;
            flags[2] = 0;
            flags[4] = 1;
        }
    }
}

// Phase 3: set the captain and cursor-position records, then clear the phase.
static void fn_2_7308C_phase3(DrawingSceneStruct *node) {
    u8 *flags = lbl_803CBBC4;
    MenuScene *scene = (MenuScene *)node;
    int idx;
    int k;

    if (flags[2] == 0) {
        idx = findCaptainOrderIndex();
        *(u32 *)(gfxRecord(scene->firstHandle + 2) + 0x5C) = lbl_2_data_2AF08[idx] << 18;
        *(u32 *)(gfxRecord(scene->firstHandle + 3) + 0x5C) = lbl_2_data_2AF08[idx] << 18;
        for (k = 0; k < 8; k++) {
            *(u32 *)(gfxRecord(scene->firstHandle + 4 + k) + 0x5C) = ((s8)cursorPositions[3 + k]) << 16;
        }
        flags[2] = 1;
        flags[3] = 1;
    }
    if (flags[3] == 1) {
        flags[3] = 0;
        flags[2] = 0;
        flags[0] = 0;
    }
}

// .text:0x00073EFC size:0x5CC
void fn_2_73EFC(void) {
    return;
}

// .text:0x00073CBC size:0x240
void fn_2_73CBC(DrawingSceneStruct *node) {
    int cur0 = menuCursors[0];
    int count = 0;
    int sum = 0;
    int row;

    if (gameSetUpStep[7] != 1) {
        return;
    }
    if (Static_Stats_Tables[0x4751] == 0) {
        for (row = 0; row < 7; row++) {
            if (cur0 == row) {
                count++;
                sum += maybeCheckAndResetGrapicsElement(node, row + 3, fn_2_73B94(cur0)) != FALSE;
            }
            if (mainMenuCursorShown == 0) {
                if (cur0 == 6 && row == mainMenuCursorShown) {
                    count++;
                    sum += maybeCheckAndResetGrapicsElement(node, row + 3, 0) != FALSE;
                }
            } else if (mainMenuCursorShown == 6) {
                if (cur0 == 0 && row == mainMenuCursorShown) {
                    count++;
                    sum += maybeCheckAndResetGrapicsElement(node, row + 3, 0x36) != FALSE;
                }
            }
        }
        count += 2;
        sum += maybeCheckAndResetGrapicsElement(node, cur0 + 0x11, 0xE) != FALSE;
        sum += maybeCheckAndResetGrapicsElement(node, 0x20, 0xA) != FALSE;
    }
    if (sum == count) {
        if (Static_Stats_Tables[0x4751] != 0) {
            lbl_2_bss_A844 = mainMenuCursorShown;
        }
        mainMenuCursorShown = cur0;
        Static_Stats_Tables[0x4752] = 0;
        if (Static_Stats_Tables[0x4751] == 0) {
            makeCursorMovable(0);
        }
        gameSetUpStep[7] = 2;
        updateCharacterSelectProcessCode(0, 0x57);
    }
}

// .text:0x00073BF0 size:0xCC
int fn_2_73BF0(int x) {
    int result;

    if (mainMenuCursorShown == 0 && x == 6) {
        if (Static_Stats_Tables[0x4752] != 0) {
            result = 0x36;
        } else {
            result = 0x36;
        }
    } else if (mainMenuCursorShown == 6 && x == 0) {
        if (Static_Stats_Tables[0x4752] != 0) {
            result = 8;
        } else {
            result = 0;
        }
    } else if (mainMenuCursorShown <= x) {
        if (Static_Stats_Tables[0x4752] != 0) {
            result = 0x17;
        } else {
            result = 0xF;
        }
    } else if (mainMenuCursorShown > x) {
        if (Static_Stats_Tables[0x4752] != 0) {
            result = 0x26;
        } else {
            result = 0x1E;
        }
    }
    return result;
}

// .text:0x00073B94 size:0x5C
int fn_2_73B94(int x) {
    int result;

    if (mainMenuCursorShown == 0 && x == 6) {
        result = 0x2D;
    } else if (mainMenuCursorShown == 6 && x == 0) {
        result = 0xE;
    } else if (mainMenuCursorShown <= x) {
        result = 0x1D;
    } else if (mainMenuCursorShown > x) {
        result = 0x2C;
    }
    return result;
}

// .text:0x00073B54 size:0x40
int fn_2_73B54(int x) {
    if (mainMenuCursorShown == 0 && x == 6) {
        return 4;
    }
    if (mainMenuCursorShown == 6 && x == 0) {
        return 1;
    }
    return 1;
}

// .text:0x00073994 size:0x1C0
void fn_2_73994(DrawingSceneStruct *node, int idx) {
    MenuScene *scene = (MenuScene *)node;
    u8 *table = Static_Stats_Tables + 0x34;
    s32 a;
    s32 b;
    u8 v1;
    u8 t2;

    if (g_d_GameSettings[7] != GAME_TYPE_CHALLENGE) {
        a = mapCaptainCursorPositionToCharID[menuCursors[idx + 4]];
        b = mapCaptainCursorPositionToCharID[cursorPositions[idx]];
    } else if (idx != 0) {
        a = (s8)*((u8 *)&g_Challenge + 0x441F);
        b = a;
    } else {
        b = *((u8 *)&g_Challenge + 0x441D);
        a = b;
    }
    v1 = table[(a / 9) * 0x5A0 + (a % 9) * 0xA0];
    t2 = table[(b / 9) * 0x5A0 + (b % 9) * 0xA0];
    *(u32 *)(gfxRecord(scene->firstHandle + idx + 0x82) + 0x5C) = lbl_2_data_2B3A4[v1] << 16;
    *(u32 *)(gfxRecord(scene->firstHandle + idx + 0x7E) + 0x5C) = lbl_2_data_2B3A4[v1] << 16;
    load_Icon(node, idx + 0x89, 1, 3, lbl_2_data_2B3A4[v1]);
    load_Icon(node, idx + 0x8B, 1, 3, lbl_2_data_2B3A4[t2]);
}

// .text:0x000738C8 size:0xCC
void fn_2_738C8(void) {
    if (*(u16 *)((u8 *)menuControlVariables + 6) == 5) {
        insertGraphicDrawingFunction(fn_80053FE8, 0);
    }
    if (g_d_GameSettings[7] == GAME_TYPE_CHALLENGE) {
        menuNumber[0] = 0xD;
        menuNumber[9] = menuNumber[8];
        menuNumber[8] = *(u16 *)(lbl_800FEF70 + 0xD8);
        insertGraphicDrawingFunction(fn_8004E2EC, 0x3000);
    } else {
        menuNumber[0] = 0;
        menuNumber[9] = menuNumber[8];
        menuNumber[8] = *(u16 *)(lbl_800FEF70 + 0x8);
        insertGraphicDrawingFunction(fn_8004F964, 0x3000);
    }
}

// .text:0x00073758 size:0x170
void fn_2_73758(void) {
    DrawingSceneStruct *node = currentDrawingItem;
    MenuScene *scene = (MenuScene *)node;
    int i;

    addGraphicsElementToScene(node, (const UIRecordDescriptor *)lbl_2_data_2AF4C);
    for (i = 0; i < 8; i++) {
        *(u32 *)(gfxRecord(scene->firstHandle + 4 + i) + 0x5C) = ((s8)cursorPositions[3 + i]) << 16;
    }
    lbl_803CBCD8[5] = 0;
    currentDrawingItem->func = fn_2_7308C;
}

// .text:0x0007308C size:0x6CC
void fn_2_7308C(void) {
    DrawingSceneStruct *node = currentDrawingItem;
    u8 *flags = lbl_803CBBC4;

    switch (flags[0]) {
    case 1:
        fn_2_7308C_phase1(node);
        break;
    case 2:
        fn_2_7308C_phase2(node);
        break;
    case 3:
        fn_2_7308C_phase3(node);
        break;
    case 0x47:
        fn_2_7308C_phase2(node);
        break;
    }

    if (lbl_803CBCD8[5] != 0) {
        lbl_803CBCD8[5] = 0;
        removeGraphicsElementFromScene(node);
        removeCurrentDrawingItem();
    }
}

// .text:0x0007302C size:0x60
int fn_2_7302C(void) {
    u8 *row = challengeCaptainCharIDArray[superstarUnlocked[0xF4]];
    int target = *(int *)(Static_Stats_Tables + 0x46E0);
    int bound = (superstarUnlocked[0xF4] != 0) + 5;
    int i;

    for (i = 0; i < bound; i++) {
        if (target == row[i]) {
            return i;
        }
    }
    return i;
}

// .text:0x00073028 size:0x4
void fn_2_73028(void) {
}

// .text:0x00072E54 size:0x1D4
void fn_2_72E54(void *scene) {
    u8 *flags = lbl_803CBBC4;
    MenuScene *ms = scene;
    int idx = -1;
    u8 target;
    int k;

    if (flags[2] != 0) {
        return;
    }
    *(u32 *)(gfxRecord(ms->firstHandle) + 0x5C) = 0;
    gfxRecord(ms->firstHandle)[0x68] = 1;
    *(u32 *)(gfxRecord(ms->firstHandle + 1) + 0x5C) = 0;
    gfxRecord(ms->firstHandle + 1)[0x68] = 1;
    target = challengeCaptainCharIDArray[superstarUnlocked[0xF4]][menuCursors[4]];
    for (k = 0; k < 6; k++) {
        if (captainIDOrderedOnCapSS[k] == target) {
            idx = k;
            break;
        }
    }
    *(u32 *)(gfxRecord(ms->firstHandle + 2) + 0x5C) = lbl_2_data_2AF08[idx] << 18;
    for (k = 0; k < 6; k++) {
        if (captainIDOrderedOnCapSS[k] == mapCaptainCursorPositionToCharID[menuCursors[4]]) {
            break;
        }
    }
    flags[2] = 1;
    markSelectionActive();
}

// .text:0x00072DDC size:0x78
void fn_2_72DDC(void *scene) {
    u8 *flags = lbl_803CBBC4;

    if (flags[3] == 1) {
        BOOL complete = maybeCheckAndResetGrapicsElement(scene, 0, 0x19) != FALSE;

        if (complete != TRUE) {
            return;
        }
        flags[3] = 0;
        resetSelectionPhase();
    }
}

// .text:0x00072D60 size:0x7C
void fn_2_72D60(void *scene) {
    u8 *flags = lbl_803CBBC4;
    MenuScene *node = scene;

    if (flags[2] != 0) {
        return;
    }
    *(u32 *)((u8 *)graphicsRelatedArray[node->firstHandle].object + 0x5C) = 0x190000;
    *((u8 *)graphicsRelatedArray[node->firstHandle].object + 0x68) = 4;
    *(u32 *)((u8 *)graphicsRelatedArray[node->firstHandle + 1].object + 0x5C) = 0x190000;
    *((u8 *)graphicsRelatedArray[node->firstHandle + 1].object + 0x68) = 4;
    flags[2] = 1;
    flags[3] = 1;
}

// .text:0x00072CB4 size:0xAC
void fn_2_72CB4(void *scene) {
    u8 *flags = lbl_803CBBC4;

    if (flags[3] == 1) {
        BOOL first = maybeCheckAndResetGrapicsElement(scene, 0, 0) != FALSE;
        BOOL second = maybeCheckAndResetGrapicsElement(scene, 1, 0) != FALSE;

        if (first + second == 2) {
            flags[3] = 0;
            resetSelectionPhase();
            lbl_803CBBC4[4] = TRUE;
        }
    }
}

// .text:0x00072A88 size:0x22C
void fn_2_72A88(void *scene) {
    u8 *flags = lbl_803CBBC4;
    MenuScene *ms = scene;
    int idx = -1;
    u8 target;
    int k;

    if (flags[2] != 0) {
        return;
    }
    target = challengeCaptainCharIDArray[superstarUnlocked[0xF4]][menuCursors[4]];
    for (k = 0; k < 6; k++) {
        if (captainIDOrderedOnCapSS[k] == target) {
            idx = k;
            break;
        }
    }
    *(u32 *)(gfxRecord(ms->firstHandle + 2) + 0x5C) = lbl_2_data_2AF08[idx] << 18;
    *(u32 *)(gfxRecord(ms->firstHandle + 3) + 0x5C) = lbl_2_data_2AF08[idx] << 18;
    for (k = 0; k < 8; k++) {
        *(u32 *)(gfxRecord(ms->firstHandle + 4 + k) + 0x5C) = ((s8)cursorPositions[3 + k]) << 16;
    }
    flags[2] = 1;
    markSelectionActive();
}

// .text:0x00072A58 size:0x30
void fn_2_72A58(void) {
    u8 *flags = lbl_803CBBC4;

    if (flags[3] != 1) {
        return;
    }
    flags[3] = 0;
    flags[2] = 0;
    flags[0] = 0;
}

// .text:0x000729E0 size:0x78
void fn_2_729E0(void *scene) {
    u8 *flags = lbl_803CBBC4;
    MenuScene *node = scene;

    if (flags[2] != 0) {
        return;
    }
    *(u32 *)((u8 *)graphicsRelatedArray[node->firstHandle].object + 0x5C) = 0x190000;
    *((u8 *)graphicsRelatedArray[node->firstHandle].object + 0x68) = 1;
    *(u32 *)((u8 *)graphicsRelatedArray[node->firstHandle + 1].object + 0x5C) = 0x190000;
    *((u8 *)graphicsRelatedArray[node->firstHandle + 1].object + 0x68) = 1;
    flags[2] = 1;
    flags[3] = 1;
}

// .text:0x0007293C size:0xA4
void fn_2_7293C(void *scene) {
    u8 *flags = lbl_803CBBC4;

    if (flags[3] == 1) {
        BOOL first = maybeCheckAndResetGrapicsElement(scene, 0, 0x19) != FALSE;
        BOOL second = maybeCheckAndResetGrapicsElement(scene, 1, 0x19) != FALSE;

        if (first + second == 2) {
            flags[3] = 0;
            resetSelectionPhase();
        }
    }
}

// .text:0x000728C0 size:0x7C
void fn_2_728C0(void *scene) {
    u8 *flags = lbl_803CBBC4;
    MenuScene *node = scene;

    if (flags[2] != 0) {
        return;
    }
    *(u32 *)((u8 *)graphicsRelatedArray[node->firstHandle].object + 0x5C) = 0x190000;
    *((u8 *)graphicsRelatedArray[node->firstHandle].object + 0x68) = 4;
    *(u32 *)((u8 *)graphicsRelatedArray[node->firstHandle + 1].object + 0x5C) = 0x190000;
    *((u8 *)graphicsRelatedArray[node->firstHandle + 1].object + 0x68) = 4;
    flags[2] = 1;
    flags[3] = 1;
}

// .text:0x00072814 size:0xAC
void fn_2_72814(void *scene) {
    u8 *flags = lbl_803CBBC4;

    if (flags[3] == 1) {
        BOOL first = maybeCheckAndResetGrapicsElement(scene, 0, 0) != FALSE;
        BOOL second = maybeCheckAndResetGrapicsElement(scene, 1, 0) != FALSE;

        if (first + second == 2) {
            flags[3] = 0;
            resetSelectionPhase();
            lbl_803CBBC4[4] = TRUE;
        }
    }
}

// .text:0x0007265C size:0x1B8
void cssCheckSomethingAboutCharacters(void) {
    int i;
    int anyUnlocked = FALSE;
    int selection;

    if (g_d_GameSettings[7] == GAME_TYPE_CHALLENGE) {
        if (g_MatchInfo[0x11] == 0) {
            g_MatchInfo[0x11] = 1;
            insertGraphicDrawingFunction(fn_80053FE8, 0x3000);
            insertGraphicDrawingFunction(fn_2_82DE8, 0x3000);
        }
    }
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        if (superstarUnlocked[i] != 0) {
            anyUnlocked = TRUE;
            break;
        }
    }
    if (g_d_GameSettings[7] != GAME_TYPE_CHALLENGE) {
        if (anyUnlocked) {
            selection = 2;
        } else {
            selection = 1;
        }
    } else {
        selection = 0x13;
    }
    menuNumber[0] = selection;
    menuNumber[9] = menuNumber[8];
    menuNumber[8] = *(u16 *)(lbl_800FEF70 + selection * 0x10 + 8);
    insertGraphicDrawingFunction(fn_80051D00, 0x3000);
}

// .text:0x00072630 size:0x2C
void fn_2_72630(void) {
    insertGraphicDrawingFunction(fn_2_72594, 0x3000);
}

// .text:0x00072594 size:0x9C
void fn_2_72594(void) {
    DrawingSceneStruct *node = currentDrawingItem;
    int i;

    addGraphicsElementToScene(node, lbl_2_data_2AADC);
    for (i = 0; i < 4; i++) {
        load_Icon(node, i + 7, 1, 0x32, 3 - i);
    }
    load_Icon(node, 2, 1, 0x35, 0);
    currentDrawingItem->func = fn_2_7207C;
}

// .text:0x0007207C size:0x518
void fn_2_7207C(void) {
    DrawingSceneStruct *node = currentDrawingItem;
    MenuScene *scene = (MenuScene *)node;
    u8 phase = gameSetUpStep[0x5D];
    int i;
    BOOL a;
    BOOL b;

    switch (phase) {
    case 0x1E:
        if (gameSetUpStep[0x1F] == 0) {
            *(u32 *)(gfxRecord(scene->firstHandle) + 0x5C) = 0;
            gfxRecord(scene->firstHandle)[0x68] = 1;
            gfxRecord(scene->firstHandle + 2)[0x68] = 1;
            clearRecordFlagLowByte(scene->firstHandle + 3);
            clearRecordFlagLowByte(scene->firstHandle + 4);
            clearRecordFlagLowByte(scene->firstHandle + 5);
            clearRecordFlagLowByte(scene->firstHandle + 6);
            gfxRecord(scene->firstHandle + lbl_803CB8D0[menuCursors[0x13]] + 3)[0x68] = 1;
            setRecordFlagLowByte(scene->firstHandle + lbl_803CB8D0[menuCursors[0x13]] + 3);
            *(u32 *)(gfxRecord(scene->firstHandle + lbl_803CB8D0[menuCursors[0x13]] + 7) + 0x5C) = 0;
            gfxRecord(scene->firstHandle + lbl_803CB8D0[menuCursors[0x13]] + 7)[0x68] = 1;
            makeCursorUnmovable(0);
            gameSetUpStep[0x1F] = 1;
        }
        if (gameSetUpStep[0x1F] == 1) {
            a = maybeCheckAndResetGrapicsElement(node, 0, 0x16) != FALSE;
            b = maybeCheckAndResetGrapicsElement(node, lbl_803CB8D0[menuCursors[0x13]] + 7, 5) != FALSE;
            if (a + b == 2) {
                gameSetUpStep[0x5E] = 0;
                makeCursorMovable(0);
                gameSetUpStep[0x1F] = 2;
            }
        }
        break;
    case 0x1F:
        if (gameSetUpStep[0x1F] == 0) {
            gfxRecord(scene->firstHandle)[0x68] = 1;
            makeCursorUnmovable(0);
            gameSetUpStep[0x1F] = 1;
        }
        if (gameSetUpStep[0x1F] == 1) {
            if (maybeCheckAndResetGrapicsElement(node, 0, 0x1C)) {
                makeCursorMovable(0);
                gameSetUpStep[0x1F] = 2;
            }
        }
        break;
    case 0x20:
        if (gameSetUpStep[0x1F] == 0) {
            for (i = 0; i < 4; i++) {
                gfxRecord(scene->firstHandle + i + 3)[0x68] = 0;
                gfxRecord(scene->firstHandle + i + 7)[0x68] = 0;
                *(u32 *)(gfxRecord(scene->firstHandle + i + 3) + 0x5C) = 0;
                *(u32 *)(gfxRecord(scene->firstHandle + i + 7) + 0x5C) = 0;
                clearRecordFlagLowByte(scene->firstHandle + i + 3);
            }
            gfxRecord(scene->firstHandle + lbl_803CB8D0[menuCursors[0x13]] + 3)[0x68] = 1;
            setRecordFlagLowByte(scene->firstHandle + lbl_803CB8D0[menuCursors[0x13]] + 3);
            *(u32 *)(gfxRecord(scene->firstHandle + lbl_803CB8D0[menuCursors[0x13]] + 7) + 0x5C) = 0;
            gfxRecord(scene->firstHandle + lbl_803CB8D0[menuCursors[0x13]] + 7)[0x68] = 1;
            makeCursorUnmovable(0);
            gameSetUpStep[0x1F] = 1;
        }
        if (gameSetUpStep[0x1F] == 1) {
            if (maybeCheckAndResetGrapicsElement(node, lbl_803CB8D0[menuCursors[0x13]] + 7, 5)) {
                makeCursorMovable(0);
                gameSetUpStep[0x1F] = 2;
            }
        }
        break;
    case 0x21:
        if (gameSetUpStep[0x1F] == 0) {
            gfxRecord(scene->firstHandle)[0x68] = 1;
            makeCursorUnmovable(0);
            gameSetUpStep[0x1F] = 1;
        }
        if (gameSetUpStep[0x1F] == 1) {
            makeCursorMovable(0);
            gameSetUpStep[0x1F] = 2;
        }
        break;
    }

    if (Static_Stats_Tables[0x472A] == 1) {
        Static_Stats_Tables[0x472A] = 0xFF;
        removeGraphicsElementFromScene(node);
        removeCurrentDrawingItem();
    }
}

// .text:0x00072054 size:0x28
void fn_2_72054(int index, u8 state) {
    CssSlot *slot = (CssSlot *)(lbl_2_bss_1A8248 + index * sizeof(CssSlot) + CSS_SLOT_BASE);

    slot->state = state;
    slot->mode = 0;
}

// .text:0x00072038 size:0x1C
void fn_2_72038(int index, s16 value) {
    *(s16 *)(lbl_2_bss_1A8248 + index * sizeof(CssSlot) + 0x16C4) = value;
}

// .text:0x00071F60 size:0xD8
void fn_2_71F60(void) {
    int i;
    CssSlot *slot;
    u8 *scratch;
    u8 status = ((ChallengeState *)lbl_2_bss_1A8248)->_44F2;

    if (status == 1 || status == 2 || status == 3) {
        return;
    }
    for (i = 0; i < 8; i++) {
        slot = (CssSlot *)(lbl_2_bss_1A8248 + i * sizeof(CssSlot) + CSS_SLOT_BASE);
        slot->handler = lbl_2_data_2A2EC[slot->state];
        slot->handler(slot);
    }
    scratch = lbl_2_bss_1A824C;
    if (scratch[0x1972BC] != 0) {
        scratch[0x1972BC] = 0;
        removeCurrentDrawingItem();
    }
}

// .text:0x00071F20 size:0x40
void fn_2_71F20(CssSlot *slot) {
    slot->handler = lbl_2_data_2A2EC[slot->state];
    slot->handler(slot);
}

// .text:0x00071EFC size:0x24
void fn_2_71EFC(CssSlot *slot) {
    *(u8 *)(lbl_2_bss_1A8248 + slot->index * sizeof(CssSlot) + 0x16D0) = 0;
}

// .text:0x00071EC4 size:0x38
void fn_2_71EC4(CssSlot *slot) {
    lbl_2_data_2A1E8[slot->mode](slot);
}
