#define SQRT2_LINKAGE static
#include "game/match_setup/pause_menu.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/animation/scene_effects.h"
#include "game/baserunning/runner.h"
#include "game/fielding/fielder.h"
#include "game/match_setup/match_flow.h"
#include "game/pitching/pitcher.h"
#include "game/character_stats.h"
#include "game/camera/camera.h"
#include "Unknown/File_0x8001c588.h"
#include "Unknown/File_0x800203e0.h"
#include "Unknown/File_0x8004cc18.h"
#include "Unknown/File_0x80035838.h"
#include "game/batting/batter.h"
#include "musyx/musyx.h"
#include "Unknown/File_0x800204cc.h"
#define REP_HEADER_DATA_FN getRepHeaderData_pauseMenu
#include "header_rep_data.h"

extern u8 hugeAnimStruct[0x3154];
extern u8 animRelated[0x124];
extern u8 highLevelSimulationFlag[4];
extern u8 lineUpInfoStruct[2][9][4];
extern u8 CommonUIFiles_pauseMenu[0x3E0];
extern u8 lbl_800EFBA4[];
extern u8 lbl_3_data_F918[];
extern u8 lbl_3_data_6104[];
extern u8 lbl_8037169C[];
void fn_3_AE900(void);
void fn_3_ADEDC(void);
void fn_3_5B408(void);
void initFielders(void);
void setPitcherStatsToInMemPitcher(int arg0);
void fn_3_AE334(void);
void fn_3_ADA3C(void);
void fn_80035B50(int arg0);
extern CharacterStats inMemRoster[TEAMS_PER_GAME][PLAYERS_PER_TEAM];
extern void QueueTextToDisplay(int code, int arg1);
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);

void loadPauseMenu(void);
void fn_3_AE334(void);
void fn_3_ADA3C(void);
void positionSwap(void);
void controlOptionsMenu(void);
void positionSwapScreenInputs(void);
BOOL championshipScreenGraphics(void);
void fn_3_AEC50(void);

// Applies each human team's auto-run and auto-fielding options to the game logic.
static void pauseMenu_applyTeamControlOptions(void) {
    int i;

    for (i = 0; i < 2; i++) {
        if (g_GameLogic.teamIsCPU[i] == FALSE) {
            if (inningSetting.controlOptions[g_GameLogic.teams[i]].autoRunning != FALSE) {
                g_GameLogic.battingAIInd[g_GameLogic.homeTeamInd ^ i] = TRUE;
            } else {
                g_GameLogic.battingAIInd[g_GameLogic.homeTeamInd ^ i] = FALSE;
            }
            if (inningSetting.controlOptions[g_GameLogic.teams[i]].autoFielding != FALSE) {
                g_GameLogic.teamAIInd[g_GameLogic.homeTeamInd ^ i] = TRUE;
                g_GameLogic.autoFielding[g_GameLogic.homeTeamInd ^ i] = TRUE;
            } else {
                g_GameLogic.teamAIInd[g_GameLogic.homeTeamInd ^ i] = FALSE;
                g_GameLogic.autoFielding[g_GameLogic.homeTeamInd ^ i] = FALSE;
            }
        }
    }
}

// Pairs the next pitcher and fielder lineup entries with their actor loads.
static inline void pauseMenu_loadLineupActors(void) {
    s16 cur;
    s16 next;

    cur = pauseControl._254[0];
    if (cur >= 0) {
        if (pauseControl._254[4] == cur) {
            pauseControl._254[0] = -1;
        } else if (pauseControl._254[2] < 0) {
            pauseControl._254[2] = cur;
            g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0] =
                (s8)lineUpInfoStruct[pauseControl.port][cur][0];
            animRelated[0x9C] = 0;
            loadPitcherActor();
        } else if (loadPitcherActor()) {
            pauseControl._254[0] = -1;
            pauseControl._254[4] = pauseControl._254[2];
            pauseControl._254[2] = -1;
        }
    } else {
        next = pauseControl._254[1];
        if (next >= 0) {
            if (pauseControl._254[5] == pauseControl._254[3]) {
                pauseControl._254[1] = -1;
                pauseControl._254[3] = -1;
            } else if (pauseControl._254[3] < 0) {
                highLevelSimulationFlag[3] = FALSE;
                pauseControl._254[3] = next;
            } else if (loadFielderActors(inMemRoster[pauseControl.port][lineUpInfoStruct[pauseControl.port][next][0]].stats.CharID)) {
                pauseControl._254[1] = -1;
                pauseControl._254[5] = pauseControl._254[3];
                pauseControl._254[3] = -1;
            }
        }
    }
}

static void pauseMenu_incSaturating(u8 *v) {
    if (*v < 0xFE) {
        *v = *v + 1;
    } else {
        *v = 0xFF;
    }
}

static void pauseMenu_scanLineup(void) {
    int i;

    pauseControl._254[0] = -1;
    pauseControl._254[2] = -1;
    pauseControl._254[1] = -1;
    pauseControl._254[3] = -1;
    for (i = 0; i < 9; i += 3) {
        if (lineUpInfoStruct[pauseControl.port][i][2] == 0) {
            pauseControl._254[4] = i;
        }
        if (lineUpInfoStruct[pauseControl.port][i][2] == 1) {
            pauseControl._254[5] = i;
        }
        if (lineUpInfoStruct[pauseControl.port][i + 1][2] == 0) {
            pauseControl._254[4] = i + 1;
        }
        if (lineUpInfoStruct[pauseControl.port][i + 1][2] == 1) {
            pauseControl._254[5] = i + 1;
        }
        if (lineUpInfoStruct[pauseControl.port][i + 2][2] == 0) {
            pauseControl._254[4] = i + 2;
        }
        if (lineUpInfoStruct[pauseControl.port][i + 2][2] == 1) {
            pauseControl._254[5] = i + 2;
        }
    }
}

// Returns the pause screen to its entry state with the frame counters cleared.
static void pauseMenu_enterScreen(int screen) {
    pauseControl._1D1 = screen;
    pauseControl._1D2 = 0;
    pauseControl.counter = 0;
    pauseControl._00E = 0;
    pauseControl._010 = 0;
}

// Plays the pause menu's sound effect `sfx` with the table's per-entry volume byte.
static void pauseMenu_playSound(int sfx, int tableIndex) {
    sndFXStartEx(sfx, lbl_800EFBA4[tableIndex], 0x3F, 0);
}

