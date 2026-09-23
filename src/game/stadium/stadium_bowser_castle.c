#define SQRT2_LINKAGE static
#include "game/stadium/stadium_bowser_castle.h"
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
#include "Unknown/File_0x800bf038.h"
#include "Unknown/File_0x8001b728.h"
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
#include "Unknown/File_0x80023b90.h"
#include "Unknown/File_0x800beb3c.h"
#include "game/stadium/sta_c2.h"
#include "Unknown/File_0x80024404.h"

typedef struct _CastleMaterialFlags {
    /*0x00*/ u8 _00[4];
    /*0x04*/ u32 animState;
    /*0x08*/ u8 _08[0x74 - 0x08];
    /*0x74*/ u32 flags;
} CastleMaterialFlags;

typedef struct _CastleModelLevel4 {
    /*0x00*/ u8 _00[4];
    /*0x04*/ CastleMaterialFlags* next;
} CastleModelLevel4;

typedef struct _CastleModelLevel3 {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ CastleModelLevel4* next;
} CastleModelLevel3;

typedef struct _CastleModelLevel2 {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ CastleModelLevel3* next;
} CastleModelLevel2;

typedef struct _CastleModelLevel1 {
    /*0x00*/ u8 _00[4];
    /*0x04*/ CastleModelLevel2* flameMat;
    /*0x08*/ u8 _08[0x34 - 0x08];
    /*0x34*/ CastleModelLevel2* thwompMat;
} CastleModelLevel1;

typedef struct _CastleModelRoot {
    /*0x00*/ u8 _00[0x18];
    /*0x18*/ CastleModelLevel1* next;
} CastleModelRoot;

typedef struct _CastleHazardObj {
    /*0x00*/ u8 _00[0xA8];
    /*0xA8*/ u8 _A8;
    /*0xA9*/ u8 hazardType;
    /*0xAA*/ u8 _AA[0xB0 - 0xAA];
    /*0xB0*/ u8 hasBounced;
    /*0xB1*/ u8 _B1[0xBD - 0xB1];
    /*0xBD*/ u8 _BD;
} CastleHazardObj;

// A DrawingSceneStruct-owned per-frame render scratch entry: the node's
// firstHandle field (+0x14) indexes into graphicsRelatedArray to fetch the
// CastleGfxObject to update.
typedef struct _CastleGfxScene {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ u16 firstHandle;
} CastleGfxScene;

typedef struct _CastleGfxObject {
    /*0x00*/ u8 _00[0x48];
    /*0x48*/ Vec pos;
    /*0x54*/ u32 flags;
    /*0x58*/ u8 _58[0x5C - 0x58];
    /*0x5C*/ u32 frameIndex;
    /*0x60*/ u8 _60[0x69 - 0x60];
    /*0x69*/ u8 scale;
} CastleGfxObject;

// Same 0x5C act-effect record stadium_wario_palace.c calls PalaceActEffect.
typedef struct _CastleActEffect {
    /*0x00*/ u32 file;
    /*0x04*/ u8 _04[0x5C - 0x04];
} CastleActEffect; // size: 0x5C

typedef struct _CastleGfxSceneHolder {
    /*0x00*/ CastleGfxScene* scene;
    /*0x04*/ CastleActEffect effects[2];
} CastleGfxSceneHolder;

// Per-camera-slot scratch entry (2 of these; index by drawStadiumRelated).
typedef struct _CastleCameraSlot {
    /*0x00*/ u32 _00;
    /*0x04*/ void (*draw)(struct _CastleCameraSlot* slot);
    /*0x08*/ Mtx mtx;
    /*0x38*/ DrawingSceneStruct* item;
} CastleCameraSlot; // size 0x3C

typedef struct _CastleMaterialEntry {
    /*0x00*/ u8 kind;
    /*0x01*/ u8 _01[3];
    /*0x04*/ u32 animState;
    /*0x08*/ u8 _08[0x10 - 0x08];
} CastleMaterialEntry; // size 0x10

typedef struct _CastleMaterialList {
    /*0x00*/ u8 _00[4];
    /*0x04*/ CastleMaterialEntry* entries;
    /*0x08*/ u16 count;
} CastleMaterialList;

typedef struct _CastleMaterialListHolder {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ CastleMaterialList* list;
} CastleMaterialListHolder;

typedef struct _CastleMaterialGroupNode {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ CastleMaterialListHolder* holder;
} CastleMaterialGroupNode;

typedef struct _CastleMaterialRoot {
    /*0x00*/ u8 _00[6];
    /*0x06*/ u16 groupCount;
    /*0x08*/ u8 _08[0x18 - 0x08];
    /*0x18*/ CastleMaterialGroupNode** groups;
} CastleMaterialRoot;

typedef struct _CastleFireballTarget {
    /*0x00*/ u8 _00[0x9C];
    /*0x9C*/ Vec anchorPos;
} CastleFireballTarget;

// Per-node scratch view of DrawingSceneStruct's shared scratch region (see
// CastleGfxScene/CastleCameraSlot for other nodes' own views of the same
// region); this node stores a 6-entry emitter-handle array starting at 0x14.
typedef struct _CastleFireEmitterScene {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ struct _CastleFlameEmitter* handles[6];
} CastleFireEmitterScene;

typedef struct _CastleFlameParticle {
    /*0x00*/ struct _CastleFlameParticle* next;
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
    /*0x40*/ u8 _40;
    /*0x41*/ u8 _41;
    /*0x42*/ u8 _42;
    /*0x43*/ u8 alphaByte;
    /*0x44*/ u8 _44[0x48 - 0x44];
    /*0x48*/ s16 _48;
    /*0x4A*/ s16 _4A;
    /*0x4C*/ u8 _4C;
    /*0x4D*/ u8 _4D;
    /*0x4E*/ u8 _4E;
    /*0x4F*/ u8 _4F;
    /*0x50*/ u8 _50;
} CastleFlameParticle;

typedef struct _CastleFlameEmitter {
    /*0x00*/ u8 _00[0x08];
    /*0x08*/ u32 _08;
    /*0x0C*/ CastleFlameParticle* particles;
    /*0x10*/ u32 _10;
    /*0x14*/ u8 _14[0x18 - 0x14];
    /*0x18*/ Vec origin;
    /*0x24*/ u8 kind;
} CastleFlameEmitter;

// A different emitter shape than CastleFlameEmitter -- `_18` is a pointer
// to an external anchor point here, not an embedded Vec.
typedef struct _CastleSmokeEmitter {
    /*0x00*/ u8 _00[0xC];
    /*0x0C*/ CastleFlameParticle* particles;
    /*0x10*/ u32 _10;
    /*0x14*/ u8 _14[0x18 - 0x14];
    /*0x18*/ Vec* target;
    /*0x1C*/ u8 _1C[0x24 - 0x1C];
    /*0x24*/ s32 _24;
} CastleSmokeEmitter;

extern void fn_800A7D4C(s32 arg0, void* arg1);
extern u8 drawStadiumRelated;
extern void fn_800528C0(f32 x, f32 y, f32 z, s16* outX, s16* outY);
extern void fn_800BDF70(StadiumModel* model);
extern u16 stadiumHazardSoundIDs[16];
extern u8 stadiumHazardSoundFxRelated[0xB4];
extern u8 lbl_3_data_84B8[0x3C];

// Same DOL global other stadium files see as `extern u8 hugeAnimStruct[0x3154]`
// (raw byte view; the struct's real layout is only partly known -- see
// stadium_framework.c's own richer partial-struct view of the same symbol).
extern u8 hugeAnimStruct[0x3154];
// stadium_framework.c's own partial view of the same 14-row light-input
// table and 4-entry light-input array used by characterLightingRelated.
extern u8 inputParams[14][0x2C];
typedef struct _StadiumLightInput {
    Vec pos;
    GXColor color;
} StadiumLightInput;
extern StadiumLightInput lbl_80367318[4];

// The pointer hugeAnimStruct+0x4 refers to; `_14` is a self-relative byte
// offset (added to the object's own address) rather than a pointer.
typedef struct _CastleAnimSubStruct {
    u8 _00[0x14];
    u32 _14;
} CastleAnimSubStruct;


typedef struct _CastleLightParticleParams {
    /*0x00*/ f32 _00;
    /*0x04*/ u8 _04[0x14 - 0x04];
    /*0x14*/ s16 _14;
    /*0x16*/ u8 _16;
    /*0x17*/ u8 _17;
    /*0x18*/ u8 _18;
    /*0x19*/ u8 _19;
    /*0x1A*/ u8 _1A[0x1D - 0x1A];
    /*0x1D*/ u8 _1D;
    /*0x1E*/ u8 _1E[0x20 - 0x1E];
} CastleLightParticleParams; // size 0x20

extern CastleLightParticleParams lbl_803C5090;

// Same DOL global stadium_framework.c declares as
// `extern struct { u8 _00[0x28]; u8 _28; } lbl_80366158;` -- only field
// `_28` has a known use so far, matching that file's own partial view.
extern struct {
    u8 _00[0x28];
    u8 _28;
} lbl_80366158;

typedef struct _CastleSparkParticle {
    /*0x00*/ struct _CastleSparkParticle* next;
    /*0x04*/ Vec pos;
    /*0x10*/ Vec vel;
    /*0x1C*/ f32 scale;
    /*0x20*/ f32 _20;
    /*0x24*/ f32 alpha;
    /*0x28*/ u8 _28[0x38 - 0x28];
    /*0x38*/ f32 _38;
    /*0x3C*/ f32 _3C;
    /*0x40*/ u8 _40;
    /*0x41*/ u8 _41;
    /*0x42*/ u8 _42;
    /*0x43*/ u8 _43;
    /*0x44*/ u8 _44[0x48 - 0x44];
    /*0x48*/ s16 _48;
    /*0x4A*/ s16 _4A;
    /*0x4C*/ u8 _4C[0x4F - 0x4C];
    /*0x4F*/ u8 _4F;
} CastleSparkParticle; // size 0x50

typedef struct _CastleFireballEmitter {
    /*0x00*/ u8 _00[0xC];
    /*0x0C*/ CastleFlameParticle* particles;
    /*0x10*/ u32 _10;
    /*0x14*/ u8 _14[0x18 - 0x14];
    /*0x18*/ Vec* targetPos;
    /*0x1C*/ u8 _1C[0x20 - 0x1C];
    /*0x20*/ StadiumObject* target;
    /*0x24*/ u32 _24;
} CastleFireballEmitter;

typedef struct _CastleSparkEmitter {
    /*0x00*/ u8 _00[0xC];
    /*0x0C*/ CastleSparkParticle* particles;
    /*0x10*/ u32 _10;
    /*0x14*/ u16 _14;
    /*0x16*/ u8 _16[0x24 - 0x16];
    /*0x24*/ s32 _24;
} CastleSparkEmitter;

typedef struct _CastleSlotPlacement {
    f32 x;
    f32 y;
    f32 z;
    f32 rotation;
    u8 usedFlag;
    u8 visible;
    u8 group;
    u8 _13;
} CastleSlotPlacement; // size 0x14

typedef struct _CastleObjControl {
    Control ctrl;
    u8 _3C[0x44 - sizeof(Control)];
} CastleObjControl;

extern void fn_80035750(void* a, void* b, int c);
extern UIRecordDescriptor lbl_3_data_10C1C[];

typedef enum _THWOMP_STATE {
    THWOMP_PERCHED,
    THWOMP_WINDUP,
    THWOMP_FALLING,
    THWOMP_GROUNDED,
    THWOMP_RETURNING,
} THWOMP_STATE;

// Thwomp view of a stadiumObjectCollision.objects[] entry (the region past
// 0x98 is laid out per hazard kind; compare CastleHazardObj).
typedef struct _CastleThwompObj {
    /*0x00*/ u8 _00[0x99];
    /*0x99*/ E(u8, BOOL) resetPending;
    /*0x9A*/ u8 _9A[0x9C - 0x9A];
    /*0x9C*/ Vec pos;
    /*0xA8*/ u8 index;
    /*0xA9*/ u8 _A9[0xAC - 0xA9];
    /*0xAC*/ f32 fallSpeed;
    /*0xB0*/ E(u8, THWOMP_STATE) state;
    /*0xB1*/ u8 framesOnGround;
    /*0xB2*/ E(u8, BOOL) checkForSlam;
} CastleThwompObj;

typedef struct _CastleFireSpawner {
    /*0x00*/ f32 x;
    /*0x04*/ f32 y;
    /*0x08*/ f32 z;
    /*0x0C*/ f32 rotation;
    /*0x10*/ u8 usedFlag;
    /*0x11*/ u8 visible;
    /*0x12*/ u8 group;
    /*0x13*/ u8 _13;
    /*0x14*/ u16 launchAngleBase;
    /*0x16*/ u16 launchAngleSpread;
} CastleFireSpawner; // size 0x18

