#ifndef __UNKNOWN_PARTICLE_EFFECTS_H_
#define __UNKNOWN_PARTICLE_EFFECTS_H_

#include "mssbTypes.h"

BOOL maybeTexOrSpriteRelated(u8* group);

void fn_80033794(void* particles);
void* fn_800337CC(void* buf, int count, int arg2);
void pitchingMachinePitching(u8 arg0);
BOOL fn_80033928(u8 id);
void fn_80033964(void* effect);
void* fn_800339F0(int arg0, u8 arg1);
void* allocParticleEffect(void* func, int arg1, int arg2, int arg3, int arg4, u8 arg5);

void setParticleXform(f32 scaleX, f32 scaleY, f32 rot);

void minigamesSetSomePointers(void);
void minigamesGXStuff(void);
void minigamesSetSomePointers2(void);

#endif // !__UNKNOWN_PARTICLE_EFFECTS_H_
