#ifndef __GAME_STADIUM_STADIUM_WARIO_PALACE_H_
#define __GAME_STADIUM_STADIUM_WARIO_PALACE_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "game/stadium/stadium_framework.h"

typedef struct _PalaceHazeParticle {
    /*0x00*/ struct _PalaceHazeParticle* next;
    /*0x04*/ Vec origin;
    /*0x10*/ f32 velX;
    /*0x14*/ f32 _14;
    /*0x18*/ f32 velZ;
    /*0x1C*/ f32 scale;
    /*0x20*/ f32 _20;
    /*0x24*/ f32 alpha;
    /*0x28*/ u8 _28[0x38 - 0x28];
    /*0x38*/ f32 _38;
    /*0x3C*/ f32 _3C;
    /*0x40*/ u8 _40[3];
    /*0x43*/ u8 alphaByte;
    /*0x44*/ u8 _44[4];
    /*0x48*/ s16 _48;
    /*0x4A*/ s16 _4A;
    /*0x4C*/ u8 index;
    /*0x4D*/ u8 _4D;
    /*0x4E*/ u8 _4E;
    /*0x4F*/ u8 _4F;
} PalaceHazeParticle;

typedef struct _PalaceHazeEmitter {
    /*0x00*/ u8 _00[0x0C];
    /*0x0C*/ PalaceHazeParticle* particles;
    /*0x10*/ u32 _10;
    /*0x14*/ u8 _14[4];
    /*0x18*/ Vec origin;
    /*0x24*/ u8 kind;
    /*0x25*/ u8 _25;
} PalaceHazeEmitter;

typedef struct _ChainChompPhysicsParams {
    /*0x00*/ f32 restLength;
    /*0x04*/ f32 restitution;
    /*0x08*/ f32 stiffness;
    /*0x0C*/ f32 damping;
    /*0x10*/ f32 groundFriction;
    /*0x14*/ f32 dragCoefficient;
    /*0x18*/ f32 externalForceScale;
    /*0x1C*/ f32 dampingA;
    /*0x20*/ s32 solverIterations;
    /*0x24*/ f32 dampingB;
} ChainChompPhysicsParams;

typedef struct _PalaceChompPlacement {
    /*0x00*/ Vec position;
    /*0x0C*/ u8 usedFlag;
    /*0x0D*/ u8 _0D[3];
    /*0x10*/ Vec awakeRotation;
    /*0x1C*/ Vec sleepRotation;
    /*0x28*/ u8 _28[8];
    /*0x30*/ u8 sideSelector;
    /*0x31*/ u8 _31[3];
} PalaceChompPlacement; // size: 0x34

typedef enum _PalaceChompState {
    PALACE_CHOMP_ASLEEP = 0,
    PALACE_CHOMP_AWAKE = 1,
    PALACE_CHOMP_WAKING = 2,
    PALACE_CHOMP_STALKING = 3,
    PALACE_CHOMP_ATTACKING = 4,
    PALACE_CHOMP_HOPPING_HOME = 5,
} PalaceChompState;

typedef struct _PalaceChompObj {
    /*0x00*/ u8 _00[0x8C];
    /*0x8C*/ StadiumObjectEffect* effect;
    /*0x90*/ u8 hasShadow : 1;
    /*0x90*/ u8 _90b : 7;
    /*0x91*/ u8 _91[8];
    /*0x99*/ u8 flags;
    /*0x9A*/ u8 _9A[2];
    /*0x9C*/ u8 index;
    /*0x9D*/ u8 _9D[3];
    /*0xA0*/ Vec pos;
    /*0xAC*/ Vec velo;
    /*0xB8*/ Vec* homePos;
    /*0xBC*/ f32 targetYaw;
    /*0xC0*/ f32 yaw;
    /*0xC4*/ StadiumLink* links;
    /*0xC8*/ s16 attacksRemaining;
    /*0xCA*/ u8 state;
    /*0xCB*/ u8 priorState;
    /*0xCC*/ u8 _CC;
    /*0xCD*/ u8 _CD;
    /*0xCE*/ u8 _CE[0xE8 - 0xCE];
} PalaceChompObj; // size: 0xE8

