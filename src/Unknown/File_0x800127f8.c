#include "Unknown/File_0x800127f8.h"
#include "Dolphin/os.h"
#include "C3/actor/act.h"
#include "C3/geoPalette/geoPalette.h"
#include "Unknown/File_0x80021ca4.h"
#include "Unknown/File_0x80025c58.h"
#include "Unknown/File_0x80025ddc.h"
#include "Unknown/File_0x800a7568.h"

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

extern struct {
    /* 0x0000 */ u8 _0000[0x13C];
    /* 0x013C */ ModelEntry* entries;
    /* 0x0140 */ u8 _0140[0x2C50 - 0x140];
    /* 0x2C50 */ ModelObject* objects[(0x3154 - 0x2C50) / 4];
} hugeAnimStruct;

extern struct {
    /* 0x000 */ u8 _000[0x1E8];
    /* 0x1E8 */ u8 unk1E8;
    /* 0x1E9 */ u8 _1E9[0x578 - 0x1E9];
} lbl_803716B8;

extern u8 lbl_803CB7C4[];
extern u16 lbl_800EEAAC[];
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
