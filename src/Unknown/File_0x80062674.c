#include "Unknown/File_0x80062674.h"
#include "static/UnknownHomes_Static.h"

typedef struct {
    /* 0x00 */ u8 _00[0x55];
    /* 0x55 */ u8 cursorLocked[4];
    /* 0x59 */ u8 portCaptainSlot[4];
    /* 0x5D */ u8 unk5D[4];
    /* 0x61 */ u8 _61[0x64 - 0x61];
} GameSetUpStep;

extern GameSetUpStep gameSetUpStep;
extern s32 framesUntilCursorMovable[4];

void makeCursorMovable(int channel) {
    framesUntilCursorMovable[channel]--;
    if (framesUntilCursorMovable[channel] != 0) {
        return;
    }
    if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
        gameSetUpStep.cursorLocked[0] = FALSE;
    } else {
        gameSetUpStep.cursorLocked[channel] = FALSE;
    }
    gameSetUpStep.unk5D[channel] = 0;
}

void makeCursorUnmovable(int channel) {
    if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
        gameSetUpStep.cursorLocked[0] = TRUE;
    } else {
        gameSetUpStep.cursorLocked[channel] = TRUE;
    }
    framesUntilCursorMovable[channel]++;
}

void resetCursorFramesTillMovable(void) {
    framesUntilCursorMovable[3] = 0;
    framesUntilCursorMovable[2] = 0;
    framesUntilCursorMovable[1] = 0;
    framesUntilCursorMovable[0] = 0;
}
