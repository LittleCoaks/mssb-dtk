#include "text/text.h"
#include "Dolphin/mtx.h"
#include "Unknown/File_0x800c0770.h"
#include "Unknown/sprt.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x800363d8.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/sub.h"

// Per-glyph font metrics for the text engine, addressed as one object:
// widths and vertical offsets for the normal and alternate (fixed-grid)
// fonts, then the control-code recolor table.
typedef struct FontMetricsTables {
    /* 0x000 */ u8 altWidths[0x65][4];
    /* 0x194 */ u8 widths[0xCB][4];
    /* 0x4C0 */ u8 altYOffs[0x65][4];
    /* 0x654 */ u8 yOffs[0xCB][4];
    /* 0x980 */ u32 colors[10];
} FontMetricsTables;

// Per-element frame data filled by fn_8000CEF0 (see LayoutFrameInfo).
typedef struct TextLayoutFrame {
    /* 0x00 */ u8 unk0[0x6];
    /* 0x06 */ u16 textureIndex;
    /* 0x08 */ u8 unk8[0x4];
    /* 0x0C */ s16 styleCode;
    /* 0x0E */ u8 unkE[0x6];
    /* 0x14 */ s16 x;
    /* 0x16 */ s16 y;
    /* 0x18 */ u8 unk18[0x4];
    /* 0x1C */ u32 scale;
    /* 0x20 */ u8 unk20[0x34];
} TextLayoutFrame;

extern FontMetricsTables lbl_800E8F60;
extern u16 glyphRemapTable[];

extern void fn_80062890(s32);

extern u8 lbl_800E9920[0x3620];
extern void* lbl_803CBBE8;

extern u8 drawStadiumRelated;
extern u8 lbl_800E9908[0x18];
extern u8 lbl_803CB760[8];
extern f32 lbl_803CC490; // 0.0f
extern f32 lbl_803CC494;
extern f32 lbl_803CC498;
extern f32 lbl_803CC49C;
extern u32 lbl_803CB784;
extern u32 lbl_803CB788;
extern u8 lbl_803CB780[4];
extern void fn_800A7D4C(s32 arg0, void* arg1);

void fn_8000F150(s32* arg0) {
    u8* base = (u8*)&lbl_800E8F60;
    GXColor clearColor;
    Mtx44 ortho;
    Mtx trans;
    s32* entry;
    f32 x;
    f32 y;

    clearColor = *(GXColor*)&lbl_803CB784;
    GXSetCopyClear(clearColor, lbl_803CB788);
    C_MTXOrtho(ortho, lbl_803CC490, lbl_803CC494, lbl_803CC490, lbl_803CC498, lbl_803CC490, lbl_803CC49C);

    entry = (s32*)(base + 0x56B0) + arg0[2] * 3;
    x = (u32)(0x280 - 9 * entry[1]) >> 1;
    y = (u32)(0x1C0 - 0x12 * entry[2]) >> 1;
    PSMTXTrans(trans, x, y, lbl_803CC490);
    GXSetProjection(ortho, GX_ORTHOGRAPHIC);
    GXLoadPosMtxImm(trans, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 10);
    GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_TRUE, 0x400, 0x400);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2X4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    SetDisplayStateTexture((TextureBody*)((u8*)lbl_803CBBE8 + (*(u16*)((u8*)lbl_803CBBE8 + 0x20) << 5) + 4), 0, 0);
    GXSetArray(GX_VA_POS, base + 0x3A20, 6);
    GXSetArray(GX_VA_CLR0, lbl_803CB780, 4);
    GXSetArray(GX_VA_TEX0, base + 0x3E60, 4);
    GXCallDisplayList(*(void**)(base + 0x5680 + arg0[2] * 4), *(u32*)(base + 0x56B0 + arg0[2] * 0xC));
    GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_FALSE, 0x400, 0x400);
}

