#include "menus/rep_10C0.h"
#include "header_rep_data.h"
#include "stl/mem.h"
#include "Unknown/File_0x800b0724.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/GX/GXTransform.h"
#include "C3/control/frustum.h"

extern u8 *lbl_2_bss_1A824C;
extern f32 lbl_2_data_3BB0[][6];
extern f32 lbl_2_bss_1A81D4[];
extern Vec lbl_2_rodata_1128;
extern Vec lbl_2_rodata_1134;
extern f32 lbl_2_rodata_1140;
extern f32 lbl_2_rodata_1144;
extern f32 lbl_2_rodata_1148;
extern f32 lbl_2_rodata_114C;
extern f32 lbl_2_rodata_1150;
extern f32 lbl_2_rodata_1154;
extern f32 lbl_2_rodata_1188;
extern f32 lbl_2_rodata_118C;
extern f32 lbl_2_rodata_1190;
extern f32 lbl_2_rodata_1194;
extern f32 lbl_2_rodata_1198;
extern f32 lbl_2_rodata_119C;
extern f32 lbl_2_rodata_11A0;
extern f32 lbl_2_rodata_11A4;
extern f32 lbl_2_rodata_11A8;
extern f32 lbl_2_rodata_11AC;
extern f32 lbl_2_rodata_11B0;
extern f32 lbl_2_rodata_11B4;
extern f32 lbl_2_rodata_11B8;
extern f32 lbl_2_rodata_1168;
extern f32 lbl_2_rodata_116C;
extern f32 lbl_2_rodata_1170;
extern f32 lbl_2_rodata_1174;
extern f32 lbl_2_rodata_1178;
extern f32 lbl_2_rodata_117C;
extern f32 lbl_2_rodata_1180;
extern f32 lbl_2_rodata_1184;
extern Vec lbl_2_rodata_1110;
extern Vec lbl_2_rodata_111C;
extern u8 lbl_2_data_38E0[];
extern f32 fn_2_4A18C(f32 arg0);
void fn_2_68DE8(s32 idx, void *dst);
extern void fn_80011640(void *arg0, void *arg1);

// .text:0x000946DC size:0x178 mapped:0x806D3770
void fn_2_946DC(s32 arg0) {
    f32 *entry = lbl_2_data_3BB0[arg0];
    f32 *arr = lbl_2_bss_1A81D4;
    f32 scaleB = lbl_2_rodata_1184;
    f32 scaleA = lbl_2_rodata_1180;

    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7668] = entry[0];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x766C] = entry[1];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7670] = entry[2];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7674] = entry[3];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7678] = entry[4];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x767C] = entry[5];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7620] = arr[19];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7624] = arr[20];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7628] = arr[21];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x762C] = scaleA + arr[19];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7630] = scaleA + arr[20];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7634] = scaleA + arr[21];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7638] = scaleA + arr[16];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x763C] = scaleA + arr[17];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7640] = scaleA + arr[18];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7644] = scaleB + arr[16];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7648] = scaleB + arr[17];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x764C] = scaleB + arr[18];
}

