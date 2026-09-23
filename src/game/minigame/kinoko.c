#include "game/minigame/kinoko.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "Dolphin/mtx.h"
#include "Dolphin/vec.h"
#include "Dolphin/gx.h"
#include "Dolphin/os.h"
#include "Dolphin/stl.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x800247e4.h"
#include "Unknown/File_0x8001b728.h"
#include "Unknown/File_0x8005268c.h"
#include "Unknown/File_0x80052734.h"
#include "Unknown/File_0x800b0a14.h"

// The ribbon effect: six ribbons trail from a character's bones (both hands,
// torso, head and both feet), each a history of 25 points that fades out.

#define RIBBON_COUNT 6
#define RIBBON_POINTS 25
#define RIBBON_QUADS 149
#define RIBBON_COLORS 6

typedef struct _RibbonPoint {
    /*0x00*/ Vec pos;
    /*0x0C*/ Vec edgeA;
    /*0x18*/ Vec edgeB;
    /*0x24*/ u8 color[4];
    /*0x28*/ u8 colorFrom;
    /*0x29*/ u8 colorTo;
    /*0x2A*/ u8 active;
    /*0x2B*/ u8 _2B;
} RibbonPoint; // size: 0x2C

typedef struct _Ribbon {
    /*0x000*/ RibbonPoint points[RIBBON_POINTS];
} Ribbon; // size: 0x44C

typedef struct _RibbonState {
    /*0x0000*/ Ribbon ribbons[RIBBON_COUNT];
    /*0x19C8*/ u8 _19C8[0x19D4 - 0x19C8];
    /*0x19D4*/ s32 frame;
    /*0x19D8*/ u8 _19D8[4];
    /*0x19DC*/ s8 charID;
    /*0x19DD*/ u8 enabled;
    /*0x19DE*/ u8 _19DE[2];
} RibbonState; // size: 0x19E0

// One screen-sorted quad joining two consecutive points of a ribbon.
typedef struct _RibbonQuad {
    /*0x00*/ Vec* pos0;
    /*0x04*/ u8* color0;
    /*0x08*/ Vec* pos1;
    /*0x0C*/ u8* color1;
    /*0x10*/ Vec* pos2;
    /*0x14*/ u8* color2;
    /*0x18*/ Vec* pos3;
    /*0x1C*/ u8* color3;
    /*0x20*/ Vec center;
    /*0x2C*/ u8 active;
} RibbonQuad; // size: 0x30

typedef struct _RibbonDepth {
    /*0x00*/ f32 z;
    /*0x04*/ u32 index;
} RibbonDepth;

// Bone ids for getAnimationCollisionOffset.
typedef enum _RIBBON_BONE {
    RIBBON_BONE_TORSO = 4,
    RIBBON_BONE_HEAD_ALT = 5,
    RIBBON_BONE_HEAD = 7,
    RIBBON_BONE_FOOT_L = 0x12,
    RIBBON_BONE_FOOT_L_ALT = 0x13,
    RIBBON_BONE_FOOT_R = 0x18,
    RIBBON_BONE_FOOT_R_ALT = 0x19,
    RIBBON_BONE_HAND_L = 0x1C,
    RIBBON_BONE_HAND_L_ALT = 0x1E,
    RIBBON_BONE_HAND_R = 0x20,
    RIBBON_BONE_HAND_R_ALT = 0x22,
} RIBBON_BONE;

extern u8 lbl_80366158[0x30];
extern u8 drawStadiumRelated;
extern void fn_80011604(void* model, void (*cb)(void*, GXTevStageID*, GXTexCoordID*, GXTexMapID*, s8*, s8*));
extern void fn_800A7D4C(s32 arg0, void* arg1);

#define PauseSimulation lbl_80366158[0x28]
#define RIBBON_STATE ribbonState

typedef struct _RibbonDrawEntry {
    /*0x00*/ u32 _00;
    /*0x04*/ void (*draw)(void);
} RibbonDrawEntry;

