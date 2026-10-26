#define REP_HEADER_DATA_FN getRepHeaderData_rep02A8
#define SQRT2_LINKAGE static
#include "debug/rep_02A8.h"
#include "game/UnknownHomes_Game.h"
#include "header_rep_data.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x80021410.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/dvdsys.h"
#include "Unknown/File_0x800a7568.h"
#include "Unknown/File_0x800b0a14.h"
#include "Dolphin/os.h"

extern u8 fn_800211F0(void);
extern s32 fn_800214D0(void);
extern void fn_80021518(s32 id, void *block);
extern s32 fn_80062890(s32 arg0);
extern void fn_80021954(void **file);
extern void fn_80021980(void *file);

unsigned long sndRemoveListener(SND_LISTENER *li);
unsigned long sndUpdateListener(SND_LISTENER *li, SND_FVECTOR *pos, SND_FVECTOR *dir, SND_FVECTOR *heading,
                                SND_FVECTOR *up, u8 vol, SND_ROOM *room);
unsigned long sndAddListener(SND_LISTENER *li, SND_FVECTOR *pos, SND_FVECTOR *dir, SND_FVECTOR *heading,
                             SND_FVECTOR *up, f32 front_sur, f32 back_sur, f32 soundSpeed, unsigned long flags,
                             unsigned char vol, SND_ROOM *room);
unsigned long sndRemoveEmitter(SND_EMITTER *em);
bool32 sndUpdateEmitter(SND_EMITTER *em, SND_FVECTOR *pos, SND_FVECTOR *dir, u8 maxVol, SND_ROOM *room);
unsigned long sndAddEmitter(SND_EMITTER *em, SND_FVECTOR *pos, SND_FVECTOR *dir, f32 maxDis, f32 comp,
                            unsigned long flags, unsigned short fxid, unsigned char maxVol,
                            unsigned char minVol, SND_ROOM *room);

typedef struct AudioLoaderTask {
    /*0x00*/ u8 pad00[0x0C];
    /*0x0C*/ DrawingSceneStruct *parent;
    /*0x10*/ u8 pad10[4];
    /*0x14*/ s32 (*pushCallback)();
    /*0x18*/ u8 state;
    /*0x19*/ u8 fileIndex;
    /*0x1A*/ u8 callbackState;
} AudioLoaderTask;

typedef struct SndTestState {
    /*0x00*/ u8 listener[0xC];
    /*0x0C*/ SND_FVECTOR pos;
    /*0x18*/ u8 pad18[4];
    /*0x1C*/ SND_FVECTOR dir;
    /*0x28*/ SND_FVECTOR heading;
    /*0x34*/ u8 pad34[0xC];
    /*0x40*/ SND_FVECTOR up;
    /*0x4C*/ u8 pad4C[0x3C];
    /*0x88*/ f32 volume;
    /*0x8C*/ u8 pad8C[4];
    /*0x90*/ u8 emitter[0x10];
    /*0xA0*/ SND_FVECTOR emitPos;
    /*0xAC*/ SND_FVECTOR emitDir;
    /*0xB8*/ u8 padB8[4];
    /*0xBC*/ f32 emitVolume;
    /*0xC0*/ u8 padC0[0x20];
    /*0xE0*/ u8 active;
    /*0xE1*/ u8 padE1[3];
} SndTestState; // size 0xE4

typedef struct SndTestListenerParams {
    /*0x00*/ f32 frontSurround;
    /*0x04*/ f32 backSurround;
    /*0x08*/ f32 soundSpeed;
    /*0x0C*/ u8 volume;
} SndTestListenerParams; // size 0x10

typedef struct SndTestEmitterParams {
    /*0x00*/ f32 maxDis;
    /*0x04*/ f32 comp;
    /*0x08*/ f32 maxVol;
    /*0x0C*/ f32 minVol;
    /*0x10*/ u16 fxid;
} SndTestEmitterParams; // size 0x14

extern SndTestListenerParams lbl_1_common_bss_49970;
extern SndTestEmitterParams lbl_1_common_bss_49980;
extern SndTestState lbl_1_common_bss_49994;
extern s8 lbl_1_common_bss_49A78[0x21B8];

#define BUTTON_HELD_ADDR (*(u16 *)((u8 *)&AtBat_ButtonInput1 + 0))
#define BUTTON_PRESSED_ADDR (*(u16 *)((u8 *)&AtBat_ButtonInput1 + 2))
#define BUTTON_REPEAT_ADDR (*(u16 *)((u8 *)&AtBat_ButtonInput1 + 4))

