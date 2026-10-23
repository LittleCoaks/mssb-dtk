#include "menus/text_5E84C.h"
#include "text/text.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x800a7568.h"

// Local prototypes for symbols owned by other units.
s16 fn_2_53BC8(void *arg0);
void load_Icon(void *scene, s32 handle, u32 part, u32 element, s32 frame);
void resetGameStadiumStateOnExit(void);
void fn_80035B50(s32 arg0);
void fn_800ACFB0(void *block);
void fn_800111B4(void *block);
s32 diskReadRelated(void *desc, s32 arg1);
void *ARAMTransfer(void *file, s32 arg1, s32 arg2, s32 arg3);
s16 fn_8006C268(void *p);
u32 fn_8006C100(s32 value);

extern u8 *lbl_2_bss_1A824C;
extern u8 *lbl_2_bss_1A8244;
extern u8 *lbl_2_bss_1A8240;
extern u8 *lbl_2_bss_1A823C;
extern u8 lbl_2_bss_33FBF0[];
extern u8 lbl_2_bss_33FBF5[];
extern s16 lbl_2_data_20C48[];
extern u8 recordsScreenTextFileDescriptor[];
extern u8 menuBarsFileDescriptorRecordsScreen[];

// Work area behind lbl_2_bss_1A824C (the 0x190000 window).
#define WORK_BASE() (lbl_2_bss_1A824C + 0x190000)
#define SCREEN_TEXT_7A0 (*(void **)((u8 *)&screenTextArray + 0x7A0))
#define ITEM_STATE(item) (*(s8 *)((u8 *)(item) + 0x28))
#define REC_UNK6(rec) (*(s16 *)((u8 *)(rec) + 0x6))
#define NUMBER_BLANK_FRAME 10

typedef struct CopyRec {
    u32 value;
    s16 a;
    s16 b;
} CopyRec;

static inline TextGraphicsObject *nodeOf(TextScene *scene, TextHandleRec *rec) {
    return graphicsRelatedArray[scene->firstHandle + rec->handle].object;
}

static inline void nodeShow(TextGraphicsObject *node) {
    node->flags |= UI_FLAG_VISIBLE;
}

static inline void nodeHide(TextGraphicsObject *node) {
    node->flags &= ~UI_FLAG_VISIBLE;
}

static inline void nodeSetPlayMode(TextGraphicsObject *node, u8 value) {
    ((UIRecord *)node)->playMode = value;
}

static inline void nodeSetElement(TextGraphicsObject *node, u16 element) {
    ((UIRecord *)node)->elementIndex = element;
}

static inline u32 nodeFrame(TextGraphicsObject *node) {
    return ((UIRecord *)node)->frame;
}

static inline void nodeSetFrame(TextGraphicsObject *node, u32 value) {
    ((UIRecord *)node)->frame = value;
}

// Makes the record visible from its first frame and leaves it in the shown state.
static void showRecord(TextScene *scene, TextHandleRec *rec) {
    nodeSetFrame(nodeOf(scene, rec), 0);
    nodeShow(nodeOf(scene, rec));
    nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_FORWARD);
    rec->state = 0x25;
}

static void hideRecord(TextScene *scene, TextHandleRec *rec) {
    nodeHide(nodeOf(scene, rec));
    rec->state = 0x26;
}

static void startCountdown(TextHandleRec *rec) {
    REC_UNK6(rec) = 10;
    rec->state = 6;
}

static void tickCountdown(TextScene *scene, TextHandleRec *rec) {
    s16 remaining = REC_UNK6(rec);
    REC_UNK6(rec) = remaining - 1;
    if (remaining <= 0) {
        nodeHide(nodeOf(scene, rec));
    }
}

// Draws the low `digitCount` decimal digits of `value`, one icon part per digit
// (part 1 is the ones digit). Digits above the magnitude of `value` are blank.
static void drawNumber(TextScene *scene, TextHandleRec *rec, s32 value, s32 digitCount, u32 element) {
    s32 place = 1;
    s32 part;
    for (part = 1; part <= digitCount; part++) {
        s32 digit = (value / place) % 10;
        if (part > 1 && value < place) {
            digit = NUMBER_BLANK_FRAME;
        }
        load_Icon(scene, rec->handle, part, element, digit);
        place *= 10;
    }
}

