#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_rep_31A0
#include "game/data_only/rep_31A0.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/character_stats.h"
#include "game/math/game_math.h"
#include "game/match_setup/match_flow.h"
#include "game/match_setup/scene_skip.h"
#include "game/match_setup/star_missions.h"
#include "game/match_setup/match_scene.h"
#include "game/batting/at_bat_results.h"
#include "game/minigame/bobomb_derby.h"
#include "game/minigame/wall_ball.h"
#include "game/minigame/barrel_batter.h"
#include "game/minigame/chain_chomp_sprint.h"
#include "game/minigame/piranha_panic.h"
#include "game/minigame/star_dash.h"
#include "game/minigame/pitching_machine.h"
#include "game/minigame/rep_3880.h"
#include "game/minigame/minigame_fielder_anim.h"
#include "game/sound/m_sound.h"
#include "game/stadium/stadium_framework.h"
#include "game/hud/stadium_draw.h"
#include "game/animation/animation_dispatch.h"
#include "game/animation/scene_effects.h"
#include "game/batting/star_hit_sprites.h"
#include "game/data_only/rep_3CE0.h"
#include "musyx/musyx.h"
#include "Dolphin/os.h"
#include "Dolphin/stl.h"
#include "stl/stdlib.h"
#include "Unknown/File_0x800204cc.h"
#include "Unknown/File_0x800203e0.h"
#include "Unknown/File_0x80035838.h"
#include "Unknown/File_0x80034220.h"
#include "Unknown/File_0x8003452c.h"
#include "Unknown/File_0x8003a538.h"
#include "Unknown/File_0x8004cc18.h"
#include "Unknown/File_0x80052f98.h"
#include "Unknown/File_0x800506e8.h"
#include "Unknown/File_0x80062a50.h"
#include "Unknown/File_0x80062a94.h"
#include "Unknown/File_0x800628d4.h"
#include "Unknown/File_0x800a70dc.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/sub.h"

extern u8 animRelated[0x124];
extern u8 hugeAnimStruct[0x3154];
extern u8 lbl_8037169C[0x1C];
extern SuperstarStatBonus stonNiceContactIncrement;
extern u8 CommonUIFiles_minigame[];
extern u8 lbl_800E854C[];
extern u8 lbl_3_data_212A4[];
extern u8 challenge_minigames_opponentCharIDs[];
extern void cssLoadingRelated_1(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
extern s32 cssCursorOnBottomControl_maybe(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void css_initValues(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void fn_8004FDA0(int);
extern void fn_80011B64(int);
extern int fn_80016710(s8 charID, int arg1);
extern u8 lbl_80366158[0x30];
extern u8 lbl_800EFBA4[0x10];
extern u8 lbl_3_data_21268[];
extern u8 lbl_3_data_21270[];
extern u8 FrameCountOfEntireGame[];
extern u8 mapping_minigame_Stadium[8];
extern u8 lbl_3_data_18944[8];
extern u8 lbl_3_data_1894C[44];
extern u8 lbl_3_data_18978[8];
extern void manageStadiumLoading(void);
extern s16 lbl_3_data_18C48[10];
extern u8 lbl_3_data_18918[8];
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern int fn_80016F7C(void);
extern int fn_3_90DD8(void);
extern s8 lbl_3_data_B060[8][3][5];
extern void fn_80035B50(int arg0);
extern void fn_3_908E8(void);
extern void fn_800189B8(void);
extern int fn_80020388(void);
extern void fn_80018B74(void);
extern void fn_80018B38(void);
extern void fn_3_909B0(void);
extern void fn_3_9081C(void);
extern int fn_3_90860(void);
extern int fn_3_90A18(void);
extern struct {
    u8 _00[0x40];
    s16 humanTeam;
} lbl_3_common_bss_37400;

extern void fn_8001CA40(int);
extern void fn_80011BE4(int);
extern int fn_3_90928(void);
extern void fn_800189E4(void);
extern void minigamePause(void);
extern void minigameSelectSwitcher(void);
extern void minigameStartSwitcher(void);
extern void minigameEndSwitcher(void);
extern void toyFieldCharSelectSwitcher(void);
extern void fn_3_10B8D0(void);
extern void fn_3_109254(void);
extern void postMinigame(void);
extern void minigames_0x26(void);
extern void minigames_0x27(void);
extern void minigames_0x28(void);
extern void fn_3_10F684(void);
extern void minigames_pickOpponentsAndLoadStats(void);

extern MinigameResultEntry lbl_803616CC[][5];
extern s16 lbl_80109410[];
extern void fn_8006C398(MiniGrandPrixScoreInput* input);
extern int fn_8006C13C(MiniGrandPrixScoreInput* input);

static inline BOOL isCurrentRoster(s8 i) {
    return i == g_Minigame.rosterID;
}

void unusedBattingSomething(void) {
    s8 i;

    i = 0;
    do {
        g_Minigame.isAIControlled[i] = FALSE;
        i++;
    } while (i < 4);

    i = 0;
    do {
        s8 slot = g_Minigame.minigameControlStruct[0].characterIndex[i];

        if (slot >= 0 && slot < 4 && isCurrentRoster(i) &&
            g_Minigame.minigameControlStruct[0].battingHandedness[i] != 0) {
            g_Minigame.isAIControlled[slot] = TRUE;
            memset(&g_Minigame._1D7C[slot], 0, sizeof(InputStruct));

            switch (g_Pitcher.pitcherActionState) {
            case PITCHER_ACTION_STATE_WINDUP:
                if (*(u8 *)&g_Minigame.minigameAICountDownTillAction == 0) {
                    bOD_BatterAI();
                    *(u8 *)&g_Minigame.minigameAICountDownTillAction = 1;
                }
                if (g_Pitcher.windupCountdownUntilBallReleased <= g_Minigame.ai_wbChargePower_bbSwingFrame) {
                    g_Minigame._1D7C[slot].buttonInput |= INPUT_BUTTON_A;
                }
                break;
            case PITCHER_ACTION_STATE_IN_AIR:
                if (g_Ball.pitchHangtimeCounter < g_Pitcher.frameWhenUnhittable - *(s16 *)&g_Minigame.ai_wbThrowType_bbVertAngle) {
                    g_Minigame._1D7C[slot].buttonInput |= INPUT_BUTTON_A;
                }
                break;
            }
        }
        i++;
    } while (i < 4);
}

void fn_3_1104A8(void) {
    s8 i;

    i = 0;
    do {
        g_Minigame.isAIControlled[i] = FALSE;
        i++;
    } while (i < 4);
}

static inline void minigamesFillRoster(void) {
    int i;

    for (i = 0; i < 4; i++) {
        g_Minigame.playerSlots.characterIndex[i] = -1;
        g_Minigame.playerSlots.aiControlledInd[i] = 0;
        g_Minigame.playerSlots._04[i] = 0xFF;
    }
    g_Minigame.miniGameNumberOfParticipants = 0;
    g_Minigame._1907 = 0;
    minigames_pickOpponentsAndLoadStats();
    for (i = 0; i < 4; i++) {
        if (g_Minigame.selectSlotState[i] >= 0) {
            g_Minigame.playerSlots.characterIndex[g_Minigame.miniGameNumberOfParticipants] = i;
            g_Minigame.playerSlots.aiControlledInd[g_Minigame.miniGameNumberOfParticipants] = g_Minigame.selectSlotState[i];
            if (g_Minigame.playerSlots.aiControlledInd[g_Minigame.miniGameNumberOfParticipants] == 0) {
                g_Minigame._1907++;
            }
            fn_3_10C450(i, g_Minigame.selectSlots[i].charID);
            g_Minigame.playerSlots._04[g_Minigame.miniGameNumberOfParticipants] = inMemRoster[0][i].stats.CharID;
            g_Minigame.miniGameNumberOfParticipants++;
        }
    }
}

static inline void minigamesRosterSetup(void) {
    switch (g_GameLogic._125) {
    case 0:
        fn_3_10F684();
        animRelated[0xD8] = 0;
        g_GameLogic._125++;
        break;
    }
    minigamesFillRoster();
    SetGameStatus(GAME_STATUS_MINIGAME_READY);
}

void minigameSimulation(void) {
    int i;

    if (g_Minigame.pauseInd != 0) {
        minigamePause();
        return;
    }

    g_GameLogic.hudElementLoadingInd = 0;
    g_GameLogic.hudLoadingRelated = 0;
    if (g_Ball.totalFramesAtPlay < 0x7FFE) {
        g_Ball.totalFramesAtPlay++;
    } else {
        g_Ball.totalFramesAtPlay = 0x7FFF;
    }

    switch (g_GameLogic.gameStatus) {
    case GAME_STATUS_0x1B:
        fn_3_10FB74();
        break;
    case GAME_STATUS_MINIGAME_SELECT:
        minigameSelectSwitcher();
        break;
    case GAME_STATUS_TOY_STADIUM_LOAD:
        toyFieldStadiumLoad();
        break;
    case GAME_STATUS_TOY_STADIUM_CHARACTER_SELECT:
        toyFieldCharSelectSwitcher();
        break;
    case GAME_STATUS_MINIGAME_READY:
        fn_3_10B8D0();
        break;
    case GAME_STATUS_GAME_START_MOVIE:
        minigameStartSwitcher();
        break;
    case GAME_STATUS_0x23:
        fn_3_10AE18();
        break;
    case GAME_STATUS_MVP_END_GAME:
        minigameEndSwitcher();
        break;
    case GAME_STATUS_0x24:
        fn_3_109254();
        break;
    case GAME_STATUS_MINIGAME_POST_MENU:
        postMinigame();
        break;
    case GAME_STATUS_0x26:
        minigames_0x26();
        break;
    case GAME_STATUS_0x28:
        minigames_0x28();
        break;
    case GAME_STATUS_0x29:
        switch (g_GameLogic._125) {
        case 0:
            g_Minigame.GameMode_MiniGame = g_Minigame.grandPrixOrder[g_Minigame.grandPrixRound++];
            changeScene(1, 6);
            g_GameLogic._125 = 1;
            break;
        case 1:
            if (*(u16*)((u8*)g_Minigame.grandPrixResults + 0x1A) != 0) {
                changeScene(3, 6);
                g_GameLogic._125 = 2;
            }
            break;
        case 2:
            if (lbl_8037169C[0x13] != 0) {
                g_GameLogic._125 = 3;
            }
            break;
        case 3:
            g_GameLogic._125 = 4;
            break;
        case 4:
            SetGameStatus(GAME_STATUS_MINIGAME_READY);
            break;
        }
        break;
    case GAME_STATUS_0x27:
        minigames_0x27();
        break;
    case GAME_STATUS_0x25:
        minigamesRosterSetup();
        break;
    default:
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY) {
            bobOmbDerbySwitcher();
        } else if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_WALLBALL) {
            wallBallSituationSwitcher();
        } else if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER) {
            barrelBatterSwitcher();
        } else if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_CHAINCHOMP_SPRINT) {
            chainChompSprintSwitcher();
        } else if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_PIRANHA_PANIC) {
            piranhaPanicSwitcher();
        } else if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_STAR_DASH) {
            starDashSwitcher();
        }
        if (g_Minigame.minigameFramesRemaining == 600) {
            callSfx(0x2FD);
        }
        break;
    }
}

