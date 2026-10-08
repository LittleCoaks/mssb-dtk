#include "game/sound/m_sound.h"
#include "header_rep_data.h"
#include "musyx/musyx.h"
#include "musyx/seq.h"
#include "Unknown/File_0x80052734.h"
#include "Unknown/File_0x800b0a14.h"
#include "static/UnknownHomes_Static.h"
#include "game/UnknownHomes_Game.h"
#include "Dolphin/mtx.h"
#include "game/camera/camera.h"
#include "game/ball/foul_detection.h"
#include "Unknown/File_0x80021410.h"
#include "Unknown/File_0x80062a94.h"

extern void fn_3_8B094(void);

// Composite listener/emitter object used by the stadium 3D sound code:
// a listener, an array of emitters, an active-flag byte per emitter, and
// two regions whose contents are unknown.
typedef struct SoundEmitterState {
    SND_LISTENER listener;         // 0x0000, size 0x90
    SND_EMITTER emitters[100];     // 0x0090, stride 0x50
    u8 emitterType[100];           // 0x1FD0, index into lbl_3_data_8974
    E(u8, BOOL) emitterActive[100]; // 0x2034
    u8 unk_2098[0xA0];             // 0x2098, unproven
} SoundEmitterState; // size 0x2138

extern SoundEmitterState sndEmitter;

unsigned long sndRemoveListener(SND_LISTENER* li);
unsigned long sndUpdateListener(SND_LISTENER* li, SND_FVECTOR* pos, SND_FVECTOR* dir,
                                 SND_FVECTOR* heading, SND_FVECTOR* up, u8 vol, SND_ROOM* room);
unsigned long sndAddListener(SND_LISTENER* li, SND_FVECTOR* pos, SND_FVECTOR* dir,
                              SND_FVECTOR* heading, SND_FVECTOR* up, f32 front_sur, f32 back_sur,
                              f32 soundSpeed, unsigned long flags, unsigned char vol,
                              SND_ROOM* room);
bool32 sndCheckEmitter(SND_EMITTER* em);
unsigned long sndRemoveEmitter(SND_EMITTER* em);
bool32 sndUpdateEmitter(SND_EMITTER* em, SND_FVECTOR* pos, SND_FVECTOR* dir, u8 maxVol,
                         SND_ROOM* room);
bool32 sndSeqGetValid(s32 unk);

extern u8 lbl_800E88A4[];
extern void fn_800A88C0(void);
extern void fn_800A8B78(void);
extern u16 fn_800A8864(void);
extern void fn_800A8878(u32 arg1, u32 arg2);

extern const f32 lbl_3_rodata_157C;
extern const f32 lbl_3_rodata_1580;

// Per-sound volume/reverb mix table, indexed by soundNumber - SOUND_EFFECT_MIX_FIRST_ID.
typedef struct SoundEffectMix {
    u8 volume;
    u8 reverb;
} SoundEffectMix;

extern u8 hugeAnimStruct[];
extern u8 pauseControl[0x264];
extern u8 animRelated[0x124];
extern u8 lbl_3_common_bss_37400[0x4E];
extern u8 lbl_3_common_bss_134C4[0x284];
bool32 sndSeqLoop(s32 unk, bool32 b);
#define SOUND_EFFECT_MIX_FIRST_ID 0x151

typedef struct SeqPlayEntry {
    u16 sgid;
    u16 sid;
    u16 _04;
} SeqPlayEntry;


// Loudness tracking state used by fn_3_8C2DC / fn_3_8C4F0. fn_3_8C4F0 reaches
// its flag byte (+1) and averaged hi/lo bytes (+0x10/+0x11) through one base
// pointer into lbl_3_bss_1760.
static u8 lbl_3_bss_1760[4];
static f32 lbl_3_bss_1764;
static struct SoundReplayQueue* lbl_3_bss_1768;
static f32 lbl_3_bss_176C[2];
static s32 lbl_3_bss_1774[0xC / sizeof(s32)];
static s32 lbl_3_bss_1780[0x78 / sizeof(s32)];

// A DrawingSceneStruct whose scratch region (0x14..0x40) is used by this
// file's callback as a 14-entry circular queue of 3-byte replay records.
typedef struct SoundReplayEventRecord {
    u8 arg1;
    u8 arg2;
    u8 arg3;
} SoundReplayEventRecord;

typedef struct SoundReplayQueue {
    u8 nodeHeader[0x14];
    u8 head;
    u8 tail;
    SoundReplayEventRecord entries[14];
} SoundReplayQueue; // overlays DrawingSceneStruct, size 0x40

#define SOUND_REPLAY_QUEUE_CAPACITY \
    ((int)(sizeof(((SoundReplayQueue*)0)->entries) / sizeof(SoundReplayEventRecord)))


typedef struct StadiumEmitterDef {
    s32 pos[3];
    s32 maxDis;
    s32 comp;
    s32 maxVol;
    s32 minVol;
    s32 flags[7];
    s32 _38;
} StadiumEmitterDef; // size 0x3C

// .data tables of this unit, in address order.
u8 unkCharacterArray[32] = {
    27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12,
    11, 10, 35, 7, 9, 33, 34, 8, 48, 46, 39, 47, 50, 37, 36, 38,
};

u16 characterSoundArray[54] = {
    324, 311, 298, 285, 272, 259, 246, 233, 220,
    207, 194, 181, 168, 155, 142, 129, 116, 103,
    513, 64, 90, 487, 487, 487, 500, 500, 500,
    77, 631, 155, 155, 155, 155, 605, 605, 605,
    605, 565, 618, 713, 539, 526, 168, 90, 116,
    116, 116, 116, 552, 552, 552, 552, 77, 77,
};

u8 lbl_3_data_81D4[8] = {42, 43, 44, 52, 2, 1, 6, 0};

u16 stadiumHazardSoundIDs[16] = {
    584, 586, 594, 783, 16, 1, 34, 0,
    585, 593, 600, 15, 23, 15, 63, 0,
};

u16 lbl_3_data_81FC[58] = {
    726, 727, 728, 729, 737, 738, 739, 740,
    741, 742, 733, 734, 735, 736, 730, 731,
    732, 743, 744, 745, 746, 747, 748, 749,
    750, 751, 752, 753, 754, 755, 756, 757,
    758, 759, 760, 761, 762, 763, 764, 765,
    766, 767, 768, 769, 770, 771, 772, 773,
    774, 775, 776, 777, 778, 779, 780, 781,
    782, 0,
};

u8 lbl_3_data_8270[8] = {0, 0, 0, 0, 0, 0, 1, 0};

u8 lbl_3_data_8278[12] = {120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120};

u8 lbl_3_data_8284[136] = {
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    0, 0, 127, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 127, 0, 0,
    0, 0, 0, 0, 0, 127, 127, 127, 127, 127, 0, 0, 0, 0, 0, 0, 0,
};

u8 lbl_3_data_830C[44] = {
    75, 40, 75, 40, 85, 40, 85, 40, 85, 40, 85, 40,
    85, 40, 85, 40, 85, 40, 90, 40, 85, 40, 85, 40,
    85, 40, 85, 40, 85, 40, 85, 40, 90, 40, 95, 40,
    105, 40, 0, 0, 85, 40, 0, 0,
};

SoundEffectMix lbl_3_data_8338[102] = {
    {127, 0}, {127, 0}, {127, 0}, {70, 0}, {75, 0}, {85, 0}, {90, 0}, {90, 0},
    {100, 0}, {127, 0}, {100, 0}, {120, 0}, {100, 0}, {127, 0}, {100, 0}, {100, 0},
    {100, 0}, {100, 0}, {100, 0}, {100, 0}, {100, 0}, {100, 0}, {100, 0}, {100, 0},
    {127, 0}, {100, 0}, {110, 0}, {127, 0}, {117, 0}, {117, 0}, {100, 0}, {100, 0},
    {87, 0}, {100, 0}, {100, 0}, {87, 0}, {100, 0}, {100, 0}, {100, 0}, {127, 0},
    {127, 0}, {117, 0}, {84, 0}, {100, 0}, {100, 0}, {80, 0}, {90, 0}, {127, 0},
    {127, 0}, {127, 0}, {127, 0}, {127, 0}, {127, 0}, {100, 0}, {100, 0}, {100, 0},
    {117, 0}, {107, 0}, {100, 0}, {115, 0}, {127, 0}, {127, 0}, {127, 0}, {127, 0},
    {127, 0}, {127, 0}, {127, 0}, {127, 0}, {127, 0}, {107, 0}, {85, 0}, {107, 0},
    {107, 0}, {127, 0}, {127, 0}, {117, 0}, {102, 0}, {117, 0}, {127, 0}, {85, 0},
    {100, 0}, {100, 0}, {100, 0}, {100, 0}, {100, 0}, {110, 0}, {100, 0}, {100, 0},
    {115, 0}, {110, 0}, {90, 0}, {110, 0}, {127, 0}, {127, 0}, {107, 0}, {127, 0},
    {117, 0}, {127, 0}, {127, 0}, {115, 0}, {127, 0}, {127, 0},
};

u8 stadiumHazardSoundFxRelated[180] = {
    60, 0, 90, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 127, 0, 127, 0, 127, 0,
    105, 0, 127, 0, 127, 0, 127, 0, 127, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    127, 0, 127, 0, 127, 0, 127, 0, 127, 0, 127, 0,
    127, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 127, 0, 127, 0, 127, 0,
    100, 0, 127, 0, 65, 0, 70, 0, 70, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    127, 0, 127, 0, 127, 0, 50, 0, 77, 0, 77, 0,
    87, 0, 87, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 127, 0, 100, 0, 100, 0,
    100, 0, 127, 0, 127, 0, 60, 0, 60, 0, 105, 0,
    127, 0, 110, 0, 127, 0, 110, 0, 127, 0, 127, 0,
};

