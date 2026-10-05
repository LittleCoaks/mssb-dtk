#include "Unknown/DisplayObject.h"
#include "Unknown/File_0x800acf14.h"
#include "Dolphin/os.h"
#include "Dolphin/stl.h"
#include "C3/charPipeline.h"
#include "stl/math.h"
#include "Unknown/sub.h"
#include "Unknown/File_0x800bd2b0.h"
#include "stl/stdarg.h"
#include "Unknown/File_0x800beb3c.h"
#include "Unknown/File_0x800bf008.h"
#include "Unknown/File_0x800bf038.h"
#include "Unknown/File_0x800bd190.h"

static const GXColor lbl_803CCFF8 = {0, 0, 0, 0x80};

FogSettings fogSettings = {GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, {0, 0, 0, 0}};

void fn_800B993C(void) {
    lbl_803CC200 = NULL;
}

void fn_800B9948(DOTevSetupCallback callback) {
    lbl_803CC200 = callback;
}

void fn_800B9950(s32 mask, f32 arg1, f32 arg2) {
    if (mask & 1) {
        lbl_803CC1F8 = arg1;
    }
    if (mask & 2) {
        lbl_803CC1FC = arg2;
    }
}

void fn_800B996C(DOTevStageCallback callback) {
    lbl_803CC1F4 = callback;
}

void SetFogNone(void) {
    GXColor color;

    color.r = color.g = color.b = 0;
    GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, color);
}

void SetFog(GXFogType type, f32 startZ, f32 endZ, f32 nearZ, f32 farZ, GXColor color) {
    fogSettings.type = type;
    fogSettings.startZ = startZ;
    fogSettings.endZ = endZ;
    fogSettings.nearZ = nearZ;
    fogSettings.farZ = farZ;
    fogSettings.color = color;
    GXSetFog(type, (f64)startZ, (f64)endZ, (f64)nearZ, (f64)farZ, color);
}

void SetFogNoneAgain(void) {
    fogSettings.color.r = fogSettings.color.g = fogSettings.color.b = 0;
    fogSettings.type = GX_FOG_NONE;
    fogSettings.startZ = 0.0f;
    fogSettings.endZ = 0.0f;
    fogSettings.nearZ = 0.0f;
    fogSettings.farZ = 0.0f;
    GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, fogSettings.color);
}

void fn_800B9A9C(void* arg0, f32 arg1) {
    lbl_803CC21C = arg0;
    lbl_803CC218 = arg1;
}

void setLITLightPtr(void* light) {
    lbl_803CC1F0 = light;
}

