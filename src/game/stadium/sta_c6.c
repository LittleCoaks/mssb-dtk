#include "game/stadium/sta_c6.h"
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
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x800b4b38.h"
#include "Unknown/File_0x800b4bc8.h"
#include "Unknown/File_0x8005268c.h"
#include "Unknown/File_0x80052734.h"
#include "Unknown/File_0x800bda94.h"
#include "musyx/musyx.h"
#include "Dolphin/pad.h"
#include "Unknown/File_0x800bdc88.h"
#include "Unknown/File_0x800bdd74.h"
#include "Unknown/File_0x800acf14.h"
#include "game/sound/m_sound.h"

// A display-list colour attribute: `formatBits >> 4` is the GXCompType colour format.
typedef struct _ToyColorAttr {
    /*0x00*/ void* data;
    /*0x04*/ u8 _04[2];
    /*0x06*/ u8 formatBits;
} ToyColorAttr;

typedef struct _ToyColorRef {
    /*0x00*/ u8 _00[4];
    /*0x04*/ ToyColorAttr* attr;
} ToyColorRef;

typedef struct _ToyTevSetting {
    /*0x00*/ u8 _00[0xA0];
    /*0xA0*/ s16 mode;
} ToyTevSetting;

typedef struct _ToyDisplayState {
    /*0x00*/ u8 _00[0xC];
    /*0x0C*/ ToyTevSetting* tev;
} ToyDisplayState;

typedef struct _ToyDisplayKind {
    /*0x00*/ u8 _00[0x20];
    /*0x20*/ u8 type;
} ToyDisplayKind;

typedef struct _ToyDisplayRef {
    /*0x00*/ u8 _00[4];
    /*0x04*/ ToyDisplayKind* kind;
} ToyDisplayRef;

#define TOY_DISPLAY_TEV 3

typedef struct _ToyDisplayObj {
    /*0x00*/ u8 _00[4];
    /*0x04*/ ToyColorAttr* color;
    /*0x08*/ ToyDisplayState* state;
    /*0x0C*/ u8 _0C[4];
    /*0x10*/ ToyDisplayRef* ref;
    /*0x14*/ u8 _14[4];
    /*0x18*/ Mtx mtx;
} ToyDisplayObj;

typedef struct _ToyActorNode {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ ToyDisplayObj* dispObj;
    /*0x18*/ ToyDisplayObj* altDispObj;
    /*0x1C*/ Control ctrl;
    /*0x..*/ u8 _pad[0xEC - 0x1C - sizeof(Control)];
    /*0xEC*/ MtxPtr worldMtx;
} ToyActorNode;

typedef struct _ToyActorRoot {
    /*0x00*/ u8 _00[6];
    /*0x06*/ u16 nodeCount;
    /*0x08*/ u8 _08[0x10];
    /*0x18*/ ToyActorNode** nodes;
    /*0x1C*/ u8 _1C[0x98 - 0x1C];
    /*0x98*/ u8 drawFlags;
} ToyActorRoot;

// An ACT actor as the stadium objects hold it (compare ACTActor).
typedef struct _ToyModel {
    /*0x00*/ ToyActorRoot* root;
    /*0x04*/ u8 _04[0xC];
    /*0x10*/ u8 ctrl[0x44];
    /*0x54*/ f32 animSpeed;
} ToyModel;

// Local control block with the size of a whole per-object control (0x44).
typedef struct _ToyObjControl {
    Control ctrl;
    u8 _34[0x44 - sizeof(Control)];
} ToyObjControl;

typedef struct _ToyPlacement {
    /*0x00*/ Vec pos;
    /*0x0C*/ f32 rotY;
    /*0x10*/ u8 type;
    /*0x11*/ u8 _11;
    /*0x12*/ u8 group;
    /*0x13*/ u8 _13;
} ToyPlacement; // size: 0x14

typedef struct _ToyHomeType {
    /*0x00*/ u8 type;
    /*0x01*/ u8 _01;
    /*0x02*/ u8 group;
    /*0x03*/ u8 _03;
} ToyHomeType;

#define TOY_LAYOUT_SLOTS 16
#define TOY_HOME_SLOTS 8
#define TOY_OBJ_END 0x1B

// Per-state colours (miss, base, hit), then one placement layout and one home-type
// table per participant count (2, 3, 4) plus a fourth used when _19A6 > 1.
typedef struct _ToyFieldData {
    /*0x000*/ u8 colors[9][3][4];
    /*0x06C*/ ToyPlacement layouts[4][TOY_LAYOUT_SLOTS];
    /*0x56C*/ ToyHomeType homeTypes[4][TOY_HOME_SLOTS];
} ToyFieldData; // size: 0x5EC

// Toy Field view of a stadiumObjectCollision.objects[] entry.
typedef struct _ToyFieldObj {
    /*0x00*/ u8 _00[0x74];
    /*0x74*/ ToyModel* model;
    /*0x78*/ u8 _78[0x9C - 0x78];
    /*0x9C*/ ToyModel* extraModel;
    /*0xA0*/ s32 _A0;
    /*0xA4*/ u8 color[4];
    /*0xA8*/ u8* colorTo;
    /*0xAC*/ u8* colorFrom;
    /*0xB0*/ u8* hitColor;
    /*0xB4*/ u8* baseColor;
    /*0xB8*/ u8* missColor;
    /*0xBC*/ u8* bodyColor;
    /*0xC0*/ u8 slot;
    /*0xC1*/ u8 state;
    /*0xC2*/ u8 showMarker;
    /*0xC3*/ u8 homeIndex;
    /*0xC4*/ u8 prop;
} ToyFieldObj;

#define TOY_STATE_HOME 8
#define TOY_ANIM_TABLE (*(u8**)(hugeAnimStruct + 0x6C))
#define TOY_PROP_SLOT 16
#define TOY_PROP_COUNT 7

// One 0x90-byte entry of the stadium animation table.
typedef struct _ToyAnimSlot {
    /*0x00*/ u8 _00[0x34];
    /*0x34*/ ACTActor act;
    /*0xA4*/ u8 _A4[0x90 - 0x34 - sizeof(ACTActor)];
} ToyAnimSlot;

extern u8 hugeAnimStruct[0x3154];

extern void fn_800BDA24(void* arg);
extern void fn_800BD478(void* actor, void* file);
extern u8 lbl_80366158[0x30];
#define PauseSimulation lbl_80366158[0x28]
extern u16 stadiumHazardSoundIDs[16];
extern u8 stadiumHazardSoundFxRelated[0xB4];
extern u8 lbl_3_data_84B8[0x3C];

