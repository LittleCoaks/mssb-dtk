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
#include "Unknown/File_0x800bd8c4.h"
#include "Unknown/File_0x80052734.h"

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

static inline u8* getObject(s32 slot) {
    return ((u8**)(hugeAnimStruct + OBJECT_TABLE_OFFSET))[slot];
}

static inline void linkHandAttachBone(u8* obj, s32 which) {
    s32 bone;

    if (obj != NULL) {
        bone = FIELD_U16(obj, 0x162 + handAttachBoneIDs[which] * 2);
    } else {
        bone = NO_BONE;
    }
    if (bone != NO_BONE) {
        s16 n = lbl_800EEAAC[FIELD_S8(obj, 0x252)];
        s32 j;

        j = 0;
        do {
            u8* act = ((u8**)obj)[j];

            if (n >= 0 && FIELD_PTR(obj, 0x30) != NULL) {
                u8* node = ((u8**)FIELD_PTR(act, 0x18))[bone];
                u8* parts = FIELD_PTR(FIELD_PTR(hugeAnimStruct, ENTRY_TABLE_OFFSET) +
                                          FIELD_U8(FIELD_PTR(obj, 0x30), 0x60 + which * 0x64) * ENTRY_STRIDE,
                                      0x34);

                if (parts != NULL) {
                    s32 i;

                    u8** p;

                    i = FIELD_U16(parts, 0x6);
                    p = (u8**)FIELD_PTR(parts, 0x18) + i;
                    do {
                        u8* cand = *--p;
                        i--;

                        if (FIELD_U32(cand, 0x14) != 0) {
                            FIELD_U32(node, 0x14) = FIELD_U32(cand, 0x14);
                            break;
                        }
                    } while (i != 0);
                }
                return;
            }
        } while (j-- != 0);
    }
}

static inline u8 attachHandModel(u32 tex) {
    u8* block;
    s32 i;
    u8* layout;
    u8* geo;
    u8* partSlot;
    u8 ret;

    if (lbl_803716B8[0x1E8] == 0) {
        block = lbl_803CBC1C;
        lbl_803CBC0C = 0;
        for (i = 0; i < 4; i++) {
            if (((u32*)FIELD_PTR(block, 0))[i] != 0) {
                ((u32*)FIELD_PTR(block, 0))[i] = (u32)FIELD_PTR(block, 0) + ((u32*)FIELD_PTR(block, 0))[i];
            }
        }
        layout = ((u8**)FIELD_PTR(block, 0))[lbl_803CB7C4[0]];
        geo = ((u8**)FIELD_PTR(block, 0))[lbl_803CB7C4[1]];
        partSlot = FIELD_PTR(hugeAnimStruct, ENTRY_TABLE_OFFSET) + FIELD_U8(block, 0x60) * ENTRY_STRIDE + 0x34;
        LoadActorLayout(layout);
        convertGeometryAndSknHeader(geo, NULL);
        haveActLayoutPointToGeoHeader(layout, geo);
        UpdateTexturePalettePointers((UnkTexPalGeo*)geo, (void*)tex);
        fn_800238E0(FIELD_PTR(hugeAnimStruct, ENTRY_TABLE_OFFSET), FIELD_U8(block, 0x60), FIELD_U8(block, 0x60), layout);
        if (((u8**)FIELD_PTR(block, 0))[2] != NULL) {
            adjustInternalPointers(((u8**)FIELD_PTR(block, 0))[lbl_803CB7C4[2]]);
            ACTActorRelated(((u8**)FIELD_PTR(block, 0))[lbl_803CB7C4[2]], partSlot);
        }
        FIELD_PTR(block, 0x4) = ((u8**)FIELD_PTR(block, 0))[lbl_803CB7C4[3]];
        actRelated(((u8**)FIELD_PTR(block, 0))[lbl_803CB7C4[2]], block + 0x4);
    lbl_803CBC1C = NULL;
        ret = TRUE;
    } else {
        ret = FALSE;
    }
    return ret;
}

