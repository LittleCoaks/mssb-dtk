#include "Unknown/sprt.h"
#include "Dolphin/gx.h"
#include "Dolphin/mtx.h"
#include "Dolphin/os.h"

typedef struct SpriteDrawList SpriteDrawList;
typedef struct SpriteBufEntry SpriteBufEntry;

struct SpriteDrawList {
    /*0x00*/ u8* start;
    /*0x04*/ u32 _04;
    /*0x08*/ u8* cursor;
    /*0x0C*/ u8* end;
};

struct SpriteBufEntry {
    /*0x00*/ s32 _00;
    /*0x04*/ void (*fn)(SpriteBufEntry* entry);
    /*0x08*/ SpriteDrawList* rec;
};

typedef struct SpriteRenderState {
    /*0x00*/ Mtx mtx;
    /*0x30*/ f32 blk30[7];
    /*0x4C*/ u32 tab4C[7];
    /*0x68*/ u16 tab68[8];
    /*0x78*/ u32 zModeReg; // last GX z-mode BP register value written (register id 0x40 in the top byte)
    /*0x7C*/ u32 savedZModeReg;
    /*0x80*/ s32 field80;
    /*0x84*/ u16 count84;
    /*0x86*/ u16 u86;
    /*0x88*/ u16 u88;
    /*0x8A*/ u8 renderingMode;
    /*0x8B*/ u8 _8B;
    /*0x8C*/ u8 unk8C;
    /*0x8D*/ u8 unk8D;
} SpriteRenderState;

typedef struct SpriteTexObj {
    /*0x00*/ u32 _00;
    /*0x04*/ void* data04;
    /*0x08*/ u16 arg5;
    /*0x0A*/ u16 arg4;
    /*0x0C*/ u8 b0C;
    /*0x0D*/ u8 b0D;
    /*0x0E*/ u8 b0E;
    /*0x0F*/ u8 b0F;
    /*0x10*/ f32 f10;
    /*0x14*/ u8 _14;
    /*0x15*/ u8 b15;
    /*0x16*/ u8 b16;
    /*0x17*/ u8 b17;
    /*0x18*/ u16 u18;
    /*0x1A*/ u8 b1A;
} SpriteTexObj;

typedef struct SpriteVtxChunk {
    /*0x00*/ u8 pos[0xC];
    /*0x0C*/ u32 word;
    /*0x10*/ u8 tc[4];
} SpriteVtxChunk;

extern s32 AllocateSprite(s32 slot, s32 size);
extern void fn_800B2240(SpriteBufEntry* entry);
extern BOOL fn_800B1EBC(SpriteTexObj* tex, s32 idx, u16 a, u16 b);
extern void DrawSprite(u32 flags, void* vtx, s32 count, void* texObj, u16 arg4, u16 arg5);

extern u8 lbl_802FE918[];
extern u8 lbl_802FEBF8[];
extern u8 lbl_802FF978[];
extern u32 lbl_802FE8B8[24];
extern u8 lbl_803C8A24[];
extern SpriteDrawList* lbl_803CC0F0;

extern s32 fn_800A1A70(void* a, void* b, s32 c);
extern void fn_800A1BB0(s32 a, s32 b, s32 c, s32 d);
extern void fn_800A1E3C(s32 a, s32 b, s32 c, s32 d, s32 e);
extern void fn_800A1F40(s32 a, s32 b, s32 c, u8 d, u8 e, s32 f, s32 g, s32 h, f32 i, f32 j, f32 k);
extern void fn_800A2194(s32 a, u16 b, u16 c, u8 d);
extern void fn_800A2294(s32 a, u32 b);
extern void fn_800A237C(s32 a, s32 b, u8 c);
extern void fn_800A246C(s32 a, u32 b, s32 c, s32 d, u32 e, s32 f, s32 g);
extern void fn_800A26FC(void* a, s32 b);
extern void fn_800A7D4C(s32 phase, SpriteBufEntry* node);

/* ---- sdata / sbss / data / rodata owned by this unit ---- */

