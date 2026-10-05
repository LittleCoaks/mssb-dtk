#ifndef __GAME_MINIGAME_PIRANHA_PANIC_H_
#define __GAME_MINIGAME_PIRANHA_PANIC_H_

#include "mssbTypes.h"
#include "Dolphin/GX/GXEnum.h"
#include "game/UnknownHomes_Game.h"

#define PP_SPAWNER_COUNT 3
#define PP_OBJECT_COUNT 40
#define PP_PLAYER_COUNT 4
#define PP_HELD_BALL_COUNT 3
#define PP_SCORE_ENTRY_COUNT 10

/* One piranha plant: emerges from a hole (mode 1), is active (2), retracts (3)
 * or is recovering after being fed (4); mode 0 is hidden. */
typedef struct _PPSpawner {
    /*0x00*/ VecXYZ pos;
    /*0x0C*/ f32 _0C;
    /*0x10*/ f32 angle;
    /*0x14*/ f32 _14;
    /*0x18*/ s16 _18;
    /*0x1A*/ s16 _1A;
    /*0x1C*/ s16 _1C;
    /*0x1E*/ s16 _1E;
    /*0x20*/ s16 _20;
    /*0x22*/ s16 _22;
    /*0x24*/ s16 _24;
    /*0x26*/ s16 _26;
    /*0x28*/ s16 _28;
    /*0x2A*/ u8 mode;
    /*0x2B*/ u8 isBig; // the special plant that accepts any ball
    /*0x2C*/ u8 kind; // hole / ball kind it accepts; 4 = any
    /*0x2D*/ u8 hitsLeft;
    /*0x2E*/ u8 _2E;
    /*0x2F*/ s8 queue[4];
    /*0x33*/ u8 _33;
    /*0x34*/ s8 _34;
    /*0x35*/ s8 _35;
    /*0x36*/ u8 _36[2];
} PPSpawner; // size: 0x38

typedef struct _PPObject {
    /*0x00*/ VecXYZ pos;
    /*0x0C*/ VecXYZ vel;
    /*0x18*/ f32 _18;
    /*0x1C*/ s32 _1C;
    /*0x20*/ s16 _20;
    /*0x22*/ s16 _22;
    /*0x24*/ s16 _24;
    /*0x26*/ u8 state;
    /*0x27*/ u8 _27;
} PPObject; // size: 0x28


typedef struct _PPAI {
    /*0x0*/ s16 timer;
    /*0x2*/ s8 state;
    /*0x3*/ s8 selection;
} PPAI; // size: 0x4

#define PP_BALL_COUNT 50

/* Piranha Panic's view of g_Minigame: the mini-game state overlays storage that
 * MiniGameStruct does not name for this mode. Fields MiniGameStruct already
 * names (turnOverStatus, multiPlayerInd, ...) are still read through g_Minigame. */