static struct {
    u16 tbl[0x3CC];
    const char *menuNames[19];
} lbl_1_data_FC0 = {
    {
        0x1B1A, 0x1918, 0x1716, 0x1514, 0x1312, 0x1110, 0x0F0E, 0x0D0C,
        0x0B0A, 0x2307, 0x0921, 0x2208, 0x302E, 0x272F, 0x3225, 0x2426,
        0x0144, 0x0137, 0x012A, 0x011D, 0x0110, 0x0103, 0x00F6, 0x00E9,
        0x00DC, 0x00CF, 0x00C2, 0x00B5, 0x00A8, 0x009B, 0x008E, 0x0081,
        0x0074, 0x0067, 0x0201, 0x0040, 0x005A, 0x01E7, 0x01E7, 0x01E7,
        0x01F4, 0x01F4, 0x01F4, 0x004D, 0x0277, 0x009B, 0x009B, 0x009B,
        0x009B, 0x025D, 0x025D, 0x025D, 0x025D, 0x0235, 0x026A, 0x02C9,
        0x021B, 0x020E, 0x00A8, 0x005A, 0x0074, 0x0074, 0x0074, 0x0074,
        0x0228, 0x0228, 0x0228, 0x0228, 0x004D, 0x004D, 0x2A2B, 0x2C34,
        0x0201, 0x0600, 0x0248, 0x024A, 0x0252, 0x030F, 0x0010, 0x0001,
        0x0022, 0x0000, 0x0249, 0x0251, 0x0258, 0x000F, 0x0017, 0x000F,
        0x003F, 0x0000, 0x02D6, 0x02D7, 0x02D8, 0x02D9, 0x02E1, 0x02E2,
        0x02E3, 0x02E4, 0x02E5, 0x02E6, 0x02DD, 0x02DE, 0x02DF, 0x02E0,
        0x02DA, 0x02DB, 0x02DC, 0x02E7, 0x02E8, 0x02E9, 0x02EA, 0x02EB,
        0x02EC, 0x02ED, 0x02EE, 0x02EF, 0x02F0, 0x02F1, 0x02F2, 0x02F3,
        0x02F4, 0x02F5, 0x02F6, 0x02F7, 0x02F8, 0x02F9, 0x02FA, 0x02FB,
        0x02FC, 0x02FD, 0x02FE, 0x02FF, 0x0300, 0x0301, 0x0302, 0x0303,
        0x0304, 0x0305, 0x0306, 0x0307, 0x0308, 0x0309, 0x030A, 0x030B,
        0x030C, 0x030D, 0x030E, 0x0000, 0x0000, 0x0000, 0x0000, 0x0100,
        0x7878, 0x7878, 0x7878, 0x7878, 0x7878, 0x7878, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x0000, 0x7F00, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x7F00, 0x0000, 0x0000, 0x0000, 0x7F7F, 0x7F7F, 0x7F00, 0x0000,
        0x0000, 0x0000, 0x4B28, 0x4B28, 0x5528, 0x5528, 0x5528, 0x5528,
        0x5528, 0x5528, 0x5528, 0x5A28, 0x5528, 0x5528, 0x5528, 0x5528,
        0x5528, 0x5528, 0x5A28, 0x5F28, 0x6928, 0x0000, 0x5528, 0x0000,
        0x7F00, 0x7F00, 0x7F00, 0x4600, 0x4B00, 0x5500, 0x5A00, 0x5A00,
        0x6400, 0x7F00, 0x6400, 0x7800, 0x6400, 0x7F00, 0x6400, 0x6400,
        0x6400, 0x6400, 0x6400, 0x6400, 0x6400, 0x6400, 0x6400, 0x6400,
        0x7F00, 0x6400, 0x6E00, 0x7F00, 0x7500, 0x7500, 0x6400, 0x6400,
        0x5700, 0x6400, 0x6400, 0x5700, 0x6400, 0x6400, 0x6400, 0x7F00,
        0x7F00, 0x7500, 0x5400, 0x6400, 0x6400, 0x5000, 0x5A00, 0x7F00,
        0x7F00, 0x7F00, 0x7F00, 0x7F00, 0x7F00, 0x6400, 0x6400, 0x6400,
        0x7500, 0x6B00, 0x6400, 0x7300, 0x7F00, 0x7F00, 0x7F00, 0x7F00,
        0x7F00, 0x7F00, 0x7F00, 0x7F00, 0x7F00, 0x6B00, 0x5500, 0x6B00,
        0x6B00, 0x7F00, 0x7F00, 0x7500, 0x6600, 0x7500, 0x7F00, 0x5500,
        0x6400, 0x6400, 0x6400, 0x6400, 0x6400, 0x6E00, 0x6400, 0x6400,
        0x7300, 0x6E00, 0x5A00, 0x6E00, 0x7F00, 0x7F00, 0x6B00, 0x7F00,
        0x7500, 0x7F00, 0x7F00, 0x7300, 0x7F00, 0x7F00, 0x3C00, 0x5A00,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x7F00, 0x7F00, 0x7F00,
        0x6900, 0x7F00, 0x7F00, 0x7F00, 0x7F00, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x7F00, 0x7F00, 0x7F00, 0x7F00,
        0x7F00, 0x7F00, 0x7F00, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x7F00, 0x7F00, 0x7F00, 0x6400, 0x7F00,
        0x4100, 0x4600, 0x4600, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x7F00, 0x7F00, 0x7F00, 0x3200, 0x4D00, 0x4D00,
        0x5700, 0x5700, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x7F00, 0x6400, 0x6400, 0x6400, 0x7F00, 0x7F00, 0x3C00,
        0x3C00, 0x6900, 0x7F00, 0x6E00, 0x7F00, 0x6E00, 0x7F00, 0x7F00,
        0x7F00, 0x6B00, 0x6400, 0x5F00, 0x7500, 0x7000, 0x6B00, 0x7F00,
        0x6B00, 0x7F00, 0x7F00, 0x7F00, 0x4B00, 0x7F00, 0x7F00, 0x7F00,
        0x6400, 0x6400, 0x6900, 0x7500, 0x6900, 0x5F00, 0x5F00, 0x6900,
        0x6400, 0x6E00, 0x7800, 0x6E00, 0x6E00, 0x7F00, 0x6B7F, 0x7F7F,
        0x7F7F, 0x7F4D, 0x4D7F, 0x616B, 0x6161, 0x7F6B, 0x5F69, 0x4337,
        0x7F7F, 0x7F69, 0x7F61, 0x7575, 0x645F, 0x7F64, 0x647F, 0x695A,
        0x646B, 0x7F7F, 0x5A7F, 0x7F75, 0x7F7F, 0x7364, 0x736E, 0x6E7F,
        0x7373, 0x7F7F, 0x7800, 0x0000, 0x6464, 0x6464, 0x6464, 0x6464,
        0x6464, 0x6464, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F,
        0x7F7F, 0x7F7F, 0x7F7F, 0x7F7F, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
        0x0000, 0x0000, 0x0000, 0x0000, 0x3F19, 0x999A, 0x4248, 0x0000,
        0x0000, 0x0000, 0x42FE, 0x0000, 0x4120, 0x0000, 0x4248, 0x0000,
        0x0000, 0x0000, 0x42FE, 0x0000, 0x4120, 0x0000, 0x4248, 0x0000,
        0x0000, 0x0000, 0x42FE, 0x0000, 0x4120, 0x0000, 0x4248, 0x0000,
        0x0000, 0x0000, 0x42FE, 0x0000, 0x4120, 0x0000, 0x42C8, 0x0000,
        0x0000, 0x0000, 0x42FE, 0x0000, 0x4120, 0x0000, 0x42C8, 0x0000,
        0x0000, 0x0000, 0x42FE, 0x0000, 0x4120, 0x0000, 0x0000, 0x0001,
        0x0000, 0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000, 0x0061,
        0x0000, 0x0061, 0x4248, 0x0000, 0x4248, 0x0000, 0x3F80, 0x0000,
        0x2000, 0x3B00, 0x0003, 0x002D, 0x0046, 0x0000, 0x2000, 0x3FFF,
        0x0001, 0x003C, 0x007F, 0x0000, 0x2000, 0x3FFF, 0x0014, 0x00A5,
        0x007F, 0x0000, 0x0303, 0x0000,
    },
    {
        "Voice Test",
        "Voice Test2",
        "Training Se Test",
        "SE Test",
        "Surround Test",
        "VOICE NO ",
        "HAPPY",
        "POWER_UP_P",
        "POWER_UP_B",
        "SWING_WIDE",
        "STRUCK_OUT",
        "RELEASE FAST",
        "RELEASE G_FAST",
        "NO 1",
        "MAX SWING OUT",
        "LOSE",
        "DEAD BALL",
        "FIRE BALL",
        "end",
    },
};

static u8 lbl_1_data_17A4[0x20] = {
    0x1B, 0x1A, 0x19, 0x18, 0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11, 0x10, 0x0F, 0x0E, 0x0D, 0x0C,
    0x0B, 0x0A, 0x23, 0x07, 0x09, 0x08, 0x25, 0x24, 0x26, 0x21, 0x22, 0x2E, 0x27, 0x2F, 0x30, 0x32,
};

