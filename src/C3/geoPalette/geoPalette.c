#include "C3/geoPalette/geoPalette.h"
#include "C3/skinning/SKNControl.h"
#include "Unknown/File_0x800acf14.h"
#include "Dolphin/mtx.h"
#include "C3/geoPalette.h"
#include "stl/mem.h"

static void rebase(u32* field, u32 addend) {
    if (*field != 0) {
        *field += addend;
    }
}

#pragma dont_inline on
void* LoadGeoPalette(void* geoFile) {
    u8* geo = (u8*)geoFile;
    u32* table;
    u16 entryCount;
    u16 i;
    u16 j;
    u16 k;
    void* result = NULL;

    if (*(u32*)(geo + 0x4) != 0 && *(u32*)(geo + 0x8) != 0) {
        *(u32*)(geo + 0x8) += (u32)geo;
    }

    *(u32*)(geo + 0x10) += (u32)geo;
    table = (u32*)(*(u32*)(geo + 0x10));
    entryCount = *(u16*)(geo + 0xC);

    for (i = 0; i < entryCount; i++) {
        u8* obj;
        u8* sub;
        u8* elems;
        u8* tail;

        table[i * 2] += (u32)geo;
        table[i * 2 + 1] += (u32)geo;
        obj = (u8*)table[i * 2];

        rebase((u32*)obj, (u32)obj);
        sub = (u8*)*(u32*)obj;
        rebase((u32*)sub, (u32)obj);
        if (sub[7] == 6) {
            result = (void*)*(u32*)sub;
        }

        rebase((u32*)(obj + 0x4), (u32)obj);
        rebase((u32*)*(u32*)(obj + 0x4), (u32)obj);

        rebase((u32*)(obj + 0x8), (u32)obj);
        elems = (u8*)*(u32*)(obj + 0x8);
        for (j = 0; j < obj[0x14]; j++) {
            rebase((u32*)(elems + j * 0x10), (u32)obj);
            rebase((u32*)(elems + j * 0x10 + 0x8), (u32)obj);
        }

        rebase((u32*)(obj + 0xC), (u32)obj);
        rebase((u32*)*(u32*)(obj + 0xC), (u32)obj);

        rebase((u32*)(obj + 0x10), (u32)obj);
        tail = (u8*)*(u32*)(obj + 0x10);
        rebase((u32*)tail, (u32)obj);
        rebase((u32*)(tail + 0x4), (u32)obj);
        elems = (u8*)*(u32*)(tail + 0x4);
        for (k = 0; k < *(u16*)(tail + 0x8); k++) {
            rebase((u32*)(elems + k * 0x10 + 0x8), (u32)obj);
        }

        rebase((u32*)(obj + 0x18), (u32)obj);
    }
    return result;
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

void* AdjustGPLDataPointers(DODisplayLayout* layout, struct DODisplayObj* dispObj) {
    u32 base = (u32)layout;
    void* result = NULL;
    u32 i;
    u32 j;

    if (layout->positionData != NULL) {
        dispObj->positionData = (PositionData*)(base + (u32)layout->positionData);
        *(u32*)dispObj->positionData += base;
        if (((u8*)*(u32*)dispObj->positionData)[7] == 6) {
            result = (void*)*(u32*)dispObj->positionData;
        }
    } else {
        dispObj->positionData = NULL;
    }

    if (layout->colorData != NULL) {
        dispObj->colorData = (ColorData*)(base + (u32)layout->colorData);
        *(u32*)dispObj->colorData += base;
    } else {
        dispObj->colorData = NULL;
    }

    if (layout->textureData != NULL && layout->numTextureChannels != 0) {
        dispObj->textureData = _OSAllocFromHeap(0x20, layout->numTextureChannels * 0x10);
        dispObj->numTextureChannels = layout->numTextureChannels;
        for (i = 0; i < layout->numTextureChannels; i++) {
            memcpy((u8*)dispObj->textureData + i * 0x10,
                   (u8*)layout->textureData + base + i * 0x10, 0x10);
            *(u32*)((u8*)dispObj->textureData + i * 0x10) += base;
        }
    } else {
        dispObj->textureData = NULL;
        dispObj->numTextureChannels = 0;
    }

    if (layout->lightingData != NULL) {
        dispObj->lightingData = (LightingData*)(base + (u32)layout->lightingData);
        *(u32*)dispObj->lightingData += base;
    } else {
        dispObj->lightingData = NULL;
    }

    if (layout->displayData != NULL) {
        dispObj->displayData = (DisplayData*)(base + (u32)layout->displayData);
        *(u32*)dispObj->displayData += base;
        *(u32*)((u8*)dispObj->displayData + 0x4) += base;
        for (j = 0; j < *(u16*)((u8*)dispObj->displayData + 0x8); j++) {
            u32* entry = (u32*)(*(u32*)((u8*)dispObj->displayData + 0x4) + j * 0x10 + 0x8);

            if (*entry != 0) {
                *entry += base;
            }
        }
    } else {
        dispObj->displayData = NULL;
    }

    dispObj->pad8 = layout->pad8;
    dispObj->visibility = 1;
    dispObj->overrideTevMode = 0;
    dispObj->userTevModeFunc = DODefaultUserTevMode;
    dispObj->shaderFunc = NULL;
    dispObj->shaderData = NULL;

    memcpy(dispObj->unk58, layout->unk20, 4);
    memcpy(dispObj->unk54, layout->unk1C, 4);
    memcpy(dispObj->unk60, layout->unk28, 4);
    memcpy(dispObj->unk5C, layout->unk24, 4);
    memcpy(dispObj->unk68, layout->unk30, 4);
    memcpy(dispObj->unk64, layout->unk2C, 4);

    return result;
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
