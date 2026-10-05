#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_rep3B70
#include "game/data_only/rep_3B70.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "Unknown/File_0x80052734.h"
#include "Unknown/sub.h"
#include "Dolphin/mtx.h"
#include "Dolphin/gx.h"
#include "Dolphin/GX/GXFifo.h"

typedef struct Rep3B70Entry Rep3B70Entry;

struct Rep3B70Entry {
    u32 _00;
    void (*draw)(Rep3B70Entry* entry);
    Mtx transform;
    u8 projection[0x1C];
    Vec corners[4];
    u8* counter;
};

typedef struct {
    s32 size;
    u32 alpha;
} Rep3B70Size;

void fn_3_15C230(Rep3B70Entry* entry);
extern u8 drawStadiumRelated;
extern u8 lbl_3_common_bss_35154[];
extern void fn_800340F4(Mtx);
extern void fn_800A7D4C(s32, void*);

// This unit's .data (0x271A8-0x273DC, symbols lbl_3_data_271A8/273CC/273D4).
// MWCC pools file-static data and addresses each object as base+offset from a
// single register, which is what the code expects; extern declarations do not
// reproduce that. The .data range must be split into this unit before it can
// be linked as Matching.
static u8 sActiveCount[4] = {0};
static Rep3B70Entry sEntries[2][2] = {
    {{0, fn_3_15C230}, {0, fn_3_15C230}},
    {{0, fn_3_15C230}, {0, fn_3_15C230}},
};
static Rep3B70Size sSizeA = {100000, 0x80};
static Rep3B70Size sSizeB = {190000, 0x80};

// .text:0x0015C3F8 size:0x1FC mapped:0x8079B48C
void fn_3_15C3F8(void) {
    Mtx matrix;
    Rep3B70Entry* entry;
    f32 scale;
    int effectIndex;
    int i;
    u8 slot = drawStadiumRelated;
    u8* activeCount = &sActiveCount[slot];
    u8 count = (*activeCount)++;

    entry = &sEntries[count][slot];
    entry->counter = activeCount;
    fn_80024390(returnFloatFromModeIndex(0)->proj, (f32*)entry->projection, GX_PERSPECTIVE);
    PSMTXTrans(entry->transform, *(f32*)(lbl_3_common_bss_35154 + 0x440),
               *(f32*)(lbl_3_common_bss_35154 + 0x444),
               *(f32*)(lbl_3_common_bss_35154 + 0x448));
    PSMTXConcat(returnFloatFromModeIndex(0)->view, entry->transform, entry->transform);

    if (g_GameLogic.bOD_framesInLiveBallScene >= 0) {
        effectIndex = 2;
    } else {
        effectIndex = g_Ball.framesSinceHit > 0;
    }
    if (effectIndex == 2) {
        scale = (f32)sSizeB.size / 100000.0f / 2.0f;
    } else {
        scale = (f32)sSizeA.size / 100000.0f / 2.0f;
    }
    fn_800340F4(matrix);
    entry->corners[3].x = -scale;
    entry->corners[1].y = -scale;
    entry->corners[0].y = -scale;
    entry->corners[0].x = -scale;
    entry->corners[1].x = scale;
    entry->corners[3].y = scale;
    entry->corners[2].y = scale;
    entry->corners[2].x = scale;
    entry->corners[3].z = 0.0f;
    entry->corners[2].z = 0.0f;
    entry->corners[1].z = 0.0f;
    entry->corners[0].z = 0.0f;
    for (i = 0; i < 4; i++) {
        PSMTXMultVec(matrix, &entry->corners[i], &entry->corners[i]);
    }
    fn_800A7D4C(11, entry);
}

// .text:0x0015C230 size:0x1C8 mapped:0x8079B304
void fn_3_15C230(Rep3B70Entry* entry) {
    int effectIndex;
    u32 color;

    gOz_GXSetTexture(GX_MODULATE, 0, FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
    GXSetZMode(TRUE, GX_LEQUAL, FALSE);
    SetDisplayStateTexture((TextureBody*)(*(u8**)(lbl_3_common_bss_35154 + 4) + 0x2E4), 0, 0);
    GXSetProjectionv((f32*)entry->projection);
    GXLoadPosMtxImm(entry->transform, 0);
    GXSetCurrentMtx(0);
    GXSetCullMode(GX_CULL_NONE);

    if (g_GameLogic.bOD_framesInLiveBallScene >= 0) {
        effectIndex = 2;
    } else {
        effectIndex = g_Ball.framesSinceHit > 0;
    }
    if (effectIndex == 2) {
        color = sSizeB.alpha | 0xFFFFFF00;
    } else {
        color = sSizeA.alpha | 0xFFFFFF00;
    }

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(entry->corners[0].x, entry->corners[0].y, entry->corners[0].z);
    GXColor1u32(color);
    GXTexCoord2s16(0, 0);
    GXPosition3f32(entry->corners[1].x, entry->corners[1].y, entry->corners[1].z);
    GXColor1u32(color);
    GXTexCoord2s16(1, 0);
    GXPosition3f32(entry->corners[2].x, entry->corners[2].y, entry->corners[2].z);
    GXColor1u32(color);
    GXTexCoord2s16(1, 1);
    GXPosition3f32(entry->corners[3].x, entry->corners[3].y, entry->corners[3].z);
    GXColor1u32(color);
    GXTexCoord2s16(0, 1);
    (*entry->counter)--;
}
