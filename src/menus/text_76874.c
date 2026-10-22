#define SQRT2_LINKAGE static
#include "menus/text_76874.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x80062674.h"
#include "Unknown/orderchange.h"
#include "text/text.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x800625a4.h"
#include "game/UnknownHomes_Game.h"
#include "game/challenge/challenge_state.h"
#include "Unknown/mb_subfunc.h"
#include "menus/text_00110.h"
#include "musyx/musyx.h"

extern u8 gameSetUpStep[0x64];
extern u8 lbl_2_bss_F468[0xC4C];
extern Text00110Ctl *menuControlVariables;
extern int menuCursors[0x16];
extern u8 superstarUnlocked[];
extern u8 challengeCaptainCharIDArray[];
extern u8 lbl_800EFBA4[];
void gfx_cssCharStatBars_and_sthgElse(MenuScene *scene, s32 port);
void fn_2_76650(MenuScene *scene, u8 team, u32 mask);
void teamSelectionSetChemStars(MenuScene *scene, u8 team);

static inline BOOL stepIsClear(u8 step) {
    return step == 0 ? TRUE : FALSE;
}

static inline s32 firstRosterSlot(s32 port, s32 position) {
    s32 i;
    for (i = 0; i < PLAYERS_PER_TEAM; i++) {
        if ((s8)cursorPositions.roster.positionSwapMapping[port][i] == position) break;
    }
    return i;
}

static inline UIRecord *channelSceneRecord(MenuScene *scene, s32 port, s32 index) {
    s32 handle = scene->firstHandle;
    handle += port;
    handle += index;
    return (UIRecord *)graphicsRelatedArray[handle].object;
}

static inline UIRecord *rosterSceneRecord(MenuScene *scene, s32 port, s32 position, s32 index) {
    s32 handle = scene->firstHandle + position;
    handle += port * PLAYERS_PER_TEAM;
    handle += index;
    return (UIRecord *)graphicsRelatedArray[handle].object;
}

