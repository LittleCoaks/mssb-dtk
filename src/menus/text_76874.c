#include "menus/text_76874.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x80062674.h"
#include "Unknown/orderchange.h"
#include "text/text.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x800625a4.h"

extern u8 gameSetUpStep[0x64];
extern u8 lbl_2_bss_F468[0xC4C];

static UIRecord *sceneRecord(MenuScene *scene, s32 index) {
    return (UIRecord *)graphicsRelatedArray[scene->firstHandle + index].object;
}

// .text:0x00078AC0 size:0x4B8 mapped:0x806B7B54
void cssAction_0x1b(MenuScene *scene, int port) {
    s32 cursor;
    s32 word;
    s32 slot;
    s32 k;
    s32 count;
    s32 expected;
    E(s8, CHAR_ID) rosterChar;
    BOOL first;
    BOOL second;
    u8 *flag;
    BOOL flagClear;

    cursor = (s8)lbl_2_bss_F468[port + 0x61];
    word = (s8)*(s32 *)&lbl_2_bss_F468[port * 4];
    if (cursor != CHAR_ID_NONE) {
        for (k = 0; k < 9; k++) {
            if ((s8)cursorPositions.roster.positionSwapMapping[port][k] == cursor) {
                slot = k;
            }
        }
    }

    flag = gameSetUpStep + port;

    flagClear = flag[0xD] == 0;
    if (flagClear) {
        sceneRecord(scene, port + 0xA)->frame = 0xF0000;
        sceneRecord(scene, port + 0xA)->playMode = UI_PLAY_BACKWARD;
        sceneRecord(scene, port + 0x1E)->playMode = UI_PLAY_BACKWARD;
        sceneRecord(scene, port + 0x93)->elementIndex = 9;
        sceneRecord(scene, port + 0x89)->frame = 0;
        sceneRecord(scene, port + 0x89)->playMode = UI_PLAY_FORWARD;
        sceneRecord(scene, port + 0x8D)->frame = 0x140000;
        sceneRecord(scene, port + 0x8D)->playMode = UI_PLAY_BACKWARD;
        sceneRecord(scene, port + 0x6A)->playMode = UI_PLAY_FORWARD;
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            sceneRecord(scene, port + 0x8F)->elementIndex = 7;
        }
        if (cursor != CHAR_ID_NONE && cursor != word) {
            sceneRecord(scene, cursor + port * 9 + 0x46)->playMode = UI_PLAY_BACKWARD;
            rosterChar = cursorPositions.roster.rosterCharID[port][slot];
            if (rosterChar != CHAR_ID_NONE && rosterChar != NUM_CHOOSABLE_CHARACTERS) {
                sceneRecord(scene, cursor + port * 9 + 0x34)->frame = 0xA0000;
                sceneRecord(scene, cursor + port * 9 + 0x34)->playMode = UI_PLAY_FORWARD;
            }
        }
        makeCursorUnmovable(port);
        flag[0xD] = 1;
    }

    if (flag[0xD] == 1) {
        expected = 2;
        first = maybeCheckAndResetGrapicsElement(scene, port + 0x89, 5) != 0;
        second = maybeCheckAndResetGrapicsElement(scene, port + 0x6A, 0xA) != 0;
        count = first + second;
        if (cursor != CHAR_ID_NONE && lbl_2_bss_F468[0x56] == 0 && cursor != word) {
            rosterChar = cursorPositions.roster.rosterCharID[port][slot];
            if (rosterChar != CHAR_ID_NONE && rosterChar != NUM_CHOOSABLE_CHARACTERS) {
                expected = 3;
                count += maybeCheckAndResetGrapicsElement(scene, cursor + port * 9 + 0x34, 0x14) != 0;
            }
        }
        if (count == expected) {
            lbl_2_bss_F468[port + 0x61] = 0xFF;
            makeCursorMovable(port);
            flag[0xD] = 2;
            if (lbl_2_bss_F468[port + 0x65] != 0) {
                if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                    updateCharacterSelectProcessCode(0, 0x13);
                    updateCharacterSelectProcessCode(1, 0x13);
                } else if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
                    updateCharacterSelectProcessCode(port, 0x11);
                } else {
                    updateCharacterSelectProcessCode(port, 0x11);
                }
                lbl_2_bss_F468[port + 0x65] = 0;
            } else if (lbl_2_bss_F468[0x56] != 0) {
                updateCharacterSelectProcessCode(port, 0x0B);
            }
        }
    }
}

// .text:0x0007836C size:0x754 mapped:0x806B7400
void cssAction_0x1c(void) {
    return;
}

// .text:0x0007805C size:0x310 mapped:0x806B70F0
void cssAction_0x1d(MenuScene *scene, int port) {
    s32 cursor;
    s32 slot;
    s32 k;
    s32 wasChecked;
    s32 done;
    u8 *flag;
    E(s8, CHAR_ID) rosterChar;

    cursor = (s8)lbl_2_bss_F468[port + 0x61];
    for (k = 0; k < 9; k++) {
        if ((s8)cursorPositions.roster.positionSwapMapping[port][k] == cursor) {
            slot = k;
        }
    }

    flag = gameSetUpStep + port;
    if (flag[0xD] == 0) {
        if (cursor != *(s32 *)&lbl_2_bss_F468[port * 4]) {
            sceneRecord(scene, cursor + port * 9 + 0x46)->playMode = UI_PLAY_BACKWARD;
            rosterChar = cursorPositions.roster.rosterCharID[port][slot];
            if (rosterChar != CHAR_ID_NONE && rosterChar != NUM_CHOOSABLE_CHARACTERS) {
                sceneRecord(scene, cursor + port * 9 + 0x34)->playMode = UI_PLAY_FORWARD;
            }
        }
        if (lbl_2_bss_F468[port + 0x37] != 0) {
            sceneRecord(scene, port + 0x93)->elementIndex = 9;
            sceneRecord(scene, port + 0x93)->frame = 0xA0000;
            sceneRecord(scene, port + 0x93)->playMode = UI_PLAY_STOP;
        }
        makeCursorUnmovable(port);
        flag[0xD] = 1;
    }

    if (flag[0xD] == 1) {
        wasChecked = 0;
        done = 0;
        if (cursor != *(s32 *)&lbl_2_bss_F468[port * 4]) {
            rosterChar = cursorPositions.roster.rosterCharID[port][slot];
            if (rosterChar != CHAR_ID_NONE && rosterChar != NUM_CHOOSABLE_CHARACTERS) {
                wasChecked = 1;
                done = maybeCheckAndResetGrapicsElement(scene, cursor + port * 9 + 0x34, 0x14) != 0;
            }
        }
        if (done == wasChecked) {
            lbl_2_bss_F468[port + 0x5F] = 0;
            lbl_2_bss_F468[port + 0x61] = 0xFF;
            makeCursorMovable(port);
            flag[0xD] = 2;
        }
    }
}

// .text:0x00078034 size:0x28 mapped:0x806B70C8
void fn_2_78034(int unused, int channel) {
    u8 *flag = gameSetUpStep + channel + 0xD;

    if (*flag == 0) {
        *flag = 1;
    }
}

// .text:0x000776A0 size:0x994 mapped:0x806B6734
void removeAllPlayersFromTeam(void) {
    return;
}

// .text:0x00076DF0 size:0x8B0 mapped:0x806B5E84
void fn_2_76DF0(void) {
    return;
}

// .text:0x00076874 size:0x57C mapped:0x806B5908
void fn_2_76874(void) {
    return;
}
