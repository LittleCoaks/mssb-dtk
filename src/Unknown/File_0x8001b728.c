#include "Unknown/File_0x8001b728.h"

typedef struct CollisionObject {
    /*0x000*/ u8 _000[0x34];
    /*0x034*/ Vec offset;
    /*0x040*/ u8 _040[0x162 - 0x40];
    /*0x162*/ u16 bones[1];
    /*0x164*/ u8 _164[0x255 - 0x164];
    /*0x255*/ s8 slot;
} CollisionObject;

extern u8 hugeAnimStruct[0x3154];
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
