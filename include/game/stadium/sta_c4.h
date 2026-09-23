#ifndef __GAME_STADIUM_STA_C4_H_
#define __GAME_STADIUM_STA_C4_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

struct _GardenSprayParticle;
struct _GardenSprayEmitter;
struct _GardenBlockObj;
struct _GardenTexInfo;

void fn_3_F8444(void);
void fn_3_F8454(void);
void fn_3_F8524(struct _GardenSprayParticle* p);
BOOL fn_3_F85B0(struct _GardenSprayEmitter* emitter);
void fn_3_F8878(struct _GardenSprayEmitter* emitter);
void peachGardenSomething(void);
void fn_3_F8B04(void);
void fn_3_F8B30(void);
void fn_3_F8B34(void);
void fn_3_F8BA8(struct _GardenBlockObj* obj);
void fn_3_F8D00(void);
void fn_3_F8E20(void);
void fn_3_F9088(Vec* p, int idx);
void fn_3_F9164(struct _GardenBlockObj* obj);
void fn_3_F92FC(void);
void fn_3_F934C(void);
void fn_3_F963C(int idx, void* hit);
void fn_3_F976C(int idx, int arg1, void* hit);
void fn_3_F99F0(int idx, int arg1, void* hit);
void fn_3_F9B9C(int idx, int arg1, void* hit);
void fn_3_F9D94(struct _GardenBlockObj* obj);
void fn_3_F9E78(int idx, int arg1, void* hit);
void fn_3_FA3C0(void);
void loadPeachGarden(void** files);
void fn_3_FB3D8(void* view);
void fn_3_FBBA0(struct _GardenTexInfo* info);

#endif // !__GAME_STADIUM_STA_C4_H_
