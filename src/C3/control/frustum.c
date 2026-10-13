#include "C3/control/frustum.h"

u8 lbl_80111670[12][2] = {
    {0, 1}, {1, 2}, {2, 3}, {3, 0}, {4, 5}, {5, 6},
    {6, 7}, {7, 4}, {0, 4}, {1, 5}, {2, 6}, {3, 7},
};

u8 lbl_80111688[6][4] = {
    {0, 3, 7, 4}, {2, 1, 5, 6}, {0, 1, 2, 3}, {7, 6, 5, 4}, {3, 2, 6, 7}, {0, 4, 5, 1},
};

Frustum lbl_803CB1FC[4];

s32 checkObjectVisibility(s32 slot, Vec* box, MtxPtr mtx) {
    Vec face[4];
    Vec worldBox[8];
    Vec clipBox[8];
    Frustum* frustum;
    u8* corners;
    s32 i;
    s32 hit;
    s32 j;
    s32 k;
    s32 result;
    u8 andFlags;
    u8 orFlags;
    u8 f;

    PSMTXMultVecArray(mtx, box, worldBox, 8);
    frustum = &lbl_803CB1FC[slot];
    PSMTX44MultVecArray(frustum->proj, worldBox, clipBox, 8);

    andFlags = 0x3F;
    orFlags = 0;
    i = 0;
    do {
        f = (clipBox[i].x < -1.0f) | ((clipBox[i].x > 1.0f) << 1);
        f |= (clipBox[i].y < -1.0f) << 2;
        f |= (clipBox[i].y > 1.0f) << 3;
        f |= (worldBox[i].z < frustum->nearZ) << 4;
        f |= (worldBox[i].z > frustum->farZ) << 5;
        if (f == 0) {
            return 1;
        }
        andFlags &= f;
        orFlags |= f;
    } while (++i < 8);

    if ((andFlags & 0x30U) == 0x10U || (andFlags & 0x30U) == 0x20U) {
        return 0;
    }
    if (!(orFlags & 0x20)) {
        if ((andFlags & 3U) == 1U || (andFlags & 3U) == 2U) {
            return 0;
        }
        if ((andFlags & 0xCU) == 4U || (andFlags & 0xCU) == 8U) {
            return 0;
        }
    }

    corners = lbl_80111688[0];
    hit = 0;
    for (j = 6; j != 0; j--) {
        face[0] = frustum->corners[corners[0]];
        face[1] = frustum->corners[corners[1]];
        face[2] = frustum->corners[corners[2]];
        face[3] = frustum->corners[corners[3]];
        corners += 4;
        result = checkPlaneIntersection(face, worldBox);
        if (result > 0) {
            return 1;
        }
        hit |= result;
    }
    if (hit == 0) {
        return 2;
    }

    corners = lbl_80111688[0];
    hit = 0;
    for (k = 0; k < 6; k++) {
        face[0] = worldBox[corners[0]];
        face[1] = worldBox[corners[1]];
        face[2] = worldBox[corners[2]];
        face[3] = worldBox[corners[3]];
        corners += 4;
        result = checkPlaneIntersection(face, frustum->corners);
        if (result > 0) {
            return 1;
        }
        hit |= result;
    }
    result = 0;
    if (hit == 0) {
        result = 2;
    }
    return result;
}

