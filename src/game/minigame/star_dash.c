#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_starDash
#define g_Minigame g_Minigame_shared
#include "game/minigame/star_dash.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/math/game_math.h"
#include "game/sound/m_sound.h"
#include "game/match_setup/match_flow.h"
#include "game/match_setup/match_loading.h"
#include "game/match_setup/roster_init.h"
#include "game/match_setup/scene_skip.h"
#include "game/baserunning/runner.h"
#include "game/baserunning/runner_base_rounding.h"
#include "game/ball/ball_physics.h"
#include "game/ball/collision_primitives.h"
#include "game/fielding/fielder.h"
#include "game/minigame/toy_field.h"
#include "game/stadium/stadium_framework.h"
#include "game/stadium/sta_c1.h"
#include "Unknown/File_0x8004c094.h"
#include "Unknown/File_0x800204cc.h"
#include "Unknown/File_0x800348c8.h"
#include "Unknown/File_0x80034220.h"
#include "Unknown/File_0x8003452c.h"
#include "Unknown/sub.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/gx.h"
#include "Dolphin/mtx.h"
#include "Dolphin/vec.h"
#include "Dolphin/os.h"
#include "Dolphin/stl.h"
#include "stl/stdlib.h"
#include "stl/math.h"
#include "Unknown/File_0x800acf14.h"
#include "musyx/musyx.h"
#undef g_Minigame

extern u8 lbl_80366158[0x30];
#define PauseSimulation lbl_80366158[0x28]

extern f32 fielderHitboxesForGarlicKnockout[];
extern VecXYZ lbl_3_data_21A48;
extern f32 lbl_3_data_21A54[3];
extern s16 lbl_3_data_21A60[2];
extern s16 lbl_3_data_21A3C[2][2];
extern s16 lbl_3_data_21A44;
extern s16 lbl_3_data_21A88[4];
extern VecXYZ lbl_3_data_219AC;
extern f32 lbl_3_data_219B8[19];
extern s16 lbl_3_data_21B20[4];
extern f32 lbl_3_data_21B58[4];
extern s8 lbl_3_data_21B88[4];
extern s16 lbl_3_data_21B8C[];

extern VecXZ base_MoundCoordinates[5];
extern f32 lbl_3_data_21B18[2];
extern VecXZ lbl_3_data_2198C[4];
extern void fn_800115C8(u8 player);
extern void fn_3_14E988(int player);
extern void fn_3_150010(s8 player);
extern void fn_3_169600(void);
extern void fn_3_106EB0(void);
extern void fn_3_10F550(int a, int b);
extern void fn_3_14E894(void);
extern void fn_3_157570(void);
extern void fn_80011578(void);
extern void fn_80011604(void* model, void (*cb)(void*, GXTevStageID*, GXTexCoordID*, GXTexMapID*, s8*, s8*));
extern u8 lbl_800EFBA4[0x10];
extern u16 lbl_3_data_81FC[0x30];
extern u8 lbl_3_data_21278[2];
extern u8 lbl_3_data_2127C[8][5];
extern u8 lbl_3_data_21984[5];
extern BOOL checkForPauses(void);
extern void starMissionsMinigamesSpecialAction(int missionType, int points, int barrelsHit);
extern s16 lbl_3_common_bss_37400[];
extern f32 lbl_3_data_21A14[6];
extern s16 lbl_3_data_21A30[6];
extern void fn_3_1695A4(s8 charID, u8 alt);
extern void fn_3_16C394(s8 charID);
extern f32 lbl_3_data_21AF8[6];
extern f32 lbl_3_data_21A64[9];
extern s16 lbl_3_data_21A04[8];
extern u8 lbl_3_data_88DC[2];
extern s16 lbl_3_data_21A90[4][4][2];
extern s16 lbl_3_data_21AD0[4][4];
extern u8 lbl_3_data_21B16;
extern s16 lbl_3_data_21B10[3];
extern s16 lbl_3_data_21AF0;
extern f32 lbl_3_data_21AF4;
extern u8 drawStadiumRelated;
extern f32 lbl_3_data_21B28[4];
extern f32 lbl_3_data_21B38[4];
extern f32 lbl_3_data_21B48[4];
extern f32 lbl_3_data_21B68[4];
extern f32 lbl_3_data_21B78[4];
extern void fn_3_156548(int index, f32 x, f32 y, f32 z);
extern void fn_3_15730C(int index, f32 x, f32 y, f32 z);

typedef struct {
    f32 nx;
    f32 nz;
    f32 d;
} SDSide;


typedef struct {
    /*0x00*/ VecXYZ pos;
    /*0x0C*/ u8 _0C[0x22 - 0x0C];
    /*0x22*/ s16 _22;
    /*0x24*/ u8 _24[2];
    /*0x26*/ u8 active;
    /*0x27*/ u8 _27;
} SDTrail; // size: 0x28

typedef struct {
    /*0x00*/ VecXYZ start;
    /*0x0C*/ VecXYZ end;
} SDPath; // size: 0x18

typedef struct {
    /*0x00*/ VecXYZ pos;
    /*0x0C*/ VecXYZ vel;
    /*0x18*/ s32 coin[10];
    /*0x40*/ u8 active;
    /*0x41*/ u8 _41[3];
} SDBurst; // size: 0x44

typedef struct {
    /*0x0*/ f32 _0;
    /*0x4*/ s16 angle;
    /*0x6*/ u8 state;
    /*0x7*/ s8 counter;
} SDAI; // size: 0x8

/* Star Dash's view of g_Minigame. */
typedef struct _SDState {
    /*0x0000*/ u8 _0000[0xA8];
    /*0x00A8*/ SDTrail trail[40];
    /*0x06E8*/ VecXYZ starPos;
    /*0x06F4*/ VecXYZ starPath[3];
    /*0x0718*/ u8 _0718[0x724 - 0x718];
    /*0x0724*/ s16 starFrames;
    /*0x0726*/ s16 pathFrames;
    /*0x0728*/ s16 pathDuration;
    /*0x072A*/ u8 x_72A;
    /*0x072B*/ u8 starBounces;
    /*0x072C*/ u8 _072C[0xB6C - 0x72C];
    /*0x0B6C*/ SDBurst burst;
    /*0x0BB0*/ SDItem item[4];
    /*0x0CB0*/ u8 _0CB0[0x1CE8 - 0xCB0];
    /*0x1CE8*/ SDPath path[4];
    /*0x1D48*/ f32 phaseProgress;
    /*0x1D4C*/ f32* factor;
    /*0x1D50*/ s16 spawnTimer;
    /*0x1D52*/ s16 _1D52;
    /*0x1D54*/ u16 spawnCount;
    /*0x1D56*/ s16 holderFrames;
    /*0x1D58*/ s16 _1D58;
    /*0x1D5A*/ s16 _1D5A[4];
    /*0x1D62*/ s16 phaseFrames;
    /*0x1D64*/ s16 pathAngle[4];
    /*0x1D6C*/ u8 spawnedCoins;
    /*0x1D6D*/ s8 holder;
    /*0x1D6E*/ u8 _1D6E[4];
    /*0x1D72*/ u8 phase;
    /*0x1D73*/ u8 phaseIndex;
    /*0x1D74*/ u8 _1D74[2];
    /*0x1D76*/ s16 x_1D76;
    /*0x1D78*/ u8 x_1D78[4];
    /*0x1D7C*/ u8 _1D7C[0x1DCC - 0x1D7C];
    /*0x1DCC*/ SDAI ai[4];
    /*0x1DEC*/ f32 rotSin;
    /*0x1DF0*/ f32 rotCos;
    /*0x1DF4*/ u8 _1DF4[4];
} SDState;

typedef union _SDMinigame {
    MiniGameStruct;
    SDState sd;
} SDMinigame;

extern SDMinigame g_Minigame;
#define SD g_Minigame.sd

#define SD_COUNTER_MAX 0x7FFF

s8 lbl_3_data_26580 = -1;

static u8 lbl_3_bss_B781;
static u8 lbl_3_bss_B780;
static u8 lbl_3_bss_B740[0x40] ATTRIBUTE_ALIGN(32);
static GXTexObj lbl_3_bss_B708;
static s32 lbl_3_bss_B704;
static s16 lbl_3_bss_B702;
static u8 lbl_3_bss_B700;


typedef struct {
    f32 distSq;
    s16 points;
    u8 player;
} SDTargetEntry;

int fn_3_134908(const void* a, const void* b);
int fn_3_134918(const void* a, const void* b);

static inline f32 sdDistSqXZ(f32 ax, f32 az, f32 bx, f32 bz) {
    f32 dz = az - bz;
    f32 dx = ax - bx;
    return dx * dx + dz * dz;
}

static inline void sdUpdatePulseTexture(void) {
    int value;
    int i;

    lbl_3_bss_B704 += !PauseSimulation;
    if ((lbl_3_bss_B704 & 1) == 0) {
        value = lbl_3_bss_B740[fn_800247E4(0, 0, 4, 4)];
        value += lbl_3_data_26580 * 2;
        if (value > 255) {
            value = 255;
        } else if (value < 0) {
            value = 0;
        }
        for (i = 0; i < 32; i += 2) {
            lbl_3_bss_B740[i] = value;
        }
        DCFlushRange(lbl_3_bss_B740, 0x40);
        if (value + lbl_3_data_26580 * 2 > 255 || value + lbl_3_data_26580 * 2 < 0) {
            lbl_3_data_26580 *= -1;
        }
    }
}

static inline void sdBounce(VecXYZ* pos, VecXYZ* vel, VecSrcDst* probe, CollisionStruct* hit) {
    f32 dot;
    u32 type;

    probe->dst.x = pos->x;
    probe->dst.y = -pos->y;
    probe->dst.z = pos->z;
    type = checkCollision(probe, hit, 0, FALSE);
    if (type == BALL_COLLISION_TYPE_UNCLIMBABLE_WALL) {
        hit->normal.y = hit->normal.y * -1.0f;
        dot = vel->x * hit->normal.x + vel->y * hit->normal.y + vel->z * hit->normal.z;
        dot *= 2.0f;
        vel->x -= dot * hit->normal.x;
        vel->y -= dot * hit->normal.y;
        vel->z -= dot * hit->normal.z;
        pos->x = hit->position.x;
        pos->y = -hit->position.y;
        pos->z = hit->position.z;
    }
}

// .text:0x0013C468 size:0x328 mapped:0x8077B4FC
void starDashSwitcher(void) {
    switch (g_GameLogic.gameStatus) {
    case GAME_STATUS_LOAD_GAME:
        starDashSomething();
        break;
    case GAME_STATUS_TRANSITION_MINIGAME_TO_BATTING:
        fn_3_13BBF4();
        break;
    case GAME_STATUS_DEFAULT:
        fn_3_13BB30();
        break;
    case GAME_STATUS_LIVE_BALL:
        starDashLiveBall();
        break;
    case GAME_STATUS_TRANSITION_MINIGAME_POSTGAME:
        fn_3_13B9C4();
        break;
    }
    if (sound_crowd_EffectsStruct._30 != 0) {
        sound_crowd_EffectsStruct._30--;
    }
}

// .text:0x0013C464 size:0x4 mapped:0x8077B4F8
void fn_3_13C464(void) {
    return;
}

