#include "C3/skinning/SKNControl.h"
#include "C3/actor.h"
#include "C3/skinning.h"

void SKNLoadFile(void* sknFile, void* pal) {
    sHdr* hdr = sknFile;
    SK1List* sk1;
    SK2List* sk2;
    SKAccList* acc;
    u32 i;

    if (hdr->sk1ListArray) {
        hdr->sk1ListArray = (SK1List*)((u32)hdr->sk1ListArray + (u32)hdr);
    }
    if (hdr->sk2ListArray) {
        hdr->sk2ListArray = (SK2List*)((u32)hdr->sk2ListArray + (u32)hdr);
    }
    if (hdr->skAccListArray) {
        hdr->skAccListArray = (SKAccList*)((u32)hdr->skAccListArray + (u32)hdr);
    }
    if (hdr->flushIndices) {
        hdr->flushIndices = (void*)((u32)hdr->flushIndices + (u32)hdr);
    }
    for (i = 0; i < hdr->numSk1List; i++) {
        sk1 = &hdr->sk1ListArray[i];
        sk1->vertSrc = (void*)((u32)sk1->vertSrc + (u32)hdr);
    }
    for (i = 0; i < hdr->numSk2List; i++) {
        sk2 = &hdr->sk2ListArray[i];
        sk2->vertSrc = (void*)((u32)sk2->vertSrc + (u32)hdr);
        sk2->weights = (void*)((u32)sk2->weights + (u32)hdr);
    }
    for (i = 0; i < hdr->numSkAccList; i++) {
        acc = &hdr->skAccListArray[i];
        acc->vertSrc = (void*)((u32)acc->vertSrc + (u32)hdr);
        acc->weights = (void*)((u32)acc->weights + (u32)hdr);
        acc->vertIndices = (void*)((u32)acc->vertIndices + (u32)hdr);
    }
    SKNInit();
}

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

void SKNInit(void) {
    if (!(PPCMfhid2() & 0x10000000)) {
        DCInvalidateRange((void*)LC_BASE, 0x4000);
        LCEnable();
    }

    SKBuffers[0] = (void*)LC_BASE;
    SKBuffers[1] = (void*)(LC_BASE + 0x1000);
    SKBuffers[2] = (void*)(LC_BASE + 0x2000);
    SKBuffers[3] = (void*)(LC_BASE + 0x3000);

    SKAccBuffers[0].src = (s16*)LC_BASE;
    SKAccBuffers[0].indices = (u16*)(LC_BASE + 0x1000);
    SKAccBuffers[0].weights = (u8*)(LC_BASE + 0x1800);
    SKAccBuffers[1].src = (s16*)(LC_BASE + 0x2000);
    SKAccBuffers[1].indices = (u16*)(LC_BASE + 0x3000);
    SKAccBuffers[1].weights = (u8*)(LC_BASE + 0x3800);

    GQRSetup5(8, 4, 8, 4);
}

void processModelDataRelated(sBone** bones, sHdr* hdr) {
    return;
}

void SKNIt(sBone** bones, sHdr* hdr) {
    return;
}
