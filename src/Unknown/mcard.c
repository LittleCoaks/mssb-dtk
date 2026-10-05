#include "Unknown/mcard.h"
#include "Unknown/File_0x800b0a14.h"
#include "Dolphin/os.h"
#include "Dolphin/card.h"
#include "PowerPC_EABI_Support/Runtime/__mem.h"
#include "string.h"
#include "Dolphin/dvd.h"
#include "Dolphin/GX/GXTypes.h"
#include "charPipeline/texPalette.h"
#include "Unknown/File_0x800acf14.h"

/* Per-channel card information. */
typedef struct McardChannel {
    /* 0x00 */ u64 serialNo;
    /* 0x08 */ s32 probeResult;
    /* 0x0C */ s32 memSize;
    /* 0x10 */ s32 sectorSize;
    /* 0x14 */ s32 freeBlocks;
    /* 0x18 */ s32 freeBytes;
    /* 0x1C */ s32 freeFiles;
    /* 0x20 */ s32 userBlocks;
    /* 0x24 */ u8 _24[4];
} McardChannel; // size 0x28

typedef struct McardState {
    /* 0x00 */ McardChannel chan[2];
    /* 0x50 */ s32 result;
    /* 0x54 */ u8 status;
    /* 0x55 */ u8 operation;
    /* 0x56 */ u8 hasBanner;
    /* 0x57 */ u8 iconCount;
    /* 0x58 */ s32 bytesTransferred;
    /* 0x5C */ u8 progress;
    /* 0x5D */ u8 _5D[3];
} McardState; // size 0x60

/* Memory-card tasks are drawing-script nodes; the header matches
 * DrawingSceneStruct and the rest is the task's own scratch area. */
typedef struct McardTaskHeader {
    /* 0x00 */ void (*func)(void);
    /* 0x04 */ DrawingSceneStruct* prev;
    /* 0x08 */ DrawingSceneStruct* next;
    /* 0x0C */ DrawingSceneStruct* parent;
    /* 0x10 */ s16 state;
    /* 0x12 */ u16 priority;
} McardTaskHeader;

typedef struct McardTask {
    /* 0x00 */ McardTaskHeader hdr;
    /* 0x14 */ s32 step;
    /* 0x18 */ u8 chan;
    /* 0x19 */ u8 async;
} McardTask;

typedef struct McardFindTask {
    /* 0x00 */ McardTaskHeader hdr;
    /* 0x14 */ s32 step;
    /* 0x18 */ u8 chan;
    /* 0x19 */ u8 async;
    /* 0x1A */ u16 found;
    /* 0x1C */ char* fileName;
} McardFindTask;

typedef struct McardSpaceTask {
    /* 0x00 */ McardTaskHeader hdr;
    /* 0x14 */ s32 step;
    /* 0x18 */ u8 chan;
    /* 0x19 */ u8 async;
    /* 0x1A */ s16 blocksNeeded;
    /* 0x1C */ char* fileName;
    /* 0x20 */ u8 result;
} McardSpaceTask;

typedef struct McardLoadTask {
    /* 0x00 */ McardTaskHeader hdr;
    /* 0x14 */ CARDFileInfo fileInfo;
    /* 0x28 */ s32 step;
    /* 0x2C */ void* buffer;
    /* 0x30 */ s32 size;
    /* 0x34 */ char* fileName;
    /* 0x38 */ s32 fileNo;
    /* 0x3C */ u8 chan;
    /* 0x3D */ u8 async;
} McardLoadTask;

typedef struct McardSaveTask {
    /* 0x00 */ McardTaskHeader hdr;
    /* 0x14 */ CARDFileInfo fileInfo;
    /* 0x28 */ s32 step;
    /* 0x2C */ void* buffer;
    /* 0x30 */ s32 size;
    /* 0x34 */ s32 fileNo;
    /* 0x38 */ u8 chan;
    /* 0x39 */ u8 async;
    /* 0x3A */ u8 attr;
} McardSaveTask;

typedef u32 (*McardCallbackFn)(void* buffer, s32 size, u32 arg);

/* The disc's "/opening.bnr" (BNR1). */
typedef struct OpeningBnr {
    /* 0x0000 */ u32 magic;
    /* 0x0004 */ u8 _0004[0x1C];
    /* 0x0020 */ u8 pixels[CARD_BANNER_WIDTH * CARD_BANNER_HEIGHT * 2];
    /* 0x1820 */ char shortTitle[0x20];
    /* 0x1840 */ char shortMaker[0x20];
    /* 0x1860 */ char longTitle[0x40];
    /* 0x18A0 */ char longMaker[0x40];
    /* 0x18E0 */ char comment[0x80];
} OpeningBnr; // size 0x1960

extern McardState mcardState;

extern u64 mcardSerialNo[2];
extern char mcardFileName[CARD_FILENAME_MAX];
extern u8 mcardComment[0x40];
extern CARDStat mcardStat;
extern u8 mcardWorkArea[CARD_WORKAREA_SIZE];
static void* mcardSaveImage;
static s32 mcardXferStart;
static void* lbl_803CC164;
static u32 lbl_803CC160;
static McardCallbackFn mcardCallback;
static u32 mcardCallbackArg;


static const u16 crcTable[256] = {
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
    0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
    0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
    0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
    0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
    0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
    0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
    0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
    0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
    0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
    0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
    0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
    0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
    0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
    0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
    0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
    0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
    0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
    0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
    0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
    0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
    0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
    0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
    0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
    0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
    0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
    0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
    0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
    0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
    0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
    0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
    0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0,
};

void mcardDeleteTask(void);
void mcardDeleteFileTask(void);
void mcardFormatTask(void);
void mcardCheckFileTask(void);
void mcardLoadTask(void);
void mcardSaveTask(void);
void mcardCheckSpaceTask(void);
void mcardProbeTask(void);
void mcardReadTask(void);
void mcardWriteTask(void);
void mcardSetResult(s32 result);

static inline int mcardStatusKind(void) {
    if (mcardState.status == 0xF) {
        return 0;
    }
    if (mcardState.status != 0x11) {
        return 2;
    }
    return 1;
}

static inline McardChannel* mcardChannelAt(s32 offset) {
    return (McardChannel*)((u8*)mcardState.chan + offset);
}

