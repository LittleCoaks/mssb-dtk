#include "Unknown/File_0x80062578.h"

extern u8 gameSetUpStep[0x64];

s32 noActiveProcessInd(void) {
    BOOL ret = FALSE;
    if (gameSetUpStep[0x5D] == 0 && gameSetUpStep[0x5E] == 0) {
        ret = TRUE;
    }
    return ret;
}
