#ifndef __UNKNOWN_ORDERCHANGE_H_
#define __UNKNOWN_ORDERCHANGE_H_

#include "mssbTypes.h"
#include "Unknown/File_0x80034e20.h"

s8 lineupOrderChangeRelated(u8 team, int position);
void transferStatsToInMemRoster(u8 team);
int randRange_FUN_80042bf0(int a, int b);
void sndFXRelated(u16 input);
void fn_80042D38(u16 screen);
BOOL fn_80042D68(MenuScene* scene, int handle, int frame);
BOOL maybeCheckAndResetGrapicsElement(MenuScene* scene, int handle, int frame);
void challengeStarMenu(void);
void starMenuCursor(void);
void swapPosMenu_left_rightPress(u8 right, u8 team);
void swapPosMenu_up_downPress(u8 down, u8 team);

#endif // !__UNKNOWN_ORDERCHANGE_H_
