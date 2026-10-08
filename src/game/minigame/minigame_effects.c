#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_minigameEffects
#define g_Minigame g_Minigame_shared
#include "game/minigame/minigame_effects.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/minigame/star_dash.h"
#include "game/minigame/piranha_panic.h"
#include "game/minigame/minigame_models.h"
#include "game/math/game_math.h"
#include "game/sound/m_sound.h"
#include "game/stadium/stadium_framework.h"
#include "game/stadium/sta_c2.h"
#include "game/minigame/minigame_hud.h"
#include "Unknown/File_0x80033794.h"
#include "Unknown/File_0x80033f64.h"
#include "Unknown/File_0x8001b728.h"
#include "Unknown/File_0x8005268c.h"
#include "Unknown/File_0x80052734.h"
#include "Unknown/File_0x800b2160.h"
#include "C3/control.h"
#include "Dolphin/gx.h"
#include "Dolphin/GX/GXFifo.h"
#include "Dolphin/mtx.h"
#include "Dolphin/mtxext.h"
#include "Dolphin/vec.h"
#include "Dolphin/os.h"
#include "Dolphin/stl.h"
#include "stl/stdlib.h"
#include "stl/math.h"
#undef g_Minigame

typedef union _MGMinigame {
    MiniGameStruct;
    PPState pp;
    SDState sd;
} MGMinigame;

extern MGMinigame g_Minigame;
#define PP g_Minigame.pp

extern u8 animRelated[0x124];
extern u8 hugeAnimStruct[0x3154];
extern f32 bB_barrelConsts[6];
extern u8 lbl_80366158[0x30];
extern u8 lbl_3_common_bss_35154[];

extern void fn_8002F5F4(Vec* start, Vec* dir, void* header);
extern void fn_80030D88(Vec* start, Vec* dir, MGFxSlot* slot, int arg);
extern void fn_80030470(Vec* start, Vec* dir, Vec* end, MGFxSlot* slot, int arg);


extern MGParticle* fn_80031F34(MGParticle* particles, int count);
extern void fn_800B24D4(int arg);
extern void fn_800B27DC(Mtx44 proj, int arg);
extern void fn_800B1468(Vec* quad, int arg, void* texture);




MGFxHead lbl_3_data_266A8 = {
    { 0.45f, -0.4f },
    {
        { 0, 21, { 2, 240000, 0, 0, 4, 2, 120000, 90000, 0, 155, 500000, 1000000, -500000, 500000, -256, 0, -28000, 1 } },
        { 0, 7, { 4, 78000, 60000, 50000, 12, 6, 109000, 101000, 0, 60, 4500000, 9500000, -1000000, 4500000, -256, 0, 0, 0 } },
        { 0, 18, { 0, 90000, 120000, 10000, 20, 10, 103000, 105999, 0, 60, 10000000, 18000000, 1000000, -1000000, 1010580480, 0, 0, 0 } },
    },
    { 0, { 20, 8, 0, 250000, 50000, 550000, 0, 0, 12, 13, 14, 15, 16, 17, 18, 19 } },
    { { 11, 10 }, { 15, 14 }, { 17, 16 }, { 13, 12 } },
};

MGFxSlot lbl_3_data_267F4 = { 0, 10, { 3, 100000, 30000, 10000, 12, 8, 110000, 50000, 0, 60, 4500000, 20000000, 0, 2000000, -256, 0, 75000, 0 } };

MGFxSlot lbl_3_data_26844 = { 0, 10, { 5, 18000, 20000, 60000, 12, 6, 109000, 101000, 0, 60, 4500000, 9400000, -1000000, 4500000, -256, 0, 75000, 0 } };

MGFxTail lbl_3_data_26894 = {
    { 0, 18, { 1, 60000, 10000, 50000, 30, 8, 104000, 106000, 0, 90, 12800000, 10000000, 1000000, 6000000, 1010580480, 0, 75000, 0 } },
    { &lbl_3_data_267F4, &lbl_3_data_26844, &lbl_3_data_26894.slot },
    { 0 },
    { { 0 } },
    { 0xFF0000FF, 65535, 0xFFFF00FF, 0x00FF00FF },
    { -0.4f, 6.0f },
};

u16 lbl_3_data_26B9C[4][2] = { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 } };

f32 lbl_3_data_26BAC = -0.2f;

f32 lbl_3_data_26BB0 = 3.0f;

Vec lbl_3_data_26BB4 = { 0.087f, -0.757f, 0.001f };

s32 lbl_3_data_26BC0[7] = { 3, 32, 0, 35000, 0, 255, 32 };

s32 lbl_3_data_26BDC[4] = { 16, 0, 255, 28 };

s32 lbl_3_data_26BEC[4] = { 0, 150000, 0, 16 };

s32 lbl_3_data_26BFC[4] = { 0, 15000, 0, 32 };

s32 lbl_3_data_26C0C[4] = { 100000, 100000, 10000, 64 };

f32 lbl_3_data_26C1C[8] = { -0.75f, 0.7f, 0.75f, 0.7f, -0.75f, -0.7f, 0.75f, -0.7f };

s32 lbl_3_data_26C3C[22] = { 2, 32, 0, 50000, 0, 255, 32, 15, 9, 150, 40000, 70000, 30000, 80000, 4400, 50000, 12000, 15000, 0, 104719, 60, 29 };

s32 lbl_3_data_26C94[9] = { 2, 90, 200000, 100000, 0, 0, 255, 36, 30 };

u8 lbl_3_data_26CB8[0x18] = { 4, 5, 6, 7, 8, 16, 17, 18, 19, 20, 22, 23, 24, 25, 26, 28, 29, 30, 31, 32, 33, 34, 35, 0 };

s32 lbl_3_data_26CD0[12] = { 2, 6, 40, 100000, 50000, 0, 255, 127, 0, 40000, 440, 31 };

s32 lbl_3_data_26D00[20] = { 6, 5, 645, 5, 0, 600000, 800000, 0, 255, 0, 2, 0, 200000, 300000, 0, 255, 0, 20, 20, 32 };

Vec lbl_3_data_26D50 = { 3.7f, -9.3f, 0.0f };

s32 lbl_3_data_26D5C[11] = { 7, 1, 8, 5, 0, 1000000, 1200000, 0, 255, 0, 33 };

s32 lbl_3_data_26D88[15] = { 8, 5, 30, 5, 0, 250000, 400000, 255, 255, 255, 0, 80, 0, 100000, 34 };

s32 lbl_3_data_26DC4[15] = { 8, 16, 30, 15, 250000, 375000, 500000, 0, 0, 0, 255, 127, 0, 100000, 34 };

f32 lbl_3_data_26E00[9] = { 2.035f, -5.718f, 1.014f, 1.793f, -4.523f, 0.914f, 1.29f, -4.119f, 0.815f };

s32 lbl_3_data_26E24[7] = { 3, 16, 100, 0, 30000, 0, 255 };

s32 lbl_3_data_26E40[15] = { 8, 6, 60, 30000, 5, 0, 100000, 40000, 50000, 0, 220, 0, 30000, 15000, 36 };

s32 lbl_3_data_26E7C[8] = { 100, 5000, 1200000, 15000, 15000, 0, 60, 37 };

s32 lbl_3_data_26E9C[25] = { 6, 30, 4, 5, 0, 250000, 350000, 0, 255, 0, 5, 20, 7, 2, 0, 250000, 350000, 0, 120, 0, 0, 4259909, 5046345, 4128768, 0 };

static MGTrailEffect* lbl_3_bss_B850;
static MGTexRecord* lbl_3_bss_B854;
static u8 lbl_3_bss_B858;
static u8 lbl_3_bss_B85C;
static f32 lbl_3_bss_B860[13];
static u8 lbl_3_bss_B894[0x124];

static inline void mgInitFollowParticle(MGFollowParticle* p) {
    Vec rot;

    rot.x = 57.29578f * p->rot->x;
    rot.y = 57.29578f * p->rot->y;
    rot.z = 57.29578f * p->rot->z;
    fn_3_1559E4((MGParticle*)p, p->pos, &rot);
}

static inline void mgInitHitParticle(MGParticle* p) {
    Vec rot;

    rot.x = 57.29578f * shortAngleToRad(g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw);
    rot.y = 57.29578f * shortAngleToRad(g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch);
    rot.z = 57.29578f * shortAngleToRad(g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll);
    fn_3_1559E4(p, (Vec*)&g_Ball.AtBat_Contact_BallPos, &rot);
}

/* Entry `slot` of the texture-id table at the pointer stored in animRelated[table]: each id selects a
 * 0x20-byte texture record following the table header. */
#define MG_TEX_RECORD(table, slot) \
    ((u8*)*(u8**)&animRelated[table] + 4 + *(u16*)((u8*)*(u8**)&animRelated[table] + 0x20 + (slot)*0x20) * 0x20)

extern void fn_80033B58(void* tex, int sub, int a, int b);



static inline void mgStarSparkOffset(MGParticle* p) {
    Vec offset;
    u32 node;

    if (p->_4C < 5) {
        node = (u32)rand() % 23;
        offset.z = 0.0f;
        offset.y = 0.0f;
        offset.x = 0.0f;
        if (!getAnimationCollisionOffset(p->_4C - 1, lbl_3_data_26CB8[node], &offset)) {
            memset(&offset, 0, sizeof(Vec));
            getAnimationCollisionOffset(p->_4C - 1, 4, &offset);
        }
    } else {
        offset.x = g_Minigame.sd.starPos.x;
        offset.y = -g_Minigame.sd.starPos.y;
        offset.z = g_Minigame.sd.starPos.z;
    }
    p->origin.x += offset.x;
    p->origin.y += offset.y;
    p->origin.z += offset.z;
}

static inline void mgStarSparkPlace(MGParticle* p) {
    Vec v = { 0.0f, 0.0f, 0.0f };

    if (p->_4C == 5) {
        v.x = v.x + (f32)(rand() % 10000 - 5000) / 10000.0f;
        v.y = v.y + (f32)(rand() % 10000 - 5000) / 10000.0f;
        p->origin.x = v.x;
        p->origin.y = v.y - 0.5f;
        p->origin.z = v.z;
    } else {
        p->origin.z = 0.0f;
        p->origin.y = 0.0f;
        p->origin.x = 0.0f;
    }
    mgStarSparkOffset(p);
}

static inline void mgStarSparksSetup(MGEffect* effect, s8 index) {
    MGParticle* p = effect->particles;
    u32 i = 0;

    do {
        if (p->_4C == index + 1) {
            p->_4A = lbl_3_data_26C94[7];
            p->alphaByte = lbl_3_data_26C94[5];
            p->_38 = p->_3C = (f32)lbl_3_data_26C94[2] / 100000.0f;
            p->_48 = (s16)((f32)p->_4A / 18.0f * (f32)i);
            if (p->_48 == 0) {
                mgStarSparkPlace(p);
            }
            p->_40 = p->_41 = p->_42 = 0xFF;
            i++;
            p->_34 = 0.0f;
        }
        p = p->next;
    } while (p != NULL);
}

static inline void mgBarrelSparksSetup(MGEffect* effect, int barrelIndex) {
    MGParticle* p = effect->particles;
    s32 i = 0;

    do {
        if (p->_44 == 0 && p->_4A == 0) {
            if (i < 3) {
                p->_44 = 1;
                p->_45 = (u8)barrelIndex;
                p->_46 = 0xFF;
                p->_4D = lbl_3_data_26D00[0];
                p->_38 = p->_3C = (f32)lbl_3_data_26D00[4];
                p->alphaByte = lbl_3_data_26D00[7];
                fn_3_14D318(p);
                p->_4A = lbl_3_data_26D00[17];
                p->_48 = 0;
            } else {
                p->_44 = 2;
                p->_45 = (u8)barrelIndex;
                p->_46 = (i - 3) / 5;
                p->_4D = lbl_3_data_26D00[1];
                p->_38 = p->_3C = (f32)lbl_3_data_26D00[11];
                p->alphaByte = lbl_3_data_26D00[14];
                p->_48 = (i - 3) % 5 * 4 + 1;
                p->_4A = lbl_3_data_26D00[18];
            }
            p->_40 = p->_41 = p->_42 = 0xFF;
            i++;
        }
        p = p->next;
    } while (p != NULL && i < 43);
}

static inline void mgBarrelRingInit(MGEffect* effect, Vec* pos) {
    MGParticle* p;
    u32 i = 0;
    f32 angle;

    effect->_10 = *(u32*)&animRelated[0x6C];
    p = effect->particles;
    do {
        p->_4D = lbl_3_data_26E40[0];
        p->_4E = 0;
        p->_4A = lbl_3_data_26E40[2];
        p->_48 = 0;
        p->origin.x = pos->x;
        p->origin.y = -pos->y;
        p->origin.z = pos->z;
        angle = 0.017453292f * (f32)(u32)(360 / lbl_3_data_26E40[1] * i);
        p->origin.x = p->origin.x + (f32)lbl_3_data_26E40[3] * (f32)cos(angle) / 100000.0f;
        p->origin.y = p->origin.y + (f32)lbl_3_data_26E40[3] * (f32)sin(angle) / 100000.0f;
        p->_3C = p->_38 = (f32)lbl_3_data_26E40[5] / 100000.0f;
        p->_40 = p->_41 = p->_42 = 0xFF;
        p->alphaByte = lbl_3_data_26E40[9];
        p->velX = 0.0f;
        p->velY = (f32)(lbl_3_data_26E40[12] - rand() % lbl_3_data_26E40[13]);
        p->velY = p->velY / 100000.0f;
        p->velY = p->velY * (f32)(1 - rand() % 2 * 2);
        i++;
        p->velZ = (f32)(lbl_3_data_26E40[6] - rand() % lbl_3_data_26E40[7]);
        p->velZ = p->velZ / 100000.0f;
        p = p->next;
    } while (p != NULL);
}

static inline void mgStarParticleInit(s8 index, MGParticle* p) {
    u8* actor = *(u8**)(hugeAnimStruct + 0x2C50 + index * 4);
    s32 base = lbl_3_data_26E7C[6];
    u8 lo = base;
    u8 range;
    s32 span;
    f32 angle;
    f32 s;
    f32 c;

    p->origin.x = 0.0f;
    p->origin.y = -((f32)lbl_3_data_26E7C[5] / 100000.0f + *(f32*)(actor + 0x38));
    p->origin.z = 0.0f;
    angle = 0.017453292f * (15.0f * ((f32)(lbl_3_data_26E7C[0] / 2 - p->_4A) / ((f32)lbl_3_data_26E7C[0] * 0.5f)));
    s = sin(angle);
    c = cos(angle);
    p->velX = s * (f32)lbl_3_data_26E7C[1] / 100000.0f;
    p->velY = c * (f32)lbl_3_data_26E7C[1] / 100000.0f;
    p->velZ = 0.0f;
    p->alpha = p->_20 = p->_1C = 0.0f;
    span = (s32)(1000.0f * ((f32)lbl_3_data_26E7C[2] / 100000.0f));
    p->_28 = (f32)(rand() % span) / 1000.0f;
    p->_2C = (f32)(rand() % span) / 1000.0f;
    p->_30 = (f32)(rand() % span) / 1000.0f;
    p->_47 = 0xFF;
    p->alphaByte = 0xFF;
    range = 0xFF - base;
    p->_41 = lo + rand() % range;
    p->_42 = lo + rand() % range;
    p->_44 = lo + rand() % range;
    p->_45 = lo + rand() % range;
    p->_46 = lo + rand() % range;
    p->_4C = 0;
}

