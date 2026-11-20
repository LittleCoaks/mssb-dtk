#include <string.h>
#include "Unknown/File_0x8000ba3c.h"
#include "Dolphin/stl.h"
#include "Unknown/sprt.h"
#include "Unknown/File_0x8000a0ac.h"

/* The UI sprite buffer the handlers fill: updateHUDRelatedUI reads it as a
 * HUDSprite, SetSpriteRect as a SpriteRectBuf, the others as raw bytes. */
extern u8 lbl_80366188[];
extern u32 lbl_803CBBD8;
extern f32 lbl_803CC458;

void fn_8000A0AC(void* out, f32 t, u8* a, u8* b);
u32 fn_8000A3EC(Mtx a, Mtx b, u8* c, u8* d, void* ctx, f32 t, f32 s);
void fn_800B1388(void* sprite);

/* Advances a record past itself for a frame that has not reached it yet.
 * The size class is the record's low 15 bits of the type word. */
static u8* skipUIRecord(u8* rec, u8* child, u32 slotWords) {
    switch (*(u16*)rec & 0x7FFF) {
    case 0:
        return rec + ((*(u16*)(child + 2) >> 2) << 2);
    case 1:
        return rec + slotWords * 4;
    case 2:
    case 3:
        return rec + *(u16*)(rec + 6) * 4;
    default:
        return rec;
    }
}

