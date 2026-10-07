#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_piranhaPanic
#define g_Minigame g_Minigame_shared
#include "game/minigame/piranha_panic.h"
#include "game/minigame/pitching_machine.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/math/game_math.h"
#include "game/sound/m_sound.h"
#include "game/match_setup/scene_skip.h"
#include "game/match_setup/match_flow.h"
#include "game/match_setup/roster_init.h"
#include "game/match_setup/match_loading.h"
#include "game/fielding/fielder.h"
#include "Unknown/File_0x8003452c.h"
#include "Unknown/File_0x80034220.h"
#include "Unknown/File_0x800348c8.h"
#include "musyx/musyx.h"
#include "game/minigame/toy_field.h"
#include "Dolphin/gx.h"
#include "Dolphin/mtx.h"
#include "Dolphin/vec.h"
#include "Dolphin/os.h"
#include "Dolphin/stl.h"
#include "stl/stdlib.h"
#include "stl/math.h"
#include "Unknown/File_0x800204cc.h"
#include "Unknown/sub.h"
#undef g_Minigame

extern u8 lbl_80366158[0x30];
#define PauseSimulation lbl_80366158[0x28]

f32 lbl_3_data_26698[3] = { 0.5f, 0.0f, -0.5f };
s8 lbl_3_data_266A4 = -1;
extern s16 lbl_3_data_21E68[26];
extern f32 lbl_3_data_21E24[17];
extern f32 lbl_3_data_21D1C[4];
extern f32 lbl_3_data_21D2C[2];
extern VecXYZ lbl_3_data_21B94[4];
extern s16 lbl_3_data_21DC4[2];
extern s16 lbl_3_data_21E04[2];
extern u8 lbl_3_data_21E10[8];
extern s16 lbl_3_data_21EAC[4][2];
extern u8 lbl_3_data_21E9C[4][4];
extern s8 lbl_3_data_21EBC[4];
extern s8 lbl_3_data_21EC0[4];
extern u8 lbl_3_data_21E1C[2];
extern s16 lbl_3_data_21DC8[5][6];

extern s16 barrelCollisionHitboxes[];
extern VecXYZ lbl_3_data_21BC4[][4];
extern f32 fielderHitboxesForGarlicKnockout[];

extern u8 lbl_800EFBA4[0x10];
extern u16 lbl_3_data_81FC[0x30];
extern u8 lbl_3_data_21278[2];
extern u8 lbl_3_data_2127C[8][5];
extern u8 lbl_3_data_21E08[8];
extern BOOL checkForPauses(void);
extern void fn_3_10F550(int a, int b);
extern void fn_3_157570(void);
extern void fn_3_157588(int arg);
extern void fn_3_154214(void);
extern void fn_800B993C(void);
extern void fn_800B9948(void* callback);
extern void fn_3_15730C(int index, f32 x, f32 y, f32 z);
extern void fn_3_1573AC(int arg);
extern void fn_3_147CFC(VecXYZ* pos);
extern void fn_3_154238(s16 index);
extern void fn_80062BE4(Vec* pos);
extern void starMissionsMinigamesSpecialAction(int missionType, int points, int barrelsHit);
extern s16 lbl_3_common_bss_37400[0x27];
extern u8 hugeAnimStruct[0x3154];
extern VecXYZ lbl_3_data_21D34[4][3];
extern u8 lbl_3_data_21E20[3];
extern u8 lbl_3_data_21E18[4];

#define SATURATING_INCREMENT(counter) \
    if ((counter) < 0x7FFE) {         \
        (counter)++;                  \
    } else {                          \
        (counter) = 0x7FFF;           \
    }


static u8 lbl_3_bss_B840[0x10];
static u8 lbl_3_bss_B800[4 * 4 * 4] ATTRIBUTE_ALIGN(32);
static u32 lbl_3_bss_B7E4;
static GXTexObj lbl_3_bss_B7C4;
static u8 lbl_3_bss_B7C1;
static u8 lbl_3_bss_B7C0;


typedef union _PPMinigame {
    MiniGameStruct;
    PPState;
} PPMinigame;

extern PPMinigame g_Minigame;

#define PP g_Minigame

/* minigamePlayerSelectedOrder is -1 when no player is selected; it is written
 * through a signed-byte lvalue (the shared header still declares it u8). */
#define MINIGAME_SELECTED_ORDER (*(s8*)&g_Minigame.minigamePlayerSelectedOrder)
#define PP_BALL_POS(i) (PP.ballPos[i])
#define PP_BALL_VEL(i) (PP.ballVel[i])
#define PP_SPAWNER(i) (&PP.spawner[i])
#define PP_OBJECT(i) (&PP.object[i])

static inline void ppStopSpawnerWaits(void) {
    int i;

    if (PP.x_1CA2 == 2) {
        for (i = 0; i < PP_SPAWNER_COUNT; i++) {
            if (PP_SPAWNER(i)->mode == 2) {
                PP_SPAWNER(i)->mode = 3;
                PP_SPAWNER(i)->_1A = 0;
            }
        }
    }
}

static inline void ppInitPulseTexture(void) {
    u32 offset;
    u32 i;
    u32 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            offset = pP_TiledTexelIndex(j, i, 4) * 4;
            if (offset < 32) {
                lbl_3_bss_B800[offset + 2] = 0xFF;
                lbl_3_bss_B800[offset] = 0xFF;
                lbl_3_bss_B800[offset + 3] = 0x96;
                lbl_3_bss_B800[offset + 1] = 0x96;
            } else {
                lbl_3_bss_B800[offset + 2] = 0;
                lbl_3_bss_B800[offset] = 0;
                lbl_3_bss_B800[offset + 3] = 0;
                lbl_3_bss_B800[offset + 1] = 0;
            }
        }
    }
    GXInitTexObj(&lbl_3_bss_B7C4, lbl_3_bss_B800, 4, 4, GX_TF_RGBA8, GX_REPEAT, GX_REPEAT, GX_DISABLE);
    GXInitTexObjLOD(&lbl_3_bss_B7C4, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_DISABLE, GX_DISABLE, GX_ANISO_1);
    lbl_3_data_266A4 = -1;
    lbl_3_bss_B7E4 = 0;
    lbl_3_bss_B7C1 = 0;
}

// .text:0x001471C4 size:0x194 mapped:0x80786258
void piranhaPanicSwitcher(void) {
    switch (g_GameLogic.gameStatus) {
        case GAME_STATUS_LOAD_GAME:
            pP_LoadGame();
            break;
        case GAME_STATUS_TRANSITION_MINIGAME_TO_BATTING:
            pP_RoundIntro();
            break;
        case GAME_STATUS_DEFAULT:
            pP_StartPlay();
            break;
        case GAME_STATUS_LIVE_BALL:
            piranhaPanicLiveBall();
            break;
    }
}

// .text:0x001471C0 size:0x4 mapped:0x80786254
void fn_3_1471C0(void) {
}

