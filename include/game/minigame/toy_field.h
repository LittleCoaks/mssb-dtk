#ifndef __GAME_MINIGAME_TOY_FIELD_H_
#define __GAME_MINIGAME_TOY_FIELD_H_

#include "mssbTypes.h"

void fn_3_D8A10(void);
void fn_3_D8CD0(void);
void fn_3_D9868(void);
void toyFieldRelated(void);
void toyFieldUpdateCoins(void);
void toyFieldSpawnCoins(int count, int type);
void toyFieldPoints(void);
void toyFieldApplyBallResult(void);
void processToyFieldBallState(void);
void toyFieldPostMenuInput(void);
void toyFieldPostMenu(void);
void toyFieldPauseMenuInput(void);
void toyFieldPause(void);
void toyFieldWaitForPause(void);
void toyFieldCheckForPause(void);
void toyFieldStateTransitionRelated(void);
void toyFieldInningTransition(void);
void toyFieldFinishTurn(void);
void toyFieldLiveBallOutcome(void);
void toyFieldLiveBall(void);
void toyFieldAtBatOutcome(void);
void initializeStgh2(void);
void toyFieldAtBat(void);
void toyFieldAwardPoints(int type);
void minigameCalculateRankings(void);
void toyFieldEndTurn(void);
void initializeToyFieldSomething(void);
void initializeMinigameData(void);
void fn_3_DEB90(void);
void toyFieldTransitionPrepareNextPlay(void);
void toyFieldTransitionToMinigameStart(void);
void toyFieldGameStartMovie(void);
void fn_3_DF608(void);
void fn_3_DF6D4(void);
void fn_3_DF820(void);
void fn_3_DFA20(void);
void toyfieldSimulation(void);

#endif // !__GAME_MINIGAME_TOY_FIELD_H_
