#ifndef __UNKNOWN_FILE_0X800363D8_H_
#define __UNKNOWN_FILE_0X800363D8_H_

#include "mssbTypes.h"

// What fn_8000CEF0 fills in for one frame of a layout element; only the
// texture index at +0x6 is read so far. The callers' stack frames put the
// size between 0x4C and 0x54 bytes.
typedef struct LayoutFrameInfo {
    /* 0x00 */ u8 _00[0x6];
    /* 0x06 */ u16 textureIndex;
    /* 0x08 */ u8 _08[0x4C];
} LayoutFrameInfo;

u32 fn_8000CEF0(void* layout, u32 element, u32 part, int frame, LayoutFrameInfo* out);
void load_Icon(void *scene, int handle, u32 part, u32 element, int frame);

#endif // !__UNKNOWN_FILE_0X800363D8_H_
