#ifndef __GAME_MATCH_SETUP_MATCH_LOADING_H_
#define __GAME_MATCH_SETUP_MATCH_LOADING_H_

#include "mssbTypes.h"

typedef struct {
    /* 0x0 */ u32 _0;
    /* 0x4 */ u32 _4;
    /* 0x8 */ u32 _8;
    /* 0xC */ u32 _C;
} MatchFileDescriptor; // size: 0x10

extern MatchFileDescriptor sequencedSongsFileDescriptor[];
extern MatchFileDescriptor lbl_3_data_3D70;
extern MatchFileDescriptor CommonUIFiles_inGame[0x43];

void QueueTextToDisplay(int arg0);
void initializeSomethingDuringTransition(void);
void fn_3_59AC0(int arg0, int arg1, int arg2);
int fn_3_59AE4(void);
void loadToyFieldCharacterFiles(void);
int fn_3_59BCC(int arg0);
void fn_3_59C2C(void);
void fn_3_59F40(void);
void fn_3_5A28C(void);

#endif // !__GAME_MATCH_SETUP_MATCH_LOADING_H_
