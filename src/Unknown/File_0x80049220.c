#include "Unknown/File_0x80049220.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x8004a2bc.h"
#include "Unknown/File_0x80049d8c.h"
#include "Unknown/File_0x800625a4.h"
#include "Unknown/orderchange.h"
#include "musyx/musyx.h"

typedef struct MenuLabel {
    /* 0x0 */ u8 _0[8];
    /* 0x8 */ u16 label;
    /* 0xA */ u8 _A[6];
} MenuLabel;

extern u8 menuNumber[0x28];
extern MenuLabel lbl_800FEF70[];
extern u8 lbl_800EFBA4[];
extern u8 gameSetUpStep[];

void controlOptionsScreen(u8 port) {
    u8 found = FALSE;
    s8 idx;
    controllerInputStruct inputs = {0, 0, 0};
    u16 newInput;
    u16 processed;
    u8 *gs = (u8 *)&gameSettings;
    u8 *opt;
    s32 value;
    s32 limit;

    if (g_d_GameSettings.PlayerPorts[port] == Static_Stats_Tables.playerNumberByPort[port]) {
        found = TRUE;
        idx = port;
    }

    if (found) {
        if (gameSetUpStep[0x5D] == 0 && gameSetUpStep[0x5E] == 0) {
            inputs.currentHeldInput = Static_Stats_Tables.controllerInputs[idx].currentHeldInput;
            inputs.newInput = Static_Stats_Tables.controllerInputs[idx].newInput;
            inputs.processedInput = Static_Stats_Tables.controllerInputs[idx].processedInput;
            newInput = inputs.newInput;
            processed = inputs.processedInput;

            if ((processed & INPUT_BUTTON_UP) || (processed & INPUT_BUTTON_DOWN)) {
                opt = (u8 *)&gameSettings + (u8)idx;
                opt[0x69] = opt[0x65];
                value = (s8)opt[0x65];

                if (gs[0x36] == 0) {
                    limit = 5;
                } else if (g_d_GameSettings.GameModeSelected == 6) {
                    limit = 2;
                } else {
                    limit = 4;
                }

                if (processed & INPUT_BUTTON_UP) {
                    value--;
                    if (value < 0) {
                        if (gs[0x36] == 0) {
                            value = 4;
                        } else {
                            value = 3;
                        }
                    }
                    updateCharacterSelectProcessCode((u8)idx, 0x30);
                    sndFXRelated(0x8);
                } else if (processed & INPUT_BUTTON_DOWN) {
                    value++;
                    if (value == limit) {
                        value = 0;
                    }
                    updateCharacterSelectProcessCode((u8)idx, 0x30);
                    sndFXRelated(0x4);
                }

                opt[0x65] = value;
            } else if (processed & INPUT_BUTTON_LEFT) {
                gameSettingsLeftRightPressed(0, (u8)idx);
            } else if (processed & INPUT_BUTTON_RIGHT) {
                gameSettingsLeftRightPressed(1, (u8)idx);
            } else if ((newInput & INPUT_TRIGGER_L) || (newInput & INPUT_BUTTON_B)) {
                if (g_d_GameSettings._06 != 2 && gs[0x36] == 1) {
                    gs[0x36] = 0;
                    gameSettings.step = 2;

                    if (g_d_GameSettings.GameModeSelected == 5) {
                        menuNumber[0] = 0x14;
                        menuNumber[9] = menuNumber[8];
                        menuNumber[8] = lbl_800FEF70[0x14].label;
                    } else {
                        menuNumber[0] = 0x6;
                        menuNumber[9] = menuNumber[8];
                        menuNumber[8] = lbl_800FEF70[0x6].label;
                    }

                    updateCharacterSelectProcessCode(0, 0x2C);
                    if (newInput & INPUT_BUTTON_B) {
                        sndFXRelated(0x200);
                    } else {
                        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                    }
                }
            }
        }
    }
}
