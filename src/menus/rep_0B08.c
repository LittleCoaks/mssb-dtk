#include "menus/rep_0B08.h"
#include "menus/text_71EC4.h"
#include "header_rep_data.h"
#include "Dolphin/mtx.h"
#include "Dolphin/vec.h"
#include "stl/math.h"
#include "PowerPC_EABI_Support/Runtime/__mem.h"
#include "C3/light/light.h"

typedef void (*Rep0B08StateFn)(u8 *obj);

extern u8 *lbl_2_bss_1A8248;
extern u8 *lbl_2_bss_1A824C;
extern u8 inputParams[0x268];
extern u8 hugeAnimStruct[];
extern u8 lbl_2_data_2EA4[];
extern u8 lbl_2_data_3150[];
extern u8 lbl_2_data_3C84[];
extern u8 lbl_2_data_2E80[];
extern u8 lbl_2_data_3198[];
extern u8 lbl_2_data_3C20[];
extern u8 lbl_2_data_3ED4[];
extern f32 lbl_2_data_3F44[];
extern s16 *lbl_2_data_3C2C[];
extern f32 lbl_2_data_3EF4[];
extern f32 lbl_2_data_3F0C[];
extern f32 lbl_2_data_3F2C[];
extern f32 lbl_2_data_3F5C;
extern u8 lbl_2_data_3D30[];
extern s32 lbl_2_data_3C40[];
extern s32 lbl_2_data_3C5C[];

extern Rep0B08StateFn lbl_2_data_2A1F4[];
extern Rep0B08StateFn lbl_2_data_2A200[];
extern Rep0B08StateFn lbl_2_data_2A208[];
extern Rep0B08StateFn lbl_2_data_2A210[];
extern Rep0B08StateFn lbl_2_data_2A220[];
extern Rep0B08StateFn lbl_2_data_2A234[];
extern Rep0B08StateFn lbl_2_data_2A248[];
extern Rep0B08StateFn lbl_2_data_2A250[];
extern Rep0B08StateFn lbl_2_data_2A25C[];
extern Rep0B08StateFn lbl_2_data_2A268[];
extern Rep0B08StateFn lbl_2_data_2A274[];
extern Rep0B08StateFn lbl_2_data_2A280[];
extern Rep0B08StateFn lbl_2_data_2A28C[];
extern Rep0B08StateFn lbl_2_data_2A29C[];
extern Rep0B08StateFn lbl_2_data_2A2AC[];
extern Rep0B08StateFn lbl_2_data_2A2B8[];
extern Rep0B08StateFn lbl_2_data_2A2C4[];
extern Rep0B08StateFn lbl_2_data_2A2D4[];
extern Rep0B08StateFn lbl_2_data_2A2E0[];

f32 fn_2_4A18C(f32 angle);
void fn_2_8CD58(s32 idx, s16 a, u8 b, s32 c, s16 d, s32 e, s32 f);
s16 fn_2_4A2C4(f32 angle);
s16 fn_2_4A150(s16 angle);
f32 fn_2_4A1E8(f32 x);
s16 fn_2_4A234(f32 x, f32 y);
s16 fn_2_4A310(s16 a, s16 b);

extern u8 lbl_2_data_2A340[];
extern u8 AtBat_ButtonInput1[];
extern f32 lbl_2_bss_A170;
s32 fn_2_8CC88(s32 p);
void fn_2_46C88(s32 a, s32 b);
void fn_80062890(s32 flag);

void fn_2_9033C(s32 idx, void *src, f32 f);
int rand(void);
void fn_2_92654(s32 slot, u8 value);
void fn_2_8F73C(s32 idx, u8 val);
#define REP_SLOT(idx) (lbl_2_bss_1A8248 + 0x1610 + (idx) * 0xD8)

// Per-index ids and entries live in the table at lbl_2_bss_1A824C + 0x190000 + 0x7756.
static void rep0B08SetCurState(s32 n, s32 k) {
    if (*(s16 *)(lbl_2_bss_1A824C + 0x190000 + 0x7756 + n * 2) != k) {
        u8 *ent = lbl_2_data_3C84 + k * 6;
        fn_2_8CD58(n, *(s16 *)(ent + 0x0), ent[0x4], 1, *(s16 *)(ent + 0x2), 0, 0);
        *(s16 *)(lbl_2_bss_1A824C + 0x190000 + 0x7756 + n * 2) = k;
    }
}

static void rep0B08TransitionSlot(s32 idx, u8 state) {
    u8 *slot = REP_SLOT(idx);
    slot[0xC3] = state;
    *(s16 *)(slot + 0x94) = 0;
}

typedef struct {
    u8 _pad[0x1610];
    CssSlot slots[8];
} Rep0B08SlotTable;

static void rep0B08EnableSlot(s32 idx) {
    ((Rep0B08SlotTable *)lbl_2_bss_1A8248)->slots[idx]._C0 = 1;
}

static u8 rep0B08SlotsWithinRange(s32 idx, s32 otherIdx) {
    u8 *slot = REP_SLOT(idx);
    u8 *other = REP_SLOT(otherIdx);
    f32 distance = PSVECDistance((Vec *)slot, (Vec *)other);
    f32 radius;
    f32 padding;
    if (idx == 0) {
        radius = lbl_2_data_3F0C[otherIdx];
        padding = lbl_2_data_3EF4[lbl_2_bss_1A8248[0x441C]];
    } else {
        radius = lbl_2_data_3F0C[idx];
        padding = lbl_2_data_3EF4[lbl_2_bss_1A8248[0x441C]];
    }
    if (distance < radius + padding && slot[0xC0] != 0 && other[0xC0] != 0) {
        return TRUE;
    }
    return FALSE;
}

static s32 rep0B08NearestSlotZeroPoint(void) {
    Vec ref;
    Vec cand;
    f32 best = 10000.0f;
    s32 bestIdx = 0;
    s32 i;
    memcpy(&ref, REP_SLOT(0), sizeof(Vec));
    for (i = 0; i < 0x33; i++) {
        f32 distance;
        memcpy(&cand, lbl_2_data_2EA4 + i * (s32)sizeof(Vec), sizeof(Vec));
        distance = PSVECDistance(&ref, &cand);
        if (distance < best) {
            best = distance;
            bestIdx = i;
        }
    }
    return bestIdx;
}

typedef struct {
    u8 _pad[0x7756];
    s16 firstState;
} Rep0B08AnimationStates;

static void rep0B08SetSlotState(s32 idx, s32 state) {
    u8 *slot = REP_SLOT(idx);
    s32 n = *(s32 *)(slot + 0x80);
    u8 *ent = lbl_2_data_3C84 + state * 6;
    Rep0B08AnimationStates *states = (Rep0B08AnimationStates *)(lbl_2_bss_1A824C + 0x190000);
    if ((&states->firstState)[n] != state) {
        fn_2_8CD58(n, *(s16 *)(ent + 0x0), ent[0x4], 1, *(s16 *)(ent + 0x2), 0, 0);
        states = (Rep0B08AnimationStates *)(lbl_2_bss_1A824C + 0x190000);
        (&states->firstState)[*(s32 *)(slot + 0x80)] = state;
    }
}

static void rep0B08SetSlotTarget(s32 idx, f32 x, f32 z) {
    u8 *slot = REP_SLOT(idx);
    f32 dx;
    f32 dz;
    *(f32 *)(slot + 0x0C) = x;
    *(f32 *)(slot + 0x14) = z;
    dx = x - *(f32 *)(slot + 0x00);
    dz = z - *(f32 *)(slot + 0x08);
    if (dx == 0.0f && dz == 0.0f) {
        *(f32 *)(slot + 0x38) = 0.0f;
        *(f32 *)(slot + 0x50) = 0.0f;
    } else {
        *(f32 *)(slot + 0x50) = dolsqrtf2(dx * dx + dz * dz);
    }
    slot[0xBB] = 1;
}

// .text:0x00071C6C size:0x258 mapped:0x806B0D00
void fn_2_71C6C(u8 *obj) {
    s32 idx = *(s32 *)(obj + 0x80);
    u8 *slot = REP_SLOT(idx);
    f32 dx;
    f32 dz;
    lbl_2_bss_1A8248[idx * 0xD8 + 0x16D0] = 1;
    memcpy(obj + 0x74, lbl_2_data_2EA4 + *(s16 *)(lbl_2_bss_1A8248 + 0x16C0) * 0xC, 12);
    *(f32 *)(slot + 0x0C) = *(f32 *)(obj + 0x74);
    *(f32 *)(slot + 0x14) = *(f32 *)(obj + 0x7C);
    dx = *(f32 *)(obj + 0x74) - *(f32 *)(slot + 0x00);
    dz = *(f32 *)(obj + 0x7C) - *(f32 *)(slot + 0x08);
    if (dx == 0.0f && dz == 0.0f) {
        *(f32 *)(slot + 0x38) = 0.0f;
        *(f32 *)(slot + 0x50) = 0.0f;
    } else {
        *(f32 *)(slot + 0x50) = dolsqrtf2(dx * dx + dz * dz);
    }
    slot[0xBB] = 1;
    obj[0xBA] = 0xD;
    rep0B08SetCurState(idx, 0);
    *(s16 *)(obj + 0x94) = 1;
}

// .text:0x00071B80 size:0xEC mapped:0x806B0C14
void fn_2_71B80(u8 *obj) {
    u8 kind;
    u8 *e;
    s32 v0;
    s32 v2;
    s32 v4;
    fn_2_69E1C(*(s32 *)(obj + 0x80));
    kind = lbl_2_bss_1A8248[0x441C];
    e = lbl_2_data_2E80 + kind * 6;
    v0 = *(s16 *)(e + 0x0) << 1;
    v2 = *(s16 *)(e + 0x2) << 1;
    v4 = *(s16 *)(e + 0x4) << 1;
    if (*(s32 *)(obj + 0x80) == 0) {
        if (hugeAnimStruct + 0xC04) {
            s16 v = *(s16 *)(hugeAnimStruct + 0xC04 + 0x68);
            if (v == v0 - v4 || v == v0 - v2) {
                fn_80062890(kind == 5 ? 1 : 0);
            }
        }
    }
    if (*(f32 *)(obj + 0x50) > 0.0f) {
        obj[0xBA] = 4;
        obj[0xC4] = 1;
        *(s16 *)(obj + 0x94) = 2;
    }
}

// .text:0x00071A70 size:0x110 mapped:0x806B0B04
void fn_2_71A70(u8 *obj) {
    s32 idx = *(s32 *)(obj + 0x80);
    u8 kind;
    u8 *e;
    s32 v0;
    s32 v2;
    s32 v4;
    fn_2_69E1C(idx);
    kind = lbl_2_bss_1A8248[0x441C];
    e = lbl_2_data_2E80 + kind * 6;
    v0 = *(s16 *)(e + 0x0) << 1;
    v2 = *(s16 *)(e + 0x2) << 1;
    v4 = *(s16 *)(e + 0x4) << 1;
    if (*(s32 *)(obj + 0x80) == 0) {
        if (hugeAnimStruct + 0xC04) {
            s16 v = *(s16 *)(hugeAnimStruct + 0xC04 + 0x68);
            if (v == v0 - v4 || v == v0 - v2) {
                fn_80062890(kind == 5 ? 1 : 0);
            }
        }
    }
    if (*(f32 *)(obj + 0x38) > 0.0f) {
        u8 *slot = REP_SLOT(idx);
        *(f32 *)(obj + 0x34) = *(f32 *)(obj + 0x4C);
        slot[0xC3] = 3;
        *(s16 *)(slot + 0x94) = 0;
    }
}

// .text:0x00071A38 size:0x38 mapped:0x806B0ACC
void fn_2_71A38(u8 *obj) {
    lbl_2_data_2A1F4[*(s16 *)(obj + 0x94)](obj);
}

// .text:0x00071098 size:0x9A0 mapped:0x806B012C
void fn_2_71098(u8 *obj) {
    s32 idx = *(s32 *)(obj + 0x80);
    s32 i;
    BOOL flag = FALSE;
    f32 h1;
    f32 h2;
    Vec tmp;
    s8 cb;
    rep0B08EnableSlot(idx);
    memcpy(obj + 0x74, lbl_2_data_2EA4 + *(s16 *)(lbl_2_bss_1A8248 + 0x16C0) * 12, 12);
    rep0B08SetSlotTarget(idx, *(f32 *)(obj + 0x74), *(f32 *)(obj + 0x7C));
    obj[0xBA] = 0xC;
    for (i = 1; i < 7; i++) {
        if (rep0B08SlotsWithinRange(idx, i)) {
            (*(s8 *)(obj + 0xCB)) = i;
            break;
        }
        (*(s8 *)(obj + 0xCB)) = -1;
    }
    cb = (s8)(*(s8 *)(obj + 0xCB));
    if (cb >= 2 && cb <= 6) {
        {
            u8 *current = REP_SLOT(idx);
            u8 *neighbor = REP_SLOT(cb);
            atan2(-(*(f32 *)(neighbor + 0x00) - *(f32 *)(current + 0x00)),
                  -(*(f32 *)(neighbor + 0x08) - *(f32 *)(current + 0x08)));
            fn_2_4A18C(*(f32 *)(current + 0x4C));
        }
        {
            u8 *current = REP_SLOT(idx);
            u8 *neighbor = REP_SLOT((s8)obj[0xCB]);
            s16 pointIdx = *(s16 *)(lbl_2_bss_1A8248 + 0x16C0);
            h1 = atan2(-(*(f32 *)(neighbor + 0x00) - *(f32 *)(current + 0x00)),
                       -(*(f32 *)(neighbor + 0x08) - *(f32 *)(current + 0x08)));
            memcpy(&tmp, lbl_2_data_2EA4 + pointIdx * 12, sizeof(Vec));
            h2 = atan2(-(tmp.x - *(f32 *)(current + 0x00)), -(tmp.z - *(f32 *)(current + 0x08)));
            h1 -= h2;
            if (h1 < 1.2217305f && h1 > -1.2217305f) {
                flag = (u8)TRUE;
            } else {
                flag = (u8)FALSE;
            }
        }
    }
    if (flag == 0) {
        fn_2_69E1C(idx);
    } else {
        fn_2_699D4(idx);
    }
    rep0B08SetSlotState(idx, 0);
    for (i = 1; i < 7; i++) {
        s32 nearby = rep0B08SlotsWithinRange(idx, i);
        if (nearby && i == 1 && lbl_2_bss_1A8248[0x44F3] == 0) {
                obj[0xC4] = 2;
                (*(s8 *)(obj + 0xCB)) = (u8)i;
                rep0B08TransitionSlot(idx, 3);
                return;
            }
        if (nearby && i >= 2 && i <= 6) {
                obj[0xBA] = 4;
                obj[0xC4] = 1;
                *(s16 *)(obj + 0xB2) = rep0B08NearestSlotZeroPoint();
                rep0B08TransitionSlot(idx, 4);
                return;
            }
        (*(s8 *)(obj + 0xCB)) = -1;
        *(s16 *)(obj + 0x94) = 1;
    }
    if (obj[0xCD] == 1) {
        u8 *s1 = REP_SLOT(idx);
        u8 *s2 = REP_SLOT((s8)obj[0xCE]);
        f32 dx = *(f32 *)(s1 + 0x00) - *(f32 *)(s2 + 0x00);
        f32 dz = *(f32 *)(s1 + 0x08) - *(f32 *)(s2 + 0x08);
        f32 heading = atan2(-dx, -dz);
        f32 diff = fn_2_4A18C(*(f32 *)(s2 + 0x4C)) - heading;
        if (s2[0xC3] == 7 && (*(s16 *)(obj + 0x94) == 0 || *(s16 *)(obj + 0x94) == 1)) {
            if (fabs(diff) < 1.5707964f) {
                lbl_2_bss_1A824C[0x1978F1] = 0;
            } else {
                lbl_2_bss_1A824C[0x1978F1] = 2;
            }
        } else {
            lbl_2_bss_1A824C[0x1978F1] = 1;
        }
        obj[0xBA] = 4;
        obj[0xC4] = 1;
        *(s16 *)(obj + 0xB2) = rep0B08NearestSlotZeroPoint();
        rep0B08TransitionSlot(idx, 4);
    }
    if (!(*(f32 *)(obj + 0x50) <= 0.0f)) {
        return;
    }
    obj[0xBA] = 9;
    obj[0xC4] = 1;
    if (lbl_2_bss_1A824C[0x19783D] == 0) {
        u8 *base = lbl_2_bss_1A8248;
        *(s16 *)(base + 0x16C2) = *(s16 *)(base + 0x16C0);
    } else {
        u8 *base = lbl_2_bss_1A8248;
        *(s16 *)(base + 0x16C2) = *(s16 *)(base + 0x16BE);
    }
    rep0B08SetSlotState(idx, 1);
    obj[0xC4] = 1;
    *(s16 *)(obj + 0xB2) = rep0B08NearestSlotZeroPoint();
    rep0B08TransitionSlot(idx, 4);
}

