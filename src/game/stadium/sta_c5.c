#define SQRT2_LINKAGE static
#include "game/stadium/sta_c5.h"
#include "header_rep_data.h"
#include "game/stadium/stadium_framework.h"
#include "game/UnknownHomes_Game.h"
#include "Dolphin/mtx.h"
#include "Dolphin/vec.h"
#include "Dolphin/gx.h"
#include "stl/math.h"
#include "Dolphin/rand.h"
#include "game/math/game_math.h"
#include "game/ball/collision_primitives.h"
#include "Dolphin/mtxext.h"
#include "Unknown/File_0x8005268c.h"
#include "Unknown/File_0x80052734.h"
#include "Dolphin/stl.h"
#include "C3/control.h"
#include "Dolphin/os.h"
#include "game/fielding/fielder.h"
#include "Unknown/File_0x800b4b38.h"
#include "text/text_channel.h"
#include "Unknown/File_0x80025ddc.h"
#include "Unknown/File_0x80033794.h"
#include "Unknown/File_0x8004c094.h"
#include "Unknown/File_0x800b4bc8.h"
#include "Unknown/File_0x80034cec.h"
#include "game/stadium/stadium_star.h"
#include "static/UnknownHomes_Static.h"
#include "musyx/musyx.h"
#include "game/ball/ball_physics.h"
#include "game/sound/m_sound.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/File_0x80025c58.h"
#include "Unknown/File_0x800bdc88.h"
#include "Unknown/File_0x800bdd74.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x80024404.h"
#include "Unknown/File_0x800247e4.h"
#include "Unknown/File_0x80039aa8.h"
#include "Unknown/File_0x80064430.h"
#include "Unknown/File_0x800527c4.h"
#include "Unknown/File_0x8001b728.h"
#include "Unknown/File_0x800b4908.h"
#include "Unknown/File_0x80033f64.h"
#include "Unknown/File_0x800bd3ec.h"

extern u16 stadiumHazardSoundIDs[16];
extern u8 hugeAnimStruct[0x3154];
extern u8 stadiumHazardSoundFxRelated[0xB4];
extern u8 lbl_3_data_84B8[0x3C];

static u32 lbl_3_bss_B560[4];
static u8* lbl_3_bss_B55C;
static f32 bezierControlPoints[191];
static u32 bezierFactors[7];
static f32 lbl_3_bss_B228[7];
static f32 lbl_3_bss_B224;
static u8 nBarrelLaunchers;
static u8 gFirstCannonPoolIndex;
static u8 maybeObjectCount;
static u8 objIndex;
static u8 numObjects;
static u8 objectIndex;
static u8 lbl_3_bss_B21A;
static u8 lbl_3_bss_B219;
static u8 lbl_3_bss_B218;
static DKJungleAnimBanks lbl_3_bss_B154;
static DKJungleIndTexState lbl_3_bss_B118;
static u8 lbl_3_bss_AF18[0x200];
static DKJungleWaterTarget lbl_3_bss_AF04;
static DKJungleEmitterState lbl_3_bss_AEE8;
static DKJungleFrameState lbl_3_bss_AEE0;

int barrelRollSfxEmitterId = -1;

DKJungleZoneCorner lbl_3_data_1B824[3][4] = {
    {{-33.215999603271484f, 75.68699645996094f},
     {-36.50299835205078f, 69.50599670410156f},
     {-12.026000022888184f, 64.41899871826172f},
     {-15.312000274658203f, 58.23899841308594f}},
    {{-9.670000076293945f, 63.58399963378906f},
     {-11.425000190734863f, 57.84700012207031f},
     {16.149999618530273f, 55.689998626708984f},
     {14.395999908447266f, 49.952999114990234f}},
    {{20.2549991607666f, 53.422000885009766f},
     {16.481000900268555f, 58.141998291015625f},
     {34.1879997253418f, 36.8390007019043f},
     {30.415000915527344f, 33.53799819946289f}},
};

DKJungleBarrelLauncher barrelLauncherDataStruct[12] = {
    {{32.5359992980957f, 4.0f, 100.625f}, -45.0f, 1, {1, 1, 0}},
    {{-32.5359992980957f, 4.0f, 100.625f}, 45.0f, 1, {1, 1, 0}},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 6, {0, 0xFF, 0}},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, {0, 0, 0}},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, {0, 0, 0}},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, {0, 0, 0}},
    {{32.5359992980957f, 10.0f, 100.625f}, -45.0f, 0, {1, 1, 0}},
    {{-32.5359992980957f, 10.0f, 100.625f}, 45.0f, 0, {1, 1, 0}},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 6, {0, 0xFF, 0}},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, {0, 0, 0}},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, {0, 0, 0}},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, {0, 0, 0}},
};

static DKJungleDustTuning lbl_3_data_1B974 = {
    {15, 10, 2},
    {1.0f, 1.0f, 1.0f},
    {0.7f, 0.7f},
    0.7f,
    2,
    3.0f,
    3.0f,
};

DKJungleKlaptrapData jungleKlaptrapData[6] = {
    {{-22.621000289916992f, 0.0f, 66.96299743652344f}, 0.0f, 2, 1, 1, 0, 0, {0, 0, 0}},
    {{2.362499952316284f, 0.0f, 56.76850128173828f}, 0.0f, 2, 1, 1, 0, 1, {0, 0, 0}},
    {{25.33449935913086f, 0.0f, 45.84000015258789f}, 0.0f, 2, 1, 1, 0, 2, {0, 0, 0}},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 6, 0, 0xFF, 0, 0, {0, 0, 0}},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0, 0, {0, 0, 0}},
    {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0, 0, {0, 0, 0}},
};

// File-type table passed to processStadiumFileObjects in loadDKJungle.
static u8 lbl_3_data_1BA34[0x12] = {
    1, 4, 4, 2, 3, 2, 2, 2, 2, 6, 6, 6, 8, 9, 8, 9, 7, 7,
};

static f32 lbl_3_data_1BA48 = 48.0f;

static f32 lbl_3_data_1BA4C[2][2] = {
    {3.0f, 0.0f},
    {-3.0f, 0.0f},
};

DKJungleDrawFuncTable lbl_3_data_1BA5C = {
    {
        {0, fn_3_EEE3C},
        {0, fn_3_EEE3C},
    },
    {1, 1, 1, 0},
};

DKJungleWaterVectors lbl_3_data_1BA70 = {
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
};

static inline void dkPlayHazardSfx(int sfx) {
    int stadiumID;
    u8 vol;
    u8 val;
    SND_VOICEID voice;

    stadiumID = g_d_GameSettings.StadiumID;
    vol = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD ? lbl_3_data_84B8[sfx * 2]
                                                                   : stadiumHazardSoundFxRelated[stadiumID * 0x1E + sfx * 2];
    voice = sndFXStartEx(stadiumHazardSoundIDs[stadiumID] + sfx, vol, 0x3F, 0);
    val = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD ? lbl_3_data_84B8[sfx * 2 + 1]
                                                                   : stadiumHazardSoundFxRelated[stadiumID * 0x1E + sfx * 2 + 1];
    sndFXCtrl(voice, 0x5B, val);
}

// .text:0x000F6FDC size:0x1468 mapped:0x80736070
void loadDKJungle(void** files) {
    u8** animTable = (u8**)(hugeAnimStruct + 0x6C);
    DKJungleBarrelLauncher* launcherCfg;
    DKJungleBarrelLauncher* barrelCfg;
    DKJungleKlaptrapData* klapCfg;
    StadiumObject* o;
    DKJungleBarrel* b;
    DKJungleCannon* c;
    DKJungleKlaptrap* k;
    u32* ids;
    u8 done = FALSE;
    u32 barrelCount;
    u32 klapCount;
    u8 propCount;
    u8 idx;
    u8 barrelAnim;
    u8 cannonAnim;
    u8 klapAnim;
    u8 ringAnim;
    u8 hazeAnim;
    u8 sparkAnim;
    u8 lastAnim;
    u8 n;
    u8 usedAnims;
    u32 shadowBit;
    int i;
    int j;
    BOOL notMinigames;

    notMinigames = g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES;
    stadiumObjectCollision.preUpdateFunc = updateGameStatusFlag;
    stadiumObjectCollision.updateFunc = fn_3_EDFAC;
    lbl_3_bss_B154.flag = 1;
    if (notMinigames) {
        fn_3_B97C8(fn_3_F6FCC);
    }
    lbl_3_bss_AEE8._00[0] = 0;
    ids = _OSAllocFromHeap(4, 0x48);
    stadiumObjectCollision._34 = ids;
    processStadiumFileObjects(lbl_3_data_1BA34, 0x12, (u8*)files, ids);
    lbl_3_bss_B560[0] = (u32)files[0];

    barrelCfg = &barrelLauncherDataStruct[6];
    for (barrelCount = 0; barrelCount < 5; barrelCount++) {
        if (barrelCfg[barrelCount].usedFlag == 6) {
            break;
        }
    }
    propCount = barrelCount + 2;
    klapCfg = jungleKlaptrapData;
    for (klapCount = 0; klapCount < 5; klapCount++) {
        if (klapCfg[klapCount].usedFlag == 6) {
            break;
        }
    }
    propCount += klapCount;
    propCount += 4;
    *animTable = ActorObjectInitTable(propCount);
    stadiumObjectCollision.propCount = propCount;

    idx = 0;
    lbl_3_bss_B219 = 0;
    for (i = 0; i < barrelCount; i++) {
        animateBallRelated(*animTable, idx, idx, files[ids[1]], 0, 0);
        actorSetAnimBank((ACTActor*)(*animTable + idx * 0x90 + 0x34), (u32)files[ids[1] + 2]);
        idx++;
    }
    lbl_3_bss_B218 = idx;
    barrelAnim = idx;
    animateBallRelated(*animTable, idx, idx, files[ids[2]], 0, 0);
    actorSetAnimBank((ACTActor*)(*animTable + idx * 0x90 + 0x34), (u32)files[ids[2] + 2]);
    (*animTable)[idx * 0x90 + 0x8F] = 2;
    updateBoneParam(*(void**)(*animTable + idx * 0x90 + 0x34), (*animTable)[idx * 0x90 + 0x8F] & 1);
    cannonAnim = idx + 1;
    animateBallRelated(*animTable, cannonAnim, cannonAnim, files[ids[3]], 0, 0);
    idx += 2;
    klapAnim = idx;
    for (i = 0; i < klapCount; i++) {
        animateBallRelated(*animTable, idx, idx, files[ids[4]], 0, (int)files[ids[4] + 2]);
        fn_3_B98E8((StadiumAnimData*)(*animTable + idx * 0x90 + 0x34));
        idx++;
    }
    ringAnim = idx;
    animateBallRelated(*animTable, idx, idx, files[ids[5]], 0, 0);
    hazeAnim = ringAnim + 1;
    animateBallRelated(*animTable, hazeAnim, hazeAnim, files[ids[6]], 0, 0);
    sparkAnim = ringAnim + 2;
    animateBallRelated(*animTable, sparkAnim, sparkAnim, files[ids[7]], 0, 0);
    lbl_3_bss_B55C = *animTable + sparkAnim * 0x90 + 0x34;
    lastAnim = ringAnim + 3;
    animateBallRelated(*animTable, lastAnim, lastAnim, files[ids[8]], 0, 0);
    lbl_3_bss_B154.animBank[0] = (u32)files[ids[16]];
    lbl_3_bss_B154.animBank[1] = (u32)files[ids[17]];
    for (i = 0; i < propCount; i++) {
        fn_800BD548(*animTable + i * 0x90 + 0x34, 4, stadiumObjectCollision.lights[0],
                    stadiumObjectCollision.lights[1], stadiumObjectCollision.lights[2],
                    stadiumObjectCollision.lights[3]);
    }
    adjustInternalPointers(files[ids[14]]);
    ACTActorRelated(files[ids[14]], *animTable + hazeAnim * 0x90 + 0x34);
    lbl_3_bss_B154.effectSlot1.file = (u32)files[ids[15]];
    actRelated(files[ids[14]], &lbl_3_bss_B154.effectSlot1);
    actorRelated(&lbl_3_bss_B154.effectSlot1, 0, 0);
    lbl_3_bss_B154.effectSlot1._10 = 0.3f;
    adjustInternalPointers(files[ids[12]]);
    ACTActorRelated(files[ids[12]], *animTable + ringAnim * 0x90 + 0x34);
    lbl_3_bss_B154.effectSlot0.file = (u32)files[ids[13]];
    actRelated(files[ids[12]], &lbl_3_bss_B154.effectSlot0);
    actorRelated(&lbl_3_bss_B154.effectSlot0, 0, 0);

    stadiumObjectCollision.objectCount = 0x19;
    o = _OSAllocFromHeap(0x20, 0x16A8);
    stadiumObjectCollision.objects = o;
    memset(o, 0, 0x16A8);
    o = _OSAllocFromHeap(0x20, 0x16A8);
    stadiumObjectCollision.objectsRelated = o;
    memset(o, 0, 0x16A8);
    o = stadiumObjectCollision.objects;
    b = (DKJungleBarrel*)o;
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES) {
        launcherCfg = barrelLauncherDataStruct;
        n = 0;
        objIndex = 0;
        usedAnims = 0;
        i = 0;
        do {
            if (launcherCfg->usedFlag == 6) {
                break;
            }
            if (barrelCfg->usedFlag != 0) {
                break;
            }
            b->_9D[0] = 0;
            o->model = (StadiumModel*)(*animTable + i * 0x90 + 0x34);
            b->_C2[0] = usedAnims;
            b->_C2[1] = barrelAnim;
            o->triangles = files[ids[9]];
            o->callback = NULL;
            o->func = (int (*)(int, int, void*))fn_3_F1674;
            shadowBit = 0;
            if (o->hasShadow && o->triangles != NULL) {
                shadowBit = 1;
            }
            o->_90b1 = shadowBit;
            b->index = i;
            b->_C5 = n;
            fn_3_F3BB0(b);
            o->fadeByDepth = 1;
            o->alpha = 0xFF;
            o->effect = NULL;
            o->preDraw = NULL;
            o->animActive = 0;
            o->animIndex = -1;
            o->drawPass = 1;
            o->shadowEnabled = 1;
            i++;
            n++;
            launcherCfg++;
            barrelCfg++;
            usedAnims++;
            o++;
            b = (DKJungleBarrel*)o;
            maybeObjectCount++;
        } while (i < 5);
        done = FALSE;
        initBinomialTable();
    }

    launcherCfg = barrelLauncherDataStruct;
    gFirstCannonPoolIndex = n;
    c = (DKJungleCannon*)o;
    i = 0;
    do {
        if (launcherCfg->usedFlag == 6) {
            done = TRUE;
        }
        if (done) {
            for (j = i; j < 5; j++) {
                barrelLauncherDataStruct[j].usedFlag = 6;
            }
            break;
        }
        c->_9D[0] = 1;
        c->index = i;
        c->_C5 = n;
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
            c->barrel = NULL;
        } else {
            c->barrel = (DKJungleBarrel*)&stadiumObjectCollision.objects[objIndex + i];
            c->barrel->pathAngle = &c->rotY;
        }
        c->mode = 0;
        o->model = (StadiumModel*)(*animTable + cannonAnim * 0x90 + 0x34);
        o->triangles = files[ids[10]];
        o->callback = dkJungleBarrelCannonUpdate;
        o->func = (int (*)(int, int, void*))fn_3_F466C;
        o->hasShadow = 1;
        shadowBit = 0;
        if (o->hasShadow && o->triangles != NULL) {
            shadowBit = 1;
        }
        o->_90b1 = shadowBit;
        fn_3_F5C30(c);
        o->fadeByDepth = 1;
        o->alpha = 0xFF;
        o->effect = NULL;
        o->preDraw = (void (*)(StadiumObject*))fn_3_F469C;
        o->animActive = 0;
        o->animIndex = -1;
        o->drawPass = 1;
        i++;
        n++;
        launcherCfg++;
        o++;
        c = (DKJungleCannon*)o;
        nBarrelLaunchers++;
    } while (i < 5);

    done = FALSE;
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES) {
        objectIndex = n;
        i = 0;
        do {
            if (klapCfg->usedFlag == 6) {
                done = TRUE;
            }
            if (done) {
                for (j = i; j < 6; j++) {
                    jungleKlaptrapData[j].usedFlag = 6;
                    jungleKlaptrapData[j]._12 = 0xFF;
                }
                break;
            }
            k = (DKJungleKlaptrap*)o;
            k->_9D[0] = 2;
            o->model = (StadiumModel*)(*animTable + (klapAnim + i) * 0x90 + 0x34);
            o->triangles = files[ids[11]];
            o->callback = klaptrapControl;
            o->func = (int (*)(int, int, void*))klaptrapHitAnimation;
            o->hasShadow = 1;
            shadowBit = 0;
            if (o->hasShadow && o->triangles != NULL) {
                shadowBit = 1;
            }
            o->_90b1 = shadowBit;
            k->index = i;
            maybeGharialCTRLRel(k);
            o->fadeByDepth = 1;
            o->alpha = 0xFF;
            o->effect = NULL;
            o->preDraw = NULL;
            o->animActive = 0;
            o->animIndex = -1;
            o->drawPass = 1;
            i++;
            n++;
            klapCfg++;
            o++;
            numObjects++;
        } while (i < 5);
        insertGraphicDrawingFunction(fn_3_F0184, 0x6001);
    }

    b = (DKJungleBarrel*)o;
    b->_9D[0] = 3;
    o->model = (StadiumModel*)(*animTable + ringAnim * 0x90 + 0x34);
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
    CTRLSetTranslation((Control*)o, 0.0f, -0.15f, 0.0f);
    CTRLSetRotation((Control*)o, 0.0f, 0.0f, 0.0f);
    o->fadeByDepth = 1;
    o->alpha = 0xFF;
    o->effect = (StadiumObjectEffect*)&lbl_3_bss_B154.effectSlot0;
    o->preDraw = NULL;
    o->animActive = 0;
    o->animIndex = -1;
    o->drawPass = 1;
    lbl_3_bss_B21A = n + 1;

    o[1]._9D[0] = 4;
    o[1].model = (StadiumModel*)(*animTable + hazeAnim * 0x90 + 0x34);
    o[1].triangles = NULL;
    o[1].callback = NULL;
    o[1].func = NULL;
    o[1].hasShadow = 1;
    shadowBit = 0;
    if (o[1].hasShadow && o[1].triangles != NULL) {
        shadowBit = 1;
    }
    o[1]._90b1 = shadowBit;
    ((Control*)&o[1])->type = 0;
    CTRLSetTranslation((Control*)&o[1], 0.0f, -0.1f, 0.0f);
    CTRLSetRotation((Control*)&o[1], 0.0f, 0.0f, 0.0f);
    o[1].fadeByDepth = 1;
    o[1].alpha = 0xFF;
    o[1].effect = (StadiumObjectEffect*)&lbl_3_bss_B154.effectSlot1;
    o[1].preDraw = (void (*)(StadiumObject*))fn_3_EEFA4;
    o[1].postDraw = NULL;
    o[1].animActive = 0;
    o[1].animIndex = -1;
    o[1].drawPass = 1;
    insertGraphicDrawingFunction(fn_3_EEF24, 5);

    o[2]._9D[0] = 5;
    o[2].model = (StadiumModel*)(*animTable + lastAnim * 0x90 + 0x34);
    o[2].triangles = NULL;
    o[2].callback = NULL;
    o[2].func = NULL;
    o[2].hasShadow = 1;
    shadowBit = 0;
    if (o[2].hasShadow && o[2].triangles != NULL) {
        shadowBit = 1;
    }
    o[2]._90b1 = shadowBit;
    ((Control*)&o[2])->type = 0;
    CTRLSetTranslation((Control*)&o[2], 0.0f, -0.2f, 0.0f);
    CTRLSetRotation((Control*)&o[2], 0.0f, 0.0f, 0.0f);
    o[2].fadeByDepth = 1;
    o[2].alpha = 0xFF;
    o[2].preDraw = NULL;
    o[2].effect = NULL;
    o[2].animActive = 0;
    o[2].animIndex = -1;
    o[2].drawPass = 1;
    o[2].customZMode = 1;
    o[2].zCompare = 1;
    o[2].zAlways = 0;
    o[2].zUpdate = 0;

    i = n + 3;
    o += 3;
    b = (DKJungleBarrel*)o;
    if (i < stadiumObjectCollision.objectCount) {
        do {
            b->_9D[0] = 0;
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
            b = (DKJungleBarrel*)o;
            i++;
        } while (i < stadiumObjectCollision.objectCount);
    }

    stadiumObjectCollision.vertexDataArray = NULL;
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES) {
        updateDKJungleControl();
    }
    fn_3_EECF4();
}

