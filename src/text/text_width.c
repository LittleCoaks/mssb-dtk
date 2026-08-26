#include "text/text_width.h"
#include "text/text_channel.h"

extern u16 lbl_80366218[];
extern u8 lbl_800E8F60[][4];
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

    bank23 = (u16*)screenTextArray.textBanks[23];
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
                    g = lbl_80366218[(u16)glyph] & 0x7FFF;
                }
                base = *bank23 & 0x7FFF;
                pageIdx = (u16)g % 0x844;
                row = pageIdx - base - 1;
                w = lbl_800E90F4[row][st];
            } else {
                w = lbl_800E8F60[(u16)glyph][text->style];
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