BOOL animateModelArmsGlovesBats(void* actorPtr) {
    u8* actor = actorPtr;
    s32 charSlot = FIELD_S8(actor, 0x252);
    s32 part = FIELD_S8(actor, 0x254);
    BOOL lowPart;
    BOOL selSet;
    s32 sel;
    u8 i;
    u8 k;
    u8* rec;
    u8* sub;
    u32 tex;
    s32 kind;
    BOOL match;
    u8 ready;

    if (lbl_803CBBFB == 0) {
        lbl_803CBBFB = 1;
        lbl_803CBC00 = FIELD_U32(FIELD_PTR(actor, 0x8), 0);

        for (i = 0; i < RECORD_COUNT; i++) {
            rec = ((u8(*)[RECORD_STRIDE])hugeAnimStruct)[i];
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
            if (!((FIELD_S8(actor, 0x254) < 9 && FIELD_S8(rec, 0x211) < 9) ||
                  (FIELD_S8(actor, 0x254) >= 9 && FIELD_S8(rec, 0x211) >= 9))) {
                continue;
            }

            FIELD_S8(RECORD(i), 0x210) = part;
            FIELD_PTR(actor, 0x30) = rec + 0x140;
            FIELD_U8(FIELD_PTR(actor, 0x30), 0xCC) = TRUE;
            linkHandAttachBone(getObject(FIELD_S8(actor, 0x254)), 0);
            linkHandAttachBone(getObject(FIELD_S8(actor, 0x254)), 1);
            lbl_803CBBFD = 0;
            lbl_803CBBFC = 0;
            lbl_803CBBFB = 0;
            lbl_803CBC00 = 0;
            return TRUE;
        }

        if (lbl_803CBBFC == 0 && lbl_803CBBFD == 0) {
            for (i = 0; i < RECORD_COUNT; i++) {
                if (FIELD_S8(RECORD(i), 0x210) == FIELD_S8(actor, 0x254) && FIELD_S8(RECORD(i), 0x210) < 9) {
                    FIELD_S8(RECORD(i), 0x210) = -1;
                    break;
                }
            }

            for (i = 0; i < RECORD_COUNT; i++) {
                rec = ((u8(*)[RECORD_STRIDE])hugeAnimStruct)[i];
                if (FIELD_S8(rec, 0x210) == -1) {
                    lbl_803CBC20 = rec + 0x140;
                    FIELD_U32(rec, 0x208) = lbl_803CBC00;
                    FIELD_S8(RECORD(i), 0x20F) = charSlot;
                    FIELD_U8(RECORD(i), 0x211) = FIELD_U8(RECORD(i), 0x210);
                    FIELD_S8(RECORD(i), 0x210) = part;
                    FIELD_U8(RECORD(i), 0x20D) = FIELD_U8(actor, 0x25A);
                    FIELD_U8(RECORD(i), 0x20E) = FIELD_U8(actor, 0x25B);
                    break;
                }
            }

            if (i == RECORD_COUNT) {
                for (i = 0; i < RECORD_COUNT; i++) {
                    sub = RECORD(i) + 0x140;
                    lbl_803CBC20 = sub;
                    for (k = 0; k < RECORD_COUNT; k++) {
                        u8* obj = getObject(k);
                        if (obj != NULL && FIELD_S8(sub, 0xCF) == FIELD_S8(obj, 0x252)) {
                            break;
                        }
                    }
                    if (k == RECORD_COUNT) {
                        FIELD_U32(sub, 0xC8) = lbl_803CBC00;
                        FIELD_S8(RECORD(i), 0x20F) = charSlot;
                        FIELD_U8(RECORD(i), 0x211) = FIELD_U8(RECORD(i), 0x210);
                        FIELD_S8(RECORD(i), 0x210) = part;
                        FIELD_U8(RECORD(i), 0x20D) = FIELD_U8(actor, 0x25A);
                        FIELD_U8(RECORD(i), 0x20E) = FIELD_U8(actor, 0x25B);
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

    if (part < 9) {
        sel = FIELD_U8(actor, 0x25A);
    } else {
        sel = FIELD_U8(actor, 0x25B);
    }
    lowPart = part < 9;
    selSet = sel != 0;

    for (;;) {
        if (lbl_803CBBFC == 0) {
            tex = lbl_803CBC00;
            sub = lbl_803CBC20;
            match = selSet == lowPart;
            if (lbl_803CBC0C == 0 && ((s8*)&lbl_803C6CF8)[0x715] == 1) {
                if (lowPart && FIELD_U8(sub, 0xCD) != 0) {
                    kind = 3;
                } else if (match) {
                    kind = 5;
                } else {
                    kind = 1;
                }
                lbl_803CBC1C = sub + 0x64;
                lbl_803CBC0C = 1;
                loadCharacterHandItem(FIELD_S8(sub, 0xCF), kind, FIELD_PTR(sub + 0x64, 0));
            }
            ready = attachHandModel(tex);
            if (!ready) {
                break;
            }
            lbl_803CBBFC = 1;
        } else {
            if (lbl_803CBBFD == 0) {
                tex = lbl_803CBC00;
                sub = lbl_803CBC20;
                match = selSet == lowPart;
                if (lbl_803CBC0C == 0 && ((s8*)&lbl_803C6CF8)[0x715] == 1) {
                    if (lowPart && FIELD_U8(sub, 0xCD) != 1) {
                        kind = 2;
                    } else if (match) {
                        kind = 4;
                    } else {
                        kind = 0;
                    }
                    lbl_803CBC1C = sub;
                    lbl_803CBC0C = 1;
                    loadCharacterHandItem(FIELD_S8(sub, 0xCF), kind, FIELD_PTR(sub, 0));
                }
                ready = attachHandModel(tex);
                if (ready) {
                    lbl_803CBBFD = 1;
                }
            }
            break;
        }
    }

    if (lbl_803CBBFC == 0 || lbl_803CBBFD == 0) {
        return FALSE;
    }

    FIELD_PTR(actor, 0x30) = lbl_803CBC20;
    linkHandAttachBone(getObject(FIELD_S8(actor, 0x254)), 0);
    linkHandAttachBone(getObject(FIELD_S8(actor, 0x254)), 1);
    FIELD_U8(FIELD_PTR(actor, 0x30), 0xCC) = TRUE;
    lbl_803CBC20 = NULL;
    lbl_803CBBFB = 0;
    lbl_803CBBFD = 0;
    lbl_803CBBFC = 0;
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
    s32 entry;
    u32 maxA;
    s32 i;
    u32 maxB;
    u32 v;
    u32 sizeA;
    u32 sizeB;
    u8* p;

    maxA = 0;
    maxB = 0;
    entry = 0;
    for (i = 0; i < 54; i++) {
        v = *(u32*)((u8*)lbl_803CB790 + entry * 16 + 4) & 0x0FFFFFFF;
        if (maxA < v) {
            maxA = v;
        }
        v = *(u32*)((u8*)lbl_803CB790 + (entry + 1) * 16 + 4) & 0x0FFFFFFF;
        if (maxB < v) {
            maxB = v;
        }
        entry += 19;
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

void fn_8001CCC8(void) {
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
}

extern void fn_800196D8(void);

extern void fn_80019C00(void);

void fn_8001A25C(void) {
    DrawingSceneStruct* task;
    s32 i;
    GXColor color;

    task = insertGraphicDrawingFunction(fn_80019C00, 0);
    *(u8*)&task->unk_14 = 0;
    task->currentDrawingItem->state = 0;

    for (i = 0; i < 4; i++) {
        characterLightingRelated(inputParams[g_d_GameSettings._54].lights[i], &lbl_80367318[i]);
    }

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

void fn_80019A60(void) {
    DrawingSceneStruct* task;
    s32 i;
    GXColor color;

    task = insertGraphicDrawingFunction(fn_800196D8, 0);
    *(u8*)&task->unk_14 = 0;
    task->currentDrawingItem->state = 0;

    for (i = 0; i < 4; i++) {
        characterLightingRelated(inputParams[g_d_GameSettings._54].lights[i], &lbl_80367318[i]);
    }

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

    count = hugeAnimStruct.effectCount = 30;

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

    for (i = 0; i < 30; i++) {
        animateBallRelated(hugeAnimStruct.modelTable, i, i, hugeAnimStruct.sources[0].data, 0, 0);
        fn_800BD548(hugeAnimStruct.modelTable + i * 0x90 + 0x34, 4, hugeAnimStruct._AC[0], hugeAnimStruct._AC[1],
                    hugeAnimStruct._AC[2], hugeAnimStruct._AC[3]);
        CTRLSetTranslation((Control*)(hugeAnimStruct.modelTable + i * 0x90 + 0x44), 0.0f, 0.0f, 0.0f);
        CTRLSetRotation((Control*)(hugeAnimStruct.modelTable + i * 0x90 + 0x44), 0.0f, 0.0f, 0.0f);
    }

    hugeAnimStruct.effects = _OSAllocFromHeap(0x20, count * sizeof(PMEffect));
    for (i = 0; i < count; i++) {
        hugeAnimStruct.effects[i].pos.x = 0.0f;
        hugeAnimStruct.effects[i].pos.y = 0.0f;
        hugeAnimStruct.effects[i].pos.z = 0.0f;
        hugeAnimStruct.effects[i].rot.x = 0.0f;
        hugeAnimStruct.effects[i].rot.y = 0.0f;
        hugeAnimStruct.effects[i].rot.z = 0.0f;
        hugeAnimStruct.effects[i].visible = FALSE;
        hugeAnimStruct.effects[i].update = NULL;
    }
}

#undef hugeAnimStruct


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


void fn_8001DB74(ActorObjectTable* table) {
    u16 i;
    u16 mode;

    for (i = 0; i < table->count; i++) {
        u8* obj = HA_OBJ(i);
        ActorObjectEntry* entry;

        if (obj == NULL) {
            continue;
        }
        if (obj[0x25D] == 0) {
            continue;
        }
        entry = &hugeAnimStruct.actorTable->entries[(s8)obj[0x255]];
        if (entry->actor == NULL) {
            continue;
        }
        if (entry->animPending != 0) {
            ACTSetAnimation(entry->actor, entry->anim, NULL, entry->seqNum, lbl_803CC4B8, entry->blendTime);
        }
        if (entry->framePending != 0) {
            setActorAnimFrame(entry->actor, entry->frame);
        }
        if (entry->speedPending != 0) {
            ACTSetSpeed(entry->actor, entry->speed);
        }
        if (entry->boneParam & 2) {
            updateBoneParam(entry->actor, entry->boneParam & 1);
        }
        Set_FUN_800b2b6c((UnkB2B4C*)entry->actor, entry->unk68);
        if (entry->applyControl != 0) {
            fn_800BDA24(entry);
        }
        for (mode = 0; mode < returnScissorMode(); mode++) {
            s32 shift = mode * 3;
            u8 keep = ~(3 << shift);
            u8* camera = (u8*)returnFloatFromModeIndex(mode) + 0x40;

            if (*HA(0x307A) == 5) {
                entry->actor->unk98 = 1;
            } else {
                Mtx trans;
                Actor* actor;

                PSMTXTrans(trans, *(f32*)(obj + 0x34), *(f32*)(obj + 0x38), *(f32*)(obj + 0x3C));
                PSMTXConcat((MtxPtr)camera, trans, trans);
                actor = entry->actor;
                actor->unk98 = (actor->unk98 & keep) | ((u8)fn_800B3C04(mode, (StadiumModelNode*)actor, trans) << shift);
            }
        }
        entry->animPending = 0;
        entry->framePending = 0;
        entry->speedPending = 0;
        entry->boneParam &= 1;
    }
}

void fn_8001DEA4(ActorObjectEntry* entry, int group, MtxPtr camera) {
    Actor* actor = entry->actor;
    u32* args = entry->drawArgs;

    if (entry->callback != NULL) {
        entry->callback(entry);
    }
    switch (entry->drawArgCount) {
    case 0:
        fn_8001DD58(actor, group, camera, 0);
        break;
    case 1:
        fn_8001DD58(actor, group, camera, 1, args[0]);
        break;
    case 2:
        fn_8001DD58(actor, group, camera, 2, args[0], args[1]);
        break;
    case 3:
        fn_8001DD58(actor, group, camera, 3, args[0], args[1], args[2]);
        break;
    case 4:
        fn_8001DD58(actor, group, camera, 4, args[0], args[1], args[2], args[3]);
        break;
    case 5:
        fn_8001DD58(actor, group, camera, 5, args[0], args[1], args[2], args[3], args[4]);
        break;
    case 6:
        fn_8001DD58(actor, group, camera, 6, args[0], args[1], args[2], args[3], args[4], args[5]);
        break;
    case 7:
        fn_8001DD58(actor, group, camera, 7, args[0], args[1], args[2], args[3], args[4], args[5], args[6]);
        break;
    case 8:
        fn_8001DD58(actor, group, camera, 8, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]);
        break;
    }
}

BOOL fn_80017340(int slot) {
    u8* rec = HA(MODEL_RECORD_BASE + slot * MODEL_RECORD_SIZE);
    s32 used[4];
    s32 i;
    s32 j;
    s32 free;

    if (*HA(0x2D8D) != 0) {
        if (((u8*)&lbl_803C6CF8)[0x715] == 1) {
            ANIMGet(*(void**)(rec + 0x14));
            return TRUE;
        }
        return FALSE;
    }

    used[0] = 0;
    used[1] = 0;
    used[2] = 0;
    used[3] = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            u8* obj = HA_OBJ(9 + i);

            if (obj != NULL) {
                if ((s8)rec[0x252] == (s8)*HA(0x2D89 + j)) {
                    *(u32*)(rec + 0x14) = *(u32*)HA(0x2CB0 + j * 4);
                    return TRUE;
                }
                if ((s8)obj[0x252] == (s8)*HA(0x2D89 + j)) {
                    used[j] = 1;
                    break;
                }
            }
        }
    }
    for (j = 0; j < 4; j++) {
        if (used[j] == 0) {
            *HA(0x2D89 + j) = 0xFF;
        }
    }
    for (free = 0; free < 4; free++) {
        if ((s8)*HA(0x2D89 + free) < 0) {
            break;
        }
    }
    *HA(0x2D89 + free) = rec[0x252];
    *(u32*)(rec + 0x14) = *(u32*)HA(0x2CB0 + free * 4);
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        i = (s8)rec[0x252] * 0x13 + 0xB;
    } else {
        i = (s8)rec[0x252] * 0x13 + 3;
    }
    ARAMTransfer((u8*)lbl_803CB790 + i * 16, *(s32*)(rec + 0x14), 0, 0);
    *HA(0x2D8D) = 1;
    return FALSE;
}

extern void fn_800B2BA8(Actor* actor, u16 bone, Actor* src, u16 srcBone);
extern void fn_800B2C08(Actor* actor, u16 value);
extern void fn_800B2B54(UnkB2B4C* obj, u16 index, u8 value);
extern void fn_800638B4(void* obj, void* entry);
extern void fn_80063010(void* obj, void* entry);
extern void fn_8004B7B4(void* obj, void* entry);
extern void fn_800637BC(void* obj, void* entry);
extern void fn_800637D4(void* obj, void* entry);
extern void fn_80052634(void* obj, void* entry);
extern void fn_80062ED4(void* obj, void* entry);
extern void initSpecialHandBones(void* obj, void* entry);

#define MODEL_BONE_FLAGGED(actor, bone) \
    (*(u8*)(((u8**)*(u8**)((u8*)(actor) + 0x18))[bone] + 0x136))

void fn_80017DBC(ModelOffsetObject* obj, int slot) {
    ActorObjectEntry* entry = &hugeAnimStruct.actorTable->entries[slot];
    u16 bone;

    callDSInsertListObject((UnkB2B4C*)entry->actor, *(u16*)((u8*)obj + 0x188));
    callDSInsertListObject((UnkB2B4C*)entry->actor, *(u16*)((u8*)obj + 0x194));
    callDSInsertListObject((UnkB2B4C*)entry->actor, *(u16*)((u8*)obj + 0x1AA));
    if (*(u16*)((u8*)obj + 0x168) != 0xFFFF) {
        fn_800B2B54(*(UnkB2B4C**)obj, *(u16*)((u8*)obj + 0x168), 13);
    }
    bone = *(u16*)((u8*)obj + 0x168);
    if (bone != 0xFFFF) {
        fn_800B2BA8(entry->actor, bone, NULL, 0);
        MODEL_BONE_FLAGGED(entry->actor, bone) = 1;
    }
    bone = *(u16*)((u8*)obj + 0x166);
    if (bone != 0xFFFF) {
        fn_800B2BA8(entry->actor, bone, NULL, 0);
        MODEL_BONE_FLAGGED(entry->actor, bone) = 1;
    }
    bone = *(u16*)((u8*)obj + 0x164);
    if (bone != 0xFFFF) {
        fn_800B2BA8(entry->actor, bone, NULL, 0);
        MODEL_BONE_FLAGGED(entry->actor, bone) = 1;
    }
    bone = *(u16*)((u8*)obj + 0x1AA);
    if (bone != 0xFFFF) {
        fn_800B2BA8(entry->actor, bone, NULL, 0);
    }
    bone = *(u16*)((u8*)obj + 0x1BE);
    if (bone != 0xFFFF) {
        fn_800B2BA8(entry->actor, bone, NULL, 0);
        MODEL_BONE_FLAGGED(entry->actor, bone) = 1;
    }
    fn_800B2C08(entry->actor, *(u16*)((u8*)obj + 0x16A));

    switch ((s8)*((u8*)obj + 0x252)) {
    case CHAR_ID_DK:
        fn_800638B4(obj, entry);
        break;
    case CHAR_ID_MAGIKOOPA_BLUE:
    case CHAR_ID_MAGIKOOPA_RED:
    case CHAR_ID_MAGIKOOPA_GREEN:
    case CHAR_ID_MAGIKOOPA_YELLOW:
        fn_80063010(obj, entry);
        break;
    case CHAR_ID_BOWSERJR:
        fn_8004B7B4(obj, entry);
        break;
    case CHAR_ID_PARATROOPA_RED:
    case CHAR_ID_PARATROOPA_GREEN:
        fn_800637BC(obj, entry);
        break;
    case CHAR_ID_PETEY:
        entry->actor->unk98 = 1;
        initSpecialHandBones(obj, entry);
        break;
    case CHAR_ID_PARAGOOMBA:
        fn_800637D4(obj, entry);
        initSpecialHandBones(obj, entry);
        break;
    case CHAR_ID_MONTY:
    case CHAR_ID_GOOMBA:
        initSpecialHandBones(obj, entry);
        break;
    case CHAR_ID_BOO:
    case CHAR_ID_KINGBOO:
        fn_80052634(obj, entry);
        break;
    case CHAR_ID_SHYGUY_RED:
    case CHAR_ID_SHYGUY_BLUE:
    case CHAR_ID_SHYGUY_YELLOW:
    case CHAR_ID_SHYGUY_GREEN:
    case CHAR_ID_SHYGUY_BLACK:
        fn_80062ED4(obj, entry);
        break;
    }
}

extern f32 lbl_803CC4F4;
extern void (*lbl_803CBBF4)(void);
extern void fn_8003A4C8(void);

void fn_8001AF98(void) {
    BOOL isToyField = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD;
    ShadowCamera cam;
    f32 projection[7];
    f32 viewport[6];
    Vec toEye;
    Vec dir;
    u32 scissorLeft;
    u32 scissorTop;
    u32 scissorWidth;
    u32 scissorHeight;
    camera_803c639c_s* view;
    f32 mag;

    if (*HA(0x3087) != 0 && fn_8003A538() == 0) {
        DrawShadows(*HA(0x3086));
    } else {
        DrawShadows(FALSE);
        return;
    }

    GXGetProjectionv(projection);
    GXGetViewportv(viewport);
    GXGetScissor(&scissorLeft, &scissorTop, &scissorWidth, &scissorHeight);
    fn_800BEC00(isToyField);
    if (isToyField) {
        view = returnFloatFromModeIndex(returnsCurrentMode());
        PSVECSubtract(&view->eye, &view->target, &toEye);
        toEye.y = lbl_803CC4F4 * -toEye.y;
        mag = PSVECMag(&toEye);
        if (!(mag == lbl_803CC4B8)) {
            PSVECNormalize(&toEye, &toEye);
            dir = toEye;
            updateVectorInArray(0, dir);
        }
    } else {
        fn_800BD1E8(NULL);
    }

    if (GetDrawShadows()) {
        ((Vec*)&cam)[0] = returnFloatFromModeIndex(0)->eye;
        ((Vec*)&cam)[2] = returnFloatFromModeIndex(0)->target;
        ((Vec*)&cam)[1] = returnFloatFromModeIndex(0)->Up;
        PSMTXCopy(returnFloatFromModeIndex(0)->view, cam.viewMtx);
        fn_800BE09C((u32)hugeAnimStruct.actorTable, &cam);
        fn_800BF058(fn_8001AB10);
        fn_800BDFE0((u8*)hugeAnimStruct.actorTable);
        if (*(void (**)(void))HA(0x308C) != NULL) {
            (*(void (**)(void))HA(0x308C))();
        }
        if (isToyField) {
            fn_8003A4C8();
        } else {
            fn_800BDEA0();
        }
    }

    if (lbl_803CBBF4 != NULL) {
        lbl_803CBBF4();
        lbl_803CBBF4 = NULL;
    }
    GXSetScissor(scissorLeft, scissorTop, scissorWidth, scissorHeight);
    GXSetViewport(viewport[0], viewport[1], viewport[2], viewport[3], viewport[4], viewport[5]);
    GXSetProjectionv(projection);
    GXInvalidateTexAll();
}

#define CHAR_RECORD_FIELD(i, off) (*(u32*)((u8*)lbl_803CB790 + (i) * 0x130 + (off)) & 0x0FFFFFFF)
#define ROUND_UP_32(v) (((v) + 0x1F) & ~0x1F)

void fn_80018B74(void) {
    u32 maxA = 0;
    u32 maxB = 0;
    u32 maxC = 0;
    u32 maxD = 0;
    u32 maxE = 0;
    u32 sizeA;
    u32 sizeB;
    u32 sizeC;
    u32 sizeD;
    u32 sizeE;
    u8 mode = g_d_GameSettings.GameModeSelected;
    s32 i;
    u32 v;
    u32 cursor;

    for (i = 0; i < 54; i++) {
        if (mode == GAME_TYPE_MINIGAMES) {
            v = CHAR_RECORD_FIELD(i, 0xD4);
        } else {
            v = CHAR_RECORD_FIELD(i, 0x44);
        }
        if (maxA < v) {
            maxA = v;
        }
        if (mode == GAME_TYPE_TOY_FIELD) {
            v = CHAR_RECORD_FIELD(i, 0xE4);
        } else {
            v = CHAR_RECORD_FIELD(i, 0xC4);
        }
        if (maxB < v) {
            maxB = v;
        }
        v = CHAR_RECORD_FIELD(i, 0x124);
        if (maxC < v) {
            maxC = v;
        }
        if (mode == GAME_TYPE_MINIGAMES) {
            v = CHAR_RECORD_FIELD(i, 0x94);
        } else {
            v = CHAR_RECORD_FIELD(i, 0x24);
        }
        if (maxD < v) {
            maxD = v;
        }
        v = CHAR_RECORD_FIELD(i, 0x104);
        if (maxE < v) {
            maxE = v;
        }
    }

    sizeB = ROUND_UP_32(maxB);
    sizeC = ROUND_UP_32(maxC);
    sizeE = ROUND_UP_32(maxE);
    sizeA = ROUND_UP_32(maxA);
    sizeD = ROUND_UP_32(maxD);
    HA_U32(0x2C98) = sizeA;
    HA_U32(0x2C94) = sizeB;
    HA_U32(0x2C9C) = sizeC;
    HA_U32(0x2C90) = sizeD;
    HA_U32(0x2CA4) = sizeE;
    HA_U32(0x2D60) = sizeD + (sizeA + sizeB + sizeC + sizeE) * 4;
    cursor = (u32)_OSAllocFromHeap(0x20, HA_U32(0x2D60));
    HA_U32(0x2C88) = cursor;

    for (i = 0; i < 4; i++) {
        u8* set = HA(i * 0x14);
        u8* rec = HA(MODEL_RECORD_BASE + i * MODEL_RECORD_SIZE);

        *(u32*)(set + 0x2CEC) = cursor;
        cursor += sizeA;
        *(u32*)(set + 0x2CF0) = cursor;
        cursor += sizeB;
        *(u32*)(set + 0x2CF4) = cursor;
        cursor += sizeC;
        if (i == 0) {
            *(u32*)(set + 0x2CF8) = cursor;
            cursor += sizeD;
        } else {
            *(u32*)(set + 0x2CF8) = HA_U32(0x2CF8);
        }
        *(u32*)(set + 0x2CFC) = cursor;
        cursor += sizeE;
        *(u32*)(rec + 0x10) = 0;
        *(u32*)(rec + 0x1C) = 0;
        *(u32*)(rec + 0x20) = 0;
        *(u32*)(rec + 0x14) = 0;
        *(u32*)(rec + 0x18) = 0;
        *(u32*)(rec + 0x24) = 0;
    }
    *(s16*)HA(0x2D68) = -1;
}

extern void fn_800177B4(void);

BOOL fn_80017098(int team, int idx, int c, int d, int e, int f) {
    u8* roster = (u8*)&inMemRoster[team][idx];
    DrawingSceneStruct* task;
    s32 i;
    s32 slot;

    if (f >= 0) {
        task = insertGraphicDrawingFunction(fn_800177B4, 0);
        slot = d;
    } else {
        for (i = 0; i < 13; i++) {
            u8* rec = HA(MODEL_RECORD_BASE + i * MODEL_RECORD_SIZE);
            BOOL same = FALSE;

            if ((s8)rec[0x252] == *(s16*)(roster + 0x24) && rec[0x25A] == roster[0x26] && rec[0x25B] == roster[0x27] &&
                (s8)rec[0x257] == (s8)idx) {
                same = TRUE;
            }
            if (rec[0x256] == team && same && rec[0x258] == c && rec[0x259] == e) {
                s32 j;

                *HA(0x2D77) = 0;
                *HA(0x2D6A + i) = d;
                *HA(0x2D79) = i;
                rec[0x254] = d;
                for (j = 0; j < 13; j++) {
                    if (HA_OBJ(j) == rec) {
                        HA_OBJ(j) = NULL;
                        break;
                    }
                }
                HA_OBJ(d) = rec;
                return TRUE;
            }
        }
        task = insertGraphicDrawingFunction(fn_800177B4, 0);
        if (d >= 9) {
            for (slot = 9; slot < 13; slot++) {
                if ((s8)*HA(0x2D6A + slot) < 0) {
                    break;
                }
            }
        } else {
            for (slot = 0; slot < 13; slot++) {
                if ((s8)*HA(0x2D6A + slot) < 0) {
                    break;
                }
            }
        }
    }
    *((u8*)task + 0x14) = 0;
    *((u8*)task + 0x1C) = slot;
    *((u8*)task + 0x19) = team;
    *((u8*)task + 0x1A) = idx;
    *((u8*)task + 0x1B) = c;
    *((u8*)task + 0x15) = d;
    *((u8*)task + 0x1D) = e;
    if (f < 0) {
        *((u8*)task + 0x16) = *(s16*)(roster + 0x24);
    } else {
        *((u8*)task + 0x16) = f;
    }
    *HA(0x2D6A + slot) = d;
    *HA(0x2D77) = 1;
    *HA(0x2D79) = slot;
    return FALSE;
}

extern void* lbl_803CB794;
extern void* lbl_803CBC30;
extern void fn_800145F8(int mode);
extern void* fn_80023AA4(void);
extern void fn_80018DEC(int mode);

/* The slot arrays of hugeAnimStruct that fn_8001A3FC resets. */
typedef struct hugeAnimStruct_view_8001a3fc {
    /* 0x0000 */ u8 _0000[0xC04];
    /* 0x0C04 */ u8 pool[13][MODEL_RECORD_SIZE];
    /* 0x2C50 */ void* objects[13];
    /* 0x2C84 */ u8 _2C84[0x2D6A - 0x2C84];
    /* 0x2D6A */ u8 flags[0x2D90 - 0x2D6A];
} hugeAnimStruct_view_8001a3fc;
#define HA_SLOTS (*(hugeAnimStruct_view_8001a3fc*)&hugeAnimStruct)

/* Largest (low 28 bits of the +4 word) of the file entries named by
 * lbl_800EEB18; negative ids are unused. */
static inline u32 maxListedFileSize(void) {
    u8* files = lbl_803CB794;
    s32 i;
    u32 v;
    u32 maxSize = 0;
    s16* ids = lbl_800EEB18;

    for (i = 0; i < 54; i++) {
        s32 id = ids[i];
        if (id >= 0) {
            v = *(u32*)(files + id * 16 + 4) & 0x0FFFFFFF;
            if (maxSize < v) {
                maxSize = v;
            }
        }
    }
    return maxSize;
}

void fn_8001A3FC(int mode) {
    s32 i;
    u32 maxSize;
    u8* pool;
    s32 count;
    s32 k;
    s32 slot;

    animationInitializationRunnerRelated(mode);
    lbl_803CBC34[0] = 0;
    lbl_803CBC34[1] = 0;
    lbl_803CBC34[2] = 0;
    lbl_803CBC34[3] = 0;
    lbl_803CBC34[4] = count = i = 1;
    for (; i < 13; i++) {
        lbl_80118220[i * 0x64 + 0x61] = -2;
    }
    if (count != 0) {
        maxSize = maxListedFileSize();
        pool = _OSAllocFromHeap(0x20, (maxSize + 0x1F) & ~0x1F);
        *(u8**)lbl_80118220 = pool;
        lbl_803CBC30 = pool;
        lbl_80118220[0x61] = 0xFF;
        lbl_80118220[0x60] = 0xFF;
    }
    fn_800145F8(mode);
    hugeAnimStruct.modelEntries = fn_80023AA4();
    fn_80018DEC(mode);
    initActorArray(13);
    slot = 0;
    for (k = 0; k < 9; k++, slot++) {
        HA_SLOTS.pool[slot][0x255] = slot;
        HA_SLOTS.objects[slot] = NULL;
        HA_SLOTS.flags[slot] = 0xFF;
        HA_SLOTS.pool[slot][0x257] = 0xFF;
    }
    for (k = 0; k < 4; k++, slot++) {
        HA_SLOTS.pool[slot][0x255] = slot;
        HA_SLOTS.objects[slot] = NULL;
        HA_SLOTS.flags[slot] = 0xFF;
        HA_SLOTS.pool[slot][0x257] = 0xFF;
    }
    for (i = 0; i < 9; i++) {
        HA_SLOTS.flags[0x2D7F - 0x2D6A + i] = 0xFF;
    }
    HA_SLOTS.flags[0x2D89 - 0x2D6A] = 0xFF;
    HA_SLOTS.flags[0x2D8A - 0x2D6A] = 0xFF;
    HA_SLOTS.flags[0x2D8B - 0x2D6A] = 0xFF;
    HA_SLOTS.flags[0x2D8C - 0x2D6A] = 0xFF;
}

extern u8 lbl_80366158[];
extern void fn_8001BA44(s32 index, s16 a, u8 b, u8 c, s16 d, u8 e, s32 f);
extern void fn_8004B208(void* obj, s16 anim, int collision, f32 time);
void fn_8001BE50(s32 index, s16 a, u8 b, u8 c, s16 d, u8 e, s32 f);

#define OBJ_S16(o, off) (*(s16*)((u8*)(o) + (off)))
#define OBJ_U8(o, off)  (*(u8*)((u8*)(o) + (off)))
#define OBJ_F32(o, off) (*(f32*)((u8*)(o) + (off)))

void fn_8001C234(u32* changedMask) {
    s32 i;
    u8* gs = (u8*)&g_d_GameSettings;

    *changedMask = 0;
    for (i = 0; i < 13; i++) {
        u8* obj = HA_OBJ(i);
        f32 time;
        f32 animTime;
        u16 bone;
        s32 state;

        if (obj == NULL) {
            continue;
        }
        if (obj[0x25D] == 0) {
            continue;
        }
        if (OBJ_S16(obj, 0x6A) < 600 && lbl_80366158[0x28] == 0 && highLevelSimulationFlag[0] == 0 &&
            obj[0x26F] == 0) {
            OBJ_S16(obj, 0x6A) = OBJ_S16(obj, 0x6A) + 1;
        }
        animTime = lbl_803CC4F0;
        if (HA_OBJ(i) != NULL) {
            bone = *(u16*)(HA_OBJ(i) + 0x16A);
        } else {
            bone = 0xFFFF;
        }
        if (bone != 0xFFFF) {
            animTime = getActorBoneAnimTime(hugeAnimStruct.actorTable->entries[(s8)obj[0x255]].actor, bone);
        }
        OBJ_S16(obj, 0x68) = (s16)(animTime / OBJ_F32(obj, 0x4C));
        if (OBJ_S16(obj, 0x70) >= 0) {
            OBJ_S16(obj, 0x68) = OBJ_S16(obj, 0x70);
        }
        OBJ_S16(obj, 0x70) = -1;

        state = obj[0x25E];
        if (state == 1 || (state == 2 && OBJ_S16(obj, 0x68) == 0 && OBJ_S16(obj, 0x6A) > 1) ||
            OBJ_S16(obj, 0x62) == -1) {
            *changedMask |= 1 << i;
            if (OBJ_S16(obj, 0x64) >= 0) {
                time = (f32)OBJ_S16(obj, 0x6C);
                if (gs[0x11] != 0 && gs[6] == 2) {
                    fn_8001BA44(i, OBJ_S16(obj, 0x64), obj[0x260], obj[0x263], OBJ_S16(obj, 0x6C), obj[0x266], obj[0x26A]);
                } else {
                    fn_8001BE50(i, OBJ_S16(obj, 0x64), obj[0x260], obj[0x263], OBJ_S16(obj, 0x6C), obj[0x266], obj[0x26A]);
                }
                OBJ_S16(obj, 0x60) = OBJ_S16(obj, 0x62);
                OBJ_S16(obj, 0x62) = OBJ_S16(obj, 0x64);
                OBJ_S16(obj, 0x64) = -1;
                obj[0x25F] = obj[0x260];
                obj[0x262] = obj[0x263];
                obj[0x265] = obj[0x266];
                obj[0x269] = obj[0x26A];
                obj[0x26C] = obj[0x26D];
                OBJ_S16(obj, 0x6A) = 0;
                if (OBJ_S16(obj, 0x66) >= 0) {
                    OBJ_S16(obj, 0x64) = OBJ_S16(obj, 0x66);
                    OBJ_S16(obj, 0x6C) = OBJ_S16(obj, 0x6E);
                    obj[0x260] = obj[0x261];
                    obj[0x263] = obj[0x264];
                    obj[0x25E] = 2;
                    obj[0x266] = obj[0x267];
                    obj[0x26A] = obj[0x26B];
                    obj[0x26D] = obj[0x26E];
                    OBJ_S16(obj, 0x66) = -1;
                    continue;
                }
            } else {
                time = lbl_803CC4B8;
            }
            obj[0x25E] = 0;
        } else {
            time = fn_800B4C40(hugeAnimStruct.actorTable->entries[(s8)obj[0x255]].actor);
        }
        if (highLevelSimulationFlag[0] == 0) {
            fn_8004B208(obj, OBJ_S16(obj, 0x62), stadiumCollisionRelated(gs[9], obj[0x275]), time);
        }
    }
}

extern f32 lbl_803CC514;
extern f32 lbl_803CC518;
extern f32 lbl_803CC51C;
extern f32 lbl_803CC520;
extern f32 lbl_803CC524;
extern f32 lbl_803CC528;

void fn_8001E488(void) {
    s32 i;
    Mtx44 proj;

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    for (i = 0; i < hugeAnimStruct.actorTable->count; i++) {
        u8* obj = HA_OBJ(i);
        ActorObjectEntry* entry = &hugeAnimStruct.actorTable->entries[i];
        Actor* actor;
        u32* args;
        MtxPtr camera;
        f32 x;
        f32 y;

        if (obj == NULL) {
            continue;
        }
        if (entry->actor == NULL) {
            continue;
        }
        if (entry->applyControl == 0) {
            continue;
        }
        x = *(f32*)(obj + 0x34) / lbl_803CC514;
        y = *(f32*)(obj + 0x38) / lbl_803CC514;
        C_MTXFrustum(proj, lbl_803CC518 + y, lbl_803CC51C + y, lbl_803CC520 + x, lbl_803CC524 + x, lbl_803CC4F0,
                     lbl_803CC528);
        GXSetProjection(proj, GX_PERSPECTIVE);
        camera = (MtxPtr)((u8*)returnFloatFromModeIndex(0) + 0x40);
        actor = entry->actor;
        args = entry->drawArgs;
        if (entry->callback != NULL) {
            entry->callback(entry);
        }
        switch (entry->drawArgCount) {
        case 0:
            fn_8001DD58(actor, 0, camera, 0);
            break;
        case 1:
            fn_8001DD58(actor, 0, camera, 1, args[0]);
            break;
        case 2:
            fn_8001DD58(actor, 0, camera, 2, args[0], args[1]);
            break;
        case 3:
            fn_8001DD58(actor, 0, camera, 3, args[0], args[1], args[2]);
            break;
        case 4:
            fn_8001DD58(actor, 0, camera, 4, args[0], args[1], args[2], args[3]);
            break;
        case 5:
            fn_8001DD58(actor, 0, camera, 5, args[0], args[1], args[2], args[3], args[4]);
            break;
        case 6:
            fn_8001DD58(actor, 0, camera, 6, args[0], args[1], args[2], args[3], args[4], args[5]);
            break;
        case 7:
            fn_8001DD58(actor, 0, camera, 7, args[0], args[1], args[2], args[3], args[4], args[5], args[6]);
            break;
        case 8:
            fn_8001DD58(actor, 0, camera, 8, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]);
            break;
        }
    }
}

int fn_80014A18(int team) {
    s32 i;
    s32 j;

    if (*HA(0x2D8E) == 0) {
        *HA(0x2D8E) = 1;
        *HA(0x2D88) = 0xFF;
        for (j = 0; j < 9; j++) {
            *HA(0x2D7F + j) = 0xFF;
        }
    }

    if (*HA(0x2D8E) == 1) {
        for (i = 0; i <= 8; i++) {
            for (j = 0; j < 9; j++) {
                if ((s8)HA_OBJ(i)[0x252] == (s8)*HA(0x2D7F + j)) {
                    *(u32*)(HA_OBJ(i) + 0x24) = *(u32*)HA(0x2CC0 + j * 4);
                    break;
                }
            }
            if (j >= 9) {
                *HA(0x2D8D) = 0;
                *HA(0x2D8E) = 2;
                *HA(0x2D88) = i;
                break;
            }
        }
        if (i > 8) {
            return TRUE;
        }
    }

    if (*HA(0x2D8E) == 2) {
        u8* obj = HA_OBJ((s8)*HA(0x2D88));
        u8* rec = HA(MODEL_RECORD_BASE + (s8)obj[0x255] * MODEL_RECORD_SIZE);

        if (*HA(0x2D8D) == 0) {
            s32 k;

            for (k = 0; k < 9; k++) {
                if ((s8)*HA(0x2D7F + k) < 0) {
                    break;
                }
            }
            *HA(0x2D7F + k) = rec[0x252];
            if (*HA(0x2D7C) == 0) {
                *(u32*)(rec + 0x18) = *(u32*)HA(0x2CC0 + k * 4);
                ARAMTransfer((u8*)lbl_803CB790 + ((s8)rec[0x252] * 0x13 + 4) * 16, *(s32*)(rec + 0x18), 0, 0);
            } else {
                *(u32*)(rec + 0x24) = *(u32*)HA(0x2CC0 + k * 4);
                ARAMTransfer((u8*)lbl_803CB790 + ((s8)rec[0x252] * 0x13 + 0x11) * 16, *(s32*)(rec + 0x24), 0, 0);
            }
            *HA(0x2D8D) = 1;
        } else {
            BOOL ready = FALSE;

            if (((u8*)&lbl_803C6CF8)[0x715] == 1) {
                if (*HA(0x2D7C) == 0) {
                    ANIMGet(*(void**)(rec + 0x18));
                } else {
                    ANIMGet(*(void**)(rec + 0x24));
                }
                ready = TRUE;
            }
            if (ready) {
                *HA(0x2D8E) = 1;
            }
        }
    }
    return FALSE;
}

int fn_80015468(int team) {
    s32 i;
    s32 j;

    if (*HA(0x2D8E) == 0) {
        s32 used[9];

        *HA(0x2D8E) = 1;
        *HA(0x2D88) = 0xFF;
        for (j = 0; j < 9; j++) {
            used[j] = 0;
        }
        for (i = 0; i <= 8; i++) {
            for (j = 0; j < 9; j++) {
                if (HA_OBJ(i) != NULL && (s8)HA_OBJ(i)[0x252] == (s8)*HA(0x2D7F + j)) {
                    used[j] = 1;
                    break;
                }
            }
        }
        for (j = 0; j < 9; j++) {
            if (used[j] == 0) {
                *HA(0x2D7F + j) = 0xFF;
            }
        }
    }

    if (*HA(0x2D8E) == 1) {
        for (i = 0; i <= 8; i++) {
            for (j = 0; j < 9; j++) {
                if ((s8)HA_OBJ(i)[0x252] == (s8)*HA(0x2D7F + j)) {
                    *(u32*)(HA_OBJ(i) + 0x18) = *(u32*)HA(0x2CC0 + j * 4);
                    break;
                }
            }
            if (j >= 9) {
                *HA(0x2D8D) = 0;
                *HA(0x2D8E) = 2;
                *HA(0x2D88) = i;
                break;
            }
        }
        if (i > 8) {
            return TRUE;
        }
    }

    if (*HA(0x2D8E) == 2) {
        u8* obj = HA_OBJ((s8)*HA(0x2D88));
        u8* rec = HA(MODEL_RECORD_BASE + (s8)obj[0x255] * MODEL_RECORD_SIZE);

        if (*HA(0x2D8D) == 0) {
            s32 k;

            for (k = 0; k < 9; k++) {
                if ((s8)*HA(0x2D7F + k) < 0) {
                    break;
                }
            }
            *HA(0x2D7F + k) = rec[0x252];
            if (*HA(0x2D7C) == 0) {
                *(u32*)(rec + 0x18) = *(u32*)HA(0x2CC0 + k * 4);
                ARAMTransfer((u8*)lbl_803CB790 + ((s8)rec[0x252] * 0x13 + 4) * 16, *(s32*)(rec + 0x18), 0, 0);
            } else {
                *(u32*)(rec + 0x24) = *(u32*)HA(0x2CC0 + k * 4);
                ARAMTransfer((u8*)lbl_803CB790 + ((s8)rec[0x252] * 0x13 + 0x11) * 16, *(s32*)(rec + 0x24), 0, 0);
            }
            *HA(0x2D8D) = 1;
        } else {
            BOOL ready = FALSE;

            if (((u8*)&lbl_803C6CF8)[0x715] == 1) {
                if (*HA(0x2D7C) == 0) {
                    ANIMGet(*(void**)(rec + 0x18));
                } else {
                    ANIMGet(*(void**)(rec + 0x24));
                }
                ready = TRUE;
            }
            if (ready) {
                *HA(0x2D8E) = 1;
            }
        }
    }
    return FALSE;
}

extern void fn_8001F8A4(void);

void fn_800196D8(void) {
    DrawingSceneStruct* item = currentDrawingItem;
    u8* itemState = (u8*)item + 0x14;
    DrawingSceneStruct* fresh;
    Vec dir;
    Vec copy;
    f32 len;
    s32 i;
    s32 k;

    switch ((s8)*itemState) {
    case 0:
        fresh = insertGraphicDrawingFunction(fn_800188C0, 0);
        *((u8*)fresh + 0x14) = 0;
        *((u8*)fresh + 0x16) = 0;
        *((u8*)fresh + 0x17) = 0xFF;
        *HA(0x307B) = 1;
        (*itemState)++;
        break;
    case 1:
        if (*HA(0x307B) == 0) {
            *itemState = *itemState + 1;
        }
        break;
    case 2:
        dir.x = -lbl_80367318[0].pos.x;
        dir.y = -lbl_80367318[0].pos.y;
        dir.z = -lbl_80367318[0].pos.z;
        len = dolsqrtf2((dir.x * dir.x) + (dir.y * dir.y) + (dir.z * dir.z));
        *HA(0x3087) = 1;
        dir.x /= len;
        dir.y /= len;
        dir.z /= len;
        fn_8003A540(0);
        *HA(0x3086) = 1;
        DrawShadows(1);
        copy = dir;
        updateVectorInArray(0, copy);
        fn_800BF048(fn_8001AAF0);
        fn_800BF058(fn_8001AB10);
        for (i = 0; i < 80; i += 8) {
            for (k = 0; k < 8; k++) {
                ((u32*)HA_U32(0x2C84))[i + k] += HA_U32(0x2C84);
            }
        }
        *HA(0x307C) = 0;
        *HA(0x307D) = 0;
        *HA(0x3082) = 0;
        fn_8001F8A4();
        (*itemState)++;
        break;
    default:
        challengeMapMaybe();
        *HA(0x2D7D) = 1;
        *HA(0x307C) = 1;
        removeCurrentDrawingItem();
        break;
    }
}

void fn_8001E0D8(ActorObjectTable* table, int group, MtxPtr camera) {
    u8 lightLevel = 0xFF;
    GXColor ambient = inputParams[g_d_GameSettings._54].ambient;
    u16 i;

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    for (i = 0; i < table->count; i++) {
        u8* obj = HA_OBJ(i);
        ActorObjectEntry* entry;
        Actor* actor;
        u32* args;
        Mtx trans;

        if (obj == NULL) {
            continue;
        }
        if (obj[0x25D] == 2) {
            continue;
        }
        entry = &hugeAnimStruct.actorTable->entries[(s8)obj[0x255]];
        if (entry->actor == NULL) {
            continue;
        }
        if (entry->applyControl == 0) {
            continue;
        }
        if (lightLevel != obj[0x277]) {
            GXColor color;

            lightLevel = obj[0x277];
            if (lightLevel == 0xFF) {
                color = inputParams[g_d_GameSettings._54].ambient;
            } else {
                ambient.a = lightLevel;
                if (lightLevel == 0) {
                    continue;
                }
                color = ambient;
            }
            adjustLightingParams(1, color);
        }
        PSMTXTrans(trans, *(f32*)(obj + 0x34), *(f32*)(obj + 0x38), *(f32*)(obj + 0x3C));
        PSMTXConcat(camera, trans, trans);
        fn_800B9948(*(DOTevSetupCallback*)(obj + 0x5C));
        lbl_803CBC18 = (u32)obj;
        actor = entry->actor;
        args = entry->drawArgs;
        if (entry->callback != NULL) {
            entry->callback(entry);
        }
        switch (entry->drawArgCount) {
        case 0:
            fn_8001DD58(actor, group, trans, 0);
            break;
        case 1:
            fn_8001DD58(actor, group, trans, 1, args[0]);
            break;
        case 2:
            fn_8001DD58(actor, group, trans, 2, args[0], args[1]);
            break;
        case 3:
            fn_8001DD58(actor, group, trans, 3, args[0], args[1], args[2]);
            break;
        case 4:
            fn_8001DD58(actor, group, trans, 4, args[0], args[1], args[2], args[3]);
            break;
        case 5:
            fn_8001DD58(actor, group, trans, 5, args[0], args[1], args[2], args[3], args[4]);
            break;
        case 6:
            fn_8001DD58(actor, group, trans, 6, args[0], args[1], args[2], args[3], args[4], args[5]);
            break;
        case 7:
            fn_8001DD58(actor, group, trans, 7, args[0], args[1], args[2], args[3], args[4], args[5], args[6]);
            break;
        case 8:
            fn_8001DD58(actor, group, trans, 8, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]);
            break;
        }
    }
    fn_800B993C();
}

extern void* lbl_803CB7A8;
extern void* lbl_803CBC24;


/* One 16-byte entry of the file table at lbl_803CB7A8; the low 28 bits of
 * `size` are the file size. */
typedef struct FileTableEntry {
    u32 _00;
    u32 size;
    u32 _08;
    u32 _0C;
} FileTableEntry;

/* Largest of the six consecutive file entries starting at `idx`. */
static inline u32 maxFileSizeOfSix(u32 maxSize, s32 idx) {
    s32 k;

    for (k = 0; k < 6; k++) {
        u32 v = ((FileTableEntry*)lbl_803CB7A8)[idx + k].size & 0x0FFFFFFF;
        if (maxSize < v) {
            maxSize = v;
        }
    }
    return maxSize;
}

void fn_800145F8(int mode) {
    u32 size;
    u8* pool;
    u32 i;
    s32 j;
    u32 t;
    s16 idx;
    u8* rec;
    u32 maxSize = 0;

    if (mode == 0) {
        for (t = 0; t < 2; t++) {
            for (j = 0; j < 9; j++) {
                idx = lbl_800EEAAC[*(s16*)((u8*)&inMemRoster[t][j] + 0x24)];
                if (idx >= 0) {
                    maxSize = maxFileSizeOfSix(maxSize, idx);
                }
            }
        }
    } else {
        for (i = 0; i < 54; i++) {
            idx = lbl_800EEAAC[i];
            if (idx >= 0) {
                maxSize = maxFileSizeOfSix(maxSize, idx);
            }
        }
    }

    size = (maxSize + 0x1F) & ~0x1F;
    pool = _OSAllocFromHeap(0x20, size * 0x1A);
    lbl_803CBC24 = pool;
    for (i = 0; i < 13; i++) {
        u8* rec = HA(i * 0xD4);

        *(u32*)(rec + 0x140) = (u32)lbl_803CBC24 + size * (i * 2);
        *(u32*)(rec + 0x1A4) = (u32)lbl_803CBC24 + size * (i * 2 + 1);
    }
    for (i = 0, rec = HA(0); i < 13; i++, rec += 0xD4) {
        ((s8*)rec)[0x20F] = -1;
        ((s8*)rec)[0x211] = -1;
        ((s8*)rec)[0x210] = -1;
        rec[0x20D] = 0xFF;
        rec[0x20E] = 0xFF;
        *(u32*)(rec + 0x208) = 0;
        rec[0x20C] = 0;
        rec[0x1A0] = i * 2;
        rec[0x204] = i * 2 + 1;
    }
}

extern u8 lbl_800EEA58[];

#define OFFSET_TABLE ((u32*)HA_U32(0x2C84))

void fn_8001F8A4(void) {
    s32 i;
    s32 set;
    u32 layout;
    u32 geo;
    u32 tex;
    u8* actorSet;
    f32 zero;

    for (i = 0; i < 24; i++) {
        layout = OFFSET_TABLE[i * 3];
        geo = OFFSET_TABLE[i * 3 + 1];
        tex = OFFSET_TABLE[i * 3 + 2];
        LoadActorLayout((void*)layout);
        convertGeometryAndSknHeader((void*)geo, NULL);
        haveActLayoutPointToGeoHeader((void*)layout, (void*)geo);
        if (i == 11) {
            tex = OFFSET_TABLE[0x80 / 4];
        } else {
            convertTextureHeader((void*)tex);
        }
        UpdateTexturePalettePointers((void*)geo, (void*)tex);
    }
    ANIMGet((void*)OFFSET_TABLE[0x120 / 4]);
    adjustInternalPointers((void*)OFFSET_TABLE[0x130 / 4]);
    HA_U32(0x309C) = OFFSET_TABLE[0x134 / 4];
    actRelated((void*)OFFSET_TABLE[0x130 / 4], HA(0x309C));
    actorRelated(HA(0x309C), 0, 0);
    adjustInternalPointers((void*)OFFSET_TABLE[0x138 / 4]);
    HA_U32(0x30F8) = OFFSET_TABLE[0x13C / 4];
    actRelated((void*)OFFSET_TABLE[0x138 / 4], HA(0x30F8));
    actorRelated(HA(0x30F8), 0, 0);

    HA_U32(0x64) = (u32)ActorObjectInitTable(0x19);
    for (i = 0; i < 25; i++) {
        ActorObjectTable* table;
        ActorObjectEntry* entry;

        set = lbl_800EEA58[i];
        layout = OFFSET_TABLE[set * 3];
        if (set < 16) {
            animateBallRelated((void*)HA_U32(0x64), (u16)i, (u16)i, (void*)layout, 0, 0);
        } else {
            animateBallRelated((void*)HA_U32(0x64), (u16)i, (u16)i, (void*)layout, OFFSET_TABLE[0x120 / 4], 0);
            table = (ActorObjectTable*)HA_U32(0x64);
            entry = &table->entries[i];
            zero = lbl_803CC4B8;
            entry->seqNum = 0;
            entry->frame = zero;
            entry->animPending = 1;
            entry->framePending = entry->speedPending = (entry->anim != NULL);
            entry->blendTime = zero;
            ACTSetAnimation(entry->actor, entry->anim, NULL, entry->seqNum, zero, entry->blendTime);
            updateBoneParam(entry->actor, 0);
        }
        set = lbl_800EEA58[i];
        if (set == 0 || set == 4 || (u8)(set - 7) <= 3 || (u8)(set - 12) <= 6 || set == 0x13) {
            fn_800BD548(&((ActorObjectTable*)HA_U32(0x64))->entries[i], 4, HA_U32(0xAC), HA_U32(0xB0), HA_U32(0xB4),
                        HA_U32(0xB8));
        } else {
            fn_800BD548(&((ActorObjectTable*)HA_U32(0x64))->entries[i], 0, 0, 0, 0, 0);
        }
        CTRLSetTranslation(&((ActorObjectTable*)HA_U32(0x64))->entries[i].control, lbl_803CC4B8, lbl_803CC4B8,
                           lbl_803CC4B8);
        CTRLSetRotation(&((ActorObjectTable*)HA_U32(0x64))->entries[i].control, lbl_803CC4B8, lbl_803CC4B8,
                        lbl_803CC4B8);
        if (i == 5) {
            ACTActorRelated((void*)HA_U32(0x30C8), &((ActorObjectTable*)HA_U32(0x64))->entries[i]);
        } else if (i == 6) {
            ACTActorRelated((void*)HA_U32(0x3124), &((ActorObjectTable*)HA_U32(0x64))->entries[i]);
        }
    }

    HA_U32(0x2D90) = (u32)_OSAllocFromHeap(0x20, 1000);
    for (i = 0; i < 25; i++) {
        u8* base = (u8*)HA_U32(0x2D90);

        *(f32*)(base + i * 0x28 + 4) = lbl_803CC4B8;
        *(f32*)(base + i * 0x28 + 8) = lbl_803CC4B8;
        *(f32*)(base + i * 0x28 + 0xC) = lbl_803CC4B8;
        *(f32*)(base + i * 0x28 + 0x10) = lbl_803CC4B8;
        *(f32*)(base + i * 0x28 + 0x14) = lbl_803CC4B8;
        *(f32*)(base + i * 0x28 + 0x18) = lbl_803CC4B8;
        ((u8*)HA_U32(0x2D90))[i * 0x28 + 0x26] = 0;
        *(u32*)((u8*)HA_U32(0x2D90) + i * 0x28) = 0;
    }
}

extern void fn_80021BBC(int charId, int dest);

int fn_80016344(int charId, int slot, int c, int d) {
    u8* rec;
    BOOL ready;
    u8* part;

    if (*HA(0x2D77) == 6) {
        return 1;
    }
    if (*HA(0x2D77) == 1) {
        return 0;
    }
    if (*HA(0x2D77) == 2) {
        HA_OBJ(slot) = HA(MODEL_RECORD_BASE + slot * MODEL_RECORD_SIZE);
        HA_OBJ(slot)[0x25A] = c;
        HA_OBJ(slot)[0x25B] = c;
        *HA(0x2D8D) = 0;
        *HA(0x2D77) = 3;
    }

    if (*HA(0x2D77) == 3) {
        rec = HA(MODEL_RECORD_BASE + slot * MODEL_RECORD_SIZE);
        if (slot == 12) {
            if (*HA(0x2D8D) == 0) {
                *HA(0x2D8D) = 1;
                *HA(0x2D7F + slot) = rec[0x252];
                *(u32*)(rec + 0x24) = HA_U32(0x2CBC);
                ARAMTransfer((u8*)lbl_803CB790 + ((s8)rec[0x252] * 0x13 + 0x11) * 16, *(s32*)(rec + 0x24), 0, 0);
                ready = FALSE;
            } else {
                ready = FALSE;
                if (((u8*)&lbl_803C6CF8)[0x715] == 1) {
                    ANIMGet(*(void**)(rec + 0x24));
                    ready = TRUE;
                }
            }
            if (!ready) {
                return 0;
            }
        } else {
            if (*HA(0x2D8D) == 0) {
                *HA(0x2D8D) = 1;
                *HA(0x2D7F + slot) = rec[0x252];
                if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
                    *(u32*)(rec + 0x24) = HA_U32(0x2CAC);
                    fn_80021BBC((s8)rec[0x252], *(s32*)(rec + 0x24));
                } else if (slot >= 9) {
                    *(u32*)(rec + 0x24) = HA_U32(0x2CAC);
                    ARAMTransfer((u8*)lbl_803CB790 + ((s8)rec[0x252] * 0x13 + 0x10) * 16, *(s32*)(rec + 0x24), 0, 0);
                } else {
                    *(u32*)(rec + 0x24) = HA_U32(0x2CFC + slot * 0x14);
                    fn_80021BBC((s8)rec[0x252], *(s32*)(rec + 0x24));
                }
                ready = FALSE;
            } else {
                ready = FALSE;
                if (((u8*)&lbl_803C6CF8)[0x715] == 1) {
                    ANIMGet(*(void**)(rec + 0x24));
                    ready = TRUE;
                }
            }
            if (!ready) {
                return 0;
            }
        }
        *HA(0x2D77) = 4;
    }

    if (*HA(0x2D77) == 4) {
        s32 fileIndex = lbl_800EEB18[(u8)charId];

        if (fileIndex != -1) {
            u8* slotRec = HA(MODEL_RECORD_BASE + slot * MODEL_RECORD_SIZE);

            part = *(u8**)(slotRec + 8);
            if (*(u32*)(part + 0x10) != 0) {
                if (lbl_803CBBFA == 0) {
                    fn_80021ADC(fileIndex, *(void**)lbl_80118220);
                    lbl_803CBBFA = 1;
                }
                if (((u8*)&lbl_803C6CF8)[0x715] == 1) {
                    lbl_80118220[0x60] = charId;
                    lbl_80118220[0x61] = slot;
                    *(u32*)(lbl_80118220 + 4) = *(u32*)lbl_80118220;
                    actRelated(*(void**)(part + 0x10), lbl_80118220 + 4);
                    lbl_803CBBFA = 0;
                    *(u8**)(slotRec + 0x2C) = lbl_80118220;
                    ready = TRUE;
                } else {
                    ready = FALSE;
                }
            } else {
                goto noPart;
            }
        } else {
        noPart:
            *(u32*)(HA(MODEL_RECORD_BASE + slot * MODEL_RECORD_SIZE) + 0x2C) = 0;
            ready = TRUE;
        }
        if (!ready) {
            return 0;
        }
        *HA(0x2D77) = 5;
    }

    if (*HA(0x2D77) == 5) {
        if (!animateModelArmsGlovesBats(HA(MODEL_RECORD_BASE + slot * MODEL_RECORD_SIZE))) {
            return 0;
        }
        *HA(0x2D77) = 0;
        return 1;
    }
    fn_80017098(0, d, 1, slot, 1, charId);
    return 0;
}

extern f32 lbl_803CC504;

typedef struct ModelAnimObject {
    /* 0x00 */ UnkB2B4C* actor;
    /* 0x04 */ u8 _04[0x10 - 0x04];
    /* 0x10 */ u8* banks[6];
    /* 0x28 */ u8 _28[0x2C - 0x28];
    /* 0x2C */ u8* effectA;
    /* 0x30 */ u8* effectB;
    /* 0x34 */ u8 _34[0x4C - 0x34];
    /* 0x4C */ f32 frameScale;
    /* 0x50 */ u8 _50[0x72 - 0x50];
    /* 0x72 */ u8 attachPoint[1];
    /* 0x73 */ u8 _73[0x162 - 0x73];
    /* 0x162 */ u16 partBones[5];
    /* 0x16C */ u8 _16C[0x255 - 0x16C];
    /* 0x255 */ s8 slot;
    /* 0x256 */ u8 _256[0x268 - 0x256];
    /* 0x268 */ u8 mode;
    /* 0x269 */ u8 _269[0x26C - 0x269];
    /* 0x26C */ u8 flag26C;
} ModelAnimObject;

static inline u16 getAnimBone(ModelAnimObject* obj, int which) {
    if (obj != NULL) {
        return obj->partBones[which];
    }
    return 0xFFFF;
}

void fn_8001BE50(s32 index, s16 anim, u8 boneParam, u8 mode, s16 frame, u8 attach, s32 speedDivisor) {
    f32 blend = lbl_803CC4B8;
    ModelAnimObject* obj = hugeAnimStruct.objects[index];
    ActorObjectEntry* entry;
    ActorObjectTable* table;
    s32 kind;
    s32 seq;
    u8* bank;
    ModelAnimObject* cur;
    u16 boneEnd;
    u16 boneRoot;
    u8* node;
    Vec offset;

    if (obj == NULL) {
        return;
    }
    entry = &hugeAnimStruct.actorTable->entries[obj->slot];
    if ((u8)speedDivisor != 0) {
        blend = lbl_803CC4F0 / (f32)(u8)speedDivisor;
    }
    if (obj->flag26C == 0) {
        fn_800B2B54(obj->actor, getAnimBone(obj, 4), 13);
    } else {
        fn_800B2B54(obj->actor, getAnimBone(obj, 4), 1);
        fn_800B2B54((UnkB2B4C*)entry->actor, getAnimBone(hugeAnimStruct.objects[index], 4), 1);
        fn_800B2B4C((UnkB2B4C*)entry->actor, lbl_803CC504);
        *(f32*)((u8*)entry->actor + 0x8C) = lbl_803CC4B8;
    }

    if (anim >= 0) {
        if (anim < 45) {
            seq = anim;
            kind = 2;
        } else if (anim < 61) {
            seq = anim - 45;
            kind = 1;
        } else if (anim < 63) {
            seq = anim - 61;
            kind = 4;
        } else if (anim < 75) {
            seq = anim - 63;
            kind = 3;
        } else if (anim < 105) {
            seq = anim - 75;
            kind = 0;
        } else {
            kind = 5;
            seq = anim - 105;
        }
    }
    bank = obj->banks[kind];
    if (bank != NULL) {
        if (seq >= *(u16*)(bank + 0xA) || seq < 0) {
            return;
        }
        entry->anim = bank;
        entry->seqNum = seq;
        entry->frame = lbl_803CC4B8;
        entry->animPending = 1;
        entry->framePending = entry->speedPending = (bank != NULL);
        entry->blendTime = blend;
    }
    if (obj->effectA != NULL) {
        actorRelated(obj->effectA + 4, kind, seq);
    }
    if (obj->effectB != NULL && obj->effectB[0xCC] != 0) {
        actorRelated(obj->effectB + 0x68, kind, seq);
        actorRelated(obj->effectB + 4, kind, seq);
    }
    if (boneParam != 0) {
        entry->boneParam = 3;
    } else {
        entry->boneParam = 2;
    }
    entry->frame = (f32)frame * obj->frameScale;
    entry->framePending = 1;

    cur = hugeAnimStruct.objects[index];
    if (cur != NULL) {
        if (mode == 0) {
            boneRoot = getAnimBone(cur, 4);
            boneEnd = getAnimBone(cur, 0);
        } else {
            boneRoot = getAnimBone(cur, 0);
            boneEnd = getAnimBone(cur, 0);
        }
        node = (u8*)hugeAnimStruct.actorTable + (u16)cur->slot * 0x90;
        maybeTransformVectorByAnimationMatrix(*(void**)(node + 0x34), *(u16*)(*(u8**)(node + 0x34) + 0x80), &offset);
        *(u16*)(node + 0x98) = boneEnd;
        *(u16*)(node + 0x9A) = boneRoot;
    }
    cur = hugeAnimStruct.objects[index];
    if (cur != NULL) {
        table = hugeAnimStruct.actorTable;
        if (attach == 0) {
            table->entries[cur->slot].unk68 = 0;
        } else {
            table->entries[cur->slot].unk68 = (u32)cur->attachPoint;
        }
    }
    obj->mode = mode;
}


void fn_8001BA44(s32 index, s16 anim, u8 boneParam, u8 mode, s16 frame, u8 attach, s32 speedDivisor) {
    f32 blend = lbl_803CC4B8;
    ModelAnimObject* obj = hugeAnimStruct.objects[index];
    ActorObjectEntry* entry;
    ActorObjectTable* table;
    s32 kind;
    s32 seq;
    u8* bank;
    ModelAnimObject* cur;
    u16 boneEnd;
    u16 boneRoot;
    u8* node;
    Vec offset;
    BOOL valid;

    if (obj == NULL) {
        return;
    }
    entry = &hugeAnimStruct.actorTable->entries[obj->slot];
    if ((u8)speedDivisor != 0) {
        blend = lbl_803CC4F0 / (f32)(u8)speedDivisor;
    }
    if (obj->flag26C == 0) {
        fn_800B2B54(obj->actor, getAnimBone(obj, 4), 13);
    } else {
        fn_800B2B54(obj->actor, getAnimBone(obj, 4), 1);
        fn_800B2B54((UnkB2B4C*)entry->actor, getAnimBone(hugeAnimStruct.objects[index], 4), 1);
        fn_800B2B4C((UnkB2B4C*)entry->actor, lbl_803CC504);
        *(f32*)((u8*)entry->actor + 0x8C) = lbl_803CC4B8;
    }

    if (anim < 0) {
        valid = FALSE;
    } else {
        if (anim < 45) {
            seq = anim;
            kind = 2;
        } else if (anim < 61) {
            seq = anim - 45;
            kind = 1;
        } else if (anim < 63) {
            seq = anim - 61;
            kind = 4;
        } else if (anim < 75) {
            seq = anim - 63;
            kind = 3;
        } else if (anim < 105) {
            seq = anim - 75;
            kind = 0;
        } else {
            kind = 5;
            seq = anim - 105;
        }
        valid = TRUE;
    }
    if (valid) {
        bank = obj->banks[kind];
        if (bank != NULL) {
            if (seq >= *(u16*)(bank + 0xA) || seq < 0) {
                return;
            }
            entry->anim = bank;
            entry->seqNum = seq;
            entry->frame = lbl_803CC4B8;
            entry->animPending = 1;
            entry->framePending = entry->speedPending = (bank != NULL);
            entry->blendTime = blend;
        }
    } else {
        entry->anim = NULL;
        entry->seqNum = 0;
        entry->frame = lbl_803CC4B8;
        entry->animPending = 1;
        entry->framePending = 0;
        entry->speedPending = 0;
        entry->blendTime = lbl_803CC4B8;
        return;
    }
    if (obj->effectA != NULL) {
        actorRelated(obj->effectA + 4, kind, seq);
    }
    if (obj->effectB != NULL) {
        fn_80011CA8(obj, kind, seq);
    }
    if (boneParam != 0) {
        entry->boneParam = 3;
    } else {
        entry->boneParam = 2;
    }
    entry->frame = (f32)frame * obj->frameScale;
    entry->framePending = 1;

    cur = hugeAnimStruct.objects[index];
    if (cur != NULL) {
        if (mode == 0) {
            boneRoot = getAnimBone(cur, 4);
            boneEnd = getAnimBone(cur, 0);
        } else {
            boneRoot = getAnimBone(cur, 0);
            boneEnd = getAnimBone(cur, 0);
        }
        node = (u8*)hugeAnimStruct.actorTable + (u16)cur->slot * 0x90;
        maybeTransformVectorByAnimationMatrix(*(void**)(node + 0x34), *(u16*)(*(u8**)(node + 0x34) + 0x80), &offset);
        *(u16*)(node + 0x98) = boneEnd;
        *(u16*)(node + 0x9A) = boneRoot;
    }
    cur = hugeAnimStruct.objects[index];
    if (cur != NULL) {
        table = hugeAnimStruct.actorTable;
        if (attach == 0) {
            table->entries[cur->slot].unk68 = 0;
        } else {
            table->entries[cur->slot].unk68 = (u32)cur->attachPoint;
        }
    }
    obj->mode = mode;
}

/* Signed variant of maxFileSizeOfSix. */
static inline s32 maxFileSizeOfSixS32(s32 maxSize, int idx) {
    s32 k;

    for (k = 0; k < 6; k++) {
        s32 v = ((FileTableEntry*)lbl_803CB7A8)[idx + k].size & 0x0FFFFFFF;
        if (maxSize < v) {
            maxSize = v;
        }
    }
    return maxSize;
}

void fn_80014204(s32 count) {
    s32 size;
    u8* pool;
    s32 total;
    s32 i;
    s32 fileBase = 0;
    u8* rec;
    s32 a;
    s32 b;
    s32 maxSize = 0;

    for (i = 0; i < 54; i++) {
        if (lbl_800EEAAC[i] >= 0) {
            maxSize = maxFileSizeOfSixS32(maxSize, fileBase);
            fileBase += 6;
        }
    }

    size = (maxSize + 0x1F) & ~0x1F;
    pool = _OSAllocFromHeap(0x20, count * (size * 6));
    lbl_803CBC24 = pool;
    total = count * 3;
    for (i = 0; i < total; i++) {
        u8* rec = HA(i * 0xD4);

        *(u32*)(rec + 0x140) = (u32)lbl_803CBC24 + size * (i * 2);
        *(u32*)(rec + 0x1A4) = (u32)lbl_803CBC24 + size * (i * 2 + 1);
    }
    for (i = 0, rec = HA(0), a = 0, b = 1; i < total; i++, rec += 0xD4, a += 2, b += 2) {
        ((s8*)rec)[0x210] = -1;
        ((s8*)rec)[0x211] = -1;
        ((s8*)rec)[0x20F] = -1;
        rec[0x20E] = 0xFF;
        rec[0x20D] = 0xFF;
        *(u32*)(rec + 0x208) = 0;
        rec[0x20C] = 0;
        rec[0x1A0] = a;
        rec[0x204] = b;
    }
}

#define MODEL_ARAM_FILE(rec, offset) ((u8*)lbl_803CB790 + ((s8)(rec)[0x252] * 0x13 + (offset)) * 16)
#define MODEL_RECORD_BUFFER(rec, offset) (*(u32*)(HA((s8)(rec)[0x255] * 0x14 + (offset))))
#define MODEL_LOAD_STATE (*HA(0x2D8D))
#define MODEL_ANIM_READY (((u8*)&lbl_803C6CF8)[0x715] == 1)

BOOL fn_80016B60(void* record) {
    u8* rec = record;
    s32 fileOffset;

    if (MODEL_LOAD_STATE == 0) {
        MODEL_LOAD_STATE = 1;
    }
    if (MODEL_LOAD_STATE == 1) {
        *(u32*)(rec + 0x18) = MODEL_RECORD_BUFFER(rec, 0x2CEC);
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
            fileOffset = 0xD;
        } else {
            fileOffset = 4;
        }
        ARAMTransfer(MODEL_ARAM_FILE(rec, fileOffset), *(s32*)(rec + 0x18), 0, 0);
        MODEL_LOAD_STATE = 2;
    } else if (MODEL_LOAD_STATE == 2) {
        if (MODEL_ANIM_READY) {
            ANIMGet(*(void**)(rec + 0x18));
            MODEL_LOAD_STATE = 3;
        }
    } else if (MODEL_LOAD_STATE == 3) {
        *(u32*)(rec + 0x14) = MODEL_RECORD_BUFFER(rec, 0x2CF0);
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
            fileOffset = 0xB;
        } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
            fileOffset = 0xE;
        } else {
            fileOffset = 0xC;
        }
        ARAMTransfer(MODEL_ARAM_FILE(rec, fileOffset), *(s32*)(rec + 0x14), 0, 0);
        MODEL_LOAD_STATE = 4;
    } else if (MODEL_LOAD_STATE == 4) {
        if (MODEL_ANIM_READY) {
            ANIMGet(*(void**)(rec + 0x14));
            MODEL_LOAD_STATE = 5;
        }
    } else if (MODEL_LOAD_STATE == 5) {
        *(u32*)(rec + 0x1C) = MODEL_RECORD_BUFFER(rec, 0x2CF4);
        if (g_d_GameSettings.minigamesEnabled != 0 || g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
            fileOffset = 0x12;
        } else {
            fileOffset = 5;
        }
        ARAMTransfer(MODEL_ARAM_FILE(rec, fileOffset), *(s32*)(rec + 0x1C), 0, 0);
        MODEL_LOAD_STATE = 6;
    } else if (MODEL_LOAD_STATE == 6) {
        if (MODEL_ANIM_READY) {
            ANIMGet(*(void**)(rec + 0x1C));
            *(u32*)(rec + 0x10) = HA_U32(0x2CF8);
            MODEL_LOAD_STATE = 9;
        }
    } else if (MODEL_LOAD_STATE == 7) {
        *(u32*)(rec + 0x10) = MODEL_RECORD_BUFFER(rec, 0x2CF8);
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
            fileOffset = 9;
        } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
            fileOffset = 0xA;
        } else {
            fileOffset = 2;
        }
        ARAMTransfer(MODEL_ARAM_FILE(rec, fileOffset), *(s32*)(rec + 0x10), 0, 0);
        MODEL_LOAD_STATE = 8;
    } else if (MODEL_LOAD_STATE == 8) {
        if (MODEL_ANIM_READY) {
            ANIMGet(*(void**)(rec + 0x10));
            MODEL_LOAD_STATE = 9;
        }
    } else if (MODEL_LOAD_STATE == 9) {
        *(u32*)(rec + 0x24) = MODEL_RECORD_BUFFER(rec, 0x2CFC);
        ARAMTransfer(MODEL_ARAM_FILE(rec, 0x10), *(s32*)(rec + 0x24), 0, 0);
        MODEL_LOAD_STATE = 10;
    } else if (MODEL_LOAD_STATE == 10) {
        if (MODEL_ANIM_READY) {
            ANIMGet(*(void**)(rec + 0x24));
            MODEL_LOAD_STATE = 0;
            return TRUE;
        }
    }
    return FALSE;
}

