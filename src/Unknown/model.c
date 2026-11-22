#include "Unknown/File_0x800127f8.h"
#include "Dolphin/os.h"
#include "C3/actor/act.h"
#include "C3/geoPalette/geoPalette.h"
#include "Unknown/File_0x80021ca4.h"
#include "Unknown/File_0x80024d2c.h"
#include "Unknown/File_0x800a7568.h"
#include "Unknown/File_0x80013680.h"
#include "Unknown/File_0x80014d4c.h"
#include "Unknown/dvdsys.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x80014e50.h"
#include "Unknown/File_0x80014f40.h"
#include "Unknown/File_0x8001594c.h"
#include "game/UnknownHomes_Game.h"
#include "Unknown/File_0x80018024.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/File_0x80018270.h"
#include "Unknown/File_0x8001a6b0.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x800bde8c.h"
#include "Unknown/File_0x8003a538.h"
#include "Unknown/File_0x8001f4c0.h"
#include "Unknown/File_0x8001b2d0.h"
#include "PowerPC_EABI_Support/Runtime/__mem.h"
#include "Unknown/File_0x8001b728.h"
#include "Unknown/File_0x8001b80c.h"
#include "Unknown/File_0x800bdd74.h"
#include "Unknown/File_0x8001b918.h"
#include "Unknown/File_0x8001c588.h"
#include "C3/anim.h"
#include "Unknown/File_0x8001c67c.h"
#include "C3/actor.h"
#include "Unknown/File_0x8001c920.h"
#include <stdarg.h>
#include "Unknown/File_0x8001cbd4.h"
#include "Unknown/File_0x80023b90.h"
#include "Unknown/File_0x8001ce74.h"
#include "Dolphin/mtx.h"
#include "Dolphin/vec.h"
#include "C3/light/light.h"
#include "Unknown/File_0x800bd478.h"
#include "Unknown/File_0x8001d0d0.h"
#include "C3/control.h"
#include "Unknown/File_0x8001d110.h"
#include "Unknown/File_0x8001d148.h"
#include "Unknown/File_0x8001d180.h"
#include "C3/skinning.h"
#include "Unknown/File_0x8001e460.h"
#include "Unknown/File_0x8001f228.h"
#include "Unknown/File_0x8001f5e8.h"
#include "Unknown/File_0x800bdc88.h"
#include "Unknown/File_0x800c0770.h"
#include "game/minigame/minigame_models.h"
#include "Unknown/File_0x8001fc4c.h"
#include "game/match_setup/match_loading.h"
#include "Unknown/File_0x8004b7f4.h"

typedef struct _StadiumLightInput {
    Vec pos;
    GXColor color;
} StadiumLightInput;

typedef struct _StadiumLightParams {
    u8 lights[4][10];
    GXColor ambient;
} StadiumLightParams;

extern u8 highLevelSimulationFlag[4];
struct HandModelEntry;

/* The one declaration of the animation/model state block; each former unit's
 * narrower view of it is a typedef plus a #define over this object. */
typedef struct HugeAnimStruct {
    /* 0x0000 */ u8 _0000[0x60];
    /* 0x0060 */ ActorObjectTable* actorTable;
    /* 0x0064 */ u8 _0064[0x13C - 0x64];
    /* 0x013C */ struct HandModelEntry* modelEntries;
    /* 0x0140 */ u8 _0140[0x2C50 - 0x140];
    /* 0x2C50 */ void* objects[(0x3154 - 0x2C50) / 4];
} HugeAnimStruct;
extern HugeAnimStruct hugeAnimStruct;
extern StadiumLightParams inputParams[14];
extern s16 lbl_800EEAAC[0x36];
extern StadiumLightInput lbl_80367318[4];
extern u8 lbl_803716B8[0x578];
extern void* lbl_803CB790;
extern u8 lbl_803CB7C4[4];

/* initShortsHandleCompressedDiskReads addresses its tables as offsets from the
 * start of this unit's .data, which begins at lbl_800EE800, so the objects ahead
 * of the swap tables are defined first, before any function's jump table. */

u8 lbl_800EE800[0x110] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

MatchFileDescriptor BallModelFiles[2] = {
    { 0x0000040B, 0x40093FF8, 0x0E581000, 0x0005F484 },
    { 0x0000040B, 0x40095BB8, 0x0E5E0800, 0x0006053C },
};

MatchFileDescriptor MinigameCommonFiles[3] = {
    { 0x0000040B, 0x40001640, 0x08EB4800, 0x00000C38 },
    { 0x0000040B, 0x400B2D00, 0x08EB5800, 0x0006A948 },
    { 0x00000000, 0x00000686, 0x08F20800, 0x00000688 },
};

static u16 lbl_800EE960[][2] = {
    {0x16, 0x10}, {0x17, 0x11}, {0x18, 0x12}, {0x19, 0x13}, {0x1A, 0x14},
    {0x1B, 0x15}, {0x20, 0x1C}, {0x21, 0x1D}, {0x22, 0x1E}, {0x23, 0x1F},
    {0x26, 0x25}, {0x28, 0x27}, {0x3D, 0x3C}, {SHORT_TABLE_END, 0},
};

static u16 lbl_800EE998[][2] = {
    {0x2F, 0x34}, {0x30, 0x35}, {0x31, 0x36}, {0x32, 0x37}, {0x33, 0x38},
    {SHORT_TABLE_END, 0},
};

static u16 lbl_800EE9B0[][2] = {
    {0x41, 0x47}, {0x42, 0x48}, {0x43, 0x49}, {0x44, 0x4A}, {0x45, 0x4B},
    {0x46, 0x4C}, {SHORT_TABLE_END, 0},
};

static u16 lbl_803CB798[][2] = {
    {0x4A, 0x4B}, {SHORT_TABLE_END, 0},
};

static u16 lbl_803CB7A0[][2] = {
    {0x2F, 0x34}, {SHORT_TABLE_END, 0},
};

#define MODEL_ENTRY_SIZE 0x90
#define NO_BONE          0xFFFF

typedef struct ModelSlotBlock {
    /* 0x00 */ void** loaded; // relocated part table: four offsets at [0..3]
    /* 0x04 */ void* _04;
    /* 0x08 */ u8 _08[0x60 - 0x08];
    /* 0x60 */ u8 slot;
    /* 0x61 */ u8 _61[0x64 - 0x61];
} ModelSlotBlock;

typedef struct ModelOwner {
    /* 0x00 */ ModelSlotBlock blocks[2];
    /* 0xC8 */ void* texPalette;
    /* 0xCC */ u8 _CC[0xCD - 0xCC];
    /* 0xCD */ u8 flag;
    /* 0xCE */ u8 _CE[0xCF - 0xCE];
    /* 0xCF */ E(s8, CHAR_ID) charId;
} ModelOwner;

typedef struct ModelLinkNode {
    /* 0x00 */ u8 _00[0x14];
    /* 0x14 */ void* link;
} ModelLinkNode;

typedef struct ModelPartList {
    /* 0x00 */ u8 _00[0x06];
    /* 0x06 */ u16 count;
    /* 0x08 */ u8 _08[0x18 - 0x08];
    /* 0x18 */ ModelLinkNode** nodes;
} ModelPartList;

typedef struct ModelEntry {
    /* 0x00 */ u8 _00[0x34];
    /* 0x34 */ ModelPartList* parts;
    /* 0x38 */ u8 _38[MODEL_ENTRY_SIZE - 0x38];
} ModelEntry;

typedef struct ModelActor {
    /* 0x00 */ u8 _00[0x18];
    /* 0x18 */ ModelLinkNode** nodes;
} ModelActor;

typedef struct ModelObject {
    /* 0x000 */ void* actors[1];
    /* 0x004 */ u8 _004[0x30 - 0x04];
    /* 0x030 */ ModelOwner* owner;
    /* 0x034 */ u8 _034[0x162 - 0x34];
    /* 0x162 */ u16 partBones[(0x252 - 0x162) / 2];
    /* 0x252 */ E(s8, CHAR_ID) charId;
    /* 0x253 */ u8 _253[0x254 - 0x253];
    /* 0x254 */ s8 slot;
} ModelObject;

typedef struct {
    /* 0x0000 */ u8 _0000[0x13C];
    /* 0x013C */ ModelEntry* entries;
    /* 0x0140 */ u8 _0140[0x2C50 - 0x140];
    /* 0x2C50 */ ModelObject* objects[(0x3154 - 0x2C50) / 4];
} hugeAnimStruct_view_800127f8;
#define hugeAnimStruct (*(hugeAnimStruct_view_800127f8*)&hugeAnimStruct)

typedef struct {
    /* 0x000 */ u8 _000[0x1E8];
    /* 0x1E8 */ u8 unk1E8;
    /* 0x1E9 */ u8 _1E9[0x578 - 0x1E9];
} lbl_803716B8_view_800127f8;
#define lbl_803716B8 (*(lbl_803716B8_view_800127f8*)&lbl_803716B8)

typedef u8 lbl_803CB7C4_view_800127f8[];
#define lbl_803CB7C4 (*(lbl_803CB7C4_view_800127f8*)&lbl_803CB7C4)
typedef u16 lbl_800EEAAC_view_800127f8[];
#define lbl_800EEAAC (*(lbl_800EEAAC_view_800127f8*)&lbl_800EEAAC)
extern u8 handAttachBoneIDs[8];

extern void fn_800238E0(void* entries, s32 slot, s32 slot2, void* layout);

ModelSlotBlock* lbl_803CBC10;
u8 lbl_803CBC14;
u8 lbl_803CBC15;

BOOL LoadModel(void* objPtr) {
    ModelObject* obj = objPtr;
    ModelOwner* owner;
    ModelSlotBlock* block;
    void** loaded;
    void* layout;
    void* geo;
    void* texPalette;
    void* partSlot;
    s32 slot;
    s32 flag;
    u16 bone;
    s32 n;
    s32 i;
    void** cursor;
    ModelActor* actor;
    ModelLinkNode* node;
    ModelPartList* parts;
    ModelLinkNode** partNodes;
    ModelObject* hugeObj;

    if (obj == NULL) {
        OSPanic("model.c", 0x22E6, " Character Data None \n");
        return FALSE;
    }
    if (obj->owner == NULL) {
        OSPanic("model.c", 0x22EA, " Character Parts Data None \n");
        return FALSE;
    }

    if (lbl_803CBC14 == 0 && lbl_803C6CF8.cancel.bytes[1] == 1) {
        owner = obj->owner;
        if (owner->flag != 0) {
            lbl_803CBC10 = &owner->blocks[1];
            loadCharacterHandItem(owner->charId, 5, owner->blocks[1].loaded);
            lbl_803CBC15 = 1;
        } else {
            lbl_803CBC10 = &owner->blocks[0];
            loadCharacterHandItem(owner->charId, 0, owner->blocks[0].loaded);
            lbl_803CBC15 = 0;
        }
        lbl_803CBC14 = 1;
    }

    if (lbl_803716B8.unk1E8 != 0) {
        return FALSE;
    }

    block = lbl_803CBC10;
    owner = obj->owner;
    texPalette = owner->texPalette;
    loaded = block->loaded;

    for (i = 0; i < 4; i++) {
        if (loaded[i] != NULL) {
            loaded[i] = (void*)((u8*)loaded + (u32)loaded[i]);
        }
    }

    slot = block->slot;
    layout = loaded[lbl_803CB7C4[0]];
    geo = loaded[lbl_803CB7C4[1]];
    partSlot = &hugeAnimStruct.entries[slot].parts;

    LoadActorLayout(layout);
    convertGeometryAndSknHeader(geo, NULL);
    haveActLayoutPointToGeoHeader(layout, geo);
    UpdateTexturePalettePointers(geo, texPalette);
    fn_800238E0(hugeAnimStruct.entries, slot, slot, layout);

    if (loaded[2] != NULL) {
        adjustInternalPointers(loaded[lbl_803CB7C4[2]]);
        ACTActorRelated(loaded[lbl_803CB7C4[2]], partSlot);
    }

    block->_04 = loaded[lbl_803CB7C4[3]];
    actRelated(loaded[lbl_803CB7C4[2]], &block->_04);

    flag = lbl_803CBC15;
    hugeObj = hugeAnimStruct.objects[obj->slot];
    if (hugeObj != NULL) {
        bone = hugeObj->partBones[handAttachBoneIDs[flag]];
    } else {
        bone = NO_BONE;
    }

    if (bone != NO_BONE) {
        owner = hugeObj->owner;
        n = (s16)lbl_800EEAAC[hugeObj->charId];
        cursor = hugeObj->actors;
        i = 0;
        if (n >= 0 && owner != NULL) {
            actor = (ModelActor*)cursor[0];
            partNodes = actor->nodes;
            node = (ModelLinkNode*)partNodes[bone];
            if (flag & 1) {
                parts = hugeAnimStruct.entries[owner->blocks[1].slot].parts;
            } else {
                parts = hugeAnimStruct.entries[owner->blocks[0].slot].parts;
            }
            if (parts != NULL) {
                for (i = parts->count; i != 0; i--) {
                    ModelLinkNode* cand = parts->nodes[i - 1];
                    if (cand->link != NULL) {
                        node->link = cand->link;
                        break;
                    }
                }
            }
        }
    }

    lbl_803CBC14 = 0;
    lbl_803CBC10 = NULL;
    return TRUE;
}

#undef MODEL_ENTRY_SIZE
#undef NO_BONE
#undef hugeAnimStruct
#undef lbl_800EEAAC
#undef lbl_803716B8
#undef lbl_803CB7C4

extern void fn_800238E0(void* entries, s32 slot, s32 slot2, void* layout);

extern u8 lbl_803CBBFB;
extern u8 lbl_803CBBFC;
extern u8 lbl_803CBBFD;
extern u32 lbl_803CBC00;
extern u8 lbl_803CBC0C;
extern u8* lbl_803CBC1C;
extern u8* lbl_803CBC20;

extern u8 handAttachBoneIDs[8];

typedef u8 hugeAnimStruct_view_80013680[0x3154];
#define hugeAnimStruct (*(hugeAnimStruct_view_80013680*)&hugeAnimStruct)


#define FIELD_U8(p, off) (*(u8*)((u8*)(p) + (off)))
#define FIELD_S8(p, off) (*(s8*)((u8*)(p) + (off)))
#define FIELD_U16(p, off) (*(u16*)((u8*)(p) + (off)))
#define FIELD_U32(p, off) (*(u32*)((u8*)(p) + (off)))
#define FIELD_PTR(p, off) (*(u8**)((u8*)(p) + (off)))

#define RECORD_COUNT 13
#define RECORD_STRIDE 0xD4
#define RECORD(i) (hugeAnimStruct + (i) * RECORD_STRIDE)
#define OBJECT_TABLE_OFFSET 0x2C50
#define ENTRY_TABLE_OFFSET 0x13C
#define ENTRY_STRIDE 0x90
#define NO_BONE 0xFFFF

static u8* getObject(s32 slot) {
    return ((u8**)(hugeAnimStruct + OBJECT_TABLE_OFFSET))[slot];
}

static u16 getHandAttachBone(u8* obj, s32 which) {
    if (obj == NULL) {
        return NO_BONE;
    }
    return FIELD_U16(obj, 0x162 + handAttachBoneIDs[which] * 2);
}