int updateMenuOrBackgroundUI(u32* frame, struct UILayout* layout, int elementIndex, Mtx mtx, u32 arg4, u32 arg5,
                             u32* arg6, s16* path) {
    u8* elem;
    u8* child;
    u8* rec;
    u8* sel[2];
    u8 buf[2][0x50];
    Mtx m1;
    Mtx m2;
    Vec vec;
    u32 frameVal;
    u32 frameArg;
    u32 childArg6;
    u32 result;
    u32 curTime;
    u32 slotWords;
    int remaining;
    int nChildren;
    int i;
    int k;
    int m;
    u8* cur;
    u8* r4p;
    u8* r5p;
    u32 sv;
    u32 rr;
    u32 gg;
    u32 bb;
    u32 aa;
    u32 mode;

    if (path != NULL) {
        path[0] = elementIndex;
    }

    frameVal = *frame;
    elem = *(u8**)(layout->elementTable + elementIndex * 4 + 8);
    slotWords = layout->unk0[5];

    result = 0;
    *arg6 = 0;

    /* Keyframe search over the first child's 12-byte records, latest first. */
    child = *(u8**)(elem + 8);
    for (i = *(u16*)child; i != 0; i--) {
        rec = child + 4 + (i - 1) * 12;
        if (frameVal >= ((u32)*(u16*)rec << 16)) {
            u32 kind;

            *arg6 = (u32)(rec + 4);
            kind = *(u16*)(rec + 2);
            result = kind + 1;
            if (kind == 0) {
                u32 span = (u32)*(u16*)rec << 16;

                frameVal %= span;
            } else if (kind == 2) {
                u32 lo = (u32)*(u16*)(rec + 4) << 16;
                u32 hi = (u32)*(u16*)rec << 16;

                frameVal = lo + ((frameVal - lo) % (hi - lo));
            }
            *frame = frameVal;
            break;
        }
    }

    nChildren = *(u32*)elem & 0x7FFFFFFF;
    lbl_80366188[0x7F] = 0;
    if (path != NULL) {
        path[1] = 0;
    }

    /* Children n-1 down to 1 each contribute one selected record to the
     * two-slot working buffers. */
    for (k = nChildren - 1; k > 0; k--) {
        child = *(u8**)(elem + 8 + k * 4);
        remaining = *(u16*)child;
        rec = child + 4;
        sel[1] = rec;

        while (remaining != 0) {
            remaining--;
            sel[0] = rec;
            curTime = *(u16*)(rec + 2);
            if (frameVal >= (curTime << 16)) {
                /* The frame has reached this record: the rest of the walk
                 * only refines the current time. */
                if ((*(u8*)rec & 0x80) != 0 && remaining != 0) {
                    int ctr = remaining;

                    do {
                        rec = skipUIRecord(rec, child, slotWords);
                        if (!(remaining != 1 && (*(u8*)rec & 0x80))) {
                            curTime = *(u16*)(rec + 2);
                        }
                        remaining--;
                    } while (--ctr != 0);
                }
                break;
            }
            sel[1] = rec;
            rec = skipUIRecord(rec, child, slotWords);
        }

        /* Build the two working buffers from the selected records. */
        for (m = 0; m < 2; m++) {
            u8* dst = buf[m];

            switch (*(u16*)sel[m] & 0x7FFF) {
            case 0:
                memset(dst, 0, slotWords * 4);
                memcpy(dst, child + 4, *(u16*)(child + 2));
                break;
            case 1:
                memcpy(dst, sel[m], slotWords * 4);
                break;
            case 2:
                memset(dst, 0, slotWords * 4);
                memcpy(dst + 4, child + 8, *(u16*)(child + 2) - 4);
                memcpy(dst, sel[m], 4);
                {
                    u32 cnt = *(u16*)(sel[m] + 4);

                    r4p = sel[m] + *(u16*)(sel[m] + 6) * 4;
                    r5p = sel[m] + cnt * 2;
                    for (; cnt != 0; cnt--) {
                        u16 idx;

                        r4p -= 4;
                        r5p -= 2;
                        idx = *(u16*)(r5p + 8);
                        *(u32*)(dst + 4 + idx * 4) = *(u32*)r4p;
                    }
                }
                break;
            case 3: {
                u8* ent;
                u8* src;
                u32 count;

                memset(dst, 0, slotWords * 4);
                memcpy(dst + 4, child + 8, *(u16*)(child + 2) - 4);
                memcpy(dst, sel[m], 4);
                count = *(u16*)(sel[m] + 4);
                ent = sel[m] + 8;
                src = sel[m] + count * 4 + 8;
                for (i = count; i != 0; i--) {
                    u16 off = *(u16*)ent;
                    u16 len = *(u16*)(ent + 2);

                    memcpy(dst + 4 + off, src, len);
                    src += len;
                    ent += 4;
                }
                break;
            }
            default:
                break;
            }
        }
    }

    /* Selected buffer: buf[1] when its mode byte is set, otherwise buf[0]. */
    cur = buf[buf[1][4] != 0 ? 1 : 0];

    if (buf[0][4] != 0) {
        f32 t = lbl_803CC458;
        u32 a = *(u16*)(buf[0] + 2);
        u32 b = *(u16*)(cur + 2);
        u32 num = frameVal - (a << 16);
        u32 den = (b - a) << 16;

        if (num < den) {
            t = (f32)num / (f32)den;
        }
        if (buf[0][8] & 0x10) {
            fn_8000A0AC(&vec, t, buf[0], cur);
        }
        arg4 |= fn_8000A3EC(m1, m2, buf[0], cur, &vec, t, (f32)*(s16*)(cur + 0x18));
        PSMTXConcat(mtx, m1, m1);

        /* Modulate the four colour words of m2 by the packed colour in arg5. */
        for (i = 0; i < 4; i++) {
            sv = ((u32*)m2)[8 + i];
            rr = ((arg5 >> 24) * (sv >> 24)) / 255;
            gg = (((arg5 >> 16) & 0xFF) * ((sv >> 16) & 0xFF)) / 255;
            bb = (((arg5 >> 8) & 0xFF) * ((sv >> 8) & 0xFF)) / 255;
            aa = ((arg5 & 0xFF) * (sv & 0xFF)) / 255;
            ((u32*)m2)[8 + i] = (rr << 24) | (gg << 16) | (bb << 8) | aa;
        }

        mode = buf[0][4];
        if (mode == 1 || (mode >= 3 && mode < 8)) {
            if (path != NULL) {
                void (*cb)(u8*, Mtx) = (void (*)(u8*, Mtx))*(u32*)(lbl_80366188 + 0x88);

                if (cb != NULL) {
                    *(s16**)(lbl_80366188 + 0x6C) = path;
                    *(Mtx**)(lbl_80366188 + 0x64) = &m1;
                    *(u32*)(lbl_80366188 + 0x68) = ((u32*)m2)[8];
                    cb(lbl_80366188, m1);
                }
            }
            if (mode == 3) {
                frameArg = frameVal - ((u32)curTime << 16);
                childArg6 = 0;
                updateMenuOrBackgroundUI(&frameArg, layout, *(u16*)(buf[0] + 6), m1, arg4,
                                         ((u32*)m2)[8], &childArg6, path + 2);
            }
        }
    }

    if (path != NULL) {
        path[1] += 1;
    }

    return result;
}

typedef struct HUDKeyEntry {
    /* 0x0 */ u16 key;
    /* 0x2 */ u16 value;
    /* 0x4 */ u8 payload[8];
} HUDKeyEntry; // size 0xC

typedef struct HUDKeyList {
    /* 0x0 */ u16 count;
    /* 0x2 */ u16 unk2;
    /* 0x4 */ HUDKeyEntry entries[1];
} HUDKeyList;

