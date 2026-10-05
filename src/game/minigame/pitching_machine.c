#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_pitchingMachine
#define g_Minigame g_Minigame_shared
#include "game/minigame/pitching_machine.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/minigame/star_dash.h"
#include "game/minigame/piranha_panic.h"
#include "game/math/game_math.h"
#include "game/sound/m_sound.h"
#include "Unknown/File_0x800b4908.h"
#include "game/match_setup/match_flow.h"
#include "game/fielding/fielder.h"
#include "Unknown/File_0x8001d0d0.h"
#include "Unknown/File_0x8001d110.h"
#include "Unknown/File_0x8005268c.h"
#include "Unknown/File_0x80052734.h"
#include "Unknown/File_0x80034cec.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x800b0a14.h"
#include "text/text_channel.h"
#include "C3/control.h"
#include "Unknown/File_0x800bdc88.h"
#include "Unknown/File_0x800bd3ec.h"
#include "Unknown/File_0x800bdd74.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/File_0x80025c58.h"
#include "Unknown/File_0x80034220.h"
#include "Unknown/File_0x8003452c.h"
#include "Unknown/File_0x800348c8.h"
#include "game/stadium/stadium_framework.h"
#include "Dolphin/gx.h"
#include "Dolphin/mtx.h"
#include "C3/actor.h"
#include "C3/skinning.h"
#include "C3/anim.h"
#include "Dolphin/vec.h"
#include "Dolphin/os.h"
#include "Dolphin/stl.h"
#include "stl/stdlib.h"
#include "stl/math.h"
#undef g_Minigame

extern f32 lbl_3_data_21A64[9];
extern VecXYZ lbl_3_data_21A48;
extern s16 lbl_3_data_21A04[8];
extern VecXYZ lbl_3_data_21B94[4];
extern VecXYZ lbl_3_data_21BC4[][4];
extern UIRecordDescriptor lbl_3_data_69D0[];
extern u8 animRelated[0x124];


static u32 MinigameCommonFiles_game[12] = { 0x40B, 0x40001640, 0x08EB4800, 0xC38, 0x40B, 0x400B2D00,
                                            0x08EB5800, 0x6A948, 0, 0x686, 0x08F20800, 0x688 };
static f32 lbl_3_data_22620[3] = { 0.0f, -0.15f, 18.5f };
static f32 lbl_3_data_2262C = 0.45f;
static u8 lbl_3_data_22630[4] = { 0, 1, 3, 2 };
static u8 lbl_3_data_22634[4] = { 15, 15, 15, 15 };
static u8 lbl_3_data_22638[4] = { 2, 0, 3, 1 };
static u8 lbl_3_data_2263C[2] = { 0, 1 };
static u8 lbl_3_data_2263E = 2;
static u8 lbl_3_data_2263F = 6;
static f32 lbl_3_data_22640[4] = { 0.75f, 0.05f, 3.0f, 0.02f };
static f32 lbl_3_data_22650[3] = { 5.0f, 5.0f, 10.0f };
static u8 lbl_3_data_2265C[4] = { 1, 0, 2, 3 };
static f32 lbl_3_data_22660[2] = { 2.0f, 8.0f };
static f32 lbl_3_data_22668 = 1.0f;
static s32 lbl_3_data_2266C = 60;
static u8 lbl_3_data_22670[8] = { 2, 0, 3, 4, 1, 0, 0, 0 };
static f32 lbl_3_data_22678[4] = { 2.0f, 2.5f, 1.0f, 1.0f };
static f32 lbl_3_data_22688[3] = { 0.5f, 0.0f, -0.5f };
static f32 lbl_3_data_22694[6] = { 0.5f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f };
static s16 lbl_3_data_226AC[6] = { 0, 0, 20, 10, 0, 0 };
static u8 lbl_3_data_226B8[4] = { 15, 80, 0, 0 };
static u8 lbl_3_data_226BC[8] = { 3, 1, 4, 2, 0, 0, 0, 0 };
static f32 lbl_3_data_226C4[4] = { 1.5f, 0.7f, 1.0f, 0.5f };
static f32 lbl_3_data_226D4[2] = { 1.0f, 30.0f };
static f32 lbl_3_data_226DC = 4.0f;

typedef struct {
    /*0x00*/ u16 frame;
    /*0x02*/ u8 _02[0x1E];
} PMMeshD; // size: 0x20

typedef struct {
    /*0x00*/ u8 _00[0xC];
    /*0x0C*/ PMMeshD* d;
} PMMeshC;

typedef struct {
    /*0x00*/ u8 _00[0x8];
    /*0x08*/ PMMeshC* c;
} PMMeshB;

typedef struct {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ PMMeshB* b;
} PMMeshA;

typedef struct {
    /*0x00*/ u8 _00[0x6];
    /*0x06*/ u16 count;
    /*0x08*/ u8 _08[0x10];
    /*0x18*/ PMMeshA** parts;
    /*0x1C*/ u8 _1C[0x98 - 0x1C];
    /*0x98*/ u8 flags;
} PMModel;

/* An ActorObjectEntry (File_0x800bdd74.h) of hugeAnimStruct's model table, viewed
 * with its actor typed as the mesh chain this file walks. */
typedef struct {
    /*0x00*/ PMModel* model;
    /*0x04*/ u8 _04[0x90 - 0x4];
} PMModelObj; // size: 0x90

/* A 12-byte record in the table at hugeAnimStruct+0x2DA0; data is the model
 * source handed to animateBallRelated. */
typedef struct {
    /*0x0*/ void* data;
    /*0x4*/ u8 _4[8];
} PMModelSource; // size: 0xC

typedef struct {
    /*0x0000*/ u8 _0000[0x68];
    /*0x0068*/ u8* modelTable;
    /*0x006C*/ u8 _006C[0xAC - 0x6C];
    /*0x00AC*/ void* _AC[4];
    /*0x00BC*/ u8 _00BC[0x2D94 - 0xBC];
    /*0x2D94*/ PMEffect* effects;
    /*0x2D98*/ u8 _2D98[0x2DA0 - 0x2D98];
    /*0x2DA0*/ PMModelSource sources[27];
    /*0x2EE4*/ u8 _2EE4[0x3078 - 0x2EE4];
    /*0x3078*/ u16 effectCount;
    /*0x307A*/ u8 _307A[4];
    /*0x307E*/ u8 _307E;
} PMHugeAnimStruct;

extern PMHugeAnimStruct hugeAnimStruct;

#define FX(i) (hugeAnimStruct.effects[i])
#define PM_MODEL(i) ((PMModelObj*)(hugeAnimStruct.modelTable + (i) * 0x90 + 0x34))
#define PM_ACTORS ((ActorObjectTable*)hugeAnimStruct.modelTable)
#define PM_ENTRY(i) ((ActorObjectEntry*)(hugeAnimStruct.modelTable + (i) * 0x90 + 0x34))
#define PM_MODEL_AT(i) (&((PMModelObj*)(hugeAnimStruct.modelTable + 0x34))[i])

static inline Actor* pmGetActor(int idx) {
    ActorObjectEntry* e = ((ActorObjectTable*)hugeAnimStruct.modelTable)->entries;

    e += idx;
    return e->actor;
}

typedef union _PMMinigame {
    MiniGameStruct;
    SDState sd;
    PPState pp;
} PMMinigame;

extern PMMinigame g_Minigame;

#define SD g_Minigame.sd
#define PP g_Minigame.pp

extern void fn_80033B58(void* tex, int sub, int a, int b);

static inline void pmSetupQuadState(void) {
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_DISABLE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_DISABLE, GX_TEVPREV);
}

