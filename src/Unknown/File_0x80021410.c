#include "Unknown/File_0x80021410.h"
#include "musyx/musyx.h"

static inline BOOL popSoundGroup(void) {
    if (sndPopGroup() == FALSE) {
        return FALSE;
    }
    audioFileDescriptors.pushedGroupCount--;
    return TRUE;
}

BOOL maybeLoadsGameSoundFiles(void) {
    s8 i;

    for (i = (s8)audioFileDescriptors.pushedGroupCount - 1; i > 0; i--) {
        if (!popSoundGroup()) {
            return FALSE;
        }
    }
    return TRUE;
}
