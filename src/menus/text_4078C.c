#include "menus/text_4078C.h"
#include "text/text.h"
#include "Unknown/File_0x800b0a14.h"

// Local prototypes and externs for symbols owned by other units.
void fn_2_72054(s32 index, u8 state);
void fn_80062890(s32 arg);
void fn_800111B4(void *bank);
void fn_2_20218(void);
void fn_2_1BF50(void);
void fn_2_1BFD0(void);
void *ARAMTransfer(void *file, s32 arg1, s32 arg2, s32 arg3);
void *memcpy(void *dest, const void *src, u32 n);

extern u8 *lbl_2_bss_1A824C;
extern u8 *lbl_2_bss_1A8248;
extern u8 *lbl_2_bss_1A8234;
extern u8 *lbl_2_bss_1A8230;
extern u8 lbl_803C6CF8[];
extern u8 AtBat_ButtonInput1[];
extern u8 hugeAnimStruct[];
extern u8 menuNumber[];
extern u8 challengeDialogueTextFileDescriptor[];
extern void *lbl_2_data_12C0C[];
extern void *lbl_2_data_12CE8[];
extern s16 lbl_2_data_36EC[];
extern u8 lbl_2_bss_15B8[];

// Work area behind lbl_2_bss_1A824C (the 0x190000 window).
#define WORK_BASE() (lbl_2_bss_1A824C + 0x190000)
#define UI_1A8234() (lbl_2_bss_1A8234 + 0x160000)
#define UI_1A8230() (lbl_2_bss_1A8230 + 0x30000)

// The per-frame drawing item this file's scenes run on. Only the fields these
// functions touch are named; +0x0C is the child node, +0x28 the item's state.
typedef struct MenuDrawItem {
    /* 0x00 */ u8 unk00[0x0C];
    /* 0x0C */ DrawingSceneStruct *node;
    /* 0x10 */ u8 unk10[0x14 - 0x10];
    /* 0x14 */ s16 timer;
    /* 0x16 */ u8 unk16[0x28 - 0x16];
    /* 0x28 */ s8 state;
} MenuDrawItem;

// .text:0x00042708 size:0x4E0 mapped:0x8068179C
void fn_2_42708(void) {
    return;
}

// .text:0x00042638 size:0xD0 mapped:0x806816CC
void fn_2_42638(void) {
    s32 i;

    for (i = 0; i < 20; i += 5) {
        *(u8 *)(WORK_BASE() + 0x78C7 + i) = lbl_2_bss_1A8248[0x43C2 + i];
        *(u8 *)(WORK_BASE() + 0x78C8 + i) = lbl_2_bss_1A8248[0x43C3 + i];
        *(u8 *)(WORK_BASE() + 0x78C9 + i) = lbl_2_bss_1A8248[0x43C4 + i];
        *(u8 *)(WORK_BASE() + 0x78CA + i) = lbl_2_bss_1A8248[0x43C5 + i];
        *(u8 *)(WORK_BASE() + 0x78CB + i) = lbl_2_bss_1A8248[0x43C6 + i];
    }
}

// .text:0x00042490 size:0x1A8 mapped:0x80681524
void fn_2_42490(void) {
    s32 i;
    u8 count;

    for (i = 0; i < 10; i++) {
        *(u8 *)(WORK_BASE() + 0x78DB + i) = 0;
    }

    count = 0;
    for (i = 0; i < 20; i++) {
        if (*(s8 *)(WORK_BASE() + 0x78C7 + i) == 0 &&
            *(s8 *)(lbl_2_bss_1A8248 + 0x43C2 + i) == 1 &&
            lbl_2_data_36EC[i] == 1) {
            *(u8 *)(WORK_BASE() + 0x78DB + count) = (u8)i;
            count++;
        }
    }
    *(u8 *)(WORK_BASE() + 0x78EF) = count;
}

// .text:0x00042474 size:0x1C mapped:0x80681508
void fn_2_42474(void) {
    *(s16 *)(WORK_BASE() + 0x76E4) = 0x78;
}

// .text:0x00042388 size:0xEC mapped:0x8068141C
void fn_2_42388(void) {
    MenuDrawItem *item = (MenuDrawItem *)currentDrawingItem;

    switch (item->state) {
    case 0:
        *(s16 *)(WORK_BASE() + 0x76E4) = 0x78;
        item->state = 1;
        break;
    case 1:
        if (fn_2_40CB8() != 0) {
            item->state = 2;
        }
        break;
    case 2:
        item->node->state = 1;
        removeCurrentDrawingItem();
        item->state = 0;
        break;
    }

    if (*(u8 *)(WORK_BASE() + 0x783F) == 1) {
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        item->state = 0;
    }
}

// .text:0x000422FC size:0x8C mapped:0x80681390
void fn_2_422FC(s32 index) {
    *(u32 *)(WORK_BASE() + 0x7694) = 0;
    *(u32 *)(WORK_BASE() + 0x768C) = 0;
    *(u32 *)(WORK_BASE() + 0x7690) = 0;
    memcpy(lbl_2_bss_15B8, lbl_2_data_12C0C[index], 0x4000);
    *(u8 **)(WORK_BASE() + 0x7684) = lbl_2_bss_15B8;
}

