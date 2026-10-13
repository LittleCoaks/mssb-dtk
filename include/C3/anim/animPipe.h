#ifndef _C3_ANIM_ANIMPIPE_H_
#define _C3_ANIM_ANIMPIPE_H_

#include "mssbTypes.h"
#include "C3/anim.h"

void Squad(void);

void GetData(void);

struct ANIMPipe;
struct ANIMAnimTrack;
struct Control;

void ANIMBind(struct ANIMPipe* animPipe, struct Control* control, struct ANIMAnimTrack* animTrack, f32 time);

#endif // _C3_ANIM_ANIMPIPE_H_
