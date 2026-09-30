#define SQRT2_LINKAGE static
#include "game/animation/scene_effects.h"
#define REP_HEADER_DATA_FN getRepHeaderData_sceneEffects
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "C3/control.h"
#include "game/animation/actor_transform.h"
#include "C3/actor.h"
#include "Dolphin/mtx.h"
#include "Dolphin/gx.h"
#include "Dolphin/stl.h"
#include "stl/math.h"
#include "stl/mem.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x8005268c.h"
#include "Unknown/File_0x80052734.h"
#include "Dolphin/mtxext.h"
#include "Unknown/File_0x800a7568.h"

typedef struct _SunLayer {
    /*0x00*/ VecXYZ pos;
    /*0x0C*/ s16 texture;
    /*0x0E*/ u8 kind;
    /*0x0F*/ u8 _0F;
} SunLayer; // size: 0x10

typedef struct _SceneFx {
    /*0x000*/ DrawingSceneStruct* sceneItem;
    /*0x004*/ u32 texture;
    /*0x008*/ void* hudModel;
    /*0x00C*/ void* _0C;
    /*0x010*/ u8* actorList;
    /*0x014*/ u8 _014[0x398];
    /*0x3AC*/ u32 flags;
    /*0x3B0*/ u8 hudLoaded;
    /*0x3B1*/ u8 _3B1;
    /*0x3B2*/ u8 _3B2[0x2];
    /*0x3B4*/ u8* textures;
    /*0x3B8*/ SunLayer* sunLayers;
    /*0x3BC*/ VecXYZ sunPos;
    /*0x3C8*/ u32 sunTick;
    /*0x3CC*/ u32 sunPeriod;
    /*0x3D0*/ f32 _3D0;
    /*0x3D4*/ f32 _3D4;
    /*0x3D8*/ f32 _3D8;
    /*0x3DC*/ f32 _3DC;
    /*0x3E0*/ u8 sunActive;
    /*0x3E1*/ u8 sunOnScreen;
    /*0x3E2*/ u8 sunVisible;
    /*0x3E3*/ u8 _3E3[0x1];
    /*0x3E4*/ u32 _3E4;
    /*0x3E8*/ VecXYZ starPos;
    /*0x3F4*/ VecXYZ starRot;
    /*0x400*/ u8 _400[0xA];
    /*0x40A*/ u8 starActive;
    /*0x40B*/ u8 _40B[0x1];
    /*0x40C*/ void* _40C[3];
    /*0x418*/ u8 _418;
    /*0x419*/ u8 contactKind;
    /*0x41A*/ u8 contactHandle;
    /*0x41B*/ u8 _41B[0x1];
    /*0x41C*/ VecXYZ contactPos;
    /*0x428*/ VecXYZ ballScreenPos;
    /*0x434*/ VecXYZ hitScreenPos;
    /*0x440*/ VecXYZ _440;
    /*0x44C*/ VecXYZ _44C;
    /*0x458*/ u8 _458[0xC];
    /*0x464*/ s16 _464;
    /*0x466*/ u8 _466;
    /*0x467*/ s8 starHitLevel;
    /*0x468*/ u8 _468[0x8];
    /*0x470*/ u8 _470;
    /*0x471*/ u8 _471[0x1];
    /*0x472*/ u8 _472[5];
    /*0x477*/ u8 _477[0x2];
    /*0x479*/ u8 paused;
    /*0x47A*/ u8 _47A[0x6];
} SceneFx; // size: 0x480

extern SceneFx lbl_3_common_bss_35154;
extern struct { u8 _00[0x28]; u8 _28; } lbl_80366158;
extern u8 drawStadiumRelated;
typedef struct _SceneQuad {
    /*0x000*/ u8 _000[0x4];
    /*0x004*/ f32 x;
    /*0x008*/ f32 y;
    /*0x00C*/ f32 scale;
    /*0x010*/ u8 _010[0xC];
    /*0x01C*/ f32 rotX;
    /*0x020*/ f32 rotY;
    /*0x024*/ f32 rotZ;
    /*0x028*/ u8 _028[0x10];
    /*0x038*/ f32 width;
    /*0x03C*/ f32 height;
    /*0x040*/ u32 colorFront;
    /*0x044*/ u32 colorBack;
} SceneQuad; // size: 0x48
typedef struct _SceneParticle {
    /*0x000*/ struct _SceneParticle* next;
    /*0x004*/ f32 x;
    /*0x008*/ f32 y;
    /*0x00C*/ f32 size;
    /*0x010*/ f32 velX;
    /*0x014*/ f32 velY;
    /*0x018*/ f32 velZ;
    /*0x01C*/ f32 _1C;
    /*0x020*/ f32 _20;
    /*0x024*/ f32 _24;
    /*0x028*/ f32 _28;
    /*0x02C*/ f32 _2C;
    /*0x030*/ f32 _30;
    /*0x034*/ u8 _034[0x4];
    /*0x038*/ f32 _38;
    /*0x03C*/ f32 _3C;
    /*0x040*/ u8 _040[0x1];
    /*0x041*/ u8 _41;
    /*0x042*/ u8 _42;
    /*0x043*/ u8 _43;
    /*0x044*/ u8 _44;
    /*0x045*/ u8 _45;
    /*0x046*/ u8 _46;
    /*0x047*/ u8 _47;
    /*0x048*/ s16 _48;
    /*0x04A*/ s16 _4A;
} SceneParticle; // size: 0x4C
typedef struct _SceneActor {
    /*0x000*/ u8 _000[0x34];
    /*0x034*/ VecXYZ pos;
    /*0x040*/ u8 _040[0x4];
    /*0x044*/ f32 yaw;
    /*0x048*/ u8 _048[0x20A];
    /*0x252*/ s8 charId;
    /*0x253*/ u8 _253[0x7];
    /*0x25A*/ u8 _25A;
    /*0x25B*/ u8 _25B[0x2];
    /*0x25D*/ u8 _25D;
    /*0x25E*/ u8 _25E[0x17];
    /*0x275*/ u8 _275;
    /*0x276*/ u8 _276;
    /*0x277*/ u8 _277[0x2];
    /*0x279*/ u8 _279;
    /*0x27A*/ u8 _27A[0x2];
} SceneActor; // size: 0x27C
typedef struct _SceneNode {
    /*0x000*/ u8 _000[0x14];
    /*0x014*/ u16 idxA;
    /*0x016*/ u16 idxB;
    /*0x018*/ s16 _18;
    /*0x01A*/ u8 _01A[0x26];
} SceneNode; // size: 0x40


typedef struct _SceneBss {
    /*0x000*/ u8 _00;
    /*0x001*/ u8 _001[0x1];
    /*0x002*/ s16 count;
    /*0x004*/ s16 _04;
    /*0x006*/ u8 _006[0x2];
    /*0x008*/ s32 alpha;
    /*0x00C*/ u8 state;
    /*0x00D*/ u8 _00D[0x3];
    /*0x010*/ s32 _10;
    /*0x014*/ f32 _14;
    /*0x018*/ u32 rngAccum;
    /*0x01C*/ VecXYZ _1C;
    /*0x028*/ VecXYZ scratch[37];
    /*0x1E4*/ VecXYZ trailA[18];
    /*0x2BC*/ VecXYZ trailB[18];
    /*0x394*/ VecXYZ last[2];
    /*0x3AC*/ s16 timer;
    /*0x3AE*/ u8 _3AE[0x22];
} SceneBss; // size: 0x3D0
static u8 lbl_3_bss_9950;
static s16 lbl_3_bss_9952[5];
static u8 lbl_3_bss_995C;
static s32 lbl_3_bss_9960;
static f32 lbl_3_bss_9964;
static u32 lbl_3_bss_9968;
static VecXYZ lbl_3_bss_996C;
static VecXYZ lbl_3_bss_9978[78];
typedef void (*SceneAnimHook)(int);
typedef struct _ScenePoolObj {
    /*0x000*/ u8 _000[0x5C];
    /*0x05C*/ u32 _5C;
    /*0x060*/ u8 _060[0x21C];
} ScenePoolObj; // size: 0x27C
typedef struct _SceneAnimView {
    /*0x000*/ u8 _000[0x70];
    /*0x070*/ void* model;
    /*0x074*/ u8 _074[0x38];
    /*0x0AC*/ u32 _AC[4];
    /*0x0BC*/ u8 _0BC[0xB48];
    /*0xC04*/ ScenePoolObj pool[13];
    /*0x2C50*/ SceneActor* actors[13];
    /*0x2C84*/ u8 _2C84[0x3EC];
    /*0x3070*/ SceneAnimHook hookA;
    /*0x3074*/ SceneAnimHook hookB;
    /*0x3078*/ u8 _3078[0xDC];
} SceneAnimView; // size: 0x3154
extern SceneAnimView hugeAnimStruct;
typedef struct _SceneFireSlot {
    /*0x00*/ s32 word0;
    /*0x04*/ u8 _04[8];
    /*0x0C*/ s32 wordC;
    /*0x10*/ u8 _10[0x48 - 0x10];
} SceneFireSlot; // size: 0x48

typedef struct _SunLayerSet {
    SunLayer layers[10];
} SunLayerSet;
typedef struct _SceneFxData {
    /*0x000*/ u8 stadiumTbl[8];
    /*0x008*/ u8 colorTbl[24];
    /*0x020*/ f32 charPairs[54][2];
    /*0x1D0*/ u8 _1D0[6];
    /*0x1D6*/ u8 _1D6[0x26E];
    /*0x444*/ u8 _444[0x10];
    /*0x454*/ u8 _454[0x5854];
    /*0x5CA8*/ s32 tblC[14];
    /*0x5CE0*/ s32 tblA[17];
    /*0x5D24*/ void* tblB[14];
    /*0x5D5C*/ u32 tblD[16];
    /*0x5D9C*/ u8 _5D9C[0x20];
    /*0x5DBC*/ SceneFireSlot slots[2];
    /*0x5E4C*/ u8 _5E4C[0x4];
} SceneFxData; // size: 0x5E50
typedef struct _ContactWordBuf {
    /*0x000*/ u8 _000[8];
    /*0x008*/ Mtx view;
    /*0x038*/ VecXYZ pos;
    /*0x044*/ s32 count;
    /*0x048*/ f32 invZoom;
    /*0x04C*/ f32 ring[96][2];
} ContactWordBuf; // size: 0x34C

typedef struct _ContactWordNode {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ s16 state;
    /*0x12*/ u8 _12[2];
    /*0x14*/ VecXYZ pos;
    /*0x20*/ s32 count;
    /*0x24*/ ContactWordBuf* buf;
} ContactWordNode;
typedef struct _HudKey {
    /*0x00*/ f32 value;
    /*0x04*/ f32 amp;
    /*0x08*/ u16 type : 4;
    /*0x08*/ u16 frame : 12;
    /*0x0A*/ u8 rising;
    /*0x0B*/ u8 flags;
} HudKey; // size: 0xC

