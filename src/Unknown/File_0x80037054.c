#include <string.h>
#include <math.h>
#include "mssbTypes.h"
#include "HugeAnimStruct.h"
#include "Dolphin/mtx.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x8001b80c.h"
#include "Unknown/File_0x8004b7f4.h"

// .text 0x80037054-0x80039AA8: one translation unit by its literal pool (docs/splits.md,
// 2026-11-20). The rope / chain simulation attached to hugeAnimStruct objects:
// 0x40-byte nodes (mass, 1/mass, position, previous position, velocity, pinned flag)
// and the hand-track follower task. Raw offsets are used for the simulation records.
// fn_80037054, fn_8003731C, fn_80037768, fn_80037BAC, fn_8003819C, fn_800387B0,
// fn_80038F08 and fn_80039310 have no C yet; they link from the original asm.

extern u8 lbl_800F79A0[];
extern u8 lbl_800F79B8[];
extern s16 lbl_803CB818;
extern s32 lbl_803CB820;
extern u8 lbl_803CBCA1;
extern u8 lbl_803CBCA2;

s32 fn_8003731C(void* obj, s32* params);
void fn_8003819C(void* obj);
void fn_80038418(void* obj, f32* pos, Quaternion* orient, f32* outPos, Quaternion* outQuat);
void fn_80038F08(void* actors, void* node, u8 slot);
void fn_80039310(void* state, f32 a, f32 b);
extern f32 lbl_803CB81C;
extern f32 lbl_803CB824;
extern u8 lbl_803CBCA0;

#define RF32(p, off) (*(f32*)((u8*)(p) + (off)))
#define RU32(p, off) (*(u32*)((u8*)(p) + (off)))

void fn_80037964(void) {
    removeCurrentDrawingItem();
}

s32 fn_80037054(void* obj, void* ctx) {
    u8 state[0x154];
    Quaternion q;
    Vec a;
    Vec b;
    Vec h;
    f32 timeLeft;
    f32 maxSpin;
    f32 mag;

    RF32(obj, 0x150) = RF32(obj, 0x48);
    memcpy(state, obj, 0x154);
    timeLeft = 1.0f / 60.0f;
    do {
        fn_8003731C(state, (s32*)ctx);
        PSVECScale((Vec*)(state + 0x104), RF32(state, 0x28) * RF32(state, 0x150), &a);
        PSVECAdd((Vec*)(state + 0x11C), &a, (Vec*)(state + 0x11C));
        PSVECScale((Vec*)(state + 0x11C), RF32(state, 0x150), &b);
        PSVECAdd((Vec*)(state + 0xE8), &b, (Vec*)(state + 0xE8));
        maxSpin = (f32)*(s32*)((u8*)ctx + 0x1C) / 100000.0f;
        h.x = RF32(state, 0x30) * RF32(state, 0x140);
        h.y = RF32(state, 0x34) * RF32(state, 0x144);
        h.z = RF32(state, 0x38) * RF32(state, 0x148);
        PSVECCrossProduct((Vec*)(state + 0x140), &h, &h);
        PSVECSubtract((Vec*)(state + 0x134), &h, &h);
        h.x = RF32(state, 0x3C) * h.x;
        h.y = RF32(state, 0x40) * h.y;
        h.z = RF32(state, 0x44) * h.z;
        PSVECScale(&h, RF32(state, 0x150), &h);
        PSVECAdd((Vec*)(state + 0x140), &h, (Vec*)(state + 0x140));
        if (maxSpin != 0.0f) {
            mag = PSVECMag((Vec*)(state + 0x140));
            if (mag > maxSpin) {
                PSVECScale((Vec*)(state + 0x140), maxSpin / mag, (Vec*)(state + 0x140));
            }
        }
        memcpy(&q, state + 0x140, 12);
        q.w = 0.0f;
        PSQUATMultiply((Quaternion*)(state + 0xF4), &q, &q);
        PSQUATScale(&q, 0.5f * RF32(state, 0x150), &q);
        PSQUATAdd((Quaternion*)(state + 0xF4), &q, (Quaternion*)(state + 0xF4));
        PSMTXQuat((f32(*)[4])(state + 0x88), (Quaternion*)(state + 0xF4));
        PSMTXInverse((f32(*)[4])(state + 0x88), (f32(*)[4])(state + 0xB8));
        PSMTXTransApply((f32(*)[4])(state + 0x88), (f32(*)[4])(state + 0x58), RF32(state, 0xE8), RF32(state, 0xEC), RF32(state, 0xF0));
        PSMTXMultVec((f32(*)[4])(state + 0xB8), (Vec*)(state + 0x11C), (Vec*)(state + 0x128));
        timeLeft -= RF32(state, 0x150);
    } while (timeLeft > 0.0f);
    memcpy(obj, state, 0x154);
    return 0;
}