static void clearBoneSlot(u8* obj, u16 bone, s32 subIndexOffset) {
    s16 val = lbl_800EEAAC[FIELD_S8(obj, 0x252)];
    u8* sub;
    u8* list;
    u8* bonePtr;
    u8* entry;
    u8* data;
    u8* arr;
    u32 count;
    u32 i;

    if (val < 0) {
        return;
    }
    sub = FIELD_PTR(obj, 0x30);
    if (sub == NULL) {
        return;
    }
    list = FIELD_PTR(FIELD_PTR(obj, 0), 0x18);
    bonePtr = ((u8**)list)[bone];
    entry = FIELD_PTR(hugeAnimStruct, ENTRY_TABLE_OFFSET) + FIELD_U8(sub, subIndexOffset) * ENTRY_STRIDE;
    data = FIELD_PTR(entry, 0x34);
    if (data == NULL) {
        return;
    }
    count = FIELD_U16(data, 0x6);
    arr = FIELD_PTR(data, 0x18);
    for (i = count; i != 0; i--) {
        u8* item = ((u8**)arr)[i - 1];
        u32 v = FIELD_U32(item, 0x14);
        if (v != 0) {
            FIELD_U32(bonePtr, 0x14) = v;
            return;
        }
    }
}

static BOOL attachHandModelTail(void) {
    u8* p;
    u8* h;
    u8* table;
    u8* entry;
    u8* a;
    u8* b;
    u8* f;
    u32 off;
    s32 idx;

    if (FIELD_U8(lbl_803716B8, 0x1E8) != 0) {
        return FALSE;
    }
    p = lbl_803CBC1C;
    lbl_803CBC0C = 0;
    h = FIELD_PTR(p, 0);
    for (off = 0; off < 0x10; off += 4) {
        u32 v = FIELD_U32(h, off);
        if (v != 0) {
            FIELD_U32(h, off) = (u32)h + v;
        }
    }

    idx = FIELD_U8(p, 0x60);
    table = FIELD_PTR(hugeAnimStruct, ENTRY_TABLE_OFFSET);
    entry = table + idx * ENTRY_STRIDE;
    a = ((u8**)h)[lbl_803CB7C4[0]];
    b = ((u8**)h)[lbl_803CB7C4[1]];
    f = entry + 0x34;

    LoadActorLayout(a);
    convertGeometryAndSknHeader(b, NULL);
    haveActLayoutPointToGeoHeader(a, b);
    UpdateTexturePalettePointers((UnkTexPalGeo*)b, (void*)lbl_803CBC00);
    fn_800238E0(table, idx, idx, a);
    if (FIELD_PTR(h, 0x8) != NULL) {
        adjustInternalPointers(((u8**)h)[lbl_803CB7C4[2]]);
        ACTActorRelated(((u8**)h)[lbl_803CB7C4[2]], f);
    }
    FIELD_PTR(p, 0x4) = ((u8**)h)[lbl_803CB7C4[3]];
    actRelated(((u8**)h)[lbl_803CB7C4[2]], p + 0x4);
    lbl_803CBC1C = NULL;
    return TRUE;
}

BOOL animateModelArmsGlovesBats(void* actorPtr) {
    u8* actor = actorPtr;
    s8 charSlot = FIELD_S8(actor, 0x252);
    s8 part = FIELD_S8(actor, 0x254);
    BOOL lowPart;
    BOOL flagsMatch;
    BOOL placed;
    u8 sel;
    s32 i;
    s32 k;
    u8* rec;

    if (lbl_803CBBFB == 0) {
        lbl_803CBBFB = 1;
        lbl_803CBC00 = FIELD_U32(FIELD_PTR(actor, 0x8), 0);

        for (i = 0; i < RECORD_COUNT; i++) {
            rec = RECORD(i);
            if (FIELD_S8(rec, 0x20F) != charSlot) {
                continue;
            }
            if (FIELD_U8(rec, 0x20D) != FIELD_U8(actor, 0x25A)) {
                continue;
            }
            if (FIELD_U8(rec, 0x20E) != FIELD_U8(actor, 0x25B)) {
                continue;
            }
            if (FIELD_S8(rec, 0x210) != -1) {
                continue;
            }
            if (FIELD_U32(rec, 0x208) != lbl_803CBC00) {
                continue;
            }
            if ((part >= 9) != (FIELD_S8(rec, 0x211) >= 9)) {
                continue;
            }

            FIELD_U8(rec, 0x210) = (u8)part;
            FIELD_PTR(actor, 0x30) = rec + 0x140;
            FIELD_U8(FIELD_PTR(actor, 0x30), 0xCC) = TRUE;
            {
                u8* obj = getObject(part);
                u16 bone = getHandAttachBone(obj, 0);
                if (bone != NO_BONE) {
                    clearBoneSlot(obj, bone, 0x60);
                }
                obj = getObject(part);
                bone = getHandAttachBone(obj, 1);
                if (bone != NO_BONE) {
                    clearBoneSlot(obj, bone, 0xC4);
                }
            }
            lbl_803CBBFD = 0;
            lbl_803CBBFC = 0;
            lbl_803CBBFB = 0;
            lbl_803CBC00 = 0;
            return TRUE;
        }

        if (lbl_803CBBFC == 0 && lbl_803CBBFD == 0) {
            for (i = 0; i < RECORD_COUNT; i++) {
                rec = RECORD(i);
                if (FIELD_S8(rec, 0x210) == part && part < 9) {
                    FIELD_S8(rec, 0x210) = -1;
                    break;
                }
            }

            placed = FALSE;
            for (i = 0; i < RECORD_COUNT; i++) {
                rec = RECORD(i);
                if (FIELD_S8(rec, 0x210) == -1) {
                    lbl_803CBC20 = rec + 0x140;
                    FIELD_U32(rec, 0x208) = lbl_803CBC00;
                    FIELD_S8(rec, 0x20F) = charSlot;
                    FIELD_U8(rec, 0x211) = FIELD_U8(rec, 0x210);
                    FIELD_U8(rec, 0x210) = (u8)part;
                    FIELD_U8(rec, 0x20D) = FIELD_U8(actor, 0x25A);
                    FIELD_U8(rec, 0x20E) = FIELD_U8(actor, 0x25B);
                    placed = TRUE;
                    break;
                }
            }

            if (!placed) {
                for (i = 0; i < RECORD_COUNT; i++) {
                    u8* sub;
                    rec = RECORD(i);
                    sub = rec + 0x140;
                    lbl_803CBC20 = sub;
                    for (k = 0; k < RECORD_COUNT; k++) {
                        u8* obj = getObject(k);
                        if (obj == NULL) {
                            continue;
                        }
                        if (FIELD_S8(sub, 0xCF) == FIELD_S8(obj, 0x252)) {
                            break;
                        }
                    }
                    if (k == RECORD_COUNT) {
                        FIELD_U32(sub, 0xC8) = lbl_803CBC00;
                        FIELD_S8(rec, 0x20F) = charSlot;
                        FIELD_U8(rec, 0x211) = FIELD_U8(rec, 0x210);
                        FIELD_U8(rec, 0x210) = (u8)part;
                        FIELD_U8(rec, 0x20D) = FIELD_U8(actor, 0x25A);
                        FIELD_U8(rec, 0x20E) = FIELD_U8(actor, 0x25B);
                        break;
                    }
                }
            }
        }

        FIELD_U8(lbl_803CBC20, 0xC1) = 0;
        FIELD_U8(lbl_803CBC20, 0x5D) = 0;
    }

    if (lbl_803CBBFB == 0) {
        return FALSE;
    }

    lowPart = part < 9;
    sel = lowPart ? FIELD_U8(actor, 0x25A) : FIELD_U8(actor, 0x25B);
    flagsMatch = ((sel != 0) == lowPart);

    if (lbl_803CBBFC == 0) {
        if (lbl_803CBC0C == 0 && FIELD_U8(&lbl_803C6CF8, 0x715) == 1) {
            u8* sub = lbl_803CBC20;
            s32 r4;
            if (lowPart && FIELD_U8(sub, 0xCD) != 0) {
                r4 = 3;
            } else if (flagsMatch) {
                r4 = 5;
            } else {
                r4 = 1;
            }
            lbl_803CBC1C = sub + 0x64;
            lbl_803CBC0C = 1;
            loadCharacterHandItem(FIELD_S8(sub, 0xCF), r4, FIELD_PTR(sub, 0x64));
        }
        if (!attachHandModelTail()) {
            return FALSE;
        }
        lbl_803CBBFC = 1;
    }

    if (lbl_803CBBFD == 0) {
        if (lbl_803CBC0C == 0 && FIELD_U8(&lbl_803C6CF8, 0x715) == 1) {
            u8* sub = lbl_803CBC20;
            s32 r4;
            if (lowPart && FIELD_U8(sub, 0xCD) != 1) {
                r4 = 2;
            } else if (flagsMatch) {
                r4 = 4;
            } else {
                r4 = 0;
            }
            lbl_803CBC1C = sub;
            lbl_803CBC0C = 1;
            loadCharacterHandItem(FIELD_S8(sub, 0xCF), r4, FIELD_PTR(sub, 0x0));
        }
        if (!attachHandModelTail()) {
            return FALSE;
        }
        lbl_803CBBFD = 1;
    }

    if (lbl_803CBBFC == 0 || lbl_803CBBFD == 0) {
        return FALSE;
    }

    FIELD_PTR(actor, 0x30) = lbl_803CBC20;
    {
        u8* obj = getObject(part);
        u16 bone = getHandAttachBone(obj, 0);
        if (bone != NO_BONE) {
            clearBoneSlot(obj, bone, 0x60);
        }
        obj = getObject(part);
        bone = getHandAttachBone(obj, 1);
        if (bone != NO_BONE) {
            clearBoneSlot(obj, bone, 0xC4);
        }
    }
    FIELD_U8(FIELD_PTR(actor, 0x30), 0xCC) = TRUE;
    lbl_803CBC20 = NULL;
    lbl_803CBBFD = 0;
    lbl_803CBBFC = 0;
    lbl_803CBBFB = 0;
    lbl_803CBC00 = 0;
    return TRUE;
}

#undef ENTRY_STRIDE
#undef ENTRY_TABLE_OFFSET
#undef FIELD_PTR
#undef FIELD_S8
#undef FIELD_U16
#undef FIELD_U32
#undef FIELD_U8
#undef NO_BONE
#undef OBJECT_TABLE_OFFSET
#undef RECORD
#undef RECORD_COUNT
#undef RECORD_STRIDE
#undef hugeAnimStruct

typedef struct CompressedFileEntry {
    /*0x00*/ u8 _00[0x10];
} CompressedFileEntry;

typedef struct {
    /*0x0000*/ u8 _0000[0x2D48];
    /*0x2D48*/ s32 modelDest;
    /*0x2D4C*/ u8 _2D4C[0x2D50 - 0x2D4C];
    /*0x2D50*/ s16 modelIndex;
    /*0x2D52*/ u8 modelLoadState;
    /*0x2D53*/ u8 _2D53[0x3154 - 0x2D53];
} hugeAnimStruct_view_80014d4c;
#define hugeAnimStruct (*(hugeAnimStruct_view_80014d4c*)&hugeAnimStruct)

typedef CompressedFileEntry* lbl_803CB790_view_80014d4c;
#define lbl_803CB790 (*(lbl_803CB790_view_80014d4c*)&lbl_803CB790)

BOOL loadSomethingFromDiskAtBeginningOfAB1(int index) {
    if (index < 0) {
        return TRUE;
    }
    if (hugeAnimStruct.modelIndex == index) {
        return TRUE;
    }
    if (hugeAnimStruct.modelLoadState <= 1) {
        int file;

        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
            file = index * 0x13 + 10;
        } else {
            file = index * 0x13 + 2;
        }
        if (lbl_803C6CF8.cancel.bytes[1] != 1) {
            hugeAnimStruct.modelLoadState = 1;
            return FALSE;
        }
        ARAMTransfer(&lbl_803CB790[file], hugeAnimStruct.modelDest, 0, 0);
        hugeAnimStruct.modelLoadState = 2;
    } else if (lbl_803C6CF8.cancel.bytes[1] == 1) {
        hugeAnimStruct.modelIndex = index;
        hugeAnimStruct.modelLoadState = 0;
        return TRUE;
    }
    return FALSE;
}

#undef hugeAnimStruct
#undef lbl_803CB790

typedef struct {
    /*0x0000*/ u8 _0000[0x2D54];
    /*0x2D54*/ s32 fileDest;
    /*0x2D58*/ u8 _2D58[0x2D5C - 0x2D58];
    /*0x2D5C*/ u16 fileIndex;
    /*0x2D5E*/ u8 fileLoadState;
    /*0x2D5F*/ u8 _2D5F[0x3154 - 0x2D5F];
} hugeAnimStruct_view_80014e50;
#define hugeAnimStruct (*(hugeAnimStruct_view_80014e50*)&hugeAnimStruct)

typedef struct {
    /*0x000*/ u8 _000[0x1E8];
    /*0x1E8*/ u8 unk1E8;
    /*0x1E9*/ u8 _1E9[0x578 - 0x1E9];
} lbl_803716B8_view_80014e50;
#define lbl_803716B8 (*(lbl_803716B8_view_80014e50*)&lbl_803716B8)

typedef CompressedFileEntry* lbl_803CB790_view_80014e50;
#define lbl_803CB790 (*(lbl_803CB790_view_80014e50*)&lbl_803CB790)

void* fn_8002204C(int index, s32 dest);

BOOL loadSomethingFromDiskAtBeginningOfAB2(int index) {
    if (index < 0) {
        return TRUE;
    }
    if (hugeAnimStruct.fileLoadState <= 1) {
        int file = index * 0x13;

        if (lbl_803C6CF8.cancel.bytes[1] != 1) {
            hugeAnimStruct.fileLoadState = 1;
            return FALSE;
        }
        if (fn_8002204C(index, hugeAnimStruct.fileDest) == NULL) {
            ARAMTransfer(&lbl_803CB790[file], hugeAnimStruct.fileDest, 0, 0);
        }
        hugeAnimStruct.fileLoadState = 2;
    } else if (lbl_803716B8.unk1E8 == 0 && lbl_803C6CF8.cancel.bytes[1] == 1) {
        hugeAnimStruct.fileIndex = index;
        hugeAnimStruct.fileLoadState = 0;
        return TRUE;
    }
    return FALSE;
}

#undef hugeAnimStruct
#undef lbl_803716B8
#undef lbl_803CB790

typedef struct {
    /*0x0000*/ u8 _0000[0x2D3C];
    /*0x2D3C*/ s32 batterModelDest;
    /*0x2D40*/ u8 _2D40[0x2D44 - 0x2D40];
    /*0x2D44*/ u16 batterModelIndex;
    /*0x2D46*/ u8 batterModelLoadState;
    /*0x2D47*/ u8 _2D47[0x3154 - 0x2D47];
} hugeAnimStruct_view_80014f40;
#define hugeAnimStruct (*(hugeAnimStruct_view_80014f40*)&hugeAnimStruct)

typedef CompressedFileEntry* lbl_803CB790_view_80014f40;
#define lbl_803CB790 (*(lbl_803CB790_view_80014f40*)&lbl_803CB790)

