#include "game/stadium/stadium_yoshi_park.h"
#include "header_rep_data.h"
#include "game/stadium/stadium_framework.h"
#include "game/UnknownHomes_Game.h"
#include "Dolphin/mtx.h"
#include "Dolphin/vec.h"
#include "C3/control.h"
#include "stl/math.h"
#include "Dolphin/rand.h"
#include "Dolphin/os.h"
#include "Dolphin/stl.h"
#include "game/math/game_math.h"
#include "game/ball/ball_physics.h"
#include "game/fielding/fielder.h"
#include "game/sound/m_sound.h"
#include "game/stadium/stadium_star.h"
#include "musyx/musyx.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x800b4908.h"
#include "Unknown/File_0x800b4b38.h"
#include "Unknown/File_0x800b4bc8.h"
#include "Unknown/File_0x800bdc88.h"
#include "Unknown/File_0x800bdd74.h"
#include "Unknown/File_0x800acf14.h"

// One entry per piranha-plant slot (11 slots, 10 usable; `usedFlag == 2` ends the list).
typedef struct _YoshiPlantPlacement {
    /*0x00*/ f32 x;
    /*0x04*/ f32 y;
    /*0x08*/ f32 z;
    /*0x0C*/ f32 rotation;
    /*0x10*/ u8 usedFlag;
    /*0x11*/ u8 _11;
    /*0x12*/ u8 group;
    /*0x13*/ u8 _13;
    /*0x14*/ f32 spitAngleBase;
    /*0x18*/ f32 spitAngleRange;
} YoshiPlantPlacement; // size 0x1C

// A stack copy of an object's Control plus the 8 bytes after it (0x44 total),
// used to build offset collision boxes without touching the real object.
typedef struct _YoshiObjControl {
    Control ctrl;
    u8 _3C[0x44 - sizeof(Control)];
} YoshiObjControl;

// Names from the annotated Ghidra project, except PLANT_POP_UP: fn_3_E3914 sets it
// together with the pop-up animation and ParkPlantsPopUp moves it on to TRACKING.
typedef enum _PLANT_STATE {
    PLANT_IDLE = 0,
    PLANT_POP_UP = 1,
    PLANT_TRACKING = 2,
    PLANT_SPIT = 3,
    PLANT_STAR = 4,
    PLANT_SHRINK = 5,
} PLANT_STATE;

// Plant view of a stadiumObjectCollision.objects[] entry (the region past 0x98
// is laid out per hazard kind, as in stadium_bowser_castle.c).
typedef struct _YoshiPlantObj {
    /*0x00*/ u8 _00[0x74];
    /*0x74*/ ACTActor* actor;
    /*0x78*/ u8 _78[0x9C - 0x78];
    /*0x9C*/ u8 index;
    /*0x9D*/ u8 _9D;
    /*0x9E*/ u8 plantID;
    /*0x9F*/ u8 _9F;
    /*0xA0*/ Vec pos;
    /*0xAC*/ u32 animBank;
    /*0xB0*/ f32 rotation;
    /*0xB4*/ f32 scale;
    /*0xB8*/ f32 animFrame;
    /*0xBC*/ f32 spitAngle;
    /*0xC0*/ f32 rotationSpeed;
    /*0xC4*/ E(u8, PLANT_STATE) state;
    /*0xC5*/ u8 stateFrame;
    /*0xC6*/ u8 stateDuration;
    /*0xC7*/ u8 _C7;
    /*0xC8*/ u8 plantType;
    /*0xC9*/ u8 _C9;
    /*0xCA*/ u8 holdingBall;
    /*0xCB*/ s8 curAnim;
} YoshiPlantObj;

typedef struct _YoshiMaterialFlags {
    /*0x00*/ u8 _00[4];
    /*0x04*/ u32 animState;
} YoshiMaterialFlags;

typedef struct _YoshiModelLevel4 {
    /*0x00*/ u8 _00[4];
    /*0x04*/ YoshiMaterialFlags* next;
} YoshiModelLevel4;

typedef struct _YoshiModelLevel3 {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ YoshiModelLevel4* next;
} YoshiModelLevel3;

typedef struct _YoshiModelLevel2 {
    /*0x00*/ YoshiModelLevel3* next;
} YoshiModelLevel2;

typedef struct _YoshiModelLevel1 {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ YoshiModelLevel2* next;
} YoshiModelLevel1;

// root->+0x18->+0x40 is the joint node whose world matrix fn_3_E4BE8 applies to the
// plant's collision mesh while it is mid-animation.
typedef struct _YoshiJointList {
    /*0x00*/ u8 _00[0x40];
    /*0x40*/ StadiumModelNode* headNode;
    /*0x44*/ StadiumModelNode* holdNode;
} YoshiJointList;

typedef struct _YoshiModelRootJoints {
    /*0x00*/ u8 _00[0x18];
    /*0x18*/ YoshiJointList* joints;
} YoshiModelRootJoints;

typedef struct _YoshiModelRoot {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ YoshiModelLevel1* next;
} YoshiModelRoot;

extern YoshiPlantPlacement parkPlantData[11];
extern u8 enumObjTypeInFile_ARRAY_807ca604[];
extern u8 hugeAnimStruct[0x3154];
extern u16 stadiumHazardSoundIDs[16];
extern u8 stadiumHazardSoundFxRelated[0xB4];
extern u8 lbl_3_data_84B8[0x3C];