// .text:0x00094634 size:0xA8 mapped:0x806D36C8
void fn_2_94634(s32 arg0) {
    f32 *entry = lbl_2_data_3BB0[arg0];

    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7668] = entry[0];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x766C] = entry[1];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7670] = entry[2];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7674] = entry[3];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7678] = entry[4];
    *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x767C] = entry[5];
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
    u8 *self = (u8 *)arg0;
    u8 *ent;
    u8 *bss;
    Mtx44 proj;
    Vec up;
    Vec ang;
    Vec entryPos;
    Vec pos;
    Vec prev;
    Vec target;
    Vec toTarget;
    Vec scaledPrev;
    Vec prevDir;
    f32 dist;
    f32 dot;
    f32 ratio;
    f32 mag;
    s32 idx;

    bss = lbl_2_bss_1A824C + 0x190000;
    idx = bss[0x7849];
    ent = lbl_2_data_38E0 + idx * 0x24;

    if (bss[0x7856] == 1) {
        memcpy(&ang, ent, sizeof(Vec));
        fn_2_68DE8(*(s16 *)&bss[0x774A], &entryPos);
        PSVECAdd(&entryPos, &ang, &ang);
        memcpy(self + 0x4C, &ang, sizeof(Vec));
    } else {
        memcpy(&ang, ent, sizeof(Vec));
        memcpy(self + 0x4C, &ang, sizeof(Vec));
    }

    if (bss[0x7848] == 0) {
        if (*(f32 *)(self + 0x4C) <= lbl_2_rodata_1168) {
            *(f32 *)(self + 0x4C) = lbl_2_rodata_1168;
        }
        if (*(f32 *)(self + 0x4C) >= lbl_2_rodata_116C) {
            *(f32 *)(self + 0x4C) = lbl_2_rodata_116C;
        }
        if (*(f32 *)(self + 0x54) <= lbl_2_rodata_1170) {
            *(f32 *)(self + 0x54) = lbl_2_rodata_1170;
        }
        if (*(f32 *)(self + 0x54) >= lbl_2_rodata_1174) {
            *(f32 *)(self + 0x54) = lbl_2_rodata_1174;
        }
    }

    memcpy(bss + 0x7650, self + 0x4C, sizeof(Vec));
    memcpy(bss + 0x7608, self + 0x4C, sizeof(Vec));

    *(f32 *)&bss[0x7620] = *(f32 *)&bss[0x7608];
    *(f32 *)&bss[0x7624] = *(f32 *)&bss[0x760C];
    *(f32 *)&bss[0x7628] = *(f32 *)&bss[0x7610];
    *(f32 *)&bss[0x762C] = lbl_2_rodata_1180 + *(f32 *)&bss[0x7608];
    *(f32 *)&bss[0x7630] = lbl_2_rodata_1180 + *(f32 *)&bss[0x760C];
    *(f32 *)&bss[0x7634] = lbl_2_rodata_1180 + *(f32 *)&bss[0x7610];

    if (*(s16 *)&bss[0x774A] != -1) {
        fn_2_68DE8(*(s16 *)&bss[0x774A], &entryPos);
    } else {
        memcpy(&entryPos, ent + 0xC, sizeof(Vec));
    }

    memcpy(bss + 0x765C, &entryPos, sizeof(Vec));
    if (bss[0x7848] == 0) {
        if (entryPos.x <= lbl_2_rodata_1168) {
            entryPos.x = lbl_2_rodata_1168;
        }
        if (entryPos.x >= lbl_2_rodata_116C) {
            entryPos.x = lbl_2_rodata_116C;
        }
        if (entryPos.z <= lbl_2_rodata_1178) {
            entryPos.z = lbl_2_rodata_1178;
        }
        if (entryPos.z >= lbl_2_rodata_117C) {
            entryPos.z = lbl_2_rodata_117C;
        }
        *(f32 *)&bss[0x765C] = entryPos.x;
        *(f32 *)&bss[0x7664] = entryPos.z;
    }
    memcpy(bss + 0x7614, &entryPos, sizeof(Vec));

    *(f32 *)&bss[0x7638] = lbl_2_rodata_1180 + *(f32 *)&bss[0x7614];
    *(f32 *)&bss[0x763C] = lbl_2_rodata_1180 + *(f32 *)&bss[0x7618];
    *(f32 *)&bss[0x7640] = lbl_2_rodata_1180 + *(f32 *)&bss[0x761C];
    *(f32 *)&bss[0x7644] = lbl_2_rodata_1184 + *(f32 *)&bss[0x7614];
    *(f32 *)&bss[0x7648] = lbl_2_rodata_1184 + *(f32 *)&bss[0x7618];
    *(f32 *)&bss[0x764C] = lbl_2_rodata_1184 + *(f32 *)&bss[0x761C];

    if (bss[0x7855] != 0) {
        pos = entryPos;
        prev = *(Vec *)&bss[0x7638];
        target = *(Vec *)&bss[0x7644];

        PSVECSubtract(&target, &pos, &toTarget);
        dist = PSVECDistance(&target, &pos);
        PSVECSubtract(&prev, &pos, &prevDir);
        PSVECScale(&prevDir, lbl_2_rodata_1140, &scaledPrev);
        dot = PSVECDotProduct(&scaledPrev, &toTarget);
        ratio = dot / dist;
        mag = *(f32 *)&bss[0x7674] * (*(f32 *)&bss[0x767C] - dist) + *(f32 *)&bss[0x7678] * ratio;
        PSVECNormalize(&toTarget, &toTarget);
        PSVECScale(&toTarget, mag * lbl_2_rodata_1140, &toTarget);
        PSVECAdd(&target, &toTarget, &target);

        *(Vec *)&bss[0x7638] = pos;
        *(Vec *)&bss[0x7644] = target;
        entryPos = target;
    }

    if (bss[0x7855] != 0) {
        pos = *(Vec *)&bss[0x7608];
        prev = *(Vec *)&bss[0x7620];
        target = *(Vec *)&bss[0x762C];

        PSVECSubtract(&target, &pos, &toTarget);
        dist = PSVECDistance(&target, &pos);
        PSVECSubtract(&prev, &pos, &prevDir);
        PSVECScale(&prevDir, lbl_2_rodata_1140, &scaledPrev);
        dot = PSVECDotProduct(&scaledPrev, &toTarget);
        ratio = dot / dist;
        mag = *(f32 *)&bss[0x7668] * (*(f32 *)&bss[0x7670] - dist) + *(f32 *)&bss[0x766C] * ratio;
        PSVECNormalize(&toTarget, &toTarget);
        PSVECScale(&toTarget, mag * lbl_2_rodata_1140, &toTarget);
        PSVECAdd(&target, &toTarget, &target);

        *(Vec *)&bss[0x7620] = pos;
        *(Vec *)&bss[0x7608] = target;
        *(Vec *)&bss[0x762C] = target;
    }

    memcpy(self + 0x4C, bss + 0x7608, sizeof(Vec));
    memcpy(self + 0x40, bss + 0x7614, sizeof(Vec));

    C_MTXFrustum(proj, lbl_2_rodata_1188, lbl_2_rodata_118C, lbl_2_rodata_1190, lbl_2_rodata_1194,
                 lbl_2_rodata_1198, lbl_2_rodata_119C);
    GXSetProjection(proj, 0);

    fn_800B806C(0, lbl_2_rodata_11A0, lbl_2_rodata_11A4, lbl_2_rodata_11A8, lbl_2_rodata_11AC,
                lbl_2_rodata_11B0, lbl_2_rodata_11B4, lbl_2_rodata_11B8);

    *(s16 *)(self + 0x30) = (s16)*(f32 *)(ent + 0x18);
    *(s16 *)(self + 0x32) = (s16)*(f32 *)(ent + 0x1C);
    *(f32 *)(self + 0x38) = lbl_2_rodata_1144;
    *(s32 *)(self + 0x58) = 0;
    *(f32 *)(self + 0x3C) = *(f32 *)(ent + 0x20);
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
    u8 *ent;
    u8 *bss;
    Vec up;
    Vec fwd;
    Vec ang;
    Vec entryPos;
    Vec pos;
    Vec prev;
    Vec target;
    Vec toTarget;
    Vec scaledPrev;
    Vec prevDir;
    Mtx rot;
    Mtx rotY;
    Mtx rotX;
    f32 dist;
    f32 dot;
    f32 ratio;
    f32 mag;
    f32 cosY;
    f32 sinY;
    s32 idx;

    up = lbl_2_rodata_1110;
    fwd = lbl_2_rodata_111C;
    bss = (u8 *)lbl_2_bss_1A824C + 0x190000;

    idx = bss[0x7849];
    ent = lbl_2_data_38E0 + idx * 0x24;

    *(s16 *)(self + 0x30) = (s16)*(f32 *)(ent + 0x18);
    *(s16 *)(self + 0x32) = (s16)*(f32 *)(ent + 0x1C);
    *(f32 *)(self + 0x34) = lbl_2_rodata_1144;
    *(f32 *)(self + 0x38) = lbl_2_rodata_1144;

    ang.x = (f32)*(u16 *)(self + 0x30);
    ang.y = (f32)*(u16 *)(self + 0x32);
    ang.z = lbl_2_rodata_1144;
    PSVECScale(&ang, lbl_2_rodata_1154, &ang);

    PSMTXRotRad(rotX, 'X', ang.x);
    PSMTXRotRad(rotY, 'Y', ang.y);
    PSMTXConcat(rotY, rotX, rot);
    PSMTXMultVec(rot, &fwd, (Vec *)(self + 0x40));

    cosY = rotY[0][0];
    sinY = rotY[0][2];
    *(f32 *)(self + 0x4C) += *(f32 *)(self + 0x38) * sinY - *(f32 *)(self + 0x34) * cosY;
    *(f32 *)(self + 0x54) += *(f32 *)(self + 0x34) * sinY + *(f32 *)(self + 0x38) * cosY;
    *(f32 *)(self + 0x40) += *(f32 *)(self + 0x4C);
    *(f32 *)(self + 0x44) += *(f32 *)(self + 0x50);
    *(f32 *)(self + 0x48) += *(f32 *)(self + 0x54);

    if (lbl_2_bss_1A824C[0x190000 + 0x7856] == 1) {
        memcpy(&ang, ent, sizeof(Vec));
        fn_2_68DE8(*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x774A], &entryPos);
        PSVECAdd(&entryPos, &ang, &ang);
        memcpy(self + 0x4C, &ang, sizeof(Vec));
    } else {
        memcpy(&ang, ent, sizeof(Vec));
        memcpy(self + 0x4C, &ang, sizeof(Vec));
    }

    if (lbl_2_bss_1A824C[0x190000 + 0x7848] == 0) {
        if (*(f32 *)(self + 0x4C) <= lbl_2_rodata_1168) {
            *(f32 *)(self + 0x4C) = lbl_2_rodata_1168;
        }
        if (*(f32 *)(self + 0x4C) >= lbl_2_rodata_116C) {
            *(f32 *)(self + 0x4C) = lbl_2_rodata_116C;
        }
        if (*(f32 *)(self + 0x54) <= lbl_2_rodata_1170) {
            *(f32 *)(self + 0x54) = lbl_2_rodata_1170;
        }
        if (*(f32 *)(self + 0x54) >= lbl_2_rodata_1174) {
            *(f32 *)(self + 0x54) = lbl_2_rodata_1174;
        }
    }

    memcpy(bss + 0x7608, self + 0x4C, sizeof(Vec));

    if (*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x774A] != -1) {
        fn_2_68DE8(*(s16 *)&lbl_2_bss_1A824C[0x190000 + 0x774A], &entryPos);
    } else {
        memcpy(&entryPos, ent + 0xC, sizeof(Vec));
    }

    if (lbl_2_bss_1A824C[0x190000 + 0x7848] == 0) {
        if (entryPos.x <= lbl_2_rodata_1168) {
            entryPos.x = lbl_2_rodata_1168;
        }
        if (entryPos.x >= lbl_2_rodata_116C) {
            entryPos.x = lbl_2_rodata_116C;
        }
        if (entryPos.z <= lbl_2_rodata_1178) {
            entryPos.z = lbl_2_rodata_1178;
        }
        if (entryPos.z >= lbl_2_rodata_117C) {
            entryPos.z = lbl_2_rodata_117C;
        }
        *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x765C] = entryPos.x;
        *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7664] = entryPos.z;
    }
    memcpy(bss + 0x7614, &entryPos, sizeof(Vec));

    if (lbl_2_bss_1A824C[0x190000 + 0x7855] != 0) {
        pos = entryPos;
        prev = *(Vec *)&lbl_2_bss_1A824C[0x190000 + 0x7638];
        target = *(Vec *)&lbl_2_bss_1A824C[0x190000 + 0x7644];

        PSVECSubtract(&target, &pos, &toTarget);
        dist = PSVECDistance(&target, &pos);
        PSVECSubtract(&prev, &pos, &prevDir);
        PSVECScale(&prevDir, lbl_2_rodata_1140, &scaledPrev);
        dot = PSVECDotProduct(&scaledPrev, &toTarget);
        ratio = dot / dist;
        mag = *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7674] * (*(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x767C] - dist) +
              *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7678] * ratio;
        PSVECNormalize(&toTarget, &toTarget);
        PSVECScale(&toTarget, mag * lbl_2_rodata_1140, &toTarget);
        PSVECAdd(&target, &toTarget, &target);

        *(Vec *)&lbl_2_bss_1A824C[0x190000 + 0x7638] = pos;
        *(Vec *)&lbl_2_bss_1A824C[0x190000 + 0x7644] = target;
        entryPos = target;
    }

    if (lbl_2_bss_1A824C[0x190000 + 0x7855] != 0) {
        pos = *(Vec *)&lbl_2_bss_1A824C[0x190000 + 0x7608];
        prev = *(Vec *)&lbl_2_bss_1A824C[0x190000 + 0x7620];
        target = *(Vec *)&lbl_2_bss_1A824C[0x190000 + 0x762C];

        PSVECSubtract(&target, &pos, &toTarget);
        dist = PSVECDistance(&target, &pos);
        PSVECSubtract(&prev, &pos, &prevDir);
        PSVECScale(&prevDir, lbl_2_rodata_1140, &scaledPrev);
        dot = PSVECDotProduct(&scaledPrev, &toTarget);
        ratio = dot / dist;
        mag = *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7668] * (*(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7670] - dist) +
              *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x766C] * ratio;
        PSVECNormalize(&toTarget, &toTarget);
        PSVECScale(&toTarget, mag * lbl_2_rodata_1140, &toTarget);
        PSVECAdd(&target, &toTarget, &target);

        *(Vec *)&lbl_2_bss_1A824C[0x190000 + 0x7620] = pos;
        *(Vec *)&lbl_2_bss_1A824C[0x190000 + 0x7608] = target;
        *(Vec *)&lbl_2_bss_1A824C[0x190000 + 0x762C] = target;
    }

    memcpy(self + 0x4C, bss + 0x7608, sizeof(Vec));
    memcpy(self + 0x40, bss + 0x7614, sizeof(Vec));
    *(f32 *)(self + 0x3C) = *(f32 *)(ent + 0x20);

    makeLookAtMatrix(arg0, (Vec *)(self + 0x4C), &up, (Vec *)(self + 0x40));
}

