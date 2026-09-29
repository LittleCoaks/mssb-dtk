#define SQRT2_LINKAGE static
#include "game/match_setup/result_stats.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/math/game_math.h"

extern void starMissionsWholeGame(void);
extern void starMissionsQuantityBased(int missionType, int rosterLocation);
extern u8 lbl_3_data_60F8[10];
extern u8 lbl_80354768[];
extern u8 characterStaticIndexes[0x144];
extern u8 pitchingInfo_A_H[2][9][5];
extern u8 abResultList[2][100];
extern struct {
    u8 _00[0x40];
    s16 humanTeam;
} lbl_3_common_bss_37400;

#define MVP_LEADER(team) (&storedInningInfo.mvpLeader)[(team) * 2]
#define MVP_POINTS(team) (&storedInningInfo.mvpLeader)[(team) * 2 + 1]

#define NO_HITTER_TRACKER storedInningInfo.noHitterTracker[g_GameLogic.awayTeamBattingInd_battingTeam]

#define SAT_INC_U8(x)     \
    if ((x) < 0xFE) {     \
        (x)++;            \
    } else {              \
        (x) = 0xFF;       \
    }
#define SAT_INC_U16(x)    \
    if ((x) < 0xFFFE) {   \
        (x)++;            \
    } else {              \
        (x) = 0xFFFF;     \
    }

