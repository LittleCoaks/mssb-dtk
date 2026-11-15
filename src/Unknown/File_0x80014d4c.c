#include "Unknown/File_0x80014d4c.h"
#include "Unknown/dvdsys.h"
#include "Unknown/File_0x800a7568.h"
#include "static/UnknownHomes_Static.h"
#include "HugeAnimStruct.h"

typedef struct CompressedFileEntry {
    /*0x00*/ u8 _00[0x10];
} CompressedFileEntry;


extern CompressedFileEntry* lbl_803CB790;

BOOL loadSomethingFromDiskAtBeginningOfAB1(int index) {
    if (index < 0) {
        return TRUE;
    }
    if (hugeAnimStruct.loadSlots[1].index == index) {
        return TRUE;
    }
    if (hugeAnimStruct.loadSlots[1].state <= 1) {
        int file;

        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
            file = index * 0x13 + 10;
        } else {
            file = index * 0x13 + 2;
        }
        if (lbl_803C6CF8.cancel.bytes[1] != 1) {
            hugeAnimStruct.loadSlots[1].state = 1;
            return FALSE;
        }
        ARAMTransfer(&lbl_803CB790[file], ((s32)hugeAnimStruct.loadSlots[1].dest), 0, 0);
        hugeAnimStruct.loadSlots[1].state = 2;
    } else if (lbl_803C6CF8.cancel.bytes[1] == 1) {
        hugeAnimStruct.loadSlots[1].index = index;
        hugeAnimStruct.loadSlots[1].state = 0;
        return TRUE;
    }
    return FALSE;
}
