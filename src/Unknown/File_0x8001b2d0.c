#include "Unknown/File_0x8001b2d0.h"
#include "PowerPC_EABI_Support/Runtime/__mem.h"
#include "HugeAnimStruct.h"

extern u8 destAnimStructs[0x204C];

void copyAnimationStructures(void) {
    memcpy(destAnimStructs, hugeAnimStruct.pool, sizeof(destAnimStructs));
}