typedef enum _FLAME_STATE {
    FLAME_IDLE,
    FLAME_FLYING,
    FLAME_EXPLODING,
    FLAME_ENDED,
} FLAME_STATE;

// Fireball view of a stadiumObjectCollision.objects[] entry (compare
// CastleThwompObj/CastleHazardObj).
typedef struct _CastleFireObj {
    /*0x00*/ u8 _00[0x90];
    /*0x90*/ u8 visible : 1;
    /*0x90*/ u8 _90b1 : 7;
    /*0x91*/ u8 _91[0x99 - 0x91];
    /*0x99*/ E(u8, BOOL) resetPending;
    /*0x9A*/ u8 _9A[0x9C - 0x9A];
    /*0x9C*/ Vec pos;
    /*0xA8*/ u8 id;
    /*0xA9*/ u8 _A9[0xAC - 0xA9];
    /*0xAC*/ Vec velo;
    /*0xB8*/ u16 launchAngleBase;
    /*0xBA*/ u16 launchAngleSpread;
    /*0xBC*/ u8 launchTimer;
    /*0xBD*/ E(u8, FLAME_STATE) state;
} CastleFireObj;

// Entries 6..8 of the actor-pointer table at hugeAnimStruct+0x2C50; only the
// position is read here.
typedef struct _CastleAnimActor {
    /*0x00*/ u8 _00[0x34];
    /*0x34*/ Vec pos;
} CastleAnimActor;


typedef struct _CastleSparkTableEntry {
    /*0x00*/ s16 x;
    /*0x02*/ s16 y;
    /*0x04*/ s16 z;
} CastleSparkTableEntry;

typedef struct _CastlePadTable {
    /*0x00*/ CastleSlotPlacement entries[11];
    /*0xDC*/ u8 objectTypes[16];
} CastlePadTable; // size 0xEC

static f32 thompFallingSpeedConstants[3] = { 1.0f, 3.0f, 5.0f };

static CastleSlotPlacement thwompStaticValues[11] = {
    { -51.592f, -18.0f, 68.051f, 306.0f, 2, 1, 1, 2 },
    { -43.569f, -18.0f, 76.869f, 314.0f, 2, 1, 1, 2 },
    { -33.845f, -18.0f, 84.008f, 330.0f, 2, 1, 1, 2 },
    { 51.592f, -18.0f, 68.051f, 52.0f, 2, 1, 2, 2 },
    { 43.569f, -18.0f, 76.869f, 44.0f, 2, 1, 2, 2 },
    { 33.845f, -18.0f, 84.008f, 28.0f, 2, 1, 2, 2 },
    { 0.0f, 0.0f, 0.0f, 0.0f, 7, 0, 0xFF, 7 },
    { 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0 },
    { 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0 },
    { 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0 },
    { 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0 },
};

static f32 flameXVelos[3] = { 0.06f, 0.07f, 0.08f };

static CastleFireSpawner BowserStadFireSpawners[11] = {
    { -48.0f, 5.5f, 25.0f, 0.0f, 3, 1, 1, 3, 295, 1 },
    { -43.0f, 5.5f, 56.0f, 0.0f, 3, 1, 1, 3, 315, 90 },
    { -10.0f, 5.5f, 77.0f, 0.0f, 3, 1, 2, 3, 180, 90 },
    { 10.0f, 5.5f, 77.0f, 0.0f, 3, 1, 2, 3, 270, 90 },
    { 45.0f, 5.5f, 23.0f, 0.0f, 3, 1, 3, 3, 245, 1 },
    { 43.0f, 5.5f, 56.0f, 0.0f, 3, 1, 3, 3, 135, 90 },
    { 0.0f, 0.0f, 0.0f, 0.0f, 7, 0, 0xFF, 7, 0, 0 },
    { 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0 },
    { 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0 },
    { 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0 },
    { 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0 },
};

static CastlePadTable lbl_3_data_17704 = {
    {
        { -12.891f, -5.93f, 87.961f, 348.0f, 4, 1, 1, 6 },
        { 12.891f, -5.93f, 87.961f, 12.0f, 4, 1, 1, 6 },
        { -23.0f, -0.02f, 72.0f, 0.0f, 5, 1, 2, 6 },
        { -22.0f, -0.02f, 45.0f, 0.0f, 5, 1, 2, 6 },
        { -50.0f, -0.02f, 38.0f, 0.0f, 5, 1, 2, 6 },
        { 23.0f, -0.02f, 72.0f, 0.0f, 5, 1, 3, 6 },
        { 22.0f, -0.02f, 45.0f, 0.0f, 5, 1, 3, 6 },
        { 50.0f, -0.02f, 38.0f, 0.0f, 5, 1, 3, 6 },
        { 0.0f, 0.0f, 0.0f, 0.0f, 7, 0, 0xFF, 7 },
        { 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0 },
        { 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0 },
    },
    { 1, 2, 2, 2, 2, 2, 2, 6, 6, 6, 8, 9, 8, 9, 0, 0 },
};

static u16 lbl_3_data_177F0 = 4;
static u32 lbl_3_data_177F4 = 2;
static u8 lbl_3_data_177F8[0xC] = { 0, 0xC8, 5, 0x92, 8, 0x68, 0xFF, 0xFF, 0xFF, 0, 0, 0 };

static CastleCameraSlot lbl_3_data_17804[2] = {
    { 0, fn_3_C1C18 },
    { 0, fn_3_C1C18 },
};

static f32 lbl_3_data_1787C = 0.7f;
static CastleSparkTableEntry lbl_3_data_17880[4] = {
    { 106, -98, 220 },
    { 94, -87, 230 },
    { 120, -80, 212 },
    { 0, 0, 0 },
};

// Per-node scratch view of DrawingSceneStruct's shared scratch region (see
// CastleGfxScene/CastleCameraSlot for other nodes' own views of the same
// region); this node's fields set up a spark-effect placement, consumed by
// fn_3_C2244's per-frame callback (which only reads `_2A` so far).
typedef struct _CastleSparkScene {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ Vec pos;
    /*0x20*/ s16 spread[2];
    /*0x24*/ s8 baseSpread;
    /*0x25*/ s8 spreadA[2];
    /*0x27*/ u8 spreadB[2];
    /*0x29*/ u8 _29;
    /*0x2A*/ u8 _2A;
} CastleSparkScene;

static u32 lbl_3_bss_9F0C[5];
static CastleGfxSceneHolder lbl_3_bss_9E50;
static u8 lbl_3_bss_9E48[8];
static Vec lbl_3_bss_9DE8[8];
static u8 lbl_3_bss_9DE7;
static u8 lbl_3_bss_9DE6;
static u8 lbl_3_bss_9DE5;
static u8 lbl_3_bss_9DE4;
static u8 lbl_3_bss_9DE3;
static u8 lbl_3_bss_9DE2;
static u8 lbl_3_bss_9DE1;
static u8 lbl_3_bss_9DE0;
static u8 lbl_3_bss_9DA0[0x40];
static s32 lbl_3_bss_9D9C;
static u32 lbl_3_bss_9D98;
static s32 lbl_3_bss_9D94;
static u32 lbl_3_bss_9D90;
static u32 thwompScreenShakeTimeRemaining;
static u32 lbl_3_bss_9D88;
static u32 lbl_3_bss_9D84;
static u8 lbl_3_bss_9D83;
static u8 lbl_3_bss_9D82;
static u8 startScreenShake;
static u8 lbl_3_bss_9D80;

static const u8 lbl_3_rodata_2028[3] = { 0xA0, 0x46, 0x00 };
static const f32 const_pi_or_180 = 0.017453292f;
static const f32 thwompConstants = 12.0f;
static const Vec lbl_3_rodata_202C[6] = {
    { -19.3f, -14.5f, 86.0f },
    { 19.3f, -14.5f, 86.0f },
    { -15.92f, -18.8f, 112.16f },
    { 15.92f, -18.8f, 112.16f },
    { -36.5f, -17.9f, -22.8f },
    { 36.5f, -17.9f, -22.8f },
};

// .text:0x000C1964 size:0x10 mapped:0x807009F8
void fn_3_C1964(void) {
    lbl_3_bss_9D9C = 1;
}

// .text:0x000C1974 size:0x54 mapped:0x80700A08
void fn_3_C1974(int offset) {
    DrawingSceneStruct* item = insertGraphicDrawingFunction(fn_3_C2644, 4);
    item->state = 0;
    lbl_3_bss_9D98 = offset + 0x3C4;
    lbl_3_bss_9D9C = 0;
}

// .text:0x000C19C8 size:0x250 mapped:0x80700A5C
void fn_3_C19C8(void) {
    int i;

    if (lbl_3_bss_9D90 == 0) {
        lbl_3_bss_9D90 = (u32)insertGraphicDrawingFunction(fn_3_C2244, 5);
    }
    if (currentDrawingItem->state != 0x136) {
        randomizeAndLoadSoundEffect(stadiumHazardSoundIDs[g_d_GameSettings.StadiumID] + 6, 8);
    }
    ((CastleSparkScene*)lbl_3_bss_9D90)->_2A = 0xFF;
    ((CastleSparkScene*)lbl_3_bss_9D90)->_29 = 2;

    i = rand() % 3;
    ((CastleSparkScene*)lbl_3_bss_9D90)->pos.x = (f32)lbl_3_data_17880[i].x;
    ((CastleSparkScene*)lbl_3_bss_9D90)->pos.y = (f32)lbl_3_data_17880[i].y;
    ((CastleSparkScene*)lbl_3_bss_9D90)->pos.z = (f32)lbl_3_data_17880[i].z;

    ((CastleSparkScene*)lbl_3_bss_9D90)->baseSpread = 10 - (rand() % 20);

    i = 2;
    while (i-- != 0) {
        s32 range = ((0x1FFF - (rand() * 0x3FFF) / 0x7FFF) >> (1 - i)) + 0x1FFF;
        ((CastleSparkScene*)lbl_3_bss_9D90)->spread[i] = (s16)((rand() * range) / 0x7FFF);
        ((CastleSparkScene*)lbl_3_bss_9D90)->spreadA[i] =
            ((CastleSparkScene*)lbl_3_bss_9D90)->baseSpread + 2 - (rand() % 2);
        ((CastleSparkScene*)lbl_3_bss_9D90)->spreadB[i] = (rand() % 2) + 1;
    }
}

// .text:0x000C1C18 size:0x62C mapped:0x80700CAC
void fn_3_C1C18(CastleCameraSlot* slot) {
    Mtx ident = {
        { 1.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f, 0.0f },
    };
    Vec pos;
    CastleSparkScene* scene;
    u32 color;
    f32 scale;
    f32 halfWidth;
    f32 height;
    f32 dx;
    f32 dy;
    int alpha;
    int i;

    scene = (CastleSparkScene*)slot->item;
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXLoadPosMtxImm(ident, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    for (i = 0; i <= 2; i++) {
        SetDisplayStateTexture((void*)(lbl_3_bss_9D98 + i * 0x20), i, i);
    }

    color = (s32)(scene->_2A * lbl_3_data_1787C) | 0xFFFFFF00;
    PSMTXMultVec(slot->mtx, &scene->pos, &pos);
    scale = (100.0f + scene->baseSpread) / 100.0f;
    halfWidth = 512.0f * scale * -pos.z / 1280.0f * 0.5f;
    height = 256.0f * scale * -pos.z / 1280.0f;
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(pos.x - halfWidth, pos.y - 0.25f * height, pos.z);
    GXColor1u32(color);
    GXTexCoord2u16(0, 0);
    GXPosition3f32(pos.x - halfWidth, pos.y + 0.75f * height, pos.z);
    GXColor1u32(color);
    GXTexCoord2u16(0, 1);
    GXPosition3f32(pos.x + halfWidth, pos.y + 0.75f * height, pos.z);
    GXColor1u32(color);
    GXTexCoord2u16(1, 1);
    GXPosition3f32(pos.x + halfWidth, pos.y - 0.25f * height, pos.z);
    GXColor1u32(color);
    GXTexCoord2u16(1, 0);

    height = 256.0f * -pos.z / 1280.0f;
    color = scene->_2A | 0xFFFFFF00;
    for (i = scene->_29; i < 2; i++) {
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, scene->spreadB[i], GX_COLOR0A0);
        SetDisplayStateTexture((void*)(lbl_3_bss_9D98 + scene->spreadB[i] * 0x20), 0, 0);
        dy = (100.0f + scene->spreadA[i]) / 100.0f * height * cos(0.0000958738f * scene->spread[i]);
        dx = (100.0f + scene->spreadA[i]) / 100.0f * height * sin(0.0000958738f * scene->spread[i]);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(pos.x, pos.y, pos.z);
        GXColor1u32(color);
        GXTexCoord2u16(0, 0);
        GXPosition3f32(pos.x - dx, pos.y + dy, pos.z);
        GXColor1u32(color);
        GXTexCoord2u16(0, 1);
        GXPosition3f32(pos.x + dy - dx, dx + (pos.y + dy), pos.z);
        GXColor1u32(color);
        GXTexCoord2u16(1, 1);
        GXPosition3f32(pos.x + dy, pos.y + dx, pos.z);
        GXColor1u32(color);
        GXTexCoord2u16(1, 0);
        pos.x = 0.5f * (dy - dx) + pos.x;
        pos.y = 0.5f * (dy + dx) + pos.y;
    }

    scene->_29 -= (scene->_29 != 0);
    alpha = scene->_2A - (scene->_29 == 0) * 42;
    scene->_2A = alpha * (alpha > 0);
}