BOOL loadBatterModelFromDisk(int index) {
    if (index < 0) {
        return TRUE;
    }
    if (hugeAnimStruct.batterModelLoadState <= 1) {
        int file = index * 0x13 + 1;

        if (lbl_803C6CF8.cancel.bytes[1] != 1) {
            hugeAnimStruct.batterModelLoadState = 1;
            return FALSE;
        }
        ARAMTransfer(&lbl_803CB790[file], hugeAnimStruct.batterModelDest, 0, 0);
        hugeAnimStruct.batterModelLoadState = 2;
    } else if (lbl_803C6CF8.cancel.bytes[1] == 1) {
        hugeAnimStruct.batterModelIndex = index;
        hugeAnimStruct.batterModelLoadState = 0;
        return TRUE;
    }
    return FALSE;
}

#undef hugeAnimStruct
#undef lbl_803CB790

typedef u8 hugeAnimStruct_view_8001594c[0x3154];
#define hugeAnimStruct (*(hugeAnimStruct_view_8001594c*)&hugeAnimStruct)
extern u8 lineUpInfoStruct[];
extern u8 lbl_80118220[0x520];
extern s16 lbl_800EEB18[];
typedef u8 lbl_803C6CF8_view_8001594c[0x708];
#define lbl_803C6CF8 (*(lbl_803C6CF8_view_8001594c*)&lbl_803C6CF8)
extern u8 lbl_803CB7C2;
extern u8 lbl_803CBC34[3];
extern u8 lbl_803CBC2C;
extern u8 lbl_803CBBF8;
extern u8 lbl_803CBBF9;
extern u8 lbl_803CBBFA;
extern s32 lbl_803CBBF0;
extern s32 lbl_803CBC28;

int fn_80015468(int team);
int fn_80014A18(int team);
int fn_80017098(int a, int b, int c, int d, int e, int f);
void fn_80021ADC(int value, void *entry);
BOOL animateModelArmsGlovesBats(void *object);
void actRelated(void *file, void *effect);

#define OBJ_SLOT(anim, i) (*(u8 **)((anim) + 0x2C50 + (i) * 4))

#define PRACTICE_LOAD_BC_STEPS() \
    if (anim[0x2D7B] == 0xB) { \
        if (lbl_803CB7C2 != 0) { \
            u8 flag0 = lbl_803CBC34[0]; \
            lbl_803CB7C2 = 0; \
            if (flag0 != 0) { \
                lbl_803CBC2C = 0; \
                lbl_803CBBF8 = 9; \
            } else { \
                if (lbl_803CBC34[1] != 0) { \
                    u8 count = lbl_803CBBF8; \
                    lbl_803CBC2C = 0; \
                    lbl_803CBBF8 = count + 1; \
                } \
                if (lbl_803CBC34[2] != 0) { \
                    lbl_803CBBF8 = lbl_803CBBF8 + 1; \
                    if (lbl_803CBC34[1] == 0) { \
                        lbl_803CBC2C = 1; \
                    } \
                } \
            } \
        } \
\
        if (lbl_803CBBF8 == 0) { \
            ok = TRUE; \
        } else { \
            int idx = lbl_803CBBF0 + lbl_803CBC2C; \
            u8 *obj = OBJ_SLOT(anim, idx); \
            u8 typeId = obj[0x252]; \
            u8 idxByte = (u8)idx; \
            int stepped = 0; \
\
            if (lbl_803CBBF9 == 0) { \
                u8 *p = lbl_80118220; \
                int found = 0; \
\
                while ((s8)p[0x61] != -2) { \
                    if ((s8)p[0x60] == typeId && (s8)p[0x61] == -1) { \
                        found = 1; \
                        break; \
                    } \
                    p += 0x64; \
                } \
\
                if (found) { \
                    u8 *sub = *(u8 **)(obj + 0x08); \
                    p[0x60] = typeId; \
                    p[0x61] = idxByte; \
                    *(u8 **)(obj + 0x2C) = p; \
                    *(u32 *)(p + 0x30) = *(u32 *)(sub + 0x10); \
                    stepped = 1; \
                } else { \
                    int count = 0; \
                    u8 *q = lbl_80118220; \
                    lbl_803CBBF9 = 1; \
                    while ((s8)q[0x61] != -2 && (s8)q[0x61] != -1) { \
                        q += 0x64; \
                        count++; \
                    } \
                    lbl_803CBC28 = count; \
                } \
            } \
\
            if (!stepped) { \
                int r3val; \
                u8 *entry = lbl_80118220 + lbl_803CBC28 * 0x64; \
                u8 *sub = *(u8 **)(obj + 0x08); \
                entry[0x5D] = 0; \
                if (lbl_800EEB18[typeId] == -1 || *(u32 *)(sub + 0x10) == 0) { \
                    *(u8 **)(obj + 0x2C) = NULL; \
                    r3val = 1; \
                } else { \
                    if (lbl_803CBBFA == 0) { \
                        fn_80021ADC(lbl_800EEB18[typeId], *(void **)entry); \
                        lbl_803CBBFA = 1; \
                    } \
                    if (lbl_803C6CF8[0x715] == 1) { \
                        entry[0x60] = typeId; \
                        entry[0x61] = idxByte; \
                        *(u32 *)(entry + 4) = *(u32 *)entry; \
                        actRelated(*(void **)(sub + 0x10), entry + 4); \
                        *(u8 **)(obj + 0x2C) = entry; \
                        lbl_803CBBFA = 0; \
                        r3val = 1; \
                    } else { \
                        r3val = 0; \
                    } \
                } \
                if (r3val) { \
                    lbl_803CBBF9 = 0; \
                    stepped = 1; \
                } \
            } \
\
            if (stepped) { \
                lbl_803CBBF0 = lbl_803CBBF0 + 1; \
            } \
            if ((u32)lbl_803CBBF8 == (u32)lbl_803CBBF0) { \
                lbl_803CBBF0 = 0; \
                ok = TRUE; \
            } else { \
                ok = FALSE; \
            } \
        } \
\
        if (!ok) { \
            return FALSE; \
        } \
        anim[0x2D7B] = 0xC; \
    } \
\
    if (anim[0x2D7B] == 0xC) { \
        int ret = animateModelArmsGlovesBats(OBJ_SLOT(anim, lbl_803CBBF0)); \
        if ((u8)ret != 0) { \
            lbl_803CBBF0 = lbl_803CBBF0 + 1; \
        } \
        if (lbl_803CBBF0 == 9) { \
            lbl_803CBBF0 = 0; \
            return TRUE; \
        } \
        return FALSE; \
    }

BOOL practice_loadAllGraphics(int team)
{
    u8 *anim = hugeAnimStruct;
    u8 *lineUp;
    int i;
    int k;
    int ok;

    if (anim[0x2D77] == 1) {
        return FALSE;
    }

    if (anim[0x2D77] == 2) {
        u8 srcSlot = anim[0x2D79];
        u8 dstSlot = anim[0x2D7B];
        OBJ_SLOT(anim, dstSlot) = anim + srcSlot * 0x27C + 0xC04;
        anim[0x2D77] = 0;
        anim[0x2D7B] = dstSlot + 1;
    }

    if (anim[0x2D7B] == 9) {
        anim[0x2D8E] = 0;
        anim[0x2D7B] = 0xA;
    }

    if (anim[0x2D7C] == 0) {
        if (anim[0x2D7B] == 0xA) {
            if (!fn_80015468(team)) {
                return FALSE;
            }
            anim[0x2D7B] = 0xB;
        }
        PRACTICE_LOAD_BC_STEPS()
    } else {
        if (anim[0x2D7B] == 0xA) {
            if (!fn_80014A18(team)) {
                return FALSE;
            }
            anim[0x2D7B] = 0xB;
        }
        PRACTICE_LOAD_BC_STEPS()
    }

    lineUp = lineUpInfoStruct + team * 0x24;

    for (i = 0; i < 9; i++) {
        u8 *obj = OBJ_SLOT(anim, i);
        if (obj == NULL) {
            continue;
        }

        for (k = 0; k < 9; k++) {
            if (inMemRoster[team][(s8)lineUp[k * 4]].stats.CharID == (s8)obj[0x252]) {
                break;
            }
        }

        if (k == 9) {
            u8 *entry = *(u8 **)(obj + 0x2C);
            u8 *sub;
            if (entry != NULL) {
                entry[0x61] = 0xFF;
                entry[0x5C] = 0xFE;
                *(u8 **)(obj + 0x2C) = NULL;
            }

            sub = *(u8 **)(obj + 0x30);
            if (sub != NULL) {
                sub[0xD1] = sub[0xD0];
                sub[0xD0] = 0xFF;
                sub[0x5C] = 0xFE;
                sub[0xC0] = 0xFE;
                *(u8 **)(obj + 0x30) = NULL;
            }

            obj[0x25C] = 0;
            OBJ_SLOT(anim, i) = NULL;
            {
                int j;
                for (j = 0; j < 13; j++) {
                    if ((s8)anim[0x2D6A + j] == i) {
                        anim[0x2D6A + j] = 0xFF;
                    }
                }
            }
        }
    }

    {
        u8 state = anim[0x2D7B];
        int idx = 9;
        for (k = 0; k < 9; k++) {
            if ((s8)state == (s8)lineUp[2 + k * 4]) {
                idx = k;
                break;
            }
        }
        if (fn_80017098(team, idx, 0, state, 0, -1)) {
            anim[0x2D77] = 2;
        }
    }

    return FALSE;
}

#undef OBJ_SLOT
#undef PRACTICE_LOAD_BC_STEPS
#undef hugeAnimStruct
#undef lbl_803C6CF8

typedef struct CompressedFileEntry_80018024 {
    /*0x00*/ u8 _00[0x04];
    /*0x04*/ u32 _04;
    /*0x08*/ u8 _08[0x08];
} CompressedFileEntry_80018024;

typedef CompressedFileEntry_80018024* lbl_803CB790_view_80018024;
#define lbl_803CB790 (*(lbl_803CB790_view_80018024*)&lbl_803CB790)

typedef struct AnimModelMemory {
    /*0x0000*/ u8 _0000[0x0C0C];
    /*0x0C0C*/ u8* _0C0C;
    /*0x0C10*/ u8* _0C10;
    /*0x0C14*/ u8 _0C14[0x0C30 - 0x0C14];
    /*0x0C30*/ u8* _0C30;
    /*0x0C34*/ u8* _0C34;
    /*0x0C38*/ u8 _0C38[0x0E88 - 0x0C38];
    /*0x0E88*/ u8* _0E88;
    /*0x0E8C*/ u8* _0E8C;
    /*0x0E90*/ u8 _0E90[0x0EAC - 0x0E90];
    /*0x0EAC*/ u8* _0EAC;
    /*0x0EB0*/ u8* _0EB0;
    /*0x0EB4*/ u8 _0EB4[0x1104 - 0x0EB4];
    /*0x1104*/ u8* _1104;
    /*0x1108*/ u8* _1108;
    /*0x110C*/ u8 _110C[0x1128 - 0x110C];
    /*0x1128*/ u8* _1128;
    /*0x112C*/ u8* _112C;
    /*0x1130*/ u8 _1130[0x1380 - 0x1130];
    /*0x1380*/ u8* _1380;
    /*0x1384*/ u8* _1384;
    /*0x1388*/ u8 _1388[0x13A4 - 0x1388];
    /*0x13A4*/ u8* _13A4;
    /*0x13A8*/ u8* _13A8;
    /*0x13AC*/ u8 _13AC[0x1620 - 0x13AC];
    /*0x1620*/ u8* _1620;
    /*0x1624*/ u8* _1624;
    /*0x1628*/ u8 _1628[0x189C - 0x1628];
    /*0x189C*/ u8* _189C;
    /*0x18A0*/ u8* _18A0;
    /*0x18A4*/ u8 _18A4[0x1B18 - 0x18A4];
    /*0x1B18*/ u8* _1B18;
    /*0x1B1C*/ u8* _1B1C;
    /*0x1B20*/ u8 _1B20[0x1D94 - 0x1B20];
    /*0x1D94*/ u8* _1D94;
    /*0x1D98*/ u8* _1D98;
    /*0x1D9C*/ u8 _1D9C[0x2C8C - 0x1D9C];
    /*0x2C8C*/ u8* _2C8C;
    /*0x2C90*/ u8 _2C90[0x2D64 - 0x2C90];
    /*0x2D64*/ u32 _2D64;
} AnimModelMemory;

typedef AnimModelMemory hugeAnimStruct_view_80018024;
#define hugeAnimStruct (*(hugeAnimStruct_view_80018024*)&hugeAnimStruct)

void setupAnimationModelMemory(void) {
    s32 i;
    s32 entry;
    u32 maxA;
    u32 maxB;
    u32 v;
    u32 sizeA;
    u32 sizeB;
    u8* p;

    maxA = 0;
    maxB = 0;
    entry = 0;
    p = (u8*)lbl_803CB790;
    for (i = 0; i < 18; i++) {
        v = ((CompressedFileEntry_80018024*)p)[0]._04 & 0x0FFFFFFF;
        if (maxA < v) {
            maxA = v;
        }
        v = ((CompressedFileEntry_80018024*)p)[1]._04 & 0x0FFFFFFF;
        if (maxB < v) {
            maxB = v;
        }
        v = ((CompressedFileEntry_80018024*)p)[19]._04 & 0x0FFFFFFF;
        if (maxA < v) {
            maxA = v;
        }
        v = ((CompressedFileEntry_80018024*)p)[20]._04 & 0x0FFFFFFF;
        if (maxB < v) {
            maxB = v;
        }
        v = ((CompressedFileEntry_80018024*)p)[38]._04 & 0x0FFFFFFF;
        if (maxA < v) {
            maxA = v;
        }
        v = ((CompressedFileEntry_80018024*)p)[39]._04 & 0x0FFFFFFF;
        if (maxB < v) {
            maxB = v;
        }
        p += 57 * 16;
    }

    sizeA = (maxA + 0x1F) & ~0x1F;
    sizeB = (maxB + 0x1F) & ~0x1F;
    hugeAnimStruct._2D64 = sizeA;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        hugeAnimStruct._2C8C = _OSAllocFromHeap(0x20, (sizeA + sizeB) * 4);
    } else {
        hugeAnimStruct._2C8C = _OSAllocFromHeap(0x20, sizeA * 4);
    }

    p = hugeAnimStruct._2C8C;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        hugeAnimStruct._0C0C = p;
        p += sizeA;
        hugeAnimStruct._0C30 = 0;
        hugeAnimStruct._0C34 = 0;
        hugeAnimStruct._0C10 = p;
        p += sizeB;
        hugeAnimStruct._1620 = 0;
        hugeAnimStruct._1624 = 0;
        hugeAnimStruct._0E88 = p;
        p += sizeA;
        hugeAnimStruct._0EAC = 0;
        hugeAnimStruct._0EB0 = 0;
        hugeAnimStruct._0E8C = p;
        p += sizeB;
        hugeAnimStruct._189C = 0;
        hugeAnimStruct._18A0 = 0;
        hugeAnimStruct._1104 = p;
        p += sizeA;
        hugeAnimStruct._1128 = 0;
        hugeAnimStruct._112C = 0;
        hugeAnimStruct._1108 = p;
        p += sizeB;
        hugeAnimStruct._1B18 = 0;
        hugeAnimStruct._1B1C = 0;
        hugeAnimStruct._1380 = p;
        p += sizeA;
        hugeAnimStruct._13A4 = 0;
        hugeAnimStruct._13A8 = 0;
        hugeAnimStruct._1384 = p;
        hugeAnimStruct._1D94 = 0;
        hugeAnimStruct._1D98 = 0;
    } else {
        hugeAnimStruct._0C0C = p;
        p += sizeA;
        hugeAnimStruct._0C30 = 0;
        hugeAnimStruct._0C34 = 0;
        hugeAnimStruct._0E88 = p;
        p += sizeA;
        hugeAnimStruct._0EAC = 0;
        hugeAnimStruct._0EB0 = 0;
        hugeAnimStruct._1104 = p;
        p += sizeA;
        hugeAnimStruct._1128 = 0;
        hugeAnimStruct._112C = 0;
        hugeAnimStruct._1380 = p;
        hugeAnimStruct._13A4 = 0;
        hugeAnimStruct._13A8 = 0;
    }
}

