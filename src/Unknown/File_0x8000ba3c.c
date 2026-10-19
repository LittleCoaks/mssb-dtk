#include "Unknown/File_0x8000ba3c.h"
#include "Unknown/File_0x8000d838.h"
#include "Dolphin/stl.h"

extern u8 lbl_80366188[];
extern f32 lbl_803CC458;

void fn_8000A0AC(Vec* out, f32 t, u8* a, u8* b);
u32 fn_8000A3EC(Mtx a, Mtx b, u8* c, u8* d, Vec* out, f32 t, f32 s);

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
