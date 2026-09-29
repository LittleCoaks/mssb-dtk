#include "Unknown/File_0x8001d0d0.h"
#include "C3/control.h"

extern struct {
    u8 _00[0x68];
    u8* models;
} hugeAnimStruct;

void applyUniformScaleToObject(f32 scale, int model) {
    CTRLSetScale((Control*)(hugeAnimStruct.models + model * 0x90 + 0x44), scale, scale, scale);
}
