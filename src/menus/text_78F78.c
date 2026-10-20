#include "menus/text_78F78.h"
#include "menus/text_744C8.h"
#include "menus/text_0323C.h"
#include "static/UnknownHomes_Static.h"
#include "text/text.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x80062674.h"
#include "Unknown/orderchange.h"

extern u8 gameSetUpStep[];
extern u8 lbl_2_bss_F468[];

/* Per-team state word in lbl_2_bss_F468 (indexed by team). */
#define TEAM_STATE(team) (((s32 *)lbl_2_bss_F468)[(team)])

/* Record for scene handle k: graphicsRelatedArray[scene->firstHandle + k]. */
#define SCENE_RECORD(scene, k) ((UIRecord *)graphicsRelatedArray[(scene)->firstHandle + (k)].object)

// .text:0x0007AE3C size:0x11BC mapped:0x806B9ED0
void fn_2_7AE3C(MenuScene *scene, s32 index) {
    return;
}

// .text:0x0007AC64 size:0x1D8 mapped:0x806B9CF8
void fn_2_7AC64(MenuScene *scene, s32 index) {
    return;
}

// .text:0x0007A9D8 size:0x28C mapped:0x806B9A6C
void fn_2_7A9D8(MenuScene *scene, s32 index) {
    return;
}

// .text:0x0007A748 size:0x290 mapped:0x806B97DC
void fn_2_7A748(MenuScene *scene, s32 index) {
    return;
}

// .text:0x0007A5B8 size:0x190 mapped:0x806B964C
void fn_2_7A5B8(MenuScene *scene, s32 index) {
    u8 *step = &gameSetUpStep[index + 0xD];

    if (*step == 0) {
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
        if (g_d_GameSettings.GameModeSelected != 5 || index == 0) {
            SCENE_RECORD(scene, index + 0x93)->flags &= ~UI_FLAG_VISIBLE;
        }
        makeCursorUnmovable(index);
        *step = 1;
    }
}

// .text:0x0007A460 size:0x158 mapped:0x806B94F4
void fn_2_7A460(MenuScene *scene, s32 index) {
    u8 *step = &gameSetUpStep[index + 0xD];

    if (*step == 1) {
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
            *step = 2;
        }
    }
}

// .text:0x0007A194 size:0x2CC mapped:0x806B9228
void fn_2_7A194(MenuScene *scene, s32 index) {
    u8 *step = &gameSetUpStep[index + 0xD];

    if (*step == 0) {
        s32 want = TEAM_STATE(index + 2);
        s32 slot;

        for (slot = 0; slot < 9; slot++) {
            if ((s8)cursorPositions.roster.positionSwapMapping[index][slot] == want) {
                break;
            }
        }
        SCENE_RECORD(scene, index + 0x93)->frame = 0;
        SCENE_RECORD(scene, index + 0x93)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, index + 0x95)->frame = 0;
        SCENE_RECORD(scene, index + 0x95)->playMode = UI_PLAY_FORWARD;
        if (want == 0xA) {
            SCENE_RECORD(scene, index + 0x91)->frame = 0xA0000;
            SCENE_RECORD(scene, index + 0x91)->playMode = UI_PLAY_BACKWARD;
        } else if (want != 9) {
            SCENE_RECORD(scene, want + index * 9 + 0x46)->frame = 0xF0000;
            SCENE_RECORD(scene, want + index * 9 + 0x46)->playMode = UI_PLAY_BACKWARD;
            if (cursorPositions.roster.rosterCharID[index][slot] != CHAR_ID_NONE &&
                cursorPositions.roster.rosterCharID[index][slot] != 0x36) {
                SCENE_RECORD(scene, want + index * 9 + 0x34)->frame = 0xA0000;
                SCENE_RECORD(scene, want + index * 9 + 0x34)->playMode = UI_PLAY_FORWARD;
            }
        }
        makeCursorUnmovable(index);
        *step = 1;
    }
}

// .text:0x00079FAC size:0x1E8 mapped:0x806B9040
void fn_2_79FAC(MenuScene *scene, s32 index) {
    u8 *step = &gameSetUpStep[index + 0xD];

    if (*step == 1) {
        s32 want = TEAM_STATE(index + 2);
        s32 slot;
        s32 placed = 0;
        s32 done = 0;

        for (slot = 0; slot < 9; slot++) {
            if ((s8)cursorPositions.roster.positionSwapMapping[index][slot] == want) {
                break;
            }
        }
        if (cursorPositions.roster.rosterCharID[index][slot] != CHAR_ID_NONE &&
            cursorPositions.roster.rosterCharID[index][slot] != 0x36 && want < 9) {
            placed = 1;
            done = maybeCheckAndResetGrapicsElement(scene, want + index * 9 + 0x34, 0x14) != FALSE;
        }
        if (done == placed) {
            makeCursorMovable(index);
            *step = 2;
        }
    }
}

