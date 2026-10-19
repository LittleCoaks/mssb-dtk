#ifndef __UNKNOWN_FILE_0X80009E94_H_
#define __UNKNOWN_FILE_0X80009E94_H_

#include "mssbTypes.h"

typedef struct InterpPoint {
    /*0x00*/ f32 x;
    /*0x04*/ f32 y;
    /*0x08*/ u8 _08[0x8];
} InterpPoint;

typedef struct Vec2f {
    /*0x00*/ f32 x;
    /*0x04*/ f32 y;
} Vec2f;

void interpolatePointsUnknown(s32 index, InterpPoint* points, BOOL hasPrev, BOOL hasNext);
void BezierInterpolate(Vec2f* out, const Vec2f* p0, const Vec2f* p1, const Vec2f* p2, const Vec2f* p3, f32 t);
u32 fn_8000A094(u32 value);

#endif // !__UNKNOWN_FILE_0X80009E94_H_