// MWCC lays these out in reverse declaration order, so they are declared from the
// highest address (plantAnimationPointers, 0xAE18) down to lbl_3_bss_AE00.
static u32 plantAnimationPointers[14];
static u8 lbl_3_bss_AE14;
static u8 lbl_3_bss_AE13;
static u8 lbl_3_bss_AE12;
static u8 lbl_3_bss_AE11;
static u8 ambientActive;
static s32 ambientTimerA;
static s32 ambientTimerB;
static s32 ambientEmitter;
static u8 lbl_3_bss_AE01;
static u8 lbl_3_bss_AE00;

// .text:0x000E1DB8 size:0x1F0 mapped:0x80720E4C
void fn_3_E1DB8(void) {
    if (g_GameLogic.gameStatus == GAME_STATUS_MINIGAME_READY) {
        return;
    }
    if (g_GameLogic.gameStatus == GAME_STATUS_PAUSED) {
        if (ambientActive) {
            updateAndRemoveStadiumEmitter(ambientEmitter);
            ambientActive = FALSE;
        }
        return;
    }
    if (!ambientActive) {
        ambientEmitter =
            initializeStadiumObjectEmitter(stadiumHazardSoundIDs[g_d_GameSettings.StadiumID] + 5, NULL, NULL, 6);
        ambientActive = TRUE;
        ambientTimerA = rand() % 900 + 100;
        ambientTimerB = rand() % 900 + 100;
    }
    if (ambientTimerA <= 0) {
        randomizeAndLoadSoundEffect(stadiumHazardSoundIDs[g_d_GameSettings.StadiumID] + 6, 7);
        ambientTimerA = rand() % 900 + 100;
    } else {
        ambientTimerA--;
    }
    if (ambientTimerB <= 0) {
        randomizeAndLoadSoundEffect(stadiumHazardSoundIDs[g_d_GameSettings.StadiumID] + 7, 7);
        ambientTimerB = rand() % 900 + 100;
    } else {
        ambientTimerB--;
    }
}

// .text:0x000E1FA8 size:0x8C mapped:0x8072103C
void fn_3_E1FA8(StadiumObject* obj) {
    ACTActor* act = ((YoshiPlantObj*)obj)->actor;
    void* actor = act->actor;

    if (act->animFrame + act->animSpeed > 900.0f) {
        act->animFrame = 180.0f;
        act->applyFrame = 1;
        setActorAnimFrame(actor, act->animFrame);
    }
    AnimateActorBones(actor);
    act->animFrame += act->animSpeed;
}

// .text:0x000E2034 size:0xE4 mapped:0x807210C8
void fn_3_E2034(YoshiPlantObj* plant) {
    Vec toBall;
    Vec fwd = { 0.0f, 0.0f, -1.0f };
    f32 ang;

    PSVECSubtract((Vec*)&g_Ball.AtBat_Contact_BallPos, &plant->pos, &toBall);
    toBall.y = 0.0f;
    PSVECNormalize(&toBall, &toBall);
    PSVECNormalize(&fwd, &fwd);
    ang = 57.29578f * (f32)acos(PSVECDotProduct(&toBall, &fwd));
    if (toBall.x < 0.0f) {
        ang = 360.0f - ang;
    }
    plant->rotation = -ang;
    CTRLSetRotation((Control*)plant, 0.0f, plant->rotation, 0.0f);
}

// .text:0x000E2118 size:0x18C mapped:0x807211AC
void fn_3_E2118(int idx) {
    YoshiPlantObj* plant = (YoshiPlantObj*)&stadiumObjectCollision.objects[idx];
    int stadiumID;
    u8 vol;
    u8 val;
    SND_VOICEID voice;

    if (plant->state == PLANT_IDLE || plant->state == PLANT_SHRINK) {
        return;
    }
    if (plant->plantType != 0 && plant->state != PLANT_STAR) {
        if (g_Ball.AtBat_ContactResult > BALL_RESULT_TYPE_LANDED) {
            return;
        }
        plant->_C9 = 1;
        plant->state = PLANT_STAR;
        fn_3_E25D0(plant, 8);
        stadiumID = g_d_GameSettings.StadiumID;
        vol = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                  ? lbl_3_data_84B8[4]
                  : stadiumHazardSoundFxRelated[stadiumID * 0x1E + 4];
        voice = sndFXStartEx(stadiumHazardSoundIDs[stadiumID] + 2, vol, 0x3f, 0);
        val = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                  ? lbl_3_data_84B8[5]
                  : stadiumHazardSoundFxRelated[stadiumID * 0x1E + 5];
        sndFXCtrl(voice, 0x5b, val);
    }
    ballState_thrown_to_holding();
    processFielderAutoCatch();
    g_FieldingLogic.knockoutFinished = 1;
}

// .text:0x000E22A4 size:0x80 mapped:0x80721338
void fn_3_E22A4(YoshiPlantObj* plant) {
    YoshiMaterialFlags* mat =
        ((YoshiModelRoot*)((StadiumModel*)plant->actor)->root)->next->next->next->next->next;
    u8 frame;

    mat->animState &= ~0x1FFF;
    if (plant->state == PLANT_IDLE) {
        return;
    }
    frame = plant->plantType + 1;
    if (plant->state == PLANT_POP_UP || plant->state == PLANT_SHRINK) {
        if (plant->stateFrame % 2 == 0) {
            frame = 0;
        }
    }
    mat->animState |= frame;
}