// .text:0x000709A0 size:0x6F8 mapped:0x806AFA34
void fn_2_709A0(u8 *obj) {
    s32 idx = *(s32 *)(obj + 0x80);
    u8 *sIdx = REP_SLOT(idx);
    u8 kind;
    s32 i;
    s32 k;
    s32 flag = 0;
    s32 bestIdx;
    f32 limit;
    f32 dist;
    f32 best;
    f32 h1;
    f32 h2;
    Vec ref;
    Vec cand;
    Vec tmp;
    s8 cb;
    s16 *bp;
    for (i = 1; i < 7; i++) {
        u8 *sI = REP_SLOT(i);
        dist = PSVECDistance((Vec *)sIdx, (Vec *)sI);
        kind = lbl_2_bss_1A8248[0x441C];
        if (idx == 0) {
            limit = lbl_2_data_3F0C[i] + lbl_2_data_3EF4[kind];
        } else {
            limit = lbl_2_data_3F0C[idx] + lbl_2_data_3EF4[kind];
        }
        if (dist < limit && sIdx[0xC0] != 0 && sI[0xC0] != 0) {
            if (i == 1 && lbl_2_bss_1A8248[0x44F3] == 0) {
                obj[0xC4] = 2;
                obj[0xCB] = (u8)i;
                sIdx[0xC3] = 3;
                *(s16 *)(sIdx + 0x94) = 0;
                return;
            }
            if (i >= 2 && i <= 6) {
                obj[0xBA] = 4;
                obj[0xC4] = 1;
                memcpy(&ref, REP_SLOT(0), 12);
                best = 10000.0f;
                bestIdx = 0;
                for (k = 0; k < 0x33; k++) {
                    memcpy(&cand, lbl_2_data_2EA4 + k * 12, 12);
                    dist = PSVECDistance(&ref, &cand);
                    if (dist < best) {
                        best = dist;
                        bestIdx = k;
                    }
                }
                *(s16 *)(obj + 0xB2) = (s16)bestIdx;
                sIdx[0xC3] = 4;
                *(s16 *)(sIdx + 0x94) = 0;
                return;
            }
        }
        obj[0xCB] = -1;
    }
    cb = (s8)obj[0xCB];
    if (cb >= 2 && cb <= 6) {
        u8 *sCb = REP_SLOT(cb);
        h1 = atan2(-(*(f32 *)(sCb + 0x00) - *(f32 *)(sIdx + 0x00)), -(*(f32 *)(sCb + 0x08) - *(f32 *)(sIdx + 0x08)));
        fn_2_4A18C(*(f32 *)(sIdx + 0x4C));
        memcpy(&tmp, lbl_2_data_2EA4 + *(s16 *)(lbl_2_bss_1A8248 + 0x16C0) * 12, 12);
        h2 = atan2(-(tmp.x - *(f32 *)(sIdx + 0x00)), -(tmp.z - *(f32 *)(sIdx + 0x08)));
        best = h1 - h2;
        flag = (best < 1.2217305f && best > -1.2217305f) ? 1 : 0;
    }
    for (i = 1; i < 7; i++) {
        u8 *sI = REP_SLOT(i);
        dist = PSVECDistance((Vec *)sIdx, (Vec *)sI);
        kind = lbl_2_bss_1A8248[0x441C];
        if (idx == 0) {
            limit = lbl_2_data_3F0C[i] + lbl_2_data_3EF4[kind];
        } else {
            limit = lbl_2_data_3F0C[idx] + lbl_2_data_3EF4[kind];
        }
        if (dist < limit && sIdx[0xC0] != 0 && sI[0xC0] != 0) {
            if (i == 1 && lbl_2_bss_1A8248[0x44F3] == 0) {
                obj[0xC4] = 2;
                obj[0xCB] = (u8)i;
                sIdx[0xC3] = 3;
                *(s16 *)(sIdx + 0x94) = 0;
                return;
            }
            if (i >= 2 && i <= 6) {
                obj[0xBA] = 4;
                obj[0xC4] = 1;
                memcpy(&ref, REP_SLOT(0), 12);
                best = 10000.0f;
                bestIdx = 0;
                for (k = 0; k < 0x33; k++) {
                    memcpy(&cand, lbl_2_data_2EA4 + k * 12, 12);
                    dist = PSVECDistance(&ref, &cand);
                    if (dist < best) {
                        best = dist;
                        bestIdx = k;
                    }
                }
                *(s16 *)(obj + 0xB2) = (s16)bestIdx;
                sIdx[0xC3] = 4;
                *(s16 *)(sIdx + 0x94) = 0;
                return;
            }
        }
        obj[0xCB] = -1;
    }
    if (flag != 0) {
        fn_2_69E1C(idx);
    } else {
        fn_2_699D4(idx);
    }
    kind = lbl_2_bss_1A8248[0x441C];
    if (idx == 0) {
        s16 *ent = (s16 *)(lbl_2_data_2E80 + kind * 6);
        s32 a = ent[0] * 2 - ent[2] * 2;
        s32 b = ent[0] * 2 - ent[1] * 2;
        {
            u8 *hp = hugeAnimStruct + 0xC04;
            if (hp != NULL && (*(s16 *)(hp + 0x68) == a || *(s16 *)(hp + 0x68) == b)) {
                fn_80062890(kind == 5 ? 1 : 0);
            }
        }
    }
    if (*(f32 *)(obj + 0x50) <= 0.0f) {
        obj[0xBA] = 4;
        obj[0xC4] = 1;
        bp = (s16 *)(lbl_2_bss_1A8248 + 0x16C2);
        if (lbl_2_bss_1A8248[0x783D] != 0) {
            *bp = *(s16 *)(lbl_2_bss_1A8248 + 0x16C0);
        } else {
            *bp = *(s16 *)(lbl_2_bss_1A8248 + 0x16BE);
        }
        *(s16 *)(obj + 0x94) = 2;
        return;
    }
    if (obj[0xCD] == 1) {
        u8 *s1 = REP_SLOT(idx);
        u8 *s2 = REP_SLOT((s8)obj[0xCE]);
        f32 dx = *(f32 *)(s1 + 0x00) - *(f32 *)(s2 + 0x00);
        f32 dz = *(f32 *)(s1 + 0x08) - *(f32 *)(s2 + 0x08);
        f32 heading = atan2(-dx, -dz);
        f32 diff = fn_2_4A18C(*(f32 *)(s2 + 0x4C)) - heading;
        if (s2[0xC3] == 7 && (*(s16 *)(obj + 0x94) == 0 || *(s16 *)(obj + 0x94) == 1)) {
            if (fabs(diff) < 1.5707964f) {
                lbl_2_bss_1A824C[0x1978F1] = 0;
            } else {
                lbl_2_bss_1A824C[0x1978F1] = 2;
            }
        } else {
            lbl_2_bss_1A824C[0x1978F1] = 1;
        }
        obj[0xBA] = 4;
        obj[0xC4] = 1;
        memcpy(&ref, REP_SLOT(0), 12);
        best = 10000.0f;
        bestIdx = 0;
        for (k = 0; k < 0x33; k++) {
            memcpy(&cand, lbl_2_data_2EA4 + k * 12, 12);
            dist = PSVECDistance(&ref, &cand);
            if (dist < best) {
                best = dist;
                bestIdx = k;
            }
        }
        *(s16 *)(obj + 0xB2) = (s16)bestIdx;
        sIdx[0xC3] = 4;
        *(s16 *)(sIdx + 0x94) = 0;
    }
}

// .text:0x000705C0 size:0x3E0 mapped:0x806AF654
void fn_2_705C0(u8 *obj) {
    s32 idx = *(s32 *)(obj + 0x80);
    u8 kind;
    s16 *ent;
    u8 *slot;
    s32 i;
    f32 limit;
    f32 dist;
    fn_2_69E1C(idx);
    kind = lbl_2_bss_1A8248[0x441C];
    ent = (s16 *)(lbl_2_data_2E80 + kind * 6);
    if (idx == 0) {
        s32 a = ent[0] * 2 - ent[2] * 2;
        s32 b = ent[0] * 2 - ent[1] * 2;
        u8 *hp = hugeAnimStruct + 0xC04;
        if (hp != NULL && (*(s16 *)(hp + 0x68) == a || *(s16 *)(hp + 0x68) == b)) {
            fn_80062890(kind == 5 ? 1 : 0);
        }
    }
    if (*(f32 *)(obj + 0x38) <= 0.0f) {
        *(f32 *)(obj + 0x34) = *(f32 *)(obj + 0x4C);
        slot = REP_SLOT(idx);
        slot[0xC3] = 4;
        *(s16 *)(slot + 0x94) = 0;
    }
    for (i = 1; i < 7; i++) {
        u8 *sIdx = REP_SLOT(idx);
        u8 *sI = REP_SLOT(i);
        dist = PSVECDistance((Vec *)sIdx, (Vec *)sI);
        if (idx == 0) {
            limit = lbl_2_data_3F0C[i] + lbl_2_data_3EF4[kind];
        } else {
            limit = lbl_2_data_3F0C[idx] + lbl_2_data_3EF4[kind];
        }
        if (dist < limit && sIdx[0xC0] != 0 && sI[0xC0] != 0) {
            if (i == 1 && lbl_2_bss_1A8248[0x44F3] == 0) {
                obj[0xC4] = 2;
                obj[0xCB] = (u8)i;
                sIdx[0xC3] = 3;
                *(s16 *)(sIdx + 0x94) = 0;
                return;
            }
        }
        obj[0xCB] = -1;
    }
    if (obj[0xCD] == 1) {
        u8 *s1 = REP_SLOT(idx);
        u8 *s2 = REP_SLOT((s8)obj[0xCE]);
        f32 dx = *(f32 *)(s1 + 0x00) - *(f32 *)(s2 + 0x00);
        f32 dz = *(f32 *)(s1 + 0x08) - *(f32 *)(s2 + 0x08);
        f32 heading = atan2(-dx, -dz);
        f32 diff = fn_2_4A18C(*(f32 *)(s2 + 0x4C)) - heading;
        Vec ref;
        Vec cand;
        f32 best = 10000.0f;
        s32 bestIdx = 0;
        if (s2[0xC3] == 7 && (*(s16 *)(obj + 0x94) == 0 || *(s16 *)(obj + 0x94) == 1)) {
            if (fabs(diff) < 1.5707964f) {
                lbl_2_bss_1A824C[0x1978F1] = 0;
            } else {
                lbl_2_bss_1A824C[0x1978F1] = 2;
            }
        } else {
            lbl_2_bss_1A824C[0x1978F1] = 1;
        }
        obj[0xBA] = 4;
        obj[0xC4] = 1;
        memcpy(&ref, REP_SLOT(0), 12);
        for (i = 0; i < 0x33; i++) {
            memcpy(&cand, lbl_2_data_2EA4 + i * 12, 12);
            dist = PSVECDistance(&ref, &cand);
            if (dist < best) {
                best = dist;
                bestIdx = i;
            }
        }
        *(s16 *)(obj + 0xB2) = (s16)bestIdx;
        slot = REP_SLOT(idx);
        slot[0xC3] = 4;
        *(s16 *)(slot + 0x94) = 0;
    }
}

// .text:0x00070588 size:0x38 mapped:0x806AF61C
void fn_2_70588(u8 *obj) {
    lbl_2_data_2A200[*(s16 *)(obj + 0x94)](obj);
}

// .text:0x000704AC size:0xDC mapped:0x806AF540
void fn_2_704AC(u8 *obj) {
    lbl_2_bss_1A8248[*(s32 *)(obj + 0x80) * 0xD8 + 0x16D0] = 1;
    rep0B08SetCurState(*(s32 *)(obj + 0x80), 1);
    *(s16 *)(obj + 0x94) = 1;
}

// .text:0x000704A0 size:0xC mapped:0x806AF534
void fn_2_704A0(u8 *obj) {
    *(s16 *)(obj + 0x94) = 2;
}

// .text:0x00070494 size:0xC mapped:0x806AF528
void fn_2_70494(u8 *obj) {
    *(s16 *)(obj + 0x94) = 2;
}

// .text:0x0007045C size:0x38 mapped:0x806AF4F0
void fn_2_7045C(u8 *obj) {
    lbl_2_data_2A208[*(s16 *)(obj + 0x94)](obj);
}

// .text:0x00070110 size:0x34C mapped:0x806AF1A4
void fn_2_70110(u8 *obj) {
    u8 *slot = REP_SLOT(*(s32 *)(obj + 0x80));
    slot[0xC0] = 1;
    rep0B08SetCurState(*(s32 *)(slot + 0x80), 1);
    {
        s32 idx;
        s32 i;
        u8 kind;
        if (obj[0xCD] == 1) {
            u8 *s1;
            u8 *s2;
            f32 dx;
            f32 dz;
            f32 heading;
            f32 diff;
            idx = *(s32 *)(obj + 0x80);
            s1 = REP_SLOT(idx);
            s2 = REP_SLOT((s8)obj[0xCE]);
            dx = *(f32 *)(s1 + 0x00) - *(f32 *)(s2 + 0x00);
            dz = *(f32 *)(s1 + 0x08) - *(f32 *)(s2 + 0x08);
            heading = atan2(-dx, -dz);
            diff = fn_2_4A18C(*(f32 *)(s2 + 0x4C)) - heading;
            if (s2[0xC3] == 7 && (*(s16 *)(obj + 0x94) == 0 || *(s16 *)(obj + 0x94) == 1)) {
                if (fabs(diff) < 1.5707964f) {
                    lbl_2_bss_1A824C[0x1978F1] = 0;
                } else {
                    lbl_2_bss_1A824C[0x1978F1] = 2;
                }
            } else {
                lbl_2_bss_1A824C[0x1978F1] = 1;
            }
        }
        idx = *(s32 *)(obj + 0x80);
        kind = lbl_2_bss_1A8248[0x441C];
        for (i = 1; i < 7; i++) {
            u8 *si = REP_SLOT(i);
            u8 *sidx = REP_SLOT(idx);
            f32 dist = PSVECDistance((Vec *)sidx, (Vec *)si);
            f32 limit;
            if (idx == 0) {
                limit = lbl_2_data_3F0C[i] + lbl_2_data_3EF4[kind];
            } else {
                limit = lbl_2_data_3F0C[idx] + lbl_2_data_3EF4[kind];
            }
            if (dist < limit && sidx[0xC0] != 0 && si[0xC0] != 0) {
                if (i == 1 && lbl_2_bss_1A8248[0x44F3] == 0) {
                    obj[0xC4] = 2;
                    obj[0xCB] = (u8)i;
                    sidx[0xC3] = 3;
                    *(s16 *)(sidx + 0x94) = 0;
                    return;
                }
                if (i >= 2 && i <= 6) {
                    obj[0xCB] = (u8)i;
                    sidx[0xC3] = 4;
                    *(s16 *)(sidx + 0x94) = 0;
                    return;
                }
            }
            obj[0xCB] = -1;
        }
    }
    *(s16 *)(obj + 0x94) = 1;
}

// .text:0x0006FE6C size:0x2A4 mapped:0x806AEF00
void fn_2_6FE6C(u8 *obj) {
    s32 idx;
    s32 i;
    u8 kind;
    if (obj[0xCD] == 1) {
        u8 *s1;
        u8 *s2;
        f32 dx;
        f32 dz;
        f32 heading;
        f32 diff;
        idx = *(s32 *)(obj + 0x80);
        s1 = REP_SLOT(idx);
        s2 = REP_SLOT((s8)obj[0xCE]);
        dx = *(f32 *)(s1 + 0x00) - *(f32 *)(s2 + 0x00);
        dz = *(f32 *)(s1 + 0x08) - *(f32 *)(s2 + 0x08);
        heading = atan2(-dx, -dz);
        diff = fn_2_4A18C(*(f32 *)(s2 + 0x4C)) - heading;
        if (s2[0xC3] == 7 && (*(s16 *)(obj + 0x94) == 0 || *(s16 *)(obj + 0x94) == 1)) {
            if (fabs(diff) < 1.5707964f) {
                lbl_2_bss_1A824C[0x1978F1] = 0;
            } else {
                lbl_2_bss_1A824C[0x1978F1] = 2;
            }
        } else {
            lbl_2_bss_1A824C[0x1978F1] = 1;
        }
    }
    idx = *(s32 *)(obj + 0x80);
    kind = lbl_2_bss_1A8248[0x441C];
    for (i = 1; i < 7; i++) {
        u8 *si = REP_SLOT(i);
        u8 *sidx = REP_SLOT(idx);
        f32 dist = PSVECDistance((Vec *)sidx, (Vec *)si);
        f32 limit;
        if (idx == 0) {
            limit = lbl_2_data_3F0C[i] + lbl_2_data_3EF4[kind];
        } else {
            limit = lbl_2_data_3F0C[idx] + lbl_2_data_3EF4[kind];
        }
        if (dist < limit && sidx[0xC0] != 0 && si[0xC0] != 0) {
            if (i == 1 && lbl_2_bss_1A8248[0x44F3] == 0) {
                obj[0xC4] = 2;
                obj[0xCB] = (u8)i;
                sidx[0xC3] = 3;
                *(s16 *)(sidx + 0x94) = 0;
                return;
            }
            if (i >= 2 && i <= 6) {
                obj[0xCB] = (u8)i;
                sidx[0xC3] = 4;
                *(s16 *)(sidx + 0x94) = 0;
                return;
            }
        }
        obj[0xCB] = -1;
    }
}

// .text:0x0006FE34 size:0x38 mapped:0x806AEEC8
void fn_2_6FE34(u8 *obj) {
    lbl_2_data_2A210[*(s16 *)(obj + 0x94)](obj);
}