// .text:0x0013BCB8 size:0x7AC mapped:0x8077AD4C
void starDashSomething(void) {
    int i;
    int p;
    int n;
    int k;
    u32 offset;
    u32 x;
    u32 y;
    f32 floorY;
    InMemFielder* fielder;
    SDItem* item;
    u8 strength;

    if (g_GameLogic._125 == 0) {
        initializeSomethingDuringTransition();
        g_GameLogic.secondaryGameMode = SECONDARY_GAME_MODE_STAR_DASH;
        g_Minigame.minigameElapsedFrames = 0;
        g_Minigame.turnOverStatus = 0;
        g_Minigame._1A37 = 0;
        for (i = 0; i < 4; i++) {
            g_Minigame.miniGameCurrentPoints[i] = 0;
            g_Minigame.miniGameLatestPoints[i] = 0;
            g_Minigame.minigamePoints_current_Latest[i][0] = 0;
            g_Minigame.minigamePoints_current_Latest[i][1] = 0;
            g_Minigame.playerSlots._28[i] = -1;
            g_Minigame.playerSlots.fielderIndex[i] = -1;
            g_Minigame.playerSlots.runnerPlayerIndex[i] = -1;
            g_Minigame.playerSlots.playerRunnerIndex[i] = -1;
            g_Minigame.playerSlots._24[i] = 0;
        }
        g_Minigame.pointsReqToWin_challenge = 0;
        *(s8*)&g_Minigame.minigamePlayerSelectedOrder = -1;
        g_Minigame.rosterID = -1;
        sound_crowd_EffectsStruct._30 = 0;
        if (!g_Minigame.multiPlayerInd) {
            g_Minigame.minigameFramesRemaining = lbl_3_data_21984[g_Minigame.soloMinigameDifficulty] * 60;
            strength = lbl_3_data_2127C[g_Minigame.GameMode_MiniGame][g_Minigame.soloMinigameDifficulty];
            for (i = 0; i < 4; i++) {
                g_Minigame.playerSlots.aiStrength[i] = strength;
            }
        } else {
            if (g_Minigame._1A3C) {
                strength = lbl_3_data_2127C[7][0];
                for (i = 0; i < 4; i++) {
                    g_Minigame.playerSlots.aiStrength[i] = strength;
                }
            }
            g_Minigame.minigameFramesRemaining = lbl_3_data_21984[4] * 60;
        }
        setDefaultInMemFielder();
        n = 0;
        for (p = 0; p < 4; p++) {
            if (g_Minigame.playerSlots.characterIndex[p] >= 0) {
                g_Minigame.playerSlots._28[n] = p;
                g_Minigame.playerSlots.fielderIndex[g_Minigame.playerSlots._28[n]] = n + 2;
                setFielderValues(p, g_Minigame.playerSlots.fielderIndex[g_Minigame.playerSlots._28[n]]);
                g_Minigame.starDashStunType[p] = 0;
                fielder = &g_Fielders[g_Minigame.playerSlots.fielderIndex[g_Minigame.playerSlots._28[n]]];
                fielder->_020D = p;
                fielder->pos.x = lbl_3_data_2198C[n].x;
                fielder->pos.z = lbl_3_data_2198C[n].z;
                fielder->pos.y = 0.0f;
                fielder->actionYOffset = 0.0f;
                fielder->lockoutDuration = 0;
                fielder->desiredMovementDirection = -1.5707964f;
                n++;
            }
        }
        for (i = 0; i < 100; i++) {
            g_Minigame.coinState[i] = 0;
        }
        floorY = lbl_3_data_21A48.y;
        SD.spawnTimer = 30;
        SD.spawnedCoins = 0;
        SD.spawnCount = 0;
        SD.burst.active = 0;
        SD.x_72A = 0;
        SD._1D52 = 600;
        SD.holder = -1;
        SD.phase = 0;
        SD.phaseIndex = 0;
        SD.path[0].start.y = floorY;
        SD.path[0].end.y = floorY;
        SD.pathAngle[0] = 0;
        SD.path[1].start.y = floorY;
        SD.path[1].end.y = floorY;
        SD.pathAngle[1] = 0x400;
        SD.path[2].start.y = floorY;
        SD.path[2].end.y = floorY;
        SD.pathAngle[2] = 0x800;
        SD.path[3].start.y = floorY;
        SD.path[3].end.y = floorY;
        SD.pathAngle[3] = 0xC00;
        for (i = 0; i < 40; i++) {
            SD.trail[i].active = 0;
            SD.trail[i].pos.y = floorY;
            SD.trail[i]._22 = 0;
        }
        if (g_Minigame.multiPlayerInd == 0 && g_Minigame._1A3C == 0) {
            lbl_3_bss_B781 = g_Minigame.soloMinigameDifficulty;
            lbl_3_bss_B780 = lbl_3_data_21A88[g_Minigame.soloMinigameDifficulty];
        } else {
            lbl_3_bss_B781 = MINIGAME_DIFFICULTY_SOLO_NON_CHALLENGE;
            lbl_3_bss_B780 = 4;
        }
        for (k = 0; k < 4; k++) {
            memset(&SD.item[k].pos, 0, sizeof(Vec));
            memset(&SD.item[k].vel, 0, sizeof(Vec));
            memset(&SD.item[k].rot, 0, sizeof(Vec));
            memset(&SD.item[k].rotVel, 0, sizeof(Vec));
            SD.item[k].state = 0;
        }
        item = SD.item;
        for (k = 0; k < lbl_3_bss_B780; k++) {
            item->timer = lbl_3_data_21A90[g_Minigame.soloMinigameDifficulty][0][0] * 60 +
                          random_fn_3_9EE24((lbl_3_data_21A90[g_Minigame.soloMinigameDifficulty][0][1] -
                                             lbl_3_data_21A90[g_Minigame.soloMinigameDifficulty][0][0]) * 60);
            item->_30 = 360 / lbl_3_bss_B780 * k;
            item->_34 = item->_30 + 360 / lbl_3_data_21A88[lbl_3_bss_B781];
            item++;
        }
        SD.x_1D78[0] = 0;
        SD.x_1D78[1] = 0;
        SD.x_1D78[2] = 0;
        SD.x_1D78[3] = 0;
        SD.x_1D76 = 0;
        g_Minigame.powerup.timer = lbl_3_data_21B10[0];
        g_Minigame.powerup.activeInd = 0;
        g_Minigame.playerIDWithPowerup[0] = -1;
        for (y = 0; y < 4; y++) {
            for (x = 0; x < 4; x++) {
                offset = fn_800247E4(x, y, 4, 4);
                if (offset < 32) {
                    lbl_3_bss_B740[offset + 2] = 0xFF;
                    lbl_3_bss_B740[offset] = 0xFF;
                    lbl_3_bss_B740[offset + 3] = 0x96;
                    lbl_3_bss_B740[offset + 1] = 0x96;
                } else {
                    lbl_3_bss_B740[offset + 2] = 0x96;
                    lbl_3_bss_B740[offset] = 0x96;
                    lbl_3_bss_B740[offset + 3] = 0x96;
                    lbl_3_bss_B740[offset + 1] = 0x96;
                }
            }
        }
        GXInitTexObj(&lbl_3_bss_B708, lbl_3_bss_B740, 4, 4, GX_TF_RGBA8, GX_REPEAT, GX_REPEAT, GX_DISABLE);
        GXInitTexObjLOD(&lbl_3_bss_B708, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_DISABLE, GX_DISABLE, GX_ANISO_1);
        lbl_3_bss_B704 = 0;
        lbl_3_data_26580 = -1;
        fn_3_169600();
        minigamesSetSomePointers();
        minigamesGXStuff();
        minigamesSetSomePointers2();
        bowserCastleSomething();
        g_GameLogic._125++;
    } else {
        SetGameStatus(GAME_STATUS_GAME_START_MOVIE);
    }
}

// .text:0x0013BBF4 size:0xC4 mapped:0x8077AC88
void fn_3_13BBF4(void) {
    switch (g_GameLogic._125) {
    case 0:
        fn_3_10F550(2, lbl_3_data_21278[0]);
        changeScene(1, 6);
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125 = 1;
        break;
    case 1:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > lbl_3_data_21278[0] + lbl_3_data_21278[1]) {
            g_GameLogic._125 = 2;
        }
        break;
    case 2:
        SetGameStatus(GAME_STATUS_DEFAULT);
        break;
    }
}

// .text:0x0013BB30 size:0xC4 mapped:0x8077ABC4
void fn_3_13BB30(void) {
    setDefaultInMemBall();
    fn_3_1356F8();
    changeScene(1, 6);
    SetGameStatus(GAME_STATUS_LIVE_BALL);
}

// .text:0x0013B9C4 size:0x16C mapped:0x8077AA58
void fn_3_13B9C4(void) {
    u32 i;

    fn_3_157570();
    minigameCalculateRankings();
    SetGameStatus(GAME_STATUS_MVP_END_GAME);
    fn_80011578();
    for (i = 0; i < 100; i++) {
        g_Minigame.coinState[i] = 0;
    }
    SD.spawnTimer = 30;
    SD.spawnedCoins = 0;
    SD.item[0].state = 0;
    SD.item[1].state = 0;
    SD.item[2].state = 0;
    SD.item[3].state = 0;
    g_Minigame.powerup.activeInd = 0;
}

// .text:0x0013B284 size:0x740 mapped:0x8077A318
void starDashLiveBall(void) {
    if (checkForPauses()) {
        return;
    }
    if (g_Minigame.turnOverStatus == 0) {
        g_Minigame.minigameElapsedFrames++;
    }
    if (g_Minigame.minigameFramesRemaining != 0 && --g_Minigame.minigameFramesRemaining < 600 &&
        g_Minigame.minigameFramesRemaining != 0 && g_Minigame.minigameFramesRemaining % 60 == 0) {
        callSfx(lbl_3_data_81FC[40]);
    }
    fn_3_13334C();
    miniGameDash();
    fn_3_133320();
    fn_3_136220();
    fn_3_139F84();
    fn_3_139700();
    fn_3_13AA78();
    fn_3_136048();
    fn_3_138AA4();
    fn_3_136EA4();
    fn_3_135924();
    fn_3_13AFE4();
}

// .text:0x0013AFE4 size:0x2A0 mapped:0x8077A078
void fn_3_13AFE4(void) {
    if (g_Minigame.turnOverStatus == 0) {
        if (g_Minigame.minigameFramesRemaining == 0) {
            g_Minigame.turnOverStatus = 1;
            fn_3_10F550(3, 0);
            sndFXStartEx(0x1BE, lbl_800EFBA4[7], 0x3F, 0);
        }
        return;
    }
    if (g_Minigame.turnOverStatus == 1) {
        g_Minigame.turnOverStatus = 2;
        g_GameLogic.CountdownUntilFade = lbl_3_data_21B20[0];
        fn_3_14E894();
    }
    if (--g_GameLogic.CountdownUntilFade == 7) {
        changeScene(3, 6);
    }
    if (g_GameLogic.CountdownUntilFade <= 0) {
        fn_3_13AE1C();
    }
}

// .text:0x0013AE1C size:0x1C8 mapped:0x80779EB0
void fn_3_13AE1C(void) {
    u32 i;

    minigameCalculateRankings();
    if (g_Minigame.soloMinigameDifficulty <= MINIGAME_DIFFICULTY_MULTIPLAYER_CHALLENGE_HARD && g_Minigame.multiPlayerInd == 0) {
        if (g_Minigame.playerSlots._1C[g_Minigame._1908] == 1 && g_Minigame.challenge_minigame_haven_tWonYetIndicator == 0) {
            g_Minigame._1A37 = 1;
        } else {
            g_Minigame._1A37 = 2;
        }
    }
    SetGameStatus(GAME_STATUS_MVP_END_GAME);
    fn_80011578();
    for (i = 0; i < 100; i++) {
        g_Minigame.coinState[i] = 0;
    }
    SD.spawnTimer = 30;
    SD.spawnedCoins = 0;
    SD.item[0].state = 0;
    SD.item[1].state = 0;
    SD.item[2].state = 0;
    SD.item[3].state = 0;
    g_Minigame.powerup.activeInd = 0;
}

// .text:0x0013ADC0 size:0x5C mapped:0x80779E54
void fn_3_13ADC0(Vec* out, Vec* in, Vec* normal) {
    f32 dot = in->x * normal->x + in->y * normal->y + in->z * normal->z;

    dot *= 2.0f;
    out->x = in->x - dot * normal->x;
    out->y = in->y - dot * normal->y;
    out->z = in->z - dot * normal->z;
}

// .text:0x0013ACB4 size:0x10C mapped:0x80779D48
void fn_3_13ACB4(CollisionStruct* hit) {
    f32 a = -hit->normal.z;
    f32 b = hit->normal.x;
    f32 dx0 = hit->position.x - SD.starPath[0].x;
    f32 dz0 = hit->position.z - SD.starPath[0].z;
    f32 d;
    f32 dx2;
    f32 dz2;

    if (dx0 * a + dz0 * b > 0.0f) {
        a *= -1.0f;
        b *= -1.0f;
    }
    d = (dx0 * a + 0.0f + dz0 * b) * 2.0f;
    SD.starPath[0].x = hit->position.x + (dx0 - d * a);
    SD.starPath[0].z = hit->position.z + (dz0 - d * b);
    a *= -1.0f;
    b *= -1.0f;
    dx2 = hit->position.x - SD.starPath[2].x;
    dz2 = hit->position.z - SD.starPath[2].z;
    d = (dx2 * a + 0.0f + dz2 * b) * 2.0f;
    SD.starPath[2].x = hit->position.x + (dx2 - d * a);
    SD.starPath[2].z = hit->position.z + (dz2 - d * b);
    SD.starPath[1].x = 0.5f * (SD.starPath[2].x + SD.starPath[0].x);
    SD.starPath[1].z = 0.5f * (SD.starPath[2].z + SD.starPath[0].z);
}

// .text:0x0013AA78 size:0x23C mapped:0x80779B0C
void fn_3_13AA78(void) {
    if (SD.x_72A != 0) {
        starDashRelated();
    } else {
        fn_3_13A89C();
    }
    if ((s8)g_Minigame._1D6D >= 0) {
        if (--SD.holderFrames < 0 || g_Minigame.turnOverStatus != 0) {
            fn_3_14E988(g_Minigame._1D6D);
            fn_800115C8(g_Minigame._1D6D);
            g_Minigame._1D6D = -1;
        }
    }
}

// .text:0x0013A89C size:0x1DC mapped:0x80779930
void fn_3_13A89C(void) {
    if (g_Minigame.turnOverStatus == 0) {
        if (--SD._1D52 <= 0) {
            SD.starPos.x = lbl_3_data_219AC.x;
            SD.starPos.y = lbl_3_data_219AC.y;
            SD.starPos.z = lbl_3_data_219AC.z;
            SD.starBounces = 0;
            fn_3_13A724();
            SD.x_72A = 1;
            SD.starFrames = 0;
            SD._1D52 = lbl_3_data_21A30[2];
            fn_3_150010(4);
            fn_3_106EB0();
        }
    }
}

// .text:0x0013A724 size:0x178 mapped:0x807797B8
void fn_3_13A724(void) {
    Vec rel;
    f32 speed;
    f32 unused;
    VecXYZ* path = SD.starPath;

    SD.starPath[0].x = SD.starPos.x;
    SD.starPath[0].y = SD.starPos.y;
    SD.starPath[0].z = SD.starPos.z;
    SD.pathDuration = RandomInt_Game_Range(lbl_3_data_21A30[3], lbl_3_data_21A30[4]);
    speed = RandomF32_Game_Range(lbl_3_data_21A14[0], lbl_3_data_21A14[1]);
    rel.x = lbl_3_data_219AC.x - SD.starPos.x;
    rel.z = lbl_3_data_219AC.z - SD.starPos.z;
    rel.y = lbl_3_data_219AC.y - SD.starPos.y;
    unused = dolsqrtf2(rel.x * rel.x + rel.z * rel.z);
    getComponentsFromSAng(random_fn_3_9EE24(0x1000), &rel.x, &rel.z);
    SD.starPath[2].x = rel.x * speed + SD.starPath[0].x;
    SD.starPath[2].z = rel.z * speed + SD.starPath[0].z;
    SD.starPath[2].y = lbl_3_data_21A14[4];
    SD.starPath[1].x = 0.5f * (SD.starPath[0].x + SD.starPath[2].x);
    SD.starPath[1].z = 0.5f * (SD.starPath[0].z + SD.starPath[2].z);
    SD.starPath[1].y = SD.starPath[0].y + RandomF32_Game_Range(lbl_3_data_21A14[2], lbl_3_data_21A14[3]);
    SD.pathFrames = 0;
}

