#define SQRT2_LINKAGE static
#include "game/match_setup/at_bat_setup.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "header_rep_data.h"
#include "game/batting/batter_ai.h"
#include "game/pitching/pitcher_ai.h"
#include "game/math/game_math.h"
#include "game/match_setup/pause_menu.h"

extern s8 lineUpInfoStruct[2][9][4];

// .text:0x0001E154 size:0x24 mapped:0x8065D1E8
void betweenABSetPitcherBatter(void) {
    resetPitcherPreAB();
    resetBatterPreAB();
}

// .text:0x0001E178 size:0x1B0 mapped:0x8065D20C
void someRosterMemoryManagement(void) {
    int i;
    int team;
    int fieldingTeam;

    resetLastPitchData();
    fieldingTeam = g_GameLogic.homeTeamBattingInd_fieldingTeam;
    for (i = 0; i < 10; i++) {
        pauseControl.battingOrderCopy[fieldingTeam][i * 2] = g_GameLogic.battingOrderAndPositionMapping[fieldingTeam][i][0];
        pauseControl.battingOrderCopy[fieldingTeam][i * 2 + 1] = g_GameLogic.battingOrderAndPositionMapping[fieldingTeam][i][1];
    }
    for (team = 0; team < 2; team++) {
        for (i = 0; i < 9; i++) {
            pauseControl.lineupCopy[team][i] = lineUpInfoStruct[team][i][3];
        }
    }
}

// .text:0x0001E328 size:0xC4 mapped:0x8065D3BC
void initializeAIConstants(void) {
    g_AiLogic._46 = (int)g_GameLogic.AIDifficulty0Special3Weak[0] * 0xFF / 4;
    g_AiLogic._47 = (int)g_GameLogic.AIDifficulty0Special3Weak[1] * 0xFF / 4;
    resetBatterAIBoxPosition();
    pauseControl._202[0] = 0;
    pauseControl._202[1] = 0;
    pauseControl._21C = 0;
    pauseControl._21D = 0;
    if (g_GameLogic.teamIsCPU[g_GameLogic.homeTeamInd]) {
        g_GameLogic.runnerAIInd[0] = 1;
    }
    if (g_GameLogic.teamIsCPU[g_GameLogic.homeTeamInd ^ 1]) {
        g_GameLogic.runnerAIInd[1] = 1;
    }
    g_AiLogic.aIPitchDesiredEndingLocIndex = U8_MAX;
}