// Copies byte 2 of the first nine lineup slots for `port` into pauseControl._242.
static void pauseMenu_copyLineupFlags(int port) {
    int i;
    int j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            pauseControl._242[i * 3 + j] = (s8)lineUpInfoStruct[port][i * 3 + j][2];
        }
    }
}

// Sets the pause menu's analog-stick style movement flags from the screen's table row.
static void pauseMenu_setStickMode(int value) {
    pauseControl._004[0] = value;
    pauseControl._004[1] = value;
    pauseControl._004[2] = value;
    pauseControl._206 = 0xD;
}

// Writes each lineup slot's value from pauseControl._242 into the batting order of the batting team.
static void pauseMenu_syncBattingOrder(void) {
    int i;
    int j;
    int team;
    int pitcherId;

    team = g_GameLogic.awayTeamBattingInd_battingTeam;
    pitcherId = g_GameLogic.battingOrderAndPositionMapping[team][0][0];
    for (i = 0; i < 9; i++) {
        for (j = 1; j < 10; j++) {
            if (g_GameLogic.battingOrderAndPositionMapping[team][j][0] == i) {
                if (g_GameLogic.battingOrderAndPositionMapping[team][j][1] != pauseControl._242[i]) {
                    pauseControl._260 = TRUE;
                    g_GameLogic.battingOrderAndPositionMapping[team][j][1] = pauseControl._242[i];
                    if (pauseControl._242[i] == 0) {
                        g_GameLogic.battingOrderAndPositionMapping[team][j][0] = i;
                    }
                    if (pitcherId != g_GameLogic.battingOrderAndPositionMapping[team][j][0]) {
                        g_GameLogic.playOverInd = TRUE;
                    }
                }
            }
        }
    }
}

void setPausedTo0AndOtherStateVars(void) {
    pauseControl._1D5 = 0;
    pauseControl._1D6 = 0;
    pauseControl._1D7 = 0;
}

void fn_3_AFD80(int arg0) {
    pauseControl._1D1 = arg0;
    pauseControl._1D2 = 0;
    pauseControl.counter = 0;
    pauseControl._00E = 0;
    pauseControl._010 = 0;
}

BOOL fn_3_AFD48(int arg0) {
    if (pauseControl._206 <= 0) {
        pauseControl._004[0] = arg0;
        pauseControl._004[1] = arg0;
        pauseControl._004[2] = arg0;
        pauseControl._206 = 0xD;
        return TRUE;
    }
    return FALSE;
}

void match_checkForPause(void) {
    int home;
    int away;

    if (hugeAnimStruct[0x2D46] != FALSE) {
        return;
    }
    if (hugeAnimStruct[0x2D52] != FALSE) {
        return;
    }
    if (hugeAnimStruct[0x2D5E] != FALSE) {
        return;
    }
    if (g_d_GameSettings.exhibitionMatchInd == FALSE && animRelated[0xB3] != FALSE) {
        return;
    }
    if (g_Pitcher.pitchTotalTimeCounter > 0) {
        return;
    }
    if (pauseControl._1D5 != FALSE) {
        return;
    }
    if (g_Pitcher.pitcherActionState == 2) {
        return;
    }

    home = g_GameLogic.teamFielding;
    pauseControl._201 = FALSE;
    if (pauseControl._202[home] != FALSE) {
        pauseControl._1D8 = 0;
        pauseControl._202[home] = FALSE;
        pauseControl._204[home] = FALSE;
    } else {
        away = g_GameLogic.teamBatting;
        if (pauseControl._202[away] != FALSE) {
            pauseControl._1D8 = 1;
            pauseControl._202[away] = FALSE;
            pauseControl._204[away] = FALSE;
        } else if (g_GameLogic.teamIsCPU[home] == FALSE &&
                   (g_Controls[g_GameLogic.teams[home]].newButtonInput & INPUT_BUTTON_START)) {
            pauseControl._1D8 = 0;
        } else {
            if (g_GameLogic.teamIsCPU[away] != FALSE) {
                return;
            }
            if (!(g_Controls[g_GameLogic.teams[away]].newButtonInput & INPUT_BUTTON_START)) {
                return;
            }
            pauseControl._1D8 = 1;
        }
    }

    pauseControl._1D5 = TRUE;
    pauseControl._1D1 = 0;
    pauseControl._1D2 = 0;
    pauseControl.counter = 0;
    pauseControl._00E = 0;
    pauseControl._010 = 0;
    QueueTextToDisplay(0xE, 0);
    sound_crowd_EffectsStruct._2A = TRUE;
    sound_crowd_EffectsStruct._24 = 0x3B;
}

void transitionToPauseScreen(void) {
    if (pauseControl.counter < 0x7FFE) {
        pauseControl.counter = pauseControl.counter + 1;
    } else {
        pauseControl.counter = 0x7FFF;
    }

    highLevelSimulationFlag[0] = TRUE;
    if (pauseControl.counter > 0x3C) {
        if (pauseControl._1D8 == FALSE) {
            if (g_d_GameSettings.exhibitionMatchInd == FALSE) {
                pauseControl._1D0 = 2;
            } else {
                pauseControl._1D0 = 0;
            }
        } else {
            if (g_d_GameSettings.exhibitionMatchInd == FALSE) {
                pauseControl._1D0 = 3;
            } else {
                pauseControl._1D0 = 1;
            }
        }
        pauseControl._1D1 = 1;
        pauseControl._1D2 = 0;
        pauseControl.counter = 0;
        pauseControl._00E = 0;
        pauseControl._010 = 0;
        SetGameStatus(GAME_STATUS_PAUSED);
        pauseAnimations();
        pauseStateOnStadiums();
    } else {
        atBat_Fielders();
        running_MainFunction();
    }
}