s32 fn_8003731C(void* obj, s32* params) {
    Vec saved;
    Vec a;
    Vec w;
    Vec c;
    Vec t;
    Vec sv;
    Vec p[3];
    Vec q[3];
    f32 k0 = params[0] / 100000.0f;
    f32 k1 = params[1] / 100000.0f;
    f32 k3 = params[3] / 100000.0f;
    f32 k4 = params[4] / 100000.0f;
    f32 k5 = params[5] / 100000.0f;
    f32 k6 = params[6] / 100000.0f;
    f32 k8 = params[8] / 100000.0f;
    f32 ty;
    s32 k;

    memcpy(&saved, (u8*)obj + 0x104, 12);
    memset((u8*)obj + 0x104, 0, 12);
    memset((u8*)obj + 0x110, 0, 12);
    memset((u8*)obj + 0x134, 0, 12);
    a.z = 0.0f;
    a.x = 0.0f;
    a.y = -RF32(obj, 0x2C);
    PSMTXMultVec((f32(*)[4])((u8*)obj + 0xB8), &a, &a);
    PSVECScale((Vec*)((u8*)obj + 0x11C), -RF32(obj, 0x50), &t);
    PSVECAdd((Vec*)((u8*)obj + 0x104), &t, (Vec*)((u8*)obj + 0x104));
    PSVECScale((Vec*)((u8*)obj + 0x140), -RF32(obj, 0x50), &w);
    ((f32*)&w)[((u8*)obj)[0x14E]] = 0.0f;
    PSVECAdd((Vec*)((u8*)obj + 0x134), &w, (Vec*)((u8*)obj + 0x134));

    for (k = 2; k >= 0; k--) {
        PSVECAdd(k == 1 ? (Vec*)((u8*)obj + 0xC) : (Vec*)obj, &a, &p[k]);
        PSMTXMultVec((f32(*)[4])((u8*)obj + 0x58), &p[k], &q[k]);
        memset(&t, 0, 12);
        t.y = -q[k].y;
        if (t.y < 0.0f) {
            continue;
        }
        if (k6 != 0.0f && t.y > k6) {
            t.y = k6;
        }
        PSVECCrossProduct(&p[k], (Vec*)((u8*)obj + 0x140), &c);
        PSMTXMultVec((f32(*)[4])((u8*)obj + 0x88), &c, &c);
        PSVECAdd((Vec*)((u8*)obj + 0x11C), &c, &c);
        ty = k0 * t.y + k1 * -c.y;
        t.y = ty;
        if (k3 != 0.0f && fabs(ty) > k3) {
            t.y = k3 * (ty / fabs(ty));
        } else if (fabs(ty) < k4) {
            continue;
        }
        if (k8 != 0.0f) {
            sv.x = -c.x;
            sv.y = 0.0f;
            sv.z = -c.z;
            PSVECScale(&sv, k8, &sv);
            t.x = t.x + sv.x;
            t.z = t.z + sv.z;
        }
        PSVECAdd((Vec*)((u8*)obj + 0x104), &t, (Vec*)((u8*)obj + 0x104));
        PSMTXMultVec((f32(*)[4])((u8*)obj + 0xB8), &t, &t);
        PSVECCrossProduct(&p[k], &t, &w);
        PSVECAdd((Vec*)((u8*)obj + 0x134), &w, (Vec*)((u8*)obj + 0x134));
    }

    t.x = 0.0f;
    t.z = 0.0f;
    t.y = -9.80665f * RF32(obj, 0x24);
    PSVECAdd((Vec*)((u8*)obj + 0x104), &t, (Vec*)((u8*)obj + 0x104));
    if (PSVECMag((Vec*)((u8*)obj + 0x134)) < k5) {
        memset((u8*)obj + 0x134, 0, 12);
    }
    return 0;
}

void fn_80037768(void* obj, u8 mode, s32 substeps, f32 a, f32 b, f32 c, f32 d) {
    RF32(obj, 0xC) = 0.0f;
    RF32(obj, 0x10) = 0.0f;
    RF32(obj, 0x14) = 0.0f;
    ((u8*)obj)[0x14E] = mode;
    RF32(obj, 0xC + mode * 4) = -a * b;
    RF32(obj, 0x0) = 0.0f;
    RF32(obj, 0x4) = 0.0f;
    RF32(obj, 0x8) = 0.0f;
    RF32(obj, mode * 4) = a + RF32(obj, 0xC + mode * 4);
    PSVECSubtract((Vec*)obj, (Vec*)((u8*)obj + 0xC), (Vec*)((u8*)obj + 0x18));
    RF32(obj, 0x24) = d;
    RF32(obj, 0x28) = 1.0f / d;
    RF32(obj, 0x2C) = c;
    RF32(obj, 0x38) = d * (a * a / 12.0f + c * c * 0.25f);
    RF32(obj, 0x34) = RF32(obj, 0x38);
    RF32(obj, 0x30) = RF32(obj, 0x38);
    RF32(obj, 0x30 + mode * 4) = c * (d * c) * 0.5f;
    RF32(obj, 0x3C) = 1.0f / RF32(obj, 0x30);
    RF32(obj, 0x40) = 1.0f / RF32(obj, 0x34);
    RF32(obj, 0x44) = 1.0f / RF32(obj, 0x38);
    RU32(obj, 0x4C) = substeps;
    RF32(obj, 0x48) = (1.0f / 60.0f) / (f32)(s32)RU32(obj, 0x4C);
    RF32(obj, 0x50) = 0.0f;
    RF32(obj, 0x54) = 0.5f;
    PSMTXIdentity((f32(*)[4])((u8*)obj + 0x88));
    PSMTXIdentity((f32(*)[4])((u8*)obj + 0xB8));
    PSMTXIdentity((f32(*)[4])((u8*)obj + 0x58));
    RF32(obj, 0xF0) = 0.0f;
    RF32(obj, 0xEC) = 0.0f;
    RF32(obj, 0xE8) = 0.0f;
    RF32(obj, 0xFC) = 0.0f;
    RF32(obj, 0xF8) = 0.0f;
    RF32(obj, 0xF4) = 0.0f;
    RF32(obj, 0x100) = 1.0f;
    RF32(obj, 0x118) = 0.0f;
    RF32(obj, 0x114) = 0.0f;
    RF32(obj, 0x110) = 0.0f;
    RF32(obj, 0x124) = 0.0f;
    RF32(obj, 0x120) = 0.0f;
    RF32(obj, 0x11C) = 0.0f;
    RF32(obj, 0x130) = 0.0f;
    RF32(obj, 0x12C) = 0.0f;
    RF32(obj, 0x128) = 0.0f;
    RF32(obj, 0x13C) = 0.0f;
    RF32(obj, 0x138) = 0.0f;
    RF32(obj, 0x134) = 0.0f;
    RF32(obj, 0x148) = 0.0f;
    RF32(obj, 0x144) = 0.0f;
    RF32(obj, 0x140) = 0.0f;
    ((u8*)obj)[0x14D] = 0;
    ((u8*)obj)[0x14C] = 0;
}

