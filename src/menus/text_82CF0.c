#include "menus/text_82CF0.h"

#include "menus/text_00110.h"
#include "text/text.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x80034cec.h"
#include "Unknown/File_0x800625a4.h"
#include "Unknown/File_0x80062674.h"

extern Text00110Ctl *menuControlVariables;
extern u8 menuNumber[0x28];
extern u8 cardCheck[0x5C];
extern u8 gameSetUpStep[];
extern u8 lbl_800FEF70[0x5D0];
extern u8 lbl_803CBCD0[];
extern u8 lbl_2_data_2B4DC[];

void fn_80053FE8(void);
void relatedToTeamSelection3(void);

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

// .text:0x00082DE8 size:0x70 mapped:0x806C1E7C
void fn_2_82DE8(void) {
    *(DrawingSceneStruct **)((u8 *)&Static_Stats_Tables + 0x4748) = currentDrawingItem;
    ((u8 *)&Static_Stats_Tables)[0x48AF] = 0;
    g_MatchInfo.unk37 = 0;
    g_MatchInfo.unk38 = 0;
    addGraphicsElementToScene(currentDrawingItem, (const UIRecordDescriptor *)lbl_2_data_2B4DC);
    currentDrawingItem->func = fn_2_82CF0;
}

// .text:0x00082E58 size:0x68 mapped:0x806C1EEC
void relatedToTeamSelection4(void) {
    if (menuControlVariables->previousScreen != 0xB &&
        g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
        insertGraphicDrawingFunction(fn_2_82DE8, 0x3000);
    }
    insertGraphicDrawingFunction(relatedToTeamSelection3, 0x3000);
}

// .text:0x00082EC0 size:0x630 mapped:0x806C1F54
void fn_2_82EC0(void) {
    return;
}

// .text:0x000834F0 size:0x1B4 mapped:0x806C2584
void fn_2_834F0(void) {
    return;
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

// .text:0x00083744 size:0x94 mapped:0x806C27D8
void fn_2_83744(TextScene *scene) {
    GraphicsArrayEntry *first = &graphicsRelatedArray[scene->firstHandle];

    if ((*(u32 *)((u8 *)first->object + 0x5C) >> 16) == 0x14) {
        ((u8 *)first->object)[0x68] = 1;
    }
    first = &graphicsRelatedArray[scene->firstHandle];
    if ((*(u32 *)((u8 *)first->object + 0x5C) >> 16) == 0x1E) {
        lbl_803CBCD0[0xC] = 1;
        makeCursorMovable(0);
        gameSetUpStep[0x31] = 2;
    }
}

// .text:0x000837D8 size:0x19C mapped:0x806C286C
void fn_2_837D8(void) {
    return;
}

// .text:0x00083974 size:0x1C0 mapped:0x806C2A08
void fn_2_83974(void) {
    return;
}

// .text:0x00083B34 size:0x660 mapped:0x806C2BC8
void stadiumRandomRelated(void) {
    return;
}

// .text:0x00084194 size:0x1F4 mapped:0x806C3228
void fn_2_84194(void) {
    return;
}

// .text:0x00084388 size:0x220 mapped:0x806C341C
void fn_2_84388(void) {
    return;
}

// .text:0x000845A8 size:0xA00 mapped:0x806C363C
void fn_2_845A8(void) {
    return;
}

// .text:0x00084FA8 size:0x160 mapped:0x806C403C
void stadiumScreenAnimations_maybe(void) {
    return;
}

// .text:0x00085108 size:0x54 mapped:0x806C419C
void loadStadiumScreen_maybe(void) {
    menuNumber[9] = menuNumber[8];
    menuNumber[0] = 5;
    menuNumber[8] = *(u16 *)(lbl_800FEF70 + 0x58);
    insertGraphicDrawingFunction(stadiumScreenAnimations_maybe, 0x3000);
}

// .text:0x0008515C size:0x4 mapped:0x806C41F0
void fn_2_8515C(void) {
    return;
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

// .text:0x000851A8 size:0x168 mapped:0x806C423C
void fn_2_851A8(void) {
    return;
}

// .text:0x00085310 size:0x1A0 mapped:0x806C43A4
void fn_2_85310(void) {
    return;
}

// .text:0x000854B0 size:0x18C mapped:0x806C4544
void fn_2_854B0(void) {
    return;
}
