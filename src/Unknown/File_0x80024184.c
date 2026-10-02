#define SQRT2_LINKAGE static
#include "Unknown/File_0x80024184.h"
#include "Unknown/File_0x800acf14.h"
#include "static/UnknownHomes_Static.h"
#include "game/UnknownHomes_Game.h"
#include "Dolphin/os.h"
#include "Dolphin/mtxext.h"
#include "string.h"

typedef struct CharStaticIndex {
    /*0x0*/ u8 _0;
    /*0x1*/ u8 trackerIdx;
    /*0x2*/ u8 requirementRow;
    /*0x3*/ u8 _3[3];
} CharStaticIndex; // size: 0x6

typedef struct StarMissionRequirement {
    /*0x0*/ s16 type;
    /*0x2*/ s16 target;
    /*0x4*/ s16 flags;
    /*0x6*/ s16 _6[2];
} StarMissionRequirement; // size: 0xA

extern CharStaticIndex characterStaticIndexes[54];
extern StarMissionRequirement starMissionRequirementsTable[32][10];
extern u8 unlockableCharacter_noDupeNoGapCharID[8];

OSThread* GXGetCurrentGXThread(void);

u16 nullTexImage[16] = {
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};

TextureBody nullTex = {
    nullTexImage, NULL, 4, 4, GX_CLAMP, GX_CLAMP, GX_LINEAR, GX_LINEAR, 0.0f, 0, 0, 0, GX_TF_RGB5A3, 0, 0, 0, 0, 0,
};

void gOz_GXSetTexture(GXTevMode mode, int texCoordFrac, BOOL useNormals) {
    if (OSGetCurrentThread() != GXGetCurrentGXThread()) {
        OSPanic("sub.c", 674, "gOz_GXSetTexture was called in thread that is not current GX thread.\n");
    }
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    if (useNormals) {
        GXSetVtxDesc(GX_VA_NRM, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_NBT, GX_F32, 0);
    }
    switch (mode) {
    case GX_MODULATE:
    case GX_PASSCLR:
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        if (mode == GX_PASSCLR) {
            break;
        }
    case GX_REPLACE:
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        if (texCoordFrac < 0) {
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        } else {
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, (u8)texCoordFrac);
        }
        break;
    }
    GXSetTevOrder(GX_TEVSTAGE0, mode == GX_PASSCLR ? GX_TEXCOORD_NULL : GX_TEXCOORD0,
                  mode == GX_PASSCLR ? GX_TEXMAP_NULL : GX_TEXMAP0, mode == GX_REPLACE ? GX_COLOR_NULL : GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3X4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumChans(mode != GX_REPLACE);
    GXSetNumTexGens(mode != GX_PASSCLR);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, mode);
}

void fn_80024390(Mtx44 mtx, f32* projection, GXProjectionType type) {
    int col = type == GX_PERSPECTIVE ? 2 : 3;

    projection[0] = type;
    projection[1] = mtx[0][0];
    projection[2] = mtx[0][col];
    projection[3] = mtx[1][1];
    projection[4] = mtx[1][col];
    projection[5] = mtx[2][2];
    projection[6] = mtx[2][3];
}

void SetDisplayStateTexture(TextureBody* tex, int texMap, int tlutName) {
    GXTlutObj tlutObj;
    GXTexObj texObj;
    GXTexWrapMode wrapS;
    GXTexWrapMode wrapT;
    u32 bits;
    u16 dim;

    if (OSGetCurrentThread() != GXGetCurrentGXThread()) {
        OSPanic("sub.c", 574, "gOz_GXSetTexture was called in thread that is not current GX thread.\n");
    }
    if (tex == NULL) {
        tex = &nullTex;
    }

    wrapS = tex->wrapS;
    if (wrapS != GX_CLAMP) {
        dim = tex->width;
        bits = 0;
        while (dim != 0) {
            bits += dim & 1;
            dim >>= 1;
        }
        if (bits > 1) {
            wrapS = GX_CLAMP;
        }
    }
    wrapT = tex->wrapT;
    if (wrapT != GX_CLAMP) {
        dim = tex->height;
        bits = 0;
        while (dim != 0) {
            bits += dim & 1;
            dim >>= 1;
        }
        if (bits > 1) {
            wrapT = GX_CLAMP;
        }
    }

    if (tex->tlut != NULL) {
        GXInitTexObjCI(&texObj, tex->pixels, tex->width, tex->height, tex->gxFormat, wrapS, wrapT,
                       tex->minLOD != tex->maxLOD, tlutName);
        GXInitTlutObj(&tlutObj, tex->tlut, tex->tlutFormat, tex->tlutEntries);
        GXLoadTlut(&tlutObj, tlutName);
    } else {
        GXInitTexObj(&texObj, tex->pixels, tex->width, tex->height, tex->gxFormat, wrapS, wrapT,
                     tex->minLOD != tex->maxLOD);
    }
    GXInitTexObjLOD(&texObj, tex->minFilter, tex->magFilter, tex->minLOD, tex->maxLOD, tex->lodBias, GX_FALSE,
                    GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, texMap);
}

void fn_800245EC(camera_803c639c_s* camera, Mtx view, Vec* src, f32* dst, int count, int flipY) {
    Mtx44 m;
    Vec out;

    PSMTX44Identity(m);
    PSMTXCopy(view, m);
    PSMTX44Concat(camera->proj, m, m);
    while (count-- != 0) {
        PSMTX44MultVec(m, src, &out);
        src++;
        dst[0] = 0.5f * out.x + 0.5f;
        dst[1] = 0.5f * out.y * -flipY + 0.5f;
        dst += 2;
    }
}