static u16 lbl_1_data_17C4[18] = {
    0x0144, 0x0137, 0x012A, 0x011D, 0x0110, 0x0103, 0x00F6, 0x00E9,
    0x00DC, 0x00CF, 0x00C2, 0x00B5, 0x00A8, 0x009B, 0x008E, 0x0081,
    0x0074, 0x0067,
};

static struct {
    u16 ids[14];
    const char *charNames[32];
} lbl_1_data_17E8 = {
    {
        0x0201, 0x0040, 0x005A, 0x004D, 0x021B, 0x020E, 0x0228, 0x01E7,
        0x01F4, 0x025D, 0x0235, 0x026A, 0x0277, 0x02C9,
    },
    {
        "MARIO      ",
        "LUIGI      ",
        "DONKEY     ",
        "DIDDY      ",
        "PEACH      ",
        "DAISY      ",
        "YOSHI      ",
        "BABYMARIO  ",
        "BABYLUIGI  ",
        "KOOPA      ",
        "WARIO      ",
        "WALUIGI    ",
        "NOKONOKO   ",
        "KINOPIO    ",
        "TERESA     ",
        "KINOPIKO   ",
        "HEIHO R    ",
        "CATHERINE  ",
        "CHOROPU    ",
        "KOOPA JR.  ",
        "PATA_P     ",
        "HAMM BROS  ",
        "KURIBO     ",
        "PATA_K     ",
        "KARON      ",
        "MONTE      ",
        "MARE       ",
        "KAMEKKU    ",
        "KING TERESA",
        "BOSS PAKKUN",
        "KINOJI     ",
        "DIXY       ",
    },
};

static u8 lbl_1_data_1884[8] = {
    0x2A, 0x2B, 0x2C, 0x34, 0x02, 0x01, 0x06, 0x00,
};

static u16 lbl_1_data_188C[48] = {
    0x0248, 0x0249, 0x024A, 0x024B, 0x024C, 0x024D, 0x024E, 0x024F,
    0x0250, 0x0252, 0x0253, 0x0254, 0x0255, 0x0256, 0x0257, 0x030F,
    0x0310, 0x0311, 0x0312, 0x0313, 0x0314, 0x0315, 0x0316, 0x0010,
    0x0011, 0x0012, 0x0013, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005,
    0x0006, 0x0007, 0x0008, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026,
    0x0027, 0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002F,
};

static u16 lbl_1_data_18EC[24] = {
    0x02D6, 0x02D7, 0x02D8, 0x02D9, 0x02DA, 0x02DB, 0x02DC, 0x02DD,
    0x02DE, 0x02DF, 0x02E0, 0x02E1, 0x02E2, 0x02E3, 0x02E4, 0x02E5,
    0x02E6, 0x02E7, 0x02E8, 0x02E9, 0x02EA, 0x02EB, 0x02EC, 0x0017,
};

static const char *lbl_1_data_191C[13] = {
    "POS_X", "POS_Y", "POS_Z", "DIR_X", "DIR_Y", "DIR_Z", "HEAD_X",
    "HEAD_Y", "HEAD_Z", "UP_X", "UP_Y", "UP_Z", "VOL",
};

static const char *lbl_1_data_1950[7] = {
    "POS_X", "POS_Y", "POS_Z", "DIR_X", "DIR_Y", "DIR_Z", "VOL",
};

u32 lbl_1_data_196C[0xC8] = {
    0x00000000, 0x0002B060, 0x07742000, 0x0002B060,
    0x00000000, 0x00415EA0, 0x0776D800, 0x00415EA0,
    0x00000000, 0x00103340, 0x07B83800, 0x00103340,
    0x00000000, 0x0029D520, 0x07C87000, 0x0029D520,
    0x00000000, 0x001364E0, 0x07F24800, 0x001364E0,
    0x00000000, 0x0002BB40, 0x0805B000, 0x0002BB40,
    0x00000000, 0x00028800, 0x08087000, 0x00028800,
    0x00000000, 0x0003DC00, 0x080AF800, 0x0003DC00,
    0x00000000, 0x00039DC0, 0x080ED800, 0x00039DC0,
    0x00000000, 0x00022260, 0x08127800, 0x00022260,
    0x00000000, 0x0001B180, 0x0814A000, 0x0001B180,
    0x00000000, 0x00021140, 0x08165800, 0x00021140,
    0x00000000, 0x0002E080, 0x08187000, 0x0002E080,
    0x00000000, 0x00029500, 0x081B5800, 0x00029500,
    0x00000000, 0x0002FEA0, 0x081DF000, 0x0002FEA0,
    0x00000000, 0x0002D360, 0x0820F000, 0x0002D360,
    0x00000000, 0x00039DC0, 0x0823C800, 0x00039DC0,
    0x00000000, 0x0000F760, 0x08276800, 0x0000F760,
    0x00000000, 0x00023EA0, 0x08286000, 0x00023EA0,
    0x00000000, 0x00026600, 0x082AA000, 0x00026600,
    0x00000000, 0x0001D8C0, 0x082D0800, 0x0001D8C0,
    0x00000000, 0x00021DE0, 0x082EE800, 0x00021DE0,
    0x00000000, 0x00035100, 0x08310800, 0x00035100,
    0x00000000, 0x00016F40, 0x08346000, 0x00016F40,
    0x00000000, 0x000246A0, 0x0835D000, 0x000246A0,
    0x00000000, 0x00013240, 0x08381800, 0x00013240,
    0x00000000, 0x0001D020, 0x083E3000, 0x0001D020,
    0x00000000, 0x00016BA0, 0x084A5800, 0x00016BA0,
    0x00000000, 0x0001A500, 0x084BC800, 0x0001A500,
    0x00000000, 0x0001A060, 0x084D7000, 0x0001A060,
    0x00000000, 0x0002CB20, 0x08395000, 0x0002CB20,
    0x00000000, 0x00020BE0, 0x083C2000, 0x00020BE0,
    0x00000000, 0x00026280, 0x0841A000, 0x00026280,
    0x00000000, 0x000217A0, 0x08440800, 0x000217A0,
    0x00000000, 0x0001A000, 0x08462000, 0x0001A000,
    0x00000000, 0x000190E0, 0x08400800, 0x000190E0,
    0x00000000, 0x000291C0, 0x0847C000, 0x000291C0,
    0x00000000, 0x00016BA0, 0x084A5800, 0x00016BA0,
    0x00000000, 0x0001A500, 0x084BC800, 0x0001A500,
    0x00000000, 0x0001A060, 0x084D7000, 0x0001A060,
    0x00000000, 0x00334600, 0x084F1800, 0x00334600,
    0x00000000, 0x001B65E0, 0x08826000, 0x001B65E0,
    0x00000000, 0x00047F20, 0x089DC800, 0x00047F20,
    0x00000000, 0x000353E0, 0x08A24800, 0x000353E0,
    0x00000000, 0x00020FA0, 0x08A5A000, 0x00020FA0,
    0x00000000, 0x000444E0, 0x08A7B000, 0x000444E0,
    0x00000000, 0x000145C0, 0x08ABF800, 0x000145C0,
    0x00000000, 0x00044CA0, 0x08AD4000, 0x00044CA0,
    0x00000000, 0x0010F6A0, 0x08B19000, 0x0010F6A0,
    0x00000000, 0x001622E0, 0x08C28800, 0x001622E0,
};

