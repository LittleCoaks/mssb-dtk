#define SQRT2_LINKAGE static
#include "game/animation/actor_transform.h"
#define REP_HEADER_DATA_FN getRepHeaderData_actorTransform
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/stadium/stadium_framework.h"
#include "C3/actor.h"
#include "Dolphin/mtx.h"
#include "stl/mem.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x8005268c.h"
#include "Unknown/File_0x80052734.h"
#include "Unknown/File_0x800b4bc8.h"
#include "Unknown/File_0x800bda94.h"

// One effect slot of the shared effects block (lbl_3_common_bss_35154), 0x5C bytes each.
typedef struct _ActorFxSlot {
    /*0x00*/ f32 unk0;
    /*0x04*/ f32 frame;
    /*0x08*/ u8 _08[4];
    /*0x0C*/ s16 unkC;
    /*0x0E*/ u8 _0E[0x18 - 0xE];
    /*0x18*/ u16 frames;
    /*0x1A*/ u8 _1A[0x20 - 0x1A];
    /*0x20*/ void* handle;
    /*0x24*/ u8 _24[0x5C - 0x24];
} ActorFxSlot;

typedef struct _ActorFxBlock {
    /*0x000*/ u8 _000[0x10];
    /*0x010*/ u8* models;
    /*0x014*/ u8 _014[0x20 - 0x14];
    /*0x020*/ ActorFxSlot slots[12];
    /*0x470*/ u8 _470[0x479 - 0x470];
    /*0x479*/ u8 _479;
    /*0x47A*/ u8 _47A[0x480 - 0x47A];
} ActorFxBlock;

// A drawing entry of the lbl_3_data_285A8 table, 0x20 bytes.
typedef struct _ActorTransformEntry {
    /*0x00*/ u32 _00;
    /*0x04*/ void (*draw)(struct _ActorTransformEntry* entry);
    /*0x08*/ VecXYZ pos;
    /*0x14*/ f32 scale;
    /*0x18*/ u32 frame;
    /*0x1C*/ u8 modelIndex;
    /*0x1D*/ u8 offsetIndex;
    /*0x1E*/ u8 slotA;
    /*0x1F*/ u8 slotB;
} ActorTransformEntry;

// DrawingSceneStruct view: +0x14.. is scratch owned by the transform draw functions.
typedef struct _ActorTransformNode {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ VecXYZ pos;
    /*0x20*/ f32 scale;
    /*0x24*/ u16 frame;
    /*0x26*/ s16 arg;
    /*0x28*/ u8 modelIndex;
    /*0x29*/ u8 slot;
    /*0x2A*/ u8 offsetIndex;
    /*0x2B*/ u8 slotA;
    /*0x2C*/ u8 slotB;
} ActorTransformNode;

// The actor's child list; each child carries a world matrix at +0xEC.
typedef struct _ActorTransformChild {
    /*0x00*/ u8 _00[0xEC];
    /*0xEC*/ MtxPtr worldMtx;
} ActorTransformChild;

typedef struct _ActorTransformActorList {
    /*0x00*/ u8 _00[6];
    /*0x06*/ u16 count;
    /*0x08*/ u8 _08[0x10];
    /*0x18*/ ActorTransformChild** children;
} ActorTransformActorList;

typedef struct _ActorTransformActor {
    /*0x000*/ u8 _000[0x252];
    /*0x252*/ s8 charId;
    /*0x253*/ u8 _253;
    /*0x254*/ s8 animIndex;
} ActorTransformActor;

typedef struct _ActorTransformModel {
    /*0x00*/ ActorTransformActorList* root;
    /*0x04*/ void* animBank;
    /*0x08*/ u8 _08[0xE - 0x8];
    /*0x0E*/ u16 sequenceNum;
    /*0x10*/ u8 _10[0x60 - 0x10];
    /*0x60*/ f32 animTime;
} ActorTransformModel;

extern ActorFxBlock lbl_3_common_bss_35154;
// Per-character vertical offset of the effect, in 1/100000 units.
static s32 lbl_3_data_285A8[NUM_CHOOSABLE_CHARACTERS] = {
    -250000, -250000, -250000, -200000, -200000, -200000,
    -250000, -240000, -240000, -250000, -200000, -150000,
    -200000, -200000, -250000, -350000, -200000, -250000,
    -200000, -200000, -250000, -200000, -200000, -200000,
    -180000, -180000, -180000, -250000, -200000, -200000,
    -200000, -200000, -200000, -250000, -250000, -250000,
    -250000, -180000, -280000, -200000, -200000, -200000,
    -250000, -250000, -200000, -200000, -200000, -200000,
    -250000, -250000, -250000, -250000, -250000, -250000,
};

