#include "game/stadium/sta_c0.h"
#include "header_rep_data.h"
#include "game/stadium/stadium_framework.h"
#include "game/UnknownHomes_Game.h"
#include "Dolphin/mtx.h"
#include "Dolphin/vec.h"
#include "Dolphin/gx.h"
#include "Dolphin/os.h"
#include "Dolphin/stl.h"
#include "Dolphin/rand.h"
#include "C3/control.h"
#include "stl/math.h"
#include "game/sound/m_sound.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x800247e4.h"
#include "Unknown/File_0x80025c58.h"
#include "Unknown/File_0x80025ddc.h"
#include "Unknown/File_0x8005268c.h"
#include "Unknown/File_0x80052734.h"
#include "Unknown/File_0x800b4b38.h"
#include "Unknown/File_0x800bdc88.h"
#include "Unknown/File_0x800bdd74.h"
#include "Unknown/File_0x800acf14.h"

// One entry per outfield tree (10 slots; `usedFlag == 4` ends the list).
typedef struct _MarioTreePlacement {
    /*0x00*/ Vec pos;
    /*0x0C*/ Vec scale;
    /*0x18*/ f32 rotation;
    /*0x1C*/ u8 usedFlag;
    /*0x1D*/ u8 _1D[3];
} MarioTreePlacement; // size: 0x20

typedef enum _MARIO_OBJ_TYPE {
    MARIO_OBJ_NONE = 0,
    MARIO_OBJ_WATER = 1,
    MARIO_OBJ_TREE = 2,
    MARIO_OBJ_MINIGAME = 3,
} MARIO_OBJ_TYPE;

#define MARIO_TREE_COUNT 10
#define MARIO_TREE_END 4

// Mario Stadium view of a stadiumObjectCollision.objects[] entry.
typedef struct _MarioStadiumObj {
    /*0x00*/ u8 _00[0xA1];
    /*0xA1*/ E(u8, MARIO_OBJ_TYPE) type;
    /*0xA2*/ E(u8, MARIO_OBJ_TYPE) variant;
    /*0xA3*/ u8 _A3;
    /*0xA4*/ s32 animOffset;
} MarioStadiumObj;

// One record of the crowd's frame table; `frame` selects the fan pose.
typedef struct _MarioCrowdRecord {
    /*0x00*/ u8 _00[0x1C];
    /*0x1C*/ u16 frame;
    /*0x1E*/ u8 _1E[2];
} MarioCrowdRecord; // size: 0x20

typedef struct _MarioActEffect {
    /*0x00*/ u32 file;
    /*0x04*/ u8 _04[0x58];
} MarioActEffect; // size: 0x5C

typedef struct _MarioCrowdSeat {
    /*0x00*/ u8 type;
    /*0x01*/ u8 frame;
    /*0x02*/ u8 phase;
} MarioCrowdSeat;

#define MARIO_ANIM_TABLE (*(u8**)(hugeAnimStruct + 0x6C))

extern u8 hugeAnimStruct[0x3154];
extern u16 stadiumHazardSoundIDs[16];
extern MarioTreePlacement marioStadiumTrees[MARIO_TREE_COUNT + 1];
extern u8 marioStadiumInputArray[];
extern u8 lbl_3_data_10F7C[];
extern u8 lbl_3_data_10F84[];
extern u8 lbl_3_data_10F88[];
extern u8 lbl_3_data_11008[];
extern MarioCrowdSeat lbl_3_data_11048[32];
extern MarioCrowdSeat lbl_3_data_11108[16];
extern void animateScoreBoardCheck(void* file, int arg);

static const Vec crowdFacing = {0.0f, 0.0f, 1.0f};

static u8 lbl_3_bss_9FCC[0x10];
static MarioActEffect waterEffect;
static u8 emitterPaused;
static GXTexObj noiseTexObj;
static u8* noiseTex;
static int seagullEmitterID;
static int emitterID;
static u32 scrollDelay;
static u32 lbl_3_bss_9F38;

