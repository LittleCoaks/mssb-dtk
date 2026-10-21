#include "menus/text_82CF0.h"

#include "menus/text_00110.h"
#include "menus/yd_step.h"
#include "text/text.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x80034cec.h"
#include "Unknown/File_0x800625a4.h"
#include "Unknown/File_0x80062674.h"
#include "Unknown/File_0x800363d8.h"

extern Text00110Ctl *menuControlVariables;
extern u8 menuNumber[0x28];
extern u8 cardCheck[0x5C];
extern u8 gameSetUpStep[];
extern u8 lbl_800FEF70[0x5D0];
extern u8 lbl_803CBCD8[8];
extern u8 lbl_2_data_2B4DC[];
extern u8 lbl_2_data_2DC84[8];
extern u8 lbl_2_data_2DC8C[0x3A0];
extern int menuCursors[0x16];
extern u8 superstarUnlocked[0x130];
extern u8 lbl_800EFBA4[];
extern u8 lbl_2_data_2E02C[0x2C0];
extern u8 lbl_2_bss_F468[0xC4C];
extern u8 lbl_2_data_2E2EC[];
extern u8 lbl_803CBBC4[];
extern u8 lbl_2_data_2D998[];
extern u8 lbl_2_bss_ABC0[];

void fn_80053FE8(void);
void relatedToTeamSelection3(void);
void fn_8004CA08(s32 frames);
void fn_8004A34C(u8 *buf, s32 a, s32 b, s32 c, s32 d);
void fn_8004C9FC(void);
void fn_80023CF4(s32 flag);
void sndFXStartEx(s32 sfxId, u8 volume, u32 pan, s32 unk);
BOOL maybeCheckAndResetGrapicsElement(void *scene, int handle, int frame);

static inline BOOL stadiumStepIsClear(u8 step) {
    return step == 0 ? TRUE : FALSE;
}

// .text:0x000854B0 size:0x18C mapped:0x806C4544
void fn_2_854B0(void) {
    switch (menuControlVariables->currentState) {
    case 0:
        fn_8004CA08(0x258);
        fn_8004A34C(cardCheck, 0, 0x4A, 0, 0);
        menuControlVariables->currentState = 2;
        break;
    case 2:
        if (cardCheck[0x45] == 2 || cardCheck[0x45] == 4) {
            fn_8004C9FC();
            fn_80023CF4(cardCheck[0x45] == 2);
            menuControlVariables->currentState = (cardCheck[0x45] == 2) ? 3 : 4;
        }
        break;
    case 3:
        fn_8004A34C(cardCheck, 0, 0x4B, 0, 0);
        menuControlVariables->currentState = 6;
        break;
    case 4:
        fn_8004A34C(cardCheck, 0, 0x4C, 0, 0);
        menuControlVariables->currentState = 6;
        break;
    case 6:
        if (cardCheck[0x45] == 2) {
            changeScreenVariables(1);
            fn_8004CA08(-1);
        }
        break;
    default:
        break;
    }
}

// .text:0x00085310 size:0x1A0 mapped:0x806C43A4
BOOL fn_2_85310(u16 unkR3, u16 buttons, u32 unkR5) {
    BOOL result = FALSE;

    if ((unkR5 & 3) != 0) {
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        if (menuCursors[0] == 1) {
            updateCharacterSelectProcessCode(0, 1);
        } else {
            updateCharacterSelectProcessCode(0, 2);
        }
        menuCursors[0] ^= 1;
    } else if ((buttons & 0x100) != 0) {
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        updateCharacterSelectProcessCode(0, 3);
        result = TRUE;
    } else if ((buttons & 0x200) != 0) {
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        if (menuCursors[0] == 1) {
            updateCharacterSelectProcessCode(0, 3);
            result = TRUE;
        } else {
            updateCharacterSelectProcessCode(0, 2);
            menuCursors[0] = 1;
        }
    }

    if ((unkR3 | buttons | (u16)unkR5) == 0) {
        s32 remaining = menuCursors[1] - 1;

        menuCursors[1] = remaining;
        if (remaining == 0) {
            updateCharacterSelectProcessCode(0, 3);
            result = TRUE;
        }
    } else {
        menuCursors[1] = 0x258;
    }
    return result;
}

// .text:0x000851A8 size:0x168 mapped:0x806C423C
void fn_2_851A8(void) {
    s16 state = currentDrawingItem->state;

    if (state < 0 || state > 1) {
        return;
    }
    if (state == 0) {
        updateCharacterSelectProcessCode(0, 0);
        currentDrawingItem->state = currentDrawingItem->state + 1;
    }

    if (gameSetUpStep[1] == 0) {
        gameSetUpStep[1] = 1;
        makeCursorUnmovable(0);
        if (gameSetUpStep[0x5D] == 4) {
            makeCursorMovable(0);
        }
    }
    if (gameSetUpStep[1] != 1) {
        return;
    }

    switch (gameSetUpStep[0x5D]) {
    case 0:
    case 1:
    case 2:
        gameSetUpStep[1] = 2;
        makeCursorMovable(0);
        break;
    case 3:
        if (menuCursors[0] != 0) {
            updateCharacterSelectProcessCode(0, 4);
        } else {
            DrawingSceneStruct *inserted;

            gameSetUpStep[1] = 2;
            inserted = insertGraphicDrawingFunction(fn_2_85160, currentDrawingItem->priority);
            inserted->state = 0xB4;
        }
        break;
    case 4:
        gameSetUpStep[1] = 2;
        makeCursorMovable(0);
        removeCurrentDrawingItem();
        break;
    default:
        break;
    }
}

