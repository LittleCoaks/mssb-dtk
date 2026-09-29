#include "Unknown/File_0x8003a538.h"

extern void (*lbl_803CBCA8)(void);
extern s32 lbl_803CBCB0;

s32 fn_8003A538(void) {
    return lbl_803CBCB0;
}

void fn_8003A540(s32 value) {
    lbl_803CBCB0 = value;
}

void updateFunctionPtr(void (*func)(void)) {
    lbl_803CBCA8 = func;
}