void fn_8000F3E8(s32 arg0) {
    u8* entry = lbl_800E9908 + drawStadiumRelated * 0xC;

    switch (arg0 + 1) {
    case 0:
        *(s32*)(entry + 8) = lbl_803CB760[4];
        break;
    case 5:
        *(s32*)(entry + 8) = lbl_803CB760[1];
        break;
    case 6:
        *(s32*)(entry + 8) = lbl_803CB760[0];
        break;
    case 7:
        *(s32*)(entry + 8) = lbl_803CB760[2];
        break;
    case 12:
        *(s32*)(entry + 8) = lbl_803CB760[3];
        break;
    }
    fn_800A7D4C(0, entry);
}

void somethingSetTexturePointer(void) {
    lbl_803CBBE8 = lbl_800E9920;
    convertTextureHeader(lbl_800E9920);
}

void fn_8000F4B8(int a, int b, int c, int d) {
    screenTextArray.skipFlags = 0;
    if (a >= 0) {
        screenTextArray.skipFlags = 1 << a;
    }
    if (b >= 0) {
        screenTextArray.skipFlags |= 1 << b;
    }
    if (c >= 0) {
        screenTextArray.skipFlags |= 1 << c;
    }
    if (d >= 0) {
        screenTextArray.skipFlags |= 1 << d;
    }
}

void fn_8000F534(TextGraphicsObject* graphics, s32 useFlag) {
    TextLayoutFrame frame;
    u8 frame8[0x50];
    TextChannel* channel;
    s32 i;
    s32 kind;
    s32 kind2;
    s32 small = 0;
    s16 y;
    s16 x;
    u32 color;
    TextureContainerSlot* slot;
    u16 element;

    for (i = 0; i < 30; i++) {
        if (graphics == screenTextArray.channels[i].graphics) {
            break;
        }
    }
    if (i >= 30) {
        return;
    }

    channel = &screenTextArray.channels[i];
    if (useFlag == 0) {
        screenTextArray.blocks[channel->blockIndex].state = 1;
        return;
    }

    screenTextArray.blocks[channel->blockIndex].state = 2;
    slot = &textureContainerSlots[graphics->unk58[0xE]];
    element = *(u16*)&graphics->unk58[0xC];
    fn_8000CEF0(slot->layout, element, 0, channel->unk6, (LayoutFrameInfo*)&frame);
    x = frame.x;
    y = frame.y;

    if (graphics->flags & 8) {
        color = byteWiseMultiply(frame.scale, *(u32*)&graphics->unk58[0]);
    } else {
        color = multBottomBits_asFloat(frame.scale, *(u32*)&graphics->unk58[0]);
    }

    kind = (frame.styleCode * 0x100) / 0x400;
    screenTextArray.blocks[channel->blockIndex].color = color;
    if (kind == 0x10) {
        screenTextArray.blocks[channel->blockIndex].style = 2;
        small = 1;
    } else if (kind == 0x12) {
        screenTextArray.blocks[channel->blockIndex].style = 1;
    } else if (kind == 0x16) {
        screenTextArray.blocks[channel->blockIndex].style = 0;
    } else {
        fn_8000CEF0(slot->layout, frame.textureIndex, 0, 0,
                    (LayoutFrameInfo*)frame8);
        kind2 = (*(s16*)&frame8[0xC] * 0x100) / 0x400;
        if (kind2 < 0x11) {
            screenTextArray.blocks[channel->blockIndex].style = 2;
            small = 1;
        } else if (kind2 < 0x14) {
            screenTextArray.blocks[channel->blockIndex].style = 1;
        } else {
            screenTextArray.blocks[channel->blockIndex].style = 0;
        }
    }

    if (small) {
        screenTextArray.blocks[channel->blockIndex].x = x;
        screenTextArray.blocks[channel->blockIndex].y = y;
    } else {
        screenTextArray.blocks[channel->blockIndex].x = x;
        screenTextArray.blocks[channel->blockIndex].y = y;
    }

    if (fn_8000CEF0(slot->layout, element, 1, channel->unk6, (LayoutFrameInfo*)&frame) != 0) {
        screenTextArray.blocks[channel->blockIndex].unkC =
            multBottomBits_asFloat(frame.scale, *(u32*)&graphics->unk58[0]);
        screenTextArray.blocks[channel->blockIndex].unk14 = frame.x - screenTextArray.blocks[channel->blockIndex].x;
        screenTextArray.blocks[channel->blockIndex].unk16 = frame.y - screenTextArray.blocks[channel->blockIndex].y;
    } else {
        screenTextArray.blocks[channel->blockIndex].unkC = 0;
    }
}

