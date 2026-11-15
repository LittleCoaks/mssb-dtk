#include "Unknown/File_0x80014f40.h"
#include "Unknown/dvdsys.h"
#include "Unknown/File_0x800a7568.h"
#include "HugeAnimStruct.h"

typedef struct CompressedFileEntry {
    /*0x00*/ u8 _00[0x10];
} CompressedFileEntry;


extern CompressedFileEntry* lbl_803CB790;

BOOL loadBatterModelFromDisk(int index) {
    if (index < 0) {
        return TRUE;
    }
    if (hugeAnimStruct.loadSlots[0].state <= 1) {
        int file = index * 0x13 + 1;

        if (lbl_803C6CF8.cancel.bytes[1] != 1) {
            hugeAnimStruct.loadSlots[0].state = 1;
            return FALSE;
        }
        ARAMTransfer(&lbl_803CB790[file], ((s32)hugeAnimStruct.loadSlots[0].dest), 0, 0);
        hugeAnimStruct.loadSlots[0].state = 2;
    } else if (lbl_803C6CF8.cancel.bytes[1] == 1) {
        hugeAnimStruct.loadSlots[0].index = index;
        hugeAnimStruct.loadSlots[0].state = 0;
        return TRUE;
    }
    return FALSE;
}
