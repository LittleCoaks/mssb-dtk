#include "Unknown/File_0x8004ac00.h"

extern struct {
    u8 _00[0x28];
    u8 _28;
} lbl_80366158;

extern s32 lbl_803CBCF8;
extern s32 lbl_803CB850;
extern s32 lbl_803CBCFC;
extern s32 setHandOnFireAsPitcher;

void fn_8004C19C(fn_80024C6C_s* obj, int arg1, int arg2, f32 frame);

void newPitcherEnteringGame(fn_80024C6C_s* obj, int arg1, int arg2, f32 frame) {
    if (lbl_80366158._28 == 1) {
        return;
    }
    if (obj->_252 == 0) {
        if (frame >= (f32)lbl_803CBCF8 && frame <= (f32)lbl_803CB850) {
            setHandOnFireAsPitcher = TRUE;
            if (frame == 0.5) {
                lbl_803CBCFC = TRUE;
            } else {
                lbl_803CBCFC = FALSE;
            }
        }
    } else if (obj->_252 == 18) {
        fn_8004C19C(obj, arg1, arg2, frame);
    }
}
