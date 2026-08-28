#include "debug/rep_7730.h"
#include "header_rep_data.h"
#include "Unknown/File_0x800b0a14.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/GX/GXGeometry.h"
#include "Dolphin/GX/GXLight.h"
#include "Dolphin/GX/GXTev.h"
#include "Dolphin/GX/GXTransform.h"
#include "Dolphin/GX/GXTexture.h"
#include "Dolphin/GX/GXFifo.h"
#include "Dolphin/GX/GXFrameBuffer.h"
#include "Dolphin/mtx.h"
#include "Dolphin/mtxext.h"
#include "Dolphin/os.h"
#include "C3/control.h"
#include "stl/math.h"
#include "Unknown/File_0x80024184.h"
#include "Dolphin/GX/GXPixel.h"
#include "stl/mem.h"
#include "Dolphin/rand.h"
#include "text/text_channel.h"

#define GFX_OBJ(item) \
    ((u8 *)graphicsRelatedArray[*(u16 *)(*(u8 **)((u8 *)(item) + 0x14) + 0x14)].object)

extern void *ARAMTransfer(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern void fn_80037B18(void *arg0, void *arg1);
extern void fn_1_272DC(void *arg0, s32 arg1);
extern void fn_1_AF4(s32 arg0, s32 arg1, f32 arg2);
extern void fn_80048C14(s32 arg0);
extern void fn_80048E00(s32 arg0, s32 arg1);
extern void fn_800AD038(void *arg0);
extern s32 fn_800B24D4(s32 arg0);
extern void fn_800B1188(void);
extern void fn_800A7D4C(s32 arg0, void *arg1);
extern s32 diskReadRelated(void *arg0, s32 arg1);
extern void addGraphicsElementToScene(void *arg0);
extern s32 fn_80035DD4(s32 arg0);
extern void fn_800385F0(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
extern void fn_1_273D8(void *arg0);

extern f32 lbl_1_bss_6BE4[4];
extern u8 lbl_1_bss_6BF4[0x154];
extern u8 lbl_1_data_10674[0x150];
extern void (*lbl_1_data_1066C[])(s16);
extern u8 lbl_1_bss_6D48[0xFC];
extern f32 lbl_1_rodata_77E4;
extern u8 lbl_803C6CF8[0x708];
extern u8 lbl_1_data_104F4[0x14];
extern Mtx44 lbl_1_bss_47010;
extern f32 lbl_1_rodata_77D8;
extern f32 lbl_1_rodata_77DC;
extern f32 lbl_1_rodata_77E0;
extern f32 lbl_1_rodata_7804;
extern f32 lbl_1_rodata_7814;
extern f32 lbl_1_rodata_7820;
extern f32 lbl_1_rodata_7858;
extern f32 lbl_1_rodata_785C;
extern f32 lbl_1_rodata_7860;
extern f32 lbl_1_rodata_7864;
extern f32 lbl_1_rodata_7868;
extern u8 lbl_80366158[0x30];
extern u8 drawStadiumRelated;
extern u8 lbl_1_data_107E4[0x38];
extern u8 lbl_1_data_107C4[0x20];
extern u8 lbl_1_data_FB98[0x7AC];
extern u8 lbl_803C4BE0[0x4B0];
extern void (*lbl_1_data_104A8[])(void);
extern f32 lbl_1_rodata_780C;
extern f32 lbl_1_rodata_7890;
extern void removeGraphicsElementFromScene(void *arg0);
extern void fn_8000CEF0(void *arg0);
extern void fn_80035A00(void);
extern u8 lbl_1_data_10344[0x40];
extern s32 lbl_1_bss_6BDC;
extern Mtx lbl_1_rodata_7780;
extern f32 lbl_1_rodata_78E4;
extern f32 lbl_1_rodata_78E8;
extern f32 lbl_1_rodata_78EC;
extern f32 lbl_1_rodata_7844;
extern f32 lbl_1_rodata_7848;
extern u8 lbl_1_bss_6BD8[0x500];
extern f32 lbl_1_rodata_784C;
extern f32 lbl_1_rodata_7810;
extern u8 lbl_1_bss_43F68[0x1900];
extern f32 lbl_1_rodata_77F8;
extern f32 lbl_1_rodata_7800;
extern f32 lbl_1_rodata_7854;
extern void fn_80038E2C(void *arg0);
extern void fn_80048C1C(void);
extern void fn_80048D4C(void);
extern void fn_80048C28(void);
extern void (*lbl_1_data_10508[])(DrawingSceneStruct *arg0);
extern void (*lbl_1_data_10510[])(DrawingSceneStruct *arg0);
extern u8 lbl_1_bss_6FE0[0x500];
extern u32 lbl_1_data_104DC[6];
extern u8 lbl_1_bss_45868[0x17A8];
extern f64 lbl_1_rodata_7878;
extern f64 lbl_1_rodata_7880;
extern f64 lbl_1_rodata_7888;

extern void LITAlloc(void *slot);
extern void LITInitAttn(void *light, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
extern void LITInitPos(void *light, f32 arg1, f32 arg2, f32 arg3);
extern void LITInitDir(void *light, f32 arg1, f32 arg2, f32 arg3);
extern void LITInitColor(void *light, GXColor *color);
extern void *ActorObjectInitTable(s32 arg0, u32 arg1, void *arg2);
extern void LoadActorLayout(void *arg0);
extern void convertGeometryAndSknHeader(void *arg0, s32 arg1);
extern void animateBallRelated(void *arg0, s32 arg1, s32 arg2, void *arg3, s32 arg4, s32 arg5);
extern void fn_800B2C08(void *arg0, s32 arg1);
extern void fn_800BD548(void *arg0, s32 arg1, void *arg2);
extern void haveActLayoutPointToGeoHeader(void *arg0, void *arg1);

extern u8 lbl_1_bss_6FA4[0x14];
extern void *lbl_1_bss_6BE0;
extern u32 lbl_1_rodata_77B0;
extern f32 lbl_1_rodata_7840;
extern GXTexObj lbl_1_bss_6EA4[8];
extern GXTlutObj lbl_1_bss_6E44[8];
extern f32 lbl_1_rodata_78C4;
extern f32 lbl_1_rodata_78C8;
extern f32 lbl_1_rodata_78CC;
extern f32 lbl_1_rodata_78D0;
extern f32 lbl_1_rodata_7808;
extern u8 lbl_1_data_10384[0x120];
extern f32 lbl_1_data_104A4;
extern f32 lbl_1_rodata_78A4;
extern f32 lbl_1_rodata_78D4;
extern f32 lbl_1_rodata_78D8;
extern f32 lbl_1_rodata_78DC;
extern f32 lbl_1_rodata_78E0;
extern u8 lbl_1_bss_6FB8[0x28];
extern f32 lbl_1_rodata_786C;
extern f64 lbl_1_rodata_7870;
extern s16 (*lbl_1_data_10668[])(s16 arg0);
extern s32 lbl_1_data_10670[];
extern void fn_1_26D28(void *arg0, u16 arg1, u16 arg2, u16 arg3, void *arg4);
extern void fn_1_27330(void *arg0);
extern void fn_80037BAC(void *arg0);
extern s32 fn_80048EA8(s32 arg0);
extern u8 lbl_1_bss_43EE0[0x88];
extern void fn_80038B48(void *arg0, void *arg1, s32 arg2, void *arg3);
extern void fn_80038CD0(u8 arg0, void *arg1, void *arg2, f32 arg3, f32 arg4);
extern void convertTextureHeader(void *arg0);
extern u8 lbl_1_data_10518[0x150];
extern void fn_800BDA24(void *arg0);
extern void fn_800BD670(void *arg0, void *arg1);
extern f64 lbl_1_rodata_7818;
extern f64 lbl_1_rodata_7828;
extern f64 lbl_1_rodata_7830;
extern f64 lbl_1_rodata_7838;
extern f32 lbl_1_data_104D0[3];
extern f32 lbl_1_rodata_78BC;
extern f32 lbl_1_rodata_78AC;
extern f32 lbl_1_rodata_78B0;
extern f32 lbl_1_rodata_78B4;
extern f32 lbl_1_rodata_78B8;
extern f32 lbl_1_rodata_78C0;
extern f32 lbl_1_bss_74E0[0x80];
extern f32 lbl_1_bss_76E0[0x2000];
extern void *_OSAllocFromHeap(s32 arg0, s32 arg1);
extern void fn_80023F0C(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
extern void SetDisplayStateTexture(void *arg0, s32 arg1, s32 arg2);
extern f32 lbl_1_rodata_77E8;
extern u8 lbl_1_bss_F6E0[0x34800];
extern f32 lbl_1_rodata_7894;
extern f32 lbl_1_rodata_7898;
extern f32 lbl_1_rodata_77FC;
extern void fn_1_F2C(s32 arg0);

// .text:0x0001D694 size:0x2B0
void fn_1_1D694(void *arg0) {
    u8 *base = arg0;

    if (*(base + 0x18) != 0) {
        u8 *tex = *(u8 **)(base + 0x8);
        u8 *buf1 = *(u8 **)(base + 0x10);
        u8 *buf2;
        s32 cols;
        s32 rows;
        s32 colOff = 0;
        s32 rowBase = 0;
        s32 i;

        buf2 = *(u8 **)(base + 0xc);
        memset(*(void **)tex, 0, (u32)(*(u16 *)(tex + 0xa)) * (u32)(*(u16 *)(tex + 0x8)));

        cols = (*(u16 *)(tex + 0x8) + 63) / 64;
        rows = (*(u16 *)(tex + 0xa) + 31) / 32;

        for (i = 0; i < cols; i++) {
            u8 *rowPtr = buf1 + rowBase;
            s32 pixOff = 0;
            s32 j;

            for (j = 0; j < rows; j++) {
                if ((j & drawStadiumRelated) != 0) {
                    u8 pixel = *rowPtr;
                    s32 band = pixel / rows;
                    s32 rem = pixel - band * rows;

                    fn_80023F0C(buf2, tex, rem * 32, band * 64, 0x20, 0x40, pixOff, colOff);
                }

                pixOff += 0x20;
                rowPtr += 1;
            }

            colOff += rows;
            rowBase += 0x40;
        }

        DCStoreRange(*(void **)tex, (u32)(*(u16 *)(tex + 0xa)) * (u32)(*(u16 *)(tex + 0x8)));
    }

    {
        f32 z = lbl_1_rodata_77D8;
        Mtx44 mtx;
        Mtx mtx2;

        C_MTXOrtho(mtx, z, lbl_1_rodata_77DC, z, lbl_1_rodata_77E0, z, lbl_1_rodata_77E4);
        PSMTXIdentity(mtx2);
        GXSetProjection(mtx, 1);
        GXLoadPosMtxImm(mtx2, 0);
        GXSetCurrentMtx(0);
        gOz_GXSetTexture(0, 0, 0);
        SetDisplayStateTexture(*(void **)(base + 0x8), 0, 0);

        GXBegin(GX_QUADS, GX_VTXFMT0, 4);

        GX_WRITE_F32(lbl_1_rodata_77D8);
        GX_WRITE_F32(lbl_1_rodata_77D8);
        GX_WRITE_F32(lbl_1_rodata_77E8);
        GX_WRITE_U32(-1);
        GX_WRITE_U16(0);
        GX_WRITE_U16(0);

        GX_WRITE_F32((f32)(*(u16 *)(*(u8 **)(base + 0x8) + 0x8)));
        GX_WRITE_F32(lbl_1_rodata_77D8);
        GX_WRITE_F32(lbl_1_rodata_77E8);
        GX_WRITE_U32(-1);
        GX_WRITE_U16(0);
        GX_WRITE_U16(1);

        GX_WRITE_F32((f32)(*(u16 *)(*(u8 **)(base + 0x8) + 0xa)));
        GX_WRITE_F32((f32)(*(u16 *)(*(u8 **)(base + 0x8) + 0x8)));
        GX_WRITE_F32(lbl_1_rodata_77E8);
        GX_WRITE_U32(-1);
        GX_WRITE_U16(1);
        GX_WRITE_U16(1);

        GX_WRITE_F32((f32)(*(u16 *)(*(u8 **)(base + 0x8) + 0xa)));
        GX_WRITE_F32(lbl_1_rodata_77D8);
        GX_WRITE_F32(lbl_1_rodata_77E8);
        GX_WRITE_U32(-1);
        GX_WRITE_U16(1);
        GX_WRITE_U16(0);
    }
}

// .text:0x0001D944 size:0x110
void fn_1_1D944(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    u16 mod;

    if (AtBat_ButtonInput1._02 & 0x200) {
        fn_800AD038(*(void **)(lbl_80366158 + 0x8));
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        return;
    }

    if (--(*(u16 *)((u8 *)item + 0x20)) == 0) {
        *(u16 *)((u8 *)item + 0x20) = *(u16 *)((u8 *)item + 0x22);
        mod = (*(u16 *)((u8 *)item + 0x1e) + 1) % *(u16 *)((u8 *)item + 0x1c);
        *(u16 *)((u8 *)item + 0x1e) = mod;
    }

    {
        u8 *elem = lbl_1_data_107E4 + drawStadiumRelated * 0x1c;

        *(void **)(elem + 0xc) = (u8 *)(*(void **)((u8 *)item + 0x18)) +
            ((*(u16 *)((u8 *)item + 0x28) + *(u16 *)((u8 *)item + 0x1e)) << 5) + 4;
        *(u16 *)(elem + 0x14) = *(u16 *)((u8 *)item + 0x24);
        *(u16 *)(elem + 0x16) = *(u16 *)((u8 *)item + 0x26);
        elem[0x18] = 1;
        *(void **)(elem + 0x10) = lbl_1_data_107C4;
        *(u32 *)(elem + 0x8) = *(u32 *)((u8 *)item + 0x2c);
        fn_800A7D4C(0, elem);
    }
}

// .text:0x0001DA54 size:0x290
void fn_1_1DA54(void) {
    DrawingSceneStruct *item = currentDrawingItem;

    if ((s8)lbl_803C6CF8[0x715] != 1) {
        return;
    }

    {
        u8 *hdr = *(u8 **)((u8 *)item + 0x14);
        u8 *info;
        u32 size;

        *(void **)((u8 *)item + 0x18) = hdr + *(u32 *)(hdr + 0x14);
        convertTextureHeader(*(void **)((u8 *)item + 0x18));

        *(u16 *)((u8 *)item + 0x28) = 2;
        *(u16 *)((u8 *)item + 0x1c) = 3;
        *(u16 *)((u8 *)item + 0x1e) = 0;
        *(u16 *)((u8 *)item + 0x22) = 3;
        *(u16 *)((u8 *)item + 0x20) = 3;
        *(u16 *)((u8 *)item + 0x24) = 0;
        *(u16 *)((u8 *)item + 0x26) = 0;

        info = _OSAllocFromHeap(0x20, 0x20);
        *(void **)((u8 *)item + 0x2c) = info;
        memcpy(info, *(u8 **)((u8 *)item + 0x18) + 0x44, 0x20);

        info = *(u8 **)((u8 *)item + 0x2c);

        if (*(u32 *)(info + 0x4) != 0) {
            if ((s8)info[0x1a] >= 0 && (s8)info[0x1a] < 3) {
                u16 count = *(u16 *)(info + 0x18);

                size = (u32)count * 2;
                *(void **)(info + 0x4) = _OSAllocFromHeap(0x20, size);
                memcpy(*(void **)(info + 0x4), *(u8 **)((u8 *)item + 0x18) + 0x48, size);
            }

            DCStoreRangeNoSync(*(void **)(info + 0x4), size);

            switch (info[0x17]) {
            case 8: {
                s32 h = *(u16 *)(info + 0xa);
                s32 w = *(u16 *)(info + 0x8);
                u32 hBlocks = ((h + 7) / 8) * 8;
                u32 wBlocks = ((w + 7) / 8) * 8;

                size = hBlocks * wBlocks;
                break;
            }
            case 9: {
                s32 h = *(u16 *)(info + 0xa);
                s32 w = *(u16 *)(info + 0x8);
                u32 hBlocks = ((h + 7) / 8) * 8;
                u32 wBlocks = ((w + 3) / 4) * 4;

                size = hBlocks * wBlocks;
                break;
            }
            default:
                fn_800AD038(*(void **)(lbl_80366158 + 0x8));
                currentDrawingItem->currentDrawingItem->state = 1;
                removeCurrentDrawingItem();
                return;
            }
        } else {
            if (info[0x17] == 0xe) {
                s32 h = *(u16 *)(info + 0xa);
                s32 w = *(u16 *)(info + 0x8);
                u32 hBlocks = ((h + 7) / 8) * 8;
                u32 wBlocks = ((w + 7) / 8) * 8;

                size = hBlocks * wBlocks;
            } else {
                fn_800AD038(*(void **)(lbl_80366158 + 0x8));
                currentDrawingItem->currentDrawingItem->state = 1;
                removeCurrentDrawingItem();
                return;
            }
        }

        *(void **)(info + 0x0) = _OSAllocFromHeap(0x20, size);
        memcpy(*(void **)(info + 0x0), *(u8 **)((u8 *)item + 0x18) + 0x44, size);
        DCStoreRangeNoSync(*(void **)(info + 0x0), size);
        PPCSync();

        currentDrawingItem->func = fn_1_1D944;
    }
}

// .text:0x0001DCE4 size:0x64
void fn_1_1DCE4(void) {
    DrawingSceneStruct *item = currentDrawingItem;

    *(void **)((u8 *)item + 0x14) = ARAMTransfer(lbl_1_data_10674, 0, 0, 0);
    currentDrawingItem->func = fn_1_1DA54;
}

// .text:0x0001DD48 size:0x4C
f32 fn_1_1DD48(u16 flags, s32 neg, f32 value, f32 opt1, f32 def, f32 opt2, f32 lo, f32 hi) {
    f32 offset = def;

    if (flags & 0x40) {
        offset = opt1;
    } else if (flags & 0x20) {
        offset = opt2;
    }

    if (neg != 0) {
        offset = -offset;
    }

    value += offset;
    if (value < lo) {
        value = lo;
    }

    if (value > hi) {
        return hi;
    }

    return value;
}

// .text:0x0001DD94 size:0x50
void fn_1_1DD94(void) {
    f32 v[3];

    v[0] = lbl_1_bss_6BE4[1];
    v[1] = lbl_1_bss_6BE4[2];
    v[2] = lbl_1_bss_6BE4[3];
    fn_80037B18(lbl_1_bss_6BF4, v);
}

// .text:0x0001DDE4 size:0x10
void fn_1_1DDE4(f32 arg0) {
    lbl_1_bss_6BE4[3] = arg0;
}

// .text:0x0001DDF4 size:0x10
void fn_1_1DDF4(f32 arg0) {
    lbl_1_bss_6BE4[2] = arg0;
}

// .text:0x0001DE04 size:0x10
void fn_1_1DE04(f32 arg0) {
    lbl_1_bss_6BE4[1] = arg0;
}

// .text:0x0001DE14 size:0xC
void fn_1_1DE14(f32 arg0) {
    lbl_1_bss_6BE4[0] = arg0;
}

// .text:0x0001DE20 size:0x10
f32 fn_1_1DE20(void) {
    return lbl_1_bss_6BE4[3];
}

// .text:0x0001DE30 size:0x10
f32 fn_1_1DE30(void) {
    return lbl_1_bss_6BE4[2];
}

// .text:0x0001DE40 size:0x10
f32 fn_1_1DE40(void) {
    return lbl_1_bss_6BE4[1];
}

// .text:0x0001DE50 size:0xC
f32 fn_1_1DE50(void) {
    return lbl_1_bss_6BE4[0];
}

// .text:0x0001DE5C size:0x4
void fn_1_1DE5C(void) {
    return;
}

// .text:0x0001DE60 size:0x42C
s32 fn_1_1DE60(s32 arg0, u16 arg1, u32 arg2, u16 flags) {
    s16 mode;

    if ((s16)arg0 < 0) {
        return arg0;
    }
    mode = (s16)arg0;
    if (mode >= 4) {
        return arg0;
    }

    if (flags & 1) {
        switch (mode) {
        case 0: {
            f32 delta = lbl_1_rodata_77F8;
            f32 v = lbl_1_bss_6BE4[0];
            if (arg1 & 0x40) {
                delta = lbl_1_rodata_77FC;
            } else if (arg1 & 0x20) {
                delta = lbl_1_rodata_7800;
            }
            delta = -delta;
            v += delta;
            if (v < lbl_1_rodata_77D8) {
                v = lbl_1_rodata_77D8;
            }
            if (v > lbl_1_rodata_77E4) {
                v = lbl_1_rodata_77E4;
            }
            lbl_1_bss_6BE4[0] = v;
            break;
        }
        case 1: {
            f32 delta = lbl_1_rodata_77F8;
            f32 v = lbl_1_bss_6BE4[1];
            if (arg1 & 0x40) {
                delta = lbl_1_rodata_77FC;
            } else if (arg1 & 0x20) {
                delta = lbl_1_rodata_7800;
            }
            delta = -delta;
            v += delta;
            if (v < lbl_1_rodata_7804) {
                v = lbl_1_rodata_7804;
            }
            if (v > lbl_1_rodata_7808) {
                v = lbl_1_rodata_7808;
            }
            lbl_1_bss_6BE4[1] = v;
            break;
        }
        case 2: {
            f32 delta = lbl_1_rodata_77F8;
            f32 v = lbl_1_bss_6BE4[2];
            if (arg1 & 0x40) {
                delta = lbl_1_rodata_77FC;
            } else if (arg1 & 0x20) {
                delta = lbl_1_rodata_7800;
            }
            delta = -delta;
            v += delta;
            if (v < lbl_1_rodata_7804) {
                v = lbl_1_rodata_7804;
            }
            if (v > lbl_1_rodata_7808) {
                v = lbl_1_rodata_7808;
            }
            lbl_1_bss_6BE4[2] = v;
            break;
        }
        case 3: {
            f32 delta = lbl_1_rodata_77F8;
            f32 v = lbl_1_bss_6BE4[3];
            if (arg1 & 0x40) {
                delta = lbl_1_rodata_77FC;
            } else if (arg1 & 0x20) {
                delta = lbl_1_rodata_7800;
            }
            delta = -delta;
            v += delta;
            if (v < lbl_1_rodata_7804) {
                v = lbl_1_rodata_7804;
            }
            if (v > lbl_1_rodata_7808) {
                v = lbl_1_rodata_7808;
            }
            lbl_1_bss_6BE4[3] = v;
            break;
        }
        }
    } else if (flags & 2) {
        switch (mode) {
        case 0: {
            f32 delta = lbl_1_rodata_77F8;
            f32 v = lbl_1_bss_6BE4[0];
            if (arg1 & 0x40) {
                delta = lbl_1_rodata_77FC;
            } else if (arg1 & 0x20) {
                delta = lbl_1_rodata_7800;
            }
            v += delta;
            if (v < lbl_1_rodata_77D8) {
                v = lbl_1_rodata_77D8;
            }
            if (v > lbl_1_rodata_77E4) {
                v = lbl_1_rodata_77E4;
            }
            lbl_1_bss_6BE4[0] = v;
            break;
        }
        case 1: {
            f32 delta = lbl_1_rodata_77F8;
            f32 v = lbl_1_bss_6BE4[1];
            if (arg1 & 0x40) {
                delta = lbl_1_rodata_77FC;
            } else if (arg1 & 0x20) {
                delta = lbl_1_rodata_7800;
            }
            v += delta;
            if (v < lbl_1_rodata_7804) {
                v = lbl_1_rodata_7804;
            }
            if (v > lbl_1_rodata_7808) {
                v = lbl_1_rodata_7808;
            }
            lbl_1_bss_6BE4[1] = v;
            break;
        }
        case 2: {
            f32 delta = lbl_1_rodata_77F8;
            f32 v = lbl_1_bss_6BE4[2];
            if (arg1 & 0x40) {
                delta = lbl_1_rodata_77FC;
            } else if (arg1 & 0x20) {
                delta = lbl_1_rodata_7800;
            }
            v += delta;
            if (v < lbl_1_rodata_7804) {
                v = lbl_1_rodata_7804;
            }
            if (v > lbl_1_rodata_7808) {
                v = lbl_1_rodata_7808;
            }
            lbl_1_bss_6BE4[2] = v;
            break;
        }
        case 3: {
            f32 delta = lbl_1_rodata_77F8;
            f32 v = lbl_1_bss_6BE4[3];
            if (arg1 & 0x40) {
                delta = lbl_1_rodata_77FC;
            } else if (arg1 & 0x20) {
                delta = lbl_1_rodata_7800;
            }
            v += delta;
            if (v < lbl_1_rodata_7804) {
                v = lbl_1_rodata_7804;
            }
            if (v > lbl_1_rodata_7808) {
                v = lbl_1_rodata_7808;
            }
            lbl_1_bss_6BE4[3] = v;
            break;
        }
        }
    } else {
        if (flags & 8) {
            arg0 -= 1;
        } else if (flags & 4) {
            arg0 += 1;
        }
    }

    return arg0;
}

// .text:0x0001E28C size:0x4
void fn_1_1E28C(void) {
    return;
}

// .text:0x0001E290 size:0x340
s32 fn_1_1E290(s32 arg0, u16 arg1, u32 arg2, u16 flags) {
    s16 mode;

    if ((s16)arg0 < 0) {
        return arg0;
    }
    mode = (s16)arg0;
    if (mode >= 3) {
        return arg0;
    }

    if (flags & 1) {
        switch (mode) {
        case 0: {
            f32 delta = lbl_1_rodata_77F8;
            f32 v = *(f32 *)(lbl_1_bss_6BF4 + 0x140);
            if (arg1 & 0x40) {
                delta = lbl_1_rodata_77FC;
            } else if (arg1 & 0x20) {
                delta = lbl_1_rodata_7800;
            }
            delta = -delta;
            v += delta;
            if (v < lbl_1_rodata_7804) {
                v = lbl_1_rodata_7804;
            }
            if (v > lbl_1_rodata_7808) {
                v = lbl_1_rodata_7808;
            }
            *(f32 *)(lbl_1_bss_6BF4 + 0x140) = v;
            break;
        }
        case 1: {
            f32 delta = lbl_1_rodata_77F8;
            f32 v = *(f32 *)(lbl_1_bss_6BF4 + 0x144);
            if (arg1 & 0x40) {
                delta = lbl_1_rodata_77FC;
            } else if (arg1 & 0x20) {
                delta = lbl_1_rodata_7800;
            }
            delta = -delta;
            v += delta;
            if (v < lbl_1_rodata_7804) {
                v = lbl_1_rodata_7804;
            }
            if (v > lbl_1_rodata_7808) {
                v = lbl_1_rodata_7808;
            }
            *(f32 *)(lbl_1_bss_6BF4 + 0x144) = v;
            break;
        }
        case 2: {
            f32 delta = lbl_1_rodata_77F8;
            f32 v = *(f32 *)(lbl_1_bss_6BF4 + 0x148);
            if (arg1 & 0x40) {
                delta = lbl_1_rodata_77FC;
            } else if (arg1 & 0x20) {
                delta = lbl_1_rodata_7800;
            }
            delta = -delta;
            v += delta;
            if (v < lbl_1_rodata_7804) {
                v = lbl_1_rodata_7804;
            }
            if (v > lbl_1_rodata_7808) {
                v = lbl_1_rodata_7808;
            }
            *(f32 *)(lbl_1_bss_6BF4 + 0x148) = v;
            break;
        }
        }
    } else if (flags & 2) {
        switch (mode) {
        case 0: {
            f32 delta = lbl_1_rodata_77F8;
            f32 v = *(f32 *)(lbl_1_bss_6BF4 + 0x140);
            if (arg1 & 0x40) {
                delta = lbl_1_rodata_77FC;
            } else if (arg1 & 0x20) {
                delta = lbl_1_rodata_7800;
            }
            v += delta;
            if (v < lbl_1_rodata_7804) {
                v = lbl_1_rodata_7804;
            }
            if (v > lbl_1_rodata_7808) {
                v = lbl_1_rodata_7808;
            }
            *(f32 *)(lbl_1_bss_6BF4 + 0x140) = v;
            break;
        }
        case 1: {
            f32 delta = lbl_1_rodata_77F8;
            f32 v = *(f32 *)(lbl_1_bss_6BF4 + 0x144);
            if (arg1 & 0x40) {
                delta = lbl_1_rodata_77FC;
            } else if (arg1 & 0x20) {
                delta = lbl_1_rodata_7800;
            }
            v += delta;
            if (v < lbl_1_rodata_7804) {
                v = lbl_1_rodata_7804;
            }
            if (v > lbl_1_rodata_7808) {
                v = lbl_1_rodata_7808;
            }
            *(f32 *)(lbl_1_bss_6BF4 + 0x144) = v;
            break;
        }
        case 2: {
            f32 delta = lbl_1_rodata_77F8;
            f32 v = *(f32 *)(lbl_1_bss_6BF4 + 0x148);
            if (arg1 & 0x40) {
                delta = lbl_1_rodata_77FC;
            } else if (arg1 & 0x20) {
                delta = lbl_1_rodata_7800;
            }
            v += delta;
            if (v < lbl_1_rodata_7804) {
                v = lbl_1_rodata_7804;
            }
            if (v > lbl_1_rodata_7808) {
                v = lbl_1_rodata_7808;
            }
            *(f32 *)(lbl_1_bss_6BF4 + 0x148) = v;
            break;
        }
        }
    } else {
        if (flags & 8) {
            arg0 -= 1;
        } else if (flags & 4) {
            arg0 += 1;
        }
    }

    return arg0;
}

// .text:0x0001E5D0 size:0x2F0
void fn_1_1E5D0(void *arg0) {
    u8 *base = arg0;
    Vec v1;
    Vec v2;

    fn_1_F2C(4);
    GXSetBlendMode(1, 4, 5, 3);

    PSMTXMultVec((f32(*)[4])(base + 0x58), (Vec *)(base + 0xc), &v1);
    PSMTXMultVec((f32(*)[4])(base + 0x58), (Vec *)base, &v2);

    GXBegin(GX_LINES, 0, 2);
    GX_WRITE_F32(v1.x);
    GX_WRITE_F32(v1.y);
    GX_WRITE_F32(v1.z);
    GX_WRITE_U8(0xff);
    GX_WRITE_U8(0x40);
    GX_WRITE_U8(0x40);
    GX_WRITE_U8(0xff);
    GX_WRITE_F32(v2.x);
    GX_WRITE_F32(v2.y);
    GX_WRITE_F32(v2.z);
    GX_WRITE_U8(0x40);
    GX_WRITE_U8(0xff);
    GX_WRITE_U8(0x40);
    GX_WRITE_U8(0xff);

    PSVECScale((Vec *)(base + 0xe8), lbl_1_rodata_77E4, &v1);
    PSVECAdd(&v1, (Vec *)(base + 0xf4), &v2);

    GXBegin(GX_LINES, 0, 4);
    GX_WRITE_F32(v1.x);
    GX_WRITE_F32(v1.y);
    GX_WRITE_F32(v1.z);
    GX_WRITE_U8(0xff);
    GX_WRITE_U8(0);
    GX_WRITE_U8(0);
    GX_WRITE_U8(0xff);
    GX_WRITE_F32(v2.x);
    GX_WRITE_F32(v2.y);
    GX_WRITE_F32(v2.z);
    GX_WRITE_U8(0xff);
    GX_WRITE_U8(0);
    GX_WRITE_U8(0);
    GX_WRITE_U8(0xff);

    PSVECScale((Vec *)(base + 0x140), lbl_1_rodata_77E4, &v1);
    PSVECAdd(&v1, &v2, &v2);

    GX_WRITE_F32(v1.x);
    GX_WRITE_F32(v1.y);
    GX_WRITE_F32(v1.z);
    GX_WRITE_U8(0);
    GX_WRITE_U8(0);
    GX_WRITE_U8(0xff);
    GX_WRITE_U8(0xff);
    GX_WRITE_F32(v2.x);
    GX_WRITE_F32(v2.y);
    GX_WRITE_F32(v2.z);
    GX_WRITE_U8(0);
    GX_WRITE_U8(0);
    GX_WRITE_U8(0xff);
    GX_WRITE_U8(0xff);

    if (*(s32 *)((u8 *)currentDrawingItem + 0x28) == 0) {
        Vec offset;

        PSVECSubtract((Vec *)base, (Vec *)(base + 0xc), &v1);
        PSVECScale(&v1, lbl_1_bss_6BE4[0], &v1);
        PSVECAdd((Vec *)(base + 0xc), &v1, &v1);
        PSMTXMultVec((f32(*)[4])(base + 0x58), &v1, &v1);

        offset.x = lbl_1_bss_6BE4[1];
        offset.y = lbl_1_bss_6BE4[2];
        offset.z = lbl_1_bss_6BE4[3];

        PSVECAdd(&v1, &offset, &v2);

        GXBegin(GX_LINES, 0, 2);
        GX_WRITE_F32(v1.x);
        GX_WRITE_F32(v1.y);
        GX_WRITE_F32(v1.z);
        GX_WRITE_U8(0xff);
        GX_WRITE_U8(0);
        GX_WRITE_U8(0xff);
        GX_WRITE_U8(0xff);
        GX_WRITE_F32(v2.x);
        GX_WRITE_F32(v2.y);
        GX_WRITE_F32(v2.z);
        GX_WRITE_U8(0xff);
        GX_WRITE_U8(0);
        GX_WRITE_U8(0xff);
        GX_WRITE_U8(0xff);
    }
}

// .text:0x0001E8C0 size:0x4C
void fn_1_1E8C0(s32 arg0) {
    lbl_1_data_1066C[*(s32 *)((u8 *)currentDrawingItem + 0x28)]((s16)(arg0 - 8));
}

// .text:0x0001E90C size:0x6E8
#pragma dont_inline on
s16 fn_1_1E90C(s16 arg0, u16 arg1, u16 arg2, u16 arg3) {
    DrawingSceneStruct *item = currentDrawingItem;
    s32 row = arg0;
    f32 v14 = item->unk_14;
    f32 v18 = *(f32 *)((u8 *)item + 0x18);
    f32 v1c = *(f32 *)((u8 *)item + 0x1c);
    f32 v20 = *(f32 *)((u8 *)item + 0x20);
    f32 v24 = *(f32 *)((u8 *)item + 0x24);
    s16 ret = lbl_1_data_10668[*(s32 *)((u8 *)item + 0x28)]((s16)(row - 8));

    if (row != ret + 8) {
        s32 m = lbl_1_data_10670[*(s32 *)((u8 *)item + 0x28)] + 8;
        row = (ret + 8 + m) % m;
        goto tail;
    }

    if (arg2 & 0x100) {
        if (row == 2) {
            *(u32 *)((u8 *)item + 0x2c) ^= 4;
        } else if (row == 1) {
            fn_800385F0(item->unk_14, *(f32 *)((u8 *)item + 0x18), *(f32 *)((u8 *)item + 0x1c),
                *(f32 *)((u8 *)item + 0x20));
            *(f32 *)(lbl_1_bss_6BF4 + 0xec) += lbl_1_rodata_780C;
            *(f32 *)(lbl_1_bss_6BF4 + 0x50) = -*(f32 *)((u8 *)item + 0x24);
            *(u32 *)((u8 *)item + 0x2c) &= ~0x6;
            *(u32 *)((u8 *)item + 0x2c) |= 0x2;
        }
        goto tail;
    }

    if (arg3 & 1) {
        if (row > 7) {
            goto tail;
        }

        switch (row) {
        case 0:
            *(s32 *)((u8 *)item + 0x28) = (*(s32 *)((u8 *)item + 0x28) + 7) % 8;
            break;
        case 1: {
            f32 delta = lbl_1_rodata_77F8;

            if (arg1 & 0x40) {
                delta = lbl_1_rodata_77FC;
            } else if (arg1 & 0x20) {
                delta = lbl_1_rodata_7800;
            }

            delta = -delta;
            v14 = v14 + delta;
            if (v14 < lbl_1_rodata_77E4) {
                v14 = lbl_1_rodata_77E4;
            }
            if (v14 > lbl_1_rodata_7808) {
                v14 = lbl_1_rodata_7808;
            }
            break;
        }
        case 2: {
            f32 delta = lbl_1_rodata_77F8;

            if (arg1 & 0x40) {
                delta = lbl_1_rodata_77FC;
            } else if (arg1 & 0x20) {
                delta = lbl_1_rodata_7800;
            }

            delta = -delta;
            v18 = v18 + delta;
            if (v18 < lbl_1_rodata_77D8) {
                v18 = lbl_1_rodata_77D8;
            }
            if (v18 > lbl_1_rodata_77E4) {
                v18 = lbl_1_rodata_77E4;
            }
            break;
        }
        case 3: {
            f32 delta = lbl_1_rodata_77F8;

            if (arg1 & 0x40) {
                delta = lbl_1_rodata_77FC;
            } else if (arg1 & 0x20) {
                delta = lbl_1_rodata_7800;
            }

            delta = -delta;
            v1c = v1c + delta;
            if (v1c < lbl_1_rodata_77E4) {
                v1c = lbl_1_rodata_77E4;
            }
            if (v1c > lbl_1_rodata_7808) {
                v1c = lbl_1_rodata_7808;
            }
            break;
        }
        case 4: {
            f32 delta = lbl_1_rodata_77F8;

            if (arg1 & 0x40) {
                delta = lbl_1_rodata_77FC;
            } else if (arg1 & 0x20) {
                delta = lbl_1_rodata_7800;
            }

            delta = -delta;
            v24 = v24 + delta;
            if (v24 < lbl_1_rodata_77D8) {
                v24 = lbl_1_rodata_77D8;
            }
            if (v24 > lbl_1_rodata_7808) {
                v24 = lbl_1_rodata_7808;
            }
            break;
        }
        }
    } else if (arg3 & 2) {
        if (row > 7) {
            goto tail;
        }

        switch (row) {
        case 0:
            *(s32 *)((u8 *)item + 0x28) = (*(s32 *)((u8 *)item + 0x28) + 1) % 8;
            break;
        case 1: {
            f32 delta = lbl_1_rodata_77F8;

            if (arg1 & 0x40) {
                delta = lbl_1_rodata_77FC;
            } else if (arg1 & 0x20) {
                delta = lbl_1_rodata_7800;
            }

            v14 = v14 + delta;
            if (v14 < lbl_1_rodata_77E4) {
                v14 = lbl_1_rodata_77E4;
            }
            if (v14 > lbl_1_rodata_7808) {
                v14 = lbl_1_rodata_7808;
            }
            break;
        }
        case 2: {
            f32 delta = lbl_1_rodata_77F8;

            if (arg1 & 0x40) {
                delta = lbl_1_rodata_77FC;
            } else if (arg1 & 0x20) {
                delta = lbl_1_rodata_7800;
            }

            v18 = v18 + delta;
            if (v18 < lbl_1_rodata_77D8) {
                v18 = lbl_1_rodata_77D8;
            }
            if (v18 > lbl_1_rodata_77E4) {
                v18 = lbl_1_rodata_77E4;
            }
            break;
        }
        case 3: {
            f32 delta = lbl_1_rodata_77F8;

            if (arg1 & 0x40) {
                delta = lbl_1_rodata_77FC;
            } else if (arg1 & 0x20) {
                delta = lbl_1_rodata_7800;
            }

            v1c = v1c + delta;
            if (v1c < lbl_1_rodata_77E4) {
                v1c = lbl_1_rodata_77E4;
            }
            if (v1c > lbl_1_rodata_7808) {
                v1c = lbl_1_rodata_7808;
            }
            break;
        }
        case 4: {
            f32 delta = lbl_1_rodata_77F8;

            if (arg1 & 0x40) {
                delta = lbl_1_rodata_77FC;
            } else if (arg1 & 0x20) {
                delta = lbl_1_rodata_7800;
            }

            v20 = v20 + delta;
            if (v20 < lbl_1_rodata_77D8) {
                v20 = lbl_1_rodata_77D8;
            }
            if (v20 > lbl_1_rodata_7808) {
                v20 = lbl_1_rodata_7808;
            }
            break;
        }
        case 5: {
            f32 delta = lbl_1_rodata_77F8;

            if (arg1 & 0x40) {
                delta = lbl_1_rodata_77FC;
            } else if (arg1 & 0x20) {
                delta = lbl_1_rodata_7800;
            }

            v24 = v24 + delta;
            if (v24 < lbl_1_rodata_77D8) {
                v24 = lbl_1_rodata_77D8;
            }
            if (v24 > lbl_1_rodata_7808) {
                v24 = lbl_1_rodata_7808;
            }
            break;
        }
        }
    } else if (arg3 & 8) {
        if (*(s32 *)((u8 *)item + 0x28) < 8) {
            DrawingSceneStruct *item2 = currentDrawingItem;
            s32 m = lbl_1_data_10670[*(s32 *)((u8 *)item2 + 0x28)] + 8;

            row = (row + m - 1) % m;
        }
    } else if (arg3 & 4) {
        if (*(s32 *)((u8 *)item + 0x28) < 8) {
            DrawingSceneStruct *item2 = currentDrawingItem;
            s32 m = lbl_1_data_10670[*(s32 *)((u8 *)item2 + 0x28)] + 8;

            row = (row + 1) % m;
        }
    }

tail:
    item = currentDrawingItem;
    item->unk_14 = v14;
    *(f32 *)((u8 *)item + 0x18) = v18;
    *(f32 *)((u8 *)item + 0x1c) = v1c;
    *(f32 *)((u8 *)item + 0x20) = v20;
    *(f32 *)((u8 *)item + 0x24) = v24;

    return (s16)row;
}
#pragma dont_inline reset

// .text:0x0001EFF4 size:0x68
void fn_1_1EFF4(void) {
    fn_1_272DC(lbl_1_bss_6D48, 0);
    fn_1_AF4(0x14, 0x14, lbl_1_rodata_77E4);

    if (*(u32 *)((u8 *)currentDrawingItem + 0x2c) & 0x2) {
        fn_1_1E5D0(lbl_1_bss_6BF4);
    }
}

// .text:0x0001F05C size:0x1E0
void fn_1_1F05C(void) {
    u8 *base = lbl_1_bss_6BD8;
    DrawingSceneStruct *item = currentDrawingItem;

    if (*(u32 *)((u8 *)item + 0x2c) & 1) {
        s16 newState = fn_1_1E90C(item->state, AtBat_ButtonInput1._00, AtBat_ButtonInput1._02,
                                   *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4));

        currentDrawingItem->state = newState;
    } else {
        fn_1_26D28(base + 0x170, AtBat_ButtonInput1._00, AtBat_ButtonInput1._02,
                    *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4), (u8 *)&AtBat_ButtonInput1 + 0x10);
    }

    if (AtBat_ButtonInput1._02 & 0x200) {
        item = currentDrawingItem;

        if (*(u32 *)((u8 *)item + 0x2c) & 1) {
            item->func = fn_1_24778;
        } else {
            *(u32 *)((u8 *)item + 0x2c) ^= 1;
        }
    } else if (AtBat_ButtonInput1._02 & 0x1000) {
        item = currentDrawingItem;
        *(u32 *)((u8 *)item + 0x2c) ^= 1;
    }

    fn_1_27330(base + 0x170);
    item = currentDrawingItem;

    if (*(s32 *)((u8 *)item + 0x28) == 0) {
        if (*(u32 *)((u8 *)item + 0x2c) & 4) {
            *(u32 *)((u8 *)item + 0x2c) ^= 4;

            {
                f32 vec[3];

                vec[0] = *(f32 *)(base + 0x10);
                vec[1] = *(f32 *)(base + 0x14);
                vec[2] = *(f32 *)(base + 0x18);
                fn_80037B18(base + 0x1c, vec);
            }
        }

        fn_80037BAC(base + 0x1c);
    }

    item = currentDrawingItem;

    if (*(u32 *)((u8 *)item + 0x2c) & 1) {
        void (*fn)(s16) = lbl_1_data_1066C[*(u32 *)((u8 *)item + 0x28)];

        fn((s16)(item->state - 8));
    }

    fn_1_272DC(base + 0x170, 0);
    fn_1_AF4(0x14, 0x14, lbl_1_rodata_77E4);
    item = currentDrawingItem;

    if (*(u32 *)((u8 *)item + 0x2c) & 2) {
        fn_1_1E5D0(base + 0x1c);
    }
}

// .text:0x0001F23C size:0x9C
void fn_1_1F23C(u8 *arg0) {
    DrawingSceneStruct *item = currentDrawingItem;

    fn_800385F0(item->unk_14, *(f32 *)((u8 *)item + 0x18), *(f32 *)((u8 *)item + 0x1c),
        *(f32 *)((u8 *)item + 0x20));

    *(f32 *)(arg0 + 0x50) = -*(f32 *)((u8 *)currentDrawingItem + 0x24);
    *(f32 *)(arg0 + 0xec) += lbl_1_rodata_780C;
    *(u32 *)((u8 *)currentDrawingItem + 0x2c) &= ~0x2;
    *(u32 *)((u8 *)currentDrawingItem + 0x2c) |= 0x2;
}

// .text:0x0001F2D8 size:0x140
void fn_1_1F2D8(void) {
    u8 *base = lbl_1_bss_6BD8;

    fn_1_273D8(base + 0x170);

    currentDrawingItem->func = fn_1_1F05C;
    *(u32 *)((u8 *)currentDrawingItem + 0x2c) = 0;
    *(u32 *)((u8 *)currentDrawingItem + 0x28) = 0;
    currentDrawingItem->unk_14 = lbl_1_rodata_780C;
    *(f32 *)((u8 *)currentDrawingItem + 0x18) = lbl_1_rodata_7810;
    *(f32 *)((u8 *)currentDrawingItem + 0x1c) = lbl_1_rodata_7810;
    *(f32 *)((u8 *)currentDrawingItem + 0x20) = lbl_1_rodata_77E4;
    *(f32 *)((u8 *)currentDrawingItem + 0x24) = lbl_1_rodata_77E4;

    fn_800385F0(currentDrawingItem->unk_14, *(f32 *)((u8 *)currentDrawingItem + 0x18),
        *(f32 *)((u8 *)currentDrawingItem + 0x1c), *(f32 *)((u8 *)currentDrawingItem + 0x20));

    {
        u8 *sub = base + 0x1c;

        *(f32 *)(sub + 0x50) = -*(f32 *)((u8 *)currentDrawingItem + 0x24);
        *(f32 *)(sub + 0xec) += lbl_1_rodata_780C;
    }
    *(u32 *)((u8 *)currentDrawingItem + 0x2c) &= ~0x2;
    *(u32 *)((u8 *)currentDrawingItem + 0x2c) |= 0x2;
    currentDrawingItem->state = 0;

    {
        u8 *sub = base + 0xc;

        *(f32 *)(sub + 0x0) = lbl_1_rodata_77D8;
        *(f32 *)(sub + 0x4) = lbl_1_rodata_77D8;
        *(f32 *)(sub + 0x8) = lbl_1_rodata_77D8;
        *(f32 *)(sub + 0xc) = lbl_1_rodata_77D8;
    }
}

// .text:0x0001F418 size:0x200
void fn_1_1F418(void *arg0) {
    u8 *item = arg0;
    s32 i;

    for (i = 0; i < 4; i++) {
        u8 sel = *(item + 0x21);

        switch (i) {
        case 0:
            if (i == sel) {
                u16 btn = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

                if (btn & 1) {
                    if (*(item + 0x20) == 0) {
                        *(item + 0x20) = 2;
                    }
                    *(item + 0x20) -= 1;
                } else if (btn & 2) {
                    *(item + 0x20) += 1;
                    if (*(item + 0x20) == 2) {
                        *(item + 0x20) = 0;
                    }
                }
            }
            break;
        case 1: {
            s32 delta = fn_80048EA8(0);

            if (i == *(item + 0x21)) {
                u16 btn = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

                if (btn & 1) {
                    delta -= 1;
                } else if (btn & 2) {
                    delta += 1;
                }
            }
            fn_80048E00(0, delta);
            break;
        }
        case 2: {
            s32 delta = fn_80048EA8(1);

            if (i == *(item + 0x21)) {
                u16 btn = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

                if (btn & 1) {
                    delta -= 1;
                } else if (btn & 2) {
                    delta += 1;
                }
            }
            fn_80048E00(1, delta);
            break;
        }
        case 3:
            if (i == sel) {
                u16 btn = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

                if (btn & 1) {
                    if (*(u32 *)(item + 0x1c) != 0) {
                        *(u32 *)(item + 0x1c) -= 1;
                    }
                } else if (btn & 2) {
                    *(u32 *)(item + 0x1c) += 1;
                }
            }
            break;
        }
    }

    {
        u16 btn = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

        if (btn & 8) {
            if (*(item + 0x21) == 0) {
                *(item + 0x21) = 4;
            }
            *(item + 0x21) -= 1;
        } else if (btn & 4) {
            *(item + 0x21) += 1;
            if (*(item + 0x21) == 4) {
                *(item + 0x21) = 0;
            }
        }
    }
}

// .text:0x0001F618 size:0x2E8
void fn_1_1F618(void *arg0) {
    u8 *item = arg0;
    s32 outerCount = *(s32 *)(item + 0x1c);
    f32 c2 = lbl_1_rodata_77FC;
    f32 c1 = lbl_1_rodata_7814;

    for (; outerCount != 0; outerCount--) {
        s32 entryVal = outerCount % 4;
        s32 *entry = &entryVal;
        f32 z;
        s32 i;

        GXSetNumTevStages(*(item + 0x22));
        GXSetNumTexGens(*(item + 0x22));

        for (i = 0; i < *(item + 0x22); i++) {
            GXSetTexCoordGen2(i, 1, 4, 0x3c, 0, 0x7d);

            if (i != 0) {
                GXSetTevColorIn(i, 0, 8, 0xb, 0xf);
                GXSetTevColorOp(i, 0, 0, 0, 1, 0);
                GXSetTevAlphaIn(i, 7, 7, 7, 0);
                GXSetTevAlphaOp(i, 0, 0, 0, 1, 0);
            } else {
                GXSetTevColorIn(i, 0xf, 0xf, 0xf, 8);
                GXSetTevColorOp(i, 0, 0, 0, 1, 0);
                GXSetTevAlphaIn(i, 7, 7, 7, 5);
                GXSetTevAlphaOp(i, 0, 0, 0, 1, 0);
            }

            GXLoadTexObj(&lbl_1_bss_6EA4[*entry], i);

            if (*entry >= 2) {
                GXLoadTlut(&lbl_1_bss_6E44[*entry], i);
            }
        }

        GXBegin(GX_QUADS, 0, 4);

        z = c1 - c2 * (f32)(u32)outerCount;

        GX_WRITE_F32(lbl_1_rodata_77D8);
        GX_WRITE_F32(lbl_1_rodata_77D8);
        GX_WRITE_F32(z);
        GX_WRITE_U32(-128);
        GX_WRITE_U16(0);
        GX_WRITE_U16(0);

        GX_WRITE_F32(lbl_1_rodata_77D8);
        GX_WRITE_F32(lbl_1_rodata_77DC);
        GX_WRITE_F32(z);
        GX_WRITE_U32(-128);
        GX_WRITE_U16(0);
        GX_WRITE_U16(0x100);

        GX_WRITE_F32(lbl_1_rodata_77E0);
        GX_WRITE_F32(lbl_1_rodata_77DC);
        GX_WRITE_F32(z);
        GX_WRITE_U32(-128);
        GX_WRITE_U16(0x100);
        GX_WRITE_U16(0x100);

        GX_WRITE_F32(lbl_1_rodata_77E0);
        GX_WRITE_F32(lbl_1_rodata_77D8);
        GX_WRITE_F32(z);
        GX_WRITE_U32(-128);
        GX_WRITE_U16(0x100);
        GX_WRITE_U16(0);
    }
}

// .text:0x0001F900 size:0x478
void fn_1_1F900(void *arg0) {
    u8 *item = arg0;
    f32 c7818 = lbl_1_rodata_7818;
    f32 zZ = lbl_1_rodata_77D8;
    s32 outerCount;

    for (outerCount = 0; outerCount < *(s32 *)(item + 0x1c); outerCount++) {
        s32 r1v = outerCount % 480;
        s32 r2v = r1v % 48;
        s32 row = r2v / 8;
        s32 col = r2v % 8;
        u8 spacing = *(item + 0x23);
        f32 x0, x1, y0, y1;
        s32 i;

        GXSetNumTevStages(*(item + 0x22));
        GXSetNumTexGens(*(item + 0x22));

        for (i = 0; i < *(item + 0x22); i++) {
            u32 entry = *((u32 *)(lbl_1_bss_6BD8 + 0x24c) + (row + i) % 8);
            u32 idx;

            GXSetTexCoordGen2(i, 1, 4, 0x3c, 0, 0x7d);

            if (i != 0) {
                GXSetTevColorIn(i, 0, 8, 0xb, 0xf);
                GXSetTevColorOp(i, 0, 0, 0, 1, 0);
                GXSetTevAlphaIn(i, 7, 7, 7, 0);
                GXSetTevAlphaOp(i, 0, 0, 0, 1, 0);
            } else {
                GXSetTevColorIn(i, 0xf, 0xf, 0xf, 8);
                GXSetTevColorOp(i, 0, 0, 0, 1, 0);
                GXSetTevAlphaIn(i, 7, 7, 7, 5);
                GXSetTevAlphaOp(i, 0, 0, 0, 1, 0);
            }

            idx = entry & 0x7fffffff;
            GXLoadTexObj((GXTexObj *)(lbl_1_bss_6BD8 + 0x2cc) + idx, i);
            if ((s32)entry < 0) {
                GXLoadTlut((GXTlutObj *)(lbl_1_bss_6BD8 + 0x26c) + idx, i);
            }
        }

        GXBegin(GX_QUADS, 0, 4);

        x0 = (f32)(s32)(row * spacing) - c7818;
        x1 = (f32)(s32)((row + 1) * spacing) - c7818;
        y0 = (f32)(s32)(col * spacing) - c7818;
        y1 = (f32)(s32)((col + 1) * spacing) - c7818;

        GX_WRITE_F32(x0);
        GX_WRITE_F32(y0);
        GX_WRITE_F32(zZ);
        GX_WRITE_U32(-128);
        GX_WRITE_U16(0);
        GX_WRITE_U16(0);

        GX_WRITE_F32(x0);
        GX_WRITE_F32(y1);
        GX_WRITE_F32(zZ);
        GX_WRITE_U32(-128);
        GX_WRITE_U16(0);
        GX_WRITE_U16(0x100);

        GX_WRITE_F32(x1);
        GX_WRITE_F32(y1);
        GX_WRITE_F32(zZ);
        GX_WRITE_U32(-128);
        GX_WRITE_U16(0x100);
        GX_WRITE_U16(0x100);

        GX_WRITE_F32(x1);
        GX_WRITE_F32(y0);
        GX_WRITE_F32(zZ);
        GX_WRITE_U32(-128);
        GX_WRITE_U16(0x100);
        GX_WRITE_U16(0);
    }
}

// .text:0x0001FD78 size:0x2D4
void fn_1_1FD78(void *arg0) {
    u8 *item = arg0;
    u32 step = (AtBat_ButtonInput1._00 & 0x20) ? 0x64 : 1;
    s32 i;

    for (i = 0; i < 6; i++) {
        switch (i) {
        case 0:
            if (i == *(item + 0x21)) {
                u16 btn = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

                if (btn & 1) {
                    if (*(item + 0x20) == 0) {
                        *(item + 0x20) = 2;
                    }
                    *(item + 0x20) -= 1;
                } else if (btn & 2) {
                    *(item + 0x20) += 1;
                    if (*(item + 0x20) == 2) {
                        *(item + 0x20) = 0;
                    }
                }
            }
            break;
        case 1: {
            s32 delta = fn_80048EA8(0);

            if (i == *(item + 0x21)) {
                u16 btn = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

                if (btn & 1) {
                    delta -= 1;
                } else if (btn & 2) {
                    delta += 1;
                }
            }
            fn_80048E00(0, delta);
            break;
        }
        case 2: {
            s32 delta = fn_80048EA8(1);

            if (i == *(item + 0x21)) {
                u16 btn = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

                if (btn & 1) {
                    delta -= 1;
                } else if (btn & 2) {
                    delta += 1;
                }
            }
            fn_80048E00(1, delta);
            break;
        }
        case 3:
            if (i == *(item + 0x21)) {
                u16 btn = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

                if (btn & 1) {
                    if (*(u32 *)(item + 0x1c) <= step) {
                        *(u32 *)(item + 0x1c) = 0;
                    } else {
                        *(u32 *)(item + 0x1c) -= step;
                    }
                } else if (btn & 2) {
                    *(u32 *)(item + 0x1c) += step;
                    if (*(u32 *)(item + 0x1c) > 0x1000) {
                        *(u32 *)(item + 0x1c) = 0x1000;
                    }
                }
            }
            break;
        case 4:
            if (i == *(item + 0x21)) {
                u16 btn = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

                if (btn & 1) {
                    *(item + 0x23) -= 1;
                } else if (btn & 2) {
                    *(item + 0x23) += 1;
                }
            }
            break;
        case 5:
            if (i == *(item + 0x21)) {
                u16 btn = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

                if (btn & 1) {
                    if (*(item + 0x22) > 1) {
                        *(item + 0x22) -= 1;
                    }
                } else if (btn & 2) {
                    if (*(item + 0x22) < 4) {
                        *(item + 0x22) += 1;
                    }
                }
            }
            break;
        }
    }

    {
        u16 btn = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

        if (btn & 8) {
            if (*(item + 0x21) == 0) {
                *(item + 0x21) = 6;
            }
            *(item + 0x21) -= 1;
        } else if (btn & 4) {
            *(item + 0x21) += 1;
            if (*(item + 0x21) == 6) {
                *(item + 0x21) = 0;
            }
        }
    }
}

// .text:0x0002004C size:0x258
void fn_1_2004C(void) {
    u8 *base = lbl_1_bss_6BD8;
    DrawingSceneStruct *item = currentDrawingItem;
    u32 indices[9] = {5, 6, 7, 8, 9, 0xd, 0x60, 0x61, 0x55};
    u8 state = *((u8 *)item + 0x21);

    switch (state) {
    case 0: {
        *(void **)((u8 *)item + 0x18) = ARAMTransfer(lbl_1_data_10518, 0, 0, 0);
        *((u8 *)item + 0x21) += 1;
        break;
    }
    case 1: {
        u8 *hdr;
        u32 i;

        if ((s8)lbl_803C6CF8[0x715] != 1) {
            break;
        }

        hdr = *(u8 **)((u8 *)item + 0x18);
        *(void **)((u8 *)item + 0x14) = hdr + *(u32 *)(hdr + 0x14);
        convertTextureHeader(*(void **)((u8 *)item + 0x14));

        for (i = 0; i < 8; i++) {
            u32 *entry = (u32 *)(base + 0x24c) + i;
            u8 *info;

            *entry = i;
            info = *(u8 **)((u8 *)item + 0x14) + indices[i] * 0x20 + 4;

            if (fn_1_2051C(info, (GXTexObj *)(base + 0x2cc) + i,
                           (GXTlutObj *)(base + 0x26c) + i, i)) {
                *entry |= 0x80000000;
            }
        }

        *((u8 *)item + 0x21) = 0;
        currentDrawingItem->func = fn_1_202A4;
        break;
    }
    }
}

// .text:0x000202A4 size:0x168
void fn_1_202A4(void) {
    DrawingSceneStruct *item = currentDrawingItem;

    fn_80048C1C();
    lbl_1_data_10508[*((u8 *)item + 0x20)](item);

    if (AtBat_ButtonInput1._02 & 0x200) {
        u32 colorWord = 0x11775500;

        GXSetCopyClear(*(GXColor *)&colorWord, 0xffffff);
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
    }

    fn_80048D4C();
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xb, 1);
    GXSetVtxDesc(0xd, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xb, 1, 5, 0);
    GXSetVtxAttrFmt(0, 0xd, 1, 2, 8);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(1);
    GXSetNumTexGens(1);

    lbl_1_data_10510[*((u8 *)item + 0x20)](item);

    fn_80048C28();
}

// .text:0x0002040C size:0x110
void fn_1_2040C(void) {
    f32 c = lbl_1_rodata_77D8;
    DrawingSceneStruct *item = currentDrawingItem;

    *(u32 *)((u8 *)item + 0x1c) = 0;
    *((u8 *)item + 0x23) = 0;
    *((u8 *)item + 0x24) = 0;
    *((u8 *)item + 0x20) = 0;
    *((u8 *)item + 0x21) = 0;
    *((u8 *)item + 0x22) = 1;

    C_MTXOrtho(lbl_1_bss_47010, c, lbl_1_rodata_77DC, c,
        lbl_1_rodata_77E0, lbl_1_rodata_7814, lbl_1_rodata_7820);
    GXSetProjection(lbl_1_bss_47010, 1);

    {
        Mtx m;

        PSMTXIdentity(m);
        GXLoadPosMtxImm(m, 0);
        GXSetCurrentMtx(0);
        GXLoadTexMtxImm(m, 0x1e, 1);
    }

    fn_80048C14(3);
    fn_80048E00(0, 0x20);
    fn_80048E00(1, 0);
    fn_800AD038(*(void **)(lbl_80366158 + 0x8));
    currentDrawingItem->func = fn_1_2004C;
}

// .text:0x0002051C size:0x124
s32 fn_1_2051C(void *arg0, GXTexObj *arg1, GXTlutObj *arg2, u32 arg3) {
    u8 *info = (u8 *)arg0;
    u8 f15 = info[0x15];
    u8 f16 = info[0x16];
    s32 useMip = (f15 != f16);

    if (*(u32 *)(info + 0x4) != 0) {
        GXInitTexObjCI(arg1, *(void **)(info + 0x0), *(u16 *)(info + 0xa), *(u16 *)(info + 0x8),
            info[0x17], info[0xc], info[0xd], useMip, arg3);
        GXInitTlutObj(arg2, *(void **)(info + 0x4), info[0x1a], *(u16 *)(info + 0x18));
    } else {
        GXInitTexObj(arg1, *(void **)(info + 0x0), *(u16 *)(info + 0xa), *(u16 *)(info + 0x8),
            info[0x17], info[0xc], info[0xd], useMip);
    }

    GXInitTexObjLOD(arg1, info[0xe], info[0xf], (f32)info[0x15], (f32)info[0x16],
        *(f32 *)(info + 0x10), 0, 0, 0);

    return *(u32 *)(info + 0x4) != 0;
}

// .text:0x00020640 size:0x194
void fn_1_20640(void *arg0, u32 *entries) {
    s32 i;

    GXSetNumTevStages(*((u8 *)arg0 + 0x22));
    GXSetNumTexGens(*((u8 *)arg0 + 0x22));

    for (i = 0; i < *((u8 *)arg0 + 0x22); i++) {
        u32 entry;

        GXSetTexCoordGen2(i, 1, 4, 0x3c, 0, 0x7d);

        if (i != 0) {
            GXSetTevColorIn(i, 0, 8, 0xb, 0xf);
            GXSetTevColorOp(i, 0, 0, 0, 1, 0);
            GXSetTevAlphaIn(i, 7, 7, 7, 0);
            GXSetTevAlphaOp(i, 0, 0, 0, 1, 0);
        } else {
            GXSetTevColorIn(i, 0xf, 0xf, 0xf, 8);
            GXSetTevColorOp(i, 0, 0, 0, 1, 0);
            GXSetTevAlphaIn(i, 7, 7, 7, 5);
            GXSetTevAlphaOp(i, 0, 0, 0, 1, 0);
        }

        entry = entries[i];
        {
            u32 tlutIdx = entry & 0x7fffffff;

            GXLoadTexObj(&lbl_1_bss_6EA4[entry], i);

            if (entry & 0x80000000) {
                GXLoadTlut(&lbl_1_bss_6E44[tlutIdx], i);
            }
        }
    }
}

// .text:0x000207D4 size:0xBC
void fn_1_207D4(void) {
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xb, 1);
    GXSetVtxDesc(0xd, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xb, 1, 5, 0);
    GXSetVtxAttrFmt(0, 0xd, 1, 2, 8);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
}

