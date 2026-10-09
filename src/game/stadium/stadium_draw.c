#define SQRT2_LINKAGE static
#include "game/stadium/stadium_draw.h"
#include "header_rep_data.h"
#include "game/stadium/stadium_framework.h"
#include "game/ball/collision_primitives.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x80052694.h"
#include "Unknown/File_0x80052734.h"
#include "Unknown/File_0x800a70dc.h"
#include "Unknown/File_0x80035ca4.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/DisplayObject.h"
#include "Dolphin/GX/GXFrameBuffer.h"
#include "Dolphin/gx.h"
#include "Dolphin/mtx.h"
#include "Dolphin/OS/OSCache.h"
#include "C3/control.h"
#include "C3/geoPalette.h"
#include "game/animation/scene_effects.h"
#include "game/stadium/sta_c5.h"
#include "Unknown/File_0x800b4908.h"
#include "Unknown/File_0x800bce38.h"
#include "Unknown/File_0x800b2ac8.h"
#include "Unknown/File_0x800bf038.h"
#include "Unknown/File_0x800bd190.h"
#include "Unknown/File_0x800bfe90.h"
#include "Unknown/File_0x8003a688.h"
#include "text/text_channel.h"

struct {
    void* fanObject;
    u8 _04[20];
} lbl_3_bss_18;
void (*lbl_3_data_A10[2])(Mtx view, int flag, u32 pass) = { 0, 0 };
extern u8 drawStadiumRelated;
extern u8 hugeAnimStruct[];
extern void* fn_80009028(void);
extern void fn_800BCDBC(void* block);
extern const f32 lbl_3_rodata_520;
extern const f32 lbl_3_rodata_538;
extern const f32 lbl_3_rodata_504;
extern const f32 lbl_3_rodata_524;
extern const f32 lbl_3_rodata_528;
extern const f32 lbl_3_rodata_52C;
extern const f32 lbl_3_rodata_530;
extern const GXColor lbl_3_rodata_210;
extern void fn_80023F0C(void* source, void* destination, s32 sourceX, s32 sourceY,
                       s32 width, s32 height, s32 destinationX, s32 destinationY);
extern int checkObjectVisibility(int mode, void* box, MtxPtr matrix);
extern u8 FrameCountOfEntireGame[];
extern u8 lbl_3_common_bss_35154[];
extern const f32 lbl_3_rodata_534;
extern void fn_8003A2C0(void);
extern void fn_8003AE5C(u8 mode);
extern u32 GXGetTexObjHeight(GXTexObj* texture);
typedef struct {
    u32 words[28];
} StadiumRenderEntry;
static inline void copyExtraStadiumEntries(StadiumRenderEntry* source, u8* first,
                                               u8* second, int count) {
    int index;
    for (index = 0; index < count; index++) {
        *(StadiumRenderEntry*)(first + index * 0xE0) = *source;
        *(StadiumRenderEntry*)(second + index * 0xE0) = *source;
    }
}
typedef struct { s16 offsets[7]; } StadiumTextureOffsets;
static const StadiumTextureOffsets stadiumTextureOffsetsSource = {{0x49, 0x95, 0x1DB, 0x121, 0x1B2, 0xFB, 0}};
u32 lbl_3_data_23C[364] = {
    /* 0x000 */ 0xAABED200, 0x42A00000, 0x43E10000, 0xAABED200,
    /* 0x010 */ 0x42A00000, 0x43E10000, 0xAABED200, 0x42A00000,
    /* 0x020 */ 0x43E10000, 0x42200000, 0x3F800000, 0x3F800000,
    /* 0x030 */ 0x0070010A, 0x42A00000, 0x3F800000, 0x3F800000,
    /* 0x040 */ 0x004001C0, 0x42A00000, 0x3F800000, 0x3F800000,
    /* 0x050 */ 0x004001C0, 0x37F403C5, 0x00000000, 0x08800000,
    /* 0x060 */ 0xAABED200, 0x42A00000, 0x43E10000, 0xAABED200,
    /* 0x070 */ 0x42A00000, 0x43E10000, 0xAABED200, 0x42A00000,
    /* 0x080 */ 0x43E10000, 0x42280000, 0x3FC00000, 0x3FC00000,
    /* 0x090 */ 0x0FA001C0, 0x42A00000, 0x3F800000, 0x3F800000,
    /* 0x0A0 */ 0x0F8001C0, 0x42A00000, 0x3F800000, 0x3F800000,
    /* 0x0B0 */ 0x0F5001C0, 0x37F403C5, 0x00000000, 0x08400000,
    /* 0x0C0 */ 0xFFDC9600, 0x00000000, 0x44000000, 0xFFDC9600,
    /* 0x0D0 */ 0x00000000, 0x44000000, 0xFFDC9600, 0x00000000,
    /* 0x0E0 */ 0x44000000, 0x42280000, 0x3FC00000, 0x3FC00000,
    /* 0x0F0 */ 0x0FA001C0, 0x42A00000, 0x3F800000, 0x3F800000,
    /* 0x100 */ 0x0F8001C0, 0x42A00000, 0x3F800000, 0x3F800000,
    /* 0x110 */ 0x0F5001C0, 0x37F403C5, 0x00000000, 0x08750000,
    /* 0x120 */ 0xAABED200, 0x42A00000, 0x43E10000, 0xAABED200,
    /* 0x130 */ 0x42A00000, 0x43E10000, 0xAABED200, 0x42A00000,
    /* 0x140 */ 0x43E10000, 0x42200000, 0x3F800000, 0x3F800000,
    /* 0x150 */ 0x0B7001C0, 0x42A00000, 0x3F800000, 0x3F800000,
    /* 0x160 */ 0x0B4001C0, 0x42A00000, 0x3F800000, 0x3F800000,
    /* 0x170 */ 0x0B4001C0, 0x37F403C5, 0x00000000, 0x08600000,
    /* 0x180 */ 0x96AADC02, 0x42A00000, 0x43960000, 0x96AADC02,
    /* 0x190 */ 0x42A00000, 0x43960000, 0x96AADC02, 0x42A00000,
    /* 0x1A0 */ 0x43960000, 0x42200000, 0x3F800000, 0x3F800000,
    /* 0x1B0 */ 0x0B7001C0, 0x42A00000, 0x3F800000, 0x3F800000,
    /* 0x1C0 */ 0x0B4001C0, 0x42A00000, 0x3F800000, 0x3F800000,
    /* 0x1D0 */ 0x0B4001C0, 0x00000000, 0x00FFFF00, 0x08600000,
    /* 0x1E0 */ 0xAABED207, 0x00000000, 0x43BE0000, 0xAABED207,
    /* 0x1F0 */ 0x00000000, 0x43BE0000, 0xAABED207, 0x00000000,
    /* 0x200 */ 0x43BE0000, 0x42480000, 0x3F800000, 0x3F800000,
    /* 0x210 */ 0x0B8001C0, 0x42480000, 0x3F800000, 0x3F800000,
    /* 0x220 */ 0x008001C0, 0x42480000, 0x3F800000, 0x3F800000,
    /* 0x230 */ 0x0B8001C0, 0x392B92A6, 0x00000000, 0x08480000,
    /* 0x240 */ 0xAABED200, 0x42A00000, 0x43E10000, 0xAABED200,
    /* 0x250 */ 0x42A00000, 0x43E10000, 0xAABED200, 0x42A00000,
    /* 0x260 */ 0x43E10000, 0x42200000, 0x3F800000, 0x3F800000,
    /* 0x270 */ 0x0070010A, 0x42A00000, 0x3F800000, 0x3F800000,
    /* 0x280 */ 0x004001C0, 0x42A00000, 0x3F800000, 0x3F800000,
    /* 0x290 */ 0x004001C0, 0x37F403C5, 0x00000000, 0x08800000,
    /* 0x2A0 */ 0xAABED200, 0x42A00000, 0x43E10000, 0xAABED200,
    /* 0x2B0 */ 0x42A00000, 0x43E10000, 0xAABED200, 0x42A00000,
    /* 0x2C0 */ 0x43E10000, 0x42200000, 0x3F800000, 0x3F800000,
    /* 0x2D0 */ 0x0070010A, 0x42A00000, 0x3F800000, 0x3F800000,
    /* 0x2E0 */ 0x004001C0, 0x42A00000, 0x3F800000, 0x3F800000,
    /* 0x2F0 */ 0x004001C0, 0x37F403C5, 0x00000000, 0x08800000,
    /* 0x300 */ 0xAABED200, 0x42A00000, 0x43E10000, 0xAABED200,
    /* 0x310 */ 0x42A00000, 0x43E10000, 0xAABED200, 0x42A00000,
    /* 0x320 */ 0x43E10000, 0x42280000, 0x3FC00000, 0x3FC00000,
    /* 0x330 */ 0x0FA001C0, 0x42A00000, 0x3F800000, 0x3F800000,
    /* 0x340 */ 0x0F8001C0, 0x42A00000, 0x3F800000, 0x3F800000,
    /* 0x350 */ 0x0F5001C0, 0x37F403C5, 0x00000000, 0x08400000,
    /* 0x360 */ 0xFFDC9600, 0x00000000, 0x44000000, 0xFFDC9600,
    /* 0x370 */ 0x00000000, 0x44000000, 0xFFDC9600, 0x00000000,
    /* 0x380 */ 0x44000000, 0x42280000, 0x3FC00000, 0x3FC00000,
    /* 0x390 */ 0x0FA001C0, 0x42A00000, 0x3F800000, 0x3F800000,
    /* 0x3A0 */ 0x0F8001C0, 0x42A00000, 0x3F800000, 0x3F800000,
    /* 0x3B0 */ 0x0F5001C0, 0x37F403C5, 0x00000000, 0x08750000,
    /* 0x3C0 */ 0xAABED200, 0x42A00000, 0x43E10000, 0xAABED200,
    /* 0x3D0 */ 0x42A00000, 0x43E10000, 0xAABED200, 0x42A00000,
    /* 0x3E0 */ 0x43E10000, 0x42200000, 0x3F800000, 0x3F800000,
    /* 0x3F0 */ 0x0B7001C0, 0x42A00000, 0x3F800000, 0x3F800000,
    /* 0x400 */ 0x0B4001C0, 0x42A00000, 0x3F800000, 0x3F800000,
    /* 0x410 */ 0x0B4001C0, 0x37F403C5, 0x00000000, 0x08600000,
    /* 0x420 */ 0x96AADC02, 0x42A00000, 0x43960000, 0x96AADC02,
    /* 0x430 */ 0x42A00000, 0x43960000, 0x96AADC02, 0x42A00000,
    /* 0x440 */ 0x43960000, 0x42200000, 0x3F800000, 0x3F800000,
    /* 0x450 */ 0x0B7001C0, 0x42A00000, 0x3F800000, 0x3F800000,
    /* 0x460 */ 0x0B4001C0, 0x42A00000, 0x3F800000, 0x3F800000,
    /* 0x470 */ 0x0B4001C0, 0x00000000, 0x00FFFF00, 0x08600000,
    /* 0x480 */ 0xAABED207, 0x00000000, 0x43BE0000, 0xAABED207,
    /* 0x490 */ 0x00000000, 0x43BE0000, 0xAABED207, 0x00000000,
    /* 0x4A0 */ 0x43BE0000, 0x42480000, 0x3F800000, 0x3F800000,
    /* 0x4B0 */ 0x0B8001C0, 0x42480000, 0x3F800000, 0x3F800000,
    /* 0x4C0 */ 0x008001C0, 0x42480000, 0x3F800000, 0x3F800000,
    /* 0x4D0 */ 0x0B8001C0, 0x392B92A6, 0x00000000, 0x08480000,
    /* 0x4E0 */ 0xAABED200, 0x42A00000, 0x43E10000, 0xAABED200,
    /* 0x4F0 */ 0x42A00000, 0x43E10000, 0xAABED200, 0x42A00000,
    /* 0x500 */ 0x43E10000, 0x42200000, 0x3F800000, 0x3F800000,
    /* 0x510 */ 0x0070010A, 0x42A00000, 0x3F800000, 0x3F800000,
    /* 0x520 */ 0x004001C0, 0x42A00000, 0x3F800000, 0x3F800000,
    /* 0x530 */ 0x004001C0, 0x37F403C5, 0x00000000, 0x08800000,
    /* 0x540 */ 0xAABED200, 0x42A00000, 0x43E10000, 0xAABED200,
    /* 0x550 */ 0x42A00000, 0x43E10000, 0xAABED200, 0x42A00000,
    /* 0x560 */ 0x43E10000, 0x42200000, 0x3F800000, 0x3F800000,
    /* 0x570 */ 0x0070010A, 0x42A00000, 0x3F800000, 0x3F800000,
    /* 0x580 */ 0x004001C0, 0x42A00000, 0x3F800000, 0x3F800000,
    /* 0x590 */ 0x004001C0, 0x37F403C5, 0x00000000, 0x08800000,
    /* 0x5A0 */ 0x00000002, (u32)fn_3_3818, 0x00000002, (u32)fn_3_3818,
};

