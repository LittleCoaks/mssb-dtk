#include "C3/skinning/SKNControl.h"
#include "C3/actor.h"
#include "C3/skinning.h"

sAccBuffers SKAccBuffers[2];
void* SKBuffers[4];

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

void SKNIt(sBone** bones, sHdr* hdr, void* vtx) {
    u16 sizes[2];
    SK1List* sk1;
    SK2List* sk2;
    SKAccList* acc;
    u32 i;

    GQRSetup7(hdr->posNrmShift, 0, hdr->posNrmShift, 0);

    if (hdr->numSk1List != 0) {
        sizes[0] = SKNLCTouchData(0, hdr->sk1ListArray[0].vertSrc,
                                  hdr->sk1ListArray[0].vertSrcOffset + hdr->sk1ListArray[0].count * 0x18);
        for (i = 0; i < hdr->numSk1List - 1; i++) {
            sizes[(i + 1) & 1] = SKNLCTouchData(((i + 1) & 1) * 2, hdr->sk1ListArray[i + 1].vertSrc,
                                                hdr->sk1ListArray[i + 1].vertSrcOffset + hdr->sk1ListArray[i + 1].count * 0x18);
            sk1 = &hdr->sk1ListArray[i];
            PSMTXReorder(bones[sk1->boneIndex]->skinMtx, (f32 (*)[3])sk1->m);
            LCQueueWait(1);
            SKNLC1Vecs16Norms16(sk1->m, (s16*)((u32)sk1->vertDst + (u32)vtx), sk1->count, (i & 1) * 2, sk1->vertSrcOffset, sizes[i & 1]);
        }
        sk1 = &hdr->sk1ListArray[i];
        PSMTXReorder(bones[sk1->boneIndex]->skinMtx, (f32 (*)[3])sk1->m);
        SKNLC1Vecs16Norms16(sk1->m, (s16*)((u32)sk1->vertDst + (u32)vtx), sk1->count, (i & 1) * 2, sk1->vertSrcOffset, sizes[i & 1]);
    }

    if (hdr->numSk2List != 0) {
        sizes[0] = SKNLC2TouchData(0, hdr->sk2ListArray[0].vertSrc,
                                   hdr->sk2ListArray[0].vertSrcOffset + hdr->sk2ListArray[0].count * 0x18);
        SKNLC2TouchData(1, hdr->sk2ListArray[0].weights, hdr->sk2ListArray[0].count * 2);
        for (i = 0; i < hdr->numSk2List - 1; i++) {
            sk2 = &hdr->sk2ListArray[i];
            sizes[(i + 1) & 1] = SKNLC2TouchData(((i + 1) & 1) * 2, hdr->sk2ListArray[i + 1].vertSrc,
                                                 hdr->sk2ListArray[i + 1].vertSrcOffset + hdr->sk2ListArray[i + 1].count * 0x18);
            SKNLC2TouchData(((i + 1) & 1) * 2 + 1, hdr->sk2ListArray[i + 1].weights, hdr->sk2ListArray[i + 1].count * 2);
            PSMTXReorder(bones[sk2->bone0Index]->skinMtx, (f32 (*)[3])sk2->m0);
            PSMTXReorder(bones[sk2->bone1Index]->skinMtx, (f32 (*)[3])sk2->m1);
            LCQueueWait(2);
            SKNLC2Vecs16Norms16(sk2->m0, sk2->m1, (i & 1) * 2, (s16*)((u32)sk2->vertDst + (u32)vtx), sk2->count, sk2->vertSrcOffset, sizes[i & 1]);
        }
        sk2 = &hdr->sk2ListArray[i];
        PSMTXReorder(bones[sk2->bone0Index]->skinMtx, (f32 (*)[3])sk2->m0);
        PSMTXReorder(bones[sk2->bone1Index]->skinMtx, (f32 (*)[3])sk2->m1);
        LCQueueWait(0);
        SKNLC2Vecs16Norms16(sk2->m0, sk2->m1, (i & 1) * 2, (s16*)((u32)sk2->vertDst + (u32)vtx), sk2->count, sk2->vertSrcOffset, sizes[i & 1]);
    }

    if (hdr->numSkAccList != 0) {
        if (hdr->skBzeroSize != 0) {
            SKNBzero32B((void*)((u32)hdr->skBzeroBase + (u32)vtx), (hdr->skBzeroSize + 0x1F) & 0x07FFFFFF);
        }
        SKNLCAccTouchData(0, hdr->skAccListArray[0].vertSrc, hdr->skAccListArray[0].vertIndices,
                          hdr->skAccListArray[0].weights, hdr->skAccListArray[0].count);
        LCQueueWait(0);
        for (i = 0; i < hdr->numSkAccList - 1; i++) {
            SKNLCAccTouchData((i + 1) & 1, hdr->skAccListArray[i + 1].vertSrc, hdr->skAccListArray[i + 1].vertIndices,
                              hdr->skAccListArray[i + 1].weights, hdr->skAccListArray[i + 1].count);
            acc = &hdr->skAccListArray[i];
            PSMTXReorder(bones[acc->boneIndex]->skinMtx, (f32 (*)[3])acc->m);
            SKNAccVecs16Norms16Iu161(acc->m, acc->count, SKAccBuffers[i & 1].src, (s16*)((u32)acc->vertDst + (u32)vtx),
                                     SKAccBuffers[i & 1].indices, SKAccBuffers[i & 1].weights);
        }
        acc = &hdr->skAccListArray[i];
        PSMTXReorder(bones[acc->boneIndex]->skinMtx, (f32 (*)[3])acc->m);
        SKNAccVecs16Norms16Iu161(acc->m, acc->count, SKAccBuffers[i & 1].src, (s16*)((u32)acc->vertDst + (u32)vtx),
                                 SKAccBuffers[i & 1].indices, SKAccBuffers[i & 1].weights);
        DCStoreRange((void*)((u32)hdr->skBzeroBase + (u32)vtx), (hdr->skBzeroSize + 0x1F) & 0x07FFFFFF);
        if (hdr->flushCount != 0) {
            SKNFlushByIndex1(hdr->flushIndices, hdr->flushCount, (void*)((u32)hdr->skAccListArray->vertDst + (u32)vtx));
        }
    }
}