// .text:0x00020890 size:0xC0
void fn_1_20890(void) {
    f32 c = lbl_1_rodata_77D8;

    C_MTXOrtho(lbl_1_bss_47010, c, lbl_1_rodata_77DC, c,
        lbl_1_rodata_77E0, lbl_1_rodata_7814, lbl_1_rodata_7820);
    GXSetProjection(lbl_1_bss_47010, 1);

    {
        Mtx m;

        PSMTXIdentity(m);
        GXLoadPosMtxImm(m, 0);
        GXSetCurrentMtx(0);
        GXLoadTexMtxImm(m, 0x1e, 1);
    }

    fn_80048C14(3);
    fn_80048E00(0, 0x20);
    fn_80048E00(1, 0);
}

// .text:0x00020950 size:0x288
void fn_1_20950(void *arg0, s32 arg1, Mtx arg2) {
    s32 j;

    for (j = 19; j >= 0; j--) {
        u8 *table1 = (u8 *)arg0 + j * 0x40;
        u8 *rec = (u8 *)lbl_1_bss_6BE0 + j * 0x90 + 0x34;
        u8 lt = arg1 > j;

        *(u8 *)(rec + 0x6c) = lt;

        if (j < arg1) {
            Vec diff;
            Vec scaled;

            PSVECSubtract((Vec *)(table1 + 0xc), (Vec *)((u8 *)arg0 + (j + 1) * 0x40 + 0xc), &diff);
            PSVECScale(&diff, lbl_1_rodata_7814, &scaled);
            PSVECAdd((Vec *)(table1 + 0xc), &scaled, &scaled);
            CTRLSetTranslation((Control *)(rec + 0x10), scaled.x, -scaled.y, scaled.z);

            if (PSVECMag(&diff) != lbl_1_rodata_77D8) {
                Quaternion q1;
                Vec axis;
                f32 angle1;

                PSVECNormalize(&diff, &diff);
                diff.y = -diff.y;

                angle1 = (f32)((lbl_1_rodata_7828 * (lbl_1_rodata_7830 + (f64)(j & 1))) / lbl_1_rodata_7838);

                axis.x = lbl_1_rodata_77E4;
                axis.y = lbl_1_rodata_77D8;
                axis.z = lbl_1_rodata_77D8;

                C_QUATRotAxisRad(&q1, &axis, angle1);

                {
                    f32 dot = PSVECDotProduct(&diff, &axis);
                    f32 angle2 = (f32)acos(dot);
                    f32 mag2;

                    PSVECCrossProduct(&diff, &axis, &axis);
                    mag2 = PSVECMag(&axis);

                    if (mag2 != lbl_1_rodata_77D8) {
                        Quaternion q2;

                        C_QUATRotAxisRad(&q2, &axis, angle2);
                        PSQUATMultiply(&q2, &q1, &q1);
                    }
                }

                CTRLSetQuat((Control *)(rec + 0x10), q1.x, q1.y, q1.z, q1.w);
            }

            CTRLSetScale((Control *)(rec + 0x10), lbl_1_data_104D0[0], lbl_1_data_104D0[1], lbl_1_data_104D0[2]);
            fn_800BDA24(rec);
        }

        {
            Mtx m;

            PSMTXTrans(m, lbl_1_rodata_77D8, lbl_1_rodata_77D8, lbl_1_rodata_77D8);
            PSMTXConcat(arg2, m, arg2);
        }

        *((u8 *)(*(void **)rec) + 0x98) |= 3;
    }

    fn_800BD670(lbl_1_bss_6BE0, arg2);
}

