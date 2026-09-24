#include "game/baserunning/play_result_tracking.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/fielding/fielder_ai.h"

#include "game/match_setup/star_missions.h"
#include "static/UnknownHomes_Static.h"

extern VecXZ base_MoundCoordinates[5];
// Per team, per roster slot: outs recorded while the pitcher's team led.
extern u8 pitchingInfo_A_H[2][9][5];
extern void steal_pickoff_incrementSteal_runsStats(void);
extern void updateStatsBasedOnABResult(int rosterID, int result, int fielder, int rbis);

// .text:0x00077914 size:0xC60 mapped:0x806B69A8
void postPlayTrackStats(void) {
    StatisticsPitcher* pitcherStats;
    u8* stat;
    s16 result = AT_BAT_RESULT_NONE;
    int fielder = -1;
    int rbis = 0;
    int pitcher;
    int battingTeam;
    int battingSlot;
    int inning;
    u8 pickoffSteal;
    u8 end;
    s8 base;
    int team;
    int (*slot)[2];
    int i;
    int k;

    pitcher = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0];
    pitcherStats = &PitcherStats_P1_P2[g_GameLogic.teamFielding][pitcher];
    if (g_Stats.replayInd != 0) {
        return;
    }
    if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FOUL && !g_Ball.maybebuntOn2Strikes) {
        return;
    }

    if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != PICKOFF_STEAL_CODE_NONE &&
        g_FieldingLogic.liveBallBcOfPickoffOrStealCd != 4) {
        steal_pickoff_incrementSteal_runsStats();
        battingTeam = g_GameLogic.homeTeamBattingInd_fieldingTeam;
        battingSlot = g_GameLogic.teamBatting;
        inning = g_Scores.Inning;
        pickoffSteal = g_FieldingLogic.liveBallBcOfPickoffOrStealCd;
        StatsScreenScores.scores[battingSlot].byInning[inning - 1] = g_Scores.scores[battingTeam].byInning[inning - 1];
        StatsScreenScores.scores[battingSlot].total = g_Scores.scores[battingTeam].total;
        StatsScreenScores.hits[battingSlot].byInning[inning - 1] = g_Scores.hits[battingTeam].byInning[inning - 1];
        StatsScreenScores.hits[battingSlot].total = g_Scores.hits[battingTeam].total;
        StatsScreenScores.stealsAgainst[battingSlot] = g_Scores.stealSuccesses[battingTeam];
        StatsScreenScores.stealsAgainst[g_GameLogic.teamFielding] =
            g_Scores.stealSuccesses[g_GameLogic.awayTeamBattingInd_battingTeam];

        if (pickoffSteal == PICKOFF_STEAL_CODE_STEAL) {
            if (g_FieldingLogic.runnerTargetedOnThrowDuringSteal != 0) {
                stat = &BatterStats_P1_P2[g_GameLogic.teamFielding][g_Fielders[1].rosterLocation]
                            .fielder_playsInvolvedIn;
                if (*stat < 0xFE) {
                    (*stat)++;
                } else {
                    *stat = 0xFF;
                }
            }
            if (g_FieldingLogic.x127_pickoff_0 == PICKOFF_TARGET_STATUS_STEALING_RUNNER_ADVANCED) {
                if (g_Scores.stealSuccesses[g_GameLogic.awayTeamBattingInd_battingTeam] < 0xFE) {
                    g_Scores.stealSuccesses[g_GameLogic.awayTeamBattingInd_battingTeam]++;
                } else {
                    g_Scores.stealSuccesses[g_GameLogic.awayTeamBattingInd_battingTeam] = 0xFF;
                }
                stat = &BatterStats_P1_P2[g_GameLogic.teamFielding][g_Fielders[1].rosterLocation]
                            .runnersAdvancedAgainst;
                if (*stat < 0xFE) {
                    (*stat)++;
                } else {
                    *stat = 0xFF;
                }
            }
        }
        if (pickoffSteal == PICKOFF_STEAL_CODE_PICKOFF) {
            if (g_FieldingLogic.runnerTargetedOnThrowDuringSteal != 0) {
                stat = &BatterStats_P1_P2[g_GameLogic.teamFielding][g_Fielders[0].rosterLocation]
                            .fielder_playsInvolvedIn;
                if (*stat < 0xFE) {
                    (*stat)++;
                } else {
                    *stat = 0xFF;
                }
            }
            if (g_FieldingLogic.x127_pickoff_0 == PICKOFF_TARGET_STATUS_STEALING_RUNNER_ADVANCED) {
                if (g_Scores.stealSuccesses[g_GameLogic.awayTeamBattingInd_battingTeam] < 0xFE) {
                    g_Scores.stealSuccesses[g_GameLogic.awayTeamBattingInd_battingTeam]++;
                } else {
                    g_Scores.stealSuccesses[g_GameLogic.awayTeamBattingInd_battingTeam] = 0xFF;
                }
                stat = &BatterStats_P1_P2[g_GameLogic.teamFielding][g_Fielders[0].rosterLocation]
                            .runnersAdvancedAgainst;
                if (*stat < 0xFE) {
                    (*stat)++;
                } else {
                    *stat = 0xFF;
                }
            }
        }
        if (g_Pitcher.strikeOutOrWalk != AT_BAT_END_STRIKEOUT && g_Pitcher.strikeOutOrWalk != AT_BAT_END_WALK) {
            if (g_Strikes.outs > g_Strikes.storedOuts) {
                if (pitcherStats->outsAsPitcher < 0xFF - g_Strikes.outs - g_Strikes.storedOuts) {
                    pitcherStats->outsAsPitcher += g_Strikes.outs - g_Strikes.storedOuts;
                } else {
                    pitcherStats->outsAsPitcher = 0xFF;
                }
                if (g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total >
                    g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total) {
                    pitchingInfo_A_H[g_GameLogic.awayTeamBattingInd_battingTeam][pitcher][0] +=
                        g_Strikes.outs - g_Strikes.storedOuts;
                }
            }
            storedInningInfo.rbisWaitingToBeAddedToScore = 0;
            goto updatePositions;
        }
    }

    end = g_Pitcher.strikeOutOrWalk;
    if (end == AT_BAT_END_STRIKEOUT || storedInningInfo.playResultCode == PLAY_RESULT_CODE_FOUL_BUNT_TWO_STRIKES) {
        result = AT_BAT_RESULT_STRIKEOUT;
        stat = &storedInningInfo.consecutiveStrikeouts[g_GameLogic.awayTeamBattingInd_battingTeam];
        if (*stat < 0xFE) {
            (*stat)++;
        } else {
            *stat = 0xFF;
        }
    } else {
        storedInningInfo.consecutiveStrikeouts[g_GameLogic.awayTeamBattingInd_battingTeam] = 0;
        if (end == AT_BAT_END_WALK) {
            result = AT_BAT_RESULT_WALK;
            if (storedInningInfo.consecutiveWalks < 0xFE) {
                storedInningInfo.consecutiveWalks++;
            } else {
                storedInningInfo.consecutiveWalks = 0xFF;
            }
            if (storedInningInfo.consecutiveWalksOrHBP < 0xFE) {
                storedInningInfo.consecutiveWalksOrHBP++;
            } else {
                storedInningInfo.consecutiveWalksOrHBP = 0xFF;
            }
        } else {
            storedInningInfo.consecutiveWalks = 0;
            if (end == AT_BAT_END_HIT_BY_PITCH) {
                result = AT_BAT_RESULT_HIT_BY_PITCH;
                if (storedInningInfo.consecutiveHBP < 0xFE) {
                    storedInningInfo.consecutiveHBP++;
                } else {
                    storedInningInfo.consecutiveHBP = 0xFF;
                }
                if (storedInningInfo.consecutiveWalksOrHBP < 0xFE) {
                    storedInningInfo.consecutiveWalksOrHBP++;
                } else {
                    storedInningInfo.consecutiveWalksOrHBP = 0xFF;
                }
            } else {
                storedInningInfo.consecutiveHBP = 0;
                storedInningInfo.consecutiveWalksOrHBP = 0;
                if (g_Ball.fielderWithBallIndexStored2 == -1) {
                    if (g_Ball.fielderWithBallIndexStored >= 0) {
                        g_Ball.fielderWithBallIndexStored2 = g_Ball.fielderWithBallIndexStored;
                    } else if (g_Ball.ballZoneAwayFromHome >= BALL_ZONE_OF_SHALLOW) {
                        if (g_Ball.ballAngleFromHome < 0x340) {
                            g_Ball.fielderWithBallIndexStored = 8;
                            g_Ball.fielderWithBallIndexStored2 = 8;
                        } else if (g_Ball.ballAngleFromHome < 0x4C0) {
                            g_Ball.fielderWithBallIndexStored = 7;
                            g_Ball.fielderWithBallIndexStored2 = 7;
                        } else {
                            g_Ball.fielderWithBallIndexStored = 6;
                            g_Ball.fielderWithBallIndexStored2 = 6;
                        }
                    } else {
                        if (g_Ball.AtBat_Contact_BallPos.z < 8.0f) {
                            g_Ball.fielderWithBallIndexStored = 1;
                            g_Ball.fielderWithBallIndexStored2 = 1;
                        }
                        if (g_Ball.ballAngleFromHome < 0x300) {
                            g_Ball.fielderWithBallIndexStored = 2;
                            g_Ball.fielderWithBallIndexStored2 = 2;
                        } else if (g_Ball.ballAngleFromHome < 0x400) {
                            g_Ball.fielderWithBallIndexStored = 3;
                            g_Ball.fielderWithBallIndexStored2 = 3;
                        } else if (g_Ball.ballAngleFromHome < 0x500) {
                            g_Ball.fielderWithBallIndexStored = 5;
                            g_Ball.fielderWithBallIndexStored2 = 5;
                        } else {
                            g_Ball.fielderWithBallIndexStored = 4;
                            g_Ball.fielderWithBallIndexStored2 = 4;
                        }
                    }
                }
                if (storedInningInfo.playResultCode == PLAY_RESULT_CODE_SAC_FLY_SCORED) {
                    result = AT_BAT_RESULT_SAC_FLY;
                } else if (storedInningInfo.playResultCode == PLAY_RESULT_CODE_ALL_RUNNERS_SAFE) {
                    result = AT_BAT_RESULT_BUNT;
                } else if (g_FieldingLogic.processErrorCode == FIELDING_ERROR_CONFIRMED) {
                    fielder = g_FieldingLogic.lastThrowingFielder;
                    result = AT_BAT_RESULT_ERROR;
                } else if (storedInningInfo.runnersTargetedWhileBatterForceable == RUNNERS_TARGETED_NOT_THROWN_TO_BASE &&
                           g_Runners[0].forceOutCd != FORCE_OUT_TYPE_OUT_ON_FORCE) {
                    fielder = g_FieldingLogic.lastThrowingFielder;
                    result = AT_BAT_RESULT_ERROR;
                } else if (storedInningInfo.runnersTargetedWhileBatterForceable > 0) {
                    result = AT_BAT_RESULT_FIELDERS_CHOICE;
                } else if ((s8)storedInningInfo.batterResultBase >= 1) {
                    base = storedInningInfo.batterResultBase;
                    result = base + (AT_BAT_RESULT_SINGLE - 1);
                    if (base <= 3) {
                        fielder = g_Ball.fielderWithBallIndexStored2;
                    }
                    g_Scores.hits[g_GameLogic.homeTeamBattingInd_fieldingTeam].byInning[g_Scores.Inning - 1]++;
                    g_Scores.hits[g_GameLogic.homeTeamBattingInd_fieldingTeam].total++;
                    if (base >= 4 && g_Ball.deadBallReason == DEAD_BALL_REASON_HOME_RUN) {
                        if (storedInningInfo.consecutiveHits < 0xFE) {
                            storedInningInfo.consecutiveHits++;
                        } else {
                            storedInningInfo.consecutiveHits = 0xFF;
                        }
                    } else {
                        storedInningInfo.consecutiveHits = 0;
                    }
                } else if (storedInningInfo.nRunnersForcedOut >= 2) {
                    result = AT_BAT_RESULT_DOUBLE_PLAY;
                } else if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT || g_FieldingLogic.infieldFlyIndicator == 2) {
                    if (g_Ball.fairBallInd == 1) {
                        result = AT_BAT_RESULT_CAUGHT_INFIELD_FLY;
                    } else if (g_Ball.Hit_VerticalAngle > 160) {
                        result = AT_BAT_RESULT_CAUGHT;
                    } else {
                        result = AT_BAT_RESULT_CAUGHT_LINE_DRIVE;
                    }
                    fielder = g_Ball.fielderWithBallIndexStored2;
                } else {
                    result = AT_BAT_RESULT_OUT;
                    fielder = g_Ball.fielderWithBallIndexStored2;
                }
            }
        }
    }

    if (g_GameLogic.secondaryGameMode != SECONDARY_GAME_MODE_NONE) {
        return;
    }
    if ((s8)storedInningInfo.batterResultBase >= 1) {
        if (storedInningInfo.consecutiveHits2 < 0xFE) {
            storedInningInfo.consecutiveHits2++;
        } else {
            storedInningInfo.consecutiveHits2 = 0xFF;
        }
    } else {
        storedInningInfo.consecutiveHits2 = 0;
        storedInningInfo.consecutiveHits = 0;
    }
    if (result != AT_BAT_RESULT_DOUBLE_PLAY && g_FieldingLogic.liveBallBcOfPickoffOrStealCd != 4) {
        rbis = storedInningInfo.rbisWaitingToBeAddedToScore;
    }
    storedInningInfo.fielderWithBallIndexStored = g_Ball.fielderWithBallIndexStored2;
    storedInningInfo.batterIDStored = g_Batter.rosterID;
    storedInningInfo.rbisWaitingToBeAddedToScoreStored = rbis;
    storedInningInfo.storedOuts = g_Strikes.storedOuts;
    storedInningInfo.atBatResultHistory[4] = storedInningInfo.atBatResultHistory[3];
    storedInningInfo.atBatResultHistory[3] = storedInningInfo.atBatResultHistory[2];
    storedInningInfo.atBatResultHistory[2] = storedInningInfo.atBatResultHistory[1];
    storedInningInfo.atBatResultHistory[1] = storedInningInfo.atBatResultHistory[0];
    storedInningInfo.atBatResultHistory[0] = result;
    if (result == AT_BAT_RESULT_STRIKEOUT || (u16)(result - AT_BAT_RESULT_OUT) <= 2 ||
        result == AT_BAT_RESULT_DOUBLE_PLAY || result == AT_BAT_RESULT_CAUGHT_INFIELD_FLY) {
        storedInningInfo.consecutiveABsWithOuts[g_GameLogic.homeTeamBattingInd_fieldingTeam]++;
    } else {
        storedInningInfo.consecutiveABsWithOuts[g_GameLogic.homeTeamBattingInd_fieldingTeam] = 0;
    }
    if (storedInningInfo.nABs[g_GameLogic.awayTeamBattingInd_battingTeam * 2] < 0x7FFE) {
        storedInningInfo.nABs[g_GameLogic.awayTeamBattingInd_battingTeam * 2]++;
    } else {
        storedInningInfo.nABs[g_GameLogic.awayTeamBattingInd_battingTeam * 2] = 0x7FFF;
    }
    updateStatsBasedOnABResult(g_Batter.rosterID, result, fielder, rbis);
    g_Stats.prevAtBatResult = result;
    if (g_RunningLogic.runnersInScoringPosition != 0) {
        storedInningInfo._69[g_GameLogic.homeTeamBattingInd_fieldingTeam]
                            [g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam]] = 1;
    } else {
        storedInningInfo._69[g_GameLogic.homeTeamBattingInd_fieldingTeam]
                            [g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam]] = 0;
    }

