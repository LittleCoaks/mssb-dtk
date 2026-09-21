#ifndef __GAME_STADIUM_STA_C5_H_
#define __GAME_STADIUM_STA_C5_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "game/ball/collision_primitives.h"
#include "game/stadium/stadium_framework.h"

typedef struct _DKJungleAnimNode {
    /*0x00*/ u8 _00[0x60];
    /*0x60*/ u8 _60;
    /*0x61*/ u8 _61[0xA4 - 0x61];
    /*0xA4*/ u8 _A4;
} DKJungleAnimNode;

typedef struct _DKJungleAnimList {
    /*0x00*/ u8 _00[6];
    /*0x06*/ u16 count;
    /*0x08*/ u8 _08[0x10];
    /*0x18*/ DKJungleAnimNode** nodes;
} DKJungleAnimList;

typedef struct _DKJungleActor {
    /*0x00*/ DKJungleAnimList* list;
    /*0x04*/ u8 _04[0x54];
    /*0x58*/ u8 applyAnimation;
    /*0x59*/ u8 _59;
    /*0x5A*/ u8 _5A[2];
    /*0x5C*/ f32 animFrame;
} DKJungleActor;

typedef struct _DKJungleObject {
    /*0x00*/ u8 _00[0x74];
    /*0x74*/ DKJungleActor* actor;
} DKJungleObject;

// Control local that has the size of the whole per-object control block (0x44).
typedef struct _DKJungleObjControl {
    Control ctrl;
    u8 _34[0x44 - sizeof(Control)];
} DKJungleObjControl;

typedef struct _DKJungleKlaptrapData {
    /*0x00*/ Vec pos;
    /*0x0C*/ f32 rotY;
    /*0x10*/ u8 usedFlag;
    /*0x11*/ u8 _11;
    /*0x12*/ u8 _12;
    /*0x13*/ u8 _13;
    /*0x14*/ u8 kind;
    /*0x15*/ u8 _15[3];
} DKJungleKlaptrapData; // size: 0x18

typedef struct _DKJungleKlaptrap {
    /*0x00*/ u8 ctrlType;
    /*0x01*/ u8 _01[0x73];
    /*0x74*/ DKJungleActor* actor;
    /*0x78*/ u8 _78[0x90 - 0x78];
    /*0x90*/ u8 hasShadow : 1;
    /*0x90*/ u8 _90b : 7;
    /*0x91*/ u8 _91[8];
    /*0x99*/ u8 _99;
    /*0x9A*/ u8 _9A[2];
    /*0x9C*/ u8 index;
    /*0x9D*/ u8 _9D[3];
    /*0xA0*/ Vec pos;
    /*0xAC*/ f32 rotY;
    /*0xB0*/ f32 _B0;
    /*0xB4*/ f32 turnAngle;
    /*0xB8*/ f32 hitAngle;
    /*0xBC*/ f32 _BC;
    /*0xC0*/ u8 _C0;
    /*0xC1*/ s8 _C1;
    /*0xC2*/ u8 _C2;
    /*0xC3*/ s8 _C3;
    /*0xC4*/ s8 turnDir;
    /*0xC5*/ u8 kind;
    /*0xC6*/ u8 state;
    /*0xC7*/ u8 timer;
    /*0xC8*/ u8 awarded;
} DKJungleKlaptrap;

// Entry of the hugeAnimStruct object table at +0x2C50 that a klaptrap can be carried by.
typedef struct _DKJungleCarrier {
    /*0x000*/ u8 _000[0x44];
    /*0x044*/ f32 rotY;
    /*0x048*/ u8 _048[0x254 - 0x48];
    /*0x254*/ s8 animIdx;
    /*0x255*/ s8 ownerId;
    /*0x256*/ u8 _256[4];
    /*0x25A*/ u8 _25A;
    /*0x25B*/ u8 _25B[2];
    /*0x25D*/ u8 _25D;
} DKJungleCarrier;

