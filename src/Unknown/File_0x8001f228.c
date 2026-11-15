#include "Unknown/File_0x8001f228.h"
#include "HugeAnimStruct.h"

#define STADIUM_POOL_OBJECT_SIZE 0x27C
#define STADIUM_POOL_COUNT 13


void DrawShadows(u8 enable);

void resetGameStadiumStateOnExit(void) {
    s32 i;
    s32 j;
    s32 m;

    hugeAnimStruct._307A = 0;
    hugeAnimStruct.stadiumFileHeader = 0;
    hugeAnimStruct.stadiumObjectLoading = 0;
    for (i = 0; i < 0x15; i++) {
        hugeAnimStruct._000C[i] = 0;
    }

    for (i = 0; i < 5; i++) {
        hugeAnimStruct.actorTables[i] = 0;
    }
    for (i = 0; i < STADIUM_POOL_COUNT; i++) {
        hugeAnimStruct.pool[i][0x25C] = 0;
        hugeAnimStruct.objects[i] = NULL;
    }

    for (i = 0; i < 3; i++) {
        hugeAnimStruct.words2C84[i] = 0;
    }

    for (i = 0; i < 4; i++) {
        m = i * 4;
        hugeAnimStruct.words2C84[10 + i * 4 + 0] = 0;
        hugeAnimStruct.words2C84[26 + m] = 0;
        hugeAnimStruct.words2C84[31 + m] = 0;
        hugeAnimStruct.words2C84[36 + m] = 0;
        hugeAnimStruct.words2C84[41 + m] = 0;
        hugeAnimStruct.words2C84[10 + i * 4 + 1] = 0;
        hugeAnimStruct.words2C84[27 + m] = 0;
        hugeAnimStruct.words2C84[32 + m] = 0;
        hugeAnimStruct.words2C84[37 + m] = 0;
        hugeAnimStruct.words2C84[42 + m] = 0;
        hugeAnimStruct.words2C84[10 + i * 4 + 2] = 0;
        hugeAnimStruct.words2C84[28 + m] = 0;
        hugeAnimStruct.words2C84[33 + m] = 0;
        hugeAnimStruct.words2C84[38 + m] = 0;
        hugeAnimStruct.words2C84[43 + m] = 0;
        hugeAnimStruct.words2C84[10 + i * 4 + 3] = 0;
        hugeAnimStruct.words2C84[29 + m] = 0;
        hugeAnimStruct.words2C84[34 + m] = 0;
        hugeAnimStruct.words2C84[39 + m] = 0;
        hugeAnimStruct.words2C84[44 + m] = 0;
    }

    for (i = 0; i < STADIUM_POOL_COUNT; i++) {
        hugeAnimStruct.flags[i] = -1;
    }

    for (i = 0; i < 4; i++) {
        ((s32*)&hugeAnimStruct.starAnimRelated)[i] = 0;
    }

    hugeAnimStruct._307C = 0;
    hugeAnimStruct._3085 = 0;
    hugeAnimStruct._308C = 0;
    hugeAnimStruct._3087 = 0;
    hugeAnimStruct._3086 = 0;
    DrawShadows(0);
}
