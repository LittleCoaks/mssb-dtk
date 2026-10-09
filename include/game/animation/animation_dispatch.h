#ifndef __GAME_ANIMATION_ANIMATION_DISPATCH_H_
#define __GAME_ANIMATION_ANIMATION_DISPATCH_H_

#include "mssbTypes.h"

typedef struct AnimObject AnimObject;

void resetAnimTracks(void);
void updateFielderState(int fielderIdx, int reset);
void foulAnimationRelatedMaybe(int fielderIdx, AnimObject* obj);
BOOL minigameFielderAnimCheck(int fielderIdx);
BOOL fielderBodyCheckAnimation(int fielderIdx);
BOOL fielderThrowWindupDone(int fielderIdx);
BOOL fielderThrowingAnimations(int fielderIdx);
BOOL animationsForFielding(int fielderIdx);
void fielderAnimations_setAnimation(int fielderIdx);
void handleRunnerActionsAndTagging(void);
void setThrowAnimationType(void);
void latchCatchAnimation(int fielderIdx);
void updateFielderAnimHints(int fielderIdx);
void shiftFielderAnimCounter(int fielderIdx);
void catcherIdleAnimation(void);
void fielderAnimations(void);
void runnerAnimation_general(int runnerIdx);
void runnerAnimation_detailed(int runnerIdx);
void runnerAnimations(void);
void batterAnimations(void);
void pitcherAnimation(void);
void minigameEndOfGameAnimations(void);
void minigameIdleAnimations(void);
void minigameAnimations(void);
void matchAnimations(void);
void unsure_updateAnimations(void);
void setDefaultPlayTrackingVariables3(void);
void resetAndRunAnimations(int arg);
void fn_3_674E0(void);

#endif // !__GAME_ANIMATION_ANIMATION_DISPATCH_H_
