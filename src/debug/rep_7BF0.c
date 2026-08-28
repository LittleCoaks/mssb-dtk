#include "debug/rep_7BF0.h"
#include "header_rep_data.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x80024184.h"
#include "Dolphin/GX/GXFifo.h"
#include "Dolphin/GX/GXGeometry.h"
#include "Dolphin/GX/GXLight.h"
#include "Dolphin/GX/GXPixel.h"
#include "Dolphin/GX/GXTev.h"
#include "Dolphin/GX/GXTransform.h"
#include "Dolphin/mtx.h"
#include "static/UnknownHomes_Static.h"
#include "stl/math.h"

extern void fn_800AD038(void *arg0);
extern void fn_800A97D0(s32 arg0, s32 arg1);
extern void fn_80037768(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
extern void fn_80037054(void *arg0, void *arg1);
extern void fn_800383BC(void *arg0);
extern void fn_1_273D8(void *arg0);
extern void fn_800B806C(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
extern void fn_80048BEC(void *arg0, s32 arg1, s32 arg2);
extern void fn_1_272DC(void *arg0, s32 arg1);
extern void fn_1_AF4(s32 arg0, s32 arg1, f32 arg2);
extern void fn_80048820(void *arg0, u16 arg1, u16 arg2, u16 arg3, u8 arg4);
extern void fn_1_26D28(void *arg0, u16 arg1, u16 arg2, u16 arg3, void *arg4);
extern void fn_1_27330(void *arg0);

extern u8 lbl_80366158[0x30];
extern u8 lbl_1_data_11300[0x634];
extern u8 lbl_1_bss_47068[0x154];
extern u8 lbl_1_bss_471BC[0x1C];
extern u8 lbl_1_bss_471D8[0xD8];
extern f32 lbl_1_rodata_7DFC;

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

typedef struct DebugCamState {
    /*0x00*/ u8 pad00[0x70];
    /*0x70*/ Vec pos;
    /*0x7C*/ Vec dir;
    /*0x88*/ Vec axis;
    /*0x94*/ u8 pad94[0x10];
    /*0xA4*/ f32 yaw;
    /*0xA8*/ f32 pitch;
    /*0xAC*/ f32 moveScale;
    /*0xB0*/ f32 turnSpeed;
    /*0xB4*/ f32 zoomSpeed;
    /*0xB8*/ f32 zoomDist;
    /*0xBC*/ f32 invZoomDist;
} DebugCamState;

// .text:0x0002858C size:0x434
void fn_1_2858C(DebugCamState *state, u32 buttons, u32 flags, s32 arg3, u8 *stick) {
    Quaternion q;
    Vec tmp;
    Mtx m;
    f32 moveX, moveY, moveZ;
    f32 v0, v1;

    if (flags & 0x10) {
        fn_1_273D8(state);
        return;
    }

    state->yaw -= ((PI * state->turnSpeed / 180.0f) * (f32)(s8)stick[2]) * 0.0078125f / 60.0f;
    state->pitch += ((PI * state->turnSpeed / 180.0f) * (f32)(s8)stick[3]) * 0.0078125f / 60.0f;

    while (state->yaw < -PI) {
        state->yaw += 2.0f * PI;
    }
    while (state->yaw >= PI) {
        state->yaw -= 2.0f * PI;
    }

    if (state->pitch < -3.1385247707366943f) {
        state->pitch = -3.1385247707366943f;
    } else if (state->pitch > 3.1385247707366943f) {
        state->pitch = 3.1385247707366943f;
    }

    tmp.x = 0.0f;
    tmp.y = 0.0f;
    tmp.z = 1.0f;

    PSVECCrossProduct(&tmp, &state->axis, &state->dir);
    PSVECNormalize(&state->dir, &state->dir);
    C_QUATRotAxisRad(&q, &state->dir, state->pitch);
    PSMTXQuat(m, &q);
    PSMTXMultVec(m, &tmp, &state->dir);

    C_QUATRotAxisRad(&q, &state->axis, state->yaw);
    PSMTXQuat(m, &q);
    PSMTXMultVec(m, &state->dir, &state->dir);

    moveY = 0.0f - (state->moveScale * (f32)(u8)stick[4]) / 150.0f / 60.0f;
    moveY = moveY + (state->moveScale * (f32)(u8)stick[5]) / 150.0f / 60.0f;
    moveX = -(state->moveScale * (f32)(s8)stick[0]) * 0.0078125f / 60.0f;
    moveZ = (state->moveScale * (f32)(s8)stick[1]) * 0.0078125f / 60.0f;

    tmp.x = moveX;
    tmp.y = moveY;
    tmp.z = moveZ;

    PSMTXMultVec(m, &tmp, &tmp);
    PSVECAdd(&state->pos, &tmp, &state->pos);

    v0 = (f32)((buttons & 0x400) != 0);
    state->zoomDist += (state->zoomSpeed * v0) / 60.0f;
    v1 = (f32)((buttons & 0x800) != 0);
    state->zoomDist -= (state->zoomSpeed * v1) / 60.0f;

    v0 = (f32)(state->zoomDist == 0.0f);
    v1 = (f32)(state->zoomDist != 0.0f);
    state->zoomDist = (state->zoomDist * v1) + (0.1f * v0);
    state->invZoomDist = 1.0f / state->zoomDist;
}

// .text:0x000289C0 size:0x20
void fn_1_289C0(void *arg0) {
    fn_1_273D8(arg0);
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
void fn_1_28CE8(void *arg0) {
    u8 *base = lbl_1_data_11300;
    Mtx m;
    f32 scaleXY = (f32) * (s32 *)(base + 0x8) / 100000.0f;
    f32 scaleZ = (f32) * (s32 *)(base + 0x0) / 100000.0f;

    PSMTXScale(m, scaleXY, scaleXY, scaleZ);
    PSMTXConcat((f32(*)[4])(lbl_1_bss_47068 + 0x58), m, m);
    PSMTXConcat((f32(*)[4])lbl_1_bss_471D8, m, m);
    GXLoadPosMtxImm(m, 0);
    GXSetCurrentMtx(0);

    gOz_GXSetTexture(4, NULL, 0);

    GXBegin(GX_LINES, GX_VTXFMT0, 6);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXColor1u32(0xFF00FF);
    GXPosition3f32(1.0f, 0.0f, 0.0f);
    GXColor1u32(0xFF00FF);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXColor1u32(0xFFFF);
    GXPosition3f32(0.0f, 1.0f, 0.0f);
    GXColor1u32(0xFFFF);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXColor1u32(0xFFFF);
    GXPosition3f32(0.0f, 0.0f, 1.0f);
    GXColor1u32(0xFFFF);
    GXEnd();

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetArray(GX_VA_POS, base + 0x60, 0xC);
    GXSetArray(GX_VA_CLR0, base + 0xC0, 0x4);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3X4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetCullMode(GX_CULL_BACK);
    GXCallDisplayList(base + 0xE0, 0x40);

    {
        Vec v;

        PSMTXMultVec((f32(*)[4])(lbl_1_bss_47068 + 0x58), (Vec *)lbl_1_bss_47068, &v);
        PSMTXMultVec((f32(*)[4])(lbl_1_bss_47068 + 0x58), (Vec *)(lbl_1_bss_47068 + 0xC), &v);
        PSVECCrossProduct((Vec *)lbl_1_bss_47068, (Vec *)(lbl_1_bss_47068 + 0x140), &v);
        PSMTXMultVec((f32(*)[4])(lbl_1_bss_47068 + 0x88), &v, &v);
        PSVECCrossProduct((Vec *)(lbl_1_bss_47068 + 0xC), (Vec *)(lbl_1_bss_47068 + 0x140), &v);
        PSMTXMultVec((f32(*)[4])(lbl_1_bss_47068 + 0x88), &v, &v);
        PSVECScale((Vec *)(lbl_1_bss_47068 + 0x104), *(f32 *)(lbl_1_bss_47068 + 0x28), &v);
    }
}

// .text:0x0002905C size:0x300
void fn_1_2905C(void) {
    u8 *base = lbl_1_data_11300;
    s32 mode = *(s8 *)(base + 0x38);

    if (mode == 1) {
        goto mode1;
    }
    if (mode >= 1) {
        goto modeGE2;
    }
    if (mode >= 0) {
        goto mode0;
    }
    return;

modeGE2:
    if (mode >= 3) {
        return;
    }
    goto tail;

mode0 : {
        // mode == 0
        f32 v0 = (f32) * (s32 *)(base + 0x0) / 100000.0f;
        f32 v4 = (f32) * (s32 *)(base + 0x4) / 100000.0f;
        f32 v8 = (f32) * (s32 *)(base + 0x8) / 100000.0f;
        f32 vC = (f32) * (s32 *)(base + 0xC) / 100000.0f;
        s32 dead34 = *(s32 *)(base + 0x34);

        fn_80037768(v0, v8, v4, vC);

        {
            f32 v14 = (f32) * (s32 *)(base + 0x14) / 100000.0f;
            f32 v1c = (f32) * (s32 *)(base + 0x1C) / 100000.0f;
            f32 v20 = (f32) * (s32 *)(base + 0x20) / 100000.0f;
            f32 v24 = (f32) * (s32 *)(base + 0x24) / 100000.0f;
            Vec *tmp = (Vec *)(lbl_1_bss_47068 + 0xE8);
            Vec *src = (Vec *)(lbl_1_bss_47068 + 0x11C);
            Vec *dst = (Vec *)(lbl_1_bss_47068 + 0x128);

            tmp->x = 0.0f;
            tmp->y = v14;
            tmp->z = 0.0f;
            src->x = v1c;
            src->y = v20;
            src->z = v24;
            PSMTXMultVec((f32(*)[4])(lbl_1_bss_47068 + 0xB8), src, dst);
        }

        {
            f32 v18 = (f32) * (s32 *)(base + 0x18) / 100000.0f;
            f32 v28 = (f32) * (s32 *)(base + 0x28) / 100000.0f;
            f32 v2c = (f32) * (s32 *)(base + 0x2C) / 100000.0f;
            f32 v30 = (f32) * (s32 *)(base + 0x30) / 100000.0f;
            f32 angle = v18 * 0.017453292f;
            Vec *axisVec = (Vec *)(lbl_1_bss_47068 + 0x140);
            Mtx m;

            axisVec->x = v28;
            axisVec->y = v2c;
            axisVec->z = v30;
            PSMTXRotRad(m, 'X', angle);
            C_QUATMtx((Quaternion *)(lbl_1_bss_47068 + 0xF4), m);
            fn_800383BC(lbl_1_bss_47068);
        }
        return;
    }

mode1:
    if (*(s8 *)(base + 0x39) == 0) {
        return;
    }
    *(u8 *)(base + 0x39) = 0;

tail:
    *(f32 *)(lbl_1_bss_47068 + 0x50) = (f32) * (s32 *)(base + 0x10) / 100000.0f;
    fn_80037054(lbl_1_bss_47068, base + 0x3C);
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
void fn_1_29414(void *arg0) {
    if (*((u8 *)arg0 + 0x14) != 0) {
        fn_80048BEC(lbl_1_bss_471BC, 0, 0);
    }
    fn_1_272DC(lbl_1_bss_471D8, 0);
    fn_1_AF4(0xa, 0xa, lbl_1_rodata_7DFC);
    fn_1_28CE8(arg0);
}

// .text:0x0002948C size:0x15C
void fn_1_2948C(void *arg0) {
    u16 v0 = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 0x0);
    u16 v2 = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 0x2);
    u16 v4 = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 0x4);

    if (v2 & 0x1000) {
        u8 flag = *((u8 *)arg0 + 0x14) ^ 1;
        *((u8 *)arg0 + 0x14) = flag;
        if (*((u8 *)arg0 + 0x14) != 0) {
            fn_800A97D0(0x20, 0);
        } else {
            fn_800A97D0(0x10, 0x1e);
        }
    } else if (*((u8 *)arg0 + 0x14) != 0) {
        s32 mask;

        if (v0 & 0x800) {
            mask = 0x91;
        } else {
            mask = (v0 & 0x400) ? 0x50 : 0;
        }
        fn_80048820(lbl_1_bss_471BC, v0, v2, v4, (u8)mask);
        v0 = v0 & ~0xC00;
        v2 = v2 & ~0xC00;
        v4 = v4 & ~0xC00;
    } else if (v2 & 0x200) {
        fn_800AD038(*(void **)(lbl_80366158 + 0x8));
        fn_800A97D0(0x10, 0x1e);
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
    }

    fn_1_26D28(lbl_1_bss_471D8, v0, v2, v4, (u8 *)&AtBat_ButtonInput1 + 0x10);
    fn_1_27330(lbl_1_bss_471D8);
}

// .text:0x000295E8 size:0x460
void fn_1_295E8(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    u8 *bss = lbl_1_bss_47068;
    u16 v0 = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 0x0);
    u16 v2 = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 0x2);
    u16 v4 = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 0x4);

    if (v2 & 0x1000) {
        u8 flag = *((u8 *)item + 0x14) ^ 1;
        *((u8 *)item + 0x14) = flag;
        if (*((u8 *)item + 0x14) != 0) {
            fn_800A97D0(0x20, 0);
        } else {
            fn_800A97D0(0x10, 0x1e);
        }
    } else if (*((u8 *)item + 0x14) != 0) {
        s32 mask;

        if (v0 & 0x800) {
            mask = 0x91;
        } else {
            mask = (v0 & 0x400) ? 0x50 : 0;
        }
        fn_80048820(bss + 0x154, v0, v2, v4, (u8)mask);
        v0 = v0 & ~0xC00;
        v2 = v2 & ~0xC00;
        v4 = v4 & ~0xC00;
    } else if (v2 & 0x200) {
        fn_800AD038(*(void **)(lbl_80366158 + 0x8));
        fn_800A97D0(0x10, 0x1e);
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
    }

    fn_1_26D28(bss + 0x170, v0, v2, v4, (u8 *)&AtBat_ButtonInput1 + 0x10);
    fn_1_27330(bss + 0x170);

    {
        u8 *base = lbl_1_data_11300;
        s32 mode = *(s8 *)(base + 0x38);

        if (mode == 1) {
            goto mode1;
        }
        if (mode >= 1) {
            goto modeGE2;
        }
        if (mode >= 0) {
            goto mode0;
        }
        goto tail2;

    modeGE2:
        if (mode >= 3) {
            goto tail2;
        }
        goto tail;

    mode0 : {
            f32 f0 = (f32) * (s32 *)(base + 0x0) / 100000.0f;
            f32 f4 = (f32) * (s32 *)(base + 0x4) / 100000.0f;
            f32 f8 = (f32) * (s32 *)(base + 0x8) / 100000.0f;
            f32 fC = (f32) * (s32 *)(base + 0xC) / 100000.0f;
            s32 dead34 = *(s32 *)(base + 0x34);

            fn_80037768(f0, f8, f4, fC);

            {
                f32 v14 = (f32) * (s32 *)(base + 0x14) / 100000.0f;
                f32 v1c = (f32) * (s32 *)(base + 0x1C) / 100000.0f;
                f32 v20 = (f32) * (s32 *)(base + 0x20) / 100000.0f;
                f32 v24 = (f32) * (s32 *)(base + 0x24) / 100000.0f;
                Vec *tmp = (Vec *)(bss + 0xE8);
                Vec *src = (Vec *)(bss + 0x11C);
                Vec *dst = (Vec *)(bss + 0x128);

                tmp->x = 0.0f;
                tmp->y = v14;
                tmp->z = 0.0f;
                src->x = v1c;
                src->y = v20;
                src->z = v24;
                PSMTXMultVec((f32(*)[4])(bss + 0xB8), src, dst);
            }

            {
                f32 v18 = (f32) * (s32 *)(base + 0x18) / 100000.0f;
                f32 v28 = (f32) * (s32 *)(base + 0x28) / 100000.0f;
                f32 v2c = (f32) * (s32 *)(base + 0x2C) / 100000.0f;
                f32 v30 = (f32) * (s32 *)(base + 0x30) / 100000.0f;
                f32 angle = v18 * 0.017453292f;
                Vec *axisVec = (Vec *)(bss + 0x140);
                Mtx m;

                axisVec->x = v28;
                axisVec->y = v2c;
                axisVec->z = v30;
                PSMTXRotRad(m, 'X', angle);
                C_QUATMtx((Quaternion *)(bss + 0xF4), m);
                fn_800383BC(bss);
            }
            goto tail2;
        }

    mode1:
        if (*(s8 *)(base + 0x39) == 0) {
            goto tail2;
        }
        *(u8 *)(base + 0x39) = 0;

    tail:
        *(f32 *)(bss + 0x50) = (f32) * (s32 *)(base + 0x10) / 100000.0f;
        fn_80037054(bss, base + 0x3C);
    }

