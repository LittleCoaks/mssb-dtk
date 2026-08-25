#ifndef __MENUS_CAPTAIN_SELECT_CAPTAIN_SELECT_H_
#define __MENUS_CAPTAIN_SELECT_CAPTAIN_SELECT_H_

#include "mssbTypes.h"

typedef struct {
    /* 0x0 */ u16 currentHeldInput;
    /* 0x2 */ u16 newInput;
    /* 0x4 */ u16 processedInput;
} controllerInputStruct; // size: 0x6

void fn_2_14574(controllerInputStruct *input);
void checkForNewPlayer(void);
void fn_2_14BB8(int port, int state);
void captainSelect_handleCursor(u8 port, controllerInputStruct *input);
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

#endif // !__MENUS_CAPTAIN_SELECT_CAPTAIN_SELECT_H_