// .text:0x000F6FCC size:0x10 mapped:0x80736060
void fn_3_F6FCC(void) {
    lbl_3_bss_AEE8._00[0] = 1;
}

// .text:0x000F6C60 size:0x36C mapped:0x80735CF4
void updateDKJungleControl(void) {
    s32 idx;
    int size;
    u8* base;

    size = stadiumObjectCollision.objectCount * 0x18 + (stadiumObjectCollision.objectCount * 4 +
           stadiumObjectCollision.objectCount * 4 + stadiumObjectCollision.objectCount * 2);
    if (stadiumObjectCollision.vertexDataArray == NULL) {
        base = _OSAllocFromHeap(4, size);
        stadiumObjectCollision.vertexDataArray = (VecSrcDst*)base;
        stadiumObjectCollision.hazardData = (s32*)(base + stadiumObjectCollision.objectCount * 0x18);
        stadiumObjectCollision.vertexData = (f32*)(stadiumObjectCollision.hazardData + stadiumObjectCollision.objectCount);
        stadiumObjectCollision.vertexOffsets =
            (u16*)(stadiumObjectCollision.vertexData + stadiumObjectCollision.objectCount);
    }
    memset(stadiumObjectCollision.vertexDataArray, 0, size);
    idx = 0;
    if (maybeObjectCount != 0) {
        fn_3_F6A94(&idx);
    }
    if (nBarrelLaunchers != 0) {
        maybeBarrelCTRLRel(&idx);
    }
    if (numObjects != 0) {
        updateDKJungleObjBoundingBoxes(&idx);
    }
    stadiumObjectCollision.boundingBoxCount = idx;
}

// .text:0x000F6A94 size:0x1CC mapped:0x80735B28
void fn_3_F6A94(s32* idx) {
    DKJungleObjControl ctrl;
    Mtx m;
    int off;
    int i;
    StadiumMeshData* mesh;

    off = (u16)(stadiumObjectCollision.vertexOffsets[*idx - 1] + stadiumObjectCollision.hazardData[*idx - 1]);
    stadiumObjectCollision.vertexOffsets[*idx] = off;
    for (i = 0; i < maybeObjectCount; i++) {
        ((s32*)stadiumObjectCollision.vertexData)[off++] = objIndex + i;
        stadiumObjectCollision.hazardData[*idx]++;
    }
    initBoundingBoxLimits();
    mesh = (StadiumMeshData*)stadiumObjectCollision.objects[objIndex].triangles;
    ctrl.ctrl.type = 0;
    CTRLSetTranslation(&ctrl.ctrl, -50.0f, 0.0f, 40.0f);
    CTRLBuildMatrix(&ctrl.ctrl, m);
    transformVectorsUpdateBoundingBox(m, mesh);
    ctrl.ctrl.type = 0;
    CTRLSetTranslation(&ctrl.ctrl, 50.0f, -20.0f, 95.0f);
    CTRLBuildMatrix(&ctrl.ctrl, m);
    transformVectorsUpdateBoundingBox(m, mesh);
    if ((u32)stadiumObjectCollision.hazardData[*idx] != 0) {
        storeBoundingBoxCoordinates((Vec*)&stadiumObjectCollision.vertexDataArray[*idx],
                                    (Vec*)stadiumObjectCollision.vertexDataArray + (*idx * 2 + 1));
        (*idx)++;
    }
}

// .text:0x000F6938 size:0x15C mapped:0x807359CC
void maybeBarrelCTRLRel(s32* count) {
    DKJungleObjControl ctrl;
    Mtx mtx;
    int i;

    for (i = 0; i < nBarrelLaunchers; i++) {
        u16 offset;
        int objIdx;
        StadiumObject* obj;
        StadiumMeshData* mesh;
        DKJungleBarrelLauncher* launcher;
        int idx = *count;

        offset = stadiumObjectCollision.vertexOffsets[idx - 1] + stadiumObjectCollision.hazardData[idx - 1];
        stadiumObjectCollision.vertexOffsets[idx] = offset;
        objIdx = gFirstCannonPoolIndex + i;
        ((s32*)stadiumObjectCollision.vertexData)[offset] = objIdx;
        stadiumObjectCollision.hazardData[*count]++;
        obj = stadiumObjectCollision.objects + objIdx;
        mesh = (StadiumMeshData*)obj->triangles;
        ctrl.ctrl.type = 0;
        launcher = &barrelLauncherDataStruct[obj->_9C];
        CTRLSetTranslation(&ctrl.ctrl, launcher->pos.x, -launcher->pos.y, launcher->pos.z);
        CTRLSetScale(&ctrl.ctrl, 1.5f, 1.5f, 1.5f);
        CTRLBuildMatrix(&ctrl.ctrl, mtx);
        initBoundingBoxLimits();
        transformVectorsUpdateBoundingBox(mtx, mesh);
        storeBoundingBoxCoordinates((Vec*)&stadiumObjectCollision.vertexDataArray[*count],
                                    (Vec*)stadiumObjectCollision.vertexDataArray + (*count * 2 + 1));
        (*count)++;
    }
}

// .text:0x000F66C8 size:0x270 mapped:0x8073575C
void updateDKJungleObjBoundingBoxes(s32* idx) {
    DKJungleObjControl ctrl;
    Mtx m;
    int i;

    initBoundingBoxLimits();
    for (i = 0; i < numObjects; i++) {
        u16 off;
        int k;
        StadiumMeshData* mesh;
        DKJungleZoneCorner* c;
        f32 minZ, maxZ, minX, maxX;
        StadiumObject* obj;

        off = stadiumObjectCollision.vertexOffsets[*idx - 1] + stadiumObjectCollision.hazardData[*idx - 1];
        stadiumObjectCollision.vertexOffsets[*idx] = off;
        k = objectIndex + i;
        ((s32*)stadiumObjectCollision.vertexData)[off] = k;
        stadiumObjectCollision.hazardData[*idx]++;
        obj = &stadiumObjectCollision.objects[k];
        c = lbl_3_data_1B824[obj->_9C];
        minX = maxX = c[0].x;
        minZ = maxZ = c[0].z;
        {
            DKJungleZoneCorner* q = &c[1];

            if (minX > q->x) {
                minX = q->x;
            } else if (maxX < q->x) {
                maxX = q->x;
            }
            if (minZ > q->z) {
                minZ = q->z;
            } else if (maxZ < q->z) {
                maxZ = q->z;
            }
        }
        {
            DKJungleZoneCorner* q = &c[2];

            if (minX > q->x) {
                minX = q->x;
            } else if (maxX < q->x) {
                maxX = q->x;
            }
            if (minZ > q->z) {
                minZ = q->z;
            } else if (maxZ < q->z) {
                maxZ = q->z;
            }
        }
        {
            DKJungleZoneCorner* q = &c[3];

            if (minX > q->x) {
                minX = q->x;
            } else if (maxX < q->x) {
                maxX = q->x;
            }
            if (minZ > q->z) {
                minZ = q->z;
            } else if (maxZ < q->z) {
                maxZ = q->z;
            }
        }
        mesh = (StadiumMeshData*)stadiumObjectCollision.objects[objectIndex].triangles;
        CTRLSetTranslation(&ctrl.ctrl, minX, 0.0f, maxZ);
        CTRLBuildMatrix(&ctrl.ctrl, m);
        transformVectorsUpdateBoundingBox(m, mesh);
        CTRLSetTranslation(&ctrl.ctrl, maxX, -5.0f, minZ);
        CTRLBuildMatrix(&ctrl.ctrl, m);
        transformVectorsUpdateBoundingBox(m, mesh);
        storeBoundingBoxCoordinates((Vec*)&stadiumObjectCollision.vertexDataArray[*idx],
                                    (Vec*)stadiumObjectCollision.vertexDataArray + (*idx * 2 + 1));
        (*idx)++;
        initBoundingBoxLimits();
    }
}

