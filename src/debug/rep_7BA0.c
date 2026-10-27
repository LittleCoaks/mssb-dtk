#define REP_HEADER_DATA_FN getRepHeaderData_rep7BA0
#define SQRT2_LINKAGE static
#include "debug/rep_7BA0.h"
#include "header_rep_data.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x800acf14.h"
#include "static/UnknownHomes_Static.h"
#include "game/UnknownHomes_Game.h"
#include "stl/mem.h"

typedef struct RepLoadState {
    /* 0x00 */ u32 bufSize;
    /* 0x04 */ void *buf;
    /* 0x08 */ void *scratch;
    /* 0x0C */ void *ctx;
} RepLoadState;

typedef struct RepScene {
    /* 0x00 */ void (*func)(void);
    /* 0x04 */ struct DrawingSceneStruct *prev;
    /* 0x08 */ struct DrawingSceneStruct *next;
    /* 0x0C */ struct DrawingSceneStruct *parent;
    /* 0x10 */ s16 state;
    /* 0x12 */ u16 priority;
    /* 0x14 */ u8 step;
    /* 0x15 */ u8 index;
} RepScene;

extern u8 movie1FileDescriptorDebug[];
extern MemoryStack lbl_80366158;

extern s32 fn_800AD070(void);
extern void fn_800ADC40(void *buf, u32 size);
extern s32 fn_800AD6BC(void *ctx);
extern void fn_800ADB04(void *desc, void *ctx, s32 a, s32 b);
extern s32 fn_800ADAFC(void);
extern void fn_800AD500(void *ctx, void *mem);
extern void fn_800AD95C(void *ctx, s32 a);
extern void fn_800AD830(void *ctx);
extern s32 fn_800AD780(void *ctx);
extern void fn_800AD9F4(void *ctx);
extern void fn_800ADBFC(void);

RepLoadState lbl_1_bss_47058;


// .text:0x0002852C size:0x60
void fn_1_2852C(void) {
    RepScene *scene = (RepScene *)currentDrawingItem;

    fn_800AD038(lbl_80366158.hi);
    scene->step = 0;
    scene->index = 0;
    currentDrawingItem->func = fn_1_284A8;
}

// .text:0x000284A8 size:0x84
void fn_1_284A8(void) {
    E(u16, INPUT_BUTTON) input = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
    RepScene *scene = (RepScene *)currentDrawingItem;

    if (input & (INPUT_BUTTON_LEFT | INPUT_BUTTON_RIGHT)) {
        scene->index ^= 1;
    } else if (input & INPUT_BUTTON_A) {
        scene->step = 0;
        currentDrawingItem->func = fn_1_282F4;
    } else if (input & INPUT_BUTTON_B) {
        scene->parent->state = 1;
        removeCurrentDrawingItem();
    }
}

// .text:0x000282F4 size:0x1B4
void fn_1_282F4(void) {
    RepLoadState *st = &lbl_1_bss_47058;
    RepScene *scene = (RepScene *)currentDrawingItem;
    s32 size;

    switch (scene->step) {
    case 0:
        st->ctx = _OSAllocFromHeap(0x20, 0x1C0);
        memset(st->ctx, 0, 0x1C0);
        st->bufSize = 0x400000;
        st->buf = _OSAllocFromHeap(0x20, 0x400000);
        fn_800ADC40(st->buf, st->bufSize);
        scene->step++;
        break;
    case 1:
        fn_800ADB04(movie1FileDescriptorDebug + scene->index * 16, st->ctx, 1, 0);
        scene->step++;
    case 2:
        if (fn_800ADAFC() != 0) {
            size = fn_800AD6BC(st->ctx);
            st->scratch = _OSAllocFromHeap(0x20, size);
            fn_800AD500(st->ctx, st->scratch);
            fn_800AD95C(st->ctx, 1);
            scene->step++;
        }
        break;
    case 3:
        if (AtBat_ButtonInput1._02 & INPUT_BUTTON_B) {
            fn_800AD830(st->ctx);
            scene->step++;
        }
    case 4:
        if (fn_800AD780(st->ctx) != 0) {
            fn_800AD9F4(st->ctx);
            fn_800ADBFC();
            fn_800AD038(lbl_80366158.hi);
            scene->step = 0;
            currentDrawingItem->func = fn_1_284A8;
        } else {
            fn_800AD070();
        }
        break;
    }
}
