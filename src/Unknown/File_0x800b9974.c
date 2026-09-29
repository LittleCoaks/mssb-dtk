#include "Unknown/File_0x800b9974.h"
#include "Dolphin/GX/GXPixel.h"

void SetFogNone(void) {
    GXColor color;

    color.r = color.g = color.b = 0;
    GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, color);
}
