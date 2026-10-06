#ifndef __GAME_MINIGAME_BARREL_BATTER_H_
#define __GAME_MINIGAME_BARREL_BATTER_H_

#include "mssbTypes.h"

void fn_3_12DB54(void);
void bB_AI(void);
BOOL fn_3_12DD88(void);
void bB_AI_setSwingVariables(void);
int fn_3_12E084(const void *a, const void *b);
void fn_3_12E17C(s8 *barrelsCleared, s16 *scores, u8 chainBonusInd);
u8 fn_3_12E384(u8 *barrels, s8 barrelIndex, u8 colour);
void fn_3_12E808(void);
void unused_BarrelBatterRelated(void);
void bB_chooseBombBarrel_dropNewBarrels(void);
void fn_3_12EB10(void);
E(u8, BOOL) fn_3_12ED80(void);
void fn_3_12EE68(int barrelIndex);
void bB_likelyReplaceBlownUpBarrels(int barrelIndex);
void fn_3_12F28C(int barrelIndex);
void bB_connectingBarrels(int barrelNum, int blowUpDelay, BOOL bombBarrelHitInd);
void bB_checkIfBarrelHitAndCalculateScore(void);
void fn_3_12F9D4(int barrelIndex);
void fn_3_12FAC4(void);
void fn_3_12FD6C(void);
void fn_3_12FE84(void);
void fn_3_12FFD4(void);
void barrelBatterLiveBallSubFun(void);
void fn_3_1307D0(void);
void fn_3_130A80(void);
void bobombDerbyRelated(void);
void bB_AtBat(void);
void fn_3_131114(void);
void fn_3_13119C(void);
void fn_3_13128C(void);
void fn_3_1312D4(void);
void barrelBatterTransitionToMainFunction(void);
void fn_3_131C88(void);
void fn_3_131EC4(void);
void fn_3_131FFC(void);
void fn_3_13207C(void);
void bB_LoadGame(void);
void fn_3_1323CC(void);
void barrelBatterSwitcher(void);

#endif // !__GAME_MINIGAME_BARREL_BATTER_H_
