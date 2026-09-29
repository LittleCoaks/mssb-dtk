#include "Unknown/File_0x800bd190.h"

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

asm void __MTGQR5(register u32 val) {
    nofralloc
    mtspr GQR5, val
    blr
}

asm void __MTGQR6(register u32 val) {
    nofralloc
    mtspr GQR6, val
    blr
}

asm void __MTGQR7(register u32 val) {
    nofralloc
    mtspr GQR7, val
    blr
}