updatePositions:
    team = g_GameLogic.teamFielding;
    slot = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam];
    for (i = 0; i <= 9; i++) {
        for (k = 0; k < 8; k++) {
            if (BatterStats_P1_P2[team][slot[i][0]].currentPosition[k] != 0) {
                break;
            }
        }
        if (k < 8) {
            continue;
        }
        if (i == 0) {
            BatterStats_P1_P2[team][slot[i][0]].currentPosition[0] = 1;
            continue;
        }
        switch (slot[i][1]) {
        case 0:
            BatterStats_P1_P2[team][slot[i][0]].currentPosition[0] = 1;
            break;
        case 1:
            BatterStats_P1_P2[team][slot[i][0]].currentPosition[1] = 1;
            break;
        case 2:
            BatterStats_P1_P2[team][slot[i][0]].currentPosition[2] = 1;
            break;
        case 3:
            BatterStats_P1_P2[team][slot[i][0]].currentPosition[3] = 1;
            break;
        case 4:
            BatterStats_P1_P2[team][slot[i][0]].currentPosition[4] = 1;
            break;
        case 5:
            BatterStats_P1_P2[team][slot[i][0]].currentPosition[5] = 1;
            break;
        case 6:
        case 7:
        case 8:
            BatterStats_P1_P2[team][slot[i][0]].currentPosition[6] = 1;
            break;
        case 9:
            BatterStats_P1_P2[team][slot[i][0]].currentPosition[7] = 1;
            break;
        }
    }
    if ((s8)g_FieldingLogic.bigPlayFielderIndex >= 0) {
        stat = &BatterStats_P1_P2[g_GameLogic.teamFielding]
                                               [g_Fielders[(s8)g_FieldingLogic.bigPlayFielderIndex].rosterLocation]
                    .BigPlays;
        if (*stat < 0xFE) {
            (*stat)++;
        } else {
            *stat = 0xFF;
        }
    }
    if (!g_d_GameSettings.exhibitionMatchInd) {
        starMissionsOffensive_StarChange_DoublePlay(result, rbis);
    }
}

