#define REP_HEADER_DATA_FN getRepHeaderData_rep7730
#define SQRT2_LINKAGE static
#include "game/UnknownHomes_Game.h"
#include "debug/rep_7730.h"
#include "Unknown/File_0x800a7568.h"
#include "header_rep_data.h"
#include "Unknown/File_0x800b0a14.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/GX/GXGeometry.h"
#include "Dolphin/GX/GXLight.h"
#include "Dolphin/GX/GXTev.h"
#include "Dolphin/GX/GXTransform.h"
#include "Dolphin/GX/GXTexture.h"
#include "Dolphin/GX/GXFifo.h"
#include "Dolphin/GX/GXFrameBuffer.h"
#include "Dolphin/mtx.h"
#include "Dolphin/mtxext.h"
#include "Dolphin/os.h"
#include "C3/control.h"
#include "stl/math.h"
#include "Unknown/sub.h"
#include "Dolphin/GX/GXPixel.h"
#include "stl/mem.h"
#include "Dolphin/rand.h"
#include "text/text_channel.h"
#include "Unknown/File_0x800363d8.h"
#include "Unknown/File_0x80034e20.h"

#define GFX_OBJ(item) \
    ((u8 *)graphicsRelatedArray[*(u16 *)(*(u8 **)((u8 *)(item) + 0x14) + 0x14)].object)

extern void *ARAMTransfer(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern void fn_80037B18(void *arg0, void *arg1, f32 arg2);
extern void fn_1_272DC(void *arg0, s32 arg1);
extern void fn_1_AF4(s32 arg0, s32 arg1, f32 arg2);
extern void fn_80048C14(s32 arg0);
extern void fn_80048E00(s32 arg0, s32 arg1);
extern void fn_800AD038(void *arg0);
extern s32 fn_800B24D4(s32 arg0);
extern void fn_800B1188(void);
extern void fn_800A7D4C(s32 arg0, void *arg1);
extern s32 diskReadRelated(void *arg0, s32 arg1);
extern s32 fn_80035DD4(s32 arg0);
extern void fn_800385F0(void *buf, f32 a, f32 b, f32 c, f32 d);
extern void fn_1_273D8(void *arg0);

extern u8 lbl_80366158[0x30];
extern u8 drawStadiumRelated;
extern void removeGraphicsElementFromScene(void *arg0);
extern void fn_80035A00(void);
extern void fn_80038E2C(void *arg0);
extern void fn_80048C1C(void);
extern void fn_80048D4C(void);
extern void fn_80048C28(void);

extern void LITAlloc(void *slot);
extern void LITInitAttn(void *light, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
extern void LITInitPos(void *light, f32 arg1, f32 arg2, f32 arg3);
extern void LITInitDir(void *light, f32 arg1, f32 arg2, f32 arg3);
extern void LITInitColor(void *light, GXColor *color);
extern void *ActorObjectInitTable(s32 arg0, u32 arg1, void *arg2);
extern void LoadActorLayout(void *arg0);
extern void convertGeometryAndSknHeader(void *arg0, s32 arg1);
extern void animateBallRelated(void *arg0, u16 arg1, u16 arg2, void *arg3, s32 arg4, s32 arg5);
extern void fn_800B2C08(void *arg0, s32 arg1);
extern void fn_800BD548(void *arg0, s32 arg1, ...);
extern void haveActLayoutPointToGeoHeader(void *arg0, void *arg1);

extern void fn_1_26D28(void *arg0, u16 arg1, u16 arg2, u16 arg3, void *arg4);
extern void fn_1_27330(void *arg0);
extern void fn_80037BAC(void *arg0);
extern s32 fn_80048EA8(s32 arg0);
extern void fn_80038B48(void *arg0, void *arg1, s32 arg2, void *arg3);
extern void fn_80038CD0(u8 arg0, void *arg1, void *arg2, f32 arg3, f32 arg4);
extern void convertTextureHeader(void *arg0);
extern void fn_800BDA24(void *arg0);
extern void fn_800BD670(void *arg0, void *arg1);
extern void fn_1_121D4(void *arg0);
extern void *_OSAllocFromHeap(s32 arg0, s32 arg1);
extern void fn_80023F0C(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
extern void fn_1_F2C(GXTevMode mode, s32 texFrac, BOOL hasNormals);

typedef struct {
    u32 files[0x40][4];
    char names[0x3AC];
} DebugFileTable;

static DebugFileTable lbl_1_data_FB98 = {
    {
        {0x40B, 0x4023491C, 0x19135800, 0x82928},
        {0x40B, 0x4013764C, 0x1A635000, 0x7DB48},
        {0x40B, 0x4003E3DC, 0x1A6B3000, 0x21420},
        {0x40B, 0x4002EC10, 0x1A6D4800, 0x13108},
        {0x40B, 0x400E72C0, 0x1A6E8000, 0x60768},
        {0x40B, 0x40049404, 0x1A748800, 0x20E34},
        {0x40B, 0x40076AE0, 0x18ED7000, 0x36BC8},
        {0x40B, 0x4010FD70, 0x1A769800, 0x5E284},
        {0x40B, 0x400DB738, 0x1A7C8000, 0x49AB4},
        {0x40B, 0x400E9864, 0x1A812000, 0x59DC0},
        {0x40B, 0x400B7718, 0x1A86C000, 0x50288},
        {0x40B, 0x400D87FC, 0x1A8BC800, 0x47BC4},
        {0x40B, 0x400D643C, 0x1A904800, 0x4E3AC},
        {0x40B, 0x400D5C7C, 0x1A953000, 0x48D9C},
        {0x40B, 0x400B767C, 0x1A99C000, 0x47518},
        {0x40B, 0x400441F8, 0x1A9E3800, 0x1AA84},
        {0x40B, 0x40106568, 0x1A9FE800, 0x68C10},
        {0x40B, 0x4010E5A0, 0xE97A800, 0x9BCAC},
        {0x40B, 0x40016980, 0xEA16800, 0xD6C4},
        {0x40B, 0x40016980, 0xEA24000, 0xC944},
        {0x40B, 0x40016980, 0xEA31000, 0xE700},
        {0x40B, 0x40016980, 0xEA3F800, 0xD64C},
        {0x40B, 0x40016980, 0xEA4D000, 0xC900},
        {0x40B, 0x40016980, 0xEA5A000, 0xCFFC},
        {0x40B, 0x40016980, 0xEA67000, 0xD720},
        {0x40B, 0x40016980, 0xEA74800, 0xD6CC},
        {0x40B, 0x40016980, 0xEA82000, 0xD21C},
        {0x40B, 0x40016980, 0xEA8F800, 0xD0BC},
        {0x40B, 0x40016980, 0xEA9D000, 0xB544},
        {0x40B, 0x40016980, 0xEAA8800, 0xC4F8},
        {0x40B, 0x400ADFFC, 0x18AEE800, 0x4BAB0},
        {0x40B, 0x4037CF5C, 0x18B3A800, 0x208AF0},
        {0x40B, 0x4000A820, 0x18ED3800, 0x3758},
        {0x40B, 0x4011EC24, 0x18F0E000, 0xD8818},
        {0x40B, 0x400193E8, 0x191B8800, 0x89D8},
        {0x40B, 0x4006C850, 0x6C96000, 0x2C884},
        {0x40B, 0x4005B178, 0x6CC3000, 0x3555C},
        {0x40B, 0x401EB174, 0x18D43800, 0xFB220},
        {0x40B, 0x4001ED60, 0x1AA67800, 0xCFF0},
        {0x40B, 0x4000BF30, 0x1AA74800, 0x26E0},
        {0x40B, 0x40003498, 0x1AA77000, 0xE28},
        {0x40B, 0x4000BDE0, 0x1AA78000, 0x24F4},
        {0x40B, 0x40006088, 0x1AA7A800, 0x1290},
        {0x40B, 0x400049F0, 0x1AA7C000, 0x18F4},
        {0x40B, 0x40005ECC, 0x1AA7E000, 0x1D38},
        {0x40B, 0x40002670, 0x1AA80000, 0xBE8},
        {0x0, 0x28240, 0x1AA81000, 0x28240},
        {0x0, 0x28240, 0x1AAA9800, 0x28240},
        {0x0, 0x28240, 0x1AAD2000, 0x28240},
        {0x0, 0x28240, 0x1AAFA800, 0x28240},
        {0x0, 0x28240, 0x1AB23000, 0x28240},
        {0x0, 0x28240, 0x1AB4B800, 0x28240},
        {0x0, 0x28240, 0x1AB74000, 0x28240},
        {0x0, 0x28240, 0x1AB9C800, 0x28240},
        {0x0, 0x28240, 0x1ABC5000, 0x28240},
        {0x0, 0x28240, 0x1ABED800, 0x28240},
        {0x0, 0x28240, 0x1AC16000, 0x28240},
        {0x0, 0x28240, 0x1AC3E800, 0x28240},
        {0x0, 0x28240, 0x1AC67000, 0x28240},
        {0x0, 0x28240, 0x1AC8F800, 0x28240},
        {0x0, 0x28240, 0x1ACB8000, 0x28240},
        {0x0, 0x28240, 0x1ACE0800, 0x28240},
        {0x0, 0x28240, 0x1AD09000, 0x28240},
        {0x0, 0x0, 0x0, 0x0}
    },
    "game_td\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "result\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "operation\0\0\0\0\0\0\0\0\0\0\0"
    "game_toy\0\0\0\0\0\0\0\0\0\0\0\0"
    "game_slot\0\0\0\0\0\0\0\0\0\0\0"
    "score\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "rule_toy\0\0\0\0\0\0\0\0\0\0\0\0"
    "rule_mini_01\0\0\0\0\0\0\0\0"
    "rule_mini_02\0\0\0\0\0\0\0\0"
    "rule_mini_03\0\0\0\0\0\0\0\0"
    "rule_mini_05\0\0\0\0\0\0\0\0"
    "rule_mini_04\0\0\0\0\0\0\0\0"
    "rule_mini_06\0\0\0\0\0\0\0\0"
    "rule_mini_07\0\0\0\0\0\0\0\0"
    "training\0\0\0\0\0\0\0\0\0\0\0\0"
    "common\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "logo_all\0\0\0\0\0\0\0\0\0\0\0\0"
    "logo_00\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "logo_01\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "logo_02\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "logo_03\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "logo_04\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "logo_05\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "logo_06\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "logo_07\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "logo_08\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "logo_09\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "logo_10\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "logo_11\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "chara_sel\0\0\0\0\0\0\0\0\0\0\0"
    "select\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "dictionary\0\0\0\0\0\0\0\0\0\0"
    "score\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "end\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "option\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "logo_all\0\0\0\0\0\0\0\0\0\0\0\0"
    "title\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "comingsoon\0\0\0\0\0\0\0\0\0\0"
    "bg_test\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "load\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "fade00\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "fade01\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "fade02\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "fade03\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "fade04\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "fade05\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
    "fade06\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
};

static u8 lbl_1_data_10344[0x40] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
    0x01, 0x04, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static u32 lbl_1_data_10384[8][7] = {
    {0xFF0000FF, 0x00FF00FF, 0xFFFF00FF, 0x0000FFFF, 0xFF00FFFF, 0x00FFFFFF, 0xFFFFFFFF},
    {0xFF0000FF, 0x00FF00FF, 0xFFFF00FF, 0x0000FFFF, 0xFF00FFFF, 0x00FFFFFF, 0xFFFFFFFF},
    {0xFF0000FF, 0x00FF00FF, 0xFFFF00FF, 0x0000FFFF, 0xFF00FFFF, 0x00FFFFFF, 0xFFFFFFFF},
    {0xFF0000FF, 0x00FF00FF, 0xFFFF00FF, 0x0000FFFF, 0xFF00FFFF, 0x00FFFFFF, 0xFFFFFFFF},
    {0xFF0000FF, 0x00FF00FF, 0xFFFF00FF, 0x0000FFFF, 0xFF00FFFF, 0x00FFFFFF, 0xFFFFFFFF},
    {0xFF0000FF, 0x00FF00FF, 0xFFFF00FF, 0x0000FFFF, 0xFF00FFFF, 0x00FFFFFF, 0xFFFFFFFF},
    {0xFF0000FF, 0x00FF00FF, 0xFFFF00FF, 0x0000FFFF, 0xFF00FFFF, 0x00FFFFFF, 0xFFFFFFFF},
    {0xFF0000FF, 0x00FF00FF, 0xFFFF00FF, 0x0000FFFF, 0xFF00FFFF, 0x00FFFFFF, 0xFFFFFFFF}
};

static u32 lbl_1_data_10464 = 100;
static f32 lbl_1_data_10468 = 200.0f;
static f32 lbl_1_data_1046C = 100.0f;
static f32 lbl_1_data_10470 = 20.0f;
static u32 lbl_1_data_10474 = 10;
static f32 lbl_1_data_10478 = 1.0f;
static f32 lbl_1_data_1047C = 1.0f;
static Vec lbl_1_data_10480 = {0.0f, -1.0f, 0.0f};
static Vec lbl_1_data_1048C = {0.0f, 0.0f, -5.0f};
static Vec lbl_1_data_10498 = {0.0f, 0.0f, 0.0f};
static f32 lbl_1_data_104A4 = 50.0f;
static void (*lbl_1_data_104A8[4])(void) = {fn_1_1F2D8, fn_1_24410, fn_1_22644, fn_1_2040C};
static f32 lbl_1_data_104B8 = 0.3f;
static f32 lbl_1_data_104BC = 0.031496063f;
static f32 lbl_1_data_104C0 = 1.0f;
static f32 lbl_1_data_104C4 = 0.98f;
static f32 lbl_1_data_104C8 = 0.05f;
static u32 lbl_1_data_104CC = 0x400;
static f32 lbl_1_data_104D0[3] = {0.125f, 0.125f, 0.125f};
static u32 lbl_1_data_104DC[6] = {0xFF8080FF, 0x80FF80FF, 0x8080FFFF, 0xFFFF80FF, 0xFF80FFFF, 0x80FFFFFF};
static u32 chainModelFileDescriptorDebug[4] = {0x40B, 0x40000528, 0x09438800, 0x424};
static char lbl_1_data_10504[2] = ">";
static void (*lbl_1_data_10508[2])(DrawingSceneStruct *) = {(void (*)(DrawingSceneStruct *))fn_1_1FD78, (void (*)(DrawingSceneStruct *))fn_1_1F418};
static void (*lbl_1_data_10510[2])(DrawingSceneStruct *) = {(void (*)(DrawingSceneStruct *))fn_1_1F900, (void (*)(DrawingSceneStruct *))fn_1_1F618};
static u32 StadiumFiles_debug_10518[21][4] = {
    {0x40B, 0x40168A6C, 0x6CFD000, 0xC69A8},
    {0x40B, 0x401331E0, 0x6DC4000, 0xB67C4},
    {0x40B, 0x4011924C, 0x6E7A800, 0xA5764},
    {0x40B, 0x400FBAE0, 0x6F20000, 0xBE038},
    {0x40B, 0x400E5AC0, 0x6FDE800, 0xB4FB8},
    {0x40B, 0x40131200, 0x7093800, 0xA317C},
    {0x40B, 0x4011B660, 0x7137000, 0xD0294},
    {0x40B, 0x4011B660, 0x7137000, 0xD0294},
    {0x40B, 0x4011B660, 0x7137000, 0xD0294},
    {0x40B, 0x40141C60, 0x7207800, 0xCE904},
    {0x40B, 0x4013CA40, 0x72D6800, 0xCA560},
    {0x40B, 0x40141C60, 0x7207800, 0xCE904},
    {0x40B, 0x4016C138, 0x73A1000, 0xED41C},
    {0x40B, 0x401157B8, 0x748E800, 0xCA83C},
    {0x40B, 0x4016C138, 0x73A1000, 0xED41C},
    {0x40B, 0x400EB1C0, 0x7559800, 0xA3510},
    {0x40B, 0x400EB1C0, 0x7559800, 0xA3510},
    {0x40B, 0x400EB1C0, 0x7559800, 0xA3510},
    {0x40B, 0x400D04E0, 0x75FD000, 0x87390},
    {0x40B, 0x400D04E0, 0x75FD000, 0x87390},
    {0x40B, 0x400D04E0, 0x75FD000, 0x87390}
};
static s16 (*lbl_1_data_10668[1])(s16) = {(s16 (*)(s16))fn_1_1DE60};
static void (*lbl_1_data_1066C[1])(s16) = {(void (*)(s16))fn_1_1DE5C};
static s32 lbl_1_data_10670[1] = {4};
static u32 StadiumFiles_debug_10674[21][4] = {
    {0x40B, 0x40168A6C, 0x6CFD000, 0xC69A8},
    {0x40B, 0x401331E0, 0x6DC4000, 0xB67C4},
    {0x40B, 0x4011924C, 0x6E7A800, 0xA5764},
    {0x40B, 0x400FBAE0, 0x6F20000, 0xBE038},
    {0x40B, 0x400E5AC0, 0x6FDE800, 0xB4FB8},
    {0x40B, 0x40131200, 0x7093800, 0xA317C},
    {0x40B, 0x4011B660, 0x7137000, 0xD0294},
    {0x40B, 0x4011B660, 0x7137000, 0xD0294},
    {0x40B, 0x4011B660, 0x7137000, 0xD0294},
    {0x40B, 0x40141C60, 0x7207800, 0xCE904},
    {0x40B, 0x4013CA40, 0x72D6800, 0xCA560},
    {0x40B, 0x40141C60, 0x7207800, 0xCE904},
    {0x40B, 0x4016C138, 0x73A1000, 0xED41C},
    {0x40B, 0x401157B8, 0x748E800, 0xCA83C},
    {0x40B, 0x4016C138, 0x73A1000, 0xED41C},
    {0x40B, 0x400EB1C0, 0x7559800, 0xA3510},
    {0x40B, 0x400EB1C0, 0x7559800, 0xA3510},
    {0x40B, 0x400EB1C0, 0x7559800, 0xA3510},
    {0x40B, 0x400D04E0, 0x75FD000, 0x87390},
    {0x40B, 0x400D04E0, 0x75FD000, 0x87390},
    {0x40B, 0x400D04E0, 0x75FD000, 0x87390}
};
static u8 lbl_1_data_107C4[0x20] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A
};
typedef struct {
    u32 _00;
    void (*func)(void *);
    u32 _08;
    void *_0C;
    void *_10;
    u16 _14;
    u16 _16;
    u8 _18;
} DrawListNode; // size: 0x1C

static DrawListNode lbl_1_data_107E4[2] = {
    {0, fn_1_1D694},
    {0, fn_1_1D694}
};

typedef struct ChainNode {
    /* 0x00 */ f32 _00;
    /* 0x04 */ u8 _04[0x8];
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec prevPos;
    /* 0x24 */ u8 _24[0x18];
    /* 0x3C */ u32 _3C;
} ChainNode; // size: 0x40
static Mtx44 lbl_1_bss_47010;
static u8 lbl_1_bss_45868[0x17A8];
static ChainNode lbl_1_bss_43F68[100];
static Mtx lbl_1_bss_43F38;
static u8 lbl_1_bss_43EE0[0x58];
typedef struct {
    f32 x;
    f32 z;
    f32 y;
} GridPoint; // size: 0xC

#define GRID_COLS 112
#define GRID_ROWS 160

static GridPoint lbl_1_bss_F6E0[GRID_ROWS][GRID_COLS];
static f32 lbl_1_bss_76E0[0x2000];
static f32 lbl_1_bss_74E0[0x80];

static ChainNode lbl_1_bss_6FE0[20];
static u8 lbl_1_bss_6FB8[0x28];
static f32 lbl_1_bss_6FB4;
static Vec lbl_1_bss_6FA8;
static void *lbl_1_bss_6FA4;
static GXTexObj lbl_1_bss_6EA4[8];
static GXTlutObj lbl_1_bss_6E44[8];
static u32 lbl_1_bss_6E24[8];
static u8 lbl_1_bss_6D48[0xDC];
static u8 lbl_1_bss_6BF4[0x154];
static f32 lbl_1_bss_6BE4[4];
static void *lbl_1_bss_6BE0;
static s32 lbl_1_bss_6BDC;
static s32 lbl_1_bss_6BD8;

// .text:0x00026AF8 size:0x84
void fn_1_26AF8(void) {
    DrawingSceneStruct *item = currentDrawingItem;

    *((u8 *)item + 0x1e) = 0;
    *((u8 *)item + 0x20) = 0;
    *((u8 *)item + 0x21) = 0;
    *((u8 *)item + 0x1f) = 0;
    *((u8 *)item + 0x22) = 0;
    while (lbl_1_data_FB98.files[*((u8 *)item + 0x1f)][0] != 0) {
        *((u8 *)item + 0x1f) += 1;
    }
    fn_80035A00();
    currentDrawingItem->func = fn_1_26928;
}

// .text:0x00026A34 size:0xC4
void fn_1_26A34(void) {
    GXSetProjection(lbl_1_bss_47010, GX_PERSPECTIVE);
    GXClearVtxDesc();
    GXSetCullMode(GX_CULL_NONE);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
}

// .text:0x00026928 size:0x10C
void fn_1_26928(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    u16 val = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

    if (val & 0x2) {
        *((u8 *)item + 0x20) += 1;
        if (*((u8 *)item + 0x20) == *((u8 *)item + 0x1f)) {
            *((u8 *)item + 0x20) = 0;
        }
    } else if (val & 0x1) {
        if (*((u8 *)item + 0x20) == 0) {
            *((u8 *)item + 0x20) = *((u8 *)item + 0x1f);
        }
        *((u8 *)item + 0x20) -= 1;
    } else if (AtBat_ButtonInput1._02 & INPUT_BUTTON_A) {
        *((u8 *)item + 0x1e) = 0;
        currentDrawingItem->func = fn_1_267F4;
    } else if (AtBat_ButtonInput1._02 & INPUT_BUTTON_B) {
        fn_800AD038(*(void **)(lbl_80366158 + 0x8));
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
    } else if (AtBat_ButtonInput1._02 & INPUT_BUTTON_START) {
        item->func = fn_1_25C68;
    }

    fn_800B24D4(4);
    fn_800B1188();
}

// .text:0x000267F4 size:0x134
void fn_1_267F4(void) {
    DrawingSceneStruct *item = currentDrawingItem;

    switch (*((u8 *)item + 0x1e)) {
    case 0: {
        u8 idx = *((u8 *)item + 0x20);
        u8 *entry = (u8 *)lbl_1_data_FB98.files + idx * 0x10;

        if (diskReadRelated(entry, 0) != 0) {
            *((u8 *)item + 0x1e) += 1;
        }
        break;
    }
    case 1: {
        s32 idx2;

        *(void **)((u8 *)item + 0x14) = insertGraphicDrawingFunction(fn_1_267BC, 1);
        (*(DrawingSceneStruct **)((u8 *)item + 0x14))->state = 0;

        idx2 = fn_80035DD4(0);
        if (idx2 == -1) {
            OSPanic("spr.c", 0xf5, "It is a number not registered. \n");
        }

        *(u16 *)((u8 *)item + 0x18) =
            *(u32 *)(*(u8 **)((u8 *)textureContainerSlots[idx2].layout + 0x8));
        addGraphicsElementToScene(*(DrawingSceneStruct **)((u8 *)item + 0x14), (UIRecordDescriptor *)lbl_1_data_10344);

        *((u8 *)item + 0x21) = 0;
        *((u8 *)item + 0x22) = 0;
        *((u8 *)item + 0x24) = 0;
        *(u16 *)((u8 *)item + 0x1a) = 0;
        *(u16 *)((u8 *)item + 0x1c) = 0;
        currentDrawingItem->func = fn_1_25F98;
        break;
    }
    }
}

// .text:0x000267BC size:0x38
void fn_1_267BC(void) {
    if (currentDrawingItem->state != 0) {
        removeCurrentDrawingItem();
    }
}

// .text:0x00025F98 size:0x824
void fn_1_25F98(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    s32 row;
    LayoutFrameInfo info;

    for (row = 0; row < 6; row++) {
        switch (row) {
        case 0:
            if (row == *((u8 *)item + 0x22)) {
                u16 f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & INPUT_BUTTON_RIGHT) {
                    removeGraphicsElementFromScene(*(void **)((u8 *)item + 0x14));
                    *((u8 *)item + 0x21) += 1;
                    if (*((u8 *)item + 0x21) == *(u16 *)((u8 *)item + 0x18)) {
                        *((u8 *)item + 0x21) = 0;
                    }
                    *((u8 *)item + 0x24) = 0;
                    *(u16 *)((u8 *)lbl_1_data_10344 + 2) = *((u8 *)item + 0x21);
                    addGraphicsElementToScene(*(DrawingSceneStruct **)((u8 *)item + 0x14), (UIRecordDescriptor *)lbl_1_data_10344);
                } else if (f & INPUT_BUTTON_LEFT) {
                    removeGraphicsElementFromScene(*(void **)((u8 *)item + 0x14));
                    if (*((u8 *)item + 0x21) == 0) {
                        *((u8 *)item + 0x21) = (u8)*(u16 *)((u8 *)item + 0x18);
                    }
                    *((u8 *)item + 0x21) -= 1;
                    *((u8 *)item + 0x24) = 0;
                    *(u16 *)((u8 *)lbl_1_data_10344 + 2) = *((u8 *)item + 0x21);
                    addGraphicsElementToScene(*(DrawingSceneStruct **)((u8 *)item + 0x14), (UIRecordDescriptor *)lbl_1_data_10344);
                } else {
                    if (AtBat_ButtonInput1._02 & INPUT_BUTTON_A) {
                        GFX_OBJ(item)[0x68] = 1;
                    } else if (AtBat_ButtonInput1._02 & INPUT_BUTTON_B) {
                        GFX_OBJ(item)[0x68] = 0;
                    } else if (AtBat_ButtonInput1._02 & INPUT_BUTTON_X) {
                        *(u32 *)(GFX_OBJ(item) + 0x5c) = 0;
                    }
                }
            }
            break;
        case 1:
            if (row == *((u8 *)item + 0x22)) {
                if (AtBat_ButtonInput1._02 & INPUT_BUTTON_A) {
                    *((u8 *)item + 0x23) = !*((u8 *)item + 0x23);
                }
                if (*((u8 *)item + 0x23)) {
                    GFX_OBJ(item)[0x68] = 0;
                } else {
                    GFX_OBJ(item)[0x68] = 1;
                }
                {
                    u16 f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                    if (f & INPUT_BUTTON_RIGHT) {
                        if (*((u8 *)item + 0x23)) {
                            GFX_OBJ(item)[0x68] = 1;
                        }
                    } else if (f & INPUT_BUTTON_LEFT) {
                        if (*((u8 *)item + 0x23)) {
                            GFX_OBJ(item)[0x68] = 4;
                        }
                    }
                }
            }
            break;
        case 2: {
            if (row == *((u8 *)item + 0x22)) {
                u16 f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & INPUT_BUTTON_RIGHT) {
                    *((u8 *)item + 0x24) += 1;
                } else if (f & INPUT_BUTTON_LEFT) {
                    *((u8 *)item + 0x24) -= 1;
                }
            }
            fn_8000CEF0(textureContainerSlots[GFX_OBJ(item)[0x66]].layout, *((u8 *)item + 0x21), 0,
                *((u8 *)item + 0x24), &info);
            break;
        }
        case 3: {
            if (row == *((u8 *)item + 0x22)) {
                u16 f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                u8 *p;

                if (f & INPUT_BUTTON_RIGHT) {
                    info.textureIndex += 1;
                } else if (f & INPUT_BUTTON_LEFT) {
                    info.textureIndex -= 1;
                }

                p = textureContainerSlots[GFX_OBJ(item)[0x66]].layout;
                p = *(u8 **)(p + 8);
                p = *(u8 **)(p + *((u8 *)item + 0x21) * 4 + 8);
                *(u16 *)(*(u8 **)(p + 0xc) + 0xa) = info.textureIndex;
            }
            break;
        }
        case 4:
            if (row == *((u8 *)item + 0x22)) {
                u16 f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & INPUT_BUTTON_Y) {
                    *(s16 *)((u8 *)item + 0x1a) = 0;
                } else if (f & INPUT_BUTTON_X) {
                    *(s16 *)((u8 *)item + 0x1a) = 0x140;
                } else if (f & INPUT_BUTTON_RIGHT) {
                    *(s16 *)((u8 *)item + 0x1a) += 8;
                } else if (f & INPUT_BUTTON_LEFT) {
                    *(s16 *)((u8 *)item + 0x1a) -= 8;
                }
                *(f32 *)((u8 *)lbl_1_data_10344 + 4) = (f32)*(s16 *)((u8 *)item + 0x1a);
                *(f32 *)(GFX_OBJ(item) + 0x48) = (f32)*(s16 *)((u8 *)item + 0x1a);
            }
            break;
        case 5:
            if (row == *((u8 *)item + 0x22)) {
                u16 f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & INPUT_BUTTON_Y) {
                    *(s16 *)((u8 *)item + 0x1c) = 0;
                } else if (f & INPUT_BUTTON_X) {
                    *(s16 *)((u8 *)item + 0x1c) = 0xe0;
                } else if (f & INPUT_BUTTON_RIGHT) {
                    *(s16 *)((u8 *)item + 0x1c) += 8;
                } else if (f & INPUT_BUTTON_LEFT) {
                    *(s16 *)((u8 *)item + 0x1c) -= 8;
                }
                *(f32 *)((u8 *)lbl_1_data_10344 + 8) = (f32)*(s16 *)((u8 *)item + 0x1c);
                *(f32 *)(GFX_OBJ(item) + 0x4c) = (f32)*(s16 *)((u8 *)item + 0x1c);
            }
            break;
        }
    }

    if (AtBat_ButtonInput1._02 & INPUT_BUTTON_DOWN) {
        *((u8 *)item + 0x22) += 1;
        if (*((u8 *)item + 0x22) == 6) {
            *((u8 *)item + 0x22) = 0;
        }
    } else if (AtBat_ButtonInput1._02 & INPUT_BUTTON_UP) {
        if (*((u8 *)item + 0x22) == 0) {
            *((u8 *)item + 0x22) = 6;
        }
        *((u8 *)item + 0x22) -= 1;
    }

    if (AtBat_ButtonInput1._02 & INPUT_BUTTON_START) {
        removeGraphicsElementFromScene(*(void **)((u8 *)item + 0x14));
        *(u16 *)(*(u8 **)((u8 *)item + 0x14) + 0x10) = 1;
        currentDrawingItem->func = fn_1_26928;
        fn_80035A00();
    }

    {
        Mtx localMtx = {
            {1.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 1.0f, 0.0f},
        };

        if (lbl_1_bss_6BD8 != 0) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 0);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetNumChans(0);
        GXSetNumTexGens(1);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
        GXLoadPosMtxImm(localMtx, GX_PNMTX0);
        GXSetCurrentMtx(GX_PNMTX0);
        SetDisplayStateTexture((TextureBody *)&textureContainerSlots[GFX_OBJ(item)[0x66]].textures->records[lbl_1_bss_6BDC], 0, 0);

        GXBegin(GX_QUADS, GX_VTXFMT0, 4);

        GX_WRITE_F32((-0.5f));
        GX_WRITE_F32((-0.35f));
        GX_WRITE_F32((-2.0f));
        GX_WRITE_U16(0);
        GX_WRITE_U16(0);

        GX_WRITE_F32((-0.5f));
        GX_WRITE_F32(0.35f);
        GX_WRITE_F32((-2.0f));
        GX_WRITE_U16(0);
        GX_WRITE_U16(1);

        GX_WRITE_F32(0.5f);
        GX_WRITE_F32(0.35f);
        GX_WRITE_F32((-2.0f));
        GX_WRITE_U16(1);
        GX_WRITE_U16(1);

        GX_WRITE_F32(0.5f);
        GX_WRITE_F32((-0.35f));
        GX_WRITE_F32((-2.0f));
        GX_WRITE_U16(1);
        GX_WRITE_U16(0);
        }
    }
}

