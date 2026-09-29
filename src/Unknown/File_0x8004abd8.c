#include "Unknown/File_0x8004abd8.h"

extern BOOL changesToZeroOnBlackTransitionScreen;
extern s32 lbl_803CBCFC;
extern BOOL setHandOnFireAsPitcher;

void Set_803cb848(BOOL value) {
    changesToZeroOnBlackTransitionScreen = value;
}

s32 fn_8004ABE0(void) {
    return lbl_803CBCFC;
}

BOOL marioHandOnFire_endFireAnimation(BOOL clear) {
    BOOL wasOnFire = setHandOnFireAsPitcher;
    if (clear) {
        setHandOnFireAsPitcher = FALSE;
    }
    return wasOnFire;
}