typedef struct HUDSprite {
    /* 0x00 */ f32 v00;
    /* 0x04 */ f32 v04;
    /* 0x08 */ f32 v08;
    /* 0x0C */ u32 w0C;
    /* 0x10 */ u8 unk10[0x4];
    /* 0x14 */ f32 v14;
    /* 0x18 */ f32 v18;
    /* 0x1C */ f32 v1C;
    /* 0x20 */ u32 w20;
    /* 0x24 */ u8 unk24[0x4];
    /* 0x28 */ f32 v28;
    /* 0x2C */ f32 v2C;
    /* 0x30 */ f32 v30;
    /* 0x34 */ u32 w34;
    /* 0x38 */ u8 unk38[0x4];
    /* 0x3C */ f32 v3C;
    /* 0x40 */ f32 v40;
    /* 0x44 */ f32 v44;
    /* 0x48 */ u32 w48;
    /* 0x4C */ u32 w4C;
    /* 0x50 */ s16 s50;
    /* 0x52 */ s16 s52;
    /* 0x54 */ u8 b54;
    /* 0x55 */ u8 b55;
    /* 0x56 */ u8 unk56[0x1A];
    /* 0x70 */ u32 w70;
    /* 0x74 */ u8 unk74[0x8];
    /* 0x7C */ u16 h7C;
    /* 0x7E */ u8 b7E;
    /* 0x7F */ u8 b7F;
    /* 0x80 */ u8 unk80[0x4];
    /* 0x84 */ u32 (*callback)(void* sprite);
    /* 0x88 */ u8 unk88[0x8];
} HUDSprite; // size 0x90

extern Mtx lbl_800E65D0;
extern f32 lbl_803CC470;
extern f32 lbl_803CC474;
extern f32 lbl_803CC478;
extern f32 lbl_803CC47C;
extern f32 lbl_803CC480;
extern f32 lbl_803CC484;

void fn_8000E030(u8* sprite, Mtx a, Mtx b);
void fn_8000D8A4(u8* sprite, Mtx a, Mtx b);
void fn_800B117C(u32 flag);
void fn_800B1188(void);

/* Advances a sub-record entry cursor by the size its kind implies. */
static u8* hudAdvanceEntry(u8* ent, u16 subSize, u8 layoutCount) {
    u32 kind = *(u16*)ent & 0x7FFF;

    switch (kind) {
    case 0:
        return ent + (subSize >> 2) * 4;
    case 1:
        return ent + layoutCount * 4;
    case 2:
    case 3:
        return ent + *(u16*)(ent + 6) * 4;
    default:
        return ent;
    }
}