static s32 lbl_3_data_28680[18] = {
    0, 50000, 0,
    0, 50000, 0,
    0, 50000, 0,
    0, 0, 0,
    0, 300000, 100000, 300000, 100000, 300000,
};

#define E_ { 0, mUpdateActorTransformAndAnimation }
static ActorTransformEntry lbl_3_data_286C8[9][2] = {
    { E_, E_ }, { E_, E_ }, { E_, E_ }, { E_, E_ }, { E_, E_ },
    { E_, E_ }, { E_, E_ }, { E_, E_ }, { E_, E_ },
};
#undef E_

// Per-slot "already queued this frame" flags, cleared once per frame by fn_3_1690C0.
static E(u8, BOOL) lbl_3_data_28908[9] = { FALSE };
static u8 lbl_3_data_28914[10] = { 0 };
static u16 lbl_3_data_2891E = 9;
static u16 lbl_3_data_28920 = 9;
static u16 lbl_3_data_28922 = 9;

extern struct {
    /*0x0000*/ u8 _0000[0x2C50];
    /*0x2C50*/ ActorTransformActor* actors[(0x3154 - 0x2C50) / 4];
} hugeAnimStruct;
extern u8 drawStadiumRelated;
extern struct {
    u8 _00[0x28];
    u8 _28;
} lbl_80366158;

extern void fn_800A7D4C(s32 arg0, void* arg1);
extern void fn_800BDA24(void* arg);

// .text:0x00169150 size:0x2C
void fn_3_169150(void) {
    insertGraphicDrawingFunction(fn_3_1690C0, 0);
}

// .text:0x001690C0 size:0x90
void fn_3_1690C0(void) {
    int i;

    memset(lbl_3_data_28908, 0, sizeof(lbl_3_data_28908));
    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154._479 != 0) {
        removeCurrentDrawingItem();
    } else {
        u8* flags = &lbl_3_data_28914[8];
        i = 8;
        do {
            *flags &= 0xFD;
            flags--;
        } while (i-- != 0);
        removeCurrentDrawingItem();
    }
}

// .text:0x00168FA0 size:0x120 mapped:0x807A8034
void displayChem_antiChemGraphics(int fielder, BOOL anti) {
    ActorTransformNode* node;

    if (hugeAnimStruct.actors[fielder] != NULL) {
        node = (ActorTransformNode*)insertGraphicDrawingFunction(fn_3_168DFC, (u16)(currentDrawingItem->priority + 1));
        node->slot = fielder;
        node->frame = 0;
        node->scale = lbl_3_data_28680[13] / 100000.0f;
        getAnimRelatedCoordinates(fielder, lbl_3_data_2891E, &node->pos);
        if (anti) {
            node->offsetIndex = 1;
            node->modelIndex = 3;
            node->slotA = 6;
        } else {
            node->offsetIndex = 0;
            node->modelIndex = 2;
            node->slotA = 5;
        }
    }
}

// .text:0x00168DFC size:0x1A4 mapped:0x807A7E90
void fn_3_168DFC(void) {
    ActorTransformNode* node = (ActorTransformNode*)currentDrawingItem;
    ActorTransformEntry* entry;
    ActorTransformActor* actor;

    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154._479 != 0) {
        removeCurrentDrawingItem();
    } else if (lbl_3_data_28908[node->slot] != 0) {
        removeCurrentDrawingItem();
    } else {
        lbl_3_data_28908[node->slot] = TRUE;
        actor = hugeAnimStruct.actors[node->slot];
        entry = &lbl_3_data_286C8[node->slot][drawStadiumRelated];
        entry->draw = mUpdateActorTransformAndAnimation;
        entry->frame = node->frame;
        entry->pos.x = node->pos.x;
        entry->pos.y = node->pos.y + lbl_3_data_285A8[actor->charId] / 100000.0f;
        entry->pos.z = node->pos.z;
        entry->scale = node->scale;
        entry->modelIndex = node->modelIndex;
        entry->slotA = node->slotA;
        entry->offsetIndex = node->offsetIndex;
        if (lbl_80366158._28 == 0) {
            node->frame++;
        }
        fn_800A7D4C(0, entry);
        if (node->frame >= lbl_3_common_bss_35154.slots[node->slotA].frames) {
            removeCurrentDrawingItem();
        }
    }
}

