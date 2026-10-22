#define SQRT2_LINKAGE static
#include "menus/rep_0AB0.h"
#include "header_rep_data.h"
#include "Unknown/File_0x800b0a14.h"
#include "static/UnknownHomes_Static.h"
#include "menus/yd_step.h"
#include "game/UnknownHomes_Game.h"
#include "Dolphin/gx.h"
#include "Dolphin/vec.h"
#include "Dolphin/mtx.h"
#include <string.h>

extern u8 menuNumber[0x28];
extern u8 *lbl_2_bss_1A8234;
extern u8 *lbl_2_bss_1A823C;
extern u8 *lbl_2_bss_1A824C;
extern u8 lbl_2_data_268A8[0x2E10];
extern struct {
    u8 _0[8];
    u16 label;
    u8 _A[6];
} lbl_800FEF70[];
extern u8 lbl_800EFBA4[0x10];
extern u8 lbl_8037169C[0x1C];
extern u8 lbl_2_data_20C68[];
extern s16 lbl_2_data_20C48[];
void fn_80053FE8(void);
void fn_2_54354(void *arg0, int count);
void fn_2_4E878(DrawingSceneStruct *item, void *data);
void fn_2_4E858(DrawingSceneStruct *item);
void fn_2_53F88(DrawingSceneStruct *item);
void fn_2_53DF8(DrawingSceneStruct *item);
void fn_2_54120(void);
void fn_8000F8F4(DrawingSceneStruct *item);
void text_freeAllBlocks(void);
void fn_2_5A224(void);
void fn_2_5C5B8(void);
void fn_2_5D26C(void);
void fn_2_5AFB0(void);
void fn_2_587F8(void);
void fn_2_8DFB0(void);
void fn_2_94854(int arg0);
void fn_2_9461C(int arg0);
void fn_2_94604(int arg0);
void fn_2_93C64(void);
void fn_2_903A8(int arg0);
void fn_2_92654(int arg0, int arg1);
void fn_2_4E7EC(void);
void fn_2_8FD14(void);
void fn_2_8AEE0(void);
void fn_2_47FF8(void);
void fn_2_47CFC(void);
void fn_2_5979C(void);
void fn_2_5CB5C(void);
extern u8 lbl_2_bss_33FBF0[];
void fn_2_1FFC4(int arg0);
void fn_2_1FF10(int arg0);
void fn_2_1FF14(int arg0);
void fn_2_1FF0C(int arg0);
void fn_2_5EB78(void);
void fn_2_93C64(void);
void fn_2_489DC(void);
extern u8 lbl_2_bss_A168;
extern u8 lbl_2_bss_A169;
extern u8 lbl_80354768[];
extern u8 *lbl_2_bss_1A8244;
extern u8 *lbl_2_bss_1A8248;
void changeScene(u8 scene, u16 arg1);
void resetGameStadiumStateOnExit(void);
void fn_8000F4B8(int arg0, int arg1, int arg2, int arg3);
void fn_2_5EB78(void);
void fn_2_54474(void);
void fn_2_5ED3C(void);
void fn_2_6ACF4(void);
void fn_2_71F60(void);
void fn_2_6AB3C(int arg0, Vec *arg1);
void fn_2_72054(s32 arg0, s32 arg1);
void fn_2_904A8(void);
void fn_2_9257C(void);
void fn_2_903A8(int arg0);
void fn_2_92654(int arg0, int arg1);
void fn_80035B50(int arg0);
void fn_800ACFB0(void *arg0);
void changeScreenVariables(u16 screen);
extern u8 lbl_803616CC[];
extern u8 *lbl_2_bss_1A8240;
extern u8 *lbl_2_bss_340140;
extern u8 *lbl_2_bss_3401BC;
extern u8 lbl_2_bss_3401C0[];
extern u8 hugeAnimStruct[];
extern u8 superstarUnlocked[];
extern u8 lbl_8037169C[];
extern u8 screenTextArray[];
extern u8 lbl_2_bss_1A8250[];
extern menuControlStruct *menuControlVariables;
extern u8 *lbl_2_bss_1A8230;
s32 sndFXStartEx(u16 soundId, u8 volume, u8 pan, u8 unk);
extern s32 lbl_2_data_35A0[];
extern s16 lbl_2_data_296B8[];
extern u8 lbl_800E869C[];
void fn_2_8E6A4(void);
void fn_2_68E68(void);
void fn_8006C2B4(void *dst, void *src);

#define WA(off)   (lbl_2_bss_1A8234[(off)])
#define WAH(off)  (*(s16 *)&lbl_2_bss_1A8234[(off)])
#define WB(off)   (lbl_2_bss_1A824C[(off)])
#define WBH(off)  (*(s16 *)&lbl_2_bss_1A824C[(off)])
#define WCH(off)  (*(s16 *)&lbl_2_bss_1A823C[(off)])
#define WB32(off) (*(s32 *)&lbl_2_bss_1A824C[(off)])
#define NODE_S16(n, off) (*(s16 *)((u8 *)(n) + (off)))
#define NODE_U16(n, off) (*(u16 *)((u8 *)(n) + (off)))
#define NODE_U8(n, off)  (*(u8 *)((u8 *)(n) + (off)))
#define PADB(i, off) (*(u8 *)((u8 *)&AtBat_ButtonInput1 + (i) * 0x20 + (off)))
#define PADH(i, off) (*(u16 *)((u8 *)&AtBat_ButtonInput1 + (i) * 0x20 + (off)))

#define SET_MENU(id)                                  \
    menuNumber[0] = (id);                             \
    menuNumber[9] = menuNumber[8];                    \
    menuNumber[8] = lbl_800FEF70[(id)].label