s32 updateHUDRelatedUI(u32* frame, UILayout* layout, int elementIndex, Mtx mtx, u32 arg4, u32 arg5, u32* arg6, TextureHeader* textures) {
    f32 ctx[4];
    f32 vtx[16];
    Mtx mtxC;
    Mtx mtxA;
    f32 scale;
    Mtx mtxB;
    f32 f184;
    u16 h188;
    u8 b18a;
    u8 bufs[2][0x50];
    u32 chan[8][4];
    u32 recArg6;
    u32 local18;
    u32* colors;
    u8* pair[2];
    u32* cursor;
    u8* element;
    HUDKeyList* keys;
    u32 frameVal;
    u32 flags;
    u32 key19 = 0;
    s32 retVal = 0;
    s32 partsLeft;
    s32 i;
    u32 layoutCount;

    element = *(u8**)(layout->elementTable + 8 + elementIndex * 4);
    partsLeft = *(u32*)element & 0x7FFFFFFF;
    layoutCount = layout->unk0[5];
    flags = arg4;
    frameVal = *frame;
    *arg6 = 0;

    /* Keyed lookup over the element's frame list, last entry first. */
    keys = *(HUDKeyList**)(element + 8);
    for (i = keys->count; i != 0; i--) {
        HUDKeyEntry* e = &keys->entries[i - 1];

        if (frameVal < ((u32)e->key << 16)) {
            continue;
        }
        *arg6 = (u32)e->payload;
        retVal = e->value + 1;
        if (e->value == 0) {
            frameVal %= (u32)e->key << 16;
        } else if (e->value == 2) {
            u32 base = (u32)*(u16*)e->payload << 16;
            frameVal = base + (frameVal - base) % (((u32)e->key << 16) - base);
        }
        *frame = frameVal;
        break;
    }

    /* Walk the element's sub-records from the last one down to index 1. */
    partsLeft -= 1;
    cursor = (u32*)(element + 8) + partsLeft;
    do {
        u8* sub = *(u8**)cursor;
        u8* ent = sub + 4;
        u32 nEntries;
        u32 hit = 0;

        cursor--;
        pair[1] = ent;
        nEntries = *(u16*)sub;

        while (nEntries != 0) {
            u16 key2;

            nEntries--;
            key2 = *(u16*)(ent + 2);
            key19 = key2;
            pair[0] = ent;

            if (frameVal < ((u32)key2 << 16)) {
                pair[1] = ent;
                ent = hudAdvanceEntry(ent, *(u16*)(sub + 2), (u8)layoutCount);
                continue;
            }

            /* This entry is reached: step through the rest of the sub-record. */
            if ((ent[0] & 0x80) != 0 && nEntries != 0) {
                u32 rem = nEntries;

                while (rem != 0) {
                    ent = hudAdvanceEntry(ent, *(u16*)(sub + 2), (u8)layoutCount);
                    if (rem == 1 || (ent[0] & 0x80) == 0) {
                        key19 = *(u16*)(ent + 2);
                    }
                    rem--;
                }
            }
            hit = 1;
            break;
        }

        if (hit) {
            s32 k;

            for (k = 0; k < 2; k++) {
                u8* e = pair[k];
                u8* b = bufs[k];
                u32 kind = *(u16*)e & 0x7FFF;

                switch (kind) {
                case 0:
                    memset(b, 0, layoutCount * 4);
                    memcpy(b, sub + 4, *(u16*)(sub + 2));
                    break;
                case 1:
                    memcpy(b, e, layoutCount * 4);
                    break;
                case 2: {
                    u32 n;
                    u32 h6;
                    u32 t;

                    memset(b, 0, layoutCount * 4);
                    memcpy(b + 4, sub + 8, *(u16*)(sub + 2) - 4);
                    memcpy(b, e, 4);
                    n = *(u16*)(e + 4);
                    h6 = *(u16*)(e + 6);
                    for (t = 0; t < n; t++) {
                        u16 idx = *(u16*)(e + 8 + 2 * (n - 1 - t));
                        u32 val = *(u32*)(e + 4 * h6 - 4 * (t + 1));

                        *(u32*)(b + 4 + idx * 4) = val;
                    }
                    break;
                }
                case 3: {
                    u32 n;
                    u32 t;
                    u8* src;
                    u8* tbl;

                    memset(b, 0, layoutCount * 4);
                    memcpy(b + 4, sub + 8, *(u16*)(sub + 2) - 4);
                    memcpy(b, e, 4);
                    n = *(u16*)(e + 4);
                    src = e + 4 * n + 8;
                    tbl = e + 8;
                    for (t = 0; t < n; t++) {
                        u16 off = *(u16*)tbl;
                        u16 len = *(u16*)(tbl + 2);

                        memcpy(b + 4 + off, src, len);
                        src += len;
                        tbl += 4;
                    }
                    break;
                }
                default:
                    break;
                }
            }

            if (bufs[0][4] != 0) {
                u8* rec = bufs[1][4] != 0 ? bufs[1] : bufs[0];
                f32 t = lbl_803CC458;
                u32 k0 = *(u16*)&bufs[0][2];
                u32 diff = frameVal - (k0 << 16);
                u32 span = ((u32)*(u16*)(rec + 2) - k0) << 16;

                if (diff < span) {
                    t = (f32)diff / (f32)span;
                }
                if ((bufs[0][8] & 0x10) != 0) {
                    fn_8000A0AC(ctx, t, bufs[0], rec);
                }

                flags |= fn_8000A3EC(mtxA, mtxB, bufs[0], rec, ctx, t, (f32)*(s16*)(rec + 0x18));
                PSMTXConcat(mtx, mtxA, mtxA);

                if ((bufs[0][9] & 0x80) != 0) {
                    fn_800B1188();
                }
                fn_800B117C(bufs[0][8] & 1);

                if ((bufs[0][8] & 1) != 0) {
                    f32 s = scale;
                    f32 d = -s / lbl_803CC470;

                    memcpy(mtxC, lbl_800E65D0, sizeof(Mtx));
                    mtxC[0][0] = d;
                    mtxC[1][1] = d;
                    mtxC[2][2] = d;
                    mtxC[2][3] = s;
                    PSMTXInverse(mtxC, mtxC);
                    PSMTXConcat(mtxC, mtxA, mtxA);
                    mtxC[0][0] = lbl_803CC474;
                    mtxC[1][1] = lbl_803CC474;
                    mtxC[2][2] = lbl_803CC474;
                    mtxC[2][3] = lbl_803CC478;
                    PSMTXConcat(mtxC, mtxA, mtxA);
                }

            /* Tint the four vertex colours by the packed multiplier in arg5. */
            colors = (u32*)((u8*)mtxB + 0x20);
            {
                s32 j;

                for (j = 0; j < 4; j++) {
                    u32 c = colors[j];
                    u32 outc[4];
                    s32 ch;

                    chan[0][j] = c >> 24;
                    chan[1][j] = (c >> 16) & 0xFF;
                    chan[2][j] = (c >> 8) & 0xFF;
                    chan[3][j] = c & 0xFF;
                    chan[4][j] = arg5 >> 24;
                    chan[5][j] = (arg5 >> 16) & 0xFF;
                    chan[6][j] = (arg5 >> 8) & 0xFF;
                    chan[7][j] = arg5 & 0xFF;
                    for (ch = 0; ch < 4; ch++) {
                        outc[ch] = (chan[ch][j] * chan[4 + ch][j]) / 255;
                    }
                    colors[j] = (outc[0] << 24) | (outc[1] << 16) | (outc[2] << 8) | outc[3];
                }
            }

            /* Text rendering mode selection. */
            if (bufs[0][4] != 3) {
                switch (bufs[0][5]) {
                case 0:
                    setTextRenderingMode(1);
                    if ((bufs[0][9] & 0x80) != 0) {
                        fn_800B1188();
                    }
                    break;
                case 1:
                    setTextRenderingMode(2);
                    break;
                case 2:
                    setTextRenderingMode(3);
                    break;
                default:
                    break;
                }
            }

            switch (bufs[0][4]) {
            case 1: {
                f32 a = lbl_803CC47C;
                f32 b = lbl_803CC480;
                HUDSprite* spr = (HUDSprite*)lbl_80366188;

                vtx[0] = a;
                vtx[1] = a;
                vtx[2] = b;
                vtx[3] = a;
                vtx[4] = a;
                vtx[5] = b;
                vtx[6] = b;
                vtx[7] = b;
                AddVec2iToQuad(vtx, mtxA, (s32*)mtxB);

                spr->v00 = vtx[0];
                spr->v04 = vtx[1];
                spr->v08 = vtx[2];
                spr->v14 = vtx[4];
                spr->v18 = vtx[5];
                spr->v1C = vtx[6];
                spr->v28 = vtx[12];
                spr->v2C = vtx[13];
                spr->v30 = vtx[14];
                spr->v3C = vtx[8];
                spr->v40 = vtx[9];
                spr->v44 = vtx[10];
                spr->w0C = colors[0];
                spr->w34 = colors[2];
                spr->w20 = colors[3];
                spr->w48 = colors[1];
                spr->h7C = (u16)(flags | ((bufs[0][8] >> 5) & 1));
                spr->b7E = 0;
                local18 = 1;
                if ((bufs[0][8] & 8) != 0 && spr->callback != NULL) {
                    local18 = spr->callback(spr);
                }
                if (local18 != 0) {
                    fn_800B1388(spr);
                }
                break;
            }
            case 2: {
                HUDSprite* spr = (HUDSprite*)lbl_80366188;

                local18 = 1;
                if ((bufs[0][8] & 8) != 0 && spr->callback != NULL) {
                    spr->w70 = 0;
                    spr->h7C = 1;
                    spr->b7E = 1;
                    memcpy(spr, mtxA, 0x30);
                    spr->w48 = *(u32*)((u8*)mtxB + 0x20);
                    spr->w4C = *(u32*)((u8*)mtxB + 0x24);
                    spr->s50 = *(s16*)&bufs[0][0x10];
                    spr->s52 = *(s16*)&bufs[0][0x12];
                    spr->v40 = lbl_803CC484;
                    spr->v44 = f184;
                    spr->b54 = (u8)h188;
                    spr->b55 = b18a;
                    local18 = spr->callback(spr);
                }
                if (local18 != 0) {
                    if (lbl_803CC47C == f184) {
                        fn_8000E030(bufs[0], mtxA, mtxB);
                    } else {
                        fn_8000D8A4(bufs[0], mtxA, mtxB);
                    }
                }
                break;
            }
            case 3:
                local18 = (u32)((s32)frameVal - (key19 << 16));
                updateHUDRelatedUI(&local18, layout, *(u16*)&bufs[0][6], mtxA, flags, *(u32*)((u8*)mtxB + 0x20), &recArg6, textures);
                break;
            case 4:
            case 5:
            case 6:
            case 7:
                SetSpriteRect(bufs[0], (u8*)textures, mtxA, (s32*)mtxB, (u16)flags);
                local18 = 1;
                if ((bufs[0][8] & 8) != 0 && ((HUDSprite*)lbl_80366188)->callback != NULL) {
                    local18 = ((HUDSprite*)lbl_80366188)->callback(lbl_80366188);
                }
                if (local18 != 0) {
                    DrawSprite_TexObj(lbl_80366188, (void*)lbl_803CBBD8, 0);
                }
                break;
            default:
                break;
            }

            }

            fn_800B117C(0);
        }
    } while (--partsLeft != 0);

    return retVal;
}

