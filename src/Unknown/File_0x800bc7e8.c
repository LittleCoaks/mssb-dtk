#include "Unknown/File_0x800bc7e8.h"
#include "Unknown/File_0x800bc0c4.h"

void DOVARenderSkin(struct DODisplayObj* dispObj, MtxPtr camera, MtxPtr mtxArray, MtxPtr invTransposeMtxArray,
                    u8 numLights, void* list) {
    SkinForwardArray = mtxArray;
    SkinInverseArray = invTransposeMtxArray;
    DOVARender(dispObj, camera, numLights, list);
    SkinForwardArray = NULL;
    SkinInverseArray = NULL;
}
