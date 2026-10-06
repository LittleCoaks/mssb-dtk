#define SQRT2_LINKAGE static
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

typedef struct HudData21F8 {
    u8 _000[0x26C];
    HudObj21F8 objects[5];
    u8 _2E4[4];
    u8 active;
    u8 _2E9[3];
    f32 scales[5];
} HudData21F8;

typedef struct HudState21F8 {
    u8 index;
    u8 _01[3];
    Vec origin;
    f32 time;
} HudState21F8;

extern HudData21F8 lbl_3_data_17898;
extern struct { void* base; void* texture; } lbl_3_common_bss_35154;
extern void fn_80034120(Mtx out);

static HudState21F8 lbl_3_bss_9F20;
static u8 lbl_3_bss_9F34;
#define HUD_PHASE(state) (((u8*)(state))[0x14])

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
    HudData21F8* data = &lbl_3_data_17898;
    HudState21F8* state = &lbl_3_bss_9F20;
    Mtx local = {
        { 1.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f },
    };
    Mtx view;
    f32 s;
    u8 active;

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
    s = data->scales[state->index];
    PSMTXScale(scale, s, s, s);
    PSMTXConcat(view, scale, view);
    active = data->active;
    {
        HudObj21F8* objects = data->objects;
        objects[state->index].time = state->time;
        objects[state->index].textures = &lbl_3_common_bss_35154.texture;
    }
    if (active != 0) {
        GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    }
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
    fn_3_BF8F8((HudObj*)&data->objects[state->index], view, &state->origin, (HudEvalFn)fn_3_C9590);
    if (data->active != 0) {
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    }
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    return HUD_PHASE(state) == 2;
}

void fn_3_C9734(void) {
    lbl_3_bss_9F34 = 2;
}