// .text:0x000C2244 size:0xCC mapped:0x807012D8
void fn_3_C2244(void) {
    DrawingSceneStruct* item = currentDrawingItem;

    if (lbl_3_bss_9D9C != 0) {
        lbl_3_bss_9D90 = 0;
        removeCurrentDrawingItem();
        return;
    }
    if (*((u8*)item + 0x2A) != 0) {
        fn_800A7D4C(1, &lbl_3_data_17804[drawStadiumRelated]);
        PSMTXCopy(fn_80052768_getCamera(0)->view, lbl_3_data_17804[drawStadiumRelated].mtx);
        lbl_3_data_17804[drawStadiumRelated].item = item;
    }
}

// .text:0x000C2310 size:0xD0 mapped:0x807013A4
void fn_3_C2310(StadiumModel* model, Mtx m) {
    Mtx world;
    Mtx local;
    StadiumModelNode* root;
    StadiumModelNode* child;

    CTRLBuildMatrix((Control*)lbl_3_bss_9D94, local);
    PSMTXConcat(m, local, world);
    root = model->root;
    child = root->firstChild;
    if (root->dispObj != NULL) {
        if (root->skinData != NULL) {
            fn_8003A8A0(root->dispObj, world, 1);
        } else {
            DOVARenderSkin(root->dispObj, world, root->skinMtxArray, root->skinInvTransposeMtxArray, 0,
                           NULL);
        }
    }
    for (; child != NULL; child = child->nextSibling) {
        if (child->dispObj != NULL) {
            DOSetWorldMatrix(child->dispObj, child->worldMtx);
            fn_8003A8A0(child->dispObj, world, 0);
        }
    }
}

// .text:0x000C23E0 size:0xC0 mapped:0x80701474
void fn_3_C23E0(void) {
    StadiumObject* obj;
    s32 i;

    fn_800BF058(fn_3_B8184);
    for (i = 0; i < stadiumObjectCollision.objectCount; i++) {
        obj = &stadiumObjectCollision.objects[i];

        fn_3_B828C((s32)obj);
        if (i >= 1 && i < 0xB) {
            if (obj->hasShadow && obj->model != NULL) {
                obj->model->root->drawFlags = obj->nodeDrawFlags | 6;
                fn_800BDF70(obj->model);
            }
        }
    }
}

// .text:0x000C24A0 size:0x1A4 mapped:0x80701534
void fn_3_C24A0(void) {
    CastleAnimSubStruct* h;
    u8 brightness;
    Vec dir;

    currentDrawingItem->state--;
    if (currentDrawingItem->state == 0) {
        removeCurrentDrawingItem();
        characterLightingRelated(&inputParams[g_d_GameSettings._54], lbl_80367318);
        h = *(CastleAnimSubStruct**)(hugeAnimStruct + 4);
        if (h != NULL) {
            *(u16*)((u8*)h + h->_14 + 0x60) = 2;
        }
    } else {
        if (currentDrawingItem->state < 0xC) {
            brightness = currentDrawingItem->state * 0x80 / 0xC;
        } else {
            brightness = 0x80;
        }
        characterLightingRelated(lbl_3_data_177F8, lbl_80367318);
        h = *(CastleAnimSubStruct**)(hugeAnimStruct + 4);
        if (h != NULL) {
            *(u16*)((u8*)h + h->_14 + 0x60) = 3;
        }
        lbl_803C5090._1D = 0xB;
        lbl_803C5090._00 = 1.0f;
        lbl_803C5090._14 = 0x1C0;
        lbl_803C5090._17 = brightness;
        lbl_803C5090._19 = (u8)lbl_3_data_177F4;
        lbl_803C5090._18 = 1;
    }
    dir.x = -lbl_80367318[0].pos.x;
    dir.y = -lbl_80367318[0].pos.y;
    dir.z = -lbl_80367318[0].pos.z;
    PSVECNormalize(&dir, &dir);
    updateVectorInArray(0, dir);
}

// .text:0x000C2644 size:0x330 mapped:0x807016D8
void fn_3_C2644(void) {
    int i;
    s32 range;

    if (!g_d_GameSettings.minigamesEnabled || g_GameLogic.gameStatus < GAME_STATUS_0x1B ||
        g_GameLogic.gameStatus > 0x29) {
        if (g_GameLogic.gameStatus == GAME_STATUS_CHAMPIONSHIP) {
            lbl_3_bss_9D9C = 1;
        }
        if (lbl_3_bss_9D9C != 0) {
            removeCurrentDrawingItem();
        } else {
            DrawingSceneStruct* item = currentDrawingItem;
            s16 state = (item->state + 1) % 0x708;

            item->state = state;
            switch (state) {
            case 300:
            case 0x136:
            case 0x4B0:
                break;
            default:
                return;
            }
            item = insertGraphicDrawingFunction(fn_3_C24A0, 5);
            item->state = 0x10;
            if (lbl_3_bss_9D90 == 0) {
                lbl_3_bss_9D90 = (u32)insertGraphicDrawingFunction(fn_3_C2244, 5);
            }
            if (currentDrawingItem->state != 0x136) {
                randomizeAndLoadSoundEffect(stadiumHazardSoundIDs[g_d_GameSettings.StadiumID] + 6, 8);
            }
            ((CastleSparkScene*)lbl_3_bss_9D90)->_2A = 0xFF;
            ((CastleSparkScene*)lbl_3_bss_9D90)->_29 = 2;

            i = rand() % 3;
            ((CastleSparkScene*)lbl_3_bss_9D90)->pos.x = (f32)lbl_3_data_17880[i].x;
            ((CastleSparkScene*)lbl_3_bss_9D90)->pos.y = (f32)lbl_3_data_17880[i].y;
            ((CastleSparkScene*)lbl_3_bss_9D90)->pos.z = (f32)lbl_3_data_17880[i].z;

            ((CastleSparkScene*)lbl_3_bss_9D90)->baseSpread = 10 - (rand() % 20);

            i = 2;
            while (i-- != 0) {
                range = ((0x1FFF - (rand() * 0x3FFF) / 0x7FFF) >> (1 - i)) + 0x1FFF;
                ((CastleSparkScene*)lbl_3_bss_9D90)->spread[i] = (s16)((rand() * range) / 0x7FFF);
                ((CastleSparkScene*)lbl_3_bss_9D90)->spreadA[i] =
                    ((CastleSparkScene*)lbl_3_bss_9D90)->baseSpread + 2 - (rand() % 2);
                ((CastleSparkScene*)lbl_3_bss_9D90)->spreadB[i] = (rand() % 2) + 1;
            }
        }
    }
}

// .text:0x000C2974 size:0x18 mapped:0x80701A08
void fn_3_C2974(void) {
    lbl_3_bss_9DE7 = 1;
    lbl_3_bss_9D82 = 1;
}

// .text:0x000C298C size:0x114 mapped:0x80701A20
void fn_3_C298C(void) {
    CastleFireEmitterScene* scene = (CastleFireEmitterScene*)currentDrawingItem;
    u32 i;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        if (g_GameLogic.gameStatus == GAME_STATUS_PAUSED || g_GameLogic.gameStatus >= GAME_STATUS_MINIGAME_POST_MENU) {
            if (g_Minigame._1A40 != 0 && g_Minigame._1A38 == 0) {
                removeCurrentDrawingItem();
            }
        }
    } else {
        if (g_GameLogic.exitingToMenu != 0 || *((u8*)&g_d_GameSettings + 0x13) != 0) {
            removeCurrentDrawingItem();
        }
    }
    for (i = 0; i < 6; i++) {
        CastleFlameEmitter* handle = scene->handles[i];

        if (handle == NULL || handle->_08 == 0) {
            scene->handles[i] = allocParticleEffect(fn_3_C30F0, 0x80, 0, 0x15, TRUE, 0);
            if (scene->handles[i] != NULL) {
                fn_3_C366C(scene->handles[i], i);
            }
        }
    }
}

// .text:0x000C2AA0 size:0x1E0 mapped:0x80701B34
E(u8, BOOL) fn_3_C2AA0(Vec* p, f32 w, f32 h) {
    camera_803c639c_s* cam;
    Vec corners[4];
    Vec clip;
    Vec* src;
    u8 combined;
    u8 code;
    u32 i;
    f32 left;
    f32 right;
    f32 top;
    f32 bottom;
    f32 z;
    f32 halfW;
    f32 halfH;

    combined = 0;
    cam = returnFloatFromModeIndex(returnsCurrentMode());
    PSMTXMultVec(cam->view, p, p);
    z = p->z;
    if (z > -1.0f || z < -512.0f) {
        return FALSE;
    }
    halfH = h * 0.5f;
    halfW = w * 0.5f;
    left = p->x - halfW;
    top = p->y - halfH;
    right = p->x + halfW;
    bottom = p->y + halfH;
    corners[0].x = left;
    corners[0].y = top;
    corners[0].z = z;
    corners[1].x = right;
    corners[1].y = top;
    corners[1].z = z;
    corners[2].x = right;
    corners[2].y = bottom;
    corners[2].z = z;
    corners[3].x = left;
    corners[3].y = bottom;
    corners[3].z = z;
    src = corners;
    for (i = 0; i < 4; i++, src++) {
        PSMTX44MultVec(cam->proj, src, &clip);
        code = (clip.x < -1.0f);
        code |= (clip.x > 1.0f) << 1;
        code |= (clip.y < -1.0f) << 2;
        code |= (clip.y > 1.0f) << 3;
        if (code == 0) {
            return TRUE;
        }
        combined &= code;
    }
    if ((u32)(combined & 3) == 1 || (u32)(combined & 3) == 2) {
        return FALSE;
    }
    if ((u32)(combined & 0xC) == 4 || (u32)(combined & 0xC) == 8) {
        return FALSE;
    }
    return TRUE;
}

// .text:0x000C2C80 size:0x25C mapped:0x80701D14
void fn_3_C2C80(CastleSparkParticle* p, StadiumLink* link) {
    f32 ang;
    f32 alpha;

    ang = const_pi_or_180 * (f32)(rand() % 360);
    p->vel.x = 0.01 * cosf_kludge(ang);
    p->vel.z = 0.01 * sinf_kludge(ang);
    p->vel.y = 0.08f;
    p->scale = 0.5f;
    p->scale = p->scale + (f64)((u32)rand() % 2500) / 1000.0;
    p->_38 = p->scale;
    p->_3C = 2.0 * p->scale;
    p->_20 = (f64)(rand() % 101) / 100.0;
    p->_4F = p->_4A = rand() % 24 + 0x48;
    p->pos.x = link->prevPos.x;
    p->pos.y = link->prevPos.y;
    p->pos.z = link->prevPos.z;
    p->_40 = lbl_3_rodata_2028[0];
    p->_41 = lbl_3_rodata_2028[1];
    p->_42 = lbl_3_rodata_2028[2];
    alpha = 255.0f;
    p->alpha = alpha;
    p->_43 = alpha;
    p->_4A = p->_4F;
    p->_48 = 0;
}

// .text:0x000C2EDC size:0x214 mapped:0x80701F70
void fn_3_C2EDC(CastleFlameParticle* p) {
    p->_38 += p->_20 * (3.0 * p->scale / p->_4F);
    p->_3C += p->_20 * (2.0 * p->scale / p->_4F);
    p->alpha += -255.0f / p->_4F;
    if (p->alpha < 0.0f) {
        p->alpha = 0.0f;
    }
    p->alphaByte = (u8)p->alpha;
    p->_40 = (u8)(lbl_3_rodata_2028[0] * (p->alphaByte / 255.0));
    p->_41 = (u8)(lbl_3_rodata_2028[1] * (p->alphaByte / 255.0));
    p->_42 = (u8)(lbl_3_rodata_2028[2] * (p->alphaByte / 255.0));
    p->origin.x += p->velX;
    p->origin.y -= p->_14;
    p->origin.z += p->velZ;
    p->_4A--;
}