u8 lbl_803CBB18[8] = {0x61, 0x28, 0x3B, 0xF0, 0x40, 0x00, 0x00, 0x00};
u8 lbl_803CBB20[8] = {0x61, 0x28, 0x3B, 0xF0, 0x41, 0x00, 0x00, 0x00};
s32 lbl_803CBB28 = 0x280;
s32 lbl_803CBB2C = 0x1E0;
s32 lbl_803CBB30 = 1;
SpriteRenderState* lbl_803CBB34 = (SpriteRenderState*)lbl_802FEBF8;
SpriteRenderState* lbl_803CBB38 = (SpriteRenderState*)lbl_802FF978;
s32 lbl_803CBB3C = 0x400;
f32* lbl_803CBB40[2] = {(f32*)lbl_802FE918, NULL};

SpriteDrawList* lbl_803CC1E4;
s32 lbl_803CC1E0;
s32 lbl_803CC1D8[2];
s32 lbl_803CC1D4;
s32 lbl_803CC1D0;
s32 lbl_803CC1CC;
s32 lbl_803CC1C8;
s32 lbl_803CC1C4;
SpriteDrawList* lbl_803CC1C0;

SpriteBufEntry lbl_80111340[2][24] = {
    {{0, fn_800B2240, 0}},
    {{0, fn_800B2240, 0}},
};
u32 lbl_80111580[8] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
u32 lbl_801115A0[4] = {0x00000000, 0x00000001, 0x00010001, 0x00010000};
f32 lbl_801115B0[16] = {
    0.003125f, 0, 0, -1,
    0, -0.004464286f, 0, 1,
    0, 0, -0.000000059604645f, -1,
    0, 0, 0, 1,
};
u32 lbl_801115F0[20] = {
    0x00000000, 0x00000000, 0xCB7FFFFF, 0x00000000, 0x00000000,
    0x00000000, 0x43E00000, 0xCB7FFFFF, 0x00000000, 0x00000001,
    0x44200000, 0x43E00000, 0xCB7FFFFF, 0x00000000, 0x00010001,
    0x44200000, 0x00000000, 0xCB7FFFFF, 0x00000000, 0x00010000,
};

/* ---- helpers ---- */

static void spriteReserve(s32 need) {
    s32 deficit = need - (s32)(lbl_803CC1C0->end - lbl_803CC1C0->cursor);

    if (deficit > 0) {
        if (AllocateSprite(lbl_803CC1D4, deficit) > 0) {
            OSPanic(__FILE__, 0x19F, "SPRITE BUFFER OVERFLOW\n");
        }
    }
}

/* ---- functions ---- */

void fn_800B0D28(s32 value) {
    lbl_803CC1D8[0] = value;
    lbl_803CC1D8[1] = value;
}

void fn_800B0D38(s32 idx, s32 value) {
    u8* entry;

    if (idx < 0) {
        return;
    }
    if (idx >= lbl_803CBB30) {
        return;
    }
    entry = (u8*)lbl_80111340 + idx * 12;
    *(s32*)(entry + 0x120) = value;
    *(s32*)entry = value;
}

