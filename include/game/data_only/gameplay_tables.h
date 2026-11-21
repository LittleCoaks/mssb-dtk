#ifndef __GAME_DATA_ONLY_GAMEPLAY_TABLES_H_
#define __GAME_DATA_ONLY_GAMEPLAY_TABLES_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"

// Tables defined in gameplay_tables.c. That file defines initialBoxPosition as f32[3]
// and hitTrajOptions as u32[98], so it does not include this header.
extern VecXYZ initialBoxPosition; // boxPosition at the start of every at-bat, before clamping
extern s16 hittableFrameInd[2][FRAME_COUNT_HIT_WINDOW];
extern BatNearFarReach batContactRange[2];
extern HitFloats g_hitFloats;
extern HitShorts g_hitShorts;
extern u8 buntPower[5][2];
extern VecXYZ s_ballCurveData[2];
extern u8 swingSoundFrame[2][4];
extern s16 CaptainStarSwingBattingVerticalAngleRanges[12][5][2];
extern s16 NonCaptainStarSwingBattingVerticalAngleRanges[3][5][2];
extern s16 HitVertTrajRanges[2][5][5][2];
extern s16 bB_launchAngles[2][3];
extern s16 lbl_3_data_54F8[2][2];
extern trajZones bODTrajProbabilities[5];
extern trajZones ToyFieldBattingVerticalAngleRanges[3][2][2][5];
extern trajZones BattingVerticalAngleRangeProbabilities[3][2][2][5];
extern trajOptions_s hitTrajOptions[];
extern s16 toyFieldHitVertTraj[2][5][5][2];
extern s16 bODHitVertTraj[5][5][2];

#endif // !__GAME_DATA_ONLY_GAMEPLAY_TABLES_H_