void fn_800B806C(s32 slot, f32 bottom, f32 top, f32 left, f32 right, f32 nearZ, f32 farZ, f32 dist) {
    f32 invDist = 1.0f / dist;
    f32 l = left * invDist;
    f32 r = right * invDist;
    f32 b = bottom * invDist;
    f32 t = top * invDist;

    lbl_803CB1FC[slot].nearZ = nearZ;
    lbl_803CB1FC[slot].farZ = farZ;

    lbl_803CB1FC[slot].proj[0][0] = (2.0f * dist) / (right - left);
    lbl_803CB1FC[slot].proj[0][1] = 0.0f;
    lbl_803CB1FC[slot].proj[0][2] = 0.0f;
    lbl_803CB1FC[slot].proj[0][3] = 0.0f;
    lbl_803CB1FC[slot].proj[1][0] = 0.0f;
    lbl_803CB1FC[slot].proj[1][1] = (2.0f * dist) / (top - bottom);
    lbl_803CB1FC[slot].proj[1][2] = 0.0f;
    lbl_803CB1FC[slot].proj[1][3] = 0.0f;
    lbl_803CB1FC[slot].proj[2][0] = 0.0f;
    lbl_803CB1FC[slot].proj[2][1] = 0.0f;
    lbl_803CB1FC[slot].proj[2][2] = (farZ + nearZ) / (farZ - nearZ);
    lbl_803CB1FC[slot].proj[2][3] = -2.0f * (farZ * nearZ) / (farZ - nearZ);
    lbl_803CB1FC[slot].proj[3][0] = 0.0f;
    lbl_803CB1FC[slot].proj[3][1] = 0.0f;
    lbl_803CB1FC[slot].proj[3][2] = 1.0f;
    lbl_803CB1FC[slot].proj[3][3] = 0.0f;

    lbl_803CB1FC[slot].corners[0].x = lbl_803CB1FC[slot].corners[4].x = l * farZ;
    lbl_803CB1FC[slot].corners[3].x = lbl_803CB1FC[slot].corners[7].x = l * nearZ;
    lbl_803CB1FC[slot].corners[1].x = lbl_803CB1FC[slot].corners[5].x = r * farZ;
    lbl_803CB1FC[slot].corners[2].x = lbl_803CB1FC[slot].corners[6].x = r * nearZ;
    lbl_803CB1FC[slot].corners[0].y = lbl_803CB1FC[slot].corners[1].y = b * farZ;
    lbl_803CB1FC[slot].corners[2].y = lbl_803CB1FC[slot].corners[3].y = b * nearZ;
    lbl_803CB1FC[slot].corners[4].y = lbl_803CB1FC[slot].corners[5].y = t * farZ;
    lbl_803CB1FC[slot].corners[6].y = lbl_803CB1FC[slot].corners[7].y = t * nearZ;
    lbl_803CB1FC[slot].corners[0].z = lbl_803CB1FC[slot].corners[1].z = lbl_803CB1FC[slot].corners[4].z = lbl_803CB1FC[slot].corners[5].z = farZ;
    lbl_803CB1FC[slot].corners[2].z = lbl_803CB1FC[slot].corners[3].z = lbl_803CB1FC[slot].corners[6].z = lbl_803CB1FC[slot].corners[7].z = nearZ;
}

s32 checkPlaneIntersection(Vec* face, Vec* pts) {
    u8 sides[8];
    Vec hit;
    f32 dists[8];
    Vec v[4];
    Vec cross[4];
    f32 planeD;
    f32 dist;
    f32 denom;
    f32 t;
    s32 anyNeg;
    s32 i;
    s32 k;
    s32 a;
    s32 b;
    u8* edge;

    PSVECSubtract(&face[1], &face[0], &v[0]);
    PSVECSubtract(&face[2], &face[1], &v[1]);
    PSVECCrossProduct(&v[0], &v[1], &v[2]);
    planeD = PSVECDotProduct(&v[2], &face[0]);

    anyNeg = 0;
    for (i = 0; i < 8; i++) {
        dist = PSVECDotProduct(&v[2], &pts[i]) - planeD;
        dists[i] = dist;
        sides[i] = ((dist < 0.0f) << 3) | ((dist > 0.0f) << 2);
        anyNeg |= dist < 0.0f;
    }
    if (anyNeg == 0) {
        return 0;
    }

    edge = lbl_80111670[0];
    for (i = 0; i < 12; i++) {
        a = edge[0];
        b = edge[1];
        edge += 2;
        if ((sides[a] | sides[b]) != 0xC) {
            continue;
        }
        denom = dists[a] - dists[b];
        if (denom) {
            t = dists[a] / denom;
            hit.x = t * (pts[b].x - pts[a].x) + pts[a].x;
            hit.y = t * (pts[b].y - pts[a].y) + pts[a].y;
            hit.z = t * (pts[b].z - pts[a].z) + pts[a].z;

            PSVECSubtract(&face[0], &hit, &v[0]);
            PSVECSubtract(&face[1], &hit, &v[1]);
            PSVECSubtract(&face[2], &hit, &v[2]);
            PSVECSubtract(&face[3], &hit, &v[3]);
            PSVECCrossProduct(&v[0], &v[1], &cross[0]);
            PSVECCrossProduct(&v[1], &v[2], &cross[1]);
            PSVECCrossProduct(&v[2], &v[3], &cross[2]);
            PSVECCrossProduct(&v[3], &v[0], &cross[3]);

            for (k = 0; k < 4; k++) {
                if (PSVECDotProduct(&cross[k], &cross[(k + 1) & 3]) < 0.0f) {
                    goto next;
                }
            }
            return 1;
        }
    next:;
    }
    return -1;
}