// .text:0x00020BD8 size:0x1F0
void fn_1_20BD8(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    u8 state = *((u8 *)item + 0x25);

    switch (state) {
    case 0: {
        DrawingSceneStruct *newItem = insertGraphicDrawingFunction(fn_1_20F8C, 1);

        newItem->state = 0;
        *((u8 *)item + 0x25) += 1;
        break;
    }
    case 1: {
        if (item->state != 0) {
            u32 color = lbl_1_rodata_77B0;
            u8 *field;
            u32 field0;
            u32 field1;
            u8 *layout;
            u8 *geo;
            u16 j;

            LITAlloc(lbl_1_bss_6FA4);
            LITInitAttn(*(void **)lbl_1_bss_6FA4, lbl_1_rodata_77E4, lbl_1_rodata_77D8, lbl_1_rodata_77D8,
                        lbl_1_rodata_77E4, lbl_1_rodata_77D8, lbl_1_rodata_77D8);
            LITInitPos(*(void **)lbl_1_bss_6FA4, lbl_1_rodata_7840, lbl_1_rodata_7840, lbl_1_rodata_7840);
            LITInitDir(*(void **)lbl_1_bss_6FA4, lbl_1_rodata_77D8, lbl_1_rodata_77D8, lbl_1_rodata_77D8);

            {
                GXColor c = *(GXColor *)&color;
                LITInitColor(*(void **)lbl_1_bss_6FA4, &c);
            }

            field = *(u8 **)((u8 *)item + 0x14);
            field0 = *(u32 *)field;
            field1 = *(u32 *)(field + 4);
            layout = field + field0;
            geo = field + field1;

            lbl_1_bss_6BE0 = ActorObjectInitTable(0x14, field0, field);

            LoadActorLayout(layout);
            convertGeometryAndSknHeader(geo, 0);
            haveActLayoutPointToGeoHeader(layout, geo);

            for (j = 0; j < 20; j++) {
                animateBallRelated(lbl_1_bss_6BE0, j, j, layout, 0, 0);
                fn_800B2C08(*(void **)((u8 *)lbl_1_bss_6BE0 + j * 0x90 + 0x34), 0);
                fn_800BD548((u8 *)lbl_1_bss_6BE0 + j * 0x90 + 0x34, 1, *(void **)lbl_1_bss_6FA4);
            }

            item->currentDrawingItem->state = 1;
            removeCurrentDrawingItem();
        }
        break;
    }
    }
}