static inline int mcardProbe(s32 chan) {
    mcardSetResult(CARDUnmount(chan));
    /* From here on chan holds the byte offset of the channel's entry. */
    mcardSetResult(mcardChannelAt(chan *= sizeof(McardChannel))->probeResult);
    if (mcardState.status == 0xF) {
        return 0;
    }
    if (mcardState.status != 0x11) {
        return 2;
    }
    mcardSetResult(mcardChannelAt(chan)->sectorSize == 0x2000 ? 0 : -0x81);
    return mcardStatusKind();
}

static inline s32 mcardReadSerialNo(u8 chan) {
    u64 serialNo = 0;
    s32 result = CARDGetSerialNo(chan, &serialNo);

    mcardState.chan[chan].serialNo = serialNo;
    return result;
}

static inline BOOL mcardMount(s32 chan, s32 async) {
    s32 result;

    if (async == TRUE) {
        result = CARDMountAsync(chan, (CARDMemoryCard*)mcardWorkArea, NULL, NULL);
        if (result == CARD_RESULT_BUSY) {
            return TRUE;
        }
    } else {
        result = CARDMount(chan, (CARDMemoryCard*)mcardWorkArea, NULL);
    }
    mcardSetResult(result);
    return FALSE;
}

static inline BOOL mcardCheck(s32 chan, s32 async) {
    s32 result;

    if (async == TRUE) {
        result = CARDCheckAsync(chan, NULL);
        if (result == CARD_RESULT_BUSY) {
            return TRUE;
        }
    } else {
        result = CARDCheck(chan);
    }
    mcardSetResult(result);
    return FALSE;
}

static inline BOOL mcardDoFormat(s32 chan, s32 async) {
    s32 result;

    if (async == TRUE) {
        result = CARDFormatAsync(chan, NULL);
        if (result == CARD_RESULT_BUSY) {
            return TRUE;
        }
    } else {
        result = CARDFormat(chan);
    }
    mcardSetResult(result);
    return FALSE;
}

static inline int mcardFileExists(s32 chan, char* fileName) {
    CARDFileInfo fileInfo;
    char name[CARD_FILENAME_MAX + 1];
    s32 result;
    int found;

    strncpy(name, fileName, CARD_FILENAME_MAX);
    name[CARD_FILENAME_MAX] = '\0';
    if (strlen(name) >= CARD_FILENAME_MAX) {
        OSPanic("mcard.c", 0x1FE, "MemoryCard FileName Error!!");
    }
    result = CARDOpen(chan, fileName, &fileInfo);
    switch (result) {
    case CARD_RESULT_READY:
        mcardState.status = 8;
        found = 0;
        CARDClose(&fileInfo);
        break;
    case CARD_RESULT_NOFILE:
        found = 1;
        break;
    default:
        mcardSetResult(result);
        found = 2;
        break;
    }
    return found;
}

static inline void mcardEndTask(s16 result) {
    currentDrawingItem->currentDrawingItem->state = result;
    removeCurrentDrawingItem();
}

static inline void mcardUpdateProgress(s32 chan, s32 size) {
    s32 transferred = CARDGetXferredBytes(chan) - mcardXferStart;

    mcardState.bytesTransferred = transferred;
    mcardState.progress = transferred * 100 / size;
    if (mcardState.progress > 100) {
        mcardState.progress = 100;
    }
}

static inline BOOL mcardSetAttributes(s32 chan, s32 fileNo, u8 attr, s32 async) {
    s32 result;

    if (async == TRUE) {
        result = CARDSetAttributesAsync(chan, fileNo, attr, NULL);
        if (result == CARD_RESULT_BUSY) {
            return TRUE;
        }
    } else {
        result = CARDSetAttributes(chan, fileNo, attr);
    }
    mcardSetResult(result);
    return FALSE;
}

void mcardDelete(u8 chan, u8 async, u64 serialNo) {
    McardTask* task;

    mcardState.operation = 6;
    task = (McardTask*)insertGraphicDrawingFunction(mcardDeleteTask, 0xFF);
    memset(&task->step, 0, 0x2C);
    task->chan = chan;
    task->async = async;
    mcardSerialNo[chan] = serialNo;
    currentDrawingItem->state = 0;
}

void mcardDeleteTask(void) {
    McardTask* task = (McardTask*)currentDrawingItem;
    McardTask* child;

    switch (task->step) {
    case 0:
        switch (mcardProbe(task->chan)) {
        case 0:
            break;
        case 1:
            task->step = 1;
            break;
        case 2:
            task->step = 9;
            break;
        }
        break;
    case 1:
        if (!mcardMount(task->chan, task->async)) {
            task->step = 2;
        }
        break;
    case 2:
        mcardSetResult(CARDGetResultCode(task->chan));
        switch (mcardState.status) {
        case 0xF:
            break;
        case 1:
        case 2:
        case 0x11:
            task->step = 3;
            break;
        default:
            task->step = 9;
            break;
        }
        break;
    case 3:
        if (!mcardCheck(task->chan, task->async)) {
            task->step = 4;
        }
        break;
    case 4:
        mcardSetResult(CARDGetResultCode(task->chan));
        switch (mcardState.status) {
        case 0xF:
            break;
        default:
            task->step = 5;
            break;
        }
        break;
    case 5:
        if (mcardState.status == 0x11) {
            if (mcardReadSerialNo(task->chan) != CARD_RESULT_BUSY) {
                if (mcardState.chan[task->chan].serialNo == mcardSerialNo[task->chan]) {
                    task->step = 6;
                } else {
                    mcardState.status = 0x10;
                    task->step = 9;
                }
            }
        } else {
            task->step = 6;
        }
        break;
    case 6:
        child = (McardTask*)insertGraphicDrawingFunction(mcardDeleteFileTask, 0xFF);
        memset(&child->step, 0, 0x2C);
        currentDrawingItem->state = 0;
        task->step = 7;
        break;
    case 7:
        switch (task->hdr.state) {
        case 0:
            break;
        case 1:
            task->step = 8;
            break;
        case 2:
            task->step = 9;
            break;
        }
        break;
    case 8:
        mcardSetResult(CARDUnmount(task->chan));
        switch (mcardState.status) {
        case 0xF:
            break;
        case 0x11:
            task->step = 10;
            break;
        case 0x10:
        default:
            task->step = 9;
            break;
        }
        break;
    case 9:
        task->step = 10;
        break;
    case 10:
        task->hdr.parent->state = 1;
        removeCurrentDrawingItem();
        break;
    }
}