void fn_80037984(void) {
    DrawingSceneStruct* item = currentDrawingItem;
    u8* obj;
    u8* node;
    u32 index;
    Mtx mtx;
    Quaternion quat;
    Vec pos;

    obj = (u8*)hugeAnimStruct.objects[((u8*)item)[0x3E]];
    node = (u8*)*(u32*)((u8*)hugeAnimStruct.actorTables[0] + (s8)obj[0x255] * 0x90 + 0x34);
    if (obj != NULL) {
        index = *(u16*)(obj + 0x162 + *(u16*)((u8*)item + 0x3C) * 2);
    } else {
        index = 0xFFFF;
    }
    PSMTXCopy((f32(*)[4])*(u32*)(*(u32*)(*(u32*)(node + 0x18) + (u16)index * 4) + 0xEC), mtx);
    mtx[0][3] = 0.0f;
    mtx[1][3] = 0.0f;
    mtx[2][3] = 0.0f;
    C_QUATMtx(&quat, mtx);
    getAnimRelatedCoordinates(((u8*)item)[0x3E], *(u16*)((u8*)item + 0x3C), (struct _VecXYZ*)&pos);
    if (getHandTrackFlags((void*)RU32(item, 0x1C)) & 0x10000000) {
        fn_80038418((void*)RU32(item, 0x18), &pos.x, &quat, (f32*)((u8*)item + 0x20), (Quaternion*)((u8*)item + 0x2C));
        currentDrawingItem->func = fn_80037964;
    } else {
        memcpy((u8*)item + 0x20, &pos, 12);
        memcpy((u8*)item + 0x2C, &quat, 16);
    }
}

void fn_80037AA0(void* a, int index, void* b, u16 c, void* d) {
    DrawingSceneStruct* item;

    if (hugeAnimStruct.objects[index] != NULL) {
        item = insertGraphicDrawingFunction(fn_80037984, 0x6001);
        RU32(item, 0x18) = (u32)a;
        ((u8*)item)[0x3E] = index;
        *(u16*)((u8*)item + 0x3C) = c;
        RU32(item, 0x1C) = (u32)d;
        RU32(item, 0x14) = (u32)b;
    }
}

void fn_80037B18(void* obj, Mtx mtx) {
    Vec cross;
    Vec v;
    Vec w;

    PSVECScale((Vec*)((u8*)obj + 0x18), 1.0f, &v);
    PSVECAdd(&v, (Vec*)((u8*)obj + 0xC), &v);
    PSMTXMultVec(mtx, (Vec*)((u8*)obj + 0xB8), &w);
    PSVECAdd((Vec*)((u8*)obj + 0x110), &w, (Vec*)((u8*)obj + 0x110));
    PSVECCrossProduct(&v, &w, &cross);
    PSVECAdd((Vec*)((u8*)obj + 0x134), &cross, (Vec*)((u8*)obj + 0x134));
}

s32 fn_80037BAC(void* objArg) {
    u8* obj = (u8*)objArg;
    u8 st[0x150];
    Quaternion q;
    Vec t;
    Vec h;
    Vec c1;
    Vec c2;
    Vec n;
    Vec cp;
    Vec pv;
    Vec P0;
    Vec P1;
    Vec* pt[2];
    s32 flag[2];
    f32 timeLeft = RF32(obj, 0x48);
    f32 dt;
    f32 lim;
    f32 denom;
    s32 j;

    memcpy(st, obj, 0x150);
    pt[0] = (Vec*)(st + 0xC);
    pt[1] = (Vec*)st;
    PSMTXMultVec((f32(*)[4])(st + 0x58), (Vec*)(st + 0xC), &P1);
    PSMTXMultVec((f32(*)[4])(st + 0x58), (Vec*)st, &P0);
    dt = RF32(st, 0x48);
    do {
        PSMTXMultVec((f32(*)[4])(st + 0xB8), (Vec*)(st + 0x11C), (Vec*)(st + 0x128));
        fn_8003819C(st);
        PSVECScale((Vec*)(st + 0x110), RF32(st, 0x28) * dt, &t);
        PSMTXMultVec((f32(*)[4])(st + 0x88), &t, &t);
        PSVECAdd((Vec*)(st + 0x11C), &t, (Vec*)(st + 0x11C));
        PSVECScale((Vec*)(st + 0x11C), dt, &t);
        PSVECAdd((Vec*)(st + 0xE8), &t, (Vec*)(st + 0xE8));
        h.x = RF32(st, 0x30) * RF32(st, 0x140);
        h.y = RF32(st, 0x34) * RF32(st, 0x144);
        h.z = RF32(st, 0x38) * RF32(st, 0x148);
        PSVECCrossProduct((Vec*)(st + 0x140), &h, &h);
        PSVECSubtract((Vec*)(st + 0x134), &h, &h);
        PSVECScale(&h, dt, &h);
        RF32(st, 0x140) = h.x * RF32(st, 0x3C) + RF32(st, 0x140);
        RF32(st, 0x144) = h.y * RF32(st, 0x40) + RF32(st, 0x144);
        RF32(st, 0x148) = h.z * RF32(st, 0x44) + RF32(st, 0x148);
        PSVECScale((Vec*)(st + 0x140), dt, (Vec*)&q);
        q.w = 0.0f;
        PSQUATMultiply((Quaternion*)(st + 0xF4), &q, &q);
        PSQUATScale(&q, 0.5f * dt, &q);
        PSQUATAdd((Quaternion*)(st + 0xF4), &q, &q);
        if (q.x != 0.0f || q.y != 0.0f || q.z != 0.0f || q.w != 0.0f) {
            PSQUATNormalize(&q, (Quaternion*)(st + 0xF4));
        } else {
            memcpy(st + 0xF4, &q, 16);
        }
        RF32(st, 0x134) = 0.0f;
        RF32(st, 0x138) = 0.0f;
        RF32(st, 0x13C) = 0.0f;
        RF32(st, 0x110) = 0.0f;
        RF32(st, 0x114) = 0.0f;
        RF32(st, 0x118) = 0.0f;
        PSMTXQuat((f32(*)[4])(st + 0x88), (Quaternion*)(st + 0xF4));
        PSMTXInverse((f32(*)[4])(st + 0x88), (f32(*)[4])(st + 0xB8));
        PSMTXTransApply((f32(*)[4])(st + 0x88), (f32(*)[4])(st + 0x58), RF32(st, 0xE8), RF32(st, 0xEC), RF32(st, 0xF0));
        PSMTXMultVec((f32(*)[4])(st + 0x58), (Vec*)(st + 0xC), &P1);
        PSMTXMultVec((f32(*)[4])(st + 0x58), (Vec*)st, &P0);
        lim = RF32(st, 0x2C);
        flag[0] = (P1.y < -lim) ? 0 : (P1.y > lim ? -1 : 1);
        flag[1] = (P0.y < -lim) ? 0 : (P0.y > lim ? -1 : 1);
        if (flag[0] == 0) {
            st[0x14D] = 0;
        } else if (st[0x14D] != 0) {
            flag[0] = 0;
        }
        if (flag[1] == 0) {
            st[0x14C] = 0;
        } else if (st[0x14C] != 0) {
            flag[1] = 0;
        }
        if (flag[0] == -1 || flag[1] == -1) {
            memcpy(st, obj, 0x150);
            dt = dt * 0.5f;
            continue;
        }
        PSMTXMultVec((f32(*)[4])(st + 0xB8), (Vec*)(st + 0x11C), (Vec*)(st + 0x128));
        memcpy(&c1, st + 0x128, 12);
        memcpy(&c2, st + 0x140, 12);
        n.x = 0.0f;
        n.y = 1.0f;
        n.z = 0.0f;
        PSMTXMultVec((f32(*)[4])(st + 0xB8), &n, &n);
        for (j = 1; j >= 0; j--) {
            if (flag[j] != 0) {
                PSVECCrossProduct(&c2, pt[j], &cp);
                PSVECAdd(&c1, &cp, &cp);
                PSMTXMultVec((f32(*)[4])(st + 0x88), &cp, &pv);
                if (pv.y > 0.0f) {
                    PSVECCrossProduct(pt[j], &n, &pv);
                    pv.x = pv.x * RF32(st, 0x3C);
                    pv.y = pv.y * RF32(st, 0x40);
                    pv.z = pv.z * RF32(st, 0x44);
                    PSVECCrossProduct(&pv, pt[j], &pv);
                    denom = RF32(st, 0x28) + PSVECDotProduct(&n, &pv);
                    PSVECScale(&n, (1.0f + RF32(st, 0x54)) * -PSVECDotProduct(&cp, &n) / denom, &cp);
                    PSVECScale(&cp, RF32(st, 0x28), &pv);
                    PSVECAdd((Vec*)(st + 0x128), &pv, (Vec*)(st + 0x128));
                    PSVECCrossProduct(pt[j], &cp, &cp);
                    cp.x = cp.x * RF32(st, 0x3C);
                    cp.y = cp.y * RF32(st, 0x40);
                    cp.z = cp.z * RF32(st, 0x44);
                    PSVECAdd((Vec*)(st + 0x140), &cp, (Vec*)(st + 0x140));
                    if (j != 0) {
                        st[0x14C] = 1;
                    } else {
                        st[0x14D] = 1;
                    }
                }
            }
        }
        PSMTXMultVec((f32(*)[4])(st + 0x88), (Vec*)(st + 0x128), (Vec*)(st + 0x11C));
        timeLeft -= dt;
        if (dt < timeLeft) {
            dt = timeLeft;
        }
        memcpy(obj, st, 0x150);
    } while (timeLeft > 0.0f);
    return 0;
}

