#ifndef __GAME_MINIGAME_MINIGAME_EFFECTS_H_
#define __GAME_MINIGAME_MINIGAME_EFFECTS_H_

#include "mssbTypes.h"
#include "Dolphin/vec.h"
#include "Dolphin/gx.h"

/* One 0x50-byte particle emitter slot (see FireEmitterSlot in pitcher_fire_effect.c). */
typedef struct _MGFxSlot {
    /*0x00*/ u32 texture;
    /*0x04*/ s32 effectId;
    /*0x08*/ s32 params[18];
} MGFxSlot; // size: 0x50

/* Header record that precedes the effect id table. */
typedef struct _MGFxHeader {
    /*0x00*/ u32 texture;
    /*0x04*/ s32 params[16];
} MGFxHeader; // size: 0x44

typedef struct _MGParticle {
    /*0x00*/ struct _MGParticle* next;
    /*0x04*/ Vec origin;
    /*0x10*/ f32 velX;
    /*0x14*/ f32 velY;
    /*0x18*/ f32 velZ;
    /*0x1C*/ f32 _1C;
    /*0x20*/ f32 _20;
    /*0x24*/ f32 alpha;
    /*0x28*/ f32 _28;
    /*0x2C*/ f32 _2C;
    /*0x30*/ f32 _30;
    /*0x34*/ f32 _34;
    /*0x38*/ f32 sizeX;
    /*0x3C*/ f32 sizeY;
    /*0x40*/ u8 colorR;
    /*0x41*/ u8 colorG;
    /*0x42*/ u8 colorB;
    /*0x43*/ u8 alphaByte;
    /*0x44*/ u8 _44;
    /*0x45*/ u8 _45;
    /*0x46*/ u8 _46;
    /*0x47*/ u8 _47;
    /*0x48*/ s16 delay;
    /*0x4A*/ s16 life;
    /*0x4C*/ u8 kind;
    /*0x4D*/ u8 texIndex;
    /*0x4E*/ u8 _4E;
    /*0x4F*/ u8 _4F;
    /*0x50*/ u8 _50;
} MGParticle;

/* Handle returned by allocParticleEffect for a time-limited effect. */
typedef struct _MGEffect {
    /*0x00*/ u8 _00[0xC];
    /*0x0C*/ MGParticle* particles;
    /*0x10*/ u32 texture;
    /*0x14*/ u16 _14 : 4;
    /*0x14*/ u16 count : 12;
    /*0x16*/ u8 _16[2];
    /*0x18*/ s32 frame;
    /*0x1C*/ s32 duration;
} MGEffect;

/* Particle of an effect that follows a position and rotation owned by someone else. */
typedef struct _MGFollowParticle {
    /*0x00*/ struct _MGParticle* next;
    /*0x04*/ Vec origin;
    /*0x10*/ Vec* pos;
    /*0x14*/ Vec* rot;
    /*0x18*/ s16 id;
    /*0x1A*/ u8 _1A[0x38 - 0x1A];
    /*0x38*/ f32 sizeX;
    /*0x3C*/ f32 sizeY;
    /*0x40*/ u8 colorR;
    /*0x41*/ u8 colorG;
    /*0x42*/ u8 colorB;
    /*0x43*/ u8 alphaByte;
    /*0x44*/ u8 _44[0x48 - 0x44];
    /*0x48*/ s16 delay;
    /*0x4A*/ s16 life;
    /*0x4C*/ u8 kind;
    /*0x4D*/ u8 texIndex;
    /*0x4E*/ u8 _4E;
} MGFollowParticle;

typedef struct _MGActor {
    /*0x00*/ u8 _00[0xEC];
    /*0xEC*/ f32 (*mtx)[4];
} MGActor;

typedef struct _MGActorList {
    /*0x00*/ u8 _00[0x18];
    /*0x18*/ MGActor** actors;
} MGActorList;

typedef struct _MGWeatherCtx {
    /*0x00*/ MGActorList* list;
    /*0x04*/ u8 _04[0x6C - 0x04];
    /*0x6C*/ u8 active;
} MGWeatherCtx;

