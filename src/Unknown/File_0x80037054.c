#include <string.h>
#include <math.h>
#include "mssbTypes.h"
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

extern u8 hugeAnimStruct[];
extern u8 lbl_800F79A0[];
extern u8 lbl_800F79B8[];
extern s16 lbl_803CB818;
extern s32 lbl_803CB820;
extern u8 lbl_803CBCA1;
extern u8 lbl_803CBCA2;

void fn_80038418(void* obj, f32* pos, Quaternion* orient, f32* outPos, Quaternion* outQuat);
void fn_800387B0(void* obj, void* nodes, s32 count, Vec* wind);
void fn_80038F08(void* a, void* b, s32 c, s32 d);

#define RF32(p, off) (*(f32*)((u8*)(p) + (off)))
#define RU32(p, off) (*(u32*)((u8*)(p) + (off)))

void fn_80037964(void) {
    removeCurrentDrawingItem();
}

void fn_80037984(void) {
    DrawingSceneStruct* item = currentDrawingItem;
    u8* obj;
    u8* node;
    u32 index;
    Mtx mtx;
    Quaternion quat;
    Vec pos;

    obj = (u8*)*(u32*)(hugeAnimStruct + 0x2C50 + ((u8*)item)[0x3E] * 4);
    node = (u8*)*(u32*)((u8*)*(u32*)(hugeAnimStruct + 0x60) + (s8)obj[0x255] * 0x90 + 0x34);
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

    if (*(u32*)(hugeAnimStruct + 0x2C50 + index * 4) != 0) {
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

void fn_80038EC4(void* a, void* b, s32 c) {
    if (*(s32*)(lbl_800F79B8 + 0x78) < 0) {
        *(s32*)(lbl_800F79B8 + 0x78) = 0;
    }
    fn_80038F08(a, *(void**)b, (u8)c, 0);
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