static inline void pmSetupQuadCamera(int sub) {
    GXLoadPosMtxImm(fn_80052768_getCamera(returnsCurrentMode())->view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetProjection(fn_80052768_getCamera(returnsCurrentMode())->proj, GX_PERSPECTIVE);
    fn_80033B58(*(void**)(animRelated + 0x6C), sub, 0, 0);
}

extern s16 lbl_3_data_21E68[26];
extern s16 lbl_3_data_217A4[];
extern VecXYZ lbl_3_data_21380;
extern s16 lbl_3_data_21654[];
extern VecXYZ lbl_3_data_21520[];
extern f32 lbl_3_data_2188C[];
extern u8 lbl_80366158[0x30];
#define PauseSimulation lbl_80366158[0x28]

extern void fn_3_14DC80(s8 slot);
extern void fn_3_14CB28(s8 slot);
extern void fn_3_151710(void* modelObj, VecXYZ* pos);
extern void fn_3_15521C(s16 idx, VecXYZ* pos, VecXYZ* rot);
extern void fn_3_14B9A0(int frames, f32* pos);
extern void barrelBatterRel(VecXYZ* pos);
extern void fn_80062C24(VecXYZ* pos);

/* The animation state that animRelated+0x10 hands to fn_80024DB0/fn_80024FA4
 * (same layout as PerfectPitchState in perfect_pitch_gfx.c). */
typedef struct {
    /*0x00*/ f32 time;
    /*0x04*/ f32 frame;
    /*0x08*/ u8 _08[0xC - 0x8];
    /*0x0C*/ u16 _0C;
    /*0x0E*/ s16 started;
    /*0x10*/ u8 _10;
    /*0x11*/ u8 flag : 1;
    /*0x11*/ u8 _11 : 7;
} PMAnimState; // size: 0x14

typedef struct {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ PMAnimState state;
    /*0x24*/ u8 _24[0x30 - 0x24];
    /*0x30*/ void* stateHandle;
} PMAnimRelated;

#define ANIM_RELATED ((PMAnimRelated*)animRelated)

#define ANIM_WORD(off) (*(s32*)(animRelated + (off)))
#define ANIM_PTR(off) (*(void**)(animRelated + (off)))

#define PM_WALL_SIZE 0x2C
#define PM_WALL(i) ((MaybeWallBallStruct*)((u8*)&g_Minigame + 0x72C + (i) * PM_WALL_SIZE))

extern void fn_3_14C348(MaybeWallBallStruct* wall, u8 flag);
extern void fn_3_1666B0(MaybeWallBallStruct* wall);

static f32 lbl_3_bss_B6BC;


extern void fn_80035B50(int arg);
extern void fn_3_5E60(void);
extern void fn_80018B38(void);
extern void fn_3_909B0(void);
extern void fn_3_9081C(void);
extern void fn_80011B64(int player);
extern void fn_800B993C(void);
extern void cleanupCharacters(void);

static inline void pmDisableWallBallEffects(void) {
    FX(0xFB).visible = FALSE;
    FX(0xE6).visible = FALSE;
    FX(0xED).visible = FALSE;
    FX(0xF4).visible = FALSE;
    FX(0xFC).visible = FALSE;
    FX(0x103).visible = FALSE;
    FX(0x10A).visible = FALSE;
    FX(0xE7).visible = FALSE;
    FX(0xEE).visible = FALSE;
    FX(0xF5).visible = FALSE;
    FX(0xFD).visible = FALSE;
    FX(0x104).visible = FALSE;
    FX(0x10B).visible = FALSE;
    FX(0xE8).visible = FALSE;
    FX(0xEF).visible = FALSE;
    FX(0xF6).visible = FALSE;
    FX(0xFE).visible = FALSE;
    FX(0x105).visible = FALSE;
    FX(0x10C).visible = FALSE;
    FX(0xE9).visible = FALSE;
    FX(0xF0).visible = FALSE;
    FX(0xF7).visible = FALSE;
    FX(0xFF).visible = FALSE;
    FX(0x106).visible = FALSE;
    FX(0x10D).visible = FALSE;
    FX(0xEA).visible = FALSE;
    FX(0xF1).visible = FALSE;
    FX(0xF8).visible = FALSE;
    FX(0x100).visible = FALSE;
    FX(0x107).visible = FALSE;
    FX(0x10E).visible = FALSE;
    FX(0xEB).visible = FALSE;
    FX(0xF2).visible = FALSE;
    FX(0xF9).visible = FALSE;
    FX(0x101).visible = FALSE;
    FX(0x108).visible = FALSE;
    FX(0x10F).visible = FALSE;
    FX(0xEC).visible = FALSE;
    FX(0xF3).visible = FALSE;
    FX(0xFA).visible = FALSE;
    FX(0x102).visible = FALSE;
    FX(0x109).visible = FALSE;
    FX(0x110).visible = FALSE;
}


// .text:0x0011D2C8 size:0xE4 mapped:0x8075C35C
void fn_3_11D2C8(int asset, int start, int count, int a, int b) {
    int i;

    for (i = start; i < start + count; i++) {
        animateBallRelated(hugeAnimStruct.modelTable, i, i, hugeAnimStruct.sources[asset].data, a, b);
        fn_800BD548(&PM_ACTORS->entries[i], 4, hugeAnimStruct._AC[0], hugeAnimStruct._AC[1], hugeAnimStruct._AC[2],
                    hugeAnimStruct._AC[3]);
        CTRLSetTranslation(&PM_ACTORS->entries[i].control, 0.0f, 0.0f, 0.0f);
        CTRLSetRotation(&PM_ACTORS->entries[i].control, 0.0f, 0.0f, 0.0f);
    }
}

// .text:0x0011D1B0 size:0x118 mapped:0x8075C244
void fn_3_11D1B0(void) {
    int i;

    switch (g_Minigame.GameMode_MiniGame) {
    case MINI_GAME_ID_BOBOMB_DERBY:
        fn_3_11CD00();
        break;
    case MINI_GAME_ID_WALLBALL:
        fn_3_11C5F8();
        break;
    case MINI_GAME_ID_BARREL_BATTER:
        fn_3_11C2CC();
        break;
    case MINI_GAME_ID_CHAINCHOMP_SPRINT:
        fn_3_11C02C();
        break;
    case MINI_GAME_ID_STAR_DASH:
        fn_3_11BBA4();
        break;
    case MINI_GAME_ID_PIRANHA_PANIC:
        fn_3_11B75C();
        break;
    }
    for (i = 0; i < hugeAnimStruct.effectCount; i++) {
        FX(i).pos.x = 0.0f;
        FX(i).pos.y = 0.0f;
        FX(i).pos.z = 0.0f;
        FX(i).rot.x = 0.0f;
        FX(i).rot.y = 0.0f;
        FX(i).rot.z = 0.0f;
        FX(i).visible = FALSE;
        FX(i).update = NULL;
    }
}

// .text:0x0011CF84 size:0x22C mapped:0x8075C018
void fn_3_11CF84(void) {
    int i;

    if ((g_Minigame._1A3C == 0 || g_Minigame._1E01[0x29] >= 6) && g_Minigame._1A38 == 0) {
        for (i = 0; i < 4; i++) {
            fn_80011B64(i);
        }
    }
    for (i = hugeAnimStruct.effectCount - 1; i >= 0; i--) {
        hugeAnimStruct.modelTable[i * 0x90 + 0xA0] = 0;
    }
    for (i = hugeAnimStruct.effectCount - 1; i >= 0; i--) {
        fn_800B4CDC(PM_MODEL(i)->model);
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        for (i = hugeAnimStruct.effectCount - 1; i >= 0; i--) {
            fn_800B4278(PM_MODEL(i)->model);
        }
        fn_800ACFB0(hugeAnimStruct.modelTable);
        fn_800ACFB0(hugeAnimStruct.effects);
    }
    fn_800B993C();
    cleanupCharacters();
    if (g_Minigame._1A38 == 0 || g_Minigame._1A3C != 0) {
        fn_3_11CF04();
    }
}

// .text:0x0011CF04 size:0x80 mapped:0x8075BF98
void fn_3_11CF04(void) {
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD) {
        hugeAnimStruct.effectCount = 0;
    }
    hugeAnimStruct._307E = 0;
    minigamesSetSomePointers();
    minigamesGXStuff();
    minigamesSetSomePointers2();
    fn_80035B50(0xD);
    cleanupMinigameResources();
    fn_3_5E60();
    fn_80018B38();
    fn_3_909B0();
    fn_3_9081C();
    fn_80035B50(0x11);
}

// .text:0x0011CD00 size:0x204 mapped:0x8075BD94
#pragma dont_inline on
void fn_3_11CD00(void) {
    hugeAnimStruct.effectCount = 3;
    hugeAnimStruct.effects = _OSAllocFromHeap(0x20, hugeAnimStruct.effectCount * 0x28);
    hugeAnimStruct.modelTable = ActorObjectInitTable(hugeAnimStruct.effectCount);
    fn_3_11D2C8(13, 0, 1, 0, 0);
    fn_3_11D2C8(14, 1, 1, 0, 0);
    fn_3_11D2C8(15, 2, 1, 0, 0);
    ANIM_RELATED->state.frame = 0.5f;
    ACTActorRelated(*(void**)animRelated, PM_MODEL(2));
}

// .text:0x0011C5F8 size:0x708 mapped:0x8075B68C
void fn_3_11C5F8(void) {
    u16 i;

    hugeAnimStruct.effectCount = 0x111;
    hugeAnimStruct.effects = _OSAllocFromHeap(0x20, hugeAnimStruct.effectCount * 0x28);
    hugeAnimStruct.modelTable = ActorObjectInitTable(hugeAnimStruct.effectCount);
    fn_3_11D2C8(0, 0, 0x82, 0, 0);
    fn_3_11D2C8(21, 0x82, 0x64, 0, 0);
    fn_3_11D2C8(1, 0xE6, 7, 0, 0);
    fn_3_11D2C8(2, 0xED, 7, 0, 0);
    fn_3_11D2C8(3, 0xF4, 7, 0, 0);
    fn_3_11D2C8(5, 0xFB, 1, 0, 0);
    fn_3_11D2C8(6, 0xFC, 7, 0, 0);
    fn_3_11D2C8(7, 0x103, 7, 0, 0);
    fn_3_11D2C8(4, 0x10A, 7, 0, 0);
    for (i = 0; i < 7; i++) {
        fn_3_11A38C(0xFC + i, 0);
        fn_3_11A38C(0x103 + i, 2);
    }
}