// .text:0x0006FB0C size:0x328 mapped:0x806AEBA0
void fn_2_6FB0C(u8 *obj) {
    s32 idx = *(s32 *)(obj + 0x80);
    s32 other = *(s32 *)(lbl_2_bss_1A8248 + 0x1690);
    u8 *sIdx = REP_SLOT(idx);
    u8 *sOther;
    u8 kind;
    f32 limit;
    f32 dist;
    sIdx[0xC0] = 1;
    rep0B08SetCurState(*(s32 *)(sIdx + 0x80), 1);
    *(f32 *)(obj + 0x34) = *(f32 *)(obj + 0x4C);
    if (idx >= 2 && idx <= 6 && lbl_2_bss_1A8248[0x16DD] == 1 && (s8)lbl_2_bss_1A8248[0x16DC] == idx) {
        rep0B08SetCurState(*(s32 *)(REP_SLOT(idx) + 0x80), 1);
        obj[0xC4] = 2;
        obj[0xCB] = 0;
        *(s16 *)(obj + 0x94) = 2;
        return;
    }
    sOther = REP_SLOT(other);
    dist = PSVECDistance((Vec *)sIdx, (Vec *)sOther);
    kind = lbl_2_bss_1A8248[0x441C];
    if (idx == 0) {
        limit = lbl_2_data_3F0C[other] + lbl_2_data_3EF4[kind];
    } else {
        limit = lbl_2_data_3F0C[idx] + lbl_2_data_3EF4[kind];
    }
    if (dist < limit && sIdx[0xC0] != 0 && sOther[0xC0] != 0) {
        if (idx == 1) {
            rep0B08SetCurState(*(s32 *)(sIdx + 0x80), 1);
            obj[0xC4] = 2;
            obj[0xCB] = 0;
            *(s16 *)(obj + 0x94) = 2;
            return;
        }
        if (idx >= 2 && idx <= 6) {
            obj[0xCB] = 0;
        }
    } else {
        obj[0xCB] = -1;
    }
    *(s16 *)(obj + 0x94) = 1;
}

// .text:0x0006F88C size:0x280 mapped:0x806AE920
void fn_2_6F88C(u8 *obj) {
    s32 idx = *(s32 *)(obj + 0x80);
    s32 other = *(s32 *)(lbl_2_bss_1A8248 + 0x1690);
    u8 *slot;
    u8 *slot2;
    f32 dist;
    f32 limit;
    if (idx >= 2 && idx <= 6 && lbl_2_bss_1A8248[0x16DD] == 1 && (s8)lbl_2_bss_1A8248[0x16DC] == idx) {
        rep0B08SetCurState(idx, 1);
        obj[0xC4] = 2;
        obj[0xCB] = 0;
        *(s16 *)(obj + 0x94) = 2;
        return;
    }
    slot = REP_SLOT(idx);
    slot2 = REP_SLOT(other);
    dist = PSVECDistance((Vec *)slot, (Vec *)slot2);
    if (idx == 0) {
        limit = lbl_2_data_3EF4[lbl_2_bss_1A8248[0x441C]] + lbl_2_data_3F0C[other];
    } else {
        limit = lbl_2_data_3F0C[idx] + lbl_2_data_3EF4[lbl_2_bss_1A8248[0x441C]];
    }
    if (dist < limit && slot[0xC0] != 0 && slot2[0xC0] != 0) {
        if (idx == 1) {
            rep0B08SetCurState(idx, 1);
            obj[0xC4] = 2;
            obj[0xCB] = 0;
            *(s16 *)(obj + 0x94) = 2;
        } else if (idx >= 2 && idx <= 6) {
            obj[0xCB] = 0;
        }
    } else {
        obj[0xCB] = 0xFF;
    }
}

// .text:0x0006F78C size:0x100 mapped:0x806AE820
void fn_2_6F78C(u8 *obj) {
    u8 *b = REP_SLOT(0);
    f32 r;
    *(f32 *)(obj + 0x4C) = (f32)atan2(-(*(f32 *)(b + 0x00) - *(f32 *)(obj + 0x00)),
                                      -(*(f32 *)(b + 0x08) - *(f32 *)(obj + 0x08)));
    r = fn_2_4A18C(*(f32 *)(obj + 0x34) - *(f32 *)(obj + 0x4C));
    if (r >= 0.02 || r <= 0.0f) {
        if (r <= -0.02 || r >= 0.0f) {
            if (r >= 0.0f) {
                *(f32 *)(obj + 0x34) = *(f32 *)(obj + 0x34) - 0.05235987901687622f;
            } else {
                *(f32 *)(obj + 0x34) = *(f32 *)(obj + 0x34) + 0.05235987901687622f;
            }
        } else {
            *(s16 *)(obj + 0x94) = 3;
        }
    } else {
        *(s16 *)(obj + 0x94) = 3;
    }
    *(f32 *)(obj + 0x4C) = *(f32 *)(obj + 0x34);
}

// .text:0x0006F72C size:0x60 mapped:0x806AE7C0
void fn_2_6F72C(u8 *obj) {
    f32 dist = (f32)fabs(PSVECDistance((Vec *)REP_SLOT(0), (Vec *)obj));
    if (dist > 1.6f) {
        *(s16 *)(obj + 0x94) = 1;
    }
}

// .text:0x0006F6F4 size:0x38 mapped:0x806AE788
void fn_2_6F6F4(u8 *obj) {
    lbl_2_data_2A220[*(s16 *)(obj + 0x94)](obj);
}

// .text:0x0006F104 size:0x5F0 mapped:0x806AE198
void fn_2_6F104(u8 *obj) {
    s32 idx = *(s32 *)(obj + 0x80);
    s32 other = *(s32 *)(lbl_2_bss_1A8248 + 0x1690);
    u8 *slot = REP_SLOT(idx);
    s16 cand[4];
    s16 *row;
    s32 count = 0;
    s32 j;
    s16 c;
    u8 *rec;
    u8 *sIdx;
    u8 *sOther;
    u8 kind;
    f32 dx;
    f32 dz;
    f32 limit;
    f32 dist;
    slot[0xC0] = 1;
    row = (s16 *)(lbl_2_data_3D30 + *(s16 *)(slot + 0xB2) * 8);
    for (j = 0; j < 4; j++) {
        c = row[j];
        if (c != -1) {
            rec = lbl_2_bss_1A8248 + c * 10;
            if (rec[0x40F4] == 0 && rec[0x40F2] != 7 && rec[0x40F2] != 8) {
                cand[count] = c;
                count++;
            }
        }
    }
    *(s16 *)(slot + 0xB0) = cand[rand() % count];
    memcpy(obj + 0x74, lbl_2_data_2EA4 + *(s16 *)(slot + 0xB0) * 12, 12);
    *(f32 *)(slot + 0x0C) = *(f32 *)(obj + 0x74);
    *(f32 *)(slot + 0x14) = *(f32 *)(obj + 0x7C);
    dx = *(f32 *)(obj + 0x74) - *(f32 *)(slot + 0x00);
    dz = *(f32 *)(obj + 0x7C) - *(f32 *)(slot + 0x08);
    if (dx == 0.0f && dz == 0.0f) {
        *(f32 *)(slot + 0x38) = 0.0f;
        *(f32 *)(slot + 0x50) = 0.0f;
    } else {
        *(f32 *)(slot + 0x50) = dolsqrtf2(dx * dx + dz * dz);
    }
    slot[0xBB] = 1;
    obj[0xBA] = 0xD;
    fn_2_69E1C(idx);
    rep0B08SetCurState(*(s32 *)(slot + 0x80), 0);
    if (idx >= 2 && idx <= 6 && lbl_2_bss_1A8248[0x16DD] == 1 && (s8)lbl_2_bss_1A8248[0x16DC] == idx) {
        rep0B08SetCurState(*(s32 *)(REP_SLOT(idx) + 0x80), 1);
        obj[0xC4] = 2;
        obj[0xCB] = 0;
        *(s16 *)(obj + 0x94) = 3;
        return;
    }
    sIdx = REP_SLOT(idx);
    sOther = REP_SLOT(other);
    dist = PSVECDistance((Vec *)sIdx, (Vec *)sOther);
    kind = lbl_2_bss_1A8248[0x441C];
    if (idx == 0) {
        limit = lbl_2_data_3F0C[other] + lbl_2_data_3EF4[kind];
    } else {
        limit = lbl_2_data_3F0C[idx] + lbl_2_data_3EF4[kind];
    }
    if (dist < limit && sIdx[0xC0] != 0 && sOther[0xC0] != 0) {
        if (idx == 1 && lbl_2_bss_1A8248[0x44F3] == 0) {
            rep0B08SetCurState(*(s32 *)(sIdx + 0x80), 1);
            obj[0xC4] = 2;
            obj[0xCB] = 0;
            *(s16 *)(obj + 0x94) = 3;
            return;
        }
        if (idx >= 2 && idx <= 6) {
            obj[0xCB] = 0;
            return;
        }
    }
    obj[0xCB] = -1;
    *(s16 *)(obj + 0x94) = 1;
}

// .text:0x0006ED30 size:0x3D4 mapped:0x806ADDC4
void fn_2_6ED30(u8 *obj) {
    s32 idx = *(s32 *)(obj + 0x80);
    s32 other = *(s32 *)(lbl_2_bss_1A8248 + 0x1690);
    u8 *sIdx;
    u8 *sOther;
    u8 kind;
    f32 limit;
    f32 dist;
    fn_2_69E1C(idx);
    if (idx >= 2 && idx <= 6 && lbl_2_bss_1A8248[0x16DD] == 1 && (s8)lbl_2_bss_1A8248[0x16DC] == idx) {
        rep0B08SetCurState(*(s32 *)(REP_SLOT(idx) + 0x80), 1);
        obj[0xC4] = 2;
        obj[0xCB] = 0;
        *(s16 *)(obj + 0x94) = 3;
        return;
    }
    sIdx = REP_SLOT(idx);
    sOther = REP_SLOT(other);
    dist = PSVECDistance((Vec *)sIdx, (Vec *)sOther);
    kind = lbl_2_bss_1A8248[0x441C];
    if (idx == 0) {
        limit = lbl_2_data_3F0C[other] + lbl_2_data_3EF4[kind];
    } else {
        limit = lbl_2_data_3F0C[idx] + lbl_2_data_3EF4[kind];
    }
    if (dist < limit && sIdx[0xC0] != 0 && sOther[0xC0] != 0) {
        if (idx == 1 && lbl_2_bss_1A8248[0x44F3] == 0) {
            rep0B08SetCurState(*(s32 *)(sIdx + 0x80), 1);
            obj[0xC4] = 2;
            obj[0xCB] = 0;
            *(s16 *)(obj + 0x94) = 3;
            return;
        }
        if (idx >= 2 && idx <= 6) {
            obj[0xCB] = 0;
        } else {
            obj[0xCB] = -1;
        }
    } else {
        obj[0xCB] = -1;
    }
    if (*(f32 *)(obj + 0x50) <= 0.0f) {
        *(s16 *)(obj + 0xAE) = *(s16 *)(obj + 0xB2);
        *(s16 *)(obj + 0xB2) = *(s16 *)(obj + 0xB0);
        if (rand() % 100 < 10) {
            rep0B08SetCurState(*(s32 *)(sIdx + 0x80), 1);
            *(s16 *)(obj + 0xA2) = rand() % 180 + 60;
            *(s16 *)(obj + 0x94) = 2;
        } else {
            *(s16 *)(obj + 0x94) = 0;
        }
    }
}

// .text:0x0006EA74 size:0x2BC mapped:0x806ADB08
void fn_2_6EA74(u8 *obj) {
    s32 idx = *(s32 *)(obj + 0x80);
    s32 other = *(s32 *)(lbl_2_bss_1A8248 + 0x1690);
    u8 *sIdx;
    u8 *sOther;
    u8 kind;
    f32 limit;
    f32 dist;
    s16 cd;
    if (idx >= 2 && idx <= 6 && lbl_2_bss_1A8248[0x16DD] == 1 && (s8)lbl_2_bss_1A8248[0x16DC] == idx) {
        rep0B08SetCurState(*(s32 *)(REP_SLOT(idx) + 0x80), 1);
        obj[0xC4] = 2;
        obj[0xCB] = 0;
        *(s16 *)(obj + 0x94) = 3;
        return;
    }
    sIdx = REP_SLOT(idx);
    sOther = REP_SLOT(other);
    dist = PSVECDistance((Vec *)sIdx, (Vec *)sOther);
    kind = lbl_2_bss_1A8248[0x441C];
    if (idx == 0) {
        limit = lbl_2_data_3F0C[other] + lbl_2_data_3EF4[kind];
    } else {
        limit = lbl_2_data_3F0C[idx] + lbl_2_data_3EF4[kind];
    }
    if (dist < limit && sIdx[0xC0] != 0 && sOther[0xC0] != 0) {
        if (idx == 1 && lbl_2_bss_1A8248[0x44F3] == 0) {
            rep0B08SetCurState(*(s32 *)(sIdx + 0x80), 1);
            obj[0xC4] = 2;
            obj[0xCB] = 0;
            *(s16 *)(obj + 0x94) = 3;
            return;
        }
        if (idx >= 2 && idx <= 6) {
            obj[0xCB] = 0;
        } else {
            obj[0xCB] = -1;
        }
    } else {
        obj[0xCB] = -1;
    }
    cd = *(s16 *)(obj + 0xA2);
    *(s16 *)(obj + 0xA2) = cd - 1;
    if (cd == 0) {
        *(s16 *)(obj + 0x94) = 0;
    }
}

// .text:0x0006E88C size:0x1E8 mapped:0x806AD920
void fn_2_6E88C(u8 *obj) {
    u8 *b = REP_SLOT(0);
    f32 r;
    f32 t;
    f32 f31;
    *(f32 *)(obj + 0x4C) = (f32)atan2(-(*(f32 *)(b + 0x00) - *(f32 *)(obj + 0x00)),
                                      -(*(f32 *)(b + 0x08) - *(f32 *)(obj + 0x08)));
    r = fn_2_4A18C(*(f32 *)(obj + 0x34) - *(f32 *)(obj + 0x4C));
    t = (f32)fabs(r);
    if (t > 2.268928050994873f) {
        f31 = 1.5707963705062866f;
    } else if (t > 1.5707963705062866f) {
        f31 = 0.6981317400932312f;
    } else if (t > 0.6981317400932312f) {
        f31 = 0.3490658700466156f;
    } else if (t > 0.3490658700466156f) {
        f31 = 0.1745329350233078f;
    } else if (t > 0.1745329350233078f) {
        f31 = 0.0872664675116539f;
    } else if (t > 0.0872664675116539f) {
        f31 = 0.03490658476948738f;
    } else if (t > 0.03490658476948738f) {
        f31 = 0.01745329238474369f;
    } else if (t > 0.01745329238474369f) {
        f31 = 0.008726646192371845f;
    } else {
        f31 = 0.0034906587097793818f;
    }
    if (r >= 0.02 || r == 0.0f) {
        *(f32 *)(obj + 0x34) = *(f32 *)(obj + 0x34) - f31;
    } else if (r <= -0.02) {
        *(f32 *)(obj + 0x34) = *(f32 *)(obj + 0x34) + f31;
    }
    *(f32 *)(obj + 0x4C) = *(f32 *)(obj + 0x34);
}

// .text:0x0006E880 size:0xC mapped:0x806AD914
void fn_2_6E880(u8 *obj) {
    *(s16 *)(obj + 0x94) = 4;
}

// .text:0x0006E848 size:0x38 mapped:0x806AD8DC
void fn_2_6E848(u8 *obj) {
    lbl_2_data_2A234[*(s16 *)(obj + 0x94)](obj);
}

// .text:0x0006E1D0 size:0x678 mapped:0x806AD264
void fn_2_6E1D0(u8 *obj) {
    s32 idx = *(s32 *)(obj + 0x80);
    s32 other = *(s32 *)(lbl_2_bss_1A8248 + 0x1690);
    u8 *slot = REP_SLOT(idx);
    s16 *row = lbl_2_data_3C2C[idx - 2];
    s16 n = *(s16 *)(lbl_2_data_3C20 + idx * 2 - 4);
    s32 pick;
    s16 chosen;
    u8 *sIdx;
    u8 *sOther;
    u8 kind;
    f32 limit;
    f32 dist;
    slot[0xC0] = 1;
    pick = rand() % n;
    if ((s8)obj[0xCF] == -1) {
        pick = 0;
        obj[0xCF] = 0;
    } else if (row[pick] == *(s16 *)(obj + 0xB2)) {
        pick = pick ^ 1;
    }
    chosen = row[pick];
    *(s16 *)(slot + 0xB0) = chosen;
    memcpy(obj + 0x74, lbl_2_data_2EA4 + *(s16 *)(slot + 0xB0) * 12, 12);
    *(f32 *)(slot + 0x0C) = *(f32 *)(obj + 0x74);
    *(f32 *)(slot + 0x14) = *(f32 *)(obj + 0x7C);
    {
        f32 dx = *(f32 *)(obj + 0x74) - *(f32 *)(slot + 0x00);
        f32 dz = *(f32 *)(obj + 0x7C) - *(f32 *)(slot + 0x08);
        if (dx == 0.0f && dz == 0.0f) {
            *(f32 *)(slot + 0x38) = 0.0f;
            *(f32 *)(slot + 0x50) = 0.0f;
        } else {
            *(f32 *)(slot + 0x50) = dolsqrtf2(dx * dx + dz * dz);
        }
    }
    slot[0xBB] = 1;
    obj[0xBA] = 0xD;
    fn_2_69E1C(idx);
    rep0B08SetCurState(*(s32 *)(slot + 0x80), 0);
    if (idx >= 2 && idx <= 6 && lbl_2_bss_1A8248[0x16DD] == 1 && (s8)lbl_2_bss_1A8248[0x16DC] == idx) {
        rep0B08SetCurState(*(s32 *)(REP_SLOT(idx) + 0x80), 1);
        obj[0xC4] = 2;
        obj[0xCB] = 0;
        *(s16 *)(obj + 0x94) = 4;
        return;
    }
    sIdx = REP_SLOT(idx);
    sOther = REP_SLOT(other);
    dist = PSVECDistance((Vec *)sIdx, (Vec *)sOther);
    kind = lbl_2_bss_1A8248[0x441C];
    if (idx == 0) {
        limit = lbl_2_data_3F0C[other] + lbl_2_data_3EF4[kind];
    } else {
        limit = lbl_2_data_3F0C[idx] + lbl_2_data_3EF4[kind];
    }
    if (dist < limit && sIdx[0xC0] != 0 && sOther[0xC0] != 0) {
        if (idx == 1) {
            rep0B08SetCurState(*(s32 *)(sIdx + 0x80), 1);
            obj[0xC4] = 2;
            obj[0xCB] = 0;
            *(s16 *)(obj + 0x94) = 3;
            return;
        }
        if (idx >= 2 && idx <= 6) {
            s16 b2 = *(s16 *)(sIdx + 0xB2);
            s16 b0 = *(s16 *)(sIdx + 0xB0);
            s16 tb = *(s16 *)(lbl_2_data_3ED4 + idx * 2 - 4);
            if ((b2 == chosen && b0 == chosen) || (b2 == tb && b0 == tb)) {
                if (*(f32 *)(obj + 0x50) <= 0.01f) {
                    *(s16 *)(obj + 0xA2) = 0x78;
                    rep0B08SetCurState(*(s32 *)(sIdx + 0x80), 1);
                    obj[0xBA] = 9;
                    obj[0xCF] = 0;
                    *(s16 *)(obj + 0x94) = 2;
                    return;
                }
            }
            obj[0xCB] = 0;
            obj[0xCF] = -1;
            *(s16 *)(obj + 0x94) = 0;
            return;
        }
        return;
    }
    obj[0xCB] = -1;
    *(s16 *)(obj + 0x94) = 1;
}