// .text:0x00168CD8 size:0x124 mapped:0x807A7D6C
void fn_3_168CD8(ActorTransformActor* actor, f32 value) {
    ActorTransformNode* node;
    int animIndex = actor->animIndex;

    if (value == lbl_3_data_28680[14] / 100000.0f && actor != NULL) {
        node = (ActorTransformNode*)insertGraphicDrawingFunction(fn_3_168DFC, (u16)(currentDrawingItem->priority + 1));
        node->slot = animIndex;
        node->frame = 0;
        node->scale = lbl_3_data_28680[15] / 100000.0f;
        getAnimRelatedCoordinates(animIndex, lbl_3_data_28920, &node->pos);
        node->offsetIndex = 2;
        node->modelIndex = 4;
        node->slotA = 7;
    }
}

// .text:0x00168A6C size:0x26C mapped:0x807A7B00
void mUpdateActorTransformAndAnimation(ActorTransformEntry* entry) {
    void* handle;
    ActorFxSlot* slot;
    ActorTransformModel* model;
    MtxPtr view;
    Mtx mtx;
    Mtx rot;

    model = (ActorTransformModel*)(lbl_3_common_bss_35154.models + entry->modelIndex * 0x90 + 0x34);
    slot = &lbl_3_common_bss_35154.slots[entry->slotA];
    handle = lbl_3_common_bss_35154.slots[entry->slotA].handle;
    view = returnFloatFromModeIndex(returnsCurrentMode())->view;
    PSMTXTrans(mtx,
               lbl_3_data_28680[entry->offsetIndex * 3 + 1] / 100000.0f,
               lbl_3_data_28680[entry->offsetIndex * 3 + 2] / 100000.0f,
               lbl_3_data_28680[entry->offsetIndex * 3 + 3] / 100000.0f);
    PSMTXInverse(view, rot);
    rot[2][3] = 0.0f;
    rot[1][3] = 0.0f;
    rot[0][3] = 0.0f;
    PSMTXConcat(rot, mtx, mtx);
    PSMTXScaleApply(mtx, mtx, entry->scale, entry->scale, entry->scale);
    PSMTXRotRad(rot, 'Y', 3.1415927f);
    PSMTXConcat(rot, mtx, mtx);
    PSMTXTransApply(mtx, mtx, entry->pos.x, entry->pos.y, entry->pos.z);
    PSMTXConcat(view, mtx, mtx);
    slot->unk0 = 0.0f;
    slot->unkC = 0;
    slot->frame = entry->frame;
    fn_80024DB0((u8*)slot);
    fn_80024FA4((StadiumModel*)model, handle, (u8*)slot, -1);
    ((u8*)model->root)[0x99] = 1;
    ACTSetAnimation((Actor*)model->root, model->animBank, NULL, model->sequenceNum, 0.0f, model->animTime);
    setActorAnimFrame(model->root, entry->frame);
    fn_800B4C04(model->root, 1.0f);
    fn_800BDA24(model);
    ((u8*)model->root)[0x98] = 0xFF;
    sknRelated(model, mtx);
}

// .text:0x0016892C size:0x140 mapped:0x807A79C0
void fn_3_16892C(ActorTransformActor* actor, f32 value, s16 arg) {
    ActorTransformNode* node;
    int animIndex = actor->animIndex;

    if (value == lbl_3_data_28680[16] / 100000.0f) {
        if ((lbl_3_data_28914[animIndex] & 1) == 0) {
            lbl_3_data_28914[animIndex] |= 1;
            if (actor != NULL) {
                node = (ActorTransformNode*)insertGraphicDrawingFunction(fn_3_168704, (u16)(currentDrawingItem->priority + 1));
                node->slot = animIndex;
                node->frame = 0;
                node->scale = lbl_3_data_28680[17] / 100000.0f;
                node->arg = arg;
                node->offsetIndex = 3;
                node->modelIndex = 5;
                node->slotA = 8;
                node->slotB = 9;
            }
        }
    }
    lbl_3_data_28914[animIndex] |= 2;
}

