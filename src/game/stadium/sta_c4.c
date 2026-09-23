#include "game/stadium/sta_c4.h"
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
#include "C3/actor.h"
#include "stl/math.h"
#include "game/stadium/stadium_star.h"
#include "game/stadium/sta_c0.h"
#include "game/sound/m_sound.h"
#include "musyx/musyx.h"
#include "static/UnknownHomes_Static.h"
#include "text/text_channel.h"
#include "Unknown/File_0x800247e4.h"
#include "Unknown/File_0x80025c58.h"
#include "Unknown/File_0x80025ddc.h"
#include "Unknown/File_0x80033794.h"
#include "Unknown/File_0x80034cec.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x80039aa8.h"
#include "Unknown/File_0x80052734.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x800b4908.h"
#include "Unknown/File_0x800b4b38.h"
#include "Unknown/File_0x800b4bc8.h"
#include "Unknown/File_0x800bdc88.h"
#include "Unknown/File_0x800bdd74.h"

// The kinds of block the garden places; `variant` is the kind a block turns
// into when hit (a mystery block rolls one at load).
typedef enum _GARDEN_BLOCK_TYPE {
    GARDEN_BLOCK_BRICK = 0,
    GARDEN_BLOCK_USED = 1,
    GARDEN_BLOCK_NOTE = 2,
    GARDEN_BLOCK_MYSTERY = 3,
    GARDEN_BLOCK_SHADOW = 4,
    GARDEN_BLOCK_DEBRIS = 5,
    GARDEN_BLOCK_FOUNTAIN = 6,
    GARDEN_BLOCK_FOUNTAIN_FX = 7,
    GARDEN_BLOCK_RANDOM = 8,
} GARDEN_BLOCK_TYPE;

#define GARDEN_BLOCK_COUNT 52
#define GARDEN_DEBRIS_COUNT 9
#define GARDEN_HIT_FX_COUNT 6

typedef enum _HIT_FX_STATE {
    HIT_FX_IDLE,
    HIT_FX_START,
    HIT_FX_PLAYING,
} HIT_FX_STATE;

typedef struct _GardenSprayParticle {
    /*0x00*/ struct _GardenSprayParticle* next;
    /*0x04*/ Vec pos;
    /*0x10*/ Vec vel;
    /*0x1C*/ u8 _1C[0x38 - 0x1C];
    /*0x38*/ f32 sizeA;
    /*0x3C*/ f32 sizeB;
    /*0x40*/ u8 color[3];
    /*0x43*/ u8 alpha;
    /*0x44*/ u8 _44[4];
    /*0x48*/ s16 age;
    /*0x4A*/ s16 lifetime;
    /*0x4C*/ u8 _4C;
    /*0x4D*/ u8 _4D;
    /*0x4E*/ u8 _4E;
    /*0x4F*/ u8 index;
} GardenSprayParticle; // size: 0x50

typedef struct _GardenSprayEmitter {
    /*0x00*/ u8 _00[0x0C];
    /*0x0C*/ GardenSprayParticle* particles;
    /*0x10*/ u32 texture;
} GardenSprayEmitter;

// One entry of the block placement table.
typedef struct _GardenBlockPlacement {
    /*0x00*/ f32 x;
    /*0x04*/ f32 y;
    /*0x08*/ f32 z;
    /*0x0C*/ f32 rotation;
    /*0x10*/ E(u8, GARDEN_BLOCK_TYPE) type;
    /*0x11*/ u8 shown;
    /*0x12*/ u8 group;
    /*0x13*/ E(u8, GARDEN_BLOCK_TYPE) variant;
} GardenBlockPlacement; // size: 0x14

// Block view of a stadiumObjectCollision.objects[] entry.
typedef struct _GardenBlockObj {
    /*0x00*/ u8 _00[0x74];
    /*0x74*/ ACTActor* actor;
    /*0x78*/ u8 _78[0x9C - 0x78];
    /*0x9C*/ f32 debrisFrame;
    /*0xA0*/ u8 index;
    /*0xA1*/ E(u8, GARDEN_BLOCK_TYPE) type;
    /*0xA2*/ E(u8, GARDEN_BLOCK_TYPE) variant;
    /*0xA3*/ u8 frame;
} GardenBlockObj;

// The fountain object reuses variant/frame as its water-texture scroll state.
#define fountainScroll variant

// Material reached from the fountain's model; the low 13 bits of `flags`
// select the water texture's scroll row.
typedef struct _GardenMaterial {
    /*0x00*/ u8 _00[4];
    /*0x04*/ u32 flags;
} GardenMaterial;

typedef struct _GardenModelLevel4 {
    /*0x00*/ u8 _00[4];
    /*0x04*/ GardenMaterial* material;
} GardenModelLevel4;

typedef struct _GardenModelLevel3 {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ GardenModelLevel4* next;
} GardenModelLevel3;

typedef struct _GardenModelLevel2 {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ GardenModelLevel3* next;
} GardenModelLevel2;

typedef struct _GardenModelLevel1 {
    /*0x00*/ GardenModelLevel2* next;
} GardenModelLevel1;

typedef struct _GardenModelRoot {
    /*0x00*/ u8 _00[0x18];
    /*0x18*/ GardenModelLevel1* next;
} GardenModelRoot;

typedef struct _GardenAnimSeq {
    /*0x00*/ f32 length;
    /*0x04*/ u8 _04[0xC];
} GardenAnimSeq; // size: 0x10

typedef struct _GardenAnimBankData {
    /*0x00*/ u8 _00[4];
    /*0x04*/ GardenAnimSeq* seqs;
} GardenAnimBankData;

typedef struct _GardenAnimBank {
    /*0x00*/ u8 _00[4];
    /*0x04*/ GardenAnimBankData* data;
} GardenAnimBank;

// Drawing-script node that pushes a hit block along the ball's path.
typedef struct _GardenKnockNode {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ s16 state;
    /*0x12*/ u16 priority;
    /*0x14*/ Vec normal;
    /*0x20*/ Vec displacement;
    /*0x2C*/ s32 objIndex;
    /*0x30*/ u8 phase;
} GardenKnockNode;

// Drawing-script node that re-enables a hit block's depth fade after a delay.
typedef struct _GardenTimerNode {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ s16 timer;
    /*0x12*/ u16 priority;
    /*0x14*/ StadiumObject* obj;
} GardenTimerNode;

typedef struct _GardenHitFxScene {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ u16 firstHandle;
} GardenHitFxScene;

typedef struct _GardenGfxObject {
    /*0x00*/ u8 _00[0x48];
    /*0x48*/ Vec pos;
    /*0x54*/ u32 flags;
    /*0x58*/ u8 _58[4];
    /*0x5C*/ u32 frameIndex;
    /*0x60*/ u8 _60[9];
    /*0x69*/ u8 scale;
} GardenGfxObject;

typedef struct _GardenHit {
    /*0x00*/ Vec pos;
    /*0x0C*/ Vec normal;
} GardenHit;

typedef struct _GardenActEffect {
    /*0x00*/ u32 file;
    /*0x04*/ u8 _04[0x58];
} GardenActEffect; // size: 0x5C

typedef struct _GardenTexInfo {
    /*0x00*/ void* data;
    /*0x04*/ void* tlut;
    /*0x08*/ u16 height;
    /*0x0A*/ u16 width;
    /*0x0C*/ u8 wrapS;
    /*0x0D*/ u8 wrapT;
    /*0x0E*/ u8 minFilter;
    /*0x0F*/ u8 magFilter;
    /*0x10*/ f32 lodBias;
    /*0x14*/ u8 _14;
    /*0x15*/ u8 minLOD;
    /*0x16*/ u8 maxLOD;
    /*0x17*/ u8 format;
    /*0x18*/ u16 tlutEntries;
    /*0x1A*/ u8 tlutFormat;
} GardenTexInfo;

