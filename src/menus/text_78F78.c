#define SQRT2_LINKAGE static
#include "menus/text_78F78.h"
#include "menus/text_744C8.h"
#include "menus/text_0323C.h"
#include "menus/text_00110.h"
#include "game/UnknownHomes_Game.h"
#include "Unknown/File_0x800625a4.h"
#include "static/UnknownHomes_Static.h"
#include "text/text.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x80062674.h"
#include "Unknown/orderchange.h"

extern u8 gameSetUpStep[];
extern u8 lbl_2_bss_F468[];
extern Text00110Ctl *menuControlVariables;

/* Per-team state word in lbl_2_bss_F468 (indexed by team). */
#define TEAM_STATE(team) (((s32 *)lbl_2_bss_F468)[(team)])

/* Record for scene handle k: graphicsRelatedArray[scene->firstHandle + k]. */
#define SCENE_RECORD(scene, k) ((UIRecord *)graphicsRelatedArray[(scene)->firstHandle + (k)].object)

static inline UIRecord *channelRecord(MenuScene *scene, s32 index, s32 offset) {
    s32 handle = scene->firstHandle;
    handle += index;
    handle += offset;
    return (UIRecord *)graphicsRelatedArray[handle].object;
}

static inline UIRecord *rosterRecord(MenuScene *scene, s32 index, s32 position, s32 offset) {
    s32 handle = scene->firstHandle + position;
    handle += index * PLAYERS_PER_TEAM;
    handle += offset;
    return (UIRecord *)graphicsRelatedArray[handle].object;
}

static inline s32 findRosterSlot(s32 index, s32 position) {
    s32 slot;
    s32 i;

    for (i = 0; i < PLAYERS_PER_TEAM; i++) {
        if ((s8)cursorPositions.roster.positionSwapMapping[index][i] == position) {
            slot = i;
            break;
        }
    }
    return slot;
}

static inline s32 rosterHandle(s32 index, s32 position, s32 offset) {
    s32 handle = position;
    handle += index * PLAYERS_PER_TEAM;
    handle += offset;
    return handle;
}

static inline BOOL isStepClear(u8 step) {
    return step == 0 ? TRUE : FALSE;
}

static inline BOOL isStepActive(u8 step) {
    return step == 1 ? TRUE : FALSE;
}

static inline BOOL resetChemistryStars(MenuScene *scene, s32 index) {
    s32 ready = 0;
    s32 expected = 0;
    s32 starCount = Static_Stats_Tables.startingChemStars[index];
    s32 i;

    for (i = 0; i < starCount; i++) {
        s32 handle = i;
        handle += index * 5;
        handle += 0x6E;
        expected++;
        ready += maybeCheckAndResetGrapicsElement(scene, handle, 30) != FALSE;
    }
    return ready == expected;
}

