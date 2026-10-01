#define SQRT2_LINKAGE static
#include "game/match_setup/stat_tracking.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/baserunning/play_result_tracking.h"

extern s8 pitchingInfo_A_H[2][9][5];
extern s8 lineUpInfoStruct[2][9][4];
extern s16 lbl_3_data_5EDC[];
extern int getAdjustedPitcherStamina(int team, int rosterID, int amount);
extern void runScored(void);
extern void challenge_postPitchStarMissionTracking(void);
extern BOOL checkForButtonPressToSkip(int a, int b);

// .text:0x0007976C size:0x294 mapped:0x806B8800
void setInitialTotalBasesOnHit(void) {
    int runnerForced = 0;
    int base = -1;
    s32 i;

    if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != PICKOFF_STEAL_CODE_NONE) {
        storedInningInfo.batterResultBase = 0;
        return;
    }
    if (g_Ball.ballInitialHitDoneInd != 0 && g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_IN_AIR &&
        g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_FOUL) {
        if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT || g_FieldingLogic.infieldFlyIndicator == 2) {
            base = 0;
        } else if (g_Ball.deadBallReason == DEAD_BALL_REASON_HOME_RUN ||
                   g_Ball.deadBallReason == DEAD_BALL_REASON_GROUND_RULE_DOUBLE) {
            base = 1;
        } else {
            for (i = 0; i < 4; i++) {
                if (g_Runners[i].forceOutCd == FORCE_OUT_TYPE_FORCED_TO_ADVANCE) {
                    runnerForced = 1;
                }
                if (g_Runners[i].forceOutCd == FORCE_OUT_TYPE_OUT_ON_FORCE) {
                    runnerForced = 2;
                }
            }
            if (runnerForced == 2) {
                base = 0;
            } else if (runnerForced == 0) {
                if (storedInningInfo.baserunnerTrackingState == BASERUNNER_TRACKING_COMPLETE &&
                    g_Runners[0].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                    base = 1;
                }
                if (g_Ball.fielderWithBallIndexStored2 >= 0 && g_Ball.fielderWithBallIndexStored2 <= 5 &&
                    g_Ball.ballZoneWhenCaught <= 1 && base == 1) {
                    for (i = 1; i < 4; i++) {
                        if (g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_OUT_DURING_PLAY) {
                            base = 0;
                            goto end;
                        }
                    }
                    for (i = 1; i < 4; i++) {
                        if (g_Runners[i].runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE &&
                            g_Runners[i].baseStandingOn < 0 &&
                            g_Runners[i].runnerOnFieldOrOutOrScored != RUNNER_STATUS_SCORED_DURING_PLAY &&
                            g_Runners[i].currentBase <= g_Runners[i].startingBase_baseAchieved) {
                            break;
                        }
                    }
                    if (i < 4) {
                        base = -1;
                    }
                }
            }
        }
    }
end:
    storedInningInfo.batterResultBase = base;
}

// .text:0x00079A00 size:0xCC mapped:0x806B8A94
void trackForceOutsThisPlay(void) {
    if (storedInningInfo.nRunnersForcedOut == -1) {
        return;
    }
    if (storedInningInfo.nRunnersForcedOut == 0) {
        if (g_Strikes.runnerIndexForEachOutThisPitch[0] >= 0) {
            if (g_Runners[g_Strikes.runnerIndexForEachOutThisPitch[0]].forceOutCd == FORCE_OUT_TYPE_OUT_ON_FORCE) {
                storedInningInfo.nRunnersForcedOut = 1;
            } else {
                storedInningInfo.nRunnersForcedOut = -1;
            }
        }
    }
    if (storedInningInfo.nRunnersForcedOut == 1) {
        if (g_Strikes.runnerIndexForEachOutThisPitch[1] >= 0) {
            s16 cd = g_Runners[g_Strikes.runnerIndexForEachOutThisPitch[1]].forceOutCd;
            if (cd == FORCE_OUT_TYPE_OUT_ON_FORCE) {
                storedInningInfo.nRunnersForcedOut = 2;
            } else if (cd == -1) {
                storedInningInfo.nRunnersForcedOut = 3;
            } else {
                storedInningInfo.nRunnersForcedOut = -1;
            }
        }
    }
}