extern PalaceChompPlacement chompPlacementConfig[];

typedef struct _PalaceTornadoPlacement {
    /*0x00*/ Vec restPos;
    /*0x0C*/ u8 usedFlag;
    /*0x0D*/ u8 _0D;
    /*0x0E*/ u8 group;
    /*0x0F*/ u8 _0F;
    /*0x10*/ f32 restYaw;
    /*0x14*/ u8 _14[0x0C];
    /*0x20*/ f32 rangeBaseA;
    /*0x24*/ f32 rangeSpanA;
    /*0x28*/ f32 rangeBaseB;
    /*0x2C*/ f32 rangeSpanB;
    /*0x30*/ f32 spinRate;
} PalaceTornadoPlacement; // size: 0x34

extern PalaceTornadoPlacement TornadoPlacementConfig[];

s16 rng(int max);

typedef struct _PalaceEffectParticle {
    /*0x00*/ struct _PalaceEffectParticle* next;
    /*0x04*/ Vec pos;
    /*0x10*/ Vec vel;
    /*0x1C*/ Vec prevPos;
    /*0x28*/ u8 _28[0x38 - 0x28];
    /*0x38*/ f32 sizeA;
    /*0x3C*/ f32 sizeB;
    /*0x40*/ u8 colorR;
    /*0x41*/ u8 colorG;
    /*0x42*/ u8 colorB;
    /*0x43*/ u8 alpha;
    /*0x44*/ u8 _44[4];
    /*0x48*/ s16 age;
    /*0x4A*/ s16 lifetime;
    /*0x4C*/ u8 _4C;
    /*0x4D*/ u8 kind;
    /*0x4E*/ u8 _4E;
    /*0x4F*/ u8 _4F;
} PalaceEffectParticle; // size: 0x50

typedef struct _PalaceEffect {
    /*0x00*/ u8 _00[0x08];
    /*0x08*/ void* link;
    /*0x0C*/ PalaceEffectParticle* particles;
    /*0x10*/ u32 _10;
    /*0x14*/ u8 _14[4];
    /*0x18*/ s32 _18;
    /*0x1C*/ u8 _1C[4];
    /*0x20*/ void* owner;
} PalaceEffect;

typedef struct _PalaceScaleSource {
    /*0x00*/ u8 _00[0xBC];
    /*0xBC*/ f32 scale;
} PalaceScaleSource;

typedef struct _PalaceHazeObj {
    /*0x00*/ u8 _00[0x90];
    /*0x90*/ u8 hasShadow : 1;
    /*0x90*/ u8 _90b : 7;
    /*0x91*/ u8 _91;
    /*0x92*/ u8 alpha;
    /*0x93*/ u8 _93[0x0D];
    /*0xA0*/ StadiumObject* source;
    /*0xA4*/ PalaceScaleSource* scaleSrc;
    /*0xA8*/ PalaceEffect* effect;
} PalaceHazeObj;

typedef struct _PalaceNadoRingObj {
    /*0x00*/ u8 _00[0x90];
    /*0x90*/ u8 hasShadow : 1;
    /*0x90*/ u8 _90b : 7;
    /*0x91*/ u8 _91;
    /*0x92*/ u8 alpha;
    /*0x93*/ u8 _93[0x0D];
    /*0xA0*/ StadiumObject* source;
    /*0xA4*/ f32 baseX;
    /*0xA8*/ u8 _A8[4];
    /*0xAC*/ f32 baseZ;
    /*0xB0*/ f32 offsetX;
    /*0xB4*/ u8 _B4[4];
    /*0xB8*/ f32 offsetZ;
    /*0xBC*/ f32 radius;
} PalaceNadoRingObj;

