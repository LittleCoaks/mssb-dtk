#define REP_HEADER_DATA_FN getRepHeaderData_rep0010
#define SQRT2_LINKAGE static
#include "game/UnknownHomes_Game.h"
#include "header_rep_data.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/sub.h"
#include "Dolphin/GX/GXFifo.h"
#include "Dolphin/GX/GXFrameBuffer.h"
#include "Dolphin/GX/GXGeometry.h"
#include "Dolphin/GX/GXLight.h"
#include "Dolphin/GX/GXPixel.h"
#include "Dolphin/GX/GXTev.h"
#include "Dolphin/GX/GXTransform.h"
#include "Dolphin/mtx.h"
#include "debug/rep_0010.h"

typedef struct RepQuad {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ u8 *texBase;
    /* 0x0C */ u32 texIndex;
    /* 0x10 */ u32 mode;
    /* 0x14 */ u8 r;
    /* 0x15 */ u8 g;
    /* 0x16 */ u8 b;
    /* 0x17 */ u8 a;
} RepQuad;

typedef struct RepScene {
    /* 0x00 */ void (*func)(void);
    /* 0x04 */ struct DrawingSceneStruct *prev;
    /* 0x08 */ struct DrawingSceneStruct *next;
    /* 0x0C */ struct DrawingSceneStruct *parent;
    /* 0x10 */ s16 state;
    /* 0x12 */ u16 priority;
    /* 0x14 */ u16 unk14;
    /* 0x16 */ u16 unk16;
} RepScene;

extern MemoryStack lbl_80366158;
extern GXColor lbl_1_data_A8;

extern void fn_80009144(void);
extern void fn_1_16A0(void);

// .text:0x00001240 size:0x2F8
void fn_1_1240(RepQuad *quad) {
    Mtx44 proj;
    Mtx mtx;
    GXColor color;

    SetDisplayStateTexture((TextureBody *)(quad->texBase + quad->texIndex * 32 + 4), 0, 0);
    PSMTXIdentity(mtx);
    C_MTXOrtho(proj, 0.0f, 448.0f, 0.0f, 640.0f, 0.0f, 1.0f);
    GXLoadPosMtxImm(mtx, 0);
    GXSetCurrentMtx(0);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    gOz_GXSetTexture(GX_MODULATE, 0, FALSE);
    color.r = quad->r;
    color.g = quad->g;
    color.b = quad->b;
    color.a = quad->a;
    GXSetChanMatColor(GX_COLOR0A0, color);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_RASA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2X4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTexGens(1);
    if (quad->mode == 1) {
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    } else if (quad->mode == 2) {
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    }
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXColor1u32(-1);
    GXTexCoord2s16(0, 0);
    GXPosition3f32(256.0f, 0.0f, 0.0f);
    GXColor1u32(-1);
    GXTexCoord2s16(1, 0);
    GXPosition3f32(256.0f, 256.0f, 0.0f);
    GXColor1u32(-1);
    GXTexCoord2s16(1, 1);
    GXPosition3f32(0.0f, 256.0f, 0.0f);
    GXColor1u32(-1);
    GXTexCoord2s16(0, 1);
}

// .text:0x000011D0 size:0x70
void fn_1_11D0(void) {
    resetAllDrawingStructs();
    fn_80009144();
    fn_800AD054((int)lbl_80366158.hi, (int)lbl_80366158.lo);
    GXSetCopyClear(lbl_1_data_A8, 0xFFFFFF);
    currentDrawingItem->func = fn_1_16A0;
}

// .text:0x00001148 size:0x88
void fn_1_1148(void) {
    RepScene *scene = (RepScene *)currentDrawingItem;

    scene->unk16 = 0;
    scene->unk14 = 0;
    resetAllDrawingStructs();
    fn_80009144();
    fn_800AD054((int)lbl_80366158.hi, (int)lbl_80366158.lo);
    GXSetCopyClear(lbl_1_data_A8, 0xFFFFFF);
    currentDrawingItem->func = fn_1_16A0;
}

// .text:0x0000110C size:0x3C
void _prolog(void) {
    setDrawingListHeadFunctions(fn_1_1148);
    fn_800AD054((int)lbl_80366158.hi, (int)lbl_80366158.lo);
}

// .text:0x00001108 size:0x4
void _unresolved(void) {
    return;
}

// .text:0x00001104 size:0x4
void _epilog(void) {
    return;
}

