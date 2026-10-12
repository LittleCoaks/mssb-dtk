#include "Unknown/sprt.h"

typedef struct SpriteRenderState {
    /*0x00*/ u8 _00[0x78];
    /*0x78*/ u32 zModeReg; // last GX z-mode BP register value written (register id 0x40 in the top byte)
    /*0x7C*/ u32 savedZModeReg;
    /*0x80*/ u8 _80[0x8A - 0x80];
    /*0x8A*/ u8 renderingMode;
    /*0x8B*/ u8 _8B;
    /*0x8C*/ u8 unk8C;
} SpriteRenderState;

extern SpriteRenderState* lbl_803CBB34;

extern s32 lbl_803CC1D8[2];

void fn_800B0D28(s32 value) {
    lbl_803CC1D8[0] = value;
    lbl_803CC1D8[1] = value;
}

void AllocateSprite(void) {
    return;
}

void fn_800B117C(u8 value) {
    lbl_803CBB34->unk8C = value;
}

void DrawNullSprite(void* vtx, s32 count) {
    DrawSprite(0x98, vtx, count, NULL, 0, 0);
}

void fn_800B12DC(void* vtx, s32 count) {
    DrawSprite(0xA0, vtx, count, NULL, 0, 0);
}

void renderSprite(void* vtx, void* tex, u16 sMax, u16 tMax) {
    DrawSprite(0x80, vtx, 4, tex, sMax, tMax);
}

typedef struct {
    /*0x00*/ u8 _00[8];
    /*0x08*/ u16 arg5;
    /*0x0A*/ u16 arg4;
} SpriteTexObj;

void DrawSprite_TexObj(void* vtx, void* texObj, s32 arg2) {
    DrawSprite(0x80, vtx, 4, texObj, ((SpriteTexObj*)texObj)->arg4, ((SpriteTexObj*)texObj)->arg5);
}

void fn_800B1388(void* vtx) {
    DrawSprite(0x80, vtx, 4, NULL, 0, 0);
}

void DrawSprite(u32 flags, void* vtx, s32 count, void* texObj, u16 arg4, u16 arg5) {
    return;
}

void setTextRenderingMode(s32 mode) {
    lbl_803CBB34->renderingMode = mode;
}

BOOL fn_800B216C(GXBool compareEnable, GXCompare func, GXBool updateEnable) {
    u32 reg = compareEnable | (func << 1) | (updateEnable << 4) | (0x40 << 24);

    if (lbl_803CBB34->zModeReg == reg) {
        return FALSE;
    }
    lbl_803CBB34->zModeReg = reg;
    return TRUE;
}

void fn_800B21A8(int mode) {
    if (mode == 2) {
        u32 prev = lbl_803CBB34->zModeReg;

        if (fn_800B216C(GX_TRUE, GX_LESS, GX_TRUE)) {
            lbl_803CBB34->savedZModeReg = prev;
        }
    } else if (mode != 0) {
        fn_800B216C(GX_TRUE, GX_LEQUAL, GX_TRUE);
    } else {
        fn_800B216C(GX_TRUE, GX_ALWAYS, GX_TRUE);
    }
}