extern BOOL fn_80012B90(void* record);

int fn_80016710(int charId, int slot) {
    u8* rec;
    BOOL ready;
    u8* part;
    u8* effectBuf;

    if (*HA(0x2D77) == 6) {
        return 1;
    }
    if (*HA(0x2D77) == 1) {
        return 0;
    }
    if (*HA(0x2D77) == 2) {
        HA_OBJ(slot) = HA(MODEL_RECORD_BASE + slot * MODEL_RECORD_SIZE);
        *HA(0x2D8D) = 0;
        *HA(0x2D77) = 3;
    }

    if (*HA(0x2D77) == 3) {
        rec = HA(MODEL_RECORD_BASE + slot * MODEL_RECORD_SIZE);
        if (*HA(0x2D8D) == 0) {
            *HA(0x2D8D) = 1;
            *HA(0x2D7F + slot) = rec[0x252];
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
                *(u32*)(rec + 0x24) = HA_U32(0x2CAC);
                fn_80021BBC((s8)rec[0x252], *(s32*)(rec + 0x24));
            } else if (slot >= 9) {
                *(u32*)(rec + 0x24) = HA_U32(0x2CAC);
                ARAMTransfer((u8*)lbl_803CB790 + ((s8)rec[0x252] * 0x13 + 0x10) * 16, *(s32*)(rec + 0x24), 0, 0);
            } else {
                *(u32*)(rec + 0x24) = HA_U32(0x2CFC + slot * 0x14);
                fn_80021BBC((s8)rec[0x252], *(s32*)(rec + 0x24));
            }
            ready = FALSE;
        } else {
            ready = FALSE;
            if (((u8*)&lbl_803C6CF8)[0x715] == 1) {
                ANIMGet(*(void**)(rec + 0x24));
                ready = TRUE;
            }
        }
        if (!ready) {
            return 0;
        }
        *HA(0x2D77) = 4;
    }

    if (*HA(0x2D77) == 4) {
        s32 fileIndex = lbl_800EEB18[(u8)charId];

        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
            if (fileIndex != -1) {
                u8* slotRec = HA(MODEL_RECORD_BASE + slot * MODEL_RECORD_SIZE);

                part = *(u8**)(slotRec + 8);
                if (*(u32*)(part + 0x10) != 0) {
                    if (lbl_803CBBFA == 0) {
                        fn_80021ADC(fileIndex, *(void**)lbl_80118220);
                        lbl_803CBBFA = 1;
                    }
                    if (((u8*)&lbl_803C6CF8)[0x715] == 1) {
                        lbl_80118220[0x60] = charId;
                        lbl_80118220[0x61] = slot;
                        *(u32*)(lbl_80118220 + 4) = *(u32*)lbl_80118220;
                        actRelated(*(void**)(part + 0x10), lbl_80118220 + 4);
                        lbl_803CBBFA = 0;
                        *(u8**)(slotRec + 0x2C) = lbl_80118220;
                        ready = TRUE;
                    } else {
                        ready = FALSE;
                    }
                } else {
                    goto noPartPractice;
                }
            } else {
            noPartPractice:
                *(u32*)(HA(MODEL_RECORD_BASE + slot * MODEL_RECORD_SIZE) + 0x2C) = 0;
                ready = TRUE;
            }
        } else {
            if (fileIndex != -1) {
                u8* slotRec = HA(MODEL_RECORD_BASE + slot * MODEL_RECORD_SIZE);

                part = *(u8**)(slotRec + 8);
                if (*(u32*)(part + 0x10) != 0) {
                    if (lbl_803CBBFA == 0) {
                        fn_80021ADC(fileIndex, *(void**)(lbl_80118220 + slot * 0x64));
                        lbl_803CBBFA = 1;
                    }
                    if (((u8*)&lbl_803C6CF8)[0x715] == 1) {
                        effectBuf = lbl_80118220 + slot * 0x64;
                        effectBuf[0x60] = charId;
                        effectBuf[0x61] = slot;
                        *(u32*)(effectBuf + 4) = *(u32*)effectBuf;
                        actRelated(*(void**)(part + 0x10), effectBuf + 4);
                        lbl_803CBBFA = 0;
                        *(u8**)(slotRec + 0x2C) = effectBuf;
                        ready = TRUE;
                    } else {
                        ready = FALSE;
                    }
                } else {
                    goto noPart;
                }
            } else {
            noPart:
                *(u32*)(HA(MODEL_RECORD_BASE + slot * MODEL_RECORD_SIZE) + 0x2C) = 0;
                ready = TRUE;
            }
        }
        if (!ready) {
            return 0;
        }
        *HA(0x2D77) = 5;
    }

    if (*HA(0x2D77) == 5) {
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
            ready = animateModelArmsGlovesBats(HA(MODEL_RECORD_BASE + slot * MODEL_RECORD_SIZE));
        } else {
            ready = fn_80012B90(HA(MODEL_RECORD_BASE + slot * MODEL_RECORD_SIZE));
        }
        if (!ready) {
            return 0;
        }
        return 1;
    }
    fn_80017098(0, 0, 0, slot, 1, charId);
    return 0;
}

