#ifndef __GAME_STADIUM_STA_C6_H_
#define __GAME_STADIUM_STA_C6_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "game/ball/collision_primitives.h"

int fn_3_E587C(void);
BOOL fn_3_E5924(void);
struct _StadiumObject;
void fn_3_E59B4(struct _StadiumObject* obj);
void fn_3_E5A1C(struct _StadiumObject* obj);
struct _ToyFieldObj;
void fn_3_E5A84(struct _ToyFieldObj* obj);
void fn_3_E5CBC(struct _ToyFieldObj* obj, f32 t);
struct _ToyColorRef;
int fn_3_E5E14(struct _ToyColorRef* ref);
void fn_3_E5E70(u8* out, u8 formatBits, void* src);
void fn_3_E5FEC(struct _ToyFieldObj* obj);
void fn_3_E6410(struct _ToyFieldObj* obj);
u8* fn_3_E64A8(void);
void fn_3_E6528(struct _ToyFieldObj* obj);
void fn_3_E6578(struct _ToyFieldObj* obj);
void fn_3_E6638(struct _ToyFieldObj* obj);
void fn_3_E6684(struct _ToyFieldObj* obj);
void fn_3_E671C(struct _ToyFieldObj* obj);
void fn_3_E6798(struct _ToyFieldObj* obj);
void fn_3_E67F4(void);
void fn_3_E68A8(struct _ToyFieldObj* obj);
void fn_3_E698C(struct _ToyFieldObj* obj);
void fn_3_E6A48(struct _ToyFieldObj* obj);
void fn_3_E6D90(struct _ToyFieldObj* obj);
void fn_3_E7350(void);
void fn_3_E7364(int idx);
struct _StadiumDrawOrder;
void processToyFieldObjectCollisions(Mtx view, struct _StadiumDrawOrder* order);
void fn_3_E7424(void);
TriangleGroup* fn_3_E751C(int offset, Mtx m);
void fn_3_E763C(void);
void fn_3_E7A2C(struct _StadiumObject* obj);
E(u8, BOOL) fn_3_E7B20(void** files, u32* ids);
BOOL fn_3_E8AC8(void);
void loadToyField(void** files);

#endif // !__GAME_STADIUM_STA_C6_H_
