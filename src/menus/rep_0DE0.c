#include "menus/rep_0DE0.h"
#include "header_rep_data.h"
#include "C3/light/light.h"
#include "C3/control.h"
#include "C3/control/frustum.h"
#include "Dolphin/GX/GXTransform.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/File_0x800bd478.h"
#include "Unknown/File_0x800bda94.h"
#include "Unknown/File_0x800bdd74.h"
#include "Unknown/File_0x800bdc88.h"
#include "Unknown/File_0x800b0724.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "PowerPC_EABI_Support/Runtime/__mem.h"

void fn_800A7D4C(u32 a, void *b);

// .text:0x0008563C size:0x268 mapped:0x806C46D0
void fn_2_8563C(Rep0DEMtxBlock *self) {
    Mtx m1;
    Mtx m2;
    Mtx m3;
    Vec ang;
    Vec fwd;
    Vec up;
    f32 sinY;
    f32 cosY;
    f32 *row = lbl_2_data_2E944 + lbl_2_bss_33FBF5 * 6;

    self->unk30 = -0x3E61;
    self->unk32 = 0;
    self->unk34 = 0.0f;
    self->unk38 = 0.0f;

    ang.x = (f32)(u16)self->unk30;
    ang.y = (f32)(u16)self->unk32;
    ang.z = 0.0f;
    PSVECScale(&ang, 9.58738e-5f, &ang);
    PSMTXRotRad(m1, 'X', ang.x);
    PSMTXRotRad(m2, 'Y', ang.y);
    cosY = m2[0][0];
    sinY = m2[0][2];
    PSMTXConcat(m2, m1, m3);

    fwd.x = 0.0f;
    fwd.y = 0.0f;
    fwd.z = 1.0f;
    PSMTXMultVec(m3, &fwd, &self->unk3C);

    self->unk48.x += self->unk38 * sinY - self->unk34 * cosY;
    self->unk48.z += self->unk34 * sinY + self->unk38 * cosY;
    self->unk3C.x += self->unk48.x;
    self->unk3C.y += self->unk48.y;
    self->unk3C.z += self->unk48.z;

    self->unk48.x = row[0];
    self->unk48.y = row[1];
    self->unk48.z = row[2];
    self->unk3C.x = row[3];
    self->unk3C.y = row[4];
    self->unk3C.z = row[5];

    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    makeLookAtMatrix(self->mtx, &self->unk48, &up, &self->unk3C);
}

// .text:0x000858A4 size:0x21C mapped:0x806C4938
void fn_2_858A4(Rep0DEMtxBlock *self) {
    Mtx m1;
    Mtx m2;
    Mtx m3;
    Vec ang;
    Vec pos;
    Vec up;
    u8 *raw = (u8 *)&AtBat_ButtonInput1;

    if ((AtBat_ButtonInput1._00 & INPUT_TRIGGER_Z) == 0) {
        self->unk30 -= (s8)raw[0x13];
        self->unk32 += (s8)raw[0x12];
        self->unk38 += (s8)raw[0x11] * 0.00390625f;
        self->unk3C.y += (u8)raw[0x15] * 0.0009765625f;
        self->unk3C.y -= (u8)raw[0x14] * 0.0009765625f;
    }

    ang.x = (f32)(u16)self->unk30;
    ang.y = (f32)(u16)self->unk32;
    ang.z = 0.0f;
    PSVECScale(&ang, 9.58738e-5f, &ang);
    PSMTXRotRad(m1, 'X', ang.x);
    PSMTXRotRad(m2, 'Y', ang.y);
    PSMTXConcat(m1, m2, m3);

    pos.x = 0.0f;
    pos.y = 0.0f;
    pos.z = -self->unk38;
    PSMTXMultVec(m3, &pos, &pos);
    PSVECAdd(&pos, &self->unk3C, &self->unk48);

    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    PSMTXMultVec(m3, &up, &pos);
    makeLookAtMatrix(self->mtx, &self->unk48, &pos, &self->unk3C);
}

