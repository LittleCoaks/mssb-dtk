#include "Unknown/File_0x800249d8.h"

static inline u32 scaleChannel(u32 factor, u32 channel) {
    int c = (u8)channel;
    int f = (u8)factor;
    return (int)(f * (c / 255.0f));
}

u32 byteWiseMultiply(u32 scale, u32 color) {
    return scaleChannel(scale, color) | (scaleChannel(scale, color >> 8) << 8) |
           (scaleChannel(scale, color >> 16) << 16) | (scaleChannel(scale, color >> 24) << 24);
}