void fn_3_AF5A4(void) {
    int i;
    int port;
    int team;
    int other;

    if (pauseControl.counter < 0x7FFE) {
        pauseControl.counter = pauseControl.counter + 1;
    } else {
        pauseControl.counter = 0x7FFF;
    }
    if (pauseControl._12 < 0x7FFE) {
        pauseControl._12 = pauseControl._12 + 1;
    } else {
        pauseControl._12 = 0x7FFF;
    }

    highLevelSimulationFlag[0] = TRUE;
    if (pauseControl._201 != FALSE) {
        pauseControl._004[0] = 0;
        pauseControl._004[1] = 0;
        pauseControl._004[2] = 0;
        pauseControl._206 = pauseControl._206 - 1;
        if (pauseControl._206 < 0) {
            pauseControl._206 = 0xC;
        }
    } else {
        pauseControl._004[0] = g_Controls[g_GameLogic.teams[pauseControl.port]].buttonInput;
        pauseControl._004[1] = g_Controls[g_GameLogic.teams[pauseControl.port]].newButtonInput;
        pauseControl._004[2] = g_Controls[g_GameLogic.teams[pauseControl.port]]._08;
    }

    switch (pauseControl._1D1) {
    case 1:
        loadPauseMenu();
        break;
    case 2:
        fn_3_AE334();
        break;
    case 3:
        fn_3_ADA3C();
        break;
    case 4:
    case 7:
    case 8:
        positionSwap();
        break;
    case 5:
        switch (pauseControl._1D2) {
        case 0:
            pauseControl._23F[pauseControl.port] = 0;
            other = pauseControl.port ^ 1;
            if (g_GameLogic.teamIsCPU[other] == FALSE) {
                pauseControl._23F[other] = 1;
            } else {
                pauseControl._23F[other] = 0xFF;
            }
            pauseControl._1D2 = 1;
            break;
        case 1:
            pauseControl._12 = 0;
            pauseControl._1D2 = 2;
            break;
        case 2:
            if (pauseControl._12 > 0x14) {
                pauseControl._1D2 = 3;
            }
            break;
        case 3:
            controlOptionsMenu();
            break;
        case 4:
            pauseControl._12 = 0;
            pauseControl._1D2 = 5;
            break;
        case 5:
            if (pauseControl._12 > 0x14) {
                pauseControl._1D2 = 6;
            }
            break;
        case 6:
            pauseControl._1D1 = 2;
            pauseControl._1D2 = 0;
            pauseControl.counter = 0;
            pauseControl._00E = 0;
            pauseControl._010 = 0;
            break;
        }
        break;
    case 6:
        howToPlayScreen();
        break;
    case 9:
        fn_3_AEC50();
        break;
    case 10:
        if (pauseControl.counter <= 1) {
            highLevelSimulationFlag[2] = FALSE;
            fn_80035B50(0x13);
        }
        resetPitcherValuesBetweenBatters(TRUE);
        setBatterContactConstants();
        pauseMenu_applyTeamControlOptions();
        fn_3_FBD70();
        fn_3_FBD58();
        hugeAnimStruct[0x307E] = TRUE;
        g_GameLogic.pre_PostMiniGameInd = TRUE;
        changeScene(1, 6);
        SetGameStatus(0);
        break;
    case 11:
    case 14:
    case 15:
        positionSwap();
        break;
    case 12:
        switch (pauseControl._1D2) {
        case 0:
            pauseControl._23F[pauseControl.port] = 0;
            other = pauseControl.port ^ 1;
            if (g_GameLogic.teamIsCPU[other] == FALSE) {
                pauseControl._23F[other] = 1;
            } else {
                pauseControl._23F[other] = 0xFF;
            }
            pauseControl._1D2 = 1;
            break;
        case 1:
            pauseControl._12 = 0;
            pauseControl._1D2 = 2;
            break;
        case 2:
            if (pauseControl._12 > 0x14) {
                pauseControl._1D2 = 3;
            }
            break;
        case 3:
            controlOptionsMenu();
            break;
        case 4:
            pauseControl._12 = 0;
            pauseControl._1D2 = 5;
            break;
        case 5:
            if (pauseControl._12 > 0x14) {
                pauseControl._1D2 = 6;
            }
            break;
        case 6:
            pauseControl._1D1 = 9;
            pauseControl._1D2 = 0;
            pauseControl.counter = 0;
            pauseControl._00E = 0;
            pauseControl._010 = 0;
            break;
        }
        break;
    case 13:
        howToPlayScreen();
        break;
    }
}

void fn_3_AF428(void) {
    pauseMenu_loadLineupActors();
}

void loadPauseMenu(void) {
    int port;

    if (pauseControl.counter <= 1) {
        if (pauseControl._1D8 == FALSE) {
            port = g_GameLogic.teamFielding;
            pauseControl.port = port;
            pauseMenu_incSaturating(&g_GameLogic._131[port]);
            pauseMenu_incSaturating(&g_GameLogic._131[port + 2]);
        } else {
            port = g_GameLogic.teamBatting;
            pauseControl.port = port;
            pauseMenu_incSaturating(&g_GameLogic._131[port]);
            pauseMenu_incSaturating(&g_GameLogic._131[port + 2]);
        }

        pauseMenu_scanLineup();

        pauseControl._1DA = 0;
        pauseControl._206 = 0xD;
        if (g_GameLogic.teamIsCPU[pauseControl.port] != FALSE) {
            pauseControl._201 = TRUE;
        } else {
            pauseControl._201 = FALSE;
        }
        pauseControl._207 = 0;
        pauseControl._208 = 0;

        pauseControl._1DB = 0;
        pauseControl._1DC = 0;
        if (g_GameLogic.playBatterWalkupAnimation != FALSE) {
            g_GameLogic.playBatterWalkupAnimation = 2;
        }
        pauseMenuCameraAngle();
    } else {
        if (diskReadRelated(CommonUIFiles_pauseMenu + 0x20, 0x13) != 0) {
            if (pauseControl._1D8 == FALSE) {
                pauseControl._1D1 = 2;
            } else {
                pauseControl._1D1 = 9;
            }
            pauseControl._1D2 = 0;
            pauseControl.counter = 0;
            pauseControl._00E = 0;
            pauseControl._010 = 0;
        }
    }
}

void fn_3_AEFF8(void) {
    pauseMenu_scanLineup();
}

