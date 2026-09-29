#ifndef __UNKNOWN_FILE_0X800BF038_H_
#define __UNKNOWN_FILE_0X800BF038_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "Dolphin/gx.h"
#include "game/stadium/stadium_framework.h"

typedef struct _ShadowCamera {
    /*0x00*/ u8 _00[0x40];
    /*0x40*/ Mtx viewMtx;
} ShadowCamera;

typedef struct _ShadowState {
    /*0x00*/ u8 _00[0x8];
    /*0x08*/ void* unk08;
    /*0x0C*/ GXTlutObj* tlut;
    /*0x10*/ u8 _10[0x4];
    /*0x14*/ ShadowCamera* camera;
    /*0x18*/ void (*callback18)(void);
    /*0x1C*/ void (*modelCallback)(StadiumModel* model, Mtx m);
    /*0x20*/ void (*callback20)(void);
    /*0x24*/ u8 _24[0x50 - 0x24];
} ShadowState;

extern ShadowState drawShadows;

void maybeUpdateFunctionPointer(void (*func)(void));
void fn_800BF048(void (*func)(void));
void fn_800BF058(void (*func)(StadiumModel* model, Mtx m));
ShadowState* ShouldDrawShadows(void);

#endif // !__UNKNOWN_FILE_0X800BF038_H_
