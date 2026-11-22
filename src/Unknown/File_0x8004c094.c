#include "Unknown/File_0x8004c094.h"
#include "Dolphin/stl.h"

// 0x8004C094-0x8004C5F8: one translation unit by its .sdata and literal pool
// (docs/splits.md, 2026-11-21): spawnDust plus fn_8004C108, fn_8004C19C and
// fn_8004C510, which have no C yet.

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
