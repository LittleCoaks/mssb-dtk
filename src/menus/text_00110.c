#include "menus/text_00110.h"

#include "menus/yd_step.h"
#include "Unknown/File_0x800b0a14.h"

extern Text00110Ctl *menuControlVariables;
extern u8 AtBat_ButtonInput1[];
extern u8 g_d_GameSettings[];
extern u8 gameSetUpStep[];
extern u8 Static_Stats_Tables[];
extern u8 rosterFileDescriptorMenus[];
extern u8 lbl_803C6CF8[];
extern u8 lbl_80366158[];
extern u32 lbl_803CB750;
extern u32 lbl_2_bss_B644;
extern DrawingSceneStruct *lbl_2_bss_4;

s32 fn_80022A24(u8 a, u8 b);
void fn_800229CC(void);
void fn_800216F8(s32 arg, void *fn);
void fn_8004153C(void);
void fn_800A97D0(s32 a, s32 b);
u32 OSGetTick(void);
void sndVolume(u8 volume, u16 time, u8 volGroup);
void *ARAMTransfer(void *file, s32 arg1, s32 arg2, s32 arg3);

#define OBJ_U8(obj, off) (*((u8 *)(obj) + (off)))
#define NODE_U16(node, off) (*(u16 *)((u8 *)(node) + (off)))
#define AT_BAT_U16(idx, off) (*(u16 *)(AtBat_ButtonInput1 + (idx) * 0x20 + (off)))
#define CURSOR_WRAP(x) ((x) % 32)

// Advance the cursor at +0x16 (limit at +0x15) and store the byte at +0x17 + cursor into dst.
#define CURSOR_STEP(obj, dst)                                          \
    do {                                                               \
        if (OBJ_U8(obj, 0x16) == OBJ_U8(obj, 0x15)) {                 \
            (dst) = 0;                                                 \
        } else {                                                       \
            OBJ_U8(obj, 0x16) = CURSOR_WRAP(OBJ_U8(obj, 0x16) + 1);    \
            (dst) = *((u8 *)(obj) + OBJ_U8(obj, 0x16) + 0x17);         \
        }                                                              \
    } while (0)

// .text:0x00000A14 size:0x5C mapped:0x8063FAA8
void fn_2_A14(void) {
    insertGraphicDrawingFunction(fn_2_160, 0x1000);
    insertGraphicDrawingFunction(fn_2_110, 0xF000);
    menuControlVariables->currentState = 0;
    menuControlVariables->currentScreen = 0;
}

// .text:0x00000978 size:0x9C mapped:0x8063FA0C
void fn_2_978(void) {
    u8 screen = lbl_80366158[0x1D];

    insertGraphicDrawingFunction(currentScreenFunctionChooser, 0x2000);
    switch (screen) {
    case 0:
        changeScreenVariables(0x11);
        break;
    case 1:
        changeScreenVariables(0xE);
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        break;
    case 7:
        changeScreenVariables(1);
        break;
    case 8:
        break;
    case 9:
        changeScreenVariables(1);
        break;
    default:
        break;
    }
    lbl_80366158[0x1D] = 1;
}

// .text:0x00000940 size:0x38 mapped:0x8063F9D4
void fn_2_940(void) {
    if (menuControlVariables->unk00 == 5) {
        removeCurrentDrawingItem();
    }
}

