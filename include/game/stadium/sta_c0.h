#ifndef __GAME_STADIUM_STA_C0_H_
#define __GAME_STADIUM_STA_C0_H_

#include "mssbTypes.h"

struct _StadiumObject;

void manageMarioStadiumSoundEmmitters(void);
void fanAnimationRelated(void);
void fn_3_C99F8(struct _StadiumObject* obj);
void fn_3_C9A60(struct _StadiumObject* obj);
void fn_3_C9AC8(void);
void fn_3_C9B5C(struct _StadiumObject* obj);
void sta_c0(void);
void loadMarioStadium(void** files);

#endif // !__GAME_STADIUM_STA_C0_H_
