#ifndef __GAME_STADIUM_STA_C6_H_
#define __GAME_STADIUM_STA_C6_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "game/ball/collision_primitives.h"

void fn_3_E59B4(void);
void fn_3_E5A1C(void);
void fn_3_E5A84(void);
void fn_3_E5CBC(void);
void fn_3_E5E14(void);
void fn_3_E5E70(void);
void fn_3_E5FEC(void);
void fn_3_E6410(void);
void fn_3_E64A8(void);
void fn_3_E6528(void);
void fn_3_E6578(void);
void fn_3_E6638(void);
void fn_3_E6684(void);
void fn_3_E671C(void);
void fn_3_E6798(void);
void fn_3_E67F4(void);
void fn_3_E68A8(void);
void fn_3_E698C(void);
void fn_3_E6A48(void);
void fn_3_E6D90(void);
void fn_3_E7350(void);
void fn_3_E7364(void);
struct _StadiumDrawOrder;
void processToyFieldObjectCollisions(Mtx view, struct _StadiumDrawOrder* order);
void fn_3_E7424(void);
TriangleGroup* fn_3_E751C(int offset, Mtx m);
void fn_3_E763C(void);
void fn_3_E7A2C(void);
void fn_3_E7B20(void);
void fn_3_E8AC8(void);
void loadToyField(void);

#endif // !__GAME_STADIUM_STA_C6_H_