// .text:0x00085160 size:0x48 mapped:0x806C41F4
void fn_2_85160(void) {
    s16 remaining = currentDrawingItem->state - 1;

    currentDrawingItem->state = remaining;
    if (remaining == 0) {
        updateCharacterSelectProcessCode(0, 4);
        removeCurrentDrawingItem();
    }
}

// .text:0x0008515C size:0x4 mapped:0x806C41F0
void fn_2_8515C(void) {
    return;
}

// .text:0x00085108 size:0x54 mapped:0x806C419C
void loadStadiumScreen_maybe(void) {
    menuNumber[9] = menuNumber[8];
    menuNumber[0] = 5;
    menuNumber[8] = *(u16 *)(lbl_800FEF70 + 0x58);
    insertGraphicDrawingFunction(stadiumScreenAnimations_maybe, 0x3000);
}

// .text:0x00084FA8 size:0x160 mapped:0x806C403C
void stadiumScreenAnimations_maybe(void) {
    DrawingSceneStruct *node = currentDrawingItem;
    s32 i;
    s8 icon;

    addGraphicsElementToScene(node, (const UIRecordDescriptor *)lbl_2_data_2DC8C);
    for (i = 0; i < 6; i++) {
        if (superstarUnlocked[0xF5] == 0 && lbl_2_data_2DC84[i] == 1) {
            icon = 6;
        } else {
            icon = lbl_2_data_2DC84[i];
        }
        load_Icon(node, i + 6, 2, 0x1E, icon);
    }
    if (superstarUnlocked[0xF5] == 0 && lbl_2_data_2DC84[menuCursors[0x11]] == 1) {
        icon = 0x12;
    } else {
        icon = lbl_2_data_2DC84[menuCursors[0x11]];
    }
    if (menuCursors[0x11] != 0) {
        load_Icon(node, 0, 1, icon, 0x20);
    }
    lbl_803CBCD8[4] = 0;
    *(s16 *)((u8 *)node + 0x18) = 0;
    currentDrawingItem->func = fn_2_845A8;
}

