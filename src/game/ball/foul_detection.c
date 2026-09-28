#define SQRT2_LINKAGE static
#include "game/ball/foul_detection.h"
#define REP_HEADER_DATA_FN getRepHeaderData_foulDetection
#include "header_rep_data.h"

#include "game/UnknownHomes_Game.h"
#include "game/ball/collision_primitives.h"

extern VecXZ base_MoundCoordinates[5];

// .text:0x000B7E44 size:0xAC mapped:0x806F6ED8
// 0 = not near the wall, 1/2 = past the near/far depth threshold. The thresholds grow toward
// center field (0x400). Zone meanings are inferred from the fielder.c callers (wall-bounce positioning).
int outfieldWallProximityZone(f32 dist, sAng angle) {
    s16 diff;
    f32 scaled;

    if (angle < 0x1e0 || angle > 0x620) {
        return 0;
    }

    diff = 0x200 - __abs(angle - 0x400);
    scaled = 0.06 * diff;

    if (63.0f + scaled < dist) {
        return 2;
    }
    if (55.0f + scaled < dist) {
        return 1;
    }
    return 0;
}

// .text:0x000B7E10 size:0x34 mapped:0x806F6EA4
BOOL foul_checkIfFoul(f32 x, f32 z) {
    if (z < x - 0.15f) {
        return TRUE;
    }
    return z < -x - 0.15f;
}

// .text:0x000B7DD8 size:0x38 mapped:0x806F6E6C
BOOL foul_ifBallConsideredPastTheBases(f32 x, f32 z) {
    f32 secondBaseZ = base_MoundCoordinates[2].z;

    if (z > x + secondBaseZ) {
        return TRUE;
    }
    return z > -x + secondBaseZ;
}

// .text:0x000B7D6C size:0x6C mapped:0x806F6E00
BOOL foul_isBallWithin3mFair(f32 x, f32 z) {
    if (x > 0.0f) {
        if (z > x - 3.0f && z < x + 3.0f) {
            return TRUE;
        }
    } else {
        if (z > -x - 3.0f && z < 3.0f - x) {
            return TRUE;
        }
    }
    return FALSE;
}

// .text:0x000B7CDC size:0x90 mapped:0x806F6D70
BOOL isCoordinateUncatchableTerrain(f32 x, f32 z) {
    VecSrcDst vec;
    CollisionStruct hit;
    u32 type;

    vec.src.x = x;
    vec.src.y = -100.0f;
    vec.src.z = z;
    vec.dst.x = x;
    vec.dst.y = 100.0f;
    vec.dst.z = z;

    type = checkCollision(&vec, &hit, 0, 0) & 0x7F;
    if (!(type != BALL_COLLISION_TYPE_GRASS && type != BALL_COLLISION_TYPE_DIRT &&
          type != BALL_COLLISION_TYPE_ROUGH_TERRAIN && type != BALL_COLLISION_TYPE_WATER &&
          type != 0x32)) {
        return FALSE;
    }
    return TRUE;
}

// .text:0x000B7C2C size:0xB0 mapped:0x806F6CC0
BOOL checkFielderCollision(InMemFielder* fielder, VecXYZ* pos) {
    VecSrcDst vec;
    CollisionStruct hit;
    u32 type;

    vec.src.x = fielder->pos.x;
    vec.src.y = -fielder->pos.y;
    vec.src.z = fielder->pos.z;
    vec.dst.x = pos->x;
    vec.dst.y = -pos->y;
    vec.dst.z = pos->z;

    type = checkCollision(&vec, &hit, 0, 0) & 0x7F;
    if (!(type != BALL_COLLISION_TYPE_WALL && type != BALL_COLLISION_TYPE_STRUCTURE &&
          type != BALL_COLLISION_TYPE_FOUL_LINE && type != BALL_COLLISION_TYPE_UNCLIMBABLE_WALL &&
          type != BALL_COLLISION_TYPE_PIT_WALL && type != BALL_COLLISION_TYPE_PIT &&
          type != BALL_COLLISION_TYPE_CHOMP_HAZARD)) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x000B79AC size:0x280 mapped:0x806F6A40
// Distance from (x, z) to the first collision along the ray from home plate through that point.
f32 distanceFromPointToWall(f32 x, f32 z) {
    f32 dist = dolsqrtf2(x * x + z * z);
    VecSrcDst vec;
    CollisionStruct hit;
    f32 scale;
    f32 hitDist;

    if (dist == 0.0f) {
        return 100.0f;
    }

    scale = 200.0f / dist;
    vec.src.x = 0.0f;
    vec.src.y = -0.5f;
    vec.src.z = 0.0f;
    vec.dst.x = x * scale;
    vec.dst.y = -0.5f;
    vec.dst.z = z * scale;

    checkCollision(&vec, &hit, 0, 0);
    hitDist = dolsqrtf2(hit.position.x * hit.position.x + hit.position.z * hit.position.z);
    return hitDist - dist;
}