// .text:0x000E2324 size:0x2AC mapped:0x807213B8
void fn_3_E2324(YoshiPlantObj* plant) {
    Mtx joint;
    Mtx m;
    Vec fielderPos;
    Vec delta;
    Vec dir;
    Vec mouth = { 0.0f, 0.0f, 0.0f };
    u8 fielders[7] = { 2, 3, 4, 5, 6, 7, 8 };
    f32 reach;
    u32 i;
    int stadiumID;
    SND_VOICEID voice;

    if (plant->holdingBall) {
        return;
    }
    PSMTXCopy(((YoshiModelRootJoints*)((StadiumModel*)plant->actor)->root)->joints->headNode->worldMtx, joint);
    CTRLBuildMatrix((Control*)plant, m);
    PSMTXConcat(m, joint, m);
    PSMTXMultVec(m, &mouth, &mouth);
    mouth.y *= -1.0f;
    reach = 2.2f * plant->scale;
    for (i = 0; i < 7; i++) {
        InMemFielder* fielder = &g_Fielders[fielders[i]];

        if (fielder->knockoutStatus != 0) {
            continue;
        }
        fielderPos.x = fielder->pos.x;
        fielderPos.y = 1.5f;
        fielderPos.z = fielder->pos.z;
        PSVECSubtract(&mouth, &fielderPos, &delta);
        dir.x = delta.x;
        dir.y = 0.0f;
        dir.z = delta.z;
        PSVECNormalize(&dir, &dir);
        if (PSVECMag(&delta) <= reach) {
            int angle = calculateAngleFromCoordinates(dir.x, dir.z);

            processFielderKnockout(fielders[i], angle);
            if (plant->curAnim != 8 && !plant->holdingBall) {
                fn_3_E25D0(plant, 9);
                plant->state = PLANT_SHRINK;
            }
            stadiumID = g_d_GameSettings.StadiumID;
            voice = sndFXStartEx(stadiumHazardSoundIDs[stadiumID] + 4,
                                 g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                                     ? lbl_3_data_84B8[8]
                                     : stadiumHazardSoundFxRelated[stadiumID * 0x1E + 8],
                                 0x3f, 0);
            sndFXCtrl(voice, 0x5b,
                      g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                          ? lbl_3_data_84B8[9]
                          : stadiumHazardSoundFxRelated[stadiumID * 0x1E + 9]);
        }
    }
}

// .text:0x000E25D0 size:0x9C mapped:0x80721664
void fn_3_E25D0(YoshiPlantObj* plant, u32 anim) {
    plant->animBank = plantAnimationPointers[anim];
    actorSetAnimBank(plant->actor, plant->animBank);
    if (anim != 0 && anim != 2 && anim != 3) {
        plant->actor->applyFlags = 2;
        updateBoneParam(plant->actor->actor, plant->actor->applyFlags & 1);
    }
    plant->animFrame = plant->actor->animFrame;
    plant->curAnim = anim;
}

// .text:0x000E266C size:0x270 mapped:0x80721700
void advancePlantInteractionPhase(YoshiPlantObj* plant) {
    ACTActor* act = plant->actor;

    if (plant->animBank == 0) {
        return;
    }
    if (!(act->applyFlags & 1) && scanBoneAttachmentData(act->actor) == 0.0f) {
        switch (plant->curAnim) {
        case 1:
            if (plant->state == PLANT_SHRINK || plant->state == PLANT_IDLE) {
                fn_3_E25D0(plant, 0);
                break;
            }
            // fallthrough
        case 4:
        case 5:
            if (plant->plantType == 0) {
                fn_3_E25D0(plant, 2);
            } else {
                fn_3_E25D0(plant, 3);
            }
            break;
        case 7:
            plant->rotation = -plant->spitAngle;
            fn_3_E25D0(plant, 8);
            CTRLSetRotation((Control*)plant, 0.0f, plant->rotation, 0.0f);
            break;
        case 8:
            fn_3_E25D0(plant, 9);
            plant->state = PLANT_SHRINK;
            break;
        default:
            fn_3_E25D0(plant, 0);
            break;
        }
    }
    AnimateActorBones(act->actor);
    plant->animFrame = fn_800B4C40(act->actor);
}

// .text:0x000E28DC size:0xD8 mapped:0x80721970
E(u8, BOOL) fn_3_E28DC(YoshiPlantObj* plant) {
    Vec pos = plant->pos;
    Vec diff;

    PSVECSubtract((Vec*)&g_Ball.AtBat_Contact_BallPos, &pos, &diff);
    diff.y = 0.0f;
    if (2.5 >= PSVECMag(&diff)) {
        fn_3_E25D0(plant, 6);
        return TRUE;
    }
    return FALSE;
}

// .text:0x000E29B4 size:0x1BC mapped:0x80721A48
E(u8, BOOL) fn_3_E29B4(YoshiPlantObj* plant) {
    static const f32 animSpeeds[3] = { 0.8f, 1.0f, 1.2f };
    Vec pos = plant->pos;
    Vec diff;
    f32 dist;

    PSVECSubtract((Vec*)&g_Ball.AtBat_Contact_BallPos, &pos, &diff);
    diff.y = 0.0f;
    dist = PSVECMag(&diff);
    if (5.5 * plant->scale > dist && g_Ball.AtBat_Contact_BallPos.y >= 1.5 * plant->scale &&
        g_Ball.AtBat_Contact_BallPos.y <= 8.5 * plant->scale) {
        if (g_Ball.AtBat_Contact_BallPos.y < 5.0 * plant->scale) {
            fn_3_E25D0(plant, 4);
        } else {
            fn_3_E25D0(plant, 5);
        }
        plant->actor->animSpeed = animSpeeds[rng(3)];
        plant->actor->applySpeed = 1;
        fn_800B4C04(plant->actor->actor, plant->actor->animSpeed);
        return TRUE;
    }
    return FALSE;
}

