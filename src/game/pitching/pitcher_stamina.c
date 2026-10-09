#define SQRT2_LINKAGE static
#include "game/pitching/pitcher_stamina.h"
#include "game/UnknownHomes_Game.h"
#include "game/math/game_math.h"
#include "game/batting/batter_ai.h"

typedef struct {
    s16 rosterID;
    s16 currentRosterID;
    s16 position;
    s16 currentPosition;
} LineupEntry;

#define LINEUP_SLOTS 10

extern struct {
    u8 _00[0x14];
    LineupEntry lineup[TEAMS_PER_GAME][LINEUP_SLOTS];
    u8 _B4[0x202 - 0xB4];
    u8 lineupChanged[TEAMS_PER_GAME];
} pauseControl;

extern s16 lbl_3_data_5EDC[];
extern int getAdjustedPitcherStamina(int team, int rosterID, int flag);

typedef struct {
    int rosterID;
    int differentClass;
} RelieverCandidate;

#define LINEUP_DST(i) pauseControl.lineup[g_GameLogic.teamFielding][i]
#define LINEUP_SRC(i) g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][i]

#define COPY_BATTING_LINEUP()                                \
    for (i = 0; i < LINEUP_SLOTS; i++) {                     \
        LINEUP_DST(i).rosterID = LINEUP_SRC(i)[0];           \
        LINEUP_DST(i).currentRosterID = LINEUP_SRC(i)[0];    \
        LINEUP_DST(i).position = LINEUP_SRC(i)[1];           \
        LINEUP_DST(i).currentPosition = LINEUP_SRC(i)[1];    \
    }

// .text:0x0001DD68 size:0x150 mapped:0x8065CDFC
void updateHighUrgencySituationTracker(void) {
    u8 inning;
    int a;
    int runners;
    int b;
    g_AiLogic.unused_highUrgencySituationTracker = 1;
    runners = 0;
    if (g_RunningLogic._02 & 0x1000) {
        runners = 1;
    }
    if (g_RunningLogic._02 & 0x100) {
        runners++;
    }
    inning = g_Scores._pad_AC;
    if (inning >= 4 && g_Scores.halfInning != 0 && runners != 0) {
        if (g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total + runners >
            g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total) {
            g_AiLogic.unused_highUrgencySituationTracker = 4;
            return;
        }
    }
    if (inning >= 3 && runners != 0) {
        a = g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total;
        b = g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total;
        if (a < b && a + runners >= b) {
            g_AiLogic.unused_highUrgencySituationTracker = 3;
            return;
        } else if (a == b) {
            g_AiLogic.unused_highUrgencySituationTracker = 2;
            return;
        }
    }
    if (g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total + 5 <
        g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total) {
        g_AiLogic.unused_highUrgencySituationTracker = 0;
    }
}

// .text:0x0001DD48 size:0x20 mapped:0x8065CDDC
void trackLastPitchInfo(void) {
    trackLastPitchInfo2();
}

// .text:0x0001DC30 size:0x118 mapped:0x8065CCC4
void cpuCheckPitcherRelief(void) {
    int changed;
    int i;
    if (g_GameLogic.teamIsCPU[g_GameLogic.teamFielding] != 0) {
        changed = 0;
        COPY_BATTING_LINEUP();
        changed |= staminaRelated();
        if (changed) {
            pauseControl.lineupChanged[g_GameLogic.teamFielding] = 1;
        }
    }
}

// .text:0x0001DB5C size:0xD4 mapped:0x8065CBF0
void fn_3_1DB5C(void) {
    int i;
    COPY_BATTING_LINEUP();
    staminaRelated();
}

// .text:0x0001D86C size:0x2F0 mapped:0x8065C900
BOOL staminaRelated(void) {
    RelieverCandidate cand[9];
    int nCand;
    int team = g_GameLogic.teamFielding;
    int pitcher = pauseControl.lineup[team][0].rosterID;
    int newPitcher;
    int pitcherClass;
    int i;
    int pick;
    int nDiff;
    int pos;

    if (getAdjustedPitcherStamina(team, pitcher, 0) >= lbl_3_data_5EDC[3]) {
        return 0;
    }
    for (i = 0, nCand = 0; i < 9; i++) {
        if (getAdjustedPitcherStamina(g_GameLogic.teamFielding, i, 0) >= lbl_3_data_5EDC[3]) {
            cand[nCand].rosterID = i;
            nCand++;
        }
    }
    if (nCand == 0) {
        return 0;
    }
    pitcherClass = inMemRoster[team][pitcher].stats.CharacterClass;
    for (i = 0, nDiff = 0; i < nCand; i++) {
        cand[i].differentClass = 0;
        if (pitcherClass != inMemRoster[team][cand[i].rosterID].stats.CharacterClass) {
            cand[i].differentClass = 1;
            nDiff++;
        }
    }
    if (nDiff != 0) {
        pick = RandomInt_Sim(nDiff);
        for (i = 0; i < nCand; i++) {
            if (cand[i].differentClass != 0) {
                if (pick == 0) {
                    newPitcher = cand[i].rosterID;
                    goto found;
                }
                pick--;
            }
        }
    }
    pick = RandomInt_Sim(nCand);
    for (i = 0; i < nCand; i++) {
        if (pick == 0) {
            newPitcher = cand[i].rosterID;
            goto found;
        }
        pick--;
    }
    return 0;

found:
    for (i = 1; i < LINEUP_SLOTS; i++) {
        if (newPitcher == pauseControl.lineup[team][i].rosterID) {
            pos = pauseControl.lineup[team][i].position;
            pauseControl.lineup[team][i].currentPosition = 0;
            pauseControl.lineup[team][0].currentRosterID = newPitcher;
        }
    }
    for (i = 1; i < LINEUP_SLOTS; i++) {
        if (pitcher == pauseControl.lineup[team][i].rosterID) {
            pauseControl.lineup[team][i].currentPosition = pos;
        }
    }
    return 1;
}
