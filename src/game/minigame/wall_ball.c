/* Every dolsqrtf2() call here is inlined, so keep it internal. With the
 * header's default `extern` linkage MWCC also emits the out-of-line copy's
 * _half/_three local statics as weak objects at the head of .rodata, which
 * the original module does not have. */
#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_wallBall
#include "game/minigame/wall_ball.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/minigame/rep_3880.h"
#include "game/sound/m_sound.h"
#include "game/math/game_math.h"
#include "Dolphin/stl.h"
#include "stl/stdlib.h"
#include "stl/math.h"
#include "static/UnknownHomes_Static.h"

extern f32 lbl_3_data_21674[];
extern f32 lbl_3_data_21634[];
extern s16 lbl_3_data_2167C[];
extern f32 lbl_3_data_219B8[];
extern f32 lbl_3_data_21688[];
extern f32 lbl_3_data_215C8[];
extern VecXYZ lbl_3_data_215E0[];
extern s16 lbl_3_data_21654[];
extern u32 wallBall_nCoinsToGenerate[];
extern s8 lbl_3_data_21694[4][7];
extern s8 lbl_3_data_216B0[4][2];
extern s8 lbl_3_data_216B8[];
extern s16 lbl_3_data_5F3C[];
extern f32 lbl_3_data_21500[];
extern f32 fieldingStartingCoords_regular[];
extern VecXYZ lbl_3_data_21520[];
extern void fn_800246D4(void* cmp, void* base, void* scratch, int size, int count);
extern void fn_8004C108(VecXYZ* pos, BOOL flag);

#define MINIGAME_OFFSET(field) ((u32)&((MiniGameStruct*)0)->field)
#define WALL_BALL_COIN_POSITION_OFFSET MINIGAME_OFFSET(wallBall_coinCoordinates)
#define WALL_BALL_COIN_VELOCITY_OFFSET MINIGAME_OFFSET(wallBall_coinVelocity)
#define WALL_BALL_COIN_FRAME_OFFSET MINIGAME_OFFSET(wallBall_coinsVisibleFrameCounter)
#define WALL_BALL_COIN_VISIBLE_OFFSET MINIGAME_OFFSET(wallBall_coinsVisibleInd)
#define WALL_BALL_COIN_POSITION_INDEX (WALL_BALL_COIN_POSITION_OFFSET / sizeof(f32))
#define WALL_BALL_COIN_VELOCITY_INDEX (WALL_BALL_COIN_VELOCITY_OFFSET / sizeof(f32))
#define WALL_BALL_MAX_COINS 100

/* The wall records at MiniGameStruct.wallBallStruct are 0x2C bytes apart; the
 * header's MaybeWallBallStruct is declared larger, so index them by hand. */
#define WALL_BALL_WALL_COUNT 7
#define WALL_BALL_WALL_SIZE 0x2C
#define WALL_BALL_WALL(index) \
    ((MaybeWallBallStruct*)((u8*)&g_Minigame + MINIGAME_OFFSET(wallBallStruct) + (index) * WALL_BALL_WALL_SIZE))

/* The coin arrays are declared in MiniGameStruct as their first element only;
 * these index the full 100-entry arrays from the struct base. */
#define WALL_BALL_COIN_VISIBLE(i) (*((u8*)&g_Minigame + WALL_BALL_COIN_VISIBLE_OFFSET + (i)))
#define WALL_BALL_COIN_FRAMES(i) (*(s16*)((u8*)&g_Minigame + WALL_BALL_COIN_FRAME_OFFSET + (i) * 2))
#define WALL_BALL_COIN_POSITION(i) ((VecXYZ*)((u8*)&g_Minigame + WALL_BALL_COIN_POSITION_OFFSET + (i) * 12))
#define WALL_BALL_COIN_VELOCITY(i) ((VecXYZ*)((u8*)&g_Minigame + WALL_BALL_COIN_VELOCITY_OFFSET + (i) * 12))