// .text:0x000E2B70 size:0x308 mapped:0x80721C04
E(u8, BOOL) updatePlantCatchState(YoshiPlantObj* plant) {
    Vec delta;

    if (g_Ball.AtBat_ContactResult >= BALL_RESULT_TYPE_FIELDED) {
        return FALSE;
    }
    if (plant->plantType != 0) {
        return FALSE;
    }
    if (g_Ball.deadBallReason == 1 || g_Ball.deadBallReason == 3) {
        return FALSE;
    }
    if (plant->curAnim >= 4 && plant->curAnim <= 6) {
        return TRUE;
    }
    PSVECSubtract((Vec*)&g_Ball.AtBat_Contact_BallPos, (Vec*)&g_Ball.pastCoordinates[0], &delta);
    if (0.0f != PSVECMag(&delta)) {
        return fn_3_E29B4(plant);
    }
    return fn_3_E28DC(plant);
}

// .text:0x000E2E78 size:0xD4 mapped:0x80721F0C
void updateStadiumObjStateAndTransform(YoshiPlantObj* plant) {
    if (plant->stateFrame == 0) {
        plant->plantType = 0;
        plant->state = PLANT_IDLE;
        return;
    }
    plant->scale = plant->scale - 1.0857142857142859 / plant->stateDuration;
    plant->pos.y = -(1.2 * plant->scale);
    CTRLSetTranslation((Control*)plant, plant->pos.x, -plant->pos.y, plant->pos.z);
    CTRLSetScale((Control*)plant, plant->scale, plant->scale, plant->scale);
    plant->stateFrame--;
}

// .text:0x000E2F4C size:0xF8 mapped:0x80721FE0
void yoshiParkPlantRelated(YoshiPlantObj* plant) {
    f32 frame = plant->animFrame;
    f32 speed = plant->actor->animSpeed;
    f32 ang;
    f32 x;

    if (frame >= 20.0 && frame - speed < 20.0 && inningSetting.starSkillsSetting != 0) {
        ang = -plant->rotation;
        ang = 0.017453292f * ang;
        x = plant->scale * (5.0 * sinf_kludge(ang)) + plant->pos.x;
        stadiumStarAwarded(x, -2.0 * plant->scale, plant->scale * (-5.0 * cosf_kludge(ang)) + plant->pos.z);
    }
}

// .text:0x000E3044 size:0x240 mapped:0x807220D8
void nadoRelated(YoshiPlantObj* plant) {
    f32 frame;
    f32 speed = plant->actor->animSpeed;
    f32 ang;
    f32 x;
    f32 z;
    int stadiumID;
    u8 vol;
    u8 val;
    SND_VOICEID voice;

    if (plant->curAnim == 7) {
        plant->rotation += plant->rotationSpeed;
        CTRLSetRotation((Control*)plant, 0.0f, plant->rotation, 0.0f);
        return;
    }
    frame = plant->animFrame;
    if (frame >= 20.0 && frame - speed < 20.0) {
        ang = plant->spitAngle;
        ang = 0.017453292f * ang;
        x = plant->scale * (5.0 * sinf_kludge(ang)) + plant->pos.x;
        z = plant->scale * (-5.0 * cosf_kludge(ang)) + plant->pos.z;
        g_Ball.AtBat_Contact_BallPos.x = x;
        g_Ball.AtBat_Contact_BallPos.y = 2.0 * plant->scale;
        g_Ball.AtBat_Contact_BallPos.z = z;
        g_Ball.physicsSubstruct.velocity.y = 0.0f;
        g_Ball.physicsSubstruct.velocity.x = 0.1 * sinf_kludge(ang);
        g_Ball.physicsSubstruct.velocity.z = 0.1 * -cosf_kludge(ang);
        setBallInactiveVariables();
        plant->holdingBall = FALSE;
        stadiumID = g_d_GameSettings.StadiumID;
        vol = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                  ? lbl_3_data_84B8[2]
                  : stadiumHazardSoundFxRelated[stadiumID * 0x1E + 2];
        voice = sndFXStartEx(stadiumHazardSoundIDs[stadiumID] + 1, vol, 0x3f, 0);
        val = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                  ? lbl_3_data_84B8[3]
                  : stadiumHazardSoundFxRelated[stadiumID * 0x1E + 3];
        sndFXCtrl(voice, 0x5b, val);
    }
}

