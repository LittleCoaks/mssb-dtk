#include "menus/text_744C8.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x800363d8.h"
#include "Unknown/File_0x800625a4.h"
#include "Unknown/File_0x80062674.h"
#include "Unknown/orderchange.h"
#include "Unknown/File_0x800204cc.h"
#include "text/text.h"
#include "menus/text_00110.h"
#include "game/character_stats.h"
#include "Unknown/mb_subfunc.h"
#include "PowerPC_EABI_Support/Runtime/__mem.h"
#include "Unknown/File_0x80034cec.h"

extern u8 gameSetUpStep[0x64];
extern int menuCursors[0x16];
extern int mainMenuCursorShown;
extern u8 Static_Stats_Tables[];
extern u8 lbl_8037169C[];
extern u8 superstarUnlocked[];
extern u8 cursorPositions[];
extern u8 lbl_2_bss_F468[];
extern Text00110Ctl *menuControlVariables;
extern u8 challengeCaptainCharIDArray[];
extern u8 lbl_2_data_2B3A4[];
extern u8 g_d_GameSettings[];
extern s32 lbl_2_bss_A844;
void fn_2_73CBC(DrawingSceneStruct *node);
void fn_2_73EFC(DrawingSceneStruct *node);
extern u8 mapCaptainCursorPositionToCharID[];
extern UIRecordDescriptor lbl_2_data_2D33C[];
void load_Icon(void *scene, int handle, u32 part, u32 element, int frame);
s32 fn_80036214(MenuScene *scene, s32 arg1, s32 arg2, s32 size);
s32 fn_2_8794(s32 arg0, s32 arg1);

static TextGraphicsObject *gfxObject(MenuScene *scene, s32 index) {
    return graphicsRelatedArray[scene->firstHandle + index].object;
}


static TextGraphicsObject *gfxNodeObject(DrawingSceneStruct *node, s32 index) {
    return graphicsRelatedArray[*(u16 *)((u8 *)node + 0x14) + index].object;
}

static void gfxNodeSetU32(DrawingSceneStruct *node, s32 index, u32 value) {
    *(u32 *)((u8 *)gfxNodeObject(node, index) + 0x5C) = value;
}

static void gfxNodeSetU8(DrawingSceneStruct *node, s32 index, u8 value) {
    *(u8 *)((u8 *)gfxNodeObject(node, index) + 0x68) = value;
}

// .text:0x00076650 size:0x224 mapped:0x806B56E4
void fn_2_76650(MenuScene *scene, u8 team, u32 mask) {
    s32 list[6];
    s32 n = 0;
    s32 i;
    s32 a;
    s32 b;

    memset(list, -1, 2);
    for (i = 0; i < 14; i++) {
        if (mask & (1 << i)) {
            if (i != 0) {
                list[n++] = i;
            }
        }
    }
    a = list[0] - 1;
    b = list[1] - 1;
    if (a < 0) {
        a = 12;
    }
    if (b < 0) {
        b = 12;
    }
    *(u32 *)((u8 *)gfxObject(scene, team + 0xCE) + 0x5C) = (u32)a << 16;
    *(u32 *)((u8 *)gfxObject(scene, team + 0xD0) + 0x5C) = (u32)b << 16;
}

// .text:0x0007664C size:0x4 mapped:0x806B56E0
void fn_2_7664C(void) {
    return;
}

