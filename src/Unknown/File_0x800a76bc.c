#include "Unknown/File_0x800a76bc.h"
#include "Unknown/File_0x800a7568.h"
#include "Unknown/File_0x800a64e0.h"
#include "Unknown/File_0x800a6900.h"

extern DriveStatusHandler lbl_8010F420[];
void fn_800A77A0(void);

static DVDFileInfo loaderFileInfo;
static u8 readThreadStack[0x1000];
static u8 thread2Stack[0x1000];

void initializeDVDSystem(void) {
    DVDInit();
    lbl_803C6CF8.cancel.cancelRequested = 1;
    gDataDecompressorValues.pendingBlock = NULL;
    lbl_803C6CF8.pendingBlock = NULL;
    lbl_803C6CF8.fileInfo = &loaderFileInfo;
    lbl_803C6CF8.driveStatusHandlers = lbl_8010F420;
    OSCreateThread(&lbl_803C6CF8.readThread, (OSThreadStartFunction)manageFileReadingProcess, NULL,
                   readThreadStack + sizeof(readThreadStack), sizeof(readThreadStack), 14, OS_THREAD_ATTR_DETACH);
    OSResumeThread(&lbl_803C6CF8.readThread);
    OSCreateThread(&lbl_803C6CF8.thread2, (OSThreadStartFunction)fn_800A77A0, NULL,
                   thread2Stack + sizeof(thread2Stack), sizeof(thread2Stack), 8, OS_THREAD_ATTR_DETACH);
    OSResumeThread(&lbl_803C6CF8.thread2);
    lbl_803C6CF8._6D8 = 0;
}
