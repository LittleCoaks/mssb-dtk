#include "game/ball/ball_visuals.h"

/* ball_visuals.c never calls dolsqrtf2(), so keep it internal. With the
 * header's default `extern` linkage MWCC materialises the unused out-of-line
 * copy's _half/_three local statics in this TU's .rodata, pushing every
 * constant-pool entry past the offsets the linked module actually has. */
#define SQRT2_LINKAGE static
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/mtx.h"
#include "Dolphin/gx.h"
#include "Dolphin/os.h"
#include "Dolphin/stl.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x80052734.h"
#include "stl/math.h"
#include "game/math/game_math.h"
#include "game/ball/collision_primitives.h"
#include "game/stadium/stadium_framework.h"

extern void setScissorAndProjection(int);
extern void SetDisplayStateTexture(void* texture, int arg1, int arg2);
extern void fn_800A7D4C(s32 arg0, void* arg1);
extern void fn_80023EEC(void* list, Vec* buffer, s32 capacity);
extern void fn_80023E48(void* list, Vec* point);
extern void fn_80023D4C(void* list, Vec* out);
extern BOOL fn_80023DFC(void* list, Vec* out);
extern BOOL fn_80023D98(void* list, Vec* out);

extern u8 drawStadiumRelated;
extern u8 lbl_80366158[0x30];
extern u8 animRelated[0x124];
extern u8 pauseControl[0x264];
extern u8 characterStaticIndexes[0x144];
extern f32 lbl_803CB740[];
extern f32 ballScaleFactors[13][3];
extern void displayChem_antiChemGraphics(int fielder, BOOL anti);
extern void baseballCTRLSetScale(f32 x, f32 y, f32 z, int model);
extern void applyUniformScaleToObject(f32 scale, int model);

// The part of the shared effects block (lbl_3_common_bss_35154) this unit reads.
extern struct {
    /*0x000*/ u8 _000[4];
    /*0x004*/ TextureHeader* textures;
    /*0x008*/ u8 _008[0x47A - 0x8];
    /*0x47A*/ u16 garlicSplitFrames[2];
} lbl_3_common_bss_35154;

// One entry of the ball trail table, indexed by trail type. `texture` holds a
// record index into the game texture container until fn_3_6750C resolves it.
typedef struct TrailDef {
    /*0x0*/ TextureRecord* texture;
    /*0x4*/ f32 width;
    /*0x8*/ f32 widthRatio;
    /*0xC*/ s32 length;
} TrailDef;

// One indexed GX mesh: display list plus the vertex arrays it indexes.
typedef struct TrailMesh {
    /*0x00*/ void* displayList;
    /*0x04*/ u32 displayListSize;
    /*0x08*/ Vec* positions;
    /*0x0C*/ void* texCoords;
    /*0x10*/ u32* colors;
} TrailMesh;

typedef struct TrailDrawRecord {
    /*0x0*/ u32 _0;
    /*0x4*/ void (*draw)(void*);
    /*0x8*/ TrailMesh* meshes[2];
} TrailDrawRecord;

typedef struct TrailPointList {
    /*0x00*/ u8 _00[8];
    /*0x08*/ s32 count;
    /*0x0C*/ u8 _0C[0x1C - 0xC];
} TrailPointList;

typedef struct TrailDrawNode {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ Vec* direction;
    /*0x18*/ Vec directionStorage;
} TrailDrawNode;

// One entry of the hugeAnimStruct ball model table at +0x2D90.
typedef struct BallModel {
    /*0x00*/ u8 _00[4];
    /*0x04*/ Vec pos;
    /*0x10*/ Vec rot;
    /*0x1C*/ u8 _1C[0x26 - 0x1C];
    /*0x26*/ E(u8, BOOL) visible;
    /*0x27*/ u8 _27;
} BallModel; // size 0x28

// This unit's view of hugeAnimStruct.
extern struct {
    /*0x0000*/ u8 _0000[0x2D90];
    /*0x2D90*/ BallModel* ballModels;
    /*0x2D94*/ BallModel* bombModels;
} hugeAnimStruct;

void fn_3_67C34(void* arg);
s32 fn_3_67EF0(TrailPointList* list, s32 capacity, Vec* positions, u32* colors, u32 color, f32 width,
               Vec* capPositions, u32* capColors, Vec* direction);

static u8 starBallOffsets[16] = { 0x00, 0x00, 0x00, 0x0C, 0x0D, 0x07, 0x07, 0x0A, 0x0B, 0x08, 0x09 };
static f32 lbl_3_data_6830[2] = { 2.5f, 5.0f };
static f32 lbl_3_data_6838[2] = { 0.6f, 0.6f };
static f32 lbl_3_data_6840[2] = { 0.3f, 1.0f };
static f32 lbl_3_data_6848[2] = { -0.1f, 1.0f };
static u16 lbl_3_data_6860[8][2] ATTRIBUTE_ALIGN(32) = {
    { 0x0000, 0x4000 }, { 0x4000, 0x4000 }, { 0x0000, 0x2000 }, { 0x4000, 0x2000 },
    { 0x0000, 0x1000 }, { 0x4000, 0x1000 }, { 0x0000, 0x0800 }, { 0x4000, 0x0800 },
};
static TrailDef lbl_3_data_6880[12] = {
    { (TextureRecord*)0x00, 0.1f, 0.1f, 60 },  { (TextureRecord*)0x0A, 0.2f, 0.2f, 30 },
    { (TextureRecord*)0x0B, 0.4f, 0.4f, 60 },  { (TextureRecord*)0x0A, 0.3f, 0.3f, 50 },
    { (TextureRecord*)0x0B, 0.5f, 0.5f, 100 }, { (TextureRecord*)0x0B, 1.0f, 1.0f, 100 },
    { (TextureRecord*)0x17, 0.4f, 0.4f, 100 }, { (TextureRecord*)0x17, 1.0f, 1.0f, 100 },
    { (TextureRecord*)0x1E, 0.3f, 0.3f, 50 },  { (TextureRecord*)0x1F, 0.3f, 0.3f, 50 },
    { (TextureRecord*)0x21, 0.4f, 0.4f, 60 },  { (TextureRecord*)0x21, 0.4f, 0.4f, 60 },
};
static u8 lbl_3_data_6940[54] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x05, 0x00,
    0x00, 0x03, 0x06, 0x03, 0x00, 0x01, 0x00, 0x02, 0x01, 0x00, 0x03, 0x03, 0x06, 0x01, 0x02, 0x03,
    0x04, 0x01, 0x00, 0x03, 0x02, 0x05, 0x00, 0x06, 0x06, 0x06, 0x00, 0x03, 0x01, 0x02, 0x03, 0x06,
    0x05, 0x03, 0x00, 0x01, 0x00, 0x01,
};
static u8 lbl_3_data_6980[32] ATTRIBUTE_ALIGN(32) = {
    GX_QUADS, 0x00, 0x08,
    0x00, 0x00, 0x00,
    0x01, 0x00, 0x01,
    0x03, 0x00, 0x03,
    0x02, 0x00, 0x02,
    0x02, 0x01, 0x02,
    0x03, 0x01, 0x03,
    0x05, 0x02, 0x01,
    0x04, 0x02, 0x00,
};
static TrailDrawRecord lbl_3_data_69A0[2] = {
    { 0, fn_3_67C34 },
    { 0, fn_3_67C34 },
};