static inline void mgStarDashDustInit(MGEffect* effect, Vec* pos) {
    MGParticle* p = effect->particles;
    f32 speed;

    effect->_10 = *(u32*)&animRelated[0x6C];
    do {
        p->_4D = lbl_3_data_26CD0[0];
        p->_4E = 0;
        p->origin.x = pos->x + (f32)(rand() % 1000 - 500) / 1000.0f;
        p->origin.y = -(0.75f + pos->y);
        p->origin.z = pos->z + (f32)(rand() % 1000 - 500) / 1000.0f;
        p->velX = p->velZ = 0.0f;
        p->velY = (f32)lbl_3_data_26CD0[9] / 100000.0f;
        speed = p->velY;
        p->velY = p->velY + ((f32)(rand() % (s32)(1000.0f * (speed * 0.5f))) - 1000.0f * (speed * 0.25f)) / 1000.0f;
        p->_40 = p->_41 = p->_42 = 0xFF;
        p->alphaByte = lbl_3_data_26CD0[6];
        p->_1C = (f32)(rand() % 1000 + 500) / 1000.0f;
        p->_38 = p->_3C = ((f32)lbl_3_data_26CD0[3] / 100000.0f) * p->_1C;
        p->_4A = lbl_3_data_26CD0[2];
        p->_48 = 0;
        p = p->next;
    } while (p != NULL);
}

// .text:0x157DB8 size:0x70
// Spawns the trail effect that follows the chomp; it lives for `duration` frames.
void chainChomp_spawnTrailEffect(s32 duration) {
    MGEffect* effect = allocParticleEffect(fn_3_157AC4, 0x80, 0, 1, 1, 0x16);

    if (effect != NULL) {
        effect->frame = 0;
        effect->duration = duration;
        effect->particles->_4D = 0;
        *(u32*)&effect->particles->_40 = 0xFFFFFFFF; // RGBA white
    }
}

// .text:0x157AC4 size:0x2F4
int fn_3_157AC4(MGEffect* effect) {
    MGParticle* p = effect->particles;
    Vec offset = { 2.775f, -6.975f, 0.0f };
    Mtx rot;
    f32 scale;

    PSMTXRotRad(rot, 'Y', shortAngleToRad(g_Minigame.ccs.chompYaw));
    PSMTXMultVec(rot, &offset, &offset);
    scale = fn_3_15791C(effect->frame);
    p->_3C = scale;
    p->_38 = scale;
    p->origin.x = g_Minigame.ccs.chompPos.x + offset.x + p->_38 * lbl_3_data_266A8.trailScale[0];
    p->origin.y = g_Minigame.ccs.chompPos.y + offset.y + p->_3C * lbl_3_data_266A8.trailScale[1];
    p->origin.z = g_Minigame.ccs.chompPos.z + offset.z;
    fn_8003403C(p->_38, p->_3C);
    fn_80033CC8(effect->particles, *(s32*)&animRelated[0x64]);
    if (lbl_80366158[0x28] == 0) {
        effect->frame++;
    }
    if (g_Minigame.minigameInactiveInd != 0) {
        return TRUE;
    }
    if (effect->frame == effect->duration && g_GameLogic.gameStatus != GAME_STATUS_MVP_END_GAME) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x15791C size:0x1A8
f32 fn_3_15791C(s32 frame) {
    s32 shifted = frame + 0x30;
    s32 cycles = shifted / 0x78;
    s32 phase = shifted % 0x78;
    f32 c;
    f32 scale;

    if (phase >= 0x30) {
        c = cos(3.1415927f * (1.0f + ((f32)phase - 48.0f) / 72.0f));
    } else {
        c = cos(3.1415927f * ((f32)phase / 48.0f));
    }
    scale = c * 0.5f + 0.5f;
    if (cycles != 0) {
        u8 status = g_GameLogic.gameStatus;

        if (status != GAME_STATUS_MVP_END_GAME && status != GAME_STATUS_MINIGAME_POST_MENU && status != GAME_STATUS_0x24 &&
            status != GAME_STATUS_0x26) {
            scale += 0.5f * ((f32)frame - 72.0f) / 120.0f;
        }
    }
    return 4.0f * scale;
}

// .text:0x1578F8 size:0x24
void fn_3_1578F8(void) {
    pitchingMachinePitching(0x16);
}

// .text:0x15767C size:0x27C
void fn_3_15767C(void) {
    MGFxData* data = (MGFxData*)&lbl_3_data_266A8;
    MGFxSlot* slot0 = &data->slotsA[0];
    MGFxSlot* slot1 = &data->slotsA[1];
    MGFxSlot* slot2 = &data->slotsA[2];
    Vec target;
    Vec dir;
    Vec toTarget;
    Vec* point;
    u32 i;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && g_Minigame.GameMode_MiniGame == MINI_GAME_ID_PIRANHA_PANIC &&
        lbl_3_bss_B850->done == FALSE) {
        for (i = 0; i < PP_OBJECT_COUNT; i++) {
            PPObject* obj = &PP.object[i];

            if (obj->state != 0) {
                target.x = obj->pos.x;
                target.y = -obj->pos.y;
                target.z = obj->pos.z;
                point = fn_3_1575F0(i);
                PSVECSubtract(point, &target, &dir);
                if (0.0f != PSVECMag(&dir)) {
                    s32 kind = obj->_1C;

                    slot2->texture = *(u32*)&animRelated[0x6C];
                    slot1->texture = *(u32*)&animRelated[0x6C];
                    slot0->texture = *(u32*)&animRelated[0x6C];
                    data->headerA.texture = *(u32*)&lbl_3_common_bss_35154[4];
                    if (kind <= 3 && kind >= 0) {
                        slot0->effectId = data->effectIds[kind][0];
                        slot1->effectId = data->effectIds[kind][1];
                        fn_8002F5F4(&target, &dir, &data->headerA);
                        if (lbl_80366158[0x28] == 0) {
                            fn_80030D88(&target, &dir, slot1, 0x29);
                            fn_80030D88(&target, &dir, slot2, 0x29);
                            PSVECNormalize(&dir, &dir);
                            PSVECSubtract(&target, point, &toTarget);
                            fn_80030470(&target, &dir, &toTarget, slot0, 0x29);
                        }
                    }
                }
            }
        }
        lbl_3_bss_B854 = NULL;
    }
    if (lbl_3_bss_B850->done != FALSE) {
        lbl_3_bss_B850 = NULL;
    }
}

// .text:0x1575F0 size:0x8C
Vec* fn_3_1575F0(u32 index) {
    MGTrailNode* node;

    if (lbl_3_bss_B850 != NULL) {
        node = lbl_3_bss_B850->nodes;
        while (index >= 7) {
            node = node->next;
            index -= 7;
        }
        return &node->pts[index];
    }
    return NULL;
}

// .text:0x157588 size:0x68
void fn_3_157588(int count) {
    lbl_3_bss_B850 = allocParticleEffect(fn_3_15767C, 0x80, 0, (count + 6) / 7, TRUE, 0x28);
    lbl_3_bss_B850->done = FALSE;
}

// .text:0x157570 size:0x18
void fn_3_157570(void) {
    lbl_3_bss_B850->done = TRUE;
}

// .text:0x1573AC size:0x1C4
void fn_3_1573AC(MGFxActor* actor) {
    MGFxData* data = (MGFxData*)&lbl_3_data_266A8;
    Vec offset;
    Vec dir;
    Mtx mtx;
    Control ctrl;
    MGFxSlot** slots;
    s32 effectId;

    offset.x = data->offsets[actor->offsetIndex][0] / 100000.0f;
    offset.y = data->offsets[actor->offsetIndex][1] / 100000.0f;
    offset.z = data->offsets[actor->offsetIndex][2] / 100000.0f;
    getAnimationCollisionOffset(actor->animIndex, 4, &offset);
    ctrl.type = 0;
    CTRLSetRotation(&ctrl, actor->rot.x, actor->rot.y, actor->rot.z);
    CTRLBuildMatrix(&ctrl, mtx);
    dir.x = 0.0f;
    dir.y = 0.0f;
    dir.z = 1.0f;
    PSMTXMultVec(mtx, &dir, &dir);
    slots = data->slotPtrs;
    slots[2]->texture = *(u32*)&animRelated[0x6C];
    slots[1]->texture = *(u32*)&animRelated[0x6C];
    data->slotPtrs[0]->texture = *(u32*)&animRelated[0x6C];
    effectId = data->effectIds[actor->slotIndex][1];
    slots[1]->effectId = effectId;
    data->slotPtrs[0]->effectId = effectId;
    fn_80030D88(&offset, &dir, data->slotPtrs[0], 0x29);
    fn_80030D88(&offset, &dir, slots[1], 0x29);
    fn_80030D88(&offset, &dir, slots[2], 0x29);
}

// .text:0x15730C size:0xA0
void fn_3_15730C(u32 index, f32 x, f32 y, f32 z) {
    Vec* point = fn_3_1575F0(index);

    if (point == NULL) {
        return;
    }
    point->x = x;
    point->y = y;
    point->z = z;
}

// .text:0x156D04 size:0x608
void fn_3_156D04(u32 index, f32 x, f32 y, f32 z) {
    MGFxData* data = (MGFxData*)&lbl_3_data_266A8;
    u32* colors = data->colors;
    s32 colorIndex = PP.object[index]._1C;
    Mtx44 proj;
    Vec screen;
    Vec trail;
    Vec dir;
    Vec step;
    Vec quad[4];
    Vec* point;
    f32 inv;
    f32 angle;
    f32 sizeScale;
    f32 g;
    f32 h;
    s32 i;

    inv = 1.0f / fn_80052768_getCamera(0)->zoom;
    fn_800B24D4(0xD);
    point = fn_3_1575F0(index);
    if (point != NULL) {
        C_MTXFrustum(proj, -0.175f * inv, 0.175f * inv, 0.25f * inv, -0.25f * inv, 1.0f, 512.0f);
        GXSetProjection(proj, GX_PERSPECTIVE);
        PSMTXMultVec(returnFloatFromModeIndex(0)->view, point, &screen);
        point->x = x;
        point->y = y;
        point->z = z;
        PSMTXMultVec(returnFloatFromModeIndex(0)->view, point, &trail);
        PSVECSubtract(&screen, &trail, &screen);
        dir = screen;
        angle = 0.017453292f * (f32)((f64)(rand() % 15000) / 1000.0);
        angle *= (f32)(1 - (rand() % 2) * 2);
        screen.x = dir.x * (f32)cos(angle) + dir.y * -(f32)sin(angle);
        screen.y = dir.x * (f32)sin(angle) + dir.y * (f32)cos(angle);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
        GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
        sizeScale = (f32)((f64)(1000 + rand() % 500) / 1000.0);
        i = 7;
        do {
            switch (i) {
            case 0:
            case 4:
            case 7:
                PSVECScale(&screen, sizeScale * (data->tail[0] + (f32)i * (data->tail[1] - data->tail[0]) / 7.0f),
                           &step);
                PSVECAdd(&trail, &step, &step);
                if (i >= 4) {
                    g = (f32)(7 - i) * 0.25f + 1.0f;
                } else {
                    g = 2.0f;
                }
                h = sizeScale * (g * 0.5f);
                quad[0].x = step.x - h;
                quad[0].y = step.y - h;
                quad[0].z = step.z;
                quad[1].x = step.x - h;
                quad[1].y = step.y + h;
                quad[1].z = step.z;
                quad[2].x = step.x + h;
                quad[2].y = step.y + h;
                quad[2].z = step.z;
                quad[3].x = step.x + h;
                quad[3].y = step.y - h;
                quad[3].z = step.z;
                GXSetBlendMode(GX_BM_SUBTRACT, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
                if (lbl_3_bss_B858 != 0) {
                    fn_3_156970(quad, -1, (MGTexRecord*)MG_TEX_RECORD(0x68, 0));
                }
                if (i >= 4) {
                    g = (f32)(7 - i) * 0.25f + 1.0f;
                } else {
                    g = 2.0f;
                }
                h = sizeScale * (g * 0.5f);
                quad[0].x = step.x - h;
                quad[0].y = step.y - h;
                quad[1].x = step.x - h;
                quad[1].y = step.y + h;
                quad[2].x = step.x + h;
                quad[2].y = step.y + h;
                quad[3].x = step.x + h;
                quad[3].y = step.y - h;
                GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
                fn_3_156970(quad, colors[colorIndex], (MGTexRecord*)MG_TEX_RECORD(0x6C, i + 10));
                break;
            }
        } while (i-- != 0);
    }
}

// .text:0x156970 size:0x394
void fn_3_156970(Vec* positions, u32 color, MGTexRecord* tex) {
    MGQuadVertex verts[4];
    Mtx identity;
    GXTexObj texObj;
    GXTlutObj tlutObj;
    int i;

    PSMTXIdentity(identity);
    for (i = 0; i < 4; i++) {
        memcpy(&verts[i].pos, &positions[i], sizeof(Vec));
        verts[i].color = color;
        memcpy(&verts[i].s, lbl_3_data_26B9C[i], 4);
    }
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetCullMode(GX_CULL_NONE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXLoadPosMtxImm(identity, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    if (lbl_3_bss_B854 != tex) {
        if (tex->tlut != NULL) {
            GXInitTexObjCI(&texObj, tex->image, tex->width, tex->height, tex->format, GX_CLAMP, GX_CLAMP, GX_FALSE, 0);
            GXInitTlutObj(&tlutObj, tex->tlut, tex->tlutFormat, tex->tlutEntries);
            GXLoadTlut(&tlutObj, 0);
        } else {
            GXInitTexObj(&texObj, tex->image, tex->width, tex->height, tex->format, GX_CLAMP, GX_CLAMP, GX_FALSE);
        }
        GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, tex->minLod, tex->maxLod, tex->lodBias, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXLoadTexObj(&texObj, GX_TEXMAP0);
        lbl_3_bss_B854 = tex;
    }
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    for (i = 0; i < 2; i++) {
        MGQuadVertex* v = &verts[i * 2];

        GXWGFifo.f32 = v[0].pos.x;
        GXWGFifo.f32 = v[0].pos.y;
        GXWGFifo.f32 = v[0].pos.z;
        GXWGFifo.u32 = v[0].color;
        GXWGFifo.f32 = v[0].s;
        GXWGFifo.f32 = v[0].t;
        GXWGFifo.f32 = v[1].pos.x;
        GXWGFifo.f32 = v[1].pos.y;
        GXWGFifo.f32 = v[1].pos.z;
        GXWGFifo.u32 = v[1].color;
        GXWGFifo.f32 = v[1].s;
        GXWGFifo.f32 = v[1].t;
    }
}

// .text:0x156548 size:0x428
void fn_3_156548(u32 index, f32 x, f32 y, f32 z) {
    Mtx44 proj;
    Vec screen;
    Vec step;
    Vec trail;
    Vec quad[4];
    Vec* point;
    f32 inv;
    f32 g;
    f32 h;
    s32 i;

    inv = 1.0f / fn_80052768_getCamera(0)->zoom;
    fn_800B24D4(0xD);
    point = fn_3_1575F0(index);
    if (point != NULL) {
        C_MTXFrustum(proj, -0.175f * inv, 0.175f * inv, 0.25f * inv, -0.25f * inv, 1.0f, 512.0f);
        fn_800B27DC(proj, 0);
        PSMTXMultVec(returnFloatFromModeIndex(0)->view, point, &screen);
        point->x = x;
        point->y = y;
        point->z = z;
        PSMTXMultVec(returnFloatFromModeIndex(0)->view, point, &trail);
        PSVECSubtract(&screen, &trail, &screen);
        setTextRenderingMode(2);
        i = 7;
        do {
            switch (i) {
            case 0:
            case 4:
            case 7:
                PSVECScale(&screen, lbl_3_data_26BAC + (f32)i * (lbl_3_data_26BB0 - lbl_3_data_26BAC) / 7.0f, &step);
                PSVECAdd(&trail, &step, &step);
                if (i >= 4) {
                    g = 0.5f * (f32)(7 - i) * 0.25f + 0.5f;
                } else {
                    g = 1.0f;
                }
                h = g * 0.5f;
                quad[0].x = step.x - h;
                quad[0].y = step.y - h;
                quad[0].z = step.z;
                quad[1].x = step.x - h;
                quad[1].y = step.y + h;
                quad[1].z = step.z;
                quad[2].x = step.x + h;
                quad[2].y = step.y + h;
                quad[2].z = step.z;
                quad[3].x = step.x + h;
                quad[3].y = step.y - h;
                quad[3].z = step.z;
                setTextRenderingMode(3);
                fn_800B1468(quad, -1, (void*)MG_TEX_RECORD(0x68, 0));
                if (i >= 4) {
                    g = 0.5f * (f32)(7 - i) * 0.25f + 0.5f;
                } else {
                    g = 1.0f;
                }
                h = g * 0.5f;
                quad[0].x = step.x - h;
                quad[0].y = step.y - h;
                quad[1].x = step.x - h;
                quad[1].y = step.y + h;
                quad[2].x = step.x + h;
                quad[2].y = step.y + h;
                quad[3].x = step.x + h;
                quad[3].y = step.y - h;
                setTextRenderingMode(2);
                fn_800B1468(quad, -1, (void*)MG_TEX_RECORD(0x68, i + 1));
                break;
            }
        } while (i-- != 0);
    }
}

// .text:0x156218 size:0x330
void bODPitchAnimation(void) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY) {
        fn_3_155F08();
    }
}

// .text:0x155F08 size:0x310
void fn_3_155F08(void) {
    MGEffect* effect = allocParticleEffect(fn_3_1552AC, 0x80, 0, lbl_3_data_26BC0[1], TRUE, 0x1B);

    if (effect != NULL) {
        fn_3_155C28(effect);
    }
}

// .text:0x155C28 size:0x2E0
void fn_3_155C28(MGEffect* effect) {
    MGParticle* p = effect->particles;
    u32 i = 0;

    effect->_10 = *(u32*)&animRelated[0x6C];
    do {
        p->_48 = (u8)i;
        i++;
        p->_4D = lbl_3_data_26BC0[0];
        p->_4E = 0;
        if (p->_48 == 0) {
            mgInitHitParticle(p);
        }
        p = p->next;
    } while (p != NULL);
}

// .text:0x1559E4 size:0x244
void fn_3_1559E4(MGParticle* p, Vec* base, Vec* rot) {
    Control ctrl;
    Mtx mtx;
    Vec offset;
    Vec scale;

    p->_4A = lbl_3_data_26BC0[6];
    ctrl.type = 0;
    CTRLSetRotation(&ctrl, rot->x, rot->y, rot->z);
    CTRLBuildMatrix(&ctrl, mtx);
    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY) {
        scale = lbl_3_data_26BB4;
    } else {
        PSVECScale(&lbl_3_data_26BB4, 1.5f, &scale);
    }
    offset.x = scale.x + 1.5 * ((rand() % 40 - 20) / 100.0);
    offset.y = scale.y;
    offset.z = scale.z + 1.5 * ((rand() % 40 - 20) / 100.0);
    PSMTXMultVec(mtx, &offset, &offset);
    offset.x = offset.x + base->x;
    offset.y = offset.y - fabs(base->y);
    offset.z = offset.z + base->z;
    p->origin.x = offset.x;
    p->origin.y = offset.y;
    p->origin.z = offset.z;
    p->_3C = p->_38 = (f32)lbl_3_data_26BC0[2];
    p->alphaByte = lbl_3_data_26BC0[4];
}

