#include "Unknown/File_0x80018270.h"
#include "game/UnknownHomes_Game.h"

extern void *_OSAllocFromHeap(s32 alignment, s32 size);
extern void *lbl_803CB790;
extern u8 hugeAnimStruct[];

#define HUGE_U32(off) (*(u32 *)(hugeAnimStruct + (off)))
#define HUGE_S16(off) (*(s16 *)(hugeAnimStruct + (off)))
#define HUGE_U8(off) (*(u8 *)(hugeAnimStruct + (off)))
#define CHAR_RECORD_U32(id, off) (*(u32 *)((u8 *)lbl_803CB790 + (id) * 0x130 + (off)))

#define CHAR_RECORD_COUNT 54
#define OBJECT_SLOT_STRIDE 0x27C

void animationInitializationRunnerRelated(int mode) {
    u32 maxA = 0;
    u32 maxB = 0;
    u32 i;
    u32 n;
    u32 v;
    u32 base;
    u32 a;
    u32 aUp;
    u32 bUp;
    u32 size;
    int t;
    int p;

    if (mode == 2) {
        base = (u32)_OSAllocFromHeap(0x20, 0x13E80);
        HUGE_U32(0x2C8C) = base;
        HUGE_U32(0xC0C) = base;
        for (i = 1; i < 9; i++) {
            HUGE_U32(0xC0C + i * OBJECT_SLOT_STRIDE) = (u32)_OSAllocFromHeap(0x20, 0x12C40);
        }

        for (n = 0; n < CHAR_RECORD_COUNT; n++) {
            v = CHAR_RECORD_U32(n, 0x4) & 0x0FFFFFFF;
            if (maxA < v) {
                maxA = v;
            }
        }

        a = maxA + 0x1F;
        aUp = a & ~0x1F;
        size = (a >> 5) + 0x13E80;
        base = (u32)_OSAllocFromHeap(0x20, size);
        HUGE_U32(0x2268) = base;
        HUGE_U32(0x24E4) = base + aUp;
        HUGE_U32(0x2760) = base + aUp * 2;
        HUGE_U32(0x29DC) = base + aUp * 3;
        HUGE_U32(0x2D64) = size;
        HUGE_U32(0x2D3C) = base + aUp * 4;
        HUGE_U32(0x2D40) = 0x13E80;
        HUGE_S16(0x2D44) = -1;
        HUGE_U8(0x2D46) = 0;
    } else {
        if (mode == 0) {
            for (t = 0; t < TEAMS_PER_GAME; t++) {
                for (p = 0; p < PLAYERS_PER_TEAM; p++) {
                    v = CHAR_RECORD_U32(inMemRoster[t][p].stats.CharID, 0x4) & 0x0FFFFFFF;
                    if (maxA < v) {
                        maxA = v;
                    }
                }
            }
            for (t = 0; t < TEAMS_PER_GAME; t++) {
                for (p = 0; p < PLAYERS_PER_TEAM; p++) {
                    v = CHAR_RECORD_U32(inMemRoster[t][p].stats.CharID, 0x14) & 0x0FFFFFFF;
                    if (maxB < v) {
                        maxB = v;
                    }
                }
            }
        } else {
            for (n = 0; n < CHAR_RECORD_COUNT; n++) {
                v = CHAR_RECORD_U32(n, 0x4) & 0x0FFFFFFF;
                if (maxA < v) {
                    maxA = v;
                }
            }
            for (n = 0; n < CHAR_RECORD_COUNT; n++) {
                v = CHAR_RECORD_U32(n, 0x14) & 0x0FFFFFFF;
                if (maxB < v) {
                    maxB = v;
                }
            }
        }

        bUp = (maxB + 0x1F) & ~0x1F;
        a = maxA + 0x1F;
        aUp = a & ~0x1F;
        size = bUp * 9 + (a >> 5) + aUp + bUp;
        base = (u32)_OSAllocFromHeap(0x20, size);
        HUGE_U32(0x2C8C) = base;
        HUGE_U32(0x2D64) = size;
        for (i = 0; i < 9; i++) {
            HUGE_U32(0xC0C + i * OBJECT_SLOT_STRIDE) = base;
            base += bUp;
        }
        HUGE_U32(0x2268) = base;
        base += aUp;
        HUGE_U32(0x24E4) = base;
        base += aUp;
        HUGE_U32(0x2760) = base;
        base += aUp;
        HUGE_U32(0x29DC) = base;
        base += aUp;
        HUGE_U32(0x2D54) = base;
        base += aUp;
        HUGE_U32(0x2D58) = aUp;
        HUGE_S16(0x2D5C) = -1;
        HUGE_U8(0x2D5E) = 0;
        HUGE_U32(0x2D3C) = base;
        HUGE_U32(0x2D40) = bUp;
        HUGE_S16(0x2D44) = -1;
        HUGE_U8(0x2D46) = 0;
    }

    for (i = 0; i < 13; i++) {
        HUGE_U32(0xC30 + i * OBJECT_SLOT_STRIDE) = 0;
        HUGE_U32(0xC34 + i * OBJECT_SLOT_STRIDE) = 0;
    }
}
