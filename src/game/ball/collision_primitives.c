#include "game/ball/collision_primitives.h"
#include "header_rep_data.h"
#include "Dolphin/stl.h"
#define SQRT2_LINKAGE static
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/stadium/stadium_framework.h"
#include "Unknown/File_0x800b0724.h"

Vec upVec = {0.f, 1.f, 0.f};
Vec Zneg = {0.f, 0.f, 0.f};
Vec UpVec = {0.f, 1.f, 0.f};
Vec lbl_3_data_21C = {0.f, 0.f, 0.f};

#define SAME_SIDE(a, b, c, d) \
    ((((*(u32*)&(a)) & (*(u32*)&(b))) | ((*(u32*)&(c)) & (*(u32*)&(d)))) & 0x80000000)

BALL_COLLISION_TYPE fn_3_8D4(VecSrcDst* inVec, CollisionStruct* outCollision);

// .text:0x00000914 size:0x158 mapped:0x8063F9A8
BALL_COLLISION_TYPE checkCollision(VecSrcDst* inVec, CollisionStruct* outCollision, int collisionCheckType,
                                   BOOL useBallCoords) {
    VecSrcDst p;
    int objectIndex;
    BALL_COLLISION_TYPE ret = 0;
    if (collisionCheckType) {
        if (useBallCoords && (g_d_GameSettings.StadiumID == STADIUM_ID_WARIO_PALACE ||
                              g_d_GameSettings.StadiumID == STADIUM_ID_YOHSI_PARK ||
                              g_d_GameSettings.StadiumID == STADIUM_ID_DK_JUNGLE)) {
            memcpy(&p.src, &g_Ball.AtBat_Contact_BallPos, sizeof(p.src));
            memcpy(&p.dst, &g_Ball.pastCoordinates[4], sizeof(p.dst));
            p.src.y *= -1.f;
            p.dst.y *= -1.f;
        } else {
            memcpy(&p, inVec, sizeof(p));
        }
        ret = checkStatiumHazardCollisions(&p, outCollision, (Vec*)&objectIndex);
        if (ret) {
            if (collisionCheckType == 2 && (ret & BALL_COLLISION_TYPE_FOUL)) {
                ret = BALL_COLLISION_TYPE_NONE;
            } else {
                processStadiumObjectFunction(g_d_GameSettings.StadiumID, objectIndex, ret, outCollision);
            }
        }
    }
    if (collisionCheckType != 3) {
        ret = didCollideWithBoundingBoxes(inVec, outCollision, g_UNK_StadiumDetails.pCollisionBoxes,
                                          g_UNK_StadiumDetails.numCollisionBoxes);
    }
    return ret;
}

// .text:0x00000A6C size:0x384 mapped:0x8063FB00
BALL_COLLISION_TYPE checkStatiumHazardCollisions(VecSrcDst* inVec, CollisionStruct* outCollision, Vec* v) {
    TriangleCollisionStruct collisionData;
    Vec diff[4];
    Mtx inverse;
    Mtx lookAt;
    Vec boxMin, boxMax;
    u8 flags[256];
    u8* flag;
    int count = stadiumObjectCollision.boundingBoxCount;
    int i, j;
    void* hazardData;
    TriangleGroup* group;
    f32 length;
    BOOL allOutside;

    memset(flags, 1, count);
    allOutside = TRUE;
    i = stadiumObjectCollision.boundingBoxCount;
    flag = flags;
    while (i--) {
        CopyOutVecSrcDst(i, &boxMin, &boxMax);
        VECSubtract(&inVec->src, &boxMin, &diff[0]);
        VECSubtract(&boxMax, &inVec->src, &diff[1]);
        VECSubtract(&inVec->dst, &boxMin, &diff[2]);
        VECSubtract(&boxMax, &inVec->dst, &diff[3]);
        if (!SAME_SIDE(diff[0].x, diff[2].x, diff[1].x, diff[3].x) &&
            !SAME_SIDE(diff[0].y, diff[2].y, diff[1].y, diff[3].y) &&
            !SAME_SIDE(diff[0].z, diff[2].z, diff[1].z, diff[3].z)) {
            *flag = FALSE;
            allOutside = FALSE;
        }
        flag++;
    }
    if (allOutside) return BALL_COLLISION_TYPE_NONE;

    makeLookAtMatrix(lookAt, &inVec->src, &UpVec, &inVec->dst);
    length = dolsqrtf2(VECSquareDistance(&inVec->dst, &inVec->src));
    collisionData.distance = length;
    collisionData.collisionDistance = length;
    collisionData.collisionType = BALL_COLLISION_TYPE_NONE;

    flag = flags;
    i = stadiumObjectCollision.boundingBoxCount;
    while (i--) {
        if (*flag++ != FALSE) continue;
        j = calculateHazardDataAddress(i, &hazardData);
        while (j--) {
            group = getStadiumHazardTriangles(g_d_GameSettings.StadiumID, ((int*)hazardData)[j],
                                              collisionData.mtx1);
            if (group != NULL) {
                PSMTXConcat(lookAt, collisionData.mtx1, collisionData.mtx1);
                if (((BOOL (*)(TriangleCollisionStruct*, TriangleGroup*))checkTriangleCollisions)(
                        &collisionData, *(TriangleGroup**)((u8*)group + 8))) {
                    *(int*)v = ((int*)hazardData)[j];
                }
            }
        }
    }
    if (collisionData.collisionType != BALL_COLLISION_TYPE_NONE) {
        PSMTXCopy(lookAt, collisionData.mtx1);
        PSMTXInverse(collisionData.mtx1, inverse);
        lbl_3_data_21C.z = -collisionData.collisionDistance;
        MTXMultVec(inverse, &lbl_3_data_21C, &outCollision->position);
        PSMTXTranspose(collisionData.mtx1, inverse);
        MTXMultVec(inverse, &collisionData.normal, &outCollision->normal);
        VECNormalize(&outCollision->normal, &outCollision->normal);
        return collisionData.collisionType;
    }
    return BALL_COLLISION_TYPE_NONE;
}

