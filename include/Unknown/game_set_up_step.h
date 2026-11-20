#ifndef __UNKNOWN_GAME_SET_UP_STEP_H_
#define __UNKNOWN_GAME_SET_UP_STEP_H_

#include "mssbTypes.h"

/* gameSetUpStep (DOL, 0x64 bytes): per-port state of the set-up screens
 * (captain select, character select, stadium select, team management).
 * The SET_UP_STEP and CHAR_SELECT_PROCESS enums are in
 * static/UnknownHomes_Static.h. */
typedef struct GameSetUpStep {
    /* 0x00 */ u8 screen; // 1 captain select, 2 character select (cssActions); 3/4 stadium select; 0 on exit
    /* 0x01 */ E(u8, SET_UP_STEP) stepFlags[14][6]; // [row][port]; cleared by updateCharacterSelectProcessCode
    /* 0x55 */ u8 preventCursorMovement[4];          // makeCursorUnmovable / makeCursorMovable
    /* 0x59 */ u8 portCaptainSlot[4];                // team slot this port controls
    /* 0x5D */ E(u8, CHAR_SELECT_PROCESS) currentCharacterSelectProcess[4];
    /* 0x61 */ u8 _61[3];
} GameSetUpStep; // size: 0x64

#endif // !__UNKNOWN_GAME_SET_UP_STEP_H_