extern u8 lbl_803CBBF9;

#define EFFECT_BUF(i) (lbl_80118220 + (i) * 0x64)

int fn_8001500C(int team, int idx, int slot) {
    u8* obj;
    u8* buf;
    s32 i;
    s32 found;
    s32 ok;
    s32 result;
    u8 charId;
    u8* flags = lbl_803CBC34;

    if (*HA(0x2D77) == 1) {
        return 0;
    }
    if (*HA(0x2D77) == 2) {
        HA_OBJ(slot) = HA(MODEL_RECORD_BASE + *HA(0x2D79) * MODEL_RECORD_SIZE);
        *HA(0x2D8D) = 0;
        *HA(0x2D77) = 3;
    }

    if (*HA(0x2D77) == 3) {
        if (fn_80017340(*HA(0x2D79))) {
            if (*HA(0x2D78) != 0 && *(u32*)(HA_OBJ(slot) + 0x2C) != 0) {
                if (*(u32*)(HA_OBJ(slot) + 0x30) == 0) {
                    *HA(0x2D77) = 5;
                    return 0;
                }
                *HA(0x2D77) = 0;
                return 1;
            }
            if (flags[3] != 0) {
                *HA(0x2D77) = 4;
            } else if (flags[4] != 0 && slot == 9) {
                *HA(0x2D77) = 4;
            } else {
                *HA(0x2D77) = 5;
            }
        } else {
            return 0;
        }
    }

    if (*HA(0x2D77) == 4) {
        obj = HA_OBJ(slot);
        charId = obj[0x252];
        found = FALSE;
        if (lbl_803CBBF9 == 0) {
            buf = lbl_80118220;
            for (i = 0; (s8)buf[0x61] != -2; i++, buf += 0x64) {
                if ((s8)charId == (s8)buf[0x60] && (s8)buf[0x61] == -1) {
                    buf = EFFECT_BUF(i);
                    *(u8**)(obj + 0x2C) = buf;
                    buf[0x60] = charId;
                    buf[0x61] = slot;
                    *(u32*)(buf + 0x30) = *(u32*)(*(u8**)(obj + 8) + 0x10);
                    found = TRUE;
                    break;
                }
            }
            if (!found) {
                lbl_803CBBF9 = 1;
                buf = lbl_80118220;
                for (i = 0; (s8)buf[0x61] != -2; i++, buf += 0x64) {
                    if ((s8)buf[0x61] == -1) {
                        break;
                    }
                }
                lbl_803CBC28 = i;
            }
        }
        if (!found) {
            s32 k = lbl_803CBC28;
            s32 fileIndex = lbl_800EEB18[charId];

            buf = EFFECT_BUF(k);
            buf[0x5D] = 0;
            if (fileIndex == -1 || *(u32*)(*(u8**)(obj + 8) + 0x10) == 0) {
                *(u32*)(obj + 0x2C) = 0;
                ok = TRUE;
            } else {
                if (lbl_803CBBFA == 0) {
                    fn_80021ADC(fileIndex, *(void**)buf);
                    lbl_803CBBFA = 1;
                }
                if (((u8*)&lbl_803C6CF8)[0x715] == 1) {
                    buf = EFFECT_BUF(k);
                    buf[0x60] = charId;
                    buf[0x61] = slot;
                    *(u32*)(buf + 4) = *(u32*)buf;
                    actRelated(*(void**)(*(u8**)(obj + 8) + 0x10), buf + 4);
                    *(u8**)(obj + 0x2C) = buf;
                    lbl_803CBBFA = 0;
                    ok = TRUE;
                } else {
                    ok = FALSE;
                }
            }
            if (ok) {
                lbl_803CBBF9 = 0;
                found = TRUE;
            }
        }
        if (found) {
            if (*HA(0x2D78) != 0 && *(u32*)(HA_OBJ(slot) + 0x30) != 0) {
                *HA(0x2D77) = 0;
                return 1;
            }
            *HA(0x2D77) = 5;
        } else {
            return 0;
        }
    }

    if (*HA(0x2D77) == 5) {
        if (animateModelArmsGlovesBats(HA_OBJ(slot))) {
            *HA(0x2D77) = 0;
            return 1;
        }
        return 0;
    }

    if (slot == 9) {
        *HA(0x2D78) = fn_80017098(team, idx, 1, slot, 1, -1);
    } else {
        *HA(0x2D78) = fn_80017098(team, idx, 1, slot, 0, -1);
    }
    result = *HA(0x2D78);
    if (result == 0) {
        return result;
    }
    if (slot == 9) {
        *HA(0x2D77) = 2;
        return 0;
    }
    if (*(u32*)(HA_OBJ(slot) + 0x30) == 0) {
        *HA(0x2D77) = 5;
        return 0;
    }
    return result;
}

