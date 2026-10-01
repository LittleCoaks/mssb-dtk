#include "Unknown/File_0x8001b918.h"

#define ANIM_OBJECT_COUNT 13

/* One animation-driven object in hugeAnimStruct's object pool. */
typedef struct AnimObject {
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
} AnimObject; // size 0x27C

/* This unit's view of hugeAnimStruct (0x3154 bytes). */
extern struct {
    /* 0x0000 */ u8 _0000[0x2C50];
    /* 0x2C50 */ AnimObject* objects[ANIM_OBJECT_COUNT];
} hugeAnimStruct;

void QueueCharacterAnimation(int objIndex, int animId, int a2, int a3, int a4, int a5, int a6) {
    AnimObject* obj = hugeAnimStruct.objects[objIndex];

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
        hugeAnimStruct.objects[objIndex]->_26E = 1;
    }
}

void AnimateCharacter(int objIndex, int animId, int a2, int a3, int a4, int a5, int a6, int a7) {
    AnimObject* obj = hugeAnimStruct.objects[objIndex];

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
        hugeAnimStruct.objects[objIndex]->_26D = 1;
    }
}
