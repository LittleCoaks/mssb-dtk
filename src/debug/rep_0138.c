#include "debug/rep_0138.h"
#include "header_rep_data.h"
#include "Dolphin/gx.h"
#include "Unknown/File_0x800bd300.h"
#include "Unknown/File_0x800b9a30.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x800b0a14.h"
#include "Dolphin/stl.h"
#include "C3/control.h"
#include "stl/math.h"
#include "Dolphin/OS/OSCache.h"

typedef struct FogParams1_4E0 {
    GXColor color;
    f32 nearZ;
    f32 farZ;
} FogParams1_4E0;

typedef struct CopyBlock108 {
    u32 w[27];
} CopyBlock108;

extern void fn_80048C28(void);
extern void fn_80048C1C(void);
extern void fn_80048D4C(void);
extern void SetFog(s32 type, GXColor color, f32 nearZ, f32 farZ, f32 arg4, f32 arg5);

extern void *lbl_1_data_848[3];
extern u8 lbl_1_data_8C4[4];
extern GXColor lbl_1_data_858;
extern u8 lbl_1_bss_C0[0x428];
extern u8 lbl_1_data_2A8[0x7f0];
extern s32 lbl_1_bss_C4;
extern FogParams1_4E0 *lbl_1_bss_4E0;
extern f32 lbl_1_rodata_1D8;
extern f32 lbl_1_rodata_208;
extern f32 lbl_1_rodata_21C;
extern f32 lbl_1_rodata_220;
extern f32 lbl_1_rodata_224;
extern f32 lbl_1_rodata_228;
extern f32 lbl_1_rodata_22C;
extern f32 lbl_1_rodata_230;
extern f32 lbl_1_rodata_234;
extern f32 lbl_1_rodata_238;
extern f32 lbl_1_rodata_23C;
extern f32 lbl_1_rodata_240;
extern f32 lbl_1_rodata_244;
extern void fn_800B806C(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
extern s32 fn_80048EA8(u8 arg0);
extern void fn_80048E00(u8 arg0, s32 arg1);
extern void fn_80048C14(s32 arg0);
extern u8 lbl_1_bss_C2;
extern u8 lbl_1_data_85C;
extern u8 lbl_1_common_bss_472B4[0x3C0];
extern u8 drawStadiumRelated;
extern void fn_800A7D4C(s32 arg0, void *arg1);
extern f32 lbl_1_rodata_204;
extern void fn_1_4DD8(void *arg0);
extern void AdjustActorPointers(void *arg0);
extern void AdjustGEOPalettePointers(void *arg0);
extern void convertTextureHeader(void *arg0);
extern void UpdateTexturePalettePointers(void *arg0, void *arg1);
extern void haveActLayoutPointToGeoHeader(void *arg0, void *arg1);
extern f32 lbl_1_rodata_1A8;
extern u8 lbl_80366158[0x30];
extern void fn_800AD038(void *arg0);
extern void *_OSAllocFromHeap(s32 arg0, s32 arg1);
extern f32 lbl_1_rodata_1F0;
extern f32 lbl_1_rodata_1F4;
extern f32 lbl_1_rodata_1F8;
extern void renderingRelated(void);
extern f32 lbl_1_data_200[6];
extern f32 lbl_1_rodata_210;
extern f32 lbl_1_rodata_218;
extern u8 lbl_1_data_8C8;
extern u8 lbl_1_bss_2E0[0x200];
extern u8 lbl_1_bss_C1;
extern s32 checkObjectVisibility(s32 arg0, void *box, MtxPtr mtx);
extern void DOVARender(void *dispObj, MtxPtr camera, u8 numLights, va_list list);
extern f32 lbl_1_rodata_20C;
extern f32 lbl_1_rodata_214;
extern Vec lbl_1_rodata_188;
extern f32 lbl_1_rodata_248;
extern Vec lbl_1_data_87C;
extern void makeLookAtMatrix(MtxPtr dst, Vec *eye, Vec *target, Vec *up);
extern void fn_80011640(void *arg0, void *arg1);
extern void fn_800B9950(s32 arg0, f32 arg1, f32 arg2);
extern f32 lbl_1_rodata_1AC;
extern f32 lbl_1_rodata_1B0;
extern f32 lbl_1_rodata_1B4;
extern f32 lbl_1_rodata_1B8;
extern f32 lbl_1_rodata_1BC;
extern f32 lbl_1_rodata_1C0;
extern f32 lbl_1_rodata_1C4;
extern GXTexObj lbl_1_bss_4E4;
extern void fn_1_196C(void);
extern void fn_800B996C(void *arg0);
extern Vec lbl_1_data_A3C;
extern f32 lbl_1_rodata_1C8;
extern f32 lbl_1_rodata_1CC;
extern f32 lbl_1_rodata_1DC;
extern f32 lbl_1_rodata_1E0;
extern f32 lbl_1_rodata_1D0;
extern f32 lbl_1_rodata_1D4;
extern Vec lbl_1_data_A48;
extern void setLITLightPtr(s32 arg0);
extern void LITAlloc(void *slot);
extern void LITInitAttn(void *light, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
extern void LITInitPos(void *light, f32 arg1, f32 arg2, f32 arg3);
extern void LITInitDir(void *light, f32 arg1, f32 arg2, f32 arg3);
extern void LITInitColor(void *light, GXColor *color);
extern void *ARAMTransfer(void *arg0);
extern void DCFlushRangeNoSync(void *addr, u32 numBytes);
extern u8 lbl_803C6CF8[0x708];
extern GXColor lbl_1_rodata_194[3];
extern f32 lbl_1_rodata_1FC;
extern f32 lbl_1_rodata_200;

// .text:0x00004E98 size:0x648
#pragma dont_inline on
void fn_1_4E98(void *arg0, void *arg1) {
    u8 *obj = (u8 *)arg0;
    Mtx concat;
    s32 attrType[12];
    f32 vx, vy, vz;
    s32 i;

    if (*(s32 *)(obj + 0xc) == 0) {
        return;
    }
    if (*(s32 *)(obj + 0x0) == 0) {
        return;
    }
    if (*(s32 *)(obj + 0x10) == 0) {
        return;
    }

    GXSetZMode(1, 7, 0);
    GXSetBlendMode(1, 4, 5, 0);
    GXSetCullMode(0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xb, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xb, 1, 5, 0);
    GXSetNumChans(1);
    GXSetNumTevStages(1);
    GXSetNumTexGens(0);
    GXSetTevOp(0, 4);
    PSMTXConcat((f32(*)[4])arg1, (f32(*)[4])(obj + 0x18), concat);
    GXLoadPosMtxImm(concat, 0);
    GXSetCurrentMtx(0);

    for (i = 0; i < *(u16 *)(*(u8 **)(obj + 0x10) + 8); i++) {
        u8 *dataArr = *(u8 **)(*(u8 **)(obj + 0x10) + 4);
        u8 *record = dataArr + i * 0x10;
        u8 cmd = *record;

        if (cmd == 2) {
            u32 flags = *(u32 *)(record + 4);
            s32 j;
            memset(attrType, 0, sizeof(attrType));
            for (j = 0; j < 12; j++) {
                s32 v = (flags >> (2 + j * 2)) & 3;
                if (v != 0) {
                    attrType[j] = v;
                }
            }
        }

        {
            u8 *stream = *(u8 **)(dataArr + i * 0x10 + 8);
            if (stream != NULL) {
                u32 consumed = 0;
                u32 length = *(u32 *)(dataArr + i * 0x10 + 0xc);

                while (consumed < length) {
                    u8 sub = *stream;
                    s32 matched = 1;

                    switch (sub) {
                        case 0:
                            stream += 1;
                            consumed += 1;
                            break;
                        case 8:
                            stream += 6;
                            consumed += 6;
                            break;
                        case 0x10: {
                            u16 v = *(u16 *)stream;
                            s32 adv = v * 4 + 5;
                            stream += adv;
                            consumed += adv;
                            break;
                        }
                        case 0x20:
                        case 0x28:
                        case 0x30:
                        case 0x38:
                            stream += 5;
                            break;
                        case 0x40:
                        case 0x48:
                            stream += 1;
                            consumed += 1;
                            break;
                        case 0x61:
                            stream += 5;
                            consumed += 5;
                            break;
                        default:
                            matched = 0;
                            break;
                    }

                    if (matched) {
                        continue;
                    }

                    {
                        u16 vcount = *(u16 *)(stream + 1);
                        s32 v;
                        stream += 3;
                        GXBegin((GXPrimitive)0xa8, (GXVtxFmt)0, (u16)(vcount * 2));

                        for (v = 0; v < vcount; v++) {
                            s32 posIdx = 0, nrmIdx = 0;
                            s32 k, va;

                            for (k = 0, va = 9; k < 12; k++, va++) {
                                s32 t = attrType[k];
                                if (t == 0) {
                                    continue;
                                }
                                if (va == 9) {
                                    if (t == 2) {
                                        posIdx = stream[0];
                                    } else if (t == 3) {
                                        posIdx = *(u16 *)stream;
                                    }
                                } else if (va == 10) {
                                    if (t == 2) {
                                        nrmIdx = stream[0];
                                    } else if (t == 3) {
                                        nrmIdx = *(u16 *)stream;
                                    }
                                }
                                if (t == 2) {
                                    stream += 1;
                                    consumed += 1;
                                } else if (t == 3) {
                                    stream += 2;
                                    consumed += 2;
                                }
                            }

                            {
                                u8 *ds0 = *(u8 **)(obj + 0x0);
                                u8 mode0 = ds0[6];
                                u8 stride0 = ds0[7];
                                f32 scale0 = (f32)(1 << (mode0 & 0xf));
                                if (((mode0 >> 4) & 0xf) == 3) {
                                    s16 *arr = *(s16 **)ds0;
                                    s16 *p = arr + stride0 * posIdx;
                                    vx = (f32)(s32)p[0] / scale0;
                                    vy = (f32)(s32)p[1] / scale0;
                                    vz = (f32)(s32)p[2] / scale0;
                                }
                            }

                            GXWGFifo.f32 = vx;
                            GXWGFifo.f32 = vy;
                            GXWGFifo.f32 = vz;
                            GXWGFifo.u32 = 0xff0000ff;

                            {
                                u8 *ds1 = *(u8 **)(obj + 0xc);
                                u8 mode1 = ds1[6];
                                u8 stride1 = ds1[7];
                                f32 scale1 = (f32)(1 << (mode1 & 0xf));
                                if (((mode1 >> 4) & 0xf) == 3) {
                                    s16 *arr = *(s16 **)ds1;
                                    s16 *p = arr + stride1 * nrmIdx;
                                    vx += (f32)(s32)p[0] / scale1;
                                    vy += (f32)(s32)p[1] / scale1;
                                    vz += (f32)(s32)p[2] / scale1;
                                }
                            }

                            GXWGFifo.f32 = vx;
                            GXWGFifo.f32 = vy;
                            GXWGFifo.f32 = vz;
                            GXWGFifo.u32 = 0xffff;
                        }
                    }
                }
            }
        }
    }
}
#pragma dont_inline reset

// .text:0x000054E0 size:0x60
void fn_1_54E0(void *arg0) {
    s32 i;
    for (i = 0; i < 3; i++) {
        LITXForm(lbl_1_data_848[i], arg0);
    }
}

// .text:0x00005540 size:0x4
void fn_1_5540(void) {
    return;
}

// .text:0x00005544 size:0x154
void fn_1_5544(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *ind = lbl_1_data_2A8;
    u8 *base = lbl_1_bss_C0;
    u8 t;
    GXLoadTexObj((GXTexObj *)(base + 0x424), arg4);
    t = base[0x1c];
    if (t != 0) {
        if (t & 2) {
            arg4--;
        }
        if (t & 4) {
            arg3--;
        }
        GXSetTevOrder(arg0, arg3, arg4, 0xff);
        GXSetTevColorIn(arg0, 0xf, 0xf, 0xf, 8);
        GXSetTevColorOp(arg0, 0, 0, 0, 1, 0);
        GXSetTevAlphaIn(arg0, 7, 7, 7, 4);
        GXSetTevAlphaOp(arg0, 0, 0, 0, 1, 0);
    } else {
        GXSetNumIndStages(1);
        GXSetIndTexMtx(arg2, *(Mtx23 *)(ind + 0x7cc), (s8)*(f32 *)(ind + 0x7c8));
        GXSetIndTexOrder(arg1, arg3, arg4);
        GXSetIndTexCoordScale(arg1, *(u32 *)(base + 0x18), *(u32 *)(base + 0x14));
        GXSetTevIndWarp(arg0, arg1, ind[0x7c5], base[0x11], arg2);
    }
}

// .text:0x00005698 size:0x28C
void fn_1_5698(void) {
    Mtx44 ortho;
    Mtx posMtx;

    C_MTXOrtho(ortho, lbl_1_rodata_1A8, lbl_1_rodata_1AC, lbl_1_rodata_1A8, lbl_1_rodata_1B0, lbl_1_rodata_1B4, lbl_1_rodata_1B8);
    GXSetProjection(ortho, GX_ORTHOGRAPHIC);
    PSMTXIdentity(posMtx);
    GXLoadPosMtxImm(posMtx, 0);
    GXSetCurrentMtx(0);
    GXSetZMode(1, 7, 0);
    GXSetBlendMode(1, 4, 5, 0);
    GXSetCullMode(0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xd, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xd, 1, 2, 2);
    GXSetNumChans(0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(0, 1, 4, 0x3c, 0, 0x7d);
    GXSetTevColorIn(0, 0xf, 0xf, 0xf, 8);
    GXSetTevColorOp(0, 0, 0, 0, 1, 0);
    GXSetTevAlphaIn(0, 7, 7, 7, 4);
    GXSetTevAlphaOp(0, 0, 0, 0, 1, 0);
    GXSetTevOrder(0, 0, 0, 0xff);
    GXLoadTexObj(&lbl_1_bss_4E4, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(lbl_1_rodata_1A8, lbl_1_rodata_1BC, lbl_1_rodata_1A8);
    GXTexCoord2u16(0, 0);
    GXPosition3f32(lbl_1_rodata_1A8, lbl_1_rodata_1C0, lbl_1_rodata_1A8);
    GXTexCoord2u16(0, 4);
    GXPosition3f32(lbl_1_rodata_1C4, lbl_1_rodata_1C0, lbl_1_rodata_1A8);
    GXTexCoord2u16(4, 4);
    GXPosition3f32(lbl_1_rodata_1C4, lbl_1_rodata_1BC, lbl_1_rodata_1A8);
    GXTexCoord2u16(4, 0);
    GXSetNumIndStages(0);
    GXSetTevDirect(0);
}

// .text:0x00005924 size:0x19C
s32 fn_1_5924(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    switch (arg3) {
        case 4:
            return (arg1 / 8) * 32 + (arg2 / 8) * arg0 * 8 + (arg2 % 8) * 8 + (arg1 % 8);
        case 8:
            return (arg1 / 8) * 32 + (arg2 / 4) * arg0 * 4 + (arg2 % 4) * 8 + (arg1 % 8);
        case 0x10:
            return (arg1 / 4) * 16 + (arg2 / 4) * arg0 * 4 + (arg2 % 4) * 4 + (arg1 % 4);
        case 0x20: {
            s32 result = (arg1 / 8) * 16 + (arg2 / 4) * arg0 * 4 + (arg2 % 4) * 8 + (arg1 % 4);
            if (arg4 != 0) {
                result += 0x10;
            }
            return result;
        }
    }
}

// .text:0x00005AC0 size:0x590
void fn_1_5AC0(void *arg0, s32 arg1, s32 arg2, f32 arg3) {
    u16 *buf = (u16 *)arg0;
    s32 w = arg1;
    s32 h = arg2;
    s32 halfH = h / 2;
    s32 y;
    s32 x;

    memset(arg0, 0, w * 2 * h);

    for (y = 0; y < h; y++) {
        f32 ny = lbl_1_rodata_1C8 * ((f32)y / (f32)h - lbl_1_rodata_1CC);
        f32 nyUv = ny * lbl_1_rodata_1CC + lbl_1_rodata_1CC;
        f32 ny2 = ny * ny;
        s32 yBand = (ny > lbl_1_rodata_1D0) && (ny < lbl_1_rodata_1D4);
        s32 rowBase = (y / 4) * w * 4 + (y % 4) * 4;

        for (x = 0; x < w; x++) {
            f32 nx = lbl_1_rodata_1C8 * ((f32)x / (f32)w - lbl_1_rodata_1CC);
            f32 nxUv = nx * lbl_1_rodata_1CC + lbl_1_rodata_1CC;
            s32 xBand = (nx > lbl_1_rodata_1D0) && (nx < lbl_1_rodata_1D4);
            s32 band = xBand && yBand;
            f32 d;
            Vec vec;
            s32 idx;
            u8 uByte;
            u8 vByte;

            if (y == halfH) {
                d = 1.0f - nx * nx;
            } else {
                d = (1.0f - nx * nx) - ny2;
            }

            if (d < 0.0f) {
                vec.x = nx;
                vec.y = ny;
                vec.z = 0.0f;
                PSVECNormalize(&vec, &vec);
            } else {
                vec.x = nx;
                vec.y = ny;
                vec.z = -(f32)sqrt((f64)d);
            }

            if (band && arg3 != 1.0f) {
                Vec cross;
                f32 mag;
                PSVECCrossProduct(&lbl_1_data_A48, &vec, &cross);
                mag = PSVECMag(&cross);
                if (mag != 0.0f) {
                    f32 angle;
                    f32 half;
                    Quaternion quat;
                    Mtx mtx;
                    PSVECNormalize(&cross, &cross);
                    angle = (f32)acos((f64)PSVECDotProduct(&lbl_1_data_A48, &vec));
                    half = (angle * arg3) * lbl_1_rodata_1CC;
                    quat.x = cross.x * (f32)sin((f64)half);
                    quat.y = cross.y * (f32)sin((f64)half);
                    quat.z = cross.z * (f32)sin((f64)half);
                    quat.w = (f32)cos((f64)half);
                    PSMTXQuat(mtx, &quat);
                    PSMTXMultVec(mtx, &lbl_1_data_A48, &vec);
                }
            }

            {
                Vec xz;
                f32 uAngle;
                f32 vAngle;

                xz.x = vec.x;
                xz.y = 0.0f;
                xz.z = vec.z;

                if (PSVECMag(&xz) == 0.0f) {
                    uAngle = 0.0f;
                    vAngle = 0.0f;
                } else {
                    PSVECNormalize(&xz, &xz);
                    if (ny == 0.0f) {
                        vAngle = lbl_1_rodata_1CC;
                    } else {
                        Vec cross2;
                        f32 mag2;
                        uAngle = (f32)acos((f64)PSVECDotProduct(&xz, &vec));
                        PSVECCrossProduct(&xz, &vec, &cross2);
                        mag2 = PSVECMag(&cross2);
                        if (mag2 != 0.0f && cross2.x < 0.0f) {
                            uAngle = -uAngle;
                        }
                        uAngle = uAngle / lbl_1_rodata_1DC + lbl_1_rodata_1CC;
                    }
                    if (nx == 0.0f) {
                        vAngle = lbl_1_rodata_1CC;
                    } else {
                        Vec cross3;
                        f32 mag3;
                        vAngle = (f32)acos((f64)PSVECDotProduct(&lbl_1_data_A48, &xz));
                        PSVECCrossProduct(&lbl_1_data_A48, &xz, &cross3);
                        mag3 = PSVECMag(&cross3);
                        if (mag3 != 0.0f && cross3.y > 0.0f) {
                            vAngle = -vAngle;
                        }
                        vAngle = vAngle / lbl_1_rodata_1DC + lbl_1_rodata_1CC;
                    }
                    uAngle -= nyUv;
                    vAngle -= nxUv;
                }

                uByte = (u8)(s32)(lbl_1_rodata_1E0 * uAngle + lbl_1_rodata_1E0);
                vByte = (u8)(s32)(lbl_1_rodata_1E0 * vAngle + lbl_1_rodata_1E0);
            }

            idx = rowBase + (x / 4) * 16 + (x % 4);
            buf[idx] = uByte | (vByte << 8);
        }
    }

    DCFlushRange(arg0, w * 2 * h);
}

// .text:0x00006050 size:0x528
#pragma dont_inline on
void fn_1_6050(void *arg0, s32 arg1, s32 arg2, f32 arg3) {
    u16 *buf = (u16 *)arg0;
    s32 w = arg1;
    s32 h = arg2;
    s32 halfH = h / 2;
    s32 y;
    s32 x;

    memset(arg0, 0, w * 2 * h);

    for (y = 0; y < h; y++) {
        f32 ny = lbl_1_rodata_1C8 * ((f32)y / (f32)h - lbl_1_rodata_1CC);
        f32 nyUv = ny * lbl_1_rodata_1CC + lbl_1_rodata_1CC;
        f32 ny2 = ny * ny;
        s32 rowBase = (y / 4) * w * 4 + (y % 4) * 4;

        for (x = 0; x < w; x++) {
            f32 nx = lbl_1_rodata_1C8 * ((f32)x / (f32)w - lbl_1_rodata_1CC);
            f32 nxUv = nx * lbl_1_rodata_1CC + lbl_1_rodata_1CC;
            f32 d;
            Vec vec;
            s32 idx;
            u8 uByte;
            u8 vByte;

            if (y == halfH) {
                d = 1.0f - nx * nx;
            } else {
                d = (1.0f - nx * nx) - ny2;
            }

            if (d < 0.0f) {
                vec.x = nx;
                vec.y = ny;
                vec.z = 0.0f;
                PSVECNormalize(&vec, &vec);
            } else {
                vec.x = nx;
                vec.y = ny;
                vec.z = -(f32)sqrt((f64)d);
            }

            if (arg3 != 1.0f) {
                Vec cross;
                f32 mag;
                PSVECCrossProduct(&lbl_1_data_A3C, &vec, &cross);
                mag = PSVECMag(&cross);
                if (mag != 0.0f) {
                    f32 angle;
                    f32 half;
                    Quaternion quat;
                    Mtx mtx;
                    PSVECNormalize(&cross, &cross);
                    angle = (f32)acos((f64)PSVECDotProduct(&lbl_1_data_A3C, &vec));
                    half = (angle * arg3) * lbl_1_rodata_1CC;
                    quat.x = cross.x * (f32)sin((f64)half);
                    quat.y = cross.y * (f32)sin((f64)half);
                    quat.z = cross.z * (f32)sin((f64)half);
                    quat.w = (f32)cos((f64)half);
                    PSMTXQuat(mtx, &quat);
                    PSMTXMultVec(mtx, &lbl_1_data_A3C, &vec);
                }
            }

            {
                Vec xz;
                f32 uAngle;
                f32 vAngle;

                xz.x = vec.x;
                xz.y = 0.0f;
                xz.z = vec.z;

                if (PSVECMag(&xz) == 0.0f) {
                    uAngle = 0.0f;
                    vAngle = 0.0f;
                } else {
                    PSVECNormalize(&xz, &xz);
                    if (ny == 0.0f) {
                        vAngle = lbl_1_rodata_1CC;
                    } else {
                        Vec cross2;
                        f32 mag2;
                        uAngle = (f32)acos((f64)PSVECDotProduct(&xz, &vec));
                        PSVECCrossProduct(&xz, &vec, &cross2);
                        mag2 = PSVECMag(&cross2);
                        if (mag2 != 0.0f && cross2.x < 0.0f) {
                            uAngle = -uAngle;
                        }
                        uAngle = uAngle / lbl_1_rodata_1DC + lbl_1_rodata_1CC;
                    }
                    if (nx == 0.0f) {
                        vAngle = lbl_1_rodata_1CC;
                    } else {
                        Vec cross3;
                        f32 mag3;
                        vAngle = (f32)acos((f64)PSVECDotProduct(&lbl_1_data_A3C, &xz));
                        PSVECCrossProduct(&lbl_1_data_A3C, &xz, &cross3);
                        mag3 = PSVECMag(&cross3);
                        if (mag3 != 0.0f && cross3.y > 0.0f) {
                            vAngle = -vAngle;
                        }
                        vAngle = vAngle / lbl_1_rodata_1DC + lbl_1_rodata_1CC;
                    }
                    uAngle -= nyUv;
                    vAngle -= nxUv;
                }

                uByte = (u8)(s32)(lbl_1_rodata_1E0 * uAngle + lbl_1_rodata_1E0);
                vByte = (u8)(s32)(lbl_1_rodata_1E0 * vAngle + lbl_1_rodata_1E0);
            }

            idx = rowBase + (x / 4) * 16 + (x % 4);
            buf[idx] = uByte | (vByte << 8);
        }
    }

    DCFlushRange(arg0, w * 2 * h);
}
#pragma dont_inline reset

// .text:0x00006578 size:0x14C
void fn_1_6578(GXTexObj *arg0, void *arg1, s32 arg2, s32 arg3) {
    u8 *base = lbl_1_data_2A8;
    s32 h = arg3;
    s32 w = arg2;
    s32 minFilter;

    if (base[0x778] == 0) {
        fn_1_6050(arg1, arg2 / 4, arg3 / 4, lbl_1_rodata_1D8);
        minFilter = 1;
    } else {
        f32 *p = (f32 *)(base + 0x77c);
        s32 offset = 0;
        s32 i;
        for (i = 0; i <= base[0x778]; i++, p++) {
            fn_1_6050((u8 *)arg1 + offset * 2, w, h, *p);
            offset += w * h;
            w /= 2;
            h /= 2;
        }
        minFilter = *(s32 *)(base + 0x790);
    }

    GXInitTexObj(arg0, arg1, (u16)arg2, (u16)arg3, 3, 1, 1, base[0x778]);
    GXInitTexObjLOD(arg0, minFilter, 1, lbl_1_rodata_1A8, (f32)base[0x778], *(f32 *)(base + 0x78c), 0, 0, 0);
}

// .text:0x000066C4 size:0x184
void fn_1_66C4(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    u8 *p;
    s8 a;
    s8 b;

    fn_800AD038(*(void **)(lbl_80366158 + 0x8));
    item->state = 0;

    p = lbl_1_common_bss_472B4;
    a = (s8)p[0x230];
    b = (s8)p[0x231];
    memset(p, 0, 0x240);
    p[0x230] = a;
    p[0x231] = b;

    *(void **)(p + 0x21c) = _OSAllocFromHeap(0x20, 0x80000);
    *(f32 *)(p + 0x4c) = lbl_1_rodata_1F0;
    *(f32 *)(p + 0x50) = lbl_1_rodata_1F4;
    *(f32 *)(p + 0x54) = lbl_1_rodata_1F8;
    *(s16 *)(p + 0x30) = -0xc94;
    *(s16 *)(p + 0x22e) = -1;
    p[0x234] = 0;
    PSMTXIdentity((f32(*)[4])(p + 0x64));

    *(void **)(p + 0x60) = fn_1_77EC;
    *(CopyBlock108 *)(p + 0xc8) = *(CopyBlock108 *)(p + 0x5c);
    *(void **)(p + 0x138) = renderingRelated;
    *(CopyBlock108 *)(p + 0x1a0) = *(CopyBlock108 *)(p + 0x134);

    currentDrawingItem->func = fn_1_6848;
}

// .text:0x00006848 size:0x5CC
void fn_1_6848(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    u8 *data2A8 = lbl_1_data_2A8;
    u8 *bssC0 = lbl_1_bss_C0;

    switch (item->state) {
        case 0: {
            s32 baseWH = *(s32 *)(data2A8 + 0x5ac);
            s32 mipCount = data2A8[0x778];
            s32 w;
            s32 h;
            s32 minFilter;
            GXColor c[3];
            void *light1;
            void *light2;
            void *light3;

            setLITLightPtr(0);

            if (mipCount == 0) {
                w = baseWH / 4;
                h = baseWH / 4;
                fn_1_6050(bssC0 + 0x460, w, h, lbl_1_rodata_1D8);
                minFilter = 1;
            } else {
                f32 *mipTab = (f32 *)(data2A8 + 0x77c);
                s32 offset = 0;
                s32 i;
                w = baseWH;
                h = baseWH;
                for (i = 0; i <= mipCount; i++, mipTab++) {
                    fn_1_6050(bssC0 + 0x460 + offset * 2, w, h, *mipTab);
                    offset += w * h;
                    w /= 2;
                    h /= 2;
                }
                minFilter = *(s32 *)(data2A8 + 0x790);
            }

            GXInitTexObj((GXTexObj *)(bssC0 + 0x424), bssC0 + 0x460, (u16)w, (u16)h, 3, 1, 1, data2A8[0x778]);
            GXInitTexObjLOD((GXTexObj *)(bssC0 + 0x424), minFilter, 1, lbl_1_rodata_1A8, (f32)data2A8[0x778], *(f32 *)(data2A8 + 0x78c), 0, 0, 0);
            fn_800B996C(fn_1_5544);

            LITAlloc(data2A8 + 0x5a0);
            LITAlloc(data2A8 + 0x5a4);
            LITAlloc(data2A8 + 0x5a8);

            c[0] = lbl_1_rodata_194[0];
            c[1] = lbl_1_rodata_194[1];
            c[2] = lbl_1_rodata_194[2];

            light1 = *(void **)(data2A8 + 0x5a0);
            LITInitAttn(light1, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
            LITInitPos(light1, lbl_1_rodata_1FC, lbl_1_rodata_200, 0.0f);
            LITInitDir(light1, 0.0f, 0.0f, 0.0f);
            LITInitColor(light1, &c[0]);

            light2 = *(void **)(data2A8 + 0x5a4);
            LITInitAttn(light2, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
            LITInitPos(light2, 0.0f, lbl_1_rodata_200, lbl_1_rodata_1FC);
            LITInitDir(light2, 0.0f, 0.0f, 0.0f);
            LITInitColor(light2, &c[1]);

            light3 = *(void **)(data2A8 + 0x5a8);
            LITInitAttn(light3, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
            LITInitPos(light3, lbl_1_rodata_1FC, lbl_1_rodata_200, lbl_1_rodata_1FC);
            LITInitDir(light3, 0.0f, 0.0f, 0.0f);
            LITInitColor(light3, &c[2]);

            item->state = 1;
            break;
        }

        case 1: {
            u16 val = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
            switch (val) {
                case 8: {
                    s8 v = lbl_1_common_bss_472B4[0x230] - 1;
                    lbl_1_common_bss_472B4[0x230] = v;
                    if (v < 0) {
                        lbl_1_common_bss_472B4[0x230] = *(s32 *)(data2A8 + 0x624) - 1;
                    }
                    break;
                }
                case 4: {
                    s32 t = lbl_1_common_bss_472B4[0x230] + 1;
                    s8 tb = (s8)t;
                    lbl_1_common_bss_472B4[0x230] = t;
                    if (tb >= *(s32 *)(data2A8 + 0x624)) {
                        lbl_1_common_bss_472B4[0x230] = 0;
                    }
                    break;
                }
                case 0x200: {
                    s8 v = lbl_1_common_bss_472B4[0x231] + 1;
                    lbl_1_common_bss_472B4[0x231] = v;
                    if (v > 2) {
                        lbl_1_common_bss_472B4[0x231] = 0;
                    }
                    break;
                }
                case 0x1000:
                    fn_800B996C(0);
                    item->currentDrawingItem->state = 1;
                    break;
                case 0x100:
                    item->state = 2;
                    break;
            }
            break;
        }

        case 2: {
            s16 idx = (s8)lbl_1_common_bss_472B4[0x230] * 3 + (s8)lbl_1_common_bss_472B4[0x231];
            s32 idx2;
            *(s16 *)((u8 *)item + 0x18) = idx;
            *(void **)((u8 *)item + 0x14) = ARAMTransfer(data2A8 + 0x628 + idx * 0x10);
            item->state = 3;
            idx2 = (s8)lbl_1_common_bss_472B4[0x230] * 0x60 + (s8)lbl_1_common_bss_472B4[0x231] * 0xc;
            *(void **)(bssC0 + 0x420) = data2A8 + idx2;
            break;
        }

        case 3: {
            if (lbl_803C6CF8[0x715] != 1) {
                break;
            }
            {
                u8 *p = *(u8 **)((u8 *)item + 0x14);
                u8 *r0 = p + *(s32 *)(p + 0x0);
                u8 *r1 = p + *(s32 *)(p + 0xc);
                u8 *r2 = p + *(s32 *)(p + 0x14);
                u8 *q1;
                u8 *q0;
                s16 idx;
                u32 sz;

                fn_1_4DD8(p + *(s32 *)(p + 0x8));
                AdjustActorPointers(r0);
                AdjustGEOPalettePointers(r1);
                convertTextureHeader(r2);
                *(void **)(lbl_1_common_bss_472B4 + 0x58) = r2 + 4;
                UpdateTexturePalettePointers(r1, r2);
                haveActLayoutPointToGeoHeader(r0, r1);
                *(u16 *)(lbl_1_common_bss_472B4 + 0x22a) = *(u16 *)(r0 + 6);
                *(void **)(lbl_1_common_bss_472B4 + 0x130) = r0;
                *(void **)(lbl_1_common_bss_472B4 + 0xc4) = r0;

                q0 = p + *(s32 *)(p + 0x4);
                q1 = p + *(s32 *)(p + 0x10);
                AdjustActorPointers(q0);
                AdjustGEOPalettePointers(q1);
                UpdateTexturePalettePointers(q1, r2);
                haveActLayoutPointToGeoHeader(q0, q1);
                *(void **)(lbl_1_common_bss_472B4 + 0x208) = q0;
                *(void **)(lbl_1_common_bss_472B4 + 0x19c) = q0;

                idx = *(s16 *)((u8 *)item + 0x18);
                sz = *(u32 *)(data2A8 + 0x628 + idx * 0x10 + 4);
                p = *(u8 **)((u8 *)item + 0x14);
                DCFlushRangeNoSync(p, sz & 0x0fffffff);

                currentDrawingItem->func = fn_1_6E14;
            }
            break;
        }
    }
}

// .text:0x00006E14 size:0x368
void fn_1_6E14(void) {
    u8 *data2A8 = lbl_1_data_2A8;
    u16 flags;

    fn_1_7960();

    if ((s8)lbl_1_common_bss_472B4[0x238] == 0) {
        u8 *base = lbl_1_common_bss_472B4;
        u8 *e1 = base + drawStadiumRelated * 0x6c + 0x5c;
        u8 *e2;
        f32 angle;

        PSMTXCopy((f32(*)[4])base, (f32(*)[4])(e1 + 0x38));
        fn_800A7D4C(0, data2A8 + 0x60c + drawStadiumRelated * 8);
        fn_800A7D4C(0, e1);
        fn_800A7D4C(0, data2A8 + 0x5fc + drawStadiumRelated * 8);

        angle = lbl_1_rodata_204 * (f32)(*(u16 *)(lbl_1_common_bss_472B4 + 0x23a));
        e2 = lbl_1_common_bss_472B4 + drawStadiumRelated * 0x6c + 0x134;
        PSMTXRotRad((f32(*)[4])(e2 + 8), 'Y', angle);
        PSMTXCopy((f32(*)[4])lbl_1_common_bss_472B4, (f32(*)[4])(e2 + 0x38));
        fn_800A7D4C(0, e2);
        fn_800A7D4C(0, data2A8 + 0x5e4 + drawStadiumRelated * 8);
    } else {
        fn_1_196C();
    }

    flags = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 2);
    if (flags & 0x1000) {
        SetFogNoneAgain();
        currentDrawingItem->func = fn_1_66C4;
    } else if (flags & 0x200) {
        lbl_1_common_bss_472B4[0x235] = 0;
        lbl_1_common_bss_472B4[0x238] = 0;
        lbl_1_common_bss_472B4[0x232] ^= 1;
        *(s16 *)(lbl_1_common_bss_472B4 + 0x22e) = -1;
    }

    if (lbl_1_common_bss_472B4[0x232] != 0) {
        u16 val = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
        switch (val) {
            case 8: {
                s32 t = lbl_1_common_bss_472B4[0x233] - 1;
                lbl_1_common_bss_472B4[0x233] = t;
                if ((s8)t < 0) lbl_1_common_bss_472B4[0x233] = 7;
                break;
            }
            case 4: {
                s32 t = lbl_1_common_bss_472B4[0x233] + 1;
                lbl_1_common_bss_472B4[0x233] = t;
                if ((s8)t >= 8) lbl_1_common_bss_472B4[0x233] = 0;
                break;
            }
            case 0x100: {
                s8 sel = (s8)lbl_1_common_bss_472B4[0x233];
                switch (sel) {
                    case 0:
                        lbl_1_common_bss_472B4[0x235] = 1;
                        lbl_1_common_bss_472B4[0x232] = 0;
                        break;
                    case 1:
                        *(s16 *)(lbl_1_common_bss_472B4 + 0x22e) = -1;
                        lbl_1_common_bss_472B4[0x235] = 1;
                        lbl_1_common_bss_472B4[0x232] = 0;
                        break;
                    case 2:
                        lbl_1_common_bss_472B4[0x235] = 1;
                        lbl_1_common_bss_472B4[0x232] = 0;
                        break;
                    case 3:
                        lbl_1_common_bss_472B4[0x235] = 1;
                        lbl_1_common_bss_472B4[0x232] = 0;
                        break;
                    case 4:
                        lbl_1_common_bss_472B4[0x234] ^= 1;
                        break;
                    case 5:
                        lbl_1_common_bss_472B4[0x235] = 1;
                        lbl_1_common_bss_472B4[0x232] = 0;
                        break;
                    case 6:
                        lbl_1_bss_C0[0] ^= 1;
                        break;
                    case 7:
                        lbl_1_bss_C1 ^= 1;
                        break;
                }
                break;
            }
        }
    }

    if ((s8)lbl_1_common_bss_472B4[0x235] != 0) {
        s8 idx = (s8)lbl_1_common_bss_472B4[0x233];
        void (*handler)(void) = *(void (**)(void))(data2A8 + 0x5b8 + idx * 4);
        handler();
    }

    if (lbl_1_bss_C0[0]) {
        fn_800B996C(fn_1_5544);
    } else {
        fn_800B996C(0);
    }
}

// .text:0x0000717C size:0x104
void fn_1_717C(u8 *arg0) {
    u8 *p0 = arg0 + *(s32 *)(arg0 + 0x0);
    u8 *p1 = arg0 + *(s32 *)(arg0 + 0xc);
    u8 *p2 = arg0 + *(s32 *)(arg0 + 0x14);
    u8 *q1;
    u8 *q0;

    fn_1_4DD8(arg0 + *(s32 *)(arg0 + 0x8));
    AdjustActorPointers(p0);
    AdjustGEOPalettePointers(p1);
    convertTextureHeader(p2);
    *(void **)(lbl_1_common_bss_472B4 + 0x58) = p2 + 4;
    UpdateTexturePalettePointers(p1, p2);
    haveActLayoutPointToGeoHeader(p0, p1);
    *(u16 *)(lbl_1_common_bss_472B4 + 0x22a) = *(u16 *)(p0 + 6);
    *(void **)(lbl_1_common_bss_472B4 + 0x130) = p0;
    *(void **)(lbl_1_common_bss_472B4 + 0xc4) = p0;

    q0 = arg0 + *(s32 *)(arg0 + 0x4);
    q1 = arg0 + *(s32 *)(arg0 + 0x10);
    AdjustActorPointers(q0);
    AdjustGEOPalettePointers(q1);
    UpdateTexturePalettePointers(q1, p2);
    haveActLayoutPointToGeoHeader(q0, q1);
    *(void **)(lbl_1_common_bss_472B4 + 0x208) = q0;
    *(void **)(lbl_1_common_bss_472B4 + 0x19c) = q0;
}

// .text:0x00007280 size:0x138
void fn_1_7280(void) {
    u8 *data2A8 = lbl_1_data_2A8;
    u8 *e1 = lbl_1_common_bss_472B4 + drawStadiumRelated * 0x6c + 0x5c;
    u8 *p1 = data2A8 + 0x60c;
    u8 *p2 = data2A8 + 0x5fc;
    u8 *p3 = data2A8 + 0x5e4;
    u8 *e2;
    f32 angle;

    PSMTXCopy((f32(*)[4])lbl_1_common_bss_472B4, (f32(*)[4])(e1 + 0x38));
    fn_800A7D4C(0, p1 + drawStadiumRelated * 8);
    fn_800A7D4C(0, e1);
    fn_800A7D4C(0, p2 + drawStadiumRelated * 8);

    angle = lbl_1_rodata_204 * (f32)(*(u16 *)(lbl_1_common_bss_472B4 + 0x23a));
    e2 = lbl_1_common_bss_472B4 + drawStadiumRelated * 0x6c + 0x134;
    PSMTXRotRad((f32(*)[4])(e2 + 8), 'Y', angle);
    PSMTXCopy((f32(*)[4])lbl_1_common_bss_472B4, (f32(*)[4])(e2 + 0x38));
    fn_800A7D4C(0, e2);
    fn_800A7D4C(0, p3 + drawStadiumRelated * 8);
}

// .text:0x000073B8 size:0x434
void fn_1_73B8(s32 arg0, s32 count, ...) {
    u8 *p = (u8 *)arg0;
    u8 *items = *(u8 **)(p + 0x68);
    u8 *mid = *(u8 **)(items + 0x10);
    u8 *cam1;
    u8 *cam2;
    u8 *lut;
    u8 *flags;
    u8 *e;
    u8 *geo;
    Mtx concat;
    f32 box[24];
    s16 sel;
    s32 start;
    s32 end;
    s32 i;
    u16 f34;
    u16 f3a;

    if (lbl_1_data_8C8 == 1) {
        memset(lbl_1_bss_2E0, 0, 0x200);
        lbl_1_data_8C8 = 0;
    } else if (lbl_1_data_8C8 == 2) {
        memset(lbl_1_bss_2E0, 1, 0x200);
        lbl_1_data_8C8 = 0;
    }

    sel = *(s16 *)(lbl_1_common_bss_472B4 + 0x22e);
    *(s16 *)(lbl_1_common_bss_472B4 + 0x22c) = 0;
    if (sel < 0) {
        start = 0;
        end = *(u16 *)(items + 6);
    } else {
        start = sel;
        end = sel + 1;
    }

    flags = lbl_1_bss_2E0 + start;
    e = items + start * 0x1c;
    cam1 = p + 8;
    cam2 = p + 0x38;
    for (i = start; i < end; i++, flags++, e += 0x1c) {
        if (*flags != 0) {
            continue;
        }
        f34 = *(u16 *)(e + 0x34);
        if (f34 == 0xffff) {
            continue;
        }

        f3a = *(u16 *)(e + 0x3a);
        if (f3a & 1) {
            GXSetZMode(0, 7, 1);
        } else {
            GXSetZMode(1, 3, 1);
        }
        switch (f3a & 6) {
            case 2:
                GXSetBlendMode(1, 1, 1, 0);
                break;
            case 4:
                GXSetBlendMode(1, 2, 0, 0);
                break;
            default:
                GXSetBlendMode(1, 4, 5, 0);
                break;
        }

        lut = *(u8 **)(mid + 0x10);
        geo = *(u8 **)(lut + (f34 << 3));
        CTRLBuildMatrix(*(Control **)(e + 0x20), (MtxPtr)(geo + 0x18));
        PSMTXConcat((MtxPtr)cam1, (MtxPtr)(geo + 0x18), (MtxPtr)(geo + 0x18));
        PSMTXConcat((MtxPtr)cam2, (MtxPtr)(geo + 0x18), concat);

        {
            f32 *b = (f32 *)(geo + 0x54);
            box[0] = b[1];
            box[1] = b[3];
            box[2] = b[4];
            box[3] = b[0];
            box[4] = b[3];
            box[5] = b[4];
            box[6] = b[0];
            box[7] = b[3];
            box[8] = b[5];
            box[9] = b[1];
            box[10] = b[3];
            box[11] = b[5];
            box[12] = b[1];
            box[13] = b[2];
            box[14] = b[4];
            box[15] = b[0];
            box[16] = b[2];
            box[17] = b[4];
            box[18] = b[0];
            box[19] = b[2];
            box[20] = b[5];
            box[21] = b[1];
            box[22] = b[2];
            box[23] = b[5];
        }

        if (checkObjectVisibility(0, box, concat)) {
            va_list args;
            va_start(args, count);
            *(s16 *)(lbl_1_common_bss_472B4 + 0x22c) = *(s16 *)(lbl_1_common_bss_472B4 + 0x22c) + 1;
            DOVARender(geo, (MtxPtr)cam2, (u8)count, args);
        }
    }

    if (lbl_1_bss_C1 != 0) {
        sel = *(s16 *)(lbl_1_common_bss_472B4 + 0x22e);
        end = *(u16 *)(items + 6);
        if (sel < 0) {
            start = 0;
        } else {
            start = sel;
            end = sel + 1;
        }

        flags = lbl_1_bss_2E0 + start;
        e = items + start * 0x1c;
        for (i = start; i < end; i++, flags++, e += 0x1c) {
            if (*flags != 0) {
                continue;
            }
            f34 = *(u16 *)(e + 0x34);
            if (f34 == 0xffff) {
                continue;
            }

            lut = *(u8 **)(mid + 0x10);
            geo = *(u8 **)(lut + (f34 << 3));
            CTRLBuildMatrix(*(Control **)(e + 0x20), (MtxPtr)(geo + 0x18));
            PSMTXConcat((MtxPtr)cam1, (MtxPtr)(geo + 0x18), (MtxPtr)(geo + 0x18));
            PSMTXConcat((MtxPtr)cam2, (MtxPtr)(geo + 0x18), concat);

            {
                f32 *b = (f32 *)(geo + 0x54);
                box[0] = b[1];
                box[1] = b[3];
                box[2] = b[4];
                box[3] = b[0];
                box[4] = b[3];
                box[5] = b[4];
                box[6] = b[0];
                box[7] = b[3];
                box[8] = b[5];
                box[9] = b[1];
                box[10] = b[3];
                box[11] = b[5];
                box[12] = b[1];
                box[13] = b[2];
                box[14] = b[4];
                box[15] = b[0];
                box[16] = b[2];
                box[17] = b[4];
                box[18] = b[0];
                box[19] = b[2];
                box[20] = b[5];
                box[21] = b[1];
                box[22] = b[2];
                box[23] = b[5];
            }

            if (checkObjectVisibility(0, box, concat)) {
                fn_1_4E98(geo, cam2);
            }
        }
    }
}

// .text:0x000077EC size:0x5C
void fn_1_77EC(s32 arg0) {
    GXSetCullMode(*(GXCullMode *)lbl_1_data_8C4);
    fn_1_73B8(arg0, 3, lbl_1_data_848[0], lbl_1_data_848[1], lbl_1_data_848[2]);
}

// .text:0x00007848 size:0x24
void fn_1_7848(void) {
    fn_80048C28();
    fn_80048C1C();
}

// .text:0x0000786C size:0x78
void fn_1_786C(void) {
    fn_80048D4C();
    GXSetCopyClear(lbl_1_data_858, 0xffffff);
    SetFog(lbl_1_bss_4E0->color.a, lbl_1_bss_4E0->color, lbl_1_bss_4E0->nearZ, lbl_1_bss_4E0->farZ, lbl_1_rodata_1D8, lbl_1_rodata_208);
}

// .text:0x000078E4 size:0x7C
void fn_1_78E4(void) {
    GXSetCopyClear(lbl_1_data_858, 0xffffff);
    if (lbl_1_bss_C4) {
        GXSetCullMode(0);
    } else {
        GXSetCullMode(2);
    }
    SetFogNoneAgain();
    GXSetAlphaCompare(4, 0, 0, 7, 0);
}

// .text:0x00007960 size:0x4A4
void fn_1_7960(void) {
    u8 *btn = (u8 *)&AtBat_ButtonInput1;
    u8 *base = lbl_1_common_bss_472B4;
    Vec templatePt = lbl_1_rodata_188;
    s8 b10 = *(s8 *)(btn + 0x10);
    s8 b11 = *(s8 *)(btn + 0x11);
    f32 t34 = (f32)b10 / lbl_1_rodata_20C;
    s8 b12 = *(s8 *)(btn + 0x12);
    u16 flag0 = *(u16 *)(btn + 0);
    s8 b13 = *(s8 *)(btn + 0x13);
    u16 f30v = *(u16 *)(base + 0x30) - (u16)(b13 * 2);
    u16 f32v = *(u16 *)(base + 0x32) + (u16)(b12 * 2);
    f32 t38 = (f32)b11 * lbl_1_rodata_210;
    Vec vec;
    Mtx rotX;
    Mtx rotY_m;
    Mtx combined;
    f32 *up = (f32 *)(base + 0x3c);
    f32 *eye = (f32 *)(base + 0x48);
    f32 dz, dx, s48, s50, s40, vx, s44;
    f32 inv;
    Mtx44 frustum;
    s32 i;

    *(u16 *)(base + 0x30) = f30v;
    *(u16 *)(base + 0x32) = f32v;
    *(f32 *)(base + 0x34) = t34;
    *(f32 *)(base + 0x38) = t38;

    if (flag0 & 0x10) {
        u8 b14 = *(u8 *)(btn + 0x14);
        u8 b15 = *(u8 *)(btn + 0x15);
        f32 v = *(f32 *)(base + 0x54) - (f32)b14 / lbl_1_rodata_214;
        *(f32 *)(base + 0x54) = v;
        *(f32 *)(base + 0x54) = v + (f32)b15 / lbl_1_rodata_214;
    } else {
        u8 b15 = *(u8 *)(btn + 0x15);
        u8 b14 = *(u8 *)(btn + 0x14);
        *(f32 *)(base + 0x4c) -= (f32)b15 * lbl_1_rodata_218;
        *(f32 *)(base + 0x4c) += (f32)b14 * lbl_1_rodata_218;
    }

    vec.x = (f32)(u16)f30v;
    vec.y = (f32)(u16)f32v;
    vec.z = lbl_1_rodata_1A8;
    PSVECScale(&vec, lbl_1_rodata_204, &vec);
    PSMTXRotRad(rotX, 'X', vec.x);
    PSMTXRotRad(rotY_m, 'Y', vec.y);
    PSMTXConcat(rotY_m, rotX, combined);
    PSMTXMultVec(combined, &templatePt, (Vec *)up);

    dz = *(f32 *)(base + 0x34) * rotY_m[0][0];
    dx = *(f32 *)(base + 0x34) * rotY_m[0][2];
    dz = *(f32 *)(base + 0x38) * rotY_m[0][2] - dz;
    dx = *(f32 *)(base + 0x38) * rotY_m[0][0] + dx;
    s48 = eye[0] + dz;
    s50 = eye[2] + dx;
    s40 = *(f32 *)(base + 0x40) + *(f32 *)(base + 0x4c);
    vx = up[0] + s48;
    s44 = *(f32 *)(base + 0x44) + s50;
    eye[0] = s48;
    eye[2] = s50;
    up[0] = vx;
    *(f32 *)(base + 0x40) = s40;
    *(f32 *)(base + 0x44) = s44;
    makeLookAtMatrix((MtxPtr)base, (Vec *)eye, &lbl_1_data_87C, (Vec *)up);

    inv = lbl_1_rodata_1D8 / *(f32 *)(base + 0x54);
    C_MTXFrustum(frustum, lbl_1_rodata_21C * inv, lbl_1_rodata_220 * inv, lbl_1_rodata_224 * inv, lbl_1_rodata_228 * inv, lbl_1_rodata_1D8, lbl_1_rodata_208);
    GXSetProjection(frustum, GX_PERSPECTIVE);
    fn_800B806C(0, lbl_1_rodata_22C * inv, lbl_1_rodata_230 * inv, lbl_1_rodata_234 * inv, lbl_1_rodata_238 * inv, lbl_1_rodata_23C, lbl_1_rodata_240, lbl_1_rodata_244);

    for (i = 0; i < 3; i++) {
        LITXForm(lbl_1_data_848[i], base);
    }
    fn_80011640(base, base);

    if (lbl_1_bss_C0) {
        s32 x = (s32)(65535 - *(u16 *)(base + 0x32));
        s16 y = *(s16 *)(base + 0x30);
        fn_800B9950(3, (f32)x / lbl_1_rodata_248, (f32)y / lbl_1_rodata_248);
    } else {
        fn_800B9950(3, lbl_1_rodata_1A8, lbl_1_rodata_1A8);
    }
}

// .text:0x00007E04 size:0xF4
void fn_1_7E04(f32 arg0) {
    Mtx44 frustum;
    f32 inv = lbl_1_rodata_1D8 / arg0;

    C_MTXFrustum(frustum, lbl_1_rodata_21C * inv, lbl_1_rodata_220 * inv, lbl_1_rodata_224 * inv, lbl_1_rodata_228 * inv, lbl_1_rodata_1D8, lbl_1_rodata_208);
    GXSetProjection(frustum, GX_PERSPECTIVE);
    fn_800B806C(0, lbl_1_rodata_22C * inv, lbl_1_rodata_230 * inv, lbl_1_rodata_234 * inv, lbl_1_rodata_238 * inv, lbl_1_rodata_23C, lbl_1_rodata_240, lbl_1_rodata_244);
}

// .text:0x00007EF8 size:0x100
void fn_1_7EF8(void) {
    u16 val = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

    switch (val) {
        case 4:
        case 8:
            lbl_1_bss_C2 = !lbl_1_bss_C2;
            break;
        case 1:
            fn_80048E00(lbl_1_bss_C2, fn_80048EA8(lbl_1_bss_C2) - 1);
            break;
        case 2:
            fn_80048E00(lbl_1_bss_C2, fn_80048EA8(lbl_1_bss_C2) + 1);
            break;
        case 0x100:
            lbl_1_data_85C = !lbl_1_data_85C;
            if (lbl_1_data_85C) {
                fn_80048C14(0x3f);
            } else {
                fn_80048C14(0);
            }
            break;
    }
}

// .text:0x00007FF8 size:0x370
void fn_1_7FF8(void) {
    u16 val = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
    u8 *p;
    s8 mode;

    switch (val) {
        case 8: {
            s8 v;
            p = lbl_1_common_bss_472B4;
            v = p[0x23c] - 1;
            p[0x23c] = v;
            if (v < 0) {
                p[0x23c] = 5;
            }
            break;
        }
        case 4: {
            s8 v;
            p = lbl_1_common_bss_472B4;
            v = p[0x23c] + 1;
            p[0x23c] = v;
            if (v >= 6) {
                p[0x23c] = 0;
            }
            break;
        }
        case 1:
            p = lbl_1_common_bss_472B4;
            mode = (s8)p[0x23c];
            switch (mode) {
                case 0: {
                    u8 v = --lbl_1_bss_4E0->color.a;
                    switch (v) {
                        case 0xff:
                            lbl_1_bss_4E0->color.a = 7;
                            break;
                        case 3:
                            lbl_1_bss_4E0->color.a = 2;
                            break;
                        case 1:
                            lbl_1_bss_4E0->color.a = 0;
                            break;
                    }
                    break;
                }
                case 1:
                    lbl_1_bss_4E0->color.r--;
                    break;
                case 2:
                    lbl_1_bss_4E0->color.g--;
                    break;
                case 3:
                    lbl_1_bss_4E0->color.b--;
                    break;
                case 4: {
                    f32 nz = lbl_1_bss_4E0->nearZ - lbl_1_rodata_1D8;
                    lbl_1_bss_4E0->nearZ = nz;
                    if (nz < lbl_1_rodata_1A8) {
                        lbl_1_bss_4E0->nearZ = lbl_1_rodata_1A8;
                    }
                    break;
                }
                case 5: {
                    f32 fz = lbl_1_bss_4E0->farZ - lbl_1_rodata_1D8;
                    lbl_1_bss_4E0->farZ = fz;
                    if (fz < lbl_1_rodata_1A8) {
                        lbl_1_bss_4E0->farZ = lbl_1_rodata_1A8;
                    }
                    break;
                }
            }
            break;
        case 2:
            p = lbl_1_common_bss_472B4;
            mode = (s8)p[0x23c];
            switch (mode) {
                case 0: {
                    u8 v = ++lbl_1_bss_4E0->color.a;
                    switch (v) {
                        case 1:
                            lbl_1_bss_4E0->color.a = 2;
                            break;
                        case 3:
                            lbl_1_bss_4E0->color.a = 4;
                            break;
                        case 8:
                            lbl_1_bss_4E0->color.a = 0;
                            break;
                    }
                    break;
                }
                case 1:
                    lbl_1_bss_4E0->color.r++;
                    break;
                case 2:
                    lbl_1_bss_4E0->color.g++;
                    break;
                case 3:
                    lbl_1_bss_4E0->color.b++;
                    break;
                case 4: {
                    f32 nz = lbl_1_bss_4E0->nearZ + lbl_1_rodata_1D8;
                    lbl_1_bss_4E0->nearZ = nz;
                    if (nz > lbl_1_rodata_208) {
                        lbl_1_bss_4E0->nearZ = lbl_1_rodata_208;
                    }
                    break;
                }
                case 5: {
                    f32 fz = lbl_1_bss_4E0->farZ + lbl_1_rodata_1D8;
                    lbl_1_bss_4E0->farZ = fz;
                    if (fz > lbl_1_rodata_208) {
                        lbl_1_bss_4E0->farZ = lbl_1_rodata_208;
                    }
                    break;
                }
            }
            break;
    }
}

// .text:0x00008368 size:0x240
void fn_1_8368(void) {
    u8 *btn = (u8 *)&AtBat_ButtonInput1;
    u8 *p = lbl_1_common_bss_472B4;
    u16 val = *(u16 *)(btn + 4);
    s16 idx;
    s8 b0;
    s8 b1;
    s8 b2;
    s8 b3;
    u8 c0;
    u8 c1;
    u16 flag;

    if (val & 1) {
        idx = *(s16 *)(p + 0x22e) - 1;
        *(s16 *)(p + 0x22e) = idx;
        if (idx < -1) {
            *(s16 *)(p + 0x22e) = *(s16 *)(p + 0x228) - 1;
        }
    } else if (val & 2) {
        idx = *(s16 *)(p + 0x22e) + 1;
        *(s16 *)(p + 0x22e) = idx;
        if (idx >= *(s16 *)(p + 0x228)) {
            *(s16 *)(p + 0x22e) = -1;
        }
    } else {
        u16 val2 = *(u16 *)(btn + 2);
        if (val2 & 0x400) {
            p[0x239] ^= 1;
        } else if (val2 & 0x100) {
            p[0x238] ^= 1;
        }
    }

    b0 = *(s8 *)(btn + 0x10);
    b1 = *(s8 *)(btn + 0x11);
    b2 = *(s8 *)(btn + 0x12);
    b3 = *(s8 *)(btn + 0x13);
    lbl_1_data_200[0] += (f32)b0 * lbl_1_rodata_210;
    lbl_1_data_200[2] += (f32)b1 * lbl_1_rodata_210;
    flag = *(u16 *)(btn + 0);
    lbl_1_data_200[3] += (f32)b2 * lbl_1_rodata_210;
    lbl_1_data_200[5] += (f32)b3 * lbl_1_rodata_210;

    c0 = *(u8 *)(btn + 0x15);
    c1 = *(u8 *)(btn + 0x14);
    if (!(flag & 0x100)) {
        lbl_1_data_200[1] -= (f32)c0 * lbl_1_rodata_218;
        lbl_1_data_200[1] += (f32)c1 * lbl_1_rodata_218;
    } else {
        lbl_1_data_200[4] -= (f32)c0 * lbl_1_rodata_218;
        lbl_1_data_200[4] += (f32)c1 * lbl_1_rodata_218;
    }
}