static u8 lbl_3_data_19018[3][4] = {{0xBE, 0x00, 0x00, 0xFF}, {0xC8, 0x76, 0x00, 0xFF}, {0x00, 0xA0, 0x00, 0xFF}};
static ToyFieldData lbl_3_data_19024 = {
    {
        {{0x05, 0x48, 0x00, 0xFF}, {0x0D, 0xB4, 0x00, 0xFF}, {0x12, 0xFA, 0x00, 0xFF}},
        {{0x05, 0x48, 0x00, 0xFF}, {0x0D, 0xB4, 0x00, 0xFF}, {0x12, 0xFA, 0x00, 0xFF}},
        {{0x58, 0x58, 0x58, 0xFF}, {0xC8, 0xC8, 0xC8, 0xC8}, {0xFF, 0xFF, 0xFF, 0xFF}},
        {{0x08, 0x20, 0x6C, 0xFF}, {0x0C, 0x38, 0xC8, 0xFF}, {0x0F, 0x47, 0xFF, 0xFF}},
        {{0x5E, 0x00, 0x00, 0xFF}, {0xDC, 0x00, 0x00, 0xFF}, {0xFF, 0x19, 0x19, 0xFF}},
        {{0x5E, 0x1B, 0x00, 0xFF}, {0xDC, 0x3E, 0x00, 0xFF}, {0xFF, 0x4C, 0x05, 0xFF}},
        {{0x5A, 0x3B, 0x00, 0xFF}, {0xDC, 0x91, 0x00, 0xFF}, {0xFF, 0xB1, 0x19, 0xFF}},
        {{0x46, 0x45, 0x00, 0xFF}, {0xD2, 0xD0, 0x00, 0xFF}, {0xFF, 0xFC, 0x19, 0xFF}},
        {{0x58, 0x58, 0x58, 0xFF}, {0xC8, 0xC8, 0xC8, 0xFF}, {0xFF, 0xFF, 0xFF, 0xFF}},
    },
    {
        {
            {{17.6f, 0.11f, 36.0f}, 40.0f, 4, 1, 1, 4},
            {{0.0f, 0.11f, 52.4f}, 0.0f, 4, 1, 1, 4},
            {{-17.6f, 0.11f, 36.0f}, -40.0f, 4, 1, 1, 4},
            {{34.6f, 0.11f, 53.0f}, 40.0f, 2, 1, 1, 2},
            {{19.4f, 0.11f, 70.0f}, 25.0f, 0, 1, 1, 0},
            {{0.0f, 0.11f, 76.2f}, 0.0f, 5, 1, 1, 5},
            {{-19.4f, 0.11f, 70.0f}, -25.0f, 0, 1, 1, 0},
            {{-34.6f, 0.11f, 53.0f}, -40.0f, 2, 1, 1, 2},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 27, 0, 255, 27},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
        },
        {
            {{17.6f, 0.11f, 36.0f}, 40.0f, 2, 1, 1, 2},
            {{0.0f, 0.11f, 52.4f}, 0.0f, 2, 1, 1, 2},
            {{-17.6f, 0.11f, 36.0f}, -40.0f, 2, 1, 1, 2},
            {{34.6f, 0.11f, 53.0f}, 40.0f, 5, 1, 1, 5},
            {{19.4f, 0.11f, 70.0f}, 25.0f, 0, 1, 1, 0},
            {{0.0f, 0.11f, 76.2f}, 0.0f, 5, 1, 1, 5},
            {{-19.4f, 0.11f, 70.0f}, -25.0f, 0, 1, 1, 0},
            {{-34.6f, 0.11f, 53.0f}, -40.0f, 5, 1, 1, 5},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 27, 0, 255, 27},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
        },
        {
            {{17.6f, 0.11f, 36.0f}, 40.0f, 4, 1, 1, 4},
            {{0.0f, 0.11f, 52.4f}, 0.0f, 4, 1, 1, 4},
            {{-17.6f, 0.11f, 36.0f}, -40.0f, 4, 1, 1, 4},
            {{34.6f, 0.11f, 53.0f}, 40.0f, 2, 1, 1, 2},
            {{19.4f, 0.11f, 70.0f}, 25.0f, 0, 1, 1, 0},
            {{0.0f, 0.11f, 76.2f}, 0.0f, 5, 1, 1, 5},
            {{-19.4f, 0.11f, 70.0f}, -25.0f, 0, 1, 1, 0},
            {{-34.6f, 0.11f, 53.0f}, -40.0f, 2, 1, 1, 2},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 27, 0, 255, 27},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
        },
        {
            {{34.6f, 0.11f, 53.0f}, 40.0f, 7, 1, 1, 7},
            {{17.6f, 0.11f, 36.0f}, 40.0f, 7, 1, 1, 7},
            {{19.4f, 0.11f, 70.0f}, 25.0f, 7, 1, 1, 7},
            {{0.0f, 0.11f, 52.4f}, 0.0f, 7, 1, 1, 7},
            {{0.0f, 0.11f, 76.2f}, 0.0f, 7, 1, 1, 7},
            {{-19.4f, 0.11f, 70.0f}, -25.0f, 7, 1, 1, 7},
            {{-17.6f, 0.11f, 36.0f}, -40.0f, 7, 1, 1, 7},
            {{-34.6f, 0.11f, 53.0f}, -40.0f, 7, 1, 1, 7},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 27, 0, 255, 27},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
            {{0.0f, 0.0f, 0.0f}, 0.0f, 0, 0, 0, 0},
        },
    },
    {
        {{14, 1, 1, 14}, {13, 1, 1, 13}, {10, 1, 1, 10}, {15, 1, 1, 15}, {10, 1, 1, 10}, {13, 1, 1, 13}, {14, 1, 1, 14}, {27, 0, 255, 27}},
        {{10, 1, 1, 10}, {14, 1, 1, 14}, {10, 1, 1, 10}, {15, 1, 1, 15}, {10, 1, 1, 10}, {14, 1, 1, 14}, {10, 1, 1, 10}, {27, 0, 255, 27}},
        {{14, 1, 1, 14}, {13, 1, 1, 13}, {10, 1, 1, 10}, {15, 1, 1, 15}, {10, 1, 1, 10}, {13, 1, 1, 13}, {14, 1, 1, 14}, {27, 0, 255, 27}},
        {{15, 1, 1, 15}, {15, 1, 1, 15}, {15, 1, 1, 15}, {15, 1, 1, 15}, {15, 1, 1, 15}, {15, 1, 1, 15}, {15, 1, 1, 15}, {27, 0, 255, 27}},
    },
};
static u8 enumObjTypeInFile_ARRAY_807cac10[0x2F] = {
    0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x02, 0x02, 0x04, 0x02, 0x02, 0x04, 0x04, 0x06,
    0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
};
static s8 lbl_3_data_1963F = -1;
static s8 lbl_3_data_19640 = -1;
static u8 lbl_3_data_19641 = 0xFF;
static Vec lbl_3_data_19644[7] = {
    {48.443f, 0.1f, 66.104f},
    {35.956f, 0.1f, 80.987f},
    {19.132f, 0.1f, 90.701f},
    {0.0f, 0.1f, 94.074f},
    {-19.132f, 0.1f, 90.701f},
    {-35.956f, 0.1f, 80.987f},
    {-48.443f, 0.1f, 66.104f},
};
static f32 lbl_3_data_19698[7] = {60.0f, 40.0f, 20.0f, 0.0f, -20.0f, -40.0f, -60.0f};
static u8 lbl_3_data_196B4[7] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static Vec lbl_3_data_196BC[7] = {
    {-54.758f, 0.0f, 69.75f},
    {-40.643f, 0.0f, 86.573f},
    {-21.625f, 0.0f, 97.552f},
    {0.0f, 0.0f, 101.366f},
    {21.625f, 0.0f, 97.552f},
    {40.643f, 0.0f, 86.573f},
    {54.758f, 0.0f, 69.75f},
};
static f32 lbl_3_data_19710[7] = {-60.0f, -40.0f, -20.0f, 0.0f, 20.0f, 40.0f, 60.0f};
static u32 lbl_3_data_1972C[16] = {10, 9, 11, 2, 3, 4, 5, 6, 10, 9, 11, 2, 3, 4, 5, 6};
static u8 lbl_3_data_1976C = 1;

