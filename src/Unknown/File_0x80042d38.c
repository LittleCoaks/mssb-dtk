#include "Unknown/File_0x80042d38.h"
#include "Unknown/File_0x80034e20.h"
#include "text/text_channel.h"
#include "menus/yd_step.h"

extern menuControlStruct* menuControlVariables;

#define SCENE_RECORD(scene, i) ((UIRecord*)graphicsRelatedArray[(scene)->firstHandle + (i)].object)

void fn_80042D38(u16 screen) {
    menuControlVariables->previousScreen = menuControlVariables->currentScreen;
    menuControlVariables->previousState = menuControlVariables->currentState;
    menuControlVariables->currentScreen = screen;
    menuControlVariables->currentState = 0;
}

BOOL fn_80042D68(MenuScene* scene, int handle, int frame) {
    UIRecord* record = SCENE_RECORD(scene, handle);

    if ((s32)(record->frame >> 16) >= frame) {
        record->playMode = UI_PLAY_STOP;
        return TRUE;
    }
    return FALSE;
}

BOOL maybeCheckAndResetGrapicsElement(MenuScene* scene, int handle, int frame) {
    UIRecord* record = SCENE_RECORD(scene, handle);

    if ((s32)(record->frame >> 16) == frame) {
        record->playMode = UI_PLAY_STOP;
        return TRUE;
    }
    return FALSE;
}
