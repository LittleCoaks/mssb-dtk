#include "Unknown/File_0x8001b2d0.h"
#include "PowerPC_EABI_Support/Runtime/__mem.h"

extern u8 destAnimStructs[0x204C];
extern u8 hugeAnimStruct[0x3154];

void copyAnimationStructures(void) {
    memcpy(destAnimStructs, hugeAnimStruct + 0xC04, sizeof(destAnimStructs));
}
