#include "Unknown/File_0x8006295c.h"
#include "Unknown/File_0x80021410.h"
#include "Unknown/File_0x800b0a14.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/os.h"
#include "musyx/musyx.h"

void fn_8006295C(void) {
    if (audioFileDescriptors.enableMusic) {
        if (!menuMusic.playing2) {
            menuMusic.handle2 = sndFXStartEx(0, lbl_803CB889, 0x3F, SND_STUDIO_DEFAULT);
            menuMusic.playing2 = TRUE;
            menuMusic.stopping2 = FALSE;
        }
        if (menuMusic.stopping2) {
            sndFXKeyOff(menuMusic.handle2);
            menuMusic.handle2 = 0;
            menuMusic.stopping2 = FALSE;
            menuMusic.playing2 = FALSE;
            removeCurrentDrawingItem();
        }
    } else {
        sndFXKeyOff(menuMusic.handle2);
        menuMusic.handle2 = 0;
        menuMusic.stopping2 = FALSE;
        menuMusic.playing2 = FALSE;
        OSReport("sound end \n");
        removeCurrentDrawingItem();
    }
}

void initializeUnknown(void) {
    Static_Stats_Tables.unk48B3 = 0;
    menuMusic.handle = 0;
    menuMusic.stopping = 0;
    menuMusic.playing = 0;
}

void fn_80062A74(void) {
    menuMusic.stopping = 1;
    Static_Stats_Tables.unk48B3 = 1;
}

void startMenuMusic(void) {
    if (audioFileDescriptors.enableMusic) {
        if (!menuMusic.playing) {
            menuMusic.handle = sndFXStartEx(0x1E4, menuMusicStartVolume, 0x3F, SND_STUDIO_DEFAULT);
            menuMusic.playing = TRUE;
            menuMusic.stopping = FALSE;
            menuMusic.fade = 0;
            menuMusic.fadeStep = 0;
        }
        if (menuMusic.fade) {
            menuMusic.fadeStep++;
            if (menuMusic.fadeStep >= menuMusic.fade) {
                menuMusic.stopping = TRUE;
            } else {
                sndFXCtrl(menuMusic.handle, SND_MIDICTRL_VOLUME, menuMusicStartVolume - menuMusicStartVolume * menuMusic.fadeStep / menuMusic.fade);
            }
        }
        if (menuMusic.stopping) {
            sndFXKeyOff(menuMusic.handle);
            menuMusic.stopping = FALSE;
            menuMusic.handle = 0;
            menuMusic.playing = FALSE;
            removeCurrentDrawingItem();
        }
    } else {
        sndFXKeyOff(menuMusic.handle);
        menuMusic.handle = 0;
        menuMusic.stopping = FALSE;
        menuMusic.playing = FALSE;
        OSReport("sound end \n");
        removeCurrentDrawingItem();
    }
}
