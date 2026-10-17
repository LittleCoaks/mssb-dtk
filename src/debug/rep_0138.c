#define REP_HEADER_DATA_FN getRepHeaderData_rep0138
#include "debug/rep_0138.h"
#define SQRT2_LINKAGE static
#include "game/UnknownHomes_Game.h"
#include "header_rep_data.h"
#include "Dolphin/gx.h"
#include "Unknown/File_0x800bd300.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x800b0a14.h"
#include "Dolphin/stl.h"
#include "C3/control.h"
#include "stl/math.h"
#include "Dolphin/OS/OSCache.h"
#include "game/match_setup/match_loading.h"

typedef struct FogParams1_4E0 {
    GXColor color;
    f32 nearZ;
    f32 farZ;
} FogParams1_4E0;

typedef struct StadiumViewScene {
    /*0x00*/ void (*func)(void);
    /*0x04*/ u8 pad04[8];
    /*0x0C*/ DrawingSceneStruct *parent;
    /*0x10*/ s16 state;
    /*0x12*/ u8 pad12[2];
    /*0x14*/ void *model;
    /*0x18*/ s16 index;
} StadiumViewScene;

#define INPUT1_FIELD(type, off) (*(type *)((u8 *)&AtBat_ButtonInput1 + (off)))

typedef struct DbgVtxArray {
    /*0x00*/ s16 *data;
    /*0x04*/ u8 pad04[2];
    /*0x06*/ u8 format;
    /*0x07*/ u8 stride;
} DbgVtxArray;

typedef struct DbgDLEntry {
    /*0x00*/ u8 cmd;
    /*0x01*/ u8 pad01[3];
    /*0x04*/ u32 attrFlags;
    /*0x08*/ u8 *stream;
    /*0x0C*/ u32 size;
} DbgDLEntry;

typedef struct DbgDLHeader {
    /*0x00*/ u8 pad00[4];
    /*0x04*/ DbgDLEntry *entries;
    /*0x08*/ u16 count;
} DbgDLHeader;

typedef struct DbgGeo {
    /*0x00*/ DbgVtxArray *pos;
    /*0x04*/ u8 pad04[8];
    /*0x0C*/ DbgVtxArray *nrm;
    /*0x10*/ DbgDLHeader *dl;
    /*0x14*/ u8 pad14[4];
    /*0x18*/ Mtx mtx;
    /*0x48*/ u8 pad48[0x54 - 0x48];
    /*0x54*/ f32 minX;
    /*0x58*/ f32 maxX;
    /*0x5C*/ f32 minY;
    /*0x60*/ f32 maxY;
    /*0x64*/ f32 minZ;
    /*0x68*/ f32 maxZ;
} DbgGeo;

typedef struct DbgGeoSlot {
    DbgGeo *geo;
    s32 unk4;
} DbgGeoSlot;

typedef struct DbgGeoTable {
    /*0x00*/ u8 pad00[0x10];
    /*0x10*/ DbgGeoSlot *slots;
} DbgGeoTable;

typedef struct DbgActorEntry {
    /*0x00*/ Control *ctrl;
    /*0x04*/ u8 pad04[0x10];
    /*0x14*/ u16 geoKey;
    /*0x16*/ u8 pad16[4];
    /*0x1A*/ u16 flags;
} DbgActorEntry;

typedef struct DbgActorSet {
    /*0x00*/ u8 pad00[6];
    /*0x06*/ u16 count;
    /*0x08*/ u8 pad08[8];
    /*0x10*/ DbgGeoTable *geoTable;
    /*0x14*/ u8 pad14[0xC];
    /*0x20*/ DbgActorEntry entries[1];
} DbgActorSet;

typedef struct DbgDrawNode {
    /*0x00*/ u32 unk00;
    /*0x04*/ void (*draw)(void *);
    /*0x08*/ Mtx local;
    /*0x38*/ Mtx world;
    /*0x68*/ DbgActorSet *model;
} DbgDrawNode;

typedef struct DbgOffsetTable {
    /*0x00*/ u16 count;
    /*0x04*/ u32 offsets[1];
} DbgOffsetTable;

typedef struct DbgViewState {
    /*0x000*/ Mtx view;
    /*0x030*/ u16 yaw;
    /*0x032*/ u16 pitch;
    /*0x034*/ f32 strafe;
    /*0x038*/ f32 forward;
    /*0x03C*/ Vec target;
    /*0x048*/ Vec eye;
    /*0x054*/ f32 zoom;
    /*0x058*/ void *texHeader;
    /*0x05C*/ DbgDrawNode nodes[2];
    /*0x134*/ DbgDrawNode nodes2[2];
    /*0x20C*/ u8 pad20C[0x21C - 0x20C];
    /*0x21C*/ void *dlBuf;
    /*0x220*/ u8 pad220[4];
    /*0x224*/ void *list;
    /*0x228*/ s16 count;
    /*0x22A*/ s16 actorCount;
    /*0x22C*/ s16 visibleCount;
    /*0x22E*/ s16 selected;
    /*0x230*/ s8 stadium;
    /*0x231*/ s8 variant;
    /*0x232*/ u8 menuOpen;
    /*0x233*/ s8 menuSel;
    /*0x234*/ u8 flag234;
    /*0x235*/ s8 runHandler;
    /*0x236*/ u8 pad236[2];
    /*0x238*/ s8 flag238;
    /*0x239*/ s8 showBoxes;
    /*0x23A*/ u16 angle;
    /*0x23C*/ s8 fogSel;
    /*0x23D*/ u8 pad23D[0x3C0 - 0x23D];
} DbgViewState;

typedef struct CallbackRec {
    s32 reserved;
    void (*fn)(void);
} CallbackRec;


