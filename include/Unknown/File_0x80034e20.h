#ifndef __UNKNOWN_FILE_0X80034E20_H_
#define __UNKNOWN_FILE_0X80034E20_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "Unknown/File_0x800b0a14.h"

/* ---- 2D menu scene graphics ---------------------------------------------
 * Every 2D menu (main menu, Options, Records, the pause screens...) is a set
 * of UI RECORDS in one DOL pool (menuGraphicsStructures, 0x8039C3E0), each
 * naming a LAYOUT ELEMENT inside a loaded texture/layout CONTAINER. A screen
 * is built from a DESCRIPTOR LIST by addGraphicsElementToScene onto a
 * drawing-script node, kept reachable by HANDLE through graphicsRelatedArray
 * (node->firstHandle + handle), animated by maybeProcessUIUpdates stepping a
 * per-record 16.16 frame counter, and freed by node with
 * removeGraphicsElementFromScene (by handle; it never walks children).
 *
 * Layout traced live on GYQE01 by ProjectRio-ASM (Include/Rio/MenuScene.h,
 * docs/menu_scenes.md), as read by maybeProcessUIUpdates (0x80035168) and
 * allocateGraphicsSlot (0x80034F50). The text engine sees the same records
 * as TextGraphicsObject (text/text_channel.h): a text record keeps its glyph
 * string at +0x0C, so +0x0C..+0x48 is element specific. */

typedef struct UIRecord {
    /* 0x00 */ struct UIRecord* parent;     // 0 = top level
    /* 0x04 */ struct UIRecord* next;       // next sibling in the parent's child list
    /* 0x08 */ struct UIRecord* firstChild;
    /* 0x0C */ u8 unkC[0x3C];               // element specific (text records: u16 glyphs[0x24])
    /* 0x48 */ Vec pos;                     // offset in the parent's space
    /* 0x54 */ u32 flags;                   // 0 = free; bit 1 = visible; bit 2 = text record
    /* 0x58 */ u32 rgba;                    // multiplier on the layout's vertex colours
    /* 0x5C */ u32 frame;                   // animation frame, 16.16 fixed
    /* 0x60 */ u32 rate;                    // frames per frame, 16.16 (normally 0x10000)
    /* 0x64 */ u16 elementIndex;            // layout element index in the container
    /* 0x66 */ u8 textureSlot;              // textureContainerSlots index
    /* 0x67 */ u8 layer;                    // draw layer (from the descriptor)
    /* 0x68 */ u8 playMode;                 // UI_PLAY_*
    /* 0x69 */ u8 unk69[0x9];
    /* 0x72 */ s16 anchorSub;               // which of the parent's anchors places this child
    /* 0x74 */ u8 unk74[0x4];
    /* 0x78 */ Mtx anchor;                  // 3x4 matrix the parent's anchor wrote this frame
    /* 0xA8 */ u8 attachedThisFrame;        // set when the parent attached it; cleared after drawing
    /* 0xA9 */ u8 unkA9[0x3];
    /* 0xAC */ u16 textureOverride[10];     // per-part texture override, 0xFFFF = none
} UIRecord; // size 0xC0

#define UI_RECORD_COUNT   864
#define UI_FLAG_VISIBLE   2
#define UI_FLAG_TEXT      4
#define UI_NO_OVERRIDE    0xFFFF

#define UI_PLAY_STOP      0
#define UI_PLAY_FORWARD   1
#define UI_PLAY_BACKWARD  4

/* One record descriptor, as allocateGraphicsSlot reads it. A list ends in a
 * descriptor whose type is 3. parent is a handle in the same list, or 0xFF
 * for a top-level record. mode 0 = visible and stopped, 1 = visible and
 * playing, 2/3 = created hidden. */
typedef struct UIRecordDescriptor {
    /* 0x00 */ u16 type;                    // 3 = end of list
    /* 0x02 */ u16 elementIndex;
    /* 0x04 */ u8 unk4[0x8];
    /* 0x0C */ u32 rgba;                    // 0xFFFFFFFF
    /* 0x10 */ u8 mode;
    /* 0x11 */ u8 layer;
    /* 0x12 */ u16 parent;                  // 0xFF = none
    /* 0x14 */ u8 tag;
    /* 0x15 */ u8 unk15[0x7];
    /* 0x1C */ u16 rate;                    // 1
    /* 0x1E */ s16 anchorSub;
} UIRecordDescriptor; // size 0x20

#define UI_DESC_END       3
#define UI_NO_PARENT      0xFF

/* A texture record inside a loaded container (0x20 bytes each, right after
 * the container's u16 count). Pointers are relocated in RAM. */
typedef struct TextureRecord {
    /* 0x00 */ u16 index;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ void* pixels;
    /* 0x08 */ void* tlut;                  // palette (palette formats only)
    /* 0x0C */ u16 height;
    /* 0x0E */ u16 width;
    /* 0x10 */ u8 unk10[0xB];
    /* 0x1B */ u8 gxFormat;                 // GXTexFmt (8 = C4, 9 = C8, ...)
    /* 0x1C */ u16 tlutEntries;
    /* 0x1E */ u8 tlutFormat;
    /* 0x1F */ u8 unk1F;
} TextureRecord; // size 0x20

typedef struct TextureHeader {
    /* 0x00 */ u16 count;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ TextureRecord records[1];    // count of them (records[i] is at +0x20*i from the header)
} TextureHeader;

/* A loaded container occupies one slot; slots are found by the tag the
 * screen loaded the container under (textureContainerTags). The layout at
 * +0x38: +8 -> element table {u32 count|flags; u32; u32 elem[count]},
 * element -> {u32 nparts|flags; u32; u32 part[nparts]},
 * part -> {u16 count; u16 subSize; sub-records...}. */
typedef struct TextureContainerSlot {
    /* 0x00 */ u8 unk0[0x30];
    /* 0x30 */ void* buffer;
    /* 0x34 */ TextureHeader* textures;
    /* 0x38 */ void* layout;
} TextureContainerSlot; // size 0x3C

#define TEXTURE_SLOT_COUNT 0x14

extern UIRecord menuGraphicsStructures[UI_RECORD_COUNT];        // 0x8039C3E0
extern s16 textureContainerTags[TEXTURE_SLOT_COUNT];             // 0x8023D6C0, -1 = free
extern TextureContainerSlot textureContainerSlots[TEXTURE_SLOT_COUNT]; // 0x803C4BE0

/* maybeProcessUIUpdates draws pool records [uiDrawLoopStart, uiDrawLoopEnd)
 * each frame, then the text pass. Stock values 0 and UI_RECORD_COUNT. */
extern u32 uiDrawLoopStart;   // 0x803CBC98
extern u32 uiDrawLoopEnd;     // 0x803CB814

/* Builds the descriptor list's records on `node` (a DrawingSceneStruct whose
 * firstHandle/handleCount span in graphicsRelatedArray receives them). */
void addGraphicsElementToScene(DrawingSceneStruct* node, const UIRecordDescriptor* descriptors);

#endif // !__UNKNOWN_FILE_0X80034E20_H_
