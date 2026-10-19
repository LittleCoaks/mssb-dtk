#include "Unknown/File_0x8004ca6c.h"
#include "Unknown/File_0x8004cc18.h"
#include "musyx/musyx.h"
#include "game/UnknownHomes_Game.h"

extern Unk803C5F74 lbl_803C5F74;
extern u8 lbl_800EFBA4[0x10];
extern s32 lbl_803CB874;
extern s32 lbl_803CB878;

int exitMenu(u16 input) {
    if (lbl_803C5F74.state == 4) {
        if (lbl_803C5F74.unk02 == 0) {
            return 3;
        }
        return 4;
    }
    if (lbl_803C5F74.state == 2) {
        int quiet;

        if (input != 0) {
            lbl_803CB874 = lbl_803CB878;
        }
        if (lbl_803CB874 > 0) {
            lbl_803CB874--;
        }
        quiet = lbl_803CB874 == 0;
        if (quiet) {
            input |= INPUT_BUTTON_A;
        }
        if (input & INPUT_BUTTON_A) {
            if (!quiet) {
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, SND_STUDIO_DEFAULT);
            }
            if (lbl_803C5F74.unk02 == 0) {
                return 1;
            }
            return 2;
        }
        if (input & INPUT_BUTTON_B) {
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, SND_STUDIO_DEFAULT);
            if (lbl_803C5F74.unk02 == 0) {
                lbl_803C5F74.unk02 = 1;
            } else {
                return 2;
            }
        } else if ((input & INPUT_BUTTON_LEFT) && lbl_803C5F74.unk02 == 1) {
            lbl_803C5F74.unk02 = 0;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
        } else if (input & INPUT_BUTTON_RIGHT) {
            if (lbl_803C5F74.unk02 == 0) {
                lbl_803C5F74.unk02 = 1;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, SND_STUDIO_DEFAULT);
            }
        }
    }
    return 0;
}
