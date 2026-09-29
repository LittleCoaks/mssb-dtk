#include "Unknown/File_0x800bd3a0.h"
#include "C3/charPipeline.h"

void LITInitColor(void* light, GXColor* color) {
    ((Light*)light)->color = *color;
}

void LITInitDir(void* light, f32 x, f32 y, f32 z) {
    ((Light*)light)->direction.x = x;
    ((Light*)light)->direction.y = y;
    ((Light*)light)->direction.z = z;
}

void LITInitPos(void* light, f32 x, f32 y, f32 z) {
    ((Light*)light)->position.x = x;
    ((Light*)light)->position.y = y;
    ((Light*)light)->position.z = z;
}
