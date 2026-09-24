#ifndef __GAME_BALL_BALL_FIELDER_COLLISION_H_
#define __GAME_BALL_BALL_FIELDER_COLLISION_H_

#include "mssbTypes.h"
#include "Dolphin/vec.h"

struct _DustEmitter;

BOOL fn_3_16C548(struct _DustEmitter* emitter);
void fn_3_16C878(Vec* pos, struct _DustEmitter* emitter, int count);
void fn_3_16CC2C(Vec* pos, u8 source);
u8 checkFielderCollisionPotential(f32 height, u8 fielderIndex);
void processBallFielderCollision(u8 source);

#endif // !__GAME_BALL_BALL_FIELDER_COLLISION_H_