static f32 lbl_3_bss_16A8;
static f32 lbl_3_bss_16A4;
static s32 lbl_3_bss_16A0;
static s32 lbl_3_bss_169C;
static TrailMesh lbl_3_bss_164C[2][2];
static TrailPointList lbl_3_bss_1630;
static Vec lbl_3_bss_1360[60] ATTRIBUTE_ALIGN(32);
static u8 lbl_3_bss_11E0[0x180] ATTRIBUTE_ALIGN(32);
static u8 lbl_3_bss_1060[0x180] ATTRIBUTE_ALIGN(32);
static Vec lbl_3_bss_520[2][120] ATTRIBUTE_ALIGN(32);
static u32 lbl_3_bss_320[2][64] ATTRIBUTE_ALIGN(32);
static Vec lbl_3_bss_260[2][8] ATTRIBUTE_ALIGN(32);
static u32 lbl_3_bss_220[2][8] ATTRIBUTE_ALIGN(32);
static s32 lbl_3_bss_20C;
static s32 lbl_3_bss_208;
static TextureRecord* lbl_3_bss_204;
static s32 lbl_3_bss_200;

static inline void stopBallTrail(void) {
    animRelated[0xCC] = 0;
    lbl_3_bss_16A8 = 0.0f;
}

#define BALL_SPIN g_Ball.matchFramesAndBallAngle.ballSpinAngle

