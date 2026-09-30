#ifndef __GAME_MATCH_SETUP_MATCH_SCENE_H_
#define __GAME_MATCH_SETUP_MATCH_SCENE_H_

#include "mssbTypes.h"
#include "Unknown/File_0x800b0a14.h"

void manageEventStates(void);
void fn_3_972A0(DrawingSceneStruct* node, int slot, int handle, int state);
void unregisterMatchHudObjects(void);
void animateMatchScene(void);
void initAnimStruct(void);
void pauseControlsMenu_update(void);
void pauseMenu_ControlsMenu(void);
void pausePageIndicator_update(void);
void pausePageIndicator_init(void);
void pauseOptionList_update(void);
void pauseOptionList_init(void);
void pauseSubPanel_update(void);
void pauseSubPanel_init(void);
void pauseMenu_openTeamManagement(void);
void animatePauseMenu(void);

#endif // !__GAME_MATCH_SETUP_MATCH_SCENE_H_
