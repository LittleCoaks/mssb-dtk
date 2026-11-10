#include "menus/menu_camera.h"
#define SQRT2_LINKAGE static
#include "header_rep_data.h"
#include "stl/mem.h"
#include "Unknown/File_0x800b0724.h"
#include "game/UnknownHomes_Game.h"
#include "Dolphin/GX/GXTransform.h"
#include "C3/control/frustum.h"

extern u8 *lbl_2_bss_1A824C;
extern f32 menuCameraSpringParams[][6];
extern f32 lbl_2_bss_1A81D4[];
extern f32 fn_2_4A18C(f32 arg0);
void fn_2_68DE8(s32 idx, void *dst);
extern void fn_80011640(void *arg0, void *arg1);

typedef struct PadInput {
    /* 0x00 */ E(u16, INPUT_BUTTON) hold;
    /* 0x02 */ E(u16, INPUT_BUTTON) trg;
    /* 0x04 */ E(u16, INPUT_BUTTON) rep;
    /* 0x06 */ u8 _06[0x10 - 0x06];
    /* 0x10 */ s8 stickX;
    /* 0x11 */ s8 stickY;
    /* 0x12 */ s8 substickX;
    /* 0x13 */ s8 substickY;
    /* 0x14 */ u8 triggerL;
    /* 0x15 */ u8 triggerR;
    /* 0x16 */ u8 _16[0x20 - 0x16];
} PadInput;

typedef struct CamPreset {
    /* 0x00 */ Vec eye;
    /* 0x0C */ Vec target;
    /* 0x18 */ f32 pitch;
    /* 0x1C */ f32 yaw;
    /* 0x20 */ f32 fov;
} CamPreset;

extern CamPreset menuCameraPresets[];
extern const f32 lbl_2_rodata_1140;

extern PadInput AtBat_ButtonInput1[4];
#define PAD_INPUTS AtBat_ButtonInput1

#define CAM (lbl_2_bss_1A824C + 0x190000)
#define CAM_F(off) (*(f32 *)&CAM[off])
#define CAM_V(off) (*(Vec *)&CAM[off])
/* x/y/z components of the Vec fields in menu_camera.h */
#define MENU_CAM_EYE_X (MENU_CAM_EYE + 0)
#define MENU_CAM_EYE_Y (MENU_CAM_EYE + 4)
#define MENU_CAM_EYE_Z (MENU_CAM_EYE + 8)
#define MENU_CAM_TARGET_X (MENU_CAM_TARGET + 0)
#define MENU_CAM_TARGET_Y (MENU_CAM_TARGET + 4)
#define MENU_CAM_TARGET_Z (MENU_CAM_TARGET + 8)
#define MENU_CAM_EYE_PREV_X (MENU_CAM_EYE_PREV + 0)
#define MENU_CAM_EYE_PREV_Y (MENU_CAM_EYE_PREV + 4)
#define MENU_CAM_EYE_PREV_Z (MENU_CAM_EYE_PREV + 8)
#define MENU_CAM_EYE_SPRING_X (MENU_CAM_EYE_SPRING + 0)
#define MENU_CAM_EYE_SPRING_Y (MENU_CAM_EYE_SPRING + 4)
#define MENU_CAM_EYE_SPRING_Z (MENU_CAM_EYE_SPRING + 8)
#define MENU_CAM_TARGET_PREV_X (MENU_CAM_TARGET_PREV + 0)
#define MENU_CAM_TARGET_PREV_Y (MENU_CAM_TARGET_PREV + 4)
#define MENU_CAM_TARGET_PREV_Z (MENU_CAM_TARGET_PREV + 8)
#define MENU_CAM_TARGET_SPRING_X (MENU_CAM_TARGET_SPRING + 0)
#define MENU_CAM_TARGET_SPRING_Y (MENU_CAM_TARGET_SPRING + 4)
#define MENU_CAM_TARGET_SPRING_Z (MENU_CAM_TARGET_SPRING + 8)
#define MENU_CAM_CLAMPED_EYE_X (MENU_CAM_CLAMPED_EYE + 0)
#define MENU_CAM_CLAMPED_EYE_Y (MENU_CAM_CLAMPED_EYE + 4)
#define MENU_CAM_CLAMPED_EYE_Z (MENU_CAM_CLAMPED_EYE + 8)
#define MENU_CAM_IN_BOUNDS_TARGET_X (MENU_CAM_IN_BOUNDS_TARGET + 0)
#define MENU_CAM_IN_BOUNDS_TARGET_Y (MENU_CAM_IN_BOUNDS_TARGET + 4)
#define MENU_CAM_IN_BOUNDS_TARGET_Z (MENU_CAM_IN_BOUNDS_TARGET + 8)
#define CAM_PORT ((s8)CAM[MENU_WORK_ACTIVE_PORT])