u8 lbl_3_data_84B8[60] = {
    127, 0, 107, 0, 100, 0, 95, 0, 117, 0, 112, 0,
    107, 0, 127, 0, 107, 0, 127, 0, 127, 0, 127, 0,
    75, 0, 127, 0, 127, 0, 127, 0, 100, 0, 100, 0,
    105, 0, 117, 0, 105, 0, 95, 0, 95, 0, 105, 0,
    100, 0, 110, 0, 120, 0, 110, 0, 110, 0, 127, 0,
};

u8 lbl_3_data_84F4[60] = {
    107, 127, 127, 127, 127, 127, 127, 77, 77, 127, 97, 107,
    97, 97, 127, 107, 95, 105, 67, 55, 127, 127, 127, 105,
    127, 97, 117, 117, 100, 95, 127, 100, 100, 127, 105, 90,
    100, 107, 127, 127, 90, 127, 127, 117, 127, 127, 115, 100,
    115, 110, 110, 127, 115, 115, 127, 127, 120, 0, 0, 0,
};

// Bytes 0x000..0x17F are per-sound volumes and 0x180..0x2FF per-sound reverb.
u8 charSoundFxVol[768] = {
    100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

f32 lbl_3_data_8830 = 0.6f;

f32 lbl_3_data_8834[24] = {
    50.0f, 0.0f, 127.0f, 10.0f, 50.0f, 0.0f, 127.0f, 10.0f, 50.0f, 0.0f, 127.0f, 10.0f,
    50.0f, 0.0f, 127.0f, 10.0f, 100.0f, 0.0f, 127.0f, 10.0f, 100.0f, 0.0f, 127.0f, 10.0f,
};

u32 lbl_3_data_8894[6] = {1, 1, 1, 1, 97, 97};

f32 lbl_3_data_88AC[3] = {50.0f, 50.0f, 1.0f};

s16 baseSoundPitchFactor[18] = {
    8192, 15104, 3, 45, 70, 0,
    8192, 16383, 1, 60, 127, 0,
    8192, 16383, 20, 165, 127, 0,
};

u8 lbl_3_data_88DC[4] = {3, 3, 0, 0};

u16 lbl_3_data_88E0[58] = {
    29, 0, 0, 29, 1, 1, 29, 2, 2,
    29, 3, 3, 29, 4, 4, 29, 6, 5,
    29, 5, 6, 29, 7, 7, 29, 8, 8,
    29, 9, 9, 29, 10, 10, 29, 11, 11,
    29, 12, 12, 29, 13, 13, 29, 14, 14,
    29, 15, 15, 29, 16, 16, 29, 17, 17,
    29, 18, 18, 0,
};

u16 lbl_3_data_8954[16] = {
    54, 21, 0, 0, 5655, 6426, 7454, 7968,
    8739, 9258, 11052, 11566, 12081, 12851, 13365, 0,
};

StadiumEmitterDef lbl_3_data_8974[17] = {
    {{-5000000, -4000000, 23000000}, 30000000, 0, 110, 30, {1, 0, 0, 0, 0, 0, 0}, 1},
    {{-5000000, 0, 19000000}, 40000000, 0, 127, 50, {1, 0, 0, 0, 0, 0, 0}, 1},
    {{0, 0, 6000000}, 8000000, 0, 90, 30, {1, 0, 0, 0, 0, 0, 0}, 16},
    {{0, 0, 0}, 20000000, 0, 90, 30, {1, 0, 0, 0, 0, 0, 64}, 32},
    {{-5000000, -1000000, 5000000}, 30000000, 0, 70, 10, {1, 0, 0, 0, 0, 0, 64}, 32},
    {{0, 0, 5000000}, 20000000, 0, 50, 15, {1, 0, 0, 0, 0, 0, 64}, 32},
    {{-5000000, 0, 19000000}, 40000000, 0, 90, 35, {1, 0, 0, 0, 0, 0, 0}, 1},
    {{0, 0, 0}, 20000000, 0, 60, 40, {1, 0, 0, 0, 0, 0, 64}, 8},
    {{0, 0, 0}, 20000000, 0, 110, 90, {1, 0, 0, 0, 0, 0, 64}, 2},
    {{0, 0, 0}, 20000000, 0, 127, 100, {1, 0, 0, 0, 0, 0, 64}, 2},
    {{0, 0, 0}, 20000000, 0, 127, 100, {1, 0, 0, 0, 0, 0, 64}, 4},
    {{0, 0, 0}, 20000000, 0, 127, 100, {1, 0, 0, 0, 0, 0, 64}, 4},
    {{0, 0, 0}, 20000000, 0, 127, 100, {1, 0, 0, 0, 0, 0, 64}, 4},
    {{0, 0, 0}, 20000000, 0, 127, 100, {1, 0, 0, 0, 0, 0, 64}, 4},
    {{0, 0, 0}, 20000000, 0, 127, 100, {1, 0, 0, 0, 0, 0, 64}, 4},
    {{0, 0, 0}, 20000000, 0, 127, 0, {1, 0, 0, 0, 0, 0, 0}, 1},
    {{0, 0, 0}, 20000000, 0, 127, 0, {1, 0, 0, 0, 0, 0, 0}, 1},
};

SND_FVECTOR lbl_3_data_8D70 = {0.0f, -1.0f, 0.0f};

SND_FVECTOR lbl_3_data_8D7C = {0.0f, 0.0f, 0.0f};

// .text:0x0008B258 size:0x8C mapped:0x806CA2EC
BOOL addToCircularBuffer(u8 arg1, u8 arg2, u8 arg3) {
    u8 head;
    u8 next;

    if (lbl_3_bss_1768 == NULL) {
        goto fail;
    }

    head = lbl_3_bss_1768->head;
    next = (head + 1) % SOUND_REPLAY_QUEUE_CAPACITY;
    if (next == lbl_3_bss_1768->tail) {
fail:
        return FALSE;
    }

    lbl_3_bss_1768->head = next;
    lbl_3_bss_1768->entries[head].arg1 = arg2;
    lbl_3_bss_1768->entries[head].arg2 = arg1;
    lbl_3_bss_1768->entries[head].arg3 = arg3;
    return TRUE;
}

// .text:0x0008B2E4 size:0x34 mapped:0x806CA378
void fn_3_8B2E4(void) {
    lbl_3_bss_1768 = (SoundReplayQueue*)insertGraphicDrawingFunction(fn_3_8B094, 0);
}

// .text:0x0008B318 size:0x400
void stadiumMusic(int stadiumID) {
    int i;

    if (stadiumID == -1) {
        for (i = 0; i < 12; i++) {
            charSoundFxVol[0x180 + i] = lbl_3_data_8278[i];
        }
    } else if (stadiumID == STADIUM_ID_TOY_FIELD) {
        for (i = 0; i < 7; i++) {
            lbl_3_data_84B8[i * 2 + 1] = lbl_3_data_8270[i];
        }
        for (i = 0; i < 12; i++) {
            charSoundFxVol[0x180 + i] = lbl_3_data_8278[i];
        }
        for (i = 0; i < 102; i++) {
            lbl_3_data_8338[i].reverb = lbl_3_data_8284[i];
        }
    } else {
        for (i = 0; i < 7; i++) {
            lbl_3_data_84B8[i * 2 + 1] = 0;
        }
        for (i = 0; i < 12; i++) {
            charSoundFxVol[0x180 + i] = 0;
        }
        for (i = 0; i < 102; i++) {
            lbl_3_data_8338[i].reverb = 0;
        }
    }
}

// .text:0x0008B718 size:0xC4 mapped:0x806CA7AC
void fn_3_8B718(Vec* pos, Vec* dir, Vec* lookDir) {
    camera_803c639c_s* cam = returnFloatFromModeIndex(0);

    if (pos != NULL) {
        pos->x = cam->eye.x;
        pos->y = cam->eye.y;
        pos->z = cam->eye.z;
    }

    if (dir != NULL) {
        dir->x = lbl_3_rodata_157C;
        dir->y = lbl_3_rodata_157C;
        dir->z = lbl_3_rodata_157C;
    }

    if (lookDir != NULL) {
        f32 mag;

        PSVECSubtract(&cam->target, &cam->eye, lookDir);
        mag = PSVECMag(lookDir);
        if (mag != lbl_3_rodata_157C) {
            PSVECNormalize(lookDir, lookDir);
        }
    }
}

// .text:0x0008B7DC size:0x28 mapped:0x806CA870
void fn_3_8B7DC(void) {
    sndRemoveListener(&sndEmitter.listener);
}

// .text:0x0008B804 size:0x8C mapped:0x806CA898
void fn_3_8B804(void) {
    int i;

    for (i = 0; i < 100; i++) {
        if (sndEmitter.emitterActive[i]) {
            if (sndCheckEmitter(&sndEmitter.emitters[i])) {
                sndRemoveEmitter(&sndEmitter.emitters[i]);
            }
            sndEmitter.emitterActive[i] = FALSE;
        }
    }
}


extern const f32 lbl_3_rodata_1584;
unsigned long sndAddEmitter(SND_EMITTER* em, SND_FVECTOR* pos, SND_FVECTOR* dir, f32 maxDis,
                            f32 comp, unsigned long flags, unsigned short fxid, unsigned char maxVol,
                            unsigned char minVol, SND_ROOM* room);
extern const SND_FVECTOR lbl_3_rodata_1558;
extern SND_FVECTOR emitterPosX;
extern SND_FVECTOR emitterDirX;

// .text:0x0008B890 size:0xD4 mapped:0x806CA924
void updateAndRemoveStadiumEmitter(int emitterID) {
    SND_EMITTER* em;
    SND_FVECTOR pos;
    SND_FVECTOR dir;

    if (emitterID >= 0 && emitterID < 100) {
        if (sndEmitter.emitterActive[emitterID]) {
            em = &sndEmitter.emitters[emitterID];
            if (sndCheckEmitter(em)) {
                pos = emitterPosX;
                dir = emitterDirX;
                sndUpdateEmitter(em, &pos, &dir, 0, NULL);
                sndRemoveEmitter(em);
            }
        }
    }
}

// .text:0x0008B964 size:0x58 mapped:0x806CA9F8
void fn_3_8B964(SND_FVECTOR* pos, SND_FVECTOR* dir, SND_FVECTOR* heading) {
    if (sndEmitter.listener.room != NULL) {
        sndUpdateListener(&sndEmitter.listener, pos, dir, heading, &lbl_3_data_8D70, 0x7f, NULL);
    }
}

// .text:0x0008B9BC size:0xA4 mapped:0x806CAA50
void fn_3_8B9BC(SND_FVECTOR* pos) {
    SND_FVECTOR heading;
    SND_FVECTOR dir;

    heading.x = lbl_3_rodata_157C;
    heading.y = lbl_3_rodata_157C;
    heading.z = lbl_3_rodata_1580;
    dir.x = lbl_3_rodata_157C;
    dir.y = lbl_3_rodata_157C;
    dir.z = lbl_3_rodata_157C;

    sndRemoveListener(&sndEmitter.listener);
    sndAddListener(&sndEmitter.listener, pos, &dir, &heading, &lbl_3_data_8D70, lbl_3_data_88AC[0],
                   lbl_3_data_88AC[0], lbl_3_data_88AC[0], SND_LISTENER_DOPPLERFX, 0x7f, NULL);
}

// .text:0x0008BA60 size:0x164 mapped:0x806CAAF4
void updateOrRemoveEmitter(int emitterID, Vec* pos, Vec* vel) {
    SND_EMITTER* em;
    SND_FVECTOR localPos;
    int type;

    if (emitterID >= 0 && emitterID < 100) {
        if (sndEmitter.emitterActive[emitterID]) {
            em = &sndEmitter.emitters[emitterID];
            if (!sndCheckEmitter(em)) {
                sndEmitter.emitterActive[emitterID] = FALSE;
            } else {
                type = sndEmitter.emitterType[emitterID];
                if (pos == NULL) {
                    localPos.x = (f32)lbl_3_data_8974[type].pos[0] / 100000.0f;
                    localPos.y = (f32)lbl_3_data_8974[type].pos[1] / 100000.0f;
                    localPos.z = (f32)lbl_3_data_8974[type].pos[2] / 100000.0f;
                    pos = (Vec*)&localPos;
                }
                if (vel == NULL) {
                    vel = (Vec*)&lbl_3_data_8D7C;
                }
                sndUpdateEmitter(em, (SND_FVECTOR*)pos, (SND_FVECTOR*)vel,
                                 (u8)lbl_3_data_8974[type].maxVol, NULL);
            }
        }
    }
}

// .text:0x0008BBC4 size:0x230 mapped:0x806CAC58
int initializeStadiumObjectEmitter(int soundId, Vec* pos, Vec* vel, int arg) {
    SND_FVECTOR localPos;
    StadiumEmitterDef* def;
    int i;

    for (i = 0; i < 100; i++) {
        if (!sndEmitter.emitterActive[i] || !sndCheckEmitter(&sndEmitter.emitters[i])) {
            sndEmitter.emitterType[i] = arg;
            sndEmitter.emitterActive[i] = TRUE;
            sndEmitter.unk_2098[i] = 0;
            if (pos == NULL) {
                localPos.x = (f32)lbl_3_data_8974[arg].pos[0] / 100000.0f;
                localPos.y = (f32)lbl_3_data_8974[arg].pos[1] / 100000.0f;
                localPos.z = (f32)lbl_3_data_8974[arg].pos[2] / 100000.0f;
                pos = (Vec*)&localPos;
            }
            if (vel == NULL) {
                vel = (Vec*)&lbl_3_data_8D7C;
            }
            def = &lbl_3_data_8974[arg];
            sndAddEmitter(&sndEmitter.emitters[i], (SND_FVECTOR*)pos, (SND_FVECTOR*)vel,
                          (f32)def->maxDis / 100000.0f, (f32)def->comp / 100000.0f,
                          def->flags[0] | def->flags[1] | def->flags[2] | def->flags[3] | def->flags[4] |
                              def->flags[5] | def->flags[6],
                          (u16)soundId, (u8)def->maxVol, (u8)def->minVol, NULL);
            return i;
        }
    }
    if (i == 100) {
        OSPanic("m_sound.c", 0xE4C, "No Empty Emitter");
    }
    return -1;
}

// .text:0x0008BDF4 size:0x98 mapped:0x806CAE88
void fn_3_8BDF4(void) {
    fn_3_8B804();
    fn_3_8B7DC();
}

// .text:0x0008BE8C size:0x1F0 mapped:0x806CAF20
void initializeCamera(void) {
    SND_FVECTOR pos = lbl_3_rodata_1558;
    int i = 0;

    for (; i < 100; i++) {
        sndEmitter.emitterType[i] = 0xFF;
        sndEmitter.emitterActive[i] = FALSE;
        sndEmitter.unk_2098[i] = 0;
    }
    sndEmitter.unk_2098[0x64] = 0xFF;
    sndEmitter.unk_2098[0x65] = 0;

    fn_3_8B9BC(&pos);
    fn_3_8B804();
}

// .text:0x0008C07C size:0x88 mapped:0x806CB110
void transitionToReplay(void) {
    addToCircularBuffer(4, 0, 0);
}

// .text:0x0008C104 size:0x1D8 mapped:0x806CB198
void fn_3_8C104(int arg0) {
    u8 tag;
    int value = 0;

    if (audioFileDescriptors.enableMusic == 0) {
        return;
    }

    if (arg0 == -2) {
        value = 1;
    }

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        tag = 9;
        value = lbl_800E88A4[value + 0x12];
    } else if (g_GameLogic.gameStatus == GAME_STATUS_0x24) {
        tag = 7;
        value = lbl_800E88A4[value + 0xE];
    } else if (sound_crowd_EffectsStruct._20 == 0x16) {
        tag = 6;
        value = lbl_800E88A4[value + 0xC];
    } else if (sound_crowd_EffectsStruct._20 == 0x17) {
        tag = 0xE;
        value = lbl_800E88A4[value + 0x1C];
    } else if (g_GameLogic.gameStatus == GAME_STATUS_MVP_END_GAME) {
        tag = 7;
        value = lbl_800E88A4[value + 0xE];
    } else if (g_GameLogic.gameStatus == GAME_STATUS_CHAMPIONSHIP) {
        tag = 8;
        value = lbl_800E88A4[value + 0x10];
    } else {
        tag = g_d_GameSettings.StadiumID;
        value = lbl_800E88A4[g_d_GameSettings.StadiumID * 2 + value];
    }

    if (arg0 >= 0) {
        value = (u8)arg0;
    }

    addToCircularBuffer(0, tag, value);

    if (value == 0) {
        fn_800A8878(value, value);
    }
}

