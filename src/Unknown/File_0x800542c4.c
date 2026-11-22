#include "Unknown/File_0x80056120.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x800363d8.h"
#include "Unknown/File_0x8004a2bc.h"
#include "text/text.h"
#include "static/UnknownHomes_Static.h"
#include "game/challenge/challenge_state.h"
#include "Unknown/game_set_up_step.h"
#include "Unknown/File_0x80062674.h"
#include "Unknown/orderchange.h"

// 0x800542C4-0x800569C8: one translation unit by its .data order and call graph
// (docs/splits.md, 2026-11-21): the former File_0x80056120.c (newMenuRelated)
// plus fn_800542C4 ... fn_800559EC, which have no C yet.

#define SCENE_FIRST_HANDLE(s) (*(u16 *)((u8 *)(s) + 0x14))
#define GRA_OBJECT(idx) (graphicsRelatedArray[(idx)].object)
#define OBJ_U16(o, off) (*(u16 *)((u8 *)(o) + (off)))
#define OBJ_U32(o, off) (*(u32 *)((u8 *)(o) + (off)))

extern GameSetUpStep gameSetUpStep;
extern u8 lbl_803C5EE0[0x18];
extern u8 lbl_802E4BB0[0x10];
extern UIRecordDescriptor lbl_800FF540[];

#define MENU_REC(scene, n) ((UIRecord *)graphicsRelatedArray[((MenuScene *)(scene))->firstHandle + (n)].object)

void fn_80054910(MenuScene *scene, int port) {
    u8 *gs = (u8 *)&gameSettings;
    s32 sel;
    s32 other;
    s32 valueA;
    s32 valueB;
    BOOL result;
    BOOL expected;

    if (gameSetUpStep.stepFlags[8][port] != SET_UP_STEP_PLAYING) {
        return;
    }
    sel = (s8)gs[port + 0x65];
    other = (s8)gs[port + 0x69];
    if (sel != 0) {
        if (gs[0x36] == 0) {
            valueA = gs[sel + 0x3B];
            valueB = gs[other + 0x40];
        } else {
            valueA = (gs + port * 4)[sel + 0x45];
            valueB = (gs + port * 4)[other + 0x55];
        }
    }
    result = FALSE;
    expected = FALSE;
    if (other == sel && (s8)valueA != (s8)valueB) {
        if (gs[0x36] == 0 && sel != 0) {
            if (sel == 1) {
                if ((s8)valueA != 0) {
                    expected = TRUE;
                    result = maybeCheckAndResetGrapicsElement(scene, 0x1A, 5) != FALSE;
                } else {
                    expected = TRUE;
                    result = maybeCheckAndResetGrapicsElement(scene, 0x1A, 0x19) != FALSE;
                }
            }
        } else if (gs[0x36] == 1) {
            if (gs[port + 0x37] == 0) {
                expected = TRUE;
                result = maybeCheckAndResetGrapicsElement(scene, sel + port * 4 + 0x33, 0) != FALSE;
            } else {
                expected = TRUE;
                result = maybeCheckAndResetGrapicsElement(scene, sel + port * 4 + 0x33, 0xA) != FALSE;
            }
        }
    }
    if (result == expected) {
        makeCursorMovable(port);
        gameSetUpStep.stepFlags[8][port] = SET_UP_STEP_DONE;
    }
}