typedef struct UIKeyEntry {
    /* 0x0 */ u16 key;
    /* 0x2 */ u16 value;
    /* 0x4 */ u8 payload[8];
} UIKeyEntry; // size 0xC

typedef struct UIPartHeader {
    /* 0x0 */ u16 count;
    /* 0x2 */ u16 subSize;
} UIPartHeader;

typedef struct UIPartList {
    /* 0x0 */ u32 count;
    /* 0x4 */ u32 unk4;
    /* 0x8 */ UIPartHeader* parts[1];
} UIPartList;

typedef struct UIAnimRecord {
    /* 0x00 */ u8 kind;        // hi nibble: text rendering mode; lo nibble: draw op
    /* 0x01 */ u8 flags;       // bits 0x20 / 0x08 / 0x04 are tested
    /* 0x02 */ u16 elementIndex;
    /* 0x04 */ u8 unk04[8];
    /* 0x0C */ u16 key;
    /* 0x0E */ u8 unk0E[6];
    /* 0x14 */ s16 x;
    /* 0x16 */ s16 y;
    /* 0x18 */ u8 unk18[0x10];
} UIAnimRecord; // size 0x28

typedef struct UIDrawBlock {
    /* 0x00 */ f32 mtxRows[2][4];
    /* 0x20 */ u32 colors[4];
    /* 0x30 */ f32 extraF;
    /* 0x34 */ u16 extraH;
    /* 0x36 */ u8 extraB;
} UIDrawBlock;