// .text:0x00020DC8 size:0x38
void fn_1_20DC8(void) {
    DrawingSceneStruct *item = insertGraphicDrawingFunction(fn_1_20BD8, 1);

    *((u8 *)item + 0x25) = 0;
    item->state = 0;
}

// .text:0x00020E00 size:0x18C
void fn_1_20E00(void *arg0) {
    u32 colorBits = lbl_1_rodata_77B0;
    u8 *field;
    u32 field0;
    u32 field1;
    u8 *geo;
    u8 *layout;
    u16 j;

    LITAlloc(lbl_1_bss_6FA4);
    LITInitAttn(*(void **)lbl_1_bss_6FA4, lbl_1_rodata_77E4, lbl_1_rodata_77D8, lbl_1_rodata_77D8,
                lbl_1_rodata_77E4, lbl_1_rodata_77D8, lbl_1_rodata_77D8);
    LITInitPos(*(void **)lbl_1_bss_6FA4, lbl_1_rodata_7840, lbl_1_rodata_7840, lbl_1_rodata_7840);
    LITInitDir(*(void **)lbl_1_bss_6FA4, lbl_1_rodata_77D8, lbl_1_rodata_77D8, lbl_1_rodata_77D8);

    {
        GXColor color = *(GXColor *)&colorBits;
        LITInitColor(*(void **)lbl_1_bss_6FA4, &color);
    }

    field = *(u8 **)((u8 *)arg0 + 0x14);
    field0 = *(u32 *)field;
    field1 = *(u32 *)(field + 4);
    layout = field + field0;
    geo = field + field1;

    lbl_1_bss_6BE0 = ActorObjectInitTable(0x14, field0, field);

    LoadActorLayout(layout);
    convertGeometryAndSknHeader(geo, 0);
    haveActLayoutPointToGeoHeader(layout, geo);

    for (j = 0; j < 20; j++) {
        animateBallRelated(lbl_1_bss_6BE0, j, j, layout, 0, 0);
        fn_800B2C08(*(void **)((u8 *)lbl_1_bss_6BE0 + j * 0x90 + 0x34), 0);
        fn_800BD548((u8 *)lbl_1_bss_6BE0 + j * 0x90 + 0x34, 1, *(void **)lbl_1_bss_6FA4);
    }
}