// .text:0x0013A0AC size:0x678 mapped:0x80779140
void starDashRelated(void) {
    u32 collision;
    VecSrcDst probe;
    CollisionStruct hit;
    InMemFielder* fielder;
    f32 bestDist;
    f32 dist;
    f32 dx;
    f32 dz;
    int best;
    int p;

    SD.starFrames++;
    SD.pathFrames++;
    if (g_Minigame.turnOverStatus != 0) {
        SD.x_72A = 0;
    } else if (SD.starFrames > lbl_3_data_21A30[0]) {
        SD.x_72A = 0;
        fn_3_14E988(4);
    } else {
        probe.src.x = SD.starPos.x;
        probe.src.y = -(lbl_3_data_21A14[2] * 0.5f);
        probe.src.z = SD.starPos.z;
        spline3D_evaluate((Vec*)&SD.starPos, (Vec*)SD.starPath, 3, (f32)SD.pathFrames / (f32)SD.pathDuration);
        probe.dst.x = SD.starPos.x;
        probe.dst.y = -(lbl_3_data_21A14[2] * 0.5f);
        probe.dst.z = SD.starPos.z;
        collision = checkCollision(&probe, &hit, 0, FALSE);
        if (collision == BALL_COLLISION_TYPE_UNCLIMBABLE_WALL) {
            SD.starPos.x = hit.position.x;
            fn_3_13ACB4(&hit);
            SD.starPos.z = probe.src.z;
        }
        if (SD.starPos.y <= lbl_3_data_21A14[4]) {
            SD.starBounces++;
            SD.starPos.y = lbl_3_data_21A14[4];
            fn_3_13A724();
        }
        best = -1;
        bestDist = 999.9f;
        for (p = 0; p < 4; p++) {
            if (g_Minigame.playerSlots.fielderIndex[p] >= 0) {
                fielder = &g_Fielders[g_Minigame.playerSlots.fielderIndex[p]];
                if (!(fielder->hitbox_barrelCollisions + fielder->actionYOffset <
                      SD.starPos.y - lbl_3_data_21A14[5])) {
                    dx = SD.starPos.x - fielder->pos.x;
                    dz = SD.starPos.z - fielder->pos.z;
                    dist = dolsqrtf2(dx * dx + dz * dz);
                    if (dist < lbl_3_data_21A14[5] + fielderHitboxesForGarlicKnockout[fielder->Weight] &&
                        dist < bestDist) {
                        bestDist = dist;
                        best = p;
                    }
                }
            }
        }
        if (best >= 0) {
            g_Minigame.miniGameCurrentPoints[best] += lbl_3_data_21A30[5];
            SD.x_72A = 0;
            g_Minigame._1D6D = best;
            SD.holderFrames = lbl_3_data_21A30[1];
            fn_3_14E988(4);
            if (g_Minigame.playerIDWithPowerup[0] == best) {
                fn_800115C8(best);
                if (SD.factor == &lbl_3_data_21AF8[5]) {
                    g_Minigame.playerIDWithPowerup[0] = -1;
                }
            }
            fn_3_150010(best);
            fn_80011604((void*)(s32)(s8)best, fn_3_132EDC);
            if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400[0x20] == best) {
                starMissionsMinigamesSpecialAction(3, 0, 0);
            }
        }
    }
}

// .text:0x0013A048 size:0x64 mapped:0x807790DC
void minigame_transferPoints(int toTeam, int fromTeam) {
    s16* points = g_Minigame.miniGameCurrentPoints;

    if (points[fromTeam] < lbl_3_data_21A04[7]) {
        points[toTeam] += points[fromTeam];
        points[fromTeam] = 0;
    } else {
        points[toTeam] += lbl_3_data_21A04[7];
        points[fromTeam] -= lbl_3_data_21A04[7];
    }
}

// .text:0x00139F84 size:0xC4 mapped:0x80779018
void fn_3_139F84(void) {
    fn_3_139CA0();
    fn_3_139808();
    fn_3_13974C();
}

// .text:0x00139CA0 size:0x2E4 mapped:0x80778D34
void fn_3_139CA0(void) {
    SDBurst* burst = NULL;
    u8 burstMode = FALSE;
    int count;
    int i;
    s16 angle;
    f32 base;

    if (g_Minigame.turnOverStatus != 0) {
        return;
    }
    if (--SD.spawnTimer > 0) {
        return;
    }
    count = lbl_3_data_21A04[2];
    if (SD.spawnCount % lbl_3_data_21A04[6] == 0 && 100 - SD.spawnedCoins >= 10 && SD.burst.active == 0) {
        burst = &SD.burst;
        SD.burst.active = 1;
        count = 10;
        burstMode = TRUE;
    }
    angle = random_fn_3_9EE24(0x1000);
    base = RandomF32_Game_Range(lbl_3_data_219B8[2], lbl_3_data_219B8[3]);
    for (i = 0; i < 100; i++) {
        if (burstMode) {
            if (count != 0) {
                if (g_Minigame.coinState[i] == 0) {
                    g_Minigame.coinState[i] = 2;
                    g_Minigame.coinFrameCounter[i] = 0;
                    SD.spawnedCoins++;
                    burst->coin[count - 1] = i;
                    count--;
                }
            } else {
                burst->pos.x = lbl_3_data_219AC.x;
                burst->pos.y = lbl_3_data_219AC.y;
                burst->pos.z = lbl_3_data_219AC.z;
                getComponentsFromSAng(angle + (random_fn_3_9EE24(lbl_3_data_21A04[4] * 2) - lbl_3_data_21A04[4]),
                                      &burst->vel.x, &burst->vel.z);
                {
                    f32 speed = base + RandomF32_Game_Range(-lbl_3_data_219B8[4], lbl_3_data_219B8[4]);
                    burst->vel.x *= speed;
                    burst->vel.z *= speed;
                }
                burst->vel.y = RandomF32_Game_Range(lbl_3_data_219B8[5], lbl_3_data_219B8[6]);
                break;
            }
        } else if (g_Minigame.coinState[i] == 0) {
            g_Minigame.coinPos[i].x = lbl_3_data_219AC.x;
            g_Minigame.coinPos[i].y = lbl_3_data_219AC.y;
            g_Minigame.coinPos[i].z = lbl_3_data_219AC.z;
            getComponentsFromSAng(angle + (random_fn_3_9EE24(lbl_3_data_21A04[4] * 2) - lbl_3_data_21A04[4]),
                                  &g_Minigame.coinVelocity[i].x, &g_Minigame.coinVelocity[i].z);
            {
                f32 speed = base + RandomF32_Game_Range(-lbl_3_data_219B8[4], lbl_3_data_219B8[4]);
                g_Minigame.coinVelocity[i].x *= speed;
                g_Minigame.coinVelocity[i].z *= speed;
            }
            g_Minigame.coinVelocity[i].y = RandomF32_Game_Range(lbl_3_data_219B8[0], lbl_3_data_219B8[1]);
            g_Minigame.coinState[i] = 1;
            g_Minigame.coinFrameCounter[i] = 0;
            SD.spawnedCoins++;
            SD.spawnCount++;
            if (--count <= 0) {
                callSfx(0x2E8);
                break;
            }
        }
    }
    SD.spawnTimer = RandomInt_Game_Range(lbl_3_data_21A04[0], lbl_3_data_21A04[1]);
}

// .text:0x00139808 size:0x498 mapped:0x8077889C
void fn_3_139808(void) {
    VecSrcDst probe;
    CollisionStruct hit;
    InMemFielder* fielder;
    f32 bestDistSq;
    f32 distSq;
    f32 reach;
    int best;
    int p;
    int i;

    for (i = 0; i < 100; i++) {
        if (g_Minigame.coinState[i] != 1) {
            continue;
        }
        g_Minigame.coinFrameCounter[i]++;
        if (g_Minigame.coinFrameCounter[i] > lbl_3_data_21A04[3]) {
            g_Minigame.coinState[i] = 0;
            SD.spawnedCoins--;
            continue;
        }
        g_Minigame.coinVelocity[i].y += lbl_3_data_219B8[11];
        probe.src.x = g_Minigame.coinPos[i].x;
        probe.src.y = -g_Minigame.coinPos[i].y;
        probe.src.z = g_Minigame.coinPos[i].z;
        g_Minigame.coinPos[i].x += g_Minigame.coinVelocity[i].x;
        g_Minigame.coinPos[i].y += g_Minigame.coinVelocity[i].y;
        g_Minigame.coinPos[i].z += g_Minigame.coinVelocity[i].z;
        if (g_Minigame.coinPos[i].y < lbl_3_data_219B8[14]) {
            g_Minigame.coinPos[i].y = lbl_3_data_219B8[14];
            g_Minigame.coinVelocity[i].y = g_Minigame.coinVelocity[i].y * -lbl_3_data_219B8[12];
            g_Minigame.coinVelocity[i].x *= lbl_3_data_219B8[13];
            g_Minigame.coinVelocity[i].z *= lbl_3_data_219B8[13];
        }
        sdBounce(&g_Minigame.coinPos[i], &g_Minigame.coinVelocity[i], &probe, &hit);
        probe.dst.x = g_Minigame.coinPos[i].x;
        probe.dst.y = -g_Minigame.coinPos[i].y;
        probe.dst.z = g_Minigame.coinPos[i].z;
        if (fn_3_1373E0(&probe, (Vec*)&g_Minigame.coinVelocity[i], &hit, lbl_3_data_219B8[15])) {
            g_Minigame.coinPos[i].x = hit.position.x;
            g_Minigame.coinPos[i].y = hit.position.y;
            g_Minigame.coinPos[i].z = hit.position.z;
            memcpy(&g_Minigame.coinVelocity[i], &hit.normal, sizeof(Vec));
            sdBounce(&g_Minigame.coinPos[i], &g_Minigame.coinVelocity[i], &probe, &hit);
        }
        if (g_Minigame.turnOverStatus == 0) {
            bestDistSq = 99999.9f;
            reach = lbl_3_data_219B8[15];
            best = -1;
            for (p = 0; p < 4; p++) {
                if (g_Minigame.playerSlots.fielderIndex[p] >= 0 &&
                    (g_Minigame.starDashStunType[p] == 0 || g_Minigame.starDashStunType[p] == 3)) {
                    fielder = &g_Fielders[g_Minigame.playerSlots.fielderIndex[p]];
                    if (fielder->isJump == 0 || fielder->jumpCountUp <= 3) {
                        if (!(fielder->hitbox_barrelCollisions + fielder->actionYOffset <
                              g_Minigame.coinPos[i].y)) {
                            distSq = sdDistSqXZ(fielder->pos.x, fielder->pos.z, g_Minigame.coinPos[i].x,
                                                g_Minigame.coinPos[i].z);
                            if (distSq < SQ(reach + fielderHitboxesForGarlicKnockout[fielder->Weight]) &&
                                distSq < bestDistSq) {
                                bestDistSq = distSq;
                                best = p;
                            }
                        }
                    }
                }
            }
            if (best >= 0) {
                g_Minigame.miniGameCurrentPoints[best] += lbl_3_data_21A04[5];
                g_Minigame.coinState[i] = 3;
                g_Minigame.coinVelocity[i].z = 0.0f;
                g_Minigame.coinVelocity[i].x = 0.0f;
                g_Minigame.coinVelocity[i].y = RandomF32_Game_Range(lbl_3_data_219B8[0], lbl_3_data_219B8[1]);
                g_Minigame.coinFrameCounter[i] = 0;
                if (sound_crowd_EffectsStruct._30 == 0) {
                    callSfx(0x2E9);
                    sound_crowd_EffectsStruct._30 = lbl_3_data_88DC[1];
                }
            }
        }
    }
}

// .text:0x0013974C size:0xBC mapped:0x807787E0
void fn_3_13974C(void) {
    u32 i;

    for (i = 0; i < 100; i++) {
        if (g_Minigame.coinState[i] == 3) {
            g_Minigame.coinFrameCounter[i]++;
            PSVECAdd((Vec*)&g_Minigame.coinPos[i], (Vec*)&g_Minigame.coinVelocity[i], (Vec*)&g_Minigame.coinPos[i]);
            g_Minigame.coinVelocity[i].y += lbl_3_data_219B8[11];
            if (g_Minigame.coinVelocity[i].y < 0.0f) {
                g_Minigame.coinState[i] = 0;
                SD.spawnedCoins--;
            }
        }
    }
}

// .text:0x00139700 size:0x4C mapped:0x80778794
void fn_3_139700(void) {
    if (SD.burst.active != 0) {
        if (g_Minigame.turnOverStatus != 0) {
            SD.burst.active = 0;
        } else {
            fn_3_1391C0();
        }
    }
}

