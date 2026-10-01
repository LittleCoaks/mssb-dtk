#include "Unknown/File_0x800b0724.h"

void makeLookAtMatrix(Mtx m, Vec* camPos, Vec* camUp, Vec* target) {
    f32 negOne;
    f32 zero;

    if (camPos->x == target->x && camPos->z == target->z) {
        negOne = -1.0f;
        zero = 0.0f;
        m[0][0] = negOne;
        m[0][1] = zero;
        m[0][2] = zero;
        m[0][3] = camPos->x;
        if (camPos->y - target->y <= zero) {
            m[1][0] = zero;
            m[1][1] = zero;
            m[1][2] = negOne;
            m[1][3] = camPos->z;
            m[2][0] = zero;
            m[2][1] = negOne;
            m[2][2] = zero;
            m[2][3] = camPos->y;
        } else {
            m[1][0] = zero;
            m[1][1] = zero;
            m[1][2] = 1.0f;
            m[1][3] = -camPos->z;
            m[2][0] = zero;
            m[2][1] = 1.0f;
            m[2][2] = zero;
            m[2][3] = -camPos->y;
        }
    } else {
        C_MTXLookAt(m, camPos, camUp, target);
    }
}