// .text:0x00025C68 size:0x330
void fn_1_25C68(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    u32 colorWord = 0;
    u8 rawByte;
    f32 signedVal;
    f32 invSigned;
    f32 value24;
    DrawingSceneStruct *cur;

    GXSetCopyClear(*(GXColor *)&colorWord, 0xffffff);

    C_MTXFrustum(lbl_1_bss_47010, (-224.0f), 224.0f, (-320.0f),
        320.0f, 1.0f, 512.0f);

    C_MTXLookAt(lbl_1_bss_43F38, &lbl_1_data_1048C, &lbl_1_data_10480,
        &lbl_1_data_10498);

    *(s16 *)((u8 *)item + 0x18) = (s16)(s32)(lbl_1_data_10468 * 64.0f);
    *(s16 *)((u8 *)item + 0x1c) = (s16)(s32)(lbl_1_data_1046C * 64.0f);
    *(s16 *)((u8 *)item + 0x1a) = (s16)(s32)lbl_1_data_10470;
    *(s16 *)((u8 *)item + 0x1e) = 0x20;
    *((u8 *)item + 0x2a) = (u8)(s32)lbl_1_data_10474;
    *(s16 *)((u8 *)item + 0x22) = 0xa;
    *((u8 *)item + 0x2b) = 0x14;
    *(s16 *)((u8 *)item + 0x20) = (s16)(s32)(lbl_1_data_1047C * 64.0f);
    *(s16 *)((u8 *)item + 0x24) = (s16)(s32)(lbl_1_data_10478 * 64.0f);
    item->unk_14 = 0.5f;
    *(s16 *)((u8 *)item + 0x26) = 0x64;
    *(s16 *)((u8 *)item + 0x28) = 0xa;

    cur = currentDrawingItem;
    fn_80038E2C(lbl_1_bss_45868);

    *(f32 *)(lbl_1_bss_45868 + 0x0) = (f32)*(u16 *)((u8 *)cur + 0x1a);
    *(f32 *)(lbl_1_bss_45868 + 0x4) = *(f32 *)((u8 *)cur + 0x14);
    *(f32 *)(lbl_1_bss_45868 + 0x8) = (f32)*(u16 *)((u8 *)cur + 0x18) / 64.0f;
    *(f32 *)(lbl_1_bss_45868 + 0xc) = (f32)*(u16 *)((u8 *)cur + 0x1c) / 64.0f;
    *(f32 *)(lbl_1_bss_45868 + 0x10) = (f32)*(u16 *)((u8 *)cur + 0x1e) / 64.0f;
    *(f32 *)(lbl_1_bss_45868 + 0x14) = (f32)*(u16 *)((u8 *)cur + 0x20) / 10000.0f;

    rawByte = *((u8 *)cur + 0x2a);
    *(u32 *)(lbl_1_bss_45868 + 0x20) = rawByte;
    signedVal = (f32)(s32)rawByte;
    invSigned = 1.0f / signedVal;
    *(f32 *)(lbl_1_bss_45868 + 0x18) = invSigned;
    *(f32 *)(lbl_1_bss_45868 + 0x1c) = invSigned * invSigned;
    *(f32 *)(lbl_1_bss_45868 + 0x24) = 1.0f / (2.0f * invSigned);

    if (AtBat_ButtonInput1._00 & INPUT_TRIGGER_L) {
        *(u32 *)(lbl_1_bss_45868 + 0x20) = 1;
    }

    value24 = (f32)*(u16 *)((u8 *)cur + 0x24) / 64.0f;
    fn_80038CD0(*((u8 *)cur + 0x2b), lbl_1_bss_45868, lbl_1_bss_43F68, 10.0f,
        value24);

    currentDrawingItem->func = fn_1_25064;
    *((u8 *)item + 0x2c) = 0;
}


static inline void updateChainParams(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    u8 rawByte;
    f32 signedVal;
    f32 invSigned;
    f32 value24;

    fn_80038E2C(lbl_1_bss_45868);

    *(f32 *)(lbl_1_bss_45868 + 0x0) = (f32)*(u16 *)((u8 *)item + 0x1a);
    *(f32 *)(lbl_1_bss_45868 + 0x4) = *(f32 *)((u8 *)item + 0x14);
    *(f32 *)(lbl_1_bss_45868 + 0x8) = (f32)*(u16 *)((u8 *)item + 0x18) / 64.0f;
    *(f32 *)(lbl_1_bss_45868 + 0xc) = (f32)*(u16 *)((u8 *)item + 0x1c) / 64.0f;
    *(f32 *)(lbl_1_bss_45868 + 0x10) = (f32)*(u16 *)((u8 *)item + 0x1e) / 64.0f;
    *(f32 *)(lbl_1_bss_45868 + 0x14) = (f32)*(u16 *)((u8 *)item + 0x20) / 10000.0f;

    rawByte = *((u8 *)item + 0x2a);
    *(u32 *)(lbl_1_bss_45868 + 0x20) = rawByte;
    signedVal = (f32)(s32)rawByte;
    invSigned = 1.0f / signedVal;
    *(f32 *)(lbl_1_bss_45868 + 0x18) = invSigned;
    *(f32 *)(lbl_1_bss_45868 + 0x1c) = invSigned * invSigned;
    *(f32 *)(lbl_1_bss_45868 + 0x24) = 1.0f / (2.0f * invSigned);

    if (AtBat_ButtonInput1._00 & INPUT_TRIGGER_L) {
        *(u32 *)(lbl_1_bss_45868 + 0x20) = 1;
    }

    value24 = (f32)*(u16 *)((u8 *)item + 0x24) / 64.0f;
    fn_80038CD0(*((u8 *)item + 0x2b), lbl_1_bss_45868, lbl_1_bss_43F68, 10.0f, value24);
}