// .text:0x0007AE3C size:0x11BC mapped:0x806B9ED0
void fn_2_7AE3C(MenuScene *scene, s32 index) {
    s32 i;
    s32 captainPosition;
    E(s32, CHAR_ID) captain;
    BOOL cpuPlayer;

    if (isStepClear(gameSetUpStep[index + 0xD])) {
        SCENE_RECORD(scene, 0x6)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, 0x8)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, 0x1C)->flags |= UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, 0x1D)->flags |= UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, 0x1E)->flags |= UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, 0x1F)->flags |= UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, 0x78)->flags &= ~UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, 0x79)->flags &= ~UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, 0x7C)->flags &= ~UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, 0x7D)->flags &= ~UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, 0x80)->flags &= ~UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, 0x81)->flags &= ~UI_FLAG_VISIBLE;
        channelRecord(scene, index, 0x97)->elementIndex = 0x77;
        channelRecord(scene, index, 0x99)->elementIndex = 0x76;
        {
            int position;
            for (position = 0; position < (s32)PLAYERS_PER_TEAM; position++) {
                rosterRecord(scene, index, position, 0x22)->flags &= ~UI_FLAG_VISIBLE;
            }
        }
        channelRecord(scene, index, 0x0)->elementIndex = 0x48;
        channelRecord(scene, index, 0x2)->elementIndex = 0x48;
        channelRecord(scene, index, 0x4)->elementIndex = 0x51;
        channelRecord(scene, index, 0x0)->frame = 0;
        channelRecord(scene, index, 0x2)->frame = 0;
        channelRecord(scene, index, 0x4)->frame = 0;
        channelRecord(scene, index, 0x0)->playMode = UI_PLAY_FORWARD;
        channelRecord(scene, index, 0x2)->playMode = UI_PLAY_FORWARD;
        channelRecord(scene, index, 0x4)->playMode = UI_PLAY_FORWARD;
        channelRecord(scene, index, 0x12)->frame = 10 << 16;
        channelRecord(scene, index, 0x12)->playMode = UI_PLAY_BACKWARD;
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            channelRecord(scene, index, 0x1C)->frame = 0;
            channelRecord(scene, index, 0x1C)->playMode = UI_PLAY_FORWARD;
            captain = Static_Stats_Tables.captainSelectedID[index];
            for (i = 0; i < PLAYERS_PER_TEAM; i++) {
                if (cursorPositions.roster.rosterCharID[index][i] == captain) {
                    captainPosition = cursorPositions.roster.positionSwapMapping[index][i];
                }
            }
            Static_Stats_Tables.captainSelectedID[index] = captain;
            for (i = 0; i < PLAYERS_PER_TEAM; i++) {
                s32 position = cursorPositions.roster.positionSwapMapping[index][i];

                if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME &&
                    lbl_2_bss_F468[index + 0x37] == 0 && index == 1) {
                    if (i == (s8)captainPosition) {
                        rosterRecord(scene, index, i, 0x46)->elementIndex =
                            (s8)(Static_Stats_Tables.playerNumberByPort[0] == 0) + 0x11;
                        rosterRecord(scene, index, i, 0x46)->flags |= UI_FLAG_VISIBLE;
                    } else {
                        rosterRecord(scene, index, i, 0x46)->flags &= ~UI_FLAG_VISIBLE;
                    }
                } else {
                    if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
                        cpuPlayer = FALSE;
                        if (Static_Stats_Tables.playerNumberByPort[0] == 0) {
                            cpuPlayer = TRUE;
                        }
                    }
                    if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && index != 0) {
                        rosterRecord(scene, index, (s8)position, 0x46)->elementIndex = (s8)cpuPlayer + 0x11;
                    } else {
                        rosterRecord(scene, index, (s8)position, 0x46)->elementIndex =
                            Static_Stats_Tables.playerNumberByPort[index] + 0x11;
                    }
                    rosterRecord(scene, index, (s8)position, 0x46)->frame = 0;
                    rosterRecord(scene, index, (s8)position, 0x46)->flags |= UI_FLAG_VISIBLE;
                    rosterRecord(scene, index, (s8)position, 0x46)->playMode = UI_PLAY_STOP;
                }
                if (cursorPositions.roster.rosterCharID[index][i] != CHAR_ID_NONE) {
                    rosterRecord(scene, index, (s8)position, 0x34)->flags |= UI_FLAG_VISIBLE;
                    if (i == TEAM_STATE(index)) {
                        rosterRecord(scene, index, (s8)position, 0x34)->frame = 10 << 16;
                        rosterRecord(scene, index, (s8)position, 0x34)->playMode = UI_PLAY_STOP;
                        rosterRecord(scene, index, (s8)position, 0x22)->flags |= UI_FLAG_VISIBLE;
                        rosterRecord(scene, index, (s8)position, 0x22)->playMode = UI_PLAY_FORWARD;
                    } else {
                        rosterRecord(scene, index, (s8)position, 0x34)->frame = 20 << 16;
                        rosterRecord(scene, index, (s8)position, 0x34)->playMode = UI_PLAY_STOP;
                        rosterRecord(scene, index, (s8)position, 0x22)->flags &= ~UI_FLAG_VISIBLE;
                    }
                    rosterRecord(scene, index, (s8)position, 0x58)->frame =
                        cursorPositions.roster.rosterCharID[index][i] << 16;
                    rosterRecord(scene, index, (s8)position, 0x58)->playMode = UI_PLAY_STOP;
                } else {
                    rosterRecord(scene, index, (s8)position, 0x34)->flags &= ~UI_FLAG_VISIBLE;
                    rosterRecord(scene, index, (s8)position, 0x22)->flags &= ~UI_FLAG_VISIBLE;
                }
            }
            channelRecord(scene, index, 0x6A)->frame = 0;
            channelRecord(scene, index, 0x6A)->playMode = UI_PLAY_FORWARD;
            {
                int star;
                for (star = 0; star < 5; star++) {
                    channelRecord(scene, index * 5, star + 0x6E)->frame = 0;
                    channelRecord(scene, index * 5, star + 0x6E)->playMode = UI_PLAY_STOP;
                }
            }
            if (g_d_GameSettings.p2_CPU_match_code != P2_CPU_CODE_1_PLAYER_GAME || index == 0) {
                channelRecord(scene, index, 0x8F)->playMode = UI_PLAY_FORWARD;
                channelRecord(scene, index, 0x91)->frame = 0;
                channelRecord(scene, index, 0x91)->playMode = UI_PLAY_FORWARD;
            }
        } else {
            channelRecord(scene, index, 0x80)->frame = 0;
            channelRecord(scene, index, 0x80)->playMode = UI_PLAY_STOP;
            channelRecord(scene, index, 0x82)->frame = 0;
            channelRecord(scene, index, 0x82)->playMode = UI_PLAY_STOP;
            channelRecord(scene, index, 0x78)->frame = 0;
            channelRecord(scene, index, 0x78)->playMode = UI_PLAY_STOP;
            channelRecord(scene, index, 0x7A)->frame = 0;
            channelRecord(scene, index, 0x7A)->playMode = UI_PLAY_STOP;
            channelRecord(scene, index, 0x97)->elementIndex = 0x77;
            SCENE_RECORD(scene, 0x98)->flags &= ~UI_FLAG_VISIBLE;
            SCENE_RECORD(scene, 0x97)->frame = 0;
            SCENE_RECORD(scene, 0x97)->flags &= ~UI_FLAG_VISIBLE;
            channelRecord(scene, index, 0xB0)->flags &= ~UI_FLAG_VISIBLE;
            channelRecord(scene, index, 0x89)->frame = 0;
            channelRecord(scene, index, 0x89)->playMode = UI_PLAY_FORWARD;
            channelRecord(scene, index, 0x85)->frame = 0;
            channelRecord(scene, index, 0x85)->playMode = UI_PLAY_FORWARD;
            channelRecord(scene, index, 0x1C)->frame = 0;
            channelRecord(scene, index, 0x1C)->playMode = UI_PLAY_FORWARD;
            if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
                cpuPlayer = FALSE;
                if (Static_Stats_Tables.playerNumberByPort[0] == 0) {
                    cpuPlayer = TRUE;
                }
            }
            for (i = 0; i < PLAYERS_PER_TEAM; i++) {
                s32 position = cursorPositions.roster.positionSwapMapping[index][i];

                if (index != 0) {
                    rosterRecord(scene, index, (s8)position, 0x46)->elementIndex = (s8)cpuPlayer + 0x11;
                } else {
                    rosterRecord(scene, index, (s8)position, 0x46)->elementIndex =
                        Static_Stats_Tables.playerNumberByPort[index] + 0x11;
                }
                if (i == TEAM_STATE(index)) {
                    rosterRecord(scene, index, (s8)position, 0x46)->flags |= UI_FLAG_VISIBLE;
                    rosterRecord(scene, index, (s8)position, 0x46)->playMode = UI_PLAY_FORWARD;
                } else {
                    rosterRecord(scene, index, (s8)position, 0x46)->flags |= UI_FLAG_VISIBLE;
                    rosterRecord(scene, index, (s8)position, 0x46)->playMode = UI_PLAY_STOP;
                }
                if (cursorPositions.roster.rosterCharID[index][i] != CHAR_ID_NONE) {
                    rosterRecord(scene, index, (s8)position, 0x34)->flags |= UI_FLAG_VISIBLE;
                    if (i == TEAM_STATE(index)) {
                        rosterRecord(scene, index, (s8)position, 0x34)->frame = 10 << 16;
                        rosterRecord(scene, index, (s8)position, 0x34)->playMode = UI_PLAY_STOP;
                    } else {
                        rosterRecord(scene, index, (s8)position, 0x34)->frame = 20 << 16;
                        rosterRecord(scene, index, (s8)position, 0x34)->playMode = UI_PLAY_STOP;
                    }
                    rosterRecord(scene, index, (s8)cursorPositions.roster.positionSwapMapping[index][i], 0x58)->frame =
                        cursorPositions.roster.rosterCharID[index][i] << 16;
                    rosterRecord(scene, index, (s8)cursorPositions.roster.positionSwapMapping[index][i], 0x58)->playMode = UI_PLAY_STOP;
                } else {
                    rosterRecord(scene, index, i, 0x34)->flags &= ~UI_FLAG_VISIBLE;
                }
            }
            if (menuControlVariables->previousScreen == 0xB && index == 0 &&
                g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
                channelRecord(scene, index, 0x6A)->frame = 0;
                channelRecord(scene, index, 0x6A)->playMode = UI_PLAY_STOP;
            } else {
                channelRecord(scene, index, 0x6A)->frame = 0;
                channelRecord(scene, index, 0x6A)->playMode = UI_PLAY_FORWARD;
            }
            teamSelectionSetChemStars(scene, index);
        }
        if (menuControlVariables->previousScreen == 0xB ||
            g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE || index == 0) {
                channelRecord(scene, index, 0x93)->frame = 0;
                channelRecord(scene, index, 0x93)->playMode = UI_PLAY_FORWARD;
                channelRecord(scene, index, 0x95)->frame = 0;
                channelRecord(scene, index, 0x95)->playMode = UI_PLAY_FORWARD;
            }
            if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
                channelRecord(scene, index, 0x8F)->frame = 0;
                channelRecord(scene, index, 0x8F)->playMode = UI_PLAY_FORWARD;
                channelRecord(scene, index, 0x91)->frame = 0;
                channelRecord(scene, index, 0x91)->playMode = UI_PLAY_STOP;
            }
        }
        if (lbl_2_bss_F468[0x3F] != 0 && lbl_2_bss_F468[0x37] != 0 &&
            g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            if (index == 0) {
                channelRecord(scene, index, 0x93)->frame = 0;
                channelRecord(scene, index, 0x93)->playMode = UI_PLAY_FORWARD;
                channelRecord(scene, index, 0x95)->frame = 0;
                channelRecord(scene, index, 0x95)->playMode = UI_PLAY_FORWARD;
            } else {
                channelRecord(scene, index, 0x93)->flags &= ~UI_FLAG_VISIBLE;
            }
        }
        makeCursorUnmovable(index);
        gameSetUpStep[index + 0xD] = 1;
    }
}