// .text:0x00146A90 size:0x730 mapped:0x80785B24
void pP_LoadGame(void) {
    s32 i;
    s32 j;
    s32 p;
    s32 k;

    if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_0) {
        initializeSomethingDuringTransition();
        g_GameLogic.secondaryGameMode = SECONDARY_GAME_MODE_PIRANHA_PANIC;
        g_Minigame.minigameElapsedFrames = 0;
        g_Minigame.turnOverStatus = 0;
        g_Minigame._1A37 = 0;
        for (i = 0; i < PP_PLAYER_COUNT; i++) {
            PP.pointsA[i] = 0;
            PP.pointsB[i] = 0;
            PP.pointsLatest[i][0] = 0;
            PP.pointsLatest[i][1] = 0;
            PP._18F4[i] = -1;
            PP.fielderIndex[i] = -1;
            PP.x_18FC[i] = -1;
            PP.x_1900[i] = -1;
            PP._18F0[i] = 0;
        }
        g_Scores.Inning = 0;
        g_Minigame.pointsReqToWin_challenge = 0;
        g_Minigame.turnNumberWithinRound = 0;
        MINIGAME_SELECTED_ORDER = -1;
        g_Minigame.rosterID = -1;
        g_Minigame.minigameElapsedFrames = 0;
        if (g_Minigame.multiPlayerInd == 0) {
            u8 value;
            g_Minigame.minigameFramesRemaining = lbl_3_data_21E08[g_Minigame.soloMinigameDifficulty] * 60;
            value = lbl_3_data_2127C[g_Minigame.GameMode_MiniGame][g_Minigame.soloMinigameDifficulty];
            PP.aiStrength[0] = value;
            PP.aiStrength[1] = value;
            PP.aiStrength[2] = value;
            PP.aiStrength[3] = value;
        } else {
            if (g_Minigame._1A3C != 0) {
                u8 value = lbl_3_data_2127C[7][0];
                PP.aiStrength[0] = value;
                PP.aiStrength[1] = value;
                PP.aiStrength[2] = value;
                PP.aiStrength[3] = value;
            }
            g_Minigame.minigameFramesRemaining = lbl_3_data_21E08[4] * 60;
        }
        pPRelated();
        setDefaultInMemFielder();
        for (i = 0, p = 0; i < PP_PLAYER_COUNT; i++) {
            InMemFielder* fielder;
            if (PP.character[i] < 0) {
                continue;
            }
            PP._18F4[p] = i;
            PP.fielderIndex[PP._18F4[p]] = p + 2;
            setFielderValues(i, PP.fielderIndex[PP._18F4[p]]);
            fielder = &g_Fielders[PP.fielderIndex[PP._18F4[p]]];
            fielder->_020D = i;
            fielder->pos.x = lbl_3_data_21B94[p].x;
            fielder->pos.y = lbl_3_data_21B94[p].y;
            fielder->pos.z = lbl_3_data_21B94[p].z;
            PP.heldBalls[i][0] = -1;
            PP.heldBalls[i][1] = -1;
            PP.heldBalls[i][2] = -1;
            PP.spawnCount[i] = 0;
            fielder->actionYOffset = lbl_3_data_21D2C[1];
            PP.swingFrames[i] = -1;
            PP.throwDirection[i] = -1;
            PP.hitState[i] = 0;
            PP.hitCount[i] = 0;
            PP.scoreEntryCount[i] = 0;
            fielder->lockoutDuration = 0;
            PP.playerState[i] = 0;
            fielder->currentVelocity = 0.0f;
            PP.goalIndex[i] = i;
            fielder->desiredMovementDirection = 1.5707964f;
            PP.x_1CB1[i] = 0;
            for (k = 0; k < PP_SCORE_ENTRY_COUNT; k++) {
                PP.scoreEntries[i][k] = 0;
            }
            PP.targeted[i] = 0;
            p++;
        }
        for (j = 0; j < 100; j++) {
            PP.ballState[j] = 0;
            PP.ballOwner[j] = -1;
        }
        g_Minigame._1B4C = 60;
        pP_RefillHeldBalls();
        for (k = 0; k < PP_SPAWNER_COUNT; k++) {
            PPSpawner* sp = PP_SPAWNER(k);
            sp->mode = 0;
            sp->isBig = 0;
            sp->_2E = 0;
            sp->_1A = 0;
            sp->_1C = -1;
            sp->_1E = 0;
            sp->_20 = 0;
            sp->_22 = 0;
            sp->_33 = 0xFF;
            sp->pos.x = lbl_3_data_21BC4[k][0].x;
            sp->pos.y = lbl_3_data_21BC4[k][0].y;
            sp->pos.z = lbl_3_data_21BC4[k][0].z;
            sp->queue[0] = -1;
            sp->queue[1] = -1;
            sp->queue[2] = -1;
            sp->queue[3] = -1;
        }
        PP.holeUsed[0] = 0;
        PP.holeUsed[1] = 0;
        PP.holeUsed[2] = 0;
        PP.holeUsed[3] = 0;
        PP.x_1CA2 = 0;
        PP.x_1CA3 = 0;
        PP.x_1CA4 = 0;
        if (g_Minigame.multiPlayerInd == 0) {
            g_Minigame._1B4E = RandomInt_Game_Range(lbl_3_data_21DC8[g_Minigame.soloMinigameDifficulty][0], lbl_3_data_21DC8[g_Minigame.soloMinigameDifficulty][1]) * 60;
        } else {
            g_Minigame._1B4E = RandomInt_Game_Range(lbl_3_data_21DC8[4][0], lbl_3_data_21DC8[4][1]) * 60;
        }
        minigamesSetSomePointers();
        minigamesGXStuff();
        minigamesSetSomePointers2();
        for (j = 0; j < PP_OBJECT_COUNT; j++) {
            PP_OBJECT(j)->state = 0;
        }
        fn_3_157588(0x28);
        g_GameLogic._125++;
    } else {
        SetGameStatus(GAME_STATUS_GAME_START_MOVIE);
    }
    ppInitPulseTexture();
}

// .text:0x001469CC size:0xC4 mapped:0x80785A60
void pP_RoundIntro(void) {
    switch (g_GameLogic._125) {
        case TRANSITION_CALCULATION_TYPE_0:
            fn_3_10F550(2, lbl_3_data_21278[0]);
            changeScene(1, 6);
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_1;
            break;
        case TRANSITION_CALCULATION_TYPE_1:
            if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > lbl_3_data_21278[0] + lbl_3_data_21278[1]) {
                g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_2;
            }
            break;
        case TRANSITION_CALCULATION_TYPE_2:
            SetGameStatus(GAME_STATUS_DEFAULT);
            break;
    }
}

// .text:0x00146928 size:0xA4 mapped:0x807859BC
void pP_StartPlay(void) {
    pP_InitAI();
    changeScene(1, 6);
    SetGameStatus(GAME_STATUS_LIVE_BALL);
}

// .text:0x00146408 size:0x520 mapped:0x8078549C
void piranhaPanicLiveBall(void) {
    if (checkForPauses()) {
        return;
    }
    if (g_Minigame.turnOverStatus == 0) {
        PP.frameCount++;
    }
    if (PP.framesRemaining != 0) {
        PP.framesRemaining--;
        if (PP.framesRemaining < 600 && PP.framesRemaining != 0 && PP.framesRemaining % 60 == 0) {
            callSfx(lbl_3_data_81FC[0x28]);
        }
    }
    pP_UpdateBalls();
    pP_UpdatePiranhas();
    pP_UpdateProjectiles();
    pP_UpdateAI();
    pP_UpdatePlayers();
    pP_TallyScores();
    pP_UpdateTimeUp();
}

// .text:0x001461A4 size:0x264 mapped:0x80785238
void pP_UpdateTimeUp(void) {
    if (g_Minigame.turnOverStatus == 0) {
        if (PP.framesRemaining == 0) {
            g_Minigame.turnOverStatus = 1;
            fn_3_10F550(3, 0);
            sndFXStartEx(0x1BE, lbl_800EFBA4[7], 0x3F, 0);
        }
    } else {
        if (g_Minigame.turnOverStatus == 1) {
            g_Minigame.turnOverStatus = 2;
            g_GameLogic.CountdownUntilFade = lbl_3_data_21E68[17];
        }
        g_GameLogic.CountdownUntilFade--;
        if (g_GameLogic.CountdownUntilFade == 7) {
            changeScene(3, 6);
        }
        if (g_GameLogic.CountdownUntilFade <= 0) {
            pP_Postgame();
        }
    }
}

// .text:0x00145FF4 size:0x1B0 mapped:0x80785088
void pP_Postgame(void) {
    u32 i;

    fn_3_157570();
    minigameCalculateRankings();
    if (g_Minigame.soloMinigameDifficulty <= MINIGAME_DIFFICULTY_MULTIPLAYER_CHALLENGE_HARD && g_Minigame.multiPlayerInd == 0) {
        if (PP._18E8[(s8)g_Minigame._1908] == 1 && g_Minigame.challenge_minigame_haven_tWonYetIndicator == 0) {
            g_Minigame._1A37 = 1;
        } else {
            g_Minigame._1A37 = 2;
        }
    }
    SetGameStatus(GAME_STATUS_MVP_END_GAME);
    for (i = 0; i < PP_BALL_COUNT; i++) {
        PP.ballState[i] = 0;
        PP.ballOwner[i] = -1;
    }
    g_Minigame._1B4C = 60;
    for (i = 0; i < PP_SPAWNER_COUNT; i++) {
        pP_UpdateHiddenPiranha(i);
        PP_SPAWNER(i)->mode = 2;
        PP_SPAWNER(i)->_1C = 1;
        PP_SPAWNER(i)->isBig = 0;
    }
    fn_3_154214();
}

// .text:0x00145EB8 size:0x13C mapped:0x80784F4C
void pP_UpdateBalls(void) {
    int i;

    pP_RefillHeldBalls();
    for (i = 0; i < PP_BALL_COUNT; i++) {
        u8 state = PP.ballState[i];
        if (state == 5 || state == 6) {
            pP_UpdateThrownBall(i);
        } else if (state == 2) {
            pP_SetHeldBallPos(i);
        }
    }
}

