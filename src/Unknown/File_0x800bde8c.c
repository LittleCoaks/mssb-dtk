#include "Unknown/File_0x800bde8c.h"
#include "Dolphin/gx.h"
#include "Dolphin/os.h"
#include "Unknown/File_0x800acf14.h"

void fn_800BDE8C(int arg0) {
    drawShadows._4C = (arg0 & 7) << 5;
}

void fn_800BDEA0(void) {
    void** dst;

    if (drawShadows.enabled) {
        if (drawShadows.callback20) {
            ((void (*)(Mtx, int))drawShadows.callback20)(drawShadows.camera->viewMtx, 0);
        }
        GXSetTexCopySrc(0, 0, 640, 448);
        GXSetTexCopyDst(640, 480, 0x20, 0);
        dst = *(void***)((u8*)&drawShadows + 4);
        GXCopyTex(*dst, TRUE);
        GXPixModeSync();
        drawShadows.pointCount = 0;
        drawShadows.bounds[0][0] = drawShadows.bounds[1][0] = drawShadows.bounds[2][0] = 100000000.0f;
        drawShadows.bounds[0][1] = drawShadows.bounds[1][1] = drawShadows.bounds[2][1] = -100000000.0f;
        drawShadows.pointSum.x = drawShadows.pointSum.y = drawShadows.pointSum.z = 0.0f;
    }
}

void fn_800BDF70(StadiumModel* model) {
    u8 flags;

    if (drawShadows.enabled && drawShadows.modelCallback && ((u8*)model)[0x6C]) {
        flags = model->root->drawFlags;
        if ((flags & 0x24) && (flags & 0x12)) {
            drawShadows.modelCallback(model, drawShadows.camera->viewMtx);
        }
    }
}

void fn_800BDFE0(u8* list) {
    u8* entry;
    s32 i;
    u8 flags;
    StadiumModel* model;

    if (drawShadows.enabled && drawShadows.modelCallback) {
        entry = list;
        for (i = 0; i < *(u16*)list; i++, entry += 0x90) {
            if (entry[0xA0]) {
                model = (StadiumModel*)(entry + 0x34);
                flags = model->root->drawFlags;
                if ((flags & 0x24) && (flags & 0x12)) {
                    drawShadows.modelCallback(model, drawShadows.camera->viewMtx);
                }
            }
        }
    }
}

void fn_800BE09C(u32 arg0, ShadowCamera* cam) {
    u32 local;

    local = arg0;
    if (drawShadows.enabled) {
        GXSetScissor(2, 2, 636, 476);
        GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
        if (drawShadows.callback18) {
            ((void (*)(u32*))drawShadows.callback18)(&local);
        }
        fn_800BE498(cam->viewMtx, 640.0f, 448.0f, 1.0f, 512.0f, 1280.0f);
        fn_800BE158(drawShadows.camera, cam);
    }
}

void fn_800BE158(ShadowCamera* camera, ShadowCamera* other) {
    Vec tmp;
    f32* c;
    f32* src;
    f32 ratio;
    f32 mag;
    f32 span;
    f32 extent;
    f32 scale;
    f32 neg;
    f32 (*proj)[4];
    f32 (*light)[4];
    s32 ix;
    s32 iz;

    c = (f32*)camera;
    src = (f32*)other;

    ratio = src[1] / (src[1] - src[7]);
    PSVECSubtract((Vec*)(src + 6), (Vec*)other, &tmp);
    PSVECScale(&tmp, ratio, &tmp);
    mag = PSVECMag(&tmp);
    PSVECAdd((Vec*)other, &tmp, &tmp);

    scale = 100.0f;
    if (drawShadows.pointCount != 0) {
        ix = (s32)(drawShadows.bounds[0][1] - drawShadows.bounds[0][0]);
        iz = (s32)(drawShadows.bounds[2][1] - drawShadows.bounds[2][0]);
        if (ix < 0) {
            ix = -ix;
        }
        if (iz < 0) {
            iz = -iz;
        }
        extent = (f32)ix;
        if ((f32)iz > extent) {
            extent = (f32)iz;
        }
        span = extent / 1.4f;
        if (span < 15.0f) {
            span = 15.0f;
        }
        c[6] = (drawShadows.bounds[0][0] + drawShadows.bounds[0][1]) * 0.5f;
        c[7] = 0.0f;
        c[8] = (drawShadows.bounds[2][0] + drawShadows.bounds[2][1]) * 0.5f;
    } else {
        c[6] = 0.0f;
        c[7] = 0.0f;
        c[8] = 0.0f;
        span = 10.0f;
    }

    proj = (f32 (*)[4])((u8*)camera + 0x70);
    light = (f32 (*)[4])((u8*)camera + 0xB0);

    if (span < 20.0f || mag > 23.0f) {
        neg = -span;
        C_MTXOrtho(proj, neg, span, span, neg, c[11], c[12]);
        GXSetProjection(proj, GX_ORTHOGRAPHIC);
        C_MTXLightOrtho(light, span, neg, span, neg, 0.5f, 0.5f, 0.5f, 0.5f);
    } else {
        scale = (src[1] - 2.0f) * 2.5f;
        if (scale > -20.0f) {
            scale = -20.0f;
        }
        c[6] = tmp.x;
        c[7] = 0.0f;
        c[8] = tmp.z;
        scale = scale * -1.0f;
        C_MTXOrtho(proj, -12.0f, 12.0f, 12.0f, -12.0f, c[11], c[12]);
        GXSetProjection(proj, GX_ORTHOGRAPHIC);
        C_MTXLightOrtho(light, 12.0f, -12.0f, 12.0f, -12.0f, 0.5f, 0.5f, 0.5f, 0.5f);
    }

    PSVECScale((Vec*)(c + 13), scale, &tmp);
    PSVECAdd((Vec*)(c + 6), &tmp, (Vec*)camera);
    c[4] = (f32)drawShadows.unk4D;
    C_MTXLookAt(camera->viewMtx, (Vec*)camera, (Vec*)(c + 3), (Vec*)(c + 6));
    PSMTXConcat(light, camera->viewMtx, light);
}