typedef struct _PalaceNadoObj {
    /*0x00*/ u8 _00[0x74];
    /*0x74*/ StadiumModel* model;
    /*0x78*/ u8 _78[0x24];
    /*0x9C*/ u8 index;
    /*0x9D*/ u8 _9D[3];
    /*0xA0*/ Vec pos;
    /*0xAC*/ Quaternion quat;
    /*0xBC*/ f32 speed;
    /*0xC0*/ f32 yaw;
    /*0xC4*/ f32 _C4;
    /*0xC8*/ f32 _C8;
    /*0xCC*/ f32 spread;
    /*0xD0*/ s8 dir;
    /*0xD1*/ u8 state;
    /*0xD2*/ u8 _D2[0x16];
} PalaceNadoObj;

typedef struct _PalaceSpinObj {
    /*0x00*/ u8 _00[0x74];
    /*0x74*/ ACTActor* model;
    /*0x78*/ u8 _78[0x18];
    /*0x90*/ u8 hasShadow : 1;
    /*0x90*/ u8 _90b : 7;
    /*0x91*/ u8 _91[0x0B];
    /*0x9C*/ u8 index;
    /*0x9D*/ u8 _9D[3];
    /*0xA0*/ f32 frame;
    /*0xA4*/ f32 rate;
    /*0xA8*/ u8* stateFlag;
    /*0xAC*/ u8 timer;
    /*0xAD*/ u8 _AD;
} PalaceSpinObj;

typedef struct _PalaceSlotObject {
    /*0x00*/ u8 _00[0xAC];
    /*0xAC*/ u8 animPhase;
} PalaceSlotObject;

typedef struct _PalaceStarActor {
    /*0x00*/ u8 _00[0x0C];
    /*0x0C*/ f32 frame;
    /*0x10*/ f32 rate;
    /*0x14*/ u8 _14[0x1A - 0x14];
    /*0x1A*/ s16 _1A;
    /*0x1C*/ u8 _1C[0x24 - 0x1C];
    /*0x24*/ u16 endFrame;
    /*0x26*/ u8 _26[0x58 - 0x26];
    /*0x58*/ u8 _58;
} PalaceStarActor;

typedef struct _PalaceStarObj {
    /*0x00*/ u8 _00[0x8C];
    /*0x8C*/ PalaceStarActor* actor;
    /*0x90*/ u8 hasShadow : 1;
    /*0x90*/ u8 _90b : 7;
    /*0x91*/ u8 _91;
    /*0x92*/ u8 alpha;
    /*0x93*/ u8 _93[9];
    /*0x9C*/ u8 index;
    /*0x9D*/ u8 _9D[3];
    /*0xA0*/ PalaceEffect* effect;
    /*0xA4*/ u8 awarded;
} PalaceStarObj;