// .text:0x00079ACC size:0x308 mapped:0x806B8B60
void midPlay_trackStats(void) {
    s32 i;
    u8* stat;

    if (storedInningInfo.batterResultBase == -1) {
        setInitialTotalBasesOnHit();
    } else if (storedInningInfo.batterResultBase >= 1) {
        adjustTotalBasesOnHit();
    }

    if (storedInningInfo.batterResultBase == 1 && storedInningInfo.runnersTargetedWhileBatterForceable == 0 &&
        g_Strikes.howRunnerReachedBase == REACHED_BASE_TBD) {
        if (g_FieldingLogic.processErrorCode == 0 || g_Ball.lineDriveThroughPitcherInd != 0 ||
            g_FieldingLogic.const_neg1 >= 0) {
            g_Strikes.howRunnerReachedBase = 1;
        }
    }

    if (g_Ball.maybeBuntInd != 0) {
        runnerResultCd_bunt();
    } else if (g_Strikes.storedOuts != 2 && g_Strikes.outs < 3) {
        if (storedInningInfo.playResultCode == PLAY_RESULT_CODE_NONE) {
            if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT || g_FieldingLogic.processErrorCode == 1) {
                if (g_Ball.landingSpotZoneAwayFromHome >= 2) {
                    storedInningInfo.playResultCode = PLAY_RESULT_CODE_OUTFIELD_CATCH_FOR_OUT;
                }
            }
        } else if (storedInningInfo.playResultCode == PLAY_RESULT_CODE_OUTFIELD_CATCH_FOR_OUT) {
            if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT) {
                for (i = 1; i < 4; i++) {
                    if (g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) {
                        storedInningInfo.playResultCode = PLAY_RESULT_CODE_SAC_FLY_SCORED;
                    }
                }
            }
        }
    }

    trackForceOutsThisPlay();
    update_runnersBeingTargetedWhileBatterCanBeForcedOut();
    monitorForErrors();

    if ((g_Batter.captainStarSwingActivated != 0 || g_Batter.nonCaptainStarSwingActivated != 0 ||
         g_Batter.moonShotInd != 0) &&
        g_Ball.framesSinceHit == 1) {
        if (BatterStats_P1_P2[g_GameLogic.teamBatting][g_Batter.rosterID].StarHitsActivated < 0xFE) {
            BatterStats_P1_P2[g_GameLogic.teamBatting][g_Batter.rosterID].StarHitsActivated++;
        } else {
            BatterStats_P1_P2[g_GameLogic.teamBatting][g_Batter.rosterID].StarHitsActivated = 0xFF;
        }
    }
}

// .text:0x00079DD4 size:0x120 mapped:0x806B8E68
void checkSaveSituation(void) {
    int pitcher;
    int fieldingTeam = g_GameLogic.homeTeamBattingInd_fieldingTeam;
    int lead = g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total - g_Scores.scores[fieldingTeam].total;
    int battingTeam = g_GameLogic.awayTeamBattingInd_battingTeam;

    g_Scores._B7[battingTeam] = -1;
    if (lead <= 0) {
        return;
    }
    if (!(g_Scores.Inning + 2 < g_Scores.inningLimit ||
          (g_Scores.Inning + 2 == g_Scores.inningLimit && g_Strikes.outs == 0))) {
        if (lead > 3 || !(g_Scores.Inning < g_Scores.inningLimit || (g_Scores.Inning >= g_Scores.inningLimit && g_Strikes.outs == 0))) {
            int onBase = 0;
            s32 i;
            for (i = 1; i < 4; i++) {
                if (g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                    onBase++;
                }
            }
            if (lead > onBase + 2) {
                return;
            }
        }
    }
    pitcher = g_GameLogic.battingOrderAndPositionMapping[battingTeam][0][0];
    g_Scores._B7[battingTeam] = pitcher;
    pitchingInfo_A_H[g_GameLogic.teamFielding][pitcher][1] = 1;
}

// .text:0x00079EF4 size:0x260 mapped:0x806B8F88
void updatePitcherStatsOnScoreChange(void) {
    int diff = g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total - g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total;
    int fieldingTeam = g_GameLogic.homeTeamBattingInd_fieldingTeam;
    int battingTeam = g_GameLogic.awayTeamBattingInd_battingTeam;
    s32 i;
    int n;
    u8* p;

    if (diff > 0 && diff <= g_Scores._9C) {
        g_Scores._AE = g_Scores.Inning;
    }
    if (diff >= 0) {
        g_Scores._B5[fieldingTeam] = -1;
    }
    if (diff <= g_Scores._9C && diff > 0) {
        if (g_Scores._9C == 1) {
            for (i = 0; i < 4; i++) {
                if (g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) {
                    g_Scores._B5[battingTeam] = g_Runners[i].pitcherWhoLetRunnerOnBase;
                    break;
                }
            }
        } else {
            n = g_Scores._9C;
            for (i = 3; i >= 0; i--) {
                if (g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) {
                    if (diff == n) {
                        g_Scores._B5[battingTeam] = g_Runners[i].pitcherWhoLetRunnerOnBase;
                        break;
                    }
                    n--;
                }
            }
        }
    }
    if (diff >= 0) {
        g_Scores._B3[battingTeam] = -1;
        p = &g_Scores._B9[battingTeam];
        if (*p == 1) {
            if (g_Scores._BB[fieldingTeam] == 1) {
                *p = 0;
            } else {
                *p = 2;
            }
        }
    }
    if (diff <= g_Scores._9C && diff > 0) {
        g_Scores._B3[fieldingTeam] = g_Scores._B1[fieldingTeam];
        g_Scores._BD[fieldingTeam] = g_Scores._BB[fieldingTeam];
        if (g_Scores._B9[fieldingTeam] == 0) {
            if (g_Scores._BB[fieldingTeam] == 1) {
                g_Scores._B9[fieldingTeam] = 1;
            } else {
                g_Scores._B9[fieldingTeam] = 2;
            }
        } else if (g_Scores._B9[fieldingTeam] == 1) {
            if (g_Scores._BB[fieldingTeam] > 1) {
                g_Scores._B9[fieldingTeam] = 2;
            }
        }
    }
    if (diff >= 0) {
        pitchingInfo_A_H[g_GameLogic.teamFielding][g_GameLogic.battingOrderAndPositionMapping[battingTeam][0][0]][1] =
            0;
    }
}