typedef struct _HudNode {
    /*0x00*/ f32 x;
    /*0x04*/ f32 y;
    /*0x08*/ f32 w;
    /*0x0C*/ f32 h;
    /*0x10*/ u16 texture;
    /*0x12*/ u16 subTexture;
    /*0x14*/ HudKey* ch[8];
    /*0x34*/ u8 count[8];
    /*0x3C*/ u8 index[8];
} HudNode; // size: 0x44

typedef struct _HudObj {
    /*0x00*/ HudNode* nodes;
    /*0x04*/ void** textures;
    /*0x08*/ s32 count;
    /*0x0C*/ u8 _0C[4];
    /*0x10*/ f32 frame;
    /*0x14*/ f32 time;
} HudObj;

typedef f32 (*HudEvalFn)(HudNode* node, int frame, Mtx out, f32 t);
typedef struct _SceneFxEntry {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ void* file14;
    /*0x18*/ u8 _18[0x28];
    /*0x40*/ void* file40;
    /*0x44*/ u8 _44[0x5C - 0x44];
} SceneFxEntry; // size: 0x5C

typedef struct _HudAct {
    /*0x00*/ void* actor;
    /*0x04*/ void* animBank;
    /*0x08*/ u8 _08[6];
    /*0x0E*/ u16 sequenceNum;
    /*0x10*/ u8 _10[0x50];
    /*0x60*/ f32 animTime;
} HudAct;

#define FX_ENTRY(k) (((SceneFxEntry*)&lbl_3_common_bss_35154)[k])
typedef struct _SceneEffect {
    /*0x00*/ u8 _00[0xC];
    /*0x0C*/ SceneParticle* head;
    /*0x10*/ u8 _10[4];
    /*0x14*/ u16 _14flags : 4;
    /*0x14*/ u16 count : 12;
} SceneEffect;
typedef struct _SceneSortEntry {
    SceneParticle* p;
    f32 depth;
} SceneSortEntry;
typedef struct _SunSpriteVtx {
    /*0x00*/ VecXYZ pos;
    /*0x0C*/ u32 color;
    /*0x10*/ s16 u;
    /*0x12*/ s16 v;
} SunSpriteVtx; // size: 0x14
typedef struct _SceneUiRecord {
    /*0x000*/ u8 _000[0x48];
    /*0x048*/ f32 x;
    /*0x04C*/ f32 y;
    /*0x050*/ f32 z;
    /*0x054*/ u32 flags;
    /*0x058*/ u32 rgba;
    /*0x05C*/ u32 frame;
    /*0x060*/ u8 _060[0x9];
    /*0x069*/ u8 playMode;
    /*0x06A*/ u8 _06A[0x56];
} SceneUiRecord; // size: 0xC0
typedef struct _SceneUiHandle {
    SceneUiRecord* object;
    u32 unk4;
} SceneUiHandle;

#define UI_REC(k) (graphicsRelatedArray[node->idxA + (k)].object)
typedef struct _SceneBone {
    /*0x00*/ u8 _00[0xEC];
    /*0xEC*/ MtxPtr worldMtx;
} SceneBone;

typedef struct _SceneBoneList {
    /*0x00*/ u8 _00[0x18];
    /*0x18*/ SceneBone** bones;
} SceneBoneList;

typedef struct _SceneAnimModel {
    /*0x00*/ SceneBoneList* list;
} SceneAnimModel;


extern SunLayerSet sunLayers[];
extern f32 lbl_3_data_111C8[][2];
extern s32 lbl_3_data_170D8[];
extern s32 lbl_3_data_17000[];
extern void (*lbl_3_data_11390[])(void*);
extern u8 lbl_3_data_1146C[];
extern void* teamStarModelFileDescriptorGame;

extern void fn_8003A688(int a, f32 x, f32 y);
extern void fn_800BD670(void* model, int arg);
extern void fn_800BD548(void* model, int mode, ...);
extern void fn_800BD8C4(void* model, int arg);
extern void fn_8006C43C(void* fn);
extern void fn_8006C3F0(void* fn);
extern void fn_3_CABB4(void);
extern void fn_3_CB538(int mode);
extern void fn_3_15F574(void);
extern void fn_3_160814(void);
extern void removeGraphicsElementFromScene(void* item);
extern void addGraphicsElementToScene(void* item, void* table);
extern void* ARAMTransfer(void* file, s32 a, s32 b, s32 c);
extern void bowserCastleSomething(void);
extern void warioPalaceSomething(void);
extern void peachGardenSomething(void);
extern void minigamesSetSomePointers(void);
extern void fn_3_C0854(void);
extern void peachDaisyStarEffect_setup(int side);
extern void peachDaisyStarPitch_updateEffectTarget(BOOL side);
extern void pitchingMachinePitching(u8 arg);
extern BOOL fn_80033928(u8 id);
extern void* allocParticleEffect(void* func, int a, int b, int c, int d, u8 e);
extern void callSfx(int sfx);
extern int rand(void);
extern u8 fn_3_8D4(VecSrcDst* seg, CollisionStruct* hit);
extern f32 lbl_3_data_12CB4;
extern void fn_8003A550(int idx, Vec* pos, Vec* vel, int flag);
extern void fn_8003A6B0(int idx, void* arg, f32 a, f32 b);
extern void fn_8003A848(int a, int b, int c);
extern void fn_8003A85C(int a);
extern SceneFxData lbl_3_data_111A8;
extern void fn_80028628(int a, int b, void* s0, int c, void* p, void* s1, int d);
extern ContactWordBuf lbl_3_data_11620[4];
extern u8 framesToSwitchCam[2];
extern void fn_800A7D4C(s32 arg0, void* arg1);
extern u16 lbl_800F7860[8];
extern void fn_80033B58(void* tex, int sub, int a, int b);
extern void processStadiumFileObjects(u8* types, int count, u8* base, u32* out);
extern void fn_8004B1B8(void* tex);
extern void fn_80035750(void* a, void* b, int c);
extern void* ActorObjectInitTable(u16 count);
extern void animateBallRelated(void* table, u16 index, u16 slot, void* data, int arg4, int arg5);
extern void fn_3_6750C(void* textures);
extern void convertTextureHeader(void* tex);
extern void LoadActorLayout(void* layout);
extern void convertGeometryAndSknHeader(void* geo, void* skn);
extern void ANIMGet(void* anim);
extern void UpdateTexturePalettePointers(void* geo, void* tex);
extern void haveActLayoutPointToGeoHeader(void* layout, void* geo);
extern void adjustInternalPointers(void* file);
extern void ACTActorRelated(void* file, void* actor);
extern void actRelated(void* file, void* effect);
extern void actorRelated(void* effect, int a, int b);
extern void fn_800245EC(camera_803c639c_s* cam, Mtx view, Vec* pos, f32* out, int a, int b);
extern s32 lbl_3_data_12350;
extern void fn_3_15FB84(int a, ...);
extern void fn_3_169150(void);
extern BOOL marioHandOnFire_endFireAnimation(BOOL clear);
extern void animatePitchersHandOnFire(void);
extern s32 fn_8004ABE0(void);
extern void* _OSAllocFromHeap(s32 heap, s32 size);
extern void fn_800ACFB0(void* p);
extern void fn_800246D4(void* cmp, void* base, void* scratch, int size, int count);
extern void fn_3_BA174(void);
extern void fn_800B24D4(int a);
extern void fn_800B27DC(camera_803c639c_s* cam, int a);
extern void setTextRenderingMode(s32 mode);
extern void fn_800B21A8(void);
extern void DrawSprite_TexObj(void* vtx, void* texObj, s32 arg2);
extern SceneUiHandle graphicsRelatedArray[];
extern void load_Icon(void* scene, int handle, u32 part, u32 element, int frame);
extern void fn_8003656C(void* scene, int handle, u32 part, u32 element, int frame);
extern SceneAnimModel* fn_800111D8(SceneActor* actor);
extern void spline3D_resample(Vec* out, Vec* points, int count, int outCount);
extern s32 lbl_3_data_115FC[7];

// .text:0x000C07B0 size:0x60 mapped:0x8070A844
void fn_3_C07B0(void) {
    if (fn_80033928(0x10) != 0 || allocParticleEffect(fn_3_C0134, 0x80, 0, 0, 0, 0x10) != NULL) {
        lbl_3_bss_995C = 0;
    }
}

// .text:0x000C07A0 size:0x10 mapped:0x8070A834
void chargeAnimRelated(void) {
    lbl_3_bss_995C = 3;
}

// .text:0x000C0770 size:0x30 mapped:0x8070A804
void fn_3_C0770(void) {
    pitchingMachinePitching(0x10);
    lbl_3_bss_9952[0] = 0;
}

