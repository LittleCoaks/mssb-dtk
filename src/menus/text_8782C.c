#include "menus/text_8782C.h"
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
extern u8 lbl_2_data_2E9F8[];
extern u8 lbl_2_data_2ECE4[];
extern u8 *lbl_2_bss_3401BC;
extern u8 superstarUnlocked[];
extern u8 menuCursors[];
extern u8 lbl_2_bss_34009C[];
extern u8 lbl_80354768[];
extern u8 lbl_2_data_2F964[];
extern u8 menuNumber[];

#undef REC_OBJ



#undef REC_OBJ

#undef REC_OBJ


#undef REC_OBJ


#undef REC_OBJ


#undef REC_OBJ

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
void fn_2_8ABFC(void) {
    DrawingSceneStruct *cur = currentDrawingItem;

    addGraphicsElementToScene(cur, (const UIRecordDescriptor *)lbl_2_data_2ECE4);
    fn_2_8A008(cur);
    if (*(u8 *)((u8 *)&Static_Stats_Tables + 0x4756) == 1) {
        *(s32 *)(menuCursors + 0x50) = superstarUnlocked[0xF6];
    }
    currentDrawingItem->func = fn_2_8A824;
}

// .text:0x0008A824 size:0x3D8 mapped:0x806C98B8
void fn_2_8A824(void) {
    u8 *lbl = lbl_2_bss_33FBCC;
    DrawingSceneStruct *node = currentDrawingItem;
    u16 first;
    s8 v;
    s32 i;
    s32 k;
    s32 count = 0;
    s32 total = 0;
    u8 *table;

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
        if (lbl[0x18] == 0) {
            first = *(u16 *)((u8 *)node + 0x14);
            v = (s8)lbl[0x0F];
            *(u16 *)((u8 *)graphicsRelatedArray[first + v + 7].object + 0x64) = 20;
            *(u32 *)((u8 *)graphicsRelatedArray[first + v + 7].object + 0x54) |= 2;
            *(u32 *)((u8 *)graphicsRelatedArray[first + v + 7].object + 0x5C) = 0;
            *(u8 *)((u8 *)graphicsRelatedArray[first + v + 7].object + 0x68) = 1;
            *(u16 *)((u8 *)graphicsRelatedArray[first + *(s32 *)(menuCursors + 0x50) + 7].object + 0x64) = 19;
            *(u8 *)((u8 *)graphicsRelatedArray[first + *(s32 *)(menuCursors + 0x50) + 7].object + 0x68) = 1;
            *(u32 *)((u8 *)graphicsRelatedArray[first + v + 0x42].object + 0x54) |= 2;
            *(u8 *)((u8 *)graphicsRelatedArray[first + v + 0x42].object + 0x68) = 1;
            lbl[0x18] = 0;
            lbl[0x19] = 0;
        }
        if (lbl[0x19] == 1) {
            lbl[0x17] = 0;
            lbl[0x18] = 0;
            lbl[0x19] = 0;
        }
        break;
    case 0x4E:
        fn_2_87FB0(node);
        break;
    case 0x4F:
        fn_2_87998(node);
        break;
    case 0x50:
        if (lbl[0x18] == 0) {
            fn_2_8A008(node);
            lbl[0x18] = 1;
            lbl[0x19] = 1;
        }
        if (lbl[0x19] == 1) {
            table = lbl_80354768;
            for (i = 0; i < 3; i++) {
                if (table[i + 0xCF5E] != 0) {
                    s8 b = (s8)table[i * 0x4508 + 0x444B];
                    if (b != -1) {
                        total++;
                        count += (maybeCheckAndResetGrapicsElement((MenuScene *)node, i + 0x32, 10) != 0);
                    } else if (table[i * 0x4508 + 0x1606] == 0) {
                        total++;
                        count += (maybeCheckAndResetGrapicsElement((MenuScene *)node, i + 0x35, 0xE) != 0);
                    }
                }
            }
            if (count == total) {
                lbl[0x17] = 0;
                lbl[0x18] = 0;
                lbl[0x19] = 0;
            }
        }
        break;
    }

    first = *(u16 *)((u8 *)node + 0x14);
    for (k = 0; k < 3; k++) {
        u32 *flags = (u32 *)((u8 *)graphicsRelatedArray[first + k + 0x3F].object + 0x54);
        if (*(s32 *)(menuCursors + 0x50) == k) {
            *flags |= 2;
        } else {
            *flags &= ~3;
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
#define REC_OBJ(idx) ((u8 *)graphicsRelatedArray[first + (idx)].object)
void fn_2_8A008(DrawingSceneStruct *node) {
    u16 first = *(u16 *)((u8 *)node + 0x14);
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
            *(u16 *)(REC_OBJ(i + 4) + 0x64) = 0x11;
            load_Icon(node, i + 0x38, 1, 5, i);

            if (table[0x1606] != 0 && table[0x441B] == 0) {
                *(u32 *)(REC_OBJ(i + 0x3B) + 0x54) |= 2;
                load_Icon(node, i + 0x3B, 1, 4, table[0x4416]);
                *(u32 *)(REC_OBJ(i + 0x3B) + 0x5C) = 0;
                *(u8 *)(REC_OBJ(i + 0x3B) + 0x68) = 1;
                load_Icon(node, i + 4, 1, 6, table[0x4416]);
                *(u32 *)(REC_OBJ(i + 0xB) + 0x54) &= ~3;
                *(u32 *)(REC_OBJ(i + 0x17) + 0x54) &= ~3;
                *(u32 *)(REC_OBJ(i + 0x32) + 0x54) &= ~3;
                *(u32 *)(REC_OBJ(i + 0x35) + 0x54) &= ~3;
            } else {
                *(u32 *)(REC_OBJ(i + 0x3B) + 0x54) &= ~3;
                *(u32 *)(REC_OBJ(i + 0xB) + 0x54) |= 2;
                *(u32 *)(REC_OBJ(i + 0x17) + 0x54) |= 2;
                *(u32 *)(REC_OBJ(i + 0x38) + 0x54) |= 2;
                *(u32 *)(REC_OBJ(i + 0x32) + 0x54) |= 2;
                *(u32 *)(REC_OBJ(i + 0x35) + 0x54) |= 2;
                *(u32 *)(REC_OBJ(3 * i + 0xE) + 0x54) |= 2;
                *(u32 *)(REC_OBJ(3 * i + 0xF) + 0x54) |= 2;
                *(u32 *)(REC_OBJ(3 * i + 0x10) + 0x54) |= 2;

                menuSel = lbl_2_data_2F964;
                sel = 0;
                for (j = 0; j < 6; j++) {
                    if (menuSel[j] == table[0x441D]) {
                        sel = j;
                    }
                }
                *(u32 *)(REC_OBJ(i + 0xB) + 0x5C) = 0;
                load_Icon(node, i + 0xB, 1, 0x54, sel);
                *(u32 *)(REC_OBJ(i + 0xB) + 0x58) |= 0xFF;
                *(u8 *)(REC_OBJ(i + 0xB) + 0x68) = 1;

                if ((s8)table[0x444B] != -1) {
                    *(u32 *)(REC_OBJ(i + 0x32) + 0x54) |= 2;
                    *(u32 *)(REC_OBJ(i + 0x32) + 0x5C) = 0;
                    load_Icon(node, i + 0x32, 4, 0x64, (s8)table[0x444B]);
                    *(u8 *)(REC_OBJ(i + 0x32) + 0x68) = 1;
                    *(u32 *)(REC_OBJ(i + 0x35) + 0x54) &= ~3;
                    *(u8 *)(REC_OBJ(i + 0x35) + 0x68) = 0;
                } else {
                    *(u32 *)(REC_OBJ(i + 0x35) + 0x54) |= 2;
                    *(u8 *)(REC_OBJ(i + 0x35) + 0x68) = 1;
                    *(u32 *)(REC_OBJ(i + 0x32) + 0x54) &= ~3;
                }
                load_Icon(node, i + 4, 1, 6, table[0x4415]);

                writes = 0;
                for (j = 0; j < 3; j++) {
                    v = *(s16 *)(table + 0x40B8 + 6 * j);
                    if (v != (s8)table[0x441D]) {
                        *(u32 *)(REC_OBJ(8 * i + writes + 0x1A) + 0x5C) = (u32)v << 16;
                        writes++;
                    }
                }
            }
        } else {
            *(u16 *)(REC_OBJ(i + 4) + 0x64) = 1;
            *(u32 *)(REC_OBJ(i + 4) + 0x5C) = 0;
            *(u8 *)(REC_OBJ(i + 4) + 0x68) = 1;
            load_Icon(node, i + 4, 1, 6, 4);
            *(u32 *)(REC_OBJ(i + 0xB) + 0x54) &= ~3;
            *(u32 *)(REC_OBJ(i + 0x17) + 0x54) &= ~3;
            *(u32 *)(REC_OBJ(i + 0x38) + 0x54) &= ~3;
            *(u32 *)(REC_OBJ(i + 0x32) + 0x54) &= ~3;
            *(u32 *)(REC_OBJ(i + 0x35) + 0x54) &= ~3;
            *(u32 *)(REC_OBJ(i + 0x3B) + 0x54) &= ~3;
            *(u32 *)(REC_OBJ(3 * i + 0xE) + 0x54) &= ~3;
            *(u32 *)(REC_OBJ(3 * i + 0xF) + 0x54) &= ~3;
            *(u32 *)(REC_OBJ(3 * i + 0x10) + 0x54) &= ~3;
        }

        if (*(s32 *)(menuCursors + 0x50) == i) {
            *(u32 *)(REC_OBJ(i + 0x3F) + 0x54) |= 2;
        } else {
            *(u32 *)(REC_OBJ(i + 0x3F) + 0x54) &= ~3;
        }
    }
}