void mcardDeleteFileTask(void) {
    McardTask* task = (McardTask*)currentDrawingItem;
    char* fileName = mcardStat.fileName;
    McardTask* parent = (McardTask*)task->hdr.parent;
    s32 result;

    switch (task->step) {
    case 0:
        if (parent->async == TRUE) {
            result = CARDDeleteAsync(parent->chan, fileName, NULL);
            if (result < 0) {
                mcardSetResult(result);
                task->step = 3;
            } else {
                task->step += 1;
            }
        } else {
            result = CARDDelete(parent->chan, fileName);
            if (result < 0) {
                mcardSetResult(result);
                task->step = 3;
            } else {
                task->step += 2;
            }
        }
        break;
    case 1:
        mcardSetResult(CARDGetResultCode(parent->chan));
        switch (currentDrawingItem->state) {
        case 0xF:
            break;
        case 0x11:
            task->step += 1;
            break;
        case 0x10:
        default:
            task->step = 3;
            break;
        }
        break;
    case 2:
        parent->hdr.state = 1;
        removeCurrentDrawingItem();
        break;
    case 3:
        parent->hdr.state = 2;
        removeCurrentDrawingItem();
        break;
    }
}

void mcardFormat(u8 chan, u8 async, u64 serialNo) {
    McardTask* task;

    mcardState.operation = 4;
    task = (McardTask*)insertGraphicDrawingFunction(mcardFormatTask, 0xFF);
    memset(&task->step, 0, 0x2C);
    task->chan = chan;
    task->async = async;
    mcardSerialNo[chan] = serialNo;
    currentDrawingItem->state = 0;
}

void mcardFormatTask(void) {
    McardTask* task = (McardTask*)currentDrawingItem;

    switch (task->step) {
    case 0:
        switch (mcardProbe(task->chan)) {
        case 0:
            break;
        case 1:
            task->step = 1;
            break;
        case 2:
            task->step = 9;
            break;
        }
        break;
    case 1:
        if (!mcardMount(task->chan, task->async)) {
            task->step = 2;
        }
        break;
    case 2:
        mcardSetResult(CARDGetResultCode(task->chan));
        switch (mcardState.status) {
        case 0xF:
            break;
        case 1:
        case 2:
        case 0x11:
            task->step = 3;
            break;
        default:
            task->step = 9;
            break;
        }
        break;
    case 3:
        if (!mcardCheck(task->chan, task->async)) {
            task->step = 4;
        }
        break;
    case 4:
        mcardSetResult(CARDGetResultCode(task->chan));
        switch (mcardState.status) {
        case 0xF:
            break;
        default:
            task->step = 5;
            break;
        }
        break;
    case 5:
        if (mcardState.status == 0x11) {
            if (mcardReadSerialNo(task->chan) != CARD_RESULT_BUSY) {
                if (mcardState.chan[task->chan].serialNo == mcardSerialNo[task->chan]) {
                    task->step = 6;
                } else {
                    mcardState.status = 0x10;
                    task->step = 9;
                }
            }
        } else {
            task->step = 6;
        }
        break;
    case 6:
        if (!mcardDoFormat(task->chan, task->async)) {
            task->step = 7;
        }
        break;
    case 7:
        mcardSetResult(CARDGetResultCode(task->chan));
        switch (mcardState.status) {
        case 0xF:
            break;
        case 0x11:
            mcardReadSerialNo(task->chan);
            task->step = 8;
            break;
        case 3:
            mcardState.status = 0xD;
            task->step = 9;
            break;
        default:
            mcardState.status = 0xC;
            task->step = 9;
            break;
        }
        break;
    case 8:
        mcardSetResult(CARDUnmount(task->chan));
        switch (mcardState.status) {
        case 0xF:
            break;
        case 0x11:
            task->step = 10;
            break;
        case 0x10:
        default:
            task->step = 9;
            break;
        }
        break;
    case 9:
        task->step = 10;
        break;
    case 10:
        task->hdr.parent->state = 1;
        removeCurrentDrawingItem();
        break;
    }
}

void mcardCheckFile(u8 chan, u8 async, const char* fileName, u64 serialNo, u8 useSerialNo) {
    char name[CARD_FILENAME_MAX + 1];
    McardFindTask* task;

    mcardState.operation = 5;
    strncpy(name, fileName, CARD_FILENAME_MAX);
    name[CARD_FILENAME_MAX] = '\0';
    if (strlen(name) >= CARD_FILENAME_MAX) {
        OSPanic("mcard.c", 0xA6A, "MemoryCard FileName Error!!");
    }
    task = (McardFindTask*)insertGraphicDrawingFunction(mcardCheckFileTask, 0xFF);
    memset(&task->step, 0, 0x2C);
    task->chan = chan;
    task->async = async;
    task->fileName = mcardFileName;
    memcpy(task->fileName, fileName, CARD_FILENAME_MAX);
    if (useSerialNo) {
        mcardSerialNo[chan] = serialNo;
    }
    currentDrawingItem->state = 0;
}

void mcardCheckFileTask(void) {
    McardFindTask* task = (McardFindTask*)currentDrawingItem;

    switch (task->step) {
    case 0:
        switch (mcardProbe(task->chan)) {
        case 0:
            break;
        case 1:
            task->step = 1;
            break;
        case 2:
            task->step = 8;
            break;
        }
        break;
    case 1:
        if (!mcardMount(task->chan, task->async)) {
            task->step = 2;
        }
        break;
    case 2:
        mcardSetResult(CARDGetResultCode(task->chan));
        switch (mcardState.status) {
        case 0xF:
            break;
        case 1:
        case 2:
        case 0x11:
            task->step = 3;
            break;
        default:
            task->step = 8;
            break;
        }
        break;
    case 3:
        if (!mcardCheck(task->chan, task->async)) {
            task->step = 4;
        }
        break;
    case 4:
        mcardSetResult(CARDGetResultCode(task->chan));
        switch (mcardState.status) {
        case 0xF:
            break;
        case 0x11:
            task->step = 5;
            break;
        case 0x10:
        default:
            task->step = 8;
            break;
        }
        break;
    case 5:
        if (mcardState.status == 0x11) {
            if (mcardReadSerialNo(task->chan) != CARD_RESULT_BUSY) {
                if (mcardState.chan[task->chan].serialNo != 0) {
                    if (mcardSerialNo[task->chan] == 0) {
                        task->step = 6;
                    } else if (mcardState.chan[task->chan].serialNo == mcardSerialNo[task->chan]) {
                        task->step = 6;
                    } else {
                        mcardState.status = 0x10;
                        task->step = 8;
                    }
                } else {
                    task->step = 8;
                }
            }
        } else {
            task->step = 8;
        }
        break;
    case 6:
        switch (mcardFileExists(task->chan, task->fileName)) {
        case 0:
            task->found = 1;
            task->step = 7;
            break;
        case 1:
            task->step = 7;
            break;
        case 2:
            task->step = 8;
            break;
        }
        break;
    case 7:
        mcardSetResult(CARDUnmount(task->chan));
        switch (mcardState.status) {
        case 0xF:
            break;
        case 0x11:
            if (task->found == 1) {
                mcardState.status = 8;
            }
            task->step = 8;
            break;
        case 0x10:
        default:
            task->step = 8;
            break;
        }
        break;
    case 8:
        task->hdr.parent->state = 1;
        removeCurrentDrawingItem();
        break;
    }
}