typedef struct _GardenView {
    /*0x00*/ u8 _00[0x38];
    /*0x38*/ Mtx mtx;
} GardenView;

typedef struct _GardenCrowdSeat {
    /*0x00*/ u8 type;
    /*0x01*/ u8 frame;
    /*0x02*/ u8 phase;
} GardenCrowdSeat;

typedef void (*GardenHitFn)(int idx, int arg1, void* hit);

// .data block the loader addresses as one table.
typedef struct _GardenData {
    /*0x000*/ GardenHitFn hitFns[4];
    /*0x010*/ GardenBlockPlacement blocks[50];
    /*0x3F8*/ u8 objTypes[0x11];
} GardenData;

extern u8 hugeAnimStruct[0x3154];
extern u16 stadiumHazardSoundIDs[16];
extern u8 stadiumHazardSoundFxRelated[0xB4];
extern u8 lbl_3_data_84B8[0x3C];
extern UIRecordDescriptor lbl_3_data_10E9C[];
extern u8 lbl_3_data_10F7C[];
extern u8 lbl_3_data_10F84[];
extern u8 lbl_3_data_10F88[];
extern u8 lbl_3_data_11008[];
extern GardenCrowdSeat lbl_3_data_110A8[32];
extern GardenCrowdSeat lbl_3_data_11138[16];
extern void fn_80035750(void* a, void* b, int c);
extern void fn_8003403C(f32 w, f32 h);
extern void fn_800528C0(f32 x, f32 y, f32 z, s16* outX, s16* outY);
extern void fn_800245EC(void* camera, MtxPtr m, Vec* src, f32* dst, int count, int arg5);
extern void fn_8003A144(void);
extern void fn_800A7D4C(s32 arg0, void* arg1);
extern u8 drawStadiumRelated;

typedef struct _GardenBlockTable {
    /*0x000*/ GardenBlockPlacement entries[50];
    /*0x3E8*/ u8 objTypes[0x11];
} GardenBlockTable; // size: 0x3FC

typedef struct _GardenCameraSlot {
    /*0x00*/ u32 _00;
    /*0x04*/ void (*draw)(void* view);
    /*0x08*/ u8 _08[0x30];
    /*0x38*/ Mtx mtx;
    /*0x68*/ u8 _68[4];
} GardenCameraSlot; // size: 0x6C

static GardenHitFn lbl_3_data_1BA88[4] = { fn_3_F9E78, fn_3_F99F0, fn_3_F976C, fn_3_F9B9C };

static GardenBlockTable blocks = {
    {
        { -12.0f, -12.0f, 55.0f, 350.0f, GARDEN_BLOCK_MYSTERY, 1, 1, GARDEN_BLOCK_RANDOM },
        { 12.0f, -12.0f, 55.0f, 10.0f, GARDEN_BLOCK_MYSTERY, 1, 1, GARDEN_BLOCK_RANDOM },
        { -20.0f, -9.0f, 73.0f, 350.0f, GARDEN_BLOCK_MYSTERY, 1, 1, GARDEN_BLOCK_RANDOM },
        { 20.0f, -9.0f, 73.0f, 10.0f, GARDEN_BLOCK_MYSTERY, 1, 1, GARDEN_BLOCK_RANDOM },
        { -25.0f, -9.0f, 45.0f, 320.0f, GARDEN_BLOCK_MYSTERY, 1, 2, GARDEN_BLOCK_RANDOM },
        { -51.0f, -9.0f, 65.0f, 315.0f, GARDEN_BLOCK_NOTE, 1, 2, GARDEN_BLOCK_RANDOM },
        { -39.0f, -10.0f, 52.0f, 315.0f, GARDEN_BLOCK_NOTE, 1, 3, GARDEN_BLOCK_RANDOM },
        { -30.0f, -12.0f, 62.0f, 325.0f, GARDEN_BLOCK_USED, 1, 3, GARDEN_BLOCK_RANDOM },
        { 25.0f, -9.0f, 45.0f, 40.0f, GARDEN_BLOCK_MYSTERY, 1, 4, GARDEN_BLOCK_RANDOM },
        { 51.0f, -9.0f, 65.0f, 45.0f, GARDEN_BLOCK_NOTE, 1, 4, GARDEN_BLOCK_RANDOM },
        { 39.0f, -10.0f, 52.0f, 45.0f, GARDEN_BLOCK_NOTE, 1, 5, GARDEN_BLOCK_RANDOM },
        { 30.0f, -12.0f, 62.0f, 35.0f, GARDEN_BLOCK_USED, 1, 5, GARDEN_BLOCK_RANDOM },
        { -29.0f, -9.0f, 26.0f, 265.0f, GARDEN_BLOCK_USED, 1, 6, GARDEN_BLOCK_RANDOM },
        { -39.0f, -10.0f, 36.0f, 265.0f, GARDEN_BLOCK_BRICK, 1, 6, GARDEN_BLOCK_RANDOM },
        { 29.0f, -9.0f, 26.0f, 85.0f, GARDEN_BLOCK_USED, 1, 7, GARDEN_BLOCK_RANDOM },
        { 39.0f, -10.0f, 36.0f, 85.0f, GARDEN_BLOCK_BRICK, 1, 7, GARDEN_BLOCK_RANDOM },
        { 0.0f, 0.0f, 0.0f, 0.0f, GARDEN_BLOCK_DEBRIS, 1, 9, GARDEN_BLOCK_RANDOM },
        { 0.0f, 0.0f, 0.0f, 0.0f, GARDEN_BLOCK_DEBRIS, 1, 9, GARDEN_BLOCK_RANDOM },
        { 0.0f, 0.0f, 0.0f, 0.0f, GARDEN_BLOCK_DEBRIS, 1, 9, GARDEN_BLOCK_RANDOM },
        { 0.0f, 0.0f, 0.0f, 0.0f, GARDEN_BLOCK_DEBRIS, 1, 9, GARDEN_BLOCK_RANDOM },
        { 0.0f, 0.0f, 0.0f, 0.0f, GARDEN_BLOCK_DEBRIS, 1, 9, GARDEN_BLOCK_RANDOM },
        { 0.0f, 0.0f, 0.0f, 0.0f, GARDEN_BLOCK_DEBRIS, 1, 9, GARDEN_BLOCK_RANDOM },
        { 0.0f, 0.0f, 0.0f, 0.0f, GARDEN_BLOCK_DEBRIS, 1, 9, GARDEN_BLOCK_RANDOM },
        { 0.0f, 0.0f, 0.0f, 0.0f, GARDEN_BLOCK_DEBRIS, 1, 9, GARDEN_BLOCK_RANDOM },
        { 0.0f, 0.0f, 0.0f, 0.0f, GARDEN_BLOCK_DEBRIS, 1, 9, GARDEN_BLOCK_RANDOM },
        { 0.0f, 0.0f, 0.0f, 0.0f, GARDEN_BLOCK_SHADOW, 1, 9, GARDEN_BLOCK_RANDOM },
    },
    { 1, 2, 4, 2, 2, 2, 2, 2, 2, 6, 6, 6, 6, 8, 9, 0, 0 },
};

static GardenCameraSlot lbl_3_data_1BE94[2] = {
    { 2, fn_3_FB3D8 },
    { 2, fn_3_FB3D8 },
};

