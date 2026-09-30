#ifndef __GAME_BATTING_AT_BAT_RESULTS_H_
#define __GAME_BATTING_AT_BAT_RESULTS_H_

#include "mssbTypes.h"

void setBatterOutAtBatResult(void);
void atBatBuntResult(void);
void atBatResultsForOuts(void);
BOOL noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance(void);
void fn_3_9D550(void);
void fn_3_9D594(void);
void setStrikeoutOrWalkAtBatResult(void);
void setAtBatResult(void);
void setDefaultPlayTrackingVariables1(void);
void initializeInningTrackers(void);
void shuffleU8Array(u8* values, int count, BOOL useGameRandom);
void shuffleIntArray(int* values, int count, BOOL useGameRandom);
int bobOmbDerbyBatterAI2(int* weights, int count);
int RandomIndexFromWeights(u8* weights, int count);
void iterateBatter(int team);
BOOL fn_3_9E834(void);
BOOL fn_3_9EA1C(int team);

#endif // !__GAME_BATTING_AT_BAT_RESULTS_H_