// .text:0x000845A8 size:0xA00 mapped:0x806C363C
void fn_2_845A8(void) {
    TextScene *scene = (TextScene *)currentDrawingItem;
    u8 *tbl = lbl_2_data_2D998;
    s32 cursor;
    s32 count;
    s32 loop;
    s32 loopOff;
    s32 loopIcon;
    s32 t;
    s32 frame;
    s32 labelIcon;

    if (lbl_803CBCD8[4] != 0) {
        lbl_803CBCD8[4] = 0;
        tbl[0x954] = 0xFF;
        removeGraphicsElementFromScene((DrawingSceneStruct *)scene);
        removeCurrentDrawingItem();
        return;
    }

    tbl[0x955] = 0xFF;
    switch (gameSetUpStep[0x5D]) {
        case 0x24:
        if (gameSetUpStep[0x2B] == 0) {
            *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 0].object) + 0x5C) = 0xA0000;
            *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 1].object) + 0x5C) = 0xA0000;
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 0].object))[0x68] = 4;
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 1].object))[0x68] = 4;
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 2].object))[0x68] = 4;
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 3].object))[0x68] = 4;
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 5].object))[0x68] = 4;
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 4].object))[0x68] = 4;
            makeCursorUnmovable(0);
            gameSetUpStep[0x2B] = 1;
        }
        if (gameSetUpStep[0x2B] == 1) {
            count = (maybeCheckAndResetGrapicsElement(scene, 0, 0) != 0) + (maybeCheckAndResetGrapicsElement(scene, 1, 0) != 0) + (maybeCheckAndResetGrapicsElement(scene, 2, 0) != 0) + (maybeCheckAndResetGrapicsElement(scene, 3, 0) != 0) + (maybeCheckAndResetGrapicsElement(scene, 5, 0) != 0);
            if (count == 5) {
                tbl[0x954] = menuCursors[0x11];
                makeCursorMovable(0);
                gameSetUpStep[0x2B] = 2;
                tbl[0x954] = 0xFF;
                removeGraphicsElementFromScene((DrawingSceneStruct *)scene);
                removeCurrentDrawingItem();
            }
        }
        break;
        case 0x25:
        if (gameSetUpStep[0x2B] == 0) {
            *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 0].object) + 0x5C) = 0xA0000;
            *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 1].object) + 0x5C) = 0;
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 0].object))[0x68] = 1;
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 1].object))[0x68] = 0;
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 2].object))[0x68] = 4;
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 3].object))[0x68] = 4;
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 5].object))[0x68] = 4;
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 4].object))[0x68] = 1;
            makeCursorUnmovable(0);
            gameSetUpStep[0x2B] = 1;
        }
        if (gameSetUpStep[0x2B] == 1) {
            count = (maybeCheckAndResetGrapicsElement(scene, 0, 20) != 0) + (maybeCheckAndResetGrapicsElement(scene, 2, 0) != 0) + (maybeCheckAndResetGrapicsElement(scene, 5, 0) != 0) + (maybeCheckAndResetGrapicsElement(scene, 3, 0) != 0);
            if (count == 4) {
                tbl[0x954] = menuCursors[0x11];
                makeCursorMovable(0);
                gameSetUpStep[0x2B] = 2;
            }
        }
        break;
        case 0x26:
        if (gameSetUpStep[0x2B] == 0) {
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 0].object))[0x68] = 4;
            *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 1].object) + 0x5C) = 0;
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 1].object))[0x68] = 0;
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 2].object))[0x68] = 1;
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 5].object))[0x68] = 1;
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 3].object))[0x68] = 1;
            *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 4].object) + 0x5C) = 0x280000;
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 4].object))[0x68] = 4;
            makeCursorUnmovable(0);
            gameSetUpStep[0x2B] = 1;
        }
        if (gameSetUpStep[0x2B] == 1) {
            count = (maybeCheckAndResetGrapicsElement(scene, 0, 10) != 0) + (maybeCheckAndResetGrapicsElement(scene, 4, 20) != 0);
            if (count == 2) {
                cursor = menuCursors[0x11];
                if (superstarUnlocked[0xF5] == 0 && cursor != 0) {
                    cursor -= 1;
                }
                tbl[0x954] = cursor;
                makeCursorMovable(0);
                gameSetUpStep[0x2B] = 2;
            }
        }
        break;
        case 0x27:
        if (gameSetUpStep[0x2B] == 0) {
            *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 0].object) + 0x5C) = 0;
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 0].object))[0x68] = 1;
            *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 4].object) + 0x5C) = 0;
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 4].object))[0x68] = 1;
            *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 6].object) + 0x58) = (*(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 6].object) + 0x58) & ~0xFF) | 0xFF;
            *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 7].object) + 0x58) = (*(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 7].object) + 0x58) & ~0xFF) | 0xFF;
            *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 8].object) + 0x58) = (*(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 8].object) + 0x58) & ~0xFF) | 0xFF;
            *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 9].object) + 0x58) = (*(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 9].object) + 0x58) & ~0xFF) | 0xFF;
            *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 10].object) + 0x58) = (*(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 10].object) + 0x58) & ~0xFF) | 0xFF;
            *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 11].object) + 0x58) = (*(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 11].object) + 0x58) & ~0xFF) | 0xFF;
            cursor = menuCursors[0x11];
            *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + cursor + 6].object) + 0x5C) = 0x10000;
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + cursor + 6].object))[0x68] = 1;
            makeCursorUnmovable(0);
            gameSetUpStep[0x2B] = 1;
        }
        if (gameSetUpStep[0x2B] == 1) {
            count = (maybeCheckAndResetGrapicsElement(scene, 0, 10) != 0) + (maybeCheckAndResetGrapicsElement(scene, 4, 20) != 0);
            if (count == 2) {
                tbl[0x954] = menuCursors[0x11];
                makeCursorMovable(0);
                gameSetUpStep[0x2B] = 2;
            }
        }
        break;
        case 0x28:
        stadiumRandomRelated(scene, menuCursors[0x11]);
        break;
        case 0x31:
        if ((*(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 0].object) + 0x5C) >> 16) == 0x14) {
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 0].object))[0x68] = 1;
        }
        if ((*(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 0].object) + 0x5C) >> 16) == 0x1E) {
            lbl_803CBCD8[4] = 1;
            makeCursorMovable(0);
            gameSetUpStep[0x31] = 2;
        }
        break;
    default:
        break;
    }

    if (lbl_803CBCD8[4] != 0) {
        return;
    }
    if (gameSetUpStep[0x5D] == 0x25 || gameSetUpStep[0x5D] == 0x24) {
        return;
    }
    if (menuControlVariables->currentScreen == 0xD) {
        return;
    }
    if (lbl_2_bss_F468[0x58] != 0) {
        return;
    }
    cursor = menuCursors[0x11];
    if ((s8)tbl[0x954] != cursor) {
        return;
    }
    if ((s8)tbl[0x955] != -1) {
        return;
    }
    if (superstarUnlocked[0xF5] == 0 && tbl[0x2EC + cursor] == 1) {
        load_Icon(scene, 0, 1, 0x20, 0x12);
        load_Icon(scene, 1, 1, 0x20, 0x12);
        return;
    }
    for (loop = 0, loopOff = 0, loopIcon = 0; loop < 3; loop++, loopIcon += 6, loopOff += 0x64) {
        if (*(u16 *)((u8 *)scene + 0x18) == loopOff) {
            t = tbl[0x2EC + cursor];
            frame = t + loopIcon;
            if (lbl_2_bss_ABC0[0] != 0) {
                lbl_2_bss_ABC0[0] = 0;
                labelIcon = t + 0xC;
            } else if (loop == 0) {
                labelIcon = t;
            } else {
                labelIcon = t + (loop - 1) * 6;
            }
            *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 0].object) + 0x5C) = 0;
            *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 1].object) + 0x5C) = 0xA0000;
            load_Icon(scene, 0, 1, 0x20, frame);
            load_Icon(scene, 1, 1, 0x20, labelIcon);
            *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 0].object) + 0x58) = (*(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 0].object) + 0x58) & ~0xFF) | 0xFF;
            *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 1].object) + 0x58) = (*(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 1].object) + 0x58) & ~0xFF) | 0xFF;
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 0].object))[0x68] = 1;
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 1].object))[0x68] = 4;
        }
    }
    count = (maybeCheckAndResetGrapicsElement(scene, 0, 10) != 0);
    count = (maybeCheckAndResetGrapicsElement(scene, 1, 0) != 0);
    *(u16 *)((u8 *)scene + 0x18) += 1;
    if (*(u16 *)((u8 *)scene + 0x18) > 0x12C) {
        *(u16 *)((u8 *)scene + 0x18) = 0;
        lbl_2_bss_ABC0[0] = 1;
    }
}