// .text:0x0007A154 size:0x9E0 mapped:0x806B91E8
void postPitchStatUpdating(int arg) {
    StatisticsPitcher* pitcherStats;
    BOOL leadChange = FALSE;
    int lead;
    s32 i;
    s32 k;
    int fieldingTeam;

    pitcherStats = getCurrentPitcherStats();
    if (g_Stats.replayInd != 0) {
        return;
    }

    for (i = 0; i < 9; i++) {
        BatterStats_P1_P2[g_GameLogic.teamFielding][g_Fielders[i].rosterLocation].onFieldForAPitch = 1;
    }
    for (i = 0; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE && g_Runners[i].rosterID >= 0) {
            BatterStats_P1_P2[g_GameLogic.teamBatting][g_Runners[i].rosterID].onFieldForAPitch = 1;
        }
    }
    PitcherStats_P1_P2[g_GameLogic.teamFielding]
                      [g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]]
                          .wasPitcher = 1;
    postPitchStatRelated(0);

    if (pitcherStats->maxPitchSpeed < g_Pitcher.pitchSpeed) {
        pitcherStats->maxPitchSpeed = g_Pitcher.pitchSpeed;
    }

    if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd == PICKOFF_STEAL_CODE_NONE) {
        if (g_Pitcher.starPitchType != 0 || g_Pitcher.nonCaptainStarPitchTriggeredType != 0) {
            getAdjustedPitcherStamina(g_GameLogic.teamFielding, g_Pitcher.rosterID, lbl_3_data_5EDC[1]);
            if (PitcherStats_P1_P2[g_GameLogic.teamFielding]
                                  [g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]]
                                      .starPitchesThrown < 0xFE) {
                PitcherStats_P1_P2[g_GameLogic.teamFielding]
                                  [g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]]
                                      .starPitchesThrown++;
            } else {
                PitcherStats_P1_P2[g_GameLogic.teamFielding]
                                  [g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]]
                                      .starPitchesThrown = 0xFF;
            }
        }
        if ((g_Pitcher.strikeOutOrWalk == AT_BAT_END_WALK || g_Pitcher.strikeOutOrWalk == AT_BAT_END_HIT_BY_PITCH) &&
            g_RunningLogic.nOffensivePlayersAtStartOfPlay >= 4) {
            getAdjustedPitcherStamina(g_GameLogic.teamFielding, g_Pitcher.rosterID, lbl_3_data_5EDC[2]);
        } else if (g_Scores._C2 != 0) {
            getAdjustedPitcherStamina(g_GameLogic.teamFielding, g_Pitcher.rosterID, lbl_3_data_5EDC[2] * g_Scores._C2);
        }
    }

    for (k = 1; k < 10; k++) {
        if (lbl_80353260[g_GameLogic.teamFielding]
                        [g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][k][0]]
                            .e == 0xA) {
            lbl_80353260[g_GameLogic.teamFielding]
                        [g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][k][0]]
                            .e = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][k][1];
        }
    }

    lead = g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total -
           g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total;
    lead -= g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].byInning[g_Scores.Inning - 1] - g_Scores._9E;
    if (g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total -
            g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total >=
        0) {
        if (lead <= 0) {
            leadChange = TRUE;
        }
    }

    if (arg == 0) {
        if ((g_Pitcher.strikeOutOrWalk == AT_BAT_END_WALK || g_Pitcher.strikeOutOrWalk == AT_BAT_END_HIT_BY_PITCH) &&
            g_RunningLogic.nOffensivePlayersAtStartOfPlay >= 4 && g_Runners[3].pitcherWhoLetRunnerOnBase >= 0) {
            int pitcher = g_Runners[3].pitcherWhoLetRunnerOnBase;
            fieldingTeam = g_GameLogic.teamFielding;
            if (PitcherStats_P1_P2[fieldingTeam][pitcher].runsAllowed < 0xFFFE) {
                PitcherStats_P1_P2[fieldingTeam][pitcher].runsAllowed++;
            } else {
                PitcherStats_P1_P2[fieldingTeam][pitcher].runsAllowed = 0xFFFF;
            }
            if (g_Runners[3].runnerDidntReachOnError != 0) {
                if (PitcherStats_P1_P2[fieldingTeam][pitcher].earnedRunsAllowed < 0xFFFE) {
                    PitcherStats_P1_P2[fieldingTeam][pitcher].earnedRunsAllowed++;
                } else {
                    PitcherStats_P1_P2[fieldingTeam][pitcher].earnedRunsAllowed = 0xFFFF;
                }
            }
            if (leadChange && ++lead >= 0) {
                pitchingInfo_A_H[fieldingTeam][pitcher][1] = 0;
            }
        }
    } else {
        int scored[4];
        int remaining = g_Scores._9C;
        int outs;

        for (i = 0; i < 4; i++) {
            scored[i] = 0;
            if (g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY ||
                g_Runners[i].scoredOnGRD != 0) {
                if (remaining <= 0) {
                    scored[i] = 1;
                } else {
                    remaining--;
                }
            }
        }
        outs = g_Strikes.storedOuts;
        if (outs == 2) {
            BOOL forced = FALSE;
            if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT) {
                forced = TRUE;
            } else {
                for (i = 0; i < 4; i++) {
                    if (g_Runners[i].forceOutCd == FORCE_OUT_TYPE_OUT_ON_FORCE) {
                        forced = TRUE;
                    }
                }
            }
            if (forced) {
                for (i = 0; i < 4; i++) {
                    scored[i] = 0;
                }
            }
        }
        if (outs == 1) {
            int outsLeft = 2;
            for (i = 0; i < 4; i++) {
                if (g_Runners[i].forceOutCd == FORCE_OUT_TYPE_OUT_ON_FORCE) {
                    outsLeft--;
                }
            }
            if (outsLeft <= 0) {
                for (i = 0; i < 4; i++) {
                    scored[i] = 0;
                }
            }
        }
        fieldingTeam = g_GameLogic.teamFielding;
        for (i = 3; i >= 0; i--) {
            if (scored[i] != 0 && g_Runners[i].pitcherWhoLetRunnerOnBase >= 0) {
                if (PitcherStats_P1_P2[fieldingTeam][g_Runners[i].pitcherWhoLetRunnerOnBase].runsAllowed < 0xFFFE) {
                    PitcherStats_P1_P2[fieldingTeam][g_Runners[i].pitcherWhoLetRunnerOnBase].runsAllowed++;
                } else {
                    PitcherStats_P1_P2[fieldingTeam][g_Runners[i].pitcherWhoLetRunnerOnBase].runsAllowed = 0xFFFF;
                }
                if (g_Runners[i].runnerDidntReachOnError != 0) {
                    if (g_FieldingLogic.processErrorCode == 9) {
                        if (i == 3 && g_FieldingLogic.errorTypeCd == 1 && g_Ball.landingSpotZoneAwayFromHome == 4) {
                            if (PitcherStats_P1_P2[fieldingTeam][g_Runners[i].pitcherWhoLetRunnerOnBase].earnedRunsAllowed < 0xFFFE) {
                                PitcherStats_P1_P2[fieldingTeam][g_Runners[i].pitcherWhoLetRunnerOnBase].earnedRunsAllowed++;
                            } else {
                                PitcherStats_P1_P2[fieldingTeam][g_Runners[i].pitcherWhoLetRunnerOnBase].earnedRunsAllowed = 0xFFFF;
                            }
                        }
                    } else {
                        if (PitcherStats_P1_P2[fieldingTeam][g_Runners[i].pitcherWhoLetRunnerOnBase].earnedRunsAllowed < 0xFFFE) {
                            PitcherStats_P1_P2[fieldingTeam][g_Runners[i].pitcherWhoLetRunnerOnBase].earnedRunsAllowed++;
                        } else {
                            PitcherStats_P1_P2[fieldingTeam][g_Runners[i].pitcherWhoLetRunnerOnBase].earnedRunsAllowed = 0xFFFF;
                        }
                    }
                }
                if (leadChange && ++lead >= 0) {
                    pitchingInfo_A_H[fieldingTeam][g_Runners[i].pitcherWhoLetRunnerOnBase][1] = 0;
                }
            }
        }
    }

    {
        int team = g_GameLogic.awayTeamBattingInd_battingTeam;
        if ((&storedInningInfo.lastPitcher)[team * 2] != g_GameLogic.battingOrderAndPositionMapping[team][0][0]) {
            (&storedInningInfo.lastPitcher)[team * 2] = g_GameLogic.battingOrderAndPositionMapping[team][0][0];
            storedInningInfo.nABs[team * 2] = 0;
            storedInningInfo.inningPitchesCompleted = 0;
        }
    }

    {
        int digit = g_Strikes.balls + g_Strikes.strikes * 16;
        for (i = 0; i < 7; i++) {
            if (storedInningInfo.strikeBallDigits[i] == 0) {
                if (i <= 0 || storedInningInfo.strikeBallDigits[i - 1] != digit) {
                    storedInningInfo.strikeBallDigits[i] = digit;
                }
                break;
            }
        }
    }
    if (storedInningInfo.inningPitchesCompleted < 0x7FFE) {
        storedInningInfo.inningPitchesCompleted++;
    } else {
        storedInningInfo.inningPitchesCompleted = 0x7FFF;
    }
    runScored();
    if (g_d_GameSettings.exhibitionMatchInd == 0) {
        challenge_postPitchStarMissionTracking();
    }
}

