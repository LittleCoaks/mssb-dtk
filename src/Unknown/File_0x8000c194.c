#include <string.h>
#include "Unknown/File_0x8000c194.h"
#include "Unknown/File_0x8000d838.h"
#include "Unknown/File_0x8000e900.h"
#include "Unknown/File_0x8000ef1c.h"
#include "Unknown/sprt.h"

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

extern HUDSprite lbl_80366188;
extern u32 lbl_803CBBD8;
extern Mtx lbl_800E65D0;
extern f32 lbl_803CC458;
extern f32 lbl_803CC470;
extern f32 lbl_803CC474;
extern f32 lbl_803CC478;
extern f32 lbl_803CC47C;
extern f32 lbl_803CC480;
extern f32 lbl_803CC484;

void fn_8000A0AC(void* out, f32 t, u8* a, u8* b);
u32 fn_8000A3EC(Mtx out, Mtx out2, u8* a, u8* b, f32* ctx, f32 t, f32 scale);
void fn_8000E030(u8* sprite, Mtx a, Mtx b);
void fn_8000D8A4(u8* sprite, Mtx a, Mtx b);
void fn_800B117C(u32 flag);
void fn_800B1188(void);
void fn_800B1388(void* sprite);

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
                HUDSprite* spr = &lbl_80366188;

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
                HUDSprite* spr = &lbl_80366188;

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
                if ((bufs[0][8] & 8) != 0 && lbl_80366188.callback != NULL) {
                    local18 = lbl_80366188.callback(&lbl_80366188);
                }
                if (local18 != 0) {
                    DrawSprite_TexObj(&lbl_80366188, (void*)lbl_803CBBD8, 0);
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