// .text:0x00084388 size:0x220 mapped:0x806C341C
void fn_2_84388(TextScene *scene) {
    BOOL a;
    BOOL b;

    if (gameSetUpStep[0x2B] == 0) {
    *(u32 *)((u8 *)graphicsRelatedArray[scene->firstHandle].object + 0x5C) = 0;
    ((u8 *)graphicsRelatedArray[scene->firstHandle].object)[0x68] = 1;
    *(u32 *)((u8 *)graphicsRelatedArray[scene->firstHandle + 4].object + 0x5C) = 0;
    ((u8 *)graphicsRelatedArray[scene->firstHandle + 4].object)[0x68] = 1;
    *(u32 *)((u8 *)graphicsRelatedArray[scene->firstHandle + 6].object + 0x58) = (*(u32 *)((u8 *)graphicsRelatedArray[scene->firstHandle + 6].object + 0x58) & ~0xFF) | 0xFF;
    *(u32 *)((u8 *)graphicsRelatedArray[scene->firstHandle + 7].object + 0x58) = (*(u32 *)((u8 *)graphicsRelatedArray[scene->firstHandle + 7].object + 0x58) & ~0xFF) | 0xFF;
    *(u32 *)((u8 *)graphicsRelatedArray[scene->firstHandle + 8].object + 0x58) = (*(u32 *)((u8 *)graphicsRelatedArray[scene->firstHandle + 8].object + 0x58) & ~0xFF) | 0xFF;
    *(u32 *)((u8 *)graphicsRelatedArray[scene->firstHandle + 9].object + 0x58) = (*(u32 *)((u8 *)graphicsRelatedArray[scene->firstHandle + 9].object + 0x58) & ~0xFF) | 0xFF;
    *(u32 *)((u8 *)graphicsRelatedArray[scene->firstHandle + 10].object + 0x58) = (*(u32 *)((u8 *)graphicsRelatedArray[scene->firstHandle + 10].object + 0x58) & ~0xFF) | 0xFF;
    *(u32 *)((u8 *)graphicsRelatedArray[scene->firstHandle + 11].object + 0x58) = (*(u32 *)((u8 *)graphicsRelatedArray[scene->firstHandle + 11].object + 0x58) & ~0xFF) | 0xFF;
    *(u32 *)((u8 *)graphicsRelatedArray[scene->firstHandle + menuCursors[0x11] + 6].object + 0x5C) = 1;
    ((u8 *)graphicsRelatedArray[scene->firstHandle + menuCursors[0x11] + 6].object)[0x68] = 1;
        makeCursorUnmovable(0);
        gameSetUpStep[0x2B] = 1;
    }

    if (gameSetUpStep[0x2B] != 1) {
        return;
    }
    a = maybeCheckAndResetGrapicsElement(scene, 0, 0xA) != 0;
    b = maybeCheckAndResetGrapicsElement(scene, 4, 0x14) != 0;
    if (a && b) {
        lbl_2_data_2E2EC[0] = menuCursors[0x11];
        makeCursorMovable(0);
        gameSetUpStep[0x2B] = 2;
    }
}

// .text:0x00084194 size:0x1F4 mapped:0x806C3228
void fn_2_84194(TextScene *scene) {
    s32 count;

    if (gameSetUpStep[0x2B] == 0) {
        *(u32 *)((u8 *)graphicsRelatedArray[scene->firstHandle].object + 0x5C) = 0xA0000;
        *(u32 *)((u8 *)graphicsRelatedArray[scene->firstHandle + 1].object + 0x5C) = 0xA0000;
        ((u8 *)graphicsRelatedArray[scene->firstHandle].object)[0x68] = 4;
        ((u8 *)graphicsRelatedArray[scene->firstHandle + 1].object)[0x68] = 4;
        ((u8 *)graphicsRelatedArray[scene->firstHandle + 2].object)[0x68] = 4;
        ((u8 *)graphicsRelatedArray[scene->firstHandle + 3].object)[0x68] = 4;
        ((u8 *)graphicsRelatedArray[scene->firstHandle + 5].object)[0x68] = 4;
        ((u8 *)graphicsRelatedArray[scene->firstHandle + 4].object)[0x68] = 4;
        makeCursorUnmovable(0);
        gameSetUpStep[0x2B] = 1;
    }

    if (gameSetUpStep[0x2B] != 1) {
        return;
    }
    count = maybeCheckAndResetGrapicsElement(scene, 0, 0) != 0;
    count += maybeCheckAndResetGrapicsElement(scene, 1, 0) != 0;
    count += maybeCheckAndResetGrapicsElement(scene, 2, 0) != 0;
    count += maybeCheckAndResetGrapicsElement(scene, 3, 0) != 0;
    count += maybeCheckAndResetGrapicsElement(scene, 5, 0) != 0;
    if (count == 5) {
        lbl_2_data_2E2EC[0] = menuCursors[0x11];
        makeCursorMovable(0);
        gameSetUpStep[0x2B] = 2;
        lbl_2_data_2E2EC[0] = 0xFF;
        removeGraphicsElementFromScene((DrawingSceneStruct *)scene);
        removeCurrentDrawingItem();
    }
}