// .text:0x000E3284 size:0x3E4 mapped:0x80722318
E(u8, BOOL) tryPlantCatchAndBeginSpitAim(YoshiPlantObj* plant) {
    Mtx m;
    Mtx joint;
    Vec mouth = { 0.0f, 0.0f, 0.0f };
    Vec down = { 0.0f, -1.0f, 0.0f };
    Vec cross;
    Vec facing;
    Vec aimDir;
    f32 reach;
    f32 ang;
    int stadiumID;
    u8 vol;
    u8 val;
    SND_VOICEID voice;

    PSMTXCopy(((YoshiModelRootJoints*)((StadiumModel*)plant->actor)->root)->joints->headNode->worldMtx, joint);
    CTRLBuildMatrix((Control*)plant, m);
    PSMTXConcat(m, joint, m);
    PSMTXMultVec(m, &mouth, &mouth);
    mouth.y *= -1.0f;
    reach = 2.2f * plant->scale;
    if ((f32)fabs(calculateBallInterceptDistance(&g_Ball.pastCoordinates[0], &g_Ball.AtBat_Contact_BallPos,
                                                 (VecXYZ*)&mouth, NULL)) <= reach) {
        plant->state = PLANT_SPIT;
        fn_3_E25D0(plant, 7);
        plant->holdingBall = TRUE;
        setValsForPlantCatches();
        ang = parkPlantData[plant->index].spitAngleBase;
        plant->spitAngle = ang + (s16)rng((s16)(u32)(10.0f * parkPlantData[plant->index].spitAngleRange)) / 10.0;
        g_Ball.physicsSubstruct.velocity.z = 0.0f;
        g_Ball.physicsSubstruct.velocity.y = 0.0f;
        g_Ball.physicsSubstruct.velocity.x = 0.0f;
        facing.x = sinf_kludge(-(0.017453292f * plant->rotation));
        facing.y = 0.0f;
        facing.z = -cosf_kludge(-(0.017453292f * plant->rotation));
        aimDir.x = sinf_kludge(0.017453292f * plant->spitAngle);
        aimDir.y = 0.0f;
        aimDir.z = -cosf_kludge(0.017453292f * plant->spitAngle);
        PSVECNormalize(&facing, &facing);
        PSVECNormalize(&aimDir, &aimDir);
        ang = acos(PSVECDotProduct(&facing, &aimDir));
        if (ang != 0.0f) {
            PSVECCrossProduct(&facing, &aimDir, &cross);
            if (!(PSVECDotProduct(&cross, &down) > 0.0f)) {
                ang *= -1.0f;
            }
        }
        plant->rotationSpeed = -(57.29578f * (ang / 60.0f));
        stadiumID = g_d_GameSettings.StadiumID;
        vol = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                  ? lbl_3_data_84B8[0]
                  : stadiumHazardSoundFxRelated[stadiumID * 0x1E + 0];
        voice = sndFXStartEx(stadiumHazardSoundIDs[stadiumID], vol, 0x3f, 0);
        val = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                  ? lbl_3_data_84B8[1]
                  : stadiumHazardSoundFxRelated[stadiumID * 0x1E + 1];
        sndFXCtrl(voice, 0x5b, val);
        return TRUE;
    }
    return FALSE;
}

// .text:0x000E3668 size:0xFC mapped:0x807226FC
void updatePlantAimingOrCatch(YoshiPlantObj* plant) {
    if (updatePlantCatchState(plant)) {
        tryPlantCatchAndBeginSpitAim(plant);
    } else {
        fn_3_E2034(plant);
    }
}

// .text:0x000E3764 size:0x1B0 mapped:0x807227F8
void ParkPlantsPopUp(YoshiPlantObj* plant) {
    plant->stateFrame++;
    plant->scale = plant->scale + 1.0857142857142859 / plant->stateDuration;
    CTRLSetScale((Control*)plant, plant->scale, plant->scale, plant->scale);
    plant->pos.y = -(1.2 * plant->scale);
    CTRLSetTranslation((Control*)plant, plant->pos.x, -plant->pos.y, plant->pos.z);
    if (updatePlantCatchState(plant)) {
        if (tryPlantCatchAndBeginSpitAim(plant)) {
            return;
        }
    } else {
        fn_3_E2034(plant);
    }
    if (plant->stateFrame >= plant->stateDuration) {
        plant->state = PLANT_TRACKING;
    }
}

// .text:0x000E3914 size:0x274 mapped:0x807229A8
void fn_3_E3914(YoshiPlantObj* plant) {
    static const u8 popUpDurations[3] = { 20, 20, 20 };
    Vec head;
    Vec delta;
    int stadiumID;
    u8 vol;
    u8 val;
    SND_VOICEID voice;

    if (plant->_C7 != 0) {
        return;
    }
    if (g_Ball.AtBat_ContactResult >= BALL_RESULT_TYPE_FIELDED) {
        return;
    }
    if (g_Ball.AtBat_Contact_BallPos.y > 11.0) {
        return;
    }
    head = plant->pos;
    head.y += 1.4;
    PSVECSubtract((Vec*)&g_Ball.AtBat_Contact_BallPos, &head, &delta);
    delta.y = 0.0f;
    if (PSVECMag(&delta) <= 12.5) {
        if ((g_Ball.currentStarSwing2 == 3) | (g_Ball.currentStarSwing2 == 4) | (g_Ball.currentStarSwing2 == 11) |
            (g_Ball.currentStarSwing2 == 12)) {
            return;
        }
        plant->state = PLANT_POP_UP;
        fn_3_E25D0(plant, 1);
        if (plant->_C9 == 0) {
            plant->plantType = rng(100) / 70;
        } else {
            plant->plantType = 0;
        }
        plant->stateFrame = 0;
        plant->stateDuration = popUpDurations[rng(3)];
        plant->_C7 = 1;
        stadiumID = g_d_GameSettings.StadiumID;
        vol = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                  ? lbl_3_data_84B8[6]
                  : stadiumHazardSoundFxRelated[stadiumID * 0x1E + 6];
        voice = sndFXStartEx(stadiumHazardSoundIDs[stadiumID] + 3, vol, 0x3f, 0);
        val = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                  ? lbl_3_data_84B8[7]
                  : stadiumHazardSoundFxRelated[stadiumID * 0x1E + 7];
        sndFXCtrl(voice, 0x5b, val);
    }
}

