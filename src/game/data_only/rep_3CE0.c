#define REP_HEADER_DATA_FN getRepHeaderData_rep3CE0
#include "game/data_only/rep_3CE0.h"
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

typedef struct {
    Vec position;
    Vec secondPosition;
    f32 halfWidth;
    f32 radius;
    u32 color;
    u32 other;
    s32 enabled;
} Rep3CE0Marker;

typedef struct Rep3CE0Overlay {
    u32 _00;
    void (*draw)(void*);
    Rep3CE0Marker markers[4];
    void* texture;
    u32 backgroundColor;
    s32 markerCount;
} Rep3CE0Overlay;

typedef struct {
    s32 x;
    s32 y;
    u32 color;
    u32 other;
} Rep3CE0Coord;

typedef struct {
    s32 fadeTarget;
    s32 fadeFrames;
    Rep3CE0Coord coords[6];
    s32 yOffset;
} Rep3CE0Settings;

extern u8 lbl_3_common_bss_35154[];

typedef struct {
    u8 _000[0x468];
    u32 backgroundColor;
    u8 _46C[4];
    u8 _470;
    u8 showMarkers;
    u8 valueCount;
    u8 values[6];
    u8 _479;
    u8 _47A[6];
} Rep3CE0State;

#define sState (*(Rep3CE0State*)lbl_3_common_bss_35154)
extern u8 hugeAnimStruct[];
extern u8 drawStadiumRelated;
extern void fn_800A7D4C(s32, void*);

