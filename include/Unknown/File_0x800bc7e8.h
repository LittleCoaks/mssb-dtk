#ifndef __UNKNOWN_FILE_0X800BC7E8_H_
#define __UNKNOWN_FILE_0X800BC7E8_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

struct DODisplayObj;

void DOVARenderSkin(struct DODisplayObj* dispObj, MtxPtr camera, MtxPtr mtxArray, MtxPtr invTransposeMtxArray,
                    u8 numLights, void* list);

#endif // !__UNKNOWN_FILE_0X800BC7E8_H_