// .text:0x000759BC size:0x7B8 mapped:0x806B4A50
void MVPCalculation(void) {
    int winner = -1;
    int slot = -1;
    int mvpTeam;
    int i;
    int k;
    int best;
    int bestIdx;
    int score[9];
    s16 result = g_Scores.winnerCd;

    StatsScreenScores.mvpCharID = -1;
    if (result == 0 || result == 1) {
        winner = result;
        slot = result ^ g_GameLogic.homeTeamInd;
    }
    StatsScreenScores.mvpKind = 0;
    if (result == 0) {
        StatsScreenScores.mvpCharID = inMemRoster[slot][g_GameLogic.Team_CaptainRosterLoc[slot]].stats.CharID;
    } else if (result == 1) {
        StatsScreenScores.mvpCharID = inMemRoster[slot][g_GameLogic.Team_CaptainRosterLoc[slot]].stats.CharID;
    } else {
        StatsScreenScores.mvpCharID = inMemRoster[slot][g_GameLogic.Team_CaptainRosterLoc[random_fn_3_9EE24(2)]].stats.CharID;
    }

    if (winner != 2 &&
        !((g_d_GameSettings.p2_CPU_match_code == 0 || g_d_GameSettings.p2_CPU_match_code == 3) &&
          ((g_GameLogic.teamIsCPU[0] == 0 && slot != 0) || (g_GameLogic.teamIsCPU[1] == 0 && slot == 0)))) {
        if (StatsScreenScores._F8[3] >= 0) {
            mvpTeam = slot;
            MVP_LEADER(winner) = StatsScreenScores._F8[3];
            StatsScreenScores.mvpRosterLoc[mvpTeam] = MVP_LEADER(winner);
            goto found;
        }
        if (StatsScreenScores.noHitterKind == 1 && g_Scores.inningLimit >= 5) {
            mvpTeam = slot;
            MVP_LEADER(winner) = StatsScreenScores.pitcherLog[slot][0].pitcher;
            StatsScreenScores.mvpRosterLoc[mvpTeam] = MVP_LEADER(winner);
            goto found;
        }
        if (StatsScreenScores.noHitterKind == 2 && g_Scores.inningLimit >= 5) {
            mvpTeam = slot;
            MVP_LEADER(winner) = StatsScreenScores.pitcherLog[slot][0].pitcher;
            StatsScreenScores.mvpRosterLoc[mvpTeam] = MVP_LEADER(winner);
            goto found;
        }
        if (StatsScreenScores._F8[2] >= 0) {
            mvpTeam = slot;
            MVP_LEADER(winner) = StatsScreenScores._F8[2];
            StatsScreenScores.mvpRosterLoc[mvpTeam] = MVP_LEADER(winner);
            goto found;
        }
        if (winner >= 0 && StatsScreenScores._F8[6] == slot && StatsScreenScores._F8[5] == StatsScreenScores._F8[7]) {
            mvpTeam = slot;
            MVP_LEADER(winner) = StatsScreenScores._F8[7];
            StatsScreenScores.mvpRosterLoc[mvpTeam] = MVP_LEADER(winner);
            goto found;
        }

        for (i = 0; i < 2; i++) {
            best = 0;
            bestIdx = -1;
            for (k = 0; k < 9; k++) {
                score[k] = 0;
                if (winner == i) {
                    if (k == StatsScreenScores.winningPitcher) {
                        score[k] = lbl_3_data_60F8[0];
                    }
                    if (k == StatsScreenScores._F8[7]) {
                        if (StatsScreenScores._100 != 0) {
                            score[k] = lbl_3_data_60F8[1];
                        } else {
                            score[k] = lbl_3_data_60F8[4];
                        }
                    }
                }
                score[k] += lbl_3_data_60F8[2] * BatterStats_P1_P2[i ^ g_GameLogic.homeTeamInd][k].HomeRuns;
                score[k] += lbl_3_data_60F8[3] * BatterStats_P1_P2[i ^ g_GameLogic.homeTeamInd][k].currentPosition[8];
                score[k] += lbl_3_data_60F8[5] * BatterStats_P1_P2[i ^ g_GameLogic.homeTeamInd][k].BigPlays;
                score[k] += lbl_3_data_60F8[6] * PitcherStats_P1_P2[i ^ g_GameLogic.homeTeamInd][k]._1C;
                score[k] += lbl_3_data_60F8[7] * BatterStats_P1_P2[i ^ g_GameLogic.homeTeamInd][k].RBI;
                score[k] += lbl_3_data_60F8[8] * (BatterStats_P1_P2[i ^ g_GameLogic.homeTeamInd][k].Hits +
                                                  BatterStats_P1_P2[i ^ g_GameLogic.homeTeamInd][k].Walks_4Balls +
                                                  BatterStats_P1_P2[i ^ g_GameLogic.homeTeamInd][k].Walks_Hit);
                score[k] += lbl_3_data_60F8[9] * BatterStats_P1_P2[i ^ g_GameLogic.homeTeamInd][k].BasesStolen;
                if (score[k] > best) {
                    best = score[k];
                    bestIdx = k;
                }
            }
            MVP_LEADER(i) = bestIdx;
            MVP_POINTS(i) = best;
        }
    }

    if (g_GameLogic.teamIsCPU[0] != g_GameLogic.teamIsCPU[1]) {
        mvpTeam = g_GameLogic.teamIsCPU[0] != 0;
        if (slot == mvpTeam) {
            StatsScreenScores.mvpRosterLoc[mvpTeam] = MVP_LEADER(winner);
            StatsScreenScores.mvpKind = 1;
        } else if (slot >= 0) {
            StatsScreenScores.mvpRosterLoc[mvpTeam] = g_GameLogic.Team_CaptainRosterLoc[mvpTeam];
            StatsScreenScores.mvpKind = 2;
        } else {
            StatsScreenScores.mvpRosterLoc[mvpTeam] = g_GameLogic.Team_CaptainRosterLoc[mvpTeam];
            StatsScreenScores.mvpKind = 3;
        }
    } else {
        mvpTeam = slot;
        if (mvpTeam >= 0) {
            StatsScreenScores.mvpRosterLoc[mvpTeam] = MVP_LEADER(winner);
            goto found;
        }
        mvpTeam = 0;
        StatsScreenScores.mvpRosterLoc[0] = g_GameLogic.Team_CaptainRosterLoc[0];
        StatsScreenScores.mvpKind = 3;
    }
    goto mvpChosen;

found:
    StatsScreenScores.mvpKind = 1;

mvpChosen:
    StatsScreenScores.mvpCharID = inMemRoster[mvpTeam][StatsScreenScores.mvpRosterLoc[mvpTeam]].stats.CharID;
    if (g_d_GameSettings.p2_CPU_match_code == 0 || g_d_GameSettings.p2_CPU_match_code == 3) {
        if ((g_d_GameSettings.p2_CPU_match_code == 0 && mvpTeam == 0) ||
            (g_d_GameSettings.p2_CPU_match_code == 3 && mvpTeam == 1)) {
            if (g_Scores.inningLimit >= 5 && StatsScreenScores.mvpKind == 1) {
                if (g_d_GameSettings.exhibitionMatchInd != 0) {
                    lbl_80354768[0xCF18 + characterStaticIndexes[StatsScreenScores.mvpCharID * 6 + 1]] = 1;
                }
                g_GameLogic._13D = 1;
            }
        }
    }
}