void fn_3_AEC50(void) {
    int flag;
    int result;

    flag = FALSE;
    if (g_d_GameSettings.exhibitionMatchInd == FALSE) {
        flag = TRUE;
    }
    switch (pauseControl._1D2) {
    case 0:
        pauseControl._12 = 0;
        pauseControl._1D2 = 1;
        if (sound_crowd_EffectsStruct._2A != FALSE) {
            sound_crowd_EffectsStruct._2A = 2;
            sound_crowd_EffectsStruct._24 = 0x78;
        }
        break;
    case 1:
        if (pauseControl._12 > 0x14) {
            pauseControl._1D2 = 2;
        }
        break;
    case 2:
        fn_3_AE900();
        pauseControl._12 = 0;
        break;
    case 3:
        if (pauseControl._12 == 1) {
            changeScene(3, 6);
            sound_crowd_EffectsStruct._2A = 1;
            sound_crowd_EffectsStruct._24 = 5;
        }
        if (lbl_8037169C[0x13] != FALSE) {
            pauseControl._1D2 = 4;
        }
        break;
    case 4:
        if (lbl_3_data_F918[(flag << 4) + pauseControl._1DA + 9] == 0) {
            pauseMenu_enterScreen(0xA);
        }
        pauseControl._1D9 = 2;
        break;
    case 5:
        if (pauseControl._12 > 0x14) {
            pauseControl._1D2 = 6;
        }
        break;
    case 6:
        result = lbl_3_data_F918[(flag << 4) + pauseControl._1DA + 9];
        switch (result) {
        case 1:
            pauseMenu_enterScreen(0xE);
            break;
        case 2:
            pauseMenu_enterScreen(0xF);
            break;
        case 3:
            pauseMenu_enterScreen(0xB);
            break;
        case 4:
            pauseMenu_enterScreen(0xC);
            break;
        case 5:
            pauseControl._220 = 0;
            pauseMenu_enterScreen(0xD);
            break;
        }
        break;
    case 7:
        result = ((int (*)(u16))exitMenu_main)((u16)pauseControl._004[1]);
        if (result == 2) {
            pauseControl._1D2 = 2;
        } else if (result == 1) {
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            pauseControl._1D2 = 8;
        }
        break;
    case 8:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x2D) {
            if (g_d_GameSettings.exhibitionMatchInd == FALSE) {
                if (g_d_GameSettings.bJMatchInd == 1) {
                    challenge_setTransitionScreenCharacterPortrait(0xC, lbl_3_data_6104[((u8 *)starMissionCompletionTracker)[0x441C]]);
                } else {
                    challenge_setTransitionScreenCharacterPortrait(0xC, lbl_3_data_6104[((u8 *)starMissionCompletionTracker)[0x441E]]);
                }
            } else {
                changeScene(4, 6);
            }
        }
        if (lbl_8037169C[0x13] != FALSE) {
            g_GameLogic.framesOfExitingToMenu = TRUE;
            pauseControl._1D9 = 2;
            g_d_GameSettings._13 = TRUE;
            fn_80035B50(0x13);
            fn_8004CC18();
        }
        break;
    }
}

void fn_3_AE900(void) {
    int flag;
    int i;
    int row;

    flag = FALSE;
    if (g_d_GameSettings.exhibitionMatchInd == FALSE) {
        flag = TRUE;
    }
    if (pauseControl._004[1] & INPUT_BUTTON_START) {
        for (i = 0; i < 6; i++) {
            if (lbl_3_data_F918[(flag << 4) + i + 9] != 0) {
                pauseControl._1DA = i;
                break;
            }
        }
        pauseControl._1D2 = 3;
        pauseMenu_playSound(0x1B8, 1);
        return;
    }

    if (pauseControl._004[1] & INPUT_BUTTON_A) {
        row = lbl_3_data_F918[(flag << 4) + pauseControl._1DA + 9];
        switch (row) {
        case 1:
        case 2:
        case 3:
            pauseControl._1D9 = 1;
            pauseControl._12 = 0;
            pauseControl._1D2 = 5;
            break;
        case 4:
        case 5:
            pauseControl._1D9 = 1;
            pauseControl._1D2 = 5;
            break;
        case 6:
            fn_3_5B408();
            pauseControl._1D2 = 7;
            pauseMenu_playSound(0x1B8, 1);
            break;
        default:
            pauseControl._1D2 = 3;
            pauseMenu_playSound(0x1B8, 1);
            break;
        }
        return;
    }

    if (pauseControl._004[1] & INPUT_BUTTON_B) {
        if (lbl_3_data_F918[(flag << 4) + pauseControl._1DA + 9] != 0) {
            for (i = 0; i < 6; i++) {
                if (lbl_3_data_F918[(flag << 4) + i + 9] != 0) {
                    pauseControl._1DA = i;
                    break;
                }
            }
        }
        pauseControl._1D2 = 3;
        pauseMenu_playSound(0x1B9, 2);
        return;
    }

    if (pauseControl._004[2] & INPUT_BUTTON_UP) {
        if (pauseControl._1DA == 0) {
            pauseControl._1DA = lbl_3_data_F918[(flag << 4) + 8] - 1;
        } else {
            pauseControl._1DA = pauseControl._1DA - 1;
        }
        pauseMenu_playSound(0x1B7, 0);
        return;
    }

    if (pauseControl._004[2] & INPUT_BUTTON_DOWN) {
        pauseControl._1DA = pauseControl._1DA + 1;
        if (pauseControl._1DA >= lbl_3_data_F918[(flag << 4) + 8]) {
            pauseControl._1DA = 0;
        }
        pauseMenu_playSound(0x1B7, 0);
    }
}

void fn_3_AE770(void) {
    if (pauseControl.counter <= 1) {
        highLevelSimulationFlag[2] = FALSE;
        fn_80035B50(0x13);
        resetPitcherValuesBetweenBatters(TRUE);
        setBatterContactConstants();
        pauseMenu_applyTeamControlOptions();
        fn_3_FBD70();
        fn_3_FBD58();
        hugeAnimStruct[0x307E] = TRUE;
        g_GameLogic.pre_PostMiniGameInd = TRUE;
        changeScene(1, 6);
        SetGameStatus(0);
    }
}

