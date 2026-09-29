#include "Unknown/File_0x800b9a30.h"
#include "Unknown/File_0x800b99c4.h"

extern const f32 lbl_803CCFFC;

void SetFogNoneAgain(void) {
    fogSettings.color.r = fogSettings.color.g = fogSettings.color.b = 0;
    fogSettings.type = GX_FOG_NONE;
    fogSettings.startZ = lbl_803CCFFC;
    fogSettings.endZ = lbl_803CCFFC;
    fogSettings.nearZ = lbl_803CCFFC;
    fogSettings.farZ = lbl_803CCFFC;
    GXSetFog(GX_FOG_NONE, lbl_803CCFFC, lbl_803CCFFC, lbl_803CCFFC, lbl_803CCFFC, fogSettings.color);
}