static inline void drawMarkers(s32 count) {
    u8 width;
    GXTexOffset offset;
    s32 i;

    GXGetLineWidth(&width, &offset);
    GXSetLineWidth(0x18, offset);
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, (u16)count);

    i = count;
    while (i-- != 0) {
        u8 *p = (u8 *)lbl_1_bss_43F68 + i * 0x40;

        GX_WRITE_F32(*(f32 *)(p + 0xc));
        GX_WRITE_F32(*(f32 *)(p + 0x10));
        GX_WRITE_F32(*(f32 *)(p + 0x14));
        GX_WRITE_U32(((u32 *)lbl_1_data_10384)[i]);
    }

    GXSetLineWidth(width, offset);
    GXBegin(GX_LINES, GX_VTXFMT0, (u16)(count * 4));

    i = count;
    while (i-- != 0) {
        u8 *p = (u8 *)lbl_1_bss_43F68 + i * 0x40;
        u32 *color = &((u32 *)lbl_1_data_10384)[i];

        GX_WRITE_F32(*(f32 *)(p + 0xc));
        GX_WRITE_F32(*(f32 *)(p + 0x10));
        GX_WRITE_F32(*(f32 *)(p + 0x14));
        GX_WRITE_U32(*color);

        GX_WRITE_F32(lbl_1_data_104A4 * *(f32 *)(p + 0x30) + *(f32 *)(p + 0xc));
        GX_WRITE_F32(lbl_1_data_104A4 * *(f32 *)(p + 0x34) + *(f32 *)(p + 0x10));
        GX_WRITE_F32(lbl_1_data_104A4 * *(f32 *)(p + 0x38) + *(f32 *)(p + 0x14));
        GX_WRITE_U32(*color);

        GX_WRITE_F32(*(f32 *)(p + 0xc));
        GX_WRITE_F32(*(f32 *)(p + 0x10));
        GX_WRITE_F32(*(f32 *)(p + 0x14));
        GX_WRITE_U32(*color ^ 0xffffff00);

        GX_WRITE_F32(lbl_1_data_104A4 * *(f32 *)(p + 0x24) + *(f32 *)(p + 0xc));
        GX_WRITE_F32(lbl_1_data_104A4 * *(f32 *)(p + 0x28) + *(f32 *)(p + 0x10));
        GX_WRITE_F32(lbl_1_data_104A4 * *(f32 *)(p + 0x2c) + *(f32 *)(p + 0x14));
        GX_WRITE_U32(*color ^ 0xffffff00);
    }
}

// .text:0x00025064 size:0xC04
void fn_1_25064(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    s32 row;
    s32 step1;
    s32 step2;

    if (AtBat_ButtonInput1._00 & INPUT_TRIGGER_R) {
        step1 = 4;
        step2 = 1;
    } else {
        step1 = 0x40;
        step2 = 0xa;
    }

    for (row = 0; row < 11; row++) {
        u16 f;

        switch (row) {
        case 0:
            if (row == *((u8 *)item + 0x2c)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & INPUT_BUTTON_LEFT) {
                    *((u8 *)item + 0x2b) -= 1;
                    updateChainParams();
                } else if (f & INPUT_BUTTON_RIGHT) {
                    *((u8 *)item + 0x2b) += 1;
                    updateChainParams();
                }
            }
            break;
        case 1:
            if (row == *((u8 *)item + 0x2c)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & INPUT_BUTTON_LEFT) {
                    *((u8 *)item + 0x2a) -= 1;
                } else if (f & INPUT_BUTTON_RIGHT) {
                    *((u8 *)item + 0x2a) += 1;
                }
                if (*((u8 *)item + 0x2a) == 0) {
                    *((u8 *)item + 0x2a) = 1;
                }
            }
            break;
        case 2:
            if (row == *((u8 *)item + 0x2c)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & INPUT_BUTTON_LEFT) {
                    *(u16 *)((u8 *)item + 0x18) -= step1;
                } else if (f & INPUT_BUTTON_RIGHT) {
                    *(u16 *)((u8 *)item + 0x18) += step1;
                }
            }
            break;
        case 3:
            if (row == *((u8 *)item + 0x2c)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & INPUT_BUTTON_LEFT) {
                    *(u16 *)((u8 *)item + 0x1c) -= step1;
                } else if (f & INPUT_BUTTON_RIGHT) {
                    *(u16 *)((u8 *)item + 0x1c) += step1;
                }
            }
            break;
        case 4:
            if (row == *((u8 *)item + 0x2c)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & INPUT_BUTTON_LEFT) {
                    *(u16 *)((u8 *)item + 0x1a) -= step2;
                } else if (f & INPUT_BUTTON_RIGHT) {
                    *(u16 *)((u8 *)item + 0x1a) += step2;
                }
            }
            break;
        case 5:
            if (row == *((u8 *)item + 0x2c)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & INPUT_BUTTON_LEFT) {
                    *(u16 *)((u8 *)item + 0x24) -= step1;
                } else if (f & INPUT_BUTTON_RIGHT) {
                    *(u16 *)((u8 *)item + 0x24) += step1;
                }
            }
            break;
        case 6:
            if (row == *((u8 *)item + 0x2c)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & INPUT_BUTTON_LEFT) {
                    *(u16 *)((u8 *)item + 0x22) -= 1;
                } else if (f & INPUT_BUTTON_RIGHT) {
                    *(u16 *)((u8 *)item + 0x22) += 1;
                }
            }
            break;
        case 7:
            if (row == *((u8 *)item + 0x2c)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & INPUT_BUTTON_LEFT) {
                    *(u16 *)((u8 *)item + 0x20) -= step2;
                } else if (f & INPUT_BUTTON_RIGHT) {
                    *(u16 *)((u8 *)item + 0x20) += step2;
                }
            }
            break;
        case 8:
            if (row == *((u8 *)item + 0x2c)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & INPUT_BUTTON_LEFT) {
                    *(u16 *)((u8 *)item + 0x26) -= step2;
                } else if (f & INPUT_BUTTON_RIGHT) {
                    *(u16 *)((u8 *)item + 0x26) += step2;
                }
            }
            break;
        case 9:
            if (row == *((u8 *)item + 0x2c)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & INPUT_BUTTON_LEFT) {
                    *(u16 *)((u8 *)item + 0x1e) -= step1;
                } else if (f & INPUT_BUTTON_RIGHT) {
                    *(u16 *)((u8 *)item + 0x1e) += step1;
                }
            }
            break;
        case 10:
            if (row == *((u8 *)item + 0x2c)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & INPUT_BUTTON_LEFT) {
                    *(u16 *)((u8 *)item + 0x28) -= step2;
                } else if (f & INPUT_BUTTON_RIGHT) {
                    *(u16 *)((u8 *)item + 0x28) += step2;
                }
            }
            break;
        }
    }

    {
        u16 f2 = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

        if (f2 & 8) {
            if (*((u8 *)item + 0x2c) == 0) {
                *((u8 *)item + 0x2c) = 0xb;
            }
            *((u8 *)item + 0x2c) -= 1;
        } else if (f2 & 4) {
            *((u8 *)item + 0x2c) += 1;
            if (*((u8 *)item + 0x2c) == 0xb) {
                *((u8 *)item + 0x2c) = 0;
            }
        } else if (AtBat_ButtonInput1._02 & INPUT_BUTTON_A) {
            updateChainParams();
        } else if (AtBat_ButtonInput1._02 & INPUT_BUTTON_B) {
            u32 clearColor = 0x11775500;

            GXSetCopyClear(*(GXColor *)&clearColor, 0xFFFFFF);

            currentDrawingItem->currentDrawingItem->state = 1;
            removeCurrentDrawingItem();
        }
    }

    fn_1_247A0();

    GXSetProjection(lbl_1_bss_47010, GX_PERSPECTIVE);
    GXClearVtxDesc();
    GXSetCullMode(GX_CULL_NONE);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXLoadPosMtxImm(lbl_1_bss_43F38, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);

    fn_1_AF4(0xb, 0xb, 50.0f);

    drawMarkers(*((u8 *)item + 0x2b));
}

// .text:0x00024C4C size:0x418
void fn_1_24C4C(u8 *arg0, s32 count, Vec *force, f32 stiffness, f32 damping, f32 restLength, f32 drag) {
    DrawingSceneStruct *item = currentDrawingItem;
    f32 windDrag = (-1.0f) * drag;
    f32 once = 1.0f;
    f32 zero = 0.0f;
    u8 *p;
    u8 *pNext;
    s32 i;
    s32 j;
    Vec local20;
    Vec local14;
    Vec local8;

    i = count;
    while (i-- != 0) {
        p = arg0 + i * 0x3c;

        if (*(u32 *)(p + 0x38) != 0) {
            *(f32 *)(p + 0x34) = 0.0f;
            *(f32 *)(p + 0x30) = 0.0f;
            *(f32 *)(p + 0x2c) = 0.0f;
        } else {
            *(f32 *)(p + 0x34) = 0.0f;
            *(f32 *)(p + 0x2c) = 0.0f;
            *(f32 *)(p + 0x30) = (-9.80665f) * *(f32 *)(p + 0x0);
        }

        {
            f32 mag = PSVECMag((Vec *)(p + 0x20));

            if (mag != zero) {
                PSVECScale((Vec *)(p + 0x20), windDrag, &local20);
                PSVECNormalize(&local20, &local20);
                PSVECScale(&local20, ((f32)*(u16 *)((u8 *)item + 0x20) / 10000.0f) * (mag * mag), &local20);
                PSVECAdd((Vec *)(p + 0x2c), &local20, (Vec *)(p + 0x2c));
            }
        }

        if (once != zero) {
            PSVECAdd((Vec *)(p + 0x2c), force, (Vec *)(p + 0x2c));
            once = 0.0f;
        }
    }

    j = count;
    while (--j != 0) {
        f32 mag20;
        f32 dampForce;
        f32 springForce;

        p = arg0 + j * 0x3c;
        pNext = arg0 + (j - 1) * 0x3c;

        PSVECSubtract((Vec *)(p + 0x8), (Vec *)(pNext + 0x8), &local20);
        PSVECSubtract((Vec *)(p + 0x20), (Vec *)(pNext + 0x20), &local14);
        PSVECScale(&local14, drag, &local14);
        mag20 = PSVECMag(&local20);
        dampForce = damping * (PSVECDotProduct(&local14, &local20) / mag20);
        PSVECNormalize(&local20, &local8);
        springForce = stiffness * (mag20 - restLength);
        PSVECScale(&local8, -(springForce + dampForce), &local8);

        if (*(u32 *)(p + 0x38) == 0) {
            PSVECAdd((Vec *)(p + 0x2c), &local8, (Vec *)(p + 0x2c));
        }

        PSVECScale(&local8, (-1.0f), &local8);

        if (*(u32 *)(pNext + 0x38) == 0) {
            PSVECAdd((Vec *)(pNext + 0x2c), &local8, (Vec *)(pNext + 0x2c));
        }
    }

    i = count;
    while (i-- != 0) {
        p = arg0 + i * 0x3c;

        if (*(u32 *)(p + 0x38) == 0 && *(f32 *)(p + 0xc) <= (f32)*(u16 *)((u8 *)item + 0x28) / 1000.0f) {
            f32 mag = PSVECMag((Vec *)(p + 0x20));

            if (mag != 0.0f) {
                f32 friction = (f32)*(u16 *)((u8 *)item + 0x1e) / 64.0f * *(f32 *)(p + 0x30);
                f32 mag2;

                if (friction < 0.0f) {
                    friction = -friction;
                }

                memcpy(&local20, p + 0x2c, sizeof(Vec));
                local20.y = 0.0f;

                mag2 = PSVECMag(&local20);
                if (mag2) {
                    PSVECNormalize(&local20, &local20);
                    if (friction > mag2) {
                        PSVECScale(&local20, -mag2, &local20);
                    } else {
                        PSVECScale(&local20, -friction, &local20);
                    }
                    PSVECAdd(&local20, (Vec *)(p + 0x2c), (Vec *)(p + 0x2c));
                }
            }
        }
    }
}


// .text:0x00024A8C size:0x1C0
void fn_1_24A8C(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    u8 rawByte;
    f32 signedVal;
    f32 invSigned;
    f32 value24;

    fn_80038E2C(lbl_1_bss_45868);

    *(f32 *)(lbl_1_bss_45868 + 0x0) = (f32)*(u16 *)((u8 *)item + 0x1a);
    *(f32 *)(lbl_1_bss_45868 + 0x4) = *(f32 *)((u8 *)item + 0x14);
    *(f32 *)(lbl_1_bss_45868 + 0x8) = (f32)*(u16 *)((u8 *)item + 0x18) / 64.0f;
    *(f32 *)(lbl_1_bss_45868 + 0xc) = (f32)*(u16 *)((u8 *)item + 0x1c) / 64.0f;
    *(f32 *)(lbl_1_bss_45868 + 0x10) = (f32)*(u16 *)((u8 *)item + 0x1e) / 64.0f;
    *(f32 *)(lbl_1_bss_45868 + 0x14) = (f32)*(u16 *)((u8 *)item + 0x20) / 10000.0f;

    rawByte = *((u8 *)item + 0x2a);
    *(u32 *)(lbl_1_bss_45868 + 0x20) = rawByte;
    signedVal = (f32)(s32)rawByte;
    invSigned = 1.0f / signedVal;
    *(f32 *)(lbl_1_bss_45868 + 0x18) = invSigned;
    *(f32 *)(lbl_1_bss_45868 + 0x1c) = invSigned * invSigned;
    *(f32 *)(lbl_1_bss_45868 + 0x24) = 1.0f / (2.0f * invSigned);

    if (AtBat_ButtonInput1._00 & INPUT_TRIGGER_L) {
        *(u32 *)(lbl_1_bss_45868 + 0x20) = 1;
    }

    value24 = (f32)*(u16 *)((u8 *)item + 0x24);
    value24 /= 64.0f;
    fn_80038CD0(*((u8 *)item + 0x2b), lbl_1_bss_45868, lbl_1_bss_43F68, 10.0f, value24);
}


// .text:0x000248BC size:0x1D0
void fn_1_248BC(s32 count) {
    u8 width;
    GXTexOffset offset;
    s32 i;

    GXGetLineWidth(&width, &offset);
    GXSetLineWidth(0x18, offset);
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, (u16)count);

    i = count;
    while (i-- != 0) {
        u8 *p = (u8 *)lbl_1_bss_43F68 + i * 0x40;

        GX_WRITE_F32(*(f32 *)(p + 0xc));
        GX_WRITE_F32(*(f32 *)(p + 0x10));
        GX_WRITE_F32(*(f32 *)(p + 0x14));
        GX_WRITE_U32(((u32 *)lbl_1_data_10384)[i]);
    }

    GXSetLineWidth(width, offset);
    GXBegin(GX_LINES, GX_VTXFMT0, (u16)(count * 4));

    i = count;
    while (i-- != 0) {
        u8 *p = (u8 *)lbl_1_bss_43F68 + i * 0x40;
        u32 *color = &((u32 *)lbl_1_data_10384)[i];

        GX_WRITE_F32(*(f32 *)(p + 0xc));
        GX_WRITE_F32(*(f32 *)(p + 0x10));
        GX_WRITE_F32(*(f32 *)(p + 0x14));
        GX_WRITE_U32(*color);

        GX_WRITE_F32(lbl_1_data_104A4 * *(f32 *)(p + 0x30) + *(f32 *)(p + 0xc));
        GX_WRITE_F32(lbl_1_data_104A4 * *(f32 *)(p + 0x34) + *(f32 *)(p + 0x10));
        GX_WRITE_F32(lbl_1_data_104A4 * *(f32 *)(p + 0x38) + *(f32 *)(p + 0x14));
        GX_WRITE_U32(*color);

        GX_WRITE_F32(*(f32 *)(p + 0xc));
        GX_WRITE_F32(*(f32 *)(p + 0x10));
        GX_WRITE_F32(*(f32 *)(p + 0x14));
        GX_WRITE_U32(*color ^ 0xffffff00);

        GX_WRITE_F32(lbl_1_data_104A4 * *(f32 *)(p + 0x24) + *(f32 *)(p + 0xc));
        GX_WRITE_F32(lbl_1_data_104A4 * *(f32 *)(p + 0x28) + *(f32 *)(p + 0x10));
        GX_WRITE_F32(lbl_1_data_104A4 * *(f32 *)(p + 0x2c) + *(f32 *)(p + 0x14));
        GX_WRITE_U32(*color ^ 0xffffff00);
    }
}

// .text:0x000247A0 size:0x11C
void fn_1_247A0(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    f32 buf[3];

    buf[0] = (f32)*(u16 *)((u8 *)item + 0x22) *
             ((f32)*((s8 *)&AtBat_ButtonInput1 + 0x10) * lbl_1_bss_43F68[*((u8 *)item + 0x2b) - 1]._00);
    buf[1] = (f32)*(u16 *)((u8 *)item + 0x22) *
             ((f32)*((s8 *)&AtBat_ButtonInput1 + 0x13) * lbl_1_bss_43F68[*((u8 *)item + 0x2b) - 1]._00);
    buf[2] = (f32)*(u16 *)((u8 *)item + 0x22) *
             ((f32)*((s8 *)&AtBat_ButtonInput1 + 0x11) * lbl_1_bss_43F68[*((u8 *)item + 0x2b) - 1]._00);

    fn_80038B48(lbl_1_bss_45868, lbl_1_bss_43F68, *((u8 *)item + 0x2b), buf);
}

// .text:0x00024778 size:0x28
void fn_1_24778(void) {
    *((u8 *)currentDrawingItem + 0x14) = 0;
    currentDrawingItem->func = fn_1_246AC;
}

// .text:0x000246AC size:0xCC
void fn_1_246AC(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    u16 val = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

    if (val & 0x8) {
        if (*((u8 *)item + 0x14) == 0) {
            *((u8 *)item + 0x14) = 4;
        }
        *((u8 *)item + 0x14) -= 1;
    } else if (val & 0x4) {
        *((u8 *)item + 0x14) += 1;
        if (*((u8 *)item + 0x14) == 4) {
            *((u8 *)item + 0x14) = 0;
        }
    } else if (AtBat_ButtonInput1._02 & INPUT_BUTTON_A) {
        item->func = lbl_1_data_104A8[*((u8 *)item + 0x14)];
    } else if (AtBat_ButtonInput1._02 & INPUT_BUTTON_B) {
        item->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
    }
}