// .text:0x00145B98 size:0x320 mapped:0x80784C2C
void pP_RefillHeldBalls(void) {
    int i;
    int j;

    if (g_Minigame.turnOverStatus != 0) {
        return;
    }
    for (i = 0; i < PP_PLAYER_COUNT; i++) {
        if ((s8)PP.character[i] < 0) {
            continue;
        }
        if (PP.heldBalls[i][2] < 0) {
            int k;
            for (k = 0; k < PP_HELD_BALL_COUNT; k++) {
                for (j = 0; j < PP_BALL_COUNT; j++) {
                    if (PP.ballState[j] == 0) {
                        PP.heldBalls[i][k] = j;
                        PP.ballOwner[j] = i;
                        PP.ballState[j] = 2;
                        PP.ballFrames[j] = 0;
                        PP.ballKind[j] = RandomInt_Game(4);
                        PP.x_1C1A[j] = 0;
                        PP.x_1C4C[j] = 0;
                        PP.spawnCount[i]++;
                        pP_SetHeldBallPos(j);
                        break;
                    }
                }
            }
        } else if (PP.heldBalls[i][0] < 0) {
            PP.heldBalls[i][0] = PP.heldBalls[i][1];
            PP.heldBalls[i][1] = PP.heldBalls[i][2];
            for (j = 0; j < PP_BALL_COUNT; j++) {
                if (PP.ballState[j] == 0) {
                    PP.heldBalls[i][2] = j;
                    PP.ballOwner[j] = i;
                    PP.ballState[j] = 2;
                    PP.ballFrames[j] = 0;
                    PP.x_1C1A[j] = 0;
                    PP.x_1C4C[j] = 0;
                    PP.spawnCount[i]++;
                    if (PP.spawnCount[i] <= lbl_3_data_21E68[1]) {
                        int open[4];
                        int unusedIdx[4] = {0, 1, 2, 3};
                        int* openEnd = open;
                        int openCount = 0;
                        int q;
                        for (q = 0; q < 4; q++) {
                            if (PP.holeUsed[q] == 1) {
                                *openEnd++ = q;
                                openCount++;
                            }
                        }
                        if (openCount == 0) {
                            PP.ballKind[j] = RandomInt_Game(4);
                        } else {
                            PP.ballKind[j] = open[RandomInt_Game(openCount)];
                        }
                    } else {
                        PP.ballKind[j] = 5;
                        PP.spawnCount[i] = 0;
                    }
                    break;
                }
            }
        }
    }
}

// .text:0x00145AD0 size:0xC8 mapped:0x80784B64
void pP_SetHeldBallPos(int p) {
    int owner = PP.ballOwner[p];
    int k;

    for (k = 0; k < PP_HELD_BALL_COUNT; k++) {
        if (PP.heldBalls[owner][k] == p) {
            break;
        }
    }
    PP_BALL_POS(p).x = lbl_3_data_21D34[PP.goalIndex[owner]][k].x;
    PP_BALL_POS(p).y = lbl_3_data_21D34[PP.goalIndex[owner]][k].y;
    PP_BALL_POS(p).z = lbl_3_data_21D34[PP.goalIndex[owner]][k].z;
}

// .text:0x001453BC size:0x714 mapped:0x80784450
void pP_UpdateThrownBall(int p) {
    int player = PP.ballOwner[p];

    SATURATING_INCREMENT(PP.ballFrames[p]);
    if (PP.ballState[p] == 6) {
        PP_BALL_VEL(p).y += lbl_3_data_21E24[11];
        if (PP.ballKind[p] != 5) {
            PP_BALL_VEL(p).x *= lbl_3_data_21E24[12];
            PP_BALL_VEL(p).z *= lbl_3_data_21E24[12];
        } else if (PP.ballFrames[p] >= lbl_3_data_21E68[23]) {
            s8 owner = -1 - PP.ballTarget[p];
            fn_3_147CFC(&PP_BALL_POS(p));
            callSfx(0x309);
            fn_3_154238(p);
            if (PP.playerState[owner] == 0 && PP.hitState[owner] == 0) {
                InMemFielder* fielder = &g_Fielders[(s8)PP.fielderIndex[owner]];
                Vec dir;
                Vec unusedDir = {0.0f, 0.0f, -1.0f};
                PP.hitState[owner] = 1;
                PP.stateFrames[owner] = lbl_3_data_21E68[14];
                PP.hitCount[owner] = 0;
                dir.x = dir.y = 0.0f;
                dir.z = -1.0f;
                PSVECNormalize(&dir, &dir);
                fielder->xMovementDir = dir.x;
                PP.x_1DF4[owner] = 1;
                fielder->zMovementDir = dir.z;
                fielder->currentVelocity = lbl_3_data_21E24[15];
                setCharacterAnimations((s8)PP.character[owner], 2);
                if (PP.x_1CB1[owner] < 0xFFFE) {
                    PP.x_1CB1[owner]++;
                } else {
                    PP.x_1CB1[owner] = 0xFF;
                }
            }
            PP.ballState[p] = 0;
            PP.ballFrames[p] = 0;
            return;
        }
    }
    PP_BALL_POS(p).x += PP_BALL_VEL(p).x;
    PP_BALL_POS(p).y += PP_BALL_VEL(p).y;
    PP_BALL_POS(p).z += PP_BALL_VEL(p).z;
    if (PP_BALL_POS(p).y < 0.0f) {
        PP.ballState[p] = 0;
        PP.ballFrames[p] = 0;
        if (PP.ballKind[p] == 5) {
            fn_3_154238(p);
        }
        return;
    }
    {
        int owner = PP.ballTarget[p];
        PPSpawner* sp;
        if (owner >= 0) {
            f32 dist = dolsqrtf2(SQ(PP_BALL_POS(p).x - lbl_3_data_21BC4[owner][1].x) + SQ(PP_BALL_POS(p).z - lbl_3_data_21BC4[owner][1].z));
            sp = PP_SPAWNER(owner);
            if (sp->mode == 2 && dist < lbl_3_data_21E24[1]) {
                u8 kind = sp->kind;
                if (PP.ballKind[p] == kind || kind == 4 || PP.ballKind[p] == 5) {
                    s8 gain;
                    VecXYZ hitPos;
                    u8* scores;
                    int remaining;
                    gain = (PP.ballKind[p] == 5) ? lbl_3_data_21E68[24] : 1;
                    memcpy(&hitPos, &PP_BALL_POS(p), sizeof(VecXYZ));
                    hitPos.y *= -1.0f;
                    if (PP.ballKind[p] == 5) {
                        fn_3_147CFC(&hitPos);
                        fn_3_154238(p);
                    } else {
                        fn_80062BE4((Vec*)&hitPos);
                    }
                    if (PP.ballKind[p] == 5) {
                        callSfx(0x309);
                    } else {
                        callSfx(0x2DC);
                    }
                    remaining = sp->hitsLeft - gain;
                    if ((s16)remaining <= 0) {
                        sp->hitsLeft = 0;
                    } else {
                        sp->hitsLeft = remaining;
                    }
                    PP.hitCount[player]++;
                    scores = PP.scoreEntries[player];
                    scores[PP.scoreEntryCount[player]] = gain * lbl_3_data_21E18[sp->isBig * 2 + 1];
                    PP.scoreEntryCount[player]++;
                    sp->queue[0] = -1;
                    sp->queue[1] = -1;
                    sp->queue[2] = -1;
                    sp->queue[3] = -1;
                    sp->_2E = 0;
                    if (sp->hitsLeft == 0) {
                        scores[PP.scoreEntryCount[player]] = lbl_3_data_21E18[sp->isBig * 2];
                        PP.scoreEntryCount[player]++;
                        if (sp->kind == 4) {
                            PP.x_1CA3 = 0;
                            sp->_2E = 0;
                        } else if (PP.x_1CA2 != 0) {
                            PP.x_1CA2 = 2;
                        }
                        sp->_1C = lbl_3_data_21E68[8] - lbl_3_data_21E68[9];
                        sp->_1A = 0;
                        sp->mode = 4;
                        PP.holeUsed[sp->kind] = 0;
                        if (!g_d_GameSettings.exhibitionMatchInd && player == lbl_3_common_bss_37400[0x20]) {
                            starMissionsMinigamesSpecialAction(5, sp->kind, 0);
                        }
                    }
                    sp->_1E = 1;
                } else {
                    u8 queued = sp->_33;
                    if ((queued == 3 && sp->_2E == 0) || queued == 0) {
                        int k;
                        if (sp->_2E == 0) {
                            sp->_26 = 0;
                        }
                        for (k = 0; k < 4; k++) {
                            if (sp->queue[k] < 0) {
                                sp->queue[k] = PP.ballOwner[p];
                                sp->_2E = 1;
                                sp->_20 = 0;
                                break;
                            }
                        }
                        PP.hitCount[player] = 0;
                    }
                }
                PP.ballState[p] = 0;
                PP.ballFrames[p] = 0;
                return;
            }
        }
    }
    if (PP.ballFrames[p] > lbl_3_data_21E68[0]) {
        PP.ballState[p] = 0;
        PP.ballFrames[p] = 0;
        if (PP.ballKind[p] == 5) {
            fn_3_154238(p);
        }
    }
}