// .text:0x00020F8C size:0xB4
void fn_1_20F8C(void) {
    DrawingSceneStruct *item = currentDrawingItem->currentDrawingItem;

    switch (currentDrawingItem->state) {
    case 0:
        if ((s8)lbl_803C6CF8[0x715] != 1) {
            break;
        }
        *(void **)((u8 *)item + 0x14) = ARAMTransfer(lbl_1_data_104F4, 0, 0, 0);
        currentDrawingItem->state += 1;
        break;
    case 1:
        if ((s8)lbl_803C6CF8[0x715] != 1) {
            break;
        }
        item->state = 1;
        break;
    }
}

// .text:0x00021040 size:0x140
void fn_1_21040(void) {
    s32 i;

    GXBegin(GX_LINES, 0, 0x2c);

    for (i = 0; i < 11; i++) {
        f32 n = (f32)((i - 5) * 10);
        u32 c1 = (i == 5) ? 0xff0000ff : -1;
        u32 c2 = (i == 5) ? 0xff00ff : -1;

        GX_WRITE_F32(n);
        GX_WRITE_F32(lbl_1_rodata_77D8);
        GX_WRITE_F32(lbl_1_rodata_7844);
        GX_WRITE_U32(c1);

        GX_WRITE_F32(n);
        GX_WRITE_F32(lbl_1_rodata_77D8);
        GX_WRITE_F32(lbl_1_rodata_7848);
        GX_WRITE_U32(c1);

        GX_WRITE_F32(lbl_1_rodata_7844);
        GX_WRITE_F32(lbl_1_rodata_77D8);
        GX_WRITE_F32(n);
        GX_WRITE_U32(c2);

        GX_WRITE_F32(lbl_1_rodata_7848);
        GX_WRITE_F32(lbl_1_rodata_77D8);
        GX_WRITE_F32(n);
        GX_WRITE_U32(c2);
    }
}

// .text:0x00021180 size:0x118
void fn_1_21180(DrawingSceneStruct *arg0) {
    f32 c1 = lbl_1_rodata_77E4;
    u32 val = *((u8 *)arg0 + 0x20);
    u8 *base = lbl_1_bss_6BD8;
    f32 floatVal = (f32)val;
    u16 flag = AtBat_ButtonInput1._00;
    u8 *item = base + 0x3e0;
    f32 ratio = c1 / floatVal;
    f32 c3 = lbl_1_rodata_780C;
    f32 speed;
    f32 t;
    f32 speed2;
    f32 result;
    u8 idx;

    *(u32 *)(item + 0x20) = val;
    speed = ratio / lbl_1_rodata_784C;
    t = c3 * speed;
    *(f32 *)(item + 0x18) = speed;
    speed2 = speed * speed;
    result = c1 / t;
    *(f32 *)(item + 0x1c) = speed2;
    *(f32 *)(item + 0x24) = result;

    if ((flag & 0x400) != 0) {
        *(u32 *)(item + 0x20) = 1;
    }

    idx = *((u8 *)arg0 + 0x21);
    fn_80038CD0(idx, item, base + 0x408, lbl_1_rodata_7810, *(f32 *)((u8 *)arg0 + 0x18));

    {
        u8 *entry = base + 0x408 + (*((u8 *)arg0 + 0x21) - 1) * 0x40;

        *(f32 *)(base + 0x3d0) = *(f32 *)(entry + 0xc);
        *(f32 *)(base + 0x3d4) = *(f32 *)(entry + 0x10);
        *(f32 *)(base + 0x3d8) = *(f32 *)(entry + 0x14);
        *(u32 *)(entry + 0x3c) = *((u8 *)arg0 + 0x23);
    }
}

// .text:0x00021298 size:0x170
void fn_1_21298(DrawingSceneStruct *arg0) {
    if (*((u8 *)arg0 + 0x22) != 0) {
        u8 count = *((u8 *)arg0 + 0x21);
        u8 *entry = lbl_1_bss_6FE0 + (count - 1) * 0x40;

        GXBegin(GX_LINESTRIP, 0, (count - 1) * 2);

        while (entry != lbl_1_bss_6FE0) {
            GX_WRITE_F32(*(f32 *)(entry + 0xc));
            GX_WRITE_F32(lbl_1_rodata_77D8);
            GX_WRITE_F32(*(f32 *)(entry + 0x14));
            GX_WRITE_U32(0x80);

            GX_WRITE_F32(*(f32 *)(entry - 0x34));
            GX_WRITE_F32(lbl_1_rodata_77D8);
            GX_WRITE_F32(*(f32 *)(entry - 0x2c));
            GX_WRITE_U32(0x80);

            entry -= 0x40;
        }
    }

    if (*((u8 *)arg0 + 0x24) != 0) {
        u8 count = *((u8 *)arg0 + 0x21);
        u8 *entry = lbl_1_bss_6FE0 + (count - 1) * 0x40;
        s32 i = count - 1;

        GXBegin(GX_LINESTRIP, 0, (count - 1) * 2);

        while (entry != lbl_1_bss_6FE0) {
            u32 color = lbl_1_data_104DC[i % 6];

            GX_WRITE_F32(*(f32 *)(entry + 0xc));
            GX_WRITE_F32(-*(f32 *)(entry + 0x10));
            GX_WRITE_F32(*(f32 *)(entry + 0x14));
            GX_WRITE_U32(color);

            GX_WRITE_F32(*(f32 *)(entry - 0x34));
            GX_WRITE_F32(-*(f32 *)(entry - 0x30));
            GX_WRITE_F32(*(f32 *)(entry - 0x2c));
            GX_WRITE_U32(color);

            entry -= 0x40;
            i--;
        }
    }
}

// .text:0x00021408 size:0x8E0
void fn_1_21408(void) {
    return;
}

// .text:0x00021CE8 size:0x8D0
void fn_1_21CE8(void) {
    return;
}

// .text:0x000225B8 size:0x8C
void fn_1_225B8(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    DrawingSceneStruct *newItem;

    switch (*((u8 *)item + 0x25)) {
    case 0:
        newItem = insertGraphicDrawingFunction(fn_1_20BD8, 1);
        *((u8 *)newItem + 0x25) = 0;
        newItem->state = 0;
        *((u8 *)item + 0x25) += 1;
        break;
    case 1:
        if (item->state != 0) {
            item->func = fn_1_21408;
        }
        break;
    }
}

// .text:0x00022644 size:0x230
void fn_1_22644(void) {
    DrawingSceneStruct *item = currentDrawingItem;

    fn_800AD038(*(void **)(lbl_80366158 + 0x8));
    *((u8 *)item + 0x25) = 0;

    {
        DrawingSceneStruct *scratch = currentDrawingItem;

        *(f32 *)((u8 *)scratch + 0x18) = lbl_1_rodata_77F8;
        *(f32 *)((u8 *)scratch + 0x1c) = lbl_1_rodata_7854;
        *((u8 *)scratch + 0x25) = 0;
        *((u8 *)scratch + 0x20) = 0xa;
        *((u8 *)scratch + 0x21) = 0xa;
        *((u8 *)scratch + 0x22) = 1;
        *((u8 *)scratch + 0x23) = 0;
        *((u8 *)scratch + 0x24) = 0;

        fn_80038E2C(lbl_1_bss_6BD8 + 0x3e0);

        {
            f32 c1 = lbl_1_rodata_77E4;
            u32 val = *((u8 *)scratch + 0x20);
            u8 *phys = lbl_1_bss_6BD8 + 0x3e0;
            f32 floatVal = (f32)val;
            u16 flag = AtBat_ButtonInput1._00;
            f32 ratio = c1 / floatVal;
            f32 c3 = lbl_1_rodata_780C;
            f32 speed;
            f32 t;
            f32 speed2;
            f32 result;
            u8 idx;

            *(u32 *)(phys + 0x20) = val;
            speed = ratio / lbl_1_rodata_784C;
            t = c3 * speed;
            *(f32 *)(phys + 0x18) = speed;
            speed2 = speed * speed;
            result = c1 / t;
            *(f32 *)(phys + 0x1c) = speed2;
            *(f32 *)(phys + 0x24) = result;

            if ((flag & 0x400) != 0) {
                *(u32 *)(phys + 0x20) = 1;
            }

            idx = *((u8 *)scratch + 0x21);
            fn_80038CD0(idx, phys, lbl_1_bss_6BD8 + 0x408, lbl_1_rodata_7810, *(f32 *)((u8 *)scratch + 0x18));

            {
                u8 *entry = lbl_1_bss_6BD8 + 0x408 + (*((u8 *)scratch + 0x21) - 1) * 0x40;

                *(f32 *)(lbl_1_bss_6BD8 + 0x3d0) = *(f32 *)(entry + 0xc);
                *(f32 *)(lbl_1_bss_6BD8 + 0x3d4) = *(f32 *)(entry + 0x10);
                *(f32 *)(lbl_1_bss_6BD8 + 0x3d8) = *(f32 *)(entry + 0x14);
                *(u32 *)(entry + 0x3c) = *((u8 *)scratch + 0x23);
            }
        }
    }

    fn_1_23AD8(lbl_1_bss_47010, (f32 *)(lbl_1_bss_43EE0 + 0x48), (f32 *)(lbl_1_bss_43EE0 + 0x3c));

    currentDrawingItem->func = fn_1_225B8;
}