// .text:0x1552AC size:0x738
int fn_3_1552AC(MGEffect* effect) {
    MGParticle* p;

    if (lbl_80366158[0x28] != 0) {
        return 0;
    }
    fn_80033620(effect);
    p = effect->particles;
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_LO_CLEAR);
    do {
        if (p->_48 != 0) {
            p->_48--;
            if (p->_48 == 0) {
                mgInitHitParticle(p);
            }
        } else if (p->_4A != 0) {
            s32 alpha;

            fn_8003403C(p->_38, p->_3C);
            fn_80033CC8(p, effect->_10);
            if (lbl_3_data_26BC0[6] / p->_4A < 2) {
                alpha = p->alphaByte + lbl_3_data_26BC0[5] / (lbl_3_data_26BC0[6] / 2);
                if (alpha > lbl_3_data_26BC0[5]) {
                    alpha = lbl_3_data_26BC0[5];
                }
                p->alphaByte = alpha;
                p->_38 += ((f32)lbl_3_data_26BC0[3] / 100000.0f) / (f32)(lbl_3_data_26BC0[6] / 2);
                p->_3C = p->_38;
            } else {
                alpha = p->alphaByte - lbl_3_data_26BC0[5] / (lbl_3_data_26BC0[6] / 2);
                if (alpha < lbl_3_data_26BC0[4]) {
                    alpha = lbl_3_data_26BC0[4];
                }
                p->alphaByte = alpha;
                p->_38 -= ((f32)lbl_3_data_26BC0[3] / 100000.0f) / (f32)(lbl_3_data_26BC0[6] / 2);
                p->_3C = p->_38;
            }
            p->_40 = p->_41 = p->_42 = (u8)(255.0f * ((f32)p->alphaByte / 255.0f));
            p->_4A--;
        }
        if (p->_4A == 0 && p->_48 <= 0) {
            mgInitHitParticle(p);
        }
        p = p->next;
    } while (p != NULL);
    return 0;
}

// .text:0x155288 size:0x24
void bobOmbDerbyPitching(void) {
    pitchingMachinePitching(0x1B);
}

// .text:0x155264 size:0x24
void fn_3_155264(void) {
    pitchingMachinePitching(0x1B);
}

// .text:0x15521C size:0x48
void fn_3_15521C(s16 id, Vec* pos, Vec* rot) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && pos != NULL && rot != NULL) {
        fn_3_154C7C(id, pos, rot);
    }
}

// .text:0x154C7C size:0x5A0
void fn_3_154C7C(s16 id, Vec* pos, Vec* rot) {
    MGEffect* existing = fn_800339F0(0, 0x27);
    MGEffect* fresh;
    u8 scratch[0x80];

    if (existing != NULL) {
        fresh = fn_800337CC(scratch, lbl_3_data_26BC0[1], 1);
        if (fresh != NULL) {
            MGParticle* tail;

            fn_3_1549F0(fresh, id, pos, rot);
            if (existing->particles != NULL) {
                tail = existing->particles;
                while (tail->next != NULL) {
                    tail = tail->next;
                }
                tail->next = fresh->particles;
            } else {
                existing->particles = fresh->particles;
            }
            existing->count += fresh->count;
        }
    } else {
        fresh = allocParticleEffect(fn_3_1542F4, 0x80, 0, lbl_3_data_26BC0[1], TRUE, 0x27);
        if (fresh != NULL) {
            fn_3_1549F0(fresh, id, pos, rot);
        }
    }
}

// .text:0x1549F0 size:0x28C
void fn_3_1549F0(MGEffect* effect, s16 id, Vec* pos, Vec* rot) {
    MGFollowParticle* p = (MGFollowParticle*)effect->particles;
    u32 i = 0;

    effect->_10 = *(u32*)&animRelated[0x6C];
    do {
        p->id = id;
        p->pos = pos;
        p->rot = rot;
        p->_48 = (u8)i;
        i++;
        p->_4D = lbl_3_data_26BC0[0];
        p->_4E = 0;
        if (p->_48 == 0) {
            fn_3_1559E4((MGParticle*)p, pos, rot);
        }
        p = (MGFollowParticle*)p->next;
    } while (p != NULL);
}

// .text:0x1542F4 size:0x6FC
int fn_3_1542F4(MGEffect* effect) {
    MGFollowParticle* p;

    if (lbl_80366158[0x28] != 0) {
        return 0;
    }
    if (effect->particles == NULL) {
        return 0;
    }
    effect->particles = fn_80031F34(effect->particles, effect->count);
    p = (MGFollowParticle*)effect->particles;
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_LO_CLEAR);
    do {
        if (p->_48 != 0) {
            p->_48--;
            if (p->_48 == 0) {
                mgInitFollowParticle(p);
            }
        } else if (p->_4A != 0) {
            s32 alpha;

            fn_8003403C(p->_38, p->_3C);
            fn_80033CC8(p, effect->_10);
            if (lbl_3_data_26BC0[6] / p->_4A < 2) {
                alpha = p->alphaByte + lbl_3_data_26BC0[5] / (lbl_3_data_26BC0[6] / 2);
                if (alpha > lbl_3_data_26BC0[5]) {
                    alpha = lbl_3_data_26BC0[5];
                }
                p->alphaByte = alpha;
                p->_38 += 3.0f * (((f32)lbl_3_data_26BC0[3] / 100000.0f) / (f32)(lbl_3_data_26BC0[6] / 2));
                p->_3C = p->_38;
            } else {
                alpha = p->alphaByte - lbl_3_data_26BC0[5] / (lbl_3_data_26BC0[6] / 2);
                if (alpha < lbl_3_data_26BC0[4]) {
                    alpha = lbl_3_data_26BC0[4];
                }
                p->alphaByte = alpha;
                p->_38 -= 3.0f * (((f32)lbl_3_data_26BC0[3] / 100000.0f) / (f32)(lbl_3_data_26BC0[6] / 2));
                p->_3C = p->_38;
            }
            p->_40 = p->_41 = p->_42 = (u8)(255.0f * ((f32)p->alphaByte / 255.0f));
            p->_4A--;
        }
        if (p->_4A == 0 && p->_48 <= 0) {
            mgInitFollowParticle(p);
        }
        p = (MGFollowParticle*)p->next;
    } while (p != NULL);
    return 0;
}

// .text:0x154238 size:0xBC
void fn_3_154238(s16 id) {
    MGEffect* effect = fn_800339F0(0, 0x27);
    MGParticle* p;
    MGParticle** link;
    MGParticle* removedHead;
    MGParticle* removedTail;

    if (effect != NULL) {
        p = effect->particles;
        link = &effect->particles;
        removedHead = NULL;
        removedTail = NULL;
        do {
            if (((MGFollowParticle*)p)->id == id) {
                *link = p->next;
                if (removedTail != NULL) {
                    removedTail->next = p;
                } else {
                    removedHead = p;
                }
                p->next = NULL;
                removedTail = p;
                effect->count--;
            } else {
                link = &p->next;
            }
            p = *link;
        } while (p != NULL);
        if (removedHead != NULL) {
            fn_80033794(removedHead);
        }
    }
}

// .text:0x154214 size:0x24
void fn_3_154214(void) {
    pitchingMachinePitching(0x27);
}

// .text:0x1541C4 size:0x50
void fn_3_1541C4(u8 kind, u8 mode, Vec* pos) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && g_Minigame.GameMode_MiniGame == MINI_GAME_ID_CHAINCHOMP_SPRINT &&
        pos != NULL) {
        fn_3_1540E4(kind, mode, pos);
    }
}

// .text:0x1540E4 size:0xE0
#pragma dont_inline on
void fn_3_1540E4(u8 kind, u8 mode, Vec* pos) {
    MGEffect* effect = fn_800339F0(0, 0x1C);
    MGParticle* p;
    if (effect != NULL) {
        fn_3_153F8C(effect, kind, mode, pos);
    } else {
        effect = allocParticleEffect(fn_3_151F2C, 0x80, 0, lbl_3_data_26BDC[0] * 15, TRUE, 0x1C);
        if (effect != NULL) {
            for (p = effect->particles; p != NULL; p = p->next) {
                p->_4A = 0;
                p->_4C = 0;
                p->_4F = 0xFF;
            }
            fn_3_153F8C(effect, kind, mode, pos);
            memset(lbl_3_bss_B894, 0, 0xF);
        }
    }
}
#pragma dont_inline reset

// .text:0x153F8C size:0x158
#pragma dont_inline on
void fn_3_153F8C(MGEffect* effect, u8 kind, u8 mode, Vec* pos) {
    MGParticle* p = effect->particles;
    u32 i = 0;
    u8 index;

    effect->_10 = *(u32*)&animRelated[0x6C];
    do {
        if (p->_4A == 0) {
            index = i;
            fn_3_153E8C(p, pos, kind, mode, index);
            fn_3_1536A8(p, (index != 0) + 1);
            i++;
        }
        p = p->next;
    } while (p != NULL && (u8)i < lbl_3_data_26BDC[0]);
}
#pragma dont_inline reset

// .text:0x153E8C size:0x100
void fn_3_153E8C(MGParticle* p, Vec* pos, u8 kind, u8 mode, u8 index) {
    f32 scale;

    p->_48 = index * lbl_3_data_26BDC[3] / lbl_3_data_26BDC[0] + (index != 0) * lbl_3_data_26BEC[3];
    p->_4D = (mode == 4);
    p->_4E = 0;
    p->_4F = kind;
    p->_40 = p->_41 = p->_42 = 0xFF;
    p->alphaByte = lbl_3_data_26BDC[1];
    p->_1C = pos->x;
    if (p->_4D != 0) {
        scale = mm_GetItemScale(2);
    } else {
        scale = mm_GetItemScale(0);
    }
    p->_20 = -pos->y - 0.1435f * scale;
    p->alpha = pos->z;
    p->_45 = 0;
    p->_44 = 0;
}

