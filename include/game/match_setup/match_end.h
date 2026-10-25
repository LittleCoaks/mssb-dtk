#ifndef __GAME_MATCH_SETUP_MATCH_END_H_
#define __GAME_MATCH_SETUP_MATCH_END_H_

#include "mssbTypes.h"

typedef struct {
    s16 score;
    s16 outs;
    s16 runnerFlags;
    s16 currentBatter;
} ChallengeSituation;

typedef struct {
    u32 _0;
    u32 _4;
    u32 _8;
    u32 _C;
} MatchEndFile;

int fn_3_5B220(int arg0);
void fn_3_5B368(void);
int exitMenu_main(u16 buttons);
void fn_3_5B408(void);
void fn_3_5B41C(void);
void startChallengeModeMatch(void);
void endOfGame_menuControl(void);
void matchEndGameScreenFunction(void);

#endif // !__GAME_MATCH_SETUP_MATCH_END_H_
