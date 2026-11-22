#include "Unknown/File_0x80064344.h"
#include "Unknown/File_0x8004c094.h"
#include "Dolphin/mtx.h"
#include "string.h"
#include "Unknown/File_0x80064430.h"

// 0x800639BC-0x80064534: one translation unit by its literal pool and .data
// (docs/splits.md, 2026-11-21): fn_800639BC (no C yet) plus the former
// File_0x80064344.c and File_0x80064430.c.

extern EffectSpawnParams lbl_80108D48;

void handleBallRollInWater(Vec* pos, Vec* vel) {
    f32 scale = 3.0f * PSVECMag(vel);
    EffectSpawnParams params;

    memcpy(&params, &lbl_80108D48, sizeof(params));
    params.texture = lbl_803CBD0C;
    params.unk14[0] *= scale;
    params.unk14[1] *= scale;
    params.unk14[2] *= scale;
    params.unk14[3] *= scale;
    params.unk14[4] *= scale;
    params.unk14[5] *= scale;
    params.unk38 *= scale;
    params.unk54[0] *= scale;
    params.unk54[1] *= scale;
    params.unk54[2] *= scale;
    fn_8002B7F8(pos, &params, 1);
}

void spawnDustPuff(Vec* pos, int type, f32 size, f32 height) {
    EffectSpawnParams params;

    memcpy(&params, &lbl_80108D48, sizeof(params));
    params.texture = lbl_803CBD0C;
    params.unk14[0] *= height;
    params.unk14[1] *= height;
    params.unk14[2] *= height;
    params.unk14[3] *= height;
    params.unk14[4] *= height;
    params.unk14[5] *= height;
    params.unk38 *= height;
    params.unk54[0] *= size;
    params.unk54[1] *= size;
    params.unk54[2] *= size;
    fn_8002B7F8(pos, &params, type);
}
