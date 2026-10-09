#ifndef __GAME_PITCHING_PERFECT_PITCH_GFX_H_
#define __GAME_PITCHING_PERFECT_PITCH_GFX_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

// Effect state passed to fn_3_CABF0.
typedef struct _PerfectPitchTrail {
    /*0x00*/ u8 _00[0x8];
    /*0x08*/ Vec pos;
    /*0x14*/ Quaternion rot;
    /*0x24*/ u32 frame;
} PerfectPitchTrail;

void fn_3_CABB4(void);
void fn_3_CABF0(PerfectPitchTrail* trail);
void fn_3_CAE00(void);
void perfectPitchGraphicsRelated(void);
void fn_3_CB344(int actorIndex, int starType);
void fn_3_CB1B0(int actorIndex, u8 pitch, int frame);
void fn_3_CB234(int actorIndex, BOOL immediate);
void fn_3_CB284(int actorIndex, int frame, f32 charge);

#endif // !__GAME_PITCHING_PERFECT_PITCH_GFX_H_