// .text:0x0011C2CC size:0x32C mapped:0x8075B360
void fn_3_11C2CC(void) {
    int i;

    hugeAnimStruct.effectCount = 0x20;
    hugeAnimStruct.effects = _OSAllocFromHeap(0x20, hugeAnimStruct.effectCount * 0x28);
    hugeAnimStruct.modelTable = ActorObjectInitTable(hugeAnimStruct.effectCount);
    fn_3_11D2C8(8, 0, 0xF, 0, 0);
    fn_3_11D2C8(9, 0xF, 1, 0, 0);
    fn_3_11D2C8(10, 0x10, 0xF, 0, 0);
    fn_3_11D2C8(16, 0x1F, 1, 0, 0);
    for (i = 0; i < 15; i++) {
        fn_3_119CA8(0x10 + i);
    }
}

// .text:0x0011C02C size:0x2A0 mapped:0x8075B0C0
void fn_3_11C02C(void) {
    hugeAnimStruct.effectCount = 0xA7;
    hugeAnimStruct.effects = _OSAllocFromHeap(0x20, hugeAnimStruct.effectCount * 0x28);
    hugeAnimStruct.modelTable = ActorObjectInitTable(hugeAnimStruct.effectCount);
    fn_3_11D2C8(0, 0, 0x82, 0, 0);
    fn_3_11D2C8(11, 0x82, 0x23, 0, 0);
    fn_3_11D2C8(12, 0xA5, 1, 0, 0);
    fn_3_11D2C8(26, 0xA6, 1, 0, 0);
}

// .text:0x0011BBA4 size:0x488 mapped:0x8075AC38
void fn_3_11BBA4(void) {
    hugeAnimStruct.effectCount = 0xEE;
    hugeAnimStruct.effects = _OSAllocFromHeap(0x20, hugeAnimStruct.effectCount * 0x28);
    hugeAnimStruct.modelTable = ActorObjectInitTable(hugeAnimStruct.effectCount);
    fn_3_11D2C8(0, 0, 0x82, 0, 0);
    fn_3_11D2C8(21, 0x82, 0x64, 0, 0);
    fn_3_11D2C8(22, 0xE6, 1, 0, 0);
    fn_3_11D2C8(23, 0xE7, 1, 0, 0);
    fn_3_11D2C8(24, 0xE8, 1, 0, 0);
    fn_3_11D2C8(25, 0xE9, 4, 0, 0);
    fn_3_11D2C8(26, 0xED, 1, 0, 0);
}

// .text:0x0011B75C size:0x448 mapped:0x8075A7F0
void fn_3_11B75C(void) {
    hugeAnimStruct.effectCount = 0xF4;
    hugeAnimStruct.effects = _OSAllocFromHeap(0x20, hugeAnimStruct.effectCount * 0x28);
    hugeAnimStruct.modelTable = ActorObjectInitTable(hugeAnimStruct.effectCount);
    fn_3_11D2C8(0, 0, 0x82, 0, 0);
    fn_3_11D2C8(17, 0x82, 3, ANIM_WORD(0x78), ANIM_WORD(0x60));
    fn_3_11D2C8(18, 0x85, 0x32, 0, 0);
    fn_3_11D2C8(13, 0xB7, 0x32, 0, 0);
    fn_3_11D2C8(19, 0xE9, 7, 0, 0);
    fn_3_11D2C8(20, 0xF0, 4, 0, 0);
}
#pragma dont_inline reset

// .text:0x0011AC6C size:0xAF0 mapped:0x80759D00
void fn_3_11AC6C(void) {
    PMEffect* fx;
    int i;

    if (g_GameLogic.gameStatus >= GAME_STATUS_0x1B && g_GameLogic.gameStatus <= 0x29) {
        if (hugeAnimStruct.effectCount != 0) {
            for (i = 0; i < hugeAnimStruct.effectCount; i++) {
                fx = &hugeAnimStruct.effects[i];
                if (fx != NULL) {
                    fx->visible = FALSE;
                }
            }
        }
    } else {
        switch (g_Minigame.GameMode_MiniGame) {
        case MINI_GAME_ID_BOBOMB_DERBY:
            loadPitchingMachineModel();
            break;
        case MINI_GAME_ID_WALLBALL:
            fn_3_11A408();
            fn_3_11A210();
            break;
        case MINI_GAME_ID_BARREL_BATTER:
            fn_3_119F6C();
            fn_3_119D34();
            break;
        case MINI_GAME_ID_CHAINCHOMP_SPRINT:
            fn_3_119934();
            fn_3_119878();
            break;
        case MINI_GAME_ID_STAR_DASH:
            fn_3_118164();
            fn_3_1180A4();
            fn_3_117FC8();
            fn_3_11874C();
            fn_3_117AE4();
            fn_3_1179EC();
            fn_3_117494();
            break;
        case MINI_GAME_ID_PIRANHA_PANIC:
            fn_3_1194FC();
            fn_3_1192B8();
            fn_3_11874C();
            fn_3_11887C();
            fn_3_1183FC();
            break;
        }
    }
}

// .text:0x0011AB2C size:0x140 mapped:0x80759BC0
void loadPitchingMachineModel(void) {
    int idx = 2;
    PMEffect* fx;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        idx = 0;
    }
    fx = &hugeAnimStruct.effects[idx];
    if (fx != NULL) {
        fx->visible = TRUE;
        nonPracticePitchingMachineLogic(fx, idx);
        if (g_Pitcher.pitcherActionState >= PITCHER_ACTION_STATE_WINDUP && PauseSimulation == 0) {
            PMAnimState* state = &ANIM_RELATED->state;

            if (state != NULL) {
                ANIM_RELATED->state.flag = 1;
            }
            fn_80024DB0((u8*)state);
            fn_80024FA4((StadiumModel*)PM_MODEL(idx), ANIM_RELATED->stateHandle, (u8*)state, -1);
        } else if (g_Pitcher.pitcherActionState < PITCHER_ACTION_STATE_WINDUP) {
            if (ANIM_RELATED->state.started == FALSE) {
                ANIM_RELATED->state.time = ANIM_RELATED->state._0C = 0;
                ANIM_RELATED->state.started = TRUE;
            }
        }
    }
}

// .text:0x0011A92C size:0x200 mapped:0x807599C0
void nonPracticePitchingMachineLogic(PMEffect* fx, int idx) {
    VecXYZ v;

    fx->pos.x = lbl_3_data_22620[0];
    fx->pos.y = lbl_3_data_22620[1];
    fx->pos.z = lbl_3_data_22620[2];
    fx->rot.x = 0.0f;
    fx->rot.y = 0.0f;
    fx->rot.z = 0.0f;
    applyUniformScaleToObject(lbl_3_data_2262C, idx);
    if (g_Minigame.pauseInd == 0 && g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE) {
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY) {
            if (g_Pitcher.pitcherActionState >= PITCHER_ACTION_STATE_IN_AIR) {
                if (g_Pitcher.currentStateFrameCounter == 1 && g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_IN_AIR) {
                    lbl_3_bss_B6BC = 3.0f;
                    v.x = lbl_3_data_21380.x;
                    v.y = -lbl_3_data_21380.y;
                    v.z = lbl_3_data_21380.z - 0.5f;
                    fn_80062C24(&v);
                    callSfx(0x2D6);
                }
                fx->pos.z += lbl_3_bss_B6BC;
                lbl_3_bss_B6BC = lbl_3_bss_B6BC - 0.2 * (fx->pos.z - lbl_3_data_22620[2]);
            }
        } else if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER) {
            if (g_Pitcher.currentStateFrameCounter == 1) {
                if (g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_PRE_PITCH) {
                    fn_3_14B9A0(lbl_3_data_217A4[6] + lbl_3_data_217A4[7], lbl_3_data_22620);
                    callSfx(0x30E);
                } else if (g_Pitcher.pitcherActionState == PITCHER_ACTION_STATE_IN_AIR) {
                    v.x = lbl_3_data_21380.x;
                    v.y = 0.4f + lbl_3_data_21380.y;
                    v.z = lbl_3_data_21380.z - 0.5f;
                    barrelBatterRel(&v);
                }
            }
        }
    }
}