static RibbonState ribbonState = {0};
static u8 ribbonColors[RIBBON_COLORS][4] = {
    {0xFF, 0x00, 0x00, 0xC8}, {0xFF, 0xFF, 0x00, 0xC8}, {0x00, 0xFF, 0x00, 0xC8},
    {0x00, 0xFF, 0xFF, 0xC8}, {0x00, 0x00, 0xFF, 0xC8}, {0xFF, 0x00, 0xFF, 0xC8},
};
static RibbonDrawEntry ribbonDraw[2] = {
    {0, fn_3_169984},
    {0, fn_3_169984},
};
static s8 pulseStep = -1;

static RibbonQuad ribbonQuads[RIBBON_QUADS];
static u8 texA[4 * 4 * 4] ATTRIBUTE_ALIGN(32);
static u8 texB[4 * 4 * 4] ATTRIBUTE_ALIGN(32);
static GXTexObj texObjA;
static GXTexObj texObjB;
static u32 pulseFrame;
static GXTexObj* curTexObj;
static u8* curTex;

// .text:0x0016917C size:0x2C0 mapped:0x807A8210
void fn_3_16917C(void* model, GXTevStageID* stage, GXTexCoordID* coord, GXTexMapID* map, s8* nStages, s8* nCoords) {
    fn_3_16943C();
    GXLoadTexObj(curTexObj, *map);
    GXSetTexCoordGen2(*coord, GX_TG_MTX2X4, GX_TG_TEX0, GX_IDENTITY, GX_DISABLE, GX_PTIDENTITY);
    GXSetTevOrder(*stage, *coord, *map, GX_COLOR_NULL);
    if (curTex == texA) {
        GXSetTevColorIn(*stage, GX_CC_CPREV, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
        GXSetTevColorOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE, GX_TEVPREV);
        GXSetTevAlphaIn(*stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
        GXSetTevAlphaOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE, GX_TEVPREV);
    } else {
        GXSetTevColorIn(*stage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_TEXA, GX_CC_CPREV);
        GXSetTevColorOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE, GX_TEVPREV);
        GXSetTevAlphaIn(*stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
        GXSetTevAlphaOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE, GX_TEVPREV);
    }
    (*stage)++;
    (*coord)++;
    (*map)++;
    (*nStages)++;
    (*nCoords)++;
}

// .text:0x0016943C size:0x164 mapped:0x807A84D0
void fn_3_16943C(void) {
    int value;
    int i;

    pulseFrame += !PauseSimulation;
    if ((pulseFrame & 1) == 0) {
        value = curTex[fn_800247E4(0, 0, 4, 4)] + pulseStep * 2;
        if (value > 255) {
            value = 255;
        } else if (value < 0) {
            value = 0;
        }
        for (i = 0; i < 32; i += 2) {
            curTex[i] = value;
        }
        DCFlushRange(curTex, 4);
        value += pulseStep * 2;
        if (value > 255 || value < 0) {
            pulseStep = -pulseStep;
        }
    }
}

// .text:0x001695A0 size:0x4 mapped:0x807A8634
void fn_3_1695A0(void) {
    return;
}

// .text:0x001695A4 size:0x5C mapped:0x807A8638
void fn_3_1695A4(void* model, u8 alt) {
    if (!alt) {
        curTex = texA;
        curTexObj = &texObjA;
    } else {
        curTex = texB;
        curTexObj = &texObjB;
    }
    fn_80011604(model, fn_3_16917C);
}

// .text:0x00169600 size:0x204 mapped:0x807A8694
void fn_3_169600(void) {
    u32 offset;
    u32 x;
    u32 y;

    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            offset = fn_800247E4(x, y, 4, 4);
            if (offset < 32) {
                texA[offset + 2] = 0xFF;
                texA[offset] = 0xFF;
                texA[offset + 3] = 0x9B;
                texA[offset + 1] = 0x9B;
            } else {
                texA[offset + 2] = 0;
                texA[offset] = 0;
                texA[offset + 3] = 0xFF;
                texA[offset + 1] = 0xFF;
            }
        }
    }
    for (y = 0; y < 4; y++) {
        for (x = 0; x < 4; x++) {
            offset = fn_800247E4(x, y, 4, 4);
            if (offset < 32) {
                texB[offset + 2] = 0xFF;
                texB[offset] = 0xFF;
                texB[offset + 3] = 0;
                texB[offset + 1] = 0;
            } else {
                texB[offset + 2] = 0x9B;
                texB[offset] = 0x9B;
                texB[offset + 3] = 0xFF;
                texB[offset + 1] = 0xFF;
            }
        }
    }
    GXInitTexObj(&texObjA, texA, 4, 4, GX_TF_RGBA8, GX_REPEAT, GX_REPEAT, GX_DISABLE);
    GXInitTexObjLOD(&texObjA, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_DISABLE, GX_DISABLE, GX_ANISO_1);
    GXInitTexObj(&texObjB, texB, 4, 4, GX_TF_RGBA8, GX_REPEAT, GX_REPEAT, GX_DISABLE);
    GXInitTexObjLOD(&texObjB, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_DISABLE, GX_DISABLE, GX_ANISO_1);
    pulseFrame = 0;
    pulseStep = -1;
}

