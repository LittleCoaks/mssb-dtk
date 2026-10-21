#include "menus/captain_select/captain_model_load.h"
#include "menus/captain_select/captain_select.h"
#include "menus/yd_step.h"
#include "header_rep_data.h"
#include "menus/debug_menu_text.h"
#include "static/UnknownHomes_Static.h"
#define SQRT2_LINKAGE static
#include "game/UnknownHomes_Game.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x800bdd74.h"
#include "Unknown/File_0x800a7568.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/File_0x80025ddc.h"
#include "Unknown/File_0x80025c58.h"
#include "Unknown/File_0x8001d180.h"
#include "Unknown/File_0x8001fc4c.h"
#include "Unknown/File_0x80023b04.h"
#include "Unknown/File_0x800bd478.h"
#include "Unknown/File_0x800bd8c4.h"
#include "Unknown/File_0x800bda94.h"
#include "Unknown/File_0x800c0770.h"
#include "Unknown/objinit.h"
#include "C3/skinning.h"
#include "Unknown/dvdsys.h"
#include "C3/actor.h"
#include "C3/actor/act.h"
#include "C3/actor/actorAnim.h"
#include "C3/control.h"
#include "C3/anim.h"
#include "C3/geoPalette/geoPalette.h"
#include "C3/geoPalette/DisplayObject.h"
#include "Dolphin/mtx.h"
#include "Dolphin/GX/GXPixel.h"
#include "Dolphin/GX/GXGeometry.h"
#include "Dolphin/GX/GXTransform.h"
#include "Dolphin/stl.h"

#define CAP_MODEL_COUNT 13
#define CAP_PORT_COUNT 4
#define BONE_SLOT_NONE 0xFFFF

typedef struct {
    /* 0x00 */ u32 _00;
    /* 0x04 */ u32 sizeFlags; // low 28 bits: size of the file
    /* 0x08 */ u32 _08;
    /* 0x0C */ u32 _0C;
} ModelFileEntry; // size: 0x10

/* One of the two draw buffers of a CapEntry. */
typedef struct {
    /* 0x00 */ void *buffer;
    /* 0x04 */ u8 _04[0x10];
    /* 0x14 */ f32 scale;
    /* 0x18 */ u8 _18[0x60 - 0x18];
    /* 0x60 */ s8 index;
    /* 0x61 */ s8 _61;
    /* 0x62 */ u8 _62[2];
} CapBuffer; // size: 0x64

typedef struct {
    /* 0x00 */ CapBuffer bufs[2];
    /* 0xC8 */ u32 _C8;
    /* 0xCC */ u8 _CC;
    /* 0xCD */ u8 _CD;
    /* 0xCE */ u8 _CE;
    /* 0xCF */ s8 _CF;
    /* 0xD0 */ s8 _D0;
    /* 0xD1 */ s8 _D1;
    /* 0xD2 */ u8 _D2[2];
} CapEntry; // size: 0xD4

/* One loaded captain model. */
typedef struct {
    /* 0x000 */ void *actor;
    /* 0x004 */ u8 _004[4];
    /* 0x008 */ u32 *files;
    /* 0x00C */ u8 _00C[4];
    /* 0x010 */ void *_10[6];
    /* 0x028 */ u8 _028[4];
    /* 0x02C */ u8 *_2C;
    /* 0x030 */ CapEntry *entry;
    /* 0x034 */ f32 _34;
    /* 0x038 */ f32 _38;
    /* 0x03C */ f32 _3C;
    /* 0x040 */ f32 _40;
    /* 0x044 */ f32 _44;
    /* 0x048 */ f32 _48;
    /* 0x04C */ f32 _4C;
    /* 0x050 */ u8 _050[0x62 - 0x50];
    /* 0x062 */ s16 _62;
    /* 0x064 */ u8 _064[4];
    /* 0x068 */ s16 _68;
    /* 0x06A */ u8 _06A[0x162 - 0x6A];
    /* 0x162 */ u16 boneSlots[0x32];
    /* 0x1C6 */ u8 _1C6[0x252 - 0x1C6];
    /* 0x252 */ E(s8, CHAR_ID) charID;
    /* 0x253 */ u8 _253;
    /* 0x254 */ u8 _254;
    /* 0x255 */ s8 entryIdx;
    /* 0x256 */ u8 _256[0x25C - 0x256];
    /* 0x25C */ u8 _25C;
    /* 0x25D */ u8 _25D;
    /* 0x25E */ u8 _25E[0x265 - 0x25E];
    /* 0x265 */ u8 _265;
    /* 0x266 */ u8 _266[0x268 - 0x266];
    /* 0x268 */ u8 _268;
    /* 0x269 */ u8 _269[3];
    /* 0x26C */ u8 _26C;
    /* 0x26D */ u8 _26D[0x27C - 0x26D];
} CapSlot; // size: 0x27C

typedef struct {
    /* 0x0000 */ u8 _0000[0x60];
    /* 0x0060 */ ActorObjectTable *objTable;
    /* 0x0064 */ u8 _0064[0xAC - 0x64];
    /* 0x00AC */ u32 _AC[4];
    /* 0x00BC */ u8 _00BC[0x13C - 0xBC];
    /* 0x013C */ void *_13C;
    /* 0x0140 */ CapEntry entries[CAP_MODEL_COUNT];
    /* 0x0C04 */ CapSlot slots[CAP_MODEL_COUNT];
    /* 0x2C50 */ CapSlot *objects[CAP_MODEL_COUNT];
    /* 0x2C84 */ u8 _2C84[8];
    /* 0x2C8C */ u8 *modelPool;
    /* 0x2C90 */ u8 _2C90[0x2D94 - 0x2C90];
    /* 0x2D94 */ u8 *actorEntries;
    /* 0x2D98 */ u8 _2D98[0x3078 - 0x2D98];
    /* 0x3078 */ u16 actorCount;
    /* 0x307A */ u8 _307A;
    /* 0x307B */ u8 _307B;
    /* 0x307C */ u8 _307C;
    /* 0x307D */ u8 _307D[0x3154 - 0x307D];
} CapAnimView; // size: 0x3154

