#define SQRT2_LINKAGE static
#include "game/batting/star_swing_peach_daisy.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "Dolphin/rand.h"
#include "Dolphin/stl.h"
#include "static/UnknownHomes_Static.h"

extern s16 pitchConstantsArray[][7];

// The part of the shared effects block (lbl_3_common_bss_35154, used by ~30 units) that this
// unit reads: a pointer-sized value at +0x4, and an in-use flag at +0x464.
typedef struct _StarSwingSharedEffectsBlock {
    u8 _000[0x4];
    u32 unk4;
    u8 _008[0x464 - 0x8];
    s16 unk464;
    u8 _466[0x480 - 0x466];
} StarSwingSharedEffectsBlock;

extern StarSwingSharedEffectsBlock lbl_3_common_bss_35154;

extern void fn_8002CDD0(VecXYZ* pos);
extern void fn_8002DC68(VecXYZ* pos);
extern void fn_8002CE4C(VecXYZ* pos, VecXYZ* vel, StarSwingEntryB* entry);
extern void fn_8002DCE4(VecXYZ* pos, VecXYZ* vel, StarSwingEntryA* entry);

StarSwingPeachDaisyData lbl_3_data_26F78 = {
    {
        {
            // entryA[0][0]
            {
                0, 22, 0x80, 0, 50000, 100000, 10, 0x20, 0x20, -3000000, 6000000, -4500000, 4500000, 0x80, -100000, 0, 0, 0
            },
            // entryA[0][1]
            {
                0, 40, 0x80, 0, 70000, 90000, 10, 0x20, 0x20, -3000000, 6000000, -4500000, 4500000, 0x80, -100000, 0, -4500000, 4500000
            },
        },
        {
            // entryA[1][0]
            {
                0, 22, 0x100, 0, 80000, 150000, 50, 0x20, 0x20, -6000000, 6000000, -4500000, 4500000, 0x20, 6000000, 9000000, 0, 0
            },
            // entryA[1][1]
            {
                0, 40, 0x100, 0, 80000, 150000, 50, 0x20, 0x20, -6000000, 6000000, -4500000, 4500000, 0x20, 6000000, 9000000, -4500000, 4500000
            },
        },
    },
    200000,
};

StarSwingEntryB lbl_3_data_2709C[2] = {
    // entryB[0]
    {
        0, 40, 0x100, 30, 10000, 90000, 100000, 60000, 70000, 30, 40, 0x20, 0x20, 80000, 150000, -6000000, 6000000, -4500000, 4500000, 2000000, 3000000, -4500000, 4500000, 400000, 800000, 70000, 80000, -100000, -120000, 25000, 50000, 0, 25000
    },
    // entryB[1]
    {
        0, 40, 0x80, 30, 10000, 90000, 100000, 80000, 90000, 20, 30, 0x80, 0x80, 70000, 90000, -3000000, 6000000, -4500000, 4500000, 1500000, 2000000, -4500000, 4500000, 400000, 800000, 70000, 80000, -100000, -120000, 25000, 50000, 0, 25000
    },
};



// .text:0x0015B79C size:0x304 mapped:0x8079A830
void fn_3_15B79C(BOOL side) {
    VecXYZ pos, vel, accel;
    f32 endZ = (f32)lbl_3_data_26F78.entryA[0][side].unk38 / 100000.0f;

    memcpy(&pos, &g_Pitcher.ballCurrentPosition, sizeof(VecXYZ));
    memcpy(&vel, &g_Pitcher.ballVelocity, sizeof(VecXYZ));
    memcpy(&accel, &g_Pitcher.pitchCurveVeloV1, sizeof(VecXYZ));

    while (pos.z > endZ) {
        fn_3_15C024(&pos, &vel, &accel, TRUE);
    }

    pos.y = -pos.y;

    if (side) {
        fn_8002CDD0(&pos);
    } else {
        fn_8002DC68(&pos);
    }
}