// .text:0x00169804 size:0x180 mapped:0x807A8898
void fn_3_169804(void) {
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
    GXSetCullMode(GX_CULL_BACK);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGBA, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_DISABLE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_DISABLE, GX_TEVPREV);
    GXLoadPosMtxImm(fn_80052768_getCamera(returnsCurrentMode())->view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetProjection(fn_80052768_getCamera(returnsCurrentMode())->proj, GX_PERSPECTIVE);
}

// .text:0x00169984 size:0x37C mapped:0x807A8A18
void fn_3_169984(void) {
    RibbonDepth tmp;
    Mtx view;
    Vec center;
    RibbonDepth order[RIBBON_QUADS];
    RibbonDepth* front = order;
    RibbonDepth* back = &order[RIBBON_QUADS - 1];
    RibbonDepth* a;
    RibbonDepth* b;
    RibbonQuad* q;
    u32 i;
    u32 j;

    PSMTXCopy(fn_80052768_getCamera(returnsCurrentMode())->view, view);
    q = ribbonQuads;
    for (i = 0; i < RIBBON_QUADS; i++, q++) {
        if (!q->active) {
            back->z = -1.0f;
            back->index = i;
            back--;
        } else {
            PSMTXMultVec(view, &q->center, &center);
            front->z = center.z;
            front->index = i;
            front++;
        }
    }
    for (i = 0, a = order; i < RIBBON_QUADS - 1; i++, a++) {
        for (j = i + 1, b = &order[j]; j < RIBBON_QUADS; j++, b++) {
            if (a->z > b->z) {
                memcpy(&tmp, a, sizeof(RibbonDepth));
                memcpy(a, b, sizeof(RibbonDepth));
                memcpy(b, &tmp, sizeof(RibbonDepth));
            }
        }
    }
    fn_3_169804();
    for (i = 0, a = order; i < RIBBON_QUADS; i++, a++) {
        q = &ribbonQuads[a->index];
        if (q->active) {
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(q->pos0->x, q->pos0->y, q->pos0->z);
            GXColor1u32(*(u32*)q->color0);
            GXPosition3f32(q->pos1->x, q->pos1->y, q->pos1->z);
            GXColor1u32(*(u32*)q->color1);
            GXPosition3f32(q->pos2->x, q->pos2->y, q->pos2->z);
            GXColor1u32(*(u32*)q->color2);
            GXPosition3f32(q->pos3->x, q->pos3->y, q->pos3->z);
            GXColor1u32(*(u32*)q->color3);
        }
    }
}

// .text:0x00169D00 size:0x170 mapped:0x807A8D94
void fn_3_169D00(Ribbon* ribbon, u32* count) {
    RibbonPoint* cur = &ribbon->points[RIBBON_POINTS - 1];
    RibbonPoint* prev;
    u32 i;

    for (i = RIBBON_POINTS - 1; i != 0 && *count < RIBBON_QUADS; cur--, i--) {
        if (cur->active) {
            prev = &ribbon->points[i - 1];
            PSVECAdd(&cur->pos, &prev->pos, &ribbonQuads[*count].center);
            PSVECScale(&ribbonQuads[*count].center, 0.5f, &ribbonQuads[*count].center);
            ribbonQuads[*count].pos0 = &prev->edgeA;
            ribbonQuads[*count].color0 = prev->color;
            ribbonQuads[*count].pos1 = &prev->edgeB;
            ribbonQuads[*count].color1 = prev->color;
            ribbonQuads[*count].pos2 = &cur->edgeB;
            ribbonQuads[*count].color2 = cur->color;
            ribbonQuads[*count].pos3 = &cur->edgeA;
            ribbonQuads[*count].color3 = cur->color;
            ribbonQuads[*count].active = 1;
            (*count)++;
        }
    }
}

