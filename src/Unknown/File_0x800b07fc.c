#include "Unknown/File_0x800b07fc.h"
#include "musyx/musyx.h"

extern void* SndAlloc(u32 len);
extern void fn_800B0934(void* addr);

void soundQuit(void) {
    SND_HOOKS hooks = {SndAlloc, fn_800B0934};
    sndSetHooks(&hooks);
    sndQuit();
}
