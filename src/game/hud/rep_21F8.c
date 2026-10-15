#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_rep_21F8
#include "game/hud/rep_21F8.h"
#include "game/animation/scene_effects.h"
#include "Dolphin/mtx.h"
#include "Dolphin/gx.h"
#include "header_rep_data.h"

typedef struct _HudKey HudKey21F8;
typedef struct _HudNode {
    f32 x, y, w, h;
    u16 texture, subTexture;
    HudKey21F8* ch[8];
    u8 count[8];
    u8 index[8];
} HudNode21F8;

typedef struct HudObj21F8 {
    HudNode21F8* nodes;
    void** textures;
    s32 count;
    u8 _0C[4];
    f32 frame;
    f32 time;
} HudObj21F8;

typedef struct HudState21F8 {
    u8 index;
    u8 _01[3];
    Vec origin;
    f32 time;
} HudState21F8;

// Animation keys for the node channels below (0xC bytes each).
static u32 lbl_3_data_17898[0x228 / 4] = {
    0x3F800000, 0x3F000000, 0x10000101,
    0x40000000, 0x00000000, 0x000E0000,
    0x3F800000, 0x3F800000, 0x10000101,
    0x40000000, 0x3FE66666, 0x10020001,
    0x3E4CCCCD, 0x00000000, 0x000E0000,
    0x3F800000, 0x3F000000, 0x10000101,
    0x40000000, 0x00000000, 0x00100000,
    0x3F800000, 0x3F800000, 0x10000101,
    0x40000000, 0x3FE66666, 0x10020001,
    0x3E4CCCCD, 0x00000000, 0x00100000,
    0x00000000, 0x40000000, 0x10000001,
    0xC0000000, 0x00000000, 0x000A0000,
    0x00000000, 0x40000000, 0x10000001,
    0xC0000000, 0x00000000, 0x000C0000,
    0x3EA0D97C, 0x00000000, 0x00000000,
    0x3FF1463B, 0x00000000, 0x00000000,
    0x405D2B0B, 0x00000000, 0x00000000,
    0x40A0D97C, 0x00000000, 0x00000000,
    0x3FA0D97C, 0x00000000, 0x00000000,
    0x4034F4AC, 0x00000000, 0x00000000,
    0x408CBE4C, 0x00000000, 0x00000000,
    0x40BF0243, 0x00000000, 0x00000000,
    0x3F71463B, 0x00000000, 0x00000000,
    0x4020D97C, 0x00000000, 0x00000000,
    0x4082B0B5, 0x00000000, 0x00000000,
    0x40B4F4AC, 0x00000000, 0x00000000,
    0x3FC90FDB, 0x00000000, 0x00000000,
    0x40490FDB, 0x00000000, 0x00000000,
    0x4096CBE4, 0x00000000, 0x00000000,
    0x40C90FDB, 0x00000000, 0x00000000,
    0x3F20D97C, 0x00000000, 0x00000000,
    0x3F10C3BD, 0x00000000, 0x00000000,
    0xBF10C3BD, 0x00000000, 0x00000000,
    0xBF20D97C, 0x00000000, 0x00000000,
    0x3F800000, 0x00000000, 0x00000000,
    0x3F800000, 0x3F800000, 0x100A0001,
    0x00000000, 0x00000000, 0x000E0000,
    0x3F800000, 0x00000000, 0x00000000,
    0x3F800000, 0x3F800000, 0x100C0001,
    0x00000000, 0x00000000, 0x00100000,
    0x3F800000, 0x3E4CCCCD, 0x10000001,
    0x3ECCCCCD, 0x00000000, 0x00100000,
    0x40400000, 0x40000000, 0x10000001,
    0x40A00000, 0x00000000, 0x00100000,
    0x3F800000, 0x3F800000, 0x10000001,
    0x00000000, 0x00000000, 0x00100000,
};
static HudNode21F8 lbl_3_data_17AC0 = {
    -1.0f, -0.5f, 1.0f, 1.0f,
    0, 0,
    {
        (HudKey21F8*)&lbl_3_data_17898[0],
        (HudKey21F8*)&lbl_3_data_17898[6],
        (HudKey21F8*)&lbl_3_data_17898[30],
        NULL,
        NULL,
        (HudKey21F8*)&lbl_3_data_17898[90],
        (HudKey21F8*)&lbl_3_data_17898[42],
        (HudKey21F8*)&lbl_3_data_17898[111],
    },
    { 2, 3, 2, 0, 0, 1, 1, 3 },
    { 0 },
};
static HudObj21F8 lbl_3_data_17B04[5] = {
    { &lbl_3_data_17AC0, NULL, 0x11, { 0, 0, 0, 1 }, 16.0f, 0.0f },
    { &lbl_3_data_17AC0, NULL, 0x11, { 0, 0, 0, 1 }, 16.0f, 0.0f },
    { &lbl_3_data_17AC0, NULL, 0x12, { 0, 0, 0, 1 }, 16.0f, 0.0f },
    { &lbl_3_data_17AC0, NULL, 0x12, { 0, 0, 0, 1 }, 16.0f, 0.0f },
    { 0 },
};
static u32 lbl_3_data_17B7C = 0xFF;
static u8 lbl_3_data_17B80 = 1;
static f32 lbl_3_data_17B84[5] = { 4.0f, 2.0f, 1.0f, 0.9f, 0.0f };


