#ifndef _C3_LIGHT_LIGHT_H_
#define _C3_LIGHT_LIGHT_H_

#include "mssbTypes.h"
#include "Dolphin/GX/GXTypes.h"
#include "Dolphin/gx.h"

u8 lightingRelated(GXColor* color);
void adjustLightingParams(u8 enable, GXColor color);
void fn_800BD2DC(void);

void LITXForm(void* arg0, void* arg1);

void LITInitColor(void* light, GXColor* color);
void LITInitDir(void* light, f32 x, f32 y, f32 z);
void LITInitPos(void* light, f32 x, f32 y, f32 z);

void LITInitAttn(void* light, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2);

void LITAlloc(void** light);

#endif // _C3_LIGHT_LIGHT_H_
