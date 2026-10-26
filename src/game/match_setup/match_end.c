#define SQRT2_LINKAGE static
#include "game/match_setup/match_end.h"
#include "game/match_setup/match_main.h"
#include "game/match_setup/match_flow.h"
#include "game/challenge/scout_state.h"
#include "mem.h"
#include "Dolphin/rand.h"
#include "game/replay/replay_inputs.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/animation/animation_dispatch.h"
#include "game/animation/scene_effects.h"
#include "game/ball/ball_physics.h"
#include "game/baserunning/play_result_tracking.h"
#include "game/baserunning/runner.h"
#include "game/batting/at_bat_results.h"
#include "game/batting/batter.h"
#include "game/camera/camera.h"
#include "game/fielding/fielder.h"
#include "game/match_setup/ai_defaults.h"
#include "game/match_setup/controller_input.h"
#include "game/replay/replay_state.h"
#include "game/stats/result_stats.h"
#include "game/match_setup/roster_init.h"
#include "game/stats/stat_tracking.h"
#include "game/match_setup/transition_init.h"
#include "game/match_setup/versus_screens.h"
#include "game/math/game_math.h"
#include "game/pitching/pitcher.h"
#include "game/pitching/pitcher_stamina.h"
#include "game/sound/m_sound.h"
#include "game/stadium/stadium_framework.h"
#include "musyx/musyx.h"
#include "Unknown/File_0x8004abd8.h"
#include "challenge/challenge_progress.h"
#include "Unknown/File_0x8001e460.h"
#include "Unknown/File_0x8001f228.h"
#include "Unknown/File_0x800204cc.h"
#include "Unknown/File_0x80035838.h"
#include "Unknown/File_0x80062a50.h"
#include "Unknown/File_0x800a7568.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x800203e0.h"
#include "Unknown/File_0x80014d4c.h"
#include "Unknown/File_0x80014e50.h"
#include "Unknown/File_0x80014f40.h"
#include "game/match_setup/pause_menu.h"
#define REP_HEADER_DATA_FN getRepHeaderData_matchEnd
#include "header_rep_data.h"

extern u8 lbl_80366158[0x30];
extern u8 animRelated[0x124];
extern s16 challenge_baseCoinsAwarded[16];

extern ChallengeSituation lbl_3_data_5FF4[2][4][2];
extern s16 lbl_3_data_6074[4];
extern u8 challengeTransitionPortraitIDs[];
extern u8 lbl_8037169C[];
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern MatchEndFile CommonUIFiles_matchEnd[];
extern int exitMenu(u16 buttons);
extern void set803c5f77(void);
extern void fn_8004CC4C(int, int, int, int, int);
extern void fn_8004CA48(int, int, int, int);
extern int loadMVPMaybe(void);
extern u8 lbl_803C5F74[];
extern u8 lbl_800EFBA4[];
extern void fn_8003BF54(int, int, int, int, int, int, int, int, int);

