#include "static/UnknownHomes_Static.h"
#include "Dolphin/mtx.h"
#include "Dolphin/mtxext.h"
#include "stl/math.h"

/* Defined with an int-width result, while every caller (via
 * Unknown/File_0x800527c4.h) sees a u8 return and truncates it; the header is
 * deliberately not included here so both views can coexist. */
BOOL isWorldPosOnScreen(Vec* pos) {
    Vec v;

    v.x = pos->x;
    v.y = -fabs(pos->y);
    v.z = pos->z;
    PSMTXMultVec(cameras[0].view, &v, &v);
    PSMTX44MultVec(cameras[0].proj, &v, &v);
    return !(v.x > 1.0f | v.x < -1.0f | v.y > 1.0f | v.y < -1.0f | v.z > 0.0f | v.z < -1.0f);
}