// .text:0x000F65C8 size:0x100 mapped:0x8073565C
void fn_3_F65C8(s32* idx) {
    DKJungleObjControl ctrl;
    Mtx m;
    u16 off;
    StadiumObject* obj = &stadiumObjectCollision.objects[lbl_3_bss_B21A];
    StadiumMeshData* mesh;

    off = stadiumObjectCollision.vertexOffsets[*idx - 1] + stadiumObjectCollision.hazardData[*idx - 1];
    stadiumObjectCollision.vertexOffsets[*idx] = off;
    ((s32*)stadiumObjectCollision.vertexData)[off] = lbl_3_bss_B21A;
    stadiumObjectCollision.hazardData[*idx]++;
    mesh = (StadiumMeshData*)obj->triangles;
    ctrl.ctrl.type = 0;
    CTRLBuildMatrix(&ctrl.ctrl, m);
    transformVectorsUpdateBoundingBox(m, mesh);
    storeBoundingBoxCoordinates((Vec*)&stadiumObjectCollision.vertexDataArray[*idx],
                                (Vec*)stadiumObjectCollision.vertexDataArray + (*idx * 2 + 1));
    (*idx)++;
}

// .text:0x000F6504 size:0xC4 mapped:0x80735598
TriangleGroup* fn_3_F6504(int offset, Mtx m) {
    StadiumObject* obj = &stadiumObjectCollision.objects[offset];

    if (obj->_9D[0] == 2) {
        if (((DKJungleKlaptrap*)obj)->state < 3 && g_Ball.ballState != BALL_STATE_HELD) {
            CTRLBuildMatrix((Control*)obj, m);
        } else {
            return NULL;
        }
    } else if (obj->_9D[0] == 0) {
        if (((DKJungleBarrel*)obj)->_C1 == 2) {
            return NULL;
        }
        if (g_Ball.AtBat_ContactResult >= BALL_RESULT_TYPE_FIELDED) {
            return NULL;
        }
        CTRLBuildMatrix((Control*)obj, m);
    } else {
        CTRLBuildMatrix((Control*)obj, m);
    }
    return stadiumObjectCollision.objects[offset].triangles;
}

// .text:0x000F6084 size:0x480 mapped:0x80735118
void processJungleObjectCollisions(Mtx view, struct _StadiumDrawOrder* order) {
    Vec pos;
    StadiumDrawOrder swap;
    StadiumDrawOrder* back;
    StadiumDrawOrder* front;
    StadiumDrawOrder* p;
    StadiumDrawOrder* sorted;
    int remaining;
    StadiumObject* obj;
    int count;
    int i;

    if (stadiumObjectCollision.gameStatusIsLiveBall) {
        obj = &stadiumObjectCollision.objects[stadiumObjectCollision.objectCount - 1];
        i = stadiumObjectCollision.objectCount - 1;
        count = 0;
        p = order;
        do {
            if (!obj->hasShadow) {
                p->depth = -512.0f;
                count++;
                p->index = i;
                p++;
            }
            obj--;
        } while (i-- != 0);

        i = stadiumObjectCollision.objectCount - 1;
        remaining = i;
        obj = &stadiumObjectCollision.objects[i];
        back = order + i;
        front = order + count;
        do {
            if (obj->hasShadow) {
                if (obj->_9D[0] == 4) {
                    order[stadiumObjectCollision.objectCount - 1].depth = -1.0f;
                    order[stadiumObjectCollision.objectCount - 1].index = i;
                } else if (obj->fadeByDepth) {
                    CTRLGetTranslation((Control*)obj, &pos.x, &pos.y, &pos.z);
                    PSMTXMultVec(view, &pos, &pos);
                    remaining--;
                    back[-1].depth = pos.z;
                    back[-1].index = i;
                    back--;
                } else {
                    front->depth = -512.0f;
                    front->index = i;
                    front++;
                }
            }
            obj--;
        } while (i-- != 0);

        sorted = allocateAlignedMemoryBlock(32, (stadiumObjectCollision.objectCount - remaining) * sizeof(StadiumDrawOrder));
        fn_800C07BC(order + remaining, sorted, stadiumObjectCollision.objectCount - remaining, sizeof(StadiumDrawOrder),
                    (s32(*)(const f32*, const f32*))fn_3_F5F28);
        unkLoadingCleanupRelated(sorted);

        for (i = 0; i < nBarrelLaunchers; i++) {
            DKJungleCannon* cannon = (DKJungleCannon*)&stadiumObjectCollision.objects[gFirstCannonPoolIndex + i];
            u32 a = fn_3_F5E78(cannon->_C5);
            u32 b = fn_3_F5E78(cannon->barrel->_C5);

            if (a > b) {
                swap = order[a];
                order[a] = order[b];
                order[b] = swap;
            }
        }
        fn_3_F5F4C(view);
    } else {
        p = order;
        obj = stadiumObjectCollision.objects;
        for (i = 0; i < stadiumObjectCollision.objectCount; i++) {
            CTRLGetTranslation((Control*)obj, &pos.x, &pos.y, &pos.z);
            p->depth = 1.0f;
            p->index = i;
            p++;
        }
    }
}

// .text:0x000F5F4C size:0x138 mapped:0x80734FE0
void fn_3_F5F4C(Mtx view) {
    Vec pos;
    u32 i;

    memcpy(&pos, &g_Ball, sizeof(Vec));
    PSMTXMultVec(view, &pos, &pos);
    for (i = 0; i < stadiumObjectCollision.objectCount; i++) {
        StadiumDrawOrder* entry = &stadiumObjectCollision.objectScratch[i];
        StadiumObject* obj = &stadiumObjectCollision.objects[entry->index];

        if (obj->hasShadow) {
            if (obj->_9D[0] == 1) {
                entry->depth = 1.0f;
            } else {
                f32 depth = entry->depth;
                f32 nearZ = 2.0f + pos.z;

                if (depth < nearZ) {
                    entry->depth = 1.0f;
                } else if (depth > 10.0f + pos.z) {
                    entry->depth = 0.25f;
                } else {
                    entry->depth = 1.0 - 0.75f * ((depth - nearZ) / 8.0f);
                }
            }
        }
    }
}

// .text:0x000F5F28 size:0x24 mapped:0x80734FBC
int fn_3_F5F28(const f32* a, const f32* b) {
    f32 x = *a;
    f32 y = *b;
    if (x < y) {
        return -1;
    }
    return x > y;
}

// .text:0x000F5EFC size:0x2C mapped:0x80734F90
int fn_3_F5EFC(const u32* a, const u32* b) {
    if (*a < *b) {
        return -1;
    }
    return *a > *b;
}

// .text:0x000F5E78 size:0x84 mapped:0x80734F0C
static const char noReturnValueString[] =
    "//OZ \x96\xDF\x82\xE8\x92\x6C\x82\xCC\x96\xB3\x82\xA2\x95\x94\x95\xAA\x82\xC9\x97\x88\x82\xDC\x82\xB5\x82\xBD\x81\x42\n";

int fn_3_F5E78(u8 id) {
    StadiumDrawOrder* p = stadiumObjectCollision.objectScratch + stadiumObjectCollision.objectCount;
    u32 i;

    for (i = stadiumObjectCollision.objectCount; i != 0; p--, i--) {
        if (id == p[-1].index) {
            return i - 1;
        }
    }
    OSPanic("sta_c5.c", 0x637, noReturnValueString);
    return 0;
}

// .text:0x000F5C30 size:0x248 mapped:0x80734CC4
void fn_3_F5C30(DKJungleCannon* cannon) {
    DKJungleCannonEmitter* emitter;

    cannon->pos.x = barrelLauncherDataStruct[cannon->index].pos.x;
    cannon->pos.y = barrelLauncherDataStruct[cannon->index].pos.y;
    cannon->pos.z = barrelLauncherDataStruct[cannon->index].pos.z;
    cannon->rotY = -barrelLauncherDataStruct[cannon->index].rotY;
    cannon->ctrlType = 0;
    CTRLSetTranslation((Control*)cannon, cannon->pos.x, -cannon->pos.y, cannon->pos.z);
    CTRLSetRotation((Control*)cannon, 0.0f, cannon->rotY, 0.0f);
    cannon->vel.x = cannon->vel.y = cannon->vel.z = 0.0f;

    emitter = cannon->emitter;
    if (emitter != NULL) {
        if (emitter->_08 != 0) {
            fn_80033964(emitter);
            cannon->emitter = NULL;
        } else {
            cannon->emitter = NULL;
        }
    }

    if (cannon->barrel != NULL) {
        fn_3_F3BB0(cannon->barrel);
    }

    cannon->_99 = 1;
    cannon->mode = 0;
    if (barrelRollSfxEmitterId != -1) {
        updateAndRemoveStadiumEmitter(barrelRollSfxEmitterId);
        barrelRollSfxEmitterId = -1;
    }
}

// .text:0x000F56CC size:0x564 mapped:0x80734760
void dkJungleBarrelCannonUpdate(StadiumObject* o) {
    DKJungleCannon* cannon = (DKJungleCannon*)o;
    DKJungleBss* bss = (DKJungleBss*)&lbl_3_bss_AEE0;
    u32 status;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        return;
    }
    status = g_GameLogic.gameStatus;
    if (status == GAME_STATUS_INNING_TRANSITION) {
        fn_3_F5C30(cannon);
        cannon->callback = dkJungleBarrelCannonCutsceneUpdate;
    } else if (status != GAME_STATUS_LIVE_BALL) {
        if (status == GAME_STATUS_DEFAULT) {
            fn_3_F5C30(cannon);
        }
        if (bss->_01 != 0) {
            bss->_01 = 0;
        }
        if (bss->_02 != 0) {
            bss->_02 = 0;
        }
    } else {
        if (cannon->_99 != 0) {
            cannon->_99 = 0;
        }
        if (cannon->barrel != NULL) {
            handleDKJungleBarrel(cannon->barrel);
        }
        switch (cannon->mode) {
        case 0:
        case 1:
        case 2:
            handleBarrelFiring(cannon);
            break;
        case 3:
            fn_3_F4D00(cannon);
            break;
        }
    }
}

// .text:0x000F4FBC size:0x710 mapped:0x80734050
void handleBarrelFiring(DKJungleCannon* cannon) {
    DKJungleBss* bss = (DKJungleBss*)&lbl_3_bss_AEE0;
    Vec v;
    Vec v2;
    Vec forward = {0.0f, 0.0f, -1.0f};
    f32 dot;
    f32 angle;
    f32 dist;

    if (g_Ball.deadBallReason == 0) {
        v.x = g_Ball.AtBat_Contact_BallPos.x - cannon->pos.x;
        v.y = 0.0f;
        v.z = g_Ball.AtBat_Contact_BallPos.z - cannon->pos.z;
        PSVECNormalize(&v, &v);
        dot = PSVECDotProduct(&v, &forward);
        if (dot > 1.0f) {
            dot = 1.0f;
        } else if (dot < -1.0f) {
            dot = -1.0f;
        }
        angle = 57.29578f * (f32)acos(dot);
        if (angle > 90.0f) {
            angle = 90.0f;
        }
        if (v.x < 0.0f) {
            angle = 360.0f - angle;
        }
        cannon->rotY = -angle;
        CTRLSetRotation((Control*)cannon, 0.0f, cannon->rotY, 0.0f);
    }

    switch (cannon->mode) {
    case 0:
        if (g_Ball.AtBat_ContactResult < BALL_RESULT_TYPE_FIELDED) {
            if (bss->_02 == 0) {
                bss->_02 = 1;
                if (rng(100) + 1 > 0x3F) {
                    bss->_01 = 1;
                }
            }
            if (bss->_01 == 0) {
                fn_3_F4DAC();
                bss->_01 = 1;
            }
        }
        break;
    case 1:
        if (g_Ball.physicsSubstruct.velocity.y < 0.0f) {
            cannon->barrel->_C1 = 1;
            fn_3_F4C4C(cannon);
            cannon->mode = 3;
            v.x = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
            v.y = 0.0f;
            v.z = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
            dist = PSVECMag(&v);
            if (dist > 68.0f) {
                PSVECNormalize(&v, &v2);
                PSVECScale(&v2, 68.0f, &v);
            }
            if (dist < 52.0f) {
                PSVECNormalize(&v, &v2);
                PSVECScale(&v2, 52.0f, &v);
            }
            dkBarrelLaunch(cannon->barrel, v.x, v.z);
            dkPlayHazardSfx(0);
        }
        break;
    case 2:
        v.x = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
        v.y = 0.0f;
        v.z = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
        if (g_Ball.AtBat_ContactResult >= BALL_RESULT_TYPE_FIELDED) {
            cannon->mode = 0;
        } else if (PSVECMag(&v) > 52.0f) {
            if (v.z < 45.0f) {
                v.z = 45.0f;
            }
            dkBarrelLaunch(cannon->barrel, v.x, v.z);
            fn_3_F4C4C(cannon);
            cannon->barrel->_C1 = 1;
            cannon->mode = 3;
            dkPlayHazardSfx(0);
        }
        break;
    }
}

