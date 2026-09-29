#include "Unknown/File_0x80052694.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/gx.h"

void setScissorAndProjection(int mode) {
    if (mode < 0) {
        mode = 0;
    } else if (mode >= 2) {
        mode = 1;
    }
    currentMode = mode;
    GXSetProjection((&cameras[2])[mode].proj, GX_PERSPECTIVE);
    if (scissorMode == 1) {
        GXSetScissor(0, 0, 640, 448);
    } else if (scissorMode == 2) {
        GXSetScissor(mode * 320, 0, 320, 448);
    }
}