// .text:0x000C30F0 size:0x57C mapped:0x80702184
BOOL fn_3_C30F0(CastleFlameEmitter* emitter) {
    CastleFlameParticle* p = emitter->particles;

    if (g_GameLogic.gameStatus >= GAME_STATUS_0x1B && g_GameLogic.gameStatus <= GAME_STATUS_MINIGAME_READY) {
        return FALSE;
    }
    if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL || g_GameLogic.gameStatus == GAME_STATUS_AT_BAT) {
        Vec pos = emitter->origin;

        if (!fn_3_C2AA0(&pos, 4.0f, 4.0f)) {
            return FALSE;
        }
    }
    fn_80033620(emitter);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_LO_CLEAR);

    do {
        if (p->_48 <= 0 && p->_4A != 0) {
            fn_8003403C(p->_38, p->_3C);
            fn_80033CC8(p, emitter->_10);
            if (returnsCurrentMode() == 0) {
                fn_3_C2EDC(p);
            }
        }
        p->_48 -= (returnsCurrentMode() == 0);
        if (p->_4A == 0) {
            f32 ang = const_pi_or_180 * (f32)(rand() % 360);
            f32 alpha = 255.0f;

            p->velX = 0.01 * cosf_kludge(ang);
            p->velZ = 0.01 * sinf_kludge(ang);
            p->_14 = 0.08f;
            p->scale = 0.5f;
            p->scale = p->scale + (f64)((u32)rand() % 2500) / 1000.0;
            p->_38 = p->scale;
            p->_3C = 2.0 * p->scale;
            p->_20 = (f64)(rand() % 101) / 100.0;
            p->_4F = p->_4A = rand() % 24 + 0x48;
            p->origin.x = emitter->origin.x;
            p->origin.y = emitter->origin.y;
            p->origin.z = emitter->origin.z;
            p->_40 = lbl_3_rodata_2028[0];
            p->_41 = lbl_3_rodata_2028[1];
            p->_42 = lbl_3_rodata_2028[2];
            p->alpha = alpha;
            p->alphaByte = alpha;
            p->_4A = p->_4F;
            p->_48 = 0;
        }
        p = p->next;
    } while (p != NULL);
    return FALSE;
}

// .text:0x000C366C size:0x35C mapped:0x80702700
void fn_3_C366C(void* handlePtr, u8 idx) {
    CastleFlameEmitter* handle = (CastleFlameEmitter*)handlePtr;
    s16 i = 0;
    CastleFlameParticle* p = handle->particles;
    f32 ang;
    f32 alpha;

    handle->_10 = lbl_3_bss_9F0C[0];
    handle->origin = lbl_3_rodata_202C[idx];
    handle->kind = idx;
    alpha = 255.0f;

    for (; p != NULL; p = p->next) {
        ang = const_pi_or_180 * (f32)(rand() % 360);
        p->velX = 0.01 * cosf_kludge(ang);
        p->velZ = 0.01 * sinf_kludge(ang);
        p->_14 = 0.08f;
        p->_48 = i;
        p->scale = 0.5f;
        p->scale = p->scale + (f64)((u32)rand() % 2500) / 1000.0;
        p->_38 = p->scale;
        p->_3C = 2.0 * p->scale;
        p->_20 = (f64)(rand() % 101) / 100.0;
        p->origin.x = handle->origin.x;
        p->origin.y = handle->origin.y;
        p->origin.z = handle->origin.z;
        p->_40 = lbl_3_rodata_2028[0];
        p->_41 = lbl_3_rodata_2028[1];
        p->_42 = lbl_3_rodata_2028[2];
        p->alpha = alpha;
        p->alphaByte = alpha;
        p->_4F = p->_4A = rand() % 24 + 0x48;
        p->_4D = 0x1D;
        p->_4E = 0;
        i += 4;
    }
}

// .text:0x000C39C8 size:0x70 mapped:0x80702A5C
void bowserCastleSomething(void) {
    u32 i;

    for (i = 0; i < 6; i++) {
        void* handle = allocParticleEffect(fn_3_C30F0, 0x80, 0, 0x15, TRUE, 0);
        if (handle != NULL) {
            fn_3_C366C(handle, i);
        }
    }
}

// .text:0x000C3A38 size:0x1F4 mapped:0x80702ACC
void thwomp_screenShake(camera_803c639c_s* cam) {
    Vec offset;
    Mtx invView;

    if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL || cam == NULL) {
        thwompScreenShakeTimeRemaining = 0;
        startScreenShake = FALSE;
        fn_800528B4();
        return;
    }
    if (startScreenShake) {
        thwompScreenShakeTimeRemaining = 60;
        startScreenShake = FALSE;
    }
    if (thwompScreenShakeTimeRemaining == 0) {
        return;
    }
    offset.x = (f32)(rand() % 20 - 10) / 17.0f;
    offset.y = (f32)(rand() % 20 - 10) / 17.0f;
    offset.z = 0.0f;
    PSMTXInverse(fn_80052768_getCamera(0)->view, invView);
    PSMTXMultVecSR(invView, &offset, &offset);
    cam->eye.x += offset.x;
    cam->eye.y += offset.y;
    cam->eye.z += offset.z;
    cam->target.x += offset.x;
    cam->target.y += offset.y;
    cam->target.z += offset.z;
    thwompScreenShakeTimeRemaining--;
}

// .text:0x000C3C2C size:0x268 mapped:0x80702CC0
void fn_3_C3C2C(void) {
    DrawingSceneStruct* item = currentDrawingItem;
    int i;

    for (i = 0; i < 8; i++) {
        u8 state = lbl_3_bss_9E48[i];

        switch (state) {
        case 1: {
            s16 sy;
            s16 sx;

            fn_800528C0(lbl_3_bss_9DE8[i].x, lbl_3_bss_9DE8[i].y, lbl_3_bss_9DE8[i].z, &sx, &sy);
            ((CastleGfxObject*)graphicsRelatedArray[lbl_3_bss_9E50.scene->firstHandle + i].object)->pos.x = (f32)sx;
            ((CastleGfxObject*)graphicsRelatedArray[lbl_3_bss_9E50.scene->firstHandle + i].object)->pos.y = (f32)sy;
            ((CastleGfxObject*)graphicsRelatedArray[lbl_3_bss_9E50.scene->firstHandle + i].object)->pos.z = 0.0f;
            ((CastleGfxObject*)graphicsRelatedArray[((CastleGfxScene*)item)->firstHandle + i].object)->frameIndex = 0;
            ((CastleGfxObject*)graphicsRelatedArray[((CastleGfxScene*)item)->firstHandle + i].object)->flags |= 2;
            lbl_3_bss_9E48[i] = 2;
            break;
        }
        case 2: {
            s16 sy;
            s16 sx;

            fn_800528C0(lbl_3_bss_9DE8[i].x, lbl_3_bss_9DE8[i].y, lbl_3_bss_9DE8[i].z, &sx, &sy);
            ((CastleGfxObject*)graphicsRelatedArray[lbl_3_bss_9E50.scene->firstHandle + i].object)->pos.x = (f32)sx;
            ((CastleGfxObject*)graphicsRelatedArray[lbl_3_bss_9E50.scene->firstHandle + i].object)->pos.y = (f32)sy;
            ((CastleGfxObject*)graphicsRelatedArray[lbl_3_bss_9E50.scene->firstHandle + i].object)->pos.z = 0.0f;
            if (((CastleGfxObject*)graphicsRelatedArray[((CastleGfxScene*)item)->firstHandle + i].object)->scale == 2) {
                ((CastleGfxObject*)graphicsRelatedArray[((CastleGfxScene*)item)->firstHandle + i].object)->flags &= ~2;
                lbl_3_bss_9E48[i] = 0;
            }
            break;
        }
        }
    }
    if (lbl_3_bss_9DE7 != 0) {
        removeCurrentDrawingItem();
        removeGraphicsElementFromScene((DrawingSceneStruct*)lbl_3_bss_9E50.scene);
        lbl_3_bss_9DE7 = 0;
    }
}

// .text:0x000C3E94 size:0xDC mapped:0x80702F28
void fn_3_C3E94(Vec* p, int idx) {
    s16 sx;
    s16 sy;

    fn_800528C0(p->x, p->y, p->z, &sx, &sy);
    ((CastleGfxObject*)graphicsRelatedArray[lbl_3_bss_9E50.scene->firstHandle + idx].object)->pos.x = sx;
    ((CastleGfxObject*)graphicsRelatedArray[lbl_3_bss_9E50.scene->firstHandle + idx].object)->pos.y = sy;
    ((CastleGfxObject*)graphicsRelatedArray[lbl_3_bss_9E50.scene->firstHandle + idx].object)->pos.z = 0.0f;
}

// .text:0x000C3F70 size:0xF8 mapped:0x80703004
void fn_3_C3F70(StadiumObject* obj) {
    CastleMaterialRoot* root = (CastleMaterialRoot*)obj->model->root;
    u32 i;

    if (lbl_3_bss_9D88++ > 4) {
        lbl_3_data_177F0++;
        if (lbl_3_data_177F0 > 0x13) {
            lbl_3_data_177F0 = 4;
        }
        lbl_3_bss_9D88 = 0;
    }
    if (lbl_3_bss_9D88 != 0) {
        return;
    }
    for (i = 0; i < root->groupCount; i++) {
        CastleMaterialListHolder* holder = root->groups[i]->holder;

        if (holder != NULL) {
            CastleMaterialEntry* entry = holder->list->entries;
            u32 j;

            for (j = 0; j < holder->list->count; entry++, j++) {
                if (entry->kind == 1) {
                    entry->animState &= ~0x1FFF;
                    entry->animState |= lbl_3_data_177F0;
                }
            }
        }
    }
}

// .text:0x000C4068 size:0x84 mapped:0x807030FC
void fn_3_C4068(StadiumObject* obj) {
    CastleModelRoot* root = (CastleModelRoot*)obj->model->root;
    CastleMaterialFlags* mat = root->next->flameMat->next->next->next;
    u16 value = mat->animState & 0x1FFF;

    if (lbl_3_bss_9D84++ > 4) {
        value++;
        if (value > 0x13) {
            value = 4;
        }
        lbl_3_bss_9D84 = 0;
    }
    mat->animState &= ~0x1FFF;
    mat->animState |= value;
}

// .text:0x000C40EC size:0x60 mapped:0x80703180
void fn_3_C40EC(StadiumObject* obj) {
    CastleModelRoot* root = (CastleModelRoot*)obj->model->root;
    CastleMaterialFlags* mat = root->next->flameMat->next->next->next;

    if (((CastleHazardObj*)obj)->hazardType != 6) {
        mat->animState &= ~0x1FFF;
        mat->animState |= 0x19;
    } else {
        mat->animState &= ~0x1FFF;
        mat->animState |= 0x1A;
    }
}

// .text:0x000C414C size:0x158 mapped:0x807031E0
void bowserCastleStarPadsContaactFn(int offset) {
    StadiumObject* obj = &stadiumObjectCollision.objects[offset];
    Vec trans;
    BOOL awarded = FALSE;

    CTRLGetTranslation((Control*)obj, &trans.x, &trans.y, &trans.z);
    if (g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_FIELDED) {
        if (((CastleHazardObj*)obj)->hazardType == 5) {
            if (inningSetting.starSkillsSetting != 0) {
                stadiumStarAwarded(trans.x, trans.y - 5.0f, trans.z);
                ((CastleHazardObj*)obj)->hazardType = 6;
                awarded = TRUE;
            }
        } else if (((CastleHazardObj*)obj)->hazardType == 4) {
            if (inningSetting.starSkillsSetting != 0) {
                stadiumStarAwarded(trans.x, trans.y, trans.z - 5.0f);
                ((CastleHazardObj*)obj)->hazardType = 6;
                awarded = TRUE;
            }
        }
    }
    if (awarded) {
        int idx = (g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy != 0) + 6;

        lbl_3_bss_9E48[idx] = 1;
        lbl_3_bss_9DE8[idx].x = g_Ball.AtBat_Contact_BallPos.x;
        lbl_3_bss_9DE8[idx].y = -g_Ball.AtBat_Contact_BallPos.y;
        lbl_3_bss_9DE8[idx].z = g_Ball.AtBat_Contact_BallPos.z;
    }
}

