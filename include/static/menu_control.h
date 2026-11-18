#ifndef __MENU_CONTROL_H_
#define __MENU_CONTROL_H_

#include "types.h"

// The separate object right after inningSetting (.data:0x800E877C). The menus
// REL addresses it as its own symbol (base +0, fields +0x30/+0x32) and keeps
// a pointer to it in lbl_2_bss_1A823C.
typedef struct _MenuControl {
    /*0x00*/ s16 rel;           // which REL is resident: 0 boot, 4 menu, 5 match
    /*0x02*/ u16 currentScene;  // the menu screenCode (5 main menu, 6 options, ...)
    /*0x04*/ u16 _4;
    /*0x06*/ u16 previousScene;
    u8 _pad_8[0x28];
    /*0x30*/ s16 sceneMode;
    /*0x32*/ s16 sceneState;
    u8 _pad_34[0x4];
} MenuControl; // size: 0x38

extern MenuControl g_MenuControl;

#endif // __MENU_CONTROL_H_