// .text:0x0015BAA0 size:0x560 mapped:0x8079AB34
void fn_3_15BAA0(int side) {
    StarSwingPeachDaisyData* data = &lbl_3_data_26F78;
    VecXYZ vA, vB, accel;
    int mode;
    int i;

    if (g_GameLogic.bOD_framesInLiveBallScene >= 0) {
        mode = 2;
    } else {
        mode = g_Ball.framesSinceHit > 0;
    }

    switch (mode) {
    case 0:
        if (lbl_3_common_bss_35154.unk464 != 0) {
            break;
        }

        {
            f32 endZ = (f32)data->entryA[0][side].unk38 / 100000.0f;

            memcpy(&vA, &g_Pitcher.ballCurrentPosition, sizeof(VecXYZ));
            memcpy(&vB, &g_Pitcher.ballVelocity, sizeof(VecXYZ));
            memcpy(&accel, &g_Pitcher.pitchCurveVeloV1, sizeof(VecXYZ));

            data->entryA[0][side].frameCount = 0;
            while (vA.z > endZ) {
                fn_3_15C024(&vA, &vB, &accel, FALSE);
                data->entryA[0][side].frameCount++;
            }

            vA.y = -vA.y;
            vB.x = g_Pitcher.ballCurrentPosition.x;
            vB.y = -g_Pitcher.ballCurrentPosition.y;
            vB.z = g_Pitcher.ballCurrentPosition.z;

            if (side) {
                lbl_3_data_2709C[1].unk0 = lbl_3_common_bss_35154.unk4;
                lbl_3_data_2709C[1].frames = data->entryA[0][side].frameCount;
                fn_8002CE4C(&vB, &vA, &lbl_3_data_2709C[1]);
            } else {
                data->entryA[0][side].unk0 = lbl_3_common_bss_35154.unk4;
                fn_8002DCE4(&vB, &vA, &data->entryA[0][side]);
            }
        }
        break;

    case 1:
    case 2:
        if (side) {
            lbl_3_data_2709C[0].unk0 = lbl_3_common_bss_35154.unk4;
            memcpy(&vA, &g_Ball.AtBat_Contact_BallPos, sizeof(VecXYZ));

            i = 0;
            while (g_Ball.physicsSubstruct.futureCoordsAndDist[i + 1].pos.y >=
                   g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.y) {
                i++;
            }

            {
                f32 thresh = (f32)data->unk120 / 100000.0f;
                while (g_Ball.physicsSubstruct.futureCoordsAndDist[i + 1].pos.y >= thresh) {
                    i++;
                }
            }

            lbl_3_data_2709C[0].frames = i;
            memcpy(&vB, &g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos, sizeof(VecXYZ));

            vA.y = -vA.y;
            vB.y = -vB.y;
            fn_8002CE4C(&vA, &vB, &lbl_3_data_2709C[0]);
        } else {
            f32 lo, range;

            data->entryA[1][side].unk0 = lbl_3_common_bss_35154.unk4;
            lo = (f32)data->entryA[1][side].unk38 / 100000.0f / 100.0f;
            range = (f32)data->entryA[1][side].unk3c / 100000.0f / 100.0f - lo;

            i = 0;
            while (g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.y <
                   g_Ball.physicsSubstruct.futureCoordsAndDist[i + 1].pos.y) {
                i++;
            }

            data->entryA[1][side].frameCount =
                (int)((lo + range * (f32)rand() / RAND_EBISAWA_MAX) * (f32)(g_Ball.hangtimeOfHit - i) + (f32)i);

            memcpy(&vA, &g_Ball.AtBat_Contact_BallPos, sizeof(VecXYZ));
            memcpy(&vB, &g_Ball.physicsSubstruct.futureCoordsAndDist[data->entryA[1][side].frameCount].pos,
                   sizeof(VecXYZ));

            vA.y = -vA.y;
            vB.y = -vB.y;
            fn_8002DCE4(&vA, &vB, &data->entryA[1][side]);
        }
        break;
    }
}

// .text:0x0015C000 size:0x14 mapped:0x8079B094
void peachDaisyStarSwingRelated2(void) {
    lbl_3_data_2709C[0].frames = 2;
}

// .text:0x0015C014 size:0x10 mapped:0x8079B0A8
int peachDaisyStarSwingRelated(void) {
    return lbl_3_data_2709C[0].frames;
}

// .text:0x0015C024 size:0x20C mapped:0x8079B0B8
void fn_3_15C024(VecXYZ* pos, VecXYZ* vel, VecXYZ* accel, BOOL applySteer) {
    f32 steer = 0.0f;
    s16* pc = pitchConstantsArray[g_Pitcher.specialPitchTypeCode];

    if (pos->z <= g_Pitcher.pitchZ_whenAirResistanceStarts) {
        f32 z = vel->z - vel->z * g_Pitcher.airResistance_veloAdj;
        if (z < -0.05f) {
            vel->x = vel->x - vel->x * g_Pitcher.airResistance_veloAdj;
            vel->y = vel->y - vel->y * g_Pitcher.airResistance_veloAdj;
            vel->z = z;
        }
    }

    vel->x *= g_Pitcher.decelerationFactor;
    vel->y *= g_Pitcher.decelerationFactor;
    vel->z *= g_Pitcher.decelerationFactor;

    vel->x += accel->x;

    pos->x += vel->x;
    pos->y += vel->y;
    pos->z += vel->z;

    if (applySteer) {
        f32 amount =
            0.00005f * LinearInterpolateToNewRange((f32)g_Pitcher.calced_curve, 1.0f, 100.0f, pc[1], pc[2]);
        u16 held = g_Controls[g_GameLogic.teams[g_GameLogic.teamFielding]].buttonInput;

        if (held & INPUT_BUTTON_LEFT) {
            steer = -1.0f;
        } else if (held & INPUT_BUTTON_RIGHT) {
            steer = 1.0f;
        }

        if (steer) {
            vel->x = amount * steer;
        }
    }
}