// .text:0x00092F2C size:0x3B0 mapped:0x806D1FC0
void fn_2_92F2C(Mtx arg0) {
    u8 *self = (u8 *)arg0;
    u8 *ent;
    u16 buttons;
    Vec up = lbl_2_rodata_1128;
    Vec fwd = lbl_2_rodata_1134;
    Vec ang;
    Mtx rot;
    Mtx rotY;
    Mtx rotX;
    f32 cosY;
    f32 sinY;

    ent = (u8 *)&AtBat_ButtonInput1 + (s8)lbl_2_bss_1A824C[0x190000 + 0x7863] * 0x20;

    if ((*(u16 *)ent & 0x10) == 0) {
        *(u16 *)(self + 0x30) -= (s8)ent[0x13];
        *(u16 *)(self + 0x32) += (s8)ent[0x12];
        *(f32 *)(self + 0x34) = (s8)ent[0x10] / lbl_2_rodata_1148;
        *(f32 *)(self + 0x38) = (s8)ent[0x11] * lbl_2_rodata_114C;
        *(f32 *)(self + 0x50) += (u8)ent[0x15] * lbl_2_rodata_1150;
        *(f32 *)(self + 0x50) -= (u8)ent[0x14] * lbl_2_rodata_1150;
    }

    buttons = *(u16 *)(ent + 4);
    if (buttons & 0x800) {
        *(f32 *)(self + 0x3C) -= lbl_2_rodata_1140;
    } else if (buttons & 0x400) {
        *(f32 *)(self + 0x3C) += lbl_2_rodata_1140;
    }

    ang.x = *(u16 *)(self + 0x30);
    ang.y = *(u16 *)(self + 0x32);
    ang.z = lbl_2_rodata_1144;
    PSVECScale(&ang, lbl_2_rodata_1154, &ang);

    PSMTXRotRad(rotX, 'X', ang.x);
    PSMTXRotRad(rotY, 'Y', ang.y);
    PSMTXConcat(rotX, rotY, rot);
    PSMTXMultVec(rot, &fwd, (Vec *)(self + 0x40));

    cosY = rotY[0][0];
    sinY = rotY[0][2];
    *(f32 *)(self + 0x4C) += *(f32 *)(self + 0x38) * sinY - *(f32 *)(self + 0x34) * cosY;
    *(f32 *)(self + 0x54) += *(f32 *)(self + 0x34) * sinY + *(f32 *)(self + 0x38) * cosY;
    *(f32 *)(self + 0x40) += *(f32 *)(self + 0x4C);
    *(f32 *)(self + 0x44) += *(f32 *)(self + 0x50);
    *(f32 *)(self + 0x48) += *(f32 *)(self + 0x54);

    makeLookAtMatrix(arg0, (Vec *)(self + 0x4C), &up, (Vec *)(self + 0x40));
}

