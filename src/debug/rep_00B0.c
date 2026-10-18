#define REP_HEADER_DATA_FN getRepHeaderData_rep00B0
#define __GDCurrentDL lbl_803CC0F0
#define GDInitGDLObj fn_800A1A70
#define GDPadCurr32 fn_800A1A88
#define GDOverflowed fn_800A1B80
#include "debug/rep_00B0.h"
#include "header_rep_data.h"
#include "Dolphin/gx.h"
#include "Dolphin/mtx.h"
#include "Dolphin/os.h"
#include "Dolphin/OS/OSCache.h"
#include "stl/math.h"
#include "Unknown/File_0x800b0724.h"
#include <string.h>


extern DbgGfxState lbl_1_common_bss_472B4;
f32 lbl_1_data_200[6] = {0.21f, -3.f, 17.26f, 0.21f, 3.f, 17.26f};
static Vec lbl_1_data_218 = {0.f, 1.f, 0.f};
static Vec lbl_1_data_224 = {0.f, 0.f, 0.f};
static f32 lbl_1_data_230[4] = {0.f, 0.f, 0.f, 0.f};
static GXColor lbl_1_data_240[21] = {
    {0x00, 0xC0, 0x00, 0xFF},
    {0x00, 0x70, 0x00, 0xFF},
    {0x00, 0x00, 0xC0, 0xFF},
    {0x00, 0x00, 0x70, 0xFF},
    {0xC0, 0x00, 0x00, 0xFF},
    {0x70, 0x00, 0x00, 0xFF},
    {0xC0, 0xC0, 0x00, 0xFF},
    {0x70, 0x70, 0x00, 0xFF},
    {0x00, 0xC0, 0xC0, 0xFF},
    {0x00, 0x70, 0x70, 0xFF},
    {0xC0, 0x00, 0xC0, 0xFF},
    {0x70, 0x00, 0x70, 0xFF},
    {0xFF, 0x00, 0x00, 0x40},
    {0x00, 0xFF, 0x00, 0x40},
    {0xFF, 0xFF, 0x00, 0x40},
    {0x00, 0x00, 0xFF, 0x40},
    {0xFF, 0x00, 0xFF, 0x40},
    {0x00, 0xFF, 0xFF, 0x40},
    {0xC0, 0xC0, 0x20, 0xFF},
    {0xFF, 0xFF, 0xFF, 0xFF},
    {0x3A, 0x6E, 0xA5, 0xFF},
};
static GXColor lbl_1_data_294 = {0x00, 0x00, 0x00, 0x00};

typedef struct DrawCallbackRec {
    s32 reserved;
    void (*fn)(void);
} DrawCallbackRec;

extern u8 drawStadiumRelated;
extern void fn_800A7D4C(s32 arg0, void *arg1);

DrawCallbackRec lbl_1_data_298[2] = {{0, fn_1_19AC}, {0, fn_1_19AC}};

#define FBITS(f) (*(u32 *)&(f))
#define FLOAT_SIGN_MASK 0x80000000
#define DL_BUFFER_SIZE 0x80000

static Vec lbl_1_bss_60[8];

static inline void dlWriteU8(u8 v) {
    GDOverflowCheck(1);
    __GDWrite(v);
}

static inline void dlWriteU16(u16 v) {
    GDOverflowCheck(2);
    __GDWrite((v >> 8) & 0xFF);
    __GDWrite(v & 0xFF);
}

static inline void dlWriteBits(u32 bits) {
    __GDWrite(bits >> 24);
    __GDWrite((bits >> 16) & 0xFF);
    __GDWrite((bits >> 8) & 0xFF);
    __GDWrite(bits & 0xFF);
}

static inline void dlWriteF32(f32 v) {
    GDOverflowCheck(4);
    dlWriteBits(*(u32 *)&v);
}

static inline void dlPos(f32 x, f32 y, f32 z) {
    dlWriteF32(x);
    dlWriteF32(y);
    dlWriteF32(z);
}

static inline void dlVertex(const Vec *p, u8 idx) {
    dlPos(p->x, p->y, p->z);
    dlWriteU8(idx);
}

static inline u8 keyToIdx(u32 key) {
    return (key >> 7) + ((key & 0x7F) - 1) * 2;
}

static inline void dlVertexKey(const Vec *p, u32 key) {
    dlPos(p->x, p->y, p->z);
    GDOverflowCheck(1);
    __GDWrite(keyToIdx(key));
}

static inline u32 keyIdx32(u32 key) {
    return (key >> 7) + ((key & 0x7F) - 1) * 2;
}

static inline void dlWriteByte(u32 v) {
    GDOverflowCheck(1);
    __GDWrite(v);
}