#undef hugeAnimStruct
#undef lbl_803CB790

extern void *_OSAllocFromHeap(s32 alignment, s32 size);

typedef u8 hugeAnimStruct_view_80018270[];
#define hugeAnimStruct (*(hugeAnimStruct_view_80018270*)&hugeAnimStruct)

#define HUGE_U32(off) (*(u32 *)(hugeAnimStruct + (off)))
#define HUGE_S16(off) (*(s16 *)(hugeAnimStruct + (off)))
#define HUGE_U8(off) (*(u8 *)(hugeAnimStruct + (off)))
#define CHAR_RECORD_U32(id, off) (*(u32 *)((u8 *)lbl_803CB790 + (id) * 0x130 + (off)))

#define CHAR_RECORD_COUNT 54
#define OBJECT_SLOT_STRIDE 0x27C

void animationInitializationRunnerRelated(int mode) {
    u32 maxA = 0;
    u32 maxB = 0;
    u32 i;
    u32 n;
    u32 v;
    u32 base;
    u32 a;
    u32 aUp;
    u32 bUp;
    u32 size;
    int t;
    int p;

    if (mode == 2) {
        base = (u32)_OSAllocFromHeap(0x20, 0x13E80);
        HUGE_U32(0x2C8C) = base;
        HUGE_U32(0xC0C) = base;
        for (i = 1; i < 9; i++) {
            HUGE_U32(0xC0C + i * OBJECT_SLOT_STRIDE) = (u32)_OSAllocFromHeap(0x20, 0x12C40);
        }

        for (n = 0; n < CHAR_RECORD_COUNT; n++) {
            v = CHAR_RECORD_U32(n, 0x4) & 0x0FFFFFFF;
            if (maxA < v) {
                maxA = v;
            }
        }

        a = maxA + 0x1F;
        aUp = a & ~0x1F;
        size = (a >> 5) + 0x13E80;
        base = (u32)_OSAllocFromHeap(0x20, size);
        HUGE_U32(0x2268) = base;
        HUGE_U32(0x24E4) = base + aUp;
        HUGE_U32(0x2760) = base + aUp * 2;
        HUGE_U32(0x29DC) = base + aUp * 3;
        HUGE_U32(0x2D64) = size;
        HUGE_U32(0x2D3C) = base + aUp * 4;
        HUGE_U32(0x2D40) = 0x13E80;
        HUGE_S16(0x2D44) = -1;
        HUGE_U8(0x2D46) = 0;
    } else {
        if (mode == 0) {
            for (t = 0; t < TEAMS_PER_GAME; t++) {
                for (p = 0; p < PLAYERS_PER_TEAM; p++) {
                    v = CHAR_RECORD_U32(inMemRoster[t][p].stats.CharID, 0x4) & 0x0FFFFFFF;
                    if (maxA < v) {
                        maxA = v;
                    }
                }
            }
            for (t = 0; t < TEAMS_PER_GAME; t++) {
                for (p = 0; p < PLAYERS_PER_TEAM; p++) {
                    v = CHAR_RECORD_U32(inMemRoster[t][p].stats.CharID, 0x14) & 0x0FFFFFFF;
                    if (maxB < v) {
                        maxB = v;
                    }
                }
            }
        } else {
            for (n = 0; n < CHAR_RECORD_COUNT; n++) {
                v = CHAR_RECORD_U32(n, 0x4) & 0x0FFFFFFF;
                if (maxA < v) {
                    maxA = v;
                }
            }
            for (n = 0; n < CHAR_RECORD_COUNT; n++) {
                v = CHAR_RECORD_U32(n, 0x14) & 0x0FFFFFFF;
                if (maxB < v) {
                    maxB = v;
                }
            }
        }

        bUp = (maxB + 0x1F) & ~0x1F;
        a = maxA + 0x1F;
        aUp = a & ~0x1F;
        size = bUp * 9 + (a >> 5) + aUp + bUp;
        base = (u32)_OSAllocFromHeap(0x20, size);
        HUGE_U32(0x2C8C) = base;
        HUGE_U32(0x2D64) = size;
        for (i = 0; i < 9; i++) {
            HUGE_U32(0xC0C + i * OBJECT_SLOT_STRIDE) = base;
            base += bUp;
        }
        HUGE_U32(0x2268) = base;
        base += aUp;
        HUGE_U32(0x24E4) = base;
        base += aUp;
        HUGE_U32(0x2760) = base;
        base += aUp;
        HUGE_U32(0x29DC) = base;
        base += aUp;
        HUGE_U32(0x2D54) = base;
        base += aUp;
        HUGE_U32(0x2D58) = aUp;
        HUGE_S16(0x2D5C) = -1;
        HUGE_U8(0x2D5E) = 0;
        HUGE_U32(0x2D3C) = base;
        HUGE_U32(0x2D40) = bUp;
        HUGE_S16(0x2D44) = -1;
        HUGE_U8(0x2D46) = 0;
    }

    for (i = 0; i < 13; i++) {
        HUGE_U32(0xC30 + i * OBJECT_SLOT_STRIDE) = 0;
        HUGE_U32(0xC34 + i * OBJECT_SLOT_STRIDE) = 0;
    }
}

#undef CHAR_RECORD_COUNT
#undef CHAR_RECORD_U32
#undef HUGE_S16
#undef HUGE_U32
#undef HUGE_U8
#undef OBJECT_SLOT_STRIDE
#undef hugeAnimStruct

/* Node of the challenge map drawing script (the object currentDrawingItem points at). */
typedef struct ChallengeMapNode {
    /* 0x00 */ u8 _00[0x0C];
    /* 0x0C */ DrawingSceneStruct *child;
    /* 0x10 */ u8 _10[0x14 - 0x10];
    /* 0x14 */ u8 step;
    /* 0x15 */ u8 _15;
    /* 0x16 */ u8 _16;
    /* 0x17 */ u8 _17;
    /* 0x18 */ u8 _18;
} ChallengeMapNode;

/* This unit's view of hugeAnimStruct (0x3154 bytes). */
typedef struct {
    /* 0x0000 */ u8 _0000[0x2C84];
    /* 0x2C84 */ u32 *offsetTable;
    /* 0x2C88 */ u8 _2C88[0x2D77 - 0x2C88];
    /* 0x2D77 */ u8 _2D77;
    /* 0x2D78 */ u8 _2D78[0x2D7A - 0x2D78];
    /* 0x2D7A */ u8 _2D7A;
    /* 0x2D7B */ u8 _2D7B;
    /* 0x2D7C */ u8 _2D7C;
    /* 0x2D7D */ u8 _2D7D[0x307B - 0x2D7D];
    /* 0x307B */ u8 _307B;
    /* 0x307C */ u8 _307C;
    /* 0x307D */ u8 _307D;
    /* 0x307E */ u8 _307E[0x3082 - 0x307E];
    /* 0x3082 */ u8 _3082;
    /* 0x3083 */ u8 _3083[0x3086 - 0x3083];
    /* 0x3086 */ u8 _3086;
    /* 0x3087 */ u8 _3087;
} hugeAnimStruct_view_8001a6b0;
#define hugeAnimStruct (*(hugeAnimStruct_view_8001a6b0*)&hugeAnimStruct)

typedef Vec lbl_80367318_view_8001a6b0;
#define lbl_80367318 (*(lbl_80367318_view_8001a6b0*)&lbl_80367318)

void challengeMapRelated(void) {
    ChallengeMapNode *node;
    Vec dir;
    f32 len;
    s32 i;
    s32 k;
    Vec copy;

    if (hugeAnimStruct._3082 != 0) {
        return;
    }

    node = (ChallengeMapNode *)currentDrawingItem;
    switch (node->step) {
    case 0:
        hugeAnimStruct._2D77 = 0;
        hugeAnimStruct._2D7B = 0;
        hugeAnimStruct._2D7C = 0;
        hugeAnimStruct._2D7A = 0;
        node->_16 = 0;
        node->_18 = 0;
        node->step = 1;
        break;
    case 1:
        if (practice_loadAllGraphics(g_d_GameSettings.home_AwaySetting ^ 1) != FALSE) {
            node->step = 2;
        }
        break;
    case 2: {
        ChallengeMapNode *fresh =
            (ChallengeMapNode *)insertGraphicDrawingFunction(fn_800188C0, 0);

        fresh->step = 0;
        fresh->_16 = 0;
        fresh->_17 = 0xFF;
        hugeAnimStruct._307B = 1;
        node->step++;
        break;
    }
    case 3:
        if (hugeAnimStruct._307B == 0) {
            node->step = 6;
        }
        break;
    case 6:
        dir.x = -lbl_80367318.x;
        dir.y = -lbl_80367318.y;
        dir.z = -lbl_80367318.z;
        len = dolsqrtf2((dir.x * dir.x) + (dir.y * dir.y) + (dir.z * dir.z));
        hugeAnimStruct._3087 = 1;
        dir.x /= len;
        dir.y /= len;
        dir.z /= len;
        fn_8003A540(0);
        hugeAnimStruct._3086 = 1;
        DrawShadows(1);
        copy = dir;
        updateVectorInArray(0, copy);
        fn_800BF048(fn_8001AAF0);
        fn_800BF058(fn_8001AB10);
        for (i = 0; i < 80; i += 8) {
            for (k = 0; k < 8; k++) {
                hugeAnimStruct.offsetTable[i + k] += (u32)hugeAnimStruct.offsetTable;
            }
        }
        hugeAnimStruct._3082 = 0;
        hugeAnimStruct._307C = 0;
        hugeAnimStruct._307D = 0;
        fn_8001F8A4();
        node->step++;
        break;
    case 7:
        challengeMapMaybe();
        node->step++;
        break;
    case 8:
        hugeAnimStruct._307C = 1;
        node->child->state = 1;
        removeCurrentDrawingItem();
        break;
    default:
        break;
    }
}

#undef hugeAnimStruct
#undef lbl_80367318

extern u8 destAnimStructs[0x204C];
typedef u8 hugeAnimStruct_view_8001b2d0[0x3154];
#define hugeAnimStruct (*(hugeAnimStruct_view_8001b2d0*)&hugeAnimStruct)

void copyAnimationStructures(void) {
    memcpy(destAnimStructs, hugeAnimStruct + 0xC04, sizeof(destAnimStructs));
}

#undef hugeAnimStruct

typedef struct CollisionObject {
    /*0x000*/ u8 _000[0x34];
    /*0x034*/ Vec offset;
    /*0x040*/ u8 _040[0x162 - 0x40];
    /*0x162*/ u16 bones[1];
    /*0x164*/ u8 _164[0x255 - 0x164];
    /*0x255*/ s8 slot;
} CollisionObject;

typedef u8 hugeAnimStruct_view_8001b728[0x3154];
#define hugeAnimStruct (*(hugeAnimStruct_view_8001b728*)&hugeAnimStruct)
extern void fn_800B2C10(void* actor, u16 bone, Vec* vec);

BOOL getAnimationCollisionOffset(int animIdx, int node, Vec* out) {
    CollisionObject* obj;
    int bone;
    u8* trackBlock;
    void* actor;

    obj = ((CollisionObject**)(hugeAnimStruct + 0x2C50))[animIdx];
    if (obj == NULL) {
        return FALSE;
    }

    if (obj != NULL) {
        bone = obj->bones[node];
    } else {
        bone = 0xFFFF;
    }
    if (bone == 0xFFFF) {
        return FALSE;
    }

    trackBlock = *(u8**)(hugeAnimStruct + 0x60);
    actor = *(void**)(trackBlock + obj->slot * 0x90 + 0x34);
    fn_800B2C10(actor, (u16)bone, out);

    out->x = out->x + obj->offset.x;
    out->y = out->y + obj->offset.y;
    out->z = out->z + obj->offset.z;
    return TRUE;
}

#undef hugeAnimStruct

#define NO_BONE 0xFFFF

/* An entry of the hugeAnimStruct object table at +0x2C50. */
typedef struct AnimObject {
    /* 0x000 */ u8 _000[0x34];
    /* 0x034 */ Vec pos;
    /* 0x040 */ u8 _040[0x162 - 0x40];
    /* 0x162 */ u16 partBones[(0x254 - 0x162) / 2];
    /* 0x254 */ s8 animIdx;
    /* 0x255 */ s8 actorIdx;
} AnimObject;

/* This unit's view of hugeAnimStruct (0x3154 bytes). */


static inline int getPartBone(AnimObject* obj, int part) {
    if (obj != NULL) {
        return obj->partBones[part];
    }
    return NO_BONE;
}

BOOL getAnimRelatedCoordinates(int objIndex, int part, VecXYZ* out) {
    AnimObject* obj = ((AnimObject*)hugeAnimStruct.objects[objIndex]);
    int bone;
    Vec v;

    if (obj == NULL) {
        return FALSE;
    }
    bone = getPartBone(obj, part);
    if (bone == NO_BONE) {
        out->x = 0.0f;
        out->y = 0.0f;
        out->z = 0.0f;
        return FALSE;
    }
    maybeTransformVectorByAnimationMatrix(*(Actor**)((u8*)hugeAnimStruct.actorTable + obj->actorIdx * sizeof(ActorObjectEntry) + 0x34), bone, &v);
    out->x = v.x;
    out->y = v.y;
    out->z = v.z;
    out->x += obj->pos.x;
    out->y += obj->pos.y;
    out->z += obj->pos.z;
    return TRUE;
}

#undef NO_BONE

#define ANIM_OBJECT_COUNT 13

/* One animation-driven object in hugeAnimStruct's object pool. */
typedef struct AnimObject_8001b918 {
    /* 0x000 */ u8 _000[0x62];
    /* 0x062 */ s16 animId;
    /* 0x064 */ s16 nextAnimId;
    /* 0x066 */ s16 queuedAnimId;
    /* 0x068 */ u8 _068[0x6C - 0x68];
    /* 0x06C */ s16 _6C;
    /* 0x06E */ s16 _6E;
    /* 0x070 */ u8 _070[0x25E - 0x70];
    /* 0x25E */ u8 _25E;
    /* 0x25F */ u8 _25F;
    /* 0x260 */ u8 _260;
    /* 0x261 */ u8 _261;
    /* 0x262 */ u8 _262;
    /* 0x263 */ u8 _263;
    /* 0x264 */ u8 _264;
    /* 0x265 */ u8 _265;
    /* 0x266 */ u8 _266;
    /* 0x267 */ u8 _267;
    /* 0x268 */ u8 _268[0x26A - 0x268];
    /* 0x26A */ u8 _26A;
    /* 0x26B */ u8 _26B;
    /* 0x26C */ u8 _26C;
    /* 0x26D */ u8 _26D;
    /* 0x26E */ u8 _26E;
    /* 0x26F */ u8 _26F[0x27C - 0x26F];
} AnimObject_8001b918; // size 0x27C