extern f32 lbl_803CB7BC;
extern u8 lbl_803CB7C0;
extern u8 lbl_803CB7C1;
extern u8 fn_8003AE54(void);

void fn_8001AB10(StadiumModel* model, Mtx camera) {
    ActorObjectEntry* entry = (ActorObjectEntry*)model;
    u8* rec = HA(MODEL_RECORD_BASE + entry->slot * MODEL_RECORD_SIZE);
    BOOL isToyField = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD;
    GXColor color;
    Mtx trans;
    Mtx world;
    f32 height;
    f32 fade;
    u8 shade;
    Actor* actor;
    u32* args;

    if (rec[0x25D] == 3) {
        height = *(f32*)(rec + 0x38);
        if (height < lbl_803CC4B8) {
            height = -height;
        }
        fade = (lbl_803CB7BC - height) / lbl_803CB7BC;
        if (fade > lbl_803CC4F0) {
            fade = lbl_803CC4F0;
        } else if (fade < lbl_803CC4B8) {
            fade = lbl_803CC4B8;
        }
        shade = (u8)(fade * (f32)fn_8003AE54());
        color.a = 0xFF;
        color.r = shade;
        color.g = shade;
        color.b = shade;
    } else if (rec[0x25D] == 1) {
        if (rec[0x277] == 0) {
            return;
        }
        shade = fn_8003AE54();
        color.r = shade;
        color.g = shade;
        color.b = shade;
        color.a = rec[0x277];
    } else {
        return;
    }
    GXSetChanMatColor(GX_COLOR0A0, color);

    if (isToyField) {
        PSMTXTrans(trans, *(f32*)(rec + 0x34), *(f32*)(rec + 0x38), *(f32*)(rec + 0x3C));
    } else {
        PSMTXTrans(trans, *(f32*)(rec + 0x34), *(f32*)(rec + 0x38), *(f32*)(rec + 0x3C));
    }

    if (!isToyField) {
        sBone* bone;
        Actor* skinActor;

        PSMTXConcat(camera, trans, world);
        skinActor = entry->actor;
        for (bone = (sBone*)skinActor->drawPriorityList.Head; bone != NULL; bone = (sBone*)bone->drawPriorityLink.Next) {
            if (bone->dispObj != NULL) {
                DOSetWorldMatrix(bone->dispObj, bone->forwardMtx);
                fn_8003A8A0(bone->dispObj, world, 1);
            }
        }
        skinActor = entry->actor;
        if (skinActor->skinObject != NULL) {
            if (skinActor->skHeader != NULL) {
                fn_8003A8A0(skinActor->skinObject, world, 0);
            } else {
                DOVARenderSkin(skinActor->skinObject, camera, skinActor->skinMtxArray, skinActor->skinInvTransposeMtxArray,
                               0, NULL);
            }
        }
        shade = fn_8003AE54();
        color.r = shade;
        color.g = shade;
        color.b = shade;
        color.a = 0xFF;
        GXSetChanMatColor(GX_COLOR0A0, color);
        return;
    }

    color.r = lbl_803CB7C1;
    color.g = lbl_803CB7C1;
    color.b = lbl_803CB7C1;
    color.a = lbl_803CB7C0;
    adjustLightingParams(1, color);
    PSMTXConcat(camera, trans, world);
    actor = entry->actor;
    args = entry->drawArgs;
    if (entry->callback != NULL) {
        entry->callback(entry);
    }
    switch (entry->drawArgCount) {
    case 0:
        fn_8001DD58(actor, 0, world, 0);
        break;
    case 1:
        fn_8001DD58(actor, 0, world, 1, args[0]);
        break;
    case 2:
        fn_8001DD58(actor, 0, world, 2, args[0], args[1]);
        break;
    case 3:
        fn_8001DD58(actor, 0, world, 3, args[0], args[1], args[2]);
        break;
    case 4:
        fn_8001DD58(actor, 0, world, 4, args[0], args[1], args[2], args[3]);
        break;
    case 5:
        fn_8001DD58(actor, 0, world, 5, args[0], args[1], args[2], args[3], args[4]);
        break;
    case 6:
        fn_8001DD58(actor, 0, world, 6, args[0], args[1], args[2], args[3], args[4], args[5]);
        break;
    case 7:
        fn_8001DD58(actor, 0, world, 7, args[0], args[1], args[2], args[3], args[4], args[5], args[6]);
        break;
    case 8:
        fn_8001DD58(actor, 0, world, 8, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]);
        break;
    }
}

