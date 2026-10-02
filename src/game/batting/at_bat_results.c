#define SQRT2_LINKAGE static
#include "game/batting/at_bat_results.h"
#include "game/ball/ball_trajectory.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/rand.h"

extern UnkSimulationRelatedStruct g_UnkSimulation_31AC0;
extern u8 superstarUnlocked[0x130];

static inline int randomIntGame(int max) {
    int ret;
    int absmax = max;
    if (absmax < 0) {
        absmax = -absmax;
    }

    if (absmax <= 1) {
        return 0;
    }

    g_Ball.StaticRandomInt1 = g_Ball.StaticRandomInt1 - ((u8)g_Ball.StaticRandomInt2) +
                              g_Ball.StaticRandomInt2 / absmax + g_Ball.totalFramesAtPlay;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_Practice.instructionNumber >= 0) {
        return 0;
    }

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        g_Ball.StaticRandomInt1 += rand();
    }

    ret = g_Ball.StaticRandomInt1 % absmax;
    ret = ABS(ret);
    if (max < 0) {
        return -ret;
    } else {
        return ret;
    }
}

static inline int randomIntGameAbs(int max) {
    int ret;
    int orig = max;
    if (max < 0) {
        max = -max;
    }

    if (max <= 1) {
        return 0;
    }

    g_Ball.StaticRandomInt1 = g_Ball.StaticRandomInt1 - ((u8)g_Ball.StaticRandomInt2) +
                              g_Ball.StaticRandomInt2 / max + g_Ball.totalFramesAtPlay;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_Practice.instructionNumber >= 0) {
        return 0;
    }

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        g_Ball.StaticRandomInt1 += rand();
    }

    ret = g_Ball.StaticRandomInt1 % max;
    ret = ABS(ret);
    if (orig < 0) {
        return -ret;
    } else {
        return ret;
    }
}

static inline int randomIntSim(int max) {
    int ret, r2;
    int orig = max;
    if (max < 0) {
        max = -max;
    }

    if (max <= 1) {
        return 0;
    }
    g_UnkSimulation_31AC0._00 = g_UnkSimulation_31AC0._00 + g_d_GameSettings.FrameCountWhileNotAtMainMenu +
                                (g_d_GameSettings.FrameCountWhileNotAtMainMenu >> 1) - g_Ball.StaticRandomInt1 +
                                ((u8)g_Ball.StaticRandomInt2) + (g_UnkSimulation_31AC0._00 / max);
    ret = g_UnkSimulation_31AC0._00 % (u32)max;
    r2 = ABS(ret);

    if (orig < 0) {
        return -r2;
    } else {
        return r2;
    }
}

// .text:0x0009CD90 size:0xE8 mapped:0x806DBE24
void setBatterOutAtBatResult(void) {
    int i;

    if (storedInningInfo.abResultTemporary != 0) {
        return;
    }
    if (g_Strikes.howRunnerReachedBase == 3) {
        storedInningInfo.abResultFinal = 0x10;
        return;
    }
    if (g_Runners[0].runnerOnFieldOrOutOrScored == RUNNER_STATUS_OUT_DURING_PLAY) {
        if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT || g_FieldingLogic.infieldFlyIndicator == 2) {
            if (g_Ball.Hit_VerticalAngle > 0xA0) {
                storedInningInfo.abResultTemporary = 0x12;
            } else {
                storedInningInfo.abResultTemporary = 0x13;
            }
        } else {
            storedInningInfo.abResultTemporary = 0x15;
        }
    }
    for (i = 1; i < 4; i++) {
        if (g_Runners[i].forceOutCd == FORCE_OUT_TYPE_OUT_ON_FORCE) {
            storedInningInfo.abResultTemporary = 0x15;
        }
    }
}