// .text:0x00083B34 size:0x660 mapped:0x806C2BC8
void stadiumRandomRelated(TextScene *scene, s32 arg) {
    u8 *tbl = lbl_2_data_2D998;
    s32 cursor;
    s32 icon;
    s32 flag;
    s32 count;
    s32 need;

    if (stadiumStepIsClear(gameSetUpStep[0x2B])) {
        ((u8 *)(graphicsRelatedArray[scene->firstHandle + 6].object))[0x68] = 0;
        *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 6].object) + 0x5C) = 0;
        ((u8 *)(graphicsRelatedArray[scene->firstHandle + 7].object))[0x68] = 0;
        *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 7].object) + 0x5C) = 0;
        ((u8 *)(graphicsRelatedArray[scene->firstHandle + 8].object))[0x68] = 0;
        *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 8].object) + 0x5C) = 0;
        ((u8 *)(graphicsRelatedArray[scene->firstHandle + 9].object))[0x68] = 0;
        *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 9].object) + 0x5C) = 0;
        ((u8 *)(graphicsRelatedArray[scene->firstHandle + 10].object))[0x68] = 0;
        *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 10].object) + 0x5C) = 0;
        ((u8 *)(graphicsRelatedArray[scene->firstHandle + 11].object))[0x68] = 0;
        *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 11].object) + 0x5C) = 0;
        if (lbl_803CBCD8[0] == 0 || lbl_803CBCD8[1] == 0) {
            *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 0].object) + 0x58) = (*(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 0].object) + 0x58) & ~0xFF) | 0xFF;
            *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 1].object) + 0x58) = (*(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 1].object) + 0x58) & ~0xFF) | 0xFF;
            *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 0].object) + 0x5C) = 0;
            *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 1].object) + 0x5C) = 0xA0000;
            cursor = menuCursors[0x11];
            flag = tbl[0x2EC + cursor] == 1 && superstarUnlocked[0xF5] == 0;
            if (lbl_803CBCD8[0] != 0) {
                load_Icon(scene, 0, 1, 0x20, tbl[0x2EC + arg]);
                if ((s8)tbl[0x954] != -1) {
                    load_Icon(scene, 1, 1, 0x20, tbl[0x2EC + (s8)tbl[0x954]]);
                } else {
                    load_Icon(scene, 1, 1, 0x20, tbl[0x2EC + arg]);
                }
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 0].object))[0x68] = 1;
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 1].object))[0x68] = 1;
                arg = (s8)tbl[0x954];
            } else {
                load_Icon(scene, 0, 1, 0x20, flag ? 0x12 : tbl[0x2EC + arg]);
                if ((s8)tbl[0x954] != -1) {
                    icon = tbl[0x2EC + (s8)tbl[0x954]];
                    if (icon == 1 && superstarUnlocked[0xF5] == 0) {
                        icon = 0x12;
                    }
                    load_Icon(scene, 1, 1, 0x20, icon);
                } else {
                    load_Icon(scene, 1, 1, 0x20, flag ? 0x12 : tbl[0x2EC + arg]);
                }
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 0].object))[0x68] = 1;
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 1].object))[0x68] = 4;
            }
        }

            *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + arg + 6].object) + 0x5C) = 0x10000;
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + arg + 6].object))[0x68] = 1;
        cursor = menuCursors[0x11];
        flag = tbl[0x2EC + cursor] == 1 && superstarUnlocked[0xF5] == 0;
        icon = flag ? 6 : tbl[0x2EC + arg];
            *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 2].object) + 0x5C) = 0;
        load_Icon(scene, 2, 1, 0x22, icon);
        flag = tbl[0x2EC + cursor] == 1 && superstarUnlocked[0xF5] == 0;
        icon = flag ? 6 : tbl[0x2EC + arg];
            *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 3].object) + 0x5C) = 0;
        load_Icon(scene, 3, 1, 0x25, icon);
        load_Icon(scene, 3, 3, 0x24, icon);
            ((u8 *)(graphicsRelatedArray[scene->firstHandle + 3].object))[0x68] = 1;
        gameSetUpStep[0x2B] = 1;
    }

    if (gameSetUpStep[0x2B] == 1) {
        if (lbl_803CBCD8[1] == 0) {
            count = maybeCheckAndResetGrapicsElement(scene, 0, 0xA) != 0;
            count += maybeCheckAndResetGrapicsElement(scene, 1, 0) != 0;
            count += maybeCheckAndResetGrapicsElement(scene, arg + 6, 4) != 0;
            need = 3;
        } else {
            count = 0;
            need = 0;
        }
        if (count == need) {
            tbl[0x955] = tbl[0x954];
            tbl[0x954] = arg;
            *(u16 *)((u8 *)scene + 0x18) = 0;
            if ((s8)lbl_803CBCD8[1] < 0) {
                lbl_803CBCD8[1] = 0;
                lbl_803CBCD8[0] = 0;
            }
            gameSetUpStep[0x2B] = 2;
            gameSetUpStep[0x5D] = 0;
        }
    }
}