// .text:0x0006DE54 size:0x37C mapped:0x806ACEE8
void fn_2_6DE54(u8 *obj) {
    s32 idx = *(s32 *)(obj + 0x80);
    s32 other = *(s32 *)(lbl_2_bss_1A8248 + 0x1690);
    u8 *sIdx;
    u8 *sOther;
    u8 kind;
    f32 limit;
    f32 dist;
    fn_2_69E1C(idx);
    if (idx >= 2 && idx <= 6 && lbl_2_bss_1A8248[0x16DD] == 1 && (s8)lbl_2_bss_1A8248[0x16DC] == idx) {
        rep0B08SetCurState(*(s32 *)(REP_SLOT(idx) + 0x80), 1);
        obj[0xC4] = 2;
        obj[0xCB] = 0;
        *(s16 *)(obj + 0x94) = 4;
        return;
    }
    sIdx = REP_SLOT(idx);
    sOther = REP_SLOT(other);
    dist = PSVECDistance((Vec *)sIdx, (Vec *)sOther);
    kind = lbl_2_bss_1A8248[0x441C];
    if (idx == 0) {
        limit = lbl_2_data_3F0C[other] + lbl_2_data_3EF4[kind];
    } else {
        limit = lbl_2_data_3F0C[idx] + lbl_2_data_3EF4[kind];
    }
    if (dist < limit && sIdx[0xC0] != 0 && sOther[0xC0] != 0) {
        if (idx == 1) {
            rep0B08SetCurState(*(s32 *)(sIdx + 0x80), 1);
            obj[0xC4] = 2;
            obj[0xCB] = 0;
            *(s16 *)(obj + 0x94) = 3;
            return;
        }
        if (idx >= 2 && idx <= 6) {
            obj[0xCB] = 0;
            obj[0xCF] = -1;
            *(s16 *)(obj + 0x94) = 0;
        }
    } else {
        obj[0xCB] = -1;
    }
    if (*(f32 *)(obj + 0x50) <= 0.0f) {
        *(s16 *)(obj + 0xAE) = *(s16 *)(obj + 0xB2);
        *(s16 *)(obj + 0xB2) = *(s16 *)(obj + 0xB0);
        *(s16 *)(obj + 0xA2) = 0x78;
        rep0B08SetCurState(*(s32 *)(sIdx + 0x80), 1);
        obj[0xBA] = 9;
        *(f32 *)(obj + 0x50) = 0.0f;
        *(f32 *)(obj + 0x38) = 0.0f;
        *(s16 *)(obj + 0x94) = 2;
    }
}

// .text:0x0006DB30 size:0x324 mapped:0x806ACBC4
void fn_2_6DB30(u8 *obj) {
    s32 idx = *(s32 *)(obj + 0x80);
    s32 other = *(s32 *)(lbl_2_bss_1A8248 + 0x1690);
    u8 *sIdx;
    u8 *sOther;
    u8 kind;
    f32 limit;
    f32 dist;
    s16 cd;
    fn_2_69E1C(idx);
    if (idx >= 2 && idx <= 6 && lbl_2_bss_1A8248[0x16DD] == 1 && (s8)lbl_2_bss_1A8248[0x16DC] == idx) {
        rep0B08SetCurState(*(s32 *)(REP_SLOT(idx) + 0x80), 1);
        obj[0xC4] = 2;
        obj[0xCB] = 0;
        *(s16 *)(obj + 0x94) = 4;
        return;
    }
    sIdx = REP_SLOT(idx);
    sOther = REP_SLOT(other);
    dist = PSVECDistance((Vec *)sIdx, (Vec *)sOther);
    kind = lbl_2_bss_1A8248[0x441C];
    if (idx == 0) {
        limit = lbl_2_data_3F0C[other] + lbl_2_data_3EF4[kind];
    } else {
        limit = lbl_2_data_3F0C[idx] + lbl_2_data_3EF4[kind];
    }
    if (dist < limit && sIdx[0xC0] != 0 && sOther[0xC0] != 0) {
        if (idx == 1) {
            rep0B08SetCurState(*(s32 *)(sIdx + 0x80), 1);
            obj[0xC4] = 2;
            obj[0xCB] = 0;
            *(s16 *)(obj + 0x94) = 4;
            return;
        }
        if (idx >= 2 && idx <= 6) {
            if (*(s16 *)(sIdx + 0xB2) == *lbl_2_data_3C2C[idx - 2]) {
                obj[0xCB] = 0;
                *(s16 *)(obj + 0xA2) = 0x78;
                obj[0xCF] = 0;
            } else {
                obj[0xCB] = 0;
                obj[0xCF] = -1;
                *(s16 *)(obj + 0x94) = 0;
            }
        }
    } else {
        obj[0xCB] = -1;
    }
    cd = *(s16 *)(obj + 0xA2);
    *(s16 *)(obj + 0xA2) = cd - 1;
    if (cd == 0) {
        *(s16 *)(obj + 0x94) = 0;
    }
}

// .text:0x0006D968 size:0x1C8 mapped:0x806AC9FC
void fn_2_6D968(u8 *obj) {
    u8 *b = REP_SLOT(0);
    f32 r;
    *(f32 *)(obj + 0x4C) = (f32)atan2(-(*(f32 *)(b + 0x00) - *(f32 *)(obj + 0x00)),
                                      -(*(f32 *)(b + 0x08) - *(f32 *)(obj + 0x08)));
    r = fn_2_4A18C(*(f32 *)(obj + 0x34) - *(f32 *)(obj + 0x4C));
    if (r >= 0.02 || r <= 0.0f) {
        if (r <= -0.02 || r >= 0.0f) {
            if (r >= 0.0f) {
                *(f32 *)(obj + 0x34) = *(f32 *)(obj + 0x34) - 0.05235987901687622f;
            } else {
                *(f32 *)(obj + 0x34) = *(f32 *)(obj + 0x34) + 0.05235987901687622f;
            }
        } else {
            *(s16 *)(obj + 0x94) = 4;
        }
    } else {
        *(s16 *)(obj + 0x94) = 4;
    }
    *(f32 *)(obj + 0x4C) = *(f32 *)(obj + 0x34);
    if ((s8)lbl_2_bss_1A8248[0x16DD] == 0) {
        *(s16 *)(obj + 0xA2) = 0x78;
        rep0B08SetCurState(*(s32 *)(obj + 0x80), 1);
        obj[0xBA] = 9;
        *(f32 *)(obj + 0x50) = 0.0f;
        *(f32 *)(obj + 0x38) = 0.0f;
        *(s16 *)(obj + 0x94) = 2;
    }
}

// .text:0x0006D878 size:0xF0 mapped:0x806AC90C
void fn_2_6D878(u8 *obj) {
    if ((s8)lbl_2_bss_1A8248[0x16DD] == 0) {
        *(s16 *)(obj + 0xA2) = 0x78;
        rep0B08SetCurState(*(s32 *)(obj + 0x80), 1);
        obj[0xBA] = 9;
        *(f32 *)(obj + 0x50) = 0.0f;
        *(f32 *)(obj + 0x38) = 0.0f;
        *(s16 *)(obj + 0x94) = 2;
    }
}

// .text:0x0006D840 size:0x38 mapped:0x806AC8D4
void fn_2_6D840(u8 *obj) {
    lbl_2_data_2A248[*(s16 *)(obj + 0x94)](obj);
}

// .text:0x0006D754 size:0xEC mapped:0x806AC7E8
void fn_2_6D754(u8 *obj) {
    lbl_2_bss_1A8248[*(s32 *)(obj + 0x80) * 0xD8 + 0x16D0] = 1;
    rep0B08SetCurState(*(s32 *)(obj + 0x80), 1);
    *(f32 *)(obj + 0x4C) = 0.0f;
    *(f32 *)(obj + 0x34) = 0.0f;
    *(s16 *)(obj + 0x94) = 1;
}

// .text:0x0006D748 size:0xC mapped:0x806AC7DC
void fn_2_6D748(u8 *obj) {
    *(s16 *)(obj + 0x94) = 1;
}

// .text:0x0006D710 size:0x38 mapped:0x806AC7A4
void fn_2_6D710(u8 *obj) {
    lbl_2_data_2A250[*(s16 *)(obj + 0x94)](obj);
}

// .text:0x0006D5D4 size:0x13C mapped:0x806AC668
void fn_2_6D5D4(u8 *obj) {
    s32 n = *(s32 *)(obj + 0x80);
    lbl_2_bss_1A8248[n * 0xD8 + 0x16D0] = 1;
    if (*(s32 *)(obj + 0x84) == 0) {
        fn_80062890(lbl_2_data_3C40[lbl_2_bss_1A8248[0x441C]]);
    } else if (*(s32 *)(obj + 0x84) == 1) {
        fn_80062890(lbl_2_data_3C40[6]);
    }
    *(f32 *)(obj + 0x34) = 0.0f;
    *(f32 *)(obj + 0x4C) = 0.0f;
    rep0B08SetCurState(*(s32 *)(obj + 0x80), 2);
    *(s16 *)(obj + 0x94) = 1;
}

// .text:0x0006D4F8 size:0xDC mapped:0x806AC58C
void fn_2_6D4F8(u8 *obj) {
    if (fn_2_8CC88(*(s32 *)(obj + 0x84))) {
        rep0B08SetCurState(*(s32 *)(obj + 0x80), 5);
        *(s16 *)(obj + 0xA2) = 0x1E;
        *(s16 *)(obj + 0x94) = 2;
    }
}

// .text:0x0006D4E8 size:0x10 mapped:0x806AC57C
void fn_2_6D4E8(u8 *obj) {
    *(s16 *)(obj + 0xA2) -= 1;
}

// .text:0x0006D4B0 size:0x38 mapped:0x806AC544
void fn_2_6D4B0(u8 *obj) {
    lbl_2_data_2A25C[*(s16 *)(obj + 0x94)](obj);
}

// .text:0x0006D374 size:0x13C mapped:0x806AC408
void fn_2_6D374(u8 *obj) {
    s32 n = *(s32 *)(obj + 0x80);
    lbl_2_bss_1A8248[n * 0xD8 + 0x16D0] = 1;
    if (*(s32 *)(obj + 0x84) == 0) {
        fn_80062890(lbl_2_data_3C5C[lbl_2_bss_1A8248[0x441C]]);
    } else if (*(s32 *)(obj + 0x84) == 1) {
        fn_80062890(lbl_2_data_3C5C[6]);
    }
    *(f32 *)(obj + 0x34) = 0.0f;
    *(f32 *)(obj + 0x4C) = 0.0f;
    rep0B08SetCurState(*(s32 *)(obj + 0x80), 3);
    *(s16 *)(obj + 0x94) = 1;
}

// .text:0x0006D298 size:0xDC mapped:0x806AC32C
void fn_2_6D298(u8 *obj) {
    if (fn_2_8CC88(*(s32 *)(obj + 0x84))) {
        rep0B08SetCurState(*(s32 *)(obj + 0x80), 6);
        *(s16 *)(obj + 0xA2) = 0x1E;
        *(s16 *)(obj + 0x94) = 2;
    }
}

// .text:0x0006D288 size:0x10 mapped:0x806AC31C
void fn_2_6D288(u8 *obj) {
    *(s16 *)(obj + 0xA2) -= 1;
}

// .text:0x0006D250 size:0x38 mapped:0x806AC2E4
void fn_2_6D250(u8 *obj) {
    lbl_2_data_2A268[*(s16 *)(obj + 0x94)](obj);
}

// .text:0x0006D164 size:0xEC mapped:0x806AC1F8
void fn_2_6D164(u8 *obj) {
    lbl_2_bss_1A8248[*(s32 *)(obj + 0x80) * 0xD8 + 0x16D0] = 1;
    *(f32 *)(obj + 0x34) = 0.0f;
    *(f32 *)(obj + 0x4C) = 0.0f;
    rep0B08SetCurState(*(s32 *)(obj + 0x80), 4);
    *(s16 *)(obj + 0x94) = 1;
}

// .text:0x0006D088 size:0xDC mapped:0x806AC11C
void fn_2_6D088(u8 *obj) {
    if (fn_2_8CC88(*(s32 *)(obj + 0x84))) {
        rep0B08SetCurState(*(s32 *)(obj + 0x80), 7);
        *(s16 *)(obj + 0xA2) = 0x1E;
        *(s16 *)(obj + 0x94) = 2;
    }
}

// .text:0x0006D078 size:0x10 mapped:0x806AC10C
void fn_2_6D078(u8 *obj) {
    *(s16 *)(obj + 0xA2) -= 1;
}

// .text:0x0006D040 size:0x38 mapped:0x806AC0D4
void fn_2_6D040(u8 *obj) {
    lbl_2_data_2A274[*(s16 *)(obj + 0x94)](obj);
}

// .text:0x0006CDD4 size:0x26C mapped:0x806ABE68
void fn_2_6CDD4(u8 *obj) {
    s32 idx = *(s32 *)(obj + 0x80);
    u8 *slot = REP_SLOT(idx);
    f32 dx;
    f32 dz;
    lbl_2_bss_1A8248[idx * 0xD8 + 0x16D0] = 1;
    memcpy(obj + 0x74, lbl_2_data_2EA4 + *(s16 *)(lbl_2_bss_1A8248 + 0x16C0) * 0xC, 12);
    *(f32 *)(slot + 0x0C) = *(f32 *)(obj + 0x74);
    *(f32 *)(slot + 0x14) = *(f32 *)(obj + 0x7C);
    dx = *(f32 *)(obj + 0x74) - *(f32 *)(slot + 0x00);
    dz = *(f32 *)(obj + 0x7C) - *(f32 *)(slot + 0x08);
    if (dx == 0.0f && dz == 0.0f) {
        *(f32 *)(slot + 0x38) = 0.0f;
        *(f32 *)(slot + 0x50) = 0.0f;
    } else {
        *(f32 *)(slot + 0x50) = dolsqrtf2(dx * dx + dz * dz);
    }
    slot[0xBB] = 1;
    obj[0xBA] = 0xC;
    fn_2_69E1C(idx);
    rep0B08SetCurState(idx, 0);
    *(s16 *)(obj + 0x94) = 1;
}

// .text:0x0006CCB8 size:0x11C mapped:0x806ABD4C
void fn_2_6CCB8(u8 *obj) {
    fn_2_69E1C(*(s32 *)(obj + 0x80));
    if (*(f32 *)(obj + 0x50) > 0.0f) {
        s16 *row;
        obj[0xBA] = 4;
        obj[0xC4] = 1;
        row = (s16 *)(lbl_2_data_3D30 + *(s16 *)(lbl_2_bss_1A8248 + 0x16C2) * 8);
        if (*(s16 *)(lbl_2_bss_1A8248 + 0x16C0) == row[0]) {
            lbl_2_bss_1A8248[0x4448] = 0;
        }
        if (*(s16 *)(lbl_2_bss_1A8248 + 0x16C0) == row[1]) {
            lbl_2_bss_1A8248[0x4448] = 1;
        }
        if (*(s16 *)(lbl_2_bss_1A8248 + 0x16C0) == row[2]) {
            lbl_2_bss_1A8248[0x4448] = 2;
        }
        if (*(s16 *)(lbl_2_bss_1A8248 + 0x16C0) == row[3]) {
            lbl_2_bss_1A8248[0x4448] = 3;
        }
        *(s16 *)(lbl_2_bss_1A8248 + 0x16C2) = *(s16 *)(lbl_2_bss_1A8248 + 0x16C0);
        *(s16 *)(obj + 0x94) = 2;
    }
}

