#include "Unknown/File_0x800096dc.h"
#include "Unknown/File_0x800097a0.h"
#include "Unknown/File_0x800a7544.h"
#include "Unknown/File_0x800b0a14.h"
#include "Dolphin/OS/OSError.h"

typedef struct {
    /* 0x0 */ u32 unk0;
    /* 0x4 */ u32 unk4;
} Unk8ByteBlock;

// Only the fields PrepFilesToBeLoaded touches.
extern struct {
    /* 0x00 */ u8 _00[0x50];
    /* 0x50 */ Unk8ByteBlock unk50;
} lbl_803C7420;

extern struct {
    /* 0x00 */ Unk8ByteBlock unk00;
    /* 0x08 */ u8 _08[0x1D - 0x08];
    /* 0x1D */ u8 unk1D;
} lbl_80366158;

extern u8 lbl_80110080[0x10];

extern s32 s32ProgId;
extern s32 s32DataId;

// The loader node's view of its scratch area (see DrawingSceneStruct).
typedef struct {
    /* 0x00 */ u8 _00[0x18];
    /* 0x18 */ u16 loaderState;
} LoaderNode;

// Path records handed to ConvertPathToEntryNum, which reads the leading path.
typedef struct {
    /* 0x0 */ char* path;
    /* 0x4 */ u32 unk4[3];
} FileEntry;

FileEntry lbl_800E8EE8 = {"aaaa.dat"};
FileEntry lbl_800E8EF8 = {"ZZZZ.dat"};

void PrepFilesToBeLoaded(void) {
    LoaderNode* item;

    item = (LoaderNode*)currentDrawingItem;
    lbl_80366158.unk00.unk0 = lbl_803C7420.unk50.unk0;
    lbl_80366158.unk00.unk4 = lbl_803C7420.unk50.unk4;
    s32ProgId = ConvertPathToEntryNum(&lbl_800E8EE8.path);
    s32DataId = ConvertPathToEntryNum(&lbl_800E8EF8.path);
    item->loaderState = 0;
    currentDrawingItem->func = handleLoadingProcess;
    OSReport("s32ProgId=%d\n", s32ProgId);
    OSReport("s32DataId=%d\n", s32DataId);
    lbl_80110080[5] = 4;
    lbl_80366158.unk1D = 1;
}