// .text:0x0007630C size:0x340 mapped:0x806B53A0
void fn_2_7630C(MenuScene *scene, u8 arg) {
    u8 slot = 0;
    u8 team;
    u8 cursorChar;
    u8 posChar;
    s32 cursorDiv;
    s32 cursorMod;
    s32 posDiv;
    s32 posMod;
    u8 iconP;
    u8 iconQ;

    if (g_d_GameSettings[0x10] != 0) {
        slot = arg;
    }
    team = gameSetUpStep[0x59 + slot];
    cursorChar = mapCaptainCursorPositionToCharID[menuCursors[4 + team]];
    posChar = mapCaptainCursorPositionToCharID[cursorPositions[team]];
    cursorDiv = cursorChar / 9;
    cursorMod = cursorChar % 9;
    posDiv = posChar / 9;
    posMod = posChar % 9;
    iconP = lbl_2_data_2B3A4[Static_Stats_Tables[0x34 + cursorDiv * 1440 + cursorMod * 160]];
    iconQ = lbl_2_data_2B3A4[Static_Stats_Tables[0x34 + posDiv * 1440 + posMod * 160]];

    *(u32 *)((u8 *)gfxObject(scene, team + 0x82) + 0x5C) = (u32)iconP << 16;
    *(u32 *)((u8 *)gfxObject(scene, team + 0x85) + 0x5C) = 0xA0000;
    *(u32 *)((u8 *)gfxObject(scene, team + 0x87) + 0x5C) = 0xA0000;
    *(u8 *)((u8 *)gfxObject(scene, team + 0x85) + 0x68) = 0;
    *(u8 *)((u8 *)gfxObject(scene, team + 0x87) + 0x68) = 0;
    load_Icon(scene, team + 0x89, 1, 3, iconP);
    load_Icon(scene, team + 0x8B, 1, 3, iconQ);
    *(u32 *)((u8 *)gfxObject(scene, team + 0x7E) + 0x5C) = (u32)iconP << 16;
    gfxObject(scene, team + 0x1A)->flags |= 2;
    *(u8 *)((u8 *)gfxObject(scene, team + 0x1A) + 0x68) = 1;
    *(u32 *)((u8 *)gfxObject(scene, team + 0x80) + 0x5C) = 0;
    *(u32 *)((u8 *)gfxObject(scene, team + 0x89) + 0x5C) = 0;
    *(u32 *)((u8 *)gfxObject(scene, team + 0x8B) + 0x5C) = 0xA0000;
    *(u32 *)((u8 *)gfxObject(scene, team + 0x78) + 0x5C) = 0;
    *(u32 *)((u8 *)gfxObject(scene, team + 0x7C) + 0x5C) = 0;
    *(u8 *)((u8 *)gfxObject(scene, team + 0x80) + 0x68) = 1;
    *(u8 *)((u8 *)gfxObject(scene, team + 0x89) + 0x68) = 1;
    *(u8 *)((u8 *)gfxObject(scene, team + 0x8B) + 0x68) = iconP;
    *(u8 *)((u8 *)gfxObject(scene, team + 0x78) + 0x68) = 1;
    *(u8 *)((u8 *)gfxObject(scene, team + 0x7C) + 0x68) = 1;
}

// .text:0x000760CC size:0x240 mapped:0x806B5160
void fn_2_760CC(MenuScene *scene) {
    s32 superstar = superstarUnlocked[0xF4];
    u8 a = challengeCaptainCharIDArray[superstar * 6 + menuCursors[4]];
    u8 b = challengeCaptainCharIDArray[superstar * 6 + cursorPositions[0]];
    s32 aDiv = a / 9;
    s32 aMod = a % 9;
    s32 bDiv = b / 9;
    s32 bMod = b % 9;
    u8 iconP = lbl_2_data_2B3A4[Static_Stats_Tables[0x34 + aDiv * 1440 + aMod * 160]];
    u8 iconQ = lbl_2_data_2B3A4[Static_Stats_Tables[0x34 + bDiv * 1440 + bMod * 160]];

    *(u32 *)((u8 *)gfxObject(scene, 0x82) + 0x5C) = (u32)iconP << 16;
    load_Icon(scene, 0x89, 1, 3, iconP);
    load_Icon(scene, 0x8B, 1, 3, iconQ);
    *(u32 *)((u8 *)gfxObject(scene, 0x7E) + 0x5C) = (u32)iconP << 16;
    *(u32 *)((u8 *)gfxObject(scene, 0x80) + 0x5C) = 0;
    *(u32 *)((u8 *)gfxObject(scene, 0x89) + 0x5C) = 0;
    *(u32 *)((u8 *)gfxObject(scene, 0x8B) + 0x5C) = 0xA0000;
    *(u32 *)((u8 *)gfxObject(scene, 0x78) + 0x5C) = 0;
    *(u32 *)((u8 *)gfxObject(scene, 0x7C) + 0x5C) = 0;
    *(u8 *)((u8 *)gfxObject(scene, 0x80) + 0x68) = 1;
    *(u8 *)((u8 *)gfxObject(scene, 0x89) + 0x68) = 1;
    *(u8 *)((u8 *)gfxObject(scene, 0x8B) + 0x68) = 4;
    *(u8 *)((u8 *)gfxObject(scene, 0x78) + 0x68) = 1;
    *(u8 *)((u8 *)gfxObject(scene, 0x7C) + 0x68) = 1;
}