// .text:0x000C0134 size:0x63C mapped:0x806FF1C8
int fn_3_C0134(void) {
    Vec splineB[48];
    Vec splineA[48];
    Vec b;
    Vec a;
    Vec tmp;
    SceneBss* S = (SceneBss*)&lbl_3_bss_9950;
    SceneActor* actor;
    SceneAnimModel* model;
    SceneBone* bone;
    int charId;
    int i;
    int m;
    int color;
    int accum;
    u16 boneIndex;
    u8 state;

    charId = (s8)g_Batter.charID;
    for (i = 0; i < 13; i++) {
        actor = hugeAnimStruct.actors[i];
        if (actor != NULL && actor->charId == charId) {
            break;
        }
    }
    if (i >= 13) {
        return 1;
    }
    model = fn_800111D8(actor);
    state = S->state;
    switch (state) {
    case 0:
        S->alpha = 0;
        S->_04 = 0;
        S->count = 1;
        S->timer = 0;
        S->state = state + 1;
        break;
    case 1:
        if (lbl_80366158._28 == 0) {
            S->alpha += (lbl_80366158._28 == 0) << 4;
            S->count += (S->timer | (lbl_80366158._28 != 0)) == 0;
            if (S->alpha >= 0xFF) {
                S->state = state + 1;
                S->alpha = 0xFF;
            }
        }
        break;
    case 3:
        if (lbl_80366158._28 == 0) {
            S->alpha -= (lbl_80366158._28 == 0) << 4;
            S->count -= (S->timer | (lbl_80366158._28 != 0)) == 0;
            if (S->count < 2) {
                S->alpha = 0;
                S->state = 0;
                return 1;
            }
        }
        break;
    }
    if (lbl_80366158._28 == 0) {
        boneIndex = *(u16*)((u8*)actor + 0x162 + lbl_3_data_115FC[6] * 2);
        if (boneIndex != 0xFFFF) {
            a.x = (f32)lbl_3_data_115FC[0] / 100000.0f;
            a.y = (f32)lbl_3_data_115FC[1] / 100000.0f;
            a.z = (f32)lbl_3_data_115FC[2] / 100000.0f;
            b.x = (f32)lbl_3_data_115FC[3] / 100000.0f;
            b.y = (f32)lbl_3_data_115FC[4] / 100000.0f;
            b.z = (f32)lbl_3_data_115FC[5] / 100000.0f;
            bone = model->list->bones[boneIndex];
            if (S->count > 1 && S->timer == 0 && lbl_80366158._28 == 0) {
                S->trailA[0] = S->last[0];
                S->trailB[0] = S->last[1];
                memmove(&S->trailA[1], &S->trailA[0], (S->count - 1) * sizeof(Vec));
                memmove(&S->trailB[1], &S->trailB[0], (S->count - 1) * sizeof(Vec));
            }
            PSMTXMultVec(bone->worldMtx, &a, &tmp);
            S->trailA[0].x = actor->pos.x + tmp.x;
            S->trailA[0].y = actor->pos.y + tmp.y;
            S->trailA[0].z = actor->pos.z + tmp.z;
            PSMTXMultVec(bone->worldMtx, &b, &tmp);
            S->trailB[0].x = actor->pos.x + tmp.x;
            S->trailB[0].y = actor->pos.y + tmp.y;
            S->trailB[0].z = actor->pos.z + tmp.z;
            if (S->timer == 0 && lbl_80366158._28 == 0) {
                S->last[0] = S->trailA[0];
                S->last[1] = S->trailB[0];
            }
        }
        S->_04 = (S->_04 + (lbl_80366158._28 == 0)) % 16;
    }
    if (S->count >= 3) {
        spline3D_resample(splineA, (Vec*)S->trailA, S->count, S->count * 3 + 1);
        spline3D_resample(splineB, (Vec*)S->trailB, S->count, S->count * 3 + 1);
        GXLoadPosMtxImm(returnFloatFromModeIndex(returnsCurrentMode())->view, 0);
        fn_80033B58((void*)lbl_3_common_bss_35154.texture, 1, 0, 0);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
        GXSetCullMode(GX_CULL_NONE);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
        m = (S->count - 1) * 3;
        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, (m + 1) * 2);
        accum = 0;
        for (i = 0; i <= m; i++) {
            color = (S->alpha - accum / m) | 0xFFFFFF00;
            accum += S->alpha;
            GXPosition3f32(splineA[i].x, splineA[i].y, splineA[i].z);
            GXColor1u32(color);
            GXTexCoord2f32((f32)i / (f32)m, 0.0f);
            GXPosition3f32(splineB[i].x, splineB[i].y, splineB[i].z);
            GXColor1u32(color);
            GXTexCoord2f32((f32)i / (f32)m, 1.0f);
        }
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    }
    S->timer = (S->timer + 2 - (lbl_80366158._28 == 0)) % 2;
    return 0;
}

// .text:0x000BFDA4 size:0x390 mapped:0x806FEE38
f32 fn_3_BFDA4(HudKey* keys, int count, int endFrame, u8 index, u8* outIndex, f32 t) {
    int dir;
    f32 span;
    f32 localT;
    f32 delta;
    f32 value;
    f32 half;
    f32 sign;
    HudKey* cur;
    HudKey* next;

    if (index < count - 1 && (f32)keys[index + 1].frame <= t) {
        dir = 1;
    } else if (index != 0 && (f32)keys[index].frame > t) {
        dir = -1;
    }
    while (1) {
        if (index < count - 1 && (f32)keys[index + 1].frame <= t) {
            index += dir;
            continue;
        }
        if (index != 0 && (f32)keys[index].frame > t) {
            index += dir;
            continue;
        }
        break;
    }
    if (index == count - 1) {
        span = endFrame - keys[index].frame;
        next = &keys[index];
    } else {
        span = keys[index + 1].frame - keys[index].frame;
        next = &keys[index + 1];
    }
    cur = &keys[index];
    localT = t - (f32)cur->frame;
    delta = next->value - cur->value;
    value = cur->value;
    switch (cur->type) {
    case 0:
        t = value + delta * localT / span;
        break;
    case 1:
        half = cur->amp * 0.5f;
        if (cur->rising != 0) {
            sign = half;
        } else {
            sign = -half;
        }
        if (cur->flags & 1) {
            if (cur->rising != 0) {
                delta -= cur->amp;
            } else {
                delta += cur->amp;
            }
        }
        t = half * cos(3.1415927f * ((f32)cur->rising + localT * (f32)cur->flags / span)) + ((value + sign) + delta * localT / span);
        break;
    }
    if (outIndex != NULL) {
        *outIndex = index;
    }
    return t;
}

// .text:0x000BFB3C size:0x268 mapped:0x806FEBD0
f32 fn_3_BFB3C(HudNode* node, int frame, Mtx out, f32 t) {
    Mtx tmp;
    f32 v;

    PSMTXIdentity(out);
    PSMTXIdentity(tmp);
    if (node->ch[0] != NULL) {
        v = fn_3_BFDA4(node->ch[0], node->count[0], frame, node->index[0], &node->index[0], t);
    } else {
        v = 1.0f;
    }
    out[0][0] = v;
    if (node->ch[1] != NULL) {
        v = fn_3_BFDA4(node->ch[1], node->count[1], frame, node->index[1], &node->index[1], t);
    } else {
        v = 1.0f;
    }
    out[1][1] = v;
    if (node->ch[6] != NULL) {
        v = fn_3_BFDA4(node->ch[6], node->count[6], frame, node->index[6], &node->index[6], t);
    } else {
        v = 0.0f;
    }
    if (v != 0.0f) {
        PSMTXRotRad(tmp, 'Z', v);
        PSMTXConcat(tmp, out, out);
    }
    if (node->ch[5] != NULL) {
        v = fn_3_BFDA4(node->ch[5], node->count[5], frame, node->index[5], &node->index[5], t);
    } else {
        v = 0.0f;
    }
    if (v != 0.0f) {
        PSMTXRotRad(tmp, 'Y', v);
        PSMTXConcat(tmp, out, out);
    }
    PSMTXIdentity(tmp);
    if (node->ch[2] != NULL) {
        v = fn_3_BFDA4(node->ch[2], node->count[2], frame, node->index[2], &node->index[2], t);
    } else {
        v = 0.0f;
    }
    tmp[0][3] = v;
    if (node->ch[3] != NULL) {
        v = fn_3_BFDA4(node->ch[3], node->count[3], frame, node->index[3], &node->index[3], t);
    } else {
        v = 0.0f;
    }
    tmp[1][3] = v;
    if (node->ch[4] != NULL) {
        v = fn_3_BFDA4(node->ch[4], node->count[4], frame, node->index[4], &node->index[4], t);
    } else {
        v = 0.0f;
    }
    tmp[2][3] = v;
    PSMTXConcat(tmp, out, out);
    if (node->ch[7] != NULL) {
        return fn_3_BFDA4(node->ch[7], node->count[7], frame, node->index[7], &node->index[7], t);
    }
    return 1.0f;
}

// .text:0x000BF8F8 size:0x244 mapped:0x806FE98C
void fn_3_BF8F8(HudObj* obj, Mtx view, Vec* origin, HudEvalFn eval) {
    Mtx concat;
    Mtx inv;
    VecXYZ quad[4];
    Vec out;
    HudNode* node;
    u8 alpha;
    int i;
    int j;

    if (eval == NULL) {
        eval = fn_3_BFB3C;
    }
    PSMTXInverse(view, inv);
    inv[0][3] = 0.0f;
    inv[1][3] = 0.0f;
    inv[2][3] = 0.0f;
    memset(quad, 0, sizeof(quad));
    for (i = 0; i < obj->count; i++) {
        node = &obj->nodes[i];
        alpha = 255.0f * eval(node, (int)obj->frame, concat, obj->time);
        if (alpha != 0) {
            quad[0].x = node->x;
            quad[0].y = node->y;
            quad[1].x = node->x + node->w;
            quad[1].y = node->y;
            quad[2].x = node->x + node->w;
            quad[2].y = node->y + node->h;
            quad[3].x = node->x;
            quad[3].y = node->y + node->h;
            PSMTXConcat(inv, concat, concat);
            fn_80033B58(obj->textures[node->texture], node->subTexture, 0, 0);
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            for (j = 0; j < 4; j++) {
                PSMTXMultVec(concat, (Vec*)&quad[j], &out);
                GXPosition3f32(origin->x + out.x, origin->y + out.y, origin->z + out.z);
                GXColor1u32(0xFFFFFF00 | alpha);
                GXTexCoord2f32((f32)lbl_800F7860[j * 2], (f32)lbl_800F7860[j * 2 + 1]);
            }
        }
    }
}

// .text:0x000BF878 size:0x80 mapped:0x806FE90C
BOOL maybeLoadHUDObjectFromMemory(void) {
    if (lbl_803C6CF8.cancel.bytes[1] == 1) {
        lbl_3_common_bss_35154.hudModel = ARAMTransfer(&teamStarModelFileDescriptorGame, 0, 0, 0);
        insertGraphicDrawingFunction(maybeHudRelated, 0);
        lbl_3_common_bss_35154.hudLoaded = TRUE;
        return TRUE;
    }
    return FALSE;
}

// .text:0x000BF6C0 size:0x1B8 mapped:0x806FE754
void maybeHudRelated(void) {
    SceneFxData* data = &lbl_3_data_111A8;
    u32 out[6];

    if (lbl_803C6CF8.cancel.bytes[1] == 1) {
        processStadiumFileObjects(data->_1D0, 6, (u8*)lbl_3_common_bss_35154.hudModel, out);
        lbl_3_common_bss_35154.texture = *(u32*)lbl_3_common_bss_35154.hudModel;
        fn_8004B1B8((void*)lbl_3_common_bss_35154.texture);
        fn_80035750(((void**)lbl_3_common_bss_35154.hudModel)[1], ((void**)lbl_3_common_bss_35154.hudModel)[2], 4);
        hugeAnimStruct.model = ActorObjectInitTable(1);
        animateBallRelated(hugeAnimStruct.model, 0, 0, ((void**)lbl_3_common_bss_35154.hudModel)[out[4]], 0, 0);
        fn_3_BF070();
        fn_3_6750C((void*)lbl_3_common_bss_35154.texture);
        lbl_3_common_bss_35154._0C = ARAMTransfer(data->_444, 0, 0, 0);
        currentDrawingItem->func = fn_3_BF238;
    }
}

