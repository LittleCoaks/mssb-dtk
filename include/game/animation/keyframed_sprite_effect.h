#ifndef __GAME_ANIMATION_KEYFRAMED_SPRITE_EFFECT_H_
#define __GAME_ANIMATION_KEYFRAMED_SPRITE_EFFECT_H_

#include "mssbTypes.h"

struct _HudNode;
BOOL keyframedSpriteEffect_draw(void);
f32 keyframedSpriteEffect_evalNode(struct _HudNode* node, int frame, f32 out[3][4], f32 t);
void keyframedSpriteEffect_stop(void);

#endif // !__GAME_ANIMATION_KEYFRAMED_SPRITE_EFFECT_H_
