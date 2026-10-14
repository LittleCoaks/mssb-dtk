#include "text/text.h"
#include "Dolphin/mtx.h"
#include "Unknown/File_0x800c0770.h"
#include "Unknown/sprt.h"
#include "static/UnknownHomes_Static.h"

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

extern FontMetricsTables lbl_800E8F60;
extern u16 glyphRemapTable[];

extern void fn_80062890(s32);

extern u8 lbl_800E9920[0x3620];
extern void* lbl_803CBBE8;

void somethingSetTexturePointer(void) {
    lbl_803CBBE8 = lbl_800E9920;
    convertTextureHeader(lbl_800E9920);
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