// .bss, declared in reverse address order (MWCC lays statics out backwards). Unnamed
// bytes are not referenced by the functions written so far.
static u8 lbl_3_bss_AEB8[0x28];
static ToyPlacement* toyPlacements;
static ToyHomeType* homeTypes;
static u8 layoutIndex;
static u8 firstHomeObj;
static u8 placedPropCount;
static u8 lbl_3_bss_AE8C[0x20];
static s32 roundCount;
static s32 resultFrames;
static u8 lbl_3_bss_AE80[4];
static u8 prevResult;
static u8 lastResult;
static u8 lbl_3_bss_AE7A;
static u8 lbl_3_bss_AE79;
static u8 lbl_3_bss_AE78;
static u8 lbl_3_bss_AE77;
static u8 lbl_3_bss_AE76;
static u8 lbl_3_bss_AE75;
static u8 lbl_3_bss_AE74;
static u8 lbl_3_bss_AE73;
static u8 lbl_3_bss_AE72;
static u8 lbl_3_bss_AE71;
static u8 lbl_3_bss_AE70;
static u8 lbl_3_bss_AE6F;
static u8 lbl_3_bss_AE6E;
static u8 lbl_3_bss_AE6D;
static u8 lbl_3_bss_AE6C;
static u8 lbl_3_bss_AE6B;
static u8 lbl_3_bss_AE6A;
static u8 lbl_3_bss_AE69;
static u8 lbl_3_bss_AE68;
static u8 lbl_3_bss_AE67;
static u8 lbl_3_bss_AE66;
static u8 lbl_3_bss_AE65;
static u8 lbl_3_bss_AE64;
static u8 lbl_3_bss_AE63;
static u8 lbl_3_bss_AE62;
static u8 lbl_3_bss_AE61;
static u8 lbl_3_bss_AE60;
static u8 lbl_3_bss_AE5F;
static u8 lbl_3_bss_AE5E;
static u8 lbl_3_bss_AE5D;
static u8 lbl_3_bss_AE5C;
static u8 lbl_3_bss_AE5B;
static u8 lbl_3_bss_AE5A;
static u8 lbl_3_bss_AE59;
static u8 lbl_3_bss_AE58;
static u8 lbl_3_bss_AE57;
static u8 lbl_3_bss_AE56;
static u8 lbl_3_bss_AE55;
static u8 lbl_3_bss_AE54;
static u8 lbl_3_bss_AE53;
static u8 hitAll;
static u8 lbl_3_bss_AE51;
static u8 lbl_3_bss_AE50;

// .text:0x000E587C size:0xA8 mapped:0x80724910
int fn_3_E587C(void) {
    int count = 0;
    int last;
    int i;

    for (i = 0; i < TOY_PROP_COUNT; i++) {
        if (lbl_3_data_196B4[i]) {
            last = i;
            count++;
        }
    }
    if (count != 1) {
        return -1;
    }
    return last;
}