extern f32 lbl_803CC4D0;

void fn_80017814(u8* rec, s32 slot, s32 mode, void (*callback)(u8*)) {
    ActorObjectEntry* entry = &hugeAnimStruct.actorTable->entries[slot];
    u32* header = *(u32**)(rec + 8);
    u32 layout;
    u32 geo;
    u32 skn;
    u32 tex;
    void* anim;
    u16 boneCount;
    s32 bone;
    u16 boneId;
    s32 i;

    if (header[0] != 0) {
        (*(u32**)(rec + 8))[0] = (u32)header + header[0];
        if ((*(u32**)(rec + 8))[1] != 0) {
            (*(u32**)(rec + 8))[1] = (u32)header + header[1];
            if ((*(u32**)(rec + 8))[2] != 0) {
                (*(u32**)(rec + 8))[2] = (u32)header + header[2];
                if ((*(u32**)(rec + 8))[3] != 0) {
                    (*(u32**)(rec + 8))[3] = (u32)header + header[3];
                    if ((*(u32**)(rec + 8))[4] != 0) {
                        (*(u32**)(rec + 8))[4] = (u32)header + header[4];
                    }
                }
            }
        }
    }
    tex = (*(u32**)(rec + 8))[0];
    convertTextureHeader((void*)tex);
    layout = (*(u32**)(rec + 8))[1];
    if (layout != 0) {
        geo = (*(u32**)(rec + 8))[2];
        skn = (*(u32**)(rec + 8))[3];
        LoadActorLayout((void*)layout);
        convertGeometryAndSknHeader((void*)geo, (void*)skn);
        haveActLayoutPointToGeoHeader((void*)layout, (void*)geo);
        UpdateTexturePalettePointers((void*)geo, (void*)tex);
    } else {
        return;
    }

    if (mode < 9) {
        anim = *(void**)(rec + 0x18);
    } else {
        anim = *(void**)(rec + 0x14);
    }
    characterAndBallDisplayRelated(entry, (s8)rec[0x255], (u16)slot, (ActorLayout*)layout, anim, skn);
    if ((*(u32**)(rec + 8))[4] != 0) {
        adjustInternalPointers((void*)(*(u32**)(rec + 8))[4]);
        ACTActorRelated((void*)(*(u32**)(rec + 8))[4], entry);
    }

    boneCount = *(u16*)((u8*)entry->actor + 6);
    memset(rec + 0x162, 0xFF, 0xF0);
    for (i = 0; i < boneCount; i++) {
        boneId = **(u16**)(*(u8**)((u8*)entry->actor + 0x18) + i * 4);
        if (boneId != 0xFFFF) {
            *(u16*)(rec + 0x162 + boneId * 2) = i;
        }
    }
    bone = *(u16*)(rec + 0x188);
    callDSInsertListObject((UnkB2B4C*)entry->actor, bone);
    bone = *(u16*)(rec + 0x194);
    callDSInsertListObject((UnkB2B4C*)entry->actor, bone);
    bone = *(u16*)(rec + 0x1AA);
    callDSInsertListObject((UnkB2B4C*)entry->actor, bone);
    *(Actor**)rec = entry->actor;
    bone = *(u16*)(rec + 0x168);
    if (bone != 0xFFFF) {
        fn_800B2B54(*(UnkB2B4C**)rec, bone, 13);
    }
    fn_800BD548(entry, 4, HA_U32(0xAC), HA_U32(0xB0), HA_U32(0xB4), HA_U32(0xB8));
    CTRLSetTranslation(&entry->control, lbl_803CC4B8, lbl_803CC4B8, lbl_803CC4B8);
    CTRLSetRotation(&entry->control, lbl_803CC4B8, lbl_803CC4B8, lbl_803CC4B8);
    entry->speed = lbl_803CC4D0;
    entry->speedPending = 1;
    bone = *(u16*)(rec + 0x168);
    if (bone != 0xFFFF) {
        fn_800B2BA8(entry->actor, bone, NULL, 0);
        MODEL_BONE_FLAGGED(entry->actor, (u16)bone) = 1;
    }
    bone = *(u16*)(rec + 0x166);
    if (bone != 0xFFFF) {
        fn_800B2BA8(entry->actor, bone, NULL, 0);
        MODEL_BONE_FLAGGED(entry->actor, (u16)bone) = 1;
    }
    bone = *(u16*)(rec + 0x164);
    if (bone != 0xFFFF) {
        fn_800B2BA8(entry->actor, bone, NULL, 0);
        MODEL_BONE_FLAGGED(entry->actor, (u16)bone) = 1;
    }
    bone = *(u16*)(rec + 0x1AA);
    if (bone != 0xFFFF) {
        fn_800B2BA8(entry->actor, bone, NULL, 0);
    }
    bone = *(u16*)(rec + 0x1BE);
    if (bone != 0xFFFF) {
        fn_800B2BA8(entry->actor, bone, NULL, 0);
        MODEL_BONE_FLAGGED(entry->actor, (u16)bone) = 1;
    }
    fn_800B2C08(entry->actor, *(u16*)(rec + 0x16A));
    initShortsHandleCompressedDiskReads((ShortsTableOwner*)rec);
    entry->callback = (void (*)(ActorObjectEntry*))callback;

    for (i = 0; i < 8; i++) {
        *(s16*)(rec + 0x60 + i * 2) = -1;
    }
    rec[0x25D] = 0;
    rec[0x25E] = 0;
    rec[0x25F] = 0;
    rec[0x260] = 0;
    rec[0x261] = 0;
    rec[0x262] = 0;
    rec[0x263] = 0;
    rec[0x264] = 0;
    rec[0x265] = 0;
    rec[0x266] = 0;
    rec[0x267] = 0;
    rec[0x268] = 0;
    rec[0x269] = 0;
    rec[0x26A] = 0;
    rec[0x26B] = 0;
    rec[0x26C] = 0;
    rec[0x26D] = 0;
    rec[0x26E] = 0;
    rec[0x270] = 0;
    rec[0x271] = 0;
    rec[0x272] = 0;
    rec[0x273] = 0;
    rec[0x277] = 0xFF;

    switch ((s8)rec[0x252]) {
    case CHAR_ID_DK:
        fn_800638B4(rec, entry);
        break;
    case CHAR_ID_MAGIKOOPA_BLUE:
    case CHAR_ID_MAGIKOOPA_RED:
    case CHAR_ID_MAGIKOOPA_GREEN:
    case CHAR_ID_MAGIKOOPA_YELLOW:
        fn_80063010(rec, entry);
        break;
    case CHAR_ID_BOWSERJR:
        fn_8004B7B4(rec, entry);
        break;
    case CHAR_ID_KOOPA_GREEN:
    case CHAR_ID_PIANTA_BLUE:
    case CHAR_ID_PIANTA_RED:
    case CHAR_ID_PIANTA_YELLOW:
    case CHAR_ID_KOOPA_RED:
        entry->actor->unk98 = 1;
        break;
    case CHAR_ID_NOKI_BLUE:
    case CHAR_ID_NOKI_RED:
    case CHAR_ID_NOKI_GREEN:
        entry->actor->unk98 = 1;
        break;
    case CHAR_ID_PARATROOPA_RED:
    case CHAR_ID_PARATROOPA_GREEN:
        fn_800637BC(rec, entry);
        break;
    case CHAR_ID_PETEY:
        entry->actor->unk98 = 1;
        initSpecialHandBones(rec, entry);
        break;
    case CHAR_ID_PARAGOOMBA:
        fn_800637D4(rec, entry);
        /* fallthrough */
    case CHAR_ID_MONTY:
    case CHAR_ID_GOOMBA:
        initSpecialHandBones(rec, entry);
        break;
    case CHAR_ID_BOO:
    case CHAR_ID_KINGBOO:
        fn_80052634(rec, entry);
        break;
    case CHAR_ID_SHYGUY_RED:
    case CHAR_ID_SHYGUY_BLUE:
    case CHAR_ID_SHYGUY_YELLOW:
    case CHAR_ID_SHYGUY_GREEN:
    case CHAR_ID_SHYGUY_BLACK:
        fn_80062ED4(rec, entry);
        break;
    }
}

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


void fn_80019C00(void) {
    DrawingSceneStruct* item = currentDrawingItem;
    u8* itemState = (u8*)item + 0x14;
    DrawingSceneStruct* fresh;
    Vec dir;
    Vec copy;
    f32 len;
    s32 i;
    s32 k;
    u32 maxSize;
    u32 v;
    u32 size;
    u8* pool;
    s16* entry;
    u8* effects = lbl_80118220;

    switch (*itemState) {
    case 0:
        setupAnimationModelMemory();
        initActorArray(((g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) + 1) * 4);
        for (k = 4; k <= 12; k++) {
            effects[0x61 + k * 0x64] = 0xFF;
        }
        maxSize = 0;
        entry = lbl_800EEB18;
        for (i = 0; i < 18; i++) {
            if (entry[0] >= 0) {
                v = *(u32*)((u8*)lbl_803CB794 + entry[0] * 16 + 4) & 0x0FFFFFFF;
                if (maxSize < v) {
                    maxSize = v;
                }
            }
            if (entry[1] >= 0) {
                v = *(u32*)((u8*)lbl_803CB794 + entry[1] * 16 + 4) & 0x0FFFFFFF;
                if (maxSize < v) {
                    maxSize = v;
                }
            }
            if (entry[2] >= 0) {
                v = *(u32*)((u8*)lbl_803CB794 + entry[2] * 16 + 4) & 0x0FFFFFFF;
                if (maxSize < v) {
                    maxSize = v;
                }
            }
            entry += 3;
        }
        size = (maxSize + 0x1F) & ~0x1F;
        pool = _OSAllocFromHeap(0x20, size * 4);
        lbl_803CBC30 = pool;
        *(u8**)effects = pool;
        effects[0x61] = 0xFF;
        effects[0x60] = 0xFF;
        *(u32*)(effects + 0x64) = (u32)pool + size;
        effects[0xC5] = 0xFF;
        effects[0xC4] = 0xFF;
        *(u32*)(effects + 0xC8) = (u32)pool + size * 2;
        effects[0x129] = 0xFF;
        effects[0x128] = 0xFF;
        *(u32*)(effects + 0x12C) = (u32)pool + size * 3;
        effects[0x18D] = 0xFF;
        effects[0x18C] = 0xFF;
        fn_80014204(4);
        HA_U32(0x13C) = (u32)fn_80023AA4();
        for (k = 0; k < 4; k++) {
            HA(MODEL_RECORD_BASE + k * MODEL_RECORD_SIZE)[0x255] = k;
            HA_OBJ(k) = NULL;
            *HA(0x2D6A + k) = 0xFF;
            HA(MODEL_RECORD_BASE + k * MODEL_RECORD_SIZE)[0x257] = 0xFF;
        }
        for (i = 0; i < 9; i++) {
            *HA(0x2D7F + i) = 0xFF;
        }
        *HA(0x2D89) = 0xFF;
        *HA(0x2D8A) = 0xFF;
        *HA(0x2D8B) = 0xFF;
        *HA(0x2D8C) = 0xFF;
        *HA(0x2D77) = 0;
        *HA(0x2D7B) = 0;
        *HA(0x2D7C) = 0;
        (*itemState)++;
        break;
    case 1:
        fresh = insertGraphicDrawingFunction(fn_800188C0, 0);
        *((u8*)fresh + 0x14) = 0;
        *((u8*)fresh + 0x16) = 0;
        *((u8*)fresh + 0x17) = 0xFF;
        *HA(0x307B) = 1;
        (*itemState)++;
        break;
    case 2:
        if (*HA(0x307B) == 0) {
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                *itemState = *itemState + 1;
            } else {
                *itemState = 5;
            }
        }
        break;
    case 3:
        HA_U32(0x2D9C) = (u32)ARAMTransfer(MinigameCommonFiles, 0, 0, 0);
        (*itemState)++;
        break;
    case 4:
        if (((u8*)&lbl_803C6CF8)[0x715] == 1) {
            *itemState = *itemState + 1;
        }
        break;
    case 5:
        dir.x = -lbl_80367318[0].pos.x;
        dir.y = -lbl_80367318[0].pos.y;
        dir.z = -lbl_80367318[0].pos.z;
        len = dolsqrtf2((dir.x * dir.x) + (dir.y * dir.y) + (dir.z * dir.z));
        *HA(0x3087) = 1;
        dir.x /= len;
        dir.y /= len;
        dir.z /= len;
        fn_8003A540(0);
        *HA(0x3086) = 1;
        DrawShadows(1);
        copy = dir;
        updateVectorInArray(0, copy);
        fn_800BF048(fn_8001AAF0);
        fn_800BF058(fn_8001AB10);
        for (i = 0; i < 80; i += 8) {
            for (k = 0; k < 8; k++) {
                ((u32*)HA_U32(0x2C84))[i + k] += HA_U32(0x2C84);
            }
        }
        *HA(0x307C) = 0;
        *HA(0x307D) = 0;
        *HA(0x3082) = 0;
        fn_8001F8A4();
        (*itemState)++;
        break;
    case 6:
        challengeMapMaybe();
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
            somethingFileHandlingLoadingRelated();
        }
        (*itemState)++;
        break;
    default:
        *HA(0x2D7D) = 1;
        *HA(0x307C) = 1;
        removeCurrentDrawingItem();
        break;
    }
}

void fn_8001C234(u32* changedMask);
extern f32 lbl_803CC510;
extern int fn_80024C6C(void* obj, int which);
extern void fn_800B2C88(Actor* actor, u16 bone, Mtx out);

#define STATE_FLAG_BIT7(p, v) ((p)[0x11] = ((p)[0x11] & 0x7F) | ((v) << 7))
#define MODEL_STATE_VIEW(p) ((u8*)(p))

