#include "menus/text_8782C.h"
#include "menus/debug_menu_text.h"
#include "game/match_setup/match_loading.h"
#include "menus/rep_0DE0.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x800363d8.h"
#include "Unknown/File_0x80034e20.h"
#include "static/UnknownHomes_Static.h"
#include "C3/geoPalette/geoPalette.h"
#include "C3/actor/act.h"
#include "Unknown/File_0x800c0770.h"
#include "text/text.h"
#include "Unknown/orderchange.h"
#include "Unknown/File_0x800204cc.h"
#include "Unknown/File_0x80034cec.h"
#include "Unknown/File_0x800b0a14.h"

extern u8 lbl_2_bss_33FBCC[];
extern u8 *lbl_2_bss_3401BC;
extern u8 superstarUnlocked[];
extern u8 menuCursors[];
extern u8 lbl_2_bss_34009C[];
extern u8 lbl_80354768[];
extern u8 menuNumber[];

DebugMenuText lbl_2_data_2E9F8 = {
    { "BAT FIRST", "BAT LAST" },
    "FL",
    "PC",
    { "RR", "RL", "LR", "LL" },
    { "OFF", "ON" },
    { "SELECT DEBUG MENU", "HIDE CHARA SET", "STAR PLAYER SET", "KOOPA STA FLAG SET", "CHALLE LEVEL FREE SET" },
    { "1P >", "COM1>", "2P >", "COM2>", "3P >", "COM3>", "4P >", "COM4>" },
    { 0x0000FF0F, 0x0000880F, 0x00000FFF, 0x0000088F, 0x0000F0FF, 0x0000808F, 0x0000F00F, 0x0000800F },
    { 0, 4, 10, 6, 2, 9, 1, 5, 11, 17, 3, 19 },
    { 0, 2, 6, 8, 4, 10, 1, 3, 7, 5, 9, 11 },
    { 0, 0, 6, 2, 8, 4, 10, 5, 11, 3, 9, 1, 7, 0, 0, 0 },
};

u8 lbl_2_data_2ECBC[0x28] = {
    2, 5, 4, 3, 8, 3, 4, 5, 2, 6,
    0, 1, 8, 6, 7, 1, 2, 0, 7, 4,
    4, 3, 1, 2, 5, 1, 2, 4, 6, 8,
    7, 6, 8, 5, 3, 3, 5, 7, 4, 6,
};

static UIRecordDescriptor lbl_2_data_2ECE4[70] = {
    { 0, 14, { 0 }, 0xFFFFFFFF, 1, 20, UI_NO_PARENT, 8, { 0 }, 1, 0 },
    { 0, 15, { 0 }, 0xFFFFFFFF, 1, 19, 0, 8, { 0 }, 1, 2 },
    { 0, 15, { 0 }, 0xFFFFFFFF, 1, 19, 0, 8, { 0 }, 1, 1 },
    { 0, 15, { 0 }, 0xFFFFFFFF, 1, 19, 0, 8, { 0 }, 1, 0 },
    { 0, 17, { 0 }, 0xFFFFFFFF, 1, 7, 0, 8, { 0 }, 1, 2 },
    { 0, 17, { 0 }, 0xFFFFFFFF, 1, 7, 0, 8, { 0 }, 1, 1 },
    { 0, 17, { 0 }, 0xFFFFFFFF, 1, 7, 0, 8, { 0 }, 1, 0 },
    { 0, 18, { 0 }, 0xFFFFFFFF, 1, 8, 0, 8, { 0 }, 1, 2 },
    { 0, 18, { 0 }, 0xFFFFFFFF, 1, 8, 0, 8, { 0 }, 1, 1 },
    { 0, 18, { 0 }, 0xFFFFFFFF, 1, 8, 0, 8, { 0 }, 1, 0 },
    { 0, 11, { 0 }, 0xFFFFFFFF, 1, 20, UI_NO_PARENT, 8, { 0 }, 1, 0 },
    { 0, 12, { 0 }, 0xFFFFFFFF, 1, 8, 10, 8, { 0 }, 1, 5 },
    { 0, 12, { 0 }, 0xFFFFFFFF, 1, 8, 10, 8, { 0 }, 1, 4 },
    { 0, 12, { 0 }, 0xFFFFFFFF, 1, 8, 10, 8, { 0 }, 1, 3 },
    { 0, 10, { 0 }, 0xFFFFFFFF, 1, 7, 1, 8, { 0 }, 1, 2 },
    { 0, 10, { 0 }, 0xFFFFFFFF, 1, 7, 1, 8, { 0 }, 1, 3 },
    { 0, 10, { 0 }, 0xFFFFFFFF, 1, 7, 1, 8, { 0 }, 1, 4 },
    { 0, 10, { 0 }, 0xFFFFFFFF, 1, 7, 2, 8, { 0 }, 1, 2 },
    { 0, 10, { 0 }, 0xFFFFFFFF, 1, 7, 2, 8, { 0 }, 1, 3 },
    { 0, 10, { 0 }, 0xFFFFFFFF, 1, 7, 2, 8, { 0 }, 1, 4 },
    { 0, 10, { 0 }, 0xFFFFFFFF, 1, 7, 3, 8, { 0 }, 1, 2 },
    { 0, 10, { 0 }, 0xFFFFFFFF, 1, 7, 3, 8, { 0 }, 1, 3 },
    { 0, 10, { 0 }, 0xFFFFFFFF, 1, 7, 3, 8, { 0 }, 1, 4 },
    { 0, 22, { 0 }, 0xFFFFFFFF, 1, 7, 1, 8, { 0 }, 1, 1 },
    { 0, 22, { 0 }, 0xFFFFFFFF, 1, 7, 2, 8, { 0 }, 1, 1 },
    { 0, 22, { 0 }, 0xFFFFFFFF, 1, 7, 3, 8, { 0 }, 1, 1 },
    { 0, 131, { 0 }, 0xFFFFFFFF, 0, 7, 23, 1, { 0 }, 1, 0 },
    { 0, 131, { 0 }, 0xFFFFFFFF, 0, 7, 23, 1, { 0 }, 1, 1 },
    { 0, 131, { 0 }, 0xFFFFFFFF, 0, 7, 23, 1, { 0 }, 1, 2 },
    { 0, 131, { 0 }, 0xFFFFFFFF, 0, 7, 23, 1, { 0 }, 1, 3 },
    { 0, 131, { 0 }, 0xFFFFFFFF, 0, 7, 23, 1, { 0 }, 1, 4 },
    { 0, 131, { 0 }, 0xFFFFFFFF, 0, 7, 23, 1, { 0 }, 1, 5 },
    { 0, 131, { 0 }, 0xFFFFFFFF, 0, 7, 23, 1, { 0 }, 1, 6 },
    { 0, 131, { 0 }, 0xFFFFFFFF, 0, 7, 23, 1, { 0 }, 1, 7 },
    { 0, 131, { 0 }, 0xFFFFFFFF, 0, 7, 24, 1, { 0 }, 1, 0 },
    { 0, 131, { 0 }, 0xFFFFFFFF, 0, 7, 24, 1, { 0 }, 1, 1 },
    { 0, 131, { 0 }, 0xFFFFFFFF, 0, 7, 24, 1, { 0 }, 1, 2 },
    { 0, 131, { 0 }, 0xFFFFFFFF, 0, 7, 24, 1, { 0 }, 1, 3 },
    { 0, 131, { 0 }, 0xFFFFFFFF, 0, 7, 24, 1, { 0 }, 1, 4 },
    { 0, 131, { 0 }, 0xFFFFFFFF, 0, 7, 24, 1, { 0 }, 1, 5 },
    { 0, 131, { 0 }, 0xFFFFFFFF, 0, 7, 24, 1, { 0 }, 1, 6 },
    { 0, 131, { 0 }, 0xFFFFFFFF, 0, 7, 24, 1, { 0 }, 1, 7 },
    { 0, 131, { 0 }, 0xFFFFFFFF, 0, 7, 25, 1, { 0 }, 1, 0 },
    { 0, 131, { 0 }, 0xFFFFFFFF, 0, 7, 25, 1, { 0 }, 1, 1 },
    { 0, 131, { 0 }, 0xFFFFFFFF, 0, 7, 25, 1, { 0 }, 1, 2 },
    { 0, 131, { 0 }, 0xFFFFFFFF, 0, 7, 25, 1, { 0 }, 1, 3 },
    { 0, 131, { 0 }, 0xFFFFFFFF, 0, 7, 25, 1, { 0 }, 1, 4 },
    { 0, 131, { 0 }, 0xFFFFFFFF, 0, 7, 25, 1, { 0 }, 1, 5 },
    { 0, 131, { 0 }, 0xFFFFFFFF, 0, 7, 25, 1, { 0 }, 1, 6 },
    { 0, 131, { 0 }, 0xFFFFFFFF, 0, 7, 25, 1, { 0 }, 1, 7 },
    { 0, 23, { 0 }, 0xFFFFFFFF, 1, 7, 1, 8, { 0 }, 1, 5 },
    { 0, 23, { 0 }, 0xFFFFFFFF, 1, 7, 2, 8, { 0 }, 1, 5 },
    { 0, 23, { 0 }, 0xFFFFFFFF, 1, 7, 3, 8, { 0 }, 1, 5 },
    { 0, 25, { 0 }, 0xFFFFFFFF, 0, 7, 1, 8, { 0 }, 1, 6 },
    { 0, 25, { 0 }, 0xFFFFFFFF, 0, 7, 2, 8, { 0 }, 1, 6 },
    { 0, 25, { 0 }, 0xFFFFFFFF, 0, 7, 3, 8, { 0 }, 1, 6 },
    { 0, 8, { 0 }, 0xFFFFFFFF, 1, 7, 1, 8, { 0 }, 1, 7 },
    { 0, 8, { 0 }, 0xFFFFFFFF, 1, 7, 2, 8, { 0 }, 1, 7 },
    { 0, 8, { 0 }, 0xFFFFFFFF, 1, 7, 3, 8, { 0 }, 1, 7 },
    { 0, 7, { 0 }, 0xFFFFFFFF, 2, 7, 1, 8, { 0 }, 1, 8 },
    { 0, 7, { 0 }, 0xFFFFFFFF, 2, 7, 2, 8, { 0 }, 1, 8 },
    { 0, 7, { 0 }, 0xFFFFFFFF, 2, 7, 3, 8, { 0 }, 1, 8 },
    { 0, 2, { 0 }, 0xFFFFFFFF, 1, 20, UI_NO_PARENT, 8, { 0 }, 1, 0 },
    { 0, 3, { 0 }, 0xFFFFFFFF, 1, 7, 62, 8, { 0 }, 1, 2 },
    { 0, 3, { 0 }, 0xFFFFFFFF, 1, 7, 62, 8, { 0 }, 1, 1 },
    { 0, 3, { 0 }, 0xFFFFFFFF, 1, 7, 62, 8, { 0 }, 1, 0 },
    { 0, 0, { 0 }, 0xFFFFFFFF, 2, 7, 1, 8, { 0 }, 1, 0 },
    { 0, 0, { 0 }, 0xFFFFFFFF, 2, 7, 2, 8, { 0 }, 1, 0 },
    { 0, 0, { 0 }, 0xFFFFFFFF, 2, 7, 3, 8, { 0 }, 1, 0 },
    { UI_DESC_END, 0, { 0 }, 0x00000000, 0, 0, 0, 0, { 0 }, 0, 0 },
};