// .text:0x00169E70 size:0x20C mapped:0x807A8F04
void fn_3_169E70(RibbonPoint* points) {
    camera_803c639c_s* cam = fn_80052768_getCamera(0);
    RibbonPoint* p = points;
    Vec forward;
    Vec along;
    Vec side;
    Vec prevPos;
    Vec nextPos;
    u32 i;

    for (i = 0; i < RIBBON_POINTS; i++, p++) {
        if (p->active) {
            forward.x = cam->view[2][0];
            forward.y = cam->view[2][1];
            forward.z = cam->view[2][2];
            if (PSVECMag(&forward) == 0.0f) {
                forward.x = 0.0f;
                forward.y = 0.0f;
                forward.z = 1.0f;
            } else {
                PSVECNormalize(&forward, &forward);
            }
            if (i == 0) {
                memcpy(&prevPos, p, sizeof(Vec));
            } else {
                memcpy(&prevPos, &points[i - 1], sizeof(Vec));
            }
            if (i == RIBBON_POINTS - 1) {
                memcpy(&nextPos, p, sizeof(Vec));
            } else {
                memcpy(&nextPos, &points[i + 1], sizeof(Vec));
            }
            PSVECSubtract(&prevPos, &nextPos, &along);
            if (PSVECMag(&along) == 0.0f) {
                along.z = 0.0f;
                along.y = 0.0f;
                along.x = 1.0f;
            }
            PSVECNormalize(&along, &along);
            PSVECCrossProduct(&along, &forward, &side);
            if (PSVECMag(&side) == 0.0f) {
                side.z = 0.0f;
                side.y = 0.0f;
                side.x = -1.0f;
            }
            PSVECNormalize(&side, &side);
            PSVECScale(&side, -0.15f, &p->edgeA);
            PSVECScale(&side, 0.15f, &p->edgeB);
            PSVECAdd(&p->edgeA, &p->pos, &p->edgeA);
            PSVECAdd(&p->edgeB, &p->pos, &p->edgeB);
        }
    }
}

