#include "Unknown/File_0x80062578.h"
#include "Unknown/game_set_up_step.h"

extern GameSetUpStep gameSetUpStep;

s32 noActiveProcessInd(void) {
    BOOL ret = FALSE;
    if (gameSetUpStep.currentCharacterSelectProcess[0] == 0 && gameSetUpStep.currentCharacterSelectProcess[1] == 0) {
        ret = TRUE;
    }
    return ret;
}
