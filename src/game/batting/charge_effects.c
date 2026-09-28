#include "game/batting/charge_effects.h"

/* charge_effects.c never calls dolsqrtf2(), so keep it internal. With the
 * header's default `extern` linkage MWCC materialises the unused out-of-line
 * copy's _half/_three local statics in this TU's .rodata, pushing every
 * constant-pool entry past the offsets the linked module actually has. */
#define SQRT2_LINKAGE static
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/stadium/stadium_framework.h"
#include "Dolphin/mtx.h"
#include "Dolphin/gx.h"
#include "Dolphin/os.h"
#include "Dolphin/stl.h"
#include "stl/math.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x8005268c.h"
#include "Unknown/File_0x80052734.h"
#include "Unknown/File_0x800b4bc8.h"
#include "Unknown/File_0x800bda94.h"

typedef void (*ChargeTevCallback)(void* model, GXTevStageID* stage, GXTexCoordID* coord, GXTexMapID* map, s8* nStages, s8* nCoords);

// An entry of the hugeAnimStruct actor table at +0x2C50.
typedef struct _ChargeAnimActor {
    /*0x000*/ u8 _000[0x34];
    /*0x034*/ VecXYZ pos;
    /*0x040*/ u8 _040[0x5C - 0x40];
    /*0x05C*/ ChargeTevCallback tevCallback;
    /*0x060*/ u8 _060[0x252 - 0x60];
    /*0x252*/ s8 charId;
    /*0x253*/ u8 _253;
    /*0x254*/ s8 animIndex;
} ChargeAnimActor;

typedef struct _ChargeSlot {
    /*0x00*/ s16 actorIndex; // -1 = free
    /*0x02*/ s16 burstTimer;
    /*0x04*/ VecXYZ pos;
    /*0x10*/ VecXYZ origin;
    /*0x1C*/ f32 phase;
} ChargeSlot;

typedef struct _ChargeBurstParams {
    /*0x00*/ u32 texture;
    /*0x04*/ s32 unk04;
    /*0x08*/ s32 unk08;
    /*0x0C*/ s32 unk0C;
    /*0x10*/ s32 unk10;
    /*0x14*/ s32 unk14;
    /*0x18*/ s32 unk18;
    /*0x1C*/ s32 lifetime;
    /*0x20*/ s32 unk20;
    /*0x24*/ s32 unk24;
    /*0x28*/ s32 unk28;
    /*0x2C*/ s32 unk2C;
    /*0x30*/ s32 unk30;
    /*0x34*/ s32 unk34;
    /*0x38*/ s32 unk38;
    /*0x3C*/ s32 unk3C;
} ChargeBurstParams;

typedef struct _ChargeGlowEntry {
    /*0x00*/ u32 _00;
    /*0x04*/ void (*draw)(struct _ChargeGlowEntry* entry);
    /*0x08*/ VecXYZ pos;
    /*0x14*/ u32 frame;
} ChargeGlowEntry;

// DrawingSceneStruct views: +0x14.. is scratch owned by the node's func.
typedef struct _ChargeGlowNode {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ u32 frame;
    /*0x18*/ int slot;
    /*0x1C*/ int actorIndex;
    /*0x20*/ E(u8, BOOL) stop;
} ChargeGlowNode;

typedef struct _ChargeFadeNode {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ u8 actorIndex;
    /*0x15*/ u8 alpha;
    /*0x16*/ u8 timer;
} ChargeFadeNode;

typedef struct _ChargeAnimState {
    /*0x00*/ f32 unk0;
    /*0x04*/ f32 frame;
    /*0x08*/ u8 _08[4];
    /*0x0C*/ s16 unkC;
} ChargeAnimState;