/* This unit's view of hugeAnimStruct (0x3154 bytes). */


void QueueCharacterAnimation(int objIndex, int animId, int a2, int a3, int a4, int a5, int a6) {
    AnimObject_8001b918* obj = ((AnimObject_8001b918*)hugeAnimStruct.objects[objIndex]);

    obj->queuedAnimId = animId;
    obj->_6E = a4;
    obj->_261 = a2;
    obj->_264 = a3;
    obj->_267 = a5;
    obj->_26E = 0;
    if (a6 == -1) {
        obj->_26B = 5;
    } else {
        obj->_26B = a6;
    }
    if ((animId >= 0x3F && animId < 0x4B) || (animId >= 0x4B && animId < 0x69)) {
        ((AnimObject_8001b918*)hugeAnimStruct.objects[objIndex])->_26E = 1;
    }
}

void AnimateCharacter(int objIndex, int animId, int a2, int a3, int a4, int a5, int a6, int a7) {
    AnimObject_8001b918* obj = ((AnimObject_8001b918*)hugeAnimStruct.objects[objIndex]);

    if (obj == NULL) {
        return;
    }
    if ((u8)a3 == 1 && obj->animId == animId) {
        return;
    }
    if ((u8)a3 == 3) {
        a3 = 1;
    }
    obj->nextAnimId = animId;
    obj->_6C = a5;
    obj->_260 = a2;
    obj->_25E = a3;
    obj->_263 = a4;
    obj->_266 = a6;
    obj->_26D = 0;
    if (a7 == -1) {
        obj->_26A = 5;
    } else {
        obj->_26A = a7;
    }
    obj->queuedAnimId = -1;
    if ((animId >= 0x3F && animId < 0x4B) || (animId >= 0x4B && animId < 0x69)) {
        ((AnimObject_8001b918*)hugeAnimStruct.objects[objIndex])->_26D = 1;
    }
}

#undef ANIM_OBJECT_COUNT

typedef struct {
    /*0x00*/ u8 _00[0x20];
    /*0x20*/ ANIMBank* animBank;
} FielderActorData;

typedef struct {
    /*0x0000*/ u8 _0000[0x2C54];
    /*0x2C54*/ FielderActorData* fielderActorData;
    /*0x2C58*/ u8 _2C58[0x2CE8 - 0x2C58];
    /*0x2CE8*/ ANIMBank* fielderAnimBank;
    /*0x2CEC*/ u8 _2CEC[0x3154 - 0x2CEC];
} hugeAnimStruct_view_8001c588;
#define hugeAnimStruct (*(hugeAnimStruct_view_8001c588*)&hugeAnimStruct)


typedef CompressedFileEntry* lbl_803CB790_view_8001c588;
#define lbl_803CB790 (*(lbl_803CB790_view_8001c588*)&lbl_803CB790)

BOOL loadFielderActors(int charID) {
    do {
        if (highLevelSimulationFlag[3] == 0) {
            if (lbl_803C6CF8.cancel.bytes[1] != 1) {
                break;
            }
            highLevelSimulationFlag[3] = 1;
        }
        if (highLevelSimulationFlag[3] == 1) {
            ARAMTransfer(&lbl_803CB790[charID * 0x13 + 6], (s32)hugeAnimStruct.fielderAnimBank, 0, 0);
            highLevelSimulationFlag[3] = 2;
        } else if (highLevelSimulationFlag[3] == 2 && lbl_803C6CF8.cancel.bytes[1] == 1) {
            ANIMGet(hugeAnimStruct.fielderAnimBank);
            if (hugeAnimStruct.fielderActorData->animBank == NULL) {
                hugeAnimStruct.fielderActorData->animBank = hugeAnimStruct.fielderAnimBank;
            }
            return TRUE;
        }
    } while (0);
    highLevelSimulationFlag[0] = 0;
    return FALSE;
}

#undef hugeAnimStruct
#undef lbl_803CB790

typedef u8 hugeAnimStruct_view_8001c67c[0x3154];
#define hugeAnimStruct (*(hugeAnimStruct_view_8001c67c*)&hugeAnimStruct)

typedef u32 lbl_803CB790_view_8001c67c;
#define lbl_803CB790 (*(lbl_803CB790_view_8001c67c*)&lbl_803CB790)
extern f32 lbl_803CC4B8;
extern f32 lbl_803CC4F0;

int loadAndAnimateCharacter(int charSlot, int objSlot) {
    if (highLevelSimulationFlag[2] == 0) {
        if (lbl_803C6CF8.cancel.bytes[1] != 1) {
            return 0;
        }
        {
            u8* charObj = *(u8**)(hugeAnimStruct + 0x64);
            Actor* actor = *(Actor**)(charObj + 0x274);
            u8* firstBoneExtra = *(u8**)((u8*)actor->boneArray[0] + 0xE8);

            if (firstBoneExtra != NULL && *(u32*)(firstBoneExtra + 0xC) != 0) {
                s32 i;
                f32 threshold = lbl_803CC4F0;
                for (i = 0; i < actor->totalBones; i++) {
                    ACTSetBoneTrack(actor->boneArray[i], NULL, lbl_803CC4B8, actor->unk8C < threshold);
                }
                charObj[0x2CC] = 0;
                charObj[0x2CD] = 0;
                charObj[0x2CE] = 0;
                *(f32*)(charObj + 0x2D4) = lbl_803CC4B8;
            }
        }
        highLevelSimulationFlag[2] = 1;
    }

    if (highLevelSimulationFlag[2] == 1) {
        if (g_d_GameSettings.minigamesEnabled) {
            s32 idx;
            if (g_d_GameSettings.GameModeSelected == 7) {
                idx = charSlot * 0x13 + 9;
            } else {
                idx = charSlot * 0x13 + 2;
            }
            ARAMTransfer((void*)(lbl_803CB790 + (idx << 4)), *(s32*)(hugeAnimStruct + 0x2CF8), 0, 0);
        } else if (charSlot == *(s16*)(hugeAnimStruct + 0x2D50)) {
            memcpy(*(void**)(hugeAnimStruct + 0x2CAC), *(void**)(hugeAnimStruct + 0x2D48), *(u32*)(hugeAnimStruct + 0x2D4C));
            ANIMGet(*(ANIMBank**)(hugeAnimStruct + 0x2CAC));
            {
                u8* obj = ((u8**)(hugeAnimStruct + 0x2C50))[objSlot];
                if (*(void**)(obj + 0x10) == NULL) {
                    *(void**)(obj + 0x10) = *(void**)(hugeAnimStruct + 0x2CAC);
                }
            }
            *(s16*)(hugeAnimStruct + 0x2D68) = (s16)charSlot;
            return 1;
        } else {
            s32 idx;
            if (g_d_GameSettings.GameModeSelected == 2) {
                idx = charSlot * 0x13 + 10;
            } else {
                idx = charSlot * 0x13 + 2;
            }
            ARAMTransfer((void*)(lbl_803CB790 + (idx << 4)), *(s32*)(hugeAnimStruct + 0x2CAC), 0, 0);
        }
        highLevelSimulationFlag[2] = 2;
    } else if (highLevelSimulationFlag[2] == 2 && lbl_803C6CF8.cancel.bytes[1] == 1) {
        if (g_d_GameSettings.minigamesEnabled) {
            ANIMGet(*(ANIMBank**)(hugeAnimStruct + 0x2CF8));
            {
                u8* obj = ((u8**)(hugeAnimStruct + 0x2C50))[objSlot];
                if (*(void**)(obj + 0x10) == NULL) {
                    *(void**)(obj + 0x10) = *(void**)(hugeAnimStruct + 0x2CF8);
                }
            }
        } else {
            ANIMGet(*(ANIMBank**)(hugeAnimStruct + 0x2CAC));
            {
                u8* obj = ((u8**)(hugeAnimStruct + 0x2C50))[objSlot];
                if (*(void**)(obj + 0x10) == NULL) {
                    *(void**)(obj + 0x10) = *(void**)(hugeAnimStruct + 0x2CAC);
                }
            }
        }
        *(s16*)(hugeAnimStruct + 0x2D68) = (s16)charSlot;
        return 1;
    }

    highLevelSimulationFlag[0] = 0;
    return 0;
}

#undef hugeAnimStruct
#undef lbl_803CB790

typedef struct {
    /*0x00*/ u8 _00[0x1C];
    /*0x1C*/ ANIMBank* animBank;
} AnimObjectView;

typedef struct {
    /*0x0000*/ u8 _0000[0x2C50];
    /*0x2C50*/ AnimObjectView* objects;
    /*0x2C54*/ u8 _2C54[0x2CE4 - 0x2C54];
    /*0x2CE4*/ ANIMBank* characterAnimBank;
} hugeAnimStruct_view_8001c920;
#define hugeAnimStruct (*(hugeAnimStruct_view_8001c920*)&hugeAnimStruct)

typedef CompressedFileEntry* lbl_803CB790_view_8001c920;
#define lbl_803CB790 (*(lbl_803CB790_view_8001c920*)&lbl_803CB790)
typedef u8 highLevelSimulationFlag_view_8001c920[2];
#define highLevelSimulationFlag (*(highLevelSimulationFlag_view_8001c920*)&highLevelSimulationFlag)

BOOL loadCharacterAnimation(int charID) {
    if (highLevelSimulationFlag[1] == 0) {
        if (lbl_803C6CF8.cancel.bytes[1] != 1) {
            goto fail;
        }
        highLevelSimulationFlag[1] = 1;
    }
    if (highLevelSimulationFlag[1] == 1) {
        int file;

        if (g_d_GameSettings.minigamesEnabled || g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
            file = charID * 0x13 + 0x12;
        } else {
            file = charID * 0x13 + 5;
        }
        ARAMTransfer(&lbl_803CB790[file], (s32)hugeAnimStruct.characterAnimBank, 0, 0);
        highLevelSimulationFlag[1] = 2;
    } else if (highLevelSimulationFlag[1] == 2 && lbl_803C6CF8.cancel.bytes[1] == 1) {
        ANIMGet(hugeAnimStruct.characterAnimBank);
        if (hugeAnimStruct.objects->animBank == NULL) {
            hugeAnimStruct.objects->animBank = hugeAnimStruct.characterAnimBank;
        }
        return TRUE;
    }
fail:
    highLevelSimulationFlag[0] = 0;
    return FALSE;
}

#undef highLevelSimulationFlag
#undef hugeAnimStruct
#undef lbl_803CB790

typedef struct {
    /* 0x00 */ u8 data[0xA];
} LightInput;

/* Per-stadium light settings; the mini-game variants follow the six stadiums. */
typedef struct {
    /* 0x00 */ LightInput lights[4];
    /* 0x28 */ u8 _28[4];
} StadiumLightInput_8001cbd4; // size: 0x2C

typedef struct {
    /* 0x00 */ Vec dir;
    /* 0x0C */ u8 _0C[4];
} LightState; // size: 0x10

typedef StadiumLightInput_8001cbd4 inputParams_view_8001cbd4[];
#define inputParams (*(inputParams_view_8001cbd4*)&inputParams)
typedef LightState lbl_80367318_view_8001cbd4[4];
#define lbl_80367318 (*(lbl_80367318_view_8001cbd4*)&lbl_80367318)

static inline void setLightDirection(LightState* light) {
    Vec dir;

    dir.x = light->dir.x;
    dir.y = light->dir.y;
    dir.z = light->dir.z;
    PSVECNormalize(&dir, &dir);
    updateVectorInArray(0, dir);
}

static inline void loadStadiumLights(u8 stadium) {
    int i;

    for (i = 0; i < 4; i++) {
        characterLightingRelated(&inputParams[stadium].lights[i], &lbl_80367318[i]);
    }
}

void fn_8001CA40(u8 stadium) {
    g_d_GameSettings._54 = stadium;
    loadStadiumLights(stadium);
    setLightDirection(&lbl_80367318[0]);
}

void fn_8001CB10(u8 (*lights)[10], int count) {
    int i;

    for (i = 0; i < count; i++) {
        characterLightingRelated(lights[i], &lbl_80367318[i]);
    }
    setLightDirection(&lbl_80367318[0]);
}

void initStadiumLighting(void) {
    int stadium;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        stadium = g_d_GameSettings.StadiumID + 7;
    } else {
        stadium = g_d_GameSettings.StadiumID;
    }
    g_d_GameSettings._54 = stadium;
    loadStadiumLights(stadium);
    setLightDirection(&lbl_80367318[0]);
}

#undef inputParams
#undef lbl_80367318

extern f32 lbl_803CC4B8;
extern f32 lbl_803CC4F0;

typedef struct {
    /*0x0000*/ u8 _00[0x6C];
    /*0x006C*/ void* propEntries;
    /*0x0070*/ u8 _70[0xAC - 0x70];
    /*0x00AC*/ void* lights[4];
    /*0x00BC*/ u8 _BC[0x3085 - 0xBC];
    /*0x3085*/ u8 _3085;
    /*0x3086*/ u8 _3086[0x3154 - 0x3086];
} hugeAnimStruct_view_8001ce74;
#define hugeAnimStruct (*(hugeAnimStruct_view_8001ce74*)&hugeAnimStruct)

void stadiumSetupRelated(void) {
    StadiumLightParams* params;
    s32 stadium;
    s32 i;
    Vec dir;
    GXColor color;

    hugeAnimStruct._3085 = 4;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        stadium = g_d_GameSettings.StadiumID + 7;
    } else {
        stadium = g_d_GameSettings.StadiumID;
    }
    params = &inputParams[(u8)stadium];
    g_d_GameSettings._54 = stadium;

    for (i = 0; i < 4; i++) {
        characterLightingRelated(params->lights[i], &lbl_80367318[i]);
    }

    dir.x = lbl_80367318[0].pos.x;
    dir.y = lbl_80367318[0].pos.y;
    dir.z = lbl_80367318[0].pos.z;
    PSVECNormalize(&dir, &dir);
    updateVectorInArray(0, dir);
    fn_800BD2DC();

    if (inputParams[g_d_GameSettings._54].ambient.a != 0) {
        adjustLightingParams(1, inputParams[g_d_GameSettings._54].ambient);
    }

    for (i = 0; i < 4; i++) {
        LITAlloc(&hugeAnimStruct.lights[i]);
        LITInitAttn(hugeAnimStruct.lights[i], lbl_803CC4F0, lbl_803CC4B8, lbl_803CC4B8, lbl_803CC4F0,
                    lbl_803CC4B8, lbl_803CC4B8);
        LITInitPos(hugeAnimStruct.lights[i], lbl_80367318[i].pos.x, lbl_80367318[i].pos.y,
                   lbl_80367318[i].pos.z);
        color = lbl_80367318[i].color;
        LITInitColor(hugeAnimStruct.lights[i], &color);
    }

    if (hugeAnimStruct.propEntries != NULL) {
        for (i = 0; i < *(u16*)hugeAnimStruct.propEntries; i++) {
            fn_800BD548((u8*)hugeAnimStruct.propEntries + i * 0x90 + 0x34, 4, hugeAnimStruct.lights[0],
                        hugeAnimStruct.lights[1], hugeAnimStruct.lights[2], hugeAnimStruct.lights[3]);
        }
    }
}

extern void fn_800196D8(void);