void fn_800246D4(int (*compare)(const void*, const void*), void* src, void* dst, int size, int count) {
    int mid;
    int hi;
    int lo;
    int cmp;
    int offset;
    int move;
    int total;
    int i;
    int n;
    u8* buf;

    total = size * count;
    buf = allocateAlignedMemoryBlock(32, total);
    i = 0;
    n = count;
    while (n-- != 0) {
        lo = 0;
        hi = i;
        while (lo != hi) {
            mid = lo + (hi - lo) / 2;
            cmp = compare(src, buf + mid * size);
            if (cmp == 0) {
                lo = mid;
                break;
            }
            if (cmp < 0) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        offset = lo * size;
        move = i - lo;
        if (move != 0) {
            memmove(buf + offset + size, buf + offset, move * size);
        }
        memcpy(buf + offset, src, size);
        src = (u8*)src + size;
        i++;
    }
    memcpy(dst, buf, total);
    unkLoadingCleanupRelated(buf);
}

int fn_800247E4(int x, int y, int width, int bytesPerPixel) {
    int fineY;
    int fineX;
    int rowBase;

    fineY = y % 4;
    y /= 4;
    rowBase = width * (y * 4);
    fineX = x % 4;
    x /= 4;
    return bytesPerPixel * (fineY * 4 + (rowBase + x * 16) + fineX);
}

BOOL challengeStarRelatedInd(int charID, int mission) {
    u8 row = characterStaticIndexes[charID].requirementRow;
    s8 status = starMissionCompletionTracker[charID].inGameMissionTracker[mission].starMissionStatus;
    s16 flags;

    if (status == (s8)STAR_MISSION_TRACKING_COMPLETED_SAVED) {
        return TRUE;
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE &&
        status == (s8)STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY) {
        flags = starMissionRequirementsTable[row][mission].flags;
        if (flags & 1) {
            return FALSE;
        }
        if (flags & 2) {
            if (g_d_GameSettings.challengeDifficulty < 1) {
                return FALSE;
            }
        } else if (flags & 4) {
            if (g_d_GameSettings.challengeDifficulty < 2) {
                return FALSE;
            }
        } else if (flags & 8) {
            if (g_d_GameSettings.challengeDifficulty < 3) {
                return FALSE;
            }
        }
        if (flags & 0x800) {
            if (((s8*)starMissionCompletionTracker)[0x44EF] == 0 && ((s8*)starMissionCompletionTracker)[0x44F0] == 0 &&
                Static_Stats_Tables.captainSelectedID[1] != CHAR_ID_BOWSER) {
                return FALSE;
            }
        }
        return TRUE;
    }
    return FALSE;
}

u32 multBottomBits_asFloat(u32 value, u32 scale) {
    int v;
    f32 fs;

    v = (u8)value;
    fs = (int)(u8)scale;
    fs /= 255.0f;
    value &= ~0xFF;
    value |= (int)(v * fs);
    return value;
}

u32 byteWiseMultiply(u32 scale, u32 color) {
    int s = (u8)scale;
    f32 f;
    u32 result;

    f = (int)(u8)color / 255.0f;
    result = (int)(s * f);
    f = (int)(u8)(color >> 8) / 255.0f;
    result |= (int)(s * f) << 8;
    f = (int)(u8)(color >> 16);
    f /= 255.0f;
    result |= (int)(s * f) << 16;
    result |= (int)(s * ((int)(color >> 24) / 255.0f)) << 24;
    return result;
}

int LERPToNewRange_Float(int value, int inMin, int inMax, int outMin, int outMax) {
    f32 t;
    f32 span;
    f32 range = inMax - inMin;

    if (range == 0.0f) {
        t = 1.0f;
    } else {
        t = (f32)(value - inMin) / range;
        t = t > 1.0f ? 1.0f : t < 0.0f ? 0.0f : t;
    }
    span = outMax - outMin;
    return outMin + (int)(span * t);
}

f32 LinearInterpolateToNewRange(f32 value, f32 prevMin, f32 prevMax, f32 nextMin, f32 nextMax) {
    f32 t;
    f32 span;
    f32 range = prevMax - prevMin;

    if (range == 0.0f) {
        t = 1.0f;
    } else {
        t = (value - prevMin) / range;
        t = t > 1.0f ? 1.0f : t < 0.0f ? 0.0f : t;
    }
    span = nextMax - nextMin;
    return span * t + nextMin;
}

BOOL isCharacterUnlocked(int charID) {
    int i;

    for (i = 0; i < 6; i++) {
        if (unlockableCharacter_noDupeNoGapCharID[i] == characterStaticIndexes[charID].requirementRow) {
            if (!g_d_GameSettings.characterUnlocked[i]) {
                return FALSE;
            }
            break;
        }
    }
    return TRUE;
}

int fn_80024C6C(fn_80024C6C_s* obj, int arg1) {
    if (!obj->_274) {
        return -1;
    }
    if (obj->_254 >= 9) {
        return -1;
    }
    if (obj->_25A != arg1) {
        switch (obj->_252) {
        case 38:
        case 40:
        case 41:
            return -1;
        case 14:
        case 16:
        case 37:
        case 44:
        case 45:
        case 46:
        case 47:
            return 2;
        }
        return 2;
    }
    switch (obj->_252) {
    case 18:
    case 38:
    case 40:
    case 41:
        return -1;
    case 14:
    case 16:
    case 37:
    case 44:
    case 45:
    case 46:
    case 47:
        return 0;
    }
    return 1;
}