static void (*lbl_1_data_1C8C[5])(void) = {fn_1_C188, fn_1_BDD8, fn_1_A634, fn_1_BA64, fn_1_B4A4};
static u8 lbl_1_data_1CA0 = 0x12;
static s16 lbl_1_data_1CA2 = 0x151;
static s16 lbl_1_data_1CA4 = 0x151;
static s32 lbl_1_data_1CA8 = 0x151;

static u8 gUnused3058[0x18];
static s16 gVoiceIndex;
static s16 gVoice2Index;
static u32 gSeVoice3;
static u32 gSeVoice2;
static u32 gSeVoice1;
static u32 gSeVoice0;
static u8 gUnused3040[4];
static f32 gListenerValues[13];
static f32 gEmitterValues[7];
static u8 gTrainingState;
static s8 gEmitterItem;
static s8 gListenerItem;
static s16 gListenerSel;
static u8 gSurroundState;
static s16 gSeIdxC;
static s16 gSeIdxB;
static s16 gSeIdxA;
static u8 gSeColumn;
static u8 gSeMode;
static u8 gSeState;
static u8 gVoice2State;
static u8 gVoiceState;
static u8 gUnused2FDC;
static u8 gAudioFileIndex;
static u8 gTopState;
static u8 gVoiceGroup;
static u8 gUnused2FD8;

// .text:0x0000C2A4 size:0x38
void fn_1_C2A4(void) {
    currentDrawingItem->currentDrawingItem->state = 1;
    removeCurrentDrawingItem();
}

// .text:0x0000C188 size:0x11C
void fn_1_C188(void) {
    DrawingSceneStruct *cur = currentDrawingItem;

    switch (gVoiceState) {
    case 0: {
        AudioLoaderTask *task;
        s32 group;

        cur->state = 0;
        group = gVoiceGroup + 5;
        task = (AudioLoaderTask *)insertGraphicDrawingFunction(fn_1_9F04, 1);
        task->state = 0;
        task->fileIndex = group;
        task->pushCallback = fn_1_A908;
        currentDrawingItem->state = 0;
        gVoiceState++;
        break;
    }
    case 1:
        if (cur->state != 0) {
            if (gVoiceGroup != 0x11) {
                gVoiceGroup++;
                gVoiceState = 0;
            } else {
                cur->state = 0;
                gVoiceState++;
            }
        }
        break;
    case 2:
        cur->func = sndTestVoiceScreen;
        gVoiceState = 0;
        break;
    }
}

// .text:0x0000BFB0 size:0x1D8
void sndTestVoiceScreen(void) {
    E(u16, INPUT_BUTTON) pressed = BUTTON_PRESSED_ADDR;
    E(u16, INPUT_BUTTON) repeat = BUTTON_REPEAT_ADDR;

    if (pressed & INPUT_BUTTON_A) {
        u16 id = lbl_1_data_17C4[gVoiceIndex / 13] + gVoiceIndex % 13;

        fn_1_BF34(id);
    } else if (pressed & (INPUT_BUTTON_B | INPUT_BUTTON_START)) {
        fn_1_A718();
        currentDrawingItem->func = sndTestTopScreen;
    } else if (repeat & INPUT_BUTTON_LEFT) {
        if (repeat & INPUT_BUTTON_Y) {
            gVoiceIndex -= 10;
        } else {
            gVoiceIndex -= 1;
        }
        if (gVoiceIndex < 0) {
            gVoiceIndex = 0xE9;
        }
    } else if (repeat & INPUT_BUTTON_RIGHT) {
        s16 next = gVoiceIndex + 1;

        if (repeat & INPUT_BUTTON_Y) {
            next = gVoiceIndex + 10;
        }
        gVoiceIndex = next;
        if (gVoiceIndex > 0xE9) {
            gVoiceIndex = 0;
        }
    }
}

// .text:0x0000BF34 size:0x7C
s32 fn_1_BF34(s16 fxid) {
    SND_VOICEID voice = sndFXStartEx(fxid, 0x7F, 0x3F, 0);

    OSReport("sndFXReverb was %s.\n", sndFXCtrl(voice, 0x5B, fn_800211F0()) ? "succeed" : "failed");
    return voice;
}

// .text:0x0000BEF4 size:0x40
void fn_1_BEF4(s16 voice) {
    sndFXKeyOff(voice);
    sndFXCtrl(voice, 7, 0);
}

// .text:0x0000BDD8 size:0x11C
void fn_1_BDD8(void) {
    DrawingSceneStruct *cur = currentDrawingItem;

    switch (gVoice2State) {
    case 0: {
        AudioLoaderTask *task;
        s32 group;

        cur->state = 0;
        group = lbl_1_data_1CA0 + 5;
        task = (AudioLoaderTask *)insertGraphicDrawingFunction(fn_1_9F04, 1);
        task->state = 0;
        task->fileIndex = group;
        task->pushCallback = fn_1_A8B4;
        currentDrawingItem->state = 0;
        gVoice2State++;
        break;
    }
    case 1:
        if (cur->state != 0) {
            if (lbl_1_data_1CA0 != 0x1F) {
                lbl_1_data_1CA0++;
                gVoice2State = 0;
            } else {
                cur->state = 0;
                gVoice2State++;
            }
        }
        break;
    case 2:
        cur->func = sndTestVoice2Screen;
        gVoice2State = 0;
        break;
    }
}

// .text:0x0000BC00 size:0x1D8
void sndTestVoice2Screen(void) {
    E(u16, INPUT_BUTTON) pressed = BUTTON_PRESSED_ADDR;
    E(u16, INPUT_BUTTON) repeat = BUTTON_REPEAT_ADDR;

    if (pressed & INPUT_BUTTON_A) {
        u16 id = lbl_1_data_17E8.ids[gVoice2Index / 13] + gVoice2Index % 13;

        fn_1_BF34(id);
    } else if (pressed & (INPUT_BUTTON_B | INPUT_BUTTON_START)) {
        fn_1_A718();
        currentDrawingItem->func = sndTestTopScreen;
    } else if (repeat & INPUT_BUTTON_LEFT) {
        if (repeat & INPUT_BUTTON_Y) {
            gVoice2Index -= 10;
        } else {
            gVoice2Index -= 1;
        }
        if (gVoice2Index < 0) {
            gVoice2Index = 0xB5;
        }
    } else if (repeat & INPUT_BUTTON_RIGHT) {
        s16 next = gVoice2Index + 1;

        if (repeat & INPUT_BUTTON_Y) {
            next = gVoice2Index + 10;
        }
        gVoice2Index = next;
        if (gVoice2Index > 0xB5) {
            gVoice2Index = 0;
        }
    }
}

