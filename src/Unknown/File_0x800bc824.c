#include "Unknown/File_0x800bc824.h"
#include "C3/charPipeline.h"

void updateMemoryLocation(struct DODisplayObj* dispObj, void* data) {
    if (dispObj != NULL) {
        dispObj->shaderData = data;
    }
}
