#include "Unknown/File_0x80064430.h"
#include "Unknown/File_0x80064344.h"
#include "Unknown/File_0x8004c094.h"
#include "string.h"

extern EffectSpawnParams lbl_80108D48;

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