// .text:0x000F4DAC size:0x210 mapped:0x80733E40
void fn_3_F4DAC(void) {
    Vec landing;
    Vec dir;
    Vec forward = {0.0f, 0.0f, 1.0f};
    u8 accum = 100 / nBarrelLaunchers;
    u8 i = 0;
    u8 roll;
    f32 dist;
    f32 angle;
    f32 t;
    DKJungleCannon* cannon;

    landing.x = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
    landing.y = 0.0f;
    landing.z = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
    PSVECNormalize(&landing, &dir);
    dist = PSVECMag(&landing);
    angle = 57.29578f * (f32)acos(PSVECDotProduct(&dir, &forward));

    if (angle < 18.0f) {
        roll = rng(100);
        while (roll / accum != 0) {
            accum += 100 / nBarrelLaunchers;
            i++;
        }
        cannon = (DKJungleCannon*)&stadiumObjectCollision.objects[i + gFirstCannonPoolIndex];
    } else if (dir.x < 0.0f) {
        cannon = (DKJungleCannon*)&stadiumObjectCollision.objects[gFirstCannonPoolIndex];
    } else {
        cannon = (DKJungleCannon*)&stadiumObjectCollision.objects[gFirstCannonPoolIndex + 1];
    }

    t = angle / 45.0f;
    if (!(dist > 90.0 * (1.0 - t) + 73.0f * t)) {
        if (dist > 52.0f) {
            cannon->mode = 1;
        } else {
            cannon->mode = 2;
        }
    }
}

// .text:0x000F4D00 size:0xAC mapped:0x80733D94
void fn_3_F4D00(DKJungleCannon* cannon) {
    Vec toLauncher;
    Vec launcherPos;

    PSVECAdd(&cannon->pos, &cannon->vel, &cannon->pos);
    CTRLSetTranslation((Control*)cannon, cannon->pos.x, -cannon->pos.y, cannon->pos.z);
    launcherPos.x = barrelLauncherDataStruct[cannon->index].pos.x;
    launcherPos.y = barrelLauncherDataStruct[cannon->index].pos.y;
    launcherPos.z = barrelLauncherDataStruct[cannon->index].pos.z;
    PSVECSubtract(&launcherPos, &cannon->pos, &toLauncher);
    cannon->vel.x = 0.2f * toLauncher.x;
    cannon->vel.z = 0.2f * toLauncher.z;
}

// .text:0x000F4C4C size:0xB4 mapped:0x80733CE0
void fn_3_F4C4C(DKJungleCannon* cannon) {
    f32 rad = cannon->rotY;
    f32 angle;
    f32 c;

    rad = -rad;
    angle = 0.017453292f * rad;

    cannon->vel.x = 3.0f * (f32)sin(angle);
    cannon->vel.y = 0.0f;
    c = (f32)cos(angle);
    cannon->vel.z = -c * 3.0f;
    PSVECScale(&cannon->vel, -1.0f, &cannon->vel);
}

// .text:0x000F4BA0 size:0xAC mapped:0x80733C34
void fn_3_F4BA0(DKJungleCannon* cannon) {
    Vec launcherPos;
    Vec toLauncher;

    PSVECAdd(&cannon->pos, &cannon->vel, &cannon->pos);
    CTRLSetTranslation((Control*)cannon, cannon->pos.x, -cannon->pos.y, cannon->pos.z);
    launcherPos.x = barrelLauncherDataStruct[cannon->index].pos.x;
    launcherPos.y = barrelLauncherDataStruct[cannon->index].pos.y;
    launcherPos.z = barrelLauncherDataStruct[cannon->index].pos.z;
    PSVECSubtract(&launcherPos, &cannon->pos, &toLauncher);
    cannon->vel.x = 0.2f * toLauncher.x;
    cannon->vel.z = 0.2f * toLauncher.z;
}

// .text:0x000F46A0 size:0x500 mapped:0x80733734
void dkJungleBarrelCannonCutsceneUpdate(StadiumObject* o) {
    DKJungleCannon* cannon = (DKJungleCannon*)o;
    Vec v;
    Vec forward = {0.0f, 0.0f, -1.0f};
    f32 angle;

    v.x = lbl_3_bss_AEE8.launchX - cannon->pos.x;
    v.y = 0.0f;
    v.z = lbl_3_data_1BA48 - cannon->pos.z;
    PSVECNormalize(&v, &v);
    angle = 57.29578f * (f32)acos(PSVECDotProduct(&v, &forward));
    if (v.x < 0.0f) {
        angle = 360.0f - angle;
    }
    cannon->rotY = -angle;
    CTRLSetRotation((Control*)cannon, 0.0f, cannon->rotY, 0.0f);

    if (g_GameLogic.gameStatus != GAME_STATUS_INNING_TRANSITION) {
        fn_3_F5C30(cannon);
        cannon->callback = dkJungleBarrelCannonUpdate;
    } else {
        handleDKJungleBarrel(cannon->barrel);
        switch (cannon->mode) {
        case 0:
            if (lbl_3_bss_AEE0._01 == 0) {
                dkBarrelLaunch(cannon->barrel, lbl_3_bss_AEE8.launchX, lbl_3_data_1BA48);
                fn_3_F4C4C(cannon);
                cannon->barrel->_C1 = 1;
                cannon->mode = 3;
                lbl_3_bss_AEE0._01 = 1;
                dkPlayHazardSfx(0);
            }
            break;
        case 3:
            fn_3_F4BA0(cannon);
            if (cannon->barrel->_C1 == 0) {
                lbl_3_bss_AEE0._01 = 0;
            }
            break;
        }
    }
}

// .text:0x000F469C size:0x4 mapped:0x80733730
void fn_3_F469C(void) {
    return;
}

// .text:0x000F466C size:0x30 mapped:0x80733700
void fn_3_F466C(void) {
    processFielderAutoCatch();
    g_FieldingLogic.knockoutFinished = 1;
}

// .text:0x000F42A0 size:0x3CC mapped:0x80733334
void dkBarrelSpawnSmoke(void) {
    DKJungleSmokeEmitter* emitter = allocParticleEffect((void*)dkBarrelSmokeUpdate, 0x80, 0, 8, 1, 0);

    if (emitter != NULL) {
        dkBarrelSmokeInit(emitter);
    }
}

// .text:0x000F3EFC size:0x3A4 mapped:0x80732F90
void dkBarrelSmokeInit(DKJungleSmokeEmitter* emitter) {
    DKJungleSmokeParticle* p = emitter->particles;
    u8 i = 0;

    emitter->_10 = lbl_3_bss_B560[0];
    for (; p != NULL; p = p->next) {
        p->_38 = p->_3C = 10.0f;
        p->vel.x = p->vel.z = 0.0f;
        p->vel.y = -0.05f;
        p->pos.x = bezierControlPoints[0] + (f64)(rand() % 600 - 300) / 100.0;
        p->pos.y = -16.5 + (f64)(rand() % 600 - 300) / 100.0;
        p->pos.z = bezierControlPoints[2] + (f64)(rand() % 600 - 300) / 100.0;
        p->_28 = 25.0 + (f32)(rand() % 300 - 150) / 10.0f;
        p->_2C = 40.0 + (f32)(rand() % 300 - 150) / 10.0f;
        p->index = i;
        p->_48 = i;
        p->color[2] = 0xFF;
        p->color[1] = 0xFF;
        p->color[0] = 0xFF;
        p->alpha = 0;
        p->_4A = 500 - p->index;
        p->_1C = 0.3 + (f32)(rand() % 50) / 100.0f;
        p->_20 = 0.0f;
        p->_24 = (f32)(1 - rand() % 2 * 2);
        i++;
        p->_4D = 0xF;
        p->_4E = 0;
    }
}

// .text:0x000F3CD0 size:0x22C mapped:0x80732D64
BOOL dkBarrelSmokeUpdate(DKJungleSmokeEmitter* emitter) {
    DKJungleSmokeParticle* p = emitter->particles;
    int alive = 0;

    fn_80033620(emitter);
    do {
        if (p->_48 <= 0 && p->_4A != 0) {
            setParticleXform(p->_38, p->_3C, p->_20);
            fn_80033CC8(p, emitter->_10);
            if (-p->_48 < 5) {
                p->_38 += (p->_28 - 10.0) / 5.0;
                p->_3C = p->_38;
                p->alpha += 12.0;
            } else {
                p->_38 = p->_38 + (p->_2C - p->_28) / 495.0f;
                p->_3C = p->_38;
                p->alpha = p->alpha + -60.0 / (0x1EF - p->index);
                if (p->alpha >= 0x3C) {
                    p->alpha = 0;
                }
            }
            p->pos.x += p->vel.x;
            p->pos.y += p->vel.y;
            p->pos.z += p->vel.z;
            p->_20 = p->_1C * p->_24 + p->_20;
            p->_4A--;
        }
        p->_48--;
        if (p->_4A != 0) {
            alive++;
        }
        p = p->next;
    } while (p != NULL);
    return alive == 0;
}

// .text:0x000F3BB0 size:0x120 mapped:0x80732C44
void fn_3_F3BB0(DKJungleBarrel* obj) {
    fn_3_F3AE0(obj);
    obj->_C1 = 0;
    obj->hasShadow = 1;
    obj->actor = (DKJungleActor*)(*(u8**)(hugeAnimStruct + 0x6C) + (lbl_3_bss_B219 + obj->index) * 0x90 + 0x34);
    obj->_C4 = 0;
    obj->_99 = 1;
}

// .text:0x000F3AE0 size:0xD0 mapped:0x80732B74
void fn_3_F3AE0(DKJungleBarrel* obj) {
    obj->rotY = barrelLauncherDataStruct[obj->index].pos.x;
    obj->_B0 = barrelLauncherDataStruct[obj->index].pos.z;
    fn_3_F3A5C(obj, obj->rotY, 10.0f, obj->_B0, -barrelLauncherDataStruct[obj->index].rotY);
}

// .text:0x000F3A5C size:0x84 mapped:0x80732AF0
void fn_3_F3A5C(DKJungleBarrel* obj, f32 x, f32 y, f32 z, f32 angle) {
    obj->pos.x = x;
    obj->pos.y = y;
    obj->pos.z = z;
    obj->_B4 = angle;
    obj->ctrlType = 0;
    CTRLSetTranslation((Control*)obj, obj->pos.x, -obj->pos.y, obj->pos.z);
    CTRLSetRotation((Control*)obj, 0.0f, angle, 0.0f);
}

// .text:0x000F3A04 size:0x58 mapped:0x80732A98
void fn_3_F3A04(DKJungleObject* obj) {
    DKJungleAnimList* list = obj->actor->list;
    u32 i;
    for (i = 0; i < list->count; i++) {
    }
}

// .text:0x000F38D4 size:0x130 mapped:0x80732968
void initBinomialTable(void) {
    u32 i;

    for (i = 0; i < 7; i++) {
        bezierFactors[i] = binomialCoefficient(6, i);
    }
}

// .text:0x000F37BC size:0x118 mapped:0x80732850
u32 binomialCoefficient(u32 n, u32 k) {
    u32 result = 1;
    u32 i;

    for (i = 1; i <= k; i++) {
        result = result * (n - i + 1) / i;
    }
    return result;
}

// .text:0x000F31E0 size:0x5DC mapped:0x80732274
void dkBarrelLaunch(DKJungleBarrel* barrel, f32 x, f32 z) {
    DKJungleSmokeEmitter* emitter;
    f32 angle;

    lbl_3_bss_B224 = 0.01f;
    barrel->velY = 0.7f;
    fn_3_F2FFC(barrel, x, z);

    emitter = allocParticleEffect((void*)dkBarrelSmokeUpdate, 0x80, 0, 8, 1, 0);
    if (emitter != NULL) {
        dkBarrelSmokeInit(emitter);
    }

    angle = *barrel->pathAngle;
    barrel->pos.x = bezierControlPoints[0];
    barrel->pos.y = 16.5f;
    barrel->pos.z = bezierControlPoints[2];
    barrel->_B4 = angle;
    barrel->ctrlType = 0;
    CTRLSetTranslation((Control*)barrel, barrel->pos.x, -barrel->pos.y, barrel->pos.z);
    CTRLSetRotation((Control*)barrel, 0.0f, angle, 0.0f);
    lbl_3_bss_AEE0.frame = 0;
}

// .text:0x000F2FFC size:0x1E4 mapped:0x80732090
void fn_3_F2FFC(DKJungleBarrel* barrel, f32 x, f32 z) {
    Vec dir;
    s8 sign;
    f32 diff;

    diff = x - barrel->rotY;
    sign = diff / fabs(diff);
    if (sign == 0) {
        sign = -(barrel->rotY / fabs(barrel->rotY));
    }
    dir.x = x - barrel->rotY;
    dir.y = 0.0f;
    dir.z = z - barrel->_B0;
    PSVECNormalize(&dir, &dir);
    bezierControlPoints[0] = 10.0f * dir.x + barrel->rotY;
    bezierControlPoints[1] = 0.0f;
    bezierControlPoints[2] = 10.0f * dir.z + barrel->_B0;
    bezierControlPoints[3] = 0.33333334f * (x - barrel->rotY) + barrel->rotY;
    bezierControlPoints[4] = 0.0f;
    bezierControlPoints[5] = 0.33333334f * (z - barrel->_B0) + barrel->_B0;
    bezierControlPoints[6] = 0.6666667f * (x - barrel->rotY) + barrel->rotY;
    bezierControlPoints[7] = 0.0f;
    bezierControlPoints[8] = 0.6666667f * (z - barrel->_B0) + barrel->_B0;
    bezierControlPoints[9] = x;
    bezierControlPoints[10] = 0.0f;
    bezierControlPoints[11] = z;
    bezierControlPoints[12] = x + ((f32)(sign * 80) - x) / 3.0f;
    bezierControlPoints[13] = 0.0f;
    bezierControlPoints[14] = z;
    bezierControlPoints[15] = x + 2.0f * ((f32)(sign * 80) - x) / 3.0f;
    bezierControlPoints[16] = 0.0f;
    bezierControlPoints[17] = z;
    bezierControlPoints[18] = (f32)(sign * 80);
    bezierControlPoints[19] = 0.0f;
    bezierControlPoints[20] = z;
}