// .text:0x000697CC size:0x994 mapped:0x806A8860
void ballAnimations(void) {
    BallModel* model;
    BallModel* garlicModel;
    s32 garlicIndex;
    s32 garlicScaleCode;
    s32 scene;
    s32 show;
    BOOL isWaluigi;
    s32 index;
    f32 scale;
    Vec avg;

    garlicModel = NULL;
    hugeAnimStruct.ballModels[0].visible = FALSE;
    hugeAnimStruct.ballModels[7].visible = FALSE;
    hugeAnimStruct.ballModels[8].visible = FALSE;
    hugeAnimStruct.ballModels[9].visible = FALSE;
    hugeAnimStruct.ballModels[10].visible = FALSE;
    hugeAnimStruct.ballModels[11].visible = FALSE;
    hugeAnimStruct.ballModels[12].visible = FALSE;
    hugeAnimStruct.ballModels[13].visible = FALSE;
    hugeAnimStruct.ballModels[14].visible = FALSE;
    hugeAnimStruct.ballModels[15].visible = FALSE;
    hugeAnimStruct.ballModels[16].visible = FALSE;
    hugeAnimStruct.ballModels[1].visible = FALSE;
    hugeAnimStruct.ballModels[2].visible = FALSE;
    hugeAnimStruct.ballModels[3].visible = FALSE;
    animRelated[0xCB] = CAPTAIN_STAR_TYPE_NONE;
    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_CHAINCHOMP_SPRINT ||
        g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PIRANHA_PANIC ||
        g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_STAR_DASH) {
        return;
    }
    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER && g_Minigame.barrelBatter_scoreCalculatedInd) {
        return;
    }
    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_BASERUNNING) {
        return;
    }

    if ((g_GameLogic.gameStatus == GAME_STATUS_AT_BAT && g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_WARIO) ||
        (!g_Ball.warioWaluGarlicIsActive && g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL &&
         g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_WARIO)) {
        animRelated[0xCB] = CAPTAIN_STAR_TYPE_WARIO;
    }
    if ((g_GameLogic.gameStatus == GAME_STATUS_AT_BAT && g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_WALUIGI) ||
        (!g_Ball.warioWaluGarlicIsActive && g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL &&
         g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_WALUIGI)) {
        animRelated[0xCB] = CAPTAIN_STAR_TYPE_WALUIGI;
    }
    if ((g_GameLogic.gameStatus == GAME_STATUS_AT_BAT && g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_DK) ||
        (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL && g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_DK)) {
        animRelated[0xCB] = CAPTAIN_STAR_TYPE_DK;
    }
    if ((g_GameLogic.gameStatus == GAME_STATUS_AT_BAT && g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_DIDDY) ||
        (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL && g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_DIDDY)) {
        animRelated[0xCB] = CAPTAIN_STAR_TYPE_DIDDY;
    }
    if ((g_GameLogic.gameStatus == GAME_STATUS_AT_BAT && g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_BOWSER) ||
        (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL && g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_BOWSER)) {
        animRelated[0xCB] = CAPTAIN_STAR_TYPE_BOWSER;
    }
    if ((g_GameLogic.gameStatus == GAME_STATUS_AT_BAT && g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_BOWSERJR) ||
        (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL && g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_BOWSERJR)) {
        animRelated[0xCB] = CAPTAIN_STAR_TYPE_BOWSERJR;
    }
    if ((g_GameLogic.gameStatus == GAME_STATUS_AT_BAT && g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_YOSHI) ||
        (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL && g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_YOSHI)) {
        animRelated[0xCB] = CAPTAIN_STAR_TYPE_YOSHI;
    }
    if ((g_GameLogic.gameStatus == GAME_STATUS_AT_BAT && g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_BIRDO) ||
        (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL && g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_BIRDO)) {
        animRelated[0xCB] = CAPTAIN_STAR_TYPE_BIRDO;
    }

    model = &hugeAnimStruct.ballModels[starBallOffsets[animRelated[0xCB]]];
    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY) {
        if (g_Minigame.bOD_KingBombInd) {
            model = &hugeAnimStruct.bombModels[1];
        } else {
            model = &hugeAnimStruct.bombModels[0];
        }
        hugeAnimStruct.bombModels[0].visible = FALSE;
        hugeAnimStruct.bombModels[1].visible = FALSE;
    }
    ballSpinSetting();
    model->pos.x = g_Ball.AtBat_Contact_BallPos.x;
    model->pos.y = -g_Ball.AtBat_Contact_BallPos.y;
    model->pos.z = g_Ball.AtBat_Contact_BallPos.z;
    model->rot.x = shortAngleToRad_Capped(BALL_SPIN.yaw);
    model->rot.y = shortAngleToRad_Capped(BALL_SPIN.pitch);
    model->rot.z = shortAngleToRad_Capped(BALL_SPIN.roll);
    if (g_Ball.warioWaluGarlicIsActive) {
        index = 14;
        isWaluigi = g_Ball.currentStarSwing != CAPTAIN_STAR_TYPE_WARIO;
        if (g_Ball.framesUntilBallHitsGround <= lbl_3_common_bss_35154.garlicSplitFrames[isWaluigi != FALSE]) {
            index = isWaluigi + 15;
        }
        garlicIndex = index;
        garlicModel = &hugeAnimStruct.ballModels[index];
        garlicModel->pos.x = g_Ball.warioStarHitCoords[2].x;
        garlicModel->pos.y = -g_Ball.warioStarHitCoords[2].y;
        garlicModel->pos.z = g_Ball.warioStarHitCoords[2].z;
        garlicModel->visible = TRUE;
        garlicModel->rot.x = model->rot.x;
        garlicModel->rot.y = model->rot.y;
        garlicModel->rot.z = model->rot.z;
    } else if (g_Pitcher.warioWaluStarAnimationStage == 1 && (g_Pitcher.pitchTotalTimeCounter & 1)) {
        model->pos.x = (g_Pitcher.ballCurrentPosition.x + g_Pitcher.pitchX_parabolicAdjustment) -
                       g_Pitcher.starPitchPositionAdjustment.x;
    }
    if (g_Ball.fielderActionOccuring) {
        model->pos.x = g_Ball.fielderActionCatchCoords.x;
        model->pos.y = -g_Ball.fielderActionCatchCoords.y;
        model->pos.z = g_Ball.fielderActionCatchCoords.z;
    }
    if (g_Ball.hitNoteBlockInd) {
        model->pos.x = stadiumObjectCollision.hitBallPos.x;
        model->pos.y = stadiumObjectCollision.hitBallPos.y;
        model->pos.z = stadiumObjectCollision.hitBallPos.z;
    }

    show = 0;
    if (g_Ball.ballState != BALL_STATE_HELD) {
        show = 1;
    } else if (g_Ball.fielderWBallIndex >= 0 &&
               characterStaticIndexes[g_Fielders[g_Ball.fielderWBallIndex].CharID * 6 + 1] == CHAR_ID_MAGIKOOPA_BLUE) {
        show = 2;
        avg.x = g_Ball.offsetWhilePickedUpHistory[1].x;
        avg.y = g_Ball.offsetWhilePickedUpHistory[1].y;
        avg.z = g_Ball.offsetWhilePickedUpHistory[1].z;
        avg.x += g_Ball.offsetWhilePickedUpHistory[2].x;
        avg.y += g_Ball.offsetWhilePickedUpHistory[2].y;
        avg.z += g_Ball.offsetWhilePickedUpHistory[2].z;
        avg.x += g_Ball.offsetWhilePickedUpHistory[3].x;
        avg.y += g_Ball.offsetWhilePickedUpHistory[3].y;
        avg.z += g_Ball.offsetWhilePickedUpHistory[3].z;
        avg.x /= 3.0f;
        avg.y /= 3.0f;
        avg.z /= 3.0f;
        model->pos.x = g_Ball.AtBat_Contact_BallPos.x + avg.x;
        model->pos.y = g_Ball.AtBat_Contact_BallPos.y + avg.y;
        model->pos.z = g_Ball.AtBat_Contact_BallPos.z + avg.z;
        model->pos.y = -model->pos.y;
    }

    if ((g_GameLogic.gameStatus == GAME_STATUS_AT_BAT && g_Ball.pitchHangtimeCounter >= 0) ||
        (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL && show != 0)) {
        if ((g_Pitcher.pitcherActionState != PITCHER_ACTION_STATE_NO_CONTACT ||
             g_Pitcher.currentStateFrameCounter < 1 || g_FieldingLogic.liveBallBcOfPickoffOrStealCd) &&
            (g_Pitcher.pitcherActionState != PITCHER_ACTION_STATE_NO_CONTACT ||
             g_FieldingLogic.liveBallBcOfPickoffOrStealCd ||
             g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES) &&
            ((g_Pitcher.pitcherActionState != PITCHER_ACTION_STATE_HIT &&
              g_Pitcher.pitcherActionState != PITCHER_ACTION_STATE_POST_HIT) ||
             g_Pitcher.currentStateFrameCounter < 1 || g_FieldingLogic.liveBallBcOfPickoffOrStealCd) &&
            g_Ball.collisionRelated < 2 && !g_Batter.hitByPitch && !g_Pitcher.peachDaisyStarAnimationOn &&
            !g_Batter.invisibleBallForPeachStarHit &&
            (g_d_GameSettings.StadiumID != STADIUM_ID_YOHSI_PARK || !g_Ball.pauseBallMovementWhenInPlant) &&
            (!(g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_NO_CONTACT ||
               g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_HIT ||
               g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_POST_HIT) ||
             g_Minigame.GameMode_MiniGame != MINI_GAME_ID_BOBOMB_DERBY)) {
            model->visible = TRUE;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
            if (g_Minigame.TF_ballDespawnedInd) {
                model->visible = FALSE;
            } else if (g_Minigame.TF_framesSinceHittingPanel > 0 && g_Minigame.TF_framesSinceHittingPanel % 3 == 0) {
                model->visible = FALSE;
            }
        }
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY && g_Minigame.bOD_hrFireworksLaunchedInd) {
            model->visible = FALSE;
            stopBallTrail();
        }
    }

    scene = 0;
    if (g_GameLogic.sceneID == SCENE_ID_LIVE_BALL) {
        scene = 1;
    }
    if (g_Stats.replayInd) {
        scene = 2;
    }
    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY) {
        applyUniformScaleToObject(lbl_3_data_6838[g_Minigame.bOD_KingBombInd], 0);
    } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        scale = lbl_803CB740[scene];
        baseballCTRLSetScale(scale, scale, scale, starBallOffsets[animRelated[0xCB]]);
    } else {
        scale = ballScaleFactors[animRelated[0xCB]][scene];
        baseballCTRLSetScale(scale, scale, scale, starBallOffsets[animRelated[0xCB]]);
    }
    if (garlicModel != NULL) {
        switch (garlicIndex) {
        case 14:
            garlicScaleCode = CAPTAIN_STAR_TYPE_NONE;
            break;
        case 15:
            garlicScaleCode = CAPTAIN_STAR_TYPE_WARIO;
            break;
        case 16:
            garlicScaleCode = CAPTAIN_STAR_TYPE_WALUIGI;
            break;
        }
        scale = ballScaleFactors[garlicScaleCode][scene];
        baseballCTRLSetScale(scale, scale, scale, garlicIndex);
        garlicModel->visible = model->visible;
    }
    ballAnimationSubFun1(model->visible);
    ballAnimationSubFun2();
    ballAnimationSubFun3();
    ballAnimationSubFun4();
}