/* Scene state of the load-screen tasks; shares the DrawingSceneStruct header. */
typedef struct {
    /* 0x00 */ u8 _00[0x10];
    /* 0x10 */ s16 _10;
    /* 0x12 */ u8 _12[2];
    /* 0x14 */ CapSlot *slot;
    /* 0x18 */ E(u8, CHAR_ID) charIDs[CAP_PORT_COUNT];
    /* 0x1C */ u8 stage;
    /* 0x1D */ u8 step;
    /* 0x1E */ u8 index;
    /* 0x1F */ u8 _1F;
    /* 0x20 */ u8 _20;
    /* 0x21 */ u8 loadStep;
} CapLoadTask;

extern CapAnimView hugeAnimStruct;
extern u8 lbl_2_bss_100B8[0x54];
extern u8 lbl_2_bss_100B4;
extern u8 lbl_2_bss_1010C[0x58];
extern CapLoadTask *lbl_2_bss_1224;
extern u8 *lbl_2_bss_1228;
extern u8 *lbl_2_bss_122C;
extern CapBuffer lbl_2_bss_101AC[CAP_PORT_COUNT];

extern ModelFileEntry CharacterHandFiles[];
extern ModelFileEntry HandPoseEventSetFiles[];

DebugMenuText lbl_2_data_1E28 = {
    { "BAT FIRST", "BAT LAST" },
    "FL",
    "PC",
    { "RR", "RL", "LR", "LL" },
    { "OFF", "ON" },
    { "SELECT DEBUG MENU", "HIDE CHARA SET", "STAR PLAYER SET", "KOOPA STA FLAG SET", "CHALLE LEVEL FREE SET" },
    { "1P >", "COM1>", "2P >", "COM2>", "3P >", "COM3>", "4P >", "COM4>" },
    { 0x0000FF0F, 0x0000880F, 0x00000FFF, 0x0000088F, 0x0000F0FF, 0x0000808F, 0x0000F00F, 0x0000800F },
    { 0, 4, 10, 6, 2, 9, 1, 5, 11, 17, 3, 19 },
    { 0, 2, 6, 8, 4, 10, 1, 3, 7, 5, 9, 11 },
    { 0, 0, 6, 2, 8, 4, 10, 5, 11, 3, 9, 1, 7, 0, 0, 0 },
};

/* Read by captain_select.c. */
f32 lbl_2_data_20EC[3] = { 0.8f, -1.1f, -4.9f };

/* Captain-select model positions, one per team (read by captain_select.c). */
f32 lbl_2_data_20F8[2][3] = {
    { -225.0f, -35.0f, 0.0f },
    { 95.0f, -35.0f, 0.0f },
};

/* Unreferenced: u16 and u8 index tables followed by f32 scales (0.7, 0.4, ...). */
u32 lbl_2_data_2110[0xC3] = {
    0x00160010, 0x00170011, 0x00180012, 0x00190013, 0x001A0014, 0x001B0015,
    0x0020001C, 0x0021001D, 0x0022001E, 0x0023001F, 0x00260025, 0x00280027,
    0x003D003C, 0xFFFF0000, 0x004A004B, 0xFFFF0000, 0x002F0034, 0x00300035,
    0x00310036, 0x00320037, 0x00330038, 0xFFFF0000, 0x00410047, 0x00420048,
    0x00430049, 0x0044004A, 0x0045004B, 0x0046004C, 0xFFFF0000, 0x002F0034,
    0xFFFF0000, 0x00000001, 0x00020003, 0x00040005, 0x00060007, 0x00080009,
    0x000E000F, 0x000D000C, 0x000B000A, 0x00160017, 0x00180019, 0x001A001B,
    0x00100011, 0x00120013, 0x00140015, 0x00200021, 0x00220023, 0x001C001D,
    0x001E001F, 0x00240026, 0x00250028, 0x00270029, 0x002A002B, 0x002C002D,
    0x002E002F, 0x00300031, 0x00320033, 0x00340035, 0x00360037, 0x00380039,
    0x003A003B, 0x003D003C, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00010203, 0x04050607, 0x08090A0B, 0x0C0D000E, 0x0F101112, 0x13141516,
    0x17000000, 0x00000000, 0x00000000, 0x00000000, 0x00000100, 0x00000000,
    0x01000000, 0x01010101, 0x00000000, 0x00000000, 0x00010000, 0x00000101,
    0x00000000, 0x00000000, 0x01010000, 0x3F333333, 0x3F333333, 0x3F333333,
    0x3F333333, 0x3F333333, 0x3F333333, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD,
    0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3E800000, 0x3ECCCCCD, 0x3ECCCCCD,
    0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD,
    0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD,
    0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD,
    0x3E800000, 0x3E99999A, 0x3E99999A, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD,
    0x3E99999A, 0x3E99999A, 0x3E99999A, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD,
    0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD,
    0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD,
    0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD,
    0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD,
    0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD,
    0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD,
    0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD,
    0x3E4CCCCD, 0x3E4CCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD,
    0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD,
    0x3ECCCCCD, 0x3ECCCCCD, 0x3ECCCCCD,
};

