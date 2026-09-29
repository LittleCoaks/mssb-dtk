#include "Unknown/File_0x8001d110.h"
#include "C3/control.h"

extern struct {
    u8 _00[0x68];
    u8* models;
} hugeAnimStruct;

void applyNonUniformScaleToObject(f32 x, f32 y, f32 z, int model) {
    CTRLSetScale((Control*)(hugeAnimStruct.models + model * 0x90 + 0x44), x, y, z);
}