// .text:0x000695F8 size:0x1D4 mapped:0x806A868C
void ballAnimationSubFun1(BOOL visible) {
    BallModel* models = hugeAnimStruct.ballModels;
    s32 type;

    models[1].visible = FALSE;
    models[1].pos.x = g_Ball.AtBat_Contact_BallPos.x;
    models[1].pos.y = -g_Ball.physicsSubstruct.twoFrameLookback[1] - 0.04f;
    models[1].pos.z = g_Ball.AtBat_Contact_BallPos.z;
    if (g_Ball.warioWaluGarlicIsActive) {
        if (g_Ball.framesSinceHit & 1) {
            models[1].pos.x = g_Ball.warioStarHitCoords[2].x;
            models[1].pos.z = g_Ball.warioStarHitCoords[2].z;
        }
    } else if (g_Pitcher.warioWaluStarAnimationStage == 1 && (g_Pitcher.pitchTotalTimeCounter & 1)) {
        models[1].pos.x = (g_Pitcher.ballCurrentPosition.x + g_Pitcher.pitchX_parabolicAdjustment) -
                          g_Pitcher.starPitchPositionAdjustment.x;
    }
    if (g_Ball.fielderActionOccuring) {
        models[1].pos.x = g_Ball.fielderActionCatchCoords.x;
        models[1].pos.y = -g_Ball.fielderActionCatchCoords.y;
        models[1].pos.z = g_Ball.fielderActionCatchCoords.z;
    }
    if (g_Ball.hitNoteBlockInd) {
        models[1].pos.x = stadiumObjectCollision.hitBallPos.x;
        models[1].pos.z = stadiumObjectCollision.hitBallPos.z;
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        baseballCTRLSetScale(lbl_3_data_6830[1], 1.0f, lbl_3_data_6830[1], 1);
    } else {
        baseballCTRLSetScale(lbl_3_data_6830[0], 1.0f, lbl_3_data_6830[0], 1);
    }
    if (visible) {
        type = g_Ball.collisionCode & 0x7F;
        if (type == BALL_COLLISION_TYPE_GRASS || type == BALL_COLLISION_TYPE_DIRT ||
            type == BALL_COLLISION_TYPE_ROUGH_TERRAIN || type == BALL_COLLISION_TYPE_WATER ||
            (type >= 0x70 && type < 0x79)) {
            models[1].visible = TRUE;
        }
    }
}

// .text:0x000692E0 size:0x318 mapped:0x806A8374
void ballAnimationSubFun2(void) {
    VecSrcDst ray;
    CollisionStruct hit;
    BallModel* model;
    s32 index;
    u32 type;
    f32 height;
    f32 rot;

    hugeAnimStruct.ballModels[2].visible = FALSE;
    hugeAnimStruct.ballModels[3].visible = FALSE;
    if (g_Stats.replayInd) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        return;
    }
    if (g_Minigame.GameMode_MiniGame != MINI_GAME_ID_NONE) {
        return;
    }
    if (g_Ball.pauseBallMovementWhenInPlant || g_Ball.frameCountdownAfterLeavingPlant) {
        return;
    }
    if (g_Ball.deadBallReason) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE &&
        !inningSetting.controlOptions[g_GameLogic.teams[g_GameLogic.teamFielding]].dropSpot) {
        return;
    }
    if (g_GameLogic.sceneID != SCENE_ID_LIVE_BALL) {
        return;
    }
    if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd) {
        return;
    }
    if (g_Ball.AtBat_ContactResult != 0) {
        return;
    }
    if (g_Ball.maxYOfHit < 2.0f) {
        return;
    }
    if (g_Ball.currentStarSwing2 == CAPTAIN_STAR_TYPE_PEACH || g_Ball.currentStarSwing2 == CAPTAIN_STAR_TYPE_DAISY) {
        return;
    }
    if (g_Ball.warioWaluGarlicIsActive) {
        return;
    }

    if (g_FieldingLogic._0144) {
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE &&
            (g_Practice.practiceType_2 == 1 || g_Practice.practiceLevel == 4)) {
            index = 2;
        } else {
            index = 3;
        }
    } else {
        index = 2;
    }
    model = &hugeAnimStruct.ballModels[index];
    model->visible = TRUE;
    ray.src.x = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
    ray.src.y = -1.0f;
    ray.src.z = g_Ball.physicsSubstruct.hitLandingSpotDistFromHome;
    ray.dst.x = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
    ray.dst.y = 1.0f;
    ray.dst.z = g_Ball.physicsSubstruct.hitLandingSpotDistFromHome;
    type = checkCollision(&ray, &hit, 0, FALSE);
    if (type == BALL_COLLISION_TYPE_GRASS || type == BALL_COLLISION_TYPE_DIRT ||
        type == BALL_COLLISION_TYPE_ROUGH_TERRAIN || type == BALL_COLLISION_TYPE_WATER || type == 50) {
        model->pos.y = hit.position.y - 0.06f;
    } else {
        model->pos.y = -0.06f;
    }
    model->pos.x = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
    model->pos.z = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
    rot = model->rot.y;
    height = 30.0f - g_Ball.AtBat_Contact_BallPos.y;
    if (height < 1.0f) {
        height = 1.0f;
    }
    height *= 0.003f;
    model->rot.y = radianAngleReduction(rot + height);
    height = LinearInterpolateToNewRange(g_Ball.framesUntilBallHitsGround, 0.0f, 120.0f, lbl_3_data_6840[0],
                                         lbl_3_data_6840[1]);
    baseballCTRLSetScale(height, height, height, index);
}

// .text:0x00069184 size:0x15C mapped:0x806A8218
void ballAnimationSubFun3(void) {
    BallModel* model;

    if (g_Batter.trimmedBat == 1) {
        model = &hugeAnimStruct.ballModels[6];
    } else {
        model = &hugeAnimStruct.ballModels[5];
    }
    model->visible = FALSE;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_MENU) {
            return;
        }
        if (g_Practice.practiceLevel != 4 && g_Practice.practiceType_2 != 1) {
            return;
        }
    } else if (!g_Batter.easyBatting) {
        return;
    }
    if (g_Stats.replayInd) {
        return;
    }
    if (g_GameLogic.gameStatus != GAME_STATUS_DEFAULT && g_GameLogic.gameStatus != GAME_STATUS_AT_BAT) {
        return;
    }
    if (g_GameLogic.sceneID != SCENE_ID_AT_BAT) {
        return;
    }
    model->visible = TRUE;
    if (g_Batter.batterHand != BATTING_HAND_RIGHT) {
        model->pos.x = -g_Batter.batPosition2.x;
        model->rot.y = 3.1415927f;
    } else {
        model->pos.x = g_Batter.batPosition2.x;
        model->rot.y = 0.0f;
    }
    model->pos.z = g_Batter.batPosition2.z + lbl_3_data_6848[1];
    model->pos.y = lbl_3_data_6848[0];
}

