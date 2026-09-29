#include "Unknown/File_0x800b9974.h"
#include "Dolphin/GX/GXPixel.h"

extern const f32 lbl_803CCFFC;

void SetFogNone(void) {
    GXColor color;

    color.r = color.g = color.b = 0;
    GXSetFog(GX_FOG_NONE, lbl_803CCFFC, lbl_803CCFFC, lbl_803CCFFC, lbl_803CCFFC, color);
}
