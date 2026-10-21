#include "menus/options_screen.h"
#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_menus_options_screen
#include "header_rep_data.h"
#include "menus/debug_menu_text.h"
#include "static/UnknownHomes_Static.h"
#include "game/UnknownHomes_Game.h"
#include "musyx/musyx.h"
#include "PowerPC_EABI_Support/Runtime/__mem.h"
#include "Unknown/File_0x800204cc.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x80021410.h"
#include "Unknown/File_0x800625a4.h"
#include "C3/geoPalette/DisplayObject.h"

/* Working copy of the options being edited (sound mode, music, rumble). */
typedef struct {
    /* 0x00 */ u16 screen;
    /* 0x02 */ s16 cursor;
    /* 0x04 */ s16 prevCursor;
    /* 0x06 */ s8 music;
    /* 0x07 */ s8 soundMode;
    /* 0x08 */ s8 rumble;
    /* 0x09 */ u8 prevSoundMode;
    /* 0x0A */ s8 _0A;
    /* 0x0B */ E(u8, BOOL) editing;
    /* 0x0C */ u8 _0C;
    /* 0x0D */ E(u8, BOOL) musicWasOn;
    /* 0x0E */ u8 _0E;
    /* 0x0F */ E(u8, BOOL) exitRequested;
} OptionsState; // size: 0x10

enum {
    OPTIONS_SCREEN_ENTER = 0,
    OPTIONS_SCREEN_SETUP = 1,
    OPTIONS_SCREEN_WAIT_SETUP = 2,
    OPTIONS_SCREEN_INPUT = 3,
    OPTIONS_SCREEN_EXIT = 4,
    OPTIONS_SCREEN_SAVE = 5,
    OPTIONS_SCREEN_SAVE_WAIT = 6,
};

enum {
    OPTIONS_ITEM_MUSIC = 0,
    OPTIONS_ITEM_SOUND_MODE = 1,
    OPTIONS_ITEM_RUMBLE = 2,
};

DebugMenuText lbl_2_data_2798 = {
    { "BAT FIRST", "BAT LAST" },
    "FL",
    "PC",
    { "RR", "RL", "LR", "LL" },
    { "OFF", "ON" },
    { "SELECT DEBUG MENU", "HIDE CHARA SET", "STAR PLAYER SET", "KOOPA STA FLAG SET", "CHALLE LEVEL FREE SET" },
    { "1P >", "COM1>", "2P >", "COM2>", "3P >", "COM3>", "4P >", "COM4>" },
    { 0x0000FF0F, 0x0000880F, 0x00000FFF, 0x0000088F, 0x0000F0FF, 0x0000808F, 0x0000F00F, 0x0000800F },
    { 0, 4, 10, 6, 2, 9, 1, 5, 11, 17, 3, 19 },
    { 0, 2, 6, 8, 4, 10, 1, 3, 7, 5, 9, 11 },
    { 0, 0, 6, 2, 8, 4, 10, 5, 11, 3, 9, 1, 7, 0, 0, 0 },
};

/* Unreferenced debug labels for the three options and their values. */
char lbl_2_data_2A5C[8][0x20] = {
    "MUSIC", "SOUND", "VIBRATION", "MONAURAL", "STEREO", "SURROUND", "ON", "OFF",
};

extern OptionsState lbl_2_bss_1033C;
extern u8 lbl_80366158[0x30];
extern u8 lbl_800EFBA4[0x10];
extern u8 cardCheck[0x5C];
extern u8 lbl_8037169C[0x1C];
extern u8 gameSetUpStep[0x64];
extern u8 menuNumber[0x28];
extern int menuCursors[0x16];

void fn_80021204(void);
void fn_80021228(int mode);
int fn_8003AE70(int index);
void fn_80062A74(void);
void initializeUnknown(void);
void startMenuMusic(void);
void fn_800A97EC(int arg0, int arg1, int arg2);
void fn_8003BF54(int, int, int, int, int, int, int, int, int);
void fn_2_96D20(void);
void changeScreenVariables(u16 screen);

#define OPTIONS lbl_2_bss_1033C

static inline BOOL optionsDiffer(void) {
    BOOL changed = FALSE;

    if (audioFileDescriptors.enableMusic != fn_8003AE70(0) || audioFileDescriptors._397 != fn_8003AE70(1) ||
        lbl_80366158[0x1F] != fn_8003AE70(2)) {
        changed = TRUE;
    }
    return changed;
}

// .text:0x000194BC size:0x2C mapped:0x80658550
void fn_2_194BC(ActorObjectEntry *entry) {
    if (entry->drawArgs[0] != 0) {
        setLITLightPtr((void *)entry->drawArgs[0]);
    }
}

// .text:0x000194E8 size:0x38 mapped:0x8065857C
void fn_2_194E8(void) {
    fn_80021204();
    inningSetting._pad_23[2] = lbl_80366158[0x1F];
}