static inline void ppUpdateCrouch(int p) {
    InputStruct* input = &g_Controls[(s8)PP.character[p]];
    InMemFielder* fielder = &g_Fielders[PP.fielderIndex[p]];

    if (PP.aiControlled[p] != 0) {
        input = &g_Minigame._1D7C[(s8)PP.character[p]];
    }
    SATURATING_INCREMENT(PP.downFrames[p]);
    switch (PP.playerState[p]) {
        case 1:
            {
                f32 lo = lbl_3_data_21D2C[0];
                f32 hi = lbl_3_data_21D2C[1];
                f32 frames = (f32)PP.downFrames[p];
                fielder->actionYOffset = (lo - hi) * (frames / (f32)lbl_3_data_21E68[16]) + hi;
            }
            if (PP.downFrames[p] >= lbl_3_data_21E68[16]) {
                PP.playerState[p] = 2;
                PP.downFrames[p] = 0;
            }
            break;
        case 2:
            if (!(input->buttonInput & INPUT_BUTTON_DOWN)) {
                PP.playerState[p] = 3;
                PP.downFrames[p] = 0;
            }
            break;
        case 3:
            {
                f32 hi = lbl_3_data_21D2C[1];
                f32 lo = lbl_3_data_21D2C[0];
                f32 frames = (f32)PP.downFrames[p];
                fielder->actionYOffset = (hi - lo) * (frames / (f32)lbl_3_data_21E68[16]) + lo;
            }
            if (PP.downFrames[p] >= lbl_3_data_21E68[16]) {
                PP.playerState[p] = 0;
                PP.downFrames[p] = 0;
            }
            break;
    }
}

// .text:0x00144CB8 size:0x704 mapped:0x80783D4C
void pP_UpdatePlayers(void) {
    int i;

    for (i = 0; i < PP_PLAYER_COUNT; i++) {
        s8 fielderIndex = PP.fielderIndex[i];
        InMemFielder* fielder;
        InputStruct* input;
        u16 pressed;
        if (fielderIndex < 0) {
            continue;
        }
        fielder = &g_Fielders[PP.fielderIndex[i]];
        input = &g_Controls[(s8)PP.character[i]];
        if (PP.aiControlled[i] != 0) {
            input = &g_Minigame._1D7C[(s8)PP.character[i]];
        }
        if (PP.playerState[i] != 0) {
            ppUpdateCrouch(i);
        } else if (PP.hitState[i] == 1) {
            PP.stateFrames[i]--;
            if (PP.stateFrames[i] <= 0) {
                PP.hitState[i] = 2;
                PP.stateFrames[i] = lbl_3_data_21E68[15];
            } else {
                fielder->pos.x = fielder->xMovementDir * lbl_3_data_21E24[14] + fielder->pos.x;
                fielder->pos.y += fielder->currentVelocity;
                fielder->pos.z = fielder->zMovementDir * lbl_3_data_21E24[14] + fielder->pos.z;
                fielder->currentVelocity -= lbl_3_data_21E24[16];
            }
            fn_3_1573AC(*(int*)(hugeAnimStruct + 0x2C50 + i * 4));
        } else if (PP.hitState[i] == 2) {
            if (g_Minigame.turnOverStatus != 0) {
                continue;
            }
            PP.stateFrames[i]--;
            if (PP.stateFrames[i] <= 0) {
                fielder->pos.x = lbl_3_data_21B94[PP.goalIndex[i]].x;
                fielder->pos.y = lbl_3_data_21B94[PP.goalIndex[i]].y;
                fielder->pos.z = lbl_3_data_21B94[PP.goalIndex[i]].z;
                PP.hitState[i] = 0;
                PP.playerState[i] = 2;
                fielder->actionYOffset = lbl_3_data_21D2C[0];
            }
        } else if (PP.swingFrames[i] >= 0) {
            int swing;
            PP.swingFrames[i]++;
            swing = LERPToNewRange_Float(PP.hitCount[i], 0, lbl_3_data_21E68[19], lbl_3_data_21E68[2], lbl_3_data_21E68[3]);
            if (PP.swingFrames[i] == lbl_3_data_21E68[4]) {
                pP_ReleaseThrow(i);
                PP.heldBalls[i][0] = -1;
            } else if (PP.swingFrames[i] >= swing) {
                PP.swingFrames[i] = -1;
                PP.throwDirection[i] = -1;
            }
        } else {
            pressed = input->newButtonInput;
            if (pressed & INPUT_BUTTON_B) {
                if (g_Minigame.turnOverStatus != 0) {
                    continue;
                }
                PP.throwDirection[i] = 3;
            } else if (pressed & INPUT_BUTTON_A) {
                s16 angle;
                if (g_Minigame.turnOverStatus != 0) {
                    continue;
                }
                angle = input->controlStickAngle;
                if (angle >= 0xE00 || (input->buttonInput & INPUT_BUTTON_RIGHT)) {
                    PP.throwDirection[i] = 0;
                } else if (angle >= 0xA00) {
                    continue;
                } else if (angle >= 0x600 || (input->buttonInput & INPUT_BUTTON_LEFT)) {
                    PP.throwDirection[i] = 2;
                } else if (angle >= 0x200 || (input->buttonInput & INPUT_BUTTON_UP)) {
                    PP.throwDirection[i] = 1;
                } else if (angle < 0 && (input->buttonInput & INPUT_BUTTON_RIGHT) == 0) {
                    continue;
                } else {
                    PP.throwDirection[i] = 0;
                }
            } else {
                goto check_down;
            }
            {
                s8 target = PP.heldBalls[i][0];
                s8 choice;
                if (PP.ballKind[target] != 5 || PP.throwDirection[i] != 3) {
                    PP.ballTarget[target] = PP.throwDirection[i];
                    fielder->throwTarget.x = lbl_3_data_21BC4[PP.ballTarget[target]][1].x;
                    fielder->throwTarget.y = lbl_3_data_21BC4[PP.ballTarget[target]][1].y;
                    fielder->throwTarget.z = lbl_3_data_21BC4[PP.ballTarget[target]][1].z;
                } else {
                    s8 order[3];
                    s8* orderEnd = order;
                    int k;
                    int a;
                    int b;
                    u8* weight;
                    for (k = 0; k < 4; k++) {
                        if (k != i) {
                            *orderEnd++ = k;
                        }
                    }
                    for (a = 0; a < 2; a++) {
                        for (b = a + 1; b < 3; b++) {
                            if (PP.pointsA[order[a]] < PP.pointsA[order[b]]) {
                                s8 swap = order[a];
                                order[a] = order[b];
                                order[b] = swap;
                            }
                        }
                    }
                    choice = rand() % 100;
                    weight = lbl_3_data_21E20;
                    if ((choice -= *weight++) < 0) {
                        choice = order[0];
                    } else if ((choice -= *weight++) < 0) {
                        choice = order[1];
                    } else if ((choice -= *weight) < 0) {
                        choice = order[2];
                    }
                    PP.ballTarget[target] = -1 - choice;
                    fielder->throwTarget.x = lbl_3_data_21B94[choice].x + 1.5 * (s8)((choice - i) / __abs(choice - i));
                    fielder->throwTarget.y = 0.0f;
                    fielder->throwTarget.z = lbl_3_data_21B94[choice].z;
                }
                PP.throwBall[i] = PP.heldBalls[i][0];
                PP.ballState[target] = 3;
                PP.swingFrames[i] = 0;
                if (PP.throwDirection[i] == 3) {
                    PP.ballState[target] = 4;
                }
                fielder->desiredMovementDirection = game_atan2(fielder->throwTarget.x - fielder->pos.x, fielder->throwTarget.z - fielder->pos.z);
            }
            continue;
        check_down:
            if (input->buttonInput & INPUT_BUTTON_DOWN) {
                PP.playerState[i] = 1;
                PP.downFrames[i] = 0;
                callSfx(0x2DB);
            }
        }
    }
}

