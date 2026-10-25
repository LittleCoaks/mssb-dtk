#ifndef __GAME_MINIGAME_CHAIN_CHOMP_SPRINT_H_
#define __GAME_MINIGAME_CHAIN_CHOMP_SPRINT_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

void ccsAI_clearControlled(void);
void ccsAI_update(void);
u8 ccsAI_isBehindInPoints(s8 player);
int ccsAI_compareTargetDist(f32* a, f32* b);
f32 ccsAI_getDistPastClosestRunner(f32 target, s8 runnerIdx, u8* direction);
int ccsAI_compareDistF32(f32* a, f32* b);
f32 ccsAI_getShortestDist(f32 target, s8 runnerIdx, u8* direction);
void ccsAI_getRunnerDists(s8 runnerIdx, f32 target, f32* forward, f32* backward);
f32 ccs_basePathDistance(u8 forward, f32 from, f32 to);
void ccsAI_init(void);
void ccs_cameraShakeCallback(camera_803c639c_s* cam);
void ccs_startCameraShake(u8 type);
void ccs_updatePowerupOnField(MinigamePowerupStruct* powerup);
void ccs_updatePowerupSpawn(MinigamePowerupStruct* powerup);
void ccs_updatePowerup(void);
void ccs_updateDroppedCoins(void);
void ccs_dropCoinsOnBite(int player);
void chainChompSpringPoints(void);
void ccs_spawnItem(int item);
void ccs_updateItemStates(void);
void ccs_updateItemsAndCoins(void);
void ccs_countRunnerMoveFrames(void);
void ccs_updateChompReturn(void);
void ccs_updateChompChase(void);
void ccs_updateChompPickTargets(void);
void ccs_updateChompJump(void);
void ccs_updateChompWait(void);
void ccs_updateChomp(void);
void ccs_finishAfterFade(void);
void ccs_updateGameEnd(void);
void chainChompSpringMainFun(void);
void chainChompSprintEndGame(void);
void ccs_startGame(void);
void ccs_introTransition(void);
void chainChompSprintRelated(void);
void ccs_EmptyHook(void);
void chainChompSprintSwitcher(void);

#endif // !__GAME_MINIGAME_CHAIN_CHOMP_SPRINT_H_
