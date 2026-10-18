#define REP_HEADER_DATA_FN getRepHeaderData_minigameWinnerSpotlight
#include "game/minigame/minigame_winner_spotlight.h"
#include "mssbTypes.h"
#include "header_rep_data.h"
#include "Dolphin/vec.h"
#include "Dolphin/mtx.h"
#include "Dolphin/gx.h"
#include "Dolphin/GX/GXFifo.h"
#include "Unknown/sub.h"
#include "Unknown/File_0x8005268c.h"
#include "Unknown/File_0x80052734.h"
#include "Unknown/File_0x80052694.h"
#include "Unknown/File_0x800b0a14.h"
#include "static/UnknownHomes_Static.h"
#include <stdarg.h>
#include <string.h>

// The minigame results spotlight: the screen dims to dimAlpha over fadeFrames,
// then up to four light beams come down on the winners' actors (sized by
// character) with a ground disc at their feet. minigame_fielder_anim starts it
// (minigameWinnerSpotlight_start, then _show next to minigameWinnerStars_spawn),
// scene_effects queues the draw each frame while it is active, and the
// minigame framework and Toy Field stop it next to minigameWinnerStars_stop.

// One light beam: a quad from a narrow top edge above the winner down to a
// wider edge at their feet, plus a textured ground disc there.
typedef struct {
    Vec top;
    Vec base;
    f32 topHalfWidth;
    f32 baseRadius;
    u32 topColor;
    u32 baseColor;
    s32 enabled;
} SpotlightBeam;

typedef struct SpotlightOverlay {
    u32 _00;
    void (*draw)(void*);
    SpotlightBeam beams[4];
    void* groundTexture;
    u32 dimColor;
    s32 beamCount;
} SpotlightOverlay;

typedef struct {
    s32 x;
    s32 y;
    u32 topColor;
    u32 baseColor;
} SpotlightBeamOffset;

typedef struct {
    s32 dimAlpha;
    s32 fadeFrames;
    SpotlightBeamOffset coords[6]; // [0] one beam, [1..2] two beams, [3..5] three or more
    s32 beamHeight;
} SpotlightSettings;

extern u8 lbl_3_common_bss_35154[];

typedef struct {
    u8 _000[0x468];
    u32 dimColor;
    u8 _46C[4];
    u8 active;
    u8 showBeams;
    u8 slotCount;
    u8 slots[6];
    u8 paused;
    u8 _47A[6];
} SpotlightState;

#define sState (*(SpotlightState*)lbl_3_common_bss_35154)
extern u8 hugeAnimStruct[];
extern u8 drawStadiumRelated;
extern void fn_800A7D4C(s32, void*);

