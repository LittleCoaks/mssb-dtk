#ifndef __GAME_MINIGAME_WALL_BALL_H_
#define __GAME_MINIGAME_WALL_BALL_H_

#include "mssbTypes.h"

typedef enum _WALL_BALL_AI_STATE {
    WALL_BALL_AI_STATE_CALCULATE_PITCH = 0,
    WALL_BALL_AI_STATE_WAIT_FOR_PITCH = 1,
    WALL_BALL_AI_STATE_PERFECT_PITCH = 2,
    WALL_BALL_AI_STATE_PERFECT_PITCH_FILL_BAR = 3,
    WALL_BALL_AI_STATE_OVERCHARGE = 4,
    WALL_BALL_AI_STATE_OVERCHARGE_HOLD_A = 5,
    WALL_BALL_AI_STATE_CHARGE_PITCH = 6,
    WALL_BALL_AI_STATE_CHARGE_PITCH_CHARGE_UP_BAR = 7,
    WALL_BALL_AI_STATE_CURVE_BALL = 8,
    WALL_BALL_AI_STATE_UNKNOWN_9 = 9
} WALL_BALL_AI_STATE;

typedef enum _WALL_BALL_AI_THROW_TYPE {
    WALL_BALL_AI_THROW_TYPE_PERFECT = 0,
    WALL_BALL_AI_THROW_TYPE_OVERCHARGE = 1,
    WALL_BALL_AI_THROW_TYPE_CHARGE = 2,
    WALL_BALL_AI_THROW_TYPE_CURVE_BALL = 3
} WALL_BALL_AI_THROW_TYPE;

void wallBallMultiplayer_AIControl(void);
void wallBallAIPitches(void);
void wallBallClearInputs(void);
void wallBallUpdateCoins(void);
void wallBallCalc_WallsBroken(void);
void wallBallUpdateWallWobble(void);
void wallBallBounceBallOffWall(void);
void wallBallHandleWallHit(void);
void wallBallDropInNewWalls(void);
void wallBallCalculateNewWalls(void);
int wallBallCompareWalls(const u8* first, const u8* second);
void wallBallUpdateWalls(void);
void wallBallRotatePitchers(int force);

#endif // !__GAME_MINIGAME_WALL_BALL_H_