// .text:0x0007609C size:0x30 mapped:0x806B5130
void fn_2_7609C(u8 arg0, u8 arg1) {
    if (arg1 == 0) {
        fn_2_8794(arg0, 0);
    }
}

// .text:0x00076098 size:0x4 mapped:0x806B512C
void fn_2_76098(void) {
    return;
}

// .text:0x00075BE4 size:0x4B4 mapped:0x806B4C78
void teamSelectionSetChemStars(MenuScene *scene, u8 team) {
    u8 *picks = &cursorPositions[team * 9];
    u32 teamWord = *(u32 *)(Static_Stats_Tables + team * 4 + 0x46E0);
    s32 sum = 0;
    s32 count = 0;
    s32 average = 0;
    s32 stars;
    s32 i;

    for (i = 0; i < 9; i++) {
        u8 value = picks[0x26 + i];

        if (value != 0 && (s32)(s8)picks[2 + i] != (s32)teamWord) {
            sum += value;
            count++;
        }
    }
    if (count != 0) {
        average = sum / count;
    }
    if (average >= 70) {
        stars = 5;
    } else if (average >= 55) {
        stars = 4;
    } else if (average >= 35) {
        stars = 3;
    } else if (average >= 15) {
        stars = 2;
    } else if (average > 0) {
        stars = 1;
    } else {
        stars = 0;
    }
    Static_Stats_Tables[0x470F + team] = (u8)stars;

    for (i = 0; i < 5; i++) {
        u8 *obj = (u8 *)gfxObject(scene, team * 5 + 0x6E + i);

        if ((*(u32 *)(obj + 0x5C) >> 16) == 0x1E) {
            obj[0x68] = 1;
        }
    }
    for (i = 0; i < stars; i++) {
        u8 *obj = (u8 *)gfxObject(scene, team * 5 + 0x6E + i);

        *(u32 *)(obj + 0x5C) = 0;
        obj[0x68] = 1;
    }
}

// .text:0x00075B58 size:0x8C mapped:0x806B4BEC
BOOL fn_2_75B58(MenuScene *scene, u8 team) {
    int total = 0;
    int hits = 0;
    int i;
    int base = team * 5;
    u8 count = Static_Stats_Tables[team + 0x470F];

    for (i = 0; i < count; i++) {
        total++;
        hits += maybeCheckAndResetGrapicsElement(scene, base + i + 0x6E, 0x1E) != FALSE;
    }
    return (total - hits) == 0;
}

