#ifndef __MENUS_YD_STEP_H_
#define __MENUS_YD_STEP_H_

#include "mssbTypes.h"

typedef struct menuControlStruct {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 currentScreen;
    /* 0x04 */ u16 currentState;
    /* 0x06 */ u16 previousScreen;
    /* 0x08 */ u16 previousState;
} menuControlStruct; // size 0xA

typedef struct DrawingSceneStruct {
    /* 0x00 */ void *aFunctionPointer;
    /* 0x04 */ u8 link[0x8];
    /* 0x0C */ struct DrawingSceneStruct *currentDrawingItem;
    /* 0x10 */ s16 state;
    /* 0x12 */ u16 priority;
    /* 0x14 */ u8 unk_14[0x2C];
} DrawingSceneStruct; // size 0x40

int fn_2_10FC(void);
void fn_2_1130(s16 state);
void fn_2_1164(void);
void fn_2_119C(void);
void changeScreenVariables(u16 screen);
void currentScreenFunctionChooser(void);
void removedStep(void);

#endif // !__MENUS_YD_STEP_H_
