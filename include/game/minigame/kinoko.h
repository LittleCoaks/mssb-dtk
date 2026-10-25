#ifndef __GAME_MINIGAME_KINOKO_H_
#define __GAME_MINIGAME_KINOKO_H_

#include "mssbTypes.h"
#include "Dolphin/vec.h"
#include "Dolphin/GX/GXEnum.h"

struct _RibbonPoint;
struct _Ribbon;

void kinoko_pulseTevCallback(void* model, GXTevStageID* stage, GXTexCoordID* coord, GXTexMapID* map, s8* nStages, s8* nCoords);
void kinoko_updatePulseTexture(void);
void fn_3_1695A0(void);
void kinoko_startPulseGlow(void* model, u8 alt);
void kinoko_initPulseTextures(void);
void kinoko_setupRibbonGX(void);
void kinoko_drawRibbons(void);
void kinoko_queueRibbonQuads(struct _Ribbon* ribbon, u32* count);
void kinoko_buildRibbonEdges(struct _RibbonPoint* points);
void kinoko_updateRibbons(void);
void kinoko_getBonePos(Vec* pos, s8 bone);
void kinoko_setRibbonHead(struct _RibbonPoint* p, s8 bone, int frame);
void kinoko_initRibbonHistory(void);
void kinoko_startRibbon(s8 charID);
void gardenSFXRelated(u8 alt);

#endif // !__GAME_MINIGAME_KINOKO_H_
