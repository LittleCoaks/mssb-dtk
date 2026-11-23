#include <string.h>
#include "mssbTypes.h"
#include "Dolphin/vi.h"
#include "Unknown/spani_default.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x800204cc.h"
#include "musyx/musyx.h"
#include "text/text.h"
#include "Unknown/sub.h"
#include "Dolphin/GX/GXFifo.h"
#include "Dolphin/GX/GXGeometry.h"
#include "Dolphin/GX/GXLight.h"
#include "Dolphin/GX/GXTev.h"
#include "Dolphin/GX/GXFrameBuffer.h"
#include "Dolphin/GX/GXTransform.h"
#include "Dolphin/GX/GXPixel.h"

// .text 0x80069B68-0x8006C0D0: one translation unit by its literal pool (docs/splits.md,
// 2026-11-20). The title / boot-sequence scenes. Only the small functions have C yet;
// fn_80069BDC, fn_8006A194, fn_8006A500, fn_8006A824, fn_8006AC24, fn_8006AF9C, fn_8006B230,
// fn_8006B78C, fn_8006BB60 and fn_8006BE00 link from the original asm.

extern u8 titleScreenTexturesFileDescriptor[];
extern UIRecordDescriptor lbl_80109378[];
extern UIRecordDescriptor lbl_801092F8[];
extern u8 lbl_80366158[0x30];
extern u8 lbl_803716B8[];
extern DrawingSceneStruct* lbl_803CBD30;
extern struct _GXRenderModeObj lbl_80109250;
extern struct _GXRenderModeObj lbl_8010928C;
extern const struct _GXRenderModeObj* lbl_803CBD34;