// .text:0x0007AC64 size:0x1D8 mapped:0x806B9CF8
void fn_2_7AC64(MenuScene *scene, s32 index) {
    s32 ready;
    s32 expected;

    if (isStepActive(gameSetUpStep[index + 0xD])) {
        ready = maybeCheckAndResetGrapicsElement(scene, index, 20) != FALSE;
        ready += maybeCheckAndResetGrapicsElement(scene, index + 2, 20) != FALSE;
        ready += maybeCheckAndResetGrapicsElement(scene, index + 0x1C, 10) != FALSE;
        ready += maybeCheckAndResetGrapicsElement(scene, index + 0x6A, 10) != FALSE;
        expected = 4;
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            ready += maybeCheckAndResetGrapicsElement(scene, index + 0x89, 5) != FALSE;
            expected = 6;
            ready += maybeCheckAndResetGrapicsElement(scene, index + 0x85, 10) != FALSE;
        }
        if (resetChemistryStars(scene, index) && ready == expected) {
            makeCursorMovable(index);
            if (menuControlVariables->previousScreen == 0xB && index == 0 &&
                g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
                updateCharacterSelectProcessCode(0, 0x11);
            } else {
                gameSetUpStep[index + 0xD] = 2;
            }
        }
    }
}

// .text:0x0007A9D8 size:0x28C mapped:0x806B9A6C
void fn_2_7A9D8(MenuScene *scene, s32 index) {
    if (isStepClear(gameSetUpStep[index + 0xD])) {
        SCENE_RECORD(scene, index)->frame = 20 << 16;
        SCENE_RECORD(scene, index + 2)->frame = 20 << 16;
        SCENE_RECORD(scene, index)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, index + 2)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, index + 4)->frame = 30 << 16;
        SCENE_RECORD(scene, index + 4)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, index + 0x85)->frame = 10 << 16;
        SCENE_RECORD(scene, index + 0x85)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, index + 0x89)->frame = 5 << 16;
        SCENE_RECORD(scene, index + 0x89)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, index + 0x6A)->frame = 10 << 16;
        SCENE_RECORD(scene, index + 0x6A)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, index + 0x34)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, index + 0x93)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, index + 0x8F)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, index + 0xB2)->flags &= ~UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, index + 0xAE)->flags &= ~UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, index + 0x97)->flags &= ~UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, index + 0xAC)->flags &= ~UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, index + 0xC)->flags &= ~UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, index + 0x12)->flags &= ~UI_FLAG_VISIBLE;
        makeCursorUnmovable(index);
        gameSetUpStep[index + 0xD] = 1;
    }
}

