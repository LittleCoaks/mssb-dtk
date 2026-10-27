#ifndef __UNUSED_REL_REP_7920_H_
#define __UNUSED_REL_REP_7920_H_

#include "mssbTypes.h"

typedef struct RepSrc {
    u16 a;
    u16 b;
    u32 c;
} RepSrc;

typedef struct RepRef {
    u16 a;
    u16 b;
    void *next;
} RepRef;

typedef struct RepFlags {
    u8 flagA : 1;
    u8 flagB : 2;
    u8 flagC : 2;
} RepFlags;

typedef struct RepSlot {
    f32 x;
    f32 y;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    u8 unk10;
    RepFlags flags;
    u32 unk14;
    u16 a;
    u16 b;
    u32 c;
} RepSlot;

void fn_1_26B7C(RepSlot *slot);
RepRef *fn_1_26BFC(RepSrc *src, s32 idx);
RepSlot *fn_1_26C2C(RepSrc *src, s32 idx);

#endif // !__UNUSED_REL_REP_7920_H_