// .text:0x0006CBB0 size:0x108 mapped:0x806ABC44
void fn_2_6CBB0(u8 *obj) {
    s32 idx = *(s32 *)(obj + 0x80);
    u8 kind;
    u8 *e;
    s32 v0;
    s32 v2;
    s32 v4;
    fn_2_69E1C(idx);
    kind = lbl_2_bss_1A8248[0x441C];
    e = lbl_2_data_2E80 + kind * 6;
    v0 = *(s16 *)(e + 0x0) << 1;
    v2 = *(s16 *)(e + 0x2) << 1;
    v4 = *(s16 *)(e + 0x4) << 1;
    if (*(s32 *)(obj + 0x80) == 0) {
        if (hugeAnimStruct + 0xC04) {
            s16 v = *(s16 *)(hugeAnimStruct + 0xC04 + 0x68);
            if (v == v0 - v4 || v == v0 - v2) {
                fn_80062890(kind == 5 ? 1 : 0);
            }
        }
    }
    if (*(f32 *)(obj + 0x38) > 0.0f) {
        u8 *slot = REP_SLOT(idx);
        slot[0xC3] = 3;
        *(s16 *)(slot + 0x94) = 0;
    }
}

// .text:0x0006CB78 size:0x38 mapped:0x806ABC0C
void fn_2_6CB78(u8 *obj) {
    lbl_2_data_2A280[*(s16 *)(obj + 0x94)](obj);
}

// .text:0x0006C988 size:0x1F0 mapped:0x806ABA1C
void fn_2_6C988(u8 *obj) {
    s32 idx = *(s32 *)(obj + 0x80);
    f32 tmp[3];
    f32 v[3];
    Mtx mtx;
    f32 r;
    lbl_2_bss_1A8248[idx * 0xD8 + 0x16D0] = 1;
    PSVECSubtract((Vec *)(lbl_2_data_2EA4 + *(s16 *)(lbl_2_bss_1A8248 + 0x16C0) * 0xC),
                  (Vec *)(lbl_2_data_2EA4 + *(s16 *)(lbl_2_bss_1A8248 + 0x16BE) * 0xC),
                  (Vec *)tmp);
    PSVECScale((Vec *)tmp, 0.5f, (Vec *)tmp);
    PSMTXRotRad(mtx, 'Y', *(f32 *)(lbl_2_bss_1A8248 + 0x165C));
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = -1.2000000476837158f;
    PSMTXMultVec(mtx, (Vec *)v, (Vec *)v);
    PSVECAdd((Vec *)tmp, (Vec *)v, (Vec *)tmp);
    memcpy(obj, lbl_2_data_2EA4 + *(s16 *)(lbl_2_bss_1A8248 + 0x16BE) * 0xC, 12);
    PSVECAdd((Vec *)obj, (Vec *)tmp, (Vec *)obj);
    rep0B08SetCurState(*(s32 *)(obj + 0x80), 1);
    r = (f32)atan2(-(*(f32 *)(lbl_2_bss_1A8248 + 0x1610) - *(f32 *)(obj + 0x00)),
                   -(*(f32 *)(lbl_2_bss_1A8248 + 0x1618) - *(f32 *)(obj + 0x08)));
    *(f32 *)(obj + 0x4C) = r;
    fn_2_46C88(*(s32 *)(obj + 0x80), 0);
    *(s16 *)(obj + 0x94) = 1;
}

// .text:0x0006C97C size:0xC mapped:0x806ABA10
void fn_2_6C97C(u8 *obj) {
    *(s16 *)(obj + 0x94) = 2;
}

// .text:0x0006C970 size:0xC mapped:0x806ABA04
void fn_2_6C970(u8 *obj) {
    *(s16 *)(obj + 0x94) = 2;
}

// .text:0x0006C938 size:0x38 mapped:0x806AB9CC
void checkForButtonPressToSkip_maybe(u8 *obj) {
    lbl_2_data_2A28C[*(s16 *)(obj + 0x94)](obj);
}

// .text:0x0006C5E0 size:0x358 mapped:0x806AB674
void fn_2_6C5E0(u8 *obj) {
    s32 idx = *(s32 *)(obj + 0x80);
    u8 *slot = REP_SLOT(idx);
    Vec tmp;
    s32 flag;
    slot[0xC0] = 1;
    obj[0xBA] = 0xB;
    if (lbl_2_bss_1A8248[0x4439] == 1) {
        memcpy(obj + 0x74, lbl_2_data_2EA4 + 0x1E0, 12);
        flag = 1;
    } else if (*(f32 *)(obj + 0x00) > *(f32 *)(lbl_2_data_2EA4 + 0x1E0) &&
               *(f32 *)(obj + 0x08) > *(f32 *)(lbl_2_data_2EA4 + 0x1E8)) {
        memcpy(obj + 0x74, lbl_2_data_2EA4 + 0x1F8, 12);
        flag = 0;
    } else {
        memcpy(obj + 0x74, lbl_2_data_2EA4 + 0x1E0, 12);
        flag = 1;
    }
    slot = REP_SLOT(idx);
    *(f32 *)(slot + 0x0C) = *(f32 *)(obj + 0x74);
    *(f32 *)(slot + 0x14) = *(f32 *)(obj + 0x7C);
    {
        f32 dx = *(f32 *)(obj + 0x74) - *(f32 *)(slot + 0x00);
        f32 dz = *(f32 *)(obj + 0x7C) - *(f32 *)(slot + 0x08);
        if (dx == 0.0f && dz == 0.0f) {
            *(f32 *)(slot + 0x38) = 0.0f;
            *(f32 *)(slot + 0x50) = 0.0f;
        } else {
            *(f32 *)(slot + 0x50) = dolsqrtf2(dx * dx + dz * dz);
        }
    }
    slot[0xBB] = 1;
    rep0B08SetCurState(*(s32 *)(slot + 0x80), 0);
    if (*(s8 *)(lbl_2_bss_1A824C + 0x197843) == 0) {
        tmp.x = 2.0f * *(f32 *)(obj + 0x00);
        tmp.y = 2.0f * (0.3f + *(f32 *)(obj + 0x04));
        tmp.z = 2.0f * *(f32 *)(obj + 0x08);
        fn_2_9033C(0x1C, &tmp, 0.0f);
        fn_2_92654(0x1C, 0xA);
        fn_2_8F73C(0x1C, 1);
    }
    if (flag == 1) {
        *(s16 *)(obj + 0x94) = 1;
    } else {
        *(s16 *)(obj + 0x94) = 2;
    }
}

// .text:0x0006C348 size:0x298 mapped:0x806AB3DC
void fn_2_6C348(u8 *obj) {
    u8 *slot;
    s32 idx = *(s32 *)(obj + 0x80);
    f32 dx;
    f32 dz;
    fn_2_69E1C(idx);
    if (*(f32 *)(obj + 0x50) > 0.0f) {
        return;
    }
    if (lbl_2_bss_1A8248[0x4439] == 1) {
        obj[0xBA] = 4;
        obj[0xC4] = 1;
        *(s16 *)(obj + 0x94) = 3;
        return;
    }
    memcpy(obj + 0x74, lbl_2_data_2EA4 + 0x1F8, 12);
    slot = REP_SLOT(idx);
    *(f32 *)(slot + 0x0C) = 0.2f + *(f32 *)(obj + 0x74);
    *(f32 *)(slot + 0x14) = 0.5f + *(f32 *)(obj + 0x7C);
    dx = *(f32 *)(slot + 0x0C) - *(f32 *)(slot + 0x00);
    dz = *(f32 *)(slot + 0x14) - *(f32 *)(slot + 0x08);
    if (dx == 0.0f && dz == 0.0f) {
        *(f32 *)(slot + 0x38) = 0.0f;
        *(f32 *)(slot + 0x50) = 0.0f;
    } else {
        *(f32 *)(slot + 0x50) = dolsqrtf2(dx * dx + dz * dz);
    }
    slot[0xBB] = 1;
    rep0B08SetCurState(idx, 0);
    *(s16 *)(obj + 0x94) = 2;
}

// .text:0x0006C2E8 size:0x60 mapped:0x806AB37C
void fn_2_6C2E8(u8 *obj) {
    fn_2_69E1C(*(s32 *)(obj + 0x80));
    if (*(f32 *)(obj + 0x50) > 0.0f) {
        obj[0xBA] = 4;
        obj[0xC4] = 1;
        *(s16 *)(obj + 0x94) = 3;
    }
}

// .text:0x0006C2C4 size:0x24 mapped:0x806AB358
void fn_2_6C2C4(void) {
    lbl_2_bss_1A8248[0x442F] = 0;
    lbl_2_bss_1A8248[0x17AB] = 0;
    *(s16 *)(lbl_2_bss_1A8248 + 0x177C) = 0;
}

// .text:0x0006C28C size:0x38 mapped:0x806AB320
void fn_2_6C28C(u8 *obj) {
    lbl_2_data_2A29C[*(s16 *)(obj + 0x94)](obj);
}

// .text:0x0006C190 size:0xFC mapped:0x806AB224
void fn_2_6C190(u8 *obj) {
    lbl_2_bss_1A8248[*(s32 *)(obj + 0x80) * 0xD8 + 0x16D0] = 1;
    rep0B08SetCurState(*(s32 *)(obj + 0x80), 1);
    *(f32 *)(obj + 0x34) = *(f32 *)(obj + 0x4C);
    fn_2_46C88(lbl_2_bss_1A8248[0x441E], 0);
    *(s16 *)(obj + 0x94) = 1;
}

// .text:0x0006C120 size:0x70 mapped:0x806AB1B4
void fn_2_6C120(u8 *obj) {
    f32 dist = (f32)fabs(PSVECDistance((Vec *)REP_SLOT(0), (Vec *)obj));
    if (dist < 1.6f && dist != 0.0f) {
        *(s16 *)(obj + 0x94) = 2;
    }
}

// .text:0x0006C020 size:0x100 mapped:0x806AB0B4
void fn_2_6C020(u8 *obj) {
    u8 *b = REP_SLOT(0);
    f32 r;
    *(f32 *)(obj + 0x4C) = (f32)atan2(-(*(f32 *)(b + 0x00) - *(f32 *)(obj + 0x00)),
                                      -(*(f32 *)(b + 0x08) - *(f32 *)(obj + 0x08)));
    r = fn_2_4A18C(*(f32 *)(obj + 0x34) - *(f32 *)(obj + 0x4C));
    if (r >= 0.02 || r <= 0.0f) {
        if (r <= -0.02 || r >= 0.0f) {
            if (r >= 0.0f) {
                *(f32 *)(obj + 0x34) = *(f32 *)(obj + 0x34) - 0.05235987901687622f;
            } else {
                *(f32 *)(obj + 0x34) = *(f32 *)(obj + 0x34) + 0.05235987901687622f;
            }
        } else {
            *(s16 *)(obj + 0x94) = 3;
        }
    } else {
        *(s16 *)(obj + 0x94) = 3;
    }
    *(f32 *)(obj + 0x4C) = *(f32 *)(obj + 0x34);
}

// .text:0x0006BFC0 size:0x60 mapped:0x806AB054
void fn_2_6BFC0(u8 *obj) {
    f32 dist = (f32)fabs(PSVECDistance((Vec *)REP_SLOT(0), (Vec *)obj));
    if (dist > 1.6f) {
        *(s16 *)(obj + 0x94) = 1;
    }
}

// .text:0x0006BF88 size:0x38 mapped:0x806AB01C
void fn_2_6BF88(u8 *obj) {
    lbl_2_data_2A2AC[*(s16 *)(obj + 0x94)](obj);
}

// .text:0x0006BE80 size:0x108 mapped:0x806AAF14
void fn_2_6BE80(u8 *obj) {
    lbl_2_bss_1A8248[*(s32 *)(obj + 0x80) * 0xD8 + 0x16D0] = 0;
    rep0B08SetCurState(*(s32 *)(obj + 0x80), 1);
    lbl_2_bss_1A8248[*(s32 *)(obj + 0x80) * 0xD8 + 0x16DA] = 0xFF;
    *(f32 *)(obj + 0x8C) = 0.0f;
    *(s16 *)(obj + 0x94) = 1;
}

// .text:0x0006BDE0 size:0xA0 mapped:0x806AAE74
void fn_2_6BDE0(u8 *obj) {
    s32 v;
    lbl_2_bss_1A8248[*(s32 *)(obj + 0x80) * 0xD8 + 0x16D0] = 1;
    *(f32 *)(obj + 0x8C) = (f32)(*(f32 *)(obj + 0x8C) + 0.1);
    v = (s32)(256.0f * *(f32 *)(obj + 0x8C));
    if (v < 0xFF) {
        lbl_2_bss_1A8248[*(s32 *)(obj + 0x80) * 0xD8 + 0x16DA] = v;
    } else {
        lbl_2_bss_1A8248[*(s32 *)(obj + 0x80) * 0xD8 + 0x16DA] = 0xFF;
        *(s16 *)(obj + 0x94) = 2;
    }
}

// .text:0x0006BDD4 size:0xC mapped:0x806AAE68
void fn_2_6BDD4(u8 *obj) {
    *(s16 *)(obj + 0x94) = 2;
}

// .text:0x0006BD9C size:0x38 mapped:0x806AAE30
void fn_2_6BD9C(u8 *obj) {
    lbl_2_data_2A2B8[*(s16 *)(obj + 0x94)](obj);
}

// .text:0x0006BCAC size:0xF0 mapped:0x806AAD40
void fn_2_6BCAC(u8 *obj) {
    s32 n = *(s32 *)(obj + 0x80);
    u8 *ent;
    lbl_2_bss_1A8248[n * 0xD8 + 0x16D0] = 0;
    ent = lbl_2_data_3C84 + 9 * 6;
    fn_2_8CD58(n, *(s16 *)(ent + 0x0), ent[0x4], 1, *(s16 *)(ent + 0x2), 0, 0);
    *(s16 *)(lbl_2_bss_1A824C + 0x190000 + 0x7756 + n * 2) = 9;
    *(f32 *)(obj + 0x4C) = 0.0f;
    *(f32 *)(obj + 0x34) = 0.0f;
    lbl_2_bss_1A8248[n * 0xD8 + 0x16DA] = 0xFF;
    *(f32 *)(obj + 0x8C) = 0.0f;
    *(s16 *)(obj + 0x94) = 1;
}

// .text:0x0006BC0C size:0xA0 mapped:0x806AACA0
void fn_2_6BC0C(u8 *obj) {
    s32 v;
    lbl_2_bss_1A8248[*(s32 *)(obj + 0x80) * 0xD8 + 0x16D0] = 1;
    *(f32 *)(obj + 0x8C) = (f32)(*(f32 *)(obj + 0x8C) + 0.1);
    v = (s32)(256.0f * *(f32 *)(obj + 0x8C));
    if (v < 0xFF) {
        lbl_2_bss_1A8248[*(s32 *)(obj + 0x80) * 0xD8 + 0x16DA] = v;
    } else {
        lbl_2_bss_1A8248[*(s32 *)(obj + 0x80) * 0xD8 + 0x16DA] = 0xFF;
        *(s16 *)(obj + 0x94) = 2;
    }
}

// .text:0x0006BC00 size:0xC mapped:0x806AAC94
void fn_2_6BC00(u8 *obj) {
    *(s16 *)(obj + 0x94) = 2;
}

// .text:0x0006BBC8 size:0x38 mapped:0x806AAC5C
void fn_2_6BBC8(u8 *obj) {
    lbl_2_data_2A2C4[*(s16 *)(obj + 0x94)](obj);
}

// .text:0x0006BB7C size:0x4C mapped:0x806AAC10
void fn_2_6BB7C(u8 *obj) {
    lbl_2_bss_1A8248[*(s32 *)(obj + 0x80) * 0xD8 + 0x16D0] = 1;
    lbl_2_bss_1A8248[*(s32 *)(obj + 0x80) * 0xD8 + 0x16DA] = 0xFF;
    *(f32 *)(obj + 0x8C) = 1.0f;
    *(s16 *)(obj + 0x94) = 1;
}

// .text:0x0006BAD8 size:0xA4 mapped:0x806AAB6C
void fn_2_6BAD8(u8 *obj) {
    s32 v;
    *(f32 *)(obj + 0x8C) = (f32)(*(f32 *)(obj + 0x8C) - 0.1);
    v = (s32)(255.0f * *(f32 *)(obj + 0x8C));
    if (v > 1) {
        lbl_2_bss_1A8248[*(s32 *)(obj + 0x80) * 0xD8 + 0x16DA] = v;
    } else {
        lbl_2_bss_1A8248[*(s32 *)(obj + 0x80) * 0xD8 + 0x16DA] = 0;
        lbl_2_bss_1A8248[*(s32 *)(obj + 0x80) * 0xD8 + 0x16D0] = 0;
        *(s16 *)(obj + 0x94) = 2;
    }
}

// .text:0x0006BAAC size:0x2C mapped:0x806AAB40
void fn_2_6BAAC(u8 *obj) {
    s32 idx = *(s32 *)(obj + 0x80);
    lbl_2_bss_1A8248[idx * 0xD8 + 0x16DA] = 0xFF;
    *(s16 *)(obj + 0x94) = 3;
}

// .text:0x0006BA50 size:0x5C mapped:0x806AAAE4
void fn_2_6BA50(u8 *obj) {
    GXColor color = *(GXColor *)&inputParams[0x28];
    color.a = 0xFF;
    adjustLightingParams(0, color);
    *(s16 *)(obj + 0x94) = 2;
}

// .text:0x0006BA18 size:0x38 mapped:0x806AAAAC
void fn_2_6BA18(u8 *obj) {
    lbl_2_data_2A2D4[*(s16 *)(obj + 0x94)](obj);
}