// .text:0x00092CB0 size:0x27C mapped:0x806D1D44
void fn_2_92CB0(void *arg0, Vec *arg1) {
    Vec pos;
    Vec prev;
    Vec target;
    Vec toTarget;
    Vec scaledPrev;
    Vec prevDir;
    f32 dist;
    f32 dot;
    f32 ratio;
    f32 mag;

    if (lbl_2_bss_1A824C[0x190000 + 0x7855] != 0) {
        pos = *(Vec *)&lbl_2_bss_1A824C[0x190000 + 0x7608];
        prev = *(Vec *)&lbl_2_bss_1A824C[0x190000 + 0x7620];
        target = *(Vec *)&lbl_2_bss_1A824C[0x190000 + 0x762C];

        PSVECSubtract(&target, &pos, &toTarget);
        dist = PSVECDistance(&target, &pos);
        PSVECSubtract(&prev, &pos, &prevDir);
        PSVECScale(&prevDir, lbl_2_rodata_1140, &scaledPrev);
        dot = PSVECDotProduct(&scaledPrev, &toTarget);
        ratio = dot / dist;
        mag = *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7668] * (*(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7670] - dist) +
              *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x766C] * ratio;

        PSVECNormalize(&toTarget, &toTarget);
        PSVECScale(&toTarget, mag * lbl_2_rodata_1140, &toTarget);
        PSVECAdd(&target, &toTarget, &target);

        *(Vec *)&lbl_2_bss_1A824C[0x190000 + 0x7620] = pos;
        *(Vec *)&lbl_2_bss_1A824C[0x190000 + 0x7608] = target;
        *(Vec *)&lbl_2_bss_1A824C[0x190000 + 0x762C] = target;
    }
}

