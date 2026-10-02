#include "Unknown/File_0x80023b90.h"
#include "Dolphin/mtx.h"

typedef struct {
    /* 0x0 */ u16 height;
    /* 0x2 */ u16 pitch;
    /* 0x4 */ u16 yaw;
    /* 0x6 */ u8 r;
    /* 0x7 */ u8 g;
    /* 0x8 */ u8 b;
} LightParams;

typedef struct {
    /* 0x0 */ Vec pos;
    /* 0xC */ u8 r;
    /* 0xD */ u8 g;
    /* 0xE */ u8 b;
} LightResult;

void characterLightingRelated(void* input, void* output) {
    LightParams* in = input;
    LightResult* out = output;
    Vec xAxis = {1.0f, 0.0f, 0.0f};
    Vec yAxis = {0.0f, 1.0f, 0.0f};
    Mtx m;
    Mtx rot;

    PSMTXRotAxisRad(rot, &xAxis, 3.1415925f * in->pitch / 2048.0f);
    PSMTXConcat(m, rot, m);
    PSMTXRotAxisRad(m, &yAxis, 3.1415925f * (in->yaw + 0x800) / 2048.0f);
    PSMTXConcat(m, rot, m);
    yAxis.y = in->height;
    PSMTXMultVec(m, &yAxis, &yAxis);
    out->pos.x = yAxis.x;
    out->pos.y = yAxis.y;
    out->pos.z = yAxis.z;
    out->r = in->r;
    out->g = in->g;
    out->b = in->b;
}
