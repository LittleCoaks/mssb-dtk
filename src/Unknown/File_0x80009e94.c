#include "Unknown/File_0x80009e94.h"

extern f32 lbl_803CC400;
extern f32 lbl_803CC404;
extern f32 lbl_803CC408;
extern f32 lbl_803CC40C;
extern f32 lbl_803CC410;
extern f32 lbl_803CC414;
extern f32 lbl_803CC418;
extern f32 lbl_803CC41C;
extern u32 lbl_80366188[];

void interpolatePointsUnknown(s32 index, InterpPoint* points, BOOL hasPrev, BOOL hasNext) {
    InterpPoint* a = &points[index - 3];
    InterpPoint* b = &points[index];
    InterpPoint* c = &points[index + 3];
    InterpPoint* prev = &points[index - 2];
    InterpPoint* left = &points[index - 1];
    InterpPoint* right = &points[index + 1];
    InterpPoint* next = &points[index + 2];

    if (hasPrev) {
        prev->x = ((lbl_803CC400 * a->x + lbl_803CC404 * b->x) - c->x) / lbl_803CC408;
        prev->y = ((lbl_803CC400 * a->y + lbl_803CC404 * b->y) - c->y) / lbl_803CC408;
    }

    left->x = ((lbl_803CC404 * b->x + a->x) - c->x) / lbl_803CC404;
    left->y = ((lbl_803CC404 * b->y + a->y) - c->y) / lbl_803CC404;
    right->x = (c->x + (lbl_803CC40C * a->x + lbl_803CC404 * b->x)) / lbl_803CC404;
    right->y = (c->y + (lbl_803CC40C * a->y + lbl_803CC404 * b->y)) / lbl_803CC404;

    if (!hasNext) {
        return;
    }

    next->x = (lbl_803CC400 * c->x + (lbl_803CC40C * a->x + lbl_803CC404 * b->x)) / lbl_803CC408;
    next->y = (lbl_803CC400 * c->y + (lbl_803CC40C * a->y + lbl_803CC404 * b->y)) / lbl_803CC408;
}

void BezierInterpolate(Vec2f* out, const Vec2f* p0, const Vec2f* p1, const Vec2f* p2, const Vec2f* p3, f32 t) {
    f32 t2 = t * t;
    f32 t3 = t2 * t;
    f32 k8t2 = lbl_803CC410 * t2;
    f32 w2 = lbl_803CC414 * t3 + k8t2;
    f32 w1 = lbl_803CC410 * t + (lbl_803CC410 * t3 + lbl_803CC41C * t2);
    f32 w0 = lbl_803CC418 + (lbl_803CC414 * t + (k8t2 - t3));
    f32 x;
    f32 y;

    x = p1->x * w1;
    x = p0->x * w0 + x;
    x = p2->x * w2 + x;
    x = t3 * p3->x + x;
    out->x = x;

    y = p1->y * w1;
    y = p0->y * w0 + y;
    y = p2->y * w2 + y;
    y = t3 * p3->y + y;
    out->y = y;
}

u32 fn_8000A094(u32 value) {
    u32 old = lbl_80366188[0x88 / 4];
    lbl_80366188[0x88 / 4] = value;
    return old;
}
