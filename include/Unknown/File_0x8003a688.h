#ifndef __UNKNOWN_FILE_0X8003A688_H_
#define __UNKNOWN_FILE_0X8003A688_H_

#include "mssbTypes.h"
#include "Dolphin/gx.h"
#include "C3/geoPalette.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x80024184.h"

#define TEX_SLOT_COUNT 13

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
