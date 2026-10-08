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
    /*0x38*/ f32 _38;
    /*0x3C*/ f32 _3C;
    /*0x40*/ u8 _40;
    /*0x41*/ u8 _41;
    /*0x42*/ u8 _42;
    /*0x43*/ u8 alphaByte;
    /*0x44*/ u8 _44;
    /*0x45*/ u8 _45;
    /*0x46*/ u8 _46;
    /*0x47*/ u8 _47;
    /*0x48*/ s16 _48;
    /*0x4A*/ s16 _4A;
    /*0x4C*/ u8 _4C;
    /*0x4D*/ u8 _4D;
    /*0x4E*/ u8 _4E;
    /*0x4F*/ u8 _4F;
    /*0x50*/ u8 _50;
} MGParticle;

/* Handle returned by allocParticleEffect for a time-limited effect. */
typedef struct _MGEffect {
    /*0x00*/ u8 _00[0xC];
    /*0x0C*/ MGParticle* particles;
    /*0x10*/ u32 _10;
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
    /*0x38*/ f32 _38;
    /*0x3C*/ f32 _3C;
    /*0x40*/ u8 _40;
    /*0x41*/ u8 _41;
    /*0x42*/ u8 _42;
    /*0x43*/ u8 alphaByte;
    /*0x44*/ u8 _44[0x48 - 0x44];
    /*0x48*/ s16 _48;
    /*0x4A*/ s16 _4A;
    /*0x4C*/ u8 _4C;
    /*0x4D*/ u8 _4D;
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
    /*0x10*/ u32 _10;
    /*0x14*/ u8 _14[0x18 - 0x14];
    /*0x18*/ MGWeatherCtx* ctx;
    /*0x1C*/ Vec pos;
} MGWeatherEffect;

