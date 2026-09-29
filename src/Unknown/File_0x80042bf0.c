#include "Unknown/File_0x80042bf0.h"

extern u32 lbl_803CB750;

static inline u32 nextRandSeed(void) {
    return lbl_803CB750 = lbl_803CB750 * 0x5D588B65 + 1;
}

/* Random integer in the inclusive range between a and b, in either order. */
int randRange_FUN_80042bf0(int a, int b) {
    int min;

    if (a == b) {
        return a;
    }
    if (a <= b) {
        min = a;
    } else {
        min = b;
        b = a;
    }
    a = nextRandSeed() >> 16;
    a %= b - min + 1;
    a += min;
    return a;
}
