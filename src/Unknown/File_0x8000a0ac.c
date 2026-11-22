#include "Unknown/File_0x8000a0ac.h"
#include "Unknown/File_0x80009e94.h"
#include "Dolphin/mtx.h"

void fn_8000E764(f32 *out, f32 angle);

void fn_8000A0AC(void *out, f32 t, u8 *a, u8 *b) {
    InterpPoint pts[4];
    s16 *p1;
    s16 *p2;

    if (a[4] == 2) {
        p1 = (s16 *)(a + 0x34);
        p2 = (s16 *)(b + 0x34);
    } else {
        p1 = (s16 *)(a + 0x34);
        p2 = (s16 *)(b + 0x34);
    }

    pts[0].x = *(s16 *)(a + 0x14);
    pts[0].y = *(s16 *)(a + 0x16);
    pts[1].x = p1[2];
    pts[1].y = p1[3];
    pts[2].x = p2[0];
    pts[2].y = p2[1];
    pts[3].x = *(s16 *)(b + 0x14);
    pts[3].y = *(s16 *)(b + 0x16);
    BezierInterpolate((Vec2f *)out, (Vec2f *)&pts[0], (Vec2f *)&pts[1], (Vec2f *)&pts[2], (Vec2f *)&pts[3], t);
}

void interpolatePointsBezier_Vec2s(void *dst, const s16 *p0, const s16 *p1, const s16 *p2, const s16 *p3, s32 mode, f32 t) {
    InterpPoint pts[10];

    pts[0].x = p0[2];
    pts[0].y = p0[3];
    pts[3].x = p1[2];
    pts[3].y = p1[3];
    pts[6].x = p2[2];
    pts[6].y = p2[3];
    pts[9].x = p3[2];
    pts[9].y = p3[3];

    if (mode == 0) {
        interpolatePointsUnknown(3, pts, TRUE, FALSE);
        BezierInterpolate(dst, (Vec2f*)&pts[0], (Vec2f*)&pts[1], (Vec2f*)&pts[2], (Vec2f*)&pts[3], t);
    } else if (mode == 1) {
        interpolatePointsUnknown(3, pts, TRUE, FALSE);
        interpolatePointsUnknown(6, pts, FALSE, TRUE);
        BezierInterpolate(dst, (Vec2f*)&pts[3], (Vec2f*)&pts[4], (Vec2f*)&pts[5], (Vec2f*)&pts[6], t);
    } else {
        interpolatePointsUnknown(6, pts, FALSE, TRUE);
        BezierInterpolate(dst, (Vec2f*)&pts[6], (Vec2f*)&pts[7], (Vec2f*)&pts[8], (Vec2f*)&pts[9], t);
    }
}

#define UI_BLEND_U8(a, b) ((u8)((f32)(a) * inv + (f32)(b) * t))