// .text:0x00060DF4 size:0x188 mapped:0x8069FE88
void fn_2_60DF4(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        hideRecord(scene, rec);
        break;
    case 2:
        showRecord(scene, rec);
        break;
    case 1:
    case 3:
    case 4:
    case 0x25:
        break;
    case 5:
        startCountdown(rec);
        break;
    case 6:
        tickCountdown(scene, rec);
        break;
    }
}

// .text:0x00060C78 size:0x17C mapped:0x8069FD0C
void fn_2_60C78(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        hideRecord(scene, rec);
        break;
    case 2:
        nodeShow(nodeOf(scene, rec));
        nodeSetFrame(nodeOf(scene, rec), (u32)*(u8 *)(WORK_BASE() + 0x7418) << 16);
        rec->state = 0x25;
        break;
    case 1:
    case 3:
    case 4:
    case 0x25:
        break;
    case 5:
        startCountdown(rec);
        break;
    case 6:
        tickCountdown(scene, rec);
        break;
    }
}

// .text:0x00060AF0 size:0x188 mapped:0x8069FB84
void fn_2_60AF0(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        hideRecord(scene, rec);
        break;
    case 2:
        showRecord(scene, rec);
        break;
    case 1:
    case 3:
    case 4:
    case 0x25:
        break;
    case 5:
        startCountdown(rec);
        break;
    case 6:
        tickCountdown(scene, rec);
        break;
    }
}

// .text:0x00060968 size:0x188 mapped:0x8069F9FC
void fn_2_60968(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        hideRecord(scene, rec);
        break;
    case 2:
        showRecord(scene, rec);
        break;
    case 1:
    case 3:
    case 4:
    case 0x25:
        break;
    case 5:
        startCountdown(rec);
        break;
    case 6:
        tickCountdown(scene, rec);
        break;
    }
}

// .text:0x000607DC size:0x18C mapped:0x8069F870
void fn_2_607DC(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        hideRecord(scene, rec);
        break;
    case 2: {
        s16 value = fn_8006C268(WORK_BASE() + 0x7430);
        nodeSetFrame(nodeOf(scene, rec), (fn_8006C100(value) & 0xFF) << 16);
        nodeShow(nodeOf(scene, rec));
        rec->state = 0x25;
        break;
    }
    case 1:
    case 3:
    case 4:
    case 0x25:
        break;
    case 5:
        startCountdown(rec);
        break;
    case 6:
        tickCountdown(scene, rec);
        break;
    }
}

// .text:0x0006051C size:0x2C0 mapped:0x8069F5B0
void fn_2_6051C(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        hideRecord(scene, rec);
        break;
    case 2: {
        s32 value = fn_8006C268(WORK_BASE() + 0x7430);
        drawNumber(scene, rec, value, 4, 0x74);
        showRecord(scene, rec);
        break;
    }
    case 1:
    case 3:
    case 4:
    case 0x25:
        break;
    case 5:
        startCountdown(rec);
        break;
    case 6:
        tickCountdown(scene, rec);
        break;
    }
}

// .text:0x00060394 size:0x188 mapped:0x8069F428
void fn_2_60394(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        hideRecord(scene, rec);
        break;
    case 2:
        showRecord(scene, rec);
        break;
    case 1:
    case 3:
    case 4:
    case 0x25:
        break;
    case 5:
        startCountdown(rec);
        break;
    case 6:
        tickCountdown(scene, rec);
        break;
    }
}

// .text:0x0006020C size:0x188 mapped:0x8069F2A0
void fn_2_6020C(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        hideRecord(scene, rec);
        break;
    case 2:
        showRecord(scene, rec);
        break;
    case 1:
    case 3:
    case 4:
    case 0x25:
        break;
    case 5:
        startCountdown(rec);
        break;
    case 6:
        tickCountdown(scene, rec);
        break;
    }
}

// .text:0x00060084 size:0x188 mapped:0x8069F118
void fn_2_60084(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        hideRecord(scene, rec);
        break;
    case 2:
        showRecord(scene, rec);
        break;
    case 1:
    case 3:
    case 4:
    case 0x25:
        break;
    case 5:
        startCountdown(rec);
        break;
    case 6:
        tickCountdown(scene, rec);
        break;
    }
}