void fn_3_AE334(void) {
    int flag;
    int result;

    flag = FALSE;
    if (g_d_GameSettings.exhibitionMatchInd == FALSE) {
        flag = TRUE;
    }
    switch (pauseControl._1D2) {
    case 0:
        pauseMenu_copyLineupFlags(pauseControl.port);
        pauseControl._1D2 = 1;
        pauseControl._12 = 0;
        pauseControl._260 = FALSE;
        if (sound_crowd_EffectsStruct._2A != FALSE) {
            sound_crowd_EffectsStruct._2A = 2;
            sound_crowd_EffectsStruct._24 = 0x78;
        }
        break;
    case 1:
        if (pauseControl._12 > 0x14) {
            pauseControl._1D2 = 2;
        }
        break;
    case 2:
        fn_3_ADEDC();
        pauseControl._12 = 0;
        break;
    case 3:
        if (pauseControl._12 == 1) {
            changeScene(3, 6);
            sound_crowd_EffectsStruct._2A = 1;
            sound_crowd_EffectsStruct._24 = 5;
        }
        if (lbl_8037169C[0x13] != FALSE) {
            pauseControl._1D2 = 4;
        }
        break;
    case 4:
        if (lbl_3_data_F918[(flag << 4) + pauseControl._1DA + 1] == 0) {
            pauseMenu_enterScreen(3);
        }
        pauseControl._1D9 = 2;
        break;
    case 5:
        if (pauseControl._12 > 0x14) {
            pauseControl._1D2 = 6;
        }
        break;
    case 6:
        result = lbl_3_data_F918[(flag << 4) + pauseControl._1DA + 1];
        switch (result) {
        case 1:
            pauseMenu_enterScreen(7);
            break;
        case 2:
            pauseMenu_enterScreen(8);
            break;
        case 3:
            pauseMenu_enterScreen(4);
            break;
        case 4:
            pauseMenu_enterScreen(5);
            break;
        case 5:
            pauseControl._220 = TRUE;
            pauseMenu_enterScreen(6);
            break;
        }
        break;
    case 7:
        result = ((int (*)(u16))exitMenu_main)((u16)pauseControl._004[1]);
        if (result == 2) {
            pauseControl._1D2 = 2;
        } else if (result == 1) {
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            pauseControl._1D2 = 8;
        }
        break;
    case 8:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x2D) {
            if (g_d_GameSettings.exhibitionMatchInd == FALSE) {
                if (g_d_GameSettings.bJMatchInd == 1) {
                    challenge_setTransitionScreenCharacterPortrait(0xC, lbl_3_data_6104[((u8 *)starMissionCompletionTracker)[0x441C]]);
                } else {
                    challenge_setTransitionScreenCharacterPortrait(0xC, lbl_3_data_6104[((u8 *)starMissionCompletionTracker)[0x441E]]);
                }
            } else {
                changeScene(4, 6);
            }
        }
        if (lbl_8037169C[0x13] != FALSE) {
            g_GameLogic.framesOfExitingToMenu = TRUE;
            pauseControl._1D9 = 2;
            g_d_GameSettings._13 = TRUE;
            fn_80035B50(0x13);
            fn_8004CC18();
        }
        break;
    }
}

void fn_3_ADEDC(void) {
    int flag;
    int i;
    int row;

    flag = FALSE;
    if (g_d_GameSettings.exhibitionMatchInd == FALSE) {
        flag = TRUE;
    }
    if (pauseControl._201 != FALSE) {
        if (pauseControl._204[g_GameLogic.teamFielding] != FALSE) {
            if (lbl_3_data_F918[(flag << 4) + pauseControl._1DA + 1] == 0) {
                if (pauseControl._206 <= 0) {
                    pauseMenu_setStickMode(0x100);
                }
            } else {
                if (pauseControl._206 <= 0) {
                    pauseMenu_setStickMode(0x8);
                }
            }
        } else {
            if (lbl_3_data_F918[(flag << 4) + pauseControl._1DA + 1] == 3) {
                if (pauseControl._206 <= 0) {
                    pauseMenu_setStickMode(0x100);
                }
            } else {
                if (pauseControl._206 <= 0) {
                    pauseMenu_setStickMode(0x4);
                }
            }
        }
    }

    if (pauseControl._004[1] & INPUT_BUTTON_START) {
        for (i = 0; i < 6; i++) {
            if (lbl_3_data_F918[(flag << 4) + i + 1] != 0) {
                pauseControl._1DA = i;
                break;
            }
        }
        pauseControl._1D2 = 3;
        pauseMenu_playSound(0x1B8, 1);
        return;
    }

    if (pauseControl._004[1] & INPUT_BUTTON_A) {
        row = lbl_3_data_F918[(flag << 4) + pauseControl._1DA + 1];
        switch (row) {
        case 1:
        case 2:
        case 3:
        case 4:
            pauseControl._1D9 = 1;
            pauseControl._12 = 0;
            pauseControl._1D2 = 5;
            break;
        case 6:
            fn_3_5B408();
            pauseControl._1D2 = 7;
            pauseMenu_playSound(0x1B8, 1);
            break;
        default:
            pauseControl._1D2 = 3;
            pauseMenu_playSound(0x1B8, 1);
            break;
        }
        return;
    }

    if (pauseControl._004[1] & INPUT_BUTTON_B) {
        if (lbl_3_data_F918[(flag << 4) + pauseControl._1DA + 1] != 0) {
            for (i = 0; i < 6; i++) {
                if (lbl_3_data_F918[(flag << 4) + i + 1] != 0) {
                    pauseControl._1DA = i;
                    break;
                }
            }
        }
        pauseControl._1D2 = 3;
        pauseMenu_playSound(0x1B9, 2);
        return;
    }

    if (pauseControl._004[2] & INPUT_BUTTON_UP) {
        if (pauseControl._1DA == 0) {
            pauseControl._1DA = lbl_3_data_F918[(flag << 4)] - 1;
        } else {
            pauseControl._1DA = pauseControl._1DA - 1;
        }
        pauseMenu_playSound(0x1B7, 0);
        return;
    }

    if (pauseControl._004[2] & INPUT_BUTTON_DOWN) {
        pauseControl._1DA = pauseControl._1DA + 1;
        if (pauseControl._1DA >= lbl_3_data_F918[(flag << 4)]) {
            pauseControl._1DA = 0;
        }
        pauseMenu_playSound(0x1B7, 0);
    }
}

void fn_3_ADA3C(void) {
    if (pauseControl._1D2 == 0) {
        fn_80035B50(0x13);
        pauseMenu_syncBattingOrder();
        initFielders();
        setPitcherStatsToInMemPitcher(g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]);
        animRelated[0x9B] = 0;
        pauseControl._1D2 = pauseControl._1D2 + 1;
    } else if (pauseControl._1D2 == 1) {
        if (pauseControl._260 == FALSE) {
            pauseControl._1D2 = pauseControl._1D2 + 1;
        } else if (championshipScreenGraphics() != FALSE) {
            pauseControl._1D2 = pauseControl._1D2 + 1;
        }
    } else if (pauseControl._1D2 == 2) {
        pauseMenu_loadLineupActors();
        if (pauseControl._254[0] < 0 && pauseControl._254[2] < 0 && pauseControl._254[1] < 0 && pauseControl._254[3] < 0) {
            pauseControl._1D2 = pauseControl._1D2 + 1;
        }
    } else {
        resetPitcherValuesBetweenBatters(TRUE);
        setBatterContactConstants();
        fn_3_FBD70();
        fn_3_FBD58();
        hugeAnimStruct[0x307E] = TRUE;
        g_GameLogic.pre_PostMiniGameInd = TRUE;
        pauseMenu_applyTeamControlOptions();
        changeScene(1, 6);
        if (g_GameLogic.playOverInd != FALSE) {
            SetGameStatus(0x16);
        } else {
            SetGameStatus(0);
        }
    }
}

