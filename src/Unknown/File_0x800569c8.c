#include "Unknown/File_0x800569c8.h"
#include "Unknown/File_0x80056120.h"
#include "Unknown/File_0x800b0a14.h"
#include "static/UnknownHomes_Static.h"

typedef struct MenuLabel {
    /* 0x0 */ u8 _0[8];
    /* 0x8 */ u16 label;
    /* 0xA */ u8 _A[6];
} MenuLabel;

extern u8 menuNumber[0x28];
extern MenuLabel lbl_800FEF70[];

void fn_80053FE8(void);

#define SET_MENU(id)                   \
    menuNumber[0] = (id);              \
    menuNumber[9] = menuNumber[8];     \
    menuNumber[8] = lbl_800FEF70[(id)].label

void updateMenuNumbers(void) {
    if (g_d_GameSettings._06 == 2) {
        insertGraphicDrawingFunction(fn_80053FE8, 0);
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            SET_MENU(0x15);
        } else {
            SET_MENU(7);
        }
    } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        SET_MENU(0x14);
    } else {
        SET_MENU(6);
    }
    insertGraphicDrawingFunction(newMenuRelated, 0x3000);
}