// .text:0x1536A8 size:0x7E4
void fn_3_1536A8(MGParticle* p, u8 kind) {
    MGFxData* data = (MGFxData*)&lbl_3_data_266A8;

    switch (kind) {
    case 1: {
            camera_803c639c_s* cam = returnFloatFromModeIndex(returnsCurrentMode());
            f32 scale;
            Mtx rotMtx;
            f32 angle;
            s32* tbl;

            if (p->_4D != 0) {
                scale = mm_GetItemScale(2);
            } else {
                scale = mm_GetItemScale(0);
            }
            {
            Vec axis = { 0.0f, 0.0f, -1.0f };
            Vec rotAxis;
            Vec dir;
            Vec v;

            v.x = 0.0f;
            v.y = 0.0f;
            v.z = -0.354f * scale;
            PSVECSubtract(&cam->eye, (Vec*)&p->_1C, &dir);
            PSVECNormalize(&dir, &dir);
            angle = acos(PSVECDotProduct(&axis, &dir));
            PSVECCrossProduct(&axis, &dir, &rotAxis);
            if (PSVECMag(&rotAxis) == 0.0f) {
                rotAxis.x = 0.0f;
                rotAxis.y = -1.0f;
                rotAxis.z = 0.0f;
            }
            PSMTXRotAxisRad(rotMtx, &rotAxis, angle);
            PSMTXMultVec(rotMtx, &v, &v);
            tbl = data->itemFxB;
            p->origin.x = p->_1C + v.x;
            p->origin.y = p->_20 + v.y;
            p->origin.z = p->alpha + v.z;
            p->_38 = p->_3C = (f32)data->itemFxB[0];
            p->_4C = 1;
            p->_4A = tbl[3];
            p->velX = p->velZ = 0.0f;
            p->velY = ((f32)tbl[2] / 100000.0f);
            }
            break;
        }
    case 2: {
            camera_803c639c_s* cam = returnFloatFromModeIndex(returnsCurrentMode());
            f32 scale;
            Mtx rotMtx;
            f32 angle;
            s32* tbl;

            if (p->_4D != 0) {
                scale = mm_GetItemScale(2);
            } else {
                scale = mm_GetItemScale(0);
            }
            {
            Vec axis = { 0.0f, 0.0f, -1.0f };
            Vec rotAxis;
            Vec dir;
            Vec v;

            v.x = 0.0f;
            v.y = 0.0f;
            v.z = -0.354f * scale;
            v.x = v.x + scale * ((rand() % 50 - 25) / 100.0);
            v.y = v.y + scale * ((rand() % 50 - 25) / 100.0);
            v.z = v.z + scale * ((rand() % 50 - 25) / 100.0);
            PSVECSubtract(&cam->eye, (Vec*)&p->_1C, &dir);
            PSVECNormalize(&dir, &dir);
            angle = acos(PSVECDotProduct(&axis, &dir));
            PSVECCrossProduct(&axis, &dir, &rotAxis);
            if (PSVECMag(&rotAxis) == 0.0f) {
                rotAxis.x = 0.0f;
                rotAxis.y = -1.0f;
                rotAxis.z = 0.0f;
            }
            PSMTXRotAxisRad(rotMtx, &rotAxis, angle);
            PSMTXMultVec(rotMtx, &v, &v);
            tbl = data->itemFxC;
            p->origin.x = p->_1C + v.x;
            p->origin.y = p->_20 + v.y;
            p->origin.z = p->alpha + v.z;
            p->_38 = p->_3C = (f32)data->itemFxC[0];
            p->_4C = 2;
            p->_4A = tbl[3];
            p->velX = p->velZ = 0.0f;
            p->velY = ((f32)tbl[2] / 100000.0f);
            }
            break;
        }
    case 3: {
            camera_803c639c_s* cam = returnFloatFromModeIndex(returnsCurrentMode());
            f32 scale;
            Mtx rotMtx;
            f32 angle;
            s32* tbl;

            if (p->_4D != 0) {
                scale = mm_GetItemScale(2);
            } else {
                scale = mm_GetItemScale(0);
            }
            {
            Vec axis = { 0.0f, 0.0f, -1.0f };
            Vec rotAxis;
            Vec dir;
            Vec v;

            v.x = 0.0f;
            v.y = 0.0f;
            v.z = -0.354f * scale;
            v.x = v.x + scale * ((rand() % 50 - 25) / 100.0);
            v.y = v.y + scale * ((rand() % 50 - 25) / 100.0);
            v.z = v.z + scale * ((rand() % 50 - 25) / 100.0);
            PSVECSubtract(&cam->eye, (Vec*)&p->_1C, &dir);
            PSVECNormalize(&dir, &dir);
            angle = acos(PSVECDotProduct(&axis, &dir));
            PSVECCrossProduct(&axis, &dir, &rotAxis);
            if (PSVECMag(&rotAxis) == 0.0f) {
                rotAxis.x = 0.0f;
                rotAxis.y = -1.0f;
                rotAxis.z = 0.0f;
            }
            PSMTXRotAxisRad(rotMtx, &rotAxis, angle);
            PSMTXMultVec(rotMtx, &v, &v);
            tbl = data->itemFxD;
            p->origin.x = p->_1C + v.x;
            p->origin.y = p->_20 + v.y;
            p->origin.z = p->alpha + v.z;
            p->_38 = p->_3C = (f32)data->itemFxD[0];
            p->_4C = 3;
            p->_4A = tbl[3];
            p->velX = p->velZ = 0.0f;
            p->velY = -((f32)tbl[2] / 100000.0f);
            }
            break;
        }
    }
}

// .text:0x1534C0 size:0x1E8
void fn_3_1534C0(MGParticle* p) {
    fn_3_1524E8(p, FALSE);
    p->_3C = p->_38 = (f32)lbl_3_data_26BEC[0];
    p->_4C = 1;
    p->_4A = lbl_3_data_26BEC[3];
    p->velX = p->velZ = 0.0f;
    p->velY = ((f32)lbl_3_data_26BEC[2] / 100000.0f);
}

// .text:0x1531A4 size:0x31C
void fn_3_1531A4(MGParticle* p) {
    fn_3_1524E8(p, TRUE);
    p->_3C = p->_38 = (f32)lbl_3_data_26BFC[0];
    p->_4C = 2;
    p->_4A = lbl_3_data_26BFC[3];
    p->velX = p->velZ = 0.0f;
    p->velY = ((f32)lbl_3_data_26BFC[2] / 100000.0f);
}

// .text:0x152AB4 size:0x6F0
void fn_3_152AB4(u8 id, u8 flag) {
    MGParticle* p;
    MGEffect* effect;
    f32* cornerY;
    f32* cornerX;
    u32 count = 0;
    camera_803c639c_s* cam;
    Vec rotated;
    Vec dir;
    Vec view;
    Vec world;
    f32 angle;
    f32 k;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && g_Minigame.GameMode_MiniGame == MINI_GAME_ID_CHAINCHOMP_SPRINT) {
        effect = fn_800339F0(0, 0x1C);
        if (effect != NULL) {
            cornerX = &lbl_3_data_26C1C[flag * 2];
            cornerY = cornerX + 1;
            p = effect->particles;
            do {
                if (p->_4F == id && p->_4A != 0) {
                    p->_48 = 0;
                    p->_4F = 0xFF;
                    fn_3_1524E8(p, TRUE);
                    cam = returnFloatFromModeIndex(returnsCurrentMode());
                    world.x = p->origin.x;
                    world.y = p->origin.y;
                    world.z = p->origin.z;
                    PSMTXMultVec(cam->view, &world, &view);
                    rotated.z = 0.0f;
                    rotated.y = 0.0f;
                    rotated.x = 0.0f;
                    PSVECSubtract(&rotated, &cam->eye, &rotated);
                    p->_34 = PSVECMag(&rotated);
                    view.z = -1.0f;
                    PSMTX44MultVec(cam->proj, &view, &view);
                    p->origin.x = view.x;
                    p->origin.y = view.y;
                    p->origin.z = view.z;
                    p->_3C = p->_38 = (f32)lbl_3_data_26C0C[0] / 100000.0f;
                    world.x = p->_38;
                    world.y = p->_38;
                    world.z = p->_34;
                    PSMTX44MultVec(cam->proj, &world, &view);
                    p->_38 = view.x * (p->_4D != 0 ? 1.5 : 1.0);
                    p->_3C = view.y * (p->_4D != 0 ? 1.5 : 1.0);
                    p->_4C = 3;
                    p->_4A = lbl_3_data_26C0C[3];
                    angle = 0.017453292f * (f32)(90.0 * (2.0 * ((f32)rand() / 32767.0f - 0.5)));
                    dir.x = *cornerX - p->origin.x;
                    dir.y = *cornerY - p->origin.y;
                    dir.z = 0.0f;
                    if (PSVECMag(&dir) >= 1.0) {
                        k = 1.0f;
                    } else {
                        k = 1.0f / (PSVECMag(&dir) * 0.5f);
                    }
                    PSVECNormalize(&dir, &dir);
                    dir.x = dir.x * -1.0f;
                    dir.y = dir.y * -1.0f;
                    rotated.x = dir.x * (f32)cos(angle) + -dir.y * (f32)sin(angle);
                    rotated.y = dir.x * (f32)sin(angle) + dir.y * (f32)cos(angle);
                    rotated.z = 0.0f;
                    PSVECScale(&rotated, ((f32)lbl_3_data_26C0C[2] / 100000.0f) * k, &rotated);
                    rotated.z = p->_34;
                    PSMTX44MultVec(cam->proj, &rotated, &rotated);
                    rotated.z = 0.0f;
                    p->velX = rotated.x;
                    p->velY = rotated.y;
                    p->velZ = rotated.z;
                    p->alphaByte = 0xFF;
                    p->_44 = flag;
                    p->_45 = (count == 0);
                    count++;
                }
                p = p->next;
            } while (p != NULL);
        }
    }
}

// .text:0x152794 size:0x320
void fn_3_152794(MGParticle* p) {
    fn_3_1524E8(p, TRUE);
    p->_3C = p->_38 = (f32)lbl_3_data_26C0C[0];
    p->_4C = 3;
    p->_4A = lbl_3_data_26C0C[3];
    p->velX = p->velZ = 0.0f;
    p->velY = -((f32)lbl_3_data_26C0C[2] / 100000.0f);
}

// .text:0x1524E8 size:0x2AC
void fn_3_1524E8(MGParticle* p, u8 randomize) {
    camera_803c639c_s* cam = returnFloatFromModeIndex(returnsCurrentMode());
    f32 scale;
    Mtx rotMtx;
    Vec v;
    Vec dir;
    Vec rotAxis;
    f32 angle;

    if (p->_4D != 0) {
        scale = mm_GetItemScale(2);
    } else {
        scale = mm_GetItemScale(0);
    }
    {
        Vec axis = { 0.0f, 0.0f, -1.0f };

        v.x = 0.0f;
        v.y = 0.0f;
        v.z = -0.354f * scale;
        if (randomize != 0) {
            v.x = v.x + scale * ((rand() % 50 - 25) / 100.0);
            v.y = v.y + scale * ((rand() % 50 - 25) / 100.0);
            v.z = v.z + scale * ((rand() % 50 - 25) / 100.0);
        }
        PSVECSubtract(&cam->eye, (Vec*)&p->_1C, &dir);
        PSVECNormalize(&dir, &dir);
        angle = acos(PSVECDotProduct(&axis, &dir));
        PSVECCrossProduct(&axis, &dir, &rotAxis);
        if (PSVECMag(&rotAxis) == 0.0f) {
            rotAxis.x = 0.0f;
            rotAxis.y = -1.0f;
            rotAxis.z = 0.0f;
        }
        PSMTXRotAxisRad(rotMtx, &rotAxis, angle);
        PSMTXMultVec(rotMtx, &v, &v);
        p->origin.x = p->_1C + v.x;
        p->origin.y = p->_20 + v.y;
        p->origin.z = p->alpha + v.z;
    }
}

// .text:0x151F2C size:0x5BC
int fn_3_151F2C(MGEffect* effect) {
    MGFxData* data = (MGFxData*)&lbl_3_data_266A8;
    MGParticle* p;
    f32 scale;

    if (lbl_80366158[0x28] != 0) {
        return 0;
    }
    fn_80033620(effect);
    p = effect->particles;
    if (p->_4C != 3) {
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    } else {
        GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    }
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
    do {
        if (p->_48 <= 0 && p->_4A != 0) {
            if (p->_4D != 0) {
                scale = mm_GetItemScale(2);
            } else {
                scale = mm_GetItemScale(0);
            }
            switch (p->_4C) {
            case 1:
                fn_3_151D6C(effect, p);
                break;
            case 2:
                fn_3_151BAC(effect, p);
                break;
            case 3:
                fn_3_1519F8(effect, p);
                break;
            }
        } else if (p->_48 != 0) {
            p->_48--;
        }
        if (p->_4A == 0 && (p->_4C == 1 || p->_4C == 2)) {
            fn_3_1536A8(p, 2);
        }
        p = p->next;
    } while (p != NULL);
    return 0;
}

// .text:0x151D6C size:0x1C0
void fn_3_151D6C(MGEffect* effect, MGParticle* p) {
    s32 duration;
    s32 alpha;
    s32 alphaStep;
    f32 sizeStep;
    f32 scale;

    fn_8003403C(p->_38, p->_3C);
    fn_80033CC8(p, effect->_10);
    if (p->_4D != 0) {
        scale = mm_GetItemScale(2);
    } else {
        scale = mm_GetItemScale(0);
    }
    duration = lbl_3_data_26BEC[3];
    alpha = p->alphaByte;
    if (duration / p->_4A < 2) {
        alphaStep = lbl_3_data_26BDC[2] / (duration / 2);
        sizeStep = (f32)lbl_3_data_26BEC[1] * scale / 100000.0f / (f32)(duration / 2);
    } else {
        alphaStep = -lbl_3_data_26BDC[2] / (duration / 2);
        sizeStep = -((f32)lbl_3_data_26BEC[1] * scale / 100000.0f) / (f32)(duration / 2);
    }
    alpha = alpha + alphaStep;
    if (alpha < 0) {
        alpha = 0;
    } else if (alpha > 0xFF) {
        alpha = 0xFF;
    }
    p->alphaByte = alpha;
    p->_38 += sizeStep;
    p->_3C = p->_38;
    PSVECAdd(&p->origin, (Vec*)&p->velX, &p->origin);
    p->_4A--;
}

// .text:0x151BAC size:0x1C0
void fn_3_151BAC(MGEffect* effect, MGParticle* p) {
    s32 duration;
    s32 alpha;
    s32 alphaStep;
    f32 sizeStep;
    f32 scale;

    fn_8003403C(p->_38, p->_3C);
    fn_80033CC8(p, effect->_10);
    if (p->_4D != 0) {
        scale = mm_GetItemScale(2);
    } else {
        scale = mm_GetItemScale(0);
    }
    duration = lbl_3_data_26BFC[3];
    alpha = p->alphaByte;
    if (duration / p->_4A < 2) {
        alphaStep = lbl_3_data_26BDC[2] / (duration / 2);
        sizeStep = (f32)lbl_3_data_26BFC[1] * scale / 100000.0f / (f32)(duration / 2);
    } else {
        alphaStep = -lbl_3_data_26BDC[2] / (duration / 2);
        sizeStep = -((f32)lbl_3_data_26BFC[1] * scale / 100000.0f) / (f32)(duration / 2);
    }
    alpha = alpha + alphaStep;
    if (alpha < 0) {
        alpha = 0;
    } else if (alpha > 0xFF) {
        alpha = 0xFF;
    }
    p->alphaByte = alpha;
    p->_38 += sizeStep;
    p->_3C = p->_38;
    PSVECAdd(&p->origin, (Vec*)&p->velX, &p->origin);
    p->_4A--;
}

