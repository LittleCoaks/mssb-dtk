#include "debug/rep_7BF0.h"
#include "header_rep_data.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/sub.h"
#include "Dolphin/GX/GXFifo.h"
#include "Dolphin/GX/GXGeometry.h"
#include "Dolphin/GX/GXLight.h"
#include "Dolphin/GX/GXPixel.h"
#include "Dolphin/GX/GXTev.h"
#include "Dolphin/GX/GXTransform.h"
#include "Dolphin/mtx.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/pad.h"
#include "stl/math.h"

extern void fn_800AD038(void *arg0);
extern void fn_800A97D0(s32 arg0, s32 arg1);
extern void fn_80037768(void *cam, s32 arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
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

typedef struct MenuItem {
    /*0x00*/ s32 kind;
    /*0x04*/ const char *name;
    /*0x08*/ s32 minValue;
    /*0x0C*/ s32 maxValue;
    /*0x10*/ s32 step0;
    /*0x14*/ s32 step1;
    /*0x18*/ s32 step2;
    /*0x1C*/ s32 *value;
    /*0x20*/ s32 flags;
    /*0x24*/ s32 leafFlag;
    /*0x28*/ void *func;
} MenuItem; // size 0x2C

typedef struct MenuDescendState {
    /*0x00*/ const char *title;
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

typedef struct DebugMenuData {
    s32 val00;
    s32 val04;
    s32 val08;
    s32 val0C;
    s32 val10;
    s32 val14;
    s32 val18;
    s32 val1C;
    s32 val20;
    s32 val24;
    s32 val28;
    s32 val2C;
    s32 val30;
    s32 val34;
    s8 mode;
    s8 modeChanged;
    u8 pad3A[2];
} DebugMenuData;

typedef struct DebugEnvData {
    s32 val3C;
    s32 val40;
    s32 val44;
    s32 val48;
    s32 val4C;
    s32 val50;
    s32 val54;
    s32 val58;
    s32 val5C;
} DebugEnvData;

typedef struct DebugCubeData {
    f32 cubePos[24];
    u32 cubeColor[6];
    u32 padD8[2];
    u8 cubeList[0x40];
} DebugCubeData;


static u8 gBssC[0xD8];
static MenuDescendState gMenuState;
static u8 gCamObj[0x154];

static DebugMenuData gDebugMenu = {
    150000, 50000, 6250, 12500, 5000, 500000, 2000000, 0, 0, 0, 0, 0, 0, 19,
    0, 0, {0, 0},
};

static DebugEnvData gDebugEnv = {
    100000000, 100, 100, 980665, 100, 100, 1000, 314000, 0,
};

static DebugCubeData gDebugCube = {
    { -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f },
    { 0xFF0000FF, 0x00FF00FF, 0x0000FFFF, 0xFFFF00FF, 0xFF00FFFF, 0x00FFFFFF },
    { 0, 0 },
    { 0x80, 0x00, 0x18, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x03, 0x00, 0x04, 0x01, 0x07, 0x01, 0x06, 0x01, 0x05, 0x01, 0x00, 0x02, 0x04, 0x02, 0x05, 0x02, 0x01, 0x02, 0x01, 0x03, 0x05, 0x03, 0x06, 0x03, 0x02, 0x03, 0x02, 0x04, 0x06, 0x04, 0x07, 0x04, 0x03, 0x04, 0x03, 0x05, 0x07, 0x05, 0x04, 0x05, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
};

static const char *gRootName = "MAIN MENU";

static const char *gModeNames[3] = { "A:Sim Start X:Sim Step", "A:Sim Start X:SimStep B:Reset", "A:Sim Stop  B:Reset" };

static MenuItem gRootItems[3] = {
        { 8, "BACK TO PREV MENU", 0, 0, 0, 0, 0, NULL, 256, -1, fn_1_28AE0 },
        { 8, "BAT MENU", 0, 0, 0, 0, 0, NULL, 256, 1, fn_1_28AE0 },
        { 0, NULL, 0, 0, 0, 0, 0, NULL, 0, 0, NULL },
};

static MenuItem gItems[26] = {
        { 8, "MAIN MENU", 0, 0, 0, 0, 0, NULL, 256, 0, fn_1_28AE0 },
        { 8, NULL, 0, 0, 0, 0, 0, NULL, 1792, 0, fn_1_289E0 },
        { 0, "SIM NUM  ", 1, 100, 1, 10, 20, &gDebugMenu.val34, 0, 0, NULL },
        { 1, "LENGTH   ", 0, 1000000, 1000, 100, 10000, &gDebugMenu.val00, 0, 0, NULL },
        { 1, "CENTER   ", 0, 1000000, 1000, 100, 10000, &gDebugMenu.val04, 0, 0, NULL },
        { 1, "RADIUS   ", 0, 1000000, 1000, 100, 10000, &gDebugMenu.val08, 0, 0, NULL },
        { 1, "MASS     ", 0, 1000000, 1000, 100, 10000, &gDebugMenu.val0C, 0, 0, NULL },
        { 1, "FIRST POS", -10000000, 10000000, 1000, 100, 10000, &gDebugMenu.val14, 0, 0, NULL },
        { 1, "FIRST ROT", -18000000, 18000000, 100000, 10000, 1000000, &gDebugMenu.val18, 0, 0, NULL },
        { 1, "VEL   X  ", -10000000, 10000000, 100, 1000, 10000, &gDebugMenu.val1C, 0, 0, NULL },
        { 1, "VEL   Y  ", -10000000, 10000000, 100, 1000, 10000, &gDebugMenu.val20, 0, 0, NULL },
        { 1, "VEL   Z  ", -10000000, 10000000, 100, 1000, 10000, &gDebugMenu.val24, 0, 0, NULL },
        { 1, "OMEGA X  ", -10000000, 10000000, 100, 1000, 10000, &gDebugMenu.val28, 0, 0, NULL },
        { 1, "OMEGA Y  ", -10000000, 10000000, 100, 1000, 10000, &gDebugMenu.val2C, 0, 0, NULL },
        { 1, "OMEGA Z  ", -10000000, 10000000, 100, 1000, 10000, &gDebugMenu.val30, 0, 0, NULL },
        { 1, "AIR REG  ", -10000000, 10000000, 10, 100, 1000, &gDebugMenu.val10, 0, 0, NULL },
        { 1, "ENV K    ", -100000000, 100000000, 10000, 100000, 1000000, &gDebugEnv.val3C, 0, 0, NULL },
        { 1, "ENV D    ", -100000000, 100000000, 100, 1000, 10000, &gDebugEnv.val40, 0, 0, NULL },
        { 1, "ENV E    ", -100000000, 100000000, 10, 100, 1000, &gDebugEnv.val44, 0, 0, NULL },
        { 1, "ENV MK   ", 0, 100000000, 1000, 10000, 100000, &gDebugEnv.val5C, 0, 0, NULL },
        { 1, "ENV R CAP", 0, 100000000, 1000, 10000, 100000, &gDebugEnv.val48, 0, 0, NULL },
        { 1, "ENV R CUT", 0, 100000000, 10, 100, 1000, &gDebugEnv.val4C, 0, 0, NULL },
        { 1, "ENV M CUT", 0, 100000000, 1000, 10000, 100000, &gDebugEnv.val50, 0, 0, NULL },
        { 1, "ENV S CAP", 0, 100000000, 100, 1000, 10000, &gDebugEnv.val54, 0, 0, NULL },
        { 1, "ENV O CAP", 0, 100000000, 1000, 10000, 100000, &gDebugEnv.val58, 0, 0, NULL },
        { 0, NULL, 0, 0, 0, 0, 0, NULL, 0, 0, NULL },
};

static MenuItem *gLevels[2] = { &gRootItems[0], &gItems[0] };

static const Vec sZeroVec = { 0.0f, 0.0f, 0.0f };

// .text:0x00029A9C size:0x1C0
void fn_1_29A9C(void) {
    f32 v0 = (f32)gDebugMenu.val00 / 100000.0f;
    f32 v4 = (f32)gDebugMenu.val04 / 100000.0f;
    f32 v8 = (f32)gDebugMenu.val08 / 100000.0f;
    f32 vC = (f32)gDebugMenu.val0C / 100000.0f;

    fn_80037768(gCamObj, 2, gDebugMenu.val34, v0, v4, v8, vC);
    fn_1_273D8(gBssC);

    gDebugMenu.mode = 0;
    fn_1_28C34(&gMenuState, 0, NULL);

    fn_800B806C(0, -240.0f, 240.0f, -320.0f, 320.0f, -512.0f, -1.0f, 1280.0f);

    currentDrawingItem->func = fn_1_295E8;
}

// .text:0x00029A48 size:0x54
void fn_1_29A48(void) {
    fn_800AD038(*(void **)(lbl_80366158 + 0x8));
    fn_800A97D0(0x10, 0x1e);
    currentDrawingItem->currentDrawingItem->state = 1;
    removeCurrentDrawingItem();
}

// .text:0x000295E8 size:0x460
void fn_1_295E8(void) {
    DrawingSceneStruct *item = currentDrawingItem;

    fn_1_2948C(item);
    fn_1_2905C();
    fn_1_29414(item);
}

// .text:0x0002948C size:0x15C
void fn_1_2948C(void *arg0) {
    u16 in0 = AtBat_ButtonInput1._00;
    u16 in2 = AtBat_ButtonInput1._02;
    u16 in4 = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 0x4);
    u16 v0 = in0;
    u16 v2 = in2;
    u16 v4 = in4;

    if (in2 & PAD_BUTTON_START) {
        u8 flag = *((u8 *)arg0 + 0x14) ^ 1;
        *((u8 *)arg0 + 0x14) = flag;
        if (*((u8 *)arg0 + 0x14) != 0) {
            fn_800A97D0(0x20, 0);
        } else {
            fn_800A97D0(0x10, 0x1e);
        }
    } else if (*((u8 *)arg0 + 0x14) != 0) {
        s32 mask;

        if (in0 & PAD_BUTTON_Y) {
            mask = 0x91;
        } else {
            mask = (in0 & PAD_BUTTON_X) ? 0x50 : 0;
        }
        fn_80048820(&gMenuState, in0, in2, in4, (u8)mask);
        v0 = in0 & ~(PAD_BUTTON_X | PAD_BUTTON_Y);
        v2 = in2 & ~(PAD_BUTTON_X | PAD_BUTTON_Y);
        v4 = in4 & ~(PAD_BUTTON_X | PAD_BUTTON_Y);
    } else if (in2 & PAD_BUTTON_B) {
        fn_1_29A48();
    }

    fn_1_26D28(gBssC, v0, v2, v4, (u8 *)&AtBat_ButtonInput1 + 0x10);
    fn_1_27330(gBssC);
}

// .text:0x00029414 size:0x78
void fn_1_29414(void *arg0) {
    if (*((u8 *)arg0 + 0x14) != 0) {
        fn_80048BEC(&gMenuState, 0, 0);
    }
    fn_1_272DC(gBssC, 0);
    fn_1_AF4(10, 10, 1.0f);
    fn_1_28CE8(arg0);
}

// .text:0x0002935C size:0xB8
void fn_1_2935C(void *cam) {
    fn_80037768(cam, 2, gDebugMenu.val34, (f32)gDebugMenu.val00 / 100000.0f, (f32)gDebugMenu.val04 / 100000.0f,
                (f32)gDebugMenu.val08 / 100000.0f, (f32)gDebugMenu.val0C / 100000.0f);
}

// .text:0x0002905C size:0x300
void fn_1_2905C(void) {
    switch (gDebugMenu.mode) {
    case 0: {
        f32 v0 = (f32)gDebugMenu.val00 / 100000.0f;
        f32 v4 = (f32)gDebugMenu.val04 / 100000.0f;
        f32 v8 = (f32)gDebugMenu.val08 / 100000.0f;
        f32 vC = (f32)gDebugMenu.val0C / 100000.0f;

        fn_80037768(gCamObj, 2, gDebugMenu.val34, v0, v4, v8, vC);

        ((Vec *)(gCamObj + 0xE8))->x = 0.0f;
        ((Vec *)(gCamObj + 0xE8))->y = (f32)gDebugMenu.val14 / 100000.0f;
        ((Vec *)(gCamObj + 0xE8))->z = 0.0f;
        ((Vec *)(gCamObj + 0x11C))->x = (f32)gDebugMenu.val1C / 100000.0f;
        ((Vec *)(gCamObj + 0x11C))->y = (f32)gDebugMenu.val20 / 100000.0f;
        ((Vec *)(gCamObj + 0x11C))->z = (f32)gDebugMenu.val24 / 100000.0f;
        PSMTXMultVec((f32(*)[4])(gCamObj + 0xB8), (Vec *)(gCamObj + 0x11C), (Vec *)(gCamObj + 0x128));

        {
            Mtx m;

            ((Vec *)(gCamObj + 0x140))->x = (f32)gDebugMenu.val28 / 100000.0f;
            ((Vec *)(gCamObj + 0x140))->y = (f32)gDebugMenu.val2C / 100000.0f;
            ((Vec *)(gCamObj + 0x140))->z = (f32)gDebugMenu.val30 / 100000.0f;
            PSMTXRotRad(m, 'X', ((f32)gDebugMenu.val18 / 100000.0f) * 0.017453292f);
            C_QUATMtx((Quaternion *)(gCamObj + 0xF4), m);
            fn_800383BC(gCamObj);
        }
        break;
    }
    case 1:
        if (gDebugMenu.modeChanged == 0) {
            break;
        }
        gDebugMenu.modeChanged = 0;
    case 2:
        *(f32 *)(gCamObj + 0x50) = (f32)gDebugMenu.val10 / 100000.0f;
        fn_80037054(gCamObj, &gDebugEnv.val3C);
        break;
    }
}

// .text:0x00028CE8 size:0x374
void fn_1_28CE8(void *arg0) {
    u8 *base = (u8 *)&gDebugMenu;
    Mtx m;
    f32 scaleXY = (f32)gDebugMenu.val08 / 100000.0f;
    f32 scaleZ = (f32)gDebugMenu.val00 / 100000.0f;

    PSMTXScale(m, scaleXY, scaleXY, scaleZ);
    PSMTXConcat((f32(*)[4])(gCamObj + 0x58), m, m);
    PSMTXConcat((f32(*)[4])gBssC, m, m);
    GXLoadPosMtxImm(m, 0);
    GXSetCurrentMtx(0);

    gOz_GXSetTexture(GX_PASSCLR, 0, FALSE);

    GXBegin(GX_LINES, GX_VTXFMT0, 6);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXColor1u32(0xFF0000FF);
    GXPosition3f32(1.0f, 0.0f, 0.0f);
    GXColor1u32(0xFF0000FF);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXColor1u32(0x00FF00FF);
    GXPosition3f32(0.0f, 1.0f, 0.0f);
    GXColor1u32(0x00FF00FF);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXColor1u32(0x0000FFFF);
    GXPosition3f32(0.0f, 0.0f, 1.0f);
    GXColor1u32(0x0000FFFF);
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
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2X4, GX_TG_TEX0, 0x3C, GX_FALSE, 0x7D);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetCullMode(GX_CULL_BACK);
    GXCallDisplayList(base + 0xE0, 0x40);

    {
        Vec v;

        PSMTXMultVec((f32(*)[4])(gCamObj + 0x58), (Vec *)gCamObj, &v);
        PSMTXMultVec((f32(*)[4])(gCamObj + 0x58), (Vec *)(gCamObj + 0xC), &v);
        PSVECCrossProduct((Vec *)gCamObj, (Vec *)(gCamObj + 0x140), &v);
        PSMTXMultVec((f32(*)[4])(gCamObj + 0x88), &v, &v);
        PSVECCrossProduct((Vec *)(gCamObj + 0xC), (Vec *)(gCamObj + 0x140), &v);
        PSMTXMultVec((f32(*)[4])(gCamObj + 0x88), &v, &v);
        PSVECScale((Vec *)(gCamObj + 0x104), *(f32 *)(gCamObj + 0x28), &v);
    }
}

// .text:0x00028C34 size:0xB4
void fn_1_28C34(MenuDescendState *state, s32 level, const char *value) {
    state->title = value ? value : gRootName;
    state->unk08 = 0x10;
    state->unk0C = 0;
    state->index = 0;
    state->unk14 = 1;
    state->items = gLevels[level];
    if (level == 1) {
        if (gItems[1].name == 0) {
            gItems[1].name = gModeNames[gDebugMenu.mode];
        }
    }
    state->count = 0;
    while (state->items[state->count].name != 0) {
        state->count++;
    }
}

// .text:0x00028AE0 size:0x154
s32 fn_1_28AE0(MenuDescendState *state) {
    u8 *scene = (u8 *)currentDrawingItem;
    s8 leaf;

    scene[0x15] = state->items[state->index].leafFlag;
    leaf = scene[0x15];
    if (leaf < 0) {
        fn_1_29A48();
    } else {
        fn_1_28C34(state, leaf, state->items[state->index].name);
    }
    return 0;
}

// .text:0x000289E0 size:0x100
s32 fn_1_289E0(MenuDescendState *state, u16 input) {
    switch (gDebugMenu.mode) {
    case 0:
        if (input & PAD_BUTTON_A) {
            gDebugMenu.mode = 2;
        } else if (input & PAD_BUTTON_X) {
            gDebugMenu.modeChanged = 1;
            gDebugMenu.mode = 1;
        }
        break;
    case 1:
        if (input & PAD_BUTTON_A) {
            gDebugMenu.mode = 2;
        } else if (input & PAD_BUTTON_B) {
            gDebugMenu.mode = 0;
        } else if (input & PAD_BUTTON_X) {
            gDebugMenu.modeChanged = 1;
        }
        break;
    case 2:
        if (input & PAD_BUTTON_A) {
            gDebugMenu.mode = 1;
        } else if (input & PAD_BUTTON_B) {
            gDebugMenu.mode = 0;
        }
        break;
    }

    state->items[state->index].name = gModeNames[gDebugMenu.mode];
    return 0;
}

// .text:0x000289C0 size:0x20
void fn_1_289C0(void *arg0) {
    fn_1_273D8(arg0);
}

// .text:0x0002858C size:0x434
void fn_1_2858C(DebugCamState *state, u32 buttons, u32 flags, s32 arg3, u8 *stick) {
    Quaternion q;
    Vec tmp;
    Mtx m;
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

    tmp.x = (state->moveScale * (f32)-(s8)stick[0]) * 0.0078125f / 60.0f;
    tmp.z = (state->moveScale * (f32)(s8)stick[1]) * 0.0078125f / 60.0f;
    tmp.y = tmp.y - (state->moveScale * (f32)stick[4]) / 150.0f / 60.0f;
    tmp.y = tmp.y + (state->moveScale * (f32)stick[5]) / 150.0f / 60.0f;

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
