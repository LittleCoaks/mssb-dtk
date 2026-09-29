#include "Unknown/File_0x800bd2b0.h"

extern u8 maybeDoLighting;
extern GXColor lightingDataArray;

u8 lightingRelated(GXColor* color) {
    if (maybeDoLighting) {
        *color = lightingDataArray;
    }
    return maybeDoLighting;
}

void adjustLightingParams(u8 enable, GXColor color) {
    maybeDoLighting = enable;
    lightingDataArray = color;
}

void fn_800BD2DC(void) {
    maybeDoLighting = 0;
    lightingDataArray.r = 0;
    lightingDataArray.b = 0;
    lightingDataArray.g = 0;
    lightingDataArray.a = 0xFF;
}
