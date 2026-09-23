#ifndef __GAME_PITCHING_PITCHER_AI_H_
#define __GAME_PITCHING_PITCHER_AI_H_

#include "mssbTypes.h"

int aiPitchCurveDirection(f32 curve);
void movePitcherOnMound(void);
void fn_3_20EEC(void);
void pitcherAISetCurve(void);
void pitcherAISelectPitch(void);
void pitcherAI_prePitchSetConstants(void);
void pitcherAINewBatter(void);
void resetPitcherPreAB(void);

#endif // !__GAME_PITCHING_PITCHER_AI_H_
