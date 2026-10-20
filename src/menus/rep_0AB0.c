#include "menus/rep_0AB0.h"
#include "header_rep_data.h"
#include "Unknown/File_0x800b0a14.h"
#include "static/UnknownHomes_Static.h"
#include "menus/yd_step.h"
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
void fn_904A8(void);
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
extern u8 g_Challenge[];
extern u8 lbl_8037169C[];
extern u8 screenTextArray[];
extern u8 lbl_2_bss_1A8250[];
extern menuControlStruct *menuControlVariables;
extern u8 *lbl_2_bss_1A8230;
s32 sndFXStartEx(u16 soundId, u8 volume, u8 pan, u8 unk);

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
                    if (PADH(idx, 0x2) & 0x100) {
                        NODE_U8(item, 0x28) = 4;
                    } else if ((s8)PADB(0, 0x13) > 0x32) {
                        NODE_U8(item, 0x28) = 4;
                    }
                }
                break;

            case 1:
                if (WB32(0x1976A0) == slot) {
                    idx = (s8)WB(0x197863);
                    if (PADH(idx, 0x2) & 0x102) {
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
                    if (PADH(idx, 0x2) & 0x102) {
                        WB(0x19784A) = 1;
                        WB(0x197846) = 2;
                        NODE_U8(item, 0x28) = 3;
                    }
                }
                break;

            case 3:
                if (WB32(0x1976A0) == slot) {
                    idx = (s8)WB(0x197863);
                    if (PADH(idx, 0x2) & 0x102) {
                        lbl_2_bss_1A8244[0xF4] ^= 1;
                        fn_2_5EB78();
                    }
                }
                break;
            }
        }

        idx = (s8)WB(0x197863);
        if ((PADH(idx, 0x2) & 0x200) || (s8)PADB(0, 0x13) > 0x32) {
            NODE_U8(item, 0x28) = 4;
        }
        break;

    case 2:
    case 3:
        fn_2_1FF14(1);
        fn_2_1FF0C(0);
        if (WB32(0x1976A4) == 0) {
            idx = (s8)WB(0x197863);
            pad = PADH(idx, 0x2);
            if (pad & 0x200) {
                WB(0x19784A) = 0;
                WB(0x197846) = 0;
                WB32(0x1976A4) = 0;
                WB(0x197845) = 0;
                NODE_U8(item, 0x28) = 1;
            } else if (sub == 2) {
                if (pad & 0x100) {
                    lbl_2_bss_A169 ^= 1;
                } else if (pad & 0x1000) {
                    fn_2_93C64();
                }
                if (lbl_2_bss_A169 != 0) {
                    fn_2_489DC();
                }
            } else {
                if (pad & 0x40) {
                    if (PADH(idx, 0x0) & 0x100) {
                        WBH(0x1972BE) = (WBH(0x1972BE) + 28) % 29;
                    }
                } else if (pad & 0x20) {
                    if (PADH(idx, 0x0) & 0x100) {
                        WBH(0x1972BE) = (WBH(0x1972BE) + 1) % 29;
                    }
                } else if (PADH(idx, 0x4) & 0x800) {
                    *(f32 *)(lbl_2_bss_1A8248 + WBH(0x1972BE) * 0xBC + 0x2208) -= 0.1f;
                } else if (PADH(idx, 0x4) & 0x400) {
                    *(f32 *)(lbl_2_bss_1A8248 + WBH(0x1972BE) * 0xBC + 0x2208) += 0.1f;
                }
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

// .text:0x00059CF8 size:0x52C mapped:0x80698D8C
void fn_2_59CF8(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    s8 sub = (s8)NODE_U8(item, 0x28);
    s32 slot;
    s8 idx;
    u16 pad;
    u8 *buf = lbl_80354768 + 0xCF18;
    u32 i;

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
                    if (PADH(idx, 0x2) & 0x100) {
                        NODE_U8(item, 0x28) = 3;
                    } else if ((s8)PADB(0, 0x13) > 0x32) {
                        NODE_U8(item, 0x28) = 3;
                    }
                }
                break;

            case 1:
                if (WB32(0x1976A0) == slot) {
                    idx = (s8)WB(0x197863);
                    if (PADH(idx, 0x2) & 0x102) {
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
                    if (PADH(idx, 0x2) & 0x3) {
                        if (buf[0] == 0) {
                            for (i = 0; i < 0x36; i++) {
                                buf[i] = 1;
                            }
                        } else if (buf[0] == 1) {
                            for (i = 0; i < 0x36; i++) {
                                buf[i] = 0;
                            }
                        }
                    }
                }
                break;
            }
        }

        idx = (s8)WB(0x197863);
        if ((PADH(idx, 0x2) & 0x200) || (s8)PADB(0, 0x13) > 0x32) {
            NODE_U8(item, 0x28) = 3;
        }
        break;

    case 2:
        fn_2_1FF14(1);
        fn_2_1FF0C(0);
        if (WB32(0x1976A4) == 0) {
            idx = (s8)WB(0x197863);
            pad = PADH(idx, 0x2);
            if (pad & 0x200) {
                WB(0x19784A) = 0;
                WB(0x197846) = 0;
                WB32(0x1976A4) = 0;
                WB(0x197845) = 0;
                NODE_U8(item, 0x28) = 1;
            } else {
                if (pad & 0x100) {
                    lbl_2_bss_A168 ^= 1;
                } else if (pad & 0x1000) {
                    fn_2_93C64();
                }
                if (lbl_2_bss_A168 != 0) {
                    fn_2_489DC();
                }
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

// .text:0x0005A224 size:0xC30 mapped:0x806992B8
void fn_2_5A224(void) {
    return;
}

// .text:0x0005AE54 size:0xD0 mapped:0x80699EE8
void fn_2_5AE54(void) {
    DrawingSceneStruct *item = currentDrawingItem;

    if (NODE_U16(item, 0x1C) == 0) {
        fn_2_4E878(item, lbl_2_data_20C68);
        NODE_U16(item, 0x1C) = 1;
        NODE_U16(item, 0x18) = 0;
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

// .text:0x0005B7DC size:0xDDC mapped:0x8069A870
void fn_2_5B7DC(void) {
    return;
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

// .text:0x0005E104 size:0x748 mapped:0x8069D198
void recordsScreen(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    DrawingSceneStruct *d;
    menuControlStruct *menu = menuControlVariables;
    u8 *w = lbl_2_bss_1A8250;
    s32 i;

    lbl_2_bss_1A8230 = w + 0x162998;
    lbl_2_bss_1A8234 = w;
    lbl_2_bss_1A823C = (u8 *)&inningSetting.rel;
    lbl_2_bss_1A8244 = superstarUnlocked;
    lbl_2_bss_1A8248 = (u8 *)&g_Challenge;
    lbl_2_bss_1A8240 = lbl_803616CC;
    lbl_2_bss_1A824C = w;
    lbl_2_bss_340140 = hugeAnimStruct;
    lbl_2_bss_3401BC = lbl_2_bss_3401C0;

    switch (menu->currentState) {
    case 0:
        resetGameStadiumStateOnExit();
        memset(w, 0, 0x1978FC);
        fn_2_54474();
        menu->currentState = 1;
        fn_2_5EB78();
        WB(0x197863) = Static_Stats_Tables.playerNumberByPort[0];
        fn_8000F4B8(0, -1, -1, -1);
        WCH(0x32) = 0;
        break;

    case 1:
        d = insertGraphicDrawingFunction(fn_2_5ED3C, 2);
        NODE_U8(d, 0x28) = 0;
        item->state = 0;
        menu->currentState = 2;
        break;

    case 2:
        if (item->state == 1) {
            menu->currentState = 3;
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
            v.x = zero;
            v.y = zero;
            v.z = zero;
            fn_2_6AB3C(0, &v);
        }
        fn_2_72054(0, 0);
        fn_904A8();
        insertGraphicDrawingFunction(fn_2_9257C, 2);
        for (i = 0; i < *(u16 *)(lbl_2_bss_340140 + 0x3078); i++) {
            fn_2_903A8(i);
            fn_2_92654(i, 0);
        }
        insertGraphicDrawingFunction(fn_2_5DC5C, 2);
        item->state = 0;
        *(u16 *)(lbl_2_bss_1A824C + 0x197730) = 0;
        *(u16 *)(lbl_2_bss_1A824C + 0x197732) = 0;
        menu->currentState = 4;
        break;

    case 4:
        menu->currentState = 5;
        break;

    case 5:
        changeScene(1, 6);
        menu->currentState = 6;
        break;

    case 6:
        if (lbl_8037169C[0x12] != 0) {
            menu->currentState = 7;
        }
        break;

    case 7:
        if (item->state == 1) {
            menuNumber[5] = 1;
            WA(0x162992) = 1;
            lbl_2_bss_1A824C[0x32A86] = 1;
            menu->currentState = 8;
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
        menu->currentState = 0;
        changeScreenVariables(5);
        WCH(0x32) = 0;
        break;
    }
}