// .text:0x00074F40 size:0xC18 mapped:0x806B3FD4
void gfx_cssCharStatBars_and_sthgElse(MenuScene *scene, s32 port) {
    s32 character;
    s32 selected;
    s32 i;
    s8 variant;
    u8 batting;
    u8 pitching;
    u8 running;
    u8 fielding;

    if (menuControlVariables->currentScreen == 9 || gameSetUpStep[port + 0x5D] == 11) {
        if (g_d_GameSettings[7] != GAME_TYPE_CHALLENGE) {
            character = mapCaptainCursorPositionToCharID[menuCursors[port + 4]];
        } else {
            character = challengeCaptainCharIDArray[superstarUnlocked[0xF4] * 6 + menuCursors[4]];
        }
        pitching = ((CharacterStats (*)[9])Static_Stats_Tables)[character / 9][character % 9].stats.PitchingStatBar;
        batting = ((CharacterStats (*)[9])Static_Stats_Tables)[character / 9][character % 9].stats.BattingStatBar;
        running = ((CharacterStats (*)[9])Static_Stats_Tables)[character / 9][character % 9].stats.RunningStatBar;
        fielding = ((CharacterStats (*)[9])Static_Stats_Tables)[character / 9][character % 9].stats.FieldingStatBar;
        fn_2_74E14(scene, port, pitching, 1);
        fn_2_74E14(scene, port, running, 3);
        fn_2_74E14(scene, port, batting, 0);
        fn_2_74E14(scene, port, fielding, 2);
        gfxObject(scene, port + 0xAE)->flags &= ~UI_FLAG_VISIBLE;
        return;
    }

    selected = ((s32 *)lbl_2_bss_F468)[port];
    if (lbl_2_bss_F468[port + 0x41] != 0) {
        gfxObject(scene, port + 0xB2)->flags &= ~UI_FLAG_VISIBLE;
        character = menuCursors[port + 8];
    } else if (selected == 9 || selected == 10) {
        character = CHAR_ID_NONE;
    } else {
        character = CHAR_ID_NONE;
        for (i = 0; i < 9; i++) {
            if ((s8)cursorPositions[port * 9 + 0x14 + i] == (s8)selected) {
                character = (s8)cursorPositions[port * 9 + 2 + i];
            }
        }
    }

    if (character != CHAR_ID_NONE && addRemoveCharVariantRelated(0, (u8)character, 2) != 0 &&
        g_d_GameSettings[7] != GAME_TYPE_CHALLENGE) {
        gfxObject(scene, port + 0xB2)->flags |= UI_FLAG_VISIBLE;
        ((UIRecord *)gfxObject(scene, port + 0xB2))->frame = 0;
        ((UIRecord *)gfxObject(scene, port + 0xB2))->playMode = UI_PLAY_FORWARD;
        variant = 0;
        switch (character) {
        case CHAR_ID_TOAD_RED: case CHAR_ID_SHYGUY_RED: case CHAR_ID_PARATROOPA_RED: case CHAR_ID_PIANTA_RED: case CHAR_ID_NOKI_RED: case CHAR_ID_MAGIKOOPA_RED: case CHAR_ID_KOOPA_RED: case CHAR_ID_DRYBONES_RED: case CHAR_ID_BRO_FIRE:
            variant = 1; break;
        case CHAR_ID_PIANTA_BLUE: case CHAR_ID_NOKI_BLUE: case CHAR_ID_TOAD_BLUE: case CHAR_ID_MAGIKOOPA_BLUE: case CHAR_ID_SHYGUY_BLUE: case CHAR_ID_DRYBONES_BLUE: case CHAR_ID_BRO_BOOMERANG:
            variant = 2; break;
        case CHAR_ID_PIANTA_YELLOW: case CHAR_ID_TOAD_YELLOW: case CHAR_ID_MAGIKOOPA_YELLOW: case CHAR_ID_SHYGUY_YELLOW:
            variant = 3; break;
        case CHAR_ID_KOOPA_GREEN: case CHAR_ID_NOKI_GREEN: case CHAR_ID_BRO_HAMMER: case CHAR_ID_TOAD_GREEN: case CHAR_ID_MAGIKOOPA_GREEN: case CHAR_ID_PARATROOPA_GREEN: case CHAR_ID_SHYGUY_GREEN: case CHAR_ID_DRYBONES_GREEN:
            variant = 4; break;
        case CHAR_ID_TOAD_PURPLE:
            variant = 5; break;
        case CHAR_ID_SHYGUY_BLACK:
            variant = 6; break;
        }
        gfxObject(scene, port + 0xAE)->flags |= UI_FLAG_VISIBLE;
        ((UIRecord *)gfxObject(scene, port + 0xAE))->frame = (s8)variant << 16;
    } else {
        gfxObject(scene, port + 0xB2)->flags &= ~UI_FLAG_VISIBLE;
        if (((s32 *)lbl_2_bss_F468)[port] != 9 && ((s32 *)lbl_2_bss_F468)[port] != 10) {
            gfxObject(scene, port + 0xAE)->flags |= UI_FLAG_VISIBLE;
            ((UIRecord *)gfxObject(scene, port + 0xAE))->frame = 0;
        }
    }

    gfxObject(scene, port + 0xAC)->flags |= UI_FLAG_VISIBLE;
    if (character >= 0 && character < 54) {
        batting = ((CharacterStats (*)[9])Static_Stats_Tables)[character / 9][character % 9].stats.BattingStatBar;
        running = ((CharacterStats (*)[9])Static_Stats_Tables)[character / 9][character % 9].stats.RunningStatBar;
        pitching = ((CharacterStats (*)[9])Static_Stats_Tables)[character / 9][character % 9].stats.PitchingStatBar;
        fielding = ((CharacterStats (*)[9])Static_Stats_Tables)[character / 9][character % 9].stats.FieldingStatBar;
        gfxObject(scene, port + 0xB0)->flags |= UI_FLAG_VISIBLE;
        ((UIRecord *)gfxObject(scene, port + 0xB0))->frame = character << 16;
        ((UIRecord *)gfxObject(scene, port + 0xAC))->frame = 0;
        ((UIRecord *)gfxObject(scene, port + 0xAC))->playMode = UI_PLAY_FORWARD;
    } else {
        gfxObject(scene, port + 0xB0)->flags &= ~UI_FLAG_VISIBLE;
        batting = 0;
        running = 0;
        pitching = 0;
        fielding = 0;
    }
    if (character >= 0 && character < 54) {
        fn_2_74E14(scene, port, pitching, 1);
        fn_2_74E14(scene, port, running, 3);
        fn_2_74E14(scene, port, batting, 0);
        fn_2_74E14(scene, port, fielding, 2);
    } else {
        gfxObject(scene, port + 0x97)->flags &= ~UI_FLAG_VISIBLE;
    }
}

