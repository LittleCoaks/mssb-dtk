#include "Unknown/File_0x8001f4c0.h"
#include "Dolphin/mtx.h"

#define ANIM_OBJECT_COUNT 13
#define BALL_MODEL_COUNT 25

/* One animation-driven object in hugeAnimStruct's object pool. */
typedef struct AnimObject {
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
} AnimObject; // size 0x27C

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
extern struct {
    /* 0x0000 */ u8 _0000[0xC04];
    /* 0x0C04 */ AnimObject pool[ANIM_OBJECT_COUNT];
    /* 0x2C50 */ AnimObject* objects[ANIM_OBJECT_COUNT];
    /* 0x2C84 */ u8 _2C84[0x2D90 - 0x2C84];
    /* 0x2D90 */ BallModel* ballModels;
    /* 0x2D94 */ u8 _2D94[0x3078 - 0x2D94];
    /* 0x3078 */ u16 _3078;
} hugeAnimStruct;

void challengeMapMaybe(void) {
    int i;

    for (i = 0; i < ANIM_OBJECT_COUNT; i++) {
        AnimObject* obj = &hugeAnimStruct.pool[i];

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
