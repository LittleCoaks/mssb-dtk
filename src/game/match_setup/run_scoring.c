#define SQRT2_LINKAGE static
#include "game/match_setup/run_scoring.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/hud/hud_gauges.h"
#include "game/hud/hud_scoreboard.h"
#include "Unknown/File_0x800b0a14.h"

extern u8 animRelated[0x124];
extern u8 pauseControl[0x264];

// .text:0x0009C794 size:0x35C mapped:0x806DB828
void runScored(void) {
    int scoringRunners;
    int i;
    int fieldingScore = g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total;
    int battingScore = g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total;
    int prevScore = g_Scores._A0;
    BOOL runScoredThisPlay = 0;

    if (g_Scores._C2 == 0) {
        return;
    }
    if (prevScore == 0 && battingScore == 0) {
        storedInningInfo.inningOfFirstRun = g_Scores.Inning;
        storedInningInfo.firstRunHalfInningBottomInd = g_Scores.halfInning;
        storedInningInfo.inningOfGoAheadRun = g_Scores.Inning;
        storedInningInfo.halfInningOfGoAheadRun = g_Scores.halfInning;
        StatsScreenScores.goAheadRunPitcher = g_Pitcher.rosterID;
        runScoredThisPlay = 1;
    } else if (fieldingScore == battingScore) {
        storedInningInfo.inningOfLastTie = g_Scores.Inning;
        storedInningInfo.lastTieHalfInningBottomInd = g_Scores.halfInning;
        storedInningInfo.comebackCounter++;
    } else if (fieldingScore > battingScore) {
        if (prevScore == battingScore) {
            if (storedInningInfo.inningOfLastTie != 0 && storedInningInfo.lastTieHalfInningBottomInd == g_Scores.halfInning) {
                storedInningInfo.inningOfComeback = g_Scores.Inning;
                storedInningInfo.lastComebackHalfInningBottomInd = g_Scores.halfInning;
                storedInningInfo.comebackCounter2++;
                storedInningInfo.inningOfGoAheadRun = g_Scores.Inning;
                storedInningInfo.halfInningOfGoAheadRun = g_Scores.halfInning;
            } else {
                storedInningInfo.inningOfLeadTakenBack = g_Scores.Inning;
                storedInningInfo.halfInningOfLeadTakenBack = g_Scores.halfInning;
                storedInningInfo.leadsTakenBack++;
                storedInningInfo.inningOfGoAheadRun = g_Scores.Inning;
                storedInningInfo.halfInningOfGoAheadRun = g_Scores.halfInning;
            }
            StatsScreenScores.goAheadRunPitcher = g_Pitcher.rosterID;
            runScoredThisPlay = 1;
        } else if (prevScore < battingScore) {
            storedInningInfo.inningOfComeback = g_Scores.Inning;
            storedInningInfo.lastComebackHalfInningBottomInd = g_Scores.halfInning;
            storedInningInfo.comebackCounter2++;
            storedInningInfo.inningOfGoAheadRun = g_Scores.Inning;
            storedInningInfo.halfInningOfGoAheadRun = g_Scores.halfInning;
            StatsScreenScores.goAheadRunPitcher = g_Pitcher.rosterID;
            runScoredThisPlay = 1;
        }
    }
    if (fieldingScore > battingScore && g_Scores.Inning >= g_Scores.inningLimit && g_Scores.halfInning != 0) {
        storedInningInfo.goAheadRunOccurrences = g_Scores.Inning;
        StatsScreenScores.walkOffBatter = g_Batter.rosterID;
        if (g_Ball.deadBallReason == 1) {
            StatsScreenScores.walkOffRunner = g_Batter.rosterID;
            StatsScreenScores.walkOffHomeRunBatter = g_Batter.rosterID;
        } else {
            scoringRunners = 0;
            for (i = 3; i >= 0; i--) {
                if (g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) {
                    scoringRunners++;
                    if (prevScore + scoringRunners > battingScore) {
                        StatsScreenScores.walkOffRunner = g_Runners[i].rosterID;
                        break;
                    }
                }
            }
        }
    }
    if (runScoredThisPlay == 0) {
        return;
    }
    if (g_Scores._pad_AC >= 3) {
        if (storedInningInfo.batterResultBase > 0) {
            StatsScreenScores.lateGoAheadHitTeam = g_GameLogic.teamBatting;
            StatsScreenScores.lateGoAheadHitBatter = g_Batter.rosterID;
        } else {
            StatsScreenScores.lateGoAheadHitTeam = -1;
            StatsScreenScores.lateGoAheadHitBatter = -1;
        }
    }
    StatsScreenScores.goAheadRbiTeam = g_GameLogic.teamBatting;
    StatsScreenScores.goAheadRbiBatter = g_Batter.rosterID;
    if (storedInningInfo.batterResultBase > 0) {
        StatsScreenScores.goAheadRbiWasHit = 1;
    } else {
        StatsScreenScores.goAheadRbiWasHit = 0;
    }
}

// .text:0x0009C578 size:0x21C mapped:0x806DB60C
void matchHudDrawingControl(void) {
    if (g_GameLogic.hudElementLoadingInd != 0 && animRelated[0xA5] == 0) {
        animRelated[0xA5] = 1;
        animRelated[0xA6] = 0;
        animRelated[0xA7] = 0xFF;
        insertGraphicDrawingFunction(init_BallStrikeOutHud, 2);
        insertGraphicDrawingFunction(draw_ScoreInningHud, 2);
        if (animRelated[0xA8] == 0) {
            insertGraphicDrawingFunction(draw_initStarGuageHud, 2);
        }
        if (g_Batter.chemLinksOnBase != 0) {
            insertGraphicDrawingFunction(draw_OnBaseChemLinks, 2);
        }
    }
    if (animRelated[0xAC] == 1 && g_GameLogic.FrameCountOfCurrentPitch == 10) {
        insertGraphicDrawingFunction(HUD_initStarChance, 2);
        animRelated[0xAC] = 2;
    }
    if (animRelated[0xA5] != 0 && animRelated[0xA6] < 0xFF) {
        if (animRelated[0xA6] < 0xF0) {
            animRelated[0xA6] += 0x10;
        } else {
            animRelated[0xA6] = 0xFF;
        }
    }
    if (animRelated[0xA7] != 0 && animRelated[0xA7] < 0xFF) {
        if (animRelated[0xA7] <= 0x10) {
            animRelated[0xA7] = 0;
            animRelated[0xA5] = 0;
        } else {
            animRelated[0xA7] -= 0x10;
        }
    } else if (animRelated[0xA5] != 0) {
        if (g_GameLogic.gameStatus != GAME_STATUS_AT_BAT && g_GameLogic.gameStatus != GAME_STATUS_DEFAULT) {
            if (g_Batter.moonShotInd == 0 || g_Ball.framesSinceHit > 1) {
                animRelated[0xA7] = 0xF0;
            }
        }
        if (pauseControl[0x1D5] != 0) {
            animRelated[0xA7] = 0xF0;
        }
    }
    if (g_GameLogic.gameStatus == GAME_STATUS_TRANSITION) {
        animRelated[0xA7] = 0;
        animRelated[0xA5] = 0;
    }
}
