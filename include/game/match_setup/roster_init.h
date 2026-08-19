#ifndef __GAME_MATCH_SETUP_ROSTER_INIT_H_
#define __GAME_MATCH_SETUP_ROSTER_INIT_H_

#include "mssbTypes.h"

void fn_3_6D6D4(void);
void initializeInMemRunner(void);
void setInMemBatterConstants(int rosterID);
void getThrowSpeedBasedOnArmStrengthStat(void);
void setFielderValues(void);
void setPitcherStatsToInMemPitcher(void);
void initRosterForMatch(void);

#endif // !__GAME_MATCH_SETUP_ROSTER_INIT_H_
