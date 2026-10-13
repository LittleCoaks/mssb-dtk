#ifndef _C3_CONTROL_FRUSTUM_H_
#define _C3_CONTROL_FRUSTUM_H_

#include "types.h"
#include "Dolphin/mtx.h"

// View frustum state, one entry per slot (four slots, .bss 0x803CB1FC).
typedef struct Frustum {
    Vec corners[8];   // 0x00: frustum corner points
    Mtx44 proj;       // 0x60: projection matrix
    f32 nearZ;        // 0xA0
    f32 farZ;         // 0xA4
} Frustum;            // size 0xA8

void fn_800B806C(s32 slot, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
s32 checkObjectVisibility(s32 slot, Vec* box, MtxPtr mtx);
s32 checkPlaneIntersection(Vec* face, Vec* pts);

#endif // _C3_CONTROL_FRUSTUM_H_