// .text:0x00144ADC size:0x1DC mapped:0x80783B70
void pP_UpdateCrouch(int p) {
    InputStruct* input = &g_Controls[(s8)PP.character[p]];
    InMemFielder* fielder = &g_Fielders[PP.fielderIndex[p]];

    if (PP.aiControlled[p] != 0) {
        input = &g_Minigame._1D7C[(s8)PP.character[p]];
    }
    SATURATING_INCREMENT(PP.downFrames[p]);
    switch (PP.playerState[p]) {
        case 1:
            {
                f32 ratio = (f32)PP.downFrames[p] / (f32)lbl_3_data_21E68[16];
                fielder->actionYOffset = (lbl_3_data_21D2C[0] - lbl_3_data_21D2C[1]) * ratio + lbl_3_data_21D2C[1];
            }
            if (PP.downFrames[p] >= lbl_3_data_21E68[16]) {
                PP.playerState[p] = 2;
                PP.downFrames[p] = 0;
            }
            break;
        case 2:
            if (!(input->buttonInput & INPUT_BUTTON_DOWN)) {
                PP.playerState[p] = 3;
                PP.downFrames[p] = 0;
            }
            break;
        case 3:
            {
                f32 ratio = (f32)PP.downFrames[p] / (f32)lbl_3_data_21E68[16];
                fielder->actionYOffset = (lbl_3_data_21D2C[1] - lbl_3_data_21D2C[0]) * ratio + lbl_3_data_21D2C[0];
            }
            if (PP.downFrames[p] >= lbl_3_data_21E68[16]) {
                PP.playerState[p] = 0;
                PP.downFrames[p] = 0;
            }
            break;
    }
}

// .text:0x0014471C size:0x3C0 mapped:0x807837B0
void pP_ReleaseThrow(int p) {
    InMemFielder* fielder = &g_Fielders[(s8)PP.fielderIndex[p]];
    int character = PP.character[p];
    u8* state;
    u8 target = PP.throwBall[p];
    VecXYZ pos;

    if (fielder->CharID == CHAR_ID_PETEY) {
        getAnimRelatedCoordinates(character, 9, &pos);
    } else if (fielder->throwingHandedness == 0) {
        getAnimRelatedCoordinates(character, 0x19, &pos);
    } else {
        getAnimRelatedCoordinates(character, 0x13, &pos);
    }
    PP.ballPos[target].x = pos.x;
    PP.ballPos[target].y = -pos.y;
    PP.ballPos[target].z = pos.z;
    pos.x = fielder->throwTarget.x - PP.ballPos[target].x;
    pos.y = fielder->throwTarget.y - PP.ballPos[target].y;
    pos.z = fielder->throwTarget.z - PP.ballPos[target].z;
    state = (u8*)PP.ballState + target;
    if (*state == 4) {
        if (PP.ballKind[target] != 5) {
            f32 dist = dolsqrtf2(SQ(pos.x) + SQ(pos.z));
            f32 scale;
            if (p == 0 || p == 3) {
                scale = lbl_3_data_21E24[8] / dist;
            } else {
                scale = lbl_3_data_21E24[9] / dist;
            }
            PP_BALL_VEL(target).x = pos.x * scale;
            PP_BALL_VEL(target).z = pos.z * scale;
            PP_BALL_VEL(target).y = lbl_3_data_21E24[10];
        } else {
            PP_BALL_VEL(target).x = pos.x / (f32)(lbl_3_data_21E68[23] + 10);
            PP_BALL_VEL(target).z = (fielder->throwTarget.z - PP.ballPos[target].z) / (f32)(lbl_3_data_21E68[23] + 10);
            PP_BALL_VEL(target).y = (-lbl_3_data_21E24[11] * (f32)(lbl_3_data_21E68[23] + 10)) / 2.0f;
        }
        *state = 6;
    } else {
        f32 frames = (f32)LERPToNewRange_Float(fielder->throwingArm, 0, 100, lbl_3_data_21E1C[0], lbl_3_data_21E1C[1]);
        PP_BALL_VEL(target).x = pos.x / frames;
        PP_BALL_VEL(target).y = pos.y / frames;
        PP_BALL_VEL(target).z = pos.z / frames;
        *state = 5;
    }
    PP.ballFrames[target] = 0;
    if (PP.ballKind[target] == 5) {
        callSfx(0x308);
    }
}

// .text:0x0014443C size:0x2E0 mapped:0x807834D0
void pP_UpdatePiranhas(void) {
    int k;

    pP_ScheduleBigPiranha();
    for (k = 0; k < PP_SPAWNER_COUNT; k++) {
        PPSpawner* sp = PP_SPAWNER(k);
        SATURATING_INCREMENT(sp->_18);
        SATURATING_INCREMENT(sp->_1A);
        if (sp->_1E != 0) {
            SATURATING_INCREMENT(sp->_1E);
        }
        if (sp->mode == 0) {
            pP_UpdateHiddenPiranha(k);
        } else if (sp->mode == 1) {
            f32 hi;
            f32 lo;
            sp->_1C--;
            hi = lbl_3_data_21D1C[sp->isBig * 2 + 1];
            lo = lbl_3_data_21D1C[sp->isBig * 2];
            sp->pos.y = (hi - lo) * ((f32)sp->_1A / (f32)lbl_3_data_21E68[5]) + lo;
            if (sp->_1C <= 0) {
                sp->mode = 2;
                sp->_1A = 0;
            }
        } else if (sp->mode == 2) {
            ppStopSpawnerWaits();
            pP_PiranhaSpit(k);
        } else if (sp->mode == 3) {
            f32 hi = lbl_3_data_21D1C[sp->isBig * 2 + 1];
            f32 lo = lbl_3_data_21D1C[sp->isBig * 2];
            sp->pos.y = (lo - hi) * ((f32)sp->_1A / (f32)lbl_3_data_21E68[6]) + lo;
            if (sp->_1A >= lbl_3_data_21E68[6]) {
                sp->mode = 0;
                sp->_1A = 0;
                PP.holeUsed[sp->kind] = 0;
                if (PP.x_1CA3 != 0) {
                    PP.x_1CA3 = 0;
                }
            }
        } else if (sp->mode == 4) {
            if (sp->_1C != 0) {
                sp->_1C--;
            }
            if (sp->_1A >= lbl_3_data_21E68[8]) {
                sp->mode = 0;
                sp->_1A = 0;
            }
        }
    }
}

// .text:0x0014423C size:0x200 mapped:0x807832D0
void pP_ScheduleBigPiranha(void) {
    int low;
    int high;
    int k;

    if (g_Minigame.turnOverStatus != 0) {
        return;
    }
    if (PP.x_1CA3 != 0) {
        PPSpawner* sp = PP_SPAWNER(1);
        if (sp->mode != 2) {
            return;
        }
        if (sp->_18 < lbl_3_data_21DC8[g_Minigame.soloMinigameDifficulty][PP.x_1CA4 * 3 - 1] * 60) {
            return;
        }
        sp->mode = 3;
        sp->_2E = 0;
        sp->_1A = 0;
        return;
    }
    if (PP.x_1CA4 >= 2) {
        return;
    }
    if (g_Minigame.multiPlayerInd == 0) {
        low = lbl_3_data_21DC8[g_Minigame.soloMinigameDifficulty][PP.x_1CA4 * 3] * 60;
        high = lbl_3_data_21DC8[g_Minigame.soloMinigameDifficulty][PP.x_1CA4 * 3 + 1] * 60;
    } else {
        low = lbl_3_data_21DC8[4][PP.x_1CA4 * 3] * 60;
        high = lbl_3_data_21DC8[4][PP.x_1CA4 * 3 + 1] * 60;
    }
    if (PP.frameCount < low || PP.frameCount > high) {
        PP.x_1CA2 = 0;
        return;
    }
    for (k = 0; k < PP_SPAWNER_COUNT; k++) {
        if (PP_SPAWNER(k)->mode != 0) {
            break;
        }
    }
    if (k < PP_SPAWNER_COUNT) {
        if (PP.x_1CA2 != 0) {
            return;
        }
        PP.x_1CA2 = 2;
        return;
    }
    {
        PPSpawner* sp = PP_SPAWNER(1);
        sp->mode = 1;
        sp->isBig = 1;
        sp->kind = 4;
        sp->hitsLeft = lbl_3_data_21E10[PP.x_1CA4 + 4];
        sp->_18 = 0;
        sp->_1A = 0;
        sp->_1C = lbl_3_data_21E68[5];
        sp->_20 = 0;
        sp->_2E = 0;
        sp->pos.y = lbl_3_data_21D1C[3];
        sp->queue[0] = -1;
        sp->queue[1] = -1;
        sp->queue[2] = -1;
        sp->queue[3] = -1;
        PP.x_1CA3 = 1;
        PP.x_1CA2 = 0;
        PP.x_1CA4++;
    }
}