ModelFileEntry lbl_2_data_241C[54] = {
    { 0x0000040B, 0x4003C4B8, 0x0EAF7000, 0x000265A8 },
    { 0x0000040B, 0x400431B4, 0x0EB1D800, 0x0002B22C },
    { 0x0000040B, 0x400396A0, 0x0EB49000, 0x00026ED4 },
    { 0x0000040B, 0x4003ED8C, 0x0EB70000, 0x00028C4C },
    { 0x0000040B, 0x40036944, 0x0EB99000, 0x00022DF4 },
    { 0x0000040B, 0x40039B44, 0x0EBBC000, 0x00026618 },
    { 0x0000040B, 0x400320E4, 0x0EBE2800, 0x00021E2C },
    { 0x0000040B, 0x40030878, 0x0EC04800, 0x0001DD80 },
    { 0x0000040B, 0x4002D3C4, 0x0EC22800, 0x0001B3EC },
    { 0x0000040B, 0x40035258, 0x0EC3E000, 0x000238DC },
    { 0x0000040B, 0x40041ED0, 0x0EC62000, 0x00029B84 },
    { 0x0000040B, 0x400414AC, 0x0EC8C000, 0x0002D160 },
    { 0x0000040B, 0x4002E988, 0x0ECB9800, 0x0001E0BC },
    { 0x0000040B, 0x4002FED0, 0x0ECD8000, 0x0001C398 },
    { 0x0000040B, 0x4001FF28, 0x0ECF4800, 0x00015000 },
    { 0x0000040B, 0x40032CF4, 0x0ED09800, 0x0001F4E4 },
    { 0x0000040B, 0x40021EF4, 0x0ED29000, 0x00015114 },
    { 0x0000040B, 0x40038998, 0x0ED3E800, 0x00023948 },
    { 0x0000040B, 0x4001CE38, 0x0ED62800, 0x00011B30 },
    { 0x0000040B, 0x40032FDC, 0x0ED74800, 0x00021154 },
    { 0x0000040B, 0x4002ED24, 0x0ED96000, 0x0001E94C },
    { 0x0000040B, 0x40031490, 0x0EDB5000, 0x0001F824 },
    { 0x0000040B, 0x40030370, 0x0EDD5000, 0x0001EB70 },
    { 0x0000040B, 0x40030370, 0x0EDF4000, 0x0001EB70 },
    { 0x0000040B, 0x400246C0, 0x0EE13000, 0x00016D78 },
    { 0x0000040B, 0x400244FC, 0x0EE2A000, 0x00016C4C },
    { 0x0000040B, 0x400244FC, 0x0EE41000, 0x00016C78 },
    { 0x0000040B, 0x40032428, 0x0EE58000, 0x0001F020 },
    { 0x0000040B, 0x40036CD8, 0x0EE77800, 0x00023828 },
    { 0x0000040B, 0x40029590, 0x0EE9B800, 0x000196B4 },
    { 0x0000040B, 0x40029590, 0x0EEB5000, 0x00019400 },
    { 0x0000040B, 0x40029590, 0x0EECE800, 0x00019304 },
    { 0x0000040B, 0x40029590, 0x0EEE8000, 0x00019310 },
    { 0x0000040B, 0x4002F524, 0x0EF01800, 0x0001E128 },
    { 0x0000040B, 0x4002F520, 0x0EF20000, 0x0001E100 },
    { 0x0000040B, 0x4002F520, 0x0EF3E800, 0x0001E0E4 },
    { 0x0000040B, 0x4002F520, 0x0EF5D000, 0x0001E210 },
    { 0x0000040B, 0x40024A18, 0x0EF7B800, 0x00016A9C },
    { 0x0000040B, 0x40025E78, 0x0EF92800, 0x00019A98 },
    { 0x0000040B, 0x4003B93C, 0x0EFAC800, 0x00027A9C },
    { 0x0000040B, 0x40016318, 0x0EFD4800, 0x0000F7B8 },
    { 0x0000040B, 0x4001BF1C, 0x0EFE4000, 0x00012754 },
    { 0x0000040B, 0x40035468, 0x0EFF6800, 0x00023CE4 },
    { 0x0000040B, 0x400357E0, 0x0F01A800, 0x00024580 },
    { 0x0000040B, 0x40021C78, 0x0F03F000, 0x00015000 },
    { 0x0000040B, 0x4001E814, 0x0F054000, 0x00012450 },
    { 0x0000040B, 0x4001E814, 0x0F066800, 0x00012484 },
    { 0x0000040B, 0x4001E814, 0x0F079000, 0x00012468 },
    { 0x0000040B, 0x40029748, 0x0F08B800, 0x0001ABF4 },
    { 0x0000040B, 0x400296E8, 0x0F0A6800, 0x0001AB78 },
    { 0x0000040B, 0x4002A908, 0x0F0C1800, 0x0001BABC },
    { 0x0000040B, 0x400296E8, 0x0F0DD800, 0x0001AB4C },
    { 0x0000040B, 0x4002A7E8, 0x0F0F8800, 0x00019ACC },
    { 0x0000040B, 0x4002A0E8, 0x0F112800, 0x0001981C },
};

ModelFileEntry *lbl_2_data_277C = CharacterHandFiles;
ModelFileEntry *lbl_2_data_2780[3] = { HandPoseEventSetFiles, (ModelFileEntry *)1, (ModelFileEntry *)1 };
s32 lbl_2_data_278C[2] = { 0x0506090B, 0x07080A0C };
u8 lbl_2_data_2794[4] = { 0, 1, 2, 0 };
extern int menuCursors[0x16];
extern menuControlStruct *menuControlVariables;
extern u8 superstarUnlocked[0x130];
extern u8 challengeCaptainCharIDArray[12];

typedef struct {
    /* 0x00 */ u8 _pad0[0x59];
    /* 0x59 */ u8 portCaptainSlot[4];
    /* 0x5D */ u8 _pad1[0x64 - 0x5D];
} CapGameSetUp; // size: 0x64

extern CapGameSetUp gameSetUpStep;

void *getAnimObjectActor(void *obj);
void fn_800B2C08(void *actor, u16 arg1);
void fn_800B2BA8(void *actor, u16 boneIdx, s32 arg2, s32 arg3);
void fn_800126EC(void *buf, void *tex, s32 *arg);
void fn_80014990(s32 idx, void *file0, void *file1);
void fn_800638B4(void *slot, void *entry);
void fn_8004B7B4(void *slot, void *entry);
void fn_80014204(s32 count);
void *fn_80023AA4(void);

