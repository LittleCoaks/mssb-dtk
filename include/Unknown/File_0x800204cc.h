#ifndef __UNKNOWN_FILE_0X800204CC_H_
#define __UNKNOWN_FILE_0X800204CC_H_

#include "mssbTypes.h"

typedef struct {
    /*0x00*/ u8 _00[0xC];
    /*0x0C*/ u16 sceneArg;
    /*0x0E*/ u8 _0E[2];
    /*0x10*/ u8 currentScene;
    /*0x11*/ u8 nextScene;
    /*0x12*/ u8 _12[2];
    /*0x14*/ E(s8, CHAR_ID) transitionPortraitCharID;
    /*0x15*/ u8 _15[0x1C - 0x15];
} SceneChangeState; // the object at lbl_8037169C

void changeScene(u8 scene, u16 arg1);

#endif // !__UNKNOWN_FILE_0X800204CC_H_