// .text:0x0006916C size:0x18 mapped:0x806A8200
void fn_3_6916C(void) {
    animRelated[0xCB] = CAPTAIN_STAR_TYPE_NONE;
    animRelated[0xCC] = 0;
}

// .text:0x000690FC size:0x70 mapped:0x806A8190
void clearAnimationRelatedPointers(void) {
    hugeAnimStruct.ballModels[0].visible = FALSE;
    hugeAnimStruct.ballModels[1].visible = FALSE;
    hugeAnimStruct.ballModels[2].visible = FALSE;
    hugeAnimStruct.ballModels[3].visible = FALSE;
    hugeAnimStruct.ballModels[5].visible = FALSE;
    hugeAnimStruct.ballModels[6].visible = FALSE;
    hugeAnimStruct.ballModels[7].visible = FALSE;
    hugeAnimStruct.ballModels[8].visible = FALSE;
    hugeAnimStruct.ballModels[9].visible = FALSE;
    hugeAnimStruct.ballModels[10].visible = FALSE;
    hugeAnimStruct.ballModels[12].visible = FALSE;
    hugeAnimStruct.ballModels[13].visible = FALSE;
}

// .text:0x00068BB4 size:0x548 mapped:0x806A7C48
void ballSpinSetting(void) {
    if (lbl_80366158[0x28] == 0 || animRelated[0xCB] == CAPTAIN_STAR_TYPE_BOWSER ||
        animRelated[0xCB] == CAPTAIN_STAR_TYPE_BOWSERJR) {
        if (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT) {
            if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY) {
                if (g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_IN_AIR) {
                    BALL_SPIN.yaw += 50;
                } else {
                    BALL_SPIN.yaw = 0;
                }
                BALL_SPIN.pitch = 0;
                BALL_SPIN.roll = 0;
            } else if (animRelated[0xCB] == CAPTAIN_STAR_TYPE_YOSHI || animRelated[0xCB] == CAPTAIN_STAR_TYPE_BIRDO) {
                BALL_SPIN.yaw += 300;
                BALL_SPIN.pitch += 100;
                BALL_SPIN.roll = 0;
            } else if (animRelated[0xCB] == CAPTAIN_STAR_TYPE_BOWSER || animRelated[0xCB] == CAPTAIN_STAR_TYPE_BOWSERJR) {
                if (g_Pitcher.bulletPitchStageCode == 1) {
                    BALL_SPIN.yaw = radToShortAngle(3.1415927f + (6.2831855f - g_Pitcher.bulletPitchLoopAngleRadians));
                } else {
                    BALL_SPIN.yaw = 0;
                }
                BALL_SPIN.pitch = 0;
                BALL_SPIN.roll = 0;
            } else if (animRelated[0xCB] == CAPTAIN_STAR_TYPE_DK || animRelated[0xCB] == CAPTAIN_STAR_TYPE_DIDDY) {
                BALL_SPIN.yaw = 0;
                BALL_SPIN.roll = 0;
                if (g_Pitcher.handedness) {
                    BALL_SPIN.pitch += 200;
                } else {
                    BALL_SPIN.pitch -= 200;
                }
            } else if (animRelated[0xCB] == CAPTAIN_STAR_TYPE_PEACH || animRelated[0xCB] == CAPTAIN_STAR_TYPE_DAISY) {
                BALL_SPIN.yaw = 0;
                BALL_SPIN.pitch = 0;
                BALL_SPIN.roll = 0;
            } else {
                BALL_SPIN.yaw -= 600;
                BALL_SPIN.pitch = 0;
                BALL_SPIN.roll = 0;
            }
        } else if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL) {
            if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY) {
                if (g_Ball.AtBat_ContactResult == 0) {
                    BALL_SPIN.yaw += (s16)(400.0f * g_Ball.ballVelocity);
                } else {
                    BALL_SPIN.yaw -= (s16)(400.0f * g_Ball.ballVelocity);
                }
                BALL_SPIN.pitch = 0;
                BALL_SPIN.roll = 0;
            } else if (g_Ball.fielderWBallIndex >= 0) {
                BALL_SPIN.roll = 0;
                BALL_SPIN.pitch = 0;
                BALL_SPIN.yaw = 0;
            } else if (animRelated[0xCB] == CAPTAIN_STAR_TYPE_YOSHI || animRelated[0xCB] == CAPTAIN_STAR_TYPE_BIRDO) {
                BALL_SPIN.pitch = -(g_Ball.ballTravelAngle - 0x400);
                BALL_SPIN.roll = 0;
                BALL_SPIN.yaw += (s16)(200.0f * g_Ball.ballVelocity);
            } else if (animRelated[0xCB] == CAPTAIN_STAR_TYPE_BOWSER || animRelated[0xCB] == CAPTAIN_STAR_TYPE_BOWSERJR) {
                BALL_SPIN.pitch = normalizeAngle(0xC00 - g_Ball.Hit_HorizontalAngle);
                BALL_SPIN.yaw = 0;
                BALL_SPIN.roll = 0;
            } else if (animRelated[0xCB] == CAPTAIN_STAR_TYPE_DK || animRelated[0xCB] == CAPTAIN_STAR_TYPE_DIDDY) {
                BALL_SPIN.yaw = 0;
                BALL_SPIN.roll = 0;
                if (g_Batter.batterHand != BATTING_HAND_RIGHT) {
                    BALL_SPIN.pitch -= 200;
                } else {
                    BALL_SPIN.pitch += 200;
                }
            } else if (animRelated[0xCB] == CAPTAIN_STAR_TYPE_PEACH || animRelated[0xCB] == CAPTAIN_STAR_TYPE_DAISY) {
                BALL_SPIN.yaw = 0;
                BALL_SPIN.pitch = 0;
                BALL_SPIN.roll = 0;
            } else {
                BALL_SPIN.roll = 0;
                BALL_SPIN.pitch = 0x800 - g_Ball.ballTravelAngle;
                if (g_Ball.AtBat_ContactResult == 0) {
                    BALL_SPIN.yaw += (s16)(400.0f * g_Ball.ballVelocity);
                } else if (g_Ball.ballState == BALL_STATE_THROWN && !g_Ball.thrownBallHasHitGround) {
                    BALL_SPIN.yaw += (s16)(800.0f * g_Ball.ballVelocity);
                } else {
                    BALL_SPIN.yaw -= (s16)(400.0f * g_Ball.ballVelocity);
                }
            }
        } else {
            BALL_SPIN.roll = 0;
            BALL_SPIN.pitch = 0;
            BALL_SPIN.yaw = 0;
        }
        BALL_SPIN.yaw = normalizeAngle(BALL_SPIN.yaw);
        BALL_SPIN.pitch = normalizeAngle(BALL_SPIN.pitch);
        BALL_SPIN.roll = normalizeAngle(BALL_SPIN.roll);
    }
}