void fn_8000F8F4(void* scene) {
    s32 first;
    s32 i;
    s32 j;
    TextGraphicsObject* graphics;

    first = ((UnkText988Arg*)scene)->unk14;
    for (i = 0; i < ((UnkText988Arg*)scene)->unk16; i++) {
        graphics = graphicsRelatedArray[first + i].object;
        if (graphics != NULL && (graphics->flags & 4)) {
            for (j = 0; j < 30; j++) {
                if (graphics == screenTextArray.channels[j].graphics) {
                    screenTextArray.channels[j].graphics = NULL;
                    break;
                }
            }
        }
    }
}

s32 text_initializeNewChannel(UnkText988Arg* arg0, s32 indexOffset, u16 arg2, s32 arg3, s32 arg4, s32 useFlag8) {
    TextGraphicsObject* graphics;
    s32 i;

    graphics = graphicsRelatedArray[arg0->unk14 + indexOffset].object;
    graphics->flags |= 4;
    if (useFlag8 != 0) {
        graphics->flags |= 8;
    }

    for (i = 0; i < 30; i++) {
        if (screenTextArray.channels[i].graphics == NULL) {
            screenTextArray.channels[i].graphics = graphics;
            screenTextArray.channels[i].unk6 = arg2;
            screenTextArray.channels[i].blockIndex =
                initializeTextParameters(arg3, arg4, 0, 0, graphics->unk67, -1, 0);
            if (graphics->unk0 != 0) {
                screenTextArray.blocks[screenTextArray.channels[i].blockIndex].text = graphics->text;
            } else {
                screenTextArray.blocks[screenTextArray.channels[i].blockIndex].text = NULL;
            }
            return screenTextArray.channels[i].blockIndex;
        }
    }
    return -1;
}

extern u8 lbl_800E90F4[][4];

s32 calculateTextBlockWidth(s32 blockIndex) {
    ScreenText* text;
    u16* str;
    u16* sub;
    s32 digitWidth = 0x16;
    s32 spaceWidth = 0xB;
    s32 maxWidth = 0;
    s32 width = 0;
    s32 fromSub = 0;
    s32 altFont = 0;
    u16** strings;
    u16* bank23;
    u32 glyph;
    s32 code;
    u16 masked;

    text = &screenTextArray.blocks[blockIndex];
    str = text->bankText;
    if (text->style == 2) {
        digitWidth = 0x12;
        spaceWidth = 9;
    } else if (text->style == 1) {
        digitWidth = 0x12;
        spaceWidth = 9;
    }

    bank23 = screenTextArray.glyphBase;
    while (1) {
        strings = screenTextArray.textBanks[0]->strings;
        if (fromSub != 0) {
            glyph = *sub++;
        } else {
            glyph = *str++;
        }
        masked = glyph;
        code = glyph & 0x4000;
        if (code) {
            code = glyph & 0x3FFF;
            switch (code) {
            case 0:
                if (fromSub == 0) {
                    goto done;
                }
                fromSub = 0;
                continue;
            case 2:
                width += spaceWidth;
                break;
            case 3:
                width += digitWidth;
                break;
            case 1:
                width = 0;
                break;
            case 0xF:
            case 0x10:
            case 0x11:
            case 0x12: {
                s32 val = ((s16*)text)[code - 3];
                if (val < 0) {
                    val = -val;
                    width += digitWidth;
                }
                while (1) {
                    if (val < 10) {
                        break;
                    }
                    width += digitWidth;
                    val /= 10;
                }
                break;
            }
            case 0x19:
            case 0x1A:
            case 0x1B:
            case 0x1C:
            case 0x23:
            case 0x24:
            case 0x25:
            case 0x26: {
                s32 n = code - 0xF;
                s32 idx;
                if (n >= 10) {
                    idx = ((s16*)text)[n + 6] + 0x3E;
                } else {
                    idx = ((s16*)text)[n + 0x10] + 8;
                }
                sub = strings[idx];
                fromSub = 1;
                break;
            }
            case 0x2D:
            case 0x2E:
            case 0x2F:
            case 0x30:
            case 0x31:
            case 0x32:
            case 0x33:
            case 0x34:
            case 0x35:
                width += 0x1C;
                width += (s8)text->unk2D;
                break;
            case 0x39:
                altFont = 1;
                break;
            case 0x3A:
                altFont = 0;
                break;
            }
        } else {
            u16 w;
            if (altFont == 0) {
                u16 g;
                u16 base;
                u16 pageIdx;
                s32 row;
                u8 st;
                st = text->style;
                if (masked & 0x8000) {
                    g = glyph & 0x7FFF;
                } else {
                    g = glyphRemapTable[(u16)glyph] & 0x7FFF;
                }
                base = *bank23 & 0x7FFF;
                pageIdx = (u16)g % 0x844;
                row = pageIdx - base - 1;
                w = lbl_800E90F4[row][st];
            } else {
                w = lbl_800E8F60.altWidths[(u16)glyph][text->style];
            }
            width += w;
            width += (s8)text->unk2D;
        }
        if (width > maxWidth) {
            maxWidth = width;
        }
    }
done:
    return maxWidth;
}