// .text:0x00076174 size:0x3E4 mapped:0x806B5208
void winningPitcher(void) {
    s16 w = g_Scores.winnerCd;
    int slot = w ^ g_GameLogic.homeTeamInd;
    int k;
    int best;
    int bestOuts;
    StatisticsPitcher* ps;
    StatisticsPitcher* cur;
    StatisticsPitcher* cmp;
    s8* pB3;
    int b3;
    u8 startPitcher;
    int d;

    if (g_Scores._BB[w] == 1) {
        StatsScreenScores.winningPitcher = g_Scores._AF[w];
        return;
    }
    if (g_Scores.scores[1].byInning[g_Scores.Inning - 1] > 0 && w == 1) {
        StatsScreenScores.winningPitcher = g_Scores._B1[w];
        return;
    }
    if (g_Scores.Inning < 5) {
        StatsScreenScores.winningPitcher = g_Scores._B1[w];
        return;
    }

    pB3 = &g_Scores._B3[w];
    b3 = *pB3;
    ps = PitcherStats_P1_P2[slot];
    cur = &ps[b3];
    if (g_Scores._B9[w] == 1) {
        if (g_Scores.Inning == 5) {
            if (cur->outsAsPitcher >= 12) {
                StatsScreenScores.winningPitcher = g_Scores._AF[w];
                return;
            }
        } else {
            if (cur->outsAsPitcher >= 15) {
                StatsScreenScores.winningPitcher = g_Scores._AF[w];
                return;
            }
        }
        best = -1;
        bestOuts = 0;
        for (k = 0; k < 9; k++) {
            cur = &ps[k];
            if (cur->_00 != 0 && b3 != k) {
                if (best == -1) {
                    bestOuts = cur->outsAsPitcher;
                    best = k;
                } else {
                    d = cur->outsAsPitcher - bestOuts;
                    if (d >= 3) {
                        bestOuts = cur->outsAsPitcher;
                        best = k;
                    } else if (d > -3) {
                        cmp = &ps[best];
                        if (cur->earnedRunsAllowed < cmp->earnedRunsAllowed) {
                            best = k;
                        } else if (cur->earnedRunsAllowed == cmp->earnedRunsAllowed) {
                            if (cur->_00 - cur->outsAsPitcher < cmp->_00 - cmp->outsAsPitcher) {
                                best = k;
                            } else if (cur->_00 - cur->outsAsPitcher == cmp->_00 - cmp->outsAsPitcher) {
                                if (cur->outsAsPitcher > bestOuts) {
                                    best = k;
                                } else if (bestOuts == cur->outsAsPitcher) {
                                    if (cur->pitchesThrown < cmp->pitchesThrown) {
                                        best = k;
                                    }
                                }
                            }
                        }
                        if (cur->outsAsPitcher > bestOuts) {
                            bestOuts = cur->outsAsPitcher;
                        }
                    }
                }
            }
        }
        StatsScreenScores.winningPitcher = BatterStats_P1_P2[slot][best]._00;
    } else {
        int bestVal = 0;
        int bestIdx = -1;

        if (g_Scores._BB[w] == 2) {
            StatsScreenScores.winningPitcher = b3;
            return;
        }
        if (b3 == -1 || b3 == g_Scores._AF[w]) {
            startPitcher = g_Scores._AF[w];
            cur = ps;
            for (k = 0; k < 9; k++, cur++) {
                if (g_Scores._AF[w] != k && b3 != k) {
                    if (bestIdx == -1) {
                        if (pitchingInfo_A_H[w][k][0] != 0 && bestVal == 0) {
                            bestIdx = k;
                            bestVal = pitchingInfo_A_H[w][k][0];
                        }
                    } else if (pitchingInfo_A_H[w][k][0] > bestVal) {
                        bestIdx = k;
                        bestVal = pitchingInfo_A_H[w][k][0];
                    } else if (bestVal == pitchingInfo_A_H[w][k][0]) {
                        cmp = &ps[bestIdx];
                        if (cur->earnedRunsAllowed < cmp->earnedRunsAllowed) {
                            bestIdx = k;
                        } else if (cur->earnedRunsAllowed == cmp->earnedRunsAllowed) {
                            if (cur->_00 < cmp->_00) {
                                bestIdx = k;
                            } else if (cur->_00 == cmp->_00) {
                                if (cur->pitchesThrown < cmp->pitchesThrown) {
                                    bestIdx = k;
                                }
                            }
                        }
                    }
                }
            }
            g_Scores._AF[w] = startPitcher;
        }
        if (bestIdx == -1) {
            StatsScreenScores.winningPitcher = *pB3;
        } else {
            StatsScreenScores.winningPitcher = BatterStats_P1_P2[slot][bestIdx]._00;
        }
        if (StatsScreenScores.winningPitcher == -1) {
            StatsScreenScores.winningPitcher = g_Scores._B1[w];
        }
    }
}