// .text:0x0008C2DC size:0x214 mapped:0x806CB370
BOOL fn_3_8C2DC(u32 arg1, u32 arg2) {
    u16 packed = fn_800A8864();
    f32 hi;
    int level;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        arg2 = lbl_800E88A4[(u8)arg2 + 0x12];
    } else if (sound_crowd_EffectsStruct._20 == 0x16) {
        arg2 = lbl_800E88A4[(u8)arg2 + 0xC];
    } else if (g_GameLogic.gameStatus == GAME_STATUS_MVP_END_GAME) {
        arg2 = lbl_800E88A4[(u8)arg2 + 0xE];
    } else if (g_GameLogic.gameStatus == GAME_STATUS_CHAMPIONSHIP) {
        arg2 = lbl_800E88A4[(u8)arg2 + 0x10];
    } else {
        arg2 = lbl_800E88A4[g_d_GameSettings.StadiumID * 2 + (u8)arg2];
    }

    hi = (f32)((packed >> 8) & 0xFF);
    if (hi > lbl_3_bss_1764) {
        lbl_3_bss_1764 = hi;
    }

    if (sound_crowd_EffectsStruct._2F == 0) {
        sound_crowd_EffectsStruct._2F = 1;
        lbl_3_bss_1764 = hi;
        lbl_3_bss_176C[0] = (f32)(u8)arg2 / (f32)arg1;
    }

    lbl_3_bss_1764 += lbl_3_bss_176C[0];
    level = (int)lbl_3_bss_1764;
    fn_800A8878(level, level);

    if (lbl_3_bss_1764 >= (f32)(u8)arg2) {
        sound_crowd_EffectsStruct._2F = 0;
        return FALSE;
    }
    return TRUE;
}


// .text:0x0008C4F0 size:0xD8 mapped:0x806CB584
BOOL fn_3_8C4F0(u32 arg1, u32 arg2) {
    u16 packed;
    u8 hi;
    u8 lo;
    u8 avgHi;
    s16 diff;
    u8* state = lbl_3_bss_1760;

    packed = fn_800A8864();
    hi = (u8)(packed >> 8);
    lo = (u8)packed;

    sound_crowd_EffectsStruct._2F = 0;

    if (state[1] == 0) {
        state[1] = 1;
        state[0x11] = (u8)(hi / arg1);
        state[0x10] = (u8)(lo / arg1);
    }

    avgHi = state[0x11];
    diff = (s16)(hi - avgHi);

    if (diff <= (s16)(u8)arg2 || arg1 == 1) {
        state[1] = 0;
        fn_800A8878(arg2, arg2);
        return FALSE;
    }

    fn_800A8878((u8)diff, (u8)(lo - state[0x10]));
    return TRUE;
}

static inline int getPanFromWorldPos(f32 x, f32 y, f32 z) {
    int screenX;
    int screenY;
    int pan = 0x3f;

    if (audioFileDescriptors.soundMode == 1) {
        fn_3_1650C(&screenX, &screenY, TRUE, x, -y, z);
        if (screenX < 0) {
            pan = 0;
        } else if (screenX > 640) {
            pan = 0x7f;
        } else {
            pan = 127.0f * ((f32)screenX / 640.0f);
        }
    }
    return pan;
}

static inline void playStadiumHazardSound(int sfx, int slot) {
    int stadiumID = g_d_GameSettings.StadiumID;
    SND_VOICEID voice = sndFXStartEx(stadiumHazardSoundIDs[stadiumID] + sfx,
                                     g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                                         ? lbl_3_data_84B8[slot]
                                         : stadiumHazardSoundFxRelated[stadiumID * 0x1E + slot],
                                     0x3F, 0);
    sndFXCtrl(voice, SND_MIDICTRL_REVERB,
              g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                  ? lbl_3_data_84B8[slot + 1]
                  : stadiumHazardSoundFxRelated[stadiumID * 0x1E + slot + 1]);
}