// .text:0x000685F0 size:0x5C4 mapped:0x806A7684
void displayBallTrail(void) {
    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_CHAINCHOMP_SPRINT ||
        g_Minigame.GameMode_MiniGame == MINI_GAME_ID_PIRANHA_PANIC ||
        g_Minigame.GameMode_MiniGame == MINI_GAME_ID_STAR_DASH) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_MENU) {
            stopBallTrail();
            return;
        }
        if (g_Practice.tutorialState == TUTORIAL_STATE_2) {
            stopBallTrail();
            return;
        }
        if (g_Practice._19F != 0 &&
            (pauseControl[0x1D2] == 7 || pauseControl[0x1D2] == 9 || pauseControl[0x1D2] == 11)) {
            stopBallTrail();
            return;
        }
    }

    if (g_Ball.pitchHangtimeCounter == 1) {
        if (g_Pitcher.starPitchType != CAPTAIN_STAR_TYPE_NONE) {
            if (g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_DK || g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_DIDDY) {
                setupBallTrailEffect(5, 45);
            } else if (g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_YOSHI ||
                       g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_BIRDO) {
                setupBallTrailEffect(6, 120);
            } else {
                stopBallTrail();
            }
        } else if (g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_NONE && g_Pitcher.ballHaloTrainInd_unused) {
            setupBallTrailEffect(10, 45);
        } else if (g_Pitcher.ChargePitchType == 3) {
            setupBallTrailEffect(2, 45);
        } else if (g_Pitcher.ChargePitchType != 0) {
            setupBallTrailEffect(1, 45);
        } else {
            setupBallTrailEffect(1, 45);
        }
    } else if (g_Ball.pitchHangtimeCounter >= 1 && g_Ball.framesSinceHit <= 0) {
        if (animRelated[0xCC] && g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_NO_CONTACT) {
            stopBallTrail();
        }
    } else if (g_Ball.framesSinceHit == 1) {
        stopBallTrail();
    } else if (g_Ball.framesSinceHit == 2) {
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY) {
            if (g_Ball.bODQualifyingHitInd) {
                setupBallTrailEffect(3, 180);
            } else {
                stopBallTrail();
            }
        } else if (g_Ball.currentStarSwing != CAPTAIN_STAR_TYPE_NONE) {
            if (g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_DK || g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_DIDDY) {
                setupBallTrailEffect(5, 90);
            } else if (g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_YOSHI ||
                       g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_BIRDO) {
                setupBallTrailEffect(7, 180);
            } else {
                stopBallTrail();
            }
        } else if (g_Batter.captainStarSwingActivated == CAPTAIN_STAR_TYPE_NONE &&
                   g_Batter.didNonCaptainStarSwingConnect) {
            setupBallTrailEffect(11, 90);
        } else if (g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy) {
            setupBallTrailEffect(4, 90);
        } else {
            setupBallTrailEffect(3, 90);
        }
    } else if (g_Ball.framesSinceHit > 0) {
        if (animRelated[0xCC]) {
            if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
                stopBallTrail();
            }
            if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER) {
                if (g_Minigame.barrelBatter_scoreCalculatedInd) {
                    stopBallTrail();
                }
            } else if (g_Ball.timeSinceBallPickedUp == 0) {
                stopBallTrail();
            } else if (g_Ball.numFieldersWhoHandledBallDuringPlay == 1 && g_Ball.numberOfThrowsDuringPlay == 0) {
                stopBallTrail();
            } else if (0.0f == g_Ball.ballVelocity) {
                stopBallTrail();
            }
        }
        if (g_Ball.framesSinceThrowStarted == 1) {
            if (g_FieldingLogic.IsChemistryThrow) {
                displayChem_antiChemGraphics(g_Ball.fielderBeingThrownTo, FALSE);
                displayChem_antiChemGraphics(g_Ball.throwingFielder, FALSE);
                setupBallTrailEffect(8, 90);
            } else if (g_Ball.IsAntichemistryThrow) {
                displayChem_antiChemGraphics(g_Ball.fielderBeingThrownTo, TRUE);
                displayChem_antiChemGraphics(g_Ball.throwingFielder, TRUE);
                setupBallTrailEffect(9, 90);
            } else if (g_FieldingLogic.laser_1) {
                setupBallTrailEffect(2, 90);
            } else if (g_FieldingLogic.smashThrowInd || g_FieldingLogic.throwSpeedType == 1) {
                setupBallTrailEffect(1, 90);
            }
        }
    }
}

