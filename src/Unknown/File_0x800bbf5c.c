#include "Unknown/File_0x800bbf5c.h"

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
