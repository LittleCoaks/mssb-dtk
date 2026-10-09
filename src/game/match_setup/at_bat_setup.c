#define SQRT2_LINKAGE static
#include "game/match_setup/at_bat_setup.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/batting/batter_ai.h"
#include "game/pitching/pitcher_ai.h"
#include "game/math/game_math.h"
#include "game/match_setup/pause_menu.h"

#define BATTING_ORDER_COPY_PAIRS 10
#define LINEUP_TEAMS 2
#define LINEUP_PLAYERS 9

extern s8 lineUpInfoStruct[LINEUP_TEAMS][LINEUP_PLAYERS][4];

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

// .text:0x0001E178 size:0x1B0 mapped:0x8065D20C
void someRosterMemoryManagement(void) {
    s32 i;
    s32 team;

    resetLastPitchData();
    for (i = 0; i < BATTING_ORDER_COPY_PAIRS; i++) {
        pauseControl.battingOrderCopy[g_GameLogic.homeTeamBattingInd_fieldingTeam][i * 2] = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.homeTeamBattingInd_fieldingTeam][i][0];
        pauseControl.battingOrderCopy[g_GameLogic.homeTeamBattingInd_fieldingTeam][i * 2 + 1] = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.homeTeamBattingInd_fieldingTeam][i][1];
    }
    for (team = 0; team < LINEUP_TEAMS; team++) {
        for (i = 0; i < LINEUP_PLAYERS; i++) {
            pauseControl.lineupCopy[team][i] = lineUpInfoStruct[team][i][3];
        }
    }
}

// .text:0x0001E154 size:0x24 mapped:0x8065D1E8
void betweenABSetPitcherBatter(void) {
    resetPitcherPreAB();
    resetBatterPreAB();
}
