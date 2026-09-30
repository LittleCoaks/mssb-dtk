#define SQRT2_LINKAGE static
#include "game/match_setup/ai_defaults.h"
#define REP_HEADER_DATA_FN getRepHeaderData_aiDefaults
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/math/game_math.h"
#include "game/pitching/pitcher_ai.h"
#include "game/batting/batter_ai.h"

extern u8 aiDashProbabilities[8];

// .text:0x0001DEB8 size:0x29C mapped:0x8065CF4C
void setDefaultAIValues(void) {
    int i;
    int bonus;
    int scoreA;
    int scoreB;
    UnkInputRelated* dash;

    g_AiLogic.aIDifficultyMultiplierArray[0] = (f32)g_AiLogic._46 / 255.0f;
    g_AiLogic.aIDifficultyMultiplierArray[1] = (f32)g_AiLogic._47 / 255.0f;
    g_AiLogic.unused_highUrgencySituationTracker = 1;

    bonus = 0;
    if (g_RunningLogic._02 & 0x1000) {
        bonus = 1;
    }
    if (g_RunningLogic._02 & 0x100) {
        bonus++;
    }

    if (g_Scores._pad_AC >= 4 && g_Scores.halfInning != 0 && bonus != 0) {
        if (g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total + bonus >
            g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total) {
            g_AiLogic.unused_highUrgencySituationTracker = 4;
            goto finish;
        }
    }
    if (g_Scores._pad_AC >= 3 && bonus != 0) {
        scoreA = g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total;
        scoreB = g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total;
        if (scoreA < scoreB && scoreA + bonus >= scoreB) {
            g_AiLogic.unused_highUrgencySituationTracker = 3;
            goto finish;
        }
        if (scoreA == scoreB) {
            g_AiLogic.unused_highUrgencySituationTracker = 2;
            goto finish;
        }
    }
    if (g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total + 5 <
        g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total) {
        g_AiLogic.unused_highUrgencySituationTracker = 0;
    }
finish:
    pitcherAINewBatter();
    batterAIRNGValueSetting();

    if (g_d_GameSettings.minigamesEnabled) {
        for (i = 0; i < 4; i++) {
            u8* fl = (u8*)&g_FieldingLogic + i * 6;
            fl[0x78] = 0;
            fl[0x77] = 0;
            if (RandomInt_Game(100) <
                aiDashProbabilities[g_Fielders[(s8)g_Minigame.minigameFielderIndex[i]].AILevel3Weak0Powerful]) {
                fl[0x78] = 1;
            }
        }
    } else {
        u8* fl = (u8*)&g_FieldingLogic;
        fl[0x78] = 0;
        fl[0x77] = 0;
        if (RandomInt_Game(100) < aiDashProbabilities[g_Fielders[0].AILevel3Weak0Powerful]) {
            fl[0x78] = 1;
        }
    }
}