static UIRecordDescriptor lbl_2_data_2F5A4[9] = {
    { 0, 209, { 0 }, 0xFFFFFFFF, 1, 2, UI_NO_PARENT, 1, { 0 }, 1, 0 },
    { 0, 216, { 0 }, 0xFFFFFFFF, 1, 2, UI_NO_PARENT, 1, { 0 }, 1, 0 },
    { 0, 192, { 0 }, 0xFFFFFFFF, 1, 2, 1, 1, { 0 }, 1, 0 },
    { 0, 206, { 0 }, 0xFFFFFFFF, 1, 2, 1, 1, { 0 }, 1, 5 },
    { 0, 206, { 0 }, 0xFFFFFFFF, 1, 2, 1, 1, { 0 }, 1, 4 },
    { 0, 206, { 0 }, 0xFFFFFFFF, 1, 2, 1, 1, { 0 }, 1, 3 },
    { 0, 206, { 0 }, 0xFFFFFFFF, 1, 2, 1, 1, { 0 }, 1, 2 },
    { 0, 206, { 0 }, 0xFFFFFFFF, 1, 2, 1, 1, { 0 }, 1, 1 },
    { UI_DESC_END, 0, { 0 }, 0x00000000, 0, 0, 0, 0, { 0 }, 0, 0 },
};

static UIRecordDescriptor lbl_2_data_2F6C4[8] = {
    { 0, 209, { 0 }, 0xFFFFFFFF, 1, 2, UI_NO_PARENT, 1, { 0 }, 1, 0 },
    { 0, 215, { 0 }, 0xFFFFFFFF, 1, 2, UI_NO_PARENT, 1, { 0 }, 1, 0 },
    { 0, 192, { 0 }, 0xFFFFFFFF, 1, 2, 1, 1, { 0 }, 1, 0 },
    { 0, 206, { 0 }, 0xFFFFFFFF, 1, 2, 1, 1, { 0 }, 1, 4 },
    { 0, 206, { 0 }, 0xFFFFFFFF, 1, 2, 1, 1, { 0 }, 1, 3 },
    { 0, 206, { 0 }, 0xFFFFFFFF, 1, 2, 1, 1, { 0 }, 1, 2 },
    { 0, 206, { 0 }, 0xFFFFFFFF, 1, 2, 1, 1, { 0 }, 1, 1 },
    { UI_DESC_END, 0, { 0 }, 0x00000000, 0, 0, 0, 0, { 0 }, 0, 0 },
};

static UIRecordDescriptor lbl_2_data_2F7C4[6] = {
    { 0, 209, { 0 }, 0xFFFFFFFF, 1, 2, UI_NO_PARENT, 1, { 0 }, 1, 0 },
    { 0, 214, { 0 }, 0xFFFFFFFF, 1, 2, UI_NO_PARENT, 1, { 0 }, 1, 0 },
    { 0, 191, { 0 }, 0xFFFFFFFF, 1, 2, 1, 1, { 0 }, 1, 0 },
    { 0, 206, { 0 }, 0xFFFFFFFF, 1, 2, 1, 1, { 0 }, 1, 2 },
    { 0, 206, { 0 }, 0xFFFFFFFF, 1, 2, 1, 1, { 0 }, 1, 1 },
    { UI_DESC_END, 0, { 0 }, 0x00000000, 0, 0, 0, 0, { 0 }, 0, 0 },
};

