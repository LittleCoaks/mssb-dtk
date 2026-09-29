#include "Unknown/File_0x80024974.h"

u32 multBottomBits_asFloat(u32 value, u32 scale) {
    int s = (u8)scale;
    int v = (u8)value;
    return (value & ~0xFF) | (int)(v * (s / 255.0f));
}