// .text:0x0007AB34 size:0x44 mapped:0x806B9BC8
void incrementPitchCount(void) {
    StatisticsPitcher* pitcher =
        &PitcherStats_P1_P2[g_GameLogic.teamFielding]
                           [g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]];
    pitcher->pitchesThrown++;
}

// .text:0x0007AB78 size:0x1F0 mapped:0x806B9C0C
void postPitchStatRelated(int arg) {
    s32 i;
    int pitcher;
    int catcher;

    if (arg != 0) {
        if (g_Scores._BB[g_GameLogic.awayTeamBattingInd_battingTeam] < 0xFE) {
            g_Scores._BB[g_GameLogic.awayTeamBattingInd_battingTeam]++;
        } else {
            g_Scores._BB[g_GameLogic.awayTeamBattingInd_battingTeam] = 0xFF;
        }
    }

    pitcher = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0];
    for (i = 1; i < 10; i++) {
        if (g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][i][1] == 1) {
            catcher = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][i][0];
            break;
        }
    }

    if (StatsScreenScores.pitcherLog[g_GameLogic.teamFielding][0].pitcher == -1) {
        StatsScreenScores.pitcherLog[g_GameLogic.teamFielding][0].pitcher = pitcher;
        StatsScreenScores.pitcherLog[g_GameLogic.teamFielding][0].inning = 1;
        StatsScreenScores.catcherLog[g_GameLogic.teamFielding][0] = catcher;
        return;
    }
    for (i = 1; i < 10; i++) {
        if (StatsScreenScores.pitcherLog[g_GameLogic.teamFielding][i].pitcher == -1) {
            if (StatsScreenScores.pitcherLog[g_GameLogic.teamFielding][i - 1].pitcher != pitcher) {
                StatsScreenScores.pitcherLog[g_GameLogic.teamFielding][i].pitcher = pitcher;
                StatsScreenScores.pitcherLog[g_GameLogic.teamFielding][i].inning = g_Scores.Inning;
                if (storedInningInfo._4C[g_GameLogic.awayTeamBattingInd_battingTeam] < 0x7FFE) {
                    storedInningInfo._4C[g_GameLogic.awayTeamBattingInd_battingTeam]++;
                } else {
                    storedInningInfo._4C[g_GameLogic.awayTeamBattingInd_battingTeam] = 0x7FFF;
                }
            }
            break;
        }
    }
    if (arg == 0) {
        for (i = 1; i < 5; i++) {
            if (StatsScreenScores.catcherLog[g_GameLogic.teamFielding][i] == -1) {
                if (StatsScreenScores.catcherLog[g_GameLogic.teamFielding][i - 1] != catcher) {
                    StatsScreenScores.catcherLog[g_GameLogic.teamFielding][i] = catcher;
                }
                return;
            }
        }
    }
}

