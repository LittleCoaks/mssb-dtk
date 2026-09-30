#include "Unknown/File_0x800bf204.h"
#include "Dolphin/PPCArch.h"
#include "Dolphin/OS/OSCache.h"
#include "C3/actor.h"
#include "C3/skinning.h"

void SKNInit(void) {
    if (!(PPCMfhid2() & 0x10000000)) {
        DCInvalidateRange((void*)LC_BASE, 0x4000);
        LCEnable();
    }

    SKBuffers[0] = (void*)LC_BASE;
    SKBuffers[1] = (void*)(LC_BASE + 0x1000);
    SKBuffers[2] = (void*)(LC_BASE + 0x2000);
    SKBuffers[3] = (void*)(LC_BASE + 0x3000);

    SKAccBuffers[0].src = (s16*)LC_BASE;
    SKAccBuffers[0].indices = (u16*)(LC_BASE + 0x1000);
    SKAccBuffers[0].weights = (u8*)(LC_BASE + 0x1800);
    SKAccBuffers[1].src = (s16*)(LC_BASE + 0x2000);
    SKAccBuffers[1].indices = (u16*)(LC_BASE + 0x3000);
    SKAccBuffers[1].weights = (u8*)(LC_BASE + 0x3800);

    GQRSetup5(8, 4, 8, 4);
}
