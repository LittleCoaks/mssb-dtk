#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_ballContactBurst
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/ball/collision_primitives.h"
#include "Unknown/File_0x8004ad54.h"
#include "Unknown/File_0x8004c094.h"
#include "Unknown/File_0x80064344.h"
#include "Dolphin/vec.h"

typedef struct {
    void* texture;
    s32 _04[15];
    u32 color;
    s32 _44[3];
} Rep3C80Burst;

typedef struct {
    void* texture;
    s32 _04[20];
} Rep3C80Emitter;

extern struct { void* _00; void* texture; } lbl_3_common_bss_35154;
extern u8 lbl_800FC0FC[][3];
extern void fn_8002955C(VecXYZ*, int, void*);
extern void fn_80030D88(VecXYZ*, VecXYZ*, void*, int);


// This unit's .data (0x27D58-0x27EAC, dtk symbol lbl_3_data_27D58). MWCC pools
// file-static data and addresses each object as base+offset from a single
// register; the .data range must be split into this unit before it can be
// linked as Matching.
static Rep3C80Burst sBurst0 = {0, {4, 10, 70000, 30000, 78000, 30, 10, 109000, 101000, 0, 30, 12800000, 0, 0, 0}, 0, {0xFFFFFF00, 0, 75000}};
static Rep3C80Emitter sEmitter0 = {0, {2, 30, 20, 40, 10000, 20000, 0, 0, 50000, 60000, 10, 0xFF000080, 16, 16, 1, 0, 0, 0, 0, 0}};
static Rep3C80Burst sBurst1 = {0, {4, 10, 80000, 90000, 50000, 30, 10, 104000, 105999, 0, 60, 12800000, 10000000, 1000000, 6000000}, 0x3C3C3C00, {0, 0, 0}};
static Rep3C80Emitter sEmitter1 = {0, {29, 15, 20, 30, 13000, 15000, -3000000, 3000000, 50000, 60000, 0, -1, 5, 10, 0, 0, 0, 0, 0, 1}};
static s32 sSpeedThresholds[3] = {30000, 30000, 24000};

void fn_3_15F648(int collisionType, int animByte, VecXYZ* position, VecXYZ* velocity);

// .text:0x0015F648 size:0x22C mapped:0x8079E6DC
void fn_3_15F648(int collisionType, int animByte, VecXYZ* position, VecXYZ* velocity) {
    int burstType;
    f32 speed;

    switch (collisionType) {
    case BALL_COLLISION_TYPE_WATER:
        handleBallRollInWater((Vec*)position, (Vec*)velocity);
        return;
    default:
        break;
    }

    if (animByte == 1) {
        speed = PSVECMag((Vec*)velocity);
        if (speed >= (f32)sSpeedThresholds[1] / 100000.0f) {
            sEmitter0.texture = lbl_3_common_bss_35154.texture;
            sBurst1.texture = lbl_3_common_bss_35154.texture;
            fn_8002955C(position, 0, &sEmitter0);
            fn_80030D88(position, velocity, &sBurst1, 5);
        }
        return;
    }

    burstType = stadiumCollisionRelated(g_d_GameSettings.StadiumID, collisionType);
    speed = PSVECMag((Vec*)velocity);
    if (speed >= (f32)sSpeedThresholds[0] / 100000.0f) {
        Rep3C80Burst* burst = &sBurst0;
        burst->texture = lbl_3_common_bss_35154.texture;
        burst->color = ((u32)lbl_800FC0FC[burstType][0] << 24) |
                       (((u32)lbl_800FC0FC[burstType][1] & 0xFF) << 16) |
                       ((u32)lbl_800FC0FC[burstType][2] << 8);
        fn_80031CA4((Vec*)position, (ParticleBurstParams*)burst);
    }

    speed = PSVECMag((Vec*)velocity);
    if (speed >= (f32)sSpeedThresholds[2] / 100000.0f) {
        switch (burstType) {
        case 1:
        case 3:
        case 7:
            sEmitter1.texture = lbl_3_common_bss_35154.texture;
            fn_8002955C(position, 0, &sEmitter1);
            break;
        }
    }
}
