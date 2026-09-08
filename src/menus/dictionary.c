#include "menus/dictionary.h"
#include "header_rep_data.h"
#include "Unknown/File_0x800b0a14.h"
#include "static/UnknownHomes_Static.h"
#include "text/text_channel.h"
#include "menus/yd_step.h"
#include "Dolphin/vec.h"
#include "Dolphin/mtx.h"
#include "musyx/musyx.h"
#include "Dolphin/gx.h"
#include <string.h>

extern u8 *lbl_2_bss_1A8230;
extern u8 *lbl_2_bss_1A8234;
extern u8 *lbl_2_bss_1A823C;
extern u8 *lbl_2_bss_1A8244;
extern u8 *lbl_2_bss_1A8248;
extern u8 *lbl_2_bss_1A824C;
extern u8 lbl_2_bss_1A8250[0x1978FC];
extern u8 lbl_2_data_1F8F0[];
extern u8 starMissionCompletionTracker[0x4508];
extern u8 superstarUnlocked[0x130];
extern u8 menuNumber[0x28];
extern menuControlStruct *menuControlVariables;
extern u8 lbl_800EFBA4[0x10];
extern u8 lbl_800FEF70[0x5D0];
extern u8 lbl_8037169C[0x1C];
extern u8 lbl_800EF808[0x39C];

/* HugeAnimStruct isn't typed in a shared header; only the one byte we need
 * is accessed here. */
extern u8 hugeAnimStruct[0x3154];

extern void fn_8000F4B8(int arg0, int arg1, int arg2, int arg3);
extern void fn_2_54474(void);
extern void fn_2_94854(void);
extern void fn_2_9461C(void);
extern void fn_2_94604(void);
extern void fn_2_93C64(void);
extern void fn_2_549B4(void);
extern void fn_8006295C(void);
extern void fn_2_6ACF4(void);
extern void fn_2_71F60(void);
extern void fn_2_6AB3C(int arg0, Vec *arg1);
extern void fn_2_72054(s32 arg0, s32 arg1);
extern void fn_80053FE8(void);
extern void fn_2_5389C(void);
extern void fn_2_46D94(s16 *arg0, s16 *arg1, s16 arg2, int arg3, int arg4);
extern s16 fn_2_5597C(void);
extern void fn_2_535B0(void);
extern void fn_80062948(void);
extern void changeScene(u8 scene, u16 arg1);
extern void fn_2_68E68(void);
extern void fn_2_47FF8(void);
extern void fn_2_47CFC(void);
extern void fn_2_4E7EC(void);
extern void resetGameStadiumStateOnExit(void);
extern void maybeLoadsGameSoundFiles(void);
extern void fn_800ACFB0(void *arg0);
extern void fn_80035B50(int arg0);
extern void changeScreenVariables(u16 screen);

typedef struct {
    /* 0x0 */ void (*func)(void);
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ s16 unk8;
    /* 0xA */ s16 unkA;
    /* 0xC */ s16 unkC;
    /* 0xE */ s16 unkE;
} MenuRowDef;

#define WA(off)  (lbl_2_bss_1A8234[(off)])
#define WAH(off) (*(s16 *)&lbl_2_bss_1A8234[(off)])
#define WB(off)  (lbl_2_bss_1A824C[(off)])
#define WBH(off) (*(s16 *)&lbl_2_bss_1A824C[(off)])
#define WD(off)  (w[(off)])
#define WDH(off) (*(s16 *)&w[(off)])
#define TBL16(off) (*(s16 *)&tbl[(off)])
#define PADB(i, off) (*(u8  *)((u8 *)&AtBat_ButtonInput1 + (i) * 0x20 + (off)))
#define PADH(i, off) (*(u16 *)((u8 *)&AtBat_ButtonInput1 + (i) * 0x20 + (off)))

