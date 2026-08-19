#ifndef __GAME_MATH_GAME_MATH_H_
#define __GAME_MATH_GAME_MATH_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"

#define SANG_MAX_ANGLE (0x1000)

#define SANG_ANG_90 (SANG_MAX_ANGLE / 4)
#define SANG_ANG_180 (SANG_MAX_ANGLE / 2)
#define SANG_ANG_270 (SANG_ANG_90 * 3)
#define SANG_ANG_360 (SANG_MAX_ANGLE)

f32 RandomF32_UNK_Range(f32 a, f32 b);
f32 RandomF32_Game_Range(f32 a, f32 b);
int RandomInt_Game_Range(int min, int max);
int random_fn_3_9EE24(int max);
int RandomInt_Game(int max);
// void static_clamp(void);
f32 calculateBallInterceptDistance(VecXYZ* a, VecXYZ* b, VecXYZ* c, VecXYZ* d);
bool calculateLineIntersection(VecXZ* out, VecXZ* a, VecXZ* b);
void normalizeVector(VecXYZ* out, VecXYZ* v);
void fieldersRunningToDugoutCalculateOffsets(f32 a, f32 b, f32 c, f32* x, f32* y);
void getComponentsFromRad(f32 v, f32* x, f32* y);
void getComponentsFromSAng(s16 ang, f32* x, f32* y);
f32 fn_3_9FAA4(f32 x, f32 y);
f32 game_atan2(f32 x, f32 y);
s16 calculateAngleFromCoordinates(f32 x, f32 y);
s16 calculateDiffInAngles(f32 a, f32 b);
s16 angleDifferenceNormalized(s16 a, s16 b);
s16 getDifferenceInAngle(s16 a, s16 b);
s16 normalizeAnglebetween_2048And2047(s16 ang);
s16 fn_3_9FD6C(s16 ang);
f32 fn_3_9FDD8(f32);
s16 normalizeAngle(s16);
f32 radianAngleReduction(f32 v);
s16 normalizeAngleToRange(f32 v);
s16 radToShortAngle(f32 v);
f32 shortAngleToRad(s16 ang);
f32 shortAngleToRad_Capped(s16);

#endif // !__GAME_MATH_GAME_MATH_H_