// .text:0x00042270 size:0x8C mapped:0x80681304
void fn_2_42270(s32 index) {
    *(u32 *)(WORK_BASE() + 0x7694) = 0;
    *(u32 *)(WORK_BASE() + 0x768C) = 0;
    *(u32 *)(WORK_BASE() + 0x7690) = 0;
    memcpy(lbl_2_bss_15B8, lbl_2_data_12CE8[index], 0x4000);
    *(u8 **)(WORK_BASE() + 0x7684) = lbl_2_bss_15B8;
}

// .text:0x00040CB8 size:0x15B8 mapped:0x8067FD4C
// Placeholder body: the state machine is not drafted yet. The caller in
// fn_2_42388 tests the return value, so the prototype returns s32.
s32 fn_2_40CB8(void) {
    return 0;
}

// .text:0x00040B90 size:0x128 mapped:0x8067FC24
void fn_2_40B90(void) {
    MenuDrawItem *item = (MenuDrawItem *)currentDrawingItem;

    switch (item->state) {
    case 0:
        *(u8 *)(WORK_BASE() + 0x78F3) = 0;
        item->state = 1;
        break;
    case 1:
        hugeAnimStruct[0x307A] = 0;
        fn_2_20218();
        *(u8 *)(UI_1A8234() + 0x2992) = 1;
        *(u8 *)(UI_1A8230() + 0x2A86) = 1;
        item->state = 2;
        break;
    case 2:
        item->state = 3;
        break;
    case 3:
        fn_2_1BFD0();
        item->state = 4;
        break;
    case 4:
        menuNumber[0x26] = 1;
        item->state = 5;
        break;
    case 5:
        item->node->state = 1;
        removeCurrentDrawingItem();
        item->state = 0;
        break;
    }
}

// .text:0x00040A9C size:0xF4 mapped:0x8067FB30
void fn_2_40A9C(void) {
    MenuDrawItem *item = (MenuDrawItem *)currentDrawingItem;

    switch (item->state) {
    case 0:
        *(u8 *)(WORK_BASE() + 0x78F3) = 0;
        item->state = 1;
        break;
    case 1:
        hugeAnimStruct[0x307A] = 0;
        fn_2_20218();
        *(u8 *)(UI_1A8234() + 0x2992) = 1;
        *(u8 *)(UI_1A8230() + 0x2A86) = 1;
        item->state = 2;
        break;
    case 2:
        fn_2_1BF50();
        item->state = 3;
        break;
    case 3:
        item->node->state = 1;
        removeCurrentDrawingItem();
        item->state = 0;
        break;
    }
}

// .text:0x000409CC size:0xD0 mapped:0x8067FA60
void fn_2_409CC(void) {
    MenuDrawItem *item = (MenuDrawItem *)currentDrawingItem;

    switch (item->state) {
    case 0:
        screenTextArray.textBanks[4] =
            (TextBank *)ARAMTransfer(challengeDialogueTextFileDescriptor, 0, 1, 0);
        item->state = 1;
        break;
    case 1:
        if (lbl_803C6CF8[0x715] == 1) {
            fn_800111B4(screenTextArray.textBanks[4]);
            item->state = 2;
        }
        break;
    case 2:
        item->node->state = 1;
        removeCurrentDrawingItem();
        item->state = 0;
        break;
    }
}

// .text:0x000408BC size:0x110 mapped:0x8067F950
void fn_2_408BC(void) {
    MenuDrawItem *item = (MenuDrawItem *)currentDrawingItem;

    switch (item->state) {
    case 0:
        item->timer = 0x3C;
        *(u8 *)(WORK_BASE() + 0x782C) = 1;
        fn_2_72054(1, 0xD);
        fn_80062890(9);
        item->state = 1;
        break;
    case 1:
        if (item->timer-- == 0) {
            item->state = 2;
        }
        break;
    case 2:
        item->node->state = 1;
        removeCurrentDrawingItem();
        item->state = 0;
        break;
    }

    if (*(u8 *)(WORK_BASE() + 0x783F) == 1) {
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        item->state = 0;
    }
}

// .text:0x0004078C size:0x130 mapped:0x8067F820
void fn_2_4078C(void) {
    MenuDrawItem *item = (MenuDrawItem *)currentDrawingItem;

    switch (item->state) {
    case 0:
        *(u8 *)(WORK_BASE() + 0x783E) = 0;
        item->state = 1;
        break;
    case 1:
        if (*(u16 *)(AtBat_ButtonInput1 + (*(s8 *)(WORK_BASE() + 0x7863) << 5) + 2) & 0x100) {
            item->state = 2;
        }
        break;
    case 2:
        *(u8 *)(WORK_BASE() + 0x783E) = 1;
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        item->state = 0;
        break;
    }

    if (*(u8 *)(WORK_BASE() + 0x783F) == 1) {
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        item->state = 0;
    }
}
