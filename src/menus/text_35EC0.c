#include "menus/text_35EC0.h"
#include "text/text.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x800b0a14.h"
#include "Dolphin/GX/GXFrameBuffer.h"

// Local prototypes for symbols owned by other units.
s16 fn_2_53BC8(void *arg0);
void fn_2_4E7EC(void);
void fn_2_4E824(void);
void fn_2_4E8E0(void);
s32 fn_2_4EABC(void);
void fn_2_515DC(s32 arg);
void fn_2_54474(void);
void fn_2_245C8(void);
void fn_2_422FC(s32 arg);
void fn_2_42388(void);
void changeScene(u8 scene, u16 arg1);
void load_Icon(void *scene, s32 handle, u32 part, u32 element, s32 frame);
BOOL fn_80068514(u32 frames, u32 target);
BOOL fn_8006862C(u32 frames, u32 target);
void playStream(u8 streamId);
void jukeboxCmd(u32 cmd);
void fn_80036134(void *scene, s32 a, s32 b, s32 c);
void *_OSAllocFromHeap(s32 heap, u32 size);
void *memset(void *dst, s32 c, u32 n);
void fn_80009018(void *p);
BOOL fn_800ADB04(void *src, void *dec, u8 a, u8 b);
BOOL fn_800ADAFC(void);
u32 fn_800AD6BC(void *dec);
void fn_800AD500(void *dec, void *base);
void fn_800AD95C(void *dec, u8 flag);
void fn_800AD070(void);
s32 fn_800AED24(void);
BOOL fn_800AD780(void *dec);
void fn_800AD9F4(void *dec);
void fn_800ADBFC(void);
void fn_800AD830(void *dec);
void fn_800ADC40(void *buf, u32 size);

extern u8 *lbl_2_bss_1A824C;
extern u8 *lbl_2_bss_1A8248;
extern u8 *lbl_2_bss_1A8234;
extern u8 *lbl_2_bss_1A8230;
extern u8 lbl_8037169C[];
extern u8 AtBat_ButtonInput1[];
extern u8 movie2FileDescriptor[];
extern u8 movie3FileDescriptor[];
extern u8 lbl_2_data_34E0[];
extern s16 lbl_2_data_C8F8[];
extern s16 lbl_2_data_C904[];
extern u32 lbl_2_data_12270;

typedef struct MovieWork {
    /* 0x00 */ u8 flag0;
    /* 0x04 */ u32 bufSize;
    /* 0x08 */ void *buf;
    /* 0x0C */ void *unkC;
    /* 0x10 */ void *decoder;
} MovieWork;

extern MovieWork lbl_2_bss_15A0;

// Work area behind lbl_2_bss_1A824C (the 0x190000 window).
#define WORK_BASE()   (lbl_2_bss_1A824C + 0x190000)
#define UI_1A8234()   (lbl_2_bss_1A8234 + 0x160000)
#define UI_1A8230()   (lbl_2_bss_1A8230 + 0x30000)
#define ITEM_STATE(item) (*(u8 *)((u8 *)(item) + 0x28))
#define ITEM_S16(item, off) (*(s16 *)((u8 *)(item) + (off)))

static inline s16 workS16(s32 off) {
    return *(s16 *)(WORK_BASE() + off);
}

static inline TextGraphicsObject *nodeOf(TextScene *scene, TextHandleRec *rec) {
    return graphicsRelatedArray[scene->firstHandle + rec->handle].object;
}

static inline void nodeShow(TextGraphicsObject *node) {
    node->flags |= UI_FLAG_VISIBLE;
}

static inline void nodeHide(TextGraphicsObject *node) {
    node->flags &= ~UI_FLAG_VISIBLE;
}

static inline void nodeSetByte68(TextGraphicsObject *node, u8 value) {
    *(u8 *)((u8 *)node + 0x68) = value;
}

static inline u32 nodeW5C(TextGraphicsObject *node) {
    return *(u32 *)((u8 *)node + 0x5C);
}

static inline void nodeSetW5C(TextGraphicsObject *node, u32 value) {
    *(u32 *)((u8 *)node + 0x5C) = value;
}