void text_setSubstringIndices(s32 blockIndex, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    ScreenText* block = &screenTextArray.blocks[blockIndex];

    block->unk20 = arg1;
    block->unk22 = arg2;
    block->unk24 = arg3;
    block->unk26 = arg4;
}

void text_setInsertedValues(s32 blockIndex, u16 arg1, u16 arg2, u16 arg3, u16 arg4) {
    ScreenText* block = &screenTextArray.blocks[blockIndex];

    block->insertedValues[0] = arg1;
    block->insertedValues[1] = arg2;
    block->insertedValues[2] = arg3;
    block->insertedValues[3] = arg4;
}

void practiceTextRelated(s32 blockIndex, s32 arg1, s32 maxLetters) {
    if (arg1 == 0) {
        screenTextArray.blocks[blockIndex].maxLettersToDraw = -1;
        screenTextArray.blocks[blockIndex].unk31 = 0;
        screenTextArray.blocks[blockIndex].unk32 = 0;
        return;
    }
    if (maxLetters >= 0) {
        screenTextArray.blocks[blockIndex].maxLettersToDraw = maxLetters;
    }
    screenTextArray.blocks[blockIndex].unk31 = arg1;
    screenTextArray.blocks[blockIndex].unk32 = 0;
}

void text_setPtrToWhereCharsAreStored(s32 blockIndex, s32 bankIndex, s32 stringIndex) {
    ScreenText* block = &screenTextArray.blocks[blockIndex];

    block->bankText = screenTextArray.textBanks[bankIndex]->strings[stringIndex];
    if (block->maxLettersToDraw < 0) {
        return;
    }
    block->maxLettersToDraw = 0;
    block->unk34 = 0;
    block->unk35 = 0;
}

void text_freeAllBlocks(void) {
    s32 i;

    for (i = 0; i < 30; i++) {
        screenTextArray.blocks[i].state = 0;
    }
}

void text_freeBlock(s32 blockIndex) {
    screenTextArray.blocks[blockIndex].state = 0;
}

s32 initializeTextParameters(s32 bankIndex, s32 stringIndex, s32 x, s32 y, u8 drawGroup, s32 color, s32 style) {
    ScreenText* block;
    s32 i;

    for (i = 0; i < 30; i++) {
        if (screenTextArray.blocks[i].state == 0) {
            break;
        }
    }

    if (i >= 30) {
        return 0;
    }

    block = &screenTextArray.blocks[i];
    block->bankText = screenTextArray.textBanks[bankIndex]->strings[stringIndex];
    block->x = x;
    block->y = y;
    block->drawGroup = drawGroup;
    block->state = 2;
    block->style = style;
    block->color = color;
    block->insertedValues[0] = 0;
    block->insertedValues[1] = 0;
    block->insertedValues[2] = 0;
    block->insertedValues[3] = 0;
    block->unk2D = 0;
    block->lineSpacing = 2;
    block->justify = 0;
    block->verticalAlign = 0;
    block->text = NULL;
    block->maxLettersToDraw = -1;
    block->unk31 = 0;
    block->unk32 = 0;
    block->unk34 = 0;
    block->unk33 = 0;
    block->unk35 = 0;
    block->unk36 = 0;
    return i;
}