static inline void updateRecordGridCursor(void) {
    s8 idx = (s8)WB(0x197863);
    u16 pad = PADH(idx, 0x4);

    if (pad & INPUT_BUTTON_LEFT) {
        WBH(0x197708)--;
        if (WBH(0x197708) == 0 && (WBH(0x19770A) == 0 || WBH(0x19770A) == 5)) {
            WBH(0x197708) = 4;
        } else if (WBH(0x197708) < 0) {
            WBH(0x197708) = 5;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (pad & INPUT_BUTTON_RIGHT) {
        WBH(0x197708)++;
        if (WBH(0x197708) == 5 && (WBH(0x19770A) == 0 || WBH(0x19770A) == 5)) {
            WBH(0x197708) = 1;
        } else if (WBH(0x197708) > 5) {
            WBH(0x197708) = 0;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
    idx = (s8)WB(0x197863);
    pad = PADH(idx, 0x4);
    if (pad & INPUT_BUTTON_UP) {
        WBH(0x19770A)--;
        if (WBH(0x19770A) == 0 && (WBH(0x197708) == 0 || WBH(0x197708) == 5)) {
            WBH(0x19770A) = 4;
        } else if (WBH(0x19770A) < 0) {
            WBH(0x19770A) = 5;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (pad & INPUT_BUTTON_DOWN) {
        WBH(0x19770A)++;
        if (WBH(0x19770A) == 5 && (WBH(0x197708) == 0 || WBH(0x197708) == 5)) {
            WBH(0x19770A) = 1;
        } else if (WBH(0x19770A) > 5) {
            WBH(0x19770A) = 0;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
    WBH(0x197706) = lbl_2_data_296B8[WBH(0x197708) + WBH(0x19770A) * 6];
}

static inline void copySelectedRecord(void) {
    s32 off = WBH(0x197706) * 0x16;

    *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x7404) = *(s16 *)(lbl_2_bss_1A8240 + off + 0x140);
    *(u8 *)((lbl_2_bss_1A824C + 0x190000) + 0x7410) = lbl_2_bss_1A8240[off + 0x14C];
    *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x7406) = *(s16 *)(lbl_2_bss_1A8240 + off + 0x142);
    *(u8 *)((lbl_2_bss_1A824C + 0x190000) + 0x7411) = lbl_2_bss_1A8240[off + 0x14D];
    *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x7408) = *(s16 *)(lbl_2_bss_1A8240 + off + 0x144);
    *(u8 *)((lbl_2_bss_1A824C + 0x190000) + 0x7412) = lbl_2_bss_1A8240[off + 0x14E];
    *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x740A) = *(s16 *)(lbl_2_bss_1A8240 + off + 0x146);
    *(u8 *)((lbl_2_bss_1A824C + 0x190000) + 0x7413) = lbl_2_bss_1A8240[off + 0x14F];
    *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x740C) = *(s16 *)(lbl_2_bss_1A8240 + off + 0x148);
    *(u8 *)((lbl_2_bss_1A824C + 0x190000) + 0x7414) = lbl_2_bss_1A8240[off + 0x150];
    *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x740E) = *(s16 *)(lbl_2_bss_1A8240 + off + 0x14A);
    *(u8 *)((lbl_2_bss_1A824C + 0x190000) + 0x7415) = lbl_2_bss_1A8240[off + 0x151];
    *(u8 *)((lbl_2_bss_1A824C + 0x190000) + 0x7417) = lbl_2_bss_1A8240[off + 0x153];
    *(u8 *)((lbl_2_bss_1A824C + 0x190000) + 0x7418) = lbl_2_bss_1A8240[off + 0x154];
    *(u8 *)((lbl_2_bss_1A824C + 0x190000) + 0x7416) = lbl_2_bss_1A8240[off + 0x152];

    fn_8006C2B4((lbl_2_bss_1A824C + 0x190000) + 0x7430, (lbl_2_bss_1A824C + 0x190000) + 0x7404);
    memcpy((lbl_2_bss_1A824C + 0x190000) + 0x741A, (lbl_2_bss_1A824C + 0x190000) + 0x7404, 0x16);
    memcpy((lbl_2_bss_1A824C + 0x190000) + 0x7440, (lbl_2_bss_1A824C + 0x190000) + 0x7430, 0x10);

    *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x7404) = *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x741A);
    *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x7406) = *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x741C);
    *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x7408) = *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x7420);
    *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x740A) = *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x7422);
    *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x740C) = *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x741E);
    *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x740E) = *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x7424);
    *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x7430) = *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x7440);
    *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x7432) = *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x7442);
    *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x7434) = *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x7446);
    *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x7436) = *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x7448);
    *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x7438) = *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x7444);
    *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x743A) = *(s16 *)((lbl_2_bss_1A824C + 0x190000) + 0x744A);
}

static inline u8 *recordCopyDestination(s32 fieldOffset, s32 recordOffset, s32 base) {
    u8 *address = lbl_2_bss_1A824C + fieldOffset;
    address += base;
    address += recordOffset;
    return address;
}

// .text:0x0005E104 size:0x748 mapped:0x8069D198
void recordsScreen(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    DrawingSceneStruct *d;
    u8 *w = lbl_2_bss_1A8250;
    s32 i;
    Static_MSSB_Data *stats = &Static_Stats_Tables;

    lbl_2_bss_1A8230 = w + 0x162998;
    lbl_2_bss_1A8234 = w;
    lbl_2_bss_1A823C = (u8 *)&inningSetting.rel;
    lbl_2_bss_1A8244 = superstarUnlocked;
    lbl_2_bss_1A8248 = (u8 *)&g_Challenge;
    lbl_2_bss_1A8240 = lbl_803616CC;
    lbl_2_bss_1A824C = w;
    lbl_2_bss_340140 = hugeAnimStruct;
    lbl_2_bss_3401BC = lbl_2_bss_3401C0;

    switch (menuControlVariables->currentState) {
    case 0:
        resetGameStadiumStateOnExit();
        memset(w, 0, 0x1978FC);
        fn_2_54474();
        menuControlVariables->currentState = 1;
        fn_2_5EB78();
        {
            s32 recordOffset = 0;
            s32 fieldOffset;

            i = 0;

            do {
                if (i == 6) {
                    *(u32 *)(lbl_2_bss_1A824C + recordOffset + 0x1972EC) = *(u32 *)(lbl_2_bss_1A8240 + 0x118);
                    *(s16 *)(lbl_2_bss_1A824C + recordOffset + 0x1972F0) = *(s16 *)(lbl_2_bss_1A8240 + 0x11C);
                    *(s16 *)(lbl_2_bss_1A824C + recordOffset + 0x1972F2) = *(s16 *)(lbl_2_bss_1A8240 + 0x11E);
                    *(u32 *)(lbl_2_bss_1A824C + recordOffset + 0x1972F4) = *(u32 *)(lbl_2_bss_1A8240 + 0x120);
                    *(s16 *)(lbl_2_bss_1A824C + recordOffset + 0x1972F8) = *(s16 *)(lbl_2_bss_1A8240 + 0x124);
                    *(s16 *)(lbl_2_bss_1A824C + recordOffset + 0x1972FA) = *(s16 *)(lbl_2_bss_1A8240 + 0x126);
                    *(u32 *)(lbl_2_bss_1A824C + recordOffset + 0x1972FC) = *(u32 *)(lbl_2_bss_1A8240 + 0x128);
                    *(s16 *)(lbl_2_bss_1A824C + recordOffset + 0x197300) = *(s16 *)(lbl_2_bss_1A8240 + 0x12C);
                    *(s16 *)(lbl_2_bss_1A824C + recordOffset + 0x197302) = *(s16 *)(lbl_2_bss_1A8240 + 0x12E);
                    *(u32 *)(lbl_2_bss_1A824C + recordOffset + 0x197304) = *(u32 *)(lbl_2_bss_1A8240 + 0x130);
                    *(s16 *)(lbl_2_bss_1A824C + recordOffset + 0x197308) = *(s16 *)(lbl_2_bss_1A8240 + 0x134);
                    *(s16 *)(lbl_2_bss_1A824C + recordOffset + 0x19730A) = *(s16 *)(lbl_2_bss_1A8240 + 0x136);
                    *(u32 *)(lbl_2_bss_1A824C + recordOffset + 0x19730C) = *(u32 *)(lbl_2_bss_1A8240 + 0x138);
                    *(s16 *)(lbl_2_bss_1A824C + recordOffset + 0x197310) = *(s16 *)(lbl_2_bss_1A8240 + 0x13C);
                    *(s16 *)(lbl_2_bss_1A824C + recordOffset + 0x197312) = *(s16 *)(lbl_2_bss_1A8240 + 0x13E);
                } else {
                    for (fieldOffset = 0; fieldOffset < 0x28; fieldOffset += 8) {
                        *(u32 *)recordCopyDestination(fieldOffset, recordOffset, 0x1972EC) =
                            *(u32 *)(lbl_2_bss_1A8240 + lbl_2_data_20C48[i] * 0x28 + fieldOffset + 0x28);
                        *(s16 *)recordCopyDestination(fieldOffset, recordOffset, 0x1972F0) =
                            *(s16 *)(lbl_2_bss_1A8240 + lbl_2_data_20C48[i] * 0x28 + fieldOffset + 0x2C);
                        *(s16 *)recordCopyDestination(fieldOffset, recordOffset, 0x1972F2) =
                            *(s16 *)(lbl_2_bss_1A8240 + lbl_2_data_20C48[i] * 0x28 + fieldOffset + 0x2E);
                    }
                }
                i++;
                recordOffset += 0x28;
            } while (i < 7);
        }
        *(u32 *)(lbl_2_bss_1A824C + 0x1972C4) = *(u32 *)(lbl_2_bss_1A8240 + 0x0);
        *(s16 *)(lbl_2_bss_1A824C + 0x1972CA) = *(s16 *)(lbl_2_bss_1A8240 + 0x6);
        *(u32 *)(lbl_2_bss_1A824C + 0x1972CC) = *(u32 *)(lbl_2_bss_1A8240 + 0x8);
        *(s16 *)(lbl_2_bss_1A824C + 0x1972D2) = *(s16 *)(lbl_2_bss_1A8240 + 0xE);
        *(u32 *)(lbl_2_bss_1A824C + 0x1972D4) = *(u32 *)(lbl_2_bss_1A8240 + 0x10);
        *(s16 *)(lbl_2_bss_1A824C + 0x1972DA) = *(s16 *)(lbl_2_bss_1A8240 + 0x16);
        *(u32 *)(lbl_2_bss_1A824C + 0x1972DC) = *(u32 *)(lbl_2_bss_1A8240 + 0x18);
        *(s16 *)(lbl_2_bss_1A824C + 0x1972E2) = *(s16 *)(lbl_2_bss_1A8240 + 0x1E);
        *(u32 *)(lbl_2_bss_1A824C + 0x1972E4) = *(u32 *)(lbl_2_bss_1A8240 + 0x20);
        *(s16 *)(lbl_2_bss_1A824C + 0x1972EA) = *(s16 *)(lbl_2_bss_1A8240 + 0x26);
        g_d_GameSettings.StadiumID = STADIUM_ID_MARIO_STADIUM;
        WB(0x197863) = stats->playerNumberByPort[0];
        fn_8000F4B8(0, -1, -1, -1);
        WCH(0x32) = 0;
        break;

    case 1:
        d = insertGraphicDrawingFunction(fn_2_5ED3C, 2);
        NODE_U8(d, 0x28) = 0;
        item->state = 0;
        menuControlVariables->currentState = 2;
        break;

    case 2:
        if (item->state == 1) {
            menuControlVariables->currentState = 3;
        }
        break;

    case 3:
        WA(0x162992) = 0;
        menuNumber[0] = 0x53;
        insertGraphicDrawingFunction(fn_80053FE8, 0);
        d = insertGraphicDrawingFunction(fn_2_5AE54, 0);
        NODE_U16(d, 0x1C) = 0;
        NODE_U16(d, 0x1E) = 0;
        fn_2_54354(lbl_2_data_268A8, 0x2E0);
        WA(0x162604) = 1;
        WA(0x162605) = 1;
        fn_2_6ACF4();
        insertGraphicDrawingFunction(fn_2_71F60, 2);
        {
            f32 zero = 0.0f;
            Vec v;
            v.z = zero;
            v.y = zero;
            v.x = zero;
            fn_2_6AB3C(0, &v);
        }
        fn_2_72054(0, 0);
        fn_2_904A8();
        insertGraphicDrawingFunction(fn_2_9257C, 2);
        for (i = 0; i < *(u16 *)(lbl_2_bss_340140 + 0x3078); i++) {
            fn_2_903A8(i);
            fn_2_92654(i, 0);
        }
        insertGraphicDrawingFunction(fn_2_5DC5C, 2);
        item->state = 0;
        *(u16 *)(lbl_2_bss_1A824C + 0x197730) = 0;
        *(u16 *)(lbl_2_bss_1A824C + 0x197732) = 0;
        menuControlVariables->currentState = 4;
        break;

    case 4:
        menuControlVariables->currentState = 5;
        break;

    case 5:
        changeScene(1, 6);
        menuControlVariables->currentState = 6;
        break;

    case 6:
        if (lbl_8037169C[0x12] != 0) {
            menuControlVariables->currentState = 7;
        }
        break;

    case 7:
        if (item->state == 1) {
            menuNumber[5] = 1;
            WA(0x162992) = 1;
            lbl_2_bss_1A824C[0x32A86] = 1;
            menuControlVariables->currentState = 8;
        }
        break;

    case 8:
        lbl_2_bss_1A824C[0x1972BC] = 1;
        lbl_2_bss_1A824C[0x1972C0] = 1;
        resetGameStadiumStateOnExit();
        fn_80035B50(10);
        if (*(void **)((u8 *)screenTextArray + 0x7A0) != NULL) {
            fn_800ACFB0(*(void **)((u8 *)screenTextArray + 0x7A0));
            *(void **)((u8 *)screenTextArray + 0x7A0) = NULL;
        }
        lbl_2_bss_1A823C[0x34] = 0;
        menuControlVariables->currentState = 0;
        changeScreenVariables(5);
        WCH(0x32) = 0;
        break;
    }
}