static inline void dlVertexOf(const DlVertex *v) {
    dlPos(v->pos.x, v->pos.y, v->pos.z);
    dlWriteByte(keyIdx32(v->key));
}

static inline void copyVec(Vec *dst, const Vec *src) {
    *dst = *src;
}

// .text:0x00004A24 size:0x3B4
void fn_1_4A24(PickState *st, DlPrim *prim) {
    Vec t[3];
    Vec e[3];
    u32 cnt;
    u32 flip;
    u8 type;
    DlVertex *v = (DlVertex *)prim;

    for (;;) {
        cnt = ((DlPrim *)v)->count;
        if (cnt == 0) {
            break;
        }
        type = ((DlPrim *)v)->type;
        v = (DlVertex *)((u8 *)v + 4);
        if (type == 0) {
            do {
                f32 hitT;
                BOOL in;
                PSMTXMultVec(st->mtx, &v[0].pos, &t[0]);
                PSMTXMultVec(st->mtx, &v[1].pos, &t[1]);
                PSMTXMultVec(st->mtx, &v[2].pos, &t[2]);
                in = t[0].x * t[1].y - t[1].x * t[0].y >= 0.0f;
                in &= t[1].x * t[2].y - t[2].x * t[1].y >= 0.0f;
                in &= t[2].x * t[0].y - t[0].x * t[2].y >= 0.0f;
                if (in) {
                    PSVECSubtract(&t[1], &t[0], &e[0]);
                    PSVECSubtract(&t[2], &t[1], &e[1]);
                    PSVECCrossProduct(&e[0], &e[1], &e[2]);
                    hitT = -PSVECDotProduct(&e[2], &t[0]) / e[2].z;
                    if (hitT >= 0.0f && st->dist > hitT) {
                        st->dist = hitT;
                        st->hit = v[2].key;
                        copyVec(&st->normal, &e[2]);
                    }
                }
                v += 3;
            } while (--cnt != 0);
        } else {
            flip = 0;
            PSMTXMultVec(st->mtx, &v[0].pos, &t[0]);
            PSMTXMultVec(st->mtx, &v[1].pos, &t[1]);
            v += 2;
            do {
                u32 inside;
                PSMTXMultVec(st->mtx, &v->pos, &t[2]);
                e[0].z = t[2].x * t[0].y - t[0].x * t[2].y;
                e[0].x = t[0].x * t[1].y - t[1].x * t[0].y;
                e[0].y = t[1].x * t[2].y - t[2].x * t[1].y;
                if (flip != 0) {
                    inside = (e[0].z <= 0.0f) & (e[0].x <= 0.0f) & (e[0].y <= 0.0f);
                } else {
                    inside = (e[0].z >= 0.0f) & (e[0].x >= 0.0f) & (e[0].y >= 0.0f);
                }
                if (inside) {
                    f32 hitT;
                    PSVECSubtract(&t[1], &t[0], &e[0]);
                    PSVECSubtract(&t[2], &t[1], &e[1]);
                    PSVECCrossProduct(&e[0], &e[1], &e[2]);
                    hitT = -PSVECDotProduct(&e[2], &t[0]) / e[2].z;
                    if (hitT >= 0.0f && st->dist > hitT) {
                        st->dist = hitT;
                        st->hit = v->key;
                        if (flip == 0) {
                            copyVec(&st->normal, &e[2]);
                        } else {
                            st->normal.x = -e[2].x;
                            st->normal.y = -e[2].y;
                            st->normal.z = -e[2].z;
                        }
                    }
                }
                copyVec(&t[0], &t[1]);
                copyVec(&t[1], &t[2]);
                flip ^= 1;
                v++;
            } while (--cnt != 0);
        }
    }
}