// .text:0x00114A88 size:0x538 mapped:0x80753B1C
void wallBallRotatePitchers(int force) {
    int i;
    MiniGameStruct* base;
    g_Minigame.wallBallPitcherRotationCounter++;
    if (g_Minigame.wallBallPitcherRotationCounter == 1 || force) {
        if (g_Minigame.soloMinigameDifficulty != MINIGAME_DIFFICULTY_SOLO_NON_CHALLENGE || g_Minigame.multiPlayerInd) {
            int prior = (g_Minigame.turnNumberWithinRound + 3) % 4;
            s8 slot = (s8)*((u8*)&g_Minigame + 0x18E0 + prior);
            s8 fielderIndex = g_Minigame.minigameFielderIndex[slot];
            g_Fielders[fielderIndex].pos.x = g_Minigame.wallBallSomeXPos;
            g_Fielders[fielderIndex].pos.z = g_Minigame.wallBallSomeZPos;
        }

        base = &g_Minigame;
        for (i = 0; i < 4; i++) {
            s8 character = *((u8*)base + MINIGAME_OFFSET(minigameControlStruct[0].characterIndex) + i);
            int relative;
            if (character < 0) continue;
            relative = i - base->turnNumberWithinRound;
            if (relative < 0) relative += base->miniGameNumberOfParticipants;
            if (relative == 0) {
                g_Minigame.wallBallWaitingLocations[(s8)*((u8*)base + 0x18E0 + i) * 2] = fieldingStartingCoords_regular[0];
                g_Minigame.wallBallWaitingLocations[(s8)*((u8*)base + 0x18E0 + i) * 2 + 1] = fieldingStartingCoords_regular[1];
            } else {
                g_Minigame.wallBallWaitingLocations[(s8)*((u8*)base + 0x18E0 + i) * 2] = lbl_3_data_21500[relative * 2];
                g_Minigame.wallBallWaitingLocations[(s8)*((u8*)base + 0x18E0 + i) * 2 + 1] = lbl_3_data_21500[relative * 2 + 1];
            }
        }
        if (force) {
            for (i = 0; i < base->miniGameNumberOfParticipants; i++) {
                s8 fielderIndex = *((u8*)base + MINIGAME_OFFSET(minigameFielderIndex) + i);
                g_Fielders[fielderIndex].pos.x = *(f32*)((u8*)base + MINIGAME_OFFSET(wallBallWaitingLocations[0]) + i * 8);
                g_Fielders[fielderIndex].pos.y = 0.0f;
                g_Fielders[fielderIndex].pos.z = *(f32*)((u8*)base + MINIGAME_OFFSET(wallBallWaitingLocations[1]) + i * 8);
            }
            return;
        }
    }
    if (g_Minigame.wallBallPitcherRotationCounter >= lbl_3_data_2167C[1]) {
        g_Minigame.wallBallRotatePitchersInd = FALSE;
        for (i = 0; i < 4; i++) {
            if (g_Minigame.minigameControlStruct[0].characterIndex[i] >= 0) {
                s8 fielderIndex = g_Minigame.minigameFielderIndex[i];
                g_Fielders[fielderIndex].currentVelocity = 0.0f;
            }
        }
        return;
    }

    {
        f32 frames = (f32)(lbl_3_data_2167C[1] - g_Minigame.wallBallPitcherRotationCounter);
        f32 factor = 1.0f / frames;
        for (i = 0; i < 4; i++) {
            if (g_Minigame.minigameControlStruct[0].characterIndex[i] >= 0) {
                s8 fielderIndex = g_Minigame.minigameFielderIndex[i];
                InMemFielder* fielder = &g_Fielders[fielderIndex];
                f32 dx = g_Minigame.wallBallWaitingLocations[i * 2] - fielder->pos.x;
                f32 dz = g_Minigame.wallBallWaitingLocations[i * 2 + 1] - fielder->pos.z;
                f32 distance;
                dx *= factor;
                dz *= factor;
                fielder->velocityX = dx;
                fielder->velocityZ = dz;
                fielder->pos.x += dx;
                fielder->pos.z += dz;
                distance = dolsqrtf2(dx * dx + dz * dz);
                fielder->currentVelocity = distance;
                if (fielder->currentVelocity > 0.0f) {
                    /* The original divides dx for both directions. */
                    fielder->xMovementDir = dx / fielder->currentVelocity;
                    fielder->zMovementDir = dx / fielder->currentVelocity;
                }
            }
        }
    }
}

// .text:0x00114A2C size:0x5C mapped:0x80753AC0
void wallBallUpdateWalls(void) {
    if (g_Minigame.wallBallGameState == WALL_BALL_GAME_STATE_CALCULATE_NEW_WALLS) {
        wallBallCalculateNewWalls();
        wallBall_updateSomePointers();
    } else if (g_Minigame.wallBallGameState == WALL_BALL_GAME_STATE_DROP_IN_NEW_WALLS) {
        wallBallDropInNewWalls();
    } else if (g_Minigame.wallBallGameState == WALL_BALL_GAME_STATE_PITCH_OR_WAITING_FOR_PITCH) {
        wallBallHandleWallHit();
        wallBallUpdateWallWobble();
    }
}