void fn_8003819C(void* obj) {
    Vec x;
    Vec g;
    Vec c;
    Vec p;
    Vec v;
    s32 i;

    v.x = 0.0f;
    v.z = 0.0f;
    v.y = 9.80665f * RF32(obj, 0x24);
    PSMTXMultVec((f32(*)[4])((u8*)obj + 0xB8), &v, &v);
    PSVECAdd((Vec*)((u8*)obj + 0x110), &v, (Vec*)((u8*)obj + 0x110));
    for (i = 0; i <= 10; i++) {
        PSVECScale((Vec*)((u8*)obj + 0x18), (f32)i / 10.0f, &p);
        PSVECAdd((Vec*)((u8*)obj + 0xC), &p, &p);
        PSVECCrossProduct((Vec*)((u8*)obj + 0x140), &p, &c);
        PSVECAdd(&c, (Vec*)((u8*)obj + 0x128), &c);
        PSVECScale(&c, RF32(obj, 0x50), &v);
        if (((u8*)obj)[0x14D] != 0 && ((u8*)obj)[0x14C] != 0) {
            g.x = 0.0f;
            g.z = 0.0f;
            g.y = -9.80665f * RF32(obj, 0x24) / 20.0f;
            if (i > 0 && i < 10) {
                g.y *= 2.0f;
            }
            PSMTXMultVec((f32(*)[4])((u8*)obj + 0xB8), &g, &g);
            PSVECAdd(&v, &g, &v);
        } else if ((((u8*)obj)[0x14D] != 0 && i == 0) || (((u8*)obj)[0x14C] != 0 && i == 10)) {
            g.x = 0.0f;
            g.z = 0.0f;
            g.y = -9.80665f * RF32(obj, 0x24);
            PSMTXMultVec((f32(*)[4])((u8*)obj + 0xB8), &g, &g);
            PSVECAdd(&v, &g, &v);
        }
        PSVECAdd((Vec*)((u8*)obj + 0x110), &v, (Vec*)((u8*)obj + 0x110));
        PSVECCrossProduct(&p, &v, &x);
        PSVECAdd((Vec*)((u8*)obj + 0x134), &x, (Vec*)((u8*)obj + 0x134));
    }
}

void fn_800383BC(void* obj) {
    PSMTXQuat((f32(*)[4])((u8*)obj + 0x88), (Quaternion*)((u8*)obj + 0xF4));
    PSMTXInverse((f32(*)[4])((u8*)obj + 0x88), (f32(*)[4])((u8*)obj + 0xB8));
    PSMTXTransApply((f32(*)[4])((u8*)obj + 0x88), (f32(*)[4])((u8*)obj + 0x58), RF32(obj, 0xE8), RF32(obj, 0xEC), RF32(obj, 0xF0));
}

void fn_80038E2C(void* obj) {
    RF32(obj, 0x0) = 0.8f;
    RF32(obj, 0x4) = 0.5f;
    RF32(obj, 0x8) = 100.0f;
    RF32(obj, 0xC) = 5.0f;
    RF32(obj, 0x10) = 1.5f;
    RF32(obj, 0x14) = 0.001f;
    RU32(obj, 0x20) = 8;
    RF32(obj, 0x18) = 1.0f / (s32)RU32(obj, 0x20) / 60.0f;
    RF32(obj, 0x1C) = RF32(obj, 0x18) * RF32(obj, 0x18);
    RF32(obj, 0x24) = 1.0f / (2.0f * RF32(obj, 0x18));
}

#define TRACK_ACTOR(actors, node, idx) \
    (((u8**)*(u32*)((u8*)(node) + 0x18))[*(u16*)((u8*)(actors) + (idx) * 2 + 0x162)])
