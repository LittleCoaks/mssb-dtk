#include "C3/geoPalette/geoPalette.h"
#include "C3/skinning/SKNControl.h"
#include "Unknown/File_0x800acf14.h"
#include "Dolphin/mtx.h"
#include "C3/geoPalette.h"
#include "stl/mem.h"

#pragma dont_inline on
void* LoadGeoPalette(DODisplayDataPtr pal) {
    DODisplayLayout* layout;
    void* result = NULL;
    u16 i;
    u16 j;

    if (pal->userDataSize != 0 && pal->userData != NULL) {
        pal->userData = (void*)((u32)pal->userData + (u32)pal);
    }
    pal->descriptorArray = (DODescriptorPtr)((u32)pal->descriptorArray + (u32)pal);

    for (i = 0; i < pal->numDescriptors; i++) {
        pal->descriptorArray[i].layout = (DODisplayLayout*)((u32)pal + (u32)pal->descriptorArray[i].layout);
        pal->descriptorArray[i].name = (char*)((u32)pal + (u32)pal->descriptorArray[i].name);
        layout = pal->descriptorArray[i].layout;

        if (layout->positionData != NULL) {
            layout->positionData = (PositionData*)((u32)layout->positionData + (u32)layout);
            if (layout->positionData->positionArray != NULL) {
                layout->positionData->positionArray = (char*)((u32)layout->positionData->positionArray + (u32)layout);
            }
            if (layout->positionData->compCount == 6) {
                result = layout->positionData->positionArray;
            }
        }

        if (layout->colorData != NULL) {
            layout->colorData = (ColorData*)((u32)layout->colorData + (u32)layout);
            if (layout->colorData->colorArray != NULL) {
                layout->colorData->colorArray = (char*)((u32)layout->colorData->colorArray + (u32)layout);
            }
        }

        if (layout->textureData != NULL) {
            layout->textureData = (TextureData*)((u32)layout->textureData + (u32)layout);
            for (j = 0; j < layout->numTextureChannels; j++) {
                if (layout->textureData[j].textureCoordArray != NULL) {
                    layout->textureData[j].textureCoordArray = (char*)((u32)layout + (u32)layout->textureData[j].textureCoordArray);
                }
                if (layout->textureData[j].texturePaletteName != NULL) {
                    layout->textureData[j].texturePaletteName = (char*)((u32)layout + (u32)layout->textureData[j].texturePaletteName);
                }
            }
        }

        if (layout->lightingData != NULL) {
            layout->lightingData = (LightingData*)((u32)layout->lightingData + (u32)layout);
            if (layout->lightingData->normalArray != NULL) {
                layout->lightingData->normalArray = (char*)((u32)layout->lightingData->normalArray + (u32)layout);
            }
        }

        if (layout->displayData != NULL) {
            layout->displayData = (DisplayData*)((u32)layout->displayData + (u32)layout);
            if (layout->displayData->primitiveBank != NULL) {
                layout->displayData->primitiveBank = (char*)((u32)layout->displayData->primitiveBank + (u32)layout);
            }
            if (layout->displayData->displayStateList != NULL) {
                layout->displayData->displayStateList = (DisplayStateList*)((u32)layout->displayData->displayStateList + (u32)layout);
            }
            for (j = 0; j < layout->displayData->numStateEntries; j++) {
                if (layout->displayData->displayStateList[j].primitiveList != NULL) {
                    layout->displayData->displayStateList[j].primitiveList =
                        (char*)((u32)layout + (u32)layout->displayData->displayStateList[j].primitiveList);
                }
            }
        }

        if (layout->unk18 != NULL) {
            layout->unk18 = (void*)((u32)layout->unk18 + (u32)layout);
        }
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

void fn_800BCDBC(DODisplayDataPtr pal) {
    int i;

    for (i = pal->numDescriptors - 1; i >= 0; i--) {
        if (((struct DODisplayObj*)pal->descriptorArray[i].layout)->textureData != NULL) {
            fn_800ACFB0(((struct DODisplayObj*)pal->descriptorArray[i].layout)->textureData);
        }
    }
    fn_800ACFB0(pal->descriptorArray[0].layout);
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
    void* result = NULL;
    int i;

    if (layout->positionData != NULL) {
        dispObj->positionData = (PositionData*)((u32)layout + (u32)layout->positionData);
        dispObj->positionData->positionArray = (char*)((u32)layout + (u32)dispObj->positionData->positionArray);
        if (dispObj->positionData->compCount == 6) {
            result = dispObj->positionData->positionArray;
        }
    } else {
        dispObj->positionData = NULL;
    }

    if (layout->colorData != NULL) {
        dispObj->colorData = (ColorData*)((u32)layout + (u32)layout->colorData);
        dispObj->colorData->colorArray = (char*)((u32)layout + (u32)dispObj->colorData->colorArray);
    } else {
        dispObj->colorData = NULL;
    }

    if (layout->textureData != NULL && layout->numTextureChannels != 0) {
        dispObj->textureData = _OSAllocFromHeap(0x20, layout->numTextureChannels * sizeof(TextureData));
        dispObj->numTextureChannels = layout->numTextureChannels;
        for (i = 0; i < layout->numTextureChannels; i++) {
            dispObj->textureData[i] = *(TextureData*)((u32)layout + (u32)&layout->textureData[i]);
            dispObj->textureData[i].textureCoordArray = (char*)((u32)layout + (u32)dispObj->textureData[i].textureCoordArray);
        }
    } else {
        dispObj->textureData = NULL;
        dispObj->numTextureChannels = 0;
    }

    if (layout->lightingData != NULL) {
        dispObj->lightingData = (LightingData*)((u32)layout + (u32)layout->lightingData);
        dispObj->lightingData->normalArray = (char*)((u32)layout + (u32)dispObj->lightingData->normalArray);
    } else {
        dispObj->lightingData = NULL;
    }

    if (layout->displayData != NULL) {
        dispObj->displayData = (DisplayData*)((u32)layout + (u32)layout->displayData);
        dispObj->displayData->primitiveBank = (char*)((u32)layout + (u32)dispObj->displayData->primitiveBank);
        dispObj->displayData->displayStateList = (DisplayStateList*)((u32)layout + (u32)dispObj->displayData->displayStateList);
        for (i = 0; i < dispObj->displayData->numStateEntries; i++) {
            if (dispObj->displayData->displayStateList[i].primitiveList != NULL) {
                dispObj->displayData->displayStateList[i].primitiveList =
                    (char*)((u32)layout + (u32)dispObj->displayData->displayStateList[i].primitiveList);
            }
        }
    } else {
        dispObj->displayData = NULL;
    }

    dispObj->pad8 = layout->pad8;
    dispObj->visibility = TRUE;
    dispObj->overrideTevMode = FALSE;
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