// .text:0x0007AD68 size:0x140 mapped:0x806B9DFC
void fn_3_7AD68(void) {
    s32 k;
    int pitcher = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0];

    if (pitchingInfo_A_H[g_GameLogic.teamFielding][pitcher][2] < 0) {
        pitchingInfo_A_H[g_GameLogic.teamFielding][pitcher][2] = 0;
    } else {
        pitchingInfo_A_H[g_GameLogic.teamFielding][pitcher][4] = 0;
    }
    for (k = 1; k < 10; k++) {
        int pos = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][k][1];
        int idx = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][k][0];
        if (pos > 0 && pitchingInfo_A_H[g_GameLogic.teamFielding][idx][2] == 0 &&
            pitchingInfo_A_H[g_GameLogic.teamFielding][idx][3] != pos) {
            pitchingInfo_A_H[g_GameLogic.teamFielding][idx][3] = pos;
        }
    }
}

// .text:0x0007AEA8 size:0x40 mapped:0x806B9F3C
int fn_3_7AEA8(void) {
    return g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam] +
           (storedInningInfo._44[g_GameLogic.homeTeamBattingInd_fieldingTeam] - 1) * 9 - 1;
}

// .text:0x0007AEE8 size:0x4 mapped:0x806B9F7C
void fn_3_7AEE8(void) {
    return;
}

// .text:0x0007AEEC size:0x7C mapped:0x806B9F80
void setRunnerOnBaseIndicators2(void) {
    s32 i;

    storedInningInfo.batterResultBase = -1;
    storedInningInfo.baserunnerTrackingState = BASERUNNER_TRACKING_NOT_STARTED;
    for (i = 1; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE) {
            storedInningInfo.runnerForcedCd[i - 1] = RUNNER_FORCE_CODE_FORCED_TO_ADVANCE;
        } else {
            storedInningInfo.runnerForcedCd[i - 1] = RUNNER_FORCE_CODE_NONE;
        }
    }
}

// .text:0x0007AF68 size:0x7C mapped:0x806B9FFC
void setRunnerOnBaseIndicators(void) {
    s32 i;

    storedInningInfo.batterResultBase = -1;
    storedInningInfo.baserunnerTrackingState = BASERUNNER_TRACKING_NOT_STARTED;
    for (i = 1; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE) {
            storedInningInfo.runnerForcedCd[i - 1] = RUNNER_FORCE_CODE_FORCED_TO_ADVANCE;
        } else {
            storedInningInfo.runnerForcedCd[i - 1] = RUNNER_FORCE_CODE_NONE;
        }
    }
}

// .text:0x0007AFE4 size:0x14C mapped:0x806BA078
void intializeRunnersDuringTransition(void) {
    int half = g_Scores.halfInning;
    int batter = g_GameLogic.currentBatterPerTeam[half];

    storedInningInfo.batterResultBase = -1;
    storedInningInfo.tentativeBatterBase = 0;
    storedInningInfo.playResultCode = PLAY_RESULT_CODE_NONE;
    storedInningInfo.runnersTargetedWhileBatterForceable = -1;
    storedInningInfo.nRunnersForcedOut = 0;
    storedInningInfo.rbisWaitingToBeAddedToScore = 0;
    if (storedInningInfo.nBattersThisInning2 < 0xFE) {
        storedInningInfo.nBattersThisInning2++;
    } else {
        storedInningInfo.nBattersThisInning2 = 0xFF;
    }
    if (batter == 1) {
        if (storedInningInfo.nBattersThisInning2 > 1 || g_Scores.Inning != 1) {
            storedInningInfo._44[half]++;
        }
        setRunnerOnBaseIndicators();
    }
    storedInningInfo.strikeBallDigits[0] = 0;
    storedInningInfo.strikeBallDigits[1] = 0;
    storedInningInfo.strikeBallDigits[2] = 0;
    storedInningInfo.strikeBallDigits[3] = 0;
    storedInningInfo.strikeBallDigits[4] = 0;
    storedInningInfo.strikeBallDigits[5] = 0;
    storedInningInfo.strikeBallDigits[6] = 0;
}

