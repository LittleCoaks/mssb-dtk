#ifndef __GAME_STADIUM_STADIUM_FRAMEWORK_H_
#define __GAME_STADIUM_STADIUM_FRAMEWORK_H_

#include "mssbTypes.h"

void randomizeAndLoadSoundEffect(void);
void maybeYoshiParkGXRelated(void);
void fn_3_B8184(void);
void fn_3_B827C(void);
void fn_3_B828C(void);
void fn_3_B8298(void);
void storeBoundingBoxCoordinates(void);
void transformVectorsUpdateBoundingBox(void);
void initBoundingBoxLimits(void);
void calculateHazardDataAddress(void);
void CopyOutVecSrcDst(void);
void fn_3_B8658(void);
void fn_3_B867C(void);
void loadStadiumObjectVisuals(void);
void fn_3_B8C08(void);
void fn_3_B902C(void);
void initStadiumObjectData(void);
void updateStadiumObjCollision(void);
int processStadiumObjectFunction(int, void*, int, void*);
void getStadiumHazardTriangles(void);
void updateGameStatusFlag(void);
void fn_3_B93C4(void);
void fn_3_B93C8(void);
void hazardSimulationRelated(void);
void fn_3_B950C(void);
void fn_3_B9510(void);
void fn_3_B9524(void);
void fn_3_B9534(void);
void cleanupMinigameResources(void);
void fn_3_B97C8(void);
void actorSetAnimBank(void);
void fn_3_B98E8(void);
void calledWhileMatchIsLoading(void);
void loadStadiumObjects(void);
void processStadiumFileObjects(void);
void loadStadiumLighting(void);

#endif // !__GAME_STADIUM_STADIUM_FRAMEWORK_H_
