#define SQRT2_LINKAGE static
#include "game/practice/player_control_transition.h"
#define REP_HEADER_DATA_FN getRepHeaderData_playerControlTransition
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

// .text:0x000B3A4C size:0x124 mapped:0x806F2AE0
void transitionToPlayerControl(void) {
    g_GameLogic.hudElementLoadingInd = 1;
    g_Practice.instructionNumber = -1;
    g_Practice.completionMenuActive = 0;
    g_Practice.guidedPracticeCompletionRelated = 0;
    g_Practice.guidedPracticeCounter = 0;
    g_Practice.frames_sincePracticeCompleted = 0;
    g_Practice.frames_sinceMovedToFromMenu = 0;
    g_Practice.practiceState = PRACTICE_STATE_0;
    g_Practice.tutorialState = TUTORIAL_STATE_3;
    g_Practice.framesSincePracticeMenuDefaultTransition = 0;
    g_GameLogic.teamIsCPU[0] = 0;
    g_GameLogic.pitcherAIInd[0] = 0;
    g_GameLogic.batterAIInd[0] = 0;
    g_GameLogic.teamAIInd[0] = 0;
    g_GameLogic.autoFielding[0] = 0;
    g_GameLogic.autoRunningInd[0] = 0;
    g_GameLogic.teamIsCPU[1] = 0;
    g_GameLogic.pitcherAIInd[1] = 0;
    g_GameLogic.batterAIInd[1] = 0;
    g_GameLogic.teamAIInd[1] = 0;
    g_GameLogic.autoFielding[1] = 0;
    g_GameLogic.autoRunningInd[1] = 0;
    switch (g_Practice.practiceType_2) {
    case PRACTICE_TYPE_BATTING:
        g_Practice.aIEnabled = 1;
        g_GameLogic.pitcherAIInd[1] = 1;
        g_GameLogic.pitcherAIInd[0] = 1;
        break;
    case PRACTICE_TYPE_FIELDING:
        g_Practice.aIEnabled = 1;
        g_Practice.practiceBatterHandedness = 1;
        g_GameLogic.pitcherAIInd[1] = 1;
        g_GameLogic.pitcherAIInd[0] = 1;
        g_GameLogic.batterAIInd[1] = 1;
        g_GameLogic.batterAIInd[0] = 1;
        g_GameLogic.autoRunningInd[1] = 1;
        g_GameLogic.autoRunningInd[0] = 1;
        break;
    case PRACTICE_TYPE_FREEPLAY:
        if (g_Practice.practiceLevel == 4) {
            g_Practice.aIEnabled = 1;
            g_Practice.practiceBatterHandedness = 0;
            g_Practice.aIEnabled = 1;
            g_GameLogic.pitcherAIInd[1] = 1;
            g_GameLogic.pitcherAIInd[0] = 1;
        } else if (g_Practice.practiceLevel == 5) {
            g_Practice.aIEnabled = 0;
            g_Practice.practiceBatterHandedness = 1;
        }
        break;
    }
    g_Pitcher.pitcher.x = 0.0f;
}