/* Fields of the camera block the scene passes in (lbl_2_bss_1A81D4). Note: Rep0DEMtxBlock in
 * menus/rep_0DE0.h describes this block with a different layout. */
#define CAMBLK_PITCH         0x30 /* u16: x rotation (debug free-look) */
#define CAMBLK_YAW           0x32 /* u16: y rotation */
#define CAMBLK_STRAFE_SPEED  0x34 /* f32: sideways speed (debug free-look) */
#define CAMBLK_FORWARD_SPEED 0x38 /* f32: forward speed (debug free-look) */
#define CAMBLK_FOV           0x3C /* f32 */
#define CAMBLK_TARGET        0x40 /* Vec: look-at target */
#define CAMBLK_TARGET_Y      (CAMBLK_TARGET + 4)
#define CAMBLK_TARGET_Z      (CAMBLK_TARGET + 8)
#define CAMBLK_EYE           0x4C /* Vec: eye */
#define CAMBLK_EYE_Y         (CAMBLK_EYE + 4)
#define CAMBLK_EYE_Z         (CAMBLK_EYE + 8)
#define CAMBLK_58            0x58 /* s32: cleared on snap; meaning unknown */
#define CAMBLK_F(off)        (lbl_2_bss_1A81D4[(off) / 4])

static inline Vec springStep(Vec target, Vec pos, Vec prev, f32 k, f32 damping, f32 rest) {
    Vec toTarget;
    Vec scaledPrev;
    Vec prevDir;
    f32 dist;
    f32 mag;

    PSVECSubtract(&target, &pos, &toTarget);
    dist = PSVECDistance(&target, &pos);
    PSVECSubtract(&prev, &pos, &prevDir);
    PSVECScale(&prevDir, 0.01f, &scaledPrev);
    mag = k * (rest - dist) + damping * (PSVECDotProduct(&scaledPrev, &toTarget) / dist);
    PSVECNormalize(&toTarget, &toTarget);
    PSVECScale(&toTarget, mag * lbl_2_rodata_1140, &toTarget);
    PSVECAdd(&target, &toTarget, &target);
    return target;
}