static Vec lbl_3_data_1BF6C[21] = {
    { 1.2209f, -0.1f, 67.7082f },
    { -1.2209f, -0.1f, 67.7082f },
    { -3.5431f, -0.1f, 66.9536f },
    { -5.5184f, -0.1f, 65.5184f },
    { -6.9536f, -0.1f, 63.5431f },
    { -7.7082f, -0.1f, 61.2209f },
    { -7.7082f, -0.1f, 58.7791f },
    { -6.9536f, -0.1f, 56.4569f },
    { -5.5184f, -0.1f, 54.4816f },
    { -3.5431f, -0.1f, 53.0464f },
    { -1.2209f, -0.1f, 52.2918f },
    { 1.2209f, -0.1f, 52.2918f },
    { 3.5431f, -0.1f, 53.0464f },
    { 5.5184f, -0.1f, 54.4816f },
    { 6.9536f, -0.1f, 56.4569f },
    { 7.7082f, -0.1f, 58.7791f },
    { 7.7082f, -0.1f, 61.2209f },
    { 6.9536f, -0.1f, 63.5431f },
    { 5.5184f, -0.1f, 65.5184f },
    { 3.5431f, -0.1f, 66.9536f },
    { 0.0f, -0.1f, 60.0f },
};

static u8 lbl_3_data_1C068[20][3] = {
    { 0x14, 0x13, 0 },
    { 0x14, 1, 2 },
    { 0x14, 0x10, 0x11 },
    { 0x14, 0xC, 0xD },
    { 0x14, 5, 6 },
    { 0x14, 0x12, 0x13 },
    { 0x14, 3, 4 },
    { 0x14, 0xE, 0xF },
    { 0x14, 0xA, 0xB },
    { 0x14, 7, 8 },
    { 0x14, 0x11, 0x12 },
    { 0x14, 8, 9 },
    { 0x14, 2, 3 },
    { 0x14, 0xB, 0xC },
    { 0x14, 0, 1 },
    { 0x14, 9, 0xA },
    { 0x14, 0xF, 0x10 },
    { 0x14, 6, 7 },
    { 0x14, 4, 5 },
    { 0x14, 0xD, 0xE },
};

#define GARDEN_ANIM_TABLE (*(u8**)(hugeAnimStruct + 0x6C))

static const Vec sprayOrigin = {0.0f, 0.5f, 60.0f};

static u8 emitterPaused;
static u32 sprayTexture;
static GXTexObj noiseTexObj;
static u8* noiseTex;
static u8 debrisSlots[GARDEN_DEBRIS_COUNT];
static u16 nBlockObj;
static GardenHitFxScene* hitFxScene;
static E(u8, HIT_FX_STATE) hitFxState[GARDEN_HIT_FX_COUNT];
static Vec hitFxPos[GARDEN_HIT_FX_COUNT];
static u8 hitFxTeardown;
static GardenActEffect fountainEffect;
static int emitterID;
static u8 lbl_3_bss_B570;

static inline void gardenActSetFrame(ACTActor* act, f32 frame) {
    act->animFrame = frame;
    act->applyFrame = 1;
}

static inline void gardenActSetSpeed(ACTActor* act, f32 speed) {
    act->animSpeed = speed;
    act->applySpeed = 1;
}

// .text:0x000F8444 size:0x10 mapped:0x807374D8
void fn_3_F8444(void) {
    hitFxTeardown = TRUE;
}

// .text:0x000F8454 size:0xD0 mapped:0x807374E8
void fn_3_F8454(void) {
    if (g_GameLogic.gameStatus == GAME_STATUS_PAUSED) {
        if (!emitterPaused) {
            updateAndRemoveStadiumEmitter(emitterID);
            emitterPaused = TRUE;
        }
    } else if (emitterPaused) {
        emitterID = initializeStadiumObjectEmitter(stadiumHazardSoundIDs[g_d_GameSettings.StadiumID] + 3, NULL, NULL, 2);
        emitterPaused = FALSE;
    } else {
        updateOrRemoveEmitter(emitterID, NULL, NULL);
    }
}

// .text:0x000F8524 size:0x8C mapped:0x807375B8
void fn_3_F8524(GardenSprayParticle* p) {
    if (p->index < 42) {
        p->vel.y = 0.123f;
        p->pos.x = sprayOrigin.x;
        p->pos.y = sprayOrigin.y - 2.0;
        p->pos.z = sprayOrigin.z;
        p->sizeA = 0.75f;
        p->sizeB = 4.0f;
    }
    p->color[2] = 0xFF;
    p->color[1] = 0xFF;
    p->color[0] = 0xFF;
    p->alpha = 0xFF;
    p->lifetime = 0x80;
    p->age = 0;
}

// .text:0x000F85B0 size:0x2C8 mapped:0x80737644
BOOL fn_3_F85B0(GardenSprayEmitter* emitter) {
    GardenSprayParticle* p = emitter->particles;

    if (g_GameLogic.gameStatus >= GAME_STATUS_0x1B && g_GameLogic.gameStatus <= GAME_STATUS_MINIGAME_READY) {
        return FALSE;
    }
    fn_80033620(emitter);
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    do {
        if (p->age <= 0 && p->lifetime != 0) {
            fn_8003403C(p->sizeA, p->sizeB);
            fn_80033CC8(p, emitter->texture);
            if (-p->age < 64) {
                p->alpha += -2.390625;
                p->sizeA += 0.05078125;
            } else {
                p->sizeA += 0.046875;
                p->alpha += -1.59375f;
                if (p->alpha > 102.0) {
                    p->alpha = 0;
                }
            }
            p->pos.x += p->vel.x;
            p->pos.y -= p->vel.y;
            p->pos.z += p->vel.z;
            p->vel.y -= 0.003;
            p->lifetime--;
        }
        p->age--;
        if (p->lifetime == 0) {
            fn_3_F8524(p);
        }
        p = p->next;
    } while (p != NULL);
    return FALSE;
}

// .text:0x000F8878 size:0x244 mapped:0x8073790C
void fn_3_F8878(GardenSprayEmitter* emitter) {
    s16 delay = 0;
    GardenSprayParticle* p = emitter->particles;
    u32 i = 0;
    f32 angle;
    f32 rad;

    emitter->texture = sprayTexture;
    for (; p != NULL; p = p->next) {
        p->vel.y = 0.123f;
        if ((i & 1) == 0) {
            angle = (i % 6) * 60;
            if (((i / 6) & 1) == 1) {
                angle += 30.0f;
            }
        } else {
            angle = 180.0f + angle;
        }
        rad = 0.017453292f * angle;
        p->vel.x = 0.05 * (f32)cos(rad);
        p->vel.z = 0.05 * (f32)sin(rad);
        p->age = delay;
        delay += 3;
        p->index = i;
        i++;
        p->pos.x = sprayOrigin.x;
        p->pos.y = sprayOrigin.y - 2.0;
        p->pos.z = sprayOrigin.z;
        p->sizeA = 0.75f;
        p->sizeB = 4.0f;
        p->color[2] = 0xFF;
        p->color[1] = 0xFF;
        p->color[0] = 0xFF;
        p->alpha = 0xFF;
        p->lifetime = 0x80;
        p->_4D = 0x1B;
        p->_4E = 0;
    }
}

// .text:0x000F8ABC size:0x48 mapped:0x80737B50
void peachGardenSomething(void) {
    GardenSprayEmitter* emitter = allocParticleEffect((void*)fn_3_F85B0, 0xF0, 0xD, 0x2A, 1, 0x7F);

    if (emitter != NULL) {
        fn_3_F8878(emitter);
    }
}

// .text:0x000F8B04 size:0x2C mapped:0x80737B98
void fn_3_F8B04(void) {
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
}

// .text:0x000F8B30 size:0x4 mapped:0x80737BC4
void fn_3_F8B30(void) {
    return;
}

