#ifndef __GAME_MATCH_SETUP_STAT_TRACKING_H_
#define __GAME_MATCH_SETUP_STAT_TRACKING_H_

#include "mssbTypes.h"
#include "static/UnknownHomes_Static.h"

void setInitialTotalBasesOnHit(void);
void fn_3_79A00(void);
void midPlay_trackStats(void);
void fn_3_79DD4(void);
void updatePitcherStatsOnScoreChange(void);
void postPitchStatUpdating(int arg);
void incrementPitchCount(void);
void postPitchStatRelated(int arg);
void fn_3_7AD68(void);
int fn_3_7AEA8(void);
void fn_3_7AEE8(void);
void fn_3_7AEEC(void);
void setRunnerOnBaseIndicators(void);
void intializeRunnersDuringTransition(void);
void resetGameControlVars_duringNewInning(void);
void initializeStats(void);
StatisticsBatter* fn_3_7BB74(void);
StatisticsPitcher* fn_3_7BBC0(void);
void fn_3_7BBF8(void);
void fn_3_7BC0C(void);
void determineIfReplayShouldPlay(void);
void fn_3_7C190(void);
BOOL fn_3_7C194(void);

#endif // !__GAME_MATCH_SETUP_STAT_TRACKING_H_