// .text:0x001391C0 size:0x540 mapped:0x80778254
void fn_3_1391C0(void) {
    SDBurst* burst = &SD.burst;
    VecSrcDst probe;
    CollisionStruct hit;
    InMemFielder* fielder;
    f32 bestDistSq;
    f32 distSq;
    f32 reach;
    f32 speed;
    int best;
    int p;
    int k;
    int coin;

    probe.src.x = burst->pos.x;
    probe.src.y = -burst->pos.y;
    probe.src.z = burst->pos.z;
    burst->vel.y += lbl_3_data_219B8[11];
    burst->pos.x += burst->vel.x;
    burst->pos.y += burst->vel.y;
    burst->pos.z += burst->vel.z;
    sdBounce(&burst->pos, &burst->vel, &probe, &hit);
    probe.dst.x = burst->pos.x;
    probe.dst.y = -burst->pos.y;
    probe.dst.z = burst->pos.z;
    if (fn_3_1373E0(&probe, (Vec*)&burst->vel, &hit, lbl_3_data_219B8[15])) {
        burst->pos.x = hit.position.x;
        burst->pos.y = hit.position.y;
        burst->pos.z = hit.position.z;
        memcpy(&burst->vel, &hit.normal, sizeof(Vec));
        sdBounce(&burst->pos, &burst->vel, &probe, &hit);
    }
    if (burst->pos.y < lbl_3_data_219B8[14]) {
        for (k = 0; k < 10; k++) {
            coin = burst->coin[k];
            g_Minigame.coinPos[coin].x = burst->pos.x;
            g_Minigame.coinPos[coin].y = burst->pos.y;
            g_Minigame.coinPos[coin].z = burst->pos.z;
            getComponentsFromSAng(random_fn_3_9EE24(0x1000) +
                                      (random_fn_3_9EE24(lbl_3_data_21A04[4] * 2) - lbl_3_data_21A04[4]),
                                  &g_Minigame.coinVelocity[coin].x, &g_Minigame.coinVelocity[coin].z);
            speed = RandomF32_Game_Range(-lbl_3_data_219B8[9], lbl_3_data_219B8[10]);
            g_Minigame.coinVelocity[coin].x *= speed;
            g_Minigame.coinVelocity[coin].z *= speed;
            g_Minigame.coinVelocity[coin].y = RandomF32_Game_Range(lbl_3_data_219B8[7], lbl_3_data_219B8[8]);
            g_Minigame.coinState[coin] = 1;
            g_Minigame.coinFrameCounter[coin] = 0;
        }
        burst->active = 0;
    } else {
        bestDistSq = 99999.9f;
        reach = lbl_3_data_219B8[15];
        best = -1;
        for (p = 0; p < 4; p++) {
            if (g_Minigame.playerSlots.fielderIndex[p] >= 0 &&
                (g_Minigame.starDashStunType[p] == 0 || g_Minigame.starDashStunType[p] == 3)) {
                fielder = &g_Fielders[g_Minigame.playerSlots.fielderIndex[p]];
                if (fielder->isJump == 0 || fielder->jumpCountUp <= 3) {
                    if (!(fielder->hitbox_barrelCollisions + fielder->actionYOffset < burst->pos.y)) {
                        distSq = sdDistSqXZ(fielder->pos.x, fielder->pos.z, burst->pos.x, burst->pos.z);
                        if (distSq < SQ(reach + fielderHitboxesForGarlicKnockout[fielder->Weight]) &&
                            distSq < bestDistSq) {
                            bestDistSq = distSq;
                            best = p;
                        }
                    }
                }
            }
        }
        if (best >= 0) {
            g_Minigame.miniGameCurrentPoints[best] += lbl_3_data_21A04[5] * 10;
            for (k = 0; k < 10; k++) {
                coin = burst->coin[k];
                g_Minigame.coinPos[coin].x = burst->pos.x;
                g_Minigame.coinPos[coin].y = burst->pos.y;
                g_Minigame.coinPos[coin].z = burst->pos.z;
                {
                    s16 angle = random_fn_3_9EE24(0x1000);
                    f32 base = RandomF32_Game_Range(lbl_3_data_219B8[2], lbl_3_data_219B8[3]);
                    g_Minigame.coinState[coin] = 3;
                    getComponentsFromSAng(angle, &g_Minigame.coinVelocity[coin].x, &g_Minigame.coinVelocity[coin].z);
                    speed = base + RandomF32_Game_Range(-lbl_3_data_219B8[4], lbl_3_data_219B8[4]);
                }
                g_Minigame.coinVelocity[coin].x *= speed;
                g_Minigame.coinVelocity[coin].z *= speed;
                g_Minigame.coinVelocity[coin].y = RandomF32_Game_Range(lbl_3_data_219B8[0], lbl_3_data_219B8[1]);
                g_Minigame.coinFrameCounter[coin] = 0;
            }
            callSfx(0x30A);
            burst->active = 0;
            sound_crowd_EffectsStruct._30 = lbl_3_data_88DC[1];
        }
    }
}

// .text:0x00138AA4 size:0x71C mapped:0x80777B38
void fn_3_138AA4(void) {
    u32 i;

    if (g_Minigame.turnOverStatus == 0) {
        for (i = 0; i < lbl_3_bss_B780; i++) {
            if (i >= 4) {
                break;
            }
            switch (SD.item[i].state) {
            case 0:
                fn_3_138448(&SD.item[i]);
                break;
            case 1:
                fn_3_1382E0(&SD.item[i]);
                break;
            case 2:
                fn_3_13802C(&SD.item[i]);
                break;
            case 3:
                fn_3_137F14(&SD.item[i]);
                break;
            case 4:
                fn_3_137DE4(&SD.item[i]);
                break;
            case 5:
                fn_3_137CF8(&SD.item[i]);
                break;
            }
        }
    }
}

// .text:0x001384B4 size:0x5F0 mapped:0x80777548
void fn_3_1384B4(SDItem* item) {
    Vec center = {0.0f, 0.0f, 20.0f};
    Vec axis = {1.0f, 0.0f, 0.0f};
    Vec rel;
    Vec dir;
    Vec spawn;
    s32 list[100];
    u32 hits = 0;
    u32 i;
    f32 sumX = 0.0f;
    f32 sumZ = 0.0f;
    f32 varX;
    f32 varZ;
    f32 meanX;
    f32 meanZ;
    f32 sdX;
    f32 sdZ;
    f32 angle;
    f32 mag;
    f32 edgeCos;
    f32 edgeSin;
    f32 along;
    f32 projX;
    f32 projZ;
    f32 rejX;
    f32 rejZ;
    f32 minX;
    f32 minZ;

    for (i = 0; i < 100; i++) {
        if (g_Minigame.coinState[i] == 1) {
            rel.x = g_Minigame.coinPos[i].x - center.x;
            rel.y = 0.0f;
            rel.z = g_Minigame.coinPos[i].z - center.z;
            PSVECNormalize(&rel, &dir);
            angle = 57.29578f * (f32)acos(PSVECDotProduct(&axis, &dir));
            if (dir.z < 0.0f) {
                angle = 360.0f - angle;
            }
            if (angle >= item->_30 && angle <= item->_34) {
                sumX += rel.x;
                sumZ += rel.z;
                list[hits++] = i;
            }
        }
    }
    if (hits != 0) {
        meanX = sumX / (f32)hits;
        meanZ = sumZ / (f32)hits;
        varX = 0.0f;
        varZ = 0.0f;
        for (i = 0; i < hits; i++) {
            rel.x = g_Minigame.coinPos[list[i]].x - center.x;
            rel.z = g_Minigame.coinPos[list[i]].z - center.z;
            varX += pow(rel.x - meanX, 2.0);
            varZ += pow(rel.z - meanZ, 2.0);
        }
        sdX = sqrt(varX / (f32)hits);
        sdZ = sqrt(varZ / (f32)hits);
        spawn.x = 0.0f;
        spawn.y = 0.0f;
        spawn.z = 0.0f;
        if (sdX > 7.0f) {
            spawn.x = sdX * (fabs(meanX) / meanX) + meanX;
        } else {
            spawn.x = meanX;
        }
        if (sdZ > 6.25f) {
            spawn.z = sdZ * (fabs(meanZ) / meanZ) + meanZ;
        } else {
            spawn.z = meanZ;
        }
        mag = sqrt(pow(spawn.x, 2.0) + pow(spawn.z, 2.0));
        if (mag < 5.0f) {
            PSVECNormalize(&spawn, &spawn);
            spawn.x *= 5.0f;
            spawn.z *= 5.0f;
        } else if (mag > 15.0f) {
            PSVECNormalize(&spawn, &spawn);
            spawn.x *= 15.0f;
            spawn.z *= 15.0f;
        }
    } else {
        angle = item->_30;
        angle = 0.017453292f * (angle + (item->_34 - angle) * ((f32)rand() / 32767.0f));
        spawn.x = cos(angle);
        spawn.z = sin(angle);
        spawn.y = 0.0f;
        PSVECNormalize(&spawn, &spawn);
        PSVECScale(&spawn, 10.0f * ((f32)rand() / 32767.0f) + 5.0f, &spawn);
    }
    edgeCos = cos(0.017453292f * item->_34);
    edgeSin = sin(0.017453292f * item->_34);
    along = spawn.x * edgeCos + spawn.z * edgeSin;
    projX = edgeCos * along;
    projZ = edgeSin * along;
    rejX = spawn.x - projX;
    rejZ = spawn.z - projZ;
    minX = 3.5 * (fabs(rejX) / rejX);
    minZ = 3.125 * (fabs(rejZ) / rejZ);
    if (fabs(rejX) < fabs(minX)) {
        spawn.x = projX + minX;
    }
    if (fabs(rejZ) < fabs(minZ)) {
        spawn.z = projZ + minZ;
    }
    item->pos.x = spawn.x + center.x;
    item->pos.y = lbl_3_data_21A64[0];
    item->pos.z = spawn.z + center.z;
    memset(&item->rot, 0, sizeof(Vec));
    memset(&item->rotVel, 0, sizeof(Vec));
    item->frames = 0;
    item->state = 1;
}

// .text:0x00138448 size:0x6C mapped:0x807774DC
void fn_3_138448(SDItem* item) {
    if (SD.x_72A == 0) {
        if (item->frames < (SD_COUNTER_MAX - 1)) {
            item->frames++;
        } else {
            item->frames = SD_COUNTER_MAX;
        }
        if (item->frames >= item->timer) {
            item->_3E = 0;
            fn_3_1384B4(item);
        }
    }
}

// .text:0x001382E0 size:0x168 mapped:0x80777374
void fn_3_1382E0(SDItem* item) {
    u32 level = g_Minigame.minigameElapsedFrames / 60 / 20;
    s16 lo;
    s16 hi;

    if (SD.x_72A != 0) {
        item->state = 0;
        item->frames = 0;
        lo = lbl_3_data_21A90[g_Minigame.soloMinigameDifficulty][level][0];
        hi = lbl_3_data_21A90[g_Minigame.soloMinigameDifficulty][level][1];
        item->timer = lo * 60 + random_fn_3_9EE24((hi - lo) * 60);
    } else {
        if (item->frames < (SD_COUNTER_MAX - 1)) {
            item->frames++;
        } else {
            item->frames = SD_COUNTER_MAX;
        }
        if (level > 3) {
            level = 3;
        }
        if (item->frames / 60 >= lbl_3_data_21AD0[lbl_3_bss_B781][level]) {
            item->vel.z = 0.0f;
            item->vel.x = 0.0f;
            item->vel.y = -lbl_3_data_21A64[1];
            item->state = 2;
            item->frames = 0;
        }
    }
}

// .text:0x0013802C size:0x2B4 mapped:0x807770C0
void fn_3_13802C(SDItem* item) {
    if (SD.x_72A != 0) {
        item->vel.y = lbl_3_data_21A64[5];
        item->state = 5;
        item->frames = 0;
    } else {
        PSVECAdd((Vec*)&item->pos, (Vec*)&item->vel, (Vec*)&item->pos);
        if (fn_3_137B10(item)) {
            SD.x_1D78[item->owner] = 0;
            callSfx(0x30D);
        } else if (item->pos.y <= 0.0f) {
            item->pos.y = 0.0f;
            memset(&item->vel, 0, sizeof(Vec));
            item->frames = 0;
            item->state = 3;
            lbl_3_bss_B702 = lbl_3_data_21AF0;
            fn_800528AC(fn_3_1370A0);
            fn_3_137224((Vec*)item);
            SD.x_1D78[item->owner] = 0;
            callSfx(0x2F7);
        }
    }
}

// .text:0x00137F14 size:0x118 mapped:0x80776FA8
void fn_3_137F14(SDItem* item) {
    if (SD.x_72A != 0) {
        item->vel.y = lbl_3_data_21A64[5];
        item->state = 5;
        item->frames = 0;
    } else {
        if (item->_3E != 0) {
            item->_3F++;
            if (item->_3F >= 10) {
                callSfx(0x303);
                item->_3E = 0;
            }
        }
        if (item->frames < (SD_COUNTER_MAX - 1)) {
            item->frames++;
        } else {
            item->frames = SD_COUNTER_MAX;
        }
        if (!fn_3_137B10(item) && (f32)item->frames >= lbl_3_data_21A64[6]) {
            item->vel.y = lbl_3_data_21A64[5];
            item->state = 5;
            item->frames = 0;
        }
    }
}

// .text:0x00137DE4 size:0x130 mapped:0x80776E78
void fn_3_137DE4(SDItem* item) {
    u32 level;
    s16 lo;
    s16 hi;

    PSVECAdd((Vec*)&item->pos, (Vec*)&item->vel, (Vec*)&item->pos);
    PSVECAdd((Vec*)&item->rot, (Vec*)&item->rotVel, (Vec*)&item->rot);
    if (item->frames < (SD_COUNTER_MAX - 1)) {
        item->frames++;
    } else {
        item->frames = SD_COUNTER_MAX;
    }
    if ((f32)item->frames >= lbl_3_data_21A64[7]) {
        level = g_Minigame.minigameElapsedFrames / 60 / 20;
        if (level > 3) {
            level = 3;
        }
        item->state = 0;
        item->frames = 0;
        lo = lbl_3_data_21A90[g_Minigame.soloMinigameDifficulty][level][0];
        hi = lbl_3_data_21A90[g_Minigame.soloMinigameDifficulty][level][1];
        item->timer = lo * 60 + random_fn_3_9EE24((hi - lo) * 60);
    }
}

// .text:0x00137CF8 size:0xEC mapped:0x80776D8C
void fn_3_137CF8(SDItem* item) {
    u32 level;
    s16 lo;
    s16 hi;

    PSVECAdd((Vec*)&item->pos, (Vec*)&item->vel, (Vec*)&item->pos);
    if (!fn_3_137B10(item) && item->pos.y >= lbl_3_data_21A64[0]) {
        level = g_Minigame.minigameElapsedFrames / 60 / 20;
        if (level > 3) {
            level = 3;
        }
        item->state = 0;
        item->frames = 0;
        lo = lbl_3_data_21A90[g_Minigame.soloMinigameDifficulty][level][0];
        hi = lbl_3_data_21A90[g_Minigame.soloMinigameDifficulty][level][1];
        item->timer = lo * 60 + random_fn_3_9EE24((hi - lo) * 60);
    }
}