// .text:0x00000DF0 size:0x2F0 mapped:0x8063FE84
BALL_COLLISION_TYPE didCollideWithBoundingBoxes(VecSrcDst* inVec, CollisionStruct* outCollision, CollisionBox* boxes,
                                                int boxCount) {
    TriangleCollisionStruct collisionData;
    Vec diff[4];
    Mtx inverse;
    u8 flags[256];
    u8* flag;
    CollisionBox* box;
    AABB_Box* bounds = boxes[0].boundingBox;
    f32 length;
    int i;
    BOOL allOutside;

    memset(flags, 1, (s16)boxCount);
    allOutside = TRUE;
    i = (s16)boxCount;
    flag = flags;
    do {
        VECSubtract(&inVec->src, &bounds->a, &diff[0]);
        VECSubtract(&bounds->b, &inVec->src, &diff[1]);
        VECSubtract(&inVec->dst, &bounds->a, &diff[2]);
        VECSubtract(&bounds->b, &inVec->dst, &diff[3]);
        if (!SAME_SIDE(diff[0].x, diff[2].x, diff[1].x, diff[3].x) &&
            !SAME_SIDE(diff[0].y, diff[2].y, diff[1].y, diff[3].y) &&
            !SAME_SIDE(diff[0].z, diff[2].z, diff[1].z, diff[3].z)) {
            *flag = FALSE;
            allOutside = FALSE;
        }
        flag++;
        bounds++;
    } while (--i);
    if (allOutside) return BALL_COLLISION_TYPE_NONE;

    makeLookAtMatrix(collisionData.mtx1, &inVec->src, &upVec, &inVec->dst);
    length = dolsqrtf2(VECSquareDistance(&inVec->dst, &inVec->src));
    collisionData.distance = length;
    collisionData.collisionDistance = length;
    collisionData.collisionType = BALL_COLLISION_TYPE_NONE;
    flag = flags;
    box = boxes + 1;
    i = (s16)boxCount;
    do {
        if (*flag++ == FALSE) {
            checkTriangleCollisions(&collisionData, (TriangleGroup*)box->boundingBox);
        }
        box++;
    } while (--i);
    if (collisionData.collisionType != BALL_COLLISION_TYPE_NONE) {
        PSMTXInverse(collisionData.mtx1, inverse);
        Zneg.z = -collisionData.collisionDistance;
        MTXMultVec(inverse, &Zneg, &outCollision->position);
        PSMTXTranspose(collisionData.mtx1, inverse);
        MTXMultVec(inverse, &collisionData.normal, &outCollision->normal);
        VECNormalize(&outCollision->normal, &outCollision->normal);
        return collisionData.collisionType;
    }
    return BALL_COLLISION_TYPE_NONE;
}