char lbl_2_data_2F884[6][0x20] = {
    "FIRST", "CONTINUE", "STRONG FIRST", "COPY", "DELETE", "CANCEL"
};

MatchFileDescriptor ChallengeMapSceneFiles[2] = {
    { 0x0000040B, 0x400B2CB8, 0x18E3F000, 0x00053454 },
    { 0x0000040B, 0x4037CF5C, 0x18B3A800, 0x00208AF0 },
};

E(u8, CHAR_ID) lbl_2_data_2F964[6] = {
    CHAR_ID_MARIO, CHAR_ID_PEACH, CHAR_ID_WARIO, CHAR_ID_DK, CHAR_ID_YOSHI, CHAR_ID_BOWSER
};

typedef struct ModelSlot {
    /* 0x0 */ void *layout;
    /* 0x4 */ void *geo;
    /* 0x8 */ void *tex;
} ModelSlot;

static inline BOOL isEqual(s32 a, s32 b) {
    return a == b ? TRUE : FALSE;
}

static inline UIRecord *sceneRecord(DrawingSceneStruct *node, s32 idx) {
    return (UIRecord *)graphicsRelatedArray[((MenuScene *)node)->firstHandle + idx].object;
}

#define REC_OBJ(idx) ((UIRecord *)graphicsRelatedArray[((MenuScene *)node)->firstHandle + (idx)].object)

// .text:0x0008ACDC size:0x4 mapped:0x806C9D70
void fn_2_8ACDC(void) {
    return;
}

// .text:0x0008ACB0 size:0x2C mapped:0x806C9D44
void fn_2_8ACB0(s32 slot, s32 flag) {
    Rep0DERec28 *rec;

    if (lbl_2_bss_340140->unk2D94 != NULL) {
        return;
    }
    rec = &lbl_2_bss_340140->unk2D94[slot];
    if (rec == NULL) {
        return;
    }
    rec->unk26 = flag;
}

// .text:0x0008AC84 size:0x2C mapped:0x806C9D18
void fn_2_8AC84(s32 slot, s32 flag) {
    if (lbl_2_bss_340140->unk2D94 == NULL) {
        return;
    }
    lbl_2_bss_3401BC[slot + 0x50] = flag;
}

// .text:0x0008ABFC size:0x88 mapped:0x806C9C90
static inline void setupScene(DrawingSceneStruct *node) {
    addGraphicsElementToScene(node, lbl_2_data_2ECE4);
    fn_2_8A008(node);
}

void fn_2_8ABFC(void) {
    setupScene(currentDrawingItem);
    if (*(u8 *)((u8 *)&Static_Stats_Tables + 0x4756) == 1) {
        *(s32 *)(menuCursors + 0x50) = superstarUnlocked[0xF6];
    }
    currentDrawingItem->func = fn_2_8A824;
}

// .text:0x0008A824 size:0x3D8 mapped:0x806C98B8
void fn_2_8A824(void) {
    u8 *lbl = lbl_2_bss_33FBCC;
    DrawingSceneStruct *node = currentDrawingItem;
    s32 i;
    s32 k;
    s32 count;
    s32 total;

    switch (lbl[0x17]) {
    case 0x49:
        fn_2_89038(node);
        break;
    case 0x4A:
        fn_2_88D90(node);
        break;
    case 0x4B:
        fn_2_887F8(node);
        break;
    case 0x4C:
        fn_2_883C8(node);
        break;
    case 0x4D:
        fn_2_88250(node);
        break;
    case 0x4E:
        fn_2_87FB0(node);
        break;
    case 0x4F:
        fn_2_87998(node);
        break;
    case 0x50:
        if (isEqual(lbl_2_bss_33FBCC[0x18], 0)) {
            fn_2_8A008(node);
            lbl_2_bss_33FBCC[0x18] = 1;
            lbl_2_bss_33FBCC[0x19] = 1;
        }
        if (isEqual(lbl_2_bss_33FBCC[0x19], 1)) {
            count = 0;
            total = 0;
            for (i = 0; i < 3; i++) {
                if (lbl_80354768[0xCF5E + i] != 0) {
                    if ((s8)lbl_80354768[i * 0x4508 + 0x444B] != -1) {
                        total++;
                        count += maybeCheckAndResetGrapicsElement((MenuScene *)node, i + 0x32, 10) != 0;
                    } else if ((s8)lbl_80354768[i * 0x4508 + 0x1606] == 0) {
                        total++;
                        count += maybeCheckAndResetGrapicsElement((MenuScene *)node, i + 0x35, 0xE) != 0;
                    }
                }
            }
            if (count == total) {
                lbl_2_bss_33FBCC[0x17] = 0;
                lbl_2_bss_33FBCC[0x18] = 0;
                lbl_2_bss_33FBCC[0x19] = 0;
            }
        }
        break;
    }

    for (k = 0; k < 3; k++) {
        if (*(s32 *)(menuCursors + 0x50) == k) {
            sceneRecord(node, k + 0x3F)->flags |= 2;
        } else {
            sceneRecord(node, k + 0x3F)->flags &= ~2;
        }
    }

    if (lbl[0x1A] != 0) {
        lbl[0x1A] = 0;
        lbl[0x17] = 0;
        lbl[0x18] = 0;
        lbl[0x19] = 0;
        removeGraphicsElementFromScene(node);
        removeCurrentDrawingItem();
        *(u8 *)(menuNumber + 3) = 0;
    }
}

