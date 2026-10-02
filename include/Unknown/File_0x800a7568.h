#ifndef __UNKNOWN_FILE_0X800A7568_H_
#define __UNKNOWN_FILE_0X800A7568_H_

#include "mssbTypes.h"
#include "Dolphin/dvd.h"
#include "Dolphin/OS/OSThread.h"

typedef void (*DriveStatusHandler)(void);

/* Disk-loader state. dtk's 0x708-byte lbl_803C6CF8 label spans several
 * objects; the loader addresses all of them through this one base, so only
 * the fields in use are named. */
typedef struct {
    /* 0x000 */ OSThread readThread;
    /* 0x318 */ OSThread thread2;
    /* 0x630 */ u8 _630[0x6CC - 0x630];
    /* 0x6CC */ DriveStatusHandler* driveStatusHandlers; // indexed by DVDGetDriveStatus() + 1
    /* 0x6D0 */ u8 _6D0[0x6D8 - 0x6D0];
    /* 0x6D8 */ u8 _6D8;
    /* 0x6D9 */ u8 _6D9[0x6DC - 0x6D9];
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
    /* 0x718 */ s32 entryNum; // DVD entry number used by DVDFastOpen
    /* 0x71C */ u8 _71C[0x722 - 0x71C];
    /* 0x722 */ u8 unk722;
} LoadState;

extern LoadState lbl_803C6CF8;

void handleDVDCancelAndARQRemoval(void);

#endif // !__UNKNOWN_FILE_0X800A7568_H_
