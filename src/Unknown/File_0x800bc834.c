#include "Unknown/File_0x800bc834.h"
#include "C3/charPipeline.h"

void DOSetWorldMatrix(struct DODisplayObj* dispObj, MtxPtr m) {
    PSMTXCopy(m, dispObj->worldMatrix);
}