// .text:0x00089F70 size:0x98 mapped:0x806C9004
void fn_2_89F70(void) {
    DrawingSceneStruct *cur = currentDrawingItem;
    u8 *base = lbl_2_data_2E9F8;
    const UIRecordDescriptor *desc;

    switch (lbl_2_bss_33FBCC[5]) {
    case 0:
        desc = (const UIRecordDescriptor *)(base + 0xDCC);
        break;
    case 1:
    case 2:
        desc = (const UIRecordDescriptor *)(base + 0xCCC);
        break;
    case 3:
        desc = (const UIRecordDescriptor *)(base + 0xBAC);
        break;
    }
    addGraphicsElementToScene(cur, desc);
    lbl_2_bss_33FBCC[0xE] = 0;
    currentDrawingItem->func = fn_2_8975C;
}

// .text:0x0008975C size:0x814 mapped:0x806C87F0
#define REC_OBJ(idx) ((u8 *)graphicsRelatedArray[first + (idx)].object)
void fn_2_8975C(void) {
    u8 *lbl = lbl_2_bss_33FBCC;
    DrawingSceneStruct *node = currentDrawingItem;
    u16 first;
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
        first = *(u16 *)((u8 *)node + 0x14);
        if (lbl[0x20] == 0) {
            *(u8 *)(REC_OBJ(1) + 0x68) = 1;
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
                *(u8 *)(REC_OBJ(k + 3) + 0x68) = 1;
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
        first = *(u16 *)((u8 *)node + 0x14);
        if (lbl[0x20] == 0) {
            *(u8 *)(REC_OBJ(0) + 0x68) = 4;
            *(u8 *)(REC_OBJ(1) + 0x68) = 4;
            for (k = 0; k < n; k++) {
                *(u32 *)(REC_OBJ(k + 3) + 0x5C) = 0x30000;
                *(u8 *)(REC_OBJ(k + 3) + 0x68) = 4;
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
        first = *(u16 *)((u8 *)node + 0x14);
        if (lbl[0x20] == 0) {
            ret1 = fn_2_895F8(0);
            ret2 = fn_2_895F8(1);
            *(u32 *)(REC_OBJ(ret1 + 3) + 0x5C) = 0x80000;
            *(u8 *)(REC_OBJ(ret1 + 3) + 0x68) = 0;
            *(u32 *)(REC_OBJ(ret2 + 3) + 0x5C) = 0x30000;
            *(u8 *)(REC_OBJ(ret2 + 3) + 0x68) = 0;
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
    u32 sel;

    if (useLocal != 0) {
        sel = *(u32 *)(lbl_2_bss_33FBCC + 0x1C);
    } else {
        sel = *(u32 *)(menuCursors + 0x54);
    }

    switch (lbl_2_bss_33FBCC[5]) {
    case 0:
        return sel == 5 ? 1 : 0;
    case 1:
        switch (sel) {
        case 3:
            return 1;
        case 4:
            return 2;
        case 5:
            return 3;
        }
        return 0;
    case 2:
        switch (sel) {
        case 2:
            return 0;
        case 3:
            return 1;
        case 4:
            return 2;
        case 5:
            return 3;
        }
        return 0;
    case 3:
        switch (sel) {
        case 1:
            return 0;
        case 2:
            return 1;
        case 3:
            return 2;
        case 4:
            return 3;
        case 5:
            return 4;
        }
        return 0;
    }
    return 0;
}

// .text:0x00089038 size:0x5C0 mapped:0x806C80CC
#define REC_OBJ(idx) ((u8 *)graphicsRelatedArray[first + (idx)].object)
void fn_2_89038(DrawingSceneStruct *node) {
    u8 *lbl = lbl_2_bss_33FBCC;
    u16 first = *(u16 *)((u8 *)node + 0x14);
    u8 *table;
    u8 digits[3];
    s16 value;
    s32 i;
    s32 j;
    s32 k;
    s32 count = 0;
    s32 total = 0;

    if (lbl[0x18] == 0) {
        table = lbl_80354768;
        for (i = 0; i < 3; i++) {
            u8 *rec = table + i * 0x4508;

            if (table[i + 0xCF5E] != 0) {
                value = *(s16 *)(rec + 0x43BC);
                digits[0] = (u8)(value / 100);
                digits[1] = (u8)((value % 100) / 10);
                digits[2] = (u8)(value % 10);
                for (j = 0; j < 3; j++) {
                    *(u32 *)(REC_OBJ(3 * i + j + 0xE) + 0x54) |= 2;
                    *(u32 *)(REC_OBJ(3 * i + j + 0xE) + 0x5C) = 0;
                    load_Icon(node, 0xE + 3 * i + j, 1, 0xD, (s8)digits[j]);
                    *(u8 *)(REC_OBJ(3 * i + j + 0xE) + 0x68) = 1;
                }

                if (*(s32 *)(menuCursors + 0x50) == i) {
                    *(u8 *)(REC_OBJ(i + 4) + 0x68) = 1;
                    *(u16 *)(REC_OBJ(i + 7) + 0x64) = 0x13;
                    *(u32 *)(REC_OBJ(i + 7) + 0x5C) = 0;
                    *(u8 *)(REC_OBJ(i + 7) + 0x68) = 1;
                } else {
                    *(u8 *)(REC_OBJ(i + 4) + 0x68) = 1;
                    *(u16 *)(REC_OBJ(i + 7) + 0x64) = 0x12;
                    *(u8 *)(REC_OBJ(i + 7) + 0x68) = 1;
                    if (table[i * 0x4508 + 0x1606] == 0 || table[i * 0x4508 + 0x441B] != 0) {
                        *(u32 *)(REC_OBJ(i + 0xB) + 0x5C) = 0x1A0000;
                        *(u8 *)(REC_OBJ(i + 0xB) + 0x68) = 0;
                    }
                    if (table[i * 0x4508 + 0x444B] != -1) {
                        *(u32 *)(REC_OBJ(i + 0x32) + 0x54) |= 2;
                        *(u32 *)(REC_OBJ(i + 0x32) + 0x5C) = 0;
                        load_Icon(node, i + 0x32, 4, 0x64, (s8)table[i * 0x4508 + 0x444B]);
                        *(u8 *)(REC_OBJ(i + 0x32) + 0x68) = 1;
                    } else {
                        *(u32 *)(REC_OBJ(i + 0x35) + 0x54) &= ~3;
                        *(u8 *)(REC_OBJ(i + 0x35) + 0x68) = 0;
                        *(u32 *)(REC_OBJ(i + 0x35) + 0x54) |= 2;
                        *(u8 *)(REC_OBJ(i + 0x35) + 0x68) = 1;
                        *(u32 *)(REC_OBJ(i + 0x32) + 0x54) &= ~3;
                    }
                }
            } else {
                if (*(s32 *)(menuCursors + 0x50) == i) {
                    *(u16 *)(REC_OBJ(i + 7) + 0x64) = 0x13;
                    *(u8 *)(REC_OBJ(i + 7) + 0x68) = 1;
                }
            }
        }
        lbl[0x18] = 1;
        lbl[0x19] = 1;
    }

    if (lbl[0x19] == 1) {
        table = lbl_80354768;
        for (i = 0; i < 3; i++) {
            if (table[i + 0xCF5E] != 0) {
                for (k = 0; k < 3; k++) {
                    total++;
                    count += (maybeCheckAndResetGrapicsElement((MenuScene *)node, 0xE + 3 * i + k, 0x15) != 0);
                }
                if (table[i * 0x4508 + 0x1606] == 0 || table[i * 0x4508 + 0x441B] != 0) {
                    if (*(s32 *)(menuCursors + 0x50) == i) {
                        total++;
                        count += (maybeCheckAndResetGrapicsElement((MenuScene *)node, i + 0xB, 0x15) != 0);
                    }
                    if (table[i * 0x4508 + 0x444B] != -1) {
                        total++;
                        count += (maybeCheckAndResetGrapicsElement((MenuScene *)node, i + 0x32, 0xA) != 0);
                    } else {
                        total++;
                        count += (maybeCheckAndResetGrapicsElement((MenuScene *)node, i + 0x35, 0xE) != 0);
                    }
                }
            }
        }
        if (count == total) {
            lbl[0x18] = 0;
            lbl[0x17] = 0;
            lbl[0x19] = 0;
        }
    }
}

// .text:0x00088D90 size:0x2A8 mapped:0x806C7E24
void fn_2_88D90(DrawingSceneStruct *node) {
    u8 *lbl = lbl_2_bss_33FBCC;
    u16 first = *(u16 *)((u8 *)node + 0x14);
    u8 *table = lbl_80354768;
    s32 i;
    BOOL done;

    if (lbl[0x18] == 0) {
        *(u32 *)((u8 *)graphicsRelatedArray[first].object + 0x5C) = 0x190000;
        *(u8 *)((u8 *)graphicsRelatedArray[first].object + 0x68) = 4;

        for (i = 0; i < 3; i++) {
            *(u8 *)((u8 *)graphicsRelatedArray[first + i + 4].object + 0x68) = 4;
            if (table[i * 0x4508 + 0xCF5E] != 0) {
                *(u8 *)((u8 *)graphicsRelatedArray[first + 3 * i + 0xE].object + 0x68) = 4;
                *(u8 *)((u8 *)graphicsRelatedArray[first + 3 * i + 0xF].object + 0x68) = 4;
                *(u8 *)((u8 *)graphicsRelatedArray[first + 3 * i + 0x10].object + 0x68) = 4;
                *(u8 *)((u8 *)graphicsRelatedArray[first + i + 0x38].object + 0x68) = 4;
                if (table[i * 0x4508 + 0x1606] != 0 && table[i * 0x4508 + 0x441B] == 0) {
                    *(u8 *)((u8 *)graphicsRelatedArray[first + i + 0x3B].object + 0x68) = 4;
                } else {
                    *(u8 *)((u8 *)graphicsRelatedArray[first + i + 0x17].object + 0x68) = 4;
                    *(u32 *)((u8 *)graphicsRelatedArray[first + i + 0xB].object + 0x5C) = 0x160000;
                    *(u8 *)((u8 *)graphicsRelatedArray[first + i + 0xB].object + 0x68) = 4;
                    if (table[i * 0x4508 + 0x444B] != -1) {
                        *(u8 *)((u8 *)graphicsRelatedArray[first + i + 0x32].object + 0x68) = 4;
                    }
                }
            }
        }
        lbl[0x18] = 1;
        lbl[0x19] = 1;
    }

    if (lbl[0x19] == 1) {
        done = maybeCheckAndResetGrapicsElement((MenuScene *)node, 0, 0) != FALSE;
        if ((*(u32 *)((u8 *)graphicsRelatedArray[first].object + 0x5C) >> 16) == 3) {
            changeScene(3, 6);
        }
        if (done) {
            *(u8 *)((u8 *)&Static_Stats_Tables + 0x48AF) = 1;
            lbl[0x1A] = 1;
            lbl[0x17] = 0;
            lbl[0x18] = 0;
            lbl[0x19] = 0;
        }
    }
}

// .text:0x000887F8 size:0x598 mapped:0x806C788C
#define REC_OBJ(idx) ((u8 *)graphicsRelatedArray[first + (idx)].object)
void fn_2_887F8(DrawingSceneStruct *node) {
    u8 *lbl = lbl_2_bss_33FBCC;
    u16 first = *(u16 *)((u8 *)node + 0x14);
    u8 *table;
    s32 i;
    s32 j;
    s32 count = 0;
    s32 total = 0;
    s32 digits[3];
    s16 value;

    if (lbl[0x18] == 0) {
        fn_2_8A008(node);
        table = lbl_80354768;
        for (i = 0; i < 3; i++) {
            u8 *rec = table + i * 0x4508;

            if (table[i + 0xCF5E] != 0) {
                if (*(s32 *)(menuCursors + 0x50) == i) {
                    value = *(s16 *)(rec + 0x43BC);
                    digits[0] = value / 100;
                    digits[1] = (value % 100) / 10;
                    digits[2] = value % 10;
                    for (j = 0; j < 3; j++) {
                        *(u32 *)(REC_OBJ(3 * i + j + 0xE) + 0x54) |= 2;
                        *(u32 *)(REC_OBJ(3 * i + j + 0xE) + 0x5C) = 0;
                        load_Icon(node, 0xE + 3 * i + j, 1, 0xD, digits[j]);
                        *(u8 *)(REC_OBJ(3 * i + j + 0xE) + 0x68) = 1;
                    }
                    *(u8 *)(REC_OBJ(i + 4) + 0x68) = 1;
                    *(u16 *)(REC_OBJ(i + 7) + 0x64) = 0x13;
                    *(u32 *)(REC_OBJ(i + 7) + 0x5C) = 0;
                    *(u8 *)(REC_OBJ(i + 7) + 0x68) = 1;
                } else {
                    *(u8 *)(REC_OBJ(i + 4) + 0x68) = 1;
                    *(u16 *)(REC_OBJ(i + 7) + 0x64) = 0x12;
                    *(u8 *)(REC_OBJ(i + 7) + 0x68) = 1;
                    *(u32 *)(REC_OBJ(i + 0xB) + 0x5C) = 0x1A0000;
                    *(u8 *)(REC_OBJ(i + 0xB) + 0x68) = 0;
                }

                if (table[i * 0x4508 + 0x444B] != -1) {
                    *(u32 *)(REC_OBJ(i + 0x32) + 0x54) |= 2;
                    *(u32 *)(REC_OBJ(i + 0x32) + 0x5C) = 0;
                    load_Icon(node, i + 0x32, 4, 0x64, (s8)table[i * 0x4508 + 0x444B]);
                    *(u8 *)(REC_OBJ(i + 0x32) + 0x68) = 1;
                } else {
                    *(u32 *)(REC_OBJ(i + 0x35) + 0x54) &= ~3;
                    *(u8 *)(REC_OBJ(i + 0x35) + 0x68) = 0;
                    *(u32 *)(REC_OBJ(i + 0x35) + 0x54) |= 2;
                    *(u8 *)(REC_OBJ(i + 0x35) + 0x68) = 1;
                    *(u32 *)(REC_OBJ(i + 0x32) + 0x54) &= ~3;
                }
            }
        }

        *(u32 *)(REC_OBJ(*(s32 *)(menuCursors + 0x50) + 7) + 0x54) |= 2;
        *(u32 *)(REC_OBJ(*(s32 *)(menuCursors + 0x50) + 7) + 0x5C) = 0;
        *(u8 *)(REC_OBJ(*(s32 *)(menuCursors + 0x50) + 7) + 0x68) = 1;
        *(u32 *)(REC_OBJ(*(s32 *)(menuCursors + 0x50) + 4) + 0x54) |= 2;
        lbl[0x18] = 1;
        lbl[0x19] = 1;
    }

    if (lbl[0x19] == 1) {
        table = lbl_80354768;
        for (i = 0; i < 3; i++) {
            if (table[i + 0xCF5E] != 0) {
                if (*(s32 *)(menuCursors + 0x50) == i) {
                    for (j = 0; j < 3; j++) {
                        total++;
                        count += (maybeCheckAndResetGrapicsElement((MenuScene *)node, 0xE + 3 * i + j, 0x15) != 0);
                    }
                } else if (table[i * 0x4508 + 0x444B] != -1) {
                    total++;
                    count += (maybeCheckAndResetGrapicsElement((MenuScene *)node, i + 0x32, 0xA) != 0);
                } else {
                    total++;
                    count += (maybeCheckAndResetGrapicsElement((MenuScene *)node, i + 0x35, 0xE) != 0);
                }
            }
        }
        if (count == total) {
            lbl[0x18] = 0;
            lbl[0x17] = 0;
            lbl[0x19] = 0;
        }
    }
}

// .text:0x000883C8 size:0x430 mapped:0x806C745C
#define REC_OBJ(idx) ((u8 *)graphicsRelatedArray[first + (idx)].object)
void fn_2_883C8(DrawingSceneStruct *node) {
    u8 *lbl = lbl_2_bss_33FBCC;
    u16 first = *(u16 *)((u8 *)node + 0x14);
    u8 *table;
    s32 i;
    s32 count = 0;
    s32 total = 0;

    if (lbl[0x18] == 0 && (s8)lbl[0x0D] != *(s32 *)(menuCursors + 0x50)) {
        table = lbl_80354768;
        for (i = 0; i < 3; i++) {
            if (table[i + 0xCF5E] != 0) {
                if (*(s32 *)(menuCursors + 0x50) == i) {
                    *(u8 *)(REC_OBJ(i + 4) + 0x68) = 1;
                    *(u16 *)(REC_OBJ(i + 7) + 0x64) = 0x13;
                    *(u8 *)(REC_OBJ(i + 7) + 0x68) = 1;
                    if (table[i * 0x4508 + 0x1606] == 0 || table[i * 0x4508 + 0x441B] != 0) {
                        *(u32 *)(REC_OBJ(i + 0xB) + 0x5C) = 0x1A0000;
                        *(u8 *)(REC_OBJ(i + 0xB) + 0x68) = 4;
                    }
                } else {
                    if ((s8)lbl[0x0D] == i && (s8)lbl[0x0F] != i) {
                        *(u8 *)(REC_OBJ(i + 4) + 0x68) = 1;
                        *(u16 *)(REC_OBJ(i + 7) + 0x64) = 0x12;
                        *(u8 *)(REC_OBJ(i + 7) + 0x68) = 1;
                        if (table[i * 0x4508 + 0x1606] == 0 || table[i * 0x4508 + 0x441B] != 0) {
                            *(u32 *)(REC_OBJ(i + 0xB) + 0x5C) = 0x160000;
                            *(u8 *)(REC_OBJ(i + 0xB) + 0x68) = 1;
                        }
                    }
                }
            } else {
                if (*(s32 *)(menuCursors + 0x50) == i) {
                    *(u16 *)(REC_OBJ(i + 7) + 0x64) = 0x13;
                    *(u8 *)(REC_OBJ(i + 7) + 0x68) = 1;
                } else {
                    *(u16 *)(REC_OBJ(i + 7) + 0x64) = 0x12;
                    *(u8 *)(REC_OBJ(i + 7) + 0x68) = 1;
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
    u8 *lbl = lbl_2_bss_33FBCC;
    u16 first = *(u16 *)((u8 *)node + 0x14);
    s8 v;
    u8 *rec;

    if (lbl[0x18] == 0) {
        v = (s8)lbl[0xF];

        rec = (u8 *)graphicsRelatedArray[first + v + 7].object;
        *(u16 *)(rec + 0x64) = 0x14;
        rec = (u8 *)graphicsRelatedArray[first + v + 7].object;
        *(u32 *)(rec + 0x54) |= 2;
        rec = (u8 *)graphicsRelatedArray[first + v + 7].object;
        *(u32 *)(rec + 0x5C) = 0;
        rec = (u8 *)graphicsRelatedArray[first + v + 7].object;
        *(u8 *)(rec + 0x68) = 1;

        rec = (u8 *)graphicsRelatedArray[first + *(u32 *)(menuCursors + 0x50) + 7].object;
        *(u16 *)(rec + 0x64) = 0x13;
        rec = (u8 *)graphicsRelatedArray[first + *(u32 *)(menuCursors + 0x50) + 7].object;
        *(u8 *)(rec + 0x68) = 1;

        rec = (u8 *)graphicsRelatedArray[first + v + 0x42].object;
        *(u32 *)(rec + 0x54) |= 2;
        rec = (u8 *)graphicsRelatedArray[first + v + 0x42].object;
        *(u8 *)(rec + 0x68) = 1;

        lbl[0x18] = 0;
        lbl[0x19] = 0;
    }
    if (lbl[0x19] == 1) {
        lbl[0x17] = 0;
        lbl[0x18] = 0;
        lbl[0x19] = 0;
    }
}

// .text:0x00087FB0 size:0x2A0 mapped:0x806C7044
void fn_2_87FB0(DrawingSceneStruct *node) {
    u8 *lbl = lbl_2_bss_33FBCC;
    u16 first = *(u16 *)((u8 *)node + 0x14);
    s8 v;
    s32 i;
    s32 count = 0;
    s32 total = 0;
    u8 *table;

    if (lbl[0x18] == 0) {
        fn_2_8A008(node);
        v = (s8)lbl[0x10];

        *(u16 *)((u8 *)graphicsRelatedArray[first + v + 7].object + 0x64) = 0x12;
        *(u32 *)((u8 *)graphicsRelatedArray[first + v + 7].object + 0x5C) = 0;
        *(u8 *)((u8 *)graphicsRelatedArray[first + v + 7].object + 0x68) = 1;

        *(u16 *)((u8 *)graphicsRelatedArray[first + *(s32 *)(menuCursors + 0x50) + 7].object + 0x64) = 0x12;
        *(u8 *)((u8 *)graphicsRelatedArray[first + *(s32 *)(menuCursors + 0x50) + 7].object + 0x68) = 1;

        *(u32 *)((u8 *)graphicsRelatedArray[first + v + 4].object + 0x54) |= 2;
        *(u32 *)((u8 *)graphicsRelatedArray[first + v + 0x42].object + 0x54) &= ~3;

        lbl[0x18] = 1;
        lbl[0xD] = (u8)v;
        *(s32 *)(menuCursors + 0x50) = v;
        lbl[0x10] = 0xFF;
        lbl[0x19] = 1;
    }

    if (lbl[0x19] == 1) {
        table = lbl_80354768;
        for (i = 0; i < 3; i++) {
            if (table[i + 0xCF5E] != 0) {
                s8 b = (s8)table[i * 0x4508 + 0x444B];
                if (b != -1) {
                    total++;
                    count += (maybeCheckAndResetGrapicsElement((MenuScene *)node, i + 0x32, 10) != 0);
                } else if (table[i * 0x4508 + 0x1606] == 0) {
                    total++;
                    count += (maybeCheckAndResetGrapicsElement((MenuScene *)node, i + 0x35, 0xE) != 0);
                }
            }
        }
        if (count == total) {
            *(u16 *)((u8 *)graphicsRelatedArray[first + *(s32 *)(menuCursors + 0x50) + 7].object + 0x64) = 0x13;
            *(u8 *)((u8 *)graphicsRelatedArray[first + *(s32 *)(menuCursors + 0x50) + 7].object + 0x68) = 1;
            lbl[0x17] = 0;
            lbl[0x18] = 0;
            lbl[0x19] = 0;
        }
    }
}

// .text:0x00087998 size:0x618 mapped:0x806C6A2C
#define REC_OBJ(idx) ((u8 *)graphicsRelatedArray[first + (idx)].object)
void fn_2_87998(DrawingSceneStruct *node) {
    u8 *lbl = lbl_2_bss_33FBCC;
    u16 first = *(u16 *)((u8 *)node + 0x14);
    u8 *table;
    u8 digits[3];
    s16 value;
    s32 i;
    s32 j;
    s32 k;
    s32 v;
    s32 count = 0;
    s32 total = 0;

    if (lbl[0x18] == 0) {
        fn_2_8A008(node);
        table = lbl_80354768;
        for (i = 0; i < 3; i++) {
            u8 *rec = table + i * 0x4508;

            if (table[i + 0xCF5E] != 0) {
                if (*(s32 *)(menuCursors + 0x50) == i) {
                    *(u32 *)(REC_OBJ(i + 0x38) + 0x54) |= 2;
                    load_Icon(node, i + 0x38, 1, 5, i);

                    value = *(s16 *)(rec + 0x43BC);
                    digits[0] = (u8)(value / 100);
                    digits[1] = (u8)((value % 100) / 10);
                    digits[2] = (u8)(value % 10);
                    for (j = 0; j < 3; j++) {
                        *(u32 *)(REC_OBJ(3 * i + j + 0xE) + 0x54) |= 2;
                        *(u32 *)(REC_OBJ(3 * i + j + 0xE) + 0x5C) = 0;
                        load_Icon(node, 0xE + 3 * i + j, 1, 0xD, (s8)digits[j]);
                        *(u8 *)(REC_OBJ(3 * i + j + 0xE) + 0x68) = 1;
                    }

                    *(u32 *)(REC_OBJ(i + 0xB) + 0x5C) = 0;
                    *(u8 *)(REC_OBJ(i + 0xB) + 0x68) = 1;
                    *(u8 *)(REC_OBJ(i + 4) + 0x68) = 1;
                    *(u16 *)(REC_OBJ(i + 7) + 0x64) = 0x13;
                    *(u32 *)(REC_OBJ(i + 7) + 0x5C) = 0;
                    *(u8 *)(REC_OBJ(i + 7) + 0x68) = 1;
                } else {
                    *(u8 *)(REC_OBJ(i + 4) + 0x68) = 1;
                    *(u16 *)(REC_OBJ(i + 7) + 0x64) = 0x12;
                    *(u8 *)(REC_OBJ(i + 7) + 0x68) = 1;
                    *(u32 *)(REC_OBJ(i + 0xB) + 0x5C) = 0x1A0000;
                    *(u8 *)(REC_OBJ(i + 0xB) + 0x68) = 0;
                }

                if (table[i * 0x4508 + 0x444B] == -1 &&
                    (table[i * 0x4508 + 0x1606] == 0 || table[i * 0x4508 + 0x441B] != 0)) {
                    *(u32 *)(REC_OBJ(i + 0x35) + 0x5C) = 0;
                    *(u8 *)(REC_OBJ(i + 0x35) + 0x68) = 1;
                }
            }
        }

        v = (s8)lbl[0x10];
        *(u32 *)(REC_OBJ(v + 7) + 0x54) |= 2;
        *(u32 *)(REC_OBJ(v + 7) + 0x5C) = 0;
        *(u8 *)(REC_OBJ(v + 7) + 0x68) = 1;
        *(u32 *)(REC_OBJ(v + 4) + 0x54) |= 2;
        *(u32 *)(REC_OBJ(v + 0x42) + 0x54) &= ~3;
        lbl[0x10] = 0xFF;
        lbl[0x18] = 1;
        lbl[0x19] = 1;
    }

    if (lbl[0x19] == 1) {
        table = lbl_80354768;
        for (i = 0; i < 3; i++) {
            if (table[i + 0xCF5E] != 0) {
                if (*(s32 *)(menuCursors + 0x50) == i) {
                    if (table[i * 0x4508 + 0x1606] == 0 || table[i * 0x4508 + 0x441B] != 0) {
                        total++;
                        count += (maybeCheckAndResetGrapicsElement((MenuScene *)node, i + 0xB, 0x15) != 0);
                    }
                    for (k = 0; k < 3; k++) {
                        total++;
                        count += (maybeCheckAndResetGrapicsElement((MenuScene *)node, 0xE + 3 * i + k, 0x15) != 0);
                    }
                }
                if (table[i * 0x4508 + 0x444B] != -1) {
                    total++;
                    count += (maybeCheckAndResetGrapicsElement((MenuScene *)node, i + 0x32, 0xA) != 0);
                } else if (table[i * 0x4508 + 0x1606] == 0 || table[i * 0x4508 + 0x441B] != 0) {
                    total++;
                    count += (maybeCheckAndResetGrapicsElement((MenuScene *)node, i + 0x35, 0xE) != 0);
                }
            }
        }
        if (count == total) {
            lbl[0x18] = 0;
            lbl[0x17] = 0;
            lbl[0x19] = 0;
        }
    }
}

// .text:0x0008782C size:0x16C mapped:0x806C68C0
void fn_2_8782C(void) {
    Rep0DEState *st = lbl_2_bss_340140;
    u32 *tbl;
    u32 *slots;
    s32 i;
    s32 j;
    s32 k;

    st->unk3078 = 0;
    tbl = *(u32 **)((u8 *)st + 0x2D9C);
    slots = (u32 *)((u8 *)st + 0x2DA0);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 5; j++) {
            slots[i * 5 + j] = (u32)tbl + tbl[i * 5 + j];
        }
    }
    *(u32 *)(lbl_2_bss_34009C + 0x64) = (u32)tbl + tbl[16];
    *(u32 *)(lbl_2_bss_34009C + 0x68) = (u32)tbl + tbl[17];

    for (k = 0; k < 5; k++) {
        u32 *p = (u32 *)((u8 *)lbl_2_bss_340140 + 0x2DA0) + k * 3;
        LoadActorLayout((void *)p[0]);
        convertGeometryAndSknHeader((void *)p[1], NULL);
        haveActLayoutPointToGeoHeader((void *)p[0], (void *)p[1]);
        convertTextureHeader((void *)p[2]);
        UpdateTexturePalettePointers((UnkTexPalGeo *)p[1], (void *)p[2]);
    }
    convertTextureHeader(*(void **)(lbl_2_bss_34009C + 0x64));
    convertTextureHeader(*(void **)(lbl_2_bss_34009C + 0x68));
}
