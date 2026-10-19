#include "Unknown/File_0x8006236c.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x80057c08.h"
#include "Unknown/File_0x80058050.h"
#include "Unknown/File_0x80061b9c.h"
#include "Unknown/File_0x800b0a14.h"

typedef struct MenuLabel {
    /* 0x0 */ u8 _0[8];
    /* 0x8 */ u16 label;
    /* 0xA */ u8 _A[6];
} MenuLabel;

extern u8 superstarUnlocked[0x130];
extern u8 menuNumber[0x28];
extern MenuLabel lbl_800FEF70[];
extern void fn_8006CF6C(void);

#define SET_MENU(id)                                              \
    menuNumber[0] = (id);                                         \
    menuNumber[9] = menuNumber[8];                                \
    menuNumber[8] = lbl_800FEF70[(id)].label

#define CHECK_SUPERSTAR_BYTE()                                    \
    if (*++p != 0) {                                              \
        found = 1;                                                \
        break;                                                    \
    }

void SetMenuNumber(void) {
    s16 menu;
    u8 found;
    int i;
    u8 code;
    u8 *p;

    if (g_d_GameSettings._06 != 2) {
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
            menu = 0x16;
        } else {
            found = 0;
            p = superstarUnlocked;
            for (i = 0; i < 6; i++) {
                if (*p != 0) {
                    found = 1;
                    break;
                }
                CHECK_SUPERSTAR_BYTE();
                CHECK_SUPERSTAR_BYTE();
                CHECK_SUPERSTAR_BYTE();
                CHECK_SUPERSTAR_BYTE();
                CHECK_SUPERSTAR_BYTE();
                CHECK_SUPERSTAR_BYTE();
                CHECK_SUPERSTAR_BYTE();
                CHECK_SUPERSTAR_BYTE();
                p++;
            }
            if (found) {
                menu = 4;
            } else {
                menu = 3;
            }
        }
        SET_MENU(menu);
    }

    code = aiPosSwapInputs._CFA2[aiPosSwapInputs.playerWhoPaused];
    if (code != 2 && code != 3) {
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE &&
            aiPosSwapInputs._CF5F[0xCF70 - 0xCF5F] != 0 &&
            superstarUnlocked[0xE4] == 0) {
            insertGraphicDrawingFunction(fn_8006CF6C, 0x3000);
        }
        insertGraphicDrawingFunction(teamManagementGraphics_initialLoad, 0x3000);
    } else {
        if (code == 2) {
            insertGraphicDrawingFunction(scoutFlagMenu, 0x3000);
        } else {
            insertGraphicDrawingFunction(starMenu, 0x3000);
        }
    }
}
