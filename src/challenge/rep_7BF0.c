#include "challenge/rep_7BF0.h"
#include "header_rep_data.h"
#include "Unknown/File_0x800b0a14.h"

extern void fn_800AD038(void *arg0);
extern void fn_800A97D0(s32 arg0, s32 arg1);
extern void fn_80037768(f32 arg0, f32 arg1, f32 arg2, f32 arg3);

extern u8 lbl_80366158[0x30];
extern u8 lbl_1_data_11300[0x634];

typedef struct MenuItem {
    /*0x00*/ s32 unk00;
    /*0x04*/ u32 unk04;
    /*0x08*/ u8 pad08[0x1C];
    /*0x24*/ s32 leafFlag;
    /*0x28*/ u8 pad28[0x4];
} MenuItem; // size 0x2C

struct MenuDescendState;

typedef struct MenuDescendState {
    /*0x00*/ s32 unk00;
    /*0x04*/ s32 count;
    /*0x08*/ s32 unk08;
    /*0x0C*/ s32 unk0C;
    /*0x10*/ s32 index;
    /*0x14*/ s32 unk14;
    /*0x18*/ MenuItem *items;
} MenuDescendState;

// .text:0x0002858C size:0x434
void fn_1_2858C(void) {
    return;
}

// .text:0x000289C0 size:0x20
void fn_1_289C0(void) {
    return;
}

// .text:0x000289E0 size:0x100
void fn_1_289E0(MenuDescendState *state, u16 input) {
    s32 mode;
    MenuItem *item;

    mode = *(s8 *)(lbl_1_data_11300 + 0x38);
    if (mode == 1) {
        if (input & 0x100) {
            *(s8 *)(lbl_1_data_11300 + 0x38) = 2;
        } else if (input & 0x200) {
            *(s8 *)(lbl_1_data_11300 + 0x38) = 0;
        } else if (input & 0x400) {
            *(u8 *)(lbl_1_data_11300 + 0x39) = 1;
        }
    } else if (mode >= 1) {
        if (mode < 3) {
            if (input & 0x100) {
                *(s8 *)(lbl_1_data_11300 + 0x38) = 1;
            } else if (input & 0x200) {
                *(s8 *)(lbl_1_data_11300 + 0x38) = 0;
            }
        }
    } else if (mode >= 0) {
        if (input & 0x100) {
            *(s8 *)(lbl_1_data_11300 + 0x38) = 2;
        } else if (input & 0x400) {
            *(u8 *)(lbl_1_data_11300 + 0x39) = 1;
            *(s8 *)(lbl_1_data_11300 + 0x38) = 1;
        }
    }

    mode = *(s8 *)(lbl_1_data_11300 + 0x38);
    item = &state->items[state->index];
    item->unk04 = ((s32 *)(lbl_1_data_11300 + 0x124))[mode];
}

// .text:0x00028AE0 size:0x154
s32 fn_1_28AE0(MenuDescendState *state) {
    u8 *base = lbl_1_data_11300;
    MenuItem *item = &state->items[state->index];
    s32 leaf = item->leafFlag;

    *((u8 *)currentDrawingItem + 0x15) = (u8)leaf;
    if ((s8)leaf < 0) {
        fn_800AD038(*(void **)(lbl_80366158 + 0x8));
        fn_800A97D0(0x10, 0x1e);
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        return 0;
    } else {
        s32 value = item->unk04;

        if (value == 0) {
            value = *(u32 *)(base + 0x120);
        }
        state->unk00 = value;
        state->unk08 = 0x10;
        state->unk0C = 0;
        state->index = 0;
        state->unk14 = 1;
        state->items = ((MenuItem **)(base + 0x62C))[leaf];
        if (leaf == 1) {
            if (*(u32 *)(base + 0x1E4) == 0) {
                s32 mode = *(s8 *)(base + 0x38);

                *(u32 *)(base + 0x1E4) = *(u32 *)(base + 0x124 + mode * 4);
            }
        }
        state->count = 0;
        while (state->items[state->count].unk04 != 0) {
            state->count++;
        }
        return 0;
    }
}

// .text:0x00028C34 size:0xB4
void fn_1_28C34(MenuDescendState *state, s32 level, u32 value) {
    u8 *base = lbl_1_data_11300;
    MenuItem *items;

    if (value == 0) {
        value = *(u32 *)(base + 0x120);
    }
    state->unk00 = value;
    state->unk08 = 0x10;
    state->unk0C = 0;
    state->index = 0;
    state->unk14 = 1;
    items = ((MenuItem **)(base + 0x62C))[level];
    state->items = items;
    if (level == 1) {
        if (*(u32 *)(base + 0x1E4) == 0) {
            s32 mode = *(s8 *)(base + 0x38);

            *(u32 *)(base + 0x1E4) = *(u32 *)(base + 0x124 + mode * 4);
        }
    }
    state->count = 0;
    while (items[state->count].unk04 != 0) {
        state->count++;
    }
}

// .text:0x00028CE8 size:0x374
void fn_1_28CE8(void) {
    return;
}

// .text:0x0002905C size:0x300
void fn_1_2905C(void) {
    return;
}

// .text:0x0002935C size:0xB8
void fn_1_2935C(void) {
    s32 field0 = *(s32 *)(lbl_1_data_11300 + 0x0);
    s32 field4 = *(s32 *)(lbl_1_data_11300 + 0x4);
    s32 field8 = *(s32 *)(lbl_1_data_11300 + 0x8);
    s32 fieldC = *(s32 *)(lbl_1_data_11300 + 0xC);
    s32 field34 = *(s32 *)(lbl_1_data_11300 + 0x34);

    fn_80037768((f32)field0 / 100000.0f, (f32)field4 / 100000.0f,
                (f32)field8 / 100000.0f, (f32)fieldC / 100000.0f);
}

// .text:0x00029414 size:0x78
void fn_1_29414(void) {
    return;
}

// .text:0x0002948C size:0x15C
void fn_1_2948C(void) {
    return;
}

// .text:0x000295E8 size:0x460
void fn_1_295E8(void) {
    return;
}

// .text:0x00029A48 size:0x54
void fn_1_29A48(void) {
    return;
}

// .text:0x00029A9C size:0x1C0
void fn_1_29A9C(void) {
    return;
}