// .text:0x0009CE78 size:0x2C8 mapped:0x806DBF0C
void atBatBuntResult(void) {
    BOOL runnerAdvanced;
    int i;

    if (g_RunningLogic.nOffensivePlayersAtStartOfPlay == 1 || g_Strikes.storedOuts == 2) {
        if ((g_Runners[0].runnerOnFieldOrOutOrScored == RUNNER_STATUS_OUT_DURING_PLAY &&
             g_Strikes.howRunnerReachedBase == 0) ||
            g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT) {
            storedInningInfo.abResultFinal = 0x1D;
            return;
        }
        if (g_Runners[0].forceOutCd == FORCE_OUT_TYPE_NOT_FORCED_TO_ADVANCE) {
            storedInningInfo.abResultFinal = 0x1C;
        }
        return;
    }

    if (g_Runners[3].runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE && g_Runners[3].furthestBaseForcedToGoToOnWalk != 0) {
        if (g_Runners[3].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) {
            if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT) {
                storedInningInfo.abResultTemporary = 0x20;
            } else {
                storedInningInfo.abResultFinal = 0x1E;
            }
            return;
        }
        if (g_Runners[3].runnerOnFieldOrOutOrScored == RUNNER_STATUS_OUT_DURING_PLAY) {
            storedInningInfo.abResultFinal = 0x1F;
        }
        return;
    }

    if (g_Scores._9E > g_Scores.scores[g_Scores.halfInning].byInning[g_Scores.Inning - 1]) {
        storedInningInfo.abResultTemporary = 0x20;
        return;
    }

    if (storedInningInfo.abResultTemporary == 0x22) {
        return;
    }
    if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT) {
        storedInningInfo.abResultTemporary = 0x22;
        return;
    }
    for (i = 1; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE &&
            g_Runners[i].currentBase == g_Runners[i].startingBase_baseAchieved &&
            g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_OUT_DURING_PLAY) {
            storedInningInfo.abResultTemporary = 0x22;
            return;
        }
    }

    runnerAdvanced = FALSE;
    for (i = 1; i < 4; i++) {
        if ((g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD ||
             g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) &&
            g_Runners[i].currentBase != g_Runners[i].startingBase_baseAchieved) {
            runnerAdvanced = TRUE;
            break;
        }
    }
    if (runnerAdvanced) {
        storedInningInfo.abResultTemporary = 0x21;
    }
}

// .text:0x0009D140 size:0x234 mapped:0x806DC1D4
void atBatResultsForOuts(void) {
    int forcedOuts;
    int i;

    if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT || g_FieldingLogic.infieldFlyIndicator == 2) {
        forcedOuts = 0;
        for (i = 1; i < 3; i++) {
            if (g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_OUT_DURING_PLAY && g_Runners[i].outType == 4) {
                forcedOuts++;
            }
        }
        if (forcedOuts == 2) {
            storedInningInfo.abResultFinal = 0x17;
            return;
        }
        if (forcedOuts == 1) {
            storedInningInfo.abResultTemporary = 0x1A;
        }
    }

    if (g_Strikes.storedOuts + 3 == g_Strikes.outs && g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FIELDED) {
        if (g_Strikes.outs == 3 || g_RunningLogic._10 == 0) {
            storedInningInfo.abResultFinal = 0x17;
            if (storedInningInfo.catches[2].outsDuringPossession == 3 ||
                storedInningInfo.catches[3].outsDuringPossession == 3) {
                storedInningInfo.abResultFinal = 0x16;
                return;
            }
        }
    }

    if (g_Strikes.storedOuts + 2 == g_Strikes.outs && g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FIELDED) {
        storedInningInfo.abResultTemporary = 0x19;
        if (storedInningInfo.catches[2].fielderIndex == 2 && storedInningInfo.catches[0].outsDuringPossession == 0 &&
            storedInningInfo.catches[1].outsDuringPossession == 1) {
            storedInningInfo.abResultTemporary = 0x18;
        }
        if (storedInningInfo.catches[3].fielderIndex >= 0 && storedInningInfo.catches[2].outsDuringPossession == 2) {
            storedInningInfo.abResultFinal = storedInningInfo.abResultTemporary;
            return;
        }
    }

    if (g_Strikes.storedOuts + 1 == g_Strikes.outs && g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FIELDED &&
        storedInningInfo.catches[2].fielderIndex == 2 && storedInningInfo.catches[0].outsDuringPossession == 0) {
        s8 base = storedInningInfo.catches[1].baseStandingOn;
        if (g_Runners[(base + 3) & 3].forcedToAdvanceInd != 0 && base >= 0 && base != 1 &&
            storedInningInfo.catches[1].outsDuringPossession == 1 &&
            storedInningInfo.catches[2].outsDuringPossession == 1 && storedInningInfo.catches[2].baseStandingOn == 1) {
            storedInningInfo.abResultTemporary = 0x14;
        }
    }
}