/* Effect that moves along a two-segment path while its particles spray out. */
typedef struct _MGPathEffect {
    /*0x00*/ u8 _00[0xC];
    /*0x0C*/ MGParticle* particles;
    /*0x10*/ u32 _10;
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
    /*0x10*/ u32 _10;
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

/* Actor-like object whose collision-offset effect is drawn by fn_3_1573AC. */
typedef struct _MGFxActor {
    /*0x00*/ u8 _00[0x40];
    /*0x40*/ Vec rot;
    /*0x4C*/ u8 _4C[0x252 - 0x4C];
    /*0x252*/ s8 offsetIndex;
    /*0x253*/ u8 _253;
    /*0x254*/ s8 slotIndex;
    /*0x255*/ s8 animIndex;
} MGFxActor;

/* First part of the minigame effect tuning data (.data object lbl_3_data_266A8, 0x266A8..0x26B9C). */
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

/* View of lbl_3_data_266A8 extended over the small tables that follow it (.data 0x266A8..0x26F00); used where the code addresses those tables relative to lbl_3_data_266A8. */
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

/* First part of the minigame effect tuning data (.data object lbl_3_data_266A8). */
typedef struct _MGFxHead {
    /*0x000*/ f32 trailScale[2];
    /*0x008*/ MGFxSlot slotsA[3];
    /*0x0F8*/ MGFxHeader headerA;
    /*0x13C*/ s16 effectIds[4][2];
} MGFxHead; // size: 0x14C

/* Object at lbl_3_data_26894: the last slot, the slot pointer table and the offset/colour tables. */
typedef struct _MGFxTail {
    /*0x000*/ MGFxSlot slot;
    /*0x050*/ MGFxSlot* slotPtrs[3];
    /*0x05C*/ u8 _5C[0xC];
    /*0x068*/ s32 offsets[54][3];
    /*0x2F0*/ u32 colors[4];
    /*0x300*/ f32 tail[2];
} MGFxTail; // size: 0x308

void chainChomp_spawnTrailEffect(s32 duration);
int fn_3_157AC4(MGEffect* effect);
f32 fn_3_15791C(s32 frame);
void fn_3_1578F8(void);
void fn_3_15767C(void);
Vec* fn_3_1575F0(u32 index);
void fn_3_157588(int count);
void fn_3_157570(void);
void fn_3_1573AC(MGFxActor* actor);
void fn_3_15730C(u32 index, f32 x, f32 y, f32 z);
void fn_3_156D04(u32 index, f32 x, f32 y, f32 z);
void fn_3_156970(Vec* positions, u32 color, MGTexRecord* tex);
void fn_3_156548(u32 index, f32 x, f32 y, f32 z);
void bODPitchAnimation(void);
void fn_3_155F08(void);
void fn_3_155C28(MGEffect* effect);
void fn_3_1559E4(MGParticle* p, Vec* base, Vec* rot);
int fn_3_1552AC(MGEffect* effect);
void bobOmbDerbyPitching(void);
void fn_3_155264(void);
void fn_3_15521C(s16 id, Vec* pos, Vec* rot);
void fn_3_154C7C(s16 id, Vec* pos, Vec* rot);
void fn_3_1549F0(MGEffect* effect, s16 id, Vec* pos, Vec* rot);
int fn_3_1542F4(MGEffect* effect);
void fn_3_154238(s16 id);
void fn_3_154214(void);
void fn_3_1541C4(u8 kind, u8 mode, Vec* pos);
void fn_3_1540E4(u8 kind, u8 mode, Vec* pos);
void fn_3_153F8C(MGEffect* effect, u8 kind, u8 mode, Vec* pos);
void fn_3_153E8C(MGParticle* p, Vec* pos, u8 kind, u8 mode, u8 index);
void fn_3_1536A8(MGParticle* p, u8 kind);
void fn_3_1534C0(MGParticle* p);
void fn_3_1531A4(MGParticle* p);
void fn_3_152AB4(u8 id, u8 flag);
void fn_3_152794(MGParticle* p);
void fn_3_1524E8(MGParticle* p, u8 randomize);
int fn_3_151F2C(MGEffect* effect);
void fn_3_151D6C(MGEffect* effect, MGParticle* p);
void fn_3_151BAC(MGEffect* effect, MGParticle* p);
void fn_3_1519F8(MGEffect* effect, MGParticle* p);
void fn_3_1517D0(MGParticle* p, MGEffect* effect);
void fn_3_151798(void);
void fn_3_151760(void);
void fn_3_151710(MGWeatherCtx* ctx, Vec* pos);
void fn_3_151694(MGWeatherCtx* ctx, Vec* pos);
void fn_3_151204(MGWeatherEffect* effect, MGWeatherCtx* ctx, Vec* pos);
void fn_3_151068(MGWeatherEffect* effect, MGParticle* p);
void fn_3_150D84(MGWeatherEffect* effect, MGParticle* p);
int fn_3_150940(MGWeatherEffect* effect);
void fn_3_1504EC(MGWeatherEffect* effect, MGParticle* p);
void fn_3_150120(MGWeatherEffect* effect, MGParticle* p);
void wallBall_updateSomePointers(void);
void fn_3_150070(void);
void fn_3_150010(s8 index);
void fn_3_14F930(s8 index);
void fn_3_14F8D0(MGEffect* effect);
void fn_3_14F5A4(MGEffect* effect, s8 index);
void fn_3_14F544(MGParticle* p);
void fn_3_14F3CC(MGParticle* p);
int fn_3_14ED24(MGEffect* effect);
void fn_3_14EAF4(MGParticle* p);
void fn_3_14E9F0(MGParticle* p);
void fn_3_14E988(s8 index);
void fn_3_14E920(s8 index);
void fn_3_14E894(void);
void fn_3_14E810(void);
void fn_3_14E7C0(MGEffect* arg);
void fn_3_14E234(Vec* pos);
void fn_3_14DF6C(MGEffect* effect, Vec* pos);
int fn_3_14DD04(MGEffect* effect);
void fn_3_14DCE0(void);
void fn_3_14DC80(s8 index);
void fn_3_14D710(u8 index);
void fn_3_14D6D4(MGEffect* effect);
void fn_3_14D44C(MGEffect* effect, int barrelIndex);
void fn_3_14D318(MGParticle* p);
void fn_3_14D2C0(MGParticle* p);
int fn_3_14CECC(MGEffect* effect);
void fn_3_14CD40(MGEffect* effect, MGParticle* p);
void fn_3_14CBB4(MGEffect* effect, MGParticle* p);
void fn_3_14CB28(s8 index);
void fn_3_14CAB4(s8 index);
void fn_3_14CA98(MGParticle* p);
void fn_3_14CA00(void);
void fn_3_14C904(void);
void fn_3_14C830(void);
void fn_3_14C79C(MGEffect* effect);
int fn_3_14C4C8(MGEffect* effect);
void fn_3_14C3BC(MGParticle* p);
void fn_3_14C398(void);
void fn_3_14C348(Vec* pos, u8 flag);
void fn_3_14BECC(Vec* pos, u8 flag);
void fn_3_14BCB0(MGEffect* effect, Vec* pos, u8 flag);
int fn_3_14BA40(MGEffect* effect);
void fn_3_14B9F0(void);
void fn_3_14B9A0(s16 frames, Vec* start);
void fn_3_14B92C(s16 frames, Vec* start);
void fn_3_14B53C(MGPathEffect* effect, s16 frames, Vec* start);
void fn_3_14B3F4(MGPathEffect* effect);
void fn_3_14B248(MGPathEffect* effect, MGParticle* p);
int fn_3_14AC40(MGPathEffect* effect);
void fn_3_14AC1C(void);
void barrelBatterRel(Vec* pos);
void fn_3_14A62C(Vec* pos);
void fn_3_14A37C(MGEffect* effect, Vec* pos);
int fn_3_14A188(MGEffect* effect);
void fn_3_14A164(void);
void fn_3_14A070(s32* values, s32 count);
void fn_3_149BA8(void);
void fn_3_14975C(s8 index);
void fn_3_149340(MGStarEffect* effect);
void fn_3_148FD0(s8 index, MGParticle* p);
void fn_3_148EF0(Vec* out, f32 degrees);
int fn_3_14841C(MGStarEffect* effect);
BOOL fn_3_1483D4(void);
void fn_3_148254(MGStarEffect* effect, MGParticle* p);
void fn_3_1480E0(MGParticle* p);
void fn_3_147F94(void);
void fn_3_147E20(void);
void fn_3_147DFC(void);
void fn_3_147CFC(Vec* pos);
void fn_3_147C00(Vec* pos);
void fn_3_147778(MGEffect* effect, Vec* pos);
int fn_3_14737C(MGEffect* effect);
void fn_3_147358(void);

#endif // !__GAME_MINIGAME_MINIGAME_EFFECTS_H_
