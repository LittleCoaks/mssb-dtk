#include "Unknown/File_0x800bf038.h"

void maybeUpdateFunctionPointer(void (*func)(void)) {
    drawShadows.callback20 = func;
}

void fn_800BF048(void (*func)(void)) {
    drawShadows.callback18 = func;
}

void fn_800BF058(void (*func)(StadiumModel* model, Mtx m)) {
    drawShadows.modelCallback = func;
}

ShadowState* ShouldDrawShadows(void) {
    return &drawShadows;
}
