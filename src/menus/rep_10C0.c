#include "menus/rep_10C0.h"
#define SQRT2_LINKAGE static
#include "header_rep_data.h"
#include "stl/mem.h"
#include "Unknown/File_0x800b0724.h"
#include "game/UnknownHomes_Game.h"
#include "Dolphin/GX/GXTransform.h"
#include "C3/control/frustum.h"

extern u8 *lbl_2_bss_1A824C;
extern f32 lbl_2_data_3BB0[][6];
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

extern CamPreset lbl_2_data_38E0[];
extern const f32 lbl_2_rodata_1140;

extern PadInput AtBat_ButtonInput1[4];
#define PAD_INPUTS AtBat_ButtonInput1

#define CAM (lbl_2_bss_1A824C + 0x190000)
#define CAM_F(off) (*(f32 *)&CAM[off])
#define CAM_V(off) (*(Vec *)&CAM[off])
#define CAM_PORT ((s8)CAM[0x7863])

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
void fn_2_946DC(s32 arg0) {
    f32 scaleB = 0.00002f;
    f32 scaleA = 0.00001f;

    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7668] = lbl_2_data_3BB0[arg0][0];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x766C] = lbl_2_data_3BB0[arg0][1];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7670] = lbl_2_data_3BB0[arg0][2];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7674] = lbl_2_data_3BB0[arg0][3];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7678] = lbl_2_data_3BB0[arg0][4];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x767C] = lbl_2_data_3BB0[arg0][5];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7620] = lbl_2_bss_1A81D4[19];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7624] = lbl_2_bss_1A81D4[20];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7628] = lbl_2_bss_1A81D4[21];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x762C] = scaleA + lbl_2_bss_1A81D4[19];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7630] = scaleA + lbl_2_bss_1A81D4[20];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7634] = scaleA + lbl_2_bss_1A81D4[21];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7638] = scaleA + lbl_2_bss_1A81D4[16];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x763C] = scaleA + lbl_2_bss_1A81D4[17];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7640] = scaleA + lbl_2_bss_1A81D4[18];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7644] = scaleB + lbl_2_bss_1A81D4[16];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7648] = scaleB + lbl_2_bss_1A81D4[17];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x764C] = scaleB + lbl_2_bss_1A81D4[18];
}

// .text:0x00094634 size:0xA8 mapped:0x806D36C8
void fn_2_94634(s32 arg0) {
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7668] = lbl_2_data_3BB0[arg0][0];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x766C] = lbl_2_data_3BB0[arg0][1];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7670] = lbl_2_data_3BB0[arg0][2];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7674] = lbl_2_data_3BB0[arg0][3];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7678] = lbl_2_data_3BB0[arg0][4];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x767C] = lbl_2_data_3BB0[arg0][5];
    if (arg0 == 0) {
        lbl_2_bss_1A824C[0x190000 + 0x7855] = 0;
    } else {
        lbl_2_bss_1A824C[0x190000 + 0x7855] = 1;
    }
}

// .text:0x0009461C size:0x18 mapped:0x806D36B0
void fn_2_9461C(s16 arg0) {
    *(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x774A] = arg0;
}

// .text:0x00094604 size:0x18 mapped:0x806D3698
void fn_2_94604(u8 arg0) {
    lbl_2_bss_1A824C[0x190000 + 0x7856] = arg0;
}

