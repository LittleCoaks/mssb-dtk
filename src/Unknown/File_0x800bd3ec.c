#include "Unknown/File_0x800bd3ec.h"
#include "Unknown/File_0x800acf14.h"
#include "C3/charPipeline.h"

void LITAlloc(void** light) {
    *light = _OSAllocFromHeap(0x20, sizeof(Light));
    ((Light*)*light)->position.x = ((Light*)*light)->position.y = ((Light*)*light)->position.z = 0.0f;
    ((Light*)*light)->direction.x = ((Light*)*light)->direction.y = 0.0f;
    ((Light*)*light)->direction.z = 1.0f;
    ((Light*)*light)->parent = NULL;
    ((Light*)*light)->animPipe = NULL;
    ((Light*)*light)->control.type = 0;
}
