#include "Unknown/File_0x8001d0d0.h"
#include "C3/control.h"
#include "HugeAnimStruct.h"


void applyUniformScaleToObject(f32 scale, int model) {
    CTRLSetScale((Control*)(((u8*)hugeAnimStruct.actorTables[2]) + model * 0x90 + 0x44), scale, scale, scale);
}