#define TRACK_MTX(obj) (*(f32(**)[4])((obj) + 0xEC))

static void trackWriteBack(u8* S, void* actors, void* node) {
    Vec v;
    u8* obj = TRACK_ACTOR(actors, node, RU32(S, 0x80));

    PSMTXCopy((f32(*)[4])S, TRACK_MTX(obj));
    PSVECScale((Vec*)(S + 0x48), -1.0f, &v);
    PSMTXMultVec((f32(*)[4])S, &v, &v);
    TRACK_MTX(obj)[0][3] = v.x;
    TRACK_MTX(obj)[1][3] = v.y;
    TRACK_MTX(obj)[2][3] = v.z;
    RU32(S, 0x78) = RU32(S, 0x78) + 1;
}

void fn_80038F08(void* actors, void* node, u8 slot) {
    u8* S = lbl_800F79B8;
    u8* obj;
    Vec v;
    Vec cur;
    Mtx dM;
    Mtx T;
    f32 dt = (1.0f / 60.0f) * lbl_803CB81C;
    s32 k;

    obj = TRACK_ACTOR(actors, node, RU32(S, 0x7C) + slot);
    if ((s32)RU32(S, 0x78) < 0) {
        return;
    }
    if (RU32(S, 0x78) == 0) {
        PSMTXCopy(TRACK_MTX(obj), (f32(*)[4])S);
        PSMTXMultVec(TRACK_MTX(obj), (Vec*)(S + 0x48), &v);
        RF32(S, 0xC) = v.x;
        RF32(S, 0x1C) = v.y;
        RF32(S, 0x2C) = v.z;
        trackWriteBack(S, actors, node);
    } else if (RU32(S, 0x78) == 1) {
        PSMTXMultVec(TRACK_MTX(obj), (Vec*)(S + 0x48), &v);
        cur.x = RF32(S, 0xC);
        cur.y = RF32(S, 0x1C);
        cur.z = RF32(S, 0x2C);
        PSVECSubtract(&v, &cur, (Vec*)(S + 0x3C));
        if (lbl_803CBCA0 != 0) {
            memcpy(S + 0x3C, lbl_800F79A0 + 0xC, 12);
        } else {
            PSVECAdd((Vec*)(S + 0x3C), (Vec*)lbl_800F79A0, (Vec*)(S + 0x3C));
        }
        PSVECScale((Vec*)(S + 0x3C), lbl_803CB824, (Vec*)(S + 0x3C));
        PSVECScale((Vec*)(S + 0x3C), 1.0f / dt, (Vec*)(S + 0x3C));
        for (k = 0; k < 3; k++) {
            dM[k][0] = (TRACK_MTX(obj)[k][0] - ((f32(*)[4])S)[k][0]) / dt;
            dM[k][1] = (TRACK_MTX(obj)[k][1] - ((f32(*)[4])S)[k][1]) / dt;
            dM[k][2] = (TRACK_MTX(obj)[k][2] - ((f32(*)[4])S)[k][2]) / dt;
        }
        dM[0][3] = 0.0f;
        dM[1][3] = 0.0f;
        dM[2][3] = 0.0f;
        PSMTXTranspose(TRACK_MTX(obj), T);
        PSMTXConcat(dM, T, dM);
        RF32(S, 0x30) = dM[2][1];
        RF32(S, 0x34) = dM[0][2];
        RF32(S, 0x38) = dM[1][0];
        PSMTXMultVec(T, (Vec*)(S + 0x30), (Vec*)(S + 0x30));
        PSMTXCopy(TRACK_MTX(obj), (f32(*)[4])S);
        PSVECScale((Vec*)(S + 0x30), 0.5f * lbl_803CB824, (Vec*)(S + 0x30));
        RF32(S, 0xC) = v.x;
        RF32(S, 0x1C) = v.y;
        RF32(S, 0x2C) = v.z;
        trackWriteBack(S, actors, node);
    } else {
        PSMTXTrans(T, RF32(HUGE_ANIM_BYTES, 0xC38), RF32(HUGE_ANIM_BYTES, 0xC3C), RF32(HUGE_ANIM_BYTES, 0xC40));
        PSMTXInverse(T, T);
        fn_80039310(S, -0.12675f, 1.8f);
        {
            u8* o2 = TRACK_ACTOR(actors, node, RU32(S, 0x80));
            Vec w;

            PSMTXCopy((f32(*)[4])S, TRACK_MTX(o2));
            PSVECScale((Vec*)(S + 0x48), -1.0f, &w);
            PSMTXMultVec((f32(*)[4])S, &w, &w);
            TRACK_MTX(o2)[0][3] = w.x;
            TRACK_MTX(o2)[1][3] = w.y;
            TRACK_MTX(o2)[2][3] = w.z;
            RU32(S, 0x78) = RU32(S, 0x78) + (RU32(S, 0x78) == 2);
        }
    }
}

void fn_80038EC4(void* a, void* b, s32 c) {
    if (*(s32*)(lbl_800F79B8 + 0x78) < 0) {
        *(s32*)(lbl_800F79B8 + 0x78) = 0;
    }
    fn_80038F08(a, *(void**)b, (u8)c);
}

void fn_80039A4C(void) {
    *(s32*)(lbl_800F79B8 + 0x78) = -1;
    lbl_803CBCA2 = 0;
    memset(lbl_800F79A0, 0, 12);
    lbl_803CB818 = -1;
    lbl_803CB820 = -1;
    lbl_803CBCA1 = 0;
}