// Barrel object in stadiumObjectCollision.objects; shares its leading layout with DKJungleKlaptrap.
typedef struct _DKJungleBarrel {
    /*0x00*/ u8 ctrlType;
    /*0x01*/ u8 _01[0x73];
    /*0x74*/ DKJungleActor* actor;
    /*0x78*/ u8 _78[0x90 - 0x78];
    /*0x90*/ u8 hasShadow : 1;
    /*0x90*/ u8 _90b : 7;
    /*0x91*/ u8 _91[8];
    /*0x99*/ u8 _99;
    /*0x9A*/ u8 _9A[2];
    /*0x9C*/ u8 index;
    /*0x9D*/ u8 _9D[3];
    /*0xA0*/ Vec pos;
    /*0xAC*/ f32 rotY;
    /*0xB0*/ f32 _B0;
    /*0xB4*/ f32 _B4;
    /*0xB8*/ f32 velY;
    /*0xBC*/ f32* pathAngle;
    /*0xC0*/ u8 _C0;
    /*0xC1*/ u8 _C1;
    /*0xC2*/ u8 _C2[2];
    /*0xC4*/ u8 _C4;
    /*0xC5*/ u8 _C5;
} DKJungleBarrel;

typedef struct _DKJungleCannonEmitter {
    /*0x00*/ u8 _00[8];
    /*0x08*/ u32 _08;
} DKJungleCannonEmitter;

// Cannon object in stadiumObjectCollision.objects; shares its leading layout with DKJungleBarrel.
typedef struct _DKJungleCannon {
    /*0x00*/ u8 ctrlType;
    /*0x01*/ u8 _01[0x7B];
    /*0x7C*/ void (*callback)(struct _DKJungleCannon* cannon);
    /*0x80*/ u8 _80[0x99 - 0x80];
    /*0x99*/ u8 _99;
    /*0x9A*/ u8 _9A[2];
    /*0x9C*/ u8 index;
    /*0x9D*/ u8 _9D[3];
    /*0xA0*/ DKJungleBarrel* barrel;
    /*0xA4*/ DKJungleCannonEmitter* emitter;
    /*0xA8*/ Vec pos;
    /*0xB4*/ Vec vel;
    /*0xC0*/ f32 rotY;
    /*0xC4*/ u8 mode;
    /*0xC5*/ u8 _C5;
} DKJungleCannon;

typedef struct _DKJungleSmokeParticle {
    /*0x00*/ struct _DKJungleSmokeParticle* next;
    /*0x04*/ Vec pos;
    /*0x10*/ Vec vel;
    /*0x1C*/ f32 _1C;
    /*0x20*/ f32 _20;
    /*0x24*/ f32 _24;
    /*0x28*/ f32 _28;
    /*0x2C*/ f32 _2C;
    /*0x30*/ u8 _30[0x38 - 0x30];
    /*0x38*/ f32 _38;
    /*0x3C*/ f32 _3C;
    /*0x40*/ u8 color[3];
    /*0x43*/ u8 alpha;
    /*0x44*/ u8 _44[4];
    /*0x48*/ s16 _48;
    /*0x4A*/ s16 _4A;
    /*0x4C*/ u8 _4C;
    /*0x4D*/ u8 _4D;
    /*0x4E*/ u8 _4E;
    /*0x4F*/ u8 index;
} DKJungleSmokeParticle; // size: 0x50

typedef struct _DKJungleSmokeEmitter {
    /*0x00*/ u8 _00[0x0C];
    /*0x0C*/ DKJungleSmokeParticle* particles;
    /*0x10*/ u32 _10;
} DKJungleSmokeEmitter;

typedef struct _DKJungleZoneCorner {
    /*0x00*/ f32 x;
    /*0x04*/ f32 z;
} DKJungleZoneCorner;

typedef struct _DKJungleBarrelLauncher {
    /*0x00*/ Vec pos;
    /*0x0C*/ f32 rotY;
    /*0x10*/ u8 usedFlag;
    /*0x11*/ u8 _11[3];
} DKJungleBarrelLauncher; // size: 0x14

// View over the .data block at barrelRollSfxEmitterId (klaptrap dust/sound tuning).
typedef struct _DKJungleKlaptrapTuning {
    /*0x000*/ u8 _000[0x154];
    /*0x154*/ s32 dustInterval[3];
    /*0x160*/ f32 dustSize[3];
    /*0x16C*/ u8 _16C[0x174 - 0x16C];
    /*0x174*/ f32 dustHeight;
    /*0x178*/ s32 barrelDustInterval;
    /*0x17C*/ f32 barrelDustHeight;
    /*0x180*/ u8 _180[0x228 - 0x180];
    /*0x228*/ f32 launchZ;
    /*0x22C*/ f32 dustOffset[2][2];
} DKJungleKlaptrapTuning;

typedef struct _DKJungleVertexData {
    /*0x00*/ void* data;
    /*0x04*/ u8 _04[2];
    /*0x06*/ u8 format;
    /*0x07*/ u8 stride;
} DKJungleVertexData;

