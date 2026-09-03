#ifndef __MENUS_YD_STEP_H_
#define __MENUS_YD_STEP_H_

#include "mssbTypes.h"
#include "Unknown/File_0x800b0a14.h"

typedef struct menuControlStruct {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 currentScreen;
    /* 0x04 */ u16 currentState;
    /* 0x06 */ u16 previousScreen;
    /* 0x08 */ u16 previousState;
} menuControlStruct; // size 0xA

int fn_2_10FC(void);
void fn_2_1130(s16 state);
void fn_2_1164(void);
void fn_2_119C(void);
void changeScreenVariables(u16 screen);

/* stadium-select cursor -> STADIUM_ID (menus .data 0x130C) */
extern u8 cursorToStadIDMapping[0x288];
void currentScreenFunctionChooser(void);
void removedStep(void);

#endif // !__MENUS_YD_STEP_H_
