#define SQRT2_LINKAGE static
#include "game/stadium/sta_c2.h"
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

typedef struct _PalaceMaterialFlags {
    /*0x00*/ u8 _00[0x74];
    /*0x74*/ u32 flags;
} PalaceMaterialFlags;

typedef struct _PalaceModelLevel4 {
    /*0x00*/ u8 _00[4];
    /*0x04*/ PalaceMaterialFlags* next;
} PalaceModelLevel4;

typedef struct _PalaceModelLevel3 {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ PalaceModelLevel4* next;
} PalaceModelLevel3;

typedef struct _PalaceModelLevel2 {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ PalaceModelLevel3* next;
} PalaceModelLevel2;

typedef struct _PalaceModelLevel1 {
    /*0x00*/ PalaceModelLevel2* next;
    /*0x04*/ u8 _04[8];
    /*0x0C*/ u8* ctrlBlock;
} PalaceModelLevel1;

typedef struct _PalaceModelRoot {
    /*0x00*/ u8 _00[0x18];
    /*0x18*/ PalaceModelLevel1* next;
} PalaceModelRoot;

typedef struct _PalaceGfxObject {
    /*0x00*/ u8 _00[0x48];
    /*0x48*/ Vec pos;
    /*0x54*/ u32 flags;
    /*0x58*/ u8 _58[4];
    /*0x5C*/ u32 frameIndex;
    /*0x60*/ u8 _60[9];
    /*0x69*/ u8 scale;
} PalaceGfxObject;

typedef struct _PalaceGfxScene {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ u16 firstHandle;
} PalaceGfxScene;

typedef struct _PalaceAnimObject {
    /*0x00*/ u8 _00[0x34];
    /*0x34*/ Vec pos;
} PalaceAnimObject;

extern u8 hugeAnimStruct[0x3154];
extern u8 lbl_80366158[0x30];
extern u16 stadiumHazardSoundIDs[16];
extern u8 stadiumHazardSoundFxRelated[0xB4];
extern u8 lbl_3_data_84B8[0x3C];

static u32 lbl_3_bss_ADD0[12];
static u32 lbl_3_bss_A8D0[320];
static ChainChompPhysicsParams lbl_3_bss_A8A8;
static PalaceGfxScene* lbl_3_bss_A8A4;
static u8 lbl_3_bss_A898[12];
static f32 lbl_3_bss_A820[30];
static u8 lbl_3_bss_A81C;
static u32 lbl_3_bss_A034[506];
static f32 lbl_3_bss_A030;
static u8 lbl_3_bss_A02D;
static u8 lbl_3_bss_A02C;
static u8 lbl_3_bss_A02B;
static u8 lbl_3_bss_A02A;
static u8 lbl_3_bss_A029;
static u8 lbl_3_bss_A028;
static u8 lbl_3_bss_A027;
static u8 lbl_3_bss_A026;
static u8 lbl_3_bss_A025;
static u8 lbl_3_bss_A024;
static u8 lbl_3_bss_A023;
static u8 lbl_3_bss_A022;
static u8 pad_A021;
static u8 lbl_3_bss_A020;
static const u8* lbl_3_bss_A01C;
static u8 lbl_3_bss_A018;

typedef struct _PalaceObjControl {
    Control ctrl;
    u8 _34[0x44 - sizeof(Control)];
} PalaceObjControl;

typedef struct _PalaceSandStarPlacement {
    /*0x00*/ Vec pos;
    /*0x0C*/ u8 usedFlag;
    /*0x0D*/ u8 _0D;
    /*0x0E*/ u8 group;
    /*0x0F*/ u8 _0F;
} PalaceSandStarPlacement;

typedef struct _PalaceSandStarTable {
    /*0x000*/ PalaceSandStarPlacement entries[22];
    /*0x160*/ Vec _160;
    /*0x16C*/ u8 _16C[4];
    /*0x170*/ f32 _170[8];
    /*0x190*/ u32 _190;
    /*0x194*/ u8 objectTypes[26];
} PalaceSandStarTable; // size: 0x1B0

typedef struct _PalaceSlotPlacement {
    /*0x00*/ f32 x;
    /*0x04*/ f32 y;
    /*0x08*/ f32 z;
    /*0x0C*/ u8 usedFlag;
    /*0x0D*/ u8 _0D;
    /*0x0E*/ u8 group;
    /*0x0F*/ u8 _0F;
    /*0x10*/ f32 _10[3];
} PalaceSlotPlacement; // size: 0x1C

typedef struct _PalaceActEffect {
    /*0x00*/ u32 file;
    /*0x04*/ u8 _04[0x28];
    /*0x2C*/ u32 srcFile;
    /*0x30*/ u8 _30[0x2C];
} PalaceActEffect; // size: 0x5C

typedef struct _PalaceSandPlacement {
    /*0x00*/ Vec pos;
    /*0x0C*/ u8 kind;
    /*0x0D*/ u8 _0D[3];
    /*0x10*/ Vec scale;
    /*0x1C*/ f32 rotY;
} PalaceSandPlacement; // size: 0x20

extern UIRecordDescriptor lbl_3_data_10D3C[];
extern void fn_80035750(void* a, void* b, int c);

typedef struct _PalaceIdObj {
    /*0x00*/ u8 _00[0xC0];
    /*0xC0*/ u8 id;
} PalaceIdObj;

typedef struct _PalaceLinkedObj {
    /*0x00*/ u8 _00[0xA0];
    /*0xA0*/ StadiumObject* nado;
    /*0xA4*/ PalaceIdObj* other;
    /*0xA8*/ u8 _A8[4];
    /*0xAC*/ u8 animPhase;
} PalaceLinkedObj;

static const u8 lbl_3_rodata_2498[4] = {0x80, 0x20, 0x00, 0x00};
static const u8 lbl_3_rodata_249C[4] = {'F', 'F', 'F', 0};
static const Vec lbl_3_rodata_24A0[4] = {
    {-49.05f, -42.19f, 131.5f}, {49.05f, -42.19f, 131.5f}, {73.5f, -42.19f, 108.5f}, {-73.5f, -42.19f, 108.5f}};
static const Vec lbl_3_rodata_24D0 = {60.0f, 0.0f, 40.0f};
static const Vec lbl_3_rodata_24DC = {-60.0f, 0.0f, 40.0f};
static const Vec lbl_3_rodata_24E8[3] = {{-4.5f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}};
static const Vec const_zeroYawAxis = {1.0f, 0.0f, 0.0f};
static const Vec lbl_3_rodata_2520 = {1.0f, 0.0f, 0.0f};
static const Vec lbl_3_rodata_252C[2] = {{1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}};
static const Vec const_chompHitboxAxis = {0.0f, 1.0f, 0.0f};
static const Vec lbl_3_rodata_25BC = {0.0f, 0.0f, 0.0f};
static const Vec lbl_3_rodata_25C8 = {1.0f, 0.0f, 0.0f};
static const Vec lbl_3_rodata_25D4 = {0.0f, 1.0f, 0.0f};
static const Vec lbl_3_rodata_25E0[2] = {{0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}};
static const Vec lbl_3_rodata_25F8 = {0.0f, 1.0f, 0.0f};
static const Vec lbl_3_rodata_2604[5] = {
    {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}};
static const Vec lbl_3_rodata_2640 = {0.0f, 1.0f, 0.0f};
static const Vec lbl_3_rodata_264C = {0.0f, 0.0f, 0.0f};
static const f32 const_pi_or_180 = 0.017453292f;

static SND_VOICEID lbl_3_data_182C0 = -1;
static int activeStadiumEmitterID = -1;

static PalaceChompPlacement chompPlacementConfig[3] = {
    { { 55.0f, 0.0f, 40.0f }, 0, 1, 1, 0, { 0.0f, 180.0f, 0.0f }, { 0.0f, 180.0f, 0.0f }, 160.0f, 120.0f, 1, 0, 0, 0 },
    { { -55.0f, 0.0f, 40.0f }, 0, 1, 2, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 290.0f, 100.0f, 0, 0, 0, 0 },
    { { 0.0f, 0.0f, 0.0f }, 0xD, 0, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0, 0, 0, 0 },
};