// The part of the shared effects block (lbl_3_common_bss_35154, used by ~30 units) that this
// unit touches.
typedef struct _ChargeSharedEffectsBlock {
    /*0x000*/ u8 _000[0x4];
    /*0x004*/ u32 burstTexture;
    /*0x008*/ u8 _008[0x10 - 0x8];
    /*0x010*/ u8* glowOwner;
    /*0x014*/ u8 _014[0x20 - 0x14];
    /*0x020*/ ChargeAnimState glowStateA;
    /*0x030*/ u8 _030[0x38 - 0x30];
    /*0x038*/ u16 glowFrames;
    /*0x03A*/ u8 _03A[0x40 - 0x3A];
    /*0x040*/ void* glowHandleA;
    /*0x044*/ u8 _044[0x7C - 0x44];
    /*0x07C*/ ChargeAnimState glowStateB;
    /*0x08C*/ u8 _08C[0x9C - 0x8C];
    /*0x09C*/ void* glowHandleB;
    /*0x0A0*/ u8 _0A0[0x3AC - 0xA0];
    /*0x3AC*/ u32 flags;
    /*0x3B0*/ u8 _3B0[0x434 - 0x3B0];
    /*0x434*/ VecXYZ starHitPos;
    /*0x440*/ u8 _440[0x467 - 0x440];
    /*0x467*/ u8 starHitPitch;
    /*0x468*/ u8 _468[0x477 - 0x468];
    /*0x477*/ u8 glowActive[2];
    /*0x479*/ u8 _479[0x480 - 0x479];
} ChargeSharedEffectsBlock;

extern ChargeSharedEffectsBlock lbl_3_common_bss_35154;
extern u8 hugeAnimStruct[0x3154];
extern u8 drawStadiumRelated;
extern struct {
    u8 _00[0x28];
    u8 _28;
} lbl_80366158;

extern ChargeAnimActor* fn_80011570(void* model);
extern void fn_80027674(VecXYZ* origin, VecXYZ* pos, ChargeBurstParams* params, f32 scale, u8 effectId);
extern void fn_80027918(u8 effectId, f32 value);
extern void fn_800A7D4C(s32 arg0, void* arg1);
extern void fn_800BDA24(void* arg);

void fn_3_C0DD8(void* model, GXTevStageID* stage, GXTexCoordID* coord, GXTexMapID* map, s8* nStages, s8* nCoords);

static u8 chargeAlpha[2] = {0x50, 0x50};
static f32 chargeWaveFreq[3] = {18.849556f, 18.849556f, 37.699112f};
static u8 chargeColor[2][3] = {{0xFF, 0xF7, 0x88}, {0xFF, 0xF7, 0x88}};
static ChargeSlot chargeSlots[2] = {{-1}, {-1}};
static s32 chargeBurstSettings[3] = {250000, 150000, 4};
static ChargeBurstParams chargeBurstParams = {
    0, 3, 30, 8000, 10, 20, 1, 15, 99000, 99800, -500, -899, 255, 20, 10, -1
};
// Indexed by character id.
static s32 chargeCharacterParams[54][2] = {
    {129999, 250000}, {129999, 250000}, {150000, 270000}, {80000, 250000},
    {150000, 250000}, {150000, 250000}, {129999, 250000}, {60000, 250000},
    {60000, 250000}, {150000, 280000}, {150000, 259999}, {150000, 259999},
    {100000, 250000}, {50000, 250000}, {150000, 250000}, {60000, 250000},
    {60000, 250000}, {120000, 250000}, {70000, 250000}, {100000, 250000},
    {129999, 250000}, {150000, 259999}, {150000, 259999}, {150000, 259999},
    {100000, 250000}, {100000, 250000}, {100000, 250000}, {150000, 250000},
    {60000, 250000}, {60000, 250000}, {60000, 250000}, {60000, 250000},
    {60000, 250000}, {100000, 250000}, {100000, 250000}, {100000, 250000},
    {100000, 250000}, {150000, 250000}, {129999, 290000}, {80000, 250000},
    {60000, 250000}, {60000, 250000}, {100000, 250000}, {129999, 250000},
    {60000, 250000}, {60000, 250000}, {60000, 250000}, {60000, 250000},
    {100000, 250000}, {100000, 250000}, {100000, 250000}, {100000, 250000},
    {150000, 250000}, {150000, 250000},
};
static f32 chargeThreshold = 95.0f;
static ChargeGlowNode* chargeDrawItems[2] = {NULL, NULL};
static ChargeGlowEntry chargeGlowEntries[2][2] = {
    {{0, fn_3_C095C}, {0, fn_3_C095C}},
    {{0, fn_3_C095C}, {0, fn_3_C095C}},
};

static u8 chargeTexData[0x40] ATTRIBUTE_ALIGN(32);
static GXTexObj chargeTexObj;