static inline void SKNLCAccTouchDataS16(u8 buffer, s16* src, u16* indices, u8* weights, u32 count) {
    u32 size = ((count * 3 * 2 * 2) + 0x1F) >> 5;

    LCLoadBlocks(SKAccBuffers[buffer].src, src, size);
    size = ((count * 2) + 0x1F) >> 5;
    LCLoadBlocks(SKAccBuffers[buffer].indices, indices, size);
    LCLoadBlocks(SKAccBuffers[buffer].weights, weights, (count + 31) >> 5);
}

static inline void SKNLC2Vecs16Norms16S16(Mtx34 m0, Mtx34 m1, u8 buffer, s16* destination, u32 count, u8 offset, u32 size) {
    fn_800C02C8(m0, m1, SKBuffers[buffer + 1], (void*)((u32)SKBuffers[buffer] + offset), (void*)((u32)SKBuffers[buffer] + offset), count);
    LCStoreBlocks(destination, SKBuffers[buffer], size);
}

static inline void SKNLC1Vecs16Norms16S16(Mtx34 m, s16* destination, u32 count, u8 buffer, u8 offset, u32 size) {
    fn_800BFF9C(m, (void*)((u32)SKBuffers[buffer] + offset), (void*)((u32)SKBuffers[buffer] + offset), count);
    LCStoreData(destination, SKBuffers[buffer], size);
}