// .text:0x00092A34 size:0x27C mapped:0x806D1AC8
void fn_2_92A34(void *arg0, Vec *arg1) {
    Vec pos;
    Vec prev;
    Vec target;
    Vec toTarget;
    Vec scaledPrev;
    Vec prevDir;
    f32 dist;
    f32 dot;
    f32 ratio;
    f32 mag;

    if (lbl_2_bss_1A824C[0x190000 + 0x7855] != 0) {
        arg1->x = fn_2_4A18C(arg1->x);
        arg1->y = fn_2_4A18C(arg1->y);

        pos.x = arg1->x;
        pos.y = arg1->y;
        pos.z = lbl_2_rodata_1144;
        prev = *(Vec *)&lbl_2_bss_1A824C[0x190000 + 0x7638];
        target = *(Vec *)&lbl_2_bss_1A824C[0x190000 + 0x7644];

        PSVECSubtract(&target, &pos, &toTarget);
        dist = PSVECDistance(&target, &pos);
        PSVECSubtract(&prev, &pos, &prevDir);
        PSVECScale(&prevDir, lbl_2_rodata_1140, &scaledPrev);
        dot = PSVECDotProduct(&scaledPrev, &toTarget);
        ratio = dot / dist;
        mag = *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7674] * (*(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x767C] - dist) +
              *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7678] * ratio;

        PSVECNormalize(&toTarget, &toTarget);
        PSVECScale(&toTarget, mag * lbl_2_rodata_1140, &toTarget);
        PSVECAdd(&target, &toTarget, &target);

        *(Vec *)&lbl_2_bss_1A824C[0x190000 + 0x7638] = pos;
        *(Vec *)&lbl_2_bss_1A824C[0x190000 + 0x7644] = target;
        arg1->x = target.x;
        arg1->y = target.y;
    }
}