// .text:0x00037D98 size:0x16C mapped:0x80676E2C
void fn_2_37D98(void) {
    DrawingSceneStruct *item = currentDrawingItem;

    switch (ITEM_STATE(item)) {
    case 0:
        changeScene(1, 6);
        ITEM_S16(item, 0x14) = 0x26AE;
        ITEM_S16(item, 0x16) = 0;
        *(u8 *)(UI_1A8234() + 0x264B) = 1;
        ITEM_STATE(item) = 1;
        break;
    case 1: {
        s16 old = ITEM_S16(item, 0x14);

        ITEM_S16(item, 0x14) = old - 1;
        if (old == 0) {
            ITEM_STATE(item) = 2;
        }
        ITEM_S16(item, 0x16) += 1;
        break;
    }
    case 2:
        if ((u8)fn_8006862C(0x1A4, 0) == 0) {
            ITEM_STATE(item) = 3;
        }
        break;
    case 3:
        changeScene(3, 6);
        ITEM_STATE(item) = 4;
        break;
    case 4:
        if (lbl_8037169C[0x13] != 0) {
            currentDrawingItem->currentDrawingItem->state = 1;
            removeCurrentDrawingItem();
            ITEM_STATE(item) = 0;
            if (WORK_BASE()[0x783F] == 1) {
                currentDrawingItem->currentDrawingItem->state = 1;
                removeCurrentDrawingItem();
                ITEM_STATE(item) = 0;
            }
        }
        break;
    }
}

// .text:0x00037D94 size:0x4 mapped:0x80676E28
void fn_2_37D94(void) {
    return;
}

// .text:0x00037D90 size:0x4 mapped:0x80676E24
void fn_2_37D90(void) {
    return;
}

// .text:0x00037D8C size:0x4 mapped:0x80676E20
void fn_2_37D8C(void) {
    return;
}

// .text:0x00037D88 size:0x4 mapped:0x80676E1C
void fn_2_37D88(void) {
    return;
}

// .text:0x00037D84 size:0x4 mapped:0x80676E18
void fn_2_37D84(void) {
    return;
}

// .text:0x00037D80 size:0x4 mapped:0x80676E14
void fn_2_37D80(void) {
    return;
}

// .text:0x00037D7C size:0x4 mapped:0x80676E10
void fn_2_37D7C(void) {
    return;
}

// .text:0x00037D78 size:0x4 mapped:0x80676E0C
void fn_2_37D78(void) {
    return;
}

// .text:0x00037D74 size:0x4 mapped:0x80676E08
void fn_2_37D74(void) {
    return;
}

// .text:0x00037D70 size:0x4 mapped:0x80676E04
void fn_2_37D70(void) {
    return;
}