// .text:0x001149B8 size:0x74 mapped:0x80753A4C
int wallBallCompareWalls(const u8* first, const u8* second) {
    MaybeWallBallStruct* firstWall = WALL_BALL_WALL(*first);
    MaybeWallBallStruct* secondWall = WALL_BALL_WALL(*second);

    if (firstWall->_28 == 3 && secondWall->_28 != 3) {
        return -1;
    }
    if (firstWall->_28 != 3 && secondWall->_28 == 3) {
        return 1;
    }
    return firstWall->coinRelated[0] - secondWall->coinRelated[0];
}

static inline void zeroWords(unsigned int* p, unsigned int count) {
    unsigned int n = 0;
    unsigned int* q = p;
    do {
        *q++ = 0;
        n++;
    } while (n < count);
}

// .text:0x00114384 size:0x634 mapped:0x80753418
void wallBallCalculateNewWalls(void) {
    unsigned int active;
    int desired;
    int candidateCount;
    unsigned int counts[3];
    int candidates[WALL_BALL_WALL_COUNT];

    if (g_Minigame.multiPlayerInd || g_Minigame._1A3C ||
        g_Minigame.soloMinigameDifficulty != MINIGAME_DIFFICULTY_SOLO_NON_CHALLENGE) {
        switch (g_Scores.Inning) {
        case 1: desired = 1; break;
        case 2: desired = 2; break;
        default: desired = 3; break;
        }
    } else {
        if (g_Minigame.miniGameTurnCounter < 6) desired = 1;
        else if (g_Minigame.miniGameTurnCounter < 11) desired = 2;
        else if (g_Minigame.miniGameTurnCounter < 16) desired = 3;
        else desired = 4;
    }

    fn_800246D4(wallBallCompareWalls, g_Minigame.wallIndexTracker, g_Minigame.wallIndexTracker, 1, WALL_BALL_WALL_COUNT);
    {
        unsigned int rank = 0;
        do {
            u8 index = *((u8*)&g_Minigame + MINIGAME_OFFSET(wallIndexTracker) + rank);
            MaybeWallBallStruct* wall = WALL_BALL_WALL(index);
            wall->coinRelated[0] = rank;
            rank++;
        } while (rank < WALL_BALL_WALL_COUNT);
    }
    zeroWords(counts, 3);
    {
        unsigned int n;
        active = 0;
        n = 0;
        do {
            u8 index = *((u8*)&g_Minigame + MINIGAME_OFFSET(wallIndexTracker) + n);
            MaybeWallBallStruct* wall = WALL_BALL_WALL(index);
            if (wall->_28 == 3) {
                active++;
                counts[wall->coinGenerationCategory]++;
            }
            n++;
        } while (n < WALL_BALL_WALL_COUNT);
    }
    {
        unsigned int rank = 0;
        do {
            u8 index = *((u8*)&g_Minigame + MINIGAME_OFFSET(wallIndexTracker) + rank);
            MaybeWallBallStruct* wall = WALL_BALL_WALL(index);
            wall->_C = lbl_3_data_21520[wall->coinRelated[0]].x;
            wall->_10 = lbl_3_data_21520[wall->coinRelated[0]].y;
            wall->_14 = lbl_3_data_21520[wall->coinRelated[0]].z;
            if (rank < active) {
                wall->_28 = 2;
            } else {
                wall->_0 = wall->_C;
                wall->_4 = wall->_10;
                wall->zPositionOfSomeWall = wall->_14;
                wall->_0 += lbl_3_data_21520[WALL_BALL_WALL_COUNT + wall->coinRelated[0]].x;
                wall->_4 += lbl_3_data_21520[WALL_BALL_WALL_COUNT + wall->coinRelated[0]].y;
                wall->zPositionOfSomeWall += lbl_3_data_21520[WALL_BALL_WALL_COUNT + wall->coinRelated[0]].z;
                wall->_28 = 1;
                wall->coinGenerationCategory = 1;
                counts[wall->coinGenerationCategory]++;
                wall->_24 = lbl_3_data_21654[4 + wall->coinGenerationCategory];
            }
            wall->_26 = 0;
            wall->_20 = wall->_1C = wall->_18 = 0.0f;
            rank++;
        } while (rank < WALL_BALL_WALL_COUNT);
    }

    if (active < WALL_BALL_WALL_COUNT) {
        if (counts[2] == 0) {
            u8 eligible[WALL_BALL_WALL_COUNT];
            unsigned int rank;
            u8 eligibleCount = 0;
            u8 chosen;
            for (rank = active; rank < WALL_BALL_WALL_COUNT; rank++) {
                unsigned int j = 0;
                do {
                    if (rank == *((u8*)&g_Minigame + MINIGAME_OFFSET(wallBallSpecialWallPos) + j)) break;
                    j++;
                } while (j < 2);
                if (j < 2) continue;
                eligible[eligibleCount++] = rank;
            }
            if (eligibleCount) chosen = eligible[RandomInt_Game(eligibleCount)];
            else chosen = RandomInt_Game_Range(active, WALL_BALL_WALL_COUNT - 1);
            {
                MaybeWallBallStruct* wall = WALL_BALL_WALL(g_Minigame.wallIndexTracker[chosen]);
                wall->coinGenerationCategory = 2;
                wall->_24 = lbl_3_data_21654[4 + wall->coinGenerationCategory];
                counts[1]--;
            }
        }

        if (counts[1] > desired) {
            candidateCount = 0;
            {
                u8* tracker = (u8*)&g_Minigame + active;
                int* candidatePtr = candidates;
                unsigned int rank;
                for (rank = active; rank < WALL_BALL_WALL_COUNT; tracker++, rank++) {
                    MaybeWallBallStruct* wall = WALL_BALL_WALL(tracker[MINIGAME_OFFSET(wallIndexTracker)]);
                    if (wall->coinGenerationCategory == 2) continue;
                    if (rank != 0) {
                        MaybeWallBallStruct* prev = WALL_BALL_WALL(tracker[MINIGAME_OFFSET(wallIndexTracker) - 1]);
                        if (prev->coinGenerationCategory == 2) continue;
                    }
                    if (rank != WALL_BALL_WALL_COUNT - 1 && desired > 1) {
                        MaybeWallBallStruct* next = WALL_BALL_WALL(tracker[MINIGAME_OFFSET(wallIndexTracker) + 1]);
                        if (next->coinGenerationCategory == 2) continue;
                    }
                    *candidatePtr++ = rank;
                    candidateCount++;
                }
            }
            if (candidateCount != 0) {
                while (counts[1] > desired) {
                    int selected = RandomInt_Game(candidateCount);
                    MaybeWallBallStruct* wall = WALL_BALL_WALL(g_Minigame.wallIndexTracker[candidates[selected]]);
                    wall->coinGenerationCategory = 0;
                    counts[1]--;
                    wall->_24 = lbl_3_data_21654[4 + wall->coinGenerationCategory];
                    {
                        unsigned int shift = selected;
                        for (; shift < candidateCount - 1; shift++) candidates[shift] = candidates[shift + 1];
                    }
                    if (--candidateCount <= 0) break;
                }
            }
        }
    }

    {
        unsigned int n = 0;
        do {
            *((u8*)&g_Minigame + MINIGAME_OFFSET(_1A7D) + n) = *((u8*)&g_Minigame + MINIGAME_OFFSET(wallBallSpecialWallPos) + n);
            n++;
        } while (n < 1);
    }
    {
        unsigned int rank = 0;
        do {
            u8 index = *((u8*)&g_Minigame + MINIGAME_OFFSET(wallIndexTracker) + rank);
            MaybeWallBallStruct* wall = WALL_BALL_WALL(index);
            if (wall->coinGenerationCategory == 2) {
                g_Minigame.wallBallSpecialWallPos = rank;
                break;
            }
            rank++;
        } while (rank < WALL_BALL_WALL_COUNT);
    }
    g_Minigame.wallBallGameState = WALL_BALL_GAME_STATE_DROP_IN_NEW_WALLS;
    g_Minigame._1A80 = 7;
}

