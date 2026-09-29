#ifndef __UNKNOWN_FILE_0X800A7568_H_
#define __UNKNOWN_FILE_0X800A7568_H_

#include "mssbTypes.h"
#include "Dolphin/dvd.h"

/* Disk-loader state. dtk's 0x708-byte lbl_803C6CF8 label spans several
 * objects; the loader addresses all of them through this one base, so only
 * the fields in use are named. */
typedef struct {
    /* 0x000 */ u8 _000[0x6DC];
    /* 0x6DC */ DVDFileInfo* fileInfo;
    /* 0x6E0 */ u8 _6E0[0x6FC - 0x6E0];
    /* 0x6FC */ void* pendingBlock;
    /* 0x700 */ u8 _700[0x714 - 0x700];
    /* 0x714 */ union {
        u16 cancelRequested;
        volatile s8 bytes[2]; // [1] is 1 once a cancel callback has run
    } cancel;
    /* 0x716 */ u8 _716;
    /* 0x717 */ u8 loadType;
    /* 0x718 */ u8 _718[0x722 - 0x718];
    /* 0x722 */ u8 unk722;
} LoadState;

extern LoadState lbl_803C6CF8;

void handleDVDCancelAndARQRemoval(void);

#endif // !__UNKNOWN_FILE_0X800A7568_H_