// .text:0x0005FDC4 size:0x2C0 mapped:0x8069EE58
void fn_2_5FDC4(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        hideRecord(scene, rec);
        break;
    case 2: {
        s16 unitIndex = rec->unkA;
        s32 value = 0;
        if (unitIndex >= 0 && unitIndex <= 5) {
            value = *(s16 *)(WORK_BASE() + 0x7430 + unitIndex * 2);
        } else if (unitIndex == 6) {
            value = *(s16 *)(WORK_BASE() + 0x743C);
        } else if (unitIndex == 7) {
            value = *(s16 *)(WORK_BASE() + 0x743E);
        }
        if (unitIndex >= 0 && unitIndex <= 7) {
            drawNumber(scene, rec, value, 3, 0x74);
        }
        showRecord(scene, rec);
        break;
    }
    case 1:
    case 3:
    case 4:
    case 0x25:
        break;
    case 5:
        startCountdown(rec);
        break;
    case 6:
        tickCountdown(scene, rec);
        break;
    }
}

// .text:0x0005F458 size:0x96C mapped:0x8069E4EC
void fn_2_5F458(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        hideRecord(scene, rec);
        break;
    case 2: {
        s16 unitIndex = rec->unkA;
        if (unitIndex >= 0 && unitIndex <= 5) {
            s32 value = *(s16 *)(WORK_BASE() + 0x7404 + unitIndex * 2);
            TextGraphicsObject *node;
            switch (unitIndex) {
            case 0:
                node = nodeOf(scene, rec);
                nodeSetElement(node, 0x75);
                drawNumber(scene, rec, value, 4, 6);
                break;
            case 1:
                node = nodeOf(scene, rec);
                if (value < 10) {
                    nodeSetElement(node, 0x79);
                } else if (value < 100) {
                    nodeSetElement(node, 0x78);
                } else if (value < 1000) {
                    nodeSetElement(node, 0x77);
                } else if (value < 10000) {
                    nodeSetElement(node, 0x76);
                }
                drawNumber(scene, rec, value, 4, 6);
                break;
            case 2:
                node = nodeOf(scene, rec);
                if (value < 10) {
                    nodeSetElement(node, 0x7D);
                } else if (value < 100) {
                    nodeSetElement(node, 0x7C);
                }
                drawNumber(scene, rec, value, 2, 6);
                break;
            case 3:
                nodeSetElement(nodeOf(scene, rec), 0x7B);
                drawNumber(scene, rec, value, 3, 6);
                break;
            case 4:
                nodeSetElement(nodeOf(scene, rec), 0x7A);
                drawNumber(scene, rec, value, 4, 6);
                break;
            case 5:
                node = nodeOf(scene, rec);
                if (value < 10) {
                    nodeSetElement(node, 0x80);
                } else if (value < 100) {
                    nodeSetElement(node, 0x7F);
                } else if (value < 1000) {
                    nodeSetElement(node, 0x7E);
                }
                drawNumber(scene, rec, value, 3, 6);
                break;
            }
        }
        showRecord(scene, rec);
        break;
    }
    case 1:
    case 3:
    case 0x25:
        break;
    case 5:
        startCountdown(rec);
        break;
    case 6:
        tickCountdown(scene, rec);
        break;
    }
}

// .text:0x0005F2A8 size:0x1B0 mapped:0x8069E33C
void fn_2_5F2A8(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        hideRecord(scene, rec);
        break;
    case 2:
        load_Icon(scene, rec->handle, 1, 0x71, *(u8 *)(WORK_BASE() + 0x7416));
        showRecord(scene, rec);
        break;
    case 1:
    case 3:
    case 4:
    case 0x25:
        break;
    case 5:
        startCountdown(rec);
        break;
    case 6:
        tickCountdown(scene, rec);
        break;
    }
}

// .text:0x0005F08C size:0x21C mapped:0x8069E120
void fn_2_5F08C(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        hideRecord(scene, rec);
        break;
    case 2: {
        s32 value = *(u8 *)(WORK_BASE() + 0x7417);
        load_Icon(scene, rec->handle, 1, 6, value % 10);
        load_Icon(scene, rec->handle, 2, 6, (value / 10) % 10);
        showRecord(scene, rec);
        break;
    }
    case 1:
    case 3:
    case 4:
    case 0x25:
        break;
    case 5:
        startCountdown(rec);
        break;
    case 6:
        tickCountdown(scene, rec);
        break;
    }
}