// .text:0x00085AC0 size:0x2AC mapped:0x806C4B54
void fn_2_85AC0(Rep0DEMtxBlock *self) {
    Mtx m1;
    Mtx m2;
    Mtx m3;
    Vec ang;
    Vec fwd;
    Vec up;
    f32 sinY;
    f32 cosY;
    u8 *raw = (u8 *)&AtBat_ButtonInput1;

    if ((AtBat_ButtonInput1._00 & INPUT_TRIGGER_Z) == 0) {
        self->unk30 -= (s8)raw[0x13];
        self->unk32 += (s8)raw[0x12];
        self->unk34 = (s8)raw[0x10] / -256.0f;
        self->unk38 = (s8)raw[0x11] * 0.00390625f;
        self->unk48.y += (u8)raw[0x15] * 0.0009765625f;
        self->unk48.y -= (u8)raw[0x14] * 0.0009765625f;
    }

    ang.x = (f32)(u16)self->unk30;
    ang.y = (f32)(u16)self->unk32;
    ang.z = 0.0f;
    PSVECScale(&ang, 9.58738e-5f, &ang);
    PSMTXRotRad(m1, 'X', ang.x);
    PSMTXRotRad(m2, 'Y', ang.y);
    cosY = m2[0][0];
    sinY = m2[0][2];
    PSMTXConcat(m2, m1, m3);

    fwd.x = 0.0f;
    fwd.y = 0.0f;
    fwd.z = 1.0f;
    PSMTXMultVec(m3, &fwd, &self->unk3C);

    self->unk48.x += self->unk38 * sinY - self->unk34 * cosY;
    self->unk48.z += self->unk34 * sinY + self->unk38 * cosY;
    self->unk3C.x += self->unk48.x;
    self->unk3C.y += self->unk48.y;
    self->unk3C.z += self->unk48.z;

    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    makeLookAtMatrix(self->mtx, &self->unk48, &up, &self->unk3C);
}

// .text:0x00085D6C size:0x704 mapped:0x806C4E00
#pragma dont_inline on
void fn_2_85D6C(Rep0DEMtxBlock *self) {
    switch (lbl_2_bss_B2A5) {
    case 0:
        fn_2_8563C(self);
        break;
    case 1:
        fn_2_85AC0(self);
        break;
    case 2:
        fn_2_858A4(self);
        break;
    }
}
#pragma dont_inline reset

// .text:0x00086470 size:0x458 mapped:0x806C5504
void fn_2_86470(void) {
    s32 i;
    s32 elemOff = 0;
    s32 recOff = 0;

    for (i = 0; i < lbl_2_bss_340140->unk3078; i++) {
        Rep0DERec28 *rec = (Rep0DERec28 *)((u8 *)lbl_2_bss_340140->unk2D94 + recOff);
        Control *ctrl = (Control *)((u8 *)lbl_2_bss_340140->unk68 + elemOff + 0x44);
        Vec pos;
        Vec delta;
        f32 oldX;
        f32 oldY;
        f32 oldZ;
        s8 row;

        memcpy(&pos, &rec->pos, sizeof(Vec));
        PSVECSubtract(&pos, &lbl_2_data_2E9E8, &delta);
        delta.x = delta.x * -1.0f;
        delta.z = delta.z * -1.0f;
        if (delta.x != 0.0f || delta.z != 0.0f) {
            lbl_2_bss_B2A0 = fn_2_4A1E8(delta.z);
        }
        memcpy(&lbl_2_data_2E9E8, &rec->pos, sizeof(Vec));
        oldX = pos.x;
        oldY = pos.y;
        oldZ = pos.z;

        rec->unk10 = lbl_2_data_2E9DC[0];
        rec->unk14 = lbl_2_data_2E9DC[1];
        rec->unk18 = lbl_2_data_2E9DC[2];

        row = lbl_2_bss_33FBF5;
        if (row == 0) {
            CTRLSetTranslation(ctrl, oldX + (i % 5) * 0.79f, oldY, oldZ - (i / 5) * 0.614f);
        } else if (row == 1) {
            CTRLSetTranslation(ctrl, oldX + (i % 6) * 0.75f, oldY, oldZ - (i / 6) * 0.69f);
        } else if (row == 2) {
            CTRLSetTranslation(ctrl, oldX + (i % 5) * 0.89f, oldY, oldZ - (i / 5) * 0.544f);
        } else {
            CTRLSetTranslation(ctrl, oldX + (i % 6) * 0.742f, oldY, oldZ - (i / 6) * 0.542f);
        }

        CTRLSetRotation(ctrl, 0.79f * lbl_2_data_2E9DC[0], 0.79f * lbl_2_data_2E9DC[1],
                        0.79f * lbl_2_data_2E9DC[2]);
        ((u8 *)lbl_2_bss_340140->unk68)[elemOff + 0xA0] = lbl_2_bss_33FBF0[i];

        recOff += 0x28;
        elemOff += 0x90;
    }
}