void fn_80038418(void* obj, f32* pos, Quaternion* orient, f32* outPos, Quaternion* outQuat) {
    Quaternion q;
    Mtx m1;
    Mtx m2;
    Vec v;
    f32 w;
    f32 s;

    v.x = -RF32(obj, 0xC);
    v.y = -RF32(obj, 0x10);
    v.z = -RF32(obj, 0x14);
    PSMTXQuat((f32(*)[4])((u8*)obj + 0x88), orient);
    PSMTXInverse((f32(*)[4])((u8*)obj + 0x88), (f32(*)[4])((u8*)obj + 0xB8));
    PSMTXTransApply((f32(*)[4])((u8*)obj + 0x88), (f32(*)[4])((u8*)obj + 0x58), pos[0], pos[1], pos[2]);
    PSMTXMultVec((f32(*)[4])((u8*)obj + 0x58), &v, (Vec*)((u8*)obj + 0xE8));
    memcpy((u8*)obj + 0xF4, orient, 16);
    PSMTXQuat(m1, outQuat);
    PSMTXTransApply(m1, m2, outPos[0], outPos[1], outPos[2]);
    PSMTXMultVec(m2, &v, &v);
    PSVECSubtract((Vec*)((u8*)obj + 0xE8), &v, &v);
    PSVECScale(&v, 60.0f, (Vec*)((u8*)obj + 0x11C));
    PSMTXMultVec((f32(*)[4])((u8*)obj + 0xB8), (Vec*)((u8*)obj + 0x11C), (Vec*)((u8*)obj + 0x128));
    memset((u8*)obj + 0x11C, 0, 12);
    memset((u8*)obj + 0x128, 0, 12);
    PSMTXQuat(m2, orient);
    PSMTXQuat(m1, outQuat);
    PSMTXInverse(m1, m1);
    PSMTXConcat(m2, m1, m2);
    C_QUATMtx(&q, m2);
    q.w = acos(q.w);
    w = 60.0f * (2.0f * q.w);
    q.w = sin(q.w);
    if (q.w != 0.0f) {
        PSVECScale((Vec*)&q, w / q.w, (Vec*)((u8*)obj + 0x140));
    } else {
        RF32(obj, 0x140) = w;
        RF32(obj, 0x144) = 0.0f;
        RF32(obj, 0x148) = 0.0f;
    }
}

void fn_800385F0(void* obj, f32 a, f32 b, f32 c, f32 d) {
    RF32(obj, 0xC) = 0.0f;
    RF32(obj, 0x10) = -a * b;
    RF32(obj, 0x14) = 0.0f;
    RF32(obj, 0x0) = 0.0f;
    RF32(obj, 0x4) = a + RF32(obj, 0x10);
    RF32(obj, 0x8) = 0.0f;
    PSVECSubtract((Vec*)obj, (Vec*)((u8*)obj + 0xC), (Vec*)((u8*)obj + 0x18));
    RF32(obj, 0x24) = d;
    RF32(obj, 0x28) = 1.0f / d;
    RF32(obj, 0x2C) = c;
    RF32(obj, 0x38) = d * (a * a / 12.0f + c * c * 0.25f);
    RF32(obj, 0x30) = RF32(obj, 0x38);
    RF32(obj, 0x34) = c * (d * c) * 0.5f;
    RF32(obj, 0x3C) = 1.0f / RF32(obj, 0x30);
    RF32(obj, 0x44) = RF32(obj, 0x3C);
    RF32(obj, 0x40) = 1.0f / RF32(obj, 0x34);
    RU32(obj, 0x4C) = 1;
    RF32(obj, 0x48) = (1.0f / 60.0f) / (f32)(s32)RU32(obj, 0x4C);
    RF32(obj, 0x50) = 0.0f;
    RF32(obj, 0x54) = 0.5f;
    PSMTXIdentity((f32(*)[4])((u8*)obj + 0x88));
    PSMTXIdentity((f32(*)[4])((u8*)obj + 0x58));
    RF32(obj, 0xF0) = 0.0f;
    RF32(obj, 0xEC) = 0.0f;
    RF32(obj, 0xE8) = 0.0f;
    RF32(obj, 0xFC) = 0.0f;
    RF32(obj, 0xF8) = 0.0f;
    RF32(obj, 0xF4) = 0.0f;
    RF32(obj, 0x100) = 1.0f;
    RF32(obj, 0x118) = 0.0f;
    RF32(obj, 0x114) = 0.0f;
    RF32(obj, 0x110) = 0.0f;
    RF32(obj, 0x124) = 0.0f;
    RF32(obj, 0x120) = 0.0f;
    RF32(obj, 0x11C) = 0.0f;
    RF32(obj, 0x130) = 0.0f;
    RF32(obj, 0x12C) = 0.0f;
    RF32(obj, 0x128) = 0.0f;
    RF32(obj, 0x13C) = 0.0f;
    RF32(obj, 0x138) = 0.0f;
    RF32(obj, 0x134) = 0.0f;
    RF32(obj, 0x148) = 0.0f;
    RF32(obj, 0x144) = 0.0f;
    RF32(obj, 0x140) = 0.0f;
    ((u8*)obj)[0x14D] = 0;
    ((u8*)obj)[0x14C] = 0;
}

