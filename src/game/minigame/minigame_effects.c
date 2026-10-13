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
#include "Unknown/sprt.h"
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

#define MG_PLAYER_COUNT 4
#define BB_BARREL_COUNT 15
/* Spark group index of the star itself; 0..3 are the players. */
#define SD_STAR_SPARK_INDEX 4

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




MGFxHead minigameFxData = {
    { 0.45f, -0.4f },
    {
        { 0, 21, { 2, 240000, 0, 0, 4, 2, 120000, 90000, 0, 155, 500000, 1000000, -500000, 500000, -256, 0, -28000, 1 } },
        { 0, 7, { 4, 78000, 60000, 50000, 12, 6, 109000, 101000, 0, 60, 4500000, 9500000, -1000000, 4500000, -256, 0, 0, 0 } },
        { 0, 18, { 0, 90000, 120000, 10000, 20, 10, 103000, 105999, 0, 60, 10000000, 18000000, 1000000, -1000000, 1010580480, 0, 0, 0 } },
    },
    { 0, { 20, 8, 0, 250000, 50000, 550000, 0, 0, 12, 13, 14, 15, 16, 17, 18, 19 } },
    { { 11, 10 }, { 15, 14 }, { 17, 16 }, { 13, 12 } },
};

MGFxSlot minigameFxSlotB0 = { 0, 10, { 3, 100000, 30000, 10000, 12, 8, 110000, 50000, 0, 60, 4500000, 20000000, 0, 2000000, -256, 0, 75000, 0 } };

MGFxSlot minigameFxSlotB1 = { 0, 10, { 5, 18000, 20000, 60000, 12, 6, 109000, 101000, 0, 60, 4500000, 9400000, -1000000, 4500000, -256, 0, 75000, 0 } };

MGFxTail minigameFxTail = {
    { 0, 18, { 1, 60000, 10000, 50000, 30, 8, 104000, 106000, 0, 90, 12800000, 10000000, 1000000, 6000000, 1010580480, 0, 75000, 0 } },
    { &minigameFxSlotB0, &minigameFxSlotB1, &minigameFxTail.slot },
    { 0 },
    { { 0 } },
    { 0xFF0000FF, 65535, 0xFFFF00FF, 0x00FF00FF },
    { -0.4f, 6.0f },
};

u16 minigameQuadTexCoords[4][2] = { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 } };

f32 starDash_fireBarTrailNear = -0.2f;

f32 starDash_fireBarTrailFar = 3.0f;

Vec bobOmbFuseSpark_offset = { 0.087f, -0.757f, 0.001f };

s32 bobOmbFuseSpark_params[7] = { 3, 32, 0, 35000, 0, 255, 32 };

s32 chainChomp_itemSparkleParams[4] = { 16, 0, 255, 28 };

s32 chainChomp_itemSparkleLayer1Params[4] = { 0, 150000, 0, 16 };

s32 chainChomp_itemSparkleLayer2Params[4] = { 0, 15000, 0, 32 };

s32 chainChomp_itemSparkleFlyParams[4] = { 100000, 100000, 10000, 64 };

f32 chainChomp_itemSparkleScoreCorners[8] = { -0.75f, 0.7f, 0.75f, 0.7f, -0.75f, -0.7f, 0.75f, -0.7f };

s32 wallBall_noteBlockBurstParams[22] = { 2, 32, 0, 50000, 0, 255, 32, 15, 9, 150, 40000, 70000, 30000, 80000, 4400, 50000, 12000, 15000, 0, 104719, 60, 29 };

s32 starDash_sparkParams[9] = { 2, 90, 200000, 100000, 0, 0, 255, 36, 30 };

u8 starDash_sparkBoneNodes[0x18] = { 4, 5, 6, 7, 8, 16, 17, 18, 19, 20, 22, 23, 24, 25, 26, 28, 29, 30, 31, 32, 33, 34, 35, 0 };

s32 starDash_dustParams[12] = { 2, 6, 40, 100000, 50000, 0, 255, 127, 0, 40000, 440, 31 };

s32 barrelBatter_explosionParams[20] = { 6, 5, 645, 5, 0, 600000, 800000, 0, 255, 0, 2, 0, 200000, 300000, 0, 255, 0, 20, 20, 32 };

Vec chainChomp_launchFlashOffset = { 3.7f, -9.3f, 0.0f };

s32 chainChomp_launchFlashParams[11] = { 7, 1, 8, 5, 0, 1000000, 1200000, 0, 255, 0, 33 };

s32 wallBall_wallHitPuffParams[15] = { 8, 5, 30, 5, 0, 250000, 400000, 255, 255, 255, 0, 80, 0, 100000, 34 };

s32 wallBall_wallHitDarkPuffParams[15] = { 8, 16, 30, 15, 250000, 375000, 500000, 0, 0, 0, 255, 127, 0, 100000, 34 };

f32 barrelBatter_machineSparkPath[9] = { 2.035f, -5.718f, 1.014f, 1.793f, -4.523f, 0.914f, 1.29f, -4.119f, 0.815f };

s32 barrelBatter_machineSparkParams[7] = { 3, 16, 100, 0, 30000, 0, 255 };

s32 barrelBatter_releaseRingParams[15] = { 8, 6, 60, 30000, 5, 0, 100000, 40000, 50000, 0, 220, 0, 30000, 15000, 36 };

s32 minigameWinnerStars_params[8] = { 100, 5000, 1200000, 15000, 15000, 0, 60, 37 };

s32 piranhaPanic_bombExplosionParams[25] = { 6, 30, 4, 5, 0, 250000, 350000, 0, 255, 0, 5, 20, 7, 2, 0, 250000, 350000, 0, 120, 0, 0, 4259909, 5046345, 4128768, 0 };

static MGTrailEffect* minigameTrail_effect;
static MGTexRecord* minigameTrail_lastTex;
static u8 lbl_3_bss_B858;
static s8 minigameWinnerStars_slots[MG_PLAYER_COUNT];
static f32 minigameWinnerStars_quadVerts[13];
static u8 lbl_3_bss_B894[0x124];

static inline s32 mgFxTableRow(MGParticle* p) {
    s32 row = 10;

    if (p->kind == 1) {
        row = 0;
    }
    return row;
}

static inline void mgInitFollowParticle(MGFollowParticle* p) {
    Vec rot;

    rot.x = 57.29578f * p->rot->x;
    rot.y = 57.29578f * p->rot->y;
    rot.z = 57.29578f * p->rot->z;
    bobOmbFuseSpark_placeParticle((MGParticle*)p, p->pos, &rot);
}

static inline void mgInitHitParticle(MGParticle* p) {
    Vec rot;

    rot.x = 57.29578f * shortAngleToRad(g_Ball.matchFramesAndBallAngle.ballSpinAngle.yaw);
    rot.y = 57.29578f * shortAngleToRad(g_Ball.matchFramesAndBallAngle.ballSpinAngle.pitch);
    rot.z = 57.29578f * shortAngleToRad(g_Ball.matchFramesAndBallAngle.ballSpinAngle.roll);
    bobOmbFuseSpark_placeParticle(p, (Vec*)&g_Ball.AtBat_Contact_BallPos, &rot);
}

/* Entry `slot` of the texture-id table at the pointer stored in animRelated[table]: each id selects a
 * 0x20-byte texture record following the table header. */
#define MG_TEX_RECORD(table, slot) \
    ((u8*)*(u8**)&animRelated[table] + 4 + *(u16*)((u8*)*(u8**)&animRelated[table] + 0x20 + (slot)*0x20) * 0x20)

extern void fn_80033B58(void* tex, int sub, int a, int b);



// .text:0x157DB8 size:0x70
// Spawns the trail effect that follows the chomp; it lives for `duration` frames.
void chainChomp_spawnTrailEffect(s32 duration) {
    MGEffect* effect = allocParticleEffect(chainChomp_updateTrailEffect, 0x80, 0, 1, TRUE, 0x16);

    if (effect != NULL) {
        effect->frame = 0;
        effect->duration = duration;
        effect->particles->texIndex = 0;
        *(u32*)&effect->particles->colorR = 0xFFFFFFFF; // RGBA white
    }
}

// .text:0x157AC4 size:0x2F4
int chainChomp_updateTrailEffect(MGEffect* effect) {
    MGParticle* p = effect->particles;
    Vec offset = { 2.775f, -6.975f, 0.0f };
    Mtx rot;
    f32 scale;

    PSMTXRotRad(rot, 'Y', shortAngleToRad(g_Minigame.ccs.chompYaw));
    PSMTXMultVec(rot, &offset, &offset);
    scale = chainChomp_trailScale(effect->frame);
    p->sizeY = scale;
    p->sizeX = scale;
    p->origin.x = g_Minigame.ccs.chompPos.x + offset.x + p->sizeX * minigameFxData.trailScale[0];
    p->origin.y = g_Minigame.ccs.chompPos.y + offset.y + p->sizeY * minigameFxData.trailScale[1];
    p->origin.z = g_Minigame.ccs.chompPos.z + offset.z;
    fn_8003403C(p->sizeX, p->sizeY);
    fn_80033CC8(effect->particles, *(s32*)&animRelated[0x64]);
    if (lbl_80366158[0x28] == 0) {
        effect->frame++;
    }
    if (g_Minigame.minigameInactiveInd != 0) {
        return TRUE;
    }
    return effect->frame == effect->duration && g_GameLogic.gameStatus != GAME_STATUS_MVP_END_GAME;
}

// .text:0x15791C size:0x1A8
f32 chainChomp_trailScale(s32 frame) {
    s32 cycles = (frame + 0x30) / 0x78;
    s32 phase = (frame + 0x30) % 0x78;
    f32 c;
    f32 scale;

    if (phase >= 0x30) {
        c = cos(3.1415927f * (1.0f + ((f32)phase - 48.0f) / 72.0f));
    } else {
        c = cos(3.1415927f * ((f32)phase / 48.0f));
    }
    scale = c / 2.0f;
    scale += 0.5f;
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
void chainChomp_stopTrailEffect(void) {
    pitchingMachinePitching(0x16);
}

// .text:0x15767C size:0x27C
void piranhaPanic_updateSpitTrailEffect(void) {
    MGFxData* data = (MGFxData*)&minigameFxData;
    MGFxSlot* slot0 = &data->slotsA[0];
    MGFxSlot* slot1 = &data->slotsA[1];
    MGFxSlot* slot2 = &data->slotsA[2];
    Vec target;
    Vec dir;
    Vec toTarget;
    Vec* point;
    u32 i;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && g_Minigame.GameMode_MiniGame == MINI_GAME_ID_PIRANHA_PANIC &&
        minigameTrail_effect->done == FALSE) {
        for (i = 0; i < PP_OBJECT_COUNT; i++) {
            PPObject* obj = &PP.object[i];

            if (obj->state != 0) {
                target.x = obj->pos.x;
                target.y = -obj->pos.y;
                target.z = obj->pos.z;
                point = minigameTrail_getPoint(i);
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
        minigameTrail_lastTex = NULL;
    }
    if (minigameTrail_effect->done != FALSE) {
        minigameTrail_effect = NULL;
    }
}

// .text:0x1575F0 size:0x8C
Vec* minigameTrail_getPoint(u32 index) {
    MGTrailNode* node;

    if (minigameTrail_effect != NULL) {
        node = minigameTrail_effect->nodes;
        while (index >= 7) {
            node = node->next;
            index -= 7;
        }
        return &node->pts[index];
    }
    return NULL;
}

// .text:0x157588 size:0x68
void minigameTrail_alloc(int count) {
    minigameTrail_effect = allocParticleEffect(piranhaPanic_updateSpitTrailEffect, 0x80, 0, (count + 6) / 7, TRUE, 0x28);
    minigameTrail_effect->done = FALSE;
}

// .text:0x157570 size:0x18
void minigameTrail_finish(void) {
    minigameTrail_effect->done = TRUE;
}

// .text:0x1573AC size:0x1C4
void piranhaPanic_emitFielderHitFire(MGFxActor* actor) {
    MGFxData* data = (MGFxData*)&minigameFxData;
    Vec offset;
    Vec dir;
    Mtx mtx;
    Control ctrl;
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
    data->slotPtrs[2]->texture = *(u32*)&animRelated[0x6C];
    data->slotPtrs[1]->texture = *(u32*)&animRelated[0x6C];
    data->slotPtrs[0]->texture = *(u32*)&animRelated[0x6C];
    effectId = data->effectIds[actor->slotIndex][1];
    data->slotPtrs[1]->effectId = effectId;
    data->slotPtrs[0]->effectId = effectId;
    fn_80030D88(&offset, &dir, data->slotPtrs[0], 0x29);
    fn_80030D88(&offset, &dir, data->slotPtrs[1], 0x29);
    fn_80030D88(&offset, &dir, data->slotPtrs[2], 0x29);
}

// .text:0x15730C size:0xA0
void minigameTrail_setPoint(u32 index, f32 x, f32 y, f32 z) {
    Vec* point = minigameTrail_getPoint(index);

    if (point == NULL) {
        return;
    }
    point->x = x;
    point->y = y;
    point->z = z;
}

// .text:0x156D04 size:0x608
void piranhaPanic_drawSpitTrail(u32 index, f32 x, f32 y, f32 z) {
    MGFxData* data = (MGFxData*)&minigameFxData;
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
    point = minigameTrail_getPoint(index);
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
        angle *= (f32)(-(rand() % 2 * 2) + 1);
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
                    g = (f32)(7 - i) / 4.0f + 1.0f;
                } else {
                    g = 2.0f;
                }
                h = sizeScale * (g / 2.0f);
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
                    minigameTrail_drawQuad(quad, -1, (MGTexRecord*)MG_TEX_RECORD(0x68, 0));
                }
                if (i >= 4) {
                    g = (f32)(7 - i) / 4.0f + 1.0f;
                } else {
                    g = 2.0f;
                }
                h = sizeScale * (g / 2.0f);
                quad[0].x = step.x - h;
                quad[0].y = step.y - h;
                quad[1].x = step.x - h;
                quad[1].y = step.y + h;
                quad[2].x = step.x + h;
                quad[2].y = step.y + h;
                quad[3].x = step.x + h;
                quad[3].y = step.y - h;
                GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
                minigameTrail_drawQuad(quad, colors[colorIndex], (MGTexRecord*)MG_TEX_RECORD(0x6C, i + 10));
                break;
            }
        } while (i-- != 0);
    }
}