extern u8 lbl_803C7420[0x398];

void fn_800BEC30(u8 count) {
    f32 corners[4][3] = {
        { 1.3f, 1.0f, 1.3f },
        { 1.3f, 1.0f, -1.3f },
        { -1.3f, 1.0f, 1.3f },
        { -1.3f, 1.0f, -1.3f },
    };
    MemoryStack* stack = &memoryUsedOrStorage;
    u8* lo = stack->lo;
    u8* hi = stack->hi;
    u8* ptrTable;
    u8* tlutTable;
    u8* camBase;
    u8* tlutEnd;
    u32 texSize;
    u32 aligned;
    u32 v;
    s32 i;
    u32 offTex;

    ptrTable = (u8*)(((u32)lo + 0x1F) & ~0x1F);
    *(u8**)((u8*)&drawShadows + 4) = ptrTable;
    aligned = ((u32)ptrTable + count * 4 + 0x1F) & ~0x1F;
    texSize = GXGetTexBufferSize(640, 480, GX_TF_I4, FALSE, FALSE);
    *(u32*)ptrTable = ((aligned + 0x1F) & ~0x1F);
    drawShadows.unk08 = (void*)((((texSize + *(u32*)ptrTable + 0x1F) & ~0x1F) + 0x1F) & ~0x1F);

    aligned = ((u32)drawShadows.unk08 + count * 0x20 + 0x1F) & ~0x1F;
    aligned = ((aligned + 0x1F) & ~0x1F);
    drawShadows.tlut = (GXTlutObj*)aligned;
    aligned = ((aligned + 0x2B) & ~0x1F);
    tlutTable = (u8*)((aligned + 0x1F) & ~0x1F);
    *(u8**)((u8*)&drawShadows + 0x10) = tlutTable;
    aligned = (((u32)tlutTable + 0x3F) & ~0x1F);

    for (v = 0x11110; v != 0;) {
        v -= 0x1111;
        *(u16*)(tlutTable + ((v & 0xF) << 1)) = (u16)v;
    }

    camBase = (u8*)((aligned + 0x1F) & ~0x1F);
    drawShadows.camera = (ShadowCamera*)camBase;
    tlutEnd = (u8*)(((u32)camBase + count * 0xE0 + 0x1F) & ~0x1F);

    fn_800AD054((int)tlutEnd, (int)hi);
    *(u32*)(lbl_803C7420 + 0x50) = (u32)tlutEnd;
    *(u32*)(lbl_803C7420 + 0x54) = (u32)hi;
    *(u32*)(lbl_803C7420 + 0x58) = (((u32)hi - (u32)tlutEnd) + 0x1F) & ~0x1F;
    OSSetArenaLo(hi);

    offTex = 0;
    for (i = 0; i < count; i++) {
        GXInitTexObjCI((GXTexObj*)((u8*)drawShadows.unk08 + offTex), ((void**)ptrTable)[i], 640, 480, GX_TF_C4, 0, 0, 0, GX_TLUT15);
        GXInitTlutObj(drawShadows.tlut, tlutTable, 0, 16);
        GXInitTexObjLOD((GXTexObj*)((u8*)drawShadows.unk08 + offTex), GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, FALSE, FALSE, 0);
        ((f32*)((u8*)drawShadows.camera + i * 0xE0))[10] = 0.175f;
        ((f32*)((u8*)drawShadows.camera + i * 0xE0))[9] = 0.25f;
        ((f32*)((u8*)drawShadows.camera + i * 0xE0))[11] = 1.0f;
        ((f32*)((u8*)drawShadows.camera + i * 0xE0))[12] = 512.0f;
        ((f32*)((u8*)drawShadows.camera + i * 0xE0))[0] = 100.0f;
        ((f32*)((u8*)drawShadows.camera + i * 0xE0))[1] = 100.0f;
        ((f32*)((u8*)drawShadows.camera + i * 0xE0))[2] = 100.0f;
        ((f32*)((u8*)drawShadows.camera + i * 0xE0))[3] = 0.0f;
        ((f32*)((u8*)drawShadows.camera + i * 0xE0))[4] = 1.0f;
        ((f32*)((u8*)drawShadows.camera + i * 0xE0))[5] = 0.0f;
        ((f32*)((u8*)drawShadows.camera + i * 0xE0))[6] = 0.0f;
        ((f32*)((u8*)drawShadows.camera + i * 0xE0))[7] = 0.0f;
        ((f32*)((u8*)drawShadows.camera + i * 0xE0))[8] = 50.0f;
        ((f32*)((u8*)drawShadows.camera + i * 0xE0))[13] = corners[i][0];
        ((f32*)((u8*)drawShadows.camera + i * 0xE0))[14] = corners[i][1];
        ((f32*)((u8*)drawShadows.camera + i * 0xE0))[15] = corners[i][2];
        offTex += 0x20;
    }

    drawShadows.enabled = 0;
    *((u8*)&drawShadows + 1) = count;
    drawShadows.callback18 = NULL;
    drawShadows.modelCallback = NULL;
    drawShadows.unk4D = 1;
}