// .text:0x0006B744 size:0x2D4 mapped:0x806AA7D8
void fn_2_6B744(u8 *obj) {
    s32 idx = *(s32 *)(obj + 0x80);
    u8 *slot = REP_SLOT(idx);
    Vec tmp;
    f32 dx;
    f32 dz;
    slot[0xC0] = 1;
    obj[0xBA] = 0xC;
    obj[0xD0] = 1;
    *(f32 *)(obj + 0x90) = 0.0f;
    *(f32 *)(obj + 0x04) = 0.0f;
    if (*(s16 *)(slot + 0xB0) == 0x30) {
        memcpy(&tmp, lbl_2_data_3198 + 0x1F4, 12);
    } else {
        memcpy(&tmp, lbl_2_data_3198 + 0x208, 12);
    }
    PSVECScale(&tmp, 0.5f, &tmp);
    memcpy(obj + 0x74, &tmp, 12);
    *(f32 *)(slot + 0x0C) = *(f32 *)(obj + 0x74);
    *(f32 *)(slot + 0x14) = *(f32 *)(obj + 0x7C);
    dx = *(f32 *)(obj + 0x74) - *(f32 *)(slot + 0x00);
    dz = *(f32 *)(obj + 0x7C) - *(f32 *)(slot + 0x08);
    if (dx == 0.0f && dz == 0.0f) {
        *(f32 *)(slot + 0x38) = 0.0f;
        *(f32 *)(slot + 0x50) = 0.0f;
    } else {
        *(f32 *)(slot + 0x50) = dolsqrtf2(dx * dx + dz * dz);
    }
    slot[0xBB] = 1;
    rep0B08SetCurState(*(s32 *)(slot + 0x80), 8);
    *(s16 *)(obj + 0x94) = 1;
}

// .text:0x0006B620 size:0x124 mapped:0x806AA6B4
void fn_2_6B620(u8 *obj) {
    s32 idx = *(s32 *)(obj + 0x80);
    u8 *slot;
    fn_2_69E1C(idx);
    slot = REP_SLOT(idx);
    if (slot[0xD0] != 0) {
        f32 angle = *(f32 *)(slot + 0x90);
        f32 f2 = 1.6f * -(f32)sin(angle);
        *(f32 *)(slot + 0x90) = angle + 0.07f;
        if (*(f32 *)(slot + 0x4) > 1.5f) {
            *(f32 *)(slot + 0x90) = 0.0f;
            f2 = 0.0f;
            slot[0xD0] = 0;
            if (slot[0xC3] == 0x13) {
                lbl_2_bss_1A8248[idx * 0xD8 + 0x16D0] = 0;
            }
        }
        *(f32 *)(slot + 0x4) = f2;
    } else {
        *(f32 *)(slot + 0x4) = 0.0f;
        if (*(f32 *)(obj + 0x50) > 0.0f) {
            obj[0xBA] = 4;
            obj[0xC4] = 1;
            *(s16 *)(obj + 0x94) = 2;
        }
    }
}

// .text:0x0006B4FC size:0x124 mapped:0x806AA590
void fn_2_6B4FC(u8 *obj) {
    s32 idx = *(s32 *)(obj + 0x80);
    u8 *slot = REP_SLOT(idx);
    if (slot[0xD0] != 0) {
        f32 angle = *(f32 *)(slot + 0x90);
        f32 f2 = 1.6f * -(f32)sin(angle);
        *(f32 *)(slot + 0x90) = angle + 0.07f;
        if (*(f32 *)(slot + 0x4) > 1.5f) {
            *(f32 *)(slot + 0x90) = 0.0f;
            f2 = 0.0f;
            slot[0xD0] = 0;
            if (slot[0xC3] == 0x13) {
                lbl_2_bss_1A8248[idx * 0xD8 + 0x16D0] = 0;
            }
        }
        *(f32 *)(slot + 0x4) = f2;
    } else {
        *(f32 *)(slot + 0x4) = 0.0f;
        if (obj[0xD0] == 0) {
            slot[0xC3] = 0;
            *(s16 *)(slot + 0x94) = 0;
        }
    }
}

// .text:0x0006B4C4 size:0x38 mapped:0x806AA558
void fn_2_6B4C4(u8 *obj) {
    lbl_2_data_2A2E0[*(s16 *)(obj + 0x94)](obj);
}

// .text:0x0006B238 size:0x28C mapped:0x806AA2CC
void fn_2_6B238(u8 *obj) {
    s32 idx = *(s32 *)(obj + 0x80);
    u8 *slot = REP_SLOT(idx);
    lbl_2_bss_1A8248[idx * 0xD8 + 0x16D0] = 1;
    obj[0xBA] = 0xE;
    obj[0xD0] = 1;
    *(f32 *)(obj + 0x90) = 0.0f;
    *(f32 *)(obj + 0x04) = 0.0f;
    if (*(s16 *)(slot + 0xB0) == 0x30) {
        memcpy(obj + 0x74, lbl_2_data_2EA4 + 0x258, 12);
    } else {
        memcpy(obj + 0x74, lbl_2_data_2EA4 + 0xD8, 12);
    }
    *(f32 *)(slot + 0x0C) = *(f32 *)(obj + 0x74);
    *(f32 *)(slot + 0x14) = *(f32 *)(obj + 0x7C);
    {
        f32 dx = *(f32 *)(obj + 0x74) - *(f32 *)(slot + 0x00);
        f32 dz = *(f32 *)(obj + 0x7C) - *(f32 *)(slot + 0x08);
        if (dx == 0.0f && dz == 0.0f) {
            *(f32 *)(slot + 0x38) = 0.0f;
            *(f32 *)(slot + 0x50) = 0.0f;
        } else {
            *(f32 *)(slot + 0x50) = dolsqrtf2(dx * dx + dz * dz);
        }
    }
    slot[0xBB] = 1;
    rep0B08SetCurState(idx, 8);
    *(s16 *)(obj + 0x94) = 1;
}

// .text:0x0006B120 size:0x118 mapped:0x806AA1B4
void fn_2_6B120(u8 *obj) {
    s32 idx = *(s32 *)(obj + 0x80);
    u8 *slot;
    fn_2_69E1C(idx);
    slot = REP_SLOT(idx);
    if (slot[0xD0] != 0) {
        f32 angle = *(f32 *)(slot + 0x90);
        f32 f2 = 1.6f * -(f32)sin(angle);
        *(f32 *)(slot + 0x90) = angle + 0.07f;
        if (*(f32 *)(slot + 0x4) > 0.0f) {
            *(f32 *)(slot + 0x90) = 0.0f;
            f2 = 0.0f;
            slot[0xD0] = 0;
            if (slot[0xC3] == 0x13) {
                lbl_2_bss_1A8248[idx * 0xD8 + 0x16D0] = 0;
            }
        }
        *(f32 *)(slot + 0x4) = f2;
    } else {
        *(f32 *)(slot + 0x4) = 0.0f;
        if (*(f32 *)(obj + 0x50) > 0.0f) {
            obj[0xBA] = 4;
            *(s16 *)(obj + 0x94) = 2;
        }
    }
}

// .text:0x0006B024 size:0xFC mapped:0x806AA0B8
void fn_2_6B024(u8 *obj) {
    s32 idx = *(s32 *)(obj + 0x80);
    u8 *slot = REP_SLOT(idx);
    f32 f2;
    if (slot[0xD0] != 0) {
        f32 angle = *(f32 *)(slot + 0x90);
        f2 = 1.6f * -(f32)sin(angle);
        *(f32 *)(slot + 0x90) = angle + 0.07f;
        if (*(f32 *)(slot + 0x4) > 0.0f) {
            *(f32 *)(slot + 0x90) = 0.0f;
            f2 = 0.0f;
            slot[0xD0] = 0;
            if (slot[0xC3] == 0x13) {
                lbl_2_bss_1A8248[idx * 0xD8 + 0x16D0] = 0;
            }
        }
        *(f32 *)(slot + 0x4) = f2;
    } else {
        *(f32 *)(slot + 0x4) = 0.0f;
        if (obj[0xD0] == 0) {
            obj[0xC4] = 1;
        }
    }
}

// .text:0x0006AFD4 size:0x50 mapped:0x806AA068
s32 fn_2_6AFD4(s32 idx) {
    u8 *slot = REP_SLOT(idx);
    if (slot[0xC4] == 1) {
        slot[0xC4] = 0;
        return 1;
    }
    if (slot[0xC4] == 2) {
        slot[0xC4] = 0;
        return 2;
    }
    return 0;
}

// .text:0x0006AF9C size:0x38 mapped:0x806AA030
BOOL fn_2_6AF9C(s32 idx) {
    u8 *slot = REP_SLOT(idx);
    if (slot[0xD0] == 0) {
        slot[0xD0] = 0;
        return TRUE;
    }
    return FALSE;
}

// .text:0x0006AF80 size:0x1C mapped:0x806AA014
void fn_2_6AF80(s32 idx, u8 val) {
    lbl_2_bss_1A8248[idx * 0xD8 + 0x16D4] = val;
}

// .text:0x0006AE08 size:0x178 mapped:0x806A9E9C
void fn_2_6AE08(void) {
    s32 i;
    for (i = 0; i < 8; i++) {
        u8 *slot = REP_SLOT(i);
        memset(slot, 0, 0xD8);
        *(s32 *)(slot + 0x80) = i;
        *(s32 *)(slot + 0x84) = i;
        *(f32 *)(slot + 0x8C) = 0.0f;
        slot[0xB6] = 10;
        *(f32 *)(slot + 0x40) = 0.0003f * (f32)slot[0xB6] + 0.1f;
        slot[0xB8] = 10;
        slot[0xB7] = 15;
        *(f32 *)(slot + 0x44) = *(f32 *)(slot + 0x40) / (f32)slot[0xB7];
        slot[0xBB] = 0;
        slot[0xC0] = 0;
        *(s16 *)(slot + 0x96) = i;
        *(s16 *)(slot + 0x98) = -1;
        slot[0xBC] = 1;
        slot[0xBA] = 12;
        slot[0xC3] = 0;
        *(s16 *)(slot + 0x94) = 0;
        slot[0xC6] = 0xFF;
        slot[0xC4] = 0;
        slot[0xC5] = 0;
        *(f32 *)(slot + 0x88) = 0.0f;
        slot[0xC1] = 0;
        *(s16 *)(slot + 0xAC) = 0;
        slot[0xCA] = 0xFF;
        slot[0xCB] = 0xFF;
        slot[0xCC] = 0xFF;
    }
}

// .text:0x0006ACF4 size:0x114 mapped:0x806A9D88
void fn_2_6ACF4(void) {
    s32 i;
    for (i = 0; i < 8; i++) {
        u8 *slot = REP_SLOT(i);
        *(s32 *)(slot + 0x80) = i;
        *(s32 *)(slot + 0x84) = i;
        *(f32 *)(slot + 0x8C) = 0.0f;
        slot[0xB6] = 10;
        *(f32 *)(slot + 0x40) = 0.0003f * (f32)slot[0xB6] + 0.1f;
        slot[0xB8] = 10;
        slot[0xB7] = 15;
        *(f32 *)(slot + 0x44) = *(f32 *)(slot + 0x40) / (f32)slot[0xB7];
        slot[0xBB] = 0;
        slot[0xC0] = 0;
        *(s16 *)(slot + 0x96) = i;
        *(s16 *)(slot + 0x98) = -1;
        slot[0xBC] = 1;
        slot[0xC3] = 0;
        *(s16 *)(slot + 0x94) = 0;
        slot[0xC6] = 0xFF;
        slot[0xC4] = 0;
        slot[0xC5] = 0;
        *(f32 *)(slot + 0x88) = 0.0f;
        slot[0xC1] = 0;
        *(s16 *)(slot + 0xAC) = 0;
        slot[0xCA] = 0xFF;
        slot[0xCB] = 0xFF;
        slot[0xCC] = 0xFF;
    }
}

// .text:0x0006ACF0 size:0x4 mapped:0x806A9D84
void fn_2_6ACF0(void) {
    return;
}

// .text:0x0006ABFC size:0xF4 mapped:0x806A9C90
void fn_2_6ABFC(s32 idx, s32 which) {
    u8 *slot = REP_SLOT(idx);
    if (idx <= 6) {
        memcpy(slot, lbl_2_data_2EA4 + which * 0xC, 12);
    } else {
        memcpy(slot, lbl_2_data_3150 + (idx - 7) * 0xC, 12);
    }
    *(f32 *)(slot + 0x0C) = 0.0f;
    *(f32 *)(slot + 0x10) = 0.0f;
    *(f32 *)(slot + 0x14) = 0.0f;
    *(f32 *)(slot + 0x18) = 0.0f;
    *(f32 *)(slot + 0x1C) = 0.0f;
    *(f32 *)(slot + 0x20) = 0.0f;
    *(f32 *)(slot + 0x6C) = *(f32 *)(slot + 0x00);
    *(f32 *)(slot + 0x70) = *(f32 *)(slot + 0x08);
    *(f32 *)(slot + 0x38) = 0.0f;
    slot[0xBB] = 0;
    {
        f32 v = *(f32 *)(slot + 0x4C);
        *(f32 *)(slot + 0x34) = v;
        *(f32 *)(slot + 0x30) = v;
    }
}

// .text:0x0006AB3C size:0xC0 mapped:0x806A9BD0
void fn_2_6AB3C(s32 idx, const void *src, f32 angle) {
    u8 *slot = REP_SLOT(idx);
    memcpy(slot, src, 12);
    *(f32 *)(slot + 0x0C) = 0.0f;
    *(f32 *)(slot + 0x10) = 0.0f;
    *(f32 *)(slot + 0x14) = 0.0f;
    *(f32 *)(slot + 0x18) = 0.0f;
    *(f32 *)(slot + 0x1C) = 0.0f;
    *(f32 *)(slot + 0x20) = 0.0f;
    *(f32 *)(slot + 0x30) = angle;
    *(f32 *)(slot + 0x6C) = *(f32 *)(slot + 0x00);
    *(f32 *)(slot + 0x70) = *(f32 *)(slot + 0x08);
    *(f32 *)(slot + 0x38) = 0.0f;
    slot[0xBB] = 0;
    angle = (f32)atan2(*(f32 *)(slot + 0x00), *(f32 *)(slot + 0x08));
    *(f32 *)(slot + 0x34) = angle;
    *(f32 *)(slot + 0x30) = angle;
}

// .text:0x0006AABC size:0x80 mapped:0x806A9B50
void fn_2_6AABC(s32 idx, const void *src) {
    u8 *slot = REP_SLOT(idx);
    memcpy(slot, src, 12);
    *(f32 *)(slot + 0x0C) = 0.0f;
    *(f32 *)(slot + 0x10) = 0.0f;
    *(f32 *)(slot + 0x14) = 0.0f;
    *(f32 *)(slot + 0x18) = 0.0f;
    *(f32 *)(slot + 0x1C) = 0.0f;
    *(f32 *)(slot + 0x20) = 0.0f;
    *(f32 *)(slot + 0x6C) = *(f32 *)(slot + 0x00);
    *(f32 *)(slot + 0x70) = *(f32 *)(slot + 0x08);
    *(f32 *)(slot + 0x38) = 0.0f;
    slot[0xBB] = 0;
}

// .text:0x0006AAB8 size:0x4 mapped:0x806A9B4C
void fn_2_6AAB8(void) {
    return;
}

// .text:0x0006A87C size:0x23C mapped:0x806A9910
void fn_2_6A87C(void) {
    f32 tmp[3];
    f32 v[3];
    Mtx mtx;
    s32 k;
    u8 *e;
    lbl_2_bss_1A8248[0x16CB] = 0;
    memcpy(tmp, REP_SLOT(0), 12);
    PSVECSubtract((Vec *)tmp, (Vec *)lbl_2_data_2A340, (Vec *)v);
    v[0] = v[0] * -1.0f;
    v[2] = v[2] * -1.0f;
    k = (s8)lbl_2_bss_1A824C[0x197863];
    e = AtBat_ButtonInput1 + k * 0x20;
    tmp[0] = tmp[0] + (f32)(s8)e[0x10] / 768.0f;
    tmp[2] = tmp[2] + (f32)(s8)e[0x11] / 768.0f;
    if (v[0] != 0.0f || v[2] != 0.0f) {
        lbl_2_bss_A170 = fn_2_4A1E8(v[2]);
    }
    memcpy(lbl_2_data_2A340, REP_SLOT(0), 12);
    *(f32 *)(REP_SLOT(0) + 0x00) = tmp[0];
    *(f32 *)(REP_SLOT(0) + 0x04) = tmp[1];
    *(f32 *)(REP_SLOT(0) + 0x08) = tmp[2];
    *(f32 *)(REP_SLOT(0) + 0x4C) = lbl_2_bss_A170;
    if (*(f32 *)(REP_SLOT(0) + 0x38) > 0.0f) {
        u8 *slot = REP_SLOT(0);
        PSMTXRotRad(mtx, 'Y', *(f32 *)(slot + 0x4C));
        v[0] = 0.0f;
        v[1] = 0.0f;
        v[2] = -*(f32 *)(slot + 0x38);
        PSMTXMultVec(mtx, (Vec *)v, (Vec *)v);
        *(f32 *)(slot + 0x18) = v[0];
        *(f32 *)(slot + 0x20) = v[2];
    }
    {
        u8 *slot = REP_SLOT(0);
        *(f32 *)(slot + 0x00) += *(f32 *)(slot + 0x18);
        *(f32 *)(slot + 0x08) += *(f32 *)(slot + 0x20);
        *(f32 *)(slot + 0x0C) = *(f32 *)(slot + 0x00);
        *(f32 *)(slot + 0x14) = *(f32 *)(slot + 0x08);
        if (*(f32 *)(slot + 0x38) == 0.0f) {
            *(f32 *)(slot + 0x24) = 0.0f;
            *(f32 *)(slot + 0x2C) = 0.0f;
        }
    }
}