typedef struct _PPState {
    /*0x0000*/ PPSpawner spawner[PP_SPAWNER_COUNT];
    /*0x00A8*/ PPObject object[PP_OBJECT_COUNT];
    /*0x06E8*/ u8 x_6E8[0xCD0 - 0x6E8];
    /*0x0CD0*/ VecXYZ ballPos[PP_BALL_COUNT];
    /*0x0F28*/ u8 _F28[0x1180 - 0xF28];
    /*0x1180*/ VecXYZ ballVel[PP_BALL_COUNT];
    /*0x13D8*/ u8 _13D8[0x17C0 - 0x13D8];
    /*0x17C0*/ u32 frameCount;
    /*0x17C4*/ u32 framesRemaining;
    /*0x17C8*/ s16 ballFrames[PP_BALL_COUNT];
    /*0x182C*/ u8 _182C[0x1890 - 0x182C];
    /*0x1890*/ s16 pointsA[PP_PLAYER_COUNT];
    /*0x1898*/ s16 pointsB[PP_PLAYER_COUNT];
    /*0x18A0*/ u8 _18A0[0x18BC - 0x18A0];
    /*0x18BC*/ s16 pointsLatest[PP_PLAYER_COUNT][2];
    /*0x18CC*/ s8 character[PP_PLAYER_COUNT];
    /*0x18D0*/ u8 _18D0[0x18D8 - 0x18D0];
    /*0x18D8*/ u8 aiControlled[PP_PLAYER_COUNT];
    /*0x18DC*/ u8 aiStrength[PP_PLAYER_COUNT];
    /*0x18E0*/ u8 _18E0[0x18E8 - 0x18E0];
    /*0x18E8*/ u8 _18E8[8];
    /*0x18F0*/ u8 _18F0[PP_PLAYER_COUNT];
    /*0x18F4*/ s8 _18F4[PP_PLAYER_COUNT];
    /*0x18F8*/ s8 fielderIndex[PP_PLAYER_COUNT];
    /*0x18FC*/ s8 x_18FC[PP_PLAYER_COUNT];
    /*0x1900*/ s8 x_1900[PP_PLAYER_COUNT];
    /*0x1904*/ u8 _1904[0x193A - 0x1904];
    /*0x193A*/ u8 ballState[PP_BALL_COUNT];
    /*0x196C*/ u8 x_196C[0x1B34 - 0x196C];
    /*0x1B34*/ s16 swingFrames[PP_PLAYER_COUNT];
    /*0x1B3C*/ s16 stateFrames[PP_PLAYER_COUNT];
    /*0x1B44*/ s16 downFrames[PP_PLAYER_COUNT];
    /*0x1B4C*/ s16 x_1B4C;
    /*0x1B4E*/ s16 x_1B4E;
    /*0x1B50*/ s16 hitCount[PP_PLAYER_COUNT];
    /*0x1B58*/ u8 scoreEntries[PP_PLAYER_COUNT][PP_SCORE_ENTRY_COUNT];
    /*0x1B80*/ u8 scoreEntryCount[PP_PLAYER_COUNT];
    /*0x1B84*/ u8 ballKind[PP_BALL_COUNT];
    /*0x1BB6*/ s8 ballOwner[PP_BALL_COUNT];
    /*0x1BE8*/ s8 ballTarget[PP_BALL_COUNT];
    /*0x1C1A*/ u8 x_1C1A[PP_BALL_COUNT];
    /*0x1C4C*/ u8 x_1C4C[PP_BALL_COUNT];
    /*0x1C7E*/ s8 heldBalls[PP_PLAYER_COUNT][PP_HELD_BALL_COUNT];
    /*0x1C8A*/ u8 spawnCount[PP_PLAYER_COUNT];
    /*0x1C8E*/ u8 throwBall[PP_PLAYER_COUNT];
    /*0x1C92*/ s8 throwDirection[PP_PLAYER_COUNT];
    /*0x1C96*/ u8 _1C96[PP_PLAYER_COUNT];
    /*0x1C9A*/ u8 hitState[PP_PLAYER_COUNT];
    /*0x1C9E*/ u8 targeted[PP_PLAYER_COUNT];
    /*0x1CA2*/ u8 x_1CA2;
    /*0x1CA3*/ u8 x_1CA3;
    /*0x1CA4*/ u8 x_1CA4;
    /*0x1CA5*/ u8 playerState[PP_PLAYER_COUNT];
    /*0x1CA9*/ u8 holeUsed[PP_PLAYER_COUNT];
    /*0x1CAD*/ u8 goalIndex[PP_PLAYER_COUNT];
    /*0x1CB1*/ u8 x_1CB1[PP_PLAYER_COUNT];
    /*0x1CB5*/ u8 _1CB5[0x1DCC - 0x1CB5];
    /*0x1DCC*/ PPAI ai[PP_PLAYER_COUNT];
    /*0x1DDC*/ u8 _1DDC[0x1DF4 - 0x1DDC];
    /*0x1DF4*/ u8 x_1DF4[PP_PLAYER_COUNT];
} PPState;

void pP_CountPulseDraws(void);
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
void pP_ReleaseThrow(int p);
void pP_UpdateCrouch(int p);
void pP_UpdatePlayers(void);
void pP_UpdateThrownBall(int p);
void pP_SetHeldBallPos(int p);
void pP_RefillHeldBalls(void);
void pP_UpdateBalls(void);
void pP_Postgame(void);
void pP_UpdateTimeUp(void);
void piranhaPanicLiveBall(void);
void pP_StartPlay(void);
void pP_RoundIntro(void);
void pP_LoadGame(void);

#endif // !__GAME_MINIGAME_PIRANHA_PANIC_H_
