#include "menus/text_37F04.h"
#include "Unknown/File_0x800b0a14.h"

// Per-scene flow node: the DrawingSceneStruct fields that these functions use
// are read at different offsets, so this local view names them directly.
typedef struct FlowNode {
    /* 0x00 */ void (*func)(void);
    /* 0x04 */ struct FlowNode *prev;
    /* 0x08 */ struct FlowNode *next;
    /* 0x0C */ struct FlowNode *child;
    /* 0x10 */ s16 _10;
    /* 0x12 */ u16 priority;
    /* 0x14 */ s16 timer;
    /* 0x16 */ s16 sub;
    /* 0x18 */ s16 sub18;
    /* 0x1A */ s16 sub1A;
    /* 0x1C */ u8 _1C[0x28 - 0x1C];
    /* 0x28 */ s8 state;
} FlowNode;

extern u8 *lbl_2_bss_1A8234;
extern u8 *lbl_2_bss_1A8244;
extern u8 *lbl_2_bss_1A8248;
extern u8 *lbl_2_bss_1A824C;
extern u8 g_d_GameSettings[];
s32 fn_80062890(int sfx);
BOOL fn_2_45A84(void);

#define CUR_NODE() ((FlowNode *)currentDrawingItem)
#define BSS_1A8234_U8(off) (lbl_2_bss_1A8234[0x160000 + (off)])
#define BSS_1A8248_U8(off) (lbl_2_bss_1A8248[(off)])
#define BSS_1A824C_U8(off) (lbl_2_bss_1A824C[0x190000 + (off)])
#define BSS_1A824C_S16(off) (*(s16 *)&lbl_2_bss_1A824C[0x190000 + (off)])

// .text:0x000399C0 size:0xF3C mapped:0x80678A54
void fn_2_399C0(void) {
    return;
}

// .text:0x000397AC size:0x214 mapped:0x80678840
void fn_2_397AC(void) {
    return;
}

// .text:0x00039408 size:0x3A4 mapped:0x8067849C
void fn_2_39408(void) {
    return;
}

// .text:0x000391B4 size:0x254 mapped:0x80678248
void fn_2_391B4(void) {
    return;
}

// .text:0x00038F48 size:0x26C mapped:0x80677FDC
void fn_2_38F48(void) {
    return;
}

// .text:0x00038EA8 size:0xA0 mapped:0x80677F3C
void fn_2_38EA8(void) {
    u8 *menuState = lbl_2_bss_1A8248;
    u8 *table = lbl_2_bss_1A8244;

    menuState[0x4416] = menuState[0x4415];
    table[menuState[0x4415] + 0xE4] = 1;
    if (menuState[0x4415] >= 3) {
        return;
    }
    if (table[menuState[0x441C] + 0xE8] == 0) {
        table[menuState[0x441C] + 0xE8] = 1;
    }
    menuState[0x4415]++;
    table[menuState[0x441C] + 0xDE]++;
}

// .text:0x00038D44 size:0x164 mapped:0x80677DD8
void fn_2_38D44(void) {
    FlowNode *cur = CUR_NODE();

    switch (cur->state) {
    case 0:
        if (fn_2_45A84() == 1) {
            cur->timer = 1;
            cur->state = 1;
        } else {
            cur->state = 4;
        }
        break;
    case 1:
        if (cur->timer-- == 0) {
            cur->state = 2;
        }
        break;
    case 2:
        BSS_1A8234_U8(0x2680) = 1;
        cur->timer = 0x5A;
        cur->state = 3;
        break;
    case 3:
        if (cur->timer-- == 0) {
            BSS_1A8234_U8(0x286A) = 1;
            cur->state = 4;
        }
        break;
    case 4:
        CUR_NODE()->child->_10 = 1;
        removeCurrentDrawingItem();
        cur->state = 0;
        break;
    }

    if (BSS_1A824C_U8(0x783F) == 1) {
        CUR_NODE()->child->_10 = 1;
        removeCurrentDrawingItem();
        cur->state = 0;
    }
}