tail2:
    if (*((u8 *)item + 0x14) != 0) {
        fn_80048BEC(bss + 0x154, 0, 0);
    }
    fn_1_272DC(bss + 0x170, 0);
    fn_1_AF4(0xa, 0xa, lbl_1_rodata_7DFC);
    fn_1_28CE8(item);
}

// .text:0x00029A48 size:0x54
void fn_1_29A48(void) {
    fn_800AD038(*(void **)(lbl_80366158 + 0x8));
    fn_800A97D0(0x10, 0x1e);
    currentDrawingItem->currentDrawingItem->state = 1;
    removeCurrentDrawingItem();
}

// .text:0x00029A9C size:0x1C0
void fn_1_29A9C(void) {
    u8 *base = lbl_1_data_11300;
    f32 v0 = (f32) * (s32 *)(base + 0x0) / 100000.0f;
    f32 v4 = (f32) * (s32 *)(base + 0x4) / 100000.0f;
    f32 v8 = (f32) * (s32 *)(base + 0x8) / 100000.0f;
    f32 vC = (f32) * (s32 *)(base + 0xC) / 100000.0f;
    s32 dead34 = *(s32 *)(base + 0x34);
    MenuDescendState *state = (MenuDescendState *)(lbl_1_bss_47068 + 0x154);
    MenuItem *items;

    fn_80037768(v0, v8, vC, v4);
    fn_1_273D8(lbl_1_bss_471D8);

    *(u8 *)(base + 0x38) = 0;
    state->unk00 = *(u32 *)(base + 0x120);
    state->unk08 = 0x10;
    state->unk0C = 0;
    state->index = 0;
    state->unk14 = 1;
    items = ((MenuItem **)(base + 0x62C))[0];
    state->items = items;
    state->count = 0;
    while (items[state->count].unk04 != 0) {
        state->count++;
    }

    fn_800B806C(0, -240.0f, 240.0f, -320.0f, 320.0f, -512.0f, -1.0f, 1280.0f);

    currentDrawingItem->func = fn_1_295E8;
}