// .text:0x00076558 size:0x544 mapped:0x806B55EC
void endOfGameStats_MVP(void) {
    int k;
    int i;
    int j;
    u8 tracker;

    if (g_Scores.winnerCd == 0) {
        StatsScreenScores.winnerSlot = g_GameLogic.homeTeamInd;
    }
    if (g_Scores.winnerCd == 1) {
        StatsScreenScores.winnerSlot = g_GameLogic.homeTeamInd ^ 1;
    }
    if (g_Scores.winnerCd == 2) {
        StatsScreenScores.winnerSlot = 2;
    }

    if (g_Scores.winnerCd == 0 || g_Scores.winnerCd == 1) {
        winningPitcher();
        SAT_INC_U8(PitcherStats_P1_P2[StatsScreenScores.winnerSlot][StatsScreenScores.winningPitcher]._13[0]);
        if (g_Scores._BB[g_Scores.winnerCd] == 1) {
            SAT_INC_U8(PitcherStats_P1_P2[StatsScreenScores.winnerSlot][StatsScreenScores.winningPitcher]._13[4]);
            if (*(u16*)&StatsScreenScores.scores[StatsScreenScores.winnerSlot ^ 1].total == 0) {
                SAT_INC_U8(PitcherStats_P1_P2[StatsScreenScores.winnerSlot][StatsScreenScores.winningPitcher]._13[5]);
                tracker = storedInningInfo.noHitterTracker[g_Scores.winnerCd];
                if (tracker == 1) {
                    StatsScreenScores.noHitterKind = 1;
                }
                if (tracker == 2) {
                    StatsScreenScores.noHitterKind = 2;
                }
            }
        }
        if (StatsScreenScores.winningPitcher != g_Scores._AF[g_Scores.winnerCd]) {
            SAT_INC_U8(PitcherStats_P1_P2[StatsScreenScores.winnerSlot][StatsScreenScores.winningPitcher]._13[3]);
        }
        StatsScreenScores.losingPitcher = g_Scores._B5[g_Scores.winnerCd ^ 1];
        SAT_INC_U8(PitcherStats_P1_P2[StatsScreenScores.winnerSlot ^ 1][g_Scores._B5[g_Scores.winnerCd ^ 1]]._13[1]);
        if (g_Scores._BB[g_Scores.winnerCd ^ 1] == 1) {
            SAT_INC_U8(PitcherStats_P1_P2[StatsScreenScores.winnerSlot ^ 1][g_Scores._B5[g_Scores.winnerCd ^ 1]]._13[4]);
        }
        if (g_Scores._B7[g_Scores.winnerCd] != StatsScreenScores.winningPitcher && g_Scores._B7[g_Scores.winnerCd] >= 0) {
            StatsScreenScores.savePitcher = g_Scores._B7[g_Scores.winnerCd];
            SAT_INC_U8(PitcherStats_P1_P2[StatsScreenScores.winnerSlot][g_Scores._B7[g_Scores.winnerCd]]._13[2]);
        }

        for (i = 0; i < 2; i++) {
            for (k = 0; k < 9; k++) {
                if (i == g_Scores.winnerCd) {
                    if (k == StatsScreenScores.winningPitcher) {
                        pitchingInfo_A_H[StatsScreenScores.winnerSlot][k][1] = 0;
                    }
                    if (k == StatsScreenScores.savePitcher) {
                        pitchingInfo_A_H[StatsScreenScores.winnerSlot][k][1] = 0;
                    }
                }
                if (i == (g_Scores.winnerCd ^ 1)) {
                    if (k == StatsScreenScores.losingPitcher) {
                        pitchingInfo_A_H[StatsScreenScores.winnerSlot ^ 1][k][1] = 0;
                    }
                }
            }
        }
    }

    j = 0;
    while (j < 9) {
        PitcherStats_P1_P2[0][j]._13[6] += pitchingInfo_A_H[0][j][1];
        PitcherStats_P1_P2[1][j]._13[6] += pitchingInfo_A_H[1][j][1];
        j++;
    }
    StatsScreenScores.inning = g_Scores.Inning;
    MVPCalculation();
    if (g_d_GameSettings.exhibitionMatchInd == 0) {
        starMissionsWholeGame();
    }
}