// .text:0x0014402C size:0x210 mapped:0x807830C0
void pP_UpdateHiddenPiranha(int idx) {
    int free[4];
    int* freeEnd;
    int freeCount;
    int k;

    if (g_Minigame.turnOverStatus == 0) {
        if (PP.spawner[idx]._1C < 0) {
            PP.spawner[idx]._1C = RandomInt_Game_Range(lbl_3_data_21DC4[0], lbl_3_data_21DC4[1]);
        } else if (PP.x_1CA3 == 0 && PP.x_1CA2 == 0) {
            PP.spawner[idx]._1C--;
            if (PP.spawner[idx]._1C == 0) {
                freeEnd = free;
                for (k = 0, freeCount = 0; k < 4; k++) {
                    if (PP.holeUsed[k] == 0) {
                        *freeEnd++ = k;
                        freeCount++;
                    }
                }
                PP.spawner[idx].kind = free[random_fn_3_9EE24(freeCount)];
                PP.holeUsed[PP.spawner[idx].kind] = 1;
                PP.spawner[idx].hitsLeft = lbl_3_data_21E10[PP.spawner[idx].kind];
                PP.spawner[idx]._1C = lbl_3_data_21E68[5];
                PP.spawner[idx]._18 = 0;
                PP.spawner[idx]._1A = 0;
                PP.spawner[idx]._1E = 0;
                PP.spawner[idx].mode = 1;
                PP.spawner[idx].isBig = 0;
                PP.spawner[idx].pos.y = lbl_3_data_21D1C[1];
                PP.spawner[idx]._22 = lbl_3_data_21E04[0] + RandomInt_Game_Range(lbl_3_data_21E04[0], lbl_3_data_21E04[1]);
                PP.spawner[idx]._24 = PP.spawner[idx]._22;
                PP.spawner[idx]._34 = -1;
                PP.spawner[idx]._14 = 0.0f;
                PP.spawner[idx]._0C = 0.0f;
                PP.spawner[idx].angle = lbl_3_data_26698[idx];
            }
        }
    }
}

// .text:0x00143FAC size:0x80 mapped:0x80783040
void pP_UpdateActivePiranha(int idx) {
    int i;

    if (PP.x_1CA2 == 2) {
        for (i = 0; i < PP_SPAWNER_COUNT; i++) {
            PPSpawner* sp = PP_SPAWNER(i);
            if (sp->mode == 2) {
                sp->mode = 3;
                sp->_1A = 0;
            }
        }
    }
    pP_PiranhaSpit(idx);
}

// .text:0x001439EC size:0x5C0 mapped:0x80782A80
void pP_PiranhaSpit(int idx) {
    PPSpawner* sp = PP_SPAWNER(idx);

    if (sp->isBig != 0) {
        sp->_20++;
        if (sp->_20 == 1) {
            sp->_2E = 0;
        }
        if (sp->_20 >= lbl_3_data_21E68[12]) {
            int i;
            sp->_20 = 0;
            for (i = 0; i < PP_PLAYER_COUNT; i++) {
                pP_SpawnProjectile(idx, i);
                callSfx(0x2DA);
            }
            sp->_2E = 1;
        }
    } else if (sp->_2E != 0) {
        sp->_26++;
        if (sp->_26 == lbl_3_data_21E68[13]) {
            pP_SpawnProjectile(idx, sp->queue[0]);
            sp->_34 = -1;
            sp->queue[0] = sp->queue[1];
            sp->queue[1] = sp->queue[2];
            sp->queue[2] = sp->queue[3];
            sp->queue[3] = -1;
            if (sp->queue[0] < 0) {
                sp->_2E = 0;
            }
            sp->_26 = 0;
            callSfx(0x2DA);
        }
    }
}

// .text:0x00143770 size:0x27C mapped:0x80782804
BOOL pP_PiranhaAimAtPlayer(PPSpawner* sp) {
    int preferred[PP_PLAYER_COUNT];
    int fallback[PP_PLAYER_COUNT];
    Vec toFielder;
    Vec forward = {0.0f, 0.0f, -1.0f};
    int preferredCount;
    int fallbackCount;
    f32 angle;

    if (sp->_2E == 0) {
        int* preferredEnd = preferred;
        int* list;
        int* count;
        int i;

        for (i = 0; i < PP_PLAYER_COUNT; i++) {
            preferred[i] = -1;
        }
        preferredCount = 0;
        fallbackCount = 0;
        for (i = 0; i < PP_PLAYER_COUNT; i++) {
            if (PP.hitState[i] == 0) {
                if (PP.targeted[i] == 0) {
                    *preferredEnd++ = i;
                    preferredCount++;
                }
                fallback[i] = i;
                fallbackCount++;
            }
        }
        if (preferredCount == 0) {
            if (fallbackCount == 0) {
                for (fallbackCount = 0; fallbackCount < PP_PLAYER_COUNT; fallbackCount++) {
                    fallback[fallbackCount] = fallbackCount;
                }
            }
            list = fallback;
            count = &fallbackCount;
        } else {
            list = preferred;
            count = &preferredCount;
        }
        sp->_35 = list[random_fn_3_9EE24(*count)];
        sp->_34 = PP.fielderIndex[sp->_35];
        PP.targeted[sp->_35] = 1;
    } else {
        sp->_34 = PP.fielderIndex[sp->queue[0]];
    }
    PSVECSubtract((Vec*)&g_Fielders[sp->_34].pos, (Vec*)sp, &toFielder);
    toFielder.y = 0.0f;
    if (PSVECMag(&toFielder)) {
        PSVECNormalize(&toFielder, &toFielder);
    }
    angle = acos(PSVECDotProduct(&toFielder, &forward));
    if (0.0f > toFielder.x) {
        angle = 6.283185258507729 - angle;
    }
    sp->angle = -angle;
    return TRUE;
}

// .text:0x00143714 size:0x5C mapped:0x807827A8
void pP_UpdateProjectiles(void) {
    int i;

    for (i = 0; i < PP_OBJECT_COUNT; i++) {
        if (PP_OBJECT(i)->state != 0) {
            pP_UpdateProjectile(i);
        }
    }
}

// .text:0x00143358 size:0x3BC mapped:0x807823EC
void pP_UpdateProjectile(int idx) {
    PPObject* obj = PP_OBJECT(idx);
    InMemFielder* fielder;
    int i;

    obj->_20++;
    if (obj->_20 > lbl_3_data_21E68[10]) {
        obj->state = 0;
        return;
    }
    obj->pos.x += obj->vel.x;
    obj->pos.y += obj->vel.y;
    obj->pos.z += obj->vel.z;
    if (obj->state == 2) {
        obj->vel.y += obj->_18;
    }
    if (obj->pos.y < lbl_3_data_21E24[13]) {
        if (obj->pos.z < 0.0f) {
            if (obj->state == 2) {
                PP.targeted[obj->_1C] = 0;
            }
            obj->state = 0;
            return;
        }
        obj->vel.y = -obj->vel.y;
    }
    for (i = 0; i < PP_PLAYER_COUNT; i++) {
        s8 fielderIndex = PP.fielderIndex[i];
        if (fielderIndex < 0) {
            continue;
        }
        fielder = &g_Fielders[fielderIndex];
        if (PP.playerState[i] != 0) {
            continue;
        }
        if (lbl_3_data_21E24[2] + fielderHitboxesForGarlicKnockout[fielder->Weight] > dolsqrtf2(SQ(obj->pos.x - fielder->pos.x) + SQ(obj->pos.z - fielder->pos.z))) {
            Vec dir;
            Vec unusedDir = {0.0f, 0.0f, -1.0f};
            if (obj->state == 2) {
                PP.targeted[obj->_1C] = 0;
            }
            obj->state = 0;
            if (PP.hitState[i] != 0) {
                return;
            }
            PP.hitState[i] = 1;
            PP.stateFrames[i] = lbl_3_data_21E68[14];
            PP.hitCount[i] = 0;
            dir.x = obj->vel.x;
            dir.y = 0.0f;
            dir.z = obj->vel.z;
            PSVECNormalize(&dir, &dir);
            fielder->xMovementDir = dir.x;
            PP.x_1DF4[i] = 1;
            fielder->zMovementDir = dir.z;
            fielder->currentVelocity = lbl_3_data_21E24[15];
            setCharacterAnimations((s8)PP.character[i], 2);
            if (PP.x_1CB1[i] < 0xFFFE) {
                PP.x_1CB1[i]++;
            } else {
                PP.x_1CB1[i] = 0xFF;
            }
            return;
        }
    }
}