// .text:0x0009D374 size:0x1DC mapped:0x806DC408
BOOL noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance(void) {
    s16 baseEarned;
    int runsThisPlay;
    BOOL runnerScoredOnlyRun = FALSE;

    if (g_Strikes.howRunnerReachedBase == 1) {
        runsThisPlay = g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total - g_Scores._A0;
        if (runsThisPlay == 1 && g_Runners[0].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) {
            runnerScoredOnlyRun = TRUE;
        }
        baseEarned = g_Runners[0].baseNumberEarned_NotIncludingFieldersChoice;
        if (baseEarned == 0 && g_Runners[0].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) {
            storedInningInfo.abResultFinal = 5;
        } else if (baseEarned == 3) {
            if (runsThisPlay != 0 && !runnerScoredOnlyRun) {
                storedInningInfo.abResultFinal = 6;
            } else {
                storedInningInfo.abResultTemporary = 0xB;
            }
        } else if (baseEarned == 2) {
            if (runsThisPlay != 0 && !runnerScoredOnlyRun) {
                storedInningInfo.abResultFinal = 7;
            } else {
                storedInningInfo.abResultTemporary = 0xC;
            }
        } else if (baseEarned == 1) {
            s8 zone = g_Ball.ballZoneWhenCaught;
            if (zone >= 0 && zone <= 1) {
                if (runsThisPlay != 0 && !runnerScoredOnlyRun) {
                    storedInningInfo.abResultFinal = 9;
                } else {
                    storedInningInfo.abResultTemporary = 0xE;
                }
            } else {
                if (runsThisPlay != 0 && !runnerScoredOnlyRun) {
                    storedInningInfo.abResultFinal = 8;
                } else {
                    storedInningInfo.abResultTemporary = 0xD;
                }
            }
        } else {
            if (runsThisPlay != 0 && !runnerScoredOnlyRun) {
                storedInningInfo.abResultTemporary = 0xA;
            } else {
                storedInningInfo.abResultTemporary = 0xF;
            }
        }
        return TRUE;
    }
    return FALSE;
}

// .text:0x0009D550 size:0x44 mapped:0x806DC5E4
void fn_3_9D550(void) {
    if (g_Ball.maybeBuntInd != 0 && g_Strikes.strikes >= 3) {
        storedInningInfo.abResultFinal = 0x27;
    } else {
        storedInningInfo.abResultFinal = 0x2C;
    }
}

// .text:0x0009D594 size:0x6C mapped:0x806DC628
void fn_3_9D594(void) {
    switch (g_RunningLogic.nOffensivePlayersAtStartOfPlay) {
        case 4:
            storedInningInfo.abResultFinal = 1;
            break;
        case 3:
            storedInningInfo.abResultFinal = 2;
            break;
        case 2:
            storedInningInfo.abResultFinal = 3;
            break;
        default:
            storedInningInfo.abResultFinal = 4;
            break;
    }
}

// .text:0x0009D600 size:0xA4 mapped:0x806DC694
void setStrikeoutOrWalkAtBatResult(void) {
    if (g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT) {
        if (g_Batter.missedBuntStatus != 0) {
            storedInningInfo.abResultTemporary = 0x26;
        } else if (g_Batter.missSwingOrBunt != 0) {
            storedInningInfo.abResultTemporary = 0x24;
        } else {
            storedInningInfo.abResultTemporary = 0x25;
        }
    } else if (g_Pitcher.strikeOutOrWalk == AT_BAT_END_WALK) {
        storedInningInfo.abResultTemporary = 0x2A;
    } else if (g_Pitcher.strikeOutOrWalk == AT_BAT_END_HIT_BY_PITCH) {
        storedInningInfo.abResultFinal = 0x2B;
    }
}

