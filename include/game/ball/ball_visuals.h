#ifndef __GAME_BALL_BALL_VISUALS_H_
#define __GAME_BALL_BALL_VISUALS_H_

#include "mssbTypes.h"
#include "Unknown/File_0x80034e20.h"

void fn_3_6750C(TextureHeader* textures);
void fn_3_675B8(u16 frames);
void setupBallTrailEffect(int type, u16 duration);
void fn_3_678B8(void);
void ballAnimationSubFun4(void);
void displayBallTrail(void);
void ballSpinSetting(void);
void clearAnimationRelatedPointers(void);
void fn_3_6916C(void);
void ballAnimationSubFun3(void);
void ballAnimationSubFun2(void);
void ballAnimationSubFun1(BOOL visible);
void ballAnimations(void);
void fn_3_6A160(void);
void AnimBlr(void);
void fn_3_6A254(void);
void fn_3_6A258(void);
void resetAnimationRelatedPointers(void);

#endif // !__GAME_BALL_BALL_VISUALS_H_
