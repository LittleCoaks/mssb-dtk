#ifndef __UNKNOWN_SUB_H_
#define __UNKNOWN_SUB_H_

#include "mssbTypes.h"
#include "Dolphin/gx.h"
#include "static/UnknownHomes_Static.h"

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
    /* 0x1C */ u16 unk1C;
    /* 0x1E */ u16 unk1E;
} TextureBody; // size 0x20

typedef struct {
    /*0x000*/ u8 _000[0x252];
    /*0x252*/ s8 _252;
    u8 _253;
    /*0x254*/ s8 _254;
    artificial_padding(0x254, 0x25A, s8);
    /*0x25A*/ u8 _25A;
    artificial_padding(0x25A, 0x274, u8);
    /*0x274*/ u8 _274;
} fn_80024C6C_s;

extern TextureBody nullTex;

void gOz_GXSetTexture(GXTevMode mode, int texCoordFrac, BOOL useNormals);
void fn_80024390(Mtx44 mtx, f32* projection, GXProjectionType type);
void SetDisplayStateTexture(TextureBody* texture, int texMap, int tlutName);
void fn_800245EC(camera_803c639c_s* camera, Mtx view, Vec* src, f32* dst, int count, int flipY);
void fn_800246D4(int (*compare)(const void*, const void*), void* src, void* dst, int size, int count);
int fn_800247E4(int x, int y, int width, int bytesPerPixel);
BOOL challengeStarRelatedInd(int charID, int mission);
u32 multBottomBits_asFloat(u32 value, u32 scale);
u32 byteWiseMultiply(u32 scale, u32 color);
int LERPToNewRange_Float(int value, int inMin, int inMax, int outMin, int outMax);
f32 LinearInterpolateToNewRange(f32 value, f32 prevMin, f32 prevMax, f32 nextMin, f32 nextMax);
BOOL isCharacterUnlocked(int charID);
int fn_80024C6C(fn_80024C6C_s* obj, int arg1);

#endif // !__UNKNOWN_SUB_H_