static inline int findChargeSlot(int actorIndex) {
    int i = 1;
    do {
        if (actorIndex == chargeSlots[i].actorIndex) {
            break;
        }
    } while (i-- != 0);
    return i;
}

static inline int getChargeEffectId(int slot) {
    int effectId = 0x18;
    if (slot != 0) {
        effectId = 0x17;
    }
    return effectId;
}

static inline void releaseChargeSlot(int actorIndex, int slot) {
    ChargeAnimActor* actor = *(ChargeAnimActor**)(hugeAnimStruct + actorIndex * 4 + 0x2C50);

    if (actor != NULL) {
        actor->tevCallback = NULL;
    }
    chargeSlots[slot].actorIndex = -1;
    fn_80027918(getChargeEffectId(slot), 0.0f);
}

// .text:0x000C1770 size:0x1C0 mapped:0x80700804
void maybeConfigureChargeEffectGraphics(int actorIndex) {
    ChargeAnimActor* actor = ((ChargeAnimActor**)(hugeAnimStruct + 0x2C50))[actorIndex];
    int slot;

    if (actor == NULL) {
        return;
    }
    slot = findChargeSlot(-1);
    if (slot < 0) {
        return;
    }

    chargeBurstParams.texture = lbl_3_common_bss_35154.burstTexture;
    chargeSlots[slot].actorIndex = actorIndex;
    chargeSlots[slot].origin.x = actor->pos.x;
    chargeSlots[slot].origin.z = actor->pos.z;
    chargeSlots[slot].origin.y = -(chargeCharacterParams[actor->charId][0] / 100000.0f);
    memcpy(&chargeSlots[slot].pos, &chargeSlots[slot].origin, sizeof(VecXYZ));
    chargeSlots[slot].burstTimer = 0;
    fn_80027918(getChargeEffectId(slot), 0.0f);
    fn_3_C0F8C();
    lbl_3_common_bss_35154.glowActive[slot] = 0;
}

// .text:0x000C1344 size:0x42C mapped:0x807003D8
void applyChargeAnimationEffect(int actorIndex, BOOL fullyCharged, f32 charge, f32 release) {
    ChargeAnimActor* actor;
    int slot;

    if (lbl_80366158._28 != 0) {
        return;
    }
    actor = ((ChargeAnimActor**)(hugeAnimStruct + 0x2C50))[actorIndex];
    if (actor == NULL) {
        return;
    }
    slot = findChargeSlot(actorIndex);
    if (slot < 0) {
        return;
    }

    getAnimRelatedCoordinates(actorIndex, 4, &chargeSlots[slot].pos);
    if (charge > 0.0f && charge < chargeThreshold) {
        if (chargeSlots[slot].burstTimer-- == 0) {
            chargeSlots[slot].burstTimer = chargeBurstParams.lifetime;
            fn_80027674(&chargeSlots[slot].origin, &chargeSlots[slot].pos, &chargeBurstParams,
                        chargeBurstSettings[0] / 100000.0f, slot <= 0 ? 0x18 : 0x17);
            actor->tevCallback = fn_3_C0DD8;
        }
    }
    sin(charge * chargeWaveFreq[slot] / 100.0f);
    if (charge < 100.0f) {
        fn_3_C0D10(slot, chargeColor[slot][0], chargeColor[slot][1], chargeColor[slot][2],
                   chargeAlpha[slot] * (0.5 * sin(charge * chargeWaveFreq[slot] / 100.0f) + 0.5));
        chargeSlots[slot].phase = charge;
    } else {
        fn_3_C0D10(slot, chargeColor[slot][0], chargeColor[slot][1], chargeColor[slot][2],
                   chargeAlpha[slot] * (0.5 * sin(release * chargeWaveFreq[slot] / 100.0f) + 0.5));
        chargeSlots[slot].phase = release;
    }
    if (fullyCharged && lbl_3_common_bss_35154.glowActive[slot] == 0) {
        lbl_3_common_bss_35154.glowActive[slot] = 1;
        fn_3_C0C4C(slot);
    }
}

