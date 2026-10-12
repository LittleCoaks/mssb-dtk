#include "C3/geoPalette/geoPalette.h"
#include "Unknown/File_0x800bf074.h"
#include "Unknown/File_0x800acf14.h"
#include "Dolphin/mtx.h"
#include "C3/geoPalette.h"

#pragma dont_inline on
void* LoadGeoPalette(void* geoFile) {
    return NULL;
}
#pragma dont_inline reset

void convertGeometryAndSknHeader(void* geo, void* skn) {
    void* pal = LoadGeoPalette(geo);

    if (skn != NULL) {
        SKNLoadFile(skn, pal);
    }
    *(void**)geo = pal;
}

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

void AdjustGPLDataPointers(DODisplayLayout* layout, struct DODisplayObj* dispObj) {
    return;
}

extern UnkShadowCallback lbl_803CC20C;

void UpdateTexturePalettePointers(UnkTexPalGeo* geo, void* tex) {
    u32 i;
    int j;

    for (i = 0; i < geo->numEntries; i++) {
        for (j = 0; j < geo->entries[i].obj->numSubs; j++) {
            geo->entries[i].obj->subs[j].tex = tex;
        }
    }
}

void fn_800BD1E8(UnkShadowCallback cb) {
    lbl_803CC20C = cb;
}
