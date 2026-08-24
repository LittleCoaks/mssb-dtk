#ifndef __MENUS_REP_04B0_H_
#define __MENUS_REP_04B0_H_

#include "mssbTypes.h"

void fn_2_14574(void);
void checkForNewPlayer(void);
void fn_2_14BB8(int port, int state);
void captainSelect_handleCursor(void);
void fn_2_14FB8(int port);
void fn_2_150D0(u8 idx);
BOOL loadNewCaptainModelOnCapSelectScreen(int currentCharId, int newCharId, u8 port, int arg3);
void captainSelect_BPress(void);
void captainSelect_APress(void);
void fn_2_15A90(int *value, u8 port, int max);
void captainSelectScreenInputs(void);
void captainSelect_handleInputs(void);
void onlySetPort1ToActiveOnInitialCapSSLoad(void);
void fn_2_16460(void);
void fn_2_16664(void);
void fn_2_166CC(void);
void fn_2_16724(void);

#endif // !__MENUS_REP_04B0_H_