void fn_3_10FBE4(void) {
    int i;

    g_GameLogic.secondaryGameMode = SECONDARY_GAME_MODE_MINI_GAME_MENU;
    insertGraphicDrawingFunction(possiblyTransitionBlackScreen, 2);
    insertGraphicDrawingFunction(drawStadium, 4);
    g_Scores.inningLimit = 5;
    g_Scores.maxNumberOfExtraInnings = 5;
    g_Minigame._19DF = GAME_STATUS_MINIGAME_SELECT;
    g_Minigame._19E1 = 0;
    g_Minigame._19E2 = 0;
    g_Minigame._19E3 = 0;
    g_Minigame._19E6 = 1;
    g_Minigame._19E7 = 1;
    g_Minigame.GameMode_MiniGame = MINI_GAME_ID_BOBOMB_DERBY;
    g_Minigame.soloMinigameDifficulty = MINIGAME_DIFFICULTY_MULTIPLAYER_CHALLENGE_EASY;
    g_Minigame._1A2C = -1;
    g_Minigame._1A0C = -1;
    g_Minigame._19A7 = 4;
    g_Minigame.pauseInd = 0;
    g_Minigame._1A3C = 0;
    g_Minigame._1A3F = 0;
    g_Minigame._190A = 0;
    g_Minigame.starDashStarHolder = -1;
    g_Minigame._1A40 = 1;
    g_Minigame.challenge_minigame_haven_tWonYetIndicator = TRUE;
    g_Minigame._19A9 = 0;
    g_Minigame._1A3D = 0;
    g_Minigame._19E0 = 0;
    g_Minigame._1A38 = 0;
    g_Minigame._1A39 = 0;
    g_Minigame._1A46[0] = 0;
    g_Minigame.battingHandedness[5] = 0;
    for (i = 0; i < 4; i++) {
        g_Minigame.selectSlotState[i] = -1;
        g_Minigame.selectSlots[i].charID = -1;
        g_Minigame.selectSlots[i]._2[0] = -1;
        g_Minigame.selectSlots[i]._2[1] = -1;
        g_Minigame.selectSlots[i]._7 = 0;
        g_Minigame.selectSlots[i]._8 = 0;
        (&g_Minigame._1A0F)[i] = -1;
        (&g_Minigame._19D2)[i] = 20;
        (&g_Minigame._1A13)[i] = 0;
        g_Minigame.playerSlots.aiStrength[i] = 0;
        g_Minigame.playerSlots._08[i] = 0;
    }
    g_Minigame.battingHandedness[4] = 0;
    animRelated[0xB9] = 0;
    if (g_d_GameSettings.exhibitionMatchInd == FALSE) {
        g_Minigame._190A = 1;
        g_Minigame.selectSlotState[g_d_GameSettings._35] = g_d_GameSettings._35;
        lbl_3_common_bss_37400.humanTeam = g_d_GameSettings._35;
        g_Minigame.GameMode_MiniGame = g_d_GameSettings._33;
        clearScoutState();
        g_Minigame._19DF = GAME_STATUS_TOY_STADIUM_CHARACTER_SELECT;
        SetGameStatus(GAME_STATUS_0x1B);
    } else {
        SetGameStatus(GAME_STATUS_0x1B);
    }
}