void fn_2_1937C(ActorObjectTable *table, Mtx cam);
void fn_2_19224(ActorObjectTable *table);
void fn_2_190DC(ActorObjectTable *table);
void fn_2_17C88(void);
void fn_2_17AB8(void);
void fn_2_17648(void);
void fn_2_16F0C(u8 idx);
void fn_2_16D38(void);
void fn_2_190B8(ActorObjectEntry *entry);
void fn_2_18398(void);
void fn_2_18748(void);
void fn_2_188EC(void);
BOOL fn_2_18650(int port);
void fn_2_18148(CapLoadTask *task);
void fn_2_17ED8(void);
void fn_2_16F78(u8 idx);
void fn_2_16DA8(void);
void fn_2_16CE0(void);
void fn_2_16A98(int idx, int anim, u8 loop, u8 val, s16 frameScale, int unused, u8 speedDiv);

#define STATE lbl_2_bss_100B8
#define SSTATE ((s8 *)lbl_2_bss_100B8)
#define TASK ((CapLoadTask *)currentDrawingItem)

// .text:0x0001937C size:0x140 mapped:0x80658410
void fn_2_1937C(ActorObjectTable *table, Mtx cam) {
    Mtx44 proj;
    u16 i;

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    for (i = 0; i < table->count; i++) {
        CapSlot *obj = hugeAnimStruct.objects[i];
        if (obj != NULL) {
            ActorObjectEntry *e = &table->entries[i];
            if (e->actor != NULL && e->applyControl != 0) {
                f32 w = obj->_34 / 1280.0f;
                f32 h = obj->_38 / 1280.0f;
                C_MTXFrustum(proj, -0.175f + h, 0.175f + h, 0.25f + w, -0.25f + w, 1.0f, 512.0f);
                GXSetProjection(proj, GX_PERSPECTIVE);
                sknRelated(e, cam);
            }
        }
    }
}

// .text:0x00019224 size:0x158 mapped:0x806582B8
void fn_2_19224(ActorObjectTable *table) {
    int i;

    for (i = 0; (u16)i < table->count; i++) {
        CapSlot *obj = hugeAnimStruct.objects[(u16)i];
        if (obj != NULL && obj->_25D != 0) {
            ActorObjectEntry *e = &table->entries[(u16)i];
            u8 bp;
            if (e->actor != NULL) {
                if (e->animPending != 0) {
                    ACTSetAnimation(e->actor, e->anim, NULL, e->seqNum, 0.0f, e->blendTime);
                }
                if (e->framePending != 0) {
                    setActorAnimFrame(e->actor, e->frame);
                }
                if (e->speedPending != 0) {
                    ACTSetSpeed(e->actor, e->speed);
                }
                bp = e->boneParam;
                if (bp & 2) {
                    updateBoneParam(e->actor, (u8)(bp & 1));
                }
                Set_FUN_800b2b6c((UnkB2B4C *)e->actor, e->unk68);
                if (e->applyControl != 0) {
                    fn_800BDA24(e);
                }
                e->actor->unk98 = 1;
                e->animPending = 0;
                e->framePending = 0;
                e->speedPending = 0;
                e->boneParam &= 1;
            }
        }
    }
}

// .text:0x000190DC size:0x148 mapped:0x80658170
void fn_2_190DC(ActorObjectTable *table) {
    int i;
    u16 idx;

    for (i = 0; (u16)i < table->count; i++) {
        idx = i;
        if (hugeAnimStruct.actorEntries + idx * 0x28 != NULL) {
            ActorObjectEntry *e = &table->entries[idx];
            u8 bp;
            if (e->actor != NULL) {
                if (e->animPending != 0) {
                    ACTSetAnimation(e->actor, e->anim, NULL, e->seqNum, 0.0f, e->blendTime);
                }
                if (e->framePending != 0) {
                    setActorAnimFrame(e->actor, e->frame);
                }
                if (e->speedPending != 0) {
                    ACTSetSpeed(e->actor, e->speed);
                }
                bp = e->boneParam;
                if (bp & 2) {
                    updateBoneParam(e->actor, (u8)(bp & 1));
                }
                Set_FUN_800b2b6c((UnkB2B4C *)e->actor, e->unk68);
                if (e->applyControl != 0) {
                    fn_800BDA24(e);
                }
                e->actor->unk98 = 1;
                e->animPending = 0;
                e->framePending = 0;
                e->speedPending = 0;
                e->boneParam &= 1;
            }
        }
    }
}

// .text:0x000190B8 size:0x24 mapped:0x8065814C
void fn_2_190B8(ActorObjectEntry *entry) {
    setLITLightPtr((void *)entry->drawArgs[0]);
}

// .text:0x00018FBC size:0xFC mapped:0x80658050
void captainSelectLoadScreen(void) {
    DrawingSceneStruct *task = insertGraphicDrawingFunction(fn_2_188EC, 0x6000);
    int i;

    STATE[0x19] = 0;
    STATE[0x1B] = 1;
    if (Static_Stats_Tables._4700[1] == 0) {
        for (i = 0; i < STATE[0x2D]; i++) {
            SSTATE[0x27 + i] = -1;
        }
        ((CapLoadTask *)task)->stage = 0;
    } else {
        for (i = 0; i < STATE[0x2D]; i++) {
            STATE[0x14 + i] = 0;
        }
        ((CapLoadTask *)task)->stage = 0;
    }
    STATE[0] = 0;
    STATE[1] = 0;
    if (SSTATE[0] < 10) {
        SSTATE[2] = -1;
        SSTATE[3] = -1;
        SSTATE[4] = -1;
        SSTATE[5] = -1;
        SSTATE[6] = -1;
        SSTATE[7] = -1;
        SSTATE[8] = -1;
        SSTATE[9] = -1;
        SSTATE[10] = -1;
        SSTATE[11] = -1;
    }
}

