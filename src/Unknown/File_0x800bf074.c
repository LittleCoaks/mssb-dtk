#include "Unknown/File_0x800bf074.h"
#include "C3/actor.h"
#include "C3/skinning.h"

void SKNLoadFile(void* sknFile, void* pal) {
    sHdr* hdr = sknFile;
    SK1List* sk1;
    SK2List* sk2;
    SKAccList* acc;
    u32 i;

    if (hdr->sk1ListArray) {
        hdr->sk1ListArray = (SK1List*)((u32)hdr->sk1ListArray + (u32)hdr);
    }
    if (hdr->sk2ListArray) {
        hdr->sk2ListArray = (SK2List*)((u32)hdr->sk2ListArray + (u32)hdr);
    }
    if (hdr->skAccListArray) {
        hdr->skAccListArray = (SKAccList*)((u32)hdr->skAccListArray + (u32)hdr);
    }
    if (hdr->flushIndices) {
        hdr->flushIndices = (void*)((u32)hdr->flushIndices + (u32)hdr);
    }
    for (i = 0; i < hdr->numSk1List; i++) {
        sk1 = &hdr->sk1ListArray[i];
        sk1->vertSrc = (void*)((u32)sk1->vertSrc + (u32)hdr);
    }
    for (i = 0; i < hdr->numSk2List; i++) {
        sk2 = &hdr->sk2ListArray[i];
        sk2->vertSrc = (void*)((u32)sk2->vertSrc + (u32)hdr);
        sk2->weights = (void*)((u32)sk2->weights + (u32)hdr);
    }
    for (i = 0; i < hdr->numSkAccList; i++) {
        acc = &hdr->skAccListArray[i];
        acc->vertSrc = (void*)((u32)acc->vertSrc + (u32)hdr);
        acc->weights = (void*)((u32)acc->weights + (u32)hdr);
        acc->vertIndices = (void*)((u32)acc->vertIndices + (u32)hdr);
    }
    SKNInit();
}
