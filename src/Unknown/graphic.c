#include "Unknown/graphic.h"
#include "Dolphin/os.h"
#include "Dolphin/gx.h"
#include "Dolphin/vi.h"

OSThread* GXSetCurrentGXThread(void);
s32 OSSignalSemaphore(OSSemaphore* sem);
GXFifoObj* GXInit(void* base, u32 size);
void fn_800AD054(int lo, int hi);
void fn_800A84C4(u32 retraceCount);
extern u8 lbl_802ED140[];
extern GXColor lbl_803CBAD0;

extern struct {
    /* 0x000 */ void* xfb;
    /* 0x004 */ void* xfbEnd;
    /* 0x008 */ GXFifoObj* fifo;
    /* 0x00C */ GXRenderModeObj* renderMode;
    /* 0x010 */ GXRenderModeObj renderModeOverscan;
    /* 0x04C */ DrawCallbackNode* callbacks;
    /* 0x050 */ void* fifoEnd;
    /* 0x054 */ void* arenaHi;
    /* 0x058 */ u32 spareSize;
    /* 0x05C */ OSThreadQueue doneQueue;
    /* 0x064 */ u8 _064[0x68 - 0x64];
    /* 0x068 */ OSThread drawThread;
    /* 0x380 */ OSThreadQueue wakeQueue;
    /* 0x388 */ OSSemaphore doneSemaphore;
    /* 0x394 */ u8 _394[2];
    /* 0x396 */ u8 drawing;
    /* 0x397 */ u8 drawPhase;
} lbl_803C7420;

void someGFXRenderingFn(void) {
    lbl_803C7420.drawPhase = 0;
    while (1) {
        GXRenderModeObj* rmode;
        DrawCallbackNode* node;
        u32 link;

        OSSleepThread(&lbl_803C7420.wakeQueue);
        GXSetCurrentGXThread();
        lbl_803C7420.drawing = TRUE;
        rmode = lbl_803C7420.renderMode;
        if (rmode->field_rendering) {
            GXSetViewportJitter(0.0f, 0.0f, rmode->fbWidth, rmode->efbHeight, 0.0f, 1.0f, VIGetNextField());
        } else {
            GXSetViewport(0.0f, 0.0f, rmode->fbWidth, rmode->efbHeight, 0.0f, 1.0f);
        }
        GXInvalidateVtxCache();
        node = lbl_803C7420.callbacks;
        while (1) {
            link = node->link;
            if (link == 0) {
                break;
            }
            if (!(link & 1) && (link & 2) == lbl_803C7420.drawPhase && node->func != NULL) {
                node->func();
            }
            node = (DrawCallbackNode*)(link & ~3);
        }
        lbl_803C7420.drawing = FALSE;
        OSSignalSemaphore(&lbl_803C7420.doneSemaphore);
    }
}

void fn_800A7D4C(s32 phase, DrawCallbackNode* node) {
    u32* slots = (u32*)lbl_803C7420.callbacks;

    node->link = (slots[phase] & ~3) | (node->link & 3);
    slots[phase] = (u32)node | 1;
}

void fn_800A7D7C(DrawCallbackNode* first, s32 count) {
    u32* link = (u32*)first;

    lbl_803C7420.callbacks = first;
    count--;
    do {
        *link = ((u32)link + 4) | 1;
        link++;
    } while (--count != 0);
    *link = 0;
}

void fn_800A7DB0(void) {
    OSSleepThread(&lbl_803C7420.doneQueue);
    GXSetColorUpdate(TRUE);
    VIFlush();
    GXDrawDone();
    GXCopyDisp(lbl_803C7420.xfb, TRUE);
}

static void configureDisplayCopy(void) {
    GXRenderModeObj* rmode;

    VIConfigure(lbl_803C7420.renderMode);
    VIFlush();
    VIWaitForRetrace();
    VIWaitForRetrace();
    GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
    rmode = lbl_803C7420.renderMode;
    GXSetDispCopySrc(0, 0, rmode->fbWidth, rmode->efbHeight);
    GXSetDispCopyDst(rmode->fbWidth, rmode->xfbHeight);
    GXSetDispCopyYScale((f32)rmode->xfbHeight / (f32)rmode->efbHeight);
    GXSetScissor(0, 0, rmode->fbWidth, rmode->efbHeight);
    GXSetCopyFilter(rmode->aa, rmode->sample_pattern, TRUE, rmode->vfilter);
}

void fn_800A7E00(void) {
    GXAdjustForOverscan(&GXNtsc480Int, &lbl_803C7420.renderModeOverscan, 0, 0x10);
    lbl_803C7420.renderMode = &lbl_803C7420.renderModeOverscan;
    configureDisplayCopy();
}