// .text:0x0008C5C8 size:0x7AC mapped:0x806CB65C
void makeSoundOfBallBouncing(void) {
    int code = g_Ball.collisionCode & 0x7F;

    if (!(g_Ball.ballVelocity < 0.2f) && g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES) {
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
            playStadiumHazardSound(0x18, 0x30);
            return;
        }

        if (g_d_GameSettings.StadiumID == STADIUM_ID_BOWSERS_CASTLE) {
            if (code == 8) {
                animateThrownBall(0x1A2, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.y,
                                  g_Ball.AtBat_Contact_BallPos.z);
            } else {
                animateThrownBall(0x1A1, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.y,
                                  g_Ball.AtBat_Contact_BallPos.z);
            }
            return;
        }
        if (g_d_GameSettings.StadiumID == STADIUM_ID_YOHSI_PARK) {
            if (code == 1) {
                animateThrownBall(0x1A4, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.y,
                                  g_Ball.AtBat_Contact_BallPos.z);
                return;
            }
        } else if (g_d_GameSettings.StadiumID == STADIUM_ID_PEACH_GARDEN) {
            if (code == 6) {
                animateThrownBall(0x1A1, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.y,
                                  g_Ball.AtBat_Contact_BallPos.z);
                return;
            } else if (code == 10) {
                animateThrownBall(0x1A2, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.y,
                                  g_Ball.AtBat_Contact_BallPos.z);
                return;
            } else if (code == 9) {
                animateThrownBall(0x1A0, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.y,
                                  g_Ball.AtBat_Contact_BallPos.z);
                return;
            }
        } else if (g_d_GameSettings.StadiumID == STADIUM_ID_DK_JUNGLE) {
            if (code == 10) {
                animateThrownBall(0x1A2, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.y,
                                  g_Ball.AtBat_Contact_BallPos.z);
                return;
            }
        }

        animateThrownBall(0x17E, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.y,
                          g_Ball.AtBat_Contact_BallPos.z);
    }
}

// .text:0x0008CD74 size:0xC4C mapped:0x806CBE08
#pragma dont_inline on
void handleGameSound(void) {
    u8 status = g_GameLogic.gameStatus;
    u8* actorPool;
    u8* actor;
    s8 actorIndex;

    if (status == GAME_STATUS_PAUSED || g_Minigame.pauseInd != 0) {
        return;
    }

    if (status == GAME_STATUS_AT_BAT) {
        if (g_Pitcher.windupCountdownUntilBallReleased == 0 && g_Ball.pitchHangtimeCounter == 0) {
            if (sound_crowd_EffectsStruct._34 == 0) {
                if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_Practice.practiceLevel == 4) {
                    playSoundEffect(0x1AE);
                } else if (g_Minigame.GameMode_MiniGame != MINI_GAME_ID_BOBOMB_DERBY &&
                           g_Minigame.GameMode_MiniGame != MINI_GAME_ID_BARREL_BATTER) {
                    if (g_GameLogic.PauseSimulationFrameCount == 5) {
                        playCharacterSound(g_Pitcher.charID, 6);
                    } else if (g_Pitcher.ChargePitchType == 3) {
                        playSoundEffect(0x188);
                        playCharacterSound(g_Pitcher.charID, 6);
                    } else if (g_Pitcher.ChargePitchType != 0) {
                        if (g_Pitcher.starPitchType == 0) {
                            playCharacterSound(g_Pitcher.charID, 5);
                        }
                        playSoundEffect(0x187);
                    } else if (g_Pitcher.TypeOfPitch == 2) {
                        playSoundEffect(0x17D);
                    } else {
                        playSoundEffect(0x186);
                    }
                }
            }
            sound_crowd_EffectsStruct._34 = 1;
        }

        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY && g_Ball.pitchHangtimeCounter == 1 &&
            g_Pitcher.starPitchInd != 0) {
            playSoundEffect(0x19E);
            lbl_3_bss_1774[2] = playSoundEffect(0x18F);
        }

        if (g_GameLogic.PauseSimulationFrameCount == 1 && g_Pitcher.starPitchType != 0) {
            playSoundEffect(0x19E);
            switch (g_Pitcher.starPitchType) {
            case 1:
            case 2:
                lbl_3_bss_1774[2] = playSoundEffect(0x18F);
                break;
            case 3:
            case 4:
                lbl_3_bss_1774[2] = playSoundEffect(0x18C);
                break;
            case 5:
            case 6:
                lbl_3_bss_1774[2] = playSoundEffect(0x18D);
                break;
            case 7:
            case 8:
                lbl_3_bss_1774[2] = playSoundEffect(0x190);
                break;
            case 9:
            case 10:
                lbl_3_bss_1774[2] = playSoundEffect(0x18E);
                break;
            case 11:
            case 12:
                lbl_3_bss_1774[2] = playSoundEffect(0x19A);
                break;
            }
        }

        if (g_Ball.pitchHangtimeCounter > 0 && g_Pitcher.framesUntilUnhittable < 30 &&
            hugeAnimStruct[0x307D] == 0) {
            actor = *(u8**)(hugeAnimStruct + 0x2C74);
            if (g_d_GameSettings.minigamesEnabled) {
                actorIndex = ((s8*)&g_Minigame)[0x18CC + g_Minigame.rosterID];
                actor = hugeAnimStruct + 0xC04 + actorIndex * 0x27C;
            }
            if (actor != NULL && *(s16*)(actor + 0x62) == 0x60 && *(s16*)(actor + 0x6A) == 5) {
                playCharacterSound(g_Batter.charID, 3);
            }
        }
    }

    if (hugeAnimStruct[0x307D] == 0) {
        if (sound_crowd_EffectsStruct._2B != 0 && g_Ball.framesSinceHit == 2) {
            sound_crowd_EffectsStruct._2B = 0;
            sndFXKeyOff(lbl_3_bss_1774[2]);
            if (g_Batter.isBunting != 0) {
                playSoundEffect(0x153);
            } else if (g_Batter.captainStarSwingActivated != 0) {
                switch (g_Batter.captainStarSwingActivated) {
                case 1:
                case 2:
                    lbl_3_bss_1774[1] = playSoundEffect(0x194);
                    break;
                case 3:
                case 4:
                    lbl_3_bss_1774[1] = playSoundEffect(0x191);
                    break;
                case 5:
                case 6:
                    lbl_3_bss_1774[1] = playSoundEffect(0x192);
                    break;
                case 7:
                case 8:
                    lbl_3_bss_1774[1] = playSoundEffect(0x195);
                    break;
                case 9:
                case 10:
                    lbl_3_bss_1774[1] = playSoundEffect(0x193);
                    break;
                case 11:
                case 12:
                    lbl_3_bss_1774[1] = playSoundEffect(0x199);
                    lbl_3_bss_1760[0] = 0;
                    break;
                }
                playSoundEffect(0x184);
                playSoundEffect(0x185);
                playCharacterSound(g_Batter.charID, 0);
            } else if (g_Batter.charID == 2) {
                playSoundEffect(0x1AF);
            } else if (g_Batter.charID == 0x26) {
                playSoundEffect(0x1B0);
            } else if (g_Batter.displayContactSprite != 0) {
                playSoundEffect(0x184);
                playSoundEffect(0x185);
            } else if (g_Batter.contactType == 2) {
                playSoundEffect(0x184);
                playCharacterSound(g_Batter.charID, 0);
            } else if (g_Batter.contactType >= 1 && g_Batter.contactType <= 3) {
                playCharacterSound(g_Batter.charID, 0);
                playSoundEffect(0x184);
            } else {
                playSoundEffect(0x183);
            }
        }

        if (g_Batter.chargeStatus == 1 && g_GameLogic.gameStatus == GAME_STATUS_AT_BAT &&
            g_Batter.chargeFrames < g_Batter.frameChargeDownBegins && g_Batter.chargeFrames == 1) {
            sound_crowd_EffectsStruct._1C = playCharacterSound(g_Batter.charID, 2);
        }
    }

    if (g_Batter.captainStarSwingActivated == 0xB && lbl_3_bss_1760[0] == 0 &&
        g_Ball.physicsSubstruct.velocity.y <= -1.43 && g_Ball.physicsSubstruct.velocity.y >= -1.45) {
        sndFXKeyOff(lbl_3_bss_1774[2]);
        lbl_3_bss_1774[1] = playSoundEffect(0x19B);
        lbl_3_bss_1760[0] = 1;
    }

    if (g_GameLogic.gameStatus != GAME_STATUS_AT_BAT && g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL &&
        lbl_3_bss_1774[2] != 0) {
        sndFXKeyOff(lbl_3_bss_1774[2]);
    }
    if (g_Ball.AtBat_Contact_BallPos.z < -3.0f && lbl_3_bss_1774[2] != 0) {
        sndFXKeyOff(lbl_3_bss_1774[2]);
    }
    if (g_Pitcher.strikeOutOrWalk == 3) {
        sndFXKeyOff(lbl_3_bss_1774[2]);
    }
    if (lbl_3_bss_1774[1] != 0) {
        if (g_Ball.currentStarSwing == 0 || g_Ball.deadBallReason != 0) {
            sndFXKeyOff(lbl_3_bss_1774[1]);
        }
    }
}
#pragma dont_inline reset

