#ifndef __UNKNOWN_FILE_0X8000BA3C_H_
#define __UNKNOWN_FILE_0X8000BA3C_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "Unknown/File_0x80034e20.h"

/* The layout a TextureContainerSlot points at (+0x38), as the UI animation
 * handlers read it. +8 -> element table {u32 count|flags; u32; elem[count]},
 * which the handlers address as raw bytes: element i's pointer is at +8 + i*4. */
typedef struct UILayoutElement {
    /* 0x0 */ u32 flags; // bit 31 = menu/background element
} UILayoutElement;

typedef struct UILayout {
    /* 0x0 */ u8 unk0[0x6];
    /* 0x6 */ u16 unk6;
    /* 0x8 */ u8* elementTable;
} UILayout;

int updateMenuOrBackgroundUI(u32* frame, struct UILayout* layout, int elementIndex, Mtx mtx, u32 arg4, u32 arg5, u32* arg6, s16* path);
s32 updateHUDRelatedUI(u32* frame, struct UILayout* layout, int elementIndex, Mtx mtx, u32 arg4, u32 arg5, u32* arg6, TextureHeader* textures);
s32 triggerDefaultHUDAction(u32* frame, struct UILayout* layout, int elementIndex, Mtx mtx, u32 arg4, u32 arg5, u32* arg6, TextureHeader* textures);
s32 handleUIAction(u32* frame, UILayout* layout, int elementIndex, Mtx mtx, u32 arg4, u32 arg5, u32* arg6,
                    TextureHeader* textures);
void SetSpriteRect(u8* sprite, u8* base, Mtx mtx, s32* vec2i, u16 flagBits);
void AddVec2iToQuad(f32* quad, Mtx mtx, s32* vec2i);

#endif // !__UNKNOWN_FILE_0X8000BA3C_H_
