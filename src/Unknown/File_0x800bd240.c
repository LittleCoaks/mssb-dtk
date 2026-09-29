#include "Unknown/File_0x800bd240.h"
#include "Unknown/File_0x800bd190.h"

void GQRSetup6(u32 loadScale, u32 loadType, u32 storeScale, u32 storeType) {
    __MTGQR6((((loadScale << 8) + loadType) << 16) | ((storeScale << 8) + storeType));
}
