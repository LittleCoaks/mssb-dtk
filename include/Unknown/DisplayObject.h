#ifndef __UNKNOWN_DISPLAYOBJECT_H_
#define __UNKNOWN_DISPLAYOBJECT_H_

#include "mssbTypes.h"
#include "Dolphin/GX/GXPixel.h"
#include "Dolphin/GX/GXEnum.h"
#include "Dolphin/mtx.h"
#include "C3/geoPalette.h"
#include "Unknown/File_0x800bd190.h"

typedef struct FogSettings {
    /* 0x00 */ GXFogType type;
    /* 0x04 */ f32 startZ;
    /* 0x08 */ f32 endZ;
    /* 0x0C */ f32 nearZ;
    /* 0x10 */ f32 farZ;
    /* 0x14 */ GXColor color;
} FogSettings; // size: 0x18

extern FogSettings fogSettings;

extern struct Light* lbl_803CC1F0;
typedef void (*DOTevStageCallback)(GXTevStageID stage, int arg1, int arg2, GXTexCoordID coord, GXTexMapID map);

extern u32 lbl_803CBB58;
extern DOTevStageCallback lbl_803CC1F4;
extern f32 lbl_803CC1F8;
extern f32 lbl_803CC1FC;
typedef void (*DOTevSetupCallback)(struct DODisplayObj* dispObj, GXTevStageID* stage, GXTexCoordID* coord,
                                   GXTexMapID* map, u8* numTevStages, u8* numTexGens, MtxPtr camera);

extern DOTevSetupCallback lbl_803CC200;
extern Mtx* SkinForwardArray;
extern Mtx* SkinInverseArray;
extern GXTlutObj lbl_803CB49C[8];
extern GXTexObj lbl_803CB5FC[8];
extern UnkShadowCallback lbl_803CC20C;
extern u8 lbl_803CC210[8];
extern f32 lbl_803CC218;
extern void* lbl_803CC21C;

void fn_800B993C(void);
void fn_800B9948(DOTevSetupCallback callback);
void fn_800B9950(s32 mask, f32 arg1, f32 arg2);
void fn_800B996C(DOTevStageCallback callback);
void SetFogNone(void);
void SetFog(GXFogType type, f32 startZ, f32 endZ, f32 nearZ, f32 farZ, GXColor color);
void SetFogNoneAgain(void);
void fn_800B9A9C(void* arg0, f32 arg1);
void setLITLightPtr(void* light);
void GetColorFromQuant(void* src, u32 format, u8* r, u8* g, u8* b, u8* a);
void updateMemoryLocation(struct DODisplayObj* dispObj, void* data);
void InitDisplayObjWithLayout(struct DODisplayObj* dispObj, DODisplayLayout* layout);

#endif // !__UNKNOWN_DISPLAYOBJECT_H_
