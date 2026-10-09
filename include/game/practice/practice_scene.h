#ifndef __GAME_PRACTICE_PRACTICE_SCENE_H_
#define __GAME_PRACTICE_PRACTICE_SCENE_H_

#include "mssbTypes.h"

struct PracticeScene;

void practiceGuidedMessage_update(void);
void practiceGuidedMessage_init(void);
void practiceCompleteBanner_update(void);
void practiceCompleteBanner_init(void);
void practiceGoalHud_updateCounter(struct PracticeScene* scene);
void practiceGoalHud_update(void);
void practiceGoalHud_init(void);
void practice_insertGoalHudScenes(void);
void practiceInstruction_update(void);
void practiceInstruction_init(void);
void practice_insertInstructionScene(void);
void practiceMenu_charSelect_update(void);
void practiceMenu_charSelect_init(void);
void practiceMenu_subMenu_update(void);
void practiceMenu_subMenu_init(void);
void practiceMenu_typeIcons_update(void);
void practiceMenu_typeIcons_init(void);
void animationOrDrawingRelated(void);
void practice_drawHud(void);
void animatePracticeScene(void);

#endif // !__GAME_PRACTICE_PRACTICE_SCENE_H_