void fn_80055798(MenuScene *scene, int port) {
    u8 *gs = (u8 *)&gameSettings;

    if (gameSetUpStep.stepFlags[8][port] != SET_UP_STEP_START) {
        return;
    }
    if (gs[0x36] == 0) {
        if (gs[0x3C] == 1) {
            MENU_REC(scene, 26)->playMode = UI_PLAY_FORWARD;
        } else {
            MENU_REC(scene, 26)->frame = 30 << 16;
            MENU_REC(scene, 26)->playMode = UI_PLAY_BACKWARD;
        }
        MENU_REC(scene, 6)->playMode = UI_PLAY_FORWARD;
        MENU_REC(scene, 11)->playMode = UI_PLAY_FORWARD;
        MENU_REC(scene, 27)->playMode = UI_PLAY_FORWARD;
        MENU_REC(scene, 28)->playMode = UI_PLAY_FORWARD;
        MENU_REC(scene, 0x20)->playMode = UI_PLAY_FORWARD;
        MENU_REC(scene, 0x21)->playMode = UI_PLAY_FORWARD;
        MENU_REC(scene, 0x22)->playMode = UI_PLAY_FORWARD;
        if (*(u8 *)((u8 *)&g_d_GameSettings + 6) != 2 && g_d_GameSettings.GameModeSelected == 5) {
            MENU_REC(scene, 87)->frame = 30 << 16;
            MENU_REC(scene, 87)->playMode = UI_PLAY_BACKWARD;
        }
    } else {
        MENU_REC(scene, 38)->playMode = UI_PLAY_FORWARD;
        MENU_REC(scene, 41)->playMode = UI_PLAY_FORWARD;
        MENU_REC(scene, 42)->playMode = UI_PLAY_FORWARD;
        MENU_REC(scene, 6)->playMode = UI_PLAY_FORWARD;
        MENU_REC(scene, 11)->playMode = UI_PLAY_FORWARD;
        MENU_REC(scene, 27)->playMode = UI_PLAY_FORWARD;
    }
    MENU_REC(scene, 88)->playMode = UI_PLAY_FORWARD;
    makeCursorUnmovable(port);
    gameSetUpStep.stepFlags[8][port] = SET_UP_STEP_PLAYING;
}

