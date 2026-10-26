#define REP_HEADER_DATA_FN getRepHeaderData_rep0250
#include "debug/rep_0250.h"
#define SQRT2_LINKAGE static
#include "game/UnknownHomes_Game.h"
#include "header_rep_data.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x80035ca4.h"
#include "Unknown/File_0x80034cec.h"
#include "Unknown/File_0x80034e20.h"
#include "text/text.h"
#include "static/UnknownHomes_Static.h"

typedef struct UIPos16 {
    /*0x00*/ u8 pad00[0x14];
    /*0x14*/ s16 x;
    /*0x16*/ s16 y;
} UIPos16;

typedef struct DebugMenuScene {
    /*0x00*/ void (*func)(void);
    /*0x04*/ u8 pad04[0x08];
    /*0x0C*/ DrawingSceneStruct *parent;
    /*0x10*/ s16 state;
    /*0x12*/ u8 pad12[2];
    /*0x14*/ u16 firstHandle;
    /*0x16*/ u16 handleCount;
    /*0x18*/ u16 timer;
    /*0x1A*/ u8 cursor;
} DebugMenuScene;

extern void fn_80035A00(void);
extern void fn_800AD038(void *arg0);
extern void fn_800111B4(void *arg0);
extern s32 diskReadRelated(void *arg0, s32 arg1);
extern void fn_80035ED0(s32 arg0);
extern void fn_80035EEC(s32 arg0, s32 arg1);
extern UIPos16 *fn_80035F20(u8 arg0, s32 arg1, u16 arg2, s16 arg3);
extern void fn_8003664C(u8 arg0, s32 arg1, u16 arg2, s32 arg3);
extern u16 fn_80036824(u8 arg0, s32 arg1, s32 arg2);

extern u8 lbl_80366158[0x30];
extern u8 lbl_1_common_bss_47698[0x22D8];

typedef struct DebugMenuState {
    /*0x00*/ s32 screen;
    /*0x04*/ s32 menuCursor;
    /*0x08*/ s32 pageCursor;
    /*0x0C*/ u8 phase;
    /*0x0D*/ u8 pageDirty;
    /*0x0E*/ u8 pageShown;
    /*0x0F*/ u8 page;
    /*0x10*/ u8 prevPage;
    /*0x11*/ u8 pad11[0x13];
} DebugMenuState;

extern DebugMenuState lbl_1_common_bss_47674;

#define SCENE_REC(scene, k) \
    ((UIRecord *)graphicsRelatedArray[((MenuScene *)(scene))->firstHandle + (k)].object)

