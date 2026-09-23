#ifndef __UNKNOWN_FILE_0X800BF038_H_
#define __UNKNOWN_FILE_0X800BF038_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "game/stadium/stadium_framework.h"

typedef struct _ShadowCamera {
    /*0x00*/ u8 _00[0x40];
    /*0x40*/ Mtx viewMtx;
} ShadowCamera;

typedef struct _ShadowState {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ ShadowCamera* camera;
} ShadowState;

void maybeUpdateFunctionPointer(void);
void fn_800BF048(void);
void fn_800BF058(void (*func)(StadiumModel* model, Mtx m));
ShadowState* ShouldDrawShadows(void);

#endif // !__UNKNOWN_FILE_0X800BF038_H_