s32 AllocateSprite(s32 slot, s32 size) {
    s32 alloc;
    s32 count;
    s32 hi;
    s32 lo;
    u8* firstStart;
    u8* lastEnd;
    s32 amt;
    s32 avail;
    s32 used;
    s32 moved;
    u8* span;
    u8* dst;
    s32 k;
    s32 a;
    s32 d;

    if (size <= 0) {
        return 0;
    }
    if (size < lbl_803CBB3C) {
        alloc = ((lbl_803CBB3C + size - 1) / lbl_803CBB3C) * lbl_803CBB3C;
    } else {
        alloc = (size + 0x1F) & ~0x1F;
    }
    count = lbl_803CBB30;
    hi = slot;
    lo = slot;
    lastEnd = lbl_803CC1E4[count - 1].end;
    firstStart = lbl_803CC1E4[0].start;

    do {
        hi -= (hi > 0);
        used = lbl_803CC1E4[hi].cursor - lbl_803CC1E4[hi].start;
        avail = (s32)lbl_803CC1E4[hi]._04 - ((used + 0x1F) & ~0x1F);
        amt = (hi != slot) ? ((alloc > avail) ? avail : alloc) : 0;
        if (amt != 0) {
            lbl_803CC1E4[hi]._04 -= amt;
            lbl_803CC1E4[hi].end -= amt;
            span = lbl_803CC1E4[hi + 1].start;
            moved = 0;
            k = hi;
            do {
                k++;
                lbl_803CC1E4[k].start -= amt;
                moved += lbl_803CC1E4[k]._04;
                lbl_803CC1E4[k].end -= amt;
                lbl_803CC1E4[k].cursor -= amt;
            } while (k < slot);
            if (moved != 0) {
                dst = span - amt;
                memmove(dst, span, moved);
                if (lastEnd > dst) {
                    lastEnd = dst;
                }
                if (firstStart < span) {
                    firstStart = span;
                }
            }
            alloc -= amt;
            lbl_803CC1E4[slot]._04 += amt;
            lbl_803CC1E4[slot].end += amt;
        }

        a = (count - 1) ^ lo;
        d = (a >> 1) - (a & (count - 1));
        lo += ((u32)d >> 31);
        used = lbl_803CC1E4[lo].cursor - lbl_803CC1E4[lo].start;
        avail = (s32)lbl_803CC1E4[lo]._04 - ((used + 0x1F) & ~0x1F);
        amt = (lo != slot) ? ((alloc > avail) ? avail : alloc) : 0;
        if (amt != 0) {
            lbl_803CC1E4[lo]._04 -= amt;
            lbl_803CC1E4[lo].end -= amt;
            span = lbl_803CC1E4[slot + 1].start;
            moved = 0;
            if (slot + 1 <= lo) {
                for (k = slot + 1; k <= lo; k++) {
                    lbl_803CC1E4[k].start += amt;
                    moved += lbl_803CC1E4[k]._04;
                    lbl_803CC1E4[k].end += amt;
                    lbl_803CC1E4[k].cursor += amt;
                }
            }
            if (moved != 0) {
                dst = span + amt;
                memmove(dst, span, moved);
                if (firstStart < dst) {
                    firstStart = dst;
                }
                if (lastEnd > span) {
                    lastEnd = span;
                }
            }
            alloc -= amt;
            lbl_803CC1E4[slot]._04 += amt;
            lbl_803CC1E4[slot].end += amt;
        }
    } while (alloc > 0 && (hi != 0 || lo != count - 1));

    if (lastEnd < firstStart) {
        DCStoreRange(lastEnd, firstStart - lastEnd);
    }
    return (alloc > 0) ? alloc : 0;
}

void fn_800B117C(u8 value) {
    lbl_803CBB34->unk8C = value;
}

void fn_800B1188(void) {
    u8 saved[0x1C];
    u32 savedZMode;
    u8 savedUnk8C;
    u16 mask;

    memcpy(saved, lbl_803CBB38->blk30, 0x1C);
    savedZMode = lbl_803CBB38->zModeReg;
    savedUnk8C = lbl_803CBB38->unk8C;

    mask = 1 << lbl_803CC1C8;
    *(u16*)((u8*)lbl_801115F0 + 0x4C) = mask;
    *(u16*)((u8*)lbl_801115F0 + 0x38) = mask;
    *(u16*)((u8*)lbl_801115F0 + 0x3A) = mask;
    *(u16*)((u8*)lbl_801115F0 + 0x26) = mask;

    lbl_803CBB34->blk30[0] = 1.0f;
    lbl_803CBB34->blk30[1] = lbl_801115B0[0];
    lbl_803CBB34->blk30[2] = lbl_801115B0[3];
    lbl_803CBB34->blk30[3] = lbl_801115B0[5];
    lbl_803CBB34->blk30[4] = lbl_801115B0[7];
    lbl_803CBB34->blk30[5] = lbl_801115B0[10];
    lbl_803CBB34->blk30[6] = lbl_801115B0[11];

    lbl_803CBB34->unk8C = 1;
    if (lbl_803CBB34->zModeReg != 0x4000001F) {
        lbl_803CBB34->zModeReg = 0x4000001F;
    }

    DrawSprite(0x80, lbl_801115F0, 4, NULL, 0, 0);

    memcpy(lbl_803CBB34->blk30, saved, 0x1C);
    lbl_803CBB34->unk8C = savedUnk8C;
    lbl_803CBB34->zModeReg = savedZMode;
}

void DrawNullSprite(void* vtx, s32 count) {
    DrawSprite(0x98, vtx, count, NULL, 0, 0);
}

void fn_800B12DC(void* vtx, s32 count) {
    DrawSprite(0xA0, vtx, count, NULL, 0, 0);
}

void renderSprite(void* vtx, void* tex, u16 sMax, u16 tMax) {
    DrawSprite(0x80, vtx, 4, tex, sMax, tMax);
}