void fn_3_CB8A8(StadiumObject* obj);
void fn_3_CBA9C(StadiumObject* obj);
void fn_3_CBAFC(StadiumObject* obj);
void fn_3_CBC18(StadiumObject* obj);
void palaceStadiumObjTransformationAndPhysics(StadiumObject* obj);
void fn_3_CC1D4(void);
void fn_3_CC354(StadiumLink* links);
void fn_3_CC438(void);
void mPalaceObjHandling(StadiumObject* obj);
void maybeChainChompSprintCTRLRelated(void);
void palaceMinigameObjectLoading(void** files, u32* ids);
void fn_3_CD958(void);
BOOL fn_3_CD968(Vec* p, f32 w, f32 h);
void fn_800528C0(f32 x, f32 y, f32 z, s16* outX, s16* outY);
void fn_80033620(void* emitter);
void fn_8003403C(f32 w, f32 h);
void fn_80033CC8(void* particle, int arg);
void fn_3_CDB48(PalaceHazeParticle* p, PalaceHazeEmitter* emitter);
void fn_3_CDD90(PalaceHazeParticle* p);
BOOL fn_3_CDFA4(PalaceHazeEmitter* emitter);
void palaceHazeTextureMaybe(PalaceHazeEmitter* emitter, u8 kind);
void warioPalaceSomething(void);
void fn_3_CE954(void);
void fn_3_CEBBC(Vec* p, int idx);
void fn_3_CEC98(void);
void fn_3_CED30(void);
void fn_3_CED34(void);
void fn_3_CED38(void);
void fn_3_CED3C(void);
void fn_3_CED40(PalaceEffectParticle* p, u32 arg);
void fn_3_CEE5C(PalaceEffectParticle* p, u32 arg);
BOOL fn_3_CEFA8(PalaceEffect* effect);
void fn_3_CF278(PalaceStarObj* obj, Vec* pos);
void starHitAnimation(int idx);
void fn_3_CF92C(void);
void warioPalaceSandStarRelated(PalaceStarObj* obj);
void fn_3_CFA88(void);
void fn_3_CFA8C(StadiumObject* obj);
void fn_3_CFAB4(PalaceEffectParticle* p, PalaceEffect* effect);
BOOL fn_3_CFB44(PalaceEffect* effect);
void fn_3_CFD58(PalaceHazeObj* obj);
void fn_3_D00CC(void);
void fn_3_D00D0(PalaceHazeObj* obj);
void fn_3_D0280(void);
void fn_3_D0284(PalaceNadoRingObj* obj);
void fn_3_D0490(void);
void fn_3_D0528(void);
int fn_3_D052C(void);
void fn_3_D0534(PalaceNadoObj* obj);
f32 fn_3_D0854(StadiumObject* obj);
void palaceNadoLogic(PalaceNadoObj* obj);
void fn_3_D1004(PalaceNadoObj* obj, f32 x, f32 y, f32 z, f32 restYaw, f32 yaw);
void fn_3_D1110(PalaceNadoObj* obj);
void fn_3_D127C(void);
void maybePalaceCTRLRelated(StadiumObject* obj);
void fn_3_D141C(StadiumObject* obj);
void applyTransformationToPalaceObjs(StadiumObject* obj);
void fn_3_D1848(PalaceSpinObj* obj);
void fn_3_D196C(int idx);
void fn_3_D1AC4(StadiumObject* obj);
void chainChomp_colveSpringForces(ChainChompPhysicsParams* params, StadiumLink* links, int count, Vec* force);
void chainChomp_simulateAndCollide(ChainChompPhysicsParams* params, StadiumLink* links, int count, Vec* force,
                                   StadiumObject* owner);
void fn_3_D2220(StadiumObject* obj);
struct _InMemBallType* fn_3_D233C(StadiumObject* obj);
BOOL fn_3_D249C(StadiumObject* obj);
void fn_3_D24E8(PalaceChompObj* obj, s8 fielderIdx);
s8 fn_3_D255C(PalaceChompObj* obj);
Vec* fn_3_D2684(StadiumObject* obj);
void fn_3_D278C(PalaceChompObj* obj);
void chomp_attack(PalaceChompObj* obj);
void chompState3_longDistanceAttack_Stalk(PalaceChompObj* obj);
void fn_3_D36B0(PalaceChompObj* obj);
void chompState1_awake(PalaceChompObj* obj);
void chompState0(PalaceChompObj* obj);
void palaceChainChompControl(PalaceChompObj* obj);
void fn_3_D4780(StadiumObject* obj);
void someCTRLButNotCalled(PalaceChompObj* obj);
void someCTRLButNotCalled2(PalaceChompObj* obj);
void fn_3_D501C(StadiumLink* links);
void fn_3_D511C(void);
int fn_3_D53C0(u8 id);
int fn_3_D5444(const u32* a, const u32* b);
int fn_3_D5470(const f32* a, const f32* b);
void fn_3_D5494(Mtx view);
struct _StadiumDrawOrder;
void processPalaceObjectCollisions(Mtx view, struct _StadiumDrawOrder* order);
void fn_3_D5B6C(s32* idx);
void fn_3_D5C8C(s32* idx);
void stadiumObjCollisionRelated_Palace(s32* idx);
void fn_3_D60C0(s32* idx);
void fn_3_D62F0(s32* idx);
void fn_3_D6514(void);
void loadWarioPalace(void** files);

#endif // !__GAME_STADIUM_STADIUM_WARIO_PALACE_H_