// .text:0x0000BA64 size:0x19C
void fn_1_BA64(void) {
    DrawingSceneStruct *cur = currentDrawingItem;

    switch (gSeState) {
    case 0: {
        AudioLoaderTask *task;

        cur->state = 0;
        task = (AudioLoaderTask *)insertGraphicDrawingFunction(fn_1_9F04, 1);
        task->state = 0;
        task->fileIndex = 1;
        task->pushCallback = fn_1_A880;
        currentDrawingItem->state = 0;
        gSeState++;
        break;
    }
    case 1:
        if (cur->state != 0) {
            cur->state = 0;
            gSeState++;
        }
        break;
    case 2:
        cur->state = 0;
        gSeState++;
        break;
    case 3:
        cur->state = 0;
        gSeState++;
        break;
    case 4:
        gSeState++;
        break;
    case 5:
        gSeState++;
        break;
    case 6: {
        AudioLoaderTask *task;

        cur->state = 0;
        task = (AudioLoaderTask *)insertGraphicDrawingFunction(fn_1_9F04, 1);
        task->state = 0;
        task->fileIndex = 0x29;
        task->pushCallback = fn_1_A77C;
        currentDrawingItem->state = 0;
        gSeState++;
        break;
    }
    case 7:
        if (cur->state != 0) {
            cur->state = 0;
            gSeState++;
        }
        break;
    case 8:
        cur->func = sndTestSeScreen;
        gSeState = 0;
        break;
    }
}

// .text:0x0000B5B8 size:0x4AC
void sndTestSeScreen(void) {
    E(u16, INPUT_BUTTON) repeat = BUTTON_REPEAT_ADDR;
    E(u16, INPUT_BUTTON) pressed = BUTTON_PRESSED_ADDR;
    s32 fast = repeat & INPUT_BUTTON_Y;

    if (fast) {
        gSeMode = 0;
    } else if (repeat & INPUT_BUTTON_X) {
        gSeMode = 1;
    } else if (gSeMode == 0) {
        if (pressed & INPUT_BUTTON_A) {
            if (gSeColumn == 0) {
                fn_1_BEF4(gSeVoice3);
                gSeVoice3 = fn_1_BF34(lbl_1_data_1CA2);
            } else if (gSeColumn == 1) {
                u16 id = lbl_1_data_188C[gSeIdxA];

                fn_1_BEF4(gSeVoice2);
                gSeVoice2 = fn_1_BF34(id);
            } else if (gSeColumn == 2) {
                u16 id = lbl_1_data_18EC[gSeIdxB];

                fn_1_BEF4(gSeVoice1);
                gSeVoice1 = fn_1_BF34(id);
            } else if (gSeColumn == 3) {
                gSeVoice0 = fn_80062890(gSeIdxC);
            }
        } else if (pressed & (INPUT_BUTTON_B | INPUT_BUTTON_START)) {
            fn_1_A718();
            fn_800ACFB0(audioFileDescriptors.files[0xA8 / 4]);
            fn_800ACFB0(audioFileDescriptors.files[0x8 / 4]);
            currentDrawingItem->func = sndTestTopScreen;
        } else if (repeat & INPUT_BUTTON_LEFT) {
            if (gSeColumn == 0) {
                if (fast) {
                    lbl_1_data_1CA2 -= 10;
                } else {
                    lbl_1_data_1CA2 -= 1;
                }
                if (lbl_1_data_1CA2 < 0x151) {
                    lbl_1_data_1CA2 = 0x1B6;
                }
            } else if (gSeColumn == 1) {
                gSeIdxA--;
                if (gSeIdxA < 0) {
                    gSeIdxA = (s32)ARRAY_COUNT(lbl_1_data_188C) - 1;
                }
            } else if (gSeColumn == 2) {
                gSeIdxB--;
                if (gSeIdxB < 0) {
                    gSeIdxB = (s32)ARRAY_COUNT(lbl_1_data_18EC) - 1;
                }
            } else if (gSeColumn == 3) {
                gSeIdxC--;
                if (gSeIdxC < 0) {
                    gSeIdxC = 0x44;
                }
            }
        } else if (repeat & INPUT_BUTTON_RIGHT) {
            if (gSeColumn == 0) {
                s16 next = lbl_1_data_1CA2 + 1;

                if (fast) {
                    next = lbl_1_data_1CA2 + 10;
                }
                lbl_1_data_1CA2 = next;
                if (lbl_1_data_1CA2 > 0x1B6) {
                    lbl_1_data_1CA2 = 0x151;
                }
            } else if (gSeColumn == 1) {
                gSeIdxA++;
                if (gSeIdxA > (s32)ARRAY_COUNT(lbl_1_data_188C) - 1) {
                    gSeIdxA = 0;
                }
            } else if (gSeColumn == 2) {
                gSeIdxB++;
                if (gSeIdxB > (s32)ARRAY_COUNT(lbl_1_data_18EC) - 1) {
                    gSeIdxB = 0;
                }
            } else if (gSeColumn == 3) {
                gSeIdxC++;
                if (gSeIdxC > 0x44) {
                    gSeIdxC = 0;
                }
            }
        } else if (repeat & INPUT_BUTTON_UP) {
            gSeColumn--;
        } else if (repeat & INPUT_BUTTON_DOWN) {
            gSeColumn++;
            if (gSeColumn > 3) {
                gSeColumn = 0;
            }
        }
    }
}

// .text:0x0000B4A4 size:0x114
void fn_1_B4A4(void) {
    DrawingSceneStruct *cur = currentDrawingItem;

    switch (gSurroundState) {
    case 0: {
        AudioLoaderTask *task;

        cur->state = 0;
        task = (AudioLoaderTask *)insertGraphicDrawingFunction(fn_1_9F04, 1);
        task->state = 0;
        task->fileIndex = 0x2A;
        task->pushCallback = fn_1_A7E4;
        currentDrawingItem->state = 0;
        gSurroundState++;
        break;
    }
    case 1:
        if (cur->state != 0) {
            audioFileDescriptors.soundMode = SND_OUTPUTMODE_SURROUND;
            sndOutputMode(SND_OUTPUTMODE_SURROUND);
            cur->state = 0;
            gSurroundState++;
        }
        break;
    case 2:
        cur->func = fn_1_A95C;
        lbl_1_common_bss_49994.active = 0;
        gSurroundState = 0;
        break;
    }
}