static PalaceTornadoPlacement TornadoPlacementConfig[6] = {
    { { 28.5f, 7.0f, 37.5f }, 3, 1, 1, 0, 30.0f, 1.0f, 1.0f, 1.0f, -60.0f, 45.0f, 60.0f, 10.0f, 4.0f },
    { { -28.5f, 7.0f, 37.5f }, 3, 1, 3, 0, 330.0f, 1.0f, 1.0f, 1.0f, -60.0f, -10.0f, 60.0f, -45.0f, 4.0f },
    { { 0.0f, 0.0f, 0.0f }, 0xD, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { { 0.0f, 0.0f, 0.0f }, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { { 0.0f, 0.0f, 0.0f }, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { { 0.0f, 0.0f, 0.0f }, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
};

static PalaceSlotPlacement lbl_3_data_1849C[11] = {
    { 0.0f, -5.0f, 40.0f, 6, 1, 1, 0, 10.0f, 0.0f, 360.0f },
    { 20.0f, -5.0f, 40.0f, 6, 1, 2, 0, 10.0f, 0.0f, 360.0f },
    { -20.0f, -5.0f, 40.0f, 6, 1, 3, 0, 10.0f, 0.0f, 360.0f },
    { 0.0f, 0.0f, 0.0f, 0xD, 0, 0, 0, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f },
};

static PalaceSandPlacement lbl_3_data_185D0[11] = {
    { { 37.4f, 0.0f, 8.0f }, 7, 1, 1, 0, { 1.0f, 1.0f, 1.0f }, -35.0f },
    { { 22.5f, 0.0f, -7.3f }, 7, 1, 1, 0, { 1.0f, 1.0f, 1.0f }, -25.0f },
    { { -22.5f, 0.0f, -7.3f }, 7, 1, 1, 0, { 1.0f, 1.0f, 1.0f }, 20.0f },
    { { -37.4f, 0.0f, 8.0f }, 7, 1, 1, 0, { 1.0f, 1.0f, 1.0f }, 0.0f },
    { { -43.34f, -3.6f, 87.797f }, 7, 1, 1, 0, { 1.0f, 0.85f, 1.0f }, -25.0f },
    { { -32.055f, -3.6f, 101.771f }, 7, 1, 1, 0, { 1.0f, 0.8f, 1.0f }, -15.0f },
    { { 31.884f, -3.6f, 101.246f }, 7, 1, 1, 0, { 1.0f, 0.8f, 1.0f }, 20.0f },
    { { 43.626f, -3.6f, 87.915f }, 7, 1, 1, 0, { 1.0f, 0.88f, 1.0f }, 25.0f },
    { { 0.0f, 0.0f, 0.0f }, 0xD, 0, 0, 0, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 0.0f, 0.0f, 0.0f }, 0, 0, 0, 0, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 0.0f, 0.0f, 0.0f }, 0, 0, 0, 0, { 0.0f, 0.0f, 0.0f }, 0.0f },
};

static PalaceSandStarTable sandStarPlacementConfig = {
    {
        { { 0.0f, 0.15f, 60.0f }, 8, 1, 1, 0 },
        { { 20.0f, 0.15f, 60.0f }, 8, 1, 2, 0 },
        { { -20.0f, 0.15f, 60.0f }, 8, 1, 3, 0 },
        { { 0.0f, 0.0f, 0.0f }, 0xD, 0, 0, 0 },
        { { 0.0f, 0.0f, 0.0f }, 0, 0, 0, 0 },
        { { 0.0f, 0.0f, 0.0f }, 0, 0, 0, 0 },
        { { 0.0f, 0.0f, 0.0f }, 0, 0, 0, 0 },
        { { 0.0f, 0.0f, 0.0f }, 0, 0, 0, 0 },
        { { 0.0f, 0.0f, 0.0f }, 0, 0, 0, 0 },
        { { 0.0f, 0.0f, 0.0f }, 0, 0, 0, 0 },
        { { 0.0f, 0.0f, 0.0f }, 0, 0, 0, 0 },
        { { 0.0f, 0.0f, 0.0f }, 0xB, 1, 1, 0 },
        { { 0.0f, 0.0f, 0.0f }, 0xD, 0, 0, 0 },
        { { 0.0f, 0.0f, 0.0f }, 0, 0, 0, 0 },
        { { 0.0f, 0.0f, 0.0f }, 0, 0, 0, 0 },
        { { 0.0f, 0.0f, 0.0f }, 0, 0, 0, 0 },
        { { 0.0f, 0.0f, 0.0f }, 0, 0, 0, 0 },
        { { 0.0f, 0.0f, 0.0f }, 0, 0, 0, 0 },
        { { 0.0f, 0.0f, 0.0f }, 0, 0, 0, 0 },
        { { 0.0f, 0.0f, 0.0f }, 0, 0, 0, 0 },
        { { 0.0f, 0.0f, 0.0f }, 0, 0, 0, 0 },
        { { 0.0f, 0.0f, 0.0f }, 0, 0, 0, 0 },
    },
    { 0.0f, 0.0f, 10.0f },
    { 0, 1, 1, 0 },
    { 0.0f, -90.0f, 0.0f, 30.0f, -120.0f, 0.0f, 0.0f, 360.0f },
    0,
    { 1, 2, 2, 4, 2, 2, 2, 2, 4, 2, 2, 2, 2, 6, 6, 8, 8, 9, 8, 9, 8, 8, 8, 9, 0, 0 },
};

static f32 lbl_3_data_188E0[2] = { 0.1f, 0.0f };

// .text:0x000CB8A8 size:0x1F4 mapped:0x8070A93C
void fn_3_CB8A8(StadiumObject* obj) {
    switch (obj->_CA) {
    case 0:
        actorRelated(obj->effect, 0, 2);
        fn_3_CC1D4();
        break;
    case 1:
        actorRelated(obj->effect, 0, 3);
        break;
    case 3:
        actorRelated(obj->effect, 0, 4);
        break;
    default:
        actorRelated(obj->effect, 0, 1);
        break;
    }
}

// .text:0x000CBA9C size:0x60 mapped:0x8070AB30
void fn_3_CBA9C(StadiumObject* obj) {
    StadiumModel* model = obj->model;
    PalaceMaterialFlags* mat = ((PalaceModelRoot*)model->root)->next->next->next->next->next;

    if (obj->_CA == 0) {
        mat->flags &= ~0x1FFF;
        mat->flags |= 3;
    } else {
        mat->flags &= ~0x1FFF;
        mat->flags |= 2;
    }
}

// .text:0x000CBAFC size:0x11C mapped:0x8070AB90
void fn_3_CBAFC(StadiumObject* obj) {
    StadiumLink* links = obj->links;
    Mtx m;
    Vec axis = lbl_3_rodata_2640;
    Vec force = lbl_3_rodata_264C;
    Vec v;

    PSMTXRotAxisRad(m, &axis, const_pi_or_180 * obj->yaw);
    PSMTXMultVec(m, &lbl_3_rodata_24E8[0], &v);
    PSVECAdd(&v, &obj->pos, &v);
    v.y = v.y + 4.5;
    links[3].pos = v;
    links[3].prevPos = links[3].pos;
    chainChomp_simulateAndCollide(&lbl_3_bss_A8A8, obj->links, 4, &force, obj);
}

// .text:0x000CBC18 size:0x368 mapped:0x8070ACAC
void fn_3_CBC18(StadiumObject* obj) {
    obj->pos.x = g_Minigame._1AE0;
    obj->pos.y = g_Minigame._1AE4;
    obj->pos.z = g_Minigame._1AE8;
    obj->yaw = -(57.29578f * shortAngleToRad(g_Minigame._1AF8));
    CTRLSetTranslation((Control*)obj, obj->pos.x, -obj->pos.y, obj->pos.z);
    CTRLSetRotation((Control*)obj, 0.0f, obj->yaw, 0.0f);
    fn_3_CBAFC(obj);
    if (g_Minigame._1B19 != obj->_CA) {
        obj->_CA = g_Minigame._1B19;
        fn_3_CB8A8(obj);
        palaceStadiumObjTransformationAndPhysics(obj);
    }
}

// .text:0x000CBF80 size:0x254 mapped:0x8070B014
void palaceStadiumObjTransformationAndPhysics(StadiumObject* obj) {
    Vec v;
    Vec w;
    Mtx m;
    PalaceObjControl ctrl;
    int i;
    u32 j;
    f32 t;
    f32 a;
    f32 dz;

    v = lbl_3_rodata_24E8[0];
    v.y = -4.5f;
    ctrl.ctrl.type = 0;
    CTRLSetRotation(&ctrl.ctrl, 0.0f, obj->yaw, 0.0f);
    CTRLBuildMatrix(&ctrl.ctrl, m);
    PSMTXMultVec(m, &v, &v);
    v.y *= -1.0f;
    v.x = v.x + obj->pos.x;
    v.y = v.y + obj->pos.y;
    v.z = v.z + obj->pos.z;
    w = v;
    for (i = 4; i != 0; i--) {
        obj->links[i - 1].pos.x = w.x;
        obj->links[i - 1].pos.y = w.y;
        w.y = w.y - 2.4f;
        obj->links[i - 1].pos.z = w.z;
        if ((f64)w.y - (f64)0.15f < 0.0) {
            t = (f32)((f64)0.15f - w.y) / 2.4f;
            a = acos(t);
            t = cos(a);
            dz = 2.4f * t;
            w.y = 0.15f;
            w.z = w.z + dz;
        }
    }
    for (j = 0; j < 4; j++) {
        obj->links[j].prevPos = obj->links[j].pos;
        memset(&obj->links[j].vel, 0, sizeof(Vec));
        memset(&obj->links[j].accel, 0, sizeof(Vec));
    }
}

// .text:0x000CC1D4 size:0x180 mapped:0x8070B268
void fn_3_CC1D4(void) {
    Mtx m;
    Vec v;
    StadiumObject* obj;
    ACTActor* actor;
    u32 i;
    u32 first;
    f32 zero;
    u32 count;
    f32 ang;

    ang = -shortAngleToRad(g_Minigame._1AF8);
    PSMTXRotRad(m, 'Y', const_pi_or_180 * ang);
    v.x = 4.5f;
    v.y = 9.0f;
    v.z = 0.0f;
    PSMTXMultVec(m, &v, &v);
    count = stadiumObjectCollision.objectCount;
    obj = stadiumObjectCollision.objects;
    for (first = 0; first < count; first++, obj++) {
        if (obj->_9D[0] == 1) {
            break;
        }
    }
    zero = 0.0f;
    for (i = first; i < first + 3; i++) {
        obj = &stadiumObjectCollision.objects[i];
        CTRLSetTranslation((Control*)obj, g_Minigame._1AE0 + v.x, g_Minigame._1AE4 - v.y, g_Minigame._1AE8 + v.z);
        actor = (ACTActor*)obj->model;
        ((PalaceSlotObject*)obj)->animPhase = i % 3 * 30;
        obj->pos.x = zero;
        actor->animFrame = obj->pos.x;
        actor->applyFrame = 1;
        setActorAnimFrame(actor->actor, actor->animFrame);
    }
}

// .text:0x000CC354 size:0xE4 mapped:0x8070B3E8
void fn_3_CC354(StadiumLink* links) {
    StadiumLink* link = links;
    u32 i;

    if (links != NULL) {
        for (i = 0; i < 4; i++, link++) {
            if (i == 3) {
                link->weight = lbl_3_data_188E0[0];
                link->radius = 0.504375f;
                link->pinned = 1;
            } else {
                link->weight = lbl_3_data_188E0[0];
                link->radius = 0.504375f;
            }
            link->mobility = 1.0f / link->weight;
            memset(&link->pos, 0, 0x18);
            memset(&link->vel, 0, sizeof(Vec));
            memset(&link->accel, 0, sizeof(Vec));
        }
    }
}

static void palaceInitChainParams(ChainChompPhysicsParams* params) {
    f32 dt;

    params->restLength = 1.755f;
    params->restitution = 0.5f;
    params->stiffness = 300.0f;
    params->damping = 20.0f;
    params->groundFriction = 1.5f;
    params->dragCoefficient = 0.001f;
    params->solverIterations = 8;
    dt = 1.0f / params->solverIterations;
    dt = dt / 60.0f;
    params->externalForceScale = dt;
    params->dampingA = dt * dt;
    params->dampingB = 1.0f / (2.0f * dt);
}

// .text:0x000CC438 size:0x18C mapped:0x8070B4CC
void fn_3_CC438(void) {
    palaceInitChainParams(&lbl_3_bss_A8A8);
    fn_3_CC354((StadiumLink*)lbl_3_bss_A8D0);
}

// .text:0x000CC5C4 size:0x258 mapped:0x8070B658
void mPalaceObjHandling(StadiumObject* obj) {
    obj->_CA = g_Minigame._1B19;
    actorRelated(obj->effect, 0, 2);
    obj->_CB[0] = obj->_CA;
    obj->hasShadow = 1;
    ((Control*)obj)->type = 0;
    CTRLSetScale((Control*)obj, 0.75f, 0.75f, 0.75f);
    obj->pos.x = g_Minigame._1AE0;
    obj->pos.y = g_Minigame._1AE4;
    obj->pos.z = g_Minigame._1AE8;
    obj->yaw = shortAngleToRad(g_Minigame._1AF8);
    CTRLSetRotation((Control*)obj, 0.0f, obj->yaw, 0.0f);
    CTRLSetTranslation((Control*)obj, obj->pos.x, -obj->pos.y, obj->pos.z);
    fn_3_CC438();
    palaceStadiumObjTransformationAndPhysics(obj);
}

// .text:0x000CC81C size:0x408 mapped:0x8070B8B0
void maybeChainChompSprintCTRLRelated(void) {
    StadiumObject* obj;
    u32 i;
    u32 count;
    PalaceHazeEmitter* emitter;

    count = stadiumObjectCollision.objectCount;
    obj = stadiumObjectCollision.objects;
    for (i = 0; i < count; i++, obj++) {
        if (obj->_9D[0] == 0) {
            mPalaceObjHandling(obj);
            break;
        }
    }
    fn_3_CC1D4();
    for (i = 0; i < 4; i++) {
        emitter = allocParticleEffect((void*)fn_3_CDFA4, 0x80, 0, 0x15, 1, 0);
        if (emitter != NULL) {
            palaceHazeTextureMaybe(emitter, i);
        }
    }
}

// .text:0x000CCC24 size:0xD34 mapped:0x8070BCB8
void palaceMinigameObjectLoading(void** files, u32* ids) {
    u8** animTable = (u8**)(hugeAnimStruct + 0x6C);
    PalaceSandPlacement* place = lbl_3_data_185D0;
    StadiumObject* obj;
    StadiumObject* o;
    StadiumLink* link;
    u8 done = FALSE;
    u32 sandCount;
    u32 propCount;
    u32 idx;
    u32 chompIdx;
    u32 firstProp;
    u32 i;
    u32 j;
    u32 k;
    u32 shadowBit;

    for (sandCount = 0; sandCount < 10; sandCount++) {
        if (place[sandCount].kind == 0xD) {
            break;
        }
    }
    propCount = sandCount + 5;
    stadiumObjectCollision.propCount = propCount;
    *animTable = ActorObjectInitTable(propCount);

    animateBallRelated(*animTable, 0, 0, files[ids[1]], 0, 0);
    idx = 1;
    for (i = 0; i < 3; i++) {
        animateBallRelated(*animTable, idx, idx, files[ids[3]], 0, 0);
        actorSetAnimBank((ACTActor*)(*animTable + idx * 0x90 + 0x34), (u32)files[ids[3] + 2]);
        idx++;
    }
    animateBallRelated(*animTable, idx, idx, files[ids[4]], 0, 0);
    chompIdx = idx;
    idx++;
    firstProp = idx;
    for (i = 0; i < sandCount; i++) {
        animateBallRelated(*animTable, idx, idx, files[ids[8]], 0, 0);
        actorSetAnimBank((ACTActor*)(*animTable + idx * 0x90 + 0x34), (u32)files[ids[8] + 2]);
        idx++;
    }
    for (i = 0; i < propCount; i++) {
        fn_800BD548(*animTable + i * 0x90 + 0x34, 4, stadiumObjectCollision.lights[0],
                    stadiumObjectCollision.lights[1], stadiumObjectCollision.lights[2],
                    stadiumObjectCollision.lights[3]);
    }
    if (files[ids[15]] != NULL && files[ids[17]] != NULL) {
        adjustInternalPointers(files[ids[15]]);
        ACTActorRelated(files[ids[15]], *animTable + 0x34);
        lbl_3_bss_A034[460] = (u32)files[ids[17]];
        actRelated(files[ids[15]], &lbl_3_bss_A034[460]);
        actorRelated(&lbl_3_bss_A034[460], 0, 1);
    }
    fn_80035750(files[ids[25]], files[ids[24]], 5);
    lbl_3_bss_A8A4 = (PalaceGfxScene*)insertGraphicDrawingFunction(fn_3_CE954, 2);
    addGraphicsElementToScene((DrawingSceneStruct*)lbl_3_bss_A8A4, lbl_3_data_10D3C);
    fn_3_D511C();

    stadiumObjectCollision.objectCount = 0x43;
    stadiumObjectCollision.objects = _OSAllocFromHeap(0x20, 0x3CB8);
    stadiumObjectCollision.objectsRelated = _OSAllocFromHeap(0x20, 0x3CB8);
    obj = stadiumObjectCollision.objects;
    memset(obj, 0, 0x28D4);
    lbl_3_bss_A02C = 0;
    obj->links = (StadiumLink*)lbl_3_bss_A8D0;
    obj->model = (StadiumModel*)(*animTable + 0x34);
    obj->triangles = files[ids[13]];
    obj->callback = (void (*)(void))fn_3_CBC18;
    obj->func = NULL;
    obj->_90b1 = 0;
    obj->fadeByDepth = 1;
    obj->_9C = 0;
    obj->alpha = 0xFF;
    obj->preDraw = fn_3_CBA9C;
    obj->effect = (StadiumObjectEffect*)&lbl_3_bss_A034[460];
    obj->animActive = 0;
    obj->animIndex = -1;
    obj->drawPass = 1;
    mPalaceObjHandling(obj);
    ((Control*)obj)->type = 0;
    obj->_CA = 0xFF;
    lbl_3_bss_A02D++;

    o = obj + 1;
    for (i = 0; i < 3; i++) {
        o->_9D[0] = 1;
        o->model = (StadiumModel*)(*animTable + (i + 1) * 0x90 + 0x34);
        o->triangles = NULL;
        o->callback = (void (*)(void))fn_3_D1848;
        o->func = NULL;
        o->hasShadow = 0;
        o->_90b1 = 0;
        ((PalaceSpinObj*)o)->rate = ((ACTActor*)o->model)->animSpeed;
        o->fadeByDepth = 0;
        ((Control*)o)->type = 0;
        CTRLSetScale((Control*)o, 0.75f, 0.75f, 0.75f);
        o->alpha = 0xFF;
        o->preDraw = applyTransformationToPalaceObjs;
        o->effect = NULL;
        o->animActive = 0;
        o->animIndex = -1;
        o->drawPass = 1;
        ((PalaceSpinObj*)o)->stateFlag = &stadiumObjectCollision.objects->_CA;
        ((PalaceSpinObj*)o)->timer = i % 3 * 30;
        ((PalaceSpinObj*)o)->_AD = 0;
        o->_9C = i;
        idx++;
        o++;
    }

    link = (StadiumLink*)lbl_3_bss_A8D0;
    for (i = 0; i < 3; i++) {
        o->anchorA = link;
        o->anchorB = (StadiumLink*)lbl_3_bss_A8D0 + (i + 1);
        o->_9D[0] = 2;
        o->model = (StadiumModel*)(*animTable + chompIdx * 0x90 + 0x34);
        o->triangles = NULL;
        o->callback = (void (*)(void))maybePalaceCTRLRelated;
        o->func = NULL;
        o->hasShadow = 1;
        o->_90b1 = 0;
        o->fadeByDepth = 1;
        ((Control*)o)->type = 0;
        memset(&o->pos, 0, sizeof(Vec));
        o->alpha = 0xFF;
        o->preDraw = (void (*)(StadiumObject*))fn_3_D127C;
        o->effect = NULL;
        o->animActive = 0;
        o->animIndex = -1;
        o->drawPass = 1;
        o->_9C = i;
        idx++;
        link++;
        o++;
    }

    j = 0;
    k = 0;
    do {
        if (place->kind == 0xD) {
            done = TRUE;
        }
        if (done) {
            for (i = j; i < 11; i++) {
                lbl_3_data_185D0[i].kind = 0xD;
            }
            break;
        }
        o->_9D[0] = place->kind;
        *(s32*)&o->pos.x = k;
        o->model = (StadiumModel*)(*animTable + (firstProp + j) * 0x90 + 0x34);
        o->triangles = NULL;
        o->callback = (void (*)(void))fn_3_CFA8C;
        o->func = NULL;
        o->hasShadow = 1;
        shadowBit = 0;
        if (o->hasShadow && o->triangles != NULL) {
            shadowBit = 1;
        }
        o->_90b1 = shadowBit;
        ((Control*)o)->type = 0;
        CTRLSetScale((Control*)o, place->scale.x, place->scale.y, place->scale.z);
        CTRLSetTranslation((Control*)o, place->pos.x, place->pos.y, place->pos.z);
        CTRLSetRotation((Control*)o, 0.0f, -place->rotY, 0.0f);
        o->fadeByDepth = 0;
        j++;
        o->alpha = 0xFF;
        done = FALSE;
        place++;
        o->effect = NULL;
        k += 30;
        idx++;
        o->preDraw = (void (*)(StadiumObject*))fn_3_CFA88;
        o->animActive = 0;
        o->animIndex = -1;
        o->drawPass = 1;
        o++;
    } while (j < 10);

    for (i = idx; i < stadiumObjectCollision.objectCount; i++) {
        o->_9D[0] = 0xFF;
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
    stadiumObjectCollision.vertexDataArray = NULL;
    fn_3_B97C8(fn_3_CD958);
}

// .text:0x000CD958 size:0x10 mapped:0x8070C9EC
void fn_3_CD958(void) {
    lbl_3_bss_A81C = 1;
}

// .text:0x000CD968 size:0x1E0 mapped:0x8070C9FC
BOOL fn_3_CD968(Vec* p, f32 w, f32 h) {
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
        return 0;
    }
    halfW = w * 0.5f;
    halfH = h * 0.5f;
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
            return 1;
        }
        combined &= code;
    }
    if ((u32)(combined & 3) == 1 || (u32)(combined & 3) == 2) {
        return 0;
    }
    if ((u32)(combined & 0xC) == 4 || (u32)(combined & 0xC) == 8) {
        return 0;
    }
    return 1;
}

// .text:0x000CDB48 size:0x248 mapped:0x8070CBDC
void fn_3_CDB48(PalaceHazeParticle* p, PalaceHazeEmitter* emitter) {
    f32 ang;
    f32 alpha;

    ang = const_pi_or_180 * (f32)(rand() % 360);
    p->velX = 0.01 * cosf_kludge(ang);
    p->velZ = 0.01 * sinf_kludge(ang);
    p->_14 = 0.12f;
    p->scale = 0.5f;
    p->scale = p->scale + (f64)((u32)rand() % 2500) / 1000.0;
    p->_38 = 2.0 * p->scale;
    p->_3C = 6.0 * p->scale;
    p->_20 = (f64)(rand() % 101) / 100.0;
    alpha = 255.0f;
    p->_4F = p->_4A = rand() % 24 + 0x48;
    p->origin.x = emitter->origin.x;
    p->origin.y = emitter->origin.y;
    p->origin.z = emitter->origin.z;
    p->alpha = alpha;
    p->alphaByte = alpha;
    p->_4A = p->_4F;
    p->_48 = 0;
}

// .text:0x000CDD90 size:0x214 mapped:0x8070CE24
void fn_3_CDD90(PalaceHazeParticle* p) {
    p->_38 = p->_20 * (4.0 * p->scale / p->_4F) + p->_38;
    p->_3C = p->_20 * (-2.0 * p->scale / p->_4F) + p->_3C;
    p->alpha = p->alpha + -255.0f / (f32)p->_4F;
    if (p->alpha < 0.0f) {
        p->alpha = 0.0f;
    }
    p->alphaByte = p->alpha;
    p->_40[0] = lbl_3_bss_A01C[0] * (p->alphaByte / 255.0);
    p->_40[1] = lbl_3_bss_A01C[1] * (p->alphaByte / 255.0);
    p->_40[2] = lbl_3_bss_A01C[2] * (p->alphaByte / 255.0);
    p->origin.x = p->origin.x + p->velX;
    p->origin.y = p->origin.y - p->_14;
    p->origin.z = p->origin.z + p->velZ;
    p->_4A--;
}

// .text:0x000CDFA4 size:0x5C8 mapped:0x8070D038
BOOL fn_3_CDFA4(PalaceHazeEmitter* emitter) {
    PalaceHazeParticle* p;
    Vec pos;

    p = emitter->particles;
    if (g_GameLogic.gameStatus >= GAME_STATUS_0x1B && g_GameLogic.gameStatus <= GAME_STATUS_MINIGAME_READY) {
        return 0;
    }
    if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL || g_GameLogic.gameStatus == GAME_STATUS_AT_BAT) {
        pos = emitter->origin;
        if (!fn_3_CD968(&pos, 6.0f, 4.0f)) {
            return 0;
        }
    }
    fn_80033620(emitter);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    do {
        if (p->_48 <= 0 && p->_4A != 0) {
            if (p->index % 3 == 0) {
                GXSetBlendMode(GX_BM_SUBTRACT, GX_BL_ONE, GX_BL_ONE, GX_LO_CLEAR);
                lbl_3_bss_A01C = lbl_3_rodata_249C;
            } else {
                GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_LO_CLEAR);
                lbl_3_bss_A01C = lbl_3_rodata_2498;
            }
            fn_8003403C(p->_38, p->_3C);
            fn_80033CC8(p, emitter->_10);
            if (returnsCurrentMode() == 0) {
                fn_3_CDD90(p);
            }
        }
        p->_48 -= (returnsCurrentMode() == 0);
        if (p->_4A == 0) {
            fn_3_CDB48(p, emitter);
        }
        p = p->next;
    } while (p != NULL);
    emitter->_25 = 1;
    return 0;
}

// .text:0x000CE56C size:0x378 mapped:0x8070D600
void palaceHazeTextureMaybe(PalaceHazeEmitter* emitter, u8 kind) {
    PalaceHazeParticle* p;
    int i;
    f32 ang;
    f32 alpha;

    p = emitter->particles;
    emitter->_10 = lbl_3_bss_ADD0[0];
    emitter->origin = lbl_3_rodata_24A0[kind];
    emitter->kind = kind;
    emitter->_25 = 1;
    alpha = 255.0f;
    i = 0;
    for (; p != NULL; p = p->next) {
        ang = const_pi_or_180 * (f32)(rand() % 360);
        p->velX = 0.01 * cosf_kludge(ang);
        p->velZ = 0.01 * sinf_kludge(ang);
        p->_14 = 0.12f;
        p->_48 = i * 4;
        p->scale = 0.5f;
        p->scale = p->scale + (f64)((u32)rand() % 2500) / 1000.0;
        p->_38 = 2.0 * p->scale;
        p->_3C = 6.0 * p->scale;
        p->_20 = (f64)(rand() % 101) / 100.0;
        p->origin.x = emitter->origin.x;
        p->origin.y = emitter->origin.y;
        p->origin.z = emitter->origin.z;
        p->alpha = alpha;
        p->alphaByte = alpha;
        p->_4F = p->_4A = rand() % 24 + 0x48;
        p->_4D = 0x15;
        p->_4E = 0;
        p->index = i;
        i++;
    }
}

// .text:0x000CE8E4 size:0x70 mapped:0x8070D978
void warioPalaceSomething(void) {
    PalaceHazeEmitter* emitter;
    u32 i;

    for (i = 0; i < 4; i++) {
        emitter = allocParticleEffect((void*)fn_3_CDFA4, 0x80, 0, 0x15, 1, 0);
        if (emitter != NULL) {
            palaceHazeTextureMaybe(emitter, i);
        }
    }
}

// .text:0x000CE954 size:0x268 mapped:0x8070D9E8
void fn_3_CE954(void) {
    PalaceGfxScene* item = (PalaceGfxScene*)currentDrawingItem;
    u8* state = lbl_3_bss_A898;
    f32* v = lbl_3_bss_A820;
    s16 sx;
    s16 sy;
    int i;

    for (i = 0; i < 10; i++, v += 3, state++) {
        switch (*state) {
        case 1:
            fn_800528C0(v[0], v[1], v[2], &sx, &sy);
            ((PalaceGfxObject*)graphicsRelatedArray[lbl_3_bss_A8A4->firstHandle + i].object)->pos.x = sx;
            ((PalaceGfxObject*)graphicsRelatedArray[lbl_3_bss_A8A4->firstHandle + i].object)->pos.y = sy;
            ((PalaceGfxObject*)graphicsRelatedArray[lbl_3_bss_A8A4->firstHandle + i].object)->pos.z = 0.0f;
            ((PalaceGfxObject*)graphicsRelatedArray[item->firstHandle + i].object)->frameIndex = 0;
            ((PalaceGfxObject*)graphicsRelatedArray[item->firstHandle + i].object)->flags |= 2;
            *state = 2;
            break;
        case 2:
            fn_800528C0(v[0], v[1], v[2], &sx, &sy);
            ((PalaceGfxObject*)graphicsRelatedArray[lbl_3_bss_A8A4->firstHandle + i].object)->pos.x = sx;
            ((PalaceGfxObject*)graphicsRelatedArray[lbl_3_bss_A8A4->firstHandle + i].object)->pos.y = sy;
            ((PalaceGfxObject*)graphicsRelatedArray[lbl_3_bss_A8A4->firstHandle + i].object)->pos.z = 0.0f;
            if (((PalaceGfxObject*)graphicsRelatedArray[item->firstHandle + i].object)->scale == 2) {
                ((PalaceGfxObject*)graphicsRelatedArray[item->firstHandle + i].object)->flags &= ~2;
                *state = 0;
            }
            break;
        }
    }
    if (lbl_3_bss_A81C != 0) {
        removeCurrentDrawingItem();
        removeGraphicsElementFromScene((DrawingSceneStruct*)lbl_3_bss_A8A4);
        lbl_3_bss_A81C = 0;
    }
}