// .text:0x00114204 size:0x180 mapped:0x80753298
void wallBallDropInNewWalls(void) {
    int i;
    int active = 0;

    for (i = 0; i < WALL_BALL_WALL_COUNT; i++) {
        MaybeWallBallStruct* wall = WALL_BALL_WALL(i);
        if (wall->_28 == 2) {
            wall->_0 += lbl_3_data_215C8[3];
            wall->_4 += lbl_3_data_215C8[4];
            wall->zPositionOfSomeWall += lbl_3_data_215C8[5];
            if (wall->zPositionOfSomeWall >= wall->_14) {
                wall->zPositionOfSomeWall = wall->_14;
                wall->_28 = 3;
            }
            active++;
        }
    }

    if (active == 0) {
        for (i = 0; i < WALL_BALL_WALL_COUNT; i++) {
            MaybeWallBallStruct* wall = WALL_BALL_WALL(i);
            if (wall->_28 == 1) {
                wall->_0 += lbl_3_data_215C8[0];
                wall->_4 += lbl_3_data_215C8[1];
                wall->zPositionOfSomeWall += lbl_3_data_215C8[2];
                if (wall->_4 <= wall->_10) {
                    wall->_4 = wall->_10;
                    wall->_28 = 3;
                    fn_8004C108((VecXYZ*)&wall->_C, TRUE);
                    callSfx(0x2F4);
                }
                active++;
            }
        }
        if (active == 0) {
            g_Minigame.wallBallGameState = WALL_BALL_GAME_STATE_PITCH_OR_WAITING_FOR_PITCH;
        }
    }
}