// .text:0x0000A95C size:0xB48
void fn_1_A95C(void) {
    E(u16, INPUT_BUTTON) pressed = BUTTON_PRESSED_ADDR;
    E(u16, INPUT_BUTTON) held = BUTTON_HELD_ADDR;
    E(u16, INPUT_BUTTON) repeat = BUTTON_REPEAT_ADDR;
    s32 i;

    if (pressed & INPUT_BUTTON_A) {
        u16 fxid = lbl_1_data_188C[gListenerSel];

        if (lbl_1_common_bss_49994.active != 0) {
            sndRemoveListener((SND_LISTENER *)&lbl_1_common_bss_49994);
            sndRemoveEmitter((SND_EMITTER *)lbl_1_common_bss_49994.emitter);
        }
        lbl_1_common_bss_49980.fxid = fxid;
        lbl_1_common_bss_49980.maxVol = 127.0f;
        lbl_1_common_bss_49980.minVol = 0.0f;
        lbl_1_common_bss_49980.comp = 0.0f;
        lbl_1_common_bss_49980.maxDis = 100.0f;
        sndAddEmitter((SND_EMITTER *)lbl_1_common_bss_49994.emitter, &lbl_1_common_bss_49994.emitPos, &lbl_1_common_bss_49994.emitDir, lbl_1_common_bss_49980.maxDis,
                      lbl_1_common_bss_49980.comp, SND_EMITTER_CONTINUOUS, fxid,
                      (u8)lbl_1_common_bss_49980.maxVol, (u8)lbl_1_common_bss_49980.minVol, NULL);
        lbl_1_common_bss_49970.frontSurround = 100.0f;
        lbl_1_common_bss_49970.backSurround = 10.0f;
        lbl_1_common_bss_49970.volume = 0x7F;
        lbl_1_common_bss_49970.soundSpeed = 1.0f;
        lbl_1_common_bss_49994.heading.x = 0.0f;
        lbl_1_common_bss_49994.heading.y = 0.0f;
        lbl_1_common_bss_49994.heading.z = -1.0f;
        lbl_1_common_bss_49994.up.x = 0.0f;
        lbl_1_common_bss_49994.up.y = 1.0f;
        lbl_1_common_bss_49994.up.z = 0.0f;
        sndAddListener((SND_LISTENER *)&lbl_1_common_bss_49994, &lbl_1_common_bss_49994.pos, &lbl_1_common_bss_49994.dir, &lbl_1_common_bss_49994.heading, &lbl_1_common_bss_49994.up,
                       lbl_1_common_bss_49970.frontSurround, lbl_1_common_bss_49970.backSurround,
                       lbl_1_common_bss_49970.soundSpeed, SND_LISTENER_DEFAULT, 0x7F, NULL);
        lbl_1_common_bss_49994.active = 1;
    } else if (pressed & (INPUT_BUTTON_B | INPUT_BUTTON_START)) {
        lbl_1_common_bss_49994.active = 0;
        fn_1_A718();
        currentDrawingItem->func = sndTestTopScreen;
    } else if (held & INPUT_BUTTON_Y) {
        if (repeat & INPUT_BUTTON_LEFT) {
            switch (gListenerItem) {
            case 0: lbl_1_common_bss_49994.pos.x -= 0.1; break;
            case 1: lbl_1_common_bss_49994.pos.y -= 0.1; break;
            case 2: lbl_1_common_bss_49994.pos.z -= 0.1; break;
            case 3: lbl_1_common_bss_49994.dir.y -= 0.1; break;
            case 4: lbl_1_common_bss_49994.dir.y -= 0.1; break;
            case 5: lbl_1_common_bss_49994.dir.z -= 0.1; break;
            case 6: lbl_1_common_bss_49994.heading.x -= 0.1; break;
            case 7: lbl_1_common_bss_49994.heading.y -= 0.1; break;
            case 8: lbl_1_common_bss_49994.heading.z -= 0.1; break;
            case 9: lbl_1_common_bss_49994.up.x -= 0.1; break;
            case 10: lbl_1_common_bss_49994.up.y -= 0.1; break;
            case 11: lbl_1_common_bss_49994.up.z -= 0.1; break;
            case 12: lbl_1_common_bss_49994.volume -= 10.0; break;
            }
        } else if (repeat & INPUT_BUTTON_RIGHT) {
            switch (gListenerItem) {
            case 0: lbl_1_common_bss_49994.pos.x += 0.1; break;
            case 1: lbl_1_common_bss_49994.pos.y += 0.1; break;
            case 2: lbl_1_common_bss_49994.pos.z += 0.1; break;
            case 3: lbl_1_common_bss_49994.dir.y += 0.1; break;
            case 4: lbl_1_common_bss_49994.dir.y += 0.1; break;
            case 5: lbl_1_common_bss_49994.dir.z += 0.1; break;
            case 6: lbl_1_common_bss_49994.heading.x += 0.1; break;
            case 7: lbl_1_common_bss_49994.heading.y += 0.1; break;
            case 8: lbl_1_common_bss_49994.heading.z += 0.1; break;
            case 9: lbl_1_common_bss_49994.up.x += 0.1; break;
            case 10: lbl_1_common_bss_49994.up.y += 0.1; break;
            case 11: lbl_1_common_bss_49994.up.z += 0.1; break;
            case 12: lbl_1_common_bss_49994.volume += 10.0; break;
            }
        } else if (repeat & INPUT_BUTTON_UP) {
            gListenerItem--;
            if (gListenerItem < 0) {
                gListenerItem = (s32)ARRAY_COUNT(gListenerValues) - 1;
            }
        } else if (repeat & INPUT_BUTTON_DOWN) {
            gListenerItem++;
            if (gListenerItem == (s32)ARRAY_COUNT(gListenerValues)) {
                gListenerItem = 0;
            }
        }
    } else if (held & INPUT_BUTTON_X) {
        if (repeat & INPUT_BUTTON_LEFT) {
            switch (gEmitterItem) {
            case 0: lbl_1_common_bss_49994.emitPos.x -= 0.1; break;
            case 1: lbl_1_common_bss_49994.emitPos.y -= 0.1; break;
            case 2: lbl_1_common_bss_49994.emitPos.z -= 0.1; break;
            case 3: lbl_1_common_bss_49994.emitDir.y -= 0.1; break;
            case 4: lbl_1_common_bss_49994.emitDir.y -= 0.1; break;
            case 5: lbl_1_common_bss_49994.emitDir.z -= 0.1; break;
            case 6: lbl_1_common_bss_49994.emitVolume -= 10.0; break;
            }
        } else if (repeat & INPUT_BUTTON_RIGHT) {
            switch (gEmitterItem) {
            case 0: lbl_1_common_bss_49994.emitPos.x += 0.1; break;
            case 1: lbl_1_common_bss_49994.emitPos.y += 0.1; break;
            case 2: lbl_1_common_bss_49994.emitPos.z += 0.1; break;
            case 3: lbl_1_common_bss_49994.emitDir.y += 0.1; break;
            case 4: lbl_1_common_bss_49994.emitDir.y += 0.1; break;
            case 5: lbl_1_common_bss_49994.emitDir.z += 0.1; break;
            case 6: lbl_1_common_bss_49994.emitVolume += 10.0; break;
            }
        } else if (repeat & INPUT_BUTTON_UP) {
            gEmitterItem--;
            if (gEmitterItem < 0) {
                gEmitterItem = (s32)ARRAY_COUNT(gEmitterValues) - 1;
            }
        } else if (repeat & INPUT_BUTTON_DOWN) {
            gEmitterItem++;
            if (gEmitterItem == (s32)ARRAY_COUNT(gEmitterValues)) {
                gEmitterItem = 0;
            }
        }
    } else {
        if (repeat & INPUT_BUTTON_LEFT) {
            if (--gListenerSel < 0) {
                gListenerSel = 1;
            }
        } else if (repeat & INPUT_BUTTON_RIGHT) {
            gListenerSel++;
            if (gListenerSel > 2) {
                gListenerSel = 0;
            }
        }
    }

    if (lbl_1_common_bss_49994.active != 0) {
        sndUpdateListener((SND_LISTENER *)&lbl_1_common_bss_49994, &lbl_1_common_bss_49994.pos, &lbl_1_common_bss_49994.dir, &lbl_1_common_bss_49994.heading, &lbl_1_common_bss_49994.up, 0x80, NULL);
        sndUpdateEmitter((SND_EMITTER *)lbl_1_common_bss_49994.emitter, &lbl_1_common_bss_49994.emitPos, &lbl_1_common_bss_49994.emitDir, 0x80, NULL);
    }

    for (i = 0; i < (s32)ARRAY_COUNT(gListenerValues); i++) {
        switch (gListenerItem) {
        case 0: gListenerValues[0] = lbl_1_common_bss_49994.pos.x; break;
        case 1: gListenerValues[1] = lbl_1_common_bss_49994.pos.y; break;
        case 2: gListenerValues[2] = lbl_1_common_bss_49994.pos.z; break;
        case 3: gListenerValues[3] = lbl_1_common_bss_49994.dir.y; break;
        case 4: gListenerValues[4] = lbl_1_common_bss_49994.dir.y; break;
        case 5: gListenerValues[5] = lbl_1_common_bss_49994.dir.z; break;
        case 6: gListenerValues[6] = lbl_1_common_bss_49994.heading.x; break;
        case 7: gListenerValues[7] = lbl_1_common_bss_49994.heading.y; break;
        case 8: gListenerValues[8] = lbl_1_common_bss_49994.heading.z; break;
        case 9: gListenerValues[9] = lbl_1_common_bss_49994.up.x; break;
        case 10: gListenerValues[10] = lbl_1_common_bss_49994.up.y; break;
        case 11: gListenerValues[11] = lbl_1_common_bss_49994.up.z; break;
        case 12: gListenerValues[12] = lbl_1_common_bss_49994.volume; break;
        }
    }

    for (i = 0; i < (s32)ARRAY_COUNT(gEmitterValues); i++) {
        switch (gEmitterItem) {
        case 0: gEmitterValues[0] = lbl_1_common_bss_49994.emitPos.x; break;
        case 1: gEmitterValues[1] = lbl_1_common_bss_49994.emitPos.y; break;
        case 2: gEmitterValues[2] = lbl_1_common_bss_49994.emitPos.z; break;
        case 3: gEmitterValues[3] = lbl_1_common_bss_49994.emitDir.y; break;
        case 4: gEmitterValues[4] = lbl_1_common_bss_49994.emitDir.y; break;
        case 5: gEmitterValues[5] = lbl_1_common_bss_49994.emitDir.z; break;
        case 6: gEmitterValues[6] = lbl_1_common_bss_49994.emitVolume; break;
        }
    }
}