// .text:0x000946DC size:0x178 mapped:0x806D3770
void menuCamera_resetSpring(s32 arg0) {
    f32 scaleB = 0.00002f;
    f32 scaleA = 0.00001f;

    CAM_F(MENU_CAM_EYE_SPRING_K) = menuCameraSpringParams[arg0][0];
    CAM_F(MENU_CAM_EYE_SPRING_DAMP) = menuCameraSpringParams[arg0][1];
    CAM_F(MENU_CAM_EYE_SPRING_REST) = menuCameraSpringParams[arg0][2];
    CAM_F(MENU_CAM_TARGET_SPRING_K) = menuCameraSpringParams[arg0][3];
    CAM_F(MENU_CAM_TARGET_SPRING_DAMP) = menuCameraSpringParams[arg0][4];
    CAM_F(MENU_CAM_TARGET_SPRING_REST) = menuCameraSpringParams[arg0][5];
    CAM_F(MENU_CAM_EYE_PREV_X) = CAMBLK_F(CAMBLK_EYE);
    CAM_F(MENU_CAM_EYE_PREV_Y) = CAMBLK_F(CAMBLK_EYE_Y);
    CAM_F(MENU_CAM_EYE_PREV_Z) = CAMBLK_F(CAMBLK_EYE_Z);
    CAM_F(MENU_CAM_EYE_SPRING_X) = scaleA + CAMBLK_F(CAMBLK_EYE);
    CAM_F(MENU_CAM_EYE_SPRING_Y) = scaleA + CAMBLK_F(CAMBLK_EYE_Y);
    CAM_F(MENU_CAM_EYE_SPRING_Z) = scaleA + CAMBLK_F(CAMBLK_EYE_Z);
    CAM_F(MENU_CAM_TARGET_PREV_X) = scaleA + CAMBLK_F(CAMBLK_TARGET);
    CAM_F(MENU_CAM_TARGET_PREV_Y) = scaleA + CAMBLK_F(CAMBLK_TARGET_Y);
    CAM_F(MENU_CAM_TARGET_PREV_Z) = scaleA + CAMBLK_F(CAMBLK_TARGET_Z);
    CAM_F(MENU_CAM_TARGET_SPRING_X) = scaleB + CAMBLK_F(CAMBLK_TARGET);
    CAM_F(MENU_CAM_TARGET_SPRING_Y) = scaleB + CAMBLK_F(CAMBLK_TARGET_Y);
    CAM_F(MENU_CAM_TARGET_SPRING_Z) = scaleB + CAMBLK_F(CAMBLK_TARGET_Z);
}

// .text:0x00094634 size:0xA8 mapped:0x806D36C8
void menuCamera_setSpringPreset(s32 arg0) {
    CAM_F(MENU_CAM_EYE_SPRING_K) = menuCameraSpringParams[arg0][0];
    CAM_F(MENU_CAM_EYE_SPRING_DAMP) = menuCameraSpringParams[arg0][1];
    CAM_F(MENU_CAM_EYE_SPRING_REST) = menuCameraSpringParams[arg0][2];
    CAM_F(MENU_CAM_TARGET_SPRING_K) = menuCameraSpringParams[arg0][3];
    CAM_F(MENU_CAM_TARGET_SPRING_DAMP) = menuCameraSpringParams[arg0][4];
    CAM_F(MENU_CAM_TARGET_SPRING_REST) = menuCameraSpringParams[arg0][5];
    if (arg0 == 0) {
        CAM[MENU_CAM_SPRING_ENABLED] = 0;
    } else {
        CAM[MENU_CAM_SPRING_ENABLED] = 1;
    }
}

// .text:0x0009461C size:0x18 mapped:0x806D36B0
void menuCamera_setFollowSlot(s16 arg0) {
    *(s16 *)&CAM[MENU_CAM_FOLLOW_SLOT] = arg0;
}

// .text:0x00094604 size:0x18 mapped:0x806D3698
void menuCamera_setEyeFollowsSlot(u8 arg0) {
    CAM[MENU_CAM_EYE_FOLLOWS_SLOT] = arg0;
}