void mcardLoad(McardRequest* req, int arg1, u64 serialNo) {
    char name[CARD_FILENAME_MAX + 1];
    McardLoadTask* task;

    if (req->size % CARD_READ_SIZE != 0) {
        OSPanic("mcard.c", 0x970, "MemoryCard LoadSize Error!!");
    }
    strncpy(name, req->fileName, CARD_FILENAME_MAX);
    name[CARD_FILENAME_MAX] = '\0';
    if (strlen(name) >= CARD_FILENAME_MAX) {
        OSPanic("mcard.c", 0x979, "MemoryCard FileName Error!!");
    }
    task = (McardLoadTask*)insertGraphicDrawingFunction(mcardLoadTask, 0xFF);
    task->chan = req->chan;
    task->async = req->async;
    task->buffer = req->buffer;
    task->size = req->size;
    task->fileName = mcardFileName;
    memcpy(task->fileName, req->fileName, CARD_FILENAME_MAX);
    mcardSerialNo[req->chan] = serialNo;
    mcardCallback = req->callback;
    mcardCallbackArg = req->callbackArg;
    lbl_803CC160 = req->flags;
    currentDrawingItem->state = 0;
}

void mcardLoadTask(void) {
    McardLoadTask* task = (McardLoadTask*)currentDrawingItem;
    McardTask* child;
    McardCallbackFn callback;
    u32 result;

    switch (task->step) {
    case 0:
        switch (mcardProbe(task->chan)) {
        case 0:
            break;
        case 1:
            task->step = 1;
            break;
        case 2:
            task->step = 9;
            break;
        }
        break;
    case 1:
        if (!mcardMount(task->chan, task->async)) {
            task->step = 2;
        }
        break;
    case 2:
        mcardSetResult(CARDGetResultCode(task->chan));
        switch (mcardState.status) {
        case 0xF:
            break;
        case 1:
        case 2:
        case 0x11:
            task->step = 3;
            break;
        default:
            task->step = 9;
            break;
        }
        break;
    case 3:
        if (!mcardCheck(task->chan, task->async)) {
            task->step = 4;
        }
        break;
    case 4:
        mcardSetResult(CARDGetResultCode(task->chan));
        switch (mcardState.status) {
        case 0xF:
            break;
        case 0x11:
            task->step = 5;
            break;
        case 0x10:
        default:
            task->step = 9;
            break;
        }
        break;
    case 5:
        if (mcardState.status == 0x11) {
            if (mcardReadSerialNo(task->chan) != CARD_RESULT_BUSY) {
                if (mcardState.chan[task->chan].serialNo != 0) {
                    if (mcardState.chan[task->chan].serialNo == mcardSerialNo[task->chan]) {
                        task->step = 6;
                    } else {
                        mcardState.status = 0x10;
                        task->step = 9;
                    }
                } else {
                    mcardState.status = 0x10;
                    task->step = 9;
                }
            }
        } else {
            task->step = 9;
        }
        break;
    case 6:
        child = (McardTask*)insertGraphicDrawingFunction(mcardReadTask, 0xFF);
        memset(&child->step, 0, 0x2C);
        task->step = 7;
        currentDrawingItem->state = 0;
        break;
    case 7:
        switch (task->hdr.state) {
        case 0:
            break;
        case 1:
            callback = mcardCallback;
            if (callback != NULL && (result = callback(task->buffer, task->size, mcardCallbackArg)) != 0x11) {
                mcardState.status = result;
            } else {
                task->step = 8;
                break;
            }
        case 2:
            task->step = 9;
            break;
        }
        break;
    case 8:
        mcardSetResult(CARDUnmount(task->chan));
        switch (mcardState.status) {
        case 0xF:
            break;
        case 0x11:
            task->step = 9;
            break;
        case 0x10:
        default:
            task->step = 9;
            break;
        }
        break;
    case 9:
        task->hdr.parent->state = 1;
        removeCurrentDrawingItem();
        break;
    }
}

void memoryCardRelatedFunction(McardRequest* req, int arg1, u64 serialNo) {
    McardSaveTask* task;
    u8 attr;

    if (req->size % CARD_READ_SIZE != 0) {
        OSPanic("mcard.c", 0x822, "MemoryCard SaveSize Error!!");
    }
    mcardState.operation = 1;
    task = (McardSaveTask*)insertGraphicDrawingFunction(mcardSaveTask, 0xFF);
    task->chan = req->chan;
    task->async = req->async;
    task->buffer = req->buffer;
    task->size = req->size;
    attr = req->attr;
    if (attr == 0) {
        attr = CARD_ATTR_PUBLIC;
    }
    task->attr = attr;
    mcardSerialNo[task->chan] = serialNo;
    mcardCallback = req->callback;
    mcardCallbackArg = req->callbackArg;
    lbl_803CC160 = req->flags;
    currentDrawingItem->state = 0;
}

static BOOL mcardLoadOpeningBnr(OpeningBnr* bnr) {
    DVDFileInfo fileInfo;

    if (!DVDOpen("/opening.bnr", &fileInfo)) {
        return FALSE;
    }
    if (OSRoundUp32B(fileInfo.length) < sizeof(OpeningBnr)) {
        return FALSE;
    }
    if (DVDReadPrio(&fileInfo, bnr, sizeof(OpeningBnr), 0, 2) == 0) {
        return FALSE;
    }
    if (bnr->magic != 'BNR1') {
        return FALSE;
    }
    return TRUE;
}

