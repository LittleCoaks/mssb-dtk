#include "Unknown/File_0x8001f228.h"

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

extern StadiumResetView hugeAnimStruct;

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