// .text:0x00168704 size:0x228 mapped:0x807A7798
void fn_3_168704(void) {
    ActorTransformNode* node = (ActorTransformNode*)currentDrawingItem;
    ActorTransformEntry* entry;
    ActorTransformActor* actor;

    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154._479 != 0) {
        removeCurrentDrawingItem();
    } else if (lbl_3_data_28908[node->slot] != 0) {
        if (lbl_80366158._28 != 0) {
            lbl_3_data_28914[node->slot] &= ~1;
        }
        removeCurrentDrawingItem();
    } else if ((lbl_3_data_28914[node->slot] & 2) == 0) {
        lbl_3_data_28914[node->slot] &= ~1;
        removeCurrentDrawingItem();
    } else {
        lbl_3_data_28908[node->slot] = TRUE;
        actor = hugeAnimStruct.actors[node->slot];
        entry = &lbl_3_data_286C8[node->slot][drawStadiumRelated];
        entry->draw = fn_3_168414;
        entry->frame = node->frame;
        getAnimRelatedCoordinates(node->slot, lbl_3_data_28922, &entry->pos);
        entry->pos.y += lbl_3_data_285A8[actor->charId] / 100000.0f;
        entry->scale = lbl_3_data_28680[13] / 100000.0f;
        entry->modelIndex = node->modelIndex;
        entry->slotA = node->slotA;
        entry->slotB = node->slotB;
        entry->offsetIndex = node->offsetIndex;
        if (lbl_80366158._28 == 0) {
            node->frame++;
        }
        fn_800A7D4C(0, entry);
        node->frame = node->frame % 60;
    }
}

// .text:0x00168414 size:0x2F0 mapped:0x807A74A8
void fn_3_168414(ActorTransformEntry* entry) {
    ActorTransformChild* child;
    void* handles[2];
    ActorFxSlot* slots[2];
    Mtx mtx;
    Mtx inv;
    ActorTransformModel* model;
    MtxPtr view;
    int i;

    model = (ActorTransformModel*)(lbl_3_common_bss_35154.models + entry->modelIndex * 0x90 + 0x34);
    slots[0] = &lbl_3_common_bss_35154.slots[entry->slotA];
    slots[1] = &lbl_3_common_bss_35154.slots[entry->slotB];
    handles[0] = lbl_3_common_bss_35154.slots[entry->slotA].handle;
    handles[1] = lbl_3_common_bss_35154.slots[entry->slotB].handle;

    view = returnFloatFromModeIndex(returnsCurrentMode())->view;
    PSMTXTrans(mtx,
               lbl_3_data_28680[entry->offsetIndex * 3 + 1] / 100000.0f,
               lbl_3_data_28680[entry->offsetIndex * 3 + 2] / 100000.0f,
               lbl_3_data_28680[entry->offsetIndex * 3 + 3] / 100000.0f);
    PSMTXScaleApply(mtx, mtx, entry->scale, entry->scale, entry->scale);
    PSMTXTransApply(mtx, mtx, entry->pos.x, entry->pos.y, entry->pos.z);
    PSMTXConcat(view, mtx, mtx);

    for (i = 0; i < 2; i++) {
        slots[i]->unk0 = 0.0f;
        slots[i]->unkC = 0;
        slots[i]->frame = entry->frame;
        fn_80024DB0((u8*)slots[i]);
        fn_80024FA4((StadiumModel*)model, handles[i], (u8*)slots[i], -1);
    }

    ((u8*)model->root)[0x99] = 1;
    ACTSetAnimation((Actor*)model->root, model->animBank, NULL, model->sequenceNum, 0.0f, model->animTime);
    setActorAnimFrame(model->root, entry->frame + 15);
    fn_800B4C04(model->root, 1.0f);
    fn_800BDA24(model);

    for (i = 0; i < model->root->count; i++) {
        switch (i) {
        case 1:
        case 2:
        case 3:
        case 4:
            child = model->root->children[i];
            PSMTXConcat(view, child->worldMtx, inv);
            PSMTXInverse(inv, inv);
            inv[2][3] = 0.0f;
            inv[1][3] = 0.0f;
            inv[0][3] = 0.0f;
            PSMTXConcat(child->worldMtx, inv, child->worldMtx);
            break;
        }
    }

    ((u8*)model->root)[0x98] = 0xFF;
    sknRelated(model, mtx);
}