// .text:0x0005EEBC size:0x1D0 mapped:0x8069DF50
void fn_2_5EEBC(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        hideRecord(scene, rec);
        break;
    case 2:
        showRecord(scene, rec);
        break;
    case 1:
    case 3:
    case 0x25:
        break;
    case 5:
        nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_FORWARD);
        rec->state = 6;
        break;
    case 6:
        if ((nodeFrame(nodeOf(scene, rec)) >> 16) >= 10) {
            nodeSetPlayMode(nodeOf(scene, rec), UI_PLAY_STOP);
            rec->state = 7;
        }
        break;
    }
    if (rec->state == 7) {
        nodeHide(nodeOf(scene, rec));
    }
}

// .text:0x0005EE34 size:0x88 mapped:0x8069DEC8
void fn_2_5EE34(void) {
    WORK_BASE()[0x72BC] = 1;
    WORK_BASE()[0x72C0] = 1;
    resetGameStadiumStateOnExit();
    fn_80035B50(10);
    if (SCREEN_TEXT_7A0 != NULL) {
        fn_800ACFB0(SCREEN_TEXT_7A0);
        SCREEN_TEXT_7A0 = NULL;
    }
    lbl_2_bss_1A823C[0x34] = 0;
}

// .text:0x0005ED3C size:0xF8 mapped:0x8069DDD0
void fn_2_5ED3C(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    s8 state = ITEM_STATE(item);

    switch (state) {
    case 0:
        SCREEN_TEXT_7A0 = ARAMTransfer(recordsScreenTextFileDescriptor, 0, 1, 0);
        ITEM_STATE(item) = 1;
        break;
    case 1:
        if (lbl_803C6CF8.cancel.bytes[1] == 1) {
            fn_800111B4(SCREEN_TEXT_7A0);
            ITEM_STATE(item) = 2;
        }
        break;
    case 2:
        if (diskReadRelated(menuBarsFileDescriptorRecordsScreen, 10) != 0) {
            ITEM_STATE(item) = 3;
        }
        break;
    case 3:
        item->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        ITEM_STATE(item) = 0;
        break;
    }
}

// .text:0x0005EB78 size:0x1C4 mapped:0x8069DC0C
void fn_2_5EB78(void) {
    u8 flags[4];
    s32 i;
    s32 k;
    u8 *src = lbl_2_bss_1A8244;

    lbl_2_bss_33FBF5[0] = 0;
    for (i = 0; i < 4; i++) {
        flags[i] = 0;
        for (k = 0; k < 5; k++) {
            if (src[0xC6 + i + 4 * k] != 0) {
                flags[i] = 1;
            }
        }
    }

    lbl_2_bss_33FBF0[0] = flags[0];
    lbl_2_bss_33FBF0[1] = flags[1];
    lbl_2_bss_33FBF0[2] = flags[2];
    lbl_2_bss_33FBF0[3] = flags[3];

    if ((s32)WORK_BASE()[0x7862] == 1) {
        *(u32 *)(lbl_2_bss_1A8240 + 0x00) = 9999;
        *(u32 *)(lbl_2_bss_1A8240 + 0x08) = 123;
        *(u32 *)(lbl_2_bss_1A8240 + 0x10) = 45;
        *(u32 *)(lbl_2_bss_1A8240 + 0x18) = 6;
        *(u32 *)(lbl_2_bss_1A8240 + 0x20) = 0;
        *(s16 *)(lbl_2_bss_1A8240 + 0x06) = 0;
        *(s16 *)(lbl_2_bss_1A8240 + 0x0E) = 1;
        *(s16 *)(lbl_2_bss_1A8240 + 0x16) = 2;
        *(s16 *)(lbl_2_bss_1A8240 + 0x1E) = 3;
        *(s16 *)(lbl_2_bss_1A8240 + 0x26) = 4;
        *(u32 *)(lbl_2_bss_1A8240 + 0x28) = 9876;
        *(u32 *)(lbl_2_bss_1A8240 + 0x30) = 543;
        *(u32 *)(lbl_2_bss_1A8240 + 0x38) = 21;
        *(u32 *)(lbl_2_bss_1A8240 + 0x40) = 1;
        *(u32 *)(lbl_2_bss_1A8240 + 0x48) = 0;
        *(s16 *)(lbl_2_bss_1A8240 + 0x2E) = 0;
        *(s16 *)(lbl_2_bss_1A8240 + 0x36) = 1;
        *(s16 *)(lbl_2_bss_1A8240 + 0x3E) = 2;
        *(s16 *)(lbl_2_bss_1A8240 + 0x46) = 3;
        *(s16 *)(lbl_2_bss_1A8240 + 0x4E) = 4;
    }
}

