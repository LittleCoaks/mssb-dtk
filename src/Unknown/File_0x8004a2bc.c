#include "Unknown/File_0x8004a2bc.h"
#include "Unknown/File_0x8004a1bc.h"
#include "Unknown/File_0x800b0a14.h"
#include "menus/yd_step.h"

extern menuControlStruct* menuControlVariables;

void gameSettingsScreen(void) {
    switch (menuControlVariables->currentState) {
    case 0:
        insertGraphicDrawingFunction(gameSettingsRelated, 0x2000);
        gameSettings.unk2C = 0;
        menuControlVariables->currentState++;
        break;
    case 1:
        break;
    }
}