// .text:0x0008D9C0 size:0xC0 mapped:0x806CCA54
void fn_3_8D9C0(void) {
    camera_803c639c_s* cam;
    Vec pos;
    Vec dir;
    Vec lookDir;
    f32 mag;

    handleGameSound();
    cam = returnFloatFromModeIndex(0);

    pos.x = cam->eye.x;
    pos.y = cam->eye.y;
    pos.z = cam->eye.z;

    dir.x = lbl_3_rodata_157C;
    dir.y = lbl_3_rodata_157C;
    dir.z = lbl_3_rodata_157C;

    PSVECSubtract(&cam->target, &cam->eye, &lookDir);
    mag = PSVECMag(&lookDir);
    if (mag != lbl_3_rodata_157C) {
        PSVECNormalize(&lookDir, &lookDir);
    }

    if (sndEmitter.listener.room != NULL) {
        sndUpdateListener(&sndEmitter.listener, (SND_FVECTOR*)&pos, (SND_FVECTOR*)&dir,
                           (SND_FVECTOR*)&lookDir, &lbl_3_data_8D70, 0x7f, NULL);
    }
}

// .text:0x0008DA80 size:0x1748 mapped:0x806CCB14
#define MINIGAME_BYTE(off) (((u8*)&g_Minigame)[off])

void soundControl(void) {
    int track = -1;
    BOOL hold = FALSE;
    BOOL paused;
    BOOL result;
    s16 trackId;
    u8 status;
    u8 secondaryMode;
    u8 pauseState;
    u8 minigamesEnabled;
    s8 roster;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        if (g_Practice.tutorialState == TUTORIAL_STATE_0 && g_Practice.practiceState == 0) {
            stadiumMusic(g_d_GameSettings.StadiumID);
        }
    } else if (g_GameLogic.gameStatus == GAME_STATUS_GAME_START_MOVIE &&
               g_GameLogic.FrameCountOfCurrentPitch == 1) {
        stadiumMusic(g_d_GameSettings.StadiumID);
    }

    if (g_GameLogic.framesOfExitingToMenu != 0) {
        return;
    }
    status = g_GameLogic.gameStatus;
    if (status == GAME_STATUS_CHAMPIONSHIP) {
        return;
    }
    if (status == GAME_STATUS_MVP_END_GAME && !g_d_GameSettings.minigamesEnabled) {
        return;
    }

    if (sound_crowd_EffectsStruct._33 != 0 && status == GAME_STATUS_DEFAULT) {
        sound_crowd_EffectsStruct._33--;
    }
    fn_3_8D9C0();

    if (audioFileDescriptors.enableMusic == 0) {
        if (sound_crowd_EffectsStruct._04 != -1) {
            if (sndSeqGetValid(sound_crowd_EffectsStruct._04)) {
                sndSeqVolume(0, 0, sound_crowd_EffectsStruct._04, SND_SEQVOL_STOP);
            }
            sound_crowd_EffectsStruct._04 = -1;
        }
        return;
    }

    sound_crowd_EffectsStruct._22 = sound_crowd_EffectsStruct._20;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        secondaryMode = g_GameLogic.secondaryGameMode;
        if (secondaryMode == SECONDARY_GAME_MODE_PRACTICE_MENU ||
            secondaryMode == SECONDARY_GAME_MODE_RETURN_TO_MENU ||
            secondaryMode == SECONDARY_GAME_MODE_LOAD_PRACTICE_SCREEN) {
            track = -1;
            goto pick;
        }
        if (g_Practice.tutorialState == TUTORIAL_STATE_0) {
            track = -1;
            goto pick;
        }
        if (g_Practice._19F != 0) {
            pauseState = pauseControl[0x1D2];
            if (pauseState == 6 || (u8)(pauseState - 7) <= 1 || pauseState == 9) {
                track = -1;
                goto pick;
            }
        }
        if (g_Practice._1C7 != 0) {
            pauseState = pauseControl[0x1D2];
            if (pauseState == 6 || pauseState == 7) {
                track = -1;
                goto pick;
            }
        }
        if (g_Practice.practiceType_2 == 4) {
            if (g_GameLogic.gameStatus != GAME_STATUS_GAME_START_MOVIE) {
                goto common;
            }
            return;
        }
        track = 0x15;
        if (g_Ball.deadBallReason == 1 && secondaryMode != SECONDARY_GAME_MODE_PRACTICE_PITCHING) {
            track = 0;
            goto common;
        }
        goto pick;
    }

    minigamesEnabled = g_d_GameSettings.minigamesEnabled;
    if (minigamesEnabled != 0 && g_GameLogic.gameStatus == GAME_STATUS_MINIGAME_READY) {
        track = -1;
        goto pick;
    }

    status = g_GameLogic.gameStatus;
    if (status == GAME_STATUS_0x27 || status == GAME_STATUS_0x24 || status == GAME_STATUS_MINIGAME_POST_MENU) {
        roster = g_Minigame.soloPlayerSlot;
        if (roster >= 0 && g_Minigame.grandPrixInd != 0) {
            if (status == GAME_STATUS_MINIGAME_POST_MENU) {
                return;
            }
            if (status == GAME_STATUS_0x24) {
                if (g_GameLogic.FrameCountOfCurrentPitch != 1) {
                    return;
                }
                fn_3_8C104(-1);
                return;
            }
            if (MINIGAME_BYTE(0x18E8 + roster) == 1 && g_Minigame.challenge_minigame_haven_tWonYetIndicator == 0) {
                track = 0xC;
            } else {
                track = 0xD;
            }
            goto pick;
        }
    }

    if (minigamesEnabled != 0 &&
        (status == GAME_STATUS_MVP_END_GAME || status == GAME_STATUS_0x24 ||
         g_GameLogic._125 == 8 || status == GAME_STATUS_MINIGAME_POST_MENU ||
         status == GAME_STATUS_0x27 || status == GAME_STATUS_0x26)) {
        if (status == GAME_STATUS_MVP_END_GAME || status == GAME_STATUS_0x24 ||
            status == GAME_STATUS_MINIGAME_POST_MENU || status == GAME_STATUS_0x26 ||
            status == GAME_STATUS_0x27) {
            if (status == GAME_STATUS_MINIGAME_POST_MENU) {
                if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                    pauseState = pauseControl[0x1D2];
                    if (pauseState == 0xA || pauseState == 4 || pauseState == 5) {
                        goto fadeOutShort;
                    }
                } else {
                    pauseState = pauseControl[0x1D2];
                    if (pauseState == 9 || (u8)(pauseState - 6) <= 1) {
                        goto fadeOutShort;
                    }
                }
            }
            if (status == GAME_STATUS_0x26) {
                return;
            }
            if (!g_d_GameSettings.exhibitionMatchInd) {
                if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY ||
                    g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER) {
                    if (g_Minigame.winLossResult == 1) {
                        track = 0xC;
                    } else {
                        track = 0xD;
                    }
                } else {
                    roster = g_Minigame.soloPlayerSlot;
                    if (MINIGAME_BYTE(0x18E8 + roster) == 1 &&
                        g_Minigame.challenge_minigame_haven_tWonYetIndicator == 0) {
                        track = 0xC;
                    } else {
                        track = 0xD;
                    }
                }
                goto pick;
            }
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                roster = g_Minigame.soloPlayerSlot;
                if (roster >= 0) {
                    if (MINIGAME_BYTE(0x18E8 + roster) == 1 &&
                        g_Minigame.challenge_minigame_haven_tWonYetIndicator == 0) {
                        track = 5;
                    } else {
                        track = 7;
                    }
                } else {
                    track = 5;
                }
                goto pick;
            }
            if (g_Minigame.multiPlayerInd != 0) {
                if (g_Minigame.grandPrixInd != 0 && g_Minigame.humanPlayerCount == 1) {
                    roster = g_Minigame.soloPlayerSlot;
                    if (MINIGAME_BYTE(0x18E8 + roster) == 1 &&
                        g_Minigame.challenge_minigame_haven_tWonYetIndicator == 0) {
                        track = 5;
                    } else {
                        track = 7;
                    }
                } else if (g_Minigame.challenge_minigame_haven_tWonYetIndicator != 0) {
                    track = 7;
                } else {
                    track = 5;
                }
                goto pick;
            }
            if (g_Minigame.soloMinigameDifficulty == 3 && g_Minigame.grandPrixInd == 0) {
                if (g_GameLogic.FrameCountOfCurrentPitch == 0) {
                    return;
                }
                if (g_Minigame.newRecordRank == 1) {
                    track = 0xE;
                } else if (g_Minigame.newRecordRank != 0) {
                    track = 0xF;
                } else {
                    track = 7;
                }
                goto pick;
            }
            if (g_Minigame.winLossResult == 1) {
                track = 5;
            } else {
                track = 7;
            }
            goto pick;
        }
        if (g_GameLogic._125 == 8) {
            sndSeqLoop(sound_crowd_EffectsStruct._08, 0);
        }
        goto notMinigame;
    }

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        if (status >= GAME_STATUS_0x1B) {
            track = -1;
            goto pick;
        }
        if (status == GAME_STATUS_GAME_START_MOVIE) {
            track = 6;
            goto pick;
        }
        sndSeqVolume(lbl_3_data_8284[134], 0xF, sound_crowd_EffectsStruct._04, SND_SEQVOL_CONTINUE);
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_STAR_DASH) {
            if ((s8)g_Minigame.starDashStarHolder >= 0) {
                hold = TRUE;
                if (g_Minigame.pauseInd != 0) {
                    sndFXKeyOff(sound_crowd_EffectsStruct._04);
                } else if (sound_crowd_EffectsStruct._20 == 0x13) {
                    if (sndFXCheck(sound_crowd_EffectsStruct._04) == -1) {
                        sound_crowd_EffectsStruct._04 = callSfx(0x2ED);
                    }
                }
                track = 0x13;
            } else {
                if (sndFXCheck(sound_crowd_EffectsStruct._04) != -1) {
                    sndFXKeyOff(sound_crowd_EffectsStruct._04);
                }
                track = 0x15;
            }
        } else {
            track = 0x15;
        }
        if (g_Minigame.pauseInd != 0) {
            pauseState = pauseControl[0x1D2];
            if (pauseState == 7 || pauseState == 9) {
                track = -1;
                goto pick;
            }
            fn_800A8878(lbl_800E88A4[g_d_GameSettings.StadiumID * 2 + 1], lbl_800E88A4[g_d_GameSettings.StadiumID * 2 + 1]);
        } else {
            fn_800A8878(lbl_800E88A4[g_d_GameSettings.StadiumID * 2], lbl_800E88A4[g_d_GameSettings.StadiumID * 2]);
        }
        goto pick;
    }

    if (minigamesEnabled != 0) {
        if (status == GAME_STATUS_MINIGAME_POST_MENU || status == GAME_STATUS_PAUSED ||
            status == GAME_STATUS_HOW_TO_PLAY_SCREEN || g_Minigame._19CE != 0) {
            if (sound_crowd_EffectsStruct._22 != -1) {
                fn_800A8878(lbl_800E88A4[0x13], lbl_800E88A4[0x13]);
            }
            sound_crowd_EffectsStruct._20 = -1;
            return;
        }
        fn_800A8878(lbl_800E88A4[0x12], lbl_800E88A4[0x12]);
        if (g_GameLogic.gameStatus >= GAME_STATUS_0x1B) {
            return;
        }
        if (g_GameLogic.gameStatus == GAME_STATUS_GAME_START_MOVIE) {
            track = 0;
        } else {
            track = 0x15;
        }
        goto pick;
    }