// .text:0x0016A07C size:0x140C mapped:0x807A9110
void fn_3_16A07C(void) {
    u32 count;
    int i;
    u8 alpha;

    if (g_d_GameSettings._55 != 0 || g_Minigame._1A40 != 0) {
        removeCurrentDrawingItem();
        memset(&RIBBON_STATE, 0, sizeof(RibbonState));
        return;
    }
    if ((s8)g_Minigame.playerIDWithPowerup[0] == -1 || !RIBBON_STATE.enabled) {
        removeCurrentDrawingItem();
        memset(&RIBBON_STATE, 0, sizeof(RibbonState));
        return;
    }
    if (!PauseSimulation) {
        RIBBON_STATE.frame++;
        for (i = RIBBON_POINTS - 1; i != 0; i--) {
            alpha = (24 - i) * 8;
            memcpy(&RIBBON_STATE.ribbons[0].points[i], &RIBBON_STATE.ribbons[0].points[i - 1], sizeof(RibbonPoint));
            RIBBON_STATE.ribbons[0].points[i].color[3] = alpha;
            memcpy(&RIBBON_STATE.ribbons[1].points[i], &RIBBON_STATE.ribbons[1].points[i - 1], sizeof(RibbonPoint));
            RIBBON_STATE.ribbons[1].points[i].color[3] = alpha;
            memcpy(&RIBBON_STATE.ribbons[2].points[i], &RIBBON_STATE.ribbons[2].points[i - 1], sizeof(RibbonPoint));
            RIBBON_STATE.ribbons[2].points[i].color[3] = alpha;
            memcpy(&RIBBON_STATE.ribbons[3].points[i], &RIBBON_STATE.ribbons[3].points[i - 1], sizeof(RibbonPoint));
            RIBBON_STATE.ribbons[3].points[i].color[3] = alpha;
            memcpy(&RIBBON_STATE.ribbons[4].points[i], &RIBBON_STATE.ribbons[4].points[i - 1], sizeof(RibbonPoint));
            RIBBON_STATE.ribbons[4].points[i].color[3] = alpha;
            memcpy(&RIBBON_STATE.ribbons[5].points[i], &RIBBON_STATE.ribbons[5].points[i - 1], sizeof(RibbonPoint));
            RIBBON_STATE.ribbons[5].points[i].color[3] = alpha;
        }
        if (RIBBON_STATE.frame % 5 == 0) {
            RIBBON_STATE.ribbons[0].points[0].colorFrom++;
            if (RIBBON_STATE.ribbons[0].points[0].colorFrom >= RIBBON_COLORS) {
                RIBBON_STATE.ribbons[0].points[0].colorFrom -= RIBBON_COLORS;
            }
            RIBBON_STATE.ribbons[0].points[0].colorTo++;
            if (RIBBON_STATE.ribbons[0].points[0].colorTo >= RIBBON_COLORS) {
                RIBBON_STATE.ribbons[0].points[0].colorTo -= RIBBON_COLORS;
            }
            RIBBON_STATE.ribbons[1].points[0].colorFrom++;
            if (RIBBON_STATE.ribbons[1].points[0].colorFrom >= RIBBON_COLORS) {
                RIBBON_STATE.ribbons[1].points[0].colorFrom -= RIBBON_COLORS;
            }
            RIBBON_STATE.ribbons[1].points[0].colorTo++;
            if (RIBBON_STATE.ribbons[1].points[0].colorTo >= RIBBON_COLORS) {
                RIBBON_STATE.ribbons[1].points[0].colorTo -= RIBBON_COLORS;
            }
            RIBBON_STATE.ribbons[2].points[0].colorFrom++;
            if (RIBBON_STATE.ribbons[2].points[0].colorFrom >= RIBBON_COLORS) {
                RIBBON_STATE.ribbons[2].points[0].colorFrom -= RIBBON_COLORS;
            }
            RIBBON_STATE.ribbons[2].points[0].colorTo++;
            if (RIBBON_STATE.ribbons[2].points[0].colorTo >= RIBBON_COLORS) {
                RIBBON_STATE.ribbons[2].points[0].colorTo -= RIBBON_COLORS;
            }
            RIBBON_STATE.ribbons[3].points[0].colorFrom++;
            if (RIBBON_STATE.ribbons[3].points[0].colorFrom >= RIBBON_COLORS) {
                RIBBON_STATE.ribbons[3].points[0].colorFrom -= RIBBON_COLORS;
            }
            RIBBON_STATE.ribbons[3].points[0].colorTo++;
            if (RIBBON_STATE.ribbons[3].points[0].colorTo >= RIBBON_COLORS) {
                RIBBON_STATE.ribbons[3].points[0].colorTo -= RIBBON_COLORS;
            }
            RIBBON_STATE.ribbons[4].points[0].colorFrom++;
            if (RIBBON_STATE.ribbons[4].points[0].colorFrom >= RIBBON_COLORS) {
                RIBBON_STATE.ribbons[4].points[0].colorFrom -= RIBBON_COLORS;
            }
            RIBBON_STATE.ribbons[4].points[0].colorTo++;
            if (RIBBON_STATE.ribbons[4].points[0].colorTo >= RIBBON_COLORS) {
                RIBBON_STATE.ribbons[4].points[0].colorTo -= RIBBON_COLORS;
            }
            RIBBON_STATE.ribbons[5].points[0].colorFrom++;
            if (RIBBON_STATE.ribbons[5].points[0].colorFrom >= RIBBON_COLORS) {
                RIBBON_STATE.ribbons[5].points[0].colorFrom -= RIBBON_COLORS;
            }
            RIBBON_STATE.ribbons[5].points[0].colorTo++;
            if (RIBBON_STATE.ribbons[5].points[0].colorTo >= RIBBON_COLORS) {
                RIBBON_STATE.ribbons[5].points[0].colorTo -= RIBBON_COLORS;
            }
        }
        fn_3_16B5B4(&RIBBON_STATE.ribbons[0].points[0], RIBBON_BONE_HAND_L, RIBBON_STATE.frame % 5);
        fn_3_16B5B4(&RIBBON_STATE.ribbons[1].points[0], RIBBON_BONE_HAND_R, RIBBON_STATE.frame % 5);
        fn_3_16B5B4(&RIBBON_STATE.ribbons[2].points[0], RIBBON_BONE_TORSO, RIBBON_STATE.frame % 5);
        fn_3_16B5B4(&RIBBON_STATE.ribbons[3].points[0], RIBBON_BONE_HEAD, RIBBON_STATE.frame % 5);
        fn_3_16B5B4(&RIBBON_STATE.ribbons[4].points[0], RIBBON_BONE_FOOT_L, RIBBON_STATE.frame % 5);
        fn_3_16B5B4(&RIBBON_STATE.ribbons[5].points[0], RIBBON_BONE_FOOT_R, RIBBON_STATE.frame % 5);
    }
    fn_3_169E70(RIBBON_STATE.ribbons[0].points);
    fn_3_169E70(RIBBON_STATE.ribbons[1].points);
    fn_3_169E70(RIBBON_STATE.ribbons[2].points);
    fn_3_169E70(RIBBON_STATE.ribbons[3].points);
    fn_3_169E70(RIBBON_STATE.ribbons[4].points);
    fn_3_169E70(RIBBON_STATE.ribbons[5].points);
    count = 0;
    memset(ribbonQuads, 0, sizeof(ribbonQuads));
    fn_3_169D00(&RIBBON_STATE.ribbons[0], &count);
    fn_3_169D00(&RIBBON_STATE.ribbons[1], &count);
    fn_3_169D00(&RIBBON_STATE.ribbons[2], &count);
    fn_3_169D00(&RIBBON_STATE.ribbons[3], &count);
    fn_3_169D00(&RIBBON_STATE.ribbons[4], &count);
    fn_3_169D00(&RIBBON_STATE.ribbons[5], &count);
    fn_800A7D4C(1, &ribbonDraw[drawStadiumRelated]);
}