extern struct { void* base; void* texture; } lbl_3_common_bss_35154;
extern void fn_80034120(Mtx out);

// MWCC lays .bss out in reverse declaration order, so the phase byte (0x9F34) is declared first.
static u8 lbl_3_bss_9F34;
static HudState21F8 lbl_3_bss_9F20;
#define HUD_PHASE(state) (((u8*)(state))[0x14])

void fn_3_C9734(void) {
    lbl_3_bss_9F34 = 2;
}

f32 fn_3_C9590(HudNode21F8* node, int frame, Mtx out, f32 t) {
    Mtx tmp;
    f32 v;

    PSMTXIdentity(out);
    out[0][0] = fn_3_BFDA4((HudKey*)node->ch[0], node->count[0], frame, node->index[0], &node->index[0], t);
    out[1][1] = fn_3_BFDA4((HudKey*)node->ch[1], node->count[1], frame, node->index[1], &node->index[1], t);
    if (node->ch[2] != NULL) {
        v = fn_3_BFDA4((HudKey*)node->ch[2], node->count[2], frame, node->index[2], &node->index[2], t);
    } else {
        v = 0.0f;
    }
    out[0][3] = v;
    if (node->ch[5] != NULL) {
        v = fn_3_BFDA4((HudKey*)node->ch[5], node->count[5], frame, node->index[5], &node->index[5], t);
    } else {
        v = 0.0f;
    }
    if (v) {
        PSMTXRotRad(tmp, 'Y', v);
        PSMTXConcat(tmp, out, out);
    }
    if (node->ch[6] != NULL) {
        v = fn_3_BFDA4((HudKey*)node->ch[6], node->count[6], frame, node->index[6], &node->index[6], t);
    } else {
        v = 0.0f;
    }
    if (v) {
        PSMTXRotRad(tmp, 'Z', v);
        PSMTXConcat(tmp, out, out);
    }
    return fn_3_BFDA4((HudKey*)node->ch[7], node->count[7], frame, node->index[7], &node->index[7], t);
}

BOOL fn_3_C937C(void) {
    Mtx scale;
    HudState21F8* state = &lbl_3_bss_9F20;
    Mtx local = {
        { 1.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f },
    };
    Mtx view;
    f32 s;
    u8 active;
    int idx;

    switch (HUD_PHASE(state)) {
    case 0:
        HUD_PHASE(state) = 1;
        state->time = 0.0f;
    case 1:
        state->time += 1.0f;
        if (state->time >= 16.0f) {
            HUD_PHASE(state) = 2;
        }
        break;
    }
    fn_80034120(view);
    PSMTXConcat(view, local, view);
    s = lbl_3_data_17B84[state->index];
    PSMTXScale(scale, s, s, s);
    PSMTXConcat(view, scale, view);
    active = lbl_3_data_17B80;
    idx = state->index;
    lbl_3_data_17B04[idx].time = state->time;
    lbl_3_data_17B04[idx].textures = &lbl_3_common_bss_35154.texture;
    if (active != 0) {
        GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    }
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
    fn_3_BF8F8((HudObj*)&lbl_3_data_17B04[state->index], view, &state->origin, (HudEvalFn)fn_3_C9590);
    if (lbl_3_data_17B80 != 0) {
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    }
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    return HUD_PHASE(state) == 2;
}