// .text:0x000F2938 size:0x6C4 mapped:0x807319CC
void dkBarrelAdvanceMotion(DKJungleBarrel* barrel) {
    Vec pt;
    Vec vel;
    Vec heading = { 0.0f, 0.0f, -1.0f };
    f32 oneMinusT;
    f32 t;
    f32 angle;
    u32 i;
    DKJungleKlaptrap* klaptrap;

    t = 0.42f * lbl_3_bss_B224 * (f32)lbl_3_bss_AEE0.frame;
    oneMinusT = 1.0f - t;
    for (i = 0; i < 7; i++) {
        lbl_3_bss_B228[i] = bezierFactors[i] * pow(t, i) * pow(oneMinusT, 6 - i);
    }
    pt = barrel->pos;
    pt.z = pt.x = 0.0f;
    for (i = 0; i < 7; i++) {
        pt.x += lbl_3_bss_B228[i] * bezierControlPoints[i * 3];
        pt.z += lbl_3_bss_B228[i] * bezierControlPoints[i * 3 + 2];
    }
    pt.y += barrel->velY;
    PSVECSubtract(&pt, &barrel->pos, &vel);
    if (pt.y < 0.0f) {
        pt.y = 0.0f;
        barrel->velY = 0.5f * -barrel->velY;
        if (barrel->velY > 0.022f) {
            dkPlayHazardSfx(1);
        } else if (barrelRollSfxEmitterId == -1) {
            barrelRollSfxEmitterId = initializeStadiumObjectEmitter(stadiumHazardSoundIDs[g_d_GameSettings.StadiumID] + 2, &pt, &vel, 3);
        } else {
            updateOrRemoveEmitter(barrelRollSfxEmitterId, &pt, &vel);
        }
    }
    barrel->velY -= 0.044f;
    vel.y = 0.0f;
    if (PSVECMag(&vel) != 0.0f) {
        PSVECNormalize(&vel, &vel);
        PSVECNormalize(&heading, &heading);
        angle = 57.29578f * (f32)acos(PSVECDotProduct(&vel, &heading));
        if (vel.x < 0.0f) {
            angle = 360.0f - angle;
        }
    } else {
        angle = -barrel->_B4;
    }
    angle = -angle;
    barrel->pos.x = pt.x;
    barrel->pos.y = pt.y;
    barrel->pos.z = pt.z;
    barrel->_B4 = angle;
    barrel->ctrlType = 0;
    CTRLSetTranslation((Control*)barrel, barrel->pos.x, -barrel->pos.y, barrel->pos.z);
    CTRLSetRotation((Control*)barrel, 0.0f, angle, 0.0f);
    if (barrel->pos.y < 0.5 && barrel->velY <= 0.0f) {
        for (i = 0; i < numObjects; i++) {
            klaptrap = (DKJungleKlaptrap*)&stadiumObjectCollision.objects[objectIndex + i];
            if (klaptrap->state < 3) {
                fn_3_F2724(barrel, klaptrap);
            }
        }
    }
    dkBarrelSpawnGroundDust(barrel);
    lbl_3_bss_AEE0.frame++;
}

// .text:0x000F2724 size:0x214 mapped:0x807317B8
void fn_3_F2724(DKJungleBarrel* barrel, DKJungleKlaptrap* klaptrap) {
    Vec v;
    f32 cosA;
    f32 sinA;
    f32 sinB;
    f32 cosB;
    f32 alongX;
    f32 alongZ;
    f32 absX;
    f32 absZ;

    sin(-(0.017453292f * barrel->_B4));
    cos(-(0.017453292f * barrel->_B4));
    PSVECSubtract(&klaptrap->pos, &barrel->pos, &v);
    v.y = 0.0f;
    cosA = (f32)cos(-(0.017453292f * barrel->_B4));
    sinA = (f32)sin(-(0.017453292f * barrel->_B4));
    sinB = (f32)sin(-(0.017453292f * barrel->_B4));
    cosB = (f32)cos(-(0.017453292f * barrel->_B4));
    alongX = v.x * cosA + v.z * sinA;
    alongZ = v.x * -sinB + v.z * cosB;
    absZ = fabs(alongZ);
    absX = fabs(alongX);
    if (absX <= 3.0 && absZ <= 1.75) {
        klaptrap->state = 5;
        dkPlayHazardSfx(0xb);
    }
}

// .text:0x000F2448 size:0x2DC mapped:0x807314DC
s8 dkBarrel_collisionWithFielder(DKJungleBarrel* barrel) {
    Vec dir;
    Vec offset;
    u8 fielderOrder[7] = { 2, 3, 4, 5, 6, 7, 8 };
    u32 i;
    InMemFielder* fielder;
    f32 range;
    f32 cosA;
    f32 sinA;
    f32 sinB;
    f32 cosB;
    f32 alongX;
    f32 alongZ;
    f32 absX;
    f32 absZ;
    int stadiumID;
    u8 vol;
    u8 val;
    SND_VOICEID voice;

    sin(-(0.017453292f * barrel->_B4));
    cos(-(0.017453292f * barrel->_B4));
    for (i = 0; i < 7; i++) {
        fielder = &g_Fielders[fielderOrder[i]];
        memset(&offset, 0, sizeof(Vec));
        getAnimationCollisionOffset(fielderOrder[i], 4, &offset);
        offset.y *= -1.0f;
        if (offset.y < barrel->pos.y) {
            range = fielder->hitbox_barrelCollisions;
        } else {
            range = 4.6666665f;
        }
        if (!(range < fabs(offset.y - barrel->pos.y)) && fielder != NULL && fielder->knockoutStatus == 0) {
            PSVECSubtract((Vec*)&fielder->pos, &barrel->pos, &dir);
            cosA = (f32)cos(-(0.017453292f * barrel->_B4));
            sinA = (f32)sin(-(0.017453292f * barrel->_B4));
            sinB = (f32)sin(-(0.017453292f * barrel->_B4));
            cosB = (f32)cos(-(0.017453292f * barrel->_B4));
            alongX = dir.x * cosA + dir.z * sinA;
            alongZ = dir.x * -sinB + dir.z * cosB;
            absZ = fabs(alongZ);
            absX = fabs(alongX);
            if (absX <= 3.0 && absZ <= 1.75) {
                stadiumID = g_d_GameSettings.StadiumID;
                vol = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD ? lbl_3_data_84B8[8]
                                                                               : stadiumHazardSoundFxRelated[stadiumID * 0x1E + 8];
                voice = sndFXStartEx(stadiumHazardSoundIDs[stadiumID] + 4, vol, 0x3F, 0);
                val = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD ? lbl_3_data_84B8[9]
                                                                               : stadiumHazardSoundFxRelated[stadiumID * 0x1E + 9];
                sndFXCtrl(voice, 0x5B, val);
                return fielderOrder[i];
            }
        }
    }
    return -1;
}

// .text:0x000F22FC size:0x14C mapped:0x80731390
void dkBarrelKnockFielder(DKJungleBarrel* barrel, s8 fielderIdx) {
    Vec dir;
    int idx = fielderIdx;
    InMemFielder* fielder = &g_Fielders[idx];
    u8* attached;
    DKJungleKlaptrap* klaptrap;
    u32 i;
    int angle;

    PSVECSubtract((Vec*)&fielder->pos, &barrel->pos, &dir);
    dir.y = 0.0f;
    PSVECNormalize(&dir, &dir);
    angle = calculateAngleFromCoordinates(dir.x, dir.z);
    processFielderKnockout(idx, angle);
    isWorldPosOnScreen(&barrel->pos);
    attached = &fielder->attachedKlaptrapCount;
    for (i = 0; i < numObjects; i++) {
        klaptrap = (DKJungleKlaptrap*)&stadiumObjectCollision.objects[objectIndex + i];
        if (klaptrap->state == 3 && klaptrap->_C1 == fielderIdx) {
            klaptrap->hitAngle = 0.017453292f * (-klaptrap->rotY - 180.0f);
            klaptrap->state = 4;
            klaptrap->_BC = 0.5f;
            (*attached)--;
        }
    }
}

// .text:0x000F1E2C size:0x4D0 mapped:0x80730EC0
void dkBarrelSpawnGroundDust(DKJungleBarrel* barrel) {
    DKJungleKlaptrapTuning* tune = (DKJungleKlaptrapTuning*)&barrelRollSfxEmitterId;
    VecSrcDst probe;
    CollisionStruct hit;
    Vec puffRight;
    Vec puffLeft;
    Vec center;
    Vec forward = { 0.0f, 0.0f, -1.0f };
    f32 angle;
    f32 sinA;
    f32 cosA;
    u32 hitLeft;
    u32 hitCenter;
    u32 hitRight;

    if (barrel->pos.y > 0.0f) {
        return;
    }
    angle = -(0.017453292f * barrel->_B4);
    sinA = (f32)sin(angle);
    cosA = (f32)cos(angle);
    center.x = 5.5 * (forward.x * cosA + forward.z * -sinA);
    cosA = (f32)cos(angle);
    sinA = (f32)sin(angle);
    center.z = 5.5 * (forward.x * sinA + forward.z * cosA);
    PSVECAdd(&center, &barrel->pos, &center);
    center.y = 0.0f;
    probe.src.x = probe.dst.x = center.x;
    probe.src.z = probe.dst.z = center.z;
    probe.src.y = -1.0f;
    probe.dst.y = 1.0f;
    hitCenter = checkCollision(&probe, &hit, 0, FALSE) & 0x7F;
    if (hitCenter == BALL_COLLISION_TYPE_WATER) {
        if (barrel->_C4 % tune->barrelDustInterval != 0) {
            barrel->_C4++;
            return;
        }
        spawnDustPuff(&probe.src, 1, 0.0f, tune->barrelDustHeight);
    }

    sinA = (f32)sin(angle);
    cosA = (f32)cos(angle);
    probe.src.x = tune->dustOffset[0][0] * cosA + tune->dustOffset[0][1] * -sinA;
    cosA = (f32)cos(angle);
    sinA = (f32)sin(angle);
    probe.src.z = tune->dustOffset[0][0] * sinA + tune->dustOffset[0][1] * cosA;
    PSVECAdd(&center, &probe.src, &probe.src);
    probe.dst.x = probe.src.x;
    probe.dst.z = probe.src.z;
    probe.src.y = -1.0f;
    probe.dst.y = 1.0f;
    hitLeft = checkCollision(&probe, &hit, 0, FALSE) & 0x7F;
    if (hitLeft == BALL_COLLISION_TYPE_WATER) {
        if (barrel->_C4 % tune->barrelDustInterval != 0) {
            barrel->_C4++;
            return;
        }
        spawnDustPuff(&probe.src, 1, 0.0f, tune->barrelDustHeight);
    }

    sinA = (f32)sin(angle);
    cosA = (f32)cos(angle);
    probe.src.x = tune->dustOffset[1][0] * cosA + tune->dustOffset[1][1] * -sinA;
    cosA = (f32)cos(angle);
    sinA = (f32)sin(angle);
    probe.src.z = tune->dustOffset[1][0] * sinA + tune->dustOffset[1][1] * cosA;
    PSVECAdd(&center, &probe.src, &probe.src);
    probe.dst.x = probe.src.x;
    probe.dst.z = probe.src.z;
    probe.src.y = -1.0f;
    probe.dst.y = 1.0f;
    hitRight = checkCollision(&probe, &hit, 0, FALSE) & 0x7F;
    if (hitRight == BALL_COLLISION_TYPE_WATER) {
        if (barrel->_C4 % tune->barrelDustInterval != 0) {
            barrel->_C4++;
            return;
        }
        spawnDustPuff(&probe.src, 1, 0.0f, tune->barrelDustHeight);
    }

    if (hitCenter == BALL_COLLISION_TYPE_WATER) {
        if (hitLeft == BALL_COLLISION_TYPE_WATER) {
            PSVECSubtract(&probe.src, &center, &puffRight);
            puffRight.x *= 0.5f;
            puffRight.z *= 0.5f;
            PSVECAdd(&puffRight, &center, &puffRight);
            spawnDustPuff(&puffRight, 1, 0.0f, tune->barrelDustHeight);
        }
        if (hitRight == BALL_COLLISION_TYPE_WATER) {
            PSVECSubtract(&probe.src, &center, &puffLeft);
            puffLeft.x *= 0.5f;
            puffLeft.z *= 0.5f;
            PSVECAdd(&puffLeft, &center, &puffLeft);
            spawnDustPuff(&puffLeft, 1, 0.0f, tune->barrelDustHeight);
        }
    }
    barrel->_C4 += ((hitCenter | hitLeft | hitRight) & BALL_COLLISION_TYPE_WATER) != 0;
}

// .text:0x000F193C size:0x4F0 mapped:0x807309D0
void handleDKJungleBarrel(DKJungleBarrel* barrel) {
    DKJungleBss* bss = (DKJungleBss*)&lbl_3_bss_AEE0;
    DKJungleActor* actor = barrel->actor;
    VecSrcDst probe;
    CollisionStruct hit;
    u32 type;
    s8 fielderIdx;
    f32 angle;
    u32 i;
    u32 count;

    switch (barrel->_C1) {
    case 0:
        angle = *barrel->pathAngle;
        barrel->_B4 = angle;
        barrel->ctrlType = 0;
        CTRLSetTranslation((Control*)barrel, barrel->pos.x, -barrel->pos.y, barrel->pos.z);
        CTRLSetRotation((Control*)barrel, 0.0f, angle, 0.0f);
        break;
    case 1:
        if (barrel->hasShadow == 0) {
            barrel->hasShadow = 1;
        }
        memcpy(&probe.src, &barrel->pos, sizeof(Vec));
        probe.src.y *= -1.0f;
        dkBarrelAdvanceMotion(barrel);
        memcpy(&probe.dst, &barrel->pos, sizeof(Vec));
        probe.dst.y *= -1.0f;
        AnimateActorBones(actor->list);
        type = checkCollision(&probe, &hit, 0, FALSE) & 0xF;
        if (type == BALL_COLLISION_TYPE_WALL || type == BALL_COLLISION_TYPE_UNCLIMBABLE_WALL) {
            barrel->_C1 = 2;
            updateAndRemoveStadiumEmitter(barrelRollSfxEmitterId);
            barrelRollSfxEmitterId = -1;
            dkPlayHazardSfx(3);
            count = barrel->actor->list->count;
            for (i = 0; i < count; i++) {
            }
            fn_3_F18A4(barrel);
        } else if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL) {
            fielderIdx = dkBarrel_collisionWithFielder(barrel);
            if (fielderIdx > -1) {
                dkBarrelKnockFielder(barrel, fielderIdx);
            }
        }
        break;
    case 2:
        fn_3_F1750(barrel);
        break;
    }
}

