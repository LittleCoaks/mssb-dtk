#ifndef __GAME_MATCH_SETUP_ROSTER_INIT_H_
#define __GAME_MATCH_SETUP_ROSTER_INIT_H_

#include "mssbTypes.h"

void fn_3_6D6D4(int runnerIdx);
void initializeInMemRunner(int rosterID, int runnerIdx);
void setInMemBatterConstants(int rosterID);
u8 getThrowSpeedBasedOnArmStrengthStat(u8 armStrength);
void setFielderValues(int characterID, int fielderIndex);
void setPitcherStatsToInMemPitcher(int rosterIdx);
void initRosterForMatch(void);

#endif // !__GAME_MATCH_SETUP_ROSTER_INIT_H_