// .text:0x00024410 size:0x29C
void fn_1_24410(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    s32 j;

    fn_1_23AD8(lbl_1_bss_47010, (f32 *)(lbl_1_bss_43EE0 + 0x48), (f32 *)(lbl_1_bss_43EE0 + 0x3c));

    *(u16 *)(lbl_1_bss_43EE0 + 0x30) = 0;
    *(f32 *)(lbl_1_bss_43EE0 + 0x38) = 0.0f;
    *(u16 *)(lbl_1_bss_43EE0 + 0x32) = 0;

    *((u8 *)item + 0x27) = 0x40;
    *((u8 *)item + 0x29) = 0x40;
    *((u8 *)item + 0x28) = 0x40;
    *((u8 *)item + 0x2a) = 0;
    item->unk_14 = 500.0f;
    *(f32 *)((u8 *)item + 0x18) = 32.0f;
    *(u16 *)((u8 *)item + 0x24) = 0;
    *(f32 *)((u8 *)item + 0x1c) = 0.15f;
    *(f32 *)((u8 *)item + 0x20) = 0.08f;
    *((u8 *)item + 0x2b) = 1;

    {
        f32 c1 = 3.1415925f;
        f32 c2 = 2.0f;
        f32 c3 = 0.0078125f;

        for (j = 0; j < 0x80; j++) {
            f32 angle = c1 * (c2 * ((f32)j * c3));

            lbl_1_bss_74E0[j] = (f32)cos((f64)angle);
        }
    }

    *((u8 *)item + 0x2c) = 0;
    memset(lbl_1_bss_76E0, 0, 0x8000);

    {
        s32 i;
        s32 idx;

        for (i = 0; i < 0x20; i++) {
            idx = (rand() % 0x20) * 0x80;
            idx += rand() % 0x80;
            lbl_1_bss_76E0[idx] = 1.0f;
        }
    }

    currentDrawingItem->func = fn_1_23B54;
}

// .text:0x00023B54 size:0x8BC
void fn_1_23B54(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    u16 flags;
    s32 row;
    s32 gr;
    s32 gc;
    f32 maxZ;
    f32 minZ;

    for (row = 0; row < 8; row++) {
        switch (row) {
        case 0:
            if (row == *((u8 *)item + 0x26)) {
                flags = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (flags & INPUT_BUTTON_LEFT) {
                    if (*((u8 *)item + 0x27) == 2) {
                        *((u8 *)item + 0x27) = 0x70;
                    }
                    *((u8 *)item + 0x27) -= 1;
                } else if (flags & INPUT_BUTTON_RIGHT) {
                    if (*((u8 *)item + 0x27) == 0x70) {
                        *((u8 *)item + 0x27) = 2;
                    }
                    *((u8 *)item + 0x27) += 1;
                }
            }
            break;
        case 1:
            if (row == *((u8 *)item + 0x26)) {
                flags = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (flags & INPUT_BUTTON_LEFT) {
                    if (*((u8 *)item + 0x28) == 2) {
                        *((u8 *)item + 0x28) = 0xa0;
                    }
                    *((u8 *)item + 0x28) -= 1;
                } else if (flags & INPUT_BUTTON_RIGHT) {
                    if (*((u8 *)item + 0x28) == 0xa0) {
                        *((u8 *)item + 0x28) = 2;
                    }
                    *((u8 *)item + 0x28) += 1;
                }
            }
            break;
        case 2:
            if (row == *((u8 *)item + 0x26)) {
                flags = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (flags & (INPUT_BUTTON_LEFT | INPUT_BUTTON_RIGHT)) {
                    *((u8 *)item + 0x2a) = !*((u8 *)item + 0x2a);
                }
            }
            break;
        case 3:
            if (row == *((u8 *)item + 0x26)) {
                flags = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (flags & INPUT_BUTTON_LEFT) {
                    if (*(f32 *)((u8 *)item + 0x14) > 1.0f) {
                        *(f32 *)((u8 *)item + 0x14) -= 1.0f;
                    }
                } else if (flags & INPUT_BUTTON_RIGHT) {
                    if (*(f32 *)((u8 *)item + 0x14) < 512.0f) {
                        *(f32 *)((u8 *)item + 0x14) += 1.0f;
                    }
                }
            }
            break;
        case 4:
            if (row == *((u8 *)item + 0x26)) {
                flags = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (flags & INPUT_BUTTON_LEFT) {
                    if (*(f32 *)((u8 *)item + 0x18) > 1.0f) {
                        *(f32 *)((u8 *)item + 0x18) -= 1.0f;
                    }
                } else if (flags & INPUT_BUTTON_RIGHT) {
                    if (*(f32 *)((u8 *)item + 0x18) < 512.0f) {
                        *(f32 *)((u8 *)item + 0x18) += 1.0f;
                    }
                }
            }
            break;
        case 5:
            if (row == *((u8 *)item + 0x26)) {
                flags = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (flags & (INPUT_BUTTON_LEFT | INPUT_BUTTON_RIGHT)) {
                    *((u8 *)item + 0x2b) = !*((u8 *)item + 0x2b);
                }
            }
            break;
        case 6:
            if (row == *((u8 *)item + 0x26)) {
                flags = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (flags & INPUT_BUTTON_LEFT) {
                    if (*(f32 *)((u8 *)item + 0x1c) > 0.0f) {
                        *(f32 *)((u8 *)item + 0x1c) -= 0.001f;
                    }
                } else if (flags & INPUT_BUTTON_RIGHT) {
                    if (*(f32 *)((u8 *)item + 0x1c) < 1.0f) {
                        *(f32 *)((u8 *)item + 0x1c) += 0.001f;
                    }
                }
            }
            break;
        case 7:
            if (row == *((u8 *)item + 0x26)) {
                flags = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (flags & INPUT_BUTTON_LEFT) {
                    if (*(f32 *)((u8 *)item + 0x20) > 0.0f) {
                        *(f32 *)((u8 *)item + 0x20) -= 0.001f;
                    }
                } else if (flags & INPUT_BUTTON_RIGHT) {
                    if (*(f32 *)((u8 *)item + 0x20) < 1.0f) {
                        *(f32 *)((u8 *)item + 0x20) += 0.001f;
                    }
                }
            }
            break;
        }
    }

    flags = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

    if (flags & INPUT_BUTTON_UP) {
        if (*((u8 *)item + 0x26) == 0) {
            *((u8 *)item + 0x26) = 8;
        }
        *((u8 *)item + 0x26) -= 1;
    } else if (flags & INPUT_BUTTON_DOWN) {
        *((u8 *)item + 0x26) += 1;
        if (*((u8 *)item + 0x26) == 8) {
            *((u8 *)item + 0x26) = 0;
        }
    } else if (AtBat_ButtonInput1._02 & INPUT_BUTTON_B) {
        currentDrawingItem->func = fn_1_24778;
    } else if (flags & INPUT_BUTTON_A) {
        s32 idx;
        s32 i;

        for (i = 0; i < 0x10; i++) {
            idx = (rand() % 0x20) * 0x80;
            idx += rand() % 0x80;
            lbl_1_bss_76E0[idx] += *(f32 *)((u8 *)item + 0x1c);
        }
    }

    fn_1_121D4(lbl_1_bss_43EE0);

    if (*((u8 *)item + 0x2a) == 0) {
        *((u8 *)item + 0x29) = fn_1_23098(lbl_1_bss_47010, *(Mtx *)lbl_1_bss_43EE0,
            *((u8 *)item + 0x27), *((u8 *)item + 0x28), *(f32 *)((u8 *)item + 0x18), *(f32 *)((u8 *)item + 0x14));

        if (*((u8 *)item + 0x2b) != 0) {
            u8 pingFlag = *((u8 *)item + 0x2c);
            f32 *src;
            f32 *dst;

            *((u8 *)item + 0x2c) = pingFlag + 1;
            src = lbl_1_bss_76E0 + (pingFlag & 1) * 0x1000;
            dst = lbl_1_bss_76E0 + (1 - (pingFlag & 1)) * 0x1000;

            fn_1_22F4C(0x20, 0x80, dst, src, dst);

            maxZ = (-100.0f);
            minZ = 100.0f;

            for (gr = 0; gr < *((u8 *)item + 0x28); gr++) {
                for (gc = 0; gc < *((u8 *)item + 0x29); gc++) {
                    GridPoint *p = &lbl_1_bss_F6E0[gr][gc];
                    f32 x = p->x;
                    f32 z = p->z;
                    u8 ping = *((u8 *)item + 0x2c);
                    s32 n;
                    f32 u;
                    f32 v;

                    if (x < 0.0f) {
                        n = (s32)-x;
                    } else {
                        n = (s32)x;
                    }
                    n = n / 2 * 2;
                    if (x < 0.0f) {
                        u = x + (f32)(n + 2);
                    } else {
                        u = x - (f32)n;
                    }
                    u = 64.0f * u;

                    if (z < 0.0f) {
                        n = (s32)-z;
                    } else {
                        n = (s32)z;
                    }
                    n = n / 2 * 2;
                    if (z < 0.0f) {
                        v = z + (f32)(n + 2);
                    } else {
                        v = z - (f32)n;
                    }
                    v = 16.0f * v;

                    p->y = ((f32 (*)[0x1000])lbl_1_bss_76E0)[ping & 1][(s32)u + (s32)v * 0x80];

                    if (p->y < minZ) {
                        minZ = p->y;
                    } else if (p->y > maxZ) {
                        maxZ = p->y;
                    }
                }
            }
        } else {
            minZ = 0.0f;
            maxZ = minZ;

            for (gr = 0; gr < *((u8 *)item + 0x28); gr++) {
                for (gc = 0; gc < *((u8 *)item + 0x29); gc++) {
                    lbl_1_bss_F6E0[gr][gc].y = minZ;
                }
            }
        }
    }

    fn_1_23804(maxZ, minZ, 10, 10, *((u8 *)item + 0x29), *((u8 *)item + 0x28));
    *(u16 *)((u8 *)item + 0x24) += 1;
}

// .text:0x00023AD8 size:0x7C
void fn_1_23AD8(Mtx44 m, f32 *arg1, f32 *arg2) {
    f32 up = 0.0f;
    f32 z = (-10.0f);

    arg1[0] = up;
    arg1[1] = up;
    arg1[2] = z;
    arg2[0] = up;
    arg2[1] = up;
    arg2[2] = up;

    C_MTXFrustum(m, (-0.175f), 0.175f, 0.25f, (-0.25f),
        1.0f, 512.0f);
}

// .text:0x00023804 size:0x2D4
void fn_1_23804(f32 argF0, f32 argF1, s32 arg0, s32 arg1, s32 cols, s32 rows) {
    s32 rowCount;

    GXSetProjection(lbl_1_bss_47010, GX_PERSPECTIVE);
    GXClearVtxDesc();
    GXSetCullMode(GX_CULL_NONE);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXLoadPosMtxImm((f32 (*)[4])lbl_1_bss_43EE0, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);

    rowCount = rows;
    while (--cols != 0) {
        rows = rowCount;
        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, rowCount * 2);

        while (rows-- != 0) {
            GridPoint *p = &lbl_1_bss_F6E0[0][cols] + rows * GRID_COLS;

            GX_WRITE_F32(p[0].x);
            GX_WRITE_F32(p[0].y);
            GX_WRITE_F32(p[0].z);
            if (cols & 1) {
                GX_WRITE_U32(0xffffffff);
            } else {
                GX_WRITE_U32(0xffff);
            }

            GX_WRITE_F32(p[-1].x);
            GX_WRITE_F32(p[-1].y);
            GX_WRITE_F32(p[-1].z);
            if (cols & 1) {
                GX_WRITE_U32(0xffff);
            } else {
                GX_WRITE_U32(0xffffffff);
            }
        }
    }

    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 8);

    GX_WRITE_F32((-25.0f));
    GX_WRITE_F32(0.0f);
    GX_WRITE_F32((-25.0f));
    GX_WRITE_U32(0xff0000ff);

    GX_WRITE_F32((-25.0f));
    GX_WRITE_F32(0.0f);
    GX_WRITE_F32(25.0f);
    GX_WRITE_U32(0xff0000ff);

    GX_WRITE_F32((-25.0f));
    GX_WRITE_F32(0.0f);
    GX_WRITE_F32(25.0f);
    GX_WRITE_U32(0xffff);

    GX_WRITE_F32(25.0f);
    GX_WRITE_F32(0.0f);
    GX_WRITE_F32(25.0f);
    GX_WRITE_U32(0xffff);

    GX_WRITE_F32(25.0f);
    GX_WRITE_F32(0.0f);
    GX_WRITE_F32(25.0f);
    GX_WRITE_U32(0xff0000ff);

    GX_WRITE_F32(25.0f);
    GX_WRITE_F32(0.0f);
    GX_WRITE_F32((-25.0f));
    GX_WRITE_U32(0xff0000ff);

    GX_WRITE_F32(25.0f);
    GX_WRITE_F32(0.0f);
    GX_WRITE_F32((-25.0f));
    GX_WRITE_U32(0xffff);

    GX_WRITE_F32((-25.0f));
    GX_WRITE_F32(0.0f);
    GX_WRITE_F32((-25.0f));
    GX_WRITE_U32(0xffff);
}

// .text:0x00023098 size:0x76C
s32 fn_1_23098(Mtx44 proj, Mtx view, s32 cols, s32 rows, f32 nearZ, f32 farZ) {
    Mtx44 m;
    Mtx inv;
    Vec ray[4];
    Vec base[4];
    Vec dir;
    Vec origin;
    f32 t[4];
    f32 d;
    f32 halfW0;
    f32 halfW1;
    f32 halfH0;
    f32 halfH1;
    f32 dy;
    s32 i;
    s32 k;
    s32 last;

    origin.x = 0.0f;
    origin.y = 0.0f;
    origin.z = 0.0f;
    dir.x = 0.0f;
    dir.y = -1.0f;
    dir.z = 0.0f;

    PSMTXMultVec(view, &origin, &origin);
    PSMTXMultVec(view, &dir, &dir);
    PSVECSubtract(&dir, &origin, &dir);
    PSVECNormalize(&dir, &dir);
    d = -PSVECDotProduct(&dir, &origin);

    base[0].y = 0.0f;
    ray[0].x = 0.0f;
    halfW0 = 640.0f * nearZ / 1280.0f / 2.0f;
    halfH0 = 448.0f * nearZ / 1280.0f / 2.0f;
    nearZ = -nearZ;
    base[0].x = halfW0;
    ray[0].z = 0.0f;
    halfW1 = 640.0f * farZ / 1280.0f / 2.0f;
    base[1].x = halfW1;
    base[1].y = 0.0f;
    base[1].z = -farZ;
    ray[0].y = halfH0;
    base[0].z = nearZ;
    ray[1].x = 0.0f;
    base[2].x = halfW1;
    halfH1 = 448.0f * farZ / 1280.0f / 2.0f;
    base[2].z = -farZ;
    ray[2].x = halfW0 - halfW1;
    ray[2].z = nearZ - base[2].z;
    ray[1].y = halfH1;
    base[3].x = halfW1;
    base[3].y = -halfH1;
    ray[2].y = halfH0 - halfH1;
    ray[1].z = 0.0f;
    base[2].y = halfH1;
    base[3].z = base[1].z;
    ray[3].x = halfW0 - halfW1;
    ray[3].y = -ray[2].y;
    ray[3].z = nearZ - base[3].z;

    for (i = 0; i < 4; i++) {
        t[i] = PSVECDotProduct(&dir, &ray[i]);
        if (t[i] == 0.0f) {
            ray[i].z = 0.0f;
        } else {
            t[i] = -(d + PSVECDotProduct(&dir, &base[i])) / t[i];
            PSVECScale(&ray[i], t[i], &ray[i]);
            PSVECAdd(&base[i], &ray[i], &ray[i]);
        }
        if (t[i] < 0.0f) {
            t[i] = -t[i];
        }
    }

    if (ray[2].z <= nearZ && ray[2].z >= -farZ && ray[3].z <= nearZ && ray[3].z >= -farZ) {
        memcpy(&ray[0], &ray[2], sizeof(Vec));
        memcpy(&ray[1], &ray[3], sizeof(Vec));
    } else if (!(t[0] <= 1.0f && t[1] <= 1.0f)) {
        if (t[0] <= 1.0f || t[1] <= 1.0f) {
            if (ray[2].z <= nearZ && ray[2].z >= -farZ) {
                memcpy(&ray[3], &ray[2], sizeof(Vec));
            }
            if (t[0] < 1.0f) {
                memcpy(&ray[1], &ray[3], sizeof(Vec));
            } else {
                memcpy(&ray[0], &ray[3], sizeof(Vec));
            }
        } else {
            return 0;
        }
    }

    PSMTXInverse(view, inv);

    PSMTXMultVec(inv, &ray[1], &ray[2]);
    last = rows - 1;
    lbl_1_bss_F6E0[last][0].x = ray[2].x;
    lbl_1_bss_F6E0[last][0].z = ray[2].z;
    ray[2].x = -ray[1].x;
    ray[2].y = ray[1].y;
    ray[2].z = ray[1].z;
    PSMTXMultVec(inv, &ray[2], &ray[2]);
    lbl_1_bss_F6E0[0][0].x = ray[2].x;
    lbl_1_bss_F6E0[0][0].z = ray[2].z;

    PSMTXMultVec(inv, &ray[0], &ray[2]);
    lbl_1_bss_F6E0[last][1].x = ray[2].x;
    lbl_1_bss_F6E0[last][1].z = ray[2].z;
    ray[2].x = -ray[0].x;
    ray[2].y = ray[0].y;
    ray[2].z = ray[0].z;
    PSMTXMultVec(inv, &ray[2], &ray[2]);
    lbl_1_bss_F6E0[0][1].x = ray[2].x;
    lbl_1_bss_F6E0[0][1].z = ray[2].z;

    PSMTX44Identity(m);
    memcpy(m, view, sizeof(Mtx));
    PSMTX44Concat(proj, m, m);
    C_MTX44Inverse(m, m);
    PSMTX44MultVec(proj, &ray[0], &ray[0]);
    PSMTX44MultVec(proj, &ray[1], &ray[1]);

    dy = ray[0].y - ray[1].y;
    if (dy < 0.0f) {
        dy = -dy;
    }

    cols = (f32)cols * (dy + 2.0f / (f32)cols) / 2.0f;
    if (cols < 2) {
        cols = 2;
    }

    k = cols - 1;
    lbl_1_bss_F6E0[0][k].x = lbl_1_bss_F6E0[0][1].x;
    lbl_1_bss_F6E0[0][k].z = lbl_1_bss_F6E0[0][1].z;
    lbl_1_bss_F6E0[last][k].x = lbl_1_bss_F6E0[last][1].x;
    lbl_1_bss_F6E0[last][k].z = lbl_1_bss_F6E0[last][1].z;

    PSVECSubtract(&ray[0], &ray[1], &ray[2]);

    while (--k != 0) {
        PSVECScale(&ray[2], (f32)k / (f32)(cols - 1), &ray[3]);
        PSVECAdd(&ray[1], &ray[3], &ray[3]);
        PSMTX44MultVec(m, &ray[3], &origin);
        lbl_1_bss_F6E0[last][k].x = origin.x;
        lbl_1_bss_F6E0[last][k].z = origin.z;
        ray[3].x = -ray[3].x;
        PSMTX44MultVec(m, &ray[3], &origin);
        lbl_1_bss_F6E0[0][k].x = origin.x;
        lbl_1_bss_F6E0[0][k].z = origin.z;
    }

    ray[0].y = 0.0f;
    ray[1].y = 0.0f;

    for (i = 0; i < cols; i++) {
        ray[0].x = lbl_1_bss_F6E0[0][i].x;
        ray[0].z = lbl_1_bss_F6E0[0][i].z;
        k = rows - 1;
        ray[1].x = lbl_1_bss_F6E0[k][i].x - lbl_1_bss_F6E0[0][i].x;
        ray[1].z = lbl_1_bss_F6E0[k][i].z - lbl_1_bss_F6E0[0][i].z;
        while (--k != 0) {
            PSVECScale(&ray[1], (f32)k / (f32)(rows - 1), &ray[2]);
            PSVECAdd(&ray[0], &ray[2], &ray[2]);
            lbl_1_bss_F6E0[k][i].x = ray[2].x;
            lbl_1_bss_F6E0[k][i].z = ray[2].z;
        }
    }

    return cols;
}

