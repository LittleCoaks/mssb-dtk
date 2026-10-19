#include "Unknown/File_0x8000a1e8.h"
#include "Unknown/File_0x80009e94.h"

void interpolatePointsBezier_Vec2s(void *dst, const s16 *p0, const s16 *p1, const s16 *p2, const s16 *p3, s32 mode, f32 t) {
    InterpPoint pts[10];

    pts[0].x = p0[2];
    pts[0].y = p0[3];
    pts[3].x = p1[2];
    pts[3].y = p1[3];
    pts[6].x = p2[2];
    pts[6].y = p2[3];
    pts[9].x = p3[2];
    pts[9].y = p3[3];

    if (mode == 0) {
        interpolatePointsUnknown(3, pts, TRUE, FALSE);
        BezierInterpolate(dst, (Vec2f*)&pts[0], (Vec2f*)&pts[1], (Vec2f*)&pts[2], (Vec2f*)&pts[3], t);
    } else if (mode == 1) {
        interpolatePointsUnknown(3, pts, TRUE, FALSE);
        interpolatePointsUnknown(6, pts, FALSE, TRUE);
        BezierInterpolate(dst, (Vec2f*)&pts[3], (Vec2f*)&pts[4], (Vec2f*)&pts[5], (Vec2f*)&pts[6], t);
    } else {
        interpolatePointsUnknown(6, pts, FALSE, TRUE);
        BezierInterpolate(dst, (Vec2f*)&pts[6], (Vec2f*)&pts[7], (Vec2f*)&pts[8], (Vec2f*)&pts[9], t);
    }
}