// .text:0x000C9744 size:0x134 mapped:0x807087D8
void manageMarioStadiumSoundEmmitters(void) {
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE &&
        g_GameLogic.gameStatus != GAME_STATUS_MINIGAME_READY) {
        if (g_GameLogic.gameStatus == GAME_STATUS_PAUSED) {
            if (!emitterPaused) {
                updateAndRemoveStadiumEmitter(emitterID);
                if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES) {
                    updateAndRemoveStadiumEmitter(seagullEmitterID);
                }
                emitterPaused = TRUE;
            }
        } else if (emitterPaused) {
            emitterID =
                initializeStadiumObjectEmitter(stadiumHazardSoundIDs[g_d_GameSettings.StadiumID] + 1, NULL, NULL, 1);
            if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES) {
                seagullEmitterID = randomizeAndLoadSoundEffect(stadiumHazardSoundIDs[g_d_GameSettings.StadiumID], 0);
            }
            emitterPaused = FALSE;
        } else {
            updateOrRemoveEmitter(emitterID, NULL, NULL);
            if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES) {
                updateOrRemoveEmitter(seagullEmitterID, NULL, NULL);
            }
        }
    }
}

// .text:0x000C9878 size:0x180 mapped:0x8070890C
void fanAnimationRelated(void) {
    StadiumCrowdWave* wave = stadiumObjectCollision.crowdWave;
    Vec view;
    Vec facing = crowdFacing;
    camera_803c639c_s* cam;
    u32 mode;
    f32 reach;
    u8* state;
    u8* row;
    u8 pose;
    int i;

    if (wave == NULL) {
        return;
    }
    GXSetZCompLoc(GX_DISABLE);
    mode = returnsCurrentMode();
    switch (g_GameLogic.gameStatus) {
    default:
        if (g_Stats.replayInd == 0) {
            cam = returnFloatFromModeIndex(mode);
            PSVECSubtract(&cam->target, &cam->eye, &view);
            view.y = 0.0f;
            reach = wave->cosAngle * PSVECMag(&view);
            pose = PSVECDotProduct(&view, &facing) > reach;
            break;
        }
        // fallthrough
    case GAME_STATUS_PAUSED:
    case GAME_STATUS_INNING_TRANSITION:
    case GAME_STATUS_HOMERUN_END:
    case GAME_STATUS_HOMERUN_LAP:
    case GAME_STATUS_BATTER_CELEBRATION:
    case GAME_STATUS_STAR_CHANCE_VS:
    case GAME_STATUS_CHAMPIONSHIP:
        pose = 0;
        break;
    }
    row = &wave->pattern[mode * 12];
    state = row + pose;
    for (i = 0; i < wave->rowCount; i++) {
        ((MarioCrowdRecord*)wave->frames)[row[0]].frame = state[1];
        ((MarioCrowdRecord*)wave->frames)[row[3]].frame = state[4];
        row += 6;
        state += 6;
    }
}

// .text:0x000C99F8 size:0x68 mapped:0x80708A8C
void fn_3_C99F8(StadiumObject* obj) {
    if (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT || g_GameLogic.gameStatus == GAME_STATUS_DEFAULT) {
        obj->hasShadow = 0;
    } else {
        obj->hasShadow = 1;
        AnimateActorBones(((ACTActor*)obj->model)->actor);
    }
}

// .text:0x000C9A60 size:0x68 mapped:0x80708AF4
void fn_3_C9A60(StadiumObject* obj) {
    if (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT || g_GameLogic.gameStatus == GAME_STATUS_DEFAULT) {
        obj->hasShadow = 0;
    } else {
        obj->hasShadow = 1;
        AnimateActorBones(((ACTActor*)obj->model)->actor);
    }
}

// .text:0x000C9AC8 size:0x94 mapped:0x80708B5C
void fn_3_C9AC8(void) {
    fn_3_B9510(0);
    fn_3_B9510(1);
    GXLoadTexObj(&noiseTexObj, GX_TEXMAP7);
    GXSetIndTexOrder(GX_IND_TEX_STAGE_0, GX_TEXCOORD0, GX_TEXMAP7);
    GXSetNumIndStages(1);
    GXSetIndTexCoordScale(GX_IND_TEX_STAGE_0, GX_ITS_1, GX_ITS_1);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_IND_TEX_STAGE_0, GX_DISABLE, GX_DISABLE, GX_ITM_0);
    GXSetTevIndWarp(GX_TEVSTAGE1, GX_IND_TEX_STAGE_0, GX_DISABLE, GX_DISABLE, GX_ITM_0);
}