// .text:0x000F8B34 size:0x74 mapped:0x80737BC8
void fn_3_F8B34(void) {
    fn_3_B9510(0);
    GXLoadTexObj(&noiseTexObj, GX_TEXMAP7);
    GXSetIndTexOrder(GX_IND_TEX_STAGE_0, GX_TEXCOORD0, GX_TEXMAP7);
    GXSetNumIndStages(1);
    GXSetIndTexCoordScale(GX_IND_TEX_STAGE_0, GX_ITS_1, GX_ITS_1);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_IND_TEX_STAGE_0, GX_DISABLE, GX_DISABLE, GX_ITM_0);
}

// .text:0x000F8BA8 size:0x158 mapped:0x80737C3C
void fn_3_F8BA8(GardenBlockObj* obj) {
    u8 frame = obj->frame;
    GardenMaterial* mat =
        ((GardenModelRoot*)((StadiumModel*)obj->actor)->root)->next->next->next->next->material;
    u32 x;
    u32 y;
    int offset;
    s8 prev;
    s8 cur;

    if (frame != 0 && frame % 3 == 0) {
        obj->fountainScroll++;
        if (obj->fountainScroll > 25) {
            obj->fountainScroll = 10;
            obj->frame = 0;
        }
        mat->flags &= ~0x1FFF;
        mat->flags |= obj->fountainScroll;
        for (x = 0; x < 128; x++) {
            for (y = 0; y < 128; y++) {
                if (y == 0) {
                    prev = noiseTex[fn_800247E4(x, 127, 128, 2)];
                }
                offset = fn_800247E4(x, y, 128, 2);
                cur = noiseTex[offset];
                noiseTex[offset] = prev;
                prev = cur;
            }
        }
        DCFlushRange(noiseTex, 128 * 128 * 2);
    }
    obj->frame++;
}

// .text:0x000F8D00 size:0x120 mapped:0x80737D94
void fn_3_F8D00(void) {
    f32 m[2][3];
    u32 x;
    u32 y;
    int offset;

    m[0][0] = 0.5f;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[1][0] = 0.0f;
    m[1][1] = 0.5f;
    m[1][2] = 0.0f;
    GXSetIndTexMtx(GX_ITM_0, m, 2);
    noiseTex = fn_3_B9534(128, 128, &noiseTexObj);
    if (noiseTex == NULL) {
        OSPanic("sta_c4.c", 0x6DF, "error\n");
    }
    for (y = 0; y < 128; y++) {
        for (x = 0; x < 128; x++) {
            offset = fn_800247E4(x, y, 128, 2);
            noiseTex[offset] = (u8)(rand() % 4) + 0x7E;
        }
    }
}

// .text:0x000F8E20 size:0x268 mapped:0x80737EB4
void fn_3_F8E20(void) {
    E(u8, HIT_FX_STATE)* state = hitFxState;
    Vec* v = hitFxPos;
    GardenHitFxScene* item = (GardenHitFxScene*)currentDrawingItem;
    int i;

    for (i = 0; i < GARDEN_HIT_FX_COUNT; i++, state++, v++) {
        switch (*state) {
        case HIT_FX_START: {
            s16 sy;
            s16 sx;

            fn_800528C0(v->x, v->y, v->z, &sx, &sy);
            ((GardenGfxObject*)graphicsRelatedArray[hitFxScene->firstHandle + i].object)->pos.x = sx;
            ((GardenGfxObject*)graphicsRelatedArray[hitFxScene->firstHandle + i].object)->pos.y = sy;
            ((GardenGfxObject*)graphicsRelatedArray[hitFxScene->firstHandle + i].object)->pos.z = 0.0f;
            ((GardenGfxObject*)graphicsRelatedArray[item->firstHandle + i].object)->frameIndex = 0;
            ((GardenGfxObject*)graphicsRelatedArray[item->firstHandle + i].object)->flags |= 2;
            *state = HIT_FX_PLAYING;
            break;
        }
        case HIT_FX_PLAYING: {
            s16 sy;
            s16 sx;

            fn_800528C0(v->x, v->y, v->z, &sx, &sy);
            ((GardenGfxObject*)graphicsRelatedArray[hitFxScene->firstHandle + i].object)->pos.x = sx;
            ((GardenGfxObject*)graphicsRelatedArray[hitFxScene->firstHandle + i].object)->pos.y = sy;
            ((GardenGfxObject*)graphicsRelatedArray[hitFxScene->firstHandle + i].object)->pos.z = 0.0f;
            if (((GardenGfxObject*)graphicsRelatedArray[item->firstHandle + i].object)->scale == 2) {
                ((GardenGfxObject*)graphicsRelatedArray[item->firstHandle + i].object)->flags &= ~2;
                *state = HIT_FX_IDLE;
            }
            break;
        }
        }
    }
    if (hitFxTeardown) {
        removeCurrentDrawingItem();
        removeGraphicsElementFromScene((DrawingSceneStruct*)hitFxScene);
        hitFxTeardown = FALSE;
    }
}

// .text:0x000F9088 size:0xDC mapped:0x8073811C
void fn_3_F9088(Vec* p, int idx) {
    s16 sx;
    s16 sy;

    fn_800528C0(p->x, p->y, p->z, &sx, &sy);
    ((GardenGfxObject*)graphicsRelatedArray[hitFxScene->firstHandle + idx].object)->pos.x = sx;
    ((GardenGfxObject*)graphicsRelatedArray[hitFxScene->firstHandle + idx].object)->pos.y = sy;
    ((GardenGfxObject*)graphicsRelatedArray[hitFxScene->firstHandle + idx].object)->pos.z = 0.0f;
}

// .text:0x000F9164 size:0x198 mapped:0x807381F8
void fn_3_F9164(GardenBlockObj* obj) {
    int stadiumID;
    u32 slot;
    int sfx;
    SND_VOICEID voice;

    switch (obj->variant) {
    case GARDEN_BLOCK_BRICK:
        sfx = 2;
        slot = g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy;
        break;
    case GARDEN_BLOCK_USED:
        sfx = 1;
        slot = g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy + 2;
        break;
    case GARDEN_BLOCK_NOTE:
        sfx = 0;
        slot = g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy + 4;
        break;
    }
    stadiumID = g_d_GameSettings.StadiumID;
    voice = sndFXStartEx(stadiumHazardSoundIDs[stadiumID] + sfx,
                         g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                             ? lbl_3_data_84B8[sfx * 2]
                             : stadiumHazardSoundFxRelated[stadiumID * 0x1E + sfx * 2],
                         0x3F, 0);
    sndFXCtrl(voice, 0x5B,
              g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                  ? lbl_3_data_84B8[sfx * 2 + 1]
                  : stadiumHazardSoundFxRelated[stadiumID * 0x1E + sfx * 2 + 1]);
    hitFxState[slot] = HIT_FX_START;
    hitFxPos[slot].x = g_Ball.AtBat_Contact_BallPos.x;
    hitFxPos[slot].y = -g_Ball.AtBat_Contact_BallPos.y;
    hitFxPos[slot].z = g_Ball.AtBat_Contact_BallPos.z;
}

// .text:0x000F92FC size:0x50 mapped:0x80738390
void fn_3_F92FC(void) {
    GardenTimerNode* node = (GardenTimerNode*)currentDrawingItem;

    if (node->timer-- == 0) {
        node->obj->fadeByDepth = 1;
        removeCurrentDrawingItem();
    }
}