// .text:0x0007B130 size:0x1D8 mapped:0x806BA1C4
void resetGameControlVars_duringNewInning(void) {
    s32 slot;
    s32 team;

    for (team = 0; team < 2; team++) {
        for (slot = 0; slot < 9; slot++) {
            if (lineUpInfoStruct[team][slot][3] == 1) {
                lbl_80353260[team][slot].d = g_Scores.Inning;
            }
        }
    }

    storedInningInfo.atBatResultHistory[0] = 0;
    storedInningInfo.atBatResultHistory[1] = 0;
    storedInningInfo.atBatResultHistory[2] = 0;
    storedInningInfo.atBatResultHistory[3] = 0;
    storedInningInfo.atBatResultHistory[4] = 0;
    storedInningInfo.batterIDStored = -1;
    storedInningInfo.inningPitchesCompleted = 0;
    storedInningInfo.rbisWaitingToBeAddedToScoreStored = 0;
    storedInningInfo.nBattersThisInning = 1;
    storedInningInfo.nBattersThisInning2Stored = storedInningInfo.nBattersThisInning2;
    storedInningInfo.nBattersThisInning2 = 0;
    storedInningInfo.consecutiveHits = 0;
    storedInningInfo.consecutiveHits2 = 0;
    storedInningInfo.consecutiveWalks = 0;
    storedInningInfo.consecutiveHBP = 0;
    storedInningInfo.consecutiveWalksOrHBP = 0;
    for (slot = 0; slot < 9; slot++) {
        pitchingInfo_A_H[g_GameLogic.teamFielding][slot][2] = -1;
        pitchingInfo_A_H[g_GameLogic.teamFielding][slot][3] = -1;
        pitchingInfo_A_H[g_GameLogic.teamFielding][slot][4] = -1;
    }
    pitchingInfo_A_H[g_GameLogic.teamFielding]
                    [g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]][2] =
        0;
}

// .text:0x0007B308 size:0x86C mapped:0x806BA39C
void initializeStats(void) {
    s32 team;
    s32 i;
    s32 j;
    StatsTableEntryA* entry;
    int found;
    u16 startingStamina = lbl_3_data_5EDC[0];

    for (team = 0; team < 2; team++) {
        for (i = 0; i < 9; i++) {
            StatisticsBatter* batter = &BatterStats_P1_P2[team][i];
            StatisticsPitcher* pitcher = &PitcherStats_P1_P2[team][i];

            batter->onFieldForAPitch = 0;
            batter->plateAppearances = 0;
            batter->AtBats = 0;
            batter->Hits = 0;
            batter->Singles = 0;
            batter->Doubles = 0;
            batter->Triples = 0;
            batter->HomeRuns = 0;
            batter->BuntSuccesses = 0;
            batter->SacFlies = 0;
            batter->GIDP = 0;
            batter->Strikeouts = 0;
            batter->Walks_4Balls = 0;
            batter->Walks_Hit = 0;
            batter->RBI = 0;
            batter->runs = 0;
            batter->BasesStolen = 0;
            batter->AB_W_RISP = 0;
            batter->hits_W_RISP = 0;
            batter->runnersAdvancedAgainst = 0;
            batter->fielder_playsInvolvedIn = 0;
            batter->RBI_W_RISP = 0;
            batter->HR_W_RISP = 0;
            batter->_19 = 0;
            batter->currentPosition[0] = 0;
            batter->currentPosition[1] = 0;
            batter->currentPosition[2] = 0;
            batter->currentPosition[3] = 0;
            batter->currentPosition[4] = 0;
            batter->currentPosition[5] = 0;
            batter->currentPosition[6] = 0;
            batter->currentPosition[7] = 0;
            batter->currentPosition[8] = 0;
            batter->BigPlays = 0;
            batter->StarHitsActivated = 0;

            pitcher->_00 = 0;
            pitcher->runsAllowed = 0;
            pitcher->earnedRunsAllowed = 0;
            pitcher->_06 = 0;
            pitcher->_08 = 0;
            pitcher->_0A = 0;
            pitcher->_0C = 0;
            pitcher->pitchesThrown = 0;
            pitcher->stamina = startingStamina;
            pitcher->wasPitcher = 0;
            pitcher->_13[0] = 0;
            pitcher->_13[1] = 0;
            pitcher->_13[2] = 0;
            pitcher->_13[3] = 0;
            pitcher->_13[4] = 0;
            pitcher->_13[5] = 0;
            pitcher->_13[6] = 0;
            pitcher->outsAsPitcher = 0;
            pitcher->maxPitchSpeed = 0;
            pitcher->_1C = 0;
            pitcher->starPitchesThrown = 0;

            pitchingInfo_A_H[team][i][0] = 0;
            pitchingInfo_A_H[team][i][1] = 0;
        }
    }

    for (team = 0; team < 2; team++) {
        storedInningInfo._44[team] = 1;
        storedInningInfo._48[team] = 1;
        storedInningInfo._4C[team] = 1;
        storedInningInfo.noHitterTracker[team] = 1;
        storedInningInfo.consecutiveStrikeouts[team] = 0;
        storedInningInfo.nABs[team * 2] = 0;
        storedInningInfo.consecutiveABsWithOuts[team] = 0;
        (&storedInningInfo.mvpLeader)[team * 2] = -1;
        for (i = 1; i <= 9; i++) {
            storedInningInfo._69[team][i] = 0;
        }
    }

    for (team = 0; team < 2; team++) {
        for (j = 0; j < 19; j++) {
            (&StatsScreenScores.scores[team].total)[j] = 0xFFFF;
            (&StatsScreenScores.hits[team].total)[j] = 0;
        }
        StatsScreenScores.stealsAgainst[team] = 0;
        StatsScreenScores.mvpRosterLoc[team] = -1;
    }
    for (team = 0; team < 2; team++) {
        for (j = 0; j < 10; j++) {
            StatsScreenScores.pitcherLog[team][j].pitcher = -1;
            StatsScreenScores.pitcherLog[team][j].inning = 0;
        }
        for (j = 0; j < 5; j++) {
            StatsScreenScores.catcherLog[team][j] = -1;
        }
    }
    for (i = 0; i < 30; i++) {
        StatsScreenScores._A0[i] = -1;
    }
    StatsScreenScores.winningPitcher = -1;
    StatsScreenScores.losingPitcher = -1;
    StatsScreenScores.savePitcher = -1;
    StatsScreenScores.inning = 0;
    StatsScreenScores.noHitterKind = 0;
    for (i = 6; i < 14; i++) {
        StatsScreenScores._F8[i - 6] = -1;
    }

    for (team = 0; team < 2; team++) {
        for (i = 0; i < 100; i++) {
            lbl_803532A8[team][i].a = 0;
            lbl_803532A8[team][i].b = 0;
            lbl_803532A8[team][i].e = -1;
            lbl_803532A8[team][i].f = 0;
            lbl_803532A8[team][i].c = 0;
            lbl_803532A8[team][i].d = 0;
        }
    }

    for (team = 0; team < 2; team++) {
        for (i = 0; i < 9; i++) {
            lbl_80353260[team][i].c = 0;
            lbl_80353260[team][i].d = 0;
            lbl_80353260[team][i].e = 0xA;
            lbl_80353260[team][i].f = 0;
            lbl_80353260[team][i].a = 9;
            lbl_80353260[team][i].b = 0;
        }
    }

    // Both passes read and write team 0; team 1's onFieldForAPitch flags are never seeded here.
    for (team = 0; team < 2; team++) {
        for (i = 0; i < 9; i++) {
            if (lineUpInfoStruct[0][i][3] == 1) {
                BatterStats_P1_P2[0][i].onFieldForAPitch = 1;
            }
        }
    }

    PitcherStats_P1_P2[g_GameLogic.teamFielding]
                      [g_GameLogic.battingOrderAndPositionMapping[g_Scores.halfInning ^ 1][0][0]]
                          .wasPitcher = 1;
    PitcherStats_P1_P2[g_GameLogic.teamBatting]
                      [g_GameLogic.battingOrderAndPositionMapping[g_Scores.halfInning][0][0]]
                          .wasPitcher = 1;
    storedInningInfo.lastPitcher = g_GameLogic.battingOrderAndPositionMapping[0][0][0];
    (&storedInningInfo.lastPitcher)[2] = g_GameLogic.battingOrderAndPositionMapping[1][0][0];

    for (team = 0; team < 2; team++) {
        found = 0;
        for (i = 0; i < 9; i++) {
            entry = &lbl_80353260[team ^ g_GameLogic.homeTeamInd]
                                 [g_GameLogic.battingOrderAndPositionMapping[team][i + 1][0]];
            entry->c = 1;
            entry->d = 1;
            entry->e = g_GameLogic.battingOrderAndPositionMapping[team][i + 1][1];
            entry->f = 1;
            entry->a = team;
            entry->b = i + 1;
            if (g_GameLogic.battingOrderAndPositionMapping[team][i + 1][1] == 9) {
                found = 1;
            }
        }
        if (found) {
            entry = &lbl_80353260[team ^ g_GameLogic.homeTeamInd]
                                 [g_GameLogic.battingOrderAndPositionMapping[team][0][0]];
            entry->c = 1;
            entry->d = 1;
            entry->e = 0;
            entry->f = 1;
            entry->a = 9;
            entry->b = 0xA;
        }
    }
    storedInningInfo.nBattersThisInning2Stored = 0;
    storedInningInfo.nBattersThisInning2 = 0;
}

