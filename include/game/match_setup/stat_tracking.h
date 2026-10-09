#ifndef __GAME_MATCH_SETUP_STAT_TRACKING_H_
#define __GAME_MATCH_SETUP_STAT_TRACKING_H_

#include "mssbTypes.h"
#include "static/UnknownHomes_Static.h"

void setInitialTotalBasesOnHit(void);
void trackForceOutsThisPlay(void);
void midPlay_trackStats(void);
void checkSaveSituation(void);
void updatePitcherStatsOnScoreChange(void);
void postPitchStatUpdating(int arg);
void incrementPitchCount(void);
void postPitchStatRelated(int arg);
void fn_3_7AD68(void);
int fn_3_7AEA8(void);
void fn_3_7AEE8(void);
void setRunnerOnBaseIndicators2(void);
void setRunnerOnBaseIndicators(void);
void intializeRunnersDuringTransition(void);
void resetGameControlVars_duringNewInning(void);
void initializeStats(void);
StatisticsBatter* getCurrentBatterStats(void);
StatisticsPitcher* getCurrentPitcherStats(void);
void fn_3_7BBF8(void);
void fn_3_7BC0C(void);

#endif // !__GAME_MATCH_SETUP_STAT_TRACKING_H_