// .text:0x00022F4C size:0x14C
void fn_1_22F4C(s32 n, s32 m, f32 *dst, f32 *src, f32 *other) {
    f64 wSq;
    f32 coeffNeighbor;
    f32 coeffCenter;
    s32 mMinus1;
    s32 k;
    s32 rowBase;
    s32 i;
    s32 j;

    wSq = (0.016666666666666666 * lbl_1_data_104C0) / lbl_1_data_104BC;
    wSq = wSq * wSq;
    coeffNeighbor = (f32)wSq;
    coeffCenter = (f32)(2.0 - 4.0 * wSq);
    mMinus1 = m - 1;

    rowBase = 0;
    for (i = 0; i < n; i++) {
        k = rowBase;
        j = 0;
        while (j < m) {
            s32 t = k++;
            f32 val = src[t];
            f32 prev = other[t];
            s32 right = (j + 1) % m;
            s32 left = (j + mMinus1) % m;

            dst[t] = coeffCenter * val
                + coeffNeighbor * (src[right + rowBase] + (src[left + rowBase]
                    + (src[j + m * ((i + n - 1) % n)] + src[j + m * ((i + 1) % n)])))
                - prev;
            j++;
            dst[t] *= lbl_1_data_104C4;
        }
        rowBase += m;
    }
}

// .text:0x00022DF4 size:0x158
void fn_1_22DF4(DrawingSceneStruct *arg0) {
    *(f32 *)((u8 *)arg0 + 0x18) = 0.01f;
    *(f32 *)((u8 *)arg0 + 0x1c) = 20.0f;
    *((u8 *)arg0 + 0x25) = 0;
    *((u8 *)arg0 + 0x20) = 10;
    *((u8 *)arg0 + 0x21) = 10;
    *((u8 *)arg0 + 0x22) = 1;
    *((u8 *)arg0 + 0x23) = 0;
    *((u8 *)arg0 + 0x24) = 0;

    fn_80038E2C((lbl_1_bss_6FB8));

    fn_1_21180(arg0);
}

// .text:0x00022874 size:0x580
BOOL fn_1_22874(DrawingSceneStruct *arg0) {
    DrawingSceneStruct *item = currentDrawingItem;
    s32 step;
    s32 row;
    u8 old21;
    u16 f;

    if (AtBat_ButtonInput1._00 & INPUT_TRIGGER_R) {
        step = 100;
    } else if (*((u8 *)&AtBat_ButtonInput1 + 0x15) >= 0x50) {
        step = 1;
    } else {
        step = 10;
    }

    for (row = 0; row < 14; row++) {
        switch (row) {
        case 0:
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & INPUT_BUTTON_LEFT) {
                    *((u8 *)item + 0x20) -= 1;
                } else if (f & INPUT_BUTTON_RIGHT) {
                    *((u8 *)item + 0x20) += 1;
                }
                if (*((u8 *)item + 0x20) == 0) {
                    *((u8 *)item + 0x20) += 1;
                }
            }
            break;
        case 1:
            old21 = *((u8 *)item + 0x21);
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & INPUT_BUTTON_LEFT) {
                    *((u8 *)item + 0x21) = old21 - 1;
                } else if (f & INPUT_BUTTON_RIGHT) {
                    *((u8 *)item + 0x21) = old21 + 1;
                }
                if (*((u8 *)item + 0x21) < 2) {
                    *((u8 *)item + 0x21) += 1;
                }
            }
            break;
        case 2:
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & INPUT_BUTTON_LEFT) {
                    *(f32 *)(lbl_1_bss_6FB8 + 0x0) -= 0.001f * (f32)step;
                } else if (f & INPUT_BUTTON_RIGHT) {
                    *(f32 *)(lbl_1_bss_6FB8 + 0x0) += 0.001f * (f32)step;
                }
            }
            break;
        case 3:
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & INPUT_BUTTON_LEFT) {
                    *(f32 *)((u8 *)item + 0x18) -= 0.01f * (f32)step;
                } else if (f & INPUT_BUTTON_RIGHT) {
                    *(f32 *)((u8 *)item + 0x18) += 0.01f * (f32)step;
                }
            }
            break;
        case 4:
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & INPUT_BUTTON_LEFT) {
                    *(f32 *)(lbl_1_bss_6FB8 + 0x8) -= 0.01f * (f32)step;
                } else if (f & INPUT_BUTTON_RIGHT) {
                    *(f32 *)(lbl_1_bss_6FB8 + 0x8) += 0.01f * (f32)step;
                }
            }
            break;
        case 5:
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & INPUT_BUTTON_LEFT) {
                    *(f32 *)(lbl_1_bss_6FB8 + 0xc) -= 0.01f * (f32)step;
                } else if (f & INPUT_BUTTON_RIGHT) {
                    *(f32 *)(lbl_1_bss_6FB8 + 0xc) += 0.01f * (f32)step;
                }
            }
            break;
        case 6:
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & INPUT_BUTTON_LEFT) {
                    *(f32 *)(lbl_1_bss_6FB8 + 0x10) -= 0.01f * (f32)step;
                } else if (f & INPUT_BUTTON_RIGHT) {
                    *(f32 *)(lbl_1_bss_6FB8 + 0x10) += 0.01f * (f32)step;
                }
            }
            break;
        case 7:
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & INPUT_BUTTON_LEFT) {
                    *(f32 *)(lbl_1_bss_6FB8 + 0x14) -= 0.0001f * (f32)step;
                } else if (f & INPUT_BUTTON_RIGHT) {
                    *(f32 *)(lbl_1_bss_6FB8 + 0x14) += 0.0001f * (f32)step;
                }
            }
            break;
        case 8:
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & INPUT_BUTTON_LEFT) {
                    *(f32 *)((u8 *)item + 0x1c) -= (f32)step;
                } else if (f & INPUT_BUTTON_RIGHT) {
                    *(f32 *)((u8 *)item + 0x1c) += (f32)step;
                }
            }
            break;
        case 9:
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & (INPUT_BUTTON_LEFT | INPUT_BUTTON_RIGHT)) {
                    *((u8 *)item + 0x22) = !*((u8 *)item + 0x22);
                }
            }
            break;
        case 10:
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & (INPUT_BUTTON_LEFT | INPUT_BUTTON_RIGHT)) {
                    *((u8 *)item + 0x23) = !*((u8 *)item + 0x23);
                }
            }
            break;
        case 11:
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & INPUT_BUTTON_LEFT) {
                    lbl_1_data_104D0[0] -= 0.125;
                } else if (f & INPUT_BUTTON_RIGHT) {
                    lbl_1_data_104D0[0] += 0.125;
                }
            }
            break;
        case 12:
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & INPUT_BUTTON_LEFT) {
                    lbl_1_data_104D0[1] -= 0.125;
                } else if (f & INPUT_BUTTON_RIGHT) {
                    lbl_1_data_104D0[1] += 0.125;
                }
            }
            break;
        case 13:
            if (row == *((u8 *)item + 0x25)) {
                f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);
                if (f & INPUT_BUTTON_LEFT) {
                    lbl_1_data_104D0[2] -= 0.125;
                } else if (f & INPUT_BUTTON_RIGHT) {
                    lbl_1_data_104D0[2] += 0.125;
                }
            }
            break;
        }
    }

    f = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

    if (f & INPUT_BUTTON_UP) {
        if (*((u8 *)item + 0x25) == 0) {
            *((u8 *)item + 0x25) = 14;
        }
        *((u8 *)item + 0x25) -= 1;
    } else if (f & INPUT_BUTTON_DOWN) {
        *((u8 *)item + 0x25) += 1;
        if (*((u8 *)item + 0x25) == 14) {
            *((u8 *)item + 0x25) = 0;
        }
    }

    return old21 != *((u8 *)item + 0x21);
}

// .text:0x00022644 size:0x230
void fn_1_22644(void) {
    DrawingSceneStruct *item = currentDrawingItem;

    fn_800AD038(*(void **)(lbl_80366158 + 0x8));
    *((u8 *)item + 0x25) = 0;

    fn_1_22DF4(currentDrawingItem);

    fn_1_23AD8(lbl_1_bss_47010, (f32 *)(lbl_1_bss_43EE0 + 0x48), (f32 *)(lbl_1_bss_43EE0 + 0x3c));

    currentDrawingItem->func = fn_1_225B8;
}

// .text:0x000225B8 size:0x8C
void fn_1_225B8(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    DrawingSceneStruct *newItem;

    switch (*((u8 *)item + 0x25)) {
    case 0:
        newItem = insertGraphicDrawingFunction(fn_1_20BD8, 1);
        *((u8 *)newItem + 0x25) = 0;
        newItem->state = 0;
        *((u8 *)item + 0x25) += 1;
        break;
    case 1:
        if (item->state != 0) {
            item->func = fn_1_21408;
        }
        break;
    }
}

static inline void updateChainLinks(void *arg0, s32 arg1, Mtx arg2) {
    u8 *rec;
    s32 j;

    j = 20;
    while (j-- != 0) {
        u8 *table1;
        Mtx m;
        Vec diff;
        Vec v;
        Quaternion q1;
        Quaternion q2;

        rec = (u8 *)lbl_1_bss_6BE0 + j * 0x90 + 0x34;
        table1 = (u8 *)arg0 + j * 0x40;

        *(u8 *)(rec + 0x6c) = arg1 > j;

        if (j < arg1) {
            PSVECSubtract((Vec *)((u8 *)arg0 + (j + 1) * 0x40 + 0xc), (Vec *)(table1 + 0xc), &diff);
            PSVECScale(&diff, 0.5f, &v);
            PSVECAdd((Vec *)(table1 + 0xc), &v, &v);
            CTRLSetTranslation((Control *)(rec + 0x10), v.x, -v.y, v.z);

            if (PSVECMag(&diff)) {
                f32 angle1;

                PSVECNormalize(&diff, &diff);
                diff.y = -diff.y;

                angle1 = (f32)((3.141592502593994 * (2.5 + (f64)(j & 1))) / 6.0);

                v.x = 1.0f;
                v.y = 0.0f;
                v.z = 0.0f;

                C_QUATRotAxisRad(&q1, &v, angle1);

                {
                    f32 dot = PSVECDotProduct(&diff, &v);
                    f32 angle2 = (f32)acos(dot);
                    f32 mag2;

                    PSVECCrossProduct(&v, &diff, &v);
                    mag2 = PSVECMag(&v);

                    if (mag2) {
                        C_QUATRotAxisRad(&q2, &v, angle2);
                        PSQUATMultiply(&q2, &q1, &q1);
                    }
                }

                CTRLSetQuat((Control *)(rec + 0x10), q1.x, q1.y, q1.z, q1.w);
            }

            CTRLSetScale((Control *)(rec + 0x10), lbl_1_data_104D0[0], lbl_1_data_104D0[1], lbl_1_data_104D0[2]);
            fn_800BDA24(rec);
        }

        PSMTXTrans(m, 0.0f, 0.0f, 0.0f);
        PSMTXConcat(arg2, m, m);

        *((u8 *)(*(void **)rec) + 0x98) |= 3;
    }

    fn_800BD670(lbl_1_bss_6BE0, arg2);
}

// .text:0x00021CE8 size:0x8D0
void fn_1_21CE8(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    f32 windVec[3];
    ChainNode *chain;
    s32 i;

    if (fn_1_22874(item) != 0 || (AtBat_ButtonInput1._02 & INPUT_BUTTON_A)) {
        fn_1_21180(item);
    } else if (AtBat_ButtonInput1._02 & INPUT_BUTTON_B) {
        currentDrawingItem->func = fn_1_21408;
    }

    if (*((u8 *)item + 0x23) != 0) {
        f32 windMul;
        s8 stickX;
        s8 substickY;
        s8 stickY;

        if (AtBat_ButtonInput1._75 >= 0x50) {
            windMul = 0.0001f * *(f32 *)((u8 *)item + 0x1c);
        } else {
            windMul = 0.00001f * *(f32 *)((u8 *)item + 0x1c);
        }

        chain = lbl_1_bss_6FE0;
        stickX = AtBat_ButtonInput1._70;
        substickY = AtBat_ButtonInput1._73;
        stickY = AtBat_ButtonInput1._71;
        chain[*((u8 *)item + 0x21) - 1].pos.x += (f32)stickX * windMul;
        chain[*((u8 *)item + 0x21) - 1].pos.y += (f32)substickY * windMul;
        chain[*((u8 *)item + 0x21) - 1].pos.z += (f32)stickY * windMul;

        memcpy(&chain[*((u8 *)item + 0x21) - 1].prevPos, &chain[*((u8 *)item + 0x21) - 1].pos, sizeof(Vec));

        windVec[0] = 0.0f;
        windVec[1] = 0.0f;
        windVec[2] = 0.0f;
    } else {
        u8 stickX = AtBat_ButtonInput1._70;
        u8 substickY = AtBat_ButtonInput1._73;
        u8 stickY = AtBat_ButtonInput1._71;
        f32 windDrag = *(f32 *)((u8 *)item + 0x1c);

        windVec[0] = windDrag * ((f32)(s8)stickX * lbl_1_bss_6FE0[*((u8 *)item + 0x21) - 1]._00);
        windVec[1] = windDrag * ((f32)(s8)substickY * lbl_1_bss_6FE0[*((u8 *)item + 0x21) - 1]._00);
        windVec[2] = windDrag * ((f32)(s8)stickY * lbl_1_bss_6FE0[*((u8 *)item + 0x21) - 1]._00);
    }

    fn_80038B48((lbl_1_bss_6FB8), (lbl_1_bss_6FE0), *((u8 *)item + 0x21), windVec);

    GXSetProjection(lbl_1_bss_47010, GX_PERSPECTIVE);
    GXClearVtxDesc();
    GXSetCullMode(GX_CULL_NONE);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXLoadPosMtxImm((f32 (*)[4])lbl_1_bss_43EE0, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);

    fn_1_21040();

    fn_1_21298(item);

    updateChainLinks(lbl_1_bss_6FE0, *((u8 *)item + 0x21) - 1, (f32 (*)[4])lbl_1_bss_43EE0);
}

// .text:0x00021408 size:0x8E0
void fn_1_21408(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    f32 windVec[3];
    ChainNode *chain;
    s32 i;

    if (AtBat_ButtonInput1._02 & INPUT_BUTTON_START) {
        item->func = fn_1_21CE8;
    } else if (AtBat_ButtonInput1._02 & INPUT_BUTTON_A) {
        fn_1_21180(item);
    } else if (AtBat_ButtonInput1._02 & INPUT_BUTTON_B) {
        lbl_1_bss_6BE0 = NULL;
        item->func = fn_1_24778;
    }

    fn_1_121D4(lbl_1_bss_43EE0);

    if (*((u8 *)item + 0x23) != 0) {
        f32 windMul;
        s8 stickX;
        s8 substickY;
        s8 stickY;

        if (AtBat_ButtonInput1._75 >= 0x50) {
            windMul = 0.0001f * *(f32 *)((u8 *)item + 0x1c);
        } else {
            windMul = 0.00001f * *(f32 *)((u8 *)item + 0x1c);
        }

        chain = lbl_1_bss_6FE0;
        stickX = AtBat_ButtonInput1._70;
        substickY = AtBat_ButtonInput1._73;
        stickY = AtBat_ButtonInput1._71;
        chain[*((u8 *)item + 0x21) - 1].pos.x += (f32)stickX * windMul;
        chain[*((u8 *)item + 0x21) - 1].pos.y += (f32)substickY * windMul;
        chain[*((u8 *)item + 0x21) - 1].pos.z += (f32)stickY * windMul;

        memcpy(&chain[*((u8 *)item + 0x21) - 1].prevPos, &chain[*((u8 *)item + 0x21) - 1].pos, sizeof(Vec));

        windVec[0] = 0.0f;
        windVec[1] = 0.0f;
        windVec[2] = 0.0f;
    } else {
        u8 stickX = AtBat_ButtonInput1._70;
        u8 substickY = AtBat_ButtonInput1._73;
        u8 stickY = AtBat_ButtonInput1._71;
        f32 windDrag = *(f32 *)((u8 *)item + 0x1c);

        windVec[0] = windDrag * ((f32)(s8)stickX * lbl_1_bss_6FE0[*((u8 *)item + 0x21) - 1]._00);
        windVec[1] = windDrag * ((f32)(s8)substickY * lbl_1_bss_6FE0[*((u8 *)item + 0x21) - 1]._00);
        windVec[2] = windDrag * ((f32)(s8)stickY * lbl_1_bss_6FE0[*((u8 *)item + 0x21) - 1]._00);
    }

    fn_80038B48((lbl_1_bss_6FB8), (lbl_1_bss_6FE0), *((u8 *)item + 0x21), windVec);

    GXSetProjection(lbl_1_bss_47010, GX_PERSPECTIVE);
    GXClearVtxDesc();
    GXSetCullMode(GX_CULL_NONE);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXLoadPosMtxImm((f32 (*)[4])lbl_1_bss_43EE0, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);

    fn_1_21040();

    fn_1_21298(item);

    if (lbl_1_bss_6BE0 != NULL) {
        updateChainLinks(lbl_1_bss_6FE0, *((u8 *)item + 0x21) - 1, (f32 (*)[4])lbl_1_bss_43EE0);
    }
}