// .text:0x0007A748 size:0x290 mapped:0x806B97DC
void fn_2_7A748(MenuScene *scene, s32 index) {
    s32 ready;

    if (isStepActive(gameSetUpStep[index + 0xD])) {
        ready = maybeCheckAndResetGrapicsElement(scene, index, 0) != FALSE;
        ready += maybeCheckAndResetGrapicsElement(scene, index + 2, 0) != FALSE;
        ready += maybeCheckAndResetGrapicsElement(scene, index + 0x85, 0) != FALSE;
        ready += maybeCheckAndResetGrapicsElement(scene, index + 0x6A, 0) != FALSE;
        if (ready == 4) {
            SCENE_RECORD(scene, index)->elementIndex = 0x47;
            SCENE_RECORD(scene, index + 2)->elementIndex = 0x47;
            SCENE_RECORD(scene, index + 0x97)->elementIndex = 0x78;
            SCENE_RECORD(scene, index + 0x99)->elementIndex = 0x79;
            SCENE_RECORD(scene, 0x1C)->flags &= ~UI_FLAG_VISIBLE;
            SCENE_RECORD(scene, 0x1D)->flags &= ~UI_FLAG_VISIBLE;
            SCENE_RECORD(scene, 0x1E)->flags &= ~UI_FLAG_VISIBLE;
            SCENE_RECORD(scene, 0x1F)->flags &= ~UI_FLAG_VISIBLE;
            SCENE_RECORD(scene, 0x78)->flags |= UI_FLAG_VISIBLE;
            SCENE_RECORD(scene, 0x79)->flags |= UI_FLAG_VISIBLE;
            SCENE_RECORD(scene, 0x7C)->flags |= UI_FLAG_VISIBLE;
            SCENE_RECORD(scene, 0x7D)->flags |= UI_FLAG_VISIBLE;
            SCENE_RECORD(scene, 0x80)->flags |= UI_FLAG_VISIBLE;
            SCENE_RECORD(scene, 0x81)->flags |= UI_FLAG_VISIBLE;
            SCENE_RECORD(scene, 0xF)->playMode = UI_PLAY_STOP;
            makeCursorMovable(index);
            gameSetUpStep[index + 0xD] = 2;
        }
    }
}