void positionSwap(void) {
    int screen;

    screen = pauseControl._1D1;
    switch (pauseControl._1D2) {
    case 0:
        aiPosSwapInputs._CFA2[pauseControl.port] = (screen != 4);
        pauseControl._12 = 0;
        if (screen == 7) {
            aiPosSwapInputs._CFA2[pauseControl.port] = 2;
        } else if (screen == 0xF) {
            pauseControl._12 = 0;
            pauseControl._1D2 = 3;
        } else if (screen == 8) {
            aiPosSwapInputs._CFA2[pauseControl.port] = 3;
            pauseControl._1D2 = 2;
        }
        break;
    case 1:
        break;
    case 2:
        if (pauseControl._12 > 0x14) {
            pauseControl._1D2 = 4;
        }
        break;
    case 3:
        positionSwapScreenInputs();
        break;
    case 4:
        pauseControl._12 = 0;
        pauseControl._1D2 = 6;
        break;
    case 5:
        if (pauseControl._12 > 0x14) {
            if (screen == 0xB || screen == 0xE) {
                break;
            }
            if (screen == 0xF) {
                pauseControl._1D1 = 9;
            } else {
                pauseControl._1D1 = 2;
            }
            pauseControl._1D2 = 0;
            pauseControl.counter = 0;
            pauseControl._00E = 0;
            pauseControl._010 = 0;
        }
        break;
    case 6:
        break;
    }
}

void positionSwapScreenInputs(void) {
    if (pauseControl._201 != FALSE) {
        switch (pauseControl._207) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            break;
        }
    }
}

void fn_3_AD2A0(void) {
    pauseMenu_syncBattingOrder();
    initFielders();
    setPitcherStatsToInMemPitcher(g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]);
}

void pauseMenuControl(void) {
    switch (pauseControl._1D2) {
    case 0:
        pauseControl._23F[pauseControl.port] = 0;
        if (g_GameLogic.teamIsCPU[pauseControl.port ^ 1] == FALSE) {
            pauseControl._23F[pauseControl.port ^ 1] = 1;
        } else {
            pauseControl._23F[pauseControl.port ^ 1] = 0xFF;
        }
        pauseControl._1D2 = 1;
        break;
    case 1:
        pauseControl._12 = 0;
        pauseControl._1D2 = 2;
        break;
    case 2:
        if (pauseControl._12 > 0x14) {
            pauseControl._1D2 = 3;
        }
        break;
    case 3:
        controlOptionsMenu();
        break;
    case 4:
        pauseControl._12 = 0;
        pauseControl._1D2 = 5;
        break;
    case 5:
        if (pauseControl._12 > 0x14) {
            pauseControl._1D2 = 6;
        }
        break;
    case 6:
        if (pauseControl._1D8 != FALSE) {
            pauseControl._1D1 = 2;
        } else {
            pauseControl._1D1 = 9;
        }
        pauseControl._1D2 = 0;
        pauseControl.counter = 0;
        pauseControl._00E = 0;
        pauseControl._010 = 0;
        break;
    }
}

// Toggles one of the per-team control options from the directional input on a side's menu row.
void controlOptionsMenu(void) {
    int i;
    int team;
    int row;

    for (i = 0; i < 2; i++) {
        if (g_GameLogic.teamIsCPU[i] == FALSE) {
            team = g_GameLogic.teams[i];
            if (g_Controls[team].newButtonInput & INPUT_BUTTON_A) {
                if (pauseControl._23F[i] == 0) {
                    pauseMenu_playSound(0x1B8, 1);
                    pauseControl._1D2 = 4;
                }
            } else if (g_Controls[team]._08 & INPUT_BUTTON_UP) {
                if (pauseControl._23F[i] == 0) {
                    pauseControl._23F[i] = 4;
                } else if (pauseControl._23F[i] == 1) {
                    if (i == pauseControl.port) {
                        pauseControl._23F[i] = 0;
                    } else {
                        pauseControl._23F[i] = 4;
                    }
                } else {
                    pauseControl._23F[i] = pauseControl._23F[i] - 1;
                }
                pauseMenu_playSound(0x1B7, 0);
            } else if (g_Controls[team]._08 & INPUT_BUTTON_DOWN) {
                if (pauseControl._23F[i] == 4) {
                    if (i == pauseControl.port) {
                        pauseControl._23F[i] = 0;
                    } else {
                        pauseControl._23F[i] = 1;
                    }
                } else {
                    pauseControl._23F[i] = pauseControl._23F[i] + 1;
                }
                pauseMenu_playSound(0x1B7, 0);
            } else if (g_Controls[team]._08 & INPUT_BUTTON_RIGHT) {
                row = pauseControl._23F[i];
                if (row != 0) {
                    switch (row) {
                    case 1:
                        if (inningSetting.controlOptions[team].easyBatting == FALSE) {
                            inningSetting.controlOptions[team].easyBatting = TRUE;
                            pauseMenu_playSound(0x1B7, 0);
                        }
                        break;
                    case 2:
                        if (inningSetting.controlOptions[team].autoFielding == FALSE) {
                            inningSetting.controlOptions[team].autoFielding = TRUE;
                            pauseMenu_playSound(0x1B7, 0);
                        }
                        break;
                    case 3:
                        if (inningSetting.controlOptions[team].autoRunning == FALSE) {
                            inningSetting.controlOptions[team].autoRunning = TRUE;
                            pauseMenu_playSound(0x1B7, 0);
                        }
                        break;
                    case 4:
                        if (inningSetting.controlOptions[team].dropSpot == 1) {
                            inningSetting.controlOptions[team].dropSpot = FALSE;
                            pauseMenu_playSound(0x1B7, 0);
                        }
                        break;
                    }
                }
            } else if (g_Controls[team]._08 & INPUT_BUTTON_LEFT) {
                row = pauseControl._23F[i];
                if (row != 0) {
                    switch (row) {
                    case 1:
                        if (inningSetting.controlOptions[team].easyBatting != FALSE) {
                            inningSetting.controlOptions[team].easyBatting = FALSE;
                            pauseMenu_playSound(0x1B7, 0);
                        }
                        break;
                    case 2:
                        if (inningSetting.controlOptions[team].autoFielding != FALSE) {
                            inningSetting.controlOptions[team].autoFielding = FALSE;
                            pauseMenu_playSound(0x1B7, 0);
                        }
                        break;
                    case 3:
                        if (inningSetting.controlOptions[team].autoRunning != FALSE) {
                            inningSetting.controlOptions[team].autoRunning = FALSE;
                            pauseMenu_playSound(0x1B7, 0);
                        }
                        break;
                    case 4:
                        if (inningSetting.controlOptions[team].dropSpot == FALSE) {
                            inningSetting.controlOptions[team].dropSpot = TRUE;
                            pauseMenu_playSound(0x1B7, 0);
                        }
                        break;
                    }
                }
            }
        }
    }
}

