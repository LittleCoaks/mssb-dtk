#define REP_HEADER_DATA_FN getRepHeaderData_rep7A28
#include "debug/rep_7A28.h"
#define SQRT2_LINKAGE static
#include "game/UnknownHomes_Game.h"
#include "header_rep_data.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x800a7568.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/GX/GXFifo.h"
#include "Dolphin/GX/GXGeometry.h"
#include "Dolphin/GX/GXPixel.h"
#include "Dolphin/mtx.h"
#include "Dolphin/pad.h"
#include "stl/mem.h"

extern void fn_80030D88(Vec *start, Vec *dir, void *slot, int arg);
extern void fn_8002F5F4(Vec *start, Vec *dir, void *header);
extern void fn_80030470(Vec *start, Vec *dir, Vec *end, void *slot, int arg);
extern void fn_80048BEC(void *arg0, s32 arg1, s32 arg2);
extern void fn_80048820(void *arg0, u16 arg1, u16 arg2, u16 arg3, u8 arg4);
extern void fn_800AD038(void *arg0);
extern void fn_8003414C(Mtx m);
extern void fn_1_272DC(void *arg0, s32 arg1);
extern void fn_1_AF4(s32 arg0, s32 arg1, f32 arg2);
extern void fn_1_F2C(s32 arg0, s32 arg1, s32 arg2);
extern void fn_1_26D28(void *arg0, u16 arg1, u16 arg2, u16 arg3, void *arg4);
extern void fn_1_27330(void *arg0);
extern void fn_1_273D8(void *arg0);
extern void GXDrawSphere1(u8 subdivisions);
extern void minigamesGXStuff(void);
extern void *ARAMTransfer(void *file, s32 arg1, s32 arg2, s32 arg3);
extern void convertTextureHeader(void *tex);
extern void *_OSAllocFromHeap(s32 alignment, s32 size);
extern u8 lbl_80366158[0x30];


