#include "Unknown/File_0x80052734.h"
#include "Unknown/File_0x80052694.h"

camera_803c639c_s* returnFloatFromModeIndex(int mode) {
    if (mode < 0) {
        mode = 0;
    } else if (mode >= 2) {
        mode = 1;
    }
    return &cameras[mode] + 2;
}

camera_803c639c_s* fn_80052768_getCamera(int mode) {
    if (mode < 0) {
        mode = 0;
    } else if (mode >= 2) {
        mode = 1;
    }
    return &cameras[mode];
}

void setScissorMode(int mode) {
    if (mode < 1) {
        mode = 1;
    } else if (mode > 2) {
        mode = 2;
    }
    scissorMode = mode;
}

int returnScissorMode(void) {
    return scissorMode;
}