// .text:0x0009D6A4 size:0x4B8 mapped:0x806DC738
void setAtBatResult(void) {
    BOOL fielderTracked = FALSE;
    int i;
    s16 fielder;
    s16 coverage;

    if (g_Stats.replayInd != 0) {
        return;
    }
    if (storedInningInfo.abResultFinal == 0) {
        if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd == 4) {
            storedInningInfo.abResultFinal = 0x28;
        } else if (g_GameLogic.gameStatus == 1) {
            setStrikeoutOrWalkAtBatResult();
        } else if (g_Ball.deadBallReason == 1) {
            fn_3_9D594();
        } else if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FOUL) {
            fn_3_9D550();
        } else {
            if (g_GameLogic.gameStatus == 2) {
                fielder = g_Ball.fielderWBallIndex;
                if (fielder >= 0) {
                    if (storedInningInfo.fielderWithBallIndex == -1) {
                        for (i = 0; i < 5; i++) {
                            if (storedInningInfo.catches[i].fielderIndex == -1) {
                                storedInningInfo.catches[i].fielderIndex = fielder;
                                storedInningInfo.catches[i].outsDuringPossession = g_Strikes.outs - g_Strikes.storedOuts;
                                coverage = g_Fielders[fielder].locationResponsibleForCovering;
                                if (coverage >= 0 && coverage <= 3) {
                                    switch (coverage) {
                                        case 0:
                                            if ((g_RunningLogic._02 & 0x1111) == 0x1111) {
                                                storedInningInfo.catches[i].baseStandingOn = 0;
                                            }
                                            break;
                                        case 1:
                                            storedInningInfo.catches[i].baseStandingOn = 1;
                                            break;
                                        case 2:
                                            if ((g_RunningLogic._02 & 0x11) == 0x11) {
                                                storedInningInfo.catches[i].baseStandingOn = 2;
                                            }
                                            break;
                                        default:
                                            if ((g_RunningLogic._02 & 0x111) == 0x111) {
                                                storedInningInfo.catches[i].baseStandingOn = 3;
                                            }
                                            break;
                                    }
                                }
                                break;
                            }
                        }
                        fielderTracked = TRUE;
                    } else if (storedInningInfo.fielderWithBallIndex == fielder) {
                        for (i = 4; i >= 0; i--) {
                            if (storedInningInfo.catches[i].fielderIndex == fielder) {
                                if (g_Ball.timeSinceBallPickedUp <= 60) {
                                    storedInningInfo.catches[i].outsDuringPossession =
                                        g_Strikes.outs - g_Strikes.storedOuts;
                                }
                                break;
                            }
                        }
                        fielderTracked = TRUE;
                    }
                }
                storedInningInfo.fielderWithBallIndex = fielder;
            }
            if (g_Ball.maybeBuntInd != 0) {
                atBatBuntResult();
            } else if (!noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance()) {
                if (fielderTracked) {
                    atBatResultsForOuts();
                }
                setBatterOutAtBatResult();
            }
        }
    }
    categorizeBallTrajectory();
    if (storedInningInfo.abResultFinal != 0) {
        storedInningInfo.abResultTemporary = storedInningInfo.abResultFinal;
    }
}

// .text:0x0009DB5C size:0x88 mapped:0x806DCBF0
void setDefaultPlayTrackingVariables1(void) {
    int i;

    for (i = 4; i > 0; i--) {
        storedInningInfo._06[i] = storedInningInfo._06[i - 1];
    }
    storedInningInfo._06[0] = storedInningInfo.abResultFinal;
    storedInningInfo.abResultTemporary = 0;
    storedInningInfo.abResultFinal = 0;
    storedInningInfo.situation = 0;
    for (i = 0; i < 5; i++) {
        storedInningInfo.catches[i].fielderIndex = -1;
        storedInningInfo.catches[i].outsDuringPossession = -1;
        storedInningInfo.catches[i].baseStandingOn = -1;
    }
    storedInningInfo.fielderWithBallIndex = -1;
}

