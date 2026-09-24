#ifndef __GAME_BASERUNNING_RUNNER_BASE_ROUNDING_H_
#define __GAME_BASERUNNING_RUNNER_BASE_ROUNDING_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"

f32 spline_evaluate(f32 frame, const f32* timings, const f32* values, const f32* curvature, int keyCount);
void spline_computeSecondDerivatives(f32* timings, f32* values, f32* curve, s32 count);
void spline2D_evaluate(f32 frame, VecXZ* out, const f32* valuesX, const f32* valuesZ, const f32* timings,
                const f32* curvatureX, const f32* curvatureZ, int keyCount);
void spline2D_build(f32* valuesX, f32* valuesZ, f32* timings, f32* curveX, f32* curveZ, s32 count);
void running_roundBasePosition(f32 frame, VecXZ* outPos, VecXZ* points, int count);
void spline3D_evaluate(Vec* out, Vec* points, int count, f32 t);
void fn_3_2D6C(Vec* out, void* list, int outCount);
void spline3D_resample(Vec* out, Vec* points, int count, int outCount);

#endif // !__GAME_BASERUNNING_RUNNER_BASE_ROUNDING_H_
