#include "Unknown/File_0x800acf14.h"

#define HEADER(block) ((MemoryStackHeader*)(block) - 1)
#define ROUND_UP4(n) (((n) + 3) & ~3)

void unkLoadingCleanupRelated(void* block) {
    memoryUsedOrStorage.hi = HEADER(block)->prevEnd;
    memoryUsedOrStorage.freeSize = memoryUsedOrStorage.hi - memoryUsedOrStorage.lo;
}

void* allocateAlignedMemoryBlock(int alignment, int size) {
    u8* hi = memoryUsedOrStorage.hi;
    u8* block = (u8*)((u32)(hi - ROUND_UP4(size)) & -alignment);
    u8* newHi = block - sizeof(MemoryStackHeader);
    s32 freeSize = newHi - memoryUsedOrStorage.lo;
    MemoryStackHeader* header = HEADER(block);

    header->prevEnd = hi;
    header->size = hi - newHi;
    memoryUsedOrStorage.freeSize = freeSize;
    memoryUsedOrStorage.hi = newHi;
    return block;
}

void fn_800ACF78(void* block, int size) {
    u8* prev = HEADER(block)->prevEnd;
    s32 offset = (u8*)block - prev;
    s32 total;

    size = ROUND_UP4(size);
    total = size + offset;
    memoryUsedOrStorage.lo = prev + total;
    memoryUsedOrStorage.freeSize = memoryUsedOrStorage.hi - memoryUsedOrStorage.lo;
    HEADER(block)->size = total;
}

void fn_800ACFB0(void* block) {
    memoryUsedOrStorage.lo = HEADER(block)->prevEnd;
    memoryUsedOrStorage.freeSize = memoryUsedOrStorage.hi - memoryUsedOrStorage.lo;
}

void* _OSAllocFromHeap(s32 alignment, s32 size) {
    u8* lo = memoryUsedOrStorage.lo;
    u8* hi = memoryUsedOrStorage.hi;
    u32 addr = (u32)lo + alignment + (sizeof(MemoryStackHeader) - 1);
    u8* block;
    u8* newLo;
    MemoryStackHeader* header;

    size = ROUND_UP4(size);
    block = (u8*)(addr & -alignment);
    newLo = block + size;
    header = HEADER(block);
    header->prevEnd = lo;
    header->size = (block - lo) + size;
    memoryUsedOrStorage.freeSize = hi - newLo;
    memoryUsedOrStorage.lo = newLo;
    return block;
}

void fn_800AD01C(void* hi) {
    memoryUsedOrStorage.hi = hi;
    memoryUsedOrStorage.freeSize = memoryUsedOrStorage.hi - memoryUsedOrStorage.lo;
}

void fn_800AD038(void* lo) {
    memoryUsedOrStorage.lo = lo;
    memoryUsedOrStorage.freeSize = memoryUsedOrStorage.hi - memoryUsedOrStorage.lo;
}

void fn_800AD054(int lo, int hi) {
    memoryUsedOrStorage.lo = (u8*)lo;
    memoryUsedOrStorage.hi = (u8*)hi;
    memoryUsedOrStorage.freeSize = hi - lo;
}