// .text:0x000F934C size:0x2F0 mapped:0x807383E0
void fn_3_F934C(void) {
    GardenKnockNode* node = (GardenKnockNode*)currentDrawingItem;
    Vec* vel = &stadiumObjectCollision.hitBallVel;
    Vec* pos = &stadiumObjectCollision.hitBallPos;
    Vec tmp;
    Vec disp;
    f32 mag;
    f32 speed;
    int shadow;

    memcpy(&tmp, vel, sizeof(Vec));
    PSVECScale(&node->normal, PSVECDotProduct(&node->normal, &tmp), &tmp);
    PSVECAdd(&node->displacement, &tmp, &disp);
    mag = PSVECMag(&disp);
    PSVECAdd(pos, vel, &tmp);
    if (node->phase != 0) {
        speed = PSVECMag(vel) + 0.1f * mag;
    } else {
        speed = PSVECMag(vel) - 0.1f * mag;
    }
    memcpy(&node->displacement, &disp, sizeof(Vec));
    memcpy(pos, &tmp, sizeof(Vec));
    if (node->phase != 0 &&
        (fabs(PSVECMag(&disp)) <= 1e-6 || !(node->normal.x * disp.x < 0.0f || node->normal.y * disp.y < 0.0f ||
                                             node->normal.z * disp.z < 0.0f))) {
        memset(&node->displacement, 0, sizeof(Vec));
        stadiumObjectCollision.hazardHitActive = FALSE;
        removeCurrentDrawingItem();
    } else if (speed <= 0.0f) {
        node->phase = 1;
        PSVECScale(&node->normal, -1.0f, &node->normal);
        PSVECScale(&node->normal, 0.1f * mag, vel);
    } else {
        PSVECNormalize(vel, &tmp);
        PSVECScale(&tmp, speed, vel);
    }
    CTRLSetTranslation((Control*)&stadiumObjectCollision.objects[node->objIndex],
                       node->displacement.x + blocks.entries[node->objIndex].x,
                       node->displacement.y + blocks.entries[node->objIndex].y,
                       node->displacement.z + blocks.entries[node->objIndex].z);
    shadow = (u16)(nBlockObj + 9);
    shadow = node->objIndex + shadow;
    CTRLGetTranslation((Control*)&stadiumObjectCollision.objects[shadow], &tmp.x, &tmp.y, &tmp.z);
    CTRLSetTranslation((Control*)&stadiumObjectCollision.objects[shadow],
                       node->displacement.x + blocks.entries[node->objIndex].x, tmp.y,
                       node->displacement.z + blocks.entries[node->objIndex].z);
}

// .text:0x000F963C size:0x130 mapped:0x807386D0
void fn_3_F963C(int idx, void* hit) {
    GardenKnockNode* node;

    stadiumObjectCollision.hazardHitActive = TRUE;
    node = (GardenKnockNode*)insertGraphicDrawingFunction(fn_3_F934C, (u16)(currentDrawingItem->priority + 1));
    memcpy(&stadiumObjectCollision.hitBallPos, &g_Ball, sizeof(Vec));
    memcpy(&stadiumObjectCollision.hitBallVel, &g_Ball.physicsSubstruct.velocity, sizeof(Vec));
    stadiumObjectCollision.hitBallPos.y = -stadiumObjectCollision.hitBallPos.y;
    stadiumObjectCollision.hitBallVel.y = -stadiumObjectCollision.hitBallVel.y;
    if (hit != NULL) {
        PSVECScale(&((GardenHit*)hit)->normal, -1.0f, &node->normal);
    }
    memset(&node->displacement, 0, sizeof(Vec));
    node->objIndex = idx;
    node->phase = 0;
    stadiumObjectCollision.objects[node->objIndex]._90b1 = 0;
}

// .text:0x000F976C size:0x284 mapped:0x80738800
void fn_3_F976C(int idx, int arg1, void* hit) {
    fn_3_F9164((GardenBlockObj*)&stadiumObjectCollision.objects[idx]);
    fn_3_F963C(idx, hit);
}

// .text:0x000F99F0 size:0x1AC mapped:0x80738A84
void fn_3_F99F0(int idx, int arg1, void* hit) {
    fn_3_F9164((GardenBlockObj*)&stadiumObjectCollision.objects[idx]);
}

// .text:0x000F9B9C size:0x1F8 mapped:0x80738C30
void fn_3_F9B9C(int idx, int arg1, void* hit) {
    StadiumObject* o = &stadiumObjectCollision.objects[idx];
    GardenTimerNode* node;
    int shadowBit;

    ((GardenBlockObj*)o)->type = ((GardenBlockObj*)o)->variant;
    if (((GardenBlockObj*)o)->type == GARDEN_BLOCK_BRICK) {
        fn_3_F9E78(idx, arg1, hit);
    } else {
        if (((GardenBlockObj*)o)->type == GARDEN_BLOCK_NOTE) {
            fn_3_F963C(idx, hit);
        }
        o->model = (StadiumModel*)(GARDEN_ANIM_TABLE + ((GardenBlockObj*)o)->variant * 0x90 + 0x34);
        o->func = (int (*)(int, int, void*))lbl_3_data_1BA88[((GardenBlockObj*)o)->variant];
        shadowBit = 0;
        if (o->hasShadow && o->triangles != NULL) {
            shadowBit = 1;
        }
        o->_90b1 = shadowBit;
        o->func(idx, arg1, hit);
        o->fadeByDepth = 0;
        node = (GardenTimerNode*)insertGraphicDrawingFunction(fn_3_F92FC, 0);
        node->timer = 90;
        node->obj = o;
    }
}

// .text:0x000F9D94 size:0xE4 mapped:0x80738E28
void fn_3_F9D94(GardenBlockObj* obj) {
    StadiumObject* o = (StadiumObject*)obj;
    ACTActor* act = obj->actor;
    int i;

    if (obj->debrisFrame >= ((GardenAnimBank*)act->animBank)->data->seqs[act->sequenceNum].length) {
        o->hasShadow = 0;
        o->model = NULL;
        o->triangles = NULL;
        o->callback = NULL;
        o->func = NULL;
        o->_90b1 = 0;
        for (i = 0; i < GARDEN_DEBRIS_COUNT; i++) {
            if (debrisSlots[i] == obj->index) {
                debrisSlots[i] = 0xFF;
                return;
            }
        }
    } else {
        AnimateActorBones(act->actor);
        obj->debrisFrame += 1.0f;
    }
}

// .text:0x000F9E78 size:0x548 mapped:0x80738F0C
void fn_3_F9E78(int idx, int arg1, void* hit) {
    StadiumObject* o = &stadiumObjectCollision.objects[idx];
    int i;
    StadiumObject* d;
    ACTActor* act;
    GardenTimerNode* node;
    Vec pos;
    int shadowBit;

    fn_3_F9164((GardenBlockObj*)o);
    if (((GardenBlockObj*)o)->variant == GARDEN_BLOCK_BRICK) {
        for (i = 0; i < GARDEN_DEBRIS_COUNT; i++) {
            if (debrisSlots[i] == 0xFF) {
                d = &stadiumObjectCollision.objects[nBlockObj + i];
                d->model = (StadiumModel*)(GARDEN_ANIM_TABLE + (i + 5) * 0x90 + 0x34);
                d->triangles = NULL;
                d->callback = (void (*)(void))fn_3_F9D94;
                d->func = NULL;
                d->_90b1 = 0;
                d->hasShadow = 1;
                ((ACTActor*)d->model)->applyFlags = 2;
                gardenActSetFrame((ACTActor*)d->model, 0.0f);
                gardenActSetSpeed((ACTActor*)d->model, 1.0f);
                ((ACTActor*)d->model)->_68 = 0;
                act = (ACTActor*)d->model;
                ACTSetAnimation(act->actor, act->animBank, NULL, act->sequenceNum, 0.0f, act->animTime);
                setActorAnimFrame(act->actor, act->animFrame);
                fn_800B4C04(act->actor, act->animSpeed);
                updateBoneParam(act->actor, act->applyFlags & 1);
                ((GardenBlockObj*)d)->debrisFrame = 0.0f;
                ((Control*)d)->type = 0;
                CTRLSetTranslation((Control*)d, blocks.entries[idx].x, blocks.entries[idx].y, blocks.entries[idx].z);
                CTRLSetRotation((Control*)d, 0.0f, blocks.entries[idx].rotation, 0.0f);
                debrisSlots[i] = ((GardenBlockObj*)d)->index;
                break;
            }
        }
        o = &stadiumObjectCollision.objects[idx];
        o->model = NULL;
        o->triangles = NULL;
        o->callback = NULL;
        o->func = NULL;
        o->hasShadow = 0;
        o->_90b1 = 0;
        if (inningSetting.starSkillsSetting) {
            CTRLGetTranslation((Control*)o, &pos.x, &pos.y, &pos.z);
            stadiumStarAwarded(pos.x, pos.y, pos.z);
        }
        stadiumObjectCollision.objects[idx + nBlockObj + 9].hasShadow = 0;
    } else {
        if (((GardenBlockObj*)o)->variant == GARDEN_BLOCK_NOTE) {
            fn_3_F963C(idx, hit);
        }
        o->model = (StadiumModel*)(GARDEN_ANIM_TABLE + ((GardenBlockObj*)o)->variant * 0x90 + 0x34);
        o->func = (int (*)(int, int, void*))lbl_3_data_1BA88[((GardenBlockObj*)o)->variant];
        shadowBit = 0;
        if (o->hasShadow && o->triangles != NULL) {
            shadowBit = 1;
        }
        o->_90b1 = shadowBit;
        o->fadeByDepth = 0;
        node = (GardenTimerNode*)insertGraphicDrawingFunction(fn_3_F92FC, 0);
        node->timer = 90;
        node->obj = o;
    }
}