// .text:0x000F18A4 size:0x98 mapped:0x80730938
void fn_3_F18A4(DKJungleBarrel* obj) {
    DKJungleActor* actor;

    obj->actor = actor = (DKJungleActor*)(*(u8**)(hugeAnimStruct + 0x6C) + lbl_3_bss_B218 * 0x90 + 0x34);
    actor->animFrame = 0.0f;
    actor->_59 = 1;
    setActorAnimFrame(actor->list, actor->animFrame);
    obj->_B4 += 180.0;
    AnimateActorBones(actor->list);
}

// .text:0x000F1750 size:0x154 mapped:0x807307E4
void fn_3_F1750(DKJungleBarrel* obj) {
    DKJungleActor* actor = obj->actor;
    f32 angle;
    f32 scan;

    scan = scanBoneAttachmentData(actor->list);
    if (!scan) {
        obj->rotY = barrelLauncherDataStruct[obj->index].pos.x;
        obj->_B0 = barrelLauncherDataStruct[obj->index].pos.z;
        angle = -barrelLauncherDataStruct[obj->index].rotY;
        obj->pos.x = obj->rotY;
        obj->pos.y = 10.0f;
        obj->pos.z = obj->_B0;
        obj->_B4 = angle;
        obj->ctrlType = 0;
        CTRLSetTranslation((Control*)obj, obj->pos.x, -obj->pos.y, obj->pos.z);
        CTRLSetRotation((Control*)obj, 0.0f, angle, 0.0f);
        obj->_C1 = 0;
        obj->hasShadow = 1;
        obj->actor = (DKJungleActor*)(*(u8**)(hugeAnimStruct + 0x6C) + (lbl_3_bss_B219 + obj->index) * 0x90 + 0x34);
        obj->_C4 = 0;
        obj->_99 = 1;
    } else {
        AnimateActorBones(actor->list);
    }
}

// .text:0x000F1674 size:0xDC mapped:0x80730708
void fn_3_F1674(void) {
    dkPlayHazardSfx(5);
    ballState_thrown_to_holding();
    processFielderAutoCatch();
    g_FieldingLogic.knockoutFinished = 1;
}

// .text:0x000F1518 size:0x15C mapped:0x807305AC
void maybeGharialCTRLRel(DKJungleKlaptrap* obj) {
    obj->kind = jungleKlaptrapData[obj->index].kind;
    obj->state = 1;
    obj->timer = 0;
    obj->_C1 = -1;
    if (!obj->hasShadow) {
        obj->hasShadow = 1;
    }
    obj->_99 = 1;
    obj->_B0 = 0.0f;
    obj->pos.x = jungleKlaptrapData[obj->index].pos.x;
    obj->pos.y = jungleKlaptrapData[obj->index].pos.y;
    obj->pos.z = jungleKlaptrapData[obj->index].pos.z;
    obj->rotY = -jungleKlaptrapData[obj->index].rotY;
    obj->ctrlType = 0;
    CTRLSetTranslation((Control*)obj, obj->pos.x, -obj->pos.y, obj->pos.z);
    CTRLSetRotation((Control*)obj, 0.0f, obj->rotY, 0.0f);
    CTRLSetScale((Control*)obj, 1.0f, 1.0f, 1.0f);
    actorSetAnimBank((ACTActor*)obj->actor, lbl_3_bss_B154.animBank[0]);
    obj->actor->applyAnimation = 1;
    obj->_C0 = 0;
}

// .text:0x000F1448 size:0xD0 mapped:0x807304DC
void klaptrapCTRLSetup(DKJungleKlaptrap* obj) {
    obj->pos.x = jungleKlaptrapData[obj->index].pos.x;
    obj->pos.y = jungleKlaptrapData[obj->index].pos.y;
    obj->pos.z = jungleKlaptrapData[obj->index].pos.z;
    obj->rotY = -jungleKlaptrapData[obj->index].rotY;
    obj->ctrlType = 0;
    CTRLSetTranslation((Control*)obj, obj->pos.x, -obj->pos.y, obj->pos.z);
    CTRLSetRotation((Control*)obj, 0.0f, obj->rotY, 0.0f);
    CTRLSetScale((Control*)obj, 1.0f, 1.0f, 1.0f);
}

// .text:0x000F13F8 size:0x50 mapped:0x8073048C
void fn_3_F13F8(DKJungleObject* obj) {
    DKJungleAnimList* list = obj->actor->list;
    u32 i;
    for (i = 0; i < list->count; i++) {
        DKJungleAnimNode* node = list->nodes[i];
        node->_60 = 0;
        node->_A4 = 0;
    }
    obj->actor->applyAnimation = 0;
}

// .text:0x000F0FA4 size:0x454 mapped:0x80730038
void klaptrapControl(StadiumObject* o) {
    DKJungleKlaptrap* obj = (DKJungleKlaptrap*)o;
    DKJungleActor* actor = obj->actor;

    if (g_GameLogic.gameStatus == GAME_STATUS_PAUSED) {
        return;
    }
    if (g_GameLogic.gameStatus == GAME_STATUS_INNING_TRANSITION) {
        if (obj->_99 == 0) {
            maybeGharialCTRLRel(obj);
        }
        return;
    }
    if (obj->_99 != 0) {
        obj->_99 = 0;
    }
    if (g_GameLogic.gameStatus == GAME_STATUS_DEFAULT) {
        if (obj->state >= 4) {
            maybeGharialCTRLRel(obj);
        }
        return;
    }
    if (actor->applyAnimation != 0) {
        AnimateActorBones(actor->list);
    }
    switch (obj->state) {
    case 0:
    case 1:
        dkKlaptrapRoamUpdate(obj);
        break;
    case 2:
        dkKlaptrapChaseUpdate((StadiumObject*)obj);
        break;
    case 4:
        dkKlaptrapLaunchedUpdate(obj);
        break;
    case 5:
        fn_3_EF890(obj);
        break;
    case 6:
        fn_3_EF800(obj);
        break;
    }
}

// .text:0x000F082C size:0x778 mapped:0x8072F8C0
void dkKlaptrapRoamUpdate(DKJungleKlaptrap* obj) {
    DKJungleKlaptrapTuning* tune = (DKJungleKlaptrapTuning*)&barrelRollSfxEmitterId;
    Vec next;
    InMemFielder* fielder;
    f32 rad;
    BOOL outside;
    u32 i;

    for (i = 0; i < 9; i++) {
        fielder = &g_Fielders[i];
        if (fielder != NULL) {
            if (!isPosOutsideKlaptrapZone(*(Vec*)&fielder->pos, obj->kind) && fielder->jumpY <= 0.0f) {
                obj->_C1 = i;
                obj->state = 2;
                actorSetAnimBank((ACTActor*)obj->actor, lbl_3_bss_B154.animBank[1]);
                return;
            }
        }
    }
    switch (obj->state) {
    case 0:
        fn_3_EF21C(obj);
        if (obj->turnAngle > 0.0f) {
            if (obj->turnAngle < 0.5) {
                obj->rotY += obj->turnDir * obj->turnAngle;
                obj->turnAngle = 0.0f;
            } else {
                obj->rotY += 0.5 * obj->turnDir;
                obj->turnAngle -= 0.5;
            }
            obj->timer++;
        } else {
            obj->timer = 0;
            obj->state = 1;
        }
        break;
    case 1:
        if (obj->timer < 20) {
            obj->timer++;
            rad = 0.017453292f * -obj->rotY;
            {
                f32 c = (f32)cos(rad);
                f32 s = (f32)sin(rad);
                next.x = obj->pos.x + (f32)(0.08 * c);
                next.y = obj->pos.y + 0.0f;
                next.z = obj->pos.z + (f32)(0.08 * s);
            }
            outside = isPosOutsideKlaptrapZone(next, obj->kind) != 0;
            if (outside) {
                DKJungleKlaptrapData* data = (DKJungleKlaptrapData*)((u8*)tune + 0x184) + obj->index;
                Vec toTarget;
                Vec heading;
                Vec cross;
                f32 dot;

                toTarget.x = data->pos.x - obj->pos.x;
                toTarget.y = 0.0f;
                toTarget.z = data->pos.z - obj->pos.z;
                PSVECNormalize(&toTarget, &toTarget);
                rad = -(0.017453292f * obj->rotY);
                heading.x = (f32)cos(rad);
                heading.y = 0.0f;
                heading.z = (f32)sin(rad);
                PSVECNormalize(&heading, &heading);
                dot = PSVECDotProduct(&toTarget, &heading);
                if (dot < -1.0) {
                    dot = -1.0f;
                }
                obj->turnAngle = 57.29578f * (f32)acos(dot);
                PSVECCrossProduct(&toTarget, &heading, &cross);
                if (cross.y < 0.0f) {
                    obj->turnDir = 1;
                } else {
                    obj->turnDir = -1;
                }
                obj->state = 0;
            } else {
                obj->pos.x = next.x;
                obj->pos.y = next.y;
                obj->pos.z = next.z;
            }
        } else {
            if (rng(10) < 8) {
                obj->state = 0;
                obj->turnAngle = rng(60) + 1;
                obj->turnDir = rng(2) * -1 + 1;
            }
            obj->timer = 0;
        }
        fn_3_EF21C(obj);
        break;
    }
    CTRLSetTranslation((Control*)obj, obj->pos.x, -obj->pos.y, obj->pos.z);
    CTRLSetRotation((Control*)obj, 0.0f, obj->rotY, 0.0f);
}

// .text:0x000F0224 size:0x608 mapped:0x8072F2B8
void dkKlaptrapChaseUpdate(StadiumObject* o) {
    DKJungleKlaptrap* obj = (DKJungleKlaptrap*)o;
    Vec next;
    Vec v;
    Vec dir;
    Vec axisX = {1.0f, 0.0f, 0.0f};
    InMemFielder* fielder = &g_Fielders[obj->_C1];
    DKJungleCarrier* carrier = *(DKJungleCarrier**)(hugeAnimStruct + obj->_C1 * 4 + 0x2C50);
    DKJungleKlaptrapTuning* tune = (DKJungleKlaptrapTuning*)&barrelRollSfxEmitterId;
    u8* base = (u8*)&lbl_3_bss_AEE0;
    f32 deg;
    f32 dist;
    u32 i;
    BOOL outside;

    if (isPosOutsideKlaptrapZone(*(Vec*)&fielder->pos, obj->kind)) {
        obj->state = 1;
        obj->_C1 = -1;
        actorSetAnimBank((ACTActor*)obj->actor, *(u32*)(base + 0x274));
        obj->timer = 0;
        return;
    }
    v.x = fielder->pos.x - obj->pos.x;
    v.y = 0.0f;
    v.z = fielder->pos.z - obj->pos.z;
    PSVECNormalize(&v, &dir);
    next.x = 0.12 * dir.x + obj->pos.x;
    next.y = obj->pos.y;
    next.z = 0.12 * dir.z + obj->pos.z;
    outside = fn_3_EF7B4(next, obj->kind) != 0;
    if (!outside) {
        obj->pos.x = next.x;
        obj->pos.y = next.y;
        obj->pos.z = next.z;
    }
    PSVECNormalize(&axisX, &axisX);
    deg = 57.29578f * (f32)acos(PSVECDotProduct(&dir, &axisX));
    if (v.z < 0.0f) {
        deg = 360.0f - deg;
    }
    obj->rotY = -deg;
    memset(&v, 0, sizeof(Vec));
    getAnimationCollisionOffset(obj->_C1, 0x23, &v);
    v.y *= -1.0f;
    dist = sqrt(pow(fielder->pos.x - obj->pos.x, 2.0) + pow(fielder->pos.z - obj->pos.z, 2.0));
    if (dist < 1.25f) {
        if (fabs(v.y) <= 0.5) {
            fn_3_F13F8((DKJungleObject*)obj);
            for (i = 0; i < ((DKJungleBss*)base)->numObjects; i++) {
                if (i != obj->index) {
                    DKJungleKlaptrap* other = (DKJungleKlaptrap*)&stadiumObjectCollision.objects[i + ((DKJungleBss*)base)->objectIndex];
                    if (other->state == 3 && other->_C1 == obj->_C1) {
                        obj->_C0++;
                    }
                }
            }
            obj->timer = 0;
            obj->state = 3;
            if (isWorldPosOnScreen((Vec*)&fielder->pos)) {
                dkPlayHazardSfx(0xa);
            }
            g_Fielders[obj->_C1].attachedKlaptrapCount++;
            obj->_C2 = fielder->CharID;
            obj->_C3 = carrier->ownerId;
        }
    }
    CTRLSetTranslation((Control*)obj, obj->pos.x, -obj->pos.y, obj->pos.z);
    CTRLSetRotation((Control*)obj, 0.0f, obj->rotY, 0.0f);
    fn_3_EF21C(obj);
    obj->timer++;
}

// .text:0x000F0184 size:0xA0 mapped:0x8072F218
void fn_3_F0184(void) {
    u8* base = (u8*)&lbl_3_bss_AEE0;
    DKJungleKlaptrap* obj;
    u32 i;

    if (base[8] != 0) {
        removeCurrentDrawingItem();
        base[8] = 0;
    } else {
        for (i = 0; i < base[0x33C]; i++) {
            obj = (DKJungleKlaptrap*)&stadiumObjectCollision.objects[i + base[0x33B]];
            if (obj != NULL && obj->state == 3) {
                fn_3_EFB54(obj);
            }
        }
    }
}

