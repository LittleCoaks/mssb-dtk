#ifndef __GAME_REPLAY_REPLAY_INPUTS_H_
#define __GAME_REPLAY_REPLAY_INPUTS_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"

void useReplayInputs(void);
void replaceGameStructs_postReplay(int arg);
void structCopying(void);
void CopyMoreStructs(int arg);
void determineIfReplayShouldPlay(void);
void fn_3_7C190(void);
BOOL checkReplaySkipButton(void);

// Game state defined in replay_inputs.c.
extern InMemPitcherType g_Pitcher;
extern InMemBallType g_Ball;
extern InMemBatterType g_Batter;
extern GameControlsStruct g_GameLogic;
extern AIStruct g_AiLogic;
extern inMemBallsStrikesOuts g_BallsStrikesOuts;
extern g_Stats_s g_Stats;
extern GameScoresControlsStruct g_Scores;

#endif // !__GAME_REPLAY_REPLAY_INPUTS_H_
