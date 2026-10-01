#include "Unknown/File_0x8001b80c.h"
#include "Unknown/File_0x800b2c44.h"
#include "Unknown/File_0x800bdd74.h"

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
extern struct {
    /* 0x0000 */ u8 _0000[0x60];
    /* 0x0060 */ ActorObjectTable* actorTable;
    /* 0x0064 */ u8 _0064[0x2C50 - 0x64];
    /* 0x2C50 */ AnimObject* objects[(0x3154 - 0x2C50) / 4];
} hugeAnimStruct;

static inline int getPartBone(AnimObject* obj, int part) {
    if (obj != NULL) {
        return obj->partBones[part];
    }
    return NO_BONE;
}

BOOL getAnimRelatedCoordinates(int objIndex, int part, Vec* out) {
    AnimObject* obj = hugeAnimStruct.objects[objIndex];
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