// .text:0x001430D0 size:0x288 mapped:0x80782164
void pP_SpawnProjectile(int arg, int owner) {
    PPObject* obj;
    int j;

    for (j = 0; j < PP_OBJECT_COUNT; j++) {
        if (PP_OBJECT(j)->state == 0) {
            break;
        }
    }
    if (j < PP_OBJECT_COUNT) {
        InMemFielder* fielder;
        f32 yOffset;
        f32 scaled;
        f32 dx;
        f32 dy;
        f32 dz;
        obj = PP_OBJECT(j);
        mm_GetPiranhaSpitPos(arg, &obj->pos);
        fielder = &g_Fielders[(s8)PP.fielderIndex[owner]];
        dx = lbl_3_data_21B94[PP.goalIndex[owner]].x - obj->pos.x;
        dy = lbl_3_data_21B94[PP.goalIndex[owner]].y - obj->pos.y;
        dz = lbl_3_data_21B94[PP.goalIndex[owner]].z - obj->pos.z;
        scaled = 0.01f * ((f32)barrelCollisionHitboxes[fielder->CharID] * charSizeMultipliers[fielder->CharID][0]);
        yOffset = lbl_3_data_21D2C[1] + scaled;
        dy += yOffset;
        obj->vel.x = dx / (f32)lbl_3_data_21E68[21];
        obj->vel.y = dy / (f32)lbl_3_data_21E68[21];
        obj->vel.z = dz / (f32)lbl_3_data_21E68[21];
        obj->state = 1;
        obj->_20 = 0;
        obj->_1C = owner;
        fn_3_15730C(j, obj->pos.x, -obj->pos.y, obj->pos.z);
    }
}

// .text:0x00142DB4 size:0x31C mapped:0x80781E48
void pP_SpawnLobbedProjectile(int idx) {
    PPSpawner* sp = PP_SPAWNER(idx);
    PPObject* obj;
    int j;

    for (j = 0; j < PP_OBJECT_COUNT; j++) {
        if (PP_OBJECT(j)->state == 0) {
            break;
        }
    }
    if (j < PP_OBJECT_COUNT) {
        InMemFielder* fielder;
        f32 yOffset;
        f32 scaled;
        f32 dx;
        f32 dy;
        f32 dz;
        obj = PP_OBJECT(j);
        if (sp->isBig != 0) {
            obj->pos.x = lbl_3_data_21BC4[idx][3].x;
            obj->pos.y = lbl_3_data_21BC4[idx][3].y;
            obj->pos.z = lbl_3_data_21BC4[idx][3].z;
        } else {
            obj->pos.x = lbl_3_data_21BC4[idx][2].x;
            obj->pos.y = lbl_3_data_21BC4[idx][2].y;
            obj->pos.z = lbl_3_data_21BC4[idx][2].z;
        }
        obj->_22 = sp->_35;
        fielder = &g_Fielders[sp->_34];
        obj->_1C = sp->_35;
        dx = lbl_3_data_21B94[PP.goalIndex[sp->_35]].x - obj->pos.x;
        dy = lbl_3_data_21B94[PP.goalIndex[sp->_35]].y - obj->pos.y;
        dz = lbl_3_data_21B94[PP.goalIndex[sp->_35]].z - obj->pos.z;
        scaled = 0.01f * ((f32)barrelCollisionHitboxes[fielder->CharID] * charSizeMultipliers[fielder->CharID][0]);
        yOffset = lbl_3_data_21D2C[1] + scaled;
        dy += yOffset;
        obj->vel.x = dx / (f32)lbl_3_data_21E68[22];
        obj->vel.y = dy / (f32)lbl_3_data_21E68[22];
        obj->vel.z = dz / (f32)lbl_3_data_21E68[22];
        obj->_18 = 0.0f;
        obj->state = 2;
        obj->_20 = 0;
        fn_3_15730C(j, obj->pos.x, -obj->pos.y, obj->pos.z);
    }
}

// .text:0x00142CA8 size:0x10C mapped:0x80781D3C
void pP_TallyScores(void) {
    int i;
    int j;

    for (i = 0; i < PP_PLAYER_COUNT; i++) {
        for (j = 0; j < (s32)PP_SCORE_ENTRY_COUNT; j++) {
            PP.pointsA[i] += PP.scoreEntries[i][j];
            PP.scoreEntries[i][j] = 0;
        }
        PP.scoreEntryCount[i] = 0;
    }
}

// .text:0x00142C18 size:0x90 mapped:0x80781CAC
void pP_InitAI(void) {
    PPAI* ai = PP.ai;
    s8 i;

    memset(g_Minigame._1D7C, 0, 0x78);
    i = 0;
    do {
        u8 aiStrength = PP.aiStrength[i];
        ai->selection = 1;
        ai->timer = RandomInt_Game_Range(lbl_3_data_21EAC[aiStrength][0], lbl_3_data_21EAC[aiStrength][1]);
        ai++;
        i++;
    } while (i < PP_PLAYER_COUNT);
}

// .text:0x001428F0 size:0x328 mapped:0x80781984
u8 pP_AIThrow(s8 slot, u8 force) {
    PPAI* ai = &PP.ai[slot];
    s8 found = -1;
    s8 character = PP.character[slot];
    u8 aiStrength = PP.aiStrength[slot];
    s8 selection = PP.ai[slot].selection;
    u8 hit = FALSE;
    s8 count = 0;
    s8 target;
    u8 targetKind;
    s8 i;

    if (PP.ai[slot].timer >= 0) {
        ai->timer--;
    }
    target = PP.heldBalls[slot][0];
    if (target < 0) {
        return 0;
    }
    i = 0;
    do {
        if (PP.spawner[i].mode == 2) {
            count++;
            if (PP.spawner[selection].kind == 4) {
                found = i;
                break;
            }
        }
        i++;
    } while (i < PP_SPAWNER_COUNT);
    if (found < 0 && ai->timer >= 0 && !force) {
        return 0;
    }
    targetKind = PP.ballKind[target];
    if (!(targetKind == 5 && (count == 0 || RandomInt_Game(100) < lbl_3_data_21EC0[aiStrength]))) {
        if (count == 0) {
            return 0;
        }
        if (RandomInt_Game(100) < lbl_3_data_21EBC[aiStrength]) {
            hit = TRUE;
        }
        if (!hit) {
            if (PP.spawner[selection].mode == 2) {
                u8 kind = PP.spawner[selection].kind;
                if (targetKind == kind || targetKind == 5 || kind == 4) {
                    hit = TRUE;
                }
            }
        }
        if (!hit) {
            i = 0;
            do {
                if (PP.spawner[i].mode == 2) {
                    u8 kind = PP.spawner[i].kind;
                    if (targetKind == kind || targetKind == 5 || kind == 4) {
                        selection = i;
                        hit = TRUE;
                        break;
                    }
                }
                i++;
            } while (i < PP_SPAWNER_COUNT);
        }
    }
    if (hit) {
        switch (selection) {
            case 0:
                g_Minigame._1D7C[character].newButtonInput |= INPUT_BUTTON_A | INPUT_BUTTON_RIGHT;
                g_Minigame._1D7C[character].buttonInput |= INPUT_BUTTON_A | INPUT_BUTTON_RIGHT;
                break;
            case 1:
                g_Minigame._1D7C[character].newButtonInput |= INPUT_BUTTON_A | INPUT_BUTTON_UP;
                g_Minigame._1D7C[character].buttonInput |= INPUT_BUTTON_A | INPUT_BUTTON_UP;
                break;
            case 2:
                g_Minigame._1D7C[character].newButtonInput |= INPUT_BUTTON_A | INPUT_BUTTON_LEFT;
                g_Minigame._1D7C[character].buttonInput |= INPUT_BUTTON_A | INPUT_BUTTON_LEFT;
                break;
        }
        ai->selection = selection;
    } else {
        g_Minigame._1D7C[character].newButtonInput |= INPUT_BUTTON_B;
        g_Minigame._1D7C[character].buttonInput |= INPUT_BUTTON_B;
    }
    ai->timer = RandomInt_Game_Range(lbl_3_data_21EAC[aiStrength][0], lbl_3_data_21EAC[aiStrength][1]);
    return 1;
}