// .text:0x000CEBBC size:0xDC mapped:0x8070DC50
void fn_3_CEBBC(Vec* p, int idx) {
    s16 sx;
    s16 sy;

    fn_800528C0(p->x, p->y, p->z, &sx, &sy);
    ((PalaceGfxObject*)graphicsRelatedArray[lbl_3_bss_A8A4->firstHandle + idx].object)->pos.x = sx;
    ((PalaceGfxObject*)graphicsRelatedArray[lbl_3_bss_A8A4->firstHandle + idx].object)->pos.y = sy;
    ((PalaceGfxObject*)graphicsRelatedArray[lbl_3_bss_A8A4->firstHandle + idx].object)->pos.z = 0.0f;
}

// .text:0x000CEC98 size:0x98 mapped:0x8070DD2C
void fn_3_CEC98(void) {
    int idx = (g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy != 0) + 8;

    lbl_3_bss_A898[idx] = 1;
    ((PalaceGfxObject*)graphicsRelatedArray[lbl_3_bss_A8A4->firstHandle + idx].object)->pos.x =
        g_Ball.AtBat_Contact_BallPos.x;
    ((PalaceGfxObject*)graphicsRelatedArray[lbl_3_bss_A8A4->firstHandle + idx].object)->pos.y =
        -g_Ball.AtBat_Contact_BallPos.y;
    ((PalaceGfxObject*)graphicsRelatedArray[lbl_3_bss_A8A4->firstHandle + idx].object)->pos.z =
        g_Ball.AtBat_Contact_BallPos.z;
}

// .text:0x000CED30 size:0x4 mapped:0x8070DDC4
void fn_3_CED30(void) {
    return;
}

// .text:0x000CED34 size:0x4 mapped:0x8070DDC8
void fn_3_CED34(void) {
    return;
}

// .text:0x000CED38 size:0x4 mapped:0x8070DDCC
void fn_3_CED38(void) {
    return;
}

// .text:0x000CED3C size:0x4 mapped:0x8070DDD0
void fn_3_CED3C(void) {
    return;
}

// .text:0x000CED40 size:0x11C mapped:0x8070DDD4
void fn_3_CED40(PalaceEffectParticle* p, u32 arg) {
    fn_8003403C(p->sizeA, p->sizeB);
    fn_80033CC8(p, arg);
    if (lbl_80366158[0x28] == 0) {
        if (-p->age < 5) {
            p->sizeA += 0.38;
            p->sizeB += 0.38;
            p->alpha += 34.0;
        } else {
            p->alpha -= 4;
        }
        p->pos.x = p->pos.x + p->vel.x;
        p->pos.y = p->pos.y + p->vel.y;
        p->pos.z = p->pos.z + p->vel.z;
    }
}

// .text:0x000CEE5C size:0x14C mapped:0x8070DEF0
void fn_3_CEE5C(PalaceEffectParticle* p, u32 arg) {
    fn_8003403C(p->sizeA, p->sizeB);
    fn_80033CC8(p, arg);
    if (lbl_80366158[0x28] == 0) {
        if (-p->age < 5) {
            p->sizeA += 0.38;
            p->sizeB += 0.38;
            p->alpha += 34.0;
        } else {
            p->alpha += -6.8;
        }
        p->pos.x = p->pos.x + p->vel.x;
        p->pos.y = p->pos.y + p->vel.y;
        p->pos.z = p->pos.z + p->vel.z;
    }
}

// .text:0x000CEFA8 size:0x2D0 mapped:0x8070E03C
BOOL fn_3_CEFA8(PalaceEffect* effect) {
    PalaceEffectParticle* p;

    p = effect->particles;
    fn_80033620(effect);
    do {
        if (p->age <= 0 && p->lifetime != 0) {
            if (p->_4F == 0) {
                fn_3_CEE5C(p, effect->_10);
            } else {
                fn_3_CED40(p, effect->_10);
            }
            p->lifetime -= (lbl_80366158[0x28] == 0);
        }
        p->age -= (lbl_80366158[0x28] == 0);
        p = p->next;
    } while (p != NULL);
    effect->_18 -= (lbl_80366158[0x28] == 0);
    return effect->_18 == 0;
}

// .text:0x000CF278 size:0x4B4 mapped:0x8070E30C
void fn_3_CF278(PalaceStarObj* obj, Vec* pos) {
    PalaceEffect* effect;
    PalaceEffectParticle* p;
    u32 i;
    u32 j;
    f32 ang;
    f32 cosA;
    f32 sinA;

    effect = obj->effect;
    p = effect->particles;
    i = 0;
    j = 0;
    effect->_10 = lbl_3_bss_ADD0[0];
    effect->_18 = 100;
    effect->owner = obj;
    for (; p != NULL; p = p->next) {
        if (i < 10) {
            p->sizeA = p->sizeB = 0.1f;
            ang = const_pi_or_180 * (f32)(rand() % 360);
            p->vel.x = 0.01 * (f32)cos(ang);
            p->vel.z = 0.01 * (f32)sin(ang);
            p->vel.y = -0.01f;
            p->pos.x = pos->x + (f32)(rand() % 200 - 100) / 100.0f;
            p->pos.y = -pos->y;
            p->pos.z = pos->z + (f32)(rand() % 200 - 100) / 100.0f;
            p->age = 0;
            p->colorR = p->colorG = p->colorB = 0xFF;
            p->alpha = 0;
            p->_4F = 0;
            p->lifetime = 30;
        } else {
            p->sizeA = p->sizeB = 0.1f;
            ang = const_pi_or_180 * (18.0f * (f32)j + (f32)(rand() % 33) - 16.0f);
            p->vel.x = 0.02 * (f32)cos(ang);
            p->vel.z = 0.02 * (f32)sin(ang);
            p->vel.y = -0.01f;
            cosA = (f32)cos(ang);
            p->pos.x = (f32)(3.0 * cosA + (f32)(rand() % 100 - 50) / 100.0f) + sandStarPlacementConfig.entries[obj->index].pos.x;
            p->pos.y = -sandStarPlacementConfig.entries[obj->index].pos.y;
            sinA = (f32)sin(ang);
            p->pos.z = (f32)(3.0 * sinA + (f32)(rand() % 100 - 50) / 100.0f) + sandStarPlacementConfig.entries[obj->index].pos.z;
            p->age = 15;
            p->colorR = p->colorG = p->colorB = 0xFF;
            p->alpha = 0;
            p->_4F = 1;
            p->lifetime = 45;
            j++;
        }
        p->kind = 9;
        p->_4E = 0;
        i++;
    }
}

// .text:0x000CF72C size:0x200 mapped:0x8070E7C0
void starHitAnimation(int idx) {
    PalaceStarObj* obj = (PalaceStarObj*)(stadiumObjectCollision.objects + idx);
    Vec trans;
    Vec ballPos;
    Vec pos;
    int stadiumID;
    u8 vol;
    u8 val;
    SND_VOICEID voice;

    if (g_Ball.AtBat_ContactResult < BALL_RESULT_TYPE_FIELDED && obj->awarded != 1) {
        if (inningSetting.starSkillsSetting != 0) {
            CTRLGetTranslation((Control*)obj, &trans.x, &trans.y, &trans.z);
            stadiumStarAwarded(trans.x, trans.y - 5.0f, trans.z);
            obj->awarded = 1;
        }
        if (obj->effect != NULL) {
            fn_80033964(obj->effect);
            obj->effect = NULL;
        }
        obj->effect = allocParticleEffect((void*)fn_3_CEFA8, 0x80, 0, 0x1E, 1, 0);
        if (obj->effect != NULL) {
            ballPos.x = g_Ball.AtBat_Contact_BallPos.x;
            ballPos.y = g_Ball.AtBat_Contact_BallPos.y;
            ballPos.z = g_Ball.AtBat_Contact_BallPos.z;
            pos = ballPos;
            fn_3_CF278(obj, &pos);
        }
        obj->actor = (PalaceStarActor*)((u8*)lbl_3_bss_A034 + obj->index * 0x5C);
        actorRelated(obj->actor, 0, 0);
        obj->actor->_1A = 1;
        obj->actor->_58 = -1;
        stadiumID = g_d_GameSettings.StadiumID;
        vol = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD ? lbl_3_data_84B8[0]
                                                                       : stadiumHazardSoundFxRelated[stadiumID * 0x1E];
        voice = sndFXStartEx(stadiumHazardSoundIDs[stadiumID], vol, 0x3F, 0);
        val = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                  ? lbl_3_data_84B8[1]
                  : stadiumHazardSoundFxRelated[stadiumID * 0x1E + 1];
        sndFXCtrl(voice, 0x5B, val);
    }
}

// .text:0x000CF92C size:0x4 mapped:0x8070E9C0
void fn_3_CF92C(void) {
    return;
}

// .text:0x000CF930 size:0x158 mapped:0x8070E9C4
void warioPalaceSandStarRelated(PalaceStarObj* obj) {
    PalaceStarActor* actor = obj->actor;
    u16 endFrame;
    f32 rate;
    f32 step;

    if (actor != NULL) {
        endFrame = actor->endFrame;
        rate = actor->rate;
        if (actor->frame == (f32)endFrame) {
            CTRLSetTranslation((Control*)obj, sandStarPlacementConfig.entries[obj->index].pos.x, 5.0f,
                               sandStarPlacementConfig.entries[obj->index].pos.z);
            obj->actor = NULL;
            obj->hasShadow = 0;
        }
        step = 1.0f / ((f32)endFrame / rate);
        if ((f32)obj->alpha <= step) {
            obj->alpha = 0;
        } else {
            obj->alpha = (f32)obj->alpha - step;
        }
    }
    if (obj->effect != NULL && obj->effect->link == NULL) {
        obj->effect = NULL;
    }
}

// .text:0x000CFA88 size:0x4 mapped:0x8070EB1C
void fn_3_CFA88(void) {
    return;
}

// .text:0x000CFA8C size:0x28 mapped:0x8070EB20
void fn_3_CFA8C(StadiumObject* obj) {
    AnimateActorBones(obj->model->root);
}

// .text:0x000CFAB4 size:0x90 mapped:0x8070EB48
void fn_3_CFAB4(PalaceEffectParticle* p, PalaceEffect* effect) {
    PalaceScaleSource* src = ((PalaceHazeObj*)effect->owner)->scaleSrc;

    p->pos.x = p->prevPos.x;
    p->pos.y = p->prevPos.y;
    p->pos.z = p->prevPos.z;
    p->sizeA = p->sizeB = 3.0 * src->scale;
    p->colorR = p->colorG = p->colorB = 255;
    p->alpha = 255.0 * src->scale;
    p->lifetime = 30;
    p->age = 0;
}

// .text:0x000CFB44 size:0x214 mapped:0x8070EBD8
BOOL fn_3_CFB44(PalaceEffect* effect) {
    PalaceEffectParticle* p = effect->particles;
    PalaceHazeObj* owner = (PalaceHazeObj*)effect->owner;

    fn_80033620(effect);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    do {
        if (p->age <= 0 && p->lifetime != 0) {
            int a;

            fn_8003403C(p->sizeA, p->sizeB);
            fn_80033CC8(p, effect->_10);
            p->sizeA += 0.1;
            if (p->sizeA < 0.0f) {
                p->sizeA = 0.0f;
            }
            p->sizeB += 0.1;
            if (p->sizeB < 0.0f) {
                p->sizeB = 0.0f;
            }
            a = p->alpha - 8;
            if (a < 0) {
                a = 0;
            }
            p->alpha = a;
            p->pos.x += p->vel.x;
            p->pos.y -= p->vel.y;
            p->pos.z += p->vel.z;
            p->lifetime--;
        }
        p->age--;
        if (p->lifetime == 0) {
            fn_3_CFAB4(p, effect);
        }
        p = p->next;
    } while (p != NULL);
    if (owner->source->_D1 == 0) {
        owner->effect = NULL;
        return 1;
    }
    return 0;
}

// .text:0x000CFD58 size:0x374 mapped:0x8070EDEC
void fn_3_CFD58(PalaceHazeObj* obj) {
    PalaceEffect* effect;
    PalaceEffectParticle* p;
    int i;
    int idx;
    f32 ang;
    int a;

    effect = obj->effect;
    p = effect->particles;
    effect->owner = obj;
    effect->_10 = lbl_3_bss_ADD0[0];
    for (i = 0; p != NULL; p = p->next) {
        idx = i / 5;
        ang = const_pi_or_180 * ((f32)(360.0 * (f64)(i % 5) / 5.0) + (f32)(-obj->source->_D0 * idx * 10));
        p->prevPos.x = p->pos.x = 6.0f * (f32)cos(ang) + obj->source->pos.x;
        p->prevPos.y = p->pos.y = 0.0f;
        p->prevPos.z = p->pos.z = 6.0f * (f32)sin(ang) + obj->source->pos.z;
        rand();
        p->vel.x = 0.0f;
        p->vel.y = 0.03f;
        p->vel.z = 0.0f;
        p->lifetime = (idx + 1) * 5;
        p->pos.x = p->vel.x * (f32)(30 - p->lifetime) + p->pos.x;
        p->pos.y = p->vel.y * (f32)(30 - p->lifetime) + p->pos.y;
        p->pos.z = p->vel.z * (f32)(30 - p->lifetime) + p->pos.z;
        p->sizeB = p->sizeA = 3.0 * ((f32)(30 - p->lifetime) / 30.0f) + 3.0;
        p->colorR = p->colorG = p->colorB = 0xFF;
        a = -255.0f * ((f32)(30 - p->lifetime) / 30.0f) + 255.0f;
        if (a < 0) {
            a = 0;
        }
        p->alpha = a;
        i++;
        p->age = 0;
        p->kind = 9;
        p->_4E = 0;
    }
}

// .text:0x000D00CC size:0x4 mapped:0x8070F160
void fn_3_D00CC(void) {
    return;
}

// .text:0x000D00D0 size:0x1B0 mapped:0x8070F164
void fn_3_D00D0(PalaceHazeObj* obj) {
    Vec v;
    u8 state = obj->source->_D1;
    Control* ctrl = (Control*)obj->scaleSrc;

    if (state == 0) {
        if (obj->hasShadow) {
            obj->hasShadow = 0;
        }
        if (obj->alpha != 0xFF) {
            obj->alpha = 0xFF;
        }
        if (obj->effect != NULL) {
            fn_80033964(obj->effect);
            obj->effect = NULL;
        }
    } else {
        if (!obj->hasShadow) {
            obj->hasShadow = 1;
        }
        if (obj->effect == NULL) {
            obj->effect = allocParticleEffect((void*)fn_3_CFB44, 0x80, 0, 0x1E, 0, 1);
            if (obj->effect != NULL) {
                fn_3_CFD58(obj);
            }
        }
        CTRLSetRotation((Control*)obj, 0.0f, obj->source->yaw, 0.0f);
        if (state == 3) {
            obj->alpha = (f32)obj->alpha - 1.7f;
            if ((f32)obj->alpha > 253.3f) {
                obj->alpha = 0;
            }
        }
    }
    CTRLGetTranslation(ctrl, &v.x, &v.y, &v.z);
    CTRLSetTranslation((Control*)obj, v.x, v.y, v.z);
}

// .text:0x000D0280 size:0x4 mapped:0x8070F314
void fn_3_D0280(void) {
    return;
}

// .text:0x000D0284 size:0x20C mapped:0x8070F318
void fn_3_D0284(PalaceNadoRingObj* obj) {
    u8 state = obj->source->_D1;
    f32 ang;
    int a;

    if (state == 0) {
        if (obj->hasShadow) {
            obj->hasShadow = 0;
        }
        if (obj->alpha != 0xFF) {
            obj->alpha = 0xFF;
        }
        if (1.0 != obj->radius) {
            obj->radius = 1.0f;
        }
    } else {
        if (!obj->hasShadow) {
            obj->hasShadow = 1;
        }
        CTRLSetRotation((Control*)obj, 0.0f, obj->source->yaw, 0.0f);
        ang = const_pi_or_180 * (f32)(rand() % 360);
        obj->offsetX = obj->radius * (f32)cos(ang);
        obj->offsetZ = obj->radius * (f32)sin(ang);
        CTRLSetTranslation((Control*)obj, obj->baseX + obj->offsetX, 0.0f, obj->baseZ + obj->offsetZ);
        if (state == 3) {
            a = (f32)(int)obj->alpha - 1.7f;
            if (a < 0) {
                a = 0;
            }
            obj->alpha = a;
            obj->radius -= 0.006666666666666667;
            if (obj->radius < 0.0f) {
                obj->radius = 0.0f;
            }
        }
    }
}

// .text:0x000D0490 size:0x98 mapped:0x8070F524
void fn_3_D0490(void) {
    int idx = (g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy != 0) + 2;

    lbl_3_bss_A898[idx] = 1;
    ((PalaceGfxObject*)graphicsRelatedArray[lbl_3_bss_A8A4->firstHandle + idx].object)->pos.x =
        g_Ball.AtBat_Contact_BallPos.x;
    ((PalaceGfxObject*)graphicsRelatedArray[lbl_3_bss_A8A4->firstHandle + idx].object)->pos.y =
        -g_Ball.AtBat_Contact_BallPos.y;
    ((PalaceGfxObject*)graphicsRelatedArray[lbl_3_bss_A8A4->firstHandle + idx].object)->pos.z =
        g_Ball.AtBat_Contact_BallPos.z;
}

// .text:0x000D0528 size:0x4 mapped:0x8070F5BC
void fn_3_D0528(void) {
    return;
}

// .text:0x000D052C size:0x8 mapped:0x8070F5C0
int fn_3_D052C(void) {
    return 0;
}

// .text:0x000D0534 size:0x320 mapped:0x8070F5C8
void fn_3_D0534(PalaceNadoObj* obj) {
    Mtx m;
    Vec ball;
    Vec d;
    Vec a;
    Vec b;
    Vec e;
    Vec c;
    f32 angle;

    lbl_3_bss_A030 += obj->speed;
    ball.x = g_Ball.AtBat_Contact_BallPos.x;
    ball.y = g_Ball.AtBat_Contact_BallPos.y;
    ball.z = g_Ball.AtBat_Contact_BallPos.z;
    PSVECSubtract(&ball, &obj->pos, &d);
    d.y = 0.0f;
    e = d;
    PSMTXRotRad(m, 'Y', const_pi_or_180 * ((f32)obj->dir * obj->speed));
    PSMTXMultVec(m, &d, &d);
    if (lbl_3_bss_A030 / 360.0f >= 1.0f) {
        b.y = 0.0f;
        a.y = 0.0f;
        if (obj->dir > 0) {
            a.x = e.z;
            a.z = -e.x;
        } else {
            a.x = -e.z;
            a.z = e.x;
        }
        if (obj->dir > 0) {
            b.x = d.z;
            b.z = -d.x;
        } else {
            b.x = -d.z;
            b.z = d.x;
        }
        PSVECNormalize(&a, &a);
        PSVECNormalize(&b, &b);
        angle = acos(PSVECDotProduct(&a, &b));
        c.x = sin(const_pi_or_180 * obj->spread);
        c.y = 0.0f;
        c.z = cos(const_pi_or_180 * obj->spread);
        if ((f32)acos(PSVECDotProduct(&a, &c)) <= angle) {
            f32 mag;

            PSVECSubtract(&d, &e, &d);
            mag = PSVECMag(&d);
            g_Ball.physicsSubstruct.velocity.x = c.x * mag;
            g_Ball.physicsSubstruct.velocity.y = 0.0f;
            g_Ball.physicsSubstruct.velocity.z = c.z * mag;
            obj->state = 3;
            setBallInactiveVariables();
            stadiumObjectCollision.hazardHitActive = 0;
            lbl_3_bss_A030 = 0.0f;
            sndFXKeyOff(lbl_3_data_182C0);
            sndFXCtrl(lbl_3_data_182C0, 7, 0);
            lbl_3_data_182C0 = -1;
            return;
        }
    }
    g_Ball.AtBat_Contact_BallPos.z = d.z + obj->pos.z;
    g_Ball.AtBat_Contact_BallPos.x = d.x + obj->pos.x;
    g_Ball.AtBat_Contact_BallPos.y = ball.y;
}