// .text:0x00022874 size:0x580
u8 fn_1_22874(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    s32 discriminant;
    f32 delta0, delta1, delta2;
    s32 row;
    u8 old21;
    u16 f;

    if (AtBat_ButtonInput1._00 & 0x20) {
        discriminant = 0x64;
    } else if (*((u8 *)&AtBat_ButtonInput1 + 0x15) >= 0x50) {
        discriminant = 1;
    } else {
        discriminant = 0xa;
    }

    delta0 = lbl_1_rodata_786C * (f32)discriminant;
    delta1 = lbl_1_rodata_77F8 * (f32)discriminant;
    delta2 = lbl_1_rodata_77FC * (f32)discriminant;

    for (row = 0; row < 14; row++) {
        switch (row) {
        case 0:
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & 1) {
                    *((u8 *)item + 0x20) -= 1;
                } else if (f & 2) {
                    *((u8 *)item + 0x20) += 1;
                }
                if (*((u8 *)item + 0x20) == 0) {
                    *((u8 *)item + 0x20) += 1;
                }
            }
            break;
        case 1:
            old21 = *((u8 *)item + 0x21);
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & 1) {
                    *((u8 *)item + 0x21) = old21 - 1;
                } else if (f & 2) {
                    *((u8 *)item + 0x21) = old21 + 1;
                }
                if (*((u8 *)item + 0x21) < 2) {
                    *((u8 *)item + 0x21) += 1;
                }
            }
            break;
        case 2:
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & 1) {
                    *(f32 *)(lbl_1_bss_6FB8 + 0x0) -= delta0;
                } else if (f & 2) {
                    *(f32 *)(lbl_1_bss_6FB8 + 0x0) += delta0;
                }
            }
            break;
        case 3:
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & 1) {
                    *(f32 *)((u8 *)item + 0x18) -= delta1;
                } else if (f & 2) {
                    *(f32 *)((u8 *)item + 0x18) += delta1;
                }
            }
            break;
        case 4:
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & 1) {
                    *(f32 *)(lbl_1_bss_6FB8 + 0x8) -= delta1;
                } else if (f & 2) {
                    *(f32 *)(lbl_1_bss_6FB8 + 0x8) += delta1;
                }
            }
            break;
        case 5:
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & 1) {
                    *(f32 *)(lbl_1_bss_6FB8 + 0xc) -= delta1;
                } else if (f & 2) {
                    *(f32 *)(lbl_1_bss_6FB8 + 0xc) += delta1;
                }
            }
            break;
        case 6:
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & 1) {
                    *(f32 *)(lbl_1_bss_6FB8 + 0x10) -= delta1;
                } else if (f & 2) {
                    *(f32 *)(lbl_1_bss_6FB8 + 0x10) += delta1;
                }
            }
            break;
        case 7:
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & 1) {
                    *(f32 *)(lbl_1_bss_6FB8 + 0x14) -= delta2;
                } else if (f & 2) {
                    *(f32 *)(lbl_1_bss_6FB8 + 0x14) += delta2;
                }
            }
            break;
        case 8:
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & 1) {
                    *(f32 *)((u8 *)item + 0x1c) -= (f32)discriminant;
                } else if (f & 2) {
                    *(f32 *)((u8 *)item + 0x1c) += (f32)discriminant;
                }
            }
            break;
        case 9:
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & 3) {
                    *((u8 *)item + 0x22) = !*((u8 *)item + 0x22);
                }
            }
            break;
        case 10:
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & 3) {
                    *((u8 *)item + 0x23) = !*((u8 *)item + 0x23);
                }
            }
            break;
        case 11:
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & 1) {
                    lbl_1_data_104D0[0] = (f32)((f64)lbl_1_data_104D0[0] - lbl_1_rodata_7870);
                } else if (f & 2) {
                    lbl_1_data_104D0[0] = (f32)((f64)lbl_1_data_104D0[0] + lbl_1_rodata_7870);
                }
            }
            break;
        case 12:
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & 1) {
                    lbl_1_data_104D0[1] = (f32)((f64)lbl_1_data_104D0[1] - lbl_1_rodata_7870);
                } else if (f & 2) {
                    lbl_1_data_104D0[1] = (f32)((f64)lbl_1_data_104D0[1] + lbl_1_rodata_7870);
                }
            }
            break;
        case 13:
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & 1) {
                    lbl_1_data_104D0[2] = (f32)((f64)lbl_1_data_104D0[2] - lbl_1_rodata_7870);
                } else if (f & 2) {
                    lbl_1_data_104D0[2] = (f32)((f64)lbl_1_data_104D0[2] + lbl_1_rodata_7870);
                }
            }
            break;
        }
    }

    f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

    if (f & 8) {
        if (*((u8 *)item + 0x25) == 0) {
            *((u8 *)item + 0x25) = 14;
        }
        *((u8 *)item + 0x25) -= 1;
    } else if (f & 4) {
        *((u8 *)item + 0x25) += 1;
        if (*((u8 *)item + 0x25) == 14) {
            *((u8 *)item + 0x25) = 0;
        }
    }

    return old21 != *((u8 *)item + 0x21);
}

// .text:0x00022DF4 size:0x158
void fn_1_22DF4(DrawingSceneStruct *arg0) {
    *(f32 *)((u8 *)arg0 + 0x18) = lbl_1_rodata_77F8;
    *(f32 *)((u8 *)arg0 + 0x1c) = lbl_1_rodata_7854;
    *((u8 *)arg0 + 0x25) = 0;
    *((u8 *)arg0 + 0x20) = 10;
    *((u8 *)arg0 + 0x21) = 10;
    *((u8 *)arg0 + 0x22) = 1;
    *((u8 *)arg0 + 0x23) = 0;
    *((u8 *)arg0 + 0x24) = 0;

    fn_80038E2C(lbl_1_bss_6BD8 + 0x3e0);

    {
        f32 c1 = lbl_1_rodata_77E4;
        u32 val = *((u8 *)arg0 + 0x20);
        u8 *base = lbl_1_bss_6BD8;
        f32 floatVal = (f32)val;
        u16 flag = AtBat_ButtonInput1._00;
        u8 *item = base + 0x3e0;
        f32 ratio = c1 / floatVal;
        f32 c3 = lbl_1_rodata_780C;
        f32 speed;
        f32 t;
        f32 speed2;
        f32 result;
        u8 idx;

        *(u32 *)(item + 0x20) = val;
        speed = ratio / lbl_1_rodata_784C;
        t = c3 * speed;
        *(f32 *)(item + 0x18) = speed;
        speed2 = speed * speed;
        result = c1 / t;
        *(f32 *)(item + 0x1c) = speed2;
        *(f32 *)(item + 0x24) = result;

        if ((flag & 0x400) != 0) {
            *(u32 *)(item + 0x20) = 1;
        }

        idx = *((u8 *)arg0 + 0x21);
        fn_80038CD0(idx, item, base + 0x408, lbl_1_rodata_7810, *(f32 *)((u8 *)arg0 + 0x18));

        {
            u8 *entry = base + 0x408 + (*((u8 *)arg0 + 0x21) - 1) * 0x40;

            *(f32 *)(base + 0x3d0) = *(f32 *)(entry + 0xc);
            *(f32 *)(base + 0x3d4) = *(f32 *)(entry + 0x10);
            *(f32 *)(base + 0x3d8) = *(f32 *)(entry + 0x14);
            *(u32 *)(entry + 0x3c) = *((u8 *)arg0 + 0x23);
        }
    }
}

// .text:0x00022F4C size:0x14C
void fn_1_22F4C(s32 n, s32 m, f32 *dst, f32 *src, f32 *other) {
    f64 wSq;
    f32 coeffNeighbor;
    f32 coeffCenter;
    s32 mMinus1;
    s32 i;

    wSq = (lbl_1_rodata_7878 * *(f32 *)(lbl_1_data_FB98 + 0x928)) / *(f32 *)(lbl_1_data_FB98 + 0x924);
    wSq = wSq * wSq;
    coeffNeighbor = (f32)wSq;
    coeffCenter = (f32)(lbl_1_rodata_7880 - lbl_1_rodata_7888 * wSq);
    mMinus1 = m - 1;

    for (i = 0; i < n; i++) {
        s32 prevRowBase = m * ((i + n - 1) % n);
        s32 nextRowBase = m * ((i + 1) % n);
        s32 rowBase = i * m;
        s32 j;

        for (j = 0; j < m; j++) {
            s32 k = rowBase + j;
            s32 prevCol = rowBase + (j + mMinus1) % m;
            s32 nextCol = rowBase + (j + 1) % m;
            f32 val = src[k];
            f32 sum = src[prevRowBase + j] + src[nextRowBase + j];

            sum += src[prevCol];
            sum += src[nextCol];
            sum = coeffNeighbor * sum;
            sum = coeffCenter * val + sum;
            sum -= other[k];
            dst[k] = sum;
            dst[k] = dst[k] * *(f32 *)(lbl_1_data_FB98 + 0x92c);
        }
    }
}

// .text:0x00023098 size:0x76C
s32 fn_1_23098(Mtx44 arg0, Mtx arg1, f32 argF0, f32 argF1, s32 arg2, s32 arg3) {
    Vec originPos;
    Vec dirVec;
    f32 planeD;
    f32 negArgF1 = -argF1;
    f32 negArgF0;
    f32 valA = (lbl_1_rodata_77E0 * argF0) / lbl_1_rodata_7890 * lbl_1_rodata_7814;
    f32 valB = (lbl_1_rodata_77E0 * argF1) / lbl_1_rodata_7890 * lbl_1_rodata_7814;
    f32 valC = (lbl_1_rodata_77DC * argF0) / lbl_1_rodata_7890 * lbl_1_rodata_7814;
    f32 valD = (lbl_1_rodata_77DC * argF1) / lbl_1_rodata_7890 * lbl_1_rodata_7814;
    Vec cornersA[4];
    Vec cornersB[4];
    f32 tvals[4];
    Mtx mtxInv;
    Mtx44 tmpMtx44;
    s32 i;
    s32 rowCount;
    Vec edgeVec;
    s32 col;
    s32 row;

    originPos.x = lbl_1_rodata_77D8;
    originPos.y = lbl_1_rodata_77D8;
    originPos.z = lbl_1_rodata_77D8;
    dirVec.x = lbl_1_rodata_77D8;
    dirVec.y = lbl_1_rodata_7820;
    dirVec.z = lbl_1_rodata_77D8;

    PSMTXMultVec(arg1, &originPos, &originPos);
    PSMTXMultVec(arg1, &dirVec, &dirVec);
    PSVECSubtract(&dirVec, &originPos, &dirVec);
    PSVECNormalize(&dirVec, &dirVec);
    planeD = PSVECDotProduct(&dirVec, &originPos);

    cornersA[0].x = valA;
    cornersA[0].y = lbl_1_rodata_77D8;
    cornersA[0].z = -argF0;
    cornersA[1].x = valB;
    cornersA[1].y = lbl_1_rodata_77D8;
    cornersA[1].z = -argF1;
    cornersA[2].x = valB;
    cornersA[2].y = valD;
    cornersA[2].z = -argF1;
    cornersA[3].x = valB;
    cornersA[3].y = -valD;
    cornersA[3].z = -argF1;

    cornersB[0].x = lbl_1_rodata_77D8;
    cornersB[0].y = valC;
    cornersB[0].z = lbl_1_rodata_77D8;
    cornersB[1].x = lbl_1_rodata_77D8;
    cornersB[1].y = valD;
    cornersB[1].z = lbl_1_rodata_77D8;
    cornersB[2].x = valA - valB;
    cornersB[2].y = valD - valC;
    cornersB[2].z = argF1 - argF0;
    cornersB[3].x = valA - valB;
    cornersB[3].y = valD - valC;
    cornersB[3].z = argF1 - argF0;

    negArgF0 = -argF0;

    for (i = 0; i < 4; i++) {
        f32 denom = PSVECDotProduct(&dirVec, &cornersB[i]);
        tvals[i] = denom;
        if (denom == lbl_1_rodata_77D8) {
            cornersB[i].z = lbl_1_rodata_77D8;
        } else {
            f32 numer = PSVECDotProduct(&dirVec, &cornersA[i]);
            f32 t = (planeD - numer) / denom;
            tvals[i] = t;
            PSVECScale(&cornersB[i], t, &cornersB[i]);
            PSVECAdd(&cornersA[i], &cornersB[i], &cornersB[i]);
            if (tvals[i] < lbl_1_rodata_77D8) {
                tvals[i] = -tvals[i];
            }
        }
    }

    if (cornersB[2].z <= negArgF0 && cornersB[2].z >= negArgF1 &&
        cornersB[3].z <= negArgF0 && cornersB[3].z >= negArgF1) {
        cornersB[0] = cornersB[2];
        cornersB[1] = cornersB[3];
    } else {
        if (!(tvals[0] <= lbl_1_rodata_77E4 && tvals[1] <= lbl_1_rodata_77E4)) {
            if (tvals[0] > lbl_1_rodata_77E4 && tvals[1] > lbl_1_rodata_77E4) {
                return 0;
            }
            if (!(cornersB[2].z <= negArgF0 && cornersB[2].z >= negArgF1)) {
                cornersB[3] = cornersB[2];
            }
            if (tvals[0] >= lbl_1_rodata_77E4) {
                cornersB[0] = cornersB[3];
            } else {
                cornersB[1] = cornersB[2];
            }
        }
    }

    PSMTXInverse(arg1, mtxInv);

    {
        Vec tmp;
        row = arg3 - 1;
        PSMTXMultVec(mtxInv, &cornersB[1], &tmp);
        *(f32 *)(lbl_1_bss_F6E0 + row * 0x540) = tmp.x;
        *(f32 *)(lbl_1_bss_F6E0 + row * 0x540 + 4) = tmp.z;

        tmp.x = -cornersB[1].x;
        tmp.y = cornersB[1].y;
        tmp.z = lbl_1_rodata_77D8;
        PSMTXMultVec(mtxInv, &tmp, &tmp);
        *(f32 *)(lbl_1_bss_F6E0 + 0) = tmp.x;
        *(f32 *)(lbl_1_bss_F6E0 + 4) = tmp.z;

        PSMTXMultVec(mtxInv, &cornersB[0], &tmp);
        *(f32 *)(lbl_1_bss_F6E0 + row * 0x540 + 0xc) = tmp.x;
        *(f32 *)(lbl_1_bss_F6E0 + row * 0x540 + 0x10) = tmp.z;

        tmp.x = -cornersB[0].x;
        tmp.y = cornersB[0].y;
        tmp.z = lbl_1_rodata_77D8;
        PSMTXMultVec(mtxInv, &tmp, &tmp);
        *(f32 *)(lbl_1_bss_F6E0 + 0xc) = tmp.x;
        *(f32 *)(lbl_1_bss_F6E0 + 0x10) = tmp.z;
    }

    PSMTX44Identity(tmpMtx44);
    memcpy(tmpMtx44, arg1, 0x30);
    PSMTX44Concat(arg0, tmpMtx44, tmpMtx44);
    C_MTX44Inverse(tmpMtx44, tmpMtx44);
    PSMTX44MultVec(arg0, &cornersB[0], &cornersB[0]);
    PSMTX44MultVec(arg0, &cornersB[1], &cornersB[1]);

    {
        f32 diff = cornersB[0].y - cornersB[1].y;
        if (diff < lbl_1_rodata_77D8) {
            diff = -diff;
        }

        rowCount = (s32)((f32)arg2 * ((lbl_1_rodata_780C / (f32)arg2) - diff) * lbl_1_rodata_7814);
        if (rowCount < 2) {
            rowCount = 2;
        }
    }

    PSVECSubtract(&cornersB[0], &cornersB[1], &edgeVec);

    for (col = rowCount - 2; col >= 1; col--) {
        f32 t = (f32)col / (f32)(rowCount - 1);
        Vec interp;
        Vec world;

        PSVECScale(&edgeVec, t, &interp);
        PSVECAdd(&cornersB[1], &interp, &interp);

        PSMTX44MultVec(tmpMtx44, &interp, &world);
        *(f32 *)(lbl_1_bss_F6E0 + row * 0x540 + col * 0xc) = world.x;
        *(f32 *)(lbl_1_bss_F6E0 + row * 0x540 + col * 0xc + 4) = world.y;

        interp.x = -interp.x;
        PSMTX44MultVec(tmpMtx44, &interp, &world);
        *(f32 *)(lbl_1_bss_F6E0 + col * 0xc) = world.x;
        *(f32 *)(lbl_1_bss_F6E0 + col * 0xc + 4) = world.y;
    }

    for (col = 0; col < rowCount; col++) {
        Vec *cell0 = (Vec *)(lbl_1_bss_F6E0 + col * 0xc);
        Vec *cellLast = (Vec *)(lbl_1_bss_F6E0 + row * 0x540 + col * 0xc);
        Vec colEdge;

        colEdge.x = cellLast->x - cell0->x;
        colEdge.y = cellLast->y - cell0->y;
        colEdge.z = lbl_1_rodata_77D8;

        for (i = arg3 - 2; i >= 1; i--) {
            f32 t = (f32)i / (f32)(arg3 - 1);
            Vec *cell = (Vec *)(lbl_1_bss_F6E0 + i * 0x540 + col * 0xc);

            cell->x = cell0->x + colEdge.x * t;
            cell->y = cell0->y + colEdge.y * t;
        }
    }

    return rowCount;
}

