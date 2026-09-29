#include "Unknown/File_0x800bf1a4.h"

#ifdef __MWERKS__ // clang-format off
asm void SKNFlushByIndex1(register u16* indices, register u32 count, register void* base) {
    nofralloc
    mtctr count
    subi indices, indices, 2
loop:
    lhzu r6, 2(indices)
    mulli r7, r6, 0x18
    dcbf r7, base
    bdnz loop
    blr
}

asm void SKNFlushByIndex2(register u16* indices, register u32 count, register void* base) {
    nofralloc
    mtctr count
    subi indices, indices, 2
loop:
    lhzu r6, 2(indices)
    add r7, r6, r6
    add r6, r7, r6
    add r6, r6, r6
    add r6, r6, r6
    dcbf r6, base
    bdnz loop
    blr
}

asm void SKNBzero32B(register void* base, register u32 size) {
    nofralloc
    li r0, 0
    srwi size, size, 5
    mtctr size
loop:
    dcbz r0, base
    addi base, base, 0x20
    bdnz loop
    blr
}
#endif // clang-format on