// .text:0x0011A408 size:0x524 mapped:0x8075949C
void fn_3_11A408(void) {
    MaybeWallBallStruct* wall;
    int i;
    int idx;
    u8 flag;
    PMEffect* fx;

    flag = 0;
    FX(0xFB).visible = FALSE;
    for (i = 0; i < 7; i++) {
        wall = PM_WALL(i);
        FX(0xE6 + i).visible = FALSE;
        FX(0xED + i).visible = FALSE;
        FX(0xF4 + i).visible = FALSE;
        FX(0xFC + i).visible = FALSE;
        FX(0x103 + i).visible = FALSE;
        FX(0x10A + i).visible = FALSE;
        if (wall->_28 == 0) {
            continue;
        }
        if (wall->_28 == 4) {
            idx = 0xFC + i + (wall->coinGenerationCategory == 2) * 7;
            if (wall->coinGenerationCategory == 2) {
                if (g_Minigame.wallBall_hitNoteBlock == 1) {
                    VecXYZ v;

                    v.x = wall->_0;
                    v.y = g_Ball.AtBat_Contact_BallPos.y;
                    v.z = wall->zPositionOfSomeWall;
                    fn_3_11A38C(idx, 3);
                    fn_3_151710(PM_MODEL(idx), &v);
                    callSfx(0x2EB);
                } else {
                    fn_3_11A38C(idx, 2);
                    callSfx(0x2EC);
                }
            } else if (wall->coinGenerationCategory == 0) {
                fn_3_11A38C(idx, 0);
                callSfx(0x2E2);
            } else {
                if (wall->coinGenerationCategory == 1) {
                    flag = 1;
                }
                callSfx(0x2FF);
            }
            fn_3_14C348(wall, flag);
            if (flag) {
                wall->_28 = 0;
                continue;
            }
            wall->_28 = 5;
        } else if (wall->_28 == 5) {
            u8 t;

            idx = 0xFC + i + (wall->coinGenerationCategory == 2) * 7;
            t = (u32)scanBoneAttachmentData(PM_MODEL(idx)->model);
            if (t < lbl_3_data_22634[wall->coinGenerationCategory] / 2 && t % 2 == 0) {
                PMModel* model = PM_MODEL(idx)->model;
                u32 j;

                for (j = 0; j < model->count; j++) {
                    f32* p = *(f32**)((u8*)model->parts[j] + 0xE8);

                    if (p != NULL) {
                        p[0] = p[0] + p[2];
                    }
                }
                continue;
            }
        } else if (wall->coinGenerationCategory == 0) {
            if (wall->_24 > lbl_3_data_21654[wall->coinGenerationCategory + 4] / 2) {
                idx = i + 0xED;
            } else {
                idx = 0xFB;
            }
        } else if (wall->coinGenerationCategory == 1) {
            idx = i + 0xF4;
        } else {
            idx = i + 0x10A;
            fn_3_1666B0(wall);
        }
        fx = &FX(idx);
        fx->visible = TRUE;
        fx->pos.x = wall->_0;
        fx->pos.y = -wall->_4;
        fx->pos.z = wall->zPositionOfSomeWall;
        fx->rot.x = 0.0f;
        fx->rot.y = 0.0f;
        fx->rot.z = 0.0f;
        fx->rot.x = wall->_18;
        applyUniformScaleToObject(1.75f, idx);
        if (-fx->pos.y <= lbl_3_data_21520[7].y && wall->_28 < 4) {
            PMEffect* shadow = &FX(0xE6 + i);

            shadow->visible = TRUE;
            shadow->pos.x = fx->pos.x;
            shadow->pos.y = -fx->pos.y;
            shadow->pos.z = fx->pos.z;
            shadow->pos.y = -0.03f;
            shadow->rot.x = 0.0f;
            shadow->rot.y = 0.0f;
            shadow->rot.z = 0.0f;
            applyUniformScaleToObject(1.75f * (1.0f - -fx->pos.y / lbl_3_data_21520[7].y), 0xE6 + i);
        }
    }
}

// .text:0x0011A38C size:0x7C mapped:0x80759420
void fn_3_11A38C(int idx, int kind) {
    void* v;
    ActorObjectEntry* obj = PM_ENTRY(idx);

    v = ANIM_PTR(0x70);
    obj->anim = v;
    obj->seqNum = kind;
    obj->frame = 0.0f;
    obj->animPending = 1;
    obj->framePending = v != NULL;
    obj->speedPending = v != NULL;
    obj->blendTime = 0.0f;
    obj->speed = 1.0f;
    obj->speedPending = 1;
    obj->frame = 0.0f;
    obj->framePending = 1;
    obj->boneParam = 2;
}

// .text:0x0011A350 size:0x3C mapped:0x807593E4
u32 fn_3_11A350(int idx) {
    return (u32)scanBoneAttachmentData(PM_MODEL_AT(idx)->model);
}

// .text:0x0011A210 size:0x140 mapped:0x807592A4
void fn_3_11A210(void) {
    PMEffect* fx;
    PMEffect* shadow;
    int i;

    for (i = 0; i < 100; i++) {
        fx = &FX(0x82 + i);
        fx->visible = FALSE;
        fx->update = NULL;
        shadow = &FX(i);
        shadow->visible = FALSE;
        shadow->update = NULL;
        if (g_Minigame.coinState[i] != 0) {
            fx->visible = TRUE;
            fx->pos.x = g_Minigame.coinPos[i].x;
            fx->pos.y = -g_Minigame.coinPos[i].y;
            fx->pos.z = g_Minigame.coinPos[i].z;
            applyUniformScaleToObject(1.75f, 0x82 + i);
            if (g_Minigame.coinFrameCounter[i] <= 1) {
                fx->rot.y = RandomF32_Game_Range(-3.1415927f, 3.1415927f);
            } else {
                fx->rot.y = radianAngleReduction(0.05f + fx->rot.y);
            }
            shadow->visible = TRUE;
            shadow->pos.x = g_Minigame.coinPos[i].x;
            shadow->pos.y = -0.05f;
            shadow->pos.z = g_Minigame.coinPos[i].z;
            applyUniformScaleToObject(4.325f, i);
        }
    }
}

// .text:0x0011A20C size:0x4 mapped:0x807592A0
void fn_3_11A20C(void) {
}

// .text:0x00119F6C size:0x2A0 mapped:0x80759000
void fn_3_119F6C(void) {
    PMEffect* fx;
    PMEffect* e;
    PMEffect* shadow;
    PMEffect* special;
    BB_barrelStruct* barrel;
    int i;
    u8 flag;

    flag = 0;
    fx = hugeAnimStruct.effects;
    special = &fx[15];
    fx[15].visible = FALSE;
    for (i = 0; i < 15; i++) {
        barrel = &g_Minigame.barrels[i];
        e = &FX(i);
        shadow = &FX(0x10 + i);
        shadow->visible = FALSE;
        e->visible = FALSE;
        if (barrel->barrelState != 0) {
            if (barrel->barrelState == 4) {
                e = shadow;
                if (barrel->animationCounter == 0) {
                    fn_3_119CA8(0x10 + i);
                    fn_3_14DC80(i);
                    callSfx(0x2E3);
                }
                {
                    u32 t = (u32)scanBoneAttachmentData(PM_MODEL(0x10 + i)->model);

                    if (t <= lbl_3_data_2263F) {
                        if ((t & 1) == 0) {
                            Actor* actor = PM_ACTORS->entries[0x10 + i].actor;
                            u32 j;

                            for (j = 0; j < actor->totalBones; j++) {
                                struct ANIMPipe* pipe = actor->boneArray[j]->animPipe;

                                if (pipe != NULL) {
                                    pipe->time = pipe->time + pipe->unk08;
                                }
                            }
                            shadow->visible = FALSE;
                            continue;
                        } else if (t == 0) {
                            fn_3_14CB28(i);
                        }
                    }
                }
            } else if (barrel->barrelColour == 3 && i == g_Minigame.bB_bombBarrelID_bOD_hrPitch) {
                flag = 1;
                e = special;
            }
            e->visible = TRUE;
            e->pos.x = barrel->currentPos.x;
            e->pos.y = -barrel->currentPos.y;
            e->pos.z = barrel->currentPos.z;
            e->rot.x = 0.0f;
            e->rot.y = 0.0f;
            e->rot.z = 0.0f;
            if (flag) {
                applyUniformScaleToObject(0.75f, 0xF);
            } else {
                applyUniformScaleToObject(0.75f, i);
            }
            if (flag) {
                flag = 0;
                e->update = fn_3_119E30;
            } else if (barrel->barrelState != 4) {
                e->update = fn_3_119EE0;
            } else {
                e->update = NULL;
            }
        }
    }
}

// .text:0x00119EE0 size:0x8C mapped:0x80758F74
void fn_3_119EE0(int idx) {
    PMMeshC* c = ((PMModel*)pmGetActor(idx))->parts[0]->b->c;

    c->d[1].frame = lbl_3_data_22638[g_Minigame.barrels[idx].barrelColour] * 3;
    c->d[2].frame = lbl_3_data_22638[g_Minigame.barrels[idx].barrelColour] * 3 + 1;
    c->d[3].frame = lbl_3_data_22638[g_Minigame.barrels[idx].barrelColour] * 3 + 2;
}