// .text:0x000D0854 size:0xC4 mapped:0x8070F8E8
f32 fn_3_D0854(StadiumObject* obj) {
    f32 base;
    f32 span;

    if (obj->_D0 > 0) {
        base = TornadoPlacementConfig[obj->_9C].rangeBaseA;
        span = TornadoPlacementConfig[obj->_9C].rangeSpanA;
    } else {
        base = TornadoPlacementConfig[obj->_9C].rangeBaseB;
        span = TornadoPlacementConfig[obj->_9C].rangeSpanB;
    }
    return span * (rng(1000) / 1000.0) + base;
}

// .text:0x000D0918 size:0x6EC mapped:0x8070F9AC
void palaceNadoLogic(PalaceNadoObj* obj) {
    u8* ctrlBlock = ((PalaceModelRoot*)obj->model->root)->next->ctrlBlock;
    Vec ball;
    Vec d;
    Vec axis = lbl_3_rodata_2604[0];
    Quaternion q;
    f32 mag;

    obj->_C4 += 0.03;
    if (obj->_C4 >= 6.2831855f) {
        obj->_C4 = 0.0f;
    }
    obj->pos.y = 0.5 * (f32)sin(obj->_C4) + obj->_C8;
    if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
        if (obj->state != 0) {
            if (obj->state == 2) {
                setBallInactiveVariables();
                stadiumObjectCollision.hazardHitActive = 0;
                lbl_3_bss_A030 = 0.0f;
                sndFXKeyOff(lbl_3_data_182C0);
                sndFXCtrl(lbl_3_data_182C0, 7, 0);
            }
            obj->state = 0;
        }
        if (lbl_3_data_182C0 != -1) {
            sndFXKeyOff(lbl_3_data_182C0);
            sndFXCtrl(lbl_3_data_182C0, 7, 0);
        }
    }
    switch (obj->state) {
    case 0:
        ball.x = g_Ball.AtBat_Contact_BallPos.x;
        ball.y = g_Ball.AtBat_Contact_BallPos.y;
        ball.z = g_Ball.AtBat_Contact_BallPos.z;
        PSVECSubtract(&ball, &obj->pos, &d);
        d.y = 0.0f;
        if (!((g_Ball.currentStarSwing2 == 3) | (g_Ball.currentStarSwing2 == 4) | (g_Ball.currentStarSwing2 == 0xB) |
              (g_Ball.currentStarSwing2 == 0xC)) &&
            PSVECMag(&d) < 5.0f && ball.y > 5.5 && ball.y < 10.0f &&
            g_Ball.AtBat_ContactResult < BALL_RESULT_TYPE_FIELDED) {
            obj->state = 1;
            obj->dir = obj->dir = -(rng(2) * 2) + 1;
            obj->speed = TornadoPlacementConfig[obj->index].spinRate;
        }
        break;
    case 1:
        obj->yaw += (f32)obj->dir * obj->speed;
        ball.x = g_Ball.AtBat_Contact_BallPos.x;
        ball.y = 0.0f;
        ball.z = g_Ball.AtBat_Contact_BallPos.z;
        PSVECSubtract(&ball, &obj->pos, &d);
        d.y = 0.0f;
        mag = PSVECMag(&d);
        if (mag < 5.0f) {
            PSVECNormalize(&d, &d);
            PSVECScale(&d, 5.0f, &d);
            g_Ball.AtBat_Contact_BallPos.x = obj->pos.x + d.x;
            g_Ball.AtBat_Contact_BallPos.z = obj->pos.z + d.z;
            obj->state = 2;
            setValsForPlantCatches();
            stadiumObjectCollision.hazardHitActive = 1;
            obj->spread = fn_3_D0854((StadiumObject*)obj);
            if (obj->spread < 0.0f) {
                obj->spread = 360.0 + obj->spread;
            }
            {
                int stadiumID = g_d_GameSettings.StadiumID;
                u8 vol;
                u8 val;
                SND_VOICEID voice;

                vol = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                          ? lbl_3_data_84B8[2]
                          : stadiumHazardSoundFxRelated[stadiumID * 0x1E + 2];
                voice = sndFXStartEx(stadiumHazardSoundIDs[stadiumID] + 1, vol, 0x3F, 0);
                val = g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                          ? lbl_3_data_84B8[3]
                          : stadiumHazardSoundFxRelated[stadiumID * 0x1E + 3];
                sndFXCtrl(voice, 0x5B, val);
                lbl_3_data_182C0 = voice;
            }
        } else {
            ball.x = g_Ball.pastCoordinates[0].x;
            ball.y = 0.0f;
            ball.z = g_Ball.pastCoordinates[0].z;
            PSVECSubtract(&ball, &obj->pos, &d);
            d.y = 0.0f;
            if (mag > PSVECMag(&d)) {
                obj->state = 3;
            }
        }
        break;
    case 2:
        obj->yaw += (f32)obj->dir * obj->speed;
        fn_3_D0534(obj);
        break;
    case 3:
        obj->speed -= TornadoPlacementConfig[obj->index].spinRate / 150.0f;
        obj->yaw += (f32)obj->dir * obj->speed;
        if (obj->speed <= 0.0f) {
            obj->state = 0;
        }
        break;
    }
    C_QUATRotAxisRad(&q, &axis, const_pi_or_180 * obj->yaw);
    PSQUATMultiply(&obj->quat, &q, &q);
    PSQUATNormalize(&q, &q);
    CTRLSetTranslation((Control*)obj, obj->pos.x, -obj->pos.y, obj->pos.z);
    CTRLSetQuat((Control*)(ctrlBlock + 0x1C), q.x, q.y, q.z, q.w);
}

// .text:0x000D1004 size:0x10C mapped:0x80710098
void fn_3_D1004(PalaceNadoObj* obj, f32 x, f32 y, f32 z, f32 restYaw, f32 yaw) {
    u8* ctrlBlock = ((PalaceModelRoot*)obj->model->root)->next->ctrlBlock;
    Vec axis = lbl_3_rodata_25F8;
    Quaternion q;

    obj->pos.x = x;
    obj->pos.y = y;
    obj->pos.z = z;
    obj->yaw = yaw;
    ((Control*)obj)->type = 0;
    CTRLSetTranslation((Control*)obj, obj->pos.x, -obj->pos.y, obj->pos.z);
    CTRLSetRotation((Control*)obj, 0.0f, restYaw, 0.0f);
    C_QUATRotAxisRad(&q, &axis, const_pi_or_180 * obj->yaw);
    PSQUATMultiply(&q, &obj->quat, &q);
    PSQUATNormalize(&q, &q);
    CTRLSetQuat((Control*)(ctrlBlock + 0x1C), q.x, q.y, q.z, q.w);
}

// .text:0x000D1110 size:0x16C mapped:0x807101A4
void fn_3_D1110(PalaceNadoObj* obj) {
    u8* ctrlBlock = ((PalaceModelRoot*)obj->model->root)->next->ctrlBlock;
    Quaternion q;
    Vec axis = lbl_3_rodata_25F8;
    f32 restYaw = TornadoPlacementConfig[obj->index].restYaw;

    obj->pos.x = TornadoPlacementConfig[obj->index].restPos.x;
    obj->pos.y = TornadoPlacementConfig[obj->index].restPos.y;
    obj->pos.z = TornadoPlacementConfig[obj->index].restPos.z;
    obj->yaw = 0.0f;
    ((Control*)obj)->type = 0;
    CTRLSetTranslation((Control*)obj, obj->pos.x, -obj->pos.y, obj->pos.z);
    CTRLSetRotation((Control*)obj, 0.0f, restYaw, 0.0f);
    C_QUATRotAxisRad(&q, &axis, const_pi_or_180 * obj->yaw);
    PSQUATMultiply(&q, &obj->quat, &q);
    PSQUATNormalize(&q, &q);
    CTRLSetQuat((Control*)(ctrlBlock + 0x1C), q.x, q.y, q.z, q.w);
    obj->_C8 = TornadoPlacementConfig[obj->index].restPos.y;
    obj->speed = 0.0f;
    obj->_C4 = 0.0f;
    obj->state = 0;
}

// .text:0x000D127C size:0x4 mapped:0x80710310
void fn_3_D127C(void) {
    return;
}

// .text:0x000D1280 size:0x19C mapped:0x80710314
void maybePalaceCTRLRelated(StadiumObject* obj) {
    Vec mid;
    Vec delta;
    Vec snd;
    f32 dist;
    int count;

    if (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT || g_GameLogic.gameStatus == GAME_STATUS_DEFAULT) {
        ((Control*)obj)->type = 0;
    }
    fn_3_D141C(obj);
    PSVECAdd(&obj->anchorB->pos, &obj->anchorA->pos, &mid);
    PSVECScale(&mid, 0.5f, &mid);
    if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL && g_GameLogic.bOD_framesInLiveBallScene >= 0) {
        PSVECSubtract(&mid, &obj->pos, &delta);
        dist = PSVECMag(&delta);
        count = obj->_B4[0] + 1;
        if (count < 0x100) {
            obj->_B4[0] = count;
        }
        if (dist >= 0.3f && obj->_B4[0] > 10) {
            memcpy(&snd, &obj->pos, sizeof(Vec));
            snd.y *= -1.0f;
            initializeStadiumObjectEmitter(stadiumHazardSoundIDs[g_d_GameSettings.StadiumID] + 6, &snd, NULL, 0xE);
            obj->_B4[0] = 0;
        }
    }
    PSVECScale(&mid, 1.0f, &obj->pos);
    CTRLSetTranslation((Control*)obj, obj->pos.x, -obj->pos.y, obj->pos.z);
    CTRLSetScale((Control*)obj, 0.75f, 0.75f, 0.75f);
}

// .text:0x000D141C size:0x320 mapped:0x807104B0
void fn_3_D141C(StadiumObject* obj) {
    Vec dir;
    Vec f;
    Vec e;
    Quaternion q;
    Quaternion qX;
    Quaternion qY;
    Quaternion qZ;
    Vec axisX;
    Vec axisY;
    Vec axisZ;
    f32 angX = 0.0f;
    f32 angY = angX;
    f32 angZ = angX;
    f32 mag;
    f32 a;

    axisX = lbl_3_rodata_25C8;
    axisY = lbl_3_rodata_25D4;
    axisZ = lbl_3_rodata_25E0[0];
    PSVECSubtract(&obj->anchorB->pos, &obj->anchorA->pos, &dir);
    f = e = dir;
    e.x = sqrt(pow(e.x, 2.0) + pow(e.z, 2.0));
    e.z = 0.0f;
    f.y = 0.0f;
    PSVECNormalize(&dir, &dir);
    mag = PSVECMag(&f);
    if (mag != 0.0f) {
        PSVECNormalize(&f, &f);
        a = acos(PSVECDotProduct(&axisX, &f));
        angY = a;
        if (f.z > 0.0f) {
            angY *= -1.0f;
        }
    }
    mag = PSVECMag(&e);
    if (mag != 0.0f) {
        PSVECNormalize(&e, &e);
        a = acos(PSVECDotProduct(&axisX, &e));
        angZ = a;
        if (e.y > 0.0f) {
            angZ *= -1.0f;
        }
    }
    if (angX != 0.0f || angY != 0.0f || angZ != 0.0f) {
        C_QUATRotAxisRad(&qY, &axisY, angY);
        C_QUATRotAxisRad(&qZ, &axisZ, angZ);
        if (obj->_9C % 2 == 0) {
            angX = 1.5707964f;
        }
        C_QUATRotAxisRad(&qX, &axisX, angX);
        q = qY;
        PSQUATMultiply(&q, &qZ, &q);
        PSQUATMultiply(&q, &qX, &q);
        PSQUATNormalize(&q, &q);
        if (PSQUATDotProduct(&q, &q) == 0.0f) {
            C_QUATRotAxisRad(&q, &axisX, 0.0f);
        }
        CTRLSetQuat((Control*)obj, q.x, q.y, q.z, q.w);
    }
}

// .text:0x000D173C size:0x10C mapped:0x807107D0
void applyTransformationToPalaceObjs(StadiumObject* obj) {
    Mtx inv;
    Mtx rot;
    camera_803c639c_s* cam;
    u32 i;
    f32 ang = 3.1415927f;

    cam = returnFloatFromModeIndex(returnsCurrentMode());
    PSMTXInverse(cam->view, inv);
    PSMTXIdentity(rot);
    rot[0][0] = cos(ang);
    rot[0][2] = -(f32)sin(ang);
    rot[2][0] = sin(ang);
    rot[2][2] = cos(ang);
    PSMTXConcat(inv, rot, inv);
    inv[2][3] = 0.0f;
    inv[1][3] = 0.0f;
    inv[0][3] = 0.0f;
    for (i = 0; i < ((StadiumAnimObjectList*)obj->model->root)->objectCount; i++) {
        MtxPtr m = ((StadiumModelNode*)((StadiumAnimObjectList*)obj->model->root)->objects[i])->worldMtx;

        PSMTXConcat(inv, m, m);
    }
}

// .text:0x000D1848 size:0x124 mapped:0x807108DC
void fn_3_D1848(PalaceSpinObj* obj) {
    ACTActor* actor = obj->model;

    if (*obj->stateFlag != 0) {
        if (obj->hasShadow) {
            obj->hasShadow = 0;
            obj->timer = obj->index % 3 * 30;
            obj->frame = 0.0f;
            actor->animFrame = obj->frame;
            actor->applyFrame = 1;
            setActorAnimFrame(actor->actor, actor->animFrame);
        }
    } else if (obj->timer != 0) {
        if (obj->hasShadow) {
            obj->hasShadow = 0;
        }
        obj->timer--;
    } else {
        if (!obj->hasShadow) {
            obj->hasShadow = 1;
        }
        obj->frame += obj->rate;
        if (obj->frame > 100.0f) {
            obj->frame -= 100.0f;
            obj->timer = 90;
        }
        AnimateActorBones(actor->actor);
    }
}

// .text:0x000D196C size:0x158 mapped:0x80710A00
void fn_3_D196C(int idx) {
    StadiumObject* obj = &stadiumObjectCollision.objects[idx];
    Vec v;
    int i;

    if (g_Ball.ballState != BALL_STATE_HELD) {
        if (obj->_CA == 0) {
            obj->_99 &= 0xFB;
            obj->_CB[1] = 5;
            obj->_CB[0] = obj->_CA;
            obj->_CA = 2;
            *(f32*)&obj->anchorB = 0.5f;
            actorRelated(obj->effect, 0, 3);
        }
        memcpy(&v, &g_Ball, sizeof(Vec));
        v.y *= -1.0f;
        initializeStadiumObjectEmitter(stadiumHazardSoundIDs[g_d_GameSettings.StadiumID] + 5, &v, NULL, 0xD);
        i = g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy != 0;
        lbl_3_bss_A898[i] = 1;
        lbl_3_bss_A820[i * 3] = g_Ball.AtBat_Contact_BallPos.x;
        lbl_3_bss_A820[i * 3 + 1] = -g_Ball.AtBat_Contact_BallPos.y;
        lbl_3_bss_A820[i * 3 + 2] = g_Ball.AtBat_Contact_BallPos.z;
        ballState_thrown_to_holding();
        processFielderAutoCatch();
        g_FieldingLogic.knockoutFinished = 1;
    }
}

// .text:0x000D1AC4 size:0x60 mapped:0x80710B58
void fn_3_D1AC4(StadiumObject* obj) {
    StadiumModel* model = obj->model;
    PalaceMaterialFlags* mat = ((PalaceModelRoot*)model->root)->next->next->next->next->next;

    if (obj->_CA == 0) {
        mat->flags &= ~0x1FFF;
        mat->flags |= 3;
    } else {
        mat->flags &= ~0x1FFF;
        mat->flags |= 2;
    }
}

// .text:0x000D1B24 size:0x408 mapped:0x80710BB8
void chainChomp_colveSpringForces(ChainChompPhysicsParams* params, StadiumLink* links, int count, Vec* force) {
    Vec vel;
    Vec dir;
    Vec sum;
    StadiumLink* link;
    StadiumLink* prev;
    int i;
    f32 mag;
    f32 spring;
    f32 damp;
    f32 amount;
    f32 velMag;

    link = links;
    for (i = 0; i < count; link++, i++) {
        memset(&link->accel, 0, sizeof(Vec));
        if (link->pinned == 0 && i != count - 1) {
            link->accel.y = -9.80665f * link->weight;
        }
        if (i == count - 1) {
            PSVECAdd(&link->accel, force, &link->accel);
        }
    }

    i = count;
    while (--i != 0) {
        link = &links[i];
        prev = &links[i - 1];
        PSVECSubtract(&link->pos, &prev->pos, &dir);
        PSVECSubtract(&link->vel, &prev->vel, &vel);
        mag = PSVECMag(&dir);
        spring = params->stiffness * (mag - params->restLength);
        damp = PSVECDotProduct(&vel, &dir) / mag;
        damp = params->damping * damp;
        amount = -(spring + damp);
        if (0.0f == PSVECMag(&dir)) {
            dir.x = dir.z = 0.0f;
            dir.y = -1.0f;
        }
        PSVECNormalize(&dir, &dir);
        PSVECScale(&dir, amount, &dir);
        if (link->pinned == 0) {
            PSVECAdd(&link->accel, &dir, &link->accel);
        }
        PSVECScale(&dir, -1.0f, &dir);
        if (prev->pinned == 0) {
            PSVECAdd(&prev->accel, &dir, &prev->accel);
        }
    }

    for (i = 0; i < count; links++, i++) {
        if (links->pinned != 0) {
            continue;
        }
        memcpy(&vel, &links->vel, sizeof(Vec));
        memcpy(&dir, &links->accel, sizeof(Vec));
        PSVECScale(&dir, links->mobility, &dir);
        PSVECScale(&dir, params->externalForceScale, &dir);
        PSVECAdd(&vel, &dir, &vel);
        memset(&sum, 0, sizeof(Vec));
        mag = PSVECMag(&vel);
        if (0.0f != mag) {
            PSVECScale(&vel, -1.0f, &dir);
            PSVECNormalize(&dir, &dir);
            PSVECScale(&dir, params->dragCoefficient * (mag * mag), &dir);
            PSVECAdd(&sum, &dir, &sum);
        }
        if (links->pos.y <= links->radius && links->accel.y < 0.0f) {
            amount = links->accel.y * params->groundFriction;
            if (amount < 0.0f) {
                amount = -amount;
            }
            memcpy(&dir, &links->accel, sizeof(Vec));
            dir.y = 0.0f;
            mag = PSVECMag(&dir);
            vel.y = 0.0f;
            velMag = PSVECMag(&vel);
            if (0.0f != velMag || mag > amount) {
                if (0.0f != velMag) {
                    PSVECNormalize(&vel, &dir);
                } else {
                    PSVECNormalize(&dir, &dir);
                }
                PSVECScale(&dir, -amount, &dir);
                PSVECAdd(&sum, &dir, &sum);
            } else {
                PSVECScale(&links->accel, -1.0f, &dir);
                PSVECAdd(&sum, &dir, &sum);
            }
        }
        PSVECAdd(&links->accel, &sum, &links->accel);
    }
}