notMinigame:
    status = g_GameLogic.gameStatus;
    if (status == GAME_STATUS_GAME_START_MOVIE && g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE) {
        track = 0;
        goto pick;
    }
    if (status == GAME_STATUS_END_OF_GAME) {
        track = 1;
        goto pick;
    }
    if (status == GAME_STATUS_INNING_TRANSITION) {
        track = 2;
        goto pick;
    }
    if (status == GAME_STATUS_TRANSITION) {
        track = -1;
        hold = TRUE;
        if (g_Strikes.outs == 3) {
            goto pick;
        }
        if (g_Stats.replayPending != 0) {
            goto pick;
        }
        if (g_Pitcher.walkedInRunInd != 0) {
            playSoundEffect(0x198);
            goto pick;
        }
        if (g_GameLogic.EventTriggers_EndOfGame != 0) {
            goto pick;
        }
        playSoundEffect(0x197);
        goto pick;
    }

common:
    if (g_GameLogic.gameStatus == GAME_STATUS_PAUSED) {
        if (pauseControl[0x1D1] == 1) {
            goto pick;
        }
        if (sound_crowd_EffectsStruct._20 != 0x15) {
            sound_crowd_EffectsStruct._20 = 0x15;
            sound_crowd_EffectsStruct._22 = 0x15;
            fn_3_8C104(0);
        }
    }

    if (g_Stats.replayInd != 0) {
        track = 0x16;
        if (g_Stats.replayPending == 4) {
            track = -1;
            hold = TRUE;
        }
        if (g_Stats.playFrameCounter > g_Stats._0028 - 30) {
            track = -1;
            hold = TRUE;
        }
        goto pick;
    }

    status = g_GameLogic.gameStatus;
    if (status == GAME_STATUS_HOMERUN_END) {
        track = 0x17;
        goto pick;
    }
    if (status == GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY || status == GAME_STATUS_DEFAULT) {
        return;
    }
    if (hugeAnimStruct[0x2D46] != 0 || hugeAnimStruct[0x2D52] != 0) {
        return;
    }

    if (!g_d_GameSettings.exhibitionMatchInd && lbl_3_common_bss_37400[0x46] != 0) {
        if (status == GAME_STATUS_STAR_CHANCE_VS) {
            if (((u8*)&g_GameLogic)[g_GameLogic.teamFielding + 0x133] == 0) {
                sound_crowd_EffectsStruct._32 = 1;
                track = 9;
                goto pick;
            }
        }
        if (sound_crowd_EffectsStruct._32 == 0) {
            if (status == GAME_STATUS_AT_BAT && ((u8*)&g_GameLogic)[g_GameLogic.teamFielding + 0x133] == 0) {
                sound_crowd_EffectsStruct._32 = 2;
                track = 0x12;
                goto pick;
            }
        } else if (sound_crowd_EffectsStruct._32 == 2) {
            if (animRelated[0xB3] != 0) {
                sound_crowd_EffectsStruct._32 = 2;
                track = 0x12;
                goto pick;
            }
        }
        if ((status == GAME_STATUS_AT_BAT || status == GAME_STATUS_LIVE_BALL) && g_Stats.replayInd == 0) {
            if (lbl_3_common_bss_37400[0x47] == 1) {
                if (g_Ball.deadBallReason != 1) {
                    track = 0xB;
                    if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != 0) {
                        sound_crowd_EffectsStruct._33 = 2;
                    }
                    goto pick;
                }
            } else if (lbl_3_common_bss_37400[0x47] == 2) {
                if (g_Ball.deadBallReason != 1) {
                    track = 0xA;
                    if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != 0) {
                        sound_crowd_EffectsStruct._33 = 2;
                    }
                    goto pick;
                }
            }
        }
    }

    if (status == GAME_STATUS_STAR_CHANCE_VS && g_GameLogic.playOverInd != 0) {
        track = 0x10;
        goto pick;
    }
    if (status == GAME_STATUS_BATTER_CELEBRATION) {
        track = 0x11;
        goto pick;
    }
    if (status == GAME_STATUS_STAR_CHANCE_VS && *(s32*)((u8*)unkStructPtr._0000 + 0x92C) == 0x60 &&
        g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
        *(s32*)((u8*)unkStructPtr._0000 + 0x92C) = 0;
        sound_crowd_EffectsStruct._2E = 1;
        track = 8;
        goto pick;
    }

    if (sound_crowd_EffectsStruct._2E != 0) {
        if (sound_crowd_EffectsStruct._27 == 0) {
            sound_crowd_EffectsStruct._2E = 0;
        }
        track = 8;
        goto pick;
    }
    if (lbl_3_common_bss_134C4[0x25C] != 0 && g_Ball.deadBallReason != 1 &&
        *(s32*)((u8*)unkStructPtr._0000 + 0x92C) != 0) {
        track = 4;
        goto pick;
    }
    if (status == GAME_STATUS_HOMERUN_END) {
        return;
    }

    if (g_Ball.deadBallReason == 1) {
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
            track = 0;
        } else {
            track = 3;
            goto pick;
        }
    }

    if (sound_crowd_EffectsStruct._2A == 1 && sound_crowd_EffectsStruct._24 != 0) {
        sound_crowd_EffectsStruct._24--;
        if (sound_crowd_EffectsStruct._24 == 0) {
            addToCircularBuffer(3, 0, 0);
        } else {
            fn_3_8C4F0(sound_crowd_EffectsStruct._24, 0);
        }
    }

    if (sound_crowd_EffectsStruct._2A == 2) {
        if (sound_crowd_EffectsStruct._33 != 0) {
            sound_crowd_EffectsStruct._33 = 0;
            sound_crowd_EffectsStruct._20 = 0x15;
        }
        if (sound_crowd_EffectsStruct._24 == 0x78) {
            fn_3_8C104(0);
        }
        paused = g_GameLogic.gameStatus == GAME_STATUS_PAUSED;
        result = fn_3_8C2DC(sound_crowd_EffectsStruct._24, paused);
        if (!result) {
            sound_crowd_EffectsStruct._2A = 0;
        }
        sound_crowd_EffectsStruct._24--;
    }

    if (g_Ball.deadBallReason == 1 && g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        goto pick;
    }
    status = g_GameLogic.gameStatus;
    if (status == GAME_STATUS_LIVE_BALL) {
        if (sound_crowd_EffectsStruct._29 != 0) {
            sound_crowd_EffectsStruct._29--;
        }
        return;
    }
    if (sound_crowd_EffectsStruct._2A != 0) {
        return;
    }
    if (status == GAME_STATUS_PAUSED) {
        return;
    }
    if (sound_crowd_EffectsStruct._33 != 0) {
        track = 0x15;
    } else if (g_Strikes.storedOuts == 0) {
        track = 0x15;
    } else if (storedInningInfo.consecutiveHits == 0) {
        playOverSounds(-1);
        sound_crowd_EffectsStruct._20 = -1;
        return;
    } else {
        track = 0x15;
    }
    goto pick;

fadeOutShort:
    playOverSounds(0xC);
    sound_crowd_EffectsStruct._20 = -1;
    return;

pick:
    if (sound_crowd_EffectsStruct._22 == track) {
        return;
    }
    if (sound_crowd_EffectsStruct._20 == 8) {
        if (sndSeqGetValid(sound_crowd_EffectsStruct._08)) {
            return;
        }
    }

    if (sound_crowd_EffectsStruct._28 == 0) {
        sound_crowd_EffectsStruct._28 = 1;
        sound_crowd_EffectsStruct._27 = 0x14;
        fn_3_903B8();
    } else if (sound_crowd_EffectsStruct._27 != 0) {
        sound_crowd_EffectsStruct._27--;
    }

    if (sound_crowd_EffectsStruct._27 != 0 && !hold) {
        return;
    }

    if (sound_crowd_EffectsStruct._04 != -1) {
        if (sndSeqGetValid(sound_crowd_EffectsStruct._04)) {
            sndSeqVolume(0, 0, sound_crowd_EffectsStruct._04, SND_SEQVOL_STOP);
        }
        sound_crowd_EffectsStruct._04 = -1;
        return;
    }

    trackId = track;
    sound_crowd_EffectsStruct._28 = 0;
    sound_crowd_EffectsStruct._20 = track;

    if (trackId == -1) {
        if (hold) {
            addToCircularBuffer(3, 0, 0);
        } else {
            addToCircularBuffer(4, 0, 0);
        }
        return;
    }

    if (trackId == 0x15 || track == 0x16 || track == 0x17) {
        if ((u16)(trackId - 0x15) <= 1 || trackId == 0x17) {
            if (trackId == sound_crowd_EffectsStruct._22) {
                return;
            }
            fn_3_8C104(-1);
            return;
        }
        addToCircularBuffer(4, 0, 0);
        fn_3_90674(sound_crowd_EffectsStruct._20);
        return;
    }

    fn_3_9056C(trackId);
    if (track != 4 && track != 0) {
        addToCircularBuffer(4, 0, 0);
    }
}