// .text:0x000E5924 size:0x90 mapped:0x807249B8
BOOL fn_3_E5924(void) {
    int i;

    for (i = 0; i < TOY_PROP_COUNT; i++) {
        if (!lbl_3_data_196B4[i]) {
            break;
        }
    }
    if (i >= TOY_PROP_COUNT) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x000E59B4 size:0x68 mapped:0x80724A48
void fn_3_E59B4(StadiumObject* obj) {
    ACTActor* act = ((ACTActor*)obj->model)->actor;

    if (1.0f + fn_800B4C40(act) > 340.0f) {
        setActorAnimFrame(act, 20.0f);
    }
    AnimateActorBones(act);
}

// .text:0x000E5A1C size:0x68 mapped:0x80724AB0
void fn_3_E5A1C(StadiumObject* obj) {
    ACTActor* act = ((ACTActor*)obj->model)->actor;

    if (1.0f + fn_800B4C40(act) > 420.0f) {
        setActorAnimFrame(act, 60.0f);
    }
    AnimateActorBones(act);
}

// .text:0x000E5A84 size:0x238 mapped:0x80724B18
void fn_3_E5A84(ToyFieldObj* obj) {
    Mtx base;
    ToyObjControl ctrl;
    ToyActorNode* node;
    int i;

    PSMTXIdentity(base);
    ctrl.ctrl.type = 0;
    if (obj->state < TOY_STATE_HOME) {
        CTRLSetTranslation(&ctrl.ctrl, toyPlacements[obj->slot].pos.x, toyPlacements[obj->slot].pos.y,
                           toyPlacements[obj->slot].pos.z);
        CTRLSetRotation(&ctrl.ctrl, 0.0f, toyPlacements[obj->slot].rotY, 0.0f);
    } else {
        CTRLSetTranslation(&ctrl.ctrl, lbl_3_data_19644[obj->homeIndex].x, lbl_3_data_19644[obj->homeIndex].y,
                           lbl_3_data_19644[obj->homeIndex].z);
        CTRLSetRotation(&ctrl.ctrl, 0.0f, lbl_3_data_19698[obj->homeIndex], 0.0f);
    }
    CTRLBuildMatrix(&ctrl.ctrl, base);
    for (i = 0; i < obj->model->root->nodeCount; i++) {
        node = obj->model->root->nodes[i];
        CTRLBuildMatrix(&node->ctrl, node->worldMtx);
        PSMTXConcat(base, node->worldMtx, node->worldMtx);
        PSMTXCopy(node->worldMtx, node->dispObj->mtx);
    }
    if (obj->extraModel != NULL) {
        for (i = 0; i < obj->extraModel->root->nodeCount; i++) {
            node = obj->extraModel->root->nodes[i];
            CTRLBuildMatrix(&node->ctrl, node->worldMtx);
            PSMTXConcat(base, node->worldMtx, node->worldMtx);
            if (node->dispObj != NULL) {
                PSMTXCopy(node->worldMtx, node->dispObj->mtx);
            }
        }
        obj->extraModel->root->drawFlags =
            fn_800B3C04(0, (StadiumModelNode*)obj->extraModel->root, returnFloatFromModeIndex(returnsCurrentMode())->view);
    }
    obj->model->root->drawFlags =
        fn_800B3C04(0, (StadiumModelNode*)obj->model->root, returnFloatFromModeIndex(returnsCurrentMode())->view);
}

// .text:0x000E5CBC size:0x158 mapped:0x80724D50
void fn_3_E5CBC(ToyFieldObj* obj, f32 t) {
    u8* from = obj->colorFrom;
    u8* to = obj->colorTo;

    if (t > 1.0f) {
        t = 1.0f;
    } else if (t < 0.0f) {
        t = 0.0f;
    }
    obj->color[0] = (1.0f - t) * from[0] + t * to[0];
    obj->color[1] = (1.0f - t) * from[1] + t * to[1];
    obj->color[2] = (1.0f - t) * from[2] + t * to[2];
    obj->color[3] = (1.0f - t) * from[3] + t * to[3];
}

// .text:0x000E5E14 size:0x5C mapped:0x80724EA8
int fn_3_E5E14(ToyColorRef* ref) {
    switch ((u8)(ref->attr->formatBits >> 4)) {
    case GX_RGB565:
    case GX_RGBA4:
        return 2;
    case GX_RGBA8:
        return 4;
    case GX_RGB8:
    case GX_RGBX8:
    case GX_RGBA6:
        return 3;
    }
    return 0;
}

// .text:0x000E5E70 size:0x17C mapped:0x80724F04
void fn_3_E5E70(u8* out, u8 formatBits, void* src) {
    u8 format = formatBits >> 4;

    if (out == NULL || src == NULL) {
        return;
    }
    switch (format) {
    case GX_RGB565:
        out[0] = (*(u16*)src >> 8) & 0xF8;
        out[1] = (*(u16*)src >> 3) & 0xFC;
        out[2] = *(u16*)src << 3;
        out[3] = 0xFF;
        break;
    case GX_RGBA4:
        out[0] = (*(u16*)src >> 12) & 0xF;
        out[1] = (*(u16*)src >> 8) & 0xF;
        out[2] = (*(u16*)src >> 4) & 0xF;
        out[3] = *(u16*)src & 0xF;
        out[0] = out[0] | (out[0] << 4);
        out[1] = out[1] | (out[1] << 4);
        out[2] = out[2] | (out[2] << 4);
        out[3] = out[3] | (out[3] << 4);
        break;
    case GX_RGBA8:
        out[0] = *(u32*)src >> 24;
        out[1] = *(u32*)src >> 16;
        out[2] = *(u32*)src >> 8;
        out[3] = *(u32*)src;
        break;
    case GX_RGB8:
    case GX_RGBX8:
        out[0] = *(u32*)src >> 24;
        out[1] = *(u32*)src >> 16;
        out[2] = *(u32*)src >> 8;
        out[3] = 0xFF;
        break;
    case GX_RGBA6:
        out[0] = (*(u16*)src >> 16) & 0xFC;
        out[1] = (*(u16*)src >> 10) & 0xFC;
        out[2] = (*(u16*)src >> 4) & 0xFC;
        out[3] = *(u16*)src << 2;
        break;
    }
}

// .text:0x000E5FEC size:0x424 mapped:0x80725080
void fn_3_E5FEC(ToyFieldObj* obj) {
    ToyColorAttr* attr;
    void* dst;

    attr = obj->extraModel->root->nodes[1]->dispObj->color;
    dst = attr->data;
    switch ((u8)(attr->formatBits >> 4)) {
    case GX_RGB565:
        *(u16*)dst = ((u16)(obj->color[0] >> 3) & 0x1F) << 11;
        *(u16*)dst |= ((u16)(obj->color[1] >> 2) & 0x3F) << 5;
        *(u16*)dst |= (u16)(obj->color[2] >> 3) & 0x1F;
        DCStoreRange(dst, 2);
        break;
    case GX_RGBA4:
        *(u16*)dst = ((u16)(obj->color[0] >> 4) & 0xF) << 12;
        *(u16*)dst |= ((u16)(obj->color[1] >> 4) & 0xF) << 8;
        *(u16*)dst |= ((u16)(obj->color[2] >> 4) & 0xF) << 4;
        *(u16*)dst |= (u16)(obj->color[3] >> 4) & 0xF;
        DCStoreRange(dst, 2);
        break;
    case GX_RGBA8:
        memcpy(dst, obj->color, 4);
        DCStoreRange(dst, 4);
        break;
    case GX_RGB8:
    case GX_RGBX8:
        *(u32*)dst = obj->color[0] << 16;
        *(u32*)dst |= obj->color[1] << 8;
        *(u32*)dst |= obj->color[2];
        DCStoreRange(dst, 3);
        break;
    case GX_RGBA6:
        *(u32*)dst = (obj->color[0] & 0xFC) << 24;
        *(u32*)dst = (obj->color[1] & 0xFC) << 18;
        *(u32*)dst = (obj->color[2] & 0xFC) << 12;
        *(u32*)dst = (obj->color[3] & 0xFC) << 6;
        DCStoreRange(dst, 3);
        break;
    }
    if (lbl_3_data_1976C) {
        if (obj->showMarker) {
            obj->extraModel->root->nodes[2]->dispObj = obj->extraModel->root->nodes[2]->altDispObj;
        } else {
            obj->extraModel->root->nodes[2]->dispObj = NULL;
        }
    } else {
        obj->extraModel->root->nodes[2]->dispObj = NULL;
    }
    attr = obj->model->root->nodes[0]->dispObj->color;
    dst = attr->data;
    switch ((u8)(attr->formatBits >> 4)) {
    case GX_RGB565:
        *(u16*)dst = ((u16)(obj->bodyColor[0] >> 3) & 0x1F) << 11;
        *(u16*)dst |= ((u16)(obj->bodyColor[1] >> 2) & 0x3F) << 5;
        *(u16*)dst |= (u16)(obj->bodyColor[2] >> 3) & 0x1F;
        DCStoreRange(dst, 2);
        break;
    case GX_RGBA4:
        *(u16*)dst = ((u16)(obj->bodyColor[0] >> 4) & 0xF) << 12;
        *(u16*)dst |= ((u16)(obj->bodyColor[1] >> 4) & 0xF) << 8;
        *(u16*)dst |= ((u16)(obj->bodyColor[2] >> 4) & 0xF) << 4;
        *(u16*)dst |= (u16)(obj->bodyColor[3] >> 4) & 0xF;
        DCStoreRange(dst, 2);
        break;
    case GX_RGBA8:
        memcpy(dst, obj->bodyColor, 4);
        DCStoreRange(dst, 4);
        break;
    case GX_RGB8:
    case GX_RGBX8:
        *(u32*)dst = obj->bodyColor[0] << 16;
        *(u32*)dst |= obj->bodyColor[1] << 8;
        *(u32*)dst |= obj->bodyColor[2];
        DCStoreRange(dst, 3);
        break;
    case GX_RGBA6:
        *(u32*)dst = (obj->bodyColor[0] & 0xFC) << 24;
        *(u32*)dst = (obj->bodyColor[1] & 0xFC) << 18;
        *(u32*)dst = (obj->bodyColor[2] & 0xFC) << 12;
        *(u32*)dst = (obj->bodyColor[3] & 0xFC) << 6;
        DCStoreRange(dst, 3);
        break;
    }
}

// .text:0x000E6410 size:0x98 mapped:0x807254A4
void fn_3_E6410(ToyFieldObj* obj) {
    u8* candidates[2];
    u8** out = candidates;
    u8* color = lbl_3_data_19018[0];
    int i;

    for (i = 0; i < 3; i++, color += 4) {
        if (obj->colorFrom != color) {
            *out++ = color;
        }
    }
    obj->colorTo = candidates[rand() % 2];
}

// .text:0x000E64A8 size:0x80 mapped:0x8072553C
u8* fn_3_E64A8(void) {
    switch ((u8)(rand() % 3)) {
    case 0:
        return lbl_3_data_19018[0];
    case 1:
        return lbl_3_data_19018[1];
    default:
        return lbl_3_data_19018[2];
    }
}

// .text:0x000E6528 size:0x50 mapped:0x807255BC
void fn_3_E6528(ToyFieldObj* obj) {
    memcpy(obj->color, obj->baseColor, 4);
    obj->bodyColor = lbl_3_data_19024.colors[8][1];
    obj->showMarker = FALSE;
}

// .text:0x000E6578 size:0xC0 mapped:0x8072560C
void fn_3_E6578(ToyFieldObj* obj) {
    ToyDisplayObj* disp;
    ToyDisplayState* state;

    if (obj->extraModel != NULL) {
        disp = obj->extraModel->root->nodes[1]->dispObj;
        state = disp->state;
        if (disp->ref->kind->type != TOY_DISPLAY_TEV) {
            OSPanic("sta_c6.c", 0x713, "参照するディスプレイステートがTEV設定部分じゃないです\n");
        }
        if (obj->state == 2) {
            state->tev->mode = 1;
        } else if (obj->state == 10) {
            state->tev->mode = 0;
        } else {
            state->tev->mode = 4;
        }
    }
}

// .text:0x000E6638 size:0x4C mapped:0x807256CC
void fn_3_E6638(ToyFieldObj* obj) {
    obj->model->root->nodes[0]->dispObj = obj->model->root->nodes[0]->altDispObj;
    obj->model->root->nodes[1]->dispObj = obj->model->root->nodes[1]->altDispObj;
    obj->model->root->nodes[2]->dispObj = obj->model->root->nodes[2]->altDispObj;
}

// .text:0x000E6684 size:0x98 mapped:0x80725718
void fn_3_E6684(ToyFieldObj* obj) {
    ToyActorNode* node;
    int i;

    for (i = 0; i < 3; i++) {
        node = obj->model->root->nodes[i];
        if (lbl_3_bss_AE80[i + 1]) {
            node->dispObj = node->altDispObj;
        } else {
            node->dispObj = NULL;
        }
    }
}

// .text:0x000E671C size:0x7C mapped:0x807257B0
void fn_3_E671C(ToyFieldObj* obj) {
    ToyActorRoot* root = obj->model->root;
    int i;

    for (i = 0; i < 7; i++) {
        root->nodes[i]->dispObj = root->nodes[i]->altDispObj;
    }
}

// .text:0x000E6798 size:0x5C mapped:0x8072582C
void fn_3_E6798(ToyFieldObj* obj) {
    ToyActorRoot* root = obj->model->root;
    int i;

    for (i = 0; i < 7; i++) {
        if (lbl_3_data_196B4[i]) {
            root->nodes[i]->dispObj = root->nodes[i]->altDispObj;
        } else {
            root->nodes[i]->dispObj = NULL;
        }
    }
}

static inline void toyActSetFrame(ACTActor* act, f32 frame) {
    act->animFrame = frame;
    act->applyFrame = 1;
}

// .text:0x000E67F4 size:0xB4 mapped:0x80725888
void fn_3_E67F4(void) {
    u32 i;
    void* actor;

    for (i = 0; i < TOY_PROP_COUNT; i++) {
        lbl_3_data_196B4[i] = 0;
        actor = ((ToyAnimSlot*)TOY_ANIM_TABLE)[TOY_PROP_SLOT + i].act.actor;
        toyActSetFrame((ACTActor*)(TOY_ANIM_TABLE + (TOY_PROP_SLOT + i) * 0x90 + 0x34), 20.0f);
        setActorAnimFrame(actor, ((ToyAnimSlot*)TOY_ANIM_TABLE)[TOY_PROP_SLOT + i].act.animFrame);
        AnimateActorBones(actor);
    }
}

// .text:0x000E68A8 size:0xE4 mapped:0x8072593C
void fn_3_E68A8(ToyFieldObj* obj) {
    ToyActorRoot* extraRoot = obj->extraModel->root;
    f32 frame = fn_800B4C40(obj->model->root) - obj->model->animSpeed;

    if (frame < 0.0f) {
        frame = 0.0f;
    }
    if (obj->extraModel != NULL) {
        memcpy(obj->extraModel->ctrl, obj, sizeof(obj->extraModel->ctrl));
        setActorAnimFrame(extraRoot, frame);
        fn_800BDA24(obj->extraModel);
        obj->extraModel->root->drawFlags =
            fn_800B3C04(0, (StadiumModelNode*)obj->extraModel->root, returnFloatFromModeIndex(returnsCurrentMode())->view);
        sknRelated(obj->extraModel, fn_80052768_getCamera(returnsCurrentMode())->view);
    }
}

// .text:0x000E698C size:0xBC mapped:0x80725A20
void fn_3_E698C(ToyFieldObj* obj) {
    void* actor = obj->model->root;
    f32 frame = fn_800B4C40(obj->model->root);
    u8 prop = obj->state - TOY_PROP_SLOT;

    if (!lbl_3_data_196B4[prop]) {
        setActorAnimFrame(actor, 0.0f);
        AnimateActorBones(actor);
    }
    if (lbl_3_data_196B4[prop] && frame <= 60.0f) {
        AnimateActorBones(actor);
    }
}

// .text:0x000E6A48 size:0x348 mapped:0x80725ADC
void fn_3_E6A48(ToyFieldObj* obj) {
    fn_3_E5A84(obj);
    fn_3_E6578(obj);
    if (obj->extraModel != NULL) {
        fn_3_E5FEC(obj);
        sknRelated(obj->extraModel, fn_80052768_getCamera(returnsCurrentMode())->view);
    }
    if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL && g_Minigame.toyFieldBallStateResult != 0 &&
        g_Minigame.toyFieldBallStateResult == lbl_3_data_1972C[obj->state] && lbl_3_data_1963F == obj->slot &&
        obj->state >= TOY_STATE_HOME) {
        lbl_3_data_196B4[obj->prop] = 1;
    }
}

