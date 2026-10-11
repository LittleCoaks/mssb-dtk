#ifndef __UNUSED_REL_REP_7978_H_
#define __UNUSED_REL_REP_7978_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

typedef struct DbgCamInput {
    s8 lookX;
    s8 lookY;
    s8 turnX;
    s8 turnY;
    u8 moveFwd;
    u8 moveBack;
} DbgCamInput;

struct DbgCam;
typedef void (*DbgCamCallback)(struct DbgCam *cam, u32 buttons, u32 flags, s32 unused, DbgCamInput *input);

typedef struct DbgCam {
    Mtx view;
    Mtx44 proj;
    Vec pos;
    Vec dir;
    Vec up;
    u8 pad94[0x10];
    f32 yaw;
    f32 pitch;
    f32 dist;
    f32 angleScale;
    f32 zoomRate;
    f32 zoom;
    f32 invZoom;
    f32 nearPlane;
    f32 farPlane;
    f32 frustum[4];
    DbgCamCallback callback;
} DbgCam;

void fn_1_26D28(DbgCam *cam, u32 buttons, u32 flags, s32 unused, DbgCamInput *input);
void fn_1_272DC(DbgCam *cam, u32 mtxId);
void fn_1_27330(DbgCam *cam);
void fn_1_273D8(DbgCam *cam);

#endif // !__UNUSED_REL_REP_7978_H_
