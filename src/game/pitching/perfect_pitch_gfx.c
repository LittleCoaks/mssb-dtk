#include "game/pitching/perfect_pitch_gfx.h"
#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_perfect_pitch_gfx
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/batting/charge_effects.h"
#include "game/batting/star_swing_peach_daisy.h"
#include "game/stadium/stadium_framework.h"
#include "C3/actor.h"
#include "Dolphin/mtx.h"
#include "Dolphin/stl.h"
#include "stl/math.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x8005268c.h"
#include "Unknown/File_0x80052734.h"
#include "Unknown/File_0x800b4bc8.h"
#include "Unknown/File_0x800bda94.h"

// The perfect-pitch trail model: a stadium model whose root actor is driven
// by ACTSetAnimation.
typedef struct _PerfectPitchModel {
    /*0x00*/ u8* root;
    /*0x04*/ void* animBank;
    /*0x08*/ u8 _08[0xE - 0x8];
    /*0x0E*/ u16 sequenceNum;
    /*0x10*/ u8 _10[0x60 - 0x10];
    /*0x60*/ f32 animTime;
} PerfectPitchModel;

// Per-camera-slot drawing entry.
typedef struct _PerfectPitchEntry {
    /*0x00*/ u32 _00;
    /*0x04*/ u32 _04;
    /*0x08*/ VecXYZ pos;
    /*0x14*/ Quaternion rot;
    /*0x24*/ u32 frame;
} PerfectPitchEntry;

// DrawingSceneStruct view: +0x14.. is scratch owned by fn_3_CAE00.
typedef struct _PerfectPitchNode {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ VecXYZ pos;
    /*0x20*/ Quaternion rot;
    /*0x30*/ u16 frame;
    /*0x32*/ u8 slot;
    /*0x33*/ u8 actorIndex;
    /*0x34*/ E(u8, BOOL) stop;
} PerfectPitchNode;

typedef struct _PerfectPitchActor {
    /*0x00*/ u8 _00[0x34];
    /*0x34*/ VecXYZ pos;
} PerfectPitchActor;

typedef struct _PerfectPitchState {
    /*0x00*/ f32 unk0;
    /*0x04*/ f32 frame;
    /*0x08*/ u8 _08[4];
    /*0x0C*/ s16 unkC;
    /*0x0E*/ u8 _0E[0x18 - 0xE];
    /*0x18*/ u16 trailFrames;
    /*0x1A*/ u8 _1A[0x20 - 0x1A];
    /*0x20*/ void* handle;
    /*0x24*/ u8 _24[0x5C - 0x24];
} PerfectPitchState;

// The part of the shared effects block (lbl_3_common_bss_35154, used by ~30 units) that this
// unit touches.
typedef struct _PerfectPitchSharedBlock {
    /*0x000*/ u8 _000[0x10];
    /*0x010*/ u8* trailOwner;
    /*0x014*/ u8 _014[0xD8 - 0x14];
    /*0x0D8*/ PerfectPitchState states[3];
    /*0x1EC*/ u8 _1EC[0x3AC - 0x1EC];
    /*0x3AC*/ u32 flags;
    /*0x3B0*/ u8 _3B0[0x428 - 0x3B0];
    /*0x428*/ VecXYZ starHitPos;
    /*0x434*/ u8 _434[0x467 - 0x434];
    /*0x467*/ s8 starHitPitch;
    /*0x468*/ u8 _468[0x480 - 0x468];
} PerfectPitchSharedBlock;

extern PerfectPitchSharedBlock lbl_3_common_bss_35154;
extern struct {
    /*0x0000*/ u8 _0000[0x2C50];
    /*0x2C50*/ PerfectPitchActor* actors[(0x3154 - 0x2C50) / 4];
} hugeAnimStruct;
extern u8 drawStadiumRelated;
extern struct {
    u8 _00[0x28];
    u8 _28;
} lbl_80366158;

extern int lbl_3_data_17D08[2];
extern PerfectPitchNode* lbl_3_data_17D10[2];
extern PerfectPitchEntry lbl_3_data_17D18[2][2];

extern void fn_800A7D4C(s32 arg0, void* arg1);
extern void fn_800BDA24(void* arg);