// .text:0x0008A008 size:0x81C mapped:0x806C909C
void fn_2_8A008(DrawingSceneStruct *node) {
    u8 *table;
    u8 *menuSel;
    s32 i;
    s32 j;
    s32 sel;
    s32 writes;
    s32 v;

    for (i = 0; i < 3; i++) {
        table = lbl_80354768 + i * 0x4508;

        if (lbl_80354768[i + 0xCF5E] != 0) {
            REC_OBJ(i + 4)->elementIndex = 0x11;
            load_Icon(node, i + 0x38, 1, 5, i);

            if (table[0x1606] != 0 && table[0x441B] == 0) {
                REC_OBJ(i + 0x3B)->flags |= UI_FLAG_VISIBLE;
                load_Icon(node, i + 0x3B, 1, 4, table[0x4416]);
                REC_OBJ(i + 0x3B)->frame = 0;
                REC_OBJ(i + 0x3B)->playMode = UI_PLAY_FORWARD;
                load_Icon(node, i + 4, 1, 6, table[0x4416]);
                REC_OBJ(i + 0xB)->flags &= ~3;
                REC_OBJ(i + 0x17)->flags &= ~3;
                REC_OBJ(i + 0x32)->flags &= ~3;
                REC_OBJ(i + 0x35)->flags &= ~3;
            } else {
                REC_OBJ(i + 0x3B)->flags &= ~3;
                REC_OBJ(i + 0xB)->flags |= UI_FLAG_VISIBLE;
                REC_OBJ(i + 0x17)->flags |= UI_FLAG_VISIBLE;
                REC_OBJ(i + 0x38)->flags |= UI_FLAG_VISIBLE;
                REC_OBJ(i + 0x32)->flags |= UI_FLAG_VISIBLE;
                REC_OBJ(i + 0x35)->flags |= UI_FLAG_VISIBLE;
                REC_OBJ(3 * i + 0xE)->flags |= UI_FLAG_VISIBLE;
                REC_OBJ(3 * i + 0xF)->flags |= UI_FLAG_VISIBLE;
                REC_OBJ(3 * i + 0x10)->flags |= UI_FLAG_VISIBLE;

                menuSel = lbl_2_data_2F964;
                sel = 0;
                for (j = 0; j < 6; j++) {
                    if (menuSel[j] == table[0x441D]) {
                        sel = j;
                    }
                }
                REC_OBJ(i + 0xB)->frame = 0;
                load_Icon(node, i + 0xB, 1, 0x54, sel);
                REC_OBJ(i + 0xB)->rgba |= 0xFF;
                REC_OBJ(i + 0xB)->playMode = UI_PLAY_FORWARD;

                if ((s8)table[0x444B] != -1) {
                    REC_OBJ(i + 0x32)->flags |= UI_FLAG_VISIBLE;
                    REC_OBJ(i + 0x32)->frame = 0;
                    load_Icon(node, i + 0x32, 4, 0x64, (s8)table[0x444B]);
                    REC_OBJ(i + 0x32)->playMode = UI_PLAY_FORWARD;
                    REC_OBJ(i + 0x35)->flags &= ~3;
                    REC_OBJ(i + 0x35)->playMode = UI_PLAY_STOP;
                } else {
                    REC_OBJ(i + 0x35)->flags |= UI_FLAG_VISIBLE;
                    REC_OBJ(i + 0x35)->playMode = UI_PLAY_FORWARD;
                    REC_OBJ(i + 0x32)->flags &= ~3;
                }
                load_Icon(node, i + 4, 1, 6, table[0x4415]);

                writes = 0;
                for (j = 0; j < 9; j++) {
                    v = *(s16 *)(table + 0x40B8 + 6 * j);
                    if (v != table[0x441D]) {
                        REC_OBJ(8 * i + writes + 0x1A)->frame = (u32)v << 16;
                        writes++;
                    }
                }
            }
        } else {
            REC_OBJ(i + 4)->elementIndex = 1;
            REC_OBJ(i + 4)->frame = 0;
            REC_OBJ(i + 4)->playMode = UI_PLAY_FORWARD;
            load_Icon(node, i + 4, 1, 6, 4);
            REC_OBJ(i + 0xB)->flags &= ~3;
            REC_OBJ(i + 0x17)->flags &= ~3;
            REC_OBJ(i + 0x38)->flags &= ~3;
            REC_OBJ(i + 0x32)->flags &= ~3;
            REC_OBJ(i + 0x35)->flags &= ~3;
            REC_OBJ(i + 0x3B)->flags &= ~3;
            REC_OBJ(3 * i + 0xE)->flags &= ~3;
            REC_OBJ(3 * i + 0xF)->flags &= ~3;
            REC_OBJ(3 * i + 0x10)->flags &= ~3;
        }

        if (*(s32 *)(menuCursors + 0x50) == i) {
            REC_OBJ(i + 0x3F)->flags |= UI_FLAG_VISIBLE;
        } else {
            REC_OBJ(i + 0x3F)->flags &= ~3;
        }
    }
}

// .text:0x00089F70 size:0x98 mapped:0x806C9004
void fn_2_89F70(void) {
    DrawingSceneStruct *cur = currentDrawingItem;
    const UIRecordDescriptor *desc;

    switch (lbl_2_bss_33FBCC[5]) {
    case 0:
        desc = lbl_2_data_2F7C4;
        break;
    case 1:
    case 2:
        desc = lbl_2_data_2F6C4;
        break;
    case 3:
        desc = lbl_2_data_2F5A4;
        break;
    }
    addGraphicsElementToScene(cur, desc);
    lbl_2_bss_33FBCC[0xE] = 0;
    currentDrawingItem->func = fn_2_8975C;
}

// .text:0x0008975C size:0x814 mapped:0x806C87F0
void fn_2_8975C(void) {
    u8 *lbl = lbl_2_bss_33FBCC;
    DrawingSceneStruct *node = currentDrawingItem;
    s32 n = 0;
    s32 i;
    s32 k;
    s32 count = 0;
    s32 total = 0;
    s32 ret1;
    s32 ret2;

    switch (lbl[0x05]) {
    case 0:
        n = 2;
        break;
    case 1:
    case 2:
        n = 4;
        break;
    case 3:
        n = 5;
        break;
    }

    switch (lbl[0x22]) {
    case 0x51:

        if (lbl[0x20] == 0) {
            REC_OBJ(1)->playMode = UI_PLAY_FORWARD;
            switch (lbl[0x05]) {
            case 0:
                load_Icon(node, 3, 1, 0xCF, 0x13);
                load_Icon(node, 4, 1, 0xCF, 0x18);
                break;
            case 1:
                load_Icon(node, 3, 1, 0xCF, 0x14);
                load_Icon(node, 4, 1, 0xCF, 0x16);
                load_Icon(node, 5, 1, 0xCF, 0x17);
                load_Icon(node, 6, 1, 0xCF, 0x18);
                break;
            case 2:
                load_Icon(node, 3, 1, 0xCF, 0x15);
                load_Icon(node, 4, 1, 0xCF, 0x16);
                load_Icon(node, 5, 1, 0xCF, 0x17);
                load_Icon(node, 6, 1, 0xCF, 0x18);
                break;
            case 3:
                load_Icon(node, 3, 1, 0xCF, 0x14);
                load_Icon(node, 4, 1, 0xCF, 0x15);
                load_Icon(node, 5, 1, 0xCF, 0x16);
                load_Icon(node, 6, 1, 0xCF, 0x17);
                load_Icon(node, 7, 1, 0xCF, 0x18);
                break;
            }
            for (k = 0; k < n; k++) {
                REC_OBJ(k + 3)->playMode = UI_PLAY_FORWARD;
            }
            lbl[0x20] = 1;
            lbl[0x21] = 1;
        }
        if (lbl[0x21] != 0) {
            count = 0;
            total = 0;
            for (k = 0; k < n; k++) {
                if (k == 0) {
                    total++;
                    count += (maybeCheckAndResetGrapicsElement((MenuScene *)node, k + 3, 8) != 0);
                } else {
                    total++;
                    count += (maybeCheckAndResetGrapicsElement((MenuScene *)node, k + 3, 3) != 0);
                }
            }
            if (count == total) {
                lbl[0x20] = 0;
                lbl[0x21] = 0;
                lbl[0x22] = 0;
            }
        }
        break;
    case 0x52:

        if (lbl[0x20] == 0) {
            REC_OBJ(0)->playMode = UI_PLAY_BACKWARD;
            REC_OBJ(1)->playMode = UI_PLAY_BACKWARD;
            for (k = 0; k < n; k++) {
                REC_OBJ(k + 3)->frame = 0x30000;
                REC_OBJ(k + 3)->playMode = UI_PLAY_BACKWARD;
            }
            lbl[0x20] = 1;
            lbl[0x21] = 1;
        }
        if (lbl[0x21] != 0) {
            if (maybeCheckAndResetGrapicsElement((MenuScene *)node, 1, 0) != FALSE) {
                lbl[0x20] = 0;
                lbl[0x21] = 0;
                lbl[0x22] = 0;
            }
        }
        break;
    case 0x53:

        if (lbl[0x20] == 0) {
            ret1 = fn_2_895F8(0);
            ret2 = fn_2_895F8(1);
            REC_OBJ(ret1 + 3)->frame = 0x80000;
            REC_OBJ(ret1 + 3)->playMode = UI_PLAY_STOP;
            REC_OBJ(ret2 + 3)->frame = 0x30000;
            REC_OBJ(ret2 + 3)->playMode = UI_PLAY_STOP;
            lbl[0x20] = 1;
            lbl[0x21] = 1;
        }
        if (lbl[0x21] != 0) {
            fn_2_895F8(0);
            fn_2_895F8(1);
            lbl[0x20] = 0;
            lbl[0x21] = 0;
            lbl[0x22] = 0;
        }
        break;
    }

    if (lbl[0x0E] != 0 && lbl[0x21] == 0) {
        lbl[0x0E] = 0;
        removeGraphicsElementFromScene(node);
        removeCurrentDrawingItem();
    }
}