// .text:0x00093C64 size:0x9A0 mapped:0x806D2CF8
void menuCamera_snapToPreset(Mtx arg0) {
    u8 *self = (u8 *)lbl_2_bss_1A81D4;
    Mtx44 proj;
    Vec ang;
    Vec offset;
    Vec lookAt;
    s32 idx;

    idx = CAM[MENU_CAM_PRESET];
    if (CAM[MENU_CAM_EYE_FOLLOWS_SLOT] == 1) {
        memcpy(&ang, &menuCameraPresets[idx].eye, sizeof(Vec));
        fn_2_68DE8(*(s16 *)&CAM[MENU_CAM_FOLLOW_SLOT], &offset);
        PSVECAdd(&offset, &ang, &ang);
        memcpy(self + CAMBLK_EYE, &ang, sizeof(Vec));
    } else {
        memcpy(&ang, &menuCameraPresets[idx].eye, sizeof(Vec));
        memcpy(self + CAMBLK_EYE, &ang, sizeof(Vec));
    }

    if (CAM[MENU_CAM_UNBOUNDED] == 0) {
        if (*(f32 *)(self + CAMBLK_EYE) <= -10.0f) {
            *(f32 *)(self + CAMBLK_EYE) = -10.0f;
        }
        if (*(f32 *)(self + CAMBLK_EYE) >= 11.0f) {
            *(f32 *)(self + CAMBLK_EYE) = 11.0f;
        }
        if (*(f32 *)(self + CAMBLK_EYE_Z) <= -50.0f) {
            *(f32 *)(self + CAMBLK_EYE_Z) = -50.0f;
        }
        if (*(f32 *)(self + CAMBLK_EYE_Z) >= -22.0f) {
            *(f32 *)(self + CAMBLK_EYE_Z) = -22.0f;
        }
        memcpy(&CAM[MENU_CAM_CLAMPED_EYE], self + CAMBLK_EYE, sizeof(Vec));
    }
    memcpy(&CAM[MENU_CAM_EYE], self + CAMBLK_EYE, sizeof(Vec));

    CAM_F(MENU_CAM_EYE_PREV_X) = CAM_F(MENU_CAM_EYE_X);
    CAM_F(MENU_CAM_EYE_PREV_Y) = CAM_F(MENU_CAM_EYE_Y);
    CAM_F(MENU_CAM_EYE_PREV_Z) = CAM_F(MENU_CAM_EYE_Z);
    CAM_F(MENU_CAM_EYE_SPRING_X) = 0.00001f + CAM_F(MENU_CAM_EYE_X);
    CAM_F(MENU_CAM_EYE_SPRING_Y) = 0.00001f + CAM_F(MENU_CAM_EYE_Y);
    CAM_F(MENU_CAM_EYE_SPRING_Z) = 0.00001f + CAM_F(MENU_CAM_EYE_Z);

    if (*(s16 *)&CAM[MENU_CAM_FOLLOW_SLOT] != -1) {
        fn_2_68DE8(*(s16 *)&CAM[MENU_CAM_FOLLOW_SLOT], &lookAt);
    } else {
        memcpy(&lookAt, &menuCameraPresets[idx].target, sizeof(Vec));
    }
    memcpy(&CAM[MENU_CAM_IN_BOUNDS_TARGET], &lookAt, sizeof(Vec));

    if (CAM[MENU_CAM_UNBOUNDED] == 0) {
        if (lookAt.x <= -10.0f) {
            lookAt.x = -10.0f;
        } else if (lookAt.x >= 11.0f) {
            lookAt.x = 11.0f;
        } else {
            CAM_F(MENU_CAM_IN_BOUNDS_TARGET_X) = lookAt.x;
        }
        if (lookAt.z <= -24.0f) {
            lookAt.z = -24.0f;
        } else if (lookAt.z >= 8.0f) {
            lookAt.z = 8.0f;
        } else {
            CAM_F(MENU_CAM_IN_BOUNDS_TARGET_Z) = lookAt.z;
        }
    }
    memcpy(&CAM[MENU_CAM_TARGET], &lookAt, sizeof(Vec));

    CAM_F(MENU_CAM_TARGET_PREV_X) = 0.00001f + CAM_F(MENU_CAM_TARGET_X);
    CAM_F(MENU_CAM_TARGET_PREV_Y) = 0.00001f + CAM_F(MENU_CAM_TARGET_Y);
    CAM_F(MENU_CAM_TARGET_PREV_Z) = 0.00001f + CAM_F(MENU_CAM_TARGET_Z);
    CAM_F(MENU_CAM_TARGET_SPRING_X) = 0.00002f + CAM_F(MENU_CAM_TARGET_X);
    CAM_F(MENU_CAM_TARGET_SPRING_Y) = 0.00002f + CAM_F(MENU_CAM_TARGET_Y);
    CAM_F(MENU_CAM_TARGET_SPRING_Z) = 0.00002f + CAM_F(MENU_CAM_TARGET_Z);

    menuCamera_springTarget(arg0, &lookAt);
    memcpy(&CAM[MENU_CAM_TARGET], &lookAt, sizeof(Vec));
    menuCamera_springEye(arg0, &lookAt);

    memcpy(self + CAMBLK_EYE, &CAM[MENU_CAM_EYE], sizeof(Vec));
    memcpy(self + CAMBLK_TARGET, &CAM[MENU_CAM_TARGET], sizeof(Vec));

    C_MTXFrustum(proj, -0.175f, 0.175f, 0.25f, -0.25f, 1.0f, 512.0f);
    GXSetProjection(proj, 0);

    fn_800B806C(0, -240.0f, 240.0f, -320.0f, 320.0f, -512.0f, -1.0f, 1280.0f);

    *(s32 *)(self + CAMBLK_58) = 0;
    *(f32 *)(self + CAMBLK_FORWARD_SPEED) = 0.0f;
    *(s16 *)(self + CAMBLK_PITCH) = menuCameraPresets[idx].pitch;
    *(s16 *)(self + CAMBLK_YAW) = menuCameraPresets[idx].yaw;
    *(f32 *)(self + CAMBLK_FOV) = menuCameraPresets[idx].fov;
}

