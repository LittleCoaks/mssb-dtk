#ifndef __GAME_MATCH_SETUP_PAUSE_MENU_H_
#define __GAME_MATCH_SETUP_PAUSE_MENU_H_

#include "mssbTypes.h"

typedef struct PauseSwapEntry {
    /* 0x0 */ s16 action;
    /* 0x2 */ s16 empty;
    /* 0x4 */ s16 _04;
    /* 0x6 */ s16 _06;
} PauseSwapEntry;

// Shared state block of the in-match pause menu.
typedef struct PauseControl {
    /* 0x000 */ s32 port;
    /* 0x004 */ u16 _004[3];
    /* 0x00A */ s16 _00A;
    /* 0x00C */ s16 counter;
    /* 0x00E */ s16 _00E;
    /* 0x010 */ s16 _010;
    /* 0x012 */ s16 _12;
    /* 0x014 */ u8 _014[0x18 - 0x14];
    /* 0x018 */ PauseSwapEntry swapEntries[2][10];
    /* 0x0B8 */ u8 _0B8[0x168 - 0xB8];
    /* 0x168 */ s16 battingOrderCopy[2][20];
    /* 0x1B8 */ u8 _1B8[0x1D0 - 0x1B8];
    /* 0x1D0 */ u8 _1D0;
    /* 0x1D1 */ u8 _1D1;
    /* 0x1D2 */ u8 state;
    /* 0x1D3 */ u8 _1D3;
    /* 0x1D4 */ u8 _1D4;
    /* 0x1D5 */ u8 _1D5;
    /* 0x1D6 */ u8 _1D6;
    /* 0x1D7 */ u8 _1D7;
    /* 0x1D8 */ u8 _1D8;
    /* 0x1D9 */ u8 _1D9;
    /* 0x1DA */ s8 cursor;
    /* 0x1DB */ u8 _1DB;
    /* 0x1DC */ u8 _1DC;
    /* 0x1DD */ u8 _1DD[0x201 - 0x1DD];
    /* 0x201 */ u8 _201;
    /* 0x202 */ u8 _202[2];
    /* 0x204 */ u8 _204[2];
    /* 0x206 */ s8 _206;
    /* 0x207 */ u8 _207;
    /* 0x208 */ u8 _208;
    /* 0x209 */ u8 _209;
    /* 0x20A */ u8 lineupCopy[2][9];
    /* 0x21C */ u8 _21C;
    /* 0x21D */ u8 _21D;
    /* 0x21E */ u8 _21E[0x220 - 0x21E];
    /* 0x220 */ u8 _220;
    /* 0x221 */ u8 _221;
    /* 0x222 */ u8 _222;
    /* 0x223 */ u8 _223[0x23F - 0x223];
    /* 0x23F */ u8 _23F[2];
    /* 0x241 */ u8 _241;
    /* 0x242 */ s16 _242[9];
    /* 0x254 */ s16 _254[6];
    /* 0x260 */ u8 _260;
    /* 0x261 */ u8 _261[0x264 - 0x261];
} PauseControl;

extern PauseControl pauseControl;

void setPausedTo0AndOtherStateVars(void);
void fn_3_AFD80(int arg0);
BOOL fn_3_AFD48(int arg0);
void fn_3_AF5A4(void);
void fn_3_AF428(void);
void fn_3_AEFF8(void);
void fn_3_AE770(void);
void fn_3_AD2A0(void);
void pauseMenuControl(int side);
void fn_3_AC9F8(void);
void howToPlayScreen(void);
void match_checkForPause(void);
void transitionToPauseScreen(void);

#endif // !__GAME_MATCH_SETUP_PAUSE_MENU_H_
