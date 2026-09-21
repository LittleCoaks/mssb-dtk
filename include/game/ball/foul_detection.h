#ifndef __GAME_BALL_FOUL_DETECTION_H_
#define __GAME_BALL_FOUL_DETECTION_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"

void fn_3_B79AC(void);
int checkFielderCollision(InMemFielder* fielder, VecXYZ* pos);
int isCoordinateUncatchableTerrain(f32 x, f32 z);
int foul_isBallWithin3mFair(f32 x, f32 z);
int foul_ifBallConsideredPastTheBases(f32 x, f32 z);
int foul_checkIfFoul(f32 x, f32 z);
int fn_3_B7E44(f32 dist, sAng angle);

#endif // !__GAME_BALL_FOUL_DETECTION_H_