// .text:0x00093BF8 size:0x6C mapped:0x806D2C8C
void menuCamera_update(Mtx arg0) {
    switch (CAM[MENU_CAM_MODE]) {
    case MENU_CAM_MODE_PRESET:
        menuCamera_updatePreset(arg0);
        break;
    case MENU_CAM_MODE_DEBUG_FREE_LOOK:
        menuCamera_updateDebugFreeLook(arg0);
        break;
    }
    fn_80011640(arg0, arg0);
}

// .text:0x000932DC size:0x91C mapped:0x806D2370
void menuCamera_updatePreset(Mtx arg0) {
    u8 *self = (u8 *)arg0;
    Vec up = {0.0f, 1.0f, 0.0f};
    Vec fwd = {0.0f, 0.0f, 1.0f};
    Vec ang;
    Vec offset;
    Vec lookAt;
    Mtx rotX;
    Mtx rotY;
    Mtx rot;
    f32 cosY;
    f32 sinY;
    s32 idx;

    idx = CAM[MENU_CAM_PRESET];
    *(u16 *)(self + CAMBLK_PITCH) = menuCameraPresets[idx].pitch;
    *(u16 *)(self + CAMBLK_YAW) = menuCameraPresets[idx].yaw;
    *(f32 *)(self + CAMBLK_STRAFE_SPEED) = 0.0f;
    *(f32 *)(self + CAMBLK_FORWARD_SPEED) = 0.0f;

    ang.x = *(u16 *)(self + CAMBLK_PITCH);
    ang.y = *(u16 *)(self + CAMBLK_YAW);
    ang.z = 0.0f;
    PSVECScale(&ang, 0.0000958738f, &ang);

    PSMTXRotRad(rotX, 'X', ang.x);
    PSMTXRotRad(rotY, 'Y', ang.y);
    sinY = rotY[0][2];
    cosY = rotY[0][0];
    PSMTXConcat(rotY, rotX, rot);
    PSMTXMultVec(rot, &fwd, (Vec *)(self + CAMBLK_TARGET));

    *(f32 *)(self + CAMBLK_EYE) += *(f32 *)(self + CAMBLK_FORWARD_SPEED) * sinY - *(f32 *)(self + CAMBLK_STRAFE_SPEED) * cosY;
    *(f32 *)(self + CAMBLK_EYE_Z) += *(f32 *)(self + CAMBLK_FORWARD_SPEED) * cosY + *(f32 *)(self + CAMBLK_STRAFE_SPEED) * sinY;
    *(f32 *)(self + CAMBLK_TARGET) += *(f32 *)(self + CAMBLK_EYE);
    *(f32 *)(self + CAMBLK_TARGET_Y) += *(f32 *)(self + CAMBLK_EYE_Y);
    *(f32 *)(self + CAMBLK_TARGET_Z) += *(f32 *)(self + CAMBLK_EYE_Z);

    if (CAM[MENU_CAM_EYE_FOLLOWS_SLOT] == 1) {
        memcpy(&ang, &menuCameraPresets[idx].eye, sizeof(Vec));
        fn_2_68DE8(*(s16 *)&CAM[MENU_CAM_FOLLOW_SLOT], &offset);
        PSVECAdd(&offset, &ang, &ang);
        memcpy(self + CAMBLK_EYE, &ang, sizeof(Vec));
    } else {
        memcpy(&ang, &menuCameraPresets[idx].eye, sizeof(Vec));
        memcpy(self + CAMBLK_EYE, &ang, sizeof(Vec));
    }

    if (CAM[MENU_CAM_UNBOUNDED] == 0) {
        if (*(f32 *)(self + CAMBLK_EYE) <= -10.0f) {
            *(f32 *)(self + CAMBLK_EYE) = -10.0f;
        }
        if (*(f32 *)(self + CAMBLK_EYE) >= 11.0f) {
            *(f32 *)(self + CAMBLK_EYE) = 11.0f;
        }
        if (*(f32 *)(self + CAMBLK_EYE_Z) <= -50.0f) {
            *(f32 *)(self + CAMBLK_EYE_Z) = -50.0f;
        }
        if (*(f32 *)(self + CAMBLK_EYE_Z) >= -22.0f) {
            *(f32 *)(self + CAMBLK_EYE_Z) = -22.0f;
        }
    }
    memcpy(&CAM[MENU_CAM_EYE], self + CAMBLK_EYE, sizeof(Vec));

    if (*(s16 *)&CAM[MENU_CAM_FOLLOW_SLOT] != -1) {
        fn_2_68DE8(*(s16 *)&CAM[MENU_CAM_FOLLOW_SLOT], &lookAt);
    } else {
        memcpy(&lookAt, &menuCameraPresets[idx].target, sizeof(Vec));
    }

    if (CAM[MENU_CAM_UNBOUNDED] == 0) {
        if (lookAt.x <= -10.0f) {
            lookAt.x = -10.0f;
        } else if (lookAt.x >= 11.0f) {
            lookAt.x = 11.0f;
        } else {
            CAM_F(MENU_CAM_IN_BOUNDS_TARGET_X) = lookAt.x;
        }
        if (lookAt.z <= -24.0f) {
            lookAt.z = -24.0f;
        } else if (lookAt.z >= 8.0f) {
            lookAt.z = 8.0f;
        } else {
            CAM_F(MENU_CAM_IN_BOUNDS_TARGET_Z) = lookAt.z;
        }
    }
    memcpy(&CAM[MENU_CAM_TARGET], &lookAt, sizeof(Vec));

    menuCamera_springTarget(arg0, &lookAt);
    memcpy(&CAM[MENU_CAM_TARGET], &lookAt, sizeof(Vec));
    menuCamera_springEye(arg0, &lookAt);

    memcpy(self + CAMBLK_EYE, &CAM[MENU_CAM_EYE], sizeof(Vec));
    memcpy(self + CAMBLK_TARGET, &CAM[MENU_CAM_TARGET], sizeof(Vec));
    *(f32 *)(self + CAMBLK_FOV) = menuCameraPresets[idx].fov;

    makeLookAtMatrix(arg0, (Vec *)(self + CAMBLK_EYE), &up, (Vec *)(self + CAMBLK_TARGET));
}