// .text:0x00004728 size:0x2FC
u32 fn_1_4728(Vec *ray, Vec *out) {
    u8 flags[260];
    PickState st;
    Vec d[4];
    Mtx inv;
    s32 i;
    u32 allOut;
    f32 (*box)[6];
    DlPrim **item;
    u8 *flag;
    f32 dist;

    box = lbl_1_common_bss_472B4.list->boxes;
    memset(flags, 1, lbl_1_common_bss_472B4.count);
    allOut = TRUE;
    flag = flags;
    i = lbl_1_common_bss_472B4.count;
    do {
        PSVECSubtract(&ray[0], (Vec *)&(*box)[0], &d[0]);
        PSVECSubtract((Vec *)&(*box)[3], &ray[0], &d[1]);
        PSVECSubtract(&ray[1], (Vec *)&(*box)[0], &d[2]);
        PSVECSubtract((Vec *)&(*box)[3], &ray[1], &d[3]);
        if (!(((FBITS(d[0].x) & FBITS(d[2].x)) | (FBITS(d[1].x) & FBITS(d[3].x))) & FLOAT_SIGN_MASK) &&
            !(((FBITS(d[0].y) & FBITS(d[2].y)) | (FBITS(d[1].y) & FBITS(d[3].y))) & FLOAT_SIGN_MASK) &&
            !(((FBITS(d[0].z) & FBITS(d[2].z)) | (FBITS(d[1].z) & FBITS(d[3].z))) & FLOAT_SIGN_MASK)) {
            *flag = 0;
            allOut = FALSE;
        }
        box++;
        flag++;
    } while (--i != 0);
    if (allOut) {
        return 0;
    }
    makeLookAtMatrix(st.mtx, &ray[0], &lbl_1_data_218, &ray[1]);
    dist = dolsqrtf2(PSVECSquareDistance(&ray[1], &ray[0]));
    flag = flags;
    i = lbl_1_common_bss_472B4.count;
    item = lbl_1_common_bss_472B4.list->prims;
    st.unk6C = dist;
    st.dist = dist;
    st.hit = 0;
    do {
        if (*flag++ == 0) {
            fn_1_4A24(&st, *item);
        }
        item++;
    } while (--i != 0);
    if (st.hit != 0) {
        PSMTXInverse(st.mtx, inv);
        lbl_1_data_224.z = -st.dist;
        PSMTXMultVec(inv, &lbl_1_data_224, &out[0]);
        PSMTXTranspose(st.mtx, inv);
        PSMTXMultVec(inv, &st.normal, &out[1]);
        PSVECNormalize(&out[1], &out[1]);
        return st.hit;
    }
    return 0;
}

// .text:0x00004290 size:0x498
void fn_1_4290(f32 *box) {
    dlWriteU8(GX_LINES);
    dlWriteU16(2);
    dlVertex((Vec *)&box[0], 0x13);
    dlVertex((Vec *)&box[3], 0x14);
}

// .text:0x00004074 size:0x21C
void fn_1_4074(Vec *p) {
    dlVertex(p, 0x12);
}

// .text:0x00003E38 size:0x23C
void fn_1_3E38(Vec *p, u32 key) {
    dlVertexKey(p, key);
}

// .text:0x000025BC size:0x187C
void fn_1_25BC(DlPrim *p) {
    u32 i;
    u32 cnt;
    DlVertex *vi;
    u32 prev;
    DlVertex *v;
    u32 left;
    u32 key;
    u32 n;

    do {
        n = p->count;
        if (p->type == 0) {
            v = p->verts;
            cnt = n * 3;
            dlWriteU8(GX_TRIANGLES);
            dlWriteU16(cnt);
            for (; cnt != 0; cnt--) {
                dlVertexOf(v);
                v++;
            }
            v = p->verts;
            for (left = n; left != 0; left--) {
                DlVertex *start;
                dlWriteU8(GX_LINESTRIP);
                dlWriteU16(4);
                start = v;
                dlVertex(&v++->pos, 0x12);
                dlVertex(&v++->pos, 0x12);
                dlVertex(&v++->pos, 0x12);
                dlVertex(&start->pos, 0x12);
            }
        } else {
            cnt = 0;
            i = n + 2;
            vi = p->verts;
            prev = p->verts[0].key;
            for (; i != 0; vi++, i--) {
                cnt++;
                if (prev != vi->key) {
                    prev = vi->key;
                    cnt += 2;
                }
            }
            v = p->verts;
            prev = v->key;
            dlWriteU8(GX_TRIANGLESTRIP);
            dlWriteU16(cnt);
            for (left = n + 2; left != 0; v++, left--) {
                key = v->key;
                if (prev != key) {
                    u8 idx;
                    prev = key;
                    dlVertexKey(&v[-2].pos, key);
                    idx = keyIdx32(key);
                    dlVertex(&v[-1].pos, idx);
                }
                dlVertexKey(&v->pos, key);
            }
            cnt = n + 2;
            vi = p->verts;
            dlWriteU8(GX_LINESTRIP);
            dlWriteU16(cnt);
            for (; cnt != 0; cnt--) {
                dlVertex(&vi++->pos, 0x12);
            }
            vi = p->verts;
            cnt = (n + 3) >> 1;
            dlWriteU8(GX_LINESTRIP);
            dlWriteU16(cnt);
            for (; cnt != 0; cnt--) {
                dlVertex(&vi->pos, 0x12);
                vi += 2;
            }
            vi = &p->verts[1];
            cnt = (n + 2) >> 1;
            dlWriteU8(GX_LINESTRIP);
            dlWriteU16(cnt);
            for (; cnt != 0; cnt--) {
                dlVertex(&vi->pos, 0x12);
                vi += 2;
            }
        }
        p = (DlPrim *)v;
    } while (*(u32 *)p != 0);
}