// .text:0x000E3B88 size:0x9CC mapped:0x80722C1C
void controlYoshiParkPlants(YoshiPlantObj* plant) {
    Mtx joint;
    Mtx m;

    if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
        if (plant->state != PLANT_IDLE) {
            fn_3_E48D0(plant);
        } else if (plant->_C7 != 0) {
            fn_3_E45F0(plant);
            fn_3_E4554(plant);
            if (plant->holdingBall) {
                setBallInactiveVariables();
                plant->holdingBall = FALSE;
                plant->rotationSpeed = 0.0f;
            }
            plant->_C7 = 0;
        }
    } else {
        if (plant->holdingBall) {
            Vec held = { 0.0f, 0.0f, 0.0f };

            PSMTXCopy(((YoshiModelRootJoints*)((StadiumModel*)plant->actor)->root)->joints->holdNode->worldMtx, joint);
            CTRLBuildMatrix((Control*)plant, m);
            PSMTXConcat(m, joint, m);
            PSMTXMultVec(m, &held, &held);
            held.y *= -1.0f;
            g_Ball.AtBat_Contact_BallPos.x = held.x;
            g_Ball.AtBat_Contact_BallPos.y = held.y;
            g_Ball.AtBat_Contact_BallPos.z = held.z;
        }
        if (g_Ball.AtBat_ContactResult >= BALL_RESULT_TYPE_FIELDED && plant->state != PLANT_IDLE &&
            plant->state != PLANT_SHRINK) {
            plant->state = PLANT_SHRINK;
            if (plant->curAnim != 1) {
                fn_3_E25D0(plant, 9);
            } else {
                setAllBoneEventFlags(plant->actor->actor, FALSE);
            }
        }
        switch (plant->state) {
        case PLANT_IDLE:
            fn_3_E3914(plant);
            break;
        case PLANT_POP_UP:
            ParkPlantsPopUp(plant);
            break;
        case PLANT_TRACKING:
            updatePlantAimingOrCatch(plant);
            break;
        case PLANT_SPIT:
            nadoRelated(plant);
            break;
        case PLANT_STAR:
            yoshiParkPlantRelated(plant);
            break;
        case PLANT_SHRINK:
            updateStadiumObjStateAndTransform(plant);
            break;
        }
    }
    advancePlantInteractionPhase(plant);
    if (plant->state != PLANT_IDLE && plant->state < PLANT_SHRINK && plant->plantType == 0) {
        fn_3_E2324(plant);
    }
}

// .text:0x000E4554 size:0x54 mapped:0x807235E8
void fn_3_E4554(YoshiPlantObj* plant) {
    plant->animBank = plantAnimationPointers[0];
    actorSetAnimBank(plant->actor, plant->animBank);
    plant->animFrame = plant->actor->animFrame;
    plant->curAnim = 0;
}

// .text:0x000E45A8 size:0x48 mapped:0x8072363C
void fn_3_E45A8(YoshiPlantObj* plant) {
    CTRLSetScale((Control*)plant, 0.2f, 0.2f, 0.2f);
    plant->scale = 0.2f;
}

// .text:0x000E45F0 size:0x68 mapped:0x80723684
void fn_3_E45F0(YoshiPlantObj* plant) {
    CTRLSetRotation((Control*)plant, 0.0f, parkPlantData[plant->index].rotation, 0.0f);
    plant->rotation = parkPlantData[plant->index].rotation;
}

// .text:0x000E4658 size:0x108 mapped:0x807236EC
void fn_3_E4658(YoshiPlantObj* plant) {
    ((Control*)plant)->type = 0;
    CTRLSetTranslation((Control*)plant, parkPlantData[plant->index].x, 0.24f + parkPlantData[plant->index].y,
                       parkPlantData[plant->index].z);
    PSVECScale((Vec*)&parkPlantData[plant->index], 1.0f, &plant->pos);
    plant->pos.y -= 0.24f;
    fn_3_E45F0(plant);
    fn_3_E45A8(plant);
}

// .text:0x000E4760 size:0x170 mapped:0x807237F4
void fn_3_E4760(YoshiPlantObj* plant) {
    fn_3_E4658(plant);
    fn_3_E4554(plant);
    plant->stateFrame = 0;
    plant->state = PLANT_IDLE;
    plant->_C7 = 0;
    plant->plantType = 0;
    if (plant->holdingBall) {
        setBallInactiveVariables();
        plant->holdingBall = FALSE;
        plant->rotationSpeed = 0.0f;
    }
    plant->_C9 = 0;
}

// .text:0x000E48D0 size:0x168 mapped:0x80723964
void fn_3_E48D0(YoshiPlantObj* plant) {
    fn_3_E4658(plant);
    fn_3_E4554(plant);
    plant->stateFrame = 0;
    plant->state = PLANT_IDLE;
    plant->_C7 = 0;
    plant->plantType = 0;
    if (plant->holdingBall) {
        setBallInactiveVariables();
        plant->holdingBall = FALSE;
        plant->rotationSpeed = 0.0f;
    }
}

