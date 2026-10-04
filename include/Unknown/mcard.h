#ifndef __UNKNOWN_MCARD_H_
#define __UNKNOWN_MCARD_H_

#include "mssbTypes.h"

typedef struct McardRequest {
    /* 0x00 */ const char* fileName;
    /* 0x04 */ void* buffer;
    /* 0x08 */ s32 size;
    /* 0x0C */ u8 chan;
    /* 0x0D */ u8 async;
    /* 0x0E */ u8 attr;
    /* 0x0F */ u8 _0F;
    /* 0x10 */ u32 (*callback)(void* buffer, s32 size, u32 arg);
    /* 0x14 */ u32 callbackArg;
    /* 0x18 */ u32 flags;
} McardRequest;

void memoryCardRelatedFunction(McardRequest* req, int arg1, u64 serialNo);
void processBannerImage(const char* fileName, void* banner, s32 bannerSize, void* icon, s32 iconSize,
                        u32 iconSpeed, u32 animType, const char* title, const char* comment, s32 blocks);

#endif // !__UNKNOWN_MCARD_H_