// .text:0x000379D0 size:0x3A0 mapped:0x80676A64
void fn_2_379D0(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    u8 *base = WORK_BASE();

    switch (ITEM_STATE(item)) {
    case 0:
        if (fn_2_4EABC() == 1) {
            ITEM_STATE(item) = 1;
        }
        break;
    case 1: {
        u32 clear = lbl_2_data_12270;
        GXSetCopyClear(*(GXColor *)&clear, 0x00FFFFFF);
        changeScene(1, 6);
        fn_2_515DC(4);
        *(u8 *)(UI_1A8234() + 0x2992) = 0;
        *(u8 *)(UI_1A8230() + 0x2A86) = 0;
        fn_2_54474();
        fn_2_245C8();
        *(s16 *)(base + 0x76E4) = 0x168;
        lbl_2_bss_15A0.flag0 = 0;
        ITEM_STATE(item) = 2;
        break;
    }
    case 2:
        ITEM_STATE(item) = 3;
        break;
    case 3:
        if (lbl_8037169C[0x12] != 0) {
            DrawingSceneStruct *node = insertGraphicDrawingFunction(fn_2_37630, 2);
            ITEM_STATE(node) = 0;
            ITEM_S16(item, 0x10) = 0;
            ITEM_STATE(item) = 4;
        }
        break;
    case 4:
        if (ITEM_S16(item, 0x10) != 0) {
            if (lbl_2_bss_15A0.flag0 != 0) {
                changeScene(3, 6);
                *(u8 *)(UI_1A8234() + 0x2838) = 1;
                *(u8 *)(UI_1A8234() + 0x2839) = 1;
                *(u8 *)(UI_1A8234() + 0x2835) = 1;
                *(u8 *)(UI_1A8234() + 0x2837) = 1;
                ITEM_STATE(item) = 7;
            } else {
                playStream(0xB);
                fn_2_422FC(lbl_2_bss_1A8248[0x441C] == 5 ? 1 : 0);
                ITEM_STATE(insertGraphicDrawingFunction(fn_2_42388, 2)) = 0;
                ITEM_S16(item, 0x10) = 0;
                ITEM_STATE(item) = 5;
            }
        }
        break;
    case 5: {
        BOOL result = fn_80068514(0x78, 0x7F);

        if (ITEM_S16(item, 0x10) == 1) {
            base[0x783F] = 0;
            changeScene(3, 6);
            *(u8 *)(UI_1A8234() + 0x2838) = 1;
            *(u8 *)(UI_1A8234() + 0x2839) = 1;
            *(u8 *)(UI_1A8234() + 0x2835) = 1;
            *(u8 *)(UI_1A8234() + 0x2837) = 1;
            ITEM_STATE(item) = 6;
        }
        {
            s32 pad = (s8)base[0x7863];
            u8 *input = AtBat_ButtonInput1 + pad * 32;

            if (*(u16 *)(input + 2) & 0x1000) {
                if ((u8)result == 0) {
                    base[0x783F] = 1;
                }
            }
        }
        break;
    }
    case 6:
        if ((u8)fn_8006862C(0x78, 0) == 0) {
            ITEM_STATE(item) = 7;
        }
        break;
    case 7:
        if (lbl_8037169C[0x13] != 0) {
            u32 clear = lbl_2_data_12270;
            jukeboxCmd(3);
            GXSetCopyClear(*(GXColor *)&clear, 0x00FFFFFF);
            *(u8 *)(UI_1A8234() + 0x2992) = 1;
            *(u8 *)(UI_1A8230() + 0x2A86) = 1;
            ITEM_STATE(item) = 8;
        }
        break;
    case 8:
        fn_2_4E8E0();
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        ITEM_STATE(item) = 0;
        break;
    }
}

// .text:0x00037630 size:0x3A0 mapped:0x806766C4
void fn_2_37630(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    MovieWork *work = &lbl_2_bss_15A0;
    u8 *base = WORK_BASE();

    switch (ITEM_STATE(item)) {
    case 0:
        *(u32 *)(base + 0x76B0) = 0;
        *(u32 *)(base + 0x76B4) = 0;
        *(u32 *)(base + 0x76B8) = 0;
        *(u32 *)(base + 0x76BC) = 0;
        fn_2_4E824();
        work->decoder = _OSAllocFromHeap(0x20, 0x1C0);
        memset(work->decoder, 0, 0x1C0);
        work->bufSize = 0x400000;
        work->buf = _OSAllocFromHeap(0x20, 0x400000);
        fn_800ADC40(work->buf, work->bufSize);
        ITEM_STATE(item)++;
        break;
    case 1:
        if (fn_800ADB04(movie2FileDescriptor, work->decoder, 1, 0)) {
            fn_80009018(work->decoder);
            ITEM_STATE(item)++;
        }
        break;
    case 2:
        if (fn_800ADAFC()) {
            u32 size = fn_800AD6BC(work->decoder);
            void *buf = _OSAllocFromHeap(0x20, size);
            work->unkC = buf;
            fn_800AD500(work->decoder, buf);
            fn_800AD95C(work->decoder, 1);
            ITEM_STATE(item)++;
        }
        break;
    case 3: {
        s32 pad = (s8)base[0x7863];
        u8 *input = AtBat_ButtonInput1 + pad * 32;

        if (*(u16 *)(input + 2) & 0x1000) {
            work->flag0 = 1;
            fn_800AD830(work->decoder);
            ITEM_STATE(item)++;
        } else {
            *(u32 *)(base + 0x76B4) += 1;
            fn_800AD070();
            if (fn_800AED24() == 1) {
                u32 n = *(u32 *)(base + 0x76B0) + 1;
                s32 set = (lbl_2_bss_1A8248[0x441C] == 5) ? 1 : 0;
                u8 *table = lbl_2_data_34E0 + set * 0x60;
                u32 count = *(u32 *)(base + 0x76B8);
                u8 *ent = table + count * 0xC;

                *(u32 *)(base + 0x76B0) = n;
                if (n == *(u32 *)ent && *(u32 *)(base + 0x76BC) == 0 && *(s32 *)ent != -1) {
                    *(s16 *)(base + 0x774C) = *(s16 *)(ent + 10);
                    *(u32 *)(base + 0x76BC) = 1;
                    *(u8 *)(UI_1A8234() + 0x264E) = 1;
                } else if (n == *(u32 *)(ent + 4) && *(u32 *)(base + 0x76BC) == 1 &&
                           *(s32 *)ent != -1) {
                    *(u8 *)(UI_1A8234() + 0x2838) = 1;
                    *(u32 *)(base + 0x76B8) += 1;
                    *(u32 *)(base + 0x76BC) = 0;
                }
            }
            if (fn_800AD780(work->decoder)) {
                ITEM_STATE(item)++;
            }
        }
        break;
    }
    case 4:
        if (fn_800AD780(work->decoder)) {
            fn_80009018(0);
            fn_800AD9F4(work->decoder);
            fn_800ADBFC();
            ITEM_STATE(item)++;
        }
        break;
    case 5:
        fn_2_4E7EC();
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        ITEM_STATE(item) = 0;
        break;
    }
}