static inline s8 captainRosterPosition(s32 port) {
    s32 i;
    s8 position;
    for (i = 0; i < PLAYERS_PER_TEAM; i++) {
        if (Static_Stats_Tables.captainSelectedID[port] == cursorPositions.roster.rosterCharID[port][i]) {
            position = cursorPositions.roster.positionSwapMapping[port][i];
            break;
        }
    }
    return position;
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
    u8 first;
    BOOL second;

    cursor = lbl_2_bss_F468[port + 0x61];
    word = (s8)*(s32 *)&lbl_2_bss_F468[port * 4];
    if ((s8)cursor != CHAR_ID_NONE) {
        for (k = 0; k < PLAYERS_PER_TEAM; k++) {
            if ((s8)cursorPositions.roster.positionSwapMapping[port][k] == (s8)cursor) {
                slot = k;
            }
        }
    }


    if (stepIsClear(gameSetUpStep[port + 0xD])) {
        channelSceneRecord(scene, port, 0xA)->frame = 0xF0000;
        channelSceneRecord(scene, port, 0xA)->playMode = UI_PLAY_BACKWARD;
        channelSceneRecord(scene, port, 0x1E)->playMode = UI_PLAY_BACKWARD;
        channelSceneRecord(scene, port, 0x93)->elementIndex = 9;
        channelSceneRecord(scene, port, 0x89)->frame = 0;
        channelSceneRecord(scene, port, 0x89)->playMode = UI_PLAY_FORWARD;
        channelSceneRecord(scene, port, 0x8D)->frame = 0x140000;
        channelSceneRecord(scene, port, 0x8D)->playMode = UI_PLAY_BACKWARD;
        channelSceneRecord(scene, port, 0x6A)->playMode = UI_PLAY_FORWARD;
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            channelSceneRecord(scene, port, 0x8F)->elementIndex = 7;
        }
        if ((s8)cursor != CHAR_ID_NONE && (s8)cursor != word) {
            rosterSceneRecord(scene, port, (s8)cursor, 0x46)->playMode = UI_PLAY_BACKWARD;
            rosterChar = cursorPositions.roster.rosterCharID[port][(s8)slot];
            if (rosterChar != CHAR_ID_NONE && rosterChar != NUM_CHOOSABLE_CHARACTERS) {
                rosterSceneRecord(scene, port, (s8)cursor, 0x34)->frame = 0xA0000;
                rosterSceneRecord(scene, port, (s8)cursor, 0x34)->playMode = UI_PLAY_FORWARD;
            }
        }
        makeCursorUnmovable(port);
        gameSetUpStep[port + 0xD] = 1;
    }

    if (gameSetUpStep[port + 0xD] == 1) {
        expected = 2;
        first = maybeCheckAndResetGrapicsElement(scene, port + 0x89, 5) != 0;
        second = maybeCheckAndResetGrapicsElement(scene, port + 0x6A, 0xA) != 0;
        count = first + second;
        if ((s8)cursor != CHAR_ID_NONE && lbl_2_bss_F468[0x56] == 0 && (s8)cursor != word) {
            rosterChar = cursorPositions.roster.rosterCharID[port][(s8)slot];
            if (rosterChar != CHAR_ID_NONE && rosterChar != NUM_CHOOSABLE_CHARACTERS) {
                expected = 3;
                count += maybeCheckAndResetGrapicsElement(scene, (s8)cursor + port * PLAYERS_PER_TEAM + 0x34, 0x14) != 0;
            }
        }
        if (count == expected) {
            lbl_2_bss_F468[port + 0x61] = 0xFF;
            makeCursorMovable(port);
            gameSetUpStep[port + 0xD] = 2;
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
void cssAction_0x1c(MenuScene *scene, int port) {
    s32 cursor;
    s32 selected;
    s8 slot;
    s8 selectedSlot;
    s32 i;
    E(s8, CHAR_ID) character;
    s32 ready;
    s32 expected;

    if (lbl_2_bss_F468[port + 0x5F] == 0) {
        cursor = lbl_2_bss_F468[port + 0x61];
        for (i = 0; i < PLAYERS_PER_TEAM; i++) {
            if ((s8)cursorPositions.roster.positionSwapMapping[port][i] == (s8)cursor) slot = i;
        }
        if (stepIsClear(gameSetUpStep[port + 0xD])) {
            if ((s8)cursor != CHAR_ID_NONE) {
                rosterSceneRecord(scene, port, (s8)cursor, 0x46)->frame = 0;
                rosterSceneRecord(scene, port, (s8)cursor, 0x46)->playMode = UI_PLAY_FORWARD;
                character = cursorPositions.roster.rosterCharID[port][slot];
                if (character != CHAR_ID_NONE && character != NUM_CHOOSABLE_CHARACTERS) {
                    rosterSceneRecord(scene, port, (s8)cursor, 0x34)->frame = 20 << 16;
                    rosterSceneRecord(scene, port, (s8)cursor, 0x34)->playMode = UI_PLAY_BACKWARD;
                }
            }
            if (lbl_2_bss_F468[port + 0x37]) {
                channelSceneRecord(scene, port, 0x93)->elementIndex = 10;
                channelSceneRecord(scene, port, 0x93)->playMode = UI_PLAY_FORWARD;
            }
            makeCursorUnmovable(port);
            gameSetUpStep[port + 0xD] = 1;
        }
        if (gameSetUpStep[port + 0xD] == 1) {
            ready = 0;
            expected = 0;
            character = cursorPositions.roster.rosterCharID[port][slot];
            if (character != CHAR_ID_NONE && character != NUM_CHOOSABLE_CHARACTERS && (s8)cursor != CHAR_ID_NONE) {
                expected = 1;
                ready = maybeCheckAndResetGrapicsElement(scene, (s8)cursor + port * PLAYERS_PER_TEAM + 0x34, 10) != 0;
            }
            if (ready == expected) {
                lbl_2_bss_F468[port + 0x5F] = 1;
                makeCursorMovable(port);
                gameSetUpStep[port + 0xD] = 2;
            }
        }
    } else {
        selected = (s8)((s32 *)lbl_2_bss_F468)[port];
        cursor = lbl_2_bss_F468[port + 0x61];
        for (i = 0; i < PLAYERS_PER_TEAM; i++) {
            if ((s8)cursorPositions.roster.positionSwapMapping[port][i] == (s8)cursor) slot = i;
            if ((s8)cursorPositions.roster.positionSwapMapping[port][i] == selected) selectedSlot = i;
        }
        if (stepIsClear(gameSetUpStep[port + 0xD])) {
            if ((s8)cursor != CHAR_ID_NONE) {
                character = cursorPositions.roster.rosterCharID[port][slot];
                if (character != CHAR_ID_NONE && character != NUM_CHOOSABLE_CHARACTERS) {
                    rosterSceneRecord(scene, port, (s8)cursor, 0x58)->frame = character << 16;
                    rosterSceneRecord(scene, port, (s8)cursor, 0x34)->flags |= UI_FLAG_VISIBLE;
                    rosterSceneRecord(scene, port, (s8)cursor, 0x34)->frame = 10 << 16;
                    rosterSceneRecord(scene, port, (s8)cursor, 0x34)->playMode = UI_PLAY_FORWARD;
                } else {
                    rosterSceneRecord(scene, port, (s8)cursor, 0x34)->flags &= ~UI_FLAG_VISIBLE;
                }
            }
            character = cursorPositions.roster.rosterCharID[port][selectedSlot];
            if (character != CHAR_ID_NONE && character != NUM_CHOOSABLE_CHARACTERS) {
                rosterSceneRecord(scene, port, selected, 0x58)->frame = character << 16;
                rosterSceneRecord(scene, port, selected, 0x34)->frame = 10 << 16;
                rosterSceneRecord(scene, port, selected, 0x34)->playMode = UI_PLAY_STOP;
                rosterSceneRecord(scene, port, selected, 0x34)->flags |= UI_FLAG_VISIBLE;
            } else {
                rosterSceneRecord(scene, port, selected, 0x34)->flags &= ~UI_FLAG_VISIBLE;
            }
            if ((s8)cursor != selected && (s8)cursor != CHAR_ID_NONE) {
                rosterSceneRecord(scene, port, (s8)cursor, 0x46)->frame = 15 << 16;
                rosterSceneRecord(scene, port, (s8)cursor, 0x46)->playMode = UI_PLAY_BACKWARD;
            }
            if (lbl_2_bss_F468[port + 0x37]) {
                channelSceneRecord(scene, port, 0x93)->elementIndex = 9;
                channelSceneRecord(scene, port, 0x93)->frame = 10 << 16;
                channelSceneRecord(scene, port, 0x93)->playMode = UI_PLAY_STOP;
            }
            gfx_cssCharStatBars_and_sthgElse(scene, port);
            makeCursorUnmovable(port);
            gameSetUpStep[port + 0xD] = 1;
        }
        if (gameSetUpStep[port + 0xD] == 1) {
            ready = 0;
            expected = 0;
            character = cursorPositions.roster.rosterCharID[port][slot];
            if (character != CHAR_ID_NONE && character != NUM_CHOOSABLE_CHARACTERS && (s8)cursor != CHAR_ID_NONE && (s8)cursor != selected) {
                expected = 1;
                ready = maybeCheckAndResetGrapicsElement(scene, (s8)cursor + port * PLAYERS_PER_TEAM + 0x34, 20) != 0;
            }
            if (ready == expected) {
                lbl_2_bss_F468[port + 0x5F] = 0;
                lbl_2_bss_F468[port + 0x61] = CHAR_ID_NONE;
                makeCursorMovable(port);
                gameSetUpStep[port + 0xD] = 2;
            }
        }
    }
}

// .text:0x0007805C size:0x310 mapped:0x806B70F0
void cssAction_0x1d(MenuScene *scene, int port) {
    s32 cursor;
    s32 slot;
    s32 k;
    s32 wasChecked;
    s32 done;
    E(s8, CHAR_ID) rosterChar;

    cursor = lbl_2_bss_F468[port + 0x61];
    for (k = 0; k < PLAYERS_PER_TEAM; k++) {
        if ((s8)cursorPositions.roster.positionSwapMapping[port][k] == (s8)cursor) {
            slot = k;
        }
    }

    if (stepIsClear(gameSetUpStep[port + 0xD])) {
        if ((s8)cursor != *(s32 *)&lbl_2_bss_F468[port * 4]) {
            rosterSceneRecord(scene, port, (s8)cursor, 0x46)->playMode = UI_PLAY_BACKWARD;
            rosterChar = cursorPositions.roster.rosterCharID[port][(s8)slot];
            if (rosterChar != CHAR_ID_NONE && rosterChar != NUM_CHOOSABLE_CHARACTERS) {
                rosterSceneRecord(scene, port, (s8)cursor, 0x34)->playMode = UI_PLAY_FORWARD;
            }
        }
        if (lbl_2_bss_F468[port + 0x37] != 0) {
            channelSceneRecord(scene, port, 0x93)->elementIndex = 9;
            channelSceneRecord(scene, port, 0x93)->frame = 0xA0000;
            channelSceneRecord(scene, port, 0x93)->playMode = UI_PLAY_STOP;
        }
        makeCursorUnmovable(port);
        gameSetUpStep[port + 0xD] = 1;
    }

    if (gameSetUpStep[port + 0xD] == 1) {
        wasChecked = 0;
        done = 0;
        if ((s8)cursor != *(s32 *)&lbl_2_bss_F468[port * 4]) {
            rosterChar = cursorPositions.roster.rosterCharID[port][(s8)slot];
            if (rosterChar != CHAR_ID_NONE && rosterChar != NUM_CHOOSABLE_CHARACTERS) {
                wasChecked = 1;
                done = maybeCheckAndResetGrapicsElement(scene, (s8)cursor + port * PLAYERS_PER_TEAM + 0x34, 0x14) != 0;
            }
        }
        if (done == wasChecked) {
            lbl_2_bss_F468[port + 0x5F] = 0;
            lbl_2_bss_F468[port + 0x61] = 0xFF;
            makeCursorMovable(port);
            gameSetUpStep[port + 0xD] = 2;
        }
    }
}

// .text:0x00078034 size:0x28 mapped:0x806B70C8
void fn_2_78034(int unused, int channel) {
    if (stepIsClear(gameSetUpStep[channel + 0xD])) {
        gameSetUpStep[channel + 0xD] = 1;
    }
}

// .text:0x000776A0 size:0x994 mapped:0x806B6734
void removeAllPlayersFromTeam(MenuScene *scene, int controller) {
    s32 port = gameSetUpStep[controller + 0x59];
    u16 input = Static_Stats_Tables.controllerInputs[controller].newInput;
    s8 captainPosition;
    s32 i;
    s32 selected;
    s32 slot;
    E(s8, CHAR_ID) character;
    s32 ready;

    if (gameSetUpStep[0] == 2 && lbl_2_bss_F468[port + 0x45] == 0) {
        if (lbl_2_bss_F468[port + 0x41] == 0) {
            if (((s32 *)lbl_2_bss_F468)[port + 2] != ((s32 *)lbl_2_bss_F468)[port]) {
                gfx_cssCharStatBars_and_sthgElse(scene, port);
            }
        } else if (((s32 *)lbl_2_bss_F468)[port + 8] != menuCursors[port + 8]) {
            gfx_cssCharStatBars_and_sthgElse(scene, port);
        }
    }
    if ((input & INPUT_BUTTON_Y) && menuControlVariables->currentScreen == 10 &&
        lbl_2_bss_F468[port + 0x52] != 0 && g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE &&
        lbl_2_bss_F468[port + 0x54] == 0) {
        if (gameSetUpStep[port + 0x55] != 0) {
            makeCursorMovable(port);
            gameSetUpStep[port + 0xD] = 2;
        } else {
            if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && port != 0) {
                gameSetUpStep[port + 0x5D] = 0;
            }
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        }
        captainPosition = captainRosterPosition(port);
        for (i = 0; i < PLAYERS_PER_TEAM; i++) {
            if (i != captainPosition) {
                rosterSceneRecord(scene, port, i, 0x34)->playMode = UI_PLAY_BACKWARD;
            }
        }
        rosterSceneRecord(scene, port, captainPosition, 0x34)->playMode = UI_PLAY_FORWARD;
        teamSelectionSetChemStars(scene, port);
        channelSceneRecord(scene, port, 0x91)->playMode = UI_PLAY_FORWARD;
        selected = ((s32 *)lbl_2_bss_F468)[port + 2];
        if (selected == 9) {
            channelSceneRecord(scene, port, 0x93)->playMode = UI_PLAY_BACKWARD;
            channelSceneRecord(scene, controller, 0x95)->frame = 10 << 16;
            channelSceneRecord(scene, port, 0x95)->playMode = UI_PLAY_BACKWARD;
        } else if (selected == 10) {
            channelSceneRecord(scene, port, 0x93)->playMode = UI_PLAY_BACKWARD;
        } else {
            rosterSceneRecord(scene, port, selected, 0x46)->frame = 15 << 16;
            rosterSceneRecord(scene, port, selected, 0x46)->playMode = UI_PLAY_BACKWARD;
            channelSceneRecord(scene, port, 0x93)->playMode = UI_PLAY_BACKWARD;
        }
        for (i = 0; i < PLAYERS_PER_TEAM; i++) {
            channelSceneRecord(scene, port, 0x97)->flags &= ~UI_FLAG_VISIBLE;
            channelSceneRecord(scene, port, 0xAC)->flags &= ~UI_FLAG_VISIBLE;
            rosterSceneRecord(scene, port, i, 0x22)->flags &= ~UI_FLAG_VISIBLE;
        }
        lbl_2_bss_F468[port + 0x54] = 1;
    }
    if (gameSetUpStep[0] == 2 && lbl_2_bss_F468[port + 0x45] == 0 && lbl_2_bss_F468[port + 0x50] != 0) {
        selected = ((s32 *)lbl_2_bss_F468)[port];
        slot = firstRosterSlot(port, selected);
        character = cursorPositions.roster.rosterCharID[port][slot];
        rosterSceneRecord(scene, port, selected, 0x58)->frame = character << 16;
        gfx_cssCharStatBars_and_sthgElse(scene, port);
        lbl_2_bss_F468[port + 0x50] = 0;
    }
    if (lbl_2_bss_F468[port + 0x54] != 0) {
        captainPosition = captainRosterPosition(port);
        ready = maybeCheckAndResetGrapicsElement(scene, captainPosition + port * PLAYERS_PER_TEAM + 0x34, 20) != 0;
        if (ready == 1) {
            lbl_2_bss_F468[port + 0x54] = 0;
            lbl_2_bss_F468[port + 0x52] = 0;
        }
    }
    if (lbl_2_bss_F468[port + 0x4B] != 0) {
        if (lbl_2_bss_F468[port + 0x45] != 0) {
            switch (lbl_2_bss_F468[port + 0x47]) {
            case 0:
                fn_2_76DF0(scene, port);
                break;
            case 1:
                fn_2_76874(scene, port);
                break;
            }
        } else {
            if (lbl_2_bss_F468[port + 0x47] == 0) {
                if ((channelSceneRecord(scene, port, 0xB4)->frame >> 16) > 5) {
                    channelSceneRecord(scene, port, 0xB4)->frame = 5 << 16;
                }
                channelSceneRecord(scene, port, 0xB4)->playMode = UI_PLAY_BACKWARD;
                channelSceneRecord(scene, port, 0xB6)->playMode = UI_PLAY_BACKWARD;
                channelSceneRecord(scene, port, 0xC6)->playMode = UI_PLAY_BACKWARD;
                ready = maybeCheckAndResetGrapicsElement(scene, port + 0xB4, 0) != 0;
                ready += maybeCheckAndResetGrapicsElement(scene, port + 0xB6, 0) != 0;
                ready += maybeCheckAndResetGrapicsElement(scene, port + 0xC6, 0) != 0;
                if (ready == 3) lbl_2_bss_F468[port + 0x4B] = 0;
            } else {
                if ((channelSceneRecord(scene, port, 0xB4)->frame >> 16) > 5) {
                    channelSceneRecord(scene, port, 0xB4)->frame = 5 << 16;
                }
                channelSceneRecord(scene, port, 0xB4)->playMode = UI_PLAY_BACKWARD;
                channelSceneRecord(scene, port, 0xE2)->playMode = UI_PLAY_BACKWARD;
                ready = maybeCheckAndResetGrapicsElement(scene, port + 0xE2, 0) != 0;
                if (ready == 1) lbl_2_bss_F468[port + 0x4B] = 0;
            }
            lbl_2_bss_F468[port + 0x49] = 0;
        }
    }
}

// .text:0x00076DF0 size:0x8B0 mapped:0x806B5E84
void fn_2_76DF0(MenuScene *scene, u8 port) {
    E(s32, CHAR_ID) character;
    u32 abilities;
    u8 pushPull;
    u8 highLow;
    E(u8, BATTING_HAND) stance;
    StatTable *stats;

    if (lbl_2_bss_F468[port + 0x49] == 0) {
        if (menuControlVariables->currentScreen == 9) {
            if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
                character = mapCaptainCursorPositionToCharID[menuCursors[port + 4]];
            } else {
                character = challengeCaptainCharIDArray[superstarUnlocked[0xF4] * 6 + menuCursors[port + 4]];
            }
        } else {
            if (lbl_2_bss_F468[port + 0x41] == 0) {
                s32 slot = firstRosterSlot(port, ((s32 *)lbl_2_bss_F468)[port]);
                character = cursorPositions.roster.rosterCharID[(s32)port][slot];
            } else {
                character = menuCursors[port + 8];
                if (character == CHAR_ID_NONE) {
                    lbl_2_bss_F468[port + 0x49] = 0;
                    return;
                }
            }
            lbl_2_bss_F468[port + 0x4D] = character;
        }
        stats = &Static_Stats_Tables.characterStats[(s8)(character / 9)][(s8)(character % 9)].stats;
        abilities = stats->FieldingStats;
        pushPull = stats->HitTrajectoryPushPull;
        highLow = stats->HitTrajectoryHighLow;
        stance = stats->BattingStance;
        channelSceneRecord(scene, port, 0xB4)->playMode = UI_PLAY_FORWARD;
        channelSceneRecord(scene, port, 0xCA)->frame = character << 16;
        channelSceneRecord(scene, port, 0xCC)->frame = fn_80064918(character) << 16;
        channelSceneRecord(scene, port, 0xC6)->frame = 0;
        channelSceneRecord(scene, port, 0xDE)->frame = character << 16;
        fn_2_76650(scene, port, abilities);
        channelSceneRecord(scene, port, 0xD2)->frame = 0;
        channelSceneRecord(scene, port, 0xD4)->frame = 1 << 16;
        channelSceneRecord(scene, port, 0xD6)->frame = 2 << 16;
        channelSceneRecord(scene, port, 0xD8)->frame = 3 << 16;
        channelSceneRecord(scene, port, 0xDA)->frame = 4 << 16;
        channelSceneRecord(scene, port, 0xDC)->frame = 5 << 16;
        channelSceneRecord(scene, port, 0xBA)->frame = 0;
        channelSceneRecord(scene, port, 0xBC)->frame = 0;
        channelSceneRecord(scene, port, 0xBE)->frame = 0;
        channelSceneRecord(scene, port, 0xC0)->frame = 0;
        channelSceneRecord(scene, port, 0xC2)->frame = 0;
        channelSceneRecord(scene, port, 0xC4)->frame = 0;
        switch (pushPull) {
        case 0:
            channelSceneRecord(scene, port, 0xBA)->playMode = UI_PLAY_FORWARD;
            channelSceneRecord(scene, port, 0xBC)->playMode = UI_PLAY_STOP;
            channelSceneRecord(scene, port, 0xBE)->playMode = UI_PLAY_STOP;
            break;
        case 1:
            if (stance == BATTING_HAND_RIGHT) {
                channelSceneRecord(scene, port, 0xBA)->playMode = UI_PLAY_STOP;
                channelSceneRecord(scene, port, 0xBC)->playMode = UI_PLAY_FORWARD;
                channelSceneRecord(scene, port, 0xBE)->playMode = UI_PLAY_STOP;
            } else {
                channelSceneRecord(scene, port, 0xBA)->playMode = UI_PLAY_STOP;
                channelSceneRecord(scene, port, 0xBC)->playMode = UI_PLAY_STOP;
                channelSceneRecord(scene, port, 0xBE)->playMode = UI_PLAY_FORWARD;
            }
            break;
        case 2:
            if (stance == BATTING_HAND_RIGHT) {
                channelSceneRecord(scene, port, 0xBA)->playMode = UI_PLAY_STOP;
                channelSceneRecord(scene, port, 0xBC)->playMode = UI_PLAY_STOP;
                channelSceneRecord(scene, port, 0xBE)->playMode = UI_PLAY_FORWARD;
            } else {
                channelSceneRecord(scene, port, 0xBA)->playMode = UI_PLAY_STOP;
                channelSceneRecord(scene, port, 0xBC)->playMode = UI_PLAY_FORWARD;
                channelSceneRecord(scene, port, 0xBE)->playMode = UI_PLAY_STOP;
            }
            break;
        }
        switch (highLow) {
        case 0:
            channelSceneRecord(scene, port, 0xC0)->playMode = UI_PLAY_FORWARD;
            channelSceneRecord(scene, port, 0xC2)->playMode = UI_PLAY_STOP;
            channelSceneRecord(scene, port, 0xC4)->playMode = UI_PLAY_STOP;
            break;
        case 1:
            channelSceneRecord(scene, port, 0xC0)->playMode = UI_PLAY_STOP;
            channelSceneRecord(scene, port, 0xC2)->playMode = UI_PLAY_FORWARD;
            channelSceneRecord(scene, port, 0xC4)->playMode = UI_PLAY_STOP;
            break;
        case 2:
            channelSceneRecord(scene, port, 0xC0)->playMode = UI_PLAY_STOP;
            channelSceneRecord(scene, port, 0xC2)->playMode = UI_PLAY_STOP;
            channelSceneRecord(scene, port, 0xC4)->playMode = UI_PLAY_FORWARD;
            break;
        }
        channelSceneRecord(scene, port, 0xE0)->flags |= UI_FLAG_VISIBLE;
        channelSceneRecord(scene, port, 0xE0)->playMode = UI_PLAY_FORWARD;
        channelSceneRecord(scene, port, 0xB6)->playMode = UI_PLAY_FORWARD;
        channelSceneRecord(scene, port, 0xC6)->frame = 0;
        channelSceneRecord(scene, port, 0xC6)->playMode = UI_PLAY_FORWARD;
        channelSceneRecord(scene, port, 0xEA)->flags &= ~UI_FLAG_VISIBLE;
        channelSceneRecord(scene, port, 0xEA)->playMode = UI_PLAY_STOP;
        channelSceneRecord(scene, port, 0xE2)->playMode = UI_PLAY_BACKWARD;
        lbl_2_bss_F468[port + 0x49] = 1;
    }
    if (menuControlVariables->currentScreen == 10 && lbl_2_bss_F468[port + 0x41] != 0 &&
        lbl_2_bss_F468[port + 0x4D] != menuCursors[port + 8]) {
        gfx_cssCharStatBars_and_sthgElse(scene, port);
        lbl_2_bss_F468[port + 0x49] = 0;
    }
}