// .text:0x00000794 size:0x1AC mapped:0x8063F828
void fn_2_794(void) {
    DrawingSceneStruct *node = currentDrawingItem;
    Text00110Ctl *ctl = menuControlVariables;
    u8 screen;

    switch (ctl->unk00) {
    case 0:
        *(s16 *)((u8 *)node + 0x10) = 0;
        insertGraphicDrawingFunction(fn_2_160, 0x1000);
        insertGraphicDrawingFunction(fn_2_110, 0xF000);
        menuControlVariables->currentState = 0;
        menuControlVariables->currentScreen = 0;
        insertGraphicDrawingFunction(fn_2_940, 0x100);
        ctl->unk00++;
        break;
    case 1:
        ctl->unk00 = 3;
        break;
    case 3:
        screen = lbl_80366158[0x1D];
        insertGraphicDrawingFunction(currentScreenFunctionChooser, 0x2000);
        switch (screen) {
        case 0:
            changeScreenVariables(0x11);
            break;
        case 1:
            changeScreenVariables(0xE);
            break;
        case 7:
        case 9:
            changeScreenVariables(1);
            break;
        default:
            break;
        }
        lbl_80366158[0x1D] = 1;
        ctl->unk00 = 4;
        /* fall through */
    case 4:
        if (*(s16 *)((u8 *)node + 0x10) == 0) {
            break;
        }
        ctl->unk00 = 5;
        /* fall through */
    case 5:
        node->currentDrawingItem->state = *(s16 *)((u8 *)node + 0x10);
        removeCurrentDrawingItem();
        break;
    default:
        break;
    }
}

// .text:0x00000708 size:0x8C mapped:0x8063F79C
void fn_2_708(void) {
    DrawingSceneStruct *node = currentDrawingItem;

    lbl_803CB750 += OSGetTick();
    fn_8004153C();
    fn_800A97D0(0x10, 0x1E);
    menuControlVariables->unk00 = 0;
    NODE_U16(node, 0x14) = 0;
    insertGraphicDrawingFunction(fn_2_664, 0x1000);
    currentDrawingItem->func = fn_2_554;
}

// .text:0x00000664 size:0xA4 mapped:0x8063F6F8
void fn_2_664(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        u8 *dst = Static_Stats_Tables + i * 6;

        if (gameSetUpStep[0x55 + i] == 1 || (s8)Static_Stats_Tables[0x46F8 + i] == -1) {
            *(u16 *)(dst + 0x472C) = 0;
            *(u16 *)(dst + 0x472E) = 0;
            *(u16 *)(dst + 0x4730) = 0;
        } else {
            *(u16 *)(dst + 0x472C) = AT_BAT_U16((s8)Static_Stats_Tables[0x46F8 + i], 0x0);
            *(u16 *)(dst + 0x472E) = AT_BAT_U16((s8)Static_Stats_Tables[0x46F8 + i], 0x2);
            *(u16 *)(dst + 0x4730) = AT_BAT_U16((s8)Static_Stats_Tables[0x46F8 + i], 0x4);
        }
    }
}

// .text:0x00000554 size:0x110 mapped:0x8063F5E8
void fn_2_554(void) {
    DrawingSceneStruct *node = currentDrawingItem;
    u16 state = NODE_U16(node, 0x14);

    switch (state) {
    case 0:
        lbl_2_bss_B644 = OSGetTick();
        fn_800216F8(2, (void *)fn_2_10FC);
        NODE_U16(node, 0x14) = 1;
        /* fall through */
    case 1:
        if (*(s16 *)((u8 *)currentDrawingItem + 0x10) != 0) {
            sndVolume(0x7F, 0xA, 0xFF);
            NODE_U16(node, 0x14) = 2;
        } else {
            break;
        }
        /* fall through */
    case 2:
        ARAMTransfer(rosterFileDescriptorMenus, (s32)Static_Stats_Tables, 1, 0);
        NODE_U16(node, 0x14) = 3;
        break;
    case 3:
        if (lbl_803C6CF8[0x715] == 1) {
            node->func = fn_2_794;
            lbl_2_bss_4 = insertGraphicDrawingFunction(fn_2_374, 0x8000);
        }
        break;
    default:
        break;
    }
}

// .text:0x00000510 size:0x44 mapped:0x8063F5A4
u8 fn_2_510(u8 *obj) {
    u8 next;

    if (OBJ_U8(obj, 0x16) == OBJ_U8(obj, 0x15)) {
        return 0;
    }
    next = CURSOR_WRAP(OBJ_U8(obj, 0x16) + 1);
    OBJ_U8(obj, 0x16) = next;
    return *((u8 *)obj + OBJ_U8(obj, 0x16) + 0x17);
}

