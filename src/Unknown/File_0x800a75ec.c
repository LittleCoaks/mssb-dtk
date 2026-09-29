#include "Unknown/File_0x800a75ec.h"
#include "Unknown/File_0x800a64e0.h"
#include "Unknown/File_0x800a7568.h"
#include "Unknown/File_0x800acf14.h"

void cancelReadCallback1(s32 result, DVDCommandBlock* block) {
    OSCancelThread(&gDataDecompressorValues.t);
    StartThreadForReadingFromDisk();
    lbl_803C6CF8.cancel.cancelRequested = 1;
    if (gDataDecompressorValues.pendingBlock != NULL) {
        unkLoadingCleanupRelated(gDataDecompressorValues.pendingBlock);
        gDataDecompressorValues.pendingBlock = NULL;
    }
    if (lbl_803C6CF8.pendingBlock != NULL) {
        unkLoadingCleanupRelated(lbl_803C6CF8.pendingBlock);
        lbl_803C6CF8.pendingBlock = NULL;
    }
}