// .text:0x156970 size:0x394
void minigameTrail_drawQuad(Vec* positions, u32 color, MGTexRecord* tex) {
    MGQuadVertex verts[4];
    Mtx identity;
    GXTexObj texObj;
    GXTlutObj tlutObj;
    int i;

    PSMTXIdentity(identity);
    for (i = 0; i < 4; i++) {
        memcpy(&verts[i].pos, &positions[i], sizeof(Vec));
        verts[i].color = color;
        memcpy(&verts[i].s, minigameQuadTexCoords[i], 4);
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
    if (minigameTrail_lastTex != tex) {
        if (tex->tlut != NULL) {
            GXInitTexObjCI(&texObj, tex->image, tex->width, tex->height, tex->format, GX_CLAMP, GX_CLAMP, GX_FALSE, 0);
            GXInitTlutObj(&tlutObj, tex->tlut, tex->tlutFormat, tex->tlutEntries);
            GXLoadTlut(&tlutObj, 0);
        } else {
            GXInitTexObj(&texObj, tex->image, tex->width, tex->height, tex->format, GX_CLAMP, GX_CLAMP, GX_FALSE);
        }
        GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, tex->minLod, tex->maxLod, tex->lodBias, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXLoadTexObj(&texObj, GX_TEXMAP0);
        minigameTrail_lastTex = tex;
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
void starDash_drawFireBarTrail(u32 index, f32 x, f32 y, f32 z) {
    Vec quad[4];
    Mtx44 proj;
    Vec screen;
    Vec step;
    Vec trail;
    Vec* point;
    f32 inv;
    f32 g;
    f32 h;
    s32 i;

    inv = 1.0f / fn_80052768_getCamera(0)->zoom;
    fn_800B24D4(0xD);
    point = minigameTrail_getPoint(index);
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
                PSVECScale(&screen, starDash_fireBarTrailNear + (f32)i * (starDash_fireBarTrailFar - starDash_fireBarTrailNear) / 7.0f, &step);
                PSVECAdd(&trail, &step, &step);
                if (i >= 4) {
                    g = 0.5f * (f32)(7 - i) * 0.25f + 0.5f;
                } else {
                    g = 1.0f;
                }
                h = g / 2.0f;
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
                h = g / 2.0f;
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
        bobOmbFuseSpark_spawnAtPitch();
    }
}

// .text:0x155F08 size:0x310
void bobOmbFuseSpark_spawnAtPitch(void) {
    MGEffect* effect = allocParticleEffect(bobOmbFuseSpark_updateAtPitch, 0x80, 0, bobOmbFuseSpark_params[1], TRUE, 0x1B);

    if (effect != NULL) {
        bobOmbFuseSpark_initAtPitch(effect);
    }
}

// .text:0x155C28 size:0x2E0
void bobOmbFuseSpark_initAtPitch(MGEffect* effect) {
    MGParticle* p = effect->particles;
    u32 i = 0;

    effect->texture = *(u32*)&animRelated[0x6C];
    do {
        p->delay = (u8)i;
        i++;
        p->texIndex = bobOmbFuseSpark_params[0];
        p->_4E = 0;
        if (p->delay == 0) {
            mgInitHitParticle(p);
        }
        p = p->next;
    } while (p != NULL);
}

// .text:0x1559E4 size:0x244
void bobOmbFuseSpark_placeParticle(MGParticle* p, Vec* base, Vec* rot) {
    Control ctrl;
    Mtx mtx;
    Vec offset;
    Vec scale;

    p->life = bobOmbFuseSpark_params[6];
    ctrl.type = 0;
    CTRLSetRotation(&ctrl, rot->x, rot->y, rot->z);
    CTRLBuildMatrix(&ctrl, mtx);
    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY) {
        scale = bobOmbFuseSpark_offset;
    } else {
        PSVECScale(&bobOmbFuseSpark_offset, 1.5f, &scale);
    }
    offset.x = scale.x + 1.5 * ((rand() % 40 - 20) / 100.0);
    offset.y = scale.y;
    offset.z = scale.z + 1.5 * ((rand() % 40 - 20) / 100.0);
    PSMTXMultVec(mtx, &offset, &offset);
    offset.x += base->x;
    offset.y -= fabs(base->y);
    offset.z += base->z;
    p->origin.x = offset.x;
    p->origin.y = offset.y;
    p->origin.z = offset.z;
    p->sizeY = p->sizeX = (f32)bobOmbFuseSpark_params[2];
    p->alphaByte = bobOmbFuseSpark_params[4];
}

// .text:0x1552AC size:0x738
int bobOmbFuseSpark_updateAtPitch(MGEffect* effect) {
    MGParticle* p;

    if (lbl_80366158[0x28] != 0) {
        return 0;
    }
    fn_80033620(effect);
    p = effect->particles;
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_LO_CLEAR);
    do {
        if (p->delay != 0) {
            p->delay--;
            if (p->delay == 0) {
                mgInitHitParticle(p);
            }
        } else if (p->life != 0) {
            s32 alpha;

            fn_8003403C(p->sizeX, p->sizeY);
            fn_80033CC8(p, effect->texture);
            if (bobOmbFuseSpark_params[6] / p->life < 2) {
                alpha = p->alphaByte + bobOmbFuseSpark_params[5] / (bobOmbFuseSpark_params[6] / 2);
                if (alpha > bobOmbFuseSpark_params[5]) {
                    alpha = bobOmbFuseSpark_params[5];
                }
                p->alphaByte = alpha;
                p->sizeX += ((f32)bobOmbFuseSpark_params[3] / 100000.0f) / (f32)(bobOmbFuseSpark_params[6] / 2);
                p->sizeY = p->sizeX;
            } else {
                alpha = p->alphaByte - bobOmbFuseSpark_params[5] / (bobOmbFuseSpark_params[6] / 2);
                if (alpha < bobOmbFuseSpark_params[4]) {
                    alpha = bobOmbFuseSpark_params[4];
                }
                p->alphaByte = alpha;
                p->sizeX -= ((f32)bobOmbFuseSpark_params[3] / 100000.0f) / (f32)(bobOmbFuseSpark_params[6] / 2);
                p->sizeY = p->sizeX;
            }
            p->colorR = p->colorG = p->colorB = (u8)(255.0f * ((f32)p->alphaByte / 255.0f));
            p->life--;
        }
        if (p->life == 0 && p->delay <= 0) {
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
void bobOmbDerbyPitching2(void) {
    pitchingMachinePitching(0x1B);
}

// .text:0x15521C size:0x48
void bobOmbFuseSpark_spawnFollow(s16 id, Vec* pos, Vec* rot) {
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES || pos == NULL || rot == NULL) {
        return;
    }
    bobOmbFuseSpark_spawnFollowEffect(id, pos, rot);
}

// .text:0x154C7C size:0x5A0
void bobOmbFuseSpark_spawnFollowEffect(s16 id, Vec* pos, Vec* rot) {
    MGEffect* existing = fn_800339F0(0, 0x27);
    MGEffect* fresh;
    u8 scratch[0x60];

    if (existing != NULL) {
        fresh = fn_800337CC(scratch, bobOmbFuseSpark_params[1], 1);
        if (fresh != NULL) {
            MGParticle* tail;

            bobOmbFuseSpark_initFollow(fresh, id, pos, rot);
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
        fresh = allocParticleEffect(bobOmbFuseSpark_updateFollow, 0x80, 0, bobOmbFuseSpark_params[1], TRUE, 0x27);
        if (fresh != NULL) {
            bobOmbFuseSpark_initFollow(fresh, id, pos, rot);
        }
    }
}

// .text:0x1549F0 size:0x28C
void bobOmbFuseSpark_initFollow(MGEffect* effect, s16 id, Vec* pos, Vec* rot) {
    MGFollowParticle* p = (MGFollowParticle*)effect->particles;
    u32 i = 0;

    effect->texture = *(u32*)&animRelated[0x6C];
    do {
        p->id = id;
        p->pos = pos;
        p->rot = rot;
        p->delay = (u8)i;
        i++;
        p->texIndex = bobOmbFuseSpark_params[0];
        p->_4E = 0;
        if (p->delay == 0) {
            bobOmbFuseSpark_placeParticle((MGParticle*)p, pos, rot);
        }
        p = (MGFollowParticle*)p->next;
    } while (p != NULL);
}

// .text:0x1542F4 size:0x6FC
int bobOmbFuseSpark_updateFollow(MGEffect* effect) {
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
        if (p->delay != 0) {
            p->delay--;
            if (p->delay == 0) {
                mgInitFollowParticle(p);
            }
        } else if (p->life != 0) {
            s32 alpha;

            fn_8003403C(p->sizeX, p->sizeY);
            fn_80033CC8(p, effect->texture);
            if (bobOmbFuseSpark_params[6] / p->life < 2) {
                alpha = p->alphaByte + bobOmbFuseSpark_params[5] / (bobOmbFuseSpark_params[6] / 2);
                if (alpha > bobOmbFuseSpark_params[5]) {
                    alpha = bobOmbFuseSpark_params[5];
                }
                p->alphaByte = alpha;
                p->sizeX += 3.0f * (((f32)bobOmbFuseSpark_params[3] / 100000.0f) / (f32)(bobOmbFuseSpark_params[6] / 2));
                p->sizeY = p->sizeX;
            } else {
                alpha = p->alphaByte - bobOmbFuseSpark_params[5] / (bobOmbFuseSpark_params[6] / 2);
                if (alpha < bobOmbFuseSpark_params[4]) {
                    alpha = bobOmbFuseSpark_params[4];
                }
                p->alphaByte = alpha;
                p->sizeX -= 3.0f * (((f32)bobOmbFuseSpark_params[3] / 100000.0f) / (f32)(bobOmbFuseSpark_params[6] / 2));
                p->sizeY = p->sizeX;
            }
            p->colorR = p->colorG = p->colorB = (u8)(255.0f * ((f32)p->alphaByte / 255.0f));
            p->life--;
        }
        if (p->life == 0 && p->delay <= 0) {
            mgInitFollowParticle(p);
        }
        p = (MGFollowParticle*)p->next;
    } while (p != NULL);
    return 0;
}

// .text:0x154238 size:0xBC
void bobOmbFuseSpark_removeFollow(s16 id) {
    MGEffect* effect = fn_800339F0(0, 0x27);
    MGParticle* p;
    MGParticle** link;
    MGParticle* removedHead;
    MGParticle* removedTail;

    if (effect != NULL) {
        p = effect->particles;
        link = &effect->particles;
        removedTail = NULL;
        removedHead = NULL;
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
void bobOmbFuseSpark_stopFollow(void) {
    pitchingMachinePitching(0x27);
}

// .text:0x1541C4 size:0x50
void chainChomp_spawnItemSparkle(u8 kind, u8 mode, Vec* pos) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && g_Minigame.GameMode_MiniGame == MINI_GAME_ID_CHAINCHOMP_SPRINT &&
        pos != NULL) {
        chainChomp_spawnItemSparkleEffect(kind, mode, pos);
    }
}

// .text:0x1540E4 size:0xE0
#pragma dont_inline on
void chainChomp_spawnItemSparkleEffect(u8 kind, u8 mode, Vec* pos) {
    MGEffect* effect = fn_800339F0(0, 0x1C);
    MGParticle* p;
    if (effect != NULL) {
        chainChomp_initItemSparkleParticles(effect, kind, mode, pos);
    } else {
        effect = allocParticleEffect(chainChomp_updateItemSparkles, 0x80, 0, chainChomp_itemSparkleParams[0] * 15, TRUE, 0x1C);
        if (effect != NULL) {
            p = effect->particles;
            do {
                p->life = 0;
                p->kind = 0;
                p->_4F = 0xFF;
                p = p->next;
            } while (p != NULL);
            chainChomp_initItemSparkleParticles(effect, kind, mode, pos);
            memset(lbl_3_bss_B894, 0, 0xF);
        }
    }
}
#pragma dont_inline reset

// .text:0x153F8C size:0x158
#pragma dont_inline on
void chainChomp_initItemSparkleParticles(MGEffect* effect, u8 kind, u8 mode, Vec* pos) {
    MGParticle* p = effect->particles;
    u32 i = 0;
    u8 index;

    effect->texture = *(u32*)&animRelated[0x6C];
    do {
        if (p->life == 0) {
            index = i;
            chainChomp_initItemSparkleParticle(p, pos, kind, mode, index);
            chainChomp_placeItemSparkleLayer(p, (index != 0) + 1);
            i++;
        }
        p = p->next;
    } while (p != NULL && (u8)i < chainChomp_itemSparkleParams[0]);
}
#pragma dont_inline reset

// .text:0x153E8C size:0x100
void chainChomp_initItemSparkleParticle(MGParticle* p, Vec* pos, u8 kind, u8 mode, u8 index) {
    f32 scale;

    p->delay = (index != 0) * chainChomp_itemSparkleLayer1Params[3] + index * chainChomp_itemSparkleParams[3] / chainChomp_itemSparkleParams[0];
    p->texIndex = (mode == 4);
    p->_4E = 0;
    p->_4F = kind;
    p->colorR = p->colorG = p->colorB = 0xFF;
    p->alphaByte = chainChomp_itemSparkleParams[1];
    p->_1C = pos->x;
    if (p->texIndex != 0) {
        scale = mm_GetItemScale(2);
    } else {
        scale = mm_GetItemScale(0);
    }
    p->_20 = -pos->y - 0.1435f * scale;
    p->alpha = pos->z;
    p->_45 = 0;
    p->_44 = 0;
}

static const Vec sFwdAxis = { 0.0f, 0.0f, -1.0f };

// .text:0x1536A8 size:0x7E4
void chainChomp_placeItemSparkleLayer(MGParticle* p, u8 kind) {
    MGFxData* data = (MGFxData*)&minigameFxData;

    switch (kind) {
    case 1: {
            camera_803c639c_s* cam = returnFloatFromModeIndex(returnsCurrentMode());
            f32 scale;
            Mtx rotMtx;
            f32 angle;
            s32* tbl;

            if (p->texIndex != 0) {
                scale = mm_GetItemScale(2);
            } else {
                scale = mm_GetItemScale(0);
            }
            {
            Vec axis = sFwdAxis;
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
            p->sizeX = p->sizeY = (f32)data->itemFxB[0];
            p->kind = 1;
            p->life = tbl[3];
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

            if (p->texIndex != 0) {
                scale = mm_GetItemScale(2);
            } else {
                scale = mm_GetItemScale(0);
            }
            {
            Vec axis = sFwdAxis;
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
            p->sizeX = p->sizeY = (f32)data->itemFxC[0];
            p->kind = 2;
            p->life = tbl[3];
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

            if (p->texIndex != 0) {
                scale = mm_GetItemScale(2);
            } else {
                scale = mm_GetItemScale(0);
            }
            {
            Vec axis = sFwdAxis;
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
            p->sizeX = p->sizeY = (f32)data->itemFxD[0];
            p->kind = 3;
            p->life = tbl[3];
            p->velX = p->velZ = 0.0f;
            p->velY = -((f32)tbl[2] / 100000.0f);
            }
            break;
        }
    }
}

// .text:0x1534C0 size:0x1E8
void chainChomp_initItemSparkleLayer1(MGParticle* p) {
    chainChomp_placeItemSparkle(p, FALSE);
    p->sizeX = p->sizeY = (f32)chainChomp_itemSparkleLayer1Params[0];
    p->kind = 1;
    p->life = chainChomp_itemSparkleLayer1Params[3];
    p->velX = p->velZ = 0.0f;
    p->velY = ((f32)chainChomp_itemSparkleLayer1Params[2] / 100000.0f);
}

// .text:0x1531A4 size:0x31C
void chainChomp_initItemSparkleLayer2(MGParticle* p) {
    chainChomp_placeItemSparkle(p, TRUE);
    p->sizeX = p->sizeY = (f32)chainChomp_itemSparkleLayer2Params[0];
    p->kind = 2;
    p->life = chainChomp_itemSparkleLayer2Params[3];
    p->velX = p->velZ = 0.0f;
    p->velY = ((f32)chainChomp_itemSparkleLayer2Params[2] / 100000.0f);
}

// .text:0x152AB4 size:0x6F0
void chainChomp_flyItemSparklesToScore(u8 id, u8 flag) {
    MGEffect* effect;
    f32* cornerY;
    f32* cornerX;
    MGParticle* p;
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
            cornerX = &chainChomp_itemSparkleScoreCorners[flag * 2];
            cornerY = cornerX + 1;
            p = effect->particles;
            do {
                if (p->_4F == id && p->life != 0) {
                    p->delay = 0;
                    p->_4F = 0xFF;
                    chainChomp_placeItemSparkle(p, TRUE);
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
                    PSMTX44MultVec(cam->proj, &view, &view);
                    view.z = -1.0f;
                    p->origin.x = view.x;
                    p->origin.y = view.y;
                    p->origin.z = view.z;
                    p->sizeX = p->sizeY = (f32)chainChomp_itemSparkleFlyParams[0] / 100000.0f;
                    world.x = world.y = p->sizeX;
                    world.z = p->_34;
                    PSMTX44MultVec(cam->proj, &world, &view);
                    p->sizeX = view.x * (p->texIndex != 0 ? 1.5 : 1.0);
                    p->sizeY = view.y * (p->texIndex != 0 ? 1.5 : 1.0);
                    p->kind = 3;
                    p->life = chainChomp_itemSparkleFlyParams[3];
                    angle = 0.017453292f * (f32)(90.0 * (2.0 * ((f32)rand() / 32767.0f - 0.5)));
                    dir.x = *cornerX - p->origin.x;
                    dir.y = *cornerY - p->origin.y;
                    dir.z = 0.0f;
                    if (PSVECMag(&dir) >= 1.0) {
                        k = 1.0f;
                    } else {
                        k = 1.0f / (PSVECMag(&dir) / 2.0f);
                    }
                    PSVECNormalize(&dir, &dir);
                    dir.x *= -1.0f;
                    dir.y *= -1.0f;
                    rotated.x = -dir.y * (f32)sin(angle) + dir.x * (f32)cos(angle);
                    rotated.y = dir.y * (f32)cos(angle) + dir.x * (f32)sin(angle);
                    rotated.z = 0.0f;
                    PSVECScale(&rotated, ((f32)chainChomp_itemSparkleFlyParams[2] / 100000.0f) * k, &rotated);
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
void chainChomp_initItemSparkleFly(MGParticle* p) {
    chainChomp_placeItemSparkle(p, TRUE);
    p->sizeX = p->sizeY = (f32)chainChomp_itemSparkleFlyParams[0];
    p->kind = 3;
    p->life = chainChomp_itemSparkleFlyParams[3];
    p->velX = p->velZ = 0.0f;
    p->velY = -((f32)chainChomp_itemSparkleFlyParams[2] / 100000.0f);
}

// .text:0x1524E8 size:0x2AC
void chainChomp_placeItemSparkle(MGParticle* p, u8 randomize) {
    camera_803c639c_s* cam = returnFloatFromModeIndex(returnsCurrentMode());
    f32 scale;
    Mtx rotMtx;
    Vec v;
    Vec dir;
    Vec rotAxis;
    f32 angle;

    if (p->texIndex != 0) {
        scale = mm_GetItemScale(2);
    } else {
        scale = mm_GetItemScale(0);
    }
    {
        Vec axis = sFwdAxis;

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
int chainChomp_updateItemSparkles(MGEffect* effect) {
    MGFxData* data = (MGFxData*)&minigameFxData;
    MGParticle* p;
    f32 scale;

    if (lbl_80366158[0x28] != 0) {
        return 0;
    }
    fn_80033620(effect);
    p = effect->particles;
    if (p->kind != 3) {
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    } else {
        GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    }
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
    do {
        if (p->delay <= 0 && p->life != 0) {
            if (p->texIndex != 0) {
                scale = mm_GetItemScale(2);
            } else {
                scale = mm_GetItemScale(0);
            }
            switch (p->kind) {
            case 1:
                chainChomp_updateItemSparkleLayer1(effect, p);
                break;
            case 2:
                chainChomp_updateItemSparkleLayer2(effect, p);
                break;
            case 3:
                chainChomp_updateItemSparkleFly(effect, p);
                break;
            }
        } else if (p->delay != 0) {
            p->delay--;
        }
        if (p->life == 0 && (p->kind == 1 || p->kind == 2)) {
            chainChomp_placeItemSparkleLayer(p, 2);
        }
        p = p->next;
    } while (p != NULL);
    return 0;
}

// .text:0x151D6C size:0x1C0
void chainChomp_updateItemSparkleLayer1(MGEffect* effect, MGParticle* p) {
    s32 duration;
    s32 alpha;
    s32 alphaStep;
    f32 sizeStep;
    f32 scale;

    fn_8003403C(p->sizeX, p->sizeY);
    fn_80033CC8(p, effect->texture);
    if (p->texIndex != 0) {
        scale = mm_GetItemScale(2);
    } else {
        scale = mm_GetItemScale(0);
    }
    duration = chainChomp_itemSparkleLayer1Params[3];
    alpha = p->alphaByte;
    if (duration / p->life < 2) {
        alphaStep = chainChomp_itemSparkleParams[2] / (duration / 2);
        sizeStep = (f32)chainChomp_itemSparkleLayer1Params[1] * scale / 100000.0f / (f32)(duration / 2);
    } else {
        alphaStep = -chainChomp_itemSparkleParams[2] / (duration / 2);
        sizeStep = -((f32)chainChomp_itemSparkleLayer1Params[1] * scale / 100000.0f) / (f32)(duration / 2);
    }
    alpha = alpha + alphaStep;
    if (alpha < 0) {
        alpha = 0;
    } else if (alpha > 0xFF) {
        alpha = 0xFF;
    }
    p->alphaByte = alpha;
    p->sizeX += sizeStep;
    p->sizeY = p->sizeX;
    PSVECAdd(&p->origin, (Vec*)&p->velX, &p->origin);
    p->life--;
}

// .text:0x151BAC size:0x1C0
void chainChomp_updateItemSparkleLayer2(MGEffect* effect, MGParticle* p) {
    s32 duration;
    s32 alpha;
    s32 alphaStep;
    f32 sizeStep;
    f32 scale;

    fn_8003403C(p->sizeX, p->sizeY);
    fn_80033CC8(p, effect->texture);
    if (p->texIndex != 0) {
        scale = mm_GetItemScale(2);
    } else {
        scale = mm_GetItemScale(0);
    }
    duration = chainChomp_itemSparkleLayer2Params[3];
    alpha = p->alphaByte;
    if (duration / p->life < 2) {
        alphaStep = chainChomp_itemSparkleParams[2] / (duration / 2);
        sizeStep = (f32)chainChomp_itemSparkleLayer2Params[1] * scale / 100000.0f / (f32)(duration / 2);
    } else {
        alphaStep = -chainChomp_itemSparkleParams[2] / (duration / 2);
        sizeStep = -((f32)chainChomp_itemSparkleLayer2Params[1] * scale / 100000.0f) / (f32)(duration / 2);
    }
    alpha = alpha + alphaStep;
    if (alpha < 0) {
        alpha = 0;
    } else if (alpha > 0xFF) {
        alpha = 0xFF;
    }
    p->alphaByte = alpha;
    p->sizeX += sizeStep;
    p->sizeY = p->sizeX;
    PSVECAdd(&p->origin, (Vec*)&p->velX, &p->origin);
    p->life--;
}

// .text:0x1519F8 size:0x1B4
void chainChomp_updateItemSparkleFly(MGEffect* effect, MGParticle* p) {
    Vec dir;
    Vec unit;
    Vec target;
    f32 dist;

    chainChomp_drawItemSparkleOnHud(p, effect);
    if (lbl_80366158[0x28] == 0) {
        PSVECAdd(&p->origin, (Vec*)&p->velX, &p->origin);
        memcpy(&dir, &p->origin, sizeof(Vec));
        dir.x = chainChomp_itemSparkleScoreCorners[p->_44 * 2] - dir.x;
        dir.y = chainChomp_itemSparkleScoreCorners[p->_44 * 2 + 1] - dir.y;
        dir.z = 0.0f;
        PSVECNormalize(&dir, &unit);
        dist = PSVECMag(&dir);
        PSVECScale(&unit, 0.0015f * (1.0f / (dist * dist)), &dir);
        PSVECAdd((Vec*)&p->velX, &dir, (Vec*)&p->velX);
        target.x = chainChomp_itemSparkleScoreCorners[p->_44 * 2];
        target.y = chainChomp_itemSparkleScoreCorners[p->_44 * 2 + 1];
        target.z = 0.0f;
        PSVECNormalize(&target, &target);
        if (PSVECDotProduct(&unit, &target) < 0.0f || !dist) {
            p->life = 0;
        }
        if (p->life == 0 && p->_45 != 0) {
            minigameHudCcsAddGemPoints(p->_44, p->texIndex == 1);
            p->_45 = 0;
        }
    }
}

// .text:0x1517D0 size:0x228
void chainChomp_drawItemSparkleOnHud(MGParticle* p, MGEffect* effect) {
    Mtx mtx;
    Mtx44 proj;
    f32 corner[4][3];
    f32 uv[4][2] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
    f32 halfW = p->sizeX / 2.0f;
    f32 halfH = p->sizeY / 2.0f;
    int i;

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
    fn_80033B58((void*)effect->texture, p->texIndex, 0, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    for (i = 0; i < 4; i++) {
        GXPosition3f32(p->origin.x + corner[i][0], p->origin.y + corner[i][1], -1.0f);
        GXColor1u32(*(u32*)&p->colorR);
        GXTexCoord2f32(uv[p->_4E + i][0], uv[p->_4E + i][1]);
    }
    GXLoadPosMtxImm(fn_80052768_getCamera(0)->view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetProjection(fn_80052768_getCamera(0)->proj, GX_PERSPECTIVE);
}

// .text:0x151798 size:0x38
void chainChomp_stopItemSparkles(void) {
    memset(lbl_3_bss_B894, 0, 0xF);
    pitchingMachinePitching(0x1C);
}

// .text:0x151760 size:0x38
void chainChomp_stopItemSparkles2(void) {
    memset(lbl_3_bss_B894, 0, 0xF);
    pitchingMachinePitching(0x1C);
}

// .text:0x151710 size:0x50
void wallBall_spawnNoteBlockBurst(MGWeatherCtx* ctx, Vec* pos) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && g_Minigame.GameMode_MiniGame == MINI_GAME_ID_WALLBALL &&
        ctx != NULL) {
        wallBall_spawnNoteBlockBurstEffect(ctx, pos);
    }
}

// .text:0x151694 size:0x7C
void wallBall_spawnNoteBlockBurstEffect(MGWeatherCtx* ctx, Vec* pos) {
    MGWeatherEffect* effect =
        allocParticleEffect(wallBall_updateNoteBlockBurst, 0x80, 0, wallBall_noteBlockBurstParams[1] + wallBall_noteBlockBurstParams[9], TRUE, 0x1D);

    if (effect != NULL) {
        wallBall_initNoteBlockBurst(effect, ctx, pos);
    }
}

// .text:0x151204 size:0x490
void wallBall_initNoteBlockBurst(MGWeatherEffect* effect, MGWeatherCtx* ctx, Vec* pos) {
    MGParticle* p;
    u32 snowCount = 0;
    u32 rainCount = 0;

    effect->texture = *(u32*)&animRelated[0x6C];
    effect->ctx = ctx;
    memcpy(&effect->pos, pos, sizeof(Vec));
    p = effect->particles;
    do {
        if (snowCount < wallBall_noteBlockBurstParams[1]) {
            p->delay = ++snowCount;
            p->texIndex = wallBall_noteBlockBurstParams[0];
            p->kind = 1;
            p->life = wallBall_noteBlockBurstParams[6];
            if (p->delay == 0) {
                wallBall_placeNoteParticle(effect, p);
            }
        } else {
            p->delay = rainCount++;
            p->texIndex = wallBall_noteBlockBurstParams[8];
            p->kind = 2;
            wallBall_placeBounceParticle(effect, p);
        }
        p->_4E = 0;
        p = p->next;
    } while (p != NULL);
}

// .text:0x151068 size:0x19C
void wallBall_placeNoteParticle(MGWeatherEffect* effect, MGParticle* p) {
    Mtx mtx;
    MGActor* actor;
    f32 x;
    f32 y;
    f32 z;

    p->life = wallBall_noteBlockBurstParams[6];
    actor = effect->ctx->list->actors[wallBall_noteBlockBurstParams[7]];
    PSMTXIdentity(mtx);
    x = actor->mtx[0][3];
    y = actor->mtx[1][3];
    z = actor->mtx[2][3];
    x += (rand() % 100 - 50) / 100.0;
    y += (rand() % 150 - 75) / 100.0;
    p->origin.x = x;
    p->origin.y = y;
    p->origin.z = z;
    p->sizeY = p->sizeX = (f32)wallBall_noteBlockBurstParams[2];
    p->alphaByte = wallBall_noteBlockBurstParams[4];
}

// .text:0x150D84 size:0x2E4
void wallBall_placeBounceParticle(MGWeatherEffect* effect, MGParticle* p) {
    f32 angle;
    f32 speed;

    p->life = wallBall_noteBlockBurstParams[20];
    p->origin.x = effect->pos.x;
    p->origin.y = -effect->pos.y;
    p->origin.z = effect->pos.z;
    p->sizeX = p->sizeY = (f32)(wallBall_noteBlockBurstParams[10] + rand() % (wallBall_noteBlockBurstParams[11] - wallBall_noteBlockBurstParams[10])) / 100000.0f;
    p->velY = (f32)(wallBall_noteBlockBurstParams[12] + rand() % (wallBall_noteBlockBurstParams[13] - wallBall_noteBlockBurstParams[12])) / 100000.0f;
    angle = 0.017453292f * (f32)((rand() % 36000) / 100.0);
    speed = (f32)(wallBall_noteBlockBurstParams[16] + rand() % (wallBall_noteBlockBurstParams[17] - wallBall_noteBlockBurstParams[16])) / 100000.0f;
    p->velX = speed * (f32)cos(angle);
    p->velZ = speed * (f32)sin(angle);
    p->_1C = 57.29578f * ((f32)(wallBall_noteBlockBurstParams[18] + rand() % (wallBall_noteBlockBurstParams[19] - wallBall_noteBlockBurstParams[18])) / 100000.0f);
    p->_1C = p->_1C * (f32)(-(rand() % 2 * 2) + 1);
    p->colorR = p->colorG = p->colorB = p->alphaByte = 0xFF;
}

// .text:0x150940 size:0x444
int wallBall_updateNoteBlockBurst(MGWeatherEffect* effect) {
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
        if (p->life != 0) {
            if (p->kind == 1) {
                wallBall_updateNoteParticle(effect, p);
            } else if (p->kind == 2) {
                wallBall_updateBounceParticle(effect, p);
            }
        }
        p = p->next;
    } while (p != NULL);
    return 0;
}

// .text:0x1504EC size:0x454
void wallBall_updateNoteParticle(MGWeatherEffect* effect, MGParticle* p) {
    s32 duration;
    s32 alpha;
    s32 alphaStep;
    f32 sizeStep;

    if (p->delay != 0) {
        p->delay--;
        if (p->delay == 0) {
            wallBall_placeNoteParticle(effect, p);
        }
        return;
    }
    fn_8003403C(p->sizeX, p->sizeY);
    fn_80033CC8(p, effect->texture);
    duration = wallBall_noteBlockBurstParams[6];
    alpha = p->alphaByte;
    if (duration / p->life < 2) {
        sizeStep = (f32)wallBall_noteBlockBurstParams[3] / 100000.0f / (f32)(duration / 2);
        alphaStep = wallBall_noteBlockBurstParams[5] / (duration / 2);
    } else {
        sizeStep = -((f32)wallBall_noteBlockBurstParams[3] / 100000.0f) / (f32)(duration / 2);
        alphaStep = -wallBall_noteBlockBurstParams[5] / (duration / 2);
    }
    alpha = alpha + alphaStep;
    if (alpha > 0xFF) {
        alpha = 0xFF;
    } else if (alpha < 0) {
        alpha = 0;
    }
    p->alphaByte = alpha;
    p->sizeX += sizeStep;
    p->sizeY = p->sizeX;
    p->life--;
    if (p->life == 0) {
        wallBall_placeNoteParticle(effect, p);
    }
}

// .text:0x150120 size:0x3CC
void wallBall_updateBounceParticle(MGWeatherEffect* effect, MGParticle* p) {
    if (p->delay != 0) {
        p->delay--;
        return;
    }
    setParticleXform(p->sizeX, p->sizeY, p->_1C);
    fn_80033CC8(p, effect->texture);
    p->origin.x += p->velX;
    p->origin.y -= p->velY;
    p->origin.z += p->velZ;
    if (p->origin.y > 0.0f) {
        p->origin.y = 0.0f;
        p->velY = -p->velY * ((f32)wallBall_noteBlockBurstParams[15] / 100000.0f);
    }
    if (--p->life == 0) {
        wallBall_placeBounceParticle(effect, p);
    }
}

// .text:0x1500C8 size:0x58
void wallBall_updateSomePointers(void) {
    MGEffect* effect = fn_800339F0(0, 0x1D);
    MGParticle* p;

    if (effect != NULL) {
        p = effect->particles;
        do {
            p->life = 0;
            p->delay = 0;
            p->kind = 0;
            p = p->next;
        } while (p != NULL);
    }
    pitchingMachinePitching(0x1D);
}

// .text:0x150070 size:0x58
void wallBall_updateSomePointers2(void) {
    MGEffect* effect = fn_800339F0(0, 0x1D);
    MGParticle* p;

    if (effect != NULL) {
        p = effect->particles;
        do {
            p->life = 0;
            p->delay = 0;
            p->kind = 0;
            p = p->next;
        } while (p != NULL);
    }
    pitchingMachinePitching(0x1D);
}

// .text:0x150010 size:0x60
void starDash_startSparks(s8 index) {
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES) {
        return;
    }
    if (g_Minigame.GameMode_MiniGame != MINI_GAME_ID_STAR_DASH) {
        return;
    }
    if (index > SD_STAR_SPARK_INDEX || index < 0) {
        return;
    }
    starDash_spawnSparksEffect(index);
}

// .text:0x14F930 size:0x6E0
void starDash_spawnSparksEffect(s8 index) {
    MGEffect* effect = fn_800339F0(0, 0x1E);
    if (effect != NULL) {
        starDash_setupSparks(effect, index);
    } else {
        effect = allocParticleEffect(starDash_updateSparks, 0x80, 0, starDash_sparkParams[1], TRUE, 0x1E);
        if (effect != NULL) {
            starDash_initSparksEffect(effect);
            starDash_setupSparks(effect, index);
        }
    }
}

// .text:0x14F8D0 size:0x60
void starDash_initSparksEffect(MGEffect* effect) {
    MGParticle* p;
    u32 i = 0;

    effect->texture = *(u32*)&animRelated[0x6C];
    p = effect->particles;
    do {
        p->_4F = 0;
        p->texIndex = starDash_sparkParams[0];
        p->_4E = 0;
        p->kind = i / 18 + 1;
        i++;
        p = p->next;
    } while (p != NULL);
}

// .text:0x14F5A4 size:0x32C
void starDash_setupSparks(MGEffect* effect, s8 index) {
    MGParticle* p = effect->particles;
    u32 i = 0;

    do {
        if (p->kind == index + 1) {
            p->life = starDash_sparkParams[7];
            p->alphaByte = starDash_sparkParams[5];
            p->sizeX = p->sizeY = (f32)starDash_sparkParams[2] / 100000.0f;
            p->delay = (s16)((f32)p->life / 18.0f * (f32)i);
            if (p->delay == 0) {
                starDash_placeSparkParticle(p);
            }
            p->colorR = p->colorG = p->colorB = 0xFF;
            i++;
            p->_34 = 0.0f;
        }
        p = p->next;
    } while (p != NULL);
}

// .text:0x14F544 size:0x60
void starDash_resetSparkParticle(MGParticle* p) {
    p->life = starDash_sparkParams[7];
    p->alphaByte = starDash_sparkParams[5];
    p->sizeX = p->sizeY = (f32)starDash_sparkParams[2] / 100000.0f;
}

// .text:0x14F3CC size:0x178
void starDash_randomizeSparkOrigin(MGParticle* p) {
    Vec v = { 0.0f, 0.0f, 0.0f };
    f32 yOffset;
    s16 rangeX;
    s16 rangeY;

    if (p->kind < 5) {
        yOffset = 1.25f;
    } else {
        yOffset = 0.5f;
    }
    rangeX = (p->kind < 5) ? 20000 : 10000;
    rangeY = (p->kind < 5) ? 20000 : 10000;
    v.x = v.x + (f32)(rand() % rangeX - rangeX / 2) / 10000.0f;
    v.y = v.y + (f32)(rand() % rangeY - rangeY / 2) / 10000.0f;
    p->origin.x = v.x;
    p->origin.y = v.y - yOffset;
    p->origin.z = v.z;
}

// .text:0x14ED24 size:0x6A8
int starDash_updateSparks(MGEffect* effect) {
    MGParticle* p;
    s32 duration;
    s32 alpha;
    f32 sizeStep;

    fn_80033620(effect);
    p = effect->particles;
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    do {
        if (p->life != 0) {
            if (p->delay <= 0) {
                GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
                fn_8003403C(p->sizeX, p->sizeY);
                fn_80033CC8(p, effect->texture);
                duration = starDash_sparkParams[7];
                if (duration / p->life < 2) {
                    alpha = p->alphaByte;
                    alpha += starDash_sparkParams[6] / (duration / 2);
                    if (alpha > starDash_sparkParams[6]) {
                        alpha = starDash_sparkParams[6];
                    }
                    p->alphaByte = alpha;
                    sizeStep = (f32)(starDash_sparkParams[3] - starDash_sparkParams[2]) / 100000.0f / (f32)(starDash_sparkParams[7] / 2);
                    p->sizeX += sizeStep;
                    p->sizeY = p->sizeX;
                } else {
                    alpha = p->alphaByte;
                    alpha -= starDash_sparkParams[6] / (duration / 2);
                    if (alpha < starDash_sparkParams[5]) {
                        alpha = starDash_sparkParams[5];
                    }
                    p->alphaByte = alpha;
                    sizeStep = (f32)(starDash_sparkParams[4] - starDash_sparkParams[3]) / 100000.0f / (f32)(starDash_sparkParams[7] / 2);
                    p->sizeX += sizeStep;
                    p->sizeY = p->sizeX;
                }
                p->life--;
                if (p->life == 0) {
                    p->life = starDash_sparkParams[7];
                    p->alphaByte = starDash_sparkParams[5];
                    p->sizeX = p->sizeY = (f32)starDash_sparkParams[2] / 100000.0f;
                    starDash_placeSparkParticle(p);
                }
            } else {
                p->delay--;
                if (p->delay == 0) {
                    starDash_placeSparkParticle(p);
                }
            }
        }
        p = p->next;
    } while (p != NULL);
    return 0;
}

// .text:0x14EAF4 size:0x230
void starDash_placeSparkParticle(MGParticle* p) {
    Vec v = { 0.0f, 0.0f, 0.0f };

    if (p->kind == 5) {
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
    starDash_offsetSparkToBone(p);
}

// .text:0x14E9F0 size:0x104
void starDash_offsetSparkToBone(MGParticle* p) {
    Vec offset;
    u32 node;

    if (p->kind < 5) {
        node = starDash_sparkBoneNodes[(u32)rand() % 23];
        offset.z = 0.0f;
        offset.y = 0.0f;
        offset.x = 0.0f;
        if (!getAnimationCollisionOffset(p->kind - 1, node, &offset)) {
            memset(&offset, 0, sizeof(Vec));
            getAnimationCollisionOffset(p->kind - 1, 4, &offset);
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

// .text:0x14E988 size:0x68
void starDash_stopSparks(s8 index) {
    MGEffect* effect = fn_800339F0(0, 0x1E);
    MGParticle* p;

    if (effect != NULL) {
        p = effect->particles;
        do {
            if (p->kind == index + 1) {
                p->life = 0;
            }
            p = p->next;
        } while (p != NULL);
    }
}

// .text:0x14E920 size:0x68
void starDash_stopSparks2(s8 index) {
    MGEffect* effect = fn_800339F0(0, 0x1E);
    MGParticle* p;

    if (effect != NULL) {
        p = effect->particles;
        do {
            if (p->kind == index + 1) {
                p->life = 0;
            }
            p = p->next;
        } while (p != NULL);
    }
}

// .text:0x14E894 size:0x8C
void starDash_stopAllSparks(void) {
    u32 i;
    s8 index;
    MGEffect* effect;
    MGParticle* p;

    for (i = 0; i < MG_PLAYER_COUNT; i++) {
        index = i;
        effect = fn_800339F0(0, 0x1E);
        if (effect != NULL) {
            p = effect->particles;
            do {
                if (p->kind == index + 1) {
                    p->life = 0;
                }
                p = p->next;
            } while (p != NULL);
        }
    }
    pitchingMachinePitching(0x1E);
}

// .text:0x14E810 size:0x84
void starDash_stopAllSparks2(void) {
    u32 i;

    for (i = 0; i < MG_PLAYER_COUNT; i++) {
        starDash_stopSparks2(i);
    }
    pitchingMachinePitching(0x1E);
}

// .text:0x14E7C0 size:0x50
void starDash_spawnDust(Vec* pos) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && g_Minigame.GameMode_MiniGame == MINI_GAME_ID_STAR_DASH &&
        pos != NULL) {
        starDash_spawnDustEffect(pos);
    }
}

// .text:0x14E234 size:0x58C
void starDash_spawnDustEffect(Vec* pos) {
    MGEffect* existing = fn_800339F0(0, 0x1F);
    MGEffect* fresh;
    u8 scratch[0x60];

    if (existing != NULL) {
        fresh = fn_800337CC(scratch, starDash_dustParams[1], 1);
        if (fresh != NULL) {
            MGParticle* tail;

            starDash_initDustParticles(fresh, pos);
            tail = existing->particles;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = fresh->particles;
            existing->count += fresh->count;
        }
    } else {
        fresh = allocParticleEffect(starDash_updateDust, 0x80, 0, starDash_dustParams[1], TRUE, 0x1F);
        if (fresh != NULL) {
            starDash_initDustParticles(fresh, pos);
        }
    }
}

// .text:0x14DF6C size:0x2C8
void starDash_initDustParticles(MGEffect* effect, Vec* pos) {
    MGParticle* p = effect->particles;
    f32 speed;

    effect->texture = *(u32*)&animRelated[0x6C];
    do {
        p->texIndex = starDash_dustParams[0];
        p->_4E = 0;
        p->origin.x = pos->x + (f32)(rand() % 1000 - 500) / 1000.0f;
        p->origin.y = -(0.75f + pos->y);
        p->origin.z = pos->z + (f32)(rand() % 1000 - 500) / 1000.0f;
        p->velX = p->velZ = 0.0f;
        p->velY = (f32)starDash_dustParams[9] / 100000.0f;
        speed = p->velY;
        p->velY = p->velY + ((f32)(rand() % (s32)(1000.0f * (speed / 2.0f))) - 1000.0f * (speed / 4.0f)) / 1000.0f;
        p->colorR = p->colorG = p->colorB = 0xFF;
        p->alphaByte = starDash_dustParams[6];
        p->_1C = (f32)(rand() % 1000 + 500) / 1000.0f;
        p->sizeX = p->sizeY = ((f32)starDash_dustParams[3] / 100000.0f) * p->_1C;
        p->life = starDash_dustParams[2];
        p->delay = 0;
        p = p->next;
    } while (p != NULL);
}

// .text:0x14DD04 size:0x268
int starDash_updateDust(MGEffect* effect) {
    MGParticle* p;
    MGParticle** link;
    MGParticle* removedTail;
    u32 alive;
    s32 duration;
    s32 alpha;
    s32 alphaStep;
    f32 sizeStep;

    alive = 0;
    p = effect->particles = fn_80031F34(effect->particles, effect->count);
    link = &effect->particles;
    removedTail = NULL;
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
    do {
        if (p->life != 0) {
            fn_8003403C(p->sizeX, p->sizeY);
            fn_80033CC8(p, effect->texture);
            p->origin.y = p->origin.y - p->velY;
            p->velY = p->velY - (f32)starDash_dustParams[10] / 100000.0f;
            duration = starDash_dustParams[2];
            alpha = p->alphaByte;
            if (duration / p->life < 2) {
                sizeStep = (f32)(starDash_dustParams[4] - starDash_dustParams[3]) / 100000.0f / (f32)(duration / 2) * p->_1C;
                alphaStep = (starDash_dustParams[7] - starDash_dustParams[6]) / (duration / 2);
            } else {
                sizeStep = (f32)(starDash_dustParams[5] - starDash_dustParams[4]) / 100000.0f / (f32)(duration / 2) * p->_1C;
                alphaStep = (starDash_dustParams[8] - starDash_dustParams[7]) / (duration / 2);
            }
            p->sizeX += sizeStep;
            p->sizeY = p->sizeX;
            alpha += alphaStep;
            if (alpha < 0) {
                alpha = 0;
            } else if (alpha > 0xFF) {
                alpha = 0xFF;
            }
            p->alphaByte = alpha;
            p->life--;
            if (p->life == 0) {
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
void starDash_stopDust(void) {
    pitchingMachinePitching(0x1F);
}

// .text:0x14DC80 size:0x60
void barrelBatter_spawnBarrelExplosion(s8 index) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER) {
        if (index < BB_BARREL_COUNT && index >= 0) {
            barrelBatter_spawnBarrelExplosionEffect(index);
        }
    }
}

// .text:0x14D710 size:0x570
void barrelBatter_spawnBarrelExplosionEffect(u8 index) {
    MGEffect* effect = fn_800339F0(0, 0x20);

    if (effect != NULL) {
        barrelBatter_setupBarrelExplosion(effect, index);
    } else {
        effect = allocParticleEffect(barrelBatter_updateBarrelExplosion, 0xF0, 0, barrelBatter_explosionParams[2], TRUE, 0x20);
        if (effect != NULL) {
            barrelBatter_initBarrelExplosion(effect);
            barrelBatter_setupBarrelExplosion(effect, index);
        }
    }
}

// .text:0x14D6D4 size:0x3C
void barrelBatter_initBarrelExplosion(MGEffect* effect) {
    MGParticle* p;

    effect->texture = *(u32*)&animRelated[0x6C];
    p = effect->particles;
    do {
        p->_46 = 0;
        p->_45 = 0;
        p->_44 = 0;
        p->life = 0;
        p->_4E = 0;
        p = p->next;
    } while (p != NULL);
}

// .text:0x14D44C size:0x288
void barrelBatter_setupBarrelExplosion(MGEffect* effect, u8 barrelIndex) {
    MGParticle* p = effect->particles;
    s32 i = 0;

    do {
        if (p->_44 == 0 && p->life == 0) {
            if (i < 3) {
                p->_44 = 1;
                p->_45 = (u8)barrelIndex;
                p->_46 = 0xFF;
                p->texIndex = barrelBatter_explosionParams[0];
                p->sizeX = p->sizeY = (f32)barrelBatter_explosionParams[4];
                p->alphaByte = barrelBatter_explosionParams[7];
                barrelBatter_placeExplosionFlash(p);
                p->life = barrelBatter_explosionParams[17];
                p->delay = 0;
            } else {
                p->_44 = 2;
                p->_45 = (u8)barrelIndex;
                p->_46 = (i - 3) / 5;
                p->texIndex = barrelBatter_explosionParams[1];
                p->sizeX = p->sizeY = (f32)barrelBatter_explosionParams[11];
                p->alphaByte = barrelBatter_explosionParams[14];
                p->delay = (i - 3) % 5 * 4 + 1;
                p->life = barrelBatter_explosionParams[18];
            }
            p->colorR = p->colorG = p->colorB = 0xFF;
            i++;
        }
        p = p->next;
    } while (p != NULL && i < 43);
}

// .text:0x14D318 size:0x134
void barrelBatter_placeExplosionFlash(MGParticle* p) {
    Vec* barrel = (Vec*)&g_Minigame.barrels[p->_45];

    p->origin.x = barrel->x;
    p->origin.y = -(barrel->y + bB_barrelConsts[3] / 2.0f);
    p->origin.z = barrel->z;
    p->origin.x = p->origin.x + (rand() % 100 - 50) / 100.0;
    p->origin.y = p->origin.y + (rand() % 100 - 50) / 100.0;
}

// .text:0x14D2C0 size:0x58
void barrelBatter_attachExplosionToBone(MGParticle* p) {
    MGActorList* list = *(MGActorList**)(*(u8**)&hugeAnimStruct[0x68] + (p->_45 + 0x10) * 0x90 + 0x34);
    MGActor* actor = list->actors[p->_46];

    p->origin.x = actor->mtx[0][3];
    p->origin.y = actor->mtx[1][3];
    p->origin.z = actor->mtx[2][3];
}

// .text:0x14CECC size:0x3F4
int barrelBatter_updateBarrelExplosion(MGEffect* effect) {
    MGParticle* p;

    if (lbl_80366158[0x28] != 0) {
        return 0;
    }
    fn_80033620(effect);
    p = effect->particles;
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    do {
        if (p->_44 != 0 && p->life != 0) {
            if (p->delay <= 0) {
                if (p->_44 == 1) {
                    barrelBatter_updateExplosionFlash(effect, p);
                } else {
                    if (p->delay == 0) {
                        barrelBatter_attachExplosionToBone(p);
                    }
                    barrelBatter_updateExplosionEmber(effect, p);
                }
                p->life--;
                if (p->life == 0) {
                    p->_44 = 0;
                    p->_45 = 0xFF;
                    p->life = 0;
                    p->kind = 0;
                }
            }
            p->delay--;
        }
        p = p->next;
    } while (p != NULL);
    return 0;
}

// .text:0x14CD40 size:0x18C
void barrelBatter_updateExplosionFlash(MGEffect* effect, MGParticle* p) {
    s32 duration;
    s32 alpha;
    s32 alphaStep;
    f32 sizeStep;

    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_LO_CLEAR);
    fn_8003403C(p->sizeX, p->sizeY);
    fn_80033CC8(p, effect->texture);
    duration = barrelBatter_explosionParams[3];
    alpha = p->alphaByte;
    if (-p->delay < duration) {
        sizeStep = (f32)barrelBatter_explosionParams[5] / 100000.0f / (f32)duration;
        alphaStep = barrelBatter_explosionParams[8] / duration;
    } else {
        sizeStep = (f32)(barrelBatter_explosionParams[6] - barrelBatter_explosionParams[5]) / 100000.0f / (f32)(barrelBatter_explosionParams[17] - duration);
        alphaStep = (barrelBatter_explosionParams[9] - barrelBatter_explosionParams[8]) / (barrelBatter_explosionParams[17] - duration);
    }
    alpha += alphaStep;
    if (alpha > 0xFF) {
        alpha = 0xFF;
    } else if (alpha < 0) {
        alpha = 0;
    }
    p->alphaByte = alpha;
    p->colorR = p->colorG = p->colorB = p->alphaByte;
    p->sizeX += sizeStep;
    p->sizeY = p->sizeX;
}

// .text:0x14CBB4 size:0x18C
void barrelBatter_updateExplosionEmber(MGEffect* effect, MGParticle* p) {
    s32 duration;
    s32 alpha;
    s32 alphaStep;
    f32 sizeStep;

    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    fn_8003403C(p->sizeX, p->sizeY);
    fn_80033CC8(p, effect->texture);
    duration = barrelBatter_explosionParams[10];
    alpha = p->alphaByte;
    if (-p->delay < duration) {
        sizeStep = (f32)barrelBatter_explosionParams[12] / 100000.0f / (f32)duration;
        alphaStep = barrelBatter_explosionParams[15] / duration;
    } else {
        sizeStep = (f32)(barrelBatter_explosionParams[13] - barrelBatter_explosionParams[12]) / 100000.0f / (f32)(barrelBatter_explosionParams[18] - duration);
        alphaStep = (barrelBatter_explosionParams[16] - barrelBatter_explosionParams[15]) / (barrelBatter_explosionParams[18] - duration);
    }
    alpha += alphaStep;
    if (alpha > 0xFF) {
        alpha = 0xFF;
    } else if (alpha < 0) {
        alpha = 0;
    }
    p->alphaByte = alpha;
    p->colorR = p->colorG = p->colorB = p->alphaByte;
    p->sizeX += sizeStep;
    p->sizeY = p->sizeX;
}

// .text:0x14CB28 size:0x8C
void barrelBatter_releaseBarrelExplosion(s8 index) {
    if (index >= BB_BARREL_COUNT || index < 0) {
        return;
    }
    barrelBatter_releaseBarrelExplosion2(index);
}

// .text:0x14CAB4 size:0x74
void barrelBatter_releaseBarrelExplosion2(s8 index) {
    MGEffect* effect = fn_800339F0(0, 0x20);
    MGParticle* p;

    if (effect != NULL) {
        p = effect->particles;
        do {
            if (p->_45 == index) {
                p->_44 = 0;
                p->_45 = 0xFF;
                p->life = 0;
                p->kind = 0;
            }
            p = p->next;
        } while (p != NULL);
    }
}

// .text:0x14CA98 size:0x1C
void barrelBatter_clearExplosionParticle(MGParticle* p) {
    p->_44 = 0;
    p->_45 = 0xFF;
    p->life = 0;
    p->kind = 0;
}

// .text:0x14CA00 size:0x98
void barrelBatter_stopBarrelExplosions(void) {
    u32 i;

    for (i = 0; i < BB_BARREL_COUNT; i++) {
        barrelBatter_releaseBarrelExplosion2(i);
    }
    pitchingMachinePitching(0x20);
}

// .text:0x14C904 size:0xFC
void chainChomp_spawnLaunchFlash(void) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && g_Minigame.GameMode_MiniGame == MINI_GAME_ID_CHAINCHOMP_SPRINT) {
        chainChomp_spawnLaunchFlashEffect();
    }
}

// .text:0x14C830 size:0xD4
void chainChomp_spawnLaunchFlashEffect(void) {
    MGEffect* effect = allocParticleEffect(chainChomp_updateLaunchFlash, 0x80, 0, chainChomp_launchFlashParams[1], TRUE, 0xA);

    if (effect != NULL) {
        chainChomp_initLaunchFlash(effect);
    }
}

// .text:0x14C79C size:0x94
void chainChomp_initLaunchFlash(MGEffect* effect) {
    MGParticle* p;

    effect->texture = *(u32*)&animRelated[0x6C];
    p = effect->particles;
    p->texIndex = chainChomp_launchFlashParams[0];
    p->_4E = 0;
    p->life = chainChomp_launchFlashParams[2];
    p->sizeX = p->sizeY = (f32)chainChomp_launchFlashParams[4] / 100000.0f;
    p->alphaByte = chainChomp_launchFlashParams[7];
    p->colorR = p->colorG = p->colorB = 0xFF;
}

// .text:0x14C4C8 size:0x2D4
int chainChomp_updateLaunchFlash(MGEffect* effect) {
    MGParticle* p;
    s32 duration;
    s32 remaining;
    s32 alpha;
    s32 alphaStep;
    f32 sizeStep;

    if (lbl_80366158[0x28] != 0) {
        return FALSE;
    }
    p = effect->particles;
    if (p->life != 0) {
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_LO_CLEAR);
        chainChomp_placeLaunchFlash(p);
        fn_8003403C(p->sizeX, p->sizeY);
        fn_80033CC8(p, effect->texture);
        duration = chainChomp_launchFlashParams[3];
        remaining = chainChomp_launchFlashParams[2] - duration;
        alpha = p->alphaByte;
        if (remaining < p->life) {
            sizeStep = (f32)(chainChomp_launchFlashParams[5] - chainChomp_launchFlashParams[4]) / 100000.0f / (f32)duration;
            alphaStep = (chainChomp_launchFlashParams[8] - chainChomp_launchFlashParams[7]) / duration;
        } else {
            sizeStep = (f32)(chainChomp_launchFlashParams[6] - chainChomp_launchFlashParams[5]) / 100000.0f / (f32)remaining;
            alphaStep = (chainChomp_launchFlashParams[9] - chainChomp_launchFlashParams[8]) / remaining;
        }
        alpha += alphaStep;
        if (alpha < 0) {
            alpha = 0;
        }
        if (alpha > 0xFF) {
            alpha = 0xFF;
        }
        p->sizeX += sizeStep;
        p->sizeY = p->sizeX;
        p->alphaByte = alpha;
        p->colorR = p->colorG = p->colorB = p->alphaByte;
        p->life--;
    } else {
        return TRUE;
    }
    return FALSE;
}

// .text:0x14C3BC size:0x10C
void chainChomp_placeLaunchFlash(MGParticle* p) {
    Vec offset;
    Mtx rot;

    PSVECScale(&chainChomp_launchFlashOffset, 0.75f, &offset);
    PSMTXRotRad(rot, 'Y', shortAngleToRad(g_Minigame.ccs.chompYaw));
    PSMTXMultVec(rot, &offset, &offset);
    p->origin.x = g_Minigame.ccs.chompPos.x + offset.x + (f32)chainChomp_launchFlashParams[5] / 100000.0f / 2.0f;
    p->origin.y = offset.y - ((f32)chainChomp_launchFlashParams[5] / 100000.0f / 2.0f + g_Minigame.ccs.chompPos.y);
    p->origin.z = g_Minigame.ccs.chompPos.z + offset.z;
}

// .text:0x14C398 size:0x24
void chainChomp_stopLaunchFlash(void) {
    pitchingMachinePitching(0x21);
}

// .text:0x14C348 size:0x50
void wallBall_spawnWallHitPuff(Vec* pos, u8 flag) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && g_Minigame.GameMode_MiniGame == MINI_GAME_ID_WALLBALL && pos != NULL) {
        wallBall_spawnWallHitPuffEffect(pos, flag);
    }
}

// .text:0x14BECC size:0x47C
void wallBall_spawnWallHitPuffEffect(Vec* pos, u8 flag) {
    MGEffect* existing = fn_800339F0(0, 0x22);
    MGEffect* fresh;
    u8 scratch[0x60];

    if (existing != NULL) {
        MGParticle* tail;

        fresh = fn_800337CC(scratch, wallBall_wallHitPuffParams[1], 1);
        wallBall_initWallHitPuff(fresh, pos, flag);
        tail = existing->particles;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = fresh->particles;
        existing->count += fresh->count;
    } else {
        fresh = allocParticleEffect(wallBall_updateWallHitPuff, 0x80, 0, wallBall_wallHitPuffParams[1], TRUE, 0x22);
        if (fresh != NULL) {
            wallBall_initWallHitPuff(fresh, pos, flag);
        }
    }
}

// .text:0x14BCB0 size:0x21C
void wallBall_initWallHitPuff(MGEffect* effect, Vec* pos, u8 flag) {
    s32* tbl;
    MGParticle* p;
    u32 count = 0;
    f32 angle;
    f32 speed;

    effect->texture = *(u32*)&animRelated[0x6C];
    p = effect->particles;
    if (flag != 0) {
        tbl = wallBall_wallHitDarkPuffParams;
    } else {
        tbl = wallBall_wallHitPuffParams;
    }
    do {
        if (p->life == 0) {
            p->texIndex = tbl[0];
            p->_4E = 0;
            p->life = tbl[2];
            p->sizeX = p->sizeY = (f32)tbl[4] / 100000.0f;
            p->alphaByte = tbl[10];
            p->colorR = tbl[7];
            p->colorG = tbl[8];
            p->colorB = tbl[9];
            speed = 2.0f * (2.0 * ((f32)rand() / 32767.0f - 0.5));
            angle = 0.017453292f * (f32)(180.0 / tbl[1] * count);
            p->origin.x = pos->x + speed * (f32)cos(angle);
            p->origin.y = pos->y - speed * (f32)sin(angle) - 1.0;
            count++;
            p->origin.z = pos->z;
            p->_4F = flag;
        }
        p = p->next;
    } while (p != NULL && count < wallBall_wallHitPuffParams[1]);
}

// .text:0x14BA40 size:0x270
int wallBall_updateWallHitPuff(MGEffect* effect) {
    s32* tbl;
    MGParticle* p;
    MGParticle** link;
    MGParticle* removedHead;
    MGParticle* removedTail;
    s32 rampLength;
    u32 alive = 0;
    s32 duration;
    s32 alpha;
    s32 alphaStep;
    f32 sizeStep;


    if (lbl_80366158[0x28] != 0) {
        return 0;
    }
    p = effect->particles = fn_80031F34(effect->particles, effect->count);
    link = &effect->particles;
    removedTail = NULL;
    removedHead = NULL;
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    do {
        if (p->life != 0) {
            if (p->_4F == 0) {
                tbl = wallBall_wallHitPuffParams;
            } else {
                tbl = wallBall_wallHitDarkPuffParams;
            }
            duration = tbl[2];
            rampLength = tbl[3];
            fn_8003403C(p->sizeX, p->sizeY);
            fn_80033CC8(p, effect->texture);
            alpha = p->alphaByte;
            if (duration - p->life < rampLength) {
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
            p->sizeX += sizeStep;
            p->sizeY = p->sizeX;
            p->life--;
            if (p->life == 0) {
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
            p->kind = 0;
            p->delay = 0;
            p = p->next;
        } while (p != NULL);
        fn_80033794(removedHead);
    }
    return alive == 0;
}

// .text:0x14B9F0 size:0x50
void wallBall_stopWallHitPuff(void) {
    MGEffect* effect = fn_800339F0(0, 0x22);
    MGParticle* p;

    if (effect != NULL) {
        p = effect->particles;
        do {
            p->life = 0;
            p = p->next;
        } while (p != NULL);
    }
    pitchingMachinePitching(0x22);
}

// .text:0x14B9A0 size:0x50
void barrelBatter_spawnMachineSparks(s32 frames, Vec* start) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER &&
        start != NULL) {
        barrelBatter_spawnMachineSparksEffect(frames, start);
    }
}

// .text:0x14B92C size:0x74
#pragma dont_inline on
void barrelBatter_spawnMachineSparksEffect(s32 frames, Vec* start) {
    MGPathEffect* effect = allocParticleEffect(barrelBatter_updateMachineSparks, 0x80, 0, barrelBatter_machineSparkParams[2], TRUE, 0x23);
    if (effect != NULL) {
        barrelBatter_initMachineSparks(effect, frames, start);
    }
}
#pragma dont_inline reset

// .text:0x14B53C size:0x3F0
void barrelBatter_initMachineSparks(MGPathEffect* effect, s32 frames, Vec* start) {
    MGParticle* p;
    Vec diff;
    f32 seg1;
    f32 seg2;
    s32 i = 0;

    effect->base = *start;
    effect->texture = *(u32*)&animRelated[0x6C];
    effect->total = frames;
    effect->remaining = frames;
    PSVECSubtract((Vec*)barrelBatter_machineSparkPath, (Vec*)(barrelBatter_machineSparkPath + 3), &diff);
    seg1 = PSVECMag(&diff);
    PSVECSubtract((Vec*)(barrelBatter_machineSparkPath + 3), (Vec*)(barrelBatter_machineSparkPath + 6), &diff);
    seg2 = PSVECMag(&diff);
    effect->span = seg1 / ((seg2 + seg1) / (f32)(u32)frames);
    barrelBatter_updateMachineSparkPos(effect);
    p = effect->particles;
    do {
        p->texIndex = barrelBatter_machineSparkParams[0];
        p->_4E = 0;
        p->delay = (s16)((f32)i * ((f32)effect->total / (f32)barrelBatter_machineSparkParams[2]));
        p->colorR = p->colorG = p->colorB = 0xFF;
        p->life = barrelBatter_machineSparkParams[1];
        if (p->delay == 0) {
            barrelBatter_respawnMachineSpark(effect, p);
        }
        p = p->next;
        i++;
    } while (p != NULL);
}

// .text:0x14B3F4 size:0x148
void barrelBatter_updateMachineSparkPos(MGPathEffect* effect) {
    f32* from;
    f32* to;
    f32 t;
    f32 scale;

    if ((f32)(effect->total - effect->remaining) < effect->span) {
        from = barrelBatter_machineSparkPath;
        to = from + 3;
        t = (f32)(effect->total - effect->remaining) / effect->span;
    } else {
        from = barrelBatter_machineSparkPath + 3;
        to = barrelBatter_machineSparkPath + 6;
        t = ((f32)(effect->total - effect->remaining) - effect->span) / ((f32)effect->total - effect->span);
    }
    scale = mm_GetPitchingMachineScale();
    effect->pos.x = scale * (from[0] * (1.0f - t) + to[0] * t) + effect->base.x;
    effect->pos.y = scale * (from[1] * (1.0f - t) + to[1] * t) + effect->base.y;
    effect->pos.z = scale * (from[2] * (1.0f - t) + to[2] * t) + effect->base.z;
}

// .text:0x14B248 size:0x1AC
void barrelBatter_respawnMachineSpark(MGPathEffect* effect, MGParticle* p) {
    f32 cosA;
    f32 angle;
    f32 radius;
    f32 dx;
    f32 dy;

    p->sizeX = p->sizeY = (f32)barrelBatter_machineSparkParams[3] / 100000.0f;
    p->alphaByte = barrelBatter_machineSparkParams[5];
    angle = 0.017453292f * (f32)(rand() % 360);
    radius = (f32)((u32)rand() % 200 / 1000.0);
    cosA = cos(angle);
    dx = radius * cosA;
    dy = radius * (f32)sin(angle);
    p->origin.x = effect->pos.x + dx;
    p->origin.y = effect->pos.y + dy;
    p->origin.z = effect->pos.z + 0.0f;
    p->life = barrelBatter_machineSparkParams[1];
}

// .text:0x14AC40 size:0x608
int barrelBatter_updateMachineSparks(MGPathEffect* effect) {
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
        barrelBatter_updateMachineSparkPos(effect);
        effect->remaining--;
    }
    sizeStep = 2.0f * ((f32)(barrelBatter_machineSparkParams[4] - barrelBatter_machineSparkParams[3]) / 100000.0f / (f32)barrelBatter_machineSparkParams[1]);
    alphaStep = (barrelBatter_machineSparkParams[6] - barrelBatter_machineSparkParams[5]) / barrelBatter_machineSparkParams[1] * 2;
    do {
        if (p->life != 0) {
            if (p->delay > 0) {
                p->delay--;
                if (p->delay == 0) {
                    barrelBatter_respawnMachineSpark(effect, p);
                }
            } else {
                fn_8003403C(p->sizeX, p->sizeY);
                fn_80033CC8(p, effect->texture);
                alpha = p->alphaByte;
                if (barrelBatter_machineSparkParams[1] / p->life < 2) {
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
                p->sizeX += sizeStep;
                p->sizeY = p->sizeX;
                p->alphaByte = alpha;
                p->life--;
                if (p->life == 0) {
                    barrelBatter_respawnMachineSpark(effect, p);
                }
            }
        }
        p = p->next;
    } while (p != NULL);
    return effect->remaining == 0;
}

// .text:0x14AC1C size:0x24
void barrelBatter_stopMachineSparks(void) {
    pitchingMachinePitching(0x23);
}

// .text:0x14A90C size:0x310
void barrelBatterRel(Vec* pos) {
    MGEffect* effect;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER &&
        pos != NULL) {
        effect = allocParticleEffect(barrelBatter_updateReleaseRing, 0x80, 0, barrelBatter_releaseRingParams[1], TRUE, 0x24);
        if (effect != NULL) {
            barrelBatter_initReleaseRing(effect, pos);
        }
    }
}

// .text:0x14A62C size:0x2E0
void barrelBatterRel2(Vec* pos) {
    MGEffect* effect = allocParticleEffect(barrelBatter_updateReleaseRing, 0x80, 0, barrelBatter_releaseRingParams[1], TRUE, 0x24);

    if (effect != NULL) {
        barrelBatter_initReleaseRing(effect, pos);
    }
}

// .text:0x14A37C size:0x2B0
void barrelBatter_initReleaseRing(MGEffect* effect, Vec* pos) {
    MGParticle* p;
    u32 i = 0;
    f32 angle;

    effect->texture = *(u32*)&animRelated[0x6C];
    p = effect->particles;
    do {
        p->texIndex = barrelBatter_releaseRingParams[0];
        p->_4E = 0;
        p->life = barrelBatter_releaseRingParams[2];
        p->delay = 0;
        p->origin.x = pos->x;
        p->origin.y = -pos->y;
        p->origin.z = pos->z;
        angle = 0.017453292f * (f32)(u32)(360 / barrelBatter_releaseRingParams[1] * i);
        p->origin.x = p->origin.x + (f32)barrelBatter_releaseRingParams[3] * (f32)cos(angle) / 100000.0f;
        p->origin.y = p->origin.y + (f32)barrelBatter_releaseRingParams[3] * (f32)sin(angle) / 100000.0f;
        p->sizeX = p->sizeY = (f32)barrelBatter_releaseRingParams[5] / 100000.0f;
        p->colorR = p->colorG = p->colorB = 0xFF;
        p->alphaByte = barrelBatter_releaseRingParams[9];
        p->velX = 0.0f;
        p->velY = (f32)(barrelBatter_releaseRingParams[12] - rand() % barrelBatter_releaseRingParams[13]);
        p->velY = p->velY / 100000.0f;
        p->velY = p->velY * (f32)(-(rand() % 2 * 2) + 1);
        p->velZ = (f32)(barrelBatter_releaseRingParams[6] - rand() % barrelBatter_releaseRingParams[7]);
        p->velZ = p->velZ / 100000.0f;
        i++;
        p = p->next;
    } while (p != NULL);
}

// .text:0x14A188 size:0x1F4
int barrelBatter_updateReleaseRing(MGEffect* effect) {
    MGParticle* p;
    s32 alpha;
    u32 alive = 0;
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
        if (p->life != 0) {
            alpha = p->alphaByte;
            setParticleXform(p->sizeX, p->sizeY, p->velX);
            fn_80033CC8(p, effect->texture);
            if (barrelBatter_releaseRingParams[2] - p->life < barrelBatter_releaseRingParams[4]) {
                sizeStep = (p->velZ - (f32)barrelBatter_releaseRingParams[5] / 100000.0f) / (f32)barrelBatter_releaseRingParams[4];
                alphaStep = (barrelBatter_releaseRingParams[10] - barrelBatter_releaseRingParams[9]) / barrelBatter_releaseRingParams[4];
            } else {
                remaining = barrelBatter_releaseRingParams[2] - barrelBatter_releaseRingParams[4];
                sizeStep = ((f32)barrelBatter_releaseRingParams[8] / 100000.0f + p->velZ) / (f32)remaining;
                alphaStep = (barrelBatter_releaseRingParams[11] - barrelBatter_releaseRingParams[10]) / remaining;
            }
            alpha += alphaStep;
            if (alpha < 0) {
                alpha = 0;
            }
            if (alpha > 0xFF) {
                alpha = 0xFF;
            }
            p->alphaByte = alpha;
            p->sizeX += sizeStep;
            p->sizeY = p->sizeX;
            p->velX += p->velY;
            if (--p->life != 0) {
                alive++;
            }
        }
        p = p->next;
    } while (p != NULL);
    return alive == 0;
}

// .text:0x14A164 size:0x24
void barrelBatter_stopReleaseRing(void) {
    pitchingMachinePitching(0x24);
}

// .text:0x14A070 size:0xF4
void minigameWinnerStars_setWinners(s32* values, s32 count) {
    u32 i;

    minigameWinnerStars_slots[0] = -1;
    minigameWinnerStars_slots[1] = -1;
    minigameWinnerStars_slots[2] = -1;
    minigameWinnerStars_slots[3] = -1;
    if (count > MG_PLAYER_COUNT || count == 0 || values == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        minigameWinnerStars_slots[i] = values[i];
    }
}

// .text:0x149BA8 size:0x4C8
void minigameWinnerStars_spawn(void) {
    u32 i;
    s8 index;
    MGStarEffect* effect;

    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES && g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD) {
        minigameWinnerStars_params[5] = 930000;
    } else {
        minigameWinnerStars_params[5] = 750000;
    }
    for (i = 0; i < MG_PLAYER_COUNT; i++) {
        index = minigameWinnerStars_slots[i];
        if (index > -1) {
            effect = allocParticleEffect(minigameWinnerStars_update, 0x80, 0, minigameWinnerStars_params[0], TRUE, 0x25);
            if (effect != NULL) {
                effect->index = index;
                minigameWinnerStars_initEffect(effect);
            }
        }
    }
}

// .text:0x14975C size:0x44C
void minigameWinnerStars_spawnOne(s8 index) {
    MGStarEffect* effect = allocParticleEffect(minigameWinnerStars_update, 0x80, 0, minigameWinnerStars_params[0], TRUE, 0x25);

    if (effect != NULL) {
        effect->index = index;
        minigameWinnerStars_initEffect(effect);
    }
}

// .text:0x149340 size:0x41C
void minigameWinnerStars_initEffect(MGStarEffect* effect) {
    MGParticle* p = effect->particles;
    u32 i = 0;
    s32 n;

    do {
        p->life = i;
        p->sizeX = (f32)minigameWinnerStars_params[3] / 100000.0f;
        p->sizeY = (f32)minigameWinnerStars_params[4] / 100000.0f;
        minigameWinnerStars_resetParticle(effect, p);
        n = minigameWinnerStars_params[0] / 5;
        p->delay = (i % 5 * n + rand() % n) * 2;
        i++;
        p = p->next;
    } while (p != NULL);
}

// .text:0x148FD0 size:0x370
void minigameWinnerStars_resetParticle(MGStarEffect* effect, MGParticle* p) {
    f32* actor = *(f32**)(hugeAnimStruct + 0x2C50 + effect->index * 4);
    u8 lo = minigameWinnerStars_params[6];
    s32 base = minigameWinnerStars_params[6];
    u8 range;
    s32 span;

    p->origin.x = 0.0f;
    p->origin.y = -((f32)minigameWinnerStars_params[5] / 100000.0f + actor[0x38 / 4]);
    p->origin.z = 0.0f;
    minigameWinnerStars_getLaunchVelocity(p, 15.0f * ((f32)(minigameWinnerStars_params[0] / 2 - p->life) / ((f32)minigameWinnerStars_params[0] / 2.0f)));
    p->_1C = p->_20 = p->alpha = 0.0f;
    span = (s32)(1000.0f * ((f32)minigameWinnerStars_params[2] / 100000.0f));
    p->_28 = (f32)(rand() % span) / 1000.0f;
    p->_2C = (f32)(rand() % span) / 1000.0f;
    p->_30 = (f32)(rand() % span) / 1000.0f;
    p->_47 = 0xFF;
    p->alphaByte = 0xFF;
    range = 0xFF - base;
    p->colorG = lo + rand() % range;
    p->colorB = lo + rand() % range;
    p->_44 = lo + rand() % range;
    p->_45 = lo + rand() % range;
    p->_46 = lo + rand() % range;
    p->kind = 0;
}

// .text:0x148EF0 size:0xE0
void minigameWinnerStars_getLaunchVelocity(MGParticle* p, f32 degrees) {
    f32 s;
    f32 c;
    f32 angle;

    angle = 0.017453292f * degrees;
    s = sin(angle);
    c = cos(angle);
    p->velX = s * (f32)minigameWinnerStars_params[1] / 100000.0f;
    p->velY = c * (f32)minigameWinnerStars_params[1] / 100000.0f;
    p->velZ = 0.0f;
}

// .text:0x14841C size:0xAD4
int minigameWinnerStars_update(MGStarEffect* effect) {
    MGParticle* p = effect->particles;
    f32* actor = ((f32**)(hugeAnimStruct + 0x2C50))[effect->index];

    minigameWinnerStars_beginDraw();
    do {
        if (p->delay <= 0) {
            minigameWinnerStars_setupMtx(effect, p);
            minigameWinnerStars_drawQuad(p);
            PSVECAdd((Vec*)&p->velX, &p->origin, &p->origin);
            PSVECAdd((Vec*)&p->_28, (Vec*)&p->_1C, (Vec*)&p->_1C);
            if (minigameWinnerStars_rollTurn() != FALSE) {
                Vec ref = { 0.0f, 1.0f, 0.0f };
                Vec dir;
                f32 angle;
                f32 jitter;

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
                minigameWinnerStars_getLaunchVelocity(p, angle);
                p->kind++;
            }
            if (-p->origin.y - p->sizeY < actor[0x38 / 4]) {
                minigameWinnerStars_resetParticle(effect, p);
            }
        } else {
            p->delay--;
        }
        p = p->next;
    } while (p != NULL);
    minigameWinnerStars_endDraw();
    return 0;
}

// .text:0x1483D4 size:0x48
E(u8, BOOL) minigameWinnerStars_rollTurn(void) {
    return rand() % 5 == 0;
}

// .text:0x148254 size:0x180
void minigameWinnerStars_setupMtx(MGStarEffect* effect, MGParticle* p) {
    f32 halfW = p->sizeX / 2.0f;
    f32 halfH = p->sizeY / 2.0f;
    f32* actor = *(f32**)(hugeAnimStruct + 0x2C50 + effect->index * 4);
    f32* v = minigameWinnerStars_quadVerts;
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
    mtx[0][1] = mtx[1][0] = mtx[1][2] = mtx[2][1] = 0.0f;
    mtx[1][1] = 1.0f;
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
void minigameWinnerStars_drawQuad(MGParticle* p) {
    f32* v;
    int i;

    GXSetCullMode(GX_CULL_BACK);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    v = minigameWinnerStars_quadVerts;
    for (i = 0; i < 4; i++) {
        GXWGFifo.f32 = v[i * 3 + 0];
        GXWGFifo.f32 = v[i * 3 + 1];
        GXWGFifo.f32 = v[i * 3 + 2];
        GXWGFifo.u32 = *(u32*)&p->colorR;
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
void minigameWinnerStars_beginDraw(void) {
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
void minigameWinnerStars_endDraw(void) {
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
void minigameStopBombExplosion(void) {
    pitchingMachinePitching(0x25);
}

// .text:0x147CFC size:0x100
void piranhaPanic_spawnBombExplosion(Vec* pos) {
    if (pos != NULL) {
        piranhaPanic_spawnBombExplosionEffect(pos);
    }
}

// .text:0x147C00 size:0xFC
void piranhaPanic_spawnBombExplosionEffect(Vec* pos) {
    MGEffect* existing = fn_800339F0(0, 0x26);
    MGEffect* fresh;
    u8 scratch[0x60];

    if (existing != NULL) {
        fresh = fn_800337CC(scratch, piranhaPanic_bombExplosionParams[2] + piranhaPanic_bombExplosionParams[12], 1);
        if (fresh != NULL) {
            MGParticle* tail;

            piranhaPanic_initBombExplosion(fresh, pos);
            tail = existing->particles;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = fresh->particles;
            existing->count += fresh->count;
        }
    } else {
        fresh = allocParticleEffect(piranhaPanic_updateBombExplosion, 0x80, 0, piranhaPanic_bombExplosionParams[2] + piranhaPanic_bombExplosionParams[12], TRUE, 0x26);
        if (fresh != NULL) {
            piranhaPanic_initBombExplosion(fresh, pos);
        }
    }
}

// .text:0x147778 size:0x488
void piranhaPanic_initBombExplosion(MGEffect* effect, Vec* pos) {
    MGParticle* p;
    u32 burstCount = (u8)piranhaPanic_bombExplosionParams[2];
    u32 ringCount = (u8)piranhaPanic_bombExplosionParams[12];
    u32 i = 0;
    s32 delay = 0;
    f64 angle;

    if (pos->y > 0.0f) {
        pos->y = pos->y * -1.0f;
    }
    effect->texture = *(u32*)&animRelated[0x6C];
    p = effect->particles;
    do {
        if (i < burstCount) {
            p->kind = 1;
            p->velX = (i == 0) ? 3.0f : 1.5f;
            p->life = piranhaPanic_bombExplosionParams[1];
            p->sizeX = p->sizeY = (f32)piranhaPanic_bombExplosionParams[4] / 100000.0f * p->velX;
            p->alphaByte = piranhaPanic_bombExplosionParams[7];
            memcpy(&p->origin, pos, sizeof(Vec));
            if (i != 0) {
                angle = 0.017453292f * (360.0 / (f64)burstCount) * (f64)(i - 1);
                p->origin.x += 1.5f * (f32)cos(angle);
                p->origin.y += 1.5f * (f32)sin(angle);
                p->origin.x = p->origin.x + 0.5 * ((f32)rand() / 32767.0f - 1.0);
                p->origin.y = p->origin.y + 0.5 * ((f32)rand() / 32767.0f - 1.0);
            }
            p->texIndex = piranhaPanic_bombExplosionParams[0];
            p->delay = delay;
        } else {
            p->kind = 2;
            p->life = piranhaPanic_bombExplosionParams[11];
            p->sizeX = p->sizeY = (f32)piranhaPanic_bombExplosionParams[14] / 100000.0f;
            p->alphaByte = piranhaPanic_bombExplosionParams[17];
            memcpy(&p->origin, pos, sizeof(Vec));
            angle = 0.017453292f * (360.0 / (f64)ringCount) * (f64)(u8)(i - burstCount);
            p->origin.x += 2.5f * (f32)cos(angle);
            p->origin.y += 2.5f * (f32)sin(angle);
            p->origin.x = p->origin.x + 0.2f * (2.0 * ((f32)rand() / 32767.0f - 0.5));
            p->origin.y = p->origin.y + 0.2f * (-1.0f * ((f32)rand() / 32767.0f));
            p->texIndex = piranhaPanic_bombExplosionParams[10];
            p->delay = 5;
        }
        p->colorR = p->colorG = p->colorB = 0xFF;
        delay += 2;
        i++;
        p->_4E = 0;
        p = p->next;
    } while (p != NULL);
}

// .text:0x14737C size:0x3FC
int piranhaPanic_updateBombExplosion(MGEffect* effect) {
    s32 rampLength;
    s32 duration;
    MGParticle* p;
    MGParticle** link;
    MGParticle* removedTail;
    u32 alive = 0;
    s32 alpha;
    s32 alphaStep;
    s32 alphaFrom;
    f32 sizeStep;
    f32 scale;

    p = effect->particles = fn_80031F34(effect->particles, effect->count);
    link = &effect->particles;
    removedTail = NULL;
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
    do {
        if (p->life != 0) {
            if (p->delay <= 0) {
                if (p->kind == 1) {
                    rampLength = piranhaPanic_bombExplosionParams[3];
                } else {
                    rampLength = piranhaPanic_bombExplosionParams[13];
                }
                if (p->kind == 1) {
                    duration = piranhaPanic_bombExplosionParams[1];
                } else {
                    duration = piranhaPanic_bombExplosionParams[11];
                }
                if (p->kind == 1) {
                    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_CLEAR);
                } else {
                    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
                }
                fn_8003403C(p->sizeX, p->sizeY);
                fn_80033CC8(p, effect->texture);
                alpha = p->alphaByte;
                if (p->kind == 1) {
                    scale = p->velX;
                } else {
                    scale = 1.0f;
                }
                if (rampLength > duration - p->life) {
                    sizeStep = ((f32)piranhaPanic_bombExplosionParams[5 + mgFxTableRow(p)] / 100000.0f -
                                (f32)piranhaPanic_bombExplosionParams[4 + mgFxTableRow(p)] / 100000.0f) /
                               (f32)rampLength * scale;
                    alphaFrom = piranhaPanic_bombExplosionParams[7 + mgFxTableRow(p)];
                    alphaStep = (piranhaPanic_bombExplosionParams[8 + mgFxTableRow(p)] - alphaFrom) / rampLength;
                } else {
                    sizeStep = ((f32)piranhaPanic_bombExplosionParams[6 + mgFxTableRow(p)] / 100000.0f -
                                (f32)piranhaPanic_bombExplosionParams[5 + mgFxTableRow(p)] / 100000.0f) /
                               (f32)(duration - rampLength) * scale;
                    alphaFrom = piranhaPanic_bombExplosionParams[8 + mgFxTableRow(p)];
                    alphaStep = (piranhaPanic_bombExplosionParams[9 + mgFxTableRow(p)] - alphaFrom) / (duration - rampLength);
                }
                alpha += alphaStep;
                if (alpha < 0) {
                    alpha = 0;
                } else if (alpha > 0xFF) {
                    alpha = 0xFF;
                }
                p->sizeY = p->sizeX += sizeStep;
                p->alphaByte = alpha;
                p->origin.y -= (p->kind == 1) ? 0.0f : 0.05f;
                p->life--;
                if (p->life == 0) {
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
                p->delay--;
                link = &p->next;
                alive++;
            }
        }
        p = *link;
    } while (p != NULL);
    return alive == 0;
}

// .text:0x147358 size:0x24
void minigameStopBombExplosion2(void) {
    pitchingMachinePitching(0x26);
}
