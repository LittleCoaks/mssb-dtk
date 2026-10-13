#include "C3/control/frustum.h"

static const u8 sFaceCorners[6][4] = {
    {0, 3, 7, 4}, {0, 1, 2, 3}, {4, 5, 6, 7}, {2, 1, 5, 6}, {0, 4, 5, 1}, {3, 2, 6, 7},
};

static Frustum sFrustums[4];

static const u8 sEdgeCorners[12][2] = {
    {0, 1}, {1, 2}, {2, 3}, {3, 0}, {4, 5}, {5, 6},
    {6, 7}, {7, 4}, {0, 4}, {1, 5}, {2, 6}, {3, 7},
};

// Separating-axis test of one face of a box against a point set.
// Returns 1 when the face's edge crosses the set, 0 when all points lie
// on one side of the face plane, and -1 otherwise.
s32 checkPlaneIntersection(const Vec* face, const Vec* pts) {
    Vec edge0;
    Vec edge1;
    Vec normal;
    Vec hit;
    Vec rel;
    Vec cross;
    f32 dists[8];
    u8 sides[8];
    f32 planeD;
    f32 t;
    u32 anyPos;
    s32 i;
    s32 k;

    PSVECSubtract(&face[1], &face[0], &edge0);
    PSVECSubtract(&face[2], &face[1], &edge1);
    PSVECCrossProduct(&edge0, &edge1, &normal);
    planeD = PSVECDotProduct(&normal, &face[0]);

    anyPos = 0;
    for (i = 0; i < 8; i++) {
        dists[i] = PSVECDotProduct(&normal, &pts[i]) - planeD;
        if (dists[i] > 0.0f) {
            sides[i] = 4;
            anyPos++;
        } else {
            sides[i] = 8;
        }
    }
    if (anyPos == 0) {
        return 0;
    }

    for (i = 0; i < 12; i++) {
        s32 a = sEdgeCorners[i][0];
        s32 b = sEdgeCorners[i][1];

        if ((sides[a] | sides[b]) != 0xC) {
            continue;
        }
        t = dists[a] / (dists[a] - dists[b]);
        hit.x = pts[a].x + t * (pts[b].x - pts[a].x);
        hit.y = pts[a].y + t * (pts[b].y - pts[a].y);
        hit.z = pts[a].z + t * (pts[b].z - pts[a].z);

        for (k = 0; k < 4; k++) {
            PSVECSubtract(&face[(k + 1) & 3], &face[k], &edge0);
            PSVECSubtract(&hit, &face[k], &rel);
            PSVECCrossProduct(&edge0, &rel, &cross);
            if (PSVECDotProduct(&cross, &normal) < 0.0f) {
                break;
            }
        }
        if (k == 4) {
            return 1;
        }
    }
    return -1;
}