void fn_800BE498(Mtx m, f32 a, f32 b, f32 c, f32 d, f32 e) {
    Mtx inv;
    Vec pts[8];
    Vec target;
    Vec origin;
    f32 s[4];
    f32 viewDot;
    f32 t;
    f32 acK;
    f32 adK;
    f32 bcK;
    f32 bdK;
    s32 i;

    if (drawShadows._4C & 0x40) {
        return;
    }

    origin.x = 0.0f;
    origin.y = 0.0f;
    origin.z = 0.0f;
    target.x = 0.0f;
    target.y = -1.0f;
    target.z = 0.0f;

    PSMTXMultVec(m, &origin, &origin);
    PSMTXMultVec(m, &target, &target);
    PSVECSubtract(&target, &origin, &target);
    if (PSVECMag(&target) == 0.0f) {
        return;
    }
    PSVECNormalize(&target, &target);
    viewDot = PSVECDotProduct(&target, &origin);

    acK = ((a * c) / e) * 0.5f;
    adK = ((a * d) / e) * 0.5f;
    bcK = ((b * c) / e) * 0.5f;
    bdK = ((b * d) / e) * 0.5f;

    pts[0].x = acK;      pts[0].y = 0.0f;   pts[0].z = -c;
    pts[1].x = adK;      pts[1].y = 0.0f;   pts[1].z = -d;
    pts[2].x = adK;      pts[2].y = bdK;    pts[2].z = -d;
    pts[3].x = adK;      pts[3].y = -bdK;   pts[3].z = -d;
    pts[4].x = 0.0f;     pts[4].y = bcK;    pts[4].z = 0.0f;
    pts[5].x = 0.0f;     pts[5].y = bdK;    pts[5].z = 0.0f;
    pts[6].x = acK - adK; pts[6].y = bcK - bdK; pts[6].z = d - c;
    pts[7].x = acK - adK; pts[7].y = bdK - bcK; pts[7].z = d - c;

    for (i = 0; i < 4; i++) {
        s[i] = PSVECDotProduct(&target, &pts[4 + i]);
        if (s[i] == 0.0f) {
            pts[4 + i].z = 0.0f;
        } else {
            t = (viewDot - PSVECDotProduct(&target, &pts[i])) / s[i];
            s[i] = t;
            PSVECScale(&pts[4 + i], t, &pts[4 + i]);
            PSVECAdd(&pts[i], &pts[4 + i], &pts[4 + i]);
        }
        if (s[i] < 0.0f) {
            s[i] = -s[i];
        }
    }

    if (pts[6].z > -c && pts[6].z < -d && pts[7].z > -c && pts[7].z < -d) {
        memcpy(&pts[4], &pts[6], sizeof(Vec));
        memcpy(&pts[5], &pts[7], sizeof(Vec));
    } else if (!(s[0] > 1.0f && s[1] <= 1.0f)) {
        if (pts[6].z > -c && pts[6].z < -d) {
            memcpy(&pts[7], &pts[6], sizeof(Vec));
        }
        if (s[0] >= 1.0f) {
            memcpy(&pts[4], &pts[7], sizeof(Vec));
        } else {
            memcpy(&pts[5], &pts[7], sizeof(Vec));
        }
    }

    PSMTXInverse(m, inv);
    PSMTXMultVec(inv, &pts[5], &pts[3]);
    pts[6].x = -pts[5].x;
    pts[6].y = pts[5].y;
    pts[6].z = pts[5].z;
    PSMTXMultVec(inv, &pts[6], &pts[0]);
    PSMTXMultVec(inv, &pts[4], &pts[2]);
    pts[6].x = -pts[4].x;
    pts[6].y = pts[4].y;
    pts[6].z = pts[4].z;
    PSMTXMultVec(inv, &pts[6], &pts[1]);

    pts[4].x = 10000.0f;
    pts[4].z = 10000.0f;
    pts[5].x = -10000.0f;
    pts[5].z = -10000.0f;
    for (i = 0; i < 4; i++) {
        if (pts[i].x < pts[4].x) pts[4].x = pts[i].x;
        if (pts[i].x > pts[5].x) pts[5].x = pts[i].x;
        if (pts[i].z < pts[4].z) pts[4].z = pts[i].z;
        if (pts[i].z > pts[5].z) pts[5].z = pts[i].z;
    }

    drawShadows.bounds[0][0] = pts[4].x;
    drawShadows.bounds[0][1] = pts[5].x;
    drawShadows.bounds[2][0] = pts[4].z;
    drawShadows.bounds[2][1] = pts[5].z;
    if (drawShadows.bounds[0][0] < -68.0f) drawShadows.bounds[0][0] = -68.0f;
    if (drawShadows.bounds[0][1] > 68.0f) drawShadows.bounds[0][1] = 68.0f;
    if (drawShadows.bounds[2][0] < -36.0f) drawShadows.bounds[2][0] = -36.0f;
    if (drawShadows.bounds[2][1] > 100.0f) drawShadows.bounds[2][1] = 100.0f;
}