// .text:0x0000A908 size:0x54
s32 fn_1_A908(void) {
    s32 slot = gVoiceGroup + 5;

    fn_80021518(lbl_1_data_17A4[gVoiceGroup], audioFileDescriptors.files[slot + 1]);
    return 0;
}

// .text:0x0000A8B4 size:0x54
s32 fn_1_A8B4(void) {
    s32 slot = lbl_1_data_1CA0 + 5;

    fn_80021518(lbl_1_data_17A4[lbl_1_data_1CA0], audioFileDescriptors.files[slot + 1]);
    return 0;
}

// .text:0x0000A880 size:0x34
s32 fn_1_A880(void) {
    fn_80021518(0x1C, audioFileDescriptors.files[0x8 / 4]);
    return 0;
}

// .text:0x0000A838 size:0x48
s32 fn_1_A838(void) {
    fn_80021518(0x1C, audioFileDescriptors.files[0x10 / 4]);
    fn_80021518(0x36, audioFileDescriptors.files[0x10 / 4]);
    return 0;
}

// .text:0x0000A7E4 size:0x54
s32 fn_1_A7E4(void) {
    s32 slot = gAudioFileIndex + 0x2A;

    fn_80021518(lbl_1_data_1884[gAudioFileIndex], audioFileDescriptors.files[slot + 1]);
    return 0;
}

// .text:0x0000A7B0 size:0x34
s32 fn_1_A7B0(void) {
    fn_80021518(0x33, audioFileDescriptors.files[0xC8 / 4]);
    return 0;
}

// .text:0x0000A77C size:0x34
s32 fn_1_A77C(void) {
    fn_80021518(0x31, audioFileDescriptors.files[0xA8 / 4]);
    return 0;
}

// .text:0x0000A718 size:0x64
s32 fn_1_A718(void) {
    s8 i;

    for (i = (s8)audioFileDescriptors.pushedGroupCount - 1; i > 0; i--) {
        if (fn_800214D0() == 0) {
            return FALSE;
        }
    }
    return TRUE;
}

// .text:0x0000A714 size:0x4
void fn_1_A714(void) {
}

// .text:0x0000A634 size:0xE0
void fn_1_A634(void) {
    DrawingSceneStruct *cur = currentDrawingItem;

    switch (gTrainingState) {
    case 0: {
        AudioLoaderTask *task;

        cur->state = 0;
        task = (AudioLoaderTask *)insertGraphicDrawingFunction(fn_1_9F04, 1);
        task->state = 0;
        task->fileIndex = 3;
        task->pushCallback = fn_1_A838;
        currentDrawingItem->state = 0;
        gTrainingState++;
        break;
    }
    case 1:
        if (cur->state != 0) {
            cur->state = 0;
            gTrainingState++;
        }
        break;
    case 2:
        cur->func = sndTestTrainingSeScreen;
        gTrainingState = 0;
        break;
    }
}