// .text:0x0007A5B8 size:0x190 mapped:0x806B964C
void fn_2_7A5B8(MenuScene *scene, s32 index) {

    if (isStepClear(gameSetUpStep[index + 0xD])) {
        SCENE_RECORD(scene, index)->frame = 0x140000;
        SCENE_RECORD(scene, index + 2)->frame = 0x140000;
        SCENE_RECORD(scene, index)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, index + 2)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, index + 0x85)->frame = 0x140000;
        SCENE_RECORD(scene, index + 0x85)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, index + 0x1C)->frame = 0x140000;
        SCENE_RECORD(scene, index + 0x1C)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, index + 0x6A)->frame = 0x1E0000;
        SCENE_RECORD(scene, index + 0x6A)->playMode = UI_PLAY_FORWARD;
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE || index == 0) {
            SCENE_RECORD(scene, index + 0x93)->flags &= ~UI_FLAG_VISIBLE;
        }
        makeCursorUnmovable(index);
        gameSetUpStep[index + 0xD] = 1;
    }
}

// .text:0x0007A460 size:0x158 mapped:0x806B94F4
void fn_2_7A460(MenuScene *scene, s32 index) {

    if (isStepActive(gameSetUpStep[index + 0xD])) {
        s32 done = 0;

        done += maybeCheckAndResetGrapicsElement(scene, index, 0x28) != FALSE;
        done += maybeCheckAndResetGrapicsElement(scene, index + 2, 0x28) != FALSE;
        done += maybeCheckAndResetGrapicsElement(scene, index + 0x85, 0x1E) != FALSE;
        done += maybeCheckAndResetGrapicsElement(scene, index + 0x1C, 0x1E) != FALSE;
        done += maybeCheckAndResetGrapicsElement(scene, index + 0x6A, 0x32) != FALSE;
        if (done == 5) {
            SCENE_RECORD(scene, index + 0xC)->flags &= ~UI_FLAG_VISIBLE;
            SCENE_RECORD(scene, index + 0x12)->flags &= ~UI_FLAG_VISIBLE;
            makeCursorMovable(index);
            gameSetUpStep[index + 0xD] = 2;
        }
    }
}