// .text:0x0006A708 size:0x174 mapped:0x806A979C
void fn_2_6A708(void) {
    f32 tmp[3];
    f32 v[3];
    s32 k;
    u8 *e;
    memcpy(tmp, REP_SLOT(0), 12);
    PSVECSubtract((Vec *)tmp, (Vec *)lbl_2_data_2A340, (Vec *)v);
    v[0] = v[0] * -1.0f;
    v[2] = v[2] * -1.0f;
    k = (s8)lbl_2_bss_1A824C[0x197863];
    e = AtBat_ButtonInput1 + k * 0x20;
    tmp[0] = tmp[0] + (f32)(s8)e[0x10] / 768.0f;
    tmp[2] = tmp[2] + (f32)(s8)e[0x11] / 768.0f;
    if (v[0] != 0.0f || v[2] != 0.0f) {
        lbl_2_bss_A170 = fn_2_4A1E8(v[2]);
    }
    memcpy(lbl_2_data_2A340, REP_SLOT(0), 12);
    *(f32 *)(REP_SLOT(0) + 0x00) = tmp[0];
    *(f32 *)(REP_SLOT(0) + 0x04) = tmp[1];
    *(f32 *)(REP_SLOT(0) + 0x08) = tmp[2];
    *(f32 *)(REP_SLOT(0) + 0x4C) = lbl_2_bss_A170;
}

// .text:0x0006A628 size:0xE0 mapped:0x806A96BC
void fn_2_6A628(void) {
    u8 *slot = REP_SLOT(0);
    Mtx mtx;
    f32 vec[3];
    if (*(f32 *)(slot + 0x38) > 0.0f) {
        PSMTXRotRad(mtx, 'Y', *(f32 *)(slot + 0x4C));
        vec[0] = 0.0f;
        vec[1] = 0.0f;
        vec[2] = -*(f32 *)(slot + 0x38);
        PSMTXMultVec(mtx, (Vec *)vec, (Vec *)vec);
        *(f32 *)(slot + 0x18) = vec[0];
        *(f32 *)(slot + 0x20) = vec[2];
    }
    *(f32 *)(slot + 0x00) += *(f32 *)(slot + 0x18);
    *(f32 *)(slot + 0x08) += *(f32 *)(slot + 0x20);
    *(f32 *)(slot + 0x0C) = *(f32 *)(slot + 0x00);
    *(f32 *)(slot + 0x14) = *(f32 *)(slot + 0x08);
    if (*(f32 *)(slot + 0x38) == 0.0f) {
        *(f32 *)(slot + 0x24) = 0.0f;
        *(f32 *)(slot + 0x2C) = 0.0f;
    }
}

// .text:0x0006A5A8 size:0x80 mapped:0x806A963C
void fn_2_6A5A8(s32 idx) {
    u8 *slot = REP_SLOT(idx);
    *(f32 *)(slot + 0x0C) = *(f32 *)(slot + 0x00);
    *(f32 *)(slot + 0x10) = *(f32 *)(slot + 0x04);
    *(f32 *)(slot + 0x14) = *(f32 *)(slot + 0x08);
    *(f32 *)(slot + 0x18) = 0.0f;
    *(f32 *)(slot + 0x1C) = 0.0f;
    *(f32 *)(slot + 0x20) = 0.0f;
    *(f32 *)(slot + 0x38) = 0.0f;
    *(f32 *)(slot + 0x50) = 0.0f;
}

// .text:0x0006A450 size:0x158 mapped:0x806A94E4
void fn_2_6A450(s32 idx, f32 x, f32 z) {
    u8 *slot = REP_SLOT(idx);
    f32 dx;
    f32 dz;
    *(f32 *)(slot + 0x0C) = x;
    *(f32 *)(slot + 0x14) = z;
    dx = x - *(f32 *)(slot + 0x00);
    dz = z - *(f32 *)(slot + 0x08);
    if (dx == 0.0f && dz == 0.0f) {
        *(f32 *)(slot + 0x38) = 0.0f;
        *(f32 *)(slot + 0x50) = 0.0f;
    } else {
        *(f32 *)(slot + 0x50) = dolsqrtf2(dx * dx + dz * dz);
    }
    slot[0xBB] = 1;
}

// .text:0x00069E1C size:0x634 mapped:0x806A8EB0
void fn_2_69E1C(s32 idx) {
    u8 *slot = REP_SLOT(idx);
    Mtx mtx;
    Vec v;
    f32 r;
    f32 a;
    f32 step;
    f32 dx;
    f32 dz;
    f32 len;
    s16 ang1;
    s16 ang2;
    u8 kind;
    if (*(f32 *)(slot + 0x50) > 0.0f) {
        ang1 = fn_2_4A2C4(*(f32 *)(slot + 0x4C));
        ang2 = fn_2_4A2C4(*(f32 *)(slot + 0x54));
        fn_2_4A310(ang1, ang2);
        slot[0xBC] = 0;
        slot[0xBD] = 0;
        if (*(s16 *)(slot + 0x9E) < 0x7FFE) {
            *(s16 *)(slot + 0x9E) = *(s16 *)(slot + 0x9E) + 1;
        } else {
            *(s16 *)(slot + 0x9E) = 0x7FFF;
        }
    } else {
        slot[0xBC] = 1;
        if (*(s16 *)(slot + 0x9E) > 0x2D) {
            *(s16 *)(slot + 0x9E) = 0x2D;
        }
        if (*(s16 *)(slot + 0x9E) != 0) {
            *(s16 *)(slot + 0x9E) = *(s16 *)(slot + 0x9E) - 1;
        }
    }
    switch (slot[0xBA]) {
    case 0:
        fn_2_69710(idx);
        break;
    case 1:
    case 5:
        *(f32 *)(slot + 0x38) = *(f32 *)(slot + 0x38) - 0.0005f;
        break;
    case 2:
    case 6:
        *(f32 *)(slot + 0x38) = *(f32 *)(slot + 0x38) - 0.001f;
        break;
    case 3:
    case 7:
        *(f32 *)(slot + 0x38) = *(f32 *)(slot + 0x38) - 0.002f;
        break;
    case 4:
    case 8:
        slot[0xBA] = slot[0xBA] + 0x14;
        break;
    case 9:
        *(f32 *)(slot + 0x38) = 0.0f;
        break;
    case 10:
        *(f32 *)(slot + 0x38) = 0.08f;
        break;
    case 11:
        *(f32 *)(slot + 0x38) = 0.12f;
        break;
    case 12:
        if (idx == 0) {
            kind = lbl_2_bss_1A8248[0x441C];
            *(f32 *)(slot + 0x38) = lbl_2_data_3F44[kind];
        } else {
            *(f32 *)(slot + 0x38) = 0.04f;
        }
        break;
    case 13:
        *(f32 *)(slot + 0x38) = 0.012f;
        break;
    case 14:
        *(f32 *)(slot + 0x38) = 0.025f;
        break;
    case 24:
    case 28:
        *(f32 *)(slot + 0x38) = *(f32 *)(slot + 0x38) - 0.005f;
        break;
    default:
        break;
    }
    if (*(f32 *)(slot + 0x38) <= 0.0f) {
        *(f32 *)(slot + 0x38) = 0.0f;
    }
    *(f32 *)(slot + 0x50) = *(f32 *)(slot + 0x50) - *(f32 *)(slot + 0x38);
    dx = *(f32 *)(slot + 0x00) - *(f32 *)(slot + 0x0C);
    dz = *(f32 *)(slot + 0x08) - *(f32 *)(slot + 0x14);
    len = dolsqrtf2(dx * dx + dz * dz);
    if (len < *(f32 *)(slot + 0x38)) {
        *(f32 *)(slot + 0x50) = -1.0f;
    }
    if (*(f32 *)(slot + 0x38) > 0.0f) {
        if (slot[0xBA] != 4 && slot[0xBA] != 0x18 && *(f32 *)(slot + 0x50) > 0.0f) {
            *(f32 *)(slot + 0x4C) = atan2(-(*(f32 *)(slot + 0x0C) - *(f32 *)(slot + 0x00)),
                                         -(*(f32 *)(slot + 0x14) - *(f32 *)(slot + 0x08)));
        }
        v.x = 0.0f;
        v.y = 0.0f;
        v.z = -*(f32 *)(slot + 0x38);
        PSMTXRotRad(mtx, 'Y', *(f32 *)(slot + 0x34));
        PSMTXMultVec(mtx, &v, &v);
        *(f32 *)(slot + 0x18) = v.x;
        *(f32 *)(slot + 0x20) = v.z;
        *(f32 *)(slot + 0x00) = *(f32 *)(slot + 0x00) + *(f32 *)(slot + 0x18);
        *(f32 *)(slot + 0x08) = *(f32 *)(slot + 0x08) + *(f32 *)(slot + 0x20);
        if (slot[0xBA] != 4 && slot[0xBA] != 0x18 && *(f32 *)(slot + 0x50) > 0.0f) {
            *(f32 *)(slot + 0x4C) = atan2(-(*(f32 *)(slot + 0x0C) - *(f32 *)(slot + 0x00)),
                                         -(*(f32 *)(slot + 0x14) - *(f32 *)(slot + 0x08)));
            r = fn_2_4A18C(*(f32 *)(slot + 0x34) - *(f32 *)(slot + 0x4C));
            a = fabs(r);
            if (a > 2.268928f) {
                step = 1.5707964f;
            } else if (a > 1.5707964f) {
                step = 0.6981317f;
            } else if (a > 0.6981317f) {
                step = 0.3490659f;
            } else if (a > 0.3490659f) {
                step = 0.1745329f;
            } else if (a > 0.1745329f) {
                step = 0.0872665f;
            } else if (a > 0.0872665f) {
                step = 0.0349066f;
            } else if (a > 0.0349066f) {
                step = 0.0174533f;
            } else if (a > 0.0174533f) {
                step = 0.0087266f;
            } else {
                step = 0.0034907f;
            }
            if (r >= 0.02 || r == 0.0) {
                *(f32 *)(slot + 0x34) = *(f32 *)(slot + 0x34) - step;
            } else if (r <= -0.02) {
                *(f32 *)(slot + 0x34) = *(f32 *)(slot + 0x34) + step;
            }
            *(f32 *)(slot + 0x4C) = *(f32 *)(slot + 0x34);
        }
    }
    if (*(f32 *)(slot + 0x38) == 0.0f && slot[0xBD] == 0) {
        slot[0xBC] = 1;
    }
}

// .text:0x000699D4 size:0x448 mapped:0x806A8A68
void fn_2_699D4(s32 idx) {
    u8 *slot = REP_SLOT(idx);
    Mtx mtx;
    Vec v;
    f32 r;
    f32 a;
    f32 step;
    f32 dx;
    f32 dz;
    f32 len;
    if (*(f32 *)(slot + 0x38) <= 0.0f) {
        *(f32 *)(slot + 0x38) = 0.0f;
    }
    *(f32 *)(slot + 0x50) = *(f32 *)(slot + 0x50) - *(f32 *)(slot + 0x38);
    dx = *(f32 *)(slot + 0x00) - *(f32 *)(slot + 0x0C);
    dz = *(f32 *)(slot + 0x08) - *(f32 *)(slot + 0x14);
    len = dolsqrtf2(dx * dx + dz * dz);
    if (len < *(f32 *)(slot + 0x38)) {
        *(f32 *)(slot + 0x50) = -1.0f;
    }
    if (slot[0xBA] != 4 && slot[0xBA] != 0x18 && *(f32 *)(slot + 0x50) > 0.0f) {
        *(f32 *)(slot + 0x4C) = atan2(-(*(f32 *)(slot + 0x0C) - *(f32 *)(slot + 0x00)),
                                     -(*(f32 *)(slot + 0x14) - *(f32 *)(slot + 0x08)));
    }
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = 0.0f;
    PSMTXRotRad(mtx, 'Y', *(f32 *)(slot + 0x34));
    PSMTXMultVec(mtx, &v, &v);
    *(f32 *)(slot + 0x18) = v.x;
    *(f32 *)(slot + 0x20) = v.z;
    *(f32 *)(slot + 0x00) = *(f32 *)(slot + 0x00) + *(f32 *)(slot + 0x18);
    *(f32 *)(slot + 0x08) = *(f32 *)(slot + 0x08) + *(f32 *)(slot + 0x20);
    if (slot[0xBA] != 4 && slot[0xBA] != 0x18 && *(f32 *)(slot + 0x50) > 0.0f) {
        *(f32 *)(slot + 0x4C) = atan2(-(*(f32 *)(slot + 0x0C) - *(f32 *)(slot + 0x00)),
                                     -(*(f32 *)(slot + 0x14) - *(f32 *)(slot + 0x08)));
        r = fn_2_4A18C(*(f32 *)(slot + 0x34) - *(f32 *)(slot + 0x4C));
        a = fabs(r);
        if (a > 2.268928f) {
            step = 1.5707964f;
        } else if (a > 1.5707964f) {
            step = 0.6981317f;
        } else if (a > 0.6981317f) {
            step = 0.3490659f;
        } else if (a > 0.3490659f) {
            step = 0.1745329f;
        } else if (a > 0.1745329f) {
            step = 0.0872665f;
        } else if (a > 0.0872665f) {
            step = 0.0349066f;
        } else if (a > 0.0349066f) {
            step = 0.0174533f;
        } else if (a > 0.0174533f) {
            step = 0.0087266f;
        } else {
            step = 0.0034907f;
        }
        if (r >= 0.02 || r == 0.0) {
            *(f32 *)(slot + 0x34) = *(f32 *)(slot + 0x34) - step;
        } else if (r <= -0.02) {
            *(f32 *)(slot + 0x34) = *(f32 *)(slot + 0x34) + step;
        }
        *(f32 *)(slot + 0x4C) = *(f32 *)(slot + 0x34);
    }
    if (*(f32 *)(slot + 0x38) == 0.0f && slot[0xBD] == 0) {
        slot[0xBC] = 1;
    }
}

// .text:0x000698EC size:0xE8 mapped:0x806A8980
void fn_2_698EC(s32 idx, f32 angle) {
    u8 *slot = REP_SLOT(idx);
    if (slot[0xD0] != 0) {
        f32 old = *(f32 *)(slot + 0x90);
        f32 out = 1.6f * -(f32)sin(old);
        *(f32 *)(slot + 0x90) = old + 0.07f;
        if (*(f32 *)(slot + 0x4) > angle) {
            *(f32 *)(slot + 0x90) = 0.0f;
            out = 0.0f;
            slot[0xD0] = 0;
            if (slot[0xC3] == 0x13) {
                lbl_2_bss_1A8248[idx * 0xD8 + 0x16D0] = 0;
            }
        }
        *(f32 *)(slot + 0x4) = out;
    } else {
        *(f32 *)(slot + 0x4) = 0.0f;
    }
}

// .text:0x00069710 size:0x1DC mapped:0x806A87A4
void fn_2_69710(s32 idx) {
    u8 *slot = REP_SLOT(idx);
    if (*(s16 *)(slot + 0x9C) == 0) {
        s16 a1 = fn_2_4A2C4(*(f32 *)(slot + 0x4C));
        s16 a2 = fn_2_4A2C4(*(f32 *)(slot + 0x30));
        s16 d = fn_2_4A150((s16)(a1 - a2));
        if (d < 0x200) {
            slot[0xBE] = 0;
        } else if (d < 0x600) {
            slot[0xBE] = 3;
        } else if (d < 0xA00) {
            slot[0xBE] = 1;
        } else if (d < 0xE00) {
            slot[0xBE] = 2;
        } else {
            slot[0xBE] = 0;
        }
        if (slot[0xBC] != 1) {
            if (slot[0xBE] == 1) {
                slot[0xBE] = 5;
            } else {
                slot[0xBE] = 4;
            }
        }
    }
    if (slot[0xBE] == 4 || slot[0xBE] == 5) {
        *(f32 *)(slot + 0x38) = 0.5f * *(f32 *)(slot + 0x44) + *(f32 *)(slot + 0x38);
    } else {
        *(f32 *)(slot + 0x38) = *(f32 *)(slot + 0x38) + *(f32 *)(slot + 0x44);
    }
    if (slot[0xC1] == 0 && slot[0xC2] != 0 && *(s16 *)(slot + 0xA0) == 0) {
        *(s16 *)(slot + 0xA0) = 30;
    }
    if (slot[0xC1] != 0) {
        if (*(f32 *)(slot + 0x38) > *(f32 *)(slot + 0x40)) {
            *(f32 *)(slot + 0x38) = *(f32 *)(slot + 0x40);
        }
        *(s16 *)(slot + 0xA0) = 0;
    } else if (*(s16 *)(slot + 0xA0) != 0) {
        if (*(f32 *)(slot + 0x38) >= *(f32 *)(slot + 0x40)) {
            *(s16 *)(slot + 0xA0) = 0;
        } else {
            *(f32 *)(slot + 0x38) = *(f32 *)(slot + 0x40);
        }
    } else {
        if (*(f32 *)(slot + 0x38) > 0.12f) {
            *(f32 *)(slot + 0x38) = 0.12f;
        }
    }
}

// .text:0x000696D4 size:0x3C mapped:0x806A8768
void fn_2_696D4(s32 idx) {
    u8 *slot = REP_SLOT(idx);
    if (*(s16 *)(slot + 0xA0) != 0) {
        *(f32 *)(slot + 0x38) = *(f32 *)(slot + 0x3C);
    } else {
        *(f32 *)(slot + 0x38) = 0.0f;
    }
}