// .text:0x00001DBC size:0x800
void fn_1_1DBC(s32 a, s32 b, s32 c, s32 d, s32 e) {
    u8 idx;
    dlVertex(&lbl_1_bss_60[a], e);
    idx = e;
    dlVertex(&lbl_1_bss_60[b], idx);
    dlVertex(&lbl_1_bss_60[c], idx);
    dlVertex(&lbl_1_bss_60[d], idx);
}

// .text:0x00001BF8 size:0x1C4
void fn_1_1BF8(f32 *boxes, s32 idx) {
    f32 *b = &boxes[idx * 6];

    lbl_1_bss_60[0].x = b[0];
    lbl_1_bss_60[0].y = b[1];
    lbl_1_bss_60[0].z = b[5];
    lbl_1_bss_60[1].x = b[3];
    lbl_1_bss_60[1].y = b[1];
    lbl_1_bss_60[1].z = b[5];
    lbl_1_bss_60[2].x = b[3];
    lbl_1_bss_60[2].y = b[1];
    lbl_1_bss_60[2].z = b[2];
    lbl_1_bss_60[3].x = b[0];
    lbl_1_bss_60[3].y = b[1];
    lbl_1_bss_60[3].z = b[2];
    lbl_1_bss_60[4].x = b[0];
    lbl_1_bss_60[4].y = b[4];
    lbl_1_bss_60[4].z = b[5];
    lbl_1_bss_60[5].x = b[3];
    lbl_1_bss_60[5].y = b[4];
    lbl_1_bss_60[5].z = b[5];
    lbl_1_bss_60[6].x = b[3];
    lbl_1_bss_60[6].y = b[4];
    lbl_1_bss_60[6].z = b[2];
    lbl_1_bss_60[7].x = b[0];
    lbl_1_bss_60[7].y = b[4];
    lbl_1_bss_60[7].z = b[2];
    dlWriteU8(GX_QUADS);
    dlWriteU16(0x18);
    fn_1_1DBC(7, 6, 2, 3, 12);
    fn_1_1DBC(5, 4, 0, 1, 13);
    fn_1_1DBC(3, 2, 1, 0, 14);
    fn_1_1DBC(4, 5, 6, 7, 15);
    fn_1_1DBC(4, 7, 3, 0, 16);
    fn_1_1DBC(6, 5, 1, 2, 17);
}

// .text:0x000019AC size:0x24C
void fn_1_19AC(void) {
    u32 size;
    u32 i;
    DlPrim **item;
    struct { Vec a; Vec b; } span;

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetCopyClear(lbl_1_data_294, 0xFFFFFF);
    GXSetCullMode(GX_CULL_FRONT);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetArray(GX_VA_CLR0, lbl_1_data_240, 4);
    GXSetLineWidth(0x12, GX_TO_ONE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXLoadPosMtxImm(lbl_1_common_bss_472B4.mtx, 0);
    item = lbl_1_common_bss_472B4.list->prims;
    GDInitGDLObj(&lbl_1_common_bss_472B4.gdl, lbl_1_common_bss_472B4.dlBuf, DL_BUFFER_SIZE);
    __GDCurrentDL = &lbl_1_common_bss_472B4.gdl;
    if (lbl_1_common_bss_472B4.selected < 0) {
        for (i = 0; i < lbl_1_common_bss_472B4.count; i++) {
            fn_1_25BC(*item++);
        }
        fn_1_4290(lbl_1_data_200);
    } else {
        fn_1_25BC(item[lbl_1_common_bss_472B4.selected]);
        fn_1_4290(lbl_1_data_200);
        if (lbl_1_common_bss_472B4.showBoxes != 0) {
            fn_1_1BF8((f32 *)lbl_1_common_bss_472B4.list->boxes, lbl_1_common_bss_472B4.selected);
        }
    }
    if (fn_1_4728((Vec *)lbl_1_data_200, &span.a) != 0) {
        PSVECAdd(&span.a, &span.b, &span.b);
        fn_1_4290((f32 *)&span.a);
    }
    GDPadCurr32();
    size = lbl_1_common_bss_472B4.gdl.pDisplayListData - lbl_1_common_bss_472B4.gdl.begin;
    DCFlushRangeNoSync(lbl_1_common_bss_472B4.dlBuf, size);
    lbl_1_common_bss_472B4.dlSize = size;
    if (size > DL_BUFFER_SIZE) {
        OSReport("Gd Buffer overflow:%d\n", size);
        for (;;) {
        }
    }
    GXCallDisplayList(lbl_1_common_bss_472B4.dlBuf, size);
}

// .text:0x0000196C size:0x40
void fn_1_196C(void) {
    fn_800A7D4C(0, &lbl_1_data_298[drawStadiumRelated]);
}
