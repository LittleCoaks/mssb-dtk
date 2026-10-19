#ifndef __GAME_MINIGAME_MINIGAME_WINNER_SPOTLIGHT_H_
#define __GAME_MINIGAME_MINIGAME_WINNER_SPOTLIGHT_H_

#include "mssbTypes.h"

void minigameWinnerSpotlight_clearDepth(BOOL nearPlane);
void minigameWinnerSpotlight_stop(void);
void minigameWinnerSpotlight_show(void);
void minigameWinnerSpotlight_fadeIn(void);
void minigameWinnerSpotlight_start(int count, s32* values);
void minigameWinnerSpotlight_queue(int count, ...);
void minigameWinnerSpotlight_draw(void* arg);

#endif // !__GAME_MINIGAME_MINIGAME_WINNER_SPOTLIGHT_H_
