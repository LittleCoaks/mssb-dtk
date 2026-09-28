#ifndef __GAME_BALL_FOUL_DETECTION_H_
#define __GAME_BALL_FOUL_DETECTION_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"

f32 fn_3_B79AC(f32 x, f32 z);
BOOL checkFielderCollision(InMemFielder* fielder, VecXYZ* pos);
BOOL isCoordinateUncatchableTerrain(f32 x, f32 z);
BOOL foul_isBallWithin3mFair(f32 x, f32 z);
BOOL foul_ifBallConsideredPastTheBases(f32 x, f32 z);
BOOL foul_checkIfFoul(f32 x, f32 z);
int fn_3_B7E44(f32 dist, sAng angle);

#endif // !__GAME_BALL_FOUL_DETECTION_H_