static void UnpackTexPalette(TEXPalettePtr pal) {
    u16 i;

    if (pal->versionNumber != 2142000) {
        OSPanic("mcard.c", 0x52F, "invalid version number for texture palette");
    }
    pal->descriptorArray = (TEXDescriptorPtr)((u32)pal->descriptorArray + (u32)pal);
    for (i = 0; i < pal->numDescriptors; i++) {
        if (pal->descriptorArray[i].textureHeader) {
            pal->descriptorArray[i].textureHeader =
                (TEXHeaderPtr)((u32)pal->descriptorArray[i].textureHeader + (u32)pal);
            if (!pal->descriptorArray[i].textureHeader->unpacked) {
                pal->descriptorArray[i].textureHeader->data =
                    (Ptr)((u32)pal->descriptorArray[i].textureHeader->data + (u32)pal);
                pal->descriptorArray[i].textureHeader->unpacked = TRUE;
            }
        }
        if (pal->descriptorArray[i].CLUTHeader) {
            pal->descriptorArray[i].CLUTHeader =
                (CLUTHeaderPtr)((u32)pal->descriptorArray[i].CLUTHeader + (u32)pal);
            if (!pal->descriptorArray[i].CLUTHeader->unpacked) {
                pal->descriptorArray[i].CLUTHeader->data =
                    (Ptr)((u32)pal->descriptorArray[i].CLUTHeader->data + (u32)pal);
                pal->descriptorArray[i].CLUTHeader->unpacked = TRUE;
            }
        }
    }
}

void mcardSaveTask(void) {
    McardSaveTask* task = (McardSaveTask*)currentDrawingItem;
    McardTask* child;
    McardCallbackFn callback;
    u32 result;

    switch (task->step) {
    case 0:
        switch (mcardProbe(task->chan)) {
        case 0:
            break;
        case 1:
            task->step = 1;
            break;
        case 2:
            task->step = 9;
            break;
        }
        break;
    case 1:
        if (!mcardMount(task->chan, task->async)) {
            task->step = 2;
        }
        break;
    case 2:
        mcardSetResult(CARDGetResultCode(task->chan));
        switch (mcardState.status) {
        case 0xF:
            break;
        case 1:
        case 2:
        case 0x11:
            task->step = 3;
            break;
        default:
            task->step = 9;
            break;
        }
        break;
    case 3:
        if (!mcardCheck(task->chan, task->async)) {
            task->step = 4;
        }
        break;
    case 4:
        mcardSetResult(CARDGetResultCode(task->chan));
        switch (mcardState.status) {
        case 0xF:
            break;
        case 0x11:
            task->step = 5;
            break;
        case 0x10:
        default:
            task->step = 9;
            break;
        }
        break;
    case 5:
        if (mcardState.status == 0x11) {
            if (mcardReadSerialNo(task->chan) != CARD_RESULT_BUSY) {
                if (mcardState.chan[task->chan].serialNo != 0) {
                    if (mcardState.chan[task->chan].serialNo == mcardSerialNo[task->chan]) {
                        task->step = 6;
                    } else {
                        mcardState.status = 0x10;
                        task->step = 9;
                    }
                } else {
                    mcardState.status = 0x10;
                    task->step = 9;
                }
            }
        } else {
            task->step = 9;
        }
        break;
    case 6:
        callback = mcardCallback;
        if (callback != NULL && (result = callback(task->buffer, task->size, mcardCallbackArg)) != 0x11) {
            mcardState.status = result;
            task->step = 9;
        } else {
            child = (McardTask*)insertGraphicDrawingFunction(mcardWriteTask, 0xFF);
            memset(&child->step, 0, 0x2C);
            task->step = 7;
            currentDrawingItem->state = 0;
        }
        break;
    case 7:
        switch (task->hdr.state) {
        case 0:
            break;
        case 1:
            task->step = 8;
            break;
        case 2:
            task->step = 9;
            break;
        }
        break;
    case 8:
        mcardSetResult(CARDUnmount(task->chan));
        switch (mcardState.status) {
        case 0xF:
            break;
        case 0x11:
            task->step = 9;
            break;
        case 0x10:
        default:
            task->step = 9;
            break;
        }
        break;
    case 9:
        fn_800ACFB0(mcardSaveImage);
        mcardEndTask(1);
        break;
    }
}

void mcardCheckSpace(u8 chan, u8 async, s16 blocksNeeded, const char* fileName, u64 serialNo) {
    McardSpaceTask* task;

    mcardState.operation = 3;
    task = (McardSpaceTask*)insertGraphicDrawingFunction(mcardCheckSpaceTask, 0xFF);
    memset(&task->step, 0, 0x2C);
    task->chan = chan;
    task->async = async;
    task->blocksNeeded = blocksNeeded;
    task->fileName = mcardFileName;
    memcpy(task->fileName, fileName, CARD_FILENAME_MAX);
    mcardSerialNo[chan] = serialNo;
    currentDrawingItem->state = 0;
}