// .text:0x00092F2C size:0x3B0 mapped:0x806D1FC0
void menuCamera_updateDebugFreeLook(Mtx arg0) {
    u8 *self = (u8 *)arg0;
    Vec up = {0.0f, 1.0f, 0.0f};
    Vec ang;
    Vec fwd = {0.0f, 0.0f, 1.0f};
    Mtx rotX;
    Mtx rotY;
    Mtx rot;
    f32 cosY;
    f32 sinY;

    if (!(PAD_INPUTS[CAM_PORT].hold & INPUT_TRIGGER_Z)) {
        *(u16 *)(self + CAMBLK_PITCH) -= PAD_INPUTS[CAM_PORT].substickY;
        *(u16 *)(self + CAMBLK_YAW) += PAD_INPUTS[CAM_PORT].substickX;
        *(f32 *)(self + CAMBLK_STRAFE_SPEED) = PAD_INPUTS[CAM_PORT].stickX / -256.0f;
        *(f32 *)(self + CAMBLK_FORWARD_SPEED) = PAD_INPUTS[CAM_PORT].stickY / 256.0f;
        *(f32 *)(self + CAMBLK_EYE_Y) += PAD_INPUTS[CAM_PORT].triggerR / 1024.0f;
        *(f32 *)(self + CAMBLK_EYE_Y) -= PAD_INPUTS[CAM_PORT].triggerL / 1024.0f;
    }

    if (PAD_INPUTS[CAM_PORT].rep & INPUT_BUTTON_Y) {
        *(f32 *)(self + CAMBLK_FOV) -= 0.01f;
    } else if (PAD_INPUTS[CAM_PORT].rep & INPUT_BUTTON_X) {
        *(f32 *)(self + CAMBLK_FOV) += 0.01f;
    }

    ang.x = *(u16 *)(self + CAMBLK_PITCH);
    ang.y = *(u16 *)(self + CAMBLK_YAW);
    ang.z = 0.0f;
    PSVECScale(&ang, 0.0000958738f, &ang);

    PSMTXRotRad(rotX, 'X', ang.x);
    PSMTXRotRad(rotY, 'Y', ang.y);
    sinY = rotY[0][2];
    cosY = rotY[0][0];
    PSMTXConcat(rotY, rotX, rot);
    PSMTXMultVec(rot, &fwd, (Vec *)(self + CAMBLK_TARGET));

    *(f32 *)(self + CAMBLK_EYE) += *(f32 *)(self + CAMBLK_FORWARD_SPEED) * sinY - *(f32 *)(self + CAMBLK_STRAFE_SPEED) * cosY;
    *(f32 *)(self + CAMBLK_EYE_Z) += *(f32 *)(self + CAMBLK_FORWARD_SPEED) * cosY + *(f32 *)(self + CAMBLK_STRAFE_SPEED) * sinY;
    *(f32 *)(self + CAMBLK_TARGET) += *(f32 *)(self + CAMBLK_EYE);
    *(f32 *)(self + CAMBLK_TARGET_Y) += *(f32 *)(self + CAMBLK_EYE_Y);
    *(f32 *)(self + CAMBLK_TARGET_Z) += *(f32 *)(self + CAMBLK_EYE_Z);

    makeLookAtMatrix(arg0, (Vec *)(self + CAMBLK_EYE), &up, (Vec *)(self + CAMBLK_TARGET));
}