void (*lbl_1_data_108E8[2])(void) = {fn_1_27AD4, fn_1_276CC};
void (*lbl_1_data_108F0[2])(void) = {fn_1_27AD0, fn_1_27594};
u32 lbl_1_data_108F8[4] = {0x40B, 0x40046100, 0xE641000, 0x24B48};
DbgTexEntry lbl_1_data_10908[3] = {
    {NULL, 0x0, 0x5, 0x445C0, 0x0, 0x0, 0x4, 0x2, 0x1D4C0, 0x15F90,
     0x0, 0x80, 0xF4240, 0xF4240, -0x7A120, 0x7A120, 0xFFFFFF00, 0x0, -0x6D60, 0x1},
    {NULL, 0x0, 0xA, 0x130B0, 0xEA60, 0xC350, 0xC, 0x6, 0x1A9C8, 0x18A88,
     0x0, 0x28, 0x44AA20, 0x90F560, -0xF4240, 0x44AA20, 0xFFFFFF00, 0x0, 0x0, 0x0},
    {NULL, 0x0, 0x3, 0x15F90, 0x186A0, 0x2710, 0x14, 0xA, 0x19258, 0x19E0F,
     0x0, 0x3C, 0x989680, 0x112A880, 0xF4240, -0xF4240, 0x3C3C3C00, 0x0, 0x0, 0x0},
};
void *lbl_1_data_109F8[2] = {
    (void *)0x0, (void *)0x14
};
void *lbl_1_data_10A00 = (void *)0x8;
void *lbl_1_data_10A04 = (void *)0x7;
void *lbl_1_data_10A08 = (void *)0x3D090;
void *lbl_1_data_10A0C = (void *)0xC350;
void *lbl_1_data_10A10 = (void *)0x86470;
void *lbl_1_data_10A14[561] = {
    (void *)0x0, (void *)0xFF, (void *)0xC, (void *)0xD,
    (void *)0xE, (void *)0xF, (void *)0x10, (void *)0x11,
    (void *)0x12, (void *)0x13, (void *)0x0, "NUM     ",
    (void *)0x1, (void *)0x64, (void *)0x1, (void *)0xA,
    (void *)0x14, (void *)&lbl_1_data_10908[0].num, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x1, "SIZE    ", (void *)0xA,
    (void *)0x989680, (void *)0x64, (void *)0xA, (void *)0x3E8,
    (void *)&lbl_1_data_10908[0].size, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x1, "SPEED   ", (void *)0x0, (void *)0x989680,
    (void *)0x64, (void *)0xA, (void *)0x3E8, (void *)&lbl_1_data_10908[0].speed,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x1,
    "SLOWDOWN", (void *)0x0, (void *)0x989680, (void *)0x64,
    (void *)0xA, (void *)0x3E8, (void *)&lbl_1_data_10908[0].slowdown, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0, "LIFE    ",
    (void *)0x1, (void *)0x64, (void *)0x1, (void *)0xA,
    (void *)0x14, (void *)&lbl_1_data_10908[0].life, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x0, "LIFETURN", (void *)0x1,
    (void *)0x64, (void *)0x1, (void *)0xA, (void *)0x14,
    (void *)&lbl_1_data_10908[0].lifeTurn, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x1, "SCALE UP", (void *)0x0, (void *)0x989680,
    (void *)0x64, (void *)0xA, (void *)0x3E8, (void *)&lbl_1_data_10908[0].scaleUp,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x1,
    "SCALE DN", (void *)0x0, (void *)0x989680, (void *)0x64,
    (void *)0xA, (void *)0x3E8, (void *)&lbl_1_data_10908[0].scaleDown, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0, "MAXALPHA",
    (void *)0x0, (void *)0xFF, (void *)0x1, (void *)0xA,
    (void *)0x14, (void *)&lbl_1_data_10908[0].maxAlpha, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x1, "SP ANGLE", (void *)0x0,
    (void *)0x989680, (void *)0x64, (void *)0xA, (void *)0x3E8,
    (void *)&lbl_1_data_10908[0].spAngle, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x1, "HANG MAX", (void *)0x0, (void *)0x112A880,
    (void *)0x186A0, (void *)0x2710, (void *)0xF4240, (void *)&lbl_1_data_10908[0].hAngMax,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x1,
    "VANG MIN", (void *)0xFEED5780, (void *)0x112A880, (void *)0x186A0,
    (void *)0x2710, (void *)0xF4240, (void *)&lbl_1_data_10908[0].vAngMin, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x1, "VANG MAX",
    (void *)0xFEED5780, (void *)0x112A880, (void *)0x186A0, (void *)0x2710,
    (void *)0xF4240, (void *)&lbl_1_data_10908[0].vAngMax, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x1, "BIAS    ", (void *)0xFF676980,
    (void *)0x989680, (void *)0x64, (void *)0xA, (void *)0x3E8,
    (void *)&lbl_1_data_10908[0].bias, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0,
    "NUM     ", (void *)0x1, (void *)0x64, (void *)0x1,
    (void *)0xA, (void *)0x14, (void *)&lbl_1_data_10908[1].num, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x1, "SIZE    ",
    (void *)0xA, (void *)0x989680, (void *)0x64, (void *)0xA,
    (void *)0x3E8, (void *)&lbl_1_data_10908[1].size, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x1, "SPEED   ", (void *)0x0,
    (void *)0x989680, (void *)0x64, (void *)0xA, (void *)0x3E8,
    (void *)&lbl_1_data_10908[1].speed, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x1, "SLOWDOWN", (void *)0x0, (void *)0x989680,
    (void *)0x64, (void *)0xA, (void *)0x3E8, (void *)&lbl_1_data_10908[1].slowdown,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0,
    "LIFE    ", (void *)0x1, (void *)0x64, (void *)0x1,
    (void *)0xA, (void *)0x14, (void *)&lbl_1_data_10908[1].life, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0, "LIFETURN",
    (void *)0x1, (void *)0x64, (void *)0x1, (void *)0xA,
    (void *)0x14, (void *)&lbl_1_data_10908[1].lifeTurn, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x1, "SCALE UP", (void *)0x0,
    (void *)0x989680, (void *)0x64, (void *)0xA, (void *)0x3E8,
    (void *)&lbl_1_data_10908[1].scaleUp, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x1, "SCALE DN", (void *)0x0, (void *)0x989680,
    (void *)0x64, (void *)0xA, (void *)0x3E8, (void *)&lbl_1_data_10908[1].scaleDown,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0,
    "MAXALPHA", (void *)0x0, (void *)0xFF, (void *)0x1,
    (void *)0xA, (void *)0x14, (void *)&lbl_1_data_10908[1].maxAlpha, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x1, "SP ANGLE",
    (void *)0x0, (void *)0x989680, (void *)0x64, (void *)0xA,
    (void *)0x3E8, (void *)&lbl_1_data_10908[1].spAngle, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x1, "HANG MAX", (void *)0x0,
    (void *)0x112A880, (void *)0x186A0, (void *)0x2710, (void *)0xF4240,
    (void *)&lbl_1_data_10908[1].hAngMax, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x1, "VANG MIN", (void *)0xFEED5780, (void *)0x112A880,
    (void *)0x186A0, (void *)0x2710, (void *)0xF4240, (void *)&lbl_1_data_10908[1].vAngMin,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x1,
    "VANG MAX", (void *)0xFEED5780, (void *)0x112A880, (void *)0x186A0,
    (void *)0x2710, (void *)0xF4240, (void *)&lbl_1_data_10908[1].vAngMax, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x0, "NUM     ", (void *)0x1,
    (void *)0x64, (void *)0x1, (void *)0xA, (void *)0x14,
    (void *)&lbl_1_data_10908[2].num, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x1, "SIZE    ", (void *)0xA, (void *)0x989680,
    (void *)0x64, (void *)0xA, (void *)0x3E8, (void *)&lbl_1_data_10908[2].size,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x1,
    "SPEED   ", (void *)0x0, (void *)0x989680, (void *)0x64,
    (void *)0xA, (void *)0x3E8, (void *)&lbl_1_data_10908[2].speed, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x1, "SLOWDOWN",
    (void *)0x0, (void *)0x989680, (void *)0x64, (void *)0xA,
    (void *)0x3E8, (void *)&lbl_1_data_10908[2].slowdown, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x0, "LIFE    ", (void *)0x1,
    (void *)0x64, (void *)0x1, (void *)0xA, (void *)0x14,
    (void *)&lbl_1_data_10908[2].life, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x0, "LIFETURN", (void *)0x1, (void *)0x64,
    (void *)0x1, (void *)0xA, (void *)0x14, (void *)&lbl_1_data_10908[2].lifeTurn,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x1,
    "SCALE UP", (void *)0x0, (void *)0x989680, (void *)0x64,
    (void *)0xA, (void *)0x3E8, (void *)&lbl_1_data_10908[2].scaleUp, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x1, "SCALE DN",
    (void *)0x0, (void *)0x989680, (void *)0x64, (void *)0xA,
    (void *)0x3E8, (void *)&lbl_1_data_10908[2].scaleDown, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x0, "MAXALPHA", (void *)0x0,
    (void *)0xFF, (void *)0x1, (void *)0xA, (void *)0x14,
    (void *)&lbl_1_data_10908[2].maxAlpha, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x1, "SP ANGLE", (void *)0x0, (void *)0x989680,
    (void *)0x64, (void *)0xA, (void *)0x3E8, (void *)&lbl_1_data_10908[2].spAngle,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x1,
    "HANG MAX", (void *)0x0, (void *)0x112A880, (void *)0x186A0,
    (void *)0x2710, (void *)0xF4240, (void *)&lbl_1_data_10908[2].hAngMax, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x1, "VANG MIN",
    (void *)0xFEED5780, (void *)0x112A880, (void *)0x186A0, (void *)0x2710,
    (void *)0xF4240, (void *)&lbl_1_data_10908[2].vAngMin, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x1, "VANG MAX", (void *)0xFEED5780,
    (void *)0x112A880, (void *)0x186A0, (void *)0x2710, (void *)0xF4240,
    (void *)&lbl_1_data_10908[2].vAngMax, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0,
    "NUM     ", (void *)0x2, (void *)0x8, (void *)0x1,
    (void *)0x1, (void *)0x1, (void *)&lbl_1_data_10A00, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0, "TAILNUM ",
    (void *)0x1, (void *)0x7, (void *)0x1, (void *)0x1,
    (void *)0x1, (void *)&lbl_1_data_10A04, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x1, "SIZE    ", (void *)0xA,
    (void *)0x989680, (void *)0x64, (void *)0xA, (void *)0x3E8,
    (void *)&lbl_1_data_10A08, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x1, "TAILSIZE", (void *)0xA, (void *)0x989680,
    (void *)0x64, (void *)0xA, (void *)0x3E8, (void *)&lbl_1_data_10A0C,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x1,
    "LENGTH  ", (void *)0xA, (void *)0x989680, (void *)0x64,
    (void *)0xA, (void *)0x3E8, (void *)&lbl_1_data_10A10, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0, "CENTER  ",
    (void *)0x0, (void *)0x7, (void *)0x1, (void *)0x1,
    (void *)0x1, (void *)&lbl_1_data_10A14, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x0
};

