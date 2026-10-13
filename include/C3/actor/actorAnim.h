#ifndef _C3_ACTOR_ACTORANIM_H_
#define _C3_ACTOR_ACTORANIM_H_

#include "mssbTypes.h"
#include "C3/actor.h"

f32 fn_800B4A44(void* actor, u16 bone);
f32 scanBoneAttachmentData(void *ptr);
void updateBoneParam(void* actor, int flag);
void AnimateActorBones(void* actor);
void setAllBoneEventFlags(void* actor, BOOL flag);
f32 fn_800B4C40(void* actor);
void setActorAnimFrame(void* actor, f32 frame);
void fn_800B4CDC(void* actor);

// ACTSetAnimation is declared in C3/actor.h (6-parameter form, proven by the
// target: r3=actor, r4/r5/r6 forwarded to ANIMGetSequence, f1=startFrame,
// f2=time).

#endif // _C3_ACTOR_ACTORANIM_H_