// .text:0x00023804 size:0x2D4
void fn_1_23804(void *arg0, void *arg1, s32 n1, s32 n2) {
    u8 *base;
    s32 stride2;
    s32 vtxCount;
    s32 i;

    GXSetProjection(lbl_1_bss_47010, 0);
    GXClearVtxDesc();
    GXSetCullMode(0);
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xb, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xb, 1, 5, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOp(0, 4);
    GXLoadPosMtxImm((f32 (*)[4])lbl_1_bss_43EE0, 0);
    GXSetCurrentMtx(0);

    base = lbl_1_bss_F6E0 + n1 * 0xc;
    stride2 = n2 * 0x540;
    vtxCount = n2 * 2;

    for (i = n1; i != 0; i--) {
        u8 *rowPtr = base + stride2;
        s32 parity = i & 1;
        s32 j;

        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, (u16)vtxCount);

        for (j = n2; j != -1; j--) {
            GX_WRITE_F32(*(f32 *)(rowPtr + 0x0));
            GX_WRITE_F32(*(f32 *)(rowPtr + 0x8));
            GX_WRITE_F32(*(f32 *)(rowPtr + 0x4));
            GX_WRITE_U32(parity == 0 ? -1 : 0xffff);

            GX_WRITE_F32(*(f32 *)(rowPtr - 0xc));
            GX_WRITE_F32(*(f32 *)(rowPtr - 0x4));
            GX_WRITE_F32(*(f32 *)(rowPtr - 0x8));
            GX_WRITE_U32(parity == 0 ? -1 : 0xffff);

            rowPtr -= 0x540;
        }

        base -= 0xc;
    }

    GXBegin(GX_LINESTRIP, 0, 8);

    GX_WRITE_F32(lbl_1_rodata_7894);
    GX_WRITE_F32(lbl_1_rodata_77D8);
    GX_WRITE_F32(lbl_1_rodata_7894);
    GX_WRITE_U32(0xff0000ff);

    GX_WRITE_F32(lbl_1_rodata_7894);
    GX_WRITE_F32(lbl_1_rodata_77D8);
    GX_WRITE_F32(lbl_1_rodata_7898);
    GX_WRITE_U32(0xff0000ff);

    GX_WRITE_F32(lbl_1_rodata_7894);
    GX_WRITE_F32(lbl_1_rodata_77D8);
    GX_WRITE_F32(lbl_1_rodata_7898);
    GX_WRITE_U32(0xffff);

    GX_WRITE_F32(lbl_1_rodata_7898);
    GX_WRITE_F32(lbl_1_rodata_77D8);
    GX_WRITE_F32(lbl_1_rodata_7898);
    GX_WRITE_U32(0xffff);

    GX_WRITE_F32(lbl_1_rodata_7898);
    GX_WRITE_F32(lbl_1_rodata_77D8);
    GX_WRITE_F32(lbl_1_rodata_7898);
    GX_WRITE_U32(0xff0000ff);

    GX_WRITE_F32(lbl_1_rodata_7898);
    GX_WRITE_F32(lbl_1_rodata_77D8);
    GX_WRITE_F32(lbl_1_rodata_7894);
    GX_WRITE_U32(0xff0000ff);

    GX_WRITE_F32(lbl_1_rodata_7898);
    GX_WRITE_F32(lbl_1_rodata_77D8);
    GX_WRITE_F32(lbl_1_rodata_7894);
    GX_WRITE_U32(0xffff);

    GX_WRITE_F32(lbl_1_rodata_7894);
    GX_WRITE_F32(lbl_1_rodata_77D8);
    GX_WRITE_F32(lbl_1_rodata_7894);
    GX_WRITE_U32(0xffff);
}

// .text:0x00023AD8 size:0x7C
void fn_1_23AD8(Mtx44 m, f32 *arg1, f32 *arg2) {
    f32 up = lbl_1_rodata_77D8;
    f32 z = lbl_1_rodata_7804;

    arg1[0] = up;
    arg1[1] = up;
    arg1[2] = z;
    arg2[0] = up;
    arg2[1] = up;
    arg2[2] = up;

    C_MTXFrustum(m, lbl_1_rodata_7858, lbl_1_rodata_785C, lbl_1_rodata_7860, lbl_1_rodata_7864,
        lbl_1_rodata_77E4, lbl_1_rodata_7868);
}

// .text:0x00023B54 size:0x8BC
void fn_1_23B54(void) {
    return;
}

// .text:0x00024410 size:0x29C
void fn_1_24410(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    s32 j;

    fn_1_23AD8(lbl_1_bss_47010, (f32 *)(lbl_1_bss_43EE0 + 0x48), (f32 *)(lbl_1_bss_43EE0 + 0x3c));

    *(u16 *)(lbl_1_bss_43EE0 + 0x30) = 0;
    *(f32 *)(lbl_1_bss_43EE0 + 0x38) = lbl_1_rodata_77D8;
    *(u16 *)(lbl_1_bss_43EE0 + 0x32) = 0;

    *((u8 *)item + 0x27) = 0x40;
    *((u8 *)item + 0x29) = 0x40;
    *((u8 *)item + 0x28) = 0x40;
    *((u8 *)item + 0x2a) = 0;
    item->unk_14 = lbl_1_rodata_78AC;
    *(f32 *)((u8 *)item + 0x18) = lbl_1_rodata_78B0;
    *(u16 *)((u8 *)item + 0x24) = 0;
    *(f32 *)((u8 *)item + 0x1c) = lbl_1_rodata_78B4;
    *(f32 *)((u8 *)item + 0x20) = lbl_1_rodata_78B8;
    *((u8 *)item + 0x2b) = 1;

    {
        f32 c1 = lbl_1_rodata_78BC;
        f32 c2 = lbl_1_rodata_780C;
        f32 c3 = lbl_1_rodata_78C0;

        for (j = 0; j < 0x80; j++) {
            f32 angle = c1 * (c2 * ((f32)j * c3));

            lbl_1_bss_74E0[j] = (f32)cos((f64)angle);
        }
    }

    memset(lbl_1_bss_76E0, 0, 0x8000);

    for (j = 0; j < 0x20; j++) {
        s32 v1 = rand() % 0x20;
        s32 v2 = rand() % 0x80;

        lbl_1_bss_76E0[v1 * 0x80 + v2] = lbl_1_rodata_77E4;
    }

    currentDrawingItem->func = fn_1_23B54;
}

// .text:0x000246AC size:0xCC
void fn_1_246AC(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    u16 val = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

    if (val & 0x8) {
        if (*((u8 *)item + 0x14) == 0) {
            *((u8 *)item + 0x14) = 4;
        }
        *((u8 *)item + 0x14) -= 1;
    } else if (val & 0x4) {
        *((u8 *)item + 0x14) += 1;
        if (*((u8 *)item + 0x14) == 4) {
            *((u8 *)item + 0x14) = 0;
        }
    } else if (AtBat_ButtonInput1._02 & 0x100) {
        item->func = lbl_1_data_104A8[*((u8 *)item + 0x14)];
    } else if (AtBat_ButtonInput1._02 & 0x200) {
        item->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
    }
}

// .text:0x00024778 size:0x28
void fn_1_24778(void) {
    *((u8 *)currentDrawingItem + 0x14) = 0;
    currentDrawingItem->func = fn_1_246AC;
}

// .text:0x000247A0 size:0x11C
void fn_1_247A0(void) {
    s8 c = *((s8 *)&AtBat_ButtonInput1 + 0x13);
    s8 b = *((s8 *)&AtBat_ButtonInput1 + 0x11);
    DrawingSceneStruct *item = currentDrawingItem;
    s8 a = *((s8 *)&AtBat_ButtonInput1 + 0x10);
    u16 amount = *(u16 *)((u8 *)item + 0x22);
    u8 idx = *((u8 *)item + 0x2b);
    f32 tableVal = *(f32 *)(lbl_1_bss_43F68 - 0x40 + idx * 0x40);
    f32 fa = (f32)a * tableVal;
    f32 fc = (f32)c * tableVal;
    f32 fb = (f32)b * tableVal;
    f32 buf[3];

    buf[0] = (f32)amount * fa;
    buf[1] = (f32)amount * fc;
    buf[2] = (f32)amount * fb;

    fn_80038B48(lbl_1_bss_45868, lbl_1_bss_43F68, idx, buf);
}

// .text:0x000248BC size:0x1D0
void fn_1_248BC(s32 count) {
    u8 width;
    GXTexOffset offset;
    u8 *table1;
    u8 *table2;

    GXGetLineWidth(&width, &offset);
    GXSetLineWidth(0x18, offset);
    GXBegin(GX_LINESTRIP, 0, (u16)count);

    table1 = lbl_1_bss_43F68 + count * 0x40;
    table2 = lbl_1_data_10384 + count * 4;

    {
        u8 *p1 = table1;
        u8 *p2 = table2;

        while (p1 != lbl_1_bss_43F68) {
            GX_WRITE_F32(*(f32 *)(p1 + 0xc));
            GX_WRITE_F32(*(f32 *)(p1 + 0x10));
            GX_WRITE_F32(*(f32 *)(p1 + 0x14));
            GX_WRITE_U32(*(u32 *)p2);
            p1 -= 0x40;
            p2 -= 4;
        }
    }

    GXSetLineWidth(width, offset);
    GXBegin(GX_LINES, 0, (u16)(count * 4));

    while (table1 != lbl_1_bss_43F68) {
        f32 x = *(f32 *)(table1 + 0xc);
        f32 y = *(f32 *)(table1 + 0x10);
        f32 z = *(f32 *)(table1 + 0x14);
        u32 color = *(u32 *)table2;

        GX_WRITE_F32(x);
        GX_WRITE_F32(y);
        GX_WRITE_F32(z);
        GX_WRITE_U32(color);

        GX_WRITE_F32(lbl_1_data_104A4 * *(f32 *)(table1 + 0x30) + x);
        GX_WRITE_F32(lbl_1_data_104A4 * *(f32 *)(table1 + 0x34) + y);
        GX_WRITE_F32(lbl_1_data_104A4 * *(f32 *)(table1 + 0x38) + z);
        GX_WRITE_U32(color);

        GX_WRITE_F32(x);
        GX_WRITE_F32(y);
        GX_WRITE_F32(z);
        GX_WRITE_U32(color ^ 0xffffff00);

        GX_WRITE_F32(lbl_1_data_104A4 * *(f32 *)(table1 + 0x24) + x);
        GX_WRITE_F32(lbl_1_data_104A4 * *(f32 *)(table1 + 0x28) + y);
        GX_WRITE_F32(lbl_1_data_104A4 * *(f32 *)(table1 + 0x2c) + z);
        GX_WRITE_U32(color ^ 0xffffff00);

        table1 -= 0x40;
        table2 -= 4;
    }
}

// .text:0x00024A8C size:0x1C0
void fn_1_24A8C(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    u8 rawByte;
    f32 signedVal;
    f32 invSigned;
    f32 value24;

    fn_80038E2C(lbl_1_bss_45868);

    *(f32 *)(lbl_1_bss_45868 + 0x0) = (f32)*(u16 *)((u8 *)item + 0x1a);
    *(f32 *)(lbl_1_bss_45868 + 0x4) = *(f32 *)((u8 *)item + 0x14);
    *(f32 *)(lbl_1_bss_45868 + 0x8) = (f32)*(u16 *)((u8 *)item + 0x18) * lbl_1_rodata_78C4;
    *(f32 *)(lbl_1_bss_45868 + 0xc) = (f32)*(u16 *)((u8 *)item + 0x1c) * lbl_1_rodata_78C4;
    *(f32 *)(lbl_1_bss_45868 + 0x10) = (f32)*(u16 *)((u8 *)item + 0x1e) * lbl_1_rodata_78C4;
    *(f32 *)(lbl_1_bss_45868 + 0x14) = (f32)*(u16 *)((u8 *)item + 0x20) / lbl_1_rodata_78C8;

    rawByte = *((u8 *)item + 0x2a);
    *(u32 *)(lbl_1_bss_45868 + 0x20) = rawByte;
    signedVal = (f32)(s32)rawByte;
    invSigned = lbl_1_rodata_77E4 / signedVal;
    *(f32 *)(lbl_1_bss_45868 + 0x18) = invSigned;
    *(f32 *)(lbl_1_bss_45868 + 0x1c) = invSigned * invSigned;
    *(f32 *)(lbl_1_bss_45868 + 0x24) = lbl_1_rodata_77E4 / (lbl_1_rodata_780C * invSigned);

    if (AtBat_ButtonInput1._00 & 0x40) {
        *(u32 *)(lbl_1_bss_45868 + 0x20) = 1;
    }

    value24 = (f32)*(u16 *)((u8 *)item + 0x24) * lbl_1_rodata_78C4;
    fn_80038CD0(*((u8 *)item + 0x2b), lbl_1_bss_45868, lbl_1_bss_43F68, lbl_1_rodata_7808, value24);
}

// .text:0x00024C4C size:0x418
void fn_1_24C4C(u8 *arg0, s32 count, Vec *arg2, f32 argF1, f32 argF2, f32 argF3, f32 argF4) {
    DrawingSceneStruct *item = currentDrawingItem;
    f32 windDrag = lbl_1_rodata_7820 * argF4;
    f32 zero = lbl_1_rodata_77D8;
    f32 once = lbl_1_rodata_77E4;
    u8 *p;
    s32 i;

    p = arg0 + count * 0x3c;
    for (i = count; i != 0; i--) {
        if (*(u32 *)(p + 0x38) != 0) {
            *(f32 *)(p + 0x34) = zero;
            *(f32 *)(p + 0x30) = zero;
            *(f32 *)(p + 0x2c) = zero;
        } else {
            f32 c78CC = lbl_1_rodata_78CC;
            *(f32 *)(p + 0x34) = zero;
            *(f32 *)(p + 0x2c) = zero;
            *(f32 *)(p + 0x30) = c78CC * *(f32 *)(p + 0x0);
        }

        {
            f32 mag = PSVECMag((Vec *)(p + 0x20));
            if (mag != zero) {
                Vec local;
                f32 scale;

                PSVECScale((Vec *)(p + 0x20), windDrag, &local);
                PSVECNormalize(&local, &local);
                scale = ((f32)*(u16 *)((u8 *)item + 0x20) / lbl_1_rodata_78C8) * (mag * mag);
                PSVECScale(&local, scale, &local);
                PSVECAdd((Vec *)(p + 0x2c), &local, (Vec *)(p + 0x2c));
            }
        }

        if (once != zero) {
            PSVECAdd((Vec *)(p + 0x2c), arg2, (Vec *)(p + 0x2c));
            once = zero;
        }

        p -= 0x3c;
    }

    {
        u8 *pCur = arg0 + count * 0x3c;
        for (i = count; i != 0; i--) {
            u8 *pNext = arg0 + (i - 1) * 0x3c;
            Vec local20;
            Vec local14;
            Vec local8;
            f32 mag20;
            f32 dot;
            f32 spring;

            PSVECSubtract((Vec *)(pCur + 0x8), (Vec *)(pNext + 0x8), &local20);
            PSVECSubtract((Vec *)(pCur + 0x20), (Vec *)(pNext + 0x20), &local14);
            PSVECScale(&local14, argF4, &local14);
            mag20 = PSVECMag(&local20);
            dot = PSVECDotProduct(&local14, &local20);
            PSVECNormalize(&local20, &local8);
            spring = -(argF2 * (dot / mag20) + argF1 * (mag20 - argF3));
            PSVECScale(&local8, spring, &local8);

            if (*(u32 *)(pCur + 0x38) == 0) {
                PSVECAdd(&local8, (Vec *)(pCur + 0x2c), (Vec *)(pCur + 0x2c));
            }

            PSVECScale(&local8, lbl_1_rodata_7820, &local8);

            if (*(u32 *)(pNext + 0x38) == 0) {
                PSVECAdd(&local8, (Vec *)(pNext + 0x2c), (Vec *)(pNext + 0x2c));
            }

            pCur -= 0x3c;
        }
    }

    {
        u8 *p3 = arg0 + count * 0x3c;
        for (i = count; i != 0; i--) {
            if (*(u32 *)(p3 + 0x38) == 0) {
                f32 threshold = *(f32 *)(p3 + 0xc);
                f32 limit = (f32)*(u16 *)((u8 *)item + 0x28) / lbl_1_rodata_78D0;

                if (threshold <= limit) {
                    f32 mag = PSVECMag((Vec *)(p3 + 0x20));
                    if (mag != zero) {
                        f32 f24 = (f32)*(u16 *)((u8 *)item + 0x1e) * lbl_1_rodata_78C4 * *(f32 *)(p3 + 0x30);
                        Vec local;
                        f32 mag2;

                        if (f24 < zero) {
                            f24 = -f24;
                        }

                        memcpy(&local, p3 + 0x2c, 0xc);
                        local.y = zero;

                        mag2 = PSVECMag(&local);
                        if (mag2 != zero) {
                            PSVECNormalize(&local, &local);
                            if (f24 <= mag2) {
                                PSVECScale(&local, -mag2, &local);
                            } else {
                                PSVECScale(&local, -f24, &local);
                            }
                            PSVECAdd(&local, (Vec *)(p3 + 0x2c), (Vec *)(p3 + 0x2c));
                        }
                    }
                }
            }

            p3 -= 0x3c;
        }
    }
}

