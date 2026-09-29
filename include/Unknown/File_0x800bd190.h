#ifndef __UNKNOWN_FILE_0X800BD190_H_
#define __UNKNOWN_FILE_0X800BD190_H_

#include "mssbTypes.h"

typedef struct {
    /* 0x00 */ u8 unk00[0xC];
    /* 0x0C */ void* tex;
} UnkTexPalSub; // size 0x10

typedef struct {
    /* 0x00 */ u8 unk00[0x8];
    /* 0x08 */ UnkTexPalSub* subs;
    /* 0x0C */ u8 unk0C[0x8];
    /* 0x14 */ u8 numSubs;
} UnkTexPalObj;

typedef struct {
    /* 0x00 */ UnkTexPalObj* obj;
    /* 0x04 */ u8 unk04[0x4];
} UnkTexPalEntry; // size 0x8

typedef struct {
    /* 0x00 */ u8 unk00[0xC];
    /* 0x0C */ u32 numEntries;
    /* 0x10 */ UnkTexPalEntry* entries;
} UnkTexPalGeo;

typedef void (*UnkShadowCallback)(void*, void*, void*, void*, void*, void*);

void UpdateTexturePalettePointers(UnkTexPalGeo* geo, void* tex);
void fn_800BD1E8(UnkShadowCallback cb);
void __MTGQR5(register u32 val);
void __MTGQR6(register u32 val);
void __MTGQR7(register u32 val);

#endif // !__UNKNOWN_FILE_0X800BD190_H_