// .text:0x000FA3C0 size:0x1CC mapped:0x80739454
void fn_3_FA3C0(void) {
    GardenBlockPlacement* cfg;
    StadiumObject* obj;
    Mtx m;
    u32 size = stadiumObjectCollision.objectCount * sizeof(s32) +
               stadiumObjectCollision.objectCount * sizeof(u16) +
               stadiumObjectCollision.objectCount * sizeof(f32) +
               stadiumObjectCollision.objectCount * sizeof(VecSrcDst);
    int group;
    int j;
    s32 count;
    int off;

    if (stadiumObjectCollision.vertexDataArray == NULL) {
        stadiumObjectCollision.vertexDataArray = (VecSrcDst*)_OSAllocFromHeap(4, size);
        stadiumObjectCollision.hazardData = (s32*)(stadiumObjectCollision.vertexDataArray + stadiumObjectCollision.objectCount);
        stadiumObjectCollision.vertexData = (f32*)(stadiumObjectCollision.hazardData + stadiumObjectCollision.objectCount);
        stadiumObjectCollision.vertexOffsets = (u16*)(stadiumObjectCollision.vertexData + stadiumObjectCollision.objectCount);
    }
    memset(stadiumObjectCollision.vertexDataArray, 0, size);
    count = 0;
    for (group = 0; group < 10; group++) {
        off = (u16)(stadiumObjectCollision.vertexOffsets[count - 1] + stadiumObjectCollision.hazardData[count - 1]);
        stadiumObjectCollision.vertexOffsets[count] = off;
        initBoundingBoxLimits();
        cfg = blocks.entries;
        for (j = 0; j < stadiumObjectCollision.objectCount; cfg++, j++) {
            if (group == cfg->group && stadiumObjectCollision.objects[j]._90b1) {
                ((s32*)stadiumObjectCollision.vertexData)[off] = j;
                off++;
                stadiumObjectCollision.hazardData[count]++;
                obj = &stadiumObjectCollision.objects[j];
                CTRLBuildMatrix((Control*)obj, m);
                transformVectorsUpdateBoundingBox(m, (StadiumMeshData*)obj->triangles);
            }
        }
        if ((u32)stadiumObjectCollision.hazardData[count] != 0) {
            storeBoundingBoxCoordinates(&((Vec*)stadiumObjectCollision.vertexDataArray)[count * 2],
                                        &((Vec*)stadiumObjectCollision.vertexDataArray)[count * 2 + 1]);
            count++;
        }
    }
    stadiumObjectCollision.boundingBoxCount = count;
}

