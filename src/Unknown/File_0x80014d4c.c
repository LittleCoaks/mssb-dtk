#include "Unknown/File_0x80014d4c.h"
#include "Unknown/File_0x800a70dc.h"
#include "Unknown/File_0x800a7568.h"
#include "static/UnknownHomes_Static.h"

typedef struct CompressedFileEntry {
    /*0x00*/ u8 _00[0x10];
} CompressedFileEntry;

extern struct {
    /*0x0000*/ u8 _0000[0x2D48];
    /*0x2D48*/ s32 modelDest;
    /*0x2D4C*/ u8 _2D4C[0x2D50 - 0x2D4C];
    /*0x2D50*/ s16 modelIndex;
    /*0x2D52*/ u8 modelLoadState;
    /*0x2D53*/ u8 _2D53[0x3154 - 0x2D53];
} hugeAnimStruct;

extern CompressedFileEntry* lbl_803CB790;

BOOL loadSomethingFromDiskAtBeginningOfAB1(int index) {
    if (index < 0) {
        return TRUE;
    }
    if (hugeAnimStruct.modelIndex == index) {
        return TRUE;
    }
    if (hugeAnimStruct.modelLoadState <= 1) {
        int file;

        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
            file = index * 0x13 + 10;
        } else {
            file = index * 0x13 + 2;
        }
        if (lbl_803C6CF8.cancel.bytes[1] != 1) {
            hugeAnimStruct.modelLoadState = 1;
            return FALSE;
        }
        ARAMTransfer(&lbl_803CB790[file], hugeAnimStruct.modelDest, 0, 0);
        hugeAnimStruct.modelLoadState = 2;
    } else if (lbl_803C6CF8.cancel.bytes[1] == 1) {
        hugeAnimStruct.modelIndex = index;
        hugeAnimStruct.modelLoadState = 0;
        return TRUE;
    }
    return FALSE;
}