void DrawSprite_TexObj(void* vtx, void* texObj, s32 arg2) {
    DrawSprite(0x80, vtx, 4, texObj, ((SpriteTexObj*)texObj)->arg4, ((SpriteTexObj*)texObj)->arg5);
}

void fn_800B1388(void* vtx) {
    DrawSprite(0x80, vtx, 4, NULL, 0, 0);
}

void fn_800B13C0(void* src, u32* ids, s32 count) {
    u8* cursor = src;
    u8* dst = lbl_803C8A24;
    s32 i;

    for (i = 0; i < count; i++) {
        memcpy(dst, cursor, 0xC);
        *(u32*)(dst + 0xC) = *ids;
        memcpy(dst + 0x10, lbl_801115A0, 4);
        cursor += 0xC;
        dst += 0x14;
        ids++;
    }
    DrawSprite(0xA0, lbl_803C8A24, count, NULL, 0, 0);
}

void fn_800B1468(void* src, u32 value, SpriteTexObj* tex) {
    u8 chunks[0x50];
    u8* cursor = src;
    u8* dst = chunks;
    s32 i;

    for (i = 0; i < 4; i++) {
        memcpy(dst, cursor, 0xC);
        *(u32*)(dst + 0xC) = value;
        memcpy(dst + 0x10, (u8*)lbl_801115A0 + i * 4, 4);
        cursor += 0xC;
        dst += 0x14;
    }
    DrawSprite(0x80, chunks, 4, tex, tex->arg4, tex->arg5);
}