// .text:0x00078574 size:0x1BC mapped:0x806B7608
void pickoff_infieldThrow_related(int throwingFielder) {
    int late = FALSE;
    int target;
    int runner;
    int frames;

    if (g_FieldingLogic.runnerTargetedOnThrowDuringSteal == -1) {
        if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd == PICKOFF_STEAL_CODE_PICKOFF) {
            if (g_Runners[g_FieldingLogic.locationThrownTo].runnerOnFieldOrOutOrScored != RUNNER_STATUS_ON_FIELD) {
                g_FieldingLogic.x127_pickoff_0 = PICKOFF_TARGET_STATUS_NONE;
                return;
            }
            g_FieldingLogic.runnerTargetedOnThrowDuringSteal = g_FieldingLogic.locationThrownTo;
        }
        if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd == PICKOFF_STEAL_CODE_STEAL) {
            runner = (g_FieldingLogic.locationThrownTo + 3) & 3;
            if (g_Runners[runner].runnerOnFieldOrOutOrScored != RUNNER_STATUS_ON_FIELD) {
                g_FieldingLogic.x127_pickoff_0 = PICKOFF_TARGET_STATUS_NONE;
                return;
            }
            g_FieldingLogic.runnerTargetedOnThrowDuringSteal = runner;
        }
    }
    if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != PICKOFF_STEAL_CODE_NONE) {
        return;
    }
    if (g_Ball.numberOfThrowsDuringPlay > 1) {
        return;
    }
    target = g_FieldingLogic.locationThrownTo;
    if (g_FieldingLogic.locationThrownTo < 0) {
        return;
    }
    if (target <= 3) {
        if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT) {
            return;
        }
        if ((s8)storedInningInfo.batterResultBase >= 1) {
            return;
        }
        if (g_Ball.ballZoneAwayFromHome >= BALL_ZONE_OF_SHALLOW) {
            return;
        }
        if (g_Strikes.outs > g_Strikes.storedOuts) {
            return;
        }
        runner = (target + 3) & 3;
        if (g_Runners[runner].runnerOnFieldOrOutOrScored != RUNNER_STATUS_ON_FIELD) {
            return;
        }
        frames = g_Ball.framesUntilThrowReachesDest + 15;
        if (g_Runners[runner].forceOutCd == FORCE_OUT_TYPE_NOT_FORCED_TO_ADVANCE) {
            if (target != g_Runners[runner].baseRunningTowards) {
                return;
            }
            if (target == g_Runners[runner].currentBase) {
                return;
            }
            frames += 30;
        }
        if (frames < g_Runners[runner].framesToNextBase) {
            late = TRUE;
        }
        if (late) {
            g_FieldingLogic.lastThrowingFielder = throwingFielder;
            g_FieldingLogic.processErrorCode = runner + FIELDING_ERROR_PENDING_LATE_THROW_R0;
        }
    }
}