/* Effect whose particles are placed relative to an actor or a fixed position. */
typedef struct _MGWeatherEffect {
    /*0x00*/ u8 _00[0xC];
    /*0x0C*/ MGParticle* particles;
    /*0x10*/ u32 texture;
    /*0x14*/ u8 _14[0x18 - 0x14];
    /*0x18*/ MGWeatherCtx* ctx;
    /*0x1C*/ Vec pos;
} MGWeatherEffect;

/* Effect that moves along a two-segment path while its particles spray out. */
typedef struct _MGPathEffect {
    /*0x00*/ u8 _00[0xC];
    /*0x0C*/ MGParticle* particles;
    /*0x10*/ u32 texture;
    /*0x14*/ u8 _14[0x18 - 0x14];
    /*0x18*/ Vec base;
    /*0x24*/ Vec pos;
    /*0x30*/ f32 span;
    /*0x34*/ s16 total;
    /*0x36*/ s16 remaining;
} MGPathEffect;

/* Star Dash star effect: the actor slot index it follows is stored at +0x18. */
typedef struct _MGStarEffect {
    /*0x00*/ u8 _00[0xC];
    /*0x0C*/ MGParticle* particles;
    /*0x10*/ u32 texture;
    /*0x14*/ u16 _14 : 4;
    /*0x14*/ u16 count : 12;
    /*0x16*/ u8 _16[2];
    /*0x18*/ s8 index;
} MGStarEffect;

/* Node of the piranha spit trail effect: seven trail points per node. */
typedef struct _MGTrailNode {
    /*0x00*/ struct _MGTrailNode* next;
    /*0x04*/ Vec pts[7];
} MGTrailNode;

typedef struct _MGTrailEffect {
    /*0x00*/ u8 _00[0xC];
    /*0x0C*/ MGTrailNode* nodes;
    /*0x10*/ u8 _10[0x18 - 0x10];
    /*0x18*/ u8 done;
} MGTrailEffect;

/* Actor-like object whose collision-offset effect is drawn by piranhaPanic_emitFielderHitFire. */
typedef struct _MGFxActor {
    /*0x00*/ u8 _00[0x40];
    /*0x40*/ Vec rot;
    /*0x4C*/ u8 _4C[0x252 - 0x4C];
    /*0x252*/ s8 offsetIndex;
    /*0x253*/ u8 _253;
    /*0x254*/ s8 slotIndex;
    /*0x255*/ s8 animIndex;
} MGFxActor;

/* First part of the minigame effect tuning data (.data object minigameFxData, 0x266A8..0x26B9C). */
typedef struct _MGFxBase {
    /*0x000*/ f32 chompTrailScale[2];
    /*0x008*/ MGFxSlot slotsA[3];
    /*0x0F8*/ MGFxHeader headerA;
    /*0x13C*/ s16 effectIds[4][2];
    /*0x14C*/ MGFxSlot slotsB[3];
    /*0x23C*/ MGFxSlot* slotPtrs[3];
    /*0x248*/ u8 _248[0xC];
    /*0x254*/ s32 offsets[54][3];
    /*0x4DC*/ u32 colors[4];
    /*0x4EC*/ f32 tail[2];
} MGFxBase; // size: 0x4F4