// This unit's .data (0x27EC0-0x281F0). MWCC pools file-static data and
// addresses each object as base+offset from a single register, so these must
// stay statics defined in this order.
static s32 sMarkerSizes[3][2] = {
    {15000, 90000},
    {20000, 129999},
    {30000, 180000},
};
static u8 sMarkerSizeClass[0x38] = {
    1, 1, 2, 1, 1, 1, 1, 0, 0, 2, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 2, 2, 2, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
};
static Rep3CE0Settings sSettings = {
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
static Rep3CE0Overlay sOverlays[2] = {
    {0, fn_3_15FF28},
    {0, fn_3_15FF28},
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
void fn_3_15FF28(void* arg) {
    Rep3CE0Overlay* overlay = (Rep3CE0Overlay*)arg;
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
    fn_3_15F874(FALSE);

    mode = returnsCurrentMode();
    camera = returnFloatFromModeIndex(mode);
    setScissorAndProjection(mode);
    gOz_GXSetTexture(GX_MODULATE, 0, FALSE);

    if (sState.valueCount != 0 && sState.showMarkers) {
        GXSetZMode(TRUE, GX_ALWAYS, TRUE);
        GXLoadPosMtxImm(identity, GX_PNMTX0);
        SetDisplayStateTexture(NULL, 0, 0);
        for (i = 0; i < overlay->markerCount; i++) {
            if (overlay->markers[i].enabled) {
                PSMTXMultVec(camera->view, &overlay->markers[i].position, &transformed);
                GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                {
                    f32 x = transformed.x;
                    GX_FIFO_F32 = x - overlay->markers[i].halfWidth;
                    GX_FIFO_F32 = transformed.y;
                    GX_FIFO_F32 = transformed.z;
                    GX_FIFO_U32 = overlay->markers[i].color;
                    GX_FIFO_U16 = 0;
                    GX_FIFO_U16 = 0;
                    GX_FIFO_F32 = x + overlay->markers[i].halfWidth;
                    GX_FIFO_F32 = transformed.y;
                    GX_FIFO_F32 = transformed.z;
                    GX_FIFO_U32 = overlay->markers[i].color;
                    GX_FIFO_U16 = 1;
                    GX_FIFO_U16 = 0;
                }
                PSMTXMultVec(camera->view, &overlay->markers[i].secondPosition, &transformed);
                direction.x = transformed.x;
                direction.y = lbl_3_rodata_3D40;
                direction.z = transformed.z;
                if (PSVECMag(&direction)) {
                    PSVECNormalize(&direction, &direction);
                    PSVECScale(&direction, overlay->markers[i].radius, &direction);
                } else {
                    direction.x = overlay->markers[i].radius;
                    direction.z = lbl_3_rodata_3D40;
                }
                {
                    f32 x = transformed.x;
                    f32 dx;
                    GX_FIFO_F32 = x - direction.z;
                    GX_FIFO_F32 = transformed.y;
                    GX_FIFO_F32 = transformed.z + (dx = direction.x);
                    GX_FIFO_U32 = overlay->markers[i].other;
                    GX_FIFO_U16 = 1;
                    GX_FIFO_U16 = 1;
                    GX_FIFO_F32 = x + direction.z;
                    GX_FIFO_F32 = transformed.y;
                    GX_FIFO_F32 = transformed.z - dx;
                    GX_FIFO_U32 = overlay->markers[i].other;
                    GX_FIFO_U16 = 0;
                    GX_FIFO_U16 = 1;
                }
            }
        }
        GXSetZMode(TRUE, GX_LEQUAL, TRUE);
        GXLoadPosMtxImm(camera->view, GX_PNMTX0);
        SetDisplayStateTexture((TextureBody*)overlay->texture, 0, 0);
        for (i = 0; i < overlay->markerCount; i++) {
            if ((&overlay->markers[i])->enabled) {
                GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                {
                    f32 y = (&overlay->markers[i])->secondPosition.y;
                    f32 radius = (&overlay->markers[i])->radius;
                    f32 x = (&overlay->markers[i])->secondPosition.x - radius;
                    f32 z = (&overlay->markers[i])->secondPosition.z - radius;
                    GX_FIFO_F32 = x;
                    GX_FIFO_F32 = y;
                    GX_FIFO_F32 = z;
                    GX_FIFO_U32 = (&overlay->markers[i])->other;
                    GX_FIFO_U16 = 0;
                    GX_FIFO_U16 = 0;
                }
                {
                    f32 y = (&overlay->markers[i])->secondPosition.y;
                    f32 radius = (&overlay->markers[i])->radius;
                    f32 x = (&overlay->markers[i])->secondPosition.x + radius;
                    f32 z = (&overlay->markers[i])->secondPosition.z - radius;
                    GX_FIFO_F32 = x;
                    GX_FIFO_F32 = y;
                    GX_FIFO_F32 = z;
                    GX_FIFO_U32 = (&overlay->markers[i])->other;
                    GX_FIFO_U16 = 1;
                    GX_FIFO_U16 = 0;
                }
                {
                    f32 y = (&overlay->markers[i])->secondPosition.y;
                    f32 radius = (&overlay->markers[i])->radius;
                    f32 x = (&overlay->markers[i])->secondPosition.x + radius;
                    f32 z = (&overlay->markers[i])->secondPosition.z + radius;
                    GX_FIFO_F32 = x;
                    GX_FIFO_F32 = y;
                    GX_FIFO_F32 = z;
                    GX_FIFO_U32 = (&overlay->markers[i])->other;
                    GX_FIFO_U16 = 1;
                    GX_FIFO_U16 = 1;
                }
                {
                    f32 y = (&overlay->markers[i])->secondPosition.y;
                    f32 radius = (&overlay->markers[i])->radius;
                    f32 x = (&overlay->markers[i])->secondPosition.x - radius;
                    f32 z = (&overlay->markers[i])->secondPosition.z + radius;
                    GX_FIFO_F32 = x;
                    GX_FIFO_F32 = y;
                    GX_FIFO_F32 = z;
                    GX_FIFO_U32 = (&overlay->markers[i])->other;
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
    GX_FIFO_U32 = overlay->backgroundColor;
    GX_FIFO_U16 = 0;
    GX_FIFO_U16 = 0;
    GX_FIFO_F32 = lbl_3_rodata_3D48;
    GX_FIFO_F32 = lbl_3_rodata_3D40;
    GX_FIFO_F32 = lbl_3_rodata_3D44;
    GX_FIFO_U32 = overlay->backgroundColor;
    GX_FIFO_U16 = 1;
    GX_FIFO_U16 = 0;
    GX_FIFO_F32 = lbl_3_rodata_3D48;
    GX_FIFO_F32 = lbl_3_rodata_3D4C;
    GX_FIFO_F32 = lbl_3_rodata_3D44;
    GX_FIFO_U32 = overlay->backgroundColor;
    GX_FIFO_U16 = 1;
    GX_FIFO_U16 = 1;
    GX_FIFO_F32 = lbl_3_rodata_3D40;
    GX_FIFO_F32 = lbl_3_rodata_3D4C;
    GX_FIFO_F32 = lbl_3_rodata_3D44;
    GX_FIFO_U32 = overlay->backgroundColor;
    GX_FIFO_U16 = 0;
    GX_FIFO_U16 = 1;
    fn_3_15F874(FALSE);
}

typedef struct {
    u8 _000[0x34];
    Vec position;
    u8 _040[0x252 - 0x40];
    s8 charID;
} Rep3CE0Actor;

typedef struct {
    u8 _0000[0x2C50];
    Rep3CE0Actor* actors[4];
} Rep3CE0AnimView;

static inline Rep3CE0Overlay* getOverlay(void) {
    return &sOverlays[drawStadiumRelated];
}

// .text:0x0015FB84 size:0x3A4 mapped:0x8079EC18
void fn_3_15FB84(int count, ...) {
    va_list args;
    int counts[4];
    int i;
    Rep3CE0Overlay* overlay;
    Rep3CE0Settings* settings;
    f32 yOffset;
    u8* slot;

    overlay = getOverlay();
    settings = &sSettings;
    yOffset = -((f32)settings->yOffset / lbl_3_rodata_3D30);
    slot = lbl_3_common_bss_35154;
    overlay->markerCount = count;
    overlay->texture = *(u8**)(slot + 4) + 0x344;
    overlay->backgroundColor = *(u32*)(slot + 0x468);
    memset(counts, 0, sizeof(counts));
    va_start(args, count);
    for (i = 0; i < count; i++) {
        counts[va_arg(args, int)]++;
    }
    va_end(args);

    {
        Rep3CE0Coord* firstCoords = &sSettings.coords[0];
        Rep3CE0Coord* secondCoords = &sSettings.coords[1];
        Rep3CE0Coord* fourthCoords = &sSettings.coords[3];
        int used = 0;
        Rep3CE0Marker* marker = getOverlay()->markers;
        for (i = 0; i < 4; i++) {
            Rep3CE0Actor* actor = ((Rep3CE0AnimView*)hugeAnimStruct)->actors[i];
            if (actor != 0) {
                Rep3CE0Coord* coords;
                switch (counts[i]) {
                case 0: break;
                case 1: coords = firstCoords; break;
                case 2: coords = secondCoords; break;
                case 3:
                default: coords = fourthCoords; break;
                }
                while (counts[i]--) {
                    f32 xOffset = coords->x / lbl_3_rodata_3D30;
                    u32 other = coords->other;
                    s32 localYOffset = coords->y;
                    u32 color = coords->color;
                    coords++;
                    marker->enabled = TRUE;
                    marker->position.x = xOffset + actor->position.x;
                    marker->position.y = yOffset + (actor->position.y + (f32)localYOffset / lbl_3_rodata_3D30);
                    marker->position.z = actor->position.z;
                    marker->secondPosition.x = actor->position.x;
                    marker->secondPosition.y = actor->position.y;
                    marker->secondPosition.z = actor->position.z;
                    marker->halfWidth = (f32)sMarkerSizes[sMarkerSizeClass[actor->charID]][0] / lbl_3_rodata_3D30;
                    marker->radius = (f32)sMarkerSizes[sMarkerSizeClass[actor->charID]][1] / lbl_3_rodata_3D30;
                    marker->color = color;
                    marker->other = other;
                    marker++;
                    used++;
                }
            }
        }
        for (; used < 4; used++, marker++) marker->enabled = FALSE;
    }
    fn_800A7D4C(11, getOverlay());
}

// .text:0x0015FA58 size:0x12C mapped:0x8079EAEC
void fn_3_15FA58(int count, s32* values) {
    DrawingSceneStruct* item = insertGraphicDrawingFunction(fn_3_15F9C0, currentDrawingItem->priority);

    sState._470 = TRUE;
    sState.showMarkers = FALSE;
    sState.backgroundColor = 0;
    sState.valueCount = 0;
    while (count-- != 0) {
        sState.values[sState.valueCount++] = *values++;
    }
    item->state = sSettings.fadeFrames;
}

// .text:0x0015F9C0 size:0x98 mapped:0x8079EA54
void fn_3_15F9C0(void) {
    if (g_d_GameSettings._55 != 0 || sState._479 != 0) {
        removeCurrentDrawingItem();
        return;
    }
    currentDrawingItem->state--;
    sState.backgroundColor = sSettings.fadeTarget * (sSettings.fadeFrames - currentDrawingItem->state) / sSettings.fadeFrames;
    if (currentDrawingItem->state == 0) {
        removeCurrentDrawingItem();
    }
}

// .text:0x0015F9AC size:0x14 mapped:0x8079EA40
void fn_3_15F9AC(void) {
    sState.showMarkers = TRUE;
}

// .text:0x0015F998 size:0x14 mapped:0x8079EA2C
void fn_3_15F998(void) {
    sState._470 = FALSE;
}

// .text:0x0015F874 size:0x124 mapped:0x8079E908
void fn_3_15F874(BOOL nearPlane) {
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
