#ifndef __GAME_MINIGAME_PIRANHA_PANIC_H_
#define __GAME_MINIGAME_PIRANHA_PANIC_H_

#include "mssbTypes.h"
#include "Dolphin/GX/GXEnum.h"

struct _PPSpawner;

void fn_3_141C44(void);
void pP_PulseTevCallback(void* model, GXTevStageID* stage, GXTexCoordID* coord, GXTexMapID* map, s8* nStages, s8* nCoords);
void pP_UpdatePulseTexture(void);
int pP_TiledTexelIndex(int x, int y, int width);
void pP_InitPulseTexture(void);
void pP_SetPulseTevCallback(void);
void pP_UpdateAI(void);
int pP_AIFramesUntilHit(s8 slot);
u8 pP_AIThrow(s8 slot, u8 force);
void pP_InitAI(void);
void pP_TallyScores(void);
void pP_SpawnLobbedProjectile(int idx);
void pP_SpawnProjectile(int arg, int owner);
void pP_UpdateProjectile(int idx);
void pP_UpdateProjectiles(void);
BOOL pP_PiranhaAimAtPlayer(struct _PPSpawner* sp);
void pP_PiranhaSpit(int idx);
void pP_UpdateActivePiranha(int idx);
void pP_UpdateHiddenPiranha(int idx);
void pP_ScheduleBigPiranha(void);
void pP_UpdatePiranhas(void);
void pP_relatedToCalculatingHeldBallLoc(int p);
void pP_UpdateCrouch(int p);
void pP_UpdatePlayers(void);
void piranhaPanicPoints(int p);
void pP_SetHeldBallPos(int p);
void ppRelated(void);
void pP_UpdateBalls(void);
void pP_Postgame(void);
void pP_UpdateTimeUp(void);
void piranhaPanicLiveBall(void);
void pP_StartPlay(void);
void pP_RoundIntro(void);
void piranhaPanicRelated(void);

#endif // !__GAME_MINIGAME_PIRANHA_PANIC_H_