// .text:0x00025064 size:0xC04
void fn_1_25064(void) {
    return;
}

// .text:0x00025C68 size:0x330
void fn_1_25C68(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    u32 colorWord = 0;
    u8 rawByte;
    f32 signedVal;
    f32 invSigned;
    f32 value24;

    GXSetCopyClear(*(GXColor *)&colorWord, 0xffffff);

    C_MTXFrustum(lbl_1_bss_47010, lbl_1_rodata_78D4, lbl_1_rodata_78D8, lbl_1_rodata_78DC,
        lbl_1_rodata_78E0, lbl_1_rodata_77E4, lbl_1_rodata_7868);

    C_MTXLookAt(*(Mtx *)lbl_1_bss_43F68, (Vec *)(lbl_1_data_FB98 + 0x8f4), (Vec *)(lbl_1_data_FB98 + 0x8e8),
        (Vec *)(lbl_1_data_FB98 + 0x900));

    *(s16 *)((u8 *)item + 0x18) = (s16)(s32)(*(f32 *)(lbl_1_data_FB98 + 0x8d0) * lbl_1_rodata_78A4);
    *(s16 *)((u8 *)item + 0x1c) = (s16)(s32)(*(f32 *)(lbl_1_data_FB98 + 0x8d4) * lbl_1_rodata_78A4);
    *(s16 *)((u8 *)item + 0x1a) = (s16)(s32)*(f32 *)(lbl_1_data_FB98 + 0x8d8);
    *(s16 *)((u8 *)item + 0x1e) = 0x20;
    *((u8 *)item + 0x2a) = (u8)*(s32 *)(lbl_1_data_FB98 + 0x8dc);
    *(s16 *)((u8 *)item + 0x22) = 0xa;
    *((u8 *)item + 0x2b) = 0x14;
    *(s16 *)((u8 *)item + 0x20) = (s16)(s32)(*(f32 *)(lbl_1_data_FB98 + 0x8e4) * lbl_1_rodata_78A4);
    *(s16 *)((u8 *)item + 0x24) = (s16)(s32)(*(f32 *)(lbl_1_data_FB98 + 0x8e0) * lbl_1_rodata_78A4);
    item->unk_14 = lbl_1_rodata_7814;
    *(s16 *)((u8 *)item + 0x26) = 0x64;
    *(s16 *)((u8 *)item + 0x28) = 0xa;

    fn_80038E2C(lbl_1_bss_45868);

    *(f32 *)(lbl_1_bss_45868 + 0x0) = (f32)*(u16 *)((u8 *)currentDrawingItem + 0x1a);
    *(f32 *)(lbl_1_bss_45868 + 0x4) = *(f32 *)((u8 *)currentDrawingItem + 0x14);
    *(f32 *)(lbl_1_bss_45868 + 0x8) = (f32)*(u16 *)((u8 *)currentDrawingItem + 0x18) * lbl_1_rodata_78C4;
    *(f32 *)(lbl_1_bss_45868 + 0xc) = (f32)*(u16 *)((u8 *)currentDrawingItem + 0x1c) * lbl_1_rodata_78C4;
    *(f32 *)(lbl_1_bss_45868 + 0x10) = (f32)*(u16 *)((u8 *)currentDrawingItem + 0x1e) * lbl_1_rodata_78C4;
    *(f32 *)(lbl_1_bss_45868 + 0x14) = (f32)*(u16 *)((u8 *)currentDrawingItem + 0x20) / lbl_1_rodata_78C8;

    rawByte = *((u8 *)currentDrawingItem + 0x2a);
    *(u32 *)(lbl_1_bss_45868 + 0x20) = rawByte;
    signedVal = (f32)(s32)rawByte;
    invSigned = lbl_1_rodata_77E4 / signedVal;
    *(f32 *)(lbl_1_bss_45868 + 0x18) = invSigned;
    *(f32 *)(lbl_1_bss_45868 + 0x1c) = invSigned * invSigned;
    *(f32 *)(lbl_1_bss_45868 + 0x24) = lbl_1_rodata_77E4 / (lbl_1_rodata_780C * invSigned);

    if (AtBat_ButtonInput1._00 & 0x40) {
        *(u32 *)(lbl_1_bss_45868 + 0x20) = 1;
    }

    value24 = (f32)*(u16 *)((u8 *)currentDrawingItem + 0x24) * lbl_1_rodata_78C4;
    fn_80038CD0(*((u8 *)currentDrawingItem + 0x2b), lbl_1_bss_45868, lbl_1_bss_43F68, lbl_1_rodata_7808,
        value24);

    currentDrawingItem->func = fn_1_25064;
    *((u8 *)item + 0x2c) = 0;
}

// .text:0x00025F98 size:0x824
void fn_1_25F98(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    s32 row;
    u16 subIndex;

    for (row = 0; row < 6; row++) {
        switch (row) {
        case 0:
            if (row == *((u8 *)item + 0x22)) {
                u16 f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & 2) {
                    removeGraphicsElementFromScene(*(void **)((u8 *)item + 0x14));
                    *((u8 *)item + 0x21) += 1;
                    if (*((u8 *)item + 0x21) == *(u16 *)((u8 *)item + 0x18)) {
                        *((u8 *)item + 0x21) = 0;
                    }
                    *((u8 *)item + 0x24) = 0;
                    *(u16 *)((u8 *)lbl_1_data_10344 + 2) = *((u8 *)item + 0x21);
                    addGraphicsElementToScene(*(void **)((u8 *)item + 0x14));
                } else if (f & 1) {
                    removeGraphicsElementFromScene(*(void **)((u8 *)item + 0x14));
                    if (*((u8 *)item + 0x21) == 0) {
                        *((u8 *)item + 0x21) = (u8)*(u16 *)((u8 *)item + 0x18);
                    }
                    *((u8 *)item + 0x21) -= 1;
                    *((u8 *)item + 0x24) = 0;
                    *(u16 *)((u8 *)lbl_1_data_10344 + 2) = *((u8 *)item + 0x21);
                    addGraphicsElementToScene(*(void **)((u8 *)item + 0x14));
                } else {
                    if (AtBat_ButtonInput1._02 & 0x100) {
                        GFX_OBJ(item)[0x68] = 1;
                    } else if (AtBat_ButtonInput1._02 & 0x200) {
                        GFX_OBJ(item)[0x68] = 0;
                    } else if (AtBat_ButtonInput1._02 & 0x400) {
                        *(u32 *)(GFX_OBJ(item) + 0x5c) = 0;
                    }
                }
            }
            break;
        case 1:
            if (row == *((u8 *)item + 0x22)) {
                if (AtBat_ButtonInput1._02 & 0x100) {
                    *((u8 *)item + 0x23) = !*((u8 *)item + 0x23);
                }
                if (*((u8 *)item + 0x23)) {
                    GFX_OBJ(item)[0x68] = 0;
                } else {
                    GFX_OBJ(item)[0x68] = 1;
                }
                {
                    u16 f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                    if (f & 2) {
                        if (*((u8 *)item + 0x23)) {
                            GFX_OBJ(item)[0x68] = 1;
                        }
                    } else if (f & 1) {
                        if (*((u8 *)item + 0x23)) {
                            GFX_OBJ(item)[0x68] = 4;
                        }
                    }
                }
            }
            break;
        case 2: {
            if (row == *((u8 *)item + 0x22)) {
                u16 f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & 2) {
                    *((u8 *)item + 0x24) += 1;
                } else if (f & 1) {
                    *((u8 *)item + 0x24) -= 1;
                }
                fn_8000CEF0(*(void **)(lbl_803C4BE0 + GFX_OBJ(item)[0x66] * 0x3c + 0x38));
            }
            break;
        }
        case 3: {
            if (row == *((u8 *)item + 0x22)) {
                u16 f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                void *structA;
                void *structB;
                void *structC;

                if (f & 2) {
                    subIndex += 1;
                } else if (f & 1) {
                    subIndex -= 1;
                }

                structA = *(void **)(lbl_803C4BE0 + GFX_OBJ(item)[0x66] * 0x3c + 0x38);
                structB = *(void **)((u8 *)structA + 8);
                structC = *(void **)((u8 *)structB + *((u8 *)item + 0x21) * 4 + 8);
                *(u16 *)((u8 *)structC + 0xa) = subIndex;
            }
            break;
        }
        case 4:
            if (row == *((u8 *)item + 0x22)) {
                u16 f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & 0x800) {
                    *(s16 *)((u8 *)item + 0x1a) = 0;
                } else if (f & 0x400) {
                    *(s16 *)((u8 *)item + 0x1a) = 0x140;
                } else if (f & 2) {
                    *(s16 *)((u8 *)item + 0x1a) += 8;
                } else if (f & 1) {
                    *(s16 *)((u8 *)item + 0x1a) -= 8;
                }
                *(f32 *)((u8 *)lbl_1_data_10344 + 4) = (f32)*(s16 *)((u8 *)item + 0x1a);
                *(f32 *)(GFX_OBJ(item) + 0x48) = (f32)*(s16 *)((u8 *)item + 0x1a);
            }
            break;
        case 5:
            if (row == *((u8 *)item + 0x22)) {
                u16 f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & 0x800) {
                    *(s16 *)((u8 *)item + 0x1c) = 0;
                } else if (f & 0x400) {
                    *(s16 *)((u8 *)item + 0x1c) = 0xe0;
                } else if (f & 2) {
                    *(s16 *)((u8 *)item + 0x1c) += 8;
                } else if (f & 1) {
                    *(s16 *)((u8 *)item + 0x1c) -= 8;
                }
                *(f32 *)((u8 *)lbl_1_data_10344 + 8) = (f32)*(s16 *)((u8 *)item + 0x1c);
                *(f32 *)(GFX_OBJ(item) + 0x4c) = (f32)*(s16 *)((u8 *)item + 0x1c);
            }
            break;
        }
    }

    if (AtBat_ButtonInput1._02 & 4) {
        *((u8 *)item + 0x22) += 1;
        if (*((u8 *)item + 0x22) == 6) {
            *((u8 *)item + 0x22) = 0;
        }
    } else if (AtBat_ButtonInput1._02 & 8) {
        if (*((u8 *)item + 0x22) == 0) {
            *((u8 *)item + 0x22) = 6;
        }
        *((u8 *)item + 0x22) -= 1;
    }

    if (AtBat_ButtonInput1._02 & 0x1000) {
        removeGraphicsElementFromScene(*(void **)((u8 *)item + 0x14));
        *(u16 *)(*(u8 **)((u8 *)item + 0x14) + 0x10) = 1;
        currentDrawingItem->func = fn_1_26928;
        fn_80035A00();
    }

    {
        Mtx localMtx;
        u32 *dst = (u32 *)localMtx;
        u32 *src = (u32 *)lbl_1_rodata_7780;

        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        dst[3] = src[3];
        dst[4] = src[4];
        dst[5] = src[5];
        dst[6] = src[6];
        dst[7] = src[7];
        dst[8] = src[8];
        dst[9] = src[9];
        dst[10] = src[10];
        dst[11] = src[11];

        if (*(s32 *)lbl_1_bss_6BD8 != 0) {
        GXClearVtxDesc();
        GXSetVtxDesc(9, 1);
        GXSetVtxDesc(0xd, 1);
        GXSetVtxAttrFmt(0, 9, 1, 4, 0);
        GXSetVtxAttrFmt(0, 0xd, 1, 2, 0);
        GXSetChanCtrl(0, 0, 1, 1, 0, 0, 2);
        GXSetNumChans(0);
        GXSetNumTexGens(1);
        GXSetNumTevStages(1);
        GXSetTevOrder(0, 0, 0, 0xff);
        GXSetTevOp(0, 3);
        GXLoadPosMtxImm(localMtx, 0);
        GXSetCurrentMtx(0);
        SetDisplayStateTexture((u8 *)(*(void **)(lbl_803C4BE0 + GFX_OBJ(item)[0x66] * 0x3c + 0x34)) + lbl_1_bss_6BDC * 0x20 + 4, 0, 0);

        GXBegin(GX_QUADS, 0, 4);

        GX_WRITE_F32(lbl_1_rodata_77E8);
        GX_WRITE_F32(lbl_1_rodata_78E4);
        GX_WRITE_F32(lbl_1_rodata_78E8);
        GX_WRITE_U16(0);
        GX_WRITE_U16(0);

        GX_WRITE_F32(lbl_1_rodata_77E8);
        GX_WRITE_F32(lbl_1_rodata_78EC);
        GX_WRITE_F32(lbl_1_rodata_78E8);
        GX_WRITE_U16(0);
        GX_WRITE_U16(1);

        GX_WRITE_F32(lbl_1_rodata_7814);
        GX_WRITE_F32(lbl_1_rodata_78EC);
        GX_WRITE_F32(lbl_1_rodata_78E8);
        GX_WRITE_U16(1);
        GX_WRITE_U16(1);

        GX_WRITE_F32(lbl_1_rodata_7814);
        GX_WRITE_F32(lbl_1_rodata_78E4);
        GX_WRITE_F32(lbl_1_rodata_78E8);
        GX_WRITE_U16(1);
        GX_WRITE_U16(0);
        }
    }
}

// .text:0x000267BC size:0x38
void fn_1_267BC(void) {
    if (currentDrawingItem->state != 0) {
        removeCurrentDrawingItem();
    }
}

// .text:0x000267F4 size:0x134
void fn_1_267F4(void) {
    DrawingSceneStruct *item = currentDrawingItem;

    switch (*((u8 *)item + 0x1e)) {
    case 0: {
        u8 idx = *((u8 *)item + 0x20);
        u8 *entry = lbl_1_data_FB98 + idx * 0x10;

        if (diskReadRelated(entry, 0) != 0) {
            *((u8 *)item + 0x1e) += 1;
        }
        break;
    }
    case 1: {
        s32 idx2;

        *(void **)((u8 *)item + 0x14) = insertGraphicDrawingFunction(fn_1_267BC, 1);
        (*(DrawingSceneStruct **)((u8 *)item + 0x14))->state = 0;

        idx2 = fn_80035DD4(0);
        if (idx2 == -1) {
            OSPanic("spr.c", 0xf5, "It is a number not registered. \n");
        }

        *(u16 *)((u8 *)item + 0x18) =
            *(u32 *)(*(u8 **)(*(u8 **)(lbl_803C4BE0 + idx2 * 0x3c + 0x38) + 0x8));
        addGraphicsElementToScene(*(void **)((u8 *)item + 0x14));

        *((u8 *)item + 0x21) = 0;
        *((u8 *)item + 0x22) = 0;
        *((u8 *)item + 0x24) = 0;
        *(u16 *)((u8 *)item + 0x1a) = 0;
        *(u16 *)((u8 *)item + 0x1c) = 0;
        currentDrawingItem->func = fn_1_25F98;
        break;
    }
    }
}

// .text:0x00026928 size:0x10C
void fn_1_26928(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    u16 val = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

    if (val & 0x2) {
        *((u8 *)item + 0x20) += 1;
        if (*((u8 *)item + 0x20) == *((u8 *)item + 0x1f)) {
            *((u8 *)item + 0x20) = 0;
        }
    } else if (val & 0x1) {
        if (*((u8 *)item + 0x20) == 0) {
            *((u8 *)item + 0x20) = *((u8 *)item + 0x1f);
        }
        *((u8 *)item + 0x20) -= 1;
    } else if (AtBat_ButtonInput1._02 & 0x100) {
        *((u8 *)item + 0x1e) = 0;
        currentDrawingItem->func = fn_1_267F4;
    } else if (AtBat_ButtonInput1._02 & 0x200) {
        fn_800AD038(*(void **)(lbl_80366158 + 0x8));
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
    } else if (AtBat_ButtonInput1._02 & 0x1000) {
        item->func = fn_1_25C68;
    }

    fn_800B24D4(4);
    fn_800B1188();
}

// .text:0x00026A34 size:0xC4
void fn_1_26A34(void) {
    GXSetProjection(lbl_1_bss_47010, 0);
    GXClearVtxDesc();
    GXSetCullMode(0);
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xb, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xb, 1, 5, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOp(0, 4);
}
