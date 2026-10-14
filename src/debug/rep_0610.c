#define REP_HEADER_DATA_FN getRepHeaderData_rep0610
#include "debug/rep_0610.h"
#include "debug/rep_0010.h"
#define SQRT2_LINKAGE static
#include "game/UnknownHomes_Game.h"
#include "header_rep_data.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x800a70dc.h"
#include "Unknown/File_0x800a7568.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/File_0x800bd300.h"
#include "Unknown/File_0x800b2b74.h"
#include "Unknown/DisplayObject.h"
#include "Unknown/sub.h"
#include "Unknown/File_0x800bdd74.h"
#include "Unknown/File_0x800bcd60.h"
#include "Unknown/File_0x800bd190.h"
#include "Unknown/File_0x800bdc88.h"
#include "Unknown/File_0x800bd2b0.h"
#include "Unknown/File_0x800bda94.h"
#include "Unknown/File_0x800b4908.h"
#include "Unknown/File_0x800b4bc8.h"
#include "Unknown/File_0x800b2b4c.h"
#include "Unknown/File_0x80052968.h"
#include "Unknown/File_0x800b0724.h"
#include "Unknown/File_0x80039aa8.h"
#include "Unknown/File_0x800bfe90.h"
#include "Dolphin/GX/GXFifo.h"
#include "Dolphin/GX/GXGeometry.h"
#include "Dolphin/GX/GXLight.h"
#include "Dolphin/GX/GXPixel.h"
#include "Dolphin/GX/GXTev.h"
#include "Dolphin/GX/GXTransform.h"
#include "Dolphin/mtx.h"
#include "Dolphin/OS/OSUtil.h"
#include "C3/control.h"
#include "C3/anim.h"
#include "C3/actor.h"
#include "stl/mem.h"

#define BTN_HELD (*(u16 *)((u8 *)&AtBat_ButtonInput1 + 0))
#define BTN_PRESSED (*(u16 *)((u8 *)&AtBat_ButtonInput1 + 2))
#define BTN_REPEAT (*(u16 *)((u8 *)&AtBat_ButtonInput1 + 4))

extern u8 lbl_80366158[0x30];

extern u32 lbl_80108B90[];
extern u8 drawStadiumRelated;
extern void fn_800324EC(u16 id, s32 a, s32 b);
extern void fn_8002955C(Vec *pos, s32 arg);
extern void fn_80031CA4(Vec *pos, void *params);
extern void fn_80030D88(Vec *start, Vec *dir, void *slot, s32 arg);
extern void fn_80037AA0(void *buf, s32 a, void (*cb)(BOOL), u16 count, void *data);
extern void fn_800385F0(void *buf, f32 a, f32 b, f32 c, f32 d);
extern void fn_8004B208(s32 a, s32 b, s32 c);
extern void fn_800BD670(void *a, void *b);
extern void fn_80026134(s32 a, Vec *v);
extern void fn_80026130(s32 a, void *p, f32 f);
extern void fn_800A7D4C(s32 arg0, void *arg1);
extern void fn_800B2C88(void *model, u16 idx, void *out);
extern void fn_800B806C(s32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g, f32 h);
extern void fn_80052D70(void);
extern void minigamesSetSomePointers(void);
extern void fn_8002F258(Vec *pos, s32 id, void *params);
extern void fn_8002F1AC(Vec *pos, s32 id);
extern void fn_80039A4C(void);
extern void fn_800B2BA8(void *model, u16 a, void *model2, u16 i);
extern u32 getHandTrackFlags(void *p);
extern DbgFog lbl_803C5090;
extern void fn_8003A2C0(void);
extern void fn_800330CC(s32 a, u32 b, Vec *c, Vec *d, f32 e, u32 f, f32 g, s32 h);
extern void fn_80011640(void *a, void *b);
extern int fn_800B3C04(int a, void *model, Mtx m);
extern void fn_800BDA24(void *arg);
extern s32 fn_80024DB0(void *state);
extern void fn_80024FA4(void *model, void *handle, void *state, s32 arg);
extern void fn_800BD8C4(void *table, Mtx m);
extern void fn_80038EC4(void *a, void *b, s32 c);
extern void fn_8003414C(Mtx m);
extern void LITAlloc(void **light);
extern void LITInitAttn(void *light, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2);
extern void LITInitPos(void *light, f32 x, f32 y, f32 z);
extern void LITInitDir(void *light, f32 x, f32 y, f32 z);
extern void LITInitColor(void *light, GXColor color);
extern void fn_1_26B7C(void *slot);
extern void fn_8004B1B8(void *p);
extern void adjustInternalPointers(void *file);
extern void ACTActorRelated(void *file, void *actor);
extern void actRelated(void *file, void *effect);
extern void actorRelated(void *effect, int a, int b);
extern void initActorArray(int count);
extern void initShortsHandleCompressedDiskReads(void *owner);
extern void characterAndBallDisplayRelated(void *entry, u16 buffer, u16 slot, void *layout, void *anim, int arg5);
extern void fn_800BD548(void *actor, int mode, ...);
extern void fn_800B2C08(void *a, int b);
extern u32 fn_80063010(void *a, void *b);
extern u32 fn_800638B4(void *a, void *b);
extern u32 fn_8004B7B4(void *a, void *b);
extern u32 fn_800637BC(void *a, void *b);
extern u32 fn_800637D4(void *a, void *b);
extern u32 fn_80052634(void *a, void *b);
extern u32 fn_80062ED4(void *a, void *b);
extern u8 lbl_800F787C[];
#define lbl_1_data_AC9C ((DbgDrawRow *)((u8 *)lbl_1_data_AC90 + 0xC))

static u8 gap_69EC[4];
static u8 lbl_1_bss_6988[1][0x64];
static DbgSel lbl_1_bss_6940[1];
static DbgBuf68FC lbl_1_bss_68FC;
static DbgBuf67E0 lbl_1_bss_67E0;
static void *lbl_1_bss_67B8[10];
static u8 lbl_1_bss_60EC[0x6CC];
static u32 lbl_1_bss_60E8;
static u32 lbl_1_bss_60E4;
static DbgActorTbl *lbl_1_bss_60E0;
static void *lbl_1_bss_60DC;
static u8 gap_60DB;
static u8 gap_60DA;
static u8 lbl_1_bss_60A4[0x36];
static u32 lbl_1_bss_60A0[1];
static u8 lbl_1_bss_5F88[0x118];
static u8 gap_5F84[4];
static void *lbl_1_bss_5F80;
static DbgActorTbl *lbl_1_bss_5F7C;
static u8 gap_5F7B;
static u8 gap_5F7A;
static u8 gap_5F79;
static u8 lbl_1_bss_5F78;
static f32 lbl_1_bss_5F74;
static u8 lbl_1_bss_5F73;
static u8 lbl_1_bss_5F72;
static u8 lbl_1_bss_5F71;
static u8 lbl_1_bss_5F70;
static u32 lbl_1_bss_5F6C;
static u8 gap_5F6B;
static u8 gap_5F6A;
static u8 lbl_1_bss_5F69;
static u8 lbl_1_bss_5F68;
static f32 lbl_1_bss_5F64;
static u8 gap_5F63;
static u8 lbl_1_bss_5F62;
static u16 lbl_1_bss_5F60;
static u32 lbl_1_bss_5F5C;
static s32 lbl_1_bss_5F58;
static u8 lbl_1_bss_3758[8][0x500];
static DbgPtc lbl_1_bss_3258[8][5];
static DbgSlotEnt lbl_1_bss_3218[8];
static u8 gap_3217;
static u8 lbl_1_bss_3216;
static u8 lbl_1_bss_3215;
static u8 lbl_1_bss_3214;
static DbgBuf30C0 lbl_1_bss_30C0;
static u32 lbl_1_bss_30BC;
static u8 gap_30BB;
static u8 gap_30BA;
static u8 gap_30B9;
static u8 lbl_1_bss_30B8;
static u8 lbl_1_bss_30B7;
static u8 lbl_1_bss_30B6;
static s16 lbl_1_bss_30B4;
static u32 lbl_1_bss_30B0;
static u8 gap_30AC[4];
static u32 lbl_1_bss_30A8;
static u8 gap_30A7;
static u8 gap_30A6;
static u16 lbl_1_bss_30A4;
static u32 lbl_1_bss_30A0;
static u32 lbl_1_bss_309C;
static u32 lbl_1_bss_3098;
static u32 lbl_1_bss_3094;
static u8 gap_3093;
static u8 gap_3092;
static u8 gap_3091;
static u8 lbl_1_bss_3090;
static u32 lbl_1_bss_308C;
static s32 lbl_1_bss_3088;
static u32 lbl_1_bss_3084;
static u8 gap_3083;
static u8 gap_3082;
static u8 lbl_1_bss_3081;
static u8 lbl_1_bss_3080;
static s32 lbl_1_bss_307C;
static u8 gap_307B;
static u8 gap_307A;
static u8 gap_3079;
static u8 lbl_1_bss_3078;
static u32 lbl_1_bss_3074;
static u8 gap_3073;
static u8 gap_3072;
static u8 gap_3071;
static u8 lbl_1_bss_3070;
#define lbl_1_bss_67CC (lbl_1_bss_67B8[5])
#define lbl_1_bss_67D0 (&lbl_1_bss_67B8[6])

static u16 lbl_1_data_1DC0[44] = {
    0x0016, 0x0010, 0x0017, 0x0011, 0x0018, 0x0012, 0x0019, 0x0013,
    0x001A, 0x0014, 0x001B, 0x0015, 0x0020, 0x001C, 0x0021, 0x001D,
    0x0022, 0x001E, 0x0023, 0x001F, 0x0026, 0x0025, 0x0028, 0x0027,
    0x003D, 0x003C, 0xFFFF, 0x0000, 0x004A, 0x004B, 0xFFFF, 0x0000,
    0x002F, 0x0034, 0x0030, 0x0035, 0x0031, 0x0036, 0x0032, 0x0037,
    0x0033, 0x0038, 0xFFFF, 0x0000,
};

static u16 lbl_1_data_1E18[129] = {
    0x0041, 0x0047, 0x0042, 0x0048, 0x0043, 0x0049, 0x0044, 0x004A,
    0x0045, 0x004B, 0x0046, 0x004C, 0xFFFF, 0x0000, 0x002F, 0x0034,
    0xFFFF, 0x0000, 0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005,
    0x0006, 0x0007, 0x0008, 0x0009, 0x000E, 0x000F, 0x000D, 0x000C,
    0x000B, 0x000A, 0x0016, 0x0017, 0x0018, 0x0019, 0x001A, 0x001B,
    0x0010, 0x0011, 0x0012, 0x0013, 0x0014, 0x0015, 0x0020, 0x0021,
    0x0022, 0x0023, 0x001C, 0x001D, 0x001E, 0x001F, 0x0024, 0x0026,
    0x0025, 0x0028, 0x0027, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D,
    0x002E, 0x002F, 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035,
    0x0036, 0x0037, 0x0038, 0x0039, 0x003A, 0x003B, 0x003D, 0x003C,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0001, 0x0203, 0x0405, 0x0607, 0x0809, 0x0A0B, 0x0C0D, 0x000E,
    0x0F10, 0x1112, 0x1314, 0x1516, 0x1700, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0100, 0x0000, 0x0000,
    0x0100, 0x0000, 0x0101, 0x0101, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0001, 0x0000, 0x0000, 0x0101, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0101,
};

static u16 lbl_1_data_1F1A = 0x100;
static const char *lbl_1_data_1F1C[54] = {
    "MARIO     ", "LUIJI     ", "DONKI     ", "DIDI      ",
    "PEACH     ", "DAISY     ", "YOSSI     ", "B_MARIO   ",
    "B_LUIJI   ", "KUPPA     ", "WARIO     ", "WALUIJI   ",
    "NOKONOKO  ", "KINOPIO   ", "TERESA    ", "KINOPIKO  ",
    "HEIHO     ", "KYASARIN  ", "CHOROPOO  ", "KOOPA_JR  ",
    "PATAPATA  ", "MONTE_BLUE", "MONTE_RED ", "MONTE_YELL",
    "MARE_BLUE ", "MARE_RED  ", "MARE_GREEN", "H BROS.   ",
    "KINO G    ", "KINOPIO B ", "KINOPIO Y ", "KINOPIO G ",
    "KINOPIO P ", "KAMECK B  ", "KAMECK R  ", "KAMECK G  ",
    "KAMECK Y  ", "KINGTERESA", "BOSS PACKN", "DICSY     ",
    "KURIBO    ", "PATAKURIBO", "NOKONOKO R", "PATAPATA G",
    "HEIHO B   ", "HEIHO Y   ", "HEIHO G   ", "HEIHO K   ",
    "KARON W   ", "KARON G   ", "KARON R   ", "KARON B   ",
    "F BROS.   ", "B BROS.   ",
};
static char lbl_1_data_1FF4[14][0x40] = {
    "PITCHER", "CATCHER", "1B     ", "2B     ",
    "3B     ", "SS     ", "LEFT   ", "CENTER ",
    "RIGHT  ", "BATTER ", "RUNNER1", "RUNNER2",
    "RUNNER3", "",
};
static const char *lbl_1_data_2374[7] = {
    "Batter", "Runner", "Fielder", "Pitcher",
    "Catcher", "Dir", "Other",
};

static u8 lbl_1_data_2390[8] = {
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00,
};

static DbgFileEnt lbl_1_data_2398[2052] = {
    {"char/nin00/model0.dat", 0x4001E0CC, 0x0, 0x12DE4}, {"char/nin00/model1.dat", 0x4000D740, 0x0, 0x9230},
    {"char/nin00/motb.dat", 0x400EA74C, 0x0, 0x8FEF4}, {"char/nin00/motr.dat", 0x400696D4, 0x0, 0x40DAC},
    {"char/nin00/motf.dat", 0x400ECCFC, 0x0, 0x892A8}, {"char/nin00/motp.dat", 0x4009DD04, 0x0, 0x656A0},
    {"char/nin00/motc.dat", 0x4000FC7C, 0x0, 0x87A0}, {"char/nin00/mote.dat", 0x400C2230, 0x0, 0x72BB4},
    {"char/nin00/moto.dat", 0x40060268, 0x0, 0x39908}, {"char/nin00/motbs.dat", 0x4008D6F4, 0x0, 0x53DF0},
    {"char/nin00/motbt.dat", 0x400BADCC, 0x0, 0x704B4}, {"char/nin00/motrt.dat", 0x40041A00, 0x0, 0x27948},
    {"char/nin00/motrm.dat", 0x4001BC38, 0x0, 0xE598}, {"char/nin00/motfm.dat", 0x40093038, 0x0, 0x51784},
    {"char/nin00/motrtoy.dat", 0x40008818, 0x0, 0x20E4}, {"char/nin00/motes.dat", 0x4002CAC0, 0x0, 0x18C18},
    {"char/nin00/motem.dat", 0x4008BA3C, 0x0, 0x4FE44}, {"char/nin00/motec.dat", 0x400301D4, 0x0, 0x1C0F0},
    {"char/nin00/motpm.dat", 0x400828E4, 0x0, 0x53C38}, {"char/nin01/model0.dat", 0x40025734, 0x0, 0x1803C},
    {"char/nin01/model1.dat", 0x40010340, 0x0, 0xB790}, {"char/nin01/motb.dat", 0x40100160, 0x0, 0x9D384},
    {"char/nin01/motr.dat", 0x40069784, 0x0, 0x409A8}, {"char/nin01/motf.dat", 0x400E8B28, 0x0, 0x87AB4},
    {"char/nin01/motp.dat", 0x40089BBC, 0x0, 0x566C8}, {"char/nin01/motc.dat", 0x4000FC7C, 0x0, 0x8570},
    {"char/nin01/mote.dat", 0x400B302C, 0x0, 0x66244}, {"char/nin01/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin01/motbs.dat", 0x4009DA84, 0x0, 0x5D858}, {"char/nin01/motbt.dat", 0x400C460C, 0x0, 0x767C0},
    {"char/nin01/motrt.dat", 0x40042F70, 0x0, 0x28638}, {"char/nin01/motrm.dat", 0x400204E8, 0x0, 0x11D9C},
    {"char/nin01/motfm.dat", 0x4008CF48, 0x0, 0x4E724}, {"char/nin01/motrtoy.dat", 0x40008818, 0x0, 0x20E4},
    {"char/nin01/motes.dat", 0x40027438, 0x0, 0x14B1C}, {"char/nin01/motem.dat", 0x400863B4, 0x0, 0x4C15C},
    {"char/nin01/motec.dat", 0x400277A8, 0x0, 0x14E10}, {"char/nin01/motpm.dat", 0x4007AFC0, 0x0, 0x4C7B8},
    {"char/nin02/model0.dat", 0x4001D3B8, 0x0, 0x15034}, {"char/nin02/model1.dat", 0x4000EDE0, 0x0, 0xAD10},
    {"char/nin02/motb.dat", 0x400F472C, 0x0, 0x95260}, {"char/nin02/motr.dat", 0x40069908, 0x0, 0x3F9B0},
    {"char/nin02/motf.dat", 0x400E570C, 0x0, 0x879FC}, {"char/nin02/motp.dat", 0x40096B74, 0x0, 0x5E200},
    {"char/nin02/motc.dat", 0x4000FF1C, 0x0, 0x882C}, {"char/nin02/mote.dat", 0x4009C3E8, 0x0, 0x5DC00},
    {"char/nin02/moto.dat", 0x40033688, 0x0, 0x1FBB8}, {"char/nin02/motbs.dat", 0x4009347C, 0x0, 0x558C8},
    {"char/nin02/motbt.dat", 0x400C845C, 0x0, 0x7A080}, {"char/nin02/motrt.dat", 0x4004A9F0, 0x0, 0x2BACC},
    {"char/nin02/motrm.dat", 0x40021EB4, 0x0, 0x118F0}, {"char/nin02/motfm.dat", 0x40082C64, 0x0, 0x484F4},
    {"char/nin02/motrtoy.dat", 0x40008818, 0x0, 0x20E4}, {"char/nin02/motes.dat", 0x400237BC, 0x0, 0x13898},
    {"char/nin02/motem.dat", 0x40062D70, 0x0, 0x373DC}, {"char/nin02/motec.dat", 0x40032BD8, 0x0, 0x20010},
    {"char/nin02/motpm.dat", 0x40078EE0, 0x0, 0x49DD4}, {"char/nin03/model0.dat", 0x40021A44, 0x0, 0x15E08},
    {"char/nin03/model1.dat", 0x40013E80, 0x0, 0xC09C}, {"char/nin03/motb.dat", 0x40111BC8, 0x0, 0xAE460},
    {"char/nin03/motr.dat", 0x40087BCC, 0x0, 0x51D60}, {"char/nin03/motf.dat", 0x40131100, 0x0, 0xB959C},
    {"char/nin03/motp.dat", 0x400A6764, 0x0, 0x68C0C}, {"char/nin03/motc.dat", 0x40012FBC, 0x0, 0xB8B4},
    {"char/nin03/mote.dat", 0x400D8264, 0x0, 0x7FB2C}, {"char/nin03/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin03/motbs.dat", 0x40097B24, 0x0, 0x5BFD4}, {"char/nin03/motbt.dat", 0x400DB6D8, 0x0, 0x8A5A8},
    {"char/nin03/motrt.dat", 0x4005C2A8, 0x0, 0x37D20}, {"char/nin03/motrm.dat", 0x40028810, 0x0, 0x166D8},
    {"char/nin03/motfm.dat", 0x400B49C8, 0x0, 0x6945C}, {"char/nin03/motrtoy.dat", 0x40008818, 0x0, 0x20E4},
    {"char/nin03/motes.dat", 0x40033FDC, 0x0, 0x1CBB8}, {"char/nin03/motem.dat", 0x400B0014, 0x0, 0x6799C},
    {"char/nin03/motec.dat", 0x4001FD7C, 0x0, 0x10980}, {"char/nin03/motpm.dat", 0x4007D1FC, 0x0, 0x4E52C},
    {"char/nin04/model0.dat", 0x4001DA50, 0x0, 0x14788}, {"char/nin04/model1.dat", 0x40012940, 0x0, 0xC298},
    {"char/nin04/motb.dat", 0x4013237C, 0x0, 0xB23F4}, {"char/nin04/motr.dat", 0x40081A98, 0x0, 0x4CB58},
    {"char/nin04/motf.dat", 0x40111B24, 0x0, 0x960A8}, {"char/nin04/motp.dat", 0x400A2B98, 0x0, 0x5F0C8},
    {"char/nin04/motc.dat", 0x40012EA4, 0x0, 0x9728}, {"char/nin04/mote.dat", 0x400E90EC, 0x0, 0x7A0E0},
    {"char/nin04/moto.dat", 0x40041E74, 0x0, 0x28DE4}, {"char/nin04/motbs.dat", 0x400C3950, 0x0, 0x6D9C4},
    {"char/nin04/motbt.dat", 0x400E86C4, 0x0, 0x85C5C}, {"char/nin04/motrt.dat", 0x400533EC, 0x0, 0x31060},
    {"char/nin04/motrm.dat", 0x40025F4C, 0x0, 0x13D14}, {"char/nin04/motfm.dat", 0x400B0F20, 0x0, 0x5D338},
    {"char/nin04/motrtoy.dat", 0x40008818, 0x0, 0x20E4}, {"char/nin04/motes.dat", 0x40031884, 0x0, 0x16B50},
    {"char/nin04/motem.dat", 0x4008C71C, 0x0, 0x43DC0}, {"char/nin04/motec.dat", 0x400549C4, 0x0, 0x2FF4C},
    {"char/nin04/motpm.dat", 0x400809E8, 0x0, 0x4A090}, {"char/nin05/model0.dat", 0x40022118, 0x0, 0x187C0},
    {"char/nin05/model1.dat", 0x400123C0, 0x0, 0xBFF0}, {"char/nin05/motb.dat", 0x401105D8, 0x0, 0x9DEE4},
    {"char/nin05/motr.dat", 0x4007C9BC, 0x0, 0x4BF30}, {"char/nin05/motf.dat", 0x400E14AC, 0x0, 0x80610},
    {"char/nin05/motp.dat", 0x400998D8, 0x0, 0x5BACC}, {"char/nin05/motc.dat", 0x400106DC, 0x0, 0x8198},
    {"char/nin05/mote.dat", 0x4009FA28, 0x0, 0x539A0}, {"char/nin05/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin05/motbs.dat", 0x400A8E34, 0x0, 0x6014C}, {"char/nin05/motbt.dat", 0x400D54C0, 0x0, 0x7955C},
    {"char/nin05/motrt.dat", 0x400515E0, 0x0, 0x313A8}, {"char/nin05/motrm.dat", 0x400222F4, 0x0, 0x11BC4},
    {"char/nin05/motfm.dat", 0x4008C8EC, 0x0, 0x4B990}, {"char/nin05/motrtoy.dat", 0x40008818, 0x0, 0x20E4},
    {"char/nin05/motes.dat", 0x40027FD0, 0x0, 0x16A28}, {"char/nin05/motem.dat", 0x4007C894, 0x0, 0x41110},
    {"char/nin05/motec.dat", 0x400215A8, 0x0, 0xF608}, {"char/nin05/motpm.dat", 0x40078314, 0x0, 0x47044},
    {"char/nin06/model0.dat", 0x40018A20, 0x0, 0x12304}, {"char/nin06/model1.dat", 0x4000F780, 0x0, 0xAB70},
    {"char/nin06/motb.dat", 0x4013CF18, 0x0, 0xB1C0C}, {"char/nin06/motr.dat", 0x4007C0F4, 0x0, 0x43FEC},
    {"char/nin06/motf.dat", 0x40168A8E, 0x0, 0xC7B48}, {"char/nin06/motp.dat", 0x400CB844, 0x0, 0x70960},
    {"char/nin06/motc.dat", 0x400148AC, 0x0, 0xA648}, {"char/nin06/mote.dat", 0x400EE648, 0x0, 0x7AE00},
    {"char/nin06/moto.dat", 0x40047D12, 0x0, 0x2EC54}, {"char/nin06/motbs.dat", 0x400C2BF0, 0x0, 0x6A444},
    {"char/nin06/motbt.dat", 0x40101FDC, 0x0, 0x91AE8}, {"char/nin06/motrt.dat", 0x400539F4, 0x0, 0x2D7C0},
    {"char/nin06/motrm.dat", 0x40020FAC, 0x0, 0xFF98}, {"char/nin06/motfm.dat", 0x400C0E98, 0x0, 0x69510},
    {"char/nin06/motrtoy.dat", 0x40008818, 0x0, 0x20E4}, {"char/nin06/motes.dat", 0x4002E910, 0x0, 0x16C4C},
    {"char/nin06/motem.dat", 0x4008244C, 0x0, 0x42898}, {"char/nin06/motec.dat", 0x40068A10, 0x0, 0x349DC},
    {"char/nin06/motpm.dat", 0x400A0264, 0x0, 0x59150}, {"char/nin07/model0.dat", 0x4001C328, 0x0, 0x1365C},
    {"char/nin07/model1.dat", 0x4000EAE0, 0x0, 0x8F28}, {"char/nin07/motb.dat", 0x4010FA88, 0x0, 0xA27D4},
    {"char/nin07/motr.dat", 0x40066668, 0x0, 0x3D364}, {"char/nin07/motf.dat", 0x400E652C, 0x0, 0x86F50},
    {"char/nin07/motp.dat", 0x4009AC90, 0x0, 0x59FFC}, {"char/nin07/motc.dat", 0x4000E7B8, 0x0, 0x6DB8},
    {"char/nin07/mote.dat", 0x4008726C, 0x0, 0x46644}, {"char/nin07/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin07/motbs.dat", 0x400A53A0, 0x0, 0x630CC}, {"char/nin07/motbt.dat", 0x400D6FAC, 0x0, 0x7DF0C},
    {"char/nin07/motrt.dat", 0x40044700, 0x0, 0x29814}, {"char/nin07/motrm.dat", 0x4001C324, 0x0, 0xF15C},
    {"char/nin07/motfm.dat", 0x400886A4, 0x0, 0x4B898}, {"char/nin07/motrtoy.dat", 0x40008818, 0x0, 0x20E4},
    {"char/nin07/motes.dat", 0x40022B8C, 0x0, 0x12974}, {"char/nin07/motem.dat", 0x40063D64, 0x0, 0x34018},
    {"char/nin07/motec.dat", 0x4001C110, 0x0, 0xC51C}, {"char/nin07/motpm.dat", 0x40076714, 0x0, 0x4493C},
    {"char/nin08/model0.dat", 0x4001D77C, 0x0, 0x14104}, {"char/nin08/model1.dat", 0x400103C0, 0x0, 0x9A1C},
    {"char/nin08/motb.dat", 0x40117B00, 0x0, 0xA6F84}, {"char/nin08/motr.dat", 0x4006BCEC, 0x0, 0x40324},
    {"char/nin08/motf.dat", 0x400D98F8, 0x0, 0x7FB74}, {"char/nin08/motp.dat", 0x40093A58, 0x0, 0x58A8C},
    {"char/nin08/motc.dat", 0x4000E7B8, 0x0, 0x6DB8}, {"char/nin08/mote.dat", 0x4007CFC8, 0x0, 0x40EC8},
    {"char/nin08/moto.dat", 0x400336E0, 0x0, 0x1FB54}, {"char/nin08/motbs.dat", 0x400AB488, 0x0, 0x661EC},
    {"char/nin08/motbt.dat", 0x400E19AC, 0x0, 0x845D0}, {"char/nin08/motrt.dat", 0x4003FADC, 0x0, 0x26A5C},
    {"char/nin08/motrm.dat", 0x4001999C, 0x0, 0xDA24}, {"char/nin08/motfm.dat", 0x4007BA70, 0x0, 0x44304},
    {"char/nin08/motrtoy.dat", 0x40008818, 0x0, 0x20E4}, {"char/nin08/motes.dat", 0x40016644, 0x0, 0xA0DC},
    {"char/nin08/motem.dat", 0x4005C0D0, 0x0, 0x2FB84}, {"char/nin08/motec.dat", 0x4001F4FC, 0x0, 0xE1F0},
    {"char/nin08/motpm.dat", 0x400709A4, 0x0, 0x44690}, {"char/nin09/model0.dat", 0x40018B54, 0x0, 0x12A70},
    {"char/nin09/model1.dat", 0x4000D540, 0x0, 0x9CC0}, {"char/nin09/motb.dat", 0x40107C04, 0x0, 0x9D8F4},
    {"char/nin09/motr.dat", 0x400B8928, 0x0, 0x74F60}, {"char/nin09/motf.dat", 0x40151EC8, 0x0, 0xC9210},
    {"char/nin09/motp.dat", 0x400A1FFC, 0x0, 0x62E00}, {"char/nin09/motc.dat", 0x400168E4, 0x0, 0xAF00},
    {"char/nin09/mote.dat", 0x400DD0B8, 0x0, 0x78630}, {"char/nin09/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin09/motbs.dat", 0x400A4474, 0x0, 0x5F184}, {"char/nin09/motbt.dat", 0x400D4484, 0x0, 0x7D28C},
    {"char/nin09/motrt.dat", 0x4008874C, 0x0, 0x57EDC}, {"char/nin09/motrm.dat", 0x4002F2D8, 0x0, 0x1BCEC},
    {"char/nin09/motfm.dat", 0x400CCDA4, 0x0, 0x71998}, {"char/nin09/motrtoy.dat", 0x40008818, 0x0, 0x20E4},
    {"char/nin09/motes.dat", 0x4003275C, 0x0, 0x1A2A0}, {"char/nin09/motem.dat", 0x40089B0C, 0x0, 0x497A4},
    {"char/nin09/motec.dat", 0x4004B5A0, 0x0, 0x285D0}, {"char/nin09/motpm.dat", 0x400853B4, 0x0, 0x5016C},
    {"char/nin10/model0.dat", 0x40020F10, 0x0, 0x147E0}, {"char/nin10/model1.dat", 0x400124A0, 0x0, 0xC3F4},
    {"char/nin10/motb.dat", 0x400F9290, 0x0, 0x96FD0}, {"char/nin10/motr.dat", 0x4006B574, 0x0, 0x3CF38},
    {"char/nin10/motf.dat", 0x400EE1BC, 0x0, 0x87D8C}, {"char/nin10/motp.dat", 0x400AB2C4, 0x0, 0x68094},
    {"char/nin10/motc.dat", 0x40010A54, 0x0, 0x7F68}, {"char/nin10/mote.dat", 0x400E1784, 0x0, 0x7F724},
    {"char/nin10/moto.dat", 0x400336E0, 0x0, 0x1FB54}, {"char/nin10/motbs.dat", 0x40091F94, 0x0, 0x56A60},
    {"char/nin10/motbt.dat", 0x400BE518, 0x0, 0x73388}, {"char/nin10/motrt.dat", 0x40047DD8, 0x0, 0x29650},
    {"char/nin10/motrm.dat", 0x4001C698, 0x0, 0xE3C8}, {"char/nin10/motfm.dat", 0x40086AF0, 0x0, 0x47900},
    {"char/nin10/motrtoy.dat", 0x40008818, 0x0, 0x20E4}, {"char/nin10/motes.dat", 0x400308B8, 0x0, 0x1A5FC},
    {"char/nin10/motem.dat", 0x40076A98, 0x0, 0x3FAD4}, {"char/nin10/motec.dat", 0x40056B08, 0x0, 0x305E4},
    {"char/nin10/motpm.dat", 0x4007A8D4, 0x0, 0x499BC}, {"char/nin11/model0.dat", 0x4001F64C, 0x0, 0x17088},
    {"char/nin11/model1.dat", 0x40012BE0, 0x0, 0xCC14}, {"char/nin11/motb.dat", 0x400E6588, 0x0, 0x8F334},
    {"char/nin11/motr.dat", 0x40067440, 0x0, 0x3F104}, {"char/nin11/motf.dat", 0x400DE890, 0x0, 0x84AB0},
    {"char/nin11/motp.dat", 0x40092E84, 0x0, 0x5A534}, {"char/nin11/motc.dat", 0x4000FC7C, 0x0, 0x8638},
    {"char/nin11/mote.dat", 0x400BE42C, 0x0, 0x6D45C}, {"char/nin11/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin11/motbs.dat", 0x4008E150, 0x0, 0x578B0}, {"char/nin11/motbt.dat", 0x400BA6DC, 0x0, 0x7140C},
    {"char/nin11/motrt.dat", 0x400454DC, 0x0, 0x29F28}, {"char/nin11/motrm.dat", 0x40020BD4, 0x0, 0x12240},
    {"char/nin11/motfm.dat", 0x40088D90, 0x0, 0x4D564}, {"char/nin11/motrtoy.dat", 0x40008818, 0x0, 0x20E4},
    {"char/nin11/motes.dat", 0x40035530, 0x0, 0x1D674}, {"char/nin11/motem.dat", 0x40093360, 0x0, 0x538BC},
    {"char/nin11/motec.dat", 0x40024AAC, 0x0, 0x13A1C}, {"char/nin11/motpm.dat", 0x40073F90, 0x0, 0x45BD0},
    {"char/nin12/model0.dat", 0x40020FDC, 0x0, 0x17938}, {"char/nin12/model1.dat", 0x4000DFC0, 0x0, 0xA1FC},
    {"char/nin12/motb.dat", 0x40104EE0, 0x0, 0x9854C}, {"char/nin12/motr.dat", 0x4009AEF8, 0x0, 0x5A6AC},
    {"char/nin12/motf.dat", 0x40119934, 0x0, 0x9E218}, {"char/nin12/motp.dat", 0x400A1054, 0x0, 0x5F8A4},
    {"char/nin12/motc.dat", 0x400134A4, 0x0, 0x9148}, {"char/nin12/mote.dat", 0x40093E94, 0x0, 0x48400},
    {"char/nin12/moto.dat", 0x400336E0, 0x0, 0x1FB54}, {"char/nin12/motbs.dat", 0x400A18B4, 0x0, 0x5CD34},
    {"char/nin12/motbt.dat", 0x400C7D2C, 0x0, 0x70F4C}, {"char/nin12/motrt.dat", 0x4007BD40, 0x0, 0x495C0},
    {"char/nin12/motrm.dat", 0x400454C4, 0x0, 0x23B4C}, {"char/nin12/motfm.dat", 0x400B3964, 0x0, 0x6004C},
    {"char/nin12/motrtoy.dat", 0x40008818, 0x0, 0x20E4}, {"char/nin12/motes.dat", 0x40024D38, 0x0, 0x1112C},
    {"char/nin12/motem.dat", 0x40067F14, 0x0, 0x32FC0}, {"char/nin12/motec.dat", 0x40026204, 0x0, 0x113EC},
    {"char/nin12/motpm.dat", 0x4008892C, 0x0, 0x514F0}, {"char/nin13/model0.dat", 0x400195B0, 0x0, 0xF888},
    {"char/nin13/model1.dat", 0x4000E380, 0x0, 0x9378}, {"char/nin13/motb.dat", 0x400EF6F4, 0x0, 0x87E20},
    {"char/nin13/motr.dat", 0x40072704, 0x0, 0x451F4}, {"char/nin13/motf.dat", 0x400EBFF4, 0x0, 0x87764},
    {"char/nin13/motp.dat", 0x40089EA0, 0x0, 0x52F04}, {"char/nin13/motc.dat", 0x400141B4, 0x0, 0xA2C8},
    {"char/nin13/mote.dat", 0x40094FF8, 0x0, 0x4F18C}, {"char/nin13/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin13/motbs.dat", 0x4009616C, 0x0, 0x52220}, {"char/nin13/motbt.dat", 0x400C5080, 0x0, 0x6ED60},
    {"char/nin13/motrt.dat", 0x4005176C, 0x0, 0x30F20}, {"char/nin13/motrm.dat", 0x4001DED8, 0x0, 0xF9A0},
    {"char/nin13/motfm.dat", 0x40098430, 0x0, 0x52CC8}, {"char/nin13/motrtoy.dat", 0x40008818, 0x0, 0x20E4},
    {"char/nin13/motes.dat", 0x40024050, 0x0, 0x12908}, {"char/nin13/motem.dat", 0x4006A1CC, 0x0, 0x38C18},
    {"char/nin13/motec.dat", 0x40026AA8, 0x0, 0x11794}, {"char/nin13/motpm.dat", 0x40070630, 0x0, 0x434F4},
    {"char/nin14/model0.dat", 0x40015CE0, 0x0, 0xE0D0}, {"char/nin14/model1.dat", 0x40010700, 0x0, 0x9E1C},
    {"char/nin14/motb.dat", 0x40154778, 0x0, 0x8BE88}, {"char/nin14/motr.dat", 0x4007F278, 0x0, 0x35D84},
    {"char/nin14/motf.dat", 0x4012CA1C, 0x0, 0x861DC}, {"char/nin14/motp.dat", 0x400A8F9C, 0x0, 0x4CE10},
    {"char/nin14/motc.dat", 0x40019014, 0x0, 0xAF08}, {"char/nin14/mote.dat", 0x400BBE68, 0x0, 0x4AB50},
    {"char/nin14/moto.dat", 0x400338F0, 0x0, 0x1FCB0}, {"char/nin14/motbs.dat", 0x400C4404, 0x0, 0x4C890},
    {"char/nin14/motbt.dat", 0x401286C4, 0x0, 0x78574}, {"char/nin14/motrt.dat", 0x4007973C, 0x0, 0x3346C},
    {"char/nin14/motrm.dat", 0x40031838, 0x0, 0x141E8}, {"char/nin14/motfm.dat", 0x400C2CC0, 0x0, 0x536A8},
    {"char/nin14/motrtoy.dat", 0x40008818, 0x0, 0x20E4}, {"char/nin14/motes.dat", 0x40034FAC, 0x0, 0x14150},
    {"char/nin14/motem.dat", 0x400943AC, 0x0, 0x3BBA8}, {"char/nin14/motec.dat", 0x400224C0, 0x0, 0xCC9C},
    {"char/nin14/motpm.dat", 0x400A5C48, 0x0, 0x4B294}, {"char/nin15/model0.dat", 0x40019EF0, 0x0, 0x10BDC},
    {"char/nin15/model1.dat", 0x400118C0, 0x0, 0xA8D8}, {"char/nin15/motb.dat", 0x40126028, 0x0, 0xAD834},
    {"char/nin15/motr.dat", 0x4008C048, 0x0, 0x52820}, {"char/nin15/motf.dat", 0x4013496C, 0x0, 0xB4438},
    {"char/nin15/motp.dat", 0x400AB858, 0x0, 0x691C4}, {"char/nin15/motc.dat", 0x400190E8, 0x0, 0xE258},
    {"char/nin15/mote.dat", 0x400A9A90, 0x0, 0x5FFE0}, {"char/nin15/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin15/motbs.dat", 0x400B5FB8, 0x0, 0x6A600}, {"char/nin15/motbt.dat", 0x400F0C14, 0x0, 0x8C2A0},
    {"char/nin15/motrt.dat", 0x400622F8, 0x0, 0x3919C}, {"char/nin15/motrm.dat", 0x400267BC, 0x0, 0x14688},
    {"char/nin15/motfm.dat", 0x400B9E90, 0x0, 0x67DE4}, {"char/nin15/motrtoy.dat", 0x40008818, 0x0, 0x20E4},
    {"char/nin15/motes.dat", 0x40028F0C, 0x0, 0x17220}, {"char/nin15/motem.dat", 0x40078D24, 0x0, 0x44850},
    {"char/nin15/motec.dat", 0x40027374, 0x0, 0x12BB8}, {"char/nin15/motpm.dat", 0x4008B838, 0x0, 0x552E4},
    {"char/nin16/model0.dat", 0x40016320, 0x0, 0xE1B8}, {"char/nin16/model1.dat", 0x40012C40, 0x0, 0xB6EC},
    {"char/nin16/motb.dat", 0x400FF80C, 0x0, 0x8E938}, {"char/nin16/motr.dat", 0x40070840, 0x0, 0x3FCE8},
    {"char/nin16/motf.dat", 0x4010B5D0, 0x0, 0x90E6C}, {"char/nin16/motp.dat", 0x400997A4, 0x0, 0x53410},
    {"char/nin16/motc.dat", 0x400166A4, 0x0, 0xA878}, {"char/nin16/mote.dat", 0x4008C894, 0x0, 0x44A10},
    {"char/nin16/moto.dat", 0x400336E0, 0x0, 0x1FB54}, {"char/nin16/motbs.dat", 0x400A2460, 0x0, 0x56EEC},
    {"char/nin16/motbt.dat", 0x400CCDD4, 0x0, 0x71018}, {"char/nin16/motrt.dat", 0x4004E51C, 0x0, 0x2BC28},
    {"char/nin16/motrm.dat", 0x40023648, 0x0, 0x12090}, {"char/nin16/motfm.dat", 0x400A5574, 0x0, 0x547BC},
    {"char/nin16/motrtoy.dat", 0x40008818, 0x0, 0x20E4}, {"char/nin16/motes.dat", 0x40025C04, 0x0, 0x11890},
    {"char/nin16/motem.dat", 0x40060CEC, 0x0, 0x2FA5C}, {"char/nin16/motec.dat", 0x40023608, 0x0, 0xEFA0},
    {"char/nin16/motpm.dat", 0x4007F2C4, 0x0, 0x44BE0}, {"char/nin17/model0.dat", 0x4001D724, 0x0, 0x12518},
    {"char/nin17/model1.dat", 0x40012F00, 0x0, 0xAB08}, {"char/nin17/motb.dat", 0x40116F08, 0x0, 0xAD338},
    {"char/nin17/motr.dat", 0x40084C24, 0x0, 0x53D9C}, {"char/nin17/motf.dat", 0x40135798, 0x0, 0xB8394},
    {"char/nin17/motp.dat", 0x400AADDC, 0x0, 0x6CCDC}, {"char/nin17/motc.dat", 0x4001C178, 0x0, 0xF070},
    {"char/nin17/mote.dat", 0x4009FD44, 0x0, 0x59D14}, {"char/nin17/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin17/motbs.dat", 0x400A7920, 0x0, 0x65C10}, {"char/nin17/motbt.dat", 0x400E9BD8, 0x0, 0x8FE10},
    {"char/nin17/motrt.dat", 0x40060FF0, 0x0, 0x3D40C}, {"char/nin17/motrm.dat", 0x40021838, 0x0, 0x124B0},
    {"char/nin17/motfm.dat", 0x400AB3E4, 0x0, 0x61F70}, {"char/nin17/motrtoy.dat", 0x40008818, 0x0, 0x20E4},
    {"char/nin17/motes.dat", 0x4002D7C4, 0x0, 0x18638}, {"char/nin17/motem.dat", 0x40074AAC, 0x0, 0x41518},
    {"char/nin17/motec.dat", 0x40024294, 0x0, 0x11B30}, {"char/nin17/motpm.dat", 0x4008A608, 0x0, 0x585B8},
    {"char/nin18/model0.dat", 0x40017DE0, 0x0, 0x10298}, {"char/nin18/model1.dat", 0x4000F020, 0x0, 0x8B10},
    {"char/nin18/motb.dat", 0x400DAAA8, 0x0, 0x7AA20}, {"char/nin18/motr.dat", 0x40061E2C, 0x0, 0x3B288},
    {"char/nin18/motf.dat", 0x400F2DE8, 0x0, 0x9193C}, {"char/nin18/motp.dat", 0x4008BA4C, 0x0, 0x4EDD0},
    {"char/nin18/motc.dat", 0x4001759C, 0x0, 0xCE34}, {"char/nin18/mote.dat", 0x400902F4, 0x0, 0x48998},
    {"char/nin18/moto.dat", 0x4009C7A8, 0x0, 0x5C1DC}, {"char/nin18/motbs.dat", 0x40083B34, 0x0, 0x4AA34},
    {"char/nin18/motbt.dat", 0x400B496C, 0x0, 0x65A40}, {"char/nin18/motrt.dat", 0x40044404, 0x0, 0x29CC4},
    {"char/nin18/motrm.dat", 0x4001BFB0, 0x0, 0xF618}, {"char/nin18/motfm.dat", 0x40090A20, 0x0, 0x51B98},
    {"char/nin18/motrtoy.dat", 0x40008818, 0x0, 0x20E4}, {"char/nin18/motes.dat", 0x4002B970, 0x0, 0x15D70},
    {"char/nin18/motem.dat", 0x4006C460, 0x0, 0x36D80}, {"char/nin18/motec.dat", 0x4001D874, 0x0, 0xC284},
    {"char/nin18/motpm.dat", 0x40071AF0, 0x0, 0x40218}, {"char/nin19/model0.dat", 0x4001ABB8, 0x0, 0x1390C},
    {"char/nin19/model1.dat", 0x4000D5C0, 0x0, 0x8CF0}, {"char/nin19/motb.dat", 0x40101EE8, 0x0, 0x961F4},
    {"char/nin19/motr.dat", 0x40079200, 0x0, 0x48440}, {"char/nin19/motf.dat", 0x400E8CEC, 0x0, 0x8A344},
    {"char/nin19/motp.dat", 0x4009BE4C, 0x0, 0x5D480}, {"char/nin19/motc.dat", 0x4000D450, 0x0, 0x74AC},
    {"char/nin19/mote.dat", 0x40076AB0, 0x0, 0x3CB84}, {"char/nin19/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin19/motbs.dat", 0x400950D0, 0x0, 0x55BA4}, {"char/nin19/motbt.dat", 0x400D9190, 0x0, 0x7EA58},
    {"char/nin19/motrt.dat", 0x4004C4EC, 0x0, 0x2D318}, {"char/nin19/motrm.dat", 0x4001D8DC, 0x0, 0xFA14},
    {"char/nin19/motfm.dat", 0x400865F0, 0x0, 0x4B7A8}, {"char/nin19/motrtoy.dat", 0x40008818, 0x0, 0x20E4},
    {"char/nin19/motes.dat", 0x40024D68, 0x0, 0x12400}, {"char/nin19/motem.dat", 0x4004F114, 0x0, 0x27734},
    {"char/nin19/motec.dat", 0x4001E6D4, 0x0, 0xDF94}, {"char/nin19/motpm.dat", 0x4007E95C, 0x0, 0x4B314},
    {"char/nin20/model0.dat", 0x40022D3C, 0x0, 0x19184}, {"char/nin20/model1.dat", 0x4000FD40, 0x0, 0xB93C},
    {"char/nin20/motb.dat", 0x4010D3F0, 0x0, 0x96260}, {"char/nin20/motr.dat", 0x40070C74, 0x0, 0x40B74},
    {"char/nin20/motf.dat", 0x4010A880, 0x0, 0x8BDC4}, {"char/nin20/motp.dat", 0x4008BAF0, 0x0, 0x4FA1C},
    {"char/nin20/motc.dat", 0x4001396C, 0x0, 0x9320}, {"char/nin20/mote.dat", 0x4008AF98, 0x0, 0x421C4},
    {"char/nin20/moto.dat", 0x400336E0, 0x0, 0x1FB54}, {"char/nin20/motbs.dat", 0x4008CB38, 0x0, 0x4AE80},
    {"char/nin20/motbt.dat", 0x400E3B50, 0x0, 0x7ECDC}, {"char/nin20/motrt.dat", 0x4004EE38, 0x0, 0x2CF3C},
    {"char/nin20/motrm.dat", 0x40021FD0, 0x0, 0x1206C}, {"char/nin20/motfm.dat", 0x400A16DC, 0x0, 0x501F8},
    {"char/nin20/motrtoy.dat", 0x40008818, 0x0, 0x20E4}, {"char/nin20/motes.dat", 0x4002324C, 0x0, 0xFFB0},
    {"char/nin20/motem.dat", 0x400670B8, 0x0, 0x30B0C}, {"char/nin20/motec.dat", 0x40020080, 0x0, 0xDC28},
    {"char/nin20/motpm.dat", 0x40072C38, 0x0, 0x4023C}, {"char/nin21/model0.dat", 0x4001881C, 0x0, 0x10B50},
    {"char/nin21/model1.dat", 0x4000F500, 0x0, 0x9DA8}, {"char/nin21/motb.dat", 0x4012453C, 0x0, 0xA4390},
    {"char/nin21/motr.dat", 0x40082A20, 0x0, 0x450B4}, {"char/nin21/motf.dat", 0x40110178, 0x0, 0x931C8},
    {"char/nin21/motp.dat", 0x400A61F8, 0x0, 0x5ABAC}, {"char/nin21/motc.dat", 0x40014210, 0x0, 0x9180},
    {"char/nin21/mote.dat", 0x400BE25C, 0x0, 0x631D8}, {"char/nin21/moto.dat", 0x4004F674, 0x0, 0x2E878},
    {"char/nin21/motbs.dat", 0x400B3CE8, 0x0, 0x61BE4}, {"char/nin21/motbt.dat", 0x400DFDF0, 0x0, 0x7AF30},
    {"char/nin21/motrt.dat", 0x40058578, 0x0, 0x2E368}, {"char/nin21/motrm.dat", 0x40023878, 0x0, 0x11438},
    {"char/nin21/motfm.dat", 0x4009152C, 0x0, 0x48EC4}, {"char/nin21/motrtoy.dat", 0x40008818, 0x0, 0x20E4},
    {"char/nin21/motes.dat", 0x4002D680, 0x0, 0x171F0}, {"char/nin21/motem.dat", 0x400937B4, 0x0, 0x4E564},
    {"char/nin21/motec.dat", 0x40027844, 0x0, 0x11304}, {"char/nin21/motpm.dat", 0x40084428, 0x0, 0x48514},
    {"char/nin22/model0.dat", 0x400176FC, 0x0, 0xFEA4}, {"char/nin22/model1.dat", 0x4000F500, 0x0, 0x9D94},
    {"char/nin21/motb.dat", 0x4012453C, 0x0, 0xA4390}, {"char/nin21/motr.dat", 0x40082A20, 0x0, 0x450B4},
    {"char/nin21/motf.dat", 0x40110178, 0x0, 0x931C8}, {"char/nin21/motp.dat", 0x400A61F8, 0x0, 0x5ABAC},
    {"char/nin21/motc.dat", 0x40014210, 0x0, 0x9180}, {"char/nin21/mote.dat", 0x400BE25C, 0x0, 0x631D8},
    {"char/nin21/moto.dat", 0x4004F674, 0x0, 0x2E878}, {"char/nin21/motbs.dat", 0x400B3CE8, 0x0, 0x61BE4},
    {"char/nin21/motbt.dat", 0x400DFDF0, 0x0, 0x7AF30}, {"char/nin21/motrt.dat", 0x40058578, 0x0, 0x2E368},
    {"char/nin21/motrm.dat", 0x40023878, 0x0, 0x11438}, {"char/nin21/motfm.dat", 0x4009152C, 0x0, 0x48EC4},
    {"char/nin21/motrtoy.dat", 0x40008818, 0x0, 0x20E4}, {"char/nin21/motes.dat", 0x4002D680, 0x0, 0x171F0},
    {"char/nin21/motem.dat", 0x400937B4, 0x0, 0x4E564}, {"char/nin21/motec.dat", 0x40027844, 0x0, 0x11304},
    {"char/nin21/motpm.dat", 0x40084428, 0x0, 0x48514}, {"char/nin23/model0.dat", 0x400176FC, 0x0, 0xFEA4},
    {"char/nin23/model1.dat", 0x4000F500, 0x0, 0x9D90}, {"char/nin21/motb.dat", 0x4012453C, 0x0, 0xA4390},
    {"char/nin21/motr.dat", 0x40082A20, 0x0, 0x450B4}, {"char/nin21/motf.dat", 0x40110178, 0x0, 0x931C8},
    {"char/nin21/motp.dat", 0x400A61F8, 0x0, 0x5ABAC}, {"char/nin21/motc.dat", 0x40014210, 0x0, 0x9180},
    {"char/nin21/mote.dat", 0x400BE25C, 0x0, 0x631D8}, {"char/nin21/moto.dat", 0x4004F674, 0x0, 0x2E878},
    {"char/nin21/motbs.dat", 0x400B3CE8, 0x0, 0x61BE4}, {"char/nin21/motbt.dat", 0x400DFDF0, 0x0, 0x7AF30},
    {"char/nin21/motrt.dat", 0x40058578, 0x0, 0x2E368}, {"char/nin21/motrm.dat", 0x40023878, 0x0, 0x11438},
    {"char/nin21/motfm.dat", 0x4009152C, 0x0, 0x48EC4}, {"char/nin21/motrtoy.dat", 0x40008818, 0x0, 0x20E4},
    {"char/nin21/motes.dat", 0x4002D680, 0x0, 0x171F0}, {"char/nin21/motem.dat", 0x400937B4, 0x0, 0x4E564},
    {"char/nin21/motec.dat", 0x40027844, 0x0, 0x11304}, {"char/nin21/motpm.dat", 0x40084428, 0x0, 0x48514},
    {"char/nin24/model0.dat", 0x40011810, 0x0, 0xBAFC}, {"char/nin24/model1.dat", 0x4000BC80, 0x0, 0x7764},
    {"char/nin24/motb.dat", 0x4011C51C, 0x0, 0xA1BA4}, {"char/nin24/motr.dat", 0x400732B8, 0x0, 0x432D8},
    {"char/nin24/motf.dat", 0x400ECA2C, 0x0, 0x83E64}, {"char/nin24/motp.dat", 0x4009A664, 0x0, 0x57A54},
    {"char/nin24/motc.dat", 0x4000DEF8, 0x0, 0x66DC}, {"char/nin24/mote.dat", 0x400956A8, 0x0, 0x4AAD8},
    {"char/nin24/moto.dat", 0x4009C7A4, 0x0, 0x5C22C}, {"char/nin24/motbs.dat", 0x400AE2B0, 0x0, 0x609E0},
    {"char/nin24/motbt.dat", 0x400D85CC, 0x0, 0x79608}, {"char/nin24/motrt.dat", 0x4004BE48, 0x0, 0x2BA30},
    {"char/nin24/motrm.dat", 0x4001A5AC, 0x0, 0xD794}, {"char/nin24/motfm.dat", 0x40090514, 0x0, 0x4AA8C},
    {"char/nin24/motrtoy.dat", 0x40008818, 0x0, 0x20E4}, {"char/nin24/motes.dat", 0x400240C4, 0x0, 0x11A08},
    {"char/nin24/motem.dat", 0x400735D8, 0x0, 0x3972C}, {"char/nin24/motec.dat", 0x400201E4, 0x0, 0xE91C},
    {"char/nin24/motpm.dat", 0x40075470, 0x0, 0x42EC8}, {"char/nin25/model0.dat", 0x40011810, 0x0, 0xBB1C},
    {"char/nin25/model1.dat", 0x4000BC80, 0x0, 0x7784}, {"char/nin24/motb.dat", 0x4011C51C, 0x0, 0xA1BA4},
    {"char/nin24/motr.dat", 0x400732B8, 0x0, 0x432D8}, {"char/nin24/motf.dat", 0x400ECA2C, 0x0, 0x83E64},
    {"char/nin24/motp.dat", 0x4009A664, 0x0, 0x57A54}, {"char/nin24/motc.dat", 0x4000DEF8, 0x0, 0x66DC},
    {"char/nin24/mote.dat", 0x400956A8, 0x0, 0x4AAD8}, {"char/nin24/moto.dat", 0x4009C7A4, 0x0, 0x5C22C},
    {"char/nin24/motbs.dat", 0x400AE2B0, 0x0, 0x609E0}, {"char/nin24/motbt.dat", 0x400D85CC, 0x0, 0x79608},
    {"char/nin24/motrt.dat", 0x4004BE48, 0x0, 0x2BA30}, {"char/nin24/motrm.dat", 0x4001A5AC, 0x0, 0xD794},
    {"char/nin24/motfm.dat", 0x40090514, 0x0, 0x4AA8C}, {"char/nin24/motrtoy.dat", 0x40008818, 0x0, 0x20E4},
    {"char/nin24/motes.dat", 0x400240C4, 0x0, 0x11A08}, {"char/nin24/motem.dat", 0x400735D8, 0x0, 0x3972C},
    {"char/nin24/motec.dat", 0x400201E4, 0x0, 0xE91C}, {"char/nin24/motpm.dat", 0x40075470, 0x0, 0x42EC8},
    {"char/nin26/model0.dat", 0x40011810, 0x0, 0xBB48}, {"char/nin26/model1.dat", 0x4000BC80, 0x0, 0x77B0},
    {"char/nin24/motb.dat", 0x4011C51C, 0x0, 0xA1BA4}, {"char/nin24/motr.dat", 0x400732B8, 0x0, 0x432D8},
    {"char/nin24/motf.dat", 0x400ECA2C, 0x0, 0x83E64}, {"char/nin24/motp.dat", 0x4009A664, 0x0, 0x57A54},
    {"char/nin24/motc.dat", 0x4000DEF8, 0x0, 0x66DC}, {"char/nin24/mote.dat", 0x400956A8, 0x0, 0x4AAD8},
    {"char/nin24/moto.dat", 0x4009C7A4, 0x0, 0x5C22C}, {"char/nin24/motbs.dat", 0x400AE2B0, 0x0, 0x609E0},
    {"char/nin24/motbt.dat", 0x400D85CC, 0x0, 0x79608}, {"char/nin24/motrt.dat", 0x4004BE48, 0x0, 0x2BA30},
    {"char/nin24/motrm.dat", 0x4001A5AC, 0x0, 0xD794}, {"char/nin24/motfm.dat", 0x40090514, 0x0, 0x4AA8C},
    {"char/nin24/motrtoy.dat", 0x40008818, 0x0, 0x20E4}, {"char/nin24/motes.dat", 0x400240C4, 0x0, 0x11A08},
    {"char/nin24/motem.dat", 0x400735D8, 0x0, 0x3972C}, {"char/nin24/motec.dat", 0x400201E4, 0x0, 0xE91C},
    {"char/nin24/motpm.dat", 0x40075470, 0x0, 0x42EC8}, {"char/nin27/model0.dat", 0x4001A71C, 0x0, 0x1128C},
    {"char/nin27/model1.dat", 0x4000F8E0, 0x0, 0x98E4}, {"char/nin27/motb.dat", 0x400D9004, 0x0, 0x7DC34},
    {"char/nin27/motr.dat", 0x4005828C, 0x0, 0x318E8}, {"char/nin27/motf.dat", 0x400E77C8, 0x0, 0x84D44},
    {"char/nin27/motp.dat", 0x40071294, 0x0, 0x3E188}, {"char/nin27/motc.dat", 0x40011370, 0x0, 0x8FA8},
    {"char/nin27/mote.dat", 0x40077E54, 0x0, 0x3C340}, {"char/nin27/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin27/motbs.dat", 0x40089DEC, 0x0, 0x4C700}, {"char/nin27/motbt.dat", 0x400B74D8, 0x0, 0x69C9C},
    {"char/nin27/motrt.dat", 0x4003EDC8, 0x0, 0x21E78}, {"char/nin27/motrm.dat", 0x4001D924, 0x0, 0xE02C},
    {"char/nin27/motfm.dat", 0x40084518, 0x0, 0x4750C}, {"char/nin27/motrtoy.dat", 0x40008818, 0x0, 0x20E4},
    {"char/nin27/motes.dat", 0x40020AD0, 0x0, 0xF47C}, {"char/nin27/motem.dat", 0x4005013C, 0x0, 0x274E4},
    {"char/nin27/motec.dat", 0x40021F9C, 0x0, 0xFB58}, {"char/nin27/motpm.dat", 0x4005E514, 0x0, 0x33954},
    {"char/nin28/model0.dat", 0x4001CE58, 0x0, 0x132DC}, {"char/nin28/model1.dat", 0x4000FE80, 0x0, 0xA0FC},
    {"char/nin28/motb.dat", 0x400F38AC, 0x0, 0x848BC}, {"char/nin28/motr.dat", 0x4006DC14, 0x0, 0x3DA58},
    {"char/nin28/motf.dat", 0x401076B0, 0x0, 0x97430}, {"char/nin28/motp.dat", 0x40089EA0, 0x0, 0x4D280},
    {"char/nin28/motc.dat", 0x400141B4, 0x0, 0x9724}, {"char/nin28/mote.dat", 0x4009A9F4, 0x0, 0x4C6B4},
    {"char/nin28/moto.dat", 0x4009C7A8, 0x0, 0x5C1DC}, {"char/nin28/motbs.dat", 0x400A0788, 0x0, 0x56398},
    {"char/nin28/motbt.dat", 0x400C9238, 0x0, 0x6CF14}, {"char/nin28/motrt.dat", 0x40055184, 0x0, 0x303B4},
    {"char/nin28/motrm.dat", 0x40027E0C, 0x0, 0x144D4}, {"char/nin28/motfm.dat", 0x4009E0C0, 0x0, 0x55EF0},
    {"char/nin28/motrtoy.dat", 0x40008818, 0x0, 0x20E4}, {"char/nin28/motes.dat", 0x4002CAC0, 0x0, 0x15C1C},
    {"char/nin28/motem.dat", 0x4006D92C, 0x0, 0x35D1C}, {"char/nin28/motec.dat", 0x40026AA8, 0x0, 0x10FC8},
    {"char/nin28/motpm.dat", 0x40070630, 0x0, 0x3F0AC}, {"char/nin29/model0.dat", 0x400195B0, 0x0, 0xF9DC},
    {"char/nin29/model1.dat", 0x4000E380, 0x0, 0x961C}, {"char/nin13/motb.dat", 0x400EF6F4, 0x0, 0x87E20},
    {"char/nin13/motr.dat", 0x40072704, 0x0, 0x451F4}, {"char/nin13/motf.dat", 0x400EBFF4, 0x0, 0x87764},
    {"char/nin13/motp.dat", 0x40089EA0, 0x0, 0x52F04}, {"char/nin13/motc.dat", 0x400141B4, 0x0, 0xA2C8},
    {"char/nin13/mote.dat", 0x40094FF8, 0x0, 0x4F18C}, {"char/nin13/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin13/motbs.dat", 0x4009616C, 0x0, 0x52220}, {"char/nin13/motbt.dat", 0x400C5080, 0x0, 0x6ED60},
    {"char/nin13/motrt.dat", 0x4005176C, 0x0, 0x30F20}, {"char/nin13/motrm.dat", 0x4001DED8, 0x0, 0xF9A0},
    {"char/nin13/motfm.dat", 0x40098430, 0x0, 0x52CC8}, {"char/nin13/motrtoy.dat", 0x40008818, 0x0, 0x20E4},
    {"char/nin13/motes.dat", 0x40024050, 0x0, 0x12908}, {"char/nin13/motem.dat", 0x4006A1CC, 0x0, 0x38C18},
    {"char/nin13/motec.dat", 0x40026AA8, 0x0, 0x11794}, {"char/nin13/motpm.dat", 0x40070630, 0x0, 0x434F4},
    {"char/nin30/model0.dat", 0x400195B0, 0x0, 0xF9BC}, {"char/nin30/model1.dat", 0x4000E380, 0x0, 0x9368},
    {"char/nin13/motb.dat", 0x400EF6F4, 0x0, 0x87E20}, {"char/nin13/motr.dat", 0x40072704, 0x0, 0x451F4},
    {"char/nin13/motf.dat", 0x400EBFF4, 0x0, 0x87764}, {"char/nin13/motp.dat", 0x40089EA0, 0x0, 0x52F04},
    {"char/nin13/motc.dat", 0x400141B4, 0x0, 0xA2C8}, {"char/nin13/mote.dat", 0x40094FF8, 0x0, 0x4F18C},
    {"char/nin13/moto.dat", 0x400336E0, 0x0, 0x1FB54}, {"char/nin13/motbs.dat", 0x4009616C, 0x0, 0x52220},
    {"char/nin13/motbt.dat", 0x400C5080, 0x0, 0x6ED60}, {"char/nin13/motrt.dat", 0x4005176C, 0x0, 0x30F20},
    {"char/nin13/motrm.dat", 0x4001DED8, 0x0, 0xF9A0}, {"char/nin13/motfm.dat", 0x40098430, 0x0, 0x52CC8},
    {"char/nin13/motrtoy.dat", 0x40008818, 0x0, 0x20E4}, {"char/nin13/motes.dat", 0x40024050, 0x0, 0x12908},
    {"char/nin13/motem.dat", 0x4006A1CC, 0x0, 0x38C18}, {"char/nin13/motec.dat", 0x40026AA8, 0x0, 0x11794},
    {"char/nin13/motpm.dat", 0x40070630, 0x0, 0x434F4}, {"char/nin31/model0.dat", 0x400195B0, 0x0, 0xF8B0},
    {"char/nin31/model1.dat", 0x4000E380, 0x0, 0x926C}, {"char/nin13/motb.dat", 0x400EF6F4, 0x0, 0x87E20},
    {"char/nin13/motr.dat", 0x40072704, 0x0, 0x451F4}, {"char/nin13/motf.dat", 0x400EBFF4, 0x0, 0x87764},
    {"char/nin13/motp.dat", 0x40089EA0, 0x0, 0x52F04}, {"char/nin13/motc.dat", 0x400141B4, 0x0, 0xA2C8},
    {"char/nin13/mote.dat", 0x40094FF8, 0x0, 0x4F18C}, {"char/nin13/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin13/motbs.dat", 0x4009616C, 0x0, 0x52220}, {"char/nin13/motbt.dat", 0x400C5080, 0x0, 0x6ED60},
    {"char/nin13/motrt.dat", 0x4005176C, 0x0, 0x30F20}, {"char/nin13/motrm.dat", 0x4001DED8, 0x0, 0xF9A0},
    {"char/nin13/motfm.dat", 0x40098430, 0x0, 0x52CC8}, {"char/nin13/motrtoy.dat", 0x40008818, 0x0, 0x20E4},
    {"char/nin13/motes.dat", 0x40024050, 0x0, 0x12908}, {"char/nin13/motem.dat", 0x4006A1CC, 0x0, 0x38C18},
    {"char/nin13/motec.dat", 0x40026AA8, 0x0, 0x11794}, {"char/nin13/motpm.dat", 0x40070630, 0x0, 0x434F4},
    {"char/nin32/model0.dat", 0x400195B0, 0x0, 0xF8B0}, {"char/nin32/model1.dat", 0x4000E380, 0x0, 0x9278},
    {"char/nin13/motb.dat", 0x400EF6F4, 0x0, 0x87E20}, {"char/nin13/motr.dat", 0x40072704, 0x0, 0x451F4},
    {"char/nin13/motf.dat", 0x400EBFF4, 0x0, 0x87764}, {"char/nin13/motp.dat", 0x40089EA0, 0x0, 0x52F04},
    {"char/nin13/motc.dat", 0x400141B4, 0x0, 0xA2C8}, {"char/nin13/mote.dat", 0x40094FF8, 0x0, 0x4F18C},
    {"char/nin13/moto.dat", 0x400336E0, 0x0, 0x1FB54}, {"char/nin13/motbs.dat", 0x4009616C, 0x0, 0x52220},
    {"char/nin13/motbt.dat", 0x400C5080, 0x0, 0x6ED60}, {"char/nin13/motrt.dat", 0x4005176C, 0x0, 0x30F20},
    {"char/nin13/motrm.dat", 0x4001DED8, 0x0, 0xF9A0}, {"char/nin13/motfm.dat", 0x40098430, 0x0, 0x52CC8},
    {"char/nin13/motrtoy.dat", 0x40008818, 0x0, 0x20E4}, {"char/nin13/motes.dat", 0x40024050, 0x0, 0x12908},
    {"char/nin13/motem.dat", 0x4006A1CC, 0x0, 0x38C18}, {"char/nin13/motec.dat", 0x40026AA8, 0x0, 0x11794},
    {"char/nin13/motpm.dat", 0x40070630, 0x0, 0x434F4}, {"char/nin33/model0.dat", 0x400150EC, 0x0, 0xDD9C},
    {"char/nin33/model1.dat", 0x4000F000, 0x0, 0x9BF8}, {"char/nin33/motb.dat", 0x400EFFB8, 0x0, 0x8D04C},
    {"char/nin33/motr.dat", 0x4006C0A4, 0x0, 0x4229C}, {"char/nin33/motf.dat", 0x401017BC, 0x0, 0x9B64C},
    {"char/nin33/motp.dat", 0x40090558, 0x0, 0x58584}, {"char/nin33/motc.dat", 0x4000FC10, 0x0, 0x8628},
    {"char/nin33/mote.dat", 0x400A5928, 0x0, 0x5A998}, {"char/nin33/moto.dat", 0x4009C7A8, 0x0, 0x5C1DC},
    {"char/nin33/motbs.dat", 0x40091AB4, 0x0, 0x547C8}, {"char/nin33/motbt.dat", 0x400C424C, 0x0, 0x72464},
    {"char/nin33/motrt.dat", 0x4004C1F0, 0x0, 0x2ED08}, {"char/nin33/motrm.dat", 0x40021FE8, 0x0, 0x12E2C},
    {"char/nin33/motfm.dat", 0x400A2334, 0x0, 0x5C0D0}, {"char/nin33/motrtoy.dat", 0x40008818, 0x0, 0x20E4},
    {"char/nin33/motes.dat", 0x4002E9C8, 0x0, 0x19388}, {"char/nin33/motem.dat", 0x40077034, 0x0, 0x4100C},
    {"char/nin33/motec.dat", 0x400278B8, 0x0, 0x12EBC}, {"char/nin33/motpm.dat", 0x40075074, 0x0, 0x467B0},
    {"char/nin34/model0.dat", 0x400150EC, 0x0, 0xDD6C}, {"char/nin34/model1.dat", 0x4000F000, 0x0, 0x9BCC},
    {"char/nin33/motb.dat", 0x400EFFB8, 0x0, 0x8D04C}, {"char/nin33/motr.dat", 0x4006C0A4, 0x0, 0x4229C},
    {"char/nin33/motf.dat", 0x401017BC, 0x0, 0x9B64C}, {"char/nin33/motp.dat", 0x40090558, 0x0, 0x58584},
    {"char/nin33/motc.dat", 0x4000FC10, 0x0, 0x8628}, {"char/nin33/mote.dat", 0x400A5928, 0x0, 0x5A998},
    {"char/nin33/moto.dat", 0x4009C7A8, 0x0, 0x5C1DC}, {"char/nin33/motbs.dat", 0x40091AB4, 0x0, 0x547C8},
    {"char/nin33/motbt.dat", 0x400C424C, 0x0, 0x72464}, {"char/nin33/motrt.dat", 0x4004C1F0, 0x0, 0x2ED08},
    {"char/nin33/motrm.dat", 0x40021FE8, 0x0, 0x12E2C}, {"char/nin33/motfm.dat", 0x400A2334, 0x0, 0x5C0D0},
    {"char/nin33/motrtoy.dat", 0x40008818, 0x0, 0x20E4}, {"char/nin33/motes.dat", 0x4002E9C8, 0x0, 0x19388},
    {"char/nin33/motem.dat", 0x40077034, 0x0, 0x4100C}, {"char/nin33/motec.dat", 0x400278B8, 0x0, 0x12EBC},
    {"char/nin33/motpm.dat", 0x40075074, 0x0, 0x467B0}, {"char/nin35/model0.dat", 0x400150EC, 0x0, 0xDD50},
    {"char/nin35/model1.dat", 0x4000F000, 0x0, 0x9BAC}, {"char/nin33/motb.dat", 0x400EFFB8, 0x0, 0x8D04C},
    {"char/nin33/motr.dat", 0x4006C0A4, 0x0, 0x4229C}, {"char/nin33/motf.dat", 0x401017BC, 0x0, 0x9B64C},
    {"char/nin33/motp.dat", 0x40090558, 0x0, 0x58584}, {"char/nin33/motc.dat", 0x4000FC10, 0x0, 0x8628},
    {"char/nin33/mote.dat", 0x400A5928, 0x0, 0x5A998}, {"char/nin33/moto.dat", 0x4009C7A8, 0x0, 0x5C1DC},
    {"char/nin33/motbs.dat", 0x40091AB4, 0x0, 0x547C8}, {"char/nin33/motbt.dat", 0x400C424C, 0x0, 0x72464},
    {"char/nin33/motrt.dat", 0x4004C1F0, 0x0, 0x2ED08}, {"char/nin33/motrm.dat", 0x40021FE8, 0x0, 0x12E2C},
    {"char/nin33/motfm.dat", 0x400A2334, 0x0, 0x5C0D0}, {"char/nin33/motrtoy.dat", 0x40008818, 0x0, 0x20E4},
    {"char/nin33/motes.dat", 0x4002E9C8, 0x0, 0x19388}, {"char/nin33/motem.dat", 0x40077034, 0x0, 0x4100C},
    {"char/nin33/motec.dat", 0x400278B8, 0x0, 0x12EBC}, {"char/nin33/motpm.dat", 0x40075074, 0x0, 0x467B0},
    {"char/nin36/model0.dat", 0x400150EC, 0x0, 0xDE80}, {"char/nin36/model1.dat", 0x4000F000, 0x0, 0x9CDC},
    {"char/nin33/motb.dat", 0x400EFFB8, 0x0, 0x8D04C}, {"char/nin33/motr.dat", 0x4006C0A4, 0x0, 0x4229C},
    {"char/nin33/motf.dat", 0x401017BC, 0x0, 0x9B64C}, {"char/nin33/motp.dat", 0x40090558, 0x0, 0x58584},
    {"char/nin33/motc.dat", 0x4000FC10, 0x0, 0x8628}, {"char/nin33/mote.dat", 0x400A5928, 0x0, 0x5A998},
    {"char/nin33/moto.dat", 0x4009C7A8, 0x0, 0x5C1DC}, {"char/nin33/motbs.dat", 0x40091AB4, 0x0, 0x547C8},
    {"char/nin33/motbt.dat", 0x400C424C, 0x0, 0x72464}, {"char/nin33/motrt.dat", 0x4004C1F0, 0x0, 0x2ED08},
    {"char/nin33/motrm.dat", 0x40021FE8, 0x0, 0x12E2C}, {"char/nin33/motfm.dat", 0x400A2334, 0x0, 0x5C0D0},
    {"char/nin33/motrtoy.dat", 0x40008818, 0x0, 0x20E4}, {"char/nin33/motes.dat", 0x4002E9C8, 0x0, 0x19388},
    {"char/nin33/motem.dat", 0x40077034, 0x0, 0x4100C}, {"char/nin33/motec.dat", 0x400278B8, 0x0, 0x12EBC},
    {"char/nin33/motpm.dat", 0x40075074, 0x0, 0x467B0}, {"char/nin37/model0.dat", 0x40017300, 0x0, 0xF260},
    {"char/nin37/model1.dat", 0x40011D40, 0x0, 0xAED0}, {"char/nin37/motb.dat", 0x4016C2F8, 0x0, 0x9905C},
    {"char/nin37/motr.dat", 0x4009E950, 0x0, 0x44F2C}, {"char/nin37/motf.dat", 0x40132D08, 0x0, 0x896B4},
    {"char/nin37/motp.dat", 0x400B28B8, 0x0, 0x51A74}, {"char/nin37/motc.dat", 0x40019014, 0x0, 0xAF08},
    {"char/nin37/mote.dat", 0x400B1238, 0x0, 0x46194}, {"char/nin37/moto.dat", 0x4009C9B8, 0x0, 0x5C2D0},
    {"char/nin37/motbs.dat", 0x400DBF84, 0x0, 0x59B44}, {"char/nin37/motbt.dat", 0x401286C4, 0x0, 0x78570},
    {"char/nin37/motrt.dat", 0x4007973C, 0x0, 0x3346C}, {"char/nin37/motrm.dat", 0x40031838, 0x0, 0x141E8},
    {"char/nin37/motfm.dat", 0x400C2CC0, 0x0, 0x536A8}, {"char/nin37/motrtoy.dat", 0x40008818, 0x0, 0x20E4},
    {"char/nin37/motes.dat", 0x40034FAC, 0x0, 0x14150}, {"char/nin37/motem.dat", 0x400943AC, 0x0, 0x3BBA8},
    {"char/nin37/motec.dat", 0x40017890, 0x0, 0x812C}, {"char/nin37/motpm.dat", 0x400AE4E8, 0x0, 0x4F564},
    {"char/nin38/model0.dat", 0x400196C0, 0x0, 0x126C0}, {"char/nin38/model1.dat", 0x40010B60, 0x0, 0xB3F4},
    {"char/nin38/motb.dat", 0x401469B0, 0x0, 0xB5088}, {"char/nin38/motr.dat", 0x400A7004, 0x0, 0x5C5E4},
    {"char/nin38/motf.dat", 0x4012F150, 0x0, 0xA76AC}, {"char/nin38/motp.dat", 0x400CD6A4, 0x0, 0x77B20},
    {"char/nin38/motc.dat", 0x400159C8, 0x0, 0x8A78}, {"char/nin38/mote.dat", 0x400C3D8C, 0x0, 0x63808},
    {"char/nin38/moto.dat", 0x4009C7A8, 0x0, 0x5C1DC}, {"char/nin38/motbs.dat", 0x400CD4AC, 0x0, 0x6EFF0},
    {"char/nin38/motbt.dat", 0x400FC938, 0x0, 0x89CE4}, {"char/nin38/motrt.dat", 0x40076214, 0x0, 0x414C8},
    {"char/nin38/motrm.dat", 0x40023D98, 0x0, 0x12730}, {"char/nin38/motfm.dat", 0x400B5CE8, 0x0, 0x5F11C},
    {"char/nin38/motrtoy.dat", 0x40008818, 0x0, 0x20E4}, {"char/nin38/motes.dat", 0x4002B1B0, 0x0, 0x17084},
    {"char/nin38/motem.dat", 0x40096400, 0x0, 0x4CF34}, {"char/nin38/motec.dat", 0x40028124, 0x0, 0x11734},
    {"char/nin38/motpm.dat", 0x4009A71C, 0x0, 0x5935C}, {"char/nin39/model0.dat", 0x4001F27C, 0x0, 0x154D0},
    {"char/nin39/model1.dat", 0x40012B00, 0x0, 0xC0A4}, {"char/nin39/motb.dat", 0x401041C0, 0x0, 0xA9E48},
    {"char/nin39/motr.dat", 0x4006D470, 0x0, 0x44114}, {"char/nin39/motf.dat", 0x4010B85C, 0x0, 0xA4514},
    {"char/nin39/motp.dat", 0x4009F540, 0x0, 0x6531C}, {"char/nin39/motc.dat", 0x40011B3C, 0x0, 0x98E8},
    {"char/nin39/mote.dat", 0x400A65DC, 0x0, 0x66AD4}, {"char/nin39/moto.dat", 0x4009C7A8, 0x0, 0x5C1DC},
    {"char/nin39/motbs.dat", 0x400A0A34, 0x0, 0x67B98}, {"char/nin39/motbt.dat", 0x400D7318, 0x0, 0x8B49C},
    {"char/nin39/motrt.dat", 0x4004E644, 0x0, 0x2F990}, {"char/nin39/motrm.dat", 0x40023494, 0x0, 0x13660},
    {"char/nin39/motfm.dat", 0x400967E0, 0x0, 0x56794}, {"char/nin39/motrtoy.dat", 0x40008818, 0x0, 0x20E4},
    {"char/nin39/motes.dat", 0x4002CADC, 0x0, 0x18AF8}, {"char/nin39/motem.dat", 0x4007BB38, 0x0, 0x4AE10},
    {"char/nin39/motec.dat", 0x40022A98, 0x0, 0x13AA4}, {"char/nin39/motpm.dat", 0x40081590, 0x0, 0x51810},
    {"char/nin40/model0.dat", 0x400118C8, 0x0, 0xD7B8}, {"char/nin40/model1.dat", 0x40007C20, 0x0, 0x52E8},
    {"char/nin40/motb.dat", 0x4010B7D8, 0x0, 0x87980}, {"char/nin40/motr.dat", 0x40074414, 0x0, 0x3C1CC},
    {"char/nin40/motf.dat", 0x40120094, 0x0, 0x9206C}, {"char/nin40/motp.dat", 0x400A5EBC, 0x0, 0x53990},
    {"char/nin40/motc.dat", 0x40010618, 0x0, 0x7A0C}, {"char/nin40/mote.dat", 0x400A163D, 0x0, 0x4B0B8},
    {"char/nin40/moto.dat", 0x4009C7A8, 0x0, 0x5C1DC}, {"char/nin40/motbs.dat", 0x400A4308, 0x0, 0x51EFC},
    {"char/nin40/motbt.dat", 0x400D5F64, 0x0, 0x6BD0C}, {"char/nin40/motrt.dat", 0x40054A7C, 0x0, 0x2BA10},
    {"char/nin40/motrm.dat", 0x400224B8, 0x0, 0x109F4}, {"char/nin40/motfm.dat", 0x400C11B0, 0x0, 0x5E198},
    {"char/nin40/motrtoy.dat", 0x40008818, 0x0, 0x20E4}, {"char/nin40/motes.dat", 0x4002F914, 0x0, 0x15D64},
    {"char/nin40/motem.dat", 0x40074258, 0x0, 0x3581C}, {"char/nin40/motec.dat", 0x40024291, 0x0, 0xF6F4},
    {"char/nin40/motpm.dat", 0x40084644, 0x0, 0x41AB0}, {"char/nin41/model0.dat", 0x40018028, 0x0, 0x12FD0},
    {"char/nin41/model1.dat", 0x4000A1E0, 0x0, 0x6CCC}, {"char/nin41/motb.dat", 0x4011D304, 0x0, 0x9DFAC},
    {"char/nin41/motr.dat", 0x4008971C, 0x0, 0x4FFB8}, {"char/nin41/motf.dat", 0x40126484, 0x0, 0xA5438},
    {"char/nin41/motp.dat", 0x400A5EC0, 0x0, 0x5C6F4}, {"char/nin41/motc.dat", 0x40010618, 0x0, 0x832C},
    {"char/nin41/mote.dat", 0x400C4011, 0x0, 0x5EA3C}, {"char/nin41/moto.dat", 0x4009C7A8, 0x0, 0x5C1DC},
    {"char/nin41/motbs.dat", 0x400B0F10, 0x0, 0x5EE14}, {"char/nin41/motbt.dat", 0x400E50F0, 0x0, 0x7EC0C},
    {"char/nin41/motrt.dat", 0x4006141C, 0x0, 0x3792C}, {"char/nin41/motrm.dat", 0x40024608, 0x0, 0x13E28},
    {"char/nin41/motfm.dat", 0x400C5024, 0x0, 0x6A138}, {"char/nin41/motrtoy.dat", 0x40008818, 0x0, 0x20E4},
    {"char/nin41/motes.dat", 0x40037600, 0x0, 0x19A98}, {"char/nin41/motem.dat", 0x400918E4, 0x0, 0x45684},
    {"char/nin41/motec.dat", 0x400295D9, 0x0, 0x12568}, {"char/nin41/motpm.dat", 0x40086FE8, 0x0, 0x4B62C},
    {"char/nin42/model0.dat", 0x40020FDC, 0x0, 0x17934}, {"char/nin42/model1.dat", 0x4000DFC0, 0x0, 0xA1F4},
    {"char/nin12/motb.dat", 0x40104EE0, 0x0, 0x9854C}, {"char/nin12/motr.dat", 0x4009AEF8, 0x0, 0x5A6AC},
    {"char/nin12/motf.dat", 0x40119934, 0x0, 0x9E218}, {"char/nin12/motp.dat", 0x400A1054, 0x0, 0x5F8A4},
    {"char/nin12/motc.dat", 0x400134A4, 0x0, 0x9148}, {"char/nin12/mote.dat", 0x40093E94, 0x0, 0x48400},
    {"char/nin12/moto.dat", 0x400336E0, 0x0, 0x1FB54}, {"char/nin12/motbs.dat", 0x400A18B4, 0x0, 0x5CD34},
    {"char/nin12/motbt.dat", 0x400C7D2C, 0x0, 0x70F4C}, {"char/nin12/motrt.dat", 0x4007BD40, 0x0, 0x495C0},
    {"char/nin12/motrm.dat", 0x400454C4, 0x0, 0x23B4C}, {"char/nin12/motfm.dat", 0x400B3964, 0x0, 0x6004C},
    {"char/nin12/motrtoy.dat", 0x40008818, 0x0, 0x20E4}, {"char/nin12/motes.dat", 0x40024D38, 0x0, 0x1112C},
    {"char/nin12/motem.dat", 0x40067F14, 0x0, 0x32FC0}, {"char/nin12/motec.dat", 0x40026204, 0x0, 0x113EC},
    {"char/nin12/motpm.dat", 0x4008892C, 0x0, 0x514F0}, {"char/nin43/model0.dat", 0x40022D3C, 0x0, 0x191A4},
    {"char/nin43/model1.dat", 0x4000FD40, 0x0, 0xB958}, {"char/nin20/motb.dat", 0x4010D3F0, 0x0, 0x96260},
    {"char/nin20/motr.dat", 0x40070C74, 0x0, 0x40B74}, {"char/nin20/motf.dat", 0x4010A880, 0x0, 0x8BDC4},
    {"char/nin20/motp.dat", 0x4008BAF0, 0x0, 0x4FA1C}, {"char/nin20/motc.dat", 0x4001396C, 0x0, 0x9320},
    {"char/nin20/mote.dat", 0x4008AF98, 0x0, 0x421C4}, {"char/nin20/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin20/motbs.dat", 0x4008CB38, 0x0, 0x4AE80}, {"char/nin20/motbt.dat", 0x400E3B50, 0x0, 0x7ECDC},
    {"char/nin20/motrt.dat", 0x4004EE38, 0x0, 0x2CF3C}, {"char/nin20/motrm.dat", 0x40021FD0, 0x0, 0x1206C},
    {"char/nin20/motfm.dat", 0x400A16DC, 0x0, 0x501F8}, {"char/nin20/motrtoy.dat", 0x40008818, 0x0, 0x20E4},
    {"char/nin20/motes.dat", 0x4002324C, 0x0, 0xFFB0}, {"char/nin20/motem.dat", 0x400670B8, 0x0, 0x30B0C},
    {"char/nin20/motec.dat", 0x40020080, 0x0, 0xDC28}, {"char/nin20/motpm.dat", 0x40072C38, 0x0, 0x4023C},
    {"char/nin44/model0.dat", 0x40016320, 0x0, 0xE1BC}, {"char/nin44/model1.dat", 0x40012C40, 0x0, 0xB6F0},
    {"char/nin16/motb.dat", 0x400FF80C, 0x0, 0x8E938}, {"char/nin16/motr.dat", 0x40070840, 0x0, 0x3FCE8},
    {"char/nin16/motf.dat", 0x4010B5D0, 0x0, 0x90E6C}, {"char/nin16/motp.dat", 0x400997A4, 0x0, 0x53410},
    {"char/nin16/motc.dat", 0x400166A4, 0x0, 0xA878}, {"char/nin16/mote.dat", 0x4008C894, 0x0, 0x44A10},
    {"char/nin16/moto.dat", 0x400336E0, 0x0, 0x1FB54}, {"char/nin16/motbs.dat", 0x400A2460, 0x0, 0x56EEC},
    {"char/nin16/motbt.dat", 0x400CCDD4, 0x0, 0x71018}, {"char/nin16/motrt.dat", 0x4004E51C, 0x0, 0x2BC28},
    {"char/nin16/motrm.dat", 0x40023648, 0x0, 0x12090}, {"char/nin16/motfm.dat", 0x400A5574, 0x0, 0x547BC},
    {"char/nin16/motrtoy.dat", 0x40008818, 0x0, 0x20E4}, {"char/nin16/motes.dat", 0x40025C04, 0x0, 0x11890},
    {"char/nin16/motem.dat", 0x40060CEC, 0x0, 0x2FA5C}, {"char/nin16/motec.dat", 0x40023608, 0x0, 0xEFA0},
    {"char/nin16/motpm.dat", 0x4007F2C4, 0x0, 0x44BE0}, {"char/nin45/model0.dat", 0x40016320, 0x0, 0xE198},
    {"char/nin45/model1.dat", 0x40012C40, 0x0, 0xB6CC}, {"char/nin16/motb.dat", 0x400FF80C, 0x0, 0x8E938},
    {"char/nin16/motr.dat", 0x40070840, 0x0, 0x3FCE8}, {"char/nin16/motf.dat", 0x4010B5D0, 0x0, 0x90E6C},
    {"char/nin16/motp.dat", 0x400997A4, 0x0, 0x53410}, {"char/nin16/motc.dat", 0x400166A4, 0x0, 0xA878},
    {"char/nin16/mote.dat", 0x4008C894, 0x0, 0x44A10}, {"char/nin16/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin16/motbs.dat", 0x400A2460, 0x0, 0x56EEC}, {"char/nin16/motbt.dat", 0x400CCDD4, 0x0, 0x71018},
    {"char/nin16/motrt.dat", 0x4004E51C, 0x0, 0x2BC28}, {"char/nin16/motrm.dat", 0x40023648, 0x0, 0x12090},
    {"char/nin16/motfm.dat", 0x400A5574, 0x0, 0x547BC}, {"char/nin16/motrtoy.dat", 0x40008818, 0x0, 0x20E4},
    {"char/nin16/motes.dat", 0x40025C04, 0x0, 0x11890}, {"char/nin16/motem.dat", 0x40060CEC, 0x0, 0x2FA5C},
    {"char/nin16/motec.dat", 0x40023608, 0x0, 0xEFA0}, {"char/nin16/motpm.dat", 0x4007F2C4, 0x0, 0x44BE0},
    {"char/nin46/model0.dat", 0x40016320, 0x0, 0xE1C4}, {"char/nin46/model1.dat", 0x40012C40, 0x0, 0xB6F8},
    {"char/nin16/motb.dat", 0x400FF80C, 0x0, 0x8E938}, {"char/nin16/motr.dat", 0x40070840, 0x0, 0x3FCE8},
    {"char/nin16/motf.dat", 0x4010B5D0, 0x0, 0x90E6C}, {"char/nin16/motp.dat", 0x400997A4, 0x0, 0x53410},
    {"char/nin16/motc.dat", 0x400166A4, 0x0, 0xA878}, {"char/nin16/mote.dat", 0x4008C894, 0x0, 0x44A10},
    {"char/nin16/moto.dat", 0x400336E0, 0x0, 0x1FB54}, {"char/nin16/motbs.dat", 0x400A2460, 0x0, 0x56EEC},
    {"char/nin16/motbt.dat", 0x400CCDD4, 0x0, 0x71018}, {"char/nin16/motrt.dat", 0x4004E51C, 0x0, 0x2BC28},
    {"char/nin16/motrm.dat", 0x40023648, 0x0, 0x12090}, {"char/nin16/motfm.dat", 0x400A5574, 0x0, 0x547BC},
    {"char/nin16/motrtoy.dat", 0x40008818, 0x0, 0x20E4}, {"char/nin16/motes.dat", 0x40025C04, 0x0, 0x11890},
    {"char/nin16/motem.dat", 0x40060CEC, 0x0, 0x2FA5C}, {"char/nin16/motec.dat", 0x40023608, 0x0, 0xEFA0},
    {"char/nin16/motpm.dat", 0x4007F2C4, 0x0, 0x44BE0}, {"char/nin47/model0.dat", 0x40016320, 0x0, 0xE0FC},
    {"char/nin47/model1.dat", 0x40012C40, 0x0, 0xB630}, {"char/nin16/motb.dat", 0x400FF80C, 0x0, 0x8E938},
    {"char/nin16/motr.dat", 0x40070840, 0x0, 0x3FCE8}, {"char/nin16/motf.dat", 0x4010B5D0, 0x0, 0x90E6C},
    {"char/nin16/motp.dat", 0x400997A4, 0x0, 0x53410}, {"char/nin16/motc.dat", 0x400166A4, 0x0, 0xA878},
    {"char/nin16/mote.dat", 0x4008C894, 0x0, 0x44A10}, {"char/nin16/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin16/motbs.dat", 0x400A2460, 0x0, 0x56EEC}, {"char/nin16/motbt.dat", 0x400CCDD4, 0x0, 0x71018},
    {"char/nin16/motrt.dat", 0x4004E51C, 0x0, 0x2BC28}, {"char/nin16/motrm.dat", 0x40023648, 0x0, 0x12090},
    {"char/nin16/motfm.dat", 0x400A5574, 0x0, 0x547BC}, {"char/nin16/motrtoy.dat", 0x40008818, 0x0, 0x20E4},
    {"char/nin16/motes.dat", 0x40025C04, 0x0, 0x11890}, {"char/nin16/motem.dat", 0x40060CEC, 0x0, 0x2FA5C},
    {"char/nin16/motec.dat", 0x40023608, 0x0, 0xEFA0}, {"char/nin16/motpm.dat", 0x4007F2C4, 0x0, 0x44BE0},
    {"char/nin48/model0.dat", 0x40012910, 0x0, 0xCF04}, {"char/nin48/model1.dat", 0x4000D4C0, 0x0, 0x89BC},
    {"char/nin48/motb.dat", 0x40106D94, 0x0, 0x924E8}, {"char/nin48/motr.dat", 0x40074128, 0x0, 0x42BDC},
    {"char/nin48/motf.dat", 0x40114C60, 0x0, 0xA0C5C}, {"char/nin48/motp.dat", 0x4009AB80, 0x0, 0x583A8},
    {"char/nin48/motc.dat", 0x400168E4, 0x0, 0x9DF0}, {"char/nin48/mote.dat", 0x400AE6A9, 0x0, 0x5270C},
    {"char/nin48/moto.dat", 0x4004E820, 0x0, 0x2E358}, {"char/nin48/motbs.dat", 0x400A7AD0, 0x0, 0x5BAD0},
    {"char/nin48/motbt.dat", 0x400D7814, 0x0, 0x78FA8}, {"char/nin48/motrt.dat", 0x400552FC, 0x0, 0x31338},
    {"char/nin48/motrm.dat", 0x40026710, 0x0, 0x13EAC}, {"char/nin48/motfm.dat", 0x400A77B8, 0x0, 0x5C8E0},
    {"char/nin48/motrtoy.dat", 0x40008818, 0x0, 0x20E4}, {"char/nin48/motes.dat", 0x4002A408, 0x0, 0x141AC},
    {"char/nin48/motem.dat", 0x4007E20C, 0x0, 0x3BAA4}, {"char/nin48/motec.dat", 0x40028491, 0x0, 0x1175C},
    {"char/nin48/motpm.dat", 0x4007DF38, 0x0, 0x47EFC}, {"char/nin49/model0.dat", 0x40012910, 0x0, 0xCEDC},
    {"char/nin49/model1.dat", 0x4000D4C0, 0x0, 0x8994}, {"char/nin48/motb.dat", 0x40106D94, 0x0, 0x924E8},
    {"char/nin48/motr.dat", 0x40074128, 0x0, 0x42BDC}, {"char/nin48/motf.dat", 0x40114C60, 0x0, 0xA0C5C},
    {"char/nin48/motp.dat", 0x4009AB80, 0x0, 0x583A8}, {"char/nin48/motc.dat", 0x400168E4, 0x0, 0x9DF0},
    {"char/nin48/mote.dat", 0x400AE6A9, 0x0, 0x5270C}, {"char/nin48/moto.dat", 0x4004E820, 0x0, 0x2E358},
    {"char/nin48/motbs.dat", 0x400A7AD0, 0x0, 0x5BAD0}, {"char/nin48/motbt.dat", 0x400D7814, 0x0, 0x78FA8},
    {"char/nin48/motrt.dat", 0x400552FC, 0x0, 0x31338}, {"char/nin48/motrm.dat", 0x40026710, 0x0, 0x13EAC},
    {"char/nin48/motfm.dat", 0x400A77B8, 0x0, 0x5C8E0}, {"char/nin48/motrtoy.dat", 0x40008818, 0x0, 0x20E4},
    {"char/nin48/motes.dat", 0x4002A408, 0x0, 0x141AC}, {"char/nin48/motem.dat", 0x4007E20C, 0x0, 0x3BAA4},
    {"char/nin48/motec.dat", 0x40028491, 0x0, 0x1175C}, {"char/nin48/motpm.dat", 0x4007DF38, 0x0, 0x47EFC},
    {"char/nin50/model0.dat", 0x40013AD4, 0x0, 0xDDC8}, {"char/nin50/model1.dat", 0x4000D7E0, 0x0, 0x8C38},
    {"char/nin48/motb.dat", 0x40106D94, 0x0, 0x924E8}, {"char/nin48/motr.dat", 0x40074128, 0x0, 0x42BDC},
    {"char/nin48/motf.dat", 0x40114C60, 0x0, 0xA0C5C}, {"char/nin48/motp.dat", 0x4009AB80, 0x0, 0x583A8},
    {"char/nin48/motc.dat", 0x400168E4, 0x0, 0x9DF0}, {"char/nin48/mote.dat", 0x400AE6A9, 0x0, 0x5270C},
    {"char/nin48/moto.dat", 0x4004E820, 0x0, 0x2E358}, {"char/nin48/motbs.dat", 0x400A7AD0, 0x0, 0x5BAD0},
    {"char/nin48/motbt.dat", 0x400D7814, 0x0, 0x78FA8}, {"char/nin48/motrt.dat", 0x400552FC, 0x0, 0x31338},
    {"char/nin48/motrm.dat", 0x40026710, 0x0, 0x13EAC}, {"char/nin48/motfm.dat", 0x400A77B8, 0x0, 0x5C8E0},
    {"char/nin48/motrtoy.dat", 0x40008818, 0x0, 0x20E4}, {"char/nin48/motes.dat", 0x4002A408, 0x0, 0x141AC},
    {"char/nin48/motem.dat", 0x4007E20C, 0x0, 0x3BAA4}, {"char/nin48/motec.dat", 0x40028491, 0x0, 0x1175C},
    {"char/nin48/motpm.dat", 0x4007DF38, 0x0, 0x47EFC}, {"char/nin51/model0.dat", 0x40012910, 0x0, 0xCEB0},
    {"char/nin51/model1.dat", 0x4000D4C0, 0x0, 0x8968}, {"char/nin48/motb.dat", 0x40106D94, 0x0, 0x924E8},
    {"char/nin48/motr.dat", 0x40074128, 0x0, 0x42BDC}, {"char/nin48/motf.dat", 0x40114C60, 0x0, 0xA0C5C},
    {"char/nin48/motp.dat", 0x4009AB80, 0x0, 0x583A8}, {"char/nin48/motc.dat", 0x400168E4, 0x0, 0x9DF0},
    {"char/nin48/mote.dat", 0x400AE6A9, 0x0, 0x5270C}, {"char/nin48/moto.dat", 0x4004E820, 0x0, 0x2E358},
    {"char/nin48/motbs.dat", 0x400A7AD0, 0x0, 0x5BAD0}, {"char/nin48/motbt.dat", 0x400D7814, 0x0, 0x78FA8},
    {"char/nin48/motrt.dat", 0x400552FC, 0x0, 0x31338}, {"char/nin48/motrm.dat", 0x40026710, 0x0, 0x13EAC},
    {"char/nin48/motfm.dat", 0x400A77B8, 0x0, 0x5C8E0}, {"char/nin48/motrtoy.dat", 0x40008818, 0x0, 0x20E4},
    {"char/nin48/motes.dat", 0x4002A408, 0x0, 0x141AC}, {"char/nin48/motem.dat", 0x4007E20C, 0x0, 0x3BAA4},
    {"char/nin48/motec.dat", 0x40028491, 0x0, 0x1175C}, {"char/nin48/motpm.dat", 0x4007DF38, 0x0, 0x47EFC},
    {"char/nin52/model0.dat", 0x4001AE1C, 0x0, 0x1157C}, {"char/nin52/model1.dat", 0x4000FFE0, 0x0, 0x9BD8},
    {"char/nin27/motb.dat", 0x400D9004, 0x0, 0x7DC34}, {"char/nin27/motr.dat", 0x4005828C, 0x0, 0x318E8},
    {"char/nin27/motf.dat", 0x400E77C8, 0x0, 0x84D44}, {"char/nin27/motp.dat", 0x40071294, 0x0, 0x3E188},
    {"char/nin27/motc.dat", 0x40011370, 0x0, 0x8FA8}, {"char/nin27/mote.dat", 0x40077E54, 0x0, 0x3C340},
    {"char/nin27/moto.dat", 0x400336E0, 0x0, 0x1FB54}, {"char/nin27/motbs.dat", 0x40089DEC, 0x0, 0x4C700},
    {"char/nin27/motbt.dat", 0x400B74D8, 0x0, 0x69C9C}, {"char/nin27/motrt.dat", 0x4003EDC8, 0x0, 0x21E78},
    {"char/nin27/motrm.dat", 0x4001D924, 0x0, 0xE02C}, {"char/nin27/motfm.dat", 0x40084518, 0x0, 0x4750C},
    {"char/nin27/motrtoy.dat", 0x40008818, 0x0, 0x20E4}, {"char/nin27/motes.dat", 0x40020AD0, 0x0, 0xF47C},
    {"char/nin27/motem.dat", 0x4005013C, 0x0, 0x274E4}, {"char/nin27/motec.dat", 0x40021F9C, 0x0, 0xFB58},
    {"char/nin27/motpm.dat", 0x4005E514, 0x0, 0x33954}, {"char/nin53/model0.dat", 0x4001A71C, 0x0, 0x112D0},
    {"char/nin53/model1.dat", 0x4000F8E0, 0x0, 0x9924}, {"char/nin27/motb.dat", 0x400D9004, 0x0, 0x7DC34},
    {"char/nin27/motr.dat", 0x4005828C, 0x0, 0x318E8}, {"char/nin27/motf.dat", 0x400E77C8, 0x0, 0x84D44},
    {"char/nin27/motp.dat", 0x40071294, 0x0, 0x3E188}, {"char/nin27/motc.dat", 0x40011370, 0x0, 0x8FA8},
    {"char/nin27/mote.dat", 0x40077E54, 0x0, 0x3C340}, {"char/nin27/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin27/motbs.dat", 0x40089DEC, 0x0, 0x4C700}, {"char/nin27/motbt.dat", 0x400B74D8, 0x0, 0x69C9C},
    {"char/nin27/motrt.dat", 0x4003EDC8, 0x0, 0x21E78}, {"char/nin27/motrm.dat", 0x4001D924, 0x0, 0xE02C},
    {"char/nin27/motfm.dat", 0x40084518, 0x0, 0x4750C}, {"char/nin27/motrtoy.dat", 0x40008818, 0x0, 0x20E4},
    {"char/nin27/motes.dat", 0x40020AD0, 0x0, 0xF47C}, {"char/nin27/motem.dat", 0x4005013C, 0x0, 0x274E4},
    {"char/nin27/motec.dat", 0x40021F9C, 0x0, 0xFB58}, {"char/nin27/motpm.dat", 0x4005E514, 0x0, 0x33954},
    {"char/nin00/model0.dat", 0x4001E0CC, 0x0, 0x12DE4}, {"char/nin00/model1.dat", 0x4000D740, 0x0, 0x9230},
    {"char/nin00/motb2.dat", 0x4006B68A, 0x0, 0x482D0}, {"char/nin00/motr2.dat", 0x4003530A, 0x0, 0x22FBC},
    {"char/nin00/motf2.dat", 0x4006C460, 0x0, 0x461C4}, {"char/nin00/motp2.dat", 0x400463F6, 0x0, 0x2F958},
    {"char/nin00/motc2.dat", 0x40004F52, 0x0, 0x32A0}, {"char/nin00/mote2.dat", 0x4004134C, 0x0, 0x2B6C4},
    {"char/nin00/moto.dat", 0x40060268, 0x0, 0x39908}, {"char/nin00/motbs2.dat", 0x4003EF10, 0x0, 0x28C6C},
    {"char/nin00/motbt2.dat", 0x40053C78, 0x0, 0x379C4}, {"char/nin00/motrt2.dat", 0x4002151A, 0x0, 0x14F54},
    {"char/nin00/motrm2.dat", 0x4000E51E, 0x0, 0x8184}, {"char/nin00/motfm2.dat", 0x4003FA2A, 0x0, 0x26DB4},
    {"char/nin00/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8}, {"char/nin00/motes2.dat", 0x4000EFCE, 0x0, 0x8CDC},
    {"char/nin00/motem2.dat", 0x4002A1AE, 0x0, 0x1BA08}, {"char/nin00/motec2.dat", 0x40014CC8, 0x0, 0xD1DC},
    {"char/nin00/motpm2.dat", 0x40039BD8, 0x0, 0x26FD4}, {"char/nin01/model0.dat", 0x40025734, 0x0, 0x1803C},
    {"char/nin01/model1.dat", 0x40010340, 0x0, 0xB790}, {"char/nin01/motb2.dat", 0x40071B74, 0x0, 0x4CBE0},
    {"char/nin01/motr2.dat", 0x400330EA, 0x0, 0x21CB8}, {"char/nin01/motf2.dat", 0x4006E90E, 0x0, 0x4798C},
    {"char/nin01/motp2.dat", 0x4003E156, 0x0, 0x2A490}, {"char/nin01/motc2.dat", 0x400051F6, 0x0, 0x356C},
    {"char/nin01/mote2.dat", 0x400381B0, 0x0, 0x25678}, {"char/nin01/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin01/motbs2.dat", 0x40042B48, 0x0, 0x2B5FC}, {"char/nin01/motbt2.dat", 0x40057066, 0x0, 0x3A394},
    {"char/nin01/motrt2.dat", 0x40020BB4, 0x0, 0x150B8}, {"char/nin01/motrm2.dat", 0x40010964, 0x0, 0x9CE8},
    {"char/nin01/motfm2.dat", 0x4003F8D8, 0x0, 0x2706C}, {"char/nin01/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8},
    {"char/nin01/motes2.dat", 0x4000E896, 0x0, 0x8ADC}, {"char/nin01/motem2.dat", 0x40029E6C, 0x0, 0x1B9A4},
    {"char/nin01/motec2.dat", 0x4000FB9C, 0x0, 0x9A00}, {"char/nin01/motpm2.dat", 0x40036258, 0x0, 0x24C3C},
    {"char/nin02/model0.dat", 0x4001D3B8, 0x0, 0x15034}, {"char/nin02/model1.dat", 0x4000EDE0, 0x0, 0xAD10},
    {"char/nin02/motb2.dat", 0x4004F750, 0x0, 0x330FC}, {"char/nin02/motr2.dat", 0x40026116, 0x0, 0x176E8},
    {"char/nin02/motf2.dat", 0x400512CA, 0x0, 0x314FC}, {"char/nin02/motp2.dat", 0x40030326, 0x0, 0x1F2F4},
    {"char/nin02/motc2.dat", 0x40003DFA, 0x0, 0x259C}, {"char/nin02/mote2.dat", 0x4002AE18, 0x0, 0x1B4AC},
    {"char/nin02/moto.dat", 0x40033688, 0x0, 0x1FBB8}, {"char/nin02/motbs2.dat", 0x4002D4E4, 0x0, 0x1BC0C},
    {"char/nin02/motbt2.dat", 0x40041982, 0x0, 0x29C54}, {"char/nin02/motrt2.dat", 0x40019D7C, 0x0, 0xEFDC},
    {"char/nin02/motrm2.dat", 0x4000C01A, 0x0, 0x626C}, {"char/nin02/motfm2.dat", 0x4002D21A, 0x0, 0x19420},
    {"char/nin02/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8}, {"char/nin02/motes2.dat", 0x4000A1B0, 0x0, 0x5930},
    {"char/nin02/motem2.dat", 0x40015A48, 0x0, 0xCFC0}, {"char/nin02/motec2.dat", 0x4001545A, 0x0, 0xDCEC},
    {"char/nin02/motpm2.dat", 0x40024B20, 0x0, 0x17880}, {"char/nin03/model0.dat", 0x40021A44, 0x0, 0x15E08},
    {"char/nin03/model1.dat", 0x40013E80, 0x0, 0xC09C}, {"char/nin03/motb2.dat", 0x4005B674, 0x0, 0x3B850},
    {"char/nin03/motr2.dat", 0x4002A888, 0x0, 0x1AD54}, {"char/nin03/motf2.dat", 0x40066E30, 0x0, 0x3FDB0},
    {"char/nin03/motp2.dat", 0x40034D20, 0x0, 0x229F8}, {"char/nin03/motc2.dat", 0x40004FA6, 0x0, 0x325C},
    {"char/nin03/mote2.dat", 0x4002A838, 0x0, 0x1AF58}, {"char/nin03/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin03/motbs2.dat", 0x400326BC, 0x0, 0x1ED5C}, {"char/nin03/motbt2.dat", 0x40049FB6, 0x0, 0x2F7F4},
    {"char/nin03/motrt2.dat", 0x4001DBE2, 0x0, 0x11EB0}, {"char/nin03/motrm2.dat", 0x4000D434, 0x0, 0x7404},
    {"char/nin03/motfm2.dat", 0x40037CB2, 0x0, 0x20D5C}, {"char/nin03/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8},
    {"char/nin03/motes2.dat", 0x4000D3E4, 0x0, 0x7AC8}, {"char/nin03/motem2.dat", 0x400241E0, 0x0, 0x17754},
    {"char/nin03/motec2.dat", 0x400074FA, 0x0, 0x3B58}, {"char/nin03/motpm2.dat", 0x400296F0, 0x0, 0x1B180},
    {"char/nin04/model0.dat", 0x4001DA50, 0x0, 0x14788}, {"char/nin04/model1.dat", 0x40012940, 0x0, 0xC298},
    {"char/nin04/motb2.dat", 0x4006A3E0, 0x0, 0x433F4}, {"char/nin04/motr2.dat", 0x40027CE6, 0x0, 0x19288},
    {"char/nin04/motf2.dat", 0x4004CB76, 0x0, 0x2E608}, {"char/nin04/motp2.dat", 0x4002CE6E, 0x0, 0x1CD24},
    {"char/nin04/motc2.dat", 0x400036F6, 0x0, 0x21D4}, {"char/nin04/mote2.dat", 0x4003C714, 0x0, 0x26594},
    {"char/nin04/moto.dat", 0x40041E74, 0x0, 0x28DE4}, {"char/nin04/motbs2.dat", 0x400419F0, 0x0, 0x27E8C},
    {"char/nin04/motbt2.dat", 0x4005062C, 0x0, 0x32064}, {"char/nin04/motrt2.dat", 0x4001A68E, 0x0, 0x10100},
    {"char/nin04/motrm2.dat", 0x4000BD0C, 0x0, 0x6490}, {"char/nin04/motfm2.dat", 0x4002BA3A, 0x0, 0x18890},
    {"char/nin04/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8}, {"char/nin04/motes2.dat", 0x4000C5B2, 0x0, 0x6B28},
    {"char/nin04/motem2.dat", 0x40020164, 0x0, 0x136F8}, {"char/nin04/motec2.dat", 0x4001CBB4, 0x0, 0x12298},
    {"char/nin04/motpm2.dat", 0x400226E4, 0x0, 0x15C94}, {"char/nin05/model0.dat", 0x40022118, 0x0, 0x187C0},
    {"char/nin05/model1.dat", 0x400123C0, 0x0, 0xBFF0}, {"char/nin05/motb2.dat", 0x40050AD6, 0x0, 0x33BC0},
    {"char/nin05/motr2.dat", 0x4002B29A, 0x0, 0x1B754}, {"char/nin05/motf2.dat", 0x4004A654, 0x0, 0x2D3CC},
    {"char/nin05/motp2.dat", 0x4002BEC8, 0x0, 0x1C92C}, {"char/nin05/motc2.dat", 0x40003118, 0x0, 0x1D60},
    {"char/nin05/mote2.dat", 0x400247BA, 0x0, 0x1667C}, {"char/nin05/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin05/motbs2.dat", 0x4003179A, 0x0, 0x1E794}, {"char/nin05/motbt2.dat", 0x4003E9CA, 0x0, 0x277FC},
    {"char/nin05/motrt2.dat", 0x4001C9AC, 0x0, 0x1160C}, {"char/nin05/motrm2.dat", 0x4000C6AE, 0x0, 0x6854},
    {"char/nin05/motfm2.dat", 0x4002C2A0, 0x0, 0x18E60}, {"char/nin05/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8},
    {"char/nin05/motes2.dat", 0x4000AEE6, 0x0, 0x6214}, {"char/nin05/motem2.dat", 0x40018F00, 0x0, 0xF6DC},
    {"char/nin05/motec2.dat", 0x4000BBFC, 0x0, 0x5C28}, {"char/nin05/motpm2.dat", 0x40022828, 0x0, 0x160CC},
    {"char/nin06/model0.dat", 0x40018A20, 0x0, 0x12304}, {"char/nin06/model1.dat", 0x4000F780, 0x0, 0xAB70},
    {"char/nin06/motb2.dat", 0x4005A288, 0x0, 0x39AEC}, {"char/nin06/motr2.dat", 0x400243C0, 0x0, 0x15F24},
    {"char/nin06/motf2.dat", 0x400646EE, 0x0, 0x3CCEC}, {"char/nin06/motp2.dat", 0x400367C6, 0x0, 0x23434},
    {"char/nin06/motc2.dat", 0x40004876, 0x0, 0x29F8}, {"char/nin06/mote2.dat", 0x40034CBA, 0x0, 0x21AD0},
    {"char/nin06/moto.dat", 0x40047D12, 0x0, 0x2EC54}, {"char/nin06/motbs2.dat", 0x400365E6, 0x0, 0x212F8},
    {"char/nin06/motbt2.dat", 0x4004AC40, 0x0, 0x2F514}, {"char/nin06/motrt2.dat", 0x400194C0, 0x0, 0xEB48},
    {"char/nin06/motrm2.dat", 0x4000B016, 0x0, 0x5714}, {"char/nin06/motfm2.dat", 0x40034024, 0x0, 0x1DD38},
    {"char/nin06/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8}, {"char/nin06/motes2.dat", 0x4000BDA2, 0x0, 0x6620},
    {"char/nin06/motem2.dat", 0x4001AD8C, 0x0, 0xFC34}, {"char/nin06/motec2.dat", 0x4001A11C, 0x0, 0x10ADC},
    {"char/nin06/motpm2.dat", 0x40029CE2, 0x0, 0x1B300}, {"char/nin07/model0.dat", 0x4001C328, 0x0, 0x1365C},
    {"char/nin07/model1.dat", 0x4000EAE0, 0x0, 0x8F28}, {"char/nin07/motb2.dat", 0x4005B686, 0x0, 0x3AB30},
    {"char/nin07/motr2.dat", 0x40024D32, 0x0, 0x17034}, {"char/nin07/motf2.dat", 0x40052E02, 0x0, 0x32730},
    {"char/nin07/motp2.dat", 0x400300AE, 0x0, 0x1E3C8}, {"char/nin07/motc2.dat", 0x40003006, 0x0, 0x1AD4},
    {"char/nin07/mote2.dat", 0x400238FE, 0x0, 0x14504}, {"char/nin07/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin07/motbs2.dat", 0x400368F4, 0x0, 0x21C08}, {"char/nin07/motbt2.dat", 0x40048258, 0x0, 0x2D55C},
    {"char/nin07/motrt2.dat", 0x4001A49A, 0x0, 0x10014}, {"char/nin07/motrm2.dat", 0x4000B5B2, 0x0, 0x5FE4},
    {"char/nin07/motfm2.dat", 0x4002E658, 0x0, 0x1A45C}, {"char/nin07/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8},
    {"char/nin07/motes2.dat", 0x4000B8F8, 0x0, 0x6478}, {"char/nin07/motem2.dat", 0x40019758, 0x0, 0xECA0},
    {"char/nin07/motec2.dat", 0x4000A088, 0x0, 0x4AC4}, {"char/nin07/motpm2.dat", 0x40025B00, 0x0, 0x17934},
    {"char/nin08/model0.dat", 0x4001D77C, 0x0, 0x14104}, {"char/nin08/model1.dat", 0x400103C0, 0x0, 0x9A1C},
    {"char/nin08/motb2.dat", 0x4005EEA8, 0x0, 0x3D418}, {"char/nin08/motr2.dat", 0x40025B5E, 0x0, 0x17480},
    {"char/nin08/motf2.dat", 0x40051204, 0x0, 0x316C0}, {"char/nin08/motp2.dat", 0x4002F91C, 0x0, 0x1E5D4},
    {"char/nin08/motc2.dat", 0x40003006, 0x0, 0x1AD4}, {"char/nin08/mote2.dat", 0x40020EC0, 0x0, 0x13524},
    {"char/nin08/moto.dat", 0x400336E0, 0x0, 0x1FB54}, {"char/nin08/motbs2.dat", 0x40039F6C, 0x0, 0x246BC},
    {"char/nin08/motbt2.dat", 0x4004CB3A, 0x0, 0x30AF0}, {"char/nin08/motrt2.dat", 0x400190BA, 0x0, 0xF270},
    {"char/nin08/motrm2.dat", 0x4000AB5A, 0x0, 0x5938}, {"char/nin08/motfm2.dat", 0x4002CB32, 0x0, 0x19510},
    {"char/nin08/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8}, {"char/nin08/motes2.dat", 0x400072FA, 0x0, 0x3440},
    {"char/nin08/motem2.dat", 0x40016576, 0x0, 0xD6B0}, {"char/nin08/motec2.dat", 0x4000B434, 0x0, 0x56CC},
    {"char/nin08/motpm2.dat", 0x400239BA, 0x0, 0x169B0}, {"char/nin09/model0.dat", 0x40018B54, 0x0, 0x12A70},
    {"char/nin09/model1.dat", 0x4000D540, 0x0, 0x9CC0}, {"char/nin09/motb2.dat", 0x4004D7E4, 0x0, 0x31D7C},
    {"char/nin09/motr2.dat", 0x40037FC6, 0x0, 0x22C80}, {"char/nin09/motf2.dat", 0x4005EBEE, 0x0, 0x387F4},
    {"char/nin09/motp2.dat", 0x4002CF56, 0x0, 0x1D058}, {"char/nin09/motc2.dat", 0x40002F1A, 0x0, 0x18FC},
    {"char/nin09/mote2.dat", 0x40028434, 0x0, 0x18E74}, {"char/nin09/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin09/motbs2.dat", 0x4002E0C0, 0x0, 0x1C780}, {"char/nin09/motbt2.dat", 0x4003E236, 0x0, 0x273D0},
    {"char/nin09/motrt2.dat", 0x4002CCB6, 0x0, 0x1B1AC}, {"char/nin09/motrm2.dat", 0x4000FE7E, 0x0, 0x9080},
    {"char/nin09/motfm2.dat", 0x40033542, 0x0, 0x1CBAC}, {"char/nin09/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8},
    {"char/nin09/motes2.dat", 0x4000AC66, 0x0, 0x5A5C}, {"char/nin09/motem2.dat", 0x40016AC0, 0x0, 0xD1FC},
    {"char/nin09/motec2.dat", 0x400123B4, 0x0, 0xB4DC}, {"char/nin09/motpm2.dat", 0x40024998, 0x0, 0x176D0},
    {"char/nin10/model0.dat", 0x40020F10, 0x0, 0x147E0}, {"char/nin10/model1.dat", 0x400124A0, 0x0, 0xC3F4},
    {"char/nin10/motb2.dat", 0x400781B0, 0x0, 0x503D0}, {"char/nin10/motr2.dat", 0x40031DC0, 0x0, 0x20478},
    {"char/nin10/motf2.dat", 0x4006F6A4, 0x0, 0x474BC}, {"char/nin10/motp2.dat", 0x4004A76A, 0x0, 0x323A0},
    {"char/nin10/motc2.dat", 0x400045B8, 0x0, 0x2A84}, {"char/nin10/mote2.dat", 0x40053C9C, 0x0, 0x36ED4},
    {"char/nin10/moto.dat", 0x400336E0, 0x0, 0x1FB54}, {"char/nin10/motbs2.dat", 0x40045274, 0x0, 0x2CA68},
    {"char/nin10/motbt2.dat", 0x4005D642, 0x0, 0x3E028}, {"char/nin10/motrt2.dat", 0x40022E6C, 0x0, 0x165FC},
    {"char/nin10/motrm2.dat", 0x4000D904, 0x0, 0x7970}, {"char/nin10/motfm2.dat", 0x4003A402, 0x0, 0x22C60},
    {"char/nin10/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8}, {"char/nin10/motes2.dat", 0x40012FA4, 0x0, 0xB900},
    {"char/nin10/motem2.dat", 0x4002EF92, 0x0, 0x1E018}, {"char/nin10/motec2.dat", 0x4001F4E2, 0x0, 0x141D0},
    {"char/nin10/motpm2.dat", 0x400343CA, 0x0, 0x22780}, {"char/nin11/model0.dat", 0x4001F64C, 0x0, 0x17088},
    {"char/nin11/model1.dat", 0x40012BE0, 0x0, 0xCC14}, {"char/nin11/motb2.dat", 0x40068578, 0x0, 0x46BB4},
    {"char/nin11/motr2.dat", 0x40031280, 0x0, 0x2089C}, {"char/nin11/motf2.dat", 0x40069882, 0x0, 0x445B0},
    {"char/nin11/motp2.dat", 0x4003D6AA, 0x0, 0x29480}, {"char/nin11/motc2.dat", 0x40004B94, 0x0, 0x3224},
    {"char/nin11/mote2.dat", 0x4003BBE2, 0x0, 0x282E0}, {"char/nin11/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin11/motbs2.dat", 0x40040560, 0x0, 0x2A4A0}, {"char/nin11/motbt2.dat", 0x40051990, 0x0, 0x369E4},
    {"char/nin11/motrt2.dat", 0x400203A2, 0x0, 0x14828}, {"char/nin11/motrm2.dat", 0x400101B6, 0x0, 0x9564},
    {"char/nin11/motfm2.dat", 0x4003F2A8, 0x0, 0x26994}, {"char/nin11/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8},
    {"char/nin11/motes2.dat", 0x40014482, 0x0, 0xCC6C}, {"char/nin11/motem2.dat", 0x4002A7F4, 0x0, 0x1BFE4},
    {"char/nin11/motec2.dat", 0x4000E6B8, 0x0, 0x8B44}, {"char/nin11/motpm2.dat", 0x4002EA98, 0x0, 0x1EEC8},
    {"char/nin12/model0.dat", 0x40020FDC, 0x0, 0x17938}, {"char/nin12/model1.dat", 0x4000DFC0, 0x0, 0xA1FC},
    {"char/nin12/motb2.dat", 0x40049138, 0x0, 0x2F164}, {"char/nin12/motr2.dat", 0x40031382, 0x0, 0x1F8DC},
    {"char/nin12/motf2.dat", 0x4005105A, 0x0, 0x30DEC}, {"char/nin12/motp2.dat", 0x4002C1C6, 0x0, 0x1CC24},
    {"char/nin12/motc2.dat", 0x40002E32, 0x0, 0x1974}, {"char/nin12/mote2.dat", 0x4001E428, 0x0, 0x10C08},
    {"char/nin12/moto.dat", 0x400336E0, 0x0, 0x1FB54}, {"char/nin12/motbs2.dat", 0x4002E522, 0x0, 0x1CD78},
    {"char/nin12/motbt2.dat", 0x40034EF2, 0x0, 0x21214}, {"char/nin12/motrt2.dat", 0x40028D72, 0x0, 0x1A2BC},
    {"char/nin12/motrm2.dat", 0x40010670, 0x0, 0x94DC}, {"char/nin12/motfm2.dat", 0x4002E65C, 0x0, 0x1A2F0},
    {"char/nin12/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8}, {"char/nin12/motes2.dat", 0x400094FC, 0x0, 0x4898},
    {"char/nin12/motem2.dat", 0x4001327A, 0x0, 0xAE18}, {"char/nin12/motec2.dat", 0x4000C15C, 0x0, 0x5F60},
    {"char/nin12/motpm2.dat", 0x40026034, 0x0, 0x18D34}, {"char/nin13/model0.dat", 0x400195B0, 0x0, 0xF888},
    {"char/nin13/model1.dat", 0x4000E380, 0x0, 0x9378}, {"char/nin13/motb2.dat", 0x40040FD2, 0x0, 0x288D0},
    {"char/nin13/motr2.dat", 0x40028B14, 0x0, 0x18898}, {"char/nin13/motf2.dat", 0x4004970A, 0x0, 0x2BF80},
    {"char/nin13/motp2.dat", 0x40027110, 0x0, 0x19234}, {"char/nin13/motc2.dat", 0x40003240, 0x0, 0x1D98},
    {"char/nin13/mote2.dat", 0x40021204, 0x0, 0x126C4}, {"char/nin13/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin13/motbs2.dat", 0x400287E0, 0x0, 0x185F8}, {"char/nin13/motbt2.dat", 0x40034F7C, 0x0, 0x208EC},
    {"char/nin13/motrt2.dat", 0x4001C13E, 0x0, 0x103B4}, {"char/nin13/motrm2.dat", 0x4000A8D6, 0x0, 0x53E4},
    {"char/nin13/motfm2.dat", 0x4002C7BC, 0x0, 0x18900}, {"char/nin13/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8},
    {"char/nin13/motes2.dat", 0x4000A956, 0x0, 0x58FC}, {"char/nin13/motem2.dat", 0x400153CE, 0x0, 0xBDEC},
    {"char/nin13/motec2.dat", 0x4000C1D4, 0x0, 0x6160}, {"char/nin13/motpm2.dat", 0x4001F8E2, 0x0, 0x13EC8},
    {"char/nin14/model0.dat", 0x40015CE0, 0x0, 0xE0D0}, {"char/nin14/model1.dat", 0x40010700, 0x0, 0x9E1C},
    {"char/nin14/motb2.dat", 0x400263BC, 0x0, 0x17774}, {"char/nin14/motr2.dat", 0x40011560, 0x0, 0x9CA8},
    {"char/nin14/motf2.dat", 0x4002BEEE, 0x0, 0x182D8}, {"char/nin14/motp2.dat", 0x40018D02, 0x0, 0xFEC8},
    {"char/nin14/motc2.dat", 0x40003542, 0x0, 0x2188}, {"char/nin14/mote2.dat", 0x400111D2, 0x0, 0x9B94},
    {"char/nin14/moto.dat", 0x400338F0, 0x0, 0x1FCB0}, {"char/nin14/motbs2.dat", 0x40017428, 0x0, 0xC900},
    {"char/nin14/motbt2.dat", 0x4002243A, 0x0, 0x147AC}, {"char/nin14/motrt2.dat", 0x40010B90, 0x0, 0x92D8},
    {"char/nin14/motrm2.dat", 0x40008F30, 0x0, 0x453C}, {"char/nin14/motfm2.dat", 0x4001D1D0, 0x0, 0xEAF8},
    {"char/nin14/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8}, {"char/nin14/motes2.dat", 0x40007FCC, 0x0, 0x3DD4},
    {"char/nin14/motem2.dat", 0x4000F10A, 0x0, 0x88EC}, {"char/nin14/motec2.dat", 0x40006260, 0x0, 0x29C8},
    {"char/nin14/motpm2.dat", 0x40018028, 0x0, 0xF504}, {"char/nin15/model0.dat", 0x40019EF0, 0x0, 0x10BDC},
    {"char/nin15/model1.dat", 0x400118C0, 0x0, 0xA8D8}, {"char/nin15/motb2.dat", 0x40057EF6, 0x0, 0x37E90},
    {"char/nin15/motr2.dat", 0x4002D4BA, 0x0, 0x1B2E8}, {"char/nin15/motf2.dat", 0x4005F900, 0x0, 0x39650},
    {"char/nin15/motp2.dat", 0x4003328A, 0x0, 0x20D0C}, {"char/nin15/motc2.dat", 0x4000445C, 0x0, 0x2914},
    {"char/nin15/mote2.dat", 0x4002BB78, 0x0, 0x198BC}, {"char/nin15/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin15/motbs2.dat", 0x400367B0, 0x0, 0x215C8}, {"char/nin15/motbt2.dat", 0x40046816, 0x0, 0x2C1C0},
    {"char/nin15/motrt2.dat", 0x40020532, 0x0, 0x13118}, {"char/nin15/motrm2.dat", 0x4000D9C4, 0x0, 0x71A8},
    {"char/nin15/motfm2.dat", 0x400348B2, 0x0, 0x1DC44}, {"char/nin15/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8},
    {"char/nin15/motes2.dat", 0x4000CEF0, 0x0, 0x7364}, {"char/nin15/motem2.dat", 0x4001BA58, 0x0, 0x10264},
    {"char/nin15/motec2.dat", 0x4000D9EA, 0x0, 0x6DA0}, {"char/nin15/motpm2.dat", 0x4002A708, 0x0, 0x1B308},
    {"char/nin16/model0.dat", 0x40016320, 0x0, 0xE1B8}, {"char/nin16/model1.dat", 0x40012C40, 0x0, 0xB6EC},
    {"char/nin16/motb2.dat", 0x400458E4, 0x0, 0x2A024}, {"char/nin16/motr2.dat", 0x40020E66, 0x0, 0x12FA0},
    {"char/nin16/motf2.dat", 0x4004D5C8, 0x0, 0x2C2FC}, {"char/nin16/motp2.dat", 0x40027776, 0x0, 0x171A4},
    {"char/nin16/motc2.dat", 0x400032EC, 0x0, 0x1EDC}, {"char/nin16/mote2.dat", 0x4001F090, 0x0, 0x107BC},
    {"char/nin16/moto.dat", 0x400336E0, 0x0, 0x1FB54}, {"char/nin16/motbs2.dat", 0x4002A278, 0x0, 0x180AC},
    {"char/nin16/motbt2.dat", 0x400360EE, 0x0, 0x2033C}, {"char/nin16/motrt2.dat", 0x4001768C, 0x0, 0xD18C},
    {"char/nin16/motrm2.dat", 0x4000BB46, 0x0, 0x5F20}, {"char/nin16/motfm2.dat", 0x4002C576, 0x0, 0x17A08},
    {"char/nin16/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8}, {"char/nin16/motes2.dat", 0x4000A4DC, 0x0, 0x5138},
    {"char/nin16/motem2.dat", 0x4001464C, 0x0, 0xB2AC}, {"char/nin16/motec2.dat", 0x4000A8BE, 0x0, 0x4E84},
    {"char/nin16/motpm2.dat", 0x40020A94, 0x0, 0x128C4}, {"char/nin17/model0.dat", 0x4001D724, 0x0, 0x12518},
    {"char/nin17/model1.dat", 0x40012F00, 0x0, 0xAB08}, {"char/nin17/motb2.dat", 0x4005D366, 0x0, 0x3C424},
    {"char/nin17/motr2.dat", 0x4002DF2C, 0x0, 0x1C508}, {"char/nin17/motf2.dat", 0x40060B9A, 0x0, 0x3A5D4},
    {"char/nin17/motp2.dat", 0x400380CE, 0x0, 0x246B0}, {"char/nin17/motc2.dat", 0x40004A8E, 0x0, 0x30B4},
    {"char/nin17/mote2.dat", 0x400298A0, 0x0, 0x19DFC}, {"char/nin17/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin17/motbs2.dat", 0x40036B26, 0x0, 0x21F44}, {"char/nin17/motbt2.dat", 0x4004DA60, 0x0, 0x31808},
    {"char/nin17/motrt2.dat", 0x40021438, 0x0, 0x139F8}, {"char/nin17/motrm2.dat", 0x4000CF50, 0x0, 0x6E08},
    {"char/nin17/motfm2.dat", 0x40033E76, 0x0, 0x1DDE8}, {"char/nin17/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8},
    {"char/nin17/motes2.dat", 0x4000C0B2, 0x0, 0x6B48}, {"char/nin17/motem2.dat", 0x4001AFF8, 0x0, 0x10BD8},
    {"char/nin17/motec2.dat", 0x4000C984, 0x0, 0x66D0}, {"char/nin17/motpm2.dat", 0x4002D3D6, 0x0, 0x1D1DC},
    {"char/nin18/model0.dat", 0x40017DE0, 0x0, 0x10298}, {"char/nin18/model1.dat", 0x4000F020, 0x0, 0x8B10},
    {"char/nin18/motb2.dat", 0x4003CBF8, 0x0, 0x26744}, {"char/nin18/motr2.dat", 0x40021AE4, 0x0, 0x14CF8},
    {"char/nin18/motf2.dat", 0x40053E92, 0x0, 0x335AC}, {"char/nin18/motp2.dat", 0x400283FA, 0x0, 0x198E0},
    {"char/nin18/motc2.dat", 0x4000487E, 0x0, 0x2F20}, {"char/nin18/mote2.dat", 0x4001D696, 0x0, 0x11754},
    {"char/nin18/moto.dat", 0x4009C7A8, 0x0, 0x5C1DC}, {"char/nin18/motbs2.dat", 0x4002596A, 0x0, 0x16CB4},
    {"char/nin18/motbt2.dat", 0x40032728, 0x0, 0x1F8E4}, {"char/nin18/motrt2.dat", 0x4001969E, 0x0, 0xF278},
    {"char/nin18/motrm2.dat", 0x4000BB26, 0x0, 0x63F8}, {"char/nin18/motfm2.dat", 0x40030CB0, 0x0, 0x1C030},
    {"char/nin18/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8}, {"char/nin18/motes2.dat", 0x4000BCBA, 0x0, 0x6588},
    {"char/nin18/motem2.dat", 0x40015AB0, 0x0, 0xCE94}, {"char/nin18/motec2.dat", 0x40006E06, 0x0, 0x3464},
    {"char/nin18/motpm2.dat", 0x40021344, 0x0, 0x14A5C}, {"char/nin19/model0.dat", 0x4001ABB8, 0x0, 0x1390C},
    {"char/nin19/model1.dat", 0x4000D5C0, 0x0, 0x8CF0}, {"char/nin19/motb2.dat", 0x400511C0, 0x0, 0x33070},
    {"char/nin19/motr2.dat", 0x40029DF6, 0x0, 0x1A77C}, {"char/nin19/motf2.dat", 0x40056008, 0x0, 0x356FC},
    {"char/nin19/motp2.dat", 0x40031126, 0x0, 0x20050}, {"char/nin19/motc2.dat", 0x40003046, 0x0, 0x1CF4},
    {"char/nin19/mote2.dat", 0x4001E068, 0x0, 0x11720}, {"char/nin19/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin19/motbs2.dat", 0x4002C38C, 0x0, 0x1A994}, {"char/nin19/motbt2.dat", 0x40045058, 0x0, 0x2B49C},
    {"char/nin19/motrt2.dat", 0x4001D1F8, 0x0, 0x11ED0}, {"char/nin19/motrm2.dat", 0x4000BB9E, 0x0, 0x6454},
    {"char/nin19/motfm2.dat", 0x4002FF30, 0x0, 0x1B748}, {"char/nin19/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8},
    {"char/nin19/motes2.dat", 0x4000A028, 0x0, 0x5460}, {"char/nin19/motem2.dat", 0x40012554, 0x0, 0xAEBC},
    {"char/nin19/motec2.dat", 0x4000B274, 0x0, 0x5774}, {"char/nin19/motpm2.dat", 0x40026860, 0x0, 0x19188},
    {"char/nin20/model0.dat", 0x40022D3C, 0x0, 0x19184}, {"char/nin20/model1.dat", 0x4000FD40, 0x0, 0xB93C},
    {"char/nin20/motb2.dat", 0x4003B996, 0x0, 0x25900}, {"char/nin20/motr2.dat", 0x400229E2, 0x0, 0x147AC},
    {"char/nin20/motf2.dat", 0x4003FFC8, 0x0, 0x257DC}, {"char/nin20/motp2.dat", 0x4002C386, 0x0, 0x1C328},
    {"char/nin20/motc2.dat", 0x40002F9A, 0x0, 0x1A28}, {"char/nin20/mote2.dat", 0x400182F0, 0x0, 0xCC9C},
    {"char/nin20/moto.dat", 0x400336E0, 0x0, 0x1FB54}, {"char/nin20/motbs2.dat", 0x400213EE, 0x0, 0x13540},
    {"char/nin20/motbt2.dat", 0x40031ECA, 0x0, 0x1F04C}, {"char/nin20/motrt2.dat", 0x40018A28, 0x0, 0xE00C},
    {"char/nin20/motrm2.dat", 0x4000BDEA, 0x0, 0x61F8}, {"char/nin20/motfm2.dat", 0x40024616, 0x0, 0x130CC},
    {"char/nin20/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8}, {"char/nin20/motes2.dat", 0x40007B86, 0x0, 0x39A8},
    {"char/nin20/motem2.dat", 0x4000F814, 0x0, 0x831C}, {"char/nin20/motec2.dat", 0x4000A68C, 0x0, 0x4D44},
    {"char/nin20/motpm2.dat", 0x400246A6, 0x0, 0x17314}, {"char/nin21/model0.dat", 0x4001881C, 0x0, 0x10B50},
    {"char/nin21/model1.dat", 0x4000F500, 0x0, 0x9DA8}, {"char/nin21/motb2.dat", 0x4005781C, 0x0, 0x37718},
    {"char/nin21/motr2.dat", 0x400275C6, 0x0, 0x17994}, {"char/nin21/motf2.dat", 0x400537C0, 0x0, 0x3152C},
    {"char/nin21/motp2.dat", 0x4002D706, 0x0, 0x1C6C4}, {"char/nin21/motc2.dat", 0x400033A0, 0x0, 0x1CF4},
    {"char/nin21/mote2.dat", 0x40027F1A, 0x0, 0x18568}, {"char/nin21/moto.dat", 0x4004F674, 0x0, 0x2E878},
    {"char/nin21/motbs2.dat", 0x4003316A, 0x0, 0x1EF94}, {"char/nin21/motbt2.dat", 0x40044332, 0x0, 0x2A1E0},
    {"char/nin21/motrt2.dat", 0x40019734, 0x0, 0xEEC4}, {"char/nin21/motrm2.dat", 0x4000BA08, 0x0, 0x610C},
    {"char/nin21/motfm2.dat", 0x4002BD48, 0x0, 0x17EE0}, {"char/nin21/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8},
    {"char/nin21/motes2.dat", 0x4000D3D6, 0x0, 0x7510}, {"char/nin21/motem2.dat", 0x4002146A, 0x0, 0x147E0},
    {"char/nin21/motec2.dat", 0x40009344, 0x0, 0x4C7C}, {"char/nin21/motpm2.dat", 0x40024B40, 0x0, 0x170B8},
    {"char/nin22/model0.dat", 0x400176FC, 0x0, 0xFEA4}, {"char/nin22/model1.dat", 0x4000F500, 0x0, 0x9D94},
    {"char/nin21/motb2.dat", 0x4005781C, 0x0, 0x37718}, {"char/nin21/motr2.dat", 0x400275C6, 0x0, 0x17994},
    {"char/nin21/motf2.dat", 0x400537C0, 0x0, 0x3152C}, {"char/nin21/motp2.dat", 0x4002D706, 0x0, 0x1C6C4},
    {"char/nin21/motc2.dat", 0x400033A0, 0x0, 0x1CF4}, {"char/nin21/mote2.dat", 0x40027F1A, 0x0, 0x18568},
    {"char/nin21/moto.dat", 0x4004F674, 0x0, 0x2E878}, {"char/nin21/motbs2.dat", 0x4003316A, 0x0, 0x1EF94},
    {"char/nin21/motbt2.dat", 0x40044332, 0x0, 0x2A1E0}, {"char/nin21/motrt2.dat", 0x40019734, 0x0, 0xEEC4},
    {"char/nin21/motrm2.dat", 0x4000BA08, 0x0, 0x610C}, {"char/nin21/motfm2.dat", 0x4002BD48, 0x0, 0x17EE0},
    {"char/nin21/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8}, {"char/nin21/motes2.dat", 0x4000D3D6, 0x0, 0x7510},
    {"char/nin21/motem2.dat", 0x4002146A, 0x0, 0x147E0}, {"char/nin21/motec2.dat", 0x40009344, 0x0, 0x4C7C},
    {"char/nin21/motpm2.dat", 0x40024B40, 0x0, 0x170B8}, {"char/nin23/model0.dat", 0x400176FC, 0x0, 0xFEA4},
    {"char/nin23/model1.dat", 0x4000F500, 0x0, 0x9D90}, {"char/nin21/motb2.dat", 0x4005781C, 0x0, 0x37718},
    {"char/nin21/motr2.dat", 0x400275C6, 0x0, 0x17994}, {"char/nin21/motf2.dat", 0x400537C0, 0x0, 0x3152C},
    {"char/nin21/motp2.dat", 0x4002D706, 0x0, 0x1C6C4}, {"char/nin21/motc2.dat", 0x400033A0, 0x0, 0x1CF4},
    {"char/nin21/mote2.dat", 0x40027F1A, 0x0, 0x18568}, {"char/nin21/moto.dat", 0x4004F674, 0x0, 0x2E878},
    {"char/nin21/motbs2.dat", 0x4003316A, 0x0, 0x1EF94}, {"char/nin21/motbt2.dat", 0x40044332, 0x0, 0x2A1E0},
    {"char/nin21/motrt2.dat", 0x40019734, 0x0, 0xEEC4}, {"char/nin21/motrm2.dat", 0x4000BA08, 0x0, 0x610C},
    {"char/nin21/motfm2.dat", 0x4002BD48, 0x0, 0x17EE0}, {"char/nin21/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8},
    {"char/nin21/motes2.dat", 0x4000D3D6, 0x0, 0x7510}, {"char/nin21/motem2.dat", 0x4002146A, 0x0, 0x147E0},
    {"char/nin21/motec2.dat", 0x40009344, 0x0, 0x4C7C}, {"char/nin21/motpm2.dat", 0x40024B40, 0x0, 0x170B8},
    {"char/nin24/model0.dat", 0x40011810, 0x0, 0xBAFC}, {"char/nin24/model1.dat", 0x4000BC80, 0x0, 0x7764},
    {"char/nin24/motb2.dat", 0x4004A62A, 0x0, 0x2FAF0}, {"char/nin24/motr2.dat", 0x40026690, 0x0, 0x1806C},
    {"char/nin24/motf2.dat", 0x4005235C, 0x0, 0x32A10}, {"char/nin24/motp2.dat", 0x4002B7DC, 0x0, 0x1BC18},
    {"char/nin24/motc2.dat", 0x40002620, 0x0, 0x1438}, {"char/nin24/mote2.dat", 0x4001E502, 0x0, 0x11E68},
    {"char/nin24/moto.dat", 0x4009C7A4, 0x0, 0x5C22C}, {"char/nin24/motbs2.dat", 0x4002E758, 0x0, 0x1C634},
    {"char/nin24/motbt2.dat", 0x4003AD24, 0x0, 0x25248}, {"char/nin24/motrt2.dat", 0x40019A3C, 0x0, 0xF4A0},
    {"char/nin24/motrm2.dat", 0x4000A1D0, 0x0, 0x51CC}, {"char/nin24/motfm2.dat", 0x4002D9DC, 0x0, 0x19D60},
    {"char/nin24/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8}, {"char/nin24/motes2.dat", 0x400094DA, 0x0, 0x4DC0},
    {"char/nin24/motem2.dat", 0x400141EC, 0x0, 0xC3D4}, {"char/nin24/motec2.dat", 0x4000BBA0, 0x0, 0x5C40},
    {"char/nin24/motpm2.dat", 0x40021A5E, 0x0, 0x153A4}, {"char/nin25/model0.dat", 0x40011810, 0x0, 0xBB1C},
    {"char/nin25/model1.dat", 0x4000BC80, 0x0, 0x7784}, {"char/nin24/motb2.dat", 0x4004A62A, 0x0, 0x2FAF0},
    {"char/nin24/motr2.dat", 0x40026690, 0x0, 0x1806C}, {"char/nin24/motf2.dat", 0x4005235C, 0x0, 0x32A10},
    {"char/nin24/motp2.dat", 0x4002B7DC, 0x0, 0x1BC18}, {"char/nin24/motc2.dat", 0x40002620, 0x0, 0x1438},
    {"char/nin24/mote2.dat", 0x4001E502, 0x0, 0x11E68}, {"char/nin24/moto.dat", 0x4009C7A4, 0x0, 0x5C22C},
    {"char/nin24/motbs2.dat", 0x4002E758, 0x0, 0x1C634}, {"char/nin24/motbt2.dat", 0x4003AD24, 0x0, 0x25248},
    {"char/nin24/motrt2.dat", 0x40019A3C, 0x0, 0xF4A0}, {"char/nin24/motrm2.dat", 0x4000A1D0, 0x0, 0x51CC},
    {"char/nin24/motfm2.dat", 0x4002D9DC, 0x0, 0x19D60}, {"char/nin24/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8},
    {"char/nin24/motes2.dat", 0x400094DA, 0x0, 0x4DC0}, {"char/nin24/motem2.dat", 0x400141EC, 0x0, 0xC3D4},
    {"char/nin24/motec2.dat", 0x4000BBA0, 0x0, 0x5C40}, {"char/nin24/motpm2.dat", 0x40021A5E, 0x0, 0x153A4},
    {"char/nin26/model0.dat", 0x40011810, 0x0, 0xBB48}, {"char/nin26/model1.dat", 0x4000BC80, 0x0, 0x77B0},
    {"char/nin24/motb2.dat", 0x4004A62A, 0x0, 0x2FAF0}, {"char/nin24/motr2.dat", 0x40026690, 0x0, 0x1806C},
    {"char/nin24/motf2.dat", 0x4005235C, 0x0, 0x32A10}, {"char/nin24/motp2.dat", 0x4002B7DC, 0x0, 0x1BC18},
    {"char/nin24/motc2.dat", 0x40002620, 0x0, 0x1438}, {"char/nin24/mote2.dat", 0x4001E502, 0x0, 0x11E68},
    {"char/nin24/moto.dat", 0x4009C7A4, 0x0, 0x5C22C}, {"char/nin24/motbs2.dat", 0x4002E758, 0x0, 0x1C634},
    {"char/nin24/motbt2.dat", 0x4003AD24, 0x0, 0x25248}, {"char/nin24/motrt2.dat", 0x40019A3C, 0x0, 0xF4A0},
    {"char/nin24/motrm2.dat", 0x4000A1D0, 0x0, 0x51CC}, {"char/nin24/motfm2.dat", 0x4002D9DC, 0x0, 0x19D60},
    {"char/nin24/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8}, {"char/nin24/motes2.dat", 0x400094DA, 0x0, 0x4DC0},
    {"char/nin24/motem2.dat", 0x400141EC, 0x0, 0xC3D4}, {"char/nin24/motec2.dat", 0x4000BBA0, 0x0, 0x5C40},
    {"char/nin24/motpm2.dat", 0x40021A5E, 0x0, 0x153A4}, {"char/nin27/model0.dat", 0x4001A71C, 0x0, 0x1128C},
    {"char/nin27/model1.dat", 0x4000F8E0, 0x0, 0x98E4}, {"char/nin27/motb2.dat", 0x4003D09E, 0x0, 0x26BD8},
    {"char/nin27/motr2.dat", 0x4001CB5C, 0x0, 0x11928}, {"char/nin27/motf2.dat", 0x4004BA56, 0x0, 0x2DB30},
    {"char/nin27/motp2.dat", 0x4001D9BA, 0x0, 0x1275C}, {"char/nin27/motc2.dat", 0x400034E6, 0x0, 0x1EF0},
    {"char/nin27/mote2.dat", 0x4001B818, 0x0, 0xF9C8}, {"char/nin27/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin27/motbs2.dat", 0x40024AC6, 0x0, 0x161B0}, {"char/nin27/motbt2.dat", 0x40033428, 0x0, 0x1FF84},
    {"char/nin27/motrt2.dat", 0x40013EBC, 0x0, 0xB978}, {"char/nin27/motrm2.dat", 0x4000A3F0, 0x0, 0x51B4},
    {"char/nin27/motfm2.dat", 0x40029748, 0x0, 0x17464}, {"char/nin27/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8},
    {"char/nin27/motes2.dat", 0x40008E8E, 0x0, 0x4890}, {"char/nin27/motem2.dat", 0x40010250, 0x0, 0x9470},
    {"char/nin27/motec2.dat", 0x4000C09C, 0x0, 0x613C}, {"char/nin27/motpm2.dat", 0x40018694, 0x0, 0xF23C},
    {"char/nin28/model0.dat", 0x4001CE58, 0x0, 0x132DC}, {"char/nin28/model1.dat", 0x4000FE80, 0x0, 0xA0FC},
    {"char/nin28/motb2.dat", 0x4003EA32, 0x0, 0x26D14}, {"char/nin28/motr2.dat", 0x4001ED2C, 0x0, 0x1206C},
    {"char/nin28/motf2.dat", 0x4004EA54, 0x0, 0x2EE10}, {"char/nin28/motp2.dat", 0x4002275A, 0x0, 0x15F34},
    {"char/nin28/motc2.dat", 0x40002CD0, 0x0, 0x1A20}, {"char/nin28/mote2.dat", 0x4001B8A4, 0x0, 0xF6B0},
    {"char/nin28/moto.dat", 0x4009C7A8, 0x0, 0x5C1DC}, {"char/nin28/motbs2.dat", 0x40028976, 0x0, 0x1830C},
    {"char/nin28/motbt2.dat", 0x40034E38, 0x0, 0x20530}, {"char/nin28/motrt2.dat", 0x4001A288, 0x0, 0xF210},
    {"char/nin28/motrm2.dat", 0x4000C7EC, 0x0, 0x690C}, {"char/nin28/motfm2.dat", 0x4002C5BA, 0x0, 0x18BD0},
    {"char/nin28/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8}, {"char/nin28/motes2.dat", 0x4000A3F8, 0x0, 0x55E4},
    {"char/nin28/motem2.dat", 0x40011862, 0x0, 0xA168}, {"char/nin28/motec2.dat", 0x4000A984, 0x0, 0x4FF8},
    {"char/nin28/motpm2.dat", 0x4001E0E0, 0x0, 0x12E10}, {"char/nin29/model0.dat", 0x400195B0, 0x0, 0xF9DC},
    {"char/nin29/model1.dat", 0x4000E380, 0x0, 0x961C}, {"char/nin13/motb2.dat", 0x40040FD2, 0x0, 0x288D0},
    {"char/nin13/motr2.dat", 0x40028B14, 0x0, 0x18898}, {"char/nin13/motf2.dat", 0x4004970A, 0x0, 0x2BF80},
    {"char/nin13/motp2.dat", 0x40027110, 0x0, 0x19234}, {"char/nin13/motc2.dat", 0x40003240, 0x0, 0x1D98},
    {"char/nin13/mote2.dat", 0x40021204, 0x0, 0x126C4}, {"char/nin13/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin13/motbs2.dat", 0x400287E0, 0x0, 0x185F8}, {"char/nin13/motbt2.dat", 0x40034F7C, 0x0, 0x208EC},
    {"char/nin13/motrt2.dat", 0x4001C13E, 0x0, 0x103B4}, {"char/nin13/motrm2.dat", 0x4000A8D6, 0x0, 0x53E4},
    {"char/nin13/motfm2.dat", 0x4002C7BC, 0x0, 0x18900}, {"char/nin13/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8},
    {"char/nin13/motes2.dat", 0x4000A956, 0x0, 0x58FC}, {"char/nin13/motem2.dat", 0x400153CE, 0x0, 0xBDEC},
    {"char/nin13/motec2.dat", 0x4000C1D4, 0x0, 0x6160}, {"char/nin13/motpm2.dat", 0x4001F8E2, 0x0, 0x13EC8},
    {"char/nin30/model0.dat", 0x400195B0, 0x0, 0xF9BC}, {"char/nin30/model1.dat", 0x4000E380, 0x0, 0x9368},
    {"char/nin13/motb2.dat", 0x40040FD2, 0x0, 0x288D0}, {"char/nin13/motr2.dat", 0x40028B14, 0x0, 0x18898},
    {"char/nin13/motf2.dat", 0x4004970A, 0x0, 0x2BF80}, {"char/nin13/motp2.dat", 0x40027110, 0x0, 0x19234},
    {"char/nin13/motc2.dat", 0x40003240, 0x0, 0x1D98}, {"char/nin13/mote2.dat", 0x40021204, 0x0, 0x126C4},
    {"char/nin13/moto.dat", 0x400336E0, 0x0, 0x1FB54}, {"char/nin13/motbs2.dat", 0x400287E0, 0x0, 0x185F8},
    {"char/nin13/motbt2.dat", 0x40034F7C, 0x0, 0x208EC}, {"char/nin13/motrt2.dat", 0x4001C13E, 0x0, 0x103B4},
    {"char/nin13/motrm2.dat", 0x4000A8D6, 0x0, 0x53E4}, {"char/nin13/motfm2.dat", 0x4002C7BC, 0x0, 0x18900},
    {"char/nin13/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8}, {"char/nin13/motes2.dat", 0x4000A956, 0x0, 0x58FC},
    {"char/nin13/motem2.dat", 0x400153CE, 0x0, 0xBDEC}, {"char/nin13/motec2.dat", 0x4000C1D4, 0x0, 0x6160},
    {"char/nin13/motpm2.dat", 0x4001F8E2, 0x0, 0x13EC8}, {"char/nin31/model0.dat", 0x400195B0, 0x0, 0xF8B0},
    {"char/nin31/model1.dat", 0x4000E380, 0x0, 0x926C}, {"char/nin13/motb2.dat", 0x40040FD2, 0x0, 0x288D0},
    {"char/nin13/motr2.dat", 0x40028B14, 0x0, 0x18898}, {"char/nin13/motf2.dat", 0x4004970A, 0x0, 0x2BF80},
    {"char/nin13/motp2.dat", 0x40027110, 0x0, 0x19234}, {"char/nin13/motc2.dat", 0x40003240, 0x0, 0x1D98},
    {"char/nin13/mote2.dat", 0x40021204, 0x0, 0x126C4}, {"char/nin13/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin13/motbs2.dat", 0x400287E0, 0x0, 0x185F8}, {"char/nin13/motbt2.dat", 0x40034F7C, 0x0, 0x208EC},
    {"char/nin13/motrt2.dat", 0x4001C13E, 0x0, 0x103B4}, {"char/nin13/motrm2.dat", 0x4000A8D6, 0x0, 0x53E4},
    {"char/nin13/motfm2.dat", 0x4002C7BC, 0x0, 0x18900}, {"char/nin13/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8},
    {"char/nin13/motes2.dat", 0x4000A956, 0x0, 0x58FC}, {"char/nin13/motem2.dat", 0x400153CE, 0x0, 0xBDEC},
    {"char/nin13/motec2.dat", 0x4000C1D4, 0x0, 0x6160}, {"char/nin13/motpm2.dat", 0x4001F8E2, 0x0, 0x13EC8},
    {"char/nin32/model0.dat", 0x400195B0, 0x0, 0xF8B0}, {"char/nin32/model1.dat", 0x4000E380, 0x0, 0x9278},
    {"char/nin13/motb2.dat", 0x40040FD2, 0x0, 0x288D0}, {"char/nin13/motr2.dat", 0x40028B14, 0x0, 0x18898},
    {"char/nin13/motf2.dat", 0x4004970A, 0x0, 0x2BF80}, {"char/nin13/motp2.dat", 0x40027110, 0x0, 0x19234},
    {"char/nin13/motc2.dat", 0x40003240, 0x0, 0x1D98}, {"char/nin13/mote2.dat", 0x40021204, 0x0, 0x126C4},
    {"char/nin13/moto.dat", 0x400336E0, 0x0, 0x1FB54}, {"char/nin13/motbs2.dat", 0x400287E0, 0x0, 0x185F8},
    {"char/nin13/motbt2.dat", 0x40034F7C, 0x0, 0x208EC}, {"char/nin13/motrt2.dat", 0x4001C13E, 0x0, 0x103B4},
    {"char/nin13/motrm2.dat", 0x4000A8D6, 0x0, 0x53E4}, {"char/nin13/motfm2.dat", 0x4002C7BC, 0x0, 0x18900},
    {"char/nin13/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8}, {"char/nin13/motes2.dat", 0x4000A956, 0x0, 0x58FC},
    {"char/nin13/motem2.dat", 0x400153CE, 0x0, 0xBDEC}, {"char/nin13/motec2.dat", 0x4000C1D4, 0x0, 0x6160},
    {"char/nin13/motpm2.dat", 0x4001F8E2, 0x0, 0x13EC8}, {"char/nin33/model0.dat", 0x400150EC, 0x0, 0xDD9C},
    {"char/nin33/model1.dat", 0x4000F000, 0x0, 0x9BF8}, {"char/nin33/motb2.dat", 0x40049E14, 0x0, 0x2EB64},
    {"char/nin33/motr2.dat", 0x40027298, 0x0, 0x1892C}, {"char/nin33/motf2.dat", 0x40054A5E, 0x0, 0x33308},
    {"char/nin33/motp2.dat", 0x4002A87C, 0x0, 0x1B6D8}, {"char/nin33/motc2.dat", 0x40002DC4, 0x0, 0x1B18},
    {"char/nin33/mote2.dat", 0x40023C14, 0x0, 0x15948}, {"char/nin33/moto.dat", 0x4009C7A8, 0x0, 0x5C1DC},
    {"char/nin33/motbs2.dat", 0x4002DC16, 0x0, 0x1BB68}, {"char/nin33/motbt2.dat", 0x4003BDA4, 0x0, 0x2535C},
    {"char/nin33/motrt2.dat", 0x4001D84C, 0x0, 0x11AE4}, {"char/nin33/motrm2.dat", 0x4000E09A, 0x0, 0x7BB0},
    {"char/nin33/motfm2.dat", 0x40031D66, 0x0, 0x1C7FC}, {"char/nin33/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8},
    {"char/nin33/motes2.dat", 0x4000B4A4, 0x0, 0x64C4}, {"char/nin33/motem2.dat", 0x40018C14, 0x0, 0xF6E0},
    {"char/nin33/motec2.dat", 0x4000B88E, 0x0, 0x5B3C}, {"char/nin33/motpm2.dat", 0x40022658, 0x0, 0x15F24},
    {"char/nin34/model0.dat", 0x400150EC, 0x0, 0xDD6C}, {"char/nin34/model1.dat", 0x4000F000, 0x0, 0x9BCC},
    {"char/nin33/motb2.dat", 0x40049E14, 0x0, 0x2EB64}, {"char/nin33/motr2.dat", 0x40027298, 0x0, 0x1892C},
    {"char/nin33/motf2.dat", 0x40054A5E, 0x0, 0x33308}, {"char/nin33/motp2.dat", 0x4002A87C, 0x0, 0x1B6D8},
    {"char/nin33/motc2.dat", 0x40002DC4, 0x0, 0x1B18}, {"char/nin33/mote2.dat", 0x40023C14, 0x0, 0x15948},
    {"char/nin33/moto.dat", 0x4009C7A8, 0x0, 0x5C1DC}, {"char/nin33/motbs2.dat", 0x4002DC16, 0x0, 0x1BB68},
    {"char/nin33/motbt2.dat", 0x4003BDA4, 0x0, 0x2535C}, {"char/nin33/motrt2.dat", 0x4001D84C, 0x0, 0x11AE4},
    {"char/nin33/motrm2.dat", 0x4000E09A, 0x0, 0x7BB0}, {"char/nin33/motfm2.dat", 0x40031D66, 0x0, 0x1C7FC},
    {"char/nin33/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8}, {"char/nin33/motes2.dat", 0x4000B4A4, 0x0, 0x64C4},
    {"char/nin33/motem2.dat", 0x40018C14, 0x0, 0xF6E0}, {"char/nin33/motec2.dat", 0x4000B88E, 0x0, 0x5B3C},
    {"char/nin33/motpm2.dat", 0x40022658, 0x0, 0x15F24}, {"char/nin35/model0.dat", 0x400150EC, 0x0, 0xDD50},
    {"char/nin35/model1.dat", 0x4000F000, 0x0, 0x9BAC}, {"char/nin33/motb2.dat", 0x40049E14, 0x0, 0x2EB64},
    {"char/nin33/motr2.dat", 0x40027298, 0x0, 0x1892C}, {"char/nin33/motf2.dat", 0x40054A5E, 0x0, 0x33308},
    {"char/nin33/motp2.dat", 0x4002A87C, 0x0, 0x1B6D8}, {"char/nin33/motc2.dat", 0x40002DC4, 0x0, 0x1B18},
    {"char/nin33/mote2.dat", 0x40023C14, 0x0, 0x15948}, {"char/nin33/moto.dat", 0x4009C7A8, 0x0, 0x5C1DC},
    {"char/nin33/motbs2.dat", 0x4002DC16, 0x0, 0x1BB68}, {"char/nin33/motbt2.dat", 0x4003BDA4, 0x0, 0x2535C},
    {"char/nin33/motrt2.dat", 0x4001D84C, 0x0, 0x11AE4}, {"char/nin33/motrm2.dat", 0x4000E09A, 0x0, 0x7BB0},
    {"char/nin33/motfm2.dat", 0x40031D66, 0x0, 0x1C7FC}, {"char/nin33/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8},
    {"char/nin33/motes2.dat", 0x4000B4A4, 0x0, 0x64C4}, {"char/nin33/motem2.dat", 0x40018C14, 0x0, 0xF6E0},
    {"char/nin33/motec2.dat", 0x4000B88E, 0x0, 0x5B3C}, {"char/nin33/motpm2.dat", 0x40022658, 0x0, 0x15F24},
    {"char/nin36/model0.dat", 0x400150EC, 0x0, 0xDE80}, {"char/nin36/model1.dat", 0x4000F000, 0x0, 0x9CDC},
    {"char/nin33/motb2.dat", 0x40049E14, 0x0, 0x2EB64}, {"char/nin33/motr2.dat", 0x40027298, 0x0, 0x1892C},
    {"char/nin33/motf2.dat", 0x40054A5E, 0x0, 0x33308}, {"char/nin33/motp2.dat", 0x4002A87C, 0x0, 0x1B6D8},
    {"char/nin33/motc2.dat", 0x40002DC4, 0x0, 0x1B18}, {"char/nin33/mote2.dat", 0x40023C14, 0x0, 0x15948},
    {"char/nin33/moto.dat", 0x4009C7A8, 0x0, 0x5C1DC}, {"char/nin33/motbs2.dat", 0x4002DC16, 0x0, 0x1BB68},
    {"char/nin33/motbt2.dat", 0x4003BDA4, 0x0, 0x2535C}, {"char/nin33/motrt2.dat", 0x4001D84C, 0x0, 0x11AE4},
    {"char/nin33/motrm2.dat", 0x4000E09A, 0x0, 0x7BB0}, {"char/nin33/motfm2.dat", 0x40031D66, 0x0, 0x1C7FC},
    {"char/nin33/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8}, {"char/nin33/motes2.dat", 0x4000B4A4, 0x0, 0x64C4},
    {"char/nin33/motem2.dat", 0x40018C14, 0x0, 0xF6E0}, {"char/nin33/motec2.dat", 0x4000B88E, 0x0, 0x5B3C},
    {"char/nin33/motpm2.dat", 0x40022658, 0x0, 0x15F24}, {"char/nin37/model0.dat", 0x40017300, 0x0, 0xF260},
    {"char/nin37/model1.dat", 0x40011D40, 0x0, 0xAED0}, {"char/nin37/motb2.dat", 0x4002D4D6, 0x0, 0x1C5A4},
    {"char/nin37/motr2.dat", 0x40015DEE, 0x0, 0xCFE0}, {"char/nin37/motf2.dat", 0x4002DB4C, 0x0, 0x18E78},
    {"char/nin37/motp2.dat", 0x40019FE2, 0x0, 0x10C58}, {"char/nin37/motc2.dat", 0x40003542, 0x0, 0x2188},
    {"char/nin37/mote2.dat", 0x400108C2, 0x0, 0x9730}, {"char/nin37/moto.dat", 0x4009C9B8, 0x0, 0x5C2D0},
    {"char/nin37/motbs2.dat", 0x4001E53A, 0x0, 0x116C8}, {"char/nin37/motbt2.dat", 0x4002241E, 0x0, 0x147A4},
    {"char/nin37/motrt2.dat", 0x40010B90, 0x0, 0x92D8}, {"char/nin37/motrm2.dat", 0x40008F30, 0x0, 0x453C},
    {"char/nin37/motfm2.dat", 0x4001D1D0, 0x0, 0xEAF8}, {"char/nin37/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8},
    {"char/nin37/motes2.dat", 0x40007FCC, 0x0, 0x3DD4}, {"char/nin37/motem2.dat", 0x4000F10A, 0x0, 0x88EC},
    {"char/nin37/motec2.dat", 0x40004D48, 0x0, 0x1A78}, {"char/nin37/motpm2.dat", 0x400188F6, 0x0, 0xFBD8},
    {"char/nin38/model0.dat", 0x400196C0, 0x0, 0x126C0}, {"char/nin38/model1.dat", 0x40010B60, 0x0, 0xB3F4},
    {"char/nin38/motb2.dat", 0x4005DC16, 0x0, 0x38DAC}, {"char/nin38/motr2.dat", 0x40034C00, 0x0, 0x1E9A4},
    {"char/nin38/motf2.dat", 0x4005E28A, 0x0, 0x34A04}, {"char/nin38/motp2.dat", 0x4003DFD2, 0x0, 0x25B94},
    {"char/nin38/motc2.dat", 0x40002920, 0x0, 0x15AC}, {"char/nin38/mote2.dat", 0x4002B206, 0x0, 0x18DDC},
    {"char/nin38/moto.dat", 0x4009C7A8, 0x0, 0x5C1DC}, {"char/nin38/motbs2.dat", 0x4003AFA0, 0x0, 0x22830},
    {"char/nin38/motbt2.dat", 0x4004973E, 0x0, 0x2BE60}, {"char/nin38/motrt2.dat", 0x40026E14, 0x0, 0x16560},
    {"char/nin38/motrm2.dat", 0x4000CAC8, 0x0, 0x66B4}, {"char/nin38/motfm2.dat", 0x4003594A, 0x0, 0x1C83C},
    {"char/nin38/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8}, {"char/nin38/motes2.dat", 0x4000DD92, 0x0, 0x7374},
    {"char/nin38/motem2.dat", 0x4001D630, 0x0, 0x111C0}, {"char/nin38/motec2.dat", 0x4000C4E0, 0x0, 0x5BBC},
    {"char/nin38/motpm2.dat", 0x40030736, 0x0, 0x1CAEC}, {"char/nin39/model0.dat", 0x4001F27C, 0x0, 0x154D0},
    {"char/nin39/model1.dat", 0x40012B00, 0x0, 0xC0A4}, {"char/nin39/motb2.dat", 0x4005DE26, 0x0, 0x3CDD8},
    {"char/nin39/motr2.dat", 0x4002C266, 0x0, 0x1B364}, {"char/nin39/motf2.dat", 0x40063F5E, 0x0, 0x3CA20},
    {"char/nin39/motp2.dat", 0x4003797E, 0x0, 0x2449C}, {"char/nin39/motc2.dat", 0x40004BAC, 0x0, 0x2FE0},
    {"char/nin39/mote2.dat", 0x4002A402, 0x0, 0x19B20}, {"char/nin39/moto.dat", 0x4009C7A8, 0x0, 0x5C1DC},
    {"char/nin39/motbs2.dat", 0x4003A81A, 0x0, 0x24E1C}, {"char/nin39/motbt2.dat", 0x4004C49A, 0x0, 0x30B2C},
    {"char/nin39/motrt2.dat", 0x4001FD10, 0x0, 0x12AC0}, {"char/nin39/motrm2.dat", 0x4000ECCE, 0x0, 0x80A8},
    {"char/nin39/motfm2.dat", 0x400358B2, 0x0, 0x1E9D4}, {"char/nin39/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8},
    {"char/nin39/motes2.dat", 0x4000D5B0, 0x0, 0x7A18}, {"char/nin39/motem2.dat", 0x4002085C, 0x0, 0x143AC},
    {"char/nin39/motec2.dat", 0x400093AE, 0x0, 0x474C}, {"char/nin39/motpm2.dat", 0x4002CE76, 0x0, 0x1D144},
    {"char/nin40/model0.dat", 0x400118C8, 0x0, 0xD7B8}, {"char/nin40/model1.dat", 0x40007C20, 0x0, 0x52E8},
    {"char/nin40/motb2.dat", 0x40041B10, 0x0, 0x28878}, {"char/nin40/motr2.dat", 0x4001D6F4, 0x0, 0x11378},
    {"char/nin40/motf2.dat", 0x40047664, 0x0, 0x2A50C}, {"char/nin40/motp2.dat", 0x40021F52, 0x0, 0x156BC},
    {"char/nin40/motc2.dat", 0x400030E2, 0x0, 0x1C34}, {"char/nin40/mote2.dat", 0x4001F04E, 0x0, 0x10888},
    {"char/nin40/moto.dat", 0x4009C7A8, 0x0, 0x5C1DC}, {"char/nin40/motbs2.dat", 0x400296AC, 0x0, 0x18924},
    {"char/nin40/motbt2.dat", 0x400347F4, 0x0, 0x1FD6C}, {"char/nin40/motrt2.dat", 0x40016ED4, 0x0, 0xD008},
    {"char/nin40/motrm2.dat", 0x4000AA58, 0x0, 0x5630}, {"char/nin40/motfm2.dat", 0x4002F530, 0x0, 0x1A5B8},
    {"char/nin40/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8}, {"char/nin40/motes2.dat", 0x4000AA9C, 0x0, 0x5AE0},
    {"char/nin40/motem2.dat", 0x40014292, 0x0, 0xAD54}, {"char/nin40/motec2.dat", 0x4000B870, 0x0, 0x5714},
    {"char/nin40/motpm2.dat", 0x4001AE56, 0x0, 0x10988}, {"char/nin41/model0.dat", 0x40018028, 0x0, 0x12FD0},
    {"char/nin41/model1.dat", 0x4000A1E0, 0x0, 0x6CCC}, {"char/nin41/motb2.dat", 0x4004F4A8, 0x0, 0x2FAF4},
    {"char/nin41/motr2.dat", 0x4002BCF0, 0x0, 0x192D4}, {"char/nin41/motf2.dat", 0x40059A24, 0x0, 0x3356C},
    {"char/nin41/motp2.dat", 0x4002CCBE, 0x0, 0x1AE14}, {"char/nin41/motc2.dat", 0x40004272, 0x0, 0x2470},
    {"char/nin41/mote2.dat", 0x4002BD44, 0x0, 0x17730}, {"char/nin41/moto.dat", 0x4009C7A8, 0x0, 0x5C1DC},
    {"char/nin41/motbs2.dat", 0x4002FBC0, 0x0, 0x1B5F0}, {"char/nin41/motbt2.dat", 0x40040DCE, 0x0, 0x269B0},
    {"char/nin41/motrt2.dat", 0x40020A8A, 0x0, 0x123B4}, {"char/nin41/motrm2.dat", 0x4000D5C8, 0x0, 0x7070},
    {"char/nin41/motfm2.dat", 0x4003A152, 0x0, 0x20228}, {"char/nin41/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8},
    {"char/nin41/motes2.dat", 0x4000E134, 0x0, 0x7100}, {"char/nin41/motem2.dat", 0x4001EFB4, 0x0, 0x10D88},
    {"char/nin41/motec2.dat", 0x4000D24C, 0x0, 0x6478}, {"char/nin41/motpm2.dat", 0x4002656A, 0x0, 0x17164},
    {"char/nin42/model0.dat", 0x40020FDC, 0x0, 0x17934}, {"char/nin42/model1.dat", 0x4000DFC0, 0x0, 0xA1F4},
    {"char/nin12/motb2.dat", 0x40049138, 0x0, 0x2F164}, {"char/nin12/motr2.dat", 0x40031382, 0x0, 0x1F8DC},
    {"char/nin12/motf2.dat", 0x4005105A, 0x0, 0x30DEC}, {"char/nin12/motp2.dat", 0x4002C1C6, 0x0, 0x1CC24},
    {"char/nin12/motc2.dat", 0x40002E32, 0x0, 0x1974}, {"char/nin12/mote2.dat", 0x4001E428, 0x0, 0x10C08},
    {"char/nin12/moto.dat", 0x400336E0, 0x0, 0x1FB54}, {"char/nin12/motbs2.dat", 0x4002E522, 0x0, 0x1CD78},
    {"char/nin12/motbt2.dat", 0x40034EF2, 0x0, 0x21214}, {"char/nin12/motrt2.dat", 0x40028D72, 0x0, 0x1A2BC},
    {"char/nin12/motrm2.dat", 0x40010670, 0x0, 0x94DC}, {"char/nin12/motfm2.dat", 0x4002E65C, 0x0, 0x1A2F0},
    {"char/nin12/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8}, {"char/nin12/motes2.dat", 0x400094FC, 0x0, 0x4898},
    {"char/nin12/motem2.dat", 0x4001327A, 0x0, 0xAE18}, {"char/nin12/motec2.dat", 0x4000C15C, 0x0, 0x5F60},
    {"char/nin12/motpm2.dat", 0x40026034, 0x0, 0x18D34}, {"char/nin43/model0.dat", 0x40022D3C, 0x0, 0x191A4},
    {"char/nin43/model1.dat", 0x4000FD40, 0x0, 0xB958}, {"char/nin20/motb2.dat", 0x4003B996, 0x0, 0x25900},
    {"char/nin20/motr2.dat", 0x400229E2, 0x0, 0x147AC}, {"char/nin20/motf2.dat", 0x4003FFC8, 0x0, 0x257DC},
    {"char/nin20/motp2.dat", 0x4002C386, 0x0, 0x1C328}, {"char/nin20/motc2.dat", 0x40002F9A, 0x0, 0x1A28},
    {"char/nin20/mote2.dat", 0x400182F0, 0x0, 0xCC9C}, {"char/nin20/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin20/motbs2.dat", 0x400213EE, 0x0, 0x13540}, {"char/nin20/motbt2.dat", 0x40031ECA, 0x0, 0x1F04C},
    {"char/nin20/motrt2.dat", 0x40018A28, 0x0, 0xE00C}, {"char/nin20/motrm2.dat", 0x4000BDEA, 0x0, 0x61F8},
    {"char/nin20/motfm2.dat", 0x40024616, 0x0, 0x130CC}, {"char/nin20/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8},
    {"char/nin20/motes2.dat", 0x40007B86, 0x0, 0x39A8}, {"char/nin20/motem2.dat", 0x4000F814, 0x0, 0x831C},
    {"char/nin20/motec2.dat", 0x4000A68C, 0x0, 0x4D44}, {"char/nin20/motpm2.dat", 0x400246A6, 0x0, 0x17314},
    {"char/nin44/model0.dat", 0x40016320, 0x0, 0xE1BC}, {"char/nin44/model1.dat", 0x40012C40, 0x0, 0xB6F0},
    {"char/nin16/motb2.dat", 0x400458E4, 0x0, 0x2A024}, {"char/nin16/motr2.dat", 0x40020E66, 0x0, 0x12FA0},
    {"char/nin16/motf2.dat", 0x4004D5C8, 0x0, 0x2C2FC}, {"char/nin16/motp2.dat", 0x40027776, 0x0, 0x171A4},
    {"char/nin16/motc2.dat", 0x400032EC, 0x0, 0x1EDC}, {"char/nin16/mote2.dat", 0x4001F090, 0x0, 0x107BC},
    {"char/nin16/moto.dat", 0x400336E0, 0x0, 0x1FB54}, {"char/nin16/motbs2.dat", 0x4002A278, 0x0, 0x180AC},
    {"char/nin16/motbt2.dat", 0x400360EE, 0x0, 0x2033C}, {"char/nin16/motrt2.dat", 0x4001768C, 0x0, 0xD18C},
    {"char/nin16/motrm2.dat", 0x4000BB46, 0x0, 0x5F20}, {"char/nin16/motfm2.dat", 0x4002C576, 0x0, 0x17A08},
    {"char/nin16/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8}, {"char/nin16/motes2.dat", 0x4000A4DC, 0x0, 0x5138},
    {"char/nin16/motem2.dat", 0x4001464C, 0x0, 0xB2AC}, {"char/nin16/motec2.dat", 0x4000A8BE, 0x0, 0x4E84},
    {"char/nin16/motpm2.dat", 0x40020A94, 0x0, 0x128C4}, {"char/nin45/model0.dat", 0x40016320, 0x0, 0xE198},
    {"char/nin45/model1.dat", 0x40012C40, 0x0, 0xB6CC}, {"char/nin16/motb2.dat", 0x400458E4, 0x0, 0x2A024},
    {"char/nin16/motr2.dat", 0x40020E66, 0x0, 0x12FA0}, {"char/nin16/motf2.dat", 0x4004D5C8, 0x0, 0x2C2FC},
    {"char/nin16/motp2.dat", 0x40027776, 0x0, 0x171A4}, {"char/nin16/motc2.dat", 0x400032EC, 0x0, 0x1EDC},
    {"char/nin16/mote2.dat", 0x4001F090, 0x0, 0x107BC}, {"char/nin16/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin16/motbs2.dat", 0x4002A278, 0x0, 0x180AC}, {"char/nin16/motbt2.dat", 0x400360EE, 0x0, 0x2033C},
    {"char/nin16/motrt2.dat", 0x4001768C, 0x0, 0xD18C}, {"char/nin16/motrm2.dat", 0x4000BB46, 0x0, 0x5F20},
    {"char/nin16/motfm2.dat", 0x4002C576, 0x0, 0x17A08}, {"char/nin16/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8},
    {"char/nin16/motes2.dat", 0x4000A4DC, 0x0, 0x5138}, {"char/nin16/motem2.dat", 0x4001464C, 0x0, 0xB2AC},
    {"char/nin16/motec2.dat", 0x4000A8BE, 0x0, 0x4E84}, {"char/nin16/motpm2.dat", 0x40020A94, 0x0, 0x128C4},
    {"char/nin46/model0.dat", 0x40016320, 0x0, 0xE1C4}, {"char/nin46/model1.dat", 0x40012C40, 0x0, 0xB6F8},
    {"char/nin16/motb2.dat", 0x400458E4, 0x0, 0x2A024}, {"char/nin16/motr2.dat", 0x40020E66, 0x0, 0x12FA0},
    {"char/nin16/motf2.dat", 0x4004D5C8, 0x0, 0x2C2FC}, {"char/nin16/motp2.dat", 0x40027776, 0x0, 0x171A4},
    {"char/nin16/motc2.dat", 0x400032EC, 0x0, 0x1EDC}, {"char/nin16/mote2.dat", 0x4001F090, 0x0, 0x107BC},
    {"char/nin16/moto.dat", 0x400336E0, 0x0, 0x1FB54}, {"char/nin16/motbs2.dat", 0x4002A278, 0x0, 0x180AC},
    {"char/nin16/motbt2.dat", 0x400360EE, 0x0, 0x2033C}, {"char/nin16/motrt2.dat", 0x4001768C, 0x0, 0xD18C},
    {"char/nin16/motrm2.dat", 0x4000BB46, 0x0, 0x5F20}, {"char/nin16/motfm2.dat", 0x4002C576, 0x0, 0x17A08},
    {"char/nin16/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8}, {"char/nin16/motes2.dat", 0x4000A4DC, 0x0, 0x5138},
    {"char/nin16/motem2.dat", 0x4001464C, 0x0, 0xB2AC}, {"char/nin16/motec2.dat", 0x4000A8BE, 0x0, 0x4E84},
    {"char/nin16/motpm2.dat", 0x40020A94, 0x0, 0x128C4}, {"char/nin47/model0.dat", 0x40016320, 0x0, 0xE0FC},
    {"char/nin47/model1.dat", 0x40012C40, 0x0, 0xB630}, {"char/nin16/motb2.dat", 0x400458E4, 0x0, 0x2A024},
    {"char/nin16/motr2.dat", 0x40020E66, 0x0, 0x12FA0}, {"char/nin16/motf2.dat", 0x4004D5C8, 0x0, 0x2C2FC},
    {"char/nin16/motp2.dat", 0x40027776, 0x0, 0x171A4}, {"char/nin16/motc2.dat", 0x400032EC, 0x0, 0x1EDC},
    {"char/nin16/mote2.dat", 0x4001F090, 0x0, 0x107BC}, {"char/nin16/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin16/motbs2.dat", 0x4002A278, 0x0, 0x180AC}, {"char/nin16/motbt2.dat", 0x400360EE, 0x0, 0x2033C},
    {"char/nin16/motrt2.dat", 0x4001768C, 0x0, 0xD18C}, {"char/nin16/motrm2.dat", 0x4000BB46, 0x0, 0x5F20},
    {"char/nin16/motfm2.dat", 0x4002C576, 0x0, 0x17A08}, {"char/nin16/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8},
    {"char/nin16/motes2.dat", 0x4000A4DC, 0x0, 0x5138}, {"char/nin16/motem2.dat", 0x4001464C, 0x0, 0xB2AC},
    {"char/nin16/motec2.dat", 0x4000A8BE, 0x0, 0x4E84}, {"char/nin16/motpm2.dat", 0x40020A94, 0x0, 0x128C4},
    {"char/nin48/model0.dat", 0x40012910, 0x0, 0xCF04}, {"char/nin48/model1.dat", 0x4000D4C0, 0x0, 0x89BC},
    {"char/nin48/motb2.dat", 0x4004692A, 0x0, 0x2BDA0}, {"char/nin48/motr2.dat", 0x40022760, 0x0, 0x14394},
    {"char/nin48/motf2.dat", 0x40058C62, 0x0, 0x35348}, {"char/nin48/motp2.dat", 0x4002A978, 0x0, 0x1AF6C},
    {"char/nin48/motc2.dat", 0x40002E50, 0x0, 0x1A40}, {"char/nin48/mote2.dat", 0x400219D2, 0x0, 0x12A88},
    {"char/nin48/moto.dat", 0x4004E820, 0x0, 0x2E358}, {"char/nin48/motbs2.dat", 0x4002CEBA, 0x0, 0x1AC10},
    {"char/nin48/motbt2.dat", 0x4003BFE6, 0x0, 0x24E48}, {"char/nin48/motrt2.dat", 0x4001A25C, 0x0, 0xEC58},
    {"char/nin48/motrm2.dat", 0x4000BEC4, 0x0, 0x616C}, {"char/nin48/motfm2.dat", 0x40033CDA, 0x0, 0x1D2AC},
    {"char/nin48/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8}, {"char/nin48/motes2.dat", 0x4000B02E, 0x0, 0x5BDC},
    {"char/nin48/motem2.dat", 0x400168E2, 0x0, 0xCD08}, {"char/nin48/motec2.dat", 0x4000C4EC, 0x0, 0x5E34},
    {"char/nin48/motpm2.dat", 0x4002346C, 0x0, 0x16348}, {"char/nin49/model0.dat", 0x40012910, 0x0, 0xCEDC},
    {"char/nin49/model1.dat", 0x4000D4C0, 0x0, 0x8994}, {"char/nin48/motb2.dat", 0x4004692A, 0x0, 0x2BDA0},
    {"char/nin48/motr2.dat", 0x40022760, 0x0, 0x14394}, {"char/nin48/motf2.dat", 0x40058C62, 0x0, 0x35348},
    {"char/nin48/motp2.dat", 0x4002A978, 0x0, 0x1AF6C}, {"char/nin48/motc2.dat", 0x40002E50, 0x0, 0x1A40},
    {"char/nin48/mote2.dat", 0x400219D2, 0x0, 0x12A88}, {"char/nin48/moto.dat", 0x4004E820, 0x0, 0x2E358},
    {"char/nin48/motbs2.dat", 0x4002CEBA, 0x0, 0x1AC10}, {"char/nin48/motbt2.dat", 0x4003BFE6, 0x0, 0x24E48},
    {"char/nin48/motrt2.dat", 0x4001A25C, 0x0, 0xEC58}, {"char/nin48/motrm2.dat", 0x4000BEC4, 0x0, 0x616C},
    {"char/nin48/motfm2.dat", 0x40033CDA, 0x0, 0x1D2AC}, {"char/nin48/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8},
    {"char/nin48/motes2.dat", 0x4000B02E, 0x0, 0x5BDC}, {"char/nin48/motem2.dat", 0x400168E2, 0x0, 0xCD08},
    {"char/nin48/motec2.dat", 0x4000C4EC, 0x0, 0x5E34}, {"char/nin48/motpm2.dat", 0x4002346C, 0x0, 0x16348},
    {"char/nin50/model0.dat", 0x40013AD4, 0x0, 0xDDC8}, {"char/nin50/model1.dat", 0x4000D7E0, 0x0, 0x8C38},
    {"char/nin48/motb2.dat", 0x4004692A, 0x0, 0x2BDA0}, {"char/nin48/motr2.dat", 0x40022760, 0x0, 0x14394},
    {"char/nin48/motf2.dat", 0x40058C62, 0x0, 0x35348}, {"char/nin48/motp2.dat", 0x4002A978, 0x0, 0x1AF6C},
    {"char/nin48/motc2.dat", 0x40002E50, 0x0, 0x1A40}, {"char/nin48/mote2.dat", 0x400219D2, 0x0, 0x12A88},
    {"char/nin48/moto.dat", 0x4004E820, 0x0, 0x2E358}, {"char/nin48/motbs2.dat", 0x4002CEBA, 0x0, 0x1AC10},
    {"char/nin48/motbt2.dat", 0x4003BFE6, 0x0, 0x24E48}, {"char/nin48/motrt2.dat", 0x4001A25C, 0x0, 0xEC58},
    {"char/nin48/motrm2.dat", 0x4000BEC4, 0x0, 0x616C}, {"char/nin48/motfm2.dat", 0x40033CDA, 0x0, 0x1D2AC},
    {"char/nin48/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8}, {"char/nin48/motes2.dat", 0x4000B02E, 0x0, 0x5BDC},
    {"char/nin48/motem2.dat", 0x400168E2, 0x0, 0xCD08}, {"char/nin48/motec2.dat", 0x4000C4EC, 0x0, 0x5E34},
    {"char/nin48/motpm2.dat", 0x4002346C, 0x0, 0x16348}, {"char/nin51/model0.dat", 0x40012910, 0x0, 0xCEB0},
    {"char/nin51/model1.dat", 0x4000D4C0, 0x0, 0x8968}, {"char/nin48/motb2.dat", 0x4004692A, 0x0, 0x2BDA0},
    {"char/nin48/motr2.dat", 0x40022760, 0x0, 0x14394}, {"char/nin48/motf2.dat", 0x40058C62, 0x0, 0x35348},
    {"char/nin48/motp2.dat", 0x4002A978, 0x0, 0x1AF6C}, {"char/nin48/motc2.dat", 0x40002E50, 0x0, 0x1A40},
    {"char/nin48/mote2.dat", 0x400219D2, 0x0, 0x12A88}, {"char/nin48/moto.dat", 0x4004E820, 0x0, 0x2E358},
    {"char/nin48/motbs2.dat", 0x4002CEBA, 0x0, 0x1AC10}, {"char/nin48/motbt2.dat", 0x4003BFE6, 0x0, 0x24E48},
    {"char/nin48/motrt2.dat", 0x4001A25C, 0x0, 0xEC58}, {"char/nin48/motrm2.dat", 0x4000BEC4, 0x0, 0x616C},
    {"char/nin48/motfm2.dat", 0x40033CDA, 0x0, 0x1D2AC}, {"char/nin48/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8},
    {"char/nin48/motes2.dat", 0x4000B02E, 0x0, 0x5BDC}, {"char/nin48/motem2.dat", 0x400168E2, 0x0, 0xCD08},
    {"char/nin48/motec2.dat", 0x4000C4EC, 0x0, 0x5E34}, {"char/nin48/motpm2.dat", 0x4002346C, 0x0, 0x16348},
    {"char/nin52/model0.dat", 0x4001AE1C, 0x0, 0x1157C}, {"char/nin52/model1.dat", 0x4000FFE0, 0x0, 0x9BD8},
    {"char/nin27/motb2.dat", 0x4003D09E, 0x0, 0x26BD8}, {"char/nin27/motr2.dat", 0x4001CB5C, 0x0, 0x11928},
    {"char/nin27/motf2.dat", 0x4004BA56, 0x0, 0x2DB30}, {"char/nin27/motp2.dat", 0x4001D9BA, 0x0, 0x1275C},
    {"char/nin27/motc2.dat", 0x400034E6, 0x0, 0x1EF0}, {"char/nin27/mote2.dat", 0x4001B818, 0x0, 0xF9C8},
    {"char/nin27/moto.dat", 0x400336E0, 0x0, 0x1FB54}, {"char/nin27/motbs2.dat", 0x40024AC6, 0x0, 0x161B0},
    {"char/nin27/motbt2.dat", 0x40033428, 0x0, 0x1FF84}, {"char/nin27/motrt2.dat", 0x40013EBC, 0x0, 0xB978},
    {"char/nin27/motrm2.dat", 0x4000A3F0, 0x0, 0x51B4}, {"char/nin27/motfm2.dat", 0x40029748, 0x0, 0x17464},
    {"char/nin27/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8}, {"char/nin27/motes2.dat", 0x40008E8E, 0x0, 0x4890},
    {"char/nin27/motem2.dat", 0x40010250, 0x0, 0x9470}, {"char/nin27/motec2.dat", 0x4000C09C, 0x0, 0x613C},
    {"char/nin27/motpm2.dat", 0x40018694, 0x0, 0xF23C}, {"char/nin53/model0.dat", 0x4001A71C, 0x0, 0x112D0},
    {"char/nin53/model1.dat", 0x4000F8E0, 0x0, 0x9924}, {"char/nin27/motb2.dat", 0x4003D09E, 0x0, 0x26BD8},
    {"char/nin27/motr2.dat", 0x4001CB5C, 0x0, 0x11928}, {"char/nin27/motf2.dat", 0x4004BA56, 0x0, 0x2DB30},
    {"char/nin27/motp2.dat", 0x4001D9BA, 0x0, 0x1275C}, {"char/nin27/motc2.dat", 0x400034E6, 0x0, 0x1EF0},
    {"char/nin27/mote2.dat", 0x4001B818, 0x0, 0xF9C8}, {"char/nin27/moto.dat", 0x400336E0, 0x0, 0x1FB54},
    {"char/nin27/motbs2.dat", 0x40024AC6, 0x0, 0x161B0}, {"char/nin27/motbt2.dat", 0x40033428, 0x0, 0x1FF84},
    {"char/nin27/motrt2.dat", 0x40013EBC, 0x0, 0xB978}, {"char/nin27/motrm2.dat", 0x4000A3F0, 0x0, 0x51B4},
    {"char/nin27/motfm2.dat", 0x40029748, 0x0, 0x17464}, {"char/nin27/motrtoy2.dat", 0x40003D7E, 0x0, 0xAE8},
    {"char/nin27/motes2.dat", 0x40008E8E, 0x0, 0x4890}, {"char/nin27/motem2.dat", 0x40010250, 0x0, 0x9470},
    {"char/nin27/motec2.dat", 0x4000C09C, 0x0, 0x613C}, {"char/nin27/motpm2.dat", 0x40018694, 0x0, 0xF23C},
};

static u32 DebugBallFiles[8] = {
    0x40B, 0x40093FF8, 0xE581000, 0x5F484, 0x40B, 0x40095BB8, 0xE5E0800, 0x6053C,
};

static u32 HandPoseEventSetFiles_debug[120] = {
    0x40B, 0x400004D8, 0xE66C800, 0x340, 0x40B, 0x40000314, 0xE66D000, 0x204,
    0x40B, 0x40000280, 0xE66D800, 0x1C4, 0x40B, 0x4000026C, 0xE66E000, 0x1A0,
    0x40B, 0x40000464, 0xE66E800, 0x2F0, 0x40B, 0x40000544, 0xE66F000, 0x364,
    0x40B, 0x400002E4, 0xE66F800, 0x1D4, 0x40B, 0x40000418, 0xE670000, 0x2C8,
    0x40B, 0x40000444, 0xE670800, 0x2CC, 0x40B, 0x400003D8, 0xE671000, 0x278,
    0x40B, 0x40000630, 0xE671800, 0x40C, 0x40B, 0x400001CC, 0xE672000, 0x130,
    0x40B, 0x40000448, 0xE672800, 0x2AC, 0x40B, 0x40000390, 0xE673000, 0x258,
    0x40B, 0x40000394, 0xE673800, 0x248, 0x40B, 0x400004F8, 0xE674000, 0x304,
    0x40B, 0x400003D8, 0xE674800, 0x220, 0x40B, 0x4000033C, 0xE675000, 0x238,
    0x40B, 0x40000444, 0xE675800, 0x2AC, 0x40B, 0x400001B0, 0xE676000, 0x110,
    0x40B, 0x400002C0, 0xE676800, 0x1D4, 0x40B, 0x40000168, 0xE677000, 0xE4,
    0x40B, 0x400000D8, 0xE677800, 0x58, 0x40B, 0x40000284, 0xE678000, 0x178,
    0x40B, 0x400000C8, 0xE678800, 0x50, 0x40B, 0x4000019C, 0xE679000, 0x100,
    0x40B, 0x40000278, 0xE679800, 0x19C, 0x40B, 0x4000021C, 0xE67A000, 0x164,
    0x40B, 0x400000C8, 0xE67A800, 0x4C, 0x40B, 0x40000145, 0xE67B000, 0xA4,
};

static u32 DebugCharacterHandFiles[216] = {
    0x40B, 0x40014D14, 0x18941800, 0xD8F8, 0x40B, 0x40015488, 0x1894F800, 0xD818,
    0x40B, 0x40018270, 0x1895D800, 0xF8DC, 0x40B, 0x4001623C, 0x1896D800, 0xE490,
    0x40B, 0x40011E6C, 0x1897C000, 0xA778, 0x40B, 0x40011FD8, 0x18986800, 0xA850,
    0x40B, 0x4001350C, 0x18991800, 0xC468, 0x40B, 0x40013EEC, 0x1899E000, 0xBEAC,
    0x40B, 0x40013F68, 0x189AA000, 0xBE84, 0x40B, 0x40017428, 0x189B6000, 0xE704,
    0x40B, 0x40013954, 0x189C4800, 0xC884, 0x40B, 0x400131A8, 0x189D1800, 0xC35C,
    0x40B, 0x400109FC, 0x189DE000, 0xAA9C, 0x40B, 0x40013C48, 0x189E9000, 0xBA28,
    0x40B, 0x4000836C, 0x189F5000, 0x6454, 0x40B, 0x40013C0C, 0x189FB800, 0xBEE4,
    0x40B, 0x40007038, 0x18A07800, 0x4CAC, 0x40B, 0x400149F0, 0x18A0C800, 0xD820,
    0x40B, 0x40008430, 0x18A1A800, 0x5FE0, 0x40B, 0x40013938, 0x18A20800, 0xB038,
    0x40B, 0x4001098C, 0x18A2C000, 0xAA3C, 0x40B, 0x40010C64, 0x18A37000, 0xA444,
    0x40B, 0x40010C64, 0x18A37000, 0xA444, 0x40B, 0x40010C64, 0x18A37000, 0xA444,
    0x40B, 0x4000EDB8, 0x18A41800, 0x90C0, 0x40B, 0x4000EDB8, 0x18A41800, 0x90C0,
    0x40B, 0x4000EDB8, 0x18A41800, 0x90C0, 0x40B, 0x400143A8, 0x18A4B000, 0xC2A4,
    0x40B, 0x400152A0, 0x18A57800, 0xDE78, 0x40B, 0x40013C48, 0x189E9000, 0xBA28,
    0x40B, 0x40013C48, 0x189E9000, 0xBA28, 0x40B, 0x40013C48, 0x189E9000, 0xBA28,
    0x40B, 0x40013C48, 0x189E9000, 0xBA28, 0x40B, 0x400144D8, 0x18A65800, 0xCCBC,
    0x40B, 0x400144D8, 0x18A65800, 0xCCBC, 0x40B, 0x400144D8, 0x18A65800, 0xCCBC,
    0x40B, 0x400144D8, 0x18A65800, 0xCCBC, 0x40B, 0x4000B7DC, 0x18A72800, 0x6E3C,
    0x40B, 0x40001918, 0x18A79800, 0xCF4, 0x40B, 0x400148FC, 0x18A7A800, 0xD9D8,
    0x40B, 0x400049BC, 0x18A88800, 0x3804, 0x40B, 0x4000495C, 0x18A8C800, 0x37C8,
    0x40B, 0x400109FC, 0x189DE000, 0xAA9C, 0x40B, 0x4001098C, 0x18A2C000, 0xAA3C,
    0x40B, 0x40007038, 0x18A07800, 0x4CAC, 0x40B, 0x40007038, 0x18A07800, 0x4CAC,
    0x40B, 0x40007038, 0x18A07800, 0x4CAC, 0x40B, 0x40007038, 0x18A07800, 0x4CAC,
    0x40B, 0x40011210, 0x18A90000, 0xADD4, 0x40B, 0x40011210, 0x18A90000, 0xADD4,
    0x40B, 0x40011210, 0x18A90000, 0xADD4, 0x40B, 0x40011210, 0x18A90000, 0xADD4,
    0x40B, 0x40010908, 0x18A9B000, 0xA7D4, 0x40B, 0x4000EDA8, 0x18AA5800, 0x9B8C,
};

static u8 lbl_1_data_A938[8] = {
    0x4B, 0x2D, 0x00, 0x3F, 0x3D, 0x69, 0x00, 0x00,
};

static void * lbl_1_data_A940[14] = {
    (void *)0x0, (void *)0x200, (void *)0x18AAF800, (void *)0x15450, (void *)0x40B, (void *)0x400204C0, (void *)0x191C1800, (void *)0x13FCC,
    (void *)0x3030000, (void *)0x0, (void *)0x0, (void *)0x0, "HAND", "GLOVE",
};

static struct {
    s16 a[56];
    void *p0;
    s16 b[26];
    void *p1;
    s16 c[24];
} lbl_1_data_A978 = {
    {
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23,
    24, 25, 26, 27, 28, 29, 30, 31,
    32, 33, 34, 35, 36, 37, 38, 39,
    40, 41, 42, 43, 44, 45, 46, 47,
    48, 49, 50, 51, 52, 53, 0, 0,
    },
    (void *)fn_1_11714,
    {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0,
    },
    (void *)fn_1_11714,
    {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    },
};
#define DBG_A978 ((s16 *)&lbl_1_data_A978)

static DbgDrawRow lbl_1_data_AA54[2] = {
    {2, (void *)fn_1_1125C},
    {2, (void *)fn_1_1125C},
};

static DbgDrawRow lbl_1_data_AAC4[2] = {
    {2, (void *)fn_1_10CEC},
    {2, (void *)fn_1_10CEC},
};

static DbgDrawRow lbl_1_data_AB34[2] = {
    {2, (void *)fn_1_C5AC},
    {2, (void *)fn_1_C5AC},
};

static f32 lbl_1_data_ABA4 = 0.5f;

static void * lbl_1_data_ABA8[58] = {
    (void *)0x1000000, "MARIO CRAY", "MARIO GRASS", (void *)fn_1_15170, (void *)fn_1_14FB8, (void *)fn_1_165E0, (void *)fn_1_15CE0, (void *)fn_1_15760,
    (void *)fn_1_1540C, (void *)fn_1_151F8, (void *)fn_1_E098, (void *)fn_1_EA20, (void *)fn_1_106C4, (void *)fn_1_10458, (void *)fn_1_10044, (void *)fn_1_FB98,
    (void *)fn_1_F6E4, (void *)fn_1_F37C, (void *)fn_1_F2F8, (void *)fn_1_F0D0, (void *)fn_1_F040, (void *)0x43414D45, (void *)0x52410000, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x4D4F4445, (void *)0x4C000000, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x2, (void *)fn_1_17954, (void *)0x2,
    (void *)fn_1_17954, (void *)0xC0000000,
};

static void * lbl_1_data_AC90[31] = {
    (void *)0xFF0A0000, "raw", "reduct", (void *)0x2, (void *)fn_1_12F18, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x2, (void *)fn_1_12F18, (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0,
};

static f32 lbl_1_data_AD0C[3] = {
    0.0f, 0.0f, 0.0f,
};

static f32 lbl_1_data_AD18[3] = {
    0.0f, 1.0f, 0.0f,
};

static f32 lbl_1_data_AD24[3] = {
    0.0f, 1.0f, 0.0f,
};

static f32 lbl_1_data_AD30[24] = {
    -2.5f, -1.0f, 9.5f, -2.5f, -1.0f, 10.5f, -1.5f, -1.0f,
    10.5f, -1.5f, -1.0f, 9.5f, -2.5f, 0.0f, 9.5f, -2.5f,
    0.0f, 10.5f, -1.5f, 0.0f, 10.5f, -1.5f, 0.0f, 9.5f,
};

static u8 lbl_1_data_AD90[6][4] = {
    0x00, 0x03, 0x02, 0x01,
    0x04, 0x05, 0x06, 0x07,
    0x00, 0x04, 0x07, 0x03,
    0x03, 0x07, 0x06, 0x02,
    0x02, 0x06, 0x05, 0x01,
    0x01, 0x05, 0x04, 0x00,
};

static u32 lbl_1_data_ADA8[6] = {
    0xFF0000FF, 0xFF00FF, 0xFFFF, 0xFFFF00FF, 0xFF00FFFF, 0xFFFFFF,
};

static f32 lbl_1_data_ADC0 = -1.0f;

static u32 lbl_1_data_ADC4[7] = {
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
};

static u32 teamStarModelFileDescriptorDebug[4] = {
    0x40B, 0x40046100, 0xE641000, 0x24B48,
};

static u32 lbl_1_data_ADF0 = 0xFF000080;
static s32 lbl_1_data_ADF4 = 0x400;
static f32 lbl_1_data_ADF8 = 1.0f;
static u32 lbl_1_data_ADFC = 0x3C;
static f32 lbl_1_data_AE00 = 0.08f;
static Vec lbl_1_data_AE04 = {0.0f, 0.0f, 10.0f};
static s16 lbl_1_data_AE10 = 0x200;
static s16 lbl_1_data_AE12 = 0xBF8;
static Vec lbl_1_data_AE14 = {0.0f, -1.0f, 0.0f};

static u32 lbl_1_data_AE20[294] = {
    0x80928000, 0x80008000, 0x4000, 0x40000D62, 0x6D45, 0x4000295D, 0x4DFD, 0x14F1295D,
    0x1B60, 0x2564295D, 0x1B60, 0x5A9B295D, 0x4DFD, 0x6B0E295D, 0x649F, 0x256456A2,
    0x3202, 0x14F156A2, 0x12BA, 0x400056A2, 0x3202, 0x6B0E56A2, 0x649F, 0x5A9B56A2,
    0x4000, 0x4000729D, 0x5A9B, 0x400014F1, 0x4839, 0x26B114F1, 0x2A78, 0x305C14F1,
    0x2A78, 0x4FA314F1, 0x4839, 0x594E14F1, 0x62D5, 0x26B12564, 0x32B2, 0x170D2564,
    0x14F1, 0x40002564, 0x32B2, 0x68F22564, 0x62D5, 0x594E2564, 0x7023, 0x305C4000,
    0x4000, 0xD624000, 0xFDC, 0x305C4000, 0x223F, 0x68F24000, 0x5DC0, 0x68F24000,
    0x7023, 0x4FA34000, 0x5DC0, 0x170D4000, 0x223F, 0x170D4000, 0xFDC, 0x4FA34000,
    0x4000, 0x729D4000, 0x4D4D, 0x170D5A9B, 0x1D2A, 0x26B15A9B, 0x1D2A, 0x594E5A9B,
    0x4D4D, 0x68F25A9B, 0x6B0E, 0x40005A9B, 0x5587, 0x305C6B0E, 0x37C6, 0x26B16B0E,
    0x2564, 0x40006B0E, 0x37C6, 0x594E6B0E, 0x5587, 0x4FA36B0E, 0x14000, 0x40000000,
    0x1793E, 0x40002360, 0x151B0, 0x98E2360, 0x111B0, 0x1E5A2360, 0x111B0, 0x61A52360,
    0x151B0, 0x76712360, 0x16E4F, 0x1E5A5C9F, 0x12E4F, 0x98E5C9F, 0x106C1, 0x40005C9F,
    0x12E4F, 0x76715C9F, 0x16E4F, 0x61A55C9F, 0x14000, 0x40008000, 0x15716, 0x4000044F,
    0x16B10, 0x400010A7, 0x14722, 0x2A0B044F, 0x14D4E, 0x170B10A7, 0x12D52, 0x326E044F,
    0x11D28, 0x26AF10A7, 0x12D52, 0x4D91044F, 0x11D28, 0x595010A7, 0x14722, 0x55F4044F,
    0x14D4E, 0x68F410A7, 0x17232, 0x2A0B1EEC, 0x16464, 0x170B1EEC, 0x13AA1, 0x9791EEC,
    0x1244B, 0x10BB1EEC, 0x10A7B, 0x34411EEC, 0x10A7B, 0x4BBE1EEC, 0x1244B, 0x6F441EEC,
    0x13AA1, 0x76861EEC, 0x16464, 0x68F41EEC, 0x17232, 0x55F41EEC, 0x17DBD, 0x326E3602,
    0x179ED, 0x26AF49FD, 0x1462C, 0x1163602, 0x139D3, 0x11649FD, 0x10612, 0x26AF3602,
    0x10242, 0x326E49FD, 0x11606, 0x6F443602, 0x12003, 0x768649FD, 0x15FFC, 0x76863602,
    0x169F9, 0x6F4449FD, 0x17DBD, 0x4D913602, 0x179ED, 0x595049FD, 0x15FFC, 0x9793602,
    0x169F9, 0x10BB49FD, 0x11606, 0x10BB3602, 0x12003, 0x97949FD, 0x10612, 0x59503602,
    0x10242, 0x4D9149FD, 0x1462C, 0x7EE93602, 0x139D3, 0x7EE949FD, 0x15BB4, 0x10BB6113,
    0x1455E, 0x9796113, 0x11B9B, 0x170B6113, 0x10DCD, 0x2A0B6113, 0x10DCD, 0x55F46113,
    0x11B9B, 0x68F46113, 0x1455E, 0x76866113, 0x15BB4, 0x6F446113, 0x17584, 0x4BBE6113,
    0x17584, 0x34416113, 0x152AD, 0x326E7BB0, 0x162D7, 0x26AF6F58, 0x138DD, 0x2A0B7BB0,
    0x132B1, 0x170B6F58, 0x128E9, 0x40007BB0, 0x114EF, 0x40006F58, 0x138DD, 0x55F47BB0,
    0x132B1, 0x68F46F58, 0x152AD, 0x4D917BB0, 0x162D7, 0x59506F58, 0x15EB0, 0x29B40C73,
    0x13447, 0x1BEC0C73, 0x11A11, 0x40000C73, 0x13447, 0x64130C73, 0x15EB0, 0x564B0C73,
    0x17F11, 0x40004AE0, 0x1537D, 0x4044AE0, 0x10CF9, 0x1AED4AE0, 0x10CF9, 0x65124AE0,
    0x1537D, 0x7BFB4AE0, 0x17306, 0x1AED351F, 0x12C82, 0x404351F, 0x100EE, 0x4000351F,
    0x12C82, 0x7BFB351F, 0x17306, 0x6512351F, 0x14BB8, 0x1BEC738C, 0x1214F, 0x29B4738C,
    0x1214F, 0x564B738C, 0x14BB8, 0x6413738C, 0x165EE, 0x4000738C, 0x24000, 0x4000186A,
    0x26367, 0x40002E4C, 0x24AF0, 0x1E532E4C, 0x2235B, 0x2B302E4C, 0x2235B, 0x54CF2E4C,
    0x24AF0, 0x61AC2E4C, 0x25CA4, 0x2B3051B3, 0x2350F, 0x1E5351B3, 0x21C98, 0x400051B3,
    0x2350F, 0x61AC51B3, 0x25CA4, 0x54CF51B3, 0x24000, 0x40006795,
};

static u32 lbl_1_data_B2B8[162] = {
    0x80508000, 0x80008000, 0x5DAB, 0x53193E5A, 0x8000, 0x386E3E5A, 0x5772, 0x28ED3E5A,
    0x48CC, 0x3E5A, 0x2D7F, 0x21DA3E5A, 0x223, 0x23353E5A, 0x19CA, 0x47A83E5A,
    0xDAC, 0x71653E5A, 0x3791, 0x66183E5A, 0x5B76, 0x7E833E5A, 0x17D1, 0x22873E5A,
    0xDF6, 0x356D3E5A, 0x5021, 0x14753E5A, 0x3B26, 0x10EB3E5A, 0x6ED5, 0x45C23E5A,
    0x6BBA, 0x30AE3E5A, 0x4982, 0x724E3E5A, 0x5C92, 0x68CD3E5A, 0x13BA, 0x5C863E5A,
    0x229E, 0x6BBD3E5A, 0x22AA, 0x222F3E5A, 0xCFC, 0x22DD3E5A, 0x13E1, 0x3E8A3E5A,
    0x80C, 0x2C523E5A, 0x53C9, 0x1EB13E5A, 0x4C75, 0xA3C3E5A, 0x3451, 0x19643E5A,
    0x41F7, 0x8753E5A, 0x6640, 0x4C6F3E5A, 0x776A, 0x3F183E5A, 0x6198, 0x2CCC3E5A,
    0x75DD, 0x348C3E5A, 0x4089, 0x6C313E5A, 0x527A, 0x78673E5A, 0x5D1D, 0x5DF43E5A,
    0x5C04, 0x73A83E5A, 0x10B3, 0x66F63E5A, 0x16C4, 0x52173E5A, 0x2D16, 0x68E93E5A,
    0x1826, 0x6E913E5A, 0x150ED, 0x4C343E5A, 0x165A1, 0x3C1F3E5A, 0x14D2D, 0x32C33E5A,
    0x14457, 0x1A143E5A, 0x133DF, 0x2E813E5A, 0x119B7, 0x2F513E5A, 0x127FC, 0x454E3E5A,
    0x120AD, 0x5E7A3E5A, 0x139F0, 0x57A83E5A, 0x14F98, 0x66653E5A, 0x126CC, 0x2EE83E5A,
    0x120DB, 0x3A4E3E5A, 0x148C1, 0x266C3E5A, 0x13C1A, 0x244B3E5A, 0x15B48, 0x44293E5A,
    0x15966, 0x37713E5A, 0x144C3, 0x5F053E5A, 0x15043, 0x594C3E5A, 0x12453, 0x51E43E5A,
    0x12D4F, 0x5B123E5A, 0x12D54, 0x2EB43E5A, 0x12042, 0x2F1D3E5A, 0x1246A, 0x3FCE3E5A,
    0x11D49, 0x34D13E5A, 0x14AF8, 0x2C993E5A, 0x1468C, 0x20423E5A, 0x137FC, 0x29653E5A,
    0x14037, 0x1F2E3E5A, 0x1561B, 0x48303E5A, 0x16073, 0x40233E5A, 0x1534A, 0x351A3E5A,
    0x15F85, 0x39C83E5A, 0x13F59, 0x5B573E5A, 0x14A2F, 0x62B63E5A, 0x15098, 0x52C13E5A,
    0x14FED, 0x5FD73E5A, 0x1227F, 0x58303E5A, 0x12628, 0x4B973E5A, 0x133A1, 0x595D3E5A,
    0x126FD, 0x5CC83E5A,
};

static u32 lbl_1_data_B540[162] = {
    0x80508000, 0x80008000, 0x6120, 0x38283C7E, 0x69EF, 0xF413C7E, 0x4273, 0x1CE83C7E,
    0x1E50, 0x7CA3C7E, 0x1F20, 0x31A53C7E, 0x0, 0x4D7A3C7E, 0x27FC, 0x59B83C7E,
    0x38E2, 0x7FFF3C7E, 0x50C6, 0x5DBE3C7E, 0x7A5A, 0x598A3C7E, 0xF90, 0x3F913C7E,
    0x13FE, 0x539A3C7E, 0x3060, 0x12593C7E, 0x1EB8, 0x1CB93C7E, 0x6589, 0x23B43C7E,
    0x562F, 0x16133C7E, 0x6591, 0x5BA43C7E, 0x6DBF, 0x48DA3C7E, 0x306E, 0x6CDC3C7E,
    0x44D4, 0x6EDD3C7E, 0x1758, 0x389B3C7E, 0x7C8, 0x46843C7E, 0x1DFC, 0x56A83C7E,
    0x9FD, 0x508A3C7E, 0x3968, 0x17A23C7E, 0x2758, 0xD133C7E, 0x1EEC, 0x272F3C7E,
    0x1E84, 0x12403C7E, 0x6353, 0x2DEE3C7E, 0x67BC, 0x197A3C7E, 0x4C50, 0x197D3C7E,
    0x600F, 0x12AB3C7E, 0x5B2C, 0x5CB03C7E, 0x6FF7, 0x5A983C7E, 0x6770, 0x40813C7E,
    0x740E, 0x51313C7E, 0x34A8, 0x766F3C7E, 0x2C36, 0x634B3C7E, 0x4ACC, 0x664E3C7E,
    0x3EDA, 0x77703C7E, 0x15377, 0x3AF43C7E, 0x158C7, 0x22493C7E, 0x140F4, 0x2A873C7E,
    0x12B2B, 0x1DCB3C7E, 0x12BA8, 0x37093C7E, 0x118DF, 0x47D13C7E, 0x130FF, 0x4F343C7E,
    0x13B30, 0x664B3C7E, 0x1499A, 0x51A13C7E, 0x162AD, 0x4F193C7E, 0x12244, 0x3F6D3C7E,
    0x124EF, 0x4B833C7E, 0x1360E, 0x24273C7E, 0x12B69, 0x2A693C7E, 0x1561F, 0x2EA03C7E,
    0x14CDE, 0x26683C7E, 0x15625, 0x505B3C7E, 0x15B13, 0x45083C7E, 0x13619, 0x5ABE3C7E,
    0x14265, 0x5BF63C7E, 0x126F6, 0x3B3B3C7E, 0x11D91, 0x439F3C7E, 0x12AF7, 0x4D5B3C7E,
    0x11EE7, 0x49AA3C7E, 0x13B82, 0x27563C7E, 0x1309C, 0x20F93C7E, 0x12B88, 0x30B83C7E,
    0x12B49, 0x241A3C7E, 0x154C9, 0x34C93C7E, 0x15772, 0x28743C7E, 0x146E9, 0x28773C7E,
    0x152D3, 0x24583C7E, 0x14FDE, 0x50FF3C7E, 0x15C69, 0x4FBA3C7E, 0x15743, 0x3FFE3C7E,
    0x15EE0, 0x4A0F3C7E, 0x138A3, 0x60853C7E, 0x1338C, 0x54FB3C7E, 0x145FE, 0x56CB3C7E,
    0x13EC9, 0x61203C7E,
};

static u32 lbl_1_data_B7C8[162] = {
    0x80508000, 0x80008000, 0x5C78, 0x29EB3AC7, 0x56B2, 0x3AC7, 0x35E3, 0x1AA43AC7,
    0xC40, 0x13133AC7, 0x1B81, 0x3A903AC7, 0x78B, 0x5FC63AC7, 0x31C6, 0x5D953AC7,
    0x4F13, 0x7C1D3AC7, 0x59EF, 0x534B3AC7, 0x8000, 0x40EC3AC7, 0x1185, 0x4D2C3AC7,
    0x1CA9, 0x5EAF3AC7, 0x2110, 0x16DA3AC7, 0x13DF, 0x26D13AC7, 0x5994, 0x14F63AC7,
    0x4649, 0xD523AC7, 0x6CF7, 0x4A1C3AC7, 0x6E3B, 0x356D3AC7, 0x406D, 0x6CD93AC7,
    0x5481, 0x67B53AC7, 0x1682, 0x43DE3AC7, 0xC88, 0x567B3AC7, 0x2738, 0x5E223AC7,
    0x121A, 0x5F393AC7, 0x2B7B, 0x18BE3AC7, 0x16A8, 0x14F63AC7, 0x17AF, 0x30B23AC7,
    0x1010, 0x1CF13AC7, 0x5B06, 0x1F723AC7, 0x5824, 0xA7B3AC7, 0x3E18, 0x13FB3AC7,
    0x4E7E, 0x6A93AC7, 0x6372, 0x4EB23AC7, 0x767A, 0x45823AC7, 0x655B, 0x2FAC3AC7,
    0x771D, 0x3B2B3AC7, 0x47C1, 0x747B3AC7, 0x391B, 0x65373AC7, 0x5737, 0x5D7F3AC7,
    0x51C9, 0x71E93AC7, 0x15075, 0x31503AC7, 0x14CF8, 0x18073AC7, 0x1392E, 0x28183AC7,
    0x12012, 0x23873AC7, 0x12945, 0x3B5A3AC7, 0x11D3B, 0x51CB3AC7, 0x136B5, 0x50773AC7,
    0x1485F, 0x62E23AC7, 0x14EEC, 0x4A453AC7, 0x165E2, 0x3F2F3AC7, 0x1233F, 0x46913AC7,
    0x129F8, 0x51233AC7, 0x12CA0, 0x25D03AC7, 0x124AB, 0x2F6F3AC7, 0x14EB8, 0x24AB3AC7,
    0x14315, 0x200F3AC7, 0x15A66, 0x44B93AC7, 0x15B2A, 0x383E3AC7, 0x13F8A, 0x59AD3AC7,
    0x14BA7, 0x56943AC7, 0x12642, 0x40F73AC7, 0x1203C, 0x4C2E3AC7, 0x13057, 0x50CD3AC7,
    0x1239A, 0x51763AC7, 0x132E9, 0x26F33AC7, 0x12658, 0x24AB3AC7, 0x126F8, 0x35643AC7,
    0x1225F, 0x297C3AC7, 0x14F95, 0x2AFC3AC7, 0x14DD8, 0x1E583AC7, 0x13E20, 0x24133AC7,
    0x14806, 0x1C0B3AC7, 0x154AA, 0x477F3AC7, 0x16024, 0x41F53AC7, 0x155CF, 0x34C73AC7,
    0x16088, 0x3BB83AC7, 0x143F4, 0x5E493AC7, 0x13B20, 0x55133AC7, 0x14D48, 0x506C3AC7,
    0x14A03, 0x5CBB3AC7,
};

static u32 lbl_1_data_BA50[134] = {
    0x80428000, 0x80008000, 0x4154, 0x3EAB0104, 0x78D3, 0x5C744000, 0x5F1D, 0x72C4000,
    0x9D5, 0x20E24000, 0x238B, 0x762A4000, 0x4154, 0x3EAB7EFB, 0x5691, 0x4A1105CF,
    0x6892, 0x53BB1376, 0x7499, 0x5A3027E5, 0x4CBA, 0x296E05CF, 0x5664, 0x176D1376,
    0x5CD9, 0xB6627E5, 0x2C17, 0x334505CF, 0x1A16, 0x299B1376, 0xE0E, 0x232627E5,
    0x35EE, 0x53E805CF, 0x2C44, 0x65E91376, 0x25CF, 0x71F127E5, 0x5691, 0x4A117A30,
    0x6892, 0x53BB6C89, 0x7499, 0x5A30581A, 0x4CBA, 0x296E7A30, 0x5664, 0x176D6C89,
    0x5CD9, 0xB66581A, 0x2C17, 0x33457A30, 0x1A16, 0x299B6C89, 0xE0E, 0x2326581A,
    0x35EE, 0x53E87A30, 0x2C44, 0x65E96C89, 0x25CF, 0x71F1581A, 0x8000, 0x44F34000,
    0x7DA2, 0x2C7D4000, 0x7216, 0x16CC4000, 0x479C, 0x4000, 0x2F26, 0x25D4000,
    0x1974, 0xDE94000, 0x2A8, 0x38634000, 0x506, 0x50D94000, 0x1092, 0x668B4000,
    0x3B0C, 0x7D574000, 0x5382, 0x7AF94000, 0x6933, 0x6F6D4000, 0x6425, 0x342C0C92,
    0x782D, 0x3D99210E, 0x6FA1, 0x213F210E, 0x36D5, 0x1BDA0C92, 0x4042, 0x7D2210E,
    0x23E8, 0x105E210E, 0x1E83, 0x492A0C92, 0xA7B, 0x3FBD210E, 0x1307, 0x5C17210E,
    0x4BD3, 0x617C0C92, 0x4266, 0x7584210E, 0x5EC0, 0x6CF8210E, 0x6425, 0x342C736D,
    0x6FA1, 0x213F5EF1, 0x782D, 0x3D995EF1, 0x36D5, 0x1BDA736D, 0x23E8, 0x105E5EF1,
    0x4042, 0x7D25EF1, 0x1E83, 0x492A736D, 0x1307, 0x5C175EF1, 0xA7B, 0x3FBD5EF1,
    0x4BD3, 0x617C736D, 0x5EC0, 0x6CF85EF1, 0x4266, 0x75845EF1,
};

static u32 lbl_1_data_BC68[86] = {
    0x802A8000, 0x80008000, 0x4066, 0x3F9900B9, 0x6033, 0xC2553F9, 0xCF3, 0x2BF12085,
    0x73DA, 0x2BF12085, 0x209A, 0xC2553F9, 0x209A, 0x730C53F9, 0x73DA, 0x53402085,
    0xCF3, 0x53402085, 0x6033, 0x730C53F9, 0x2CBF, 0x5F6573C5, 0x8000, 0x3F994052,
    0x2CBF, 0x1FCC73C5, 0x4066, 0x4052, 0xCF3, 0x5340601E, 0x2CBF, 0x1FCC0CDE,
    0x2CBF, 0x5F650CDE, 0x6033, 0xC252CAB, 0x6033, 0x730C2CAB, 0x73DA, 0x5340601E,
    0x209A, 0x730C2CAB, 0x4066, 0x3F997FEB, 0xCF3, 0x2BF1601E, 0x73DA, 0x2BF1601E,
    0x209A, 0xC252CAB, 0x540E, 0x1FCC0CDE, 0xCD, 0x3F994052, 0x540E, 0x5F650CDE,
    0x4066, 0x7F324052, 0x540E, 0x5F6573C5, 0x540E, 0x1FCC73C5, 0x4066, 0x23272EBE,
    0x4066, 0x5C0A2EBE, 0x51FA, 0x3F995CC3, 0x23F5, 0x2E054052, 0x51FA, 0x3F9923E1,
    0x4066, 0x5C0A51E6, 0x4066, 0x232751E6, 0x2ED2, 0x3F9923E1, 0x5CD8, 0x512D4052,
    0x2ED2, 0x3F995CC3, 0x5CD8, 0x2E054052, 0x23F5, 0x512D4052,
};

static u32 lbl_1_data_BDC0[86] = {
    0x802A8000, 0x80008000, 0x4316, 0x3D0E0354, 0x5BC9, 0x6E742576, 0x79B3, 0x34D52576,
    0x4C24, 0x6932576, 0x1212, 0x239C2576, 0x1BBD, 0x63D02576, 0x741A, 0x56815CB1,
    0x6A6F, 0x164D5CB1, 0x2A63, 0xBA95CB1, 0xC79, 0x45485CB1, 0x3A08, 0x738A5CB1,
    0x4316, 0x3D0E7ED3, 0x519B, 0x5A180C8D, 0x6330, 0x38390C8D, 0x4868, 0x1D090C8D,
    0x2646, 0x2E1A0C8D, 0x2BF5, 0x53D60C8D, 0x71B4, 0x5542209D, 0x6882, 0x1833209D,
    0x2B99, 0xE14209D, 0xF26, 0x44E1209D, 0x3A7A, 0x70DF209D, 0x6E6A, 0x690C4114,
    0x7A50, 0x21714114, 0x39E4, 0x4114, 0x62D, 0x32EF4114, 0x26A3, 0x73DC4114,
    0x4C48, 0x7A1D4114, 0x8000, 0x472E4114, 0x5F89, 0x6414114, 0x17C2, 0x11114114,
    0xBDC, 0x58AC4114, 0x7707, 0x353C618A, 0x4BB2, 0x93E618A, 0x1478, 0x24DB618A,
    0x1DAA, 0x61EA618A, 0x5A94, 0x6C09618A, 0x5FE6, 0x4C03759A, 0x5A37, 0x2647759A,
    0x3492, 0x2005759A, 0x22FC, 0x41E4759A, 0x3DC4, 0x5D14759A,
};

static u32 lbl_1_data_BF18[186] = {
    0x805C8000, 0x80008000, 0x4205, 0x3DD30108, 0x7A46, 0x3DD323CC, 0x5367, 0x85323CC,
    0x1483, 0x1CC223CC, 0x1483, 0x5EE323CC, 0x5367, 0x735223CC, 0x6F88, 0x1CC25C0C,
    0x30A3, 0x8535C0C, 0x9C5, 0x3DD35C0C, 0x30A3, 0x73525C0C, 0x6F88, 0x5EE35C0C,
    0x4205, 0x3DD37ED0, 0x58B5, 0x3DD30544, 0x6C57, 0x3DD31166, 0x4908, 0x283F0544,
    0x4F19, 0x15931166, 0x2FAB, 0x307D0544, 0x1FC9, 0x24F31166, 0x2FAB, 0x4B280544,
    0x1FC9, 0x56B21166, 0x4908, 0x53660544, 0x4F19, 0x66121166, 0x735A, 0x283F1F6B,
    0x65C9, 0x15931F6B, 0x3CBE, 0x83D1F6B, 0x26CB, 0xF5F1F6B, 0xD6E, 0x32491F6B,
    0xD6E, 0x495D1F6B, 0x26CB, 0x6C461F6B, 0x3CBE, 0x73681F6B, 0x65C9, 0x66121F6B,
    0x735A, 0x53661F6B, 0x7EB2, 0x307D361B, 0x7AF2, 0x24F349BD, 0x4816, 0x361B,
    0x3BF4, 0x49BD, 0x919, 0x24F3361B, 0x559, 0x307D49BD, 0x18C6, 0x6C46361B,
    0x2297, 0x736849BD, 0x6174, 0x7368361B, 0x6B45, 0x6C4649BD, 0x7EB2, 0x4B28361B,
    0x7AF2, 0x56B249BD, 0x6174, 0x83D361B, 0x6B45, 0xF5F49BD, 0x18C6, 0xF5F361B,
    0x2297, 0x83D49BD, 0x919, 0x56B2361B, 0x559, 0x4B2849BD, 0x4816, 0x7BA6361B,
    0x3BF4, 0x7BA649BD, 0x5D3F, 0xF5F606D, 0x474C, 0x83D606D, 0x1E42, 0x1593606D,
    0x10B1, 0x283F606D, 0x10B1, 0x5366606D, 0x1E42, 0x6612606D, 0x474C, 0x7368606D,
    0x5D3F, 0x6C46606D, 0x769D, 0x495D606D, 0x769D, 0x3248606D, 0x5460, 0x307D7A94,
    0x6442, 0x24F36E72, 0x3B03, 0x283F7A94, 0x34F1, 0x15936E72, 0x2B55, 0x3DD37A94,
    0x17B4, 0x3DD36E72, 0x3B03, 0x53667A94, 0x34F1, 0x66126E72, 0x5460, 0x4B287A94,
    0x6442, 0x56B26E72, 0x602D, 0x27E90D44, 0x3680, 0x1A5F0D44, 0x1CBF, 0x3DD30D44,
    0x3680, 0x61460D44, 0x602D, 0x53BC0D44, 0x8000, 0x3DD34A9C, 0x552C, 0x2E14A9C,
    0xFE1, 0x19654A9C, 0xFE1, 0x62404A9C, 0x552C, 0x78C44A9C, 0x7429, 0x1965353C,
    0x2EDE, 0x2E1353C, 0x40B, 0x3DD3353C, 0x2EDE, 0x78C4353C, 0x7429, 0x6240353C,
    0x4D8A, 0x1A5F7294, 0x23DD, 0x27E97294, 0x23DD, 0x53BC7294, 0x4D8A, 0x61467294,
    0x674C, 0x3DD37294,
};

static u32 lbl_1_data_C200[270] = {
    0x80868000, 0x80008000, 0x4000, 0x4000144B, 0x6717, 0x40002C74, 0x4C14, 0x1AD22C74,
    0x2060, 0x29062C74, 0x2060, 0x56F92C74, 0x4C14, 0x652D2C74, 0x5F9F, 0x2906538B,
    0x33EB, 0x1AD2538B, 0x18E8, 0x4000538B, 0x33EB, 0x652D538B, 0x5F9F, 0x56F9538B,
    0x4000, 0x40006BB4, 0x56F9, 0x40001AD2, 0x4719, 0x2A251AD2, 0x2D69, 0x327E1AD2,
    0x2D69, 0x4D811AD2, 0x4719, 0x55DA1AD2, 0x5E13, 0x2A252906, 0x3483, 0x1CA42906,
    0x1AD2, 0x40002906, 0x3483, 0x635B2906, 0x5E13, 0x55DA2906, 0x6990, 0x327E4000,
    0x4000, 0x144B4000, 0x166F, 0x327E4000, 0x264F, 0x635B4000, 0x59B0, 0x635B4000,
    0x6990, 0x4D814000, 0x59B0, 0x1CA44000, 0x264F, 0x1CA44000, 0x166F, 0x4D814000,
    0x4000, 0x6BB44000, 0x4B7C, 0x1CA456F9, 0x21EC, 0x2A2556F9, 0x21EC, 0x55DA56F9,
    0x4B7C, 0x635B56F9, 0x652D, 0x400056F9, 0x5296, 0x327E652D, 0x38E6, 0x2A25652D,
    0x2906, 0x4000652D, 0x38E6, 0x55DA652D, 0x5296, 0x4D81652D, 0x14000, 0x40000000,
    0x1793E, 0x40002360, 0x151B0, 0x98E2360, 0x111B0, 0x1E5A2360, 0x111B0, 0x61A52360,
    0x151B0, 0x76712360, 0x16E4F, 0x1E5A5C9F, 0x12E4F, 0x98E5C9F, 0x106C1, 0x40005C9F,
    0x12E4F, 0x76715C9F, 0x16E4F, 0x61A55C9F, 0x14000, 0x40008000, 0x15716, 0x4000044F,
    0x16B10, 0x400010A7, 0x14722, 0x2A0B044F, 0x14D4E, 0x170B10A7, 0x12D52, 0x326E044F,
    0x11D28, 0x26AF10A7, 0x12D52, 0x4D91044F, 0x11D28, 0x595010A7, 0x14722, 0x55F4044F,
    0x14D4E, 0x68F410A7, 0x17232, 0x2A0B1EEC, 0x16464, 0x170B1EEC, 0x13AA1, 0x9791EEC,
    0x1244B, 0x10BB1EEC, 0x10A7B, 0x34411EEC, 0x10A7B, 0x4BBE1EEC, 0x1244B, 0x6F441EEC,
    0x13AA1, 0x76861EEC, 0x16464, 0x68F41EEC, 0x17232, 0x55F41EEC, 0x17DBD, 0x326E3602,
    0x179ED, 0x26AF49FD, 0x1462C, 0x1163602, 0x139D3, 0x11649FD, 0x10612, 0x26AF3602,
    0x10242, 0x326E49FD, 0x11606, 0x6F443602, 0x12003, 0x768649FD, 0x15FFC, 0x76863602,
    0x169F9, 0x6F4449FD, 0x17DBD, 0x4D913602, 0x179ED, 0x595049FD, 0x15FFC, 0x9793602,
    0x169F9, 0x10BB49FD, 0x11606, 0x10BB3602, 0x12003, 0x97949FD, 0x10612, 0x59503602,
    0x10242, 0x4D9149FD, 0x1462C, 0x7EE93602, 0x139D3, 0x7EE949FD, 0x15BB4, 0x10BB6113,
    0x1455E, 0x9796113, 0x11B9B, 0x170B6113, 0x10DCD, 0x2A0B6113, 0x10DCD, 0x55F46113,
    0x11B9B, 0x68F46113, 0x1455E, 0x76866113, 0x15BB4, 0x6F446113, 0x17584, 0x4BBE6113,
    0x17584, 0x34416113, 0x152AD, 0x326E7BB0, 0x162D7, 0x26AF6F58, 0x138DD, 0x2A0B7BB0,
    0x132B1, 0x170B6F58, 0x128E9, 0x40007BB0, 0x114EF, 0x40006F58, 0x138DD, 0x55F47BB0,
    0x132B1, 0x68F46F58, 0x152AD, 0x4D917BB0, 0x162D7, 0x59506F58, 0x15EB0, 0x29B40C73,
    0x13447, 0x1BEC0C73, 0x11A11, 0x40000C73, 0x13447, 0x64130C73, 0x15EB0, 0x564B0C73,
    0x17F11, 0x40004AE0, 0x1537D, 0x4044AE0, 0x10CF9, 0x1AED4AE0, 0x10CF9, 0x65124AE0,
    0x1537D, 0x7BFB4AE0, 0x17306, 0x1AED351F, 0x12C82, 0x404351F, 0x100EE, 0x4000351F,
    0x12C82, 0x7BFB351F, 0x17306, 0x6512351F, 0x14BB8, 0x1BEC738C, 0x1214F, 0x29B4738C,
    0x1214F, 0x564B738C, 0x14BB8, 0x6413738C, 0x165EE, 0x4000738C,
};

static u32 lbl_1_data_C638[270] = {
    0x80868000, 0x80008000, 0x4000, 0x4000144B, 0x6717, 0x40002C74, 0x4C14, 0x1AD22C74,
    0x2060, 0x29062C74, 0x2060, 0x56F92C74, 0x4C14, 0x652D2C74, 0x5F9F, 0x2906538B,
    0x33EB, 0x1AD2538B, 0x18E8, 0x4000538B, 0x33EB, 0x652D538B, 0x5F9F, 0x56F9538B,
    0x4000, 0x40006BB4, 0x56F9, 0x40001AD2, 0x4719, 0x2A251AD2, 0x2D69, 0x327E1AD2,
    0x2D69, 0x4D811AD2, 0x4719, 0x55DA1AD2, 0x5E13, 0x2A252906, 0x3483, 0x1CA42906,
    0x1AD2, 0x40002906, 0x3483, 0x635B2906, 0x5E13, 0x55DA2906, 0x6990, 0x327E4000,
    0x4000, 0x144B4000, 0x166F, 0x327E4000, 0x264F, 0x635B4000, 0x59B0, 0x635B4000,
    0x6990, 0x4D814000, 0x59B0, 0x1CA44000, 0x264F, 0x1CA44000, 0x166F, 0x4D814000,
    0x4000, 0x6BB44000, 0x4B7C, 0x1CA456F9, 0x21EC, 0x2A2556F9, 0x21EC, 0x55DA56F9,
    0x4B7C, 0x635B56F9, 0x652D, 0x400056F9, 0x5296, 0x327E652D, 0x38E6, 0x2A25652D,
    0x2906, 0x4000652D, 0x38E6, 0x55DA652D, 0x5296, 0x4D81652D, 0x14000, 0x40000000,
    0x1793E, 0x40002360, 0x151B0, 0x98E2360, 0x111B0, 0x1E5A2360, 0x111B0, 0x61A52360,
    0x151B0, 0x76712360, 0x16E4F, 0x1E5A5C9F, 0x12E4F, 0x98E5C9F, 0x106C1, 0x40005C9F,
    0x12E4F, 0x76715C9F, 0x16E4F, 0x61A55C9F, 0x14000, 0x40008000, 0x15716, 0x4000044F,
    0x16B10, 0x400010A7, 0x14722, 0x2A0B044F, 0x14D4E, 0x170B10A7, 0x12D52, 0x326E044F,
    0x11D28, 0x26AF10A7, 0x12D52, 0x4D91044F, 0x11D28, 0x595010A7, 0x14722, 0x55F4044F,
    0x14D4E, 0x68F410A7, 0x17232, 0x2A0B1EEC, 0x16464, 0x170B1EEC, 0x13AA1, 0x9791EEC,
    0x1244B, 0x10BB1EEC, 0x10A7B, 0x34411EEC, 0x10A7B, 0x4BBE1EEC, 0x1244B, 0x6F441EEC,
    0x13AA1, 0x76861EEC, 0x16464, 0x68F41EEC, 0x17232, 0x55F41EEC, 0x17DBD, 0x326E3602,
    0x179ED, 0x26AF49FD, 0x1462C, 0x1163602, 0x139D3, 0x11649FD, 0x10612, 0x26AF3602,
    0x10242, 0x326E49FD, 0x11606, 0x6F443602, 0x12003, 0x768649FD, 0x15FFC, 0x76863602,
    0x169F9, 0x6F4449FD, 0x17DBD, 0x4D913602, 0x179ED, 0x595049FD, 0x15FFC, 0x9793602,
    0x169F9, 0x10BB49FD, 0x11606, 0x10BB3602, 0x12003, 0x97949FD, 0x10612, 0x59503602,
    0x10242, 0x4D9149FD, 0x1462C, 0x7EE93602, 0x139D3, 0x7EE949FD, 0x15BB4, 0x10BB6113,
    0x1455E, 0x9796113, 0x11B9B, 0x170B6113, 0x10DCD, 0x2A0B6113, 0x10DCD, 0x55F46113,
    0x11B9B, 0x68F46113, 0x1455E, 0x76866113, 0x15BB4, 0x6F446113, 0x17584, 0x4BBE6113,
    0x17584, 0x34416113, 0x152AD, 0x326E7BB0, 0x162D7, 0x26AF6F58, 0x138DD, 0x2A0B7BB0,
    0x132B1, 0x170B6F58, 0x128E9, 0x40007BB0, 0x114EF, 0x40006F58, 0x138DD, 0x55F47BB0,
    0x132B1, 0x68F46F58, 0x152AD, 0x4D917BB0, 0x162D7, 0x59506F58, 0x15EB0, 0x29B40C73,
    0x13447, 0x1BEC0C73, 0x11A11, 0x40000C73, 0x13447, 0x64130C73, 0x15EB0, 0x564B0C73,
    0x17F11, 0x40004AE0, 0x1537D, 0x4044AE0, 0x10CF9, 0x1AED4AE0, 0x10CF9, 0x65124AE0,
    0x1537D, 0x7BFB4AE0, 0x17306, 0x1AED351F, 0x12C82, 0x404351F, 0x100EE, 0x4000351F,
    0x12C82, 0x7BFB351F, 0x17306, 0x6512351F, 0x14BB8, 0x1BEC738C, 0x1214F, 0x29B4738C,
    0x1214F, 0x564B738C, 0x14BB8, 0x6413738C, 0x165EE, 0x4000738C,
};

static u32 lbl_1_data_CA70[294] = {
    0x80928000, 0x80008000, 0x4000, 0x40000D62, 0x6D45, 0x4000295D, 0x4DFD, 0x14F1295D,
    0x1B60, 0x2564295D, 0x1B60, 0x5A9B295D, 0x4DFD, 0x6B0E295D, 0x649F, 0x256456A2,
    0x3202, 0x14F156A2, 0x12BA, 0x400056A2, 0x3202, 0x6B0E56A2, 0x649F, 0x5A9B56A2,
    0x4000, 0x4000729D, 0x5A9B, 0x400014F1, 0x4839, 0x26B114F1, 0x2A78, 0x305C14F1,
    0x2A78, 0x4FA314F1, 0x4839, 0x594E14F1, 0x62D5, 0x26B12564, 0x32B2, 0x170D2564,
    0x14F1, 0x40002564, 0x32B2, 0x68F22564, 0x62D5, 0x594E2564, 0x7023, 0x305C4000,
    0x4000, 0xD624000, 0xFDC, 0x305C4000, 0x223F, 0x68F24000, 0x5DC0, 0x68F24000,
    0x7023, 0x4FA34000, 0x5DC0, 0x170D4000, 0x223F, 0x170D4000, 0xFDC, 0x4FA34000,
    0x4000, 0x729D4000, 0x4D4D, 0x170D5A9B, 0x1D2A, 0x26B15A9B, 0x1D2A, 0x594E5A9B,
    0x4D4D, 0x68F25A9B, 0x6B0E, 0x40005A9B, 0x5587, 0x305C6B0E, 0x37C6, 0x26B16B0E,
    0x2564, 0x40006B0E, 0x37C6, 0x594E6B0E, 0x5587, 0x4FA36B0E, 0x14000, 0x40000000,
    0x1793E, 0x40002360, 0x151B0, 0x98E2360, 0x111B0, 0x1E5A2360, 0x111B0, 0x61A52360,
    0x151B0, 0x76712360, 0x16E4F, 0x1E5A5C9F, 0x12E4F, 0x98E5C9F, 0x106C1, 0x40005C9F,
    0x12E4F, 0x76715C9F, 0x16E4F, 0x61A55C9F, 0x14000, 0x40008000, 0x15716, 0x4000044F,
    0x16B10, 0x400010A7, 0x14722, 0x2A0B044F, 0x14D4E, 0x170B10A7, 0x12D52, 0x326E044F,
    0x11D28, 0x26AF10A7, 0x12D52, 0x4D91044F, 0x11D28, 0x595010A7, 0x14722, 0x55F4044F,
    0x14D4E, 0x68F410A7, 0x17232, 0x2A0B1EEC, 0x16464, 0x170B1EEC, 0x13AA1, 0x9791EEC,
    0x1244B, 0x10BB1EEC, 0x10A7B, 0x34411EEC, 0x10A7B, 0x4BBE1EEC, 0x1244B, 0x6F441EEC,
    0x13AA1, 0x76861EEC, 0x16464, 0x68F41EEC, 0x17232, 0x55F41EEC, 0x17DBD, 0x326E3602,
    0x179ED, 0x26AF49FD, 0x1462C, 0x1163602, 0x139D3, 0x11649FD, 0x10612, 0x26AF3602,
    0x10242, 0x326E49FD, 0x11606, 0x6F443602, 0x12003, 0x768649FD, 0x15FFC, 0x76863602,
    0x169F9, 0x6F4449FD, 0x17DBD, 0x4D913602, 0x179ED, 0x595049FD, 0x15FFC, 0x9793602,
    0x169F9, 0x10BB49FD, 0x11606, 0x10BB3602, 0x12003, 0x97949FD, 0x10612, 0x59503602,
    0x10242, 0x4D9149FD, 0x1462C, 0x7EE93602, 0x139D3, 0x7EE949FD, 0x15BB4, 0x10BB6113,
    0x1455E, 0x9796113, 0x11B9B, 0x170B6113, 0x10DCD, 0x2A0B6113, 0x10DCD, 0x55F46113,
    0x11B9B, 0x68F46113, 0x1455E, 0x76866113, 0x15BB4, 0x6F446113, 0x17584, 0x4BBE6113,
    0x17584, 0x34416113, 0x152AD, 0x326E7BB0, 0x162D7, 0x26AF6F58, 0x138DD, 0x2A0B7BB0,
    0x132B1, 0x170B6F58, 0x128E9, 0x40007BB0, 0x114EF, 0x40006F58, 0x138DD, 0x55F47BB0,
    0x132B1, 0x68F46F58, 0x152AD, 0x4D917BB0, 0x162D7, 0x59506F58, 0x15EB0, 0x29B40C73,
    0x13447, 0x1BEC0C73, 0x11A11, 0x40000C73, 0x13447, 0x64130C73, 0x15EB0, 0x564B0C73,
    0x17F11, 0x40004AE0, 0x1537D, 0x4044AE0, 0x10CF9, 0x1AED4AE0, 0x10CF9, 0x65124AE0,
    0x1537D, 0x7BFB4AE0, 0x17306, 0x1AED351F, 0x12C82, 0x404351F, 0x100EE, 0x4000351F,
    0x12C82, 0x7BFB351F, 0x17306, 0x6512351F, 0x14BB8, 0x1BEC738C, 0x1214F, 0x29B4738C,
    0x1214F, 0x564B738C, 0x14BB8, 0x6413738C, 0x165EE, 0x4000738C, 0x24000, 0x4000186A,
    0x26367, 0x40002E4C, 0x24AF0, 0x1E532E4C, 0x2235B, 0x2B302E4C, 0x2235B, 0x54CF2E4C,
    0x24AF0, 0x61AC2E4C, 0x25CA4, 0x2B3051B3, 0x2350F, 0x1E5351B3, 0x21C98, 0x400051B3,
    0x2350F, 0x61AC51B3, 0x25CA4, 0x54CF51B3, 0x24000, 0x40006795,
};

static u32 lbl_1_data_CF08[294] = {
    0x80928000, 0x80008000, 0x4000, 0x40000D62, 0x6D45, 0x4000295D, 0x4DFD, 0x14F1295D,
    0x1B60, 0x2564295D, 0x1B60, 0x5A9B295D, 0x4DFD, 0x6B0E295D, 0x649F, 0x256456A2,
    0x3202, 0x14F156A2, 0x12BA, 0x400056A2, 0x3202, 0x6B0E56A2, 0x649F, 0x5A9B56A2,
    0x4000, 0x4000729D, 0x5A9B, 0x400014F1, 0x4839, 0x26B114F1, 0x2A78, 0x305C14F1,
    0x2A78, 0x4FA314F1, 0x4839, 0x594E14F1, 0x62D5, 0x26B12564, 0x32B2, 0x170D2564,
    0x14F1, 0x40002564, 0x32B2, 0x68F22564, 0x62D5, 0x594E2564, 0x7023, 0x305C4000,
    0x4000, 0xD624000, 0xFDC, 0x305C4000, 0x223F, 0x68F24000, 0x5DC0, 0x68F24000,
    0x7023, 0x4FA34000, 0x5DC0, 0x170D4000, 0x223F, 0x170D4000, 0xFDC, 0x4FA34000,
    0x4000, 0x729D4000, 0x4D4D, 0x170D5A9B, 0x1D2A, 0x26B15A9B, 0x1D2A, 0x594E5A9B,
    0x4D4D, 0x68F25A9B, 0x6B0E, 0x40005A9B, 0x5587, 0x305C6B0E, 0x37C6, 0x26B16B0E,
    0x2564, 0x40006B0E, 0x37C6, 0x594E6B0E, 0x5587, 0x4FA36B0E, 0x14000, 0x40000000,
    0x1793E, 0x40002360, 0x151B0, 0x98E2360, 0x111B0, 0x1E5A2360, 0x111B0, 0x61A52360,
    0x151B0, 0x76712360, 0x16E4F, 0x1E5A5C9F, 0x12E4F, 0x98E5C9F, 0x106C1, 0x40005C9F,
    0x12E4F, 0x76715C9F, 0x16E4F, 0x61A55C9F, 0x14000, 0x40008000, 0x15716, 0x4000044F,
    0x16B10, 0x400010A7, 0x14722, 0x2A0B044F, 0x14D4E, 0x170B10A7, 0x12D52, 0x326E044F,
    0x11D28, 0x26AF10A7, 0x12D52, 0x4D91044F, 0x11D28, 0x595010A7, 0x14722, 0x55F4044F,
    0x14D4E, 0x68F410A7, 0x17232, 0x2A0B1EEC, 0x16464, 0x170B1EEC, 0x13AA1, 0x9791EEC,
    0x1244B, 0x10BB1EEC, 0x10A7B, 0x34411EEC, 0x10A7B, 0x4BBE1EEC, 0x1244B, 0x6F441EEC,
    0x13AA1, 0x76861EEC, 0x16464, 0x68F41EEC, 0x17232, 0x55F41EEC, 0x17DBD, 0x326E3602,
    0x179ED, 0x26AF49FD, 0x1462C, 0x1163602, 0x139D3, 0x11649FD, 0x10612, 0x26AF3602,
    0x10242, 0x326E49FD, 0x11606, 0x6F443602, 0x12003, 0x768649FD, 0x15FFC, 0x76863602,
    0x169F9, 0x6F4449FD, 0x17DBD, 0x4D913602, 0x179ED, 0x595049FD, 0x15FFC, 0x9793602,
    0x169F9, 0x10BB49FD, 0x11606, 0x10BB3602, 0x12003, 0x97949FD, 0x10612, 0x59503602,
    0x10242, 0x4D9149FD, 0x1462C, 0x7EE93602, 0x139D3, 0x7EE949FD, 0x15BB4, 0x10BB6113,
    0x1455E, 0x9796113, 0x11B9B, 0x170B6113, 0x10DCD, 0x2A0B6113, 0x10DCD, 0x55F46113,
    0x11B9B, 0x68F46113, 0x1455E, 0x76866113, 0x15BB4, 0x6F446113, 0x17584, 0x4BBE6113,
    0x17584, 0x34416113, 0x152AD, 0x326E7BB0, 0x162D7, 0x26AF6F58, 0x138DD, 0x2A0B7BB0,
    0x132B1, 0x170B6F58, 0x128E9, 0x40007BB0, 0x114EF, 0x40006F58, 0x138DD, 0x55F47BB0,
    0x132B1, 0x68F46F58, 0x152AD, 0x4D917BB0, 0x162D7, 0x59506F58, 0x15EB0, 0x29B40C73,
    0x13447, 0x1BEC0C73, 0x11A11, 0x40000C73, 0x13447, 0x64130C73, 0x15EB0, 0x564B0C73,
    0x17F11, 0x40004AE0, 0x1537D, 0x4044AE0, 0x10CF9, 0x1AED4AE0, 0x10CF9, 0x65124AE0,
    0x1537D, 0x7BFB4AE0, 0x17306, 0x1AED351F, 0x12C82, 0x404351F, 0x100EE, 0x4000351F,
    0x12C82, 0x7BFB351F, 0x17306, 0x6512351F, 0x14BB8, 0x1BEC738C, 0x1214F, 0x29B4738C,
    0x1214F, 0x564B738C, 0x14BB8, 0x6413738C, 0x165EE, 0x4000738C, 0x24000, 0x4000186A,
    0x26367, 0x40002E4C, 0x24AF0, 0x1E532E4C, 0x2235B, 0x2B302E4C, 0x2235B, 0x54CF2E4C,
    0x24AF0, 0x61AC2E4C, 0x25CA4, 0x2B3051B3, 0x2350F, 0x1E5351B3, 0x21C98, 0x400051B3,
    0x2350F, 0x61AC51B3, 0x25CA4, 0x54CF51B3, 0x24000, 0x40006795,
};

static u32 lbl_1_data_D3A0[294] = {
    0x80928000, 0x80008000, 0x4000, 0x40000D62, 0x6D45, 0x4000295D, 0x4DFD, 0x14F1295D,
    0x1B60, 0x2564295D, 0x1B60, 0x5A9B295D, 0x4DFD, 0x6B0E295D, 0x649F, 0x256456A2,
    0x3202, 0x14F156A2, 0x12BA, 0x400056A2, 0x3202, 0x6B0E56A2, 0x649F, 0x5A9B56A2,
    0x4000, 0x4000729D, 0x5A9B, 0x400014F1, 0x4839, 0x26B114F1, 0x2A78, 0x305C14F1,
    0x2A78, 0x4FA314F1, 0x4839, 0x594E14F1, 0x62D5, 0x26B12564, 0x32B2, 0x170D2564,
    0x14F1, 0x40002564, 0x32B2, 0x68F22564, 0x62D5, 0x594E2564, 0x7023, 0x305C4000,
    0x4000, 0xD624000, 0xFDC, 0x305C4000, 0x223F, 0x68F24000, 0x5DC0, 0x68F24000,
    0x7023, 0x4FA34000, 0x5DC0, 0x170D4000, 0x223F, 0x170D4000, 0xFDC, 0x4FA34000,
    0x4000, 0x729D4000, 0x4D4D, 0x170D5A9B, 0x1D2A, 0x26B15A9B, 0x1D2A, 0x594E5A9B,
    0x4D4D, 0x68F25A9B, 0x6B0E, 0x40005A9B, 0x5587, 0x305C6B0E, 0x37C6, 0x26B16B0E,
    0x2564, 0x40006B0E, 0x37C6, 0x594E6B0E, 0x5587, 0x4FA36B0E, 0x14000, 0x40000000,
    0x1793E, 0x40002360, 0x151B0, 0x98E2360, 0x111B0, 0x1E5A2360, 0x111B0, 0x61A52360,
    0x151B0, 0x76712360, 0x16E4F, 0x1E5A5C9F, 0x12E4F, 0x98E5C9F, 0x106C1, 0x40005C9F,
    0x12E4F, 0x76715C9F, 0x16E4F, 0x61A55C9F, 0x14000, 0x40008000, 0x15716, 0x4000044F,
    0x16B10, 0x400010A7, 0x14722, 0x2A0B044F, 0x14D4E, 0x170B10A7, 0x12D52, 0x326E044F,
    0x11D28, 0x26AF10A7, 0x12D52, 0x4D91044F, 0x11D28, 0x595010A7, 0x14722, 0x55F4044F,
    0x14D4E, 0x68F410A7, 0x17232, 0x2A0B1EEC, 0x16464, 0x170B1EEC, 0x13AA1, 0x9791EEC,
    0x1244B, 0x10BB1EEC, 0x10A7B, 0x34411EEC, 0x10A7B, 0x4BBE1EEC, 0x1244B, 0x6F441EEC,
    0x13AA1, 0x76861EEC, 0x16464, 0x68F41EEC, 0x17232, 0x55F41EEC, 0x17DBD, 0x326E3602,
    0x179ED, 0x26AF49FD, 0x1462C, 0x1163602, 0x139D3, 0x11649FD, 0x10612, 0x26AF3602,
    0x10242, 0x326E49FD, 0x11606, 0x6F443602, 0x12003, 0x768649FD, 0x15FFC, 0x76863602,
    0x169F9, 0x6F4449FD, 0x17DBD, 0x4D913602, 0x179ED, 0x595049FD, 0x15FFC, 0x9793602,
    0x169F9, 0x10BB49FD, 0x11606, 0x10BB3602, 0x12003, 0x97949FD, 0x10612, 0x59503602,
    0x10242, 0x4D9149FD, 0x1462C, 0x7EE93602, 0x139D3, 0x7EE949FD, 0x15BB4, 0x10BB6113,
    0x1455E, 0x9796113, 0x11B9B, 0x170B6113, 0x10DCD, 0x2A0B6113, 0x10DCD, 0x55F46113,
    0x11B9B, 0x68F46113, 0x1455E, 0x76866113, 0x15BB4, 0x6F446113, 0x17584, 0x4BBE6113,
    0x17584, 0x34416113, 0x152AD, 0x326E7BB0, 0x162D7, 0x26AF6F58, 0x138DD, 0x2A0B7BB0,
    0x132B1, 0x170B6F58, 0x128E9, 0x40007BB0, 0x114EF, 0x40006F58, 0x138DD, 0x55F47BB0,
    0x132B1, 0x68F46F58, 0x152AD, 0x4D917BB0, 0x162D7, 0x59506F58, 0x15EB0, 0x29B40C73,
    0x13447, 0x1BEC0C73, 0x11A11, 0x40000C73, 0x13447, 0x64130C73, 0x15EB0, 0x564B0C73,
    0x17F11, 0x40004AE0, 0x1537D, 0x4044AE0, 0x10CF9, 0x1AED4AE0, 0x10CF9, 0x65124AE0,
    0x1537D, 0x7BFB4AE0, 0x17306, 0x1AED351F, 0x12C82, 0x404351F, 0x100EE, 0x4000351F,
    0x12C82, 0x7BFB351F, 0x17306, 0x6512351F, 0x14BB8, 0x1BEC738C, 0x1214F, 0x29B4738C,
    0x1214F, 0x564B738C, 0x14BB8, 0x6413738C, 0x165EE, 0x4000738C, 0x24000, 0x4000186A,
    0x26367, 0x40002E4C, 0x24AF0, 0x1E532E4C, 0x2235B, 0x2B302E4C, 0x2235B, 0x54CF2E4C,
    0x24AF0, 0x61AC2E4C, 0x25CA4, 0x2B3051B3, 0x2350F, 0x1E5351B3, 0x21C98, 0x400051B3,
    0x2350F, 0x61AC51B3, 0x25CA4, 0x54CF51B3, 0x24000, 0x40006795,
};

static void *lbl_1_data_D838[1555] = {
    (void *)0x82E68000, (void *)0x80008000, (void *)0x3FB7, (void *)0x3F6D26E7, (void *)0x563B, (void *)0x3F6D34D2, (void *)0x46AC, (void *)0x2A0434D2,
    (void *)0x2D80, (void *)0x323134D2, (void *)0x2D80, (void *)0x4CA934D2, (void *)0x46AC, (void *)0x54D734D2, (void *)0x51EE, (void *)0x32314B55,
    (void *)0x38C2, (void *)0x2A044B55, (void *)0x2933, (void *)0x3F6D4B55, (void *)0x38C2, (void *)0x54D74B55, (void *)0x51EE, (void *)0x4CA94B55,
    (void *)0x3FB7, (void *)0x3F6D5940, (void *)0x13FB7, (void *)0x3F6D26E7, (void *)0x1563B, (void *)0x3F6D34D2, (void *)0x146AC, (void *)0x2A0434D2,
    (void *)0x12D80, (void *)0x323134D2, (void *)0x12D80, (void *)0x4CA934D2, (void *)0x146AC, (void *)0x54D734D2, (void *)0x151EE, (void *)0x32314B55,
    (void *)0x138C2, (void *)0x2A044B55, (void *)0x12933, (void *)0x3F6D4B55, (void *)0x138C2, (void *)0x54D74B55, (void *)0x151EE, (void *)0x4CA94B55,
    (void *)0x13FB7, (void *)0x3F6D5940, (void *)0x148CC, (void *)0x3F6D2899, (void *)0x150A7, (void *)0x3F6D2D74, (void *)0x14285, (void *)0x36CA2899,
    (void *)0x144F3, (void *)0x2F512D74, (void *)0x1385E, (void *)0x3A172899, (void *)0x13203, (void *)0x35792D74, (void *)0x1385E, (void *)0x44C42899,
    (void *)0x13203, (void *)0x49622D74, (void *)0x14285, (void *)0x48102899, (void *)0x144F3, (void *)0x4F892D74, (void *)0x15376, (void *)0x36CA3311,
    (void *)0x14E08, (void *)0x2F513311, (void *)0x13D9A, (void *)0x29FB3311, (void *)0x134D1, (void *)0x2CD63311, (void *)0x12AAA, (void *)0x3ACF3311,
    (void *)0x12AAA, (void *)0x440C3311, (void *)0x134D1, (void *)0x52053311, (void *)0x13D9A, (void *)0x54E03311, (void *)0x14E08, (void *)0x4F893311,
    (void *)0x15376, (void *)0x48103311, (void *)0x15800, (void *)0x3A173C26, (void *)0x15680, (void *)0x35794401, (void *)0x14225, (void *)0x26AE3C26,
    (void *)0x13D49, (void *)0x26AE4401, (void *)0x128EE, (void *)0x35793C26, (void *)0x1276E, (void *)0x3A174401, (void *)0x12F35, (void *)0x52053C26,
    (void *)0x13322, (void *)0x54E04401, (void *)0x14C4C, (void *)0x54E03C26, (void *)0x15039, (void *)0x52054401, (void *)0x15800, (void *)0x44C43C26,
    (void *)0x15680, (void *)0x49624401, (void *)0x14C4C, (void *)0x29FB3C26, (void *)0x15039, (void *)0x2CD64401, (void *)0x12F35, (void *)0x2CD63C26,
    (void *)0x13322, (void *)0x29FB4401, (void *)0x128EE, (void *)0x49623C26, (void *)0x1276E, (void *)0x44C44401, (void *)0x14225, (void *)0x582C3C26,
    (void *)0x13D49, (void *)0x582C4401, (void *)0x14A9D, (void *)0x2CD64D16, (void *)0x141D4, (void *)0x29FB4D16, (void *)0x13166, (void *)0x2F514D16,
    (void *)0x12BF8, (void *)0x36CA4D16, (void *)0x12BF8, (void *)0x48104D16, (void *)0x13166, (void *)0x4F894D16, (void *)0x141D4, (void *)0x54E04D16,
    (void *)0x14A9D, (void *)0x52054D16, (void *)0x154C4, (void *)0x440C4D16, (void *)0x154C4, (void *)0x3ACF4D16, (void *)0x14710, (void *)0x3A17578E,
    (void *)0x14D6B, (void *)0x357952B3, (void *)0x13CE9, (void *)0x36CA578E, (void *)0x13A7B, (void *)0x2F5152B3, (void *)0x136A2, (void *)0x3F6D578E,
    (void *)0x12EC7, (void *)0x3F6D52B3, (void *)0x13CE9, (void *)0x4810578E, (void *)0x13A7B, (void *)0x4F8952B3, (void *)0x14710, (void *)0x44C4578E,
    (void *)0x14D6B, (void *)0x496252B3, (void *)0x14BC9, (void *)0x36A82BCD, (void *)0x13B1B, (void *)0x313D2BCD, (void *)0x130CB, (void *)0x3F6D2BCD,
    (void *)0x13B1B, (void *)0x4D9E2BCD, (void *)0x14BC9, (void *)0x48322BCD, (void *)0x15885, (void *)0x3F6D445B, (void *)0x14761, (void *)0x27D6445B,
    (void *)0x12BA5, (void *)0x30D9445B, (void *)0x12BA5, (void *)0x4E02445B, (void *)0x14761, (void *)0x5705445B, (void *)0x153C9, (void *)0x30D93BCC,
    (void *)0x1380D, (void *)0x27D63BCC, (void *)0x126E9, (void *)0x3F6D3BCC, (void *)0x1380D, (void *)0x57053BCC, (void *)0x153C9, (void *)0x4E023BCC,
    (void *)0x14453, (void *)0x313D545A, (void *)0x133A5, (void *)0x36A8545A, (void *)0x133A5, (void *)0x4832545A, (void *)0x14453, (void *)0x4D9E545A,
    (void *)0x14EA2, (void *)0x3F6D545A, (void *)0x24011, (void *)0x3F261D8A, (void *)0x25EF5, (void *)0x3F2630A1, (void *)0x2499D, (void *)0x21C530A1,
    (void *)0x22713, (void *)0x2CFE30A1, (void *)0x22713, (void *)0x514E30A1, (void *)0x2499D, (void *)0x5C8730A1, (void *)0x2590F, (void *)0x2CFE4F86,
    (void *)0x23685, (void *)0x21C54F86, (void *)0x2212D, (void *)0x3F264F86, (void *)0x23685, (void *)0x5C874F86, (void *)0x2590F, (void *)0x514E4F86,
    (void *)0x24011, (void *)0x3F26629D, (void *)0x25239, (void *)0x3F2622B2, (void *)0x245AD, (void *)0x2DE122B2, (void *)0x23160, (void *)0x347A22B2,
    (void *)0x23160, (void *)0x49D222B2, (void *)0x245AD, (void *)0x506B22B2, (void *)0x257D6, (void *)0x2DE12DEB, (void *)0x236FD, (void *)0x23352DEB,
    (void *)0x222B0, (void *)0x3F262DEB, (void *)0x236FD, (void *)0x5B172DEB, (void *)0x257D6, (void *)0x506B2DEB, (void *)0x260EA, (void *)0x347A4013,
    (void *)0x24011, (void *)0x1C9C4013, (void *)0x21F38, (void *)0x347A4013, (void *)0x22BC4, (void *)0x5B174013, (void *)0x2545E, (void *)0x5B174013,
    (void *)0x260EA, (void *)0x49D24013, (void *)0x2545E, (void *)0x23354013, (void *)0x22BC4, (void *)0x23354013, (void *)0x21F38, (void *)0x49D24013,
    (void *)0x24011, (void *)0x61B04013, (void *)0x24925, (void *)0x2335523C, (void *)0x2284C, (void *)0x2DE1523C, (void *)0x2284C, (void *)0x506B523C,
    (void *)0x24925, (void *)0x5B17523C, (void *)0x25D72, (void *)0x3F26523C, (void *)0x24EC2, (void *)0x347A5D75, (void *)0x23A75, (void *)0x2DE15D75,
    (void *)0x22DE9, (void *)0x3F265D75, (void *)0x23A75, (void *)0x506B5D75, (void *)0x24EC2, (void *)0x49D25D75, (void *)0x34585, (void *)0x4E5B1483,
    (void *)0x36B7E, (void *)0x453E31C9, (void *)0x34FDB, (void *)0x20752180, (void *)0x32180, (void *)0x2FB3208B, (void *)0x3207D, (void *)0x5DE6303D,
    (void *)0x34E38, (void *)0x6B373AE5, (void *)0x35EF1, (void *)0x20F44FE9, (void *)0x33136, (void *)0x13A44542, (void *)0x313F0, (void *)0x399D4E5E,
    (void *)0x32F93, (void *)0x5E655EA7, (void *)0x35DEE, (void *)0x4F285F9B, (void *)0x339E9, (void *)0x30806BA4, (void *)0x355BD, (void *)0x4D00198A,
    (void *)0x362FD, (void *)0x49D223C1, (void *)0x34A97, (void *)0x3E2B12F8, (void *)0x34E33, (void *)0x2E261781, (void *)0x337E6, (void *)0x44501296,
    (void *)0x32B53, (void *)0x399D16C9, (void *)0x3377D, (void *)0x56F218EA, (void *)0x32A90, (void *)0x5C5F2298, (void *)0x349EE, (void *)0x5C511D36,
    (void *)0x34CF7, (void *)0x66632A9C, (void *)0x36729, (void *)0x375028FE, (void *)0x35D83, (void *)0x2A79234F, (void *)0x33FAC, (void *)0x21C91C5B,
    (void *)0x32F7F, (void *)0x271B1C06, (void *)0x31C64, (void *)0x3FE221F8, (void *)0x31C0A, (void *)0x50022772, (void *)0x32E12, (void *)0x68033213,
    (void *)0x33E08, (void *)0x6CA835CB, (void *)0x35C48, (void *)0x62B7366A, (void *)0x3667F, (void *)0x5576333C, (void *)0x36D3E, (void *)0x37833BB6,
    (void *)0x368DD, (void *)0x2AD9463A, (void *)0x34602, (void *)0x16782B2A, (void *)0x33B50, (void *)0x11FF37A4, (void *)0x31754, (void *)0x31402E1E,
    (void *)0x31299, (void *)0x34B63E1C, (void *)0x321B7, (void *)0x62D7407F, (void *)0x326FA, (void *)0x630450B1, (void *)0x356D0, (void *)0x66B648E5,
    (void *)0x35C4B, (void *)0x5CEB55B5, (void *)0x36CD5, (void *)0x4A25420B, (void *)0x3681A, (void *)0x4D9B5209, (void *)0x35874, (void *)0x1BD72F76,
    (void *)0x35DB7, (void *)0x1C033FA8, (void *)0x32323, (void *)0x21EF2A72, (void *)0x3289E, (void *)0x18243742, (void *)0x31691, (void *)0x540239ED,
    (void *)0x31230, (void *)0x47584471, (void *)0x3441E, (void *)0x6CDC4883, (void *)0x3396C, (void *)0x686254FD, (void *)0x3515C, (void *)0x16D84E14,
    (void *)0x34166, (void *)0x12324A5C, (void *)0x32326, (void *)0x1C2449BD, (void *)0x318EF, (void *)0x29654CEB, (void *)0x31845, (void *)0x478B5729,
    (void *)0x321EB, (void *)0x54615CD8, (void *)0x33FC2, (void *)0x5D1163CC, (void *)0x34FEF, (void *)0x57C06421, (void *)0x3630A, (void *)0x3EF85E2F,
    (void *)0x36364, (void *)0x2ED858B5, (void *)0x347F1, (void *)0x27E8673D, (void *)0x354DE, (void *)0x227B5D8F, (void *)0x33580, (void *)0x228A62F1,
    (void *)0x33277, (void *)0x1877558B, (void *)0x329B1, (void *)0x31DA669D, (void *)0x31C71, (void *)0x35085C66, (void *)0x334D7, (void *)0x40B06D2F,
    (void *)0x3313B, (void *)0x50B468A6, (void *)0x34788, (void *)0x3A8A6D91, (void *)0x3541B, (void *)0x453D695E, (void *)0x35ACE, (void *)0x3BAE1A92,
    (void *)0x33C80, (void *)0x32DB1383, (void *)0x3291A, (void *)0x4C05198C, (void *)0x33B6A, (void *)0x64652457, (void *)0x35A22, (void *)0x5A4C24F9,
    (void *)0x36C1A, (void *)0x3BF14D33, (void *)0x34DA7, (void *)0x136A3B42, (void *)0x31A94, (void *)0x24353A34, (void *)0x31977, (void *)0x571C4B7F,
    (void *)0x34BD9, (void *)0x65C7573D, (void *)0x365F7, (void *)0x27BF34A8, (void *)0x33395, (void *)0x191328EA, (void *)0x31354, (void *)0x42EA32F4,
    (void *)0x331C7, (void *)0x6B7044E5, (void *)0x364DA, (void *)0x5AA645F2, (void *)0x34404, (void *)0x1A765BD0, (void *)0x3254C, (void *)0x248F5B2E,
    (void *)0x324A0, (void *)0x432C6595, (void *)0x342EE, (void *)0x4BFF6CA4, (void *)0x35654, (void *)0x32D5669B, (void *)0x44962, (void *)0x52A90C16,
    (void *)0x47557, (void *)0x46A331BD, (void *)0x454A5, (void *)0x1AB51B7A, (void *)0x41CC6, (void *)0x2DA417AA, (void *)0x41AF1, (void *)0x65452B92,
    (void *)0x451AD, (void *)0x74B83BAF, (void *)0x463E5, (void *)0x1A2F5495, (void *)0x42D29, (void *)0xABD4478, (void *)0x40980, (void *)0x38D24E6A,
    (void *)0x42A32, (void *)0x64C064AD, (void *)0x46210, (void *)0x51D1687D, (void *)0x43574, (void *)0x2CCC7411, (void *)0x45549, (void *)0x51D10F8B,
    (void *)0x4601F, (void *)0x5016155F, (void *)0x4695B, (void *)0x4D8F1D49, (void *)0x4708C, (void *)0x4A5B26E6, (void *)0x44D42, (void *)0x47070A14,
    (void *)0x45075, (void *)0x3B0A0AB5, (void *)0x452D2, (void *)0x2F480DF1, (void *)0x4543E, (void *)0x2453139F, (void *)0x43F8A, (void *)0x4BAE0924,
    (void *)0x435B0, (void *)0x441D08E1, (void *)0x42C50, (void *)0x3C550B50, (void *)0x423DF, (void *)0x34B81052, (void *)0x43F17, (void *)0x59560E08,
    (void *)0x434CF, (void *)0x5EC4126B, (void *)0x42B0D, (void *)0x62AD1908, (void *)0x42249, (void *)0x64E1218E, (void *)0x44C87, (void *)0x5D2111FD,
    (void *)0x44F09, (void *)0x662A1A23, (void *)0x450C7, (void *)0x6D532424, (void *)0x451AC, (void *)0x72412F82, (void *)0x47350, (void *)0x3C9E2AAD,
    (void *)0x46EC1, (void *)0x32C124A8, (void *)0x467E1, (void *)0x29851FFB, (void *)0x45F09, (void *)0x215F1CDE, (void *)0x44949, (void *)0x1B3C1677,
    (void *)0x43D73, (void *)0x1D8C137C, (void *)0x431B5, (void *)0x218612AF, (void *)0x426A3, (void *)0x26FB141A, (void *)0x41878, (void *)0x394A180D,
    (void *)0x41610, (void *)0x45401A65, (void *)0x415AE, (void *)0x50F11E94, (void *)0x41755, (void *)0x5BCA2466, (void *)0x42452, (void *)0x6D3E2D3E,
    (void *)0x42F06, (void *)0x72FE2FD6, (void *)0x43A87, (void *)0x763D3339, (void *)0x44645, (void *)0x76D3373D, (void *)0x45C77, (void *)0x6F4D38C1,
    (void *)0x465D6, (void *)0x6790362E, (void *)0x46D55, (void *)0x5DE13417, (void *)0x47295, (void *)0x52B83296, (void *)0x4770F, (void *)0x3C7D38B3,
    (void *)0x4760F, (void *)0x32814005, (void *)0x47265, (void *)0x29294757, (void *)0x46C3D, (void *)0x20EC4E4F, (void *)0x44D4F, (void *)0x12AA2177,
    (void *)0x4454D, (void *)0xCD328F4, (void *)0x43D01, (void *)0x9783191, (void *)0x434D3, (void *)0x8C33AE4, (void *)0x4142F, (void *)0x2E60209C,
    (void *)0x40DB5, (void *)0x2FF42B17, (void *)0x409A8, (void *)0x324D3699, (void *)0x4083B, (void *)0x354F4291, (void *)0x41AA0, (void *)0x6953374F,
    (void *)0x41C1B, (void *)0x6B58437A, (void *)0x41F50, (void *)0x6B3B4F7B, (void *)0x42416, (void *)0x69005ABB, (void *)0x457BC, (void *)0x720C4633,
    (void *)0x45C9A, (void *)0x6CEB5069, (void *)0x4600C, (void *)0x659559D4, (void *)0x461E5, (void *)0x5C6661FD, (void *)0x4769B, (void *)0x4A263D96,
    (void *)0x4752E, (void *)0x4D28498E, (void *)0x47121, (void *)0x4F815510, (void *)0x46AA7, (void *)0x51155F8B, (void *)0x45AC0, (void *)0x1675256C,
    (void *)0x45F86, (void *)0x143930AC, (void *)0x462BB, (void *)0x141D3CAD, (void *)0x46436, (void *)0x162248D8, (void *)0x41CF1, (void *)0x230F1E2A,
    (void *)0x41ECB, (void *)0x19E02653, (void *)0x4223C, (void *)0x128A2FBE, (void *)0x4271B, (void *)0xD6939F4, (void *)0x41299, (void *)0x5E8931D8,
    (void *)0x40C71, (void *)0x564C38CF, (void *)0x408C7, (void *)0x4CF44022, (void *)0x407C8, (void *)0x42F74774, (void *)0x44A04, (void *)0x76B24543,
    (void *)0x441D6, (void *)0x75FD4E96, (void *)0x43989, (void *)0x72A25733, (void *)0x43187, (void *)0x6CCB5EB0, (void *)0x45A84, (void *)0x123752E9,
    (void *)0x44FD0, (void *)0xC775051, (void *)0x4444F, (void *)0x9374CEE, (void *)0x43891, (void *)0x8A248EA, (void *)0x4225F, (void *)0x10284766,
    (void *)0x41900, (void *)0x17E549F9, (void *)0x41181, (void *)0x21944C10, (void *)0x40C41, (void *)0x2CBD4D91, (void *)0x40B86, (void *)0x42D7557A,
    (void *)0x41016, (void *)0x4CB45B7F, (void *)0x416F5, (void *)0x55F0602C, (void *)0x41FCE, (void *)0x5E156349, (void *)0x4358D, (void *)0x643969B0,
    (void *)0x44163, (void *)0x61E96CAB, (void *)0x44D21, (void *)0x5DEE6D78, (void *)0x45833, (void *)0x587A6C0D, (void *)0x4665F, (void *)0x462B681A,
    (void *)0x468C6, (void *)0x3A3565C2, (void *)0x46929, (void *)0x2E846193, (void *)0x46782, (void *)0x23AA5BC1, (void *)0x43FC0, (void *)0x261E721F,
    (void *)0x44A07, (void *)0x20B16DBC, (void *)0x453C9, (void *)0x1CC8671F, (void *)0x45C8D, (void *)0x1A935E99, (void *)0x4324F, (void *)0x22536E2A,
    (void *)0x42FCE, (void *)0x194B6604, (void *)0x42E0F, (void *)0x12225C03, (void *)0x42D2A, (void *)0xD3450A5, (void *)0x4298D, (void *)0x2DA4709C,
    (void *)0x41EB8, (void *)0x2F5F6AC8, (void *)0x4157B, (void *)0x31E662DE, (void *)0x40E4A, (void *)0x35195941, (void *)0x43195, (void *)0x386D7613,
    (void *)0x42E62, (void *)0x446A7572, (void *)0x42C04, (void *)0x502D7236, (void *)0x42A99, (void *)0x5B216C88, (void *)0x43F4C, (void *)0x33C77703,
    (void *)0x44926, (void *)0x3B587746, (void *)0x45286, (void *)0x432074D7, (void *)0x45AF7, (void *)0x4ABD6FD5, (void *)0x4591E, (void *)0x45C20E70,
    (void *)0x463E9, (void *)0x437D1579, (void *)0x45C3E, (void *)0x392F1041, (void *)0x46CE3, (void *)0x405A1F04, (void *)0x466B3, (void *)0x364F18F9,
    (void *)0x45E54, (void *)0x2CCB151B, (void *)0x44332, (void *)0x3F9207FC, (void *)0x44621, (void *)0x32F209BE, (void *)0x43907, (void *)0x376208D9,
    (void *)0x4482F, (void *)0x268B0E96, (void *)0x43BA4, (void *)0x2A280C4C, (void *)0x42F4F, (void *)0x2EF90CE3, (void *)0x434E9, (void *)0x52070BF8,
    (void *)0x42A9E, (void *)0x4A010CDE, (void *)0x42A30, (void *)0x570C1189, (void *)0x420E2, (void *)0x419E10E9, (void *)0x41F97, (void *)0x4E68141F,
    (void *)0x42011, (void *)0x5A6319C6, (void *)0x44201, (void *)0x639F14E2, (void *)0x43766, (void *)0x68CC1A87, (void *)0x4443C, (void *)0x6C6B1E4F,
    (void *)0x42D4B, (void *)0x6C2822C8, (void *)0x4394F, (void *)0x70F725A2, (void *)0x445AA, (void *)0x730929F5, (void *)0x45862, (void *)0x5C0A1669,
    (void *)0x45ACE, (void *)0x64C51FD9, (void *)0x4632B, (void *)0x59F61D84, (void *)0x45C44, (void *)0x6B602B80, (void *)0x46542, (void *)0x621228A2,
    (void *)0x46C25, (void *)0x56DB2712, (void *)0x4776D, (void *)0x3FD544F2, (void *)0x474CE, (void *)0x42A35173, (void *)0x4753C, (void *)0x35974CC8,
    (void *)0x46F15, (void *)0x44C55D75, (void *)0x470DD, (void *)0x382D59BD, (void *)0x46FE6, (void *)0x2C005498, (void *)0x4530B, (void *)0xEF32C2C,
    (void *)0x45759, (void *)0xD6F386E, (void *)0x44A83, (void *)0x9D034A7, (void *)0x459E8, (void *)0xE73459F, (void *)0x44E21, (void *)0x9814216,
    (void *)0x44189, (void *)0x7933E72, (void *)0x414E1, (void *)0x240527EE, (void *)0x41771, (void *)0x1B1F312B, (void *)0x40F14, (void *)0x25ED3380,
    (void *)0x41BF4, (void *)0x144F3BE1, (void *)0x412C6, (void *)0x1D9F3E09, (void *)0x40C13, (void *)0x28D4404F, (void *)0x412D6, (void *)0x61EC3E14,
    (void *)0x40D67, (void *)0x58C745B2, (void *)0x41512, (void *)0x63154AEB, (void *)0x40AD8, (void *)0x4E3F4DB3, (void *)0x410D4, (void *)0x58B9532F,
    (void *)0x41966, (void *)0x61CF579C, (void *)0x44FBF, (void *)0x731C5003, (void *)0x4471B, (void *)0x713359A6, (void *)0x45435, (void *)0x6CC35A8B,
    (void *)0x43E38, (void *)0x6C336274, (void *)0x44AFA, (void *)0x6922644F, (void *)0x45718, (void *)0x63C46426, (void *)0x46C00, (void *)0x1D894213,
    (void *)0x469C4, (void *)0x1C60353C, (void *)0x4716F, (void *)0x26AD3A75, (void *)0x46570, (void *)0x1DA6288B, (void *)0x46E03, (void *)0x26BC2CF7,
    (void *)0x473FF, (void *)0x31363274, (void *)0x42F18, (void *)0xC593024, (void *)0x42AA1, (void *)0x12B2259C, (void *)0x437BB, (void *)0xE412681,
    (void *)0x427BE, (void *)0x1BB11C01, (void *)0x433DC, (void *)0x16531BD8, (void *)0x4409E, (void *)0x13421DB3, (void *)0x40769, (void *)0x3FA03B35,
    (void *)0x4099A, (void *)0x49DE335F, (void *)0x40A08, (void *)0x3CD22EB4, (void *)0x40EF0, (void *)0x53752B8F, (void *)0x40DF9, (void *)0x4748266A,
    (void *)0x40FC1, (void *)0x3AB022B2, (void *)0x42BCB, (void *)0x708153FB, (void *)0x43453, (void *)0x75A54B80, (void *)0x4277D, (void *)0x720647B8,
    (void *)0x43D4D, (void *)0x77E241B5, (void *)0x430B5, (void *)0x75F43E10, (void *)0x424EE, (void *)0x71023A88, (void *)0x469F6, (void *)0x5B705839,
    (void *)0x46FC2, (void *)0x59884CA7, (void *)0x46765, (void *)0x64564EFC, (void *)0x472C3, (void *)0x56A13FD8, (void *)0x46C10, (void *)0x61D6421D,
    (void *)0x462E2, (void *)0x6B264446, (void *)0x43CD5, (void *)0x1BD66B45, (void *)0x43A9A, (void *)0x130A61D8, (void *)0x44770, (void *)0x16A965A0,
    (void *)0x4392C, (void *)0xC6C5632, (void *)0x44587, (void *)0xE7E5A85, (void *)0x4518B, (void *)0x134D5D5F, (void *)0x42675, (void *)0x236B69BE,
    (void *)0x41BAB, (void *)0x257F62A3, (void *)0x42408, (void *)0x1AB0604E, (void *)0x412B1, (void *)0x289A5915, (void *)0x41995, (void *)0x1D635785,
    (void *)0x42292, (void *)0x141554A7, (void *)0x425B9, (void *)0x39B371B7, (void *)0x42298, (void *)0x46456FE6, (void *)0x41AEE, (void *)0x3BF86AAE,
    (void *)0x42082, (void *)0x52AA6B0C, (void *)0x41823, (void *)0x4926672E, (void *)0x411F3, (void *)0x3F1B6123, (void *)0x43BA5, (void *)0x3FE3782B,
    (void *)0x445D0, (void *)0x4812774E, (void *)0x438B6, (void *)0x4C837669, (void *)0x44F87, (void *)0x507C7344, (void *)0x44332, (void *)0x554C73DB,
    (void *)0x436A7, (void *)0x58EA7191, (void *)0x449ED, (void *)0x2D6E742F, (void *)0x454A6, (void *)0x28696E9E, (void *)0x45438, (void *)0x35747349,
    (void *)0x45EC5, (void *)0x25126661, (void *)0x45F3F, (void *)0x310C6C08, (void *)0x45DF4, (void *)0x3DD76F3E, (void *)0x53FFD, (void *)0x3F870027,
    (void *)0x57929, (void *)0x3F87237D, (void *)0x551A8, (void *)0x927237D, (void *)0x511BC, (void *)0x1DEC237D, (void *)0x511BC, (void *)0x6122237D,
    (void *)0x551A8, (void *)0x75E7237D, (void *)0x56E3E, (void *)0x1DEC5CAA, (void *)0x52E52, (void *)0x9275CAA, (void *)0x506D0, (void *)0x3F875CAA,
    (void *)0x52E52, (void *)0x75E75CAA, (void *)0x56E3E, (void *)0x61225CAA, (void *)0x53FFD, (void *)0x3F878000, (void *)0x54E07, (void *)0x3F8701B7,
    (void *)0x55B61, (void *)0x3F870652, (void *)0x56765, (void *)0x3F870DBF, (void *)0x5717D, (void *)0x3F8717A1, (void *)0x54453, (void *)0x322D01B7,
    (void *)0x54874, (void *)0x257A0652, (void *)0x54C2A, (void *)0x1A0D0DBF, (void *)0x54F49, (void *)0x107417A1, (void *)0x534A1, (void *)0x374701B7,
    (void *)0x529D4, (void *)0x2F6E0652, (void *)0x5201B, (void *)0x285E0DBF, (void *)0x517F1, (void *)0x226F17A1, (void *)0x534A1, (void *)0x47C801B7,
    (void *)0x529D4, (void *)0x4FA10652, (void *)0x5201B, (void *)0x56B10DBF, (void *)0x517F1, (void *)0x5CA017A1, (void *)0x54453, (void *)0x4CE101B7,
    (void *)0x54874, (void *)0x59950652, (void *)0x54C2A, (void *)0x65020DBF, (void *)0x54F49, (void *)0x6E9B17A1, (void *)0x575D3, (void *)0x322D204F,
    (void *)0x56FDC, (void *)0x257A1EAD, (void *)0x5678F, (void *)0x1A0D1EAD, (void *)0x55D53, (void *)0x1074204F, (void *)0x543ED, (void *)0x833204F,
    (void *)0x53601, (void *)0x9F31EAD, (void *)0x52892, (void *)0xE501EAD, (void *)0x51C48, (void *)0x1515204F, (void *)0x50C96, (void *)0x2AB0204F,
    (void *)0x509F2, (void *)0x38771EAD, (void *)0x509F2, (void *)0x46971EAD, (void *)0x50C96, (void *)0x545F204F, (void *)0x51C48, (void *)0x69FA204F,
    (void *)0x52892, (void *)0x70BE1EAD, (void *)0x53601, (void *)0x751C1EAD, (void *)0x543ED, (void *)0x76DB204F, (void *)0x55D53, (void *)0x6E9B204F,
    (void *)0x5678F, (void *)0x65021EAD, (void *)0x56FDC, (void *)0x59951EAD, (void *)0x575D3, (void *)0x4CE1204F, (void *)0x57CD8, (void *)0x37472E59,
    (void *)0x57D8E, (void *)0x2F6E3A11, (void *)0x57B43, (void *)0x285E4615, (void *)0x57613, (void *)0x226F51CE, (void *)0x54AF2, (void *)0x31A2E59,
    (void *)0x543B3, (void *)0x3A11, (void *)0x53C46, (void *)0x4615, (void *)0x53508, (void *)0x31A51CE, (void *)0x509E7, (void *)0x226F2E59,
    (void *)0x504B7, (void *)0x285E3A11, (void *)0x5026B, (void *)0x2F6E4615, (void *)0x50321, (void *)0x374751CE, (void *)0x5139B, (void *)0x69FA2E59,
    (void *)0x517A4, (void *)0x70BE3A11, (void *)0x51DA6, (void *)0x751C4615, (void *)0x52555, (void *)0x76DB51CE, (void *)0x55AA4, (void *)0x76DB2E59,
    (void *)0x56254, (void *)0x751C3A11, (void *)0x56856, (void *)0x70BE4615, (void *)0x56C5F, (void *)0x69FA51CE, (void *)0x57CD8, (void *)0x47C82E59,
    (void *)0x57D8E, (void *)0x4FA13A11, (void *)0x57B43, (void *)0x56B14615, (void *)0x57613, (void *)0x5CA051CE, (void *)0x55AA4, (void *)0x8332E59,
    (void *)0x56254, (void *)0x9F33A11, (void *)0x56856, (void *)0xE504615, (void *)0x56C5F, (void *)0x151551CE, (void *)0x5139B, (void *)0x15152E59,
    (void *)0x517A4, (void *)0xE503A11, (void *)0x51DA6, (void *)0x9F34615, (void *)0x52555, (void *)0x83351CE, (void *)0x509E7, (void *)0x5CA02E59,
    (void *)0x504B7, (void *)0x56B13A11, (void *)0x5026B, (void *)0x4FA14615, (void *)0x50321, (void *)0x47C851CE, (void *)0x54AF2, (void *)0x7BF52E59,
    (void *)0x543B3, (void *)0x7F0F3A11, (void *)0x53C46, (void *)0x7F0F4615, (void *)0x53508, (void *)0x7BF551CE, (void *)0x563B2, (void *)0x15155FD8,
    (void *)0x55768, (void *)0xE50617A, (void *)0x549F9, (void *)0x9F3617A, (void *)0x53C0D, (void *)0x8335FD8, (void *)0x522A7, (void *)0x10745FD8,
    (void *)0x5186B, (void *)0x1A0D617A, (void *)0x5101D, (void *)0x257A617A, (void *)0x50A26, (void *)0x322D5FD8, (void *)0x50A26, (void *)0x4CE15FD8,
    (void *)0x5101D, (void *)0x5995617A, (void *)0x5186B, (void *)0x6502617A, (void *)0x522A7, (void *)0x6E9B5FD8, (void *)0x53C0D, (void *)0x76DB5FD8,
    (void *)0x549F9, (void *)0x751C617A, (void *)0x55768, (void *)0x70BE617A, (void *)0x563B2, (void *)0x69FA5FD8, (void *)0x57364, (void *)0x545F5FD8,
    (void *)0x57608, (void *)0x4697617A, (void *)0x57608, (void *)0x3877617A, (void *)0x57364, (void *)0x2AB05FD8, (void *)0x54B58, (void *)0x37477E70,
    (void *)0x55626, (void *)0x2F6E79D5, (void *)0x55FDF, (void *)0x285E7268, (void *)0x56809, (void *)0x226F6886, (void *)0x53BA6, (void *)0x322D7E70,
    (void *)0x53786, (void *)0x257A79D5, (void *)0x533CF, (void *)0x1A0D7268, (void *)0x530B1, (void *)0x10746886, (void *)0x531F3, (void *)0x3F877E70,
    (void *)0x52498, (void *)0x3F8779D5, (void *)0x51894, (void *)0x3F877268, (void *)0x50E7D, (void *)0x3F876886, (void *)0x53BA6, (void *)0x4CE17E70,
    (void *)0x53786, (void *)0x599579D5, (void *)0x533CF, (void *)0x65027268, (void *)0x530B1, (void *)0x6E9B6886, (void *)0x54B58, (void *)0x47C87E70,
    (void *)0x55626, (void *)0x4FA179D5, (void *)0x55FDF, (void *)0x56B17268, (void *)0x56809, (void *)0x5CA06886, (void *)0x55283, (void *)0x32120465,
    (void *)0x56015, (void *)0x31F40A7D, (void *)0x556D1, (void *)0x25330A7D, (void *)0x56C28, (void *)0x31EF13EA, (void *)0x56460, (void *)0x251812A7,
    (void *)0x55A91, (void *)0x19B913EA, (void *)0x538E9, (void *)0x29C00465, (void *)0x53CFE, (void *)0x1CCF0A7D, (void *)0x52E01, (void *)0x21AE0A7D,
    (void *)0x540B5, (void *)0x115213EA, (void *)0x53217, (void *)0x14C112A7, (void *)0x5243F, (void *)0x1A9113EA, (void *)0x52917, (void *)0x3F870465,
    (void *)0x51E0B, (void *)0x37A60A7D, (void *)0x51E0B, (void *)0x47690A7D, (void *)0x51443, (void *)0x309113EA, (void *)0x51303, (void *)0x3F8712A7,
    (void *)0x51443, (void *)0x4E7E13EA, (void *)0x538E9, (void *)0x554F0465, (void *)0x52E01, (void *)0x5D610A7D, (void *)0x53CFE, (void *)0x62400A7D,
    (void *)0x5243F, (void *)0x647D13EA, (void *)0x53217, (void *)0x6A4D12A7, (void *)0x540B5, (void *)0x6DBD13EA, (void *)0x55283, (void *)0x4CFD0465,
    (void *)0x556D1, (void *)0x59DB0A7D, (void *)0x56015, (void *)0x4D1B0A7D, (void *)0x55A91, (void *)0x655613EA, (void *)0x56460, (void *)0x59F712A7,
    (void *)0x56C28, (void *)0x4D2013EA, (void *)0x57F9C, (void *)0x3F8739DE, (void *)0x57F19, (void *)0x47694679, (void *)0x57F19, (void *)0x37A64679,
    (void *)0x57B0B, (void *)0x4E7E536F, (void *)0x57CBB, (void *)0x3F8753FD, (void *)0x57B0B, (void *)0x3091536F, (void *)0x553A6, (void *)0x30639DE,
    (void *)0x55AFC, (void *)0x5F14679, (void *)0x54BFF, (void *)0x1124679, (void *)0x56078, (void *)0xBFD536F, (void *)0x552C2, (void *)0x5C353FD,
    (void *)0x54401, (void *)0x2BE536F, (void *)0x50C85, (void *)0x1A2239DE, (void *)0x51190, (void *)0x140F4679, (void *)0x5084C, (void *)0x20CF4679,
    (void *)0x51902, (void *)0x10B6536F, (void *)0x50ED9, (void *)0x1BD353FD, (void *)0x5076B, (void *)0x28EC536F, (void *)0x50C85, (void *)0x64EC39DE,
    (void *)0x5084C, (void *)0x5E404679, (void *)0x51190, (void *)0x6B004679, (void *)0x5076B, (void *)0x5622536F, (void *)0x50ED9, (void *)0x633B53FD,
    (void *)0x51902, (void *)0x6E58536F, (void *)0x553A6, (void *)0x7C0939DE, (void *)0x54BFF, (void *)0x7DFC4679, (void *)0x55AFC, (void *)0x791E4679,
    (void *)0x54401, (void *)0x7C51536F, (void *)0x552C2, (void *)0x794C53FD, (void *)0x56078, (void *)0x7311536F, (void *)0x57375, (void *)0x1A224649,
    (void *)0x56E6A, (void *)0x140F39AE, (void *)0x577AE, (void *)0x20CF39AE, (void *)0x566F8, (void *)0x10B62CB7, (void *)0x57121, (void *)0x1BD32C2A,
    (void *)0x5788F, (void *)0x28EC2CB7, (void *)0x52C54, (void *)0x3064649, (void *)0x524FD, (void *)0x5F139AE, (void *)0x533FB, (void *)0x11239AE,
    (void *)0x51F82, (void *)0xBFD2CB7, (void *)0x52D38, (void *)0x5C32C2A, (void *)0x53BF8, (void *)0x2BE2CB7, (void *)0x5005E, (void *)0x3F874649,
    (void *)0x500E0, (void *)0x476939AE, (void *)0x500E0, (void *)0x37A639AE, (void *)0x504EF, (void *)0x4E7E2CB7, (void *)0x5033F, (void *)0x3F872C2A,
    (void *)0x504EF, (void *)0x30912CB7, (void *)0x52C54, (void *)0x7C094649, (void *)0x533FB, (void *)0x7DFC39AE, (void *)0x524FD, (void *)0x791E39AE,
    (void *)0x53BF8, (void *)0x7C512CB7, (void *)0x52D38, (void *)0x794C2C2A, (void *)0x51F82, (void *)0x73112CB7, (void *)0x57375, (void *)0x64EC4649,
    (void *)0x577AE, (void *)0x5E4039AE, (void *)0x56E6A, (void *)0x6B0039AE, (void *)0x5788F, (void *)0x56222CB7, (void *)0x57121, (void *)0x633B2C2A,
    (void *)0x566F8, (void *)0x6E582CB7, (void *)0x54710, (void *)0x29C07BC1, (void *)0x542FB, (void *)0x1CCF75AA, (void *)0x551F9, (void *)0x21AE75AA,
    (void *)0x53F45, (void *)0x11526C3D, (void *)0x54DE3, (void *)0x14C16D80, (void *)0x55BBB, (void *)0x1A916C3D, (void *)0x52D76, (void *)0x32127BC1,
    (void *)0x51FE5, (void *)0x31F475AA, (void *)0x52928, (void *)0x253375AA, (void *)0x513D1, (void *)0x31EF6C3D, (void *)0x51B9A, (void *)0x25186D80,
    (void *)0x52569, (void *)0x19B96C3D, (void *)0x52D76, (void *)0x4CFD7BC1, (void *)0x52928, (void *)0x59DB75AA, (void *)0x51FE5, (void *)0x4D1B75AA,
    (void *)0x52569, (void *)0x65566C3D, (void *)0x51B9A, (void *)0x59F76D80, (void *)0x513D1, (void *)0x4D206C3D, (void *)0x54710, (void *)0x554F7BC1,
    (void *)0x551F9, (void *)0x5D6175AA, (void *)0x542FB, (void *)0x624075AA, (void *)0x55BBB, (void *)0x647D6C3D, (void *)0x54DE3, (void *)0x6A4D6D80,
    (void *)0x53F45, (void *)0x6DBD6C3D, (void *)0x556E3, (void *)0x3F877BC1, (void *)0x561EF, (void *)0x37A675AA, (void *)0x561EF, (void *)0x476975AA,
    (void *)0x56BB6, (void *)0x30916C3D, (void *)0x56CF6, (void *)0x3F876D80, (void *)0x56BB6, (void *)0x4E7E6C3D, &lbl_1_data_AE20, &lbl_1_data_B2B8,
    &lbl_1_data_B540, &lbl_1_data_B7C8, &lbl_1_data_BA50, &lbl_1_data_BC68, &lbl_1_data_BDC0, &lbl_1_data_BF18, &lbl_1_data_C200, &lbl_1_data_C638,
    &lbl_1_data_CA70, &lbl_1_data_CF08, &lbl_1_data_D3A0, &lbl_1_data_D838, (void *)0x2A, (void *)0x15, (void *)0x21, (void *)0x2A,
    (void *)0x1E, (void *)0x21, (void *)0x24, (void *)0x27, (void *)0x27, (void *)0x27, (void *)0x24, (void *)0x2A,
    (void *)0x27, (void *)0x36, (void *)0x8F5C0AFF, (void *)0xFF0000FF, (void *)0xF1DA95FF, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0, (void *)0x0,
    (void *)0x0, (void *)0x0, (void *)0x0, (void *)0xFF4040FF, (void *)0x40FF40FF, (void *)0x4040FFFF, (void *)0xFFFF40FF, (void *)0xFF40FFFF,
    (void *)0x40FFFFFF, (void *)0xFF6060FF, (void *)0x60FF60FF, (void *)0x6060FFFF, (void *)0xFFFF60FF, (void *)0xFF60FFFF, (void *)0x60FFFFFF, (void *)0xF5FFFAFF,
    (void *)0x60FFFFFF, (void *)0xFFD700FF, (void *)0xFF60FFFF, (void *)0xFFFF60FF, (void *)0x98FB98FF, (void *)0x6060FFFF, (void *)0x7FFFD4FF, (void *)0x60FF60FF,
    (void *)0xAFEEEEFF, (void *)0x40FFFFFF, (void *)0xFF6060FF,
};
static s32 lbl_1_data_F084 = 0x100;
static s32 lbl_1_data_F088 = 2;
static f32 lbl_1_data_F08C[5] = {0.0003f, 0.0004f, 0.005f, 0.003f, 0.0f};
static f32 lbl_1_data_F0A0 = -20.0f;
static f32 lbl_1_data_F0A4 = 10.0f;

static u8 lbl_1_data_F0A8[20] = {
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x14, 0x15, 0x16,
    0x17, 0x18, 0x00, 0x00,
};

static s32 lbl_1_data_F0BC[20] = {
    0x0, 0x4, 0x14, 0x13880, 0x7530, 0x130B0, 0x3C, 0xA,
    0x1A9C8, 0x18A88, 0x0, 0x28, 0xC35000, 0x0, 0x0, 0x0,
    -256, 0x0, 0x124F8, 0x0,
};

static s32 lbl_1_data_F10C[26] = {
    0x0, 0x4, 0x2, 0x13880, 0x7530, 0x130B0, 0x32, 0x5,
    0x1A9C8, 0x18A88, 0x0, 0x28, 0xC35000, 0x7A1200, 0x0, 0x0,
    -256, 0x0, 0x0, 0x0, 0x0, 0x9C40, 0x80, 0x40,
    0xC350, -1000,
};

static s32 *lbl_1_data_F174[2] = {&lbl_1_data_F10C[18], (s32 *)lbl_800F787C};

static u16 lbl_1_data_F17C[6] = {
    0x0007, 0x0008, 0x0004, 0x0005, 0x0006, 0xFFFF,
};

static s32 lbl_1_data_F188[20] = {
    0x0, 0x7, 0x3, 0x186A0, 0x7530, 0x2710, 0xC, 0x8,
    0x1ADB0, 0xC350, 0x0, 0x3C, 0x44AA20, 0x1312D00, 0x0, 0x1E8480,
    -256, 0x0, 0x124F8, 0x0,
};

static s32 lbl_1_data_F1D8[20] = {
    0x0, 0x7, 0xA, 0x4650, 0x4E20, 0xEA60, 0xC, 0x6,
    0x1A9C8, 0x18A88, 0x0, 0x3C, 0x44AA20, 0x8F6EC0, -1000000, 0x44AA20,
    -256, 0x0, 0x124F8, 0x0,
};

static s32 lbl_1_data_F228[20] = {
    0x0, 0x4, 0x1, 0xEA60, 0x2710, 0xC350, 0x1E, 0x8,
    0x19640, 0x19E0F, 0x0, 0x5A, 0xC35000, 0x989680, 0xF4240, 0x5B8D80,
    0x3C3C3C00, 0x0, 0x124F8, 0x0,
};

static s32 *lbl_1_data_F278[3] = {lbl_1_data_F188, lbl_1_data_F1D8, lbl_1_data_F228};

static DbgRowTbl lbl_1_data_F4D4;

// .text:0x00017D90 size:0x16C
void fn_1_17D90(void) {
    fn_800AD038(*(void **)(lbl_80366158 + 8));
    currentDrawingItem->state = 0;
    currentDrawingItem->func = fn_1_17B5C;
    fn_1_D7A4(0);
    while ((s8)lbl_1_data_F4D4.tbl[lbl_1_data_F4D4.cur].name[0] != 0) {
        lbl_1_data_F4D4.cur++;
    }
}

// .text:0x00017B5C size:0x234
void fn_1_17B5C(void) {
    s32 i;
    s32 first;
    lbl_1_bss_5F62 = -1;
    lbl_1_bss_5F60 = 4;
    for (i = 0; i < 0x36; i++) {
        lbl_1_bss_60A4[i] = DBG_A978[i] != -1;
    }
    for (first = 0; first < 7; first++) {
        if (lbl_1_data_2390[first] != 0) {
            break;
        }
    }
    lbl_1_bss_68FC.f40[0] = 0;
    lbl_1_bss_6940[0].f44 = first;
    lbl_1_bss_6940[0].f45 = 0;
    lbl_1_bss_6940[0].f46 = 0;
    lbl_1_bss_5F5C = 0;
    currentDrawingItem->func = fn_1_176EC;
    fn_80052D70();
}

static inline void dbgSetAnim(u8 *obj, void *anim, u16 frame) {
    *(void **)(obj + 4) = anim;
    *(u16 *)(obj + 0xE) = frame;
    *(f32 *)(obj + 0x5C) = 0.0f;
    *(u8 *)(obj + 0x58) = 1;
    *(u8 *)(obj + 0x59) = anim != NULL;
    *(u8 *)(obj + 0x5A) = anim != NULL;
    *(f32 *)(obj + 0x60) = 0.0f;
}

static inline void dbgMoveCamera(void) {
    u8 *in = (u8 *)&AtBat_ButtonInput1;
    DbgActor *a = &hugeAnimStruct.slots[lbl_1_bss_5F73];
    f32 rt = in[0x15] / 768.0f;
    f32 sx = (s8)in[0x10] / 768.0f;
    f32 sy = (s8)in[0x11] / 768.0f;
    f32 lt = in[0x14] / 768.0f;
    f32 cy = (s8)in[0x13];
    f32 cx = (s8)in[0x12];
    a->pos.x += sx;
    a->pos.y = a->pos.y + rt - lt;
    a->pos.z += sy;
    lbl_1_data_AD0C[0] -= cy * 0.001953125f;
    lbl_1_data_AD0C[1] -= cx * 0.001953125f;
    a->rotX = lbl_1_data_AD0C[0];
    a->rotY = lbl_1_data_AD0C[1];
    a->rotZ = lbl_1_data_AD0C[2];
}

// .text:0x000179CC size:0x190
void fn_1_179CC(void) {
    switch (lbl_1_bss_5F72) {
    case 0:
        fn_1_121D4(&lbl_1_bss_67E0);
        break;
    case 1:
        dbgMoveCamera();
        break;
    }
}

// .text:0x00017954 size:0x78
void fn_1_17954(void) {
    Mtx44 m;
    C_MTXFrustum(m, -0.000175f, 0.000175f, 0.00025f, -0.00025f, 0.001f, 512.0f);
    GXSetProjection(m, GX_PERSPECTIVE);
}

// .text:0x0001770C size:0x248
void fn_1_1770C(void) {
    s32 f;
    DbgDrawRow *a9e4 = (DbgDrawRow *)((u8 *)DBG_A978 + 0x6C);
    ((void (**)(void))((u8 *)lbl_1_data_ABA8 + 0xC))[lbl_1_bss_5F71]();
    f = 0;
    if (lbl_1_bss_5F71 != 0) {
        if (lbl_1_bss_5F68 == 0 || lbl_1_bss_5F64 != 0.0f) {
            f = 1;
        }
    }
    lbl_1_bss_3215 = f;
    if (lbl_1_bss_5F5C == 1) {
        insertGraphicDrawingFunction(fn_1_107B8, 0xFF);
        lbl_1_bss_5F5C = 2;
    }
    fn_1_179CC();
    PSMTXCopy(lbl_1_bss_67E0.mtx0, lbl_1_bss_68FC.mtx10);
    fn_1_129D0();
    PSMTXCopy(lbl_1_bss_68FC.mtx10, lbl_1_data_AAC4[drawStadiumRelated].mtx);
    fn_800A7D4C(7, &lbl_1_data_AAC4[drawStadiumRelated]);
    if (lbl_1_bss_3078 != 0) {
        fn_800A7D4C(7, &lbl_1_data_AB34[drawStadiumRelated]);
    }
    PSMTXCopy(lbl_1_bss_68FC.mtx10, lbl_1_data_AA54[drawStadiumRelated].mtx);
    fn_800A7D4C(7, &lbl_1_data_AA54[drawStadiumRelated]);
    if (*(u8 *)&lbl_1_data_1F1A != 0) {
        PSMTXCopy(lbl_1_bss_68FC.mtx10, a9e4[drawStadiumRelated].mtx);
        fn_800A7D4C(9, &a9e4[drawStadiumRelated]);
    }
    lbl_803C5090.f1D = 1;
    lbl_803C5090.f0 = 1.0f;
    lbl_803C5090.f4 = 1.0f;
    lbl_803C5090.f17 = 0xFF;
    lbl_803C5090.f8 = 0.0f;
    lbl_803C5090.fC = 0.0f;
    lbl_803C5090.h14 = 0x1C0;
    fn_8003A2C0();
    fn_800A7D4C(0, (u8 *)lbl_1_data_ABA8 + 0xD4 + drawStadiumRelated * 8);
}

// .text:0x000176EC size:0x20
void fn_1_176EC(void) {
    fn_1_1496C();
}

// .text:0x00016978 size:0xD74
void fn_1_16978(void) {
    s32 i;
    switch (currentDrawingItem->state) {
    case 0: {
        DbgScene *d;
        lbl_1_bss_3098 = 0;
        d = (DbgScene *)insertGraphicDrawingFunction(fn_1_10560, 11);
        d->state = 0;
        currentDrawingItem->state++;
        break;
    }
    case 1:
        if (lbl_1_bss_3098 != 0) {
            fn_8004B1B8((void *)lbl_1_bss_3098);
            currentDrawingItem->state++;
        }
        break;
    case 2:
        lbl_1_bss_5F73 = 0;
        currentDrawingItem->state = 4;
        break;
    case 3:
        lbl_1_bss_5F73++;
        if (lbl_1_bss_5F73 == 1) {
            currentDrawingItem->state = 0x1B;
        } else {
            currentDrawingItem->state = 4;
        }
        break;
    case 4:
        hugeAnimStruct.slots[lbl_1_bss_5F73].p8 = ARAMTransfer(
            &lbl_1_data_2398[lbl_1_bss_3074 + lbl_1_bss_68FC.f40[lbl_1_bss_5F73] * 0x13 + lbl_1_bss_6940[lbl_1_bss_5F73].f46], 0, 0, 0);
        currentDrawingItem->state++;
        break;
    case 5:
        if (lbl_803C6CF8.cancel.bytes[1] == 1) {
            currentDrawingItem->state = 6;
        }
        break;
    case 6:
        if (lbl_1_data_2390[lbl_1_bss_5F73 * 7 + 0] != 0) {
            hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[0] = ARAMTransfer(
                &lbl_1_data_2398[lbl_1_bss_3074 + lbl_1_bss_68FC.f40[lbl_1_bss_5F73] * 0x13 + 2], 0, 0, 0);
            currentDrawingItem->state++;
        } else {
            hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[0] = NULL;
            currentDrawingItem->state = 8;
        }
        break;
    case 7:
        if (lbl_803C6CF8.cancel.bytes[1] == 1) {
            ANIMGet((ANIMBank *)hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[0]);
            currentDrawingItem->state++;
        }
        break;
    case 8:
        if (lbl_1_data_2390[lbl_1_bss_5F73 * 7 + 1] != 0) {
            hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[1] = ARAMTransfer(
                &lbl_1_data_2398[lbl_1_bss_3074 + lbl_1_bss_68FC.f40[lbl_1_bss_5F73] * 0x13 + 3], 0, 0, 0);
            currentDrawingItem->state++;
        } else {
            hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[1] = NULL;
            currentDrawingItem->state = 10;
        }
        break;
    case 9:
        if (lbl_803C6CF8.cancel.bytes[1] == 1) {
            ANIMGet((ANIMBank *)hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[1]);
            currentDrawingItem->state++;
        }
        break;
    case 10:
        if (lbl_1_data_2390[lbl_1_bss_5F73 * 7 + 2] != 0) {
            hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[2] = ARAMTransfer(
                &lbl_1_data_2398[lbl_1_bss_3074 + lbl_1_bss_68FC.f40[lbl_1_bss_5F73] * 0x13 + 4], 0, 0, 0);
            currentDrawingItem->state++;
        } else {
            hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[2] = NULL;
            currentDrawingItem->state = 12;
        }
        break;
    case 11:
        if (lbl_803C6CF8.cancel.bytes[1] == 1) {
            ANIMGet((ANIMBank *)hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[2]);
            currentDrawingItem->state++;
        }
        break;
    case 12:
        if (lbl_1_data_2390[lbl_1_bss_5F73 * 7 + 3] != 0) {
            hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[3] = ARAMTransfer(
                &lbl_1_data_2398[lbl_1_bss_3074 + lbl_1_bss_68FC.f40[lbl_1_bss_5F73] * 0x13 + 5], 0, 0, 0);
            currentDrawingItem->state++;
        } else {
            hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[3] = NULL;
            currentDrawingItem->state = 14;
        }
        break;
    case 13:
        if (lbl_803C6CF8.cancel.bytes[1] == 1) {
            ANIMGet((ANIMBank *)hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[3]);
            currentDrawingItem->state++;
        }
        break;
    case 14:
        if (lbl_1_data_2390[lbl_1_bss_5F73 * 7 + 4] != 0) {
            hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[4] = ARAMTransfer(
                &lbl_1_data_2398[lbl_1_bss_3074 + lbl_1_bss_68FC.f40[lbl_1_bss_5F73] * 0x13 + 6], 0, 0, 0);
            currentDrawingItem->state++;
        } else {
            hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[4] = NULL;
            currentDrawingItem->state = 18;
        }
        break;
    case 15:
        if (lbl_803C6CF8.cancel.bytes[1] == 1) {
            ANIMGet((ANIMBank *)hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[4]);
            currentDrawingItem->state++;
        }
        break;
    case 16:
        if (lbl_1_data_2390[lbl_1_bss_5F73 * 7 + 5] != 0) {
            hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[5] = ARAMTransfer(
                &lbl_1_data_2398[lbl_1_bss_3074 + lbl_1_bss_68FC.f40[lbl_1_bss_5F73] * 0x13 + 7], 0, 0, 0);
            currentDrawingItem->state++;
        } else {
            hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[5] = NULL;
            currentDrawingItem->state = 18;
        }
        break;
    case 17:
        if (lbl_803C6CF8.cancel.bytes[1] == 1) {
            ANIMGet((ANIMBank *)hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[5]);
            currentDrawingItem->state++;
        }
        break;
    case 18:
        if (lbl_1_data_2390[lbl_1_bss_5F73 * 7 + 6] != 0) {
            hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[6] = ARAMTransfer(
                &lbl_1_data_2398[lbl_1_bss_3074 + lbl_1_bss_68FC.f40[lbl_1_bss_5F73] * 0x13 + 8], 0, 0, 0);
            currentDrawingItem->state++;
        } else {
            hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[6] = NULL;
            currentDrawingItem->state = currentDrawingItem->state + 1;
        }
        break;
    case 19:
        if (lbl_803C6CF8.cancel.bytes[1] == 1) {
            if (lbl_1_data_2390[lbl_1_bss_5F73 * 7 + 6] != 0) {
                ANIMGet((ANIMBank *)hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[6]);
            }
            currentDrawingItem->state++;
        }
        break;
    case 20:
        if (lbl_1_bss_3070 != 0 && hugeAnimStruct.slots[lbl_1_bss_5F73].p8->f10 != 0) {
            hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[7] = (void *)&lbl_1_bss_6988[lbl_1_bss_5F73];
            if (lbl_1_bss_68FC.f40[lbl_1_bss_5F73] == 0) {
                *(void **)hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[7] = ARAMTransfer(HandPoseEventSetFiles_debug, 0, 0, 0);
                currentDrawingItem->state++;
            } else {
                lbl_1_bss_3070 = 0;
                currentDrawingItem->state = 0x16;
            }
        } else {
            currentDrawingItem->state = 0x16;
        }
        break;
    case 21:
        if (lbl_803C6CF8.cancel.bytes[1] == 1) {
            currentDrawingItem->state++;
        }
        break;
    case 22: {
        s16 v = DBG_A978[lbl_1_bss_68FC.f40[lbl_1_bss_5F73]];
        if (v >= 0) {
            lbl_1_bss_60A0[lbl_1_bss_5F73] = (u32)ARAMTransfer(&DebugCharacterHandFiles[v * 4], 0, 0, 0);
            currentDrawingItem->state++;
        } else {
            currentDrawingItem->state = 3;
        }
        break;
    }
    case 23:
        if (lbl_803C6CF8.cancel.bytes[1] == 1) {
            currentDrawingItem->state = 3;
        }
        break;
    case 24:
        hugeAnimStruct.f2C84 = ARAMTransfer(DebugBallFiles, 0, 0, 0);
        currentDrawingItem->state++;
        break;
    case 25:
        if (lbl_803C6CF8.cancel.bytes[1] == 1) {
            currentDrawingItem->state++;
        }
        break;
    case 26: {
        u32 base = (u32)hugeAnimStruct.f2C84;
        fn_1_D7A4(0);
        for (i = 0; i < 0x50; i++) {
            ((u32 *)hugeAnimStruct.f2C84)[i] = base + ((u32 *)base)[i];
        }
        currentDrawingItem->state = 0x1B;
        break;
    }
    case 27:
        lbl_1_bss_60DC = ARAMTransfer(&lbl_1_data_A940[4], 0, 0, 0);
        currentDrawingItem->state = 0x1C;
        break;
    case 28:
        if (lbl_803C6CF8.cancel.bytes[1] == 1) {
            void *layout;
            void *geo;
            lbl_1_bss_60E0 = ActorObjectInitTable(5);
            for (i = 0; i < 15; i++) {
                if (((u32 *)lbl_1_bss_60DC)[i] != 0) {
                    void *tex;
                    ((u32 *)lbl_1_bss_60DC)[i] += (u32)lbl_1_bss_60DC;
                    switch (i) {
                    case 0:
                    case 3:
                    case 6:
                    case 9:
                    case 12:
                        layout = (void *)((u32 *)lbl_1_bss_60DC)[i];
                        LoadActorLayout(layout);
                        break;
                    case 1:
                    case 4:
                    case 7:
                    case 10:
                    case 13:
                        geo = (void *)((u32 *)lbl_1_bss_60DC)[i];
                        convertGeometryAndSknHeader(geo, NULL);
                        haveActLayoutPointToGeoHeader(layout, geo);
                        break;
                    case 2:
                    case 5:
                    case 8:
                    case 11:
                    case 14:
                        tex = (void *)((u32 *)lbl_1_bss_60DC)[i];
                        convertTextureHeader(tex);
                        UpdateTexturePalettePointers(geo, tex);
                        animateBallRelated(lbl_1_bss_60E0, i / 3, i / 3, layout, 0, 0);
                        break;
                    }
                }
            }
            currentDrawingItem->state = 0x1D;
        }
        break;
    case 29:
        lbl_1_bss_5F73 = 0;
        currentDrawingItem->state = 0;
        currentDrawingItem->func = fn_1_168C8;
        break;
    }
}

// .text:0x000168C8 size:0xB0
void fn_1_168C8(void) {
    DbgScene *s = (DbgScene *)currentDrawingItem;
    if (lbl_1_bss_3084 == 0) {
        lbl_1_bss_3084 = 1;
        s->tick = OSGetTick();
        fn_1_135C0();
        s->tick = OSGetTick() - s->tick;
    } else {
        lbl_1_bss_3084 = 0;
        s->state = 0;
        if (hugeAnimStruct.slots[0].p8->f10 != 0) {
            currentDrawingItem->func = fn_1_1770C;
        } else {
            currentDrawingItem->func = fn_1_1770C;
        }
    }
}

// .text:0x000165E0 size:0x2E8
void fn_1_165E0(void) {
    DbgLight *light = hugeAnimStruct.lights[(s8)lbl_1_bss_5F70];
    s16 step = 0;
    u16 b = BTN_REPEAT;
    if (b & INPUT_BUTTON_LEFT) {
        step = -1;
    } else if (b & INPUT_BUTTON_RIGHT) {
        step = 1;
    } else if (b & INPUT_BUTTON_UP) {
        if (--lbl_1_bss_307C < 0) {
            lbl_1_bss_307C = 9;
        }
    } else if (b & INPUT_BUTTON_DOWN) {
        if (++lbl_1_bss_307C >= 10) {
            lbl_1_bss_307C = 0;
        }
    } else if (BTN_PRESSED & INPUT_BUTTON_B) {
        lbl_1_bss_5F70 = 0;
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 1;
    }
    if (BTN_HELD & INPUT_BUTTON_X) {
        step *= 10;
    }
    switch (lbl_1_bss_307C) {
    case 0:
        lbl_1_bss_5F70 += step;
        if ((s8)lbl_1_bss_5F70 < 0) {
            lbl_1_bss_5F70 = 2;
        } else if ((s8)lbl_1_bss_5F70 >= 3) {
            lbl_1_bss_5F70 = 0;
        }
        break;
    case 1:
        light->r += step;
        if (light->r > 0xFF) {
            light->r = 0;
        }
        break;
    case 2:
        light->g += step;
        if (light->g > 0xFF) {
            light->g = 0;
        }
        break;
    case 3:
        light->b += step;
        if (light->b > 0xFF) {
            light->b = 0;
        }
        break;
    case 4:
        light->f40 += step;
        break;
    case 5:
        light->f44 += step;
        break;
    case 6:
        light->f48 += step;
        break;
    case 7:
        light->f58 += step;
        break;
    case 8:
        light->f5C += step;
        break;
    case 9:
        light->f60 += step;
        break;
    }
}

// .text:0x00016590 size:0x50
u32 fn_1_16590(void) {
    DbgSel *s = &lbl_1_bss_6940[lbl_1_bss_5F73];
    return hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[s->f44]->p4[s->f45][0];
}

// .text:0x00016558 size:0x38
u32 fn_1_16558(s32 a, s32 b) {
    return hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[a]->p4[b][0];
}

#pragma dont_inline on
// .text:0x00001644C
void fn_1_1644C(void) {
    u8 idx = lbl_1_bss_5F73;
    DbgActor *act = hugeAnimStruct.actors[idx];
    s32 i;
    lbl_1_bss_5F69 ^= 1;
    if (act != NULL) {
        if (lbl_1_bss_5F69 == 0) {
            *(void **)((u8 *)&hugeAnimStruct.objs->e[idx] + 0x68) = NULL;
        } else {
            *(void **)((u8 *)&hugeAnimStruct.objs->e[idx] + 0x68) = (u8 *)act + 0x72;
        }
        fn_1_ECF8(lbl_1_bss_5F73, lbl_1_bss_6940[lbl_1_bss_5F73].f44, lbl_1_bss_5F69);
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_67B8[i] != NULL) {
                ((DbgGaugeLink *)lbl_1_bss_67B8[i])->mode = 3;
            }
        }
    }
}

#pragma dont_inline reset

// .text:0x00016400 size:0x4C
void fn_1_16400(s8 delta) {
    u32 n = hugeAnimStruct.slots[lbl_1_bss_5F73].p4->count;
    lbl_1_bss_5F6C = (lbl_1_bss_5F6C + n + delta) % n;
}

// .text:0x000163FC size:0x4
void fn_1_163FC(void) {
}

// .text:0x0001620C size:0x1F0
void fn_1_1620C(void) {
    s32 i = 0;
    do {
        hugeAnimStruct.slots[i].pos.x = 0.0f;
        hugeAnimStruct.slots[i].pos.y = 0.0f;
        hugeAnimStruct.slots[i].pos.z = 10.0f;
        hugeAnimStruct.slots[i].rotX = 0.0f;
        hugeAnimStruct.slots[i].rotY = 0.0f;
        hugeAnimStruct.slots[i].rotZ = 0.0f;
        CTRLSetTranslation((Control *)((u8 *)&hugeAnimStruct.objs->e[i] + 0x10), 0.0f, 0.0f, 0.0f);
        CTRLSetRotation((Control *)((u8 *)&hugeAnimStruct.objs->e[i] + 0x10), 0.0f, 0.0f, 0.0f);
        i++;
    } while (i < 1);
    fn_1_1347C();
}

// .text:0x000161D0 size:0x3C
void fn_1_161D0(void) {
    lbl_1_bss_5F78 ^= 1;
    fn_800B9A9C((void *)lbl_1_bss_5F78, lbl_1_bss_5F74);
}

// .text:0x000160F8 size:0xD8
void fn_1_160F8(s32 dir) {
    f32 step = 0.01f;
    if (BTN_HELD & INPUT_BUTTON_X) {
        step *= 10.0f;
    }
    lbl_1_bss_5F74 += step * dir;
    if (lbl_1_bss_5F74 > 1.0f) {
        lbl_1_bss_5F74 = 0.0f;
    }
    if (lbl_1_bss_5F74 < 0.0f) {
        lbl_1_bss_5F74 = 1.0f;
    }
    fn_800B9A9C((void *)lbl_1_bss_5F78, lbl_1_bss_5F74);
}

// .text:0x000160D8 size:0x20
s32 fn_1_160D8(s8 a, s8 b) {
    if (a == b) {
        return 0xFF0F;
    }
    return 0xFFFF;
}

// .text:0x00015CE0 size:0x3F8
void fn_1_15CE0(void) {
    u16 b = BTN_REPEAT;
    if (b & INPUT_BUTTON_UP) {
        if (--lbl_1_bss_307C < 0) {
            lbl_1_bss_307C = 5;
        }
    } else if (b & INPUT_BUTTON_DOWN) {
        if (++lbl_1_bss_307C >= 6) {
            lbl_1_bss_307C = 0;
        }
    } else if (b & INPUT_BUTTON_LEFT) {
        switch (lbl_1_bss_307C) {
        case 0:
            lbl_1_bss_5F72--;
            if (lbl_1_bss_5F72 >= 2) {
                lbl_1_bss_5F72 = 1;
            }
            break;
        case 2:
            lbl_1_bss_67E0.f118 ^= 1;
            break;
        case 3:
            *(u8 *)&lbl_1_data_1F1A ^= 1;
            break;
        case 4:
            if ((s8)lbl_1_bss_5F62 >= 0) {
                lbl_1_bss_5F62--;
            }
            break;
        case 5:
            if (lbl_1_bss_5F60 > 1) {
                lbl_1_bss_5F60--;
            }
            break;
        }
    } else if (b & INPUT_BUTTON_RIGHT) {
        switch (lbl_1_bss_307C) {
        case 0:
            lbl_1_bss_5F72++;
            if (lbl_1_bss_5F72 >= 2) {
                lbl_1_bss_5F72 = 0;
            }
            break;
        case 2:
            lbl_1_bss_67E0.f118 ^= 1;
            break;
        case 3:
            *(u8 *)&lbl_1_data_1F1A ^= 1;
            break;
        case 4:
            if ((s8)lbl_1_bss_5F62 < 1) {
                lbl_1_bss_5F62++;
            }
            break;
        case 5:
            if (lbl_1_bss_5F60 < 16) {
                lbl_1_bss_5F60++;
            }
            break;
        }
    } else if (b & INPUT_BUTTON_A) {
        if (lbl_1_bss_307C == 1) {
            fn_1_1620C();
        }
    } else if (b & INPUT_BUTTON_B) {
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 1;
    }
}

// .text:0x00015760 size:0x580
void fn_1_15760(void) {
    s32 i;
    lbl_1_bss_5F73 = 0;
    if (lbl_1_bss_5F5C == 0) {
        u16 b = BTN_REPEAT;
        if (b & INPUT_BUTTON_UP) {
            if (--lbl_1_bss_307C < 0) {
                lbl_1_bss_307C = 7;
            }
        } else if (b & INPUT_BUTTON_DOWN) {
            if (++lbl_1_bss_307C >= 8) {
                lbl_1_bss_307C = 0;
            }
        } else if (b & INPUT_BUTTON_LEFT) {
            switch (lbl_1_bss_307C) {
            case 0: {
                u8 old = lbl_1_bss_6940[0].f44;
                u8 k = old;
                do {
                    if (k != 0) {
                        k = k - 1;
                    } else {
                        k = 6;
                    }
                } while (lbl_1_data_2390[k] == 0);
                lbl_1_bss_6940[0].f44 = k;
                if (old != k) {
                    lbl_1_bss_5F5C = 1;
                    lbl_1_bss_6940[0].f45 = 0;
                }
                break;
            }
            case 1: {
                u8 old = lbl_1_bss_6940[0].f45;
                u16 n = *(u16 *)((u8 *)hugeAnimStruct.slots[0].tbl[lbl_1_bss_6940[0].f44] + 0xA);
                if (old != 0) {
                    lbl_1_bss_6940[0].f45 = old - 1;
                } else {
                    lbl_1_bss_6940[0].f45 = n - 1;
                }
                if (old != lbl_1_bss_6940[0].f45) {
                    lbl_1_bss_5F5C = 1;
                }
                break;
            }
            case 2:
                lbl_1_data_ABA4 = lbl_1_data_ABA4 - 0.01f;
                if (lbl_1_data_ABA4 < 0.0f) {
                    lbl_1_data_ABA4 = 0.0f;
                }
                break;
            case 3:
                fn_1_1644C();
                break;
            case 4:
                lbl_1_bss_3081 ^= 1;
                break;
            case 6:
                lbl_1_bss_5F68 ^= 1;
                if (lbl_1_bss_5F68 != 0) {
                    *(f32 *)((u8 *)&hugeAnimStruct.objs->e[0] + 0x5C) = 0.0f;
                    *((u8 *)&hugeAnimStruct.objs->e[0] + 0x59) = 1;
                }
                break;
            case 5:
                if (lbl_1_bss_3216 == 0) {
                    lbl_1_bss_3216 = 3;
                }
                lbl_1_bss_3216--;
                break;
            }
        } else if (b & INPUT_BUTTON_RIGHT) {
            switch (lbl_1_bss_307C) {
            case 0: {
                u8 old = lbl_1_bss_6940[0].f44;
                u8 k = old;
                do {
                    k = k + 1;
                    if (k == 7) {
                        k = 0;
                    }
                } while (lbl_1_data_2390[k] == 0);
                lbl_1_bss_6940[0].f44 = k;
                if (old != k) {
                    lbl_1_bss_5F5C = 1;
                    lbl_1_bss_6940[0].f45 = 0;
                }
                break;
            }
            case 1: {
                u8 old = lbl_1_bss_6940[0].f45;
                u16 n = *(u16 *)((u8 *)hugeAnimStruct.slots[0].tbl[lbl_1_bss_6940[0].f44] + 0xA);
                lbl_1_bss_6940[0].f45 = old + 1;
                if (n == lbl_1_bss_6940[0].f45) {
                    lbl_1_bss_6940[0].f45 = 0;
                }
                if (old != lbl_1_bss_6940[0].f45) {
                    lbl_1_bss_5F5C = 1;
                }
                break;
            }
            case 2:
                lbl_1_data_ABA4 = lbl_1_data_ABA4 + 0.01f;
                break;
            case 3:
                fn_1_1644C();
                break;
            case 4:
                lbl_1_bss_3081 ^= 1;
                break;
            case 6:
                lbl_1_bss_5F68 ^= 1;
                if (lbl_1_bss_5F68 != 0) {
                    *(f32 *)((u8 *)&hugeAnimStruct.objs->e[0] + 0x5C) = 0.0f;
                    *((u8 *)&hugeAnimStruct.objs->e[0] + 0x59) = 1;
                    for (i = 0; i < 5; i++) {
                        if (lbl_1_bss_67B8[i] != NULL) {
                            fn_1_26B7C(lbl_1_bss_67B8[i]);
                        }
                    }
                }
                break;
            case 5:
                lbl_1_bss_3216++;
                if (lbl_1_bss_3216 == 3) {
                    lbl_1_bss_3216 = 0;
                }
                break;
            }
        } else if (b & INPUT_BUTTON_START) {
            fn_1_CC24();
        } else if (b & INPUT_BUTTON_X) {
            if (lbl_1_bss_307C == 6 && (b & INPUT_BUTTON_X) && lbl_1_bss_5F68 != 0) {
                lbl_1_bss_5F64 = lbl_1_data_ABA4;
            }
        } else if (b & INPUT_BUTTON_Y) {
            if (lbl_1_bss_307C == 6 && (b & INPUT_BUTTON_Y) && lbl_1_bss_5F68 != 0) {
                lbl_1_bss_5F64 = -lbl_1_data_ABA4;
            }
        } else if (b & INPUT_BUTTON_A) {
            switch (lbl_1_bss_307C) {
            case 6:
                if ((b & INPUT_BUTTON_A) && lbl_1_bss_5F68 != 0) {
                    lbl_1_bss_5F64 = 1.0f;
                }
                break;
            case 5:
                if (b & INPUT_BUTTON_A) {
                    lbl_1_bss_3214 = 1;
                }
                break;
            }
        } else if (b & INPUT_BUTTON_B) {
            lbl_1_bss_307C = 0;
            lbl_1_bss_5F71 = 1;
        }
    }
    fn_1_D71C(lbl_1_bss_5F73);
}

// .text:0x0001540C size:0x354
void fn_1_1540C(void) {
    s32 base = lbl_1_bss_5F6C;
    s32 span = 0x14;
    s32 top;
    u8 buf[0x28];
    u16 b = 0;
    if (lbl_1_bss_3088 > base) {
        lbl_1_bss_3088 = base;
    } else if (lbl_1_bss_3088 < base - 0x13) {
        lbl_1_bss_3088 = base - 0x13;
    }
    top = lbl_1_bss_3088;
    fn_1_C2DC((DbgTreeNode *)hugeAnimStruct.objs->e[lbl_1_bss_5F73].model->parts[0], (char *)buf, 0, 0x13, 4, &base, &top, &span);
    b = BTN_REPEAT;
    if (b & INPUT_BUTTON_UP) {
        if (--lbl_1_bss_307C < 0) {
            lbl_1_bss_307C = 5;
        }
    } else if (b & INPUT_BUTTON_DOWN) {
        if (++lbl_1_bss_307C >= 6) {
            lbl_1_bss_307C = 0;
        }
    } else if (b & INPUT_BUTTON_LEFT) {
        switch (lbl_1_bss_307C) {
        case 0:
            lbl_1_bss_3080 ^= 1;
            break;
        case 1:
            *(u8 *)lbl_1_data_ABA8 ^= 1;
            break;
        case 2: {
            u32 n = hugeAnimStruct.slots[lbl_1_bss_5F73].p4->count;
            lbl_1_bss_5F6C = (lbl_1_bss_5F6C + n - 1) % n;
            break;
        }
        case 3:
            break;
        case 4:
            if (*(s8 *)lbl_1_data_AC90 >= 0) {
                (*(s8 *)lbl_1_data_AC90)--;
            }
            break;
        case 5:
            fn_1_1644C();
            break;
        }
    } else if (b & INPUT_BUTTON_RIGHT) {
        switch (lbl_1_bss_307C) {
        case 0:
            lbl_1_bss_3080 ^= 1;
            break;
        case 1:
            *(u8 *)lbl_1_data_ABA8 ^= 1;
            break;
        case 2: {
            u32 n = hugeAnimStruct.slots[lbl_1_bss_5F73].p4->count;
            lbl_1_bss_5F6C = (lbl_1_bss_5F6C + n + 1) % n;
            break;
        }
        case 3:
            break;
        case 4:
            if (*(s8 *)lbl_1_data_AC90 < 4) {
                (*(s8 *)lbl_1_data_AC90)++;
            }
            break;
        case 5:
            fn_1_1644C();
            break;
        }
    } else if (b & INPUT_BUTTON_B) {
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 1;
    }
    {
        u16 id = hugeAnimStruct.slots[0].partIdx[36];
        if (id != 0xFFFF) {
            if (*(s8 *)lbl_1_data_AC90 >= 0) {
                DbgModel *m = lbl_1_bss_60E0->e[*(s8 *)lbl_1_data_AC90].model;
                s32 j;
                for (j = 0; j < m->count; j++) {
                    if (m->parts[j]->f14 != 0) {
                        fn_800B2BA8(hugeAnimStruct.objs->e[0].model, id, m, j);
                    }
                }
            } else {
                fn_800B2BA8(hugeAnimStruct.objs->e[0].model, id, 0, 0);
            }
        }
    }
}

// .text:0x000151F8 size:0x214
void fn_1_151F8(void) {
    u16 b = BTN_REPEAT;
    if (b & INPUT_BUTTON_UP) {
        if (--lbl_1_bss_307C < 0) {
            lbl_1_bss_307C = 1;
        }
    } else if (b & INPUT_BUTTON_DOWN) {
        if (++lbl_1_bss_307C >= 2) {
            lbl_1_bss_307C = 0;
        }
    } else if (b & INPUT_BUTTON_LEFT) {
        switch (lbl_1_bss_307C) {
        case 0:
            fn_1_161D0();
            break;
        case 1:
            fn_1_160F8(-1);
            break;
        }
    } else if (b & INPUT_BUTTON_RIGHT) {
        switch (lbl_1_bss_307C) {
        case 0:
            fn_1_161D0();
            break;
        case 1:
            fn_1_160F8(1);
            break;
        }
    } else if (b & INPUT_BUTTON_B) {
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 1;
    }
}

// .text:0x00015170 size:0x88
void fn_1_15170(void) {
    u16 b = BTN_REPEAT;
    if (b & INPUT_BUTTON_B) {
        fn_800AD038(*(void **)(lbl_80366158 + 8));
        currentDrawingItem->state = 0;
        currentDrawingItem->func = fn_1_176EC;
        lbl_1_bss_30B8 = 1;
    } else if (b & INPUT_BUTTON_A) {
        lbl_1_bss_5F71 = 1;
    }
}

// .text:0x00014FB8 size:0x1B8
void fn_1_14FB8(void) {
    DbgSceneB *s = (DbgSceneB *)currentDrawingItem;
    u16 b = BTN_REPEAT;
    if (b & INPUT_BUTTON_UP) {
        if (s->b20 != 0) {
            s->b20--;
        } else {
            s->b20 = 8;
        }
    } else if (b & INPUT_BUTTON_DOWN) {
        s->b20++;
        if (s->b20 == 9) {
            s->b20 = 0;
        }
    } else if (BTN_HELD & INPUT_BUTTON_A) {
        switch (s->b20) {
        case 0:
            if (b & INPUT_BUTTON_A) {
                lbl_1_bss_5F71 = 3;
            }
            break;
        case 1:
            if (b & INPUT_BUTTON_A) {
                lbl_1_bss_5F71 = 4;
            }
            break;
        case 2:
            if (b & INPUT_BUTTON_A) {
                lbl_1_bss_5F71 = 5;
            }
            break;
        case 3:
            if (b & INPUT_BUTTON_A) {
                lbl_1_bss_5F71 = 6;
            }
            break;
        case 4:
            if (BTN_PRESSED & INPUT_BUTTON_A) {
                lbl_1_bss_5F71 = 2;
            }
            break;
        case 5:
            if (BTN_PRESSED & INPUT_BUTTON_A) {
                lbl_1_bss_5F71 = 8;
            }
            break;
        case 6:
            if (BTN_PRESSED & INPUT_BUTTON_A) {
                lbl_1_bss_5F71 = 7;
            }
            break;
        case 7:
            if (b & INPUT_BUTTON_A) {
                lbl_1_bss_5F71 = 9;
            }
            break;
        case 8:
            if (b & INPUT_BUTTON_A) {
                lbl_1_bss_5F71 = 10;
            }
            break;
        }
    } else if (BTN_PRESSED & INPUT_BUTTON_B) {
        lbl_1_bss_5F71 = 0;
        minigamesSetSomePointers();
    }
}

// .text:0x0001496C size:0x64C
void fn_1_1496C(void) {
    DbgSceneB *s = (DbgSceneB *)currentDrawingItem;
    u16 b = BTN_REPEAT;
    u8 i = 0;
    lbl_1_bss_5F73 = i;
    if (b & INPUT_BUTTON_LEFT) {
        if (lbl_1_bss_68FC.f40[0] != 0) {
            do {
                lbl_1_bss_68FC.f40[i]--;
                i++;
            } while (i < 1);
            lbl_1_bss_5F73 = i;
        } else {
            do {
                lbl_1_bss_68FC.f40[i] = 0x35;
                i++;
            } while (i < 1);
            lbl_1_bss_5F73 = i;
        }
    } else if (b & INPUT_BUTTON_RIGHT) {
        do {
            lbl_1_bss_68FC.f40[i]++;
            if (lbl_1_bss_68FC.f40[i] == 0x36) {
                lbl_1_bss_68FC.f40[i] = 0;
            }
            i++;
        } while (i < 1);
        lbl_1_bss_5F73 = i;
    } else {
        u16 p = BTN_PRESSED;
        if (p & INPUT_BUTTON_X) {
            do {
                lbl_1_bss_6940[i].f46 ^= 1;
                i++;
            } while (i < 1);
            lbl_1_bss_5F73 = i;
        } else if (p & INPUT_BUTTON_Y) {
            lbl_1_bss_3074 = 0x402 - lbl_1_bss_3074;
        } else if (p & INPUT_TRIGGER_L) {
            lbl_1_bss_3070 = 1;
        } else if (p & INPUT_TRIGGER_R) {
            lbl_1_bss_3070 = 0;
        }
    }
    if (BTN_PRESSED & INPUT_BUTTON_A) {
        s32 k;
        DbgActor *a0 = hugeAnimStruct.slots;
        memset(a0, 0, 0x204C);
        for (k = 0; k < 13; k++) {
            hugeAnimStruct.actors[k] = a0;
        }
        hugeAnimStruct.actors[0]->f255 = 0;
        hugeAnimStruct.actors[0]->f254 = 0;
        fn_1_1347C();
        fn_1_131E4();
        s->b20 = 0;
        s->state = 0;
        s->func = fn_1_16978;
        s->state = 0;
        lbl_1_bss_5F68 = 0;
        lbl_1_bss_5F64 = 0.0f;
    } else if (BTN_PRESSED & INPUT_BUTTON_B) {
        memset(&hugeAnimStruct, 0, 0x3154);
        lbl_1_bss_3070 = 0;
        fn_800AD038(*(void **)(lbl_80366158 + 8));
        currentDrawingItem->currentDrawingItem->state = 1;
    }
}

// .text:0x00014928 size:0x44
void fn_1_14928(void) {
    fn_800AD038(*(void **)(lbl_80366158 + 8));
    currentDrawingItem->currentDrawingItem->state = 1;
}

// .text:0x000148CC size:0x5C
void fn_1_148CC(void) {
    fn_800AD038(*(void **)(lbl_80366158 + 8));
    currentDrawingItem->state = 0;
    currentDrawingItem->func = fn_1_176EC;
    lbl_1_bss_30B8 = 1;
}

// .text:0x00014888 size:0x44
void fn_1_14888(DbgLightHolder *h) {
    if (lbl_1_bss_67E0.f118 != 0) {
        setLITLightPtr(lbl_1_bss_67E0.light30);
    } else {
        setLITLightPtr(h->light70);
    }
}

// .text:0x00014710 size:0x178
void fn_1_14710(DbgPairObj *o) {
    s32 i;
    u16 *p;
    u16 *tbl;
    for (i = 0; i < 0x78; i++) {
        o->a[i] = i;
    }
    p = lbl_1_data_1DC0;
    do {
        u16 x = o->b[p[0]];
        u16 y = o->b[p[1]];
        if (x != 0xFFFF && y != 0xFFFF) {
            o->a[x] = y;
            o->a[y] = x;
        }
        p += 2;
    } while (p[0] != 0xFFFF);
    switch (lbl_1_bss_68FC.f40[lbl_1_bss_5F73]) {
    case 0x10:
    case 0x2C:
    case 0x2D:
    case 0x2E:
    case 0x2F:
        tbl = lbl_1_data_1E18;
        break;
    default:
        tbl = NULL;
        break;
    }
    if (tbl == NULL) {
        return;
    }
    for (p = tbl; p[0] != 0xFFFF; p += 2) {
        u16 x = o->b[p[0]];
        u16 y = o->b[p[1]];
        if (x != 0xFFFF && y != 0xFFFF) {
            o->a[x] = y;
            o->a[y] = x;
        }
    }
}

static inline void dbgBindActor(DbgActor *src) {
    s32 a, b;
    switch (lbl_1_bss_6940[lbl_1_bss_5F73].f44) {
    case 0:
    case 1:
        a = 1;
        b = 2;
        break;
    default:
        if (lbl_1_bss_5F69 != 0) {
            a = 1;
            b = 4;
        } else {
            a = 3;
            b = 2;
        }
        break;
    }
    hugeAnimStruct.actors[lbl_1_bss_5F73]->ext = (DbgActorExt *)((u8 *)&hugeAnimStruct + lbl_1_bss_5F73 * 0xD4 + 0x140);
    memcpy(hugeAnimStruct.actors[lbl_1_bss_5F73]->ext->blk4, &lbl_1_bss_60EC[a * 0x5C], 0x5C);
    memcpy(hugeAnimStruct.actors[lbl_1_bss_5F73]->ext->blk68, &lbl_1_bss_60EC[b * 0x5C], 0x5C);
    hugeAnimStruct.actors[(u8)lbl_1_bss_5F73]->ext->b60 = lbl_1_bss_5F73;
    hugeAnimStruct.actors[(u8)lbl_1_bss_5F73]->ext->bC4 = lbl_1_bss_5F73;
    hugeAnimStruct.actors[lbl_1_bss_5F73]->ext->bCD = src->f25A;
    hugeAnimStruct.actors[lbl_1_bss_5F73]->ext->bCE = src->f25B;
    hugeAnimStruct.actors[(u8)lbl_1_bss_5F73]->ext->bCF = lbl_1_bss_5F73;
    hugeAnimStruct.actors[(u8)lbl_1_bss_5F73]->ext->bD0 = lbl_1_bss_5F73;
    hugeAnimStruct.actors[lbl_1_bss_5F73]->model = hugeAnimStruct.objs->e[lbl_1_bss_5F73].model;
}

// .text:0x000135C0 size:0x1150
void fn_1_135C0(void) {
    DbgActor *s0;
    s32 i;
    s32 k;
    s32 j;
    void *tex;
    void *layout;
    void *geo;
    void *geoExtra;
    void *anim;
    u8 *entry0;
    initActorArray(13);
    hugeAnimStruct.objs = ActorObjectInitTable(1);
    lbl_1_bss_5F80 = ActorObjectInitTable(1);
    lbl_1_bss_5F7C = ActorObjectInitTable(5);
    j = 0;
    memset(lbl_1_bss_5F88, 0, 0x118);
    s0 = &hugeAnimStruct.slots[0];
    s0->f252 = lbl_1_bss_68FC.f40[0];
    if (j < 1) {
        {
            u32 *p = (u32 *)hugeAnimStruct.slots[j].p8;
            if (p[0] != 0) {
                ((u32 *)hugeAnimStruct.slots[j].p8)[0] = (u32)p + p[0];
            }
            if (p[1] != 0) {
                ((u32 *)hugeAnimStruct.slots[j].p8)[1] = (u32)p + p[1];
            }
            if (p[2] != 0) {
                ((u32 *)hugeAnimStruct.slots[j].p8)[2] = (u32)p + p[2];
            }
            if (p[3] != 0) {
                ((u32 *)hugeAnimStruct.slots[j].p8)[3] = (u32)p + p[3];
            }
            if (p[4] != 0) {
                ((u32 *)hugeAnimStruct.slots[j].p8)[4] = (u32)p + p[4];
            }
        }
        if (DBG_A978[lbl_1_bss_68FC.f40[0]] >= 0) {
            for (i = 0; i < 16; i++) {
                ((u32 *)lbl_1_bss_60A0[j])[i] += lbl_1_bss_60A0[j];
            }
        }
        {
            u32 *p = (u32 *)hugeAnimStruct.slots[j].p8;
            tex = (void *)p[0];
            layout = (void *)p[1];
            geo = (void *)p[2];
            geoExtra = (void *)p[3];
            convertTextureHeader(tex);
            LoadActorLayout(layout);
            convertGeometryAndSknHeader(geo, geoExtra);
            haveActLayoutPointToGeoHeader(layout, geo);
            UpdateTexturePalettePointers(geo, tex);
        }
        if (DBG_A978[lbl_1_bss_68FC.f40[0]] >= 0) {
            for (i = 0; i <= 7; i += 2) {
                void *l2 = ((void **)lbl_1_bss_60A0[j])[i];
                void *g2 = ((void **)lbl_1_bss_60A0[j])[i + 1];
                LoadActorLayout(l2);
                convertGeometryAndSknHeader(g2, NULL);
                haveActLayoutPointToGeoHeader(l2, g2);
                UpdateTexturePalettePointers(g2, tex);
                animateBallRelated(lbl_1_bss_5F7C, (u16)i / 2, (u16)i / 2, l2, 0, 0);
            }
            for (i = 0; i < lbl_1_bss_5F7C->count; i++) {
                ((u8 *)&lbl_1_bss_5F7C->e[i])[0x6C] = 1;
                CTRLSetTranslation((Control *)((u8 *)&lbl_1_bss_5F7C->e[i] + 0x10), (f32)i, 0.0f, 0.0f);
                CTRLSetRotation((Control *)((u8 *)&lbl_1_bss_5F7C->e[i] + 0x10), 0.0f, 0.0f, 0.0f);
            }
        }
    }
    if (j < 1) {
        if (hugeAnimStruct.slots[j].tbl[lbl_1_bss_6940[lbl_1_bss_5F73].f44] == NULL) {
            lbl_1_bss_6940[lbl_1_bss_5F73].f44 = 0;
            while (lbl_1_bss_6940[lbl_1_bss_5F73].f44 < 7) {
                if (hugeAnimStruct.slots[j].tbl[lbl_1_bss_6940[lbl_1_bss_5F73].f44] != NULL) {
                    break;
                }
                lbl_1_bss_6940[lbl_1_bss_5F73].f44++;
            }
        }
    }
    anim = hugeAnimStruct.slots[j].tbl[lbl_1_bss_6940[lbl_1_bss_5F73].f44];
    if (lbl_1_bss_6940[lbl_1_bss_5F73].f45 >= *(u16 *)((u8 *)anim + 0xA)) {
        lbl_1_bss_6940[lbl_1_bss_5F73].f45 = 0;
    }
    characterAndBallDisplayRelated((u8 *)&hugeAnimStruct.objs->e[0], 0, 0, layout, anim, (int)geoExtra);
    dbgSetAnim((u8 *)&hugeAnimStruct.objs->e[lbl_1_bss_5F73], hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[lbl_1_bss_6940[lbl_1_bss_5F73].f44], lbl_1_bss_6940[lbl_1_bss_5F73].f45);
    lbl_1_bss_67CC = (void *)hugeAnimStruct.slots[0].p8->f10;
    if (lbl_1_bss_67CC != NULL && lbl_1_bss_6940[lbl_1_bss_5F73].f46 == 0) {
        adjustInternalPointers(lbl_1_bss_67CC);
        ACTActorRelated(lbl_1_bss_67CC, (u8 *)&hugeAnimStruct.objs->e[0]);
        if (DBG_A978[lbl_1_bss_68FC.f40[0]] >= 0) {
            for (k = 0; k < 4; k++) {
                lbl_1_bss_67D0[k] = ((void **)lbl_1_bss_60A0[0])[8 + k];
                adjustInternalPointers(lbl_1_bss_67D0[k]);
                ACTActorRelated(lbl_1_bss_67D0[k], (u8 *)&lbl_1_bss_5F7C->e[k]);
                if (k + 1 == 4) {
                    *(u32 *)&lbl_1_bss_60EC[k * 0x5C + 0x5C] = ((u32 *)lbl_1_bss_60A0[0])[15];
                } else {
                    *(u32 *)&lbl_1_bss_60EC[k * 0x5C + 0x5C] = ((u32 *)lbl_1_bss_60A0[0])[k + 13];
                    actRelated(lbl_1_bss_67D0[k], &lbl_1_bss_60EC[(k + 1) * 0x5C]);
                    actorRelated(&lbl_1_bss_60EC[(k + 1) * 0x5C], 0, 0);
                }
                lbl_1_bss_67B8[k + 1] = &lbl_1_bss_60EC[(k + 1) * 0x5C + 0xC];
            }
            dbgBindActor(s0);
        }
        if (lbl_1_bss_3070 != 0) {
            *(u32 *)&lbl_1_bss_60EC[0x5C] = ((u32 *)lbl_1_bss_60A0[0])[12];
            actRelated(lbl_1_bss_67CC, lbl_1_bss_60EC);
            actorRelated(lbl_1_bss_60EC, 0, 0);
            lbl_1_bss_67B8[0] = &lbl_1_bss_60EC[0xC];
        }
    } else {
        lbl_1_bss_67B8[0] = NULL;
    }
    {
        DbgModel *mdl = hugeAnimStruct.objs->e[0].model;
        u16 n = mdl->count;
        memset(s0->partIdx, 0xFF, sizeof(s0->partIdx));
        for (i = 0; i < n; i++) {
            u16 id = hugeAnimStruct.objs->e[0].model->parts[i]->h0;
            if (id != 0xFFFF) {
                hugeAnimStruct.slots[0].partIdx[id] = i;
            }
        }
    }
    fn_800BD548((u8 *)&hugeAnimStruct.objs->e[0], 3, hugeAnimStruct.lights[0], hugeAnimStruct.lights[1], hugeAnimStruct.lights[2], hugeAnimStruct.lights[3]);
    hugeAnimStruct.slots[0].pos.x = hugeAnimStruct.slots[0].pos.y = hugeAnimStruct.slots[0].pos.z = 0.0f;
    hugeAnimStruct.slots[0].rotX = hugeAnimStruct.slots[0].rotY = hugeAnimStruct.slots[0].rotZ = 0.0f;
    CTRLSetTranslation((Control *)((u8 *)&hugeAnimStruct.objs->e[0] + 0x10), 0.0f, 0.0f, 0.0f);
    CTRLSetRotation((Control *)((u8 *)&hugeAnimStruct.objs->e[0] + 0x10), 0.0f, 0.0f, 0.0f);
    *(f32 *)((u8 *)&hugeAnimStruct.objs->e[0] + 0x54) = 0.5f;
    *((u8 *)&hugeAnimStruct.objs->e[0] + 0x5A) = 1;
    {
        s32 id = s0->partIdx[3];
        entry0 = (u8 *)&hugeAnimStruct.objs->e[0];
        if (id != 0xFFFF) {
            fn_800B2BA8(*(void **)entry0, id, 0, 0);
            ((DbgModel *)*(void **)entry0)->parts[(u16)id]->fb136 = 1;
        }
        id = s0->partIdx[2];
        if (id != 0xFFFF) {
            fn_800B2BA8(*(void **)entry0, id, 0, 0);
            ((DbgModel *)*(void **)entry0)->parts[(u16)id]->fb136 = 1;
        }
        id = s0->partIdx[1];
        if (id != 0xFFFF) {
            fn_800B2BA8(*(void **)entry0, id, 0, 0);
            ((DbgModel *)*(void **)entry0)->parts[(u16)id]->fb136 = 1;
        }
        id = s0->partIdx[36];
        if (id != 0xFFFF) {
            fn_800B2BA8(*(void **)entry0, id, 0, 0);
        }
        id = s0->partIdx[46];
        if (id != 0xFFFF) {
            fn_800B2BA8(*(void **)entry0, id, 0, 0);
            ((DbgModel *)*(void **)entry0)->parts[(u16)id]->fb136 = 1;
        }
    }
    fn_800B2C08((void *)hugeAnimStruct.objs->e[0].model, 4);
    initShortsHandleCompressedDiskReads(hugeAnimStruct.actors[0]);
    s0->p4 = (void *)hugeAnimStruct.objs->e[0].model;
    s0->pos.x = 0.0f;
    s0->pos.y = 0.0f;
    s0->pos.z = 10.0f;
    *(f32 *)((u8 *)s0 + 0x4C) = 0.5f;
    *((u8 *)s0 + 0x25D) = 1;
    s0->f252 = lbl_1_bss_68FC.f40[0];
    *((u8 *)s0 + 0x25C) = 1;
    *((u8 *)s0 + 0x277) = 0xFF;
    *(void **)((u8 *)&hugeAnimStruct.objs->e[0] + 0x8) = fn_1_14888;
    if (lbl_1_bss_60A4[lbl_1_bss_68FC.f40[0]] != 0) {
        callDSInsertListObject((void *)hugeAnimStruct.objs->e[0].model, s0->partIdx[19]);
        callDSInsertListObject((void *)hugeAnimStruct.objs->e[0].model, s0->partIdx[25]);
        fn_1_ECF8(lbl_1_bss_5F73, 0, 0);
        callDSInsertListObject((void *)hugeAnimStruct.objs->e[0].model, s0->partIdx[36]);
    }
    switch (s0->f252) {
    case 33:
    case 34:
    case 35:
    case 36:
        lbl_1_bss_60E8 = fn_80063010(s0, entry0);
        break;
    case 2:
        lbl_1_bss_60E8 = fn_800638B4(s0, (u8 *)&hugeAnimStruct.objs->e[(s8) * ((u8 *)s0 + 0x255)]);
        break;
    case 19:
        lbl_1_bss_60E8 = fn_8004B7B4(s0, (u8 *)&hugeAnimStruct.objs->e[(s8) * ((u8 *)s0 + 0x255)]);
        break;
    case 20:
    case 43:
        lbl_1_bss_60E8 = fn_800637BC(s0, (u8 *)&hugeAnimStruct.objs->e[(s8) * ((u8 *)s0 + 0x255)]);
        break;
    case 38:
        *((u8 *)hugeAnimStruct.objs->e[(s8) * ((u8 *)s0 + 0x255)].model + 0x99) = 1;
        fn_1_D13C();
        dbgBindActor(&hugeAnimStruct.slots[lbl_1_bss_5F73]);
        break;
    case 41:
        lbl_1_bss_60E8 = fn_800637D4(s0, (u8 *)&hugeAnimStruct.objs->e[(s8) * ((u8 *)s0 + 0x255)]);
        /* fallthrough */
    case 18:
    case 40:
        fn_1_D13C();
        dbgBindActor(&hugeAnimStruct.slots[lbl_1_bss_5F73]);
        break;
    case 14:
    case 37:
        lbl_1_bss_60E8 = fn_80052634(s0, (u8 *)&hugeAnimStruct.objs->e[(s8) * ((u8 *)s0 + 0x255)]);
        break;
    case 16:
    case 44:
    case 45:
    case 46:
    case 47:
        lbl_1_bss_60E8 = fn_80062ED4(s0, (u8 *)&hugeAnimStruct.objs->e[(s8) * ((u8 *)s0 + 0x255)]);
        break;
    default:
        lbl_1_bss_60E8 = 0;
        break;
    }
}

// .text:0x0001347C size:0x144
void fn_1_1347C(void) {
    Mtx44 m;
    lbl_1_bss_67E0.f10C = -0.8f;
    lbl_1_bss_67E0.f108 = 0.0f;
    lbl_1_bss_67E0.f110 = 0.0f;
    lbl_1_bss_67E0.fFC = 0.0f;
    lbl_1_bss_67E0.f100 = 0.0f;
    lbl_1_bss_67E0.f104 = 10.0f;
    C_MTXFrustum(m, -0.000175f, 0.000175f, 0.00025f, -0.00025f, 0.001f, 512.0f);
    GXSetProjection(m, GX_PERSPECTIVE);
    fn_800B806C(0, -240.0f, 240.0f, -320.0f, 320.0f, -512.0f, -0.001f, 1280.0f);
    lbl_1_bss_67E0.f114 = 0;
    lbl_1_bss_67E0.fF8 = 0.0f;
    lbl_1_bss_67E0.fF0 = 0;
    lbl_1_bss_67E0.fF2 = 0;
}

// .text:0x000131E4 size:0x298
void fn_1_131E4(void) {
    static const GXColor cols[3] = {{0xFF, 0xFF, 0xFF, 0xFF}, {0x00, 0x00, 0xFF, 0xFF}, {0xFF, 0x00, 0x00, 0xFF}};
    GXColor c = cols[0];
    LITAlloc((void **)&hugeAnimStruct.lights[0]);
    LITAlloc((void **)&hugeAnimStruct.lights[1]);
    LITAlloc((void **)&hugeAnimStruct.lights[2]);
    LITAlloc((void **)&hugeAnimStruct.lights[3]);
    LITInitAttn(hugeAnimStruct.lights[0], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(hugeAnimStruct.lights[0], 5.0f, -10.0f, 5.0f);
    LITInitDir(hugeAnimStruct.lights[0], 0.0f, 0.0f, 0.0f);
    LITInitColor(hugeAnimStruct.lights[0], c);
    LITInitDir(hugeAnimStruct.lights[0], -5.0f, 0.0f, -5.0f);
    LITInitAttn(hugeAnimStruct.lights[1], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(hugeAnimStruct.lights[1], -5.0f, -10.0f, 0.0f);
    LITInitDir(hugeAnimStruct.lights[1], 0.0f, 0.0f, 0.0f);
    LITInitColor(hugeAnimStruct.lights[1], c);
    LITInitAttn(hugeAnimStruct.lights[2], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(hugeAnimStruct.lights[2], 0.0f, -10.0f, 5.0f);
    LITInitDir(hugeAnimStruct.lights[2], 0.0f, 0.0f, 0.0f);
    LITInitColor(hugeAnimStruct.lights[2], c);
    LITInitAttn(hugeAnimStruct.lights[3], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(hugeAnimStruct.lights[3], 0.0f, -10.0f, -5.0f);
    LITInitDir(hugeAnimStruct.lights[3], 0.0f, 0.0f, 0.0f);
    LITInitColor(hugeAnimStruct.lights[3], c);
}

// .text:0x00012F8C size:0x258
void fn_1_12F8C(DbgActorTbl *objs, Mtx cam) {
    u16 i;
    for (i = 0; i < objs->count; i++) {
        DbgActorEnt *o = &objs->e[i];
        u8 *e = (u8 *)o;
        if (o->model != NULL) {
            DbgModel *model;
            Mtx t;
            s32 r;
            if (e[0x58] != 0) {
                ACTSetAnimation((Actor *)o->model, *(ANIMBank **)(e + 4), NULL, *(u16 *)(e + 0xE), 0.0f, *(f32 *)(e + 0x60));
            }
            if (e[0x59] != 0) {
                setActorAnimFrame(*(void **)e, *(f32 *)(e + 0x5C));
            }
            if (e[0x5A] != 0) {
                fn_800B4C04(*(void **)e, *(f32 *)(e + 0x54));
            }
            if (e[0x5B] & 2) {
                updateBoneParam(*(void **)e, e[0x5B] & 1);
            }
            Set_FUN_800b2b6c(*(void **)e, *(s32 *)(e + 0x68));
            if (*((u8 *)o + 0x6C) != 0) {
                fn_800BDA24(e);
                if (lbl_1_bss_3081 != 0) {
                    Vec v;
                    v.x = lbl_1_bss_67E0.f108 - hugeAnimStruct.slots[i].pos.x;
                    v.y = lbl_1_bss_67E0.f10C - hugeAnimStruct.slots[i].pos.y;
                    v.z = lbl_1_bss_67E0.f110 - hugeAnimStruct.slots[i].pos.z;
                    fn_80026134(0, &v);
                    fn_80026130(0, lbl_1_data_ADC4, lbl_1_data_ADC0);
                }
                if (lbl_1_bss_308C != 0) {
                    lbl_1_bss_308C = 0;
                    for (i = 0; i < ((DbgModel *)*(void **)e)->count; i++) {
                        DbgPart *p = ((DbgModel *)*(void **)e)->parts[i];
                        OSReport("#%3d %f %f %f\n", p->h0, p->f64, p->f68, p->f6C);
                    }
                }
            }
            PSMTXTrans(t, hugeAnimStruct.slots[i].pos.x, hugeAnimStruct.slots[i].pos.y, hugeAnimStruct.slots[i].pos.z);
            PSMTXConcat(cam, t, t);
            model = *(DbgModel **)e;
            r = fn_800B3C04(0, (void *)model, t);
            model->f98 = (model->f98 & 0xFC) | r;
            *((u8 *)o + 0x8C) = 0;
            *((u8 *)o + 0x8D) = 0;
            *((u8 *)o + 0x8E) = 0;
            *((u8 *)o + 0x8F) &= 1;
        }
    }
}

// .text:0x00012F18 size:0x74
void fn_1_12F18(DbgBlob *s) {
    fn_1_12820(hugeAnimStruct.objs, s->mtx8);
    if (DBG_A978[(u8)lbl_1_bss_68FC.f40] >= 0) {
        fn_800BD670(lbl_1_bss_5F7C, s->mtx8);
    }
}

// .text:0x000129D0 size:0x548
void fn_1_129D0(void) {
    DbgActorEnt *obj0;
    f32 speed;
    f32 val;
    s32 k;
    s32 idx;
    fn_1_D4BC();
    fn_1_11C98();
    obj0 = &hugeAnimStruct.objs->e[0];
    CTRLSetTranslation((Control *)((u8 *)obj0 + 0x10), 0.0f, 0.0f, 0.0f);
    CTRLSetRotation((Control *)((u8 *)obj0 + 0x10), 57.295776f * hugeAnimStruct.slots[0].rotX,
                    57.295776f * hugeAnimStruct.slots[0].rotY, 57.295776f * hugeAnimStruct.slots[0].rotZ);
    if (lbl_1_bss_5F68 == 0) {
        speed = lbl_1_data_ABA4;
    } else {
        speed = lbl_1_bss_5F64;
    }
    *(f32 *)((u8 *)obj0 + 0x54) = speed;
    *((u8 *)obj0 + 0x5A) = 1;
    if (lbl_1_bss_67B8[0] != NULL) {
        ((DbgGaugeLink *)lbl_1_bss_67B8[0])->value = speed;
    }
    if (speed != 0.0f && fn_1_D660()) {
        val = fn_1_D71C(0);
        idx = lbl_1_data_A938[lbl_1_bss_6940[lbl_1_bss_5F73].f44] + lbl_1_bss_6940[lbl_1_bss_5F73].f45;
        fn_1_D590((s32)hugeAnimStruct.slots, idx, val);
    }
    lbl_1_bss_5F64 = 0.0f;
    if (lbl_1_bss_5F5C == 0) {
        for (k = 0; k < 4; k++) {
            if (lbl_1_bss_67B8[5 + k] != NULL && lbl_1_bss_67B8[k] != NULL) {
                void *mdl;
                ((DbgGaugeLink *)lbl_1_bss_67B8[k])->value = speed;
                if (fn_80024DB0(lbl_1_bss_67B8[k]) != 0 && lbl_1_bss_67B8[k] != NULL) {
                    ((DbgGaugeLink *)lbl_1_bss_67B8[k])->mode = 3;
                }
                if (k == 0) {
                    mdl = (u8 *)&hugeAnimStruct.objs->e[0];
                } else if (k == 3) {
                    mdl = (u8 *)&lbl_1_bss_5F7C->e[k];
                } else {
                    mdl = (u8 *)&lbl_1_bss_5F7C->e[(k - 1)];
                }
                if (k == 0 || lbl_1_bss_5F69 == 0) {
                    fn_80024FA4(mdl, lbl_1_bss_67B8[5 + k], lbl_1_bss_67B8[k], -1);
                } else if (k == 2) {
                    fn_80024FA4(mdl, lbl_1_bss_67B8[5 + k - 1], lbl_1_bss_67B8[k], -1);
                } else {
                    fn_80024FA4(mdl, lbl_1_bss_67B8[5 + k + 1], lbl_1_bss_67B8[k], -1);
                }
            }
        }
        if (lbl_1_bss_67B8[0] != NULL) {
            memcpy((u8 *)hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[7] + 0x10, lbl_1_bss_67B8[0], 0x20);
        }
    }
    PSMTXCopy(lbl_1_bss_68FC.mtx10, lbl_1_data_AC9C[drawStadiumRelated].mtx);
    fn_800A7D4C(7, &lbl_1_data_AC9C[drawStadiumRelated]);
    if (DBG_A978[lbl_1_bss_68FC.f40[0]] >= 0) {
        fn_800BD8C4(lbl_1_bss_5F7C, lbl_1_bss_68FC.mtx10);
    }
    *((u8 *)&hugeAnimStruct.objs->e[0] + 0x6C) = 1;
    fn_1_12F8C(hugeAnimStruct.objs, lbl_1_bss_68FC.mtx10);
    *((u8 *)&hugeAnimStruct.objs->e[0] + 0x6C) = (lbl_1_bss_3080 == 0) & (lbl_1_bss_5F73 == 0);
    if (hugeAnimStruct.f3083 != 0) {
        fn_80038EC4(&hugeAnimStruct.slots[hugeAnimStruct.f3084], (u8 *)&hugeAnimStruct.objs->e[hugeAnimStruct.f3084], 0);
    }
    fn_8003414C(lbl_1_bss_67E0.mtx0);
}

// .text:0x00012820 size:0x1B0
void fn_1_12820(DbgActorTbl *objs, Mtx cam) {
    Mtx44 proj;
    GXColor col = {0x64, 0x72, 0x6C, 0xFF};
    Mtx t;
    u8 lastLevel = 0xFF;
    u16 i;
    C_MTXFrustum(proj, -0.000175f, 0.000175f, 0.00025f, -0.00025f, 0.001f, 512.0f);
    GXSetProjection(proj, GX_PERSPECTIVE);
    GXSetZMode(1, GX_LEQUAL, 1);
    GXSetCullMode(GX_CULL_BACK);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_OR);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_ALWAYS, 0);
    for (i = 0; i < objs->count; i++) {
        DbgActorEnt *o = &objs->e[i];
        DbgActor *a = &hugeAnimStruct.slots[i];
        if (o->model != NULL) {
            o->model->f98 = 0xFF;
            if (*((u8 *)o + 0x6C) != 0) {
                u8 level = a->f277;
                if (lastLevel != level) {
                    lastLevel = level;
                    if (level == 0xFF) {
                        col.a = 0xFF;
                        adjustLightingParams(0, col);
                    } else {
                        col.a = level;
                        if (level == 0) {
                            continue;
                        }
                        adjustLightingParams(1, col);
                    }
                }
                PSMTXTrans(t, a->pos.x, a->pos.y, a->pos.z);
                PSMTXConcat(cam, t, t);
                sknRelated(&o->model, t);
            }
        }
    }
}

// .text:0x000126CC size:0x154
void fn_1_126CC(void) {
    dbgMoveCamera();
}

// .text:0x000121D4 size:0x4F8
void fn_1_121D4(DbgBuf67E0 *p) {
    switch (p->f114) {
    case 0:
        fn_1_11F08(p);
        break;
    case 1:
        fn_1_11D00(p);
        break;
    }
    fn_80011640(p, p);
    PSVECSubtract((Vec *)&p->f108, (Vec *)&p->fFC, (Vec *)((u8 *)p + 0x88));
    PSVECNormalize((Vec *)((u8 *)p + 0x88), (Vec *)((u8 *)p + 0x88));
    graphics_relatedToVsScreen();
}

// .text:0x00011F08 size:0x2CC
void fn_1_11F08(DbgBuf67E0 *p) {
    Vec v = {0.0f, 0.0f, 100.0f};
    Mtx m1;
    Mtx m2;
    Mtx m3;
    Vec a;
    camera_803c639c_s *cam;
    f32 s;
    f32 c;
    u8 *in = (u8 *)&AtBat_ButtonInput1;
    if (!(BTN_HELD & INPUT_TRIGGER_Z)) {
        p->fF0 -= (s8)in[0x13] * 4;
        p->fF2 += (s8)in[0x12] * 4;
        p->fF4 = (s8)in[0x10] / -256.0f;
        p->fF8 = (s8)in[0x11] * 0.00390625f;
        p->f10C += in[0x15] * 0.0009765625f;
        p->f10C -= in[0x14] * 0.0009765625f;
    }
    a.x = (u16)p->fF0;
    a.z = 0.0f;
    a.y = (u16)p->fF2;
    PSVECScale(&a, 0.0000958738f, &a);
    PSMTXRotRad(m1, 'X', a.x);
    PSMTXRotRad(m2, 'Y', a.y);
    s = m2[0][2];
    c = m2[0][0];
    PSMTXConcat(m2, m1, m3);
    PSMTXMultVec(m3, &v, (Vec *)&p->fFC);
    p->f108 = p->f108 + (p->fF8 * s - p->fF4 * c);
    p->f110 = p->f110 + (p->fF8 * c + p->fF4 * s);
    p->fFC = p->fFC + p->f108;
    p->f100 = p->f100 + p->f10C;
    p->f104 = p->f104 + p->f110;
    makeLookAtMatrix((void *)p, (Vec *)&p->f108, (Vec *)lbl_1_data_AD18, (Vec *)&p->fFC);
    cam = fn_80052768_getCamera(0);
    memcpy(&cam->eye, &p->f108, 0xC);
    memcpy(&cam->target, &p->fFC, 0xC);
}

// .text:0x00011D00 size:0x208
void fn_1_11D00(DbgBuf67E0 *p) {
    Vec v = {0.0f, 0.0f, 100.0f};
    Mtx m1;
    Mtx m2;
    Mtx m3;
    Vec a;
    u8 *in = (u8 *)&AtBat_ButtonInput1;
    if (!(BTN_HELD & INPUT_TRIGGER_Z)) {
        p->fF0 -= (s8)in[0x13] * 4;
        p->fF2 += (s8)in[0x12] * 4;
        p->fF8 += (s8)in[0x11] / 256.0f;
        p->f100 += in[0x15] * 0.0009765625f;
        p->f100 -= in[0x14] * 0.0009765625f;
    }
    a.x = (u16)p->fF0;
    a.z = 0.0f;
    a.y = (u16)p->fF2;
    PSVECScale(&a, 0.0000958738f, &a);
    PSMTXRotRad(m1, 'X', a.x);
    PSMTXRotRad(m2, 'Y', a.y);
    PSMTXConcat(m1, m2, m3);
    v.z = -p->fF8;
    PSMTXMultVec(m3, &v, &v);
    PSVECAdd(&v, (Vec *)&p->fFC, (Vec *)&p->f108);
    PSMTXMultVec(m3, (Vec *)lbl_1_data_AD24, &v);
    makeLookAtMatrix((void *)p, (Vec *)&p->f108, &v, (Vec *)&p->fFC);
}

// .text:0x00011C98 size:0x68
void fn_1_11C98(void) {
    s32 i;
    for (i = 0; i < 3; i++) {
        LITXForm(hugeAnimStruct.lights[i], lbl_1_bss_68FC.mtx10);
    }
}

// .text:0x00011714 size:0x584
void fn_1_11714(DbgBlob *blob) {
    Mtx44 proj;
    Mtx44 proj2;
    f32 scr[8][2];
    s32 n;
    s32 f;
    C_MTXFrustum(proj, -0.000175f, 0.000175f, 0.00025f, -0.00025f, 0.001f, 512.0f);
    GXSetProjection(proj, GX_PERSPECTIVE);
    GXLoadPosMtxImm(blob->mtx8, 0);
    GXSetCurrentMtx(0);
    GXSetColorUpdate(1);
    C_MTXFrustum(proj2, -0.000175f, 0.000175f, 0.00025f, -0.00025f, 0.001f, 512.0f);
    fn_800245EC((camera_803c639c_s *)proj2, lbl_1_bss_68FC.mtx10, (Vec *)lbl_1_data_AD30, &scr[0][0], 8, 1);
    SetDisplayStateTexture(returnTexture(), 0, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetZMode(1, GX_LEQUAL, 1);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2X4, GX_TG_TEX0, GX_IDENTITY, FALSE, GX_PTIDENTITY);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0, FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
    GXBegin(GX_QUADS, GX_VTXFMT0, 24);
    for (n = 0; n < 24; n++) {
        s32 idx = lbl_1_data_AD90[n / 4][n % 4];
        GXWGFifo.f32 = ((Vec *)lbl_1_data_AD30)[idx].x;
        GXWGFifo.f32 = ((Vec *)lbl_1_data_AD30)[idx].y;
        GXWGFifo.f32 = ((Vec *)lbl_1_data_AD30)[idx].z;
        GXColor1u32(lbl_1_data_ADA8[n / 4]);
        GXTexCoord2f32(scr[idx][0], scr[idx][1]);
    }
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetNumTexGens(0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    for (f = 0; f < 6; f++) {
        GXBegin(GX_LINESTRIP, GX_VTXFMT0, 6);
        GXWGFifo.f32 = ((Vec *)lbl_1_data_AD30)[lbl_1_data_AD90[f][0]].x;
        GXWGFifo.f32 = ((Vec *)lbl_1_data_AD30)[lbl_1_data_AD90[f][0]].y;
        GXWGFifo.f32 = ((Vec *)lbl_1_data_AD30)[lbl_1_data_AD90[f][0]].z;
        GXColor1u32(0xFFFFFFFF);
        GXWGFifo.f32 = ((Vec *)lbl_1_data_AD30)[lbl_1_data_AD90[f][1]].x;
        GXWGFifo.f32 = ((Vec *)lbl_1_data_AD30)[lbl_1_data_AD90[f][1]].y;
        GXWGFifo.f32 = ((Vec *)lbl_1_data_AD30)[lbl_1_data_AD90[f][1]].z;
        GXColor1u32(0xFFFFFFFF);
        GXWGFifo.f32 = ((Vec *)lbl_1_data_AD30)[lbl_1_data_AD90[f][2]].x;
        GXWGFifo.f32 = ((Vec *)lbl_1_data_AD30)[lbl_1_data_AD90[f][2]].y;
        GXWGFifo.f32 = ((Vec *)lbl_1_data_AD30)[lbl_1_data_AD90[f][2]].z;
        GXColor1u32(0xFFFFFFFF);
        GXWGFifo.f32 = ((Vec *)lbl_1_data_AD30)[lbl_1_data_AD90[f][3]].x;
        GXWGFifo.f32 = ((Vec *)lbl_1_data_AD30)[lbl_1_data_AD90[f][3]].y;
        GXWGFifo.f32 = ((Vec *)lbl_1_data_AD30)[lbl_1_data_AD90[f][3]].z;
        GXColor1u32(0xFFFFFFFF);
        GXWGFifo.f32 = ((Vec *)lbl_1_data_AD30)[lbl_1_data_AD90[f][0]].x;
        GXWGFifo.f32 = ((Vec *)lbl_1_data_AD30)[lbl_1_data_AD90[f][0]].y;
        GXWGFifo.f32 = ((Vec *)lbl_1_data_AD30)[lbl_1_data_AD90[f][0]].z;
        GXColor1u32(0xFFFFFFFF);
        GXWGFifo.f32 = ((Vec *)lbl_1_data_AD30)[lbl_1_data_AD90[f][2]].x;
        GXWGFifo.f32 = ((Vec *)lbl_1_data_AD30)[lbl_1_data_AD90[f][2]].y;
        GXWGFifo.f32 = ((Vec *)lbl_1_data_AD30)[lbl_1_data_AD90[f][2]].z;
        GXColor1u32(0xFFFFFFFF);
    }
}

// .text:0x000116EC size:0x28
void fn_1_116EC(void *tex) {
    SetDisplayStateTexture(tex, 0, 0);
}

// .text:0x0001125C size:0x490
void fn_1_1125C(DbgBlob *blob) {
    Mtx44 proj;
    s32 i;
    GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    C_MTXFrustum(proj, -0.000175f, 0.000175f, 0.00025f, -0.00025f, 0.001f, 512.0f);
    GXSetProjection(proj, GX_PERSPECTIVE);
    GXLoadPosMtxImm(blob->mtx8, 0);
    GXSetCurrentMtx(0);
    GXSetColorUpdate(1);
    if ((s8)lbl_1_bss_5F62 < 0) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetNumTevStages(1);
        GXSetNumChans(1);
        GXSetNumTexGens(0);
        GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetChanCtrl(GX_COLOR0, FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetChanCtrl(GX_ALPHA0, FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
        for (i = -24; i < 25; i++) {
            f32 f = i;
            GXBegin(GX_LINES, GX_VTXFMT0, 4);
            GXPosition3f32(-24.0f, 0.0f, f);
            GXColor4u8(0, 255, 0, 200);
            GXPosition3f32(24.0f, 0.0f, f);
            GXColor4u8(0, 255, 0, 200);
            GXPosition3f32(f, 0.0f, -24.0f);
            GXColor4u8(0, 255, 0, 200);
            GXPosition3f32(f, 0.0f, 24.0f);
            GXColor4u8(0, 255, 0, 200);
        }
    } else {
        SetDisplayStateTexture((void *)((u8 *)lbl_1_bss_60E4 + (s8)lbl_1_bss_5F62 * 32 + 4), 0, 0);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 0);
        GXSetNumTevStages(1);
        GXSetNumChans(1);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2X4, GX_TG_TEX0, GX_IDENTITY, FALSE, GX_PTIDENTITY);
        GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetChanCtrl(GX_COLOR0, FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetChanCtrl(GX_ALPHA0, FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(-24.0f, 0.0f, -24.0f);
        GXColor1u32(0xFFFFFFFF);
        GXTexCoord2u16(0, 0);
        GXPosition3f32(-24.0f, 0.0f, 24.0f);
        GXColor1u32(0xFFFFFFFF);
        GXTexCoord2u16(0, lbl_1_bss_5F60);
        GXPosition3f32(24.0f, 0.0f, 24.0f);
        GXColor1u32(0xFFFFFFFF);
        GXTexCoord2u16(lbl_1_bss_5F60, lbl_1_bss_5F60);
        GXPosition3f32(24.0f, 0.0f, -24.0f);
        GXColor1u32(0xFFFFFFFF);
        GXTexCoord2u16(lbl_1_bss_5F60, 0);
    }
}

// .text:0x00010E2C size:0x430
void fn_1_10E2C(Mtx m, Mtx cam, u32 c0, u32 c1, u32 c2) {
    GXCullMode cull;
    Mtx cat;
    GXGetCullMode(&cull);
    PSMTXConcat(cam, m, cat);
    GXLoadPosMtxImm(cat, 0);
    GXSetCurrentMtx(0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0, FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(1, GX_ALWAYS, 1);
    GXSetLineWidth(7, GX_TO_ZERO);
    GXBegin(GX_LINES, GX_VTXFMT0, 22);
    GXPosition3f32(-0.01f, 0.0f, 0.0f);
    GXColor1u32(c0);
    GXPosition3f32(0.2f, 0.0f, 0.0f);
    GXColor1u32(c0);
    GXPosition3f32(0.0f, 0.0f, 0.01f);
    GXColor1u32(c0);
    GXPosition3f32(0.2f, 0.0f, 0.0f);
    GXColor1u32(c0);
    GXPosition3f32(0.0f, 0.0f, -0.01f);
    GXColor1u32(c0);
    GXPosition3f32(0.2f, 0.0f, 0.0f);
    GXColor1u32(c0);
    GXPosition3f32(-0.01f, 0.0f, 0.0f);
    GXColor1u32(c0);
    GXPosition3f32(0.0f, 0.0f, 0.01f);
    GXColor1u32(c0);
    GXPosition3f32(-0.01f, 0.0f, 0.0f);
    GXColor1u32(c0);
    GXPosition3f32(0.0f, 0.0f, -0.01f);
    GXColor1u32(c0);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXColor1u32(c1);
    GXPosition3f32(0.0f, 0.05f, 0.0f);
    GXColor1u32(c1);
    GXPosition3f32(-0.005f, 0.0f, 0.0f);
    GXColor1u32(c1);
    GXPosition3f32(0.0f, 0.05f, 0.0f);
    GXColor1u32(c1);
    GXPosition3f32(0.005f, 0.0f, 0.0f);
    GXColor1u32(c1);
    GXPosition3f32(0.0f, 0.05f, 0.0f);
    GXColor1u32(c1);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXColor1u32(c2);
    GXPosition3f32(0.0f, 0.0f, 0.05f);
    GXColor1u32(c2);
    GXPosition3f32(-0.005f, 0.0f, 0.0f);
    GXColor1u32(c2);
    GXPosition3f32(0.0f, 0.0f, 0.05f);
    GXColor1u32(c2);
    GXPosition3f32(0.005f, 0.0f, 0.0f);
    GXColor1u32(c2);
    GXPosition3f32(0.0f, 0.0f, 0.05f);
    GXColor1u32(c2);

    GXSetLineWidth(6, GX_TO_ZERO);
    GXSetCullMode(cull);
    GXSetZMode(1, GX_LEQUAL, 1);
}

// .text:0x00010CEC size:0x140
void fn_1_10CEC(DbgBlob *blob) {
    if (*(u8 *)lbl_1_data_ABA8 == 0) {
        Mtx m;
        Mtx buf;
        s32 i;
        DbgActor *a = &hugeAnimStruct.slots[lbl_1_bss_5F73];
        PSMTXTrans(m, a->pos.x, a->pos.y, a->pos.z);
        PSMTXConcat(blob->mtx8, m, m);
        for (i = 0; i < hugeAnimStruct.objs->e[lbl_1_bss_5F73].model->count; i++) {
            u32 c0, c1, c2;
            if (i != lbl_1_bss_5F6C) {
                c0 = 0x80008080;
                c1 = 0x80800080;
                c2 = 0x00808080;
            } else {
                u8 t = lbl_1_bss_3090++;
                if (t & 0x20) {
                    c0 = 0xFF8080FF;
                    c1 = 0x80FF80FF;
                    c2 = 0x8080FFFF;
                } else {
                    c0 = 0xFFFFFFFF;
                    c1 = 0xFFFFFFFF;
                    c2 = 0xFFFFFFFF;
                }
            }
            fn_800B2C88(hugeAnimStruct.objs->e[lbl_1_bss_5F73].model, i, buf);
            fn_1_10E2C(buf, m, c0, c1, c2);
        }
    }
}

// .text:0x00010ACC size:0x220
void fn_1_10ACC(Mtx m, Vec *p, s32 unused, GXColor *c, f32 size) {
    GXCullMode cull;
    GXGetCullMode(&cull);
    GXLoadPosMtxImm(m, 0);
    GXSetCurrentMtx(0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0, FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(1, GX_ALWAYS, 1);
    GXSetLineWidth(10, GX_TO_ZERO);
    GXBegin(GX_LINES, GX_VTXFMT0, 2);
    GXPosition3f32(p->x, p->y, p->z);
    GXColor4u8(c->r, c->g, c->b, c->a);
    GXPosition3f32(p->x + size, p->y + size, p->z + size);
    GXColor4u8(c->r, c->g, c->b, c->a);
    GXSetLineWidth(6, GX_TO_ZERO);
    GXSetCullMode(cull);
    GXSetZMode(1, GX_LEQUAL, 1);
}

// .text:0x00010AA4 size:0x28
void fn_1_10AA4(DbgGauge *g, f32 v) {
    g->value = v;
    g->dirty = TRUE;
    if (lbl_1_bss_67B8[0] != NULL) {
        ((DbgGaugeLink *)lbl_1_bss_67B8[0])->value = v;
    }
}

// .text:0x000107B8 size:0x2EC
void fn_1_107B8(void) {
    s32 kind = lbl_1_bss_6940[lbl_1_bss_5F73].f44;
    DbgModel *mdl;
    s32 a, b;
    hugeAnimStruct.slots[lbl_1_bss_5F73].f278 = kind == 0;
    switch (kind) {
    case 0:
        hugeAnimStruct.slots[lbl_1_bss_5F73].f254 = 9;
        break;
    case 1:
        hugeAnimStruct.slots[lbl_1_bss_5F73].f254 = 10;
        break;
    case 2:
        hugeAnimStruct.slots[lbl_1_bss_5F73].f254 = 2;
        break;
    case 3:
        hugeAnimStruct.slots[lbl_1_bss_5F73].f254 = 0;
        break;
    case 4:
        hugeAnimStruct.slots[lbl_1_bss_5F73].f254 = 1;
        break;
    default:
        hugeAnimStruct.slots[lbl_1_bss_5F73].f254 = 9;
        break;
    }
    hugeAnimStruct.slots[lbl_1_bss_5F73].h62 = lbl_1_data_A938[kind] + lbl_1_bss_6940[lbl_1_bss_5F73].f45;
    dbgSetAnim((u8 *)&hugeAnimStruct.objs->e[lbl_1_bss_5F73], hugeAnimStruct.slots[lbl_1_bss_5F73].tbl[(u8)kind], lbl_1_bss_6940[lbl_1_bss_5F73].f45);
    fn_1_ECF8(lbl_1_bss_5F73, lbl_1_bss_6940[lbl_1_bss_5F73].f44, lbl_1_bss_5F69);
    lbl_1_bss_5F5C = 0;
    dbgBindActor(&hugeAnimStruct.slots[lbl_1_bss_5F73]);
    removeCurrentDrawingItem();
}

// .text:0x0001073C size:0x7C
void fn_1_1073C(DbgActor *a) {
    Vec v;
    v.x = lbl_1_bss_67E0.f108 - a->pos.x;
    v.y = lbl_1_bss_67E0.f10C - a->pos.y;
    v.z = lbl_1_bss_67E0.f110 - a->pos.z;
    fn_80026134(0, &v);
    fn_80026130(0, lbl_1_data_ADC4, lbl_1_data_ADC0);
}

// .text:0x000106C4 size:0x78
void fn_1_106C4(void) {
    u16 b = BTN_REPEAT;
    if (b & INPUT_BUTTON_UP) {
        return;
    }
    if (b & INPUT_BUTTON_DOWN) {
        return;
    }
    if (b & INPUT_BUTTON_LEFT) {
        lbl_1_bss_3081 ^= 1;
        return;
    }
    if (b & INPUT_BUTTON_RIGHT) {
        lbl_1_bss_3081 ^= 1;
        return;
    }
    if (b & INPUT_BUTTON_A) {
        return;
    }
    if (!(b & INPUT_BUTTON_B)) {
        return;
    }
    lbl_1_bss_307C = 0;
    lbl_1_bss_5F71 = 1;
}

// .text:0x000106B4 size:0x10
void fn_1_106B4(void) {
    lbl_1_bss_3098 = 0;
}

// .text:0x000106A4 size:0x10
u32 fn_1_106A4(void) {
    return lbl_1_bss_3098;
}

// .text:0x00010670 size:0x34
void fn_1_10670(void) {
    DbgScene *d = (DbgScene *)insertGraphicDrawingFunction(fn_1_10560, 11);
    d->state = 0;
}

// .text:0x00010560 size:0x110
void fn_1_10560(void) {
    switch (currentDrawingItem->state) {
    case 0:
        lbl_1_bss_3094 = (u32)ARAMTransfer(teamStarModelFileDescriptorDebug, 0, 0, 0);
        currentDrawingItem->state = 1;
        break;
    case 1:
        if (lbl_803C6CF8.cancel.bytes[1] == 1) {
            lbl_1_bss_3098 = lbl_1_bss_3094 + *(u32 *)lbl_1_bss_3094;
            convertTextureHeader((void *)lbl_1_bss_3098);
            lbl_1_bss_60E4 = (u32)ARAMTransfer(lbl_1_data_A940, 0, 1, 0);
            currentDrawingItem->state = 2;
        }
        break;
    case 2:
        if (lbl_803C6CF8.cancel.bytes[1] == 1) {
            convertTextureHeader((void *)lbl_1_bss_60E4);
            removeCurrentDrawingItem();
        }
        break;
    }
}

// .text:0x00010458 size:0x108
void fn_1_10458(void) {
    if (lbl_1_bss_3098 == 0) {
        if (lbl_1_bss_3094 == 0) {
            DbgScene *d = (DbgScene *)insertGraphicDrawingFunction(fn_1_10560, 11);
            d->state = 0;
        }
    } else {
        u16 b = BTN_REPEAT;
        if (b & INPUT_BUTTON_UP) {
            if (lbl_1_bss_307C != 0) {
                lbl_1_bss_307C--;
            } else {
                lbl_1_bss_307C = 6;
            }
        } else if (b & INPUT_BUTTON_DOWN) {
            lbl_1_bss_307C++;
            if (lbl_1_bss_307C == 7) {
                lbl_1_bss_307C = 0;
            }
        } else if (!(b & INPUT_BUTTON_LEFT) && !(b & INPUT_BUTTON_RIGHT)) {
            if (b & INPUT_BUTTON_A) {
                lbl_1_bss_5F71 = lbl_1_bss_307C + lbl_1_bss_5F71 + 1;
                lbl_1_bss_307C = 0;
            } else if (b & INPUT_BUTTON_B) {
                lbl_1_bss_307C = 0;
                lbl_1_bss_5F71 = 1;
            }
        }
    }
}

// .text:0x00010044 size:0x414
void fn_1_10044(void) {
    u16 rep = BTN_REPEAT;
    s32 step;
    if (rep & INPUT_BUTTON_UP) {
        if (lbl_1_bss_307C != 0) {
            lbl_1_bss_307C--;
        } else {
            lbl_1_bss_307C = 4;
        }
    } else if (rep & INPUT_BUTTON_DOWN) {
        lbl_1_bss_307C++;
        if (lbl_1_bss_307C == 5) {
            lbl_1_bss_307C = 0;
        }
    } else if (rep & INPUT_BUTTON_LEFT) {
        u16 held = BTN_HELD;
        if (held & INPUT_BUTTON_X) {
            step = 10;
        } else if (held & INPUT_BUTTON_Y) {
            step = 100;
        } else {
            step = 1;
        }
        switch (lbl_1_bss_307C) {
        case 0:
            lbl_1_data_ADF4 -= step;
            if (lbl_1_data_ADF4 < 0) {
                lbl_1_data_ADF4 = 0;
            }
            break;
        case 2:
            lbl_1_data_ADF8 -= 0.001f * step;
            if (lbl_1_data_ADF8 < 0.001f) {
                lbl_1_data_ADF8 = 0.001f;
            }
            break;
        case 3:
            lbl_1_data_AE10 -= step;
            if (lbl_1_data_AE10 < 1) {
                lbl_1_data_AE10 = 1;
            }
            break;
        case 4:
            lbl_1_data_AE12 = (lbl_1_data_AE12 - step) & 0xFFF;
            break;
        }
    } else if (rep & INPUT_BUTTON_RIGHT) {
        u16 held = BTN_HELD;
        if (held & INPUT_BUTTON_X) {
            step = 10;
        } else if (held & INPUT_BUTTON_Y) {
            step = 100;
        } else {
            step = 1;
        }
        switch (lbl_1_bss_307C) {
        case 0:
            lbl_1_data_ADF4 += step;
            if (lbl_1_data_ADF4 >= 0x1400) {
                lbl_1_data_ADF4 = 0x1400;
            }
            break;
        case 2:
            lbl_1_data_ADF8 += 0.001f * step;
            if (lbl_1_data_ADF8 > 10.0f) {
                lbl_1_data_ADF8 = 10.0f;
            }
            break;
        case 3:
            lbl_1_data_AE10 += step;
            if (lbl_1_data_AE10 > 0x200) {
                lbl_1_data_AE10 = 0x200;
            }
            break;
        case 4:
            lbl_1_data_AE12 = (lbl_1_data_AE12 + step) & 0xFFF;
            break;
        }
    } else if (BTN_HELD & INPUT_BUTTON_A) {
        if (BTN_PRESSED & INPUT_BUTTON_A) {
            Mtx m1;
            Mtx m2;
            PSMTXRotRad(m1, 'x', 0.01745329238474369 * (360.0 * lbl_1_data_AE10 / 4096.0));
            lbl_1_data_AE14.x = 0.0f;
            lbl_1_data_AE14.y = -1.0f;
            lbl_1_data_AE14.z = 0.0f;
            PSMTXRotRad(m2, 'y', 0.01745329238474369 * (360.0 * lbl_1_data_AE12 / 4096.0));
            PSMTXConcat(m2, m1, m1);
            PSMTXMultVec(m1, &lbl_1_data_AE14, &lbl_1_data_AE14);
            fn_800330CC(lbl_1_data_ADF4, lbl_1_data_ADF0, &lbl_1_data_AE04, &lbl_1_data_AE14,
                        lbl_1_data_ADF8, lbl_1_data_ADFC, lbl_1_data_AE00, 0);
        }
    } else if (BTN_PRESSED & INPUT_BUTTON_B) {
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 10;
    }
}

// .text:0x0000FB98 size:0x4AC
void fn_1_FB98(void) {
    u16 rep = BTN_REPEAT;
    s32 step;
    if (rep & INPUT_BUTTON_UP) {
        if (lbl_1_bss_307C != 0) {
            lbl_1_bss_307C--;
        } else {
            lbl_1_bss_307C = 7;
        }
    } else if (rep & INPUT_BUTTON_DOWN) {
        lbl_1_bss_307C++;
        if (lbl_1_bss_307C == 8) {
            lbl_1_bss_307C = 0;
        }
    } else if (rep & INPUT_BUTTON_LEFT) {
        u16 held = BTN_HELD;
        if (held & INPUT_BUTTON_X) {
            step = 10;
        } else if (held & INPUT_BUTTON_Y) {
            step = 100;
        } else {
            step = 1;
        }
        switch (lbl_1_bss_307C) {
        case 0:
            if (--lbl_1_bss_309C < 0) {
                lbl_1_bss_309C = 13;
            }
            break;
        case 1:
            lbl_1_data_F0A0 -= 0.1 * step;
            break;
        case 2:
            lbl_1_data_F08C[0] -= 0.0001 * step;
            break;
        case 3:
            lbl_1_data_F08C[1] -= 0.0001 * step;
            break;
        case 4:
            lbl_1_data_F08C[2] -= 0.0001 * step;
            break;
        case 5:
            lbl_1_data_F08C[3] -= 0.0001 * step;
            break;
        case 6:
            lbl_1_data_F084 -= step;
            if (lbl_1_data_F084 < 1) {
                lbl_1_data_F084 = 1;
            }
            break;
        case 7:
            lbl_1_data_F088 -= step;
            if (lbl_1_data_F088 < 0) {
                lbl_1_data_F088 = 0;
            }
            break;
        }
    } else if (rep & INPUT_BUTTON_RIGHT) {
        u16 held = BTN_HELD;
        if (held & INPUT_BUTTON_X) {
            step = 10;
        } else if (held & INPUT_BUTTON_Y) {
            step = 100;
        } else {
            step = 1;
        }
        switch (lbl_1_bss_307C) {
        case 0:
            if (++lbl_1_bss_309C >= 14) {
                lbl_1_bss_309C = 0;
            }
            break;
        case 1:
            lbl_1_data_F0A0 += 0.1 * step;
            break;
        case 2:
            lbl_1_data_F08C[0] += 0.0001 * step;
            break;
        case 3:
            lbl_1_data_F08C[1] += 0.0001 * step;
            break;
        case 4:
            lbl_1_data_F08C[2] += 0.0001 * step;
            break;
        case 5:
            lbl_1_data_F08C[3] += 0.0001 * step;
            break;
        case 6:
            lbl_1_data_F084 += step;
            break;
        case 7:
            lbl_1_data_F088 += step;
            if (lbl_1_data_F088 > 0xFF) {
                lbl_1_data_F088 = 0xFF;
            }
            break;
        }
    } else if (BTN_HELD & INPUT_BUTTON_A) {
        if (BTN_PRESSED & INPUT_BUTTON_A) {
            lbl_1_bss_30A0 = (lbl_1_bss_30A0 + 1) % 16;
        }
    } else if (BTN_REPEAT & INPUT_BUTTON_B) {
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 10;
    }
}

// .text:0x0000F798 size:0x400
void fn_1_F798(s32 *vals, u8 *map, s32 n) {
    s32 s, m, l;
    u16 held = BTN_HELD;
    u16 rep;
    u8 v;
    if (held & INPUT_BUTTON_X) {
        s = 10;
        m = 100;
        l = 10000;
    } else if (held & INPUT_BUTTON_Y) {
        s = 20;
        m = 10000;
        l = 1000000;
    } else {
        s = 1;
        m = 1000;
        l = 100000;
    }
    rep = BTN_REPEAT;
    if (rep & INPUT_BUTTON_UP) {
        if (lbl_1_bss_307C != 0) {
            lbl_1_bss_307C--;
        } else {
            lbl_1_bss_307C = n - 1;
        }
        return;
    }
    if (rep & INPUT_BUTTON_DOWN) {
        lbl_1_bss_307C++;
        if (lbl_1_bss_307C == n) {
            lbl_1_bss_307C = 0;
        }
        return;
    }
    if (rep & INPUT_BUTTON_LEFT) {
        v = map[lbl_1_bss_307C];
        switch (v) {
        case 1:
            vals[v] = (vals[v] + 0x29) % 0x2A;
            break;
        case 2:
            vals[2] -= s;
            if (vals[2] < 1) {
                vals[2] = 1;
            }
            break;
        case 3:
        case 4:
        case 5:
        case 8:
        case 9:
        case 20:
            if (vals[v] - m > 0) {
                vals[v] -= m;
            }
            break;
        case 6:
            vals[6] -= s;
            if (vals[6] < 1) {
                vals[6] = 1;
            }
            if (vals[7] > vals[6]) {
                vals[7] = vals[6];
            }
            break;
        case 7:
        case 11:
        case 21:
        case 22:
            vals[v] -= s;
            if (vals[map[lbl_1_bss_307C]] < 0) {
                vals[map[lbl_1_bss_307C]] = 0;
            }
            break;
        case 10:
            vals[v] ^= 1;
            break;
        case 12:
        case 13:
            vals[v] -= l;
            if (vals[map[lbl_1_bss_307C]] < 0) {
                vals[map[lbl_1_bss_307C]] = 0;
            }
            break;
        case 23:
        case 24:
            vals[v] -= m;
            break;
        case 14:
        case 15:
            vals[v] -= l;
            /* fallthrough */
        case 16: {
            s32 c = (vals[16] >> 8) & 0xFF;
            c -= s;
            if (c < 0) {
                c = 0;
            }
            vals[16] = c * 0x1010100;
            break;
        }
        }
    } else if (rep & INPUT_BUTTON_RIGHT) {
        v = map[lbl_1_bss_307C];
        switch (v) {
        case 1:
            vals[v] = (vals[v] + 1) % 0x2A;
            break;
        case 2:
            vals[2] += s;
            break;
        case 3:
        case 4:
        case 5:
        case 8:
        case 9:
        case 20:
            vals[v] += m;
            break;
        case 6:
            vals[6] += s;
            break;
        case 7:
            vals[7] += s;
            if (vals[7] > vals[6]) {
                vals[7] = vals[6];
            }
            break;
        case 11:
        case 21:
            vals[v] += s;
            if (vals[map[lbl_1_bss_307C]] > 0xFF) {
                vals[map[lbl_1_bss_307C]] = 0xFF;
            }
            break;
        case 22:
            vals[v] += s;
            break;
        case 10:
            vals[v] ^= 1;
            break;
        case 12:
        case 13:
            vals[v] += l;
            break;
        case 23:
        case 24:
            vals[v] += m;
            break;
        case 14:
        case 15:
            vals[v] += l;
            break;
        case 16: {
            s32 c = (vals[16] >> 8) & 0xFF;
            c += s;
            if (c > 0xFF) {
                c = 0xFF;
            }
            vals[16] = c * 0x1010100;
            break;
        }
        }
    }
}

// .text:0x0000F6E4 size:0xB4
void fn_1_F6E4(void) {
    Vec v = {0.0f, 0.0f, 10.0f};
    s32 *p = lbl_1_data_F0BC;
    fn_1_F798(p, lbl_1_data_F0A8, 12);
    if (BTN_REPEAT & INPUT_BUTTON_A) {
        p[0] = lbl_1_bss_3098;
        fn_80031CA4(&v, p);
    } else if (BTN_REPEAT & INPUT_BUTTON_B) {
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 10;
    }
}

static struct {
    u8 map[16];
    const char *names[3];
} lbl_1_data_F284 = {
    {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10},
    {"Fire", "Sub Fire", "Smoke"},
};

static s32 lbl_1_data_F2A0[21] = {
    0x0, 0x19, 0x64, 0x28, 0x3C, 0x4650, 0x4E20, -2000000,
    0x1E8480, 0x13880, 0x186A0, 0xC8, -1, 0x0, 0x0, 0x1,
    0x0, 0x0, 0x0, 0x0, 0x0,
};

static s32 lbl_1_data_F2F4[120] = {
    0x54455354, 0x0, 0x0, 0x0, 0x1370000, 0x1BFFFE, 0x11E0000, 0xFFFE,
    0x11E0000, 0xFFFE, 0x11E0000, 0xFFFE, 0x11E0000, 0xFFFE, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x54455354, 0x0, 0x0, 0x0,
    0x11E0000, 0xFFFE, 0x1080000, 0x2FFFE, 0x1090000, 0x5FFFE, 0x1150000, 0x3FFFE,
    0x11E0000, 0xFFFE, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x54455354, 0x0, 0x0, 0x0, 0x11E0000, 0xFFFE, 0x11E0000, 0x1FFFE,
    0x1280000, 0xAFFFE, 0x1090000, 0x8FFFE, 0x1110000, 0x9FFFE, 0x10A0000, 0x4FFFE,
    0x11E0000, 0xFFFE, 0x0, 0x0, 0x54455354, 0x0, 0x0, 0x0,
    0x11E0000, 0xFFFE, 0x1050000, 0xBFFFE, 0x1280000, 0xCFFFE, 0x10F0000, 0xDFFFE,
    0x11E0000, 0xFFFE, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x54455354, 0x0, 0x0, 0x0, 0x11E0000, 0xFFFE, 0x11A0000, 0x7FFFE,
    0x11E0000, 0xFFFE, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
};

static DbgRowTbl lbl_1_data_F4D4 = {0, 0, (DbgRow *)lbl_1_data_F2F4};

// .text:0x0000F50C size:0x1D8
void fn_1_F50C(void) {
    DbgSceneP *s = (DbgSceneP *)currentDrawingItem;
    DbgActor *a = &hugeAnimStruct.slots[lbl_1_bss_5F73];
    if (a != NULL) {
        a->pos.x = s->pos.x;
        a->pos.y = s->pos.y;
        a->pos.z = s->pos.z;
    }
    fn_80030D88(&s->pos, &s->vel, lbl_1_data_F10C, 5);
    if (s->b3E != 0) {
        s->b3E = 0;
        if (s->b3F != 0) {
            Vec p;
            getAnimRelatedCoordinates(0, 0x1E, (VecXYZ *)&p);
            p.y = 0.0f;
            fn_8002F258(&p, s->w38, lbl_1_data_F174[0]);
            getAnimRelatedCoordinates(0, 0x22, (VecXYZ *)&p);
            p.y = 0.0f;
            fn_8002F258(&p, s->w38 + 1, lbl_1_data_F174[0]);
        } else {
            fn_8002F258(&s->pos, s->w38, lbl_1_data_F174[0]);
        }
    } else {
        if (s->b3F != 0) {
            Vec p;
            getAnimRelatedCoordinates(0, 0x1E, (VecXYZ *)&p);
            p.y = 0.0f;
            fn_8002F1AC(&p, s->w38);
            getAnimRelatedCoordinates(0, 0x22, (VecXYZ *)&p);
            p.y = 0.0f;
            fn_8002F1AC(&p, s->w38 + 1);
        } else {
            fn_8002F1AC(&s->pos, s->w38);
        }
    }
    PSVECAdd(&s->vel, &s->acc, &s->vel);
    PSVECAdd(&s->pos, &s->vel, &s->pos);
    if (--s->h3C == 0) {
        removeCurrentDrawingItem();
    }
}

// .text:0x0000F37C size:0x190
void fn_1_F37C(void) {
    fn_1_F798(lbl_1_data_F10C, lbl_1_data_F0A8, 18);
    if (BTN_REPEAT & (INPUT_BUTTON_A | INPUT_BUTTON_START)) {
        DbgSceneP *d;
        u32 v = lbl_1_bss_3098;
        lbl_1_data_F10C[0] = v;
        lbl_1_data_F174[0][0] = v;
        lbl_1_data_F174[0][1] = 5;
        d = (DbgSceneP *)insertGraphicDrawingFunction(fn_1_F50C, currentDrawingItem->priority + 1);
        d->pos.x = 0.0f;
        d->pos.y = 0.0f;
        d->pos.z = 10.0f;
        d->vel.x = 0.0f;
        d->vel.y = 0.0f;
        d->vel.z = (s32)lbl_1_data_F10C[0x5C / 4] / 100000.0f;
        d->acc.x = 0.0f;
        d->acc.y = 0.0f;
        d->acc.z = (s32)lbl_1_data_F10C[0x60 / 4] / 100000.0f;
        d->h3C = 0x20;
        d->b3E = 1;
        d->w38 = lbl_1_bss_30A4;
        lbl_1_bss_30A4 += 2;
        d->b3F = (BTN_REPEAT >> 12) & 1;
    } else if (BTN_REPEAT & INPUT_BUTTON_B) {
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 10;
    }
}

// .text:0x0000F2F8 size:0x84
void fn_1_F2F8(void) {
    u16 b = BTN_REPEAT;
    if (b & INPUT_BUTTON_A) {
        lbl_80108B90[0] = lbl_1_bss_3098;
        fn_800324EC(lbl_1_data_F17C[0], 0, -1);
    } else if (b & INPUT_BUTTON_B) {
        lbl_80108B90[0] = 0;
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 10;
    }
}

// .text:0x0000F1D8 size:0x120
void fn_1_F1D8(void) {
    DbgSceneT *s = (DbgSceneT *)currentDrawingItem;
    DbgActor *a = hugeAnimStruct.actors[lbl_1_bss_5F73];
    Vec p;
    Control ctl;
    Mtx m;
    Vec v;
    getAnimRelatedCoordinates(0, s->w24, (VecXYZ *)&p);
    ctl.type = 0;
    CTRLSetRotation(&ctl, a->rotX, a->rotY, a->rotZ);
    CTRLBuildMatrix(&ctl, m);
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = 1.0f;
    PSMTXMultVec(m, &v, &v);
    fn_80030D88(&p, &v, lbl_1_data_F278[0], 5);
    fn_80030D88(&p, &v, lbl_1_data_F278[1], 5);
    fn_80030D88(&p, &v, lbl_1_data_F278[2], 5);
    if (--s->w20 == 0) {
        removeCurrentDrawingItem();
    }
}

// .text:0x0000F0D0 size:0x108
void fn_1_F0D0(void) {
    fn_1_F798(lbl_1_data_F278[lbl_1_bss_30A8], lbl_1_data_F284.map, 16);
    if (BTN_REPEAT & INPUT_BUTTON_START) {
        lbl_1_bss_30A8 = (lbl_1_bss_30A8 + 1) % 3;
    } else if (BTN_HELD & INPUT_BUTTON_A) {
        if (BTN_PRESSED & INPUT_BUTTON_A) {
            u32 v = lbl_1_bss_3098;
            DbgSceneT *d;
            lbl_1_data_F278[2][0] = v;
            lbl_1_data_F278[1][0] = v;
            lbl_1_data_F278[0][0] = v;
            d = (DbgSceneT *)insertGraphicDrawingFunction(fn_1_F1D8, 0);
            d->w20 = 0xF0;
            d->w24 = 4;
        }
    } else if (BTN_REPEAT & INPUT_BUTTON_B) {
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 10;
    }
}

// .text:0x0000F040 size:0x90
void fn_1_F040(void) {
    Vec v = {0.0f, -5.0f, 0.0f};
    u16 b = BTN_REPEAT;
    if (b & INPUT_BUTTON_A) {
        lbl_1_data_F2A0[0] = lbl_1_bss_3098;
        fn_8002955C(&v, 0);
    } else if (b & INPUT_BUTTON_B) {
        lbl_1_bss_307C = 0;
        lbl_1_bss_5F71 = 10;
    }
}

static const char *lbl_1_data_F4DC[3] = {"OFF", "ON", "NEXT LOOP"};

static u16 lbl_1_data_F4E8[8] = {
    0x0014, 0x001A, 0x003C, 0x003D, 0x003C, 0x003D, 0x004A, 0x004B,
};

static DbgDrawRow lbl_1_data_F4F8[2] = {
    {0, (void *)fn_1_C9E0},
    {0, (void *)fn_1_C9E0},
};

static f32 lbl_1_data_F568 = 0.5f;

static u16 lbl_1_data_F56C = 0x14;

static u16 lbl_1_data_F56E = 0x1A;

static f32 lbl_1_data_F570 = 1.0f;
static u32 lbl_1_data_F574 = 0x80;
static f32 lbl_1_data_F578 = 16777216.0f;
static f32 lbl_1_data_F57C = 16777215.0f;
static u32 lbl_1_data_F580 = 0xFFFF00C0;
static u32 lbl_1_data_F584 = 0xFFFF0000;

// .text:0x0000ECF8 size:0x348
void fn_1_ECF8(s32 idx, s32 kind, s32 flag) {
    s32 a, b;
    u16 fa, fb;
    s32 i;
    if (lbl_1_bss_60A4[lbl_1_bss_68FC.f40[idx]] != 0) {
        fa = hugeAnimStruct.slots[idx].partIdx[19];
        fb = hugeAnimStruct.slots[idx].partIdx[25];
        switch (kind) {
        case 0:
        case 1:
        case 5:
        case 6:
            a = 1;
            b = 2;
            break;
        default:
            if (flag != 0) {
                a = 1;
                b = 4;
            } else {
                a = 3;
                b = 2;
            }
            break;
        }
        {
            for (i = 0; i < lbl_1_bss_5F7C->e[a - 1].model->count; i++) {
                if (lbl_1_bss_5F7C->e[a - 1].model->parts[i]->f14 != 0) {
                    fn_800B2BA8(((DbgActorTbl *)hugeAnimStruct.objs)->e[idx].model, fa, lbl_1_bss_5F7C->e[a - 1].model, i);
                    break;
                }
            }
        }
        {
            for (i = 0; i < lbl_1_bss_5F7C->e[b - 1].model->count; i++) {
                if (lbl_1_bss_5F7C->e[b - 1].model->parts[i]->f14 != 0) {
                    fn_800B2BA8(((DbgActorTbl *)hugeAnimStruct.objs)->e[idx].model, fb, lbl_1_bss_5F7C->e[b - 1].model, i);
                    break;
                }
            }
        }
        dbgBindActor(&hugeAnimStruct.slots[lbl_1_bss_5F73]);
    }
}

// .text:0x0000EA20 size:0x2D8
void fn_1_EA20(void) {
    switch (lbl_1_bss_30B0) {
    case 0: {
        DbgActor *a;
        u32 (*arr)[3];
        s32 i;
        u8 *obj = (u8 *)&hugeAnimStruct.objs->e[lbl_1_bss_5F73];
        lbl_1_bss_5F68 = 1;
        lbl_1_bss_5F64 = 0.0f;
        *(f32 *)(obj + 0x5C) = 0.0f;
        *(u8 *)(obj + 0x59) = 1;
        lbl_1_bss_30B0 = 1;
        lbl_1_bss_5F58 = 0;
        a = &hugeAnimStruct.slots[lbl_1_bss_5F73];
        arr = a->tbl[lbl_1_bss_6940[lbl_1_bss_5F73].f44]->p4;
        for (i = 0; i < *(u16 *)((u8 *)arr + lbl_1_bss_6940[lbl_1_bss_5F73].f45 * 12 + 8); i++) {
            f32 f = ((f32 *)arr[lbl_1_bss_6940[lbl_1_bss_5F73].f45][1])[i * 4];
            if ((f32)lbl_1_bss_5F58 < f) {
                lbl_1_bss_5F58 = (s32)f;
            }
        }
        break;
    }
    case 1:
        if (BTN_PRESSED & INPUT_BUTTON_B) {
            lbl_1_bss_30B0 = 0;
            lbl_1_bss_5F71 = 1;
        } else if (BTN_REPEAT & INPUT_BUTTON_LEFT) {
            lbl_1_bss_30B4--;
            if (lbl_1_bss_30B4 < 0) {
                lbl_1_bss_30B4 = lbl_1_bss_5F58 - 2;
            }
        } else if (BTN_REPEAT & INPUT_BUTTON_RIGHT) {
            lbl_1_bss_30B4++;
            if (lbl_1_bss_30B4 > lbl_1_bss_5F58 - 2) {
                lbl_1_bss_30B4 = 0;
            }
        } else if (BTN_REPEAT & INPUT_BUTTON_A) {
            lbl_1_bss_5F68 = 0;
            fn_80039A4C();
            hugeAnimStruct.f3084 = lbl_1_bss_5F73;
            lbl_1_bss_30B0 = 2;
            hugeAnimStruct.actors[lbl_1_bss_5F73] = &hugeAnimStruct.slots[lbl_1_bss_5F73];
        }
        break;
    default:
        if (lbl_1_bss_30B0 - 2 == lbl_1_bss_30B4 * 2) {
            hugeAnimStruct.f3083 = 1;
        }
        lbl_1_bss_30B0++;
        if (BTN_PRESSED & INPUT_BUTTON_B) {
            lbl_1_bss_30B0 = 0;
            hugeAnimStruct.f3083 = 0;
        } else if (BTN_PRESSED & INPUT_BUTTON_A) {
            u8 *obj = (u8 *)&hugeAnimStruct.objs->e[lbl_1_bss_5F73];
            *(f32 *)(obj + 0x5C) = 0.0f;
            *(u8 *)(obj + 0x59) = 1;
            fn_80039A4C();
            hugeAnimStruct.f3084 = lbl_1_bss_5F73;
            lbl_1_bss_30B0 = 2;
            hugeAnimStruct.actors[lbl_1_bss_5F73] = &hugeAnimStruct.slots[lbl_1_bss_5F73];
        }
        break;
    }
}

// .text:0x0000E9F8 size:0x28
void fn_1_E9F8(DbgModel *m, s32 start, s32 count) {
    s32 i;
    for (i = 0; i < count; i++) {
        start++;
        if (start == m->count) {
            start = 0;
        }
    }
}

// .text:0x0000E8D4 size:0x124
void fn_1_E8D4(void) {
    fn_1_D7A4(0);
    while ((s8)lbl_1_data_F4D4.tbl[lbl_1_data_F4D4.cur].name[0] != 0) {
        lbl_1_data_F4D4.cur++;
    }
}

// .text:0x0000E098 size:0x83C
void fn_1_E098(void) {
    DbgSlotEnt *e = lbl_1_bss_3218;
    s32 i;
    s32 off = 0;
    for (i = 0; i < 11; i++, e++, off += 0x20) {
        switch (i) {
        case 8:
            if (i == lbl_1_bss_30B6) {
                u16 rep = BTN_REPEAT;
                s16 prev = lbl_1_data_F4D4.sel;
                if (rep & INPUT_BUTTON_LEFT) {
                    if (prev == 0) {
                        lbl_1_data_F4D4.sel = lbl_1_data_F4D4.cur;
                    }
                    lbl_1_data_F4D4.sel--;
                } else if (rep & INPUT_BUTTON_RIGHT) {
                    lbl_1_data_F4D4.sel = prev + 1;
                    if (lbl_1_data_F4D4.sel == lbl_1_data_F4D4.cur) {
                        lbl_1_data_F4D4.sel = 0;
                    }
                }
                if (prev != lbl_1_data_F4D4.sel) {
                    fn_1_D7A4(lbl_1_data_F4D4.sel);
                }
            }
            break;
        case 9:
            if (i == lbl_1_bss_30B6) {
                if (BTN_PRESSED & INPUT_BUTTON_A) {
                    DbgSceneB *s = (DbgSceneB *)currentDrawingItem;
                    s->func = fn_1_DE1C;
                    s->b14 = 0;
                    s->b15 = 8;
                }
            }
            break;
        case 10:
            if (i == lbl_1_bss_30B6) {
                if (BTN_PRESSED & INPUT_BUTTON_A) {
                    DbgSceneB *s = (DbgSceneB *)currentDrawingItem;
                    s32 k;
                    s->func = fn_1_DE1C;
                    s->b15 = 0;
                    lbl_1_bss_6940[lbl_1_bss_5F73].f44 = lbl_1_bss_3218[(s8)s->b15].f0;
                    lbl_1_bss_6940[lbl_1_bss_5F73].f45 = lbl_1_bss_3218[(s8)s->b15].f2;
                    dbgSetAnim((u8 *)&hugeAnimStruct.objs->e[lbl_1_bss_5F73], SLOTA(lbl_1_bss_5F73)->a.tbl[lbl_1_bss_6940[lbl_1_bss_5F73].f44], lbl_1_bss_6940[lbl_1_bss_5F73].f45);
                    k = 5;
                    do {
                        DbgPtc *p = &lbl_1_bss_3258[(s8)s->b15][k];
                        if (p->h8 != 0) {
                            lbl_1_bss_67B8[k] = (void *)p;
                            ((DbgPtc *)lbl_1_bss_67B8[k])->f0 = 0.0f;
                        } else {
                            lbl_1_bss_67B8[k] = NULL;
                        }
                    } while (k-- != 0);
                    dbgBindActor(&hugeAnimStruct.slots[lbl_1_bss_5F73]);
                }
            }
            break;
        default: {
            DbgAnimEntry *tbl;
            u32 *p;
            s32 m;
            u16 rep = BTN_REPEAT;
            s32 l = rep & INPUT_BUTTON_LEFT;
            s32 r = rep & INPUT_BUTTON_RIGHT;
            s32 lr = rep & (INPUT_BUTTON_LEFT | INPUT_BUTTON_RIGHT);
            s32 held = BTN_HELD & INPUT_BUTTON_A;
            if (e->f0 >= 0) {
                tbl = SLOTA(lbl_1_bss_5F73)->a.tbl[e->f0];
                p = (u32 *)((u8 *)tbl->p4 + e->f2 * 12);
            } else {
                tbl = NULL;
                p = NULL;
            }
            for (m = 0; m < 4; m++) {
                u32 act;
                if (i != lbl_1_bss_30B6 || m != lbl_1_bss_30B7) {
                    act = 0xFFFF;
                } else if (held != 0) {
                    act = 0xF00F;
                } else {
                    act = 0xF0F;
                }
                switch (m) {
                case 0:
                    if ((u16)act == 0xF00F && tbl != NULL) {
                        if (l != 0) {
                            if (e->f4 >= 0) {
                                e->f4--;
                            }
                        } else if (r != 0) {
                            if (e->f4 < (s16)(s32) * (f32 *)p[1]) {
                                e->f4++;
                            }
                        }
                    }
                    break;
                case 1:
                    if ((u16)act == 0xF00F) {
                        s16 c = e->f0;
                        if (l != 0) {
                            if (c >= 0) {
                                e->f0 = c - 1;
                            }
                        } else if (r != 0) {
                            if (c < 6) {
                                e->f0 = c + 1;
                            }
                        }
                        if (c != e->f0) {
                            e->f2 = 0;
                        }
                    }
                    break;
                case 2:
                    if ((u16)act == 0xF00F && tbl != NULL) {
                        if (l != 0) {
                            if (e->f2 > 0) {
                                e->f2--;
                            }
                        } else if (r != 0) {
                            if (e->f2 < *(u16 *)((u8 *)tbl + 0xA) - 1) {
                                e->f2++;
                            }
                        }
                    }
                    break;
                case 3:
                    if ((u16)act == 0xF00F && tbl != NULL && lr != 0) {
                        e->f6 = e->f6 == 0;
                    }
                    break;
                }
            }
            break;
        }
        }
    }
    if (!(BTN_HELD & INPUT_BUTTON_A)) {
        u16 rep = BTN_REPEAT;
        if (rep & INPUT_BUTTON_UP) {
            if (lbl_1_bss_30B6 == 0) {
                lbl_1_bss_30B6 = 11;
            }
            lbl_1_bss_30B6--;
        } else if (rep & INPUT_BUTTON_DOWN) {
            lbl_1_bss_30B6++;
            if (lbl_1_bss_30B6 == 11) {
                lbl_1_bss_30B6 = 0;
            }
        } else if (rep & INPUT_BUTTON_LEFT) {
            if (lbl_1_bss_30B7 == 0) {
                lbl_1_bss_30B7 = 4;
            }
            lbl_1_bss_30B7--;
        } else if (rep & INPUT_BUTTON_RIGHT) {
            lbl_1_bss_30B7++;
            if (lbl_1_bss_30B7 == 4) {
                lbl_1_bss_30B7 = 0;
            }
        } else if (rep & INPUT_BUTTON_B) {
            lbl_1_bss_5F71 = 1;
        }
    }
}

// .text:0x0000DF14 size:0x184
void fn_1_DF14(void) {
    DbgSceneB *s = (DbgSceneB *)currentDrawingItem;
    s32 row = s->b14;
    switch (s->state) {
    case 0: {
        DbgSlotEnt *e = &lbl_1_bss_3218[row];
        lbl_1_bss_6940[lbl_1_bss_5F73].f44 = e->f0;
        lbl_1_bss_6940[lbl_1_bss_5F73].f45 = e->f2;
        insertGraphicDrawingFunction(fn_1_107B8, 0xFF);
        lbl_1_bss_5F5C = 2;
        currentDrawingItem->state++;
        break;
    }
    case 1:
        if (lbl_1_bss_5F5C == 0) {
            s32 k = 5;
            do {
                DbgPtc *dst = &lbl_1_bss_3258[row][k];
                if (lbl_1_bss_67B8[k] != NULL) {
                    memcpy(dst, lbl_1_bss_67B8[k], 0x20);
                    dst->p1C = &lbl_1_bss_3758[row][k * 0x100];
                    memcpy(&lbl_1_bss_3758[row][k * 0x100], ((DbgPtc *)lbl_1_bss_67B8[k])->p1C,
                           ((DbgPtc *)lbl_1_bss_67B8[k])->h1A * 4);
                } else {
                    memset(dst, 0, 0x20);
                }
            } while (k-- != 0);
            currentDrawingItem->currentDrawingItem->state = 1;
            removeCurrentDrawingItem();
        }
        break;
    }
}

// .text:0x0000DE1C size:0xF8
void fn_1_DE1C(void) {
    DbgSceneB *s = (DbgSceneB *)currentDrawingItem;
    switch (s->b14) {
    case 0:
        if ((s8)s->b15 == 0) {
            s->func = fn_1_D9B8;
        } else {
            while ((s8)s->b15-- != 0) {
                if (lbl_1_bss_3218[(s8)s->b15].f0 >= 0) {
                    DbgSceneB *d = (DbgSceneB *)insertGraphicDrawingFunction(fn_1_DF14, currentDrawingItem->priority + 1);
                    d->state = 0;
                    d->b14 = s->b15;
                    s->state = 0;
                    s->b14++;
                    break;
                }
            }
        }
        break;
    case 1:
        if (s->state != 0) {
            s->b14 = 0;
        }
        break;
    }
    fn_1_D8A0();
}

// .text:0x0000D9B8 size:0x464
void fn_1_D9B8(void) {
    DbgModel *m = hugeAnimStruct.objs->e[lbl_1_bss_5F73].model;
    DbgSceneB *s = (DbgSceneB *)currentDrawingItem;
    u16 n = m->count;
    s32 i;
    s32 fr;
    s16 f4;
    for (i = 0; i < n; i++) {
        DbgPartData *d = m->parts[i]->data;
        if (d != NULL && d->flag != 0) {
            break;
        }
    }
    if (i < n) {
        fr = (s32)m->parts[i]->data->value;
    }
    f4 = lbl_1_bss_3218[(s8)s->b15].f4;
    if ((f4 < 0 && (BTN_PRESSED & INPUT_BUTTON_A)) || (f4 >= 0 && fr >= f4)) {
        s32 k;
        f32 f2;
        do {
            s->b15++;
            if (s->b15 == 8) {
                s->b15 = 0;
            }
        } while (lbl_1_bss_3218[(s8)s->b15].f0 < 0);
        lbl_1_bss_6940[lbl_1_bss_5F73].f44 = lbl_1_bss_3218[(s8)s->b15].f0;
        lbl_1_bss_6940[lbl_1_bss_5F73].f45 = lbl_1_bss_3218[(s8)s->b15].f2;
        dbgSetAnim((u8 *)&hugeAnimStruct.objs->e[lbl_1_bss_5F73], SLOTA(lbl_1_bss_5F73)->a.tbl[lbl_1_bss_6940[lbl_1_bss_5F73].f44], lbl_1_bss_6940[lbl_1_bss_5F73].f45);
        k = 5;
        f2 = *(f32 *)lbl_1_bss_67B8[0];
        while (k-- != 0) {
            DbgPtc *p = &lbl_1_bss_3258[(s8)s->b15][k];
            if (p->h8 != 0) {
                u16 h = *(u16 *)((u8 *)lbl_1_bss_67B8[0] + 0xC);
                lbl_1_bss_67B8[k] = (void *)p;
                if (lbl_1_bss_3218[(s8)s->b15].f6 != 0) {
                    if ((f32)((DbgPtc *)lbl_1_bss_67B8[k])->h18 < f2) {
                        ((DbgPtc *)lbl_1_bss_67B8[k])->f0 = f2;
                        ((DbgPtc *)lbl_1_bss_67B8[k])->hC = h;
                    } else {
                        ((DbgPtc *)lbl_1_bss_67B8[k])->f0 = 0.0f;
                        ((DbgPtc *)lbl_1_bss_67B8[k])->hC = 0;
                    }
                }
            } else {
                lbl_1_bss_67B8[k] = NULL;
            }
        }
        dbgBindActor(&hugeAnimStruct.slots[lbl_1_bss_5F73]);
    }
    if (BTN_REPEAT & INPUT_BUTTON_B) {
        currentDrawingItem->func = fn_1_1770C;
    }
    fn_1_D8A0();
}

// .text:0x0000D8A0 size:0x118
void fn_1_D8A0(void) {
    fn_1_17954();
    fn_1_179CC();
    PSMTXCopy(lbl_1_bss_67E0.mtx0, lbl_1_bss_68FC.mtx10);
    fn_800A7D4C(7, &lbl_1_data_AA54[drawStadiumRelated]);
    if (lbl_1_bss_3078 != 0) {
        fn_800A7D4C(7, &lbl_1_data_AB34[drawStadiumRelated]);
    }
    fn_800A7D4C(7, &lbl_1_data_AAC4[drawStadiumRelated]);
    fn_1_129D0();
}

// .text:0x0000D7A4 size:0xFC
void fn_1_D7A4(s32 row) {
    DbgSlotAbs *act = SLOTA(lbl_1_bss_5F73);
    DbgRow *r = (DbgRow *)((u8 *)lbl_1_data_F4D4.tbl + row * 0x50);
    s32 i;
    i = 8;
    do {
        DbgRowEnt *s = &r->ent[i];
        DbgSlotEnt *e = &lbl_1_bss_3218[i];
        if ((s8)s->kind != 0) {
            DbgAnimEntry *tb;
            s16 a = s->a;
            s16 b;
            e->f0 = a;
            tb = act->a.tbl[a];
            b = s->b;
            e->f2 = b;
            e->f6 = (s8)s->c;
            if (s->d == -2) {
                if (tb != NULL) {
                    e->f4 = *(f32 *)tb->p4[b][1];
                } else {
                    e->f4 = 0;
                }
            } else {
                e->f4 = s->d;
            }
        } else {
            e->f0 = -1;
            e->f6 = 0;
            e->f4 = 0;
        }
    } while (i-- != 0);
}

// .text:0x0000D71C size:0x88
f32 fn_1_D71C(s32 idx) {
    DbgModel *m = hugeAnimStruct.objs->e[idx].model;
    u16 n = m->count;
    s32 i;
    for (i = 0; i < n; i++) {
        DbgPartData *d = m->parts[i]->data;
        if (d != NULL && d->flag != 0) {
            break;
        }
    }
    if (i < n) {
        return m->parts[i]->data->value;
    }
    return 0.0f;
}

const char *fn_1_D6E4(void) {
    s32 i = lbl_1_bss_3216;
    switch (i) {
    case 0:
    case 1:
    case 2:
        return lbl_1_data_F4DC[(u8)i];
    default:
        return 0;
    }
}

// .text:0x0000D6B4 size:0x30
void fn_1_D6B4(void) {
    if (lbl_1_bss_3216 == 0) {
        lbl_1_bss_3216 = 3;
    }
    lbl_1_bss_3216--;
}

// .text:0x0000D688 size:0x2C
void fn_1_D688(void) {
    lbl_1_bss_3216++;
    if (lbl_1_bss_3216 == 3) {
        lbl_1_bss_3216 = 0;
    }
}

// .text:0x0000D67C size:0xC
void fn_1_D67C(u8 value) {
    lbl_1_bss_3215 = value;
}

// .text:0x0000D660 size:0x1C
BOOL fn_1_D660(void) {
    return lbl_1_bss_3215 != 0;
}

// .text:0x0000D650 size:0x10
void fn_1_D650(void) {
    lbl_1_bss_3214 = TRUE;
}

// .text:0x0000D638 size:0x18
u8 fn_1_D638(void) {
    u8 v = lbl_1_bss_3214;
    lbl_1_bss_3214 = FALSE;
    return v;
}

// .text:0x0000D590 size:0xA8
void fn_1_D590(s32 a, s32 b, f32 v) {
    if (lbl_1_bss_3215 != 0) {
        if (lbl_1_bss_3216 == 0) {
            return;
        }
        if (lbl_1_bss_3216 == 2) {
            if ((s32)v == 0) {
                lbl_1_bss_3214 += (lbl_1_bss_3214 != 0);
            }
            if (lbl_1_bss_3214 == 3) {
                lbl_1_bss_3214 = 0;
            }
            if (lbl_1_bss_3214 != 2) {
                return;
            }
        }
        {
            s32 lvl = (s8)lbl_1_bss_5F62;
            if (lvl < 0) {
                lvl = 0;
            }
            fn_8004B208(a, b, lvl);
        }
    }
}

// .text:0x0000D4BC size:0xD4
void fn_1_D4BC(void) {
    DbgActor *a = hugeAnimStruct.slots;
    if (a != NULL) {
        VecXYZ p;
        a->flags = (s32)a->flags >> 1;
        a->flags = (a->flags & 0x1F) << 3;
        getAnimRelatedCoordinates(0, 0x1E, &p);
        if (a->pos.y - p.y < 0.3f) {
            a->flags |= 2;
        }
        getAnimRelatedCoordinates(0, 0x22, &p);
        if (a->pos.y - p.y < 0.3f) {
            a->flags |= 4;
        }
    }
    hugeAnimStruct.actors[0]->flags |= 1;
}

// .text:0x0000D300 size:0x1BC
void fn_1_D300(DbgActor *src) {
    dbgBindActor(src);
}

// .text:0x0000D2F0 size:0x10
void fn_1_D2F0(void) {
    lbl_1_bss_30B8 = TRUE;
}

// .text:0x0000D13C size:0x1B4
void fn_1_D13C(void) {
    DbgActor *act = &hugeAnimStruct.slots[lbl_1_bss_5F73];
    DbgScene *d;
    s32 k;
    u16 ids[2];
    u16 *w162;
    s32 i;
    d = (DbgScene *)insertGraphicDrawingFunction(fn_1_CDC8, currentDrawingItem->priority + 1);
    lbl_1_bss_60E8 = (u32)d;
    d->state = lbl_1_bss_6940[lbl_1_bss_5F73].f44;
    switch (lbl_1_bss_68FC.f40[lbl_1_bss_5F73]) {
    case 0x12:
        k = 3;
        break;
    case 0x26:
        k = 0;
        break;
    case 0x28:
        k = 1;
        break;
    case 0x29:
        k = 2;
        break;
    }
    act->f25A = ((lbl_1_bss_6940[lbl_1_bss_5F73].f44 < 2) - (lbl_1_bss_5F69 == 0)) == 0;
    w162 = (u16 *)((u8 *)&hugeAnimStruct.slots[lbl_1_bss_5F73] + 0x162);
    ids[act->f25A] = w162[lbl_1_data_F4E8[k * 2]];
    ids[act->f25A == 0] = w162[lbl_1_data_F4E8[k * 2 + 1]];
    for (i = 0; i < 2; i++) {
        callDSInsertListObject((void *)hugeAnimStruct.objs->e[lbl_1_bss_5F73].model, ids[i]);
    }
}

// .text:0x0000CDC8 size:0x374
void fn_1_CDC8(void) {
    DbgActor *act;
    u16 fa, fb;
    s32 k;
    s32 kind;
    s32 flag;
    u16 ids[2];
    void *ptrsB[2];
    void *ptrsA[2];
    s32 i;
    if (lbl_1_bss_30B8 != 0) {
        lbl_1_bss_30B8 = 0;
        removeCurrentDrawingItem();
        return;
    }
    act = &hugeAnimStruct.slots[lbl_1_bss_5F73];
    fb = act->partIdx[25];
    fa = act->partIdx[19];
    fn_800B2BA8(((DbgActorTbl *)hugeAnimStruct.objs)->e[lbl_1_bss_5F73].model, fa, 0, 0);
    fn_800B2BA8(((DbgActorTbl *)hugeAnimStruct.objs)->e[lbl_1_bss_5F73].model, fb, 0, 0);
    switch (lbl_1_bss_68FC.f40[lbl_1_bss_5F73]) {
    case 0x12:
        k = 3;
        break;
    case 0x26:
        k = 0;
        break;
    case 0x28:
        k = 1;
        break;
    case 0x29:
        k = 2;
        break;
    }
    act->f25A = ((lbl_1_bss_6940[lbl_1_bss_5F73].f44 < 2) - (lbl_1_bss_5F69 == 0)) == 0;
    ids[0] = act->partIdx[lbl_1_data_F4E8[k * 2]];
    ids[1] = act->partIdx[lbl_1_data_F4E8[k * 2 + 1]];
    ptrsA[lbl_1_bss_5F69] = lbl_1_bss_67B8[2];
    ptrsA[lbl_1_bss_5F69 == 0] = lbl_1_bss_67B8[1];
    ptrsB[0] = (u8 *)&lbl_1_bss_5F7C->e[1];
    ptrsB[1] = (u8 *)&lbl_1_bss_5F7C->e[0];
    kind = lbl_1_bss_6940[lbl_1_bss_5F73].f44;
    switch (kind) {
    case 0:
    case 1:
    case 5:
    case 6:
        flag = 1;
        break;
    case 2:
    case 3:
    case 4:
        flag = 0;
        break;
    }
    i = 0;
    do {
        if (ptrsA[i] != NULL) {
            if (getHandTrackFlags(ptrsA[i]) & 0x20000000) {
                DbgModel *m = *(DbgModel **)ptrsB[i];
                s32 j;
                for (j = 0; j < m->count; j++) {
                    if (m->parts[j]->f14 != 0) {
                        fn_800B2BA8(((DbgActorTbl *)hugeAnimStruct.objs)->e[lbl_1_bss_5F73].model, ids[i], m, j);
                        break;
                    }
                }
            } else {
                fn_800B2BA8(((DbgActorTbl *)hugeAnimStruct.objs)->e[lbl_1_bss_5F73].model, ids[i], 0, 0);
            }
        }
        i++;
    } while ((flag != 0 || lbl_1_bss_68FC.f40[lbl_1_bss_5F73] == 0x26) && i < 2);
    if (i == 1) {
        DbgModel **pp;
        DbgModel *m;
        s32 j;
        if (lbl_1_bss_5F69 != 0) {
            pp = (DbgModel **)((u8 *)&lbl_1_bss_5F7C->e[2]);
        } else {
            pp = (DbgModel **)((u8 *)&lbl_1_bss_5F7C->e[2]);
        }
        m = *pp;
        ptrsB[0] = pp;
        for (j = 0; j < m->count; j++) {
            if (m->parts[j]->f14 != 0) {
                fn_800B2BA8(((DbgActorTbl *)hugeAnimStruct.objs)->e[lbl_1_bss_5F73].model, ids[i], m, j);
                break;
            }
        }
    }
}

// .text:0x0000CCC8 size:0x100
void fn_1_CCC8(void) {
    DbgScene *s = (DbgScene *)currentDrawingItem;
    f32 *fp = s->data;
    if (fp != NULL && fp[0] < fp[1]) {
        if (lbl_1_bss_5F69 != 0) {
            fn_800385F0(&lbl_1_bss_30C0, 1.0f, 0.5f, 0.1f, 1.0f);
        } else {
            fn_800385F0(&lbl_1_bss_30C0, -1.0f, 0.5f, 0.1f, 1.0f);
        }
        lbl_1_bss_30C0.f50 = lbl_1_data_F568;
        fn_80037AA0(&lbl_1_bss_30C0, 0, fn_1_CB9C, s->count, s->data);
        removeCurrentDrawingItem();
    }
}

// .text:0x0000CC24 size:0xA4
void fn_1_CC24(void) {
    if (lbl_1_bss_30BC == 0) {
        DbgScene *d;
        lbl_1_bss_30BC = 1;
        d = (DbgScene *)insertGraphicDrawingFunction(fn_1_CCC8, currentDrawingItem->priority + 1);
        if (lbl_1_bss_5F69 != 0) {
            d->data = lbl_1_bss_67B8[1];
            d->count = lbl_1_data_F56C;
        } else {
            d->data = lbl_1_bss_67B8[2];
            d->count = lbl_1_data_F56E;
        }
    }
}

// .text:0x0000CB9C size:0x88
void fn_1_CB9C(BOOL flag) {
    if (flag) {
        lbl_1_bss_30BC = 0;
    } else {
        PSMTXCopy(lbl_1_bss_30C0.mtx58, lbl_1_data_F4F8[drawStadiumRelated].mtx);
        fn_800A7D4C(8, &lbl_1_data_F4F8[drawStadiumRelated]);
    }
}

// .text:0x0000C9E0 size:0x1BC
void fn_1_C9E0(DbgBlob *blob) {
    Mtx m;
    Vec v;
    fn_1_F2C(4, 0, 0);
    PSMTXConcat(lbl_1_bss_68FC.mtx10, blob->mtx8, m);
    GXLoadPosMtxImm(m, 0);
    GXSetCurrentMtx(0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZMode(1, GX_ALWAYS, 1);
    GXBegin(GX_LINES, GX_VTXFMT0, 6);
    GXPosition3f32(lbl_1_bss_30C0.f0[3], lbl_1_bss_30C0.f0[4], lbl_1_bss_30C0.f0[5]);
    GXColor1u32(0xFF0000FF);
    GXPosition3f32(lbl_1_bss_30C0.f0[0], lbl_1_bss_30C0.f0[1], lbl_1_bss_30C0.f0[2]);
    GXColor1u32(0x00FF00FF);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXColor1u32(0xFF);
    PSVECScale(&lbl_1_bss_30C0.v128, lbl_1_data_F570, &v);
    GXPosition3f32(v.x, v.y, v.z);
    GXColor1u32(0xFF);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXColor1u32(0xFFFFFFFF);
    PSVECScale(&lbl_1_bss_30C0.v140, lbl_1_data_F570, &v);
    GXPosition3f32(v.x, v.y, v.z);
    GXColor1u32(0xFFFFFFFF);
}

// .text:0x0000C5AC size:0x434
void fn_1_C5AC(void) {
    Mtx44 proj;
    Mtx ident = {{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}};
        C_MTXOrtho(proj, 0.0f, 448.0f, 0.0f, 640.0f, 0.0f, lbl_1_data_F578);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    GXLoadPosMtxImm(ident, 0);
    GXSetCurrentMtx(0);
    fn_1_F2C(4, 0, 0);
    GXSetColorUpdate(0);
    GXSetAlphaUpdate(0);
    GXSetZMode(1, GX_ALWAYS, 1);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, -lbl_1_data_F57C);
    GXColor1u32(lbl_1_data_F574);
    GXPosition3f32(640.0f, 0.0f, -lbl_1_data_F57C);
    GXColor1u32(lbl_1_data_F574);
    GXPosition3f32(640.0f, 448.0f, -lbl_1_data_F57C);
    GXColor1u32(lbl_1_data_F574);
    GXPosition3f32(0.0f, 448.0f, -lbl_1_data_F57C);
    GXColor1u32(lbl_1_data_F574);
    GXSetColorUpdate(1);
    GXSetAlphaUpdate(1);
    GXSetZMode(1, GX_LEQUAL, 1);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(330.0f, 0.0f, -1.0f);
    GXColor1u32(lbl_1_data_F580);
    GXPosition3f32(310.0f, 0.0f, -1.0f);
    GXColor1u32(lbl_1_data_F580);
    GXPosition3f32(220.0f, 336.0f, -1.0f);
    GXColor1u32(lbl_1_data_F584);
    GXPosition3f32(420.0f, 336.0f, -1.0f);
    GXColor1u32(lbl_1_data_F584);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, -2.0f);
    GXColor1u32(lbl_1_data_F574);
    GXPosition3f32(640.0f, 0.0f, -2.0f);
    GXColor1u32(lbl_1_data_F574);
    GXPosition3f32(640.0f, 448.0f, -2.0f);
    GXColor1u32(lbl_1_data_F574);
    GXPosition3f32(0.0f, 448.0f, -2.0f);
    GXColor1u32(lbl_1_data_F574);
    GXSetColorUpdate(0);
    GXSetAlphaUpdate(0);
    GXSetZMode(1, GX_ALWAYS, 1);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, -lbl_1_data_F57C);
    GXColor1u32(lbl_1_data_F574);
    GXPosition3f32(640.0f, 0.0f, -lbl_1_data_F57C);
    GXColor1u32(lbl_1_data_F574);
    GXPosition3f32(640.0f, 448.0f, -lbl_1_data_F57C);
    GXColor1u32(lbl_1_data_F574);
    GXPosition3f32(0.0f, 448.0f, -lbl_1_data_F57C);
    GXColor1u32(lbl_1_data_F574);
    GXSetColorUpdate(1);
    GXSetAlphaUpdate(1);
}

// .text:0x0000C5A8
void fn_1_C5A8(void) {
}

#pragma dont_inline on
// .text:0x0000C2DC
s32 fn_1_C2DC(DbgTreeNode *n, char *buf, s32 pos, s32 w, s32 ret, s32 *p28, s32 *p29, s32 *p30) {
    DbgTreeNode *c;
    if (*p29 == 0) {
        buf[pos] = '+';
        buf[pos + 1] = 0;
        (*p30)--;
        if (*p30 == 0) {
            return ret;
        }
    } else {
        (*p29)--;
    }
    (*p28)--;
    if (n->child != NULL) {
        if (n->sibling != NULL) {
            buf[pos] = '|';
        } else {
            buf[pos] = ' ';
        }
        c = n->child;
        if (*p29 == 0) {
            buf[pos + 1] = '+';
            buf[pos + 2] = 0;
            (*p30)--;
            if (*p30 == 0) {
                goto done1;
            }
        } else {
            (*p29)--;
        }
        (*p28)--;
        if (c->child != NULL) {
            if (c->sibling != NULL) {
                buf[pos + 1] = '|';
            } else {
                buf[pos + 1] = ' ';
            }
            ret = fn_1_C2DC(c->child, buf, pos + 2, w, ret, p28, p29, p30);
            if (*p30 == 0) {
                goto done1;
            }
        }
        if (c->sibling != NULL) {
            ret = fn_1_C2DC(c->sibling, buf, pos + 1, w, ret, p28, p29, p30);
        }
    done1:
        if (*p30 == 0) {
            return ret;
        }
    }
    c = n->sibling;
    if (c != NULL) {
        if (*p29 == 0) {
            buf[pos] = '+';
            buf[pos + 1] = 0;
            (*p30)--;
            if (*p30 == 0) {
                goto done2;
            }
        } else {
            (*p29)--;
        }
        (*p28)--;
        if (c->child != NULL) {
            if (c->sibling != NULL) {
                buf[pos] = '|';
            } else {
                buf[pos] = ' ';
            }
            ret = fn_1_C2DC(c->child, buf, pos + 1, w, ret, p28, p29, p30);
            if (*p30 == 0) {
                goto done2;
            }
        }
        if (c->sibling != NULL) {
            ret = fn_1_C2DC(c->sibling, buf, pos, w, ret, p28, p29, p30);
        }
    done2:
        if (*p30 == 0) {
            return ret;
        }
    }
    return ret;
}

#pragma dont_inline reset