// .text:0x00037460 size:0x1D0 mapped:0x806764F4
void fn_2_37460(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    MovieWork *work = &lbl_2_bss_15A0;

    switch (ITEM_STATE(item)) {
    case 0:
        fn_2_4E824();
        work->decoder = _OSAllocFromHeap(0x20, 0x1C0);
        memset(work->decoder, 0, 0x1C0);
        work->bufSize = 0x400000;
        work->buf = _OSAllocFromHeap(0x20, 0x400000);
        fn_800ADC40(work->buf, work->bufSize);
        ITEM_STATE(item)++;
        break;
    case 1:
        if (fn_800ADB04(movie3FileDescriptor, work->decoder, 1, 0)) {
            fn_80009018(work->decoder);
            ITEM_STATE(item)++;
        }
        break;
    case 2:
        if (fn_800ADAFC()) {
            u32 size = fn_800AD6BC(work->decoder);
            void *base = _OSAllocFromHeap(0x20, size);
            work->unkC = base;
            fn_800AD500(work->decoder, base);
            fn_800AD95C(work->decoder, 1);
            ITEM_STATE(item)++;
        }
        break;
    case 3:
        fn_800AD070();
        if (fn_800AD780(work->decoder)) {
            ITEM_STATE(item)++;
        }
        break;
    case 4:
        if (fn_800AD780(work->decoder)) {
            fn_80009018(0);
            fn_800AD9F4(work->decoder);
            fn_800ADBFC();
            ITEM_STATE(item)++;
        }
        break;
    case 5:
        fn_2_4E7EC();
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        ITEM_STATE(item) = 0;
        break;
    }
}

// .text:0x0003745C size:0x4 mapped:0x806764F0
void fn_2_3745C(void) {
    return;
}

// .text:0x00037430 size:0x2C mapped:0x806764C4
void fn_2_37430(TextScene *scene, TextHandleRec *rec) {
    nodeHide(nodeOf(scene, rec));
}

// .text:0x0003735C size:0xD4 mapped:0x806763F0
void fn_2_3735C(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        rec->state = 0x25;
        break;
    }
}

// .text:0x000372AC size:0xB0 mapped:0x80676340
void fn_2_372AC(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        rec->state = 0x26;
        break;
    case 2:
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x25;
        break;
    case 0x25:
        break;
    }
}

