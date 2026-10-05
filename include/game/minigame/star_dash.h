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

typedef struct {
    /*0x00*/ VecXYZ pos;
    /*0x0C*/ u8 _0C[0x22 - 0x0C];
    /*0x22*/ s16 _22;
    /*0x24*/ u8 _24[2];
    /*0x26*/ u8 active;
    /*0x27*/ u8 _27;
} SDFireBarFlame; // size: 0x28

typedef struct {
    /*0x00*/ VecXYZ start;
    /*0x0C*/ VecXYZ end;
} SDFireBar; // size: 0x18

typedef struct {
    /*0x00*/ VecXYZ pos;
    /*0x0C*/ VecXYZ vel;
    /*0x18*/ s32 coin[10];
    /*0x40*/ u8 active;
    /*0x41*/ u8 _41[3];
} SDCoinBag; // size: 0x44

typedef struct {
    /*0x0*/ f32 avoidMargin; // extra fire-bar clearance, 3.0 or 1.5
    /*0x4*/ s16 angle;
    /*0x6*/ u8 state;
    /*0x7*/ s8 counter;
} SDAI; // size: 0x8

typedef struct {
    /*0x00*/ SDAI ai[4];
    /*0x20*/ f32 rotSin;
    /*0x24*/ f32 rotCos;
} SDAIState; // size: 0x28

/* Star Dash's view of g_Minigame. */
typedef struct _SDState {
    /*0x0000*/ u8 _0000[0xA8];
    /*0x00A8*/ SDFireBarFlame fireBarFlame[40]; // 10 flames per fire bar
    /*0x06E8*/ VecXYZ starPos;
    /*0x06F4*/ VecXYZ starPath[3];
    /*0x0718*/ u8 _0718[0x724 - 0x718];
    /*0x0724*/ s16 starFrames;
    /*0x0726*/ s16 pathFrames;
    /*0x0728*/ s16 pathDuration;
    /*0x072A*/ u8 starActive;
    /*0x072B*/ u8 starBounces;
    /*0x072C*/ u8 _072C[0xB6C - 0x72C];
    /*0x0B6C*/ SDCoinBag coinBag;
    /*0x0BB0*/ SDThwomp thwomp[4];
    /*0x0CB0*/ u8 _0CB0[0x1CE8 - 0xCB0];
    /*0x1CE8*/ SDFireBar fireBar[4];
    /*0x1D48*/ f32 fireBarExtent; // 0..1 while growing/shrinking
    /*0x1D4C*/ f32* factor;
    /*0x1D50*/ s16 spawnTimer;
    /*0x1D52*/ s16 starSpawnTimer;
    /*0x1D54*/ u16 spawnCount;
    /*0x1D56*/ s16 holderFrames;
    /*0x1D58*/ s16 _1D58;
    /*0x1D5A*/ s16 stunFrames[4];
    /*0x1D62*/ s16 fireBarFrames;
    /*0x1D64*/ s16 fireBarAngle[4];
    /*0x1D6C*/ u8 spawnedCoins;
    /*0x1D6D*/ s8 holder;
    /*0x1D6E*/ u8 _1D6E[4];
    /*0x1D72*/ u8 fireBarPhase; // 0 off, 1 growing, 2 out, 3 shrinking
    /*0x1D73*/ u8 fireBarWave;
    /*0x1D74*/ u8 _1D74[2];
    /*0x1D76*/ s16 x_1D76;
    /*0x1D78*/ u8 x_1D78[4];
    /*0x1D7C*/ u8 _1D7C[0x1DCC - 0x1D7C];
    /*0x1DCC*/ SDAIState aiState;
    /*0x1DF4*/ u8 _1DF4[4];
} SDState;

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
