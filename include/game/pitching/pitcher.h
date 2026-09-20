#ifndef __GAME_PITCHING_PITCHER_H_
#define __GAME_PITCHING_PITCHER_H_

#include "mssbTypes.h"

BOOL fn_3_6F6CC(void);
BOOL waitingForPitch_checkForPickoffs(void);
void fn_3_6FA28(void);
void fn_3_6FB98(void);
void fn_3_6FDA0(void);
void fn_3_6FFC4(void);
void fn_3_70280(void);
void pitchCall(void);
BOOL fn_3_70680(f32 x);
void fn_3_706B8(int idx);
int estimateXAndFrameAtBatterZ(f32* outX, f32 z, int flag);
void fn_3_70838(void);
void fn_3_709B4(void);
void fn_3_70AEC(void);
void fn_3_70B94(void);
void pitchCurve(void);
void pitchInAirFunction(void);
void pitchSetPhysicsConstants(void);
void adjustPitchCurveSpeedCursedBall(void);
void pitchBeingReleased(void);
void handleHPBORRunnerAdvance(void);
void resetBatterCount(void);
void resetCounter(void);
void fn_3_7372C(void);
void fn_3_73850(void);
void endAtBatNonHit(void);
void fn_3_73DE8(void);
void fn_3_73F2C(void);
void fn_3_73FAC(void);
void fn_3_740D0(void);
void pitchingWindUpFunction(void);
void pitcherMovementOnMound(void);
void waitingForPitch(void);
void fn_3_75090(void);
void pitcherAITransitionFromPrePitchToWindup(u8 state);
BOOL loadPitcherActor(void);
void setDefaultInMemPitcher(void);
void resetPitcherValuesBetweenBatters(int flag);
void resetInMemPitcher(void);
void setPitchingConstants(void);
void atBat_Pitcher(void);

#endif // !__GAME_PITCHING_PITCHER_H_
