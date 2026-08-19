#ifndef __GAME_BALL_FOUL_DETECTION_H_
#define __GAME_BALL_FOUL_DETECTION_H_

#include "mssbTypes.h"

void fn_3_B79AC(void);
void checkFielderCollision(void);
void isCoordinateUncatchableTerrain(void);
void foul_isBallWithin3mFair(void);
void foul_ifBallConsideredPastTheBases(void);
void foul_checkIfFoul(void);
void fn_3_B7E44(void);

#endif // !__GAME_BALL_FOUL_DETECTION_H_
