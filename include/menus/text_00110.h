#ifndef __MENUS_TEXT_00110_H_
#define __MENUS_TEXT_00110_H_

#include "mssbTypes.h"

// View of the menuControlVariables block (larger than menuControlStruct in yd_step.h).
typedef struct Text00110Ctl {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 currentScreen;
    /* 0x04 */ u16 currentState;
    /* 0x06 */ u16 previousScreen;
    /* 0x08 */ u16 previousState;
    /* 0x0A */ u8 _pad0A[0x0C - 0x0A];
    /* 0x0C */ u16 slots[2];
    /* 0x10 */ u8 flags10;
} Text00110Ctl;

void fn_2_110(void);
void fn_2_160(void);
s32 fn_2_1A8(u8 index, u8 mode, u16 mask);
void fn_2_2D8(void);
void bPressOnStadSelectScreen(void);
void fn_2_328(void);
void fn_2_374(void);
s32 fn_2_4C4(u8 *obj, u8 value);
u8 fn_2_510(u8 *obj);
void fn_2_554(void);
void fn_2_664(void);
void fn_2_708(void);
void fn_2_794(void);
void fn_2_940(void);
void fn_2_978(void);
void fn_2_A14(void);

#endif // !__MENUS_TEXT_00110_H_
