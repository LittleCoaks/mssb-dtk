#ifndef __GAME_MATCH_SETUP_REPLAY_INPUTS_H_
#define __GAME_MATCH_SETUP_REPLAY_INPUTS_H_

#include "mssbTypes.h"

void useReplayInputs(void);
void replaceGameStructs_postReplay(int arg);
void structCopying(void);
void CopyMoreStructs(int arg);
void determineIfReplayShouldPlay(void);
void fn_3_7C190(void);
BOOL checkReplaySkipButton(void);

#endif // !__GAME_MATCH_SETUP_REPLAY_INPUTS_H_