// .text:0x0005BD40 size:0x6D8 mapped:0x8069ADD4
void matchEndGameScreenFunction(void) {
    s8 mvp;
    InputStruct* input = &g_Controls[(u8)lbl_80366158[0x27]];
    u32 stage = g_GameLogic._125;

    if (stage >= 3) {
        if (pauseControl._12 < 0x7FFE) {
            (pauseControl._12)++;
        } else {
            pauseControl._12 = 0x7FFF;
        }
    }
    switch (stage) {
    case 0:
        pauseControl.cursor = 0;
        pauseControl._1DB = 0;
        pauseControl._1D8 = 0;
        pauseControl._12 = 0;
        g_GameLogic.scoreBook_teamDisplayed = 0;
        g_GameLogic.scoreBook_batter_pitcherStatsDisplayed = 0;
        g_GameLogic.scoreBook_scrollIndex = 0;
        g_GameLogic.scoreBook_logoFadeDirectionLeft_Right = 0;
        g_GameLogic._118 = 0;
        g_GameLogic._11A = -1;
        if (!g_d_GameSettings.exhibitionMatchInd) {
            fn_3_5B41C();
        }
        g_GameLogic._125 = 1;
        break;
    case 1:
        if (diskReadRelated(&CommonUIFiles_matchEnd[1], 0xC) != 0) {
            animRelated[0x9A] = 0;
            animRelated[0xD1] = 1;
            g_GameLogic._125 = 2;
        }
        break;
    case 2:
        if (loadMVPMaybe() != 0) {
            fn_3_8C104(-1);
            g_GameLogic._125 = 3;
        }
        break;
    case 3:
        changeScene(1, 6);
        g_GameLogic.framesInGameStatus_copy = 0;
        g_GameLogic._125 = 4;
        break;
    case 4:
        if (g_GameLogic.framesInGameStatus_copy > 0xB4) {
            g_GameLogic.framesInGameStatus_copy = 0;
            if (g_GameLogic._13D != 0) {
                if (!g_d_GameSettings.exhibitionMatchInd) {
                    g_GameLogic._125 = 7;
                } else {
                    g_GameLogic._125 = 6;
                }
            } else {
                g_GameLogic._125 = 7;
            }
        }
        break;
    case 5:
        if (g_GameLogic.framesInGameStatus_copy == 1) {
            fn_8004CC4C(7, 0, 0, 0, 0x8B);
            mvp = StatsScreenScores.mvpRosterLoc[0];
            if (mvp >= 0) {
                fn_8004CA48(inMemRoster[0][mvp].stats.CharID, 0, 0, 0);
            } else {
                mvp = StatsScreenScores.mvpRosterLoc[1];
                if (mvp >= 0) {
                    fn_8004CA48(inMemRoster[0][mvp].stats.CharID, 0, 0, 0);
                }
            }
        }
        if (g_GameLogic.framesInGameStatus_copy >= 0x14 && (input->newButtonInput & INPUT_BUTTON_A)) {
            set803c5f77();
        }
        if (lbl_803C5F74[3] == 4) {
            g_GameLogic.framesInGameStatus_copy = 0;
            g_GameLogic._125 = 6;
        }
        break;
    case 6:
        if (fn_3_5B220(0) != 0) {
            g_GameLogic.framesInGameStatus_copy = 0;
            g_GameLogic._125 = 7;
        }
        break;
    case 7:
        if (g_GameLogic.framesInGameStatus_copy > 0x2D) {
            endOfGame_menuControl();
        }
        break;
    case 8:
        if (g_GameLogic.framesInGameStatus_copy > 0x2D) {
            pauseControl._1D8 ^= 1;
            pauseControl._12 = 0;
            g_GameLogic.framesInGameStatus_copy = 0;
            g_GameLogic._125 = 7;
        }
        break;
    case 9:
        if (g_GameLogic.playOverFadeOutStarted >= 0) {
            changeScene(3, 6);
        } else if (!g_d_GameSettings.exhibitionMatchInd) {
            if (g_d_GameSettings.bJMatchInd == 1) {
                challenge_setTransitionScreenCharacterPortrait(0xC, challengeTransitionPortraitIDs[g_Challenge.captain]);
            } else {
                challenge_setTransitionScreenCharacterPortrait(0xC, challengeTransitionPortraitIDs[g_Challenge.opponentCaptain]);
            }
        } else {
            changeScene(4, 6);
        }
        if (lbl_8037169C[0x13] != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
            g_GameLogic._125 = 10;
            g_GameLogic.framesInGameStatus_copy = 0;
        }
        break;
    case 10:
        if (g_GameLogic.framesInGameStatus_copy > 0xA) {
            transitionToReplay();
            g_GameLogic._125 = 11;
            animRelated[0xCD] = 1;
        }
        break;
    case 11:
        if (g_GameLogic.playOverFadeOutStarted >= 0) {
            SetGameStatus(GAME_STATUS_CHAMPIONSHIP);
        } else {
            g_GameLogic.exitingToMenu = 1;
            g_GameLogic.framesOfExitingToMenu = 1;
        }
        break;
    }
}