// .text:0x00083974 size:0x1C0 mapped:0x806C2A08
void fn_2_83974(TextScene *scene) {
    s32 count;

    if (gameSetUpStep[0x2B] == 0) {
        *(u32 *)((u8 *)graphicsRelatedArray[scene->firstHandle].object + 0x5C) = 0xA0000;
        *(u32 *)((u8 *)graphicsRelatedArray[scene->firstHandle + 1].object + 0x5C) = 0;
        ((u8 *)graphicsRelatedArray[scene->firstHandle].object)[0x68] = 1;
        ((u8 *)graphicsRelatedArray[scene->firstHandle + 1].object)[0x68] = 0;
        ((u8 *)graphicsRelatedArray[scene->firstHandle + 2].object)[0x68] = 4;
        ((u8 *)graphicsRelatedArray[scene->firstHandle + 3].object)[0x68] = 4;
        ((u8 *)graphicsRelatedArray[scene->firstHandle + 5].object)[0x68] = 4;
        ((u8 *)graphicsRelatedArray[scene->firstHandle + 4].object)[0x68] = 1;
        makeCursorUnmovable(0);
        gameSetUpStep[0x2B] = 1;
    }

    if (gameSetUpStep[0x2B] != 1) {
        return;
    }
    count = maybeCheckAndResetGrapicsElement(scene, 0, 0x14) != 0;
    count += maybeCheckAndResetGrapicsElement(scene, 2, 0) != 0;
    count += maybeCheckAndResetGrapicsElement(scene, 5, 0) != 0;
    count += maybeCheckAndResetGrapicsElement(scene, 3, 0) != 0;
    if (count == 4) {
        lbl_2_data_2E2EC[0] = menuCursors[0x11];
        makeCursorMovable(0);
        gameSetUpStep[0x2B] = 2;
    }
}

// .text:0x000837D8 size:0x19C mapped:0x806C286C
void fn_2_837D8(TextScene *scene) {
    BOOL a;
    BOOL b;

    if (gameSetUpStep[0x2B] == 0) {
        ((u8 *)graphicsRelatedArray[scene->firstHandle].object)[0x68] = 4;
        *(u32 *)((u8 *)graphicsRelatedArray[scene->firstHandle + 1].object + 0x5C) = 0;
        ((u8 *)graphicsRelatedArray[scene->firstHandle + 1].object)[0x68] = 0;
        ((u8 *)graphicsRelatedArray[scene->firstHandle + 2].object)[0x68] = 1;
        ((u8 *)graphicsRelatedArray[scene->firstHandle + 5].object)[0x68] = 1;
        ((u8 *)graphicsRelatedArray[scene->firstHandle + 3].object)[0x68] = 1;
        *(u32 *)((u8 *)graphicsRelatedArray[scene->firstHandle + 4].object + 0x5C) = 0x280000;
        ((u8 *)graphicsRelatedArray[scene->firstHandle + 4].object)[0x68] = 4;
        makeCursorUnmovable(0);
        gameSetUpStep[0x2B] = 1;
    }

    if (gameSetUpStep[0x2B] != 1) {
        return;
    }
    a = maybeCheckAndResetGrapicsElement(scene, 0, 0xA) != 0;
    b = maybeCheckAndResetGrapicsElement(scene, 4, 0x14) != 0;
    if (a && b) {
        s32 cursor = menuCursors[0x11];

        if (superstarUnlocked[0xF5] == 0 && cursor != 0) {
            cursor -= 1;
        }
        lbl_2_data_2E2EC[0] = cursor;
        makeCursorMovable(0);
        gameSetUpStep[0x2B] = 2;
    }
}

// .text:0x00083744 size:0x94 mapped:0x806C27D8
void fn_2_83744(TextScene *scene) {
    GraphicsArrayEntry *first = &graphicsRelatedArray[scene->firstHandle];

    if ((((UIRecord *)first->object)->frame >> 16) == 0x14) {
        ((UIRecord *)first->object)->playMode = UI_PLAY_FORWARD;
    }
    first = &graphicsRelatedArray[scene->firstHandle];
    if ((((UIRecord *)first->object)->frame >> 16) == 0x1E) {
        lbl_803CBCD8[4] = TRUE;
        makeCursorMovable(0);
        gameSetUpStep[0x31] = 2;
    }
}

// .text:0x000836A4 size:0xA0 mapped:0x806C2738
void fn_2_836A4(void) {
    if (cardCheck[0x47] != 0) {
        insertGraphicDrawingFunction(fn_80053FE8, 0);
    }
    menuNumber[9] = menuNumber[8];
    menuNumber[0] = 0xC;
    menuNumber[8] = *(u16 *)(lbl_800FEF70 + 0xC8);
    if (menuControlVariables->previousScreen != 9) {
        insertGraphicDrawingFunction(fn_2_82DE8, 0x3000);
    }
    insertGraphicDrawingFunction(fn_2_834F0, 0x3000);
}

