#include "Unknown/File_0x800203e0.h"
#include "Unknown/File_0x800204cc.h"
#include "Unknown/File_0x800b0a14.h"

// 0x80020278-0x80021188: one translation unit by its .sdata and .data order
// (docs/splits.md, 2026-11-21): the former File_0x800203e0.c and
// File_0x800204cc.c plus fn_80020278, fn_80020388, fn_8002059C, fn_80020624,
// fn_800206FC and fn_80021064, which have no C yet.

extern SceneChangeState lbl_8037169C;

void fn_80020624(void);

void challenge_setTransitionScreenCharacterPortrait(u8 scene, s8 charID) {
    if (charID >= 0) {
        lbl_8037169C.transitionPortraitCharID = charID;
    }
    if (scene == 7) {
        lbl_8037169C.currentScene = 7;
        lbl_8037169C.sceneArg = 1;
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
    lbl_8037169C.sceneArg = 1;
}

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