#define DBG_SCENE() ((DbgScene *)currentDrawingItem)
#define PAD_U16(off) (*(u16 *)((u8 *)&AtBat_ButtonInput1 + (off)))
#define PAD_CUR PAD_U16(0x0)
#define PAD_NEW PAD_U16(0x2)
#define PAD_PROC PAD_U16(0x4)

// .text:0x00028200 size:0xF4
void fn_1_28200(void) {
    DbgScene *item = DBG_SCENE();

    item->state = 0;
    fn_800AD038(*(void **)(lbl_80366158 + 0x8));
    item->mtx = _OSAllocFromHeap(0x20, 0xDC);
    fn_1_273D8(item->mtx);
    item->menu = _OSAllocFromHeap(0x20, 0x1C);
    item->menu->unk8 = 0x10;
    item->menu->unk14 = 1;
    ((f32 *)item->mtx)[0x8C / 4] *= -1.0f;
    item->pos.x = 0.0f;
    item->pos.y = -1.0f;
    item->pos.z = 0.0f;
    item->radius = 1.0f;
    item->scale = 1.0f;
    item->mode = 0;
    item->field = 0;
    item->flags = 0;
    DBG_SCENE()->func = fn_1_28118;
}

// .text:0x00028118 size:0xE8
void fn_1_28118(void) {
    DbgScene *item = DBG_SCENE();

    switch (item->state) {
    case 0:
        item->state++;
        item->tex = ARAMTransfer(lbl_1_data_108F8, 0, 0, 0);
        // fallthrough
    case 1:
        if (lbl_803C6CF8.cancel.bytes[1] == 1) {
            item->tex = (u8 *)item->tex + *(u32 *)item->tex;
            convertTextureHeader(item->tex);
            fn_1_27560(item->tex);
            DBG_SCENE()->func = fn_1_27E98;
        }
        break;
    }
}

