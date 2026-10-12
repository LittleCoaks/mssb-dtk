#ifndef _C3_CONTROL_FRUSTUM_H_
#define _C3_CONTROL_FRUSTUM_H_

#include "types.h"
#include "Dolphin/mtx.h"

// View frustums, one 0xA8-byte entry per slot (.bss 0x803CB1FC, four slots).
void fn_800B806C(s32 slot, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
s32 checkObjectVisibility(s32 slot, void* box, MtxPtr mtx);
void checkPlaneIntersection(void);

#endif // _C3_CONTROL_FRUSTUM_H_