/* View of minigameFxData extended over the small tables that follow it (.data 0x266A8..0x26F00); used where the code addresses those tables relative to minigameFxData. */
typedef struct _MGFxData {
    /*0x000*/ f32 chompTrailScale[2];
    /*0x008*/ MGFxSlot slotsA[3];
    /*0x0F8*/ MGFxHeader headerA;
    /*0x13C*/ s16 effectIds[4][2];
    /*0x14C*/ MGFxSlot slotsB[3];
    /*0x23C*/ MGFxSlot* slotPtrs[3];
    /*0x248*/ u8 _248[0xC];
    /*0x254*/ s32 offsets[54][3];
    /*0x4DC*/ u32 colors[4];
    /*0x4EC*/ f32 tail[2];
    /*0x4F4*/ u16 quadUv[4][2];
    /*0x504*/ f32 trailLo;
    /*0x508*/ f32 trailHi;
    /*0x50C*/ Vec hitOffset;
    /*0x518*/ s32 hitParams[7];
    /*0x534*/ s32 itemFxA[4];
    /*0x544*/ s32 itemFxB[4];
    /*0x554*/ s32 itemFxC[4];
    /*0x564*/ s32 itemFxD[4];
    /*0x574*/ f32 corners[8];
    /*0x594*/ s32 fxE[22];
    /*0x5EC*/ s32 fxF[9];
    /*0x610*/ u8 fxG[0x18];
    /*0x628*/ s32 fxH[12];
    /*0x658*/ s32 fxI[20];
    /*0x6A8*/ Vec fxJ;
    /*0x6B4*/ s32 fxK[11];
    /*0x6E0*/ s32 fxL[15];
    /*0x71C*/ s32 fxM[15];
    /*0x758*/ f32 fxN[9];
    /*0x77C*/ s32 fxO[7];
    /*0x798*/ s32 fxP[15];
    /*0x7D4*/ s32 fxQ[8];
    /*0x7F4*/ s32 fxR[25];
} MGFxData; // size: 0x858


/* Texture record as read by the quad drawer. */
typedef struct _MGTexRecord {
    /*0x00*/ void* image;
    /*0x04*/ void* tlut;
    /*0x08*/ u16 height;
    /*0x0A*/ u16 width;
    /*0x0C*/ u8 _0C[4];
    /*0x10*/ f32 lodBias;
    /*0x14*/ u8 _14;
    /*0x15*/ u8 minLod;
    /*0x16*/ u8 maxLod;
    /*0x17*/ u8 format;
    /*0x18*/ u16 tlutEntries;
    /*0x1A*/ u8 tlutFormat;
} MGTexRecord;

typedef struct _MGQuadVertex {
    /*0x00*/ Vec pos;
    /*0x0C*/ u32 color;
    /*0x10*/ u16 s;
    /*0x12*/ u16 t;
} MGQuadVertex; // size: 0x14

/* First part of the minigame effect tuning data (.data object minigameFxData). */
typedef struct _MGFxHead {
    /*0x000*/ f32 trailScale[2];
    /*0x008*/ MGFxSlot slotsA[3];
    /*0x0F8*/ MGFxHeader headerA;
    /*0x13C*/ s16 effectIds[4][2];
} MGFxHead; // size: 0x14C

/* Object at minigameFxTail: the last slot, the slot pointer table and the offset/colour tables. */
typedef struct _MGFxTail {
    /*0x000*/ MGFxSlot slot;
    /*0x050*/ MGFxSlot* slotPtrs[3];
    /*0x05C*/ u8 _5C[0xC];
    /*0x068*/ s32 offsets[54][3];
    /*0x2F0*/ u32 colors[4];
    /*0x300*/ f32 tail[2];
} MGFxTail; // size: 0x308