// .text:0x00027E98 size:0x280
void fn_1_27E98(void) {
    DbgScene *item = DBG_SCENE();
    Mtx m;
    Vec v;

    if (item->flags & 1) {
        lbl_1_data_108E8[item->mode]();
    } else {
        u8 buf[6];
        memcpy(buf, (u8 *)&AtBat_ButtonInput1 + 0x10, 6);
        buf[0] = -buf[0];
        buf[4] = *((u8 *)&AtBat_ButtonInput1 + 0x15);
        buf[5] = *((u8 *)&AtBat_ButtonInput1 + 0x14);
        fn_1_26D28(DBG_SCENE()->mtx, PAD_CUR, PAD_NEW, PAD_PROC, buf);
    }
    if (PAD_NEW & INPUT_BUTTON_START) {
        DBG_SCENE()->flags ^= 1;
    }
    fn_1_27330(item->mtx);

    item = DBG_SCENE();
    fn_8003414C(item->mtx);
    fn_1_272DC(item->mtx, 0);
    fn_1_AF4(0x14, 0x14, 1.0f);
    PSMTXScale(m, item->scale, item->scale, item->scale);
    PSMTXTransApply(m, m, item->pos.x, item->pos.y, item->pos.z);
    PSMTXConcat(item->mtx, m, item->mtx);
    fn_1_272DC(item->mtx, 0);
    fn_1_F2C(4, 0, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXDrawSphere1(2);
    PSMTXTrans(m, item->pos.x, item->pos.y, item->pos.z);
    PSMTXConcat(item->mtx, m, item->mtx);
    fn_1_272DC(item->mtx, 0);
    fn_1_F2C(4, 0, 0);
    GXBegin(GX_LINES, 0, 2);
    GXPosition3f32(item->pos.x, item->pos.y, item->pos.z);
    GXColor1u32(0xFF0000FF);
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = item->radius;
    PSVECAdd(&item->pos, &v, &v);
    GXPosition3f32(v.x, v.y, v.z);
    GXColor1u32(0xFF0000FF);
    lbl_1_data_108F0[item->mode]();
    minigamesGXStuff();
}

// .text:0x00027E50 size:0x48
void fn_1_27E50(void) {
    fn_800AD038(*(void **)(lbl_80366158 + 0x8));
    currentDrawingItem->currentDrawingItem->state = 1;
    removeCurrentDrawingItem();
}

// .text:0x00027D6C size:0xE4
void fn_1_27D6C(void) {
    if (DBG_SCENE()->flags & 1) {
        lbl_1_data_108E8[DBG_SCENE()->mode]();
    } else {
        u8 buf[6];
        memcpy(buf, (u8 *)&AtBat_ButtonInput1 + 0x10, 6);
        buf[0] = -buf[0];
        buf[4] = *((u8 *)&AtBat_ButtonInput1 + 0x15);
        buf[5] = *((u8 *)&AtBat_ButtonInput1 + 0x14);
        fn_1_26D28(DBG_SCENE()->mtx, PAD_CUR, PAD_NEW, PAD_PROC, buf);
    }
    if (PAD_NEW & INPUT_BUTTON_START) {
        DBG_SCENE()->flags ^= 1;
    }
}

// .text:0x00027BB8 size:0x1B4
void fn_1_27BB8(void) {
    DbgScene *item = DBG_SCENE();
    Mtx m;
    Vec v;

    fn_8003414C(item->mtx);
    fn_1_272DC(item->mtx, 0);
    fn_1_AF4(0x14, 0x14, 1.0f);
    PSMTXScale(m, item->scale, item->scale, item->scale);
    PSMTXTransApply(m, m, item->pos.x, item->pos.y, item->pos.z);
    PSMTXConcat(item->mtx, m, item->mtx);
    fn_1_272DC(item->mtx, 0);
    fn_1_F2C(4, 0, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXDrawSphere1(2);
    PSMTXTrans(m, item->pos.x, item->pos.y, item->pos.z);
    PSMTXConcat(item->mtx, m, item->mtx);
    fn_1_272DC(item->mtx, 0);
    fn_1_F2C(4, 0, 0);
    GXBegin(GX_LINES, 0, 2);
    GXPosition3f32(item->pos.x, item->pos.y, item->pos.z);
    GXColor1u32(0xFF0000FF);
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = item->radius;
    PSVECAdd(&item->pos, &v, &v);
    GXPosition3f32(v.x, v.y, v.z);
    GXColor1u32(0xFF0000FF);
    lbl_1_data_108F0[item->mode]();
    minigamesGXStuff();
}

// .text:0x00027AD4 size:0xE4
void fn_1_27AD4(void) {
    DbgScene *item;
    u16 proc = PAD_PROC;

    item = DBG_SCENE();
    if (proc & INPUT_BUTTON_UP) {
        item->field = (item->field + 1) % 2;
    } else if (proc & INPUT_BUTTON_DOWN) {
        item->field = (item->field + 1) % 2;
    } else if (PAD_NEW & INPUT_BUTTON_A) {
        item->mode = item->field + 1;
        item->field = 0;
    } else if (PAD_NEW & INPUT_BUTTON_B) {
        fn_800AD038(*(void **)(lbl_80366158 + 0x8));
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
    }
}

// .text:0x00027AD0 size:0x4
void fn_1_27AD0(void) {
}

// .text:0x000276CC size:0x404
void fn_1_276CC(void) {
    u8 *data = (u8 *)lbl_1_data_108E8;
    DbgScene *item = DBG_SCENE();

    if (item->flags & 8) {
        fn_80048820(item->menu, PAD_CUR, PAD_NEW, PAD_PROC, *((u8 *)&AtBat_ButtonInput1 + 0x15));
        if (PAD_CUR & INPUT_BUTTON_A) {
            DBG_SCENE()->flags &= ~2;
            DBG_SCENE()->flags |= 2;
        } else if (PAD_NEW & INPUT_BUTTON_B) {
            DBG_SCENE()->flags ^= 8;
        }
    } else if (PAD_PROC & INPUT_BUTTON_UP) {
        item->field = (item->field + 6) % 7;
    } else if (PAD_PROC & INPUT_BUTTON_DOWN) {
        item->field = (item->field + 1) % 7;
    } else if (PAD_PROC & INPUT_BUTTON_LEFT) {
        switch (item->field) {
        case 0:
            item->flags ^= 4;
            break;
        case 1:
            item->scale *= 0.5f;
            break;
        case 2:
            item->radius = item->radius - (f32)(item->radius > 1.0f);
            break;
        }
    } else if (PAD_PROC & INPUT_BUTTON_RIGHT) {
        switch (item->field) {
        case 0:
            item->flags ^= 4;
            break;
        case 1:
            item->scale *= 2.0f;
            break;
        case 2:
            item->radius += 1.0f;
            break;
        }
    } else if (PAD_CUR & INPUT_BUTTON_A) {
        item->menu->unkC = 0;
        item->menu->unk10 = 0;
        item->menu->cursor = 0;
        switch (item->field) {
        case 3:
            item->menu->title = "Fire 0";
            item->menu->items = (DbgMenuItem *)(data + 0x154);
            DBG_SCENE()->flags ^= 8;
            break;
        case 4:
            item->menu->title = "Fire 1";
            item->menu->items = (DbgMenuItem *)(data + 0x3E8);
            DBG_SCENE()->flags ^= 8;
            break;
        case 5:
            item->menu->title = "Smoke";
            item->menu->items = (DbgMenuItem *)(data + 0x650);
            DBG_SCENE()->flags ^= 8;
            break;
        case 6:
            item->menu->title = "Fireball";
            item->menu->items = (DbgMenuItem *)(data + 0x8B8);
            DBG_SCENE()->flags ^= 8;
            break;
        default:
            item->menu->items = NULL;
            DBG_SCENE()->flags &= ~2;
            DBG_SCENE()->flags |= 2;
            break;
        }
        if (item->menu->items != NULL) {
            while (item->menu->items[item->menu->cursor].label != 0) {
                item->menu->cursor++;
            }
        }
    } else if (PAD_NEW & INPUT_BUTTON_B) {
        item->mode = 0;
        item->field = 0;
    }
}

// .text:0x00027594 size:0x138
void fn_1_27594(void) {
    DbgScene *item = DBG_SCENE();
    Vec dir;
    Vec local = {0.0f, 0.0f, 0.0f};
    s32 i;

    if ((item->flags & 2) || (item->flags & 4)) {
        dir.x = 0.0f;
        dir.y = 0.0f;
        dir.z = item->radius;
        for (i = 1; i < 3; i++) {
            fn_80030D88(&item->pos, &dir, &lbl_1_data_10908[i], 5);
        }
        fn_8002F5F4(&item->pos, &dir, lbl_1_data_109F8);
        PSVECNormalize(&dir, &dir);
        fn_80030470(&item->pos, &dir, &local, lbl_1_data_10908, 5);
        DBG_SCENE()->flags ^= 2;
    }
    if (DBG_SCENE()->flags & 8) {
        fn_80048BEC(item->menu, 1, 1);
    }
}

// .text:0x00027560 size:0x34
void fn_1_27560(void *tex) {
    lbl_1_data_10908[2].tex = tex;
    lbl_1_data_10908[1].tex = tex;
    lbl_1_data_10908[0].tex = tex;
    lbl_1_data_10908[0].fmt = 7;
    lbl_1_data_10908[1].fmt = 7;
    lbl_1_data_10908[2].fmt = 4;
    lbl_1_data_109F8[0] = tex;
}