// .text:0x00019520 size:0x34 mapped:0x806585B4
void fn_2_19520(void) {
    OPTIONS.music = audioFileDescriptors.enableMusic;
    OPTIONS.rumble = lbl_80366158[0x1F];
    OPTIONS.soundMode = audioFileDescriptors.soundMode;
}

// .text:0x00019554 size:0x84 mapped:0x806585E8
BOOL fn_2_19554(void) {
    s8 changed = FALSE;

    if (audioFileDescriptors.enableMusic != fn_8003AE70(0) || audioFileDescriptors._397 != fn_8003AE70(1) ||
        lbl_80366158[0x1F] != fn_8003AE70(2)) {
        changed = TRUE;
    }
    return changed;
}

// .text:0x000195D8 size:0x4 mapped:0x8065866C
void fn_2_195D8(void) {
}

// .text:0x000195DC size:0x19C mapped:0x80658670
void fn_2_195DC(void) {
    switch (OPTIONS.cursor) {
    case OPTIONS_ITEM_MUSIC:
        if (OPTIONS.music != 0 && audioFileDescriptors.enableMusic == 0) {
            initializeUnknown();
            insertGraphicDrawingFunction(startMenuMusic, 0x1000);
        } else if (OPTIONS.music == 0 && audioFileDescriptors.enableMusic != 0) {
            fn_80062A74();
        }
        audioFileDescriptors.enableMusic = OPTIONS.music;
        OPTIONS.musicWasOn = OPTIONS.music;
        break;
    case OPTIONS_ITEM_SOUND_MODE:
        if (OPTIONS.soundMode != audioFileDescriptors.soundMode) {
            fn_80062A74();
            if (OPTIONS.soundMode == 1) {
                audioFileDescriptors.soundMode = 1;
            } else if (OPTIONS.soundMode == 0) {
                audioFileDescriptors.soundMode = 0;
            } else {
                audioFileDescriptors.soundMode = 2;
            }
            fn_80021228(audioFileDescriptors.soundMode);
            insertGraphicDrawingFunction(startMenuMusic, 0x1000);
            audioFileDescriptors.soundMode = OPTIONS.soundMode;
        }
        break;
    case OPTIONS_ITEM_RUMBLE:
        if (OPTIONS.rumble != 0) {
            lbl_80366158[0x1F] = 1;
            fn_800A97EC(0, 0x32, 1);
        } else {
            lbl_80366158[0x1F] = 0;
        }
        break;
    }
    OPTIONS.editing = FALSE;
}

// .text:0x00019778 size:0x34 mapped:0x8065880C
void fn_2_19778(void) {
    OPTIONS.music = audioFileDescriptors.enableMusic;
    OPTIONS.rumble = lbl_80366158[0x1F];
    OPTIONS.soundMode = audioFileDescriptors.soundMode;
}