// .text:0x00074E14 size:0x12C mapped:0x806B3EA8
void fn_2_74E14(MenuScene *scene, s32 a, s32 b, u8 c) {
    u32 packed = ((u32)(b - 1) << 16);
    s32 result;

    gfxObject(scene, a + 0x97)->flags |= UI_FLAG_VISIBLE;
    ((UIRecord *)gfxObject(scene, a + 0x97))->frame = 0;
    ((UIRecord *)gfxObject(scene, a + 0x97))->playMode = UI_PLAY_FORWARD;
    ((UIRecord *)gfxObject(scene, c + a * 4 + 0x9B))->frame = packed;
    result = fn_80036214(scene, 0xAB, 0, (b + 1) / 2 - 1);
    ((UIRecord *)gfxObject(scene, c + a * 4 + 0xA3))->frame = packed;
    ((UIRecord *)gfxObject(scene, c + a * 4 + 0xA3))->rgba = result;
}

// .text:0x00074DB8 size:0x5C mapped:0x806B3E4C
s32 fn_2_74DB8(s32 character) {
    switch (character) {
    case CHAR_ID_TOAD_RED:
    case CHAR_ID_SHYGUY_RED:
    case CHAR_ID_PARATROOPA_RED:
    case CHAR_ID_PIANTA_RED:
    case CHAR_ID_NOKI_RED:
    case CHAR_ID_MAGIKOOPA_RED:
    case CHAR_ID_KOOPA_RED:
    case CHAR_ID_DRYBONES_RED:
    case CHAR_ID_BRO_FIRE:
        return 1;
    case CHAR_ID_PIANTA_BLUE:
    case CHAR_ID_NOKI_BLUE:
    case CHAR_ID_TOAD_BLUE:
    case CHAR_ID_MAGIKOOPA_BLUE:
    case CHAR_ID_SHYGUY_BLUE:
    case CHAR_ID_DRYBONES_BLUE:
    case CHAR_ID_BRO_BOOMERANG:
        return 2;
    case CHAR_ID_PIANTA_YELLOW:
    case CHAR_ID_TOAD_YELLOW:
    case CHAR_ID_MAGIKOOPA_YELLOW:
    case CHAR_ID_SHYGUY_YELLOW:
        return 3;
    case CHAR_ID_KOOPA_GREEN:
    case CHAR_ID_NOKI_GREEN:
    case CHAR_ID_BRO_HAMMER:
    case CHAR_ID_TOAD_GREEN:
    case CHAR_ID_MAGIKOOPA_GREEN:
    case CHAR_ID_PARATROOPA_GREEN:
    case CHAR_ID_SHYGUY_GREEN:
    case CHAR_ID_DRYBONES_GREEN:
        return 4;
    case CHAR_ID_TOAD_PURPLE:
        return 5;
    case CHAR_ID_SHYGUY_BLACK:
        return 6;
    default:
        return 0;
    }
}