// .text:0x000BF238 size:0x488 mapped:0x806FE2CC
void fn_3_BF238(void) {
    SceneFx* fx = &lbl_3_common_bss_35154;
    void* tex;
    void* layout;
    void* geo;
    void* anim;
    void* file;
    HudAct* act;
    void* effect;
    int actorCount;
    int actorOffset;
    int i;

    if (lbl_803C6CF8.cancel.bytes[1] == 1) {
        actorCount = 0;
        fx->actorList = ActorObjectInitTable(7);
        actorOffset = 0;
        for (i = 0; i < 44; i++) {
            if (((u32*)fx->_0C)[i] != 0) {
                ((u32*)fx->_0C)[i] += (u32)fx->_0C;
                switch (i) {
                case 0:
                case 8:
                case 18:
                case 24:
                case 30:
                case 36:
                    tex = (void*)((u32*)fx->_0C)[i];
                    convertTextureHeader(tex);
                    break;
                case 1:
                case 9:
                case 19:
                case 25:
                case 31:
                case 37:
                    layout = (void*)((u32*)fx->_0C)[i];
                    LoadActorLayout(layout);
                    break;
                case 2:
                case 10:
                case 20:
                case 26:
                case 32:
                case 38:
                    geo = (void*)((u32*)fx->_0C)[i];
                    convertGeometryAndSknHeader(geo, NULL);
                    break;
                case 3:
                case 11:
                case 21:
                case 27:
                case 33:
                case 39:
                    anim = (void*)((u32*)fx->_0C)[i];
                    ANIMGet(anim);
                    UpdateTexturePalettePointers(geo, tex);
                    haveActLayoutPointToGeoHeader(layout, geo);
                    animateBallRelated(fx->actorList, (u16)actorCount, (u16)actorCount, layout, (int)anim, 0);
                    act = (HudAct*)(fx->actorList + actorOffset + 0x34);
                    ACTSetAnimation(act->actor, act->animBank, NULL, act->sequenceNum, 0.0f, act->animTime);
                    actorOffset += 0x90;
                    actorCount++;
                    break;
                case 4:
                case 5:
                    file = (void*)((u32*)fx->_0C)[i];
                    FX_ENTRY(i - 4).file40 = file;
                    adjustInternalPointers(file);
                    ACTActorRelated(file, fx->actorList + 0x34);
                    break;
                case 12:
                case 13:
                case 14:
                    file = (void*)((u32*)fx->_0C)[i];
                    FX_ENTRY(i - 10).file40 = file;
                    adjustInternalPointers(file);
                    ACTActorRelated(file, fx->actorList + 0xC4);
                    break;
                case 22:
                    file = (void*)((u32*)fx->_0C)[i];
                    FX_ENTRY(i - 0x11).file40 = file;
                    adjustInternalPointers(file);
                    ACTActorRelated(file, fx->actorList + 0x154);
                    break;
                case 28:
                    file = (void*)((u32*)fx->_0C)[i];
                    FX_ENTRY(i - 0x16).file40 = file;
                    adjustInternalPointers(file);
                    ACTActorRelated(file, fx->actorList + 0x1E4);
                    break;
                case 34:
                    file = (void*)((u32*)fx->_0C)[i];
                    FX_ENTRY(i - 0x1B).file40 = file;
                    adjustInternalPointers(file);
                    ACTActorRelated(file, fx->actorList + 0x274);
                    break;
                case 40:
                case 41:
                    file = (void*)((u32*)fx->_0C)[i];
                    FX_ENTRY(i - 0x20).file40 = file;
                    adjustInternalPointers(file);
                    ACTActorRelated(file, fx->actorList + 0x304);
                    break;
                case 6:
                case 7:
                    FX_ENTRY(i - 6).file14 = ((void**)fx->_0C)[i];
                    effect = &FX_ENTRY(i - 6).file14;
                    actRelated(FX_ENTRY(i - 6).file40, effect);
                    actorRelated(effect, 0, 0);
                    break;
                case 15:
                case 16:
                case 17:
                    FX_ENTRY(i - 0xD).file14 = ((void**)fx->_0C)[i];
                    effect = &FX_ENTRY(i - 0xD).file14;
                    actRelated(FX_ENTRY(i - 0xD).file40, effect);
                    actorRelated(effect, 0, 0);
                    break;
                case 23:
                    FX_ENTRY(i - 0x12).file14 = ((void**)fx->_0C)[i];
                    effect = &FX_ENTRY(i - 0x12).file14;
                    actRelated(FX_ENTRY(i - 0x12).file40, effect);
                    actorRelated(effect, 0, 0);
                    break;
                case 29:
                    FX_ENTRY(i - 0x17).file14 = ((void**)fx->_0C)[i];
                    effect = &FX_ENTRY(i - 0x17).file14;
                    actRelated(FX_ENTRY(i - 0x17).file40, effect);
                    actorRelated(effect, 0, 0);
                    break;
                case 35:
                    FX_ENTRY(i - 0x1C).file14 = ((void**)fx->_0C)[i];
                    effect = &FX_ENTRY(i - 0x1C).file14;
                    actRelated(FX_ENTRY(i - 0x1C).file40, effect);
                    actorRelated(effect, 0, 0);
                    break;
                case 42:
                case 43:
                    FX_ENTRY(i - 0x22).file14 = ((void**)fx->_0C)[i];
                    effect = &FX_ENTRY(i - 0x22).file14;
                    actRelated(FX_ENTRY(i - 0x22).file40, effect);
                    actorRelated(effect, 0, 0);
                    break;
                }
            }
        }
        lbl_3_common_bss_35154.hudLoaded = 0;
        insertGraphicDrawingFunction(fn_3_BEFF8, 6);
        removeCurrentDrawingItem();
    }
}

// .text:0x000BF20C size:0x2C mapped:0x806FE2A0
void fn_3_BF20C(void) {
    fn_8006C43C(0);
    fn_8006C3F0(0);
}

// .text:0x000BF1AC size:0x60 mapped:0x806FE240
void pauseAnimations(void) {
    int i;

    minigamesSetSomePointers();
    fn_3_C0854();
    fn_3_CABB4();
    i = 12;
    do {
        hugeAnimStruct.pool[i]._5C = 0;
    } while (i-- != 0);
    lbl_3_common_bss_35154.paused = TRUE;
}

// .text:0x000BF158 size:0x54 mapped:0x806FE1EC
void pauseStateOnStadiums(void) {
    if (g_d_GameSettings.StadiumID == STADIUM_ID_BOWSERS_CASTLE) {
        bowserCastleSomething();
    } else if (g_d_GameSettings.StadiumID == STADIUM_ID_WARIO_PALACE) {
        warioPalaceSomething();
    } else if (g_d_GameSettings.StadiumID == STADIUM_ID_PEACH_GARDEN) {
        peachGardenSomething();
    }
}

// .text:0x000BF070 size:0xE8 mapped:0x806FE104
void fn_3_BF070(void) {
    SceneFxData* data = &lbl_3_data_111A8;
    u8* hud;
    int i;
    SceneActor* actor;

    fn_8003A85C(data->stadiumTbl[g_d_GameSettings.StadiumID]);
    fn_8003A848(data->colorTbl[g_d_GameSettings.StadiumID * 3], data->colorTbl[g_d_GameSettings.StadiumID * 3 + 1], data->colorTbl[g_d_GameSettings.StadiumID * 3 + 2]);
    hud = *(u8**)((u8*)lbl_3_common_bss_35154.hudModel + 0x18);
    lbl_3_common_bss_35154._3B1 = 1;
    for (i = 0; i < 13; i++) {
        actor = hugeAnimStruct.actors[i];
        if (actor != NULL) {
            fn_8003A6B0(i, hud + 4, data->charPairs[actor->charId][0], data->charPairs[actor->charId][1]);
        } else {
            fn_8003A6B0(i, hud + 4, data->charPairs[0][0], data->charPairs[0][1]);
        }
    }
}

// .text:0x000BEFF8 size:0x78 mapped:0x806FE08C
void fn_3_BEFF8(void) {
    DrawingSceneStruct* item = currentDrawingItem;

    lbl_3_common_bss_35154.sceneItem = item;
    addGraphicsElementToScene(item, lbl_3_data_1146C);
    ((SceneNode*)item)->_18 = 0;
    currentDrawingItem->func = fn_3_BE1D4;
    lbl_3_common_bss_35154.flags = 0;
}

