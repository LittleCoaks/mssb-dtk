#include "Unknown/File_0x800a7568.h"
#include "Unknown/File_0x800a75ec.h"
#include "Unknown/File_0x800a7670.h"
#include "Dolphin/ar.h"

void handleDVDCancelAndARQRemoval(void) {
    DVDCBCallback callback;

    lbl_803C6CF8.cancel.bytes[0] = 0;
    lbl_803C6CF8.unk722 = 0;
    if (lbl_803C6CF8.cancel.bytes[1] == 1) {
        return;
    }
    if (lbl_803C6CF8.loadType == 0 || lbl_803C6CF8.loadType == 3) {
        callback = cancelReadCallback1;
    } else {
        callback = cancelReadCallback2;
    }
    DVDCancelAsync(&lbl_803C6CF8.fileInfo->cBlock, callback);
    ARQRemoveOwnerRequest(2000);
}
