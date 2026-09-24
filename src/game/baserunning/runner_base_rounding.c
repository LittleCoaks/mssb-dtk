#define SQRT2_LINKAGE static
#include "game/baserunning/runner_base_rounding.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"

extern BOOL fn_80023DFC(void* list, Vec* out);
extern BOOL fn_80023D98(void* list, Vec* out);

// .text:0x0000310C size:0x4C8 mapped:0x806421A0
void spline3D_resample(Vec* out, Vec* points, int count, int outCount) {
    int i;
    f32 timings[2][17];
    f32 curveA[2][17];
    f32 curveB[2][17];
    f32 xs[17];
    f32 ys[17];
    f32 zs[17];
    VecXZ tmp;

    for (i = 0; i < count; i++) {
        xs[i] = points[i].x;
        ys[i] = points[i].y;
        zs[i] = points[i].z;
    }
    spline2D_build(xs, ys, timings[0], curveA[0], curveB[0], count);
    spline2D_build(xs, zs, timings[1], curveA[1], curveB[1], count);
    for (i = 0; i < outCount; i++) {
        f32 t = (f32)i / (f32)(outCount - 1);
        spline2D_evaluate(t, &tmp, xs, ys, timings[0], curveA[0], curveB[0], count);
        out[i].x = tmp.x;
        out[i].y = tmp.z;
        spline2D_evaluate(t, &tmp, xs, zs, timings[1], curveA[1], curveB[1], count);
        out[i].z = tmp.z;
    }
}

// .text:0x00002D6C size:0x3A0 mapped:0x80641E00
void fn_3_2D6C(Vec* out, void* list, int outCount) {
    int i;
    int n;
    f32 timings[2][17];
    f32 curveA[2][17];
    f32 curveB[2][17];
    f32 xs[17];
    f32 ys[17];
    f32 zs[17];
    Vec p;
    VecXZ tmp;

    if (list == NULL) {
        return;
    }
    n = ((s32*)list)[2];

    i = 0;
    fn_80023DFC(list, &p);
    do {
        xs[i] = p.x;
        ys[i] = p.y;
        zs[i] = p.z;
        i++;
    } while (fn_80023D98(list, &p));

    spline2D_build(xs, ys, timings[0], curveA[0], curveB[0], n);
    spline2D_build(xs, zs, timings[1], curveA[1], curveB[1], n);
    for (i = 0; i < outCount; i++) {
        f32 t = (f32)i / (f32)(outCount - 1);
        spline2D_evaluate(t, &tmp, xs, ys, timings[0], curveA[0], curveB[0], n);
        out[i].x = tmp.x;
        out[i].y = tmp.z;
        spline2D_evaluate(t, &tmp, xs, zs, timings[1], curveA[1], curveB[1], n);
        out[i].z = tmp.z;
    }
}

// .text:0x000028E4 size:0x488 mapped:0x80641978
void spline3D_evaluate(Vec* out, Vec* points, int count, f32 t) {
    int i;
    f32 xs[17];
    f32 ys[17];
    f32 zs[17];
    f32 timings[17];
    f32 curveA[17];
    f32 curveB[17];
    VecXZ tmp;

    for (i = 0; i < count; i++) {
        xs[i] = points[i].x;
        ys[i] = points[i].y;
        zs[i] = points[i].z;
    }
    spline2D_build(xs, ys, timings, curveA, curveB, count);
    spline2D_evaluate(t, &tmp, xs, ys, timings, curveA, curveB, count);
    out->x = tmp.x;
    out->y = tmp.z;
    spline2D_build(xs, zs, timings, curveA, curveB, count);
    spline2D_evaluate(t, &tmp, xs, zs, timings, curveA, curveB, count);
    out->z = tmp.z;
}