// .text:0x00021298 size:0x170
void fn_1_21298(DrawingSceneStruct *arg0) {
    s32 i;
    u8 *entry;

    if (*((u8 *)arg0 + 0x22) != 0) {
        GXBegin(GX_LINESTRIP, GX_VTXFMT0, (*((u8 *)arg0 + 0x21) - 1) * 2);

        i = *((u8 *)arg0 + 0x21);
        while (--i != 0) {
            entry = (u8 *)lbl_1_bss_6FE0 + i * 0x40;

            GX_WRITE_F32(*(f32 *)(entry + 0xc));
            GX_WRITE_F32(0.0f);
            GX_WRITE_F32(*(f32 *)(entry + 0x14));
            GX_WRITE_U32(0x80);

            GX_WRITE_F32(*(f32 *)(entry - 0x34));
            GX_WRITE_F32(0.0f);
            GX_WRITE_F32(*(f32 *)(entry - 0x2c));
            GX_WRITE_U32(0x80);
        }
    }

    if (*((u8 *)arg0 + 0x24) != 0) {
        GXBegin(GX_LINESTRIP, GX_VTXFMT0, (*((u8 *)arg0 + 0x21) - 1) * 2);

        i = *((u8 *)arg0 + 0x21);
        while (--i != 0) {
            u32 color;

            entry = (u8 *)lbl_1_bss_6FE0 + i * 0x40;

            GX_WRITE_F32(*(f32 *)(entry + 0xc));
            GX_WRITE_F32(-*(f32 *)(entry + 0x10));
            GX_WRITE_F32(*(f32 *)(entry + 0x14));
            color = lbl_1_data_104DC[i % 6];
            GX_WRITE_U32(color);

            GX_WRITE_F32(*(f32 *)(entry - 0x34));
            GX_WRITE_F32(-*(f32 *)(entry - 0x30));
            GX_WRITE_F32(*(f32 *)(entry - 0x2c));
            GX_WRITE_U32(color);
        }
    }
}

// .text:0x00021180 size:0x118
void fn_1_21180(DrawingSceneStruct *arg0) {
    f32 c1 = 1.0f;
    s32 val = *((u8 *)arg0 + 0x20);
    f32 floatVal = (f32)val;
    f32 ratio = c1 / floatVal;
    f32 c3 = 2.0f;
    f32 speed;
    f32 t;
    f32 speed2;
    f32 result;
    u8 idx;

    *(u32 *)(lbl_1_bss_6FB8 + 0x20) = val;
    speed = ratio / 60.0f;
    t = c3 * speed;
    *(f32 *)(lbl_1_bss_6FB8 + 0x18) = speed;
    speed2 = speed * speed;
    result = c1 / t;
    *(f32 *)(lbl_1_bss_6FB8 + 0x1c) = speed2;
    *(f32 *)(lbl_1_bss_6FB8 + 0x24) = result;

    if (AtBat_ButtonInput1._00 & INPUT_BUTTON_X) {
        *(u32 *)(lbl_1_bss_6FB8 + 0x20) = 1;
    }

    idx = *((u8 *)arg0 + 0x21);
    fn_80038CD0(idx, lbl_1_bss_6FB8, (lbl_1_bss_6FE0), 0.2f, *(f32 *)((u8 *)arg0 + 0x18));

    {
        s32 last = *((u8 *)arg0 + 0x21) - 1;

        lbl_1_bss_6FA8.x = lbl_1_bss_6FE0[last].pos.x;
        lbl_1_bss_6FA8.y = lbl_1_bss_6FE0[last].pos.y;
        lbl_1_bss_6FA8.z = lbl_1_bss_6FE0[last].pos.z;
        lbl_1_bss_6FE0[last]._3C = *((u8 *)arg0 + 0x23);
    }
}

// .text:0x00021040 size:0x140
void fn_1_21040(void) {
    s32 i;

    GXBegin(GX_LINES, GX_VTXFMT0, 0x2c);

    for (i = 0; i < 11; i++) {
        u32 color = 0xFFFFFFFF;

        if (i == 5) {
            color = 0xFF0000FF;
        }

        GX_WRITE_F32((f32)((i - 5) * 10));
        GX_WRITE_F32(0.0f);
        GX_WRITE_F32(-50.0f);
        GX_WRITE_U32(color);

        GX_WRITE_F32((f32)((i - 5) * 10));
        GX_WRITE_F32(0.0f);
        GX_WRITE_F32(50.0f);
        GX_WRITE_U32(color);

        if (i == 5) {
            color = 0x00FF00FF;
        }

        GX_WRITE_F32(-50.0f);
        GX_WRITE_F32(0.0f);
        GX_WRITE_F32((f32)((i - 5) * 10));
        GX_WRITE_U32(color);

        GX_WRITE_F32(50.0f);
        GX_WRITE_F32(0.0f);
        GX_WRITE_F32((f32)((i - 5) * 10));
        GX_WRITE_U32(color);
    }
}

// .text:0x00020F8C size:0xB4
void fn_1_20F8C(void) {
    DrawingSceneStruct *item = currentDrawingItem->currentDrawingItem;

    switch (currentDrawingItem->state) {
    case 0:
        if (lbl_803C6CF8.cancel.bytes[1] != 1) {
            break;
        }
        *(void **)((u8 *)item + 0x14) = ARAMTransfer(chainModelFileDescriptorDebug, 0, 0, 0);
        currentDrawingItem->state += 1;
        break;
    case 1:
        if (lbl_803C6CF8.cancel.bytes[1] != 1) {
            break;
        }
        item->state = 1;
        break;
    }
}

// .text:0x00020E00 size:0x18C
void fn_1_20E00(void *arg0) {
    u16 j;
    GXColor lightColor = {0x80, 0x80, 0xFF, 0xFF};
    GXColor color;
    u8 *field;
    u32 field0;
    u32 field1;
    u8 *layout;
    u8 *geo;

    LITAlloc(&lbl_1_bss_6FA4);
    LITInitAttn(lbl_1_bss_6FA4, 1.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f);
    LITInitPos(lbl_1_bss_6FA4, 5.0f, 5.0f, 5.0f);
    LITInitDir(lbl_1_bss_6FA4, 0.0f, 0.0f, 0.0f);

    color = lightColor;
    LITInitColor(lbl_1_bss_6FA4, &color);

    field = *(u8 **)((u8 *)arg0 + 0x14);
    field0 = *(u32 *)field;
    field1 = *(u32 *)(field + 4);
    layout = field + field0;
    geo = field + field1;

    lbl_1_bss_6BE0 = ActorObjectInitTable(0x14, field0, field);

    LoadActorLayout(layout);
    convertGeometryAndSknHeader(geo, 0);
    haveActLayoutPointToGeoHeader(layout, geo);

    for (j = 0; j < 20; j++) {
        animateBallRelated(lbl_1_bss_6BE0, j, j, layout, 0, 0);
        fn_800B2C08(*(void **)((u8 *)lbl_1_bss_6BE0 + j * 0x90 + 0x34), 0);
        fn_800BD548((u8 *)lbl_1_bss_6BE0 + j * 0x90 + 0x34, 1, lbl_1_bss_6FA4);
    }
}

// .text:0x00020DC8 size:0x38
void fn_1_20DC8(void) {
    DrawingSceneStruct *item = insertGraphicDrawingFunction(fn_1_20BD8, 1);

    *((u8 *)item + 0x25) = 0;
    item->state = 0;
}

// .text:0x00020BD8 size:0x1F0
void fn_1_20BD8(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    u8 state = *((u8 *)item + 0x25);

    switch (state) {
    case 0: {
        DrawingSceneStruct *newItem = insertGraphicDrawingFunction(fn_1_20F8C, 1);

        newItem->state = 0;
        *((u8 *)item + 0x25) += 1;
        break;
    }
    case 1: {
        if (item->state != 0) {
            fn_1_20E00(item);

            item->currentDrawingItem->state = 1;
            removeCurrentDrawingItem();
        }
        break;
    }
    }
}

// .text:0x00020950 size:0x288
void fn_1_20950(void *arg0, s32 arg1, Mtx arg2) {
    u8 *rec;
    s32 j;

    j = 20;
    while (j-- != 0) {
        u8 *table1;
        Mtx m;
        Vec diff;
        Vec v;
        Quaternion q1;
        Quaternion q2;

        rec = (u8 *)lbl_1_bss_6BE0 + j * 0x90 + 0x34;
        table1 = (u8 *)arg0 + j * 0x40;

        *(u8 *)(rec + 0x6c) = arg1 > j;

        if (j < arg1) {
            PSVECSubtract((Vec *)((u8 *)arg0 + (j + 1) * 0x40 + 0xc), (Vec *)(table1 + 0xc), &diff);
            PSVECScale(&diff, 0.5f, &v);
            PSVECAdd((Vec *)(table1 + 0xc), &v, &v);
            CTRLSetTranslation((Control *)(rec + 0x10), v.x, -v.y, v.z);

            if (PSVECMag(&diff)) {
                f32 angle1;

                PSVECNormalize(&diff, &diff);
                diff.y = -diff.y;

                angle1 = (f32)((3.141592502593994 * (2.5 + (f64)(j & 1))) / 6.0);

                v.x = 1.0f;
                v.y = 0.0f;
                v.z = 0.0f;

                C_QUATRotAxisRad(&q1, &v, angle1);

                {
                    f32 dot = PSVECDotProduct(&diff, &v);
                    f32 angle2 = (f32)acos(dot);
                    f32 mag2;

                    PSVECCrossProduct(&v, &diff, &v);
                    mag2 = PSVECMag(&v);

                    if (mag2) {
                        C_QUATRotAxisRad(&q2, &v, angle2);
                        PSQUATMultiply(&q2, &q1, &q1);
                    }
                }

                CTRLSetQuat((Control *)(rec + 0x10), q1.x, q1.y, q1.z, q1.w);
            }

            CTRLSetScale((Control *)(rec + 0x10), lbl_1_data_104D0[0], lbl_1_data_104D0[1], lbl_1_data_104D0[2]);
            fn_800BDA24(rec);
        }

        PSMTXTrans(m, 0.0f, 0.0f, 0.0f);
        PSMTXConcat(arg2, m, m);

        *((u8 *)(*(void **)rec) + 0x98) |= 3;
    }

    fn_800BD670(lbl_1_bss_6BE0, arg2);
}

// .text:0x00020890 size:0xC0
void fn_1_20890(void) {
    f32 c = 0.0f;

    C_MTXOrtho(lbl_1_bss_47010, c, 448.0f, c,
        640.0f, 0.5f, (-1.0f));
    GXSetProjection(lbl_1_bss_47010, GX_ORTHOGRAPHIC);

    {
        Mtx m;

        PSMTXIdentity(m);
        GXLoadPosMtxImm(m, GX_PNMTX0);
        GXSetCurrentMtx(GX_PNMTX0);
        GXLoadTexMtxImm(m, GX_TEXMTX0, GX_MTX2x4);
    }

    fn_80048C14(3);
    fn_80048E00(0, 0x20);
    fn_80048E00(1, 0);
}

// .text:0x000207D4 size:0xBC
void fn_1_207D4(void) {
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 8);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
}