// .text:0x000E4A38 size:0x1B0 mapped:0x80723ACC
void fn_3_E4A38(Mtx m, StadiumMeshData* mesh) {
    int count;
    StadiumVertexGroup* p = mesh->groups;
    Vec out;
    Vec ball;
    f32 minX = 10000.0f;
    f32 minY = minX;
    f32 minZ = minX;
    f32 maxX = -10000.0f;
    f32 maxY = maxX;
    f32 maxZ = maxX;
    u32 n;

    while (TRUE) {
        n = p->vertexCount;
        if (n == 0) {
            break;
        }
        if (p->isTriangleStrip != 0) {
            count = n + 2;
        } else {
            count = n * 3;
        }
        p = (StadiumVertexGroup*)p->vertices;
        do {
            if (lbl_3_bss_AE01 == 0) {
                PSMTXMultVec(m, (Vec*)p, &out);
            } else {
                PSVECScale((Vec*)p, 1.0f, &out);
            }
            p = (StadiumVertexGroup*)((StadiumVertex*)p + 1);
            if (minX > out.x) {
                minX = out.x;
            }
            if (minY > out.y) {
                minY = out.y;
            }
            if (minZ > out.z) {
                minZ = out.z;
            }
            if (maxX < out.x) {
                maxX = out.x;
            }
            if (maxY < out.y) {
                maxY = out.y;
            }
            if (maxZ < out.z) {
                maxZ = out.z;
            }
        } while (--count != 0);
    }
    PSVECScale((Vec*)&g_Ball.AtBat_Contact_BallPos, 1.0f, &ball);
}

// .text:0x000E4BE8 size:0xC8 mapped:0x80723C7C
TriangleGroup* fn_3_E4BE8(int offset, Mtx m) {
    YoshiPlantObj* plant = (YoshiPlantObj*)&stadiumObjectCollision.objects[offset];
    Mtx joint;

    CTRLBuildMatrix((Control*)plant, m);
    if (plant->_9D == 0) {
        if (plant->plantType == 0 || plant->state == PLANT_IDLE || plant->state == PLANT_SHRINK || plant->state == PLANT_STAR) {
            return NULL;
        }
        PSMTXCopy(((YoshiModelRootJoints*)((StadiumModel*)plant->actor)->root)->joints->headNode->worldMtx, joint);
        PSMTXConcat(m, joint, m);
    }
    return stadiumObjectCollision.objects[offset].triangles;
}

// .text:0x000E4CB0 size:0x244 mapped:0x80723D44
void processYoshiParkPlantBoundingBoxes(s32* idx, s32* count) {
    YoshiPlantPlacement* cfg;
    int off;
    int i;
    int j;
    StadiumObject* obj;
    Vec pos;
    Mtx m;
    YoshiObjControl ctrl;

    for (i = 0; i < 10; i++) {
        off = (u16)(stadiumObjectCollision.vertexOffsets[*idx - 1] + stadiumObjectCollision.hazardData[*idx - 1]);
        stadiumObjectCollision.vertexOffsets[*idx] = off;
        initBoundingBoxLimits();
        cfg = parkPlantData;
        for (j = 0; j < 10; cfg++, j++) {
            if (i == cfg->group && cfg->usedFlag != 2) {
                if (stadiumObjectCollision.objects[*count]._90b1) {
                    ((s32*)stadiumObjectCollision.vertexData)[off] = *count;
                    off++;
                    stadiumObjectCollision.hazardData[*idx]++;
                    obj = &stadiumObjectCollision.objects[*count];
                    ctrl = *(YoshiObjControl*)obj;
                    CTRLGetTranslation(&ctrl.ctrl, &pos.x, &pos.y, &pos.z);
                    CTRLSetTranslation(&ctrl.ctrl, pos.x - 4.0, pos.y, pos.z - 4.0);
                    CTRLBuildMatrix(&ctrl.ctrl, m);
                    transformVectorsUpdateBoundingBox(m, (StadiumMeshData*)obj->triangles);
                    CTRLSetTranslation(&ctrl.ctrl, 4.0 + pos.x, pos.y - 10.0, 4.0 + pos.z);
                    CTRLBuildMatrix(&ctrl.ctrl, m);
                    transformVectorsUpdateBoundingBox(m, (StadiumMeshData*)obj->triangles);
                    (*count)++;
                }
            }
        }
        if ((u32)stadiumObjectCollision.hazardData[*idx] != 0) {
            storeBoundingBoxCoordinates(&((Vec*)stadiumObjectCollision.vertexDataArray)[*idx * 2],
                                        &((Vec*)stadiumObjectCollision.vertexDataArray)[*idx * 2 + 1]);
            (*idx)++;
        }
    }
}

// .text:0x000E4EF4 size:0xD0 mapped:0x80723F88
void fn_3_E4EF4(void) {
    s32 idx;
    s32 count;
    u32 size = stadiumObjectCollision.objectCount * sizeof(VecSrcDst) +
               stadiumObjectCollision.objectCount * sizeof(s32) +
               stadiumObjectCollision.objectCount * sizeof(f32) +
               stadiumObjectCollision.objectCount * sizeof(u16);

    if (stadiumObjectCollision.vertexDataArray == NULL) {
        stadiumObjectCollision.vertexDataArray = (VecSrcDst*)_OSAllocFromHeap(4, size);
        stadiumObjectCollision.hazardData = (s32*)(stadiumObjectCollision.vertexDataArray + stadiumObjectCollision.objectCount);
        stadiumObjectCollision.vertexData = (f32*)(stadiumObjectCollision.hazardData + stadiumObjectCollision.objectCount);
        stadiumObjectCollision.vertexOffsets = (u16*)(stadiumObjectCollision.vertexData + stadiumObjectCollision.objectCount);
    }
    memset(stadiumObjectCollision.vertexDataArray, 0, size);
    idx = 0;
    count = 0;
    processYoshiParkPlantBoundingBoxes(&idx, &count);
    stadiumObjectCollision.boundingBoxCount = idx;
}