// .text:0x000927C8 size:0x26C mapped:0x806D185C
void fn_2_927C8(void *arg0, Vec *arg1) {
    Vec pos;
    Vec prev;
    Vec target;
    Vec toTarget;
    Vec scaledPrev;
    Vec prevDir;
    f32 dist;
    f32 dot;
    f32 ratio;
    f32 mag;

    if (lbl_2_bss_1A824C[0x190000 + 0x7855] != 0) {
        memcpy(&pos, arg1, sizeof(Vec));
        prev = *(Vec *)&lbl_2_bss_1A824C[0x190000 + 0x7638];
        target = *(Vec *)&lbl_2_bss_1A824C[0x190000 + 0x7644];

        PSVECSubtract(&target, &pos, &toTarget);
        dist = PSVECDistance(&target, &pos);
        PSVECSubtract(&prev, &pos, &prevDir);
        PSVECScale(&prevDir, lbl_2_rodata_1140, &scaledPrev);
        dot = PSVECDotProduct(&scaledPrev, &toTarget);
        ratio = dot / dist;
        mag = *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7674] * (*(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x767C] - dist) +
              *(f32 *)&lbl_2_bss_1A824C[0x190000 + 0x7678] * ratio;

        PSVECNormalize(&toTarget, &toTarget);
        PSVECScale(&toTarget, mag * lbl_2_rodata_1140, &toTarget);
        PSVECAdd(&target, &toTarget, &target);

        *(Vec *)&lbl_2_bss_1A824C[0x190000 + 0x7638] = *arg1;
        *(Vec *)&lbl_2_bss_1A824C[0x190000 + 0x7644] = target;
        *arg1 = target;
    }
}
