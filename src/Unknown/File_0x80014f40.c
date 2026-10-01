#include "Unknown/File_0x80014f40.h"
#include "Unknown/File_0x800a70dc.h"
#include "Unknown/File_0x800a7568.h"

typedef struct CompressedFileEntry {
    /*0x00*/ u8 _00[0x10];
} CompressedFileEntry;

extern struct {
    /*0x0000*/ u8 _0000[0x2D3C];
    /*0x2D3C*/ s32 batterModelDest;
    /*0x2D40*/ u8 _2D40[0x2D44 - 0x2D40];
    /*0x2D44*/ u16 batterModelIndex;
    /*0x2D46*/ u8 batterModelLoadState;
    /*0x2D47*/ u8 _2D47[0x3154 - 0x2D47];
} hugeAnimStruct;

extern CompressedFileEntry* lbl_803CB790;

BOOL loadBatterModelFromDisk(int index) {
    if (index < 0) {
        return TRUE;
    }
    if (hugeAnimStruct.batterModelLoadState <= 1) {
        int file = index * 0x13 + 1;

        if (lbl_803C6CF8.cancel.bytes[1] != 1) {
            hugeAnimStruct.batterModelLoadState = 1;
            return FALSE;
        }
        ARAMTransfer(&lbl_803CB790[file], hugeAnimStruct.batterModelDest, 0, 0);
        hugeAnimStruct.batterModelLoadState = 2;
    } else if (lbl_803C6CF8.cancel.bytes[1] == 1) {
        hugeAnimStruct.batterModelIndex = index;
        hugeAnimStruct.batterModelLoadState = 0;
        return TRUE;
    }
    return FALSE;
}
