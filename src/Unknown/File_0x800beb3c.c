#include "Unknown/File_0x800beb3c.h"
#include "Unknown/File_0x800bf038.h"

void fn_800BEB3C(void) {
    drawShadows.unk24 = 0;
    drawShadows.unk28[0][0] = drawShadows.unk28[1][0] = drawShadows.unk28[2][0] = 100000000.0f;
    drawShadows.unk28[0][1] = drawShadows.unk28[1][1] = drawShadows.unk28[2][1] = -100000000.0f;
    drawShadows.unk40.x = drawShadows.unk40.y = drawShadows.unk40.z = 0.0f;
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