// .text:0x00137B10 size:0x1E8 mapped:0x80776BA4
u8 fn_3_137B10(SDItem* item) {
    u8 result = FALSE;
    InMemFielder* fielder;
    Vec launch;
    f32 y;
    f32 limit;
    f32 dx;
    f32 dz;
    int p;

    for (p = 0; p < 4; p++) {
        if (g_Minigame.playerSlots.fielderIndex[p] >= 0 &&
            (g_Minigame.starDashStunType[p] == 0 || g_Minigame.starDashStunType[p] == 3)) {
            if (item->state == 2 || p == SD.holder) {
                fielder = &g_Fielders[g_Minigame.playerSlots.fielderIndex[p]];
                y = fielder->jumpY + (fielder->actionYOffset + fielder->pos.y);
                limit = (y < item->pos.y) ? fielder->hitbox_barrelCollisions : 12.0f;
                if (!(limit < fabs(y - item->pos.y))) {
                    dx = fabs(item->pos.x - fielder->pos.x);
                    dz = fabs(item->pos.z - fielder->pos.z);
                    if (dx <= 3.5f && dz <= 3.125f) {
                        if (p == SD.holder) {
                            if (!result) {
                                launch.x = fielder->xMovementDir;
                                launch.z = fielder->zMovementDir;
                                result = TRUE;
                                launch.y = 0.0f;
                                PSVECScale(&launch, lbl_3_data_21A64[2], &launch);
                                launch.y = lbl_3_data_21A64[3];
                                memcpy(&item->vel, &launch, sizeof(Vec));
                                item->rotVel.x = lbl_3_data_21A64[4];
                                item->frames = 0;
                                item->state = 4;
                            }
                        } else {
                            g_Minigame.starDashStunType[p] = 1;
                            g_Minigame.starDashCollisionPushDelta[p].x = fielder->pos.x - item->pos.x;
                            g_Minigame.starDashCollisionPushDelta[p].z = fielder->pos.z - item->pos.z;
                            item->_3E = 1;
                            item->_3F = 0;
                        }
                    }
                }
            }
        }
    }
    return result;
}

