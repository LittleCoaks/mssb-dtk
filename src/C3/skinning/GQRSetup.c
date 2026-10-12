#include "C3/skinning/GQRSetup.h"

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

void GQRSetup7(u32 loadScale, u32 loadType, u32 storeScale, u32 storeType) {
    __MTGQR7((((loadScale << 8) + loadType) << 16) | ((storeScale << 8) + storeType));
}

void GQRSetup6(u32 loadScale, u32 loadType, u32 storeScale, u32 storeType) {
    __MTGQR6((((loadScale << 8) + loadType) << 16) | ((storeScale << 8) + storeType));
}

void GQRSetup5(u32 loadScale, u32 loadType, u32 storeScale, u32 storeType) {
    __MTGQR5((((loadScale << 8) + loadType) << 16) | ((storeScale << 8) + storeType));
}
