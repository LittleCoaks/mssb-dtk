#include "Unknown/File_0x8004a1bc.h"
#include "Unknown/File_0x8004a2bc.h"
#include "Unknown/File_0x80035838.h"
#include "Unknown/File_0x80048eb8.h"
#include "Unknown/File_0x80049220.h"
#include "Unknown/File_0x800494cc.h"
#include "Unknown/File_0x80049c80.h"

extern struct {
    /* 0x00 */ u8 _00[0x5D];
    /* 0x5D */ u8 unk5D;
} gameSetUpStep;

extern u8 skyPanoramaFileDescriptor[0x10];

void fn_80049D3C(void);

void gameSettingsRelated(void) {
    GameSettingsScreenState* settings = &gameSettings;
    int i;

    switch (settings->step) {
    case 0:
        stadiumSelect();
        break;
    case 1:
        if (gameSetUpStep.unk5D == 0) {
            settings->step++;
        }
        break;
    case 2:
        for (i = 0; i < 2; i++) {
            gameSettingsControllerInputs(i);
        }
        break;
    case 3:
        for (i = 0; i < 2; i++) {
            controlOptionsScreen(i);
        }
        break;
    case 4:
        if (diskReadRelated(skyPanoramaFileDescriptor, 6) != 0) {
            gameSettings.unk32 = 1;
            settings->step = 0;
        }
        break;
    case 5:
        startGameRelated();
        break;
    }
    fn_80049D3C();
}