// .text:0x000EFB54 size:0x630 mapped:0x8072EBE8
void fn_3_EFB54(DKJungleKlaptrap* obj) {
    Quaternion tiltZ;
    Quaternion tiltY;
    Quaternion result;
    Vec axis;
    Vec side;
    Vec flat;
    Vec axisX = {1.0f, 0.0f, 0.0f};
    Vec p;
    Vec offset = {0.0f, 0.0f, 0.0f};
    DKJungleCarrier* carrier;
    f32 ang;
    f32 h;
    f32 r;
    s8 sel;
    int i;

    carrier = (DKJungleCarrier*)*(void**)(hugeAnimStruct + obj->_C1 * 4 + 0x2C50);
    if (carrier != NULL) {
        if (carrier->ownerId != obj->_C3) {
            for (i = 0; i < 9; i++) {
                carrier = (DKJungleCarrier*)*(void**)(hugeAnimStruct + i * 4 + 0x2C50);
                if (carrier != NULL && obj->_C3 == carrier->ownerId) {
                    obj->_C1 = carrier->animIdx;
                    break;
                }
            }
        }
        if (carrier != NULL) {
            memset(&offset, 0, sizeof(Vec));
            if (carrier->_25A == 0) {
                getAnimationCollisionOffset(carrier->animIdx, 0x22, &offset);
                sel = -1;
            } else {
                getAnimationCollisionOffset(carrier->animIdx, 0x1E, &offset);
                sel = 1;
            }
            switch (obj->_C0) {
            case 0:
                ang = -carrier->rotY - 0.017453292f * (f32)(sel * 30 + 90);
                break;
            case 1:
                ang = -carrier->rotY - 0.017453292f * (f32)(sel * 30 + 60);
                break;
            case 2:
                ang = -carrier->rotY - 0.017453292f * (f32)(sel * 30 + 120);
                break;
            }
            if (offset.y < 0.0f) {
                h = offset.y;
                if (h < -2.5f) {
                    h = -2.5f;
                }
                r = sqrt(6.25f - h * h);
            } else {
                h = 0.0f;
                r = 2.5f;
            }
            p.x = -r * (f32)cos(ang);
            p.y = -h;
            p.z = -r * (f32)sin(ang);
            offset.x += p.x * 0.5f;
            offset.y += p.y * 0.5f;
            offset.z += p.z * 0.5f;
            offset.y *= -1.0f;
            obj->pos = offset;
            p.x *= -1.0f;
            p.y *= -1.0f;
            p.z *= -1.0f;
            flat = p;
            side = p;
            side.z = 0.0f;
            flat.y = 0.0f;
            side.x = sqrt(pow(p.x, 2.0) + pow(p.z, 2.0));
            if (0.0f != r) {
                PSVECNormalize(&flat, &flat);
            }
            PSVECNormalize(&side, &side);
            ang = acos(PSVECDotProduct(&flat, &axisX));
            obj->rotY = 57.29578f * -ang;
            if (flat.z < 0.0f) {
                obj->rotY = 360.0f - obj->rotY;
            }
            axis.x = 0.0f;
            axis.y = 1.0f;
            axis.z = 0.0f;
            C_QUATRotAxisRad(&tiltY, &axis, 0.017453292f * obj->rotY);
            ang = acos(PSVECDotProduct(&side, &axisX));
            obj->_B0 = 57.29578f * ang;
            if (side.y < 0.0f) {
                obj->_B0 = 360.0f - obj->_B0;
            }
            axis.x = 0.0f;
            axis.y = 0.0f;
            axis.z = 1.0f;
            C_QUATRotAxisRad(&tiltZ, &axis, 0.017453292f * obj->_B0);
            PSQUATMultiply(&tiltY, &tiltZ, &result);
            PSQUATNormalize(&result, &result);
            if (PSQUATDotProduct(&result, &result) == 0.0f) {
                axis.x = 0.0f;
                axis.y = 1.0f;
                axis.z = 0.0f;
                C_QUATRotAxisRad(&result, &axis, 0.0f);
            }
            if (carrier->_25D != 1) {
                obj->hasShadow = 0;
            } else {
                obj->hasShadow = 1;
            }
            CTRLSetTranslation((Control*)obj, obj->pos.x, -obj->pos.y, obj->pos.z);
            CTRLSetQuat((Control*)obj, result.x, result.y, result.z, result.w);
        }
    }
}

// .text:0x000EF930 size:0x224 mapped:0x8072E9C4
void dkKlaptrapLaunchedUpdate(DKJungleKlaptrap* obj) {
    Quaternion tilt;
    Quaternion spin;
    Vec cross;
    Vec vel;
    Vec down;
    Vec axis = {0.0f, -1.0f, 0.0f};
    f32 ang;

    vel.x = 0.3 * (f32)cos(obj->hitAngle);
    vel.y = obj->_BC;
    vel.z = 0.3 * (f32)sin(obj->hitAngle);
    PSVECAdd(&obj->pos, &vel, &obj->pos);
    if (obj->_BC < 0.0f && obj->pos.y - 1.0f < 0.0f) {
        obj->pos.x -= vel.x;
        obj->pos.y = 1.0f;
        obj->pos.z -= vel.z;
        obj->state = 6;
        obj->timer = 0x4B;
    } else {
        obj->_BC -= 0.044;
    }
    C_QUATRotAxisRad(&spin, &axis, -(0.017453292f * obj->rotY));
    vel.y = -vel.y;
    down.x = -vel.x;
    down.y = -0.5f;
    down.z = -vel.z;
    PSVECNormalize(&vel, &vel);
    PSVECNormalize(&down, &down);
    PSVECCrossProduct(&down, &vel, &cross);
    ang = acos(PSVECDotProduct(&vel, &down));
    if (1.0f != ang && -1.0f != ang) {
        C_QUATRotAxisRad(&tilt, &cross, ang);
        PSQUATMultiply(&tilt, &spin, &tilt);
        PSQUATNormalize(&tilt, &tilt);
        CTRLSetQuat((Control*)obj, tilt.x, tilt.y, tilt.z, tilt.w);
    }
    CTRLSetTranslation((Control*)obj, obj->pos.x, -obj->pos.y, obj->pos.z);
}

// .text:0x000EF890 size:0xA0 mapped:0x8072E924
void fn_3_EF890(DKJungleKlaptrap* obj) {
    fn_3_F13F8((DKJungleObject*)obj);
    CTRLSetScale((Control*)obj, 2.0f, 0.1f, 2.0f);
    obj->state = 6;
    obj->timer = 0x4B;
}

// .text:0x000EF800 size:0x90 mapped:0x8072E894
void fn_3_EF800(DKJungleKlaptrap* obj) {
    if (obj->timer == 0) {
        CTRLSetTranslation((Control*)obj, obj->pos.x, 100.0f, obj->pos.z);
    } else {
        if (obj->timer % 6 == 0) {
            obj->hasShadow = 0;
        } else {
            obj->hasShadow = 1;
        }
        obj->timer--;
    }
}

// .text:0x000EF7B4 size:0x4C mapped:0x8072E848
BOOL fn_3_EF7B4(Vec pos, u8 zone) {
    return isPosOutsideKlaptrapZone(pos, zone) != 0;
}

// .text:0x000EF55C size:0x258 mapped:0x8072E5F0
u8 isPosOutsideKlaptrapZone(Vec pos, u8 zone) {
    u8 orderAlt[4] = {1, 3, 0, 2};
    u8 order[4] = {0, 1, 2, 3};
    const DKJungleZoneCorner* corners;
    Vec toPos;
    Vec edge;
    Vec cross;
    u32 i;
    s8 sign;

    if (pos.y > 0.0f) {
        return 1;
    }
    corners = lbl_3_data_1B824[zone];
    for (sign = -1, i = 0; i < 2; sign += 2, i++) {
        toPos.x = pos.x - corners[orderAlt[i * 2]].x;
        toPos.y = 0.0f;
        toPos.z = pos.z - corners[orderAlt[i * 2]].z;
        edge.x = corners[orderAlt[i * 2 + 1]].x - corners[orderAlt[i * 2]].x;
        edge.z = corners[orderAlt[i * 2 + 1]].z - corners[orderAlt[i * 2]].z;
        edge.y = 0.0f;
        PSVECNormalize(&toPos, &toPos);
        PSVECNormalize(&edge, &edge);
        PSVECCrossProduct(&edge, &toPos, &cross);
        if (cross.y * (f32)sign < 0.0f) {
            return 1;
        }
    }
    for (sign = -1, i = 0; i < 2; sign += 2, i++) {
        toPos.x = pos.x - corners[order[i * 2]].x;
        toPos.y = 0.0f;
        toPos.z = pos.z - corners[order[i * 2]].z;
        edge.x = corners[order[i * 2 + 1]].x - corners[order[i * 2]].x;
        edge.z = corners[order[i * 2 + 1]].z - corners[order[i * 2]].z;
        edge.y = 0.0f;
        PSVECNormalize(&toPos, &toPos);
        PSVECNormalize(&edge, &edge);
        PSVECCrossProduct(&edge, &toPos, &cross);
        if (cross.y * (f32)sign < 0.0f) {
            return 1;
        }
    }
    return 0;
}

// .text:0x000EF408 size:0x154 mapped:0x8072E49C
void jungleStadiumObjectRelated(DKJungleKlaptrap* obj) {
    DKJungleKlaptrapData* data = &jungleKlaptrapData[obj->index];
    Vec toTarget;
    Vec heading;
    Vec cross;
    f32 rad;
    f32 dot;

    toTarget.x = jungleKlaptrapData[obj->index].pos.x - obj->pos.x;
    toTarget.y = 0.0f;
    toTarget.z = data->pos.z - obj->pos.z;
    PSVECNormalize(&toTarget, &toTarget);
    rad = -(0.017453292f * obj->rotY);
    heading.x = (f32)cos(rad);
    heading.y = 0.0f;
    heading.z = (f32)sin(rad);
    PSVECNormalize(&heading, &heading);
    dot = PSVECDotProduct(&toTarget, &heading);
    if (dot < -1.0) {
        dot = -1.0f;
    }
    obj->turnAngle = 57.29578f * (f32)acos(dot);
    PSVECCrossProduct(&toTarget, &heading, &cross);
    if (cross.y < 0.0f) {
        obj->turnDir = 1;
    } else {
        obj->turnDir = -1;
    }
    obj->state = 0;
}

// .text:0x000EF3D4 size:0x34 mapped:0x8072E468
void fn_3_EF3D4(StadiumObject* obj, u8 idx) {
    actorSetAnimBank((ACTActor*)obj->model, lbl_3_bss_B154.animBank[idx]);
}

// .text:0x000EF21C size:0x1B8 mapped:0x8072E2B0
void fn_3_EF21C(DKJungleKlaptrap* obj) {
    DKJungleKlaptrapTuning* tune = (DKJungleKlaptrapTuning*)&barrelRollSfxEmitterId;

    if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL && isWorldPosOnScreen(&obj->pos)) {
        switch (obj->state) {
        case 0:
            if (obj->timer % tune->dustInterval[0] == 0) {
                spawnDustPuff(&obj->pos, 0, tune->dustSize[0], 0.0f);
            }
            break;
        case 1:
            if (obj->timer % tune->dustInterval[1] == 0) {
                spawnDustPuff(&obj->pos, 0, tune->dustSize[1], 0.0f);
            }
            break;
        case 2:
            if (obj->timer % tune->dustInterval[2] == 0) {
                spawnDustPuff(&obj->pos, 1, tune->dustSize[2], tune->dustHeight);
                dkPlayHazardSfx(8);
            }
            break;
        }
    }
}

// .text:0x000EF218 size:0x4 mapped:0x8072E2AC
void fn_3_EF218(void) {
    return;
}

// .text:0x000EEFD4 size:0x244 mapped:0x8072E068
void klaptrapHitAnimation(int idx) {
    DKJungleKlaptrap* obj = (DKJungleKlaptrap*)(stadiumObjectCollision.objects + idx);
    Vec dir;
    Vec fwd = {1.0f, 0.0f, 0.0f};
    Vec trans;
    f32 ang;

    if (obj->state < 3) {
        dir.x = g_Ball.physicsSubstruct.velocity.x;
        dir.y = 0.0f;
        dir.z = g_Ball.physicsSubstruct.velocity.z;
        PSVECNormalize(&dir, &dir);
        ang = (f32)acos(PSVECDotProduct(&fwd, &dir));
        if (dir.z < 0.0f) {
            ang = 6.283185258507729 - ang;
        }
        obj->hitAngle = ang;
        obj->_BC = 0.5f;
        obj->state = 4;
        fn_3_F13F8((DKJungleObject*)obj);
        if (g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_FIELDED && inningSetting.starSkillsSetting != 0) {
            CTRLGetTranslation((Control*)obj, &trans.x, &trans.y, &trans.z);
            stadiumStarAwarded(trans.x, trans.y - 5.0f, trans.z);
            obj->awarded = 1;
        }
        dkPlayHazardSfx(9);
        processFielderAutoCatch();
        g_FieldingLogic.knockoutFinished = 1;
    }
}

// .text:0x000EEFD0 size:0x4 mapped:0x8072E064
void fn_3_EEFD0(void) {
    return;
}

// .text:0x000EEFA4 size:0x2C mapped:0x8072E038
void fn_3_EEFA4(void) {
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
}

// .text:0x000EEF24 size:0x80 mapped:0x8072DFB8
void fn_3_EEF24(void) {
    if (hugeAnimStruct[0x3088] == 0) {
        removeCurrentDrawingItem();
    } else if (hugeAnimStruct[0x307E] != 0) {
        fn_800BDA24((void*)lbl_3_bss_B55C);
        fn_3_EE388();
        fn_3_EEB94();
        fn_800A7D4C(1, (u8*)&lbl_3_data_1BA5C + drawStadiumRelated * 8);
    }
}

