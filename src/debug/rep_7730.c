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
#include "Dolphin/os.h"

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
extern f32 lbl_1_rodata_7844;
extern f32 lbl_1_rodata_7848;
extern u8 lbl_1_bss_6BD8[0x500];
extern f32 lbl_1_rodata_784C;
extern f32 lbl_1_rodata_7810;
extern u8 lbl_1_bss_43F68[0x1900];
extern f32 lbl_1_rodata_77F8;
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
extern void fn_80038B48(void *arg0, void *arg1, s32 arg2, void *arg3);
extern void fn_80038CD0(u8 arg0, void *arg1, void *arg2, f32 arg3, f32 arg4);

// .text:0x0001D694 size:0x2B0
void fn_1_1D694(void) {
    return;
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
    return;
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
void fn_1_1DE60(void) {
    return;
}

// .text:0x0001E28C size:0x4
void fn_1_1E28C(void) {
    return;
}

// .text:0x0001E290 size:0x340
void fn_1_1E290(void) {
    return;
}

// .text:0x0001E5D0 size:0x2F0
#pragma dont_inline on
void fn_1_1E5D0(void *arg0) {
    *(s32 *)arg0 = 0;
}
#pragma dont_inline reset

// .text:0x0001E8C0 size:0x4C
void fn_1_1E8C0(s32 arg0) {
    lbl_1_data_1066C[*(s32 *)((u8 *)currentDrawingItem + 0x28)]((s16)(arg0 - 8));
}

// .text:0x0001E90C size:0x6E8
void fn_1_1E90C(void) {
    return;
}

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
    return;
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
void fn_1_1F418(void) {
    return;
}

// .text:0x0001F618 size:0x2E8
void fn_1_1F618(void) {
    return;
}

// .text:0x0001F900 size:0x478
void fn_1_1F900(void) {
    return;
}

// .text:0x0001FD78 size:0x2D4
void fn_1_1FD78(void) {
    return;
}

// .text:0x0002004C size:0x258
void fn_1_2004C(void) {
    return;
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
void fn_1_20640(void) {
    return;
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
void fn_1_20950(void) {
    return;
}

// .text:0x00020BD8 size:0x1F0
void fn_1_20BD8(void) {
    return;
}

// .text:0x00020DC8 size:0x38
void fn_1_20DC8(void) {
    DrawingSceneStruct *item = insertGraphicDrawingFunction(fn_1_20BD8, 1);

    *((u8 *)item + 0x25) = 0;
    item->state = 0;
}

// .text:0x00020E00 size:0x18C
void fn_1_20E00(void) {
    return;
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
    return;
}

// .text:0x00022874 size:0x580
void fn_1_22874(void) {
    return;
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
void fn_1_22F4C(void) {
    return;
}

// .text:0x00023098 size:0x76C
void fn_1_23098(void) {
    return;
}

// .text:0x00023804 size:0x2D4
void fn_1_23804(void) {
    return;
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
    return;
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
void fn_1_248BC(void) {
    return;
}

// .text:0x00024A8C size:0x1C0
void fn_1_24A8C(void) {
    return;
}

// .text:0x00024C4C size:0x418
void fn_1_24C4C(void) {
    return;
}

// .text:0x00025064 size:0xC04
void fn_1_25064(void) {
    return;
}

// .text:0x00025C68 size:0x330
void fn_1_25C68(void) {
    return;
}

// .text:0x00025F98 size:0x824
void fn_1_25F98(void) {
    return;
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