// .text:0x00074D8C size:0x2C mapped:0x806B3E20
void fn_2_74D8C(void) {
    insertGraphicDrawingFunction(fn_2_74CD8, 0x1000);
}

// .text:0x00074CD8 size:0xB4 mapped:0x806B3D6C
void fn_2_74CD8(void) {
    DrawingSceneStruct *node = currentDrawingItem;
    int i;

    addGraphicsElementToScene(node, lbl_2_data_2D33C);
    for (i = 0; i < 7; i++) {
        load_Icon(node, i + 0x18, 1, 0x36, i);
    }
    load_Icon(node, 0x20, 1, 0x32, 0);
    mainMenuCursorShown = menuCursors[0];
    currentDrawingItem->func = fn_2_747FC;
}

// .text:0x000747FC size:0x4DC mapped:0x806B3890
void fn_2_747FC(void) {
    DrawingSceneStruct *node = currentDrawingItem;
    s32 cursor = menuCursors[0];
    s32 i;

    if (Static_Stats_Tables[0x472A] == 0) {
        removeGraphicsElementFromScene(node);
        removeCurrentDrawingItem();
        Static_Stats_Tables[0x472A] = 0xFF;
        return;
    }

    switch (gameSetUpStep[0x5D]) {
    case 0x54:
        if (gameSetUpStep[0x7] == 0) {
            for (i = 0; i < 7; i++) {
                if (menuCursors[0] == i) {
                    gfxNodeObject(node, i + 3)->flags |= 2;
                    gfxNodeSetU32(node, i + 3, 0);
                    gfxNodeSetU8(node, i + 3, 1);
                    gfxNodeSetU32(node, i + 0x18, 0);
                    gfxNodeSetU8(node, i + 0x18, 1);
                } else {
                    gfxNodeSetU32(node, i + 0x18, 0);
                    gfxNodeSetU8(node, i + 0x18, 0);
                    gfxNodeObject(node, i + 3)->flags &= ~2;
                }
            }
            if (lbl_8037169C[0x10] != 0) {
                changeScene(1, 6);
            }
            gfxNodeSetU32(node, 0x20, 0);
            gfxNodeSetU8(node, 0x20, 1);
            makeCursorUnmovable(0);
            gameSetUpStep[0x7] = 1;
        }
        if (gameSetUpStep[0x7] == 1) {
            s32 hits = 0;
            s32 ready = 0;

            for (i = 0; i < 7; i++) {
                if (menuCursors[0] == i) {
                    hits++;
                    ready += maybeCheckAndResetGrapicsElement((MenuScene *)node, i + 3, 0xE) != FALSE;
                }
            }
            ready += maybeCheckAndResetGrapicsElement((MenuScene *)node, 0x20, 0xA) != FALSE;
            if (ready == hits + 1) {
                makeCursorMovable(0);
                gameSetUpStep[0x7] = 2;
                updateCharacterSelectProcessCode(0, 0x57);
            }
        }
        break;
    case 0x55:
        if (gameSetUpStep[0x7] == 0) {
            makeCursorUnmovable(0);
            gameSetUpStep[0x7] = 1;
        }
        if (gameSetUpStep[0x7] == 1) {
            makeCursorMovable(0);
            gameSetUpStep[0x7] = 2;
        }
        break;
    case 0x56:
        fn_2_73EFC(node);
        fn_2_73CBC(node);
        break;
    case 0x57:
        if (gameSetUpStep[0x7] == 0) {
            gfxNodeSetU32(node, cursor + 0x11, 0xE0000);
            gfxNodeSetU8(node, cursor + 0x11, 1);
            gameSetUpStep[0x7] = 1;
        }
        if (gameSetUpStep[0x7] == 1) {
            if (*(u16 *)(Static_Stats_Tables + 0x472C) == 0 && Static_Stats_Tables[0x4751] != 0) {
                Static_Stats_Tables[0x4752] = 1;
                if (menuCursors[0] != menuCursors[1]) {
                    updateCharacterSelectProcessCode(0, 0x56);
                }
                mainMenuCursorShown = lbl_2_bss_A844;
                Static_Stats_Tables[0x4751] = 0;
            } else if (maybeCheckAndResetGrapicsElement((MenuScene *)node, cursor + 0x11, 0x37)) {
                gfxNodeSetU32(node, cursor + 0x11, 0xE0000);
                gfxNodeSetU8(node, cursor + 0x11, 1);
            }
        }
        break;
    case 0x58:
        if (gameSetUpStep[0x7] == 0) {
            gfxNodeSetU32(node, cursor + 0x11, 0x370000);
            gfxNodeSetU8(node, cursor + 0x11, 1);
            makeCursorUnmovable(0);
            gameSetUpStep[0x7] = 1;
        }
        if (gameSetUpStep[0x7] == 1) {
            if (maybeCheckAndResetGrapicsElement((MenuScene *)node, cursor + 0x11, 0x41)) {
                makeCursorMovable(0);
                gameSetUpStep[0x7] = 2;
            }
        }
        break;
    }
}

