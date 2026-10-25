#ifndef __UNKNOWN_FILE_0X80025DDC_H_
#define __UNKNOWN_FILE_0X80025DDC_H_

#include "mssbTypes.h"

typedef struct RelocEntry {
    /*0x00*/ u8 _00[0xC];
    /*0x0C*/ u32 value0C;
} RelocEntry; // size 0x10

typedef struct RelocSub {
    /*0x00*/ u8 _00[8];
    /*0x08*/ void* ptr08;
    /*0x0C*/ u32 links[1];
} RelocSub;

typedef struct RelocSeq {
    /*0x00*/ u16 linkCount;
    /*0x02*/ u16 subCount;
    /*0x04*/ u32 subStride;
    /*0x08*/ RelocSub* subs;
} RelocSeq; // size 0x0C

typedef struct RelocFile {
    /*0x00*/ u8 _00[2];
    /*0x02*/ u16 seqCount;
    /*0x04*/ u16 entryCount;
    /*0x06*/ u8 _06[2];
    /*0x08*/ RelocSeq* seqs;
    /*0x0C*/ RelocEntry* entries;
    /*0x10*/ u32 _10;
} RelocFile;

typedef struct ActRelatedHeader {
    /*0x00*/ u32 count0;
    /*0x04*/ u32 ptr04;
    /*0x08*/ u32 ptr08;
    /*0x0C*/ u32 count2;
} ActRelatedHeader;

typedef struct ActRelatedDesc {
    /*0x00*/ u16 h00;
    /*0x02*/ u16 h02;
    /*0x04*/ u32 ptr04;
} ActRelatedDesc;

typedef union ActRelatedWord18 {
    u32 w;
    struct {
        u16 hi;
        u16 lo;
    } h;
} ActRelatedWord18;

typedef struct ActRelatedCtl {
    /*0x00*/ f32 f00;
    /*0x04*/ f32 f04;
    /*0x08*/ s16 s08;
    /*0x0A*/ s16 s0A;
    /*0x0C*/ s16 s0C;
    /*0x0E*/ s16 s0E;
    /*0x10*/ u8 b10;
    /*0x11*/ u8 flagHi : 1;
    /*0x11*/ u8 flagMid : 2;
    /*0x11*/ u8 flagLow : 2;
    /*0x11*/ u8 flagTail : 3;
    /*0x12*/ u8 _12[2];
    /*0x14*/ u32 w14;
    /*0x18*/ ActRelatedWord18 w18;
    /*0x1C*/ u32 w1C;
} ActRelatedCtl; // size 0x20

typedef struct ActRelatedEffect {
    /*0x00*/ ActRelatedHeader* header;
    /*0x04*/ u32* arr1;
    /*0x08*/ u32* arr2;
    /*0x0C*/ ActRelatedCtl ctl;
    /*0x2C*/ void* file;
    /*0x30*/ u8* seqTables[10];
    /*0x58*/ s8 cur;
    /*0x59*/ u8 flag59;
} ActRelatedEffect;

void adjustInternalPointers(void* file);
void actorRelated(void* effect, int arg1, int arg2);
void actRelated(void* file, void* effect);
void fn_80026130(void);

#endif // !__UNKNOWN_FILE_0X80025DDC_H_
