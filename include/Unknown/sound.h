#ifndef __UNKNOWN_SOUND_H_
#define __UNKNOWN_SOUND_H_

#include "mssbTypes.h"

typedef struct SndHeap {
    /*0x0*/ s32 remaining;
    /*0x4*/ u32 cur;
    /*0x8*/ u32 end;
} SndHeap;

extern SndHeap* lbl_803CBB10;

void soundQuit(void);
typedef struct SndConfig {
    /* 0x0 */ u8 voices;
    /* 0x1 */ u8 music;
    /* 0x2 */ u8 sfx;
    /* 0x3 */ u8 studios;
    /* 0x4 */ u32 flags;
    /* 0x8 */ u32 aramSize;
} SndConfig;

void initSound(SndConfig* config, u8* aiStack, void* aramBuffer, u32 aramSize);
void fn_800B0934(void* addr);
void SndFree(void* addr);
void* SndAlloc(u32 len);

#endif // !__UNKNOWN_SOUND_H_