void mcardCheckSpaceTask(void) {
    McardSpaceTask* task = (McardSpaceTask*)currentDrawingItem;
    McardChannel* info;
    s32 result;
    u8 chan;

    switch (task->step) {
    case 0:
        switch (mcardProbe(task->chan)) {
        case 0:
            break;
        case 1:
            task->step = 1;
            break;
        case 2:
            task->step = 9;
            break;
        }
        break;
    case 1:
        if (!mcardMount(task->chan, task->async)) {
            task->step = 2;
        }
        break;
    case 2:
        mcardSetResult(CARDGetResultCode(task->chan));
        switch (mcardState.status) {
        case 0xF:
            break;
        case 1:
        case 2:
        case 0x11:
            task->step = 3;
            break;
        default:
            task->step = 9;
            break;
        }
        break;
    case 3:
        if (!mcardCheck(task->chan, task->async)) {
            task->step = 4;
        }
        break;
    case 4:
        mcardSetResult(CARDGetResultCode(task->chan));
        switch (mcardState.status) {
        case 0xF:
            break;
        case 0x11:
            task->step = 5;
            break;
        case 0x10:
        default:
            task->step = 9;
            break;
        }
        break;
    case 5:
        if (mcardState.status == 0x11) {
            if (mcardReadSerialNo(task->chan) != CARD_RESULT_BUSY) {
                if (mcardState.chan[task->chan].serialNo != 0) {
                    if (mcardState.chan[task->chan].serialNo == mcardSerialNo[task->chan]) {
                        task->step = 6;
                    } else {
                        mcardState.status = 0x10;
                        task->step = 9;
                    }
                } else {
                    mcardState.status = 0x10;
                    task->step = 9;
                }
            }
        } else {
            task->step = 9;
        }
        break;
    case 6:
        switch (mcardFileExists(task->chan, task->fileName)) {
        case 0:
            task->result = 0;
            task->step = 8;
            break;
        case 1:
            task->step = 7;
            break;
        case 2:
            task->step = 9;
            break;
        }
        break;
    case 7:
        chan = task->chan;
        result = CARDFreeBlocks(chan, &mcardState.chan[chan].freeBytes, &mcardState.chan[chan].freeFiles);
        if (result >= 0) {
            mcardState.chan[chan].freeBlocks = mcardState.chan[chan].freeBytes / mcardState.chan[chan].sectorSize;
            mcardState.chan[chan].userBlocks =
                ((mcardState.chan[chan].memSize << 20) / 8) / mcardState.chan[chan].sectorSize - CARD_NUM_SYSTEM_BLOCK;
        }
        mcardSetResult(result);
        switch (mcardState.status) {
        case 0xF:
            break;
        case 0x11:
            info = &mcardState.chan[task->chan];
            if (info->freeFiles == 0) {
                task->result = 1;
            } else if (task->blocksNeeded > info->freeBlocks) {
                task->result = 2;
            } else {
                task->result = 0;
            }
            task->step = 8;
            break;
        case 0x10:
        default:
            task->step = 9;
            break;
        }
        break;
    case 8:
        mcardSetResult(CARDUnmount(task->chan));
        switch (mcardState.status) {
        case 0xF:
            break;
        case 0x11:
            switch (task->result) {
            case 1:
                mcardState.status = 5;
                break;
            case 2:
                mcardState.status = 6;
                break;
            }
            task->step = 9;
            break;
        case 0x10:
        default:
            task->step = 9;
            break;
        }
        break;
    case 9:
        task->hdr.parent->state = 1;
        removeCurrentDrawingItem();
        break;
    }
}

u16 mcardCrc16(u8* data, s32 length) {
    u16 crc = 0xFFFF;

    while (--length >= 0) {
        crc = (crc << 8) ^ crcTable[(crc >> 8) ^ *data++];
    }
    return ~crc;
}

static inline u16 mcardChecksum(s32 length, u8* data) {
    u16 crc = 0xFFFF;

    while (--length >= 0) {
        crc = (crc << 8) ^ crcTable[(crc >> 8) ^ *data++];
    }
    return ~crc;
}

void mcardProbeTask(void) {
    int i;

    if (mcardState.operation == 7) {
        removeCurrentDrawingItem();
    } else {
        for (i = 0; i < 2; i++) {
            mcardState.chan[i].probeResult =
                CARDProbeEx(i, &mcardState.chan[i].memSize, &mcardState.chan[i].sectorSize);
        }
    }
}

void mcardReadTask(void) {
    McardTask* task = (McardTask*)currentDrawingItem;
    CARDStat* stat = &mcardStat;
    McardLoadTask* parent = (McardLoadTask*)task->hdr.parent;
    s32 result;
    u8* buffer;

    switch (task->step) {
    case 0:
        result = CARDOpen(parent->chan, parent->fileName, &parent->fileInfo);
        if (result == CARD_RESULT_READY) {
            parent->fileNo = parent->fileInfo.fileNo;
        } else {
            mcardSetResult(result);
            mcardEndTask(2);
            break;
        }
        result = CARDGetStatus(parent->chan, parent->fileNo, stat);
        if (result == CARD_RESULT_READY) {
            if (stat->iconAddr == 0xFFFFFFFF || stat->commentAddr == 0xFFFFFFFF) {
                mcardSetResult(CARD_RESULT_CANCELED);
                mcardState.status = 0xB;
                mcardEndTask(2);
                break;
            }
        } else {
            mcardSetResult(result);
            mcardEndTask(2);
            break;
        }
        task->step++;
        break;
    case 1:
        mcardXferStart = CARDGetXferredBytes(parent->chan);
        if (parent->async == TRUE) {
            result = CARDReadAsync(&parent->fileInfo, parent->buffer, parent->size, stat->offsetData, NULL);
            if (result < 0) {
                mcardSetResult(result);
                CARDClose(&parent->fileInfo);
                mcardEndTask(2);
            } else {
                task->step++;
            }
        } else {
            result = CARDRead(&parent->fileInfo, parent->buffer, parent->size, stat->offsetData);
            CARDClose(&parent->fileInfo);
            if (result < 0) {
                mcardSetResult(result);
                mcardEndTask(2);
            } else {
                task->step += 2;
            }
        }
        break;
    case 2:
        mcardUpdateProgress(parent->chan, parent->size);
        mcardSetResult(CARDGetResultCode(parent->chan));
        switch (mcardState.status) {
        case 0xF:
            break;
        case 0x11:
            CARDClose(&parent->fileInfo);
            task->step++;
            break;
        case 0x10:
        default:
            CARDClose(&parent->fileInfo);
            mcardEndTask(2);
            break;
        }
        break;
    case 3:
        if (!(lbl_803CC160 & 1)) {
            buffer = parent->buffer;
            if (*(u16*)(buffer + 0x40) != mcardChecksum(parent->size - 0x44, buffer + 0x44)) {
                mcardState.status = 0xB;
                task->hdr.parent->state = 2;
                removeCurrentDrawingItem();
                break;
            }
        }
        task->step++;
    case 4:
        mcardEndTask(1);
        break;
    }
}