void fn_2_54BB0(void) {
    u8 *w;
    const u8 *tbl;
    Static_MSSB_Data *st;
    DrawingSceneStruct *item;
    DrawingSceneStruct *d;
    const MenuRowDef *rows;
    u8 *dst;
    int i;
    s16 n;
    u16 buttons;
    Vec v;

    w = lbl_2_bss_1A8250;
    tbl = lbl_2_data_1F8F0;
    st = &Static_Stats_Tables;
    lbl_2_bss_1A8230 = &w[0x162998];
    lbl_2_bss_1A8234 = w;
    lbl_2_bss_1A823C = (u8 *)&inningSetting.rel;
    lbl_2_bss_1A8244 = superstarUnlocked;
    lbl_2_bss_1A8248 = starMissionCompletionTracker;
    lbl_2_bss_1A824C = w;
    item = currentDrawingItem;

    if (PADB((s8)WD(0x197863), 0xC) == 0xC) {
        PADH((s8)WD(0x197863), 0x4) |= PADH((s8)WD(0x197863), 0x0);
    }

    switch (menuControlVariables->currentState) {
    case 0:
        memset(w, 0, 0x1978FC);
        fn_2_54474();
        WB(0x197848) = 1;
        fn_2_94854();
        fn_2_9461C();
        fn_2_94604();
        fn_2_93C64();
        g_d_GameSettings.StadiumID = 0;
        WB(0x197863) = st->playerNumberByPort[0];
        d = insertGraphicDrawingFunction(fn_2_549B4, 2);
        *((u8 *)d + 0x28) = 0;
        item->state = 0;
        fn_8000F4B8(0, -1, -1, -1);
        menuControlVariables->currentState = 1;
        break;

    case 1:
        if (item->state == 1) {
            menuControlVariables->currentState = 2;
        }
        break;

    case 2:
        insertGraphicDrawingFunction(fn_8006295C, 2);
        changeScene(1, 6);
        fn_2_6ACF4();
        insertGraphicDrawingFunction(fn_2_71F60, 2);
        v.x = v.y = v.z = 0.0f;
        fn_2_6AB3C(0, &v);
        fn_2_72054(0, 0);
        WA(0x162992) = 0;
        menuNumber[0] = 0x5C;
        menuNumber[9] = menuNumber[8];
        menuNumber[8] = *(u16 *)&lbl_800FEF70[0x5C8];
        insertGraphicDrawingFunction(fn_80053FE8, 0);
        d = insertGraphicDrawingFunction(fn_2_5389C, 0);
        *(s16 *)((u8 *)d + 0x1C) = 0;
        *(s16 *)((u8 *)d + 0x1E) = 0;
        rows = (const MenuRowDef *)&tbl[0xCE4];
        for (i = 0; i < 0x2B; i++) {
            dst = lbl_2_bss_1A8234 + rows->unk8 * 0x5100 + rows->unk4 * 0x18;
            *(void **)(dst + 0x00) = (void *)rows->func;
            *(s16 *)(dst + 0x08) = rows->unk4;
            *(s16 *)(dst + 0x0A) = rows->unk6;
            *(s16 *)(dst + 0x0C) = rows->unk8;
            *(s16 *)(dst + 0x0E) = rows->unkA;
            *(s16 *)(dst + 0x10) = rows->unkC;
            rows++;
        }
        WA(0x162604) = 1;
        WA(0x162605) = 1;
        WA(0x162606) = 1;
        WA(0x162607) = 1;
        WA(0x16260A) = 1;
        WBH(0x1976F6) = 0;
        WBH(0x1976F4) = 0;
        menuControlVariables->currentState = 3;
        break;

    case 3:
        if (lbl_8037169C[0x12] != 0) {
            WA(0x16264A) = 1;
            WA(0x16264B) = 1;
            WA(0x16264C) = 1;
            WAH(0x162600) = 0x10;
            menuControlVariables->currentState = 4;
        }
        break;

    case 4:
        if (WAH(0x162600)-- == 0) {
            WA(0x16264E) = 1;
            menuControlVariables->currentState = 5;
        }
        break;

    case 5:
        if (PADH((s8)WD(0x197863), 0x4) == 1) {
            WDH(0x1976F6) = WDH(0x1976F4);
            WBH(0x1976F4) = (WBH(0x1976F4) + 10) % 11;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (PADH((s8)WD(0x197863), 0x4) == 2) {
            WDH(0x1976F6) = WDH(0x1976F4);
            WBH(0x1976F4) = (WBH(0x1976F4) + 1) % 11;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        buttons = PADH((s8)WB(0x197863), 0x2);
        if (buttons & 0x100) {
            menuControlVariables->currentState = 6;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (buttons & 0x200) {
            menuControlVariables->currentState = 8;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;

    case 6:
        WA(0x162835) = 1;
        WA(0x162836) = 1;
        menuControlVariables->currentState = 7;
        WAH(0x162600) = 0x10;
        break;

    case 7:
        if (WAH(0x162600)-- == 0) {
            menuControlVariables->currentState = 9;
        }
        break;

    case 8:
        WAH(0x162600) = 0x14;
        WA(0x162834) = 1;
        WA(0x162835) = 1;
        WA(0x162836) = 1;
        WA(0x162838) = 1;
        menuNumber[5] = 1;
        menuControlVariables->currentState = 0x10;
        break;

    case 9:
        fn_2_72054(0, 0x11);
        WBH(0x19772E) = 0xE7;
        WBH(0x197700) = TBL16(0x664 + WBH(0x1976F4) * 2);
        WBH(0x1976FE) = WBH(0x197700);
        WBH(0x1976FC) = 0;
        WBH(0x1976FA) = 0;
        WB(0x197822) = 0;
        WA(0x16264B) = 1;
        WA(0x16264D) = 1;
        WA(0x162650) = 1;
        WAH(0x162600) = 0x10;
        menuControlVariables->currentState = 0xA;
        break;

    case 10:
        if (WAH(0x162600)-- == 0) {
            WA(0x16264F) = 1;
            menuControlVariables->currentState = 0xC;
        }
        break;

    case 12:
        if (PADH((s8)WD(0x197863), 0x4) == 1) {
            WDH(0x1976F6) = WDH(0x1976F4);
            WBH(0x1976F4) = (WBH(0x1976F4) + 10) % 11;
            WBH(0x197700) = WBH(0x1976FE);
            WBH(0x1976FC) = WBH(0x1976FA);
            WBH(0x1976FE) = TBL16(0x664 + WBH(0x1976F4) * 2);
            WBH(0x1976FA) = 0;
            WB(0x197822) = 0;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            WA(0x1626DC) = 1;
            menuControlVariables->currentState = 0xF;
        } else if (PADH((s8)WD(0x197863), 0x4) == 2) {
            WDH(0x1976F6) = WDH(0x1976F4);
            WBH(0x1976F4) = (WBH(0x1976F4) + 1) % 11;
            WBH(0x197700) = WBH(0x1976FE);
            WBH(0x1976FC) = WBH(0x1976FA);
            WBH(0x1976FE) = TBL16(0x664 + WBH(0x1976F4) * 2);
            WBH(0x1976FA) = 0;
            WB(0x197822) = 0;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            WA(0x1626DC) = 1;
            menuControlVariables->currentState = 0xF;
        } else if (PADH((s8)WD(0x197863), 0x4) == 8 || PADH((s8)WD(0x197863), 0x4) == 4) {
            WDH(0x197700) = WDH(0x1976FE);
            WBH(0x1976FC) = WBH(0x1976FA);
            fn_2_46D94(&WBH(0x1976FA), &WBH(0x1976FE), WBH(0x19772E), 5, 9);
            WBH(0x1976F4) = fn_2_5597C();
            WB(0x197822) = 0;
            WA(0x1626DC) = 1;
            menuControlVariables->currentState = 0xF;
        } else {
            buttons = PADH((s8)WD(0x197863), 0x2);
            if ((buttons & 0x100) && (n = TBL16(0x494 + (WDH(0x1976FA) + WDH(0x1976FE)) * 2)) >= 2) {
                WD(0x197822) = ((s8)WD(0x197822) + 1) % n;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                WA(0x1627AE) = 1;
            } else if (buttons & 0x200) {
                menuControlVariables->currentState = 0xD;
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            }
        }
        break;

    case 13:
        WA(0x162835) = 1;
        WA(0x162837) = 1;
        WA(0x162839) = 1;
        WA(0x16283A) = 1;
        fn_2_72054(0, 0x12);
        WAH(0x162600) = 0x10;
        menuControlVariables->currentState = 0xE;
        break;

    case 14:
        if (WAH(0x162600)-- == 0) {
            WA(0x16264B) = 1;
            WA(0x16264C) = 1;
            WAH(0x162600) = 0x10;
            menuControlVariables->currentState = 4;
        }
        break;

    case 15:
        menuControlVariables->currentState = 0xC;
        break;

    case 16:
        if (WAH(0x162600)-- == 0) {
            fn_80062948();
            changeScene(3, 6);
            menuControlVariables->currentState = 0x11;
        }
        break;

    case 17:
        if (lbl_8037169C[0x13] != 0) {
            hugeAnimStruct[0x307A] = 0;
            WA(0x162992) = 1;
            lbl_2_bss_1A8230[0x32A86] = 1;
            menuControlVariables->currentState = 0x12;
        }
        break;

    case 18:
        WD(0x1972BC) = 1;
        fn_2_4E7EC();
        resetGameStadiumStateOnExit();
        maybeLoadsGameSoundFiles();
        fn_800ACFB0(*(void **)&lbl_800EF808[0x14]);
        fn_80035B50(10);
        if (screenTextArray.textBanks[2] != NULL) {
            fn_800ACFB0(screenTextArray.textBanks[2]);
            screenTextArray.textBanks[2] = NULL;
        }
        lbl_2_bss_1A823C[0x34] = 0;
        changeScreenVariables(5);
        break;

    case 19:
        d = insertGraphicDrawingFunction(fn_2_535B0, 2);
        *((u8 *)d + 0x28) = 0;
        item->state = 0;
        menuControlVariables->currentState = 0x14;
        break;

    case 20:
        if (item->state == 1) {
            menuControlVariables->currentState = 0xC;
        }
        break;
    }

    if (hugeAnimStruct[0x307A] == 2) {
        if (lbl_2_bss_1A8248[0x44F2] != 4) {
            fn_2_68E68();
        }
        fn_2_47FF8();
        if (lbl_2_bss_1A8248[0x44F2] != 4) {
            fn_2_47CFC();
        }
    }
    GXSetZCompLoc(0);
}
