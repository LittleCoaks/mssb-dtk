#ifndef __TEXT_SPRITE_DRAW_H_
#define __TEXT_SPRITE_DRAW_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

// One vertex of a textured sprite quad: position, RGBA color, and
// texture coordinates in 1/0x400 texture units.
typedef struct SpriteVertex {
    /* 0x00 */ Vec pos;
    /* 0x0C */ u32 color;
    /* 0x10 */ u16 s;
    /* 0x12 */ u16 t;
} SpriteVertex; // size 0x14

void drawTransformedSprite(s32 x, s32 y, u16 s, u16 t, u16 w, u32 color, s32 style, MtxPtr mtx);

#endif // !__TEXT_SPRITE_DRAW_H_