// .text:0x00092CB0 size:0x27C mapped:0x806D1D44
void menuCamera_springEye(void *arg0, Vec *arg1) {
    Vec result;
    Vec target;
    Vec pos;
    Vec prev;
    f32 x;
    f32 y;
    f32 z;

    if (CAM[MENU_CAM_SPRING_ENABLED] != 0) {
        x = CAM_F(MENU_CAM_EYE_X);
        y = CAM_F(MENU_CAM_EYE_Y);
        z = CAM_F(MENU_CAM_EYE_Z);
        target.x = CAM_F(MENU_CAM_EYE_SPRING_X);
        target.y = CAM_F(MENU_CAM_EYE_SPRING_Y);
        target.z = CAM_F(MENU_CAM_EYE_SPRING_Z);
        pos.x = x;
        pos.y = y;
        pos.z = z;
        prev.x = CAM_F(MENU_CAM_EYE_PREV_X);
        prev.y = CAM_F(MENU_CAM_EYE_PREV_Y);
        prev.z = CAM_F(MENU_CAM_EYE_PREV_Z);
        result = springStep(target, pos, prev, CAM_F(MENU_CAM_EYE_SPRING_K), CAM_F(MENU_CAM_EYE_SPRING_DAMP), CAM_F(MENU_CAM_EYE_SPRING_REST));
        CAM_F(MENU_CAM_EYE_X) = result.x;
        CAM_F(MENU_CAM_EYE_Y) = result.y;
        CAM_F(MENU_CAM_EYE_Z) = result.z;
        CAM_F(MENU_CAM_EYE_SPRING_X) = result.x;
        CAM_F(MENU_CAM_EYE_SPRING_Y) = result.y;
        CAM_F(MENU_CAM_EYE_SPRING_Z) = result.z;
        CAM_F(MENU_CAM_EYE_PREV_X) = x;
        CAM_F(MENU_CAM_EYE_PREV_Y) = y;
        CAM_F(MENU_CAM_EYE_PREV_Z) = z;
    }
}