// .text:0x00038C14 size:0x130 mapped:0x80677CA8
void fn_2_38C14(void) {
    FlowNode *cur = CUR_NODE();

    switch (cur->state) {
    case 0:
        cur->timer = 0x14;
        cur->state = 2;
        break;
    case 1:
        if (cur->timer-- == 0) {
            BSS_1A824C_U8(0x782C) = 1;
            cur->timer = 0x14;
            cur->state = 2;
        }
        break;
    case 2:
        if (cur->timer-- == 0) {
            cur->timer = 0x14;
            cur->state = 3;
        }
        break;
    case 3:
        CUR_NODE()->child->_10 = 1;
        removeCurrentDrawingItem();
        cur->state = 0;
        break;
    }

    if (BSS_1A824C_U8(0x783F) == 1) {
        CUR_NODE()->child->_10 = 1;
        removeCurrentDrawingItem();
        cur->state = 0;
    }
}

// .text:0x00038A40 size:0x1D4 mapped:0x80677AD4
void fn_2_38A40(void) {
    FlowNode *cur = CUR_NODE();

    switch (cur->state) {
    case 0:
        BSS_1A8248_U8(0x44F2) = 3;
        cur->timer = 0xF;
        if (BSS_1A824C_S16(0x729C) != 0) {
            BSS_1A8234_U8(0x264C) = 1;
            BSS_1A8234_U8(0x264D) = 1;
            BSS_1A8234_U8(0x264E) = 1;
        }
        if (BSS_1A824C_S16(0x729E) != 0) {
            BSS_1A8234_U8(0x2652) = 1;
            BSS_1A8234_U8(0x2653) = 1;
        }
        if (BSS_1A824C_U8(0x78FA) == 0) {
            *(s32 *)&lbl_2_bss_1A824C[0x190000 + 0x76A8] = fn_80062890(0x11);
            BSS_1A824C_U8(0x78FA) = 0;
        }
        cur->state = 1;
        break;
    case 1:
        if (cur->timer-- == 0) {
            cur->state = 2;
        }
        break;
    case 2:
        CUR_NODE()->child->_10 = 1;
        removeCurrentDrawingItem();
        cur->state = 0;
        break;
    }

    if (BSS_1A824C_U8(0x783F) == 1) {
        CUR_NODE()->child->_10 = 1;
        removeCurrentDrawingItem();
        cur->state = 0;
    }
}

// .text:0x00038824 size:0x21C mapped:0x806778B8
void fn_2_38824(void) {
    FlowNode *cur = CUR_NODE();

    switch (cur->state) {
    case 0:
        cur->timer = 0xA;
        if (cur->sub18 == 1) {
            cur->sub18 = 0;
            switch (BSS_1A824C_S16(0x72AC)) {
            case 0:
                BSS_1A8234_U8(0x264F) = 1;
                break;
            case 1:
                BSS_1A8234_U8(0x2650) = 1;
                break;
            case 2:
            case 3:
                BSS_1A8234_U8(0x2651) = 1;
                break;
            }
        }
        if (cur->sub1A == 1) {
            cur->sub1A = 0;
            switch (BSS_1A824C_S16(0x72AE)) {
            case 0:
                BSS_1A8234_U8(0x2654) = 1;
                break;
            case 1:
                BSS_1A8234_U8(0x2655) = 1;
                break;
            case 2:
            case 3:
                BSS_1A8234_U8(0x2656) = 1;
                break;
            }
        }
        cur->state = 1;
        break;
    case 1:
        if (cur->timer-- == 0) {
            cur->state = 2;
        }
        break;
    case 2:
        CUR_NODE()->child->_10 = 1;
        removeCurrentDrawingItem();
        cur->state = 0;
        break;
    }

    if (BSS_1A824C_U8(0x783F) == 1) {
        CUR_NODE()->child->_10 = 1;
        removeCurrentDrawingItem();
        cur->state = 0;
    }
}

// .text:0x00038538 size:0x2EC mapped:0x806775CC
void fn_2_38538(void) {
    return;
}

