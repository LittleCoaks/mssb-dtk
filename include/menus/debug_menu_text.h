#ifndef __MENUS_DEBUG_MENU_TEXT_H_
#define __MENUS_DEBUG_MENU_TEXT_H_

#include "mssbTypes.h"

/* Debug-menu text and tables. An identical copy opens the .data of several
 * menus translation units (captain_select 0x19E8, challenge_file_select
 * 0x2B78, and 0x1E28 which belongs to the unit before the options screen), so
 * it most likely comes from a shared header. Only the strings are understood;
 * the trailing tables are kept as raw values. */
typedef struct {
    /* 0x000 */ char batOrder[2][0x20];
    /* 0x040 */ char fl[0x20];
    /* 0x060 */ char pc[0x20];
    /* 0x080 */ char hands[4][4];
    /* 0x090 */ char offOn[2][0x20];
    /* 0x0D0 */ char menuItems[5][0x20];
    /* 0x170 */ char portLabels[8][0x20];
    /* 0x270 */ u32 colors[8];
    /* 0x290 */ u16 unk290[12];
    /* 0x2A8 */ u8 unk2A8[12];
    /* 0x2B4 */ u8 unk2B4[16];
} DebugMenuText; // size: 0x2C4

#endif // !__MENUS_DEBUG_MENU_TEXT_H_