// .text:0x0005E84C size:0x32C mapped:0x8069D8E0
void fn_2_5E84C(void) {
    s32 i = 0;
    s32 k;
    s32 off = 0;

    do {
        if (i == 6) {
            *(u32 *)(WORK_BASE() + 0x72EC) = *(u32 *)(lbl_2_bss_1A8240 + 0x118);
            *(s16 *)(WORK_BASE() + 0x72F0) = *(s16 *)(lbl_2_bss_1A8240 + 0x11C);
            *(s16 *)(WORK_BASE() + 0x72F2) = *(s16 *)(lbl_2_bss_1A8240 + 0x11E);
            *(u32 *)(WORK_BASE() + 0x72F4) = *(u32 *)(lbl_2_bss_1A8240 + 0x120);
            *(s16 *)(WORK_BASE() + 0x72F8) = *(s16 *)(lbl_2_bss_1A8240 + 0x124);
            *(s16 *)(WORK_BASE() + 0x72FA) = *(s16 *)(lbl_2_bss_1A8240 + 0x126);
            *(u32 *)(WORK_BASE() + 0x72FC) = *(u32 *)(lbl_2_bss_1A8240 + 0x128);
            *(s16 *)(WORK_BASE() + 0x7300) = *(s16 *)(lbl_2_bss_1A8240 + 0x12C);
            *(s16 *)(WORK_BASE() + 0x7302) = *(s16 *)(lbl_2_bss_1A8240 + 0x12E);
            *(u32 *)(WORK_BASE() + 0x7304) = *(u32 *)(lbl_2_bss_1A8240 + 0x130);
            *(s16 *)(WORK_BASE() + 0x7308) = *(s16 *)(lbl_2_bss_1A8240 + 0x134);
            *(s16 *)(WORK_BASE() + 0x730A) = *(s16 *)(lbl_2_bss_1A8240 + 0x136);
            *(u32 *)(WORK_BASE() + 0x730C) = *(u32 *)(lbl_2_bss_1A8240 + 0x138);
            *(s16 *)(WORK_BASE() + 0x7310) = *(s16 *)(lbl_2_bss_1A8240 + 0x13C);
            *(s16 *)(WORK_BASE() + 0x7312) = *(s16 *)(lbl_2_bss_1A8240 + 0x13E);
        } else {
            u8 *src = lbl_2_bss_1A8240;
            u8 *dst = WORK_BASE() + 0x72EC + off;
            CopyRec *srcRec = (CopyRec *)(src + lbl_2_data_20C48[i] * 0x28 + 0x28);
            CopyRec *dstRec = (CopyRec *)dst;
            for (k = 0; k < 5; k++) {
                dstRec[k].value = srcRec[k].value;
                dstRec[k].a = srcRec[k].a;
                dstRec[k].b = srcRec[k].b;
            }
        }
        i++;
        off += 0x28;
    } while (i < 7);

    {
        *(u32 *)(WORK_BASE() + 0x72C4) = *(u32 *)(lbl_2_bss_1A8240 + 0x00);
        *(s16 *)(WORK_BASE() + 0x72CA) = *(s16 *)(lbl_2_bss_1A8240 + 0x06);
        *(u32 *)(WORK_BASE() + 0x72CC) = *(u32 *)(lbl_2_bss_1A8240 + 0x08);
        *(s16 *)(WORK_BASE() + 0x72D2) = *(s16 *)(lbl_2_bss_1A8240 + 0x0E);
        *(u32 *)(WORK_BASE() + 0x72D4) = *(u32 *)(lbl_2_bss_1A8240 + 0x10);
        *(s16 *)(WORK_BASE() + 0x72DA) = *(s16 *)(lbl_2_bss_1A8240 + 0x16);
        *(u32 *)(WORK_BASE() + 0x72DC) = *(u32 *)(lbl_2_bss_1A8240 + 0x18);
        *(s16 *)(WORK_BASE() + 0x72E2) = *(s16 *)(lbl_2_bss_1A8240 + 0x1E);
        *(u32 *)(WORK_BASE() + 0x72E4) = *(u32 *)(lbl_2_bss_1A8240 + 0x20);
        *(s16 *)(WORK_BASE() + 0x72EA) = *(s16 *)(lbl_2_bss_1A8240 + 0x26);
    }
}
