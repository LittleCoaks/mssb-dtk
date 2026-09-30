#ifndef __GAME_MATCH_SETUP_MATCH_FLOW_H_
#define __GAME_MATCH_SETUP_MATCH_FLOW_H_

#include "mssbTypes.h"

typedef struct {
    s16 score;
    s16 outs;
    s16 runnerFlags;
    s16 currentBatter;
} ChallengeSituation;

typedef struct {
    u32 _0;
    u32 _4;
    u32 _8;
    u32 _C;
} MatchEndFile;

void resetCount(void);
void configureTeamsForGame_Unused(int arg0, int arg1, int arg2, int arg3);
void SetGameStatus(int status);
void exitToMenuControl(void);
void gameInitRelated(void);
void simulate1FrameOfTheGame(void);
void fn_3_5AE0C(void);
void transferSomeValuesOnMatchLoad(void);
void gameSimulationFunction(void);
int fn_3_5B220(int arg0);
void fn_3_5B368(void);
int exitMenu_main(void);
void fn_3_5B408(void);
void fn_3_5B41C(void);
void startChallengeModeMatch(void);
void endOfGame_menuControl(void);
void matchEndGameScreenFunction(void);
void fn_3_5C418(void);
int evaluateInningCondition(int inning);
void uncalledRunnerUpdateRelated(void);
void transitionToLiveBallWithoutContact(int arg0);
void processScoreChanges(int arg0);
void fn_3_5CD24(void);
void endOfMatch(void);
void fn_3_5CFD0(void);
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
