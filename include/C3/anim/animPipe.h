#ifndef _C3_ANIM_ANIMPIPE_H_
#define _C3_ANIM_ANIMPIPE_H_

#include "mssbTypes.h"
#include "C3/anim.h"

void Squad(const f32* q0, f32 t, const f32* s0, const f32* s1, const f32* q1, f32* out);

void GetData(u8 type, void* src, f32* dst, f32 scale, u8 count);

struct ANIMPipe;
struct ANIMAnimTrack;
struct Control;

void ANIMBind(struct ANIMPipe* animPipe, struct Control* control, struct ANIMAnimTrack* animTrack, f32 time);

#endif // _C3_ANIM_ANIMPIPE_H_
