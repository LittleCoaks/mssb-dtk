#ifndef __GAME_PRACTICE_PRACTICE_MENU_H_
#define __GAME_PRACTICE_PRACTICE_MENU_H_

#include "mssbTypes.h"

void practiceRelatedReset(void);
void baserunningPracticeRelated(void);
void fn_3_B3C64(void);
void setTutorialState(int state);
void updatePracticeTransitionState(int state);
void switchSecondaryGameMode(int mode);
BOOL practice_relatedToSettingCharacters(void);
void practiceLoadingRelatedMaybe(void);
void practice_loadCharacter(int team, int slot, int character, int flags);
void practice_loadCharacterData(void);
void loadPracticeScreen(void);
void practiceSimulation(void);
void fn_3_B49D4(void);
void practiceRelatedMenu(void);
void unref(void);
void practice_subMenu_stateHandling(void);
void notReferenced(void);
void practice_mainMenu_stateHandling(void);
void unused_MaybePractice(void);
void practiceMenu_setScreen(int screen);
void practiceMenu(void);

#endif