// .text:0x0007A194 size:0x2CC mapped:0x806B9228
void fn_2_7A194(MenuScene *scene, s32 index) {

    if (isStepClear(gameSetUpStep[index + 0xD])) {
        s32 want = TEAM_STATE(index + 2);
        s32 slot;

        slot = findRosterSlot(index, want);
        SCENE_RECORD(scene, index + 0x93)->frame = 0;
        SCENE_RECORD(scene, index + 0x93)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, index + 0x95)->frame = 0;
        SCENE_RECORD(scene, index + 0x95)->playMode = UI_PLAY_FORWARD;
        if (want == 0xA) {
            SCENE_RECORD(scene, index + 0x91)->frame = 0xA0000;
            SCENE_RECORD(scene, index + 0x91)->playMode = UI_PLAY_BACKWARD;
        } else if (want != 9) {
            rosterRecord(scene, index, want, 0x46)->frame = 0xF0000;
            rosterRecord(scene, index, want, 0x46)->playMode = UI_PLAY_BACKWARD;
            if (cursorPositions.roster.rosterCharID[index][slot] != CHAR_ID_NONE &&
                cursorPositions.roster.rosterCharID[index][slot] != NUM_CHOOSABLE_CHARACTERS) {
                rosterRecord(scene, index, want, 0x34)->frame = 0xA0000;
                rosterRecord(scene, index, want, 0x34)->playMode = UI_PLAY_FORWARD;
            }
        }
        makeCursorUnmovable(index);
        gameSetUpStep[index + 0xD] = 1;
    }
}

// .text:0x00079FAC size:0x1E8 mapped:0x806B9040
void fn_2_79FAC(MenuScene *scene, s32 index) {

    if (isStepActive(gameSetUpStep[index + 0xD])) {
        s32 want = TEAM_STATE(index + 2);
        s32 slot;
        s32 placed = 0;
        s32 done = 0;

        slot = findRosterSlot(index, want);
        if (cursorPositions.roster.rosterCharID[index][slot] != CHAR_ID_NONE &&
            cursorPositions.roster.rosterCharID[index][slot] != NUM_CHOOSABLE_CHARACTERS && want < 9) {
            placed = 1;
            done = maybeCheckAndResetGrapicsElement(scene, rosterHandle(index, want, 0x34), 0x14) != FALSE;
        }
        if (done == placed) {
            makeCursorMovable(index);
            gameSetUpStep[index + 0xD] = 2;
        }
    }
}

// .text:0x00079CF8 size:0x2B4 mapped:0x806B8D8C
void fn_2_79CF8(MenuScene *scene, s32 index) {

    if (isStepClear(gameSetUpStep[index + 0xD])) {
        s32 want = (s8)TEAM_STATE(index);
        s32 copy = TEAM_STATE(index + 2);
        s32 slot;

        slot = findRosterSlot(index, want);
        if (copy == 9) {
            SCENE_RECORD(scene, index + 0x95)->frame = 0xA0000;
            SCENE_RECORD(scene, index + 0x95)->playMode = UI_PLAY_BACKWARD;
        } else if (copy == 0xA) {
            SCENE_RECORD(scene, index + 0x91)->frame = 0xA0000;
            SCENE_RECORD(scene, index + 0x91)->playMode = UI_PLAY_BACKWARD;
        }
        rosterRecord(scene, index, want, 0x46)->frame = 0;
        rosterRecord(scene, index, want, 0x46)->playMode = UI_PLAY_FORWARD;
        if (cursorPositions.roster.rosterCharID[index][slot] != CHAR_ID_NONE) {
            rosterRecord(scene, index, want, 0x34)->frame = 0x140000;
            rosterRecord(scene, index, want, 0x34)->playMode = UI_PLAY_BACKWARD;
        }
        makeCursorUnmovable(index);
        gameSetUpStep[index + 0xD] = 1;
    }
}

// .text:0x00079B24 size:0x1D4 mapped:0x806B8BB8
void fn_2_79B24(MenuScene *scene, s32 index) {

    if (isStepActive(gameSetUpStep[index + 0xD])) {
        s32 want = (s8)TEAM_STATE(index);
        s32 slot;
        s32 placed = 0;
        s32 done = 0;

        slot = findRosterSlot(index, want);
        if (cursorPositions.roster.rosterCharID[index][slot] != CHAR_ID_NONE) {
            placed = 1;
            done = maybeCheckAndResetGrapicsElement(scene, rosterHandle(index, want, 0x34), 10) != FALSE;
        }
        if (done == placed) {
            makeCursorMovable(index);
            gameSetUpStep[index + 0xD] = 2;
        }
    }
}

