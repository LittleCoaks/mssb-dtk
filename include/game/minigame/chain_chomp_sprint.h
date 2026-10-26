#ifndef __GAME_MINIGAME_CHAIN_CHOMP_SPRINT_H_
#define __GAME_MINIGAME_CHAIN_CHOMP_SPRINT_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

typedef struct _CcsGameplayConsts {
    /* 0x00 */ f32 biteRadius;
    /* 0x04 */ f32 chaseSpeed;
    /* 0x08 */ f32 returnSpeed;
    /* 0x0C */ f32 launchVelocityY;
    /* 0x10 */ f32 chaseHopVelocityY;
    /* 0x14 */ f32 returnHopVelocityY;
    /* 0x18 */ f32 gravity;
    /* 0x1C */ f32 knockbackSpeed;
    /* 0x20 */ f32 itemPickupRange[4]; // indexed by item type; [3] is the powerup
    /* 0x30 */ f32 cameraShakeFrames[2]; // [0] chomp landing, [1] bite
    /* 0x38 */ f32 cameraShakeMagnitude[2];
    /* 0x40 */ f32 speedBoostPerPoint;
    /* 0x44 */ f32 maxSpeedBoost;
} CcsGameplayConsts; // size: 0x48

typedef struct _CcsTimingConsts {
    /* 0x00 */ s16 turnOverFadeFrames;
    /* 0x02 */ s16 knockbackFrames;
    /* 0x04 */ s16 hitRecoverFrames;
    /* 0x06 */ s16 itemRespawnMinFrames;
    /* 0x08 */ s16 itemRespawnMaxFrames;
    /* 0x0A */ s16 specialItem0MinSeconds;
    /* 0x0C */ s16 specialItem0MaxSeconds;
    /* 0x0E */ s16 specialItem1MinSeconds;
    /* 0x10 */ s16 specialItem1MaxSeconds;
    /* 0x12 */ s16 chompJumpFrames;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
} CcsTimingConsts; // size: 0x18

typedef struct _CcsSpeedMults {
    /* 0x0 */ f32 unk_0;
    /* 0x4 */ f32 powerupBoost;
} CcsSpeedMults;

extern CcsGameplayConsts ccs_gameplayConsts;
extern CcsTimingConsts ccs_timingConsts;
extern CcsSpeedMults ccs_speedMults;

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