// .text:0x000004C4 size:0x4C mapped:0x8063F558
s32 fn_2_4C4(u8 *obj, u8 value) {
    u8 next = CURSOR_WRAP(OBJ_U8(obj, 0x15) + 1);

    if (next == OBJ_U8(obj, 0x16)) {
        return 0;
    }
    OBJ_U8(obj, 0x15) = next;
    *((u8 *)obj + OBJ_U8(obj, 0x15) + 0x17) = value;
    return 1;
}

// .text:0x00000374 size:0x150 mapped:0x8063F408
void fn_2_374(void) {
    DrawingSceneStruct *node = currentDrawingItem;
    u8 state = OBJ_U8(node, 0x14);
    u8 next;

    switch (state) {
    case 0:
        CURSOR_STEP(node, next);
        OBJ_U8(node, 0x14) = next;
        break;
    case 1:
        if (fn_80022A24(g_d_GameSettings[0x9], g_d_GameSettings[0xA]) != 0) {
            CURSOR_STEP(node, next);
            OBJ_U8(node, 0x14) = next;
            if (next == 2) {
                fn_800229CC();
                CURSOR_STEP(node, next);
                OBJ_U8(node, 0x14) = next;
            }
        }
        break;
    case 2:
        fn_800229CC();
        CURSOR_STEP(node, next);
        OBJ_U8(node, 0x14) = next;
        break;
    default:
        break;
    }
}

// .text:0x00000328 size:0x4C mapped:0x8063F3BC
void fn_2_328(void) {
    u8 *obj = (u8 *)lbl_2_bss_4;
    u8 next = CURSOR_WRAP(OBJ_U8(obj, 0x15) + 1);

    if (next == OBJ_U8(obj, 0x16)) {
        return;
    }
    OBJ_U8(obj, 0x15) = next;
    *((u8 *)obj + OBJ_U8(obj, 0x15) + 0x17) = 1;
}

// .text:0x000002DC size:0x4C mapped:0x8063F370
void bPressOnStadSelectScreen(void) {
    u8 *obj = (u8 *)lbl_2_bss_4;
    u8 next = CURSOR_WRAP(OBJ_U8(obj, 0x15) + 1);

    if (next == OBJ_U8(obj, 0x16)) {
        return;
    }
    OBJ_U8(obj, 0x15) = next;
    ((u8 *)obj + OBJ_U8(obj, 0x15))[0x17] = 2;
}

// .text:0x000002D8 size:0x4 mapped:0x8063F36C
void fn_2_2D8(void) {
}

// .text:0x000001A8 size:0x130 mapped:0x8063F23C
s32 fn_2_1A8(u8 index, u8 mode, u16 mask) {
    u16 value = 0;
    s32 result = -1;

    if (mode == 0) {
        value = AT_BAT_U16(index, 0x0);
    } else if (mode == 1) {
        value = menuControlVariables->slots[index];
    } else if (mode == 2) {
        value = AT_BAT_U16(index, 0x4);
    }
    value &= mask;
    if (mode == 1) {
        menuControlVariables->flags10 |= (1 << index);
    }
    if (value & 0x100) {
        result = 4;
    } else if (value & 0x200) {
        result = 5;
    } else if (value & 0x8) {
        result = 0;
    } else if (value & 0x4) {
        result = 1;
    } else if (value & 0x1) {
        result = 2;
    } else if (value & 0x2) {
        result = 3;
    } else if (value & 0x40) {
        result = 6;
    } else if (value & 0x20) {
        result = 7;
    }
    return result;
}

// .text:0x00000160 size:0x48 mapped:0x8063F1F4
void fn_2_160(void) {
    Text00110Ctl *ctl = menuControlVariables;

    ctl->slots[0] |= AT_BAT_U16(0, 0x2);
    menuControlVariables->slots[1] |= AT_BAT_U16(0, 0x22);
    menuControlVariables->flags10 = 0;
}

// .text:0x00000110 size:0x50 mapped:0x8063F1A4
void fn_2_110(void) {
    u8 i;

    for (i = 0; i < 2; i++) {
        if (menuControlVariables->flags10 & (1 << i)) {
            menuControlVariables->slots[i] = 0;
        }
    }
}