// .text:0x0007BB74 size:0x4C mapped:0x806BAC08
StatisticsBatter* getCurrentBatterStats(void) {
    return &BatterStats_P1_P2[g_GameLogic.teamBatting]
                             [g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.homeTeamBattingInd_fieldingTeam]
                                                                        [g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam]]
                                                                        [0]];
}

// .text:0x0007BBC0 size:0x38 mapped:0x806BAC54
StatisticsPitcher* getCurrentPitcherStats(void) {
    return &PitcherStats_P1_P2[g_GameLogic.teamFielding]
                              [g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0]
                                                                         [0]];
}

// .text:0x0007BBF8 size:0x14 mapped:0x806BAC8C
void fn_3_7BBF8(void) {
    g_Stats.replayPending = 1;
}

// .text:0x0007BC0C size:0x14 mapped:0x806BACA0
void fn_3_7BC0C(void) {
    g_Stats.replayPending = 1;
}

// .text:0x0007BC20 size:0x570 mapped:0x806BACB4
void determineIfReplayShouldPlay(void) {
    s32 reason = 0;
    int arg = 0;
    InMemBallType* ball = &g_Ball;
    inMemStrikes* strikes = &g_Strikes;
    int result;
    int count;
    int count2;

    if (g_GameLogic.freeFieldingPracticeInd != 0) {
        return;
    }
    if (ball->deadBallReason == DEAD_BALL_REASON_HOME_RUN) {
        reason = 2;
        if (storedInningInfo.goAheadRunOccurrences != 0) {
            reason = 9;
        }
        if (g_Ball.homeRunClassification == 1) {
            reason = 0xD;
        }
    } else if (g_Scores._C2 != 0) {
        result = storedInningInfo.abResultTemporary;
        if (result >= 6 && result <= 10) {
            reason = 3;
            if (reason == 3) {
                InMemRunnerType* runner = &g_Runners[0];
                if (strikes->outs != 3 && runner->runnerOnFieldOrOutOrScored != RUNNER_STATUS_OUT_DURING_PLAY &&
                    runner->runnerOnFieldOrOutOrScored != RUNNER_STATUS_SCORED_DURING_PLAY) {
                    reason = 4;
                }
            }
            if (ball->fielderWithBallIndexStored2 != 6 && ball->fielderWithBallIndexStored2 != 7 &&
                ball->fielderWithBallIndexStored2 != 8) {
                arg = reason;
                reason = 1;
            }
            if (g_pCamera->_AC6 == 3) {
                arg = reason;
                reason = 1;
            }
        }
        if (result == 0x11) {
            if (g_Scores._A6 <= 1) {
                reason = 5;
            } else if (g_Scores._A6 <= 1 && g_Scores._pad_AC >= 3) {
                reason = 5;
            }
            if (storedInningInfo.goAheadRunOccurrences != 0) {
                reason = 0xB;
            }
        }
        result = g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total -
                 g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total;
        if (result > 4 || result < -4) {
            reason = 0;
        }
    } else {
        inMemCamera* cam = g_pCamera;
        BOOL gameEnding = g_GameLogic.EventTriggers_EndOfGame;

        if (cam->_A50 >= 2) {
            if (gameEnding) {
                if (cam->_A98 > 0 &&
                    (storedInningInfo.abResultTemporary == 0x12 || storedInningInfo.abResultTemporary == 0x13 ||
                     storedInningInfo.abResultTemporary == 0x1A)) {
                    reason = 7;
                } else if (cam->_A98 > 0 && storedInningInfo.abResultTemporary >= 0x14 &&
                           storedInningInfo.abResultTemporary <= 0x1B) {
                    reason = 8;
                }
            } else {
                count = 0;
                if (g_Runners[1].rosterID != -1) {
                    count = 1;
                }
                if (g_Runners[2].rosterID != -1) {
                    count++;
                }
                if (g_Runners[3].rosterID != -1) {
                    count++;
                }
                if (g_Scores._A6 <= 4 && count == 3) {
                    if (cam->_A98 > 0 &&
                    (storedInningInfo.abResultTemporary == 0x12 || storedInningInfo.abResultTemporary == 0x13 ||
                     storedInningInfo.abResultTemporary == 0x1A)) {
                    reason = 7;
                } else if (cam->_A98 > 0 && storedInningInfo.abResultTemporary >= 0x14 &&
                           storedInningInfo.abResultTemporary <= 0x1B) {
                    reason = 8;
                }
                }
                count2 = 0;
                if (g_Runners[2].rosterID != -1) {
                    count2 = 1;
                }
                if (g_Runners[3].rosterID != -1) {
                    count2++;
                }
                if (g_Scores._A6 <= count2 && count2 > 0) {
                    if (cam->_A98 > 0 &&
                    (storedInningInfo.abResultTemporary == 0x12 || storedInningInfo.abResultTemporary == 0x13 ||
                     storedInningInfo.abResultTemporary == 0x1A)) {
                    reason = 7;
                } else if (cam->_A98 > 0 && storedInningInfo.abResultTemporary >= 0x14 &&
                           storedInningInfo.abResultTemporary <= 0x1B) {
                    reason = 8;
                }
                }
            }
        }
        result = storedInningInfo.abResultTemporary;
        if (result >= 0x24 && result <= 0x26 && cam->_A50 == 2) {
            if (g_GameLogic.EventTriggers_EndOfGame) {
                reason = 6;
            } else {
                count = 0;
                if (g_Runners[1].rosterID != -1) {
                    count = 1;
                }
                if (g_Runners[2].rosterID != -1) {
                    count++;
                }
                if (g_Runners[3].rosterID != -1) {
                    count++;
                }
                if (g_Scores._A6 <= 4 && count == 3) {
                    reason = 6;
                }
                count2 = 0;
                if (g_Runners[2].rosterID != -1) {
                    count2 = 1;
                }
                if (g_Runners[3].rosterID != -1) {
                    count2++;
                }
                if (g_Scores._A6 <= count2 && count2 > 0) {
                    reason = 6;
                }
            }
        }
    }

    if (reason == 0) {
        return;
    }
    switch (reason) {
    case 2:
    case 9:
        g_Stats.replayReason = 2;
        break;
    case 13:
        g_Stats.replayReason = 0xD;
        break;
    case 3:
    case 10:
        g_Stats.replayReason = 3;
        break;
    case 4:
        g_Stats.replayReason = 4;
        break;
    case 5:
        g_Stats.replayReason = 5;
        break;
    case 6:
        g_Stats.replayReason = 6;
        break;
    case 7:
        g_Stats.replayReason = 7;
        break;
    case 8:
        g_Stats.replayReason = 1;
        g_Stats.replayArg = 0;
        break;
    case 11:
        g_Stats.replayReason = 0xB;
        break;
    default:
        g_Stats.replayReason = 1;
        g_Stats.replayArg = arg;
        break;
    }
    g_Stats.replayPending = 1;
}

// .text:0x0007C190 size:0x4 mapped:0x806BB224
void fn_3_7C190(void) {
    return;
}

// .text:0x0007C194 size:0x68 mapped:0x806BB228
BOOL checkReplaySkipButton(void) {
    if (g_Stats.playFrameCounter < 0x5A) {
        return FALSE;
    }
    if (g_Stats.playFrameCounter > g_Stats._0028 - 0x3C) {
        return FALSE;
    }
    return checkForButtonPressToSkip(1, 0x1100) != 0;
}
