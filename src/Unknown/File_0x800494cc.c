#include "Unknown/File_0x800494cc.h"
#include "Unknown/File_0x8004a2bc.h"
#include "Unknown/File_0x80049d8c.h"
#include "Unknown/File_0x800625a4.h"
#include "Unknown/File_0x80062a50.h"
#include "Unknown/File_0x80021410.h"
#include "Unknown/File_0x800204cc.h"
#include "Unknown/orderchange.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "musyx/musyx.h"

extern u8 gameSetUpStep[0x64];
extern u8 lbl_803C5EE0[0x18];
extern u32 lbl_803CBCF0;
extern u8 menuNumber[0x28];
extern u8 lbl_800EFBA4[];
extern u8 lbl_800FEF70[];

void gameSettingsControllerInputs(u8 port) {
    u8 *gs;
    controllerInputStruct *input;
    BOOL isMine = FALSE;
    s8 playerNumber;
    s8 cursor;
    s32 limit;
    u16 table;

    if (gameSetUpStep[0x5D] != 0 || gameSetUpStep[0x5E] != 0) {
        return;
    }

    playerNumber = Static_Stats_Tables.playerNumberByPort[port];
    Static_Stats_Tables.playerNumberByPort[port] = playerNumber;
    if (g_d_GameSettings.PlayerPorts[0] == playerNumber) {
        isMine = TRUE;
    }
    if (g_d_GameSettings.PlayerPorts[1] == playerNumber) {
        isMine = TRUE;
    }
    if (!isMine) {
        return;
    }

    input = &Static_Stats_Tables.controllerInputs[port];
    gs = (u8 *)&gameSettings;
    if (input->processedInput & (INPUT_BUTTON_UP | INPUT_BUTTON_DOWN)) {
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            return;
        }

        gs[0x69] = gs[0x65];
        cursor = (s8)gs[0x65];
        if (gs[0x36] == 0) {
            limit = 5;
        } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
            limit = 2;
        } else {
            limit = 4;
        }

        if (input->processedInput & INPUT_BUTTON_UP) {
            cursor--;
            if (cursor < 0) {
                cursor = (gs[0x36] != 0) ? 3 : 4;
            }
            updateCharacterSelectProcessCode(0, 0x30);
            sndFXRelated(0x8);
        } else {
            cursor++;
            if (cursor == limit) {
                cursor = 0;
            }
            updateCharacterSelectProcessCode(0, 0x30);
            sndFXRelated(0x4);
        }
        gs[0x65] = (u8)cursor;
    } else if (input->processedInput & INPUT_BUTTON_LEFT) {
        gameSettingsLeftRightPressed(0, 0);
    } else if (input->processedInput & INPUT_BUTTON_RIGHT) {
        gameSettingsLeftRightPressed(1, 0);
    } else if (input->newInput & INPUT_TRIGGER_R) {
        if (g_d_GameSettings.highLevelMenuScene == HIGH_LEVEL_MENU_SCENE_IN_GAME) {
            return;
        }

        gs[0x36] = 1;
        gameSettings.step = 3;
        gs[0x69] = gs[0x65];
        gs[0x65] = 0;
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            menuNumber[0] = 0x15;
            table = *(u16 *)&lbl_800FEF70[0x158];
        } else {
            menuNumber[0] = 0x7;
            table = *(u16 *)&lbl_800FEF70[0x78];
        }
        menuNumber[9] = menuNumber[8];
        menuNumber[8] = (u8)table;

        updateCharacterSelectProcessCode(0, 0x2B);
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (input->newInput & INPUT_BUTTON_A) {
        if (gs[0x65] != 0) {
            return;
        }

        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            updateCharacterSelectProcessCode(0, 0x31);
            gs[0x35] = 0;
        } else {
            ((u8 *)&Static_Stats_Tables)[0x48B0] = 1;
            lbl_803C5EE0[0x15] = 1;
            fn_80062A74();
            maybeLoadsGameSoundFiles();
            gs[0x35] = 1;
        }
        changeScene(0xF, 6);
        gameSettings.step = 5;
        gs[0x34] = 1;
        sndFXRelated(0x100);
    } else if (input->newInput & INPUT_BUTTON_B) {
        if (gs[0x65] != 0) {
            gs[0x69] = gs[0x65];
            gs[0x65] = 0;
            updateCharacterSelectProcessCode(0, 0x30);
        } else {
            lbl_803CBCF0 = 0;
            updateCharacterSelectProcessCode(0, 0x2A);
            gameSettings.step = 5;
            gs[0x34] = 0;
            gs[0x35] = 1;
        }
        sndFXRelated(0x200);
    }
}