// .text:0x000197AC size:0x558 mapped:0x80658840
void fn_2_197AC(u8 port) {
    u8 changed = FALSE;
    controllerInputStruct input;

    if (Static_Stats_Tables.playerNumberByPort[port] == -1) {
        return;
    }
    memset(&input, 0, sizeof(input));
    input.currentHeldInput = Static_Stats_Tables.controllerInputs[port].currentHeldInput;
    input.newInput = Static_Stats_Tables.controllerInputs[port].newInput;
    input.processedInput = Static_Stats_Tables.controllerInputs[port].processedInput;

    if (input.newInput & INPUT_BUTTON_A) {
        if (OPTIONS.editing != 0) {
            fn_2_195DC();
        } else {
            OPTIONS.editing = TRUE;
        }
        updateCharacterSelectProcessCode(0, 0x5C);
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
    } else if (input.newInput & INPUT_BUTTON_B) {
        if (OPTIONS.editing != 0) {
            OPTIONS.editing = FALSE;
            updateCharacterSelectProcessCode(0, 0x5C);
            fn_2_19520();
        } else if (cardCheck[0x47] != 0) {
            fn_2_194E8();
            updateCharacterSelectProcessCode(0, 0x5A);
            OPTIONS.screen = OPTIONS_SCREEN_EXIT;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        } else {
            if (optionsDiffer()) {
                OPTIONS.screen = OPTIONS_SCREEN_SAVE;
            } else {
                updateCharacterSelectProcessCode(0, 0x5A);
                OPTIONS.screen = OPTIONS_SCREEN_EXIT;
            }
        }
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
    } else if (input.processedInput & INPUT_BUTTON_UP) {
        if (OPTIONS.editing == 0) {
            OPTIONS.prevCursor = OPTIONS.cursor;
            OPTIONS.cursor--;
            if (OPTIONS.cursor < 0) {
                OPTIONS.cursor = 2;
            } else if (OPTIONS.music == 0 && OPTIONS.cursor == OPTIONS_ITEM_SOUND_MODE) {
                OPTIONS.cursor--;
            }
            updateCharacterSelectProcessCode(0, 0x5B);
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
    } else if (input.processedInput & INPUT_BUTTON_DOWN) {
        if (OPTIONS.editing == 0) {
            OPTIONS.prevCursor = OPTIONS.cursor;
            OPTIONS.cursor = OPTIONS.cursor + 1;
            if (OPTIONS.cursor == 3) {
                OPTIONS.cursor = 0;
            } else if (OPTIONS.music == 0 && OPTIONS.cursor == OPTIONS_ITEM_SOUND_MODE) {
                OPTIONS.cursor = OPTIONS.cursor + 1;
            }
            updateCharacterSelectProcessCode(0, 0x5B);
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
    } else if (input.newInput & INPUT_BUTTON_LEFT) {
        if (OPTIONS.editing != 0) {
            switch (OPTIONS.cursor) {
            case OPTIONS_ITEM_MUSIC: {
                changed = OPTIONS.music == 0;
                OPTIONS.music = 1;
                OPTIONS._0A = 0;
                break;
            }
            case OPTIONS_ITEM_SOUND_MODE: {
                s8 old = OPTIONS.soundMode;
                OPTIONS.prevSoundMode = old;
                if (old > 0) {
                    OPTIONS.soundMode = old - 1;
                    changed = TRUE;
                }
                break;
            }
            case OPTIONS_ITEM_RUMBLE: {
                changed = OPTIONS.rumble == 0;
                OPTIONS.rumble = 1;
                break;
            }
            }
            if (changed) {
                updateCharacterSelectProcessCode(0, 0x5B);
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
    } else if (input.newInput & INPUT_BUTTON_RIGHT) {
        if (OPTIONS.editing != 0) {
            switch (OPTIONS.cursor) {
            case OPTIONS_ITEM_MUSIC: {
                u8 old = OPTIONS.music;
                OPTIONS.music = 0;
                if (OPTIONS.music == 0) {
                    OPTIONS._0A = 0;
                } else {
                    OPTIONS._0A = 1;
                }
                if (old != OPTIONS.music) {
                    changed = TRUE;
                }
                break;
            }
            case OPTIONS_ITEM_SOUND_MODE: {
                OPTIONS.prevSoundMode = OPTIONS.soundMode;
                OPTIONS.soundMode = OPTIONS.soundMode + 1;
                if (OPTIONS.soundMode == 3) {
                    OPTIONS.soundMode = 2;
                }
                if (OPTIONS.prevSoundMode != OPTIONS.soundMode) {
                    changed = TRUE;
                }
                break;
            }
            case OPTIONS_ITEM_RUMBLE: {
                u8 old = OPTIONS.rumble;
                OPTIONS.rumble = 0;
                if (old != OPTIONS.rumble) {
                    changed = TRUE;
                }
                break;
            }
            }
            if (changed) {
                updateCharacterSelectProcessCode(0, 0x5B);
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
    }
}

// .text:0x00019D04 size:0x228 mapped:0x80658D98
void optionsScreen(void) {
    switch (OPTIONS.screen) {
    case OPTIONS_SCREEN_ENTER:
        if (lbl_8037169C[0x13] == 0) {
            break;
        }
        OPTIONS.screen = OPTIONS_SCREEN_SETUP;
    case OPTIONS_SCREEN_SETUP:
        changeScene(1, 6);
        menuCursors[2] = 0;
        menuCursors[3] = 0;
        fn_2_96D20();
        updateCharacterSelectProcessCode(0, 0x59);
        OPTIONS.prevCursor = 0;
        OPTIONS.cursor = 0;
        OPTIONS.editing = FALSE;
        fn_2_19778();
        OPTIONS.musicWasOn = OPTIONS.music != 0;
        OPTIONS.screen = OPTIONS_SCREEN_WAIT_SETUP;
        break;
    case OPTIONS_SCREEN_WAIT_SETUP:
        if (gameSetUpStep[0x5D] == 0) {
            OPTIONS.screen = OPTIONS_SCREEN_INPUT;
        }
        break;
    case OPTIONS_SCREEN_INPUT:
        fn_2_197AC(Static_Stats_Tables.playerNumberByPort[0]);
        break;
    case OPTIONS_SCREEN_SAVE:
        fn_2_194E8();
        fn_8003BF54(0, 0, 0, 0, 1, 4, 1, 0, 4);
        currentDrawingItem->state = 0;
        OPTIONS.screen = OPTIONS_SCREEN_SAVE_WAIT;
        break;
    case OPTIONS_SCREEN_SAVE_WAIT: {
        s16 result = currentDrawingItem->state;

        if (result != 0) {
            switch (result) {
            case 1:
            case 0xB:
                updateCharacterSelectProcessCode(0, 0x5A);
                OPTIONS.screen = OPTIONS_SCREEN_EXIT;
                break;
            default:
                OPTIONS.screen = OPTIONS_SCREEN_SAVE;
                break;
            }
        }
        break;
    }
    case OPTIONS_SCREEN_EXIT:
        if (gameSetUpStep[0x55] == 0) {
            OPTIONS.exitRequested = TRUE;
            OPTIONS.screen = OPTIONS_SCREEN_ENTER;
            menuNumber[0x26] = 1;
            changeScreenVariables(5);
        }
        break;
    }
}
