#ifndef __GAME_MINIGAME_PIRANHA_PANIC_H_
#define __GAME_MINIGAME_PIRANHA_PANIC_H_

#include "mssbTypes.h"
#include "Dolphin/GX/GXEnum.h"

struct _PPSpawner;

void fn_3_141C44(void);
void fn_3_141C8C(void* model, GXTevStageID* stage, GXTexCoordID* coord, GXTexMapID* map, s8* nStages, s8* nCoords);
void fn_3_141F30(void);
int fn_3_142030(int x, int y, int width);
void fn_3_142088(void);
void fn_3_14225C(void);
void fn_3_142284(void);
int fn_3_142570(s8 slot);
u8 fn_3_1428F0(s8 slot, u8 force);
void fn_3_142C18(void);
void fn_3_142CA8(void);
void fn_3_142DB4(int idx);
void fn_3_1430D0(int arg, int owner);
void fn_3_143358(int idx);
void fn_3_143714(void);
BOOL fn_3_143770(struct _PPSpawner* sp);
void fn_3_1439EC(int idx);
void fn_3_143FAC(int idx);
void fn_3_14402C(int idx);
void fn_3_14423C(void);
void fn_3_14443C(void);
void pP_relatedToCalculatingHeldBallLoc(int p);
void fn_3_144ADC(int p);
void fn_3_144CB8(void);
void piranhaPanicPoints(int p);
void fn_3_145AD0(int p);
void ppRelated(void);
void fn_3_145EB8(void);
void fn_3_145FF4(void);
void fn_3_1461A4(void);
void piranhaPanicLiveBall(void);
void fn_3_146928(void);
void fn_3_1469CC(void);
void piranhaPanicRelated(void);

#endif // !__GAME_MINIGAME_PIRANHA_PANIC_H_