extern void fn_80048C28(void);
extern void fn_80048C1C(void);
extern void fn_80048D4C(void);
extern void SetFog(s32 type, GXColor color, f32 nearZ, f32 farZ, f32 arg4, f32 arg5);
extern void SetFogNoneAgain(void);
extern void fn_800B806C(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
extern s32 fn_80048EA8(u8 arg0);
extern void fn_80048E00(u8 arg0, s32 arg1);
extern void fn_80048C14(s32 arg0);
extern DbgViewState lbl_1_common_bss_472B4;
extern u8 drawStadiumRelated;
extern void fn_800A7D4C(s32 arg0, void *arg1);
extern void AdjustActorPointers(void *arg0);
extern void AdjustGEOPalettePointers(void *arg0);
extern void convertTextureHeader(void *arg0);
extern void UpdateTexturePalettePointers(void *arg0, void *arg1);
extern void haveActLayoutPointToGeoHeader(void *arg0, void *arg1);
extern u8 lbl_80366158[0x30];
extern void fn_800AD038(void *arg0);
extern void *_OSAllocFromHeap(s32 arg0, s32 arg1);
extern void renderingRelated(void);
extern s32 checkObjectVisibility(s32 arg0, void *box, MtxPtr mtx);
extern void DOVARender(void *dispObj, MtxPtr camera, u8 numLights, va_list list);
extern void makeLookAtMatrix(MtxPtr dst, Vec *eye, Vec *target, Vec *up);
extern void fn_80011640(void *arg0, void *arg1);
extern void fn_800B9950(s32 arg0, f32 arg1, f32 arg2);
extern void fn_1_196C(void);
extern void fn_800B996C(void *arg0);
extern void setLITLightPtr(s32 arg0);
extern void LITAlloc(void **light);
extern void LITInitAttn(void *light, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
extern void LITInitPos(void *light, f32 arg1, f32 arg2, f32 arg3);
extern void LITInitDir(void *light, f32 arg1, f32 arg2, f32 arg3);
extern void LITInitColor(void *light, GXColor color);
extern void *ARAMTransfer(void *file, s32 arg1, s32 arg2, s32 arg3);
extern void DCFlushRangeNoSync(void *addr, u32 numBytes);
extern u8 lbl_803C6CF8[0x708];
extern f32 lbl_1_data_200[6];

static u8 lbl_1_bss_520[0x2A88] ATTRIBUTE_ALIGN(32);
static GXTexObj lbl_1_bss_4E4;
static FogParams1_4E0 *lbl_1_bss_4E0;
static u8 lbl_1_bss_2E0[0x200];
static u8 lbl_1_bss_E0[0x200];
static u8 lbl_1_bss_DC;
static u32 lbl_1_bss_D8;
static u32 lbl_1_bss_D4;
static u8 lbl_1_bss_D1;
static u8 lbl_1_bss_D0;
static u32 lbl_1_bss_C8[2];
static s32 lbl_1_bss_C4;
static u8 lbl_1_bss_C2;
static u8 lbl_1_bss_C1;
static u8 lbl_1_bss_C0;

static u32 lbl_1_data_2A8[15][24] = {
    {
        0xAABED200, 0x42A00000, 0x43E10000, 0xAABED200, 0x42A00000, 0x43E10000,
        0xAABED200, 0x42A00000, 0x43E10000, 0x42200000, 0x3F800000, 0x3F800000,
        0x0070010A, 0x42A00000, 0x3F800000, 0x3F800000, 0x004001C0, 0x42A00000,
        0x3F800000, 0x3F800000, 0x004001C0, 0x37F403C5, 0x00000000, 0x08800000,
    },
    {
        0xAABED200, 0x42A00000, 0x43E10000, 0xAABED200, 0x42A00000, 0x43E10000,
        0xAABED200, 0x42A00000, 0x43E10000, 0x42280000, 0x3FC00000, 0x3FC00000,
        0x0FA001C0, 0x42A00000, 0x3F800000, 0x3F800000, 0x0F8001C0, 0x42A00000,
        0x3F800000, 0x3F800000, 0x0F5001C0, 0x37F403C5, 0x00000000, 0x08400000,
    },
    {
        0xFFDC9600, 0x00000000, 0x44000000, 0xFFDC9600, 0x00000000, 0x44000000,
        0xFFDC9600, 0x00000000, 0x44000000, 0x42280000, 0x3FC00000, 0x3FC00000,
        0x0FA001C0, 0x42A00000, 0x3F800000, 0x3F800000, 0x0F8001C0, 0x42A00000,
        0x3F800000, 0x3F800000, 0x0F5001C0, 0x37F403C5, 0x00000000, 0x08750000,
    },
    {
        0xAABED200, 0x42A00000, 0x43E10000, 0xAABED200, 0x42A00000, 0x43E10000,
        0xAABED200, 0x42A00000, 0x43E10000, 0x42200000, 0x3F800000, 0x3F800000,
        0x0B7001C0, 0x42A00000, 0x3F800000, 0x3F800000, 0x0B4001C0, 0x42A00000,
        0x3F800000, 0x3F800000, 0x0B4001C0, 0x37F403C5, 0x00000000, 0x08600000,
    },
    {
        0x96AADC02, 0x42A00000, 0x43960000, 0x96AADC02, 0x42A00000, 0x43960000,
        0x96AADC02, 0x42A00000, 0x43960000, 0x42200000, 0x3F800000, 0x3F800000,
        0x0B7001C0, 0x42A00000, 0x3F800000, 0x3F800000, 0x0B4001C0, 0x42A00000,
        0x3F800000, 0x3F800000, 0x0B4001C0, 0x00000000, 0x00FFFF00, 0x08600000,
    },
    {
        0xAABED207, 0x00000000, 0x43BE0000, 0xAABED207, 0x00000000, 0x43BE0000,
        0xAABED207, 0x00000000, 0x43BE0000, 0x42480000, 0x3F800000, 0x3F800000,
        0x0B8001C0, 0x42480000, 0x3F800000, 0x3F800000, 0x008001C0, 0x42480000,
        0x3F800000, 0x3F800000, 0x0B8001C0, 0x392B92A6, 0x00000000, 0x08480000,
    },
    {
        0xAABED200, 0x42A00000, 0x43E10000, 0xAABED200, 0x42A00000, 0x43E10000,
        0xAABED200, 0x42A00000, 0x43E10000, 0x42200000, 0x3F800000, 0x3F800000,
        0x0070010A, 0x42A00000, 0x3F800000, 0x3F800000, 0x004001C0, 0x42A00000,
        0x3F800000, 0x3F800000, 0x004001C0, 0x37F403C5, 0x00000000, 0x08800000,
    },
    {
        0xAABED200, 0x42A00000, 0x43E10000, 0xAABED200, 0x42A00000, 0x43E10000,
        0xAABED200, 0x42A00000, 0x43E10000, 0x42200000, 0x3F800000, 0x3F800000,
        0x0070010A, 0x42A00000, 0x3F800000, 0x3F800000, 0x004001C0, 0x42A00000,
        0x3F800000, 0x3F800000, 0x004001C0, 0x37F403C5, 0x00000000, 0x08800000,
    },
    {
        0xAABED200, 0x42A00000, 0x43E10000, 0xAABED200, 0x42A00000, 0x43E10000,
        0xAABED200, 0x42A00000, 0x43E10000, 0x42280000, 0x3FC00000, 0x3FC00000,
        0x0FA001C0, 0x42A00000, 0x3F800000, 0x3F800000, 0x0F8001C0, 0x42A00000,
        0x3F800000, 0x3F800000, 0x0F5001C0, 0x37F403C5, 0x00000000, 0x08400000,
    },
    {
        0xFFDC9600, 0x00000000, 0x44000000, 0xFFDC9600, 0x00000000, 0x44000000,
        0xFFDC9600, 0x00000000, 0x44000000, 0x42280000, 0x3FC00000, 0x3FC00000,
        0x0FA001C0, 0x42A00000, 0x3F800000, 0x3F800000, 0x0F8001C0, 0x42A00000,
        0x3F800000, 0x3F800000, 0x0F5001C0, 0x37F403C5, 0x00000000, 0x08750000,
    },
    {
        0xAABED200, 0x42A00000, 0x43E10000, 0xAABED200, 0x42A00000, 0x43E10000,
        0xAABED200, 0x42A00000, 0x43E10000, 0x42200000, 0x3F800000, 0x3F800000,
        0x0B7001C0, 0x42A00000, 0x3F800000, 0x3F800000, 0x0B4001C0, 0x42A00000,
        0x3F800000, 0x3F800000, 0x0B4001C0, 0x37F403C5, 0x00000000, 0x08600000,
    },
    {
        0x96AADC02, 0x42A00000, 0x43960000, 0x96AADC02, 0x42A00000, 0x43960000,
        0x96AADC02, 0x42A00000, 0x43960000, 0x42200000, 0x3F800000, 0x3F800000,
        0x0B7001C0, 0x42A00000, 0x3F800000, 0x3F800000, 0x0B4001C0, 0x42A00000,
        0x3F800000, 0x3F800000, 0x0B4001C0, 0x00000000, 0x00FFFF00, 0x08600000,
    },
    {
        0xAABED207, 0x00000000, 0x43BE0000, 0xAABED207, 0x00000000, 0x43BE0000,
        0xAABED207, 0x00000000, 0x43BE0000, 0x42480000, 0x3F800000, 0x3F800000,
        0x0B8001C0, 0x42480000, 0x3F800000, 0x3F800000, 0x008001C0, 0x42480000,
        0x3F800000, 0x3F800000, 0x0B8001C0, 0x392B92A6, 0x00000000, 0x08480000,
    },
    {
        0xAABED200, 0x42A00000, 0x43E10000, 0xAABED200, 0x42A00000, 0x43E10000,
        0xAABED200, 0x42A00000, 0x43E10000, 0x42200000, 0x3F800000, 0x3F800000,
        0x0070010A, 0x42A00000, 0x3F800000, 0x3F800000, 0x004001C0, 0x42A00000,
        0x3F800000, 0x3F800000, 0x004001C0, 0x37F403C5, 0x00000000, 0x08800000,
    },
    {
        0xAABED200, 0x42A00000, 0x43E10000, 0xAABED200, 0x42A00000, 0x43E10000,
        0xAABED200, 0x42A00000, 0x43E10000, 0x42200000, 0x3F800000, 0x3F800000,
        0x0070010A, 0x42A00000, 0x3F800000, 0x3F800000, 0x004001C0, 0x42A00000,
        0x3F800000, 0x3F800000, 0x004001C0, 0x37F403C5, 0x00000000, 0x08800000,
    },
};
static void *lbl_1_data_848[3] = {NULL, NULL, NULL};
static s32 lbl_1_data_854 = 0x40;
static GXColor lbl_1_data_858 = {0xFF, 0x80, 0x80, 0x00};
static u8 lbl_1_data_85C = 1;
static void (*lbl_1_data_860[7])(void) = {fn_1_85A8, fn_1_8368, fn_1_7FF8, fn_1_85A8, NULL, fn_1_7EF8, NULL};
static f32 lbl_1_data_87C[4] = {0.0f, 1.0f, 0.0f, 0.0f};
static CallbackRec lbl_1_data_88C[3] = {{0, fn_1_78E4}, {0, fn_1_78E4}, {0, (void (*)(void))0xFFFFFF0A}};
static CallbackRec lbl_1_data_8A4[2] = {{0, fn_1_786C}, {0, fn_1_786C}};
static CallbackRec lbl_1_data_8B4[2] = {{0, fn_1_7848}, {0, fn_1_7848}};
static GXCullMode lbl_1_data_8C4 = GX_CULL_BACK;
static u8 lbl_1_data_8C8 = 1;
static s32 lbl_1_data_8CC = 7;
static MatchFileDescriptor lbl_1_data_8D0[21] = {
    {0x0000040B, 0x40168A6C, 0x06CFD000, 0x000C69A8},
    {0x0000040B, 0x401331E0, 0x06DC4000, 0x000B67C4},
    {0x0000040B, 0x4011924C, 0x06E7A800, 0x000A5764},
    {0x0000040B, 0x400FBAE0, 0x06F20000, 0x000BE038},
    {0x0000040B, 0x400E5AC0, 0x06FDE800, 0x000B4FB8},
    {0x0000040B, 0x40131200, 0x07093800, 0x000A317C},
    {0x0000040B, 0x4011B660, 0x07137000, 0x000D0294},
    {0x0000040B, 0x4011B660, 0x07137000, 0x000D0294},
    {0x0000040B, 0x4011B660, 0x07137000, 0x000D0294},
    {0x0000040B, 0x40141C60, 0x07207800, 0x000CE904},
    {0x0000040B, 0x4013CA40, 0x072D6800, 0x000CA560},
    {0x0000040B, 0x40141C60, 0x07207800, 0x000CE904},
    {0x0000040B, 0x4016C138, 0x073A1000, 0x000ED41C},
    {0x0000040B, 0x401157B8, 0x0748E800, 0x000CA83C},
    {0x0000040B, 0x4016C138, 0x073A1000, 0x000ED41C},
    {0x0000040B, 0x400EB1C0, 0x07559800, 0x000A3510},
    {0x0000040B, 0x400EB1C0, 0x07559800, 0x000A3510},
    {0x0000040B, 0x400EB1C0, 0x07559800, 0x000A3510},
    {0x0000040B, 0x400D04E0, 0x075FD000, 0x00087390},
    {0x0000040B, 0x400D04E0, 0x075FD000, 0x00087390},
    {0x0000040B, 0x400D04E0, 0x075FD000, 0x00087390},
};
static u8 lbl_1_data_A20 = 3;
static f32 lbl_1_data_A24[4] = {0.0625f, 0.25f, 0.5f, 1.0f};
static f32 lbl_1_data_A34 = 2.0f;
static s32 lbl_1_data_A38 = GX_LIN_MIP_LIN;
static Vec lbl_1_data_A3C = {0.0f, 0.0f, -1.0f};
static Vec lbl_1_data_A48 = {0.0f, 0.0f, -1.0f};
static f32 lbl_1_data_A54[6] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
static u8 lbl_1_data_A6C = 1;
static u8 lbl_1_data_A6D = 1;
static f32 lbl_1_data_A70 = 1.0f;
static f32 lbl_1_data_A74[2][3] = {{0.5f, 0.0f, 0.0f}, {0.0f, 0.5f, 0.0f}};


// .text:0x000085A8 size:0x7C
void fn_1_85A8(void) {
    u16 buttons = INPUT1_FIELD(u16, 4);

    if (buttons & INPUT_BUTTON_LEFT) {
        lbl_1_common_bss_472B4.selected--;
        if (lbl_1_common_bss_472B4.selected < -1) {
            lbl_1_common_bss_472B4.selected = lbl_1_common_bss_472B4.actorCount - 1;
        }
    } else if (buttons & INPUT_BUTTON_RIGHT) {
        lbl_1_common_bss_472B4.selected++;
        if (lbl_1_common_bss_472B4.selected >= lbl_1_common_bss_472B4.actorCount) {
            lbl_1_common_bss_472B4.selected = -1;
        }
    }
}

// .text:0x00008368 size:0x240
void fn_1_8368(void) {
    u16 buttons = INPUT1_FIELD(u16, 4);
    u16 pressed;

    if (buttons & INPUT_BUTTON_LEFT) {
        lbl_1_common_bss_472B4.selected--;
        if (lbl_1_common_bss_472B4.selected < -1) {
            lbl_1_common_bss_472B4.selected = lbl_1_common_bss_472B4.count - 1;
        }
    } else if (buttons & INPUT_BUTTON_RIGHT) {
        lbl_1_common_bss_472B4.selected++;
        if (lbl_1_common_bss_472B4.selected >= lbl_1_common_bss_472B4.count) {
            lbl_1_common_bss_472B4.selected = -1;
        }
    } else {
        pressed = AtBat_ButtonInput1._02;
        if (pressed & INPUT_BUTTON_X) {
            lbl_1_common_bss_472B4.showBoxes ^= 1;
        } else if (pressed & INPUT_BUTTON_A) {
            lbl_1_common_bss_472B4.flag238 ^= 1;
        }
    }

    lbl_1_data_200[0] += (f32)INPUT1_FIELD(s8, 0x10) / 128.0f;
    lbl_1_data_200[2] += (f32)INPUT1_FIELD(s8, 0x11) / 128.0f;
    lbl_1_data_200[3] += (f32)INPUT1_FIELD(s8, 0x12) / 128.0f;
    lbl_1_data_200[5] += (f32)INPUT1_FIELD(s8, 0x13) / 128.0f;

    if (!(AtBat_ButtonInput1._00 & INPUT_BUTTON_A)) {
        lbl_1_data_200[1] -= (f32)INPUT1_FIELD(u8, 0x15) / 1024.0f;
        lbl_1_data_200[1] += (f32)INPUT1_FIELD(u8, 0x14) / 1024.0f;
    } else {
        lbl_1_data_200[4] -= (f32)INPUT1_FIELD(u8, 0x15) / 1024.0f;
        lbl_1_data_200[4] += (f32)INPUT1_FIELD(u8, 0x14) / 1024.0f;
    }
}

// .text:0x00007FF8 size:0x370
void fn_1_7FF8(void) {
    switch (*(u16 *)((u8 *)&AtBat_ButtonInput1 + 4)) {
        case INPUT_BUTTON_UP:
            if (--lbl_1_common_bss_472B4.fogSel < 0) {
                lbl_1_common_bss_472B4.fogSel = 5;
            }
            break;
        case INPUT_BUTTON_DOWN:
            if (++lbl_1_common_bss_472B4.fogSel >= 6) {
                lbl_1_common_bss_472B4.fogSel = 0;
            }
            break;
        case INPUT_BUTTON_LEFT:
            switch (lbl_1_common_bss_472B4.fogSel) {
                case 0: {
                    u8 v = --lbl_1_bss_4E0->color.a;
                    switch (v) {
                        case 0xff:
                            lbl_1_bss_4E0->color.a = 7;
                            break;
                        case 3:
                            lbl_1_bss_4E0->color.a = 2;
                            break;
                        case 1:
                            lbl_1_bss_4E0->color.a = 0;
                            break;
                    }
                    break;
                }
                case 1:
                    lbl_1_bss_4E0->color.r--;
                    break;
                case 2:
                    lbl_1_bss_4E0->color.g--;
                    break;
                case 3:
                    lbl_1_bss_4E0->color.b--;
                    break;
                case 4:
                    if (--lbl_1_bss_4E0->nearZ < 0.0f) {
                        lbl_1_bss_4E0->nearZ = 0.0f;
                    }
                    break;
                case 5:
                    if (--lbl_1_bss_4E0->farZ < 0.0f) {
                        lbl_1_bss_4E0->farZ = 0.0f;
                    }
                    break;
            }
            break;
        case INPUT_BUTTON_RIGHT:
            switch (lbl_1_common_bss_472B4.fogSel) {
                case 0: {
                    u8 v = ++lbl_1_bss_4E0->color.a;
                    switch (v) {
                        case 1:
                            lbl_1_bss_4E0->color.a = 2;
                            break;
                        case 3:
                            lbl_1_bss_4E0->color.a = 4;
                            break;
                        case 8:
                            lbl_1_bss_4E0->color.a = 0;
                            break;
                    }
                    break;
                }
                case 1:
                    lbl_1_bss_4E0->color.r++;
                    break;
                case 2:
                    lbl_1_bss_4E0->color.g++;
                    break;
                case 3:
                    lbl_1_bss_4E0->color.b++;
                    break;
                case 4:
                    if (++lbl_1_bss_4E0->nearZ > 512.0f) {
                        lbl_1_bss_4E0->nearZ = 512.0f;
                    }
                    break;
                case 5:
                    if (++lbl_1_bss_4E0->farZ > 512.0f) {
                        lbl_1_bss_4E0->farZ = 512.0f;
                    }
                    break;
            }
            break;
    }
}

// .text:0x00007EF8 size:0x100
void fn_1_7EF8(void) {
    u16 val = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

    switch (val) {
        case 4:
        case 8:
            lbl_1_bss_C2 = !lbl_1_bss_C2;
            break;
        case 1:
            fn_80048E00(lbl_1_bss_C2, fn_80048EA8(lbl_1_bss_C2) - 1);
            break;
        case 2:
            fn_80048E00(lbl_1_bss_C2, fn_80048EA8(lbl_1_bss_C2) + 1);
            break;
        case 0x100:
            lbl_1_data_85C = !lbl_1_data_85C;
            if (lbl_1_data_85C) {
                fn_80048C14(0x3f);
            } else {
                fn_80048C14(0);
            }
            break;
    }
}

// .text:0x00007E04 size:0xF4
void fn_1_7E04(f32 arg0) {
    Mtx44 frustum;
    f32 inv = 1.0f / arg0;

    C_MTXFrustum(frustum, -0.175f * inv, 0.175f * inv, 0.25f * inv, -0.25f * inv, 1.0f, 512.0f);
    GXSetProjection(frustum, GX_PERSPECTIVE);
    fn_800B806C(0, -240.0f * inv, 240.0f * inv, -320.0f * inv, 320.0f * inv, -512.0f, -1.0f, 1280.0f);
}

// .text:0x00007960 size:0x4A4
void fn_1_7960(void) {
    Mtx rotX;
    Mtx rotY;
    Mtx combined;
    Mtx44 frustum;
    Vec vec;
    Vec templatePt = {0.0f, 0.0f, 100.0f};
    f32 cosY;
    f32 inv;
    f32 sinY;

    lbl_1_common_bss_472B4.yaw -= INPUT1_FIELD(s8, 0x13) * 2;
    lbl_1_common_bss_472B4.pitch += INPUT1_FIELD(s8, 0x12) * 2;
    lbl_1_common_bss_472B4.strafe = (f32)INPUT1_FIELD(s8, 0x10) / -128.0f;
    lbl_1_common_bss_472B4.forward = (f32)INPUT1_FIELD(s8, 0x11) / 128.0f;

    if (AtBat_ButtonInput1._00 & INPUT_TRIGGER_Z) {
        lbl_1_common_bss_472B4.zoom -= (f32)INPUT1_FIELD(u8, 0x14) / 4096.0f;
        lbl_1_common_bss_472B4.zoom += (f32)INPUT1_FIELD(u8, 0x15) / 4096.0f;
    } else {
        lbl_1_common_bss_472B4.eye.y -= (f32)INPUT1_FIELD(u8, 0x15) / 1024.0f;
        lbl_1_common_bss_472B4.eye.y += (f32)INPUT1_FIELD(u8, 0x14) / 1024.0f;
    }

    vec.x = (f32)lbl_1_common_bss_472B4.yaw;
    vec.y = (f32)lbl_1_common_bss_472B4.pitch;
    vec.z = 0.0f;
    PSVECScale(&vec, 0.0000958738f, &vec);
    PSMTXRotRad(rotX, 'X', vec.x);
    PSMTXRotRad(rotY, 'Y', vec.y);
    sinY = rotY[0][2];
    cosY = rotY[0][0];
    PSMTXConcat(rotY, rotX, combined);
    PSMTXMultVec(combined, &templatePt, &lbl_1_common_bss_472B4.target);

    lbl_1_common_bss_472B4.eye.x += lbl_1_common_bss_472B4.forward * sinY - lbl_1_common_bss_472B4.strafe * cosY;
    lbl_1_common_bss_472B4.eye.z += lbl_1_common_bss_472B4.forward * cosY + lbl_1_common_bss_472B4.strafe * sinY;
    lbl_1_common_bss_472B4.target.x += lbl_1_common_bss_472B4.eye.x;
    lbl_1_common_bss_472B4.target.y += lbl_1_common_bss_472B4.eye.y;
    lbl_1_common_bss_472B4.target.z += lbl_1_common_bss_472B4.eye.z;
    makeLookAtMatrix(lbl_1_common_bss_472B4.view, &lbl_1_common_bss_472B4.eye, (Vec *)lbl_1_data_87C,
                     &lbl_1_common_bss_472B4.target);

    inv = lbl_1_common_bss_472B4.zoom;
    inv = 1.0f / inv;
    C_MTXFrustum(frustum, -0.175f * inv, 0.175f * inv, 0.25f * inv, -0.25f * inv, 1.0f, 512.0f);
    GXSetProjection(frustum, GX_PERSPECTIVE);
    fn_800B806C(0, -240.0f * inv, 240.0f * inv, -320.0f * inv, 320.0f * inv, -512.0f, -1.0f, 1280.0f);

    fn_1_54E0(&lbl_1_common_bss_472B4);
    fn_80011640(&lbl_1_common_bss_472B4, &lbl_1_common_bss_472B4);

    if (lbl_1_bss_C0) {
        fn_800B9950(3, (f32)(0xFFFF - lbl_1_common_bss_472B4.pitch) / 32768.0f,
                    (f32)(s16)lbl_1_common_bss_472B4.yaw / 32768.0f);
    } else {
        fn_800B9950(3, 0.0f, 0.0f);
    }
}

// .text:0x000078E4 size:0x7C
void fn_1_78E4(void) {
    GXSetCopyClear(lbl_1_data_858, 0xffffff);
    if (lbl_1_bss_C4) {
        GXSetCullMode(0);
    } else {
        GXSetCullMode(2);
    }
    SetFogNoneAgain();
    GXSetAlphaCompare(4, 0, 0, 7, 0);
}

// .text:0x0000786C size:0x78
void fn_1_786C(void) {
    fn_80048D4C();
    GXSetCopyClear(lbl_1_data_858, 0xffffff);
    SetFog(lbl_1_bss_4E0->color.a, lbl_1_bss_4E0->color, lbl_1_bss_4E0->nearZ, lbl_1_bss_4E0->farZ, 1.0f, 512.0f);
}

// .text:0x00007848 size:0x24
void fn_1_7848(void) {
    fn_80048C28();
    fn_80048C1C();
}

// .text:0x000077EC size:0x5C
void fn_1_77EC(void *arg0) {
    GXSetCullMode(lbl_1_data_8C4);
    fn_1_73B8(arg0, 3, lbl_1_data_848[0], lbl_1_data_848[1], lbl_1_data_848[2]);
}

// .text:0x000073B8 size:0x434
void fn_1_73B8(void *arg0, u8 count, ...) {
    Mtx concat;
    f32 box[24];
    DbgGeoTable *table;
    DbgActorSet *set;
    DbgGeo *geo;
    MtxPtr cam1;
    s16 sel;
    MtxPtr cam2;
    s32 i;
    s32 end;
    u16 key;

    set = ((DbgDrawNode *)arg0)->model;
    table = set->geoTable;
    if (lbl_1_data_8C8 == 1) {
        memset(lbl_1_bss_2E0, 0, sizeof(lbl_1_bss_2E0));
        lbl_1_data_8C8 = 0;
    } else if (lbl_1_data_8C8 == 2) {
        memset(lbl_1_bss_2E0, 1, sizeof(lbl_1_bss_2E0));
        lbl_1_data_8C8 = 0;
    }

    end = set->count;
    sel = lbl_1_common_bss_472B4.selected;
    lbl_1_common_bss_472B4.visibleCount = 0;
    if (sel < 0) {
        i = 0;
    } else {
        i = sel;
        end = sel + 1;
    }

    cam1 = ((DbgDrawNode *)arg0)->local;
    cam2 = ((DbgDrawNode *)arg0)->world;
    for (; i < end; i++) {
        if (lbl_1_bss_2E0[i] != 0) {
            continue;
        }
        key = set->entries[i].geoKey;
        if (key == 0xFFFF) {
            continue;
        }

        if (set->entries[i].flags & 1) {
            GXSetZMode(0, 7, 1);
        } else {
            GXSetZMode(1, 3, 1);
        }
        switch (set->entries[i].flags & 6) {
            case 2:
                GXSetBlendMode(1, 1, 1, 0);
                break;
            case 4:
                GXSetBlendMode(1, 2, 0, 0);
                break;
            default:
                GXSetBlendMode(1, 4, 5, 0);
                break;
        }

        geo = table->slots[key].geo;
        CTRLBuildMatrix(set->entries[i].ctrl, geo->mtx);
        PSMTXConcat(cam1, geo->mtx, geo->mtx);
        PSMTXConcat(cam2, geo->mtx, concat);

        box[0] = geo->maxX;
        box[1] = geo->maxY;
        box[2] = geo->minZ;
        box[3] = geo->minX;
        box[4] = geo->maxY;
        box[5] = geo->minZ;
        box[6] = geo->minX;
        box[7] = geo->maxY;
        box[8] = geo->maxZ;
        box[9] = geo->maxX;
        box[10] = geo->maxY;
        box[11] = geo->maxZ;
        box[12] = geo->maxX;
        box[13] = geo->minY;
        box[14] = geo->minZ;
        box[15] = geo->minX;
        box[16] = geo->minY;
        box[17] = geo->minZ;
        box[18] = geo->minX;
        box[19] = geo->minY;
        box[20] = geo->maxZ;
        box[21] = geo->maxX;
        box[22] = geo->minY;
        box[23] = geo->maxZ;

        if (checkObjectVisibility(0, box, concat)) {
            va_list args;
            lbl_1_common_bss_472B4.visibleCount++;
            va_start(args, count);
            DOVARender(geo, cam2, count, args);
        }
    }

    if (lbl_1_bss_C1 != 0) {
        sel = lbl_1_common_bss_472B4.selected;
        end = set->count;
        if (sel < 0) {
            i = 0;
        } else {
            i = sel;
            end = sel + 1;
        }

        for (; i < end; i++) {
            if (lbl_1_bss_2E0[i] != 0) {
                continue;
            }
            key = set->entries[i].geoKey;
            if (key == 0xFFFF) {
                continue;
            }

            geo = table->slots[key].geo;
            CTRLBuildMatrix(set->entries[i].ctrl, geo->mtx);
            PSMTXConcat(cam1, geo->mtx, geo->mtx);
            PSMTXConcat(cam2, geo->mtx, concat);

            box[0] = geo->maxX;
            box[1] = geo->maxY;
            box[2] = geo->minZ;
            box[3] = geo->minX;
            box[4] = geo->maxY;
            box[5] = geo->minZ;
            box[6] = geo->minX;
            box[7] = geo->maxY;
            box[8] = geo->maxZ;
            box[9] = geo->maxX;
            box[10] = geo->maxY;
            box[11] = geo->maxZ;
            box[12] = geo->maxX;
            box[13] = geo->minY;
            box[14] = geo->minZ;
            box[15] = geo->minX;
            box[16] = geo->minY;
            box[17] = geo->minZ;
            box[18] = geo->minX;
            box[19] = geo->minY;
            box[20] = geo->maxZ;
            box[21] = geo->maxX;
            box[22] = geo->minY;
            box[23] = geo->maxZ;

            if (checkObjectVisibility(0, box, concat)) {
                fn_1_4E98(geo, cam2);
            }
        }
    }
}

// .text:0x00007280 size:0x138
void fn_1_7280(void) {
    DbgDrawNode *node = &lbl_1_common_bss_472B4.nodes[drawStadiumRelated];
    DbgDrawNode *node2;

    PSMTXCopy(lbl_1_common_bss_472B4.view, node->world);
    fn_800A7D4C(0, &lbl_1_data_8B4[drawStadiumRelated]);
    fn_800A7D4C(0, node);
    fn_800A7D4C(0, &lbl_1_data_8A4[drawStadiumRelated]);

    node2 = &lbl_1_common_bss_472B4.nodes2[drawStadiumRelated];
    PSMTXRotRad(node2->local, 'Y', 0.0000958738f * (f32)lbl_1_common_bss_472B4.angle);
    PSMTXCopy(lbl_1_common_bss_472B4.view, node2->world);
    fn_800A7D4C(0, node2);
    fn_800A7D4C(0, &lbl_1_data_88C[drawStadiumRelated]);
}

// .text:0x0000717C size:0x104
void fn_1_717C(u8 *arg0) {
    void *geo;
    u8 *tex;
    DbgActorSet *set;

    set = (DbgActorSet *)(arg0 + *(s32 *)(arg0 + 0x0));
    geo = arg0 + *(s32 *)(arg0 + 0xc);
    tex = arg0 + *(s32 *)(arg0 + 0x14);

    fn_1_4DD8(arg0 + *(s32 *)(arg0 + 0x8));
    AdjustActorPointers(set);
    AdjustGEOPalettePointers(geo);
    convertTextureHeader(tex);
    lbl_1_common_bss_472B4.texHeader = tex + 4;
    UpdateTexturePalettePointers(geo, tex);
    haveActLayoutPointToGeoHeader(set, geo);
    lbl_1_common_bss_472B4.actorCount = set->count;
    lbl_1_common_bss_472B4.nodes[1].model = set;
    lbl_1_common_bss_472B4.nodes[0].model = set;

    set = (DbgActorSet *)(arg0 + *(s32 *)(arg0 + 0x4));
    geo = arg0 + *(s32 *)(arg0 + 0x10);
    AdjustActorPointers(set);
    AdjustGEOPalettePointers(geo);
    UpdateTexturePalettePointers(geo, tex);
    haveActLayoutPointToGeoHeader(set, geo);
    lbl_1_common_bss_472B4.nodes2[1].model = set;
    lbl_1_common_bss_472B4.nodes2[0].model = set;
}

// .text:0x00006E14 size:0x368
void fn_1_6E14(void) {
    u16 buttons;

    fn_1_7960();

    if (lbl_1_common_bss_472B4.flag238 == 0) {
        fn_1_7280();
    } else {
        fn_1_196C();
    }

    buttons = AtBat_ButtonInput1._02;
    if (buttons & INPUT_BUTTON_MENU) {
        SetFogNoneAgain();
        currentDrawingItem->func = fn_1_66C4;
    } else if (buttons & INPUT_BUTTON_B) {
        lbl_1_common_bss_472B4.runHandler = 0;
        lbl_1_common_bss_472B4.flag238 = 0;
        lbl_1_common_bss_472B4.menuOpen ^= 1;
        lbl_1_common_bss_472B4.selected = -1;
    }

    if (lbl_1_common_bss_472B4.menuOpen != 0) {
        switch (*(u16 *)((u8 *)&AtBat_ButtonInput1 + 4)) {
            case INPUT_BUTTON_UP:
                if (--lbl_1_common_bss_472B4.menuSel < 0) {
                    lbl_1_common_bss_472B4.menuSel = 7;
                }
                break;
            case INPUT_BUTTON_DOWN:
                if (++lbl_1_common_bss_472B4.menuSel >= 8) {
                    lbl_1_common_bss_472B4.menuSel = 0;
                }
                break;
            case INPUT_BUTTON_A:
                switch (lbl_1_common_bss_472B4.menuSel) {
                    case 0:
                        lbl_1_common_bss_472B4.runHandler = 1;
                        lbl_1_common_bss_472B4.menuOpen = 0;
                        break;
                    case 1:
                        lbl_1_common_bss_472B4.selected = -1;
                        lbl_1_common_bss_472B4.runHandler = 1;
                        lbl_1_common_bss_472B4.menuOpen = 0;
                        break;
                    case 2:
                        lbl_1_common_bss_472B4.runHandler = 1;
                        lbl_1_common_bss_472B4.menuOpen = 0;
                        break;
                    case 3:
                        lbl_1_common_bss_472B4.runHandler = 1;
                        lbl_1_common_bss_472B4.menuOpen = 0;
                        break;
                    case 4:
                        lbl_1_common_bss_472B4.flag234 ^= 1;
                        break;
                    case 5:
                        lbl_1_common_bss_472B4.runHandler = 1;
                        lbl_1_common_bss_472B4.menuOpen = 0;
                        break;
                    case 6:
                        lbl_1_bss_C0 ^= 1;
                        break;
                    case 7:
                        lbl_1_bss_C1 ^= 1;
                        break;
                }
                break;
        }
    }

    if (lbl_1_common_bss_472B4.runHandler != 0) {
        lbl_1_data_860[lbl_1_common_bss_472B4.menuSel]();
    }

    if (lbl_1_bss_C0) {
        fn_800B996C(fn_1_5544);
    } else {
        fn_800B996C(0);
    }
}

// .text:0x00006848 size:0x5CC
void fn_1_6848(void) {
    StadiumViewScene *item = (StadiumViewScene *)currentDrawingItem;

    switch (item->state) {
        case 0:
            setLITLightPtr(0);
            fn_1_6578(&lbl_1_bss_4E4, lbl_1_bss_520, lbl_1_data_854, lbl_1_data_854);
            fn_800B996C(fn_1_5544);

            LITAlloc(&lbl_1_data_848[0]);
            LITAlloc(&lbl_1_data_848[1]);
            LITAlloc(&lbl_1_data_848[2]);

            {
                GXColor colors[3] = {{0xFF, 0x00, 0x00, 0xFF}, {0x00, 0x00, 0xFF, 0xFF}, {0x00, 0xFF, 0x00, 0xFF}};

                LITInitAttn(lbl_1_data_848[0], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
                LITInitPos(lbl_1_data_848[0], 10000.0f, -200.0f, 0.0f);
                LITInitDir(lbl_1_data_848[0], 0.0f, 0.0f, 0.0f);
                LITInitColor(lbl_1_data_848[0], colors[0]);

                LITInitAttn(lbl_1_data_848[1], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
                LITInitPos(lbl_1_data_848[1], 0.0f, -200.0f, 10000.0f);
                LITInitDir(lbl_1_data_848[1], 0.0f, 0.0f, 0.0f);
                LITInitColor(lbl_1_data_848[1], colors[1]);

                LITInitAttn(lbl_1_data_848[2], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
                LITInitPos(lbl_1_data_848[2], 10000.0f, -200.0f, 10000.0f);
                LITInitDir(lbl_1_data_848[2], 0.0f, 0.0f, 0.0f);
                LITInitColor(lbl_1_data_848[2], colors[2]);
            }

            item->state = 1;
        /* fallthrough */
        case 1:
            switch (*(u16 *)((u8 *)&AtBat_ButtonInput1 + 4)) {
                case INPUT_BUTTON_UP:
                    if (--lbl_1_common_bss_472B4.stadium < 0) {
                        lbl_1_common_bss_472B4.stadium = lbl_1_data_8CC - 1;
                    }
                    break;
                case INPUT_BUTTON_DOWN:
                    if (++lbl_1_common_bss_472B4.stadium >= lbl_1_data_8CC) {
                        lbl_1_common_bss_472B4.stadium = 0;
                    }
                    break;
                case INPUT_BUTTON_B:
                    if (++lbl_1_common_bss_472B4.variant > 2) {
                        lbl_1_common_bss_472B4.variant = 0;
                    }
                    break;
                case INPUT_BUTTON_A:
                    item->state = 2;
                    break;
                case INPUT_BUTTON_START:
                    fn_800B996C(NULL);
                    item->parent->state = 1;
                    break;
            }
            break;

        case 2:
            item->index = lbl_1_common_bss_472B4.stadium * 3 + lbl_1_common_bss_472B4.variant;
            item->model = ARAMTransfer(&lbl_1_data_8D0[item->index], 0, 0, 0);
            item->state = 3;
            lbl_1_bss_4E0 = (FogParams1_4E0 *)((u8 *)lbl_1_data_2A8 + lbl_1_common_bss_472B4.stadium * 0x60 +
                                               lbl_1_common_bss_472B4.variant * 0xc);
            break;

        case 3:
            if ((s8)lbl_803C6CF8[0x715] != 1) {
                break;
            }
            fn_1_717C(item->model);
            DCFlushRangeNoSync(item->model, ((u32 *)&lbl_1_data_8D0[item->index])[1] & 0x0FFFFFFF);
            currentDrawingItem->func = fn_1_6E14;
            break;
    }
}

// .text:0x000066C4 size:0x184
void fn_1_66C4(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    DbgViewState *state;
    s32 stadium;
    s32 variant;

    fn_800AD038(*(void **)(lbl_80366158 + 0x8));
    item->state = 0;

    state = &lbl_1_common_bss_472B4;
    stadium = state->stadium;
    variant = state->variant;
    memset(state, 0, 0x240);
    state->stadium = stadium;
    state->variant = variant;

    lbl_1_common_bss_472B4.dlBuf = _OSAllocFromHeap(0x20, 0x80000);
    lbl_1_common_bss_472B4.eye.y = -6.0f;
    lbl_1_common_bss_472B4.eye.z = -10.666667f;
    lbl_1_common_bss_472B4.yaw = -0xc94;
    lbl_1_common_bss_472B4.zoom = 0.63f;
    lbl_1_common_bss_472B4.selected = -1;
    lbl_1_common_bss_472B4.flag234 = 0;
    PSMTXIdentity(lbl_1_common_bss_472B4.nodes[0].local);

    lbl_1_common_bss_472B4.nodes[0].draw = fn_1_77EC;
    lbl_1_common_bss_472B4.nodes[1] = lbl_1_common_bss_472B4.nodes[0];
    lbl_1_common_bss_472B4.nodes2[0].draw = (void (*)(void *))renderingRelated;
    lbl_1_common_bss_472B4.nodes2[1] = lbl_1_common_bss_472B4.nodes2[0];

    currentDrawingItem->func = fn_1_6848;
}

// .text:0x00006578 size:0x14C
void fn_1_6578(GXTexObj *arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 minFilter;
    s32 levelW = arg2;
    s32 levelH = arg3;
    s32 offset = 0;
    s32 i;

    if (lbl_1_data_A20 == 0) {
        arg2 /= 4;
        arg3 /= 4;
        fn_1_6050(arg1, arg2, arg3, 1.0f);
        minFilter = GX_LINEAR;
    } else {
        for (i = 0; i <= lbl_1_data_A20; i++) {
            fn_1_6050((u8 *)arg1 + offset * 2, levelW, levelH, lbl_1_data_A24[i]);
            offset += levelW * levelH;
            levelW /= 2;
            levelH /= 2;
        }
        minFilter = lbl_1_data_A38;
    }

    GXInitTexObj(arg0, arg1, (u16)arg2, (u16)arg3, 3, 1, 1, lbl_1_data_A20);
    GXInitTexObjLOD(arg0, minFilter, 1, 0.0f, (f32)lbl_1_data_A20, lbl_1_data_A34, 0, 0, 0);
}

// .text:0x00006050 size:0x528
#pragma dont_inline on
void fn_1_6050(void *arg0, s32 arg1, s32 arg2, f32 arg3) {
    u16 *buf = (u16 *)arg0;
    s32 w = arg1;
    s32 h = arg2;
    s32 y;
    s32 x;
    f32 ny2;
    f32 uAngle;
    f32 nx;
    f32 ny;
    f32 nxUv;
    f32 nyUv;
    f32 vAngle;
    f32 d;

    memset(arg0, 0, w * 2 * h);

    for (y = 0; y < h; y++) {
        ny = 2.0f * ((f32)y / (f32)h - 0.5f);
        nyUv = ny / 2 + 0.5f;
        ny2 = ny * ny;

        for (x = 0; x < w; x++) {
            Vec vec;
            Vec xz;
            Vec cross;

            nx = 2.0f * ((f32)x / (f32)w - 0.5f);
            nxUv = nx / 2 + 0.5f;

            if (y == h / 2) {
                d = 1.0f - nx * nx;
            } else {
                d = (1.0f - nx * nx) - ny2;
            }

            if (d < 0.0f) {
                vec.x = nx;
                vec.y = ny;
                vec.z = 0.0f;
                PSVECNormalize(&vec, &vec);
            } else {
                vec.z = -sqrt(d);
                vec.x = nx;
                vec.y = ny;
            }

            if (arg3 != 1.0f) {
                PSVECCrossProduct(&lbl_1_data_A3C, &vec, &cross);
                if (PSVECMag(&cross)) {
                    f32 half;
                    f32 s;
                    f32 c;
                    Quaternion quat;
                    Mtx mtx;

                    PSVECNormalize(&cross, &cross);
                    half = (f32)acos(PSVECDotProduct(&lbl_1_data_A3C, &vec));
                    half = half * arg3 / 2;
                    s = sin(half);
                    c = cos(half);
                    quat.x = cross.x * s;
                    quat.y = cross.y * s;
                    quat.z = cross.z * s;
                    quat.w = c;
                    PSMTXQuat(mtx, &quat);
                    PSMTXMultVec(mtx, &lbl_1_data_A3C, &vec);
                }
            }

            xz.x = vec.x;
            xz.y = 0.0f;
            xz.z = vec.z;

            if (!PSVECMag(&xz)) {
                vAngle = 0.0f;
                uAngle = vAngle;
            } else {
                PSVECNormalize(&xz, &xz);
                if (ny == 0.0f) {
                    uAngle = 0.5f;
                } else {
                    uAngle = acos(PSVECDotProduct(&xz, &vec));
                    PSVECCrossProduct(&xz, &vec, &cross);
                    if (!PSVECMag(&cross)) {
                        uAngle = 0.0f;
                    } else if (cross.x < 0.0f) {
                        uAngle = -uAngle;
                    }
                    uAngle /= 3.1415927f;
                    uAngle += 0.5f;
                }
                if (nx == 0.0f) {
                    vAngle = 0.5f;
                } else {
                    vAngle = acos(PSVECDotProduct(&lbl_1_data_A3C, &xz));
                    PSVECCrossProduct(&lbl_1_data_A3C, &xz, &cross);
                    if (!PSVECMag(&cross)) {
                        vAngle = 0.0f;
                    } else if (cross.y > 0.0f) {
                        vAngle = -vAngle;
                    }
                    vAngle /= 3.1415927f;
                    vAngle += 0.5f;
                }
                vAngle -= nxUv;
                uAngle -= nyUv;
            }

            buf[fn_1_5924(w, x, y, 0x10, 0)] =
                ((u8)(s32)(128.0f * vAngle + 128.0f) << 8) | (u8)(s32)(128.0f * uAngle + 128.0f);
        }
    }

    DCFlushRange(arg0, w * 2 * h);
}
#pragma dont_inline reset

// .text:0x00005AC0 size:0x590
void fn_1_5AC0(void *arg0, s32 arg1, s32 arg2, f32 arg3) {
    u16 *buf = (u16 *)arg0;
    s32 w = arg1;
    s32 h = arg2;
    s32 yBand;
    s32 halfH;
    u8 band;
    s32 y;
    s32 x;
    f32 uAngle;
    f32 vAngle;
    f32 nx;
    f32 ny;
    f32 nxUv;
    f32 nyUv;
    f32 d;

    memset(arg0, 0, w * 2 * h);
    halfH = h / 2;

    for (y = 0; y < h; y++) {
        x = 0;
        ny = 2.0f * ((f32)y / (f32)h - 0.5f);
        nyUv = ny / 2 + 0.5f;
        yBand = (ny > 0.2f) & (ny < 0.8f);

        for (; x < w; x++) {
            Vec vec;
            Vec xz;
            Vec cross;

            nx = 2.0f * ((f32)x / (f32)w - 0.5f);
            nxUv = nx / 2 + 0.5f;
            band = (nx < 0.8f) & ((nx > 0.2f) & yBand);

            if (y == halfH) {
                d = 1.0f - nx * nx;
            } else {
                d = (1.0f - nx * nx) - ny * ny;
            }

            if (d < 0.0f) {
                vec.x = nx;
                vec.y = ny;
                vec.z = 0.0f;
                PSVECNormalize(&vec, &vec);
            } else {
                vec.z = -sqrt(d);
                vec.x = nx;
                vec.y = ny;
            }

            if (band && arg3 != 1.0f) {
                PSVECCrossProduct(&lbl_1_data_A48, &vec, &cross);
                if (PSVECMag(&cross)) {
                    f32 c;
                    Quaternion quat;
                    Mtx mtx;

                    PSVECNormalize(&cross, &cross);
                    uAngle = (f32)acos(PSVECDotProduct(&lbl_1_data_A48, &vec));
                    uAngle = uAngle * arg3 / 2;
                    vAngle = sin(uAngle);
                    c = cos(uAngle);
                    quat.x = cross.x * vAngle;
                    quat.y = cross.y * vAngle;
                    quat.z = cross.z * vAngle;
                    quat.w = c;
                    PSMTXQuat(mtx, &quat);
                    PSMTXMultVec(mtx, &lbl_1_data_A48, &vec);
                }
            }

            xz.x = vec.x;
            xz.y = 0.0f;
            xz.z = vec.z;

            if (!PSVECMag(&xz)) {
                vAngle = 0.0f;
                uAngle = vAngle;
            } else {
                PSVECNormalize(&xz, &xz);
                if (ny == 0.0f) {
                    uAngle = 0.5f;
                } else {
                    uAngle = acos(PSVECDotProduct(&xz, &vec));
                    PSVECCrossProduct(&xz, &vec, &cross);
                    if (!PSVECMag(&cross)) {
                        uAngle = 0.0f;
                    } else if (cross.x < 0.0f) {
                        uAngle = -uAngle;
                    }
                    uAngle /= 3.1415927f;
                    uAngle += 0.5f;
                }
                if (nx == 0.0f) {
                    vAngle = 0.5f;
                } else {
                    vAngle = acos(PSVECDotProduct(&lbl_1_data_A48, &xz));
                    PSVECCrossProduct(&lbl_1_data_A48, &xz, &cross);
                    if (!PSVECMag(&cross)) {
                        vAngle = 0.0f;
                    } else if (cross.y > 0.0f) {
                        vAngle = -vAngle;
                    }
                    vAngle /= 3.1415927f;
                    vAngle += 0.5f;
                }
                vAngle -= nxUv;
                uAngle -= nyUv;
            }

            buf[fn_1_5924(w, x, y, 0x10, 0)] =
                ((u8)(s32)(128.0f * vAngle + 128.0f) << 8) | (u8)(s32)(128.0f * uAngle + 128.0f);
        }
    }

    DCFlushRange(arg0, w * 2 * h);
}

// .text:0x00005924 size:0x19C
s32 fn_1_5924(s32 w, s32 x, s32 y, s32 bpp, s32 flag) {
    switch (bpp) {
        case 4:
            w = (y / 8) * w;
            return (x / 8) * 32 + w * 8 + (y % 8) * 8 + x % 8;
        case 8:
            w = (y / 4) * w;
            return (x / 8) * 32 + w * 4 + (y % 4) * 8 + x % 8;
        case 0x10:
            w = (y / 4) * w;
            return (x / 4) * 16 + w * 4 + (y % 4) * 4 + x % 4;
        case 0x20: {
            s32 result;
            w = (y / 4) * w;
            result = (x / 8) * 16 + w * 4 + (y % 4) * 8 + x % 4;
            if (flag != 0) {
                result += 0x10;
            }
            return result;
        }
    }
}

// .text:0x00005698 size:0x28C
void fn_1_5698(void) {
    Mtx44 ortho;
    Mtx posMtx;

    C_MTXOrtho(ortho, 0.0f, 448.0f, 0.0f, 640.0f, -0.0f, -0.5f);
    GXSetProjection(ortho, GX_ORTHOGRAPHIC);
    PSMTXIdentity(posMtx);
    GXLoadPosMtxImm(posMtx, 0);
    GXSetCurrentMtx(0);
    GXSetZMode(1, 7, 0);
    GXSetBlendMode(1, 4, 5, 0);
    GXSetCullMode(0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xd, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xd, 1, 2, 2);
    GXSetNumChans(0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(0, 1, 4, 0x3c, 0, 0x7d);
    GXSetTevColorIn(0, 0xf, 0xf, 0xf, 8);
    GXSetTevColorOp(0, 0, 0, 0, 1, 0);
    GXSetTevAlphaIn(0, 7, 7, 7, 4);
    GXSetTevAlphaOp(0, 0, 0, 0, 1, 0);
    GXSetTevOrder(0, 0, 0, 0xff);
    GXLoadTexObj(&lbl_1_bss_4E4, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 100.0f, 0.0f);
    GXTexCoord2u16(0, 0);
    GXPosition3f32(0.0f, 356.0f, 0.0f);
    GXTexCoord2u16(0, 4);
    GXPosition3f32(256.0f, 356.0f, 0.0f);
    GXTexCoord2u16(4, 4);
    GXPosition3f32(256.0f, 100.0f, 0.0f);
    GXTexCoord2u16(4, 0);
    GXSetNumIndStages(0);
    GXSetTevDirect(0);
}

// .text:0x00005544 size:0x154
void fn_1_5544(s32 stage, s32 indStage, s32 indMtx, s32 coord, s32 map) {
    u8 mode;

    GXLoadTexObj(&lbl_1_bss_4E4, map);
    mode = lbl_1_bss_DC;
    if (mode != 0) {
        if (mode & 2) {
            map--;
        }
        if (mode & 4) {
            coord--;
        }
        GXSetTevOrder(stage, coord, map, 0xff);
        GXSetTevColorIn(stage, 0xf, 0xf, 0xf, 8);
        GXSetTevColorOp(stage, 0, 0, 0, 1, 0);
        GXSetTevAlphaIn(stage, 7, 7, 7, 4);
        GXSetTevAlphaOp(stage, 0, 0, 0, 1, 0);
    } else {
        GXSetNumIndStages(1);
        GXSetIndTexMtx(indMtx, lbl_1_data_A74, (s8)lbl_1_data_A70);
        GXSetIndTexOrder(indStage, coord, map);
        GXSetIndTexCoordScale(indStage, lbl_1_bss_D8, lbl_1_bss_D4);
        GXSetTevIndWarp(stage, indStage, lbl_1_data_A6D, lbl_1_bss_D1, indMtx);
    }
}

// .text:0x00005540 size:0x4
void fn_1_5540(void) {
    return;
}

// .text:0x000054E0 size:0x60
void fn_1_54E0(void *arg0) {
    s32 i;
    for (i = 0; i < 3; i++) {
        LITXForm(lbl_1_data_848[i], arg0);
    }
}

// .text:0x00004E98 size:0x648
#pragma dont_inline on
void fn_1_4E98(void *arg0, void *arg1) {
    DbgGeo *geo = (DbgGeo *)arg0;
    Mtx concat;
    s32 attrType[21];
    f32 vx, vy, vz;
    s32 nrmIdx;
    s32 posIdx;
    s32 vcount;
    s32 i;
    u32 consumed;
    u8 *stream;

    if (geo->nrm == NULL || geo->pos == NULL || geo->dl == NULL) {
        return;
    }

    GXSetZMode(1, 7, 0);
    GXSetBlendMode(1, 4, 5, 0);
    GXSetCullMode(0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xb, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xb, 1, 5, 0);
    GXSetNumChans(1);
    GXSetNumTevStages(1);
    GXSetNumTexGens(0);
    GXSetTevOp(0, 4);
    PSMTXConcat((MtxPtr)arg1, geo->mtx, concat);
    GXLoadPosMtxImm(concat, 0);
    GXSetCurrentMtx(0);

    for (i = 0; i < geo->dl->count; i++) {
        switch (geo->dl->entries[i].cmd) {
            case 0:
            case 1:
                break;
            case 2: {
                u32 flags;
                s32 j;
                s32 shift;

                memset(attrType, 0, sizeof(attrType));
                flags = geo->dl->entries[i].attrFlags;
                for (j = 9, shift = 2; j < 21; j++, shift += 2) {
                    s32 v = (flags >> shift) & 3;
                    if (v != 0) {
                        attrType[j] = v;
                    }
                }
                break;
            }
        }

        stream = geo->dl->entries[i].stream;
        if (stream != NULL) {

            consumed = 0;
            while (consumed < geo->dl->entries[i].size) {
                s32 handled = 0;

                switch (*stream) {
                    case 0:
                        handled = 1;
                        stream += 1;
                        consumed += 1;
                        break;
                    case 0x61:
                        handled = 1;
                        stream += 5;
                        consumed += 5;
                        break;
                    case 8:
                        handled = 1;
                        stream += 6;
                        consumed += 6;
                        break;
                    case 0x10: {
                        s32 adv = *(u16 *)stream * 4 + 5;
                        handled = 1;
                        stream += adv;
                        consumed += adv;
                        break;
                    }
                    case 0x20:
                    case 0x28:
                    case 0x30:
                    case 0x38:
                        handled = 1;
                        stream += 5;
                        break;
                    case 0x40:
                    case 0x48:
                        handled = 1;
                        stream += 1;
                        consumed += 1;
                        break;
                    case 0x80:
                    case 0x90:
                    case 0x98:
                    case 0xa0:
                    case 0xa8:
                    case 0xb0:
                    case 0xb8:
                        break;
                }

                if (handled == 0) {
                    vcount = *(u16 *)(stream + 1);

                    stream += 3;
                    consumed += 3;
                    GXBegin(GX_LINES, GX_VTXFMT0, vcount * 2);

                    while (vcount-- != 0) {
                        s32 k;
                        s32 attr;
                        DbgVtxArray *arr;
                        u8 format;
                        u8 stride;
                        f32 scale;

                        for (k = 0, attr = 9; k < 12; k++, attr++) {
                            s32 t = attrType[attr];
                            if (t != 0) {
                                switch (attr) {
                                    case 9:
                                        switch (t) {
                                            case 1:
                                                break;
                                            case 2:
                                                posIdx = stream[0];
                                                break;
                                            case 3:
                                                posIdx = *(u16 *)stream;
                                                break;
                                        }
                                        break;
                                    case 10:
                                        switch (t) {
                                            case 1:
                                                break;
                                            case 2:
                                                nrmIdx = stream[0];
                                                break;
                                            case 3:
                                                nrmIdx = *(u16 *)stream;
                                                break;
                                        }
                                        break;
                                }
                                switch (t) {
                                    case 2:
                                        stream += 1;
                                        consumed += 1;
                                        break;
                                    case 3:
                                        stream += 2;
                                        consumed += 2;
                                        break;
                                }
                            }
                        }

                        arr = geo->pos;
                        format = arr->format;
                        stride = arr->stride;
                        scale = 1 << (format & 0xf);
                        switch ((format >> 4) & 0xf) {
                            case 3: {
                                s16 *p = arr->data;
                                p += stride * posIdx;
                                vx = p[0] / scale;
                                vy = p[1] / scale;
                                vz = p[2] / scale;
                                break;
                            }
                        }
                        GXWGFifo.f32 = vx;
                        GXWGFifo.f32 = vy;
                        GXWGFifo.f32 = vz;
                        GXWGFifo.u32 = 0xff0000ff;

                        arr = geo->nrm;
                        format = arr->format;
                        stride = arr->stride;
                        scale = 1 << (format & 0xf);
                        switch ((format >> 4) & 0xf) {
                            case 3: {
                                s16 *p = arr->data;
                                p += stride * nrmIdx;
                                vx += p[0] / scale;
                                vy += p[1] / scale;
                                vz += p[2] / scale;
                                break;
                            }
                        }
                        GXWGFifo.f32 = vx;
                        GXWGFifo.f32 = vy;
                        GXWGFifo.f32 = vz;
                        GXWGFifo.u32 = 0xffff;
                    }
                }
            }
        }
    }
}
#pragma dont_inline reset

// .text:0x00004DD8 size:0xC0
#pragma dont_inline on
void fn_1_4DD8(void *arg0) {
    DbgOffsetTable *table = arg0;
    u32 *p;
    s32 i;

    lbl_1_common_bss_472B4.count = table->count;
    lbl_1_common_bss_472B4.list = table->offsets;
    p = table->offsets;
    for (i = (s16)table->count; i >= 0; i--) {
        *p++ += (u32)table;
    }
}
#pragma dont_inline reset