void processModelDataRelated(sBone** bones, sHdr* hdr, void* vtx) {
    u16 sizes[2];
    SK1List* sk1;
    SK2List* sk2;
    SKAccList* acc;
    u32 i;

    GQRSetup6(hdr->posNrmShift, 7, hdr->posNrmShift, 7);

    if (hdr->numSk1List != 0) {
        sizes[0] = SKNLCTouchData(0, hdr->sk1ListArray[0].vertSrc,
                                  hdr->sk1ListArray[0].vertSrcOffset + hdr->sk1ListArray[0].count * 0xC);
        for (i = 0; i < hdr->numSk1List - 1; i++) {
            sizes[(i + 1) & 1] = SKNLCTouchData(((i + 1) & 1) * 2, hdr->sk1ListArray[i + 1].vertSrc,
                                                hdr->sk1ListArray[i + 1].vertSrcOffset + hdr->sk1ListArray[i + 1].count * 0xC);
            sk1 = &hdr->sk1ListArray[i];
            PSMTXReorder(bones[sk1->boneIndex]->skinMtx, (f32 (*)[3])sk1->m);
            LCQueueWait(1);
            SKNLC1Vecs16Norms16S16(sk1->m, (s16*)((u32)sk1->vertDst + (u32)vtx), sk1->count, (i & 1) * 2, sk1->vertSrcOffset, sizes[i & 1]);
        }
        sk1 = &hdr->sk1ListArray[i];
        PSMTXReorder(bones[sk1->boneIndex]->skinMtx, (f32 (*)[3])sk1->m);
        SKNLC1Vecs16Norms16S16(sk1->m, (s16*)((u32)sk1->vertDst + (u32)vtx), sk1->count, (i & 1) * 2, sk1->vertSrcOffset, sizes[i & 1]);
    }

    if (hdr->numSk2List != 0) {
        sizes[0] = SKNLC2TouchData(0, hdr->sk2ListArray[0].vertSrc,
                                   hdr->sk2ListArray[0].vertSrcOffset + hdr->sk2ListArray[0].count * 0xC);
        SKNLC2TouchData(1, hdr->sk2ListArray[0].weights, hdr->sk2ListArray[0].count * 2);
        for (i = 0; i < hdr->numSk2List - 1; i++) {
            sk2 = &hdr->sk2ListArray[i];
            sizes[(i + 1) & 1] = SKNLC2TouchData(((i + 1) & 1) * 2, hdr->sk2ListArray[i + 1].vertSrc,
                                                 hdr->sk2ListArray[i + 1].vertSrcOffset + hdr->sk2ListArray[i + 1].count * 0xC);
            SKNLC2TouchData(((i + 1) & 1) * 2 + 1, hdr->sk2ListArray[i + 1].weights, hdr->sk2ListArray[i + 1].count * 2);
            PSMTXReorder(bones[sk2->bone0Index]->skinMtx, (f32 (*)[3])sk2->m0);
            PSMTXReorder(bones[sk2->bone1Index]->skinMtx, (f32 (*)[3])sk2->m1);
            LCQueueWait(2);
            SKNLC2Vecs16Norms16S16(sk2->m0, sk2->m1, (i & 1) * 2, (s16*)((u32)sk2->vertDst + (u32)vtx), sk2->count, sk2->vertSrcOffset, sizes[i & 1]);
        }
        sk2 = &hdr->sk2ListArray[i];
        PSMTXReorder(bones[sk2->bone0Index]->skinMtx, (f32 (*)[3])sk2->m0);
        PSMTXReorder(bones[sk2->bone1Index]->skinMtx, (f32 (*)[3])sk2->m1);
        LCQueueWait(0);
        SKNLC2Vecs16Norms16S16(sk2->m0, sk2->m1, (i & 1) * 2, (s16*)((u32)sk2->vertDst + (u32)vtx), sk2->count, sk2->vertSrcOffset, sizes[i & 1]);
    }

    if (hdr->numSkAccList != 0) {
        if (hdr->skBzeroSize != 0) {
            SKNBzero32B((void*)((u32)hdr->skBzeroBase + (u32)vtx), (hdr->skBzeroSize + 0x1F) & 0x07FFFFFF);
        }
        SKNLCAccTouchDataS16(0, hdr->skAccListArray[0].vertSrc, hdr->skAccListArray[0].vertIndices,
                          hdr->skAccListArray[0].weights, hdr->skAccListArray[0].count);
        LCQueueWait(0);
        for (i = 0; i < hdr->numSkAccList - 1; i++) {
            SKNLCAccTouchDataS16((i + 1) & 1, hdr->skAccListArray[i + 1].vertSrc, hdr->skAccListArray[i + 1].vertIndices,
                              hdr->skAccListArray[i + 1].weights, hdr->skAccListArray[i + 1].count);
            acc = &hdr->skAccListArray[i];
            PSMTXReorder(bones[acc->boneIndex]->skinMtx, (f32 (*)[3])acc->m);
            SKNAccVecs16Norms16Iu162(acc->m, acc->count, SKAccBuffers[i & 1].src, (s16*)((u32)acc->vertDst + (u32)vtx),
                                     SKAccBuffers[i & 1].indices, SKAccBuffers[i & 1].weights);
        }
        acc = &hdr->skAccListArray[i];
        PSMTXReorder(bones[acc->boneIndex]->skinMtx, (f32 (*)[3])acc->m);
        SKNAccVecs16Norms16Iu162(acc->m, acc->count, SKAccBuffers[i & 1].src, (s16*)((u32)acc->vertDst + (u32)vtx),
                                 SKAccBuffers[i & 1].indices, SKAccBuffers[i & 1].weights);
        DCStoreRange((void*)((u32)hdr->skBzeroBase + (u32)vtx), (hdr->skBzeroSize + 0x1F) & 0x07FFFFFF);
        if (hdr->flushCount != 0) {
            SKNFlushByIndex2(hdr->flushIndices, hdr->flushCount, (void*)((u32)hdr->skAccListArray->vertDst + (u32)vtx));
        }
    }
}