void fn_800A7F10(s32 overscan) {
    if (overscan != 0) {
        GXAdjustForOverscan(&GXNtsc480Int, &lbl_803C7420.renderModeOverscan, 0, 0x10);
        lbl_803C7420.renderMode = &lbl_803C7420.renderModeOverscan;
        configureDisplayCopy();
    } else {
        configureDisplayCopy();
    }
}

void initRenderMode(GXRenderModeObj* rmode, u32 fifoSize, u16 overscan) {
    void* arenaLo;
    void* arenaHi;
    void* xfbEnd;
    u32 xfbBytes;
    GXRenderModeObj* mode;

    lbl_803C7420._394[0] = 0;
    lbl_803C7420._394[1] = 0;
    OSCreateThread(&lbl_803C7420.drawThread, (OSThreadStartFunction)someGFXRenderingFn, NULL, lbl_802ED140 + 0x2000, 0x2000, 12, 1);
    OSInitThreadQueue(&lbl_803C7420.wakeQueue);
    OSInitSemaphore(&lbl_803C7420.doneSemaphore, 0);
    OSResumeThread(&lbl_803C7420.drawThread);
    OSInitThreadQueue(&lbl_803C7420.doneQueue);
    VIInit();

    if (rmode != NULL) {
        lbl_803C7420.renderMode = rmode;
    } else {
        switch (VIGetTvFormat()) {
        case VI_NTSC:
            lbl_803C7420.renderMode = &GXNtsc480IntDf;
            break;
        case VI_PAL:
            lbl_803C7420.renderMode = &GXPal528IntDf;
            break;
        case VI_MPAL:
            lbl_803C7420.renderMode = &GXMpal480IntDf;
            break;
        default:
            OSPanic("graphic.c", 0x60, "sNp_InitRenderMode: invalid TV format\n");
            break;
        }
        GXAdjustForOverscan(lbl_803C7420.renderMode, &lbl_803C7420.renderModeOverscan, 0, overscan);
        lbl_803C7420.renderMode = &lbl_803C7420.renderModeOverscan;
    }

    arenaLo = OSGetArenaLo();
    arenaHi = OSGetArenaHi();
    mode = lbl_803C7420.renderMode;
    lbl_803C7420.xfb = (void*)(((u32)arenaLo + 0x1F) & ~0x1F);
    xfbBytes = ((mode->fbWidth + 0xF) & ~0xF) * mode->xfbHeight * 2;
    xfbEnd = (void*)(((u32)lbl_803C7420.xfb + xfbBytes + 0x1F) & ~0x1F);
    lbl_803C7420.xfbEnd = xfbEnd;
    lbl_803C7420.fifo = GXInit(xfbEnd, fifoSize);
    lbl_803C7420.fifoEnd = (u8*)xfbEnd + fifoSize;
    fn_800AD054((int)lbl_803C7420.fifoEnd, (int)arenaHi);
    lbl_803C7420.arenaHi = arenaHi;
    lbl_803C7420.spareSize = ((u32)arenaHi - (u32)lbl_803C7420.fifoEnd + 0x1F) & ~0x1F;
    OSSetArenaLo(arenaHi);

    VIConfigure(lbl_803C7420.renderMode);
    VISetPreRetraceCallback(fn_800A84C4);
    if (lbl_803C7420.renderMode->aa) {
        GXSetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
    } else {
        GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
    }
    mode = lbl_803C7420.renderMode;
    GXSetDispCopySrc(0, 0, mode->fbWidth, mode->efbHeight);
    GXSetDispCopyDst(mode->fbWidth, mode->xfbHeight);
    GXSetDispCopyYScale((f32)mode->xfbHeight / (f32)mode->efbHeight);
    GXSetCopyFilter(mode->aa, mode->sample_pattern, TRUE, mode->vfilter);
    GXSetDispCopyGamma(GX_GM_1_0);
    GXCopyDisp(lbl_803C7420.xfb, TRUE);
    VISetNextFrameBuffer(lbl_803C7420.xfb);
    VIFlush();
    VIWaitForRetrace();
    if (lbl_803C7420.renderMode->viTVmode & 1) {
        VIWaitForRetrace();
    }
    GXSetScissorBoxOffset(0, 0);
    mode = lbl_803C7420.renderMode;
    GXSetScissor(0, 0, mode->fbWidth, mode->efbHeight);
    GXSetViewport(0.0f, 0.0f, mode->fbWidth, mode->efbHeight, 0.0f, 1.0f);
    GXSetCopyClear(lbl_803CBAD0, 0xFFFFFF);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    VISetBlack(FALSE);
}