extern f32 lbl_803CBBDC;
extern f32 lbl_803CBBE0;
extern f32 lbl_803CC490; // 0.0f
extern f32 lbl_803CC4A8; // 1.0f

void drawTransformedSprite(s32 x, s32 y, u16 s, u16 t, u16 w, u32 color, s32 style, MtxPtr mtx) {
    Quaternion c3;
    Quaternion c2;
    Quaternion c1;
    Quaternion c0;
    Mtx trans;
    Mtx m;
    SpriteVertex vtx[4];
    Vec* p1;
    Vec* p2;
    Vec* p3;
    s32 h;

    h = 0x16;
    setTextRenderingMode(1);
    if (style >= 10) {
        h = 0x14;
        w = 0x1C;
    } else if (style == 3) {
        h = 0x16;
    } else if (style == 2) {
        h = 0x12;
    } else if (style == 1) {
        h = 0x12;
    }

    if (mtx != NULL) {
        PSMTXTrans(trans, x, y, lbl_803CC490);
        PSMTXConcat(mtx, trans, m);
    } else {
        PSMTXTrans(trans, x - 320, y - 224, lbl_803CC490);
    }

    c0.x = lbl_803CC490;
    c0.y = lbl_803CC490;
    c1.x = c0.x + w;
    c1.y = c0.y;
    c2.x = c0.x;
    c2.y = c0.y + h;
    c3.x = c1.x;
    c3.y = c2.y;
    c0.z = c1.z = c2.z = c3.z = lbl_803CC490;
    p1 = (Vec*)&c1;
    p2 = (Vec*)&c2;
    p3 = (Vec*)&c3;

    if (mtx == NULL) {
        f32 k = lbl_803CBBE0 / lbl_803CBBDC;
        PSMTXScale(m, k, k, lbl_803CC4A8);
        PSMTXConcat(m, trans, m);
    }

    PSMTXMultVec(m, (Vec*)&c0, (Vec*)&c0);
    PSMTXMultVec(m, p1, p1);
    PSMTXMultVec(m, p2, p2);
    PSMTXMultVec(m, p3, p3);

    vtx[0].pos.x = c0.x;
    vtx[0].pos.y = c0.y;
    vtx[1].pos.x = c2.x;
    vtx[1].pos.y = c2.y;
    vtx[2].pos.x = c3.x;
    vtx[2].pos.y = c3.y;
    vtx[3].pos.x = c1.x;
    vtx[3].pos.y = c1.y;
    if (mtx != NULL) {
        vtx[0].pos.z = c0.z;
        vtx[1].pos.z = c2.z;
        vtx[2].pos.z = c3.z;
        vtx[3].pos.z = c1.z;
    } else {
        vtx[0].pos.z = vtx[1].pos.z = vtx[2].pos.z = vtx[3].pos.z = -lbl_803CBBE0;
    }
    vtx[0].color = vtx[1].color = vtx[2].color = vtx[3].color = color;

    if (style < 10) {
        u8 sx = screenTextArray.texCoordScaleX;
        u8 sy = screenTextArray.texCoordScaleY;
        s = s * sx;
        t = t * sy;
        w = w * sx;
        h = h * sy;
    }

    vtx[0].s = vtx[1].s = s;
    vtx[2].s = vtx[3].s = s + w;
    vtx[0].t = vtx[3].t = t;
    vtx[1].t = vtx[2].t = t + h;

    if (style >= 10) {
        vtx[0].s = vtx[1].s = 0;
        vtx[2].s = vtx[3].s = 0x400;
        vtx[0].t = vtx[3].t = 0;
        vtx[1].t = vtx[2].t = 0x400;
        DrawSprite_TexObj(vtx, screenTextArray.textBanks[style + 2], 0x400);
    } else if (style == 3) {
        renderSprite(vtx, screenTextArray.textBanks[11], 0x400, 0x400);
    } else if (style == 2) {
        renderSprite(vtx, screenTextArray.textBanks[10], 0x400, 0x400);
    } else if (style == 1) {
        renderSprite(vtx, screenTextArray.textBanks[9], 0x400, 0x400);
    } else {
        renderSprite(vtx, screenTextArray.textBanks[8], 0x400, 0x400);
    }
}

