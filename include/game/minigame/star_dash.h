#ifndef __GAME_MINIGAME_STAR_DASH_H_
#define __GAME_MINIGAME_STAR_DASH_H_

#include "mssbTypes.h"
#include "Dolphin/gx.h"
#include "game/UnknownHomes_Game.h"
#include "game/ball/collision_primitives.h"
#include "static/UnknownHomes_Static.h"

typedef struct {
    /*0x00*/ f32 score;
    /*0x04*/ s32 coin;
    /*0x08*/ f32 x;
    /*0x0C*/ f32 z;
    /*0x10*/ u8 quadrant;
    /*0x11*/ u8 valid;
    /*0x12*/ u8 _12[2];
} SDCoinEntry; // size: 0x14

typedef struct _SDThwomp {
    /*0x00*/ VecXYZ pos;
    /*0x0C*/ VecXYZ vel;
    /*0x18*/ VecXYZ rot;
    /*0x24*/ VecXYZ rotVel;
    /*0x30*/ f32 sectorStart; // degrees around the pillar this Thwomp may land in
    /*0x34*/ f32 sectorEnd;
    /*0x38*/ s16 timer;
    /*0x3A*/ s16 frames;
    /*0x3C*/ s8 owner;
    /*0x3D*/ u8 state;
    /*0x3E*/ u8 stunSfxPending;
    /*0x3F*/ u8 stunSfxFrames;
} SDThwomp; // size: 0x40

void sD_PulseTevCallback(void* model, GXTevStageID* stage, GXTexCoordID* coord, GXTexMapID* map, s8* nStages, s8* nCoords);
void sD_UpdatePulseTexture(void);
void sD_InitPulseTexture(void);
void sD_ClearAIInputFlags(void);
void sD_UpdateAI(void);
BOOL sD_IsAheadAroundCenter(int a, int b);
s16 sD_AITurnToward(s16 a, s16 b, u32 c);
void sD_AIPickTargetPlayer(u32 target, f32* outX, f32* outZ, u32* outQuadrant);
int sD_AIRouteAroundCenter(u32 player, f32* targetX, f32* targetZ, u32 depth);
BOOL sD_AIPathBlocked(u32 player, int a, u32 b, f32 x, f32 z);
u32 sD_SegmentHitsCircle(f32 cx, f32 cz, f32 radius, f32 ax, f32 az, f32 bx, f32 bz);
SDCoinEntry* sD_AIRankCoins(u32 player, u32 quadrant, u32 count, SDCoinEntry* entries);
BOOL sD_IsNearThwomp(u32 item, f32 x, f32 z);
u32 sD_FireBarZone(f32 x, f32 z, f32 radius);
void sD_ToFireBarSpace(f32 x, f32 z, f32* outX, f32* outZ);
int sD_GetQuadrant(f32 x, f32 z);
int sD_CompareCoinEntries(const void* a, const void* b);
void sD_InitAI(void);
void sD_PushToPillarEdge(Vec* out, Vec* dir);
void sD_KeepOutOfPillar(Vec* pos);
void sD_PushCoinsOutOfPillar(void);
void sD_FireBarBurnPlayers(void);
void sD_UpdateFireBars(void);
void sD_FireBarHold(void);
void sD_FireBarShrink(void);
void sD_FireBarGrow(void);
void sD_CheckFireBarStart(void);
void sD_RotateFireBars(void);
void sD_DropCoins(int player);
void sD_UpdateStuns(void);
void sD_UpdateLoosePowerup(MinigamePowerupStruct* powerup);
void sD_UpdatePowerupTimer(MinigamePowerupStruct* powerup);
void sD_UpdatePowerup(void);
void sD_CameraShakeCallback(camera_803c639c_s* cam);
void sD_StartCameraShake(void);
void sD_ThwompScatterCoins(Vec* pos);
u8 sD_CollideWithThwomps(VecSrcDst* segment, Vec* velocity, CollisionStruct* out, f32 radius);
BOOL sD_IsBlockedByThwomp(int fielderIndex);
u8 sD_ThwompHitPlayers(SDThwomp* item);
void sD_ThwompRise(SDThwomp* item);
void sD_ThwompKicked(SDThwomp* item);
void sD_ThwompGrounded(SDThwomp* item);
void sD_ThwompFall(SDThwomp* item);
void sD_ThwompHover(SDThwomp* item);
void sD_ThwompWait(SDThwomp* item);
void sD_ThwompPlace(SDThwomp* item);
void sD_UpdateThwomps(void);
void sD_UpdateCoinBag(void);
void sD_CheckCoinBag(void);
void sD_UpdateCollectedCoins(void);
void sD_UpdateLooseCoins(void);
void sD_SpawnCoins(void);
void sD_UpdateCoins(void);
void minigame_transferPoints(int toTeam, int fromTeam);
void sD_UpdateStar(void);
void sD_NewStarArc(void);
void sD_UpdateStarSpawn(void);
void sD_UpdateStarAndHolder(void);
void sD_ReflectStarArc(CollisionStruct* hit);
void sD_ReflectVec(Vec* out, Vec* in, Vec* normal);
void sD_EndGame(void);
void sD_UpdateTimeUp(void);
void starDashLiveBall(void);
void sD_Postgame(void);
void sD_StartPlay(void);
void sD_RoundIntro(void);
void sD_LoadGame(void);
void sD_EmptyHook(void);
void starDashSwitcher(void);

#endif // !__GAME_MINIGAME_STAR_DASH_H_