// .text:0x000E6D90 size:0x5C0 mapped:0x80725E24
static inline void toyPlaySound(int sfx, int slot) {
    int stadiumID = g_d_GameSettings.StadiumID;
    SND_VOICEID voice = sndFXStartEx(stadiumHazardSoundIDs[stadiumID] + sfx,
                                     g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                                         ? lbl_3_data_84B8[slot]
                                         : stadiumHazardSoundFxRelated[stadiumID * 0x1E + slot],
                                     0x3F, 0);
    sndFXCtrl(voice, 0x5B,
              g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                  ? lbl_3_data_84B8[slot + 1]
                  : stadiumHazardSoundFxRelated[stadiumID * 0x1E + slot + 1]);
}

void fn_3_E6D90(ToyFieldObj* obj) {

    fn_3_E5A84(obj);
    if (g_GameLogic.gameStatus == GAME_STATUS_DEFAULT || g_GameLogic.gameStatus == GAME_STATUS_AT_BAT) {
        fn_3_E6528(obj);
        if (hitAll) {
            hitAll = FALSE;
        }
    }
    if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL) {
        if (g_Ball.AtBat_ContactResult != 0) {
            if (lbl_3_data_1963F == obj->slot &&
                g_Minigame.maybeTFCollisionResultState == lbl_3_data_1972C[obj->state]) {
                memcpy(obj->color, obj->hitColor, 4);
                obj->bodyColor = lbl_3_data_19024.colors[8][2];
                if (!obj->showMarker) {
                    toyPlaySound(0x14, 0x28);
                }
                obj->showMarker = TRUE;
                if (g_Minigame.toyFieldBallStateResult != 0 &&
                    g_Minigame.toyFieldBallStateResult == lbl_3_data_1972C[obj->state] &&
                    obj->state >= TOY_STATE_HOME) {
                    if (!lbl_3_data_196B4[obj->prop]) {
                        toyPlaySound(0x17, 0x2E);
                    }
                    lbl_3_data_196B4[obj->prop] = 1;
                }
            } else {
                memcpy(obj->color, obj->missColor, 4);
                obj->bodyColor = lbl_3_data_19024.colors[8][0];
                obj->showMarker = FALSE;
            }
        }
    } else {
        obj->_A0 = 0;
    }
    if (hitAll) {
        memcpy(obj->color, obj->hitColor, 4);
        obj->bodyColor = lbl_3_data_19024.colors[8][2];
        obj->showMarker = TRUE;
    }
    fn_3_E5FEC(obj);
    fn_3_E6578(obj);
    if (obj->extraModel != NULL) {
        sknRelated(obj->extraModel, fn_80052768_getCamera(returnsCurrentMode())->view);
        obj->extraModel->root->nodes[2]->dispObj = obj->extraModel->root->nodes[2]->altDispObj;
    }
}

// .text:0x000E7350 size:0x14 mapped:0x807263E4
void fn_3_E7350(void) {
    lbl_3_data_1963F = lbl_3_data_19640;
}

// .text:0x000E7364 size:0x24 mapped:0x807263F8
void fn_3_E7364(int idx) {
    lbl_3_data_19640 = ((ToyFieldObj*)&stadiumObjectCollision.objects[idx])->slot;
}

// .text:0x000E7388 size:0x9C mapped:0x8072641C
void processToyFieldObjectCollisions(Mtx view, StadiumDrawOrder* order) {
    StadiumDrawOrder* front = order;
    StadiumDrawOrder* back;
    StadiumObject* obj;
    int i;

    i = stadiumObjectCollision.objectCount - 1;
    obj = &stadiumObjectCollision.objects[i];
    do {
        if (!obj->hasShadow) {
            front->index = i;
            front++;
        }
        obj--;
    } while (i-- != 0);
    i = stadiumObjectCollision.objectCount - 1;
    back = order + stadiumObjectCollision.objectCount;
    obj = &stadiumObjectCollision.objects[i];
    do {
        if (obj->hasShadow) {
            back--;
            back->index = i;
            back->depth = 1.0f;
        }
        obj--;
    } while (i-- != 0);
}

