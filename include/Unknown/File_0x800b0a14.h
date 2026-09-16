#ifndef __UNKNOWN_FILE_0X800B0A14_H_
#define __UNKNOWN_FILE_0X800B0A14_H_

#include "mssbTypes.h"

/* A per-frame drawing-script node. +0x10.. is scratch the node's func owns;
 * the uses seen so far:
 *  - 2D menu scenes (addGraphicsElementToScene): +0x14 u16 firstHandle,
 *    +0x16 u16 handleCount -- the node's records are
 *    graphicsRelatedArray[firstHandle + handle].object.
 *  - the audio file loader task (audioFileLoaderTask, 0x80021758):
 *    +0x14 push callback, +0x18 u8 state, +0x19 u8 audio file index.
 *  - relLoaderNode (0x80111300): +0x10 loaderFinished, +0x18 u16 loader state.
 *  - some debug.rel scenes keep a f32 at +0x14. */
typedef struct DrawingSceneStruct {
    /* 0x00 */ void (*func)(void);
    /* 0x04 */ struct DrawingSceneStruct *prev;
    /* 0x08 */ struct DrawingSceneStruct *next;
    /* 0x0C */ struct DrawingSceneStruct *currentDrawingItem;
    /* 0x10 */ s16 state;
    /* 0x12 */ u16 priority;
    /* 0x14 */ f32 unk_14;      // menu scenes: u16 firstHandle, u16 handleCount
    /* 0x18 */ u64 unk_18;
    /* 0x20 */ u64 unk_20;
    /* 0x28 */ u64 unk_28;
    /* 0x30 */ u64 unk_30;
    /* 0x38 */ u64 unk_38;
} DrawingSceneStruct; // size 0x40

extern DrawingSceneStruct DSS_Head1[64];
extern DrawingSceneStruct relLoaderNode;    // 0x80111300: the root node the REL loader state machine runs on
extern DrawingSceneStruct *currentDrawingItem;
extern u16 DrawingStructArray_Count1;
extern u16 DrawingStructArray_Count2;
extern volatile u16 DrawingStructArray_SearchIndex;

void removeCurrentDrawingItem(void);
DrawingSceneStruct *insertGraphicDrawingFunction(void (*func)(void), u32 priority);
void resetAllDrawingStructs_tonop(void);
void resetAllDrawingStructs(void);
void setDrawingListHeadFunctions(void (*func)(void));
void nop_function(void);

#endif // !__UNKNOWN_FILE_0X800B0A14_H_
