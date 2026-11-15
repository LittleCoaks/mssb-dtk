#include "Unknown/File_0x80014e50.h"
#include "Unknown/dvdsys.h"
#include "Unknown/File_0x800a7568.h"
#include "HugeAnimStruct.h"

typedef struct CompressedFileEntry {
    /*0x00*/ u8 _00[0x10];
} CompressedFileEntry;


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
    if (hugeAnimStruct.loadSlots[2].state <= 1) {
        int file = index * 0x13;

        if (lbl_803C6CF8.cancel.bytes[1] != 1) {
            hugeAnimStruct.loadSlots[2].state = 1;
            return FALSE;
        }
        if (fn_8002204C(index, ((s32)hugeAnimStruct.loadSlots[2].dest)) == NULL) {
            ARAMTransfer(&lbl_803CB790[file], ((s32)hugeAnimStruct.loadSlots[2].dest), 0, 0);
        }
        hugeAnimStruct.loadSlots[2].state = 2;
    } else if (lbl_803716B8.unk1E8 == 0 && lbl_803C6CF8.cancel.bytes[1] == 1) {
        hugeAnimStruct.loadSlots[2].index = index;
        hugeAnimStruct.loadSlots[2].state = 0;
        return TRUE;
    }
    return FALSE;
}
