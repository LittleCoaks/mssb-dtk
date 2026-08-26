#ifndef __UNKNOWN_FILE_0X8000F988_H_
#define __UNKNOWN_FILE_0X8000F988_H_

#include "mssbTypes.h"

// A renderable object owned by the graphics system; the text engine
// stores per-channel state in it and reads its glyph string at +0xC.
typedef struct TextGraphicsObject {
    /* 0x00 */ u32 unk0;        // nonzero when the object carries text
    /* 0x04 */ u8 unk4[0x8];
    /* 0x0C */ u16 text[0x24];  // glyph string handed to the ScreenText block
    /* 0x54 */ u32 flags;
    /* 0x58 */ u8 unk58[0xF];
    /* 0x67 */ u8 unk67;
} TextGraphicsObject;

typedef struct GraphicsArrayEntry {
    /* 0x0 */ TextGraphicsObject* object;
    /* 0x4 */ u32 unk4;
} GraphicsArrayEntry; // size 0x8

typedef struct ScreenText {
    /* 0x00 */ u16* text;
    /* 0x04 */ u8 unk4[0x34];
} ScreenText; // size 0x38

typedef struct TextChannel {
    /* 0x0 */ TextGraphicsObject* graphics;
    /* 0x4 */ u16 blockIndex;
    /* 0x6 */ u16 unk6;
} TextChannel; // size 0x8

// The 30 ScreenText blocks and the 30-entry channel table live in one
// linker object (screenTextArray, 0x80366B18, size 0x800), so both are
// addressed through this single containing struct.
typedef struct ScreenTextPool {
    /* 0x000 */ ScreenText blocks[30];
    /* 0x690 */ TextChannel channels[30];
    /* 0x780 */ u8 unk780[0x80];
} ScreenTextPool; // size 0x800

typedef struct UnkText988Arg {
    /* 0x00 */ u8 unk0[0x14];
    /* 0x14 */ u16 unk14;
} UnkText988Arg;

extern ScreenTextPool screenTextArray;
extern GraphicsArrayEntry graphicsRelatedArray[];

s32 text_initializeNewChannel(UnkText988Arg* arg0, s32 indexOffset, u16 arg2, s32 arg3, s32 arg4, s32 useFlag8);

#endif // !__UNKNOWN_FILE_0X8000F988_H_
