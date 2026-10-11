#define REP_HEADER_DATA_FN getRepHeaderData_rep7978
#include "debug/rep_7978.h"
/* No dolsqrtf2() calls here; static linkage keeps its local statics out of .rodata. */
#define SQRT2_LINKAGE static
#include "game/UnknownHomes_Game.h"
#include "header_rep_data.h"
#include "Dolphin/GX/GXTransform.h"

static inline void camUpdateView(DbgCam *cam) {
    Vec target;

    PSVECAdd(&cam->pos, &cam->dir, &target);
    C_MTXLookAt(cam->view, &cam->pos, &cam->up, &target);
}

static inline void camUpdateProj(DbgCam *cam) {
    C_MTXFrustum(cam->proj,
                 cam->invZoom * (cam->frustum[0] * cam->nearPlane) / 1280.f,
                 cam->invZoom * (cam->frustum[1] * cam->nearPlane) / 1280.f,
                 cam->invZoom * (cam->frustum[2] * cam->nearPlane) / 1280.f,
                 cam->invZoom * (cam->frustum[3] * cam->nearPlane) / 1280.f,
                 cam->nearPlane, cam->farPlane);
}

// .text:0x000273D8 size:0x188
void fn_1_273D8(DbgCam *cam) {
    cam->dist = 5.f;
    cam->angleScale = 120.f;
    cam->callback = NULL;
    cam->yaw = 0.f;
    cam->pitch = 0.f;
    cam->pos.z = 0.f;
    cam->pos.y = 0.f;
    cam->pos.x = 0.f;
    cam->dir.y = 0.f;
    cam->dir.x = 0.f;
    cam->dir.z = 1.f;
    cam->up.x = 0.f;
    cam->up.y = 1.f;
    cam->up.z = 0.f;
    camUpdateView(cam);
    cam->zoomRate = 1.f;
    cam->zoom = 1.f;
    cam->invZoom = 1.f / cam->zoom;
    cam->nearPlane = 1.f;
    cam->farPlane = 512.f;
    cam->frustum[0] = 240.f;
    cam->frustum[1] = -240.f;
    cam->frustum[2] = -320.f;
    cam->frustum[3] = 320.f;
    camUpdateProj(cam);
}

// .text:0x00027330 size:0xA8
void fn_1_27330(DbgCam *cam) {
    camUpdateView(cam);
    camUpdateProj(cam);
}

// .text:0x000272DC size:0x54
void fn_1_272DC(DbgCam *cam, u32 mtxId) {
    GXSetProjection(cam->proj, GX_PERSPECTIVE);
    GXLoadPosMtxImm(cam->view, mtxId);
    GXSetCurrentMtx(mtxId);
}

// .text:0x00026D28 size:0x5B4
void fn_1_26D28(DbgCam *cam, u32 buttons, u32 flags, s32 unused, DbgCamInput *input) {
    Quaternion quat;
    Vec move;
    Mtx rot;

    if (cam->callback == NULL || cam->callback == fn_1_26D28) {
      if (flags & 0x10) {
        fn_1_273D8(cam);
      } else {
        cam->yaw -= (3.1415927f * cam->angleScale / 180.f * input->turnX) / 128.f / 60.f;
        cam->pitch -= (3.1415927f * cam->angleScale / 180.f * input->turnY) / 128.f / 60.f;
        while (cam->yaw < -3.1415927f) {
            cam->yaw += 6.2831855f;
        }
        while (cam->yaw >= 3.1415927f) {
            cam->yaw -= 6.2831855f;
        }
        if (cam->pitch < -3.1385248f) {
            cam->pitch = -3.1385248f;
        } else if (cam->pitch > 3.1385248f) {
            cam->pitch = 3.1385248f;
        }
        move.x = 0.f;
        move.y = 0.f;
        move.z = 1.f;
        PSVECCrossProduct(&move, &cam->up, &cam->dir);
        PSVECNormalize(&cam->dir, &cam->dir);
        C_QUATRotAxisRad(&quat, &cam->dir, cam->pitch);
        PSMTXQuat(rot, &quat);
        PSMTXMultVec(rot, &move, &cam->dir);
        C_QUATRotAxisRad(&quat, &cam->up, cam->yaw);
        PSMTXQuat(rot, &quat);
        PSMTXMultVec(rot, &cam->dir, &cam->dir);
        move.x = -cam->dist * input->lookX / 128.f / 60.f;
        move.z = cam->dist * input->lookY / 128.f / 60.f;
        move.y = cam->dist * input->moveFwd / 150.f / 60.f;
        move.y = move.y - cam->dist * input->moveBack / 150.f / 60.f;
        PSMTXMultVec(rot, &move, &move);
        PSVECAdd(&cam->pos, &move, &cam->pos);
        cam->zoom += cam->zoomRate * ((buttons & INPUT_BUTTON_X) != 0) / 60.f;
        cam->zoom -= cam->zoomRate * ((buttons & INPUT_BUTTON_Y) != 0) / 60.f;
        cam->zoom = 0.1f * (cam->zoom == 0.f) + cam->zoom * (cam->zoom != 0.f);
        cam->invZoom = 1.f / cam->zoom;
      }
    } else {
        cam->callback(cam, buttons, flags, unused, input);
    }
}