// .text:0x000D1F2C size:0x2F4 mapped:0x80710FC0
void chainChomp_simulateAndCollide(ChainChompPhysicsParams* params, StadiumLink* links, int count, Vec* force,
                                   StadiumObject* owner) {
    Vec accelScaled;
    Vec scaledForce;
    Vec chompPos;
    Vec diff;
    Vec normal;
    Vec push;
    Vec tmp2;
    Vec tmp1;
    StadiumLink* link;
    int iter;
    int i;
    f32 mag;
    f32 dampA;
    f32 dampB;
    f32 pen;

    chompPos = owner->pos;
    chompPos.y = chompPos.y + 4.5;
    PSVECScale(force, params->externalForceScale, &scaledForce);
    for (iter = 0; iter < params->solverIterations; iter++) {
        chainChomp_colveSpringForces(params, links, count, &scaledForce);
        link = links;
        for (i = 0; i < count; link++, i++) {
            PSVECScale(&link->accel, link->mobility, &accelScaled);
            dampB = params->dampingB;
            dampA = params->dampingA;
            PSVECScale(&link->pos, 2.0f, &tmp1);
            PSVECSubtract(&tmp1, &link->prevPos, &tmp1);
            PSVECScale(&accelScaled, dampA, &tmp2);
            PSVECAdd(&tmp1, &tmp2, &tmp1);
            PSVECSubtract(&tmp1, &link->prevPos, &link->vel);
            PSVECScale(&link->vel, dampB, &link->vel);
            memcpy(&link->prevPos, &link->pos, sizeof(Vec));
            memcpy(&link->pos, &tmp1, sizeof(Vec));
            if (link->pinned == 0) {
                pen = link->pos.y - link->radius;
                if (pen < 0.0f) {
                    link->pos.y = link->pos.y - pen * params->restitution;
                    link->prevPos.y = link->prevPos.y - (link->prevPos.y - link->radius) * params->restitution;
                }
                PSVECSubtract(&link->pos, &chompPos, &diff);
                mag = PSVECMag(&diff);
                if (4.5 + link->radius > mag) {
                    PSVECNormalize(&diff, &normal);
                    PSVECScale(&normal, (f32)(4.5 + link->radius - mag), &push);
                    link->pos.x += push.x * params->restitution;
                    link->pos.y += push.y * params->restitution;
                    link->pos.z += push.z * params->restitution;
                    PSVECSubtract(&link->prevPos, &chompPos, &diff);
                    mag = PSVECMag(&diff);
                    PSVECNormalize(&diff, &normal);
                    PSVECScale(&normal, (f32)(4.5 + link->radius - mag), &push);
                    link->prevPos.x += push.x * params->restitution;
                    link->prevPos.y += push.y * params->restitution;
                    link->prevPos.z += push.z * params->restitution;
                }
            }
        }
    }
}

// .text:0x000D2220 size:0x11C mapped:0x807112B4
void fn_3_D2220(StadiumObject* obj) {
    StadiumLink* links = obj->links;
    Mtx m;
    Vec axis = const_chompHitboxAxis;
    Vec force = lbl_3_rodata_25BC;
    Vec v;

    PSMTXRotAxisRad(m, &axis, const_pi_or_180 * obj->yaw);
    PSMTXMultVec(m, &lbl_3_rodata_24E8[0], &v);
    PSVECAdd(&v, &obj->pos, &v);
    v.y = v.y + 4.5;
    links[7].pos = v;
    links[7].prevPos = links[7].pos;
    chainChomp_simulateAndCollide(&lbl_3_bss_A8A8, obj->links, 8, &force, obj);
}

// .text:0x000D233C size:0x160 mapped:0x807113D0
InMemBallType* fn_3_D233C(StadiumObject* obj) {
    Mtx m;
    Vec d;
    Vec rot;
    Vec base = {1.0f, 0.0f, 0.0f};
    Vec axis = {0.0f, 1.0f, 0.0f};
    Vec p;

    p = obj->pos;
    if (g_Ball.AtBat_ContactResult >= 2) {
        return 0;
    }
    p.y = 4.5f;
    PSVECSubtract((Vec*)&g_Ball, &p, &d);
    d.y = 0.0f;
    if (PSVECMag(&d) < 23.0f) {
        f32 a;
        PSVECNormalize(&d, &d);
        PSMTXRotAxisRad(m, &axis, const_pi_or_180 * obj->yaw);
        PSMTXMultVec(m, &base, &rot);
        a = acos(PSVECDotProduct(&d, &rot));
        if (57.29578f * a <= 60.0f) {
            return &g_Ball;
        }
    }
    return 0;
}

// .text:0x000D249C size:0x4C mapped:0x80711530
BOOL fn_3_D249C(StadiumObject* obj) {
    Vec d;

    PSVECSubtract(&obj->links[7].pos, &obj->links[0].pos, &d);
    return PSVECMag(&d) > 14.250000447034836;
}

// .text:0x000D24E8 size:0x74 mapped:0x8071157C
void fn_3_D24E8(PalaceChompObj* obj, s8 fielderIdx) {
    Vec d;
    int idx = fielderIdx;

    PSVECSubtract((Vec*)&g_Fielders[idx].pos, &obj->pos, &d);
    d.y = 0.0f;
    PSVECNormalize(&d, &d);
    processFielderKnockout(idx, calculateAngleFromCoordinates(d.x, d.z));
}