// .text:0x00067EF0 size:0x700 mapped:0x806A6F84
s32 fn_3_67EF0(TrailPointList* list, s32 capacity, Vec* positions, u32* colors, u32 color, f32 width,
               Vec* capPositions, u32* capColors, Vec* direction) {
    Mtx m;
    // [0..1]: the two most recent trail points (view space); [2..3]: the current segment's
    // endpoints projected to a common depth.
    Vec pts[4];
    Vec e;
    Vec d;
    s32 alpha;
    s32 cur;
    s32 n;
    s32 i;
    s32 sign;
    s32 k;
    Vec* prev;
    Vec* pa;
    Vec* pb;
    Vec* pe;
    f32 angle;
    f32 tmp;

    *colors = color;
    alpha = color & 0xFF;
    PSMTXCopy(returnFloatFromModeIndex(0)->view, m);
    cur = 1;
    n = 0;
    fn_80023DFC(list, &pts[0]);
    PSMTXMultVec(m, &pts[0], &pts[0]);
    pa = &pts[2];
    pb = &pts[3];
    pe = &e;
    while (fn_80023D98(list, &pts[cur])) {
        PSMTXMultVec(m, &pts[cur], &pts[cur]);
        prev = &pts[cur == 0];
        if (pts[cur].z == prev->z) {
            memcpy(pa, prev, sizeof(Vec));
            memcpy(pb, &pts[cur], sizeof(Vec));
        } else if (0.0f != prev->z) {
            pts[2].x = prev->x * pts[cur].z / prev->z;
            pts[2].y = prev->y * pts[cur].z / prev->z;
            pts[2].z = prev->z;
            memcpy(pb, &pts[cur], sizeof(Vec));
        } else {
            memcpy(pa, prev, sizeof(Vec));
            pts[3].x = pts[cur].x * prev->z / pts[cur].z;
            pts[3].y = pts[cur].y * prev->z / pts[cur].z;
            pts[3].z = pts[cur].z;
        }
        PSVECSubtract(pa, pb, &d);
        d.z = 0.0f;
        if (PSVECMag(&d) != 0.0f) {
            PSVECNormalize(&d, pe);
            memcpy(&positions[n * 2], prev, sizeof(Vec));
            PSVECScale(pe, width, &positions[n * 2 + 1]);
            cur ^= 1;
            n++;
        }
    }
    prev = &pts[cur == 0];
    memcpy(&positions[n * 2], prev, sizeof(Vec));
    memcpy(&positions[n * 2 + 1], prev, sizeof(Vec));
    colors[n] = 0xFFFFFF00;
    n = n * alpha / 255;

    PSVECNormalize(&positions[1], &d);
    PSVECSubtract(&positions[0], &positions[2], &pts[0]);
    if (PSVECMag(&pts[0]) != 0.0f) {
        PSVECNormalize(&pts[0], &pts[0]);
    }
    angle = acos(PSVECDotProduct(&pts[0], &d));
    d.z = -d.y;
    d.y = d.x;
    d.x = d.z;
    d.z = 0.0f;

    for (i = 0; i < n; i++) {
        memcpy(&pts[0], &positions[i * 2], sizeof(Vec));
        if (direction != NULL) {
            PSVECScale(direction, width * (n - i) / n, pe);
        } else {
            PSVECScale(&positions[i * 2 + 1], (f32)(n - i) / n, pe);
            e.z = -e.y;
            e.y = e.x;
            e.x = e.z;
            e.z = 0.0f;
        }
        PSVECAdd(&pts[0], pe, &positions[i * 2]);
        PSVECSubtract(&pts[0], pe, &positions[i * 2 + 1]);
        colors[i] = (color & 0xFFFFFF00) | ((alpha * (n - i) / n) & 0xFF);
    }

    if (positions[0].z >= positions[(n - 1) * 2].z) {
        sign = -1;
    } else {
        sign = 1;
    }
    PSMTXRotAxisRad(m, &d, angle * -sign);

    for (i = 0; i < 2; i++) {
        if (direction != NULL) {
            PSVECScale(direction, width, &d);
            tmp = -d.y;
            d.y = d.x;
            d.x = tmp;
        } else {
            PSVECSubtract(&positions[i], &positions[i + 2], &d);
            if (PSVECMag(&d) != 0.0f) {
                PSVECNormalize(&d, &d);
            } else {
                d.y = 0.0f;
                d.z = 0.0f;
                d.x = 1.0f;
            }
            PSVECScale(&d, width, &d);
        }
        PSMTXMultVec(m, &d, &d);
        PSVECAdd(&positions[i], &d, &capPositions[i]);
        memcpy(&capPositions[i + 2], &positions[i], sizeof(Vec));
        PSVECSubtract(&positions[i], &d, &capPositions[i + 4]);
    }

    capColors[0] = colors[0];
    capColors[1] = colors[0];
    capColors[2] = colors[0];
    if (angle > 1.5707964f) {
        angle = 3.1415927f - angle;
    }
    angle /= 1.5707964f;
    alpha = colors[0] & 0xFF;
    capColors[1] &= 0xFFFFFF00;
    capColors[2] &= 0xFFFFFF00;
    k = (u32)alpha * angle;
    colors[0] &= 0xFFFFFF00;
    capColors[1] |= k & 0xFF;
    capColors[2] |= k & 0xFF;
    colors[0] |= (alpha - k) & 0xFF;

    memset(&positions[n * 2], 0, (capacity - n) * sizeof(Vec) * 2);
    memset(&colors[n], 0, (capacity - n) * sizeof(u32));
    DCStoreRangeNoSync(positions, capacity * 2 * sizeof(Vec));
    DCStoreRangeNoSync(colors, capacity * sizeof(u32));
    DCStoreRangeNoSync(capPositions, sizeof(Vec) * 6);
    DCStoreRangeNoSync(capColors, sizeof(u32) * 6);
    return sign;
}

// .text:0x00067C34 size:0x2BC mapped:0x806A6CC8
void fn_3_67C34(void* arg) {
    TrailDrawRecord* rec = arg;
    Mtx mtx = {
        { 1.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f },
    };
    int i;

    setScissorAndProjection(0);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 14);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetColorUpdate(GX_TRUE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3X4, GX_TG_TEXCOORD0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
    if (lbl_3_bss_204 != NULL) {
        ((u8*)lbl_3_bss_204)[0xD] = 0;
        SetDisplayStateTexture(lbl_3_bss_204, 0, 0);
    }
    if (lbl_3_bss_204 != NULL) {
        GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
    } else {
        GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    }
    GXSetZCompLoc(GX_FALSE);
    GXInvalidateVtxCache();
    for (i = 0; i < 2; i++) {
        GXSetArray(GX_VA_POS, rec->meshes[i]->positions, sizeof(Vec));
        GXSetArray(GX_VA_CLR0, rec->meshes[i]->colors, sizeof(u32));
        GXSetArray(GX_VA_TEX0, rec->meshes[i]->texCoords, sizeof(lbl_3_data_6860[0]));
        GXCallDisplayList(rec->meshes[i]->displayList, rec->meshes[i]->displayListSize);
    }
}

// .text:0x00067A48 size:0x1EC mapped:0x806A6ADC
void ballAnimationSubFun4(void) {
    Vec cur;
    Vec last;
    BOOL push;
    TrailDrawNode* node;

    if (lbl_3_bss_16A8 > 0.0f) {
        if (lbl_80366158[0x28] == 0) {
            push = TRUE;
            if (g_Ball.fielderActionOccuring) {
                cur.x = g_Ball.fielderActionCatchCoords.x;
                cur.y = -g_Ball.fielderActionCatchCoords.y;
                cur.z = g_Ball.fielderActionCatchCoords.z;
            } else {
                cur.x = g_Ball.AtBat_Contact_BallPos.x;
                cur.y = -g_Ball.AtBat_Contact_BallPos.y;
                cur.z = g_Ball.AtBat_Contact_BallPos.z;
            }
            if (lbl_3_bss_1630.count != 0) {
                fn_80023D4C(&lbl_3_bss_1630, &last);
                if (memcmp(&cur, &last, sizeof(Vec)) == 0) {
                    push = FALSE;
                }
            }
            if (push) {
                fn_80023E48(&lbl_3_bss_1630, &cur);
            }
        }
        if (lbl_3_bss_1630.count >= 2) {
            node = (TrailDrawNode*)insertGraphicDrawingFunction(fn_3_678B8, 1000);
            if (lbl_3_bss_16A0 == 6 || lbl_3_bss_16A0 == 7) {
                node->direction = &node->directionStorage;
                node->directionStorage.x = 1.0f;
                node->directionStorage.y = 0.0f;
                node->directionStorage.z = 0.0f;
            } else {
                node->direction = NULL;
            }
            fn_800A7D4C(0, &lbl_3_data_69A0[drawStadiumRelated]);
            if (lbl_80366158[0x28] == 0) {
                if (lbl_3_bss_20C != 0) {
                    lbl_3_bss_20C -= lbl_3_bss_20C > 0;
                } else if (--lbl_3_bss_208 != 0) {
                    lbl_3_bss_16A8 -= lbl_3_bss_16A4;
                } else {
                    lbl_3_bss_16A8 = 0.0f;
                }
            }
        }
    }
}