// .text:0x000FA58C size:0xE4C mapped:0x80739620
void loadPeachGarden(void** files) {
    GardenData* data = (GardenData*)lbl_3_data_1BA88;
    GardenBlockPlacement* cfg;
    GardenBlockObj* b;
    StadiumCrowdWave* wave;
    GardenCrowdSeat* seat;
    StadiumObject* o;
    StadiumObject* f;
    u32* ids;
    u8* slot;
    u32 size;
    int shadowsDone;
    int fountainIdx = 0;
    int shadowBit;
    int i;
    int k;

    stadiumObjectCollision.preUpdateFunc = g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES ? NULL : fn_3_FBCD0;
    stadiumObjectCollision.updateFunc = fn_3_F8454;
    emitterPaused = TRUE;
    ids = stadiumObjectCollision._34 = _OSAllocFromHeap(4, 0x44);
    processStadiumFileObjects(data->objTypes, 0x11, (u8*)files, ids);
    sprayTexture = (u32)files[0];
    fn_80035750(files[ids[16]], files[ids[15]], 5);
    hitFxScene = (GardenHitFxScene*)insertGraphicDrawingFunction(fn_3_F8E20, 2);
    addGraphicsElementToScene((DrawingSceneStruct*)hitFxScene, lbl_3_data_10E9C);

    GARDEN_ANIM_TABLE = ActorObjectInitTable(0x10);
    animateBallRelated(GARDEN_ANIM_TABLE, 0, 0, files[ids[1]], 0, 0);
    animateBallRelated(GARDEN_ANIM_TABLE, 1, 1, files[ids[3]], 0, 0);
    animateBallRelated(GARDEN_ANIM_TABLE, 2, 2, files[ids[4]], 0, 0);
    animateBallRelated(GARDEN_ANIM_TABLE, 3, 3, files[ids[5]], 0, 0);
    animateBallRelated(GARDEN_ANIM_TABLE, 4, 4, files[ids[6]], 0, 0);
    for (i = 0; i < GARDEN_DEBRIS_COUNT; i++) {
        animateBallRelated(GARDEN_ANIM_TABLE, i + 5, i + 5, files[ids[2]], (int)files[ids[2] + 2], 0);
        actorSetAnimBank((ACTActor*)(GARDEN_ANIM_TABLE + (i + 5) * 0x90 + 0x34), (u32)files[ids[2] + 2]);
        (GARDEN_ANIM_TABLE)[i * 0x90 + 0x35C] = 0;
    }
    animateBallRelated(GARDEN_ANIM_TABLE, 14, 14, files[ids[7]], 0, 0);
    animateBallRelated(GARDEN_ANIM_TABLE, 15, 15, files[ids[8]], 0, 0);
    stadiumObjectCollision.propCount = 0x10;
    for (i = 0; i < 0x10; i++) {
        fn_800BD548(GARDEN_ANIM_TABLE + i * 0x90 + 0x34, 4, stadiumObjectCollision.lights[0],
                    stadiumObjectCollision.lights[1], stadiumObjectCollision.lights[2],
                    stadiumObjectCollision.lights[3]);
    }
    if (files[ids[13]] != NULL) {
        adjustInternalPointers(files[ids[13]]);
        ACTActorRelated(files[ids[13]], GARDEN_ANIM_TABLE + 0x8A4);
        fountainEffect.file = (u32)files[ids[14]];
        actRelated(files[ids[13]], &fountainEffect);
        actorRelated(&fountainEffect, 0, 0);
    }

    stadiumObjectCollision.objectCount = GARDEN_BLOCK_COUNT;
    size = (g_d_GameSettings.miniGameStadiumIndicator == 0 ? 0xEC : 0) + GARDEN_BLOCK_COUNT * sizeof(StadiumObject);
    stadiumObjectCollision.objects = _OSAllocFromHeap(0x20, size);
    memset(stadiumObjectCollision.objects, 0, size);
    stadiumObjectCollision.objectsRelated = _OSAllocFromHeap(0x20, size);
    memset(stadiumObjectCollision.objectsRelated, 0, size);
    if (g_d_GameSettings.miniGameStadiumIndicator == 0) {
        stadiumObjectCollision.crowd = (StadiumCrowdAnim*)(stadiumObjectCollision.objectsRelated + GARDEN_BLOCK_COUNT);
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
    b = (GardenBlockObj*)o;
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES) {
        slot = debrisSlots;
        shadowsDone = FALSE;
        nBlockObj = 0xFFFF;
        for (i = 0; i < GARDEN_BLOCK_COUNT; i++, o++, b = (GardenBlockObj*)o) {
            cfg = &data->blocks[i];
            b->index = i;
            if (cfg->type == GARDEN_BLOCK_DEBRIS) {
                b->type = cfg->type;
                if (nBlockObj == 0xFFFF) {
                    nBlockObj = i;
                }
                *slot++ = 0xFF;
                o->model = (StadiumModel*)(GARDEN_ANIM_TABLE + (i + 5) * 0x90 + 0x34);
                o->triangles = NULL;
                o->callback = NULL;
                o->func = NULL;
                o->hasShadow = 0;
                o->_90b1 = 0;
                o->fadeByDepth = 0;
                ((Control*)o)->type = 0;
            } else if (shadowsDone) {
                b->type = 0;
                b->variant = 0;
                o->model = (StadiumModel*)(GARDEN_ANIM_TABLE + 0x34);
                o->triangles = files[ids[9]];
                o->callback = NULL;
                o->func = NULL;
                o->hasShadow = 0;
                o->_90b1 = 0;
                o->fadeByDepth = 1;
                ((Control*)o)->type = 0;
                CTRLSetTranslation((Control*)o, 0.0f, 0.0f, 0.0f);
                CTRLSetRotation((Control*)o, 0.0f, 0.0f, 0.0f);
            } else if (shadowsDone = (cfg->type == GARDEN_BLOCK_SHADOW)) {
                cfg = data->blocks;
                for (k = 0; k < nBlockObj; k++) {
                    b->type = 0;
                    b->variant = 0;
                    o->model = (StadiumModel*)(GARDEN_ANIM_TABLE + 0x274);
                    o->triangles = NULL;
                    o->callback = NULL;
                    o->func = NULL;
                    o->hasShadow = cfg->shown;
                    o->_90b1 = 0;
                    ((Control*)o)->type = 0;
                    CTRLSetTranslation((Control*)o, cfg->x, -0.02f, cfg->z);
                    CTRLSetRotation((Control*)o, 0.0f, cfg->rotation, 0.0f);
                    o->alpha = 0xFF;
                    cfg++;
                    i++;
                    o->fadeByDepth = 0;
                    o->preDraw = NULL;
                    o->effect = NULL;
                    o->animActive = 0;
                    o->animIndex = -1;
                    o->drawPass = 1;
                    o++;
                    b = (GardenBlockObj*)o;
                }
                fountainIdx = i;
                i--;
                o--;
                continue;
            } else {
                b->type = cfg->type;
                b->variant = cfg->variant;
                if (b->type == GARDEN_BLOCK_MYSTERY) {
                    if (b->variant == GARDEN_BLOCK_RANDOM) {
                        b->variant = rand() % 3;
                    }
                } else if (b->type == GARDEN_BLOCK_BRICK &&
                           b->variant == GARDEN_BLOCK_RANDOM) {
                    b->variant = rand() % 3;
                } else {
                    b->variant = b->type;
                }
                o->model = (StadiumModel*)(GARDEN_ANIM_TABLE + b->type * 0x90 + 0x34);
                o->triangles = files[ids[b->variant + 9]];
                o->callback = NULL;
                o->func = (int (*)(int, int, void*))data->hitFns[b->type];
                o->hasShadow = cfg->shown;
                shadowBit = 0;
                if (o->hasShadow && o->triangles != NULL) {
                    shadowBit = 1;
                }
                o->_90b1 = shadowBit;
                ((Control*)o)->type = 0;
                CTRLSetTranslation((Control*)o, cfg->x, cfg->y, cfg->z);
                CTRLSetRotation((Control*)o, 0.0f, cfg->rotation, 0.0f);
                o->fadeByDepth = 1;
            }
            o->alpha = 0xFF;
            o->preDraw = NULL;
            o->effect = NULL;
            o->animActive = 0;
            o->animIndex = -1;
            o->drawPass = 1;
        }
    }

    f = &stadiumObjectCollision.objects[fountainIdx];
    ((GardenBlockObj*)f)->index = 0x33;
    ((GardenBlockObj*)f)->type = GARDEN_BLOCK_FOUNTAIN;
    ((GardenBlockObj*)f)->variant = 10;
    peachGardenSomething();
    f->model = (StadiumModel*)(GARDEN_ANIM_TABLE + 0x814);
    f->triangles = NULL;
    f->callback = (void (*)(void))fn_3_F8BA8;
    f->func = NULL;
    f->hasShadow = 1;
    shadowBit = 0;
    if (f->hasShadow && f->triangles != NULL) {
        shadowBit = 1;
    }
    f->_90b1 = shadowBit;
    ((Control*)f)->type = 0;
    CTRLSetTranslation((Control*)f, 0.0f, 0.0f, 0.0f);
    CTRLSetRotation((Control*)f, 0.0f, 0.0f, 0.0f);
    f->fadeByDepth = 1;
    f->alpha = 0xFF;
    f->preDraw = (void (*)(StadiumObject*))fn_3_F8B34;
    f->effect = NULL;
    f->animActive = 0;
    f->animIndex = -1;
    f->drawPass = 1;
    fn_3_F8D00();

    f++;
    ((GardenBlockObj*)f)->index = 0x33;
    ((GardenBlockObj*)f)->type = GARDEN_BLOCK_FOUNTAIN_FX;
    f->model = (StadiumModel*)(GARDEN_ANIM_TABLE + 0x8A4);
    f->triangles = NULL;
    f->callback = NULL;
    f->func = NULL;
    f->hasShadow = 1;
    shadowBit = 0;
    if (f->hasShadow && f->triangles != NULL) {
        shadowBit = 1;
    }
    f->_90b1 = shadowBit;
    ((Control*)f)->type = 0;
    CTRLSetTranslation((Control*)f, 0.0f, -0.01f, 0.0f);
    CTRLSetRotation((Control*)f, 0.0f, 0.0f, 0.0f);
    f->fadeByDepth = 1;
    f->alpha = 0xFF;
    f->preDraw = NULL;
    f->effect = (StadiumObjectEffect*)&fountainEffect;
    f->animActive = 0;
    f->animIndex = -1;
    f->drawPass = 1;

    if (g_d_GameSettings.miniGameStadiumIndicator == 0) {
        stadiumObjectCollision.crowd->layout = lbl_3_data_10F7C;
        seat = lbl_3_data_110A8;
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
        seat = lbl_3_data_11138;
        stadiumObjectCollision.crowdAlt->sequence = lbl_3_data_11008;
        stadiumObjectCollision.crowdAlt->frames = (u8*)g_UNK_StadiumDetails._00 + 0xA0;
        stadiumObjectCollision.crowdAlt->altFrames = (u8*)g_UNK_StadiumDetails._00 + 0x80;
        stadiumObjectCollision.crowdAlt->fanCount = 0x10;
        stadiumObjectCollision.crowdAlt->framesPerLoop = 2;
        stadiumObjectCollision.crowdAlt->phaseRange = 8;
        for (i = 0, k = 0; i < 0x10; i++, k += 3, seat++) {
            stadiumObjectCollision.crowdAlt->fans[k] = seat->type;
            if (seat->frame >= 2) {
                stadiumObjectCollision.crowdAlt->fans[k + 1] = seat->frame;
            } else {
                stadiumObjectCollision.crowdAlt->fans[k + 1] = rand() % 6;
            }
            if (seat->phase >= 8) {
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

    stadiumObjectCollision.vertexDataArray = NULL;
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES) {
        fn_3_FA3C0();
    }
    fn_3_B97C8(fn_3_F8444);
}

// .text:0x000FB3D8 size:0x7C8 mapped:0x8073A46C
void fn_3_FB3D8(void* view) {
    Vec delta;
    Vec step;
    GXTlutObj tlut;
    GXTexObj tex;
    f32 ringUV[42];
    f32* uv;
    Vec* grid;
    Vec* dst;
    Vec* out;
    Vec* spoke;
    Vec* center;
    GardenTexInfo* info;
    u8* strip;
    f32 minX;
    f32 maxX;
    f32 minY;
    f32 maxY;
    f32 x;
    f32 rangeX;
    f32 rangeY;
    int i;
    int j;
    int a;
    int b;

    fn_8003A144();
    uv = _OSAllocFromHeap(4, 0x20D0);
    spoke = lbl_3_data_1BF6C;
    grid = (Vec*)(uv + 0x348);
    center = &lbl_3_data_1BF6C[20];
    dst = grid;
    for (i = 0; i < 21; i++, spoke++) {
        if (i != 20) {
            PSVECSubtract(spoke, center, &delta);
            out = dst;
            for (j = 1; j <= 20; j++) {
                PSVECScale(&delta, (f32)j / 22.0f, &step);
                PSVECAdd(center, &step, out);
                out++;
                dst++;
            }
        }
    }
    fn_800245EC(fn_80052768_getCamera(0), ((GardenView*)view)->mtx, lbl_3_data_1BF6C, ringUV, 21, 1);
    fn_800245EC(fn_80052768_getCamera(0), ((GardenView*)view)->mtx, grid, uv, 400, 1);
    minX = 16777215.0f;
    maxX = -minX;
    minY = minX;
    maxY = maxX;
    for (i = 0; i < 400; i++) {
        x = uv[i * 2];
        if (minX > x) {
            minX = x;
        }
        if (maxX < x) {
            maxX = x;
        }
        x = uv[i * 2 + 1];
        if (minY > x) {
            minY = x;
        }
        if (maxY < x) {
            maxY = x;
        }
    }
    rangeX = 0.005f * (maxX - minX);
    rangeY = 0.005f * (maxY - minY);
    for (i = 0; i < 800; i += 2) {
        uv[i] += rangeX * (rand() % 256) * 0.00390625f - 0.0025f;
        uv[i + 1] += rangeY * (rand() % 256) * 0.00390625f - 0.0025f;
    }

    info = returnTexture();
    if (info->tlut != NULL) {
        GXInitTexObjCI(&tex, info->data, info->width, info->height, info->format, info->wrapS, info->wrapT,
                       info->minLOD != info->maxLOD, 0);
        GXInitTlutObj(&tlut, info->tlut, info->tlutFormat, info->tlutEntries);
        GXLoadTlut(&tlut, 0);
    } else {
        GXInitTexObj(&tex, info->data, info->width, info->height, info->format, info->wrapS, info->wrapT,
                     info->minLOD != info->maxLOD);
    }
    GXInitTexObjLOD(&tex, info->minFilter, info->magFilter, info->minLOD, info->maxLOD, info->lodBias, GX_DISABLE,
                    GX_DISABLE, GX_ANISO_1);
    GXLoadTexObj(&tex, GX_TEXMAP0);
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_DISABLE);
    GXSetCullMode(GX_CULL_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_OR);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGBA, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_CLR_RGBA, GX_F32, 0);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2X4, GX_TG_TEX0, GX_IDENTITY, GX_DISABLE, GX_PTIDENTITY);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
    GXLoadPosMtxImm(((GardenView*)view)->mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);

    strip = lbl_3_data_1C068[0];
    for (i = 0; i < 20; i++, strip += 3) {
        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 43);
        GX_WRITE_F32(lbl_3_data_1BF6C[strip[0]].x);
        GX_WRITE_F32(0.01f + lbl_3_data_1BF6C[strip[0]].y);
        GX_WRITE_F32(lbl_3_data_1BF6C[strip[0]].z);
        GX_WRITE_U32(0xFFFFFFFF);
        GX_WRITE_F32(ringUV[strip[0] * 2]);
        GX_WRITE_F32(ringUV[strip[0] * 2 + 1]);
        a = strip[1];
        b = strip[2];
        for (j = 0; j < 20; j++) {
            GXPosition3f32(grid[a * 20 + j].x, 0.01f + grid[a * 20 + j].y, grid[a * 20 + j].z);
            GXColor1u32(0xFFFFFFFF);
            GXTexCoord2f32(uv[(a * 20 + j) * 2], uv[(a * 20 + j) * 2 + 1]);
            GXPosition3f32(grid[b * 20 + j].x, 0.01f + grid[b * 20 + j].y, grid[b * 20 + j].z);
            GXColor1u32(0xFFFFFFFF);
            GXTexCoord2f32(uv[(b * 20 + j) * 2], uv[(b * 20 + j) * 2 + 1]);
        }
        GX_WRITE_F32(lbl_3_data_1BF6C[a].x);
        GX_WRITE_F32(0.01f + lbl_3_data_1BF6C[a].y);
        GX_WRITE_F32(lbl_3_data_1BF6C[a].z);
        GX_WRITE_U32(0xFFFFFFFF);
        GX_WRITE_F32(ringUV[a * 2]);
        GX_WRITE_F32(ringUV[a * 2 + 1]);
        GX_WRITE_F32(lbl_3_data_1BF6C[b].x);
        GX_WRITE_F32(0.01f + lbl_3_data_1BF6C[b].y);
        GX_WRITE_F32(lbl_3_data_1BF6C[b].z);
        GX_WRITE_U32(0xFFFFFFFF);
        GX_WRITE_F32(ringUV[b * 2]);
        GX_WRITE_F32(ringUV[b * 2 + 1]);
    }
    fn_800ACFB0(uv);
}

