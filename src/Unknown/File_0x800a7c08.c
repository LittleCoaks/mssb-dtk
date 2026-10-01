#include "Unknown/File_0x800a7c08.h"
#include "Dolphin/os.h"
#include "Dolphin/gx.h"
#include "Dolphin/vi.h"

OSThread* GXSetCurrentGXThread(void);
s32 OSSignalSemaphore(OSSemaphore* sem);

/* One entry of the draw-callback list. `link` is the next entry's address
 * with two flag bits in its low bits. */
typedef struct DrawCallbackNode {
    /* 0x0 */ u32 link;
    /* 0x4 */ void (*func)(void);
} DrawCallbackNode;

extern struct {
    /* 0x000 */ u8 _000[0xC];
    /* 0x00C */ GXRenderModeObj* renderMode;
    /* 0x010 */ u8 _010[0x4C - 0x10];
    /* 0x04C */ DrawCallbackNode* callbacks;
    /* 0x050 */ u8 _050[0x380 - 0x50];
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