// .text:0x000E7424 size:0xF8 mapped:0x807264B8
void fn_3_E7424(void) {
    if (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT || g_GameLogic.gameStatus == GAME_STATUS_DEFAULT) {
        roundCount++;
        lbl_3_bss_AE80[0] = g_Minigame._1914 != 0;
        lbl_3_bss_AE80[1] = g_Minigame._1915 != 0;
        lbl_3_bss_AE80[2] = g_Minigame._1916 != 0;
        lbl_3_bss_AE80[3] = g_Minigame._1917 != 0;
        lbl_3_data_1963F = -1;
        lbl_3_data_19640 = -1;
    }
    prevResult = lastResult;
    lastResult = g_Minigame.toyFieldBallStateResult;
    resultFrames += !PauseSimulation;
    if (prevResult != lastResult) {
        resultFrames = 0;
    }
    lbl_3_bss_AE51 = 0;
}

// .text:0x000E751C size:0x120 mapped:0x807265B0
TriangleGroup* fn_3_E751C(int idx, Mtx m) {
    ToyObjControl ctrl;
    ToyFieldObj* obj;

    ctrl.ctrl.type = 0;
    obj = (ToyFieldObj*)&stadiumObjectCollision.objects[idx];
    if (obj->state <= 7) {
        CTRLSetTranslation(&ctrl.ctrl, toyPlacements[idx].pos.x, -0.04f, toyPlacements[idx].pos.z);
        CTRLSetRotation(&ctrl.ctrl, 0.0f, toyPlacements[idx].rotY, 0.0f);
    } else {
        CTRLSetTranslation(&ctrl.ctrl, lbl_3_data_19644[obj->homeIndex].x, -0.04f,
                           lbl_3_data_19644[obj->homeIndex].z);
        CTRLSetRotation(&ctrl.ctrl, 0.0f, lbl_3_data_19698[obj->homeIndex], 0.0f);
    }
    CTRLBuildMatrix(&ctrl.ctrl, m);
    return ((StadiumObject*)obj)->triangles;
}

// .text:0x000E763C size:0x3F0 mapped:0x807266D0
void fn_3_E763C(void) {
    Mtx m;
    ToyObjControl ctrl;
    StadiumObject* obj;
    u32 size = stadiumObjectCollision.objectCount * sizeof(s32) + stadiumObjectCollision.objectCount * sizeof(u16) +
               stadiumObjectCollision.objectCount * sizeof(f32) +
               stadiumObjectCollision.objectCount * sizeof(VecSrcDst);
    s32 count;
    int off;
    int group;
    int j;

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
        if ((AtBat_ButtonInput1._00 & PAD_BUTTON_Y) && group != 0) {
            continue;
        }
        if ((AtBat_ButtonInput1._00 & PAD_BUTTON_X) && j != 0) {
            continue;
        }
        for (j = 0; j < 15; j++) {
            if (group == toyPlacements[j].group && stadiumObjectCollision.objects[j]._90b1 &&
                stadiumObjectCollision.objects[j].triangles != NULL) {
                ((s32*)stadiumObjectCollision.vertexData)[off] = j;
                off++;
                stadiumObjectCollision.hazardData[count]++;
                ctrl.ctrl.type = 0;
                obj = &stadiumObjectCollision.objects[j];
                CTRLSetTranslation(&ctrl.ctrl, toyPlacements[j].pos.x, toyPlacements[j].pos.y, toyPlacements[j].pos.z);
                CTRLSetRotation(&ctrl.ctrl, 0.0f, toyPlacements[j].rotY, 0.0f);
                CTRLBuildMatrix(&ctrl.ctrl, m);
                transformVectorsUpdateBoundingBox(m, (StadiumMeshData*)obj->triangles);
            }
        }
        if ((u32)stadiumObjectCollision.hazardData[count] != 0) {
            storeBoundingBoxCoordinates(&((Vec*)stadiumObjectCollision.vertexDataArray)[count * 2],
                                        &((Vec*)stadiumObjectCollision.vertexDataArray)[count * 2 + 1]);
            count++;
        }
    }
    for (group = 0; group < 10; group++) {
        off = (u16)(stadiumObjectCollision.vertexOffsets[count - 1] + stadiumObjectCollision.hazardData[count - 1]);
        stadiumObjectCollision.vertexOffsets[count] = off;
        initBoundingBoxLimits();
        for (j = 0; j < TOY_PROP_COUNT; j++) {
            if (group == toyPlacements[j].group && stadiumObjectCollision.objects[j]._90b1 &&
                stadiumObjectCollision.objects[j].triangles != NULL) {
                ((s32*)stadiumObjectCollision.vertexData)[off] = j + firstHomeObj;
                off++;
                stadiumObjectCollision.hazardData[count]++;
                ctrl.ctrl.type = 0;
                obj = &stadiumObjectCollision.objects[j + firstHomeObj];
                CTRLSetTranslation(&ctrl.ctrl, lbl_3_data_19644[j].x, lbl_3_data_19644[j].y, lbl_3_data_19644[j].z);
                CTRLSetRotation(&ctrl.ctrl, 0.0f, lbl_3_data_19698[j], 0.0f);
                CTRLBuildMatrix(&ctrl.ctrl, m);
                transformVectorsUpdateBoundingBox(m, (StadiumMeshData*)obj->triangles);
            }
        }
        if ((u32)stadiumObjectCollision.hazardData[count] != 0) {
            storeBoundingBoxCoordinates(&((Vec*)stadiumObjectCollision.vertexDataArray)[count * 2],
                                        &((Vec*)stadiumObjectCollision.vertexDataArray)[count * 2 + 1]);
            count++;
        }
        stadiumObjectCollision.boundingBoxCount = count;
    }
}

// .text:0x000E7A2C size:0xF4 mapped:0x80726AC0
void fn_3_E7A2C(StadiumObject* obj) {
    obj->callback = NULL;
    obj->func = NULL;
    obj->preDraw = NULL;
    obj->postDraw = NULL;
    switch (((ToyFieldObj*)obj)->state) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        obj->func = (int (*)(int, int, void*))fn_3_E7364;
        obj->preDraw = (void (*)(StadiumObject*))fn_3_E6D90;
        placedPropCount++;
        break;
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
        obj->callback = (void (*)(void))fn_3_E698C;
        obj->preDraw = (void (*)(StadiumObject*))fn_3_E68A8;
        break;
    case 23:
        obj->preDraw = (void (*)(StadiumObject*))fn_3_E6798;
        obj->postDraw = (void (*)(StadiumObject*))fn_3_E671C;
        break;
    case 24:
        obj->preDraw = (void (*)(StadiumObject*))fn_3_E6684;
        obj->postDraw = (void (*)(StadiumObject*))fn_3_E6638;
        break;
    case 26:
        obj->callback = (void (*)(void))fn_3_E59B4;
        break;
    case 25:
        obj->callback = (void (*)(void))fn_3_E5A1C;
        break;
    }
}

