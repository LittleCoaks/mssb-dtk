#include "Unknown/File_0x80018024.h"
#include "Unknown/File_0x800acf14.h"
#include "static/UnknownHomes_Static.h"
#include "HugeAnimStruct.h"

typedef struct CompressedFileEntry {
    /*0x00*/ u8 _00[0x04];
    /*0x04*/ u32 _04;
    /*0x08*/ u8 _08[0x08];
} CompressedFileEntry;

extern CompressedFileEntry* lbl_803CB790;

/* A pointer field inside animation object `k` of the pool. */
#define POOL_PTR(k, off) (*(u8**)(hugeAnimStruct.pool[k] + (off)))

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
        v = ((CompressedFileEntry*)p)[0]._04 & 0x0FFFFFFF;
        if (maxA < v) {
            maxA = v;
        }
        v = ((CompressedFileEntry*)p)[1]._04 & 0x0FFFFFFF;
        if (maxB < v) {
            maxB = v;
        }
        v = ((CompressedFileEntry*)p)[19]._04 & 0x0FFFFFFF;
        if (maxA < v) {
            maxA = v;
        }
        v = ((CompressedFileEntry*)p)[20]._04 & 0x0FFFFFFF;
        if (maxB < v) {
            maxB = v;
        }
        v = ((CompressedFileEntry*)p)[38]._04 & 0x0FFFFFFF;
        if (maxA < v) {
            maxA = v;
        }
        v = ((CompressedFileEntry*)p)[39]._04 & 0x0FFFFFFF;
        if (maxB < v) {
            maxB = v;
        }
        p += 57 * 16;
    }

    sizeA = (maxA + 0x1F) & ~0x1F;
    sizeB = (maxB + 0x1F) & ~0x1F;
    hugeAnimStruct._2D64 = sizeA;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        hugeAnimStruct.modelData = _OSAllocFromHeap(0x20, (sizeA + sizeB) * 4);
    } else {
        hugeAnimStruct.modelData = _OSAllocFromHeap(0x20, sizeA * 4);
    }

    p = hugeAnimStruct.modelData;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        POOL_PTR(0, 0x08) = p;
        p += sizeA;
        POOL_PTR(0, 0x2C) = 0;
        POOL_PTR(0, 0x30) = 0;
        POOL_PTR(0, 0x0C) = p;
        p += sizeB;
        POOL_PTR(4, 0x2C) = 0;
        POOL_PTR(4, 0x30) = 0;
        POOL_PTR(1, 0x08) = p;
        p += sizeA;
        POOL_PTR(1, 0x2C) = 0;
        POOL_PTR(1, 0x30) = 0;
        POOL_PTR(1, 0x0C) = p;
        p += sizeB;
        POOL_PTR(5, 0x2C) = 0;
        POOL_PTR(5, 0x30) = 0;
        POOL_PTR(2, 0x08) = p;
        p += sizeA;
        POOL_PTR(2, 0x2C) = 0;
        POOL_PTR(2, 0x30) = 0;
        POOL_PTR(2, 0x0C) = p;
        p += sizeB;
        POOL_PTR(6, 0x2C) = 0;
        POOL_PTR(6, 0x30) = 0;
        POOL_PTR(3, 0x08) = p;
        p += sizeA;
        POOL_PTR(3, 0x2C) = 0;
        POOL_PTR(3, 0x30) = 0;
        POOL_PTR(3, 0x0C) = p;
        POOL_PTR(7, 0x2C) = 0;
        POOL_PTR(7, 0x30) = 0;
    } else {
        POOL_PTR(0, 0x08) = p;
        p += sizeA;
        POOL_PTR(0, 0x2C) = 0;
        POOL_PTR(0, 0x30) = 0;
        POOL_PTR(1, 0x08) = p;
        p += sizeA;
        POOL_PTR(1, 0x2C) = 0;
        POOL_PTR(1, 0x30) = 0;
        POOL_PTR(2, 0x08) = p;
        p += sizeA;
        POOL_PTR(2, 0x2C) = 0;
        POOL_PTR(2, 0x30) = 0;
        POOL_PTR(3, 0x08) = p;
        POOL_PTR(3, 0x2C) = 0;
        POOL_PTR(3, 0x30) = 0;
    }
}
