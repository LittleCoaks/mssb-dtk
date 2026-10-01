#include "Unknown/File_0x80064344.h"
#include "Unknown/File_0x8004c094.h"
#include "Dolphin/mtx.h"
#include "string.h"

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