void fn_3_10FB74(void) {
    switch (g_GameLogic._125) {
    case 0:
        animRelated[0xD8] = 0;
        sound_crowd_EffectsStruct._2C = 0;
        g_GameLogic._125++;
        break;
    }
    hugeAnimStruct[0x307A] = 0;
    SetGameStatus(GAME_STATUS_TOY_STADIUM_LOAD);
}

void fn_3_10F91C(void) {
    minigamesRosterSetup();
}

void fn_3_10F684(void) {
    int arr[6];
    int i;
    int n;
    int j;
    int idx;
    int r;
    int k;

    g_Minigame.GameMode_MiniGame = g_d_GameSettings._33;
    g_Minigame.selectSlotState[g_d_GameSettings._35] = 0;
    n = 0;
    for (i = 0; i < 4; i++) {
        if (g_d_GameSettings._35 == i) {
            g_Minigame.selectSlots[i].charID = (s8)g_d_GameSettings._36;
            g_Minigame.selectSlots[i]._1 = 1;
        } else {
            g_Minigame.selectSlotState[i] = 1;
            n++;
            g_Minigame.playerSlots.aiStrength[i] = lbl_3_data_18978[g_d_GameSettings.challengeDifficulty];
            if (n >= lbl_3_data_18944[g_Minigame.GameMode_MiniGame]) {
                break;
            }
        }
    }

    g_Minigame.miniGameNumberOfParticipants = lbl_3_data_18944[g_Minigame.GameMode_MiniGame] + 1;
    g_Minigame._1907 = 1;
    g_Minigame.multiPlayerInd = 1;
    g_Minigame.soloMinigameDifficulty = 0;
    for (k = 0; k < 6; k++) {
        arr[k] = lbl_3_data_1894C[g_Minigame.GameMode_MiniGame * 7 + 1 + k];
    }
    idx = 0;
    for (j = 0; j < lbl_3_data_18944[g_Minigame.GameMode_MiniGame]; j++) {
        for (;;) {
            if (g_Minigame.selectSlotState[idx] == 1) {
                break;
            }
            idx++;
        }
        r = random_fn_3_9EE24(lbl_3_data_1894C[g_Minigame.GameMode_MiniGame * 7] - j);
        for (k = 0; k < 6; k++) {
            if (arr[k] == 0xFF) {
                continue;
            }
            if (r == 0) {
                g_Minigame.selectSlots[idx].charID = arr[k];
                g_Minigame.selectSlots[idx]._1 = 1;
                idx++;
                arr[k] = 0xFF;
                break;
            }
            r--;
        }
    }
}

static inline void minigameStadiumSetup(void) {
    g_Minigame._1A2C = -1;
    FrameCountOfEntireGame[0x10] = 0;
    g_d_GameSettings.StadiumID = mapping_minigame_Stadium[g_Minigame.GameMode_MiniGame];
    g_d_GameSettings.miniGameStadiumIndicator = 0;
    if (g_d_GameSettings.StadiumID == STADIUM_ID_MARIO_STADIUM || g_d_GameSettings.StadiumID == STADIUM_ID_PEACH_GARDEN
        || g_d_GameSettings.StadiumID == STADIUM_ID_BOWSERS_CASTLE || g_d_GameSettings.StadiumID == STADIUM_ID_YOHSI_PARK) {
        g_d_GameSettings.miniGameStadiumIndicator = 1;
    }
    insertGraphicDrawingFunction(manageStadiumLoading, 0);
}

void fn_3_10F5BC(void) {
    if (g_Minigame._1A2C >= 0) {
        hugeAnimStruct[0x307E] = 0;
        cleanupMinigameResources();
        fn_3_5E60();
    }
    minigameStadiumSetup();
}

BOOL fn_3_10F564(void) {
    if (g_Minigame._1A2C == -1) {
        if (FrameCountOfEntireGame[0x10] != 0) {
            g_Minigame._1A2C = mapping_minigame_Stadium[g_Minigame.GameMode_MiniGame];
            return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}

void fn_3_10F550(u8 arg0, s16 arg1) {
    g_Minigame._1A41 = arg0;
    g_Minigame.someGraphicFrameCountdown = arg1;
}

void toyFieldStadiumLoad(void) {
    int i;

    switch (g_GameLogic._125) {
    case 0:
        stadiumMusic(-1);
        fn_3_10C7A4();
        sound_crowd_EffectsStruct._2C = 0;
        g_GameLogic._125++;
        // fallthrough
    case 1:
        if (fn_3_90928()) {
            g_GameLogic._125++;
        }
        break;
    case 2:
        if (diskReadRelated(CommonUIFiles_minigame + 0x1D0, 9)) {
            g_GameLogic._125++;
        }
        break;
    case 3:
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
            if (diskReadRelated(CommonUIFiles_minigame + 0xD0, 0x11)) {
                g_GameLogic._125++;
            }
        } else {
            g_GameLogic._125++;
        }
        break;
    default:
        fn_800189E4();
        insertGraphicDrawingFunction(startMenuMusic, 1);
        g_Minigame.battingHandedness[5] = 1;
        SetGameStatus(g_Minigame._19DF);
        break;
    }
}

void minigameSelectSwitcher(void) {
    u8 mode;

    switch (g_GameLogic._125) {
    case 0:
        changeScene(6, 6);
        g_GameLogic._125++;
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        hugeAnimStruct[0x307E] = 0;
        g_Minigame._19E4 = 0;
        break;
    case 1:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 20) {
            g_GameLogic._125++;
        }
        break;
    case 2:
        fn_3_10EFAC();
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        break;
    case 3:
        if (animRelated[0xBB] == 0) {
            g_GameLogic._125++;
        }
        break;
    case 4:
        mode = g_Minigame.GameMode_MiniGame;
        if (mode >= MINI_GAME_ID_BOBOMB_DERBY && mode <= MINI_GAME_ID_STAR_DASH) {
            if (g_Minigame._190A != 0) {
                g_Minigame._19E4 = 0;
            } else {
                g_Minigame._19E4 = ((u8*)&g_d_GameSettings)[0x13 + mode];
            }
        }
        SetGameStatus(GAME_STATUS_TOY_STADIUM_CHARACTER_SELECT);
        break;
    case 5:
        switch (((int (*)(u16))exitMenu_main)(g_Controls[lbl_80366158[0x27]].newButtonInput)) {
        case 1:
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_GameLogic._125++;
            break;
        case 2:
            g_GameLogic._125 = 2;
            break;
        }
        break;
    case 6:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 45) {
            changeScene(4, 6);
        }
        if (lbl_8037169C[0x13] != 0) {
            fn_80062A74();
            g_Minigame.battingHandedness[5] = 0;
            g_GameLogic._125++;
        }
        break;
    case 7:
        fn_8004CC18();
        g_GameLogic.framesOfExitingToMenu = 1;
        break;
    }
}

