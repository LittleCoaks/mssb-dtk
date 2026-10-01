#include "Unknown/File_0x8003ad84.h"
#include "Dolphin/GX/GXTexture.h"

extern GXTexObj lbl_803C50B0;
extern GXTlutObj lbl_803C50DC;
extern u8 lbl_803CBCAC;

u16 lbl_800F7AC0[16] = {
    0x0000, 0x11FF, 0x22FF, 0x33FF, 0x44FF, 0x55FF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};

void GXTexObjRelated(TextureRecord* texture) {
    GXInitTexObjCI(&lbl_803C50B0, texture->pixels, texture->width, texture->height, GX_TF_C4, texture->wrapS,
                   texture->wrapT, GX_FALSE, 0);
    GXInitTlutObj(&lbl_803C50DC, lbl_800F7AC0, GX_TL_IA8, 16);
    GXInitTexObjLOD(&lbl_803C50B0, texture->minFilter, texture->magFilter, texture->minLOD, texture->maxLOD,
                    texture->lodBias, GX_FALSE, GX_FALSE, GX_ANISO_1);
    lbl_803CBCAC = TRUE;
}
