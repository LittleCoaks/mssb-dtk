#ifndef __UNKNOWN_MOVIE_H_
#define __UNKNOWN_MOVIE_H_

#include "mssbTypes.h"
#include "Dolphin/OS/OSMessage.h"
#include "Dolphin/OS/OSThread.h"
#include "Dolphin/OS/OSUtil.h"
#include "Dolphin/ai.h"
#include "Dolphin/ar.h"
#include "Dolphin/OS/OSCache.h"
#include "Dolphin/gx.h"
#include "Dolphin/mtx.h"
#include "stl/mem.h"

// Ring buffer control block at lbl_803C79D4 (0x2C bytes).
typedef struct MovieRing {
    u32 unk00;
    u32 unk04;      // wrap limit
    u32 unk08;      // read/write cursor
    u32 unk0C;
    u32 unk10;      // wrap distance
    u32 unk14;
    u32 unk18;
    u32 unk1C;
    u32 unk20;
    u32 unk24;      // last advance
    u8 unk28;
    u8 unk29;
} MovieRing;

// Second control block at lbl_803C7A00.
typedef struct MovieRingB {
    u32 unk00;
    u32 unk04;
    u32 unk08;
    u32 unk0C;      // wrap limit
    u32 unk10;      // cursor
    u32 unk14;      // write position
    u32 unk18;      // wrap distance
    u32 unk1C;
    u32 unk20;
} MovieRingB;

// Source block passed to fn_800ADB04; only the word at +0xC is used here.
typedef struct MovieSource {
    u8 unk00[0xC];
    u32 unk0C;
} MovieSource;

// Movie decoder object; fn_* methods take a pointer to it. Offsets verified against asm.
typedef struct MovieSlot {
    u8* unk00;
    u32 unk04;
    u8 state;
    u8 unk09[0x3];
} MovieSlot;

typedef struct MovieDecoder {
    u8 pad000[0x18];
    u32 unk18;
    u32 unk1C;
    u8 pad020[0x4];
    u32 unk24;
    u32 unk28;
    u8 pad02C[0x4];
    u32 unk30;
    u8 pad034[0x8];
    u8 unk3C;
    u8 pad03D[0x3];
    u32 unk40;
    u8 pad044[0x24];
    u32 unk68;
    u32 unk6C;
    u8 pad070[0x10];
    u16 unk80;
    u16 unk82;
    u32 unk84;
    u8 pad088[0x18];
    u8 unkA0[0x4];
    u16 unkA4;
    u16 unkA6;
    u8 unkA8;
    u8 unkA9;
    u8 pad0AA[0x26];
    u8* unkD0;
    u8* unkD4;
    u8 pad0D8[0x10];
    u8* unkE8;
    u8* unkEC;
    MovieSource* unkF0;
    u8* unkF4;
    u8 pad0F8[0x4];
    u8 unkFC;
    u8 pad0FD[0x3];
    u8* unk100;
    u8 pad104[0x4];
    u8 unk108;
    u8 pad109[0x3];
    u8* unk10C;
    u8 pad110[0x4];
    u8 unk114;
    u8 pad115[0x3];
    u8* unk118;
    u8 pad11C[0x4];
    u8 unk120;
    u8 pad121[0x3];
    u8* unk124;
    u8 pad128[0x4];
    u8 unk12C;
    u8 pad12D[0x3];
    u8* unk130;
    u8 pad134[0x4];
    u8 unk138;
    u8 pad139[0x3];
    u8* unk13C;
    u8* unk140;
    u8* unk144;
    u8* unk148;
    u8* unk14C;
    u8* unk150;
    u8* unk154;
    u8* unk158;
    u8* unk15C;
    u8* unk160;
    u8* unk164;
    u8* unk168;
    u8* unk16C;
    u8* unk170;
    u32 unk174;
    u32 unk178;
    u32 unk17C;
    u32 unk180;
    u32 unk184;
    u32 unk188;
    u32 unk18C;
    u32 unk190;
    u8 pad194[0x4];
    OSTime unk198;
    OSTime unk1A0;
    u32 unk1A8;
    u32 unk1AC;
    u16 unk1B0;
    u16 unk1B2;
    s16 unk1B4;
    s16 unk1B6;
    u8 unk1B8;
    u8 unk1B9;
    u8 unk1BA;
    u8 unk1BB;
    u8 unk1BC;
    u8 pad1BD[0x0];
} MovieDecoder;

extern MovieRing lbl_803C79D4;
extern MovieRingB lbl_803C7A00;