void chainChomp_spawnTrailEffect(s32 duration);
int chainChomp_updateTrailEffect(MGEffect* effect);
f32 chainChomp_trailScale(s32 frame);
void chainChomp_stopTrailEffect(void);
void piranhaPanic_updateSpitTrailEffect(void);
Vec* minigameTrail_getPoint(u32 index);
void minigameTrail_alloc(int count);
void minigameTrail_finish(void);
void piranhaPanic_emitFielderHitFire(MGFxActor* actor);
void minigameTrail_setPoint(u32 index, f32 x, f32 y, f32 z);
void piranhaPanic_drawSpitTrail(u32 index, f32 x, f32 y, f32 z);
void minigameTrail_drawQuad(Vec* positions, u32 color, MGTexRecord* tex);
void starDash_drawFireBarTrail(u32 index, f32 x, f32 y, f32 z);
void bODPitchAnimation(void);
void bobOmbFuseSpark_spawnAtPitch(void);
void bobOmbFuseSpark_initAtPitch(MGEffect* effect);
void bobOmbFuseSpark_placeParticle(MGParticle* p, Vec* base, Vec* rot);
int bobOmbFuseSpark_updateAtPitch(MGEffect* effect);
void bobOmbDerbyPitching(void);
void bobOmbDerbyPitching2(void);
void bobOmbFuseSpark_spawnFollow(s16 id, Vec* pos, Vec* rot);
void bobOmbFuseSpark_spawnFollowEffect(s16 id, Vec* pos, Vec* rot);
void bobOmbFuseSpark_initFollow(MGEffect* effect, s16 id, Vec* pos, Vec* rot);
int bobOmbFuseSpark_updateFollow(MGEffect* effect);
void bobOmbFuseSpark_removeFollow(s16 id);
void bobOmbFuseSpark_stopFollow(void);
void chainChomp_spawnItemSparkle(u8 kind, u8 mode, Vec* pos);
void chainChomp_spawnItemSparkleEffect(u8 kind, u8 mode, Vec* pos);
void chainChomp_initItemSparkleParticles(MGEffect* effect, u8 kind, u8 mode, Vec* pos);
void chainChomp_initItemSparkleParticle(MGParticle* p, Vec* pos, u8 kind, u8 mode, u8 index);
void chainChomp_placeItemSparkleLayer(MGParticle* p, u8 kind);
void chainChomp_initItemSparkleLayer1(MGParticle* p);
void chainChomp_initItemSparkleLayer2(MGParticle* p);
void chainChomp_flyItemSparklesToScore(u8 id, u8 flag);
void chainChomp_initItemSparkleFly(MGParticle* p);
void chainChomp_placeItemSparkle(MGParticle* p, u8 randomize);
int chainChomp_updateItemSparkles(MGEffect* effect);
void chainChomp_updateItemSparkleLayer1(MGEffect* effect, MGParticle* p);
void chainChomp_updateItemSparkleLayer2(MGEffect* effect, MGParticle* p);
void chainChomp_updateItemSparkleFly(MGEffect* effect, MGParticle* p);
void chainChomp_drawItemSparkleOnHud(MGParticle* p, MGEffect* effect);
void chainChomp_stopItemSparkles(void);
void chainChomp_stopItemSparkles2(void);
void wallBall_spawnNoteBlockBurst(MGWeatherCtx* ctx, Vec* pos);
void wallBall_spawnNoteBlockBurstEffect(MGWeatherCtx* ctx, Vec* pos);
void wallBall_initNoteBlockBurst(MGWeatherEffect* effect, MGWeatherCtx* ctx, Vec* pos);
void wallBall_placeNoteParticle(MGWeatherEffect* effect, MGParticle* p);
void wallBall_placeBounceParticle(MGWeatherEffect* effect, MGParticle* p);
int wallBall_updateNoteBlockBurst(MGWeatherEffect* effect);
void wallBall_updateNoteParticle(MGWeatherEffect* effect, MGParticle* p);
void wallBall_updateBounceParticle(MGWeatherEffect* effect, MGParticle* p);
void wallBall_updateSomePointers(void);
void wallBall_updateSomePointers2(void);
void starDash_startSparks(s8 index);
void starDash_spawnSparksEffect(s8 index);
void starDash_initSparksEffect(MGEffect* effect);
void starDash_setupSparks(MGEffect* effect, s8 index);
void starDash_resetSparkParticle(MGParticle* p);
void starDash_randomizeSparkOrigin(MGParticle* p);
int starDash_updateSparks(MGEffect* effect);
void starDash_placeSparkParticle(MGParticle* p);
void starDash_offsetSparkToBone(MGParticle* p);
void starDash_stopSparks(s8 index);
void starDash_stopSparks2(s8 index);
void starDash_stopAllSparks(void);
void starDash_stopAllSparks2(void);
void starDash_spawnDust(Vec* pos);
void starDash_spawnDustEffect(Vec* pos);
void starDash_initDustParticles(MGEffect* effect, Vec* pos);
int starDash_updateDust(MGEffect* effect);
void starDash_stopDust(void);
void barrelBatter_spawnBarrelExplosion(s8 index);
void barrelBatter_spawnBarrelExplosionEffect(u8 index);
void barrelBatter_initBarrelExplosion(MGEffect* effect);
void barrelBatter_setupBarrelExplosion(MGEffect* effect, u8 barrelIndex);
void barrelBatter_placeExplosionFlash(MGParticle* p);
void barrelBatter_attachExplosionToBone(MGParticle* p);
int barrelBatter_updateBarrelExplosion(MGEffect* effect);
void barrelBatter_updateExplosionFlash(MGEffect* effect, MGParticle* p);
void barrelBatter_updateExplosionEmber(MGEffect* effect, MGParticle* p);
void barrelBatter_releaseBarrelExplosion(s8 index);
void barrelBatter_releaseBarrelExplosion2(s8 index);
void barrelBatter_clearExplosionParticle(MGParticle* p);
void barrelBatter_stopBarrelExplosions(void);
void chainChomp_spawnLaunchFlash(void);
void chainChomp_spawnLaunchFlashEffect(void);
void chainChomp_initLaunchFlash(MGEffect* effect);
int chainChomp_updateLaunchFlash(MGEffect* effect);
void chainChomp_placeLaunchFlash(MGParticle* p);
void chainChomp_stopLaunchFlash(void);
void wallBall_spawnWallHitPuff(Vec* pos, u8 flag);
void wallBall_spawnWallHitPuffEffect(Vec* pos, u8 flag);
void wallBall_initWallHitPuff(MGEffect* effect, Vec* pos, u8 flag);
int wallBall_updateWallHitPuff(MGEffect* effect);
void wallBall_stopWallHitPuff(void);
void barrelBatter_spawnMachineSparks(s32 frames, Vec* start);
void barrelBatter_spawnMachineSparksEffect(s32 frames, Vec* start);
void barrelBatter_initMachineSparks(MGPathEffect* effect, s32 frames, Vec* start);
void barrelBatter_updateMachineSparkPos(MGPathEffect* effect);
void barrelBatter_respawnMachineSpark(MGPathEffect* effect, MGParticle* p);
int barrelBatter_updateMachineSparks(MGPathEffect* effect);
void barrelBatter_stopMachineSparks(void);
void barrelBatterRel(Vec* pos);
void barrelBatterRel2(Vec* pos);
void barrelBatter_initReleaseRing(MGEffect* effect, Vec* pos);
int barrelBatter_updateReleaseRing(MGEffect* effect);
void barrelBatter_stopReleaseRing(void);
void minigameWinnerStars_setWinners(s32* values, s32 count);
void minigameWinnerStars_spawn(void);
void minigameWinnerStars_spawnOne(s8 index);
void minigameWinnerStars_initEffect(MGStarEffect* effect);
void minigameWinnerStars_resetParticle(MGStarEffect* effect, MGParticle* p);
void minigameWinnerStars_getLaunchVelocity(MGParticle* p, f32 degrees);
int minigameWinnerStars_update(MGStarEffect* effect);
E(u8, BOOL) minigameWinnerStars_rollTurn(void);
void minigameWinnerStars_setupMtx(MGStarEffect* effect, MGParticle* p);
void minigameWinnerStars_drawQuad(MGParticle* p);
void minigameWinnerStars_beginDraw(void);
void minigameWinnerStars_endDraw(void);
void minigameStopBombExplosion(void);
void piranhaPanic_spawnBombExplosion(Vec* pos);
void piranhaPanic_spawnBombExplosionEffect(Vec* pos);
void piranhaPanic_initBombExplosion(MGEffect* effect, Vec* pos);
int piranhaPanic_updateBombExplosion(MGEffect* effect);
void minigameStopBombExplosion2(void);

#endif // !__GAME_MINIGAME_MINIGAME_EFFECTS_H_
