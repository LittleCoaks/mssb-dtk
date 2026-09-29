#include "Unknown/File_0x800bf008.h"
#include "Unknown/File_0x800bf038.h"
#include "Dolphin/gx.h"

void loadTlutRelated(void) {
    GXLoadTlut(drawShadows.tlut, GX_TLUT15);
}