void howToPlayScreen(void) {
    switch (pauseControl._1D2) {
    case 0:
        pauseControl._12 = 0;
        pauseControl._221 = TRUE;
        pauseControl._222 = 3;
        pauseControl._1D2 = 2;
        break;
    case 1:
        break;
    case 2:
        pauseControl._12 = 0;
        pauseControl._1D2 = 3;
        break;
    case 3:
        changeScene(1, 6);
        if (pauseControl._12 > 0x14) {
            pauseControl._1D2 = 4;
        }
        break;
    case 4:
        if (animRelated[0xC3] != FALSE) {
            break;
        }
        if (pauseControl._004[1] & INPUT_BUTTON_B) {
            pauseControl._1D2 = 5;
            pauseMenu_playSound(0x1B9, 2);
        } else if (g_d_GameSettings.GameModeSelected != 6) {
            if (pauseControl._004[2] & INPUT_BUTTON_LEFT) {
                if (pauseControl._221 != 0) {
                    pauseControl._221 = pauseControl._221 - 1;
                    pauseMenu_playSound(0x1B7, 0);
                }
            } else if (pauseControl._004[2] & INPUT_BUTTON_RIGHT) {
                if (pauseControl._221 < pauseControl._222 - 1) {
                    pauseControl._221 = pauseControl._221 + 1;
                    pauseMenu_playSound(0x1B7, 0);
                    pauseControl._12 = 0;
                }
            }
        }
        break;
    case 5:
        if (pauseControl._12 > 0x14 && animRelated[0xC3] == FALSE) {
            pauseControl._1D2 = 6;
        }
        break;
    case 6:
        if (g_d_GameSettings.GameModeSelected == 6) {
            pauseControl._1D2 = 0;
            SetGameStatus(GAME_STATUS_PAUSED);
        } else {
            if (pauseControl._1D8 == FALSE) {
                pauseControl._1D1 = 2;
            } else {
                pauseControl._1D1 = 9;
            }
            pauseControl._1D2 = 0;
            pauseControl.counter = 0;
            pauseControl._00E = 0;
            pauseControl._010 = 0;
        }
        break;
    }
}

void fn_3_AC9F8(void) {
    if (animRelated[0xC3] != FALSE) {
        return;
    }
    if (pauseControl._004[1] & INPUT_BUTTON_B) {
        pauseControl._1D2 = 5;
        pauseMenu_playSound(0x1B9, 2);
        return;
    }
    if (g_d_GameSettings.GameModeSelected == 6) {
        return;
    }
    if (pauseControl._004[2] & INPUT_BUTTON_LEFT) {
        if (pauseControl._221 != 0) {
            pauseControl._221 = pauseControl._221 - 1;
            pauseMenu_playSound(0x1B7, 0);
        }
    } else if (pauseControl._004[2] & INPUT_BUTTON_RIGHT) {
        if (pauseControl._221 < pauseControl._222 - 1) {
            pauseControl._221 = pauseControl._221 + 1;
            pauseMenu_playSound(0x1B7, 0);
        }
    }
}

void positionSwapScreenInputs(void);
void controlOptionsMenu(void);

// Pause menu data tables.
u8 lbl_3_data_F50C[44] = {
    0x00, 0x00, 0x00, 0x00, 0x02, 0x05, 0x04, 0x03, 0x08, 0x03, 0x04, 0x05, 0x02, 0x06, 0x00, 0x01,
    0x08, 0x06, 0x07, 0x01, 0x02, 0x00, 0x07, 0x04, 0x04, 0x03, 0x01, 0x02, 0x05, 0x01, 0x02, 0x04,
    0x06, 0x08, 0x07, 0x06, 0x08, 0x05, 0x03, 0x03, 0x05, 0x07, 0x04, 0x06,
};