// .text:0x0016B488 size:0x12C mapped:0x807AA51C
void fn_3_16B488(Vec* pos, s8 bone) {
    if (pos == NULL) {
        OSPanic("kinoko.c", 0x11C, "Ribbon Effect Pos Data None\n");
    }
    memset(pos, 0, sizeof(Vec));
    if (!getAnimationCollisionOffset(RIBBON_STATE.charID, bone, pos)) {
        switch (bone) {
        case RIBBON_BONE_HAND_L:
            getAnimationCollisionOffset(RIBBON_STATE.charID, RIBBON_BONE_HAND_L_ALT, pos);
            break;
        case RIBBON_BONE_HAND_R:
            getAnimationCollisionOffset(RIBBON_STATE.charID, RIBBON_BONE_HAND_R_ALT, pos);
            break;
        case RIBBON_BONE_HEAD:
            getAnimationCollisionOffset(RIBBON_STATE.charID, RIBBON_BONE_HEAD_ALT, pos);
            break;
        case RIBBON_BONE_FOOT_L:
            getAnimationCollisionOffset(RIBBON_STATE.charID, RIBBON_BONE_FOOT_L_ALT, pos);
            break;
        case RIBBON_BONE_FOOT_R:
            getAnimationCollisionOffset(RIBBON_STATE.charID, RIBBON_BONE_FOOT_R_ALT, pos);
            break;
        }
    }
}

// .text:0x0016B5B4 size:0x2D0 mapped:0x807AA648
void fn_3_16B5B4(RibbonPoint* p, s8 bone, int frame) {
    f32 t = (f32)frame / 5.0f;

    p->color[0] = (1.0 - t) * ribbonColors[p->colorFrom][0] + t * ribbonColors[p->colorTo][0];
    p->color[1] = (1.0 - t) * ribbonColors[p->colorFrom][1] + t * ribbonColors[p->colorTo][1];
    p->color[2] = (1.0 - t) * ribbonColors[p->colorFrom][2] + t * ribbonColors[p->colorTo][2];
    p->color[3] = (1.0 - t) * ribbonColors[p->colorFrom][3] + t * ribbonColors[p->colorTo][3];
    p->active = 1;
    fn_3_16B488(&p->pos, bone);
}