void fn_80019A60(void) {
    DrawingSceneStruct* task;
    s32 i;
    Vec dir;
    GXColor color;

    task = insertGraphicDrawingFunction(fn_800196D8, 0);
    *(u8*)&task->unk_14 = 0;
    task->currentDrawingItem->state = 0;

    for (i = 0; i < 4; i++) {
        characterLightingRelated(inputParams[g_d_GameSettings._54].lights[i], &lbl_80367318[i]);
    }

    dir.x = lbl_80367318[0].pos.x;
    dir.y = lbl_80367318[0].pos.y;
    dir.z = lbl_80367318[0].pos.z;
    PSVECNormalize(&dir, &dir);
    updateVectorInArray(0, dir);
    fn_800BD2DC();

    if (inputParams[g_d_GameSettings._54].ambient.a != 0) {
        adjustLightingParams(1, inputParams[g_d_GameSettings._54].ambient);
    }

    for (i = 0; i < 4; i++) {
        LITAlloc(&hugeAnimStruct.lights[i]);
        LITInitAttn(hugeAnimStruct.lights[i], lbl_803CC4F0, lbl_803CC4B8, lbl_803CC4B8, lbl_803CC4F0,
                    lbl_803CC4B8, lbl_803CC4B8);
        LITInitPos(hugeAnimStruct.lights[i], lbl_80367318[i].pos.x, lbl_80367318[i].pos.y,
                   lbl_80367318[i].pos.z);
        color = lbl_80367318[i].color;
        LITInitColor(hugeAnimStruct.lights[i], &color);
    }

    if (hugeAnimStruct.propEntries != NULL) {
        for (i = 0; i < *(u16*)hugeAnimStruct.propEntries; i++) {
            fn_800BD548((u8*)hugeAnimStruct.propEntries + i * 0x90 + 0x34, 4, hugeAnimStruct.lights[0],
                        hugeAnimStruct.lights[1], hugeAnimStruct.lights[2], hugeAnimStruct.lights[3]);
        }
    }
}

#undef hugeAnimStruct

typedef struct {
    u8 _00[0x68];
    u8* models;
} hugeAnimStruct_view_8001d0d0;
#define hugeAnimStruct (*(hugeAnimStruct_view_8001d0d0*)&hugeAnimStruct)

void applyUniformScaleToObject(f32 scale, int model) {
    CTRLSetScale((Control*)(hugeAnimStruct.models + model * 0x90 + 0x44), scale, scale, scale);
}

#undef hugeAnimStruct

typedef struct {
    u8 _00[0x68];
    u8* models;
} hugeAnimStruct_view_8001d110;
#define hugeAnimStruct (*(hugeAnimStruct_view_8001d110*)&hugeAnimStruct)

void applyNonUniformScaleToObject(f32 x, f32 y, f32 z, int model) {
    CTRLSetScale((Control*)(hugeAnimStruct.models + model * 0x90 + 0x44), x, y, z);
}

#undef hugeAnimStruct

typedef struct {
    u8 _00[0x64];
    u8* balls;
} hugeAnimStruct_view_8001d148;
#define hugeAnimStruct (*(hugeAnimStruct_view_8001d148*)&hugeAnimStruct)

void baseballCTRLSetScale(f32 x, f32 y, f32 z, int model) {
    CTRLSetScale((Control*)(hugeAnimStruct.balls + model * 0x90 + 0x44), x, y, z);
}

#undef hugeAnimStruct

#define NO_BONE 0xFFFF

typedef struct HandModelEntry {
    /* 0x00 */ u8 _00[0x34];
    /* 0x34 */ Actor* actor;
    /* 0x38 */ u8 _38[0x90 - 0x38];
} HandModelEntry;

typedef struct HandOwner {
    /* 0x00 */ u8 _00[0x60];
    /* 0x60 */ u8 evenSlotModel;
    /* 0x61 */ u8 _61[0xC4 - 0x61];
    /* 0xC4 */ u8 oddSlotModel;
} HandOwner;

/* An entry of the hugeAnimStruct object table at +0x2C50. */
typedef struct HandObject {
    /* 0x000 */ Actor* actors[1];
    /* 0x004 */ u8 _004[0x30 - 0x04];
    /* 0x030 */ HandOwner* owner;
    /* 0x034 */ u8 _034[0x162 - 0x34];
    /* 0x162 */ u16 partBones[(0x252 - 0x162) / 2];
    /* 0x252 */ E(s8, CHAR_ID) charId;
} HandObject;



extern u8 handAttachBoneIDs[8];
typedef s16 lbl_800EEAAC_view_8001d180[NUM_CHOOSABLE_CHARACTERS];
#define lbl_800EEAAC (*(lbl_800EEAAC_view_8001d180*)&lbl_800EEAAC)

static inline s32 getHandBone(s32 playerIdx, s32 slot) {
    HandObject* obj = ((HandObject*)hugeAnimStruct.objects[playerIdx]);
    if (obj != NULL) {
        return obj->partBones[handAttachBoneIDs[slot]];
    }
    return NO_BONE;
}

// Gives `bone` the display object of the last bone of `src` that has one.
static inline void copyLastDispObj(sBone* bone, Actor* src) {
    s32 n = src->totalBones;
    sBone** p = src->boneArray + n;

    do {
        sBone* b = *--p;
        n--;
        if (b->dispObj != NULL) {
            bone->dispObj = b->dispObj;
            return;
        }
    } while (n != 0);
}

void setHandModelAttached(s32 playerIdx, s32 slot, BOOL attach) {
    HandOwner* owner;
    HandObject* obj = ((HandObject*)hugeAnimStruct.objects[playerIdx]);
    s32 boneID;
    Actor* actor;
    sBone* bone;
    Actor* src;
    s32 i;

    boneID = getHandBone(playerIdx, slot);
    if (boneID == NO_BONE) {
        return;
    }

    i = 0;
    do {
        actor = obj->actors[i];
        if (!attach) {
            if (actor != NULL && (bone = actor->boneArray[boneID]) != NULL) {
                bone->dispObj = NULL;
            }
        } else if (lbl_800EEAAC[obj->charId] >= 0) {
            owner = obj->owner;
            if (owner != NULL) {
                bone = actor->boneArray[boneID];
                if (slot & 1) {
                    src = hugeAnimStruct.modelEntries[owner->oddSlotModel].actor;
                } else {
                    src = hugeAnimStruct.modelEntries[owner->evenSlotModel].actor;
                }
                if (src == NULL) {
                    return;
                }
                copyLastDispObj(bone, src);
                return;
            }
        }
    } while (i-- != 0);
}

#undef NO_BONE
#undef lbl_800EEAAC

extern u8 drawStadiumRelated;
extern void (*lbl_803CB7AC[2])(Mtx view, int flag, u32 pass);

void fn_8001E460(void (*func)(Mtx view, int flag, u32 pass)) {
    lbl_803CB7AC[drawStadiumRelated] = func;
}

void setNullPtrForStadiumObjs(void) {
    lbl_803CB7AC[0] = NULL;
    lbl_803CB7AC[1] = NULL;
}

#define STADIUM_POOL_OBJECT_SIZE 0x27C
#define STADIUM_POOL_COUNT 13

typedef struct StadiumResetView {
    /*0x0000*/ u8 _0000[0x0004];
    /*0x0004*/ s32 _0004;
    /*0x0008*/ s32 _0008;
    /*0x000C*/ s32 _000C[0x15];
    /*0x0060*/ s32 _0060[5];
    /*0x0074*/ u8 _0074[0x0C04 - 0x0074];
    /*0x0C04*/ u8 pool[STADIUM_POOL_COUNT][STADIUM_POOL_OBJECT_SIZE];
    /*0x2C50*/ void* objects[STADIUM_POOL_COUNT];
    /*0x2C84*/ s32 _2C84[(0x2D6A - 0x2C84) / 4];
    /*0x2D6A*/ s8 _2D6A[0x2D90 - 0x2D6A];
    /*0x2D90*/ s32 _2D90[4];
    /*0x2DA0*/ u8 _2DA0[0x307A - 0x2DA0];
    /*0x307A*/ u8 _307A;
    /*0x307B*/ u8 _307B[0x307C - 0x307B];
    /*0x307C*/ u8 _307C;
    /*0x307D*/ u8 _307D;
    /*0x307E*/ u8 _307E;
    /*0x307F*/ u8 _307F[0x3085 - 0x307F];
    /*0x3085*/ u8 _3085;
    /*0x3086*/ u8 _3086;
    /*0x3087*/ u8 _3087;
    /*0x3088*/ u8 _3088[0x308C - 0x3088];
    /*0x308C*/ s32 _308C;
} StadiumResetView;

typedef StadiumResetView hugeAnimStruct_view_8001f228;
#define hugeAnimStruct (*(hugeAnimStruct_view_8001f228*)&hugeAnimStruct)

void DrawShadows(u8 enable);

void resetGameStadiumStateOnExit(void) {
    s32 i;
    s32 j;
    s32 m;

    hugeAnimStruct._307A = 0;
    hugeAnimStruct._0004 = 0;
    hugeAnimStruct._0008 = 0;
    for (i = 0; i < 0x15; i++) {
        hugeAnimStruct._000C[i] = 0;
    }

    for (i = 0; i < 5; i++) {
        hugeAnimStruct._0060[i] = 0;
    }
    for (i = 0; i < STADIUM_POOL_COUNT; i++) {
        hugeAnimStruct.pool[i][0x25C] = 0;
        hugeAnimStruct.objects[i] = NULL;
    }

    for (i = 0; i < 3; i++) {
        hugeAnimStruct._2C84[i] = 0;
    }

    for (i = 0; i < 4; i++) {
        m = i * 4;
        hugeAnimStruct._2C84[10 + i * 4 + 0] = 0;
        hugeAnimStruct._2C84[26 + m] = 0;
        hugeAnimStruct._2C84[31 + m] = 0;
        hugeAnimStruct._2C84[36 + m] = 0;
        hugeAnimStruct._2C84[41 + m] = 0;
        hugeAnimStruct._2C84[10 + i * 4 + 1] = 0;
        hugeAnimStruct._2C84[27 + m] = 0;
        hugeAnimStruct._2C84[32 + m] = 0;
        hugeAnimStruct._2C84[37 + m] = 0;
        hugeAnimStruct._2C84[42 + m] = 0;
        hugeAnimStruct._2C84[10 + i * 4 + 2] = 0;
        hugeAnimStruct._2C84[28 + m] = 0;
        hugeAnimStruct._2C84[33 + m] = 0;
        hugeAnimStruct._2C84[38 + m] = 0;
        hugeAnimStruct._2C84[43 + m] = 0;
        hugeAnimStruct._2C84[10 + i * 4 + 3] = 0;
        hugeAnimStruct._2C84[29 + m] = 0;
        hugeAnimStruct._2C84[34 + m] = 0;
        hugeAnimStruct._2C84[39 + m] = 0;
        hugeAnimStruct._2C84[44 + m] = 0;
    }

    for (i = 0; i < STADIUM_POOL_COUNT; i++) {
        hugeAnimStruct._2D6A[i] = -1;
    }

    for (i = 0; i < 4; i++) {
        hugeAnimStruct._2D90[i] = 0;
    }

    hugeAnimStruct._307C = 0;
    hugeAnimStruct._3085 = 0;
    hugeAnimStruct._308C = 0;
    hugeAnimStruct._3087 = 0;
    hugeAnimStruct._3086 = 0;
    DrawShadows(0);
}

#undef STADIUM_POOL_COUNT
#undef STADIUM_POOL_OBJECT_SIZE
#undef hugeAnimStruct

#define ANIM_OBJECT_COUNT 13
#define BALL_MODEL_COUNT 25

/* One animation-driven object in hugeAnimStruct's object pool. */
typedef struct AnimObject_8001f4c0 {
    /* 0x000 */ u8 _000[0x34];
    /* 0x034 */ f32 _34[6];
    /* 0x04C */ f32 _4C;
    /* 0x050 */ u8 _050[0x5C - 0x50];
    /* 0x05C */ u32 _5C;
    /* 0x060 */ s16 _60;
    /* 0x062 */ s16 animId;
    /* 0x064 */ s16 _64;
    /* 0x066 */ u8 _066[0x6A - 0x66];
    /* 0x06A */ s16 _6A;
    /* 0x06C */ u8 _06C[0x70 - 0x6C];
    /* 0x070 */ s16 _70;
    /* 0x072 */ u8 _072[0x25C - 0x72];
    /* 0x25C */ u8 _25C;
    /* 0x25D */ u8 _25D;
    /* 0x25E */ u8 _25E;
    /* 0x25F */ u8 _25F[0x268 - 0x25F];
    /* 0x268 */ u8 _268;
    /* 0x269 */ u8 _269[0x273 - 0x269];
    /* 0x273 */ u8 _273;
    /* 0x274 */ u8 _274;
    /* 0x275 */ u8 _275[0x278 - 0x275];
    /* 0x278 */ u8 _278;
    /* 0x279 */ u8 _279[0x27C - 0x279];
} AnimObject_8001f4c0; // size 0x27C

/* One entry of the hugeAnimStruct ball model table at +0x2D90. */
typedef struct BallModel {
    /* 0x00 */ u8 _00[4];
    /* 0x04 */ Vec pos;
    /* 0x10 */ Vec rot;
    /* 0x1C */ u8 _1C[0x26 - 0x1C];
    /* 0x26 */ E(u8, BOOL) visible;
    /* 0x27 */ u8 _27;
} BallModel; // size 0x28

/* This unit's view of hugeAnimStruct (0x3154 bytes). */
typedef struct {
    /* 0x0000 */ u8 _0000[0xC04];
    /* 0x0C04 */ AnimObject_8001f4c0 pool[ANIM_OBJECT_COUNT];
    /* 0x2C50 */ AnimObject_8001f4c0* objects[ANIM_OBJECT_COUNT];
    /* 0x2C84 */ u8 _2C84[0x2D90 - 0x2C84];
    /* 0x2D90 */ BallModel* ballModels;
    /* 0x2D94 */ u8 _2D94[0x3078 - 0x2D94];
    /* 0x3078 */ u16 _3078;
} hugeAnimStruct_view_8001f4c0;
#define hugeAnimStruct (*(hugeAnimStruct_view_8001f4c0*)&hugeAnimStruct)

void challengeMapMaybe(void) {
    int i;

    for (i = 0; i < ANIM_OBJECT_COUNT; i++) {
        AnimObject_8001f4c0* obj = &hugeAnimStruct.pool[i];

        obj->_25C = 0;
        obj->_25D = 0;
        obj->_4C = 0.5f;
        obj->_60 = 0;
        obj->animId = 0;
        obj->_64 = 0;
        obj->_6A = 0;
        obj->_25E = 1;
        obj->_268 = 0;
        obj->_273 = 0;
        obj->_274 = 0;
        obj->_278 = 0;
        obj->_5C = 0;
        obj->_34[0] = 0.0f;
        obj->_34[1] = 0.0f;
        obj->_34[2] = 0.0f;
        obj->_34[3] = 0.0f;
        obj->_34[4] = 0.0f;
        obj->_34[5] = 0.0f;
        obj->_70 = -1;
    }
    for (i = 0; i < ANIM_OBJECT_COUNT; i++) {
        if (hugeAnimStruct.objects[i] != NULL) {
            hugeAnimStruct.objects[i]->_25C = 1;
        }
    }
    for (i = 0; i < BALL_MODEL_COUNT; i++) {
        hugeAnimStruct.ballModels[i].visible = FALSE;
        hugeAnimStruct.ballModels[i].pos.x = 0.0f;
        hugeAnimStruct.ballModels[i].pos.y = 0.0f;
        hugeAnimStruct.ballModels[i].pos.z = 0.0f;
        hugeAnimStruct.ballModels[i].rot.x = 0.0f;
        hugeAnimStruct.ballModels[i].rot.y = 0.0f;
        hugeAnimStruct.ballModels[i].rot.z = 0.0f;
    }
    hugeAnimStruct._3078 = 0;
}