void setVectors(Vec v) {
    drawShadows.bounds[0][0] = drawShadows.bounds[0][0] <= v.x ? drawShadows.bounds[0][0] : v.x;
    drawShadows.bounds[0][1] = drawShadows.bounds[0][1] >= v.x ? drawShadows.bounds[0][1] : v.x;
    drawShadows.bounds[1][0] = drawShadows.bounds[1][0] <= v.y ? drawShadows.bounds[1][0] : v.y;
    drawShadows.bounds[1][1] = drawShadows.bounds[1][1] >= v.y ? drawShadows.bounds[1][1] : v.y;
    drawShadows.bounds[2][0] = drawShadows.bounds[2][0] <= v.z ? drawShadows.bounds[2][0] : v.z;
    drawShadows.bounds[2][1] = drawShadows.bounds[2][1] >= v.z ? drawShadows.bounds[2][1] : v.z;
    PSVECAdd(&drawShadows.pointSum, &v, &drawShadows.pointSum);
    drawShadows.pointCount++;
}

void fn_800BEB3C(void) {
    drawShadows.pointCount = 0;
    drawShadows.bounds[0][0] = drawShadows.bounds[1][0] = drawShadows.bounds[2][0] = 100000000.0f;
    drawShadows.bounds[0][1] = drawShadows.bounds[1][1] = drawShadows.bounds[2][1] = -100000000.0f;
    drawShadows.pointSum.x = drawShadows.pointSum.y = drawShadows.pointSum.z = 0.0f;
}

MtxPtr returnMtxPtr(u8 index) {
    return drawShadows.camera[index].mtxB0;
}

u8 returnDrawShadows(void) {
    return drawShadows.enabled;
}

u8 GetDrawShadows(void) {
    return drawShadows.enabled;
}

void DrawShadows(u8 enable) {
    drawShadows.enabled = enable;
}

void updateVectorInArray(u8 index, Vec v) {
    drawShadows.camera[index].lightDir = v;
}

void fn_800BEC00(BOOL flag) {
    if (flag) {
        drawShadows.unk4D = -1;
    } else {
        drawShadows.unk4D = 1;
    }
}

void loadTlutRelated(void) {
    GXLoadTlut(drawShadows.tlut, GX_TLUT15);
}

void maybeUpdateFunctionPointer(void (*func)(void)) {
    drawShadows.callback20 = func;
}

void fn_800BF048(void (*func)(void)) {
    drawShadows.callback18 = func;
}

void fn_800BF058(void (*func)(StadiumModel* model, Mtx m)) {
    drawShadows.modelCallback = func;
}

ShadowState* ShouldDrawShadows(void) {
    return &drawShadows;
}
