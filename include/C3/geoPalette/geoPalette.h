#ifndef _C3_GEOPALETTE_GEOPALETTE_H_
#define _C3_GEOPALETTE_GEOPALETTE_H_

#include "mssbTypes.h"
#include "C3/geoPalette.h"

void* LoadGeoPalette(void* geoFile);

void convertGeometryAndSknHeader(void* geo, void* skn);

void AdjustGEOPalettePointers(DODisplayDataPtr pal);

void AdjustGPLDataPointers(DODisplayLayout* layout, struct DODisplayObj* dispObj);

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

#endif // _C3_GEOPALETTE_GEOPALETTE_H_
