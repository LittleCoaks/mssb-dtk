#ifndef __TEXT_TEXT_CHANNEL_H_
#define __TEXT_TEXT_CHANNEL_H_

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

// A bank of glyph-string pointers (the game's text data); blocks can only
// point at strings from these banks or at a channel's own graphics text.
typedef struct TextBank {
    /* 0x0 */ u32 unk0;
    /* 0x4 */ u16* strings[1];
} TextBank;

typedef struct ScreenText {
    /* 0x00 */ u16* text;               // override glyph string (set per-channel)
    /* 0x04 */ u16* bankText;           // glyph string taken from a TextBank
    /* 0x08 */ u32 color;               // RGBA
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u16 x;
    /* 0x12 */ u16 y;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ u16 insertedValues[4];   // values spliced in by control codes 0x400F-0x4012
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 maxLettersToDraw;    // -1 = show all
    /* 0x2A */ u8 state;                // 0 = free, 2 = active
    /* 0x2B */ u8 drawGroup;
    /* 0x2C */ u8 style;                // font size: 0 = large, 1/2 = small
    /* 0x2D */ u8 unk2D;
    /* 0x2E */ u8 lineSpacing;
    /* 0x2F */ u8 justify;              // 0 = left, 1 = center, 2 = right
    /* 0x30 */ u8 verticalAlign;
    /* 0x31 */ u8 unk31;
    /* 0x32 */ u8 unk32;
    /* 0x33 */ u8 unk33;
    /* 0x34 */ u8 unk34;
    /* 0x35 */ u8 unk35;
    /* 0x36 */ u8 unk36;
    /* 0x37 */ u8 unk37;
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
    /* 0x780 */ u8 unk780[0x18];
    /* 0x798 */ TextBank* textBanks[25];
    /* 0x7FC */ u8 texCoordScaleX;  // scales glyph pixel coords into 1/0x400 texcoord units
    /* 0x7FD */ u8 texCoordScaleY;
    /* 0x7FE */ u8 skipFlags;      // per-port bitmask: allow button-press text fast-forward
    /* 0x7FF */ u8 pad7FF;
} ScreenTextPool; // size 0x800

typedef struct UnkText988Arg {
    /* 0x00 */ u8 unk0[0x14];
    /* 0x14 */ u16 unk14;
} UnkText988Arg;

extern ScreenTextPool screenTextArray;
extern GraphicsArrayEntry graphicsRelatedArray[];

s32 text_initializeNewChannel(UnkText988Arg* arg0, s32 indexOffset, u16 arg2, s32 arg3, s32 arg4, s32 useFlag8);

#endif // !__TEXT_TEXT_CHANNEL_H_