void fn_3_10EFAC(void) {
    InputStruct* input = &g_Controls[lbl_80366158[0x27]];

    if (animRelated[0xBB] == 0) {
        if (input->newButtonInput & INPUT_BUTTON_A) {
            u8 id = lbl_3_data_21268[(s8)g_Minigame._19E1];

            if (id == MINI_GAME_ID_STAR_DASH && g_d_GameSettings._12 < 1) {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            } else if (id == MINI_GAME_ID_MARIO_GRAND_PRIX && g_d_GameSettings._12 < 2) {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            } else {
                g_GameLogic._125 = 3;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            }
        } else if (input->newButtonInput & INPUT_BUTTON_B) {
            fn_3_5B408();
            g_GameLogic._125 = 5;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        } else if (input->_08 & INPUT_BUTTON_LEFT) {
            if ((s8)g_Minigame._19E1 != 0) {
                g_Minigame._19E1--;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else if (input->_08 & INPUT_BUTTON_RIGHT) {
            if ((s8)g_Minigame._19E1 < 6) {
                g_Minigame._19E1++;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    }
    g_Minigame.GameMode_MiniGame = lbl_3_data_21268[(s8)g_Minigame._19E1];
    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_MARIO_GRAND_PRIX) {
        g_Minigame._1A3C = 1;
    } else {
        g_Minigame._1A3C = 0;
    }
    animRelated[0xB9] = g_Minigame._19E1;
}

void toyFieldCharSelectSwitcher(void) {
    int i;
    int j;
    u32 k;

    if (g_GameLogic._125 <= 2) {
        for (i = 0; i < 4; i++) {
            g_Minigame.selectSlots[i]._8 = g_Minigame.selectSlots[i]._7;
            g_Minigame.selectSlots[i]._7 = 1;
        }
    }
    switch (g_GameLogic._125) {
    case 0:
        for (i = 0; i < 4; i++) {
            if (g_Minigame.selectSlotState[i] == 1) {
                g_Minigame.selectSlotState[i] = -1;
            }
            g_Minigame.playerSlots.aiStrength[i] = 0;
            (&g_Minigame._1A13)[i] = 1;
        }
        if (g_Minigame._190A != 0) {
            css_initValues(1, 1, 1, 1, 1, 0);
            for (i = 0; i < 54; i++) {
                if ((s8)starMissionCompletionTracker[i]._31 != CHALLENGE_RECRUITMENT_CD_RECRUITED) {
                    fn_8004FDA0(i);
                }
            }
            g_Minigame.selectSlots[lbl_3_common_bss_37400.humanTeam].charID = g_d_GameSettings._36;
        } else {
            css_initValues(1, 1, 1, 1, 1, 1);
            for (i = 0; i < 4; i++) {
                if (g_Minigame.selectSlotState[i] < 0) {
                    g_Minigame.selectSlots[i].charID = -1;
                }
            }
        }
        for (i = 0; i < 3; i++) {
            if (g_Minigame.selectSlots[i].charID >= 0) {
                for (j = i + 1; j < 4; j++) {
                    if (g_Minigame.selectSlots[i].charID == g_Minigame.selectSlots[j].charID) {
                        g_Minigame.selectSlots[j].charID = -3;
                    }
                }
            }
        }
        cssLoadingRelated_1(1, g_Minigame.selectSlots[0].charID, g_Minigame.selectSlots[1].charID,
                            g_Minigame.selectSlots[2].charID, g_Minigame.selectSlots[3].charID, 1);
        for (i = 0; i < 4; i++) {
            g_Minigame.selectSlots[i]._1 = 0;
            (&g_Minigame._19D2)[i] = 20;
        }
        hugeAnimStruct[0x307E] = 0;
        hugeAnimStruct[0x2D77] = 0;
        hugeAnimStruct[0x307A] = 5;
        g_Minigame.bB_bombBarrelHitInd_bOD_hrYaw = -1;
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_Minigame._19DE = 0;
        g_Minigame._19E2 = 0;
        g_Minigame._19E3 = 0;
        if (g_Minigame.battingHandedness[5] == 0) {
            insertGraphicDrawingFunction(startMenuMusic, 1);
        }
        changeScene(1, 6);
        g_GameLogic._125++;
        break;
    case 1:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
            for (i = 0; i < 4; i++) {
                if (g_Minigame.selectSlotState[i] == 0) {
                    g_Minigame.selectSlots[i].charID = cssCursorOnBottomControl_maybe(i, 0, 0, 0, 0);
                    g_Minigame.selectSlots[i]._6 = 0;
                    g_Minigame.battingHandedness[i] =
                        ((CharacterStats*)&Static_Stats_Tables)[g_Minigame.selectSlots[i].charID].stats.FieldingArm * 2 +
                        ((CharacterStats*)&Static_Stats_Tables)[g_Minigame.selectSlots[i].charID].stats.BattingStance;
                    g_Minigame.playerSlots._08[i] = 0;
                }
            }
            changeScene(1, 6);
        }
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 30) {
            g_Minigame._19DE = 0;
            if (g_Minigame._19E0 != 0) {
                g_Minigame._19DE = 5;
                g_Minigame._19E0 = 0;
                g_Minigame.selectSlots[lbl_80366158[0x27]]._1 = 1;
                addOrRemoveCharacterToTeam(lbl_80366158[0x27], g_Minigame.selectSlots[lbl_80366158[0x27]].charID, TRUE);
            }
            g_GameLogic._125++;
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        }
        break;
    case 2:
        fn_3_10CC20();
        break;
    case 3:
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
            if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 20) {
                switch (((int (*)(u16))exitMenu_main)(g_Controls[lbl_80366158[0x27]].newButtonInput)) {
                case 1:
                    g_GameLogic._125 = 4;
                    g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                    break;
                case 2:
                    g_GameLogic._125 = 2;
                    break;
                }
            }
            return;
        }
        g_GameLogic._125 = 4;
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        break;
    case 4:
        if (g_Minigame._1A0C == -1) {
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 45) {
                    changeScene(4, 6);
                }
                if (lbl_8037169C[0x13] != 0) {
                    g_GameLogic._125 = 5;
                }
            } else if (g_GameLogic.FrameCountOfCurrentAtBat_Copy >= 15) {
                SetGameStatus(GAME_STATUS_MINIGAME_SELECT);
            }
        }
        hugeAnimStruct[0x307A] = 0;
        break;
    case 5:
        unregisterMatchHudObjects();
        fn_8004CC18();
        g_GameLogic.framesOfExitingToMenu = 1;
        break;
    case 6:
        if (g_Minigame._1A0F < 0) {
            for (i = 0; i < 4; i++) {
                if (g_Minigame.selectSlots[i]._7 == 0 && g_Minigame.selectSlots[i]._1 != 0) {
                    break;
                }
            }
            if (i >= 4) {
                changeScene(3, 6);
                if (g_Minigame._1A3C == 0) {
                    menuMusic.fade = 6;
                    g_Minigame.battingHandedness[5] = 0;
                }
            }
        }
        if (lbl_8037169C[0x13] != 0) {
            g_GameLogic._125 = 7;
        }
        break;
    case 7:
        resetAnimTracks();
        minigamesFillRoster();
        hugeAnimStruct[0x307A] = 0;
        g_Minigame.battingHandedness[6] = 0;
        if (g_Minigame._1A3C != 0) {
            memset(&g_Minigame.grandPrixResults, 0, 0x28);
            g_Minigame._1A3D = 0;
            g_Minigame._1A3F = 0;
            hugeAnimStruct[0x307E] = 0;
            k = 0;
            do {
                g_Minigame.grandPrixOrder[k] = k + 1;
                k++;
            } while (k < 6);
            shuffleU8Array(g_Minigame.grandPrixOrder, 6, FALSE);
            SetGameStatus(GAME_STATUS_0x28);
        } else {
            SetGameStatus(GAME_STATUS_MINIGAME_READY);
        }
        break;
    }
    if (g_GameLogic._125 == 3 || g_GameLogic._125 == 4) {
        for (i = 0; i < 4; i++) {
            g_Minigame.selectSlots[i]._7 = 0;
        }
    }
    if (g_GameLogic._125 >= 2) {
        fn_3_10C81C();
    }
}

