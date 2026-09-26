#ifndef __GAME_MINIGAME_KINOKO_H_
#define __GAME_MINIGAME_KINOKO_H_

#include "mssbTypes.h"
#include "Dolphin/vec.h"
#include "Dolphin/GX/GXEnum.h"

struct _RibbonPoint;
struct _Ribbon;

void fn_3_16917C(void* model, GXTevStageID* stage, GXTexCoordID* coord, GXTexMapID* map, s8* nStages, s8* nCoords);
void fn_3_16943C(void);
void fn_3_1695A0(void);
void fn_3_1695A4(void* model, u8 alt);
void fn_3_169600(void);
void fn_3_169804(void);
void fn_3_169984(void);
void fn_3_169D00(struct _Ribbon* ribbon, u32* count);
void fn_3_169E70(struct _RibbonPoint* points);
void fn_3_16A07C(void);
void fn_3_16B488(Vec* pos, s8 bone);
void fn_3_16B5B4(struct _RibbonPoint* p, s8 bone, int frame);
void fn_3_16B884(void);
void fn_3_16C394(s8 charID);

#endif // !__GAME_MINIGAME_KINOKO_H_
