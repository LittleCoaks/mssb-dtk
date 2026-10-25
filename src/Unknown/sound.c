#include "Unknown/sound.h"
#include "Dolphin/os.h"
#include "Dolphin/ai.h"
#include "Dolphin/ar.h"
#include "musyx/musyx.h"

extern SndHeap lbl_802FE8A0[2];
SndHeap* lbl_803CBB10 = lbl_802FE8A0;

SndConfig lbl_801112F0 = {0x40, 0x30, 0x10, 1, 0, 0x800000};

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

void fn_800B0934(void* addr) {
}

void initSound(SndConfig* config, u8* aiStack, void* aramBuffer, u32 aramSize) {
    SND_HOOKS hooks = {SndAlloc, SndFree};
    u32 end;

    AIInit(aiStack);
    ARInit(NULL, 0);
    ARQInit();
    if (config == NULL) {
        config = &lbl_801112F0;
    }
    end = (u32)aramBuffer + aramSize;
    lbl_803CBB10->cur = (u32)aramBuffer;
    lbl_803CBB10->end = end;
    lbl_803CBB10->remaining = end - (u32)aramBuffer;
    sndSetHooks(&hooks);
    if (sndInit(config->voices, config->music, config->sfx, config->studios, config->flags, config->aramSize)) {
        OSPanic("sound.c", 278, "gYd_MusyXInit()::Failed to sndInit().");
    }
    if (OSGetSoundMode() == 0) {
        sndOutputMode(SND_OUTPUTMODE_MONO);
    } else {
        sndOutputMode(SND_OUTPUTMODE_STEREO);
    }
}

void soundQuit(void) {
    SND_HOOKS hooks = {SndAlloc, fn_800B0934};
    sndSetHooks(&hooks);
    sndQuit();
}
