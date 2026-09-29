#ifndef __UNKNOWN_FILE_0X800B0938_H_
#define __UNKNOWN_FILE_0X800B0938_H_

#include "mssbTypes.h"

typedef struct SndHeap {
    /*0x0*/ s32 remaining;
    /*0x4*/ u32 cur;
    /*0x8*/ u32 end;
} SndHeap;

extern SndHeap* lbl_803CBB10;

void SndFree(void* addr);
void* SndAlloc(u32 len);

#endif // !__UNKNOWN_FILE_0X800B0938_H_