// .text:0x001379A0 size:0x170 mapped:0x80776A34
BOOL fn_3_1379A0(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    SDItem* item;
    u32 player;
    u32 i;
    f32 y;
    f32 limit;
    f32 dx;
    f32 dz;

    for (player = 0; player < 4; player++) {
        if (g_Minigame.playerSlots.fielderIndex[player] == fielderIndex) {
            break;
        }
    }
    if (player == SD.holder) {
        return FALSE;
    }
    for (i = 0; i < lbl_3_bss_B780; i++) {
        item = &SD.item[i];
        if (SD.item[i].state == 3 || SD.item[i].state == 5) {
            y = fielder->jumpY + (fielder->actionYOffset + fielder->pos.y);
            limit = (y < item->pos.y) ? fielder->hitbox_barrelCollisions : 12.0f;
            if (!(limit < fabs(y - item->pos.y))) {
                dx = fabs(item->pos.x - (fielder->pos.x + fielder->velocityX));
                dz = fabs(item->pos.z - (fielder->pos.z + fielder->velocityZ));
                if (dx < 3.5f && dz < 3.125f) {
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

// .text:0x001373E0 size:0x5C0 mapped:0x80776474
u8 fn_3_1373E0(VecSrcDst* segment, Vec* velocity, CollisionStruct* out, f32 radius) {
    SDSide sides[4] = {{-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}};
    f32 diameter = 2.0f * radius;
    f32 halfX = 3.5f + radius;
    f32 halfZ = 3.125f + radius;
    u32 i;
    u8 pushedOut;
    SDItem* item;
    SDSide* side;
    Vec toDst;
    Vec toSrc;
    Vec dir;
    Vec hit;
    Vec dstDiff;
    f32 limit;
    f32 t;
    f32 ratio;
    f32 signX;
    f32 signZ;

    for (i = 0; i < lbl_3_bss_B780; i++) {
        item = &SD.item[i];
        pushedOut = TRUE;
        if (item->state > 1 || item->state == 4) {
            limit = (item->pos.y > -segment->dst.y) ? diameter : 12.0f;
            if (!(limit < fabs(item->pos.y + segment->dst.y))) {
                PSVECSubtract(&segment->dst, (Vec*)&item->pos, &dstDiff);
                if (!(fabs(dstDiff.x) > halfX) && !(fabs(dstDiff.z) > halfZ)) {
                    if (PSVECMag(&dstDiff) != 0.0f) {
                        PSVECNormalize(&dstDiff, &toDst);
                    } else {
                        memset(&toDst, 0, sizeof(Vec));
                    }
                    PSVECSubtract(&segment->dst, &segment->src, &dir);
                    if (PSVECMag(&dir) != 0.0f) {
                        PSVECNormalize(&dir, &dir);
                    } else {
                        memset(&dir, 0, sizeof(Vec));
                    }
                    dir.y = 0.0f;
                    toDst.y = 0.0f;
                    if (!(PSVECDotProduct(&toDst, &dir) > 0.0f)) {
                        PSVECSubtract(&segment->src, (Vec*)&item->pos, &toSrc);
                        if (fabs(toSrc.x) <= halfX && fabs(toSrc.z) <= halfZ) {
                            PSVECSubtract(&segment->src, &segment->dst, &dir);
                            dir.y = 0.0f;
                            if (PSVECMag(&dir) != 0.0f) {
                                PSVECNormalize(&dir, &dir);
                                segment->dst.x = segment->src.x;
                                segment->dst.z = segment->src.z;
                                pushedOut = FALSE;
                                segment->src.x = 7.0f * dir.x + segment->src.x;
                                segment->src.z = 6.25f * dir.z + segment->src.z;
                                goto sweep;
                            }
                            ratio = toDst.z / toDst.x;
                            signX = toDst.x;
                            signZ = toDst.z;
                            if (0.8928571343421936 < fabs(ratio)) {
                                signZ = fabs(signZ) / signZ;
                            } else if (0.8928571343421936 > fabs(ratio)) {
                                signX = fabs(signX) / signX;
                            } else {
                                signZ = fabs(signZ) / signZ;
                                signX = fabs(signX) / signX;
                            }
                            out->position.x = signX * halfX + item->pos.x;
                            out->position.y = -segment->src.y;
                            out->position.z = signZ * halfZ + item->pos.z;
                            out->normal.x = -1.0f * velocity->x;
                            out->normal.y = velocity->y;
                            out->normal.z = -1.0f * velocity->z;
                            return TRUE;
                        }
                    sweep:
                        PSVECSubtract(&segment->dst, &segment->src, &dir);
                        side = (dir.x > 0.0f) ? &sides[0] : &sides[1];
                        side->d = side->nx * (halfX * (fabs(side->nx) / side->nx) + item->pos.x);
                        t = -(segment->src.x * side->nx + segment->src.z * side->nz - side->d) /
                            (dir.x * side->nx + dir.z * side->nz);
                        hit.x = dir.x * t + segment->src.x;
                        hit.z = dir.z * t + segment->src.z;
                        hit.y = -segment->src.y;
                        if (fabs(hit.z - item->pos.z) <= halfZ && t >= 0.0f) {
                            memcpy(&out->normal, velocity, sizeof(Vec));
                            out->normal.x *= -1.0f;
                        } else {
                            side = (dir.z > 0.0f) ? &sides[3] : &sides[2];
                            side->d = side->nz * (item->pos.z + halfZ * fabs(side->nz) / side->nz);
                            t = -(segment->src.x * side->nx + segment->src.z * side->nz - side->d) /
                                (dir.x * side->nx + dir.z * side->nz);
                            hit.x = dir.x * t + segment->src.x;
                            hit.z = dir.z * t + segment->src.z;
                            hit.y = -segment->src.y;
                            memcpy(&out->normal, velocity, sizeof(Vec));
                            out->normal.z *= -1.0f;
                        }
                        if (pushedOut) {
                            memcpy(&out->position, &hit, sizeof(Vec));
                        } else {
                            segment->dst.y *= -1.0f;
                            memcpy(&out->position, &segment->dst, sizeof(Vec));
                        }
                        return TRUE;
                    }
                }
            }
        }
    }
    return FALSE;
}

// .text:0x00137224 size:0x1BC mapped:0x807762B8
void fn_3_137224(Vec* pos) {
    u32 i;
    Vec coin;
    Vec diff;
    Vec kick;
    f32 strength;

    for (i = 0; i < 100; i++) {
        if (g_Minigame.coinState[i] == 1 && !(g_Minigame.coinPos[i].y > lbl_3_data_219B8[14]) &&
            !(g_Minigame.coinVelocity[i].y > 0.05)) {
            coin.x = g_Minigame.coinPos[i].x;
            coin.y = g_Minigame.coinPos[i].y;
            coin.z = g_Minigame.coinPos[i].z;
            PSVECSubtract(&coin, pos, &diff);
            strength = (36.0f - PSVECMag(&diff)) / 36.0f;
            diff.y = 0.0f;
            if (PSVECMag(&diff) == 0.0f) {
                diff.z = -1.0f;
            }
            PSVECNormalize(&diff, &diff);
            kick.x = 0.0f;
            kick.z = 0.0f;
            kick.y = 0.05f * (2.0 * ((f32)rand() / 32767.0f - 0.5)) + 0.3f;
            PSVECScale(&kick, strength, &kick);
            PSVECAdd(&kick, (Vec*)&g_Minigame.coinVelocity[i], (Vec*)&g_Minigame.coinVelocity[i]);
        }
    }
}

// .text:0x001371E8 size:0x3C mapped:0x8077627C
void fn_3_1371E8(void) {
    lbl_3_bss_B702 = lbl_3_data_21AF0;
    fn_800528AC(fn_3_1370A0);
}

// .text:0x001370A0 size:0x148 mapped:0x80776134
void fn_3_1370A0(camera_803c639c_s* cam) {
    Vec offset;
    Mtx invView;

    memset(&offset, 0, sizeof(Vec));
    offset.y = lbl_3_data_21AF4 * (2.0 * ((f32)rand() / 32767.0f - 0.5));
    PSMTXInverse(cam->view, invView);
    PSMTXMultVecSR(invView, &offset, &offset);
    cam->eye.x += offset.x;
    cam->eye.y += offset.y;
    cam->eye.z += offset.z;
    cam->target.x += offset.x;
    cam->target.y += offset.y;
    cam->target.z += offset.z;
    if (--lbl_3_bss_B702 <= 0) {
        lbl_3_bss_B702 = 0;
        fn_800528B4();
    }
}

// .text:0x00136EA4 size:0x1FC mapped:0x80775F38
void fn_3_136EA4(void) {
    if (g_Minigame.turnOverStatus != 0) {
        g_Minigame.playerIDWithPowerup[0] = -1;
        g_Minigame.powerup.activeInd = 0;
    } else if (g_Minigame.powerup.activeInd != 0) {
        fn_3_13688C(&g_Minigame.powerup);
    } else {
        fn_3_136CF4(&g_Minigame.powerup);
    }
}

// .text:0x00136CF4 size:0x1B0 mapped:0x80775D88
void fn_3_136CF4(MinigamePowerupStruct* powerup) {
    f32 angle;

    if (g_Minigame.playerIDWithPowerup[0] != -1) {
        if (--g_Minigame._1D58 <= 0) {
            if ((s8)g_Minigame._1D6D != g_Minigame.playerIDWithPowerup[0]) {
                fn_800115C8(g_Minigame.playerIDWithPowerup[0]);
            }
            g_Minigame.playerIDWithPowerup[0] = -1;
        }
    } else if (--powerup->timer <= 0) {
        if ((s8)(rand() % 100 - lbl_3_data_21B16) < 0) {
            powerup->activeInd = 1;
        } else {
            powerup->activeInd = 2;
        }
        powerup->pos.x = lbl_3_data_219AC.x;
        powerup->pos.y = lbl_3_data_219AC.y;
        powerup->pos.z = lbl_3_data_219AC.z;
        powerup->_0C.y = lbl_3_data_21AF8[0];
        angle = 360.0f * ((f32)rand() / 32767.0f);
        angle = 0.017453292f * angle;
        powerup->_0C.x = lbl_3_data_21AF8[1] * (f32)cos(angle);
        powerup->_0C.z = lbl_3_data_21AF8[1] * (f32)sin(angle);
        powerup->timer = lbl_3_data_21B10[1];
    }
}

// .text:0x0013688C size:0x468 mapped:0x80775920
void fn_3_13688C(MinigamePowerupStruct* powerup) {
    VecSrcDst probe;
    CollisionStruct hit;
    InMemFielder* fielder;
    f32 bestDistSq;
    f32 distSq;
    f32 reach;
    int best;
    int p;

    probe.src.x = powerup->pos.x;
    probe.src.y = -powerup->pos.y;
    probe.src.z = powerup->pos.z;
    powerup->_0C.y += lbl_3_data_21AF8[2];
    powerup->pos.x += powerup->_0C.x;
    powerup->pos.y += powerup->_0C.y;
    powerup->pos.z += powerup->_0C.z;
    if (powerup->pos.y < 0.0f) {
        powerup->pos.y = 0.0f;
        powerup->_0C.y = 0.0f;
    }
    sdBounce(&powerup->pos, &powerup->_0C, &probe, &hit);
    probe.dst.x = powerup->pos.x;
    probe.dst.y = -powerup->pos.y;
    probe.dst.z = powerup->pos.z;
    if (fn_3_1373E0(&probe, (Vec*)&powerup->_0C, &hit, lbl_3_data_21AF8[3])) {
        powerup->pos.x = hit.position.x;
        powerup->pos.y = hit.position.y;
        powerup->pos.z = hit.position.z;
        memcpy(&powerup->_0C, &hit.normal, sizeof(Vec));
        sdBounce(&powerup->pos, &powerup->_0C, &probe, &hit);
    }
    bestDistSq = 99999.9f;
    reach = lbl_3_data_21AF8[3];
    best = -1;
    for (p = 0; p < 4; p++) {
        if (g_Minigame.playerSlots.fielderIndex[p] >= 0 &&
            (g_Minigame.starDashStunType[p] == 0 || g_Minigame.starDashStunType[p] == 3)) {
            fielder = &g_Fielders[g_Minigame.playerSlots.fielderIndex[p]];
            if (fielder->isJump == 0 || fielder->jumpCountUp <= 3) {
                if (!(fielder->hitbox_barrelCollisions + fielder->actionYOffset < powerup->pos.y)) {
                    distSq = sdDistSqXZ(fielder->pos.x, fielder->pos.z, powerup->pos.x, powerup->pos.z);
                    if (distSq < SQ(reach + fielderHitboxesForGarlicKnockout[fielder->Weight]) &&
                        distSq < bestDistSq) {
                        bestDistSq = distSq;
                        best = p;
                    }
                }
            }
        }
    }
    if (best >= 0) {
        g_Minigame.playerIDWithPowerup[0] = best;
        g_Minigame._1D58 = lbl_3_data_21B10[2];
        if (g_Minigame.powerup.activeInd == 2) {
            if ((s8)g_Minigame._1D6D == best) {
                fn_3_14E988(g_Minigame._1D6D);
                fn_800115C8((s8)best);
                g_Minigame._1D6D = -1;
            }
            SD.factor = &lbl_3_data_21AF8[5];
            callSfx(0x2F5);
            fn_3_1695A4(best, 0);
        } else {
            SD.factor = &lbl_3_data_21AF8[4];
            callSfx(0x2F6);
            fn_3_16C394(best);
        }
        powerup->activeInd = 0;
        powerup->timer = lbl_3_data_21B10[0];
    } else {
        powerup->timer--;
        if (powerup->timer <= 0) {
            powerup->activeInd = 0;
            powerup->timer = lbl_3_data_21B10[0];
        }
    }
}

// .text:0x00136220 size:0x66C mapped:0x807752B4
void fn_3_136220(void) {
    InMemFielder* fielder;
    int p;
    VecSrcDst probe;
    CollisionStruct hit;
    u32 type;
    f32 len;
    f32 factor;
    f32 dx;
    f32 dz;
    f32 dist;

    for (p = 0; p < 4; p++) {
        if (g_Minigame.playerSlots.fielderIndex[p] < 0) {
            continue;
        }
        fielder = &g_Fielders[g_Minigame.playerSlots.fielderIndex[p]];
        if (fielder->onFire == 0) {
            if (g_Minigame.starDashStunType[p] == 1) {
                len = VEC_LENGTH_XZ(&g_Minigame.starDashCollisionPushDelta[p]);
                factor = lbl_3_data_21B18[0] / len;
                g_Minigame.starDashCollisionPushDelta[p].x *= factor;
                g_Minigame.starDashCollisionPushDelta[p].z *= factor;
                g_Minigame.starDashCollisionPushDelta[p].y = 0.0f;
                SD._1D5A[p] = 0;
                g_Minigame.starDashStunType[p] = 2;
                if (g_Minigame.playerIDWithPowerup[0] == p) {
                    fn_800115C8(g_Minigame.playerIDWithPowerup[0]);
                    g_Minigame.playerIDWithPowerup[0] = -1;
                }
                fn_3_1360BC(p);
                callSfx(0x2E7);
                playCharacterSound(fielder->CharID, 10);
                setCharacterAnimations(g_Minigame.playerSlots.characterIndex[p], 2);
            } else if (g_Minigame.starDashStunType[p] == 2) {
                SD._1D5A[p]++;
                len = VEC_LENGTH_XZ(&g_Minigame.starDashCollisionPushDelta[p]);
                if (len > 0.0f) {
                    probe.src.x = fielder->pos.x;
                    probe.src.y = -1.0f;
                    probe.src.z = fielder->pos.z;
                    probe.dst.x = 2.0f * g_Minigame.starDashCollisionPushDelta[p].x + fielder->pos.x;
                    probe.dst.y = -1.0f;
                    probe.dst.z = 2.0f * g_Minigame.starDashCollisionPushDelta[p].z + fielder->pos.z;
                    type = checkCollision(&probe, &hit, 0, FALSE);
                    if (type) {
                        g_Minigame.starDashCollisionPushDelta[p].x = 0.0f;
                        g_Minigame.starDashCollisionPushDelta[p].z = 0.0f;
                    }
                    fielder->pos.x += g_Minigame.starDashCollisionPushDelta[p].x;
                    fielder->pos.y += g_Minigame.starDashCollisionPushDelta[p].y;
                    fielder->pos.z += g_Minigame.starDashCollisionPushDelta[p].z;
                    g_Minigame.starDashCollisionPushDelta[p].x *= lbl_3_data_21B18[1];
                    g_Minigame.starDashCollisionPushDelta[p].z *= lbl_3_data_21B18[1];
                }
                if (SD._1D5A[p] > lbl_3_data_21B20[1]) {
                    g_Minigame.starDashStunType[p] = 3;
                    fielder->velocityX = 0.0f;
                    fielder->velocityZ = 0.0f;
                    SD._1D5A[p] = 0;
                    fielder->currentVelocity = 0.0f;
                }
            } else if (g_Minigame.starDashStunType[p] == 3) {
                SD._1D5A[p]++;
                if (SD._1D5A[p] > lbl_3_data_21B20[2]) {
                    g_Minigame.starDashStunType[p] = 0;
                }
            }
        }
        probe.src.x = fielder->pos.x;
        probe.src.y = -1.0f;
        probe.src.z = fielder->pos.z;
        probe.dst.x = fielder->pos.x;
        probe.dst.y = 1.0f;
        probe.dst.z = fielder->pos.z;
        type = checkCollision(&probe, &hit, 0, FALSE) & (BALL_COLLISION_TYPE_FOUL - 1);
        if (type == BALL_COLLISION_TYPE_WALL || type == BALL_COLLISION_TYPE_STRUCTURE ||
            (type >= BALL_COLLISION_TYPE_PIT_WALL && type <= BALL_COLLISION_TYPE_PIT) ||
            type == BALL_COLLISION_TYPE_UNCLIMBABLE_WALL) {
            dz = base_MoundCoordinates[4].x - fielder->pos.z;
            dx = base_MoundCoordinates[4].x - fielder->pos.x;
            dist = dolsqrtf2(dx * dx + dz * dz);
            if (dist == 0.0f) {
                fielder->pos.x = lbl_3_data_2198C[p].x;
                fielder->pos.z = lbl_3_data_2198C[p].z;
            } else {
                dx /= dist;
                dz /= dist;
                if (dist < 7.0f) {
                    fielder->pos.x -= 0.2f * dx;
                    fielder->pos.z -= 0.2f * dz;
                } else {
                    fielder->pos.x += 0.2f * dx;
                    fielder->pos.z += 0.2f * dz;
                }
            }
        }
    }
}

#pragma dont_inline on
// .text:0x001360BC size:0x164 mapped:0x80775150
void fn_3_1360BC(int player) {
    InMemFielder* fielder;
    int n;
    int i;
    int count;

    fielder = &g_Fielders[g_Minigame.playerSlots.fielderIndex[player]];
    SD._1DF4[player] = 1;
    n = lbl_3_data_21B20[3];
    if (g_Minigame.miniGameCurrentPoints[player] < n) {
        n = g_Minigame.miniGameCurrentPoints[player];
    }
    if (n != 0) {
        count = 0;
        for (i = 0; i < 50; i++) {
            if (g_Minigame.coinState[i] == 0) {
                g_Minigame.coinPos[i].x = fielder->pos.x;
                g_Minigame.coinPos[i].y = fielder->pos.y;
                g_Minigame.coinPos[i].z = fielder->pos.z;
                g_Minigame.coinPos[i].y = fielder->hitbox_barrelCollisions;
                g_Minigame.coinVelocity[i].y = lbl_3_data_219B8[18];
                getComponentsFromSAng(random_fn_3_9EE24(0x1000), &g_Minigame.coinVelocity[i].x,
                                      &g_Minigame.coinVelocity[i].z);
                {
                    f32 speed = RandomF32_Game_Range(lbl_3_data_219B8[16], lbl_3_data_219B8[17]);
                    g_Minigame.coinVelocity[i].x *= speed;
                    g_Minigame.coinVelocity[i].z *= speed;
                }
                g_Minigame.coinState[i] = 1;
                g_Minigame.coinFrameCounter[i] = 0;
                SD.spawnedCoins++;
                count++;
                if (count >= n) {
                    break;
                }
            }
        }
        callSfx(0x2E8);
        g_Minigame.miniGameCurrentPoints[player] -= n;
    }
}
#pragma dont_inline reset

// .text:0x00136048 size:0x74 mapped:0x807750DC
void fn_3_136048(void) {
    int p;

    for (p = 0; p < 4; p++) {
        SD.pathAngle[p] += lbl_3_data_21A44;
        SD.pathAngle[p] = normalizeAngle(SD.pathAngle[p]);
    }
}

// .text:0x00135FF4 size:0x54 mapped:0x80775088
void fn_3_135FF4(void) {
    if (lbl_3_data_21A3C[SD.phaseIndex][0] * 60 == g_Minigame.minigameElapsedFrames) {
        SD.phase = 1;
        SD.phaseFrames = 0;
        SD.phaseProgress = 0.0f;
        SD.phaseIndex++;
    }
}

// .text:0x00135F4C size:0xA8 mapped:0x80774FE0
void fn_3_135F4C(void) {
    SD.phaseFrames++;
    SD.phaseProgress = (f32)SD.phaseFrames / (f32)lbl_3_data_21A60[0];
    fn_3_135C18();
    if (SD.phaseFrames >= lbl_3_data_21A60[0]) {
        SD.phase = 2;
    }
}

// .text:0x00135E98 size:0xB4 mapped:0x80774F2C
void fn_3_135E98(void) {
    SD.phaseFrames++;
    SD.phaseProgress = 1.0f - (f32)SD.phaseFrames / (f32)lbl_3_data_21A60[0];
    fn_3_135C18();
    if (SD.phaseFrames >= lbl_3_data_21A60[0]) {
        SD.phase = 0;
    }
}

// .text:0x00135E38 size:0x60 mapped:0x80774ECC
void fn_3_135E38(void) {
    fn_3_135C18();
    if (lbl_3_data_21A3C[SD.phaseIndex - 1][1] * 60 == g_Minigame.minigameElapsedFrames) {
        SD.phase = 3;
        SD.phaseFrames = 0;
    }
}

// .text:0x00135C18 size:0x220 mapped:0x80774CAC
void fn_3_135C18(void) {
    int p;
    int k;
    int idx;
    SDTrail* trail;
    f32 vx;
    f32 vz;
    f32 d;
    f32 stepLen;
    f32 span;
    f32 outerR;

    span = SD.phaseProgress * lbl_3_data_21A54[1] - lbl_3_data_21A54[0];
    stepLen = (lbl_3_data_21A54[1] - lbl_3_data_21A54[0]) / (f32)lbl_3_data_21A60[1];
    outerR = span + lbl_3_data_21A54[0];
    idx = 0;
    for (p = 0; p < 4; p++) {
        getComponentsFromSAng(SD.pathAngle[p], &vx, &vz);
        SD.path[p].start.x = vx * lbl_3_data_21A54[0] + lbl_3_data_21A48.x;
        SD.path[p].start.z = vz * lbl_3_data_21A54[0] + lbl_3_data_21A48.z;
        SD.path[p].end.x = vx * outerR + lbl_3_data_21A48.x;
        SD.path[p].end.z = vz * outerR + lbl_3_data_21A48.z;
        vx = (SD.path[p].end.x - SD.path[p].start.x) / span;
        vz = (SD.path[p].end.z - SD.path[p].start.z) / span;
        d = span;
        trail = &SD.trail[idx];
        for (k = 0; k < lbl_3_data_21A60[1]; k++) {
            trail->pos.x = vx * d + SD.path[p].start.x;
            trail->pos.z = vz * d + SD.path[p].start.z;
            if (d < 0.0f) {
                trail->active = 0;
            } else {
                d -= stepLen;
                if (trail->active) {
                    fn_3_156548(idx, trail->pos.x, -trail->pos.y, trail->pos.z);
                } else {
                    fn_3_15730C(idx, trail->pos.x, -trail->pos.y, trail->pos.z);
                    trail->active = 1;
                }
            }
            trail++;
            idx++;
        }
    }
}

// .text:0x00135A64 size:0x1B4 mapped:0x80774AF8
void fn_3_135A64(void) {
    int p;
    int k;
    InMemFielder* fielder;
    s16 angle;
    f32 dist;

    if (g_Minigame.turnOverStatus == 0 && !(SD.phaseProgress < 0.3f)) {
        for (p = 0; p < 4; p++) {
            if (g_Minigame.playerSlots.fielderIndex[p] >= 0 && p != SD.holder &&
                g_Minigame.starDashStunType[p] == 0) {
                fielder = &g_Fielders[g_Minigame.playerSlots.fielderIndex[p]];
                if (fielder->isJump == 0 || fielder->jumpCountUp <= 3) {
                    angle = calculateAngleFromCoordinates(fielder->pos.x - lbl_3_data_219AC.x,
                                                          fielder->pos.z - lbl_3_data_219AC.z);
                    for (k = 0; k < 4; k++) {
                        if (getDifferenceInAngle(angle, SD.pathAngle[k]) <= 0x200) {
                            dist = calculateBallInterceptDistance(&SD.path[k].start, &SD.path[k].end,
                                                                  &fielder->pos, NULL);
                            if (dist < lbl_3_data_21A54[2] + fielderHitboxesForGarlicKnockout[fielder->Weight] &&
                                dist >= 0.0f) {
                                fn_3_1360BC(p);
                                g_Minigame.starDashStunType[p] = 3;
                                SD._1D5A[p] = 0;
                                maybeCastleFireballBurn(g_Minigame.playerSlots.fielderIndex[p], 2);
                                setCharacterAnimations(g_Minigame.playerSlots.characterIndex[p], 2);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

// .text:0x00135924 size:0x140 mapped:0x807749B8
void fn_3_135924(void) {
    u32 i;

    for (i = 0; i < 100; i++) {
        if (g_Minigame.coinState[i] == 1 && g_Minigame.coinPos[i].y < 3.0f) {
            fn_3_13583C((Vec*)&g_Minigame.coinPos[i]);
        }
    }
}

// .text:0x0013583C size:0xE8 mapped:0x807748D0
void fn_3_13583C(Vec* pos) {
    Vec center = {0.0f, 0.0f, 20.0f};
    Vec diff;

    if (pos == NULL) {
        return;
    }
    PSVECSubtract(pos, &center, &diff);
    diff.y = 0.0f;
    if (PSVECMag(&diff) <= 3.5f) {
        fn_3_1357A4(pos, &diff);
    }
}

// .text:0x001357A4 size:0x98 mapped:0x80774838
void fn_3_1357A4(Vec* out, Vec* dir) {
    Vec base = {0.0f, 0.0f, 20.0f};
    Vec offset;

    if (out == NULL || dir == NULL) {
        return;
    }
    PSVECNormalize(dir, &offset);
    PSVECScale(&offset, 3.5f, &offset);
    out->x = base.x + offset.x;
    out->z = base.z + offset.z;
}

// .text:0x001356F8 size:0xAC mapped:0x8077478C
void fn_3_1356F8(void) {
    u32 i;
    u8 strength;
    SDAI* ai = g_Minigame.sd.ai;

    memset(g_Minigame._1D7C, 0, 0x78);
    for (i = 0; i < 4; i++) {
        strength = g_Minigame.playerSlots.aiStrength[i];
        ai->angle = -1;
        ai->_0 = RandomInt_Game(100) < lbl_3_data_21B88[strength] ? 3.0f : 1.5f;
        ai++;
    }
}

// .text:0x00135698 size:0x60 mapped:0x8077472C
int fn_3_135698(const void* a, const void* b) {
    const SDCoinEntry* ea = a;
    const SDCoinEntry* eb = b;

    if (ea->valid != 0 && eb->valid == 0) {
        return -1;
    }
    if (ea->valid == 0 && eb->valid != 0) {
        return 1;
    }
    if (ea->score < eb->score) {
        return -1;
    }
    return ea->score > eb->score;
}

// .text:0x0013564C size:0x4C mapped:0x807746E0
int fn_3_13564C(f32 x, f32 z) {
    if (x >= 0.0f) {
        if (z >= 0.0f) {
            return 0;
        }
        return 3;
    }
    if (z >= 0.0f) {
        return 1;
    }
    return 2;
}

// .text:0x00135600 size:0x4C mapped:0x80774694
void fn_3_135600(f32 x, f32 z, f32* outX, f32* outZ) {
    f32 dx = x - lbl_3_data_21A48.x;
    f32 dz = z - lbl_3_data_21A48.z;

    *outX = dx * g_Minigame.sd.rotCos - dz * g_Minigame.sd.rotSin;
    *outZ = dz * g_Minigame.sd.rotCos + dx * g_Minigame.sd.rotSin;
}

#pragma dont_inline on
// .text:0x00135520 size:0xE0 mapped:0x807745B4
int fn_3_135520(f32 x, f32 z, f32 radius) {
    if (x >= 0.0f) {
        if (z >= 0.0f) {
            if (z <= radius) {
                return 1;
            }
            if (x <= radius) {
                return 2;
            }
        } else {
            if (x <= radius) {
                return 1;
            }
            if (z >= -radius) {
                return 2;
            }
        }
    } else {
        if (z >= 0.0f) {
            if (x >= -radius) {
                return 1;
            }
            if (z <= radius) {
                return 2;
            }
        } else {
            if (z >= -radius) {
                return 1;
            }
            if (x >= -radius) {
                return 2;
            }
        }
    }
    return 0;
}
#pragma dont_inline reset

// .text:0x001354BC size:0x64 mapped:0x80774550
BOOL fn_3_1354BC(int item, f32 x, f32 z) {
    BOOL result = FALSE;
    f32 dx = fabs(g_Minigame.sd.item[item].pos.x - x);
    f32 dz = fabs(g_Minigame.sd.item[item].pos.z - z);

    if (dx <= 4.7f && dz <= 4.325f) {
        result = TRUE;
    }
    return result;
}

// .text:0x001350BC size:0x400 mapped:0x80774150
SDCoinEntry* fn_3_1350BC(u32 player, int quadrant, u32 count, SDCoinEntry* entries) {
    u32 k;
    u32 i;
    u32 p;
    int strength;
    f32 holderLimit;
    f32 powerupLimit;
    SDCoinEntry* e;
    VecXYZ* coin;
    f32 cx;
    f32 cz;

    strength = g_Minigame.playerSlots.aiStrength[player];
    if (count != 0) {
        k = 0;
        do {
            e = &entries[k];
            e->valid = 1;
            cx = g_Minigame.coinPos[e->coin].x;
            cz = g_Minigame.coinPos[e->coin].z;
            if (sdDistSqXZ(cx, cz, lbl_3_data_21A48.x, lbl_3_data_21A48.z) < 20.25f) {
                e->valid = 0;
            } else if (player != SD.holder) {
                if (SD.holder >= 0) {
                    InMemFielder* holder = &g_Fielders[g_Minigame.playerSlots.fielderIndex[SD.holder]];
                    holderLimit = lbl_3_data_21B38[strength];
                    if (sdDistSqXZ(cx, cz, holder->pos.x, holder->pos.z) <= holderLimit * holderLimit) {
                        e->valid = 0;
                    }
                }
                if (e->valid) {
                    i = 0;
                    do {
                        if (SD.item[i].state >= 1 && SD.item[i].state <= 3) {
                            if (fn_3_1354BC(i, cx, cz)) {
                                e->valid = 0;
                                break;
                            }
                        }
                    } while (++i < lbl_3_data_21A88[g_Minigame.soloMinigameDifficulty]);
                }
                if (e->valid && g_Minigame.powerup.activeInd == 2) {
                    powerupLimit = lbl_3_data_21B58[strength];
                    if (sdDistSqXZ(cx, cz, g_Minigame.powerup.pos.x, g_Minigame.powerup.pos.z) <=
                        powerupLimit * powerupLimit) {
                        e->valid = 0;
                    }
                }
            }
            coin = &g_Minigame.coinPos[e->coin];
            e->score = sdDistSqXZ(coin->x, coin->z, g_Fielders[g_Minigame.playerSlots.fielderIndex[player]].pos.x,
                                  g_Fielders[g_Minigame.playerSlots.fielderIndex[player]].pos.z);
            for (p = 0; p < g_Minigame.miniGameNumberOfParticipants; p++) {
                if (p != player) {
                    InMemFielder* other = &g_Fielders[g_Minigame.playerSlots.fielderIndex[p]];
                    f32 distSq = sdDistSqXZ(coin->x, coin->z, other->pos.x, other->pos.z);
                    if (distSq < 36.0f && distSq < e->score) {
                        e->score += 100.0f;
                    }
                }
            }
            if (SD.phase != 0 && player != SD.holder) {
                if (e->quadrant == ((quadrant + 1) & 3)) {
                    e->score += 10000.0f;
                } else if (e->quadrant == ((quadrant + 2) & 3)) {
                    e->score += 400.0f;
                }
                if (fn_3_135520(e->x, e->z, 2.0f * lbl_3_data_21A54[2])) {
                    e->valid = 0;
                }
            }
        } while (++k < count);
        fn_800246D4(fn_3_135698, entries, entries, sizeof(SDCoinEntry), count);
        return entries;
    }
    return NULL;
}

// .text:0x00134D4C size:0x370 mapped:0x80773DE0
u32 fn_3_134D4C(f32 cx, f32 cz, f32 radius, f32 ax, f32 az, f32 bx, f32 bz) {
    f32 dx;
    f32 dz;
    f32 dist;
    f32 ex;
    f32 ez;
    f32 len;
    f32 nx;
    f32 nz;
    f32 t;
    f32 disc;
    f32 sqX;
    f32 sqZ;

    dx = cx - ax;
    dz = cz - az;
    sqX = dx * dx;
    sqZ = dz * dz;
    dist = dolsqrtf2(sqX + sqZ);
    ex = bx - ax;
    ez = bz - az;
    sqX = ex * ex;
    sqZ = ez * ez;
    len = dolsqrtf2(sqX + sqZ);
    nz = ez / len;
    nx = ex / len;
    t = dz * nz + dx * nx;
    if (dist < radius) {
        return 1;
    }
    if (dist == radius && t > 0.0f) {
        return 2;
    }
    if (t > 0.0f) {
        disc = t * t + (radius * radius - dist * dist);
        if (disc >= 0.0f && t - dolsqrtf2(disc) <= len) {
            return 3;
        }
    }
    return 0;
}

// .text:0x00134C80 size:0xCC mapped:0x80773D14
BOOL fn_3_134C80(u32 player, int a, u32 b, f32 x, f32 z) {
    if (g_Minigame._1D72 != 0 && player != (s8)g_Minigame._1D6D) {
        if (b == ((a + 1) & 3) || b == ((a + 2) & 3)) {
            return TRUE;
        }
    }
    return !!fn_3_134D4C(lbl_3_data_21A48.x, lbl_3_data_21A48.z, 4.5f,
                         g_Fielders[g_Minigame.playerSlots.fielderIndex[player]].pos.x,
                         g_Fielders[g_Minigame.playerSlots.fielderIndex[player]].pos.z, x, z);
}

// .text:0x0013493C size:0x344 mapped:0x807739D0
int fn_3_13493C(u32 player, f32* targetX, f32* targetZ, u32 depth) {
    f32 angle;
    f32 x1;
    f32 z1;
    f32 x2;
    f32 z2;
    f32 dx;
    f32 dz;
    f32 dist1;
    f32 dist2;
    f32 rotX;
    f32 rotZ;

    dx = *targetX - g_Fielders[g_Minigame.playerSlots.fielderIndex[player]].pos.x;
    dz = *targetZ - g_Fielders[g_Minigame.playerSlots.fielderIndex[player]].pos.z;
    angle = atan2(dz, dx);
    if (g_Minigame._1D72 != 0 && player != (s8)g_Minigame._1D6D) {
        angle += HALF_PI;
        angle = radianAngleReduction(angle);
        *targetX = 8.0f * COSF(angle) + lbl_3_data_21A48.x;
        *targetZ = 8.0f * SINF(angle) + lbl_3_data_21A48.z;
    } else {
        angle = radianAngleReduction(angle - HALF_PI);
        x1 = 8.0f * COSF(angle) + lbl_3_data_21A48.x;
        z1 = 8.0f * SINF(angle) + lbl_3_data_21A48.z;
        dx = x1 - g_Fielders[g_Minigame.playerSlots.fielderIndex[player]].pos.x;
        dz = z1 - g_Fielders[g_Minigame.playerSlots.fielderIndex[player]].pos.z;
        angle += PI;
        dist1 = dz + (dx * dx + dz);
        angle = radianAngleReduction(angle);
        x2 = 8.0f * COSF(angle) + lbl_3_data_21A48.x;
        z2 = 8.0f * SINF(angle) + lbl_3_data_21A48.z;
        dx = x2 - g_Fielders[g_Minigame.playerSlots.fielderIndex[player]].pos.x;
        dz = z2 - g_Fielders[g_Minigame.playerSlots.fielderIndex[player]].pos.z;
        dist2 = dz + (dx * dx + dz);
        if (dist1 < dist2) {
            *targetX = x1;
            *targetZ = z1;
        } else {
            *targetX = x2;
            *targetZ = z2;
        }
    }
    if (depth != 0) {
        if (fn_3_134D4C(lbl_3_data_21A48.x, lbl_3_data_21A48.z, 4.5f,
                        g_Fielders[g_Minigame.playerSlots.fielderIndex[player]].pos.x,
                        g_Fielders[g_Minigame.playerSlots.fielderIndex[player]].pos.z, *targetX, *targetZ)) {
            fn_3_13493C(player, targetX, targetZ, depth - 1);
        }
    }
    dz = *targetZ - lbl_3_data_21A48.z;
    dx = *targetX - lbl_3_data_21A48.x;
    rotX = dx * g_Minigame._1DF0 - dz * g_Minigame._1DEC;
    rotZ = dz * g_Minigame._1DF0 + dx * g_Minigame._1DEC;
    return fn_3_13564C(rotX, rotZ);
}

// .text:0x00134918 size:0x24 mapped:0x807739AC
int fn_3_134918(const void* a, const void* b) {
    if (((const SDTargetEntry*)a)->distSq < ((const SDTargetEntry*)b)->distSq) {
        return -1;
    }
    return ((const SDTargetEntry*)a)->distSq > ((const SDTargetEntry*)b)->distSq;
}

// .text:0x00134908 size:0x10 mapped:0x8077399C
int fn_3_134908(const void* a, const void* b) {
    return ((const SDTargetEntry*)b)->points - ((const SDTargetEntry*)a)->points;
}

// .text:0x00134658 size:0x2B0 mapped:0x807736EC
void fn_3_134658(u32 target, f32* outX, f32* outZ, int* outQuadrant) {
    SDTargetEntry entries[4];
    u32 i;
    u32 count;
    f32 dx;
    f32 dz;

    count = 0;
    i = 0;
    do {
        InMemFielder* other;
        InMemFielder* self;

        if (i == target) {
            continue;
        }
        if (g_Minigame.starDashStunType[i] != 0) {
            continue;
        }
        other = &g_Fielders[g_Minigame.playerSlots.fielderIndex[i]];
        if (other->onFire != 0) {
            continue;
        }
        self = &g_Fielders[g_Minigame.playerSlots.fielderIndex[target]];
        dz = other->pos.z - self->pos.z;
        dx = other->pos.x - self->pos.x;
        entries[count].distSq = dx * dx + dz * dz;
        entries[count].points = g_Minigame.miniGameCurrentPoints[i];
        entries[count].player = i;
        count++;
    } while (++i < 4);
    if (count != 0) {
        u32 k;
        fn_800246D4(fn_3_134918, entries, entries, 8, count);
        k = 0;
        do {
            if (entries[k].distSq <= 4.0f && entries[k].points > 0) {
                *outX = g_Fielders[g_Minigame.playerSlots.fielderIndex[entries[k].player]].pos.x;
                *outZ = g_Fielders[g_Minigame.playerSlots.fielderIndex[entries[k].player]].pos.z;
                *outQuadrant = fn_3_13564C(*outX, *outZ);
                return;
            }
        } while (++k < count);
        fn_800246D4(fn_3_134908, entries, entries, 8, count);
        if (entries[0].points > 0) {
            *outX = g_Fielders[g_Minigame.playerSlots.fielderIndex[entries[0].player]].pos.x;
            *outZ = g_Fielders[g_Minigame.playerSlots.fielderIndex[entries[0].player]].pos.z;
            *outQuadrant = fn_3_13564C(*outX, *outZ);
        }
    }
}

// .text:0x001345AC size:0xAC mapped:0x80773640
s16 fn_3_1345AC(s16 a, s16 b, int c) {
    s16 step;

    if (a < 0 || b < 0) {
        return b;
    }
    step = angleDifferenceNormalized(b, a) / lbl_3_data_21B8C[c];
    if (step == 0 || __abs(step) > 1500) {
        return b;
    }
    return normalizeAngle(a + step);
}

// .text:0x001344BC size:0xF0 mapped:0x80773550
BOOL fn_3_1344BC(int a, int b) {
    f32 bX;
    f32 bZ;
    f32 aAngle;
    s16 bAngle;

    bX = g_Fielders[g_Minigame.playerSlots.fielderIndex[b]].pos.x - lbl_3_data_21A48.x;
    bZ = g_Fielders[g_Minigame.playerSlots.fielderIndex[b]].pos.z - lbl_3_data_21A48.z;
    aAngle = atan2(g_Fielders[g_Minigame.playerSlots.fielderIndex[a]].pos.z - lbl_3_data_21A48.z,
                   g_Fielders[g_Minigame.playerSlots.fielderIndex[a]].pos.x - lbl_3_data_21A48.x);
    bAngle = radToShortAngle(atan2(bZ, bX));
    return angleDifferenceNormalized(radToShortAngle(aAngle), bAngle) >= 0;
}

// .text:0x0013334C size:0x1170 mapped:0x807723E0
void fn_3_13334C(void) {
    SDCoinEntry* list;
    SDCoinEntry* entry;
    InMemFielder* fielder;
    InMemFielder* holder;
    InputStruct* input;
    FielderDash* dash = (FielderDash*)&g_FieldingLogic;
    SDAI* ai = SD.ai;
    VecXYZ* c = &lbl_3_data_21A48;
    int count;
    int quadStar;
    int quadBurst;
    int quadPowerup;
    int quadrant;
    int targetQuadrant;
    f32 targetX;
    f32 targetZ;
    f32 rx;
    f32 rz;
    f32 lx;
    f32 lz;
    f32 dxh;
    f32 dzh;
    f32 radius;
    s16 angle;
    s16 candidate;
    s16 side;
    s16 away;
    s16 tangent;
    s16 half;
    u8 strength;
    s8 p;
    s8 i;
    s8 character;
    s8 k;

    list = _OSAllocFromHeap(4, 1000);
    fn_3_133320();
    SD.rotSin = sin(-fn_3_9FDD8(SD.pathAngle[0]));
    SD.rotCos = cos(-fn_3_9FDD8(SD.pathAngle[0]));
    if (SD.x_72A != 0) {
        fn_3_135600(SD.starPos.x, SD.starPos.z, &rx, &rz);
        quadStar = fn_3_13564C(rx, rz);
    } else {
        quadStar = 4;
    }
    if (SD.burst.active != 0) {
        fn_3_135600(SD.burst.pos.x, SD.burst.pos.z, &rx, &rz);
        quadBurst = fn_3_13564C(rx, rz);
    } else {
        quadBurst = 4;
    }
    if (g_Minigame.powerup.activeInd == 1) {
        fn_3_135600(g_Minigame.powerup.pos.x, g_Minigame.powerup.pos.z, &rx, &rz);
        quadPowerup = fn_3_13564C(rx, rz);
    } else {
        quadPowerup = 4;
    }
    count = 0;
    entry = list;
    for (i = 0; i < 100; i++) {
        if (g_Minigame.coinState[i] == 1) {
            entry->coin = i;
            fn_3_135600(g_Minigame.coinPos[i].x, g_Minigame.coinPos[i].z, &entry->x, &entry->z);
            entry->quadrant = fn_3_13564C(entry->x, entry->z);
            entry++;
            count++;
        }
    }
    for (p = 0; p < 4; p++, dash++, ai++) {
        character = g_Minigame.playerSlots.characterIndex[p];
        if (character < 0 || character >= 4 || !g_Minigame.playerSlots.aiControlledInd[p]) {
            continue;
        }
        g_Minigame._1DC8[character] = 1;
        input = &g_Minigame._1D7C[character];
        memset(input, 0, sizeof(InputStruct));
        input->controlStickAngle = -1;
        fielder = &g_Fielders[g_Minigame.playerSlots.fielderIndex[p]];
        strength = g_Minigame.playerSlots.aiStrength[p];
        fn_3_135600(fielder->pos.x, fielder->pos.z, &rx, &rz);
        quadrant = fn_3_13564C(rx, rz);
        switch (ai->state) {
        case 0:
            if (drawStadiumRelated != 0 && dash->sprintSpeedMultiplier <= lbl_3_data_21B28[strength]) {
                if (SD.phase == 0 || p == SD.holder || fn_3_135520(rx, rz, 5.0f) == 0) {
                    input->newButtonInput |= INPUT_BUTTON_B;
                    input->buttonInput = input->newButtonInput;
                }
            }
            targetQuadrant = 4;
            if (p == SD.holder) {
                fn_3_134658(p, &targetX, &targetZ, &targetQuadrant);
            }
            if (targetQuadrant == 4 && SD.x_72A != 0) {
                targetX = SD.starPos.x;
                targetZ = SD.starPos.z;
                targetQuadrant = quadStar;
            }
            if (targetQuadrant == 4 && SD.burst.active != 0) {
                if (sdDistSqXZ(fielder->pos.x, fielder->pos.z, SD.burst.pos.x, SD.burst.pos.z) <=
                    SQ(lbl_3_data_21B78[strength])) {
                    for (k = 0; k < lbl_3_data_21A88[g_Minigame.soloMinigameDifficulty]; k++) {
                        if (SD.item[k].state >= 1 && SD.item[k].state <= 3 &&
                            fn_3_1354BC(k, SD.burst.pos.x, SD.burst.pos.z)) {
                            break;
                        }
                    }
                    if (k >= lbl_3_data_21A88[g_Minigame.soloMinigameDifficulty]) {
                        targetX = SD.burst.pos.x;
                        targetZ = SD.burst.pos.z;
                        targetQuadrant = quadBurst;
                    }
                }
            }
            if (targetQuadrant == 4 && g_Minigame.powerup.activeInd == 1) {
                if (sdDistSqXZ(fielder->pos.x, fielder->pos.z, g_Minigame.powerup.pos.x,
                               g_Minigame.powerup.pos.z) <= SQ(lbl_3_data_21B68[strength])) {
                    for (k = 0; k < lbl_3_data_21A88[g_Minigame.soloMinigameDifficulty]; k++) {
                        if (SD.item[k].state >= 1 && SD.item[k].state <= 3 &&
                            fn_3_1354BC(k, g_Minigame.powerup.pos.x, g_Minigame.powerup.pos.z)) {
                            break;
                        }
                    }
                    if (k >= lbl_3_data_21A88[g_Minigame.soloMinigameDifficulty]) {
                        targetX = g_Minigame.powerup.pos.x;
                        targetZ = g_Minigame.powerup.pos.z;
                        targetQuadrant = quadPowerup;
                    }
                }
            }
            if (targetQuadrant == 4 && g_Minigame.minigameFramesRemaining != 0) {
                entry = fn_3_1350BC(p, quadrant, count, list);
                if (entry != NULL && entry->valid != 0) {
                    targetX = g_Minigame.coinPos[entry->coin].x;
                    targetZ = g_Minigame.coinPos[entry->coin].z;
                    targetQuadrant = entry->quadrant;
                }
            }
            if (targetQuadrant != 4) {
                if (fn_3_134C80(p, quadrant, targetQuadrant, targetX, targetZ)) {
                    targetQuadrant = fn_3_13493C(p, &targetX, &targetZ, 2);
                }
                angle = radToShortAngle(atan2(targetZ - fielder->pos.z, targetX - fielder->pos.x));
                input->controlStickAngle = fn_3_1345AC(ai->angle, angle, strength);
            }
            if (SD.holder >= 0 && p != SD.holder) {
                holder = &g_Fielders[g_Minigame.playerSlots.fielderIndex[SD.holder]];
                fielder = &g_Fielders[g_Minigame.playerSlots.fielderIndex[p]];
                dzh = fielder->pos.z - holder->pos.z;
                dxh = fielder->pos.x - holder->pos.x;
                if (dxh * dxh + dzh * dzh <= SQ(lbl_3_data_21B38[strength])) {
                    lx = fielder->pos.x - c->x;
                    lz = fielder->pos.z - c->z;
                    side = angleDifferenceNormalized(radToShortAngle(atan2(holder->pos.z - c->z, holder->pos.x - c->x)),
                                                     radToShortAngle(atan2(lz, lx))) >= 0 ? 0 : 0x800;
                    away = radToShortAngle(atan2(dzh, dxh));
                    tangent = radToShortAngle(atan2(-(fielder->pos.x - c->x), fielder->pos.z - c->z));
                    half = angleDifferenceNormalized(normalizeAngle(tangent + side), away) / 2;
                    input->controlStickAngle = normalizeAngle(radToShortAngle(atan2(dzh, dxh)) + half);
                }
            }
            if (p != SD.holder) {
                for (k = 0; k < lbl_3_data_21A88[g_Minigame.soloMinigameDifficulty]; k++) {
                    if (SD.item[k].state >= 1 && SD.item[k].state <= 3 &&
                        sdDistSqXZ(fielder->pos.x, fielder->pos.z, SD.item[k].pos.x, SD.item[k].pos.z) <=
                            SQ(lbl_3_data_21B48[strength])) {
                        away = radToShortAngle(atan2(fielder->pos.z - SD.item[k].pos.z, fielder->pos.x - SD.item[k].pos.x));
                        candidate = normalizeAngle(input->controlStickAngle +
                                                   angleDifferenceNormalized(away, input->controlStickAngle) / 2);
                        input->controlStickAngle = fn_3_1345AC(input->controlStickAngle, candidate, strength);
                    }
                }
            }
            if (g_Minigame.powerup.activeInd == 2 &&
                sdDistSqXZ(fielder->pos.x, fielder->pos.z, g_Minigame.powerup.pos.x, g_Minigame.powerup.pos.z) <=
                    SQ(lbl_3_data_21B58[strength])) {
                away = radToShortAngle(atan2(fielder->pos.z - g_Minigame.powerup.pos.z,
                                             fielder->pos.x - g_Minigame.powerup.pos.x));
                candidate = normalizeAngle(input->controlStickAngle +
                                           angleDifferenceNormalized(away, input->controlStickAngle) / 2);
                input->controlStickAngle = fn_3_1345AC(input->controlStickAngle, candidate, strength);
            }
            if (SD.phase != 0 && p != SD.holder) {
                radius = ai->_0 + 0.20943952f * dolsqrtf2(rz * rz + rx * rx);
                if (fn_3_135520(rx, rz, radius) == 1) {
                    ai->_0 = RandomInt_Game(100) < lbl_3_data_21B88[strength] ? 3.0f : 1.5f;
                    input->controlStickAngle = normalizeAngle(radToShortAngle(
                        atan2(-(fielder->pos.x - c->x), fielder->pos.z - c->z)));
                    ai->state = 1;
                }
            }
            break;
        case 1:
            ai->counter = 1;
            ai->state = 2;
        case 2:
            input->controlStickAngle = normalizeAngle(radToShortAngle(
                atan2(-(fielder->pos.x - c->x), fielder->pos.z - c->z)));
            if (ai->counter-- <= 0) {
                input->buttonInput |= INPUT_BUTTON_A;
                input->newButtonInput |= INPUT_BUTTON_A;
                ai->state = 3;
            }
            break;
        case 3:
            if (fielder->isJump == 0) {
                ai->state = 0;
            }
            break;
        }
        ai->angle = input->controlStickAngle;
    }
    fn_800ACFB0(list);
}

// .text:0x00133320 size:0x2C mapped:0x807723B4
void fn_3_133320(void) {
    s8 i = 0;

    do {
        g_Minigame._1DC8[i] = 0;
    } while (++i < 4);
}

// .text:0x00133200 size:0x120 mapped:0x80772294
void fn_3_133200(void) {
    u32 i;
    u32 j;
    u32 offset;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            offset = fn_800247E4(j, i, 4, 4);
            if (offset < 32) {
                lbl_3_bss_B740[offset + 2] = 0xFF;
                lbl_3_bss_B740[offset] = 0xFF;
                lbl_3_bss_B740[offset + 3] = 0x96;
                lbl_3_bss_B740[offset + 1] = 0x96;
            } else {
                lbl_3_bss_B740[offset + 2] = 0x96;
                lbl_3_bss_B740[offset] = 0x96;
                lbl_3_bss_B740[offset + 3] = 0x96;
                lbl_3_bss_B740[offset + 1] = 0x96;
            }
        }
    }
    GXInitTexObj(&lbl_3_bss_B708, lbl_3_bss_B740, 4, 4, GX_TF_RGBA8, GX_REPEAT, GX_REPEAT, GX_DISABLE);
    GXInitTexObjLOD(&lbl_3_bss_B708, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_DISABLE, GX_DISABLE, GX_ANISO_1);
    lbl_3_bss_B704 = 0;
    lbl_3_data_26580 = -1;
}

// .text:0x001330E4 size:0x11C mapped:0x80772178
void fn_3_1330E4(void) {
    sdUpdatePulseTexture();
}

// .text:0x00132EDC size:0x208 mapped:0x80771F70
void fn_3_132EDC(void* model, GXTevStageID* stage, GXTexCoordID* coord, GXTexMapID* map, s8* nStages, s8* nCoords) {
    sdUpdatePulseTexture();
    GXLoadTexObj(&lbl_3_bss_B708, *map);
    GXSetTexCoordGen2(*coord, GX_TG_MTX3X4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(*stage, *coord, *map, GX_COLOR_NULL);
    GXSetTevColorIn(*stage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_TEXA, GX_CC_CPREV);
    GXSetTevColorOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE, GX_TEVPREV);
    GXSetTevAlphaIn(*stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    GXSetTevAlphaOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE, GX_TEVPREV);
    (*stage)++;
    (*coord)++;
    (*map)++;
    (*nStages)++;
    (*nCoords)++;
}