// .text:0x000E4FC4 size:0x8B8 mapped:0x80724058
void loadYoshiPark(void** files) {
    u8** animTable = (u8**)(hugeAnimStruct + 0x6C);
    YoshiPlantPlacement* cfg;
    StadiumObject* o;
    ACTActor* act;
    u32* ids;
    u8 done = FALSE;
    u8 plantCount;
    u8 animCount;
    u8 idx;
    u8 count = 0;
    u32 shadowBit;
    int i;
    int k;
    s32 n;

    stadiumObjectCollision.preUpdateFunc = updateGameStatusFlag;
    stadiumObjectCollision.updateFunc = fn_3_E1DB8;
    ambientActive = FALSE;
    ids = _OSAllocFromHeap(4, 0x38);
    stadiumObjectCollision._34 = ids;
    processStadiumFileObjects(enumObjTypeInFile_ARRAY_807ca604, 0xE, (u8*)files, ids);

    for (i = 0; i < 10; i++) {
        if (parkPlantData[i].usedFlag == 2) {
            break;
        }
    }
    plantCount = i;
    animCount = plantCount + 1;
    *animTable = ActorObjectInitTable(animCount);
    stadiumObjectCollision.propCount = animCount;
    idx = 0;
    for (i = 0; i < plantCount; i++) {
        animateBallRelated(*animTable, idx, idx, files[ids[1]], 0, (int)files[ids[1] + 2]);
        fn_3_B98E8((StadiumAnimData*)(*animTable + i * 0x90 + 0x34));
        idx++;
    }
    animateBallRelated(*animTable, idx, idx, files[ids[2]], 0, 0);
    actorSetAnimBank((ACTActor*)(*animTable + idx * 0x90 + 0x34), (u32)files[ids[2] + 2]);
    act = (ACTActor*)(*animTable + idx * 0x90 + 0x34);
    act->animFrame = 180.0f;
    act->applyFrame = 1;
    setActorAnimFrame(act->actor, act->animFrame);
    for (k = 0; k < 10; k++) {
        plantAnimationPointers[k] = (u32)files[ids[k + 4]];
    }
    for (i = 0; i < animCount; i++) {
        fn_800BD548(*animTable + i * 0x90 + 0x34, 4, stadiumObjectCollision.lights[0],
                    stadiumObjectCollision.lights[1], stadiumObjectCollision.lights[2],
                    stadiumObjectCollision.lights[3]);
    }

    stadiumObjectCollision.objectCount = 0x14;
    stadiumObjectCollision.objects = _OSAllocFromHeap(0x20, 0x1220);
    memset(stadiumObjectCollision.objects, 0, 0x1220);
    stadiumObjectCollision.objectsRelated = _OSAllocFromHeap(0x20, 0x1220);
    memset(stadiumObjectCollision.objectsRelated, 0, 0x1220);
    o = stadiumObjectCollision.objects;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        stadiumObjectCollision.preUpdateFunc = NULL;
    } else {
        i = 0;
        cfg = parkPlantData;
        lbl_3_bss_AE13 = 0;
        do {
            if (cfg->usedFlag == 2) {
                done = TRUE;
            }
            if (done) {
                for (k = i; k < 11; k++) {
                    parkPlantData[k].usedFlag = 2;
                }
                break;
            }
            ((YoshiPlantObj*)o)->index = i;
            ((YoshiPlantObj*)o)->_9D = 0;
            ((YoshiPlantObj*)o)->plantID = cfg->group;
            o->model = (StadiumModel*)(*animTable + i * 0x90 + 0x34);
            o->triangles = files[ids[3]];
            o->callback = (void (*)(void))controlYoshiParkPlants;
            o->func = (int (*)(int, int, void*))fn_3_E2118;
            o->hasShadow = 1;
            shadowBit = 0;
            if (o->hasShadow && o->triangles != NULL) {
                shadowBit = 1;
            }
            o->_90b1 = shadowBit;
            o->shadowEnabled = 1;
            fn_3_E4658((YoshiPlantObj*)o);
            fn_3_E4554((YoshiPlantObj*)o);
            i++;
            cfg++;
            count++;
            o->fadeByDepth = 0;
            o->alpha = 0xFF;
            o->preDraw = (void (*)(StadiumObject*))fn_3_E22A4;
            o->effect = NULL;
            o->animActive = 0;
            o->animIndex = -1;
            o->drawPass = 1;
            o++;
            lbl_3_bss_AE14++;
        } while (i < 10);
    }

    lbl_3_bss_AE11 = count;
    ((YoshiPlantObj*)o)->index = 0;
    ((YoshiPlantObj*)o)->_9D = 1;
    ((YoshiPlantObj*)o)->plantID = 0;
    o->model = (StadiumModel*)(*animTable + idx * 0x90 + 0x34);
    o->triangles = NULL;
    o->callback = (void (*)(void))fn_3_E1FA8;
    o->func = NULL;
    o->hasShadow = 1;
    o->_90b1 = 0;
    o->shadowEnabled = 0;
    ((Control*)o)->type = 0;
    o->fadeByDepth = 0;
    o->alpha = 0xFF;
    o->preDraw = NULL;
    o->effect = NULL;
    o->animActive = 0;
    o->animIndex = -1;
    o->drawPass = 1;
    o++;
    n = count + 1;
    stadiumObjectCollision.objectCount = n;
    lbl_3_bss_AE12++;
    if (n < stadiumObjectCollision.objectCount) {
        for (; n < stadiumObjectCollision.objectCount; n++) {
            ((YoshiPlantObj*)o)->_9D = 0;
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
        }
    }

    stadiumObjectCollision.vertexDataArray = NULL;
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES) {
        fn_3_E4EF4();
    }
}

