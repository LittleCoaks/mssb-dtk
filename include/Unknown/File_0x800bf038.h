#ifndef __UNKNOWN_FILE_0X800BF038_H_
#define __UNKNOWN_FILE_0X800BF038_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "Dolphin/gx.h"
#include "game/stadium/stadium_framework.h"

typedef struct _ShadowCamera {
    /*0x00*/ u8 _00[0x34];
    /*0x34*/ Vec lightDir;
    /*0x40*/ Mtx viewMtx;
    /*0x70*/ u8 _70[0xB0 - 0x70];
    /*0xB0*/ Mtx mtxB0;
} ShadowCamera; // size: 0xE0

typedef struct _ShadowState {
    /*0x00*/ E(u8, BOOL) enabled;
    /*0x01*/ u8 _01[0x8 - 0x1];
    /*0x08*/ void* unk08;
    /*0x0C*/ GXTlutObj* tlut;
    /*0x10*/ u8 _10[0x4];
    /*0x14*/ ShadowCamera* camera;
    /*0x18*/ void (*callback18)(void);
    /*0x1C*/ void (*modelCallback)(StadiumModel* model, Mtx m);
    /*0x20*/ void (*callback20)(void);
    /*0x24*/ u16 pointCount;     // points accumulated by setVectors since the last reset
    /*0x26*/ u8 _26[2];
    /*0x28*/ f32 bounds[3][2];   // [axis][0] = min, [axis][1] = max of the accumulated points
    /*0x40*/ Vec pointSum;
    /*0x4C*/ u8 _4C;
    /*0x4D*/ s8 unk4D;
    /*0x4E*/ u8 _4E[0x50 - 0x4E];
} ShadowState;

extern ShadowState drawShadows;

void maybeUpdateFunctionPointer(void (*func)(void));
void fn_800BF048(void (*func)(void));
void fn_800BF058(void (*func)(StadiumModel* model, Mtx m));
ShadowState* ShouldDrawShadows(void);

#endif // !__UNKNOWN_FILE_0X800BF038_H_