u32 lbl_1_data_AB0[0x30] = {
    0x00030000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x20324420, 0x20205649, 0x45574552, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x4D4F5649, 0x45205649, 0x45574552, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x54455354, 0x204D4F56, 0x49452030, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x54455354, 0x204D4F56, 0x49452031, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x54455354, 0x204D4F56, 0x49452032, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

u32 skyPanoramaFileDescriptorDebug[4] = {0x40B, 0x4037CF5C, 0x18B3A800, 0x208AF0};

u32 lbl_1_data_B80 = 0x10000;
s32 lbl_1_data_B84 = 0xBB8;

UIRecordDescriptor lbl_1_data_B88[2] = {
    {0, 0, {0}, 0xFFFFFFFF, 1, 5, UI_NO_PARENT, 0, {0}, 1, 0},
    {UI_DESC_END},
};

UIRecordDescriptor lbl_1_data_BC8[5] = {
    {0, 0, {0}, 0xFFFFFFFF, 1, 5, UI_NO_PARENT, 0, {0}, 1, 0},
    {0, 0, {0}, 0xFFFFFFFF, 1, 5, UI_NO_PARENT, 0, {0}, 1, 0},
    {0, 0, {0}, 0xFFFFFFFF, 1, 5, UI_NO_PARENT, 0, {0}, 1, 0},
    {0, 2, {0}, 0xFFFFFFFF, 1, 5, UI_NO_PARENT, 0, {0}, 1, 0},
    {UI_DESC_END},
};

UIRecordDescriptor lbl_1_data_C68[3] = {
    {0, 5, {0}, 0xFFFFFFFF, 1, 5, UI_NO_PARENT, 0, {0}, 1, 0},
    {0, 4, {0}, 0xFFFFFFFF, 1, 5, UI_NO_PARENT, 0, {0}, 1, 0},
    {UI_DESC_END},
};

UIRecordDescriptor lbl_1_data_CC8[3] = {
    {0, 8, {0}, 0xFFFFFFFF, 1, 5, UI_NO_PARENT, 0x0A, {0}, 1, 0},
    {0, 9, {0}, 0xFFFFFFFF, 1, 5, UI_NO_PARENT, 0x0A, {0}, 1, 0},
    {UI_DESC_END},
};
char lbl_1_data_D28[12][0x20] = {
    "TEX_TEST1", "TEX_TEST2", "TEX_TEST3", "TEX_TEST4", "TEX_TEST5", "TEX_TEST6",
    "TEX_TEST7", "TEX_TEST8", "TEX_TEST9", "TEX_TEST10", "TEX_TEST11", "GAME_TD",
};
u8 lbl_1_data_EA8[0x64] = {
    0x00, 0x03, 0x0D, 0x0E, 0x00, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00, 0x4C,
    0x83, 0xA4, 0x89, 0x46, 0x40, 0x02, 0x83, 0x26,
    0x85, 0x98, 0x40, 0x02, 0x00, 0x7C, 0x00, 0x4D,
    0x00, 0x8A, 0x00, 0x3E, 0x00, 0x90, 0x40, 0x02,
    0x82, 0x59, 0x8C, 0xC5, 0x40, 0x00, 0x00, 0x27,
    0x00, 0x36, 0x00, 0x24, 0x00, 0x27, 0x00, 0x24,
    0x00, 0x36, 0x00, 0x27, 0x00, 0x36, 0x00, 0x24,
    0x00, 0x29, 0x00, 0x24, 0x00, 0x27, 0x00, 0x36,
    0x00, 0x29, 0x40, 0x00, 0x00, 0x2A, 0x00, 0x27,
    0x00, 0x36, 0x00, 0x2A, 0x00, 0x29, 0x00, 0x36,
    0x00, 0x2B, 0x00, 0x29, 0x00, 0x36, 0x00, 0x36,
    0x00, 0x2B, 0x40, 0x00,
};
u32 DebugTexFiles[44] = {
    0x0000040B, 0x4005BDE4, 0x0EAB5000, 0x000161A0,
    0x0000040B, 0x40002BDC, 0x0EACB800, 0x00001430,
    0x0000040B, 0x40004E98, 0x0EACD000, 0x00001E18,
    0x0000040B, 0x40011910, 0x0EACF000, 0x00006C30,
    0x0000040B, 0x40006038, 0x0EAD6000, 0x0000338C,
    0x0000040B, 0x40006044, 0x0EAD9800, 0x00003390,
    0x0000040B, 0x40004380, 0x0EADD000, 0x000018DC,
    0x0000040B, 0x4000124C, 0x0EADF000, 0x00000488,
    0x0000040B, 0x40000478, 0x0EADF800, 0x00000208,
    0x0000040B, 0x40002E6C, 0x0EAE0000, 0x00001510,
    0x0000040B, 0x4000785C, 0x0EAE1800, 0x000023A8,
};
E(u8, BOOL) lbl_1_data_FBC = TRUE;
u16 lbl_1_data_FBE = 3;

static u16 lbl_1_bss_2FD6;
static u16 lbl_1_bss_2FD4;
static u16 lbl_1_bss_2FD2;
static u8 lbl_1_bss_2FD1;
static u8 gPhase;
DrawingSceneStruct *lbl_1_bss_2FCC;
static void *gTextBank;
static s32 gLoadIndex;
static u16 lbl_1_bss_2FC2;
static u16 gLoadFrame;
static u16 lbl_1_bss_2FBE;
static u16 lbl_1_bss_2FBC;
static u16 lbl_1_bss_2FBA;
u8 lbl_1_bss_2FB9;
static u8 lbl_1_bss_2FB8;
static u16 lbl_1_bss_2FB6;
static u16 lbl_1_bss_2FB4;
static u16 lbl_1_bss_2FB2;
static u8 lbl_1_bss_2FB1;
static u8 lbl_1_bss_2FB0;
static u8 gMode;
static E(u8, BOOL) lbl_1_bss_2FAE;
u16 lbl_1_bss_2FAC;
static u8 lbl_1_bss_2FAB;
s8 lbl_1_bss_2FAA;
static u8 lbl_1_bss_2FA9;
u8 lbl_1_bss_2FA8;

static inline void drawThreeDigits(s32 value) {
    SCENE_REC(lbl_1_bss_2FCC, 0)->frame = 0x80000;
    fn_8003664C(lbl_1_data_BC8[0].tag, 0, value / 1000 + 10, 4);
    value %= 1000;
    SCENE_REC(lbl_1_bss_2FCC, 1)->frame = 0xC0000;
    fn_8003664C(lbl_1_data_BC8[0].tag, 1, value / 100 + 10, 5);
    value %= 100;
    SCENE_REC(lbl_1_bss_2FCC, 2)->frame = 0x100000;
    fn_8003664C(lbl_1_data_BC8[0].tag, 2, value / 10 + 10, 6);
}

/* Clears buf[n] down to buf[1]; buf[0] is left untouched. */
static inline void clearBytes(u8 *buf, s32 n) {
    do {
        buf[n] = 0;
    } while (--n);
}

// .text:0x00009AB0 size:0x3F0
void fn_1_9AB0(void) {
    s32 value;
    DebugMenuScene *item = (DebugMenuScene *)currentDrawingItem;

    switch (currentDrawingItem->state) {
    case 0:
        fn_800111B4(lbl_1_data_EA8);
        gTextBank = lbl_1_data_EA8 + 4;
        *(u16 *)lbl_1_common_bss_47698 = 0;
        clearBytes(lbl_1_common_bss_47698 + 2, 10);
        lbl_1_common_bss_47698[0xC] = 0;
        item->cursor = 0;
        gLoadIndex = 0;
        lbl_1_bss_2FAA = 0;
        gMode = 0;
        lbl_1_bss_2FB1 = 1;
        gPhase = 0;
        currentDrawingItem->state = 1;
        break;
    case 1:
        {
            s32 idx = gLoadIndex;
            if (idx > 11) {
                item->state = 2;
            } else if (diskReadRelated((u8 *)DebugTexFiles + idx * 16, idx & 0xFF)) {
                gLoadIndex++;
            }
        }
        break;
    case 2:
        fn_1_97E4();
        switch (lbl_1_bss_2FAA) {
        case 0:
            if (gPhase == 0) {
                gPhase = 1;
            } else {
                if (gMode == 1) {
                    if (--lbl_1_data_B84 < 0) {
                        lbl_1_data_B84 = 3000;
                    }
                    value = lbl_1_data_B84;
                    if (value % 10 == 0) {
                        fn_1_90E4(value);
                    }
                }
                gPhase = 2;
            }
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            if (gPhase == 0) {
                gPhase = 1;
            } else {
                if (gPhase == 1) {
                    fn_1_97B8();
                }
                gPhase = 2;
            }
            break;
        case 11:
            if (gPhase == 0) {
                gPhase = 1;
            } else {
                gPhase = 2;
            }
            break;
        case 10:
            if (gPhase == 0) {
                gPhase = 1;
            } else {
                if (gPhase == 1) {
                    if (gMode == 1 || gMode == 3) {
                        fn_1_90B8();
                    } else {
                        fn_1_90B8();
                    }
                }
                gPhase = 2;
            }
            break;
        }
        break;
    }
}

// .text:0x000097E4 size:0x2CC
void fn_1_97E4(void) {
    DebugMenuScene *item = (DebugMenuScene *)currentDrawingItem;

    switch (*(u16 *)((u8 *)&AtBat_ButtonInput1 + 4)) {
    case INPUT_BUTTON_A:
        lbl_1_bss_2FB0 = 0;
        lbl_1_bss_2FB1 = 0;
        gPhase = 0;
        gMode++;
        if (gMode == 3) {
            gMode = 0;
        }
        if (lbl_1_bss_2FAA != 11) {
            removeGraphicsElementFromScene(lbl_1_bss_2FCC);
        }
        lbl_1_bss_2FAE = FALSE;
        break;
    case INPUT_BUTTON_B:
        removeGraphicsElementFromScene(lbl_1_bss_2FCC);
        fn_80035A00();
        fn_800AD038(*(void **)(lbl_80366158 + 8));
        item->parent->state = 1;
        break;
    case INPUT_BUTTON_Y:
        lbl_1_data_FBC = TRUE;
        break;
    case INPUT_BUTTON_X:
        lbl_1_data_FBC = FALSE;
        break;
    case INPUT_TRIGGER_R:
        lbl_1_data_B80 = 0;
        break;
    case INPUT_BUTTON_START:
        lbl_1_data_B80 = 0x10000;
        break;
    case INPUT_BUTTON_UP:
        if (item->cursor != 0) {
            item->cursor--;
        } else {
            item->cursor = 1;
        }
        break;
    case INPUT_BUTTON_DOWN:
        item->cursor++;
        if (item->cursor == 2) {
            item->cursor = 0;
        }
        break;
    case INPUT_BUTTON_LEFT | INPUT_BUTTON_RIGHT:
    case INPUT_TRIGGER_Z:
    case INPUT_TRIGGER_L:
        break;
    case INPUT_BUTTON_LEFT:
        switch (item->cursor) {
        case 0:
            lbl_1_bss_2FB8 = 0;
            lbl_1_bss_2FAA++;
            if (lbl_1_bss_2FAA >= 12) {
                lbl_1_bss_2FAA = 0;
            }
            break;
        case 1:
            lbl_1_data_B80 += 1000;
            if (lbl_1_data_B80 > 0x70000) {
                lbl_1_data_B80 = 0x70000;
            }
            break;
        }
        gPhase = 0;
        break;
    case INPUT_BUTTON_RIGHT:
        switch (item->cursor) {
        case 0:
            lbl_1_bss_2FB8 = 0;
            lbl_1_bss_2FAA--;
            if (lbl_1_bss_2FAA < 0) {
                lbl_1_bss_2FAA = 11;
            }
            break;
        case 1:
            lbl_1_data_B80 -= 1000;
            if (lbl_1_data_B80 >= (u32)-1000) {
                lbl_1_data_B80 = 0;
            }
            break;
        }
        gPhase = 0;
        break;
    }
}

// .text:0x000097B8 size:0x2C
void fn_1_97B8(void) {
    insertGraphicDrawingFunction(fn_1_973C, 2);
}

// .text:0x0000973C size:0x7C
void fn_1_973C(void) {
    DebugMenuScene *item = (DebugMenuScene *)currentDrawingItem;

    addGraphicsElementToScene((DrawingSceneStruct *)item, lbl_1_data_B88);
    SCENE_REC(item, 0)->textureSlot = lbl_1_bss_2FAA;
    item->timer = 0;
    currentDrawingItem->func = fn_1_96D4;
}

// .text:0x000096D4 size:0x68
void fn_1_96D4(void) {
    DebugMenuScene *item = (DebugMenuScene *)currentDrawingItem;
    u16 buttons;

    item->timer++;
    buttons = AtBat_ButtonInput1._02;
    if ((buttons & INPUT_BUTTON_LEFT) || (buttons & INPUT_BUTTON_RIGHT)) {
        removeGraphicsElementFromScene((DrawingSceneStruct *)item);
        removeCurrentDrawingItem();
    }
    lbl_1_bss_2FB9 = lbl_1_bss_2FAA;
}

// .text:0x000096D0 size:0x4
void fn_1_96D0(void) {
    return;
}

// .text:0x000096A4 size:0x2C
void fn_1_96A4(void) {
    insertGraphicDrawingFunction(fn_1_9380, 2);
}

// .text:0x00009380 size:0x324
void fn_1_9380(void) {
    u8 tag = lbl_1_data_BC8[0].tag;
    DebugMenuScene *item = (DebugMenuScene *)currentDrawingItem;
    UIPos16 *pos;
    u16 count;
    s32 value;

    lbl_1_bss_2FCC = (DrawingSceneStruct *)item;
    if (gMode == 0) {
        addGraphicsElementToScene((DrawingSceneStruct *)item, lbl_1_data_BC8);
        count = fn_80036824(tag, 1, 4);
        fn_8003664C(tag, 0, count, 2);
        fn_8003664C(tag, 1, 0x11, 3);
    } else if (gMode == 1) {
        addGraphicsElementToScene((DrawingSceneStruct *)item, lbl_1_data_BC8);
        value = lbl_1_data_B84;
        SCENE_REC(lbl_1_bss_2FCC, 0)->frame = 0x80000;
        fn_8003664C(tag, 0, value / 1000 + 10, 4);
        value %= 1000;
        SCENE_REC(lbl_1_bss_2FCC, 1)->frame = 0xC0000;
        fn_8003664C(tag, 1, value / 100 + 10, 5);
        value %= 100;
        SCENE_REC(lbl_1_bss_2FCC, 2)->frame = 0x100000;
        fn_8003664C(tag, 2, value / 10 + 10, 6);
    } else {
        addGraphicsElementToScene((DrawingSceneStruct *)item, lbl_1_data_C68);
        pos = fn_80035F20(lbl_1_data_C68[0].tag, 1, gLoadFrame, -1);
        SCENE_REC(item, 0)->pos.x = pos->x / 2;
        SCENE_REC(item, 0)->pos.y = pos->y / 2;
        fn_80035ED0(1);
        fn_8003664C(lbl_1_data_C68[0].tag, 0, lbl_1_data_FBE, 1);
        gLoadFrame++;
        if (gLoadFrame > 7) {
            gLoadFrame = 0;
        }
        lbl_1_data_FBE++;
        if (lbl_1_data_FBE > 9) {
            lbl_1_data_FBE = 0;
        }
    }
    item->timer = 0;
    currentDrawingItem->func = fn_1_9290;
}

// .text:0x00009290 size:0xF0
void fn_1_9290(void) {
    DebugMenuScene *item = (DebugMenuScene *)currentDrawingItem;

    item->timer++;
    if (gMode == 0) {
        fn_80035EEC(3, 0);
        fn_80035EEC(7, 1);
        fn_80035ED0(2);
    } else if (gMode == 1) {
        fn_80035EEC(0xB, 0);
        fn_80035EEC(0xF, 1);
        fn_80035EEC(0x13, 2);
    } else {
        fn_80035ED0(2);
        fn_80035ED0(3);
    }
    if (lbl_1_bss_2FB9 != lbl_1_bss_2FAA) {
        removeGraphicsElementFromScene((DrawingSceneStruct *)item);
        removeCurrentDrawingItem();
    }
    if (AtBat_ButtonInput1._02 & INPUT_BUTTON_B) {
        removeCurrentDrawingItem();
    }
}

// .text:0x000090E4 size:0x1AC
void fn_1_90E4(s32 value) {
    removeGraphicsElementFromScene(lbl_1_bss_2FCC);
    addGraphicsElementToScene(lbl_1_bss_2FCC, lbl_1_data_BC8);
    drawThreeDigits(value);
}

// .text:0x000090B8 size:0x2C
void fn_1_90B8(void) {
    insertGraphicDrawingFunction(fn_1_8F34, 2);
}

// .text:0x00008F34 size:0x184
void fn_1_8F34(void) {
    DebugMenuScene *item = (DebugMenuScene *)currentDrawingItem;

    if (AtBat_ButtonInput1._02 & INPUT_BUTTON_B) {
        removeGraphicsElementFromScene(lbl_1_bss_2FCC);
        removeCurrentDrawingItem();
        return;
    }
    lbl_1_bss_2FCC = (DrawingSceneStruct *)item;
    addGraphicsElementToScene((DrawingSceneStruct *)item, lbl_1_data_CC8);
    if (gMode == 1 || gMode == 3) {
        UIPos16 *pos = fn_80035F20(lbl_1_data_CC8[0].tag, 1, lbl_1_bss_2FAC, lbl_1_bss_2FAC + 2);

        SCENE_REC(item, 0)->pos.x = pos->x;
        SCENE_REC(item, 0)->pos.y = pos->y;
        fn_80035ED0(1);
        lbl_1_bss_2FAC++;
        if (lbl_1_bss_2FAC > 3) {
            lbl_1_bss_2FAC = 0;
        }
    } else {
        SCENE_REC(item, 0)->elementIndex = 7;
        fn_80035ED0(1);
        fn_80035ED0(2);
        fn_80035ED0(3);
    }
    currentDrawingItem->func = fn_1_8DBC;
}

// .text:0x00008DBC size:0x178
void fn_1_8DBC(void) {
    DebugMenuScene *item = (DebugMenuScene *)currentDrawingItem;
    u16 buttons;

    item->timer++;
    if (gMode == 1 || gMode == 3) {
        if (menuGraphicsStructures[0].unk69[0] == 1) {
            if (lbl_1_bss_2FAE == FALSE) {
                removeCurrentDrawingItem();
                lbl_1_bss_2FAE = TRUE;
                return;
            }
            fn_1_8CD4();
        }
        fn_80035ED0(2);
        fn_80035ED0(3);
    }
    buttons = AtBat_ButtonInput1._02;
    if ((buttons & INPUT_BUTTON_LEFT) || (buttons & INPUT_BUTTON_RIGHT)) {
        removeGraphicsElementFromScene((DrawingSceneStruct *)item);
        removeCurrentDrawingItem();
    }
}

// .text:0x00008CD4 size:0xE8
void fn_1_8CD4(void) {
    UIPos16 *pos = fn_80035F20(lbl_1_data_CC8[0].tag, 1, lbl_1_bss_2FAC, lbl_1_bss_2FAC + 2);

    SCENE_REC(lbl_1_bss_2FCC, 0)->pos.x = pos->x;
    SCENE_REC(lbl_1_bss_2FCC, 0)->pos.y = pos->y;
    fn_80035ED0(1);
    lbl_1_bss_2FAC++;
    if (lbl_1_bss_2FAC > 3) {
        lbl_1_bss_2FAC = 0;
    }
}

// .text:0x00008C9C size:0x38
void fn_1_8C9C(void) {
    *(u16 *)lbl_1_common_bss_47698 = 0;
    clearBytes(lbl_1_common_bss_47698 + 2, 10);
    lbl_1_common_bss_47698[0xC] = 0;
}

// .text:0x00008B90 size:0x10C
void fn_1_8B90(void) {
    DebugMenuScene *item;
    u16 buttons;

    switch (lbl_1_common_bss_47674.screen) {
    case 0:
        lbl_1_common_bss_47674.screen++;
        break;
    case 1:
        item = (DebugMenuScene *)currentDrawingItem;
        buttons = AtBat_ButtonInput1._02;
        if (buttons & INPUT_BUTTON_UP) {
            if (--lbl_1_common_bss_47674.menuCursor < 0) {
                lbl_1_common_bss_47674.menuCursor = 1;
            }
        } else if (buttons & INPUT_BUTTON_DOWN) {
            if (++lbl_1_common_bss_47674.menuCursor == 2) {
                lbl_1_common_bss_47674.menuCursor = 0;
            }
        } else if (buttons & INPUT_BUTTON_A) {
            if (lbl_1_common_bss_47674.menuCursor == 0) {
                item->func = fn_1_9AB0;
            } else {
                item->func = fn_1_88D0;
            }
        } else if (buttons & INPUT_BUTTON_B) {
            lbl_1_common_bss_47674.screen = 0;
            unregisterObjectByID(6);
            item->parent->state = 1;
        }
        break;
    }
}

// .text:0x00008B8C size:0x4
void fn_1_8B8C(void) {
    return;
}

// .text:0x00008A90 size:0xFC
void fn_1_8A90(void) {
    DebugMenuScene *item = (DebugMenuScene *)currentDrawingItem;
    u16 buttons = AtBat_ButtonInput1._02;

    if (buttons & INPUT_BUTTON_UP) {
        if (--lbl_1_common_bss_47674.menuCursor < 0) {
            lbl_1_common_bss_47674.menuCursor = 1;
        }
    } else if (buttons & INPUT_BUTTON_DOWN) {
        if (++lbl_1_common_bss_47674.menuCursor == 2) {
            lbl_1_common_bss_47674.menuCursor = 0;
        }
    } else if (buttons & INPUT_BUTTON_A) {
        if (lbl_1_common_bss_47674.menuCursor == 0) {
            item->func = fn_1_9AB0;
        } else {
            item->func = fn_1_88D0;
        }
    } else if (buttons & INPUT_BUTTON_B) {
        lbl_1_common_bss_47674.screen = 0;
        unregisterObjectByID(6);
        item->parent->state = 1;
    }
}

// .text:0x000088D0 size:0x1C0
void fn_1_88D0(void) {
    u16 buttons;

    switch (lbl_1_common_bss_47674.phase) {
    case 0:
        if (diskReadRelated(skyPanoramaFileDescriptorDebug, 6)) {
            lbl_1_common_bss_47674.pageDirty = 0;
            lbl_1_common_bss_47674.prevPage = 3;
            lbl_1_common_bss_47674.phase++;
        }
        break;
    case 1:
        buttons = AtBat_ButtonInput1._02;
        if (buttons & INPUT_BUTTON_UP) {
            if (--lbl_1_common_bss_47674.pageCursor < 0) {
                lbl_1_common_bss_47674.pageCursor = 2;
            }
        } else if (buttons & INPUT_BUTTON_DOWN) {
            if (++lbl_1_common_bss_47674.pageCursor == 3) {
                lbl_1_common_bss_47674.pageCursor = 0;
            }
        } else if (buttons & INPUT_BUTTON_A) {
            if (lbl_1_common_bss_47674.pageShown == 0) {
                lbl_1_common_bss_47674.pageDirty = 1;
                lbl_1_common_bss_47674.pageShown = 1;
            } else {
                lbl_1_common_bss_47674.pageDirty = 2;
            }
            fn_1_86E4();
        } else if (buttons & INPUT_BUTTON_B) {
            lbl_1_common_bss_47674.phase = 0;
            currentDrawingItem->func = fn_1_8B90;
        }
        break;
    }
}

// .text:0x000088CC size:0x4
void fn_1_88CC(void) {
    return;
}

// .text:0x00008770 size:0x15C
void fn_1_8770(void) {
    u16 buttons = AtBat_ButtonInput1._02;

    if (buttons & INPUT_BUTTON_UP) {
        if (--lbl_1_common_bss_47674.pageCursor < 0) {
            lbl_1_common_bss_47674.pageCursor = 2;
        }
    } else if (buttons & INPUT_BUTTON_DOWN) {
        if (++lbl_1_common_bss_47674.pageCursor == 3) {
            lbl_1_common_bss_47674.pageCursor = 0;
        }
    } else if (buttons & INPUT_BUTTON_A) {
        if (lbl_1_common_bss_47674.pageShown == 0) {
            lbl_1_common_bss_47674.pageDirty = 1;
            lbl_1_common_bss_47674.pageShown = 1;
        } else {
            lbl_1_common_bss_47674.pageDirty = 2;
        }
        fn_1_86E4();
    } else if (buttons & INPUT_BUTTON_B) {
        lbl_1_common_bss_47674.phase = 0;
        currentDrawingItem->func = fn_1_8B90;
    }
}

// .text:0x000086E4 size:0x8C
void fn_1_86E4(void) {
    if (lbl_1_common_bss_47674.pageDirty == 0) {
        return;
    }
    switch (lbl_1_common_bss_47674.pageCursor) {
    case 0:
        if (lbl_1_common_bss_47674.page == lbl_1_common_bss_47674.prevPage) {
            return;
        }
        lbl_1_common_bss_47674.prevPage = lbl_1_common_bss_47674.page;
        lbl_1_common_bss_47674.page = 0;
        break;
    case 1:
        lbl_1_common_bss_47674.prevPage = lbl_1_common_bss_47674.page;
        lbl_1_common_bss_47674.page = 1;
        break;
    case 2:
        lbl_1_common_bss_47674.prevPage = lbl_1_common_bss_47674.page;
        lbl_1_common_bss_47674.page = 2;
        break;
    }
    lbl_1_common_bss_47674.pageDirty = 0;
}

// .text:0x000086BC size:0x28
void fn_1_86BC(void) {
    ((DebugMenuScene *)currentDrawingItem)->timer = 0;
    currentDrawingItem->func = fn_1_8624;
}

// .text:0x00008624 size:0x98
void fn_1_8624(void) {
    DebugMenuScene *item = (DebugMenuScene *)currentDrawingItem;

    if (AtBat_ButtonInput1._02 & INPUT_BUTTON_A) {
        SCENE_REC(item, 0)->frame = 0;
        item->timer = 0;
    }
    if (lbl_1_common_bss_47674.page != 0 || lbl_1_common_bss_47674.phase == 0) {
        removeGraphicsElementFromScene((DrawingSceneStruct *)item);
        removeCurrentDrawingItem();
    }
    item->timer++;
}