void fn_3_10C81C(void) {
    struct {
        int idx;
        int val;
    } order[4];
    int count;
    int n;
    int i;
    int j;
    int k;
    int offset;
    int slot;
    int sel;
    int fontCharID;

    n = 4;
    for (;;) {
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
            n = 1;
        }
        count = 0;
        for (i = 0; i < n; i++) {
            order[i].idx = -1;
            if (g_Minigame._1A0C != i) {
                s8 c = g_Minigame.selectSlots[i].charID;

                if (c != -1) {
                    if (c == g_Minigame.selectSlots[i]._2[0] && g_Minigame.selectSlots[i]._2[2] == g_Minigame.battingHandedness[i]) {
                        continue;
                    }
                    g_Minigame.selectSlots[i]._7 = 0;
                    if ((&g_Minigame._19D2)[i] >= 20 || g_Minigame._19DE == 4) {
                        order[count].idx = i;
                        order[count].val = (&g_Minigame._19D2)[i];
                        count++;
                        g_Minigame.selectSlots[i]._2[3] = g_Minigame.battingHandedness[i];
                    }
                }
            }
        }
        for (i = 0; i < count - 1; i++) {
            for (j = i + 1; j < count; j++) {
                if (order[i].val < order[j].val) {
                    int tmpIdx = order[i].idx;
                    int tmpVal = order[i].val;

                    order[i].idx = order[j].idx;
                    order[i].val = order[j].val;
                    order[j].idx = tmpIdx;
                    order[j].val = tmpVal;
                }
            }
        }
        (&g_Minigame._1A0F)[0] = -1;
        (&g_Minigame._1A0F)[1] = -1;
        (&g_Minigame._1A0F)[2] = -1;
        (&g_Minigame._1A0F)[3] = -1;
        offset = 0;
        if (g_Minigame._1A0C >= 0) {
            g_Minigame._1A0F = g_Minigame._1A0C;
            offset = 1;
        }
        for (k = 0; k < count; k++) {
            (&g_Minigame._1A0F)[offset + k] = order[k].idx;
        }
        if (g_Minigame._1A0F >= 0) {
            slot = g_Minigame._1A0F;
            sel = slot;
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
                sel = 9;
            }
            if (g_Minigame.battingHandedness[4] == 0) {
                g_Minigame.battingHandedness[4] = 1;
                fn_80011B64(sel);
            }
            if (g_Minigame.selectSlots[slot]._2[1] >= 0) {
                fontCharID = fn_80016710(g_Minigame.selectSlots[slot]._2[1], sel);
            } else {
                fontCharID = fn_80016710(g_Minigame.selectSlots[slot].charID, sel);
            }
            if (fontCharID != 0) {
                g_Minigame.selectSlots[slot]._2[0] = g_Minigame.selectSlots[slot]._2[1];
                g_Minigame.selectSlots[slot]._2[1] = -1;
                hugeAnimStruct[0x2D77] = 0;
                g_Minigame.selectSlots[slot]._2[2] = g_Minigame.selectSlots[slot]._2[3];
                g_Minigame._1A0C = -1;
                g_Minigame._1A0F = -1;
                (&g_Minigame._1A13)[slot] = 0;
                g_Minigame.battingHandedness[4] = 0;
                fn_3_E1370(3);
                continue;
            }
            if (g_Minigame.selectSlots[slot]._2[1] < 0) {
                g_Minigame.selectSlots[slot]._2[1] = g_Minigame.selectSlots[slot].charID;
            }
            g_Minigame.selectSlots[slot]._2[0] = -1;
            g_Minigame._1A0C = slot;
        }
        break;
    }
    for (i = 0; i < 4; i++) {
        if ((&g_Minigame._1A13)[i] != 0 && g_Minigame.selectSlots[i].charID == g_Minigame.selectSlots[i]._2[0]) {
            (&g_Minigame._1A13)[i] = 0;
        }
    }
}

void fn_3_10C7A4(void) {
    int i;

    fn_8001CA40(0);
    for (i = 0; i < 4; i++) {
        fn_80011BE4(i);
        g_Minigame.selectSlots[i]._1 = 0;
        g_Minigame.selectSlots[i]._2[0] = -1;
    }
}

void fn_3_10C58C(void) {
    minigamesFillRoster();
}

void fn_3_10C450(int slot, int charID) {
    CharacterStats* roster = &inMemRoster[0][slot];

    memcpy(roster, &((CharacterStats*)&Static_Stats_Tables)[charID], sizeof(CharacterStats));
    if (g_Minigame.playerSlots._08[slot] != 0) {
        roster->stats.SlapContactSize += stonNiceContactIncrement.SlapContactSize;
        roster->stats.ChargeContactSize += stonNiceContactIncrement.ChargeContactSize;
        roster->stats.SlapHitPower += stonNiceContactIncrement.SlapHitPower;
        roster->stats.ChargeHitPower += stonNiceContactIncrement.ChargeHitPower;
        roster->stats.BuntingContactSize += stonNiceContactIncrement.BuntingContactSize;
        roster->stats.Speed += stonNiceContactIncrement.Speed;
        roster->stats.ThrowingArm += stonNiceContactIncrement.ThrowingArm;
        roster->stats.CurveBallSpeed += stonNiceContactIncrement.CurveBallSpeed;
        roster->stats.FastBallSpeed += stonNiceContactIncrement.FastBallSpeed;
        roster->stats.cursedBall += stonNiceContactIncrement.cursedBall;
        roster->stats.Curve += stonNiceContactIncrement.Curve;
        roster->stats.curveControl += stonNiceContactIncrement.curveControl;
    }
}