// .text:0x0000A464 size:0x1D0
void sndTestTrainingSeScreen(void) {
    E(u16, INPUT_BUTTON) pressed = BUTTON_PRESSED_ADDR;
    E(u16, INPUT_BUTTON) repeat = BUTTON_REPEAT_ADDR;

    if (pressed & INPUT_BUTTON_A) {
        fn_1_BEF4(lbl_1_data_1CA8);
        lbl_1_data_1CA8 = fn_1_BF34(lbl_1_data_1CA4);
    } else if (pressed & (INPUT_BUTTON_B | INPUT_BUTTON_START)) {
        fn_1_A718();
        fn_800ACFB0(audioFileDescriptors.files[0x10 / 4]);
        currentDrawingItem->func = sndTestTopScreen;
    } else if (repeat & INPUT_BUTTON_LEFT) {
        if (repeat & INPUT_BUTTON_Y) {
            lbl_1_data_1CA4 -= 10;
        } else {
            lbl_1_data_1CA4 -= 1;
        }
        if (lbl_1_data_1CA4 < 0x1AD) {
            lbl_1_data_1CA4 = 0x1B6;
        }
    } else if (repeat & INPUT_BUTTON_RIGHT) {
        s16 next = lbl_1_data_1CA4 + 1;

        if (repeat & INPUT_BUTTON_Y) {
            next = lbl_1_data_1CA4 + 10;
        }
        lbl_1_data_1CA4 = next;
        if (lbl_1_data_1CA4 > 0x1B6) {
            lbl_1_data_1CA4 = 0x151;
        }
    }
}

// .text:0x0000A348 size:0x11C
void sndTestTopScreen(void) {
    E(u16, INPUT_BUTTON) repeat = BUTTON_REPEAT_ADDR;
    E(u16, INPUT_BUTTON) pressed = BUTTON_PRESSED_ADDR;

    if (repeat & INPUT_BUTTON_UP) {
        lbl_1_common_bss_49A78[0] = (lbl_1_common_bss_49A78[0] + 4) % 5;
    } else if (repeat & INPUT_BUTTON_DOWN) {
        lbl_1_common_bss_49A78[0] = (lbl_1_common_bss_49A78[0] + 6) % 5;
    } else if (pressed & INPUT_BUTTON_A) {
        currentDrawingItem->func = lbl_1_data_1C8C[lbl_1_common_bss_49A78[0]];
        lbl_1_common_bss_49A78[1] = 0;
    } else if (pressed & (INPUT_BUTTON_B | INPUT_BUTTON_START)) {
        gTopState = 0;
        gVoiceGroup = 0;
        currentDrawingItem->func = fn_1_C2A4;
    }
}

// .text:0x0000A2E4 size:0x64
void fn_1_A2E4(void) {
    switch (gTopState) {
    case 0:
        gTopState++;
        break;
    case 1:
        gTopState++;
        break;
    case 2:
        currentDrawingItem->func = fn_1_A250;
        break;
    }
}

// .text:0x0000A250 size:0x94
void fn_1_A250(void) {
    s32 i;

    for (i = 0; i < 11; i++) {
        ((s32 *)lbl_1_common_bss_49A78)[i + 9] = -1;
    }
    ((s32 *)lbl_1_common_bss_49A78)[3] = -1;
    currentDrawingItem->func = sndTestTopScreen;
}

// .text:0x0000A210 size:0x40
char *fn_1_A210(char *path) {
    char c;
    char *name = path;

    if (path == NULL) {
        return NULL;
    }
    while ((c = *path++) != 0) {
        if (c == '/') {
            name = path;
        }
    }
    return name;
}

// .text:0x0000A1F4 size:0x1C
void fn_1_A1F4(ScrollList *list, ScrollListEntry *items, s32 total, s32 visible) {
    list->items = items;
    list->total = total;
    list->visible = visible;
    list->top = 0;
    list->cursor = 0;
}

static inline s32 textLength(const char *s) {
    s32 n = 0;

    if (s != NULL) {
        while (*s++ != '\0') {
            n++;
        }
    }
    return n;
}

// .text:0x0000A184 size:0x70
void fn_1_A184(ScrollList *list) {
    s32 visible;
    s32 total;
    s32 top;
    s32 page;
    ScrollListEntry *entry;
    s32 i;

    top = list->top;
    visible = list->visible;
    total = list->total;

    if (top + visible < total) {
        page = visible;
    } else if (total < visible) {
        page = total;
    } else {
        page = total - top;
    }
    entry = &list->items[top];
    for (i = 0; i < page; i++, entry++) {
        textLength(entry->text);
    }
}

// .text:0x0000A024 size:0x160
void fn_1_A024(ScrollList *list, ScrollDir dir) {
    s32 top = list->top;
    s32 visible = list->visible;
    s32 total = list->total;
    s32 cursor = list->cursor;
    s32 row = cursor - top;
    s32 page;

    if (top + visible < total) {
        page = visible;
    } else if (total < visible) {
        page = total;
    } else {
        page = total - top;
    }

    switch (dir) {
    case SCROLL_UP:
        if (row != 0) {
            list->cursor--;
        } else if (top != 0) {
            list->top--;
            list->cursor--;
        }
        break;
    case SCROLL_DOWN:
        if (row + 1 == page) {
            if (cursor + 1 < total) {
                list->top++;
                list->cursor++;
            }
        } else {
            list->cursor++;
        }
        break;
    case SCROLL_PAGE_UP:
        if (top < visible) {
            list->top = 0;
            list->cursor = 0;
        } else {
            list->top -= visible;
            list->cursor -= list->visible;
        }
        break;
    case SCROLL_PAGE_DOWN:
        if (cursor + page >= total) {
            list->top = total - page;
            list->cursor = list->total - 1;
        } else {
            list->top += visible;
            list->cursor += list->visible;
        }
        break;
    }
}

// .text:0x00009F04 size:0x120
void fn_1_9F04(void) {
    AudioLoaderTask *task = (AudioLoaderTask *)currentDrawingItem;

    switch (task->state) {
    case 0:
        (audioFileDescriptors.files + task->fileIndex)[1] =
            ARAMTransfer(&lbl_1_data_196C[task->fileIndex * 4], 0, 1, 0);
        task->state = 1;
        break;
    case 1:
        if (lbl_803C6CF8.cancel.bytes[1] != 1) {
            break;
        }
        fn_80021980((audioFileDescriptors.files + task->fileIndex)[1]);
        task->state = 2;
        task->callbackState = 0;
    case 2:
        if (task->pushCallback(&task->callbackState) == 0) {
            fn_80021954(&(audioFileDescriptors.files + task->fileIndex)[1]);
            task->parent->state = 1;
            removeCurrentDrawingItem();
        }
        break;
    }
}

// .text:0x00009EA0 size:0x64
void fn_1_9EA0(s32 fileIndex, s32 (*pushCallback)()) {
    AudioLoaderTask *task = (AudioLoaderTask *)insertGraphicDrawingFunction(fn_1_9F04, 1);

    task->state = 0;
    task->fileIndex = fileIndex;
    task->pushCallback = pushCallback;
    currentDrawingItem->state = 0;
}