// .text:0x00119E30 size:0xB0 mapped:0x80758EC4
void fn_3_119E30(int idx) {
    PMMeshC* c;

    if (g_Minigame.barrels[g_Minigame.bB_bombBarrelID_bOD_hrPitch].animationCounter % lbl_3_data_2263E != 0) {
        return;
    }
    c = ((PMModel*)pmGetActor(idx))->parts[0]->b->c;
    c->d[1].frame = lbl_3_data_2263C[c->d[1].frame] == 0;
    c->d[2].frame = lbl_3_data_2263C[c->d[2].frame] == 0;
    c->d[3].frame = lbl_3_data_2263C[c->d[3].frame] == 0;
}

// .text:0x00119D34 size:0xFC mapped:0x80758DC8
void fn_3_119D34(void) {
    PMEffect* fx = &hugeAnimStruct.effects[0x1F];

    fx->visible = TRUE;
    nonPracticePitchingMachineLogic(fx, 0x1F);
    if (PauseSimulation == 0 && g_GameLogic.gameStatus == GAME_STATUS_AT_BAT &&
        g_Pitcher.pitchTotalTimeCounter == lbl_3_data_217A4[7]) {
        fn_3_119C34();
        callSfx(0x2E6);
    }
}

// .text:0x00119D28 size:0xC mapped:0x80758DBC
f32 fn_3_119D28(void) {
    return lbl_3_data_2262C;
}

// .text:0x00119CA8 size:0x80 mapped:0x80758D3C
void fn_3_119CA8(int idx) {
    void* v;
    ActorObjectEntry* obj = PM_ENTRY(idx);

    v = ANIM_PTR(0x74);
    obj->anim = v;
    obj->seqNum = 0;
    obj->frame = 0.0f;
    obj->animPending = 1;
    obj->framePending = v != NULL;
    obj->speedPending = v != NULL;
    obj->blendTime = 0.0f;
    obj->speed = 1.0f;
    obj->speedPending = 1;
    obj->frame = 0.0f;
    obj->framePending = 1;
    obj->boneParam = 2;
}

// .text:0x00119C34 size:0x74 mapped:0x80758CC8
void fn_3_119C34(void) {
    void* v;
    ActorObjectEntry* obj = PM_ENTRY(0x1F);

    v = ANIM_PTR(0x74);
    obj->anim = v;
    obj->seqNum = 1;
    obj->frame = 0.0f;
    obj->animPending = 1;
    obj->framePending = v != NULL;
    obj->speedPending = v != NULL;
    obj->blendTime = 0.0f;
    obj->speed = 1.0f;
    obj->speedPending = 1;
    obj->frame = 0.0f;
    obj->framePending = 1;
    obj->boneParam = 2;
}

// .text:0x00119934 size:0x300 mapped:0x807589C8
void fn_3_119934(void) {
    PMEffect* e;
    int kind;
    int i;
    PMEffect* fx;

    fx = hugeAnimStruct.effects;
    fx[0xA5].visible = FALSE;
    for (i = 0; i < 15; i++) {
        e = &FX(0x82 + i);
        e->visible = FALSE;
        kind = (&g_Minigame.ccs.chompState)[g_Minigame.coinState[i]] - 2;
        if (kind == 2) {
            if (g_Minigame.coinState[i] >= 1 && g_Minigame.coinState[i] <= 6) {
                fx[0xA5].visible = TRUE;
                fx[0xA5].pos.x = g_Minigame.coinPos[i].x;
                fx[0xA5].pos.y = g_Minigame.coinPos[i].y;
                fx[0xA5].pos.z = g_Minigame.coinPos[i].z;
                applyUniformScaleToObject(lbl_3_data_22650[kind], 0xA5);
                fx[0xA5].rot.y += 0.005f;
                if (fx[0xA5].rot.y > 3.1415927f) {
                    fx[0xA5].rot.y -= 6.2831855f;
                }
            }
        } else if (g_Minigame.coinState[i] >= 1 && g_Minigame.coinState[i] <= 6) {
            e->visible = TRUE;
            e->pos.x = g_Minigame.coinPos[i].x;
            e->pos.y = g_Minigame.coinPos[i].y;
            e->pos.z = g_Minigame.coinPos[i].z;
            applyUniformScaleToObject(lbl_3_data_22650[kind], 0x82 + i);
            e->rot.y += 0.005f;
            if (e->rot.y > 3.1415927f) {
                e->rot.y -= 6.2831855f;
            }
        }
    }
    for (i = 15; i < 35; i++) {
        e = &FX(0x82 + i);
        e->visible = FALSE;
        if (g_Minigame.turnOverStatus == 0 && g_Minigame.coinState[i] == 1) {
            VecXYZ tmp;

            e->visible = TRUE;
            e->pos.x = g_Minigame.coinPos[i].x;
            e->pos.y = -g_Minigame.coinPos[i].y;
            e->pos.z = g_Minigame.coinPos[i].z;
            applyUniformScaleToObject(5.0f, 0x82 + i);
            if (g_Minigame.coinFrameCounter[i] == 0) {
                f32 angle;

                e->rot.x = RandomF32_Game_Range(-3.1415927f, 3.1415927f);
                memcpy(&tmp, &g_Minigame.coinVelocity[i], sizeof(VecXYZ));
                tmp.y = 0.0f;
                PSVECNormalize((Vec*)&tmp, (Vec*)&tmp);
                angle = acos(tmp.x);
                if (0.0f > tmp.z) {
                    angle = 6.2831855f - angle;
                }
                e->rot.y = angle;
            } else if (PauseSimulation == 0) {
                memcpy(&tmp, &g_Minigame.coinVelocity[i], sizeof(VecXYZ));
                tmp.y = 0.0f;
                e->rot.x += 0.05f * PSVECMag((Vec*)&tmp) / lbl_3_data_2188C[3];
            }
        }
    }
}

// .text:0x00119878 size:0xBC mapped:0x8075890C
void fn_3_119878(void) {
    PMMinigame* g = &g_Minigame;
    PMEffect* fx = &hugeAnimStruct.effects[0xA6];

    fx->visible = FALSE;
    fx->update = NULL;
    if (g->powerup.activeInd) {
        if (g->powerup.timer > 60 || g->powerup.timer % 2 != 0 || g->ccs.chompState == 2 ||
            g->ccs.chompState == 3) {
            fx->visible = TRUE;
            fx->update = fn_3_11741C;
            fx->pos.x = g->powerup.pos.x;
            fx->pos.y = -g->powerup.pos.y;
            fx->pos.z = g->powerup.pos.z;
            applyUniformScaleToObject(3.5f, 0xA6);
        }
    }
}

// .text:0x00119854 size:0x24 mapped:0x807588E8
f32 fn_3_119854(u8 kind) {
    if (kind > 2) {
        kind = 2;
    }
    return lbl_3_data_22650[kind];
}

// .text:0x001194FC size:0x358 mapped:0x80758590
void fn_3_1194FC(void) {
    VecXYZ dir;
    VecXYZ ref = { 0.0f, 0.0f, 1.0f };
    PMEffect* a;
    PMEffect* shadow;
    int base;
    PMEffect* b;
    int i;
    int step;

    for (i = 0; i < PP_BALL_COUNT; i++) {
        a = &FX(0x85 + i);
        a->visible = FALSE;
        a->update = NULL;
        b = &FX(0xB7 + i);
        b->visible = FALSE;
        b->update = NULL;
        shadow = &FX(0x28 + i);
        shadow->visible = FALSE;
        shadow->update = NULL;
        if (PP.ballState[i] != 0 && PP.ballState[i] != 3 && PP.ballState[i] != 4) {
            if (PP.ballKind[i] == 5) {
                b->update = NULL;
                a = b;
                base = 0xB7;
            } else {
                a->update = fn_3_1194AC;
                base = 0x85;
            }
            a->visible = TRUE;
            a->pos.x = PP.ballPos[i].x;
            a->pos.y = -PP.ballPos[i].y;
            a->pos.z = PP.ballPos[i].z;
            if (PP.ballState[i] == 2) {
                f32 scaleY = lbl_3_data_22660[0] - PP.x_1C4C[i] * (lbl_3_data_22660[0] - lbl_3_data_22668) / lbl_3_data_2266C;

                if (PauseSimulation == 0) {
                    applyNonUniformScaleToObject(lbl_3_data_22660[0], scaleY, lbl_3_data_22660[0], base + i);
                    step = PP.x_1C4C[i] + (PP.x_1C1A[i] * -2 + 1);
                    PP.x_1C4C[i] = step;
                    if ((u8)step >= 0x3C) {
                        PP.x_1C1A[i] = PP.x_1C1A[i] == 0;
                    }
                    PP.x_1C4C[i] += PP.x_1C1A[i] * -2 + 1;
                }
                a->rot.x = 0.0f;
                a->rot.y = 0.0f;
                a->rot.z = 0.0f;
                if (PP.ballKind[i] == 5) {
                    a->pos.y -= 0.5f;
                }
            } else {
                applyUniformScaleToObject(lbl_3_data_22660[0], base + i);
                if (PP.ballState[i] != 6) {
                    f32 angle;

                    dir.x = PP.ballVel[i].x;
                    dir.y = 0.0f;
                    dir.z = PP.ballVel[i].z;
                    PSVECNormalize((Vec*)&dir, (Vec*)&dir);
                    angle = acos(PSVECDotProduct((Vec*)&ref, (Vec*)&dir));
                    if (0.0f > dir.x) {
                        angle = 6.2831855f - angle;
                    }
                    if (PauseSimulation == 0) {
                        a->rot.y = angle;
                        a->rot.x += -0.17453292f;
                    }
                }
                if (PP.ballKind[i] == 5 && PP.ballFrames[i] == 1) {
                    fn_3_15521C(i, &a->pos, &a->rot);
                }
                if (PP.ballKind[i] == 5) {
                    a->update = fn_3_119468;
                }
                shadow->visible = TRUE;
                shadow->pos.x = PP.ballPos[i].x;
                shadow->pos.y = -0.05f;
                shadow->pos.z = PP.ballPos[i].z;
                applyUniformScaleToObject(lbl_3_data_22660[1], 0x28 + i);
            }
        }
    }
}