void DrawSprite(u32 flags, void* vtx, s32 count, void* texObj, u16 arg4, u16 arg5) {
    s32 result = 0;
    s32 mode;
    s32 changed;
    u8* hdr;

    if (texObj != NULL) {
        lbl_803CC0F0 = lbl_803CC1C0;
        result = fn_800B1EBC(texObj, 0, arg4, arg5);
        lbl_803CC0F0 = NULL;
    }

    if (memcmp(lbl_803CBB38->blk30, lbl_803CBB34->blk30, 0x1C) != 0) {
        memcpy(lbl_803CBB38->blk30, lbl_803CBB34->blk30, 0x1C);
        spriteReserve(0x21);
        lbl_803CC1C0->cursor[0] = 0x10;
        *(u16*)(lbl_803CC1C0->cursor + 1) = 6;
        *(u16*)(lbl_803CC1C0->cursor + 3) = 0x1020;
        lbl_803CC1C0->cursor += 5;
        *(u32*)lbl_803CC1C0->cursor = *(u32*)&lbl_803CBB34->blk30[1];
        lbl_803CC1C0->cursor += 4;
        *(u32*)lbl_803CC1C0->cursor = *(u32*)&lbl_803CBB34->blk30[2];
        lbl_803CC1C0->cursor += 4;
        *(u32*)lbl_803CC1C0->cursor = *(u32*)&lbl_803CBB34->blk30[3];
        lbl_803CC1C0->cursor += 4;
        *(u32*)lbl_803CC1C0->cursor = *(u32*)&lbl_803CBB34->blk30[4];
        lbl_803CC1C0->cursor += 4;
        *(u32*)lbl_803CC1C0->cursor = *(u32*)&lbl_803CBB34->blk30[5];
        lbl_803CC1C0->cursor += 4;
        *(u32*)lbl_803CC1C0->cursor = *(u32*)&lbl_803CBB34->blk30[6];
        lbl_803CC1C0->cursor += 4;
        *(u32*)lbl_803CC1C0->cursor = (u32)lbl_803CBB34->blk30[0];
        lbl_803CC1C0->cursor += 4;
        changed = 1;
    } else {
        changed = 0;
    }
    result |= changed;

    if (memcmp(lbl_803CBB38->mtx, lbl_803CBB34->mtx, 0x30) != 0) {
        PSMTXCopy(lbl_803CBB34->mtx, lbl_803CBB38->mtx);
        spriteReserve(0x35);
        lbl_803CC1C0->cursor[0] = 0x10;
        *(u16*)(lbl_803CC1C0->cursor + 1) = 0xB;
        *(u16*)(lbl_803CC1C0->cursor + 3) = 0;
        lbl_803CC1C0->cursor += 5;
        memcpy(lbl_803CC1C0->cursor, lbl_803CBB34->mtx, 0x30);
        lbl_803CC1C0->cursor += 0x30;
        changed = 1;
    } else {
        changed = 0;
    }
    result |= changed;

    if (lbl_803CBB34->renderingMode != lbl_803CBB38->renderingMode) {
        lbl_803CBB38->renderingMode = lbl_803CBB34->renderingMode;
        spriteReserve(0xA);
        lbl_803CC0F0 = lbl_803CC1C0;
        switch (lbl_803CBB34->renderingMode) {
        case 0:
            fn_800A1BB0(0, 0, 0, 0);
            break;
        case 1:
            fn_800A1BB0(1, 4, 5, 0);
            break;
        case 2:
            fn_800A1BB0(1, 4, 6, 0);
            break;
        case 3:
            fn_800A1BB0(3, 4, 5, 0);
            break;
        }
        changed = 1;
    } else {
        changed = 0;
    }
    result |= changed;

    mode = (lbl_803CBB34->unk8C != 0) ? 2 : 0;
    if (lbl_803CBB38->unk8D == mode) {
        if (lbl_803CBB38->zModeReg != lbl_803CBB34->zModeReg) {
            lbl_803CBB38->zModeReg = lbl_803CBB34->zModeReg;
            spriteReserve(5);
            lbl_803CC1C0->cursor[0] = 0x61;
            *(u32*)(lbl_803CC1C0->cursor + 1) = lbl_803CBB38->zModeReg;
            lbl_803CC1C0->cursor += 5;
            changed = 1;
        } else {
            changed = 0;
        }
        result |= changed;
    } else {
        lbl_803CBB38->unk8D = mode;
        if (mode == 0) {
            if (lbl_803CBB38->zModeReg != lbl_803CBB34->zModeReg) {
                lbl_803CBB38->zModeReg = lbl_803CBB34->zModeReg;
                spriteReserve(5);
                lbl_803CC1C0->cursor[0] = 0x61;
                *(u32*)(lbl_803CC1C0->cursor + 1) = lbl_803CBB34->zModeReg;
                lbl_803CC1C0->cursor += 5;
            }
            spriteReserve(5);
            lbl_803CC0F0 = lbl_803CC1C0;
            fn_800A1E3C(4, 0, 0, 7, 0);
        } else {
            if (lbl_803CBB38->zModeReg != 0x40000013) {
                lbl_803CBB38->zModeReg = 0x40000013;
                spriteReserve(5);
                lbl_803CC1C0->cursor[0] = 0x61;
                *(u32*)(lbl_803CC1C0->cursor + 1) = 0x40000013;
                lbl_803CC1C0->cursor += 5;
            }
            spriteReserve(5);
            lbl_803CC0F0 = lbl_803CC1C0;
            fn_800A1E3C(7, 0, 0, 7, 0);
        }
        lbl_803CC0F0 = NULL;
        result |= 1;
    }

    if (lbl_803CBB34->field80 >= 0 && result == 0) {
        hdr = lbl_803CC1C0->start + lbl_803CBB34->field80;
        if (hdr[0] == 0x80 && flags == 0x80 && lbl_803CC1C0->cursor == hdr + *(u16*)(hdr + 1) * 0x14 + 3 &&
            *(u16*)(hdr + 1) < 0xFFFF - count) {
            spriteReserve(count * 0x14);
            memcpy(lbl_803CC1C0->cursor, vtx, count * 0x14);
            lbl_803CC1C0->cursor += count * 0x14;
            *(u16*)(hdr + 1) += count;
            return;
        }
    }

    lbl_803CBB34->field80 = lbl_803CC1C0->cursor - lbl_803CC1C0->start;
    spriteReserve(count * 0x14 + 3);
    lbl_803CC1C0->cursor[0] = flags;
    *(u16*)(lbl_803CC1C0->cursor + 1) = count;
    lbl_803CC1C0->cursor += 3;
    memcpy(lbl_803CC1C0->cursor, vtx, count * 0x14);
    lbl_803CC1C0->cursor += count * 0x14;
}

static s32 spritePopcount16(u16 v) {
    s32 n = 0;

    while (v != 0) {
        n += v & 1;
        v = (v >> 1) & 0x7FFF;
    }
    return n;
}