// .text:0x000C9B5C size:0x138 mapped:0x80708BF0
void fn_3_C9B5C(StadiumObject* obj) {
    u32 x;
    u32 y;
    int offset;
    s8 prev;
    s8 cur;

    if (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT || g_GameLogic.gameStatus == GAME_STATUS_DEFAULT) {
        obj->hasShadow = 0;
    } else {
        obj->hasShadow = 1;
        if (scrollDelay < 3) {
            scrollDelay++;
        } else {
            for (x = 0; x < 128; x++) {
                for (y = 0; y < 64; y++) {
                    if (y == 0) {
                        prev = noiseTex[fn_800247E4(x, 63, 128, 2)];
                    }
                    offset = fn_800247E4(x, y, 128, 2);
                    cur = noiseTex[offset];
                    noiseTex[offset] = prev;
                    prev = cur;
                }
            }
            scrollDelay = 0;
            DCFlushRange(noiseTex, 128 * 64 * 2);
        }
    }
}

// .text:0x000C9C94 size:0x120 mapped:0x80708D28
void sta_c0(void) {
    f32 m[2][3];
    u32 x;
    u32 y;
    int offset;

    m[0][0] = 0.5f;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[1][0] = 0.0f;
    m[1][1] = 0.0f;
    m[1][2] = 0.0f;
    GXSetIndTexMtx(GX_ITM_0, m, 2);
    noiseTex = fn_3_B9534(128, 64, &noiseTexObj);
    if (noiseTex == NULL) {
        OSPanic("sta_c0.c", 0x29F, "error\n");
    }
    for (y = 0; y < 64; y++) {
        for (x = 0; x < 128; x++) {
            offset = fn_800247E4(x, y, 128, 2);
            noiseTex[offset] = (u8)(rand() % 4) + 0x7E;
        }
    }
}