// .text:0x00093C64 size:0x9A0 mapped:0x806D2CF8
void fn_2_93C64(Mtx arg0) {
    u8 *self = (u8 *)lbl_2_bss_1A81D4;
    Mtx44 proj;
    Vec ang;
    Vec offset;
    Vec lookAt;
    s32 idx;

    idx = CAM[0x7849];
    if (CAM[0x7856] == 1) {
        memcpy(&ang, &lbl_2_data_38E0[idx].eye, sizeof(Vec));
        fn_2_68DE8(*(s16 *)&CAM[0x774A], &offset);
        PSVECAdd(&offset, &ang, &ang);
        memcpy(self + 0x4C, &ang, sizeof(Vec));
    } else {
        memcpy(&ang, &lbl_2_data_38E0[idx].eye, sizeof(Vec));
        memcpy(self + 0x4C, &ang, sizeof(Vec));
    }

    if (CAM[0x7848] == 0) {
        if (*(f32 *)(self + 0x4C) <= -10.0f) {
            *(f32 *)(self + 0x4C) = -10.0f;
        }
        if (*(f32 *)(self + 0x4C) >= 11.0f) {
            *(f32 *)(self + 0x4C) = 11.0f;
        }
        if (*(f32 *)(self + 0x54) <= -50.0f) {
            *(f32 *)(self + 0x54) = -50.0f;
        }
        if (*(f32 *)(self + 0x54) >= -22.0f) {
            *(f32 *)(self + 0x54) = -22.0f;
        }
        memcpy(&CAM[0x7650], self + 0x4C, sizeof(Vec));
    }
    memcpy(&CAM[0x7608], self + 0x4C, sizeof(Vec));

    CAM_F(0x7620) = CAM_F(0x7608);
    CAM_F(0x7624) = CAM_F(0x760C);
    CAM_F(0x7628) = CAM_F(0x7610);
    CAM_F(0x762C) = 0.00001f + CAM_F(0x7608);
    CAM_F(0x7630) = 0.00001f + CAM_F(0x760C);
    CAM_F(0x7634) = 0.00001f + CAM_F(0x7610);

    if (*(s16 *)&CAM[0x774A] != -1) {
        fn_2_68DE8(*(s16 *)&CAM[0x774A], &lookAt);
    } else {
        memcpy(&lookAt, &lbl_2_data_38E0[idx].target, sizeof(Vec));
    }
    memcpy(&CAM[0x765C], &lookAt, sizeof(Vec));

    if (CAM[0x7848] == 0) {
        if (lookAt.x <= -10.0f) {
            lookAt.x = -10.0f;
        } else if (lookAt.x >= 11.0f) {
            lookAt.x = 11.0f;
        } else {
            CAM_F(0x765C) = lookAt.x;
        }
        if (lookAt.z <= -24.0f) {
            lookAt.z = -24.0f;
        } else if (lookAt.z >= 8.0f) {
            lookAt.z = 8.0f;
        } else {
            CAM_F(0x7664) = lookAt.z;
        }
    }
    memcpy(&CAM[0x7614], &lookAt, sizeof(Vec));

    CAM_F(0x7638) = 0.00001f + CAM_F(0x7614);
    CAM_F(0x763C) = 0.00001f + CAM_F(0x7618);
    CAM_F(0x7640) = 0.00001f + CAM_F(0x761C);
    CAM_F(0x7644) = 0.00002f + CAM_F(0x7614);
    CAM_F(0x7648) = 0.00002f + CAM_F(0x7618);
    CAM_F(0x764C) = 0.00002f + CAM_F(0x761C);

    fn_2_927C8(arg0, &lookAt);
    memcpy(&CAM[0x7614], &lookAt, sizeof(Vec));
    fn_2_92CB0(arg0, &lookAt);

    memcpy(self + 0x4C, &CAM[0x7608], sizeof(Vec));
    memcpy(self + 0x40, &CAM[0x7614], sizeof(Vec));

    C_MTXFrustum(proj, -0.175f, 0.175f, 0.25f, -0.25f, 1.0f, 512.0f);
    GXSetProjection(proj, 0);

    fn_800B806C(0, -240.0f, 240.0f, -320.0f, 320.0f, -512.0f, -1.0f, 1280.0f);

    *(s32 *)(self + 0x58) = 0;
    *(f32 *)(self + 0x38) = 0.0f;
    *(s16 *)(self + 0x30) = lbl_2_data_38E0[idx].pitch;
    *(s16 *)(self + 0x32) = lbl_2_data_38E0[idx].yaw;
    *(f32 *)(self + 0x3C) = lbl_2_data_38E0[idx].fov;
}

// .text:0x00093BF8 size:0x6C mapped:0x806D2C8C
void fn_2_93BF8(Mtx arg0) {
    switch (lbl_2_bss_1A824C[0x190000 + 0x7845]) {
    case 0:
        fn_2_932DC(arg0);
        break;
    case 1:
        fn_2_92F2C(arg0);
        break;
    }
    fn_80011640(arg0, arg0);
}

