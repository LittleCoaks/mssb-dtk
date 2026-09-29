#include "Unknown/File_0x8004c094.h"
#include "Dolphin/stl.h"

void spawnDust(Vec* pos) {
    ParticleBurstParams params;
    ParticleBurstParams* p = &params;

    if (pos != NULL) {
        memcpy(p, lbl_803CB860, sizeof(ParticleBurstParams));
        p->texture = lbl_803CBD0C;
        p->unkC = 120000;
        p->unk10 = 60000;
        fn_80031CA4(pos, p);
    }
}
