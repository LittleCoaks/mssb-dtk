#ifndef __GAME_MATCH_SETUP_STAT_LOOKUPS_H_
#define __GAME_MATCH_SETUP_STAT_LOOKUPS_H_

#include "mssbTypes.h"

void resetInputTrackers(void);
int getAdjustedPitcherStamina(int team, int rosterID, int flag);
BOOL checkFieldingStat(int team, int rosterID, int ability);
int calculateChemistry(int team, int charIdA, int charIdB);

#endif // !__GAME_MATCH_SETUP_STAT_LOOKUPS_H_