// .text:0x00142570 size:0x380 mapped:0x80781604
int pP_AIFramesUntilHit(s8 slot) {
    InMemFielder* fielder = &g_Fielders[PP.fielderIndex[slot]];
    f32 reach = lbl_3_data_21E24[2] + fielderHitboxesForGarlicKnockout[fielder->Weight];
    int best = 10000;
    u8 found = FALSE;
    s8 i;

    i = 0;
    do {
        PPObject* obj = PP_OBJECT(i);
        if (obj->state != 0) {
            f32 dz = fielder->pos.z - obj->pos.z;
            f32 dx = fielder->pos.x - obj->pos.x;
            f32 dist = dolsqrtf2(dx * dx + dz * dz);
            f32 speed;
            if (dist < reach) {
                return 0;
            }
            dx /= dist;
            dz /= dist;
            speed = dolsqrtf2(obj->vel.x * obj->vel.x + obj->vel.z * obj->vel.z);
            if (dx * (obj->vel.x / speed) + dz * (obj->vel.z / speed) >= 0.9994f) {
                int frames = (int)((dist - reach) / speed);
                if (frames < best) {
                    best = frames;
                }
                found = TRUE;
            }
        }
        i++;
    } while (i < PP_OBJECT_COUNT);
    i = 0;
    do {
        if (PP.ballState[i] == 6 && PP.ballKind[i] == 5 && slot == -1 - PP.ballTarget[i]) {
            int frames = lbl_3_data_21E68[23] - PP.ballFrames[i];
            if (frames >= 0) {
                if (frames < best) {
                    best = frames;
                }
                found = TRUE;
            }
        }
        i++;
    } while (i < PP_BALL_COUNT);
    return found ? best : -1;
}

// .text:0x00142284 size:0x2EC mapped:0x80781318
void pP_UpdateAI(void) {
    int target[PP_PLAYER_COUNT];
    PPAI* ai = PP.ai;
    s8 i;

    i = 0;
    do {
        s8 character = PP.character[i];
        if (character >= 0 && character < PP_PLAYER_COUNT) {
            target[i] = pP_AIFramesUntilHit(i);
            if (PP.aiControlled[i] != 0) {
                u8 aiStrength;
                memset(&g_Minigame._1D7C[character], 0, sizeof(InputStruct));
                aiStrength = PP.aiStrength[i];
                switch (ai[i].state) {
                    case 0:
                        if (target[i] >= 0) {
                            switch (RandomIndexFromWeights(lbl_3_data_21E9C[aiStrength], 4)) {
                                case 0:
                                    if (target[i] > LERPToNewRange_Float(PP.hitCount[i], 0, lbl_3_data_21E68[19], lbl_3_data_21E68[2], lbl_3_data_21E68[3]) + 3) {
                                        if (pP_AIThrow(i, FALSE)) {
                                            ai[i].state = 1;
                                        }
                                    } else {
                                        g_Minigame._1D7C[character].newButtonInput |= INPUT_BUTTON_DOWN;
                                        g_Minigame._1D7C[character].buttonInput |= INPUT_BUTTON_DOWN;
                                        ai[i].state = 2;
                                    }
                                    break;
                                case 1:
                                    if (target[i] > lbl_3_data_21E68[2] + 3) {
                                        if (pP_AIThrow(i, FALSE)) {
                                            ai[i].state = 1;
                                        }
                                    } else {
                                        g_Minigame._1D7C[character].newButtonInput |= INPUT_BUTTON_DOWN;
                                        g_Minigame._1D7C[character].buttonInput |= INPUT_BUTTON_DOWN;
                                        ai[i].state = 2;
                                    }
                                    break;
                                case 2:
                                    g_Minigame._1D7C[character].newButtonInput |= INPUT_BUTTON_DOWN;
                                    g_Minigame._1D7C[character].buttonInput |= INPUT_BUTTON_DOWN;
                                    ai[i].state = 2;
                                    break;
                                case 3:
                                    if (pP_AIThrow(i, TRUE)) {
                                        ai[i].state = 1;
                                    }
                                    break;
                            }
                        } else {
                            if (pP_AIThrow(i, FALSE)) {
                                ai[i].state = 1;
                            }
                        }
                        break;
                    case 1:
                        if (PP.throwDirection[i] < 0) {
                            ai[i].state = 0;
                        }
                        break;
                    case 2:
                        g_Minigame._1D7C[character].buttonInput |= INPUT_BUTTON_DOWN;
                        if (PP.playerState[i] != 1) {
                            ai[i].state = 3;
                        }
                        break;
                    case 3:
                        if (target[i] >= 0) {
                            g_Minigame._1D7C[character].buttonInput |= INPUT_BUTTON_DOWN;
                        } else {
                            ai[i].state = 4;
                        }
                        break;
                    case 4:
                        if (PP.playerState[i] != 3) {
                            ai[i].state = 0;
                        }
                        break;
                }
            }
        } else {
            target[i] = -1;
        }
        i++;
    } while (i < PP_PLAYER_COUNT);
}

// .text:0x0014225C size:0x28 mapped:0x807812F0
void pP_SetPulseTevCallback(void) {
    fn_800B9948(pP_PulseTevCallback);
}

// .text:0x00142088 size:0x1D4 mapped:0x8078111C
void pP_InitPulseTexture(void) {
    u32 offset;
    u32 i;
    u32 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            /* pP_TiledTexelIndex(j, i, 4) * 4, written out */
            offset = (((int)i % 4) * 4 + ((int)i / 4) * 16 + (int)j % 4 + ((int)j / 4) * 16) * 4;
            if (offset < 32) {
                lbl_3_bss_B800[offset + 2] = 0xFF;
                lbl_3_bss_B800[offset] = 0xFF;
                lbl_3_bss_B800[offset + 3] = 0x96;
                lbl_3_bss_B800[offset + 1] = 0x96;
            } else {
                lbl_3_bss_B800[offset + 2] = 0;
                lbl_3_bss_B800[offset] = 0;
                lbl_3_bss_B800[offset + 3] = 0;
                lbl_3_bss_B800[offset + 1] = 0;
            }
        }
    }
    GXInitTexObj(&lbl_3_bss_B7C4, lbl_3_bss_B800, 4, 4, GX_TF_RGBA8, GX_REPEAT, GX_REPEAT, GX_DISABLE);
    GXInitTexObjLOD(&lbl_3_bss_B7C4, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_DISABLE, GX_DISABLE, GX_ANISO_1);
    lbl_3_data_266A4 = -1;
    lbl_3_bss_B7E4 = 0;
    lbl_3_bss_B7C1 = 0;
}

// .text:0x00142030 size:0x58 mapped:0x807810C4
int pP_TiledTexelIndex(int x, int y, int width) {
    int fineY;
    int fineX;
    int rowBase;

    fineY = y % 4;
    y /= 4;
    rowBase = width * (y * 4);
    fineX = x % 4;
    x /= 4;
    return fineY * 4 + (rowBase + x * 16) + fineX;
}

// .text:0x00141F30 size:0x100 mapped:0x80780FC4
void pP_UpdatePulseTexture(void) {
    int value;
    int i;

    lbl_3_bss_B7E4 += !PauseSimulation;
    if ((lbl_3_bss_B7E4 & 1) == 0) {
        u8* tex = lbl_3_bss_B800;
        value = tex[0];
        value += lbl_3_data_266A4 * 2;
        if (value > 255) {
            value = 255;
        } else if (value < 0) {
            value = 0;
        }
        for (i = 0; i < 32; i += 2) {
            tex[i] = value;
        }
        DCFlushRange(lbl_3_bss_B800, 0x40);
        if (value + lbl_3_data_266A4 * 2 > 255 || value + lbl_3_data_266A4 * 2 < 0) {
            lbl_3_data_266A4 *= -1;
        }
    }
}

// .text:0x00141C8C size:0x2A4 mapped:0x80780D20
void pP_PulseTevCallback(void* model, GXTevStageID* stage, GXTexCoordID* coord, GXTexMapID* map, s8* nStages, s8* nCoords) {
    Mtx texMtx;
    Mtx postMtx;
    Mtx trans;

    pP_UpdatePulseTexture();
    GXLoadTexObj(&lbl_3_bss_B7C4, *map);
    PSMTXIdentity(texMtx);
    PSMTXScale(postMtx, 0.5f, -0.5f, 0.0f);
    PSMTXTrans(trans, 0.5f, 0.5f, 1.0f);
    PSMTXConcat(trans, postMtx, postMtx);
    GXLoadTexMtxImm(texMtx, GX_TEXMTX0 + *map * 3, GX_MTX3x4);
    GXLoadTexMtxImm(postMtx, GX_PTTEXMTX0 + *map * 3, GX_MTX3x4);
    GXSetTexCoordGen2(*coord, GX_TG_MTX2X4, GX_TG_POS, GX_TEXMTX0 + *map * 3, GX_TRUE, GX_PTTEXMTX0 + *map * 3);
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
    pP_CountPulseDraws();
}

// .text:0x00141C44 size:0x48 mapped:0x80780CD8
void pP_CountPulseDraws(void) {
    lbl_3_bss_B7C1++;
    if (lbl_3_bss_B7C1 >= 6) {
        lbl_3_bss_B7C1 = 0;
        fn_800B993C();
    }
}