#undef ANIM_OBJECT_COUNT
#undef BALL_MODEL_COUNT
#undef hugeAnimStruct

typedef struct {
    void* data;
    void* geo;
    void* tex;
} PMModelSource;

typedef struct {
    u8 _0000[0x68];
    u8* modelTable;
    u8 _006C[0xAC - 0x6C];
    void* _AC[4];
    u8 _00BC[0x2D94 - 0xBC];
    PMEffect* effects;
    u8 _2D98[0x2D9C - 0x2D98];
    u32* archive;
    PMModelSource sources[27];
    u8 _2EE4[0x3078 - 0x2EE4];
    u16 effectCount;
    u8 _307A[4];
    u8 _307E;
} PMHugeAnimStruct;

typedef PMHugeAnimStruct hugeAnimStruct_view_8001f5e8;
#define hugeAnimStruct (*(hugeAnimStruct_view_8001f5e8*)&hugeAnimStruct)

void somethingFileHandlingLoadingRelated(void) {
    u32* archive;
    void* data;
    void* geo;
    void* tex;
    int i;
    s32 count;
    int off;

    count = 30;
    hugeAnimStruct.effectCount = count;

    archive = hugeAnimStruct.archive;
    hugeAnimStruct.sources[0].data = (u8*)archive + archive[0];
    hugeAnimStruct.sources[0].geo = (u8*)archive + archive[1];
    hugeAnimStruct.sources[0].tex = (u8*)archive + archive[2];
    data = hugeAnimStruct.sources[0].data;
    geo = hugeAnimStruct.sources[0].geo;
    tex = hugeAnimStruct.sources[0].tex;

    LoadActorLayout(data);
    convertGeometryAndSknHeader(geo, 0);
    haveActLayoutPointToGeoHeader(data, geo);
    convertTextureHeader(tex);
    UpdateTexturePalettePointers(geo, tex);

    hugeAnimStruct.modelTable = ActorObjectInitTable(count);

    for (i = 0, off = 0; i < 30; i++, off += 0x90) {
        animateBallRelated(hugeAnimStruct.modelTable, i, i, hugeAnimStruct.sources[0].data, 0, 0);
        fn_800BD548(hugeAnimStruct.modelTable + off + 0x34, 4, hugeAnimStruct._AC[0], hugeAnimStruct._AC[1],
                    hugeAnimStruct._AC[2], hugeAnimStruct._AC[3]);
        CTRLSetTranslation((Control*)(hugeAnimStruct.modelTable + off + 0x44), 0.0f, 0.0f, 0.0f);
        CTRLSetRotation((Control*)(hugeAnimStruct.modelTable + off + 0x44), 0.0f, 0.0f, 0.0f);
    }

    hugeAnimStruct.effects = _OSAllocFromHeap(0x20, count * sizeof(PMEffect));
    for (i = 0; i < 30; i++) {
        PMEffect* fx = &hugeAnimStruct.effects[i];
        fx->update = 0;
        fx->pos.x = 0.0f;
        fx->pos.y = 0.0f;
        fx->pos.z = 0.0f;
        fx->rot.x = 0.0f;
        fx->rot.y = 0.0f;
        fx->rot.z = 0.0f;
        fx->visible = FALSE;
    }
}

#undef hugeAnimStruct


static inline void swapShortPair(ShortsTableOwner* owner, u16 first, u16 second) {
    u16 b;
    u16 a;

    a = owner->slot[first];
    b = owner->slot[second];
    if (a != SHORT_TABLE_END && b != SHORT_TABLE_END) {
        owner->order[a] = b;
        owner->order[b] = a;
    }
}

static inline void swapShortPairs(ShortsTableOwner* owner, u16 (*pairs)[2]) {
    for (; (*pairs)[0] != SHORT_TABLE_END; pairs++) {
        swapShortPair(owner, (*pairs)[0], (*pairs)[1]);
    }
}

static inline void swapShortPairsNonEmpty(ShortsTableOwner* owner, u16 (*pairs)[2]) {
    s32 i;
    u16(*p)[2];

    p = pairs;
    i = 0;
    do {
        swapShortPair(owner, (*p)[0], (*p)[1]);
        p++;
    } while (pairs[++i][0] != SHORT_TABLE_END);
}

void initShortsHandleCompressedDiskReads(ShortsTableOwner* owner) {
    s32 i;
    u16(*pairs)[2];

    for (i = 0; i < SHORT_TABLE_COUNT; i++) {
        owner->order[i] = i;
    }

    swapShortPairsNonEmpty(owner, lbl_800EE960);

    switch (owner->charId) {
    case CHAR_ID_PARATROOPA_RED:
    case CHAR_ID_PARATROOPA_GREEN:
        pairs = lbl_803CB798;
        break;
    case CHAR_ID_PARAGOOMBA:
        pairs = lbl_800EE998;
        break;
    case CHAR_ID_BIRDO:
        pairs = lbl_803CB7A0;
        break;
    case CHAR_ID_SHYGUY_RED:
    case CHAR_ID_SHYGUY_BLUE:
    case CHAR_ID_SHYGUY_YELLOW:
    case CHAR_ID_SHYGUY_GREEN:
    case CHAR_ID_SHYGUY_BLACK:
        pairs = lbl_800EE9B0;
        break;
    default:
        pairs = NULL;
        break;
    }

    if (pairs != NULL) {
        swapShortPairs(owner, pairs);
    }
}

/* Small accessors over the animation/model state block, addressed by raw offset. */
#define HA(off)       (((u8*)&hugeAnimStruct) + (off))
#define HA_OBJ(index) (*(u8**)HA(0x2C50 + (index) * 4))

extern u32 lbl_803CBC18;
BOOL fn_8001758C(void* a, u8 b, u8 c, u8 d, u8 e, u8 f, u8 g, u8 h);

u32 fn_80011570(void) {
    return lbl_803CBC18;
}

static inline void clearObjectField5C(s8 index) {
    u8* obj;

    if (index < 0 || index >= 13) {
        return;
    }
    obj = HA_OBJ(index);
    if (obj == NULL) {
        return;
    }
    *(u32*)(obj + 0x5C) = 0;
}

typedef struct ModelStateObject {
    /* 0x00 */ u8 _00[0x62];
    /* 0x62 */ s16 frame;
    /* 0x64 */ u8 _64[0x252 - 0x64];
    /* 0x252 */ E(s8, CHAR_ID) charId;
    /* 0x253 */ u8 _253[0x255 - 0x253];
    /* 0x255 */ s8 slot;
} ModelStateObject;

extern void fn_8004B6EC(void* obj);
extern void updateSpecialBatAttach(void* obj);
extern void fn_8005240C(void* obj);

#define MODEL_ENTRY_ACTOR_FLAG(entry) (*(u8*)(*(u8**)(entry) + 0x99))

void fn_80011468(void) {
    s32 i;

    for (i = 0; i < 13; i++) {
        ModelStateObject* obj = hugeAnimStruct.objects[i];
        u8* entry;

        if (obj == NULL) {
            continue;
        }
        entry = (u8*)hugeAnimStruct.actorTable + obj->slot * 0x90 + 0x34;
        switch (obj->charId) {
        case CHAR_ID_BOWSERJR:
            fn_8004B6EC(obj);
            break;
        case CHAR_ID_GOOMBA:
        case CHAR_ID_PARAGOOMBA:
            processCharacterStateBasedOnGameMode((CharacterStateActor*)obj);
            break;
        case CHAR_ID_PETEY:
            MODEL_ENTRY_ACTOR_FLAG(entry) = 1;
            updateSpecialBatAttach(obj);
            break;
        case CHAR_ID_MONTY:
            updateSpecialBatAttach(obj);
            break;
        case CHAR_ID_BOO:
        case CHAR_ID_KINGBOO:
            fn_8005240C(obj);
            break;
        case CHAR_ID_YOSHI:
        case CHAR_ID_WARIO:
        case CHAR_ID_KOOPA_GREEN:
        case CHAR_ID_NOKI_BLUE:
        case CHAR_ID_NOKI_RED:
        case CHAR_ID_NOKI_GREEN:
        case CHAR_ID_KOOPA_RED:
            MODEL_ENTRY_ACTOR_FLAG(entry) = 1;
            break;
        case CHAR_ID_PARATROOPA_RED:
        case CHAR_ID_PARATROOPA_GREEN:
            if (obj->frame == 0x40) {
                MODEL_ENTRY_ACTOR_FLAG(entry) = 0;
            } else {
                MODEL_ENTRY_ACTOR_FLAG(entry) = 1;
            }
            break;
        }
    }
}

void fn_800126EC(ModelSlotBlock* block, void* texPalette, u8* partIndex) {
    void** loaded = block->loaded;
    void* layout = loaded[partIndex[0]];
    void* geo = loaded[partIndex[1]];
    u8* partSlot = (u8*)hugeAnimStruct.modelEntries + block->slot * 0x90 + 0x34;

    LoadActorLayout(layout);
    convertGeometryAndSknHeader(geo, NULL);
    haveActLayoutPointToGeoHeader(layout, geo);
    UpdateTexturePalettePointers(geo, texPalette);
    fn_800238E0(hugeAnimStruct.modelEntries, block->slot, block->slot, layout);

    if (block->loaded[2] != NULL) {
        adjustInternalPointers(block->loaded[partIndex[2]]);
        ACTActorRelated(block->loaded[partIndex[2]], partSlot);
    }

    block->_04 = block->loaded[partIndex[3]];
    actRelated(block->loaded[partIndex[2]], &block->_04);
}

typedef struct ModelOffsetObject {
    /* 0x000 */ u8 _000[0x34];
    /* 0x034 */ Vec pos;
    /* 0x040 */ u8 _040[0x162 - 0x40];
    /* 0x162 */ u16 partBones[5];
    /* 0x16C */ u8 _16C[0x255 - 0x16C];
    /* 0x255 */ s8 slot;
    /* 0x256 */ u8 _256[0x268 - 0x256];
    /* 0x268 */ u8 offsetApplied;
} ModelOffsetObject;

static inline u16 getRootBone(ModelOffsetObject* obj) {
    if (obj != NULL) {
        return obj->partBones[0];
    }
    return 0xFFFF;
}

static inline u16 getEndBone(ModelOffsetObject* obj) {
    if (obj != NULL) {
        return obj->partBones[4];
    }
    return 0xFFFF;
}

void fn_8001B5EC(int index, int mode) {
    ModelOffsetObject* obj = hugeAnimStruct.objects[index];
    u16 boneEnd;
    u16 boneRoot;
    u8* node;
    Vec offset;
    s32 slot;

    if (obj == NULL) {
        return;
    }
    slot = obj->slot;
    if (mode == 0) {
        boneEnd = getEndBone(obj);
        boneRoot = getRootBone(obj);
        node = (u8*)hugeAnimStruct.actorTable + (u16)slot * 0x90;
        maybeTransformVectorByAnimationMatrix(*(void**)(node + 0x34), *(u16*)(*(u8**)(node + 0x34) + 0x80), &offset);
        *(u16*)(node + 0x98) = boneRoot;
        *(u16*)(node + 0x9A) = boneEnd;
    } else {
        boneEnd = getRootBone(obj);
        boneRoot = getRootBone(obj);
        node = (u8*)hugeAnimStruct.actorTable + (u16)slot * 0x90;
        maybeTransformVectorByAnimationMatrix(*(void**)(node + 0x34), *(u16*)(*(u8**)(node + 0x34) + 0x80), &offset);
        *(u16*)(node + 0x98) = boneRoot;
        *(u16*)(node + 0x9A) = boneEnd;
    }
}

void fn_8001B4D8(int index, int apply) {
    ModelOffsetObject* obj = hugeAnimStruct.objects[index];
    u16 bone;
    u16 bone2;
    u8* node;
    u8* actors;
    Vec offset;
    Vec moved;
    s32 slot;

    if (obj == NULL) {
        return;
    }
    slot = obj->slot;
    if (apply == 0 || obj->offsetApplied != 0) {
        return;
    }
    bone = getRootBone(obj);
    bone2 = getRootBone(obj);
    actors = (u8*)hugeAnimStruct.actorTable;
    node = actors + (u16)slot * 0x90;
    maybeTransformVectorByAnimationMatrix(*(void**)(node + 0x34), *(u16*)(*(u8**)(node + 0x34) + 0x80), &offset);
    *(u16*)(node + 0x98) = bone2;
    *(u16*)(node + 0x9A) = bone;
    moved = offset;
    obj->pos.x = obj->pos.x + moved.x;
    obj->pos.y = obj->pos.y + moved.y;
    obj->pos.z = obj->pos.z + moved.z;
    obj->offsetApplied = 1;
}

extern BOOL fn_80016B60(void* record);

#define MODEL_RECORD_BASE 0xC04
#define MODEL_RECORD_SIZE 0x27C
#define MODEL_RECORD(index) (HA(MODEL_RECORD_BASE + (index) * MODEL_RECORD_SIZE))

BOOL fn_80016F7C(void) {
    if (*HA(0x2D8E) == 0) {
        *HA(0x2D8E) = 1;
        *HA(0x2D8D) = 0;
        *HA(0x2D88) = 0;
    }
    do {
        s8 cur = *HA(0x2D88);

        if (!fn_80016B60(MODEL_RECORD(cur))) {
            return FALSE;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
            u32* src = (u32*)MODEL_RECORD((s8)*HA(0x2D88));
            u32* dst = (u32*)MODEL_RECORD((s8)*HA(0x2D88) + 4);

            dst[4] = src[4];
            dst[5] = src[5];
            dst[6] = src[6];
            dst[7] = src[7];
            dst[8] = src[8];
            dst[9] = src[9];
            dst[10] = src[10];
        }
        (*HA(0x2D88))++;
    } while ((s8)*HA(0x2D88) < 4);
    return TRUE;
}

void fn_8001DD58(Actor* actor, int group, MtxPtr camera, u8 numLights, ...) {
    va_list list;
    sBone* bone;

    if (actor->unk98 & (1 << (group * 3))) {
        if (actor->skinObject != NULL) {
            GXInvalidateVtxCache();
            va_start(list, numLights);
            if (actor->skHeader != NULL) {
                DOVARender(actor->skinObject, camera, numLights, &list);
            } else {
                DOVARenderSkin(actor->skinObject, camera, actor->skinMtxArray, actor->skinInvTransposeMtxArray, numLights, &list);
            }
            va_end(list);
        }

        for (bone = (sBone*)actor->drawPriorityList.Head; bone != NULL; bone = (sBone*)bone->drawPriorityLink.Next) {
            if (bone->dispObj != NULL) {
                DOSetWorldMatrix(bone->dispObj, bone->forwardMtx);
            }
            va_start(list, numLights);
            DOVARender(bone->dispObj, camera, numLights, &list);
            va_end(list);
        }
    }
}

