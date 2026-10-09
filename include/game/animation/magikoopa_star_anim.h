#ifndef __GAME_ANIMATION_MAGIKOOPA_STAR_ANIM_H_
#define __GAME_ANIMATION_MAGIKOOPA_STAR_ANIM_H_

#include "mssbTypes.h"
#include "Dolphin/vec.h"

struct _MagiAnimObj;

void fn_3_1666B0(Vec* pos);
void fn_3_16689C(void);
void magikoopaAnimationRelated(void);
void applyStarRelatedTransformations(void);
void fn_3_166C30(struct _MagiAnimObj* obj, s8 node);
void fn_3_166D40(void);
void fn_3_166E04(void);
void fn_3_166FCC(void);
void fn_3_167178(void);
void fn_3_1674D0(void);
void fn_3_1678A8(void);

void fn_3_167CC4(void);
void fn_3_167D4C(void);
void fn_3_167F14(void);
void fn_3_1680D4(void);
void fieldingRelatedAnimations(void *anim, s8 kind);

#endif // !__GAME_ANIMATION_MAGIKOOPA_STAR_ANIM_H_