// .text:0x000FBBA0 size:0x130 mapped:0x8073AC34
void fn_3_FBBA0(GardenTexInfo* info) {
    GXTlutObj tlut;
    GXTexObj tex;

    if (info->tlut != NULL) {
        GXInitTexObjCI(&tex, info->data, info->width, info->height, info->format, info->wrapS, info->wrapT,
                       info->minLOD != info->maxLOD, 0);
        GXInitTlutObj(&tlut, info->tlut, info->tlutFormat, info->tlutEntries);
        GXLoadTlut(&tlut, 0);
    } else {
        GXInitTexObj(&tex, info->data, info->width, info->height, info->format, info->wrapS, info->wrapT,
                     info->minLOD != info->maxLOD);
    }
    GXInitTexObjLOD(&tex, info->minFilter, info->magFilter, info->minLOD, info->maxLOD, info->lodBias, GX_DISABLE,
                    GX_DISABLE, GX_ANISO_1);
    GXLoadTexObj(&tex, GX_TEXMAP0);
}

// .text:0x000FBCD0 size:0x88 mapped:0x8073AD64
void fn_3_FBCD0(void) {
    updateGameStatusFlag();
    if (g_GameLogic.bOD_framesInLiveBallScene >= 0) {
        PSMTXCopy(fn_80052768_getCamera(0)->view, lbl_3_data_1BE94[drawStadiumRelated].mtx);
        fn_800A7D4C(1, &lbl_3_data_1BE94[drawStadiumRelated]);
    }
}
