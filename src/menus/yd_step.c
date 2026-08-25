#include "menus/yd_step.h"
#include "header_rep_data.h"
#include "Unknown/File_0x800b0a14.h"
#include "Dolphin/os.h"

extern menuControlStruct *menuControlVariables;
extern DrawingSceneStruct *currentDrawingItem;
extern void (*pCurrentScreenControlFunction[])(void);
extern void *lbl_800EF808[];
extern int fn_80021518(int arg0, void *arg1);

// .text:0x000010FC size:0x34 mapped:0x80640190
int fn_2_10FC(void) {
    fn_80021518(0x1F, lbl_800EF808[3]);
    return 0;
}

// .text:0x00001130 size:0x34 mapped:0x806401C4
void fn_2_1130(s16 state) {
    currentDrawingItem->currentDrawingItem->state = state;
    removeCurrentDrawingItem();
}

// .text:0x00001164 size:0x38 mapped:0x806401F8
void fn_2_1164(void) {
    currentDrawingItem->currentDrawingItem->state = 1;
    removeCurrentDrawingItem();
}

// .text:0x0000119C size:0x4 mapped:0x8064022C
void fn_2_119C(void) {
}

// .text:0x000011A0 size:0x38 mapped:0x80640234
void changeScreenVariables(u16 screen) {
    menuControlVariables->previousScreen = menuControlVariables->currentScreen;
    menuControlVariables->previousState = menuControlVariables->currentState;
    menuControlVariables->currentScreen = screen;
    menuControlVariables->currentState = 0;
}

// .text:0x000011D8 size:0x44 mapped:0x8064026C
void currentScreenFunctionChooser(void) {
    pCurrentScreenControlFunction[menuControlVariables->currentScreen]();
}

// .text:0x0000121C size:0x38 mapped:0x806402B0
void removedStep(void) {
    OSPanic("yd_step.c", 76, "Removed step was called.\n");
}