// .text:0x1519F8 size:0x1B4
void fn_3_1519F8(MGEffect* effect, MGParticle* p) {
    Vec dir;
    Vec unit;
    Vec target;
    f32 dist;

    fn_3_1517D0(p, effect);
    if (lbl_80366158[0x28] == 0) {
        PSVECAdd(&p->origin, (Vec*)&p->velX, &p->origin);
        memcpy(&dir, &p->origin, sizeof(Vec));
        dir.x = lbl_3_data_26C1C[p->_44 * 2] - dir.x;
        dir.y = lbl_3_data_26C1C[p->_44 * 2 + 1] - dir.y;
        dir.z = 0.0f;
        PSVECNormalize(&dir, &unit);
        dist = PSVECMag(&dir);
        PSVECScale(&unit, 0.0015f * (1.0f / (dist * dist)), &dir);
        PSVECAdd((Vec*)&p->velX, &dir, (Vec*)&p->velX);
        target.x = lbl_3_data_26C1C[p->_44 * 2];
        target.y = lbl_3_data_26C1C[p->_44 * 2 + 1];
        target.z = 0.0f;
        PSVECNormalize(&target, &target);
        if (PSVECDotProduct(&unit, &target) < 0.0f || 0.0f == dist) {
            p->_4A = 0;
        }
        if (p->_4A == 0 && p->_45 != 0) {
            fn_3_11F4B4(p->_44, p->_4D == 1);
            p->_45 = 0;
        }
    }
}

// .text:0x1517D0 size:0x228
void fn_3_1517D0(MGParticle* p, MGEffect* effect) {
    Mtx mtx;
    Mtx44 proj;
    f32 corner[4][3];
    f32 uv[4][2] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
    f32 halfW = p->_38 * 0.5f;
    f32 halfH = p->_3C * 0.5f;
    int i;
    int k;

    corner[0][0] = -halfW;
    corner[0][1] = -halfH;
    corner[1][0] = halfW;
    corner[1][1] = -halfH;
    corner[2][0] = halfW;
    corner[2][1] = halfH;
    corner[3][0] = -halfW;
    corner[3][1] = halfH;
    corner[3][2] = 0.0f;
    corner[2][2] = 0.0f;
    corner[1][2] = 0.0f;
    corner[0][2] = 0.0f;
    PSMTXIdentity(mtx);
    PSMTX44Identity(proj);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetProjection(proj, GX_PERSPECTIVE);
    fn_80033B58((void*)effect->_10, p->_4D, 0, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    k = 0;
    for (i = 0; i < 2; i++) {
        f32* t;

        GXWGFifo.f32 = p->origin.x + corner[i * 2][0];
        GXWGFifo.f32 = p->origin.y + corner[i * 2][1];
        GXWGFifo.f32 = -1.0f;
        GXWGFifo.u32 = *(u32*)&p->_40;
        t = uv[p->_4E + k++];
        GXWGFifo.f32 = t[0];
        GXWGFifo.f32 = t[1];
        GXWGFifo.f32 = p->origin.x + corner[i * 2 + 1][0];
        GXWGFifo.f32 = p->origin.y + corner[i * 2 + 1][1];
        GXWGFifo.f32 = -1.0f;
        GXWGFifo.u32 = *(u32*)&p->_40;
        t = uv[p->_4E + k++];
        GXWGFifo.f32 = t[0];
        GXWGFifo.f32 = t[1];
    }
    GXLoadPosMtxImm(fn_80052768_getCamera(0)->view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetProjection(fn_80052768_getCamera(0)->proj, GX_PERSPECTIVE);
}

// .text:0x151798 size:0x38
void fn_3_151798(void) {
    memset(lbl_3_bss_B894, 0, 0xF);
    pitchingMachinePitching(0x1C);
}

// .text:0x151760 size:0x38
void fn_3_151760(void) {
    memset(lbl_3_bss_B894, 0, 0xF);
    pitchingMachinePitching(0x1C);
}

// .text:0x151710 size:0x50
void fn_3_151710(MGWeatherCtx* ctx, Vec* pos) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && g_Minigame.GameMode_MiniGame == MINI_GAME_ID_WALLBALL &&
        ctx != NULL) {
        fn_3_151694(ctx, pos);
    }
}

// .text:0x151694 size:0x7C
void fn_3_151694(MGWeatherCtx* ctx, Vec* pos) {
    MGWeatherEffect* effect =
        allocParticleEffect(fn_3_150940, 0x80, 0, lbl_3_data_26C3C[1] + lbl_3_data_26C3C[9], TRUE, 0x1D);

    if (effect != NULL) {
        fn_3_151204(effect, ctx, pos);
    }
}

// .text:0x151204 size:0x490
void fn_3_151204(MGWeatherEffect* effect, MGWeatherCtx* ctx, Vec* pos) {
    MGParticle* p;
    u32 snowCount = 0;
    u32 rainCount = 0;

    effect->_10 = *(u32*)&animRelated[0x6C];
    effect->ctx = ctx;
    memcpy(&effect->pos, pos, sizeof(Vec));
    p = effect->particles;
    do {
        if (snowCount < lbl_3_data_26C3C[1]) {
            p->_48 = ++snowCount;
            p->_4D = lbl_3_data_26C3C[0];
            p->_4C = 1;
            p->_4A = lbl_3_data_26C3C[6];
            if (p->_48 == 0) {
                fn_3_151068(effect, p);
            }
        } else {
            p->_48 = rainCount++;
            p->_4D = lbl_3_data_26C3C[8];
            p->_4C = 2;
            fn_3_150D84(effect, p);
        }
        p->_4E = 0;
        p = p->next;
    } while (p != NULL);
}

// .text:0x151068 size:0x19C
void fn_3_151068(MGWeatherEffect* effect, MGParticle* p) {
    Mtx mtx;
    MGActor* actor;
    f32 x;
    f32 y;
    f32 z;

    p->_4A = lbl_3_data_26C3C[6];
    actor = effect->ctx->list->actors[lbl_3_data_26C3C[7]];
    PSMTXIdentity(mtx);
    x = actor->mtx[0][3];
    y = actor->mtx[1][3];
    z = actor->mtx[2][3];
    x += (rand() % 100 - 50) / 100.0;
    y += (rand() % 150 - 75) / 100.0;
    p->origin.x = x;
    p->origin.y = y;
    p->origin.z = z;
    p->_3C = p->_38 = (f32)lbl_3_data_26C3C[2];
    p->alphaByte = lbl_3_data_26C3C[4];
}

// .text:0x150D84 size:0x2E4
void fn_3_150D84(MGWeatherEffect* effect, MGParticle* p) {
    f32 angle;
    f32 speed;

    p->_4A = lbl_3_data_26C3C[20];
    p->origin.x = effect->pos.x;
    p->origin.y = -effect->pos.y;
    p->origin.z = effect->pos.z;
    p->_3C = p->_38 = (f32)(lbl_3_data_26C3C[10] + rand() % (lbl_3_data_26C3C[11] - lbl_3_data_26C3C[10])) / 100000.0f;
    p->velY = (f32)(lbl_3_data_26C3C[12] + rand() % (lbl_3_data_26C3C[13] - lbl_3_data_26C3C[12])) / 100000.0f;
    angle = 0.017453292f * (f32)((rand() % 36000) / 100.0);
    speed = (f32)(lbl_3_data_26C3C[16] + rand() % (lbl_3_data_26C3C[17] - lbl_3_data_26C3C[16])) / 100000.0f;
    p->velX = speed * (f32)cos(angle);
    p->velZ = speed * (f32)sin(angle);
    p->_1C = 57.29578f * ((f32)(lbl_3_data_26C3C[18] + rand() % (lbl_3_data_26C3C[19] - lbl_3_data_26C3C[18])) / 100000.0f);
    p->_1C = p->_1C * (f32)(1 - (rand() % 2) * 2);
    p->_40 = p->_41 = p->_42 = p->alphaByte = 0xFF;
}

// .text:0x150940 size:0x444
int fn_3_150940(MGWeatherEffect* effect) {
    MGParticle* p;

    if (lbl_80366158[0x28] != 0) {
        return 0;
    }
    if (effect->ctx->active == 0) {
        return 0;
    }
    fn_80033620(effect);
    p = effect->particles;
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
    do {
        if (p->_4A != 0) {
            if (p->_4C == 1) {
                fn_3_1504EC(effect, p);
            } else if (p->_4C == 2) {
                fn_3_150120(effect, p);
            }
        }
        p = p->next;
    } while (p != NULL);
    return 0;
}

// .text:0x1504EC size:0x454
void fn_3_1504EC(MGWeatherEffect* effect, MGParticle* p) {
    s32 duration;
    s32 alpha;
    s32 alphaStep;
    f32 sizeStep;

    if (p->_48 != 0) {
        p->_48--;
        if (p->_48 == 0) {
            fn_3_151068(effect, p);
        }
        return;
    }
    fn_8003403C(p->_38, p->_3C);
    fn_80033CC8(p, effect->_10);
    duration = lbl_3_data_26C3C[6];
    alpha = p->alphaByte;
    if (duration / p->_4A < 2) {
        alphaStep = lbl_3_data_26C3C[5] / (duration / 2);
        sizeStep = (f32)lbl_3_data_26C3C[3] / 100000.0f / (f32)(duration / 2);
    } else {
        alphaStep = -lbl_3_data_26C3C[5] / (duration / 2);
        sizeStep = -((f32)lbl_3_data_26C3C[3] / 100000.0f) / (f32)(duration / 2);
    }
    alpha = alpha + alphaStep;
    if (alpha > 0xFF) {
        alpha = 0xFF;
    } else if (alpha < 0) {
        alpha = 0;
    }
    p->alphaByte = alpha;
    p->_38 += sizeStep;
    p->_3C = p->_38;
    p->_4A--;
    if (p->_4A == 0) {
        fn_3_151068(effect, p);
    }
}

// .text:0x150120 size:0x3CC
void fn_3_150120(MGWeatherEffect* effect, MGParticle* p) {
    if (p->_48 != 0) {
        p->_48--;
        return;
    }
    setParticleXform(p->_38, p->_3C, p->_1C);
    fn_80033CC8(p, effect->_10);
    p->origin.x += p->velX;
    p->origin.y -= p->velY;
    p->origin.z += p->velZ;
    if (p->origin.y > 0.0f) {
        p->origin.y = 0.0f;
        p->velY = -p->velY * ((f32)lbl_3_data_26C3C[15] / 100000.0f);
    }
    p->_4A--;
    if (p->_4A == 0) {
        fn_3_150D84(effect, p);
    }
}

// .text:0x1500C8 size:0x58
void wallBall_updateSomePointers(void) {
    MGEffect* effect = fn_800339F0(0, 0x1D);
    MGParticle* p;

    if (effect != NULL) {
        p = effect->particles;
        do {
            p->_4A = 0;
            p->_48 = 0;
            p->_4C = 0;
            p = p->next;
        } while (p != NULL);
    }
    pitchingMachinePitching(0x1D);
}

// .text:0x150070 size:0x58
void fn_3_150070(void) {
    MGEffect* effect = fn_800339F0(0, 0x1D);
    MGParticle* p;

    if (effect != NULL) {
        p = effect->particles;
        do {
            p->_4A = 0;
            p->_48 = 0;
            p->_4C = 0;
            p = p->next;
        } while (p != NULL);
    }
    pitchingMachinePitching(0x1D);
}

// .text:0x150010 size:0x60
void fn_3_150010(s8 index) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && g_Minigame.GameMode_MiniGame == MINI_GAME_ID_STAR_DASH) {
        if (index <= 4 && index >= 0) {
            fn_3_14F930(index);
        }
    }
}

// .text:0x14F930 size:0x6E0
void fn_3_14F930(s8 index) {
    MGEffect* effect = fn_800339F0(0, 0x1E);
    if (effect != NULL) {
        mgStarSparksSetup(effect, index);
    } else {
        effect = allocParticleEffect(fn_3_14ED24, 0x80, 0, lbl_3_data_26C94[1], TRUE, 0x1E);
        if (effect != NULL) {
            fn_3_14F8D0(effect);
            mgStarSparksSetup(effect, index);
        }
    }
}

// .text:0x14F8D0 size:0x60
void fn_3_14F8D0(MGEffect* effect) {
    MGParticle* p;
    u32 i = 0;

    effect->_10 = *(u32*)&animRelated[0x6C];
    p = effect->particles;
    do {
        p->_4F = 0;
        p->_4D = lbl_3_data_26C94[0];
        p->_4E = 0;
        p->_4C = i / 18 + 1;
        i++;
        p = p->next;
    } while (p != NULL);
}

// .text:0x14F5A4 size:0x32C
void fn_3_14F5A4(MGEffect* effect, s8 index) {
    mgStarSparksSetup(effect, index);
}

// .text:0x14F544 size:0x60
void fn_3_14F544(MGParticle* p) {
    p->_4A = lbl_3_data_26C94[7];
    p->alphaByte = lbl_3_data_26C94[5];
    p->_38 = p->_3C = (f32)lbl_3_data_26C94[2] / 100000.0f;
}

// .text:0x14F3CC size:0x178
void fn_3_14F3CC(MGParticle* p) {
    Vec v = { 0.0f, 0.0f, 0.0f };
    f32 yOffset;
    s16 rangeX;
    s16 rangeY;

    if (p->_4C < 5) {
        yOffset = 1.25f;
    } else {
        yOffset = 0.5f;
    }
    rangeX = (p->_4C < 5) ? 20000 : 10000;
    rangeY = (p->_4C < 5) ? 20000 : 10000;
    v.x = v.x + (f32)(rand() % rangeX - rangeX / 2) / 10000.0f;
    v.y = v.y + (f32)(rand() % rangeY - rangeY / 2) / 10000.0f;
    p->origin.x = v.x;
    p->origin.y = v.y - yOffset;
    p->origin.z = v.z;
}

// .text:0x14ED24 size:0x6A8
int fn_3_14ED24(MGEffect* effect) {
    MGParticle* p;
    s32 duration;
    s32 alpha;
    f32 sizeStep;

    fn_80033620(effect);
    p = effect->particles;
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    do {
        if (p->_4A != 0) {
            if (p->_48 <= 0) {
                GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
                fn_8003403C(p->_38, p->_3C);
                fn_80033CC8(p, effect->_10);
                duration = lbl_3_data_26C94[7];
                if (duration / p->_4A < 2) {
                    alpha = p->alphaByte + lbl_3_data_26C94[6] / (duration / 2);
                    if (alpha > lbl_3_data_26C94[6]) {
                        alpha = lbl_3_data_26C94[6];
                    }
                    p->alphaByte = alpha;
                    sizeStep = (f32)(lbl_3_data_26C94[3] - lbl_3_data_26C94[2]) / 100000.0f / (f32)(duration / 2);
                    p->_38 += sizeStep;
                    p->_3C = p->_38;
                } else {
                    alpha = p->alphaByte - lbl_3_data_26C94[6] / (duration / 2);
                    if (alpha < lbl_3_data_26C94[5]) {
                        alpha = lbl_3_data_26C94[5];
                    }
                    p->alphaByte = alpha;
                    sizeStep = (f32)(lbl_3_data_26C94[4] - lbl_3_data_26C94[3]) / 100000.0f / (f32)(duration / 2);
                    p->_38 += sizeStep;
                    p->_3C = p->_38;
                }
                p->_4A--;
                if (p->_4A == 0) {
                    p->_4A = lbl_3_data_26C94[7];
                    p->alphaByte = lbl_3_data_26C94[5];
                    p->_38 = p->_3C = (f32)lbl_3_data_26C94[2] / 100000.0f;
                    mgStarSparkPlace(p);
                }
            } else {
                p->_48--;
                if (p->_48 == 0) {
                    mgStarSparkPlace(p);
                }
            }
        }
        p = p->next;
    } while (p != NULL);
    return 0;
}

