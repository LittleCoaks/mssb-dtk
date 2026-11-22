#include "Unknown/File_0x80062674.h"
#include "static/UnknownHomes_Static.h"

extern GameSetUpStep gameSetUpStep;
extern s32 framesUntilCursorMovable[4];

void makeCursorMovable(int channel) {
    framesUntilCursorMovable[channel]--;
    if (framesUntilCursorMovable[channel] != 0) {
        return;
    }
    if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
        gameSetUpStep.preventCursorMovement[0] = FALSE;
    } else {
        gameSetUpStep.preventCursorMovement[channel] = FALSE;
    }
    gameSetUpStep.currentCharacterSelectProcess[channel] = 0;
}

void makeCursorUnmovable(int channel) {
    if (g_d_GameSettings.p2_CPU_match_code == P2_CPU_CODE_1_PLAYER_GAME) {
        gameSetUpStep.preventCursorMovement[0] = TRUE;
    } else {
        gameSetUpStep.preventCursorMovement[channel] = TRUE;
    }
    framesUntilCursorMovable[channel]++;
}

void resetCursorFramesTillMovable(void) {
    framesUntilCursorMovable[3] = 0;
    framesUntilCursorMovable[2] = 0;
    framesUntilCursorMovable[1] = 0;
    framesUntilCursorMovable[0] = 0;
}