typedef enum _DKJungleEntryKind {
    DKJUNGLE_ENTRY_SETUP_VTX = 2,
    DKJUNGLE_ENTRY_SETUP_EFFECT = 3,
} DKJungleEntryKind;

typedef struct _DKJungleDrawEntry {
    /*0x00*/ u8 kind;
    /*0x01*/ u8 _01[3];
    /*0x04*/ u32 vtxDescBits;
    /*0x08*/ void* displayList;
    /*0x0C*/ u32 displayListSize;
} DKJungleDrawEntry; // size: 0x10

typedef struct _DKJungleDrawList {
    /*0x00*/ u8 _00[4];
    /*0x04*/ DKJungleDrawEntry* entries;
    /*0x08*/ u16 count;
} DKJungleDrawList;

typedef struct _DKJungleDispObj {
    /*0x00*/ DKJungleVertexData* vertices;
    /*0x04*/ u8 _04[0x0C];
    /*0x10*/ DKJungleDrawList* drawList;
    /*0x14*/ u8 _14[4];
    /*0x18*/ Mtx mtx;
} DKJungleDispObj;

// View over the .bss block starting at lbl_3_bss_AEE0 (the original object spans several split symbols).
typedef struct _DKJungleBss {
    /*0x000*/ u8 _00;
    /*0x001*/ u8 _01;
    /*0x002*/ u8 _02;
    /*0x003*/ u8 _03;
    /*0x004*/ u32 frame;
    /*0x008*/ u8 _08[4];
    /*0x00C*/ f32 launchX;
    /*0x010*/ u8 _10[4];
    /*0x014*/ u32 _14;
    /*0x018*/ int emitters[2];
    /*0x020*/ f32 _20;
    /*0x024*/ f32 _24;
    /*0x028*/ f32 _28;
    /*0x02C*/ Vec target;
    /*0x038*/ u8 _38[0x238 - 0x38];
    /*0x238*/ u8* texBuf;
    /*0x23C*/ f32 indMtx[2][3];
    /*0x254*/ GXTexObj texObj;
    /*0x274*/ u8 _274[0x27C - 0x274];
    /*0x27C*/ u8 _27C;
    /*0x27D*/ u8 _27D[0x339 - 0x27D];
    /*0x339*/ u8 _339;
    /*0x33A*/ u8 _33A;
    /*0x33B*/ u8 objectIndex;
    /*0x33C*/ u8 numObjects;
    /*0x33D*/ u8 objIndex;
    /*0x33E*/ u8 maybeObjectCount;
    /*0x33F*/ u8 gFirstCannonPoolIndex;
    /*0x340*/ u8 nBarrelLaunchers;
    /*0x341*/ u8 _341[0x344 - 0x341];
    /*0x344*/ f32 rate;
    /*0x348*/ f32 basis[7];
    /*0x364*/ u32 factors[7];
    /*0x380*/ Vec points[7];
    /*0x3D4*/ u8 _3D4[0x67C - 0x3D4];
    /*0x67C*/ void* _67C;
    /*0x680*/ u32 _680;
} DKJungleBss;

// View over the .data block at barrelRollSfxEmitterId.
typedef struct _DKJungleWaterState {
    /*0x000*/ u8 _00[0x24D];
    /*0x24D*/ u8 needsRespawn;
    /*0x24E*/ u8 needsReroll;
    /*0x24F*/ u8 _24F;
    /*0x250*/ Vec pos;
    /*0x25C*/ Vec vel;
} DKJungleWaterState;

extern int barrelRollSfxEmitterId;
extern f32 lbl_3_data_1BA70[6];
extern u8 lbl_3_data_1BA5C[];
extern u8 lbl_803C5090[0x20];
extern DKJungleKlaptrapData jungleKlaptrapData[];
extern DKJungleZoneCorner lbl_3_data_1B824[][4];
extern DKJungleBarrelLauncher barrelLauncherDataStruct[];
extern u8 drawStadiumRelated;
s16 rng(int max);
void fn_8003A144(void);
void fn_800BDA24(void* arg);
extern void fn_800BD548(void* actor, int mode, ...);
void fn_800A7D4C(s32 arg0, void* arg1);
void fn_80033620(void* emitter);
void fn_80033CC8(void* particle, int arg);