// Small-data and bss globals used by this unit (scalars so MWCC uses sda21).
extern u8 lbl_803CC17C;
extern u8 lbl_803CC17D;
extern u8 lbl_803CC17E;
extern u8 lbl_803CC17F;
extern u8 lbl_803CC181;
extern u8 lbl_803CC1A8;
extern u8 lbl_803CC194;
extern u8 lbl_801112E0[0x10];
extern u8 lbl_801102C0[0x1000];
extern u32 lbl_803CC198;
extern u32 yuv2rgbConverters;
extern u32 lbl_803CC188;
extern u8 lbl_803CBAE0;
extern u8 lbl_802F93E0[0x1E00];
extern u8 lbl_801101C0[0x100];
extern u32 lbl_803CC1A0;
extern u8 lbl_803CC182;
extern u32 lbl_803CBAE8;
extern u32 lbl_803CBAF0;
extern u32 lbl_803CBAF8;
extern u8 lbl_803C7420[0x398];
extern char lbl_803CCF00;
extern char lbl_800E7B98;
extern char lbl_800E7B50[];
extern char lbl_800E7B74[];
extern u8 lbl_803C78A4[0x20];
extern u8 lbl_803CBB00[];
extern u8 lbl_803CBAD8[];
extern u32 lbl_803CCEE8;
extern f32 lbl_803CC184;
extern u8 lbl_801112C0[];
extern f32 lbl_802FB1E0[16];
extern u32 lbl_803CC1A4;
extern u32 lbl_803CC1AC;
extern u32 lbl_803CC19C;
extern MovieDecoder* lbl_803CC170;
extern u16 lbl_803CBAE2;
extern u16 lbl_803CBAE4;
extern u8 lbl_803CC180;
extern u32 lbl_803CC190;
extern void* lbl_803CC174;
extern void* lbl_803CC178;
extern AIDCallback lbl_803CC18C;
extern u8 lbl_802F93A0[];
extern u8 lbl_803C78C4[0xD0];
extern u8 lbl_803C7994[0x40];
extern u8 data_803C6780[];
extern f32 lbl_803CCEEC;
extern f32 lbl_803CCEF0;
extern f32 lbl_803CCEF4;
extern f32 lbl_803CCEF8;
extern f32 lbl_803CCEFC;
extern OSMessageQueue lbl_802FB870;
extern OSThread lbl_802FB220;
extern u8 lbl_803C6CF8[0x800];

void fn_800A63C8(void);
void fn_800A6D10(u32 n);
void fn_800A6E24(void* src, void* a, void* b);
void fn_800E4AE8(void* a, void* b);
u32 fn_800E4B1C(void* p);
void fn_800B03F4(u32 start, u32 len);
void fn_800B0230(u32 start, u32 len);
void fn_800AE5B8(void);
void fn_800E4FF4(void* a, void* b, u32 c);
void fn_800E591C(void* a, void* b, u32 c, u32 d);
void fn_800E5940(void* a, void* b, u32 c, u32 d, u32 e);
s32 fn_800AF5FC(MovieDecoder* self, u32 kind, u32 size);
void* fn_800AE8B8(void* arg);
void fn_800E4AC8(void);
u32 fn_800E4B1C(void* p);
void fn_800A7D4C(u32 a, void* b);
void fn_800DFDD4(void* a, void* b, u8 c, u32 d, u32 e, void* f);
void fn_800ACFB0(void* block);
void* fn_800A6418(u32 size);
void* _OSAllocFromHeap(s32 alignment, s32 size);
void ARQSetChunkSize(u32 size);
void ARQFlushQueue(void);
void fn_800B0390(void);
void fn_800B0580(void);

u32 fn_800AD490(MovieDecoder* self);
BOOL fn_800AD780(MovieDecoder* self);
u32 fn_800AD6BC(MovieDecoder* self);
void fn_800AD830(MovieDecoder* self);
void fn_800AD914(MovieDecoder* self);
void fn_800AD95C(MovieDecoder* self, u8 flag);
void fn_800AD9F4(MovieDecoder* self);
BOOL fn_800ADB04(MovieSource* src, MovieDecoder* dec, u8 a, u8 b);
BOOL fn_800B0134(u32 n);
BOOL fn_800AF9B4(u8* dst, u32 len);
void* fn_800AE8B8(void* arg);
BOOL fn_800AFD4C(void);
void fn_800AFBF0(void);
void fn_800A6C80(void);
u8 fn_800AFFB0(void);
void fn_800AFFC0(u32 n);
BOOL fn_800B0008(u32 n);
void fn_800ADC40(void* a, void* b);
void fn_800AD500(MovieDecoder* self, u8* base);
void fn_800ADD70(void);
void fn_800B05E4(s32 sel, u32 size);
void fn_800AFC10(void);


BOOL MovStreamThread(MovieDecoder* self);

void* MovDecodeThread(void* arg);
s32 fn_800AF1A8(MovieDecoder* self);
void fn_800AD070(void);
void fn_800AFFC0(u32 n);
void fn_800B0580(void);
void fn_800AD9F4(MovieDecoder* self);
void YUV2RGB_(u8* y, u8* dst, u32 w, u32 h);
void YUV2RGB(u8* y, u8* dst, u32 w, u32 h);

#endif // !__UNKNOWN_MOVIE_H_
