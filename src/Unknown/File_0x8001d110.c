#include "Unknown/File_0x8001d110.h"
#include "C3/control.h"
#include "HugeAnimStruct.h"


void applyNonUniformScaleToObject(f32 x, f32 y, f32 z, int model) {
    CTRLSetScale((Control*)(((u8*)hugeAnimStruct.actorTables[2]) + model * 0x90 + 0x44), x, y, z);
}