void fn_3_EDFAC(void);
int fn_3_EE0BC(u32 flags);
void fn_3_EE100(DKJungleDispObj* obj, Mtx view);
void fn_3_EE388(void);
void fn_3_EE67C(DKJungleDispObj* obj, Mtx view);
void fn_3_EE96C(Vec* pos);
void fn_3_EEB94(void);
void fn_3_EECF4(void);
void fn_3_EEE3C(void);
void fn_3_EEF24(void);
void fn_3_EEFA4(void);
void fn_3_EEFD0(void);
void klaptrapHitAnimation(int idx);
void fn_3_EF218(void);
void fn_3_EF21C(DKJungleKlaptrap* obj);
void fn_3_EF3D4(StadiumObject* obj, u8 idx);
void jungleStadiumObjectRelated(DKJungleKlaptrap* obj);
u8 isPosOutsideKlaptrapZone(Vec pos, u8 zone);
BOOL fn_3_EF7B4(Vec pos, u8 zone);
void fn_3_EF800(DKJungleKlaptrap* obj);
void fn_3_EF890(DKJungleKlaptrap* obj);
void dkKlaptrapLaunchedUpdate(DKJungleKlaptrap* obj);
void fn_3_EFB54(DKJungleKlaptrap* obj);
void fn_3_F0184(void);
void dkKlaptrapChaseUpdate(DKJungleKlaptrap* obj);
void dkKlaptrapRoamUpdate(DKJungleKlaptrap* obj);
void klaptrapControl(DKJungleKlaptrap* obj);
void fn_3_F13F8(DKJungleObject* obj);
void klaptrapCTRLSetup(DKJungleKlaptrap* obj);
void maybeGharialCTRLRel(DKJungleKlaptrap* obj);
void fn_3_F1674(void);
void fn_3_F1750(DKJungleBarrel* obj);
void fn_3_F18A4(DKJungleBarrel* obj);
void handleDKJungleBarrel(DKJungleBarrel* barrel);
void dkBarrelSpawnGroundDust(DKJungleBarrel* barrel);
void fn_3_F22FC(DKJungleBarrel* barrel, s8 fielderIdx);
s8 dkBarrel_collisionWithFielder(DKJungleBarrel* barrel);
void fn_3_F2724(DKJungleBarrel* barrel, DKJungleKlaptrap* klaptrap);
void dkBarrelAdvanceMotion(DKJungleBarrel* barrel);
void fn_3_F2FFC(DKJungleBarrel* barrel, f32 x, f32 z);
void dkBarrelLaunch(DKJungleBarrel* barrel, f32 x, f32 z);
u32 fn_3_F37BC(u32 n, u32 k);
void fn_3_F38D4(void);
void fn_3_F3A04(DKJungleObject* obj);
void fn_3_F3A5C(DKJungleBarrel* obj, f32 x, f32 y, f32 z, f32 angle);
void fn_3_F3AE0(DKJungleBarrel* obj);
void fn_3_F3BB0(DKJungleBarrel* obj);
BOOL dkBarrelSmokeUpdate(DKJungleSmokeEmitter* emitter);
void fn_3_F3EFC(DKJungleSmokeEmitter* emitter);
void fn_3_F42A0(void);
void fn_3_F466C(void);
void fn_3_F469C(void);
void dkJungleBarrelCannonCutsceneUpdate(DKJungleCannon* cannon);
void fn_3_F4BA0(DKJungleCannon* cannon);
void fn_3_F4C4C(DKJungleCannon* cannon);
void fn_3_F4D00(DKJungleCannon* cannon);
void fn_3_F4DAC(void);
void handleBarrelFiring(DKJungleCannon* cannon);
void dkJungleBarrelCannonUpdate(DKJungleCannon* cannon);
void fn_3_F5C30(DKJungleCannon* cannon);
int fn_3_F5E78(u8 id);
int fn_3_F5EFC(const u32* a, const u32* b);
int fn_3_F5F28(const f32* a, const f32* b);
void fn_3_F5F4C(Mtx view);
struct _StadiumDrawOrder;
void processJungleObjectCollisions(Mtx view, struct _StadiumDrawOrder* order);
TriangleGroup* fn_3_F6504(int offset, Mtx m);
void fn_3_F65C8(s32* idx);
void updateDKJungleObjBoundingBoxes(s32* idx);
void maybeBarrelCTRLRel(s32* count);
void fn_3_F6A94(s32* idx);
void updateDKJungleControl(void);
void fn_3_F6FCC(void);
void loadDKJungle(void** files);

#endif // !__GAME_STADIUM_STA_C5_H_
