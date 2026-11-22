#include "mssbTypes.h"
#include "Dolphin/vi.h"
#include "Unknown/spani_default.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x800204cc.h"

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
void fn_8006AF9C(void);
void fn_8006B230(void);
void fn_80022B68(void);

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