#define HA_U32(off) (*(u32*)HA(off))

void fn_800189E4(void) {
    u32 maxSize = 0;
    u32 size;
    u8* base;
    s32 i;

    for (i = 0; i < 54; i++) {
        u32 v = *(u32*)((u8*)lbl_803CB790 + i * 0x130 + 0xF4) & 0x0FFFFFFF;

        if (maxSize < v) {
            maxSize = v;
        }
    }

    size = (maxSize + 0x1F) & ~0x1F;
    HA_U32(0x2CA4) = size;
    base = _OSAllocFromHeap(0x20, size * 4);
    HA_U32(0x2D10) = (u32)base + size;
    HA_U32(0x2D24) = (u32)base + size * 2;
    HA_U32(0x2C88) = (u32)base;
    HA_U32(0x2CFC) = (u32)base;
    HA_U32(0xC28) = 0;
    HA_U32(0xEA4) = 0;
    HA_U32(0x1120) = 0;
    HA_U32(0x2D38) = (u32)base + size * 3;
    HA_U32(0x139C) = 0;
}

s32 fn_8001B35C(int index, int mode) {
    ModelOffsetObject* obj = hugeAnimStruct.objects[index];
    s32 steps = 0;
    s32 part = 1;
    f32 diff;
    f32 limit;
    u16 bone;
    Vec v;

    if (obj == NULL) {
        return 0;
    }
    switch (mode) {
    case 0:
        part = 3;
        break;
    case 1:
        part = 2;
        break;
    case 2:
        part = 1;
        break;
    }
    if (obj != NULL) {
        bone = obj->partBones[part];
    } else {
        bone = 0xFFFF;
    }
    if (bone == 0xFFFF) {
        diff = 0.0f;
    } else {
        maybeTransformVectorByAnimationMatrix(*(void**)((u8*)hugeAnimStruct.actorTable + obj->slot * 0x90 + 0x34), bone, &v);
        diff = v.y + obj->pos.y;
    }
    diff = diff - obj->pos.y;
    if (diff < 0.0f) {
        if (diff >= -30.0f) {
            limit = -0.5f;
            steps = 1;
            while (!(diff > limit)) {
                limit -= 0.5f;
                steps++;
            }
        }
    } else if (diff >= 0.5f && diff < 30.0f) {
        limit = 0.5f;
        while (!(diff < limit)) {
            limit += 0.5f;
            steps--;
        }
    }
    return steps;
}

void fn_80011578(void) {
    s8 i;

    for (i = 0; i < 13; i++) {
        clearObjectField5C(i);
    }
}

void fn_800115C8(s8 index) {
    clearObjectField5C(index);
}

void fn_80011604(s8 index, u32 value) {
    u8* obj;

    if (index < 0 || index >= 13) {
        return;
    }
    obj = HA_OBJ(index);
    if (obj == NULL) {
        return;
    }
    *(u32*)(obj + 0x5C) = value;
}

void fn_80011B64(int index) {
    u8** slot = (u8**)HA(0x2C50 + index * 4);
    u8* part;

    if (*slot == NULL) {
        return;
    }
    part = *(u8**)(*slot + 0x2C);
    if (part != NULL) {
        part[0x61] = -1;
        part[0x5C] = -2;
        *(u8**)(*slot + 0x2C) = NULL;
    }
    part = *(u8**)(*slot + 0x30);
    if (part == NULL) {
        return;
    }
    part[0xD1] = part[0xD0];
    part[0xD0] = -1;
    part[0x5C] = -2;
    part[0xC0] = -2;
    *(u8**)(*slot + 0x30) = NULL;
}

void fn_80014990(int index, void* file, u32 value) {
    u8* obj;
    u8* effect;

    if (index < 0 || index >= 13) {
        return;
    }
    obj = HA_OBJ(index);
    if (obj == NULL) {
        return;
    }
    effect = lbl_80118220 + index * 0x64;
    *(u8**)(obj + 0x2C) = effect;
    effect[0x60] = obj[0x252];
    effect[0x61] = obj[0x254];
    *(u32*)(effect + 4) = value;
    *(void**)(effect + 0x30) = file;
    actRelated(file, effect + 4);
}

void fn_800177B4(void) {
    DrawingSceneStruct* item = currentDrawingItem;

    if (fn_8001758C((u8*)item + 0x14, ((u8*)item)[0x1C], ((u8*)item)[0x16], ((u8*)item)[0x19], ((u8*)item)[0x1A],
                    ((u8*)item)[0x1B], ((u8*)item)[0x15], ((u8*)item)[0x1D])) {
        *HA(0x2D77) = 2;
        removeCurrentDrawingItem();
    }
}

void fn_800189B8(void) {
    fn_800ACFB0(*(void**)HA(0x2C88));
}

void fn_80018B38(void) {
    fn_800ACFB0(*(void**)HA(0x2C88));
    *(s16*)HA(0x2D68) = -1;
}

void fn_8001AAA4(void) {
    DrawingSceneStruct* item = insertGraphicDrawingFunction(challengeMapRelated, 0);

    ((u8*)item)[0x14] = 0;
    item->currentDrawingItem->state = 0;
    *HA(0x3082) = 0;
    lbl_803CBBF0 = 0;
}

void fn_8001AAF0(void) {
    fn_8003AC90();
}

void fn_8001B200(void) {
    *(u32*)HA(0x308C) = 0;
}

void fn_8001B214(void (*func)(void)) {
    *(void (**)(void))HA(0x308C) = func;
}

void fn_8001B308(int index, int attach) {
    u8* obj = HA_OBJ(index);
    u8* node;

    if (obj == NULL) {
        return;
    }
    node = (u8*)hugeAnimStruct.actorTable + (s8)obj[0x255] * 0x90 + 0x34;
    if (attach != 0) {
        *(u8**)(node + 0x68) = obj + 0x72;
    } else {
        *(u8**)(node + 0x68) = NULL;
    }
}

void fn_8001C528(void) {
    u8* p = HA(0);
    s32 i;

    for (i = 0; i < 13; i++) {
        *(s16*)(p + 0xC64) = -1;
        *(s16*)(p + 0xC66) = -1;
        *(s16*)(p + 0xC68) = -1;
        *(s16*)(p + 0xC6A) = -1;
        *(s16*)(p + 0xC6C) = 0;
        *(s16*)(p + 0xC6E) = 0;
        p[0xE62] = 1;
        p[0xE63] = 0;
        p[0xE66] = 0;
        p[0xE6C] = 0;
        p[0xE6D] = 0;
        p[0xE6E] = 0;
        p[0xE6F] = 0;
        p[0xE73] = 0;
        p += 0x27C;
    }
}

void fn_8001D074(int index, int enable) {
    u8* obj = HA_OBJ(index);
    u8* node;

    if (obj == NULL) {
        return;
    }
    node = *(u8**)((u8*)hugeAnimStruct.actorTable + (s8)obj[0x255] * 0x90 + 0x34);
    if (enable != 0) {
        node[0x98] |= 4;
    } else {
        node[0x98] &= ~4;
    }
}

void fn_8001FDD4(u8* obj) {
    if (*(void**)(obj + 0x70) != NULL) {
        setLITLightPtr(*(void**)(obj + 0x70));
    }
}

extern Mtx identityMtx;
extern Mtx lbl_800E6630;
extern f32 lbl_803CC4B8;
extern u8 destAnimStructs[0x204C];
void fn_8001BE50(s32 index, s16 a, u8 b, u8 c, s16 d, u8 e, s32 f);
void fn_80017814(void* record);
void fn_800B2D5C(void* ptr);

typedef struct MtxCopy {
    Mtx m;
} MtxCopy;

void fn_80011640(void* a, void* b) {
    MtxCopy tmp = *(MtxCopy*)lbl_800E6630;

    PSMTXConcat(tmp.m, (f32(*)[4])a, (f32(*)[4])b);
}

void fn_800116DC(StadiumModel* a, Mtx m, u16 index) {
    MtxCopy tmp = *(MtxCopy*)identityMtx;
    Mtx local;
    f32(*dst)[4];

    PSMTXConcat(tmp.m, m, local);
    local[0][3] = lbl_803CC4B8;
    local[1][3] = lbl_803CC4B8;
    local[2][3] = lbl_803CC4B8;
    PSMTXInverse(local, local);
    dst = *(f32(**)[4])(*(u8**)(*(u8**)(*(u8**)a + 0x18) + index * 4) + 0xEC);
    local[0][3] = dst[0][3];
    local[1][3] = dst[1][3];
    local[2][3] = dst[2][3];
    PSMTXCopy(local, dst);
}

void fn_800117CC(Mtx a, Mtx m, Mtx out) {
    MtxCopy tmp = *(MtxCopy*)identityMtx;
    Mtx local;

    PSMTXConcat(tmp.m, m, local);
    local[0][3] = lbl_803CC4B8;
    local[1][3] = lbl_803CC4B8;
    local[2][3] = lbl_803CC4B8;
    PSMTXInverse(local, local);
    local[0][3] = a[0][3];
    local[1][3] = a[1][3];
    local[2][3] = a[2][3];
    PSMTXCopy(local, out);
}

f32 (*fn_800118AC(Mtx a, Mtx out))[4] {
    MtxCopy tmp = *(MtxCopy*)identityMtx;

    PSMTXConcat(tmp.m, a, out);
    out[0][3] = lbl_803CC4B8;
    out[1][3] = lbl_803CC4B8;
    out[2][3] = lbl_803CC4B8;
    PSMTXInverse(out, out);
    return out;
}

void fn_80011BE4(int index) {
    u8** slot = (u8**)HA(0x2C50 + index * 4);
    u8* part;
    s32 i;

    if (*slot != NULL) {
        part = *(u8**)(*slot + 0x2C);
        if (part != NULL) {
            part[0x61] = -1;
            part[0x5C] = -2;
            *(u8**)(*slot + 0x2C) = NULL;
        }
        part = *(u8**)(*slot + 0x30);
        if (part != NULL) {
            part[0xD1] = part[0xD0];
            part[0xD0] = -1;
            part[0x5C] = -2;
            part[0xC0] = -2;
            *(u8**)(*slot + 0x30) = NULL;
        }
        (*slot)[0x25C] = 0;
    }
    *slot = NULL;
    for (i = 0; i < 13; i++) {
        if ((s8)HA(0)[0x2D6A + i] == index) {
            HA(0)[0x2D6A + i] = -1;
        }
    }
}

void fn_8001B224(void) {
    s32 i;
    u8* obj;

    memcpy(HA(0xC04), destAnimStructs, 0x204C);
    for (i = 0; i < 13; i++) {
        obj = HA_OBJ(i);
        if (obj != NULL) {
            if (obj[0x25D] != 0 || i <= 8) {
                fn_8001BE50(i, *(s16*)(obj + 0x62), obj[0x25F], obj[0x262], *(s16*)(obj + 0x6A) + 1, obj[0x265], 0);
            }
        }
    }
}

void fn_80017D28(u8* obj) {
    s32 slot = (s8)obj[0x255] + 4;
    u8* rec = HA(0) + slot * 0x27C;
    u8* p;

    rec[0xE56] = obj[0x252];
    p = rec + 0xC04;
    p[0x254] = obj[0x254];
    p[0x255] = slot;
    p[0x25C] = 1;
    p[0x25D] = 0;
    *(u32*)(p + 0x30) = *(u32*)(obj + 0x30);
    p[0x25A] = obj[0x25A];
    p[0x25B] = obj[0x25B];
    *(u32*)(p + 8) = *(u32*)(obj + 0xC);
    fn_80017814(p);
}

void fn_8001F16C(void) {
    u8* node;
    u8* obj;
    s32 i;
    u8* actors;

    if (*HA(0x307A) != 0 && *HA(0x307A) != 3) {
        actors = (u8*)hugeAnimStruct.actorTable;
        for (i = 0; i < *(u16*)actors; i++) {
            obj = HA_OBJ(i);
            if (obj != NULL) {
                node = (u8*)hugeAnimStruct.actorTable + (s8)obj[0x255] * 0x90 + 0x34;
                if (*(void**)node != NULL && node[0x6C] != 0) {
                    fn_800B2D5C(*(void**)node);
                }
            }
        }
    }
}

void fn_8001196C(void) {
    s32 idx;
    s32 i;
    u8** slot;
    u8* part;

    for (idx = 0; idx < 9; idx++) {
        slot = (u8**)HA(0x2C50 + idx * 4);
        if (*slot != NULL && *(u8**)(*slot + 0x2C) != NULL && (s8)(*slot)[0x254] == idx) {
            part = *(u8**)(*slot + 0x2C);
            part[0x61] = -1;
            part[0x5C] = -2;
            *(u8**)(*slot + 0x2C) = NULL;
        }
        if (*slot != NULL && *(u8**)(*slot + 0x30) != NULL && (s8)(*slot)[0x254] == idx) {
            part = *(u8**)(*slot + 0x30);
            part[0xD1] = part[0xD0];
            part[0xD0] = -1;
            part[0x5C] = -2;
            part[0xC0] = -2;
            *(u8**)(*slot + 0x30) = NULL;
        }
        (*slot)[0x25C] = 0;
        *slot = NULL;
        for (i = 0; i < 13; i++) {
            if ((s8)HA(0)[0x2D6A + i] == idx) {
                HA(0)[0x2D6A + i] = -1;
            }
        }
    }
}

void fn_80011A60(void) {
    s32 n;
    s32 idx;
    s32 i;
    u8** slot;
    u8* part;

    for (n = 0; n < 4; n++) {
        idx = n + 9;
        slot = (u8**)HA(0x2C50 + idx * 4);
        if (*slot != NULL && *(u8**)(*slot + 0x2C) != NULL && (s8)(*slot)[0x254] == idx) {
            part = *(u8**)(*slot + 0x2C);
            part[0x61] = -1;
            part[0x5C] = -2;
            *(u8**)(*slot + 0x2C) = NULL;
        }
        if (*slot != NULL && *(u8**)(*slot + 0x30) != NULL && (s8)(*slot)[0x254] == idx) {
            part = *(u8**)(*slot + 0x30);
            part[0xD1] = part[0xD0];
            part[0xD0] = -1;
            part[0x5C] = -2;
            part[0xC0] = -2;
            *(u8**)(*slot + 0x30) = NULL;
        }
        if (*slot != NULL) {
            (*slot)[0x25C] = 0;
            *slot = NULL;
        }
        for (i = 0; i < 13; i++) {
            if ((s8)HA(0)[0x2D6A + i] == idx) {
                HA(0)[0x2D6A + i] = -1;
            }
        }
    }
}

void fn_800188C0(void) {
    DrawingSceneStruct* item = currentDrawingItem;

    switch (((u8*)item)[0x14]) {
    case 0:
        if (g_d_GameSettings.GameModeSelected == 6) {
            *(void**)HA(0x2C84) = ARAMTransfer(&BallModelFiles[1], 0, 0, 0);
        } else {
            *(void**)HA(0x2C84) = ARAMTransfer(BallModelFiles, 0, 0, 0);
        }
        ((u8*)item)[0x14]++;
        break;
    case 1:
        if (lbl_803C6CF8.cancel.bytes[1] == 1) {
            ((u8*)item)[0x14]++;
        }
        break;
    case 2:
        *HA(0x307B) = 0;
        removeCurrentDrawingItem();
        break;
    }
}
