#ifndef __GAME_BALL_FOUL_DETECTION_H_
#define __GAME_BALL_FOUL_DETECTION_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"

f32 distanceFromPointToWall(f32 x, f32 z);
BOOL checkFielderCollision(InMemFielder* fielder, VecXYZ* pos);
BOOL isCoordinateUncatchableTerrain(f32 x, f32 z);
BOOL foul_isBallWithin3mFair(f32 x, f32 z);
BOOL foul_ifBallConsideredPastTheBases(f32 x, f32 z);
BOOL foul_checkIfFoul(f32 x, f32 z);
int outfieldWallProximityZone(f32 dist, sAng angle);

#endif // !__GAME_BALL_FOUL_DETECTION_H_
