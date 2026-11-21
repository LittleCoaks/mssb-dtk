#include "Unknown/File_0x80039aa8.h"

// 0x80039AA8-0x8003A37C: one translation unit (docs/splits.md, 2026-11-21):
// GetUITexture/returnTexture plus fn_80039AC0 ... fn_8003A2EC, which read the
// same .data object and literal pool. Those have no C yet.

extern u8 UITexture[];
extern u8 lbl_800F7A40[];

void* GetUITexture(void) {
    return UITexture;
}

void* returnTexture(void) {
    return lbl_800F7A40;
}