BOOL fn_800B1EBC(SpriteTexObj* tex, s32 idx, u16 a, u16 b) {
    BOOL changed = FALSE;
    s32 idx1 = idx + 1;
    s32 flag;
    s32 need;
    s32 pa = 0;
    s32 pb = 0;

    lbl_803CBB34->tab68[idx] = lbl_803CBB34->count84;
    lbl_803CBB34->count84++;
    if (lbl_803CBB34->tab4C[idx] != (u32)tex) {
        lbl_803CBB34->tab4C[idx] = (u32)tex;
        flag = (tex->data04 != NULL);
        need = (flag * 7 + 4) * 5;
        if (need - (s32)(lbl_803CC1C0->end - lbl_803CC1C0->cursor) > 0) {
            if (AllocateSprite(lbl_803CC1D4, need - (s32)(lbl_803CC1C0->end - lbl_803CC1C0->cursor)) > 0) {
                OSPanic(__FILE__, 0x19F, "SPRITE BUFFER OVERFLOW\n");
            }
        }
        if (tex->data04 != NULL) {
            s32 r26 = (idx << 13) + 0xC0000;

            fn_800A26FC(tex->data04, r26);
            fn_800A237C(idx1, r26, tex->b1A);
        }
        if (tex->b0C != 0 && spritePopcount16(tex->arg4) <= 1) {
            pa = tex->b0C;
        }
        if (tex->b0D != 0 && spritePopcount16(tex->arg5) <= 1) {
            pb = tex->b0D;
        }
        fn_800A1F40(idx1, pa, pb, tex->b0E, tex->b0F, 0, 0, 0, (f32)(u32)tex->b15, (f32)(u32)tex->b16, tex->f10);
        fn_800A2194(idx1, tex->arg4, tex->arg5, tex->b17);
        fn_800A2294(idx1, tex->_00);
        changed = TRUE;
    }

    if (lbl_803CBB34->u86 != a || lbl_803CBB34->u88 != b) {
        lbl_803CBB34->u86 = a;
        lbl_803CBB34->u88 = b;
        if (0xF - (s32)(lbl_803CC1C0->end - lbl_803CC1C0->cursor) > 0) {
            if (AllocateSprite(lbl_803CC1D4, 0xF - (s32)(lbl_803CC1C0->end - lbl_803CC1C0->cursor)) > 0) {
                OSPanic(__FILE__, 0x19F, "SPRITE BUFFER OVERFLOW\n");
            }
        }
        fn_800A246C(idx, a, 0, 0, b, 0, 0);
        changed = TRUE;
    }
    return changed;
}

void setTextRenderingMode(s32 mode) {
    lbl_803CBB34->renderingMode = mode;
}

BOOL fn_800B216C(GXBool compareEnable, GXCompare func, GXBool updateEnable) {
    u32 reg = compareEnable | (func << 1) | (updateEnable << 4) | (0x40 << 24);

    if (lbl_803CBB34->zModeReg == reg) {
        return FALSE;
    }
    lbl_803CBB34->zModeReg = reg;
    return TRUE;
}

void fn_800B21A8(int mode) {
    if (mode == 2) {
        u32 prev = lbl_803CBB34->zModeReg;

        if (fn_800B216C(GX_TRUE, GX_LESS, GX_TRUE)) {
            lbl_803CBB34->savedZModeReg = prev;
        }
    } else if (mode != 0) {
        fn_800B216C(GX_TRUE, GX_LEQUAL, GX_TRUE);
    } else {
        fn_800B216C(GX_TRUE, GX_ALWAYS, GX_TRUE);
    }
}

