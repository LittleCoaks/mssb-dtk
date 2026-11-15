#include "Unknown/File_0x8001d148.h"
#include "C3/control.h"
#include "HugeAnimStruct.h"


void baseballCTRLSetScale(f32 x, f32 y, f32 z, int model) {
    CTRLSetScale((Control*)(((u8*)hugeAnimStruct.actorTables[1]) + model * 0x90 + 0x44), x, y, z);
}
