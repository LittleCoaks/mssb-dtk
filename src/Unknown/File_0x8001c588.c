#include "Unknown/File_0x8001c588.h"
#include "Unknown/dvdsys.h"
#include "Unknown/File_0x800a7568.h"
#include "C3/anim.h"
#include "HugeAnimStruct.h"

typedef struct CompressedFileEntry {
    /*0x00*/ u8 _00[0x10];
} CompressedFileEntry;

typedef struct {
    /*0x00*/ u8 _00[0x20];
    /*0x20*/ ANIMBank* animBank;
} FielderActorData;


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
            ARAMTransfer(&lbl_803CB790[charID * 0x13 + 6], (s32)hugeAnimStruct.animBanks[15], 0, 0);
            highLevelSimulationFlag[3] = 2;
        } else if (highLevelSimulationFlag[3] == 2 && lbl_803C6CF8.cancel.bytes[1] == 1) {
            ANIMGet(hugeAnimStruct.animBanks[15]);
            if (((FielderActorData*)hugeAnimStruct.objects[1])->animBank == NULL) {
                ((FielderActorData*)hugeAnimStruct.objects[1])->animBank = hugeAnimStruct.animBanks[15];
            }
            return TRUE;
        }
    } while (0);
    highLevelSimulationFlag[0] = 0;
    return FALSE;
}
