#ifndef __GAME_MATCH_SETUP_REPLAY_STATE_H_
#define __GAME_MATCH_SETUP_REPLAY_STATE_H_

#include "mssbTypes.h"

#define REPLAY_MAX_FRAMES 0x4B0

// One controller's state for a single recorded frame.
typedef struct _ReplayPadFrame {
    /*0x0*/ sAng controlStickAngle;
    /*0x2*/ u16 buttonInput;
    /*0x4*/ u16 newButtonInput;
    /*0x6*/ s8 right_left;
    /*0x7*/ s8 up_down;
} ReplayPadFrame; // size: 0x8

typedef struct _ReplayFrame {
    /*0x0*/ ReplayPadFrame pad[2];
} ReplayFrame; // size: 0x10

extern ReplayFrame g_ReplayLogic[REPLAY_MAX_FRAMES];

void lastPlayStats(void);
void initializeReplayState(void);
void fn_3_7D2E0(void);
void fn_3_7D39C(void);
void ReplayRelatedCopying_storeDataBeforePlay(void);
void initializeReplayVariables(void);

#endif // !__GAME_MATCH_SETUP_REPLAY_STATE_H_
