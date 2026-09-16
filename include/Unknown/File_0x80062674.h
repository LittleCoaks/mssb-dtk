#ifndef __UNKNOWN_FILE_0X80062674_H_
#define __UNKNOWN_FILE_0X80062674_H_

#include "mssbTypes.h"

// channel indexes framesUntilCursorMovable[4] and the per-channel bytes at
// gameSetUpStep+0x55 / +0x5D (r3 is a 0..3 index in the DOL, not void).
void makeCursorMovable(int channel);
void makeCursorUnmovable(int channel);
void resetCursorFramesTillMovable(void);

#endif // !__UNKNOWN_FILE_0X80062674_H_
