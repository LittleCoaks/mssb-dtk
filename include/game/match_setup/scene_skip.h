#ifndef __GAME_MATCH_SETUP_SCENE_SKIP_H_
#define __GAME_MATCH_SETUP_SCENE_SKIP_H_

#include "mssbTypes.h"

void setCharacterAnimations(int player, int anim);
BOOL checkForButtonPressToSkip(int inputKind, int mask);
BOOL isSkipButtonPressedForPlayer(int player, int inputKind, int mask);

#endif // !__GAME_MATCH_SETUP_SCENE_SKIP_H_