// .text:0x00079930 size:0x1F4 mapped:0x806B89C4
void randomTeamMemberSelection(MenuScene *scene, s32 index) {

    if (isStepClear(gameSetUpStep[index + 0xD])) {
        s32 i;

        for (i = 0; i < PLAYERS_PER_TEAM; i++) {
            s32 swap = (s8)cursorPositions.roster.positionSwapMapping[index][i];
            s32 ch = cursorPositions.roster.rosterCharID[index][i];

            rosterRecord(scene, index, swap, 0x34)->flags |= UI_FLAG_VISIBLE;
            rosterRecord(scene, index, swap, 0x34)->frame = 0;
            rosterRecord(scene, index, swap, 0x34)->playMode = UI_PLAY_FORWARD;
            rosterRecord(scene, index, swap, 0x58)->frame = ch << 16;
        }
        teamSelectionSetChemStars(scene, index);
        if (TEAM_STATE(index) == 9) {
            SCENE_RECORD(scene, index + 0x93)->frame = 0;
            SCENE_RECORD(scene, index + 0x93)->playMode = UI_PLAY_FORWARD;
            SCENE_RECORD(scene, index + 0x95)->frame = 0;
            SCENE_RECORD(scene, index + 0x95)->playMode = UI_PLAY_FORWARD;
            SCENE_RECORD(scene, index + 0x91)->frame = 0xA0000;
            SCENE_RECORD(scene, index + 0x91)->playMode = UI_PLAY_BACKWARD;
        }
        makeCursorUnmovable(index);
        gameSetUpStep[index + 0xD] = 1;
    }
}

// .text:0x00079764 size:0x1CC mapped:0x806B87F8
void fn_2_79764(MenuScene *scene, s32 index) {

    if (isStepActive(gameSetUpStep[index + 0xD])) {
        s32 hits = 0;
        s32 total = 0;
        s32 i;

        for (i = 0; i < PLAYERS_PER_TEAM; i++) {
            total++;
            hits += maybeCheckAndResetGrapicsElement(scene, rosterHandle(index, i, 0x34), 0x14) != FALSE;
        }
        if (!resetChemistryStars(scene, index)) {
            return;
        }
        if (hits != total) {
            return;
        }
        for (i = 0; i < PLAYERS_PER_TEAM; i++) {
            if ((s8)cursorPositions.roster.rosterSpotFilledInd[index][i] == 0) {
                cursorPositions.roster.rosterSpotFilledInd[index][i] = 1;
            }
        }
        makeCursorMovable(index);
        gameSetUpStep[index + 0xD] = 2;
    }
}

// .text:0x00079688 size:0xDC mapped:0x806B871C
void fn_2_79688(MenuScene *scene, s32 index) {
    int i;

    if (gameSetUpStep[index + 0xD] != 0) {
        return;
    }
    for (i = 0; i < (s32)PLAYERS_PER_TEAM; i++) {
        s32 handle = scene->firstHandle + i;
        handle += index * PLAYERS_PER_TEAM;
        handle += 0x46;
        ((UIRecord *)graphicsRelatedArray[handle].object)->playMode = UI_PLAY_BACKWARD;
    }
    channelRecord(scene, index, 0x95)->frame = 0xA0000;
    channelRecord(scene, index, 0x95)->playMode = UI_PLAY_FORWARD;
}

// .text:0x00079634 size:0x54 mapped:0x806B86C8
void fn_2_79634(void *unused, s32 index) {

    if (isStepActive(gameSetUpStep[index + 0xD])) {
        makeCursorMovable(index);
        gameSetUpStep[index + 0xD] = 2;
    }
}

// .text:0x00079394 size:0x2A0 mapped:0x806B8428
void cssAction_0x18(MenuScene *scene, s32 index) {

    if (isStepClear(gameSetUpStep[index + 0xD])) {
        if (TEAM_STATE(index) == 9) {
            SCENE_RECORD(scene, index + 0x95)->frame = 0;
            SCENE_RECORD(scene, index + 0x95)->playMode = UI_PLAY_FORWARD;
            SCENE_RECORD(scene, index + 0x91)->frame = 0xA0000;
            SCENE_RECORD(scene, index + 0x91)->playMode = UI_PLAY_BACKWARD;
        } else if (TEAM_STATE(index) == 0xA) {
            SCENE_RECORD(scene, index + 0x95)->frame = 0xA0000;
            SCENE_RECORD(scene, index + 0x95)->playMode = UI_PLAY_BACKWARD;
            SCENE_RECORD(scene, index + 0x91)->frame = 0;
            SCENE_RECORD(scene, index + 0x91)->playMode = UI_PLAY_FORWARD;
        }
        makeCursorUnmovable(index);
        gameSetUpStep[index + 0xD] = 1;
    }
    if (gameSetUpStep[index + 0xD] == 1) {
        s32 teamState = TEAM_STATE(index);
        s32 ready = 0;
        s32 target = 0;

        if (teamState == 9) {
            target = 2;
            ready = ((SCENE_RECORD(scene, index + 0x95)->frame >> 16) >= 10) +
                    ((SCENE_RECORD(scene, index + 0x91)->frame >> 16) == 0);
        } else if (teamState == 0xA) {
            target = 2;
            ready = ((SCENE_RECORD(scene, index + 0x91)->frame >> 16) >= 10) +
                    ((SCENE_RECORD(scene, index + 0x95)->frame >> 16) == 0);
        }
        if (ready == target) {
            TEAM_STATE(index + 2) = teamState;
            makeCursorMovable(index);
            gameSetUpStep[index + 0xD] = 2;
        }
    }
}

