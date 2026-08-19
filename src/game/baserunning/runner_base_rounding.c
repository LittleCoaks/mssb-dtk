#include "game/baserunning/runner_base_rounding.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"


// .text:0x0000310C size:0x4C8 mapped:0x806421A0
void fn_3_310C(void) {
    return;
}

// .text:0x00002D6C size:0x3A0 mapped:0x80641E00
void fn_3_2D6C(void) {
    return;
}

// .text:0x000028E4 size:0x488 mapped:0x80641978
void fn_3_28E4(Vec*, Vec* arr, int count, f32 f1) {
    return;
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
    fn_3_1B24(valuesX, valuesZ, timings, curveX, curveZ, count);
    fn_3_19B0_(frame, outPos, valuesX, valuesZ, timings, curveX, curveZ, count);
}

inline void fn_3_1B24_inline(f32* values, f32* timings, f32* curve, s32 count)
{
    s32 i;
    float sp98[17];
    float spd4[17];
    curve[0] = 0.f;
    curve[count - 1] = 0.f;
    {
        // s32 i;
        for (i = 0; i < count - 1; i++) {
            sp98[i] = timings[i + 1] - timings[i];
            spd4[i + 1] = (values[i + 1] - values[i]) / sp98[i];
        }
    }
    
    curve[1] = (spd4[2] - spd4[1]) - (sp98[0] * curve[0]);
    spd4[1] = 2.f * (timings[2] - timings[0]);
    {
        // int i;   
        for (i = 1; i < count - 2; i++) {
            f32 f = (sp98[i] / spd4[i]);
            curve[i + 1] = (spd4[i + 2] - spd4[i + 1]) - (f * curve[i]);
            spd4[i + 1] = (2.f * (timings[i + 2] - timings[i])) - (f * sp98[i]);
        }
    }

    curve[count - 2] -= (sp98[count - 2] * curve[count - 1]);

    {
        // int i;
        for (i = count - 2; i > 0; i--) {
            curve[i] = (curve[i] - sp98[i] * curve[i + 1]) / spd4[i];
        }
    }
}

// .text:0x00001B24 size:0xABC mapped:0x80640BB8
void fn_3_1B24(f32* valuesX, f32* valuesZ, f32* timings, f32* curveX, f32* curveZ, s32 count) {
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

    fn_3_155C(timings, valuesX, curveX, count);
    fn_3_155C(timings, valuesZ, curveZ, count);
}

// .text:0x000019B0 size:0x174 mapped:0x80640A44
void fn_3_19B0(f32 distance, VecXZ* out, const f32* valuesX, const f32* valuesZ, const f32* endLengths,
                const f32* curvatureX, const f32* curvatureZ, int keyCount) {
    out->x = fn_3_14A4(distance, endLengths, valuesX, curvatureX, keyCount);
    out->z = fn_3_14A4(distance, endLengths, valuesZ, curvatureZ, keyCount);
}

// .text:0x0000155C size:0x454 mapped:0x806405F0
void fn_3_155C(f32* timings, f32* values, f32* curve, s32 count) {
    s32 i;
    float sp98[17];
    float spd4[17];
    curve[0] = 0.f;
    curve[count - 1] = 0.f;
    {
        // s32 i;
        for (i = 0; i < count - 1; i++) {
            sp98[i] = timings[i + 1] - timings[i];
            spd4[i + 1] = (values[i + 1] - values[i]) / sp98[i];
        }
    }
    
    curve[1] = (spd4[2] - spd4[1]) - (sp98[0] * curve[0]);
    spd4[1] = 2.f * (timings[2] - timings[0]);
    {
        // int i;   
        for (i = 1; i < count - 2; i++) {
            f32 f = (sp98[i] / spd4[i]);
            curve[i + 1] = (spd4[i + 2] - spd4[i + 1]) - (f * curve[i]);
            spd4[i + 1] = (2.f * (timings[i + 2] - timings[i])) - (f * sp98[i]);
        }
    }

    curve[count - 2] -= (sp98[count - 2] * curve[count - 1]);

    {
        // int i;
        for (i = count - 2; i > 0; i--) {
            curve[i] = (curve[i] - sp98[i] * curve[i + 1]) / spd4[i];
        }
    }
}

// .text:0x000014A4 size:0xB8 mapped:0x80640538
f32 fn_3_14A4(f32 distance, const f32* endLengths, const f32* values, const f32* curvature, int keyCount) {
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
        f32 linearCoeffecient = -(intervalLength * (2.0f * curvature[segment] + curvature[segment + 1]) - (values[segment + 1] - values[segment]) / intervalLength);

        return values[segment] + localTime * (localTime * (3.0f * curvature[segment] + (localTime * (curvature[segment + 1] - curvature[segment])) / intervalLength) + linearCoeffecient);
    }
}
