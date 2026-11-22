#ifndef __UNKNOWN_FILE_0X8000A0AC_H_
#define __UNKNOWN_FILE_0X8000A0AC_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "Unknown/File_0x80009e94.h"

void fn_8000A0AC(void *out, f32 t, u8 *a, u8 *b);
u32 fn_8000A3EC(Mtx dest, Mtx outBuf, u8 *c, u8 *d, void *ctx, f32 t, f32 s);
void interpolatePointsBezier_Vec2s(void *dst, const s16 *p0, const s16 *p1, const s16 *p2, const s16 *p3, s32 mode, f32 t);

#endif // !__UNKNOWN_FILE_0X8000A0AC_H_