// .text:0x00113F14 size:0x2F0 mapped:0x80752FA8
void wallBallHandleWallHit(void) {
    int i;

    if (g_Ball.pitchHangtimeCounter < 1) return;

    for (i = 0; i < WALL_BALL_WALL_COUNT; i++) {
        MaybeWallBallStruct* wall = WALL_BALL_WALL(i);
        f32 ballZ = g_Ball.AtBat_Contact_BallPos.z - g_Ball.groundYForBounces - lbl_3_data_21674[1];
        if (wall->_28 != 3 || !(ballZ <= wall->zPositionOfSomeWall) || g_Minigame.ballStoppedBreakingWallsInd) continue;

        wall->_24 -= g_Minigame.wallBallPitchPowerRemaining;
        if ((s16)wall->_24 <= 0) {
            int coin;
            u8 count;
            g_Minigame.wallBallPitchPowerRemaining = -wall->_24;
            wall->_28 = 4;
            g_Minigame.miniGameLatestPoints[(s8)g_Minigame.minigamePlayerSelectedOrder] += lbl_3_data_21654[7 + wall->coinGenerationCategory];
            count = (u8)wallBall_nCoinsToGenerate[wall->coinGenerationCategory];
            for (coin = 0; coin < WALL_BALL_MAX_COINS; coin++) {
                if (WALL_BALL_COIN_VISIBLE(coin) == FALSE) {
                    f32 angle;
                    WALL_BALL_COIN_FRAMES(coin) = 0;
                    WALL_BALL_COIN_VISIBLE(coin) = TRUE;
                    WALL_BALL_COIN_POSITION(coin)->x = lbl_3_data_215E0[wall->coinRelated[0]].x;
                    WALL_BALL_COIN_POSITION(coin)->y = lbl_3_data_215E0[wall->coinRelated[0]].y;
                    WALL_BALL_COIN_POSITION(coin)->z = lbl_3_data_215E0[wall->coinRelated[0]].z;
                    angle = MTXDegToRad((f32)(rand() % 180));
                    WALL_BALL_COIN_VELOCITY(coin)->x = lbl_3_data_21634[1] * (f32)cos(angle);
                    WALL_BALL_COIN_VELOCITY(coin)->z = lbl_3_data_21634[1] * (f32)sin(angle);
                    WALL_BALL_COIN_VELOCITY(coin)->y = lbl_3_data_21634[0];
                    if ((u8)--count == 0) break;
                }
            }
            setCharacterAnimations(g_Minigame.minigameControlStruct[0].characterIndex[(s8)g_Minigame.minigamePlayerSelectedOrder], 0);
        } else {
            wall->_18 = 0.0f;
            wall->_1C = lbl_3_data_21688[0];
            wall->_20 = lbl_3_data_21688[1];
            callSfx(0x2E1);
            wallBallBounceBallOffWall();
        }
        return;
    }
}

// .text:0x00113EC0 size:0x54 mapped:0x80752F54
void wallBallBounceBallOffWall(void) {
    f32 factor = lbl_3_data_21674[0];
    g_Pitcher.ballVelocity.z = -g_Pitcher.ballVelocity.z;
    g_Pitcher.ballVelocity.x *= factor;
    g_Pitcher.ballVelocity.y *= factor;
    g_Pitcher.ballVelocity.z *= factor;
    g_Minigame.ballStoppedBreakingWallsInd = TRUE;
}

// .text:0x00113D20 size:0x1A0 mapped:0x80752DB4
void wallBallUpdateWallWobble(void) {
    MaybeWallBallStruct* wall;
    int i;
    s8 crossed = FALSE;

    for (i = 0; i < WALL_BALL_WALL_COUNT; i++) {
        f32 previous;
        s8 sign;
        wall = WALL_BALL_WALL(i);
        previous = wall->_18;

        if (previous == 0.0f && wall->_1C == 0.0f) {
            continue;
        }

        wall->_18 = (f32)(wall->_1C * cos(previous) + wall->_18);
        if (wall->_18 >= 0.0f) {
            sign = -1;
        } else {
            sign = 1;
        }

        if (previous < wall->_18) {
            if (previous < 0.0f && wall->_18 >= 0.0f) crossed = TRUE;
        } else {
            if (previous > 0.0f && wall->_18 <= 0.0f) crossed = TRUE;
        }

        if (crossed) {
            wall->_1C *= lbl_3_data_21688[2];
            if (fabs(wall->_1C) < wall->_20 * lbl_3_data_21688[2]) {
                wall->_20 = 0.0f;
                wall->_1C = 0.0f;
                wall->_18 = 0.0f;
            }
            crossed = FALSE;
        }
        wall->_1C += sign * wall->_20;
    }
}

