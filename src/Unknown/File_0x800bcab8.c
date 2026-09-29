#include "Unknown/File_0x800bcab8.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/File_0x800bc860.h"
#include "Dolphin/os.h"

void DOGet(struct DODisplayObj** dispObj, DODisplayDataPtr pal, u16 id, char* name) {
    DODisplayLayout* layout;

    if (id >= pal->numDescriptors) {
        OSReport("Display object id %d is greater than number of objects %d", id, pal->numDescriptors);
        *dispObj = NULL;
        return;
    }
    layout = pal->descriptorArray[id].layout;
    *dispObj = _OSAllocFromHeap(0x20, sizeof(struct DODisplayObj));
    InitDisplayObjWithLayout(*dispObj, layout);
}
