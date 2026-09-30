#ifndef __GAME_MATCH_SETUP_RESULT_STATS_H_
#define __GAME_MATCH_SETUP_RESULT_STATS_H_

#include "mssbTypes.h"

void MVPCalculation(void);
void winningPitcher(void);
void endOfGameStats_MVP(void);
void steal_pickoff_incrementSteal_runsStats(void);
void fn_3_76C78(void);
void updateStatsBasedOnABResult(int rosterID, int result, int fielder, int rbis);

#endif // !__GAME_MATCH_SETUP_RESULT_STATS_H_