// .text:0x001194AC size:0x50 mapped:0x80758540
void fn_3_1194AC(int idx) {
    ((PMModel*)pmGetActor(idx))->parts[0]->b->c->d[1].frame = lbl_3_data_2265C[PP.ballKind[idx - 0x85]];
}

// .text:0x00119468 size:0x44 mapped:0x807584FC
void fn_3_119468(int idx) {
    if (PM_MODEL_AT(idx)->model->flags & 9) {
        pP_SetPulseTevCallback();
    }
}

// .text:0x001192B8 size:0x1B0 mapped:0x8075834C
void fn_3_1192B8(void) {
    PMEffect* fx;
    PPSpawner* sp;
    int i;

    for (i = 0; i < PP_SPAWNER_COUNT; i++) {
        fx = &FX(0x82 + i);
        sp = &PP.spawner[i];
        fx->visible = FALSE;
        if (sp->mode != 0) {
            fx->visible = TRUE;
            fx->pos.x = sp->pos.x;
            fx->pos.y = -sp->pos.y;
            fx->pos.z = sp->pos.z;
            if (sp->mode != 3) {
                applyUniformScaleToObject(lbl_3_data_22678[sp->isBig], 0x82 + i);
            } else {
                f32 t = (f32)sp->_1A / (f32)lbl_3_data_21E68[6];
                f32* scales = &lbl_3_data_22678[sp->isBig];

                applyUniformScaleToObject((1.0f - t) * scales[0] + scales[2] * t, 0x82 + i);
            }
            if (sp->isBig == 0) {
                fx->rot.y = sp->angle;
                fx->rot.x = 0.0f;
                fx->rot.z = 0.0f;
            } else {
                fx->rot.y = lbl_3_data_22688[i];
            }
            if (sp->mode == 4 && sp->_1C <= 0 && (sp->_1A & 1)) {
                fx->visible = FALSE;
            }
            fx->update = fn_3_11897C;
            fn_3_118B18(i);
        }
    }
}

// .text:0x00118B18 size:0x7A0 mapped:0x80757BAC
void fn_3_118B18(int slot) {
    PPSpawner* sp = &PP.spawner[slot];

    sp->_28++;
    if (sp->mode == 1) {
        if (sp->_1A <= 1) {
            fn_3_1189C8(slot, 2, 0, 0, FALSE);
            applyUniformScaleToObject(0.01f, 0x82 + slot);
        } else {
            applyUniformScaleToObject(LinearInterpolateToNewRange(sp->_1A, 0.0f, lbl_3_data_21E68[5],
                                                                  lbl_3_data_22678[2 + sp->isBig],
                                                                  lbl_3_data_22678[sp->isBig]),
                                      0x82 + slot);
        }
        if (sp->_1C == 1) {
            fn_3_1189C8(slot, 0, 0, 6, TRUE);
        }
    } else if (sp->mode == 4) {
        if (sp->_1A <= 1) {
            fn_3_1189C8(slot, 4, 0, 0, FALSE);
        }
    } else if (sp->_1E == 2) {
        if (sp->isBig == 0) {
            fn_3_1189C8(slot, 1, 0, 0, FALSE);
        } else {
            fn_3_1189C8(slot, 5, 0, 0, FALSE);
        }
    } else if (sp->_1E == lbl_3_data_21E68[7]) {
        if (sp->_33 != 0) {
            fn_3_1189C8(slot, 0, 0, 6, TRUE);
        }
    } else {
        if (sp->_2E != 0 && (sp->_26 == 1 || sp->isBig != 0)) {
            int frame = lbl_3_data_226B8[0] - lbl_3_data_21E68[13] - 1;

            if (sp->isBig == 0) {
                pP_PiranhaAimAtPlayer(sp);
            }
            fn_3_1189C8(slot, 3, frame, 2, FALSE);
        }
        if (sp->_33 == 3 && sp->_28 == lbl_3_data_226B8[1] - lbl_3_data_226AC[3]) {
            fn_3_1189C8(slot, 0, 0, 6, TRUE);
            PP.spawner[slot]._14 = 0.0f;
            PP.spawner[slot]._0C = 0.0f;
            PP.spawner[slot].angle = lbl_3_data_22688[slot];
        }
    }
}

// .text:0x001189C8 size:0x150 mapped:0x80757A5C
void fn_3_1189C8(int slot, int kind, int frame, int divisor, u8 flag) {
    PPSpawner* sp = &PP.spawner[slot];
    ActorObjectEntry* obj = PM_ENTRY(0x82 + slot);
    f32 rate = 0.0f;
    void* v;

    if (divisor != 0) {
        rate = 1.0f / divisor;
    }
    v = ANIM_PTR(0x78);
    obj->anim = v;
    obj->seqNum = kind;
    obj->frame = 0.0f;
    obj->animPending = 1;
    obj->framePending = v != NULL;
    obj->speedPending = v != NULL;
    obj->blendTime = rate;
    obj->speed = lbl_3_data_22694[kind];
    obj->speedPending = 1;
    obj->frame = frame + lbl_3_data_226AC[kind];
    obj->framePending = 1;
    if (flag) {
        obj->boneParam = 3;
    } else {
        obj->boneParam = 2;
    }
    sp->_33 = kind;
    sp->_28 = frame;
}

// .text:0x0011897C size:0x4C mapped:0x80757A10
void fn_3_11897C(int idx) {
    ((PMMeshA*)pmGetActor(idx))->b->c->d[1].frame = lbl_3_data_22670[PP.spawner[idx - 0x82].kind];
}

// .text:0x0011887C size:0x100 mapped:0x80757910
void fn_3_11887C(void) {
    PMEffect* fx;
    int i;

    for (i = 0; i < 7; i++) {
        fx = &FX(0xE9 + i);
        fx->visible = TRUE;
        if (i < 4) {
            fx->pos.x = lbl_3_data_21B94[i].x;
            fx->pos.y = -lbl_3_data_21B94[i].y;
            fx->pos.z = lbl_3_data_21B94[i].z;
            fx->pos.y = 0.0f;
            applyNonUniformScaleToObject(lbl_3_data_226C4[2], lbl_3_data_226C4[3], lbl_3_data_226C4[2], 0xE9 + i);
            fx->update = fn_3_11881C;
        } else {
            fx->pos.x = lbl_3_data_21BC4[i - 4][0].x;
            fx->pos.y = -lbl_3_data_21BC4[i - 4][0].y;
            fx->pos.z = lbl_3_data_21BC4[i - 4][0].z;
            applyNonUniformScaleToObject(lbl_3_data_226C4[0], lbl_3_data_226C4[1], lbl_3_data_226C4[0], 0xE9 + i);
            fx->update = fn_3_11881C;
        }
    }
}

// .text:0x0011881C size:0x60 mapped:0x807578B0
void fn_3_11881C(int idx) {
    s16 frame;

    if (idx - 0xE9 < 4) {
        frame = lbl_3_data_226BC[idx - 0xE9];
    } else {
        frame = lbl_3_data_226BC[4];
    }
    {
        ActorObjectEntry* e = ((ActorObjectTable*)hugeAnimStruct.modelTable)->entries;
        e += idx;
        ((PMModel*)e->actor)->parts[0]->b->c->d[1].frame = frame;
    }
}

