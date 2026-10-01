#include "Unknown/File_0x80014e50.h"
#include "Unknown/File_0x800a70dc.h"
#include "Unknown/File_0x800a7568.h"

typedef struct CompressedFileEntry {
    /*0x00*/ u8 _00[0x10];
} CompressedFileEntry;

extern struct {
    /*0x0000*/ u8 _0000[0x2D54];
    /*0x2D54*/ s32 fileDest;
    /*0x2D58*/ u8 _2D58[0x2D5C - 0x2D58];
    /*0x2D5C*/ u16 fileIndex;
    /*0x2D5E*/ u8 fileLoadState;
    /*0x2D5F*/ u8 _2D5F[0x3154 - 0x2D5F];
} hugeAnimStruct;

extern struct {
    /*0x000*/ u8 _000[0x1E8];
    /*0x1E8*/ u8 unk1E8;
    /*0x1E9*/ u8 _1E9[0x578 - 0x1E9];
} lbl_803716B8;

extern CompressedFileEntry* lbl_803CB790;

void* fn_8002204C(int index, s32 dest);

BOOL loadSomethingFromDiskAtBeginningOfAB2(int index) {
    if (index < 0) {
        return TRUE;
    }
    if (hugeAnimStruct.fileLoadState <= 1) {
        int file = index * 0x13;

        if (lbl_803C6CF8.cancel.bytes[1] != 1) {
            hugeAnimStruct.fileLoadState = 1;
            return FALSE;
        }
        if (fn_8002204C(index, hugeAnimStruct.fileDest) == NULL) {
            ARAMTransfer(&lbl_803CB790[file], hugeAnimStruct.fileDest, 0, 0);
        }
        hugeAnimStruct.fileLoadState = 2;
    } else if (lbl_803716B8.unk1E8 == 0 && lbl_803C6CF8.cancel.bytes[1] == 1) {
        hugeAnimStruct.fileIndex = index;
        hugeAnimStruct.fileLoadState = 0;
        return TRUE;
    }
    return FALSE;
}
