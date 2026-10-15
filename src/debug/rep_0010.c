#define REP_HEADER_DATA_FN getRepHeaderData_rep0010
#define SQRT2_LINKAGE static
#include "game/UnknownHomes_Game.h"
/* Weak local static placed ahead of the header table so the unit's first .rodata object stays a
 * weak symbol (see header_rep_data.h). */
inline const f32 *getRepLeadData_rep0010(void) {
    static const f32 repLeadData[] = {1.75f, 0.0f, 2.125f, 0.0f};
    return repLeadData;
}

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
#include "C3/anim.h"
#include "Unknown/File_0x800a7568.h"
#include "Unknown/File_0x800a8cbc.h"
#include "Unknown/File_0x800a70dc.h"
#include "Unknown/File_0x80025ddc.h"
#include "Unknown/File_0x800b4908.h"
#include "Unknown/File_0x800bcd60.h"
#include "Unknown/File_0x800bfe90.h"
#include "game/match_setup/match_loading.h"
#include "debug/rep_0010.h"

typedef struct RepQuad {
    /* 0x00 */ u32 tag;
    /* 0x04 */ void (*func)(struct RepQuad *);
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
    /* 0x16 */ s16 selection;
} RepScene;

typedef struct RepFileScene {
    /* 0x00 */ void (*func)(void);
    /* 0x04 */ struct DrawingSceneStruct *prev;
    /* 0x08 */ struct DrawingSceneStruct *next;
    /* 0x0C */ struct DrawingSceneStruct *parent;
    /* 0x10 */ s16 state;
    /* 0x12 */ u16 priority;
    /* 0x14 */ u32 *file;
    /* 0x18 */ union {
        u8 index;
        u8 *tex;
    } u;
} RepFileScene;

typedef struct RepPackedFile {
    union {
        u32 ptrs[5];
        struct {
            /* 0x00 */ u32 tex;
            /* 0x04 */ u32 layout;
            /* 0x08 */ u32 geo;
            /* 0x0C */ u32 skn;
            /* 0x10 */ u32 extra;
        };
    };
} RepPackedFile;

typedef struct RepQuadInit {
    /* 0x00 */ RepQuad quads[2];
    /* 0x30 */ u32 mode;
    /* 0x34 */ u32 color;
} RepQuadInit;

#define REP_MENU_COUNT 10
#define INPUT1_FIELD(type, off) (*(type *)((u8 *)&AtBat_ButtonInput1 + (off)))

extern MemoryStack lbl_80366158;
extern MatchFileDescriptor CharacterFiles[];

extern void haveActLayoutPointToGeoHeader(void *layout, void *geo);
extern u8 drawStadiumRelated;
extern void fn_80009144(void);
extern void fn_800A7D4C(s32 arg0, void *arg1);
extern BOOL fn_800A8518(u32 mode);
extern u32 fn_800A88C8(void);
extern void fn_800A8B78(void *stream);
extern void fn_1_66C4(void);
extern void fn_1_8B90(void);
extern void fn_1_17D90(void);
extern void fn_1_28200(void);
extern void fn_1_1D514(void);
extern void fn_1_26AF8(void);
extern void fn_1_A2E4(void);
extern void fn_1_24778(void);
extern void fn_1_2852C(void);
extern void fn_1_29A9C(void);

MatchFileDescriptor StadiumPropFiles_debug[7] = {
    {0x0000040B, 0x40022EF0, 0x07684800, 0x00016B18},
    {0x0000040B, 0x40020260, 0x0769B800, 0x00012864},
    {0x0000040B, 0x4002FDC0, 0x076AE800, 0x000207F8},
    {0x0000040B, 0x40024E2C, 0x076CF000, 0x000159AC},
    {0x0000040B, 0x4001CB88, 0x076E5000, 0x0000EE60},
    {0x0000040B, 0x40035BD0, 0x076F4000, 0x000257FC},
    {0x0000040B, 0x400397CC, 0x07719800, 0x00023FF4},
};

RepQuadInit lbl_1_data_70 = {
    {{0, fn_1_1240, 0, 0, 0, 0}, {0, fn_1_1240, 0, 0, 0, 0}},
    2,
    0xFFFFFFFF,
};

GXColor lbl_1_data_A8 = {0x11, 0x77, 0x55, 0x00};