int fn_800B9AB0(u32 mode, struct DODisplayObj* dispObj, DisplayStateList* state, GXTevStageID* stage, GXTexCoordID* coord,
                GXTexMapID* map, GXChannelID* chan, MtxPtr camera) {
    GXTexGenSrc src = GX_TG_NRM;
    Mtx mvMtx;
    Mtx scaleMtx;
    Mtx transMtx;
    Mtx nrmMtx;
    Mtx envMtx;
    Mtx shiftMtx;
    f32 half = 0.5f;
    GXColor kColor;
    GXTevColorArg colorD;
    GXTevAlphaArg alphaD;
    GXTevColorArg colorC;

    if (lbl_803CBB58 == 0) {
        return -1;
    }
    if (dispObj == NULL || dispObj->lightingData == NULL || state == NULL) {
        return -1;
    }

    PSMTXIdentity(nrmMtx);
    PSMTXIdentity(envMtx);
    PSMTXConcat(camera, dispObj->worldMatrix, mvMtx);
    PSMTXInverse(mvMtx, scaleMtx);
    PSMTXTranspose(scaleMtx, nrmMtx);
    PSMTXScale(scaleMtx, -half, half, 0.0f);
    PSMTXTrans(transMtx, half, half, 1.0f);
    PSMTXConcat(transMtx, scaleMtx, shiftMtx);
    PSMTXScale(scaleMtx, -half, half, 0.0f);
    PSMTXTrans(transMtx, half + lbl_803CC1F8, half + lbl_803CC1FC, 1.0f);
    PSMTXConcat(transMtx, scaleMtx, envMtx);

    if (mode == 5) {
        colorD = GX_CC_RASC;
        *chan = GX_COLOR0A0;
        alphaD = GX_CA_RASA;
    } else {
        colorD = GX_CC_CPREV;
        *chan = GX_COLOR_NULL;
        alphaD = GX_CA_APREV;
    }

    if (state->pad8 != 0) {
        colorC = GX_CC_KONST;
        kColor.r = kColor.g = kColor.b = kColor.a = state->pad8;
        GXSetTevKColor(GX_KCOLOR0, kColor);
        GXSetTevKColorSel(*stage, GX_TEV_KCSEL_K0);
    } else {
        colorC = GX_CC_APREV;
    }

    if (dispObj->lightingData->compCount == 2) {
        src = GX_TG_BINRM;
    }

    GXLoadTexMtxImm(nrmMtx, GX_TEXMTX0 + *map * 3, GX_MTX3x4);
    GXLoadTexMtxImm(envMtx, GX_PTTEXMTX0 + *map * 3, GX_MTX3x4);
    GXSetTexCoordGen2(*coord, GX_TG_MTX3X4, src, GX_TEXMTX0 + *map * 3, GX_TRUE, GX_PTTEXMTX0 + *map * 3);
    GXSetTevOrder(*stage, *coord, *map, *chan);

    if (lbl_803CC210[*map] == 1) {
        GXSetTevColorIn(*stage, GX_CC_ZERO, GX_CC_TEXC, colorC, colorD);
        GXSetTevColorOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    } else if (lbl_803CC210[*map] == 0) {
        GXSetTevColorIn(*stage, colorD, GX_CC_TEXC, colorC, GX_CC_ZERO);
        GXSetTevColorOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    } else {
        GXSetTevColorIn(*stage, GX_CC_ZERO, GX_CC_TEXC, colorC, colorD);
        GXSetTevColorOp(*stage, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    }
    GXSetTevAlphaIn(*stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, alphaD);
    GXSetTevAlphaOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

    if (lbl_803CC1F4 != NULL) {
        (*coord)++;
        GXLoadTexMtxImm(nrmMtx, GX_TEXMTX0 + (*map + 1) * 3, GX_MTX3x4);
        GXLoadTexMtxImm(shiftMtx, GX_PTTEXMTX0 + (*map + 1) * 3, GX_MTX3x4);
        GXSetTexCoordGen2(*coord, GX_TG_MTX3X4, src, GX_TEXMTX0 + (*map + 1) * 3, GX_TRUE,
                          GX_PTTEXMTX0 + (*map + 1) * 3);
        (*map)++;
        lbl_803CC1F4(*stage, 0, 1, *coord, *map);
    }

    (*stage)++;
    (*coord)++;
    (*map)++;
    return 0;
}

int fn_800B9EA8(u32 mode, struct DODisplayObj* dispObj, DisplayStateList* state, GXTevStageID* stage,
                GXTexCoordID* coord, GXTexMapID* map, GXChannelID* chan, MtxPtr camera) {
    Mtx mvMtx;
    Mtx rotMtx;
    Mtx transMtx;
    Mtx lightMtx;
    Mtx projMtx;
    Vec dir;
    Vec axis;
    Vec up = {0.0f, 0.0f, 1.0f};
    GXColor kColor;
    f32 dot;
    f32 size;
    GXTexGenSrc src = GX_TG_NRM;
    GXTevColorArg colorD;
    GXTevAlphaArg alphaD;
    GXTevColorArg colorC;
    GXTexMapID lutMap;

    if (lbl_803CBB58 == 0) {
        return -1;
    }
    if (dispObj == NULL || dispObj->lightingData == NULL || lbl_803CC1F0 == NULL || state == NULL) {
        return -1;
    }

    PSMTXIdentity(lightMtx);
    PSMTXIdentity(projMtx);
    PSMTXConcat(camera, dispObj->worldMatrix, mvMtx);
    PSMTXInverse(mvMtx, rotMtx);
    PSMTXTranspose(rotMtx, mvMtx);
    PSMTXMultVecSR(camera, &lbl_803CC1F0->direction, &dir);
    dot = PSVECDotProduct(&dir, &up);
    if (dot == -1.0f) {
        PSMTXScale(lightMtx, 0.0f, 0.0f, 0.0f);
        PSMTXScale(projMtx, 0.0f, 0.0f, 0.0f);
    } else {
        dir.x = -dir.x;
        dir.y = -dir.y;
        dir.z = -dir.z;
        if (PSVECMag(&dir) == 0.0f) {
            return -1;
        }
        PSVECNormalize(&dir, &dir);
        if (dot == 1.0f) {
            PSMTXIdentity(rotMtx);
        } else {
            PSVECCrossProduct(&dir, &up, &axis);
            if (PSVECMag(&axis) == 0.0f) {
                PSMTXIdentity(rotMtx);
            } else {
                PSMTXRotAxisRad(rotMtx, &axis, acos(PSVECDotProduct(&up, &dir)));
            }
        }
        PSMTXConcat(rotMtx, mvMtx, lightMtx);
        if (lbl_803CC21C != NULL) {
            size = lbl_803CC218;
        } else {
            size = (state->pad8 & 0x7F) / 100.0f;
        }
        size = 0.5f * (0.5f - size) + 0.75f;
        PSMTXScale(rotMtx, size, -size, 0.0f);
        PSMTXTrans(transMtx, 0.5f, 0.5f, 1.0f);
        PSMTXConcat(transMtx, rotMtx, projMtx);
    }

    if (mode == 5) {
        colorD = GX_CC_RASC;
        *chan = GX_COLOR0A0;
        alphaD = GX_CA_RASA;
    } else {
        colorD = GX_CC_CPREV;
        *chan = GX_COLOR_NULL;
        alphaD = GX_CA_APREV;
    }

    if (dispObj->pad8 != 0) {
        colorC = GX_CC_KONST;
        kColor.r = kColor.g = kColor.b = kColor.a = dispObj->pad8;
        GXSetTevKColor(GX_KCOLOR0, kColor);
        GXSetTevKColorSel(*stage, GX_TEV_KCSEL_K0);
    } else {
        colorC = GX_CC_APREV;
    }

    if (dispObj->lightingData->compCount == 2) {
        src = GX_TG_BINRM;
    }

    GXLoadTexMtxImm(lightMtx, GX_TEXMTX0 + *map * 3, GX_MTX3x4);
    GXLoadTexMtxImm(projMtx, GX_PTTEXMTX0 + *map * 3, GX_MTX3x4);

    if (state->pad16 == 0) {
        GXSetTexCoordGen2(*coord, GX_TG_MTX3X4, src, GX_TEXMTX0 + *map * 3, GX_TRUE, GX_PTTEXMTX0 + *map * 3);
        GXSetTevOrder(*stage, *coord, *map, *chan);
        GXSetTevColorIn(*stage, GX_CC_ZERO, GX_CC_TEXC, colorC, colorD);
        GXSetTevColorOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(*stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, alphaD);
        GXSetTevAlphaOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        (*stage)++;
        (*coord)++;
        (*map)++;
    } else {
        lutMap = *map + 1;
        GXSetTexCoordGen2(*coord, GX_TG_MTX2X4, GX_TG_TEX0 + lutMap, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetTevOrder(*stage, *coord, lutMap, GX_COLOR0A0);
        GXSetTevColorIn(*stage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
        GXSetTevColorOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
        GXSetTevAlphaIn(*stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
        GXSetTevAlphaOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
        (*stage)++;
        (*coord)++;
        GXSetTexCoordGen2(*coord, GX_TG_MTX3X4, src, GX_TEXMTX0 + *map * 3, GX_TRUE, GX_PTTEXMTX0 + *map * 3);
        GXSetTevOrder(*stage, *coord, *map, GX_COLOR_NULL);
        GXSetTevColorIn(*stage, colorD, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
        GXSetTevColorOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(*stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, alphaD);
        GXSetTevAlphaOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        (*stage)++;
        (*coord)++;
        *map += 2;
    }
    return 0;
}

void DODefaultUserTevMode(int mode, struct DODisplayObj* dispObj, MtxPtr camera, u8* numTexGens, u8* numTevStages) {
    GXTevStageID stage;
    GXTexCoordID coord;
    GXTexMapID map;
    GXTevColorArg colorD;
    GXTevAlphaArg alphaD;
    GXChannelID chan;
    f32 x;
    f32 y;
    f32 len;
    f32 angle;
    Mtx m;

    if (dispObj->overrideTevMode) {
        OSReport("Error: DODefaultUserTevMode: Cannot override tev mode AND use default user tev mode function.\n");
        return;
    }

    stage = *numTevStages;
    coord = *numTevStages;
    map = *numTevStages;
    if (stage == GX_TEVSTAGE0) {
        colorD = GX_CC_RASC;
        alphaD = GX_CA_RASA;
        chan = GX_COLOR0A0;
    } else {
        colorD = GX_CC_CPREV;
        alphaD = GX_CA_APREV;
        chan = GX_COLOR_NULL;
    }

    switch (mode) {
    case 9:
        GXSetTevOrder(stage, coord, map, chan);
        GXSetTevColorIn(stage, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, colorD);
        GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, alphaD);
        GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        break;
    case 10:
        GXSetTevOrder(stage, coord, map, chan);
        GXSetTevColorIn(stage, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, colorD);
        GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, alphaD);
        GXSetTevColorOp(stage, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        break;
    case 11:
        x = camera[2][0];
        y = camera[2][1];
        if (x == 0.0f && y == 0.0f) {
            GXSetTexCoordGen2(coord, GX_TG_MTX2X4, GX_TG_TEX0 + *numTevStages, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        } else {
            len = dolsqrtf2(x * x + y * y);
            angle = 0.159154f * (f32)asin(y / len);
            if (x < 0.0f) {
                angle = 0.5f - angle;
            }
            PSMTXIdentity(m);
            m[0][0] = 2.0f;
            m[0][3] = -angle;
            GXLoadTexMtxImm(m, GX_TEXMTX0 + *numTevStages * 3, GX_MTX3x4);
            GXSetTexCoordGen2(coord, GX_TG_MTX3X4, GX_TG_TEX0 + *numTevStages, GX_TEXMTX0 + *numTevStages * 3, GX_FALSE,
                              GX_PTIDENTITY);
        }
        GXSetTevOrder(stage, coord, map, chan);
        GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_APREV, colorD);
        GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
        GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        break;
    default:
        OSReport("Warning: DODefaultUserTevMode: Unknown user tev mode %d\n", mode);
        return;
    }

    (*numTexGens)++;
    (*numTevStages)++;
}

void Custom_SetState(struct DODisplayObj* dispObj, DisplayStateList* state, MtxPtr m) {
    GXTevStageID stage;
    GXTexCoordID coord;
    GXTexMapID map;
    GXChannelID chan;
    u8 numStages;
    u8 numTexGens;
    int i;
    int mode;
    u32 setting;
    u8 nChans;
    u8 shift;
    u8 flag;
    u8 texIndex;
    f32 scale;
    GXColor tevColor;
    GXColor kColor;
    GXTevColorArg colorC;
    GXTevColorArg colorD;
    GXTevAlphaArg alphaD;
    GXTexGenSrc src;
    Mtx mvMtx;
    Mtx nrmMtx;
    Mtx texMtx;
    Mtx transMtx;
    Mtx scaleMtx;
    Mtx shadowMtx;

    stage = GX_TEVSTAGE0;
    nChans = 0;
    coord = GX_TEXCOORD0;
    shift = 0;
    flag = 0;
    texIndex = 0;
    map = GX_TEXMAP0;
    setting = state->setting;
    numStages = 0;
    numTexGens = 0;
    GXSetNumIndStages(0);
    for (i = GX_TEVSTAGE0; i < GX_MAXTEVSTAGE; i++) {
        GXSetTevDirect(i);
    }

    do {
        mode = (setting >> shift) & 0xF;
        if (mode == 0) {
            break;
        }
        switch (mode) {
        case 10:
            chan = GX_COLOR0A0;
            nChans++;
            GXSetTevOrder(stage, coord, map, GX_COLOR0A0);
            GXSetTexCoordGen2(coord, GX_TG_MTX2X4, GX_TG_TEX0 + texIndex, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
            GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
            GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            texIndex++;
            numTexGens++;
            numStages++;
            break;
        case 12:
            chan = GX_COLOR_NULL;
            GXSetTevOrder(stage, coord, map, GX_COLOR_NULL);
            GXSetTexCoordGen2(coord, GX_TG_MTX2X4, GX_TG_TEX0 + texIndex, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_CPREV, GX_CC_ZERO);
            GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_TEXA, GX_CA_APREV, GX_CA_ZERO);
            GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            if (lbl_803CC210[map] == 2) {
                numStages++;
                GXSetTevOrder(stage + 1, coord, map, chan);
                GXSetTevColorIn(stage + 1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_APREV, GX_CC_ZERO);
                GXSetTevColorOp(stage + 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(stage + 1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                GXSetTevAlphaOp(stage + 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            }
            texIndex++;
            numTexGens++;
            numStages++;
            break;
        case 1:
        case 2:
        case 3:
        case 4:
            if (numStages != 0 || mode == 4) {
                chan = GX_COLOR_NULL;
            } else {
                chan = GX_COLOR0A0;
            }
            GXSetTevOrder(stage, coord, map, chan);
            GXSetTexCoordGen2(coord, GX_TG_MTX2X4, GX_TG_TEX0 + texIndex, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            GXSetTevOp(stage, mode - 1);
            if (lbl_803CC210[map] == 2) {
                numStages++;
                GXSetTevOrder(stage + 1, coord, map, GX_COLOR_NULL);
                GXSetTevColorIn(stage + 1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_APREV, GX_CC_ZERO);
                GXSetTevColorOp(stage + 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(stage + 1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                GXSetTevAlphaOp(stage + 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            }
            texIndex++;
            numTexGens++;
            numStages++;
            break;
        case 5:
            if (dispObj->shaderFunc == NULL) {
                GXSetTevOrder(stage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
                GXSetTevOp(stage, GX_PASSCLR);
                numStages++;
            }
            break;
        case 6:
            if (numStages != 0 || mode == 4) {
                chan = GX_COLOR_NULL;
            } else {
                chan = GX_COLOR0A0;
            }
            GXSetTexCoordGen2(coord, GX_TG_MTX2X4, GX_TG_TEX0 + texIndex, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            numTexGens++;
            GXSetTexCoordGen2(coord + 1, GX_TG_MTX2X4, GX_TG_TEX1 + texIndex, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            GXSetTevOrder(stage, coord + 1, map + 1, GX_COLOR0A0);
            GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
            GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
            GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
            GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
            numStages++;
            stage++;
            GXSetTevOrder(stage, coord, map, chan);
            GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
            GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
            GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
            flag = 1;
            texIndex++;
            numTexGens++;
            numStages++;
            break;
        case 7:
            if (!flag) {
                GXSetTexCoordGen2(coord, GX_TG_MTX2X4, GX_TG_TEX0 + texIndex, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                numTexGens++;
                GXSetTevOrder(stage, coord, map, GX_COLOR0A0);
                numStages++;
                GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
                GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
                GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
                GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
                stage++;
            }
            GXSetTevOrder(stage, coord, map, GX_COLOR_NULL);
            texIndex++;
            numStages++;
            if (flag == 1) {
                switch (lbl_803CC210[map]) {
                case 0:
                default:
                    GXSetTevColorIn(stage, GX_CC_CPREV, GX_CC_C0, GX_CC_A0, GX_CC_ZERO);
                    GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    GXSetTevAlphaIn(stage, GX_CA_A0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                    GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    break;
                case 1:
                    GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_C0, GX_CC_C0, GX_CC_CPREV);
                    GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                    GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    break;
                case 2:
                    GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_C0, GX_CC_C0, GX_CC_CPREV);
                    GXSetTevColorOp(stage, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                    GXSetTevAlphaOp(stage, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    break;
                }
            } else {
                switch (lbl_803CC210[map]) {
                case 0:
                default:
                    GXSetTevColorIn(stage, GX_CC_CPREV, GX_CC_C0, GX_CC_TEXA, GX_CC_ZERO);
                    GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                    GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    break;
                case 1:
                    GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_C0, GX_CC_A0, GX_CC_CPREV);
                    GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                    GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    break;
                case 2:
                    GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_C0, GX_CC_A0, GX_CC_CPREV);
                    GXSetTevColorOp(stage, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                    GXSetTevAlphaOp(stage, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    break;
                }
            }
            flag = 2;
            break;
        case 8:
            scale = state->listSize / 1000.0f;
            tevColor = lbl_803CCFF8;
            GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_CLEAR);
            PSMTXConcat(m, dispObj->worldMatrix, mvMtx);
            GXLoadPosMtxImm(mvMtx, GX_PNMTX0);
            PSMTXScale(nrmMtx, scale, scale, scale);
            PSMTXConcat(mvMtx, nrmMtx, nrmMtx);
            GXLoadNrmMtxImm(nrmMtx, GX_PNMTX0);
            nChans++;
            GXSetChanCtrl(GX_COLOR0, GX_TRUE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT0, GX_DF_CLAMP, GX_AF_NONE);
            GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
            numTexGens += 2;
            GXSetTexCoordGen2(coord, GX_TG_MTX2X4, GX_TG_TEX0 + numStages, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            if (numStages == 0) {
                GXSetTexCoordGen2(coord + 1, GX_TG_BUMP0, GX_TG_TEXCOORD0 + coord, GX_IDENTITY, GX_FALSE,
                                  GX_PTIDENTITY);
            } else {
                GXSetTexCoordGen2(coord + 1, GX_TG_BUMP0, GX_TG_TEXCOORD0 + coord, GX_IDENTITY, GX_FALSE,
                                  GX_PTIDENTITY);
            }
            GXSetTevOrder(stage, coord, map, GX_COLOR0A0);
            GXSetTevOrder(stage + 1, coord + 1, map, GX_COLOR_NULL);
            GXSetTevColor(GX_TEVREG0, tevColor);
            if (numStages == 0) {
                GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A0, GX_CC_RASC);
            } else {
                GXSetTevColorIn(stage, GX_CC_CPREV, GX_CC_TEXC, GX_CC_A0, GX_CC_RASC);
            }
            GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
            GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
            GXSetTevColorIn(stage + 1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A0, GX_CC_CPREV);
            GXSetTevColorOp(stage + 1, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(stage + 1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaOp(stage + 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
            texIndex += 2;
            numStages += 2;
            break;
        default:
            if (dispObj->userTevModeFunc != NULL) {
                dispObj->userTevModeFunc(mode, dispObj, m, &numTexGens, &numStages);
            } else {
                OSReport("Warning: DisplayObject.c: User TevMode %d not handled.\n", mode);
            }
            break;
        }
        if (mode == 5) {
            break;
        }
        stage = numStages;
        coord = texIndex;
        map = texIndex;
        shift += 4;
    } while ((u32)map < dispObj->numTextureChannels);

    if (dispObj->lightingData != NULL && flag != 0) {
        GXSetTevOrder(stage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
        GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
        GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        numStages++;
        stage++;
    }

    if (state->pad16 & 0x80) {
        if (fn_800B9AB0(mode, dispObj, state, &stage, &coord, &map, &chan, m) == 0) {
            numTexGens++;
            numStages++;
            if (lbl_803CC1F4 != NULL) {
                numTexGens++;
            }
        }
    } else if (state->pad8 & 0x80) {
        if (fn_800B9EA8(mode, dispObj, state, &stage, &coord, &map, &chan, m) == 0) {
            if (state->pad16 == 0) {
                numTexGens++;
                numStages++;
            } else {
                numTexGens += 2;
                numStages += 2;
            }
        }
    }

    if (dispObj->shaderFunc != NULL && dispObj->lightingData != NULL) {
        colorD = GX_CC_CPREV;
        alphaD = GX_CA_APREV;
        src = GX_TG_NRM;
        if (dispObj->lightingData->compCount == 2) {
            src = GX_TG_BINRM;
        }
        chan = GX_COLOR_NULL;
        if (mode == 5) {
            chan = GX_COLOR0A0;
            colorD = GX_CC_RASC;
            alphaD = GX_CA_RASA;
        }
        if (dispObj->pad8 != 0) {
            colorC = GX_CC_KONST;
            kColor.r = kColor.g = kColor.b = kColor.a = dispObj->pad8;
            GXSetTevKColor(GX_KCOLOR0, kColor);
            GXSetTevKColorSel(stage, GX_TEV_KCSEL_K0);
        } else {
            colorC = GX_CC_APREV;
            alphaD = GX_CA_KONST;
        }
        PSMTXScale(scaleMtx, 0.5f, -0.5f, 0.0f);
        PSMTXTrans(transMtx, 0.5f, 0.5f, 1.0f);
        PSMTXConcat(m, dispObj->worldMatrix, texMtx);
        PSMTXInverse(texMtx, texMtx);
        PSMTXTranspose(texMtx, texMtx);
        GXLoadTexMtxImm(texMtx, GX_TEXMTX0 + numStages * 3, GX_MTX3x4);
        PSMTXConcat(transMtx, scaleMtx, texMtx);
        GXLoadTexMtxImm(texMtx, GX_PTTEXMTX0 + numStages * 3, GX_MTX3x4);
        GXSetTexCoordGen2(coord, GX_TG_MTX3X4, src, GX_TEXMTX0 + numStages * 3, GX_TRUE,
                          GX_PTTEXMTX0 + numStages * 3);
        GXLoadTexObj(dispObj->shaderFunc, map);
        GXSetTevOrder(stage, coord, map, chan);
        GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_TEXC, colorC, colorD);
        GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, alphaD);
        GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        numTexGens++;
        numStages++;
        stage++;
        coord++;
        map++;
    }

    if (dispObj->shaderData != NULL && returnDrawShadows() && (state->pad16 & ShouldDrawShadows()->_4C)) {
        PSMTXConcat(returnMtxPtr(returnDrawShadows() - 1), dispObj->worldMatrix, shadowMtx);
        if (lbl_803CC20C != NULL) {
            lbl_803CC20C(shadowMtx, &stage, &coord, &map, &numStages, &numTexGens);
        } else {
            GXSetTevOrder(stage, coord, map, GX_COLOR0A0);
            GXSetTevColorIn(stage, GX_CC_CPREV, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ZERO);
            GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(stage, GX_CA_APREV, GX_CA_APREV, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTexCoordGen2(coord, GX_TG_MTX3X4, GX_TG_POS, GX_TEXMTX0 + numStages * 3, GX_FALSE, GX_PTIDENTITY);
            loadTlutRelated();
            GXLoadTexObj(dispObj->shaderData, map);
            GXLoadTexMtxImm(shadowMtx, GX_TEXMTX0 + numStages * 3, GX_MTX3x4);
            numTexGens++;
            numStages++;
            stage++;
            coord++;
            map++;
        }
    }

    if (state->pad16 & 0x10) {
        SetFogNone();
    } else {
        GXSetFog(fogSettings.type, fogSettings.startZ, fogSettings.endZ, fogSettings.nearZ, fogSettings.farZ,
                 fogSettings.color);
    }

    if (lbl_803CC200 != NULL) {
        lbl_803CC200(dispObj, &stage, &coord, &map, &numStages, &numTexGens, m);
    }

    GXSetNumTexGens(numTexGens);
    if (numStages != 0) {
        GXSetNumTevStages(numStages);
    }
    if (nChans != 0) {
        GXSetNumChans(nChans);
    }
}

typedef struct DOTexRecord {
    /* 0x00 */ u16 index;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u8 body[0x1C];
} DOTexRecord; // size 0x20

static inline TextureBody* DOTexGet(void* palette, u32 id) {
    DOTexRecord* records = palette;

    return (TextureBody*)records[records[id + 1].index].body;
}

static inline void DOSetVtxDesc(u32 setting) {
    GXVtxDescList vcd[27];
    u32 type;
    int i;
    int shift;
    GXAttr attr;

    GXClearVtxDesc();
    i = 0;
    type = setting & 3;
    if (type != 0) {
        vcd[i].mAttr = GX_VA_PNMTXIDX;
        vcd[i].mType = type;
        i++;
    }
    for (attr = GX_VA_POS, shift = 2; attr <= GX_VA_TEX7; attr++, shift += 2) {
        type = (setting >> shift) & 3;
        if (type != 0) {
            vcd[i].mAttr = attr;
            vcd[i].mType = type;
            i++;
        }
    }
    type = (setting >> 26) & 3;
    if (type != 0) {
        vcd[i].mAttr = GX_VA_NBT;
        vcd[i].mType = type;
        i++;
    }
    vcd[i].mAttr = GX_VA_NULL;
    GXSetVtxDescv(vcd);
}

void SetState(DisplayStateList* state, struct DODisplayObj* dispObj, MtxPtr m) {
    GXTexFilter minFilter;
    GXTexFilter magFilter;
    u32 channel;
    TextureBody* tex;
    GXTexWrapMode wrapS;
    GXTexWrapMode wrapT;
    GXBool mipmap;
    f32 minLOD;
    f32 maxLOD;
    f32 lodBias;
    int mtxIdx;
    Mtx tmp;

    switch (state->id) {
    case 1:
        channel = (state->setting >> 13) & 7;
        tex = DOTexGet(dispObj->textureData[channel].texturePalette, state->setting & 0x1FFF);
        lbl_803CC210[channel] = state->pad16;
        wrapS = (state->setting >> 16) & 0xF;
        switch (wrapS) {
        case 0:
            wrapS = GX_CLAMP;
            break;
        case 1:
            wrapS = GX_REPEAT;
            break;
        case 2:
            wrapS = GX_MIRROR;
            break;
        }
        wrapT = (state->setting >> 20) & 0xF;
        switch (wrapT) {
        case 0:
            wrapT = GX_CLAMP;
            break;
        case 1:
            wrapT = GX_REPEAT;
            break;
        case 2:
            wrapT = GX_MIRROR;
            break;
        }
        mipmap = tex->minLOD != tex->maxLOD;
        minLOD = tex->minLOD;
        maxLOD = tex->maxLOD;
        minFilter = tex->minFilter;
        magFilter = tex->magFilter;
        lodBias = tex->lodBias;
        if (tex->tlut != NULL) {
            GXInitTexObjCI(&lbl_803CB5FC[channel], tex->pixels, tex->width, tex->height, tex->gxFormat, wrapS, wrapT,
                           mipmap, channel);
            GXInitTlutObj(&lbl_803CB49C[channel], tex->tlut, tex->tlutFormat, tex->tlutEntries);
            GXLoadTlut(&lbl_803CB49C[channel], channel);
        } else {
            GXInitTexObj(&lbl_803CB5FC[channel], tex->pixels, tex->width, tex->height, tex->gxFormat, wrapS, wrapT,
                         mipmap);
        }
        GXInitTexObjLOD(&lbl_803CB5FC[channel], minFilter, magFilter, minLOD, maxLOD, lodBias, GX_FALSE, GX_FALSE,
                        GX_ANISO_1);
        GXLoadTexObj(&lbl_803CB5FC[channel], channel);
        break;
    case 2:
        DOSetVtxDesc(state->setting);
        break;
    case 3:
        Custom_SetState(dispObj, state, m);
        break;
    case 4:
        mtxIdx = (state->setting & 0xFFFF) * 3;
        PSMTXConcat(m, SkinForwardArray[state->setting >> 16], tmp);
        GXLoadPosMtxImm(tmp, mtxIdx);
        if (dispObj->lightingData != NULL) {
            PSMTXConcat(m, SkinInverseArray[state->setting >> 16], tmp);
            GXLoadNrmMtxImm(tmp, mtxIdx);
        }
        break;
    }
}

void GetColorFromQuant(void* src, u32 format, u8* r, u8* g, u8* b, u8* a) {
    switch ((format >> 4) & 0xF) {
    case GX_RGB565:
        *r = (*(u16*)src >> 8) & 0xF8;
        *g = (*(u16*)src >> 3) & 0xFC;
        *b = (*(u16*)src & 0x1F) << 3;
        *a = 0xFF;
        break;
    case GX_RGBA4:
        *r = (*(u16*)src >> 12) & 0xF;
        *g = (*(u16*)src >> 8) & 0xF;
        *b = (*(u16*)src >> 4) & 0xF;
        *a = *(u16*)src & 0xF;
        *r |= *r << 4;
        *g |= *g << 4;
        *b |= *b << 4;
        *a |= *a << 4;
        break;
    case GX_RGBA8:
        *r = *(u32*)src >> 24;
        *g = *(u32*)src >> 16;
        *b = *(u32*)src >> 8;
        *a = *(u32*)src;
        break;
    case GX_RGB8:
    case GX_RGBX8:
        *r = *(u32*)src >> 24;
        *g = *(u32*)src >> 16;
        *b = *(u32*)src >> 8;
        *a = 0xFF;
        break;
    case GX_RGBA6:
        *r = (*(u16*)src & 0xFC0000) >> 16;
        *g = (*(u16*)src & 0x3F000) >> 10;
        *b = (*(u16*)src & 0xFC0) >> 4;
        *a = (*(u16*)src & 0x3F) << 2;
        break;
    }
}

static inline u8 DOGetCompSize(u8 type) {
    switch (type) {
    case GX_U8:
    case GX_S8:
        return 1;
    case GX_U16:
    case GX_S16:
        return 2;
    case GX_F32:
        return 4;
    }
    return 0;
}

static inline u32 DOGetColorSize(u8 type) {
    u8 size;

    switch (type) {
    case GX_RGB565:
    case GX_RGBA4:
        size = 2;
        break;
    case GX_RGB8:
    case GX_RGBA6:
        size = 3;
        break;
    case GX_RGBX8:
    case GX_RGBA8:
        size = 4;
        break;
    default:
        size = 0;
        break;
    }
    return size;
}

// Plain static, not static inline: MWCC also compiles it standalone at this point, which pools its
// 255.0f ahead of DOVARender's own literals (the .sdata2 layout depends on it). The standalone copy
// is unreferenced once inlined and mwld dead-strips it.
static void DOSetLights(f32 amb, u8 numLights, va_list* list, GXColorSrc colorSrc) {
    GXColor color;
    u32 i;
    u32 lightMask;
    Light* light;

    lightMask = GX_LIGHT_NULL;
    if (!lightingRelated(&color)) {
        color.r = color.g = color.b = 255.0f * amb;
        color.a = 0xFF;
    }
    GXSetChanAmbColor(GX_COLOR0A0, color);
    amb = 1.0f - amb;
    for (i = 0; i < numLights; i++) {
        light = va_arg(*list, Light*);
        color.r = light->color.r * amb;
        color.g = light->color.g * amb;
        color.b = light->color.b * amb;
        GXInitLightColor(&light->lt_obj, color);
        GXInitLightPos(&light->lt_obj, light->worldPosition.x, light->worldPosition.y, light->worldPosition.z);
        GXInitLightDir(&light->lt_obj, light->worldDirection.x, light->worldDirection.y, light->worldDirection.z);
        GXLoadLightObjImm(&light->lt_obj, 1 << i);
        lightMask |= 1 << i;
    }
    GXSetChanCtrl(GX_COLOR0A0, GX_TRUE, GX_SRC_REG, colorSrc, lightMask, GX_DF_CLAMP, GX_AF_SPOT);
}


static void DODrawStates(struct DODisplayObj* dispObj, MtxPtr camera) {
    DisplayStateList* state;
    u32 i;

    state = dispObj->displayData->displayStateList;
    for (i = 0; i < dispObj->displayData->numStateEntries; i++) {
        SetState(state, dispObj, camera);
        if (state->primitiveList != NULL) {
            GXCallDisplayList(state->primitiveList, state->listSize);
        }
        state++;
    }
}

void DOVARender(struct DODisplayObj* dispObj, MtxPtr camera, u8 numLights, va_list* list) {
    GXColor matColor;
    Mtx mv;
    Mtx tmpMtx;
    u32 i;
    GXColorSrc colorSrc = GX_SRC_VTX;

    if (dispObj == NULL || !dispObj->visibility) {
        return;
    }

    if (SkinForwardArray == NULL) {
        PSMTXConcat(camera, dispObj->worldMatrix, mv);
        GXLoadPosMtxImm(mv, GX_PNMTX0);
        GXSetCurrentMtx(GX_PNMTX0);
    }

    GXSetArray(GX_VA_POS, dispObj->positionData->positionArray,
               dispObj->positionData->compCount * DOGetCompSize(dispObj->positionData->quantizeInfo >> 4));
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, dispObj->positionData->quantizeInfo >> 4,
                    dispObj->positionData->quantizeInfo & 0xF);

    if (dispObj->colorData != NULL) {
        if (dispObj->colorData->numColors == 1) {
            colorSrc = GX_SRC_REG;
            GetColorFromQuant(dispObj->colorData->colorArray, dispObj->colorData->quantizeInfo, &matColor.r,
                              &matColor.g, &matColor.b, &matColor.a);
            GXSetChanMatColor(GX_COLOR0A0, matColor);
        } else {
            GXSetArray(GX_VA_CLR0, dispObj->colorData->colorArray, DOGetColorSize(dispObj->colorData->quantizeInfo >> 4));
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, dispObj->colorData->compCount != 3,
                            dispObj->colorData->quantizeInfo >> 4, 0);
        }
        GXSetNumChans(1);
    } else {
        matColor.r = 0xFF;
        matColor.g = 0xFF;
        matColor.b = 0xFF;
        matColor.a = 0xFF;
        GXSetChanMatColor(GX_COLOR0A0, matColor);
        GXSetNumChans(1);
        colorSrc = GX_SRC_REG;
    }

    if (dispObj->textureData != NULL) {
        for (i = 0; i < dispObj->numTextureChannels; i++) {
            GXSetArray(GX_VA_TEX0 + i, dispObj->textureData[i].textureCoordArray,
                       dispObj->textureData[i].compCount * DOGetCompSize(dispObj->textureData[i].quantizeInfo >> 4));
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0 + i, GX_TEX_ST, dispObj->textureData[i].quantizeInfo >> 4,
                            dispObj->textureData[i].quantizeInfo & 0xF);
            GXSetTexCoordGen2(i, GX_TG_MTX2X4, GX_TG_TEX0 + i, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        }
    }

    if (dispObj->lightingData != NULL) {
        if (dispObj->lightingData->normalArray != NULL) {
            if (dispObj->lightingData->compCount == 3 || dispObj->lightingData->compCount == 6) {
                GXSetArray(GX_VA_NRM, dispObj->lightingData->normalArray,
                           dispObj->lightingData->compCount * DOGetCompSize(dispObj->lightingData->quantizeInfo >> 4));
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, dispObj->lightingData->quantizeInfo >> 4,
                                dispObj->lightingData->quantizeInfo & 0xF);
            } else if (dispObj->lightingData->compCount == 2) {
                GXSetArray(GX_VA_NBT, dispObj->lightingData->normalArray,
                           DOGetCompSize(dispObj->lightingData->quantizeInfo >> 4) * 3);
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NBT, GX_NRM_NBT3, dispObj->lightingData->quantizeInfo >> 4,
                                dispObj->lightingData->quantizeInfo & 0xF);
            } else {
                OSReport("DOVARender: Invalid component count for normals %d\n", dispObj->lightingData->compCount);
            }
        } else {
            GXSetArray(GX_VA_NRM, normalTable, DOGetCompSize(normalTableQuantizeInfo >> 4) * 3);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, normalTableQuantizeInfo >> 4,
                            normalTableQuantizeInfo & 0xF);
        }
        if (SkinForwardArray == NULL) {
            PSMTXInverse(mv, tmpMtx);
            PSMTXTranspose(tmpMtx, mv);
            GXLoadNrmMtxImm(mv, GX_PNMTX0);
        }
    }

    if (dispObj->lightingData != NULL && dispObj->colorData != NULL && numLights != 0) {
        DOSetLights(0.01f * dispObj->lightingData->ambientPercentage, numLights, list, colorSrc);
    } else {
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, colorSrc, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    }

    DODrawStates(dispObj, camera);
}

void DOVARenderSkin(struct DODisplayObj* dispObj, MtxPtr camera, MtxPtr mtxArray, MtxPtr invTransposeMtxArray,
                    u8 numLights, va_list* list) {
    SkinForwardArray = (Mtx*)mtxArray;
    SkinInverseArray = (Mtx*)invTransposeMtxArray;
    DOVARender(dispObj, camera, numLights, list);
    SkinForwardArray = NULL;
    SkinInverseArray = NULL;
}

void updateMemoryLocation(struct DODisplayObj* dispObj, void* data) {
    if (dispObj != NULL) {
        dispObj->shaderData = data;
    }
}

void DOSetWorldMatrix(struct DODisplayObj* dispObj, MtxPtr m) {
    PSMTXCopy(m, dispObj->worldMatrix);
}

void InitDisplayObjWithLayout(struct DODisplayObj* dispObj, DODisplayLayout* layout) {
    u16 i;

    if (layout->positionData != NULL) {
        dispObj->positionData = _OSAllocFromHeap(0x20, sizeof(PositionData));
        *dispObj->positionData = *layout->positionData;
    } else {
        dispObj->positionData = NULL;
    }

    if (layout->colorData != NULL) {
        dispObj->colorData = _OSAllocFromHeap(0x20, sizeof(ColorData));
        *dispObj->colorData = *layout->colorData;
    } else {
        dispObj->colorData = NULL;
    }

    if (layout->textureData != NULL && layout->numTextureChannels != 0) {
        dispObj->textureData = _OSAllocFromHeap(0x20, layout->numTextureChannels * sizeof(TextureData));
        dispObj->numTextureChannels = layout->numTextureChannels;
        for (i = 0; i < layout->numTextureChannels; i++) {
            dispObj->textureData[i] = layout->textureData[i];
        }
    } else {
        dispObj->textureData = NULL;
        dispObj->numTextureChannels = 0;
    }

    if (layout->lightingData != NULL) {
        dispObj->lightingData = _OSAllocFromHeap(0x20, sizeof(LightingData));
        *dispObj->lightingData = *layout->lightingData;
    } else {
        dispObj->lightingData = NULL;
    }

    if (layout->displayData != NULL) {
        dispObj->displayData = _OSAllocFromHeap(0x20, sizeof(DisplayData));
        *dispObj->displayData = *layout->displayData;
    } else {
        dispObj->displayData = NULL;
    }

    dispObj->visibility = TRUE;
    PSMTXIdentity(dispObj->worldMatrix);
    dispObj->shaderFunc = NULL;
    dispObj->shaderData = NULL;
    dispObj->pad8 = layout->pad8;
    memcpy(dispObj->unk58, layout->unk20, sizeof(dispObj->unk58));
    memcpy(dispObj->unk54, layout->unk1C, sizeof(dispObj->unk54));
    memcpy(dispObj->unk60, layout->unk28, sizeof(dispObj->unk60));
    memcpy(dispObj->unk5C, layout->unk24, sizeof(dispObj->unk5C));
    memcpy(dispObj->unk68, layout->unk30, sizeof(dispObj->unk68));
    memcpy(dispObj->unk64, layout->unk2C, sizeof(dispObj->unk64));
}

void DOGet(struct DODisplayObj** dispObj, DODisplayDataPtr pal, u16 id, char* name) {
    DODisplayLayout* layout;

    if (id >= pal->numDescriptors) {
        OSReport("Display object id %d is greater than number of objects %d", id, pal->numDescriptors);
        *dispObj = NULL;
        return;
    }
    layout = pal->descriptorArray[id].layout;
    *dispObj = _OSAllocFromHeap(0x20, sizeof(struct DODisplayObj));
    InitDisplayObjWithLayout(*dispObj, layout);
}