// .text:0x0009DBE4 size:0x34 mapped:0x806DCC78
void initializeInningTrackers(void) {
    storedInningInfo.inningOfFirstRun = 0;
    storedInningInfo.inningOfLastTie = 0;
    storedInningInfo.comebackCounter = 0;
    storedInningInfo.inningOfComeback = 0;
    storedInningInfo.comebackCounter2 = 0;
    storedInningInfo.inningOfLeadTakenBack = 0;
    storedInningInfo.leadsTakenBack = 0;
    storedInningInfo.inningOfGoAheadRun = 0;
    storedInningInfo.goAheadRunOccurrences = 0;
}

// .text:0x0009DC18 size:0x460 mapped:0x806DCCAC
void shuffleU8Array(u8* values, int count, BOOL useGameRandom) {
    int result[10];
    u32 u;

    for (u = 0; u < count; u++) {
        result[u] = values[u];
    }
    shuffleIntArray(result, count, useGameRandom);
    for (u = 0; u < count; u++) {
        values[u] = result[u];
    }
}

// .text:0x0009E078 size:0x2F0 mapped:0x806DD10C
void shuffleIntArray(int* values, int count, BOOL useGameRandom) {
    int source[20];
    int taken[20];
    int i;
    int j;
    int k;
    int r;

    for (i = 0; i < count; i++) {
        source[i] = values[i];
        taken[i] = 0;
    }
    for (k = count - 1; k >= 0; k--) {
        if (useGameRandom) {
            r = randomIntGameAbs(k + 1);
        } else {
            r = randomIntSim(k + 1);
        }
        for (j = 0; j < count; j++) {
            if (taken[j] == 0) {
                if (r == 0) {
                    values[k] = source[j];
                    taken[j] = 1;
                    break;
                }
                r--;
            }
        }
    }
}

// .text:0x0009E368 size:0x238 mapped:0x806DD3FC
int RandomIndexFromIntWeights(int* weights, int count) {
    int buf[10];
    int total = 0;
    int i;
    int r;

    for (i = 0; i < count; i++) {
        buf[i] = weights[i];
        total += buf[i];
    }
    r = randomIntGame(total);
    for (i = 0; i < count; i++) {
        if (r < buf[i]) {
            return i;
        }
        r -= buf[i];
    }
    return 0;
}

// .text:0x0009E5A0 size:0x234 mapped:0x806DD634
int RandomIndexFromWeights(u8* weights, int count) {
    int buf[10];
    int total = 0;
    int i;
    int r;

    for (i = 0; i < count; i++) {
        buf[i] = weights[i];
        total += buf[i];
    }
    r = randomIntGame(total);
    for (i = 0; i < count; i++) {
        if (r < buf[i]) {
            return i;
        }
        r -= buf[i];
    }
    return 0;
}

// .text:0x0009E7D4 size:0x60 mapped:0x806DD868
void iterateBatter(int team) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_GameLogic.secondaryGameMode == 0xF) {
        return;
    }
    if (g_GameLogic.currentBatterPerTeam[team] == 9) {
        g_GameLogic.currentBatterPerTeam[team] = 1;
    } else {
        g_GameLogic.currentBatterPerTeam[team]++;
    }
}

// .text:0x0009E834 size:0x1E8 mapped:0x806DD8C8
BOOL fn_3_9E834(void) {
    int i;

    if (!g_d_GameSettings.exhibitionMatchInd) {
        for (i = 0; i < 54; i++) {
            if (((u8*)starMissionCompletionTracker)[0x43D6 + i] != 0) {
                return TRUE;
            }
        }
    } else {
        for (i = 0; i < 54; i++) {
            if (superstarUnlocked[i] != 0) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

// .text:0x0009EA1C size:0xC8 mapped:0x806DDAB0
BOOL fn_3_9EA1C(int team) {
    int i;

    for (i = 1; i < 10; i++) {
        if (g_GameLogic.battingOrderAndPositionMapping[team][i][1] % 10 == 9) {
            return TRUE;
        }
    }
    return FALSE;
}