MatchFileDescriptor lbl_1_data_AC[15] = {
    {0x00000000, 0x01070000, 0x00000000, 0x01070000},
    {0x00000000, 0x01040000, 0x01070000, 0x01040000},
    {0x00000000, 0x01020000, 0x020B0000, 0x01020000},
    {0x00000000, 0x01070000, 0x030D0000, 0x01070000},
    {0x00000000, 0x01088000, 0x04140000, 0x01088000},
    {0x00000000, 0x01040000, 0x051C8000, 0x01040000},
    {0x00000000, 0x00A18000, 0x06208000, 0x00A18000},
    {0x00000000, 0x00A18000, 0x06C20000, 0x00A18000},
    {0x00000000, 0x00AC0000, 0x07638000, 0x00AC0000},
    {0x00000000, 0x01010000, 0x080F8000, 0x01010000},
    {0x00000000, 0x009A8000, 0x09108000, 0x009A8000},
    {0x00000000, 0x00198000, 0x09AB0000, 0x00198000},
    {0x00000000, 0x00038000, 0x09C48000, 0x00038000},
    {0x00000000, 0x00C40000, 0x09C80000, 0x00C40000},
    {0x00000000, 0x00040000, 0x0A8C0000, 0x00040000},
};

static u32 lbl_1_bss_0;
static u8 lbl_1_bss_4[0x5C];

static inline void loadPackedFile(RepPackedFile *file) {
    s32 i;

    for (i = 0; i < 5; i++) {
        if (file->ptrs[i] != 0) {
            file->ptrs[i] += (u32)file;
        }
    }
    convertTextureHeader((void *)file->tex);
    LoadActorLayout((void *)file->layout);
    convertGeometryAndSknHeader((void *)file->geo, (void *)file->skn);
    haveActLayoutPointToGeoHeader((void *)file->layout, (void *)file->geo);
    if (file->extra != 0) {
        adjustInternalPointers((void *)file->extra);
    }
}

// .text:0x00001948 size:0x24
void fn_1_1948(void) {
    if (currentDrawingItem->state != 0) {
        currentDrawingItem->func = fn_1_11D0;
    }
}

// .text:0x000016A0 size:0x2A8
void fn_1_16A0(void) {
    RepScene *scene = (RepScene *)currentDrawingItem;
    u16 input = INPUT1_FIELD(u16, 4);

    if (input == INPUT_BUTTON_UP) {
        if (--scene->selection < 0) {
            scene->selection = REP_MENU_COUNT - 1;
        }
    } else if (input == INPUT_BUTTON_DOWN) {
        if (++scene->selection >= REP_MENU_COUNT) {
            scene->selection = 0;
        }
    } else if (AtBat_ButtonInput1._02 == INPUT_BUTTON_A) {
        switch ((u8)scene->selection) {
        case 0:
            insertGraphicDrawingFunction(fn_1_66C4, 10);
            currentDrawingItem->func = fn_1_1948;
            break;
        case 1:
            insertGraphicDrawingFunction(fn_1_8B90, 10);
            currentDrawingItem->func = fn_1_1948;
            break;
        case 2:
            insertGraphicDrawingFunction(fn_1_17D90, 10);
            currentDrawingItem->func = fn_1_1948;
            break;
        case 3:
            insertGraphicDrawingFunction(fn_1_28200, 10);
            currentDrawingItem->func = fn_1_1948;
            break;
        case 4:
            insertGraphicDrawingFunction(fn_1_1D514, 10);
            currentDrawingItem->func = fn_1_1948;
            break;
        case 5:
            insertGraphicDrawingFunction(fn_1_26AF8, 10);
            currentDrawingItem->func = fn_1_1948;
            break;
        case 6:
            insertGraphicDrawingFunction(fn_1_A2E4, 10);
            currentDrawingItem->func = fn_1_1948;
            break;
        case 7:
            insertGraphicDrawingFunction(fn_1_24778, 10);
            currentDrawingItem->func = fn_1_1948;
            break;
        case 8:
            insertGraphicDrawingFunction(fn_1_2852C, 10);
            currentDrawingItem->func = fn_1_1948;
            break;
        case 9:
            insertGraphicDrawingFunction(fn_1_29A9C, 10);
            currentDrawingItem->func = fn_1_1948;
            break;
        case 10:
        case 11:
        case 12:
        case 13:
            break;
        }
    } else if (AtBat_ButtonInput1._02 == INPUT_BUTTON_START) {
        scene->parent->state = 1;
    } else if ((AtBat_ButtonInput1._00 & (INPUT_BUTTON_B | INPUT_BUTTON_Y)) == (INPUT_BUTTON_B | INPUT_BUTTON_Y)) {
        scene->func = fn_1_58C;
    }
}

// .text:0x00001634 size:0x6C
void fn_1_1634(void) {
    if (lbl_803C6CF8.cancel.bytes[1] == 1) {
        ((RepFileScene *)currentDrawingItem)->file = ARAMTransfer(&StadiumPropFiles_debug[3], 0, 0, 0);
        currentDrawingItem->func = fn_1_15CC;
    }
}

