#ifndef __UNKNOWN_FILE_0X800ACF14_H_
#define __UNKNOWN_FILE_0X800ACF14_H_

#include "mssbTypes.h"

// Two-ended bump allocator: blocks are carved upward from `lo` and downward
// from `hi`. Each block is preceded by an 8-byte header holding the previous
// end pointer and the block's total size (header included).
typedef struct MemoryStack {
    /* 0x0 */ s32 freeSize;
    /* 0x4 */ u8* lo;
    /* 0x8 */ u8* hi;
} MemoryStack;

typedef struct MemoryStackHeader {
    /* 0x0 */ u8* prevEnd;
    /* 0x4 */ s32 size;
} MemoryStackHeader;

extern MemoryStack memoryUsedOrStorage;

void unkLoadingCleanupRelated(void* block);
void* allocateAlignedMemoryBlock(int alignment, int size);
void fn_800ACF78(void* block, int size);
void fn_800ACFB0(void* block);
void* _OSAllocFromHeap(s32 alignment, s32 size);
void fn_800AD01C(void* hi);
void fn_800AD038(void* lo);
void fn_800AD054(int lo, int hi);

#endif // !__UNKNOWN_FILE_0X800ACF14_H_