// .text:0x000370F8 size:0x1B4 mapped:0x8067618C
void fn_2_370F8(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeShow(nodeOf(scene, rec));
        nodeSetByte68(nodeOf(scene, rec), 1);
        rec->state = 0x25;
        break;
    case 5:
        nodeSetByte68(nodeOf(scene, rec), 4);
        rec->state = 6;
        break;
    case 6:
        if ((nodeW5C(nodeOf(scene, rec)) >> 16) == 0) {
            nodeSetByte68(nodeOf(scene, rec), 0);
            rec->state = 7;
        }
        break;
    case 7:
        nodeHide(nodeOf(scene, rec));
        break;
    }
}

// .text:0x00036F44 size:0x1B4 mapped:0x80675FD8
void fn_2_36F44(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeShow(nodeOf(scene, rec));
        nodeSetByte68(nodeOf(scene, rec), 1);
        rec->state = 0x25;
        break;
    case 5:
        nodeSetByte68(nodeOf(scene, rec), 4);
        rec->state = 6;
        break;
    case 6:
        if ((nodeW5C(nodeOf(scene, rec)) >> 16) == 0) {
            nodeSetByte68(nodeOf(scene, rec), 0);
            rec->state = 7;
        }
        break;
    case 7:
        nodeHide(nodeOf(scene, rec));
        break;
    }
}

// .text:0x00036D04 size:0x240 mapped:0x80675D98
void fn_2_36D04(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeSetW5C(nodeOf(scene, rec), 0x000F0000);
        nodeShow(nodeOf(scene, rec));
        nodeSetByte68(nodeOf(scene, rec), 1);
        rec->state = 3;
        break;
    case 3:
        if ((nodeW5C(nodeOf(scene, rec)) >> 16) >= (u16)lbl_2_data_C8F8[rec->unk10]) {
            nodeSetByte68(nodeOf(scene, rec), 0);
            rec->state = 0x25;
        }
        break;
    case 5:
        nodeSetW5C(nodeOf(scene, rec), (u32)lbl_2_data_C8F8[rec->unk10] << 16);
        nodeSetByte68(nodeOf(scene, rec), 1);
        rec->state = 6;
        break;
    case 6:
        if ((nodeW5C(nodeOf(scene, rec)) >> 16) >= (u16)lbl_2_data_C904[rec->unk10]) {
            nodeSetByte68(nodeOf(scene, rec), 0);
            rec->state = 7;
        }
        break;
    case 7:
        nodeHide(nodeOf(scene, rec));
        break;
    }
}

// .text:0x00036B30 size:0x1D4 mapped:0x80675BC4
void fn_2_36B30(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeSetByte68(nodeOf(scene, rec), 1);
        rec->state = 0x25;
        break;
    case 0x25:
        if (workS16(0x7298 + rec->unkA * 2) != 0) {
            nodeShow(nodeOf(scene, rec));
        } else {
            nodeHide(nodeOf(scene, rec));
        }
        break;
    case 5:
        nodeSetByte68(nodeOf(scene, rec), 0);
        rec->state = 6;
        break;
    case 6:
        nodeHide(nodeOf(scene, rec));
        break;
    }
}

// .text:0x0003697C size:0x1B4 mapped:0x80675A10
void fn_2_3697C(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeShow(nodeOf(scene, rec));
        nodeSetByte68(nodeOf(scene, rec), 1);
        rec->state = 0x25;
        break;
    case 5:
        nodeSetByte68(nodeOf(scene, rec), 4);
        rec->state = 6;
        break;
    case 6:
        if ((nodeW5C(nodeOf(scene, rec)) >> 16) == 0) {
            nodeSetByte68(nodeOf(scene, rec), 0);
            rec->state = 7;
        }
        break;
    case 7:
        nodeHide(nodeOf(scene, rec));
        break;
    }
}