// .text:0x00078730 size:0x394 mapped:0x806B77C4
void monitorForErrors(void) {
    int target;
    int idx;
    u8 error;
    s16 contact;

    if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != PICKOFF_STEAL_CODE_NONE) {
        if (g_FieldingLogic.x127_pickoff_0 != PICKOFF_TARGET_STATUS_ONGOING) {
            return;
        }
        if (g_FieldingLogic.runnerTargetedOnThrowDuringSteal < 0 && g_Ball.framesSinceHit > 160) {
            g_FieldingLogic.x127_pickoff_0 = PICKOFF_TARGET_STATUS_NONE;
            return;
        }
        if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd == PICKOFF_STEAL_CODE_PICKOFF &&
            g_FieldingLogic.runnerTargetedOnThrowDuringSteal >= 0) {
            target = g_FieldingLogic.runnerTargetedOnThrowDuringSteal;
            if (target <= 3) {
                if (g_Ball.looseBall_codeForHowLongUntilSomeoneWillGetIt == 1) {
                    g_FieldingLogic.runnerTargetedOnThrowDuringSteal += 4;
                }
            } else if (target <= 7) {
                idx = target - 4;
                if (g_Runners[idx].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) {
                    g_FieldingLogic.x127_pickoff_0 = PICKOFF_TARGET_STATUS_PICKED_OFF_RUNNER_ADVANCED;
                    return;
                }
                if (g_Runners[idx].baseStandingOn >= idx + 1) {
                    g_FieldingLogic.x127_pickoff_0 = PICKOFF_TARGET_STATUS_PICKED_OFF_RUNNER_ADVANCED;
                    return;
                }
            }
        }
        if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != PICKOFF_STEAL_CODE_STEAL) {
            return;
        }
        if (g_FieldingLogic.runnerTargetedOnThrowDuringSteal < 0) {
            return;
        }
        target = g_FieldingLogic.runnerTargetedOnThrowDuringSteal;
        if (target <= 3) {
            if (target == 3) {
                g_FieldingLogic.x127_pickoff_0 = PICKOFF_TARGET_STATUS_NONE;
                return;
            }
            if (g_Ball.looseBall_codeForHowLongUntilSomeoneWillGetIt != 1) {
                return;
            }
            g_FieldingLogic.runnerTargetedOnThrowDuringSteal += 4;
            return;
        }
        if (target > 7) {
            return;
        }
        idx = target - 4;
        if (g_Runners[idx].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) {
            g_FieldingLogic.x127_pickoff_0 = PICKOFF_TARGET_STATUS_STEALING_RUNNER_ADVANCED;
            return;
        }
        if (g_Runners[idx].baseStandingOn >= idx + 2) {
            g_FieldingLogic.x127_pickoff_0 = PICKOFF_TARGET_STATUS_STEALING_RUNNER_ADVANCED;
            return;
        }
        return;
    }

    error = g_FieldingLogic.processErrorCode;
    if (error == FIELDING_ERROR_CONFIRMED && g_Runners[0].currentBase >= 1) {
        g_Strikes.howRunnerReachedBase = REACHED_BASE_ON_ERROR;
        return;
    }
    if ((error == FIELDING_ERROR_PENDING_DROPPED_FLY || error == FIELDING_ERROR_PENDING_GROUNDBALL) &&
        g_Ball.lineDriveThroughPitcherInd == 0 && (s8)g_FieldingLogic.const_neg1 < 0 &&
        g_FieldingLogic.always0__ == 0 && (contact = g_Ball.AtBat_ContactResult) != BALL_RESULT_TYPE_IN_AIR &&
        g_Ball.deadBallReason == DEAD_BALL_REASON_NONE) {
        if ((g_Runners[0].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD && g_Runners[0].fractionalBasesRan >= 1.0f) ||
            g_Runners[0].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) {
            if (error == FIELDING_ERROR_PENDING_DROPPED_FLY) {
                g_FieldingLogic.errorTypeCd = FIELDING_ERROR_TYPE_DROPPED_FLY;
            } else {
                g_FieldingLogic.errorTypeCd = FIELDING_ERROR_TYPE_GROUNDBALL;
            }
            g_FieldingLogic.processErrorCode = FIELDING_ERROR_CONFIRMED;
            g_Runners[0].runnerDidntReachOnError = 0;
        }
        if (g_Runners[0].runnerOnFieldOrOutOrScored == RUNNER_STATUS_OUT_DURING_PLAY &&
            (g_Runners[0].forceOutCd == FORCE_OUT_TYPE_OUT_ON_FORCE || contact == BALL_RESULT_TYPE_CAUGHT)) {
            g_FieldingLogic.processErrorCode = FIELDING_ERROR_NONE;
        }
    }
    if (g_FieldingLogic.processErrorCode >= FIELDING_ERROR_PENDING_LATE_THROW_R0 && g_FieldingLogic.processErrorCode <= 7) {
        if ((g_Runners[g_FieldingLogic.processErrorCode - FIELDING_ERROR_PENDING_LATE_THROW_R0].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD && g_Runners[g_FieldingLogic.processErrorCode - FIELDING_ERROR_PENDING_LATE_THROW_R0].baseStandingOn >= 0 &&
             g_Runners[g_FieldingLogic.processErrorCode - FIELDING_ERROR_PENDING_LATE_THROW_R0].forceOutCd <= FORCE_OUT_TYPE_NOT_FORCED_TO_ADVANCE) ||
            g_Runners[g_FieldingLogic.processErrorCode - FIELDING_ERROR_PENDING_LATE_THROW_R0].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) {
            g_FieldingLogic.processErrorCode = FIELDING_ERROR_CONFIRMED;
            g_Runners[0].runnerDidntReachOnError = 0;
            g_FieldingLogic.errorTypeCd = FIELDING_ERROR_TYPE_FAILED_RUNDOWN;
        }
        if (g_Runners[g_FieldingLogic.processErrorCode - FIELDING_ERROR_PENDING_LATE_THROW_R0].runnerOnFieldOrOutOrScored ==
            RUNNER_STATUS_OUT_DURING_PLAY) {
            g_FieldingLogic.processErrorCode = FIELDING_ERROR_NONE;
        }
    }
    if (g_FieldingLogic.processErrorCode != FIELDING_ERROR_CONFIRMED) {
        return;
    }
    if (g_Strikes.storedOuts != 2) {
        return;
    }
    g_Runners[0].runnerDidntReachOnError = 0;
    g_Runners[1].runnerDidntReachOnError = 0;
    g_Runners[2].runnerDidntReachOnError = 0;
    g_Runners[3].runnerDidntReachOnError = 0;
}

