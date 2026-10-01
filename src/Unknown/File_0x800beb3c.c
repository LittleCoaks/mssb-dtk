#include "Unknown/File_0x800beb3c.h"
#include "Unknown/File_0x800bf038.h"

void fn_800BEB3C(void) {
    drawShadows.pointCount = 0;
    drawShadows.bounds[0][0] = drawShadows.bounds[1][0] = drawShadows.bounds[2][0] = 100000000.0f;
    drawShadows.bounds[0][1] = drawShadows.bounds[1][1] = drawShadows.bounds[2][1] = -100000000.0f;
    drawShadows.pointSum.x = drawShadows.pointSum.y = drawShadows.pointSum.z = 0.0f;
}

MtxPtr returnMtxPtr(u8 index) {
    return drawShadows.camera[index].mtxB0;
}

u8 returnDrawShadows(void) {
    return drawShadows.enabled;
}

u8 GetDrawShadows(void) {
    return drawShadows.enabled;
}

void DrawShadows(u8 enable) {
    drawShadows.enabled = enable;
}

void updateVectorInArray(u8 index, Vec v) {
    drawShadows.camera[index].lightDir = v;
}

void fn_800BEC00(BOOL flag) {
    if (flag) {
        drawShadows.unk4D = -1;
    } else {
        drawShadows.unk4D = 1;
    }
}