// .text:0x0011874C size:0xD0 mapped:0x807577E0
void fn_3_11874C(void) {
    int i;

    if (g_GameLogic.secondaryGameMode != SECONDARY_GAME_MODE_STAR_DASH) {
        for (i = 0; i < (s32)ARRAY_SIZE(SD.fireBarFlame); i++) {
            PMEffect* fx = &FX(i);
            SDFireBarFlame* flame = &SD.fireBarFlame[i];

            fx->visible = FALSE;
            fx->update = NULL;
            if (flame->active) {
                fx->visible = TRUE;
                fx->pos.x = flame->pos.x;
                fx->pos.z = flame->pos.z;
                fx->pos.y = -0.01f;
                applyNonUniformScaleToObject(lbl_3_data_226D4[1], 1.0f, lbl_3_data_226D4[1], i);
            }
        }
    }
}

// .text:0x00118614 size:0x138 mapped:0x807576A8
void fn_3_118614(void) {
    DrawingSceneStruct* node = currentDrawingItem;
    int i;

    addGraphicsElementToScene(node, lbl_3_data_69D0);
    for (i = 0; i < (s32)ARRAY_SIZE(SD.fireBarFlame); i++) {
        ((UIRecord*)graphicsRelatedArray[((MenuScene*)node)->firstHandle + i].object)->frame = 0x20000;
    }
    currentDrawingItem->func = fn_3_118508;
}

// .text:0x00118508 size:0x10C mapped:0x8075759C
void fn_3_118508(void) {
    DrawingSceneStruct* node = currentDrawingItem;
    int i;

    if (g_GameLogic.gameStatus == GAME_STATUS_TRANSITION_MINIGAME_POSTGAME) {
        removeGraphicsElementFromScene(node);
        removeCurrentDrawingItem();
    } else {
        for (i = 0; i < (s32)ARRAY_SIZE(SD.fireBarFlame); i++) {
            if (SD.fireBarFlame[i].active == 0) {
                ((UIRecord*)graphicsRelatedArray[((MenuScene*)node)->firstHandle + i].object)->flags &= ~UI_FLAG_VISIBLE;
            } else {
                ((UIRecord*)graphicsRelatedArray[((MenuScene*)node)->firstHandle + i].object)->flags |= UI_FLAG_VISIBLE;
                ((UIRecord*)graphicsRelatedArray[((MenuScene*)node)->firstHandle + i].object)->pos.x = SD.fireBarFlame[i].pos.x;
                ((UIRecord*)graphicsRelatedArray[((MenuScene*)node)->firstHandle + i].object)->pos.y = -SD.fireBarFlame[i].pos.y;
                ((UIRecord*)graphicsRelatedArray[((MenuScene*)node)->firstHandle + i].object)->pos.z = SD.fireBarFlame[i].pos.z;
            }
        }
    }
}

// .text:0x001183FC size:0x10C mapped:0x80757490
static inline void pmPlaceMarker(int i) {
    PMEffect* fx = &hugeAnimStruct.effects[0xF0 + i];

    fx->pos.x = lbl_3_data_21B94[i].x;
    fx->pos.y = -lbl_3_data_21B94[i].y;
    fx->pos.z = lbl_3_data_21B94[i].z;
    fx->pos.y = 0.0f;
    fx->pos.z -= lbl_3_data_226DC;
    fx->visible = TRUE;
}

void fn_3_1183FC(void) {
    pmPlaceMarker(0);
    pmPlaceMarker(1);
    pmPlaceMarker(2);
    pmPlaceMarker(3);
}

// .text:0x00118358 size:0xA4 mapped:0x807573EC
void fn_3_118358(int slot, VecXYZ* out) {
    sBone* bone = ((Actor*)PM_MODEL(0x82 + slot)->model)->boneArray[17];

    if (slot < 0 || slot > 2) {
        return;
    }
    if (out != NULL) {
        memset(out, 0, sizeof(VecXYZ));
        PSMTXMultVec(bone->forwardMtx, (Vec*)out, (Vec*)out);
        out->y *= -1.0f;
    }
}

// .text:0x00118164 size:0x1F4 mapped:0x807571F8
void fn_3_118164(void) {
    PMEffect* fx;
    PMEffect* shadow;
    int i;
    int idx;

    for (i = 0; i < 100; i++) {
        idx = 0x82 + i;
        fx = &FX(idx);
        fx->visible = FALSE;
        shadow = &FX(i);
        shadow->visible = FALSE;
        if (g_Minigame.coinState[i] == 1 || g_Minigame.coinState[i] == 3) {
            fx->visible = TRUE;
            fx->pos.x = g_Minigame.coinPos[i].x;
            fx->pos.y = -g_Minigame.coinPos[i].y;
            fx->pos.z = g_Minigame.coinPos[i].z;
            fx->rot.x = 0.0f;
            fx->rot.z = 0.0f;
            applyUniformScaleToObject(2.0f, idx);
            if (g_Minigame.coinFrameCounter[i] <= 1) {
                fx->rot.y = RandomF32_Game_Range(-3.1415927f, 3.1415927f);
            } else if (g_Minigame.coinState[i] == 1) {
                fx->rot.y = radianAngleReduction(0.05f + fx->rot.y);
            } else {
                fx->rot.y = radianAngleReduction(10.0f + fx->rot.y);
            }
            shadow->visible = TRUE;
            shadow->update = NULL;
            shadow->pos.x = g_Minigame.coinPos[i].x;
            shadow->pos.y = -0.05f;
            shadow->pos.z = g_Minigame.coinPos[i].z;
            applyUniformScaleToObject(5.0f, i);
            if (g_Minigame.coinFrameCounter[i] > lbl_3_data_21A04[3] - 0xB4 && g_Minigame.coinState[i] == 1 &&
                (g_d_GameSettings.FrameCountWhileNotAtMainMenu & 1)) {
                fx->visible = FALSE;
                shadow->visible = FALSE;
            }
            if (g_Minigame.coinState[i] == 3 && (g_d_GameSettings.FrameCountWhileNotAtMainMenu & 1)) {
                fx->visible = FALSE;
                shadow->visible = FALSE;
            }
        }
    }
}

// .text:0x001180A4 size:0xC0 mapped:0x80757138
void fn_3_1180A4(void) {
    PMEffect* fx = hugeAnimStruct.effects;

    fx[100].visible = FALSE;
    fx[0xE6].visible = FALSE;
    if (SD.coinBag.active == 1) {
        fx[0xE6].visible = TRUE;
        fx[0xE6].pos.x = SD.coinBag.pos.x;
        fx[0xE6].pos.y = -SD.coinBag.pos.y;
        fx[0xE6].pos.z = SD.coinBag.pos.z;
        fx[0xE6].rot.x = 0.0f;
        fx[0xE6].rot.y = 0.0f;
        fx[0xE6].rot.z = 0.0f;
        fx[100].visible = TRUE;
        fx[100].update = NULL;
        fx[100].pos.x = SD.coinBag.pos.x;
        fx[100].pos.y = -0.05f;
        fx[100].pos.z = SD.coinBag.pos.z;
        applyUniformScaleToObject(10.0f, 100);
    }
}

// .text:0x00117FC8 size:0xDC mapped:0x8075705C
void fn_3_117FC8(void) {
    PMEffect* fx = hugeAnimStruct.effects;

    fx[0xE8].visible = FALSE;
    FX(0x65).visible = FALSE;
    if (SD.starActive) {
        fx[0xE8].visible = TRUE;
        fx[0xE8].pos.x = SD.starPos.x;
        fx[0xE8].pos.y = -SD.starPos.y;
        fx[0xE8].pos.z = SD.starPos.z;
        applyUniformScaleToObject(3.0f, 0xE8);
        if (SD.starFrames == 0) {
            fx[0xE8].rot.y = RandomF32_Game_Range(-3.1415927f, 3.1415927f);
        } else {
            fx[0xE8].rot.y = radianAngleReduction(0.1f + fx[0xE8].rot.y);
        }
        fx[0xE8].update = fn_3_117B78;
    }
}

// .text:0x00117B78 size:0x450 mapped:0x80756C0C
void fn_3_117B78(int idx) {
    PMEffect* fx = &FX(idx);
    f32 uv[8] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f };
    VecXYZ v[4];
    VecXYZ tmp;
    GXColor color;
    u32 i;
    f32 half = 1.5f;
    f32 sinA;
    f32 cosA;

    pmSetupQuadState();
    v[0].z = v[1].z = half;
    v[0].x = v[3].x = -half;
    v[1].x = v[2].x = half;
    v[2].z = v[3].z = -half;
    for (i = 0; i < 4; i++) {
        memcpy(&tmp, &v[i], sizeof(VecXYZ));
        sinA = sin(-fx->rot.y);
        cosA = cos(-fx->rot.y);
        v[i].x = tmp.x * cosA + tmp.z * -sinA;
        cosA = cos(-fx->rot.y);
        sinA = sin(-fx->rot.y);
        v[i].z = tmp.x * sinA + tmp.z * cosA;
    }
    for (i = 0; i < 4; i++) {
        v[i].x += fx->pos.x;
        v[i].z += fx->pos.z;
    }
    v[0].y = v[1].y = v[2].y = v[3].y = -0.06f;
    color.r = color.g = color.b = 0;
    color.a = 0x9B;
    pmSetupQuadCamera(0x14);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    for (i = 0; i < 4; i++) {
        GXPosition3f32(v[i].x, v[i].y, v[i].z);
        GXColor1u32(*(u32*)&color);
        GXTexCoord2f32(uv[i * 2], uv[i * 2 + 1]);
    }
}

