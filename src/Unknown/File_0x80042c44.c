#include "Unknown/File_0x80042c44.h"
#include "game/UnknownHomes_Game.h"
#include "musyx/musyx.h"

extern u8 lbl_800EFBA4[0x10];

void sndFXRelated(u16 input) {
    switch (input) {
    case INPUT_BUTTON_A:
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, SND_STUDIO_DEFAULT);
        break;
    case INPUT_BUTTON_B:
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, SND_STUDIO_DEFAULT);
        break;
    case INPUT_BUTTON_LEFT:
    case INPUT_BUTTON_RIGHT:
    case INPUT_BUTTON_DOWN:
    case INPUT_BUTTON_UP:
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
        break;
    case INPUT_BUTTON_LEFT | INPUT_BUTTON_RIGHT:
    case INPUT_TRIGGER_R:
    case INPUT_TRIGGER_L:
    case INPUT_BUTTON_X:
    case INPUT_BUTTON_Y:
        break;
    }
}