// .text:0x000EEE3C size:0xE8 mapped:0x8072DED0
void fn_3_EEE3C(void) {
    StadiumModelNode* node = ((StadiumModel*)lbl_3_bss_B55C)->root;
    Vec pos;
    MtxPtr m;

    lbl_803C5090[0x1D] = 1;
    fn_8003A144();
    SetDisplayStateTexture(returnTexture(), 0, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    for (node = node->firstChild; node != NULL; node = node->nextSibling, GXSetTevDirect(GX_TEVSTAGE0)) {
        m = node->worldMtx;
        pos.x = m[0][3];
        pos.y = m[1][3];
        pos.z = m[2][3];
        fn_3_EE96C(&pos);
        if (node->dispObj != NULL) {
            DOSetWorldMatrix(node->dispObj, node->worldMtx);
            fn_3_EE67C((DKJungleDispObj*)node->dispObj, returnFloatFromModeIndex(returnsCurrentMode())->view);
        }
    }
}

// .text:0x000EECF4 size:0x148 mapped:0x8072DD88
void fn_3_EECF4(void) {
    DKJungleBss* bss = (DKJungleBss*)&lbl_3_bss_AEE0;
    f32 (*m)[3];
    u32 y;
    u32 x;
    int idx;

    m = bss->indMtx;
    m[0][0] = 0.01f;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[1][0] = 0.0f;
    m[1][1] = 0.01f;
    m[1][2] = 0.0f;
    GXSetIndTexMtx(GX_ITM_0, m, 2);
    if ((bss->texBuf = fn_3_B9534(16, 16, &bss->texObj)) == NULL) {
        OSPanic("sta_c5.c", 0x1028, "error\n");
    }
    for (y = 0; y < 16; y++) {
        for (x = 0; x < 16; x++) {
            idx = fn_800247E4(x, y, 16, 2);
            bss->texBuf[idx] = (u8)(rand() % 200) + 0x1B;
            bss->texBuf[idx + 1] = (u8)(rand() % 200) + 0x1B;
        }
    }
    memset((u8*)bss + 0x38, 1, 0x200);
}

// .text:0x000EEB94 size:0x160 mapped:0x8072DC28
void fn_3_EEB94(void) {
    u32 y;
    u32 x;
    int idx;
    int a;
    int b;
    s8* dir;

    for (y = 0; y < 16; y++) {
        for (x = 0; x < 16; x++) {
            idx = fn_800247E4(x, y, 16, 2);
            dir = (s8*)lbl_3_bss_AF18;
            a = lbl_3_bss_B118.texBuf[idx];
            b = lbl_3_bss_B118.texBuf[idx + 1];
            a += dir[idx] * (rand() % 14 + 8);
            b += dir[idx + 1] * (rand() % 14 + 8);
            if (a >= 227) {
                a--;
                dir[idx] = -1;
            } else if (a <= 27) {
                a++;
                dir[idx] = 1;
            }
            if (b >= 227) {
                b--;
                dir[idx + 1] = -1;
            } else if (b <= 27) {
                b++;
                dir[idx + 1] = 1;
            }
            lbl_3_bss_B118.texBuf[idx] = a;
            lbl_3_bss_B118.texBuf[idx + 1] = b;
        }
    }
}

// .text:0x000EE96C size:0x228 mapped:0x8072DA00
void fn_3_EE96C(Vec* pos) {
    Mtx mtx;
    Vec dir;
    Vec down = {0.0f, -1.0f, 0.0f};
    DKJungleBss* bss;
    camera_803c639c_s* cam;
    f32 dist;
    f32 clamped;
    f32 scale;
    f32 tilt;
    f32* ind;
    int sScale;
    int tScale;

    bss = (DKJungleBss*)&lbl_3_bss_AEE0;
    cam = fn_80052768_getCamera(returnsCurrentMode());
    PSVECSubtract(&cam->eye, &cam->target, &dir);
    clamped = PSVECMag(&dir);
    if (clamped) {
        PSVECNormalize(&dir, &dir);
    } else {
        dir.y = 0.0f;
        dir.x = 0.0f;
        dir.z = 1.0f;
    }
    acos(PSVECDotProduct(&dir, &down));
    PSVECSubtract(&cam->eye, pos, &dir);
    clamped = PSVECMag(&dir);
    dist = clamped;
    if (clamped < 20.0f) {
        clamped = 20.0f;
    }
    PSMTXCopy(cam->view, mtx);
    tilt = down.y * mtx[1][1];
    scale = 0.2f / clamped;
    ind = &bss->indMtx[0][0];
    ind[0] = scale;
    ind[4] = scale * (f32)(1.0 - fabs(0.5f * tilt));
    if (dist < 35.0f) {
        tScale = sScale = GX_ITS_16;
    } else if (dist < 55.0f) {
        tScale = sScale = GX_ITS_8;
    } else {
        tScale = sScale = GX_ITS_4;
    }
    bss->_14 = 0;
    DCFlushRange(bss->texBuf, 0x200);
    GXSetIndTexMtx(GX_ITM_0, bss->indMtx, 2);
    GXLoadTexObj(&bss->texObj, GX_TEXMAP7);
    GXSetIndTexOrder(GX_IND_TEX_STAGE_0, GX_TEXCOORD0, GX_TEXMAP7);
    GXSetNumIndStages(1);
    GXSetIndTexCoordScale(GX_IND_TEX_STAGE_0, sScale, tScale);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_IND_TEX_STAGE_0, GX_TRUE, GX_FALSE, GX_ITM_0);
}

// .text:0x000EE67C size:0x2F0 mapped:0x8072D710
void fn_3_EE67C(DKJungleDispObj* obj, Mtx view) {
    Mtx model;
    GXVtxDescList desc[GX_VA_MAX_ATTR + 1];
    DKJungleDrawEntry* entry;
    int i;
    int n;
    u32 j;
    int compSize;

    PSMTXConcat(view, obj->mtx, model);
    GXLoadPosMtxImm(model, 0);
    GXSetCurrentMtx(0);
    switch ((u8)(obj->vertices->format >> 4)) {
    case 0:
    case 1:
        compSize = 1;
        break;
    case 2:
    case 3:
        compSize = 2;
        break;
    case 4:
        compSize = 4;
        break;
    default:
        compSize = 0;
        break;
    }
    GXSetArray(GX_VA_POS, obj->vertices->data, obj->vertices->stride * compSize);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, obj->vertices->format >> 4, obj->vertices->format & 0xF);
    GXSetNumTexGens(1);
    entry = obj->drawList->entries;
    for (i = 0; i < obj->drawList->count; i++, entry++) {
        switch (entry->kind) {
        case 1:
            break;
        case DKJUNGLE_ENTRY_SETUP_VTX:
            GXClearVtxDesc();
            n = 0;
            if ((entry->vtxDescBits & 3) != 0) {
                desc[n].mAttr = GX_VA_PNMTXIDX;
                desc[n].mType = entry->vtxDescBits & 3;
                n = 1;
            }
            {
                GXAttr attr;
                u32 shift = 2;
                for (attr = GX_VA_POS; attr <= GX_VA_TEX7; attr++, shift += 2) {
                    u32 type = (entry->vtxDescBits >> shift) & 3;
                    if (type != 0) {
                        desc[n].mAttr = attr;
                        desc[n].mType = type;
                        n++;
                    }
                }
                {
                    u32 type = (entry->vtxDescBits >> shift) & 3;
                    if (type != 0) {
                        desc[n].mAttr = attr;
                        desc[n].mType = type;
                        n++;
                    }
                }
            }
            desc[n].mAttr = GX_VA_NULL;
            GXSetVtxDescv(desc);
            break;
        case DKJUNGLE_ENTRY_SETUP_EFFECT:
            GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
            fn_3_EE100(obj, view);
            break;
        }
        if (entry->displayList != NULL) {
            GXCallDisplayList(entry->displayList, entry->displayListSize);
        }
    }
}

// .text:0x000EE388 size:0x2F4 mapped:0x8072D41C
void fn_3_EE388(void) {
    DKJungleWaterState* water = (DKJungleWaterState*)&barrelRollSfxEmitterId;
    DKJungleBss* bss = (DKJungleBss*)&lbl_3_bss_AEE0;
    f32 angle;
    f32 step;
    f32 targetMag;
    f32 phase;

    if (water->needsRespawn != 0) {
        rand();
        angle = 6.2831855f * ((f32)rand() / 32767.0f);
        bss->target.x = 0.01f * (f32)cos(angle);
        bss->target.y = 0.01f * (f32)sin(angle);
        bss->target.z = 0.0f;
        PSVECSubtract(&bss->target, &water->pos, &water->vel);
        if (PSVECMag(&water->vel) != 0.0f) {
            PSVECNormalize(&water->vel, &water->vel);
        }
        PSVECScale(&water->vel, 0.0005f, &water->vel);
        water->needsRespawn = 0;
    }
    PSVECAdd(&water->pos, &water->vel, &water->pos);
    targetMag = PSVECMag(&bss->target);
    if (PSVECMag(&water->pos) > targetMag) {
        f32 vx = water->vel.x * -1.0f;
        f32 vy = water->vel.y * -1.0f;
        water->vel.x = vx;
        water->vel.y = vy;
        PSVECScale(&bss->target, 2.0f, &bss->target);
    } else if (PSVECDotProduct(&water->pos, &bss->target) <= 0.0f) {
        water->pos.y = 0.0f;
        water->pos.x = 0.0f;
        water->needsRespawn = 1;
    }
    if (water->needsReroll != 0) {
        step = 0.0005 * (2.0 * ((f64)((f32)rand() / 32767.0f) - 0.5));
        water->needsReroll = 0;
        bss->_28 = step;
        bss->_24 = 0.0f;
        bss->_20 = 2.5e-05 * (fabs(step) / step);
    }
    {
        f64 absPhase;
        f64 absStep28;
        phase = bss->_24 + bss->_20;
        absPhase = fabs(phase);
        absStep28 = fabs(bss->_28);
        bss->_24 = phase;
        if (absPhase >= absStep28) {
            bss->_20 = bss->_20 * -1.0f;
        } else if ((int)(absPhase / phase) != (int)(absStep28 / bss->_28)) {
            water->needsReroll = 1;
        }
    }
}

// .text:0x000EE100 size:0x288 mapped:0x8072D194
void fn_3_EE100(DKJungleDispObj* obj, Mtx view) {
    Mtx camMtx;
    Mtx model;
    Mtx tmp;
    Mtx44 proj;
    GXColor white;
    f32 scale;
    camera_803c639c_s* cam;

    white.r = 0xFF;
    white.g = 0xFF;
    white.b = 0xFF;
    white.a = 0xFF;
    GXSetChanMatColor(GX_COLOR0A0, white);
    GXSetNumChans(1);
    scale = lbl_3_bss_AF04._00;
    PSMTXCopy(obj->mtx, model);
    PSMTXCopy(view, camMtx);
    camMtx[0][3] += lbl_3_data_1BA70.pos.x;
    camMtx[1][3] += lbl_3_data_1BA70.pos.y;
    scale = 1.0f + scale;
    camMtx[0][0] *= scale;
    camMtx[0][1] *= scale;
    camMtx[0][2] *= scale;
    camMtx[1][0] *= scale;
    camMtx[1][1] *= scale;
    camMtx[1][2] *= scale;
    PSMTXConcat(camMtx, model, model);
    PSMTXIdentity(tmp);
    cam = returnFloatFromModeIndex(returnsCurrentMode());
    PSMTX44Copy(cam->proj, proj);
    tmp[0][0] = proj[0][0];
    tmp[0][2] = proj[0][2];
    tmp[1][1] = proj[1][1];
    tmp[1][2] = proj[1][2];
    tmp[2][2] = proj[3][2];
    PSMTXConcat(tmp, model, model);
    PSMTXIdentity(tmp);
    tmp[0][0] = 0.5f;
    tmp[0][2] = 0.5f;
    tmp[1][1] = -0.5f;
    tmp[1][2] = 0.5f;
    tmp[2][2] = 1.0f;
    tmp[2][3] = 0.0f;
    tmp[1][3] = 0.0f;
    tmp[0][3] = 0.0f;
    PSMTXConcat(tmp, model, model);
    GXLoadTexMtxImm(model, GX_TEXMTX0, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2X4, GX_TG_POS, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_RASA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
}

// .text:0x000EE0BC size:0x44 mapped:0x8072D150
int fn_3_EE0BC(u32 flags) {
    switch ((flags >> 4) & 0xF) {
    case 0:
    case 1:
        return 1;
    case 2:
    case 3:
        return 2;
    case 4:
        return 4;
    default:
        return 0;
    }
}

// .text:0x000EDFAC size:0x110 mapped:0x8072D040
void fn_3_EDFAC(void) {
    u8* base = (u8*)&lbl_3_bss_AEE0;
    int* emitters = (int*)(base + 0x18);
    if (g_GameLogic.gameStatus != GAME_STATUS_MINIGAME_READY) {
        if (g_GameLogic.gameStatus == GAME_STATUS_PAUSED) {
            if (base[0x27C] == 0) {
                updateAndRemoveStadiumEmitter(emitters[1]);
                updateAndRemoveStadiumEmitter(emitters[0]);
                base[0x27C] = 1;
            }
        } else if (base[0x27C] != 0) {
            int newEmitter1 = initializeStadiumObjectEmitter(stadiumHazardSoundIDs[g_d_GameSettings.StadiumID] + 6, NULL, NULL, 4);
            emitters[0] = initializeStadiumObjectEmitter(stadiumHazardSoundIDs[g_d_GameSettings.StadiumID] + 7, NULL, NULL, 5);
            emitters[1] = newEmitter1;
            base[0x27C] = 0;
        } else {
            updateOrRemoveEmitter(emitters[1], 0, 0);
            updateOrRemoveEmitter(emitters[0], 0, 0);
        }
    }
}