// .text:0x000895F8 size:0x164 mapped:0x806C868C
s32 fn_2_895F8(u8 useLocal) {
    s32 ret;
    u32 sel = *(u32 *)(menuCursors + 0x54);
    u32 alt = *(u32 *)(lbl_2_bss_33FBCC + 0x1C);

    if (useLocal) {
        sel = alt;
    }
    ret = 0;

    switch (lbl_2_bss_33FBCC[5]) {
    case 0:
        switch (sel) {
        case 0:
            ret = 0;
            break;
        case 5:
            ret = 1;
            break;
        }
        break;
    case 1:
        switch (sel) {
        case 1:
            ret = 0;
            break;
        case 3:
            ret = 1;
            break;
        case 4:
            ret = 2;
            break;
        case 5:
            ret = 3;
            break;
        }
        break;
    case 2:
        switch (sel) {
        case 2:
            ret = 0;
            break;
        case 3:
            ret = 1;
            break;
        case 4:
            ret = 2;
            break;
        case 5:
            ret = 3;
            break;
        }
        break;
    case 3:
        switch (sel) {
        case 1:
            ret = 0;
            break;
        case 2:
            ret = 1;
            break;
        case 3:
            ret = 2;
            break;
        case 4:
            ret = 3;
            break;
        case 5:
            ret = 4;
            break;
        }
        break;
    }
    return ret;
}

// .text:0x00089038 size:0x5C0 mapped:0x806C80CC
void fn_2_89038(DrawingSceneStruct *node) {
    u8 digits[3];
    s32 i;
    s32 j;
    s32 count;
    s32 total;

    if (isEqual(lbl_2_bss_33FBCC[0x18], 0)) {
        for (i = 0; i < 3; i++) {
            if (lbl_80354768[0xCF5E + i] != 0) {
                s16 value = *(s16 *)(lbl_80354768 + i * 0x4508 + 0x43BC);
                digits[0] = value / 100;
                digits[1] = (value - (s8)digits[0] * 100) / 10;
                digits[2] = value - digits[0] * 100 - digits[1] * 10;
                for (j = 0; j < 3; j++) {
                    sceneRecord(node, 3 * i + j + 0xE)->flags |= UI_FLAG_VISIBLE;
                    sceneRecord(node, 3 * i + j + 0xE)->frame = 0;
                    load_Icon(node, 0xE + 3 * i + j, 1, 0xD, (s8)digits[j]);
                    sceneRecord(node, 3 * i + j + 0xE)->playMode = UI_PLAY_FORWARD;
                }
                if (*(s32 *)(menuCursors + 0x50) == i) {
                    sceneRecord(node, i + 4)->playMode = UI_PLAY_FORWARD;
                    sceneRecord(node, i + 7)->elementIndex = 0x13;
                    sceneRecord(node, i + 7)->frame = 0;
                    sceneRecord(node, i + 7)->playMode = UI_PLAY_FORWARD;
                } else {
                    sceneRecord(node, i + 4)->playMode = UI_PLAY_FORWARD;
                    sceneRecord(node, i + 7)->elementIndex = 0x12;
                    sceneRecord(node, i + 7)->playMode = UI_PLAY_FORWARD;
                    if ((s8)lbl_80354768[i * 0x4508 + 0x1606] == 0 ||
                        ((s8)lbl_80354768[i * 0x4508 + 0x1606] != 0 && lbl_80354768[i * 0x4508 + 0x441B] != 0)) {
                        sceneRecord(node, i + 0xB)->frame = 0x1A0000;
                        sceneRecord(node, i + 0xB)->playMode = UI_PLAY_STOP;
                        if ((s8)lbl_80354768[i * 0x4508 + 0x444B] != -1) {
                            sceneRecord(node, i + 0x32)->flags |= UI_FLAG_VISIBLE;
                            sceneRecord(node, i + 0x32)->frame = 0;
                            load_Icon(node, i + 0x32, 4, 0x64, (s8)lbl_80354768[i * 0x4508 + 0x444B]);
                            sceneRecord(node, i + 0x32)->playMode = UI_PLAY_FORWARD;
                        } else {
                            sceneRecord(node, i + 0x35)->flags &= ~UI_FLAG_VISIBLE;
                            sceneRecord(node, i + 0x35)->playMode = UI_PLAY_STOP;
                            sceneRecord(node, i + 0x35)->flags |= UI_FLAG_VISIBLE;
                            sceneRecord(node, i + 0x35)->playMode = UI_PLAY_FORWARD;
                            sceneRecord(node, i + 0x32)->flags &= ~UI_FLAG_VISIBLE;
                        }
                    }
                }
            } else if (*(s32 *)(menuCursors + 0x50) == i) {
                sceneRecord(node, i + 7)->elementIndex = 0x13;
                sceneRecord(node, i + 7)->playMode = UI_PLAY_FORWARD;
            }
        }
        lbl_2_bss_33FBCC[0x18] = 1;
        lbl_2_bss_33FBCC[0x19] = 1;
    }

    if (isEqual(lbl_2_bss_33FBCC[0x19], 1)) {
        count = 0;
        total = 0;
        for (i = 0; i < 3; i++) {
            if (lbl_80354768[0xCF5E + i] != 0) {
                for (j = 0; j < 3; j++) {
                    total++;
                    count += maybeCheckAndResetGrapicsElement((MenuScene *)node, 0xE + 3 * i + j, 0x15) != 0;
                }
                if ((s8)lbl_80354768[i * 0x4508 + 0x1606] == 0 ||
                    ((s8)lbl_80354768[i * 0x4508 + 0x1606] != 0 && lbl_80354768[i * 0x4508 + 0x441B] != 0)) {
                    if (*(s32 *)(menuCursors + 0x50) == i) {
                        total++;
                        count += maybeCheckAndResetGrapicsElement((MenuScene *)node, i + 0xB, 0x15) != 0;
                    }
                    if ((s8)lbl_80354768[i * 0x4508 + 0x444B] != -1) {
                        total++;
                        count += maybeCheckAndResetGrapicsElement((MenuScene *)node, i + 0x32, 0xA) != 0;
                    } else {
                        total++;
                        count += maybeCheckAndResetGrapicsElement((MenuScene *)node, i + 0x35, 0xE) != 0;
                    }
                }
            }
        }
        if (count == total) {
            lbl_2_bss_33FBCC[0x18] = 0;
            lbl_2_bss_33FBCC[0x17] = 0;
            lbl_2_bss_33FBCC[0x19] = 0;
        }
    }
}

