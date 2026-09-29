#include "Unknown/File_0x800b0938.h"
#include "Dolphin/os.h"

void SndFree(void* addr) {
    SndHeap* heap = lbl_803CBB10;
    u32 start = ((u32*)addr)[-2];
    u32 end = start + ((u32*)addr)[-1];

    if (end != heap->cur) {
        OSReport("sNp_SndFree err\n");
        while (TRUE) {}
    }
    heap->cur = start;
    lbl_803CBB10->remaining = lbl_803CBB10->end - lbl_803CBB10->cur;
}

void* SndAlloc(u32 len) {
    u32 cur;
    u32 end;
    u32 block;
    u32 size;
    s32 remaining;

    len = (len + 3) & ~3;
    cur = lbl_803CBB10->cur;
    end = lbl_803CBB10->end;
    block = (cur + 0x27) & ~0x1F;
    size = block - cur;
    size += len;
    len += block;
    remaining = end - len;
    if (remaining < 0) {
        OSReport("sNp_SndAlloc:: no enough space:%d\n", remaining);
        while (TRUE) {}
    }
    ((u32*)block)[-2] = cur;
    ((u32*)block)[-1] = size;
    lbl_803CBB10->remaining = remaining;
    lbl_803CBB10->cur = len;
    return (void*)block;
}