// .text:0x000025E0 size:0x304 mapped:0x80641674
void running_roundBasePosition(f32 frame, VecXZ* outPos, VecXZ* points, int count) {
    int i;
    f32 valuesX[17];
    f32 valuesZ[17];
    f32 timings[17];
    f32 curveX[17];
    f32 curveZ[17];
    for (i = 0; i < count; i++) {
        valuesX[i] = points[i].x;
        valuesZ[i] = points[i].z;
    }
    spline2D_build(valuesX, valuesZ, timings, curveX, curveZ, count);
    spline2D_evaluate(frame, outPos, valuesX, valuesZ, timings, curveX, curveZ, count);
}

// .text:0x00001B24 size:0xABC mapped:0x80640BB8
void spline2D_build(f32* valuesX, f32* valuesZ, f32* timings, f32* curveX, f32* curveZ, s32 count) {
    int i;

    timings[0] = 0.f;
    for (i = 1; i < count; i++) {
        f32 x = valuesX[i] - valuesX[i - 1];
        f32 z = valuesZ[i] - valuesZ[i - 1];
        timings[i] = timings[i - 1] + dolsqrtf2(SQ(x) + SQ(z));
    }
    for (i = 1; i < count; i++) {
        timings[i] /= timings[count - 1];
    }

    spline_computeSecondDerivatives(timings, valuesX, curveX, count);
    spline_computeSecondDerivatives(timings, valuesZ, curveZ, count);
}

// .text:0x000019B0 size:0x174 mapped:0x80640A44
void spline2D_evaluate(f32 distance, VecXZ* out, const f32* valuesX, const f32* valuesZ, const f32* endLengths,
                const f32* curvatureX, const f32* curvatureZ, int keyCount) {
    out->x = spline_evaluate(distance, endLengths, valuesX, curvatureX, keyCount);
    out->z = spline_evaluate(distance, endLengths, valuesZ, curvatureZ, keyCount);
}

// .text:0x0000155C size:0x454 mapped:0x806405F0
void spline_computeSecondDerivatives(f32* timings, f32* values, f32* curve, s32 count) {
    s32 i;
    float sp98[17];
    float spd4[17];
    curve[0] = 0.f;
    curve[count - 1] = 0.f;
    {
        for (i = 0; i < count - 1; i++) {
            sp98[i] = timings[i + 1] - timings[i];
            spd4[i + 1] = (values[i + 1] - values[i]) / sp98[i];
        }
    }

    curve[1] = (spd4[2] - spd4[1]) - (sp98[0] * curve[0]);
    spd4[1] = 2.f * (timings[2] - timings[0]);
    {
        for (i = 1; i < count - 2; i++) {
            f32 f = (sp98[i] / spd4[i]);
            curve[i + 1] = (spd4[i + 2] - spd4[i + 1]) - (f * curve[i]);
            spd4[i + 1] = (2.f * (timings[i + 2] - timings[i])) - (f * sp98[i]);
        }
    }

    curve[count - 2] -= (sp98[count - 2] * curve[count - 1]);

    {
        for (i = count - 2; i > 0; i--) {
            curve[i] = (curve[i] - sp98[i] * curve[i + 1]) / spd4[i];
        }
    }
}

// .text:0x000014A4 size:0xB8 mapped:0x80640538
f32 spline_evaluate(f32 distance, const f32* endLengths, const f32* values, const f32* curvature, int keyCount) {
    int segment = 0;
    int end = keyCount - 1;
    while (segment < end) {
        int half = (segment + end) / 2;
        if (endLengths[half] < distance) {
            segment = half + 1;
        } else {
            end = half;
        }
    }
    if (segment > 0) {
        segment--;
    }
    
    {
        f32 localTime = distance - endLengths[segment];
        f32 intervalLength = endLengths[segment + 1] - endLengths[segment];

        return values[segment] + localTime * (localTime * (3.0f * curvature[segment] + (localTime * (curvature[segment + 1] - curvature[segment])) / intervalLength) + ((values[segment + 1] - values[segment]) / intervalLength - intervalLength * (2.0f * curvature[segment] + curvature[segment + 1])));
    }
}