// .text:0x000015CC size:0x68
void fn_1_15CC(void) {
    RepFileScene *scene = (RepFileScene *)currentDrawingItem;

    if (lbl_803C6CF8.cancel.bytes[1] == 1) {
        scene->u.tex = (u8 *)scene->file + *scene->file;
        convertTextureHeader(scene->u.tex);
        currentDrawingItem->func = fn_1_1538;
    }
}

// .text:0x00001538 size:0x94
void fn_1_1538(void) {
    RepFileScene *scene = (RepFileScene *)currentDrawingItem;
    RepQuadInit *init = (RepQuadInit *)&StadiumPropFiles_debug[7];
    RepQuad *quad;

    fn_800A7D4C(0, &init->quads[drawStadiumRelated]);
    quad = &init->quads[drawStadiumRelated];
    quad->texBase = scene->u.tex;
    quad->texIndex = lbl_1_bss_0;
    quad->mode = init->mode;
    *(u32 *)&quad->r = init->color;
}

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
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
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

    scene->selection = 0;
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
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
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
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2X4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumChans(mode != GX_REPLACE);
    GXSetNumTexGens(mode != GX_PASSCLR);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, mode);
}

// .text:0x00000AF4 size:0x438
void fn_1_AF4(s32 zCells, s32 xCells, f32 scale) {
    f32 x;
    f32 z0;
    f32 z1;
    f32 zLen;
    f32 x0;
    f32 x1;
    f32 xLen;
    s32 i;

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2X4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    xLen = (f32)xCells * scale;
    x0 = -scale * (f32)xCells / 2.0f;
    z0 = -scale * (f32)zCells / 2.0f;
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
    for (i = zCells; i >= 0; i--) {
        GXPosition3f32(x0, 0.0f, z0);
        GXColor1u32(-1);
        GXPosition3f32(x1, 0.0f, z0);
        z0 += scale;
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
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
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

// .text:0x000005E8 size:0x4
void fn_1_5E8(void) {
}

// .text:0x0000058C size:0x5C
void fn_1_58C(void) {
    insertGraphicDrawingFunction(fn_1_1E0, 0)->state = 0;
    currentDrawingItem->func = fn_1_568;
    currentDrawingItem->state = 0;
}

// .text:0x00000568 size:0x24
void fn_1_568(void) {
    if (currentDrawingItem->state == 1) {
        currentDrawingItem->func = fn_1_16A0;
    }
}

// .text:0x000001E0 size:0x388
void fn_1_1E0(void) {
    RepFileScene *scene = (RepFileScene *)currentDrawingItem;

    switch (scene->state) {
    case 0:
        LoadFile((char **)lbl_1_data_AC, (LoadFileNode *)lbl_1_bss_4, 0, NULL, TRUE);
        currentDrawingItem->state++;
    case 1:
        if (fn_800A8518(1)) {
            currentDrawingItem->state++;
        }
        break;
    case 2:
        if (INPUT1_FIELD(u16, 4) & INPUT_BUTTON_A) {
            scene->file = ARAMTransfer(&CharacterFiles[scene->u.index], 0, 0, 0);
            currentDrawingItem->state++;
        }
        break;
    case 3:
        if (lbl_803C6CF8.cancel.bytes[1] == 1) {
            switch (scene->u.index % 19) {
            case 0:
                loadPackedFile((RepPackedFile *)scene->file);
                break;
            case 1:
                loadPackedFile((RepPackedFile *)scene->file);
                break;
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
                ANIMGet((ANIMBank *)scene->file);
                break;
            }
            fn_800ACFB0(scene->file);
            if (AtBat_ButtonInput1._00 & INPUT_BUTTON_B) {
                currentDrawingItem->state++;
            } else {
                scene->file = ARAMTransfer(&CharacterFiles[++scene->u.index], 0, 0, 0);
            }
        }
        break;
    case 4:
        if (fn_800A8518(3)) {
            currentDrawingItem->state++;
        }
        break;
    case 5:
        if (fn_800A88C8() == 0) {
            fn_800A8B78(lbl_1_bss_4);
            currentDrawingItem->state++;
        }
        break;
    case 6:
        scene->prev->state = 1;
        removeCurrentDrawingItem();
        break;
    }
}

// .text:0x000001B0 size:0x30
void fn_1_1B0(u32 *table, s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        if (table[i] != 0) {
            table[i] += (u32)table;
        }
    }
}

// .text:0x000000E8 size:0xC8
void fn_1_E8(RepPackedFile *file) {
    loadPackedFile(file);
}

// .text:0x00000020 size:0xC8
void fn_1_20(RepPackedFile *file) {
    loadPackedFile(file);
}

// .text:0x00000000 size:0x20
void fn_1_0(ANIMBank *bank) {
    ANIMGet(bank);
}
