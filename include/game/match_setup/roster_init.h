#ifndef __GAME_MATCH_SETUP_ROSTER_INIT_H_
#define __GAME_MATCH_SETUP_ROSTER_INIT_H_

#include "mssbTypes.h"

void setRunnerSpeedConstants(int runnerIdx);
void initializeInMemRunner(int rosterID, int runnerIdx);
void setInMemBatterConstants(int rosterID);
u8 getThrowSpeedBasedOnArmStrengthStat(u8 armStrength);
void setFielderValues(int rosterID, int fielderIndex);
void setPitcherStatsToInMemPitcher(int rosterIdx);
void initRosterForMatch(void);

#endif // !__GAME_MATCH_SETUP_ROSTER_INIT_H_