// .text:0x0008F1C8 size:0x54 mapped:0x806CE25C
void fn_3_8F1C8(void) {
    sound_crowd_EffectsStruct._20 = -1;
    sound_crowd_EffectsStruct._22 = -1;
    sound_crowd_EffectsStruct._29 = 0;
    sound_crowd_EffectsStruct._2A = 0;
    lbl_3_bss_1768 = (SoundReplayQueue*)insertGraphicDrawingFunction(fn_3_8B094, 0);
}

static inline BOOL stadiumHasCrowdSounds(int stadiumID) {
    BOOL result = FALSE;

    if (stadiumID == STADIUM_ID_BOWSERS_CASTLE || stadiumID == STADIUM_ID_WARIO_PALACE ||
        stadiumID == STADIUM_ID_YOHSI_PARK || stadiumID == STADIUM_ID_DK_JUNGLE) {
        result = TRUE;
    }
    return result;
}

// .text:0x0008F21C size:0x9F0 mapped:0x806CE2B0
void soundFxRelated(void) {
    BOOL stopVoices = FALSE;
    BOOL crowdStadium;
    BOOL playHit;
    u8 lastState;
    int i;
    u32* slot;
    s16 result;

    crowdStadium = stadiumHasCrowdSounds(g_d_GameSettings.StadiumID);

    if (crowdStadium) {
        if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != 0) {
            lastState = sound_crowd_EffectsStruct._26;
            for (i = 1; i < 4; i++) {
                if (lastState <= 1 &&
                    g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_OUT_DURING_PLAY) {
                    stopVoices = TRUE;
                    goto checkStop;
                }
            }
        }

        if (g_Ball.framesSinceHit <= 0) {
            return;
        }

        if ((g_Ball.ballInitialHitDoneInd != 0 && g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_LANDED &&
             g_Ball.ballZoneAwayFromHome >= 3 && sound_crowd_EffectsStruct._26 < 2) ||
            (g_Runners[0].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
             g_Runners[0].currentBase != 0 && g_Runners[0].forceOutCd == 0 &&
             (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_LANDED ||
              g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FIELDED) &&
             g_Strikes.outs == g_Strikes.storedOuts)) {
            sound_crowd_EffectsStruct._26 = 2;
            if (sound_crowd_EffectsStruct._14 == -1) {
                sound_crowd_EffectsStruct._14 = sndFXStartEx(0x156, 0, 0x3f, 0);
                if (g_Stats.replayInd == 0 && g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES) {
                    playSoundEffect(0x196);
                }
            }
        }
        return;
    }

    if (g_GameLogic.gameStatus == GAME_STATUS_INNING_TRANSITION) {
        stopVoices = TRUE;
        goto checkStop;
    }

    if (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT) {
        if (g_Ball.pitchHangtimeCounter == 10) {
            for (i = 1; i < 4; i++) {
                if (g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
                    g_Runners[i].furthestBaseForcedToGoToOnWalk != 0) {
                    if (sound_crowd_EffectsStruct._10 == -1) {
                        sound_crowd_EffectsStruct._10 = playSoundEffect(0x155);
                    }
                    goto checkStop;
                }
            }
        }
        goto checkStop;
    }

    if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != 0) {
        for (i = 1; i < 4; i++) {
            lastState = sound_crowd_EffectsStruct._26;
            if (lastState == 0 &&
                ((g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
                  g_Runners[i].baseStandingOn > i) ||
                 g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY)) {
                sound_crowd_EffectsStruct._26 = 1;
                if (sound_crowd_EffectsStruct._10 == -1) {
                    sound_crowd_EffectsStruct._10 = playSoundEffect(0x155);
                }
            } else if (lastState <= 1 &&
                       g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_OUT_DURING_PLAY) {
                sound_crowd_EffectsStruct._26 = 2;
                playSoundEffect(0x158);
                stopVoices = TRUE;
                goto checkStop;
            }
        }
        goto checkStop;
    }

    if (g_Ball.framesSinceHit <= 0) {
        goto checkStop;
    }

    if (g_Ball.framesSinceHit > 20 && sound_crowd_EffectsStruct._26 == 0) {
        sound_crowd_EffectsStruct._26 = 1;
        if (g_Batter.isBunting != 0) {
            if (g_RunningLogic._02 == 1 || (g_RunningLogic._02 & 0x1000)) {
                if (sound_crowd_EffectsStruct._10 == -1) {
                    sound_crowd_EffectsStruct._10 = playSoundEffect(0x155);
                }
            }
        } else if (g_Ball.Hit_HorizontalPower > 0x96 &&
                   (g_Ball.Hit_VerticalAngle > 0xF80 || g_Ball.Hit_VerticalAngle < 0x200) &&
                   g_Ball.Hit_HorizontalAngle > 0x80 && g_Ball.Hit_HorizontalAngle < 0x780) {
            if (sound_crowd_EffectsStruct._10 == -1) {
                sound_crowd_EffectsStruct._10 = playSoundEffect(0x155);
            }
        }
    }

    if ((g_Ball.ballInitialHitDoneInd != 0 && g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_LANDED &&
         g_Ball.ballZoneAwayFromHome >= 3 && sound_crowd_EffectsStruct._26 < 2) ||
        (g_Runners[0].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
         g_Runners[0].currentBase != 0 && g_Runners[0].forceOutCd == 0 &&
         (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_LANDED ||
          g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FIELDED) &&
         g_Strikes.outs == g_Strikes.storedOuts)) {
        sound_crowd_EffectsStruct._26 = 2;
        if (sound_crowd_EffectsStruct._14 == -1) {
            sound_crowd_EffectsStruct._14 = playSoundEffect(0x156);
            if (g_Stats.replayInd == 0 && g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES) {
                playSoundEffect(0x196);
            }
        }
    }

    if (g_Ball.deadBallReason == 1 && sound_crowd_EffectsStruct._26 < 9) {
        sound_crowd_EffectsStruct._26 = 9;
        if (sound_crowd_EffectsStruct._14 == -1) {
            sound_crowd_EffectsStruct._14 = playSoundEffect(0x156);
        }
    }

    if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FOUL && sound_crowd_EffectsStruct._26 < 9) {
        if (g_Ball.deadBallReason == 2) {
            if (g_Ball.matchFramesAndBallAngle.ballOverWallFrames == 30) {
                sound_crowd_EffectsStruct._26 = 9;
                stopVoices = TRUE;
                if (foul_isBallWithin3mFair(g_Ball.deadballLastLoc.x, g_Ball.deadballLastLoc.z)) {
                    playSoundEffect(0x158);
                }
            }
        } else if (g_Ball.framesSinceBallHitGroundOrWasCaught == 30) {
            sound_crowd_EffectsStruct._26 = 9;
            stopVoices = TRUE;
            if (foul_isBallWithin3mFair(g_Ball.landingSpotLocation.x, g_Ball.landingSpotLocation.z)) {
                if (g_Ball.ballZoneAwayFromHome == 4 ||
                    (g_Ball.Hit_HorizontalPower > 0x96 &&
                     (g_Ball.Hit_VerticalAngle > 0xFC0 || g_Ball.Hit_VerticalAngle < 0x200))) {
                    playSoundEffect(0x157);
                }
            }
        }
    }

    if (g_Runners[0].runnerOnFieldOrOutOrScored == RUNNER_STATUS_OUT_DURING_PLAY &&
        g_Runners[0].framesSinceOut == 20 && g_Scores._C2 == 0 &&
        !(g_Runners[3].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
          g_Runners[3].fractionalBasesRan > 3.5f)) {
        playHit = FALSE;
        result = storedInningInfo.abResultTemporary;
        if (result == 0x15 || result == 0x18 || result == 0x16) {
            playHit = TRUE;
        }
        if (result == 0x12) {
            if (g_Ball.ballZoneAwayFromHome <= 1 || foul_checkIfFoul(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z)) {
                playHit = TRUE;
            }
        }
        if (storedInningInfo.abResultTemporary == 0x13) {
            if (g_Ball.ballZoneAwayFromHome <= 1 && g_Ball.Hit_HorizontalPower > 0xB4) {
                playHit = TRUE;
            }
        }
        if (playHit) {
            stopVoices = TRUE;
            playSoundEffect(0x157);
        }
    }

checkStop:
    if (stopVoices) {
        if (sound_crowd_EffectsStruct._10 != -1) {
            sndFXKeyOff(sound_crowd_EffectsStruct._10);
            sound_crowd_EffectsStruct._10 = -1;
        }
        if (sound_crowd_EffectsStruct._14 != -1) {
            sndFXKeyOff(sound_crowd_EffectsStruct._14);
            sound_crowd_EffectsStruct._14 = -1;
        }
    }

    if (g_GameLogic.gameStatus == GAME_STATUS_PAUSED) {
        slot = (u32*)&sound_crowd_EffectsStruct;
        for (i = 0; i < 3; i++) {
            if (slot[i + 3] != -1) {
                sndFXKeyOff(slot[i + 3]);
                slot[i + 3] = -1;
            }
        }
    }
}

// .text:0x0008FC0C size:0x74 mapped:0x806CECA0
void newAtBatPlaySound(void) {
    sound_crowd_EffectsStruct._26 = 0;

    if (sound_crowd_EffectsStruct._10 != -1) {
        sndFXKeyOff(sound_crowd_EffectsStruct._10);
        sound_crowd_EffectsStruct._10 = -1;
    }

    if (sound_crowd_EffectsStruct._14 != -1) {
        sndFXKeyOff(sound_crowd_EffectsStruct._14);
        sound_crowd_EffectsStruct._14 = -1;
    }
}

