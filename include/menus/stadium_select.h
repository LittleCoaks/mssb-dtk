#ifndef __MENUS_STADIUM_SELECT_H_
#define __MENUS_STADIUM_SELECT_H_

#include "mssbTypes.h"
#include "text/text.h"

extern u8 cursorToStadIDMapping[6];

s32 fn_2_112F4(UnkText988Arg* arg0, s32 indexOffset, s32 arg2, u16* arg3, u16 arg4);
void stadiumSelectControls(u8 idx);
void selectStadiumScreen(void);
void fn_2_11EA8(void);
void fn_2_120D0(void);
void fn_2_1216C(void);

#endif // !__MENUS_STADIUM_SELECT_H_