// .text:0x00078AC4 size:0x57C mapped:0x806B7B58
void update_runnersBeingTargetedWhileBatterCanBeForcedOut(void) {
    int targeted = storedInningInfo.runnersTargetedWhileBatterForceable;
    BOOL batterSafeUnforced = FALSE;
    int hi;
    int lo;
    int i;
    u8 status;
    u8 status2;
    u8 status3;

    if (storedInningInfo.baserunnerTrackingState == BASERUNNER_TRACKING_NOT_STARTED && g_Ball.ballState == BALL_STATE_HELD) {
        storedInningInfo.baserunnerTrackingState = BASERUNNER_TRACKING_COMPLETE;
        if ((g_Runners[0].forceOutCd != FORCE_OUT_TYPE_NOT_FORCED_TO_ADVANCE ||
             g_Runners[0].runnerOnFieldOrOutOrScored != RUNNER_STATUS_ON_FIELD) &&
            g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_CAUGHT && g_Ball.ballZoneAwayFromHome < BALL_ZONE_OF_SHALLOW &&
            estimatedThrowFramesBetweenTwoPoints(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z,
                                                 base_MoundCoordinates[1].x, base_MoundCoordinates[1].z) + 75 <
                g_Runners[0].framesToNextBase) {
            storedInningInfo.baserunnerTrackingState = BASERUNNER_TRACKING_WAITING;
        }
    } else if (storedInningInfo.baserunnerTrackingState == BASERUNNER_TRACKING_NOT_STARTED && g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_IN_AIR &&
               g_Ball.ballState != BALL_STATE_HELD && g_Runners[0].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
               g_Runners[0].currentBase >= 1) {
        storedInningInfo.baserunnerTrackingState = BASERUNNER_TRACKING_COMPLETE;
    }

    if (storedInningInfo.baserunnerTrackingState == BASERUNNER_TRACKING_WAITING) {
        for (i = 1; i < 4; i++) {
            if (g_Runners[i].baseStandingOn >= 0 ||
                g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) {
                storedInningInfo.runnerForcedCd[i - 1] = RUNNER_FORCE_CODE_REACHED_NEXT_BASE;
            }
        }
        for (i = 0; i < 3; i++) {
            if (storedInningInfo.runnerForcedCd[i] == RUNNER_FORCE_CODE_FORCED_TO_ADVANCE) {
                break;
            }
        }
        if (i >= 3) {
            storedInningInfo.baserunnerTrackingState = BASERUNNER_TRACKING_COMPLETE;
        }
    }

    if (g_Runners[0].forceOutCd == FORCE_OUT_TYPE_NOT_FORCED_TO_ADVANCE &&
        g_Runners[0].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
        batterSafeUnforced = TRUE;
    }

    if (targeted == RUNNERS_TARGETED_NOT_THROWN_TO_BASE) {
        if (batterSafeUnforced) {
            g_FieldingLogic.processErrorCode = FIELDING_ERROR_CONFIRMED;
            storedInningInfo.runnersTargetedWhileBatterForceable = RUNNERS_TARGETED_NONE;
            g_Runners[0].runnerDidntReachOnError = 0;
            g_FieldingLogic.errorTypeCd = FIELDING_ERROR_TYPE_FAILED_RUNDOWN;
        }
        for (i = 0; i < 4; i++) {
            if (g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_OUT_DURING_PLAY &&
                g_Runners[i].forceOutCd == FORCE_OUT_TYPE_OUT_ON_FORCE) {
                storedInningInfo.runnersTargetedWhileBatterForceable = RUNNERS_TARGETED_NONE;
                break;
            }
        }
    } else if (g_Runners[0].runnerOnFieldOrOutOrScored == RUNNER_STATUS_OUT_DURING_PLAY && g_Runners[0].currentBase == 0) {
        storedInningInfo.runnersTargetedWhileBatterForceable = RUNNERS_TARGETED_NONE;
    } else if ((u32)(targeted + 1) <= 1 || targeted == 4) {
        if (targeted == RUNNERS_TARGETED_UNINITIALIZED && g_Runners[0].currentBase >= 1 &&
            (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_LANDED || g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FIELDED)) {
            storedInningInfo.runnersTargetedWhileBatterForceable = RUNNERS_TARGETED_NONE;
        }
        if (storedInningInfo.runnersTargetedWhileBatterForceable == 4 && g_Strikes.howRunnerReachedBase == REACHED_BASE_TBD &&
            g_Runners[0].forceOutCd == FORCE_OUT_TYPE_NOT_FORCED_TO_ADVANCE) {
            g_Strikes.howRunnerReachedBase = REACHED_BASE_FIELDERS_CHOICE_ERROR;
        }
    } else if (targeted >= 100) {
        if ((status = g_Runners[1].runnerOnFieldOrOutOrScored) == RUNNER_STATUS_OUT_DURING_PLAY ||
            (status2 = g_Runners[2].runnerOnFieldOrOutOrScored) == RUNNER_STATUS_OUT_DURING_PLAY ||
            (status3 = g_Runners[3].runnerOnFieldOrOutOrScored) == RUNNER_STATUS_OUT_DURING_PLAY) {
            storedInningInfo.runnersTargetedWhileBatterForceable = RUNNERS_TARGETED_NONE;
        } else if (g_Runners[1].baseStandingOn >= 0 && status != RUNNER_STATUS_OUT_DURING_PLAY) {
            storedInningInfo.runnersTargetedWhileBatterForceable = 23;
        } else if (g_Runners[2].baseStandingOn >= 0 && status2 != RUNNER_STATUS_OUT_DURING_PLAY) {
            storedInningInfo.runnersTargetedWhileBatterForceable = 13;
        } else if (g_Runners[3].baseStandingOn >= 0 && status3 != RUNNER_STATUS_OUT_DURING_PLAY) {
            storedInningInfo.runnersTargetedWhileBatterForceable = 12;
        }
    } else if (targeted >= 10) {
        hi = targeted / 10;
        if ((status = g_Runners[hi].runnerOnFieldOrOutOrScored) == RUNNER_STATUS_OUT_DURING_PLAY ||
            (status2 = g_Runners[lo = targeted % 10].runnerOnFieldOrOutOrScored) == RUNNER_STATUS_OUT_DURING_PLAY) {
            storedInningInfo.runnersTargetedWhileBatterForceable = RUNNERS_TARGETED_NONE;
        } else if (g_Runners[hi].baseStandingOn >= 0 && status != RUNNER_STATUS_OUT_DURING_PLAY) {
            storedInningInfo.runnersTargetedWhileBatterForceable = lo;
        } else if (g_Runners[lo].baseStandingOn >= 0 && status2 != RUNNER_STATUS_OUT_DURING_PLAY) {
            storedInningInfo.runnersTargetedWhileBatterForceable = hi;
        }
    } else {
        status = g_Runners[targeted].runnerOnFieldOrOutOrScored;
        if (status == RUNNER_STATUS_OUT_DURING_PLAY) {
            storedInningInfo.runnersTargetedWhileBatterForceable = RUNNERS_TARGETED_NONE;
        }
        if (((g_Runners[targeted].baseStandingOn >= 0 && status == RUNNER_STATUS_ON_FIELD) ||
             status == RUNNER_STATUS_SCORED_DURING_PLAY) &&
            batterSafeUnforced) {
            storedInningInfo.runnersTargetedWhileBatterForceable = 4;
        }
    }
}

