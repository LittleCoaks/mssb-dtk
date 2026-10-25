#include "Unknown/File_0x8000ef1c.h"

void AddVec2iToQuad(f32* quad, Mtx mtx, s32* vec2i) {
    Mtx m;
    f32 pts[4][4];

    PSMTXCopy(mtx, m);
    pts[0][0] = quad[0] + (f32)vec2i[0];
    pts[0][1] = quad[1] + (f32)vec2i[1];
    pts[0][2] = 1.0f;
    pts[1][0] = quad[2] + (f32)vec2i[2];
    pts[1][1] = quad[3] + (f32)vec2i[3];
    pts[1][2] = 1.0f;
    pts[2][0] = quad[4] + (f32)vec2i[4];
    pts[2][1] = quad[5] + (f32)vec2i[5];
    pts[2][2] = 1.0f;
    pts[3][0] = quad[6] + (f32)vec2i[6];
    pts[3][1] = quad[7] + (f32)vec2i[7];
    pts[3][2] = 1.0f;

    PSMTXMultVec(m, (Vec*)pts[0], (Vec*)pts[0]);
    PSMTXMultVec(m, (Vec*)pts[1], (Vec*)pts[1]);
    PSMTXMultVec(m, (Vec*)pts[2], (Vec*)pts[2]);
    PSMTXMultVec(m, (Vec*)pts[3], (Vec*)pts[3]);

    quad[0] = pts[0][0];
    quad[1] = pts[0][1];
    quad[2] = pts[0][2];
    quad[4] = pts[1][0];
    quad[5] = pts[1][1];
    quad[6] = pts[1][2];
    quad[8] = pts[2][0];
    quad[9] = pts[2][1];
    quad[10] = pts[2][2];
    quad[12] = pts[3][0];
    quad[13] = pts[3][1];
    quad[14] = pts[3][2];
}