// .text:0x00079CF8 size:0x2B4 mapped:0x806B8D8C
void fn_2_79CF8(MenuScene *scene, s32 index) {
    u8 *step = &gameSetUpStep[index + 0xD];

    if (*step == 0) {
        s32 want = (s8)TEAM_STATE(index);
        s32 copy = TEAM_STATE(index + 2);
        s32 slot;

        for (slot = 0; slot < 9; slot++) {
            if ((s8)cursorPositions.roster.positionSwapMapping[index][slot] == want) {
                break;
            }
        }
        if (copy == 9) {
            SCENE_RECORD(scene, index + 0x95)->frame = 0xA0000;
            SCENE_RECORD(scene, index + 0x95)->playMode = UI_PLAY_BACKWARD;
        } else if (copy == 0xA) {
            SCENE_RECORD(scene, index + 0x91)->frame = 0xA0000;
            SCENE_RECORD(scene, index + 0x91)->playMode = UI_PLAY_BACKWARD;
        }
        SCENE_RECORD(scene, want + index * 9 + 0x46)->frame = 0;
        SCENE_RECORD(scene, want + index * 9 + 0x46)->playMode = UI_PLAY_FORWARD;
        if (cursorPositions.roster.rosterCharID[index][slot] != CHAR_ID_NONE) {
            SCENE_RECORD(scene, want + index * 9 + 0x34)->frame = 0x140000;
            SCENE_RECORD(scene, want + index * 9 + 0x34)->playMode = UI_PLAY_BACKWARD;
        }
        makeCursorUnmovable(index);
        *step = 1;
    }
}

// .text:0x00079B24 size:0x1D4 mapped:0x806B8BB8
void fn_2_79B24(MenuScene *scene, s32 index) {
    u8 *step = &gameSetUpStep[index + 0xD];

    if (*step == 1) {
        s32 want = TEAM_STATE(index);
        s32 slot;
        s32 placed = 0;
        s32 done = 0;

        for (slot = 0; slot < 9; slot++) {
            if (cursorPositions.roster.positionSwapMapping[index][slot] == want) {
                break;
            }
        }
        if (cursorPositions.roster.rosterCharID[index][slot] != CHAR_ID_NONE) {
            placed = 1;
            done = maybeCheckAndResetGrapicsElement(scene, want + index * 9 + 0x34, 10) != FALSE;
        }
        if (done == placed) {
            makeCursorMovable(index);
            *step = 2;
        }
    }
}

// .text:0x00079930 size:0x1F4 mapped:0x806B89C4
void randomTeamMemberSelection(MenuScene *scene, s32 index) {
    u8 *step = &gameSetUpStep[index + 0xD];

    if (*step == 0) {
        s32 i;

        for (i = 0; i < 9; i++) {
            s32 swap = cursorPositions.roster.positionSwapMapping[index][i];
            s32 ch = cursorPositions.roster.rosterCharID[index][i];

            SCENE_RECORD(scene, swap + index * 9 + 0x34)->flags |= UI_FLAG_VISIBLE;
            SCENE_RECORD(scene, swap + index * 9 + 0x34)->frame = 0;
            SCENE_RECORD(scene, swap + index * 9 + 0x34)->playMode = UI_PLAY_FORWARD;
            SCENE_RECORD(scene, swap + index * 9 + 0x58)->frame = ch << 16;
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
        *step = 1;
    }
}

// .text:0x00079764 size:0x1CC mapped:0x806B87F8
void fn_2_79764(MenuScene *scene, s32 index) {
    u8 *step = &gameSetUpStep[index + 0xD];

    if (*step == 1) {
        s32 hits = 0;
        s32 total = 0;
        s32 i;
        s32 k;
        s32 limit;
        s32 attempted = 0;
        s32 succeeded = 0;

        for (i = 0; i < 9; i++) {
            total++;
            hits += maybeCheckAndResetGrapicsElement(scene, i + index * 9 + 0x34, 0x14) != FALSE;
        }
        limit = Static_Stats_Tables.startingChemStars[index];
        for (k = 0; k < limit; k++) {
            attempted++;
            succeeded += maybeCheckAndResetGrapicsElement(scene, k + index * 5 + 0x6E, 0x1E) != FALSE;
        }
        if (succeeded != attempted) {
            return;
        }
        if (hits != total) {
            return;
        }
        for (i = 0; i < 9; i++) {
            if (cursorPositions.roster.rosterSpotFilledInd[index][i] == 0) {
                cursorPositions.roster.rosterSpotFilledInd[index][i] = 1;
            }
        }
        makeCursorMovable(index);
        *step = 2;
    }
}

// .text:0x00079688 size:0xDC mapped:0x806B871C
void fn_2_79688(MenuScene *scene, s32 index) {
    s32 i;

    if (gameSetUpStep[index + 0xD] != 0) {
        return;
    }
    for (i = 0; i < 9; i += 3) {
        SCENE_RECORD(scene, i + index * 9 + 0x46)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, i + index * 9 + 0x47)->playMode = UI_PLAY_BACKWARD;
        SCENE_RECORD(scene, i + index * 9 + 0x48)->playMode = UI_PLAY_BACKWARD;
    }
    SCENE_RECORD(scene, index + 0x95)->frame = 0xA0000;
    SCENE_RECORD(scene, index + 0x95)->playMode = UI_PLAY_FORWARD;
}