// .text:0x00020640 size:0x194
void fn_1_20640(void *arg0, u32 *entries) {
    s32 i;

    GXSetNumTevStages(*((u8 *)arg0 + 0x22));
    GXSetNumTexGens(*((u8 *)arg0 + 0x22));

    for (i = 0; i < *((u8 *)arg0 + 0x22); i++) {
        u32 entry;

        GXSetTexCoordGen2(i, GX_TG_MTX2X4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);

        if (i != 0) {
            GXSetTevColorIn(i, GX_CC_CPREV, GX_CC_TEXC, GX_CC_RASA, GX_CC_ZERO);
            GXSetTevColorOp(i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(i, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevAlphaOp(i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        } else {
            GXSetTevColorIn(i, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
            GXSetTevColorOp(i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(i, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
            GXSetTevAlphaOp(i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        }

        entry = entries[i];
        {
            u32 tlutIdx = entry & 0x7fffffff;

            GXLoadTexObj(&lbl_1_bss_6EA4[entry], i);

            if (entry & 0x80000000) {
                GXLoadTlut(&lbl_1_bss_6E44[tlutIdx], i);
            }
        }
    }
}

// .text:0x0002051C size:0x124
s32 fn_1_2051C(void *arg0, GXTexObj *arg1, GXTlutObj *arg2, u32 arg3) {
    u8 *info = (u8 *)arg0;
    u8 f15 = info[0x15];
    u8 f16 = info[0x16];
    s32 useMip = (f15 != f16);

    if (*(u32 *)(info + 0x4) != 0) {
        GXInitTexObjCI(arg1, *(void **)(info + 0x0), *(u16 *)(info + 0xa), *(u16 *)(info + 0x8),
            info[0x17], info[0xc], info[0xd], useMip, arg3);
        GXInitTlutObj(arg2, *(void **)(info + 0x4), info[0x1a], *(u16 *)(info + 0x18));
    } else {
        GXInitTexObj(arg1, *(void **)(info + 0x0), *(u16 *)(info + 0xa), *(u16 *)(info + 0x8),
            info[0x17], info[0xc], info[0xd], useMip);
    }

    GXInitTexObjLOD(arg1, info[0xe], info[0xf], (f32)info[0x15], (f32)info[0x16],
        *(f32 *)(info + 0x10), 0, 0, 0);

    return !!*(u32 *)(info + 0x4);
}

// .text:0x0002040C size:0x110
void fn_1_2040C(void) {
    f32 c = 0.0f;
    DrawingSceneStruct *item = currentDrawingItem;

    *(u32 *)((u8 *)item + 0x1c) = 0;
    *((u8 *)item + 0x23) = 0;
    *((u8 *)item + 0x24) = 0;
    *((u8 *)item + 0x20) = 0;
    *((u8 *)item + 0x21) = 0;
    *((u8 *)item + 0x22) = 1;

    C_MTXOrtho(lbl_1_bss_47010, c, 448.0f, c,
        640.0f, 0.5f, (-1.0f));
    GXSetProjection(lbl_1_bss_47010, GX_ORTHOGRAPHIC);

    {
        Mtx m;

        PSMTXIdentity(m);
        GXLoadPosMtxImm(m, GX_PNMTX0);
        GXSetCurrentMtx(GX_PNMTX0);
        GXLoadTexMtxImm(m, GX_TEXMTX0, GX_MTX2x4);
    }

    fn_80048C14(3);
    fn_80048E00(0, 0x20);
    fn_80048E00(1, 0);
    fn_800AD038(*(void **)(lbl_80366158 + 0x8));
    currentDrawingItem->func = fn_1_2004C;
}

// .text:0x000202A4 size:0x168
void fn_1_202A4(void) {
    DrawingSceneStruct *item = currentDrawingItem;

    fn_80048C1C();
    lbl_1_data_10508[*((u8 *)item + 0x20)](item);

    if (AtBat_ButtonInput1._02 & INPUT_BUTTON_B) {
        u32 colorWord = 0x11775500;

        GXSetCopyClear(*(GXColor *)&colorWord, 0xffffff);
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
    }

    fn_80048D4C();
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 8);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);

    lbl_1_data_10510[*((u8 *)item + 0x20)](item);

    fn_80048C28();
}

// .text:0x0002004C size:0x258
void fn_1_2004C(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    u32 indices[9] = {5, 6, 7, 8, 9, 0xd, 0x60, 0x61, 0x55};

    switch (*((u8 *)item + 0x21)) {
    case 0: {
        *(void **)((u8 *)item + 0x18) = ARAMTransfer(StadiumFiles_debug_10518, 0, 0, 0);
        *((u8 *)item + 0x21) += 1;
        break;
    }
    case 1: {
        u8 *hdr;
        u32 i;

        if (lbl_803C6CF8.cancel.bytes[1] != 1) {
            break;
        }

        hdr = *(u8 **)((u8 *)item + 0x18);
        *(void **)((u8 *)item + 0x14) = hdr + *(u32 *)(hdr + 0x14);
        convertTextureHeader(*(void **)((u8 *)item + 0x14));

        for (i = 0; i < 8; i++) {
            lbl_1_bss_6E24[i] = i;

            if (fn_1_2051C(*(u8 **)((u8 *)item + 0x14) + indices[i] * 0x20 + 4, (GXTexObj *)((lbl_1_bss_6EA4)) + i,
                           (GXTlutObj *)((lbl_1_bss_6E44)) + i, i)) {
                lbl_1_bss_6E24[i] |= 0x80000000;
            }
        }

        *((u8 *)item + 0x21) = 0;
        currentDrawingItem->func = fn_1_202A4;
        break;
    }
    }
}

// .text:0x0001FD78 size:0x2D4
void fn_1_1FD78(void *arg0) {
    u8 *item = arg0;
    u32 step = (AtBat_ButtonInput1._00 & INPUT_TRIGGER_R) ? 0x64 : 1;
    s32 i;

    for (i = 0; i < 6; i++) {
        u8 sel = *(item + 0x21);

        switch (i) {
        case 0:
            if (i == sel) {
                u16 btn = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

                if (btn & INPUT_BUTTON_LEFT) {
                    if (*(item + 0x20) == 0) {
                        *(item + 0x20) = 2;
                    }
                    *(item + 0x20) -= 1;
                } else if (btn & INPUT_BUTTON_RIGHT) {
                    *(item + 0x20) += 1;
                    if (*(item + 0x20) == 2) {
                        *(item + 0x20) = 0;
                    }
                }
            }
            break;
        case 1: {
            s32 delta = fn_80048EA8(0);

            if (i == *(item + 0x21)) {
                u16 btn = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

                if (btn & INPUT_BUTTON_LEFT) {
                    delta -= 1;
                } else if (btn & INPUT_BUTTON_RIGHT) {
                    delta += 1;
                }
                fn_80048E00(0, delta);
            }
            break;
        }
        case 2: {
            s32 delta = fn_80048EA8(1);

            if (i == *(item + 0x21)) {
                u16 btn = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

                if (btn & INPUT_BUTTON_LEFT) {
                    delta -= 1;
                } else if (btn & INPUT_BUTTON_RIGHT) {
                    delta += 1;
                }
                fn_80048E00(1, delta);
            }
            break;
        }
        case 3:
            if (i == sel) {
                u16 btn = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

                if (btn & INPUT_BUTTON_LEFT) {
                    if (*(u32 *)(item + 0x1c) <= step) {
                        *(u32 *)(item + 0x1c) = 0;
                    } else {
                        *(u32 *)(item + 0x1c) -= step;
                    }
                } else if (btn & INPUT_BUTTON_RIGHT) {
                    *(u32 *)(item + 0x1c) += step;
                    if (*(u32 *)(item + 0x1c) > 0x1000) {
                        *(u32 *)(item + 0x1c) = 0x1000;
                    }
                }
            }
            break;
        case 4:
            if (i == sel) {
                u16 btn = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

                if (btn & INPUT_BUTTON_LEFT) {
                    *(item + 0x23) -= 1;
                } else if (btn & INPUT_BUTTON_RIGHT) {
                    *(item + 0x23) += 1;
                }
            }
            break;
        case 5:
            if (i == sel) {
                u16 btn = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

                if (btn & INPUT_BUTTON_LEFT) {
                    if (*(item + 0x22) > 1) {
                        *(item + 0x22) -= 1;
                    }
                } else if (btn & INPUT_BUTTON_RIGHT) {
                    if (*(item + 0x22) < 4) {
                        *(item + 0x22) += 1;
                    }
                }
            }
            break;
        }
    }

    {
        u16 btn = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

        if (btn & INPUT_BUTTON_UP) {
            if (*(item + 0x21) == 0) {
                *(item + 0x21) = 6;
            }
            *(item + 0x21) -= 1;
        } else if (btn & INPUT_BUTTON_DOWN) {
            *(item + 0x21) += 1;
            if (*(item + 0x21) == 6) {
                *(item + 0x21) = 0;
            }
        }
    }
}

// .text:0x0001F900 size:0x478
void fn_1_1F900(void *arg0) {
    u8 *item = arg0;
    s32 n;

    for (n = 0; n < *(u32 *)(item + 0x1c); n++) {
        s32 cell = (n % 480) % 48;
        s32 xIdx = cell % 8;
        s32 yIdx = cell / 8;
        u32 entries[4];
        s32 i;

        for (i = 0; i < *(item + 0x22); i++) {
            entries[i] = lbl_1_bss_6E24[(xIdx + yIdx) % 8];
        }

        GXSetNumTevStages(*(item + 0x22));
        GXSetNumTexGens(*(item + 0x22));

        for (i = 0; i < *(item + 0x22); i++) {
            u32 idx;

            GXSetTexCoordGen2(i, GX_TG_MTX2X4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);

            if (i != 0) {
                GXSetTevColorIn(i, GX_CC_CPREV, GX_CC_TEXC, GX_CC_RASA, GX_CC_ZERO);
                GXSetTevColorOp(i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(i, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                GXSetTevAlphaOp(i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            } else {
                GXSetTevColorIn(i, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
                GXSetTevColorOp(i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(i, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
                GXSetTevAlphaOp(i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            }

            idx = entries[i] & 0x7fffffff;
            GXLoadTexObj((GXTexObj *)((lbl_1_bss_6EA4)) + idx, i);
            if ((entries[i] & 0x80000000) != 0) {
                GXLoadTlut((GXTlutObj *)((lbl_1_bss_6E44)) + idx, i);
            }
        }

        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        {
            GXPosition3f32((f32)(xIdx * *(item + 0x23)), (f32)(yIdx * *(item + 0x23)), 0.0f);
            GX_WRITE_U32(-128);
            GX_WRITE_U16(0);
            GX_WRITE_U16(0);

            GXPosition3f32((f32)(xIdx * *(item + 0x23)), (f32)(yIdx * *(item + 0x23) + *(item + 0x23)), 0.0f);
            GX_WRITE_U32(-128);
            GX_WRITE_U16(0);
            GX_WRITE_U16(0x100);

            GXPosition3f32((f32)(xIdx * *(item + 0x23) + *(item + 0x23)), (f32)(yIdx * *(item + 0x23) + *(item + 0x23)), 0.0f);
            GX_WRITE_U32(-128);
            GX_WRITE_U16(0x100);
            GX_WRITE_U16(0x100);

            GXPosition3f32((f32)(xIdx * *(item + 0x23) + *(item + 0x23)), (f32)(yIdx * *(item + 0x23)), 0.0f);
            GX_WRITE_U32(-128);
            GX_WRITE_U16(0x100);
            GX_WRITE_U16(0);
        }
    }
}

// fn_1_20640's body, except entries[i] is re-read for the 0x80000000 test: the copy
// inlined into fn_1_1F618 differs from the standalone function in that one load.
static inline void setupTevStages(void *arg0, u32 *entries) {
    s32 i;

    GXSetNumTevStages(*((u8 *)arg0 + 0x22));
    GXSetNumTexGens(*((u8 *)arg0 + 0x22));

    for (i = 0; i < *((u8 *)arg0 + 0x22); i++) {
        u32 entry;

        GXSetTexCoordGen2(i, GX_TG_MTX2X4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);

        if (i != 0) {
            GXSetTevColorIn(i, GX_CC_CPREV, GX_CC_TEXC, GX_CC_RASA, GX_CC_ZERO);
            GXSetTevColorOp(i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(i, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevAlphaOp(i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        } else {
            GXSetTevColorIn(i, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
            GXSetTevColorOp(i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(i, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
            GXSetTevAlphaOp(i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        }

        entry = entries[i];
        {
            u32 tlutIdx = entry & 0x7fffffff;

            GXLoadTexObj(&lbl_1_bss_6EA4[entry], i);

            if (entries[i] & 0x80000000) {
                GXLoadTlut(&lbl_1_bss_6E44[tlutIdx], i);
            }
        }
    }
}

// .text:0x0001F618 size:0x2E8
void fn_1_1F618(void *arg0) {
    u8 *item = arg0;
    s32 outerCount = *(s32 *)(item + 0x1c);

    while (outerCount-- != 0) {
        u32 entries[1];

        entries[0] = outerCount % 4;

        setupTevStages(item, entries);

        GXBegin(GX_QUADS, GX_VTXFMT0, 4);

        GXPosition3f32(0.0f, 0.0f, 0.5f - 0.0001f * (f32)outerCount);
        GXColor1u32(0xFFFFFF80);
        GXTexCoord2u16(0, 0);

        GXPosition3f32(0.0f, 448.0f, 0.5f - 0.0001f * (f32)outerCount);
        GXColor1u32(0xFFFFFF80);
        GXTexCoord2u16(0, 0x100);

        GXPosition3f32(640.0f, 448.0f, 0.5f - 0.0001f * (f32)outerCount);
        GXColor1u32(0xFFFFFF80);
        GXTexCoord2u16(0x100, 0x100);

        GXPosition3f32(640.0f, 0.0f, 0.5f - 0.0001f * (f32)outerCount);
        GXColor1u32(0xFFFFFF80);
        GXTexCoord2u16(0x100, 0);
    }
}

// .text:0x0001F418 size:0x200
void fn_1_1F418(void *arg0) {
    u8 *item = arg0;
    s32 i;

    for (i = 0; i < 4; i++) {
        u8 sel = *(item + 0x21);

        switch (i) {
        case 0:
            if (i == sel) {
                u16 btn = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

                if (btn & INPUT_BUTTON_LEFT) {
                    if (*(item + 0x20) == 0) {
                        *(item + 0x20) = 2;
                    }
                    *(item + 0x20) -= 1;
                } else if (btn & INPUT_BUTTON_RIGHT) {
                    *(item + 0x20) += 1;
                    if (*(item + 0x20) == 2) {
                        *(item + 0x20) = 0;
                    }
                }
            }
            break;
        case 1: {
            s32 delta = fn_80048EA8(0);

            if (i == *(item + 0x21)) {
                u16 btn = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

                if (btn & INPUT_BUTTON_LEFT) {
                    delta -= 1;
                } else if (btn & INPUT_BUTTON_RIGHT) {
                    delta += 1;
                }
                fn_80048E00(0, delta);
            }
            break;
        }
        case 2: {
            s32 delta = fn_80048EA8(1);

            if (i == *(item + 0x21)) {
                u16 btn = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

                if (btn & INPUT_BUTTON_LEFT) {
                    delta -= 1;
                } else if (btn & INPUT_BUTTON_RIGHT) {
                    delta += 1;
                }
                fn_80048E00(1, delta);
            }
            break;
        }
        case 3:
            if (i == sel) {
                u16 btn = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

                if (btn & INPUT_BUTTON_LEFT) {
                    if (*(u32 *)(item + 0x1c) != 0) {
                        *(u32 *)(item + 0x1c) -= 1;
                    }
                } else if (btn & INPUT_BUTTON_RIGHT) {
                    *(u32 *)(item + 0x1c) += 1;
                }
            }
            break;
        }
    }

    {
        u16 btn = *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4);

        if (btn & INPUT_BUTTON_UP) {
            if (*(item + 0x21) == 0) {
                *(item + 0x21) = 4;
            }
            *(item + 0x21) -= 1;
        } else if (btn & INPUT_BUTTON_DOWN) {
            *(item + 0x21) += 1;
            if (*(item + 0x21) == 4) {
                *(item + 0x21) = 0;
            }
        }
    }
}

// .text:0x0001F2D8 size:0x140
void fn_1_1F2D8(void) {

    fn_1_273D8((lbl_1_bss_6D48));

    currentDrawingItem->func = fn_1_1F05C;
    *(u32 *)((u8 *)currentDrawingItem + 0x2c) = 0;
    *(u32 *)((u8 *)currentDrawingItem + 0x28) = 0;
    currentDrawingItem->unk_14 = 2.0f;
    *(f32 *)((u8 *)currentDrawingItem + 0x18) = 0.2f;
    *(f32 *)((u8 *)currentDrawingItem + 0x1c) = 0.2f;
    *(f32 *)((u8 *)currentDrawingItem + 0x20) = 1.0f;
    *(f32 *)((u8 *)currentDrawingItem + 0x24) = 1.0f;

    {
        DrawingSceneStruct *cur;

        fn_800385F0(lbl_1_bss_6BF4, currentDrawingItem->unk_14, *(f32 *)((u8 *)currentDrawingItem + 0x18),
            *(f32 *)((u8 *)currentDrawingItem + 0x1c), *(f32 *)((u8 *)currentDrawingItem + 0x20));
        cur = currentDrawingItem;
        *(f32 *)(lbl_1_bss_6BF4 + 0x50) = -*(f32 *)((u8 *)cur + 0x24);
        *(f32 *)(lbl_1_bss_6BF4 + 0xec) += 2.0f;
        *(u32 *)((u8 *)cur + 0x2c) &= ~0x2;
        *(u32 *)((u8 *)currentDrawingItem + 0x2c) |= 0x2;
    }
    currentDrawingItem->state = 0;

    lbl_1_bss_6BE4[0] = 0.0f;
    lbl_1_bss_6BE4[1] = 0.0f;
    lbl_1_bss_6BE4[2] = 0.0f;
    lbl_1_bss_6BE4[3] = 0.0f;
}

// .text:0x0001F23C size:0x9C
void fn_1_1F23C(u8 *arg0) {
    DrawingSceneStruct *item = currentDrawingItem;

    fn_800385F0(lbl_1_bss_6BF4, item->unk_14, *(f32 *)((u8 *)item + 0x18), *(f32 *)((u8 *)item + 0x1c),
        *(f32 *)((u8 *)item + 0x20));

    *(f32 *)(arg0 + 0x50) = -*(f32 *)((u8 *)currentDrawingItem + 0x24);
    *(f32 *)(arg0 + 0xec) += 2.0f;
    *(u32 *)((u8 *)currentDrawingItem + 0x2c) &= ~0x2;
    *(u32 *)((u8 *)currentDrawingItem + 0x2c) |= 0x2;
}

// .text:0x0001F05C size:0x1E0
void fn_1_1F05C(void) {
    DrawingSceneStruct *item = currentDrawingItem;

    if (*(u32 *)((u8 *)item + 0x2c) & 1) {
        s16 newState = fn_1_1E90C(item->state, AtBat_ButtonInput1._00, AtBat_ButtonInput1._02,
                                   *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4));

        currentDrawingItem->state = newState;
    } else {
        fn_1_26D28((lbl_1_bss_6D48), AtBat_ButtonInput1._00, AtBat_ButtonInput1._02,
                    *(u16 *)((u8 *)&AtBat_ButtonInput1 + 4), (u8 *)&AtBat_ButtonInput1 + 0x10);
    }

    if (AtBat_ButtonInput1._02 & INPUT_BUTTON_B) {
        item = currentDrawingItem;

        if (*(u32 *)((u8 *)item + 0x2c) & 1) {
            item->func = fn_1_24778;
        } else {
            *(u32 *)((u8 *)item + 0x2c) ^= 1;
        }
    } else if (AtBat_ButtonInput1._02 & INPUT_BUTTON_START) {
        item = currentDrawingItem;
        *(u32 *)((u8 *)item + 0x2c) ^= 1;
    }

    fn_1_27330((lbl_1_bss_6D48));
    item = currentDrawingItem;

    switch (*(s32 *)((u8 *)item + 0x28)) {
    case 0:
        if (*(u32 *)((u8 *)item + 0x2c) & 4) {
            *(u32 *)((u8 *)item + 0x2c) ^= 4;

            {
                f32 vec[3];

                vec[0] = lbl_1_bss_6BE4[1];
                vec[1] = lbl_1_bss_6BE4[2];
                vec[2] = lbl_1_bss_6BE4[3];
                fn_80037B18(lbl_1_bss_6BF4, vec, lbl_1_bss_6BE4[0]);
            }
        }

        fn_80037BAC(lbl_1_bss_6BF4);
        break;
    }

    item = currentDrawingItem;

    if (*(u32 *)((u8 *)item + 0x2c) & 1) {
        void (*fn)(s16) = lbl_1_data_1066C[*(u32 *)((u8 *)item + 0x28)];

        fn((s16)(item->state - 8));
    }

    fn_1_272DC((lbl_1_bss_6D48), 0);
    fn_1_AF4(0x14, 0x14, 1.0f);
    item = currentDrawingItem;

    if (*(u32 *)((u8 *)item + 0x2c) & 2) {
        fn_1_1E5D0((lbl_1_bss_6BF4));
    }
}

// .text:0x0001EFF4 size:0x68
void fn_1_1EFF4(void) {
    fn_1_272DC(lbl_1_bss_6D48, 0);
    fn_1_AF4(0x14, 0x14, 1.0f);

    if (*(u32 *)((u8 *)currentDrawingItem + 0x2c) & 0x2) {
        fn_1_1E5D0(lbl_1_bss_6BF4);
    }
}

// .text:0x0001E90C size:0x6E8
#pragma dont_inline on
s16 fn_1_1E90C(s16 arg0, u16 arg1, u16 arg2, u16 arg3) {
    DrawingSceneStruct *item = currentDrawingItem;
    f32 v14 = item->unk_14;
    f32 v18 = *(f32 *)((u8 *)item + 0x18);
    f32 v1c = *(f32 *)((u8 *)item + 0x1c);
    f32 v20 = *(f32 *)((u8 *)item + 0x20);
    f32 v24 = *(f32 *)((u8 *)item + 0x24);
    s16 ret = lbl_1_data_10668[*(s32 *)((u8 *)item + 0x28)]((s16)(arg0 - 8)) + 8;

    if (arg0 != ret) {
        s32 m = lbl_1_data_10670[*(s32 *)((u8 *)currentDrawingItem + 0x28)] + 8;
        arg0 = (ret + m) % m;
    } else if (arg2 & INPUT_BUTTON_A) {
        switch (arg0) {
        case 0:
            break;
        case 1: {
            DrawingSceneStruct *cur;

            fn_800385F0(lbl_1_bss_6BF4, currentDrawingItem->unk_14, *(f32 *)((u8 *)currentDrawingItem + 0x18),
                *(f32 *)((u8 *)currentDrawingItem + 0x1c), *(f32 *)((u8 *)currentDrawingItem + 0x20));
            cur = currentDrawingItem;
            {
                f32 z = -*(f32 *)((u8 *)cur + 0x24);

                *(f32 *)(lbl_1_bss_6BF4 + 0xec) += 2.0f;
                *(f32 *)(lbl_1_bss_6BF4 + 0x50) = z;
            }
            *(u32 *)((u8 *)cur + 0x2c) &= ~0x2;
            *(u32 *)((u8 *)currentDrawingItem + 0x2c) |= 0x2;
            break;
        }
        case 2:
            *(u32 *)((u8 *)currentDrawingItem + 0x2c) ^= 4;
            break;
        case 3:
            break;
        }
    } else if (arg3 & INPUT_BUTTON_LEFT) {
        switch (arg0) {
        case 0:
            *(s32 *)((u8 *)currentDrawingItem + 0x28) = (*(s32 *)((u8 *)currentDrawingItem + 0x28) + 7) % 8;
            break;
        case 3:
            v14 = fn_1_1DD48(arg1, TRUE, v14, 0.0001f, 0.01f, 0.1f, 1.0f, 10.0f);
            break;
        case 4:
            v18 = fn_1_1DD48(arg1, TRUE, v18, 0.0001f, 0.01f, 0.1f, 0.0f, 1.0f);
            break;
        case 5:
            v1c = fn_1_1DD48(arg1, TRUE, v1c, 0.0001f, 0.01f, 0.1f, 1.0f, 10.0f);
            break;
        case 7:
            v24 = fn_1_1DD48(arg1, TRUE, v24, 0.0001f, 0.01f, 0.1f, 0.0f, 10.0f);
            break;
        }
    } else if (arg3 & INPUT_BUTTON_RIGHT) {
        switch (arg0) {
        case 0:
            *(s32 *)((u8 *)currentDrawingItem + 0x28) = (*(s32 *)((u8 *)currentDrawingItem + 0x28) + 1) % 8;
            break;
        case 3:
            v14 = fn_1_1DD48(arg1, FALSE, v14, 0.0001f, 0.01f, 0.1f, 1.0f, 10.0f);
            break;
        case 4:
            v18 = fn_1_1DD48(arg1, FALSE, v18, 0.0001f, 0.01f, 0.1f, 0.0f, 1.0f);
            break;
        case 5:
            v1c = fn_1_1DD48(arg1, FALSE, v1c, 0.0001f, 0.01f, 0.1f, 1.0f, 10.0f);
            break;
        case 6:
            v20 = fn_1_1DD48(arg1, FALSE, v20, 0.0001f, 0.01f, 0.1f, 0.0f, 10.0f);
            break;
        case 7:
            v24 = fn_1_1DD48(arg1, FALSE, v24, 0.0001f, 0.01f, 0.1f, 0.0f, 10.0f);
            break;
        }
    } else if (arg3 & INPUT_BUTTON_UP) {
        if (arg0 < 8) {
            s32 n = lbl_1_data_10670[*(s32 *)((u8 *)currentDrawingItem + 0x28)];

            arg0 = (n + 7 + arg0) % (n + 8);
        }
    } else if (arg3 & INPUT_BUTTON_DOWN) {
        if (arg0 < 8) {
            s32 m = lbl_1_data_10670[*(s32 *)((u8 *)currentDrawingItem + 0x28)] + 8;

            arg0 = (arg0 + 1) % m;
        }
    }

    currentDrawingItem->unk_14 = v14;
    *(f32 *)((u8 *)currentDrawingItem + 0x18) = v18;
    *(f32 *)((u8 *)currentDrawingItem + 0x1c) = v1c;
    *(f32 *)((u8 *)currentDrawingItem + 0x20) = v20;
    *(f32 *)((u8 *)currentDrawingItem + 0x24) = v24;

    return arg0;
}
#pragma dont_inline reset

// .text:0x0001E8C0 size:0x4C
void fn_1_1E8C0(s32 arg0) {
    lbl_1_data_1066C[*(s32 *)((u8 *)currentDrawingItem + 0x28)]((s16)(arg0 - 8));
}

// .text:0x0001E5D0 size:0x2F0
void fn_1_1E5D0(u8 *base) {
    Vec v2;
    Vec v1;
    Vec *pv2;

    fn_1_F2C(GX_PASSCLR, 0, FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);

    PSMTXMultVec((f32(*)[4])(base + 0x58), (Vec *)(base + 0xc), &v1);
    PSMTXMultVec((f32(*)[4])(base + 0x58), (Vec *)base, pv2 = &v2);

    GXBegin(GX_LINES, GX_VTXFMT0, 2);
    GX_WRITE_F32(v1.x);
    GX_WRITE_F32(v1.y);
    GX_WRITE_F32(v1.z);
    GX_WRITE_U8(0xff);
    GX_WRITE_U8(0x40);
    GX_WRITE_U8(0x40);
    GX_WRITE_U8(0xff);
    GX_WRITE_F32(v2.x);
    GX_WRITE_F32(v2.y);
    GX_WRITE_F32(v2.z);
    GX_WRITE_U8(0x40);
    GX_WRITE_U8(0xff);
    GX_WRITE_U8(0x40);
    GX_WRITE_U8(0xff);

    GXBegin(GX_LINES, GX_VTXFMT0, 4);
    PSVECScale((Vec *)(base + 0xe8), 1.0f, &v1);
    PSVECAdd(&v1, (Vec *)(base + 0xf4), pv2);
    GX_WRITE_F32(v1.x);
    GX_WRITE_F32(v1.y);
    GX_WRITE_F32(v1.z);
    GX_WRITE_U8(0xff);
    GX_WRITE_U8(0);
    GX_WRITE_U8(0);
    GX_WRITE_U8(0xff);
    GX_WRITE_F32(v2.x);
    GX_WRITE_F32(v2.y);
    GX_WRITE_F32(v2.z);
    GX_WRITE_U8(0xff);
    GX_WRITE_U8(0);
    GX_WRITE_U8(0);
    GX_WRITE_U8(0xff);

    PSVECScale((Vec *)(base + 0x140), 1.0f, pv2);
    PSVECAdd(&v1, pv2, pv2);

    GX_WRITE_F32(v1.x);
    GX_WRITE_F32(v1.y);
    GX_WRITE_F32(v1.z);
    GX_WRITE_U8(0);
    GX_WRITE_U8(0);
    GX_WRITE_U8(0xff);
    GX_WRITE_U8(0xff);
    GX_WRITE_F32(v2.x);
    GX_WRITE_F32(v2.y);
    GX_WRITE_F32(v2.z);
    GX_WRITE_U8(0);
    GX_WRITE_U8(0);
    GX_WRITE_U8(0xff);
    GX_WRITE_U8(0xff);

    if (*(s32 *)((u8 *)currentDrawingItem + 0x28) == 0) {
        PSVECSubtract((Vec *)base, (Vec *)(base + 0xc), &v1);
        PSVECScale(&v1, lbl_1_bss_6BE4[0], &v1);
        PSVECAdd((Vec *)(base + 0xc), &v1, &v1);
        PSMTXMultVec((f32(*)[4])(base + 0x58), &v1, &v1);
        v2.x = lbl_1_bss_6BE4[1];
        v2.y = lbl_1_bss_6BE4[2];
        v2.z = lbl_1_bss_6BE4[3];
        PSVECAdd(&v1, pv2, pv2);

        GXBegin(GX_LINES, GX_VTXFMT0, 2);
        GX_WRITE_F32(v1.x);
        GX_WRITE_F32(v1.y);
        GX_WRITE_F32(v1.z);
        GX_WRITE_U8(0xff);
        GX_WRITE_U8(0);
        GX_WRITE_U8(0xff);
        GX_WRITE_U8(0xff);
        GX_WRITE_F32(v2.x);
        GX_WRITE_F32(v2.y);
        GX_WRITE_F32(v2.z);
        GX_WRITE_U8(0xff);
        GX_WRITE_U8(0);
        GX_WRITE_U8(0xff);
        GX_WRITE_U8(0xff);
    }
}

static inline void stepValue(f32 *p, u16 flags, BOOL neg, f32 lo, f32 hi) {
    f32 offset = 0.01f;
    f32 value = *p;

    if (flags & INPUT_TRIGGER_L) {
        offset = 0.0001f;
    } else if (flags & INPUT_TRIGGER_R) {
        offset = 0.1f;
    }

    if (neg) {
        offset = -offset;
    }

    value += offset;
    if (value < lo) {
        value = lo;
    }

    if (value > hi) {
        value = hi;
    }

    *p = value;
}

// .text:0x0001E290 size:0x340
s32 fn_1_1E290(s32 arg0, u16 arg1, u32 arg2, u16 flags) {
    if ((s16)arg0 < 0 || (s16)arg0 >= 3) {
        return arg0;
    }

    if (flags & INPUT_BUTTON_LEFT) {
        switch ((s16)arg0) {
        case 0:
            stepValue((f32 *)(lbl_1_bss_6BF4 + 0x140), arg1, TRUE, -10.0f, 10.0f);
            break;
        case 1:
            stepValue((f32 *)(lbl_1_bss_6BF4 + 0x144), arg1, TRUE, -10.0f, 10.0f);
            break;
        case 2:
            stepValue((f32 *)(lbl_1_bss_6BF4 + 0x148), arg1, TRUE, -10.0f, 10.0f);
            break;
        }
    } else if (flags & INPUT_BUTTON_RIGHT) {
        switch ((s16)arg0) {
        case 0:
            stepValue((f32 *)(lbl_1_bss_6BF4 + 0x140), arg1, FALSE, -10.0f, 10.0f);
            break;
        case 1:
            stepValue((f32 *)(lbl_1_bss_6BF4 + 0x144), arg1, FALSE, -10.0f, 10.0f);
            break;
        case 2:
            stepValue((f32 *)(lbl_1_bss_6BF4 + 0x148), arg1, FALSE, -10.0f, 10.0f);
            break;
        }
    } else {
        if (flags & INPUT_BUTTON_UP) {
            arg0 -= 1;
        } else if (flags & INPUT_BUTTON_DOWN) {
            arg0 += 1;
        }
    }

    return arg0;
}

// .text:0x0001E28C size:0x4
void fn_1_1E28C(void) {
    return;
}

// .text:0x0001DE60 size:0x42C
s32 fn_1_1DE60(s32 arg0, u16 arg1, u32 arg2, u16 flags) {
    if ((s16)arg0 < 0 || (s16)arg0 >= 4) {
        return arg0;
    }

    if (flags & INPUT_BUTTON_LEFT) {
        switch ((s16)arg0) {
        case 0:
            stepValue(&lbl_1_bss_6BE4[0], arg1, TRUE, 0.0f, 1.0f);
            break;
        case 1:
            stepValue(&lbl_1_bss_6BE4[1], arg1, TRUE, -10.0f, 10.0f);
            break;
        case 2:
            stepValue(&lbl_1_bss_6BE4[2], arg1, TRUE, -10.0f, 10.0f);
            break;
        case 3:
            stepValue(&lbl_1_bss_6BE4[3], arg1, TRUE, -10.0f, 10.0f);
            break;
        }
    } else if (flags & INPUT_BUTTON_RIGHT) {
        switch ((s16)arg0) {
        case 0:
            stepValue(&lbl_1_bss_6BE4[0], arg1, FALSE, 0.0f, 1.0f);
            break;
        case 1:
            stepValue(&lbl_1_bss_6BE4[1], arg1, FALSE, -10.0f, 10.0f);
            break;
        case 2:
            stepValue(&lbl_1_bss_6BE4[2], arg1, FALSE, -10.0f, 10.0f);
            break;
        case 3:
            stepValue(&lbl_1_bss_6BE4[3], arg1, FALSE, -10.0f, 10.0f);
            break;
        }
    } else {
        if (flags & INPUT_BUTTON_UP) {
            arg0 -= 1;
        } else if (flags & INPUT_BUTTON_DOWN) {
            arg0 += 1;
        }
    }

    return arg0;
}

// .text:0x0001DE5C size:0x4
void fn_1_1DE5C(void) {
    return;
}

// .text:0x0001DE50 size:0xC
f32 fn_1_1DE50(void) {
    return lbl_1_bss_6BE4[0];
}

// .text:0x0001DE40 size:0x10
f32 fn_1_1DE40(void) {
    return lbl_1_bss_6BE4[1];
}

// .text:0x0001DE30 size:0x10
f32 fn_1_1DE30(void) {
    return lbl_1_bss_6BE4[2];
}

// .text:0x0001DE20 size:0x10
f32 fn_1_1DE20(void) {
    return lbl_1_bss_6BE4[3];
}

// .text:0x0001DE14 size:0xC
void fn_1_1DE14(f32 arg0) {
    lbl_1_bss_6BE4[0] = arg0;
}

// .text:0x0001DE04 size:0x10
void fn_1_1DE04(f32 arg0) {
    lbl_1_bss_6BE4[1] = arg0;
}

// .text:0x0001DDF4 size:0x10
void fn_1_1DDF4(f32 arg0) {
    lbl_1_bss_6BE4[2] = arg0;
}

// .text:0x0001DDE4 size:0x10
void fn_1_1DDE4(f32 arg0) {
    lbl_1_bss_6BE4[3] = arg0;
}

// .text:0x0001DD94 size:0x50
void fn_1_1DD94(void) {
    f32 v[3];

    v[0] = lbl_1_bss_6BE4[1];
    v[1] = lbl_1_bss_6BE4[2];
    v[2] = lbl_1_bss_6BE4[3];
    fn_80037B18(lbl_1_bss_6BF4, v, lbl_1_bss_6BE4[0]);
}

// .text:0x0001DD48 size:0x4C
f32 fn_1_1DD48(u16 flags, BOOL neg, f32 value, f32 opt1, f32 def, f32 opt2, f32 lo, f32 hi) {
    f32 offset = def;

    if (flags & INPUT_TRIGGER_L) {
        offset = opt1;
    } else if (flags & INPUT_TRIGGER_R) {
        offset = opt2;
    }

    if (neg) {
        offset = -offset;
    }

    value += offset;
    if (value < lo) {
        value = lo;
    }

    if (value > hi) {
        value = hi;
    }

    return value;
}

// .text:0x0001DCE4 size:0x64
void fn_1_1DCE4(void) {
    DrawingSceneStruct *item = currentDrawingItem;

    *(void **)((u8 *)item + 0x14) = ARAMTransfer(StadiumFiles_debug_10674, 0, 0, 0);
    currentDrawingItem->func = fn_1_1DA54;
}

// .text:0x0001DA54 size:0x290
void fn_1_1DA54(void) {
    DrawingSceneStruct *item = currentDrawingItem;

    if (lbl_803C6CF8.cancel.bytes[1] != 1) {
        return;
    }

    {
        u8 *hdr = *(u8 **)((u8 *)item + 0x14);
        u32 size;

        *(void **)((u8 *)item + 0x18) = hdr + *(u32 *)(hdr + 0x14);
        convertTextureHeader(*(void **)((u8 *)item + 0x18));

        *(u16 *)((u8 *)item + 0x28) = 2;
        *(u16 *)((u8 *)item + 0x1c) = 3;
        *(u16 *)((u8 *)item + 0x1e) = 0;
        *(u16 *)((u8 *)item + 0x22) = 3;
        *(u16 *)((u8 *)item + 0x20) = 3;
        *(u16 *)((u8 *)item + 0x24) = 0;
        *(u16 *)((u8 *)item + 0x26) = 0;

        *(void **)((u8 *)item + 0x2c) = _OSAllocFromHeap(0x20, 0x20);
        memcpy(*(void **)((u8 *)item + 0x2c), *(u8 **)((u8 *)item + 0x18) + 0x44, 0x20);

#define INFO (*(u8 **)((u8 *)item + 0x2c))
        if (*(u32 *)(INFO + 0x4) != 0) {
            switch (INFO[0x1a]) {
            case 0:
            case 1:
            case 2:
                size = *(u16 *)(INFO + 0x18) * 2;
                *(void **)(INFO + 0x4) = _OSAllocFromHeap(0x20, size);
                memcpy(*(void **)(INFO + 0x4), *(void **)(*(u8 **)((u8 *)item + 0x18) + 0x48), size);
                break;
            }

            DCStoreRangeNoSync(*(void **)(INFO + 0x4), size);

            switch (INFO[0x17]) {
            case 8:
                size = (((*(u16 *)(INFO + 0xa) + 7) / 8) * 8) * (((*(u16 *)(INFO + 0x8) + 7) / 8) * 8);
                break;
            case 9:
                size = (((*(u16 *)(INFO + 0xa) + 7) / 8) * 8) * (((*(u16 *)(INFO + 0x8) + 3) / 4) * 4);
                break;
            default:
                fn_800AD038(*(void **)(lbl_80366158 + 0x8));
                currentDrawingItem->currentDrawingItem->state = 1;
                removeCurrentDrawingItem();
                return;
            }
        } else {
            switch (INFO[0x17]) {
            case 0xe:
                size = (((*(u16 *)(INFO + 0xa) + 7) / 8) * 8) * (((*(u16 *)(INFO + 0x8) + 7) / 8) * 8);
                break;
            default:
                fn_800AD038(*(void **)(lbl_80366158 + 0x8));
                currentDrawingItem->currentDrawingItem->state = 1;
                removeCurrentDrawingItem();
                return;
            }
        }

        *(void **)(INFO + 0x0) = _OSAllocFromHeap(0x20, size);
        memcpy(*(void **)(INFO + 0x0), *(void **)(*(u8 **)((u8 *)item + 0x18) + 0x44), size);
        DCStoreRangeNoSync(*(void **)(INFO + 0x0), size);
#undef INFO
        PPCSync();

        currentDrawingItem->func = fn_1_1D944;
    }
}

// .text:0x0001D944 size:0x110
void fn_1_1D944(void) {
    DrawingSceneStruct *item = currentDrawingItem;
    u16 mod;

    if (AtBat_ButtonInput1._02 & INPUT_BUTTON_B) {
        fn_800AD038(*(void **)(lbl_80366158 + 0x8));
        currentDrawingItem->currentDrawingItem->state = 1;
        removeCurrentDrawingItem();
        return;
    }

    if (--(*(u16 *)((u8 *)item + 0x20)) == 0) {
        *(u16 *)((u8 *)item + 0x20) = *(u16 *)((u8 *)item + 0x22);
        mod = (*(u16 *)((u8 *)item + 0x1e) + 1) % *(u16 *)((u8 *)item + 0x1c);
        *(u16 *)((u8 *)item + 0x1e) = mod;
    }

    lbl_1_data_107E4[drawStadiumRelated]._0C = (u8 *)(*(void **)((u8 *)item + 0x18)) +
        ((*(u16 *)((u8 *)item + 0x28) + *(u16 *)((u8 *)item + 0x1e)) << 5) + 4;
    lbl_1_data_107E4[drawStadiumRelated]._14 = *(u16 *)((u8 *)item + 0x24);
    lbl_1_data_107E4[drawStadiumRelated]._16 = *(u16 *)((u8 *)item + 0x26);
    lbl_1_data_107E4[drawStadiumRelated]._18 = 1;
    lbl_1_data_107E4[drawStadiumRelated]._10 = lbl_1_data_107C4;
    lbl_1_data_107E4[drawStadiumRelated]._08 = *(u32 *)((u8 *)item + 0x2c);
    fn_800A7D4C(0, &lbl_1_data_107E4[drawStadiumRelated]);
}

// .text:0x0001D694 size:0x2B0
void fn_1_1D694(void *arg0) {
    u8 *base = arg0;

    if (*(base + 0x18) != 0) {
        fn_1_1D590(*(void **)(base + 0xc), *(u8 **)(base + 0x8), *(u8 **)(base + 0x10), 32, 64);
    }

    {
        /* The original declares the projection as a 3x4 Mtx, so C_MTXOrtho's
           4x4 result overruns it by one row; the frame layout depends on it. */
        Mtx mtx;
        Mtx mtx2;

        C_MTXOrtho(mtx, 0.0f, 448.0f, 0.0f, 640.0f, 0.0f, 1.0f);
        PSMTXIdentity(mtx2);
        GXSetProjection(mtx, GX_ORTHOGRAPHIC);
        GXLoadPosMtxImm(mtx2, GX_PNMTX0);
        GXSetCurrentMtx(GX_PNMTX0);
        gOz_GXSetTexture(GX_MODULATE, 0, FALSE);
        SetDisplayStateTexture(*(void **)(base + 0x8), 0, 0);

        GXBegin(GX_QUADS, GX_VTXFMT0, 4);

        GXPosition3f32(0.0f, 0.0f, -0.5f);
        GXColor1u32(0xFFFFFFFF);
        GXTexCoord2u16(0, 0);

        GXPosition3f32(0.0f, (f32)(*(u16 *)(*(u8 **)(base + 0x8) + 0x8)), -0.5f);
        GXColor1u32(0xFFFFFFFF);
        GXTexCoord2u16(0, 1);

        GXPosition3f32((f32)(*(u16 *)(*(u8 **)(base + 0x8) + 0xa)), (f32)(*(u16 *)(*(u8 **)(base + 0x8) + 0x8)), -0.5f);
        GXColor1u32(0xFFFFFFFF);
        GXTexCoord2u16(1, 1);

        GXPosition3f32((f32)(*(u16 *)(*(u8 **)(base + 0x8) + 0xa)), 0.0f, -0.5f);
        GXColor1u32(0xFFFFFFFF);
        GXTexCoord2u16(1, 0);
    }
}


// .text:0x0001D590 size:0x104
void fn_1_1D590(void *src, u8 *tex, u8 *map, s32 w, s32 h) {
    s32 i;
    s32 j;
    s32 cols;
    s32 rows;

    memset(*(void **)tex, 0, *(u16 *)(tex + 0xa) * *(u16 *)(tex + 0x8));

    cols = *(u16 *)(tex + 0x8) / h;
    rows = *(u16 *)(tex + 0xa) / w;

    for (i = 0; i < cols; i++) {
        for (j = 0; j < rows; j++) {
            if (j & drawStadiumRelated) {
                fn_80023F0C(src, tex, w * (map[i * rows + j] % rows), h * (map[i * rows + j] / rows), w, h, j * w, i * h);
            }
        }
    }

    DCStoreRange(*(void **)tex, *(u16 *)(tex + 0xa) * *(u16 *)(tex + 0x8));
}
