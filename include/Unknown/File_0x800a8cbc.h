#ifndef __UNKNOWN_FILE_0X800A8CBC_H_
#define __UNKNOWN_FILE_0X800A8CBC_H_

#include "mssbTypes.h"
#include "Dolphin/dvd.h"

typedef void (*LoadFileCallback)(u32 event);

/* Node in the queue of files waiting to be streamed from disc. */
typedef struct LoadFileNode {
    /* 0x00 */ struct LoadFileNode* prev;
    /* 0x04 */ struct LoadFileNode* next;
    /* 0x08 */ u32 flags;
    /* 0x0C */ LoadFileCallback callback; // called with the event bit when that bit is set in flags
    /* 0x10 */ DVDFileInfo fileInfo;
    /* 0x4C */ char** path;
} LoadFileNode;

s32 LoadFile(char** path, LoadFileNode* node, u32 flags, LoadFileCallback callback, u32 checkQueued);

#endif // !__UNKNOWN_FILE_0X800A8CBC_H_