// .text:0x00079040 size:0x2F8 mapped:0x806B80D4
void initialize_runnersBeingTargetedWhileBatterCanBeForcedOut(void) {
    int throwStrat;
    int runStrat;
    int frames;
    s16 base;

    if (storedInningInfo.runnersTargetedWhileBatterForceable != RUNNERS_TARGETED_UNINITIALIZED) {
        return;
    }
    if (g_Ball.fielderWBallIndex > 5) {
        storedInningInfo.runnersTargetedWhileBatterForceable = RUNNERS_TARGETED_NONE;
    } else if (g_Runners[0].runnerOnFieldOrOutOrScored != RUNNER_STATUS_ON_FIELD || g_Runners[0].currentBase != 0) {
        storedInningInfo.runnersTargetedWhileBatterForceable = RUNNERS_TARGETED_NONE;
    } else if (g_FieldingLogic.locationThrownTo == 1) {
        storedInningInfo.runnersTargetedWhileBatterForceable = RUNNERS_TARGETED_NONE;
    } else {
        frames = howManyFramesTheRunnerIsOutOfReach(0, TRUE, &throwStrat, &runStrat) + 10;
        if (g_Fielders[g_Ball.fielderWBallIndex].always0_ != 0) {
            frames += 20;
        }
        if (frames >= 0) {
            storedInningInfo.runnersTargetedWhileBatterForceable = RUNNERS_TARGETED_NONE;
            return;
        }
        base = g_FieldingLogic.locationThrownTo;
        storedInningInfo.runnersTargetedWhileBatterForceable = RUNNERS_TARGETED_NOT_THROWN_TO_BASE;
        if (base == 0) {
            if (g_Runners[3].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                storedInningInfo.runnersTargetedWhileBatterForceable = 3;
            }
            if (g_Runners[3].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY &&
                g_Runners[3].timeStandingOnBase < 60) {
                storedInningInfo.runnersTargetedWhileBatterForceable = 3;
            }
            if (g_Runners[2].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD && g_Runners[2].currentBase == 3 &&
                storedInningInfo.runnersTargetedWhileBatterForceable == 3) {
                storedInningInfo.runnersTargetedWhileBatterForceable = 23;
            }
        } else if (base == 3) {
            if (g_Runners[1].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD && g_Runners[1].currentBase == 2) {
                if (g_Runners[3].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
                    g_Runners[2].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                    storedInningInfo.runnersTargetedWhileBatterForceable = 123;
                } else if (g_Runners[3].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                    storedInningInfo.runnersTargetedWhileBatterForceable = 13;
                } else if (g_Runners[2].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                    storedInningInfo.runnersTargetedWhileBatterForceable = 12;
                } else {
                    storedInningInfo.runnersTargetedWhileBatterForceable = 1;
                }
            } else if (g_Runners[3].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
                       g_Runners[2].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                storedInningInfo.runnersTargetedWhileBatterForceable = 23;
            } else if (g_Runners[3].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                storedInningInfo.runnersTargetedWhileBatterForceable = 3;
            } else if (g_Runners[2].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                storedInningInfo.runnersTargetedWhileBatterForceable = 2;
            }
        } else if (base == 2) {
            if (g_Runners[2].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
                g_Runners[1].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                storedInningInfo.runnersTargetedWhileBatterForceable = 12;
            } else if (g_Runners[2].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                storedInningInfo.runnersTargetedWhileBatterForceable = 2;
            } else if (g_Runners[1].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                storedInningInfo.runnersTargetedWhileBatterForceable = 1;
            }
        }
        if (storedInningInfo.runnersTargetedWhileBatterForceable == RUNNERS_TARGETED_NOT_THROWN_TO_BASE) {
            g_FieldingLogic.lastThrowingFielder = g_Ball.fielderWBallIndex;
        }
    }
}

