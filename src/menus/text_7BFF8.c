#include "menus/text_7BFF8.h"
#include "Unknown/File_0x80062674.h"
#include "Unknown/orderchange.h"
#include "static/UnknownHomes_Static.h"

typedef struct {
    u8 _00[0xD];
    u8 unk0D[4];
} CssStepFlags;
extern CssStepFlags gameSetUpStep;

// .text:0x0007BFF8 size:0x1864 mapped:0x806BB08C
void cssAction_case9(void) {
    return;
}

// .text:0x0007D85C size:0x25C mapped:0x806BC8F0
void fn_2_7D85C(void) {
    return;
}

// .text:0x0007DAB8 size:0x6DC mapped:0x806BCB4C
void fn_2_7DAB8(void) {
    return;
}

// .text:0x0007E194 size:0x1EC mapped:0x806BD228
void fn_2_7E194(MenuScene* scene, s32 slot) {
    s32 count;
    s32 threshold;
    s8 swapIdx;
    s32 captainID;
    s8* cursor;

    if (gameSetUpStep.unk0D[slot] == 1) {
        count = maybeCheckAndResetGrapicsElement(scene, slot + 0x1C, 10) != 0;
        count += maybeCheckAndResetGrapicsElement(scene, slot + 0x6A, 10) != 0;
        threshold = 3;
        count += maybeCheckAndResetGrapicsElement(scene, slot + 0x89, 5) != 0;
        if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME && slot == 0) {
            cursor = (s8*)&cursorPositions;
            captainID = Static_Stats_Tables.captainSelectedID[1];
            if (cursor[0xB] == captainID) swapIdx = cursor[0x1D];
            if (cursor[0xC] == captainID) swapIdx = cursor[0x1E];
            if (cursor[0xD] == captainID) swapIdx = cursor[0x1F];
            if (cursor[0xE] == captainID) swapIdx = cursor[0x20];
            if (cursor[0xF] == captainID) swapIdx = cursor[0x21];
            if (cursor[0x10] == captainID) swapIdx = cursor[0x22];
            if (cursor[0x11] == captainID) swapIdx = cursor[0x23];
            if (cursor[0x12] == captainID) swapIdx = cursor[0x24];
            if (cursor[0x13] == captainID) swapIdx = cursor[0x25];
            count += maybeCheckAndResetGrapicsElement(scene, swapIdx + 0x3D, 0x14) != 0;
            threshold = 4;
        }
        if (count == threshold) {
            makeCursorMovable(slot);
            gameSetUpStep.unk0D[slot] = 2;
        }
    }
}
