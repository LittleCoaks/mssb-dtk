#ifndef __GAME_MATCH_SETUP_MATCH_FLOW_H_
#define __GAME_MATCH_SETUP_MATCH_FLOW_H_

#include "mssbTypes.h"

void fn_3_5C418(void);
int evaluateInningCondition(int inning);
void uncalledRunnerUpdateRelated(void);
void transitionToLiveBallWithoutContact(int arg0);
void processScoreChanges(int arg0);
void fn_3_5CD24(void);
void endOfMatch(void);
void challenge_onGameEnd(void);
void endOfGameCheck(int arg0);
void inningImportanceAI(void);
void switchHalfInning(void);
void inningChange(void);
void fn_3_5D9F8(void);
void settingGameStatus(void);
int handleABEndEvent(void);
void handleDeadBall(void);
void playOverTransitionStuff(void);
void checkIfPlayOver(void);
void switchFromAtBatToLiveBall(void);
void freePracticeSomething(void);
void endBatterTransition(void);
void atBatScreen(void);
void newPitch(void);
void matchTransitionPrepareNextAB(void);
void practiceNewBatter(void);
void initNewInning(void);
void exhibitionGameTransitionCalculations(void);
void fn_3_5FE88(void);
void initializeGame(void);
void baseballMatchSimulation(void);

#endif // !__GAME_MATCH_SETUP_MATCH_FLOW_H_