// .text:0x0016B884 size:0xB10 mapped:0x807AA918
void fn_3_16B884(void) {
    RibbonPoint* p;
    u32 i;
    u8 alpha;
    u8 c;

    c = 0;
    RIBBON_STATE.ribbons[0].points[0].colorFrom = c++;
    RIBBON_STATE.ribbons[0].points[0].colorTo = c;
    fn_3_16B5B4(&RIBBON_STATE.ribbons[0].points[0], RIBBON_BONE_HAND_L, 0);
    RIBBON_STATE.ribbons[1].points[0].colorFrom = c++;
    RIBBON_STATE.ribbons[1].points[0].colorTo = c;
    fn_3_16B5B4(&RIBBON_STATE.ribbons[1].points[0], RIBBON_BONE_HAND_R, 0);
    RIBBON_STATE.ribbons[2].points[0].colorFrom = c++;
    RIBBON_STATE.ribbons[2].points[0].colorTo = c;
    fn_3_16B5B4(&RIBBON_STATE.ribbons[2].points[0], RIBBON_BONE_TORSO, 0);
    RIBBON_STATE.ribbons[3].points[0].colorFrom = c++;
    RIBBON_STATE.ribbons[3].points[0].colorTo = c;
    fn_3_16B5B4(&RIBBON_STATE.ribbons[3].points[0], RIBBON_BONE_HEAD, 0);
    RIBBON_STATE.ribbons[4].points[0].colorFrom = c++;
    RIBBON_STATE.ribbons[4].points[0].colorTo = c;
    fn_3_16B5B4(&RIBBON_STATE.ribbons[4].points[0], RIBBON_BONE_FOOT_L, 0);
    RIBBON_STATE.ribbons[5].points[0].colorFrom = c++;
    RIBBON_STATE.ribbons[5].points[0].colorTo = 0;
    fn_3_16B5B4(&RIBBON_STATE.ribbons[5].points[0], RIBBON_BONE_FOOT_R, 0);
    for (i = 1, p = RIBBON_STATE.ribbons[0].points; i < RIBBON_POINTS; i++, p++) {
        alpha = (24 - i) * 8;
        memcpy(&p[1], &RIBBON_STATE.ribbons[0].points[i - 1], sizeof(RibbonPoint));
        p[1].color[3] = alpha;
        memcpy(&p[1 * RIBBON_POINTS + 1], &RIBBON_STATE.ribbons[1].points[i - 1], sizeof(RibbonPoint));
        p[1 * RIBBON_POINTS + 1].color[3] = alpha;
        memcpy(&p[2 * RIBBON_POINTS + 1], &RIBBON_STATE.ribbons[2].points[i - 1], sizeof(RibbonPoint));
        p[2 * RIBBON_POINTS + 1].color[3] = alpha;
        memcpy(&p[3 * RIBBON_POINTS + 1], &RIBBON_STATE.ribbons[3].points[i - 1], sizeof(RibbonPoint));
        p[3 * RIBBON_POINTS + 1].color[3] = alpha;
        memcpy(&p[4 * RIBBON_POINTS + 1], &RIBBON_STATE.ribbons[4].points[i - 1], sizeof(RibbonPoint));
        p[4 * RIBBON_POINTS + 1].color[3] = alpha;
        memcpy(&p[5 * RIBBON_POINTS + 1], &RIBBON_STATE.ribbons[5].points[i - 1], sizeof(RibbonPoint));
        p[5 * RIBBON_POINTS + 1].color[3] = alpha;
    }
}

// .text:0x0016C394 size:0x7C mapped:0x807AB428
void fn_3_16C394(s8 charID) {
    memset(&RIBBON_STATE, 0, sizeof(RibbonState));
    memset(ribbonQuads, 0, sizeof(ribbonQuads));
    RIBBON_STATE.charID = charID;
    RIBBON_STATE.enabled = 1;
    RIBBON_STATE.frame = 1;
    fn_3_16B884();
    insertGraphicDrawingFunction(fn_3_16A07C, 0);
}