void fn_800387B0(void* obj, void* nodes, s32 count, Vec* extra) {
    Vec f;
    Vec d;
    Vec dv;
    u8* n;
    u8* prev;
    f32 len;
    f32 spring;
    f32 damp;
    f32 mag;
    f32 m2;
    f32 friction;
    s32 i;

    n = (u8*)nodes;
    for (i = 0; i < count; i++) {
        memset(n + 0x30, 0, 12);
        if (RU32(n, 0x3C) == 0) {
            RF32(n, 0x34) = -9.80665f * RF32(n, 0x0);
        }
        if (i == count - 1) {
            PSVECAdd((Vec*)(n + 0x30), extra, (Vec*)(n + 0x30));
        }
        n += 0x40;
    }

    n = (u8*)nodes + count * 0x40;
    i = count;
    do {
        prev = (u8*)nodes + (i - 1) * 0x40;
        PSVECSubtract((Vec*)(n + 0xC), (Vec*)(prev + 0xC), &d);
        PSVECSubtract((Vec*)(n + 0x24), (Vec*)(prev + 0x24), &dv);
        len = PSVECMag(&d);
        if (len != 0.0f) {
            spring = RF32(obj, 0x8) * (len - RF32(obj, 0x0));
            damp = RF32(obj, 0xC) * (PSVECDotProduct(&dv, &d) / len);
            PSVECNormalize(&d, &d);
            PSVECScale(&d, -(spring + damp), &d);
            if (RU32(n, 0x3C) == 0) {
                PSVECAdd((Vec*)(n + 0x30), &d, (Vec*)(n + 0x30));
            }
            PSVECScale(&d, -1.0f, &d);
            if (RU32(prev, 0x3C) == 0) {
                PSVECAdd((Vec*)(prev + 0x30), &d, (Vec*)(prev + 0x30));
            }
        }
        n -= 0x40;
    } while (--i != 0);

    n = (u8*)nodes;
    for (i = 0; i < count; i++) {
        if (RU32(n, 0x3C) == 0) {
            memcpy(&dv, n + 0x24, 12);
            memcpy(&d, n + 0x30, 12);
            PSVECScale(&d, RF32(n, 0x4), &d);
            PSVECScale(&d, RF32(obj, 0x18), &d);
            PSVECAdd(&dv, &d, &dv);
            memset(&f, 0, 12);
            mag = PSVECMag(&dv);
            if (mag != 0.0f) {
                PSVECScale(&dv, -1.0f, &d);
                PSVECNormalize(&d, &d);
                PSVECScale(&d, RF32(obj, 0x14) * (mag * mag), &d);
                PSVECAdd(&f, &d, &f);
            }
            if (RF32(n, 0x10) <= RF32(n, 0x8)) {
                if (RF32(n, 0x34) < 0.0f) {
                    friction = RF32(n, 0x34) * RF32(obj, 0x10);
                    if (friction < 0.0f) {
                        friction = -friction;
                    }
                    memcpy(&d, n + 0x30, 12);
                    d.y = 0.0f;
                    mag = PSVECMag(&d);
                    dv.y = 0.0f;
                    m2 = PSVECMag(&dv);
                    if (m2 == 0.0f && mag <= friction) {
                        PSVECScale((Vec*)(n + 0x30), -1.0f, &d);
                        PSVECAdd(&f, &d, &f);
                    } else {
                        if (m2 != 0.0f) {
                            PSVECNormalize(&dv, &d);
                        } else {
                            PSVECNormalize(&d, &d);
                        }
                        PSVECScale(&d, -friction, &d);
                        PSVECAdd(&f, &d, &f);
                    }
                }
            }
            PSVECAdd((Vec*)(n + 0x30), &f, (Vec*)(n + 0x30));
        }
        n += 0x40;
    }
}

void fn_80038B48(void* obj, void* nodes, s32 count, Vec* wind) {
    Vec w;
    Vec p;
    Vec u;
    Vec t;
    u8* n;
    f32 damping;
    f32 gravityStep;
    s32 it;
    s32 j;

    PSVECScale(wind, RF32(obj, 0x18), &w);
    for (it = 0; it < (s32)RU32(obj, 0x20); it++) {
        fn_800387B0(obj, nodes, count, &w);
        n = (u8*)nodes;
        for (j = 0; j < count; j++) {
            PSVECScale((Vec*)(n + 0x30), RF32(n, 0x4), &t);
            damping = RF32(obj, 0x24);
            gravityStep = RF32(obj, 0x1C);
            PSVECScale((Vec*)(n + 0xC), 2.0f, &p);
            PSVECSubtract(&p, (Vec*)(n + 0x18), &p);
            PSVECScale(&t, gravityStep, &u);
            PSVECAdd(&p, &u, &p);
            PSVECSubtract(&p, (Vec*)(n + 0x18), (Vec*)(n + 0x24));
            PSVECScale((Vec*)(n + 0x24), damping, (Vec*)(n + 0x24));
            memcpy(n + 0x18, n + 0xC, 12);
            memcpy(n + 0xC, &p, 12);
            if (RU32(n, 0x3C) == 0) {
                f32 pen = RF32(n, 0x10) - RF32(n, 0x8);
                if (pen < 0.0f) {
                    RF32(n, 0x10) = RF32(n, 0x10) - pen * RF32(obj, 0x4);
                    RF32(n, 0x1C) = RF32(n, 0x1C) - (RF32(n, 0x1C) - RF32(n, 0x8)) * RF32(obj, 0x4);
                }
            }
            n += 0x40;
        }
    }
}

void* fn_80038CD0(u8 count, f32* spacing, void* buf, f32 y, f32 mass) {
    u8* node = (u8*)buf;
    f32 massMid = 2.0f * mass;
    s32 i;

    memset(buf, 0, count * 0x40);
    for (i = 0; i < count; i++) {
        if (i == 0) {
            RF32(node, 0x0) = mass;
        } else if (i == count - 1) {
            RF32(node, 0x0) = mass;
        } else {
            RF32(node, 0x0) = massMid;
        }
        RF32(node, 0x8) = y;
        RF32(node, 0x4) = 1.0f / RF32(node, 0x0);
        RF32(node, 0xC) = 0.0f;
        RF32(node, 0x10) = spacing[0] * (f32)i + y;
        RF32(node, 0x14) = 0.0f;
        memcpy(node + 0x18, node + 0xC, 12);
        RU32(node, 0x3C) = (i == 0);
        node += 0x40;
    }
    return buf;
}

