#ifndef __UNKNOWN_FILE_0X80064344_H_
#define __UNKNOWN_FILE_0X80064344_H_

#include "mssbTypes.h"
#include "Dolphin/vec.h"

/* 0x70-byte effect description copied from a .data template and passed to
 * fn_8002B7F8. Only the fields scaled at run time are named. */
typedef struct {
    /* 0x00 */ void* texture;
    /* 0x04 */ s32 unk04[4];
    /* 0x14 */ f32 unk14[6];
    /* 0x2C */ s32 unk2C[3];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 _3C[0x54 - 0x3C];
    /* 0x54 */ f32 unk54[3];
    /* 0x60 */ u8 _60[0x70 - 0x60];
} EffectSpawnParams; // size: 0x70

void fn_8002B7F8(Vec* pos, EffectSpawnParams* params, int count);

void handleBallRollInWater(Vec* pos, Vec* vel);

#endif // !__UNKNOWN_FILE_0X80064344_H_