// .text:0x000188EC size:0x6D0 mapped:0x80657980
void fn_2_188EC(void) {
    CapLoadTask *task;
    int i;

    task = TASK;
    hugeAnimStruct._307A = 0;
    hugeAnimStruct._307C = 0;
    switch (task->stage) {
    case 0:
        fn_2_166CC();
        captainSelect_setupCameraProjection();
        fn_2_17ED8();
        fn_2_16DA8();
        task->stage++;
        break;
    case 1: {
        CapLoadTask *t = (CapLoadTask *)insertGraphicDrawingFunction(fn_2_18748, 0);
        t->step = 0;
        t->_1F = 0;
        t->index = 0;
        task->stage++;
        break;
    }
    case 2:
        if (lbl_2_bss_100B4 != 0) {
            for (i = 0; i < STATE[0x2D]; i++) {
                if (STATE[0x40 + i] == 0) {
                    goto notDone;
                }
            }
            for (i = 0; i < STATE[0x2D]; i++) {
                hugeAnimStruct.objects[i] = NULL;
            }
            removeCurrentDrawingItem();
            break;
        }
    notDone:
        if (STATE[0x19] != 0) {
            for (i = 0; i < STATE[0x2D]; i++) {
                if (STATE[0x14 + i] != 0) {
                    if (fn_2_18650(i)) {
                        STATE[0x14 + i] = 0;
                    }
                }
            }
            hugeAnimStruct._307A = 5;
            hugeAnimStruct._307C = 1;
            fn_2_16460();
            PSMTXCopy((f32(*)[4])lbl_2_bss_1010C, fn_80052768_getCamera(0)->view);
            fn_2_16CE0();
        }
        break;
    }
}

// .text:0x00018748 size:0x1A4 mapped:0x806577DC
void fn_2_18748(void) {
    CapLoadTask *task = TASK;
    int i;

    switch (task->step) {
    case 0:
        for (i = 0; i < STATE[0x2D]; i++) {
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
                task->charIDs[i] = challengeCaptainCharIDArray[superstarUnlocked[0xF4] * 6 + menuCursors[4 + task->index]];
            } else {
                task->charIDs[i] = mapCaptainCursorPositionToCharID[menuCursors[4 + task->index]];
            }
            if (task->index == 2) {
                task->index = 0;
            }
        }
        task->_10 = 0;
        task->loadStep = 0;
        task->step++;
    case 1:
        fn_2_18148(task);
        if (STATE[0x18] != 0) {
            STATE[0x18] = 0;
            STATE[0x32] = 0;
            task->loadStep = 0;
            task->_10 = 0;
            task->index++;
            if (task->index >= STATE[0x2D]) {
                task->index = 0;
                task->step = 0;
                STATE[0x19] = 1;
                removeCurrentDrawingItem();
            } else {
                task->step = 0;
            }
        } else if (lbl_2_bss_100B4 != 0) {
            task->index = 0;
            task->step = 0;
            removeCurrentDrawingItem();
        }
        break;
    }
}

// .text:0x00018650 size:0xF8 mapped:0x806576E4
BOOL fn_2_18650(int port) {
    int head = ((s8)STATE[0] + 1) % 10;

    if (head != (s8)STATE[1]) {
        if (lbl_2_bss_1224 == NULL) {
            if ((lbl_2_bss_1224 = (CapLoadTask *)insertGraphicDrawingFunction(fn_2_18398, 0xFFFF)) != NULL) {
                lbl_2_bss_1224->stage = 0;
                lbl_2_bss_1224->step = 0;
            } else {
                return FALSE;
            }
        }
        STATE[2 + (s8)STATE[0]] = port;
        STATE[0] = head;
        STATE[0x42 + port] = 1;
        return TRUE;
    }
    return FALSE;
}

// .text:0x00018398 size:0x2B8 mapped:0x8065742C
void fn_2_18398(void) {
    CapLoadTask *task = TASK;
    u8 mode;
    u8 gameMode;

    switch (task->step) {
    case 0: {
        s8 *queue = &SSTATE[2];
        u8 port = queue[(s8)STATE[1]];
        if ((s8)port == -1) {
            STATE[0x18] = 0;
            STATE[0x1B] = 1;
            STATE[0x1A] = 0;
            STATE[0x32] = 0;
            lbl_2_bss_1224 = NULL;
            removeCurrentDrawingItem();
            break;
        }
        task->index = port;
        queue[(s8)STATE[1]] = -1;
        STATE[0x1A] = 1;
        STATE[0x1B] = 0;
        STATE[1] = ((s8)STATE[1] + 1) % 10;
        STATE[0x27 + task->index] = task->index;
        task->step = 1;
        task->_10 = 0;
        mode = Static_Stats_Tables._4744[0x11];
        gameMode = g_d_GameSettings.GameModeSelected;
        if (mode == 0) {
            if (gameMode == GAME_TYPE_CHALLENGE) {
                task->charIDs[task->index] = challengeCaptainCharIDArray[superstarUnlocked[0xF4] * 6 + menuCursors[4 + (u8)task->index]];
            } else {
                task->charIDs[task->index] = mapCaptainCursorPositionToCharID[menuCursors[4 + (u8)task->index]];
            }
            if (task->index == 2) {
                task->index = 0;
            }
        } else if (mode == 1) {
            int idx = task->index;

            switch (idx) {
            case 0:
            case 1:
                task->charIDs[idx] = inMemRoster[idx][menuCursors[12 + idx] - (idx * 11 + 2)].stats.CharID;
                break;
            case 2:
            case 3:
                task->charIDs[idx] = menuCursors[6 + idx];
                break;
            }
        }
    }
    case 1:
        fn_2_18148(task);
        if (lbl_2_bss_100B4 != 0 && ((u8 *)&lbl_2_bss_100B4)[1] == 0) {
            lbl_2_bss_1224 = NULL;
            STATE[0x18] = 0;
            STATE[0x1B] = 1;
            STATE[0x1A] = 0;
            STATE[0x32] = 0;
            task->step = 0;
            removeCurrentDrawingItem();
        } else if (STATE[0x18] != 0) {
            STATE[0x18] = 0;
            STATE[0x1A] = 0;
            task->step = 0;
        }
        break;
    }
}