// .text:0x00000F2C size:0x1D8
void fn_1_F2C(GXTevMode mode, s32 texFrac, BOOL hasNormals) {
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    if (hasNormals) {
        GXSetVtxDesc(GX_VA_NRM, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_POS_XYZ, GX_F32, 0);
    }
    switch (mode) {
    case GX_MODULATE:
    case GX_PASSCLR:
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_POS_XYZ, GX_RGBA8, 0);
        if (mode == GX_PASSCLR) {
            break;
        }
    case GX_REPLACE:
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        if (texFrac == -1) {
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_POS_XYZ, GX_F32, 0);
        } else {
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_POS_XYZ, GX_U16, (u8)texFrac);
        }
        break;
    }
    GXSetTevOrder(GX_TEVSTAGE0, (mode == GX_PASSCLR) ? GX_TEXCOORD_NULL : GX_TEXCOORD0,
                  (mode == GX_PASSCLR) ? GX_TEXMAP_NULL : GX_TEXMAP0, (mode == GX_REPLACE) ? GX_COLOR_NULL : GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2X4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumChans(mode != GX_REPLACE);
    GXSetNumTexGens(mode != GX_PASSCLR);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, mode);
}

// .text:0x00000AF4 size:0x438
void fn_1_AF4(s32 zCells, s32 xCells, f32 scale) {
    f32 x0;
    f32 z0;
    f32 xLen;
    f32 zLen;
    f32 x;
    f32 z;
    f32 z1;
    f32 x1;
    s32 i;

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_POS_XYZ, GX_RGBA8, 0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2X4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    x0 = -scale * (f32)xCells / 2.0f;
    z0 = -scale * (f32)zCells / 2.0f;
    xLen = (f32)xCells * scale;
    x = x0;
    GXBegin(GX_LINES, GX_VTXFMT0, (xCells + 1) * 2);
    zLen = (f32)zCells * scale;
    z1 = z0 + zLen;
    for (i = xCells; i >= 0; i--) {
        GXPosition3f32(x, 0.0f, z0);
        GXColor1u32(-1);
        GXPosition3f32(x, 0.0f, z1);
        x += scale;
        GXColor1u32(-1);
    }
    GXBegin(GX_LINES, GX_VTXFMT0, (zCells + 1) * 2);
    x1 = x0 + xLen;
    z = z0;
    for (i = zCells; i >= 0; i--) {
        GXPosition3f32(x0, 0.0f, z);
        GXColor1u32(-1);
        GXPosition3f32(x1, 0.0f, z);
        z += scale;
        GXColor1u32(-1);
    }
}

// .text:0x000005EC size:0x508
void fn_1_5EC(void) {
    Mtx44 proj;
    Mtx mtx;

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_POS_XYZ, GX_RGBA8, 0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2X4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    C_MTXOrtho(proj, 0.0f, 448.0f, 0.0f, 640.0f, 0.0f, 1.0f);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    PSMTXIdentity(mtx);
    GXLoadPosMtxImm(mtx, 0);
    GXSetCurrentMtx(0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, -0.5f);
    GXColor1u32(0x808080FF);
    GXPosition3f32(0.0f, 448.0f, -0.5f);
    GXColor1u32(0x808080FF);
    GXPosition3f32(640.0f, 448.0f, -0.5f);
    GXColor1u32(0x808080FF);
    GXPosition3f32(640.0f, 0.0f, -0.5f);
    GXColor1u32(0x808080FF);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(100.0f, 100.0f, -0.5f);
    GXColor1u32(0x00FF0080);
    GXPosition3f32(50.0f, 150.0f, -0.5f);
    GXColor1u32(0x00FF0080);
    GXPosition3f32(100.0f, 200.0f, -0.5f);
    GXColor1u32(0x00FF0080);
    GXPosition3f32(150.0f, 150.0f, -0.5f);
    GXColor1u32(0x00FF0080);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(120.0f, 100.0f, -0.5f);
    GXColor1u32(0xFF000080);
    GXPosition3f32(70.0f, 150.0f, -0.5f);
    GXColor1u32(0xFF000080);
    GXPosition3f32(120.0f, 200.0f, -0.5f);
    GXColor1u32(0xFF000080);
    GXPosition3f32(170.0f, 150.0f, -0.5f);
    GXColor1u32(0xFF000080);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(120.0f, 220.0f, -0.5f);
    GXColor1u32(0xFF000080);
    GXPosition3f32(70.0f, 270.0f, -0.5f);
    GXColor1u32(0xFF000080);
    GXPosition3f32(120.0f, 320.0f, -0.5f);
    GXColor1u32(0xFF000080);
    GXPosition3f32(170.0f, 270.0f, -0.5f);
    GXColor1u32(0xFF000080);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(100.0f, 220.0f, -0.5f);
    GXColor1u32(0x00FF0080);
    GXPosition3f32(50.0f, 270.0f, -0.5f);
    GXColor1u32(0x00FF0080);
    GXPosition3f32(100.0f, 320.0f, -0.5f);
    GXColor1u32(0x00FF0080);
    GXPosition3f32(150.0f, 270.0f, -0.5f);
    GXColor1u32(0x00FF0080);
}