void fn_80069B08(void);
void fn_8006B230(void);
void fn_80022B68(void);
void fn_8000900C(void);
void fn_80008E00(void (*func)(void));
void fn_800A7F10(void);
void fn_8006AC24(void* rec);
void fn_80069BDC(u32 a, u32 b, u32 c, f32 alphaA, f32 alphaB);
void fn_80069BDC(u32 a, u32 b, u32 c, f32 alphaA, f32 alphaB) {
    const struct _GXRenderModeObj* rm = &lbl_80109250;
    u8 ca;
    u8 cb;

    GXSetDispCopySrc(0, 0, ((u16*)rm)[2], ((u16*)rm)[3]);
    GXSetDispCopyDst(((u16*)rm)[2], ((u16*)rm)[3]);
    GXSetDispCopyYScale((f32)((u16*)rm)[4] / (f32)((u16*)rm)[3]);
    GXSetScissor(0, 0, 0x260, 0x1C0);
    GXSetViewport(0.0f, 0.0f, 608.0f, 448.0f, -1.0f, 1.0f);
    SetDisplayStateTexture((TextureBody*)(a + b * 0x20 + 4), 0, 0);
    SetDisplayStateTexture((TextureBody*)(a + c * 0x20 + 4), 1, 1);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxAttrFmt(0, 9, 1, 2, 0);
    GXSetVtxDesc(0xB, 1);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetVtxDesc(0xC, 1);
    GXSetVtxAttrFmt(0, 0xC, 1, 5, 0);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxAttrFmt(0, 0xD, 1, 0, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetChanCtrl(5, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(2);
    GXSetTexCoordGen2(0, 1, 4, 0x3C, 0, 0x7D);
    GXSetNumTexGens(1);
    GXSetTevOrder(0, 0xFF, 0xFF, 4);
    GXSetTevOrder(1, 0, 0, 5);
    GXSetTevColorIn(0, 0xF, 0xF, 0xF, 0xA);
    GXSetTevColorOp(0, 0, 0, 0, 1, 1);
    GXSetTevAlphaIn(0, 7, 7, 7, 5);
    GXSetTevAlphaOp(0, 0, 0, 0, 1, 1);
    GXSetTevColorIn(1, 2, 0xA, 8, 0xF);
    GXSetTevColorOp(1, 0, 0, 0, 1, 0);
    GXSetTevAlphaIn(1, 4, 7, 7, 7);
    GXSetTevAlphaOp(1, 0, 0, 0, 1, 0);
    GXSetNumTevStages(2);
    GXBegin(0x80, 0, 4);
    ca = (u8)(255.0f * alphaA);
    GXPosition3s16(0, 0, 0);
    GXColor1u32(0);
    GXColor4u8(ca, ca, ca, 0xFF);
    GXTexCoord2s8(0, 0);
    GXPosition3s16(0x260, 0, 0);
    GXColor1u32(0);
    GXColor4u8(ca, ca, ca, 0xFF);
    GXTexCoord2s8(1, 0);
    GXPosition3s16(0x260, 0x1C0, 0);
    GXColor1u32(0);
    GXColor4u8(ca, ca, ca, 0xFF);
    GXTexCoord2s8(1, 1);
    GXPosition3s16(0, 0x1C0, 0);
    GXColor1u32(0);
    GXColor4u8(ca, ca, ca, 0xFF);
    GXTexCoord2s8(0, 1);
    GXSetTevOrder(1, 0, 1, 5);
    GXBegin(0x80, 0, 4);
    cb = (u8)(255.0f * alphaB);
    GXPosition3s16(0, 0x167, 0);
    GXColor1u32(0);
    GXColor4u8(cb, cb, cb, 0xFF);
    GXTexCoord2s8(0, 0);
    GXPosition3s16(0x260, 0x167, 0);
    GXColor1u32(0);
    GXColor4u8(cb, cb, cb, 0xFF);
    GXTexCoord2s8(1, 0);
    GXPosition3s16(0x260, 0x197, 0);
    GXColor1u32(0);
    GXColor4u8(cb, cb, cb, 0xFF);
    GXTexCoord2s8(1, 1);
    GXPosition3s16(0, 0x197, 0);
    GXColor1u32(0);
    GXColor4u8(cb, cb, cb, 0xFF);
    GXTexCoord2s8(0, 1);
}

void fn_8006A194(u32 a, u32 b, f32 alpha);
void fn_8006A500(u32 a, u32 b, f32 alpha);
void fn_8006A824(u32 a, u32 b, f32 alpha);
void fn_800A7D4C(s32 arg0, void* arg1);
void* _OSAllocFromHeap(s32 alignment, s32 size);
void fn_800ADC40(void* a, void* b);
BOOL fn_800ADB04(void* src, void* dec, u8 a, u8 b);
void fn_80009018(void* arg);
u8 fn_800ADAFC(void);
u32 fn_800AD6BC(void* dec);
void fn_800AD500(void* dec, u8* base);
void fn_800AD95C(void* dec, u8 flag);
BOOL fn_800AD780(void* dec);
void fn_800AD9F4(void* dec);
void fn_800ADBFC(void);
void fn_800AD830(void* dec);
void fn_800AD070(void);
void fn_800ACFB0(void* block);
void fn_8006B668(void);
void fn_8006AF9C(void);
void fn_800214D0(void);
void fn_8002149C(s32 arg);
void unkLoadingCleanupRelated(void* arg);
extern u8 lbl_8037169C[];
extern s32 lbl_803CB8D8;
extern u8 lbl_800EFBA4[];
extern u32 lbl_803CB8DC;
void* allocateAlignedMemoryBlock(s32 align, s32 size);
void* ARAMTransfer(void* file, s32 arg1, s32 arg2, s32 arg3);
void fn_800215F8(void* arg);
void fn_80035750(void* buffer, void* textures, s32 id);
void convertTextureHeader(void* tex);
void fn_8006B78C(void);
void fn_8006BB60(void);
void fn_8006C088(BOOL widescreen);
extern u8 BootSequenceFiles[];
extern u8 drawStadiumRelated;
extern u8 lbl_803C6CF8[];

BOOL fn_80069B68(void) {
    if (diskReadRelated(titleScreenTexturesFileDescriptor, 0x16)) {
        lbl_803CBD30 = insertGraphicDrawingFunction(fn_80069B08, currentDrawingItem->priority);
        addGraphicsElementToScene(lbl_803CBD30, lbl_80109378);
        lbl_80366158[0x2A] = 0;
        return TRUE;
    }
    return FALSE;
}

void fn_8006AF6C(void) {
    if (((u8*)currentDrawingItem)[0x3B] == 0) {
        removeCurrentDrawingItem();
    }
}

void fn_8006B668(void) {
    DrawingSceneStruct* item = currentDrawingItem;
    DrawingSceneStruct* node;

    if (lbl_803716B8[0x1E9] == 0 && *(s16*)((u8*)item + 0x34) != 6) {
        fn_80022B68();
    }

    switch (*(s16*)((u8*)item + 0x34)) {
    case 0:
        if (item->state != 0) {
            node = insertGraphicDrawingFunction(fn_8006B230, currentDrawingItem->priority);
            addGraphicsElementToScene(node, lbl_801092F8);
            changeScene(3, 0);
            ((u8*)item)[0x38] = 0;
            *(s16*)((u8*)item + 0x36) = 1;
            *(s16*)((u8*)item + 0x34) = *(s16*)((u8*)item + 0x34) + 1;
        }
        break;
    case 5:
        if (((u8*)currentDrawingItem)[0x3B] != 0) {
            *(s16*)((u8*)item + 0x34) = 0;
            currentDrawingItem->func = fn_8006AF9C;
        }
        break;
    case 4:
    case 6:
        if (((u8*)currentDrawingItem)[0x3B] != 0) {
            *(s16*)((u8*)item + 0x34) = 0;
            currentDrawingItem->func = fn_8006AF6C;
        }
        break;
    }
}

void fn_8006C088(BOOL widescreen) {
    if (widescreen) {
        lbl_803CBD34 = &lbl_8010928C;
    } else {
        lbl_803CBD34 = &lbl_80109250;
    }
    VIConfigure(lbl_803CBD34);
    VIFlush();
    VIWaitForRetrace();
    VIWaitForRetrace();
}

void fn_8006A194(u32 a, u32 b, f32 alpha) {
    const struct _GXRenderModeObj* rm = &lbl_80109250;
    u8 c;

    GXSetDispCopySrc(0, 0, ((u16*)rm)[2], ((u16*)rm)[3]);
    GXSetDispCopyDst(((u16*)rm)[2], ((u16*)rm)[3]);
    GXSetDispCopyYScale((f32)((u16*)rm)[4] / (f32)((u16*)rm)[3]);
    GXSetScissor(0, 0, 0x260, 0x1C0);
    GXSetViewport(0.0f, 0.0f, 608.0f, 448.0f, -1.0f, 1.0f);
    SetDisplayStateTexture((TextureBody*)(a + b * 0x20 + 4), 0, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxAttrFmt(0, 9, 1, 2, 0);
    GXSetVtxDesc(0xB, 1);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxAttrFmt(0, 0xD, 1, 0, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(1);
    GXSetTexCoordGen2(0, 1, 4, 0x3C, 0, 0x7D);
    GXSetNumTexGens(1);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetTevColorIn(0, 0xA, 0xF, 0xF, 0xF);
    GXSetTevColorOp(0, 0, 0, 0, 1, 0);
    GXSetTevAlphaIn(0, 4, 7, 7, 7);
    GXSetTevAlphaOp(0, 0, 0, 0, 1, 0);
    GXSetNumTevStages(1);
    GXBegin(0x80, 0, 4);
    c = (u8)(255.0f * alpha);
    GXPosition3s16(0xBD, 0x96, 0);
    GXColor4u8(c, c, c, 0xFF);
    GXTexCoord2s8(0, 0);
    GXPosition3s16(0x1A5, 0x96, 0);
    GXColor4u8(c, c, c, 0xFF);
    GXTexCoord2s8(1, 0);
    GXPosition3s16(0x1A5, 0x106, 0);
    GXColor4u8(c, c, c, 0xFF);
    GXTexCoord2s8(1, 1);
    GXPosition3s16(0xBD, 0x106, 0);
    GXColor4u8(c, c, c, 0xFF);
    GXTexCoord2s8(0, 1);
}

void fn_8006A500(u32 a, u32 b, f32 alpha) {
    const struct _GXRenderModeObj* rm = &lbl_80109250;
    u8* tex = (u8*)(a + b * 0x20);
    s32 halfW;
    s32 halfH;
    u8 c;

    GXSetDispCopySrc(0, 0, ((u16*)rm)[2], ((u16*)rm)[3]);
    GXSetDispCopyDst(((u16*)rm)[2], ((u16*)rm)[3]);
    GXSetDispCopyYScale((f32)((u16*)rm)[4] / (f32)((u16*)rm)[3]);
    GXSetScissor(0, 0, 0x260, 0x1C0);
    GXSetViewport(0.0f, 0.0f, 608.0f, 448.0f, -1.0f, 1.0f);
    SetDisplayStateTexture((TextureBody*)(tex + 4), 0, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxAttrFmt(0, 9, 1, 2, 0);
    GXSetVtxDesc(0xB, 1);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxAttrFmt(0, 0xD, 1, 0, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(1);
    GXSetTexCoordGen2(0, 1, 4, 0x3C, 0, 0x7D);
    GXSetNumTexGens(1);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetTevOp(0, 0);
    GXSetNumTevStages(1);
    halfW = *(u16*)(tex + 0xE) >> 1;
    halfH = *(u16*)(tex + 0xC) >> 1;
    GXBegin(0x80, 0, 4);
    c = (u8)(255.0f * alpha);
    GXPosition3s16(0x130 - halfW, 0xE0 - halfH, 0);
    GXColor4u8(c, c, c, 0xFF);
    GXTexCoord2s8(0, 0);
    GXPosition3s16(0x130 + halfW, 0xE0 - halfH, 0);
    GXColor4u8(c, c, c, 0xFF);
    GXTexCoord2s8(1, 0);
    GXPosition3s16(0x130 + halfW, 0xE0 + halfH, 0);
    GXColor4u8(c, c, c, 0xFF);
    GXTexCoord2s8(1, 1);
    GXPosition3s16(0x130 - halfW, 0xE0 + halfH, 0);
    GXColor4u8(c, c, c, 0xFF);
    GXTexCoord2s8(0, 1);
}

void fn_8006A824(u32 a, u32 b, f32 alpha) {
    const struct _GXRenderModeObj* rm = &lbl_80109250;
    u8 c;

    GXSetDispCopySrc(0, 0, ((u16*)rm)[2], ((u16*)rm)[3]);
    GXSetDispCopyDst(((u16*)rm)[2], ((u16*)rm)[3]);
    GXSetDispCopyYScale((f32)((u16*)rm)[4] / (f32)((u16*)rm)[3]);
    GXSetScissor(0, 0, 0x260, 0x1C0);
    GXSetViewport(0.0f, 0.0f, 608.0f, 448.0f, -1.0f, 1.0f);
    SetDisplayStateTexture((TextureBody*)(a + b * 0x20 + 4), 0, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxAttrFmt(0, 9, 1, 2, 0);
    GXSetVtxDesc(0xB, 1);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetVtxDesc(0xC, 1);
    GXSetVtxAttrFmt(0, 0xC, 1, 5, 0);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxAttrFmt(0, 0xD, 1, 0, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetChanCtrl(5, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(2);
    GXSetTexCoordGen2(0, 1, 4, 0x3C, 0, 0x7D);
    GXSetNumTexGens(1);
    GXSetTevOrder(0, 0xFF, 0xFF, 4);
    GXSetTevOrder(1, 0, 0, 5);
    GXSetTevColorIn(0, 0xF, 0xF, 0xF, 0xA);
    GXSetTevColorOp(0, 0, 0, 0, 1, 1);
    GXSetTevAlphaIn(0, 7, 7, 7, 5);
    GXSetTevAlphaOp(0, 0, 0, 0, 1, 1);
    GXSetTevColorIn(1, 2, 0xA, 8, 0xF);
    GXSetTevColorOp(1, 0, 0, 0, 1, 0);
    GXSetTevAlphaIn(1, 4, 7, 7, 7);
    GXSetTevAlphaOp(1, 0, 0, 0, 1, 0);
    GXSetNumTevStages(2);
    GXBegin(0x80, 0, 4);
    c = (u8)(220.0f * alpha);
    GXPosition3s16(0x75, 0x9A, 0);
    GXColor1u32(0);
    GXColor4u8(c, 0, 0, 0xFF);
    GXTexCoord2s8(0, 0);
    GXPosition3s16(0x1ED, 0x9A, 0);
    GXColor1u32(0);
    GXColor4u8(c, 0, 0, 0xFF);
    GXTexCoord2s8(1, 0);
    GXPosition3s16(0x1ED, 0x102, 0);
    GXColor1u32(0);
    GXColor4u8(c, 0, 0, 0xFF);
    GXTexCoord2s8(1, 1);
    GXPosition3s16(0x75, 0x101, 0);
    GXColor1u32(0);
    GXColor4u8(c, 0, 0, 0xFF);
    GXTexCoord2s8(0, 1);
}

#define BOOT_ORTHO(t, b, l, r, n, f)       \
    do {                                   \
        Mtx44 proj;                        \
        Mtx ident;                         \
        PSMTXIdentity(ident);              \
        C_MTXOrtho(proj, t, b, l, r, n, f); \
        GXSetProjection(proj, 1);          \
        GXLoadPosMtxImm(ident, 0);         \
        GXSetCurrentMtx(0);                \
    } while (0)

void fn_8006AC24(void* recArg) {
    u8* rec = (u8*)recArg;

    switch (*(s32*)(rec + 8)) {
    case 0:
        BOOT_ORTHO(-23.0f, 448.0f, 0.0f, 608.0f, -100.0f, 100.0f);
        fn_80069BDC(*(u32*)(rec + 0xC), *(u32*)(rec + 0x10), *(u32*)(rec + 0x14), *(f32*)(rec + 0x18), *(f32*)(rec + 0x1C));
        break;
    case 1:
        BOOT_ORTHO(-23.0f, 448.0f, 0.0f, 608.0f, -100.0f, 100.0f);
        fn_8006A824(*(u32*)(rec + 0xC), *(u32*)(rec + 0x10), *(f32*)(rec + 0x18));
        break;
    case 2:
        BOOT_ORTHO(0.0f, 448.0f, 0.0f, 608.0f, -100.0f, 100.0f);
        fn_8006A500(*(u32*)(rec + 0xC), *(u32*)(rec + 0x10), *(f32*)(rec + 0x18));
        break;
    case 3:
        BOOT_ORTHO(0.0f, 448.0f, 0.0f, 608.0f, -100.0f, 100.0f);
        fn_8006A194(*(u32*)(rec + 0xC), *(u32*)(rec + 0x10), *(f32*)(rec + 0x18));
        break;
    case 4:
        BOOT_ORTHO(0.0f, 448.0f, 0.0f, 640.0f, 0.0f, 1.0f);
        gOz_GXSetTexture(4, 0, 0);
        GXBegin(0x80, 0, 4);
        GXPosition3f32(0.0f, 0.0f, -0.5f);
        GXColor4u8(0, 0, 0, (u8)(255.0f * *(f32*)(rec + 0x18) / 30.0f));
        GXPosition3f32(640.0f, 0.0f, -0.5f);
        GXColor4u8(0, 0, 0, (u8)(255.0f * *(f32*)(rec + 0x18) / 30.0f));
        GXPosition3f32(640.0f, 448.0f, -0.5f);
        GXColor4u8(0, 0, 0, (u8)(255.0f * *(f32*)(rec + 0x18) / 30.0f));
        GXPosition3f32(0.0f, 448.0f, -0.5f);
        GXColor4u8(0, 0, 0, (u8)(255.0f * *(f32*)(rec + 0x18) / 30.0f));
        break;
    }
}

void fn_8006AF9C(void) {
    DrawingSceneStruct* item = currentDrawingItem;
    u8* it = (u8*)item;
    u8* rec;
    s16 state = *(s16*)(it + 0x34);

    switch (state) {
    case 0:
        it[0x38] = 0;
        *(s16*)(it + 0x36) = 0;
        *(void**)(it + 0x1C) = _OSAllocFromHeap(0x20, 0x1C0);
        memset(*(void**)(it + 0x1C), 0, 0x1C0);
        *(void**)(it + 0x20) = _OSAllocFromHeap(0x20, 0x400000);
        fn_800ADC40(*(void**)(it + 0x20), (void*)0x400000);
        *(s16*)(it + 0x34) = *(s16*)(it + 0x34) + 1;
        break;
    case 1:
        if (fn_800ADB04(BootSequenceFiles, *(void**)(it + 0x1C), 0, 0)) {
            fn_80009018(*(void**)(it + 0x1C));
            *(s16*)(it + 0x34) = *(s16*)(it + 0x34) + 1;
        }
        break;
    case 2:
        if (fn_800ADAFC()) {
            *(void**)(it + 0x24) = _OSAllocFromHeap(0x20, fn_800AD6BC(*(void**)(it + 0x1C)));
            fn_800AD500(*(void**)(it + 0x1C), *(u8**)(it + 0x24));
            fn_800AD95C(*(void**)(it + 0x1C), 1);
            *(s16*)(it + 0x34) = *(s16*)(it + 0x34) + 1;
        }
        break;
    case 3:
        if (*(u16*)((u8*)&AtBat_ButtonInput1 + 4) & 0x1000) {
            *(s16*)(it + 0x34) = 5;
            break;
        }
    case 4:
        if (fn_800AD780(*(void**)(it + 0x1C))) {
            fn_80009018(NULL);
            fn_800AD9F4(*(void**)(it + 0x1C));
            fn_800ADBFC();
            fn_800ACFB0(*(void**)(it + 0x24));
            fn_800ACFB0(*(void**)(it + 0x20));
            fn_800ACFB0(*(void**)(it + 0x1C));
            *(s16*)(it + 0x34) = 0;
            ((u8*)currentDrawingItem)[0x3B] = 0;
            currentDrawingItem->func = fn_8006B668;
            return;
        }
        break;
    case 5:
        it[0x38]++;
        if (it[0x38] == 0x1E) {
            fn_800AD830(*(void**)(it + 0x1C));
            *(s16*)(it + 0x34) = 4;
        }
        break;
    }

    if (*(s16*)(it + 0x34) >= 3) {
        fn_800AD070();
    }
    if (it[0x38] != 0) {
        rec = *(u8**)(it + 0x18) + drawStadiumRelated * 0x20;
        *(s32*)(rec + 8) = 4;
        *(f32*)(rec + 0x18) = (f32)it[0x38];
        *(u32*)rec = 0;
        *(void**)(rec + 4) = fn_8006AC24;
        fn_800A7D4C(0xE, rec);
    }
}

#define BOOT_REC(n) ((UIRecord*)graphicsRelatedArray[((MenuScene*)item)->firstHandle + (n)].object)

void fn_8006B230(void) {
    DrawingSceneStruct* item = currentDrawingItem;
    u8* parent = (u8*)item->currentDrawingItem;
    s32 i;
    s32 vol;
    u32 h;

    switch (*(s16*)(parent + 0x34)) {
    case 1:
        if (*(u16*)(parent + 0x36) != 0) {
            *(u16*)(parent + 0x36) = 0;
            changeScene(1, 6);
            BOOT_REC(0)->flags |= UI_FLAG_VISIBLE;
            BOOT_REC(1)->frame = 0;
            BOOT_REC(2)->frame = 0;
            BOOT_REC(1)->flags |= UI_FLAG_VISIBLE;
            BOOT_REC(2)->flags |= UI_FLAG_VISIBLE;
            BOOT_REC(1)->playMode = 0;
            BOOT_REC(2)->playMode = 0;
        } else if (lbl_8037169C[0x12] != 0) {
            BOOT_REC(1)->playMode = 1;
            BOOT_REC(2)->playMode = 1;
            parent[0x3C] = 8;
            *(u32*)(parent + 0x30) = sndFXStartEx(0x318, 0x6E, 0xFF, 0);
            *(u16*)(parent + 0x36) = 0x12C;
            *(s16*)(parent + 0x34) = *(s16*)(parent + 0x34) + 1;
        }
        break;
    case 2:
        if ((BOOT_REC(2)->frame >> 16) == 0x64) {
            *(s16*)(parent + 0x34) = *(s16*)(parent + 0x34) + 1;
        }
        break;
    case 3:
        if (*(u16*)((u8*)&AtBat_ButtonInput1 + 2) & 0x1100) {
            for (i = 0; i < 4; i++) {
                if (*(u16*)((u8*)&AtBat_ButtonInput1 + i * 0x20 + 2) & 0x1100) {
                    lbl_80366158[0x27] = i;
                    break;
                }
            }
            *(s16*)(parent + 0x34) = 4;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if ((s32)sndFXCheck(*(u32*)(parent + 0x30)) == -1) {
            if (lbl_803CB8D8 != 0) {
                *(s16*)(parent + 0x34) = 6;
            } else {
                *(s16*)(parent + 0x34) = 5;
            }
            lbl_803CB8D8 = lbl_803CB8D8 ^ 1;
        }
        if (*(s16*)(parent + 0x34) != 3) {
            BOOT_REC(1)->playMode = 0;
            BOOT_REC(2)->playMode = 0;
            BOOT_REC(0)->frame = 0;
            BOOT_REC(0)->playMode = 1;
        }
        break;
    case 4:
    case 5:
    case 6:
        if ((s32)sndFXCheck(*(u32*)(parent + 0x30)) != -1) {
            if ((s8)parent[0x3C] > 0) {
                parent[0x3C] = parent[0x3C] - 1;
                if (sndFXCtrl(*(u32*)(parent + 0x30), 7, (u8)(((s8)parent[0x3C] * 0x6E) / 8)) != 0) {
                    break;
                }
            }
            if ((s8)parent[0x3C] >= 0) {
                parent[0x3C] = -1;
                sndFXKeyOff(*(u32*)(parent + 0x30));
            }
        }
        if ((BOOT_REC(0)->frame >> 16) == 0x14) {
            removeGraphicsElementFromScene(item);
            switch (*(s16*)(parent + 0x34)) {
            case 5:
                parent[0x3B] = 1;
                break;
            case 4:
                fn_800214D0();
                fn_8002149C(0x2F);
                unkLoadingCleanupRelated(*(void**)(parent + 0x14));
                unregisterObjectByID(0x16);
                unkLoadingCleanupRelated(*(void**)(parent + 0x28));
                unkLoadingCleanupRelated(*(void**)(parent + 0x18));
                parent[0x3B] = 2;
                break;
            case 6:
                fn_800214D0();
                fn_8002149C(0x2F);
                fn_800214D0();
                fn_8002149C(0x25);
                unkLoadingCleanupRelated(*(void**)(parent + 0x14));
                unregisterObjectByID(0x16);
                unkLoadingCleanupRelated(*(void**)(parent + 0x28));
                unkLoadingCleanupRelated(*(void**)(parent + 0x18));
                parent[0x3B] = 3;
                break;
            }
            removeCurrentDrawingItem();
        }
        break;
    }
}

#define BOOT_FADE_SETUP(mode, extra)                                              \
    do {                                                                          \
        *(s32*)(*(u8**)(it + 0x18) + drawStadiumRelated * 0x20 + 8) = (mode);     \
        *(u32*)(*(u8**)(it + 0x18) + drawStadiumRelated * 0x20 + 0xC) = **(u32**)(it + 0x14); \
        *(s32*)(*(u8**)(it + 0x18) + drawStadiumRelated * 0x20 + 0x10) = (extra); \
        *(f32*)(*(u8**)(it + 0x18) + drawStadiumRelated * 0x20 + 0x18) = (f32)it[0x38] / 30.0f; \
        *(u32*)(*(u8**)(it + 0x18) + drawStadiumRelated * 0x20) = 0;              \
        *(void**)(*(u8**)(it + 0x18) + drawStadiumRelated * 0x20 + 4) = fn_8006AC24; \
        fn_800A7D4C(0, *(u8**)(it + 0x18) + drawStadiumRelated * 0x20);           \
    } while (0)

void fn_8006B78C(void) {
    DrawingSceneStruct* item = currentDrawingItem;
    u8* it = (u8*)item;
    BOOL flag = TRUE;
    s16 state = *(s16*)(it + 0x34);

    switch (state) {
    case 0:
        fn_8000900C();
        lbl_80366158[0x20] = 1;
    case 3:
    case 6:
        it[0x38]++;
        if (it[0x38] == 0x1E) {
            *(s16*)(it + 0x36) = 0x3C;
            *(s16*)(it + 0x34) = *(s16*)(it + 0x34) + 1;
        }
        break;
    case 1:
    case 4:
    case 7:
        if (*(u16*)(it + 0x36) != 0) {
            *(u16*)(it + 0x36) = *(u16*)(it + 0x36) - 1;
        } else {
            *(s16*)(it + 0x34) = *(s16*)(it + 0x34) + 1;
        }
        break;
    case 8:
        flag = FALSE;
    case 2:
    case 5:
        if (it[0x38] != 0) {
            it[0x38]--;
            flag = TRUE;
        } else if (state == 8) {
            if (lbl_803C6CF8[0x715] == 1) {
                *(s16*)(it + 0x34) = *(s16*)(it + 0x34) + 1;
            }
        } else {
            *(s16*)(it + 0x34) = *(s16*)(it + 0x34) + 1;
        }
        break;
    }

    if (flag) {
        fn_80022B68();
    }
    if (*(s16*)(it + 0x34) == 9) {
        *(s16*)(it + 0x36) = 0;
        *(s16*)(it + 0x34) = 0;
        fn_80008E00(fn_800A7F10);
        currentDrawingItem->func = fn_8006AF9C;
    } else if (*(s16*)(it + 0x34) >= 6) {
        if (*(s16*)(it + 0x34) < 9) {
            BOOT_FADE_SETUP(3, 0);
        }
    } else if (*(s16*)(it + 0x34) >= 3) {
        BOOT_FADE_SETUP(2, 2);
    } else if (*(s16*)(it + 0x34) >= 0) {
        BOOT_FADE_SETUP(1, 1);
    }
}

void fn_8006BB60(void) {
    DrawingSceneStruct* item = currentDrawingItem;
    u8* it = (u8*)item;
    u8* rec;

    fn_80022B68();
    switch (*(s16*)(it + 0x34)) {
    case 0:
        it[0x38]++;
        if (it[0x38] == 0x1E) {
            *(u16*)(it + 0x36) = 0x5A;
            *(s16*)(it + 0x34) = *(s16*)(it + 0x34) + 1;
        }
        break;
    case 1:
        if ((*(u16*)(it + 0x36))-- == 0) {
            fn_8000900C();
            lbl_80366158[0x20] = 1;
            *(u16*)(it + 0x36) = 0xD98;
            *(s16*)(it + 0x34) = *(s16*)(it + 0x34) + 1;
        }
        break;
    case 2:
    case 3:
        if (*(s16*)(it + 0x34) == 2) {
            it[0x39]++;
            if (it[0x39] == 0x1E) {
                *(s16*)(it + 0x34) = 3;
            }
        }
        if (*(s16*)(it + 0x34) == 3) {
            it[0x39]--;
            if (it[0x39] == 0) {
                *(s16*)(it + 0x34) = 2;
            }
        }
        *(u16*)(it + 0x36) = *(u16*)(it + 0x36) - 1;
        if (*(u16*)(it + 0x36) == 0 || *(u16*)&AtBat_ButtonInput1 != 0) {
            *(s16*)(it + 0x34) = 4;
        }
        break;
    case 4:
        it[0x38]--;
        if (it[0x38] == 0) {
            *(s16*)(it + 0x34) = 0;
            currentDrawingItem->func = fn_8006B78C;
        }
        break;
    }

    rec = *(u8**)(it + 0x18) + drawStadiumRelated * 0x20;
    *(s32*)(rec + 8) = 0;
    *(u32*)(*(u8**)(it + 0x18) + drawStadiumRelated * 0x20 + 0xC) = **(u32**)(it + 0x14);
    *(s32*)(*(u8**)(it + 0x18) + drawStadiumRelated * 0x20 + 0x10) = 6;
    *(f32*)(*(u8**)(it + 0x18) + drawStadiumRelated * 0x20 + 0x18) = (f32)it[0x38] / 30.0f;
    *(s32*)(*(u8**)(it + 0x18) + drawStadiumRelated * 0x20 + 0x14) = 7;
    *(f32*)(*(u8**)(it + 0x18) + drawStadiumRelated * 0x20 + 0x1C) = ((f32)it[0x39] / 30.0f) * (f32)it[0x38] / 30.0f;
    *(u32*)(*(u8**)(it + 0x18) + drawStadiumRelated * 0x20) = 0;
    *(void**)(*(u8**)(it + 0x18) + drawStadiumRelated * 0x20 + 4) = fn_8006AC24;
    fn_800A7D4C(0, *(u8**)(it + 0x18) + drawStadiumRelated * 0x20);
}

void fn_8006BE00(void) {
    u8* d = (u8*)&lbl_80109250;
    DrawingSceneStruct* item = currentDrawingItem;
    u8* it = (u8*)item;
    u8* p;
    GXColor clear;

    switch (*(s16*)(it + 0x34)) {
    case 0:
        it[0x3A] = lbl_8037169C[0x13];
        if (lbl_8037169C[0x13] != 0) {
            changeScene(1, 6);
        }
        *(u32*)&clear = lbl_803CB8DC;
        GXSetCopyClear(clear, 0xFFFFFF);
        *(u16*)(it + 0x36) = 0;
        *(void**)(it + 0x18) = allocateAlignedMemoryBlock(0x20, 0x40);
        *(void**)(it + 0x28) = allocateAlignedMemoryBlock(0x20, *(u32*)(d + 0x98 + 4) & 0x0FFFFFFF);
        ARAMTransfer(d + 0x98, *(s32*)(it + 0x28), 0, 0);
        *(s16*)(it + 0x34) = *(s16*)(it + 0x34) + 1;
        break;
    case 1:
        if (lbl_803C6CF8[0x715] == 1) {
            p = *(u8**)(it + 0x28);
            *(u32*)p = *(u32*)p + (u32)p;
            p = *(u8**)(it + 0x28);
            *(u32*)(p + 4) = *(u32*)(p + 4) + (u32)p;
            fn_80035750(*(void**)(*(u8**)(it + 0x28) + 4), *(void**)*(u8**)(it + 0x28), 0x16);
            *(void**)(it + 0x14) = allocateAlignedMemoryBlock(0x20, *(u32*)(d + 0x88 + 4) & 0x0FFFFFFF);
            ARAMTransfer(d + 0x88, *(s32*)(it + 0x14), 0, 0);
            *(s16*)(it + 0x34) = *(s16*)(it + 0x34) + 1;
        }
        break;
    case 2:
        if (*(u16*)(it + 0x36) != 0) {
            *(u16*)(it + 0x36) = *(u16*)(it + 0x36) - 1;
            break;
        }
        if (it[0x3A] != 0 && lbl_8037169C[0x12] == 0) {
            break;
        }
        if (lbl_803C6CF8[0x715] != 1) {
            break;
        }
        if (lbl_80366158[0x29] == 0 || lbl_80366158[0x29] == 1) {
            fn_80008E00((void (*)(void))fn_8006C088);
        }
        *(void**)(d + 0x168 + 8) = currentDrawingItem;
        fn_800215F8(d + 0x168);
        p = *(u8**)(it + 0x14);
        *(u32*)p = *(u32*)p + (u32)p;
        convertTextureHeader(*(void**)*(u8**)(it + 0x14));
        *(s16*)(it + 0x34) = 0;
        it[0x38] = 0;
        it[0x39] = 0;
        switch (lbl_80366158[0x29]) {
        case 0:
            currentDrawingItem->func = fn_8006BB60;
            break;
        case 1:
            currentDrawingItem->func = fn_8006B78C;
            break;
        case 2:
            currentDrawingItem->func = fn_8006B668;
            break;
        }
        break;
    }
}