// .text:0x000C42A4 size:0x1A8 mapped:0x80703338
void stadiumObjCollision_Castle(s32* idx, s32* count) {
    CastleSlotPlacement* cfg;
    int off;
    int i;
    int j;
    int k;
    StadiumObject* obj;
    Mtx m;

    for (i = 0; i < 5; i++) {
        off = (u16)(stadiumObjectCollision.vertexOffsets[*idx - 1] + stadiumObjectCollision.hazardData[*idx - 1]);
        stadiumObjectCollision.vertexOffsets[*idx] = off;
        initBoundingBoxLimits();
        cfg = lbl_3_data_17704.entries;
        for (j = 0; j < 10; cfg++, j++) {
            if (i == cfg->group && cfg->usedFlag != 7) {
                k = j + lbl_3_bss_9DE0;
                if (stadiumObjectCollision.objects[k]._90b1) {
                    ((s32*)stadiumObjectCollision.vertexData)[off] = k;
                    off++;
                    stadiumObjectCollision.hazardData[*idx]++;
                    obj = &stadiumObjectCollision.objects[j + lbl_3_bss_9DE0];
                    CTRLBuildMatrix((Control*)obj, m);
                    transformVectorsUpdateBoundingBox(m, (StadiumMeshData*)obj->triangles);
                    m[1][3] = m[1][3] * -100.0f;
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

// .text:0x000C444C size:0x2D8 mapped:0x807034E0
void fn_3_C444C(CastleFireballEmitter* handle, StadiumObject* obj) {
    CastleFlameParticle* p = handle->particles;
    f32 x = ((CastleFireballTarget*)obj)->anchorPos.x;
    f32 y = ((CastleFireballTarget*)obj)->anchorPos.y;
    f32 z = ((CastleFireballTarget*)obj)->anchorPos.z;
    u32 i = 0;
    f32 ang1;
    f32 ang2;
    f32 mag;

    for (; p != NULL; p = p->next) {
        p->origin.x = x;
        p->origin.y = y;
        p->origin.z = z;
        ang1 = 3.1415927f * (f32)(rand() % 360) / 180.0f;
        ang2 = 3.1415927f * (f32)(rand() % 360) / 180.0f;
        mag = 0.5f - (f32)(rand() % 3) / 10.0f;
        p->velX = mag * cos(ang1) * cos(ang2);
        p->_14 = -mag * sin(ang1);
        p->velZ = mag * sin(ang1) * cos(ang2);
        p->_3C = 4.4f;
        p->_38 = 4.4f;
        p->_48 = i / 6;
        i++;
        p->_4D = 0x1B;
        p->_4E = 0;
        p->alphaByte = 0xFF;
        p->_42 = 0xFF;
        p->_41 = 0xFF;
        p->_40 = 0xFF;
        p->_4A = 1;
    }
}

// .text:0x000C4724 size:0x1AC mapped:0x807037B8
BOOL fn_3_C4724(CastleSparkEmitter* emitter) {
    CastleSparkParticle* p = emitter->particles;
    u32 i = 0;

    fn_80033620(emitter);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    do {
        if (p->_48 != 0) {
            p->_48 -= (lbl_80366158._28 == 0);
        } else {
            if (p->_4A == 0) {
                continue;
            }
            fn_8003403C(p->_38, p->_3C);
            fn_80033CC8(p, emitter->_10);
            if (lbl_80366158._28 == 0) {
                p->pos.x += p->vel.x;
                p->pos.y += p->vel.y;
                p->pos.z += p->vel.z;
                p->_38 -= 0.275f;
                p->_3C -= 0.275f;
                p->_43 -= 0xF;
                if (p->_38 <= 0.0f || p->_3C <= 0.0f) {
                    p->_4A = 0;
                }
            }
        }
        i++;
    } while ((p = p->next) != NULL && i < (emitter->_14 & 0xFFF));

    emitter->_24 -= (lbl_80366158._28 == 0);
    if (emitter->_24 == 0) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x000C48D0 size:0x2B0 mapped:0x80703964
void fn_3_C48D0(CastleFireballEmitter* handle, Vec pos) {
    CastleFlameParticle* p;
    u32 i = 0;
    f32 ang1;
    f32 ang2;
    f32 mag;

    for (p = handle->particles; p != NULL; p = p->next) {
        p->origin.x = pos.x;
        p->origin.y = pos.y;
        p->origin.z = pos.z;
        ang1 = 3.1415927f * (f32)(rand() % 181) / 180.0f;
        ang2 = 3.1415927f * (f32)(rand() % 360) / 180.0f;
        mag = 0.5f - (f32)(rand() % 3) / 10.0f;
        p->velX = mag * cos(ang1) * cos(ang2);
        p->_14 = -mag * sin(ang1);
        p->velZ = mag * sin(ang1) * cos(ang2);
        p->_3C = 4.4f;
        p->_38 = 4.4f;
        p->_48 = i / 6;
        i++;
        p->_4D = 0x1B;
        p->_4E = 0;
        p->alphaByte = 0xFF;
        p->_42 = 0xFF;
        p->_41 = 0xFF;
        p->_40 = 0xFF;
        p->_4A = 1;
    }
}

// .text:0x000C4B80 size:0x174 mapped:0x80703C14
void fn_3_C4B80(void) {
    camera_803c639c_s* cam;

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
    cam = returnFloatFromModeIndex(returnsCurrentMode());
    GXSetProjection(cam->proj, GX_PERSPECTIVE);
    cam = returnFloatFromModeIndex(returnsCurrentMode());
    GXLoadPosMtxImm(cam->view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
}

// .text:0x000C4CF4 size:0x20C mapped:0x80703D88
void fn_3_C4CF4(CastleFlameEmitter* emitter, u8 group) {
    CastleFlameParticle* p = emitter->particles;
    camera_803c639c_s* cam;

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
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
    cam = returnFloatFromModeIndex(returnsCurrentMode());
    GXSetProjection(cam->proj, GX_PERSPECTIVE);
    cam = returnFloatFromModeIndex(returnsCurrentMode());
    GXLoadPosMtxImm(cam->view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    while (p != NULL) {
        if (p->_48 <= 0 && p->_4A > 0 && group == p->_50) {
            fn_8003403C(p->_38, p->_3C);
            fn_80033CC8(p, emitter->_10);
        }
        p = p->next;
    }
}

// .text:0x000C4F00 size:0x404 mapped:0x80703F94
BOOL fn_3_C4F00(CastleFireballEmitter* handle) {
    CastleFlameParticle* p;
    Vec off;
    Mtx m;
    f32 ang;
    f32 mag;

    fn_80033620(handle);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);

    p = handle->particles;
    do {
        if (p->_48 != 0) {
            p->_48 -= (lbl_80366158._28 == 0);
            if (p->_48 == 0) {
                mag = (f32)(15 - rand() % 31) / 10.0f;
                ang = 3.1415927f * (f32)(rand() % 361) / 180.0f;
                off.x = mag * cos(ang);
                off.z = mag * sin(ang);
                off.y = 2.5f;
                CTRLBuildMatrix((Control*)handle->target, m);
                PSMTXMultVec(m, &off, &p->origin);
            }
        } else if (p->_4A != 0 && lbl_80366158._28 == 0) {
            if (p->_4F == 0) {
                p->alphaByte += 0xF;
                p->_38 += 0.125f;
                p->_3C += 0.125f;
                if (p->_38 >= 2.0f || p->_3C >= 2.0f) {
                    p->_4F = 1;
                }
            } else {
                p->alphaByte -= 0xF;
                p->_38 -= 0.125f;
                p->_3C -= 0.125f;
                if (p->_38 <= 0.0f || p->_3C <= 0.0f) {
                    p->_4A = 0;
                }
            }
        }

        if (p->_4A == 0) {
            p->_3C = 0.0f;
            p->_38 = 0.0f;
            p->_4A = 1;
            p->_4F = 0;
            p->_48 = 0;
            mag = (f32)(15 - rand() % 31) / 10.0f;
            ang = 3.1415927f * (f32)(rand() % 361) / 180.0f;
            off.x = mag * cos(ang);
            off.z = mag * sin(ang);
            off.y = 2.5f;
            CTRLBuildMatrix((Control*)handle->target, m);
            PSMTXMultVec(m, &off, &p->origin);
            p->alphaByte = 0;
        }
        p = p->next;
    } while (p != NULL);
    return FALSE;
}

// .text:0x000C5304 size:0x1CC mapped:0x80704398
void fn_3_C5304(CastleFireballEmitter* handle, StadiumObject* obj) {
    CastleFlameParticle* p = handle->particles;
    s16 i = 0;

    handle->targetPos = &((CastleFireballTarget*)obj)->anchorPos;
    handle->target = obj;

    for (; p != NULL; p = p->next) {
        p->_3C = 0.0f;
        p->_38 = 0.0f;
        p->_48 = i;
        i += 4;
        p->_4D = 0x15;
        p->_4E = 0;
        p->_42 = 0xFF;
        p->_41 = 0xFF;
        p->_40 = 0xFF;
        p->alphaByte = 0;
        p->_4A = 1;
        p->_4F = 0;
        if (p->_48 == 0) {
            p->origin.x = handle->targetPos->x + (f32)(15 - rand() % 31) / 10.0f;
            p->origin.y = 2.5f + handle->targetPos->y;
            p->origin.z = handle->targetPos->z + (f32)(15 - rand() % 31) / 10.0f;
        } else {
            p->origin.z = 0.0f;
            p->origin.y = 0.0f;
            p->origin.x = 0.0f;
        }
    }
}

// .text:0x000C54D0 size:0x218 mapped:0x80704564
void fn_3_C54D0(StadiumObject* obj) {
    CastleFlameEmitter* handle =
        (CastleFlameEmitter*)fn_800339F0(0, ((CastleHazardObj*)obj)->_A8 + 0x2A);
    CastleFlameParticle* p;
    camera_803c639c_s* cam;

    if (handle == NULL) {
        return;
    }
    p = handle->particles;

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
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
    cam = returnFloatFromModeIndex(returnsCurrentMode());
    GXSetProjection(cam->proj, GX_PERSPECTIVE);
    cam = returnFloatFromModeIndex(returnsCurrentMode());
    GXLoadPosMtxImm(cam->view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    while (p != NULL) {
        if (p->_48 <= 0 && p->_4A > 0 && p->_50 == 1) {
            fn_8003403C(p->_38, p->_3C);
            fn_80033CC8(p, handle->_10);
        }
        p = p->next;
    }
}

// .text:0x000C56E8 size:0x294 mapped:0x8070477C
void fn_3_C56E8(StadiumObject* obj) {
    camera_803c639c_s* cam;
    Vec anchorView;
    CastleFireballEmitter* handle;
    CastleFlameParticle* p;

    cam = returnFloatFromModeIndex(returnsCurrentMode());
    PSMTXMultVec(cam->view, &((CastleFireballTarget*)obj)->anchorPos, &anchorView);
    handle = fn_800339F0(0, ((CastleHazardObj*)obj)->_A8 + 0x2A);
    if (handle == NULL) {
        return;
    }
    for (p = handle->particles; p != NULL; p = p->next) {
        Vec pView;

        cam = returnFloatFromModeIndex(returnsCurrentMode());
        PSMTXMultVec(cam->view, &p->origin, &pView);
        if (anchorView.z >= pView.z) {
            p->_50 = 1;
        } else {
            p->_50 = 0;
        }
    }

    p = handle->particles;
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
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
    cam = returnFloatFromModeIndex(returnsCurrentMode());
    GXSetProjection(cam->proj, GX_PERSPECTIVE);
    cam = returnFloatFromModeIndex(returnsCurrentMode());
    GXLoadPosMtxImm(cam->view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    for (; p != NULL; p = p->next) {
        if (p->_48 <= 0 && p->_4A > 0 && p->_50 == 0) {
            fn_8003403C(p->_38, p->_3C);
            fn_80033CC8(p, handle->_10);
        }
    }
}

// .text:0x000C597C size:0x364 mapped:0x80704A10
void fn_3_C597C(s32 objIndex) {
    StadiumObject* obj = &stadiumObjectCollision.objects[objIndex];
    CastleFireballEmitter* handle;
    CastleFlameParticle* p;
    f32 x;
    f32 y;
    f32 z;
    u32 i;
    f32 ang1;
    f32 ang2;
    f32 mag;

    pitchingMachinePitching(((CastleHazardObj*)obj)->_A8 + 0x2A);
    handle = allocParticleEffect(fn_3_C4724, 0x80, 0, 0x18, TRUE, ((CastleHazardObj*)obj)->_A8 + 0x34);
    if (handle != NULL) {
        p = handle->particles;
        x = ((CastleFireballTarget*)obj)->anchorPos.x;
        y = ((CastleFireballTarget*)obj)->anchorPos.y;
        z = ((CastleFireballTarget*)obj)->anchorPos.z;
        i = 0;

        for (; p != NULL; p = p->next) {
            p->origin.x = x;
            p->origin.y = y;
            p->origin.z = z;
            ang1 = 3.1415927f * (f32)(rand() % 360) / 180.0f;
            ang2 = 3.1415927f * (f32)(rand() % 360) / 180.0f;
            mag = 0.5f - (f32)(rand() % 3) / 10.0f;
            p->velX = mag * cos(ang1) * cos(ang2);
            p->_14 = -mag * sin(ang1);
            p->velZ = mag * sin(ang1) * cos(ang2);
            p->_3C = 4.4f;
            p->_38 = 4.4f;
            p->_48 = i / 6;
            i++;
            p->_4D = 0x1B;
            p->_4E = 0;
            p->alphaByte = 0xFF;
            p->_42 = 0xFF;
            p->_41 = 0xFF;
            p->_40 = 0xFF;
            p->_4A = 1;
        }
        handle->_10 = lbl_3_bss_9F0C[0];
        handle->_24 = 0x1E;
    }
    ((CastleHazardObj*)obj)->_BD = 2;
    obj->hasShadow = 0;
    obj->pos.x = 10.0f;
}

// .text:0x000C5CE0 size:0xFC mapped:0x80704D74
BOOL castleFireballMaybe(StadiumObject* obj) {
    Vec off = { 0.0f, 0.0f, 0.0f };
    Vec diff;
    f32 dist;
    u32 i;

    if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL && g_GameLogic.playOver) {
        return FALSE;
    }
    for (i = 0; i < 9; i++) {
        memset(&off, 0, sizeof(Vec));
        getAnimationCollisionOffset(i, 4, &off);
        PSVECSubtract(&off, &((CastleFireballTarget*)obj)->anchorPos, &diff);
        dist = PSVECMag(&diff);
        if (dist <= 2.6f) {
            maybeCastleFireballBurn(i, 1);
            return TRUE;
        }
    }
    return FALSE;
}

// .text:0x000C5DDC size:0x480 mapped:0x80704E70
void bowserCastleRelated(void) {
    u32 i;

    if (lbl_3_bss_9D82 != 0) {
        lbl_3_bss_9D82 = 0;
        removeCurrentDrawingItem();
    } else {
        for (i = 0; i < lbl_3_bss_9DE3; i++) {
            StadiumObject* obj = &stadiumObjectCollision.objects[lbl_3_bss_9DE2 + i];

            if (((CastleFireObj*)obj)->state == FLAME_FLYING && castleFireballMaybe(obj)) {
                CastleFireballEmitter* handle =
                    allocParticleEffect(fn_3_C4724, 0x80, 0, 0x18, TRUE, ((CastleHazardObj*)obj)->_A8 + 0x34);

                if (handle != NULL) {
                    fn_3_C48D0(handle, ((CastleFireballTarget*)obj)->anchorPos);
                    handle->_10 = lbl_3_bss_9F0C[0];
                    handle->_24 = 0x1E;
                }
                ((CastleFireObj*)obj)->state = FLAME_EXPLODING;
                ((CastleFireObj*)obj)->visible = FALSE;
                ((CastleFireObj*)obj)->pos.y = 10.0f;
            }
        }
    }
}

// .text:0x000C625C size:0x174 mapped:0x807052F0
E(u8, BOOL) fn_3_C625C(StadiumObject* obj) {
    Vec target = ((CastleFireballTarget*)obj)->anchorPos;
    Vec diff;
    f32 dist;
    int stadiumID;
    u8 vol;
    u8 val;
    SND_VOICEID voice;

    if (g_Ball.ballState == BALL_STATE_HELD) {
        return FALSE;
    }
    if ((g_Ball.currentStarSwing2 == 11) | (g_Ball.currentStarSwing2 == 12)) {
        return FALSE;
    }
    target.y *= -1.0f;
    PSVECSubtract((Vec*)&g_Ball.AtBat_Contact_BallPos, &target, &diff);
    dist = PSVECMag(&diff);
    if (dist <= 2.6f) {
        stadiumID = g_d_GameSettings.StadiumID;
        vol = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                  ? lbl_3_data_84B8[4]
                  : stadiumHazardSoundFxRelated[stadiumID * 0x1E + 4];
        voice = sndFXStartEx(stadiumHazardSoundIDs[stadiumID] + 2, vol, 0x3f, 0);
        val = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                  ? lbl_3_data_84B8[5]
                  : stadiumHazardSoundFxRelated[stadiumID * 0x1E + 5];
        sndFXCtrl(voice, 0x5b, val);
        return TRUE;
    }
    return FALSE;
}

// .text:0x000C63D0 size:0xDFC mapped:0x80705464
void flameControl(CastleFireObj* fire) {
    Vec up = { 0.0f, 1.0f, 0.0f };
    VecSrcDst seg;
    CollisionStruct hitInfo;
    Vec axis;
    Vec dir;
    Quaternion q;
    CastleFireballEmitter* handle;
    f32 ang;
    f32 speed;
    u32 i;
    int stadiumID;
    u8 vol;
    u8 val;
    SND_VOICEID voice;
    u8 hit = 0;

    if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
        if (!fire->resetPending) {
            fire->pos.x = BowserStadFireSpawners[fire->id].x;
            fire->pos.y = BowserStadFireSpawners[fire->id].y;
            fire->pos.z = BowserStadFireSpawners[fire->id].z;
            fire->state = FLAME_IDLE;
            CTRLSetTranslation((Control*)fire, fire->pos.x, fire->pos.y, fire->pos.z);
            fire->visible = FALSE;
            pitchingMachinePitching(fire->id + 0x2A);
            pitchingMachinePitching(fire->id + 0x34);
            fire->resetPending = TRUE;
        }
        return;
    }

    fire->resetPending = FALSE;
    switch (fire->state) {
    case FLAME_IDLE:
        if (fire->launchTimer == 0) {
            for (i = 6; i < 9; i++) {
                if ((f32)sqrt(pow((*(CastleAnimActor**)(hugeAnimStruct + i * 4 + 0x2C50))->pos.x - fire->pos.x, 2.0) +
                              pow((*(CastleAnimActor**)(hugeAnimStruct + i * 4 + 0x2C50))->pos.z - fire->pos.z, 2.0)) < 5.0) {
                    fire->pos.x = BowserStadFireSpawners[fire->id].x;
                    fire->pos.y = BowserStadFireSpawners[fire->id].y;
                    fire->pos.z = BowserStadFireSpawners[fire->id].z;
                    CTRLSetTranslation((Control*)fire, fire->pos.x, fire->pos.y, fire->pos.z);
                    return;
                }
            }
            fire->state = FLAME_FLYING;
            fire->visible = TRUE;
            ang = 3.1415927f * (f32)(fire->launchAngleBase + rng((s16)fire->launchAngleSpread)) / 180.0f;
            speed = flameXVelos[rng(3)];
            fire->velo.x = speed * cos(ang);
            fire->velo.y = 0.37f;
            fire->velo.z = speed * sin(ang);
            handle = allocParticleEffect(fn_3_C4F00, 0x80, 0, 7, TRUE, fire->id + 0x2A);
            if (handle != NULL) {
                fn_3_C5304(handle, (StadiumObject*)fire);
                handle->_10 = lbl_3_bss_9F0C[0];
            }
            fire->launchTimer = rng(240) + 1;
            stadiumID = g_d_GameSettings.StadiumID;
            vol = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                      ? lbl_3_data_84B8[6]
                      : stadiumHazardSoundFxRelated[stadiumID * 0x1E + 6];
            voice = sndFXStartEx(stadiumHazardSoundIDs[stadiumID] + 3, vol, 0x3f, 0);
            val = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                      ? lbl_3_data_84B8[7]
                      : stadiumHazardSoundFxRelated[stadiumID * 0x1E + 7];
            sndFXCtrl(voice, 0x5b, val);
        } else {
            fire->launchTimer--;
        }
        break;
    case FLAME_FLYING:
        seg.src = fire->pos;
        fire->pos.x += fire->velo.x;
        fire->pos.y -= fire->velo.y;
        fire->pos.z += fire->velo.z;
        seg.dst = fire->pos;
        fire->velo.y -= 0.0044f;
        PSVECNormalize(&fire->velo, &dir);
        PSVECCrossProduct(&dir, &up, &axis);
        C_QUATRotAxisRad(&q, &axis, acos(PSVECDotProduct(&dir, &up)));
        CTRLSetQuat((Control*)fire, q.x, q.y, q.z, q.w);
        if (fire->velo.y < 0.0f && (u32)checkCollision(&seg, &hitInfo, 0, FALSE) != 0) {
            hit = 1;
        }
        if (fn_3_C625C((StadiumObject*)fire)) {
            hit = 2;
        }
        if (hit) {
            pitchingMachinePitching(fire->id + 0x2A);
            if (hit == 1) {
                handle = allocParticleEffect(fn_3_C4724, 0x80, 0, 0x18, TRUE, fire->id + 0x34);
                if (handle != NULL) {
                    fn_3_C48D0(handle, fire->pos);
                    handle->_10 = lbl_3_bss_9F0C[0];
                    handle->_24 = 0x1E;
                }
            } else if (hit == 2) {
                handle = allocParticleEffect(fn_3_C4724, 0x80, 0, 0x18, TRUE, fire->id + 0x34);
                if (handle != NULL) {
                    fn_3_C444C(handle, (StadiumObject*)fire);
                    handle->_10 = lbl_3_bss_9F0C[0];
                    handle->_24 = 0x1E;
                }
            }
            fire->state = FLAME_ENDED;
            fire->visible = FALSE;
            fire->pos.y = 10.0f;
        }
        break;
    case FLAME_EXPLODING:
        if (!fn_80033928(fire->id + 0x34)) {
            fire->state = FLAME_ENDED;
        }
        break;
    case FLAME_ENDED:
        fire->state = FLAME_IDLE;
        fire->pos.x = BowserStadFireSpawners[fire->id].x;
        fire->pos.y = BowserStadFireSpawners[fire->id].y;
        fire->pos.z = BowserStadFireSpawners[fire->id].z;
        fire->velo.y = 0.37f;
        fire->visible = FALSE;
        fire->launchTimer = rng(240) + 1;
        CTRLSetRotation((Control*)fire, 0.0f, BowserStadFireSpawners[fire->id].rotation, 0.0f);
        break;
    }
    CTRLSetTranslation((Control*)fire, fire->pos.x, fire->pos.y, fire->pos.z);
}

// .text:0x000C71CC size:0x278 mapped:0x80706260
void stadiumObjRelated_Castle(s32* idx, s32* count) {
    CastleFireSpawner* cfg;
    int off;
    int i;
    int j;
    int k;
    StadiumObject* obj;
    CastleObjControl ctrl;
    Mtx m;
    f32 scale = 84.09091186523438f;
    f32 base = 15.556818962097168f;
    f64 transY = -0.3 * scale + base;

    for (i = 0; i < 5; i++) {
        off = (u16)(stadiumObjectCollision.vertexOffsets[*idx - 1] + stadiumObjectCollision.hazardData[*idx - 1]);
        stadiumObjectCollision.vertexOffsets[*idx] = off;
        initBoundingBoxLimits();
        cfg = BowserStadFireSpawners;
        for (j = 0; j < 10; cfg++, j++) {
            if (i == cfg->group && cfg->usedFlag != 7) {
                k = *count;
                if (stadiumObjectCollision.objects[k]._90b1) {
                    f32 y;
                    f32 jitter;

                    ((s32*)stadiumObjectCollision.vertexData)[off] = k;
                    off++;
                    stadiumObjectCollision.hazardData[*idx]++;
                    obj = &stadiumObjectCollision.objects[*count];
                    ctrl = *(CastleObjControl*)obj;
                    CTRLBuildMatrix((Control*)obj, m);
                    transformVectorsUpdateBoundingBox(m, (StadiumMeshData*)obj->triangles);
                    y = transY;
                    jitter = flameXVelos[2] * 168.18182373046875f;
                    CTRLSetTranslation(&ctrl.ctrl, jitter + cfg->x, y + cfg->y, jitter + cfg->z);
                    CTRLBuildMatrix(&ctrl.ctrl, m);
                    transformVectorsUpdateBoundingBox(m, (StadiumMeshData*)obj->triangles);
                    CTRLSetTranslation(&ctrl.ctrl, cfg->x - jitter, y + cfg->y, cfg->z - jitter);
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

// .text:0x000C7444 size:0x58 mapped:0x807064D8
void fn_3_C7444(StadiumObject* obj) {
    CastleModelRoot* root = (CastleModelRoot*)obj->model->root;
    CastleMaterialFlags* mat = root->next->thwompMat->next->next->next;
    BOOL hasBounced = ((CastleHazardObj*)obj)->hasBounced;

    switch (hasBounced) {
    case 0:
        mat->animState &= ~0x1FFF;
        mat->animState |= 2;
        break;
    default:
        mat->animState &= ~0x1FFF;
        break;
    }
}

// .text:0x000C749C size:0x11C mapped:0x80706530
void thwomp_bounceOffSoundAndVisualFx(void) {
    int idx = (g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy != 0) + 2;
    int stadiumID;
    u8 vol;
    u8 val;
    SND_VOICEID voice;

    lbl_3_bss_9E48[idx] = 1;
    lbl_3_bss_9DE8[idx].x = g_Ball.AtBat_Contact_BallPos.x;
    lbl_3_bss_9DE8[idx].y = -g_Ball.AtBat_Contact_BallPos.y;
    lbl_3_bss_9DE8[idx].z = g_Ball.AtBat_Contact_BallPos.z;

    stadiumID = g_d_GameSettings.StadiumID;
    vol = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD ? lbl_3_data_84B8[8]
                                                                    : stadiumHazardSoundFxRelated[stadiumID * 0x1E + 8];
    voice = sndFXStartEx(stadiumHazardSoundIDs[stadiumID] + 4, vol, 0x3f, 0);
    val = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
              ? lbl_3_data_84B8[9]
              : stadiumHazardSoundFxRelated[stadiumID * 0x1E + 9];
    sndFXCtrl(voice, 0x5b, val);
}

// .text:0x000C75B8 size:0x1F4 mapped:0x8070664C
BOOL thwomp_smokeRelated(CastleSmokeEmitter* smoke) {
    CastleFlameParticle* p;
    s32 fallCounter;

    fallCounter = -smoke->_24;
    fn_80033620(smoke);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    p = smoke->particles;
    do {
        if (p->_48 != 0) {
            p->_48 -= (lbl_80366158._28 == 0);
        } else if (p->_4A != 0) {
            fn_8003403C(p->_38, p->_3C);
            fn_80033CC8(p, smoke->_10);
            if (lbl_80366158._28 == 0) {
                if (p->_38 < p->scale) {
                    p->_38 += p->scale / thwompConstants;
                    p->_3C += p->scale / thwompConstants;
                }
                p->origin.x += p->velX;
                p->origin.z += p->velZ;
                p->origin.y = p->_14 + smoke->target->y - 5.0 * pow(2.0, (f64)fallCounter);
                if (30 - smoke->_24 >= 0x10) {
                    p->alphaByte = (u8)((f32)p->alphaByte - 10.928571701049805f);
                }
            }
        }
        p = p->next;
    } while (p != NULL);

    smoke->_24 -= (lbl_80366158._28 == 0);
    if (smoke->_24 == 0) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x000C77AC size:0x260 mapped:0x80706840
void fn_3_C77AC(CastleFireballEmitter* handle, StadiumObject* obj) {
    CastleFlameParticle* p = handle->particles;
    u32 idx = 0;
    u32 i = 0;
    f32 ang;

    handle->targetPos = &((CastleFireballTarget*)obj)->anchorPos;
    handle->target = obj;
    handle->_10 = lbl_3_bss_9F0C[0];
    handle->_24 = 0x1e;

    for (; p != NULL; p = p->next) {
        p->_3C = 0.0f;
        p->_38 = 0.0f;
        p->scale = 8.0f - (rand() % 3);
        ang = 3.1415927f * ((f32)idx + thwompStaticValues[((CastleHazardObj*)obj)->_A8].rotation) / 180.0f;
        p->velX = 0.35f * cos(ang);
        p->_14 = -(rand() % 3);
        p->velZ = 0.35f * sin(ang);
        idx += 0x1e;
        p->origin.x = handle->targetPos->x;
        p->origin.z = handle->targetPos->z;
        p->_48 = i++ >> 2;
        p->_4D = 0x1c;
        p->_4E = 0;
        p->_42 = 0x7f;
        p->_41 = 0x7f;
        p->_40 = 0x7f;
        p->alphaByte = 0x99;
        p->_4A = 1;
    }
}

// .text:0x000C7A0C size:0x650 mapped:0x80706AA0
void thwomp_slamControl(CastleThwompObj* thwomp) {
    Vec soundPos;
    CastleFireballEmitter* handle;

    if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
        if (!thwomp->resetPending) {
            thwomp->pos.y = thwompStaticValues[thwomp->index].y;
            thwomp->state = THWOMP_PERCHED;
            thwomp->checkForSlam = TRUE;
            CTRLSetTranslation((Control*)thwomp, thwomp->pos.x, thwomp->pos.y, thwomp->pos.z);
            pitchingMachinePitching(thwomp->index + 0x3E);
            thwomp->resetPending = TRUE;
        }
        if (g_GameLogic.gameStatus == GAME_STATUS_DEFAULT) {
            thwomp->fallSpeed = thompFallingSpeedConstants[rng(3)];
        }
        return;
    }

    thwomp->resetPending = FALSE;
    switch (thwomp->state) {
    case THWOMP_PERCHED:
        if (!thwomp->checkForSlam) {
            break;
        }
        if (g_Ball.ballState != BALL_STATE_HIT) {
            thwomp->checkForSlam = FALSE;
        } else if (g_Ball.physicsSubstruct.velocity.z < 0.0f) {
            thwomp->checkForSlam = FALSE;
        } else if (g_Ball.deadBallReason != 0) {
            thwomp->checkForSlam = FALSE;
        } else {
            f32 crossX = g_Ball.physicsSubstruct.velocity.x / g_Ball.physicsSubstruct.velocity.z *
                             (thwomp->pos.z - g_Ball.AtBat_Contact_BallPos.z) +
                         g_Ball.AtBat_Contact_BallPos.x;

            if (crossX < thwomp->pos.x - 25.0f || crossX > 25.0f + thwomp->pos.x) {
                thwomp->checkForSlam = FALSE;
            } else if ((f32)sqrt(pow(thwomp->pos.z - g_Ball.AtBat_Contact_BallPos.z, 2.0) +
                                 (pow(thwomp->pos.x - g_Ball.AtBat_Contact_BallPos.x, 2.0) +
                                  pow(thwomp->pos.y + g_Ball.AtBat_Contact_BallPos.y, 2.0))) < 23.0f &&
                       g_Ball.AtBat_Contact_BallPos.y < 3.0f - thwomp->pos.y) {
                thwomp->state = THWOMP_WINDUP;
            }
        }
        break;
    case THWOMP_WINDUP:
        if (thwomp->pos.y <= thwompStaticValues[thwomp->index].y - 2.5) {
            thwomp->pos.y = thwompStaticValues[thwomp->index].y - 2.5;
            thwomp->state = THWOMP_FALLING;
        } else {
            thwomp->pos.y = thwomp->pos.y - 0.25;
        }
        break;
    case THWOMP_FALLING:
        thwomp->pos.y += thwomp->fallSpeed;
        if (thwomp->pos.y >= -5.0) {
            thwomp->pos.y = -5.0f;
            memcpy(&soundPos, &thwomp->pos, sizeof(Vec));
            thwomp->state = THWOMP_GROUNDED;
            thwomp->framesOnGround = 0;
            startScreenShake = TRUE;
            fn_800528AC(thwomp_screenShake);
            initializeStadiumObjectEmitter(stadiumHazardSoundIDs[g_d_GameSettings.StadiumID] + 5, &soundPos,
                                           NULL, 9);
        }
        if (4.0f * thwomp->fallSpeed + thwomp->pos.y >= -5.0) {
            handle = allocParticleEffect(thwomp_smokeRelated, 0x80, 0, 0xC, TRUE, thwomp->index + 0x3E);
            if (handle != NULL) {
                fn_3_C77AC(handle, (StadiumObject*)thwomp);
            }
        }
        break;
    case THWOMP_GROUNDED:
        if (thwomp->framesOnGround++ > 40) {
            thwomp->state = THWOMP_RETURNING;
            thwomp->framesOnGround = 0;
        }
        break;
    case THWOMP_RETURNING:
        if (thwomp->pos.y <= thwompStaticValues[thwomp->index].y) {
            thwomp->pos.y = thwompStaticValues[thwomp->index].y;
            thwomp->state = THWOMP_PERCHED;
        } else {
            thwomp->pos.y = thwomp->pos.y - 0.2;
        }
        break;
    }
    CTRLSetTranslation((Control*)thwomp, thwomp->pos.x, thwomp->pos.y, thwomp->pos.z);
}

// .text:0x000C805C size:0x1E0 mapped:0x807070F0
void fn_3_C805C(s32* idx, s32* count) {
    CastleSlotPlacement* cfg;
    int off;
    int i;
    int j;
    int k;
    StadiumObject* obj;
    CastleObjControl ctrl;
    Mtx m;

    for (i = 0; i < 5; i++) {
        off = (u16)(stadiumObjectCollision.vertexOffsets[*idx - 1] + stadiumObjectCollision.hazardData[*idx - 1]);
        stadiumObjectCollision.vertexOffsets[*idx] = off;
        initBoundingBoxLimits();
        cfg = thwompStaticValues;
        for (j = 0; j < 10; cfg++, j++) {
            if (i == cfg->group && cfg->usedFlag != 7) {
                k = j + lbl_3_bss_9DE4;
                if (stadiumObjectCollision.objects[k]._90b1) {
                    ((s32*)stadiumObjectCollision.vertexData)[off] = k;
                    off++;
                    stadiumObjectCollision.hazardData[*idx]++;
                    obj = &stadiumObjectCollision.objects[j + lbl_3_bss_9DE4];
                    ctrl = *(CastleObjControl*)obj;
                    CTRLBuildMatrix((Control*)obj, m);
                    transformVectorsUpdateBoundingBox(m, (StadiumMeshData*)obj->triangles);
                    CTRLSetTranslation(&ctrl.ctrl, cfg->x, -5.0f, cfg->z);
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

// .text:0x000C823C size:0x78 mapped:0x807072D0
TriangleGroup* fn_3_C823C(int offset, Mtx m) {
    StadiumObject* obj = &stadiumObjectCollision.objects[offset];

    CTRLBuildMatrix((Control*)obj, m);
    if (((CastleHazardObj*)obj)->hazardType == 5) {
        m[1][3] = 0.002f;
    }
    return stadiumObjectCollision.objects[offset].triangles;
}

// .text:0x000C82B4 size:0x39C mapped:0x80707348
void fn_3_C82B4(void) {
    int idx;
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
    {
        CastleSlotPlacement* cfg;
        int off;
        int i;
        int j;
        int k;
        StadiumObject* obj;
        CastleObjControl ctrl;
        Mtx m;

        for (i = 0; i < 5; i++) {
            off = (u16)(stadiumObjectCollision.vertexOffsets[idx - 1] + stadiumObjectCollision.hazardData[idx - 1]);
            stadiumObjectCollision.vertexOffsets[idx] = off;
            initBoundingBoxLimits();
            cfg = thwompStaticValues;
            for (j = 0; j < 10; cfg++, j++) {
                if (i == cfg->group && cfg->usedFlag != 7) {
                    k = j + lbl_3_bss_9DE4;
                    if (stadiumObjectCollision.objects[k]._90b1) {
                        ((s32*)stadiumObjectCollision.vertexData)[off] = k;
                        off++;
                        stadiumObjectCollision.hazardData[idx]++;
                        obj = &stadiumObjectCollision.objects[j + lbl_3_bss_9DE4];
                        ctrl = *(CastleObjControl*)obj;
                        CTRLBuildMatrix((Control*)obj, m);
                        transformVectorsUpdateBoundingBox(m, (StadiumMeshData*)obj->triangles);
                        CTRLSetTranslation(&ctrl.ctrl, cfg->x, -5.0f, cfg->z);
                        CTRLBuildMatrix(&ctrl.ctrl, m);
                        transformVectorsUpdateBoundingBox(m, (StadiumMeshData*)obj->triangles);
                    }
                }
            }
            if ((u32)stadiumObjectCollision.hazardData[idx] != 0) {
                storeBoundingBoxCoordinates(&((Vec*)stadiumObjectCollision.vertexDataArray)[idx * 2],
                                            &((Vec*)stadiumObjectCollision.vertexDataArray)[idx * 2 + 1]);
                idx++;
            }
        }
    }

    {
        CastleSlotPlacement* cfg;
        int off;
        int i;
        int j;
        int k;
        StadiumObject* obj;
        Mtx m;

        for (i = 0; i < 5; i++) {
            off = (u16)(stadiumObjectCollision.vertexOffsets[idx - 1] + stadiumObjectCollision.hazardData[idx - 1]);
            stadiumObjectCollision.vertexOffsets[idx] = off;
            initBoundingBoxLimits();
            cfg = lbl_3_data_17704.entries;
            for (j = 0; j < 10; cfg++, j++) {
                if (i == cfg->group && cfg->usedFlag != 7) {
                    k = j + lbl_3_bss_9DE0;
                    if (stadiumObjectCollision.objects[k]._90b1) {
                        ((s32*)stadiumObjectCollision.vertexData)[off] = k;
                        off++;
                        stadiumObjectCollision.hazardData[idx]++;
                        obj = &stadiumObjectCollision.objects[j + lbl_3_bss_9DE0];
                        CTRLBuildMatrix((Control*)obj, m);
                        transformVectorsUpdateBoundingBox(m, (StadiumMeshData*)obj->triangles);
                        m[1][3] = m[1][3] * -100.0f;
                        transformVectorsUpdateBoundingBox(m, (StadiumMeshData*)obj->triangles);
                    }
                }
            }
            if ((u32)stadiumObjectCollision.hazardData[idx] != 0) {
                storeBoundingBoxCoordinates(&((Vec*)stadiumObjectCollision.vertexDataArray)[idx * 2],
                                            &((Vec*)stadiumObjectCollision.vertexDataArray)[idx * 2 + 1]);
                idx++;
            }
        }
    }

    stadiumObjectCollision.boundingBoxCount = idx;
}

// .text:0x000C8650 size:0xD2C mapped:0x807076E4
void loadBowserCastle(void** files) {
    u8** animTable = (u8**)(hugeAnimStruct + 0x6C);
    CastleSlotPlacement* thwompCfg;
    CastleFireSpawner* fireCfg;
    CastleSlotPlacement* padCfg;
    StadiumObject* o;
    u32* ids;
    u8 done;
    u32 fireCount;
    u32 animCount;
    u32 idx;
    u32 padAnim;
    u32 i;
    s32 j;
    s32 k;
    s32 n;
    u32 shadowBit;
    CastleFireballEmitter* emitter;

    stadiumObjectCollision.preUpdateFunc = updateGameStatusFlag;
    ids = _OSAllocFromHeap(4, 0x40);
    stadiumObjectCollision._34 = ids;
    processStadiumFileObjects(lbl_3_data_17704.objectTypes, 0x10, (u8*)files, ids);
    lbl_3_bss_9F0C[0] = (u32)files[0];

    for (fireCount = 0; fireCount < 10; fireCount++) {
        if (BowserStadFireSpawners[fireCount].usedFlag == 7) {
            break;
        }
    }
    animCount = fireCount + 5;
    stadiumObjectCollision.propCount = animCount;
    *animTable = ActorObjectInitTable(animCount);
    animateBallRelated(*animTable, 0, 0, files[ids[1]], 0, 0);
    animateBallRelated(*animTable, 1, 1, files[ids[2]], 0, 0);
    animateBallRelated(*animTable, 2, 2, files[ids[3]], 0, 0);
    idx = 3;
    for (i = 0; i < fireCount; i++) {
        animateBallRelated(*animTable, idx, idx, files[ids[4]], 0, 0);
        idx++;
    }
    animateBallRelated(*animTable, idx, idx, files[ids[5]], 0, 0);
    padAnim = idx + 1;
    animateBallRelated(*animTable, padAnim, padAnim, files[ids[6]], 0, 0);
    for (i = 0; i < animCount; i++) {
        fn_800BD548(*animTable + i * 0x90 + 0x34, 4, stadiumObjectCollision.lights[0],
                    stadiumObjectCollision.lights[1], stadiumObjectCollision.lights[2],
                    stadiumObjectCollision.lights[3]);
    }

    adjustInternalPointers(files[ids[10]]);
    for (i = 0; i < fireCount; i++) {
        ACTActorRelated(files[ids[10]], *animTable + (i + 3) * 0x90 + 0x34);
    }
    lbl_3_bss_9E50.effects[1].file = (u32)files[ids[11]];
    actRelated(files[ids[10]], &lbl_3_bss_9E50.effects[1]);
    actorRelated(&lbl_3_bss_9E50.effects[1], 0, 0);
    adjustInternalPointers(files[ids[12]]);
    ACTActorRelated(files[ids[12]], *animTable + 0xC4);
    lbl_3_bss_9E50.effects[0].file = (u32)files[ids[13]];
    actRelated(files[ids[12]], &lbl_3_bss_9E50.effects[0]);
    actorRelated(&lbl_3_bss_9E50.effects[0], 0, 0);
    fn_80035750(files[ids[15]], files[ids[14]], 5);
    lbl_3_bss_9E50.scene = (CastleGfxScene*)insertGraphicDrawingFunction(fn_3_C3C2C, 2);
    addGraphicsElementToScene((DrawingSceneStruct*)lbl_3_bss_9E50.scene, lbl_3_data_10C1C);

    stadiumObjectCollision.objectCount = 0x20;
    stadiumObjectCollision.objects = _OSAllocFromHeap(0x20, 0x1D00);
    memset(stadiumObjectCollision.objects, 0, 0x1D00);
    stadiumObjectCollision.objectsRelated = _OSAllocFromHeap(0x20, 0x1D00);
    memset(stadiumObjectCollision.objectsRelated, 0, 0x1D00);
    o = stadiumObjectCollision.objects;

    ((CastleHazardObj*)o)->hazardType = 0;
    o->model = (StadiumModel*)(*animTable + 0x34);
    o->triangles = NULL;
    o->callback = (void (*)(void))fn_3_C4068;
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
    o->fadeByDepth = 0;
    o->alpha = 0xFF;
    o->effect = NULL;
    o->preDraw = NULL;
    o->animActive = 0;
    o->animIndex = -1;
    o->drawPass = 0;
    o++;

    ((CastleHazardObj*)o)->hazardType = 1;
    o->model = (StadiumModel*)(*animTable + 0xC4);
    o->triangles = NULL;
    o->callback = (void (*)(void))fn_3_C3F70;
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
    o->fadeByDepth = 0;
    o->alpha = 0xFF;
    o->effect = (StadiumObjectEffect*)&lbl_3_bss_9E50.effects[0];
    o->preDraw = NULL;
    o->animActive = 0;
    o->animIndex = -1;
    o->drawPass = 1;
    o++;
    n = 2;

    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES) {
        done = FALSE;
        j = 0;
        thwompCfg = thwompStaticValues;
        lbl_3_bss_9DE5 = 0;
        lbl_3_bss_9DE4 = n;
        do {
            if (thwompCfg->usedFlag == 7) {
                done = TRUE;
            }
            if (done) {
                for (k = j; k < 11; k++) {
                    thwompStaticValues[k].usedFlag = 7;
                }
                break;
            }
            ((CastleHazardObj*)o)->_A8 = j;
            ((CastleHazardObj*)o)->hazardType = thwompCfg->usedFlag;
            o->model = (StadiumModel*)(*animTable + 0x154);
            o->triangles = files[ids[7]];
            o->callback = (void (*)(void))thwomp_slamControl;
            o->func = (int (*)(int, int, void*))thwomp_bounceOffSoundAndVisualFx;
            o->hasShadow = thwompCfg->visible;
            shadowBit = 0;
            if (o->hasShadow && o->triangles != NULL) {
                shadowBit = 1;
            }
            o->_90b1 = shadowBit;
            ((Control*)o)->type = 0;
            CTRLSetTranslation((Control*)o, thwompCfg->x, thwompCfg->y, thwompCfg->z);
            CTRLSetRotation((Control*)o, 0.0f, thwompCfg->rotation, 0.0f);
            j++;
            ((CastleThwompObj*)o)->pos.x = thwompCfg->x;
            n++;
            ((CastleThwompObj*)o)->pos.y = thwompCfg->y;
            ((CastleThwompObj*)o)->pos.z = thwompCfg->z;
            thwompCfg++;
            ((CastleThwompObj*)o)->fallSpeed = 0.0f;
            ((CastleThwompObj*)o)->state = THWOMP_PERCHED;
            ((CastleThwompObj*)o)->framesOnGround = 0;
            ((CastleThwompObj*)o)->checkForSlam = TRUE;
            o->fadeByDepth = 0;
            o->alpha = 0xFF;
            o->preDraw = fn_3_C7444;
            o->effect = NULL;
            o->animActive = 0;
            o->animIndex = -1;
            o->drawPass = 1;
            o->shadowEnabled = 1;
            o++;
            lbl_3_bss_9DE5++;
        } while (j < 10);

        done = FALSE;
        j = 0;
        fireCfg = BowserStadFireSpawners;
        lbl_3_bss_9DE3 = 0;
        lbl_3_bss_9DE2 = n;
        do {
            if (fireCfg->usedFlag == 7) {
                done = TRUE;
            }
            if (done) {
                for (k = j; k < 11; k++) {
                    BowserStadFireSpawners[k].usedFlag = 7;
                }
                break;
            }
            ((CastleHazardObj*)o)->_A8 = j;
            ((CastleHazardObj*)o)->hazardType = fireCfg->usedFlag;
            o->model = (StadiumModel*)(*animTable + (j + 3) * 0x90 + 0x34);
            o->triangles = NULL;
            o->callback = (void (*)(void))flameControl;
            o->func = NULL;
            o->hasShadow = fireCfg->visible;
            shadowBit = 0;
            if (o->hasShadow && o->triangles != NULL) {
                shadowBit = 1;
            }
            o->_90b1 = shadowBit;
            ((CastleFireObj*)o)->launchTimer = rng(240) + 1;
            ((CastleFireObj*)o)->state = FLAME_IDLE;
            ((CastleFireObj*)o)->velo.z = 0.0f;
            ((CastleFireObj*)o)->velo.y = 0.0f;
            ((CastleFireObj*)o)->velo.x = 0.0f;
            ((CastleFireObj*)o)->launchAngleBase = fireCfg->launchAngleBase;
            ((CastleFireObj*)o)->launchAngleSpread = fireCfg->launchAngleSpread;
            ((Control*)o)->type = 0;
            CTRLSetTranslation((Control*)o, fireCfg->x, fireCfg->y, fireCfg->z);
            CTRLSetRotation((Control*)o, 0.0f, fireCfg->rotation, 0.0f);
            j++;
            ((CastleFireObj*)o)->pos.x = fireCfg->x;
            n++;
            ((CastleFireObj*)o)->pos.y = fireCfg->y;
            ((CastleFireObj*)o)->pos.z = fireCfg->z;
            fireCfg++;
            o->fadeByDepth = 1;
            o->alpha = 0xFF;
            o->effect = (StadiumObjectEffect*)&lbl_3_bss_9E50.effects[1];
            o->preDraw = fn_3_C56E8;
            o->postDraw = fn_3_C54D0;
            o->animActive = 1;
            o->animIndex = 4;
            o->drawPass = 1;
            o->shadowEnabled = 1;
            o++;
            lbl_3_bss_9DE3++;
        } while (j < 10);

        lbl_3_bss_9D82 = 0;
        insertGraphicDrawingFunction(bowserCastleRelated, 0x6001);

        done = FALSE;
        j = 0;
        padCfg = lbl_3_data_17704.entries;
        lbl_3_bss_9DE1 = 0;
        lbl_3_bss_9DE0 = n;
        do {
            if (padCfg->usedFlag == 7) {
                done = TRUE;
            }
            if (done) {
                for (k = j; k < 11; k++) {
                    lbl_3_data_17704.entries[k].usedFlag = 7;
                }
                break;
            }
            ((CastleHazardObj*)o)->_A8 = j;
            ((CastleHazardObj*)o)->hazardType = padCfg->usedFlag;
            if (((CastleHazardObj*)o)->hazardType == 4) {
                o->model = (StadiumModel*)(*animTable + idx * 0x90 + 0x34);
                o->triangles = files[ids[8]];
            } else {
                o->model = (StadiumModel*)(*animTable + padAnim * 0x90 + 0x34);
                o->triangles = files[ids[9]];
            }
            o->callback = NULL;
            o->func = (int (*)(int, int, void*))bowserCastleStarPadsContaactFn;
            o->hasShadow = padCfg->visible;
            shadowBit = 0;
            if (o->hasShadow && o->triangles != NULL) {
                shadowBit = 1;
            }
            o->_90b1 = shadowBit;
            ((Control*)o)->type = 0;
            CTRLSetTranslation((Control*)o, padCfg->x, padCfg->y, padCfg->z);
            CTRLSetRotation((Control*)o, 0.0f, padCfg->rotation, 0.0f);
            o->fadeByDepth = 1;
            j++;
            o->alpha = 0xFF;
            padCfg++;
            n++;
            o->effect = NULL;
            o->preDraw = fn_3_C40EC;
            o->animActive = 0;
            o->animIndex = -1;
            o->drawPass = 1;
            o++;
            lbl_3_bss_9DE1++;
        } while (j < 10);
    }

    if (n < stadiumObjectCollision.objectCount) {
        for (k = n; k < stadiumObjectCollision.objectCount; k++) {
            ((CastleHazardObj*)o)->hazardType = 0;
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
        fn_3_C82B4();
    }
    fn_800528AC(thwomp_screenShake);
    for (i = 0; i < 6; i++) {
        emitter = allocParticleEffect(fn_3_C30F0, 0x80, 0, 0x15, TRUE, 0);
        if (emitter != NULL) {
            fn_3_C366C(emitter, i);
        }
    }
    fn_3_C1974((int)files[ids[0]]);
    fn_3_B97C8(fn_3_C2974);
}