u32 fn_8000A3EC(Mtx dest, Mtx outBuf, u8 *c, u8 *d, void *ctx, f32 t, f32 s) {
    u8 *out = (u8 *)outBuf;
    Mtx rot;
    Mtx scale;
    Mtx trans;
    u8 tmp[4];
    f32 inv = 1.0f - t;
    f32 tx = 0.0f;
    f32 ty = 0.0f;
    u32 changed;
    s32 i;
    s32 k;
    u8 *cc;
    u8 *dd;
    f32 angle;

    changed = 0;
    if (c[4] == 2) {
        if (*(u16 *)(c + 0x1C) != d[0x28]) {
            *(f32 *)(out + 0x30) = (f32)c[0x28] * inv + (f32)d[0x28] * t;
        } else {
            *(f32 *)(out + 0x30) = c[0x28];
        }
        if (*(u16 *)(c + 0x1E) != *(u16 *)(d + 0x1E)) {
            *(s16 *)(out + 0x34) = (s16)((f32)*(u16 *)(c + 0x1E) * inv + (f32)*(u16 *)(d + 0x1E) * t);
        } else {
            *(s16 *)(out + 0x34) = *(u16 *)(c + 0x1E);
        }
        if (c[0x2A] != d[0x2A]) {
            out[0x36] = (u8)((f32)c[0x2A] * inv + (f32)d[0x2A] * t);
        } else {
            out[0x36] = c[0x2A];
        }
        if (*(u32 *)(c + 0x20) != *(u32 *)(d + 0x20)) {
            out[0x20] = UI_BLEND_U8(c[0x20], d[0x20]);
            out[0x21] = UI_BLEND_U8(c[0x21], d[0x21]);
            out[0x22] = UI_BLEND_U8(c[0x22], d[0x22]);
            out[0x23] = UI_BLEND_U8(c[0x23], d[0x23]);
        } else {
            *(u32 *)(out + 0x20) = *(u32 *)(c + 0x20);
        }
        if (*(u32 *)(c + 0x24) != *(u32 *)(d + 0x24)) {
            out[0x24] = UI_BLEND_U8(c[0x24], d[0x24]);
            out[0x25] = UI_BLEND_U8(c[0x25], d[0x25]);
            out[0x26] = UI_BLEND_U8(c[0x26], d[0x26]);
            out[0x27] = UI_BLEND_U8(c[0x27], d[0x27]);
        } else {
            *(u32 *)(out + 0x24) = *(u32 *)(c + 0x24);
        }
    } else {
        for (i = 0; i < 8; i++) {
            *(s32 *)(out + i * 4) = (s32)((f32) * (s16 *)(c + 0x40 + i * 2) * inv + (f32) * (s16 *)(d + 0x40 + i * 2) * t);
        }
        cc = c;
        dd = d;
        for (i = 0; i < 4; i++) {
            for (k = 3; k >= 0; k--) {
                if (cc[0x1C + k] != dd[0x1C + k]) {
                    tmp[k] = (u8)((f32)cc[0x1C + k] * inv + (f32)dd[0x1C + k] * t);
                } else {
                    tmp[k] = cc[0x1C + k];
                }
                if (c[5] == 2 && k <= 2) {
                    tmp[k] = tmp[k] * tmp[3] / 255;
                }
            }
            *(u32 *)(out + 0x20 + i * 4) = *(u32 *)tmp;
            cc += (((c[8] >> 2) & 1) | ((d[8] >> 2) & 1)) << 2;
            dd += (((c[8] >> 2) & 1) | ((d[8] >> 2) & 1)) << 2;
        }
    }

    cc = c + 0x2C;
    dd = d + 0x2C;
    if (*(s16 *)(c + 0x10) != *(s16 *)(d + 0x10)) {
        tx = (f32)*(s16 *)(c + 0x10) * inv + (f32)*(s16 *)(d + 0x10) * t;
    } else if (*(s16 *)(c + 0x10) != 0) {
        tx = *(s16 *)(c + 0x10);
    }
    if (*(s16 *)(c + 0x12) != *(s16 *)(d + 0x12)) {
        ty = (f32)*(s16 *)(c + 0x12) * inv + (f32)*(s16 *)(d + 0x12) * t;
    } else if (*(s16 *)(c + 0x12) != 0) {
        ty = *(s16 *)(c + 0x12);
    }

    PSMTXTrans(trans, -tx, -ty, 0.0f);
    PSMTXScale(scale, ((f32)*(s16 *)(c + 0xC) * (1.0f / 1024.0f)) * inv + ((f32)*(s16 *)(d + 0xC) * (1.0f / 1024.0f)) * t,
               ((f32)*(s16 *)(c + 0xE) * (1.0f / 1024.0f)) * inv + ((f32)*(s16 *)(d + 0xE) * (1.0f / 1024.0f)) * t, 1.0f);
    PSMTXConcat(scale, trans, scale);

    for (i = 3; i >= 0; i--) {
        angle = inv * ((f32)*(s16 *)(cc + 6 + (i - 3) * 2) / 4096.0f) + t * ((f32)*(s16 *)(dd + 6 + (i - 3) * 2) / 4096.0f);
        if (angle != 0.0f) {
            changed |= 1;
            angle *= 6.2831855f;
            switch (i) {
            case 0:
                PSMTXRotRad(rot, 'X', angle);
                break;
            case 1:
                PSMTXRotRad(rot, 'Y', angle);
                break;
            case 2:
                PSMTXRotRad(rot, 'Z', angle);
                break;
            }
            if (i < 3) {
                PSMTXConcat(rot, scale, scale);
            }
        }
    }

    PSMTXTrans(trans, tx, ty, 0.0f);
    if (c[8] & 0x10) {
        trans[0][3] += ((f32 *)ctx)[0];
        trans[1][3] += ((f32 *)ctx)[1];
    } else {
        trans[0][3] += (f32)*(s16 *)(c + 0x14) * inv + (f32)*(s16 *)(d + 0x14) * t;
        trans[1][3] += (f32)*(s16 *)(c + 0x16) * inv + (f32)*(s16 *)(d + 0x16) * t;
    }
    trans[2][3] = s;
    PSMTXConcat(trans, scale, dest);
    return changed;
}

