#ifndef _C3_ANIM_ANIMBANK_H_
#define _C3_ANIM_ANIMBANK_H_

#include "mssbTypes.h"
#include "C3/anim.h"

struct ANIMAnimTrack* ANIMGetTrackFromSequence(ANIMSequences* animSeq, u16 animTrackID);

// ANIMGet is declared in C3/anim.h (single-parameter form, proven by the
// target: only r3 is read; r4 is clobbered before any use).

#endif // _C3_ANIM_ANIMBANK_H_