// .text:0x00079634 size:0x54 mapped:0x806B86C8
void fn_2_79634(void *unused, s32 index) {
    u8 *step = &gameSetUpStep[index + 0xD];

    if (*step == 1) {
        makeCursorMovable(index);
        *step = 2;
    }
}

// .text:0x00079394 size:0x2A0 mapped:0x806B8428
void cssAction_0x18(MenuScene *scene, s32 index) {
    u8 *step = &gameSetUpStep[index + 0xD];

    if (*step == 0) {
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
        *step = 1;
    }
    if (*step == 1) {
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
            *step = 2;
        }
    }
}

// .text:0x0007912C size:0x268 mapped:0x806B81C0
void cssAction_0x19(MenuScene *scene, s32 index) {
    u8 *step = &gameSetUpStep[index + 0xD];

    if (*step == 0) {
        if (gameSetUpStep[0] == 2) {
            s32 j;

            for (j = 1; j <= 8; j++) {
                s32 slot = cursorPositions.roster.positionSwapMapping[index][j];

                if (cursorPositions.roster.rosterCharID[index][slot] != CHAR_ID_NONE &&
                    cursorPositions.roster.rosterCharID[index][slot] != 0x36) {
                    SCENE_RECORD(scene, j + index * 9 + 0x34)->playMode = UI_PLAY_BACKWARD;
                }
            }
            teamSelectionSetChemStars(scene, index);
        }
        makeCursorUnmovable(index);
        *step = 1;
    }
    if (*step == 1) {
        s32 attempted = 0;
        s32 succeeded = 0;
        s32 j;

        for (j = 1; j <= 8; j++) {
            s32 slot = cursorPositions.roster.positionSwapMapping[index][j];

            if (cursorPositions.roster.rosterCharID[index][slot] != CHAR_ID_NONE &&
                cursorPositions.roster.rosterCharID[index][slot] != 0x36) {
                attempted++;
                succeeded += maybeCheckAndResetGrapicsElement(scene, j + index * 9 + 0x34, 0) != FALSE;
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
            *step = 2;
            if (lbl_2_bss_F468[index + 0x43] != 0) {
                starHitSetting_Unused_maybe((u8)index);
                lbl_2_bss_F468[index + 0x43] = 0;
            }
        }
    }
}

// .text:0x00078F78 size:0x1B4 mapped:0x806B800C
void cssAction_0x1a(MenuScene *scene, s32 index) {
    u8 *step = &gameSetUpStep[index + 0xD];

    if (*step == 0) {
        SCENE_RECORD(scene, index + 0xA)->flags |= UI_FLAG_VISIBLE;
        SCENE_RECORD(scene, index + 0xA)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, index + 0x1E)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, index + 0x89)->frame = 0;
        SCENE_RECORD(scene, index + 0x89)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, index + 0x8D)->frame = 0;
        SCENE_RECORD(scene, index + 0x8D)->playMode = UI_PLAY_FORWARD;
        SCENE_RECORD(scene, index + 0x6A)->playMode = UI_PLAY_BACKWARD;
        if (g_d_GameSettings.GameModeSelected != 5) {
            SCENE_RECORD(scene, index + 0x8F)->elementIndex = 8;
            SCENE_RECORD(scene, index + 0x8F)->frame = 0;
            SCENE_RECORD(scene, index + 0x8F)->playMode = UI_PLAY_FORWARD;
        }
        makeCursorUnmovable(index);
        *step = 1;
    }
    if (*step == 1) {
        makeCursorMovable(index);
        *step = 2;
    }
}