void mcardWriteTask(void) {
    McardTask* task = (McardTask*)currentDrawingItem;
    McardSaveTask* parent = (McardSaveTask*)task->hdr.parent;
    CARDStat* stat = &mcardStat;
    u8* buffer;
    char name[CARD_FILENAME_MAX + 1];
    s32 result;

    if (mcardState.chan[parent->chan].probeResult == CARD_RESULT_NOCARD) {
        task->step = 10;
    }
    switch (task->step) {
    case 0:
        buffer = parent->buffer;
        memcpy(buffer, mcardComment, sizeof(mcardComment));
        if (!(lbl_803CC160 & 1)) {
            *(u16*)(buffer + 0x40) = mcardChecksum(parent->size - 0x44, (u8*)parent->buffer + 0x44);
        }
        memcpy(lbl_803CC164, parent->buffer, parent->size);
        if (stat->commentAddr + parent->size > stat->length) {
            OSPanic("mcard.c", 0x3A4, "MemoryCard SizeOver Error!!");
        }
        strncpy(name, stat->fileName, CARD_FILENAME_MAX);
        name[CARD_FILENAME_MAX] = '\0';
        if (strlen(name) >= CARD_FILENAME_MAX) {
            OSPanic("mcard.c", 0x3AA, "MemoryCard FileName Error!!");
        }
        result = CARDOpen(parent->chan, stat->fileName, &parent->fileInfo);
        switch (result) {
        case CARD_RESULT_NOFILE:
            task->step++;
            break;
        case CARD_RESULT_READY:
            task->step += 3;
            break;
        default:
            mcardSetResult(result);
            task->step = 10;
            break;
        }
        break;
    case 1:
        if (parent->async == TRUE) {
            result = CARDCreateAsync(parent->chan, stat->fileName, stat->length, &parent->fileInfo, NULL);
            if (result < 0) {
                mcardSetResult(result);
                CARDClose(&parent->fileInfo);
                task->step = 10;
            } else {
                task->step++;
            }
        } else {
            result = CARDCreate(parent->chan, stat->fileName, stat->length, &parent->fileInfo);
            if (result < 0) {
                mcardSetResult(result);
                CARDClose(&parent->fileInfo);
                task->step = 10;
            } else {
                task->step += 2;
            }
        }
        break;
    case 2:
        mcardSetResult(CARDGetResultCode(parent->chan));
        switch (mcardState.status) {
        case 0xF:
            break;
        case 0x11:
            task->step++;
            break;
        case 0x10:
        default:
            CARDClose(&parent->fileInfo);
            task->step = 10;
            break;
        }
        break;
    case 3:
        mcardXferStart = CARDGetXferredBytes(parent->chan);
        parent->fileNo = parent->fileInfo.fileNo;
        if (parent->async == TRUE) {
            result = CARDWriteAsync(&parent->fileInfo, mcardSaveImage, stat->length, 0, NULL);
            if (result < 0) {
                mcardSetResult(result);
                CARDClose(&parent->fileInfo);
                task->step = 10;
            } else {
                task->step++;
            }
        } else {
            result = CARDWrite(&parent->fileInfo, mcardSaveImage, stat->length, 0);
            CARDClose(&parent->fileInfo);
            if (result < 0) {
                mcardSetResult(result);
                task->step = 10;
            } else {
                task->step += 2;
            }
        }
        break;
    case 4:
        mcardUpdateProgress(parent->chan, stat->length);
        mcardSetResult(CARDGetResultCode(parent->chan));
        switch (mcardState.status) {
        case 0xF:
            break;
        case 0x11:
            CARDClose(&parent->fileInfo);
            task->step++;
            break;
        case 0x10:
        default:
            CARDClose(&parent->fileInfo);
            task->step = 10;
            break;
        }
        break;
    case 5:
        if (parent->async == TRUE) {
            result = CARDSetStatusAsync(parent->chan, parent->fileNo, stat, NULL);
            if (result < 0) {
                mcardSetResult(result);
                task->step = 10;
            } else {
                task->step++;
            }
        } else {
            result = CARDSetStatus(parent->chan, parent->fileNo, stat);
            if (result < 0) {
                mcardSetResult(result);
                task->step = 10;
            } else {
                task->step += 2;
            }
        }
        break;
    case 6:
        mcardSetResult(CARDGetResultCode(parent->chan));
        switch (mcardState.status) {
        case 0xF:
            break;
        case 0x11:
            task->step++;
            break;
        case 0x10:
        default:
            task->step = 10;
            break;
        }
        break;
    case 7:
        if (!mcardSetAttributes(parent->chan, parent->fileNo, parent->attr, parent->async)) {
            task->step++;
        }
        break;
    case 8:
        mcardSetResult(CARDGetResultCode(parent->chan));
        switch (mcardState.status) {
        case 0xF:
            break;
        case 0x11:
            task->step = 9;
            break;
        case 0x10:
        default:
            task->step = 10;
            break;
        }
        break;
    case 9:
        mcardEndTask(1);
        break;
    case 10:
        mcardEndTask(2);
        break;
    }
}

