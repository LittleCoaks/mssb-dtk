#include "Unknown/File_0x8003a688.h"
#include "Unknown/File_0x80024184.h"
#include "Dolphin/mtx.h"
#include "string.h"

extern GXTexObj lbl_803C50B0;
extern GXTlutObj lbl_803C50DC;
extern u8 lbl_803CBCAC;
extern void (*lbl_803CBCA8)(void);
extern u8 lbl_803CBCB4;
extern u8 lbl_803CB828[3];

u16 lbl_800F7AC0[16] = {
    0x0000, 0x11FF, 0x22FF, 0x33FF, 0x44FF, 0x55FF, 0xFFFF, 0xFFFF,
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};

void fn_8003A688(int slot, f32 scaleS, f32 scaleT) {
    lbl_802D3D80.texScale[slot][0] = scaleS / 2;
    lbl_802D3D80.texScale[slot][1] = scaleT / 2;
}

void fn_8003A6B0(int slot, TextureBody* texture, f32 scaleS, f32 scaleT) {
    if (texture->tlut != NULL) {
        lbl_802D3D80.texKind[slot] = 2;
        GXInitTexObjCI(&lbl_802D3D80.texObj[slot], texture->pixels, texture->width, texture->height,
                       texture->gxFormat, texture->wrapS, texture->wrapT, GX_FALSE, slot);
        GXInitTlutObj(&lbl_802D3D80.tlutObj[slot], texture->tlut, texture->tlutFormat, texture->tlutEntries);
    } else {
        lbl_802D3D80.texKind[slot] = 1;
        GXInitTexObj(&lbl_802D3D80.texObj[slot], texture->pixels, texture->width, texture->height,
                     texture->gxFormat, texture->wrapS, texture->wrapT, GX_FALSE);
    }
    GXInitTexObjLOD(&lbl_802D3D80.texObj[slot], texture->minFilter, texture->magFilter, texture->minLOD,
                    texture->maxLOD, texture->lodBias, GX_FALSE, GX_FALSE, GX_ANISO_1);
    fn_8003A688(slot, scaleS, scaleT);
}

void fn_8003A848(u8 r, u8 g, u8 b) {
    lbl_803CB828[0] = r;
    lbl_803CB828[1] = g;
    lbl_803CB828[2] = b;
}

void fn_8003A85C(u8 value) {
    lbl_802D3D80.unkD38 = value;
    lbl_802D3D80.unkA00 = 0;
    lbl_802D3D80.unkA02 = 0;
    memset(lbl_802D3D80.texKind, 0, sizeof(lbl_802D3D80.texKind));
}

static inline u8 getCompSize(u8 compType) {
    switch (compType) {
    case GX_U8:
    case GX_S8:
        return 1;
    case GX_U16:
    case GX_S16:
        return 2;
    case GX_F32:
        return 4;
    default:
        return 0;
    }
}

void fn_8003A8A0(struct DODisplayObj* dispObj, MtxPtr camera, int flag) {
    Mtx mv;
    GXVtxDescList vcd[GX_VA_MAX_ATTR + 1];
    DisplayStateList* state;
    GXAttr attr;
    int i;
    int j;
    u32 shift;
    u32 type;

    PSMTXConcat(camera, dispObj->worldMatrix, mv);
    GXLoadPosMtxImm(mv, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);

    GXSetArray(GX_VA_POS, dispObj->positionData->positionArray,
               dispObj->positionData->compCount * getCompSize(dispObj->positionData->quantizeInfo >> 4));
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, dispObj->positionData->quantizeInfo >> 4,
                    dispObj->positionData->quantizeInfo & 0xF);

    if (dispObj->textureData != NULL) {
        for (i = 0; i < dispObj->numTextureChannels; i++) {
            GXSetArray(attr = GX_VA_TEX0 + i, dispObj->textureData[i].textureCoordArray,
                       dispObj->textureData[i].compCount * getCompSize(dispObj->textureData[i].quantizeInfo >> 4));
            GXSetVtxAttrFmt(GX_VTXFMT0, attr, GX_TEX_ST, dispObj->textureData[i].quantizeInfo >> 4,
                            dispObj->textureData[i].quantizeInfo & 0xF);
            GXSetTexCoordGen2(GX_TEXCOORD0 + i, GX_TG_MTX3X4, GX_TG_TEX0 + i, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        }
        GXSetNumTexGens(dispObj->numTextureChannels);
    } else {
        GXSetNumTexGens(0);
    }

    state = dispObj->displayData->displayStateList;
    for (j = 0; j < dispObj->displayData->numStateEntries; j++) {
        switch (state->id) {
        case 1: {
            TEXPalettePtr pal = dispObj->textureData[(state->setting >> 13) & 7].texturePalette;
            u16 index = *(u16*)((u8*)pal + (state->setting & 0x1FFF) * 0x20 + 0x20);
            SetDisplayStateTexture((TextureBody*)((u8*)pal + index * 0x20 + 4), (state->setting >> 13) & 7,
                                   (state->setting >> 13) & 7);
            break;
        }
        case 2:
            GXClearVtxDesc();
            i = 0;
            type = state->setting & 3;
            if (type != 0) {
                vcd[0].mType = type;
                i = 1;
                vcd[0].mAttr = GX_VA_PNMTXIDX;
            }
            for (attr = GX_VA_POS, shift = 2; attr <= GX_VA_TEX7; attr++, shift += 2) {
                type = (state->setting >> shift) & 3;
                if (type != 0) {
                    vcd[i].mAttr = attr;
                    vcd[i].mType = type;
                    i++;
                }
            }
            type = (state->setting >> 26) & 3;
            if (type != 0) {
                vcd[i].mAttr = attr;
                vcd[i].mType = type;
                i++;
            }
            vcd[i].mAttr = GX_VA_NULL;
            GXSetVtxDescv(vcd);
            break;
        case 3:
            if (lbl_803CBCA8 != NULL) {
                lbl_803CBCA8();
            }
            break;
        case 4:
            break;
        }
        if (state->primitiveList != NULL) {
            GXCallDisplayList(state->primitiveList, state->listSize);
        }
        state++;
    }
}

void fn_8003AC90(void) {
    GXColor color;

    color.r = color.g = color.b = lbl_803CBCB4;
    color.a = 0xFF;
    GXSetChanMatColor(GX_COLOR0A0, color);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_RASA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
}

void GXTexObjRelated(TextureRecord* texture) {
    GXInitTexObjCI(&lbl_803C50B0, texture->pixels, texture->width, texture->height, GX_TF_C4, texture->wrapS,
                   texture->wrapT, GX_FALSE, 0);
    GXInitTlutObj(&lbl_803C50DC, lbl_800F7AC0, GX_TL_IA8, 16);
    GXInitTexObjLOD(&lbl_803C50B0, texture->minFilter, texture->magFilter, texture->minLOD, texture->maxLOD,
                    texture->lodBias, GX_FALSE, GX_FALSE, GX_ANISO_1);
    lbl_803CBCAC = TRUE;
}