// .text:0x000CB344 size:0x68
void fn_3_CB344(int actorIndex, int starType) {
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES
        || (g_Minigame.GameMode_MiniGame != MINI_GAME_ID_BOBOMB_DERBY
            && g_Minigame.GameMode_MiniGame != MINI_GAME_ID_BARREL_BATTER)) {
        maybeConfigureChargeEffectGraphics(actorIndex);
    }
    lbl_3_common_bss_35154.starHitPitch = starType;
}

// .text:0x000CB284 size:0xC0 mapped:0x8070A318
void fn_3_CB284(int actorIndex, int frame, f32 charge) {
    PerfectPitchActor* actor;

    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES
        || (g_Minigame.GameMode_MiniGame != MINI_GAME_ID_BOBOMB_DERBY
            && g_Minigame.GameMode_MiniGame != MINI_GAME_ID_BARREL_BATTER)) {
        if (lbl_3_common_bss_35154.starHitPitch != 0 && frame == 0x23) {
            actor = hugeAnimStruct.actors[actorIndex];
            lbl_3_common_bss_35154.starHitPos.x = actor->pos.x;
            lbl_3_common_bss_35154.starHitPos.y = -actor->pos.y;
            lbl_3_common_bss_35154.starHitPos.z = actor->pos.z;
            lbl_3_common_bss_35154.flags |= 0x10;
        }
        applyChargeAnimationEffect(actorIndex, 100.0f * charge, 100.0f, frame == 0x1E);
    }
}

// .text:0x000CB234 size:0x50 mapped:0x8070A2C8
void fn_3_CB234(int actorIndex, BOOL immediate) {
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES
        || (g_Minigame.GameMode_MiniGame != MINI_GAME_ID_BOBOMB_DERBY
            && g_Minigame.GameMode_MiniGame != MINI_GAME_ID_BARREL_BATTER)) {
        fn_3_C11CC(actorIndex, immediate);
    }
}

// .text:0x000CB1B0 size:0x84 mapped:0x8070A244
void fn_3_CB1B0(int actorIndex, u8 pitch, int frame) {
    PerfectPitchActor* actor;

    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES
        || (g_Minigame.GameMode_MiniGame != MINI_GAME_ID_BOBOMB_DERBY
            && g_Minigame.GameMode_MiniGame != MINI_GAME_ID_BARREL_BATTER)) {
        if (frame == 0x23) {
            lbl_3_common_bss_35154.starHitPitch = pitch;
            actor = hugeAnimStruct.actors[actorIndex];
            lbl_3_common_bss_35154.starHitPos.x = actor->pos.x;
            lbl_3_common_bss_35154.starHitPos.y = -actor->pos.y;
            lbl_3_common_bss_35154.starHitPos.z = actor->pos.z;
            lbl_3_common_bss_35154.flags |= 0x10;
        }
    }
}

// .text:0x000CAF9C size:0x214 mapped:0x8070A030
void perfectPitchGraphicsRelated(void) {
    VecXYZ pos;
    VecXYZ vel;
    VecXYZ accel;
    PerfectPitchNode* node;
    int count;
    int i;

    node = (PerfectPitchNode*)insertGraphicDrawingFunction(fn_3_CAE00, 1);
    node->frame = 0;
    node->actorIndex = g_Pitcher.rosterID;
    memcpy(&pos, &g_Pitcher.ballCurrentPosition, sizeof(VecXYZ));
    memcpy(&vel, &g_Pitcher.ballVelocity, sizeof(VecXYZ));
    memcpy(&accel, &g_Pitcher.pitchCurveVeloV1, sizeof(VecXYZ));
    count = lbl_3_data_17D08[1];
    while (count-- != 0) {
        peachDaisyStarPitch_stepPhysics(&pos, &vel, &accel, FALSE);
    }
    node->pos.x = pos.x;
    node->pos.y = -pos.y;
    node->pos.z = pos.z;
    pos.x -= g_Pitcher.ballCurrentPosition.x;
    pos.y -= g_Pitcher.ballCurrentPosition.y;
    pos.z -= g_Pitcher.ballCurrentPosition.z;
    pos.y = -pos.y;
    PSVECNormalize((Vec*)&pos, (Vec*)&pos);
    vel.x = -1.0f;
    vel.y = 0.0f;
    vel.z = 0.0f;
    PSVECCrossProduct((Vec*)&vel, (Vec*)&pos, (Vec*)&node->rot);
    node->rot.w = acos(PSVECDotProduct((Vec*)&vel, (Vec*)&pos)) / 2.0;
    if (PSVECMag((Vec*)&node->rot)) {
        PSVECNormalize((Vec*)&node->rot, (Vec*)&node->rot);
        PSVECScale((Vec*)&node->rot, sin(node->rot.w), (Vec*)&node->rot);
    }
    node->rot.w = cos(node->rot.w);
    node->stop = i = 0;
    for (; i < ARRAY_SIZE(lbl_3_data_17D10); i++) {
        if (lbl_3_data_17D10[i] == NULL) {
            lbl_3_data_17D10[i] = node;
            node->slot = i;
            break;
        }
    }
}