// .text:0x00113A48 size:0x2D8 mapped:0x80752ADC
void wallBallCalc_WallsBroken(void) {
    int i;
    int total;
    int remaining;

    if (g_Ball.pitchHangtimeCounter != 1) return;

    g_Minigame.wallBallPitchPower = lbl_3_data_21654[3];
    if (g_Pitcher.ChargePitchType == 3) {
        g_Minigame.wallBallPitchPower = lbl_3_data_21654[2];
    } else if (g_Pitcher.ChargePitchType >= 2) {
        g_Minigame.wallBallPitchPower = (s16)LinearInterpolateToNewRange(
            g_Pitcher.pitchChargeUp, 0.0f, 1.0f, (f32)lbl_3_data_21654[0], (f32)lbl_3_data_21654[1]);
    }
    g_Minigame.wallBallPitchPowerRemaining = g_Minigame.wallBallPitchPower;

    total = 0;
    {
        u8* indexPtr = (u8*)&g_Minigame;
        i = 0;
        do {
            u8 index = indexPtr[MINIGAME_OFFSET(wallIndexTracker)];
            u8* wallEntry = (u8*)&g_Minigame + index * WALL_BALL_WALL_SIZE;
            total += *(s16*)(wallEntry + MINIGAME_OFFSET(wallBallStruct._24));
            if (wallEntry[MINIGAME_OFFSET(wallBallStruct.coinGenerationCategory)] == 2) {
                i++;
                break;
            }
            i++;
            indexPtr++;
        } while (i < WALL_BALL_WALL_COUNT);
    }
    if (g_Minigame.wallBallPitchPower >= total) {
        if (i < WALL_BALL_WALL_COUNT) {
            u8 index = g_Minigame.wallIndexTracker[i];
            MaybeWallBallStruct* wall = WALL_BALL_WALL(index);
            if (g_Minigame.wallBallPitchPower <= total + wall->_24 - 1) {
                g_Minigame.wallBall_hitNoteBlock = TRUE;
            }
        } else {
            g_Minigame.wallBall_hitNoteBlock = TRUE;
        }
    }
    if (g_Minigame.wallBall_hitNoteBlock == TRUE) return;

    remaining = g_Minigame.wallBallPitchPower;
    for (i = 0; i < WALL_BALL_WALL_COUNT; i++) {
        u8 index = g_Minigame.wallIndexTracker[i];
        MaybeWallBallStruct* wall = WALL_BALL_WALL(index);
        remaining -= wall->_24;
        if ((s16)remaining < 0) break;
    }
    if (--i >= 0) {
        u8 index = g_Minigame.wallIndexTracker[i];
        MaybeWallBallStruct* wall = WALL_BALL_WALL(index);
        if (wall->coinGenerationCategory == 1) {
            g_Minigame._1A8B = i;
            g_Minigame.wallBall_hitBowserWall = TRUE;
        }
    }
}

// .text:0x00113950 size:0xF8 mapped:0x807529E4
void wallBallUpdateCoins(void) {
    int i;
    u8* visible = (u8*)&g_Minigame;
    u8* frames = (u8*)&g_Minigame;
    u8* vector = (u8*)&g_Minigame;
    f32 gravity = lbl_3_data_21634[2];
    f32 floor = lbl_3_data_219B8[14];
    f32 bounce = lbl_3_data_21634[3];
    f32 damping = lbl_3_data_21634[4];
    s16 lifetime = lbl_3_data_2167C[4];

    for (i = 0; i < WALL_BALL_MAX_COINS; i++, visible++, frames += 2, vector += 12) {
        if (visible[WALL_BALL_COIN_VISIBLE_OFFSET]) {
            f32* values = (f32*)vector;
            ++*(s16*)(frames + WALL_BALL_COIN_FRAME_OFFSET);
            values[WALL_BALL_COIN_POSITION_INDEX] += values[WALL_BALL_COIN_VELOCITY_INDEX];
            values[WALL_BALL_COIN_POSITION_INDEX + 1] += values[WALL_BALL_COIN_VELOCITY_INDEX + 1];
            values[WALL_BALL_COIN_POSITION_INDEX + 2] += values[WALL_BALL_COIN_VELOCITY_INDEX + 2];
            values[WALL_BALL_COIN_VELOCITY_INDEX + 1] -= gravity;
            if (values[WALL_BALL_COIN_POSITION_INDEX + 1] < floor) {
                values[WALL_BALL_COIN_POSITION_INDEX + 1] = floor;
                values[WALL_BALL_COIN_VELOCITY_INDEX + 1] = -values[WALL_BALL_COIN_VELOCITY_INDEX + 1] * bounce;
                values[WALL_BALL_COIN_VELOCITY_INDEX] *= damping;
                values[WALL_BALL_COIN_VELOCITY_INDEX + 2] *= damping;
            }
            if (*(s16*)(frames + WALL_BALL_COIN_FRAME_OFFSET) > lifetime) {
                visible[WALL_BALL_COIN_VISIBLE_OFFSET] = FALSE;
            }
        }
    }
}