// .text:0x00092A34 size:0x27C mapped:0x806D1AC8
void menuCamera_springTarget2D(void *arg0, Vec *arg1) {
    Vec result;
    Vec target;
    Vec pos;
    Vec prev;

    if (CAM[MENU_CAM_SPRING_ENABLED] != 0) {
        arg1->x = fn_2_4A18C(arg1->x);
        arg1->y = fn_2_4A18C(arg1->y);
        target.x = CAM_F(MENU_CAM_TARGET_SPRING_X);
        target.y = CAM_F(MENU_CAM_TARGET_SPRING_Y);
        target.z = CAM_F(MENU_CAM_TARGET_SPRING_Z);
        pos.x = arg1->x;
        pos.y = arg1->y;
        pos.z = 0.0f;
        prev.x = CAM_F(MENU_CAM_TARGET_PREV_X);
        prev.y = CAM_F(MENU_CAM_TARGET_PREV_Y);
        prev.z = CAM_F(MENU_CAM_TARGET_PREV_Z);
        result = springStep(target, pos, prev, CAM_F(MENU_CAM_TARGET_SPRING_K), CAM_F(MENU_CAM_TARGET_SPRING_DAMP), CAM_F(MENU_CAM_TARGET_SPRING_REST));
        CAM_F(MENU_CAM_TARGET_PREV_X) = arg1->x;
        CAM_F(MENU_CAM_TARGET_PREV_Y) = arg1->y;
        CAM_F(MENU_CAM_TARGET_PREV_Z) = 0.0f;
        CAM_F(MENU_CAM_TARGET_SPRING_X) = result.x;
        CAM_F(MENU_CAM_TARGET_SPRING_Y) = result.y;
        CAM_F(MENU_CAM_TARGET_SPRING_Z) = result.z;
        arg1->x = result.x;
        arg1->y = result.y;
    }
}

// .text:0x000927C8 size:0x26C mapped:0x806D185C
void menuCamera_springTarget(void *arg0, Vec *arg1) {
    Vec result;
    Vec target;
    Vec pos;
    Vec prev;
    Vec in;

    if (CAM[MENU_CAM_SPRING_ENABLED] != 0) {
        memcpy(&in, arg1, sizeof(Vec));
        target.x = CAM_F(MENU_CAM_TARGET_SPRING_X);
        target.y = CAM_F(MENU_CAM_TARGET_SPRING_Y);
        target.z = CAM_F(MENU_CAM_TARGET_SPRING_Z);
        memcpy(&pos, arg1, sizeof(Vec));
        prev.x = CAM_F(MENU_CAM_TARGET_PREV_X);
        prev.y = CAM_F(MENU_CAM_TARGET_PREV_Y);
        prev.z = CAM_F(MENU_CAM_TARGET_PREV_Z);
        result = springStep(target, pos, prev, CAM_F(MENU_CAM_TARGET_SPRING_K), CAM_F(MENU_CAM_TARGET_SPRING_DAMP), CAM_F(MENU_CAM_TARGET_SPRING_REST));
        CAM_F(MENU_CAM_TARGET_PREV_X) = arg1->x;
        CAM_F(MENU_CAM_TARGET_PREV_Y) = arg1->y;
        CAM_F(MENU_CAM_TARGET_PREV_Z) = arg1->z;
        CAM_F(MENU_CAM_TARGET_SPRING_X) = result.x;
        CAM_F(MENU_CAM_TARGET_SPRING_Y) = result.y;
        CAM_F(MENU_CAM_TARGET_SPRING_Z) = result.z;
        arg1->x = result.x;
        arg1->y = result.y;
        arg1->z = result.z;
    }
}