// .text:0x00076874 size:0x57C mapped:0x806B5908
void fn_2_76874(MenuScene *scene, u8 port) {
    E(s32, CHAR_ID) character;
    u8 star;
    u8 swing;
    u8 pitch;
    u8 swingIcon;
    u8 pitchIcon;
    s32 starIndex;
    s8 group;
    s8 member;

    if (lbl_2_bss_F468[port + 0x49] == 0) {
        channelSceneRecord(scene, port, 0xE0)->flags &= ~UI_FLAG_VISIBLE;
        channelSceneRecord(scene, port, 0xE0)->playMode = UI_PLAY_STOP;
        channelSceneRecord(scene, port, 0xB6)->playMode = UI_PLAY_BACKWARD;
        channelSceneRecord(scene, port, 0xC6)->playMode = UI_PLAY_BACKWARD;
        if (menuControlVariables->currentScreen == 9) {
            if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
                character = mapCaptainCursorPositionToCharID[menuCursors[port + 4]];
            } else {
                character = challengeCaptainCharIDArray[superstarUnlocked[0xF4] * 6 + menuCursors[port + 4]];
            }
        } else {
            if (lbl_2_bss_F468[port + 0x41] == 0) {
                s32 slot = firstRosterSlot(port, ((s32 *)lbl_2_bss_F468)[port]);
                character = cursorPositions.roster.rosterCharID[(s32)port][slot];
            } else {
                character = menuCursors[port + 8];
                if (character == CHAR_ID_NONE) {
                    lbl_2_bss_F468[port + 0x49] = 0;
                    return;
                }
            }
        }
        lbl_2_bss_F468[port + 0x4D] = character;
        group = character / 9;
        member = character % 9;
        star = Static_Stats_Tables.characterStats[group][member].stats.CaptainStarHitPitch;
        if (star == 0) {
            swing = Static_Stats_Tables.characterStats[group][member].stats.NonCaptainStarSwing + 11;
            pitch = Static_Stats_Tables.characterStats[group][member].stats.NonCaptainStarPitch + 11;
        } else if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            swing = star - 1;
            pitch = swing;
        } else {
            starIndex = translateStarPitchHitIndex(star - 1);
            if ((s8)starIndex != -1 && ((s8 *)&g_Challenge)[0x15F1 + (s8)starIndex] == 0 && menuControlVariables->currentScreen == 9) {
                swing = Static_Stats_Tables.characterStats[group][member].stats.NonCaptainStarSwing + 11;
                pitch = Static_Stats_Tables.characterStats[group][member].stats.NonCaptainStarPitch + 11;
            } else if ((s8)starIndex != -1 && g_Challenge._43C2[(s8)starIndex] == 0 && menuControlVariables->currentScreen == 10) {
                swing = Static_Stats_Tables.characterStats[group][member].stats.NonCaptainStarSwing + 11;
                pitch = Static_Stats_Tables.characterStats[group][member].stats.NonCaptainStarPitch + 11;
            } else {
                swing = star - 1;
                pitch = star - 1;
            }
        }
        swingIcon = translateStarSwing(swing);
        pitchIcon = translateStarPitch(pitch);
        channelSceneRecord(scene, port, 0xE6)->elementIndex = swingIcon;
        channelSceneRecord(scene, port, 0xE6)->frame = 0;
        channelSceneRecord(scene, port, 0xE6)->playMode = UI_PLAY_FORWARD;
        channelSceneRecord(scene, port, 0xE8)->elementIndex = pitchIcon;
        channelSceneRecord(scene, port, 0xE8)->frame = 0;
        channelSceneRecord(scene, port, 0xE8)->playMode = UI_PLAY_FORWARD;
        channelSceneRecord(scene, port, 0xEA)->flags |= UI_FLAG_VISIBLE;
        channelSceneRecord(scene, port, 0xEA)->playMode = UI_PLAY_FORWARD;
        channelSceneRecord(scene, port, 0xE2)->playMode = UI_PLAY_FORWARD;
        lbl_2_bss_F468[port + 0x49] = 1;
    }
    if (menuControlVariables->currentScreen == 10 && lbl_2_bss_F468[port + 0x41] != 0 &&
        lbl_2_bss_F468[port + 0x4D] != menuCursors[port + 8]) {
        gfx_cssCharStatBars_and_sthgElse(scene, port);
        lbl_2_bss_F468[port + 0x49] = 0;
    }
}