// .text:0x0011391C size:0x34 mapped:0x807529B0
void wallBallClearInputs(void) {
    memset(&g_Minigame._1D7C, 0, 0x78);
}

// .text:0x001136FC size:0x220 mapped:0x80752790
void wallBallAIPitches(void) {
    MiniGameStruct* minigame = &g_Minigame;
    u8* indexPtr = (u8*)minigame;
    int i = 0;
    u8 difficulty = minigame->minigameControlStruct[0].aIStrength[(s8)minigame->minigamePlayerSelectedOrder];
    s16 minimum = 0;
    s16 maximum = S16_MAX;
    int lastSpecial = 0;

    do {
        u8 index = indexPtr[MINIGAME_OFFSET(wallIndexTracker)];
        u8* wallEntry = (u8*)minigame + index * WALL_BALL_WALL_SIZE;
        minimum += *(s16*)(wallEntry + MINIGAME_OFFSET(wallBallStruct._24));
        if (wallEntry[MINIGAME_OFFSET(wallBallStruct.coinGenerationCategory)] == 2) {
            lastSpecial = i;
            i++;
            break;
        }
        i++;
        indexPtr++;
    } while ((s8)i < WALL_BALL_WALL_COUNT);
    if ((s8)i < WALL_BALL_WALL_COUNT) {
        u8 index = g_Minigame.wallIndexTracker[(s8)i];
        MaybeWallBallStruct* wall = WALL_BALL_WALL(index);
        maximum = minimum + wall->_24 - 1;
    }

    if (RandomInt_Game(100) < lbl_3_data_21694[difficulty][(s8)lastSpecial]) {
        int offset = RandomInt_Game_Range(lbl_3_data_216B0[difficulty][0], lbl_3_data_216B0[difficulty][1]);
        minimum += (s16)offset;
        maximum += (s16)offset;
    }

    if (minimum <= lbl_3_data_21654[2] && lbl_3_data_21654[2] <= maximum) {
        minigame->ai_wbThrowType_bbVertAngle = WALL_BALL_AI_THROW_TYPE_PERFECT;
    } else if (minimum <= lbl_3_data_21654[3] && lbl_3_data_21654[3] <= maximum) {
        minigame->ai_wbThrowType_bbVertAngle = WALL_BALL_AI_THROW_TYPE_CURVE_BALL;
    } else if (maximum >= lbl_3_data_21654[0] && minimum <= lbl_3_data_21654[1]) {
        minigame->ai_wbThrowType_bbVertAngle = WALL_BALL_AI_THROW_TYPE_CHARGE;
        if (minimum < lbl_3_data_21654[0]) minimum = lbl_3_data_21654[0];
        if (maximum > lbl_3_data_21654[1]) maximum = lbl_3_data_21654[1];
        minigame->ai_wbChargePower_bbSwingFrame = RandomInt_Game_Range(minimum, maximum);
    } else {
        minigame->ai_wbThrowType_bbVertAngle = WALL_BALL_AI_THROW_TYPE_OVERCHARGE;
    }

    if (minigame->ai_wbThrowType_bbVertAngle == WALL_BALL_AI_THROW_TYPE_PERFECT && RandomInt_Game(100) < lbl_3_data_216B8[difficulty]) {
        minigame->ai_wbThrowType_bbVertAngle = WALL_BALL_AI_THROW_TYPE_OVERCHARGE;
    }
}