// .text:0x14EAF4 size:0x230
void fn_3_14EAF4(MGParticle* p) {
    mgStarSparkPlace(p);
}

// .text:0x14E9F0 size:0x104
void fn_3_14E9F0(MGParticle* p) {
    mgStarSparkOffset(p);
}

// .text:0x14E988 size:0x68
void fn_3_14E988(s8 index) {
    MGEffect* effect = fn_800339F0(0, 0x1E);
    MGParticle* p;

    if (effect != NULL) {
        p = effect->particles;
        do {
            if (p->_4C == index + 1) {
                p->_4A = 0;
            }
            p = p->next;
        } while (p != NULL);
    }
}

// .text:0x14E920 size:0x68
void fn_3_14E920(s8 index) {
    MGEffect* effect = fn_800339F0(0, 0x1E);
    MGParticle* p;

    if (effect != NULL) {
        p = effect->particles;
        do {
            if (p->_4C == index + 1) {
                p->_4A = 0;
            }
            p = p->next;
        } while (p != NULL);
    }
}

// .text:0x14E894 size:0x8C
void fn_3_14E894(void) {
    u32 i;

    for (i = 0; i < 4; i++) {
        fn_3_14E988(i);
    }
    pitchingMachinePitching(0x1E);
}

// .text:0x14E810 size:0x84
void fn_3_14E810(void) {
    u32 i;

    for (i = 0; i < 4; i++) {
        fn_3_14E920(i);
    }
    pitchingMachinePitching(0x1E);
}

// .text:0x14E7C0 size:0x50
void fn_3_14E7C0(MGEffect* arg) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && g_Minigame.GameMode_MiniGame == MINI_GAME_ID_STAR_DASH &&
        arg != NULL) {
        fn_3_14E234((Vec*)arg);
    }
}

// .text:0x14E234 size:0x58C
void fn_3_14E234(Vec* pos) {
    MGEffect* existing = fn_800339F0(0, 0x1F);
    MGEffect* fresh;
    u8 scratch[0x80];

    if (existing != NULL) {
        fresh = fn_800337CC(scratch, lbl_3_data_26CD0[1], 1);
        if (fresh != NULL) {
            MGParticle* tail;

            mgStarDashDustInit(fresh, pos);
            tail = existing->particles;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = fresh->particles;
            existing->count += fresh->count;
        }
    } else {
        fresh = allocParticleEffect(fn_3_14DD04, 0x80, 0, lbl_3_data_26CD0[1], TRUE, 0x1F);
        if (fresh != NULL) {
            mgStarDashDustInit(fresh, pos);
        }
    }
}

// .text:0x14DF6C size:0x2C8
void fn_3_14DF6C(MGEffect* effect, Vec* pos) {
    MGParticle* p = effect->particles;
    f32 speed;

    effect->_10 = *(u32*)&animRelated[0x6C];
    do {
        p->_4D = lbl_3_data_26CD0[0];
        p->_4E = 0;
        p->origin.x = pos->x + (f32)(rand() % 1000 - 500) / 1000.0f;
        p->origin.y = -(0.75f + pos->y);
        p->origin.z = pos->z + (f32)(rand() % 1000 - 500) / 1000.0f;
        p->velX = p->velZ = 0.0f;
        p->velY = (f32)lbl_3_data_26CD0[9] / 100000.0f;
        speed = p->velY;
        p->velY = p->velY + ((f32)(rand() % (s32)(1000.0f * (speed * 0.5f))) - 1000.0f * (speed * 0.25f)) / 1000.0f;
        p->_40 = p->_41 = p->_42 = 0xFF;
        p->alphaByte = lbl_3_data_26CD0[6];
        p->_1C = (f32)(rand() % 1000 + 500) / 1000.0f;
        p->_38 = p->_3C = ((f32)lbl_3_data_26CD0[3] / 100000.0f) * p->_1C;
        p->_4A = lbl_3_data_26CD0[2];
        p->_48 = 0;
        p = p->next;
    } while (p != NULL);
}

// .text:0x14DD04 size:0x268
int fn_3_14DD04(MGEffect* effect) {
    MGParticle* p;
    MGParticle** link;
    MGParticle* removedTail = NULL;
    u32 alive = 0;
    s32 duration;
    s32 alpha;
    s32 alphaStep;
    f32 sizeStep;

    effect->particles = fn_80031F34(effect->particles, effect->count);
    p = effect->particles;
    link = &effect->particles;
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
    do {
        if (p->_4A != 0) {
            fn_8003403C(p->_38, p->_3C);
            fn_80033CC8(p, effect->_10);
            p->origin.y = p->origin.y - p->velY;
            p->velY = p->velY - (f32)lbl_3_data_26CD0[10] / 100000.0f;
            duration = lbl_3_data_26CD0[2];
            alpha = p->alphaByte;
            if (duration / p->_4A < 2) {
                sizeStep = (f32)(lbl_3_data_26CD0[4] - lbl_3_data_26CD0[3]) / 100000.0f / (f32)(duration / 2) * p->_1C;
                alphaStep = (lbl_3_data_26CD0[7] - lbl_3_data_26CD0[6]) / (duration / 2);
            } else {
                sizeStep = (f32)(lbl_3_data_26CD0[5] - lbl_3_data_26CD0[4]) / 100000.0f / (f32)(duration / 2) * p->_1C;
                alphaStep = (lbl_3_data_26CD0[8] - lbl_3_data_26CD0[7]) / (duration / 2);
            }
            p->_38 += sizeStep;
            p->_3C = p->_38;
            alpha += alphaStep;
            if (alpha < 0) {
                alpha = 0;
            } else if (alpha > 0xFF) {
                alpha = 0xFF;
            }
            p->alphaByte = alpha;
            p->_4A--;
            if (p->_4A == 0) {
                *link = p->next;
                if (removedTail != NULL) {
                    removedTail->next = p;
                }
                removedTail = p;
                p->next = NULL;
                effect->count--;
            } else {
                link = &p->next;
                alive++;
            }
        }
        p = *link;
    } while (p != NULL);
    return alive == 0;
}

// .text:0x14DCE0 size:0x24
void fn_3_14DCE0(void) {
    pitchingMachinePitching(0x1F);
}

// .text:0x14DC80 size:0x60
void fn_3_14DC80(s8 index) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER) {
        if (index < 15 && index >= 0) {
            fn_3_14D710(index);
        }
    }
}

// .text:0x14D710 size:0x570
void fn_3_14D710(u8 index) {
    MGEffect* effect = fn_800339F0(0, 0x20);

    if (effect != NULL) {
        mgBarrelSparksSetup(effect, index);
    } else {
        effect = allocParticleEffect(fn_3_14CECC, 0xF0, 0, lbl_3_data_26D00[2], TRUE, 0x20);
        if (effect != NULL) {
            fn_3_14D6D4(effect);
            mgBarrelSparksSetup(effect, index);
        }
    }
}

// .text:0x14D6D4 size:0x3C
void fn_3_14D6D4(MGEffect* effect) {
    MGParticle* p;

    effect->_10 = *(u32*)&animRelated[0x6C];
    p = effect->particles;
    do {
        p->_46 = 0;
        p->_45 = 0;
        p->_44 = 0;
        p->_4A = 0;
        p->_4E = 0;
        p = p->next;
    } while (p != NULL);
}

// .text:0x14D44C size:0x288
void fn_3_14D44C(MGEffect* effect, int barrelIndex) {
    mgBarrelSparksSetup(effect, barrelIndex);
}

// .text:0x14D318 size:0x134
void fn_3_14D318(MGParticle* p) {
    Vec* barrel = (Vec*)&g_Minigame.barrels[p->_45];

    p->origin.x = barrel->x;
    p->origin.y = barrel->y - bB_barrelConsts[3] * 0.5f;
    p->origin.z = barrel->z;
    p->origin.x = p->origin.x + (rand() % 100 - 50) / 100.0;
    p->origin.y = p->origin.y + (rand() % 100 - 50) / 100.0;
}

// .text:0x14D2C0 size:0x58
void fn_3_14D2C0(MGParticle* p) {
    MGActorList* list = *(MGActorList**)(*(u8**)&hugeAnimStruct[0x68] + (p->_45 + 0x10) * 0x90 + 0x34);
    MGActor* actor = list->actors[p->_46];

    p->origin.x = actor->mtx[0][3];
    p->origin.y = actor->mtx[1][3];
    p->origin.z = actor->mtx[2][3];
}

// .text:0x14CECC size:0x3F4
int fn_3_14CECC(MGEffect* effect) {
    MGParticle* p;

    if (lbl_80366158[0x28] != 0) {
        return 0;
    }
    fn_80033620(effect);
    p = effect->particles;
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    do {
        if (p->_44 != 0 && p->_4A != 0) {
            if (p->_48 <= 0) {
                if (p->_44 == 1) {
                    fn_3_14CD40(effect, p);
                } else {
                    if (p->_48 == 0) {
                        fn_3_14D2C0(p);
                    }
                    fn_3_14CBB4(effect, p);
                }
                p->_4A--;
                if (p->_4A == 0) {
                    p->_44 = 0;
                    p->_45 = 0xFF;
                    p->_4A = 0;
                    p->_4C = 0;
                }
            }
            p->_48--;
        }
        p = p->next;
    } while (p != NULL);
    return 0;
}

// .text:0x14CD40 size:0x18C
void fn_3_14CD40(MGEffect* effect, MGParticle* p) {
    s32 duration;
    s32 range;
    s32 alpha;
    s32 alphaStep;
    f32 sizeStep;

    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_LO_CLEAR);
    fn_8003403C(p->_38, p->_3C);
    fn_80033CC8(p, effect->_10);
    duration = lbl_3_data_26D00[3];
    alpha = p->alphaByte;
    if (-p->_48 < duration) {
        sizeStep = (f32)lbl_3_data_26D00[5] / 100000.0f / (f32)duration;
        alphaStep = lbl_3_data_26D00[8] / duration;
    } else {
        range = lbl_3_data_26D00[17] - duration;
        sizeStep = (f32)(lbl_3_data_26D00[6] - lbl_3_data_26D00[5]) / 100000.0f / (f32)range;
        alphaStep = (lbl_3_data_26D00[9] - lbl_3_data_26D00[8]) / range;
    }
    alpha += alphaStep;
    if (alpha > 0xFF) {
        alpha = 0xFF;
    } else if (alpha < 0) {
        alpha = 0;
    }
    p->alphaByte = alpha;
    p->_40 = p->_41 = p->_42 = p->alphaByte;
    p->_38 += sizeStep;
    p->_3C = p->_38;
}

// .text:0x14CBB4 size:0x18C
void fn_3_14CBB4(MGEffect* effect, MGParticle* p) {
    s32 duration;
    s32 range;
    s32 alpha;
    s32 alphaStep;
    f32 sizeStep;

    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    fn_8003403C(p->_38, p->_3C);
    fn_80033CC8(p, effect->_10);
    duration = lbl_3_data_26D00[10];
    alpha = p->alphaByte;
    if (-p->_48 < duration) {
        sizeStep = (f32)lbl_3_data_26D00[12] / 100000.0f / (f32)duration;
        alphaStep = lbl_3_data_26D00[15] / duration;
    } else {
        range = lbl_3_data_26D00[18] - duration;
        sizeStep = (f32)(lbl_3_data_26D00[13] - lbl_3_data_26D00[12]) / 100000.0f / (f32)range;
        alphaStep = (lbl_3_data_26D00[16] - lbl_3_data_26D00[15]) / range;
    }
    alpha += alphaStep;
    if (alpha > 0xFF) {
        alpha = 0xFF;
    } else if (alpha < 0) {
        alpha = 0;
    }
    p->alphaByte = alpha;
    p->_40 = p->_41 = p->_42 = p->alphaByte;
    p->_38 += sizeStep;
    p->_3C = p->_38;
}

// .text:0x14CB28 size:0x8C
void fn_3_14CB28(s8 index) {
    MGEffect* effect;
    MGParticle* p;

    if (index < 15 && index >= 0) {
        effect = fn_800339F0(0, 0x20);
        if (effect != NULL) {
            p = effect->particles;
            do {
                if (p->_45 == index) {
                    p->_44 = 0;
                    p->_45 = 0xFF;
                    p->_4A = 0;
                    p->_4C = 0;
                }
                p = p->next;
            } while (p != NULL);
        }
    }
}

// .text:0x14CAB4 size:0x74
void fn_3_14CAB4(s8 index) {
    MGEffect* effect = fn_800339F0(0, 0x20);
    MGParticle* p;

    if (effect != NULL) {
        p = effect->particles;
        do {
            if (p->_45 == index) {
                p->_44 = 0;
                p->_45 = 0xFF;
                p->_4A = 0;
                p->_4C = 0;
            }
            p = p->next;
        } while (p != NULL);
    }
}

// .text:0x14CA98 size:0x1C
void fn_3_14CA98(MGParticle* p) {
    p->_44 = 0;
    p->_45 = 0xFF;
    p->_4A = 0;
    p->_4C = 0;
}

// .text:0x14CA00 size:0x98
void fn_3_14CA00(void) {
    u32 i;

    for (i = 0; i < 15; i++) {
        fn_3_14CAB4(i);
    }
    pitchingMachinePitching(0x20);
}

// .text:0x14C904 size:0xFC
void fn_3_14C904(void) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && g_Minigame.GameMode_MiniGame == MINI_GAME_ID_CHAINCHOMP_SPRINT) {
        fn_3_14C830();
    }
}

// .text:0x14C830 size:0xD4
void fn_3_14C830(void) {
    MGEffect* effect = allocParticleEffect(fn_3_14C4C8, 0x80, 0, lbl_3_data_26D5C[1], TRUE, 0xA);

    if (effect != NULL) {
        fn_3_14C79C(effect);
    }
}

// .text:0x14C79C size:0x94
void fn_3_14C79C(MGEffect* effect) {
    MGParticle* p;

    effect->_10 = *(u32*)&animRelated[0x6C];
    p = effect->particles;
    p->_4D = lbl_3_data_26D5C[0];
    p->_4E = 0;
    p->_4A = lbl_3_data_26D5C[2];
    p->_38 = p->_3C = (f32)lbl_3_data_26D5C[4] / 100000.0f;
    p->alphaByte = lbl_3_data_26D5C[7];
    p->_40 = p->_41 = p->_42 = 0xFF;
}

