#ifndef __GAME_STADIUM_STADIUM_YOSHI_PARK_H_
#define __GAME_STADIUM_STADIUM_YOSHI_PARK_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "game/ball/collision_primitives.h"
#include "game/stadium/stadium_framework.h"

void fn_3_E1DB8(void);
void fn_3_E1FA8(StadiumObject* obj);
void fn_3_E2034(struct _YoshiPlantObj* plant);
void fn_3_E2118(int idx);
void fn_3_E22A4(struct _YoshiPlantObj* plant);
void fn_3_E2324(struct _YoshiPlantObj* plant);
void fn_3_E25D0(struct _YoshiPlantObj* plant, u32 anim);
void advancePlantInteractionPhase(struct _YoshiPlantObj* plant);
E(u8, BOOL) fn_3_E28DC(struct _YoshiPlantObj* plant);
E(u8, BOOL) fn_3_E29B4(struct _YoshiPlantObj* plant);
E(u8, BOOL) updatePlantCatchState(struct _YoshiPlantObj* plant);
void updateStadiumObjStateAndTransform(struct _YoshiPlantObj* plant);
void yoshiParkPlantRelated(struct _YoshiPlantObj* plant);
void nadoRelated(struct _YoshiPlantObj* plant);
E(u8, BOOL) tryPlantCatchAndBeginSpitAim(struct _YoshiPlantObj* plant);
void updatePlantAimingOrCatch(struct _YoshiPlantObj* plant);
void ParkPlantsPopUp(struct _YoshiPlantObj* plant);
void fn_3_E3914(struct _YoshiPlantObj* plant);
void controlYoshiParkPlants(struct _YoshiPlantObj* plant);
void fn_3_E4554(struct _YoshiPlantObj* plant);
void fn_3_E45A8(struct _YoshiPlantObj* plant);
void fn_3_E45F0(struct _YoshiPlantObj* plant);
void fn_3_E4658(struct _YoshiPlantObj* plant);
void fn_3_E4760(struct _YoshiPlantObj* plant);
void fn_3_E48D0(struct _YoshiPlantObj* plant);
void fn_3_E4A38(Mtx m, StadiumMeshData* mesh);
TriangleGroup* fn_3_E4BE8(int offset, Mtx m);
void processYoshiParkPlantBoundingBoxes(s32* idx, s32* count);
void fn_3_E4EF4(void);
void loadYoshiPark(void** files);

#endif // !__GAME_STADIUM_STADIUM_YOSHI_PARK_H_
