#ifndef __GAME_BASERUNNING_RUNNER_BASE_ROUNDING_H_
#define __GAME_BASERUNNING_RUNNER_BASE_ROUNDING_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"

f32 fn_3_14A4(f32 frame, const f32* timings, const f32* values, const f32* curvature, int keyCount);
void fn_3_155C(f32* timings, f32* values, f32* curve, s32 count);
void fn_3_19B0_(f32 frame, VecXZ* out, const f32* valuesX, const f32* valuesZ, const f32* timings,
                const f32* curvatureX, const f32* curvatureZ, int keyCount);
void fn_3_1B24(f32* valuesX, f32* valuesZ, f32* timings, f32* curveX, f32* curveZ, s32 count);
void running_roundBasePosition(f32 frame, VecXZ* outPos, VecXZ* points, int count);
void fn_3_28E4(Vec*, Vec* arr, int count, f32 f1);
void fn_3_2D6C(void);
void fn_3_310C(void);

#endif // !__GAME_BASERUNNING_RUNNER_BASE_ROUNDING_H_
