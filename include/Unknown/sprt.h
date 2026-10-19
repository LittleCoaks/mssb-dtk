#ifndef __UNKNOWN_SPRT_H_
#define __UNKNOWN_SPRT_H_

#include "mssbTypes.h"
#include "Dolphin/GX/GXEnum.h"

s32 AllocateSprite(s32 slot, s32 size);

void DrawNullSprite(void* vtx, s32 count);

void renderSprite(void* vtx, void* tex, u16 sMax, u16 tMax);

void DrawSprite_TexObj(void* vtx, void* texObj, s32 arg2);

void DrawSprite(u32 flags, void* vtx, s32 count, void* texObj, u16 arg4, u16 arg5);

void setTextRenderingMode(s32 mode);
BOOL fn_800B216C(GXBool compareEnable, GXCompare func, GXBool updateEnable);
void fn_800B21A8(int mode);

#endif // !__UNKNOWN_SPRT_H_
