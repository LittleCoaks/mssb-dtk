#ifndef __UNKNOWN_FILE_0X8003A688_H_
#define __UNKNOWN_FILE_0X8003A688_H_

#include "mssbTypes.h"
#include "Dolphin/gx.h"
#include "C3/geoPalette.h"
#include "Unknown/File_0x80034e20.h"

#define TEX_SLOT_COUNT 13

/* The part of a TextureRecord after its 4-byte index header; texture palettes
 * hand out pointers to this (TextureRecord.pixels onwards). */
typedef struct TextureBody {
    /* 0x00 */ void* pixels;
    /* 0x04 */ void* tlut;
    /* 0x08 */ u16 height;
    /* 0x0A */ u16 width;
    /* 0x0C */ u8 wrapS;
    /* 0x0D */ u8 wrapT;
    /* 0x0E */ u8 minFilter;
    /* 0x0F */ u8 magFilter;
    /* 0x10 */ f32 lodBias;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 minLOD;
    /* 0x16 */ u8 maxLOD;
    /* 0x17 */ u8 gxFormat;
    /* 0x18 */ u16 tlutEntries;
    /* 0x1A */ u8 tlutFormat;
    /* 0x1B */ u8 unk1B;
} TextureBody;

/* Per-slot texture objects; slots are indexed like hugeAnimStruct.actors. */
typedef struct TexSlotTable {
    /* 0x000 */ u8 unk000[0xA00];
    /* 0xA00 */ u16 unkA00;
    /* 0xA02 */ u16 unkA02;
    /* 0xA04 */ u8 unkA04[0x80];
    /* 0xA84 */ GXTexObj texObj[TEX_SLOT_COUNT];
    /* 0xC24 */ GXTlutObj tlutObj[TEX_SLOT_COUNT];
    /* 0xCC0 */ u8 texKind[TEX_SLOT_COUNT]; // 0 = none, 1 = direct, 2 = color-indexed
    /* 0xCD0 */ f32 texScale[TEX_SLOT_COUNT][2];
    /* 0xD38 */ u8 unkD38;
} TexSlotTable; // size 0xD40

extern TexSlotTable lbl_802D3D80;

void fn_8003A688(int slot, f32 scaleS, f32 scaleT);
void fn_8003A6B0(int slot, TextureBody* texture, f32 scaleS, f32 scaleT);
void fn_8003A848(u8 r, u8 g, u8 b);
void fn_8003A85C(u8 value);
void fn_8003A8A0(struct DODisplayObj* dispObj, MtxPtr camera, int flag);
void fn_8003AC90(void);
void GXTexObjRelated(TextureRecord* texture);

#endif // !__UNKNOWN_FILE_0X8003A688_H_
