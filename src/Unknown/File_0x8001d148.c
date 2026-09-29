#include "Unknown/File_0x8001d148.h"
#include "C3/control.h"

extern struct {
    u8 _00[0x64];
    u8* balls;
} hugeAnimStruct;

void baseballCTRLSetScale(f32 x, f32 y, f32 z, int model) {
    CTRLSetScale((Control*)(hugeAnimStruct.balls + model * 0x90 + 0x44), x, y, z);
}