// .text:0x00079338 size:0xDC mapped:0x806B83CC
void fn_3_79338(void) {
    int i;

    if (g_Strikes.storedOuts == 2) {
        return;
    }
    if (g_Strikes.outs >= 3) {
        return;
    }
    if (storedInningInfo.playResultCode == PLAY_RESULT_CODE_NONE) {
        if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT || g_FieldingLogic.processErrorCode == FIELDING_ERROR_PENDING_DROPPED_FLY) {
            if (g_Ball.landingSpotZoneAwayFromHome >= 2) {
                storedInningInfo.playResultCode = PLAY_RESULT_CODE_OUTFIELD_CATCH_FOR_OUT;
            }
        }
    } else if (storedInningInfo.playResultCode == PLAY_RESULT_CODE_OUTFIELD_CATCH_FOR_OUT &&
               g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT) {
        for (i = 1; i < 4; i++) {
            if (g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) {
                storedInningInfo.playResultCode = PLAY_RESULT_CODE_SAC_FLY_SCORED;
            }
        }
    }
}

// .text:0x00079414 size:0x194 mapped:0x806B84A8
void runnerResultCd_bunt(void) {
    InMemRunnerType* runner;
    int advanced;
    int nForced;
    int i;

    if (g_Ball.maybebuntOn2Strikes) {
        storedInningInfo.playResultCode = PLAY_RESULT_CODE_FOUL_BUNT_TWO_STRIKES;
        return;
    }
    if (g_Strikes.storedOuts >= 2) {
        return;
    }
    if (g_RunningLogic.nOffensivePlayersAtStartOfPlay <= 1) {
        return;
    }
    if (storedInningInfo.playResultCode == PLAY_RESULT_CODE_NONE &&
        (g_Ball.ballState == BALL_STATE_HELD || g_Ball.ballState == BALL_STATE_THROWN ||
         g_FieldingLogic.somethingForTryingTagOutTargetBase >= 0 || g_FieldingLogic.runnerBeingTargettedForOut >= 0)) {
        storedInningInfo.playResultCode = PLAY_RESULT_CODE_PLAY_ONGOING;
    }
    if (storedInningInfo.playResultCode != PLAY_RESULT_CODE_PLAY_ONGOING &&
        storedInningInfo.playResultCode != PLAY_RESULT_CODE_0F) {
        return;
    }

    advanced = 0;
    runner = &g_Runners[1];
    nForced = 0;
    for (i = 0; i < 3; i++) {
        if (runner[i].forceOutCd != FORCE_OUT_TYPE_NOT_FORCED_TO_ADVANCE) {
            nForced++;
        }
    }
    for (i = 3; i != 0; i--) {
        if (runner->currentBase > runner->startingBase_baseAchieved ||
            runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) {
            if (runner->currentBase == 4 && runner->startingBase_baseAchieved == 3 &&
                runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_OUT_DURING_PLAY) {
                storedInningInfo.playResultCode = PLAY_RESULT_CODE_FIELDERS_CHOICE;
                break;
            }
            if (runner->forceOutCd == FORCE_OUT_TYPE_NOT_FORCED_TO_ADVANCE) {
                advanced++;
            }
        } else if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_OUT_DURING_PLAY) {
            storedInningInfo.playResultCode = PLAY_RESULT_CODE_FIELDERS_CHOICE;
            break;
        }
        runner++;
    }
    if (advanced != 0 && nForced == 0) {
        storedInningInfo.playResultCode = PLAY_RESULT_CODE_ALL_RUNNERS_SAFE;
    }
}