// .text:0x00018148 size:0x250 mapped:0x806571DC
void fn_2_18148(CapLoadTask *task) {
    switch (task->loadStep) {
    case 0:
        task->slot = &hugeAnimStruct.slots[task->index];
        task->slot->charID = task->charIDs[task->index];
        task->_20 = STATE[0x46 + task->index];
        hugeAnimStruct.slots[task->index]._25D = 0;
        task->slot->_68 = -1;
        ((u8 *)&lbl_2_bss_100B4)[1] = 1;
        task->loadStep++;
        break;
    case 1:
        ARAMTransfer(&lbl_2_data_241C[(s8)task->charIDs[task->index]], (s32)task->slot->files, 0, 0);
        task->loadStep++;
        break;
    case 2:
        if (lbl_803C6CF8.cancel.bytes[1] == TRUE) {
            u8 cpuCode;

            fn_2_16F78(task->index);
            cpuCode = g_d_GameSettings.p2_CPU_match_code;
            if (cpuCode == P2_CPU_CODE_1_PLAYER_GAME && gameSetUpStep.portCaptainSlot[0] == 0 && task->index == 1) {
                hugeAnimStruct.slots[task->index]._25D = 0;
            } else {
                hugeAnimStruct.slots[task->index]._25D = task->_20 != 0;
            }
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE || cpuCode != 0 ||
                menuControlVariables->previousScreen == 5) {
                fn_2_14BB8(task->index, 1);
            } else if (STATE[0x10] != 0) {
                fn_2_14BB8(task->index, task->index != 0);
            }
            task->loadStep = 0;
            STATE[0x32] = 1;
            STATE[0x18] = 1;
            ((u8 *)&lbl_2_bss_100B4)[1] = 0;
            STATE[0x42 + task->index] = 0;
        }
        break;
    }
}

// .text:0x00017ED8 size:0x270 mapped:0x80656F6C
void fn_2_17ED8(void) {
    int t, j, i;
    u32 maxSize = 0;
    u32 size;

    for (t = 0; t < 12; t++) {
        for (j = 0; j < 9; j++) {
            u32 sz;
            if (t * 9 + j == CHAR_ID_MAX) {
                goto done;
            }
            sz = lbl_2_data_241C[Static_Stats_Tables.characterStats[t][j].stats.CharID].sizeFlags & 0x0FFFFFFF;
            if (maxSize < sz) {
                maxSize = sz;
            }
        }
    }
done:
    size = (maxSize + 31) & ~31;
    hugeAnimStruct.modelPool = _OSAllocFromHeap(32, size * STATE[0x2D]);
    for (i = 0; i < STATE[0x2D]; i++) {
        hugeAnimStruct.slots[i].files = (u32 *)(hugeAnimStruct.modelPool + size * i);
    }
    fn_80014204(STATE[0x2D]);
    hugeAnimStruct._13C = fn_80023AA4();
    initActorArray(4);
}

// .text:0x00017C88 size:0x250 mapped:0x80656D1C
void fn_2_17C88(void) {
    int t, j, i;
    u32 maxSize = 0;
    u32 size;

    for (t = 0; t < 12; t++) {
        for (j = 0; j < 9; j++) {
            u32 sz;
            if (t * 9 + j == CHAR_ID_MAX) {
                goto done;
            }
            sz = lbl_2_data_241C[Static_Stats_Tables.characterStats[t][j].stats.CharID].sizeFlags & 0x0FFFFFFF;
            if (maxSize < sz) {
                maxSize = sz;
            }
        }
    }
done:
    size = (maxSize + 31) & ~31;
    hugeAnimStruct.modelPool = _OSAllocFromHeap(32, size * STATE[0x2D]);
    for (i = 0; i < STATE[0x2D]; i++) {
        hugeAnimStruct.slots[i].files = (u32 *)(hugeAnimStruct.modelPool + size * i);
    }
}

// .text:0x00017AB8 size:0x1D0 mapped:0x80656B4C
void fn_2_17AB8(void) {
    int size = ((lbl_2_data_2780[0]->sizeFlags & 0x0FFFFFFF) + 31) & ~31;
    int i;

    lbl_2_bss_122C = _OSAllocFromHeap(32, size * STATE[0x2D]);
    for (i = 0; i < STATE[0x2D]; i++) {
        lbl_2_bss_101AC[i].buffer = lbl_2_bss_122C + size * i;
        lbl_2_bss_101AC[i]._61 = -1;
        lbl_2_bss_101AC[i].index = -1;
    }
}

// .text:0x00017648 size:0x470 mapped:0x806566DC
void fn_2_17648(void) {
    int t, j, k, i;
    u32 maxSize = 0;
    u32 size;

    for (t = 0; t < 12; t++) {
        for (j = 0; j < 9; j++) {
            if (t * 9 + j == CHAR_ID_MAX || j != 0) {
                goto done;
            }
            for (k = 0; k < 6; k++) {
                u32 sz = lbl_2_data_277C[Static_Stats_Tables.characterStats[t][j].stats.CharID + k].sizeFlags & 0x0FFFFFFF;
                if (maxSize < sz) {
                    maxSize = sz;
                }
            }
        }
    }
done:
    size = (maxSize + 31) & ~31;
    lbl_2_bss_1228 = _OSAllocFromHeap(32, size * STATE[0x2D] * 2);
    for (i = 0; i < STATE[0x2D]; i++) {
        hugeAnimStruct.entries[i].bufs[0].buffer = lbl_2_bss_1228 + size * (i * 2);
        hugeAnimStruct.entries[i].bufs[1].buffer = lbl_2_bss_1228 + size * (i * 2 + 1);
    }
    for (i = 0; i < STATE[0x2D]; i++) {
        CapEntry *e = &hugeAnimStruct.entries[i];
        e->_CF = -1;
        e->_D1 = -1;
        e->_D0 = -1;
        e->_CD = 0xFF;
        e->_C8 = 0;
        e->_CC = 0;
        e->bufs[0].index = i * 2;
        e->bufs[1].index = i * 2 + 1;
    }
}

