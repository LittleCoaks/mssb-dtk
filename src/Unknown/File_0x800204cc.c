#include "Unknown/File_0x800204cc.h"
#include "Unknown/File_0x800b0a14.h"

extern struct {
    /*0x00*/ u8 _00[0xC];
    /*0x0C*/ u16 sceneArg;
    /*0x0E*/ u8 _0E[2];
    /*0x10*/ u8 currentScene;
    /*0x11*/ u8 nextScene;
    /*0x12*/ u8 _12[0x1C - 0x12];
} lbl_8037169C;

void fn_80020624(void);

void changeScene(u8 scene, u16 arg1) {
    if (scene == 7) {
        lbl_8037169C.sceneArg = arg1;
        lbl_8037169C.currentScene = 7;
        insertGraphicDrawingFunction(fn_80020624, 2);
        return;
    }
    if (scene == 1 || scene == 6 || scene == 13) {
        u8 current = lbl_8037169C.currentScene;

        if (current >= 4 && current <= 6) {
            scene = 6;
        } else if (current >= 10 && current <= 12) {
            scene = 10;
        } else if (current >= 13 && current <= 15) {
            scene = 13;
        } else {
            scene = 1;
        }
    }
    lbl_8037169C.nextScene = scene;
    lbl_8037169C.sceneArg = arg1;
}