// .text:0x00076A9C size:0x1DC mapped:0x806B5B30
void steal_pickoff_incrementSteal_runsStats(void) {
    int i;
    int runs;

    for (i = 1; i < 4; i++) {
        if ((g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD ||
             g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) &&
            i != g_Runners[i].currentBase) {
            if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd == 3 && g_Runners[i].furthestBaseForcedToGoToOnWalk == 0) {
                continue;
            }
            if (g_Runners[i].forceOutCd <= 0) {
                SAT_INC_U8(BatterStats_P1_P2[g_GameLogic.teamBatting][g_Runners[i].rosterID].BasesStolen);
                if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400.humanTeam == g_GameLogic.teamBatting) {
                    starMissionsQuantityBased(10, g_Runners[i].rosterID);
                }
            }
        }
    }

    runs = g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total - g_Scores._A0;
    for (i = 3; i >= 0; i--) {
        if (runs <= 0) {
            break;
        }
        if (g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) {
            SAT_INC_U8(BatterStats_P1_P2[g_GameLogic.teamBatting][g_Runners[i].rosterID].runs);
            runs--;
            if (g_d_GameSettings.exhibitionMatchInd == 0 && g_GameLogic.teamBatting == lbl_3_common_bss_37400.humanTeam) {
                starMissionsQuantityBased(11, g_Runners[i].rosterID);
            }
        }
    }
}