void fn_80039310(void* obj, f32 ground, f32 restLimit) {
    u8* S = (u8*)obj;
    Quaternion qr;
    Quaternion qv;
    Mtx rot;
    Mtx M;
    Vec w0;
    Vec acc;
    Vec k;
    Vec d;
    Vec wp;
    Vec n;
    Vec nrm;
    Vec p2;
    Vec a;
    Vec b;
    Vec up;
    f32 invX = 1.0f / RF32(S, 0x6C);
    f32 invY = 1.0f / RF32(S, 0x70);
    f32 invZ = 1.0f / RF32(S, 0x74);
    f32 dt = (1.0f / 60.0f) * lbl_803CB81C;
    f32 mag;
    f32 half;
    f32 height;
    f32 ke;
    f32 denom;
    f32 ang;
    s32 i;
    s32 j;

    mag = PSVECMag((Vec*)(S + 0x30));
    if (mag >= 50.0f) {
        PSVECScale((Vec*)(S + 0x30), 50.0f / mag, (Vec*)(S + 0x30));
    }
    half = 0.5f * dt;
    PSVECScale((Vec*)(S + 0x3C), half, &k);
    PSMTXTransApply((f32(*)[4])S, (f32(*)[4])S, k.x, k.y, k.z);
    PSVECScale((Vec*)(S + 0x3C), 0.5f * -dt, &k);
    PSVECAdd((Vec*)(S + 0x3C), &k, (Vec*)(S + 0x3C));
    RF32(S, 0x40) = 20.0f * dt + RF32(S, 0x40);
    PSVECScale((Vec*)(S + 0x3C), half, &k);
    PSMTXTransApply((f32(*)[4])S, (f32(*)[4])S, k.x, k.y, k.z);

    memcpy(&w0, S + 0x30, 12);
    memset(&acc, 0, 12);
    d.x = invX * (RF32(S, 0x70) - RF32(S, 0x74));
    d.y = invY * (RF32(S, 0x74) - RF32(S, 0x6C));
    d.z = invZ * (RF32(S, 0x6C) - RF32(S, 0x70));
    PSVECScale(&d, dt, &d);
    for (i = 0; i < 4; i++) {
        k.x = d.x * (w0.y * w0.z - 0.2f * w0.x);
        k.y = d.y * (w0.z * w0.x - 0.2f * w0.y);
        k.z = d.z * (w0.x * w0.y - 0.2f * w0.z);
        if (i == 1 || i == 2) {
            PSVECScale(&k, 2.0f, &k);
        }
        PSVECAdd(&acc, &k, &acc);
        PSVECScale(&k, 0.5f, &w0);
    }
    PSVECScale(&acc, 1.0f / 6.0f, &k);
    PSVECAdd((Vec*)(S + 0x30), &k, (Vec*)(S + 0x30));

    mag = PSVECMag((Vec*)(S + 0x30));
    if (mag > 0.0001f) {
        ang = 0.5f * (-mag * dt);
        qr.w = cos(ang);
        PSVECScale((Vec*)(S + 0x30), (1.0f / mag) * sin(ang), (Vec*)&qr);
    } else {
        qr.x = 0.0f;
        qr.y = 0.0f;
        qr.z = 0.0f;
        qr.w = 1.0f;
    }
    PSMTXQuat(rot, &qr);
    PSMTXConcat((f32(*)[4])S, rot, (f32(*)[4])S);

    for (j = 0; j < 2; j++) {
        u8* pt = S + 0x54 + j * 12;

        PSMTXMultVec((f32(*)[4])S, (Vec*)pt, &wp);
        height = wp.y;
        if (height > ground) {
            PSMTXCopy((f32(*)[4])S, M);
            M[0][3] = 0.0f;
            M[1][3] = 0.0f;
            M[2][3] = 0.0f;
            PSVECCrossProduct((Vec*)(S + 0x30), (Vec*)pt, &wp);
            PSMTXMultVec(M, &wp, &wp);
            PSVECAdd((Vec*)(S + 0x3C), &wp, &wp);
            n.x = wp.x;
            n.y = 1.3f * -wp.y;
            n.z = wp.z;
            nrm.x = 0.0f;
            nrm.y = -1.0f;
            nrm.z = 0.0f;
            PSMTXMultVec(M, (Vec*)pt, &p2);
            PSMTXScale(M, invX, invY, invZ);
            PSMTXConcat((f32(*)[4])S, M, M);
            PSMTXTranspose((f32(*)[4])S, rot);
            PSMTXConcat(M, rot, M);
            PSVECCrossProduct(&p2, &nrm, &wp);
            PSMTXMultVec(M, &wp, &wp);
            PSVECCrossProduct(&wp, &p2, &wp);
            denom = 0.2962963f + PSVECDotProduct(&wp, &nrm);
            n.y = n.y / denom;
            RF32(S, 0x40) = RF32(S, 0x40) + n.y / 3.375f;
            n.x = n.x * -0.1f;
            n.z = n.z * -0.1f;
            RF32(S, 0x3C) = RF32(S, 0x3C) + n.x;
            RF32(S, 0x44) = RF32(S, 0x44) + n.z;
            PSMTXTranspose((f32(*)[4])S, rot);
            rot[0][3] = 0.0f;
            rot[1][3] = 0.0f;
            rot[2][3] = 0.0f;
            PSMTXMultVec(rot, &n, &wp);
            PSVECCrossProduct((Vec*)pt, &wp, &wp);
            nrm.x = RF32(S, 0x30) * RF32(S, 0x6C);
            nrm.y = RF32(S, 0x34) * RF32(S, 0x70);
            nrm.z = RF32(S, 0x38) * RF32(S, 0x74);
            PSVECAdd(&wp, &nrm, &wp);
            RF32(S, 0x30) = wp.x * invX;
            RF32(S, 0x34) = wp.y * invY;
            RF32(S, 0x38) = wp.z * invZ;
            RF32(S, 0x1C) = RF32(S, 0x1C) - (height - ground);
            lbl_803CBCA1 = 1;
        }
    }

    ke = 0.5f * (RF32(S, 0x30) * (RF32(S, 0x6C) * RF32(S, 0x30)) + RF32(S, 0x34) * (RF32(S, 0x70) * RF32(S, 0x34)) +
                 RF32(S, 0x38) * (RF32(S, 0x74) * RF32(S, 0x38))) +
         0.5f * (RF32(S, 0x3C) * RF32(S, 0x3C) + RF32(S, 0x40) * RF32(S, 0x40) + RF32(S, 0x44) * RF32(S, 0x44));
    if (RF32(S, 0x1C) > 0.0f) {
        ke = RF32(S, 0x1C) * 20.0f + ke;
    } else {
        ke = ke - RF32(S, 0x1C) * 20.0f;
    }
    if (ke <= restLimit) {
        RF32(S, 0x1C) = ground;
        RF32(S, 0x44) = 0.0f;
        RF32(S, 0x40) = 0.0f;
        RF32(S, 0x3C) = 0.0f;
        RF32(S, 0x38) = 0.0f;
        RF32(S, 0x34) = 0.0f;
        RF32(S, 0x30) = 0.0f;
        PSMTXMultVec((f32(*)[4])S, (Vec*)(S + 0x54), &a);
        PSMTXMultVec((f32(*)[4])S, (Vec*)(S + 0x60), &b);
        PSVECSubtract(&a, &b, &a);
        half = 0.5f * sin(a.y / PSVECMag(&a));
        up.x = 0.0f;
        up.y = -1.0f;
        up.z = 0.0f;
        PSVECCrossProduct(&up, &a, &a);
        PSVECScale(&a, sin(half) / PSVECMag(&a), (Vec*)&qv);
        qv.w = cos(half);
        PSMTXQuat(rot, &qv);
        PSMTXConcat(rot, (f32(*)[4])S, rot);
        PSMTXCopy(rot, (f32(*)[4])S);
    }
}