// .text:0x001133C4 size:0x338 mapped:0x80752458
void wallBallMultiplayer_AIControl(void) {
    MiniGameStruct* base = &g_Minigame;
    s8 i;

    i = 0;
    do {
        *((u8*)base + MINIGAME_OFFSET(portOfAIBeingProcessed) + i) = FALSE;
        i++;
    } while (i < 4);

    i = 0;
    do {
        s8 character = *((s8*)base + MINIGAME_OFFSET(minigameControlStruct[0].characterIndex) + i);
        if (character < 0 || character >= 4) continue;
        if ((s8)i != (s8)g_Minigame.minigamePlayerSelectedOrder) continue;
        if (!*((u8*)base + MINIGAME_OFFSET(minigameControlStruct[0].battingHandedness) + i)) continue;

        g_Minigame.portOfAIBeingProcessed[character] = TRUE;
        memset(&g_Minigame._1D7C[character], 0, sizeof(InputStruct));

        switch ((s8)base->wallBallAISwitchVar) {
        case WALL_BALL_AI_STATE_CALCULATE_PITCH:
            wallBallAIPitches();
            *(s8*)&base->minigameAICountDownTillAction = 60;
            base->wallBallAISwitchVar = WALL_BALL_AI_STATE_WAIT_FOR_PITCH;
            break;
        case WALL_BALL_AI_STATE_WAIT_FOR_PITCH:
            if (--*(s8*)&base->minigameAICountDownTillAction > 0) break;
            switch (base->ai_wbThrowType_bbVertAngle) {
            case WALL_BALL_AI_THROW_TYPE_PERFECT:
                base->wallBallAISwitchVar = WALL_BALL_AI_STATE_PERFECT_PITCH;
                break;
            case WALL_BALL_AI_THROW_TYPE_OVERCHARGE:
                base->wallBallAISwitchVar = WALL_BALL_AI_STATE_OVERCHARGE;
                break;
            case WALL_BALL_AI_THROW_TYPE_CHARGE:
                base->wallBallAISwitchVar = WALL_BALL_AI_STATE_CHARGE_PITCH;
                break;
            case WALL_BALL_AI_THROW_TYPE_CURVE_BALL:
            default:
                base->wallBallAISwitchVar = WALL_BALL_AI_STATE_CURVE_BALL;
                break;
            }
            break;
        case WALL_BALL_AI_STATE_PERFECT_PITCH:
            g_Minigame._1D7C[character].newButtonInput |= INPUT_BUTTON_A;
            g_Minigame._1D7C[character].buttonInput |= INPUT_BUTTON_A;
            base->wallBallAISwitchVar = WALL_BALL_AI_STATE_PERFECT_PITCH_FILL_BAR;
            break;
        case WALL_BALL_AI_STATE_PERFECT_PITCH_FILL_BAR:
            if (g_Pitcher.windupCountdownUntilBallReleased < lbl_3_data_5F3C[2]) {
                base->wallBallAISwitchVar = WALL_BALL_AI_STATE_UNKNOWN_9;
            } else {
                g_Minigame._1D7C[character].buttonInput |= INPUT_BUTTON_A;
            }
            break;
        case WALL_BALL_AI_STATE_OVERCHARGE:
            g_Minigame._1D7C[character].newButtonInput |= INPUT_BUTTON_A;
            g_Minigame._1D7C[character].buttonInput |= INPUT_BUTTON_A;
            base->wallBallAISwitchVar = WALL_BALL_AI_STATE_OVERCHARGE_HOLD_A;
            break;
        case WALL_BALL_AI_STATE_OVERCHARGE_HOLD_A:
            g_Minigame._1D7C[character].buttonInput |= INPUT_BUTTON_A;
            break;
        case WALL_BALL_AI_STATE_CHARGE_PITCH:
            g_Minigame._1D7C[character].newButtonInput |= INPUT_BUTTON_A;
            g_Minigame._1D7C[character].buttonInput |= INPUT_BUTTON_A;
            base->wallBallAISwitchVar = WALL_BALL_AI_STATE_CHARGE_PITCH_CHARGE_UP_BAR;
            break;
        case WALL_BALL_AI_STATE_CHARGE_PITCH_CHARGE_UP_BAR:
            if (g_Pitcher.framesAHeldForChargePitches == 0 &&
                (s16)LinearInterpolateToNewRange(
                    1.0f - (f32)g_Pitcher.windupCountdownUntilBallReleased / (f32)g_Pitcher.pitchWindUpCountDown,
                    0.0f, 1.0f, (f32)lbl_3_data_21654[0], (f32)lbl_3_data_21654[1]) >=
                    base->ai_wbChargePower_bbSwingFrame) {
                base->wallBallAISwitchVar = WALL_BALL_AI_STATE_UNKNOWN_9;
            } else {
                g_Minigame._1D7C[character].buttonInput |= INPUT_BUTTON_A;
            }
            break;
        case WALL_BALL_AI_STATE_CURVE_BALL:
            g_Minigame._1D7C[character].newButtonInput |= INPUT_BUTTON_A;
            g_Minigame._1D7C[character].buttonInput |= INPUT_BUTTON_A;
            base->wallBallAISwitchVar = WALL_BALL_AI_STATE_UNKNOWN_9;
            break;
        case WALL_BALL_AI_STATE_UNKNOWN_9:
            break;
        }
    } while (++i < 4);
}