// .text:0x00088D90 size:0x2A8 mapped:0x806C7E24
void fn_2_88D90(DrawingSceneStruct *node) {
    s32 i;
    BOOL done;

    if (isEqual(lbl_2_bss_33FBCC[0x18], 0)) {
        sceneRecord(node, 0)->frame = 0x190000;
        sceneRecord(node, 0)->playMode = 4;
        for (i = 0; i < 3; i++) {
            sceneRecord(node, i + 4)->playMode = 4;
            if (lbl_80354768[0xCF5E + i] != 0) {
                sceneRecord(node, 3 * i + 0xE)->playMode = 4;
                sceneRecord(node, 3 * i + 0xF)->playMode = 4;
                sceneRecord(node, 3 * i + 0x10)->playMode = 4;
                sceneRecord(node, i + 0x38)->playMode = 4;
                if ((s8)lbl_80354768[i * 0x4508 + 0x1606] != 0 && lbl_80354768[i * 0x4508 + 0x441B] == 0) {
                    sceneRecord(node, i + 0x3B)->playMode = 4;
                } else {
                    sceneRecord(node, i + 0x17)->playMode = 4;
                    sceneRecord(node, i + 0xB)->frame = 0x160000;
                    sceneRecord(node, i + 0xB)->playMode = 4;
                    if ((s8)lbl_80354768[i * 0x4508 + 0x444B] != -1) {
                        sceneRecord(node, i + 0x32)->playMode = 4;
                    }
                }
            }
        }
        lbl_2_bss_33FBCC[0x18] = 1;
        lbl_2_bss_33FBCC[0x19] = 1;
    }

    if (isEqual(lbl_2_bss_33FBCC[0x19], 1)) {
        done = maybeCheckAndResetGrapicsElement((MenuScene *)node, 0, 0) != 0;
        if ((sceneRecord(node, 0)->frame >> 16) == 3) {
            changeScene(3, 6);
        }
        if (done == TRUE) {
            *(u8 *)((u8 *)&Static_Stats_Tables + 0x48AF) = 1;
            lbl_2_bss_33FBCC[0x1A] = 1;
            lbl_2_bss_33FBCC[0x17] = 0;
            lbl_2_bss_33FBCC[0x18] = 0;
            lbl_2_bss_33FBCC[0x19] = 0;
        }
    }
}

// .text:0x000887F8 size:0x598 mapped:0x806C788C
void fn_2_887F8(DrawingSceneStruct *node) {
    s32 digits[3];
    s32 i;
    s32 j;
    s32 count;
    s32 total;

    if (isEqual(lbl_2_bss_33FBCC[0x18], 0)) {
        fn_2_8A008(node);
        for (i = 0; i < 3; i++) {
            if (lbl_80354768[0xCF5E + i] != 0) {
                if (*(s32 *)(menuCursors + 0x50) == i) {
                    s16 value = *(s16 *)(lbl_80354768 + i * 0x4508 + 0x43BC);
                    s32 rem;
                    digits[0] = value / 100;
                    rem = value - digits[0] * 100;
                    digits[1] = rem / 10;
                    digits[2] = rem - digits[1] * 10;
                    for (j = 0; j < 3; j++) {
                        sceneRecord(node, 3 * i + j + 0xE)->flags |= UI_FLAG_VISIBLE;
                        sceneRecord(node, 3 * i + j + 0xE)->frame = 0;
                        load_Icon(node, 0xE + 3 * i + j, 1, 0xD, digits[j]);
                        sceneRecord(node, 3 * i + j + 0xE)->playMode = UI_PLAY_FORWARD;
                    }
                    sceneRecord(node, i + 4)->playMode = UI_PLAY_FORWARD;
                    sceneRecord(node, i + 7)->elementIndex = 0x13;
                    sceneRecord(node, i + 7)->frame = 0;
                    sceneRecord(node, i + 7)->playMode = UI_PLAY_FORWARD;
                } else {
                    sceneRecord(node, i + 4)->playMode = UI_PLAY_FORWARD;
                    sceneRecord(node, i + 7)->elementIndex = 0x12;
                    sceneRecord(node, i + 7)->playMode = UI_PLAY_FORWARD;
                    sceneRecord(node, i + 0xB)->frame = 0x1A0000;
                    sceneRecord(node, i + 0xB)->playMode = UI_PLAY_STOP;
                }
                if ((s8)lbl_80354768[i * 0x4508 + 0x444B] != -1) {
                    sceneRecord(node, i + 0x32)->flags |= UI_FLAG_VISIBLE;
                    sceneRecord(node, i + 0x32)->frame = 0;
                    load_Icon(node, i + 0x32, 4, 0x64, (s8)lbl_80354768[i * 0x4508 + 0x444B]);
                    sceneRecord(node, i + 0x32)->playMode = UI_PLAY_FORWARD;
                } else {
                    sceneRecord(node, i + 0x35)->flags &= ~UI_FLAG_VISIBLE;
                    sceneRecord(node, i + 0x35)->playMode = UI_PLAY_STOP;
                    sceneRecord(node, i + 0x35)->flags |= UI_FLAG_VISIBLE;
                    sceneRecord(node, i + 0x35)->playMode = UI_PLAY_FORWARD;
                    sceneRecord(node, i + 0x32)->flags &= ~UI_FLAG_VISIBLE;
                }
            }
        }
        sceneRecord(node, *(s32 *)(menuCursors + 0x50) + 7)->flags |= UI_FLAG_VISIBLE;
        sceneRecord(node, *(s32 *)(menuCursors + 0x50) + 7)->frame = 0;
        sceneRecord(node, *(s32 *)(menuCursors + 0x50) + 7)->playMode = UI_PLAY_FORWARD;
        sceneRecord(node, *(s32 *)(menuCursors + 0x50) + 4)->flags |= UI_FLAG_VISIBLE;
        lbl_2_bss_33FBCC[0x18] = 1;
        lbl_2_bss_33FBCC[0x19] = 1;
    }

    if (isEqual(lbl_2_bss_33FBCC[0x19], 1)) {
        count = 0;
        total = 0;
        for (i = 0; i < 3; i++) {
            if (lbl_80354768[0xCF5E + i] != 0) {
                if (*(s32 *)(menuCursors + 0x50) == i) {
                    for (j = 0; j < 3; j++) {
                        total++;
                        count += maybeCheckAndResetGrapicsElement((MenuScene *)node, 0xE + 3 * i + j, 0x15) != 0;
                    }
                }
                if ((s8)lbl_80354768[i * 0x4508 + 0x444B] != -1) {
                    total++;
                    count += maybeCheckAndResetGrapicsElement((MenuScene *)node, i + 0x32, 0xA) != 0;
                } else {
                    total++;
                    count += maybeCheckAndResetGrapicsElement((MenuScene *)node, i + 0x35, 0xE) != 0;
                }
            }
        }
        if (count == total) {
            lbl_2_bss_33FBCC[0x18] = 0;
            lbl_2_bss_33FBCC[0x17] = 0;
            lbl_2_bss_33FBCC[0x19] = 0;
        }
    }
}