// .text:0x14C4C8 size:0x2D4
int fn_3_14C4C8(MGEffect* effect) {
    MGParticle* p;
    s32 duration;
    s32 remaining;
    s32 alpha;
    s32 alphaStep;
    f32 sizeStep;

    if (lbl_80366158[0x28] != 0) {
        return 0;
    }
    p = effect->particles;
    if (p->_4A == 0) {
        return 1;
    }
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_LO_CLEAR);
    fn_3_14C3BC(p);
    fn_8003403C(p->_38, p->_3C);
    fn_80033CC8(p, effect->_10);
    duration = lbl_3_data_26D5C[3];
    remaining = lbl_3_data_26D5C[2] - duration;
    alpha = p->alphaByte;
    if (remaining < p->_4A) {
        sizeStep = (f32)(lbl_3_data_26D5C[5] - lbl_3_data_26D5C[4]) / 100000.0f / (f32)duration;
        alphaStep = (lbl_3_data_26D5C[8] - lbl_3_data_26D5C[7]) / duration;
    } else {
        sizeStep = (f32)(lbl_3_data_26D5C[6] - lbl_3_data_26D5C[5]) / 100000.0f / (f32)remaining;
        alphaStep = (lbl_3_data_26D5C[9] - lbl_3_data_26D5C[8]) / remaining;
    }
    alpha += alphaStep;
    if (alpha < 0) {
        alpha = 0;
    }
    if (alpha > 0xFF) {
        alpha = 0xFF;
    }
    p->_38 += sizeStep;
    p->_3C = p->_38;
    p->alphaByte = alpha;
    p->_40 = p->_41 = p->_42 = p->alphaByte;
    p->_4A--;
    return 0;
}

// .text:0x14C3BC size:0x10C
void fn_3_14C3BC(MGParticle* p) {
    Vec offset;
    Mtx rot;

    PSVECScale(&lbl_3_data_26D50, 0.75f, &offset);
    PSMTXRotRad(rot, 'Y', shortAngleToRad(g_Minigame.ccs.chompYaw));
    PSMTXMultVec(rot, &offset, &offset);
    p->origin.x = g_Minigame.ccs.chompPos.x + offset.x + (f32)lbl_3_data_26D5C[5] / 100000.0f * 0.5f;
    p->origin.y = offset.y - ((f32)lbl_3_data_26D5C[5] / 100000.0f * 0.5f + g_Minigame.ccs.chompPos.y);
    p->origin.z = g_Minigame.ccs.chompPos.z + offset.z;
}

// .text:0x14C398 size:0x24
void fn_3_14C398(void) {
    pitchingMachinePitching(0x21);
}

// .text:0x14C348 size:0x50
void fn_3_14C348(Vec* pos, u8 flag) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && g_Minigame.GameMode_MiniGame == MINI_GAME_ID_WALLBALL && pos != NULL) {
        fn_3_14BECC(pos, flag);
    }
}

// .text:0x14BECC size:0x47C
void fn_3_14BECC(Vec* pos, u8 flag) {
    MGEffect* existing = fn_800339F0(0, 0x22);
    MGEffect* fresh;
    u8 scratch[0x80];

    if (existing != NULL) {
        fresh = fn_800337CC(scratch, lbl_3_data_26D88[1], 1);
        fn_3_14BCB0(fresh, pos, flag);
        if (existing->particles != NULL) {
            MGParticle* tail = existing->particles;

            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = fresh->particles;
        } else {
            existing->particles = fresh->particles;
        }
        existing->count += fresh->count;
    } else {
        fresh = allocParticleEffect(fn_3_14BA40, 0x80, 0, lbl_3_data_26D88[1], TRUE, 0x22);
        if (fresh != NULL) {
            fn_3_14BCB0(fresh, pos, flag);
        }
    }
}

// .text:0x14BCB0 size:0x21C
void fn_3_14BCB0(MGEffect* effect, Vec* pos, u8 flag) {
    MGParticle* p;
    s32* tbl = lbl_3_data_26D88;
    u32 count = 0;
    f32 speed;
    f32 angle;

    effect->_10 = *(u32*)&animRelated[0x6C];
    p = effect->particles;
    if (flag != 0) {
        tbl = lbl_3_data_26DC4;
    }
    do {
        if (p->_4A == 0) {
            p->_4D = tbl[0];
            p->_4E = 0;
            p->_4A = tbl[2];
            p->_38 = p->_3C = (f32)tbl[4] / 100000.0f;
            p->alphaByte = tbl[10];
            p->_40 = tbl[7];
            p->_41 = tbl[8];
            p->_42 = tbl[9];
            speed = 2.0f * (2.0 * ((f32)rand() / 32767.0f - 0.5));
            angle = 0.017453292f * (f32)(180.0 / tbl[1] * count);
            p->origin.x = pos->x + speed * (f32)cos(angle);
            p->origin.y = pos->y - speed * (f32)sin(angle) - 1.0;
            count++;
            p->origin.z = pos->z;
            p->_4F = flag;
        }
        p = p->next;
    } while (p != NULL && count < lbl_3_data_26D88[1]);
}

// .text:0x14BA40 size:0x270
int fn_3_14BA40(MGEffect* effect) {
    MGParticle* p;
    MGParticle** link;
    MGParticle* removedTail = NULL;
    MGParticle* removedHead = NULL;
    u32 alive = 0;
    s32* tbl;
    s32 duration;
    s32 rampLength;
    s32 alpha;
    s32 alphaStep;
    f32 sizeStep;

    if (lbl_80366158[0x28] != 0) {
        return 0;
    }
    effect->particles = fn_80031F34(effect->particles, effect->count);
    p = effect->particles;
    link = &effect->particles;
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    do {
        if (p->_4A != 0) {
            tbl = lbl_3_data_26DC4;
            if (p->_4F == 0) {
                tbl = lbl_3_data_26D88;
            }
            duration = tbl[2];
            rampLength = tbl[3];
            fn_8003403C(p->_38, p->_3C);
            fn_80033CC8(p, effect->_10);
            alpha = p->alphaByte;
            if (duration - p->_4A < rampLength) {
                sizeStep = (f32)((tbl[5] - tbl[4]) / rampLength) / 100000.0f;
                alphaStep = (tbl[11] - tbl[10]) / rampLength;
            } else {
                s32 remaining = duration - rampLength;

                sizeStep = (f32)((tbl[6] - tbl[5]) / remaining) / 100000.0f;
                alphaStep = (tbl[12] - tbl[11]) / remaining;
            }
            alpha += alphaStep;
            if (alpha > 0xFF) {
                alpha = 0xFF;
            }
            if (alpha < 0) {
                alpha = 0;
            }
            p->alphaByte = alpha;
            p->_38 += sizeStep;
            p->_3C = p->_38;
            p->_4A--;
            if (p->_4A == 0) {
                *link = p->next;
                if (removedTail != NULL) {
                    removedTail->next = p;
                } else {
                    removedHead = p;
                }
                removedTail = p;
                p->next = NULL;
                effect->count--;
            } else {
                link = &p->next;
                alive++;
            }
        }
        p = *link;
    } while (p != NULL);
    if (removedHead != NULL) {
        p = removedHead;
        do {
            p->_4C = 0;
            p->_48 = 0;
            p = p->next;
        } while (p != NULL);
        fn_80033794(removedHead);
    }
    return alive == 0;
}

// .text:0x14B9F0 size:0x50
void fn_3_14B9F0(void) {
    MGEffect* effect = fn_800339F0(0, 0x22);
    MGParticle* p;

    if (effect != NULL) {
        p = effect->particles;
        do {
            p->_4A = 0;
            p = p->next;
        } while (p != NULL);
    }
    pitchingMachinePitching(0x22);
}

// .text:0x14B9A0 size:0x50
void fn_3_14B9A0(s16 frames, Vec* start) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER &&
        start != NULL) {
        fn_3_14B92C(frames, start);
    }
}

// .text:0x14B92C size:0x74
#pragma dont_inline on
void fn_3_14B92C(s16 frames, Vec* start) {
    MGPathEffect* effect = allocParticleEffect(fn_3_14AC40, 0x80, 0, lbl_3_data_26E24[2], TRUE, 0x23);
    if (effect != NULL) {
        fn_3_14B53C(effect, frames, start);
    }
}
#pragma dont_inline reset

// .text:0x14B53C size:0x3F0
void fn_3_14B53C(MGPathEffect* effect, s16 frames, Vec* start) {
    MGParticle* p;
    Vec diff;
    f32 seg1;
    f32 seg2;
    u32 i = 0;

    effect->base.x = start->x;
    effect->base.y = start->y;
    effect->base.z = start->z;
    effect->_10 = *(u32*)&animRelated[0x6C];
    effect->total = frames;
    effect->remaining = frames;
    PSVECSubtract((Vec*)(lbl_3_data_26E00 + 3), (Vec*)lbl_3_data_26E00, &diff);
    seg1 = PSVECMag(&diff);
    PSVECSubtract((Vec*)(lbl_3_data_26E00 + 6), (Vec*)(lbl_3_data_26E00 + 3), &diff);
    seg2 = PSVECMag(&diff);
    effect->span = seg1 / ((seg2 + seg1) / (f32)(u32)frames);
    fn_3_14B3F4(effect);
    p = effect->particles;
    do {
        p->_4D = lbl_3_data_26E24[0];
        p->_4E = 0;
        p->_48 = (s16)((f32)i * ((f32)effect->total / (f32)lbl_3_data_26E24[2]));
        p->_40 = p->_41 = p->_42 = 0xFF;
        p->_4A = lbl_3_data_26E24[1];
        if (p->_48 == 0) {
            fn_3_14B248(effect, p);
        }
        p = p->next;
        i++;
    } while (p != NULL);
}

// .text:0x14B3F4 size:0x148
void fn_3_14B3F4(MGPathEffect* effect) {
    f32* from;
    f32* to;
    f32 t;
    f32 scale;

    if ((f32)(effect->total - effect->remaining) < effect->span) {
        from = lbl_3_data_26E00;
        to = from + 3;
        t = (f32)(effect->total - effect->remaining) / effect->span;
    } else {
        from = lbl_3_data_26E00 + 3;
        to = lbl_3_data_26E00 + 6;
        t = ((f32)(effect->total - effect->remaining) - effect->span) / ((f32)effect->total - effect->span);
    }
    scale = mm_GetPitchingMachineScale();
    effect->pos.x = scale * (from[0] * (1.0f - t) + to[0] * t) + effect->base.x;
    effect->pos.y = scale * (from[1] * (1.0f - t) + to[1] * t) + effect->base.y;
    effect->pos.z = scale * (from[2] * (1.0f - t) + to[2] * t) + effect->base.z;
}

// .text:0x14B248 size:0x1AC
void fn_3_14B248(MGPathEffect* effect, MGParticle* p) {
    f32 angle;
    f32 radius;
    f32 cosA;
    f32 dx;
    f32 dy;

    p->_38 = p->_3C = (f32)lbl_3_data_26E24[3] / 100000.0f;
    p->alphaByte = lbl_3_data_26E24[5];
    angle = 0.017453292f * (f32)(rand() % 360);
    radius = (f32)((u32)rand() % 200 / 1000.0);
    cosA = cos(angle);
    dx = radius * cosA;
    dy = radius * (f32)sin(angle);
    p->origin.x = effect->pos.x + dx;
    p->origin.y = effect->pos.y + dy;
    p->origin.z = effect->pos.z + 0.0f;
    p->_4A = lbl_3_data_26E24[1];
}

// .text:0x14AC40 size:0x608
int fn_3_14AC40(MGPathEffect* effect) {
    MGParticle* p;
    s32 alphaStep;
    s32 alpha;
    f32 sizeStep;

    if (lbl_80366158[0x28] != 0) {
        return 0;
    }
    fn_80033620(effect);
    p = effect->particles;
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
    if (lbl_80366158[0x28] == 0) {
        fn_3_14B3F4(effect);
        effect->remaining--;
    }
    sizeStep = 2.0f * ((f32)(lbl_3_data_26E24[4] - lbl_3_data_26E24[3]) / 100000.0f / (f32)lbl_3_data_26E24[1]);
    alphaStep = (lbl_3_data_26E24[6] - lbl_3_data_26E24[5]) / lbl_3_data_26E24[1] * 2;
    do {
        if (p->_4A != 0) {
            if (p->_48 > 0) {
                p->_48--;
                if (p->_48 == 0) {
                    fn_3_14B248(effect, p);
                }
            } else {
                fn_8003403C(p->_38, p->_3C);
                fn_80033CC8(p, effect->_10);
                alpha = p->alphaByte;
                if (lbl_3_data_26E24[1] / p->_4A < 2) {
                    sizeStep = fabs(sizeStep);
                    alphaStep = (s32)fabs((f64)alphaStep);
                } else {
                    sizeStep = -1.0 * fabs(sizeStep);
                    alphaStep = (s32)(-1.0 * fabs((f64)alphaStep));
                }
                alpha += alphaStep;
                if (alpha > 0xFF) {
                    alpha = 0xFF;
                }
                if (alpha < 0) {
                    alpha = 0;
                }
                p->_38 += sizeStep;
                p->_3C = p->_38;
                p->alphaByte = alpha;
                p->_4A--;
                if (p->_4A == 0) {
                    fn_3_14B248(effect, p);
                }
            }
        }
        p = p->next;
    } while (p != NULL);
    return effect->remaining == 0;
}

// .text:0x14AC1C size:0x24
void fn_3_14AC1C(void) {
    pitchingMachinePitching(0x23);
}

// .text:0x14A90C size:0x310
void barrelBatterRel(Vec* pos) {
    MGEffect* effect;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER &&
        pos != NULL) {
        effect = allocParticleEffect(fn_3_14A188, 0x80, 0, lbl_3_data_26E40[1], TRUE, 0x24);
        if (effect != NULL) {
            mgBarrelRingInit(effect, pos);
        }
    }
}

// .text:0x14A62C size:0x2E0
void fn_3_14A62C(Vec* pos) {
    MGEffect* effect = allocParticleEffect(fn_3_14A188, 0x80, 0, lbl_3_data_26E40[1], TRUE, 0x24);

    if (effect != NULL) {
        mgBarrelRingInit(effect, pos);
    }
}

// .text:0x14A37C size:0x2B0
void fn_3_14A37C(MGEffect* effect, Vec* pos) {
    mgBarrelRingInit(effect, pos);
}