// .text:0x0005DC5C size:0x4A8 mapped:0x8069CCF0
void fn_2_5DC5C(void) {
    DrawingSceneStruct *item = currentDrawingItem;

    switch (WCH(0x32)) {
    case 0:
        SET_MENU(0x53);
        WCH(0x32) = 1;
        break;

    case 1:
        WA(0x16264A) = 1;
        WA(0x16264B) = 1;
        WAH(0x162600) = 0x10;
        WCH(0x32) = 2;
        break;

    case 2:
        if (WAH(0x162600)-- == 0) {
            WCH(0x32) = 3;
        }
        break;

    case 3: {
        s8 idx = (s8)WB(0x197863);
        u16 pad4 = PADH(idx, 0x4);
        s16 cursor;

        if (pad4 & 0x8) {
            cursor = WBH(0x1976FE);
            WBH(0x1976FE) = (cursor + 3) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (pad4 & 0x4) {
            cursor = WBH(0x1976FE);
            WBH(0x1976FE) = (cursor + 1) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }

        if (PADH(idx, 0x2) & 0x100) {
            WCH(0x32) = 4;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (PADH(idx, 0x2) & 0x200) {
            WCH(0x32) = 6;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    }

    case 4:
        WA(0x162834) = 1;
        WA(0x162835) = 1;
        WAH(0x162600) = 0x10;
        WCH(0x32) = 5;
        break;

    case 5:
        if (WAH(0x162600)-- == 0) {
            WA(0x16264C) = 1;
            switch (WBH(0x1976FE)) {
            case 0:
                WBH(0x197730) = 5;
                currentDrawingItem->func = fn_2_5A224;
                break;
            case 1:
                WBH(0x197730) = 0;
                currentDrawingItem->func = fn_2_5D26C;
                break;
            case 2:
                WBH(0x197730) = 2;
                currentDrawingItem->func = fn_2_5C5B8;
                break;
            case 3:
                WBH(0x197730) = 3;
                currentDrawingItem->func = fn_2_5AFB0;
                break;
            }
            WCH(0x32) = 0;
        }
        break;

    case 6:
        WA(0x162834) = 1;
        WA(0x162835) = 1;
        WAH(0x162600) = 0x10;
        WCH(0x32) = 7;
        break;

    case 7:
        if (WAH(0x162600)-- == 0) {
            changeScene(3, 6);
            WCH(0x32) = 8;
        }
        break;

    case 8:
        if (lbl_8037169C[0x13] != 0) {
            WCH(0x32) = 9;
        }
        break;

    case 9:
        NODE_S16(item->currentDrawingItem, 0x10) = 1;
        removeCurrentDrawingItem();
        WCH(0x32) = 0;
        break;

    case 10: {
        DrawingSceneStruct *d = insertGraphicDrawingFunction(fn_2_587F8, 2);
        NODE_U8(d, 0x28) = 0;
        NODE_S16(item, 0x10) = 0;
        WCH(0x32) = 11;
        break;
    }

    case 11:
        if (NODE_S16(item, 0x10) == 1) {
            WCH(0x32) = 3;
        }
        break;
    }
}

// .text:0x0005D26C size:0x9F0 mapped:0x8069C300
void fn_2_5D26C(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    DrawingSceneStruct *d;
    u16 count;
    s8 idx;
    u16 pad;
    s16 v;
    s32 i;

    switch (WCH(0x32)) {
    case 0:
        resetGameStadiumStateOnExit();
        WB(0x197848) = 2;
        WBH(0x197702) = 0;
        d = insertGraphicDrawingFunction(fn_2_8DFB0, 2);
        NODE_U8(d, 0x28) = 0;
        NODE_U16(d, 0x16) = 0;
        item->state = 0;
        WCH(0x32) = 1;
        break;

    case 1:
        if (item->state == 1) {
            fn_2_94854(1);
            fn_2_9461C(-1);
            fn_2_94604(0);
            fn_2_93C64();
            WCH(0x32) = 2;
        }
        break;

    case 2:
        WCH(0x32) = 3;
        break;

    case 3:
        WCH(0x32) = 4;
        break;

    case 4:
        WA(0x16264D) = 1;
        SET_MENU(0x55);
        WAH(0x162600) = 0x10;
        WCH(0x32) = 8;
        break;

    case 5:
        WBH(0x197702) = 0;
        d = insertGraphicDrawingFunction(fn_2_8DFB0, 2);
        NODE_U8(d, 0x28) = 0;
        NODE_U16(d, 0x16) = 0;
        item->state = 0;
        WCH(0x32) = 6;
        break;

    case 6:
        if (item->state == 1) {
            fn_2_94854(1);
            fn_2_9461C(-1);
            fn_2_94604(0);
            fn_2_93C64();
            WCH(0x32) = 7;
        }
        break;

    case 7:
        WA(0x16264D) = 1;
        SET_MENU(0x55);
        WAH(0x162600) = 0x12;
        WCH(0x32) = 8;
        break;

    case 8:
        if (WAH(0x162600) == 0xE) {
            for (i = 0; i < *(u16 *)(lbl_2_bss_340140 + 0x3078); i++) {
                if (lbl_2_bss_33FBF0[i] == 1) {
                    fn_2_903A8(i);
                    fn_2_92654(i, 0xD);
                }
            }
        }
        if (WAH(0x162600)-- == 0) {
            WCH(0x32) = 9;
        }
        break;

    case 9:
        idx = (s8)WB(0x197863);
        pad = PADH(idx, 0x2);
        if (pad & 0x40) {
            WBH(0x197730) = 6;
            WA(0x162908) = 1;
            WA(0x162837) = 1;
            WCH(0x32) = 10;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (pad & 0x20) {
            WBH(0x197730) = 6;
            WA(0x16294E) = 1;
            WA(0x162837) = 1;
            WCH(0x32) = 10;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (pad & 0x200) {
            WBH(0x1976FE) = 0;
            WCH(0x32) = 12;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;

    case 10:
        count = *(u16 *)(lbl_2_bss_340140 + 0x3078);
        for (i = 0; i < count; i++) {
            fn_2_92654(i, 0);
        }
        WCH(0x32) = 11;
        break;

    case 11:
        fn_2_4E7EC();
        currentDrawingItem->func = fn_2_5CB5C;
        WCH(0x32) = 1;
        break;

    case 12:
        WA(0x16264E) = 1;
        WAH(0x162600) = 0x10;
        WCH(0x32) = 13;
        break;

    case 13:
        if (WAH(0x162600)-- == 0) {
            WCH(0x32) = 14;
        }
        break;

    case 14:
        idx = (s8)WB(0x197863);
        pad = PADH(idx, 0x4);
        if (pad & 0x8) {
            WBH(0x1976FE) = (WBH(0x1976FE) + 3) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (pad & 0x4) {
            WBH(0x1976FE) = (WBH(0x1976FE) + 1) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }

        pad = PADH(idx, 0x2);
        if (pad & 0x100) {
            WCH(0x32) = (WBH(0x1976FE) == 1) ? 18 : 15;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (pad & 0x200) {
            WCH(0x32) = 20;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;

    case 15:
        WA(0x162837) = 1;
        WA(0x162838) = 1;
        count = *(u16 *)(lbl_2_bss_340140 + 0x3078);
        for (i = 0; i < count; i++) {
            fn_2_92654(i, 0);
        }
        WAH(0x162600) = 0x10;
        WCH(0x32) = 16;
        break;

    case 16:
        if (WAH(0x162600)-- == 0) {
            fn_2_4E7EC();
            WCH(0x32) = 17;
        }
        break;

    case 17:
        WA(0x1626D8) = 1;
        switch (WBH(0x1976FE)) {
        case 0:
            WBH(0x197730) = 5;
            currentDrawingItem->func = fn_2_5A224;
            break;
        case 2:
            WBH(0x197730) = 2;
            currentDrawingItem->func = fn_2_5C5B8;
            break;
        case 3:
            WBH(0x197730) = 3;
            currentDrawingItem->func = fn_2_5AFB0;
            break;
        }
        WCH(0x32) = 0;
        break;

    case 18:
        WA(0x162838) = 1;
        WAH(0x162600) = 0x10;
        WCH(0x32) = 19;
        break;

    case 19:
        if (WAH(0x162600)-- == 0) {
            WCH(0x32) = 9;
        }
        break;

    case 20:
        changeScene(3, 6);
        count = *(u16 *)(lbl_2_bss_340140 + 0x3078);
        for (i = 0; i < count; i++) {
            fn_2_92654(i, 0);
        }
        WA(0x162836) = 1;
        WA(0x162837) = 1;
        WA(0x162838) = 1;
        WA(0x162834) = 1;
        WA(0x162835) = 1;
        WAH(0x162600) = 0x10;
        WCH(0x32) = 21;
        break;

    case 21:
        if (WAH(0x162600)-- == 0) {
            fn_2_4E7EC();
            NODE_S16(item->currentDrawingItem, 0x10) = 1;
            removeCurrentDrawingItem();
            WCH(0x32) = 0;
        }
        break;

    case 22:
        d = insertGraphicDrawingFunction(fn_2_5979C, 2);
        NODE_U8(d, 0x28) = 0;
        item->state = 0;
        WCH(0x32) = 23;
        break;

    case 23:
        if (item->state == 1) {
            WCH(0x32) = 9;
            if (*(u8 *)(lbl_2_bss_340140 + 0x307A) == 3) {
                fn_2_8FD14();
                fn_2_8AEE0();
                fn_2_47FF8();
                fn_2_47CFC();
            }
        }
        break;
    }
}

// .text:0x0005CB5C size:0x710 mapped:0x8069BBF0
void fn_2_5CB5C(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    s8 idx;
    u16 pad;

    switch (WCH(0x32)) {
    case 0:
    case 1:
        WA(0x162655) = 1;
        SET_MENU(0x56);
        WCH(0x32) = 2;
        break;

    case 2:
        WBH(0x197702) = 0;
        WCH(0x32) = 3;
        break;

    case 3:
        idx = (s8)WB(0x197863);
        pad = PADH(idx, 0x2);
        if (pad & 0x40) {
            WBH(0x197730) = 0;
            WA(0x16283F) = 1;
            WA(0x162908) = 1;
            WCH(0x32) = 5;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (pad & 0x20) {
            WA(0x16283F) = 1;
            WBH(0x197730) = 0;
            WCH(0x32) = 5;
            WA(0x16294E) = 1;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        }
        break;

    case 4:
        if (WAH(0x162600)-- == 0) {
            WCH(0x32) = 3;
        }
        break;

    case 5:
        WCH(0x32) = 6;
        break;

    case 6:
        currentDrawingItem->func = fn_2_5D26C;
        WCH(0x32) = 5;
        break;

    case 7:
        WA(0x16264E) = 1;
        WAH(0x162600) = 0x32;
        WCH(0x32) = 8;
        break;

    case 8:
        if (WAH(0x162600)-- == 0) {
            WCH(0x32) = 9;
        }
        break;

    case 9:
        idx = (s8)WB(0x197863);
        pad = PADH(idx, 0x4);
        if (pad & 0x8) {
            WBH(0x1976FE) = (WBH(0x1976FE) + 3) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (pad & 0x4) {
            WBH(0x1976FE) = (WBH(0x1976FE) + 1) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }

        pad = PADH(idx, 0x2);
        if (pad & 0x100) {
            WCH(0x32) = (WBH(0x1976FE) == 1) ? 13 : 10;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (pad & 0x200) {
            WCH(0x32) = 15;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;

    case 10:
        WA(0x16283F) = 1;
        WA(0x162838) = 1;
        WAH(0x162600) = 0x32;
        WCH(0x32) = 11;
        break;

    case 11:
        if (WAH(0x162600)-- == 0) {
            WCH(0x32) = 12;
        }
        break;

    case 12:
        WA(0x1626D8) = 1;
        switch (WBH(0x1976FE)) {
        case 0:
            WBH(0x197730) = 5;
            currentDrawingItem->func = fn_2_5A224;
            break;
        case 2:
            WBH(0x197730) = 2;
            currentDrawingItem->func = fn_2_5C5B8;
            break;
        case 3:
            WBH(0x197730) = 3;
            currentDrawingItem->func = fn_2_5AFB0;
            break;
        }
        WCH(0x32) = 0;
        break;

    case 13:
        WA(0x162838) = 1;
        WAH(0x162600) = 0x10;
        WCH(0x32) = 14;
        break;

    case 14:
        if (WAH(0x162600)-- == 0) {
            WCH(0x32) = 3;
        }
        break;

    case 15:
        changeScene(3, 6);
        WA(0x16283F) = 1;
        WA(0x162836) = 1;
        WA(0x162838) = 1;
        WA(0x162834) = 1;
        WA(0x162835) = 1;
        WAH(0x162600) = 0x32;
        WCH(0x32) = 16;
        break;

    case 16:
        if (WAH(0x162600)-- == 0) {
            NODE_S16(item->currentDrawingItem, 0x10) = 1;
            removeCurrentDrawingItem();
            WCH(0x32) = 0;
        }
        break;
    }
}

// .text:0x0005C5B8 size:0x5A4 mapped:0x8069B64C
void fn_2_5C5B8(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    s8 idx;
    u16 pad;

    switch (WCH(0x32)) {
    case 0:
        WA(0x162650) = 1;
        SET_MENU(0x57);
        WCH(0x32) = 1;
        break;

    case 1:
        WBH(0x1976FA) = 0;
        WCH(0x32) = 2;
        break;

    case 2:
        idx = (s8)WB(0x197863);
        if (PADH(idx, 0x2) & 0x200) {
            WBH(0x1976FE) = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            WCH(0x32) = 5;
        }
        break;

    case 5:
        WA(0x16264E) = 1;
        WAH(0x162600) = 0x10;
        WCH(0x32) = 6;
        break;

    case 6:
        if (WAH(0x162600)-- == 0) {
            WCH(0x32) = 7;
        }
        break;

    case 7:
        idx = (s8)WB(0x197863);
        pad = PADH(idx, 0x4);
        if (pad & 0x8) {
            WBH(0x1976FE) = (WBH(0x1976FE) + 3) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (pad & 0x4) {
            WBH(0x1976FE) = (WBH(0x1976FE) + 1) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }

        pad = PADH(idx, 0x2);
        if (pad & 0x100) {
            WCH(0x32) = (WBH(0x1976FE) == 2) ? 11 : 8;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (pad & 0x200) {
            WCH(0x32) = 13;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;

    case 8:
        WA(0x16283A) = 1;
        WA(0x162838) = 1;
        WAH(0x162600) = 0x10;
        WCH(0x32) = 9;
        break;

    case 9:
        if (WAH(0x162600)-- == 0) {
            WCH(0x32) = 10;
        }
        break;

    case 10:
        WA(0x1626D8) = 1;
        switch (WBH(0x1976FE)) {
        case 0:
            WBH(0x197730) = 5;
            currentDrawingItem->func = fn_2_5A224;
            break;
        case 1:
            WBH(0x197730) = 0;
            currentDrawingItem->func = fn_2_5D26C;
            break;
        case 2:
            WBH(0x197730) = 2;
            WCH(0x32) = 11;
            break;
        case 3:
            WBH(0x197730) = 3;
            currentDrawingItem->func = fn_2_5AFB0;
            break;
        }
        WCH(0x32) = 0;
        break;

    case 11:
        WA(0x162838) = 1;
        WAH(0x162600) = 0x10;
        WCH(0x32) = 12;
        break;

    case 12:
        if (WAH(0x162600)-- == 0) {
            WCH(0x32) = 2;
        }
        break;

    case 13:
        changeScene(3, 6);
        WA(0x16283A) = 1;
        WA(0x162836) = 1;
        WA(0x162838) = 1;
        WA(0x162834) = 1;
        WA(0x162835) = 1;
        WAH(0x162600) = 0x10;
        WCH(0x32) = 14;
        break;

    case 14:
        if (WAH(0x162600)-- == 0) {
            NODE_S16(item->currentDrawingItem, 0x10) = 1;
            removeCurrentDrawingItem();
            WCH(0x32) = 0;
        }
        break;
    }
}

// .text:0x0005B7DC size:0xDDC mapped:0x8069A870
void fn_2_5B7DC(void) {
    s8 idx;
    u16 pad;

    switch (WCH(0x32)) {
    case 0:
        WBH(0x197706) = 0;
        WBH(0x197708) = 1;
        WBH(0x19770A) = 0;
        WA(0x16264F) = TRUE;
        SET_MENU(0x58);
        WCH(0x32) = 1;
        break;
    case 1:
        WCH(0x32) = 2;
        break;
    case 2:
        updateRecordGridCursor();
        idx = (s8)WB(0x197863);
        pad = PADH(idx, 0x2);
        if (pad & INPUT_TRIGGER_L) {
            WBH(0x197730) = 3;
            WCH(0x32) = 3;
            WA(0x162908) = TRUE;
            WA(0x162839) = TRUE;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (pad & INPUT_TRIGGER_R) {
            WBH(0x197730) = 3;
            WCH(0x32) = 3;
            WA(0x16294E) = TRUE;
            WA(0x162839) = TRUE;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (pad & INPUT_BUTTON_A) {
            if (lbl_2_bss_1A8240[WBH(0x197706) * 0x16 + 0x153] > 0) {
                WAH(0x162600) = 10;
                WA(0x162656) = TRUE;
                copySelectedRecord();
                WCH(0x32) = 13;
                sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
            } else {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            }
        } else if (pad & INPUT_BUTTON_B) {
            WBH(0x1976FE) = 0;
            WCH(0x32) = 5;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    case 3:
        WCH(0x32) = 4;
        WAH(0x162600) = 0x24;
        break;
    case 4:
        if (WAH(0x162600)-- == 0) {
            currentDrawingItem->func = fn_2_5AFB0;
            WCH(0x32) = 0;
        }
        break;
    case 5:
        WA(0x16264E) = TRUE;
        WAH(0x162600) = 0x10;
        WCH(0x32) = 6;
        break;
    case 6:
        if (WAH(0x162600)-- == 0) WCH(0x32) = 7;
        break;
    case 7:
        idx = (s8)WB(0x197863);
        pad = PADH(idx, 0x4);
        if (pad & INPUT_BUTTON_UP) {
            WBH(0x1976FE) = (WBH(0x1976FE) + 3) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (pad & INPUT_BUTTON_DOWN) {
            WBH(0x1976FE) = (WBH(0x1976FE) + 1) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        idx = (s8)WB(0x197863);
        pad = PADH(idx, 0x2);
        if (pad & INPUT_BUTTON_A) {
            WCH(0x32) = WBH(0x1976FE) == 3 ? 11 : 8;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (pad & INPUT_BUTTON_B) {
            WCH(0x32) = 17;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    case 8:
        WA(0x162838) = TRUE;
        WA(0x162839) = TRUE;
        WAH(0x162600) = 0x24;
        WCH(0x32) = 9;
        break;
    case 9:
        if (WAH(0x162600)-- == 0) WCH(0x32) = 10;
        break;
    case 10:
        WA(0x1626D8) = TRUE;
        switch (WBH(0x1976FE)) {
        case 0:
            WBH(0x197730) = 5;
            currentDrawingItem->func = fn_2_5A224;
            break;
        case 1:
            WBH(0x197730) = 0;
            currentDrawingItem->func = fn_2_5D26C;
            break;
        case 2:
            WBH(0x197730) = 2;
            currentDrawingItem->func = fn_2_5C5B8;
            break;
        case 3:
            WBH(0x197730) = 4;
            WCH(0x32) = 11;
            break;
        }
        WCH(0x32) = 0;
        break;
    case 11:
        WA(0x162838) = TRUE;
        WAH(0x162600) = 0x10;
        WCH(0x32) = 12;
        break;
    case 12:
        if (WAH(0x162600)-- == 0) WCH(0x32) = 2;
        break;
    case 13:
        if (WAH(0x162600)-- == 0) WCH(0x32) = 14;
        break;
    case 14:
        idx = (s8)WB(0x197863);
        pad = PADH(idx, 0x2);
        if (pad & INPUT_BUTTON_A) {
            WAH(0x162600) = 4;
            WA(0x162840) = TRUE;
            WCH(0x32) = 15;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (pad & INPUT_BUTTON_B) {
            WAH(0x162600) = 4;
            WA(0x162840) = TRUE;
            WCH(0x32) = 15;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    case 15:
        if (WAH(0x162600)-- == 0) WCH(0x32) = 2;
        break;
    case 16:
        break;
    case 17:
        changeScene(3, 6);
        WA(0x162839) = TRUE;
        WA(0x162836) = TRUE;
        WA(0x162838) = TRUE;
        WA(0x162834) = TRUE;
        WA(0x162835) = TRUE;
        WAH(0x162600) = 0x24;
        WCH(0x32) = 18;
        break;
    case 18:
        if (WAH(0x162600)-- == 0) {
            currentDrawingItem->currentDrawingItem->state = 1;
            removeCurrentDrawingItem();
            WCH(0x32) = 0;
        }
        break;
    }
}

// .text:0x0005AFB0 size:0x82C mapped:0x8069A044
void fn_2_5AFB0(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    s8 idx;
    u16 pad;
    s16 v;
    s16 n;

    switch (WCH(0x32)) {
    case 0:
        WA(0x162651) = 1;
        SET_MENU(0x59);
        WAH(0x162600) = 0x10;
        WBH(0x1976FA) = 0;
        WA(0x162652) = 1;
        WBH(0x19772E) = 7;
        WCH(0x32) = 1;
        break;

    case 1:
        if (WAH(0x162600)-- == 0) {
            WCH(0x32) = 2;
        }
        break;

    case 2:
        idx = (s8)WB(0x197863);
        pad = PADH(idx, 0x4);
        v = WBH(0x1976FA);
        n = WBH(0x19772E);
        if (pad & 0x1) {
            WBH(0x1976FA) = (v + n - 1) % n;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            WA(0x1627AF) = 1;
            WA(0x1627B0) = 1;
            WCH(0x32) = 3;
        } else if (pad & 0x2) {
            WBH(0x1976FA) = (v + 1) % n;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            WA(0x1627AF) = 1;
            WA(0x1627B0) = 1;
            WCH(0x32) = 3;
        } else {
            pad = PADH(idx, 0x2);
            if (pad & 0x40) {
                WBH(0x197730) = 4;
                WA(0x162908) = 1;
                WCH(0x32) = 5;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            } else if (pad & 0x20) {
                WBH(0x197730) = 4;
                WA(0x16294E) = 1;
                WCH(0x32) = 5;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            } else if (pad & 0x200) {
                WBH(0x1976FE) = 0;
                WCH(0x32) = 7;
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            }
        }
        break;

    case 3:
        WCH(0x32) = 4;
        break;

    case 4:
        WCH(0x32) = 2;
        break;

    case 5:
        WA(0x16283B) = 1;
        WA(0x16283C) = 1;
        WCH(0x32) = 6;
        break;

    case 6:
        currentDrawingItem->func = fn_2_5B7DC;
        WCH(0x32) = 0;
        break;

    case 7:
        WA(0x16264E) = 1;
        WAH(0x162600) = 0x10;
        WCH(0x32) = 8;
        break;

    case 8:
        if (WAH(0x162600)-- == 0) {
            WCH(0x32) = 9;
        }
        break;

    case 9:
        idx = (s8)WB(0x197863);
        pad = PADH(idx, 0x4);
        if (pad & 0x8) {
            WBH(0x1976FE) = (WBH(0x1976FE) + 3) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (pad & 0x4) {
            WBH(0x1976FE) = (WBH(0x1976FE) + 1) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }

        pad = PADH(idx, 0x2);
        if (pad & 0x100) {
            WCH(0x32) = (WBH(0x1976FE) == 3) ? 13 : 10;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (pad & 0x200) {
            WCH(0x32) = 15;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;

    case 10:
        WA(0x16283B) = 1;
        WA(0x162838) = 1;
        WA(0x16283C) = 1;
        WAH(0x162600) = 0x10;
        WCH(0x32) = 11;
        break;

    case 11:
        if (WAH(0x162600)-- == 0) {
            WCH(0x32) = 12;
        }
        break;

    case 12:
        WA(0x1626D8) = 1;
        switch (WBH(0x1976FE)) {
        case 0:
            WBH(0x197730) = 5;
            currentDrawingItem->func = fn_2_5A224;
            break;
        case 1:
            WBH(0x197730) = 0;
            currentDrawingItem->func = fn_2_5D26C;
            break;
        case 2:
            WBH(0x197730) = 2;
            currentDrawingItem->func = fn_2_5C5B8;
            break;
        case 3:
            WBH(0x197730) = 4;
            break;
        }
        WCH(0x32) = 0;
        break;

    case 13:
        WA(0x162838) = 1;
        WAH(0x162600) = 0x10;
        WCH(0x32) = 14;
        break;

    case 14:
        if (WAH(0x162600)-- == 0) {
            WCH(0x32) = 2;
        }
        break;

    case 15:
        changeScene(3, 6);
        WA(0x16283B) = 1;
        WA(0x16283C) = 1;
        WA(0x162836) = 1;
        WA(0x162838) = 1;
        WA(0x162834) = 1;
        WA(0x162835) = 1;
        WAH(0x162600) = 0x10;
        WCH(0x32) = 0x10;
        break;

    case 16:
        if (WAH(0x162600)-- == 0) {
            NODE_S16(item->currentDrawingItem, 0x10) = 1;
            removeCurrentDrawingItem();
            WCH(0x32) = 0;
        }
        break;
    }
}

// .text:0x0005AF24 size:0x8C mapped:0x80699FB8
void fn_2_5AF24(void) {
    DrawingSceneStruct *item;

    menuNumber[0] = 0x53;
    insertGraphicDrawingFunction(fn_80053FE8, 0);
    item = insertGraphicDrawingFunction(fn_2_5AE54, 0);
    NODE_U16(item, 0x1C) = 0;
    NODE_U16(item, 0x1E) = 0;
    fn_2_54354(lbl_2_data_268A8, 0x2E0);
    WA(0x162604) = 1;
    WA(0x162605) = 1;
}

// .text:0x0005AE54 size:0xD0 mapped:0x80699EE8
void fn_2_5AE54(void) {
    DrawingSceneStruct *item = currentDrawingItem;

    switch (NODE_U16(item, 0x1C)) {
    case 0:
        fn_2_4E878(item, lbl_2_data_20C68);
        NODE_U16(item, 0x1C) = 1;
        NODE_U16(item, 0x18) = 0;
        break;
    case 1:
        break;
    }
    fn_2_53F88(item);
    fn_2_54120();
    if (WA(0x162992) != 0) {
        fn_2_53DF8(item);
        fn_8000F8F4(item);
        text_freeAllBlocks();
        fn_2_4E858(item);
        removeCurrentDrawingItem();
        NODE_U16(item, 0x1C) = 0;
        NODE_U16(item, 0x1E) = 0;
        WA(0x162992) = 0;
    }
}

// .text:0x0005A224 size:0xC30 mapped:0x806992B8
void fn_2_5A224(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    DrawingSceneStruct *child;
    s8 idx;
    u16 pad;

    switch (WCH(0x32)) {
    case 0:
        WB(0x197848) = 2;
        WA(0x162653) = 1;
        SET_MENU(0x54);
        WCH(0x32) = 1;
        break;
    case 1:
        WBH(0x197706) = 0;
        WBH(0x197708) = 1;
        WBH(0x19770A) = 0;
        fn_2_94854(lbl_2_data_35A0[WBH(0x197706)] + 2);
        fn_2_9461C(-1);
        fn_2_94604(0);
        fn_2_93C64();
        WCH(0x32) = 2;
        break;
    case 2:
        updateRecordGridCursor();
        idx = (s8)WB(0x197863);
        pad = PADH(idx, 0x2);
        if (pad & INPUT_BUTTON_A) {
            if (lbl_80354768[0xCF18 + lbl_800E869C[WBH(0x197706)]] != 0) {
                WAH(0x162600) = 0x10;
                sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
                WCH(0x32) = 13;
            } else {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            }
        } else if (pad & INPUT_BUTTON_B) {
            WBH(0x1976FE) = 0;
            WCH(0x32) = 5;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    case 5:
        WA(0x16264E) = 1;
        WAH(0x162600) = 0x10;
        WCH(0x32) = 6;
        break;
    case 6:
        if (WAH(0x162600)-- == 0) WCH(0x32) = 7;
        break;
    case 7:
        idx = (s8)WB(0x197863);
        pad = PADH(idx, 0x4);
        if (pad & INPUT_BUTTON_UP) {
            WBH(0x1976FE) = (WBH(0x1976FE) + 3) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (pad & INPUT_BUTTON_DOWN) {
            WBH(0x1976FE) = (WBH(0x1976FE) + 1) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        idx = (s8)WB(0x197863);
        pad = PADH(idx, 0x2);
        if (pad & INPUT_BUTTON_A) {
            WCH(0x32) = WBH(0x1976FE) == 0 ? 11 : 8;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (pad & INPUT_BUTTON_B) {
            WCH(0x32) = 22;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    case 8:
        WA(0x16283D) = 1;
        WA(0x162838) = 1;
        WAH(0x162600) = 0x24;
        WCH(0x32) = 9;
        break;
    case 9:
        if (WAH(0x162600)-- == 0) WCH(0x32) = 10;
        break;
    case 10:
        WA(0x1626D8) = 1;
        switch (WBH(0x1976FE)) {
        case 0:
            WBH(0x197730) = 5;
            WCH(0x32) = 11;
            break;
        case 1:
            WBH(0x197730) = 0;
            currentDrawingItem->func = fn_2_5D26C;
            break;
        case 2:
            WBH(0x197730) = 2;
            currentDrawingItem->func = fn_2_5C5B8;
            break;
        case 3:
            WBH(0x197730) = 3;
            currentDrawingItem->func = fn_2_5AFB0;
            break;
        }
        WCH(0x32) = 0;
        break;
    case 11:
        WA(0x162838) = 1;
        WAH(0x162600) = 0x10;
        WCH(0x32) = 12;
        break;
    case 12:
        if (WAH(0x162600)-- == 0) WCH(0x32) = 2;
        break;
    case 13:
        WCH(0x32) = 14;
        break;
    case 14:
        WBH(0x197746) = 1;
        child = insertGraphicDrawingFunction(fn_2_8E6A4, 2);
        NODE_U8(child, 0x28) = 0;
        NODE_S16(child, 0x16) = WBH(0x197706);
        item->state = 0;
        WCH(0x32) = 15;
        break;
    case 15:
        if (item->state == 1) WCH(0x32) = 16;
        break;
    case 16:
        WAH(0x162600) = 0x14;
        WA(0x162654) = 1;
        fn_2_94854(lbl_2_data_35A0[WBH(0x197706)] + 2);
        WCH(0x32) = 17;
        break;
    case 17:
        if (WAH(0x162600) == 0x10) fn_2_72054(0, 0x11);
        if (WAH(0x162600)-- == 0) WCH(0x32) = 18;
        break;
    case 18:
        idx = (s8)WB(0x197863);
        pad = PADH(idx, 0x2);
        if (pad & INPUT_BUTTON_A) {
            WAH(0x162600) = 0x14;
            WA(0x16283E) = 1;
            fn_2_72054(0, 0x12);
            WCH(0x32) = 19;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (pad & INPUT_BUTTON_B) {
            WAH(0x162600) = 0x14;
            WA(0x16283E) = 1;
            fn_2_72054(0, 0x12);
            WCH(0x32) = 19;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    case 19:
        if (WAH(0x162600)-- == 0) {
            fn_2_4E7EC();
            WCH(0x32) = 20;
        }
        break;
    case 20:
        WCH(0x32) = 21;
        break;
    case 21:
        fn_2_4E7EC();
        WCH(0x32) = 2;
        break;
    case 22:
        changeScene(3, 6);
        WA(0x16283D) = 1;
        WA(0x162836) = 1;
        WA(0x162838) = 1;
        WA(0x162834) = 1;
        WA(0x162835) = 1;
        WAH(0x162600) = 0x24;
        WCH(0x32) = 23;
        break;
    case 23:
        if (WAH(0x162600)-- == 0) {
            currentDrawingItem->currentDrawingItem->state = 1;
            removeCurrentDrawingItem();
            WCH(0x32) = 0;
        }
        break;
    case 24:
        child = insertGraphicDrawingFunction(fn_2_59CF8, 2);
        NODE_U8(child, 0x28) = 0;
        item->state = 0;
        WCH(0x32) = 25;
        break;
    case 25:
        if (item->state == 1) WCH(0x32) = 18;
        break;
    }
    if (hugeAnimStruct[0x307A] == 2) {
        fn_2_68E68();
        fn_2_47FF8();
        fn_2_47CFC();
    }
    GXSetZCompLoc(GX_FALSE);
}

// .text:0x00059CF8 size:0x52C mapped:0x80698D8C
void fn_2_59CF8(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    s8 sub = (s8)NODE_U8(item, 0x28);
    s32 slot;
    s8 idx;
    u16 pad;
    u8 *buf = lbl_80354768;
    int i;

    switch (sub) {
    case 0:
        WB32(0x1976A4) = 0;
        WB32(0x1976A0) = 0;
        NODE_U8(item, 0x28) = 1;
        break;

    case 1:
        fn_2_1FFC4(3);
        for (slot = 0; slot < 3; slot++) {
            fn_2_1FF10(slot);
            switch (slot) {
            case 0:
                if (WB32(0x1976A0) == slot) {
                    idx = (s8)WB(0x197863);
                    if ((PADH(idx, 0x2) & INPUT_BUTTON_A) || (s8)PADB(0, 0x13) > 0x32) {
                        NODE_U8(item, 0x28) = 3;
                    }
                }
                break;

            case 1:
                if (WB32(0x1976A0) == slot) {
                    idx = (s8)WB(0x197863);
                    if (PADH(idx, 0x2) & (INPUT_BUTTON_A | INPUT_BUTTON_RIGHT)) {
                        WB(0x19784A) = 1;
                        WB(0x197846) = 0;
                        WB(0x197845) = 1;
                        lbl_2_bss_A168 = 1;
                        NODE_U8(item, 0x28) = 2;
                    }
                }
                break;

            case 2:
                if (WB32(0x1976A0) == slot) {
                    idx = (s8)WB(0x197863);
                    if (PADH(idx, 0x2) & (INPUT_BUTTON_LEFT | INPUT_BUTTON_RIGHT)) {
                        if (buf[0xCF18] == 0) {
                            for (i = 0; i < (s32)NUM_CHOOSABLE_CHARACTERS; i++) {
                                buf[(s32)i + 0xCF18] = 1;
                            }
                        } else if (buf[0xCF18] == 1) {
                            for (i = 0; i < (s32)NUM_CHOOSABLE_CHARACTERS; i++) {
                                buf[(s32)i + 0xCF18] = 0;
                            }
                        }
                    }
                }
                break;
            }
        }

        idx = (s8)WB(0x197863);
        if ((PADH(idx, 0x2) & INPUT_BUTTON_B) || (s8)PADB(0, 0x13) > 0x32) {
            NODE_U8(item, 0x28) = 3;
        }
        break;

    case 2:
        fn_2_1FF14(1);
        for (slot = 0; slot < 1; slot++) {
            fn_2_1FF0C(slot);
            switch (slot) {
            case 0:
                if (WB32(0x1976A4) == slot) {
                    idx = (s8)WB(0x197863);
                    pad = PADH(idx, 0x2);
                    if (pad & INPUT_BUTTON_B) {
                        WB(0x19784A) = 0;
                        WB(0x197846) = 0;
                        WB32(0x1976A4) = 0;
                        WB(0x197845) = 0;
                        NODE_U8(item, 0x28) = 1;
                    } else {
                        if (pad & INPUT_BUTTON_A) {
                            lbl_2_bss_A168 ^= 1;
                        } else if (pad & INPUT_BUTTON_START) {
                            fn_2_93C64();
                        }
                    }
                    if ((s8)lbl_2_bss_A168 != 0) {
                        fn_2_489DC();
                    }
                }
                break;
            }
        }
        break;

    case 3:
        NODE_S16(item->currentDrawingItem, 0x10) = 1;
        removeCurrentDrawingItem();
        NODE_U8(item, 0x28) = 0;
        break;
    }
}

// .text:0x0005979C size:0x55C mapped:0x80698830
void fn_2_5979C(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    s8 sub = (s8)NODE_U8(item, 0x28);
    s32 slot;
    s8 idx;
    u16 pad;

    switch (sub) {
    case 0:
        WB32(0x1976A4) = 0;
        WB32(0x1976A0) = 0;
        NODE_U8(item, 0x28) = 1;
        break;

    case 1:
        fn_2_1FFC4(4);
        for (slot = 0; slot < 4; slot++) {
            fn_2_1FF10(slot);
            switch (slot) {
            case 0:
                if (WB32(0x1976A0) == slot) {
                    idx = (s8)WB(0x197863);
                    if ((PADH(idx, 0x2) & INPUT_BUTTON_A) || (s8)PADB(0, 0x13) > 0x32) {
                        NODE_U8(item, 0x28) = 4;
                    }
                }
                break;

            case 1:
                if (WB32(0x1976A0) == slot) {
                    idx = (s8)WB(0x197863);
                    if (PADH(idx, 0x2) & (INPUT_BUTTON_A | INPUT_BUTTON_RIGHT)) {
                        WB(0x19784A) = 1;
                        WB(0x197846) = 0;
                        WB(0x197845) = 1;
                        lbl_2_bss_A169 = 1;
                        NODE_U8(item, 0x28) = 2;
                    }
                }
                break;

            case 2:
                if (WB32(0x1976A0) == slot) {
                    idx = (s8)WB(0x197863);
                    if (PADH(idx, 0x2) & (INPUT_BUTTON_A | INPUT_BUTTON_RIGHT)) {
                        WB(0x19784A) = 1;
                        WB(0x197846) = 2;
                        NODE_U8(item, 0x28) = 3;
                    }
                }
                break;

            case 3:
                if (WB32(0x1976A0) == slot) {
                    idx = (s8)WB(0x197863);
                    if (PADH(idx, 0x2) & (INPUT_BUTTON_A | INPUT_BUTTON_RIGHT)) {
                        lbl_2_bss_1A8244[0xF4] ^= 1;
                        fn_2_5EB78();
                    }
                }
                break;
            }
        }

        idx = (s8)WB(0x197863);
        if ((PADH(idx, 0x2) & INPUT_BUTTON_B) || (s8)PADB(0, 0x13) > 0x32) {
            NODE_U8(item, 0x28) = 4;
        }
        break;

    case 2:
        fn_2_1FF14(1);
        for (slot = 0; slot < 1; slot++) {
            fn_2_1FF0C(slot);
            switch (slot) {
            case 0:
                if (WB32(0x1976A4) == slot) {
                    idx = (s8)WB(0x197863);
                    pad = PADH(idx, 0x2);
                    if (pad & INPUT_BUTTON_B) {
                        WB(0x19784A) = 0;
                        WB(0x197846) = 0;
                        WB32(0x1976A4) = 0;
                        WB(0x197845) = 0;
                        NODE_U8(item, 0x28) = 1;
                    } else if (pad & INPUT_BUTTON_A) {
                        lbl_2_bss_A169 ^= 1;
                    } else if (pad & INPUT_BUTTON_START) {
                        fn_2_93C64();
                    }
                    if ((s8)lbl_2_bss_A169 != 0) {
                        fn_2_489DC();
                    }
                }
                break;
            }
        }
        break;

    case 3:
        fn_2_1FF14(1);
        for (slot = 0; slot < 1; slot++) {
            fn_2_1FF0C(slot);
            switch (slot) {
            case 0:
                if (WB32(0x1976A4) == slot) {
                    idx = (s8)WB(0x197863);
                    pad = PADH(idx, 0x2);
                    if (pad & INPUT_BUTTON_B) {
                        WB(0x19784A) = 0;
                        WB(0x197846) = 0;
                        WB32(0x1976A4) = 0;
                        NODE_U8(item, 0x28) = 1;
                    } else if ((pad & INPUT_TRIGGER_L) && (PADH(idx, 0x0) & INPUT_BUTTON_A)) {
                        WBH(0x1972BE) = (WBH(0x1972BE) + 28) % 29;
                    } else if ((pad & INPUT_TRIGGER_R) && (PADH(idx, 0x0) & INPUT_BUTTON_A)) {
                        WBH(0x1972BE) = (WBH(0x1972BE) + 1) % 29;
                    } else if (PADH(idx, 0x4) & INPUT_BUTTON_Y) {
                        *(f32 *)(lbl_2_bss_1A8248 + WBH(0x1972BE) * 0xBC + 0x2208) -= 0.1f;
                    } else if (PADH(idx, 0x4) & INPUT_BUTTON_X) {
                        *(f32 *)(lbl_2_bss_1A8248 + WBH(0x1972BE) * 0xBC + 0x2208) += 0.1f;
                    }
                }
                break;
            }
        }
        break;

    case 4:
        NODE_S16(item->currentDrawingItem, 0x10) = 1;
        removeCurrentDrawingItem();
        NODE_U8(item, 0x28) = 0;
        break;
    }
}
