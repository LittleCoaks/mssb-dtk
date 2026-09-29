#ifndef __UNKNOWN_FILE_0X800B99C4_H_
#define __UNKNOWN_FILE_0X800B99C4_H_

#include "mssbTypes.h"
#include "Dolphin/GX/GXPixel.h"

typedef struct FogSettings {
    /* 0x00 */ GXFogType type;
    /* 0x04 */ f32 startZ;
    /* 0x08 */ f32 endZ;
    /* 0x0C */ f32 nearZ;
    /* 0x10 */ f32 farZ;
    /* 0x14 */ GXColor color;
} FogSettings; // size: 0x18

extern FogSettings fogSettings;

void SetFog(GXFogType type, f32 startZ, f32 endZ, f32 nearZ, f32 farZ, GXColor color);

#endif // !__UNKNOWN_FILE_0X800B99C4_H_