void minigames_pickOpponentsAndLoadStats(void) {
    int pool[12];
    int used[4];
    int i;
    int j;
    int k;
    int cursor;
    int count;
    int idx;

    for (i = 0; i < 4; i++) {
        if (g_Minigame.playerSlots.aiControlledInd[i] == 0 && g_Minigame.selectSlotState[i] >= 0) {
            used[i] = g_Minigame.selectSlots[i].charID;
        } else {
            used[i] = -1;
        }
    }

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && g_d_GameSettings.exhibitionMatchInd == FALSE) {
        for (i = 0; i < lbl_3_data_1894C[0]; i++) {
            pool[i] = lbl_3_data_1894C[i + 1];
        }
    } else if (g_Minigame._1A3C != 0) {
        for (i = 0; i < 12; i++) {
            pool[i] = lbl_800E854C[i];
        }
        shuffleIntArray(pool, 12, FALSE);
    } else {
        u8 mode = g_Minigame.GameMode_MiniGame;

        if ((mode == MINI_GAME_ID_BOBOMB_DERBY || mode == MINI_GAME_ID_BARREL_BATTER) && g_Minigame._1908 >= 0) {
            return;
        }
        count = 6;
        if (g_d_GameSettings.exhibitionMatchInd == FALSE) {
            if (mode == MINI_GAME_ID_WALLBALL) {
                idx = g_Minigame.soloMinigameDifficulty;
            } else if (mode == MINI_GAME_ID_CHAINCHOMP_SPRINT) {
                idx = g_Minigame.soloMinigameDifficulty + 3;
            } else if (mode == MINI_GAME_ID_PIRANHA_PANIC) {
                idx = g_Minigame.soloMinigameDifficulty + 6;
            } else if (mode == MINI_GAME_ID_STAR_DASH) {
                idx = g_Minigame.soloMinigameDifficulty + 9;
            } else {
                idx = 0;
            }
            count = 0;
            for (i = 0; i < 6; i++) {
                pool[i] = challenge_minigames_opponentCharIDs[idx * 6 + i];
                if (pool[i] != 0xFF) {
                    count++;
                }
            }
        } else {
            if (mode == MINI_GAME_ID_WALLBALL) {
                if (g_Minigame.soloMinigameDifficulty == MINIGAME_DIFFICULTY_SOLO_NON_CHALLENGE) {
                    idx = -1;
                } else {
                    idx = g_Minigame.soloMinigameDifficulty + 1;
                }
            } else if (mode == MINI_GAME_ID_CHAINCHOMP_SPRINT) {
                idx = g_Minigame.soloMinigameDifficulty + 5;
            } else if (mode == MINI_GAME_ID_PIRANHA_PANIC) {
                idx = g_Minigame.soloMinigameDifficulty + 9;
            } else if (mode == MINI_GAME_ID_STAR_DASH) {
                idx = g_Minigame.soloMinigameDifficulty + 13;
            } else {
                idx = 0;
            }
            if (idx < 0) {
                for (i = 0; i < 6; i++) {
                    pool[i] = -1;
                }
            } else {
                u8* row = lbl_3_data_212A4 + idx * 6;

                for (i = 0; i < 6; i++) {
                    pool[i] = row[i];
                }
            }
        }
        shuffleIntArray(pool, count, FALSE);
    }

    cursor = 0;
    for (i = 0; i < 4; i++) {
        if (g_Minigame.selectSlotState[i] != 0 && g_Minigame.selectSlots[i]._1 == 0) {
            for (j = cursor; j < 6; j++) {
                for (k = 0; k < 4; k++) {
                    if (pool[j] == used[k] && pool[j] >= 0) {
                        break;
                    }
                }
                if (k >= 4) {
                    break;
                }
                cursor++;
            }
            g_Minigame.selectSlots[i].charID = pool[j];
            (&g_Minigame._19D2)[i] = 20;
            g_Minigame.battingHandedness[i] =
                ((CharacterStats*)&Static_Stats_Tables)[pool[j]].stats.FieldingArm * 2 +
                ((CharacterStats*)&Static_Stats_Tables)[pool[j]].stats.BattingStance;
            cursor++;
        }
    }
}

void fn_3_10B8D0(void) {
    int i;

    switch (g_GameLogic._125) {
    case 0:
        hugeAnimStruct[0x307E] = 0;
        if ((g_Minigame._1A3C == 0 || g_Minigame.grandPrixRound <= 1) && g_Minigame._1A38 == 0) {
            fn_80062A74();
            fn_800189B8();
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
                fn_80035B50(0x11);
            }
            fn_80035B50(9);
            fn_3_908E8();
        }
        g_Minigame.battingHandedness[5] = 0;
        g_Minigame._1A41 = 0;
        g_Minigame.multiPlayerInd = 0;
        g_Minigame._19AA = 0;
        g_Minigame._1908 = -1;
        g_Minigame.battingHandedness[6] = 0;
        g_Minigame._1A23 = 0;
        g_Minigame._1A24[0] = 2;
        g_Minigame._1A46[0] = 0;
        if (g_d_GameSettings.exhibitionMatchInd == FALSE) {
            g_Minigame._1A24[0] = 0;
        }
        g_d_GameSettings._3A = g_Minigame.soloMinigameDifficulty;
        lbl_8037169C[0x15] = 0;
        sound_crowd_EffectsStruct._2C = 0;
        if (g_Minigame._1907 != 1 || g_Minigame._1A3C != 0) {
            g_Minigame.multiPlayerInd = 1;
            g_Minigame.soloMinigameDifficulty = MINIGAME_DIFFICULTY_MULTIPLAYER_CHALLENGE_EASY;
        }
        if (g_Minigame._1907 == 1) {
            for (i = 0; i < 4; i++) {
                if (g_Minigame.playerSlots.aiControlledInd[i] == 0) {
                    g_Minigame._1908 = i;
                    break;
                }
            }
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
            g_d_GameSettings._33 = 0;
        } else {
            g_d_GameSettings._33 = g_Minigame.GameMode_MiniGame;
        }
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125++;
        if (g_Minigame._1A38 != 0 && g_Minigame._1A3C == 0) {
            changeScene(1, 6);
            g_GameLogic._125 = 2;
        }
        break;
    case 1:
        if (diskReadRelated(CommonUIFiles_minigame + (g_Minigame.GameMode_MiniGame + 6) * 16, 0x11)) {
            changeScene(1, 6);
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_GameLogic._125++;
        }
        break;
    case 2:
        if (g_Minigame._1A38 != 0 && g_Minigame._1A3C == 0) {
            g_GameLogic._125 = 8;
        } else if (fn_3_90860()) {
            sound_crowd_EffectsStruct._2C = 0;
            g_GameLogic._125++;
        }
        break;
    case 3:
        g_d_GameSettings.StadiumID = mapping_minigame_Stadium[g_Minigame.GameMode_MiniGame];
        if (fn_3_90A18()) {
            g_GameLogic._125++;
        }
        break;
    case 4:
        fn_80018B74();
        g_GameLogic._125++;
        // fallthrough
    case 5:
        minigameStadiumSetup();
        g_GameLogic._125++;
        break;
    case 6:
        if (!fn_3_10F564()) {
            g_GameLogic._125++;
        }
        break;
    case 7:
        if (fn_80020388()) {
            g_GameLogic._125++;
        }
        break;
    case 8:
        if (g_Minigame.battingHandedness[6] != 0) {
            changeScene(3, 6);
            if (g_Minigame.battingHandedness[6] == 2) {
                g_GameLogic._125 = 10;
            } else {
                g_GameLogic._125 = 9;
            }
        }
        break;
    case 9:
        if (lbl_8037169C[0x13] != 0) {
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                g_Scores.inningLimit = g_Minigame._1A24[0] * 2 + 1;
                g_Scores.maxNumberOfExtraInnings = g_Minigame._1A24[0] * 2 + 1;
                SetGameStatus(GAME_STATUS_GAME_START_MOVIE);
            } else {
                SetGameStatus(GAME_STATUS_LOAD_GAME);
            }
            fn_3_BF070();
        }
        break;
    case 10:
        if (lbl_8037169C[0x13] != 0) {
            g_GameLogic._125 = 11;
        }
        break;
    case 11:
        g_Minigame._1A38 = 0;
        fn_3_10B200();
        break;
    }
    if (g_GameLogic._125 >= 2 && g_Minigame.battingHandedness[6] == 0) {
        fn_3_10B27C();
    }
}