void newMenuRelated(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    u8 *gs = (u8 *)&gameSettings;
    u8 *gameInit = (u8 *)&g_d_GameSettings;
    u8 *statics = (u8 *)&Static_Stats_Tables;
    s16 *shorts = (s16 *)lbl_803C5EE0;
    u8 *icons = lbl_802E4BB0;
    s32 i;
    s32 k;
    s32 j;
    s32 t;
    s32 r29;
    s32 r31;
    s32 src;
    s32 v;
    s32 base;
    s32 frame;

    shorts[0] = (s8)gs[0x65];
    for (i = 0; i < 0x10; i++) {
        icons[i] = gs[0x45 + i];
    }
    icons[2] = gs[0x3D];
    icons[3] = gs[0x3E];
    icons[4] = gs[0x3F];
    shorts[1] = (s8)gs[0x66];
    shorts[2] = (s8)gs[0x67];
    shorts[3] = (s8)gs[0x68];

    addGraphicsElementToScene(item, lbl_800FF540);

    for (i = 1; i < 5; i++) {
        load_Icon(item, i + 1, 1, 0x110, i - 1);
        if (i > 1) {
            TextGraphicsObject *obj = GRA_OBJECT(SCENE_FIRST_HANDLE(item) + i + 0x1B);
            OBJ_U32(obj, 0x5C) = (u32)(i - 2) << 16;
            OBJ_U32(obj, 0x54) &= ~2;
        }
    }

    OBJ_U16(GRA_OBJECT(SCENE_FIRST_HANDLE(item) + (s8)gs[0x3C] + 0xC), 0x64) = 0x107;
    OBJ_U16(GRA_OBJECT(SCENE_FIRST_HANDLE(item) + ((s8)gs[0x3D] ^ 1) + 0xE), 0x64) = 0x107;
    load_Icon(item, 0x20, 1, 0xF9, (s8)gs[0x3D] ^ 1);
    OBJ_U16(GRA_OBJECT(SCENE_FIRST_HANDLE(item) + (s8)gs[0x3E] + 0x10), 0x64) = 0x109;
    load_Icon(item, 0x21, 1, 0xF9, (s8)gs[0x3E] + 2);
    OBJ_U16(GRA_OBJECT(SCENE_FIRST_HANDLE(item) + ((s8)gs[0x3F] ^ 1) + 0x15), 0x64) = 0x107;
    load_Icon(item, 0x22, 1, 0xF9, (s8)gs[0x3F] ^ 1);

    for (k = 0; k < 2; k++) {
        if (gameInit[0x10] == 0 && k != 0) {
            load_Icon(item, k + 0xC, 1, 0x116, 0xD);
        } else {
            load_Icon(item, k + 0xC, 1, 0x116, (s8)statics[0x46F8 + k] + 9);
        }
        load_Icon(item, k + 0xE, 1, 0x116, k + 2);
        load_Icon(item, k + 0x15, 1, 0x116, k + 2);
    }

    for (j = 0; j < 5; j++) {
        load_Icon(item, j + 0x10, 1, 0x116, j + 4);
    }

    OBJ_U32(GRA_OBJECT(SCENE_FIRST_HANDLE(item) + 0x18), 0x5C) = (u32)statics[0x470D] << 16;
    OBJ_U32(GRA_OBJECT(SCENE_FIRST_HANDLE(item) + 0x19), 0x5C) = (u32)statics[0x470E] << 16;

    for (r31 = 0; r31 < 2; r31++) {
        if (gameInit[0x10] == 0 && r31 != 0) {
            if ((s8)statics[0x46F8] != 0) {
                frame = 4;
            } else {
                frame = 5;
            }
            load_Icon(item, r31 + 0x27, 1, 0x46, frame);
        } else {
            load_Icon(item, r31 + 0x27, 1, 0x46, (s8)statics[0x46F8 + r31]);
        }

        if (gameInit[7] == 5 && r31 != 0) {
            v = (s8)((u8 *)&g_Challenge)[0x441F];
        } else {
            v = *(s32 *)(statics + 0x46E0 + 4 * r31);
        }
        OBJ_U32(GRA_OBJECT(SCENE_FIRST_HANDLE(item) + r31 + 0x3D), 0x5C) = (u32)v << 16;

        for (t = 0; t < 4; t++) {
            load_Icon(item, 0x2B + 4 * r31 + t, 1, 0x11A, t);
        }

        for (r29 = 0; r29 < 4; r29++) {
            s32 e = 0x33 + 4 * r31 + r29;
            src = (s8)gs[0x45 + 4 * r31 + r29];

            if (r29 == 0) {
                load_Icon(item, e, 1, 0x116, 1);
                load_Icon(item, e, 2, 0x116, 0);
                OBJ_U32(GRA_OBJECT(SCENE_FIRST_HANDLE(item) + e), 0x5C) = (u32)(src * 0xA0000);
            } else if (r29 == 3) {
                load_Icon(item, e, 1, 0x116, 2);
                load_Icon(item, e, 2, 0x116, 3);
                OBJ_U32(GRA_OBJECT(SCENE_FIRST_HANDLE(item) + e), 0x5C) = (u32)((src ^ 1) * 0xA0000);
            } else {
                load_Icon(item, e, 1, 0x116, 1);
                load_Icon(item, e, 2, 0x116, 0xE);
                OBJ_U32(GRA_OBJECT(SCENE_FIRST_HANDLE(item) + e), 0x5C) = (u32)(src * 0xA0000);
            }

            base = SCENE_FIRST_HANDLE(item) + 4 * r29 + r31;
            if (src != 0) {
                if (r29 == 3) {
                    OBJ_U32(GRA_OBJECT(base + 0x47), 0x54) &= ~2;
                    OBJ_U32(GRA_OBJECT(base + 0x49), 0x54) |= 2;
                } else {
                    OBJ_U32(GRA_OBJECT(base + 0x47), 0x54) |= 2;
                    OBJ_U32(GRA_OBJECT(base + 0x49), 0x54) &= ~2;
                }
            } else {
                if (r29 == 3) {
                    OBJ_U32(GRA_OBJECT(base + 0x47), 0x54) |= 2;
                    OBJ_U32(GRA_OBJECT(base + 0x49), 0x54) &= ~2;
                } else {
                    OBJ_U32(GRA_OBJECT(base + 0x47), 0x54) &= ~2;
                    OBJ_U32(GRA_OBJECT(base + 0x49), 0x54) |= 2;
                }
            }
        }
    }

    if (gameInit[7] == 5) {
        load_Icon(item, 0x57, 1, 0x20, gameInit[9]);
    } else {
        OBJ_U32(GRA_OBJECT(SCENE_FIRST_HANDLE(item) + 0x57), 0x54) &= ~2;
    }

    lbl_803C5EE0[0x15] = 0;
    currentDrawingItem->func = fn_800559EC;
}
