#ifndef __MENUS_CAPTAIN_SELECT_CAPTAIN_SELECT_H_
#define __MENUS_CAPTAIN_SELECT_CAPTAIN_SELECT_H_

#include "mssbTypes.h"
#include "static/UnknownHomes_Static.h"   // controllerInputStruct, Static_Stats_Tables

void fn_2_14574(controllerInputStruct *input);
void checkForNewPlayer(void);
void fn_2_14BB8(int port, int state);
void captainSelect_handleCursor(u8 port, controllerInputStruct *input);
void captainSelect_randomizeCaptainForSlot(int slot);
void fn_2_150D0(u8 idx);
BOOL loadNewCaptainModelOnCapSelectScreen(int currentCharId, int newCharId, int port, int arg3);
void captainSelect_BPress(int idx);
void captainSelect_APress(int idx);
void fn_2_15A90(int *value, u8 port, int max);
void captainSelectScreenInputs(int port, u16 currentHeldInput, u16 newInput, u16 processedInput);
void captainSelect_handleInputs(int port);
void onlySetPort1ToActiveOnInitialCapSSLoad(void);
void fn_2_16460(void);
void fn_2_16664(void);
void fn_2_166CC(void);
void captainSelect_setupCameraProjection(void);

#endif // !__MENUS_CAPTAIN_SELECT_CAPTAIN_SELECT_H_