// .text:0x000010E0 size:0x3C4 mapped:0x80640174
bool checkTriangleCollisions(TriangleCollisionStruct* collisionData, TriangleGroup* _triangleGroup) {
#define O_GROUP ((TriangleGroup*)_triangleGroup)
#define O_TRI ((CollisionTriangle*)_triangleGroup)

    Vec tri[3];
    Vec dist[3];
    u32 remainingTriangles;
    u32 didVecPassTriangle;
    u32 isBackwardsTriangle;

    bool ret = false;
    f32 d;
    while (true) {
        bool isList;
        remainingTriangles = O_GROUP->count;
        if (remainingTriangles == 0)
            break;

        isList = O_GROUP->isTriangleList;
        // this should be reassigned to r24? but they're different types?
        // i hope it's not a union
        O_TRI = O_GROUP->tris;
        if (!isList) {
            // grou of 3 verts to make up a triangle
            do {
                MTXMultVec(collisionData->mtx1, &O_TRI[0].trianglePoint, &tri[00]);
                MTXMultVec(collisionData->mtx1, &O_TRI[1].trianglePoint, &tri[01]);
                MTXMultVec(collisionData->mtx1, &O_TRI[2].trianglePoint, &tri[02]);
                didVecPassTriangle = tri[00].x * tri[01].y - tri[01].x * tri[00].y >= 0;
                didVecPassTriangle &= tri[01].x * tri[02].y - tri[02].x * tri[01].y >= 0;
                didVecPassTriangle &= tri[02].x * tri[00].y - tri[00].x * tri[02].y >= 0;
                if (didVecPassTriangle) {
                    VECSubtract(&tri[01], &tri[00], &dist[0]);
                    VECSubtract(&tri[02], &tri[01], &dist[1]);
                    VECCrossProduct(&dist[0], &dist[1], &dist[2]);
                    d = -VECDotProduct(&dist[2], &tri[00]) / dist[2].z;
                    if (d >= 0.f && collisionData->collisionDistance > d) {
                        collisionData->collisionDistance = d;
                        ret = true;
                        collisionData->collisionType = O_TRI[2].collisionType;
                        collisionData->normal = dist[2];
                    }
                }
                O_TRI += 3;
            } while (--remainingTriangles);
        } else {
            // the first 3 verts describe a triangle, after that each new vert replaces the oldest vert to make a
            // triangle fan
            isBackwardsTriangle = false;
            MTXMultVec(collisionData->mtx1, &O_TRI[0].trianglePoint, &tri[00]);
            MTXMultVec(collisionData->mtx1, &O_TRI[1].trianglePoint, &tri[01]);
            O_TRI += 2;
            do {
                MTXMultVec(collisionData->mtx1, &O_TRI->trianglePoint, &tri[02]);
                dist[0].x = tri[00].x * tri[01].y - tri[01].x * tri[00].y;
                dist[0].y = tri[01].x * tri[02].y - tri[02].x * tri[01].y;
                dist[0].z = tri[02].x * tri[00].y - tri[00].x * tri[02].y;

                if (isBackwardsTriangle) {
                    didVecPassTriangle = dist[0].x <= 0.f & dist[0].y <= 0.f & dist[0].z <= 0.f;
                } else {
                    didVecPassTriangle = dist[0].x >= 0.f & dist[0].y >= 0.f & dist[0].z >= 0.f;
                }

                if (didVecPassTriangle) {
                    VECSubtract(&tri[01], &tri[00], &dist[0]);
                    VECSubtract(&tri[02], &tri[01], &dist[1]);
                    VECCrossProduct(&dist[0], &dist[1], &dist[2]);
                    d = -VECDotProduct(&dist[2], &tri[00]) / dist[2].z;
                    if (d >= 0.f && collisionData->collisionDistance > d) {
                        collisionData->collisionDistance = d;
                        collisionData->collisionType = O_TRI[0].collisionType;
                        if (!isBackwardsTriangle) {
                            collisionData->normal = dist[2];
                        } else {
                            collisionData->normal.x = -dist[2].x;
                            collisionData->normal.y = -dist[2].y;
                            collisionData->normal.z = -dist[2].z;
                        }
                        ret = true;
                    }
                }
                tri[00] = tri[01];
                tri[01] = *&tri[02];
                isBackwardsTriangle ^= 1;
                O_TRI++;
            } while (--remainingTriangles);
        }
    }

    return ret;
}

BALL_COLLISION_TYPE fn_3_8D4(VecSrcDst* inVec, CollisionStruct* outCollision) {
    if (g_UNK_StadiumDetails.pCollisionBoxes_778 != NULL) {
        return didCollideWithBoundingBoxes(inVec, outCollision, g_UNK_StadiumDetails.pCollisionBoxes_778,
                                           g_UNK_StadiumDetails.numCollisionBoxes_77C);
    }
    return BALL_COLLISION_TYPE_NONE;
}