u8 StadiumFiles_game[21][16] = {
    { 0x00, 0x00, 0x04, 0x0B, 0x40, 0x16, 0x8A, 0x6C, 0x06, 0xCF, 0xD0, 0x00, 0x00, 0x0C, 0x69, 0xA8 },
    { 0x00, 0x00, 0x04, 0x0B, 0x40, 0x13, 0x31, 0xE0, 0x06, 0xDC, 0x40, 0x00, 0x00, 0x0B, 0x67, 0xC4 },
    { 0x00, 0x00, 0x04, 0x0B, 0x40, 0x11, 0x92, 0x4C, 0x06, 0xE7, 0xA8, 0x00, 0x00, 0x0A, 0x57, 0x64 },
    { 0x00, 0x00, 0x04, 0x0B, 0x40, 0x0F, 0xBA, 0xE0, 0x06, 0xF2, 0x00, 0x00, 0x00, 0x0B, 0xE0, 0x38 },
    { 0x00, 0x00, 0x04, 0x0B, 0x40, 0x0E, 0x5A, 0xC0, 0x06, 0xFD, 0xE8, 0x00, 0x00, 0x0B, 0x4F, 0xB8 },
    { 0x00, 0x00, 0x04, 0x0B, 0x40, 0x13, 0x12, 0x00, 0x07, 0x09, 0x38, 0x00, 0x00, 0x0A, 0x31, 0x7C },
    { 0x00, 0x00, 0x04, 0x0B, 0x40, 0x11, 0xB6, 0x60, 0x07, 0x13, 0x70, 0x00, 0x00, 0x0D, 0x02, 0x94 },
    { 0x00, 0x00, 0x04, 0x0B, 0x40, 0x11, 0xB6, 0x60, 0x07, 0x13, 0x70, 0x00, 0x00, 0x0D, 0x02, 0x94 },
    { 0x00, 0x00, 0x04, 0x0B, 0x40, 0x11, 0xB6, 0x60, 0x07, 0x13, 0x70, 0x00, 0x00, 0x0D, 0x02, 0x94 },
    { 0x00, 0x00, 0x04, 0x0B, 0x40, 0x14, 0x1C, 0x60, 0x07, 0x20, 0x78, 0x00, 0x00, 0x0C, 0xE9, 0x04 },
    { 0x00, 0x00, 0x04, 0x0B, 0x40, 0x13, 0xCA, 0x40, 0x07, 0x2D, 0x68, 0x00, 0x00, 0x0C, 0xA5, 0x60 },
    { 0x00, 0x00, 0x04, 0x0B, 0x40, 0x14, 0x1C, 0x60, 0x07, 0x20, 0x78, 0x00, 0x00, 0x0C, 0xE9, 0x04 },
    { 0x00, 0x00, 0x04, 0x0B, 0x40, 0x16, 0xC1, 0x38, 0x07, 0x3A, 0x10, 0x00, 0x00, 0x0E, 0xD4, 0x1C },
    { 0x00, 0x00, 0x04, 0x0B, 0x40, 0x11, 0x57, 0xB8, 0x07, 0x48, 0xE8, 0x00, 0x00, 0x0C, 0xA8, 0x3C },
    { 0x00, 0x00, 0x04, 0x0B, 0x40, 0x16, 0xC1, 0x38, 0x07, 0x3A, 0x10, 0x00, 0x00, 0x0E, 0xD4, 0x1C },
    { 0x00, 0x00, 0x04, 0x0B, 0x40, 0x0E, 0xB1, 0xC0, 0x07, 0x55, 0x98, 0x00, 0x00, 0x0A, 0x35, 0x10 },
    { 0x00, 0x00, 0x04, 0x0B, 0x40, 0x0E, 0xB1, 0xC0, 0x07, 0x55, 0x98, 0x00, 0x00, 0x0A, 0x35, 0x10 },
    { 0x00, 0x00, 0x04, 0x0B, 0x40, 0x0E, 0xB1, 0xC0, 0x07, 0x55, 0x98, 0x00, 0x00, 0x0A, 0x35, 0x10 },
    { 0x00, 0x00, 0x04, 0x0B, 0x40, 0x0D, 0x04, 0xE0, 0x07, 0x5F, 0xD0, 0x00, 0x00, 0x08, 0x73, 0x90 },
    { 0x00, 0x00, 0x04, 0x0B, 0x40, 0x0D, 0x04, 0xE0, 0x07, 0x5F, 0xD0, 0x00, 0x00, 0x08, 0x73, 0x90 },
    { 0x00, 0x00, 0x04, 0x0B, 0x40, 0x0D, 0x04, 0xE0, 0x07, 0x5F, 0xD0, 0x00, 0x00, 0x08, 0x73, 0x90 },
};