void fn_8001D2D4(void) {
    u32 changedMask;
    s32 i;
    s32 k;
    u8* obj;
    ActorObjectEntry* entry;
    Actor* actor;
    u8* shadowA;
    u8* shadowB;
    u8* shadowC;
    u8* effectFile;
    f32 scale;
    Vec point;
    Vec transformed;
    Mtx mtx;
    u8* gs = (u8*)&g_d_GameSettings;
    u8* item;

    if (*HA(0x307A) == 0 || *HA(0x307C) == 0) {
        return;
    }
    if (lbl_80366158[0x28] != 0) {
        highLevelSimulationFlag[0] = 1;
    }
    fn_8001C234(&changedMask);

    for (i = 0; i < 13; i++) {
        obj = HA_OBJ(i);
        if (obj == NULL) {
            continue;
        }
        entry = &hugeAnimStruct.actorTable->entries[(s8)obj[0x255]];
        switch ((s8)obj[0x252]) {
        case CHAR_ID_BOWSERJR:
            fn_8004B6EC(obj);
            break;
        case CHAR_ID_GOOMBA:
        case CHAR_ID_PARAGOOMBA:
            processCharacterStateBasedOnGameMode((CharacterStateActor*)obj);
            break;
        case CHAR_ID_PETEY:
            entry->actor->unk98 = 1;
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
            entry->actor->unk98 = 1;
            break;
        case CHAR_ID_PARATROOPA_RED:
        case CHAR_ID_PARATROOPA_GREEN:
            if (*(s16*)(obj + 0x62) == 0x40) {
                entry->actor->unk98 = 0;
            } else {
                entry->actor->unk98 = 1;
            }
            break;
        }
    }

    for (i = 0; i < hugeAnimStruct.actorTable->count; i++) {
        hugeAnimStruct.actorTable->entries[i].applyControl = 0;
    }

    for (i = 0; i < 13; i++) {
        obj = HA_OBJ(i);
        if (obj == NULL) {
            continue;
        }
        entry = &hugeAnimStruct.actorTable->entries[(s8)obj[0x255]];
        shadowA = NULL;
        if (*(u8**)(obj + 0x2C) != NULL) {
            shadowA = *(u8**)(obj + 0x2C) + 0x10;
        }
        if (*(u8**)(obj + 0x30) != NULL) {
            shadowB = *(u8**)(obj + 0x30) + 0x10;
            shadowC = *(u8**)(obj + 0x30) + 0x74;
        } else {
            shadowB = NULL;
            shadowC = NULL;
        }
        entry->applyControl = obj[0x25D];
        CTRLSetRotation(&entry->control, lbl_803CC510 * *(f32*)(obj + 0x40), lbl_803CC510 * *(f32*)(obj + 0x44),
                        lbl_803CC510 * *(f32*)(obj + 0x48));
        scale = charSizeMultipliers[(s8)obj[0x252]][*HA(0x307A) == 5];
        CTRLSetScale(&entry->control, scale, scale, scale);
        if (highLevelSimulationFlag[0] != 0) {
            entry->speed = lbl_803CC4B8;
            entry->speedPending = 1;
            if (shadowA != NULL) {
                STATE_FLAG_BIT7(shadowA, 0);
            }
            if (shadowB != NULL) {
                STATE_FLAG_BIT7(shadowB, 0);
            }
            if (shadowC != NULL) {
                STATE_FLAG_BIT7(shadowC, 0);
            }
        } else if (obj[0x26F] != 0) {
            entry->speed = lbl_803CC4B8;
            entry->speedPending = 1;
            obj[0x26F] = 0;
            if (shadowA != NULL) {
                STATE_FLAG_BIT7(shadowA, 0);
            }
            if (shadowB != NULL) {
                STATE_FLAG_BIT7(shadowB, 0);
            }
            if (shadowC != NULL) {
                STATE_FLAG_BIT7(shadowC, 0);
            }
        } else {
            entry->speed = *(f32*)(obj + 0x4C);
            entry->speedPending = 1;
            if (shadowA != NULL) {
                *(f32*)(shadowA + 4) = *(f32*)(obj + 0x4C);
            }
            if (shadowB != NULL) {
                *(f32*)(shadowB + 4) = *(f32*)(obj + 0x4C);
            }
            if (shadowC != NULL) {
                *(f32*)(shadowC + 4) = *(f32*)(obj + 0x4C);
            }
            if (shadowA != NULL) {
                STATE_FLAG_BIT7(shadowA, 1);
            }
            if (shadowB != NULL) {
                STATE_FLAG_BIT7(shadowB, 1);
            }
            if (shadowC != NULL) {
                STATE_FLAG_BIT7(shadowC, 1);
            }
        }
        if (*(s16*)(obj + 0x68) != 0) {
            if (*(u8**)(obj + 0x2C) != NULL) {
                fn_80024DB0(*(u8**)(obj + 0x2C) + 0x10);
            }
            effectFile = *(u8**)(obj + 0x30);
            if (effectFile != NULL && *(u32*)(effectFile + 4) != 0 && *(u32*)(effectFile + 0x68) != 0 &&
                effectFile[0xCC] != 0) {
                fn_80024DB0(effectFile + 0x10);
                fn_80024DB0(*(u8**)(obj + 0x30) + 0x74);
            }
        }
    }

    fn_8001DB74(hugeAnimStruct.actorTable);

    for (i = 0; i < 13; i++) {
        obj = HA_OBJ(i);
        if (obj == NULL) {
            continue;
        }
        if (obj[0x25D] == 0) {
            continue;
        }
        entry = &hugeAnimStruct.actorTable->entries[(s8)obj[0x255]];
        actor = entry->actor;
        if ((actor->unk98 & 9) == 0) {
            continue;
        }
        if (actor != NULL) {
            point.x = point.y = point.z = lbl_803CC4B8;
            fn_800B2C88(actor, actor->unk84, mtx);
            PSMTXTransApply(mtx, mtx, *(f32*)(obj + 0x34), *(f32*)(obj + 0x38), *(f32*)(obj + 0x3C));
            PSMTXMultVec(mtx, &point, &point);
            transformed = point;
            setVectors(transformed);
        }
        if (*(u8**)(obj + 0x2C) != NULL) {
            fn_80024FA4((StadiumModel*)entry, *(void**)(*(u8**)(obj + 0x2C) + 0x30), *(u8**)(obj + 0x2C) + 0x10, -1);
        }
        effectFile = *(u8**)(obj + 0x30);
        if (effectFile != NULL && *(u32*)(effectFile + 4) != 0 && *(u32*)(effectFile + 0x68) != 0 &&
            effectFile[0xCC] != 0) {
            u8* modelEntry;
            s16 anim = *(s16*)(obj + 0x62);

            if (anim >= 0x3A && anim <= 0x3C && obj[0x25B] == 0) {
                modelEntry = (u8*)HA_U32(0x13C) + effectFile[0x60] * 0x90 + 0x34;
                fn_80024FA4((StadiumModel*)modelEntry, *(void**)(effectFile + 0x30), effectFile + 0x74,
                            fn_80024C6C(obj, 0));
                effectFile = *(u8**)(obj + 0x30);
                modelEntry = (u8*)HA_U32(0x13C) + effectFile[0xC4] * 0x90 + 0x34;
                fn_80024FA4((StadiumModel*)modelEntry, *(void**)(*(u8**)(obj + 0x30) + 0x94), effectFile + 0x10,
                            fn_80024C6C(obj, 1));
            } else {
                modelEntry = (u8*)HA_U32(0x13C) + effectFile[0x60] * 0x90 + 0x34;
                fn_80024FA4((StadiumModel*)modelEntry, *(void**)(effectFile + 0x30), effectFile + 0x10,
                            fn_80024C6C(obj, 1));
                effectFile = *(u8**)(obj + 0x30);
                modelEntry = (u8*)HA_U32(0x13C) + effectFile[0xC4] * 0x90 + 0x34;
                fn_80024FA4((StadiumModel*)modelEntry, *(void**)(effectFile + 0x94), effectFile + 0x74,
                            fn_80024C6C(obj, 0));
            }
        }
    }

    if (*HA(0x307A) == 2) {
        highLevelSimulationFlag[0] = 0;
        return;
    }
    highLevelSimulationFlag[0] = 0;
    if (HA_U32(0x2D90) != 0) {
        u8* base = (u8*)HA_U32(0x2D90);

        if (base[0xEE] != 0) {
            fn_80024DB0(HA(0x30A8));
            fn_80024FA4((StadiumModel*)((u8*)HA_U32(0x64) + 0x304), (void*)HA_U32(0x30C8), HA(0x30A8), -1);
        }
        if (((u8*)HA_U32(0x2D90))[0x116] != 0) {
            fn_80024DB0(HA(0x3104));
            fn_80024FA4((StadiumModel*)((u8*)HA_U32(0x64) + 0x394), (void*)HA_U32(0x3124), HA(0x3104), -1);
        }
        for (k = 0; k < 25; k++) {
            item = (u8*)HA_U32(0x2D90) + k * 0x28;
            if (k == 4) {
                item[0x26] = 0;
                *((u8*)HA_U32(0x64) + 0xA0 + k * 0x90) = item[0x26];
            }
            *((u8*)HA_U32(0x64) + 0xA0 + k * 0x90) = item[0x26] & 1;
            if (item[0x26] != 0) {
                CTRLSetTranslation((Control*)((u8*)HA_U32(0x64) + 0x44 + k * 0x90), *(f32*)(item + 4), *(f32*)(item + 8),
                                   *(f32*)(item + 0xC));
                CTRLSetRotation((Control*)((u8*)HA_U32(0x64) + 0x44 + k * 0x90), lbl_803CC510 * *(f32*)(item + 0x10),
                                lbl_803CC510 * *(f32*)(item + 0x14), lbl_803CC510 * *(f32*)(item + 0x18));
            }
        }
        fn_800BD8C4((ActorObjectTable*)HA_U32(0x64), (MtxPtr)((u8*)returnFloatFromModeIndex(0) + 0x40));
    }
    if (*(u16*)HA(0x3078) != 0) {
        for (k = 0; k < *(u16*)HA(0x3078); k++) {
            item = (u8*)HA_U32(0x2D94) + k * 0x28;
            *((u8*)HA_U32(0x68) + 0xA0 + k * 0x90) = item[0x26] & 1;
            if (item[0x26] != 0) {
                CTRLSetTranslation((Control*)((u8*)HA_U32(0x68) + 0x44 + k * 0x90), *(f32*)(item + 4), *(f32*)(item + 8),
                                   *(f32*)(item + 0xC));
                CTRLSetRotation((Control*)((u8*)HA_U32(0x68) + 0x44 + k * 0x90), lbl_803CC510 * *(f32*)(item + 0x10),
                                lbl_803CC510 * *(f32*)(item + 0x14), lbl_803CC510 * *(f32*)(item + 0x18));
            }
        }
        fn_800BD8C4((ActorObjectTable*)HA_U32(0x68), (MtxPtr)((u8*)returnFloatFromModeIndex(0) + 0x40));
    }
    if (HA_U32(0x3070) != 0) {
        ((void (*)(MtxPtr))HA_U32(0x3070))((MtxPtr)((u8*)returnFloatFromModeIndex(0) + 0x40));
        HA_U32(0x3070) = 0;
    }
}

#define REC_FIELD(rec, off) (*(u32*)((u8*)(rec) + (off)) & 0x0FFFFFFF)
#define TRACK_MAX(maxVar, rec, off)         \
    do {                                    \
        u32 v_ = REC_FIELD(rec, off);       \
        if ((maxVar) < v_) {                \
            (maxVar) = v_;                  \
        }                                   \
    } while (0)

void fn_80018DEC(int mode) {
    u32 m3 = 0;
    u32 m4 = 0;
    u32 m5 = 0;
    u32 m6 = 0;
    u32 m7 = 0;
    u32 m8 = 0;
    u8* files = lbl_803CB790;
    s32 i;
    s32 j;
    s32 n;
    u32 sizeA;
    u32 sizeB;
    u32 sizeC;
    u32 sizeD;
    u32 sizeE;
    u32 sizeG;
    u32 total;
    u32 cursor;
    u32* table;

    if (mode == 2) {
        u8* rec = files;

        for (i = 0; i < 18; i++) {
            for (j = 0; j < 3; j++) {
                TRACK_MAX(m3, rec + j * 0x130, 0xA4);
                TRACK_MAX(m4, rec + j * 0x130, 0xB4);
                TRACK_MAX(m6, rec + j * 0x130, 0x124);
                TRACK_MAX(m8, rec + j * 0x130, 0x44);
            }
            rec += 0x390;
        }
        for (i = 1; i < 9; i++) {
            u8* ch = files + *(s16*)((u8*)&inMemRoster[0][i] + 0x24) * 0x130;

            TRACK_MAX(m5, ch, 0x44);
            TRACK_MAX(m7, ch, 0x64);
        }
    } else if (mode == 0) {
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 9; j++) {
                u8* ch = files + *(s16*)((u8*)&inMemRoster[i][j] + 0x24) * 0x130;

                TRACK_MAX(m3, ch, 0x24);
                TRACK_MAX(m4, ch, 0x34);
                TRACK_MAX(m5, ch, 0x44);
                TRACK_MAX(m6, ch, 0x54);
                TRACK_MAX(m7, ch, 0x64);
            }
        }
    } else {
        u8* rec = files;

        for (i = 0; i < 27; i++) {
            for (j = 0; j < 2; j++) {
                TRACK_MAX(m3, rec + j * 0x130, 0x24);
                TRACK_MAX(m4, rec + j * 0x130, 0x34);
                TRACK_MAX(m5, rec + j * 0x130, 0x44);
                TRACK_MAX(m6, rec + j * 0x130, 0x54);
                TRACK_MAX(m7, rec + j * 0x130, 0x64);
            }
            rec += 0x260;
        }
    }

    sizeA = (m3 + 0x1F) & ~0x1F;
    sizeB = (m4 + 0x1F) & ~0x1F;
    sizeC = (m6 + 0x1F) & ~0x1F;
    sizeG = (m7 + 0x1F) & ~0x1F;
    sizeE = (m5 + 0x1F) & ~0x1F;
    sizeD = (m8 + 0x1F) & ~0x1F;
    HA_U32(0x2C90) = sizeA;
    HA_U32(0x2C94) = sizeB;
    HA_U32(0x2C9C) = sizeC;
    HA_U32(0x2CA0) = sizeG;
    HA_U32(0x2C98) = sizeE;
    if (mode == 2) {
        total = sizeB * 4 + sizeE * 8 + sizeD + sizeC + sizeG + sizeA + sizeA;
    } else {
        total = sizeB * 4 + sizeE * 9 + sizeC + sizeG + sizeA + sizeA;
    }
    HA_U32(0x2C88) = (u32)_OSAllocFromHeap(0x20, total);
    HA_U32(0x2D60) = total;

    cursor = HA_U32(0x2C88);
    HA_U32(0x2CE8) = cursor;
    cursor += sizeG;
    table = (u32*)HA(0x2CA8);
    n = 15;
    while (n > 14) {
        table[n] = cursor;
        cursor += sizeC;
        n--;
    }
    if (mode == 2) {
        while (n > 6) {
            table[n] = cursor;
            cursor += sizeE;
            n--;
        }
        n--;
        table[n + 1] = cursor;
        cursor += sizeD;
    } else {
        while (n > 5) {
            table[n] = cursor;
            cursor += sizeE;
            n--;
        }
    }
    while (n > 1) {
        table[n] = cursor;
        cursor += sizeB;
        n--;
    }
    while (n > 0) {
        table[n] = cursor;
        cursor += sizeA;
        n--;
    }
    HA_U32(0x2D48) = cursor;
    HA_U32(0x2D4C) = sizeA;
    *(s16*)HA(0x2D50) = -1;
    *HA(0x2D52) = 0;

    for (i = 0; i < 13; i++) {
        u8* rec = HA(MODEL_RECORD_BASE + i * MODEL_RECORD_SIZE);

        *(u32*)(rec + 0x10) = 0;
        *(u32*)(rec + 0x1C) = 0;
        *(u32*)(rec + 0x20) = 0;
        *(u32*)(rec + 0x14) = 0;
        *(u32*)(rec + 0x18) = 0;
        *(u32*)(rec + 0x24) = 0;
    }
    *(s16*)HA(0x2D68) = -1;
}

extern void GXSetCurrentGXThread(void);
extern void fn_8003414C(MtxPtr camera);
extern void fn_800BD670(void* table, MtxPtr camera);

#define STADIUM_HOOK() (lbl_803CB7AC[drawStadiumRelated == 0])
#define CAMERA_VIEW(mode) ((MtxPtr)((u8*)returnFloatFromModeIndex(mode) + 0x40))

#define RUN_STADIUM_HOOK(mode, arg)                      \
    if (STADIUM_HOOK() != NULL) {                        \
        STADIUM_HOOK()(CAMERA_VIEW(mode), (arg), 1);     \
    }

#define RUN_AND_CLEAR_STADIUM_HOOK(mode)                 \
    if (STADIUM_HOOK() != NULL) {                        \
        STADIUM_HOOK()(CAMERA_VIEW(mode), 1, 1);         \
        STADIUM_HOOK() = NULL;                           \
    }

#define DRAW_OVERLAY_TABLE()                                                                   \
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);                                                   \
    GXSetCullMode(GX_CULL_BACK);                                                               \
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);               \
    for (k = 0; (u16)k < ((ActorObjectTable*)HA_U32(0x68))->count; k++) {                      \
        ActorObjectEntry* overlay = &((ActorObjectTable*)HA_U32(0x68))->entries[(u16)k];       \
        if (overlay->actor != NULL && overlay->applyControl != 0) {                            \
            void (*overlayCb)(void) = *(void (**)(void))((u8*)HA_U32(0x2D94) + (u16)k * 0x28); \
            if (overlayCb != NULL) {                                                           \
                overlayCb();                                                                   \
            }                                                                                  \
            sknRelated(overlay, CAMERA_VIEW(0));                                               \
        }                                                                                      \
    }