// .text:0x000868C8 size:0xEC mapped:0x806C595C
void fn_2_868C8(void) {
    Vec prev;
    Vec delta;
    Rep0DERec28 *rec = lbl_2_bss_340140->unk2D94;

    memcpy(&prev, &rec->pos, sizeof(Vec));
    PSVECSubtract(&prev, &lbl_2_data_2E9D0, &delta);
    delta.x = delta.x * -1.0f;
    delta.z = delta.z * -1.0f;
    if (delta.x != 0.0f || delta.z != 0.0f) {
        lbl_2_bss_B29C = fn_2_4A1E8(delta.z);
    }
    memcpy(&lbl_2_data_2E9D0, &rec->pos, sizeof(Vec));
    rec->pos.x = prev.x;
    rec->pos.y = prev.y;
    rec->pos.z = prev.z;
    rec->unk10 = lbl_2_data_2E9C4[0];
    rec->unk14 = lbl_2_bss_B29C;
    rec->unk18 = lbl_2_data_2E9C4[2];
}

// .text:0x000869B4 size:0x58 mapped:0x806C5A48
void fn_2_869B4(void) {
    s32 i;
    s32 off = 0;

    for (i = 0; i < lbl_2_bss_340140->unk3078; i++) {
        Rep0DERec28 *rec = (Rep0DERec28 *)((u8 *)lbl_2_bss_340140->unk2D94 + off);
        rec->pos.x = 0.0f;
        rec->pos.y = 0.0f;
        rec->pos.z = 0.0f;
        rec->unk10 = 0.0f;
        rec->unk14 = 0.0f;
        rec->unk18 = 0.0f;
        off += 0x28;
    }
}

// .text:0x00086A0C size:0x74 mapped:0x806C5AA0
void fn_2_86A0C(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        camera_803c639c_s *cam = fn_80052768_getCamera(0);
        LITXForm(lbl_2_bss_340140->unkAC[i], cam->view);
    }
}

