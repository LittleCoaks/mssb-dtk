#ifndef __UNKNOWN_FILE_0X800B0A14_H_
#define __UNKNOWN_FILE_0X800B0A14_H_

#include "mssbTypes.h"

typedef struct DrawingSceneStruct {
    /* 0x00 */ void (*func)(void);
    /* 0x04 */ struct DrawingSceneStruct *prev;
    /* 0x08 */ struct DrawingSceneStruct *next;
    /* 0x0C */ struct DrawingSceneStruct *currentDrawingItem;
    /* 0x10 */ s16 state;
    /* 0x12 */ u16 priority;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ u64 unk_18;
    /* 0x20 */ u64 unk_20;
    /* 0x28 */ u64 unk_28;
    /* 0x30 */ u64 unk_30;
    /* 0x38 */ u64 unk_38;
} DrawingSceneStruct; // size 0x40

extern DrawingSceneStruct DSS_Head1[64];
extern DrawingSceneStruct lbl_80111300;
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