// .text:0x000883C8 size:0x430 mapped:0x806C745C
void fn_2_883C8(DrawingSceneStruct *node) {
    u8 *lbl = lbl_2_bss_33FBCC;
    u8 *table;
    s32 i;
    s32 count = 0;
    s32 total = 0;

    if (lbl[0x18] == 0 && (s8)lbl[0x0D] != *(s32 *)(menuCursors + 0x50)) {
        table = lbl_80354768;
        for (i = 0; i < 3; i++) {
            if (table[i + 0xCF5E] != 0) {
                if (*(s32 *)(menuCursors + 0x50) == i) {
                    REC_OBJ(i + 4)->playMode = UI_PLAY_FORWARD;
                    REC_OBJ(i + 7)->elementIndex = 0x13;
                    REC_OBJ(i + 7)->playMode = UI_PLAY_FORWARD;
                    if (table[i * 0x4508 + 0x1606] == 0 || table[i * 0x4508 + 0x441B] != 0) {
                        REC_OBJ(i + 0xB)->frame = 0x1A0000;
                        REC_OBJ(i + 0xB)->playMode = UI_PLAY_BACKWARD;
                    }
                } else {
                    if ((s8)lbl[0x0D] == i && (s8)lbl[0x0F] != i) {
                        REC_OBJ(i + 4)->playMode = UI_PLAY_FORWARD;
                        REC_OBJ(i + 7)->elementIndex = 0x12;
                        REC_OBJ(i + 7)->playMode = UI_PLAY_FORWARD;
                        if (table[i * 0x4508 + 0x1606] == 0 || table[i * 0x4508 + 0x441B] != 0) {
                            REC_OBJ(i + 0xB)->frame = 0x160000;
                            REC_OBJ(i + 0xB)->playMode = UI_PLAY_FORWARD;
                        }
                    }
                }
            } else {
                if (*(s32 *)(menuCursors + 0x50) == i) {
                    REC_OBJ(i + 7)->elementIndex = 0x13;
                    REC_OBJ(i + 7)->playMode = UI_PLAY_FORWARD;
                } else {
                    REC_OBJ(i + 7)->elementIndex = 0x12;
                    REC_OBJ(i + 7)->playMode = UI_PLAY_FORWARD;
                }
            }
        }
        lbl[0x18] = 1;
        lbl[0x19] = 1;
    }

    if (lbl[0x19] == 1 && (s8)lbl[0x0D] != *(s32 *)(menuCursors + 0x50)) {
        table = lbl_80354768;
        for (i = 0; i < 3; i++) {
            if (table[i + 0xCF5E] != 0) {
                if (*(s32 *)(menuCursors + 0x50) == i) {
                    if (table[i * 0x4508 + 0x1606] == 0 || table[i * 0x4508 + 0x441B] != 0) {
                        total++;
                        count += (maybeCheckAndResetGrapicsElement((MenuScene *)node, i + 0xB, 0x16) != 0);
                    }
                } else if ((s8)lbl[0x0D] == i && (s8)lbl[0x0F] != i) {
                    if (table[i * 0x4508 + 0x1606] == 0 || table[i * 0x4508 + 0x441B] != 0) {
                        total++;
                        count += (maybeCheckAndResetGrapicsElement((MenuScene *)node, i + 0xB, 0x1A) != 0);
                    }
                }
            }
        }
        if (count == total) {
            lbl[0x0D] = (u8)*(s32 *)(menuCursors + 0x50);
            lbl[0x17] = 0;
            lbl[0x18] = 0;
            lbl[0x19] = 0;
        }
    }
}

// .text:0x00088250 size:0x178 mapped:0x806C72E4

void fn_2_88250(DrawingSceneStruct *node) {
    if (isEqual(lbl_2_bss_33FBCC[0x18], 0)) {
        sceneRecord(node, (s8)lbl_2_bss_33FBCC[0xF] + 7)->elementIndex = 0x14;
        sceneRecord(node, (s8)lbl_2_bss_33FBCC[0xF] + 7)->flags |= 2;
        sceneRecord(node, (s8)lbl_2_bss_33FBCC[0xF] + 7)->frame = 0;
        sceneRecord(node, (s8)lbl_2_bss_33FBCC[0xF] + 7)->playMode = 1;
        sceneRecord(node, *(s32 *)(menuCursors + 0x50) + 7)->elementIndex = 0x13;
        sceneRecord(node, *(s32 *)(menuCursors + 0x50) + 7)->playMode = 1;
        sceneRecord(node, (s8)lbl_2_bss_33FBCC[0xF] + 0x42)->flags |= 2;
        sceneRecord(node, (s8)lbl_2_bss_33FBCC[0xF] + 0x42)->playMode = 1;
        lbl_2_bss_33FBCC[0x18] = 1;
        lbl_2_bss_33FBCC[0x19] = 1;
    }
    if (isEqual(lbl_2_bss_33FBCC[0x19], 1)) {
        lbl_2_bss_33FBCC[0x17] = 0;
        lbl_2_bss_33FBCC[0x18] = 0;
        lbl_2_bss_33FBCC[0x19] = 0;
    }
}

// .text:0x00087FB0 size:0x2A0 mapped:0x806C7044
void fn_2_87FB0(DrawingSceneStruct *node) {
    s32 i;
    s32 count;
    s32 total;

    if (isEqual(lbl_2_bss_33FBCC[0x18], 0)) {
        fn_2_8A008(node);
        sceneRecord(node, (s8)lbl_2_bss_33FBCC[0x10] + 7)->elementIndex = 0x12;
        sceneRecord(node, (s8)lbl_2_bss_33FBCC[0x10] + 7)->frame = 0;
        sceneRecord(node, (s8)lbl_2_bss_33FBCC[0x10] + 7)->playMode = 1;
        sceneRecord(node, *(s32 *)(menuCursors + 0x50) + 7)->elementIndex = 0x12;
        sceneRecord(node, *(s32 *)(menuCursors + 0x50) + 7)->playMode = 1;
        sceneRecord(node, (s8)lbl_2_bss_33FBCC[0x10] + 4)->flags |= 2;
        sceneRecord(node, (s8)lbl_2_bss_33FBCC[0x10] + 0x42)->flags &= ~2;
        lbl_2_bss_33FBCC[0x18] = 1;
        lbl_2_bss_33FBCC[0xD] = lbl_2_bss_33FBCC[0x10];
        *(s32 *)(menuCursors + 0x50) = (s8)lbl_2_bss_33FBCC[0x10];
        lbl_2_bss_33FBCC[0x10] = -1;
        lbl_2_bss_33FBCC[0x19] = 1;
    }

    if (isEqual(lbl_2_bss_33FBCC[0x19], 1)) {
        count = 0;
        total = 0;
        for (i = 0; i < 3; i++) {
            if (lbl_80354768[0xCF5E + i] != 0) {
                if ((s8)lbl_80354768[i * 0x4508 + 0x444B] != -1) {
                    total++;
                    count += maybeCheckAndResetGrapicsElement((MenuScene *)node, i + 0x32, 10) != 0;
                } else if ((s8)lbl_80354768[i * 0x4508 + 0x1606] == 0) {
                    total++;
                    count += maybeCheckAndResetGrapicsElement((MenuScene *)node, i + 0x35, 0xE) != 0;
                }
            }
        }
        if (count == total) {
            sceneRecord(node, *(s32 *)(menuCursors + 0x50) + 7)->elementIndex = 0x13;
            sceneRecord(node, *(s32 *)(menuCursors + 0x50) + 7)->playMode = 1;
            lbl_2_bss_33FBCC[0x17] = 0;
            lbl_2_bss_33FBCC[0x18] = 0;
            lbl_2_bss_33FBCC[0x19] = 0;
        }
    }
}

