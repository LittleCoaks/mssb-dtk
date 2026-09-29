#include "Unknown/File_0x800b99c4.h"

void SetFog(GXFogType type, f32 startZ, f32 endZ, f32 nearZ, f32 farZ, GXColor color) {
    fogSettings.type = type;
    fogSettings.startZ = startZ;
    fogSettings.endZ = endZ;
    fogSettings.nearZ = nearZ;
    fogSettings.farZ = farZ;
    fogSettings.color = color;
    GXSetFog(type, (f64)startZ, (f64)endZ, (f64)nearZ, (f64)farZ, color);
}