u32 lbl_3_data_93C[53] = {
    0x00000002,
    (u32)fn_3_5C68,
    0x00000000,
    0x00000000,
    0x00000002,
    (u32)fn_3_5C68,
    0x00000000,
    0x00000000,
    0xFFFFFF0A,
    0x00000002,
    (u32)fn_3_5BF0,
    0x00000002,
    (u32)fn_3_5BF0,
    0x00000002,
    (u32)fn_3_5BF0,
    0x00000002,
    (u32)fn_3_5BF0,
    0x00000002,
    (u32)fn_3_5BF0,
    0x00000002,
    (u32)fn_3_5BF0,
    0x00000002,
    (u32)fn_3_5BF0,
    0x00000002,
    (u32)fn_3_5BF0,
    0x00000002,
    (u32)fn_3_5BF0,
    0x00000000,
    (u32)fn_3_5BF0,
    0x00000002,
    (u32)fn_3_5BCC,
    0x00000000,
    0x00000002,
    (u32)fn_3_5BCC,
    0x00000000,
    0x00000002,
    (u32)fn_3_5BCC,
    0x00000001,
    0x00000002,
    (u32)fn_3_5BCC,
    0x00000001,
    0x00000002,
    (u32)fn_3_5BCC,
    0x00000002,
    0x00000002,
    (u32)fn_3_5BCC,
    0x00000002,
    0x00000002,
    (u32)fn_3_5BCC,
    0x00000003,
    0x00000002,
    (u32)fn_3_5BCC,
    0x00000003,
};

#define STADIUM_ATLAS_SKIP_FLAG 0x4000
#define STADIUM_ATLAS_PAGED_FLAG 0x8000
#define STADIUM_ATLAS_COLUMNS 46
#define STADIUM_ATLAS_CELL_SIZE 22
#define STADIUM_ATLAS_HALF_CELL_SIZE 11
#define STADIUM_ATLAS_CELLS_PER_PAGE (STADIUM_ATLAS_COLUMNS * STADIUM_ATLAS_COLUMNS)
#define STADIUM_ATLAS_HALF_COLUMNS (STADIUM_ATLAS_COLUMNS * 2)

typedef struct {
    void* pixels;
    u8 _04[4];
    u16 width;
    u16 height;
} StadiumTextureBuffer;

typedef struct {
    void* source;
    StadiumTextureBuffer* destination;
    u8* tileMap;
    u8* tileIndex;
    u8* animationState;
    u16 tileCount;
    u16 resetFrames;
    u16 frameCount;
} StadiumAnimatedTexture;

typedef struct {
    u8 _00[8];
    StadiumAnimatedTexture* slots[3];
} StadiumAnimatedTexturePair;

void fn_3_35F0(void) {
    if (fn_80009028() == 0) {
        GXColor clearColor = *(GXColor*)((u8*)&g_UNK_StadiumDetails + 0x76C);
        GXSetCopyClear(clearColor, 0xFFFFFF);
    }
}

// .text:0x00003904 size:0x2E4 mapped:0x80642998
void fn_3_3904(int x, int y, int textIndex, const GXColor* foreground,
                  const GXColor* background, u8 alternate) {
    u16* text = screenTextArray.textBanks[0]->strings[textIndex];
    GXTexObj texture;
    int cursorY = y;
    int cursorX = x;
    int value;
    for (;;) {
        value = *text++;
        if (value & STADIUM_ATLAS_SKIP_FLAG) {
            switch (value & 0x3FFF) {
            case 0:
                return;
            case 1:
                cursorX = x;
                cursorY += 22;
                break;
            case 2:
                cursorX += 11;
                break;
            case 3:
                cursorX += 22;
                break;
            default:
                break;
            }
            continue;
        }
        {
            s16 column, row, cellWidth, cellHeight;
            f32 drawWidth;
            f32 drawHeight;
            if (value & STADIUM_ATLAS_PAGED_FLAG) {
                u16 cell = (value & 0x7FFF) % STADIUM_ATLAS_CELLS_PER_PAGE;
                column = cell % STADIUM_ATLAS_COLUMNS;
                row = (cell / STADIUM_ATLAS_COLUMNS) * STADIUM_ATLAS_CELL_SIZE;
                column *= STADIUM_ATLAS_CELL_SIZE;
                cellWidth = 22;
                cellHeight = 22;
                drawWidth = 16.0f;
                drawHeight = 18.0f;
            } else {
                column = value % STADIUM_ATLAS_HALF_COLUMNS;
                row = (value / STADIUM_ATLAS_HALF_COLUMNS) * 22;
                column = ((column / 2) * 2 + column % 2) * 11;
                cellWidth = 11;
                cellHeight = 22;
                drawWidth = 8.0f;
                drawHeight = 18.0f;
            }
            GXInitTexObjLOD(&texture, 1, 1, 0.0f, 0.0f, 0.0f, FALSE, FALSE, 0);
            fn_3_42CC(&texture, cursorX, cursorY,
                         (s16)((f32)(s16)cursorX + drawWidth),
                         (s16)((f32)(s16)cursorY + drawHeight),
                         column, row, cellWidth, cellHeight,
                         *foreground, *background, alternate & 1);
            cursorX = (s16)((f32)(s16)cursorX + drawWidth);
        }
    }
}