typedef u32 (*SpriteCallback)(u8* sprite);


u32 fn_8000AF1C(void* mtxA, void* block, UIAnimRecord* rec, UIAnimRecord* next, u32 unkC, s16* bezierOut, f32 t);
void fn_8000E7BC(UIAnimRecord* rec, void* mtxA, void* block, u32 arg4);
void fn_8000E2D4(UIAnimRecord* rec, void* mtxA, void* block);
void fn_8000DC9C(UIAnimRecord* rec, void* mtxA, void* block);
void fn_8000EC0C(UIAnimRecord* rec, TextureHeader* textures, void* mtxA, void* block, u32 arg4);

s32 triggerDefaultHUDAction(u32* frame, struct UILayout* layout, int elementIndex, Mtx mtx, u32 arg4, u32 arg5, u32* arg6, TextureHeader* textures) {
    s32 rc = 0;
    u8* sprite = lbl_80366188;
    Mtx mtxA;
    UIDrawBlock block;
    s16 bezierOut[8];
    u32 frameCopy;
    u32 localC;
    u32 frameVal = *frame;
    UIPartList* elem = *(UIPartList**)(layout->elementTable + elementIndex * 4 + 8);
    u32 unkC = *(u32*)((u8*)layout + 0xC);
    UIPartHeader* part0 = elem->parts[0];
    s32 partIdx;
    s32 drawRet;

    if (part0->count != 0) {
        UIKeyEntry* e = (UIKeyEntry*)((u8*)part0 + 4 + part0->count * 12);
        u32 ctr;

        for (ctr = part0->count; ctr != 0; ctr--) {
            e--;
            if (frameVal >= ((u32)e->key << 16)) {
                *arg6 = (u32)((u8*)e + 4);
                rc = e->value + 1;
                if (e->value == 0) {
                    frameVal %= (u32)e->key << 16;
                } else if (e->value == 2) {
                    u32 a = (u32)*(u16*)((u8*)e + 4) << 16;
                    u32 b = (u32)e->key << 16;
                    frameVal = a + ((frameVal - a) % (b - a));
                }
                *frame = frameVal;
                break;
            }
        }
    }

    sprite[0x7f] = 0;
    partIdx = (s32)elem->count - 1;

    do {
        UIPartHeader* part = elem->parts[partIdx];
        UIAnimRecord* base = (UIAnimRecord*)((u8*)part + 4);
        UIAnimRecord* rec;
        UIAnimRecord* last = base + part->count - 1;
        s32 idx;

        for (idx = part->count; idx != 0;) {
            idx--;
            rec = base + idx;
            if (frameVal < ((u32)rec->key << 16)) {
                last = rec;
                continue;
            }

            {
                u32 chosenKey = rec->key;
                u32 curKey = rec->key;
                s32 c;

                if ((rec->flags & 0x20) && idx != 0) {
                    UIAnimRecord* prev = rec;
                    for (c = idx; c != 0; c--) {
                        prev--;
                        if (!((c != 1) && (prev->flags & 0x20))) {
                            chosenKey = prev->key;
                        }
                    }
                }

                if ((last->kind & 0xF) == 0) {
                    last = rec;
                }
                if ((rec->kind & 0xF) == 0) {
                    goto nextPart;
                }

                {
                    u32 nextKey = last->key;
                    u32 cur = frameVal - (curKey << 16);
                    u32 span = (nextKey - curKey) << 16;
                    f32 t = lbl_803CC458;
                    s32 hi;
                    s32 lo;
                    u32* colors = block.colors;
                    u32 i;

                    if (cur < span) {
                        t = (f32)cur / (f32)span;
                    }

                    if (rec->flags & 0x08) {
                        if (idx != 0 && ((rec - 1)->flags & 0x08)) {
                            if ((rec + 1)->flags & 0x08) {
                                interpolatePointsBezier_Vec2s(bezierOut, (s16*)(rec - 1), (s16*)rec, (s16*)(rec + 1), (s16*)(rec + 2), 1, t);
                            } else {
                                interpolatePointsBezier_Vec2s(bezierOut, (s16*)(rec - 1), (s16*)(rec - 1), (s16*)rec, (s16*)(rec + 1), 2, t);
                            }
                        } else if (idx != 0) {
                            interpolatePointsBezier_Vec2s(bezierOut, (s16*)rec, (s16*)(rec + 1), (s16*)(rec + 2), (s16*)(rec + 2), 0, t);
                        } else {
                            interpolatePointsBezier_Vec2s(bezierOut, (s16*)rec, (s16*)(rec + 1), (s16*)(rec + 1), (s16*)(rec + 2), 0, t);
                        }
                    }

                    arg4 |= fn_8000AF1C(mtxA, &block, rec, last, unkC, bezierOut, t);
                    PSMTXConcat(mtx, mtxA, mtxA);

                    for (i = 0; i < 4; i++) {
                        u32 w = colors[i];
                        u32 r = ((arg5 >> 24) * (w >> 24)) / 255;
                        u32 g = (((arg5 >> 16) & 0xFF) * ((w >> 16) & 0xFF)) / 255;
                        u32 b = (((arg5 >> 8) & 0xFF) * ((w >> 8) & 0xFF)) / 255;
                        u32 a = ((arg5 & 0xFF) * (w & 0xFF)) / 255;
                        colors[i] = (r << 24) | (g << 16) | (b << 8) | a;
                    }

                    hi = (rec->kind >> 4) & 0xF;
                    if (hi == 0) {
                        setTextRenderingMode(1);
                    } else if (hi == 1) {
                        setTextRenderingMode(2);
                    } else if (hi == 2) {
                        setTextRenderingMode(3);
                    }

                    lo = rec->kind & 0xF;
                    if (lo == 1 || lo == 2) {
                        fn_8000E7BC(rec, mtxA, &block, arg4);
                        drawRet = 1;
                        if (*(SpriteCallback*)(sprite + 0x84) != NULL && (rec->flags & 0x04)) {
                            drawRet = (*(SpriteCallback*)(sprite + 0x84))(sprite);
                        }
                        if (drawRet != 0) {
                            fn_800B1388(sprite);
                        }
                    } else if (lo == 3) {
                        drawRet = 1;
                        if (*(SpriteCallback*)(sprite + 0x84) != NULL && (rec->flags & 0x04)) {
                            *(UIAnimRecord**)(sprite + 0x78) = rec;
                            *(void**)(sprite + 0x70) = NULL;
                            *(u16*)(sprite + 0x7c) = 1;
                            sprite[0x7e] = 1;
                            memcpy(sprite, mtxA, 0x30);
                            *(u32*)(sprite + 0x48) = colors[0];
                            *(u32*)(sprite + 0x4c) = colors[1];
                            *(f32*)(sprite + 0x40) = lbl_803CC484;
                            *(s16*)(sprite + 0x50) = rec->x;
                            *(f32*)(sprite + 0x44) = block.extraF;
                            *(s16*)(sprite + 0x52) = rec->y;
                            sprite[0x54] = (u8)block.extraH;
                            sprite[0x55] = block.extraB;
                            drawRet = (*(SpriteCallback*)(sprite + 0x84))(sprite);
                        }
                        if (drawRet != 0) {
                            if (lbl_803CC47C == block.extraF) {
                                fn_8000E2D4(rec, mtxA, &block);
                            } else {
                                fn_8000DC9C(rec, mtxA, &block);
                            }
                        }
                    } else if (lo == 4) {
                        fn_8000EC0C(rec, textures, mtxA, &block, arg4);
                        drawRet = 1;
                        if (*(SpriteCallback*)(sprite + 0x84) != NULL && (rec->flags & 0x04)) {
                            drawRet = (*(SpriteCallback*)(sprite + 0x84))(sprite);
                        }
                        if (drawRet != 0) {
                            ((void (*)(u8*, u32))DrawSprite_TexObj)(sprite, lbl_803CBBD8);
                        }
                    } else if (lo == 5) {
                        frameCopy = frameVal - (chosenKey << 16);
                        localC = 0;
                        triggerDefaultHUDAction(&frameCopy, (struct UILayout*)layout, rec->elementIndex, mtxA, arg4, colors[0], &localC, textures);
                    }
                }
            }
            break;
        }

nextPart:
        partIdx--;
    } while (partIdx != 0);

    return rc;
}

