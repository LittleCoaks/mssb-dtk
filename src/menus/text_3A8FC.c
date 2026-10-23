#include "menus/text_3A8FC.h"
#include "Unknown/File_0x800b0a14.h"
#include "game/UnknownHomes_Game.h"
#include "game/challenge/star_mission_data.h"
#include "menus/text_44F14.h"

typedef struct MenuFlowItem {
    void (*func)(void);
    void *prev;
    void *next;
    DrawingSceneStruct *parent;
    s16 state;
    u16 priority;
    s16 timer;
    u8 unk16[0x28 - 0x16];
    s8 phase;
} MenuFlowItem;

extern u8 *lbl_2_bss_1A824C;
extern u8 *lbl_2_bss_1A8248;
extern u8 *lbl_2_bss_1A8234;
extern u8 AtBat_ButtonInput1[];
void fn_2_90428(s32 slot);
void fn_2_92654(s32 slot, u8 value);
s32 fn_80062890(s32 value);
void fn_2_4A6E8(void);
extern s16 lbl_2_data_122A8[][2];
extern u8 lbl_800EFBA4[];
s32 sndFXStartEx(u16 soundId, u8 volume, u8 pan, u8 studio);

extern s16 lbl_2_data_373C[];
extern s16 lbl_2_data_296B8[];
extern E(u8, CHAR_ID) lbl_800E869C[];
extern u8 lbl_8037169C[];
extern u8 menuNumber[];
extern struct {
    u8 unk0[8];
    u16 label;
    u8 unkA[6];
} lbl_800FEF70[];
void changeScene(u8 scene, u16 arg);
void fn_80053FE8(void);
BOOL challenge_isCharRecruited(s32 charID);

#define WORK(off) (lbl_2_bss_1A824C + 0x190000 + (off))
#define WORK_S16(off) (*(s16 *)WORK(off))
#define UI(off) (lbl_2_bss_1A8234 + 0x160000 + (off))

static inline void setRecordAnimation(s32 normalOffset, s32 alternateOffset) {
    if ((s8)lbl_2_bss_1A8248[0x44F4] == 0) *UI(normalOffset) = TRUE;
    else *UI(alternateOffset) = TRUE;
}

static inline void finishCancelledItem(MenuFlowItem *item) {
    if (*WORK(0x783F) == TRUE) {
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        item->phase = 0;
    }
}

static inline u16 pressedButtons(void) {
    s8 index = (s8)*WORK(0x7863);
    return *(u16 *)(AtBat_ButtonInput1 + index * 0x20 + 2);
}

static inline s16 recordMenuSize(s32 index, s32 offset) {
    u8 *sizes = (u8 *)starMenuSizes + offset;
    sizes += index * sizeof(s16);
    return *(s16 *)sizes;
}

static inline void setMenu(s32 menu) {
    menuNumber[0] = menu;
    menuNumber[9] = menuNumber[8];
    menuNumber[8] = lbl_800FEF70[menu].label;
}

