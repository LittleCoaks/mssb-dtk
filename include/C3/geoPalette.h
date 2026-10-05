#ifndef _DOLPHIN_CP_GEOPALETTE_H_
#define _DOLPHIN_CP_GEOPALETTE_H_

#include "types.h"
#include "stdarg.h"
#include "C3/unktypes.h"

enum DOTextureState {
    DOTS_WRAP_S = 0,
    DOTS_WRAP_T = 1,
    DOTS_MIPMAP = 2,
    DOTS_MIN_FILTER = 3,
    DOTS_MAG_FILTER = 4,
    DOTS_MIN_LOD = 5,
    DOTS_MAX_LOD = 6,
    DOTS_LOD_BIAS = 7,
    DOTS_BIAS_CLAMP = 8,
    DOTS_EDGE_LOD = 9,
    DOTS_MAX_ANISO = 10,
};

enum DOTextureSetting {
    DOTS_USEDEFAULT = -1,
    DOTS_CLAMP = 0,
    DOTS_REPEAT = 1,
    DOTS_MIRROR = 2,
    DOTS_MIPMAP_ON = 1,
    DOTS_MIPMAP_OFF = 0,
    DOTS_NEAR = 0,
    DOTS_LINEAR = 1,
    DOTS_NEAR_MIP_NEAR = 2,
    DOTS_LIN_MIP_NEAR = 3,
    DOTS_NEAR_MIP_LIN = 4,
    DOTS_LIN_MIP_LIN = 5,
    DOTS_LOD_SET = 0,
    DOTS_BIAS_CLAMP_ON = 1,
    DOTS_BIAS_CLAMP_OFF = 0,
    DOTS_EDGE_LOD_ON = 1,
    DOTS_EDGE_LOD_OFF = 0,
    DOTS_ANISO_1 = 0,
    DOTS_ANISO_2 = 1,
    DOTS_ANISO_4 = 2,
};

typedef void * (*unkCB)(void *, struct DODisplayObj *, u32, void *, int, char *);

typedef void (*DOUserTevModeFunc)(int mode, struct DODisplayObj *dispObj, MtxPtr camera, u8 *numTexGens, u8 *numTevStages);

typedef struct {
    /* 0x00 */ PositionData *positionData;
    /* 0x04 */ ColorData *colorData;
    /* 0x08 */ TextureData *textureData;
    /* 0x0C */ LightingData *lightingData;
    /* 0x10 */ DisplayData *displayData;
    /* 0x14 */ u8 numTextureChannels;
    /* 0x15 */ u8 pad8;
    /* 0x16 */ u16 pad16;
    /* 0x18 */ u8 unk18[4];
    /* 0x1C */ u8 unk1C[4];
    /* 0x20 */ u8 unk20[4];
    /* 0x24 */ u8 unk24[4];
    /* 0x28 */ u8 unk28[4];
    /* 0x2C */ u8 unk2C[4];
    /* 0x30 */ u8 unk30[4];
} DODisplayLayout; // size: 0x34 (MSSB extends the SDK layout)

struct DODisplayObj {
    /* 0x00 */ PositionData *positionData;
    /* 0x04 */ ColorData *colorData;
    /* 0x08 */ TextureData *textureData;
    /* 0x0C */ LightingData *lightingData;
    /* 0x10 */ DisplayData *displayData;
    /* 0x14 */ u8 numTextureChannels;
    /* 0x15 */ u8 pad8;
    /* 0x16 */ u8 visibility;
    /* 0x17 */ u8 overrideTevMode;
    /* 0x18 */ Mtx worldMatrix;
    /* 0x48 */ DOUserTevModeFunc userTevModeFunc;
    /* 0x4C */ GXTexObj *shaderFunc;
    /* 0x50 */ GXTexObj *shaderData;
    /* 0x54 */ u8 unk54[4]; // MSSB's display object is 0x6C bytes (see DOGet)
    /* 0x58 */ u8 unk58[4];
    /* 0x5C */ u8 unk5C[4];
    /* 0x60 */ u8 unk60[4];
    /* 0x64 */ u8 unk64[4];
    /* 0x68 */ u8 unk68[4];
};

typedef struct {
    /* 0x00 */ DODisplayLayout *layout;
    /* 0x04 */ char *name;
} DODescriptor, *DODescriptorPtr;

typedef struct DODisplayData {
    /* 0x00 */ u32 versionNumber;
    /* 0x04 */ u32 userDataSize;
    /* 0x08 */ void *userData;
    /* 0x0C */ u32 numDescriptors;
    /* 0x10 */ DODescriptorPtr descriptorArray;
} DODisplayData, *DODisplayDataPtr;

// displayObject.c
extern u32 HackTevState;
extern int CPEnableMultiTexture;

void DORelease(struct DODisplayObj * * dispObj);
Mtx *DOGetWorldMatrix(struct DODisplayObj * dispObj);
void DOHide(struct DODisplayObj * dispObj);
void DORender(struct DODisplayObj * dispObj, MtxPtr camera, u8 numLights, ...);
void DOVARender(struct DODisplayObj * dispObj, MtxPtr camera, u8 numLights, va_list *list);
void DORenderSkin(struct DODisplayObj *dispObj, MtxPtr camera, MtxPtr mtxArray, MtxPtr invTransposeMtxArray, u8 numLights, ...);
void DOVARenderSkin(struct DODisplayObj *dispObj, MtxPtr camera, MtxPtr mtxArray, MtxPtr invTransposeMtxArray, u8 numLights, va_list *list);
void DOSetWorldMatrix(struct DODisplayObj * dispObj, MtxPtr m);
void DOShow(struct DODisplayObj * dispObj);
f32 DOSetAmbientPercentage(struct DODisplayObj * dispObj, f32 percent);
void DOSetEffectsShader(struct DODisplayObj *dispObj, char *shaderFunc, char *data);
void DOOverrideTextureState(enum DOTextureState state, enum DOTextureSetting setting, f32 LODValue);

// geoPalette.c
struct sHdr *GEOGetPalette(DODisplayDataPtr *pal, char *name);
void GEOReleasePalette(DODisplayDataPtr *pal);
u32 GEOGetUserDataSize(DODisplayDataPtr pal);
char *GEOGetUserData(DODisplayDataPtr pal);
void DOGet(struct DODisplayObj **dispObj, DODisplayDataPtr pal, u16 id, char *name);

// normalTable.c
extern u8 normalTableQuantizeInfo;
extern u8 normalTableNumComponents;
extern u16 normalTableNumNormals;

extern f32 normalTable[252][3];

#endif // _DOLPHIN_CP_GEOPALETTE_H_