// .text:0x0007912C size:0x268 mapped:0x806B81C0
void cssAction_0x19(MenuScene *scene, s32 index) {

    if (isStepClear(gameSetUpStep[index + 0xD])) {
        if (gameSetUpStep[0] == 2) {
            s32 j;

            for (j = 1; j <= 8; j++) {
                s32 slot = (s8)cursorPositions.roster.positionSwapMapping[index][j];

                if (cursorPositions.roster.rosterCharID[index][slot] != CHAR_ID_NONE &&
                    cursorPositions.roster.rosterCharID[index][slot] != NUM_CHOOSABLE_CHARACTERS) {
                    rosterRecord(scene, index, j, 0x34)->playMode = UI_PLAY_BACKWARD;
                }
            }
            teamSelectionSetChemStars(scene, index);
        }
        makeCursorUnmovable(index);
        gameSetUpStep[index + 0xD] = 1;
    }
    if (gameSetUpStep[index + 0xD] == 1) {
        s32 attempted = 0;
        s32 succeeded = 0;
        s32 j;

        for (j = 1; j <= 8; j++) {
            s32 slot = (s8)cursorPositions.roster.positionSwapMapping[index][j];

            if (cursorPositions.roster.rosterCharID[index][slot] != CHAR_ID_NONE &&
                cursorPositions.roster.rosterCharID[index][slot] != NUM_CHOOSABLE_CHARACTERS) {
                attempted++;
                succeeded += maybeCheckAndResetGrapicsElement(scene, rosterHandle(index, j, 0x34), 0) != FALSE;
            }
        }
        if (gameSetUpStep[0] == 2) {
            s32 k;
            s32 limit = Static_Stats_Tables.startingChemStars[index];
            s32 attempted2 = 0;
            s32 succeeded2 = 0;

            for (k = 0; k < limit; k++) {
                attempted2++;
                succeeded2 += maybeCheckAndResetGrapicsElement(scene, k + index * 5 + 0x6E, 0x1E) != FALSE;
            }
            if (succeeded2 != attempted2) {
                return;
            }
        }
        if (succeeded == attempted) {
            makeCursorMovable(index);
            gameSetUpStep[index + 0xD] = 2;
            if (lbl_2_bss_F468[index + 0x43] != 0) {
                starHitSetting_Unused_maybe(index);
                lbl_2_bss_F468[index + 0x43] = 0;
            }
        }
    }
}

// .text:0x00078F78 size:0x1B4 mapped:0x806B800C
void cssAction_0x1a(MenuScene *scene, s32 index) {

    if (isStepClear(gameSetUpStep[index + 0xD])) {
        SCENE_RECORD(scene, index + 0xA)->flags |= UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, index + 0xA)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, index + 0x1E)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, index + 0x89)->frame = 0;
        SCENE_RECORD(scene, index + 0x89)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, index + 0x8D)->frame = 0;
        SCENE_RECORD(scene, index + 0x8D)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, index + 0x6A)->playMode = UI_PLAY_BACKWARD;
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
            SCENE_RECORD(scene, index + 0x8F)->elementIndex = 8;
            SCENE_RECORD(scene, index + 0x8F)->frame = 0;
            SCENE_RECORD(scene, index + 0x8F)->playMode = UI_PLAY_FORWARD;
        }
        makeCursorUnmovable(index);
        gameSetUpStep[index + 0xD] = 1;
    }
    if (gameSetUpStep[index + 0xD] == 1) {
        makeCursorMovable(index);
        gameSetUpStep[index + 0xD] = 2;
    }
}