// .text:0x000E7B20 size:0xFA8 mapped:0x80726BB4
E(u8, BOOL) fn_3_E7B20(void** files, u32* ids) {
    StadiumObject* o;
    StadiumObject* last;
    u8 done = FALSE;
    int count = 0;
    u32 i;
    u32 n;

    if (files == NULL || ids == NULL) {
        return FALSE;
    }
    placedPropCount = 0;
    memset(lbl_3_bss_AE8C, 0xFF, sizeof(lbl_3_bss_AE8C));
    memset(stadiumObjectCollision.objects, 0, stadiumObjectCollision.objectCount * sizeof(StadiumObject));
    o = last = stadiumObjectCollision.objects;
    switch (g_Minigame.miniGameNumberOfParticipants) {
    case 2:
        toyPlacements = lbl_3_data_19024.layouts[0];
        homeTypes = lbl_3_data_19024.homeTypes[0];
        break;
    case 3:
        toyPlacements = lbl_3_data_19024.layouts[1];
        homeTypes = lbl_3_data_19024.homeTypes[1];
        break;
    default:
        toyPlacements = lbl_3_data_19024.layouts[2];
        homeTypes = lbl_3_data_19024.homeTypes[2];
        break;
    }
    layoutIndex = g_Minigame.miniGameNumberOfParticipants - 2;
    if (g_Minigame._19A6 > 1) {
        hitAll = TRUE;
        toyPlacements = lbl_3_data_19024.layouts[3];
        homeTypes = lbl_3_data_19024.homeTypes[3];
        layoutIndex = 3;
    }

    for (i = 0; i < 15; i++, o++, count++) {
        last = o;
        if (toyPlacements[i].type == TOY_OBJ_END) {
            done = TRUE;
        }
        if (done) {
            for (; i < TOY_LAYOUT_SLOTS; i++) {
                memset(&toyPlacements[i], 0, sizeof(ToyPlacement));
                toyPlacements[i].type = TOY_OBJ_END;
                toyPlacements[i].group = 10;
            }
            break;
        }
        ((ToyFieldObj*)o)->slot = i;
        ((ToyFieldObj*)o)->state = toyPlacements[i].type;
        ((ToyFieldObj*)o)->extraModel = (ToyModel*)(TOY_ANIM_TABLE + 0xD24);
        o->model = (StadiumModel*)(TOY_ANIM_TABLE + ((ToyFieldObj*)o)->state * 0x90 + 0x34);
        o->triangles = files[ids[((ToyFieldObj*)o)->state + 31]];
        o->hasShadow = 1;
        o->_90b1 = 1;
        ((Control*)o)->type = 0;
        CTRLSetTranslation((Control*)o, 0.0f, 0.0f, 0.0f);
        ((ToyFieldObj*)o)->missColor = lbl_3_data_19024.colors[((ToyFieldObj*)o)->state][0];
        ((ToyFieldObj*)o)->baseColor = lbl_3_data_19024.colors[((ToyFieldObj*)o)->state][1];
        ((ToyFieldObj*)o)->hitColor = lbl_3_data_19024.colors[((ToyFieldObj*)o)->state][2];
        ((ToyFieldObj*)o)->bodyColor = lbl_3_data_19024.colors[8][1];
        fn_3_E6528((ToyFieldObj*)o);
        o->fadeByDepth = 0;
        o->alpha = 0xFF;
        o->effect = NULL;
        o->animActive = 0;
        o->animIndex = -1;
        o->drawPass = 1;
        fn_3_E7A2C(o);
    }

    done = FALSE;
    firstHomeObj = count;
    for (i = 0; i < TOY_PROP_COUNT; i++, o++, count++) {
        last = o;
        if (homeTypes[i].type == TOY_OBJ_END) {
            done = TRUE;
        }
        if (done) {
            for (; i < TOY_HOME_SLOTS; i++) {
                memset(&homeTypes[i], 0, sizeof(ToyHomeType));
                homeTypes[i].type = TOY_OBJ_END;
                homeTypes[i].group = 10;
            }
            break;
        }
        ((ToyFieldObj*)o)->slot = count;
        ((ToyFieldObj*)o)->state = homeTypes[i].type;
        ((ToyFieldObj*)o)->homeIndex = i;
        ((ToyFieldObj*)o)->prop = 6 - i;
        ((ToyFieldObj*)o)->extraModel = (ToyModel*)(TOY_ANIM_TABLE + 0xDB4);
        o->model = (StadiumModel*)(TOY_ANIM_TABLE + ((ToyFieldObj*)o)->state * 0x90 + 0x34);
        o->triangles = files[ids[((ToyFieldObj*)o)->state + 31]];
        o->hasShadow = 1;
        o->_90b1 = 1;
        ((Control*)o)->type = 0;
        CTRLSetTranslation((Control*)o, 0.0f, 0.0f, 0.0f);
        ((ToyFieldObj*)o)->missColor = lbl_3_data_19024.colors[((ToyFieldObj*)o)->state - 8][0];
        ((ToyFieldObj*)o)->baseColor = lbl_3_data_19024.colors[((ToyFieldObj*)o)->state - 8][1];
        ((ToyFieldObj*)o)->hitColor = lbl_3_data_19024.colors[((ToyFieldObj*)o)->state - 8][2];
        ((ToyFieldObj*)o)->bodyColor = lbl_3_data_19024.colors[8][1];
        fn_3_E6528((ToyFieldObj*)o);
        o->fadeByDepth = 0;
        o->alpha = 0xFF;
        o->effect = NULL;
        o->animActive = 0;
        o->animIndex = -1;
        o->drawPass = 1;
        fn_3_E7A2C(o);
    }

    for (i = TOY_PROP_SLOT; i < TOY_PROP_SLOT + TOY_PROP_COUNT; i++, o++, count++) {
        last = o;
        ((ToyFieldObj*)o)->slot = count;
        ((ToyFieldObj*)o)->state = i;
        ((ToyFieldObj*)o)->extraModel = (ToyModel*)(TOY_ANIM_TABLE + 0xE44);
        o->model = (StadiumModel*)(TOY_ANIM_TABLE + i * 0x90 + 0x34);
        o->triangles = NULL;
        o->hasShadow = 1;
        o->_90b1 = 1;
        ((Control*)o)->type = 0;
        CTRLSetTranslation((Control*)o, lbl_3_data_196BC[((ToyFieldObj*)o)->state - TOY_PROP_SLOT].x,
                           lbl_3_data_196BC[((ToyFieldObj*)o)->state - TOY_PROP_SLOT].y,
                           lbl_3_data_196BC[((ToyFieldObj*)o)->state - TOY_PROP_SLOT].z);
        CTRLSetRotation((Control*)o, 0.0f, lbl_3_data_19710[((ToyFieldObj*)o)->state - TOY_PROP_SLOT], 0.0f);
        o->fadeByDepth = 1;
        o->alpha = 0xFF;
        o->effect = NULL;
        o->animActive = 0;
        o->animIndex = -1;
        o->drawPass = 1;
        fn_3_E7A2C(o);
    }

    ((ToyFieldObj*)&last[1])->slot = count;
    ((ToyFieldObj*)&last[1])->state = 0x17;
    last[1].model = (StadiumModel*)(TOY_ANIM_TABLE + 0xED4);
    last[1].triangles = NULL;
    last[1].hasShadow = 1;
    last[1]._90b1 = 0;
    ((Control*)&last[1])->type = 0;
    CTRLSetTranslation((Control*)&last[1], 0.0f, 0.0f, 0.0f);
    last[1].fadeByDepth = 0;
    last[1].alpha = 0xFF;
    last[1].effect = NULL;
    last[1].animActive = 0;
    last[1].animIndex = -1;
    last[1].drawPass = 1;
    fn_3_E7A2C(&last[1]);

    ((ToyFieldObj*)&last[2])->slot = count + 1;
    ((ToyFieldObj*)&last[2])->state = 0x18;
    last[2].model = (StadiumModel*)(TOY_ANIM_TABLE + 0xF64);
    last[2].triangles = NULL;
    last[2].hasShadow = 1;
    last[2]._90b1 = 0;
    ((Control*)&last[2])->type = 0;
    CTRLSetTranslation((Control*)&last[2], 0.0f, 0.0f, 0.0f);
    last[2].fadeByDepth = 0;
    last[2].alpha = 0xFF;
    last[2].effect = NULL;
    last[2].animActive = 0;
    last[2].animIndex = -1;
    last[2].drawPass = 1;
    fn_3_E7A2C(&last[2]);

    ((ToyFieldObj*)&last[3])->slot = count + 2;
    ((ToyFieldObj*)&last[3])->state = 0x1A;
    last[3].model = (StadiumModel*)(TOY_ANIM_TABLE + 0xFF4);
    last[3].triangles = NULL;
    last[3].hasShadow = 1;
    last[3]._90b1 = 0;
    ((Control*)&last[3])->type = 0;
    CTRLSetTranslation((Control*)&last[3], 0.0f, 0.0f, 0.0f);
    last[3].fadeByDepth = 0;
    last[3].alpha = 0xFF;
    last[3].effect = NULL;
    last[3].animActive = 0;
    last[3].animIndex = -1;
    last[3].drawPass = 0;
    fn_3_E7A2C(&last[3]);

    ((ToyFieldObj*)&last[4])->slot = count + 3;
    ((ToyFieldObj*)&last[4])->state = 0x19;
    last[4].model = (StadiumModel*)(TOY_ANIM_TABLE + 0x1084);
    last[4].triangles = NULL;
    last[4].hasShadow = 1;
    last[4]._90b1 = 0;
    ((Control*)&last[4])->type = 0;
    CTRLSetTranslation((Control*)&last[4], 0.0f, 0.0f, 0.0f);
    last[4].fadeByDepth = 0;
    last[4].alpha = 0xFF;
    last[4].effect = NULL;
    last[4].animActive = 0;
    last[4].animIndex = -1;
    last[4].drawPass = 1;
    fn_3_E7A2C(&last[4]);

    o = last + 5;
    for (n = count + 4; n < stadiumObjectCollision.objectCount; n++, o++) {
        ((ToyFieldObj*)o)->state = TOY_OBJ_END;
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
    }
    fn_3_E763C();
    if (g_GameLogic.gameStatus == GAME_STATUS_GAME_START_MOVIE) {
        fn_3_E67F4();
    }
    return TRUE;
}