static inline void updateRecordGridCursor(void) {
    u16 *repeat = (u16 *)(AtBat_ButtonInput1 + 4);
    s8 idx = (s8)*WORK(0x7863);
    u16 pad = repeat[idx * 16];

    if (pad & INPUT_BUTTON_LEFT) {
        WORK_S16(0x7708)--;
        if (WORK_S16(0x7708) == 0 && (WORK_S16(0x770A) == 0 || WORK_S16(0x770A) == 5)) {
            WORK_S16(0x7708) = 4;
        } else if (WORK_S16(0x7708) < 0) {
            WORK_S16(0x7708) = 5;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (pad & INPUT_BUTTON_RIGHT) {
        WORK_S16(0x7708)++;
        if (WORK_S16(0x7708) == 5 && (WORK_S16(0x770A) == 0 || WORK_S16(0x770A) == 5)) {
            WORK_S16(0x7708) = 1;
        } else if (WORK_S16(0x7708) > 5) {
            WORK_S16(0x7708) = 0;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
    idx = (s8)*WORK(0x7863);
    pad = repeat[idx * 16];
    if (pad & INPUT_BUTTON_UP) {
        WORK_S16(0x770A)--;
        if (WORK_S16(0x770A) == 0 && (WORK_S16(0x7708) == 0 || WORK_S16(0x7708) == 5)) {
            WORK_S16(0x770A) = 4;
        } else if (WORK_S16(0x770A) < 0) {
            WORK_S16(0x770A) = 5;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (pad & INPUT_BUTTON_DOWN) {
        WORK_S16(0x770A)++;
        if (WORK_S16(0x770A) == 5 && (WORK_S16(0x7708) == 0 || WORK_S16(0x7708) == 5)) {
            WORK_S16(0x770A) = 1;
        } else if (WORK_S16(0x770A) > 5) {
            WORK_S16(0x770A) = 0;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
    WORK_S16(0x7706) = lbl_2_data_296B8[WORK_S16(0x7708) + WORK_S16(0x770A) * 6];
}

// .text:0x0003A8FC size:0x60C mapped:0x80679990
void fn_2_3A8FC(void) {
    MenuFlowItem *item = (MenuFlowItem *)currentDrawingItem;
    u16 *repeat;
    u16 buttons;
    switch (item->phase) {
    case 0:
        setRecordAnimation(0x267F, 0x2651);
        item->timer = 12;
        item->phase = 1;
        break;
    case 1:
        if (item->timer-- == 0) item->phase = 2;
        break;
    case 2:
        repeat = (u16 *)(AtBat_ButtonInput1 + 4);
        buttons = repeat[(s8)*WORK(0x7863) * 16];
        if (buttons & INPUT_BUTTON_LEFT) {
            WORK_S16(0x7712) = WORK_S16(0x7710);
            WORK_S16(0x770C)--;
            if (WORK_S16(0x770C) < 0)
                WORK_S16(0x770C) = lbl_2_data_122A8[WORK_S16(0x7714)][0];
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (buttons & INPUT_BUTTON_RIGHT) {
            WORK_S16(0x7712) = WORK_S16(0x7710);
            WORK_S16(0x770C)++;
            if (WORK_S16(0x770C) > lbl_2_data_122A8[WORK_S16(0x7714)][0])
                WORK_S16(0x770C) = 0;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        buttons = repeat[(s8)*WORK(0x7863) * 16];
        if (buttons & INPUT_BUTTON_UP) {
            if (lbl_2_data_122A8[WORK_S16(0x7714)][1] != 0) {
                WORK_S16(0x7712) = WORK_S16(0x7710);
                WORK_S16(0x770E)--;
                if (WORK_S16(0x770E) < 0)
                    WORK_S16(0x770E) = lbl_2_data_122A8[WORK_S16(0x7714)][1];
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else if (buttons & INPUT_BUTTON_DOWN) {
            if (lbl_2_data_122A8[WORK_S16(0x7714)][1] != 0) {
                WORK_S16(0x7712) = WORK_S16(0x7710);
                WORK_S16(0x770E)++;
                if (WORK_S16(0x770E) > lbl_2_data_122A8[WORK_S16(0x7714)][1])
                    WORK_S16(0x770E) = 0;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
        WORK_S16(0x7710) = WORK_S16(0x770C) + WORK_S16(0x770E) *
            (lbl_2_data_122A8[WORK_S16(0x7714)][0] + 1);
        buttons = repeat[(s8)*WORK(0x7863) * 16];
        if ((buttons & INPUT_BUTTON_UP) || (buttons & INPUT_BUTTON_DOWN)) {
            if (lbl_2_data_122A8[WORK_S16(0x7714)][1] != 0) {
                setRecordAnimation(0x270B, 0x26DD);
                item->phase = 3;
                break;
            }
        } else if ((buttons & INPUT_BUTTON_LEFT) || (buttons & INPUT_BUTTON_RIGHT)) {
            setRecordAnimation(0x270B, 0x26DD);
            item->phase = 3;
            break;
        }
        buttons = pressedButtons();
        if (buttons & INPUT_BUTTON_A) {
            setRecordAnimation(0x2869, 0x283B);
            item->timer = 12;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            item->phase = 4;
        } else if (buttons & INPUT_BUTTON_B) {
            setRecordAnimation(0x2869, 0x283B);
            item->timer = 12;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            item->phase = 4;
        }
        break;
    case 3:
        item->phase = 2;
        break;
    case 4:
        if (item->timer-- == 0) item->phase = 5;
        break;
    case 5:
        item->parent->state = 1;
        removeCurrentDrawingItem();
        item->phase = 0;
        break;
    }
    finishCancelledItem(item);
}

// .text:0x0003AF08 size:0xB38 mapped:0x80679F9C
void fn_2_3AF08(void) {
    MenuFlowItem *item = (MenuFlowItem *)currentDrawingItem;
    s32 i, count;
    u16 buttons;
    switch (item->phase) {
    case 0:
        for (i = 0, count = 0; i < 20; i++) {
            if ((s8)lbl_2_bss_1A8248[0x43C2 + i] == 1 && lbl_2_data_373C[i] == 0)
                *WORK(0x78B3 + count++) = TRUE;
        }
        changeScene(3, 6);
        item->phase = 1;
        break;
    case 1:
        if (lbl_8037169C[0x13] != 0) item->phase = 2;
        break;
    case 2:
        WORK_S16(0x7730) = 6;
        lbl_2_bss_1A8248[0x44F2] = 2;
        WORK_S16(0x7706) = 0;
        WORK_S16(0x7708) = 1;
        WORK_S16(0x770A) = 0;
        *UI(0x267B) = TRUE;
        *UI(0x267E) = TRUE;
        menuNumber[3] = lbl_2_bss_1A8248[0x4415];
        insertGraphicDrawingFunction(fn_80053FE8, 0);
        menuNumber[0] = 14;
        setMenu(14);
        changeScene(1, 6);
        item->phase = 3;
        break;
    case 3:
        item->timer--;
        if (lbl_8037169C[0x12] != 0) item->phase = 4;
        break;
    case 4:
        item->timer = 40;
        *UI(0x267C) = TRUE;
        item->phase = 5;
        break;
    case 5:
        if (item->timer-- <= 0) item->phase = 6;
        break;
    case 6:
        updateRecordGridCursor();
        buttons = pressedButtons();
        if (buttons & INPUT_TRIGGER_L) {
            WORK_S16(0x7730) = 1;
            *UI(0x293A) = TRUE;
            *UI(0x2866) = TRUE;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            item->timer = 50;
            item->phase = 7;
        } else if (buttons & INPUT_TRIGGER_R) {
            WORK_S16(0x7730) = 1;
            *UI(0x2980) = TRUE;
            *UI(0x2866) = TRUE;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            item->timer = 50;
            item->phase = 7;
        } else if (buttons & INPUT_BUTTON_A) {
            if (challenge_isCharRecruited(lbl_800E869C[WORK_S16(0x7706)]) == TRUE) {
                WORK_S16(0x7712) = 0;
                WORK_S16(0x7710) = 0;
                WORK_S16(0x770C) = 0;
                WORK_S16(0x770E) = 0;
                WORK_S16(0x7714) = recordMenuSize(fn_2_44F14(lbl_800E869C[WORK_S16(0x7706)]), 12);
                sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
                item->phase = 8;
            } else {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            }
        } else if (buttons & INPUT_BUTTON_B) {
            *UI(0x2866) = TRUE;
            item->timer = 40;
            item->phase = 14;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    case 7:
        if (item->timer-- == 0) item->phase = 10;
        break;
    case 8: {
        MenuFlowItem *child = (MenuFlowItem *)insertGraphicDrawingFunction(fn_2_3A8FC, 2);
        child->phase = 0;
        item->state = 0;
        item->phase = 9;
        break;
    }
    case 9:
        if (item->state == 1) item->phase = 6;
        break;
    case 10:
        item->timer = 30;
        setMenu(15);
        *UI(0x267D) = TRUE;
        item->phase = 11;
        break;
    case 11:
        if (item->timer-- <= 0) item->phase = 12;
        break;
    case 12:
        buttons = pressedButtons();
        if (buttons & INPUT_TRIGGER_L) {
            WORK_S16(0x7730) = 6;
            *UI(0x293A) = TRUE;
            *UI(0x2867) = TRUE;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            item->timer = 30;
            setMenu(14);
            item->phase = 13;
        } else if (buttons & INPUT_TRIGGER_R) {
            WORK_S16(0x7730) = 6;
            *UI(0x2980) = TRUE;
            *UI(0x2867) = TRUE;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            item->timer = 30;
            setMenu(14);
            item->phase = 13;
        } else if (buttons & INPUT_BUTTON_B) {
            *UI(0x2867) = TRUE;
            item->timer = 30;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            item->phase = 14;
        }
        break;
    case 13:
        if (item->timer-- == 0) item->phase = 4;
        break;
    case 14:
        if (item->timer-- == 0) {
            changeScene(3, 6);
            item->phase = 15;
        }
        break;
    case 15:
        if (lbl_8037169C[0x13] != 0) item->phase = 16;
        break;
    case 16:
        lbl_2_bss_1A8248[0x44F2] = 0;
        menuNumber[0x26] = TRUE;
        *UI(0x2865) = TRUE;
        *UI(0x2868) = TRUE;
        item->timer = 50;
        changeScene(1, 6);
        item->phase = 17;
        break;
    case 17:
        item->timer--;
        if (lbl_8037169C[0x12] != 0) item->phase = 18;
        break;
    case 18:
        item->parent->state = 1;
        removeCurrentDrawingItem();
        item->phase = 0;
        break;
    }
    finishCancelledItem(item);
}

// .text:0x0003BA40 size:0x1E4 mapped:0x8067AAD4
void fn_2_3BA40(void) {
    MenuFlowItem *item = (MenuFlowItem *)currentDrawingItem;
    s32 i;
    switch (item->phase) {
    case 0:
        item->timer = 60;
        fn_2_4A6E8();
        for (i = 0; i < 5; i++) *UI(0x2669 + i) = TRUE;
        item->phase = 1;
        break;
    case 1:
        if (item->timer-- == 0) item->phase = 2;
        break;
    case 2:
        if (pressedButtons() &
            (INPUT_BUTTON_A | INPUT_BUTTON_B)) {
            item->timer = 50;
            for (i = 0; i < 5; i++) *UI(0x2853 + i) = TRUE;
            item->phase = 3;
        }
        break;
    case 3:
        if (item->timer-- == 0) item->phase = 4;
        break;
    case 4:
        item->parent->state = 1;
        removeCurrentDrawingItem();
        item->phase = 0;
        break;
    }
    finishCancelledItem(item);
}

// .text:0x0003BC24 size:0x164 mapped:0x8067ACB8
void fn_2_3BC24(void) {
    MenuFlowItem *item = (MenuFlowItem *)currentDrawingItem;
    switch (item->phase) {
    case 0:
        lbl_2_bss_1A8248[0x442A] = TRUE;
        item->timer = 60;
        item->phase = 1;
        break;
    case 1:
        if (item->timer-- == 0) {
            fn_2_90428(0x19);
            fn_2_92654(0x19, 8);
            fn_2_90428(0x1A);
            fn_2_92654(0x1A, 1);
            fn_2_90428(0x1B);
            fn_2_92654(0x1B, 2);
            fn_80062890(0x42);
            item->timer = 180;
            item->phase = 2;
        }
        break;
    case 2:
        if (item->timer-- == 0) item->phase = 3;
        break;
    case 3:
        item->parent->state = 1;
        removeCurrentDrawingItem();
        item->phase = 0;
        break;
    }
    finishCancelledItem(item);
}