void fn_800B2240(SpriteBufEntry* entry) {
    SpriteDrawList* rec = entry->rec;
    Mtx ident;
    GXTexObj texObj;
    GXColor fogColor = {0, 0, 0, 0};
    s32 size;

    GXSetScissor(lbl_803CC1CC, lbl_803CC1D0, lbl_803CBB28, lbl_803CBB2C);
    GXSetZMode(1, 7, 1);
    GXSetZCompLoc(1);
    GXSetBlendMode(1, 4, 5, 0);
    GXSetCullMode(0);
    GXSetFog(0, 0.0f, 0.0f, 0.0f, 0.0f, fogColor);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(11, 1);
    GXSetVtxDesc(13, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 11, 1, 5, 0);
    GXSetVtxAttrFmt(0, 13, 1, 2, lbl_803CC1C8);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(0, 1, 4, 0x3C, 0, 0x7D);
    GXInitTexObj(&texObj, lbl_80111580, 4, 4, 5, 0, 0, 0);
    GXInitTexObjLOD(&texObj, 1, 1, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    GXLoadTexObj(&texObj, 0);
    GXLoadTexObj(&texObj, 1);
    GXSetNumTevStages(1);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetTevColorIn(0, 15, 10, 8, 15);
    GXSetTevAlphaIn(0, 7, 5, 4, 7);
    GXSetTevColorOp(0, 0, 0, 0, 0, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
    GXSetNumIndStages(0);
    GXSetTevDirect(0);
    GXSetProjectionv((f32*)lbl_803CBB40[0]);
    PSMTXIdentity(ident);
    GXLoadPosMtxImm(ident, 0);
    GXSetCurrentMtx(0);

    size = (s32)(rec->cursor - rec->start);
    GXCallDisplayList(rec->start, size);
}

void fn_800B24D4(s32 idx) {
    u8* a = (u8*)lbl_802FEBF8 + idx * 0x90;

    lbl_803CC1D4 = idx;
    lbl_803CBB34 = (SpriteRenderState*)a;
    lbl_803CBB38 = (SpriteRenderState*)(a + 0xD80);
    lbl_803CBB40[0] = (f32*)(lbl_802FE918 + idx * 0x1C);
    lbl_803CC1C0 = lbl_803CC1E4 + idx;
}

void fn_800B251C(void) {
    u32* ids = lbl_802FE8B8;
    s32 off = 0;
    s32 k;
    s32 buf;
    s32 count;
    u8* entry;
    u8* ring;
    u8* ctxBase;
    u8* ctxNext;
    SpriteDrawList* rec;

    if (lbl_803CC1C0 == NULL) {
        return;
    }

    lbl_803CC1C0 = lbl_803CC1E4;
    for (k = 0; k < lbl_803CBB30; k++) {
        rec = lbl_803CC1C0;
        if (rec->cursor - rec->start != 0) {
            while (((rec->cursor - rec->start) & 0x1F) != 0) {
                *rec->cursor++ = 0;
            }
            DCStoreRangeNoSync(rec->start, rec->cursor - rec->start);
            entry = (u8*)lbl_80111340 + lbl_803CC1C4 * 0x120 + off;
            ((SpriteBufEntry*)entry)->rec = rec;
            ((SpriteBufEntry*)entry)->fn = fn_800B2240;
            fn_800A7D4C(*ids, (SpriteBufEntry*)entry);
        }
        lbl_803CC1C0 = rec + 1;
        off += 12;
        ids++;
    }

    count = lbl_803CBB30;
    buf = lbl_803CC1C4 ^ 1;
    lbl_803CC1D4 = count;
    lbl_803CC1C4 = buf;
    ring = (u8*)lbl_802FE8B8 + 0x1E40 + buf * 0x180;
    ctxBase = (u8*)lbl_802FE8B8 + 0x340 + count * 0x90;
    ctxNext = ctxBase + 0xD80;
    lbl_803CC1E4 = (SpriteDrawList*)ring;
    lbl_803CBB34 = (SpriteRenderState*)ctxBase;
    lbl_803CBB38 = (SpriteRenderState*)ctxNext;
    lbl_803CBB40[0] = (f32*)((u8*)lbl_802FE8B8 + 0x60 + count * 0x1C);
    lbl_803CC1C0 = (SpriteDrawList*)(ring + count * 16);
    lbl_803CC1C0->end = ((SpriteDrawList*)ring)->start + lbl_803CC1E0;

    while (lbl_803CC1D4 != 0) {
        lbl_803CC1D4--;
        lbl_803CC1C0 = lbl_803CC1C0 - 1;
        lbl_803CBB34 = (SpriteRenderState*)((u8*)lbl_803CBB34 - 0x90);
        lbl_803CBB38 = (SpriteRenderState*)((u8*)lbl_803CBB38 - 0x90);
        lbl_803CBB40[0] = (f32*)((u8*)lbl_803CBB40[0] - 0x1C);
        memset(lbl_803CBB34, 0, 0x90);
        PSMTXIdentity(lbl_803CBB34->mtx);
        memcpy(lbl_803CBB34->blk30, lbl_803CBB40[0], 0x1C);
        lbl_803CBB34->renderingMode = 1;
        lbl_803CBB34->field80 = -1;
        memcpy(lbl_803CBB38, lbl_803CBB34, 0x90);
    }
    lbl_803CC1D8[lbl_803CC1C4] = 0;
}

void fn_800B27A4(s32 idx) {
    u8* p;
    u16 mask;

    if (idx < 0) {
        return;
    }
    if (idx > 14) {
        return;
    }
    mask = 1 << idx;
    lbl_803CC1C8 = idx;
    p = (u8*)lbl_801115A0;
    *(u16*)(p + 0xC) = mask;
    *(u16*)(p + 0xA) = mask;
    *(u16*)(p + 0x8) = mask;
    *(u16*)(p + 0x6) = mask;
}

void fn_800B27DC(f32* src, u32 idx) {
    SpriteRenderState* ctx;
    u32 isOne = !(1 - idx);
    u32 off = (isOne + 2) * 4;

    ctx = lbl_803CBB34;
    ctx->blk30[0] = (f32)idx;
    ctx->blk30[1] = src[0];
    ctx->blk30[2] = *(f32*)((u8*)src + off);
    ctx->blk30[3] = src[5];
    ctx->blk30[4] = *(f32*)((u8*)src + off + 0x10);
    ctx->blk30[5] = src[10];
    ctx->blk30[6] = src[11];
}

void fn_800B2854(u8* a, s32 b, f32* vtx, u32 flag, s32 count, u32* src, u32* lens) {
    s32 half;
    s32 per;
    s32 k;
    s32 off;
    s32 len;
    s32 buf;
    u8* aCur;
    u8* bCur;
    u8* ring;
    u8* ctxA;
    u32 isOne;
    f32* e;
    f32* p;

    lbl_803CBB30 = count;
    half = b / 2;
    lbl_803CC1E0 = half;
    memcpy(lbl_802FE8B8, src, count * 4);

    half = b / 2;
    aCur = a;
    bCur = a + half;
    ring = (u8*)lbl_802FE8B8 + 0x1E40;
    per = half / count;
    off = 0;

    for (k = 0; k < count; k++) {
        len = (lens != NULL) ? (s32)lens[k] : per;
        fn_800A1A70(ring, aCur, len);
        fn_800A1A70(ring + 0x180, bCur, len);
        isOne = !(1 - flag);
        e = (f32*)((u8*)lbl_803CBB40[0] + off);
        p = (f32*)((u8*)vtx + ((isOne + 2) * 4));
        e[0] = (f32)flag;
        e[1] = vtx[0];
        e[2] = p[0];
        e[3] = vtx[5];
        e[4] = p[4];
        e[5] = vtx[10];
        e[6] = vtx[11];
        aCur += len;
        bCur += len;
        ring += 0x10;
        off += 0x1C;
    }

    lbl_803CC1D4 = count;
    buf = lbl_803CC1C4;
    ring = (u8*)lbl_802FE8B8 + 0x1E40 + buf * 0x180;
    ctxA = (u8*)lbl_802FE8B8 + 0x340 + count * 0x90;
    lbl_803CBB34 = (SpriteRenderState*)ctxA;
    lbl_803CBB38 = (SpriteRenderState*)(ctxA + 0xD80);
    lbl_803CC1E4 = (SpriteDrawList*)ring;
    lbl_803CC1C0 = (SpriteDrawList*)(ring + count * 16);
    lbl_803CBB40[0] = (f32*)((u8*)lbl_802FE8B8 + 0x60 + count * 0x1C);
    lbl_803CC1C0->end = lbl_803CC1E4[0].start + lbl_803CC1E0;

    while (lbl_803CC1D4 != 0) {
        lbl_803CC1D4--;
        lbl_803CC1C0 = lbl_803CC1C0 - 1;
        lbl_803CBB34 = (SpriteRenderState*)((u8*)lbl_803CBB34 - 0x90);
        lbl_803CBB38 = (SpriteRenderState*)((u8*)lbl_803CBB38 - 0x90);
        lbl_803CBB40[0] = (f32*)((u8*)lbl_803CBB40[0] - 0x1C);
        memset(lbl_803CBB34, 0, 0x90);
        PSMTXIdentity(lbl_803CBB34->mtx);
        memcpy(lbl_803CBB34->blk30, lbl_803CBB40[0], 0x1C);
        lbl_803CBB34->renderingMode = 1;
        lbl_803CBB34->field80 = -1;
        memcpy(lbl_803CBB38, lbl_803CBB34, 0x90);
    }
    lbl_803CC1D8[0] = 0;
    lbl_803CC1D8[1] = 0;
}
