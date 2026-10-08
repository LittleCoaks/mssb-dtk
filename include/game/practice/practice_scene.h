#ifndef __GAME_PRACTICE_PRACTICE_SCENE_H_
#define __GAME_PRACTICE_PRACTICE_SCENE_H_

#include "mssbTypes.h"

struct PracticeScene;

void chainChomp_spawnTrailEffect(void* owner);
void practiceAnimationRelated4(void);
void practiceAnimationRelated2(void);
void practiceCompleteBanner_update(void);
void practiceCompleteBanner_init(void);
void practiceGoalHud_updateCounter(struct PracticeScene* scene);
void practiceGoalHud_update(void);
void practiceGoalHud_init(void);
void practice_insertGoalHudScenes(void);
void practiceAnimationRelated_text(void);
void practiceAnimationRelated(void);
void practice_insertInstructionScene(void);
void practiceMenu_charSelect_update(void);
void practiceMenu_charSelect_init(void);
void practiceMenu_subMenu_update(void);
void graphicsRelated(void);
void practiceMenu_typeIcons_update(void);
void practiceMenu_typeIcons_init(void);
void animationOrDrawingRelated(void);
void practice_drawHud(void);
void animatePracticeScene(void);
void practice_startPitchAfter90Frames(void);
void freeFieldingPracticeTransition(void);
void practiceRelated(void);
void unused_matchSimulationRelated(void);
void fieldingPractice_resetMem(void);
void freeFieldingPracticeLoadCharacters(void);
void freeFieldingPracticeSwitcher(void);
void freeFieldingPracticeControl(void);

#endif // !__GAME_PRACTICE_PRACTICE_SCENE_H_