// .text:0x0008FC80 size:0x298 mapped:0x806CED14
void adjustBallSoundEffectBasedOnHeight(void) {
    SND_VOICEID vid;
    int height;
    int clamped;
    int pitch;
    f32 ratio;
    u8 mode = g_GameLogic.secondaryGameMode;

    if (mode != SECONDARY_GAME_MODE_NONE && (u8)(mode - SECONDARY_GAME_MODE_PRACTICE_PITCHING) > 4 &&
        mode != SECONDARY_GAME_MODE_FREE_FIELDING) {
        goto stop;
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        if (g_Practice._19F != 0) {
            goto stop;
        }
        if (g_Practice.tutorialState == TUTORIAL_STATE_0) {
            goto stop;
        }
    }
    if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
        goto stop;
    }
    if (!(g_Ball.AtBat_Contact_BallPos.y > 3.0f)) {
        goto stop;
    }
    if (!(g_Ball.maxYOfHit > 8.0f)) {
        goto stop;
    }
    if (g_Ball.AtBat_Contact_BallPos.y < 6.0f && g_Ball.physicsSubstruct.velocity.y < 0.0f) {
        goto stop;
    }
    if (g_Ball.collisionRelated != 0 || g_Ball.ballCughtByPlantInd != 0 || g_Ball.deadBallReason != 0) {
        goto stop;
    }
    if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_LANDED ||
        (u16)(g_Ball.AtBat_ContactResult - BALL_RESULT_TYPE_FIELDED) <= 1) {
        goto stop;
    }

    if (sound_crowd_EffectsStruct._18 == -1) {
        vid = playSoundEffect(0x17F);
        sound_crowd_EffectsStruct._18 = vid;
        sndFXCtrl(vid, SND_MIDICTRL_VOLUME, (u8)baseSoundPitchFactor[4]);
    }
    height = (int)g_Ball.AtBat_Contact_BallPos.y;
    clamped = height;
    if (height > baseSoundPitchFactor[3]) {
        clamped = baseSoundPitchFactor[3];
    }
    ratio = (f32)(clamped - baseSoundPitchFactor[2]) / (f32)(baseSoundPitchFactor[3] - baseSoundPitchFactor[2]);
    pitch = baseSoundPitchFactor[0] + (int)(ratio * (f32)(baseSoundPitchFactor[1] - baseSoundPitchFactor[0]));
    sndFXCtrl14(sound_crowd_EffectsStruct._18, SND_MIDICTRL_PITCHBEND, (u16)pitch);
    return;

stop:
    if (sound_crowd_EffectsStruct._18 != -1) {
        sndFXKeyOff(sound_crowd_EffectsStruct._18);
        sound_crowd_EffectsStruct._18 = -1;
    }
}

// .text:0x0008FF18 size:0x44 mapped:0x806CEFAC
void initializeSounds(void) {
    sound_crowd_EffectsStruct._0C = -1;
    lbl_3_bss_1780[0] = -1;
    sound_crowd_EffectsStruct._10 = -1;
    sound_crowd_EffectsStruct._14 = -1;
    sound_crowd_EffectsStruct._18 = -1;
    sound_crowd_EffectsStruct._1C = -1;
    sound_crowd_EffectsStruct._28 = 0;
    sound_crowd_EffectsStruct._04 = -1;
    sound_crowd_EffectsStruct._08 = -1;
    sound_crowd_EffectsStruct._2F = 0;
    sound_crowd_EffectsStruct._33 = 0;
}

// .text:0x0008FF5C size:0x108 mapped:0x806CEFF0
SND_VOICEID animateThrownBall(int soundNumber, f32 x, f32 y, f32 z) {
    SND_VOICEID vid;
    int pan = getPanFromWorldPos(x, y, z);

    vid = sndFXStartEx(soundNumber, lbl_3_data_8338[soundNumber - SOUND_EFFECT_MIX_FIRST_ID].volume, pan, 0);
    sndFXCtrl(vid, SND_MIDICTRL_REVERB, lbl_3_data_8338[soundNumber - SOUND_EFFECT_MIX_FIRST_ID].reverb);
    return vid;
}

// .text:0x00090064 size:0xEC mapped:0x806CF0F8
SND_VOICEID callSfx(int soundId) {
    int i;

    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES) {
        OSPanic("m_sound.c", 0x402, "no mini game");
    }

    for (i = 0; i < 57; i++) {
        if (soundId == lbl_3_data_81FC[i]) {
            break;
        }
    }

    if (i == 57) {
        OSPanic("m_sound.c", 0x40D, "no entry mini_se_no");
    }

    return sndFXStartEx((u16)soundId, lbl_3_data_84F4[i], 0x3f, 0);
}

// The reverb bytes for a character's sound codes live 0x180 bytes after
// charSoundFxVol in .data, in an otherwise unnamed foreign table.
#define CHAR_SOUND_REVERB_OFFSET 0x180

// A scale factor embedded in the same unnamed foreign table as
// charSoundFxVol, 0x300 bytes past its start.

// .text:0x00090150 size:0xD0 mapped:0x806CF1E4
SND_VOICEID fn_3_90150(int charID, int soundCode) {
    SND_VOICEID vid;
    u8* reverbTable = charSoundFxVol + soundCode;
    f32 volF = (f32)charSoundFxVol[soundCode];
    f32 reverbF = (f32)reverbTable[CHAR_SOUND_REVERB_OFFSET];
    int fid = soundCode + characterSoundArray[charID];
    int vol = volF * lbl_3_data_8830;
    int reverb = reverbF * lbl_3_data_8830;

    vid = sndFXStartEx(fid, vol, 0x3f, 0);
    sndFXCtrl(vid, SND_MIDICTRL_REVERB, reverb);
    return vid;
}

// .text:0x00090220 size:0x74 mapped:0x806CF2B4
SND_VOICEID playCharacterSound(int charID, int soundCode) {
    SND_VOICEID vid;
    u8* reverbTable = charSoundFxVol + soundCode;
    u8 vol = charSoundFxVol[soundCode];
    int fid = soundCode + characterSoundArray[charID];
    u8 reverb = reverbTable[CHAR_SOUND_REVERB_OFFSET];

    vid = sndFXStartEx(fid, vol, 0x3f, 0);
    sndFXCtrl(vid, SND_MIDICTRL_REVERB, reverb);
    return vid;
}

// .text:0x00090294 size:0x68 mapped:0x806CF328
SND_VOICEID playSoundEffect(int soundNumber) {
    SND_VOICEID vid;

    vid = sndFXStartEx(soundNumber, lbl_3_data_8338[soundNumber - SOUND_EFFECT_MIX_FIRST_ID].volume, 0x3f, 0);
    sndFXCtrl(vid, SND_MIDICTRL_REVERB, lbl_3_data_8338[soundNumber - SOUND_EFFECT_MIX_FIRST_ID].reverb);
    return vid;
}

// .text:0x000902FC size:0x2C mapped:0x806CF390
void fn_3_902FC(void) {
    sndVolume(0, 10, 0xff);
}

// .text:0x00090328 size:0x90 mapped:0x806CF3BC
void playOverSounds(int param) {
    if (param < 0) {
        param = 3000;
    }

    if (sndSeqGetValid(sound_crowd_EffectsStruct._04)) {
        sndSeqVolume(0, param, sound_crowd_EffectsStruct._04, SND_SEQVOL_STOP);
    }

    if (sndSeqGetValid(sound_crowd_EffectsStruct._08)) {
        sndSeqVolume(0, param, sound_crowd_EffectsStruct._08, SND_SEQVOL_STOP);
    }
}

// .text:0x000903B8 size:0x7C mapped:0x806CF44C
void fn_3_903B8(void) {
    if (sndSeqGetValid(sound_crowd_EffectsStruct._04)) {
        sndSeqVolume(0, 0xa0, sound_crowd_EffectsStruct._04, SND_SEQVOL_STOP);
    }

    if (sndSeqGetValid(sound_crowd_EffectsStruct._08)) {
        sndSeqVolume(0, 0xa0, sound_crowd_EffectsStruct._08, SND_SEQVOL_STOP);
    }
}

// .text:0x00090434 size:0x138
void fn_3_90434(void) {
    int i;
    u32* slot;

    jukeboxCmd(3);
    fn_800A88C0();
    fn_800A8B78();
    playOverSounds(0);

    slot = (u32*)&sound_crowd_EffectsStruct;
    for (i = 0; i < 3; i++) {
        if (slot[i + 3] != -1) {
            sndFXKeyOff(slot[i + 3]);
            slot[i + 3] = -1;
        }
    }

    fn_3_8BDF4();
}

// .text:0x0009056C size:0x108
BOOL fn_3_9056C(int index) {
    SeqPlayEntry* entry;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        entry = (SeqPlayEntry*)lbl_3_data_8954 + index;
    } else {
        entry = (SeqPlayEntry*)lbl_3_data_88E0 + index;
    }

    if (sndSeqGetValid(sound_crowd_EffectsStruct._08)) {
        sndSeqVolume(0, 0, sound_crowd_EffectsStruct._08, SND_SEQVOL_STOP);
        return FALSE;
    }

    sound_crowd_EffectsStruct._08 =
        sndSeqPlayEx(entry->sgid, entry->sid, ((void**)lbl_3_bss_1774[0])[index], NULL, 0);
    audioFileDescriptors.musicVolume = lbl_3_data_830C[index * 2];
    sndSeqVolume(lbl_3_data_830C[index * 2], 0, sound_crowd_EffectsStruct._08, SND_SEQVOL_CONTINUE);
    return TRUE;
}

// .text:0x00090674 size:0x88 mapped:0x806CF708
void fn_3_90674(int index) {
    SeqPlayEntry* entry = &((SeqPlayEntry*)lbl_3_data_88E0)[index];
    void** arrTable = (void**)lbl_3_bss_1774[0];

    sound_crowd_EffectsStruct._04 = sndSeqPlayEx(entry->sgid, entry->sid, arrTable[index], NULL, 0);
    sndSeqVolume(lbl_3_data_830C[index * 2], 0, sound_crowd_EffectsStruct._04, SND_SEQVOL_CONTINUE);
}

// .text:0x000906FC size:0x58 mapped:0x806CF790
void fn_3_906FC(void) {
    s32* p;
    s32 base;
    s32 i;

    base = sound_crowd_EffectsStruct._00;
    p = (s32*)base;

    for (i = 0; i < (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE ? 1 : 0x14); i++) {
        *p += base;
        p++;
    }

    lbl_3_bss_1774[0] = base;
}