// .text:0x0005BA2C size:0x314 mapped:0x8069AAC0
void endOfGame_menuControl(void) {
    InputStruct* input = &g_Controls[lbl_80366158[0x27]];

    if (pauseControl._1D8 == 0) {
        if (input->newButtonInput & INPUT_BUTTON_A) {
            if (pauseControl.cursor == 0) {
                g_GameLogic._125 = 9;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            } else {
                animRelated[0xCE] = 1;
                g_GameLogic.framesInGameStatus_copy = 0;
                g_GameLogic._125 = 8;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            }
        } else if (input->newButtonInput & INPUT_BUTTON_RIGHT) {
            if (pauseControl.cursor == 0) {
                pauseControl.cursor = 1;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else if (input->newButtonInput & INPUT_BUTTON_LEFT) {
            if (pauseControl.cursor == 1) {
                pauseControl.cursor = 0;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    } else if (animRelated[0xD2] == 0) {
        if (input->newButtonInput & INPUT_BUTTON_B) {
            g_GameLogic.framesInGameStatus_copy = 0;
            g_GameLogic._125 = 8;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        } else if ((input->newButtonInput & INPUT_TRIGGER_R) || (input->newButtonInput & INPUT_TRIGGER_L)) {
            if (input->newButtonInput & INPUT_TRIGGER_L) {
                g_GameLogic.scoreBook_logoFadeDirectionLeft_Right = 0;
            } else {
                g_GameLogic.scoreBook_logoFadeDirectionLeft_Right = 1;
            }
            g_GameLogic.scoreBook_teamDisplayed ^= 1;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (input->newButtonInput & INPUT_BUTTON_RIGHT) {
            if (g_GameLogic.scoreBook_batter_pitcherStatsDisplayed == 0) {
                g_GameLogic.scoreBook_batter_pitcherStatsDisplayed = 1;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else if (input->newButtonInput & INPUT_BUTTON_LEFT) {
            if (g_GameLogic.scoreBook_batter_pitcherStatsDisplayed == 1) {
                g_GameLogic.scoreBook_batter_pitcherStatsDisplayed = 0;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else if (input->buttonInput & INPUT_BUTTON_UP) {
            if (g_GameLogic.scoreBook_scrollIndex != 0) {
                g_GameLogic.scoreBook_scrollIndex--;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else if (input->buttonInput & INPUT_BUTTON_DOWN) {
            if (g_GameLogic.scoreBook_scrollIndex < 4) {
                g_GameLogic.scoreBook_scrollIndex++;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    }
}

// .text:0x0005B5A0 size:0x48C mapped:0x8069A634
void startChallengeModeMatch(void) {
    int i;
    int j;

    g_d_GameSettings.challengeMinigame_baseCoinsEarned = 0;
    g_d_GameSettings.bJMatchRelated = 0;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE) {
        if (g_GameLogic.teamIsCPU[g_GameLogic.homeTeamInd] != 0) {
            g_GameLogic.AIDifficulty0Special3Weak[0] = lbl_3_data_6074[g_d_GameSettings.challengeDifficulty];
        } else {
            g_GameLogic.AIDifficulty0Special3Weak[1] = lbl_3_data_6074[g_d_GameSettings.challengeDifficulty];
        }
        if (g_d_GameSettings.bJMatchInd == 1) {
            int idx;
            int flags;

            g_Scores.Inning = 9;
            g_Scores.inningLimit = 9;
            g_Scores.maxNumberOfExtraInnings = 9;
            g_Scores.halfInning = 1;
            g_GameLogic.homeTeamBattingInd_fieldingTeam ^= 1;
            g_GameLogic.awayTeamBattingInd_battingTeam ^= 1;
            g_GameLogic.teamBatting ^= 1;
            g_GameLogic.teamFielding ^= 1;
            idx = rand() % 2;
            g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam] =
                lbl_3_data_5FF4[g_d_GameSettings.home_AwaySetting][g_d_GameSettings.challengeDifficulty][idx].currentBatter;
            g_BallsStrikesOuts.storedOuts = lbl_3_data_5FF4[g_d_GameSettings.home_AwaySetting][g_d_GameSettings.challengeDifficulty][idx].outs;
            g_BallsStrikesOuts.outs = lbl_3_data_5FF4[g_d_GameSettings.home_AwaySetting][g_d_GameSettings.challengeDifficulty][idx].outs;
            g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total =
                lbl_3_data_5FF4[g_d_GameSettings.home_AwaySetting][g_d_GameSettings.challengeDifficulty][idx].score;
            if (g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total < 0) {
                g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total =
                    -g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total;
                g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total = 0;
            }
            flags = lbl_3_data_5FF4[g_d_GameSettings.home_AwaySetting][g_d_GameSettings.challengeDifficulty][idx].runnerFlags;
            g_Runners[1].rosterID = -1;
            g_Runners[2].rosterID = -1;
            g_Runners[3].rosterID = -1;
            i = g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam];
            if (flags & 1) {
                i--;
                if (i < 1) {
                    i = 9;
                }
                g_Runners[1].rosterID =
                    g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.homeTeamBattingInd_fieldingTeam][i][0];
            }
            if (flags & 0x10) {
                i--;
                if (i < 1) {
                    i = 9;
                }
                g_Runners[2].rosterID =
                    g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.homeTeamBattingInd_fieldingTeam][i][0];
            }
            if (flags & 0x100) {
                i--;
                if (i < 1) {
                    i = 9;
                }
                g_Runners[3].rosterID =
                    g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.homeTeamBattingInd_fieldingTeam][i][0];
            }
            setBatterContactConstants();
            running_initRunner();
            g_d_GameSettings.home_AwaySetting ^= 1;
        } else {
            if (Static_Stats_Tables.captainSelectedID[1] == CHAR_ID_BOWSER || g_Challenge._16C2 == 0x2A) {
                g_Scores.inningLimit = challengeInnings[g_d_GameSettings.challengeDifficulty].finalBossInningLimit;
            } else {
                g_Scores.inningLimit = challengeInnings[g_d_GameSettings.challengeDifficulty].inningLimit;
            }
            g_Scores.maxNumberOfExtraInnings = g_Scores.inningLimit + 3;
        }
        g_Scores.mercyThreshold = challengeInnings[g_d_GameSettings.challengeDifficulty].mercyThreshold;
    }
    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++) {
            if (g_Challenge.characters[i].inGameMissionTracker[j].starMissionStatus != STAR_MISSION_TRACKING_COMPLETED_SAVED) {
                g_Challenge.characters[i].inGameMissionTracker[j].starMissionStatus = STAR_MISSION_TRACKING_NOT_COMPLETED;
            }
        }
    }
}

// .text:0x0005B41C size:0x184 mapped:0x8069A4B0
void fn_3_5B41C(void) {
    int result = 2;
    int diff;

    if (g_Scores.winnerCd == 2) {
        result = 1;
    } else if (g_Scores.winnerCd == g_GameLogic.homeTeamInd) {
        result = 0;
    }
    if (g_d_GameSettings.bJMatchInd == 0) {
        g_d_GameSettings.challengeMinigame_baseCoinsEarned += challenge_baseCoinsAwarded[result];
        diff = __abs(g_Scores.scores[g_GameLogic.homeTeamInd].total - g_Scores.scores[g_GameLogic.homeTeamInd ^ 1].total);
        if (result == 0) {
            g_d_GameSettings.challengeMinigame_baseCoinsEarned += diff * challenge_baseCoinsAwarded[3] / 100;
        } else if (result == 2) {
            g_d_GameSettings.challengeMinigame_baseCoinsEarned += diff * challenge_baseCoinsAwarded[4] / 100;
        }
        g_d_GameSettings.challengeMinigame_baseCoinsEarned +=
            g_GameLogic.TeamStars[0] * challenge_baseCoinsAwarded[5] / 100;
    } else {
        g_d_GameSettings.challengeMinigame_baseCoinsEarned += challenge_baseCoinsAwarded[result + 9];
        g_d_GameSettings.bJMatchRelated += challenge_baseCoinsAwarded[result + 12];
    }
}

// .text:0x0005B408 size:0x14 mapped:0x8069A49C
void fn_3_5B408(void) {
    g_GameLogic.frame_exitMenuShowing = 0;
}

// .text:0x0005B380 size:0x88 mapped:0x8069A414
int exitMenu_main(u16 buttons) {
    if (g_GameLogic.frame_exitMenuShowing < 0x7FFE) {
        g_GameLogic.frame_exitMenuShowing++;
    } else {
        g_GameLogic.frame_exitMenuShowing = 0x7FFF;
    }
    if (g_GameLogic.frame_exitMenuShowing > 0x14) {
        int result = exitMenu(buttons);
        if (result == 1) {
            return 1;
        } else if (result == 2) {
            set803c5f77();
        } else if (result == 4) {
            return 2;
        }
    }
    return 0;
}

// .text:0x0005B368 size:0x18 mapped:0x8069A3FC
void fn_3_5B368(void) {
    g_GameLogic.frames_memoryCardWriteOnMVP = 0;
    g_GameLogic.endGameStage = 0;
}

// .text:0x0005B220 size:0x148 mapped:0x8069A2B4
int fn_3_5B220(int arg0) {
    if (g_GameLogic.frames_memoryCardWriteOnMVP < 0x7FFE) {
        g_GameLogic.frames_memoryCardWriteOnMVP++;
    } else {
        g_GameLogic.frames_memoryCardWriteOnMVP = 0x7FFF;
    }
    switch (g_GameLogic.endGameStage) {
    case 0:
        if (arg0 == 1 && g_Minigame.grandPrixInd == 0 && g_Minigame.difficultyUnlockedInd == 0 && g_Minigame.grandPrixUnlockedInd == 0 &&
            g_Minigame.newRecordRank == 0) {
            return 1;
        }
        fn_8003BF54(lbl_80366158[0x27], 0, 0, 1, 0, 4, 5, 0, 0);
        g_GameLogic.endGameStage++;
        break;
    case 1:
        if (currentDrawingItem->state == 1 || (u16)(currentDrawingItem->state - 0xB) <= 1 ||
            currentDrawingItem->state == 7) {
            g_GameLogic.endGameStage++;
        }
        break;
    default:
        return 1;
    }
    return 0;
}
