#include "Unknown/File_0x800a8cbc.h"
#include "Unknown/File_0x800a7544.h"
#include "Unknown/File_0x800a7568.h"
#include "Dolphin/OS/OSInterrupt.h"

extern LoadFileNode* jukeboxQueueHead;
extern LoadFileNode* lbl_803CC14C;
extern LoadFileNode* lbl_803CC154;
extern u32 lbl_803CC148;

BOOL fn_800A750C(char** path, DVDFileInfo* fileInfo);
void fn_800A9424(s32 result, DVDFileInfo* fileInfo);

s32 LoadFile(char** path, LoadFileNode* node, u32 flags, LoadFileCallback callback, u32 checkQueued) {
    s32 savedEntryNum;
    BOOL startStream;
    BOOL enabled;
    LoadFileNode* it;

    if ((checkQueued & 1) && jukeboxQueueHead != NULL) {
        for (it = jukeboxQueueHead; it != NULL; it = it->next) {
            if (it == node) {
                return 0x100;
            }
        }
    }

    startStream = FALSE;
    savedEntryNum = lbl_803C6CF8.entryNum;
    lbl_803C6CF8.entryNum = ConvertPathToEntryNum(path);
    if (!fn_800A750C(path, &node->fileInfo)) {
        return 1;
    }
    lbl_803C6CF8.entryNum = savedEntryNum;

    enabled = OSDisableInterrupts();
    node->path = path;
    node->flags = flags;
    node->callback = callback;
    if (jukeboxQueueHead == NULL) {
        jukeboxQueueHead = node;
        lbl_803CC14C = node;
        node->prev = NULL;
        node->next = NULL;
        if (lbl_803CC148 == 1) {
            startStream = TRUE;
        }
    } else {
        lbl_803CC14C->next = node;
        node->prev = lbl_803CC14C;
        lbl_803CC154 = node;
        node->next = NULL;
    }
    if (lbl_803CC154 == NULL) {
        lbl_803CC154 = node;
    }
    OSRestoreInterrupts(enabled);

    if (node != NULL && node->callback != NULL && (node->flags & 8)) {
        node->callback(node->flags & 8);
    }

    if (startStream) {
        lbl_803CC148 = 3;
        DVDPrepareStreamAsync(&lbl_803CC154->fileInfo, 0, 0, fn_800A9424);
    }
    return 0;
}
