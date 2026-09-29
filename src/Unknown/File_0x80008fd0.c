#include "Unknown/File_0x80008fd0.h"
#include "Dolphin/OS/OSReset.h"

extern s32 lbl_803CBBAC;
extern u8 lbl_803CBBC2;

void PostRetraceCallback(u32 retraceCount) {
    if (OSGetResetButtonState() && lbl_803CBBAC != 0) {
        lbl_803CBBC2 = 1;
    }
}
