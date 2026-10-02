#ifndef __GAME_MINIGAME_BOBOMB_DERBY_H_
#define __GAME_MINIGAME_BOBOMB_DERBY_H_

#include "mssbTypes.h"

void bOD_BatterAI(void);
void bOD_ClearInputs(void);
s32 bOD_EstimatePitchFrames(void);
void bOD_HomeRunFireworks(void);
void bOD_ScoreHomeRun(void);
void bOD_SetRunnerAngleFromHit(void);
void bOD_FinishPitch(void);
void bOD_LiveBallOutcome(void);
void bOD_LiveBall(void);
void bOD_bB_Pitcher_waitingForPitch(void);
void bOD_FinishTurn(void);
void bOD_AtBatOutcome(void);
void bOD_AtBat(void);
void bOD_RoundIntro(void);
void bOD_Postgame(void);
void bOD_CheckRoundsLeft(void);
void bOD_EndTurn(void);
void bOD_ResetPlayState(void);
void bOD_PrepareNextPitch(void);
void bOD_PrepareNextBatter(void);
void bOD_StartRound(void);
void bOD_TransitionToBatting(void);
void bOD_LoadGame(void);
void bOD_UpdateFieldObjects(void);
void bOD_AmbientFireworks(void);
void bobOmbDerbySwitcher(void);

#endif // !__GAME_MINIGAME_BOBOMB_DERBY_H_