// .text:0x000BE1D4 size:0xE24 mapped:0x806FD268
void fn_3_BE1D4(void) {
    SceneNode* node = (SceneNode*)currentDrawingItem;
    SceneFx* fx = &lbl_3_common_bss_35154;
    Vec pos;
    SceneActor* actor;
    SceneAnimModel* tmpObj;
    u8 alpha;
    int i;
    int charId;

    if (fx->sceneItem == NULL) {
        removeCurrentDrawingItem();
        return;
    }
    if (fx->flags & 3) {
        if (g_d_GameSettings._55 != 0 || fx->paused != 0) {
            UI_REC(fx->contactHandle)->flags &= ~2;
            UI_REC(fx->contactHandle)->frame = 0;
            fx->flags &= ~3;
        } else {
            UI_REC(fx->contactKind)->x = fx->contactPos.x;
            UI_REC(fx->contactKind)->y = fx->contactPos.y;
            UI_REC(fx->contactKind)->z = fx->contactPos.z;
            if (fx->flags & 1) {
                if (fx->contactKind == 4) {
                    fx->contactHandle = 3;
                } else {
                    fx->contactHandle = fx->contactKind;
                }
                UI_REC(fx->contactHandle)->flags |= 2;
                fx->flags &= ~3;
                fx->flags |= 2;
                if (fx->contactKind == 4) {
                    fx->flags |= 0x40;
                }
            } else if (UI_REC(fx->contactHandle)->playMode == 2) {
                if (*(s16*)((u8*)&g_Ball + 0x1B66) > 0) {
                    UI_REC(fx->contactHandle)->flags &= ~2;
                    UI_REC(fx->contactHandle)->frame = 0;
                    fx->flags &= ~3;
                }
            }
        }
    }
    if (fx->flags & 0x30) {
        if (g_d_GameSettings._55 != 0 || fx->paused != 0) {
            UI_REC(7)->flags &= ~2;
            UI_REC(7)->frame = 0;
            UI_REC(8)->flags &= ~2;
            UI_REC(9)->flags &= ~2;
            UI_REC(8)->frame = 0;
            UI_REC(9)->frame = 0;
            fx->flags &= ~0x30;
        } else {
            tmpObj = NULL;
            charId = g_Pitcher.charID;
            for (i = 0; i < 9; i++) {
                actor = hugeAnimStruct.actors[i];
                if (actor != NULL && actor->charId == charId) {
                    tmpObj = fn_800111D8(actor);
                    break;
                }
            }
            if (tmpObj != NULL && (((u8*)tmpObj->list)[0x98] & 9) == 0) {
                alpha = 0;
            } else {
                alpha = 0xFF;
            }
            PSMTXMultVec(returnFloatFromModeIndex(0)->view, (Vec*)&fx->ballScreenPos, &pos);
            PSMTX44MultVec(returnFloatFromModeIndex(0)->proj, &pos, &pos);
            if (g_Stats.replayInd != 0) {
                pos.y = 0.0f;
            }
            pos.x = pos.x * 320.0f;
            pos.y = pos.y * 224.0f;
            for (i = 4; i < 10; i++) {
                load_Icon(node, 8, i, 0xD, fx->starHitLevel - 1);
            }
            for (i = 1; i < 5; i++) {
                fn_8003656C(node, 6, i, 0x11, fx->starHitLevel - 1);
            }
            if (fx->flags & 0x10) {
                fx->flags &= ~0x30;
                fx->flags |= 0x20;
                UI_REC(7)->x = 320.0f + pos.x;
                UI_REC(7)->y = 224.0f - pos.y;
                UI_REC(7)->z = 0.0f;
                UI_REC(7)->flags |= 2;
                UI_REC(7)->rgba = (UI_REC(7)->rgba & 0xFFFFFF00) | alpha;
                playSoundEffect(0x1A5);
            } else if ((UI_REC(7)->frame >> 16) == 0x23) {
                UI_REC(7)->flags &= ~2;
                UI_REC(7)->frame = 0;
                if (fx->starHitLevel != 0) {
                    UI_REC(8)->x = 320.0f;
                    UI_REC(8)->y = 224.0f - pos.y;
                    UI_REC(8)->z = 0.0f;
                    UI_REC(9)->x = 320.0f;
                    UI_REC(9)->y = 224.0f;
                    UI_REC(9)->z = 0.0f;
                    UI_REC(8)->flags |= 2;
                    UI_REC(9)->flags |= 2;
                    UI_REC(8)->rgba = (UI_REC(8)->rgba & 0xFFFFFF00) | alpha;
                    UI_REC(9)->rgba = (UI_REC(9)->rgba & 0xFFFFFF00) | alpha;
                    fn_3_BDE14();
                    playSoundEffect(0x1A6);
                } else {
                    fx->flags &= ~0x30;
                }
            } else if ((UI_REC(8)->frame >> 16) == 0x3C) {
                UI_REC(8)->flags &= ~2;
                UI_REC(9)->flags &= ~2;
                UI_REC(8)->frame = 0;
                UI_REC(9)->frame = 0;
                fx->flags &= ~0x30;
            }
        }
    }
    if (fx->flags & 0xC0) {
        if (g_d_GameSettings._55 != 0 || fx->paused != 0) {
            UI_REC(5)->flags &= ~2;
            UI_REC(6)->flags &= ~2;
            UI_REC(5)->frame = 0;
            UI_REC(6)->frame = 0;
            fx->flags &= ~0xC0;
        } else if (fx->starHitLevel != 0) {
            PSMTXMultVec(returnFloatFromModeIndex(0)->view, (Vec*)&fx->hitScreenPos, &pos);
            PSMTX44MultVec(returnFloatFromModeIndex(0)->proj, &pos, &pos);
            pos.x = pos.x * 320.0f;
            pos.y = pos.y * 224.0f;
            for (i = 4; i < 10; i++) {
                load_Icon(node, 5, i, 0xD, fx->starHitLevel - 1);
            }
            for (i = 1; i < 5; i++) {
                fn_8003656C(node, 6, i, 0x11, fx->starHitLevel - 1);
            }
            UI_REC(5)->x = 320.0f;
            UI_REC(5)->y = 224.0f - pos.y;
            UI_REC(5)->z = 0.0f;
            UI_REC(6)->x = 320.0f;
            UI_REC(6)->y = 224.0f;
            UI_REC(6)->z = 0.0f;
            if (fx->flags & 0x40) {
                UI_REC(5)->flags |= 2;
                UI_REC(6)->flags |= 2;
                fx->flags &= ~0xC0;
                fx->flags |= 0x80;
            } else if ((UI_REC(5)->frame >> 16) == 0x34) {
                UI_REC(5)->flags &= ~2;
                UI_REC(6)->flags &= ~2;
                UI_REC(5)->frame = 0;
                UI_REC(6)->frame = 0;
                fx->flags &= ~0xC0;
            }
        } else {
            fx->flags &= ~0xC0;
        }
    }
    if (fx->flags & 0x300) {
        if (g_d_GameSettings._55 != 0 || fx->paused != 0) {
            UI_REC(4)->flags &= ~2;
            UI_REC(4)->frame = 0;
            fx->flags &= ~0x300;
        } else {
            PSMTXMultVec(returnFloatFromModeIndex(0)->view, (Vec*)&fx->hitScreenPos, &pos);
            PSMTX44MultVec(returnFloatFromModeIndex(0)->proj, &pos, &pos);
            pos.x = pos.x * 320.0f;
            pos.y = pos.y * 224.0f;
            UI_REC(4)->x = 320.0f + pos.x;
            UI_REC(4)->y = 224.0f - pos.y;
            UI_REC(4)->z = 0.0f;
            if (fx->flags & 0x100) {
                UI_REC(4)->flags |= 2;
                fx->flags &= ~0x300;
                fx->flags |= 0x200;
                playSoundEffect(0x1A5);
            } else if ((UI_REC(4)->frame >> 16) == 0x23) {
                UI_REC(4)->flags &= ~2;
                UI_REC(4)->frame = 0;
                fx->flags &= ~0x300;
                playSoundEffect(0x1A6);
            }
        }
    }
    if (fx->flags & 0xC) {
        if (g_d_GameSettings._55 != 0 || fx->paused != 0) {
            UI_REC(10)->flags &= ~2;
            UI_REC(10)->frame = 0;
            fx->flags &= ~0xC;
        } else {
            UI_REC(10)->x = fx->starPos.x;
            UI_REC(10)->y = fx->starPos.y;
            UI_REC(10)->z = fx->starPos.z;
            if (fx->flags & 4) {
                UI_REC(10)->flags |= 2;
                fx->flags &= ~0xC;
                fx->flags |= 8;
            } else if (fx->starActive == 0) {
                UI_REC(10)->flags &= ~2;
                UI_REC(10)->frame = 0;
                fx->flags &= ~0xC;
            } else if (UI_REC(10)->playMode == 2) {
                UI_REC(10)->frame = 0;
            }
        }
    }
}

// .text:0x000BE174 size:0x60 mapped:0x806FD208
void setContactWordSprite(int kind, f32 x, f32 y, f32 z) {
    DrawingSceneStruct* item;

    lbl_3_common_bss_35154.flags |= 1;
    lbl_3_common_bss_35154.contactPos.x = x;
    lbl_3_common_bss_35154.contactPos.y = y;
    lbl_3_common_bss_35154.contactPos.z = z;
    lbl_3_common_bss_35154.contactKind = kind;
    if (kind == 4) {
        item = insertGraphicDrawingFunction(fn_3_BDF74, 3);
        item->state = 2;
    }
}

// .text:0x000BE140 size:0x34 mapped:0x806FD1D4
void fn_3_BE140(void) {
    DrawingSceneStruct* item = insertGraphicDrawingFunction(fn_3_BDF74, 3);

    item->state = 2;
}

// .text:0x000BDF74 size:0x1CC mapped:0x806FD008
void fn_3_BDF74(void) {
    ContactWordNode* node = (ContactWordNode*)currentDrawingItem;
    f32* ball = (f32*)((u8*)&g_Ball + 0x354);
    int i;

    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154.paused != 0) {
        removeCurrentDrawingItem();
    } else if (node->state != 0) {
        node->state--;
    } else {
        node->pos.x = ball[0];
        node->pos.y = -ball[1];
        node->pos.z = ball[2];
        node->count = framesToSwitchCam[1] - 2;
        node->buf = &lbl_3_data_11620[2];
        for (i = 0; i < 96; i++) {
            f32 angle = 6.2831855f * (f32)rand() / 32767.0f;

            lbl_3_data_11620[2].ring[i][0] = 400.0 * cos(angle);
            lbl_3_data_11620[2].ring[i][1] = 400.0 * sin(angle);
        }
        memcpy(lbl_3_data_11620[3].ring, lbl_3_data_11620[2].ring, sizeof(lbl_3_data_11620[2].ring));
        currentDrawingItem->func = fn_3_BDCA4;
    }
}

// .text:0x000BDE14 size:0x160 mapped:0x806FCEA8
void fn_3_BDE14(void) {
    ContactWordNode* node = (ContactWordNode*)insertGraphicDrawingFunction(fn_3_BDCA4, 3);
    int i;

    getAnimRelatedCoordinates(0, 7, &node->pos);
    node->count = framesToSwitchCam[1] - 2;
    node->buf = &lbl_3_data_11620[0];
    for (i = 0; i < 96; i++) {
        f32 angle = 6.2831855f * (f32)rand() / 32767.0f;

        lbl_3_data_11620[0].ring[i][0] = 400.0 * cos(angle);
        lbl_3_data_11620[0].ring[i][1] = 400.0 * sin(angle);
    }
    memcpy(lbl_3_data_11620[1].ring, lbl_3_data_11620[0].ring, sizeof(lbl_3_data_11620[0].ring));
}

// .text:0x000BDCA4 size:0x170 mapped:0x806FCD38
void fn_3_BDCA4(void) {
    ContactWordNode* node = (ContactWordNode*)currentDrawingItem;

    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154.paused != 0) {
        removeCurrentDrawingItem();
    } else {
        node->count -= (lbl_80366158._28 != 2);
        node->buf[drawStadiumRelated].invZoom = 1.0f / fn_80052768_getCamera(0)->zoom;
        node->buf[drawStadiumRelated].pos.x = node->pos.x;
        node->buf[drawStadiumRelated].pos.y = node->pos.y;
        node->buf[drawStadiumRelated].pos.z = node->pos.z;
        node->buf[drawStadiumRelated].count = node->count;
        PSMTXCopy(fn_80052768_getCamera(0)->view, node->buf[drawStadiumRelated].view);
        fn_800A7D4C(0, &node->buf[drawStadiumRelated]);
        if (node->count == 0) {
            removeCurrentDrawingItem();
        }
    }
}

