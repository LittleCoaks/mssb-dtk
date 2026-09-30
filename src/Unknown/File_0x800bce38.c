#include "Unknown/File_0x800bce38.h"
#include "Unknown/File_0x800acf14.h"
#include "Dolphin/mtx.h"
#include "C3/geoPalette.h"

void AdjustGPLDataPointers(DODisplayLayout* layout, struct DODisplayObj* dispObj);

void AdjustGEOPalettePointers(DODisplayDataPtr pal) {
    struct DODisplayObj* dispObjs;
    u32 i;

    pal->userData = (void*)((u32)pal + (u32)pal->userData);
    pal->descriptorArray = (DODescriptorPtr)((u32)pal + (u32)pal->descriptorArray);

    dispObjs = _OSAllocFromHeap(0x20, sizeof(struct DODisplayObj) * pal->numDescriptors);
    for (i = 0; i < pal->numDescriptors; i++) {
        AdjustGPLDataPointers((DODisplayLayout*)((u32)pal + (u32)pal->descriptorArray[i].layout), &dispObjs[i]);
        pal->descriptorArray[i].layout = (DODisplayLayout*)&dispObjs[i];
        pal->descriptorArray[i].name = (char*)((u32)pal + (u32)pal->descriptorArray[i].name);
    }
}