// This unit's .data (0x27EC0-0x281F0). MWCC pools file-static data and
// addresses each object as base+offset from a single register, so these must
// stay statics defined in this order.
static s32 sBeamSizes[3][2] = {
    {15000, 90000},
    {20000, 129999},
    {30000, 180000},
};
// Beam size class (row of sBeamSizes) per CHAR_ID.
static u8 sBeamSizeClass[0x38] = {
    1, 1, 2, 1, 1, 1, 1, 0, 0, 2, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 2, 2, 2, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
};
static SpotlightSettings sSettings = {
    0x40,
    0x10,
    {
        {0, 0, 0xFFFF0080, 0xFFFFC818},
        {-200000, 0, 0xFFFF0080, 0xFFFFC818},
        {200000, 0, 0xFFFF0080, 0xFFFFC818},
        {0, 0, 0xFFFF0080, 0xFFFFC818},
        {-300000, 0, 0xFFFF0080, 0xFFFFC818},
        {300000, 0, 0xFFFF0080, 0xFFFFC818},
    },
    900000,
};
static SpotlightOverlay sOverlays[2] = {
    {0, minigameWinnerSpotlight_draw},
    {0, minigameWinnerSpotlight_draw},
};
static Mtx44 sScreenProjection = {
    {0.003125f, 0.0f, 0.0f, -1.0f},
    {0.0f, -0.004464286f, 0.0f, 1.0f},
    {0.0f, 0.0f, -5.9604645e-08f, -1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
};
static u8 sScreenQuadDL[0x20] ATTRIBUTE_ALIGN(32) = {
    0x80, 0x00, 0x04, 0x00, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0x03, 0xFF, 0xFF, 0x00,
};
static Vec sScreenQuadFar[4] ATTRIBUTE_ALIGN(32) = {
    {0.0f, 0.0f, -16777215.0f},
    {0.0f, 448.0f, -16777215.0f},
    {640.0f, 448.0f, -16777215.0f},
    {640.0f, 0.0f, -16777215.0f},
};
static Vec sScreenQuadNear[4] ATTRIBUTE_ALIGN(32) = {
    {0.0f, 0.0f, -1.0f},
    {0.0f, 448.0f, -1.0f},
    {640.0f, 448.0f, -1.0f},
    {640.0f, 0.0f, -1.0f},
};

#define GX_FIFO_F32 (*(volatile f32*)0xCC008000)
#define GX_FIFO_U32 (*(volatile u32*)0xCC008000)
#define GX_FIFO_U16 (*(volatile u16*)0xCC008000)

static const f32 lbl_3_rodata_3D30 = 100000.0f;
static const f64 lbl_3_rodata_3D38 = 4503601774854144.0;
static const f32 lbl_3_rodata_3D40 = 0.0f;
static const f32 lbl_3_rodata_3D44 = -16777215.0f;
static const f32 lbl_3_rodata_3D48 = 640.0f;
static const f32 lbl_3_rodata_3D4C = 448.0f;

// .text:0x0015FF28 size:0x650 mapped:0x8079EFBC
void minigameWinnerSpotlight_draw(void* arg) {
    SpotlightOverlay* overlay = (SpotlightOverlay*)arg;
    Mtx identity;
    Vec transformed;
    Vec direction;
    camera_803c639c_s* camera;
    int i;
    int mode;

    GXSetCullMode(GX_CULL_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    PSMTXIdentity(identity);
    GXSetZCompLoc(FALSE);
    minigameWinnerSpotlight_clearDepth(FALSE);

    mode = returnsCurrentMode();
    camera = returnFloatFromModeIndex(mode);
    setScissorAndProjection(mode);
    gOz_GXSetTexture(GX_MODULATE, 0, FALSE);

    if (sState.slotCount != 0 && sState.showBeams) {
        GXSetZMode(TRUE, GX_ALWAYS, TRUE);
        GXLoadPosMtxImm(identity, GX_PNMTX0);
        SetDisplayStateTexture(NULL, 0, 0);
        for (i = 0; i < overlay->beamCount; i++) {
            if (overlay->beams[i].enabled) {
                PSMTXMultVec(camera->view, &overlay->beams[i].top, &transformed);
                GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                {
                    f32 x = transformed.x;
                    GX_FIFO_F32 = x - overlay->beams[i].topHalfWidth;
                    GX_FIFO_F32 = transformed.y;
                    GX_FIFO_F32 = transformed.z;
                    GX_FIFO_U32 = overlay->beams[i].topColor;
                    GX_FIFO_U16 = 0;
                    GX_FIFO_U16 = 0;
                    GX_FIFO_F32 = x + overlay->beams[i].topHalfWidth;
                    GX_FIFO_F32 = transformed.y;
                    GX_FIFO_F32 = transformed.z;
                    GX_FIFO_U32 = overlay->beams[i].topColor;
                    GX_FIFO_U16 = 1;
                    GX_FIFO_U16 = 0;
                }
                PSMTXMultVec(camera->view, &overlay->beams[i].base, &transformed);
                direction.x = transformed.x;
                direction.y = lbl_3_rodata_3D40;
                direction.z = transformed.z;
                if (PSVECMag(&direction)) {
                    PSVECNormalize(&direction, &direction);
                    PSVECScale(&direction, overlay->beams[i].baseRadius, &direction);
                } else {
                    direction.x = overlay->beams[i].baseRadius;
                    direction.z = lbl_3_rodata_3D40;
                }
                {
                    f32 x = transformed.x;
                    f32 dx;
                    GX_FIFO_F32 = x - direction.z;
                    GX_FIFO_F32 = transformed.y;
                    GX_FIFO_F32 = transformed.z + (dx = direction.x);
                    GX_FIFO_U32 = overlay->beams[i].baseColor;
                    GX_FIFO_U16 = 1;
                    GX_FIFO_U16 = 1;
                    GX_FIFO_F32 = x + direction.z;
                    GX_FIFO_F32 = transformed.y;
                    GX_FIFO_F32 = transformed.z - dx;
                    GX_FIFO_U32 = overlay->beams[i].baseColor;
                    GX_FIFO_U16 = 0;
                    GX_FIFO_U16 = 1;
                }
            }
        }
        GXSetZMode(TRUE, GX_LEQUAL, TRUE);
        GXLoadPosMtxImm(camera->view, GX_PNMTX0);
        SetDisplayStateTexture((TextureBody*)overlay->groundTexture, 0, 0);
        for (i = 0; i < overlay->beamCount; i++) {
            if ((&overlay->beams[i])->enabled) {
                GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                {
                    f32 y = (&overlay->beams[i])->base.y;
                    f32 baseRadius = (&overlay->beams[i])->baseRadius;
                    f32 x = (&overlay->beams[i])->base.x - baseRadius;
                    f32 z = (&overlay->beams[i])->base.z - baseRadius;
                    GX_FIFO_F32 = x;
                    GX_FIFO_F32 = y;
                    GX_FIFO_F32 = z;
                    GX_FIFO_U32 = (&overlay->beams[i])->baseColor;
                    GX_FIFO_U16 = 0;
                    GX_FIFO_U16 = 0;
                }
                {
                    f32 y = (&overlay->beams[i])->base.y;
                    f32 baseRadius = (&overlay->beams[i])->baseRadius;
                    f32 x = (&overlay->beams[i])->base.x + baseRadius;
                    f32 z = (&overlay->beams[i])->base.z - baseRadius;
                    GX_FIFO_F32 = x;
                    GX_FIFO_F32 = y;
                    GX_FIFO_F32 = z;
                    GX_FIFO_U32 = (&overlay->beams[i])->baseColor;
                    GX_FIFO_U16 = 1;
                    GX_FIFO_U16 = 0;
                }
                {
                    f32 y = (&overlay->beams[i])->base.y;
                    f32 baseRadius = (&overlay->beams[i])->baseRadius;
                    f32 x = (&overlay->beams[i])->base.x + baseRadius;
                    f32 z = (&overlay->beams[i])->base.z + baseRadius;
                    GX_FIFO_F32 = x;
                    GX_FIFO_F32 = y;
                    GX_FIFO_F32 = z;
                    GX_FIFO_U32 = (&overlay->beams[i])->baseColor;
                    GX_FIFO_U16 = 1;
                    GX_FIFO_U16 = 1;
                }
                {
                    f32 y = (&overlay->beams[i])->base.y;
                    f32 baseRadius = (&overlay->beams[i])->baseRadius;
                    f32 x = (&overlay->beams[i])->base.x - baseRadius;
                    f32 z = (&overlay->beams[i])->base.z + baseRadius;
                    GX_FIFO_F32 = x;
                    GX_FIFO_F32 = y;
                    GX_FIFO_F32 = z;
                    GX_FIFO_U32 = (&overlay->beams[i])->baseColor;
                    GX_FIFO_U16 = 0;
                    GX_FIFO_U16 = 1;
                }
            }
        }
    }
    GXSetProjection(sScreenProjection, GX_ORTHOGRAPHIC);
    GXLoadPosMtxImm(identity, GX_PNMTX0);
    SetDisplayStateTexture(NULL, 0, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GX_FIFO_F32 = lbl_3_rodata_3D40;
    GX_FIFO_F32 = lbl_3_rodata_3D40;
    GX_FIFO_F32 = lbl_3_rodata_3D44;
    GX_FIFO_U32 = overlay->dimColor;
    GX_FIFO_U16 = 0;
    GX_FIFO_U16 = 0;
    GX_FIFO_F32 = lbl_3_rodata_3D48;
    GX_FIFO_F32 = lbl_3_rodata_3D40;
    GX_FIFO_F32 = lbl_3_rodata_3D44;
    GX_FIFO_U32 = overlay->dimColor;
    GX_FIFO_U16 = 1;
    GX_FIFO_U16 = 0;
    GX_FIFO_F32 = lbl_3_rodata_3D48;
    GX_FIFO_F32 = lbl_3_rodata_3D4C;
    GX_FIFO_F32 = lbl_3_rodata_3D44;
    GX_FIFO_U32 = overlay->dimColor;
    GX_FIFO_U16 = 1;
    GX_FIFO_U16 = 1;
    GX_FIFO_F32 = lbl_3_rodata_3D40;
    GX_FIFO_F32 = lbl_3_rodata_3D4C;
    GX_FIFO_F32 = lbl_3_rodata_3D44;
    GX_FIFO_U32 = overlay->dimColor;
    GX_FIFO_U16 = 0;
    GX_FIFO_U16 = 1;
    minigameWinnerSpotlight_clearDepth(FALSE);
}

typedef struct {
    u8 _000[0x34];
    Vec position;
    u8 _040[0x252 - 0x40];
    s8 charID;
} SpotlightActor;

typedef struct {
    u8 _0000[0x2C50];
    SpotlightActor* actors[4];
} SpotlightAnimView;

static inline SpotlightOverlay* getOverlay(void) {
    return &sOverlays[drawStadiumRelated];
}

// .text:0x0015FB84 size:0x3A4 mapped:0x8079EC18
void minigameWinnerSpotlight_queue(int count, ...) {
    va_list args;
    int counts[4];
    int i;
    SpotlightOverlay* overlay;
    SpotlightSettings* settings;
    f32 beamHeight;
    u8* slot;

    overlay = getOverlay();
    settings = &sSettings;
    beamHeight = -((f32)settings->beamHeight / lbl_3_rodata_3D30);
    slot = lbl_3_common_bss_35154;
    overlay->beamCount = count;
    overlay->groundTexture = *(u8**)(slot + 4) + 0x344; // textures->records[26]
    overlay->dimColor = *(u32*)(slot + 0x468);
    memset(counts, 0, sizeof(counts));
    va_start(args, count);
    for (i = 0; i < count; i++) {
        counts[va_arg(args, int)]++;
    }
    va_end(args);

    {
        SpotlightBeamOffset* oneBeamOffsets = &sSettings.coords[0];
        SpotlightBeamOffset* twoBeamOffsets = &sSettings.coords[1];
        SpotlightBeamOffset* threeBeamOffsets = &sSettings.coords[3];
        int used = 0;
        SpotlightBeam* beam = getOverlay()->beams;
        for (i = 0; i < 4; i++) {
            SpotlightActor* actor = ((SpotlightAnimView*)hugeAnimStruct)->actors[i];
            if (actor != 0) {
                SpotlightBeamOffset* coords;
                switch (counts[i]) {
                case 0: break;
                case 1: coords = oneBeamOffsets; break;
                case 2: coords = twoBeamOffsets; break;
                case 3:
                default: coords = threeBeamOffsets; break;
                }
                while (counts[i]--) {
                    f32 xOffset = coords->x / lbl_3_rodata_3D30;
                    u32 baseColor = coords->baseColor;
                    s32 beamYOffset = coords->y;
                    u32 topColor = coords->topColor;
                    coords++;
                    beam->enabled = TRUE;
                    beam->top.x = xOffset + actor->position.x;
                    beam->top.y = beamHeight + (actor->position.y + (f32)beamYOffset / lbl_3_rodata_3D30);
                    beam->top.z = actor->position.z;
                    beam->base.x = actor->position.x;
                    beam->base.y = actor->position.y;
                    beam->base.z = actor->position.z;
                    beam->topHalfWidth = (f32)sBeamSizes[sBeamSizeClass[actor->charID]][0] / lbl_3_rodata_3D30;
                    beam->baseRadius = (f32)sBeamSizes[sBeamSizeClass[actor->charID]][1] / lbl_3_rodata_3D30;
                    beam->topColor = topColor;
                    beam->baseColor = baseColor;
                    beam++;
                    used++;
                }
            }
        }
        for (; used < 4; used++, beam++) beam->enabled = FALSE;
    }
    fn_800A7D4C(11, getOverlay());
}

// .text:0x0015FA58 size:0x12C mapped:0x8079EAEC
void minigameWinnerSpotlight_start(int count, s32* slots) {
    DrawingSceneStruct* item = insertGraphicDrawingFunction(minigameWinnerSpotlight_fadeIn, currentDrawingItem->priority);

    sState.active = TRUE;
    sState.showBeams = FALSE;
    sState.dimColor = 0;
    sState.slotCount = 0;
    while (count-- != 0) {
        sState.slots[sState.slotCount++] = *slots++;
    }
    item->state = sSettings.fadeFrames;
}

// .text:0x0015F9C0 size:0x98 mapped:0x8079EA54
void minigameWinnerSpotlight_fadeIn(void) {
    if (g_d_GameSettings._55 != 0 || sState.paused != 0) {
        removeCurrentDrawingItem();
        return;
    }
    currentDrawingItem->state--;
    sState.dimColor = sSettings.dimAlpha * (sSettings.fadeFrames - currentDrawingItem->state) / sSettings.fadeFrames;
    if (currentDrawingItem->state == 0) {
        removeCurrentDrawingItem();
    }
}

// .text:0x0015F9AC size:0x14 mapped:0x8079EA40
void minigameWinnerSpotlight_show(void) {
    sState.showBeams = TRUE;
}

// .text:0x0015F998 size:0x14 mapped:0x8079EA2C
void minigameWinnerSpotlight_stop(void) {
    sState.active = FALSE;
}

// .text:0x0015F874 size:0x124 mapped:0x8079E908
void minigameWinnerSpotlight_clearDepth(BOOL nearPlane) {
    Mtx model;

    GXSetProjection(sScreenProjection, GX_ORTHOGRAPHIC);
    PSMTXIdentity(model);
    GXLoadPosMtxImm(model, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetColorUpdate(FALSE);
    GXSetAlphaUpdate(FALSE);
    GXSetZMode(TRUE, GX_ALWAYS, TRUE);
    gOz_GXSetTexture(GX_PASSCLR, 0, FALSE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA4, 0);
    if (nearPlane) {
        GXSetArray(GX_VA_POS, sScreenQuadNear, sizeof(Vec));
    } else {
        GXSetArray(GX_VA_POS, sScreenQuadFar, sizeof(Vec));
    }
    GXCallDisplayList(sScreenQuadDL, sizeof(sScreenQuadDL));
    GXSetColorUpdate(TRUE);
    GXSetAlphaUpdate(TRUE);
}
