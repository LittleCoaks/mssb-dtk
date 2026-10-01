#include "Unknown/File_0x8001c920.h"
#include "Unknown/File_0x800a70dc.h"
#include "Unknown/File_0x800a7568.h"
#include "static/UnknownHomes_Static.h"
#include "C3/anim.h"

typedef struct CompressedFileEntry {
    /*0x00*/ u8 _00[0x10];
} CompressedFileEntry;

typedef struct {
    /*0x00*/ u8 _00[0x1C];
    /*0x1C*/ ANIMBank* animBank;
} AnimObjectView;

extern struct {
    /*0x0000*/ u8 _0000[0x2C50];
    /*0x2C50*/ AnimObjectView* objects;
    /*0x2C54*/ u8 _2C54[0x2CE4 - 0x2C54];
    /*0x2CE4*/ ANIMBank* characterAnimBank;
} hugeAnimStruct;

extern CompressedFileEntry* lbl_803CB790;
extern u8 highLevelSimulationFlag[2];

BOOL loadCharacterAnimation(int charID) {
    if (highLevelSimulationFlag[1] == 0) {
        if (lbl_803C6CF8.cancel.bytes[1] != 1) {
            goto fail;
        }
        highLevelSimulationFlag[1] = 1;
    }
    if (highLevelSimulationFlag[1] == 1) {
        int file;

        if (g_d_GameSettings.minigamesEnabled || g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
            file = charID * 0x13 + 0x12;
        } else {
            file = charID * 0x13 + 5;
        }
        ARAMTransfer(&lbl_803CB790[file], (s32)hugeAnimStruct.characterAnimBank, 0, 0);
        highLevelSimulationFlag[1] = 2;
    } else if (highLevelSimulationFlag[1] == 2 && lbl_803C6CF8.cancel.bytes[1] == 1) {
        ANIMGet(hugeAnimStruct.characterAnimBank);
        if (hugeAnimStruct.objects->animBank == NULL) {
            hugeAnimStruct.objects->animBank = hugeAnimStruct.characterAnimBank;
        }
        return TRUE;
    }
fail:
    highLevelSimulationFlag[0] = 0;
    return FALSE;
}
