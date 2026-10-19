#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_starEffectGlow
#include "game/batting/star_effect_glow.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "Unknown/File_0x80052734.h"
#include "Unknown/sub.h"
#include "Dolphin/mtx.h"
#include "Dolphin/gx.h"
#include "Dolphin/GX/GXFifo.h"
#include "Unknown/File_0x80034e20.h"

// An additive-blended glow quad drawn at the captain star-effect position
// (the shared effects block's +0x440, which scene_effects' fn_3_BD6AC and
// animationRelated set for both star swings and star pitches). It is smaller
// before contact and larger once the ball is hit or a live-ball scene runs.
// Nothing in the REL calls starEffectGlow_queue, so this looks like leftover
// code; which captain's effect it belonged to is not known (it links between
// star_swing_peach_daisy.c and stat_book.c). Names are inferred.

typedef struct StarGlowEntry StarGlowEntry;

struct StarGlowEntry {
    u32 _00;
    void (*draw)(StarGlowEntry* entry);
    Mtx transform;
    u8 projection[0x1C];
    Vec corners[4];
    u8* counter;
};

typedef struct {
    s32 size;
    u32 alpha;
} StarGlowSize;

void starEffectGlow_draw(StarGlowEntry* entry);
extern u8 drawStadiumRelated;

// The part of the shared effects block (lbl_3_common_bss_35154) this unit reads.
extern struct {
    /*0x000*/ u8 _000[4];
    /*0x004*/ TextureHeader* textures;
    /*0x008*/ u8 _008[0x440 - 0x8];
    /*0x440*/ VecXYZ starEffectPos;
} lbl_3_common_bss_35154;
extern void fn_800340F4(Mtx);
extern void fn_800A7D4C(s32, void*);

// This unit's .data (0x271A8-0x273DC, symbols lbl_3_data_271A8/273CC/273D4).
// MWCC pools file-static data and addresses each object as base+offset from a
// single register, which is what the code expects; extern declarations do not
// reproduce that, so these stay statics defined in this order.
static u8 sActiveCount[4] = {0};
static StarGlowEntry sEntries[2][2] = {
    {{0, starEffectGlow_draw}, {0, starEffectGlow_draw}},
    {{0, starEffectGlow_draw}, {0, starEffectGlow_draw}},
};
// Half-size of the quad (x 100000) and its alpha: before contact, then once hit.
static StarGlowSize sSizeBeforeHit = {100000, 0x80};
static StarGlowSize sSizeAfterHit = {190000, 0x80};

// .text:0x0015C3F8 size:0x1FC mapped:0x8079B48C
void starEffectGlow_queue(void) {
    Mtx matrix;
    StarGlowEntry* entry;
    f32 scale;
    int effectIndex;
    int i;
    u8 slot = drawStadiumRelated;
    u8* activeCount = &sActiveCount[slot];
    u8 count = (*activeCount)++;

    entry = &sEntries[count][slot];
    entry->counter = activeCount;
    fn_80024390(returnFloatFromModeIndex(0)->proj, (f32*)entry->projection, GX_PERSPECTIVE);
    PSMTXTrans(entry->transform, lbl_3_common_bss_35154.starEffectPos.x,
               lbl_3_common_bss_35154.starEffectPos.y,
               lbl_3_common_bss_35154.starEffectPos.z);
    PSMTXConcat(returnFloatFromModeIndex(0)->view, entry->transform, entry->transform);

    if (g_GameLogic.bOD_framesInLiveBallScene >= 0) {
        effectIndex = 2;
    } else {
        effectIndex = g_Ball.framesSinceHit > 0;
    }
    if (effectIndex == 2) {
        scale = (f32)sSizeAfterHit.size / 100000.0f / 2.0f;
    } else {
        scale = (f32)sSizeBeforeHit.size / 100000.0f / 2.0f;
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
void starEffectGlow_draw(StarGlowEntry* entry) {
    int effectIndex;
    u32 color;

    gOz_GXSetTexture(GX_MODULATE, 0, FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
    GXSetZMode(TRUE, GX_LEQUAL, FALSE);
    SetDisplayStateTexture((TextureBody*)&lbl_3_common_bss_35154.textures->records[23], 0, 0);
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
        color = sSizeAfterHit.alpha | 0xFFFFFF00;
    } else {
        color = sSizeBeforeHit.alpha | 0xFFFFFF00;
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