void fn_3_10B27C(void) {
    int k;

    if (g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
        int mode;

        g_Minigame.battingHandedness[7] = 0;
        g_Minigame.battingHandedness[8] = 0;
        g_Minigame._1A20 = 0;
        g_Minigame._1A22 = 0;
        if (g_Minigame.multiPlayerInd != 0) {
            g_Minigame._1A20 = 2;
        } else if (g_Minigame.soloMinigameDifficulty == MINIGAME_DIFFICULTY_SOLO_NON_CHALLENGE) {
            g_Minigame._1A20 = 1;
        }
        mode = g_Minigame.GameMode_MiniGame;
        if (g_GameLogic.gameStatus == GAME_STATUS_0x28) {
            mode = MINI_GAME_ID_MARIO_GRAND_PRIX;
        }
        g_Minigame._1A21 = 0;
        for (k = 0; k < 5; k++) {
            if (lbl_3_data_B060[mode][g_Minigame._1A20][k] >= 0) {
                g_Minigame._1A21++;
            }
        }
    }
    if (lbl_8037169C[0x12] == 0) {
        return;
    }
    if (g_Minigame.battingHandedness[8] != 0) {
        g_Minigame.battingHandedness[8]--;
        return;
    }
    if (g_Minigame.battingHandedness[7] == 0) {
        if (checkForButtonPressToSkip(1, INPUT_BUTTON_B)) {
            if (g_Minigame._1A3C == 0 || g_GameLogic.gameStatus == GAME_STATUS_0x28) {
                g_Minigame.battingHandedness[6] = 2;
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            }
            return;
        }
        if (g_GameLogic._125 >= 8 || g_GameLogic.gameStatus == GAME_STATUS_0x28) {
            if (checkForButtonPressToSkip(1, INPUT_BUTTON_A)) {
                if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                    if (g_Minigame._1A23 != 0) {
                        return;
                    }
                    g_Minigame.battingHandedness[6] = 1;
                    sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                } else {
                    g_Minigame.battingHandedness[6] = 1;
                    sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                }
                return;
            }
        }
        if (checkForButtonPressToSkip(2, INPUT_TRIGGER_R)) {
            g_Minigame.battingHandedness[7] = 1;
            g_Minigame._1A22 = 0;
            g_Minigame.battingHandedness[8] = 30;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            return;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && g_d_GameSettings.exhibitionMatchInd != FALSE) {
            if (checkForButtonPressToSkip(2, INPUT_BUTTON_UP) && g_Minigame._1A23 == 1) {
                g_Minigame._1A23 = 0;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            } else if (checkForButtonPressToSkip(2, INPUT_BUTTON_DOWN) && g_Minigame._1A23 == 0) {
                g_Minigame._1A23 = 1;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            } else if (g_Minigame._1A23 == 1) {
                if (checkForButtonPressToSkip(2, INPUT_BUTTON_LEFT)) {
                    if (g_Minigame._1A24[0] == 0) {
                        g_Minigame._1A24[0] = 4;
                    } else {
                        g_Minigame._1A24[0]--;
                    }
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                } else if (checkForButtonPressToSkip(2, INPUT_BUTTON_RIGHT)) {
                    if (g_Minigame._1A24[0] == 4) {
                        g_Minigame._1A24[0] = 0;
                    } else {
                        g_Minigame._1A24[0]++;
                    }
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                }
            }
        }
    } else {
        if (g_GameLogic._125 >= 8 || g_GameLogic.gameStatus == GAME_STATUS_0x28) {
            if (checkForButtonPressToSkip(0, INPUT_BUTTON_A)) {
                g_Minigame.battingHandedness[6] = 1;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                return;
            }
        }
        if (checkForButtonPressToSkip(2, INPUT_BUTTON_B | INPUT_TRIGGER_R)) {
            g_Minigame.battingHandedness[7] = 0;
            g_Minigame._1A22 = 0;
            g_Minigame.battingHandedness[8] = 30;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (g_Minigame._1A21 > 1) {
            if (checkForButtonPressToSkip(2, INPUT_BUTTON_RIGHT)) {
                if (g_Minigame.battingHandedness[7] == g_Minigame._1A21) {
                    g_Minigame.battingHandedness[7] = 1;
                } else {
                    g_Minigame.battingHandedness[7]++;
                }
                g_Minigame._1A22 = 0;
                g_Minigame.battingHandedness[8] = 20;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            } else if (checkForButtonPressToSkip(2, INPUT_BUTTON_LEFT)) {
                if (g_Minigame.battingHandedness[7] == 1) {
                    g_Minigame.battingHandedness[7] = g_Minigame._1A21;
                } else {
                    g_Minigame.battingHandedness[7]--;
                }
                g_Minigame._1A22 = 1;
                g_Minigame.battingHandedness[8] = 20;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    }
}

void fn_3_10B200(void) {
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD) {
        *(s16*)&hugeAnimStruct[0x3078] = 0;
    }
    fn_80035B50(0xD);
    cleanupMinigameResources();
    fn_3_5E60();
    fn_80018B38();
    fn_3_909B0();
    fn_3_9081C();
    fn_80035B50(0x11);
    g_Minigame._19DF = GAME_STATUS_TOY_STADIUM_CHARACTER_SELECT;
    SetGameStatus(GAME_STATUS_TOY_STADIUM_LOAD);
}

void minigameStartSwitcher(void) {
    int i;

    switch (g_GameLogic._125) {
    case 0:
        challenge_setTransitionScreenCharacterPortrait(7, 0);
        g_Minigame._1A40 = 0;
        g_Minigame._19A7 = lbl_3_data_21270[g_Minigame.GameMode_MiniGame];
        g_Minigame._1A3E = 0;
        hugeAnimStruct[0x307E] = 1;
        hugeAnimStruct[0x2D8E] = 0;
        g_GameLogic._125 = 1;
        if (g_d_GameSettings.exhibitionMatchInd == FALSE) {
            g_d_GameSettings._36 = g_Minigame.playerSlots._04[(s8)g_Minigame._1908];
        }
        break;
    case 1:
        fn_3_10C81C();
        if (g_Minigame._1A0F < 0) {
            fn_3_E1370(lbl_3_data_18918[g_Minigame.GameMode_MiniGame]);
            g_GameLogic._125 = 2;
        }
        break;
    case 2:
        if (fn_80016F7C()) {
            g_GameLogic._125 = 3;
            sound_crowd_EffectsStruct._2C = 0;
        }
        break;
    case 3:
        if (fn_3_90DD8()) {
            g_GameLogic._125 = 5;
        }
        break;
    case 5:
        g_GameLogic._125 = 6;
        break;
    case 6:
        if (lbl_8037169C[0x12] == 0) {
            return;
        }
        if (g_GameLogic.FrameCountOfCurrentPitch >= lbl_3_data_18C48[2] ||
            (g_GameLogic.FrameCountOfCurrentPitch >= lbl_3_data_18C48[1] && checkForButtonPressToSkip(2, 0x1100))) {
            g_GameLogic._125 = 7;
            changeScene(3, 6);
            fn_8003A540(0);
        }
        break;
    case 7:
        if (lbl_8037169C[0x13] != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
            g_GameLogic._125 = 8;
        }
        break;
    case 8:
        g_Minigame._1A38 = 0;
        g_Minigame._1A39 = 0;
        hugeAnimStruct[0x307A] = 1;
        for (i = 0; i < 4; i++) {
            if (g_Minigame.playerSlots.characterIndex[i] >= 0) {
                g_Minigame.playerSlots._14[i] = i;
            }
        }
        if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_BOBOMB_DERBY) {
            minigamesSetSomePointers();
            minigamesGXStuff();
            g_Minigame.bOD_fireworksTimer = 0;
        }
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_WALLBALL) {
            SetGameStatus(GAME_STATUS_0x23);
        } else if (g_Minigame.miniGameNumberOfParticipants >= 2) {
            if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_STAR_DASH) {
                SetGameStatus(GAME_STATUS_TRANSITION_MINIGAME_TO_BATTING);
            } else {
                SetGameStatus(GAME_STATUS_0x23);
            }
        } else {
            SetGameStatus(GAME_STATUS_TRANSITION_MINIGAME_TO_BATTING);
        }
        break;
    }
    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_BOBOMB_DERBY && g_GameLogic._125 >= 3) {
        bOD_AmbientFireworks();
    }
}