void DrawText(s32 blockIndex) {
    GameInitVariables* settings;
    u16* str;
    u16* sub;
    s32 spaceWidth;
    s32 fromSub;
    s32 speedOverride;
    s32 lineX;
    s32 digits[5];
    ScreenText* text;
    s32 x;
    s32 y;
    s32 w;
    s32 h;
    s32 style;
    u32 color;
    s32 count;
    s32 letterFlag;
    s16 maxL;
    u32 glyph;
    u16 masked;
    u32 code;
    s32 val;

    text = &screenTextArray.blocks[blockIndex];
    w = 0x16;
    spaceWidth = 0xB;
    h = 0x16;
    count = 0;
    style = 0;
    letterFlag = 1;
    str = text->bankText;
    color = text->color;
    fromSub = 0;
    speedOverride = -1;

    if (text->maxLettersToDraw >= 3) {
        if (((AtBat_ButtonInput1._02 & 0x1100) && (screenTextArray.skipFlags & 1))
         || ((AtBat_ButtonInput1._22 & 0x1100) && (screenTextArray.skipFlags & 2))
         || ((AtBat_ButtonInput1._42 & 0x1100) && (screenTextArray.skipFlags & 4))
         || ((AtBat_ButtonInput1._62 & 0x1100) && (screenTextArray.skipFlags & 8))) {
            text->unk34 = 1;
            text->maxLettersToDraw = 0x2710;
        }
    }

    if (text->style == 2) {
        spaceWidth = 9;
        style = 2;
        w = 0x12;
        h = 0x12;
    } else if (text->style != 0) {
        spaceWidth = 9;
        style = 1;
        w = 0x12;
        h = 0x12;
    }

    lineX = text->x;
    x = lineX;
    y = text->y;
    if (text->justify == 1) {
        s32 bw = calculateTextBlockWidth(blockIndex);
        x = spaceWidth + (lineX - bw / 2);
        lineX = x;
    } else if (text->justify == 2) {
        s32 bw = calculateTextBlockWidth(blockIndex);
        x = w + (lineX - bw);
        lineX = x;
    }

    if (text->verticalAlign == 1) {
        s32 lines = 1;
        u16* p = text->bankText;
        s32 lineH = 0x16;
        s32 total;
        if (text->style == 2) {
            lineH = 0x12;
        } else if (text->style == 1) {
            lineH = 0x12;
        }
        while (1) {
            u32 g = *p++;
            u32 c;
            if (!(g & 0x4000)) continue;
            c = g & 0x3FFF;
            if (c == 0) break;
            if (c == 1) lines++;
        }
        total = lines * lineH;
        if (lines > 1) {
            total += (s8)text->lineSpacing * (lines - 1);
        }
        y = h / 2 + (y - total / 2);
    } else if (text->verticalAlign == 2) {
        s32 lines = 1;
        u16* p = text->bankText;
        s32 lineH = 0x16;
        s32 total;
        if (text->style == 2) {
            lineH = 0x12;
        } else if (text->style == 1) {
            lineH = 0x12;
        }
        while (1) {
            u32 g = *p++;
            u32 c;
            if (!(g & 0x4000)) continue;
            c = g & 0x3FFF;
            if (c == 0) break;
            if (c == 1) lines++;
        }
        total = lines * lineH;
        if (lines > 1) {
            total += (s8)text->lineSpacing * (lines - 1);
        }
        y = (y + total) - h;
    }

    settings = &g_d_GameSettings;

    while (1) {
        maxL = text->maxLettersToDraw;
        if (maxL >= 0 && text->unk34 == 0) {
            if (count > maxL) break;
            speedOverride = -1;
        }
        letterFlag = 1;
        if (fromSub != 0) {
            glyph = *sub++;
        } else {
            glyph = *str++;
        }
        masked = glyph;
        code = glyph & 0x4000;
        if (code) {
            code = glyph & 0x3FFF;
            if (code == 0) {
                if (fromSub != 0) {
                    fromSub = 0;
                    continue;
                }
                text->unk34 = 1;
                letterFlag = 0;
                break;
            }
            if (code >= 0x4B && code <= 0x72) {
                if (text->unk35 == 0) {
                    if (settings->GameModeSelected == GAME_TYPE_CHALLENGE) {
                        fn_80062890(code - 0x39);
                    }
                    text->unk35 = 1;
                }
                letterFlag = 0;
                continue;
            }
            switch (code) {
            case 2:
                x += spaceWidth;
                x += (s8)text->unk2D;
                count++;
                letterFlag = 0;
                break;
            case 3:
                x += w;
                x += (s8)text->unk2D;
                count++;
                letterFlag = 0;
                break;
            case 1:
                y += h;
                x = lineX;
                y += (s8)text->lineSpacing;
                count++;
                letterFlag = 0;
                break;
            case 5: case 6: case 7: case 8: case 9:
            case 0xA: case 0xB: case 0xC: case 0xD: case 0xE: {
                s32 n = code - 5;
                if (n == 0) {
                    color = text->color;
                } else {
                    color = (u8)color | lbl_800E8F60.colors[n];
                }
                letterFlag = 0;
                break;
            }
            case 0xF: case 0x10: case 0x11: case 0x12: {
                s32 i;
                s32* dp;
                s32 v;
                u16 dw;
                val = ((s16*)text)[code - 3];
                if (val < 0) {
                    u16* bank21 = screenTextArray.digitGlyphs;
                    u32 g = bank21[10] & 0x7FFF;
                    u16 cell = (u16)g % 0x844;
                    s32 row = cell / 0x2E;
                    u16 col = cell % 0x2E;
                    u16 s = col * w;
                    u16 t = row * h;
                    val = -val;
                    dw = w;
                    if (text->unkC != 0) {
                        drawTransformedSprite(x + text->unk14, y + text->unk16, s, t, dw, text->unkC, style, (MtxPtr)text->text);
                    }
                    drawTransformedSprite(x, y, s, t, dw, color, style, (MtxPtr)text->text);
                    x += dw;
                    x += (s8)text->unk2D;
                }
                i = 0;
                dp = digits;
                v = val;
                while (1) {
                    *dp = v % 10;
                    if (v < 10) break;
                    v /= 10;
                    dp++;
                    i++;
                }
                dw = w;
                dp = &digits[i];
                while (i >= 0) {
                    u16* bank21 = screenTextArray.digitGlyphs;
                    u32 g = bank21[*dp] & 0x7FFF;
                    u16 cell = (u16)g % 0x844;
                    s32 row = cell / 0x2E;
                    u16 col = cell % 0x2E;
                    u16 s = col * w;
                    u16 t = row * h;
                    if (text->unkC != 0) {
                        drawTransformedSprite(x + text->unk14, y + text->unk16, s, t, dw, text->unkC, style, (MtxPtr)text->text);
                    }
                    drawTransformedSprite(x, y, s, t, dw, color, style, (MtxPtr)text->text);
                    x += dw;
                    count++;
                    dp--;
                    i--;
                    x += (s8)text->unk2D;
                }
                break;
            }
            case 0x19: case 0x1A: case 0x1B: case 0x1C:
            case 0x23: case 0x24: case 0x25: case 0x26: {
                s32 n = code - 0xF;
                s32 idx;
                TextBank* bank0 = screenTextArray.textBanks[0];
                if (n >= 10) {
                    idx = ((s16*)text)[n + 6] + 0x3E;
                } else {
                    idx = ((s16*)text)[n + 0x10] + 8;
                }
                sub = bank0->strings[idx];
                fromSub = 1;
                break;
            }
            case 0x2D: case 0x2E: case 0x2F: case 0x30: case 0x31:
            case 0x32: case 0x33: case 0x34: case 0x35:
                drawTransformedSprite(x, y - 1, 0, 0, 0, color | 0xFFFFFF00, code - 0x23, (MtxPtr)text->text);
                x += 0x1C;
                count++;
                x += (s8)text->unk2D;
                break;
            case 0x37:
                spaceWidth = 0xB;
                w = 0x16;
                h = 0x16;
                style = 3;
                letterFlag = 0;
                break;
            case 0x38: {
                u8 st = text->style;
                if (st == 2) {
                    spaceWidth = 9;
                    w = 0x12;
                    h = 0x12;
                } else if (st != 0) {
                    spaceWidth = 9;
                    w = 0x12;
                    h = 0x12;
                } else {
                    spaceWidth = 0xB;
                    w = 0x16;
                    h = 0x16;
                }
                style = st;
                letterFlag = 0;
                break;
            }
            case 0x39:
                text->unk36 = 1;
                break;
            case 0x3A:
                text->unk36 = 0;
                break;
            case 0x42: case 0x43: case 0x44: case 0x45: case 0x46:
            case 0x47: case 0x48: case 0x49: case 0x4A:
                speedOverride = (code - 0x41) * 10;
                count++;
                letterFlag = 0;
                break;
            }
        } else {
            u16 gw;
            s32 yoff;
            u16 s;
            u16 t;
            if (text->unk36 == 0) {
                u32 g;
                u16* bank23;
                u32 base;
                u16 cell;
                s32 row;
                s32 row2;
                u16 col;
                if (masked & 0x8000) {
                    g = glyph & 0x7FFF;
                } else {
                    g = glyphRemapTable[(u16)glyph] & 0x7FFF;
                }
                bank23 = screenTextArray.glyphBase;
                base = *bank23 & 0x7FFF;
                cell = (u16)g % 0x844;
                row2 = cell - base - 1;
                count++;
                gw = lbl_800E8F60.widths[row2][style];
                yoff = lbl_800E8F60.yOffs[row2][style];
                row = cell / 0x2E;
                col = cell % 0x2E;
                s = col * w;
                t = row * h;
            } else {
                u16 rem;
                s32 row;
                yoff = lbl_800E8F60.altYOffs[(u16)glyph][style];
                gw = lbl_800E8F60.altWidths[(u16)glyph][style];
                count++;
                row = masked / 0x5C;
                rem = masked % 0x5C;
                t = row * h;
                s = spaceWidth * (rem % 2 + (rem & 0xFFFE));
            }
            if (text->unkC != 0) {
                drawTransformedSprite(x + text->unk14, y + (text->unk16 + yoff), s, t, gw, text->unkC, style, (MtxPtr)text->text);
            }
            drawTransformedSprite(x, y + yoff, s, t, gw, color, style, (MtxPtr)text->text);
            x += gw;
            x += (s8)text->unk2D;
        }
    }

    maxL = text->maxLettersToDraw;
    if (maxL >= 0 && maxL < 0x2710) {
        s32 delay = text->unk31;
        if (speedOverride >= 0) {
            delay = speedOverride;
        }
        if (text->unk34 != 0) {
            text->maxLettersToDraw = 0x2710;
            text->unk35 = 1;
        } else if (text->unk32 > delay) {
            text->unk32 = 0;
            if (text->maxLettersToDraw < 0x7FFE) {
                text->maxLettersToDraw++;
            } else {
                text->maxLettersToDraw = 0x7FFF;
            }
            if (letterFlag != 0) {
                if (settings->GameModeSelected == GAME_TYPE_CHALLENGE && text->maxLettersToDraw > 2) {
                    fn_80062890(2);
                }
            }
        } else {
            text->unk32++;
        }
    }
}