// .text:0x000CAE00 size:0x19C mapped:0x80709E94
void fn_3_CAE00(void) {
    PerfectPitchNode* node = (PerfectPitchNode*)currentDrawingItem;
    PerfectPitchActor* actor = hugeAnimStruct.actors[node->actorIndex];

    if (node->stop == FALSE && actor != NULL) {
        fn_800A7D4C(0, &lbl_3_data_17D18[node->slot][drawStadiumRelated]);
        lbl_3_data_17D18[node->slot][drawStadiumRelated].frame = node->frame;
        lbl_3_data_17D18[node->slot][drawStadiumRelated].pos.x = node->pos.x;
        lbl_3_data_17D18[node->slot][drawStadiumRelated].pos.y = node->pos.y;
        lbl_3_data_17D18[node->slot][drawStadiumRelated].pos.z = node->pos.z;
        lbl_3_data_17D18[node->slot][drawStadiumRelated].rot = node->rot;
        if (lbl_80366158._28 == 0) {
            node->frame++;
        }
    } else {
        lbl_3_data_17D10[node->slot] = NULL;
        removeCurrentDrawingItem();
    }
    if (node->frame >= lbl_3_common_bss_35154.states[0].trailFrames) {
        lbl_3_data_17D10[node->slot] = NULL;
        removeCurrentDrawingItem();
    }
}

// .text:0x000CABF0 size:0x210 mapped:0x80709C84
void fn_3_CABF0(PerfectPitchTrail* trail) {
    Mtx mtx;
    void* handles[3];
    PerfectPitchState* states[3];
    PerfectPitchModel* model;
    f32 scale;
    int i;
    PerfectPitchState** state;
    void** handle;

    scale = lbl_3_data_17D08[0] / 100000.0f;
    for (i = 0; i < 3; i++) {
        handles[i] = lbl_3_common_bss_35154.states[i].handle;
        states[i] = &lbl_3_common_bss_35154.states[i];
    }
    model = (PerfectPitchModel*)(lbl_3_common_bss_35154.trailOwner + 0xC4);

    PSMTXQuat(mtx, &trail->rot);
    PSMTXScaleApply(mtx, mtx, scale, scale, scale);
    PSMTXTransApply(mtx, mtx, trail->pos.x, trail->pos.y, trail->pos.z);
    PSMTXConcat(returnFloatFromModeIndex(returnsCurrentMode())->view, mtx, mtx);

    state = &states[2];
    handle = &handles[2];
    i = 2;
    do {
        (*state)->unk0 = 0.0f;
        (*state)->unkC = 0;
        (*state)->frame = trail->frame;
        fn_80024DB0((u8*)*state);
        fn_80024FA4((StadiumModel*)model, *handle, (u8*)*state, -1);
        state--;
        handle--;
    } while (i-- != 0);

    model->root[0x99] = 1;
    ACTSetAnimation((Actor*)model->root, model->animBank, NULL, model->sequenceNum, 0.0f, model->animTime);
    setActorAnimFrame(model->root, trail->frame);
    fn_800B4C04(model->root, 1.0f);
    fn_800BDA24(model);
    model->root[0x98] = 0xFF;
    sknRelated(model, mtx);
}

// .text:0x000CABB4 size:0x3C
void fn_3_CABB4(void) {
    if (lbl_3_data_17D10[0] != NULL) {
        lbl_3_data_17D10[0]->stop = TRUE;
    }
    if (lbl_3_data_17D10[1] != NULL) {
        lbl_3_data_17D10[1]->stop = TRUE;
    }
}