// .text:0x000382A0 size:0x298 mapped:0x80677334
void fn_2_382A0(void) {
    FlowNode *cur = CUR_NODE();

    switch (cur->state) {
    case 0:
        cur->timer = 5;
        if (cur->sub == 0 || cur->sub == 2) {
            if (BSS_1A824C_S16(0x72A4) != 0) {
                switch (BSS_1A824C_S16(0x72AC)) {
                case 0:
                    BSS_1A8234_U8(0x2839) = 1;
                    break;
                case 1:
                    BSS_1A8234_U8(0x283A) = 1;
                    break;
                case 2:
                case 3:
                    BSS_1A8234_U8(0x283B) = 1;
                    break;
                }
            }
        }
        if (cur->sub == 1 || cur->sub == 2) {
            if (BSS_1A824C_S16(0x72A6) != 0) {
                switch (BSS_1A824C_S16(0x72AE)) {
                case 0:
                    BSS_1A8234_U8(0x283E) = 1;
                    break;
                case 1:
                    BSS_1A8234_U8(0x283F) = 1;
                    break;
                case 2:
                case 3:
                    BSS_1A8234_U8(0x2840) = 1;
                    break;
                }
            }
        }
        cur->state = 1;
        break;
    case 1:
        if (cur->timer-- == 0) {
            cur->state = 2;
        }
        break;
    case 2:
        if (cur->sub == 0 || cur->sub == 2) {
            BSS_1A824C_S16(0x72A4) = 0;
        }
        if (cur->sub == 1 || cur->sub == 2) {
            BSS_1A824C_S16(0x72A6) = 0;
        }
        CUR_NODE()->child->_10 = 1;
        removeCurrentDrawingItem();
        cur->state = 0;
        break;
    }

    if (BSS_1A824C_U8(0x783F) == 1) {
        CUR_NODE()->child->_10 = 1;
        removeCurrentDrawingItem();
        cur->state = 0;
    }
}

// .text:0x000381A8 size:0xF8 mapped:0x8067723C
void fn_2_381A8(void) {
    FlowNode *cur = CUR_NODE();

    switch (cur->state) {
    case 0:
        cur->timer = 0x15;
        BSS_1A8234_U8(0x2838) = 1;
        cur->state = 1;
        break;
    case 1:
        if (cur->timer-- == 0) {
            cur->state = 2;
        }
        break;
    case 2:
        CUR_NODE()->child->_10 = 1;
        removeCurrentDrawingItem();
        cur->state = 0;
        break;
    }

    if (BSS_1A824C_U8(0x783F) == 1) {
        CUR_NODE()->child->_10 = 1;
        removeCurrentDrawingItem();
        cur->state = 0;
    }
}

// .text:0x000380B0 size:0xF8 mapped:0x80677144
void fn_2_380B0(void) {
    FlowNode *cur = CUR_NODE();

    switch (cur->state) {
    case 0:
        cur->timer = 0x15;
        BSS_1A8234_U8(0x264E) = 1;
        cur->state = 1;
        break;
    case 1:
        if (cur->timer-- == 0) {
            cur->state = 2;
        }
        break;
    case 2:
        CUR_NODE()->child->_10 = 1;
        removeCurrentDrawingItem();
        cur->state = 0;
        break;
    }

    if (BSS_1A824C_U8(0x783F) == 1) {
        CUR_NODE()->child->_10 = 1;
        removeCurrentDrawingItem();
        cur->state = 0;
    }
}

// .text:0x00037F04 size:0x1AC mapped:0x80676F98
void fn_2_37F04(void) {
    FlowNode *cur = CUR_NODE();

    switch (cur->state) {
    case 0:
        if ((s8)BSS_1A8248_U8(0x444B) == -1) {
            cur->state = 4;
        } else {
            cur->timer = 0x14;
            cur->state = 1;
        }
        break;
    case 1:
        if (cur->timer == 4) {
            fn_80062890(0x43);
        }
        if (cur->timer-- == 0) {
            cur->state = 2;
        }
        break;
    case 2: {
        s8 idx = (s8)BSS_1A8248_U8(0x444B);

        g_d_GameSettings[0x3C + idx] = 0;
        BSS_1A8248_U8(0x444C) = -1;
        BSS_1A8248_U8(0x444B) = -1;
        BSS_1A8234_U8(0x281C) = 1;
        cur->timer = 0x3C;
        cur->state = 3;
        break;
    }
    case 3:
        if (cur->timer-- == 0) {
            cur->state = 4;
        }
        break;
    case 4:
        CUR_NODE()->child->_10 = 1;
        removeCurrentDrawingItem();
        cur->state = 0;
        break;
    }

    if (BSS_1A824C_U8(0x783F) == 1) {
        CUR_NODE()->child->_10 = 1;
        removeCurrentDrawingItem();
        cur->state = 0;
    }
}