// .text:0x000834F0 size:0x1B4 mapped:0x806C2584
void fn_2_834F0(void) {
    DrawingSceneStruct *node = currentDrawingItem;
    TextScene *scene = (TextScene *)node;
    s32 i;

    addGraphicsElementToScene(node, (const UIRecordDescriptor *)lbl_2_data_2E02C);
    for (i = 0; i < 4; i++) {
        if (lbl_2_bss_F468[0x57] < i) {
            load_Icon(node, i + 3, 1, 0x6B, 4);
        } else {
            load_Icon(node, i + 3, 1, 0x6B, i);
        }
    }

    *(u32 *)((u8 *)graphicsRelatedArray[scene->firstHandle + 12].object + 0x5C) = 0;
    if (superstarUnlocked[0xF4] != 0) {
        *(u16 *)((u8 *)graphicsRelatedArray[scene->firstHandle + 1].object + 0x64) = 0x22;
        *(u32 *)((u8 *)graphicsRelatedArray[scene->firstHandle + 11].object + 0x5C) = 0x40000;
    } else {
        *(u16 *)((u8 *)graphicsRelatedArray[scene->firstHandle + 1].object + 0x64) = 0x21;
        *(u32 *)((u8 *)graphicsRelatedArray[scene->firstHandle + 11].object + 0x5C) = 0;
    }
    if (superstarUnlocked[0xE4] != 0) {
        *(u32 *)((u8 *)graphicsRelatedArray[scene->firstHandle + 9].object + 0x54) |= 2;
        ((u8 *)graphicsRelatedArray[scene->firstHandle + 9].object)[0x68] = 1;
        load_Icon(node, 9, 1, 0x27, 0);
    }
    currentDrawingItem->func = fn_2_82EC0;
}

// .text:0x00082EC0 size:0x630 mapped:0x806C1F54
void fn_2_82EC0(void) {
    TextScene *scene = (TextScene *)currentDrawingItem;
    s32 cursor = menuCursors[0x11];
    s32 arg = lbl_803CBBC4[1];
    s32 st = lbl_803CBBC4[0];

    if (st == 0x5F) {
        if ((*(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + cursor + 3].object) + 0x5C) >> 16) >= 0x37) {
        *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + cursor + 3].object) + 0x5C) = 0x50000;
        ((u8 *)(graphicsRelatedArray[scene->firstHandle + cursor + 3].object))[0x68] = 1;
        }
        if ((*(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 0].object) + 0x5C) >> 16) >= 0x23) {
        *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 0].object) + 0x5C) = 0x230000;
        ((u8 *)(graphicsRelatedArray[scene->firstHandle + 0].object))[0x68] = 0;
        }
    } else if (st > 0x5F) {
        if (st == 0x61) {
        if (lbl_803CBBC4[2] == 0) {
        ((u8 *)(graphicsRelatedArray[scene->firstHandle + 2].object))[0x68] = 4;
        *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 3].object) + 0x5C) = 0;
        ((u8 *)(graphicsRelatedArray[scene->firstHandle + 3].object))[0x68] = 0;
        *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 4].object) + 0x5C) = 0;
        ((u8 *)(graphicsRelatedArray[scene->firstHandle + 4].object))[0x68] = 0;
        *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 5].object) + 0x5C) = 0;
        ((u8 *)(graphicsRelatedArray[scene->firstHandle + 5].object))[0x68] = 0;
        *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 6].object) + 0x5C) = 0;
        ((u8 *)(graphicsRelatedArray[scene->firstHandle + 6].object))[0x68] = 0;
            lbl_803CBBC4[2] = 1;
            lbl_803CBBC4[3] = 1;
        }
    if (lbl_803CBBC4[3] == 1 && maybeCheckAndResetGrapicsElement(scene, 2, 0) == 1) {
        lbl_803CBBC4[0] = 0;
        lbl_803CBBC4[2] = 0;
        lbl_803CBBC4[3] = 0;
        lbl_803CBBC4[4] = 1;
    }
        } else if (st == 0x60) {
        if (lbl_803CBBC4[2] == 0) {
        *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 0].object) + 0x5C) = 0x230000;
        ((u8 *)(graphicsRelatedArray[scene->firstHandle + 0].object))[0x68] = 1;
        ((u8 *)(graphicsRelatedArray[scene->firstHandle + 1].object))[0x68] = 4;
        *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + cursor + 3].object) + 0x5C) = 0x370000;
        ((u8 *)(graphicsRelatedArray[scene->firstHandle + cursor + 3].object))[0x68] = 1;
        ((u8 *)(graphicsRelatedArray[scene->firstHandle + 7].object))[0x68] = 4;
        ((u8 *)(graphicsRelatedArray[scene->firstHandle + 8].object))[0x68] = 4;
        ((u8 *)(graphicsRelatedArray[scene->firstHandle + 10].object))[0x68] = 4;
        ((u8 *)(graphicsRelatedArray[scene->firstHandle + 9].object))[0x68] = 4;
            lbl_803CBBC4[2] = 1;
            lbl_803CBBC4[3] = 1;
        }
    if (lbl_803CBBC4[3] == 1 && maybeCheckAndResetGrapicsElement(scene, cursor + 3, 0x46) == 1) {
        lbl_803CBBC4[0] = 0x61;
        lbl_803CBBC4[2] = 0;
        lbl_803CBBC4[3] = 0;
    }
        }
    } else if (st == 0x5D) {
        if (lbl_803CBBC4[2] == 0) {
        ((u8 *)(graphicsRelatedArray[scene->firstHandle + 0].object))[0x68] = 1;
        ((u8 *)(graphicsRelatedArray[scene->firstHandle + 1].object))[0x68] = 1;
        ((u8 *)(graphicsRelatedArray[scene->firstHandle + 2].object))[0x68] = 1;
        ((u8 *)(graphicsRelatedArray[scene->firstHandle + cursor + 3].object))[0x68] = 1;
            lbl_803CBBC4[2] = 1;
            lbl_803CBBC4[3] = 1;
        }
    if (lbl_803CBBC4[3] == 1) {
        lbl_803CBBC4[0] = 0x5F;
        lbl_803CBBC4[2] = 0;
        lbl_803CBBC4[3] = 0;
    }
    } else if (st == 0x5E) {
        if (lbl_803CBBC4[2] == 0) {
        ((u8 *)(graphicsRelatedArray[scene->firstHandle + cursor + 3].object))[0x68] = 1;
            if (lbl_2_bss_F468[0x57] < cursor) {
        *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 12].object) + 0x5C) = 0x80000;
        *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 11].object) + 0x5C) = 0x80000;
            } else {
        *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 12].object) + 0x5C) = cursor << 16;
                if (superstarUnlocked[0xF4] == 0) {
        *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 11].object) + 0x5C) = cursor << 16;
                } else {
        *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + 11].object) + 0x5C) = (cursor + 4) << 16;
                }
            }
            if (superstarUnlocked[0xE4 + cursor] == 0) {
                load_Icon(scene, 9, 1, 0x27, 4);
            } else {
                load_Icon(scene, 9, 1, 0x27, cursor);
            }
            if (arg != -1) {
        *(u32 *)((u8 *)(graphicsRelatedArray[scene->firstHandle + arg + 3].object) + 0x5C) = 0;
        ((u8 *)(graphicsRelatedArray[scene->firstHandle + arg + 3].object))[0x68] = 0;
            }
            lbl_803CBBC4[2] = 1;
            lbl_803CBBC4[3] = 1;
        }
    if (lbl_803CBBC4[3] == 1) {
        lbl_803CBBC4[0] = 0x5F;
        lbl_803CBBC4[2] = 0;
        lbl_803CBBC4[3] = 0;
    }
    }
    if (lbl_803CBBC4[4] != 0 && lbl_803CBBC4[3] != 1) {
        lbl_803CBBC4[4] = 0;
        lbl_803CBBC4[5] = 1;
        removeGraphicsElementFromScene((DrawingSceneStruct *)scene);
        removeCurrentDrawingItem();
    }
}