// .text:0x14A188 size:0x1F4
int fn_3_14A188(MGEffect* effect) {
    MGParticle* p;
    u32 alive = 0;
    s32 alpha;
    s32 alphaStep;
    s32 remaining;
    f32 sizeStep;

    if (lbl_80366158[0x28] != 0) {
        return 0;
    }
    fn_80033620(effect);
    p = effect->particles;
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    do {
        if (p->_4A != 0) {
            alpha = p->alphaByte;
            setParticleXform(p->_38, p->_3C, p->velX);
            fn_80033CC8(p, effect->_10);
            if (lbl_3_data_26E40[2] - p->_4A < lbl_3_data_26E40[4]) {
                sizeStep = (p->velZ - (f32)lbl_3_data_26E40[5] / 100000.0f) / (f32)lbl_3_data_26E40[4];
                alphaStep = (lbl_3_data_26E40[10] - lbl_3_data_26E40[9]) / lbl_3_data_26E40[4];
            } else {
                remaining = lbl_3_data_26E40[2] - lbl_3_data_26E40[4];
                sizeStep = ((f32)lbl_3_data_26E40[8] / 100000.0f + p->velZ) / (f32)remaining;
                alphaStep = (lbl_3_data_26E40[11] - lbl_3_data_26E40[10]) / remaining;
            }
            alpha += alphaStep;
            if (alpha < 0) {
                alpha = 0;
            }
            if (alpha > 0xFF) {
                alpha = 0xFF;
            }
            p->alphaByte = alpha;
            p->_38 += sizeStep;
            p->_3C = p->_38;
            p->velX += p->velY;
            p->_4A--;
            if (p->_4A != 0) {
                alive++;
            }
        }
        p = p->next;
    } while (p != NULL);
    return alive == 0;
}

// .text:0x14A164 size:0x24
void fn_3_14A164(void) {
    pitchingMachinePitching(0x24);
}

// .text:0x14A070 size:0xF4
void fn_3_14A070(s32* values, s32 count) {
    s8* slots = (s8*)&lbl_3_bss_B85C;
    u32 i;

    slots[0] = -1;
    slots[1] = -1;
    slots[2] = -1;
    slots[3] = -1;
    if (count > 4) {
        return;
    }
    if (count == 0) {
        return;
    }
    if (values == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        slots[i] = values[i];
    }
}

// .text:0x149BA8 size:0x4C8
void fn_3_149BA8(void) {
    s8* slots = (s8*)&lbl_3_bss_B85C;
    u32 i;
    s8 index;
    MGStarEffect* effect;

    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES && g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD) {
        lbl_3_data_26E7C[5] = 930000;
    } else {
        lbl_3_data_26E7C[5] = 750000;
    }
    for (i = 0; i < 4; i++) {
        index = slots[i];
        if (index > -1) {
            effect = allocParticleEffect(fn_3_14841C, 0x80, 0, lbl_3_data_26E7C[0], TRUE, 0x25);
            if (effect != NULL) {
                effect->index = index;
                fn_3_149340(effect);
            }
        }
    }
}

// .text:0x14975C size:0x44C
void fn_3_14975C(s8 index) {
    MGStarEffect* effect = allocParticleEffect(fn_3_14841C, 0x80, 0, lbl_3_data_26E7C[0], TRUE, 0x25);

    if (effect != NULL) {
        effect->index = index;
        fn_3_149340(effect);
    }
}

// .text:0x149340 size:0x41C
void fn_3_149340(MGStarEffect* effect) {
    MGParticle* p = effect->particles;
    u32 i = 0;
    s32 n;

    do {
        p->_4A = 0;
        p->_38 = (f32)lbl_3_data_26E7C[3] / 100000.0f;
        p->_3C = (f32)lbl_3_data_26E7C[4] / 100000.0f;
        mgStarParticleInit(effect->index, p);
        n = lbl_3_data_26E7C[0] / 5;
        p->_48 = (i % 5 * n + rand() % n) * 2;
        i++;
        p = p->next;
    } while (p != NULL);
}

// .text:0x148FD0 size:0x370
void fn_3_148FD0(s8 index, MGParticle* p) {
    mgStarParticleInit(index, p);
}

// .text:0x148EF0 size:0xE0
void fn_3_148EF0(Vec* out, f32 degrees) {
    f32 angle = 0.017453292f * degrees;
    f32 s = sin(angle);
    f32 c = cos(angle);

    out->x = s * (f32)lbl_3_data_26E7C[1] / 100000.0f;
    out->y = c * (f32)lbl_3_data_26E7C[1] / 100000.0f;
    out->z = 0.0f;
}

// .text:0x14841C size:0xAD4
int fn_3_14841C(MGStarEffect* effect) {
    f32* actor = *(f32**)(hugeAnimStruct + 0x2C50 + effect->index * 4);
    MGParticle* p = effect->particles;

    fn_3_147F94();
    do {
        if (p->_48 <= 0) {
            fn_3_148254(effect, p);
            fn_3_1480E0(p);
            PSVECAdd(&p->origin, (Vec*)&p->velX, &p->origin);
            PSVECAdd((Vec*)&p->_1C, (Vec*)&p->_28, (Vec*)&p->_1C);
            if (rand() % 5 == 0) {
                Vec ref = { 0.0f, 1.0f, 0.0f };
                Vec dir;
                f32 angle;
                f32 jitter;
                f32 rad;

                memcpy(&dir, &p->velX, sizeof(Vec));
                PSVECNormalize(&dir, &dir);
                angle = 57.29578f * (f32)acos(PSVECDotProduct(&ref, &dir));
                if (dir.x < 0.0f) {
                    angle *= -1.0f;
                }
                jitter = 20.0 * (2.0 * ((f32)rand() / 32767.0f - 0.5));
                if (fabs(angle + jitter) > 20.0) {
                    angle = 20.0 * (fabs(angle) / angle);
                } else {
                    angle += jitter;
                }
                rad = 0.017453292f * angle;
                p->velX = (f32)sin(rad) * (f32)lbl_3_data_26E7C[1] / 100000.0f;
                p->velY = (f32)cos(rad) * (f32)lbl_3_data_26E7C[1] / 100000.0f;
                p->velZ = 0.0f;
                p->_4C++;
            }
            if (-p->origin.y - p->_3C < actor[0x38 / 4]) {
                mgStarParticleInit(effect->index, p);
            }
        } else {
            p->_48--;
        }
        p = p->next;
    } while (p != NULL);
    fn_3_147E20();
    return 0;
}

// .text:0x1483D4 size:0x48
BOOL fn_3_1483D4(void) {
    return rand() % 5 == 0;
}

// .text:0x148254 size:0x180
void fn_3_148254(MGStarEffect* effect, MGParticle* p) {
    f32 halfW = p->_38 * 0.5f;
    f32 halfH = p->_3C * 0.5f;
    f32* actor = *(f32**)(hugeAnimStruct + 0x2C50 + effect->index * 4);
    f32* v = lbl_3_bss_B860;
    Mtx mtx;
    Vec pos;
    Control ctrl;

    v[3] = halfW;
    v[0] = -halfW;
    v[1] = -halfH;
    v[4] = -halfH;
    v[6] = halfW;
    v[7] = halfH;
    v[9] = -halfW;
    v[10] = halfH;
    PSMTXInverse(fn_80052768_getCamera(0)->view, mtx);
    mtx[1][1] = 1.0f;
    mtx[0][1] = 0.0f;
    mtx[1][0] = 0.0f;
    mtx[1][2] = 0.0f;
    mtx[2][1] = 0.0f;
    pos.x = p->origin.x;
    pos.y = p->origin.y;
    pos.z = p->origin.z;
    PSMTXMultVecSR(mtx, &pos, &pos);
    ctrl.type = 0;
    CTRLSetRotation(&ctrl, p->_1C, p->_20, p->alpha);
    CTRLSetTranslation(&ctrl, actor[0x34 / 4] + pos.x, -actor[0x38 / 4] + pos.y, actor[0x3C / 4] + pos.z);
    CTRLBuildMatrix(&ctrl, mtx);
    PSMTXConcat(fn_80052768_getCamera(0)->view, mtx, mtx);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
}

// .text:0x1480E0 size:0x174
void fn_3_1480E0(MGParticle* p) {
    f32* v = lbl_3_bss_B860;
    int i;

    GXSetCullMode(GX_CULL_BACK);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    for (i = 0; i < 4; i++) {
        GXWGFifo.f32 = v[i * 3 + 0];
        GXWGFifo.f32 = v[i * 3 + 1];
        GXWGFifo.f32 = v[i * 3 + 2];
        GXWGFifo.u32 = *(u32*)&p->_40;
    }
    GXSetCullMode(GX_CULL_FRONT);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    for (i = 0; i < 4; i++) {
        GXWGFifo.f32 = v[i * 3 + 0];
        GXWGFifo.f32 = v[i * 3 + 1];
        GXWGFifo.f32 = v[i * 3 + 2];
        GXWGFifo.u32 = *(u32*)&p->_44;
    }
}

// .text:0x147F94 size:0x14C
void fn_3_147F94(void) {
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
}

// .text:0x147E20 size:0x174
void fn_3_147E20(void) {
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetCullMode(GX_CULL_NONE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXLoadPosMtxImm(fn_80052768_getCamera(0)->view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
}

// .text:0x147DFC size:0x24
void fn_3_147DFC(void) {
    pitchingMachinePitching(0x26);
}

// .text:0x147CFC size:0x100
void fn_3_147CFC(Vec* pos) {
    if (pos != NULL) {
        fn_3_147C00(pos);
    }
}

// .text:0x147C00 size:0xFC
void fn_3_147C00(Vec* pos) {
    MGEffect* existing = fn_800339F0(0, 0x26);
    MGEffect* fresh;
    u8 scratch[0x80];

    if (existing != NULL) {
        fresh = fn_800337CC(scratch, lbl_3_data_26E9C[2] + lbl_3_data_26E9C[12], 1);
        if (fresh != NULL) {
            MGParticle* tail;

            fn_3_147778(fresh, pos);
            tail = existing->particles;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = fresh->particles;
            existing->count += fresh->count;
        }
    } else {
        fresh = allocParticleEffect(fn_3_14737C, 0x80, 0, lbl_3_data_26E9C[2] + lbl_3_data_26E9C[12], TRUE, 0x26);
        if (fresh != NULL) {
            fn_3_147778(fresh, pos);
        }
    }
}

// .text:0x147778 size:0x488
void fn_3_147778(MGEffect* effect, Vec* pos) {
    MGParticle* p;
    u32 burstCount = (u8)lbl_3_data_26E9C[2];
    u32 ringCount = (u8)lbl_3_data_26E9C[12];
    u32 i = 0;
    s32 delay = 0;
    f64 angle;

    if (pos->y > 0.0f) {
        pos->y = pos->y * -1.0f;
    }
    effect->_10 = *(u32*)&animRelated[0x6C];
    p = effect->particles;
    do {
        if (i < burstCount) {
            p->_4C = 1;
            p->velX = (i == 0) ? 3.0f : 1.5f;
            p->_4A = lbl_3_data_26E9C[1];
            p->_38 = p->_3C = (f32)lbl_3_data_26E9C[4] / 100000.0f * p->velX;
            p->alphaByte = lbl_3_data_26E9C[7];
            memcpy(&p->origin, pos, sizeof(Vec));
            if (i != 0) {
                angle = 0.017453292519943295 * (360.0 / (f64)burstCount) * (f64)(i - 1);
                p->origin.x += 1.5f * (f32)cos(angle);
                p->origin.y += 1.5f * (f32)sin(angle);
                p->origin.x = p->origin.x + 0.5 * ((f32)rand() / 32767.0f - 1.0);
                p->origin.y = p->origin.y + 0.5 * ((f32)rand() / 32767.0f - 1.0);
            }
            p->_4D = lbl_3_data_26E9C[0];
            p->_48 = delay;
        } else {
            p->_4C = 2;
            p->_4A = lbl_3_data_26E9C[11];
            p->_38 = p->_3C = (f32)lbl_3_data_26E9C[14] / 100000.0f;
            p->alphaByte = lbl_3_data_26E9C[17];
            memcpy(&p->origin, pos, sizeof(Vec));
            angle = 0.017453292519943295 * (360.0 / (f64)ringCount) * (f64)(u8)(i - burstCount);
            p->origin.x += 2.5f * (f32)cos(angle);
            p->origin.y += 2.5f * (f32)sin(angle);
            p->origin.x = p->origin.x + 0.2 * (2.0 * ((f32)rand() / 32767.0f - 0.5));
            p->origin.y = p->origin.y + 0.2f * (-1.0f * ((f32)rand() / 32767.0f));
            p->_4D = lbl_3_data_26E9C[10];
            p->_48 = 5;
        }
        p->_40 = p->_41 = p->_42 = 0xFF;
        delay += 2;
        i++;
        p->_4E = 0;
        p = p->next;
    } while (p != NULL);
}

// .text:0x14737C size:0x3FC
int fn_3_14737C(MGEffect* effect) {
    MGParticle* p;
    MGParticle** link;
    MGParticle* removedTail = NULL;
    u32 alive = 0;
    s32 idx;
    s32 rampLength;
    s32 duration;
    s32 alpha;
    s32 alphaStep;
    s32 remaining;
    f32 sizeStep;
    f32 scale;

    effect->particles = fn_80031F34(effect->particles, effect->count);
    p = effect->particles;
    link = &effect->particles;
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
    do {
        if (p->_4A != 0) {
            if (p->_48 <= 0) {
                if (p->_4C == 1) {
                    rampLength = lbl_3_data_26E9C[3];
                } else {
                    rampLength = lbl_3_data_26E9C[13];
                }
                if (p->_4C == 1) {
                    duration = lbl_3_data_26E9C[1];
                } else {
                    duration = lbl_3_data_26E9C[11];
                }
                if (p->_4C == 1) {
                    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
                } else {
                    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
                }
                fn_8003403C(p->_38, p->_3C);
                fn_80033CC8(p, effect->_10);
                alpha = p->alphaByte;
                if (p->_4C == 1) {
                    scale = p->velX;
                } else {
                    scale = 1.0f;
                }
                if (p->_4C == 1) {
                    idx = 0;
                } else {
                    idx = 10;
                }
                if (rampLength > duration - p->_4A) {
                    sizeStep = ((f32)lbl_3_data_26E9C[5 + idx] / 100000.0f - (f32)lbl_3_data_26E9C[4 + idx] / 100000.0f) /
                               (f32)rampLength * scale;
                    alphaStep = (lbl_3_data_26E9C[8 + idx] - lbl_3_data_26E9C[7 + idx]) / rampLength;
                } else {
                    remaining = duration - rampLength;
                    sizeStep = ((f32)lbl_3_data_26E9C[6 + idx] / 100000.0f - (f32)lbl_3_data_26E9C[5 + idx] / 100000.0f) /
                               (f32)remaining * scale;
                    alphaStep = (lbl_3_data_26E9C[9 + idx] - lbl_3_data_26E9C[8 + idx]) / remaining;
                }
                alpha += alphaStep;
                if (alpha < 0) {
                    alpha = 0;
                } else if (alpha > 0xFF) {
                    alpha = 0xFF;
                }
                p->_38 += sizeStep;
                p->_3C = p->_38;
                p->alphaByte = alpha;
                if (p->_4C == 1) {
                    p->origin.y -= 0.0f;
                } else {
                    p->origin.y -= 0.05f;
                }
                p->_4A--;
                if (p->_4A == 0) {
                    *link = p->next;
                    if (removedTail != NULL) {
                        removedTail->next = p;
                    }
                    removedTail = p;
                    p->next = NULL;
                    effect->count--;
                } else {
                    link = &p->next;
                    alive++;
                }
            } else {
                p->_48--;
                link = &p->next;
                alive++;
            }
        }
        p = *link;
    } while (p != NULL);
    return alive == 0;
}

// .text:0x147358 size:0x24
void fn_3_147358(void) {
    pitchingMachinePitching(0x26);
}
