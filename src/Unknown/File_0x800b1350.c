#include "Unknown/File_0x800b1350.h"
#include "Unknown/File_0x800b1500.h"

typedef struct {
    /*0x00*/ u8 _00[8];
    /*0x08*/ u16 arg5;
    /*0x0A*/ u16 arg4;
} SpriteTexObj;

void DrawSprite_TexObj(void* vtx, void* texObj, s32 arg2) {
    DrawSprite(0x80, vtx, 4, texObj, ((SpriteTexObj*)texObj)->arg4, ((SpriteTexObj*)texObj)->arg5);
}