void fn_800B806C(s32 slot, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    Frustum* frustum = &sFrustums[slot];
    f32 invDist = 1.0f / arg7;
    f32 nearZ = arg5;
    f32 farZ = arg6;
    f32 scale = 2.0f * nearZ * farZ;
    f32 zRange = farZ - nearZ;
    f32 l = arg1 * invDist;
    f32 r = arg2 * invDist;
    f32 b = arg3 * invDist;
    f32 t = arg4 * invDist;

    frustum->corners[0].x = l * farZ;
    frustum->corners[0].y = b * farZ;
    frustum->corners[0].z = farZ;
    frustum->corners[1].x = r * farZ;
    frustum->corners[1].y = b * farZ;
    frustum->corners[1].z = farZ;
    frustum->corners[2].x = r * nearZ;
    frustum->corners[2].y = t * nearZ;
    frustum->corners[2].z = nearZ;
    frustum->corners[3].x = l * nearZ;
    frustum->corners[3].y = t * nearZ;
    frustum->corners[3].z = nearZ;
    frustum->corners[4].x = l * farZ;
    frustum->corners[4].y = t * farZ;
    frustum->corners[4].z = farZ;
    frustum->corners[5].x = r * farZ;
    frustum->corners[5].y = t * farZ;
    frustum->corners[5].z = farZ;
    frustum->corners[6].x = r * nearZ;
    frustum->corners[6].y = b * nearZ;
    frustum->corners[6].z = nearZ;
    frustum->corners[7].x = l * nearZ;
    frustum->corners[7].y = b * nearZ;
    frustum->corners[7].z = nearZ;

    frustum->proj[0][0] = scale / (r - l);
    frustum->proj[0][1] = 0.0f;
    frustum->proj[0][2] = 0.0f;
    frustum->proj[0][3] = 0.0f;
    frustum->proj[1][0] = 0.0f;
    frustum->proj[1][1] = scale / (t - b);
    frustum->proj[1][2] = 0.0f;
    frustum->proj[1][3] = 0.0f;
    frustum->proj[2][0] = 0.0f;
    frustum->proj[2][1] = 0.0f;
    frustum->proj[2][2] = (farZ + nearZ) / zRange;
    frustum->proj[2][3] = -scale / zRange;
    frustum->proj[3][0] = 0.0f;
    frustum->proj[3][1] = 0.0f;
    frustum->proj[3][2] = 0.0f;
    frustum->proj[3][3] = 1.0f;
    frustum->nearZ = nearZ;
    frustum->farZ = farZ;
}

s32 checkObjectVisibility(s32 slot, void* box, MtxPtr mtx) {
    Frustum* frustum = &sFrustums[slot];
    Vec worldBox[8];
    Vec clipBox[8];
    u8 flags[8];
    u8 andFlags = 0x3F;
    u8 orFlags = 0;
    s32 i;
    s32 face;
    s32 hitA = 0;
    s32 hitB = 0;

    PSMTXMultVecArray(mtx, box, worldBox, 8);
    PSMTX44MultVecArray(frustum->proj, worldBox, clipBox, 8);

    for (i = 0; i < 8; i++) {
        u8 f = 0;

        if (clipBox[i].x < -1.0f) {
            f |= 0x01;
        }
        if (clipBox[i].x > 1.0f) {
            f |= 0x02;
        }
        if (clipBox[i].y < -1.0f) {
            f |= 0x04;
        }
        if (clipBox[i].y > 1.0f) {
            f |= 0x08;
        }
        if (worldBox[i].z < frustum->nearZ) {
            f |= 0x10;
        }
        if (worldBox[i].z > frustum->farZ) {
            f |= 0x20;
        }
        if (f == 0) {
            return 1;
        }
        flags[i] = f;
        andFlags &= f;
        orFlags |= f;
    }

    if (andFlags == 0x10 || andFlags == 0x20) {
        return 0;
    }
    if ((orFlags & 0x20) == 0) {
        if ((andFlags & 3) == 1 || (andFlags & 3) == 2) {
            return 0;
        }
        if ((andFlags & 0xC) == 4 || (andFlags & 0xC) == 8) {
            return 0;
        }
    }

    for (face = 0; face < 6; face++) {
        Vec faceCorners[4];
        s32 j;

        for (j = 0; j < 4; j++) {
            faceCorners[j] = frustum->corners[sFaceCorners[face][j]];
        }
        if (checkPlaneIntersection(faceCorners, worldBox) > 0) {
            return 1;
        }
        hitA |= 1;
    }
    for (face = 0; face < 6; face++) {
        Vec faceCorners[4];
        s32 j;

        for (j = 0; j < 4; j++) {
            faceCorners[j] = worldBox[sFaceCorners[face][j]];
        }
        if (checkPlaneIntersection(faceCorners, frustum->corners) > 0) {
            return 1;
        }
        hitB |= 1;
    }
    if (hitA == 0) {
        return 2;
    }
    if (hitB == 0) {
        return 2;
    }
    return 0;
}
