#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_rep_3880
#define g_Minigame g_Minigame_shared
#include "game/minigame/rep_3880.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/minigame/star_dash.h"
#include "game/minigame/piranha_panic.h"
#include "game/minigame/pitching_machine.h"
#include "game/math/game_math.h"
#include "game/sound/m_sound.h"
#include "game/stadium/stadium_framework.h"
#include "game/stadium/sta_c2.h"
#include "game/hud/rep_3448.h"
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



static inline void mgStarSparkPlace(MGParticle* p) {
    Vec v = { 0.0f, 0.0f, 0.0f };
    Vec offset;

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
    if (p->_4C < 5) {
        offset.z = 0.0f;
        offset.y = 0.0f;
        offset.x = 0.0f;
        if (!getAnimationCollisionOffset(p->_4C - 1, lbl_3_data_26CB8[(u32)rand() % 23], &offset)) {
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
    if (g_Minigame._1A40 != 0) {
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
void fn_3_14EAF4(void) {
    return;
}

// .text:0x14E9F0 size:0x104
void fn_3_14E9F0(void) {
    return;
}

// .text:0x14E988 size:0x68
void fn_3_14E988(void) {
    return;
}

// .text:0x14E920 size:0x68
void fn_3_14E920(void) {
    return;
}

// .text:0x14E894 size:0x8C
void fn_3_14E894(void) {
    return;
}

// .text:0x14E810 size:0x84
void fn_3_14E810(void) {
    return;
}

// .text:0x14E7C0 size:0x50
void fn_3_14E7C0(void) {
    return;
}

// .text:0x14E234 size:0x58C
void fn_3_14E234(void) {
    return;
}

// .text:0x14DF6C size:0x2C8
void fn_3_14DF6C(void) {
    return;
}

// .text:0x14DD04 size:0x268
void fn_3_14DD04(void) {
    return;
}

// .text:0x14DCE0 size:0x24
void fn_3_14DCE0(void) {
    return;
}

// .text:0x14DC80 size:0x60
void fn_3_14DC80(void) {
    return;
}

// .text:0x14D710 size:0x570
void fn_3_14D710(void) {
    return;
}

// .text:0x14D6D4 size:0x3C
void fn_3_14D6D4(void) {
    return;
}

// .text:0x14D44C size:0x288
void fn_3_14D44C(void) {
    return;
}

// .text:0x14D318 size:0x134
void fn_3_14D318(void) {
    return;
}

// .text:0x14D2C0 size:0x58
void fn_3_14D2C0(void) {
    return;
}

// .text:0x14CECC size:0x3F4
void fn_3_14CECC(void) {
    return;
}

// .text:0x14CD40 size:0x18C
void fn_3_14CD40(void) {
    return;
}

// .text:0x14CBB4 size:0x18C
void fn_3_14CBB4(void) {
    return;
}

// .text:0x14CB28 size:0x8C
void fn_3_14CB28(void) {
    return;
}

// .text:0x14CAB4 size:0x74
void fn_3_14CAB4(void) {
    return;
}

// .text:0x14CA98 size:0x1C
void fn_3_14CA98(void) {
    return;
}

// .text:0x14CA00 size:0x98
void fn_3_14CA00(void) {
    return;
}

// .text:0x14C904 size:0xFC
void fn_3_14C904(void) {
    return;
}

// .text:0x14C830 size:0xD4
void fn_3_14C830(void) {
    return;
}

// .text:0x14C79C size:0x94
void fn_3_14C79C(void) {
    return;
}

// .text:0x14C4C8 size:0x2D4
void fn_3_14C4C8(void) {
    return;
}

// .text:0x14C3BC size:0x10C
void fn_3_14C3BC(void) {
    return;
}

// .text:0x14C398 size:0x24
void fn_3_14C398(void) {
    return;
}

// .text:0x14C348 size:0x50
void fn_3_14C348(void) {
    return;
}

// .text:0x14BECC size:0x47C
void fn_3_14BECC(void) {
    return;
}

// .text:0x14BCB0 size:0x21C
void fn_3_14BCB0(void) {
    return;
}

// .text:0x14BA40 size:0x270
void fn_3_14BA40(void) {
    return;
}

// .text:0x14B9F0 size:0x50
void fn_3_14B9F0(void) {
    return;
}

// .text:0x14B9A0 size:0x50
void fn_3_14B9A0(void) {
    return;
}

// .text:0x14B92C size:0x74
void fn_3_14B92C(void) {
    return;
}

// .text:0x14B53C size:0x3F0
void fn_3_14B53C(void) {
    return;
}

// .text:0x14B3F4 size:0x148
void fn_3_14B3F4(void) {
    return;
}

// .text:0x14B248 size:0x1AC
void fn_3_14B248(void) {
    return;
}

// .text:0x14AC40 size:0x608
void fn_3_14AC40(void) {
    return;
}

// .text:0x14AC1C size:0x24
void fn_3_14AC1C(void) {
    return;
}

// .text:0x14A90C size:0x310
void barrelBatterRel(void) {
    return;
}

// .text:0x14A62C size:0x2E0
void fn_3_14A62C(void) {
    return;
}

// .text:0x14A37C size:0x2B0
void fn_3_14A37C(void) {
    return;
}

// .text:0x14A188 size:0x1F4
void fn_3_14A188(void) {
    return;
}

// .text:0x14A164 size:0x24
void fn_3_14A164(void) {
    return;
}

// .text:0x14A070 size:0xF4
void fn_3_14A070(void) {
    return;
}

// .text:0x149BA8 size:0x4C8
void fn_3_149BA8(void) {
    return;
}

// .text:0x14975C size:0x44C
void fn_3_14975C(void) {
    return;
}

// .text:0x149340 size:0x41C
void fn_3_149340(void) {
    return;
}

// .text:0x148FD0 size:0x370
void fn_3_148FD0(void) {
    return;
}

// .text:0x148EF0 size:0xE0
void fn_3_148EF0(void) {
    return;
}

// .text:0x14841C size:0xAD4
void fn_3_14841C(void) {
    return;
}

// .text:0x1483D4 size:0x48
void fn_3_1483D4(void) {
    return;
}

// .text:0x148254 size:0x180
void fn_3_148254(void) {
    return;
}

// .text:0x1480E0 size:0x174
void fn_3_1480E0(void) {
    return;
}

// .text:0x147F94 size:0x14C
void fn_3_147F94(void) {
    return;
}

// .text:0x147E20 size:0x174
void fn_3_147E20(void) {
    return;
}

// .text:0x147DFC size:0x24
void fn_3_147DFC(void) {
    return;
}

// .text:0x147CFC size:0x100
void fn_3_147CFC(void) {
    return;
}

// .text:0x147C00 size:0xFC
void fn_3_147C00(void) {
    return;
}

// .text:0x147778 size:0x488
void fn_3_147778(void) {
    return;
}

// .text:0x14737C size:0x3FC
void fn_3_14737C(void) {
    return;
}

// .text:0x147358 size:0x24
void fn_3_147358(void) {
    return;
}
