#include "Unknown/File_0x800a7670.h"
#include "Unknown/File_0x800acf14.h"

/* The loader state is addressed through one base register that runs past
 * the end of dtk's 0x708-byte lbl_803C6CF8 label; only the fields used here
 * are named. */
typedef struct {
    /* 0x000 */ u8 _000[0x6FC];
    /* 0x6FC */ void* pendingBlock;
    /* 0x700 */ u8 _700[0x714 - 0x700];
    /* 0x714 */ u16 cancelRequested;
} LoadState;

extern LoadState lbl_803C6CF8;

void cancelReadCallback2(void) {
    lbl_803C6CF8.cancelRequested = 1;
    if (lbl_803C6CF8.pendingBlock != NULL) {
        unkLoadingCleanupRelated(lbl_803C6CF8.pendingBlock);
        lbl_803C6CF8.pendingBlock = NULL;
    }
}