void fn_3_10AE18(void) {
    fn_3_10AD48();
    SetGameStatus(GAME_STATUS_TRANSITION_MINIGAME_TO_BATTING);
}

void fn_3_10AD48(void) {
    int order[4];
    int i;

    order[0] = -1;
    order[1] = -1;
    order[2] = -1;
    order[3] = -1;
    for (i = 0; i < 4; i++) {
        if (g_Minigame.playerSlots.characterIndex[i] >= 0) {
            order[i] = i;
        }
    }
    shuffleIntArray(order, g_Minigame.miniGameNumberOfParticipants, FALSE);
    g_Minigame.playerSlots._14[0] = order[0];
    g_Minigame.playerSlots._14[1] = order[1];
    g_Minigame.playerSlots._14[2] = order[2];
    g_Minigame.playerSlots._14[3] = order[3];
}

void fn_3_10A01C(void) {
    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY) {
        bOD_UpdateFieldObjects();
    } else if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_WALLBALL) {
        wallBallEmptyHook();
    } else if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER) {
        fn_3_1323CC();
    } else if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_CHAINCHOMP_SPRINT) {
        fn_3_141A2C();
    } else if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_PIRANHA_PANIC) {
        fn_3_1471C0();
    } else if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_STAR_DASH) {
        sD_EmptyHook();
    }
}

void fn_3_109DE0(MinigameResultEntry* out) {
    memset(out, 0, sizeof(MinigameResultEntry));
    if (g_Minigame._1907 == 1) {
        out->charID = inMemRoster[0][g_Minigame.playerSlots.characterIndex[(s8)g_Minigame._1908]].stats.CharID;
        if (g_Minigame._1A3C != 0) {
            MiniGrandPrixScoreInput input;

            fn_8006C398(&input);
            if (g_Minigame._1A3C != 0 && (s8)g_Minigame._1908 >= 0 && (s8)g_Minigame._1908 < 4) {
                u32 i;
                u32 j;
                u8 order[4][2];

                i = 0;
                do {
                    input.vals[i] = g_Minigame.grandPrixPoints[i];
                    i++;
                } while (i < 6);
                i = 0;
                do {
                    input.bytes[i] = g_Minigame.grandPrixOrder[i];
                    i++;
                } while (i < 6);
                fn_3_1079C8(order, 1);
                j = 0;
                do {
                    if ((s8)g_Minigame._1908 == order[j][0]) {
                        input.placeRank = order[j][1];
                    }
                    j++;
                } while (j < g_Minigame.miniGameNumberOfParticipants);
                input.extra = g_Minigame._1E22[(s8)g_Minigame._1908];
                input.charID = inMemRoster[0][g_Minigame.playerSlots.characterIndex[(s8)g_Minigame._1908]].stats.CharID;
            }
            out->score = (s16)fn_8006C13C(&input);
            out->count = 0;
        } else {
            out->score = g_Minigame.miniGameCurrentPoints[(s8)g_Minigame._1908];
            if (out->score > lbl_80109410[g_Minigame.GameMode_MiniGame]) {
                out->score = lbl_80109410[g_Minigame.GameMode_MiniGame];
            }
            switch (g_Minigame.GameMode_MiniGame) {
            case MINI_GAME_ID_BOBOMB_DERBY:
                out->count = g_Minigame.bOD_HitPowerOfEachChar[(s8)g_Minigame._1908];
                if (out->count > 999) {
                    out->count = 999;
                }
                break;
            default:
                out->count = 0;
                break;
            }
        }
    }
}

MinigameResultEntry* fn_3_109D88(void) {
    if (g_Minigame._1A3C != 0) {
        return &lbl_803616CC[7][0];
    }
    if (g_Minigame.GameMode_MiniGame != 0) {
        return &lbl_803616CC[g_Minigame.GameMode_MiniGame - 1][5];
    }
    return &lbl_803616CC[0][0];
}

int fn_3_109CE8(MinigameResultEntry* entry) {
    MinigameResultEntry* table;
    u32 i;

    if (g_Minigame._1907 != 1) {
        return;
    }
    table = fn_3_109D88();
    i = 0;
    do {
        if (entry->score > table[i].score) {
            break;
        }
        if (entry->score == table[i].score && entry->count > table[i].count) {
            break;
        }
        i++;
    } while (i < 5);
    return i;
}