s32 handleUIAction(u32* frame, UILayout* layout, int elementIndex, Mtx mtx, u32 arg4, u32 arg5, u32* arg6,
                    TextureHeader* textures) {
    s16 path[60];

    if (layout->unk6 == 0) {
        return triggerDefaultHUDAction(frame, layout, elementIndex, mtx, arg4, arg5, arg6, textures);
    } else if ((*(UILayoutElement**)(layout->elementTable + elementIndex * 4 + 8))->flags & 0x80000000) {
        path[0] = -1;
        path[1] = 0;
        return updateMenuOrBackgroundUI(frame, layout, elementIndex, mtx, arg4, arg5, arg6, &path[2]);
    } else {
        return updateHUDRelatedUI(frame, layout, elementIndex, mtx, arg4, arg5, arg6, textures);
    }
}

typedef struct SpriteVertex {
    f32 pos[3];
    u32 color;
    s16 u;
    s16 v;
} SpriteVertex;

typedef struct SpriteRectBuf {
    SpriteVertex verts[4];
    u8 unk50[0x20];
    u8* base;
    u8 unk74[8];
    u16 flags;
    u8 unk7e;
    u8 unk7f[0x11];
} SpriteRectBuf;


static void SetVertexPos(SpriteVertex* vtx, const f32* corner) {
    vtx->pos[0] = corner[0];
    vtx->pos[1] = corner[1];
    vtx->pos[2] = corner[2];
}