// .text:0x000C9DB4 size:0xE00 mapped:0x80708E48
void loadMarioStadium(void** files) {
    int phase;
    u32* ids;
    int count;
    u32 treeCount;
    int shadowBit;
    StadiumCrowdWave* wave;
    int i;
    u32 size;
    u8 done = FALSE;
    MarioCrowdSeat* seat;
    MarioTreePlacement* cfg;
    MarioStadiumObj* m;
    int k;
    StadiumObject* o;
    int n;
    int slot;
    u32 t;

    stadiumObjectCollision.preUpdateFunc = updateGameStatusFlag;
    stadiumObjectCollision.updateFunc = manageMarioStadiumSoundEmmitters;
    emitterPaused = TRUE;
    ids = _OSAllocFromHeap(4, 0x24);
    stadiumObjectCollision._34 = ids;
    processStadiumFileObjects(marioStadiumInputArray, 9, (u8*)files, ids);
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES &&
        g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE) {
        animateScoreBoardCheck(files[0], 0xB);
    }

    for (treeCount = 0; treeCount < MARIO_TREE_COUNT; treeCount++) {
        if (marioStadiumTrees[treeCount].usedFlag == MARIO_TREE_END) {
            break;
        }
    }
    stadiumObjectCollision.propCount = treeCount + 3;
    MARIO_ANIM_TABLE = ActorObjectInitTable(treeCount + 3);
    animateBallRelated(MARIO_ANIM_TABLE, 0, 0, files[ids[1]], 0, 0);
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        animateBallRelated(MARIO_ANIM_TABLE, 1, 1, files[ids[4]], (int)files[ids[4] + 2], 0);
        actorSetAnimBank((ACTActor*)(MARIO_ANIM_TABLE + 0xC4), (u32)files[ids[4] + 2]);
    } else {
        animateBallRelated(MARIO_ANIM_TABLE, 1, 1, files[ids[2]], (int)files[ids[2] + 2], 0);
        actorSetAnimBank((ACTActor*)(MARIO_ANIM_TABLE + 0xC4), (u32)files[ids[2] + 2]);
    }
    slot = 2;
    for (t = 0; t < treeCount; t++, slot++) {
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
            animateBallRelated(MARIO_ANIM_TABLE, slot, slot, files[ids[5]], (int)files[ids[5] + 2], 0);
            actorSetAnimBank((ACTActor*)(MARIO_ANIM_TABLE + slot * 0x90 + 0x34), (u32)files[ids[5] + 2]);
        } else {
            animateBallRelated(MARIO_ANIM_TABLE, slot, slot, files[ids[3]], (int)files[ids[3] + 2], 0);
            actorSetAnimBank((ACTActor*)(MARIO_ANIM_TABLE + slot * 0x90 + 0x34), (u32)files[ids[3] + 2]);
        }
    }
    animateBallRelated(MARIO_ANIM_TABLE, slot, slot, files[ids[6]], 0, 0);
    for (i = 0; i < stadiumObjectCollision.propCount; i++) {
        fn_800BD548(MARIO_ANIM_TABLE + i * 0x90 + 0x34, 4, stadiumObjectCollision.lights[0],
                    stadiumObjectCollision.lights[1], stadiumObjectCollision.lights[2],
                    stadiumObjectCollision.lights[3]);
    }
    if (files[ids[7]] != NULL) {
        adjustInternalPointers(files[ids[7]]);
        ACTActorRelated(files[ids[7]], MARIO_ANIM_TABLE + 0x34);
        waterEffect.file = (u32)files[ids[8]];
        actRelated(files[ids[7]], &waterEffect);
        actorRelated(&waterEffect, 0, 0);
    }

    stadiumObjectCollision.objectCount = 0x14;
    size = (g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE ? 0xEC : 0) + 0x14 * sizeof(StadiumObject);
    stadiumObjectCollision.objects = _OSAllocFromHeap(0x20, size);
    memset(stadiumObjectCollision.objects, 0, size);
    stadiumObjectCollision.objectsRelated = _OSAllocFromHeap(0x20, size);
    memset(stadiumObjectCollision.objectsRelated, 0, size);
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE) {
        stadiumObjectCollision.crowd = (StadiumCrowdAnim*)(stadiumObjectCollision.objectsRelated + 0x14);
        stadiumObjectCollision.crowdAlt = stadiumObjectCollision.crowd + 1;
        stadiumObjectCollision.crowd->fans = (u8*)(stadiumObjectCollision.crowdAlt + 1);
        stadiumObjectCollision.crowdAlt->fans = stadiumObjectCollision.crowd->fans + 0x60;
        stadiumObjectCollision.crowdWave = (StadiumCrowdWave*)(stadiumObjectCollision.crowdAlt->fans + 0x30);
    } else {
        stadiumObjectCollision.crowd = NULL;
        stadiumObjectCollision.crowdAlt = NULL;
        stadiumObjectCollision.crowdWave = NULL;
    }

    o = stadiumObjectCollision.objects;
    m = (MarioStadiumObj*)o;
    m->type = MARIO_OBJ_WATER;
    m->variant = MARIO_OBJ_WATER;
    o->model = (StadiumModel*)(MARIO_ANIM_TABLE + 0xC4);
    o->triangles = NULL;
    o->callback = (void (*)(void))fn_3_C9A60;
    o->func = NULL;
    o->hasShadow = 1;
    shadowBit = 0;
    if (o->hasShadow && o->triangles != NULL) {
        shadowBit = 1;
    }
    o->_90b1 = shadowBit;
    ((Control*)o)->type = 0;
    CTRLSetTranslation((Control*)o, 0.0f, 0.0f, 0.0f);
    CTRLSetRotation((Control*)o, 0.0f, 0.0f, 0.0f);
    o->fadeByDepth = 1;
    o->alpha = 0xFF;
    o->effect = NULL;
    o->preDraw = NULL;
    o->animActive = 0;
    o->animIndex = -1;
    o->drawPass = 1;

    o++;
    m = (MarioStadiumObj*)o;
    m->type = MARIO_OBJ_NONE;
    m->variant = MARIO_OBJ_NONE;
    o->model = (StadiumModel*)(MARIO_ANIM_TABLE + 0x34);
    o->triangles = NULL;
    o->callback = (void (*)(void))fn_3_C9B5C;
    o->func = NULL;
    o->hasShadow = 1;
    shadowBit = 0;
    if (o->hasShadow && o->triangles != NULL) {
        shadowBit = 1;
    }
    o->_90b1 = shadowBit;
    ((Control*)o)->type = 0;
    CTRLSetTranslation((Control*)o, 0.0f, 0.0f, 0.0f);
    CTRLSetRotation((Control*)o, 0.0f, 0.0f, 0.0f);
    o->fadeByDepth = 1;
    o->alpha = 0xFF;
    o->effect = (StadiumObjectEffect*)&waterEffect;
    o->preDraw = (void (*)(StadiumObject*))fn_3_C9AC8;
    o->animActive = 0;
    o->animIndex = -1;
    o->drawPass = 1;

    o++;
    m = (MarioStadiumObj*)o;
    count = 2;
    phase = 0;
    cfg = marioStadiumTrees;
    for (i = 0; i < MARIO_TREE_COUNT; i++, cfg++) {
        if (cfg->usedFlag == MARIO_TREE_END) {
            done = TRUE;
        }
        if (done) {
            for (k = i; k < MARIO_TREE_COUNT; k++) {
                marioStadiumTrees[k].usedFlag = MARIO_TREE_END;
            }
            break;
        }
        m->type = MARIO_OBJ_TREE;
        m->variant = MARIO_OBJ_TREE;
        m->animOffset = phase;
        o->model = (StadiumModel*)(MARIO_ANIM_TABLE + (i + 2) * 0x90 + 0x34);
        o->triangles = NULL;
        o->callback = (void (*)(void))fn_3_C99F8;
        o->func = NULL;
        o->hasShadow = 1;
        shadowBit = 0;
        if (o->hasShadow && o->triangles != NULL) {
            shadowBit = 1;
        }
        o->_90b1 = shadowBit;
        ((Control*)o)->type = 0;
        CTRLSetScale((Control*)o, cfg->scale.x, cfg->scale.y, cfg->scale.z);
        CTRLSetTranslation((Control*)o, cfg->pos.x, cfg->pos.y, cfg->pos.z);
        CTRLSetRotation((Control*)o, 0.0f, cfg->rotation, 0.0f);
        o->fadeByDepth = 0;
        o->alpha = 0xFF;
        count++;
        phase += 100;
        o->effect = NULL;
        o->preDraw = NULL;
        o->animActive = 0;
        o->animIndex = -1;
        o->drawPass = 1;
        o++;
        m = (MarioStadiumObj*)o;
    }

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        m->type = MARIO_OBJ_MINIGAME;
        o->model = (StadiumModel*)(MARIO_ANIM_TABLE + slot * 0x90 + 0x34);
        o->triangles = NULL;
        o->callback = NULL;
        o->func = NULL;
        o->hasShadow = 1;
        shadowBit = 0;
        if (o->hasShadow && o->triangles != NULL) {
            shadowBit = 1;
        }
        o->_90b1 = shadowBit;
        ((Control*)o)->type = 0;
        CTRLSetTranslation((Control*)o, 0.0f, 0.0f, 0.0f);
        o->fadeByDepth = 0;
        count++;
        o->alpha = 0xFF;
        o->effect = NULL;
        o->preDraw = NULL;
        o->animActive = 0;
        o->animIndex = -1;
        o->drawPass = 1;
        o++;
        m = (MarioStadiumObj*)o;
    }

    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE) {
        stadiumObjectCollision.crowd->layout = lbl_3_data_10F7C;
        seat = lbl_3_data_11048;
        stadiumObjectCollision.crowd->sequence = lbl_3_data_10F88;
        stadiumObjectCollision.crowd->frames = (u8*)g_UNK_StadiumDetails._00 + 0x60;
        stadiumObjectCollision.crowd->altFrames = (u8*)g_UNK_StadiumDetails._00 + 0x40;
        stadiumObjectCollision.crowd->fanCount = 0x20;
        stadiumObjectCollision.crowd->framesPerLoop = 6;
        stadiumObjectCollision.crowd->phaseRange = 5;
        for (i = 0, k = 0; i < 0x20; i++, k += 3, seat++) {
            stadiumObjectCollision.crowd->fans[k] = seat->type;
            if (seat->frame < 6) {
                stadiumObjectCollision.crowd->fans[k + 1] = seat->frame;
            } else {
                stadiumObjectCollision.crowd->fans[k + 1] = rand() % 6;
            }
            if (seat->phase < 5) {
                stadiumObjectCollision.crowd->fans[k + 2] = seat->phase;
            } else {
                stadiumObjectCollision.crowd->fans[k + 2] = rand() % stadiumObjectCollision.crowd->phaseRange;
            }
        }
        stadiumObjectCollision.crowdAlt->layout = lbl_3_data_10F84;
        seat = lbl_3_data_11108;
        stadiumObjectCollision.crowdAlt->sequence = lbl_3_data_11008;
        stadiumObjectCollision.crowdAlt->frames = (u8*)g_UNK_StadiumDetails._00 + 0xA0;
        stadiumObjectCollision.crowdAlt->altFrames = (u8*)g_UNK_StadiumDetails._00 + 0x80;
        stadiumObjectCollision.crowdAlt->fanCount = 0x10;
        stadiumObjectCollision.crowdAlt->framesPerLoop = 2;
        stadiumObjectCollision.crowdAlt->phaseRange = 8;
        for (i = 0, k = 0; i < 0x10; i++, k += 3, seat++) {
            stadiumObjectCollision.crowdAlt->fans[k] = seat->type;
            if (seat->frame < 2) {
                stadiumObjectCollision.crowdAlt->fans[k + 1] = seat->frame;
            } else {
                stadiumObjectCollision.crowdAlt->fans[k + 1] = rand() % 6;
            }
            if (seat->phase < 8) {
                stadiumObjectCollision.crowdAlt->fans[k + 2] = seat->phase;
            } else {
                stadiumObjectCollision.crowdAlt->fans[k + 2] = rand() % stadiumObjectCollision.crowdAlt->phaseRange;
            }
        }
        fn_3_35E4((int)fanAnimationRelated);
        wave = stadiumObjectCollision.crowdWave;
        wave->frames = g_UNK_StadiumDetails._00;
        wave->rowCount = 2;
        wave->cosAngle = cos(1.3962634801864624);
        o++;
        m = (MarioStadiumObj*)o;
        wave->pattern[0] = 8;
        wave->pattern[1] = 2;
        wave->pattern[2] = 7;
        wave->pattern[3] = 4;
        wave->pattern[4] = 7;
        wave->pattern[5] = 4;
        wave->pattern[6] = 9;
        wave->pattern[7] = 2;
        wave->pattern[8] = 7;
        wave->pattern[9] = 10;
        wave->pattern[10] = 7;
        wave->pattern[11] = 4;
        wave->pattern[12] = 8;
        wave->pattern[13] = 2;
        wave->pattern[14] = 7;
        wave->pattern[15] = 4;
        wave->pattern[16] = 7;
        wave->pattern[17] = 4;
        wave->pattern[18] = 9;
        wave->pattern[19] = 2;
        wave->pattern[20] = 7;
        wave->pattern[21] = 10;
        wave->pattern[22] = 7;
        wave->pattern[23] = 4;
    }

    if (stadiumObjectCollision.objectCount > count) {
        for (n = count; n < stadiumObjectCollision.objectCount; n++) {
            m->type = MARIO_OBJ_NONE;
            m->variant = MARIO_OBJ_NONE;
            o->model = NULL;
            o->triangles = NULL;
            o->callback = NULL;
            o->func = NULL;
            o->hasShadow = 0;
            o->_90b1 = 0;
            o->fadeByDepth = 0;
            ((Control*)o)->type = 0;
            CTRLSetTranslation((Control*)o, 0.0f, 0.0f, 0.0f);
            CTRLSetRotation((Control*)o, 0.0f, 0.0f, 0.0f);
            o->alpha = 0;
            o->effect = NULL;
            o->animActive = 0;
            o->animIndex = -1;
            o++;
            m = (MarioStadiumObj*)o;
        }
    }
    stadiumObjectCollision.vertexDataArray = NULL;
    sta_c0();
}