// .text:0x00003BE8 size:0x300 mapped:0x80642C7C
void fn_3_3BE8(void* textureRecord, s16 left, s16 top, s16 right, s16 bottom,
                  s16 textureX, s16 textureY, s16 textureWidth, s16 textureHeight) {
    u8* record = (u8*)textureRecord;
    GXTexObj texture;
    GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    volatile f32* position = (volatile f32*)0xCC008000;
    volatile u16* uv = (volatile u16*)0xCC008000;
    f32 x0 = left;
    f32 y0 = top;
    f32 x1 = right;
    f32 y1 = bottom;
    GXInitTexObj(&texture, *(void**)record, *(u16*)(record + 0xA), *(u16*)(record + 8),
                    0, 0, 0, FALSE);
    GXInitTexObjLOD(&texture, 1, 1, 0.0f, 0.0f, 0.0f, FALSE, FALSE, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(13, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 13, 1, 3, 9);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTevColor(1, white);
    GXSetTevColorIn(0, 15, 15, 15, 8);
    GXSetTevAlphaIn(0, 7, 7, 7, 1);
    GXSetTevColorOp(0, 0, 0, 0, 0, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetBlendMode(1, 4, 5, 7);
    GXLoadTexObj(&texture, 0);
    GXBegin(GX_QUADS, 0, 4);
    *position = x0; *position = y0; *position = -0.5f;
    *uv = textureX; *uv = textureY;
    *position = x1; *position = y0; *position = -0.5f;
    *uv = textureX + textureWidth; *uv = textureY;
    *position = x1; *position = y1; *position = -0.5f;
    *uv = textureX + textureWidth; *uv = textureY + textureHeight;
    *position = x0; *position = y1; *position = -0.5f;
    *uv = textureX; *uv = textureY + textureHeight;
}

// .text:0x00003EE8 size:0x3E4 mapped:0x80642F7C
void fn_3_3EE8(void* textureRecord, s16 left, s16 top, s16 right, s16 bottom,
                  s16 textureX, s16 textureY, s16 textureWidth, s16 textureHeight) {
    u8* record = (u8*)textureRecord;
    GXTexObj texture;
    GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    volatile f32* fifo = (volatile f32*)0xCC008000;
    f32 x0 = left;
    f32 y0 = top;
    f32 x1 = right;
    f32 y1 = bottom;
    f32 u0 = (f32)textureX / *(u16*)(record + 0xA);
    f32 v0 = (f32)textureY / *(u16*)(record + 8);
    f32 u1 = (f32)(textureX + textureWidth) / *(u16*)(record + 0xA);
    f32 v1 = (f32)(textureY + textureHeight) / *(u16*)(record + 8);
    GXInitTexObj(&texture, *(void**)record, *(u16*)(record + 0xA), *(u16*)(record + 8),
                    0, 0, 0, FALSE);
    GXInitTexObjLOD(&texture, 0, 0, 0.0f, 0.0f, 0.0f, FALSE, FALSE, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(13, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 13, 1, 4, 0);
    GXSetChanCtrl(4, 0, 0, 0, 0, 0, 2);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevColor(1, white);
    GXSetTevColorIn(0, 15, 15, 15, 8);
    GXSetTevAlphaIn(0, 7, 7, 7, 1);
    GXSetTevColorOp(0, 0, 0, 0, 0, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetBlendMode(0, 4, 5, 7);
    GXLoadTexObj(&texture, 0);
    GXBegin(GX_QUADS, 0, 4);
    *fifo = x0; *fifo = y0; *fifo = -0.5f; *fifo = u0; *fifo = v0;
    *fifo = x1; *fifo = y0; *fifo = -0.5f; *fifo = u1; *fifo = v0;
    *fifo = x1; *fifo = y1; *fifo = -0.5f; *fifo = u1; *fifo = v1;
    *fifo = x0; *fifo = y1; *fifo = -0.5f; *fifo = u0; *fifo = v1;
}

// .text:0x000042CC size:0x6B8 mapped:0x80643360
void fn_3_42CC(GXTexObj* texture, s16 left, s16 top, s16 right, s16 bottom,
                  s16 textureX, s16 textureY, s16 textureWidth, s16 textureHeight,
                  GXColor foreground, GXColor background, u8 alternate) {
    volatile f32* fifo = (volatile f32*)0xCC008000;
    f32 x0 = left;
    f32 y0 = top;
    f32 x1 = right;
    f32 y1 = bottom;
    u32 texWidth = GXGetTexObjWidth(texture);
    u32 texHeight = GXGetTexObjHeight(texture);
    f32 u0 = (f32)textureX / texWidth;
    f32 v0 = (f32)textureY / texHeight;
    f32 u1 = (f32)(textureX + textureWidth) / texWidth;
    f32 v1 = (f32)(textureY + textureHeight) / texHeight;

    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetTevColor(1, foreground);
    GXSetTevColor(2, background);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    if (alternate & 1) {
        GXSetTevColorIn(0, 15, 12, 2, 4);
    } else {
        GXSetTevColorIn(0, 15, 15, 2, 4);
    }
    GXSetTevAlphaIn(0, 7, 7, 7, 1);
    GXSetTevColorOp(0, 0, 0, 0, 0, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
    GXSetTevOrder(0, 0xFF, 0xFF, 4);
    GXSetBlendMode(1, 4, 5, 7);
    GXBegin(GX_QUADS, 0, 4);
    *fifo = x0 - 1.0f; *fifo = y0 - 1.0f; *fifo = -0.5f;
    *fifo = x1 + 1.0f; *fifo = y0 - 1.0f; *fifo = -0.5f;
    *fifo = x1 + 1.0f; *fifo = y1 + 1.0f; *fifo = -0.5f;
    *fifo = x0 - 1.0f; *fifo = y1 + 1.0f; *fifo = -0.5f;

    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(13, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 13, 1, 4, 0);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetNumTevStages(2);
    if (alternate & 1) {
        GXSetTevColorIn(0, 15, 8, 9, 12);
        GXSetTevAlphaIn(0, 7, 7, 7, 1);
        GXSetTevColorOp(0, 1, 0, 0, 0, 0);
        GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
        GXSetTevColorIn(1, 15, 0, 2, 4);
        GXSetTevAlphaIn(1, 7, 7, 7, 1);
        GXSetTevColorOp(1, 0, 0, 0, 0, 0);
        GXSetTevAlphaOp(1, 0, 0, 0, 0, 0);
    } else {
        GXSetTevColorIn(0, 15, 8, 9, 15);
        GXSetTevAlphaIn(0, 7, 7, 7, 1);
        GXSetTevColorOp(0, 0, 0, 0, 0, 0);
        GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
        GXSetTevColorIn(1, 15, 0, 2, 4);
        GXSetTevAlphaIn(1, 7, 7, 7, 1);
        GXSetTevColorOp(1, 0, 0, 0, 0, 0);
        GXSetTevAlphaOp(1, 0, 0, 0, 0, 0);
    }
    GXLoadTexObj(texture, 0);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetTevOrder(1, 0xFF, 0xFF, 4);
    GXSetBlendMode(1, 4, 5, 7);
    GXBegin(GX_QUADS, 0, 4);
    *fifo = x0; *fifo = y0; *fifo = -0.5f; *fifo = u0; *fifo = v0;
    *fifo = x1; *fifo = y0; *fifo = -0.5f; *fifo = u1; *fifo = v0;
    *fifo = x1; *fifo = y1; *fifo = -0.5f; *fifo = u1; *fifo = v1;
    *fifo = x0; *fifo = y1; *fifo = -0.5f; *fifo = u0; *fifo = v1;
}

// .text:0x00004984 size:0xB4 mapped:0x80643A18
void fn_3_4984(void) {
    Mtx identity;
    Mtx44 projection;
    GXSetZMode(TRUE, GX_ALWAYS, TRUE);
    GXSetScissor(0, 0, 640, 448);
    C_MTXOrtho(projection, lbl_3_rodata_504, lbl_3_rodata_524,
               lbl_3_rodata_504, lbl_3_rodata_528,
               lbl_3_rodata_52C, lbl_3_rodata_530);
    GXSetProjection(projection, GX_ORTHOGRAPHIC);
    GXSetCullMode(GX_CULL_NONE);
    PSMTXIdentity(identity);
    GXLoadPosMtxImm(identity, 0);
    GXSetCurrentMtx(0);
}

// .text:0x00004A38 size:0x558 mapped:0x80643ACC
void inningScoreDisplayRelated(int stadiumID) {
    GXColor colors[7][2] = {
        {{0x66, 0x66, 0x66, 0xFF}, {0, 0, 0, 0xFF}},
        {{0x66, 0x66, 0x66, 0xFF}, {0, 0, 0, 0xFF}},
        {{0x66, 0x66, 0x66, 0xFF}, {0, 0, 0, 0xFF}},
        {{0x66, 0x66, 0x66, 0xFF}, {0, 0, 0, 0xFF}},
        {{0x66, 0x66, 0x66, 0xFF}, {0, 0, 0, 0xFF}},
        {{0x66, 0x66, 0x66, 0xFF}, {0, 0, 0, 0xFF}},
        {{0x66, 0x66, 0x66, 0xFF}, {0, 0, 0, 0xFF}},
    };
    s16 firstInning[8] = {10, 9, 0, 0, 0, 0, 0, 0};
    s16 topInnings[7][2] = {{28, 192}, {18, 138}};
    s16 bottomInnings[7][2] = {{28, 214}, {18, 159}};
    s16 topTotal[7][2] = {{250, 192}, {180, 138}};
    s16 bottomTotal[7][2] = {{250, 214}, {180, 159}};
    s16 inningStep[7][2] = {{22, 18}, {18, 18}};
    u8 digitSlots[8] = {1, 1};
    GXTexObj texture;
    int stadium = (u8)stadiumID;
    int inning;
    int firstVisibleInning;
    int offset = 0;
    int lastInning;

    GXInitTexObjLOD(&texture, 1, 1, 0.0f, 0.0f, 0.0f, FALSE, FALSE, 0);
    lastInning = g_Scores.Inning;
    firstVisibleInning = firstInning[stadium] + 1;
    if (lastInning < firstVisibleInning) {
        firstVisibleInning = 1;
    }
    inning = firstVisibleInning;
    while (inning <= lastInning) {
        s16 runs = g_Scores.scores[0].byInning[inning - 1];
        if (inning == lastInning && runs == 0 && g_Scores.halfInning == 0 && ((u8*)&g_GameLogic)[0x127] == 0) {
            break;
        }
        fn_3_4F90(&texture, topInnings[stadium][0] + offset,
                     topInnings[stadium][1], runs, 1,
                     colors[stadium][0], colors[stadium][1], 0);
        offset += inningStep[stadium][0];
        inning++;
    }
    fn_3_4F90(&texture, topTotal[stadium][0], topTotal[stadium][1],
                 g_Scores.scores[0].total, digitSlots[stadium],
                 colors[stadium][0], colors[stadium][1], 0);

    if (((u8*)&g_GameLogic)[0x127] == 0) {
        lastInning = g_Scores.Inning + g_Scores.halfInning;
    } else {
        lastInning = g_Scores.inningLimit + 1;
    }
    offset = 0;
    inning = firstVisibleInning;
    while (inning < lastInning) {
        s16 runs = g_Scores.scores[1].byInning[inning - 1];
        int outline = 0;
        if (inning >= g_Scores.inningLimit && g_Scores.scores[1].total > runs) {
            outline = 1;
        }
        if (inning == g_Scores.Inning && runs == 0 && outline == 0 && ((u8*)&g_GameLogic)[0x127] == 0) {
            break;
        }
        fn_3_4F90(&texture, bottomInnings[stadium][0] + offset,
                     bottomInnings[stadium][1], runs, 1,
                     colors[stadium][0], colors[stadium][1], outline);
        offset += inningStep[stadium][0];
        inning++;
    }
    fn_3_4F90(&texture, bottomTotal[stadium][0], bottomTotal[stadium][1],
                 g_Scores.scores[1].total, digitSlots[stadium],
                 colors[stadium][0], colors[stadium][1], 0);
}

// .text:0x00004F90 size:0x450 mapped:0x80644024
void fn_3_4F90(GXTexObj* texture, s16 x, s16 y, s16 value, u8 digitSlots,
                  GXColor foreground, GXColor background, u8 outline) {
    u16** digits = screenTextArray.textBanks[0]->strings;
    int count;
    s16 width;
    s16 cursor;
    int drawn;
    if (value > 99) {
        value = 99;
    }
    count = value >= 10 ? 2 : 1;
    if (outline != 0 && value != 0) {
        count++;
    }
    width = digitSlots < count ? digitSlots * 16 / count : 16;
    cursor = x + digitSlots * 16 - width;
    if (outline != 0) {
        volatile f32* fifo = (volatile f32*)0xCC008000;
        GXClearVtxDesc();
        GXSetTevColor(1, foreground);
        GXSetVtxDesc(9, 1);
        GXSetVtxAttrFmt(0, 9, 1, 4, 0);
        GXSetTevColorIn(0, 15, 15, 2, 2);
        GXSetTevAlphaIn(0, 7, 7, 7, 1);
        GXSetTevOrder(0, 0xFF, 0xFF, 4);
        GXSetNumTexGens(0);
        GXSetNumChans(1);
        GXSetNumTevStages(1);
        GXSetLineWidth(18, 0);
        GXBegin(GX_LINES, 0, 4);
        *fifo = cursor; *fifo = y; *fifo = -0.5f;
        *fifo = cursor + width; *fifo = y; *fifo = -0.5f;
        *fifo = cursor + width; *fifo = y + 18; *fifo = -0.5f;
        *fifo = cursor; *fifo = y + 18; *fifo = -0.5f;
        GXSetLineWidth(18, 0);
        cursor -= width;
        count--;
    }
    for (drawn = 0; drawn < count; drawn++) {
        u16 glyph = *digits[value % 10];
        if ((glyph & STADIUM_ATLAS_SKIP_FLAG) == 0) {
            s16 column, row, cellWidth, cellHeight, page;
            fn_3_53E0(&glyph, &column, &row, &cellWidth, &cellHeight, &page);
            fn_3_42CC(texture, cursor, y, cursor + width, y + 18,
                         column, row, cellWidth, cellHeight,
                         foreground, background, 0);
        }
        cursor -= width;
        value /= 10;
    }
}

// .text:0x000053E0 size:0x138 mapped:0x80644474
void fn_3_53E0(const u16* encoded, s16* column, s16* row, s16* width, s16* height, s16* page) {
    int value = *encoded;
    if (value & STADIUM_ATLAS_SKIP_FLAG) {
        return;
    }
    if (value & STADIUM_ATLAS_PAGED_FLAG) {
        u16 remainder;
        value &= 0x7FFF;
        *page = value / STADIUM_ATLAS_CELLS_PER_PAGE;
        remainder = value % STADIUM_ATLAS_CELLS_PER_PAGE;
        *column = remainder % STADIUM_ATLAS_COLUMNS;
        *row = (remainder / STADIUM_ATLAS_COLUMNS) * STADIUM_ATLAS_CELL_SIZE;
        *column *= STADIUM_ATLAS_CELL_SIZE;
        *width = STADIUM_ATLAS_CELL_SIZE;
        *height = STADIUM_ATLAS_CELL_SIZE;
    } else {
        *column = value % STADIUM_ATLAS_HALF_COLUMNS;
        *row = (value / STADIUM_ATLAS_HALF_COLUMNS) * STADIUM_ATLAS_CELL_SIZE;
        *column = (((*column / 2) * 2) + (*column % 2)) * STADIUM_ATLAS_HALF_CELL_SIZE;
        *width = STADIUM_ATLAS_HALF_CELL_SIZE;
        *height = STADIUM_ATLAS_CELL_SIZE;
        *page = 0;
    }
}

// .text:0x00005518 size:0x164 mapped:0x806445AC
void fn_3_5518(void) {
    Mtx44 projection;
    Mtx identity;
    StadiumTextureOffsets stadiumTextureOffsets = stadiumTextureOffsetsSource;
    u8 stadiumID = g_d_GameSettings.StadiumID;
    u8* textureTable = (u8*)g_UNK_StadiumDetails._00;
    int textureOffset = stadiumTextureOffsets.offsets[stadiumID] << 5;
    void* texture;

    GXSetZMode(TRUE, GX_ALWAYS, TRUE);
    GXSetScissor(0, 0, 640, 448);
    C_MTXOrtho(projection, lbl_3_rodata_504, lbl_3_rodata_524,
               lbl_3_rodata_504, lbl_3_rodata_528,
               lbl_3_rodata_52C, lbl_3_rodata_530);
    GXSetProjection(projection, GX_ORTHOGRAPHIC);
    GXSetCullMode(GX_CULL_NONE);
    PSMTXIdentity(identity);
    GXLoadPosMtxImm(identity, 0);
    GXSetCurrentMtx(0);
    GXSetTexCopySrc(0, 0, 512, 480);
    GXSetTexCopyDst(512, 480, 0x20, FALSE);
    inningScoreDisplayRelated(g_d_GameSettings.StadiumID);
    texture = *(void**)(textureTable + textureOffset);
    GXDrawDone();
    GXCopyTex(texture, TRUE);
    GXPixModeSync();
}

// .text:0x0000567C size:0x530 mapped:0x80644710
void drawStadiumObjects(void) {
    u8* frameData = FrameCountOfEntireGame;
    u8* sunData;
    int cameraCount;
    int slot;
    f32 rotation;
    int mode = ((u8*)&g_GameLogic)[0x120];

    if (mode < 3 && mode >= 1) {
        sunData = ((u8*)&g_UNK_StadiumDetails) + 0x738 + (mode - 1) * 0x10;
    } else {
        sunData = ((u8*)&g_UNK_StadiumDetails) + 0x758;
    }
    if (hugeAnimStruct[0x307E] == 0) {
        return;
    }
    *(u8*)((u8*)&lbl_3_common_bss_35154 + 0x3E0) = mode != 1;
    if (mode != 1) {
        sunRelated((MtxPtr)((u8*)fn_80052768_getCamera(0) + 0x40));
    }
    fn_3_B8C08((MtxPtr)((u8*)fn_80052768_getCamera(0) + 0x40));
    rotation = *(f32*)(((u8*)&g_UNK_StadiumDetails) + 0x710) + *(f32*)(((u8*)&g_UNK_StadiumDetails) + 0x768);
    *(f32*)(((u8*)&g_UNK_StadiumDetails) + 0x710) = rotation;
    if (rotation >= lbl_3_rodata_534) {
        rotation -= lbl_3_rodata_534;
        *(f32*)(((u8*)&g_UNK_StadiumDetails) + 0x710) = rotation;
    }
    cameraCount = ((int (*)(void))returnScissorMode)();
    if (cameraCount >= 2) {
        u8* object = ((u8*)&g_UNK_StadiumDetails) + 0x2A8 + drawStadiumRelated * 0x70;
        *(u32*)(object + 0x6C) = 1;
        PSMTXCopy((MtxPtr)((u8*)returnFloatFromModeIndex(1) + 0x40), (MtxPtr)(object + 0x38));
        fn_800A7D4C(0, object);
        fn_800A7D4C(0, frameData + 0x748 + drawStadiumRelated * 8);
        object = ((u8*)&g_UNK_StadiumDetails) + 0x1C8 + drawStadiumRelated * 0x70;
        *(u32*)(object + 0x6C) = 1;
        PSMTXRotRad((MtxPtr)(object + 8), 'Y', *(f32*)(((u8*)&g_UNK_StadiumDetails) + 0x710));
        PSMTXCopy((MtxPtr)((u8*)returnFloatFromModeIndex(1) + 0x40), (MtxPtr)(object + 0x38));
        if (((u8*)&g_GameLogic)[0x121] != 3) {
            fn_800A7D4C(0, object);
        }
        fn_800A7D4C(0, frameData + 0x7A0 + drawStadiumRelated * 0xC);
    }
    if (((int (*)(void))returnScissorMode)() > 2) {
        for (slot = 0; slot < 0; slot++) {
            u8* object = ((u8*)&g_UNK_StadiumDetails) + 0x548 + drawStadiumRelated * 0x70 + slot * 0xE0;
            *(u32*)(object + 0x6C) = slot + 2;
            PSMTXCopy((MtxPtr)((u8*)returnFloatFromModeIndex(slot + 2) + 0x40), (MtxPtr)(object + 0x38));
            fn_800A7D4C(0, object);
            fn_800A7D4C(0, frameData + 0x738 + (slot + 2) * 0x10 + drawStadiumRelated * 8);
            object = ((u8*)&g_UNK_StadiumDetails) + 0x388 + drawStadiumRelated * 0x70 + slot * 0xE0;
            *(u32*)(object + 0x6C) = slot + 2;
            PSMTXRotRad((MtxPtr)(object + 8), 'Y', *(f32*)(((u8*)&g_UNK_StadiumDetails) + 0x710));
            PSMTXCopy((MtxPtr)((u8*)returnFloatFromModeIndex(slot + 2) + 0x40), (MtxPtr)(object + 0x38));
            if (((u8*)&g_GameLogic)[0x121] != 3) {
                fn_800A7D4C(0, object);
            }
            fn_800A7D4C(0, frameData + 0x788 + (slot + 2) * 0x18 + drawStadiumRelated * 0xC);
        }
    }
    {
        u8* object = ((u8*)&g_UNK_StadiumDetails) + 0xE8 + drawStadiumRelated * 0x70;
        *(u32*)(object + 0x6C) = 0;
        PSMTXCopy((MtxPtr)((u8*)returnFloatFromModeIndex(0) + 0x40), (MtxPtr)(object + 0x38));
        fn_800A7D4C(0, object);
        fn_800A7D4C(0, frameData + 0x738 + drawStadiumRelated * 8);
        fn_800A7D4C(0, frameData + 0x5B4 + drawStadiumRelated * 8);
        object = ((u8*)&g_UNK_StadiumDetails) + 8 + drawStadiumRelated * 0x70;
        *(u32*)(object + 0x6C) = 0;
        PSMTXRotRad((MtxPtr)(object + 8), 'Y', *(f32*)(((u8*)&g_UNK_StadiumDetails) + 0x710));
        PSMTXCopy((MtxPtr)((u8*)returnFloatFromModeIndex(0) + 0x40), (MtxPtr)(object + 0x38));
        fn_800A7D4C(0, object);
        fn_800A7D4C(0, frameData + 0x788 + drawStadiumRelated * 0xC);
    }
    if ((g_d_GameSettings.GameModeSelected == 0 || g_d_GameSettings.GameModeSelected == 4) &&
        g_d_GameSettings.StadiumID != 2) {
        *(u32*)(frameData + 0x71C + drawStadiumRelated * 0x10) = *(u32*)((u8*)&stadiumObjectCollision + 8);
        *(u32*)(frameData + 0x720 + drawStadiumRelated * 0x10) = *(u32*)((u8*)&stadiumObjectCollision + 0xC);
    } else {
        *(u32*)(frameData + 0x71C + drawStadiumRelated * 0x10) = 0;
        *(u32*)(frameData + 0x720 + drawStadiumRelated * 0x10) = 0;
    }
    fn_800A7D4C(0, frameData + 0x714 + drawStadiumRelated * 0x10);
    if (*(u8*)((u8*)&lbl_3_common_bss_35154 + 0x3E0) != 0) {
        drawSun();
    }
    lbl_803C5090[0x1D] = sunData[0xC];
    *(f32*)(lbl_803C5090 + 0) = *(f32*)(sunData + 0);
    *(f32*)(lbl_803C5090 + 4) = lbl_3_rodata_520 / *(f32*)((u8*)fn_80052768_getCamera(0) + 0xA4);
    *(f32*)(lbl_803C5090 + 8) = *(f32*)(sunData + 4);
    *(f32*)(lbl_803C5090 + 0xC) = *(f32*)(sunData + 8);
    *(u16*)(lbl_803C5090 + 0x14) = *(u16*)(sunData + 0xE);
    lbl_803C5090[0x17] = sunData[0xD];
    lbl_803C5090[0x18] = 0;
    lbl_803C5090[0x1A] = 0xFF;
    lbl_803C5090[0x1B] = 0xFF;
    lbl_803C5090[0x1C] = 0xFF;
    fn_8003A2C0();
}

// .text:0x00005BAC size:0x20 mapped:0x80644C40
void drawStadium(void) {
    drawStadiumObjects();
}

// .text:0x00005BCC size:0x24 mapped:0x80644C60
void fn_3_5BCC(void* context) {
    setScissorAndProjection(*(s32*)((u8*)context + 8));
}

// .text:0x00005BF0 size:0x78 mapped:0x80644C84
void fn_3_5BF0(void) {
    u8* stadium = (u8*)&g_UNK_StadiumDetails;
    GXColor color;
    if (lbl_3_bss_18.fanObject != 0) {
        ((void (*)(void))lbl_3_bss_18.fanObject)();
    }
    color = *(GXColor*)(stadium + 0x714);
    SetFog((GXFogType)stadium[0x717], *(f32*)(stadium + 0x718), *(f32*)(stadium + 0x71C),
           lbl_3_rodata_520, lbl_3_rodata_538, color);
}

// .text:0x00005C68 size:0x1F8 mapped:0x80644CFC
void fn_3_5C68(void* context) {
    StadiumAnimatedTexturePair* pair = (StadiumAnimatedTexturePair*)context;
    u8* slotCursor;
    int pass;
    GXSetCullMode(GX_CULL_BACK);
    SetFog(GX_FOG_NONE, lbl_3_rodata_504, lbl_3_rodata_504,
           lbl_3_rodata_504, lbl_3_rodata_504, lbl_3_rodata_210);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    slotCursor = (u8*)pair + 8;
    pass = 2;
    do {
        StadiumAnimatedTexture* animation = *(StadiumAnimatedTexture**)(slotCursor + 8);
        int index;
        int stateOffset;
        int updated;
        if (animation != 0) {
          updated = 0;
          for (index = 0, stateOffset = 0; index < animation->tileCount; index++, stateOffset += 3) {
            u8 previous = animation->animationState[stateOffset + 2]--;
            if (previous == 0) {
                int destinationX = (index % 8) * 32;
                int destinationY = (index / 8) * 64;
                int frame = (animation->animationState[stateOffset + 1] + 1) % animation->frameCount;
                int tile;
                int mapIndex;
                int sourceX;
                int sourceY;
                animation->animationState[stateOffset + 1] = frame;
                tile = animation->tileIndex[animation->animationState[stateOffset + 1]];
                if (pass != 0) {
                    mapIndex = animation->animationState[stateOffset] * 4 + tile * 2;
                    sourceX = animation->tileMap[mapIndex] * 32;
                    sourceY = animation->tileMap[mapIndex + 1] * 64;
                } else {
                    mapIndex = animation->animationState[stateOffset] * 8 + tile * 2;
                    sourceX = animation->tileMap[mapIndex] * 32;
                    sourceY = animation->tileMap[mapIndex + 1] * 64;
                }
                fn_80023F0C(animation->source, animation->destination,
                              sourceX, sourceY, 32, 64, destinationX,
                              destinationY);
                animation->animationState[stateOffset + 2] = animation->resetFrames;
                updated++;
            }
          }
          if (updated != 0) {
              DCStoreRange(animation->destination->pixels,
                           animation->destination->height * animation->destination->width);
          }
        }
        slotCursor -= 4;
    } while (pass-- != 0);
    if (lbl_3_bss_18.fanObject != 0) {
        ((void (*)(void))lbl_3_bss_18.fanObject)();
    }
    GXSetZCompLoc(FALSE);
}

void fn_3_38E8(void (*func)(Mtx view, int flag, u32 pass)) {
    lbl_3_data_A10[drawStadiumRelated] = func;
}

void fn_3_3818(void) {
    int slot = !drawStadiumRelated;
    if (lbl_3_data_A10[slot] != 0) {
        int mode = ((int (*)(void))returnScissorMode)() - 1;
        do {
            camera_803c639c_s* camera;
            setScissorAndProjection(mode);
            camera = returnFloatFromModeIndex(mode);
            lbl_3_data_A10[!drawStadiumRelated](camera->view, 0, 0);
        } while (mode-- != 0);
        lbl_3_data_A10[!drawStadiumRelated] = 0;
    }
}

void fn_3_35E4(int fanObject) {
    lbl_3_bss_18.fanObject = (void*)fanObject;
}

void* setFanObjPtr(void) {
    return lbl_3_bss_18.fanObject;
}

void fn_3_5E60(void) {
    u8* block = *(u8**)(hugeAnimStruct + 4);
    unregisterObjectByID(5);
    fn_800BCDBC(block + *(u32*)(block + 0x10));
    fn_800BCDBC(block + *(u32*)(block + 0xC));
    fn_800ACFB0(*(void**)(hugeAnimStruct + 4));
}

s16 fn_3_6424(void* base, void*** tableOut) {
    s16 count = *(u16*)base;
    void** table = (void**)((u8*)base + 4);
    void** cursor = table;
    int i;
    *tableOut = table;
    for (i = 0; i <= count; i++) {
        *cursor = (u8*)((u32)*cursor + (u32)base);
        cursor++;
    }
    return count;
}

void fn_3_64DC(void) {
    u8 stadium = g_d_GameSettings.StadiumID;
    u8 variant = g_d_GameSettings.miniGameStadiumIndicator;
    ARAMTransfer(StadiumFiles_game[stadium * 3 + variant], 0, 0, 0);
}

void updateStadiumFileHeaders(void* file) {
    u8* bytes = (u8*)file;
    u8* actor = bytes + *(u32*)(bytes + 0);
    u8* geometry = bytes + *(u32*)(bytes + 0xC);
    u8* texture = bytes + *(u32*)(bytes + 0x14);
    u8* pointerBlock = bytes + *(u32*)(bytes + 8);
    u8* pointerList = pointerBlock + 4;
    s16 pointerCount = *(u16*)pointerBlock;
    int i;

    *(void**)(((u8*)&g_UNK_StadiumDetails) + 0x70C) = pointerList;
    for (i = 0; i <= pointerCount; i++) {
        ((u32*)pointerList)[i] += (u32)pointerBlock;
    }
    *(s16*)(((u8*)&g_UNK_StadiumDetails) + 0x70A) = pointerCount;
    AdjustActorPointers(actor);
    AdjustGEOPalettePointers((DODisplayDataPtr)geometry);
    convertTextureHeader(texture);
    UpdateTexturePalettePointers((UnkTexPalGeo*)geometry, texture);
    haveActLayoutPointToGeoHeader(actor, geometry);
    ProcessActorBonesForShadows((ActorLayoutFile*)actor);
    *(void**)(((u8*)&g_UNK_StadiumDetails) + 4) = texture;

    PSMTXIdentity((MtxPtr)(((u8*)&g_UNK_StadiumDetails) + 0xF0));
    *(u32*)(((u8*)&g_UNK_StadiumDetails) + 0xE8) = 2;
    *(void**)(((u8*)&g_UNK_StadiumDetails) + 0xEC) = (void*)CTRLBuildMatrixRelated;
    *(void**)(((u8*)&g_UNK_StadiumDetails) + 0x150) = actor;
    *(StadiumRenderEntry*)(((u8*)&g_UNK_StadiumDetails) + 0x158) = *(StadiumRenderEntry*)(((u8*)&g_UNK_StadiumDetails) + 0xE8);
    *(StadiumRenderEntry*)(((u8*)&g_UNK_StadiumDetails) + 0x2A8) = *(StadiumRenderEntry*)(((u8*)&g_UNK_StadiumDetails) + 0xE8);
    *(StadiumRenderEntry*)(((u8*)&g_UNK_StadiumDetails) + 0x318) = *(StadiumRenderEntry*)(((u8*)&g_UNK_StadiumDetails) + 0xE8);
    copyExtraStadiumEntries((StadiumRenderEntry*)(((u8*)&g_UNK_StadiumDetails) + 0xE8),
                                ((u8*)&g_UNK_StadiumDetails) + 0x548, ((u8*)&g_UNK_StadiumDetails) + 0x5B8, 0);

    actor = bytes + *(u32*)(bytes + 4);
    geometry = bytes + *(u32*)(bytes + 0x10);
    AdjustActorPointers(actor);
    AdjustGEOPalettePointers((DODisplayDataPtr)geometry);
    UpdateTexturePalettePointers((UnkTexPalGeo*)geometry, texture);
    haveActLayoutPointToGeoHeader(actor, geometry);
    *(u32*)(((u8*)&g_UNK_StadiumDetails) + 8) = 2;
    *(void**)(((u8*)&g_UNK_StadiumDetails) + 0xC) = (void*)CTRLBuildMatrixRelated;
    *(void**)(((u8*)&g_UNK_StadiumDetails) + 0x70) = actor;
    *(StadiumRenderEntry*)(((u8*)&g_UNK_StadiumDetails) + 0x78) = *(StadiumRenderEntry*)(((u8*)&g_UNK_StadiumDetails) + 8);
    *(StadiumRenderEntry*)(((u8*)&g_UNK_StadiumDetails) + 0x1C8) = *(StadiumRenderEntry*)(((u8*)&g_UNK_StadiumDetails) + 8);
    *(StadiumRenderEntry*)(((u8*)&g_UNK_StadiumDetails) + 0x238) = *(StadiumRenderEntry*)(((u8*)&g_UNK_StadiumDetails) + 8);
    copyExtraStadiumEntries((StadiumRenderEntry*)(((u8*)&g_UNK_StadiumDetails) + 8),
                                ((u8*)&g_UNK_StadiumDetails) + 0x388, ((u8*)&g_UNK_StadiumDetails) + 0x3F8, 0);

    {
        typedef struct StadiumStyleRecord {
            u32 words[24];
        } StadiumStyleRecord;
        u32* selected = lbl_3_data_23C +
            (g_d_GameSettings.miniGameStadiumIndicator * 7 + g_d_GameSettings.StadiumID) * 24;
        *(StadiumStyleRecord*)(((u8*)&g_UNK_StadiumDetails) + 0x714) = *(StadiumStyleRecord*)selected;
    }
    *(void**)(((u8*)&g_UNK_StadiumDetails) + 0) = texture + 4;
    ((u8*)&g_UNK_StadiumDetails)[0x774] = 0;
    fn_8003AE5C(((u8*)&g_UNK_StadiumDetails)[0x771]);

    texture = bytes + *(u32*)(bytes + 0x28);
    convertTextureHeader(texture);
    *(void**)(lbl_3_common_bss_35154 + 0x3B4) = texture + 4;
    setSunLocation(g_d_GameSettings.StadiumID, g_d_GameSettings.miniGameStadiumIndicator);

    if (*(u32*)(bytes + 0x2C) != 0) {
        pointerBlock = bytes + *(u32*)(bytes + 0x2C);
        pointerList = pointerBlock + 4;
        pointerCount = *(u16*)pointerBlock;
        *(void**)(((u8*)&g_UNK_StadiumDetails) + 0x778) = pointerList;
        for (i = 0; i <= pointerCount; i++) {
            ((u32*)pointerList)[i] += (u32)pointerBlock;
        }
        *(s16*)(((u8*)&g_UNK_StadiumDetails) + 0x77C) = pointerCount;
    } else {
        *(s16*)(((u8*)&g_UNK_StadiumDetails) + 0x77C) = 0;
    }
    if (*(u32*)(bytes + 0x30) != 0) {
        texture = bytes + *(u32*)(bytes + 0x30);
        convertTextureHeader(texture);
        GXTexObjRelated((TextureRecord*)texture);
    }
    maybeUpdateFunctionPointer(fn_3_35F0);
}

void CTRLBuildMatrixRelated(void* object) {
    u8* base = (u8*)object;
    u8* list = *(u8**)(base + 0x68);
    u8* entry = list;
    u8* table = *(u8**)(list + 0x10);
    int index;
    for (index = 0; index < *(u16*)(list + 6); index++, entry += 0x1C) {
        u16 objectIndex = *(u16*)(entry + 0x34);
        u8* child;
        if (objectIndex == 0xFFFF) {
            continue;
        }
        child = *(u8**)(*(u8**)(table + 0x10) + objectIndex * 8);
        CTRLBuildMatrix((Control*)*(void**)(entry + 0x20), (MtxPtr)(child + 0x18));
        PSMTXConcat((MtxPtr)(base + 8), (MtxPtr)(child + 0x18), (MtxPtr)(child + 0x18));
        {
            Mtx temporary;
            f32 corners[8][3];
            PSMTXConcat((MtxPtr)(base + 0x38), (MtxPtr)(child + 0x18), temporary);
            corners[0][0] = *(f32*)(child + 0x58); corners[0][1] = *(f32*)(child + 0x60); corners[0][2] = *(f32*)(child + 0x64);
            corners[1][0] = *(f32*)(child + 0x54); corners[1][1] = *(f32*)(child + 0x60); corners[1][2] = *(f32*)(child + 0x64);
            corners[2][0] = *(f32*)(child + 0x54); corners[2][1] = *(f32*)(child + 0x60); corners[2][2] = *(f32*)(child + 0x68);
            corners[3][0] = *(f32*)(child + 0x58); corners[3][1] = *(f32*)(child + 0x60); corners[3][2] = *(f32*)(child + 0x68);
            corners[4][0] = *(f32*)(child + 0x58); corners[4][1] = *(f32*)(child + 0x5C); corners[4][2] = *(f32*)(child + 0x64);
            corners[5][0] = *(f32*)(child + 0x54); corners[5][1] = *(f32*)(child + 0x5C); corners[5][2] = *(f32*)(child + 0x64);
            corners[6][0] = *(f32*)(child + 0x54); corners[6][1] = *(f32*)(child + 0x5C); corners[6][2] = *(f32*)(child + 0x68);
            corners[7][0] = *(f32*)(child + 0x58); corners[7][1] = *(f32*)(child + 0x5C); corners[7][2] = *(f32*)(child + 0x68);
            if (!checkObjectVisibility(*(int*)(base + 0x6C), corners, temporary)) {
                continue;
            }
        }
        if (*(u16*)(entry + 0x3A) & 1) {
            GXSetZMode(TRUE, GX_ALWAYS, TRUE);
        } else {
            GXSetZMode(TRUE, GX_LEQUAL, TRUE);
        }
        switch (*(u16*)(entry + 0x3A) & 6) {
        case 2:
            GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_LO_CLEAR);
            break;
        case 4:
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCCOL, GX_BL_ZERO, GX_LO_CLEAR);
            break;
        default:
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
            break;
        }
        DOVARender((struct DODisplayObj*)child, (MtxPtr)(base + 0x38), 0, 0);
    }
}