static inline BOOL isSpecialHandChar(s8 id) {
    if (id == CHAR_ID_MONTY || id == CHAR_ID_PETEY || id == CHAR_ID_GOOMBA || id == CHAR_ID_PARAGOOMBA) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x00016F78 size:0x6D0 mapped:0x8065600C
void fn_2_16F78(u8 idx) {
    CapSlot *slot = &hugeAnimStruct.slots[idx];
    ActorObjectEntry *entry;
    ActorObjectEntry *e;
    u32 *base;
    void *tex;
    void *layout;
    void *geo;
    void *skn;
    void *anim;
    void *bank;
    void *file13;
    void *file14;
    VecXYZ *pos;
    CapEntry *capEntry;
    int k;
    int handL;
    int handR;
    int bones;
    int id;
    u16 boneID;
    u8 port;

    slot->entryIdx = idx;
    base = slot->files;
    for (k = 0; k < 15; k++) {
        if (slot->files[k] == 0) {
            break;
        }
        slot->files[k] = (u32)base + base[k];
    }
    tex = (void *)slot->files[0];
    layout = (void *)slot->files[1];
    geo = (void *)slot->files[2];
    skn = (void *)slot->files[3];
    convertTextureHeader(tex);
    LoadActorLayout(layout);
    convertGeometryAndSknHeader(geo, skn);
    haveActLayoutPointToGeoHeader(layout, geo);
    UpdateTexturePalettePointers(geo, tex);
    anim = slot->_10[5] = (void *)slot->files[4];
    ANIMGet(slot->_10[5]);
    entry = getAnimObjectActor(slot);
    characterAndBallDisplayRelated(entry, idx, idx, layout, anim, (int)skn);

    e = &hugeAnimStruct.objTable->entries[idx];
    bank = slot->_10[5];
    e->anim = bank;
    e->seqNum = 0;
    e->frame = 0.0f;
    e->animPending = 1;
    e->speedPending = e->framePending = bank != NULL;
    e->blendTime = 0.0f;
    bones = hugeAnimStruct.objTable->entries[idx].actor->totalBones;
    memset(slot->boneSlots, 0xFF, sizeof(slot->boneSlots));
    for (k = 0; k < bones; k++) {
        boneID = hugeAnimStruct.objTable->entries[idx].actor->boneArray[k]->boneID;
        if (boneID != BONE_SLOT_NONE) {
            slot->boneSlots[boneID] = k;
        }
    }
    fn_800BD548(&hugeAnimStruct.objTable->entries[idx], 4, hugeAnimStruct._AC[0], hugeAnimStruct._AC[1],
                hugeAnimStruct._AC[2], hugeAnimStruct._AC[3]);
    slot->_40 = slot->_44 = slot->_48 = 0.0f;
    CTRLSetTranslation(&hugeAnimStruct.objTable->entries[idx].control, 0.0f, 0.0f, 0.0f);
    CTRLSetRotation(&hugeAnimStruct.objTable->entries[idx].control, 0.0f, 0.0f, 0.0f);
    e = &hugeAnimStruct.objTable->entries[idx];
    e->speed = 0.5f;
    e->speedPending = 1;
    fn_800B2C08(hugeAnimStruct.objTable->entries[idx].actor,
                hugeAnimStruct.objects[idx] != NULL ? hugeAnimStruct.objects[idx]->boneSlots[4] : BONE_SLOT_NONE);
    initShortsHandleCompressedDiskReads((ShortsTableOwner *)hugeAnimStruct.objects[idx]);
    pos = (VecXYZ *)lbl_2_data_20F8[idx];
    slot->_34 = pos->x;
    slot->_38 = pos->y;
    slot->_3C = pos->z;
    slot->_4C = 0.5f;
    slot->_25D = 0;
    *(void (**)(void))((u8 *)hugeAnimStruct.objTable + (idx * 0x90 + 0x3C)) = (void (*)(void))fn_2_190B8;
    slot->actor = entry->actor;
    callDSInsertListObject((UnkB2B4C *)entry->actor, slot->boneSlots[19]);
    callDSInsertListObject((UnkB2B4C *)entry->actor, slot->boneSlots[25]);

    id = slot->boneSlots[3];
    if (id != BONE_SLOT_NONE) {
        fn_800B2B54(slot->actor, id, 13);
    }
    id = slot->boneSlots[3];
    if (id != BONE_SLOT_NONE) {
        fn_800B2BA8(entry->actor, id, 0, 0);
        *((u8 *)entry->actor->boneArray[(u16)id] + 0x136) = 1;
    }
    id = slot->boneSlots[2];
    if (id != BONE_SLOT_NONE) {
        fn_800B2BA8(entry->actor, id, 0, 0);
        *((u8 *)entry->actor->boneArray[(u16)id] + 0x136) = 1;
    }
    id = slot->boneSlots[1];
    if (id != BONE_SLOT_NONE) {
        fn_800B2BA8(entry->actor, id, 0, 0);
        *((u8 *)entry->actor->boneArray[(u16)id] + 0x136) = 1;
    }
    id = slot->boneSlots[36];
    if (id != BONE_SLOT_NONE) {
        fn_800B2BA8(entry->actor, id, 0, 0);
    }
    id = slot->boneSlots[46];
    if (id != BONE_SLOT_NONE) {
        fn_800B2BA8(entry->actor, id, 0, 0);
        *((u8 *)entry->actor->boneArray[(u16)id] + 0x136) = 1;
    }

    capEntry = &hugeAnimStruct.entries[slot->entryIdx];
    if (slot->files[5] != 0) {
        slot->entry = &hugeAnimStruct.entries[idx];
        capEntry->bufs[0].buffer = slot->files;
        fn_800126EC(capEntry, tex, &lbl_2_data_278C[0]);
        capEntry->bufs[1].buffer = slot->files;
        fn_800126EC(&capEntry->bufs[1], tex, &lbl_2_data_278C[1]);
    }

    if (isSpecialHandChar(slot->charID)) {
        switch (slot->charID) {
        case CHAR_ID_MONTY:
            handL = 4;
            handR = 5;
            break;
        case CHAR_ID_PETEY:
            handL = 2;
            handR = 3;
            break;
        case CHAR_ID_GOOMBA:
        case CHAR_ID_PARAGOOMBA:
            handL = 6;
            handR = 7;
            break;
        }
    } else {
        handL = 1;
        handR = 0;
    }
    port = idx;
    setHandModelAttached(port, handL, TRUE);
    setHandModelAttached(port, handR, TRUE);
    file13 = (void *)slot->files[13];
    if (file13 != NULL) {
        file14 = (void *)slot->files[14];
        if (file14 != NULL) {
            adjustInternalPointers(file13);
            fn_80014990(port, file13, file14);
            ACTActorRelated(file13, entry);
        }
    }
    slot->entry->_CC = 1;
    slot->entry->bufs[1].scale = 0.5f;
    slot->entry->bufs[0].scale = 0.5f;
    switch (slot->charID) {
    case CHAR_ID_DK:
        fn_800638B4(slot, entry);
        break;
    case CHAR_ID_BOWSERJR:
        slot->_25C = 1;
        fn_8004B7B4(slot, entry);
        break;
    }
    fn_2_16A98(port, 0, 1, 0, 0, 0, 0);
}

// .text:0x00016F0C size:0x6C mapped:0x80655FA0
void fn_2_16F0C(u8 idx) {
    CapSlot *slot = &hugeAnimStruct.slots[idx];
    u8 a = hugeAnimStruct.slots[idx].charID;
    u8 b = hugeAnimStruct.slots[idx]._254;

    if (hugeAnimStruct.entries[idx]._D0 == -1) {
        hugeAnimStruct.entries[idx]._CF = a;
        hugeAnimStruct.entries[idx]._D1 = hugeAnimStruct.entries[idx]._D0;
        hugeAnimStruct.entries[idx]._D0 = b;
        hugeAnimStruct.entries[idx]._CD = slot->_265;
    }
    slot->entry = &hugeAnimStruct.entries[idx];
}

// .text:0x00016DA8 size:0x164 mapped:0x80655E3C
void fn_2_16DA8(void) {
    int i;
    u8 *p;

    hugeAnimStruct.actorCount = 0;
    for (i = 0; i < STATE[0x2D]; i++) {
        hugeAnimStruct.objects[i] = &hugeAnimStruct.slots[i];
    }
    i = 3;
    p = STATE + 3;
    do {
        p[0x42] = 0;
        p--;
    } while (i-- != 0);
    if (menuControlVariables->previousScreen == 5 || g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        STATE[0x46] = 1;
        STATE[0x47] = 0;
    } else {
        STATE[0x46] = 1;
        STATE[0x47] = 1;
    }
}

// .text:0x00016D38 size:0x70 mapped:0x80655DCC
void fn_2_16D38(void) {
    int i;

    for (i = 0; i < STATE[0x2D]; i++) {
        memset(hugeAnimStruct.slots[i].files, 0, 0x5C);
    }
}

// .text:0x00016CE0 size:0x58 mapped:0x80655D74
void fn_2_16CE0(void) {
    int i;

    for (i = 0; i < STATE[0x2D]; i++) {
        if (hugeAnimStruct.objects[i] != NULL && hugeAnimStruct.objects[i]->_62 == 0x6B) {
            STATE[0x40 + i] = 1;
        }
    }
}

// .text:0x00016A98 size:0x248 mapped:0x80655B2C
void fn_2_16A98(int idx, int anim, u8 loop, u8 val, s16 frameScale, int unused, u8 speedDiv) {
    CapSlot *obj;
    ActorObjectEntry *e;
    f32 speed = 0.0f;
    int boneKind;
    int animIdx;
    u8 seq;

    obj = hugeAnimStruct.objects[idx];
    if (obj != NULL) {
        e = getAnimObjectActor(obj);
        if (speedDiv != 0) {
            speed = 1.0f / speedDiv;
        }
        if (obj->_26C == 0) {
            fn_800B2B54(obj->actor,
                        hugeAnimStruct.objects[idx] != NULL ? hugeAnimStruct.objects[idx]->boneSlots[4] : BONE_SLOT_NONE, 13);
        } else {
            fn_800B2B54(obj->actor,
                        hugeAnimStruct.objects[idx] != NULL ? hugeAnimStruct.objects[idx]->boneSlots[4] : BONE_SLOT_NONE, 1);
        }
        if (anim < 3) {
            boneKind = 5;
            animIdx = anim;
        }
        seq = lbl_2_data_2794[animIdx];
        if (obj->_2C != NULL) {
            actorRelated(obj->_2C + 4, 5, seq);
        }
        if (obj->entry != NULL && obj->entry->_CC != 0) {
            actorRelated((u8 *)obj->entry + 0x68, 5, seq);
            actorRelated((u8 *)obj->entry + 4, 5, seq);
        }
        if (idx < STATE[0x2D]) {
            void *bank = obj->_10[boneKind];
            if (bank != NULL) {
                if (animIdx >= *(u16 *)((u8 *)bank + 0xA)) {
                    return;
                }
                e->anim = bank;
                e->seqNum = animIdx;
                e->frame = 0.0f;
                e->animPending = 1;
                e->framePending = bank != NULL;
                e->speedPending = bank != NULL;
                e->blendTime = speed;
            }
        }
        if (loop != 0) {
            e->boneParam = 3;
        } else {
            e->boneParam = 2;
        }
        e->frame = frameScale * obj->_4C;
        e->framePending = 1;
        obj->_268 = val;
    }
}