// .text:0x00086A80 size:0x34C mapped:0x806C5B14
void fn_2_86A80(void) {
    u32 white = 0xFFFFFFFF;
    u32 blue = 0x0000FFFF;
    u32 red = 0xFF0000FF;

    LITAlloc(&lbl_2_bss_340140->unkAC[0]);
    LITAlloc(&lbl_2_bss_340140->unkAC[1]);
    LITAlloc(&lbl_2_bss_340140->unkAC[2]);
    LITAlloc(&lbl_2_bss_340140->unkAC[3]);

    LITInitAttn(lbl_2_bss_340140->unkAC[0], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(lbl_2_bss_340140->unkAC[0], 0.75f, 0.0f, 0.75f);
    LITInitDir(lbl_2_bss_340140->unkAC[0], 0.0f, 0.0f, 0.0f);
    LITInitColor(lbl_2_bss_340140->unkAC[0], (GXColor *)&red);
    LITInitDir(lbl_2_bss_340140->unkAC[0], 0.69f, 0.0f, 0.69f);

    LITInitAttn(lbl_2_bss_340140->unkAC[1], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(lbl_2_bss_340140->unkAC[1], 0.69f, 0.75f, 0.0f);
    LITInitDir(lbl_2_bss_340140->unkAC[1], 0.0f, 0.0f, 0.0f);
    LITInitColor(lbl_2_bss_340140->unkAC[1], (GXColor *)&blue);

    LITInitAttn(lbl_2_bss_340140->unkAC[2], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(lbl_2_bss_340140->unkAC[2], 0.0f, 0.0f, 0.75f);
    LITInitDir(lbl_2_bss_340140->unkAC[2], 0.0f, 0.0f, 0.0f);
    LITInitColor(lbl_2_bss_340140->unkAC[2], (GXColor *)&white);

    LITInitAttn(lbl_2_bss_340140->unkAC[3], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(lbl_2_bss_340140->unkAC[3], 0.0f, 0.0f, 0.69f);
    LITInitDir(lbl_2_bss_340140->unkAC[3], 0.0f, 0.0f, 0.0f);
    LITInitColor(lbl_2_bss_340140->unkAC[3], (GXColor *)&white);
}

// .text:0x00086DCC size:0x174 mapped:0x806C5E60
void fn_2_86DCC(void) {
    Mtx44 proj;
    f32 *row = lbl_2_data_2E944 + lbl_2_bss_33FBF5 * 6;

    lbl_2_bss_1A81D4.unk48.x = row[0];
    lbl_2_bss_1A81D4.unk48.y = row[1];
    lbl_2_bss_1A81D4.unk48.z = row[2];
    lbl_2_bss_1A81D4.unk3C.x = row[3];
    lbl_2_bss_1A81D4.unk3C.y = row[4];
    lbl_2_bss_1A81D4.unk3C.z = row[5];
    lbl_2_bss_B2A5 = 0;
    lbl_2_bss_B2A4 = 0;
    C_MTXFrustum(proj, -0.175f, 0.175f, 0.25f, -0.25f, 1.0f, 512.0f);
    GXSetProjection(proj, GX_PERSPECTIVE);
    fn_800B806C(0, -240.0f, 240.0f, -320.0f, 320.0f, -512.0f, -1.0f, 1280.0f);
    lbl_2_bss_1A81D4.unk38 = 0.0f;
    lbl_2_bss_1A81D4.unk54 = 0;
    lbl_2_bss_1A81D4.unk30 = -0x3E61;
    lbl_2_bss_1A81D4.unk32 = 0;
}

// .text:0x00086F40 size:0xAC mapped:0x806C5FD4
void fn_2_86F40(void) {
    s32 i;
    s32 elemOff = 0;
    s32 recOff = 0;

    for (i = 0; i < *(u16 *)hugeAnimStruct.unk68; i++) {
        u8 *elem = (u8 *)hugeAnimStruct.unk68 + elemOff;
        void *model = elem + 0x34;

        if (*(void **)model != NULL && elem[0xA0] != 0) {
            Rep0DERec28 *rec = (Rep0DERec28 *)((u8 *)hugeAnimStruct.unk2D94 + recOff);

            if (rec->unk0 != NULL) {
                rec->unk0(i);
            }
            sknRelated(model, fn_80052768_getCamera(0)->view);
        }
        elemOff += 0x90;
        recOff += 0x28;
    }
}

// .text:0x000870D4 size:0x40 mapped:0x806C6168
void fn_2_870D4(f32 arg) {
    if (arg != 0.0f) {
        lbl_2_bss_340140->unk307A = 3;
    } else {
        lbl_2_bss_340140->unk307A = 0;
    }
}

// .text:0x00086FEC size:0xE8 mapped:0x806C6080
void fn_2_86FEC(void) {
    Mtx44 proj;
    camera_803c639c_s *cam;

    C_MTXFrustum(proj, -0.175f, 0.175f, 0.25f, -0.25f, 1.0f, 512.0f);
    GXSetProjection(proj, GX_PERSPECTIVE);
    fn_2_48D54();
    fn_2_86470();
    fn_2_85D6C(&lbl_2_bss_1A81D4);
    cam = fn_80052768_getCamera(0);
    PSMTXCopy(cam->view, lbl_2_bss_1A81D4.mtx);
    fn_800A7D4C(0, lbl_2_data_2E9B4 + drawStadiumRelated * 8);
    cam = fn_80052768_getCamera(0);
    fn_2_190DC(lbl_2_bss_340140->unk68, cam->view);
}

// .text:0x00087114 size:0x4 mapped:0x806C61A8
void fn_2_87114(void) {
    return;
}

// .text:0x00087118 size:0x238 mapped:0x806C61AC
void fn_2_87118(void) {
    s32 i;
    s32 cellOff = 0;
    s32 elemOff = 0;
    u8 *base = (u8 *)lbl_2_data_2E608;

    lbl_2_bss_340140->unk3078 = (s8)base[0x338 + lbl_2_bss_33FBF5];
    lbl_2_bss_340140->unk2D94 = _OSAllocFromHeap(0x20, lbl_2_bss_340140->unk3078 * 0x28);
    lbl_2_bss_340140->unk68 = ActorObjectInitTable(lbl_2_bss_340140->unk3078);

    for (i = 0; i < lbl_2_bss_340140->unk3078; i++) {
        s16 *cell = (s16 *)(base + lbl_2_bss_33FBF5 * 0xB4 + cellOff);
        s16 cell0 = cell[0];
        s16 cell1 = cell[1];
        s16 cell2 = cell[2];
        Control *ctrl = (Control *)((u8 *)lbl_2_bss_340140->unk68 + elemOff + 0x44);

        animateBallRelated(lbl_2_bss_340140->unk68, (u16)i, (u16)i,
                           *(void **)((u8 *)lbl_2_bss_340140 + 0x2DA0 + cell0 * 12), 0, 0);
        fn_800BD548((u8 *)lbl_2_bss_340140->unk68 + elemOff + 0x34, 4, lbl_2_bss_340140->unkAC[0],
                    lbl_2_bss_340140->unkAC[1], lbl_2_bss_340140->unkAC[2], lbl_2_bss_340140->unkAC[3]);
        CTRLSetTranslation(ctrl, 0.0f, 0.0f, 0.0f);
        CTRLSetRotation(ctrl, -90.0f, 0.0f, 0.0f);

        if (cell2 != 0) {
            s32 count1 = *(s16 *)(base + 0x2D0 + cell0 * 2);
            s32 count2 = *(s16 *)(base + 0x2DC + cell0 * 2);
            s16 *src = (s16 *)(base + 0x2E8 + cell1 * 16);
            s32 k;
            s32 j;

            for (k = 0; k < count1; k++) {
                u8 *model = *(u8 **)((u8 *)lbl_2_bss_340140->unk68 + elemOff + 0x34);
                u8 *p18 = *(u8 **)(model + 0x18);
                u8 *entry = *(u8 **)(p18 + k * 4);
                u8 *p14 = *(u8 **)(entry + 0x14);
                u8 *arr = *(u8 **)(p14 + 8);
                u8 *out = *(u8 **)(arr + 0xC);

                for (j = 0; j < count2; j++) {
                    *(s16 *)(out + 0x20 * j + 0x20) = (s16)(k + src[j]);
                }
            }
        }
        cellOff += 6;
        elemOff += 0x90;
    }
}

// .text:0x00087350 size:0x304 mapped:0x806C63E4
void fn_2_87350(void) {
    s32 i;
    s32 cellOff = 0;
    s32 elemOff = 0;
    s32 recOff = 0;
    u8 *base = (u8 *)lbl_2_data_2E608;

    lbl_2_bss_340140->unk3078 = (s8)base[0x338 + lbl_2_bss_33FBF5];
    lbl_2_bss_340140->unk2D94 = _OSAllocFromHeap(0x20, lbl_2_bss_340140->unk3078 * 0x28);
    lbl_2_bss_340140->unk68 = ActorObjectInitTable(lbl_2_bss_340140->unk3078);

    for (i = 0; i < lbl_2_bss_340140->unk3078; i++) {
        s16 *cell = (s16 *)(base + lbl_2_bss_33FBF5 * 0xB4 + cellOff);
        s16 cell0 = cell[0];
        s16 cell1 = cell[1];
        s16 cell2 = cell[2];
        Control *ctrl = (Control *)((u8 *)lbl_2_bss_340140->unk68 + elemOff + 0x44);

        animateBallRelated(lbl_2_bss_340140->unk68, (u16)i, (u16)i,
                           *(void **)((u8 *)lbl_2_bss_340140 + 0x2DA0 + cell0 * 12), 0, 0);
        fn_800BD548((u8 *)lbl_2_bss_340140->unk68 + elemOff + 0x34, 4, lbl_2_bss_340140->unkAC[0],
                    lbl_2_bss_340140->unkAC[1], lbl_2_bss_340140->unkAC[2], lbl_2_bss_340140->unkAC[3]);
        CTRLSetTranslation(ctrl, 0.0f, 0.0f, 0.0f);
        CTRLSetRotation(ctrl, -90.0f, 0.0f, 0.0f);

        if (cell2 != 0) {
            s32 count1 = *(s16 *)(base + 0x2D0 + cell0 * 2);
            s32 count2 = *(s16 *)(base + 0x2DC + cell0 * 2);
            s16 *src = (s16 *)(base + 0x2E8 + cell1 * 16);
            s32 k;
            s32 j;

            for (k = 0; k < count1; k++) {
                u8 *model = *(u8 **)((u8 *)lbl_2_bss_340140->unk68 + elemOff + 0x34);
                u8 *p18 = *(u8 **)(model + 0x18);
                u8 *entry = *(u8 **)(p18 + k * 4);
                u8 *p14 = *(u8 **)(entry + 0x14);
                u8 *arr = *(u8 **)(p14 + 8);
                u8 *out = *(u8 **)(arr + 0xC);

                for (j = 0; j < count2; j++) {
                    *(s16 *)(out + 0x20 * j + 0x20) = (s16)(k + src[j]);
                }
            }
        }
        cellOff += 6;
        elemOff += 0x90;
    }

    elemOff = 0;
    for (i = 0; i < lbl_2_bss_340140->unk3078; i++) {
        Rep0DERec28 *rec = (Rep0DERec28 *)((u8 *)lbl_2_bss_340140->unk2D94 + recOff);
        u8 *elem = (u8 *)lbl_2_bss_340140->unk68 + elemOff;

        rec->pos.x = 0.0f;
        rec->pos.y = 0.0f;
        rec->pos.z = 0.0f;
        rec->unk10 = 0.0f;
        rec->unk14 = 0.0f;
        rec->unk18 = 0.0f;
        rec->unk26 = 0;
        rec->unk0 = NULL;
        elem[0xA0] = 0;
        recOff += 0x28;
        elemOff += 0x90;
    }
}

// .text:0x00087654 size:0x1D8 mapped:0x806C66E8
void fn_2_87654(s32 unused, s32 start, s32 count, s32 a, s32 b) {
    s32 i;
    s32 cellOff = start * 6;
    s32 elemOff = start * 0x90;
    s32 end = start + count;
    u8 *base = (u8 *)lbl_2_data_2E608;

    for (i = start; i < end; i++) {
        s16 *cell = (s16 *)(base + lbl_2_bss_33FBF5 * 0xB4 + cellOff);
        s16 cell0 = cell[0];
        s16 cell1 = cell[1];
        s16 cell2 = cell[2];
        Control *ctrl = (Control *)((u8 *)lbl_2_bss_340140->unk68 + elemOff + 0x44);

        animateBallRelated(lbl_2_bss_340140->unk68, (u16)i, (u16)i,
                           *(void **)((u8 *)lbl_2_bss_340140 + 0x2DA0 + cell0 * 12), a, b);
        fn_800BD548((u8 *)lbl_2_bss_340140->unk68 + elemOff + 0x34, 4, lbl_2_bss_340140->unkAC[0],
                    lbl_2_bss_340140->unkAC[1], lbl_2_bss_340140->unkAC[2], lbl_2_bss_340140->unkAC[3]);
        CTRLSetTranslation(ctrl, 0.0f, 0.0f, 0.0f);
        CTRLSetRotation(ctrl, -90.0f, 0.0f, 0.0f);

        if (cell2 != 0) {
            s32 count1 = *(s16 *)(base + 0x2D0 + cell0 * 2);
            s32 count2 = *(s16 *)(base + 0x2DC + cell0 * 2);
            s16 *src = (s16 *)(base + 0x2E8 + cell1 * 16);
            s32 k;
            s32 j;

            for (k = 0; k < count1; k++) {
                u8 *model = *(u8 **)((u8 *)lbl_2_bss_340140->unk68 + elemOff + 0x34);
                u8 *p18 = *(u8 **)(model + 0x18);
                u8 *entry = *(u8 **)(p18 + k * 4);
                u8 *p14 = *(u8 **)(entry + 0x14);
                u8 *arr = *(u8 **)(p14 + 8);
                u8 *out = *(u8 **)(arr + 0xC);

                for (j = 0; j < count2; j++) {
                    *(s16 *)(out + 0x20 * j + 0x20) = (s16)(k + src[j]);
                }
            }
        }
        cellOff += 6;
        elemOff += 0x90;
    }
}
