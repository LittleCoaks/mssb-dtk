#include "Unknown/File_0x8001d180.h"
#include "C3/actor.h"
#include "C3/skinning.h"

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

extern struct {
    /* 0x0000 */ u8 _0000[0x13C];
    /* 0x013C */ HandModelEntry* modelEntries;
    /* 0x0140 */ u8 _0140[0x2C50 - 0x140];
    /* 0x2C50 */ HandObject* objects[(0x3154 - 0x2C50) / 4];
} hugeAnimStruct;

extern u8 handAttachBoneIDs[8];
extern s16 lbl_800EEAAC[NUM_CHOOSABLE_CHARACTERS];

static inline s32 getHandBone(s32 playerIdx, s32 slot) {
    HandObject* obj = hugeAnimStruct.objects[playerIdx];
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
    HandObject* obj = hugeAnimStruct.objects[playerIdx];
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