// .text:0x000BD8FC size:0x3A8 mapped:0x806FC990
void fn_3_BD8FC(ContactWordBuf* buf) {
    Mtx ident;
    VecXYZ v;
    VecXYZ n;
    f32 pos[2];
    int colorA;
    int colorB;
    f32 scale;
    f32 cx;
    f32 cy;
    f32 x;
    f32 y;
    int i;
    int t;

    if (lbl_3_bss_9960 != 0) {
        colorA = -1;
        colorB = colorA;
    } else {
        t = framesToSwitchCam[1] - 0x12;
        if (buf->count < t) {
            colorA = (buf->count * 0xFF / t) | 0xFFFFFF00;
            colorB = colorA;
        } else if (buf->count < framesToSwitchCam[1] - 10) {
            colorA = ((buf->count - t) * 0x7F8 / 8) | 0xFFFFFF00;
            colorB = -1;
        } else {
            colorA = 0xFFFFFF00;
            colorB = ((framesToSwitchCam[1] - 2 - buf->count) * 0xFF / 8) | 0xFFFFFF00;
        }
    }
    scale = 0.00078125f * buf->invZoom;
    fn_800245EC(fn_80052768_getCamera(0), buf->view, (Vec*)&buf->pos, pos, 1, lbl_3_data_12350);
    cx = (-(640.0f * pos[0] + -320.0f)) * scale;
    cy = (-(448.0f * pos[1] + -224.0f)) * scale;
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    PSMTXIdentity(ident);
    GXLoadPosMtxImm(ident, 0);
    GXSetCurrentMtx(0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetProjection(fn_80052768_getCamera(0)->proj, GX_PERSPECTIVE);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
    GXSetCullMode(GX_CULL_NONE);
    GXBegin(GX_TRIANGLES, GX_VTXFMT0, 0x120);
    for (i = 0; i < 96; i++) {
        x = buf->ring[i][0] * scale;
        y = buf->ring[i][1] * scale;
        v.x = cx - x;
        v.y = cy - y;
        v.z = 0.0f;
        PSVECScale((Vec*)&v, 0.75f, (Vec*)&v);
        n.x = v.y;
        n.y = -v.x;
        n.z = 0.0f;
        PSVECNormalize((Vec*)&n, (Vec*)&n);
        PSVECScale((Vec*)&n, 0.003125f, (Vec*)&n);
        GXPosition3f32(x - n.x, y - n.y, -1.0f);
        GXColor1u32(colorB);
        GXPosition3f32(x + n.x, y + n.y, -1.0f);
        GXColor1u32(colorB);
        GXPosition3f32(x + v.x, y + v.y, -1.0f);
        GXColor1u32(colorA);
    }
}

// .text:0x000BD8D8 size:0x24 mapped:0x806FC96C
void fn_3_BD8D8(void) {
    hugeAnimStruct.hookA = fn_3_BD80C;
    hugeAnimStruct.hookB = fn_3_BD7DC;
}

// .text:0x000BD80C size:0xCC mapped:0x806FC8A0
void fn_3_BD80C(int arg) {
    SceneFx* fx = &lbl_3_common_bss_35154;
    SceneAnimView* h = &hugeAnimStruct;
    f32* star = (f32*)&fx->_3E4;

    if (fx->starActive != 0) {
        CTRLSetTranslation((Control*)((u8*)h->model + 0x44), star[1], star[2], star[3]);
        CTRLSetRotation((Control*)((u8*)h->model + 0x44), 57.29578f * star[4], 57.29578f * star[5], 57.29578f * star[6]);
        fn_800BD548((u8*)h->model + 0x34, 4, h->_AC[0], h->_AC[1], h->_AC[2], h->_AC[3]);
    }
    fn_800BD8C4(h->model, arg);
}

// .text:0x000BD7DC size:0x30 mapped:0x806FC870
void fn_3_BD7DC(int arg) {
    fn_800BD670(hugeAnimStruct.model, arg);
}

// .text:0x000BD7D8 size:0x4 mapped:0x806FC86C
void fn_3_BD7D8(void) {
}

// .text:0x000BD7D0 size:0x8 mapped:0x806FC864
BOOL fn_3_BD7D0(void) {
    return TRUE;
}

// .text:0x000BD758 size:0x78 mapped:0x806FC7EC
void fn_3_BD758(void) {
    SceneNode* node = (SceneNode*)currentDrawingItem;

    if (lbl_803C6CF8.cancel.bytes[1] == 1) {
        lbl_3_common_bss_35154._418 = 0;
        lbl_3_data_11390[node->idxA](lbl_3_common_bss_35154._40C[node->idxB]);
        removeCurrentDrawingItem();
    }
}

// .text:0x000BD6AC size:0xAC mapped:0x806FC740
void fn_3_BD6AC(BOOL isBatter, f32 x, f32 y, f32 z) {
    SceneFx* fx = &lbl_3_common_bss_35154;
    u8 type;

    fx->_466 = TRUE;
    fx->_440.x = x;
    fx->_440.y = y;
    fx->_440.z = z;
    fx->_464 = 0;
    if (isBatter) {
        type = g_Ball.currentStarSwing;
        switch (type) {
        case CAPTAIN_STAR_TYPE_PEACH:
        case CAPTAIN_STAR_TYPE_DAISY:
            peachDaisyStarEffect_setup(type == CAPTAIN_STAR_TYPE_DAISY);
            break;
        }
    } else {
        type = g_Pitcher.starPitchType;
        switch (type) {
        case CAPTAIN_STAR_TYPE_PEACH:
        case CAPTAIN_STAR_TYPE_DAISY:
            peachDaisyStarEffect_setup(type == CAPTAIN_STAR_TYPE_DAISY);
            break;
        }
    }
}

// .text:0x000BD504 size:0x1A8 mapped:0x806FC598
void animationRelated(f32 x, f32 y, f32 z, BOOL isBatter) {
    u8 type;

    if (lbl_80366158._28 == 0) {
        memcpy(&lbl_3_common_bss_35154._44C, &lbl_3_common_bss_35154._440, sizeof(VecXYZ));
        lbl_3_common_bss_35154._440.x = x;
        lbl_3_common_bss_35154._440.y = y;
        lbl_3_common_bss_35154._440.z = z;
    }
    if (lbl_3_common_bss_35154._466 != 0) {
        if (isBatter) {
            type = g_Ball.currentStarSwing;
            switch (type) {
            case CAPTAIN_STAR_TYPE_MARIO:
            case CAPTAIN_STAR_TYPE_LUIGI:
                fn_3_CB538(type);
                break;
            case CAPTAIN_STAR_TYPE_WARIO:
            case CAPTAIN_STAR_TYPE_WALUIGI:
                fn_3_160814();
                break;
            case CAPTAIN_STAR_TYPE_BOWSER:
            case CAPTAIN_STAR_TYPE_BOWSERJR:
                fn_3_15F574();
                break;
            case CAPTAIN_STAR_TYPE_PEACH:
            case CAPTAIN_STAR_TYPE_DAISY:
                break;
            }
        } else {
            type = g_Pitcher.starPitchType;
            switch (type) {
            case CAPTAIN_STAR_TYPE_MARIO:
            case CAPTAIN_STAR_TYPE_LUIGI:
                fn_3_CB538(type);
                break;
            case CAPTAIN_STAR_TYPE_BOWSER:
            case CAPTAIN_STAR_TYPE_BOWSERJR:
                fn_3_15F574();
                break;
            case CAPTAIN_STAR_TYPE_PEACH:
            case CAPTAIN_STAR_TYPE_DAISY:
                peachDaisyStarPitch_updateEffectTarget(type == CAPTAIN_STAR_TYPE_DAISY);
                break;
            }
        }
        if (lbl_80366158._28 == 0) {
            lbl_3_common_bss_35154._464++;
        }
    }
}

// .text:0x000BD4F0 size:0x14 mapped:0x806FC584
void fn_3_BD4F0(void) {
    lbl_3_common_bss_35154._466 = FALSE;
}

// .text:0x000BD434 size:0xBC mapped:0x806FC4C8
void setSunLocation(int a, int b) {
    SunLayer* layer;
    int i;

    lbl_3_common_bss_35154.sunLayers = sunLayers[a + b * 7].layers;
    lbl_3_common_bss_35154.sunPeriod = 0x1518;
    lbl_3_common_bss_35154.sunTick = 0;
    lbl_3_common_bss_35154._3D0 = 0.3125f;
    lbl_3_common_bss_35154._3D4 = 0.0002f;
    lbl_3_common_bss_35154._3D8 = 0.5f;
    for (i = 0, layer = lbl_3_common_bss_35154.sunLayers; layer->kind < 4; layer++, i++) {
    }
    lbl_3_common_bss_35154.sunActive = TRUE;
    lbl_3_common_bss_35154.sunPos.x = lbl_3_common_bss_35154.sunLayers[i].pos.x;
    lbl_3_common_bss_35154.sunPos.y = lbl_3_common_bss_35154.sunLayers[i].pos.y;
    lbl_3_common_bss_35154.sunPos.z = lbl_3_common_bss_35154.sunLayers[i].pos.z;
    lbl_3_common_bss_35154._3DC = 128.0f;
}

// .text:0x000BD1D8 size:0x25C mapped:0x806FC26C
void sunRelated(Mtx view) {
    SceneFx* fx = &lbl_3_common_bss_35154;
    camera_803c639c_s* cam = fn_80052768_getCamera(0);
    f32 invZoom = 1.0f / cam->zoom;
    VecSrcDst seg;
    CollisionStruct hit;
    Vec tmp;
    f32 halfW;
    f32 halfH;
    u8 inside;

    fx->sunTick = (u32)(fx->sunTick + 1) % (u32)fx->sunPeriod;
    PSVECScale((Vec*)&fx->sunPos, 1.0f, &tmp);
    PSMTXMultVec(view, &tmp, (Vec*)&lbl_3_bss_9978[0]);
    if (lbl_3_bss_9978[0].z <= -1.0f) {
        halfW = 640.0f * lbl_3_bss_9978[0].z * 0.5f / -1280.0f * invZoom;
        halfH = -448.0f * lbl_3_bss_9978[0].z * 0.5f / -1280.0f * invZoom;
        inside = FALSE;
        if (halfH < 384.0f + lbl_3_bss_9978[0].y && lbl_3_bss_9978[0].y - 384.0f < -halfH && halfW > lbl_3_bss_9978[0].x - 384.0f && 384.0f + lbl_3_bss_9978[0].x > -halfW) {
            inside = TRUE;
        }
        fx->sunOnScreen = inside;
        if (inside) {
            lbl_3_bss_996C.x = 2.0f * -lbl_3_bss_9978[0].x;
            lbl_3_bss_996C.y = 2.0f * -lbl_3_bss_9978[0].y;
            lbl_3_bss_996C.z = 0.0f;
            if (g_UNK_StadiumDetails.numCollisionBoxes_77C != 0) {
                memcpy(&seg.src, &fn_80052768_getCamera(0)->eye, sizeof(Vec));
                memcpy(&seg.dst, &fx->sunPos, sizeof(Vec));
                fx->sunVisible = fn_3_8D4(&seg, &hit);
                if (fx->sunVisible == 0) {
                    memcpy(&seg.dst, &fn_80052768_getCamera(0)->eye, sizeof(Vec));
                    memcpy(&seg.src, &fx->sunPos, sizeof(Vec));
                    fx->sunVisible = fn_3_8D4(&seg, &hit);
                }
            }
        }
    } else {
        fx->sunOnScreen = FALSE;
    }
}

// .text:0x000BD1D4 size:0x4 mapped:0x806FC268
void fn_3_BD1D4(void) {
}

// .text:0x000BCA20 size:0x7B4 mapped:0x806FBAB4
void drawSun(void) {
    SceneFx* fx = &lbl_3_common_bss_35154;
    camera_803c639c_s* cam = fn_80052768_getCamera(0);
    f32 depthScale = -lbl_3_bss_9978[0].z / 1280.0f;
    f32 invZoom = 1.0f / cam->zoom;
    SunLayer* layers;
    SunLayer* layer;
    SunSpriteVtx sprite[4];
    Mtx rot;
    VecXYZ quad[4];
    Vec toSun;
    Vec axis;
    Quaternion qSpin;
    Quaternion qTilt;
    f32 dist;
    f32 halfDiag;
    f32 fade;
    f32 angle;
    f32 size;
    f32 c;
    f32 s;
    f32 tilt;
    f32 k;
    int alpha;
    int off;
    int i;

    if (fx->sunOnScreen != 0) {
        layers = fx->sunLayers;
        fn_800B24D4(10);
        fn_800B27DC(fn_80052768_getCamera(0), 0);
        setTextRenderingMode(2);
        toSun.x = lbl_3_bss_9978[0].x;
        toSun.y = lbl_3_bss_9978[0].y;
        toSun.z = 0.0f;
        dist = PSVECMag(&toSun);
        toSun.z = 0.0f;
        toSun.x = 640.0f * lbl_3_bss_9978[0].z * invZoom * 0.5f / -1280.0f;
        toSun.y = 448.0f * lbl_3_bss_9978[0].z * invZoom * 0.5f / -1280.0f;
        halfDiag = PSVECMag(&toSun);
        fade = -255.0f * dist / halfDiag;
        angle = 3.1415925f * (f32)(u32)(fx->sunTick * 2) / (f32)(u32)fx->sunPeriod;
        axis.x = lbl_3_bss_996C.y;
        axis.y = -lbl_3_bss_996C.x;
        axis.z = 0.0f;
        PSVECNormalize(&axis, &axis);
        off = 0;
        for (layer = &layers[off]; layer->pos.z != 0.0f; layer = (SunLayer*)((u8*)layers + off)) {
            if (layer->_0F == 0 && fx->sunVisible != 0) {
                off += 0x10;
                continue;
            }
            fn_800B21A8();
            PSVECScale((Vec*)&lbl_3_bss_996C, layer->pos.x, &toSun);
            PSVECAdd((Vec*)&lbl_3_bss_9978[0], &toSun, &toSun);
            size = fx->_3DC * layer->pos.z / 100.0f;
            switch (layer->kind) {
            case 0:
            case 1:
                alpha = 255;
                break;
            case 2:
            case 3:
                alpha = (int)(fade * layer->pos.y + 255.0f);
                break;
            }
            if (alpha > 0) {
                alpha |= 0xFFFFFF00;
                switch (layer->kind) {
                case 0:
                    c = size * cos(angle);
                    s = size * sin(angle);
                    quad[0].x = depthScale * (toSun.x - c);
                    quad[0].y = depthScale * (toSun.y - s);
                    quad[0].z = toSun.z * depthScale;
                    quad[1].x = depthScale * (toSun.x - s);
                    quad[1].y = depthScale * (toSun.y + c);
                    quad[1].z = toSun.z * depthScale;
                    quad[2].x = depthScale * (toSun.x + c);
                    quad[2].y = depthScale * (toSun.y + s);
                    quad[2].z = toSun.z * depthScale;
                    quad[3].x = depthScale * (toSun.x + s);
                    quad[3].y = depthScale * (toSun.y - c);
                    quad[3].z = toSun.z * depthScale;
                    break;
                case 1:
                    c = -size * cos(angle);
                    s = size * sin(angle);
                    quad[0].x = depthScale * (toSun.x - c);
                    quad[0].y = depthScale * (toSun.y - s);
                    quad[0].z = toSun.z * depthScale;
                    quad[1].x = depthScale * (toSun.x - s);
                    quad[1].y = depthScale * (toSun.y + c);
                    quad[1].z = toSun.z * depthScale;
                    quad[2].x = depthScale * (toSun.x + c);
                    quad[2].y = depthScale * (toSun.y + s);
                    quad[2].z = toSun.z * depthScale;
                    quad[3].x = depthScale * (toSun.x + s);
                    quad[3].y = depthScale * (toSun.y - c);
                    quad[3].z = toSun.z * depthScale;
                    break;
                case 2:
                    quad[0].x = depthScale * (toSun.x - size);
                    quad[0].y = depthScale * (toSun.y - size);
                    quad[0].z = toSun.z * depthScale;
                    quad[1].x = depthScale * (toSun.x - size);
                    quad[1].y = depthScale * (toSun.y + size);
                    quad[1].z = toSun.z * depthScale;
                    quad[2].x = depthScale * (toSun.x + size);
                    quad[2].y = depthScale * (toSun.y + size);
                    quad[2].z = toSun.z * depthScale;
                    quad[3].x = depthScale * (toSun.x + size);
                    quad[3].y = depthScale * (toSun.y - size);
                    quad[3].z = toSun.z * depthScale;
                    break;
                case 3:
                    tilt = 3.1415925f * (2.0f * (lbl_3_bss_9978[0].x + lbl_3_bss_9978[0].y)) * fx->_3D4;
                    qSpin.x = 0.0f;
                    qSpin.y = 0.0f;
                    qSpin.z = SINF(tilt);
                    qSpin.w = COSF(tilt);
                    tilt = 3.141592502593994 * (0.5 * (fx->_3D0 * dist)) / halfDiag * 0.5;
                    s = SINF(tilt);
                    qTilt.x = axis.x * s;
                    qTilt.y = axis.y * s;
                    qTilt.z = axis.z * s;
                    qTilt.w = COSF(tilt);
                    PSQUATMultiply(&qTilt, &qSpin, &qTilt);
                    PSMTXQuat(rot, &qTilt);
                    k = 1.0f + fx->_3D8 * dist / halfDiag;
                    size = size * (invZoom * (k * k));
                    quad[0].z = 0.0f;
                    quad[1].z = 0.0f;
                    quad[2].z = 0.0f;
                    quad[3].z = 0.0f;
                    tilt = -lbl_3_bss_9978[0].z / 1280.0f;
                    quad[1].y = size * tilt;
                    quad[2].x = size * tilt;
                    quad[2].y = size * tilt;
                    quad[3].x = size * tilt;
                    quad[0].x = -size * tilt;
                    quad[0].y = -size * tilt;
                    quad[1].x = -size * tilt;
                    quad[3].y = -size * tilt;
                    for (i = 0; i < 4; i++) {
                        PSMTXMultVec(rot, (Vec*)&quad[i], (Vec*)&quad[i]);
                        quad[i].x = depthScale * (toSun.x + quad[i].x) + quad[i].x;
                        quad[i].y = depthScale * (toSun.y + quad[i].y) + quad[i].y;
                        quad[i].z = depthScale * (toSun.z + quad[i].z) + quad[i].z;
                    }
                    break;
                }
                sprite[0].pos = quad[0];
                sprite[1].pos = quad[1];
                sprite[2].pos = quad[2];
                sprite[3].pos = quad[3];
                sprite[0].u = 0;
                sprite[0].v = 0;
                sprite[1].u = 0;
                sprite[1].v = 0x400;
                sprite[2].u = 0x400;
                sprite[2].v = 0x400;
                sprite[3].u = 0x400;
                sprite[3].v = 0;
                sprite[0].color = alpha;
                sprite[1].color = alpha;
                sprite[2].color = alpha;
                sprite[3].color = alpha;
                DrawSprite_TexObj(sprite, fx->textures + (layer->texture << 5), 0);
            }
            off += 0x10;
        }
    }
}

// .text:0x000BC888 size:0x198 mapped:0x806FB91C
void fn_3_BC888(void) {
    SceneActor* actor;
    int flags;
    int i;
    Mtx rot;
    Vec pos;
    Vec vel;

    for (i = 0; i < 13; i++) {
        actor = hugeAnimStruct.actors[i];
        if (actor == NULL) {
            continue;
        }
        if (actor->_25D == 0) {
            actor->_279 = 0;
            continue;
        }
        PSMTXRotRad(rot, 'Y', actor->yaw);
        vel.x = lbl_3_bss_9964;
        vel.y = 0.0f;
        vel.z = lbl_3_data_12CB4;
        PSMTXMultVec(rot, &vel, &vel);
        flags = actor->_276 & 0x14;
        if (flags == 0x10 && (actor->_275 & 0x7F) == 6) {
            getAnimRelatedCoordinates(i, 0x22, (VecXYZ*)&pos);
            pos.y = 0.0f;
            fn_8003A550(i, &pos, &vel, actor->_25A == 0);
        }
        actor->_279 = (flags == 4);
        flags = actor->_276 & 0xA;
        if (flags == 8 && (actor->_275 & 0x7F) == 6) {
            getAnimRelatedCoordinates(i, 0x1E, (VecXYZ*)&pos);
            pos.y = 0.0f;
            fn_8003A550(i, &pos, &vel, actor->_25A);
        }
        actor->_279 |= (flags == 2) << 1;
    }
}

// .text:0x000BC850 size:0x38 mapped:0x806FB91C
void fn_3_BC850(int arg, int index) {
    fn_8003A688(arg, lbl_3_data_111C8[index][0], lbl_3_data_111C8[index][1]);
}

// .text:0x000BC6D8 size:0x178 mapped:0x806FB76C
void maybeFireworks(int a, int b, int index, int c) {
    SceneFxData* data = &lbl_3_data_111A8;
    SceneFireSlot* slot = data->slots;
    s32 stadiumWord = ((s32*)&g_UNK_StadiumDetails)[1];
    s32 savedWordC = slot->wordC;
    void* arg;

    data->slots[0].word0 = stadiumWord;
    data->slots[1].word0 = stadiumWord;
    slot->wordC = (s32)((f32)savedWordC * ((f32)data->tblA[index % 14] / 100000.0f));
    arg = data->tblB[index];
    if (arg == NULL) {
        arg = &data->tblD[lbl_3_bss_9968 & 0xF];
    }
    fn_80028628(a, b, &data->slots[0], data->tblC[index % 14], arg, &data->slots[1], c);
    lbl_3_bss_9968 += rand();
    slot->wordC = savedWordC;
    if (index == 13) {
        callSfx(0x2D9);
    } else if (index >= 4 && index <= 7) {
        callSfx(0x2D7);
    } else {
        callSfx(0x2D8);
    }
}

// .text:0x000BC2DC size:0x3FC mapped:0x806FB370
void animateDustCloudsBehindFielder_Runner(void) {
    SceneActor* actor;
    int i;
    Vec pos;
    FielderDash* dash;

    for (i = 0; i < 13; i++) {
        actor = hugeAnimStruct.actors[i];
        if (actor != NULL) {
            actor->_276 >>= 1;
            actor->_276 = (actor->_276 & 0x1F) << 3;
            getAnimRelatedCoordinates(i, 0x1E, (VecXYZ*)&pos);
            actor->_276 |= ((actor->pos.y - pos.y) < (f32)lbl_3_data_17000[actor->charId] / 100000.0f) << 1;
            getAnimRelatedCoordinates(i, 0x22, (VecXYZ*)&pos);
            actor->_276 |= ((actor->pos.y - pos.y) < (f32)lbl_3_data_17000[actor->charId] / 100000.0f) << 2;
        }
    }
    if (g_d_GameSettings.minigamesEnabled != 0) {
        dash = (FielderDash*)&g_FieldingLogic;
        for (i = 0; i < 4; i++) {
            actor = hugeAnimStruct.actors[i];
            if (actor != NULL && dash[i].sprintingState != 0 && i == dash[i].dashingFielderIndex) {
                actor->_276 |= 1;
            }
        }
    } else {
        dash = (FielderDash*)&g_FieldingLogic;
        for (i = 0; i < 9; i++) {
            actor = hugeAnimStruct.actors[i];
            if (actor != NULL && dash[i].sprintingState != 0 && i == dash[i].dashingFielderIndex) {
                actor->_276 |= 1;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        actor = hugeAnimStruct.actors[9 + i];
        if (actor != NULL && g_Runners[i].mashPercent >= 0.75f) {
            actor->_276 |= 1;
        }
    }
}

// .text:0x000BC274 size:0x68 mapped:0x806FB308
BOOL fn_3_BC274(SceneActor* actor, VecXYZ* a, VecXYZ* b) {
    return (a->y - b->y) < (f32)lbl_3_data_17000[actor->charId] / 100000.0f;
}

// .text:0x000BC25C size:0x18 mapped:0x806FB2F0
void fn_3_BC25C(void) {
    lbl_3_common_bss_35154.flags |= 0x40;
}

// .text:0x000BC224 size:0x38 mapped:0x806FB2B8
void fn_3_BC224(void) {
    removeGraphicsElementFromScene(lbl_3_common_bss_35154.sceneItem);
    lbl_3_common_bss_35154.sceneItem = NULL;
}

// .text:0x000BBF94 size:0x290 mapped:0x806FB028
void spriteAnimations(void) {
    u8 mode = g_GameLogic.gameStatus;
    int i;

    switch (mode) {
    case 0:
    case 3:
    case 4:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 15:
    case 16:
    case 17:
    case 18:
    case 24:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
    case 41:
        lbl_3_common_bss_35154.paused = 1;
        break;
    }
    if (mode < 0x1B) {
        animateDustCloudsBehindFielder_Runner();
    }
    mode = g_GameLogic.gameStatus;
    if (mode == 1 || (u8)(mode - 2) <= 1 || (u8)(mode - 0x13) <= 1 || mode == 0x16 || mode == 0x17) {
        fn_3_BC888();
    }
    if (lbl_3_common_bss_35154._470 != 0) {
        fn_3_15FB84(lbl_3_common_bss_35154._472[0], lbl_3_common_bss_35154._472[1], lbl_3_common_bss_35154._472[2], lbl_3_common_bss_35154._472[3], lbl_3_common_bss_35154._472[4]);
    }
    fn_3_169150();
    fn_8006C43C((void*)fn_3_168CD8);
    fn_8006C3F0((void*)fn_3_16892C);
    if (marioHandOnFire_endFireAnimation(TRUE)) {
        animatePitchersHandOnFire();
        if (fn_8004ABE0()) {
            playSoundEffect(0x1B6);
        }
    }
}

// .text:0x000BBBC4 size:0x3D0 mapped:0x806FAC58
void fn_3_BBBC4(void) {
    SceneEffect* effect = allocParticleEffect(fn_3_BA7F4, 0x80, 0, lbl_3_data_170D8[0], 1, 0x19);

    if (effect != NULL) {
        fn_3_BB454(effect);
    }
}

// .text:0x000BB7F4 size:0x3D0 mapped:0x806FA888
void fn_3_BB7F4(void) {
    SceneEffect* effect = allocParticleEffect(fn_3_BA7F4, 0x80, 0, lbl_3_data_170D8[0], 1, 0x19);

    if (effect != NULL) {
        fn_3_BB454(effect);
    }
}

// .text:0x000BB454 size:0x3A0 mapped:0x806FA4E8
void fn_3_BB454(SceneEffect* effect) {
    SceneParticle* p = effect->head;
    u32 i = 0;
    int n;

    do {
        p->_4A = i;
        p->_38 = (f32)lbl_3_data_170D8[3] / 100000.0f;
        p->_3C = (f32)lbl_3_data_170D8[4] / 100000.0f;
        fn_3_BB15C(p);
        n = lbl_3_data_170D8[0] / 10;
        p->_48 = ((i % 5) * n + rand() % n) * 2;
        i++;
        p = p->next;
    } while (p != NULL);
}

// .text:0x000BB15C size:0x2F8 mapped:0x806FA1F0
void fn_3_BB15C(SceneParticle* p) {
    int raw = lbl_3_data_170D8[5];
    u8 base = raw;
    u8 range;
    f32 speed;
    f32 angle = 0.0f;
    f32 s;
    f32 c;

    p->x = (f32)(p->_4A * 2) / (f32)lbl_3_data_170D8[0] - 1.0f;
    p->y = -1.0f;
    p->size = 50.0f * ((f32)rand() / 32767.0f) + 50.0f;
    s = SINF(angle);
    c = COSF(angle);
    p->velX = s * (f32)lbl_3_data_170D8[1] / 100000.0f;
    p->velY = c * (f32)lbl_3_data_170D8[1] / 100000.0f;
    p->velZ = 0.0f;
    p->_24 = 0.0f;
    p->_20 = 0.0f;
    p->_1C = 0.0f;
    speed = (f32)lbl_3_data_170D8[2] / 100000.0f;
    p->_28 = speed * ((f32)rand() / 32767.0f);
    p->_2C = speed * ((f32)rand() / 32767.0f);
    p->_30 = speed * ((f32)rand() / 32767.0f);
    p->_47 = 0xFF;
    p->_43 = 0xFF;
    range = 0xFF - raw;
    p->_41 = base + rand() % range;
    p->_42 = base + rand() % range;
    p->_44 = base + rand() % range;
    p->_45 = base + rand() % range;
    p->_46 = base + rand() % range;
}

// .text:0x000BB07C size:0xE0 mapped:0x806FA110
void fn_3_BB07C(SceneParticle* p, f32 angle) {
    f32 c;
    f32 s;
    f32 rad = 0.017453292f * angle;

    s = SINF(rad);
    c = COSF(rad);

    p->velX = s * (f32)lbl_3_data_170D8[1] / 100000.0f;
    p->velY = c * (f32)lbl_3_data_170D8[1] / 100000.0f;
    p->velZ = 0.0f;
}

// .text:0x000BA7F4 size:0x888 mapped:0x806F9888
int fn_3_BA7F4(SceneEffect* effect) {
    Vec up = { 0.0f, 1.0f, 0.0f };
    Vec dir;
    SceneParticle* p;
    SceneParticle* head;
    SceneSortEntry* sorted;
    SceneSortEntry* e;
    int count;
    int remaining;
    f32 angle;
    f32 delta;
    f32 rad;
    f32 s;
    f32 c;

    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);

    head = effect->head;
    count = effect->count;
    sorted = _OSAllocFromHeap(0x20, count * 8);
    e = sorted;
    for (p = head; p != NULL; p = p->next) {
        e->p = p;
        e->depth = p->size;
        e++;
    }
    fn_800246D4(fn_3_BA174, sorted, sorted, 8, count);
    head = sorted[0].p;
    e = sorted;
    remaining = count;
    while (--remaining != 0) {
        e->p->next = e[1].p;
        e++;
    }
    e->p->next = NULL;
    fn_800ACFB0(sorted);
    effect->head = head;

    p = head;
    do {
        if (p->_48 > 0) {
            p->_48--;
        } else {
            fn_3_BA538((SceneQuad*)p);
            PSVECAdd((Vec*)&p->velX, (Vec*)&p->x, (Vec*)&p->x);
            PSVECAdd((Vec*)&p->_28, (Vec*)&p->_1C, (Vec*)&p->_1C);
            if (fabs(p->x) > 1.0) {
                p->x = fabs(p->x) / p->x;
                p->velX = p->velX * -1.0f;
            } else if (rand() % 5 == 0) {
                memcpy(&dir, &p->velX, sizeof(Vec));
                PSVECNormalize(&dir, &dir);
                angle = 57.29578f * (f32)acos(PSVECDotProduct(&up, &dir));
                if (dir.x < 0.0f) {
                    angle = angle * -1.0f;
                }
                delta = 20.0 * (2.0 * ((f32)rand() / 32767.0f - 0.5));
                if (fabs(angle + delta) > 20.0) {
                    angle = 20.0 * (fabs(angle) / angle);
                } else {
                    angle = angle + delta;
                }
                rad = 0.017453292f * angle;
                s = SINF(rad);
                c = COSF(rad);
                p->velX = s * (f32)lbl_3_data_170D8[1] / 100000.0f;
                p->velY = c * (f32)lbl_3_data_170D8[1] / 100000.0f;
                p->velZ = 0.0f;
            }
            if (p->y > 1.0f) {
                fn_3_BB15C(p);
            }
        }
        p = p->next;
    } while (p != NULL);

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetCullMode(GX_CULL_NONE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXLoadPosMtxImm(fn_80052768_getCamera(0)->view, 0);
    GXSetCurrentMtx(0);
    GXSetProjection(fn_80052768_getCamera(0)->proj, GX_PERSPECTIVE);
    return 0;
}

// .text:0x000BA538 size:0x2BC mapped:0x806F95CC
void fn_3_BA538(SceneQuad* quad) {
    Control ctrl;
    VecXYZ verts[4];
    Mtx mtx;
    Mtx44 proj;
    f32 halfW = 0.5f * quad->width;
    f32 halfH = 0.5f * quad->height;
    int i;

    ctrl.type = 0;
    verts[0].x = -halfW;
    verts[0].y = -halfH;
    verts[0].z = 0.0f;
    verts[1].x = halfW;
    verts[1].y = -halfH;
    verts[1].z = 0.0f;
    verts[2].x = halfW;
    verts[2].y = halfH;
    verts[2].z = 0.0f;
    verts[3].x = -halfW;
    verts[3].y = halfH;
    verts[3].z = 0.0f;
    CTRLSetRotation(&ctrl, quad->rotX, quad->rotY, quad->rotZ);
    CTRLSetTranslation(&ctrl, 0.5f * quad->x * 0.5f * quad->scale, 0.35f * quad->y * 0.5f * quad->scale, -1.5f);
    CTRLBuildMatrix(&ctrl, mtx);
    GXLoadPosMtxImm(mtx, 0);
    GXSetCurrentMtx(0);
    C_MTXOrtho(proj, quad->scale * -0.175f, quad->scale * 0.175f, quad->scale * 0.25f, quad->scale * -0.25f, 1.0f, 512.0f);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    GXSetCullMode(GX_CULL_BACK);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    for (i = 0; i < 4; i++) {
        GXPosition3f32(verts[i].x, verts[i].y, verts[i].z);
        GXColor1u32(quad->colorFront);
    }
    GXSetCullMode(GX_CULL_FRONT);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    for (i = 0; i < 4; i++) {
        GXPosition3f32(verts[i].x, verts[i].y, verts[i].z);
        GXColor1u32(quad->colorBack);
    }
}