// .text:0x00069554 size:0x180 mapped:0x806A85E8
s32 fn_2_69554(s32 idx, f32 x, f32 z) {
    u8 *slot = REP_SLOT(idx);
    f32 dx;
    f32 dz;
    f32 div;
    f32 t;
    if (x == *(f32 *)(slot + 0x00) && z == *(f32 *)(slot + 0x08)) {
        return 1;
    }
    dx = x - *(f32 *)(slot + 0x00);
    dz = z - *(f32 *)(slot + 0x08);
    t = dolsqrtf2(dx * dx + dz * dz);
    div = *(f32 *)(slot + 0x40);
    if (div == 0.0f) {
        div = 1.0f;
    }
    return (slot[0xB7] >> 1) + (s32)(t / div);
}

// .text:0x000692D0 size:0x284 mapped:0x806A8364
void fn_2_692D0(s32 idx, s32 n, f32 x, f32 z, f32 *outX, f32 *outZ, f32 *outT) {
    u8 *slot = REP_SLOT(idx);
    f32 t = 0.0f;
    f32 acc = *(f32 *)(slot + 0x38);
    f32 len;
    f32 nx;
    f32 nz;
    s16 ang;
    s32 cnt;
    s32 i;
    if (x == 0.0f && z == 0.0f) {
        *outX = *(f32 *)(slot + 0x00);
        *outZ = *(f32 *)(slot + 0x08);
        *outT = 0.0f;
        return;
    }
    len = dolsqrtf2(x * x + z * z);
    nx = x / len;
    nz = z / len;
    ang = fn_2_4A234(nx, nz);
    if (*(f32 *)(slot + 0x38) >= 0.05f && *(s16 *)(slot + 0x9A) >= 0 &&
        fn_2_4A310(ang, *(s16 *)(slot + 0x9A)) > 0x2A8) {
        acc = 0.0f;
    }
    cnt = slot[0xB7];
    for (i = 0; i <= cnt; i++) {
        acc += *(f32 *)(slot + 0x44);
        if (acc > *(f32 *)(slot + 0x40)) {
            t += *(f32 *)(slot + 0x40);
            break;
        }
        t += acc;
    }
    t += *(f32 *)(slot + 0x40) * (f32)(n - (i + 1));
    *outT = t;
    *outX = nx * t + *(f32 *)(slot + 0x00);
    *outZ = nz * t + *(f32 *)(slot + 0x08);
}

// .text:0x00069070 size:0x260 mapped:0x806A8104
f32 fn_2_69070(s32 idx, f32 x, f32 z) {
    u8 *slot = REP_SLOT(idx);
    f32 dx;
    f32 dz;
    f32 proj;
    f32 disc;
    if (*(f32 *)(slot + 0x38) < 0.01f) {
        dx = *(f32 *)(slot + 0x00) - x;
        dz = *(f32 *)(slot + 0x08) - z;
        {
            f32 squaredX = dx * dx;
            f32 squaredZ = dz * dz;
            return dolsqrtf2(squaredX + squaredZ);
        }
    }
    dz = z - *(f32 *)(slot + 0x08);
    dx = x - *(f32 *)(slot + 0x00);
    proj = *(f32 *)(slot + 0x24) * dx + *(f32 *)(slot + 0x2C) * dz;
    disc = dx * dx + dz * dz - proj * proj;
    if (disc < 0.0f) {
        return 0.0f;
    }
    return dolsqrtf2(disc);
}

// .text:0x00068FBC size:0xB4 mapped:0x806A8050
void fn_2_68FBC(s32 idx, s32 val) {
    u8 *slot = REP_SLOT(idx);
    s32 n = *(s32 *)(slot + 0x80);
    if (*(s16 *)(lbl_2_bss_1A824C + 0x190000 + 0x7756 + n * 2) != val) {
        u8 *ent = lbl_2_data_3C84 + val * 6;
        fn_2_8CD58(n, *(s16 *)(ent + 0x0), ent[0x4], 1, *(s16 *)(ent + 0x2), 0, 0);
        *(s16 *)(lbl_2_bss_1A824C + 0x190000 + 0x7756 + n * 2) = val;
    }
}

// .text:0x00068F24 size:0x98 mapped:0x806A7FB8
void fn_2_68F24(s32 idx, s32 val) {
    u8 *slot = REP_SLOT(idx);
    u8 *ent = lbl_2_data_3C84 + val * 6;
    fn_2_8CD58(*(s32 *)(slot + 0x80), *(s16 *)(ent + 0x0), ent[0x4], 1,
               *(s16 *)(ent + 0x2), 0, 0);
    *(s16 *)(lbl_2_bss_1A824C + 0x190000 + 0x7756 + *(s32 *)(slot + 0x80) * 2) = val;
}

// .text:0x00068F08 size:0x1C mapped:0x806A7F9C
void fn_2_68F08(s32 idx, u8 val) {
    lbl_2_bss_1A8248[idx * 0xD8 + 0x16D0] = val;
}

// .text:0x00068E68 size:0xA0 mapped:0x806A7EFC
void fn_2_68E68(void) {
    s32 i;
    for (i = 0; i < *(s16 *)(lbl_2_bss_1A824C + 0x197746); i++) {
        u8 *slot = REP_SLOT(i);
        u8 *dst = hugeAnimStruct + i * 0x27C + 0xC04;
        memcpy(dst + 0x34, slot, 12);
        *(f32 *)(dst + 0x44) = *(f32 *)(slot + 0x4C);
        dst[0x25D] = slot[0xC0];
        dst[0x277] = slot[0xCA];
    }
}

// .text:0x00068DE8 size:0x80 mapped:0x806A7E7C
void fn_2_68DE8(s32 idx, void *dst) {
    if (idx != -1) {
        memcpy(dst, REP_SLOT(idx), 12);
        PSVECScale(dst, 2.0f, dst);
    } else {
        *(f32 *)((u8 *)dst + 0x8) = 0.0f;
        *(f32 *)((u8 *)dst + 0x4) = 0.0f;
        *(f32 *)((u8 *)dst + 0x0) = 0.0f;
    }
}

// .text:0x00068DAC size:0x3C mapped:0x806A7E40
void fn_2_68DAC(s32 idx, void *dst) {
    memcpy(dst, REP_SLOT(idx), 12);
}

// .text:0x00068D90 size:0x1C mapped:0x806A7E24
void fn_2_68D90(s32 idx, u8 val) {
    lbl_2_bss_1A8248[idx * 0xD8 + 0x16DA] = val;
}

// .text:0x00068C80 size:0x110 mapped:0x806A7D14
BOOL fn_2_68C80(s32 idxA, s32 idxB) {
    u8 *a = REP_SLOT(idxA);
    u8 *b = REP_SLOT(idxB);
    u8 kind = lbl_2_bss_1A8248[0x441C];
    f32 dist = PSVECDistance((Vec *)a, (Vec *)b);
    f32 limit;
    if (idxA == 0) {
        limit = lbl_2_data_3EF4[kind] + lbl_2_data_3F0C[idxB];
    } else {
        limit = lbl_2_data_3F0C[idxA] + lbl_2_data_3EF4[kind];
    }
    if (dist < limit && a[0xC0] != 0 && b[0xC0] != 0) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x00068B54 size:0x12C mapped:0x806A7BE8
BOOL fn_2_68B54(s32 idxA, s32 idxB) {
    u8 *a = REP_SLOT(idxA);
    u8 *b = REP_SLOT(idxB);
    u8 kind = lbl_2_bss_1A8248[0x441C];
    f32 dist = PSVECDistance((Vec *)a, (Vec *)b);
    f32 limit;
    if (idxA == 0) {
        limit = (lbl_2_data_3EF4[kind] + lbl_2_data_3F2C[kind]) + lbl_2_data_3F0C[idxB];
    } else {
        limit = (lbl_2_data_3EF4[kind] + lbl_2_data_3F2C[kind]) + lbl_2_data_3F0C[idxA];
    }
    if (dist < limit && a[0xC0] != 0 && b[0xC0] != 0) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x00068A88 size:0xCC mapped:0x806A7B1C
BOOL fn_2_68A88(s32 idx, s32 which) {
    u8 *slot = REP_SLOT(idx);
    f32 *rec = (f32 *)(lbl_2_bss_1A8248 + 0x21E0 + which * 0xBC);
    f32 tmp[3];
    f32 dist;
    f32 limit;
    tmp[0] = rec[0] * 0.5f;
    tmp[1] = rec[1] * 0.5f;
    tmp[2] = rec[2] * 0.5f;
    dist = PSVECDistance((Vec *)slot, (Vec *)tmp);
    limit = lbl_2_data_3EF4[lbl_2_bss_1A8248[0x441C]] + lbl_2_data_3F5C;
    if (dist < limit && slot[0xC0] != 0) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x000689CC size:0xBC mapped:0x806A7A60
s16 fn_2_689CC(s32 idx) {
    Vec a;
    Vec b;
    f32 best = 10000.0f;
    s32 bestIdx = 0;
    s32 i;
    memcpy(&a, REP_SLOT(idx), 12);
    for (i = 0; i < 0x33; i++) {
        f32 dist;
        memcpy(&b, lbl_2_data_2EA4 + i * 0xC, 12);
        dist = PSVECDistance(&a, &b);
        if (dist < best) {
            best = dist;
            bestIdx = i;
        }
    }
    return (s16)bestIdx;
}

// .text:0x00068940 size:0x8C mapped:0x806A79D4
f32 fn_2_68940(s32 idxA, s32 idxB) {
    u8 *a = REP_SLOT(idxA);
    u8 *b = REP_SLOT(idxB);
    return fn_2_4A18C(*(f32 *)(a + 0x4C)) -
           (f32)atan2(-(*(f32 *)(b + 0x00) - *(f32 *)(a + 0x00)),
                      -(*(f32 *)(b + 0x08) - *(f32 *)(a + 0x08)));
}

// .text:0x000688A4 size:0x9C mapped:0x806A7938
f32 fn_2_688A4(s32 idx, s32 which) {
    f32 tmp[3];
    u8 *a = REP_SLOT(idx);
    memcpy(tmp, lbl_2_data_2EA4 + which * 0xC, 12);
    return fn_2_4A18C(*(f32 *)(a + 0x4C)) -
           (f32)atan2(-(tmp[0] - *(f32 *)(a + 0x00)),
                      -(tmp[2] - *(f32 *)(a + 0x08)));
}

// .text:0x000687A4 size:0x100 mapped:0x806A7838
BOOL fn_2_687A4(s32 idxA, s32 idxB, s32 which) {
    u8 *a = REP_SLOT(idxA);
    u8 *b = REP_SLOT(idxB);
    f32 tmp[3];
    f32 angleB;
    f32 angleTmp;
    f32 diff;
    angleB = (f32)atan2(-(*(f32 *)(b + 0x00) - *(f32 *)(a + 0x00)),
                        -(*(f32 *)(b + 0x08) - *(f32 *)(a + 0x08)));
    memcpy(tmp, lbl_2_data_2EA4 + which * 0xC, 12);
    angleTmp = (f32)atan2(-(tmp[0] - *(f32 *)(a + 0x00)),
                          -(tmp[2] - *(f32 *)(a + 0x08)));
    diff = angleB - angleTmp;
    if (diff < 1.2217305898666382f && diff > -1.2217305898666382f) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x000686EC size:0xB8 mapped:0x806A7780
BOOL fn_2_686EC(s32 idxA, s32 idxB) {
    u8 *a = REP_SLOT(idxA);
    u8 *b = REP_SLOT(idxB);
    f32 diff;
    diff = fn_2_4A18C(*(f32 *)(a + 0x4C)) -
           (f32)atan2(-(*(f32 *)(b + 0x00) - *(f32 *)(a + 0x00)),
                      -(*(f32 *)(b + 0x08) - *(f32 *)(a + 0x08)));
    if (diff < 1.2217305898666382f && diff > -1.2217305898666382f) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x000686D0 size:0x1C mapped:0x806A7764
void fn_2_686D0(s32 idx, u8 val) {
    lbl_2_bss_1A8248[idx * 0xD8 + 0x16DF] = val;
}

// .text:0x000686B0 size:0x20 mapped:0x806A7744
s8 fn_2_686B0(s32 idx) {
    return (s8)lbl_2_bss_1A8248[idx * 0xD8 + 0x16DB];
}

// .text:0x00068690 size:0x20 mapped:0x806A7724
s8 fn_2_68690(s32 idx) {
    return (s8)lbl_2_bss_1A8248[idx * 0xD8 + 0x16DC];
}

// .text:0x00068670 size:0x20 mapped:0x806A7704
s8 fn_2_68670(s32 idx) {
    return (s8)lbl_2_bss_1A8248[idx * 0xD8 + 0x16DD];
}

// .text:0x00068654 size:0x1C mapped:0x806A76E8
void fn_2_68654(s32 idx, u8 val) {
    lbl_2_bss_1A8248[idx * 0xD8 + 0x16DD] = val;
}

// .text:0x00068638 size:0x1C mapped:0x806A76CC
void fn_2_68638(s32 idx, u8 val) {
    lbl_2_bss_1A8248[idx * 0xD8 + 0x16DE] = val;
}

// .text:0x000684D0 size:0x168 mapped:0x806A7564
s8 fn_2_684D0(s32 idx) {
    u8 *a = REP_SLOT(idx);
    s32 k;
    a[0xCC] = 0xFF;
    for (k = 1; k < 7; k++) {
        u8 *b = REP_SLOT(k);
        u8 kind = lbl_2_bss_1A8248[0x441C];
        f32 dist = PSVECDistance((Vec *)a, (Vec *)b);
        f32 limit;
        if (idx == 0) {
            limit = lbl_2_data_3F0C[k] + (lbl_2_data_3EF4[kind] + lbl_2_data_3F2C[kind]);
        } else {
            limit = lbl_2_data_3F0C[idx] + (lbl_2_data_3EF4[kind] + lbl_2_data_3F2C[kind]);
        }
        if (dist < limit && a[0xC0] != 0 && b[0xC0] != 0) {
            if (k >= 2 && k <= 6) {
                a[0xCC] = k;
                return (s8)a[0xCC];
            }
        }
        a[0xCC] = 0xFF;
    }
    return (s8)a[0xCC];
}

// .text:0x000683EC size:0xE4 mapped:0x806A7480
void fn_2_683EC(void) {
    u8 *s1 = lbl_2_bss_1A8248 + 0x16E8;
    *(f32 *)(s1 + 0x00) = *(f32 *)(lbl_2_bss_1A8248 + 0x1610);
    *(f32 *)(s1 + 0x04) = *(f32 *)(lbl_2_bss_1A8248 + 0x1614);
    *(f32 *)(s1 + 0x08) = *(f32 *)(lbl_2_bss_1A8248 + 0x1618);
    memcpy(s1, lbl_2_data_2EA4 + *(s16 *)(lbl_2_bss_1A8248 + 0x16C2) * 0xC, 12);
    *(f32 *)(s1 + 0x0C) = 0.0f;
    *(f32 *)(s1 + 0x10) = 0.0f;
    *(f32 *)(s1 + 0x14) = 0.0f;
    *(f32 *)(s1 + 0x18) = 0.0f;
    *(f32 *)(s1 + 0x1C) = 0.0f;
    *(f32 *)(s1 + 0x20) = 0.0f;
    *(f32 *)(s1 + 0x6C) = *(f32 *)(s1 + 0x00);
    *(f32 *)(s1 + 0x70) = *(f32 *)(s1 + 0x08);
    *(f32 *)(s1 + 0x38) = 0.0f;
    s1[0xBB] = 0;
    {
        f32 v = *(f32 *)(s1 + 0x4C);
        *(f32 *)(s1 + 0x34) = v;
        *(f32 *)(s1 + 0x30) = v;
    }
    *(s16 *)(lbl_2_bss_1A8248 + 0x179A) = *(s16 *)(lbl_2_bss_1A8248 + 0x16C2);
    lbl_2_bss_1A8248[0x17AB] = 6;
    *(s16 *)(lbl_2_bss_1A8248 + 0x177C) = 0;
    lbl_2_bss_1A8248[0x442F] = 1;
}

// .text:0x0006832C size:0xC0 mapped:0x806A73C0
void fn_2_6832C(void) {
    u8 *slot = lbl_2_bss_1A8248 + 0x16E8;
    memcpy(slot, lbl_2_data_2EA4 + 0x3C, 12);
    *(f32 *)(slot + 0x0C) = 0.0f;
    *(f32 *)(slot + 0x10) = 0.0f;
    *(f32 *)(slot + 0x14) = 0.0f;
    *(f32 *)(slot + 0x18) = 0.0f;
    *(f32 *)(slot + 0x1C) = 0.0f;
    *(f32 *)(slot + 0x20) = 0.0f;
    *(f32 *)(slot + 0x6C) = *(f32 *)(slot + 0x00);
    *(f32 *)(slot + 0x70) = *(f32 *)(slot + 0x08);
    *(f32 *)(slot + 0x38) = 0.0f;
    slot[0xBB] = 0;
    {
        f32 v = *(f32 *)(slot + 0x4C);
        *(f32 *)(slot + 0x34) = v;
        *(f32 *)(slot + 0x30) = v;
    }
    *(s16 *)(lbl_2_bss_1A8248 + 0x179A) = 5;
    lbl_2_bss_1A8248[0x17AB] = 6;
    *(s16 *)(lbl_2_bss_1A8248 + 0x177C) = 0;
    lbl_2_bss_1A8248[0x442F] = 1;
}