u8 CommonUIFiles_pauseMenu[992] = {
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x13, 0x76, 0x4C, 0x1A, 0x63, 0x50, 0x00, 0x00, 0x07, 0xDB, 0x48,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x03, 0xE3, 0xDC, 0x1A, 0x6B, 0x30, 0x00, 0x00, 0x02, 0x14, 0x20,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x02, 0xEC, 0x10, 0x1A, 0x6D, 0x48, 0x00, 0x00, 0x01, 0x31, 0x08,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x0E, 0x72, 0xC0, 0x1A, 0x6E, 0x80, 0x00, 0x00, 0x06, 0x07, 0x68,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x04, 0x94, 0x04, 0x1A, 0x74, 0x88, 0x00, 0x00, 0x02, 0x0E, 0x34,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x07, 0x6A, 0xE0, 0x18, 0xED, 0x70, 0x00, 0x00, 0x03, 0x6B, 0xC8,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x10, 0xFD, 0x70, 0x1A, 0x76, 0x98, 0x00, 0x00, 0x05, 0xE2, 0x84,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x0D, 0xB7, 0x38, 0x1A, 0x7C, 0x80, 0x00, 0x00, 0x04, 0x9A, 0xB4,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x0E, 0x98, 0x64, 0x1A, 0x81, 0x20, 0x00, 0x00, 0x05, 0x9D, 0xC0,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x0B, 0x77, 0x18, 0x1A, 0x86, 0xC0, 0x00, 0x00, 0x05, 0x02, 0x88,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x0D, 0x87, 0xFC, 0x1A, 0x8B, 0xC8, 0x00, 0x00, 0x04, 0x7B, 0xC4,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x0D, 0x64, 0x3C, 0x1A, 0x90, 0x48, 0x00, 0x00, 0x04, 0xE3, 0xAC,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x0D, 0x5C, 0x7C, 0x1A, 0x95, 0x30, 0x00, 0x00, 0x04, 0x8D, 0x9C,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x0B, 0x76, 0x7C, 0x1A, 0x99, 0xC0, 0x00, 0x00, 0x04, 0x75, 0x18,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x04, 0x41, 0xF8, 0x1A, 0x9E, 0x38, 0x00, 0x00, 0x01, 0xAA, 0x84,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x10, 0x65, 0x68, 0x1A, 0x9F, 0xE8, 0x00, 0x00, 0x06, 0x8C, 0x10,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x10, 0xE5, 0xA0, 0x0E, 0x97, 0xA8, 0x00, 0x00, 0x09, 0xBC, 0xAC,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x01, 0x69, 0x80, 0x0E, 0xA1, 0x68, 0x00, 0x00, 0x00, 0xD6, 0xC4,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x01, 0x69, 0x80, 0x0E, 0xA2, 0x40, 0x00, 0x00, 0x00, 0xC9, 0x44,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x01, 0x69, 0x80, 0x0E, 0xA3, 0x10, 0x00, 0x00, 0x00, 0xE7, 0x00,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x01, 0x69, 0x80, 0x0E, 0xA3, 0xF8, 0x00, 0x00, 0x00, 0xD6, 0x4C,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x01, 0x69, 0x80, 0x0E, 0xA4, 0xD0, 0x00, 0x00, 0x00, 0xC9, 0x00,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x01, 0x69, 0x80, 0x0E, 0xA5, 0xA0, 0x00, 0x00, 0x00, 0xCF, 0xFC,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x01, 0x69, 0x80, 0x0E, 0xA6, 0x70, 0x00, 0x00, 0x00, 0xD7, 0x20,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x01, 0x69, 0x80, 0x0E, 0xA7, 0x48, 0x00, 0x00, 0x00, 0xD6, 0xCC,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x01, 0x69, 0x80, 0x0E, 0xA8, 0x20, 0x00, 0x00, 0x00, 0xD2, 0x1C,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x01, 0x69, 0x80, 0x0E, 0xA8, 0xF8, 0x00, 0x00, 0x00, 0xD0, 0xBC,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x01, 0x69, 0x80, 0x0E, 0xA9, 0xD0, 0x00, 0x00, 0x00, 0xB5, 0x44,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x01, 0x69, 0x80, 0x0E, 0xAA, 0x88, 0x00, 0x00, 0x00, 0xC4, 0xF8,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x0A, 0xDF, 0xFC, 0x18, 0xAE, 0xE8, 0x00, 0x00, 0x04, 0xBA, 0xB0,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x37, 0xCF, 0x5C, 0x18, 0xB3, 0xA8, 0x00, 0x00, 0x20, 0x8A, 0xF0,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x00, 0xA8, 0x20, 0x18, 0xED, 0x38, 0x00, 0x00, 0x00, 0x37, 0x58,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x11, 0xEC, 0x24, 0x18, 0xF0, 0xE0, 0x00, 0x00, 0x0D, 0x88, 0x18,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x01, 0x93, 0xE8, 0x19, 0x1B, 0x88, 0x00, 0x00, 0x00, 0x89, 0xD8,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x06, 0xC8, 0x50, 0x06, 0xC9, 0x60, 0x00, 0x00, 0x02, 0xC8, 0x84,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x05, 0xB1, 0x78, 0x06, 0xCC, 0x30, 0x00, 0x00, 0x03, 0x55, 0x5C,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x1E, 0xB1, 0x74, 0x18, 0xD4, 0x38, 0x00, 0x00, 0x0F, 0xB2, 0x20,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x01, 0xED, 0x60, 0x1A, 0xA6, 0x78, 0x00, 0x00, 0x00, 0xCF, 0xF0,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x00, 0xBF, 0x30, 0x1A, 0xA7, 0x48, 0x00, 0x00, 0x00, 0x26, 0xE0,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x00, 0x34, 0x98, 0x1A, 0xA7, 0x70, 0x00, 0x00, 0x00, 0x0E, 0x28,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x00, 0xBD, 0xE0, 0x1A, 0xA7, 0x80, 0x00, 0x00, 0x00, 0x24, 0xF4,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x00, 0x60, 0x88, 0x1A, 0xA7, 0xA8, 0x00, 0x00, 0x00, 0x12, 0x90,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x00, 0x49, 0xF0, 0x1A, 0xA7, 0xC0, 0x00, 0x00, 0x00, 0x18, 0xF4,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x00, 0x5E, 0xCC, 0x1A, 0xA7, 0xE0, 0x00, 0x00, 0x00, 0x1D, 0x38,
    0x00, 0x00, 0x04, 0x0B, 0x40, 0x00, 0x26, 0x70, 0x1A, 0xA8, 0x00, 0x00, 0x00, 0x00, 0x0B, 0xE8,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x82, 0x40, 0x1A, 0xA8, 0x10, 0x00, 0x00, 0x02, 0x82, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x82, 0x40, 0x1A, 0xAA, 0x98, 0x00, 0x00, 0x02, 0x82, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x82, 0x40, 0x1A, 0xAD, 0x20, 0x00, 0x00, 0x02, 0x82, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x82, 0x40, 0x1A, 0xAF, 0xA8, 0x00, 0x00, 0x02, 0x82, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x82, 0x40, 0x1A, 0xB2, 0x30, 0x00, 0x00, 0x02, 0x82, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x82, 0x40, 0x1A, 0xB4, 0xB8, 0x00, 0x00, 0x02, 0x82, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x82, 0x40, 0x1A, 0xB7, 0x40, 0x00, 0x00, 0x02, 0x82, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x82, 0x40, 0x1A, 0xB9, 0xC8, 0x00, 0x00, 0x02, 0x82, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x82, 0x40, 0x1A, 0xBC, 0x50, 0x00, 0x00, 0x02, 0x82, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x82, 0x40, 0x1A, 0xBE, 0xD8, 0x00, 0x00, 0x02, 0x82, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x82, 0x40, 0x1A, 0xC1, 0x60, 0x00, 0x00, 0x02, 0x82, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x82, 0x40, 0x1A, 0xC3, 0xE8, 0x00, 0x00, 0x02, 0x82, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x82, 0x40, 0x1A, 0xC6, 0x70, 0x00, 0x00, 0x02, 0x82, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x82, 0x40, 0x1A, 0xC8, 0xF8, 0x00, 0x00, 0x02, 0x82, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x82, 0x40, 0x1A, 0xCB, 0x80, 0x00, 0x00, 0x02, 0x82, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x82, 0x40, 0x1A, 0xCE, 0x08, 0x00, 0x00, 0x02, 0x82, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x82, 0x40, 0x1A, 0xD0, 0x90, 0x00, 0x00, 0x02, 0x82, 0x40,
};

u8 lbl_3_data_F918[32] = {
    0x05, 0x00, 0x03, 0x04, 0x05, 0x06, 0x00, 0x00, 0x04, 0x00, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00,
    0x07, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x06, 0x00, 0x01, 0x02, 0x04, 0x05, 0x06, 0x00,
};