// .text:0x000C11CC size:0x178 mapped:0x80700260
void fn_3_C11CC(int actorIndex, BOOL immediate) {
    int slot = findChargeSlot(actorIndex);
    ChargeFadeNode* node;

    if (slot < 0) {
        return;
    }
    if (immediate) {
        releaseChargeSlot(actorIndex, slot);
    } else {
        node = (ChargeFadeNode*)insertGraphicDrawingFunction(fn_3_C1004, currentDrawingItem->priority);
        node->actorIndex = actorIndex;
        node->alpha = chargeAlpha[slot] * (0.5 * sin(chargeWaveFreq[slot] * chargeSlots[slot].phase / 100.0f) + 0.5);
        node->timer = 10;
    }
}

// .text:0x000C1004 size:0x1C8 mapped:0x80700098
void fn_3_C1004(void) {
    ChargeFadeNode* node = (ChargeFadeNode*)currentDrawingItem;
    ChargeAnimActor* actor = ((ChargeAnimActor**)(hugeAnimStruct + 0x2C50))[node->actorIndex];
    int slot = findChargeSlot(node->actorIndex);

    if (slot < 0) {
        return;
    }
    if (--node->timer == 0) {
        if (actor != NULL) {
            actor->tevCallback = NULL;
        }
        chargeSlots[slot].actorIndex = -1;
        removeCurrentDrawingItem();
    }
    fn_3_C0D10(slot, chargeColor[slot][0], chargeColor[slot][1], chargeColor[slot][2], node->alpha * node->timer / 10);
    fn_80027918(getChargeEffectId(slot), node->timer / 10.0f);
}