#define UI_BLEND_S16(a, b) ((f32)(a) * inv + (f32)(b) * t)

u32 fn_8000AF1C(Mtx dest, void *outBuf, u8 *c, u8 *d, u8 *block, f32 *ctx, f32 t) {
    u8 *out = (u8 *)outBuf;
    Mtx m1;
    Mtx m2;
    Mtx m3;
    Quaternion quat;
    f32 sc[2];
    u8 tmp[4];
    f32 inv = 1.0f - t;
    f32 tx = 0.0f;
    f32 ty = 0.0f;
    f32 angle;
    f32 sx;
    f32 sy;
    f32 qc;
    f32 qd;
    s32 i;
    u8 *cc;
    u8 *dd;
    u8 *rowC;
    u8 *rowD;

    if (*(s16 *)(c + 0x14) != *(s16 *)(d + 0x14)) {
        tx = UI_BLEND_S16(*(s16 *)(c + 0x14), *(s16 *)(d + 0x14));
    } else if (*(s16 *)(c + 0x14) != 0) {
        tx = *(s16 *)(c + 0x14);
    }
    if (*(s16 *)(c + 0x16) != *(s16 *)(d + 0x16)) {
        ty = UI_BLEND_S16(*(s16 *)(c + 0x16), *(s16 *)(d + 0x16));
    } else if (*(s16 *)(c + 0x16) != 0) {
        ty = *(s16 *)(c + 0x16);
    }

    PSMTXIdentity(m1);
    sx = ((f32)*(s16 *)(c + 0x10) * (1.0f / 1024.0f)) * inv + ((f32)*(s16 *)(d + 0x10) * (1.0f / 1024.0f)) * t;
    m1[0][0] = sx;
    m1[0][3] = sx * -tx;
    sy = ((f32)*(s16 *)(c + 0x12) * (1.0f / 1024.0f)) * inv + ((f32)*(s16 *)(d + 0x12) * (1.0f / 1024.0f)) * t;
    m1[1][1] = sy;
    m1[1][3] = sy * -ty;

    if (*(s16 *)(c + 0xE) != *(s16 *)(d + 0xE)) {
        angle = (f32)*(s16 *)(c + 0xE) / 4096.0f * inv + (f32)*(s16 *)(d + 0xE) / 4096.0f * t;
    } else {
        angle = (f32)*(s16 *)(c + 0xE) / 4096.0f;
    }
    if (angle != 0.0f) {
        angle *= 360.0f;
        if (((c[1] >> 1) & 1) != ((d[1] >> 1) & 1)) {
            angle *= 0.5f;
            fn_8000E764(sc, 1.5707964f * t);
            qc = sc[(c[1] >> 1) & 1];
            qd = sc[(d[1] >> 1) & 1];
            fn_8000E764(sc, 0.017453292f * angle);
            quat.x = 0.0f;
            quat.y = qc * sc[0];
            quat.z = qd * sc[0];
            quat.w = sc[1];
            PSMTXQuat(m2, &quat);
        } else if (((c[1] >> 1) & 1) != 0) {
            PSMTXRotRad(m2, 'Y', 0.017453292f * angle);
        } else {
            PSMTXRotRad(m2, 'Z', 0.017453292f * angle);
        }
        PSMTXConcat(m2, m1, m1);
    }

    PSMTXTrans(m3, tx, ty, 0.0f);
    if (c[1] & 8) {
        m3[0][3] += ctx[0];
        m3[1][3] += ctx[1];
    } else if (*(s16 *)(c + 4) != *(s16 *)(d + 4) || *(s16 *)(c + 6) != *(s16 *)(d + 6)) {
        m3[0][3] += UI_BLEND_S16(*(s16 *)(c + 4), *(s16 *)(d + 4));
        m3[1][3] += UI_BLEND_S16(*(s16 *)(c + 6), *(s16 *)(d + 6));
    } else {
        m3[0][3] += *(s16 *)(c + 4);
        m3[1][3] += *(s16 *)(c + 6);
    }
    PSMTXConcat(m3, m1, dest);

    cc = c + 0x18;
    dd = d + 0x18;
    for (i = 0; i < 4; i++) {
        if (*(u32 *)cc != *(u32 *)dd) {
            *(s32 *)(out + i * 8) = (s32)UI_BLEND_S16(*(s16 *)cc, *(s16 *)dd);
            *(s32 *)(out + i * 8 + 4) = (s32)UI_BLEND_S16(*(s16 *)(cc + 2), *(s16 *)(dd + 2));
        } else {
            *(s32 *)(out + i * 8) = *(s16 *)cc;
            *(s32 *)(out + i * 8 + 4) = *(s16 *)(cc + 2);
        }
        cc += 4;
        dd += 4;
    }

    if ((c[0] & 0xF) == 3) {
        if (*(u16 *)(c + 0x18) != *(u16 *)(d + 0x18)) {
            *(f32 *)(out + 0x30) = (f32)*(u16 *)(c + 0x18) * inv + (f32)*(u16 *)(d + 0x18) * t;
        } else {
            *(f32 *)(out + 0x30) = *(u16 *)(c + 0x18);
        }
        if (*(u16 *)(c + 0x1A) != *(u16 *)(d + 0x1A)) {
            *(s16 *)(out + 0x34) = (s16)((f32)*(u16 *)(c + 0x1A) * inv + (f32)*(u16 *)(d + 0x1A) * t);
        } else {
            *(s16 *)(out + 0x34) = *(u16 *)(c + 0x1A);
        }
        if (c[0x26] != d[0x26]) {
            out[0x36] = (u8)((f32)c[0x26] * inv + (f32)d[0x26] * t);
        } else {
            out[0x36] = c[0x26];
        }
        if (*(u32 *)(c + 0x1C) != *(u32 *)(d + 0x1C)) {
            *(u32 *)(out + 0x20) = (u32)((f32)*(u32 *)(c + 0x1C) * inv + (f32)*(u32 *)(d + 0x1C) * t);
        } else {
            *(u32 *)(out + 0x20) = *(u32 *)(c + 0x1C);
        }
        if (*(u32 *)(c + 0x20) != *(u32 *)(d + 0x20)) {
            *(u32 *)(out + 0x24) = (u32)((f32)*(u32 *)(c + 0x20) * inv + (f32)*(u32 *)(d + 0x20) * t);
        } else {
            *(u32 *)(out + 0x24) = *(u32 *)(c + 0x20);
        }
    } else if ((c[0] & 0xF) != 2) {
        if (*(u32 *)(c + 8) != *(u32 *)(d + 8)) {
            tmp[0] = UI_BLEND_U8(c[8], d[8]);
            tmp[1] = UI_BLEND_U8(c[9], d[9]);
            tmp[2] = UI_BLEND_U8(c[10], d[10]);
            tmp[3] = UI_BLEND_U8(c[11], d[11]);
            *(u32 *)(out + 0x2C) = *(u32 *)tmp;
            *(u32 *)(out + 0x28) = *(u32 *)tmp;
            *(u32 *)(out + 0x24) = *(u32 *)tmp;
            *(u32 *)(out + 0x20) = *(u32 *)tmp;
        } else {
            *(u32 *)(out + 0x2C) = *(u32 *)(c + 8);
            *(u32 *)(out + 0x28) = *(u32 *)(c + 8);
            *(u32 *)(out + 0x24) = *(u32 *)(c + 8);
            *(u32 *)(out + 0x20) = *(u32 *)(c + 8);
        }
    } else {
        for (i = 0; i < 4; i++) {
            rowC = block + *(u16 *)(c + 2) * 16 + 4 + i * 4;
            rowD = block + *(u16 *)(d + 2) * 16 + 4 + i * 4;
            if (*(u32 *)rowC != *(u32 *)rowD) {
                tmp[0] = UI_BLEND_U8(rowC[0], rowD[0]);
                tmp[1] = UI_BLEND_U8(rowC[1], rowD[1]);
                tmp[2] = UI_BLEND_U8(rowC[2], rowD[2]);
                tmp[3] = UI_BLEND_U8(rowC[3], rowD[3]);
                *(u32 *)(out + 0x20 + i * 4) = *(u32 *)tmp;
            } else {
                *(u32 *)(out + 0x20 + i * 4) = *(u32 *)rowC;
            }
        }
    }

    return angle != 0.0f;
}

