#include "Unknown/File_0x800bd3cc.h"
#include "C3/charPipeline.h"

void LITInitAttn(void* light, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2) {
    GXInitLightAttn(&((Light*)light)->lt_obj, a0, a1, a2, k0, k1, k2);
}
