#include "menus/text_8782C.h"
#include "menus/rep_0DE0.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x80034e20.h"
#include "static/UnknownHomes_Static.h"

extern u8 lbl_2_bss_33FBCC[];
extern u8 lbl_2_data_2E9F8[];
extern u8 lbl_2_data_2ECE4[];
extern u8 *lbl_2_bss_3401BC;
extern u8 superstarUnlocked[];
extern u8 menuCursors[];

// .text:0x0008782C size:0x16C mapped:0x806C68C0
void fn_2_8782C(void) {
    return;
}

// .text:0x00087998 size:0x618 mapped:0x806C6A2C
void fn_2_87998(void) {
    return;
}

// .text:0x00087FB0 size:0x2A0 mapped:0x806C7044
void fn_2_87FB0(void) {
    return;
}

// .text:0x00088250 size:0x178 mapped:0x806C72E4
void fn_2_88250(void) {
    return;
}

// .text:0x000883C8 size:0x430 mapped:0x806C745C
void fn_2_883C8(void) {
    return;
}

// .text:0x000887F8 size:0x598 mapped:0x806C788C
void fn_2_887F8(void) {
    return;
}

// .text:0x00088D90 size:0x2A8 mapped:0x806C7E24
void fn_2_88D90(void) {
    return;
}

// .text:0x00089038 size:0x5C0 mapped:0x806C80CC
void fn_2_89038(void) {
    return;
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

// .text:0x0008975C size:0x814 mapped:0x806C87F0
void fn_2_8975C(void) {
    return;
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

// .text:0x0008A008 size:0x81C mapped:0x806C909C
#pragma dont_inline on
void fn_2_8A008(DrawingSceneStruct *node) {
    return;
}
#pragma dont_inline reset

// .text:0x0008A824 size:0x3D8 mapped:0x806C98B8
void fn_2_8A824(void) {
    return;
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

// .text:0x0008AC84 size:0x2C mapped:0x806C9D18
void fn_2_8AC84(s32 slot, s32 flag) {
    if (lbl_2_bss_340140->unk2D94 == NULL) {
        return;
    }
    lbl_2_bss_3401BC[slot + 0x50] = flag;
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

// .text:0x0008ACDC size:0x4 mapped:0x806C9D70
void fn_2_8ACDC(void) {
    return;
}
