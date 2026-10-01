#include "Unknown/File_0x8001c588.h"
#include "Unknown/File_0x800a70dc.h"
#include "Unknown/File_0x800a7568.h"
#include "C3/anim.h"

typedef struct CompressedFileEntry {
    /*0x00*/ u8 _00[0x10];
} CompressedFileEntry;

typedef struct {
    /*0x00*/ u8 _00[0x20];
    /*0x20*/ ANIMBank* animBank;
} FielderActorData;

extern struct {
    /*0x0000*/ u8 _0000[0x2C54];
    /*0x2C54*/ FielderActorData* fielderActorData;
    /*0x2C58*/ u8 _2C58[0x2CE8 - 0x2C58];
    /*0x2CE8*/ ANIMBank* fielderAnimBank;
    /*0x2CEC*/ u8 _2CEC[0x3154 - 0x2CEC];
} hugeAnimStruct;

extern u8 highLevelSimulationFlag[4];
extern CompressedFileEntry* lbl_803CB790;

BOOL loadFielderActors(int charID) {
    do {
        if (highLevelSimulationFlag[3] == 0) {
            if (lbl_803C6CF8.cancel.bytes[1] != 1) {
                break;
            }
            highLevelSimulationFlag[3] = 1;
        }
        if (highLevelSimulationFlag[3] == 1) {
            ARAMTransfer(&lbl_803CB790[charID * 0x13 + 6], (s32)hugeAnimStruct.fielderAnimBank, 0, 0);
            highLevelSimulationFlag[3] = 2;
        } else if (highLevelSimulationFlag[3] == 2 && lbl_803C6CF8.cancel.bytes[1] == 1) {
            ANIMGet(hugeAnimStruct.fielderAnimBank);
            if (hugeAnimStruct.fielderActorData->animBank == NULL) {
                hugeAnimStruct.fielderActorData->animBank = hugeAnimStruct.fielderAnimBank;
            }
            return TRUE;
        }
    } while (0);
    highLevelSimulationFlag[0] = 0;
    return FALSE;
}