// .text:0x00087998 size:0x618 mapped:0x806C6A2C
void fn_2_87998(DrawingSceneStruct *node) {
    u8 digits[3];
    s32 i;
    s32 j;
    s32 count;
    s32 total;

    if (isEqual(lbl_2_bss_33FBCC[0x18], 0)) {
        fn_2_8A008(node);
        for (i = 0; i < 3; i++) {
            if (lbl_80354768[0xCF5E + i] != 0) {
                if (*(s32 *)(menuCursors + 0x50) == i) {
                    s16 value;
                    s32 rem;
                    sceneRecord(node, i + 0x38)->flags |= UI_FLAG_VISIBLE;
                    load_Icon(node, i + 0x38, 1, 5, i);
                    value = *(s16 *)(lbl_80354768 + i * 0x4508 + 0x43BC);
                    digits[0] = value / 100;
                    rem = value - digits[0] * 100;
                    digits[1] = rem / 10;
                    digits[2] = rem - digits[1] * 10;
                    for (j = 0; j < 3; j++) {
                        sceneRecord(node, 3 * i + j + 0xE)->flags |= UI_FLAG_VISIBLE;
                        sceneRecord(node, 3 * i + j + 0xE)->frame = 0;
                        load_Icon(node, 0xE + 3 * i + j, 1, 0xD, digits[j]);
                        sceneRecord(node, 3 * i + j + 0xE)->playMode = UI_PLAY_FORWARD;
                    }
                    sceneRecord(node, i + 0xB)->frame = 0;
                    sceneRecord(node, i + 0xB)->playMode = UI_PLAY_FORWARD;
                    sceneRecord(node, i + 4)->playMode = UI_PLAY_FORWARD;
                    sceneRecord(node, i + 7)->elementIndex = 0x13;
                    sceneRecord(node, i + 7)->frame = 0;
                    sceneRecord(node, i + 7)->playMode = UI_PLAY_FORWARD;
                } else {
                    sceneRecord(node, i + 4)->playMode = UI_PLAY_FORWARD;
                    sceneRecord(node, i + 7)->elementIndex = 0x12;
                    sceneRecord(node, i + 7)->playMode = UI_PLAY_FORWARD;
                    sceneRecord(node, i + 0xB)->frame = 0x1A0000;
                    sceneRecord(node, i + 0xB)->playMode = UI_PLAY_STOP;
                }
                if (((s8)lbl_80354768[i * 0x4508 + 0x444B] == -1 && (s8)lbl_80354768[i * 0x4508 + 0x1606] == 0) ||
                    ((s8)lbl_80354768[i * 0x4508 + 0x444B] == -1 && (s8)lbl_80354768[i * 0x4508 + 0x1606] != 0 &&
                     lbl_80354768[i * 0x4508 + 0x441B] != 0)) {
                    sceneRecord(node, i + 0x35)->frame = 0;
                    sceneRecord(node, i + 0x35)->playMode = UI_PLAY_FORWARD;
                }
            }
        }
        sceneRecord(node, (s8)lbl_2_bss_33FBCC[0x10] + 7)->flags |= UI_FLAG_VISIBLE;
        sceneRecord(node, (s8)lbl_2_bss_33FBCC[0x10] + 7)->frame = 0;
        sceneRecord(node, (s8)lbl_2_bss_33FBCC[0x10] + 7)->playMode = UI_PLAY_FORWARD;
        sceneRecord(node, (s8)lbl_2_bss_33FBCC[0x10] + 4)->flags |= UI_FLAG_VISIBLE;
        sceneRecord(node, (s8)lbl_2_bss_33FBCC[0x10] + 0x42)->flags &= ~UI_FLAG_VISIBLE;
        lbl_2_bss_33FBCC[0x10] = -1;
        lbl_2_bss_33FBCC[0x18] = 1;
        lbl_2_bss_33FBCC[0x19] = 1;
    }

    if (isEqual(lbl_2_bss_33FBCC[0x19], 1)) {
        count = 0;
        total = 0;
        for (i = 0; i < 3; i++) {
            if (lbl_80354768[0xCF5E + i] != 0) {
                if (*(s32 *)(menuCursors + 0x50) == i) {
                    if ((s8)lbl_80354768[i * 0x4508 + 0x1606] == 0 ||
                        ((s8)lbl_80354768[i * 0x4508 + 0x1606] != 0 && lbl_80354768[i * 0x4508 + 0x441B] != 0)) {
                        total++;
                        count += maybeCheckAndResetGrapicsElement((MenuScene *)node, i + 0xB, 0x15) != 0;
                    }
                    for (j = 0; j < 3; j++) {
                        total++;
                        count += maybeCheckAndResetGrapicsElement((MenuScene *)node, 0xE + 3 * i + j, 0x15) != 0;
                    }
                }
                if ((s8)lbl_80354768[i * 0x4508 + 0x444B] != -1) {
                    total++;
                    count += maybeCheckAndResetGrapicsElement((MenuScene *)node, i + 0x32, 0xA) != 0;
                }
                if (((s8)lbl_80354768[i * 0x4508 + 0x444B] == -1 && (s8)lbl_80354768[i * 0x4508 + 0x1606] == 0) ||
                    ((s8)lbl_80354768[i * 0x4508 + 0x444B] == -1 && (s8)lbl_80354768[i * 0x4508 + 0x1606] != 0 &&
                     lbl_80354768[i * 0x4508 + 0x441B] != 0)) {
                    total++;
                    count += maybeCheckAndResetGrapicsElement((MenuScene *)node, i + 0x35, 0xE) != 0;
                }
            }
        }
        if (count == total) {
            lbl_2_bss_33FBCC[0x18] = 0;
            lbl_2_bss_33FBCC[0x17] = 0;
            lbl_2_bss_33FBCC[0x19] = 0;
        }
    }
}

// .text:0x0008782C size:0x16C mapped:0x806C68C0
void fn_2_8782C(void) {
    u32 *tbl;
    int i;
    void *layout;
    void *geo;
    void *tex;

    lbl_2_bss_340140->unk3078 = 0;
    tbl = *(u32 **)((u8 *)lbl_2_bss_340140 + 0x2D9C);
    for (i = 0; i < 15; i++) {
        *(u32 *)((u8 *)lbl_2_bss_340140 + 0x2DA0 + i * 4) = (u32)tbl + tbl[i];
    }
    i++;
    *(u32 *)(lbl_2_bss_34009C + 0x64) = (u32)tbl + tbl[i];
    i++;
    *(u32 *)(lbl_2_bss_34009C + 0x68) = (u32)tbl + tbl[i];

    for (i = 0; i < 5; i++) {
        layout = ((ModelSlot *)lbl_2_bss_340140->unk2DA0)[i].layout;
        geo = ((ModelSlot *)lbl_2_bss_340140->unk2DA0)[i].geo;
        tex = ((ModelSlot *)lbl_2_bss_340140->unk2DA0)[i].tex;
        LoadActorLayout(layout);
        convertGeometryAndSknHeader(geo, NULL);
        haveActLayoutPointToGeoHeader(layout, geo);
        convertTextureHeader(tex);
        UpdateTexturePalettePointers(geo, tex);
    }
    convertTextureHeader(*(void **)(lbl_2_bss_34009C + 0x64));
    convertTextureHeader(*(void **)(lbl_2_bss_34009C + 0x68));
}