// .text:0x000932DC size:0x91C mapped:0x806D2370
void fn_2_932DC(Mtx arg0) {
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

    idx = CAM[0x7849];
    *(u16 *)(self + 0x30) = lbl_2_data_38E0[idx].pitch;
    *(u16 *)(self + 0x32) = lbl_2_data_38E0[idx].yaw;
    *(f32 *)(self + 0x34) = 0.0f;
    *(f32 *)(self + 0x38) = 0.0f;

    ang.x = *(u16 *)(self + 0x30);
    ang.y = *(u16 *)(self + 0x32);
    ang.z = 0.0f;
    PSVECScale(&ang, 0.0000958738f, &ang);

    PSMTXRotRad(rotX, 'X', ang.x);
    PSMTXRotRad(rotY, 'Y', ang.y);
    sinY = rotY[0][2];
    cosY = rotY[0][0];
    PSMTXConcat(rotY, rotX, rot);
    PSMTXMultVec(rot, &fwd, (Vec *)(self + 0x40));

    *(f32 *)(self + 0x4C) += *(f32 *)(self + 0x38) * sinY - *(f32 *)(self + 0x34) * cosY;
    *(f32 *)(self + 0x54) += *(f32 *)(self + 0x38) * cosY + *(f32 *)(self + 0x34) * sinY;
    *(f32 *)(self + 0x40) += *(f32 *)(self + 0x4C);
    *(f32 *)(self + 0x44) += *(f32 *)(self + 0x50);
    *(f32 *)(self + 0x48) += *(f32 *)(self + 0x54);

    if (CAM[0x7856] == 1) {
        memcpy(&ang, &lbl_2_data_38E0[idx].eye, sizeof(Vec));
        fn_2_68DE8(*(s16 *)&CAM[0x774A], &offset);
        PSVECAdd(&offset, &ang, &ang);
        memcpy(self + 0x4C, &ang, sizeof(Vec));
    } else {
        memcpy(&ang, &lbl_2_data_38E0[idx].eye, sizeof(Vec));
        memcpy(self + 0x4C, &ang, sizeof(Vec));
    }

    if (CAM[0x7848] == 0) {
        if (*(f32 *)(self + 0x4C) <= -10.0f) {
            *(f32 *)(self + 0x4C) = -10.0f;
        }
        if (*(f32 *)(self + 0x4C) >= 11.0f) {
            *(f32 *)(self + 0x4C) = 11.0f;
        }
        if (*(f32 *)(self + 0x54) <= -50.0f) {
            *(f32 *)(self + 0x54) = -50.0f;
        }
        if (*(f32 *)(self + 0x54) >= -22.0f) {
            *(f32 *)(self + 0x54) = -22.0f;
        }
    }
    memcpy(&CAM[0x7608], self + 0x4C, sizeof(Vec));

    if (*(s16 *)&CAM[0x774A] != -1) {
        fn_2_68DE8(*(s16 *)&CAM[0x774A], &lookAt);
    } else {
        memcpy(&lookAt, &lbl_2_data_38E0[idx].target, sizeof(Vec));
    }

    if (CAM[0x7848] == 0) {
        if (lookAt.x <= -10.0f) {
            lookAt.x = -10.0f;
        } else if (lookAt.x >= 11.0f) {
            lookAt.x = 11.0f;
        } else {
            CAM_F(0x765C) = lookAt.x;
        }
        if (lookAt.z <= -24.0f) {
            lookAt.z = -24.0f;
        } else if (lookAt.z >= 8.0f) {
            lookAt.z = 8.0f;
        } else {
            CAM_F(0x7664) = lookAt.z;
        }
    }
    memcpy(&CAM[0x7614], &lookAt, sizeof(Vec));

    fn_2_927C8(arg0, &lookAt);
    memcpy(&CAM[0x7614], &lookAt, sizeof(Vec));
    fn_2_92CB0(arg0, &lookAt);

    memcpy(self + 0x4C, &CAM[0x7608], sizeof(Vec));
    memcpy(self + 0x40, &CAM[0x7614], sizeof(Vec));
    *(f32 *)(self + 0x3C) = lbl_2_data_38E0[idx].fov;

    makeLookAtMatrix(arg0, (Vec *)(self + 0x4C), &up, (Vec *)(self + 0x40));
}

// .text:0x00092F2C size:0x3B0 mapped:0x806D1FC0
void fn_2_92F2C(Mtx arg0) {
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
        *(u16 *)(self + 0x30) -= PAD_INPUTS[CAM_PORT].substickY;
        *(u16 *)(self + 0x32) += PAD_INPUTS[CAM_PORT].substickX;
        *(f32 *)(self + 0x34) = PAD_INPUTS[CAM_PORT].stickX / -256.0f;
        *(f32 *)(self + 0x38) = PAD_INPUTS[CAM_PORT].stickY / 256.0f;
        *(f32 *)(self + 0x50) += PAD_INPUTS[CAM_PORT].triggerR / 1024.0f;
        *(f32 *)(self + 0x50) -= PAD_INPUTS[CAM_PORT].triggerL / 1024.0f;
    }

    if (PAD_INPUTS[CAM_PORT].rep & INPUT_BUTTON_Y) {
        *(f32 *)(self + 0x3C) -= 0.01f;
    } else if (PAD_INPUTS[CAM_PORT].rep & INPUT_BUTTON_X) {
        *(f32 *)(self + 0x3C) += 0.01f;
    }

    ang.x = *(u16 *)(self + 0x30);
    ang.y = *(u16 *)(self + 0x32);
    ang.z = 0.0f;
    PSVECScale(&ang, 0.0000958738f, &ang);

    PSMTXRotRad(rotX, 'X', ang.x);
    PSMTXRotRad(rotY, 'Y', ang.y);
    sinY = rotY[0][2];
    cosY = rotY[0][0];
    PSMTXConcat(rotY, rotX, rot);
    PSMTXMultVec(rot, &fwd, (Vec *)(self + 0x40));

    *(f32 *)(self + 0x4C) += *(f32 *)(self + 0x38) * sinY - *(f32 *)(self + 0x34) * cosY;
    *(f32 *)(self + 0x54) += *(f32 *)(self + 0x38) * cosY + *(f32 *)(self + 0x34) * sinY;
    *(f32 *)(self + 0x40) += *(f32 *)(self + 0x4C);
    *(f32 *)(self + 0x44) += *(f32 *)(self + 0x50);
    *(f32 *)(self + 0x48) += *(f32 *)(self + 0x54);

    makeLookAtMatrix(arg0, (Vec *)(self + 0x4C), &up, (Vec *)(self + 0x40));
}