// .text:0x000D255C size:0x128 mapped:0x807115F0
s8 fn_3_D255C(PalaceChompObj* obj) {
    Vec d;
    u8 right[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    u8 left[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    u8* sel;
    u8* p;
    InMemFielder* f;
    u32 i;

    if (obj->pos.y > 3.0) {
        return -1;
    }
    if (obj->pos.x > 0.0f) {
        sel = right;
    } else {
        sel = left;
    }
    p = sel;
    for (i = 0; i < 9; i++, p++) {
        f = &g_Fielders[*p];
        if (f != 0 && f->knockoutStatus == 0) {
            PSVECSubtract(&obj->pos, (Vec*)&f->pos, &d);
            if (PSVECMag(&d) <= 4.5) {
                return sel[i];
            }
        }
    }
    return -1;
}

// .text:0x000D2684 size:0x108 mapped:0x80711718
Vec* fn_3_D2684(StadiumObject* obj) {
    Vec d;
    u8 right[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    u8 left[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    u8* sel;
    u8* p;
    PalaceAnimObject* a;
    u32 i;

    if (obj->pos.x > 0.0f) {
        sel = right;
    } else {
        sel = left;
    }
    p = sel;
    for (i = 0; i < 4; i++, p++) {
        a = *(PalaceAnimObject**)(hugeAnimStruct + *p * 4 + 0x2C50);
        if (a != 0) {
            PSVECSubtract(&obj->pos, &a->pos, &d);
            if (PSVECMag(&d) <= 12.5f) {
                return &a->pos;
            }
        }
    }
    return 0;
}

// .text:0x000D278C size:0x280 mapped:0x80711820
void fn_3_D278C(PalaceChompObj* obj) {
    Mtx m;
    Vec d;
    Vec snd;
    Vec v;
    Vec force;
    Vec axis;
    StadiumLink* links;

    obj->pos.x = obj->pos.x + obj->velo.x;
    obj->pos.y = obj->pos.y + obj->velo.y;
    obj->pos.z = obj->pos.z + obj->velo.z;
    obj->velo.y = obj->velo.y - 0.4f;
    if (obj->pos.y < 0.0f) {
        obj->pos.y = 0.0f;
        PSVECSubtract(obj->homePos, &obj->pos, &d);
        if (5.0f >= PSVECMag(&d)) {
            obj->state = PALACE_CHOMP_AWAKE;
            if (obj->homePos->x < 0.0f) {
                obj->yaw = 0.0f;
            } else {
                obj->yaw = 180.0f;
            }
        } else {
            obj->velo.y = 0.2f;
        }
        memcpy(&snd, &obj->pos, sizeof(Vec));
        snd.y *= -1.0f;
        initializeStadiumObjectEmitter(stadiumHazardSoundIDs[g_d_GameSettings.StadiumID] + 2, &snd, 0, 10);
        spawnDust(&obj->pos);
    }
    CTRLSetTranslation((Control*)obj, obj->pos.x, -obj->pos.y, obj->pos.z);
    CTRLSetRotation((Control*)obj, 0.0f, obj->yaw, 0.0f);
    links = obj->links;
    axis = const_chompHitboxAxis;
    force = lbl_3_rodata_25BC;
    PSMTXRotAxisRad(m, &axis, const_pi_or_180 * obj->yaw);
    PSMTXMultVec(m, &lbl_3_rodata_24E8[0], &v);
    PSVECAdd(&v, &obj->pos, &v);
    v.y = v.y + 4.5;
    links[7].pos = v;
    links[7].prevPos = links[7].pos;
    chainChomp_simulateAndCollide(&lbl_3_bss_A8A8, obj->links, 8, &force, (StadiumObject*)obj);
}

// .text:0x000D2A0C size:0x6C4 mapped:0x80711AA0
void chomp_attack(PalaceChompObj* obj) {
    Mtx m;
    Vec chompPos;
    Vec d;
    Vec knockDir;
    Vec dir;
    Vec axisX;
    Vec snd;
    Vec snd2;
    Vec v;
    Vec force;
    Vec axis;
    Vec chainD;
    StadiumLink* links;
    f32 prevVy;
    s8 hit;
    f32 ang;
    f32 dot;

    axisX = lbl_3_rodata_252C[0];
    prevVy = obj->velo.y;
    obj->pos.x = obj->pos.x + obj->velo.x;
    obj->pos.y = obj->pos.y + obj->velo.y;
    obj->pos.z = obj->pos.z + obj->velo.z;
    obj->velo.y = obj->velo.y - 0.4f;
    if (prevVy > 0.0f && obj->velo.y <= 0.0f) {
        memcpy(&snd, &obj->pos, sizeof(Vec));
        snd.y *= -1.0f;
        initializeStadiumObjectEmitter(stadiumHazardSoundIDs[g_d_GameSettings.StadiumID] + 3, &snd, 0, 11);
    }
    if (obj->pos.y < 0.0f) {
        obj->pos.y = 0.0f;
        obj->velo.y = 0.3f;
        memcpy(&snd, &obj->pos, sizeof(Vec));
        snd.y *= -1.0f;
        initializeStadiumObjectEmitter(stadiumHazardSoundIDs[g_d_GameSettings.StadiumID] + 2, &snd, 0, 10);
        spawnDust(&obj->pos);
    }
    CTRLSetTranslation((Control*)obj, obj->pos.x, -obj->pos.y, obj->pos.z);
    CTRLSetRotation((Control*)obj, 0.0f, obj->yaw, 0.0f);
    links = obj->links;
    axis = const_chompHitboxAxis;
    force = lbl_3_rodata_25BC;
    PSMTXRotAxisRad(m, &axis, const_pi_or_180 * obj->yaw);
    PSMTXMultVec(m, &lbl_3_rodata_24E8[0], &v);
    PSVECAdd(&v, &obj->pos, &v);
    v.y = v.y + 4.5;
    links[7].pos = v;
    links[7].prevPos = links[7].pos;
    chainChomp_simulateAndCollide(&lbl_3_bss_A8A8, obj->links, 8, &force, (StadiumObject*)obj);

    if (g_Ball.AtBat_ContactResult < BALL_RESULT_TYPE_FIELDED) {
        chompPos = obj->pos;
        chompPos.y = chompPos.y + 4.5;
        PSVECSubtract((Vec*)&g_Ball.AtBat_Contact_BallPos, &chompPos, &d);
        if (g_Ball.AtBat_Contact_BallPos.y < chompPos.y) {
            d.y = 0.0f;
        }
        if (PSVECMag(&d) < 4.5) {
            PSVECNormalize(&d, &knockDir);
            g_Ball.AtBat_Contact_BallPos.x = 4.5 * knockDir.x + chompPos.x;
            g_Ball.AtBat_Contact_BallPos.z = 4.5 * knockDir.z + chompPos.z;
            g_Ball.physicsSubstruct.velocity.x = 0.3 * knockDir.x;
            g_Ball.physicsSubstruct.velocity.y = 0.3 * knockDir.y;
            g_Ball.physicsSubstruct.velocity.z = 0.3 * knockDir.z;
            obj->state = PALACE_CHOMP_HOPPING_HOME;
            memcpy(&snd2, &g_Ball, sizeof(Vec));
            snd2.y *= -1.0f;
            initializeStadiumObjectEmitter(stadiumHazardSoundIDs[g_d_GameSettings.StadiumID] + 5, &snd2, 0, 13);
            processFielderAutoCatch();
            g_FieldingLogic.knockoutFinished = 1;
            chompCollision_processStarHitVariables();
            lbl_3_bss_A820[5] = g_Ball.AtBat_Contact_BallPos.z;
            lbl_3_bss_A898[1] = 1;
            lbl_3_bss_A820[3] = g_Ball.AtBat_Contact_BallPos.x;
            lbl_3_bss_A820[4] = -g_Ball.AtBat_Contact_BallPos.y;
        }
    }
    PSVECSubtract(&obj->links[7].pos, &obj->links[0].pos, &chainD);
    if (PSVECMag(&chainD) > 14.250000447034836) {
        obj->state = PALACE_CHOMP_HOPPING_HOME;
    }
    hit = fn_3_D255C(obj);
    if (hit >= 0) {
        fn_3_D24E8(obj, hit);
        obj->state = PALACE_CHOMP_HOPPING_HOME;
    }
    if (obj->state == PALACE_CHOMP_HOPPING_HOME) {
        PSVECNormalize(&obj->velo, &dir);
        dir.x = dir.x * -1.0f;
        dir.z = dir.z * -1.0f;
        obj->velo.x = 0.15 * dir.x;
        obj->velo.y = 0.2f;
        obj->velo.z = 0.15 * dir.z;
        dot = PSVECDotProduct(&axisX, &dir);
        dot = acos(dot);
        ang = -(57.29578f * dot);
        if (dir.z < 0.0f) {
            ang *= -1.0f;
        }
        obj->yaw = ang;
        actorRelated(obj->effect, 0, 1);
    }
}

// .text:0x000D30D0 size:0x5E0 mapped:0x80712164
void chompState3_longDistanceAttack_Stalk(PalaceChompObj* obj) {
    Mtx m;
    Vec axisX;
    Vec ballFlat;
    Vec chompFlat;
    Vec d;
    Vec dir;
    Vec snd;
    Vec v;
    Vec force;
    Vec axis;
    StadiumLink* links;
    f32 prevVy;
    s8 hit;
    f32 deg;
    f32 ang;
    f32 dot;

    axisX = lbl_3_rodata_2520;
    prevVy = obj->velo.y;
    obj->pos.y = obj->pos.y + obj->velo.y;
    obj->velo.y = obj->velo.y - 0.4f;
    if (prevVy > 0.0f && obj->velo.y <= 0.0f) {
        memcpy(&snd, &obj->pos, sizeof(Vec));
        snd.y *= -1.0f;
        initializeStadiumObjectEmitter(stadiumHazardSoundIDs[g_d_GameSettings.StadiumID] + 3, &snd, 0, 11);
    }
    if (obj->pos.y < 0.0f) {
        obj->pos.y = 0.0f;
        obj->velo.y = 0.4f;
        chompFlat.x = obj->pos.x;
        chompFlat.y = 0.0f;
        chompFlat.z = obj->pos.z;
        ballFlat.x = g_Ball.AtBat_Contact_BallPos.x;
        ballFlat.y = 0.0f;
        ballFlat.z = g_Ball.AtBat_Contact_BallPos.z;
        PSVECSubtract(&ballFlat, &chompFlat, &d);
        if (PSVECMag(&d) == 0.0f) {
            d.z = 0.0f;
            d.y = 0.0f;
            d.x = 1.0f;
        }
        PSVECNormalize(&d, &dir);
        dot = PSVECDotProduct(&axisX, &dir);
        if (dot > 1.0f) {
            dot = 1.0f;
        } else if (dot < -1.0f) {
            dot = -1.0f;
        }
        ang = acos(dot);
        if (dir.z < 0.0f) {
            ang = 6.2831855f - ang;
        }
        deg = 57.29578f * ang;
        if ((PSVECMag(&d) <= 12.5f || g_Ball.ballState == BALL_STATE_HELD) && obj->attacksRemaining > 0 &&
            g_Ball.AtBat_Contact_BallPos.y <= 10.0) {
            obj->state = PALACE_CHOMP_ATTACKING;
            obj->targetYaw = deg;
            obj->velo.x = 0.26f * (f32)cos(const_pi_or_180 * obj->targetYaw);
            obj->velo.y = 0.0f;
            obj->velo.z = 0.26f * (f32)sin(const_pi_or_180 * obj->targetYaw);
            obj->attacksRemaining--;
        } else if (PSVECMag(&d) > 21.25) {
            obj->state = PALACE_CHOMP_AWAKE;
            obj->velo.y = 0.0f;
            actorRelated(obj->effect, 0, 1);
        }
        memcpy(&snd, &obj->pos, sizeof(Vec));
        snd.y *= -1.0f;
        initializeStadiumObjectEmitter(stadiumHazardSoundIDs[g_d_GameSettings.StadiumID] + 2, &snd, 0, 10);
        obj->yaw = -deg;
        spawnDust(&obj->pos);
    }
    CTRLSetTranslation((Control*)obj, obj->pos.x, -obj->pos.y, obj->pos.z);
    CTRLSetRotation((Control*)obj, 0.0f, obj->yaw, 0.0f);
    links = obj->links;
    axis = const_chompHitboxAxis;
    force = lbl_3_rodata_25BC;
    PSMTXRotAxisRad(m, &axis, const_pi_or_180 * obj->yaw);
    PSMTXMultVec(m, &lbl_3_rodata_24E8[0], &v);
    PSVECAdd(&v, &obj->pos, &v);
    v.y = v.y + 4.5;
    links[7].pos = v;
    links[7].prevPos = links[7].pos;
    chainChomp_simulateAndCollide(&lbl_3_bss_A8A8, obj->links, 8, &force, (StadiumObject*)obj);
    hit = fn_3_D255C(obj);
    if (hit >= 0) {
        fn_3_D24E8(obj, hit);
    }
}

// .text:0x000D36B0 size:0x1D0 mapped:0x80712744
void fn_3_D36B0(PalaceChompObj* obj) {
    obj->pos.y = obj->pos.y + obj->velo.y;
    obj->velo.y = obj->velo.y - 0.4f;
    if (obj->pos.y < 0.0f) {
        obj->pos.y = 0.0f;
        if ((obj->flags & 4) == 0) {
            obj->priorState = obj->state;
            obj->state = PALACE_CHOMP_AWAKE;
            actorRelated(obj->effect, 0, 1);
        }
        obj->flags &= 0xFB;
        spawnDust(&obj->pos);
    }
    {
        StadiumLink* links = obj->links;
        Mtx m;
        Vec v;
        Vec force;
        Vec axis;

        axis = const_chompHitboxAxis;
        force = lbl_3_rodata_25BC;
        PSMTXRotAxisRad(m, &axis, const_pi_or_180 * obj->yaw);
        PSMTXMultVec(m, &lbl_3_rodata_24E8[0], &v);
        PSVECAdd(&v, &obj->pos, &v);
        v.y = v.y + 4.5;
        links[7].pos = v;
        links[7].prevPos = links[7].pos;
        chainChomp_simulateAndCollide(&lbl_3_bss_A8A8, obj->links, 8, &force, (StadiumObject*)obj);
    }
    CTRLSetRotation((Control*)obj, 0.0f, obj->yaw, 0.0f);
    CTRLSetTranslation((Control*)obj, obj->pos.x, -obj->pos.y, obj->pos.z);
}

// .text:0x000D3880 size:0x45C mapped:0x80712914
void chompState1_awake(PalaceChompObj* obj) {
    Mtx m;
    Vec diff;
    Vec dir;
    Vec pos;
    Vec yawAxis = const_zeroYawAxis;
    Vec facing;
    Vec sndPos;
    Vec sndVel;
    Vec v;
    Vec force;
    Vec axis;
    StadiumLink* links;
    f32 ang;
    f32 dot;
    f32 mag;

    memcpy(&pos, &obj->pos, sizeof(Vec));
    pos.y = pos.y + 4.5;
    if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL && !(g_Ball.AtBat_Contact_BallPos.y > 10.0)) {
        PSVECSubtract((Vec*)&g_Ball.AtBat_Contact_BallPos, &pos, &diff);
        memcpy(&dir, &diff, sizeof(Vec));
        dir.y = 0.0f;
        if (PSVECMag(&dir) == 0.0f) {
            dir.x = 1.0f;
        }
        PSVECNormalize(&dir, &dir);
        memset(&facing, 0, sizeof(Vec));
        facing.x = cos(const_pi_or_180 * -obj->yaw);
        facing.z = sin(const_pi_or_180 * -obj->yaw);
        PSVECNormalize(&facing, &facing);
        dot = PSVECDotProduct(&dir, &facing);
        dot = acos(dot);
        if (57.29578f * dot <= 60.0f) {
            PSVECNormalize(&yawAxis, &yawAxis);
            dot = PSVECDotProduct(&dir, &yawAxis);
            if (dot > 1.0f) {
                dot = 1.0f;
            } else if (dot < -1.0f) {
                dot = -1.0f;
            }
            dot = acos(dot);
            ang = 57.29578f * dot;
            if (dir.z < 0.0f) {
                ang *= -1.0f;
            }
            obj->yaw = -ang;
            mag = PSVECMag(&diff);
            if (mag <= 21.25 && obj->attacksRemaining > 0) {
                obj->targetYaw = ang;
                if (mag <= 12.5f || g_Ball.ballState == BALL_STATE_HELD) {
                    obj->state = PALACE_CHOMP_ATTACKING;
                    obj->velo.x = 0.26f * (f32)cos(const_pi_or_180 * obj->targetYaw);
                    obj->velo.y = 0.3f;
                    obj->velo.z = 0.26f * (f32)sin(const_pi_or_180 * obj->targetYaw);
                    obj->attacksRemaining--;
                } else {
                    obj->state = PALACE_CHOMP_STALKING;
                    obj->velo.y = 0.4f;
                }
                actorRelated(obj->effect, 0, 4);
                initializeStadiumObjectEmitter(stadiumHazardSoundIDs[g_d_GameSettings.StadiumID] + 4, &sndPos,
                                               &sndVel, 12);
            }
        }
    }
    CTRLSetRotation((Control*)obj, 0.0f, obj->yaw, 0.0f);
    links = obj->links;
    axis = const_chompHitboxAxis;
    force = lbl_3_rodata_25BC;
    PSMTXRotAxisRad(m, &axis, const_pi_or_180 * obj->yaw);
    PSMTXMultVec(m, &lbl_3_rodata_24E8[0], &v);
    PSVECAdd(&v, &obj->pos, &v);
    v.y = v.y + 4.5;
    links[7].pos = v;
    links[7].prevPos = links[7].pos;
    chainChomp_simulateAndCollide(&lbl_3_bss_A8A8, obj->links, 8, &force, (StadiumObject*)obj);
}

// .text:0x000D3CDC size:0x278 mapped:0x80712D70
void chompState0(PalaceChompObj* obj) {
    Mtx m;
    Vec d;
    Vec v;
    Vec force;
    Vec axis;
    u8 right[4] = {2, 3, 7, 8};
    u8 left[4] = {4, 5, 6, 7};
    u8* sel;
    u8* p;
    PalaceAnimObject* a;
    StadiumLink* links;
    u32 i;

    if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
        if (obj->flags & 2) {
            obj->flags &= 0xFD;
        }
    } else if ((obj->flags & 2) == 0) {
        if (obj->pos.x > 0.0f) {
            sel = right;
        } else {
            sel = left;
        }
        p = sel;
        for (i = 0; i < 4; i++, p++) {
            a = *(PalaceAnimObject**)(hugeAnimStruct + *p * 4 + 0x2C50);
            if (a != 0) {
                PSVECSubtract(&obj->pos, &a->pos, &d);
                if (PSVECMag(&d) <= 12.5f) {
                    obj->flags |= 2;
                    if (rng(10) < 4) {
                        obj->flags &= 0xFB;
                        obj->_CC = 5;
                        obj->priorState = obj->state;
                        obj->state = PALACE_CHOMP_WAKING;
                        obj->velo.y = 0.5f;
                        actorRelated(obj->effect, 0, 3);
                    }
                    break;
                }
            }
        }
    }
    links = obj->links;
    axis = const_chompHitboxAxis;
    force = lbl_3_rodata_25BC;
    PSMTXRotAxisRad(m, &axis, const_pi_or_180 * obj->yaw);
    PSMTXMultVec(m, &lbl_3_rodata_24E8[0], &v);
    PSVECAdd(&v, &obj->pos, &v);
    v.y = v.y + 4.5;
    links[7].pos = v;
    links[7].prevPos = links[7].pos;
    chainChomp_simulateAndCollide(&lbl_3_bss_A8A8, obj->links, 8, &force, (StadiumObject*)obj);
}

// .text:0x000D3F54 size:0x82C mapped:0x80712FE8
void palaceChainChompControl(PalaceChompObj* obj) {
    if (g_GameLogic.gameStatus == GAME_STATUS_INNING_TRANSITION) {
        if (obj->_CD == 0) {
            someCTRLButNotCalled2(obj);
        }
    } else {
        if (obj->_CD != 0) {
            obj->_CD = 0;
        }
        if (g_GameLogic.gameStatus == GAME_STATUS_DEFAULT) {
            if (obj->state != PALACE_CHOMP_ASLEEP) {
                obj->state = PALACE_CHOMP_AWAKE;
                actorRelated(obj->effect, 0, 1);
            }
            someCTRLButNotCalled(obj);
            obj->attacksRemaining = 1;
        } else {
            if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL) {
                obj->hasShadow = 1;
            }
            switch (obj->state) {
            case PALACE_CHOMP_ASLEEP:
                chompState0(obj);
                break;
            case PALACE_CHOMP_AWAKE:
                chompState1_awake(obj);
                break;
            case PALACE_CHOMP_WAKING:
                fn_3_D36B0(obj);
                break;
            case PALACE_CHOMP_STALKING:
                chompState3_longDistanceAttack_Stalk(obj);
                break;
            case PALACE_CHOMP_ATTACKING:
                chomp_attack(obj);
                break;
            case PALACE_CHOMP_HOPPING_HOME: {
                Mtx m;
                Vec d;
                Vec snd;
                Vec v;
                Vec force;
                Vec axis;
                StadiumLink* links;

                obj->pos.x = obj->pos.x + obj->velo.x;
                obj->pos.y = obj->pos.y + obj->velo.y;
                obj->pos.z = obj->pos.z + obj->velo.z;
                obj->velo.y = obj->velo.y - 0.4f;
                if (obj->pos.y < 0.0f) {
                    obj->pos.y = 0.0f;
                    PSVECSubtract(obj->homePos, &obj->pos, &d);
                    if (5.0f >= PSVECMag(&d)) {
                        obj->state = PALACE_CHOMP_AWAKE;
                        if (obj->homePos->x < 0.0f) {
                            obj->yaw = 0.0f;
                        } else {
                            obj->yaw = 180.0f;
                        }
                    } else {
                        obj->velo.y = 0.2f;
                    }
                    memcpy(&snd, &obj->pos, sizeof(Vec));
                    snd.y *= -1.0f;
                    initializeStadiumObjectEmitter(stadiumHazardSoundIDs[g_d_GameSettings.StadiumID] + 2, &snd, 0,
                                                   10);
                    spawnDust(&obj->pos);
                }
                CTRLSetTranslation((Control*)obj, obj->pos.x, -obj->pos.y, obj->pos.z);
                CTRLSetRotation((Control*)obj, 0.0f, obj->yaw, 0.0f);
                links = obj->links;
                axis = const_chompHitboxAxis;
                force = lbl_3_rodata_25BC;
                PSMTXRotAxisRad(m, &axis, const_pi_or_180 * obj->yaw);
                PSMTXMultVec(m, &lbl_3_rodata_24E8[0], &v);
                PSVECAdd(&v, &obj->pos, &v);
                v.y = v.y + 4.5;
                links[7].pos = v;
                links[7].prevPos = links[7].pos;
                chainChomp_simulateAndCollide(&lbl_3_bss_A8A8, obj->links, 8, &force, (StadiumObject*)obj);
                break;
            }
            }
        }
    }
}

// .text:0x000D4780 size:0x524 mapped:0x80713814
void fn_3_D4780(StadiumObject* obj) {
    PalaceObjControl ctrl;
    Mtx m;
    Vec far;
    Vec near;
    Vec diff;
    u32 i;
    u32 j;
    f32 mag;
    f32 amp;
    f32 end;

    near = lbl_3_rodata_24E8[0];
    memcpy(&near, &lbl_3_rodata_24E8[0], sizeof(Vec));
    if (chompPlacementConfig[obj->_9C].sideSelector == 0) {
        memcpy(&far, &lbl_3_rodata_24DC, sizeof(Vec));
    } else {
        memcpy(&far, &lbl_3_rodata_24D0, sizeof(Vec));
    }
    far.y = 0.5f;
    near.y = -0.5f;
    ctrl.ctrl.type = 0;
    if (obj->_CA == 0) {
        CTRLSetRotation(&ctrl.ctrl, chompPlacementConfig[obj->_9C].sleepRotation.x,
                        -chompPlacementConfig[obj->_9C].sleepRotation.y,
                        chompPlacementConfig[obj->_9C].sleepRotation.z);
    } else {
        CTRLSetRotation(&ctrl.ctrl, chompPlacementConfig[obj->_9C].awakeRotation.x,
                        -chompPlacementConfig[obj->_9C].awakeRotation.y,
                        chompPlacementConfig[obj->_9C].awakeRotation.z);
    }
    CTRLBuildMatrix(&ctrl.ctrl, m);
    PSMTXMultVec(m, &near, &near);
    near.y *= -1.0f;
    near.x = near.x + obj->pos.x;
    near.y = near.y + obj->pos.y;
    near.z = near.z + obj->pos.z;
    PSVECSubtract(&near, &far, &diff);
    mag = PSVECMag(&diff);
    obj->links[0].pos.x = 0.0f * diff.x + far.x;
    obj->links[0].pos.y = 0.0f * diff.y + far.y;
    obj->links[0].pos.z = 0.0f * diff.z + far.z;
    obj->links[1].pos.x = 0.14285715f * diff.x + far.x;
    obj->links[1].pos.y = 0.14285715f * diff.y + far.y;
    obj->links[1].pos.z = 0.14285715f * diff.z + far.z;
    obj->links[2].pos.x = 0.2857143f * diff.x + far.x;
    obj->links[2].pos.y = 0.2857143f * diff.y + far.y;
    obj->links[2].pos.z = 0.2857143f * diff.z + far.z;
    obj->links[3].pos.x = 0.42857143f * diff.x + far.x;
    obj->links[3].pos.y = 0.42857143f * diff.y + far.y;
    obj->links[3].pos.z = 0.42857143f * diff.z + far.z;
    obj->links[4].pos.x = 0.5714286f * diff.x + far.x;
    obj->links[4].pos.y = 0.5714286f * diff.y + far.y;
    obj->links[4].pos.z = 0.5714286f * diff.z + far.z;
    obj->links[5].pos.x = 0.71428573f * diff.x + far.x;
    obj->links[5].pos.y = 0.71428573f * diff.y + far.y;
    obj->links[5].pos.z = 0.71428573f * diff.z + far.z;
    obj->links[6].pos.x = 0.85714287f * diff.x + far.x;
    obj->links[6].pos.y = 0.85714287f * diff.y + far.y;
    obj->links[6].pos.z = 0.85714287f * diff.z + far.z;
    end = 1.0f;
    obj->links[7].pos.x = end * diff.x + far.x;
    obj->links[7].pos.y = end * diff.y + far.y;
    obj->links[7].pos.z = end * diff.z + far.z;
    amp = 7.125f - mag * 0.5f;
    for (i = 0; i < 8; i++) {
        obj->links[i].pos.y -= amp * (f32)sin(3.1415927f * ((f32)i / 7.0f));
        if (obj->links[i].pos.y < obj->links[i].radius) {
            obj->links[i].pos.y = obj->links[i].radius;
        }
    }
    for (j = 0; j < 8; j++) {
        memcpy(&obj->links[j].prevPos, &obj->links[j].pos, sizeof(Vec));
        memset(&obj->links[j].vel, 0, sizeof(Vec));
        memset(&obj->links[j].accel, 0, sizeof(Vec));
    }
}

// .text:0x000D4CA4 size:0x15C mapped:0x80713D38
void someCTRLButNotCalled(PalaceChompObj* obj) {
    ((Control*)obj)->type = 0;
    CTRLSetScale((Control*)obj, 0.75f, 0.75f, 0.75f);
    if (obj->state == PALACE_CHOMP_ASLEEP) {
        CTRLSetRotation((Control*)obj, chompPlacementConfig[obj->index].sleepRotation.x,
                        -chompPlacementConfig[obj->index].sleepRotation.y,
                        chompPlacementConfig[obj->index].sleepRotation.z);
        obj->yaw = -chompPlacementConfig[obj->index].sleepRotation.y;
    } else {
        CTRLSetRotation((Control*)obj, chompPlacementConfig[obj->index].awakeRotation.x,
                        -chompPlacementConfig[obj->index].awakeRotation.y,
                        chompPlacementConfig[obj->index].awakeRotation.z);
        obj->yaw = -chompPlacementConfig[obj->index].awakeRotation.y;
    }
    CTRLSetTranslation((Control*)obj, chompPlacementConfig[obj->index].position.x,
                       chompPlacementConfig[obj->index].position.y, chompPlacementConfig[obj->index].position.z);
    obj->pos.x = chompPlacementConfig[obj->index].position.x;
    obj->pos.y = -chompPlacementConfig[obj->index].position.y;
    obj->pos.z = chompPlacementConfig[obj->index].position.z;
    fn_3_D4780((StadiumObject*)obj);
}

// .text:0x000D4E00 size:0x21C mapped:0x80713E94
void someCTRLButNotCalled2(PalaceChompObj* obj) {
    obj->state = rand() % 10;
    if (obj->state < 3) {
        obj->state = PALACE_CHOMP_ASLEEP;
        actorRelated(obj->effect, 0, 2);
    } else {
        obj->state = PALACE_CHOMP_AWAKE;
        actorRelated(obj->effect, 0, 1);
    }
    obj->priorState = obj->state;
    obj->hasShadow = 1;
    ((Control*)obj)->type = 0;
    CTRLSetScale((Control*)obj, 0.75f, 0.75f, 0.75f);
    if (obj->state == PALACE_CHOMP_ASLEEP) {
        CTRLSetRotation((Control*)obj, chompPlacementConfig[obj->index].sleepRotation.x,
                        -chompPlacementConfig[obj->index].sleepRotation.y,
                        chompPlacementConfig[obj->index].sleepRotation.z);
        obj->yaw = -chompPlacementConfig[obj->index].sleepRotation.y;
    } else {
        CTRLSetRotation((Control*)obj, chompPlacementConfig[obj->index].awakeRotation.x,
                        -chompPlacementConfig[obj->index].awakeRotation.y,
                        chompPlacementConfig[obj->index].awakeRotation.z);
        obj->yaw = -chompPlacementConfig[obj->index].awakeRotation.y;
    }
    CTRLSetTranslation((Control*)obj, chompPlacementConfig[obj->index].position.x,
                       chompPlacementConfig[obj->index].position.y, chompPlacementConfig[obj->index].position.z);
    obj->pos.x = chompPlacementConfig[obj->index].position.x;
    obj->pos.y = -chompPlacementConfig[obj->index].position.y;
    obj->pos.z = chompPlacementConfig[obj->index].position.z;
    fn_3_D4780((StadiumObject*)obj);
    obj->flags = 0;
    obj->attacksRemaining = 1;
    if (activeStadiumEmitterID != -1) {
        updateAndRemoveStadiumEmitter(activeStadiumEmitterID);
        activeStadiumEmitterID = -1;
    }
    obj->_CD = 1;
}

// .text:0x000D501C size:0x100 mapped:0x807140B0
void fn_3_D501C(StadiumLink* links) {
    StadiumLink* link;
    u32 i;

    if (links != NULL) {
        memset(links, 0, sizeof(StadiumLink));
        link = links;
        for (i = 0; i < 8; i++, link++) {
            if (i == 7) {
                link->weight = lbl_3_data_188E0[0];
                link->radius = 0.504375f;
                link->pinned = 1;
            } else {
                if (i == 0) {
                    link->pinned = 1;
                }
                link->weight = lbl_3_data_188E0[0];
                link->radius = 0.504375f;
            }
            link->mobility = 1.0f / link->weight;
            memset(&link->pos, 0, 0x18);
            memset(&link->vel, 0, sizeof(Vec));
            memset(&link->accel, 0, sizeof(Vec));
        }
    }
}

// .text:0x000D511C size:0x2A4 mapped:0x807141B0
void fn_3_D511C(void) {
    memset(&lbl_3_bss_A8A8, 0, sizeof(ChainChompPhysicsParams));
    palaceInitChainParams(&lbl_3_bss_A8A8);
    fn_3_D501C((StadiumLink*)lbl_3_bss_A8D0 + 12);
    fn_3_D501C((StadiumLink*)lbl_3_bss_A8D0 + 4);
}

static const char noReturnValueString[] =
    "//OZ \x96\xDF\x82\xE8\x92\x6C\x82\xCC\x96\xB3\x82\xA2\x95\x94\x95\xAA\x82\xC9\x97\x88\x82\xDC\x82\xB5\x82\xBD\x81\x42\n";

// .text:0x000D53C0 size:0x84 mapped:0x80714454
int fn_3_D53C0(u8 id) {
    StadiumDrawOrder* p = stadiumObjectCollision.objectScratch + stadiumObjectCollision.objectCount;
    u32 i;

    for (i = stadiumObjectCollision.objectCount; i != 0; p--, i--) {
        if (id == p[-1].index) {
            return i - 1;
        }
    }
    OSPanic("sta_c2.c", 0x863, noReturnValueString);
    return 0;
}

// .text:0x000D5444 size:0x2C mapped:0x807144D8
int fn_3_D5444(const u32* a, const u32* b) {
    u32 x = *a;
    u32 y = *b;

    if (x < y) {
        return -1;
    }
    return x > y;
}

// .text:0x000D5470 size:0x24 mapped:0x80714504
int fn_3_D5470(const f32* a, const f32* b) {
    f32 x = *a;
    f32 y = *b;

    if (x < y) {
        return -1;
    }
    return x > y;
}

// .text:0x000D5494 size:0x158 mapped:0x80714528
void fn_3_D5494(Mtx view) {
    Vec pos;
    u32 i;

    memcpy(&pos, &g_Ball, sizeof(Vec));
    PSMTXMultVec(view, &pos, &pos);
    for (i = 0; i < stadiumObjectCollision.objectCount; i++) {
        StadiumDrawOrder* entry = &stadiumObjectCollision.objectScratch[i];
        StadiumObject* obj = &stadiumObjectCollision.objects[entry->index];

        if (obj->hasShadow) {
            u8 kind = obj->_9D[0];

            if (kind == 0 || (u8)(kind - 4) <= 1 || (kind > 7 && kind < 11)) {
                entry->depth = 1.0f;
            } else {
                f32 depth = entry->depth;
                f32 nearZ = 2.0f + pos.z;

                if (depth < nearZ) {
                    entry->depth = 1.0f;
                } else if (depth > 10.0f + pos.z) {
                    entry->depth = 0.25f;
                } else {
                    entry->depth = 1.0 - 0.75f * ((depth - nearZ) * 0.125f);
                }
            }
        }
    }
}

// .text:0x000D55EC size:0x580 mapped:0x80714680
void processPalaceObjectCollisions(Mtx view, struct _StadiumDrawOrder* order) {
    StadiumDrawOrder sorted[3];
    int slots[3];
    Vec pos;
    StadiumDrawOrder* back;
    StadiumDrawOrder* front;
    StadiumDrawOrder* p;
    StadiumDrawOrder* scratch;
    int remaining;
    int count;
    StadiumObject* obj;
    int i;

    if (stadiumObjectCollision.gameStatusIsLiveBall) {
        count = 0;
        p = order;
        i = stadiumObjectCollision.objectCount - 1;
        obj = &stadiumObjectCollision.objects[i];
        do {
            if (!obj->hasShadow) {
                p->depth = -512.0f;
                count++;
                p->index = i;
                p++;
            }
            obj--;
        } while (i-- != 0);

        remaining = stadiumObjectCollision.objectCount;
        i = stadiumObjectCollision.objectCount - 1;
        obj = &stadiumObjectCollision.objects[i];
        back = order + stadiumObjectCollision.objectCount;
        front = order + count;
        do {
            if (obj->hasShadow) {
                if (obj->fadeByDepth) {
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

        p = allocateAlignedMemoryBlock(32, (stadiumObjectCollision.objectCount - remaining) * sizeof(StadiumDrawOrder));
        fn_800C07BC(order + remaining, p, stadiumObjectCollision.objectCount - remaining, sizeof(StadiumDrawOrder),
                    (s32(*)(const f32*, const f32*))fn_3_D5470);
        unkLoadingCleanupRelated(p);

        scratch =
            allocateAlignedMemoryBlock(32, (stadiumObjectCollision.objectCount - remaining) * sizeof(StadiumDrawOrder));
        for (i = 0; i < lbl_3_bss_A027; i++) {
            PalaceLinkedObj* linked = (PalaceLinkedObj*)&stadiumObjectCollision.objects[lbl_3_bss_A026 + i];

            if (linked->nado->_D1 != 0) {
                slots[0] = fn_3_D53C0(linked->animPhase);
                slots[1] = fn_3_D53C0(linked->nado->_D2[0]);
                slots[2] = fn_3_D53C0(linked->other->id);
                sorted[0] = order[slots[0]];
                sorted[1] = order[slots[1]];
                sorted[2] = order[slots[2]];
                fn_800C07BC(slots, scratch, 3, sizeof(int), (s32(*)(const f32*, const f32*))fn_3_D5444);
                order[slots[0]] = sorted[0];
                order[slots[1]] = sorted[1];
                order[slots[2]] = sorted[2];
            }
        }
        unkLoadingCleanupRelated(scratch);
        fn_3_D5494(view);
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

// .text:0x000D5B6C size:0x120 mapped:0x80714C00
void fn_3_D5B6C(s32* idx) {
    PalaceObjControl ctrl;
    Mtx m;
    int off;
    StadiumObject* obj;

    off = (u16)(stadiumObjectCollision.vertexOffsets[*idx - 1] + stadiumObjectCollision.hazardData[*idx - 1]);
    stadiumObjectCollision.vertexOffsets[*idx] = off;
    ((s32*)stadiumObjectCollision.vertexData)[off] = lbl_3_bss_A020;
    stadiumObjectCollision.hazardData[*idx]++;
    obj = &stadiumObjectCollision.objects[lbl_3_bss_A020];
    ctrl = *(PalaceObjControl*)obj;
    CTRLBuildMatrix(&ctrl.ctrl, m);
    transformVectorsUpdateBoundingBox(m, (StadiumMeshData*)obj->triangles);
    storeBoundingBoxCoordinates(&((Vec*)stadiumObjectCollision.vertexDataArray)[*idx * 2],
                                &((Vec*)stadiumObjectCollision.vertexDataArray)[*idx * 2 + 1]);
    (*idx)++;
}

// .text:0x000D5C8C size:0x1F4 mapped:0x80714D20
void fn_3_D5C8C(s32* idx) {
    Mtx m;
    Mtx scale;
    PalaceObjControl ctrl;
    int off;
    PalaceSandStarPlacement* cfg;
    int i;
    int j;
    StadiumObject* obj;
    int k;

    PSMTXIdentity(scale);
    PSMTXScale(scale, 2.0f, 2.0f, 2.0f);
    for (i = 0; i < 5; i++) {
        off = (u16)(stadiumObjectCollision.vertexOffsets[*idx - 1] + stadiumObjectCollision.hazardData[*idx - 1]);
        stadiumObjectCollision.vertexOffsets[*idx] = off;
        initBoundingBoxLimits();
        cfg = sandStarPlacementConfig.entries;
        for (j = 0; j < lbl_3_bss_A023; cfg++, j++) {
            if (i == cfg->group && cfg->usedFlag != 0xD) {
                k = j + lbl_3_bss_A022;
                if (stadiumObjectCollision.objects[k]._90b1) {
                    ((s32*)stadiumObjectCollision.vertexData)[off] = k;
                    stadiumObjectCollision.hazardData[*idx]++;
                    obj = &stadiumObjectCollision.objects[k];
                    off++;
                    ctrl = *(PalaceObjControl*)obj;
                    CTRLBuildMatrix(&ctrl.ctrl, m);
                    PSMTXConcat(m, scale, m);
                    transformVectorsUpdateBoundingBox(m, (StadiumMeshData*)obj->triangles);
                    m[1][3] = m[1][3] * 100.0f;
                    transformVectorsUpdateBoundingBox(m, (StadiumMeshData*)obj->triangles);
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

// .text:0x000D5E80 size:0x240 mapped:0x80714F14
void stadiumObjCollisionRelated_Palace(s32* idx) {
    PalaceObjControl ctrl;
    Mtx m;
    int off;
    PalaceSlotPlacement* cfg;
    int i;
    int j;
    StadiumObject* obj;
    int k;
    f32 r;

    for (i = 0; i < 5; i++) {
        off = (u16)(stadiumObjectCollision.vertexOffsets[*idx - 1] + stadiumObjectCollision.hazardData[*idx - 1]);
        stadiumObjectCollision.vertexOffsets[*idx] = off;
        initBoundingBoxLimits();
        cfg = lbl_3_data_1849C;
        for (j = 0; j < lbl_3_bss_A025; cfg++, j++) {
            if (i == cfg->group && cfg->usedFlag != 0xD) {
                k = j + lbl_3_bss_A024;
                if (stadiumObjectCollision.objects[k]._90b1) {
                    ((s32*)stadiumObjectCollision.vertexData)[off] = k;
                    stadiumObjectCollision.hazardData[*idx]++;
                    obj = &stadiumObjectCollision.objects[k];
                    off++;
                    ctrl = *(PalaceObjControl*)obj;
                    CTRLBuildMatrix(&ctrl.ctrl, m);
                    transformVectorsUpdateBoundingBox(m, (StadiumMeshData*)obj->triangles);
                    r = *(f32*)&obj->anchorA;
                    CTRLSetTranslation(&ctrl.ctrl, r + lbl_3_data_1849C[obj->_9C].x, 0.0f,
                                       r + lbl_3_data_1849C[obj->_9C].z);
                    CTRLBuildMatrix(&ctrl.ctrl, m);
                    transformVectorsUpdateBoundingBox(m, (StadiumMeshData*)obj->triangles);
                    r = *(f32*)&obj->anchorA;
                    CTRLSetTranslation(&ctrl.ctrl, lbl_3_data_1849C[obj->_9C].x - r, 0.0f,
                                       lbl_3_data_1849C[obj->_9C].z - r);
                    CTRLBuildMatrix(&ctrl.ctrl, m);
                    transformVectorsUpdateBoundingBox(m, (StadiumMeshData*)obj->triangles);
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

// .text:0x000D60C0 size:0x230 mapped:0x80715154
void fn_3_D60C0(s32* idx) {
    PalaceObjControl ctrl;
    Mtx m;
    int off;
    PalaceTornadoPlacement* cfg;
    int i;
    int j;
    StadiumObject* obj;
    int k;

    for (i = 0; i < 3; i++) {
        off = (u16)(stadiumObjectCollision.vertexOffsets[*idx - 1] + stadiumObjectCollision.hazardData[*idx - 1]);
        stadiumObjectCollision.vertexOffsets[*idx] = off;
        initBoundingBoxLimits();
        cfg = TornadoPlacementConfig;
        for (j = 0; j < lbl_3_bss_A02B; cfg++, j++) {
            if (i == cfg->group && cfg->usedFlag != 0xD) {
                k = j + lbl_3_bss_A02A;
                if (stadiumObjectCollision.objects[k]._90b1) {
                    ((s32*)stadiumObjectCollision.vertexData)[off] = k;
                    stadiumObjectCollision.hazardData[*idx]++;
                    obj = &stadiumObjectCollision.objects[k];
                    off++;
                    ctrl = *(PalaceObjControl*)obj;
                    CTRLSetTranslation(&ctrl.ctrl, TornadoPlacementConfig[obj->_9C].restPos.x,
                                       -(TornadoPlacementConfig[obj->_9C].restPos.y - 0.5),
                                       TornadoPlacementConfig[obj->_9C].restPos.z);
                    CTRLBuildMatrix(&ctrl.ctrl, m);
                    transformVectorsUpdateBoundingBox(m, (StadiumMeshData*)obj->triangles);
                    CTRLSetTranslation(&ctrl.ctrl, TornadoPlacementConfig[obj->_9C].restPos.x,
                                       -(0.5 + TornadoPlacementConfig[obj->_9C].restPos.y),
                                       TornadoPlacementConfig[obj->_9C].restPos.z);
                    CTRLBuildMatrix(&ctrl.ctrl, m);
                    transformVectorsUpdateBoundingBox(m, (StadiumMeshData*)obj->triangles);
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

// .text:0x000D62F0 size:0x224 mapped:0x80715384
void fn_3_D62F0(s32* idx) {
    PalaceObjControl ctrl;
    Mtx m;
    int off;
    int i;
    StadiumObject* obj;
    int k;

    for (i = 0; i < lbl_3_bss_A02D; i++) {
        off = (u16)(stadiumObjectCollision.vertexOffsets[*idx - 1] + stadiumObjectCollision.hazardData[*idx - 1]);
        stadiumObjectCollision.vertexOffsets[*idx] = off;
        k = lbl_3_bss_A02C + i;
        ((s32*)stadiumObjectCollision.vertexData)[off] = k;
        stadiumObjectCollision.hazardData[*idx]++;
        obj = &stadiumObjectCollision.objects[k];
        ctrl = *(PalaceObjControl*)obj;
        CTRLBuildMatrix(&ctrl.ctrl, m);
        transformVectorsUpdateBoundingBox(m, (StadiumMeshData*)obj->triangles);
        CTRLSetTranslation(&ctrl.ctrl, 14.25 + chompPlacementConfig[obj->_9C].position.x,
                           -(9.375f + chompPlacementConfig[obj->_9C].position.y),
                           14.25 + chompPlacementConfig[obj->_9C].position.z);
        CTRLBuildMatrix(&ctrl.ctrl, m);
        transformVectorsUpdateBoundingBox(m, (StadiumMeshData*)obj->triangles);
        CTRLSetTranslation(&ctrl.ctrl, chompPlacementConfig[obj->_9C].position.x - 14.25,
                           -(9.375f + chompPlacementConfig[obj->_9C].position.y),
                           chompPlacementConfig[obj->_9C].position.z - 14.25);
        CTRLBuildMatrix(&ctrl.ctrl, m);
        transformVectorsUpdateBoundingBox(m, (StadiumMeshData*)obj->triangles);
        if ((u32)stadiumObjectCollision.hazardData[*idx] != 0) {
            storeBoundingBoxCoordinates(&((Vec*)stadiumObjectCollision.vertexDataArray)[*idx * 2],
                                        &((Vec*)stadiumObjectCollision.vertexDataArray)[*idx * 2 + 1]);
            (*idx)++;
        }
    }
}

// .text:0x000D6514 size:0x2B8 mapped:0x807155A8
void fn_3_D6514(void) {
    s32 idx;
    int size;
    u8* base;

    size = stadiumObjectCollision.objectCount * 2 + stadiumObjectCollision.objectCount * 4 +
           stadiumObjectCollision.objectCount * 0x18 + stadiumObjectCollision.objectCount * 4;
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
    fn_3_D62F0(&idx);
    fn_3_D5C8C(&idx);
    stadiumObjectCollision.boundingBoxCount = idx;
}

// .text:0x000D67CC size:0x2244 mapped:0x80715860
void loadWarioPalace(void** files) {
    u8** animTable = (u8**)(hugeAnimStruct + 0x6C);
    PalaceChompPlacement* chompCfg = chompPlacementConfig;
    PalaceChompPlacement* spinCfg;
    PalaceTornadoPlacement* tornadoCfg;
    PalaceSandPlacement* sandCfg;
    PalaceSandStarPlacement* starCfg;
    PalaceSandStarPlacement* sunCfg;
    PalaceActEffect* effects;
    StadiumObject* o;
    StadiumObject* chompObj;
    u32* ids;
    u8 done = FALSE;
    u8 spinDone;
    u8 sandDone;
    u8 starDone;
    u8 sunDone;
    u8* base;
    u32 chompCount;
    u32 chompAnims;
    u32 tornadoCount;
    u32 sandCount;
    u32 starCount;
    u32 sunCount;
    u32 propCount;
    u32 idx;
    u32 chompBodyBase;
    u32 linkAnim;
    u32 tornadoBase;
    u32 ringAnim;
    u32 hazeAnim;
    u32 sandBase;
    u32 starBase;
    u32 sunBase;
    u32 usedAnims;
    u32 n;
    u32 i;
    u32 j;
    u32 k;
    u32 shadowBit;
    Mtx m;
    Vec v;
    PalaceHazeEmitter* emitter;

    stadiumObjectCollision.preUpdateFunc = updateGameStatusFlag;
    n = 0;
    ids = stadiumObjectCollision._34 = _OSAllocFromHeap(4, 0x68);
    processStadiumFileObjects((u8*)&lbl_3_data_182C0 + 0x604, 0x1A, (u8*)files, ids);
    lbl_3_bss_ADD0[0] = (u32)files[0];
    lbl_3_data_182C0 = -1;
    activeStadiumEmitterID = -1;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        palaceMinigameObjectLoading(files, ids);
        return;
    }

    for (chompCount = 0; chompCount < 2; chompCount++) {
        if (chompCfg[chompCount].usedFlag == 0xD) {
            break;
        }
    }
    tornadoCfg = TornadoPlacementConfig;
    chompAnims = chompCount * 3;
    propCount = chompCount + chompAnims;
    propCount += 1;
    for (tornadoCount = 0; tornadoCount < 5; tornadoCount++) {
        if (tornadoCfg[tornadoCount].usedFlag == 0xD) {
            break;
        }
    }
    propCount += tornadoCount;
    propCount += 3;
    sandCfg = lbl_3_data_185D0;
    for (sandCount = 0; sandCount < 10; sandCount++) {
        if (sandCfg[sandCount].kind == 0xD) {
            break;
        }
    }
    propCount += sandCount;
    starCfg = sandStarPlacementConfig.entries;
    for (starCount = 0; starCount < 10; starCount++) {
        if (starCfg[starCount].usedFlag == 0xD) {
            break;
        }
    }
    propCount += starCount;
    sunCfg = &sandStarPlacementConfig.entries[11];
    for (sunCount = 0; sunCount < 10; sunCount++) {
        if (sunCfg[sunCount].usedFlag == 0xD) {
            break;
        }
    }
    propCount += sunCount;
    stadiumObjectCollision.propCount = propCount;
    *animTable = ActorObjectInitTable(propCount);

    idx = 0;
    for (i = 0; i < chompCount; i++) {
        animateBallRelated(*animTable, idx, idx, files[ids[i + 1]], 0, 0);
        idx++;
    }
    chompBodyBase = idx;
    for (i = 0; i < chompAnims; i++) {
        animateBallRelated(*animTable, idx, idx, files[ids[3]], 0, 0);
        actorSetAnimBank((ACTActor*)(*animTable + idx * 0x90 + 0x34), (u32)files[ids[3] + 2]);
        idx++;
    }
    linkAnim = idx;
    animateBallRelated(*animTable, idx, idx, files[ids[4]], 0, 0);
    idx++;
    tornadoBase = idx;
    for (i = 0; i < tornadoCount; i++) {
        animateBallRelated(*animTable, idx, idx, files[ids[5]], 0, 0);
        idx++;
    }
    ringAnim = idx;
    animateBallRelated(*animTable, idx, idx, files[ids[6]], 0, 0);
    idx++;
    hazeAnim = idx;
    animateBallRelated(*animTable, idx, idx, files[ids[7]], 0, 0);
    idx++;
    sandBase = idx;
    for (i = 0; i < sandCount; i++) {
        animateBallRelated(*animTable, idx, idx, files[ids[8]], 0, 0);
        actorSetAnimBank((ACTActor*)(*animTable + idx * 0x90 + 0x34), (u32)files[ids[8] + 2]);
        idx++;
    }
    starBase = idx;
    for (i = 0; i < starCount; i++) {
        animateBallRelated(*animTable, idx, idx, files[ids[i + 9]], 0, 0);
        idx++;
    }
    sunBase = idx;
    for (i = 0; i < sunCount; i++) {
        animateBallRelated(*animTable, idx, idx, files[ids[12]], 0, 0);
        idx++;
    }
    for (i = 0; i < propCount; i++) {
        fn_800BD548(*animTable + i * 0x90 + 0x34, 4, stadiumObjectCollision.lights[0],
                    stadiumObjectCollision.lights[1], stadiumObjectCollision.lights[2],
                    stadiumObjectCollision.lights[3]);
    }

    if (files[ids[15]] != NULL && files[ids[16]] != NULL && files[ids[17]] != NULL) {
        adjustInternalPointers(files[ids[15]]);
        adjustInternalPointers(files[ids[16]]);
        for (i = 0; i < chompCount; i++) {
            ACTActorRelated(files[ids[i + 15]], *animTable + i * 0x90 + 0x34);
        }
        effects = (PalaceActEffect*)&lbl_3_bss_A034[460];
        for (i = 0; i < chompCount; i++) {
            if (i == 0) {
                effects[0].file = (u32)files[ids[17]];
                actRelated(files[ids[15]], &effects[0]);
            } else {
                memcpy(&effects[i], &effects[i - 1], sizeof(PalaceActEffect));
                effects[i].srcFile = (u32)files[ids[i + 15]];
            }
            actorRelated(&effects[i], 0, 1);
        }
    }
    if (files[ids[18]] != NULL && files[ids[19]] != NULL) {
        adjustInternalPointers(files[ids[18]]);
        for (i = 0; i < sunCount; i++) {
            ACTActorRelated(files[ids[i + 18]], *animTable + (sunBase + i) * 0x90 + 0x34);
        }
        effects = (PalaceActEffect*)&lbl_3_bss_A034[230];
        for (i = 0; i < sunCount; i++) {
            if (i == 0) {
                effects[0].file = (u32)files[ids[19]];
                actRelated(files[ids[18]], &effects[0]);
            } else {
                memcpy(&effects[i], &effects[i - 1], sizeof(PalaceActEffect));
                effects[i].srcFile = (u32)files[ids[i + 18]];
            }
            actorRelated(&effects[i], 0, 0);
        }
    }
    if (files[ids[20]] != NULL && files[ids[21]] != NULL && files[ids[22]] != NULL && files[ids[23]] != NULL) {
        adjustInternalPointers(files[ids[20]]);
        adjustInternalPointers(files[ids[21]]);
        adjustInternalPointers(files[ids[22]]);
        for (i = 0; i < starCount; i++) {
            ACTActorRelated(files[ids[i + 20]], *animTable + (starBase + i) * 0x90 + 0x34);
        }
        effects = (PalaceActEffect*)&lbl_3_bss_A034[0];
        for (i = 0; i < starCount; i++) {
            if (i == 0) {
                effects[0].file = (u32)files[ids[23]];
                actRelated(files[ids[20]], &effects[0]);
            } else {
                memcpy(&effects[i], &effects[i - 1], sizeof(PalaceActEffect));
                effects[i].srcFile = (u32)files[ids[i + 20]];
            }
            actorRelated(&effects[i], 0, 0);
        }
    }
    fn_80035750(files[ids[25]], files[ids[24]], 5);
    lbl_3_bss_A8A4 = (PalaceGfxScene*)insertGraphicDrawingFunction(fn_3_CE954, 2);
    addGraphicsElementToScene((DrawingSceneStruct*)lbl_3_bss_A8A4, lbl_3_data_10D3C);
    fn_3_D511C();

    stadiumObjectCollision.objectCount = 0x43;
    o = _OSAllocFromHeap(0x20, 0x3CB8);
    stadiumObjectCollision.objects = o;
    memset(o, 0, 0x3CB8);
    o = _OSAllocFromHeap(0x20, 0x3CB8);
    stadiumObjectCollision.objectsRelated = o;
    memset(o, 0, 0x3CB8);
    o = stadiumObjectCollision.objects;
    usedAnims = 0;
    i = 0;
    lbl_3_bss_A02C = 0;
    do {
        if (chompCfg->usedFlag == 0xD) {
            done = TRUE;
        }
        if (done) {
            for (k = i; k < 2; k++) {
                chompPlacementConfig[k].usedFlag = 0xD;
            }
            break;
        }
        o->_9D[0] = chompCfg->usedFlag;
        if (chompCfg->sideSelector == 0) {
            ((PalaceChompObj*)o)->homePos = (Vec*)&lbl_3_rodata_24DC;
        } else {
            ((PalaceChompObj*)o)->homePos = (Vec*)&lbl_3_rodata_24D0;
        }
        o->model = (StadiumModel*)(*animTable + i * 0x90 + 0x34);
        o->triangles = files[ids[13]];
        o->callback = (void (*)(void))palaceChainChompControl;
        o->func = (int (*)(int, int, void*))fn_3_D196C;
        o->_90b1 = 1;
        o->fadeByDepth = 1;
        o->_9C = i;
        o->alpha = 0xFF;
        o->preDraw = fn_3_D1AC4;
        o->effect = (StadiumObjectEffect*)&((PalaceActEffect*)&lbl_3_bss_A034[460])[i];
        o->animActive = 0;
        o->animIndex = -1;
        o->drawPass = 1;
        if (chompCfg->sideSelector == 0) {
            o->links = (StadiumLink*)((u8*)lbl_3_bss_A8D0 + 0x300);
        } else {
            o->links = (StadiumLink*)((u8*)lbl_3_bss_A8D0 + 0x100);
        }
        someCTRLButNotCalled2((PalaceChompObj*)o);
        i++;
        n++;
        usedAnims++;
        lbl_3_bss_A02D++;
        chompCfg++;
        o++;
    } while (i < 2);

    spinDone = FALSE;
    i = 0;
    do {
        spinCfg = &chompPlacementConfig[i / 3];
        if (spinCfg->usedFlag == 0xD) {
            spinDone = TRUE;
        }
        if (spinDone) {
            break;
        }
        chompObj = &stadiumObjectCollision.objects[i / 3];
        o->_9D[0] = 1;
        o->model = (StadiumModel*)(*animTable + (chompBodyBase + i) * 0x90 + 0x34);
        o->triangles = NULL;
        o->callback = (void (*)(void))fn_3_D1848;
        o->func = NULL;
        o->hasShadow = 0;
        o->_90b1 = 0;
        ((PalaceSpinObj*)o)->rate = ((ACTActor*)o->model)->animSpeed;
        o->fadeByDepth = 0;
        ((Control*)o)->type = 0;
        PSMTXRotRad(m, 'Y', const_pi_or_180 * -spinCfg->sleepRotation.y);
        v.x = 4.5f;
        v.y = 9.0f;
        v.z = 0.0f;
        PSMTXMultVec(m, &v, &v);
        CTRLSetTranslation((Control*)o, v.x + spinCfg->position.x, spinCfg->position.y - v.y,
                           v.z + spinCfg->position.z);
        CTRLSetScale((Control*)o, 0.75f, 0.75f, 0.75f);
        o->alpha = 0xFF;
        o->preDraw = applyTransformationToPalaceObjs;
        o->effect = NULL;
        o->animActive = 0;
        o->animIndex = -1;
        o->drawPass = 1;
        ((PalaceSpinObj*)o)->stateFlag = &chompObj->_CA;
        o->_9C = i;
        ((PalaceSpinObj*)o)->timer = i % 3 * 30;
        ((PalaceSpinObj*)o)->_AD = 0;
        n++;
        usedAnims++;
        o++;
        i++;
    } while (i < 6);

    i = 0;
    do {
        base = (u8*)lbl_3_bss_A8D0 + 0x100;
        if (i / 7 == 0) {
            base = (u8*)lbl_3_bss_A8D0 + 0x300;
        }
        o->anchorA = (StadiumLink*)(base + (i % 7) * 0x40);
        o->anchorB = (StadiumLink*)(base + (i % 7 + 1) * 0x40);
        o->_9D[0] = 2;
        o->model = (StadiumModel*)(*animTable + linkAnim * 0x90 + 0x34);
        if (linkAnim != usedAnims) {
            usedAnims++;
        }
        o->triangles = NULL;
        o->callback = (void (*)(void))maybePalaceCTRLRelated;
        o->func = NULL;
        o->hasShadow = 1;
        o->_90b1 = 0;
        o->fadeByDepth = 1;
        fn_3_D141C(o);
        PSVECAdd(&o->anchorB->pos, &o->anchorA->pos, &o->pos);
        PSVECScale(&o->pos, 0.5f, &o->pos);
        CTRLSetTranslation((Control*)o, o->pos.x, -o->pos.y, o->pos.z);
        CTRLSetScale((Control*)o, 0.75f, 0.75f, 0.75f);
        o->alpha = 0xFF;
        o->preDraw = (void (*)(StadiumObject*))fn_3_D127C;
        o->effect = NULL;
        o->animActive = 0;
        o->animIndex = -1;
        o->drawPass = 1;
        n++;
        o->_9C = i;
        o++;
        i++;
    } while (i < 14);

    lbl_3_bss_A02A = n;
    i = 0;
    do {
        if (tornadoCfg->usedFlag == 0xD) {
            done = TRUE;
        }
        if (done) {
            for (k = i; k < 6; k++) {
                TornadoPlacementConfig[i].usedFlag = 0xD;
            }
            break;
        }
        o->_9D[0] = tornadoCfg->usedFlag;
        o->_9C = i;
        o->_D2[0] = n;
        o->model = (StadiumModel*)(*animTable + (tornadoBase + i) * 0x90 + 0x34);
        o->triangles = NULL;
        o->callback = (void (*)(void))palaceNadoLogic;
        o->func = NULL;
        o->hasShadow = 1;
        shadowBit = 0;
        if (o->hasShadow && o->triangles != NULL) {
            shadowBit = 1;
        }
        o->_90b1 = shadowBit;
        CTRLGetQuat((Control*)(((PalaceModelRoot*)o->model->root)->next->ctrlBlock + 0x1C),
                    &((PalaceNadoObj*)o)->quat.x, &((PalaceNadoObj*)o)->quat.y, &((PalaceNadoObj*)o)->quat.z,
                    &((PalaceNadoObj*)o)->quat.w);
        fn_3_D1110((PalaceNadoObj*)o);
        o->fadeByDepth = 1;
        o->alpha = 0xFF;
        o->effect = NULL;
        o->preDraw = (void (*)(StadiumObject*))fn_3_D0528;
        o->animActive = 0;
        o->animIndex = -1;
        o->drawPass = 1;
        o->shadowEnabled = 1;
        o++;
        n++;
        lbl_3_bss_A02B++;
        tornadoCfg++;
        i++;
    } while (i < 5);

    lbl_3_bss_A028 = n;
    for (i = 0; i < lbl_3_bss_A02B; i++) {
        o->_9D[0] = 4;
        o->_9C = i;
        ((PalaceNadoRingObj*)o)->source = &stadiumObjectCollision.objects[lbl_3_bss_A02A + i];
        ((PalaceIdObj*)o)->id = n;
        ((PalaceNadoRingObj*)o)->radius = 1.0f;
        o->model = (StadiumModel*)(*animTable + ringAnim * 0x90 + 0x34);
        o->triangles = NULL;
        o->callback = (void (*)(void))fn_3_D0284;
        o->func = NULL;
        o->hasShadow = 1;
        shadowBit = 0;
        if (o->hasShadow && o->triangles != NULL) {
            shadowBit = 1;
        }
        o->_90b1 = shadowBit;
        ((Control*)o)->type = 0;
        CTRLSetTranslation((Control*)o, ((PalaceNadoRingObj*)o)->source->pos.x, 0.0f,
                           ((PalaceNadoRingObj*)o)->source->pos.z);
        *(Vec*)&((PalaceNadoRingObj*)o)->baseX = ((PalaceNadoRingObj*)o)->source->pos;
        *(f32*)&((PalaceNadoRingObj*)o)->_A8 = 0.0f;
        o->fadeByDepth = ((PalaceNadoRingObj*)o)->source->fadeByDepth;
        o->alpha = 0xFF;
        o->effect = NULL;
        o->preDraw = (void (*)(StadiumObject*))fn_3_D0280;
        o->animActive = 0;
        o->animIndex = -1;
        o->drawPass = ((PalaceNadoRingObj*)o)->source->drawPass;
        o++;
        n++;
        lbl_3_bss_A029++;
    }

    lbl_3_bss_A026 = n;
    for (i = 0; i < lbl_3_bss_A02B; i++) {
        o->_9D[0] = 5;
        o->_9C = i;
        ((PalaceLinkedObj*)o)->nado = &stadiumObjectCollision.objects[lbl_3_bss_A02A + i];
        ((PalaceLinkedObj*)o)->other = (PalaceIdObj*)&stadiumObjectCollision.objects[lbl_3_bss_A028 + i];
        ((PalaceLinkedObj*)o)->animPhase = n;
        o->model = (StadiumModel*)(*animTable + hazeAnim * 0x90 + 0x34);
        o->triangles = NULL;
        o->callback = (void (*)(void))fn_3_D00D0;
        o->func = NULL;
        o->hasShadow = 1;
        o->_90b1 = 0;
        ((Control*)o)->type = 0;
        CTRLSetTranslation((Control*)o, ((PalaceLinkedObj*)o)->nado->pos.x, 0.0f,
                           ((PalaceLinkedObj*)o)->nado->pos.z);
        o->fadeByDepth = ((PalaceLinkedObj*)o)->nado->fadeByDepth;
        o->alpha = 0xFF;
        o->effect = NULL;
        o->preDraw = (void (*)(StadiumObject*))fn_3_D00CC;
        o->animActive = 0;
        o->animIndex = -1;
        o->drawPass = ((PalaceLinkedObj*)o)->nado->fadeByDepth;
        o++;
        n++;
        lbl_3_bss_A027++;
    }

    sandDone = FALSE;
    j = 0;
    k = 0;
    do {
        if (sandCfg->kind == 0xD) {
            sandDone = TRUE;
        }
        if (sandDone) {
            for (i = j; i < 11; i++) {
                lbl_3_data_185D0[i].kind = 0xD;
            }
            break;
        }
        o->_9D[0] = sandCfg->kind;
        *(s32*)&o->pos.x = k;
        o->model = (StadiumModel*)(*animTable + (sandBase + j) * 0x90 + 0x34);
        o->triangles = NULL;
        o->callback = (void (*)(void))fn_3_CFA8C;
        o->func = NULL;
        o->hasShadow = 1;
        shadowBit = 0;
        if (o->hasShadow && o->triangles != NULL) {
            shadowBit = 1;
        }
        o->_90b1 = shadowBit;
        ((Control*)o)->type = 0;
        CTRLSetScale((Control*)o, sandCfg->scale.x, sandCfg->scale.y, sandCfg->scale.z);
        CTRLSetTranslation((Control*)o, sandCfg->pos.x, sandCfg->pos.y, sandCfg->pos.z);
        CTRLSetRotation((Control*)o, 0.0f, -sandCfg->rotY, 0.0f);
        o->fadeByDepth = 0;
        j++;
        o->alpha = 0xFF;
        n++;
        sandCfg++;
        o->effect = NULL;
        k += 30;
        o->preDraw = (void (*)(StadiumObject*))fn_3_CFA88;
        o->animActive = 0;
        o->animIndex = -1;
        o->drawPass = 1;
        o++;
    } while (j < 10);

    lbl_3_bss_A022 = n;
    starDone = FALSE;
    j = 0;
    do {
        if (starCfg->usedFlag == 0xD) {
            starDone = TRUE;
        }
        if (starDone) {
            for (k = j; k < 11; k++) {
                memset(&sandStarPlacementConfig.entries[k], 0, sizeof(PalaceSandStarPlacement));
                sandStarPlacementConfig.entries[k].usedFlag = 0xD;
            }
            break;
        }
        o->_9D[0] = j + 8;
        o->_9C = j;
        ((PalaceStarObj*)o)->awarded = 0;
        ((PalaceStarObj*)o)->effect = NULL;
        o->model = (StadiumModel*)(*animTable + (starBase + j) * 0x90 + 0x34);
        o->triangles = files[ids[14]];
        o->callback = (void (*)(void))warioPalaceSandStarRelated;
        o->func = (int (*)(int, int, void*))starHitAnimation;
        o->hasShadow = 1;
        shadowBit = 0;
        if (o->hasShadow && o->triangles != NULL) {
            shadowBit = 1;
        }
        o->_90b1 = shadowBit;
        ((Control*)o)->type = 0;
        CTRLSetTranslation((Control*)o, starCfg->pos.x, -starCfg->pos.y, starCfg->pos.z);
        o->fadeByDepth = 1;
        j++;
        o->alpha = 0xFF;
        starCfg++;
        n++;
        o->effect = NULL;
        o->preDraw = (void (*)(StadiumObject*))fn_3_CF92C;
        o->animActive = 0;
        o->animIndex = -1;
        o->drawPass = 1;
        o++;
        lbl_3_bss_A023++;
    } while (j < 10);

    effects = (PalaceActEffect*)&lbl_3_bss_A034[230];
    sunDone = FALSE;
    j = 0;
    do {
        if (sunCfg->usedFlag == 0xD) {
            sunDone = TRUE;
        }
        if (sunDone) {
            for (i = j; i < 11; i++) {
                lbl_3_data_185D0[i].kind = 0xD;
            }
            break;
        }
        o->_9D[0] = sunCfg->usedFlag;
        o->model = (StadiumModel*)(*animTable + (sunBase + j) * 0x90 + 0x34);
        o->triangles = NULL;
        o->callback = (void (*)(void))fn_3_CED3C;
        o->func = NULL;
        o->hasShadow = 1;
        shadowBit = 0;
        if (o->hasShadow && o->triangles != NULL) {
            shadowBit = 1;
        }
        o->_90b1 = shadowBit;
        ((Control*)o)->type = 0;
        CTRLSetTranslation((Control*)o, sunCfg->pos.x, sunCfg->pos.y, sunCfg->pos.z);
        o->fadeByDepth = 1;
        j++;
        o->alpha = 0xFF;
        sunCfg++;
        o->effect = (StadiumObjectEffect*)effects;
        effects++;
        o->preDraw = (void (*)(StadiumObject*))fn_3_CED38;
        o->animActive = 0;
        o->animIndex = -1;
        o->drawPass = 1;
        o->customZMode = 1;
        o->zCompare = 1;
        o->zAlways = 1;
        o->zUpdate = 0;
        o++;
    } while (j < 10);

    stadiumObjectCollision.vertexDataArray = NULL;
    fn_3_D6514();
    for (i = 0; i < 4; i++) {
        emitter = allocParticleEffect((void*)fn_3_CDFA4, 0x80, 0, 0x15, 1, 0);
        if (emitter != NULL) {
            palaceHazeTextureMaybe(emitter, i);
        }
    }
    fn_3_B97C8(fn_3_CD958);
}