// .text:0x000C0F8C size:0x78 mapped:0x80700020
void fn_3_C0F8C(void) {
    GXInitTexObj(&chargeTexObj, chargeTexData, 4, 4, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&chargeTexObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
}

// .text:0x000C0DD8 size:0x1B4 mapped:0x806FFE6C
void fn_3_C0DD8(void* model, GXTevStageID* stage, GXTexCoordID* coord, GXTexMapID* map, s8* nStages, s8* nCoords) {
    Mtx texMtx;
    int slot = findChargeSlot(fn_80011570(model)->animIndex);

    if (slot >= 0) {
        GXLoadTexObj(&chargeTexObj, *map);
        memset(texMtx, 0, sizeof(Mtx));
        texMtx[0][3] = 0.0f;
        texMtx[1][3] = slot;
        GXLoadTexMtxImm(texMtx, GX_TEXMTX0 + *map * 3, GX_MTX2x4);
        GXSetTexCoordGen2(*coord, GX_TG_MTX3X4, GX_TG_TEX0, GX_TEXMTX0 + *map * 3, GX_FALSE, GX_PTIDENTITY);
        GXSetTevOrder(*stage, *coord, *map, GX_COLOR0A0);
        GXSetTevColorIn(*stage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_TEXA, GX_CC_CPREV);
        GXSetTevColorOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(*stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
        GXSetTevAlphaOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        (*stage)++;
        (*map)++;
        (*nCoords)++;
        (*nStages)++;
    }
}

// Writes one colour into the 4x4 RGBA8 glow texture: the AR half lives at
// +0x00 and the GB half at +0x20 of the tile.
// .text:0x000C0D10 size:0xC8 mapped:0x806FFDA4
void fn_3_C0D10(int row, u8 r, u8 g, u8 b, u8 a) {
    int i = row * 16;

    chargeTexData[i] = a;
    chargeTexData[i + 1] = r;
    *(u16*)&chargeTexData[i + 2] = *(u16*)&chargeTexData[i];
    *(u32*)&chargeTexData[i + 4] = *(u32*)&chargeTexData[i];
    memcpy(&chargeTexData[i + 8], &chargeTexData[i], 8);
    {
        int j = i + 0x20;
        chargeTexData[j] = g;
        chargeTexData[j + 1] = b;
        *(u16*)&chargeTexData[i + 0x22] = *(u16*)&chargeTexData[j];
        *(u32*)&chargeTexData[i + 0x24] = *(u32*)&chargeTexData[j];
        memcpy(&chargeTexData[i + 0x28], &chargeTexData[j], 8);
    }
    DCStoreRange(chargeTexData, sizeof(chargeTexData));
}

// .text:0x000C0CE8 size:0x28 mapped:0x806FFD7C
void fn_3_C0CE8(int pitch, f32 x, f32 y, f32 z) {
    lbl_3_common_bss_35154.starHitPos.x = x;
    lbl_3_common_bss_35154.starHitPos.y = y;
    lbl_3_common_bss_35154.starHitPos.z = z;
    lbl_3_common_bss_35154.starHitPitch = pitch;
    lbl_3_common_bss_35154.flags |= 0x100;
}

// .text:0x000C0C4C size:0x9C mapped:0x806FFCE0
void fn_3_C0C4C(int slot) {
    ChargeGlowNode* node = (ChargeGlowNode*)insertGraphicDrawingFunction(fn_3_C0AD8, 1);

    node->frame = 0;
    node->actorIndex = chargeSlots[slot].actorIndex;
    node->stop = FALSE;
    for (slot = 0; slot < 2; slot++) {
        if (chargeDrawItems[slot] == NULL) {
            chargeDrawItems[slot] = node;
            node->slot = slot;
            return;
        }
    }
}

// .text:0x000C0AD8 size:0x174 mapped:0x806FFB6C
void fn_3_C0AD8(void) {
    ChargeGlowNode* node = (ChargeGlowNode*)currentDrawingItem;
    ChargeAnimActor* actor = ((ChargeAnimActor**)(hugeAnimStruct + 0x2C50))[node->actorIndex];

    if (node->stop == FALSE && actor != NULL) {
        fn_800A7D4C(0, &chargeGlowEntries[node->slot][drawStadiumRelated]);
        chargeGlowEntries[node->slot][drawStadiumRelated].frame = node->frame;
        chargeGlowEntries[node->slot][drawStadiumRelated].pos.x = actor->pos.x;
        chargeGlowEntries[node->slot][drawStadiumRelated].pos.y = actor->pos.y;
        chargeGlowEntries[node->slot][drawStadiumRelated].pos.z = actor->pos.z;
        if (lbl_80366158._28 == 0) {
            node->frame++;
        }
    } else {
        chargeDrawItems[node->slot] = NULL;
        removeCurrentDrawingItem();
    }
    if (node->frame >= lbl_3_common_bss_35154.glowFrames) {
        chargeDrawItems[node->slot] = NULL;
        removeCurrentDrawingItem();
    }
}

// .text:0x000C095C size:0x17C mapped:0x806FF9F0
void fn_3_C095C(ChargeGlowEntry* entry) {
    ChargeAnimState* states[2];
    void* handles[2];
    StadiumModel* model = (StadiumModel*)(lbl_3_common_bss_35154.glowOwner + 0x34);
    Mtx mtx;
    int i;

    states[0] = &lbl_3_common_bss_35154.glowStateA;
    states[1] = &lbl_3_common_bss_35154.glowStateB;
    handles[0] = lbl_3_common_bss_35154.glowHandleA;
    handles[1] = lbl_3_common_bss_35154.glowHandleB;

    PSMTXTrans(mtx, entry->pos.x, entry->pos.y, entry->pos.z);
    PSMTXConcat(returnFloatFromModeIndex(returnsCurrentMode())->view, mtx, mtx);
    i = 2;
    while (i-- != 0) {
        states[i]->unk0 = 0.0f;
        states[i]->unkC = 0;
        states[i]->frame = entry->frame;
        fn_80024DB0((u8*)states[i]);
        fn_80024FA4(model, handles[i], (u8*)states[i], -1);
    }
    ((u8*)model->root)[0x99] = 1;
    setActorAnimFrame(model->root, entry->frame);
    fn_800B4C04(model->root, 1.0f);
    fn_800BDA24(model);
    model->root->drawFlags = 0xFF;
    sknRelated(model, mtx);
}

// .text:0x000C0854 size:0x108 mapped:0x806FF8E8
void fn_3_C0854(void) {
    int i;
    for (i = 0; i < 2; i++) {
        if (chargeDrawItems[i] != NULL) {
            chargeDrawItems[i]->stop = TRUE;
        }
        if (chargeSlots[i].actorIndex >= 0) {
            int slot = findChargeSlot(chargeSlots[i].actorIndex);
            if (slot >= 0) {
                releaseChargeSlot(chargeSlots[i].actorIndex, slot);
            }
        }
    }
}