// .text:0x000678B8 size:0x190 mapped:0x806A694C
void fn_3_678B8(void) {
    s32 idx = drawStadiumRelated;
    s32 dir;

    dir = (fn_3_67EF0(&lbl_3_bss_1630, 60, lbl_3_bss_520[idx], lbl_3_bss_320[idx],
                      (u32)lbl_3_bss_16A8 | 0xFFFFFF00, lbl_3_data_6880[lbl_3_bss_16A0].width,
                      lbl_3_bss_260[idx], lbl_3_bss_220[idx], ((TrailDrawNode*)currentDrawingItem)->direction) +
           1) >> 1;
    lbl_3_bss_164C[drawStadiumRelated][0].positions = lbl_3_bss_520[drawStadiumRelated];
    lbl_3_bss_164C[drawStadiumRelated][0].texCoords = lbl_3_data_6860;
    lbl_3_bss_164C[drawStadiumRelated][0].colors = lbl_3_bss_320[drawStadiumRelated];
    lbl_3_bss_164C[drawStadiumRelated][1].positions = lbl_3_bss_260[drawStadiumRelated];
    lbl_3_bss_164C[drawStadiumRelated][1].texCoords = lbl_3_data_6860;
    lbl_3_bss_164C[drawStadiumRelated][1].colors = lbl_3_bss_220[drawStadiumRelated];
    lbl_3_bss_164C[drawStadiumRelated][1].displayListSize = sizeof(lbl_3_data_6980);
    lbl_3_bss_164C[drawStadiumRelated][1].displayList = lbl_3_data_6980;
    if (dir) {
        lbl_3_bss_164C[drawStadiumRelated][0].displayListSize = sizeof(lbl_3_bss_1060);
        lbl_3_data_69A0[drawStadiumRelated].meshes[0] = &lbl_3_bss_164C[drawStadiumRelated][1];
        lbl_3_bss_164C[drawStadiumRelated][0].displayList = lbl_3_bss_1060;
        lbl_3_data_69A0[drawStadiumRelated].meshes[1] = &lbl_3_bss_164C[drawStadiumRelated][0];
    } else {
        lbl_3_bss_164C[drawStadiumRelated][0].displayListSize = sizeof(lbl_3_bss_11E0);
        lbl_3_bss_164C[drawStadiumRelated][0].displayList = lbl_3_bss_11E0;
        lbl_3_data_69A0[drawStadiumRelated].meshes[0] = &lbl_3_bss_164C[drawStadiumRelated][0];
        lbl_3_data_69A0[drawStadiumRelated].meshes[1] = &lbl_3_bss_164C[drawStadiumRelated][1];
    }
    removeCurrentDrawingItem();
}

// .text:0x00067620 size:0x298 mapped:0x806A66B4
void setupBallTrailEffect(int type, u16 duration) {
    u8* dl;
    u8* start;
    u8* src;
    u8* dst;
    int i;

    lbl_3_bss_16A0 = type;
    if (type == 10) {
        lbl_3_data_6880[type].texture =
            &lbl_3_common_bss_35154.textures->records[lbl_3_data_6940[g_Pitcher.charID] + 0x21];
    } else if (type == 11) {
        lbl_3_data_6880[type].texture =
            &lbl_3_common_bss_35154.textures->records[lbl_3_data_6940[g_Batter.charID] + 0x21];
    }
    lbl_3_bss_16A8 = 255.0f;
    if (duration == 0) {
        lbl_3_bss_20C = -1;
        lbl_3_bss_16A4 = 0.0f;
    } else if (lbl_3_data_6880[type].texture != NULL) {
        lbl_3_bss_20C = duration - 8;
        lbl_3_bss_208 = 8;
        lbl_3_bss_16A4 = 31.875f;
    } else {
        lbl_3_bss_20C = 0;
        lbl_3_bss_208 = duration;
        lbl_3_bss_16A4 = 255.0f / lbl_3_bss_208;
    }
    lbl_3_bss_204 = lbl_3_data_6880[type].texture;
    fn_80023EEC(&lbl_3_bss_1630, lbl_3_bss_1360, lbl_3_data_6880[type].length);

    i = 1;
    lbl_3_bss_11E0[0] = GX_TRIANGLESTRIP;
    start = dl = lbl_3_bss_11E0;
    dl[1] = 0;
    dl[2] = 120;
    dl[3] = 0;
    dl[4] = 0;
    dl[5] = 2;
    dl[6] = 1;
    dl[7] = 0;
    dl[8] = 3;
    dl += 9;
    do {
        *dl++ = i * 2;
        *dl++ = i;
        *dl++ = 6 - (i & 1) * 2;
        *dl++ = i * 2 + 1;
        *dl++ = i;
        *dl++ = 7 - (i & 1) * 2;
    } while (++i < 60);
    DCStoreRangeNoSync(start, dl - start);

    src = lbl_3_bss_11E0;
    memcpy(lbl_3_bss_1060, src, 3);
    dst = lbl_3_bss_1060;
    src += 3;
    dst += 0x16B;
    i = 120;
    while (i-- != 0) {
        dst -= 3;
        memcpy(dst, src, 3);
        src += 3;
    }
    DCStoreRangeNoSync(lbl_3_bss_1060, 0x16B);
    animRelated[0xCC] = 1;
}

// .text:0x000675B8 size:0x68 mapped:0x806A664C
void fn_3_675B8(u16 frames) {
    if (frames == 0) {
        stopBallTrail();
    } else {
        lbl_3_bss_16A4 = lbl_3_bss_16A8 / frames;
        lbl_3_bss_20C = frames;
    }
}

// .text:0x0006750C size:0xAC mapped:0x806A65A0
void fn_3_6750C(TextureHeader* textures) {
    int i;

    for (i = 1; i < 12; i++) {
        lbl_3_data_6880[i].texture = &textures->records[(s32)lbl_3_data_6880[i].texture];
        if (0.0f == lbl_3_data_6880[i].widthRatio) {
            lbl_3_data_6880[i].widthRatio = 1.0f;
        } else {
            lbl_3_data_6880[i].widthRatio = lbl_3_data_6880[i].widthRatio / lbl_3_data_6880[i].width;
        }
        lbl_3_data_6880[i].length = lbl_3_data_6880[i].length * 60 / 100;
        if (lbl_3_data_6880[i].length < 2) {
            lbl_3_data_6880[i].length = 2;
        }
    }
    lbl_3_bss_169C = 0;
}
