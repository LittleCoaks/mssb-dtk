#include "Unknown/File_0x800a7670.h"
#include "Unknown/File_0x800a7568.h"
#include "Unknown/File_0x800acf14.h"

void cancelReadCallback2(s32 result, DVDCommandBlock* block) {
    lbl_803C6CF8.cancel.cancelRequested = 1;
    if (lbl_803C6CF8.pendingBlock != NULL) {
        unkLoadingCleanupRelated(lbl_803C6CF8.pendingBlock);
        lbl_803C6CF8.pendingBlock = NULL;
    }
}