// .text:0x000E8AC8 size:0x5C mapped:0x80727B5C
BOOL fn_3_E8AC8(void) {
    if (g_d_GameSettings.StadiumID != STADIUM_ID_TOY_FIELD) {
        return FALSE;
    }
    return fn_3_E7B20(stadiumObjectCollision.stadiumData, stadiumObjectCollision._34) != FALSE;
}

// .text:0x000E8B24 size:0x5F8 mapped:0x80727BB8
void loadToyField(void** files) {
    u32* ids;
    u32 i;

    stadiumObjectCollision.preUpdateFunc = fn_3_E7424;
    stadiumObjectCollision.gameStatusIsLiveBall = FALSE;
    ids = stadiumObjectCollision._34 = _OSAllocFromHeap(4, 0xBC);
    processStadiumFileObjects(enumObjTypeInFile_ARRAY_807cac10, 0x2F, (u8*)files, ids);
    TOY_ANIM_TABLE = ActorObjectInitTable(30);
    animateBallRelated(TOY_ANIM_TABLE, 0, 0, files[ids[1]], 0, 0);
    animateBallRelated(TOY_ANIM_TABLE, 1, 1, files[ids[2]], 0, 0);
    animateBallRelated(TOY_ANIM_TABLE, 2, 2, files[ids[3]], 0, 0);
    animateBallRelated(TOY_ANIM_TABLE, 3, 3, files[ids[4]], 0, 0);
    animateBallRelated(TOY_ANIM_TABLE, 4, 4, files[ids[5]], 0, 0);
    animateBallRelated(TOY_ANIM_TABLE, 5, 5, files[ids[6]], 0, 0);
    animateBallRelated(TOY_ANIM_TABLE, 6, 6, files[ids[7]], 0, 0);
    animateBallRelated(TOY_ANIM_TABLE, 7, 7, files[ids[8]], 0, 0);
    animateBallRelated(TOY_ANIM_TABLE, 8, 8, files[ids[9]], 0, 0);
    animateBallRelated(TOY_ANIM_TABLE, 9, 9, files[ids[10]], 0, 0);
    animateBallRelated(TOY_ANIM_TABLE, 10, 10, files[ids[11]], 0, 0);
    animateBallRelated(TOY_ANIM_TABLE, 11, 11, files[ids[12]], 0, 0);
    animateBallRelated(TOY_ANIM_TABLE, 12, 12, files[ids[13]], 0, 0);
    animateBallRelated(TOY_ANIM_TABLE, 13, 13, files[ids[14]], 0, 0);
    animateBallRelated(TOY_ANIM_TABLE, 14, 14, files[ids[15]], 0, 0);
    animateBallRelated(TOY_ANIM_TABLE, 15, 15, files[ids[16]], 0, 0);
    for (i = 0; i < TOY_PROP_COUNT; i++) {
        animateBallRelated(TOY_ANIM_TABLE, TOY_PROP_SLOT + i, TOY_PROP_SLOT + i, files[ids[i + 17]], 0, 0);
        actorSetAnimBank((ACTActor*)(TOY_ANIM_TABLE + (TOY_PROP_SLOT + i) * 0x90 + 0x34), (u32)files[ids[i + 17] + 2]);
    }
    animateBallRelated(TOY_ANIM_TABLE, 23, 23, files[ids[24]], 0, 0);
    animateBallRelated(TOY_ANIM_TABLE, 24, 24, files[ids[25]], 0, 0);
    animateBallRelated(TOY_ANIM_TABLE, 25, 25, files[ids[26]], 0, 0);
    actorSetAnimBank((ACTActor*)(TOY_ANIM_TABLE + 25 * 0x90 + 0x34), (u32)files[ids[26] + 2]);
    animateBallRelated(TOY_ANIM_TABLE, 26, 26, files[ids[27]], 0, 0);
    animateBallRelated(TOY_ANIM_TABLE, 27, 27, files[ids[28]], 0, 0);
    animateBallRelated(TOY_ANIM_TABLE, 28, 28, files[ids[29]], 0, 0);
    actorSetAnimBank((ACTActor*)(TOY_ANIM_TABLE + 28 * 0x90 + 0x34), (u32)files[ids[29] + 2]);
    toyActSetFrame((ACTActor*)(TOY_ANIM_TABLE + 28 * 0x90 + 0x34), 20.0f);
    setActorAnimFrame(((ToyAnimSlot*)TOY_ANIM_TABLE)[28].act.actor, ((ToyAnimSlot*)TOY_ANIM_TABLE)[28].act.animFrame);
    animateBallRelated(TOY_ANIM_TABLE, 29, 29, files[ids[30]], 0, 0);
    actorSetAnimBank((ACTActor*)(TOY_ANIM_TABLE + 29 * 0x90 + 0x34), (u32)files[ids[30] + 2]);
    toyActSetFrame((ACTActor*)(TOY_ANIM_TABLE + 29 * 0x90 + 0x34), 60.0f);
    setActorAnimFrame(((ToyAnimSlot*)TOY_ANIM_TABLE)[29].act.actor, ((ToyAnimSlot*)TOY_ANIM_TABLE)[29].act.animFrame);
    stadiumObjectCollision.propCount = 30;
    for (i = 0; i < stadiumObjectCollision.propCount; i++) {
        fn_800BD478(TOY_ANIM_TABLE + i * 0x90 + 0x34, files[ids[i + 1]]);
    }
    for (i = 0; i < 30; i++) {
        fn_800BD548(TOY_ANIM_TABLE + i * 0x90 + 0x34, 4, stadiumObjectCollision.lights[0],
                    stadiumObjectCollision.lights[1], stadiumObjectCollision.lights[2],
                    stadiumObjectCollision.lights[3]);
    }
    stadiumObjectCollision.objectCount = 32;
    stadiumObjectCollision.objects = _OSAllocFromHeap(0x20, stadiumObjectCollision.objectCount * sizeof(StadiumObject));
    memset(stadiumObjectCollision.objects, 0, stadiumObjectCollision.objectCount * sizeof(StadiumObject));
    stadiumObjectCollision.objectsRelated = _OSAllocFromHeap(0x20, stadiumObjectCollision.objectCount * sizeof(StadiumObject));
    memset(stadiumObjectCollision.objectsRelated, 0, stadiumObjectCollision.objectCount * sizeof(StadiumObject));
    stadiumObjectCollision.vertexDataArray = NULL;
    fn_3_E7B20(files, ids);
    roundCount = 0;
}