// .text:0x00117AE4 size:0x94 mapped:0x80756B78
void fn_3_117AE4(void) {
    PMEffect* fx = hugeAnimStruct.effects;

    fx[0xE7].visible = TRUE;
    fx[0xE7].pos.x = lbl_3_data_21A48.x;
    fx[0xE7].pos.z = lbl_3_data_21A48.z;
    fx[0xE7].pos.y = 0.0f;
    fx[0xE7].rot.x = 0.0f;
    fx[0xE7].rot.z = 0.0f;
    fx[0xE7].rot.y = shortAngleToRad(0x1000 - SD.fireBarAngle[0]);
    applyUniformScaleToObject(3.0f, 0xE7);
}

// .text:0x001179EC size:0xF8 mapped:0x80756A80
void fn_3_1179EC(void) {
    PMEffect* fx;
    SDThwomp* thwomp;
    u32 i;

    for (i = 0; i < 4; i++) {
        fx = &FX(0xE9 + i);
        thwomp = &SD.thwomp[i];
        fx->visible = FALSE;
        fx->update = NULL;
        if (thwomp->state != 0) {
            fx->visible = TRUE;
            fx->pos.x = thwomp->pos.x;
            fx->pos.y = -thwomp->pos.y;
            fx->pos.z = thwomp->pos.z;
            fx->rot.x = 0.017453292f * thwomp->rot.x;
            fx->rot.y = 0.017453292f * thwomp->rot.y;
            fx->rot.z = 0.017453292f * thwomp->rot.z;
            applyUniformScaleToObject(2.5f, 0xE9 + i);
            fx->update = fn_3_117588;
        }
    }
}

// .text:0x00117588 size:0x464 mapped:0x8075661C
void fn_3_117588(int idx) {
    f32 uv[8] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f };
    PMEffect* fx = &FX(idx);
    SDThwomp* thwomp = &SD.thwomp[idx - 0xE9];
    f32 scale;
    f32 halfW;
    f32 halfH;
    VecXYZ v[4];
    GXColor color;
    PMModel* model;
    int frame;
    int i;

    scale = 2.5f * (1.0f - (-fx->pos.y * 0.5f) / lbl_3_data_21A64[0]);
    pmSetupQuadState();
    halfW = 2.8f * scale * 0.5f;
    halfH = 2.5f * scale * 0.5f;
    color.r = color.g = color.b = 0;
    v[0].x = v[3].x = -halfW + fx->pos.x;
    v[0].z = v[1].z = halfH + fx->pos.z;
    v[1].x = v[2].x = halfW + fx->pos.x;
    v[2].z = v[3].z = -halfH + fx->pos.z;
    v[0].y = v[1].y = v[2].y = v[3].y = -0.06f;
    color.a = 0x9B;
    pmSetupQuadCamera(0x13);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    for (i = 0; i < 4; i++) {
        GXPosition3f32(v[i].x, v[i].y, v[i].z);
        GXColor1u32(*(u32*)&color);
        GXTexCoord2f32(uv[i * 2], uv[i * 2 + 1]);
    }

    model = PM_MODEL_AT(idx)->model;
    if (thwomp->state == 1 || thwomp->state == 5) {
        frame = 0;
    } else {
        frame = 1;
    }
    for (i = 0; i < model->count; i++) {
        model->parts[i]->b->c->d[1].frame = frame;
    }
}

// .text:0x00117494 size:0xF4 mapped:0x80756528
void fn_3_117494(void) {
    PMMinigame* g = &g_Minigame;
    PMEffect* fx = hugeAnimStruct.effects;

    fx[0xED].visible = FALSE;
    fx[0x65].visible = FALSE;
    fx[0xED].update = NULL;
    if (g->powerup.activeInd) {
        if (g->powerup.timer > 60 || g->powerup.timer % 2 != 0) {
            fx[0xED].visible = TRUE;
            fx[0xED].update = fn_3_11741C;
            fx[0xED].pos.x = g->powerup.pos.x;
            fx[0xED].pos.y = -g->powerup.pos.y;
            fx[0xED].pos.z = g->powerup.pos.z;
            applyUniformScaleToObject(2.5f, 0xED);
            fx[0x65].visible = TRUE;
            fx[0x65].pos.x = g->powerup.pos.x;
            fx[0x65].pos.y = -0.05f;
            fx[0x65].pos.z = g->powerup.pos.z;
            applyUniformScaleToObject(12.5f, 0x65);
        }
    }
}

// .text:0x0011741C size:0x78 mapped:0x807564B0
void fn_3_11741C(int idx) {
    PMModel* model;
    int frame;
    int i;

    model = PM_MODEL_AT(idx)->model;
    frame = g_Minigame.powerup.activeInd == 1 ? 0 : 2;
    for (i = 0; i < model->count; i++) {
        model->parts[i]->b->c->d[1].frame = frame;
    }
}

// .text:0x00116B74 size:0x8A8 mapped:0x80755C08
void fn_3_116B74(void) {
    int i;
    int j;

    switch (g_Minigame.GameMode_MiniGame) {
    case MINI_GAME_ID_BOBOMB_DERBY:
        fn_3_116B38();
        break;
    case MINI_GAME_ID_WALLBALL:
        pmDisableWallBallEffects();
        break;
    case MINI_GAME_ID_BARREL_BATTER:
        fn_3_116B38();
        fn_3_119F6C();
        break;
    case MINI_GAME_ID_CHAINCHOMP_SPRINT:
        fn_3_119934();
        fn_3_117494();
        break;
    case MINI_GAME_ID_STAR_DASH:
        fn_3_118164();
        fn_3_117FC8();
        for (i = 0; i < 40; i++) {
            PMEffect* fx = &FX(i);

            fx->visible = FALSE;
            fx->update = NULL;
        }
        fn_3_1179EC();
        fn_3_117494();
        break;
    case MINI_GAME_ID_PIRANHA_PANIC:
        fn_3_1194FC();
        fn_3_116840();
        for (i = 0; i < 40; i++) {
            PMEffect* fx = &FX(i);

            fx->visible = FALSE;
            fx->update = NULL;
        }
        for (j = 0; j < 7; j++) {
            PMEffect* fx = &FX(0xE9 + j);

            fx->visible = FALSE;
            if (j >= 4) {
                fx->visible = TRUE;
                fx->pos.x = lbl_3_data_21BC4[j - 4][0].x;
                fx->pos.y = -lbl_3_data_21BC4[j - 4][0].y;
                fx->pos.z = lbl_3_data_21BC4[j - 4][0].z;
                applyNonUniformScaleToObject(lbl_3_data_226C4[0], lbl_3_data_226C4[1],
                                             lbl_3_data_226C4[0], 0xE9 + j);
                fx->update = fn_3_11881C;
            }
        }
        FX(0xF0).visible = FALSE;
        FX(0xF1).visible = FALSE;
        FX(0xF2).visible = FALSE;
        FX(0xF3).visible = FALSE;
        break;
    }
}

// .text:0x00116B38 size:0x3C mapped:0x80755BCC
void fn_3_116B38(void) {
    int idx = 2;

    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER) {
        idx = 0x1F;
    }
    ((u8*)hugeAnimStruct.effects)[idx * 0x28 + 0x26] = 0;
}

// .text:0x001169D0 size:0x168 mapped:0x80755A64
void fn_3_1169D0(void) {
    pmDisableWallBallEffects();
}

// .text:0x00116840 size:0x190 mapped:0x807558D4
void fn_3_116840(void) {
    int i;

    for (i = 0; i < PP_SPAWNER_COUNT; i++) {
        PMEffect* fx = &FX(0x82 + i);
        PPSpawner* sp = &PP.spawner[i];

        fx->visible = FALSE;
        if (sp->mode != 0) {
            fx->visible = TRUE;
            fx->pos.x = sp->pos.x;
            fx->pos.y = -sp->pos.y;
            fx->pos.z = sp->pos.z;
            applyUniformScaleToObject(lbl_3_data_22678[sp->isBig], 0x82 + i);
            fx->rot.y = lbl_3_data_22688[i];
            fx->update = fn_3_11897C;
            if (sp->_1C == 1) {
                fn_3_1189C8(i, 0, 0, 6, TRUE);
                sp->_1C++;
            }
        }
    }
}