// .text:0x00082E58 size:0x68 mapped:0x806C1EEC
void relatedToTeamSelection4(void) {
    if (menuControlVariables->previousScreen != 0xB &&
        g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
        insertGraphicDrawingFunction(fn_2_82DE8, 0x3000);
    }
    insertGraphicDrawingFunction(relatedToTeamSelection3, 0x3000);
}

// .text:0x00082DE8 size:0x70 mapped:0x806C1E7C
void fn_2_82DE8(void) {
    *(DrawingSceneStruct **)((u8 *)&Static_Stats_Tables + 0x4748) = currentDrawingItem;
    ((u8 *)&Static_Stats_Tables)[0x48AF] = 0;
    g_MatchInfo.unk37 = 0;
    g_MatchInfo.unk38 = 0;
    addGraphicsElementToScene(currentDrawingItem, (const UIRecordDescriptor *)lbl_2_data_2B4DC);
    currentDrawingItem->func = fn_2_82CF0;
}

// .text:0x00082CF0 size:0xF8 mapped:0x806C1D84
void fn_2_82CF0(void) {
    DrawingSceneStruct *node = *(DrawingSceneStruct **)((u8 *)&Static_Stats_Tables + 0x4748);
    TextScene *scene = (TextScene *)node;

    if (g_MatchInfo.unk36 != 0) {
        *(u32 *)((u8 *)graphicsRelatedArray[scene->firstHandle].object + 0x5C) = 0;
        *(u32 *)((u8 *)graphicsRelatedArray[scene->firstHandle + 1].object + 0x5C) = 0x280000;
        *(u16 *)((u8 *)graphicsRelatedArray[scene->firstHandle + 2].object + 0x64) = g_MatchInfo.unk38 + 0x123;
        *(u16 *)((u8 *)graphicsRelatedArray[scene->firstHandle + 3].object + 0x64) = g_MatchInfo.unk37 + 0x123;
        ((u8 *)graphicsRelatedArray[scene->firstHandle].object)[0x68] = 1;
        ((u8 *)graphicsRelatedArray[scene->firstHandle + 1].object)[0x68] = 4;
        g_MatchInfo.unk36 = 0;
    }
    if (((u8 *)&Static_Stats_Tables)[0x48AF] != 0) {
        ((u8 *)&Static_Stats_Tables)[0x48AF] = 0;
        removeGraphicsElementFromScene(node);
        removeCurrentDrawingItem();
    }
}