// .text:0x000795A8 size:0x1C4 mapped:0x806B863C
void adjustTotalBasesOnHit(void) {
    int base;

    if (storedInningInfo.tentativeBatterBase > 0) {
        return;
    }
    if (g_Ball.deadBallReason == DEAD_BALL_REASON_HOME_RUN) {
        storedInningInfo.batterResultBase = 4;
        storedInningInfo.tentativeBatterBase = 4;
        return;
    }
    if (g_Ball.deadBallReason == DEAD_BALL_REASON_GROUND_RULE_DOUBLE) {
        storedInningInfo.batterResultBase = 2;
        storedInningInfo.tentativeBatterBase = 2;
        return;
    }
    if (g_Runners[0].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) {
        storedInningInfo.batterResultBase = 4;
        storedInningInfo.tentativeBatterBase = 4;
        return;
    }
    if (g_Ball.ballZoneAwayFromHome <= BALL_ZONE_IF_DIRT && g_Ball.ballState != BALL_STATE_HIT) {
        if (g_Runners[0].currentBase == 0) {
            base = 1;
        } else if (g_Runners[0].percentTowardsNextBase < 0.3f) {
            if (g_Runners[0].runnerOnFieldOrOutOrScored == RUNNER_STATUS_OUT_DURING_PLAY &&
                0.0f == g_Runners[0].percentTowardsNextBase) {
                base = g_Runners[0].currentBase - 1;
            } else {
                base = g_Runners[0].currentBase;
            }
        } else {
            base = g_Runners[0].nextBase;
        }
        storedInningInfo.tentativeBatterBase = -base;
    }
    if (g_Runners[0].currentBase == -storedInningInfo.tentativeBatterBase && storedInningInfo.tentativeBatterBase != 0) {
        storedInningInfo.tentativeBatterBase *= -1;
        if ((s8)g_Runners[0].baseOfFailedBodyCheck == storedInningInfo.tentativeBatterBase) {
            storedInningInfo.tentativeBatterBase--;
        }
        storedInningInfo.batterResultBase = storedInningInfo.tentativeBatterBase;
        return;
    }
    if (g_Runners[0].currentBase - 1 == -storedInningInfo.tentativeBatterBase &&
        storedInningInfo.tentativeBatterBase != 0 &&
        (s8)g_Runners[0].baseOfFailedBodyCheck == (1 - storedInningInfo.tentativeBatterBase) % 4) {
        storedInningInfo.tentativeBatterBase *= -1;
        storedInningInfo.batterResultBase = storedInningInfo.tentativeBatterBase;
        return;
    }
    if (g_Runners[0].currentBase != 0) {
        storedInningInfo.batterResultBase = g_Runners[0].currentBase;
    }
}