// .text:0x00036750 size:0x22C mapped:0x806757E4
void fn_2_36750(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        if (rec->unkA == 0) {
            if (workS16(0x72AA) != 0xA) {
                load_Icon(scene, rec->handle, 1, 0x54, workS16(0x72AA));
            }
        } else {
            load_Icon(scene, rec->handle, 1, 0x54, *(lbl_2_bss_1A8248 + 0x441C));
        }
        nodeShow(nodeOf(scene, rec));
        nodeSetByte68(nodeOf(scene, rec), 1);
        rec->state = 3;
        break;
    case 3:
        if ((nodeW5C(nodeOf(scene, rec)) >> 16) >= 0x15) {
            nodeSetByte68(nodeOf(scene, rec), 0);
            rec->state = 0x25;
        }
        break;
    case 5:
        nodeSetByte68(nodeOf(scene, rec), 4);
        rec->state = 6;
        break;
    case 6:
        if ((nodeW5C(nodeOf(scene, rec)) >> 16) == 0) {
            nodeSetByte68(nodeOf(scene, rec), 0);
            rec->state = 7;
        }
        break;
    case 7:
        nodeHide(nodeOf(scene, rec));
        break;
    }
}

// .text:0x00036590 size:0x1C0 mapped:0x80675624
void fn_2_36590(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeShow(nodeOf(scene, rec));
        nodeSetByte68(nodeOf(scene, rec), 1);
        fn_80036134(scene, 0x12, workS16(0x72B0), rec->handle);
        rec->state = 0x25;
        break;
    case 0x25:
        fn_80036134(scene, 0x12, workS16(0x72B0), rec->handle);
        break;
    case 5:
        nodeSetByte68(nodeOf(scene, rec), 0);
        rec->state = 6;
        break;
    case 6:
        nodeHide(nodeOf(scene, rec));
        break;
    }
}

// .text:0x000363C8 size:0x1C8 mapped:0x8067545C
void fn_2_363C8(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeShow(nodeOf(scene, rec));
        nodeSetByte68(nodeOf(scene, rec), 1);
        fn_80036134(scene, 0x293, workS16(0x72B0) + 1, rec->handle);
        rec->state = 0x25;
        break;
    case 0x25:
        fn_80036134(scene, 0x293, workS16(0x72B0) + 1, rec->handle);
        break;
    case 5:
        nodeSetByte68(nodeOf(scene, rec), 0);
        rec->state = 6;
        break;
    case 6:
        nodeHide(nodeOf(scene, rec));
        break;
    }
}

// .text:0x00036204 size:0x1C4 mapped:0x80675298
void fn_2_36204(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        if (workS16(0x72AC + rec->unkA * 2) == 3) {
            nodeShow(nodeOf(scene, rec));
            nodeSetByte68(nodeOf(scene, rec), 1);
        }
        rec->state = 0x25;
        break;
    case 5:
        if (workS16(0x72AC + rec->unkA * 2) == 3) {
            nodeSetByte68(nodeOf(scene, rec), 0);
        }
        rec->state = 6;
        break;
    case 6:
        nodeHide(nodeOf(scene, rec));
        break;
    }
}

// .text:0x00036074 size:0x190 mapped:0x80675108
void fn_2_36074(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 2:
        nodeSetW5C(nodeOf(scene, rec), 0);
        nodeShow(nodeOf(scene, rec));
        nodeSetByte68(nodeOf(scene, rec), 1);
        rec->state = 0x25;
        break;
    case 5:
        nodeSetByte68(nodeOf(scene, rec), 0);
        rec->state = 6;
        break;
    case 6:
        nodeHide(nodeOf(scene, rec));
        break;
    }
}

// .text:0x00035EC0 size:0x1B4 mapped:0x80674F54
void fn_2_35EC0(TextScene *scene, TextHandleRec *rec) {
    s16 result = fn_2_53BC8(rec);
    if (result != -1) {
        rec->state = result;
    }
    switch (rec->state) {
    case 0:
        nodeHide(nodeOf(scene, rec));
        rec->state = 0x26;
        break;
    case 1:
    case 3:
        break;
    case 2:
        nodeShow(nodeOf(scene, rec));
        nodeSetByte68(nodeOf(scene, rec), 1);
        rec->state = 0x25;
        break;
    case 5:
        nodeSetByte68(nodeOf(scene, rec), 4);
        rec->state = 6;
        break;
    case 6:
        if ((nodeW5C(nodeOf(scene, rec)) >> 16) == 0) {
            nodeSetByte68(nodeOf(scene, rec), 0);
            rec->state = 7;
        }
        break;
    case 7:
        nodeHide(nodeOf(scene, rec));
        break;
    case 0x25:
        break;
    }
}