// .text:0x0007463C size:0x1C0 mapped:0x806B36D0
void fn_2_7463C(MenuScene *scene) {
    s32 i;

    if (gameSetUpStep[0x7] == 0) {
        for (i = 0; i < 7; i++) {
            if (menuCursors[0] == i) {
                gfxObject(scene, i + 3)->flags |= 2;
                *(u32 *)((u8 *)gfxObject(scene, i + 3) + 0x5C) = 0;
                *(u8 *)((u8 *)gfxObject(scene, i + 3) + 0x68) = 1;
                *(u32 *)((u8 *)gfxObject(scene, i + 0x18) + 0x5C) = 0;
                *(u8 *)((u8 *)gfxObject(scene, i + 0x18) + 0x68) = 1;
            } else {
                *(u32 *)((u8 *)gfxObject(scene, i + 0x18) + 0x5C) = 0;
                *(u8 *)((u8 *)gfxObject(scene, i + 0x18) + 0x68) = 0;
                gfxObject(scene, i + 3)->flags &= ~2;
            }
        }
        if (lbl_8037169C[0x10] != 0) {
            changeScene(1, 6);
        }
        *(u32 *)((u8 *)gfxObject(scene, 0x20) + 0x5C) = 0;
        *(u8 *)((u8 *)gfxObject(scene, 0x20) + 0x68) = 1;
        makeCursorUnmovable(0);
        gameSetUpStep[0x7] = 1;
    }
}

// .text:0x00074564 size:0xD8 mapped:0x806B35F8
void fn_2_74564(MenuScene *scene) {
    if (gameSetUpStep[0x7] == 1) {
        int hits = 0;
        int ready = 0;
        int i;

        for (i = 0; i < 7; i++) {
            if (menuCursors[0] == i) {
                hits++;
                ready += maybeCheckAndResetGrapicsElement(scene, i + 3, 0xE) != FALSE;
            }
        }
        ready += maybeCheckAndResetGrapicsElement(scene, 0x20, 0xA) != FALSE;
        if (ready == hits + 1) {
            makeCursorMovable(0);
            gameSetUpStep[0x7] = 2;
            updateCharacterSelectProcessCode(0, 0x57);
        }
    }
}

// .text:0x00074518 size:0x4C mapped:0x806B35AC
void fn_2_74518(void) {
    if (gameSetUpStep[0x7] == 0) {
        makeCursorUnmovable(0);
        gameSetUpStep[0x7] = 1;
    }
}

// .text:0x000744C8 size:0x50 mapped:0x806B355C
void fn_2_744C8(void) {
    if (!(1 - gameSetUpStep[0x7])) {
        makeCursorMovable(0);
        gameSetUpStep[0x7] = 2;
    }
}
