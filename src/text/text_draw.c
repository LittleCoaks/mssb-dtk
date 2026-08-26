#include "text/text_draw.h"
#include "text/text_channel.h"
#include "text/text_width.h"
#include "text/sprite_draw.h"
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