// .text:0x00076C78 size:0x90 mapped:0x806B5D0C
void fn_3_76C78(void) {
    int i;

    for (i = 0; i < 50; i++) {
        if (StatsScreenScores._A0[i] == -1) {
            if (g_GameLogic.teamBatting == 0) {
                StatsScreenScores._A0[i] = g_Batter.rosterID;
            } else {
                StatsScreenScores._A0[i] = (s8)g_Batter.rosterID + 9;
            }
            return;
        }
    }
}

// .text:0x00076D08 size:0xC0C mapped:0x806B5D9C
void updateStatsBasedOnABResult(int rosterID, int result, int fielder, int rbis) {
    int pitcherSlot;
    StatisticsPitcher* pitcher;
    int isAtBat = 0;
    int idx;
    int runs;
    StatisticsBatter* batter;
    int i;

    pitcherSlot = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0];
    batter = &BatterStats_P1_P2[g_GameLogic.teamBatting][rosterID];
    pitcher = &PitcherStats_P1_P2[g_GameLogic.teamFielding][pitcherSlot];
    SAT_INC_U8(batter->plateAppearances);

    idx = g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam] +
          (storedInningInfo._44[g_GameLogic.homeTeamBattingInd_fieldingTeam] - 1) * 9 - 1;
    if (idx >= 100) {
        for (i = 0; i < 99; i++) {
            lbl_803532A8[g_GameLogic.teamBatting][i].a = lbl_803532A8[g_GameLogic.teamBatting][i + 1].a;
            lbl_803532A8[g_GameLogic.teamBatting][i].b = lbl_803532A8[g_GameLogic.teamBatting][i + 1].b;
            lbl_803532A8[g_GameLogic.teamBatting][i].e = lbl_803532A8[g_GameLogic.teamBatting][i + 1].e;
            lbl_803532A8[g_GameLogic.teamBatting][i].f = lbl_803532A8[g_GameLogic.teamBatting][i + 1].f;
            lbl_803532A8[g_GameLogic.teamBatting][i].c = lbl_803532A8[g_GameLogic.teamBatting][i + 1].c;
            lbl_803532A8[g_GameLogic.teamBatting][i].d = lbl_803532A8[g_GameLogic.teamBatting][i + 1].d;
            abResultList[g_GameLogic.teamBatting][i] = abResultList[g_GameLogic.teamBatting][i + 1];
        }
        idx = 99;
    }
    lbl_803532A8[g_GameLogic.teamBatting][idx].a = g_Scores.Inning;
    lbl_803532A8[g_GameLogic.teamBatting][idx].b =
        g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam];
    lbl_803532A8[g_GameLogic.teamBatting][idx].e = rosterID;
    lbl_803532A8[g_GameLogic.teamBatting][idx].f = result;
    abResultList[g_GameLogic.teamBatting][idx] = storedInningInfo.abResultFinal;
    lbl_803532A8[g_GameLogic.teamBatting][idx].c = (s8)fielder;
    lbl_803532A8[g_GameLogic.teamBatting][idx].d = rbis;
    if (result == AT_BAT_RESULT_HOME_RUN) {
        int angle = calculateAngleFromCoordinates(g_Ball.landingSpotLocation.x, g_Ball.landingSpotLocation.z);
        if (angle < 0x380) {
            lbl_803532A8[g_GameLogic.teamBatting][idx].c = 8;
        } else if (angle < 0x480) {
            lbl_803532A8[g_GameLogic.teamBatting][idx].c = 7;
        } else {
            lbl_803532A8[g_GameLogic.teamBatting][idx].c = 6;
        }
    }

    switch (result) {
    case AT_BAT_RESULT_STRIKEOUT:
        SAT_INC_U8(batter->Strikeouts);
        isAtBat = 1;
        break;
    case AT_BAT_RESULT_WALK:
        SAT_INC_U8(batter->Walks_4Balls);
        break;
    case AT_BAT_RESULT_HIT_BY_PITCH:
        SAT_INC_U8(batter->Walks_Hit);
        break;
    case AT_BAT_RESULT_SINGLE:
        SAT_INC_U8(batter->Singles);
        SAT_INC_U8(batter->Hits);
        isAtBat = 1;
        break;
    case AT_BAT_RESULT_DOUBLE:
        SAT_INC_U8(batter->Doubles);
        SAT_INC_U8(batter->Hits);
        isAtBat = 1;
        break;
    case AT_BAT_RESULT_TRIPLE:
        SAT_INC_U8(batter->Triples);
        SAT_INC_U8(batter->Hits);
        isAtBat = 1;
        break;
    case AT_BAT_RESULT_HOME_RUN:
        SAT_INC_U8(batter->HomeRuns);
        SAT_INC_U8(batter->Hits);
        isAtBat = 1;
        fn_3_76C78();
        break;
    case AT_BAT_RESULT_BUNT:
        SAT_INC_U8(batter->BuntSuccesses);
        break;
    case AT_BAT_RESULT_SAC_FLY:
        SAT_INC_U8(batter->SacFlies);
        break;
    case AT_BAT_RESULT_DOUBLE_PLAY:
        SAT_INC_U8(batter->GIDP);
        isAtBat = 1;
        break;
    default:
        isAtBat = 1;
        break;
    }

    if (batter->AtBats < 0xFF - isAtBat) {
        batter->AtBats += isAtBat;
    } else {
        batter->AtBats = 0xFF;
    }
    if (batter->RBI < 0xFF - rbis) {
        batter->RBI += rbis;
    } else {
        batter->RBI = 0xFF;
    }
    if (g_RunningLogic.runnersInScoringPosition != 0) {
        if (batter->AB_W_RISP < 0xFF - isAtBat) {
            batter->AB_W_RISP += isAtBat;
        } else {
            batter->AB_W_RISP = 0xFF;
        }
        if (result >= AT_BAT_RESULT_SINGLE && result <= AT_BAT_RESULT_HOME_RUN) {
            SAT_INC_U8(batter->hits_W_RISP);
        }
        if (result == AT_BAT_RESULT_HOME_RUN) {
            SAT_INC_U8(batter->HR_W_RISP);
        }
        if (rbis != 0) {
            if (batter->RBI_W_RISP < 0xFF - rbis) {
                batter->RBI_W_RISP += rbis;
            } else {
                batter->RBI_W_RISP = 0xFF;
            }
        }
    }

    runs = g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total - g_Scores._A0;
    for (i = 3; i >= 0; i--) {
        if (runs <= 0) {
            break;
        }
        if (g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) {
            SAT_INC_U8(BatterStats_P1_P2[g_GameLogic.teamBatting][g_Runners[i].rosterID].runs);
            runs--;
            if (g_d_GameSettings.exhibitionMatchInd == 0 && g_GameLogic.teamBatting == lbl_3_common_bss_37400.humanTeam) {
                starMissionsQuantityBased(11, g_Runners[i].rosterID);
            }
        }
    }

    g_Scores._B1[g_GameLogic.awayTeamBattingInd_battingTeam] = pitcherSlot;
    SAT_INC_U16(pitcher->_00);
    if (pitcher->outsAsPitcher < 0xFF - g_Strikes.outs - g_Strikes.storedOuts) {
        pitcher->outsAsPitcher += g_Strikes.outs - g_Strikes.storedOuts;
    } else {
        pitcher->outsAsPitcher = 0xFF;
    }
    if (g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total >
        g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total) {
        pitchingInfo_A_H[g_GameLogic.awayTeamBattingInd_battingTeam][pitcherSlot][0] +=
            g_Strikes.outs - g_Strikes.storedOuts;
    }
    if (result >= AT_BAT_RESULT_SINGLE && result <= AT_BAT_RESULT_HOME_RUN) {
        SAT_INC_U16(pitcher->_0A);
    }
    if (result == AT_BAT_RESULT_HOME_RUN) {
        SAT_INC_U16(pitcher->_0C);
    }
    if (result == AT_BAT_RESULT_STRIKEOUT) {
        SAT_INC_U8(pitcher->_1C);
    }
    if (result == AT_BAT_RESULT_WALK) {
        if (g_Strikes._1E >= 0) {
            SAT_INC_U16(PitcherStats_P1_P2[g_GameLogic.teamFielding][g_Strikes._1E]._06);
        } else {
            SAT_INC_U16(pitcher->_06);
        }
    }
    if (result == AT_BAT_RESULT_HIT_BY_PITCH) {
        SAT_INC_U16(pitcher->_08);
    }

    if (NO_HITTER_TRACKER != 0) {
        if (storedInningInfo._4C[g_GameLogic.awayTeamBattingInd_battingTeam] > 1) {
            NO_HITTER_TRACKER = 0;
        } else {
            if (NO_HITTER_TRACKER == 1) {
                if ((u32)(result - 2) <= 1 || result == AT_BAT_RESULT_ERROR || result == AT_BAT_RESULT_FIELDERS_CHOICE) {
                    NO_HITTER_TRACKER = 2;
                }
            }
            if (NO_HITTER_TRACKER != 0) {
                if ((u32)(result - 7) <= 3 || g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total > 0 ||
                    StatsScreenScores.pitcherLog[g_GameLogic.teamFielding][1].pitcher >= 0) {
                    NO_HITTER_TRACKER = 0;
                }
            }
        }
    }

    if (g_FieldingLogic.processErrorCode == FIELDING_ERROR_CONFIRMED) {
        SAT_INC_U8(g_Scores.stealSuccesses[g_GameLogic.awayTeamBattingInd_battingTeam]);
        SAT_INC_U8(BatterStats_P1_P2[g_GameLogic.teamFielding][g_Fielders[g_FieldingLogic.lastThrowingFielder].rosterLocation]
                       .runnersAdvancedAgainst);
    }
    if (g_Ball.fielderWithBallIndexStored >= 0 && g_Ball.fielderWithBallIndexStored <= 8) {
        SAT_INC_U8(BatterStats_P1_P2[g_GameLogic.teamFielding][g_Fielders[g_Ball.fielderWithBallIndexStored].rosterLocation]
                       .fielder_playsInvolvedIn);
    }
    if (g_FieldingLogic.bigPlayPotential == 2) {
        if (g_Ball.fielderWithBallIndexStored2 >= 0) {
            SAT_INC_U8(BatterStats_P1_P2[g_GameLogic.teamFielding]
                                        [g_Fielders[g_Ball.fielderWithBallIndexStored2].rosterLocation]
                           .fielder_playsInvolvedIn);
        }
    }

    {
        int battingTeam = g_GameLogic.homeTeamBattingInd_fieldingTeam;
        int battingSlot = g_GameLogic.teamBatting;
        int inning = g_Scores.Inning;

        StatsScreenScores.scores[battingSlot].byInning[inning - 1] = g_Scores.scores[battingTeam].byInning[inning - 1];
        StatsScreenScores.hits[battingSlot].byInning[inning - 1] = g_Scores.hits[battingTeam].byInning[inning - 1];
        StatsScreenScores.scores[battingSlot].total = g_Scores.scores[battingTeam].total;
        StatsScreenScores.hits[battingSlot].total = g_Scores.hits[battingTeam].total;
        StatsScreenScores.stealsAgainst[battingSlot] = g_Scores.stealSuccesses[battingTeam];
        StatsScreenScores.stealsAgainst[g_GameLogic.teamFielding] =
            g_Scores.stealSuccesses[g_GameLogic.awayTeamBattingInd_battingTeam];
    }
}
