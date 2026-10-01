#ifndef __UNKNOWN_FILE_0X800AAEE4_H_
#define __UNKNOWN_FILE_0X800AAEE4_H_

#include "mssbTypes.h"

typedef struct McardSaveRequest {
    /* 0x00 */ u8 _00[4];
    /* 0x04 */ u32 unk04;
    /* 0x08 */ s32 saveSize;
    /* 0x0C */ u8 unk0C;
    /* 0x0D */ u8 unk0D;
    /* 0x0E */ u8 unk0E;
    /* 0x0F */ u8 _0F;
    /* 0x10 */ u32 unk10;
    /* 0x14 */ u32 unk14;
    /* 0x18 */ u32 unk18;
} McardSaveRequest;

void memoryCardRelatedFunction(McardSaveRequest* req, int arg1, u64 slotData);

#endif // !__UNKNOWN_FILE_0X800AAEE4_H_