void processBannerImage(const char* fileName, void* banner, s32 bannerSize, void* icon, s32 iconSize,
                        u32 iconSpeed, u32 animType, const char* title, const char* comment, s32 blocks) {
    u16 speed;
    TEXPalettePtr pal;
    int i;
    char* header;
    TEXDescriptorPtr desc;
    OpeningBnr* openingBnr = NULL;
    u8* dst;
    CARDStat* stat;
    s16 hasClut;

    memset(&mcardStat, 0, 0x6C);
    stat = &mcardStat;
    stat->length = blocks * 0x2000;
    mcardSaveImage = _OSAllocFromHeap(0x20, stat->length);
    memset(mcardSaveImage, 0, stat->length);
    strncpy(mcardStat.fileName, fileName, CARD_FILENAME_MAX);
    if ((banner == NULL && bannerSize == 0) || title == NULL) {
        openingBnr = _OSAllocFromHeap(0x20, sizeof(OpeningBnr));
        if (!mcardLoadOpeningBnr(openingBnr)) {
            OSPanic("mcard.c", 0x2F4, "\"opening.bnr\" is not found in the root directory.\n");
        }
    }
    header = (char*)mcardComment;
    memset(header, 0, 4);
    if (title == NULL) {
        strncpy(header, openingBnr->shortTitle, 0x1F);
    } else {
        strncpy(header, title, 0x1F);
    }
    memset(header + 0x20, 0, 4);
    strncpy(header + 0x20, comment, 0x1F);
    mcardStat.iconAddr = 0;
    dst = mcardSaveImage;
    if (banner == NULL) {
        if (bannerSize == 0) {
            mcardStat.bannerFormat = CARD_STAT_BANNER_RGB5A3;
            memcpy(dst, openingBnr->pixels, CARD_BANNER_WIDTH * CARD_BANNER_HEIGHT * 2);
            mcardState.hasBanner = TRUE;
            dst += CARD_BANNER_WIDTH * CARD_BANNER_HEIGHT * 2;
        }
    } else {
        pal = _OSAllocFromHeap(0x20, bannerSize);
        memcpy(pal, banner, bannerSize);
        UnpackTexPalette(pal);
        desc = TEXGet(pal, 0);
        switch (desc->textureHeader->format) {
        case GX_TF_RGB5A3:
            mcardStat.bannerFormat = CARD_STAT_BANNER_RGB5A3;
            memcpy(dst, desc->textureHeader->data, CARD_BANNER_WIDTH * CARD_BANNER_HEIGHT * 2);
            dst += CARD_BANNER_WIDTH * CARD_BANNER_HEIGHT * 2;
            break;
        case GX_TF_C8:
            mcardStat.bannerFormat = CARD_STAT_BANNER_C8;
            memcpy(dst, desc->textureHeader->data, CARD_BANNER_WIDTH * CARD_BANNER_HEIGHT);
            memcpy(dst + CARD_BANNER_WIDTH * CARD_BANNER_HEIGHT, desc->CLUTHeader->data, 256 * 2);
            dst += CARD_BANNER_WIDTH * CARD_BANNER_HEIGHT + 256 * 2;
            break;
        default:
            OSPanic("mcard.c", 0x32E, "Unsupported banner texture format.");
            break;
        }
        fn_800ACFB0(pal);
        mcardState.hasBanner = TRUE;
    }
    if (icon != NULL) {
        hasClut = 0;
        pal = _OSAllocFromHeap(0x20, iconSize);
        memcpy(pal, icon, iconSize);
        UnpackTexPalette(pal);
        speed = iconSpeed & CARD_STAT_SPEED_MASK;
        stat = &mcardStat;
        for (i = 0; i < pal->numDescriptors && i < CARD_ICON_MAX; i++) {
            desc = TEXGet(pal, i);
            switch (desc->textureHeader->format) {
            case GX_TF_RGB5A3:
                CARDSetIconFormat(stat, i, CARD_STAT_ICON_RGB5A3);
                memcpy(dst, desc->textureHeader->data, CARD_ICON_WIDTH * CARD_ICON_HEIGHT * 2);
                dst += CARD_ICON_WIDTH * CARD_ICON_HEIGHT * 2;
                break;
            case GX_TF_C8:
                CARDSetIconFormat(stat, i, CARD_STAT_ICON_C8);
                memcpy(dst, desc->textureHeader->data, CARD_ICON_WIDTH * CARD_ICON_HEIGHT);
                hasClut = 1;
                dst += CARD_ICON_WIDTH * CARD_ICON_HEIGHT;
                break;
            default:
                OSPanic("mcard.c", 0x351, "Unsupported icon texture formant.");
                break;
            }
            CARDSetIconSpeed(stat, i, speed);
        }
        for (; i < CARD_ICON_MAX; i++) {
            CARDSetIconFormat(stat, i, CARD_STAT_ICON_NONE);
            CARDSetIconSpeed(stat, i, CARD_STAT_SPEED_END);
        }
        mcardState.iconCount = i;
        if (hasClut == 1) {
            memcpy(dst, desc->CLUTHeader->data, 256 * 2);
            dst += 256 * 2;
        }
        mcardStat.bannerFormat |= (u8)(animType & CARD_STAT_ANIM_MASK);
        fn_800ACFB0(pal);
    }
    if (openingBnr != NULL) {
        fn_800ACFB0(openingBnr);
    }
    lbl_803CC164 = dst;
    mcardStat.commentAddr = dst - (u8*)mcardSaveImage;
}

int mcardCalcBlocks(int bannerFormat, int iconSize, int dataSize) {
    int size;
    int blocks;

    switch (bannerFormat) {
    case 0:
        bannerFormat = 0;
        break;
    case 1:
        bannerFormat = CARD_BANNER_WIDTH * CARD_BANNER_HEIGHT * 2;
        break;
    case 2:
        bannerFormat = CARD_BANNER_WIDTH * CARD_BANNER_HEIGHT + 256 * 2;
        break;
    }
    size = bannerFormat + iconSize + dataSize;
    blocks = size / 0x2000;
    if (size % 0x2000 != 0) {
        blocks++;
    }
    return blocks;
}

void mcardStopProbe(void) {
    mcardState.operation = 7;
}

void mcardStartProbe(void) {
    memset(&mcardState, 0, sizeof(McardState));
    mcardState.status = 0xF;
    mcardState.chan[0].probeResult = CARD_RESULT_BUSY;
    mcardState.chan[1].probeResult = CARD_RESULT_BUSY;
    insertGraphicDrawingFunction(mcardProbeTask, 0xF0);
}

void mcardInit(void) {
    CARDInit();
}

void mcardSetResult(s32 result) {
    mcardState.result = result;
    switch (result) {
    case CARD_RESULT_READY:
        mcardState.status = 0x11;
        break;
    case CARD_RESULT_BUSY:
        mcardState.status = 0xF;
        break;
    case CARD_RESULT_NOCARD:
        mcardState.status = 0;
        break;
    case CARD_RESULT_BROKEN:
        mcardState.status = 1;
        break;
    case CARD_RESULT_ENCODING:
        mcardState.status = 2;
        break;
    case CARD_RESULT_IOERROR:
    case CARD_RESULT_FATAL_ERROR:
        mcardState.status = 3;
        break;
    case CARD_RESULT_WRONGDEVICE:
        mcardState.status = 4;
        break;
    case CARD_RESULT_NOENT:
        mcardState.status = 5;
        break;
    case CARD_RESULT_INSSPACE:
        mcardState.status = 6;
        break;
    case CARD_RESULT_EXIST:
        mcardState.status = 8;
        break;
    case CARD_RESULT_NOPERM:
    case CARD_RESULT_LIMIT:
    case CARD_RESULT_CANCELED:
        if (mcardState.operation == 1) {
            mcardState.status = 9;
        } else if (mcardState.operation == 2) {
            mcardState.status = 0xA;
        }
        break;
    case CARD_RESULT_NOFILE:
        if (mcardState.operation == 1) {
            mcardState.status = 9;
        } else if (mcardState.operation == 2) {
            mcardState.status = 0xE;
        }
        break;
    case CARD_RESULT_NAMETOOLONG:
        OSPanic("mcard.c", 0xEC, "CARD_RESULT_NAMETOOLONG           \n");
        break;
    case -0x81:
        mcardState.status = 7;
        break;
    }
}