void fn_8001E784(void) {
    s32 i;
    s32 k;
    s32 mode;
    u32 level;
    Mtx44 proj;
    GXColor color;
    Vec dir;
    StadiumLightInput* light = lbl_80367318;
    u8* state = HA(0x307A);

    GXSetCurrentGXThread();
    if (*state == 0) {
        if (*HA(0x3088) != 0 && *HA(0x307E) != 0) {
            RUN_STADIUM_HOOK(0, 0);
            if (STADIUM_HOOK() != NULL) {
                STADIUM_HOOK()(CAMERA_VIEW(0), 1, 1);
                STADIUM_HOOK() = NULL;
            }
        }
        fn_8003414C(CAMERA_VIEW(returnsCurrentMode()));
        minigamesGXStuff();
        return;
    }

    if (*HA(0x3085) != 0) {
        color = inputParams[g_d_GameSettings._54].ambient;
        adjustLightingParams(inputParams[g_d_GameSettings._54].ambient.a != 0, color);
        for (i = 0; i < 4; i++) {
            LITInitAttn((void*)HA_U32(0xAC + i * 4), lbl_803CC4F0, lbl_803CC4B8, lbl_803CC4B8, lbl_803CC4F0,
                        lbl_803CC4B8, lbl_803CC4B8);
            LITInitPos((void*)HA_U32(0xAC + i * 4), light[i].pos.x, light[i].pos.y, light[i].pos.z);
            color = light[i].color;
            LITInitColor((void*)HA_U32(0xAC + i * 4), &color);
            dir = light[i].pos;
            PSVECNormalize(&dir, &dir);
            LITInitDir((void*)HA_U32(0xAC + i * 4), dir.x, dir.y, dir.z);
            LITXForm((void*)HA_U32(0xAC + i * 4), CAMERA_VIEW(0));
        }
    }

    mode = returnScissorMode() - 1;
    do {
        setScissorAndProjection(mode);
        if (*state == 3) {
            RUN_STADIUM_HOOK(mode, 0);
            RUN_AND_CLEAR_STADIUM_HOOK(mode);
            if (*(u16*)HA(0x3078) != 0) {
                DRAW_OVERLAY_TABLE();
            }
            if (*HA(0x307E) != 0) {
                fn_8003414C(CAMERA_VIEW(returnsCurrentMode()));
                minigamesGXStuff();
            }
        } else if (*state == 5) {
            GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
            GXSetCullMode(GX_CULL_BACK);
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
            {
                s32 i2;
                for (i2 = 0; i2 < hugeAnimStruct.actorTable->count; i2++) {
                    u8* obj = HA_OBJ(i2);
                    ActorObjectEntry* entry = &hugeAnimStruct.actorTable->entries[i2];
                    Actor* actor;
                    u32* args;
                    MtxPtr camera;
                    f32 x;
                    f32 y;

                    if (obj == NULL) {
                        continue;
                    }
                    if (entry->actor == NULL) {
                        continue;
                    }
                    if (entry->applyControl == 0) {
                        continue;
                    }
                    x = *(f32*)(obj + 0x34) / lbl_803CC514;
                    y = *(f32*)(obj + 0x38) / lbl_803CC514;
                    C_MTXFrustum(proj, lbl_803CC518 + y, lbl_803CC51C + y, lbl_803CC520 + x, lbl_803CC524 + x,
                                 lbl_803CC4F0, lbl_803CC528);
                    GXSetProjection(proj, GX_PERSPECTIVE);
                    camera = CAMERA_VIEW(0);
                    actor = entry->actor;
                    args = entry->drawArgs;
                    if (entry->callback != NULL) {
                        entry->callback(entry);
                    }
                    switch (entry->drawArgCount) {
                    case 0:
                        fn_8001DD58(actor, 0, camera, 0);
                        break;
                    case 1:
                        fn_8001DD58(actor, 0, camera, 1, args[0]);
                        break;
                    case 2:
                        fn_8001DD58(actor, 0, camera, 2, args[0], args[1]);
                        break;
                    case 3:
                        fn_8001DD58(actor, 0, camera, 3, args[0], args[1], args[2]);
                        break;
                    case 4:
                        fn_8001DD58(actor, 0, camera, 4, args[0], args[1], args[2], args[3]);
                        break;
                    case 5:
                        fn_8001DD58(actor, 0, camera, 5, args[0], args[1], args[2], args[3], args[4]);
                        break;
                    case 6:
                        fn_8001DD58(actor, 0, camera, 6, args[0], args[1], args[2], args[3], args[4], args[5]);
                        break;
                    case 7:
                        fn_8001DD58(actor, 0, camera, 7, args[0], args[1], args[2], args[3], args[4], args[5], args[6]);
                        break;
                    case 8:
                        fn_8001DD58(actor, 0, camera, 8, args[0], args[1], args[2], args[3], args[4], args[5], args[6],
                                    args[7]);
                        break;
                    }
                }
            }
        } else if (*state == 2) {
            GXSetZCompLoc(0);
            fn_8001E0D8(hugeAnimStruct.actorTable, mode, CAMERA_VIEW(mode));
        } else if (*state == 4) {
            fn_8001E0D8(hugeAnimStruct.actorTable, mode, CAMERA_VIEW(mode));
            if (*(u16*)HA(0x3078) != 0) {
                DRAW_OVERLAY_TABLE();
            }
            fn_8003414C(CAMERA_VIEW(returnsCurrentMode()));
            minigamesGXStuff();
        } else {
            RUN_STADIUM_HOOK(mode, 0);
            if (*HA(0x307C) != 0) {
                fn_8001E0D8(hugeAnimStruct.actorTable, mode, CAMERA_VIEW(mode));
                fn_800BD670((void*)HA_U32(0x64), CAMERA_VIEW(mode));
                if (*(u16*)HA(0x3078) != 0) {
                    DRAW_OVERLAY_TABLE();
                }
                if (HA_U32(0x3074) != 0) {
                    ((void (*)(MtxPtr))HA_U32(0x3074))(CAMERA_VIEW(mode));
                    HA_U32(0x3074) = 0;
                }
            }
            RUN_AND_CLEAR_STADIUM_HOOK(mode);
            if (*HA(0x307E) != 0) {
                fn_8003414C(CAMERA_VIEW(returnsCurrentMode()));
                minigamesGXStuff();
            }
        }
    } while (mode-- != 0);
    GXSetScissor(0, 0, 0x280, 0x1C0);
}

#define BANK_DESC_SIZE 0x64
#define BANK_DESC_AT(rec, k) ((rec) + 0x140 + ((k) >> 1) * 0xD4 + ((k) & 1) * BANK_DESC_SIZE)

static inline void copyBankDesc(u8* dst, u8* src) {
    *(u32*)(dst + 0x0) = *(u32*)(src + 0x0);
    dst[0x60] = src[0x60];
    *(u32*)(dst + 0x4) = *(u32*)(src + 0x4);
    *(u32*)(dst + 0x8) = *(u32*)(src + 0x8);
    *(u32*)(dst + 0xC) = *(u32*)(src + 0xC);
    *(u32*)(dst + 0x30) = *(u32*)(src + 0x30);
    dst[0x5C] = src[0x5C];
    memcpy(dst + 0x10, src + 0x10, 0x20);
    memcpy(dst + 0x34, src + 0x34, 0x28);
}

static inline void linkHandPartNode(ModelObject* cur, s32 which) {
    s32 bone;

    if (cur != NULL) {
        bone = cur->partBones[handAttachBoneIDs[which]];
    } else {
        bone = 0xFFFF;
    }
    if (bone != 0xFFFF) {
        s16 n = lbl_800EEAAC[cur->charId];
        s32 j = 0;

        do {
            ModelActor* actor = (ModelActor*)cur->actors[j];

            if (n >= 0 && cur->owner != NULL) {
                ModelLinkNode* node = (ModelLinkNode*)actor->nodes[bone];
                ModelPartList* parts =
                    ((ModelEntry*)hugeAnimStruct.modelEntries)[cur->owner->blocks[which].slot].parts;

                if (parts != NULL) {
                    s32 i = parts->count;
                    ModelLinkNode** p = parts->nodes + i;

                    do {
                        ModelLinkNode* cand = *--p;

                        i--;
                        if (cand->link != NULL) {
                            node->link = cand->link;
                            break;
                        }
                    } while (i != 0);
                }
                return;
            }
        } while (j-- != 0);
    }
}

BOOL fn_80011CA8(void* objPtr, s32 kind, s32 seq) {
    u8* obj = objPtr;
    u8 bankCopy[6][BANK_DESC_SIZE];
    u8 used[6] = {0, 0, 0, 0, 0, 0};
    u8* rec = HA((s8)obj[0x254] * 0x27C);
    u8* effect;
    s32 i;
    s32 first;
    s32 second;
    s32 spare;

    copyBankDesc(bankCopy[BANK_DESC_AT(rec, 0)[0x60] % 6], BANK_DESC_AT(rec, 0));
    copyBankDesc(bankCopy[BANK_DESC_AT(rec, 1)[0x60] % 6], BANK_DESC_AT(rec, 1));
    copyBankDesc(bankCopy[BANK_DESC_AT(rec, 2)[0x60] % 6], BANK_DESC_AT(rec, 2));
    copyBankDesc(bankCopy[BANK_DESC_AT(rec, 3)[0x60] % 6], BANK_DESC_AT(rec, 3));
    copyBankDesc(bankCopy[BANK_DESC_AT(rec, 4)[0x60] % 6], BANK_DESC_AT(rec, 4));
    copyBankDesc(bankCopy[BANK_DESC_AT(rec, 5)[0x60] % 6], BANK_DESC_AT(rec, 5));

    if ((u32)(kind - 2) > 2) {
        if (obj[0x25B] != 0) {
            first = 2;
            second = 3;
        } else {
            first = 4;
            second = 5;
        }
    } else if (obj[0x25A] != 0) {
        first = 4;
        second = 1;
    } else {
        first = 0;
        second = 3;
    }

    effect = *(u8**)(obj + 0x30);
    copyBankDesc(effect, bankCopy[first]);
    copyBankDesc(effect + BANK_DESC_SIZE, bankCopy[second]);
    used[first] = 1;
    used[second] = 1;

    spare = 0;
    for (i = 0; i < 6; i++) {
        if (used[i] == 0) {
            switch (spare) {
            case 0:
                copyBankDesc(BANK_DESC_AT(rec, 2), bankCopy[i]);
                break;
            case 1:
                copyBankDesc(BANK_DESC_AT(rec, 3), bankCopy[i]);
                break;
            case 2:
                copyBankDesc(BANK_DESC_AT(rec, 4), bankCopy[i]);
                break;
            case 3:
                copyBankDesc(BANK_DESC_AT(rec, 5), bankCopy[i]);
                break;
            }
            spare++;
        }
    }

    linkHandPartNode(hugeAnimStruct.objects[(s8)obj[0x254]], 0);
    linkHandPartNode(hugeAnimStruct.objects[(s8)obj[0x254]], 1);

    actorRelated(*(u8**)(obj + 0x30) + 4, kind, seq);
    actorRelated(*(u8**)(obj + 0x30) + 0x68, kind, seq);
    return TRUE;
}

extern u8 lbl_803CBC04;
extern u32 lbl_803CBC08;

static inline BOOL finishHandItemLoad(u32 tex) {
    ModelSlotBlock* block;
    s32 i;
    void* layout;
    void* geo;
    u8* partSlot;

    if (lbl_803716B8[0x1E8] != 0) {
        return FALSE;
    }
    block = (ModelSlotBlock*)lbl_803CBC1C;
    lbl_803CBC0C = 0;
    for (i = 0; i < 4; i++) {
        if (block->loaded[i] != NULL) {
            block->loaded[i] = (void*)((u8*)block->loaded + (u32)block->loaded[i]);
        }
    }
    layout = block->loaded[lbl_803CB7C4[0]];
    geo = block->loaded[lbl_803CB7C4[1]];
    partSlot = (u8*)hugeAnimStruct.modelEntries + block->slot * 0x90 + 0x34;
    LoadActorLayout(layout);
    convertGeometryAndSknHeader(geo, NULL);
    haveActLayoutPointToGeoHeader(layout, geo);
    UpdateTexturePalettePointers(geo, (void*)tex);
    fn_800238E0(hugeAnimStruct.modelEntries, block->slot, block->slot, layout);
    if (block->loaded[2] != NULL) {
        adjustInternalPointers(block->loaded[lbl_803CB7C4[2]]);
        ACTActorRelated(block->loaded[lbl_803CB7C4[2]], partSlot);
    }
    block->_04 = block->loaded[lbl_803CB7C4[3]];
    actRelated(block->loaded[lbl_803CB7C4[2]], &block->_04);
    lbl_803CBC1C = NULL;
    return TRUE;
}

BOOL fn_80012B90(void* objPtr) {
    u8* obj = objPtr;
    s32 charId = (s8)obj[0x252];
    s32 slot = (s8)obj[0x254];
    u8 phase = lbl_803CBC04;
    ModelOwner* owner;
    u32 tex;
    s32 ready;
    s32 isFlagClear;
    s32 kind;
    ModelSlotBlock* target;
    s32 groupIndex;

    if (phase < 3) {
        owner = (ModelOwner*)(HA(slot * 0x27C) + 0x140);
    } else if (phase < 6) {
        owner = (ModelOwner*)(HA((slot * 3 + 1) * 0xD4) + 0x140);
    } else if (phase < 9) {
        owner = (ModelOwner*)(HA((slot * 3 + 2) * 0xD4) + 0x140);
    }

    switch (phase) {
    case 0:
    case 3:
    case 6:
        owner->texPalette = **(void***)(obj + 8);
        lbl_803CBC08 = (u32)**(void***)(obj + 8);
        owner->charId = charId;
        if (lbl_803CBC04 == 0) {
            ((u8*)owner)[0xD1] = ((u8*)owner)[0xD0];
            ((u8*)owner)[0xD0] = obj[0x254];
        } else {
            ((u8*)owner)[0xD1] = 9;
            ((u8*)owner)[0xD0] = 9;
        }
        ((u8*)owner)[0xCD] = obj[0x25A];
        ((u8*)owner)[0xCE] = obj[0x25B];
        owner->_CC[0] = 1;
        groupIndex = lbl_803CBC04 / 3 + slot * 3;
        lbl_803CBC04 = lbl_803CBC04 + 1;
        owner->blocks[0].slot = groupIndex * 2;
        owner->blocks[1].slot = groupIndex * 2 + 1;
        break;
    case 1:
    case 2:
        tex = lbl_803CBC08;
        isFlagClear = (owner->flag == 0);
        if (lbl_803CBC0C == 0 && ((u8*)&lbl_803C6CF8)[0x715] == 1) {
            if (isFlagClear == owner->flag) {
                kind = 1 - isFlagClear;
            } else {
                kind = 3 - isFlagClear;
            }
            if (isFlagClear != 0) {
                target = &owner->blocks[0];
            } else {
                target = &owner->blocks[1];
            }
            lbl_803CBC1C = (u8*)target;
            lbl_803CBC0C = 1;
            loadCharacterHandItem(owner->charId, kind, target->loaded);
        }
        ready = finishHandItemLoad(tex);
        if (ready) {
            owner->flag = (owner->flag == 0);
            lbl_803CBC04 = lbl_803CBC04 + 1;
        }
        break;
    case 4:
        tex = lbl_803CBC08;
        if (lbl_803CBC0C == 0 && ((u8*)&lbl_803C6CF8)[0x715] == 1) {
            lbl_803CBC1C = (u8*)&owner->blocks[1];
            lbl_803CBC0C = 1;
            loadCharacterHandItem(owner->charId, 1, owner->blocks[1].loaded);
        }
        if (finishHandItemLoad(tex)) {
            lbl_803CBC04 = 5;
        }
        break;
    case 5:
        tex = lbl_803CBC08;
        if (lbl_803CBC0C == 0 && ((u8*)&lbl_803C6CF8)[0x715] == 1) {
            lbl_803CBC1C = (u8*)&owner->blocks[0];
            lbl_803CBC0C = 1;
            loadCharacterHandItem(owner->charId, 0, owner->blocks[0].loaded);
        }
        if (finishHandItemLoad(tex)) {
            lbl_803CBC04 = 6;
        }
        break;
    case 7:
        tex = lbl_803CBC08;
        if (lbl_803CBC0C == 0 && ((u8*)&lbl_803C6CF8)[0x715] == 1) {
            lbl_803CBC1C = (u8*)&owner->blocks[1];
            lbl_803CBC0C = 1;
            loadCharacterHandItem(owner->charId, 5, owner->blocks[1].loaded);
        }
        if (finishHandItemLoad(tex)) {
            lbl_803CBC04 = 8;
        }
        break;
    case 8:
        tex = lbl_803CBC08;
        if (lbl_803CBC0C == 0 && ((u8*)&lbl_803C6CF8)[0x715] == 1) {
            lbl_803CBC1C = (u8*)&owner->blocks[0];
            lbl_803CBC0C = 1;
            loadCharacterHandItem(owner->charId, 4, owner->blocks[0].loaded);
        }
        if (finishHandItemLoad(tex)) {
            *(u8**)((u8*)&hugeAnimStruct + 0x30) = HA(slot * 0x27C) + 0x140;
            lbl_803CBC04 = 0;
            lbl_803CBC08 = 0;
            return TRUE;
        }
        break;
    default:
        break;
    }
    return FALSE;
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

extern void fn_80017814(u8* record, s32 slot, s32 mode, void (*callback)(u8*));
extern void fn_8001FDD4(u8* obj);

BOOL fn_8001758C(void* a, u8 b, u8 c, u8 d, u8 e, u8 f, u8 g, u8 h) {
    u8* state = a;
    u8* rec = HA(MODEL_RECORD_BASE + b * MODEL_RECORD_SIZE);
    s32 fileIndex;

    switch (*state) {
    case 0:
        if (((u8*)&lbl_803C6CF8)[0x715] != 1) {
            return FALSE;
        }
        rec[0x25C] = 1;
        rec[0x256] = d;
        rec[0x257] = e;
        rec[0x254] = g;
        rec[0x252] = c;
        rec[0x258] = f;
        rec[0x259] = h;
        rec[0x25A] = ((u8*)&inMemRoster[d][e])[0x26];
        rec[0x25B] = ((u8*)&inMemRoster[d][e])[0x27];
        rec[0x278] = (g == 9);
        fileIndex = (s8)rec[0x252] * 0x13;
        if (h == 0) {
            fileIndex += 1;
        }
        if (rec[0x278] != 0 && h == 1 && *(s16*)HA(0x2D5C) == c) {
            memcpy(*(void**)(rec + 8), *(void**)HA(0x2D54), *(u32*)HA(0x2D58));
            break;
        }
        if (g >= 10 && g <= 12 && h == 0 && *(s16*)HA(0x2D44) == c) {
            memcpy(*(void**)(rec + 8), *(void**)HA(0x2D3C), *(u32*)HA(0x2D40));
            break;
        }
        if (h == 0 || fn_8002204C((s8)rec[0x252], *(s32*)(rec + 8)) == NULL) {
            ARAMTransfer((u8*)lbl_803CB790 + fileIndex * 16, *(s32*)(rec + 8), 0, 0);
        }
        *state = 1;
        return FALSE;
    case 1:
        if (lbl_803716B8[0x1E8] != 0 || ((u8*)&lbl_803C6CF8)[0x715] != 1) {
            return FALSE;
        }
        break;
    default:
        return FALSE;
    }
    fn_80017814(rec, (s8)rec[0x255], g, fn_8001FDD4);
    return TRUE;
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
    /* fn_80017814 takes four arguments; the original passes only what is already in r4-r6, so the call is cast to one argument. */
    ((void (*)(void*))fn_80017814)(p);
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