// .text:0x00092CB0 size:0x27C mapped:0x806D1D44
void fn_2_92CB0(void *arg0, Vec *arg1) {
    Vec result;
    Vec target;
    Vec pos;
    Vec prev;
    f32 x;
    f32 y;
    f32 z;

    if (CAM[0x7855] != 0) {
        x = CAM_F(0x7608);
        y = CAM_F(0x760C);
        z = CAM_F(0x7610);
        target.x = CAM_F(0x762C);
        target.y = CAM_F(0x7630);
        target.z = CAM_F(0x7634);
        pos.x = x;
        pos.y = y;
        pos.z = z;
        prev.x = CAM_F(0x7620);
        prev.y = CAM_F(0x7624);
        prev.z = CAM_F(0x7628);
        result = springStep(target, pos, prev, CAM_F(0x7668), CAM_F(0x766C), CAM_F(0x7670));
        CAM_F(0x7608) = result.x;
        CAM_F(0x760C) = result.y;
        CAM_F(0x7610) = result.z;
        CAM_F(0x762C) = result.x;
        CAM_F(0x7630) = result.y;
        CAM_F(0x7634) = result.z;
        CAM_F(0x7620) = x;
        CAM_F(0x7624) = y;
        CAM_F(0x7628) = z;
    }
}

// .text:0x00092A34 size:0x27C mapped:0x806D1AC8
void fn_2_92A34(void *arg0, Vec *arg1) {
    Vec result;
    Vec target;
    Vec pos;
    Vec prev;

    if (CAM[0x7855] != 0) {
        arg1->x = fn_2_4A18C(arg1->x);
        arg1->y = fn_2_4A18C(arg1->y);
        target.x = CAM_F(0x7644);
        target.y = CAM_F(0x7648);
        target.z = CAM_F(0x764C);
        pos.x = arg1->x;
        pos.y = arg1->y;
        pos.z = 0.0f;
        prev.x = CAM_F(0x7638);
        prev.y = CAM_F(0x763C);
        prev.z = CAM_F(0x7640);
        result = springStep(target, pos, prev, CAM_F(0x7674), CAM_F(0x7678), CAM_F(0x767C));
        CAM_F(0x7638) = arg1->x;
        CAM_F(0x763C) = arg1->y;
        CAM_F(0x7640) = 0.0f;
        CAM_F(0x7644) = result.x;
        CAM_F(0x7648) = result.y;
        CAM_F(0x764C) = result.z;
        arg1->x = result.x;
        arg1->y = result.y;
    }
}

// .text:0x000927C8 size:0x26C mapped:0x806D185C
void fn_2_927C8(void *arg0, Vec *arg1) {
    Vec result;
    Vec target;
    Vec pos;
    Vec prev;
    Vec in;

    if (CAM[0x7855] != 0) {
        memcpy(&in, arg1, sizeof(Vec));
        target.x = CAM_F(0x7644);
        target.y = CAM_F(0x7648);
        target.z = CAM_F(0x764C);
        memcpy(&pos, arg1, sizeof(Vec));
        prev.x = CAM_F(0x7638);
        prev.y = CAM_F(0x763C);
        prev.z = CAM_F(0x7640);
        result = springStep(target, pos, prev, CAM_F(0x7674), CAM_F(0x7678), CAM_F(0x767C));
        CAM_F(0x7638) = arg1->x;
        CAM_F(0x763C) = arg1->y;
        CAM_F(0x7640) = arg1->z;
        CAM_F(0x7644) = result.x;
        CAM_F(0x7648) = result.y;
        CAM_F(0x764C) = result.z;
        arg1->x = result.x;
        arg1->y = result.y;
        arg1->z = result.z;
    }
}