void SetSpriteRect(u8* sprite, u8* base, Mtx mtx, s32* vec2i, u16 flagBits) {
    f32 quad[16];
    u8* entry;
    u8* rect;
    f32 sizeX;
    f32 sizeY;
    u8 flags;
    SpriteRectBuf* buf;

    entry = base + *(u16*)(sprite + 6) * 0x20;
    rect = base + *(u16*)(entry + 0x20) * 0x20 + 4;
    lbl_803CBBD8 = (u32)rect;

    quad[0] = 0.0f;
    quad[1] = 0.0f;
    sizeX = 0.0f + (f32)*(u16*)(rect + 0xA);
    quad[3] = 0.0f;
    quad[4] = 0.0f;
    quad[2] = sizeX;
    quad[6] = sizeX;
    sizeY = 0.0f + (f32)*(u16*)(rect + 8);
    quad[5] = sizeY;
    quad[7] = sizeY;

    AddVec2iToQuad(quad, mtx, vec2i);

    buf = (SpriteRectBuf*)lbl_80366188;
    flags = sprite[8];
    if ((flags & 0x80) && (flags & 0x40)) {
        SetVertexPos(&buf->verts[0], &quad[12]);
        SetVertexPos(&buf->verts[1], &quad[4]);
        SetVertexPos(&buf->verts[2], &quad[0]);
        SetVertexPos(&buf->verts[3], &quad[8]);
    } else if (flags & 0x80) {
        SetVertexPos(&buf->verts[0], &quad[4]);
        SetVertexPos(&buf->verts[1], &quad[12]);
        SetVertexPos(&buf->verts[2], &quad[8]);
        SetVertexPos(&buf->verts[3], &quad[0]);
    } else if (flags & 0x40) {
        SetVertexPos(&buf->verts[0], &quad[8]);
        SetVertexPos(&buf->verts[1], &quad[0]);
        SetVertexPos(&buf->verts[2], &quad[4]);
        SetVertexPos(&buf->verts[3], &quad[12]);
    } else {
        SetVertexPos(&buf->verts[0], &quad[0]);
        SetVertexPos(&buf->verts[1], &quad[8]);
        SetVertexPos(&buf->verts[2], &quad[12]);
        SetVertexPos(&buf->verts[3], &quad[4]);
    }

    buf->unk7e = 0;
    buf->verts[0].color = vec2i[8];
    buf->verts[1].color = vec2i[9];
    buf->verts[2].color = vec2i[10];
    buf->verts[3].color = vec2i[11];

    buf->verts[0].u = 0;
    buf->verts[0].v = 0;
    buf->verts[1].u = 0;
    buf->verts[1].v = 0x400;
    buf->verts[2].u = 0x400;
    buf->verts[2].v = 0x400;
    buf->verts[3].u = 0x400;
    buf->verts[3].v = 0;

    buf->base = base;
    buf->flags = flagBits | ((flags >> 5) & 1);
}

void AddVec2iToQuad(f32* quad, Mtx mtx, s32* vec2i) {
    Mtx m;
    f32 pts[4][4];

    PSMTXCopy(mtx, m);
    pts[0][0] = quad[0] + (f32)vec2i[0];
    pts[0][1] = quad[1] + (f32)vec2i[1];
    pts[0][2] = 1.0f;
    pts[1][0] = quad[2] + (f32)vec2i[2];
    pts[1][1] = quad[3] + (f32)vec2i[3];
    pts[1][2] = 1.0f;
    pts[2][0] = quad[4] + (f32)vec2i[4];
    pts[2][1] = quad[5] + (f32)vec2i[5];
    pts[2][2] = 1.0f;
    pts[3][0] = quad[6] + (f32)vec2i[6];
    pts[3][1] = quad[7] + (f32)vec2i[7];
    pts[3][2] = 1.0f;

    PSMTXMultVec(m, (Vec*)pts[0], (Vec*)pts[0]);
    PSMTXMultVec(m, (Vec*)pts[1], (Vec*)pts[1]);
    PSMTXMultVec(m, (Vec*)pts[2], (Vec*)pts[2]);
    PSMTXMultVec(m, (Vec*)pts[3], (Vec*)pts[3]);

    quad[0] = pts[0][0];
    quad[1] = pts[0][1];
    quad[2] = pts[0][2];
    quad[4] = pts[1][0];
    quad[5] = pts[1][1];
    quad[6] = pts[1][2];
    quad[8] = pts[2][0];
    quad[9] = pts[2][1];
    quad[10] = pts[2][2];
    quad[12] = pts[3][0];
    quad[13] = pts[3][1];
    quad[14] = pts[3][2];
}
