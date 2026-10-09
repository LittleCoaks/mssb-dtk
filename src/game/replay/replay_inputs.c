#define SQRT2_LINKAGE static
#include "game/replay/replay_inputs.h"
#define REP_HEADER_DATA_FN getRepHeaderData_replayInputs
#include "header_rep_data.h"
#include "game/replay/replay_state.h"
#include "game/stats/stat_tracking.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/camera/camera.h"
#include "game/match_setup/scene_skip.h"
#include "game/animation/scene_effects.h"
#include "game/sound/m_sound.h"
#include "game/ball/ball_visuals.h"
#include "game/stadium/stadium_framework.h"
#include "Unknown/File_0x800204cc.h"
#include "Dolphin/stl.h"
#include "musyx/musyx.h"

extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern void setScissorMode(int mode);
extern void fn_8001B224(void);
extern void fn_3_21C7C(int a, int b);

extern u8 us80893314[];
extern u8 us80893310[];
extern u8 lbl_3_common_bss_32220[];
extern u8 g_UnkThrowing_31ACC[];
extern u8 g_UnkAnimation_31EAC[];
extern u8 lbl_3_common_bss_321A0[];
extern u8 animRelated[];
extern u8 g_ReplayCopies[];

static u32 lbl_3_bss_1748[6];

#define STATS_AT(off) ((void*)((u8*)&g_Stats + (off)))
#define COPY_AT(off) ((void*)((u8*)g_ReplayCopies + (off)))

// .text:0x0007C9D8 size:0x4B8 mapped:0x806BBA6C
void CopyMoreStructs(int arg) {
    int i;

    if (arg == 0) {
        structCopying();
    }
    memcpy(&g_GameLogic, STATS_AT(0x44), sizeof(g_GameLogic));
    memcpy(&g_Strikes, STATS_AT(0x19C), sizeof(g_Strikes));
    memcpy(&g_Scores, STATS_AT(0x1C0), sizeof(g_Scores));
    memcpy(&g_Ball, STATS_AT(0x288), sizeof(g_Ball));
    memcpy(&g_Pitcher, STATS_AT(0x1E80), sizeof(g_Pitcher));
    memcpy(&g_Batter, STATS_AT(0x1FF8), sizeof(g_Batter));
    memcpy(&g_AiLogic, STATS_AT(0x20A8), sizeof(g_AiLogic));
    memcpy(&g_FieldingLogic, STATS_AT(0x2164), sizeof(g_FieldingLogic));
    memcpy(&g_RunningLogic, STATS_AT(0x22B4), sizeof(g_RunningLogic));
    memcpy(g_Fielders, STATS_AT(0x22D4), sizeof(g_Fielders));
    memcpy(g_Runners, STATS_AT(0x387C), sizeof(g_Runners));
    memcpy(BatterStats_P1_P2, STATS_AT(0x416C), sizeof(BatterStats_P1_P2));
    memcpy(PitcherStats_P1_P2, STATS_AT(0x4418), sizeof(PitcherStats_P1_P2));
    memcpy(us80893314, STATS_AT(0x3DCC), 6);
    memcpy(us80893310, STATS_AT(0x3DD2), 4);
    memcpy(lbl_3_common_bss_32220, STATS_AT(0x3DD6), 0xE);
    memcpy(g_UnkThrowing_31ACC, STATS_AT(0x3DE4), 0x14);
    memcpy(g_UnkAnimation_31EAC, STATS_AT(0x3DF8), 0x2F4);
    memcpy(lbl_3_common_bss_321A0, STATS_AT(0x40EC), 0x80);
    g_Stats.replayInd = 1;
    g_Stats.playFrameCounter = 0;
    useReplayInputs();
    fn_3_1CBCC();
    newAtBatPlaySound();
    animRelated[0xC8] = 0;
    fn_8001B224();
    initStadiumObjectData();
    for (i = 0; i < 13; i++) {
        fn_3_21C7C(i, 1);
    }
    sound_crowd_EffectsStruct._34 = 0;
}

// .text:0x0007C7AC size:0x22C mapped:0x806BB840
void structCopying(void) {
    memcpy(COPY_AT(0), &g_GameLogic, sizeof(g_GameLogic));
    memcpy(COPY_AT(0x158), &g_Strikes, sizeof(g_Strikes));
    memcpy(COPY_AT(0x17C), &g_Scores, sizeof(g_Scores));
    memcpy(COPY_AT(0x244), &g_Ball, sizeof(g_Ball));
    memcpy(COPY_AT(0x1E3C), &g_Pitcher, sizeof(g_Pitcher));
    memcpy(COPY_AT(0x1FB4), &g_Batter, sizeof(g_Batter));
    memcpy(COPY_AT(0x2064), &g_AiLogic, sizeof(g_AiLogic));
    memcpy(COPY_AT(0x2120), &g_FieldingLogic, sizeof(g_FieldingLogic));
    memcpy(COPY_AT(0x2270), &g_RunningLogic, sizeof(g_RunningLogic));
    memcpy(COPY_AT(0x2290), g_Fielders, sizeof(g_Fielders));
    memcpy(COPY_AT(0x3838), g_Runners, sizeof(g_Runners));
    memcpy(COPY_AT(0x4128), BatterStats_P1_P2, sizeof(BatterStats_P1_P2));
    memcpy(COPY_AT(0x43D4), PitcherStats_P1_P2, sizeof(PitcherStats_P1_P2));
    memcpy(COPY_AT(0x3D88), us80893314, 6);
    memcpy(COPY_AT(0x3D8E), us80893310, 4);
    memcpy(COPY_AT(0x3D92), lbl_3_common_bss_32220, 0xE);
    memcpy(COPY_AT(0x3DA0), g_UnkThrowing_31ACC, 0x14);
    memcpy(COPY_AT(0x3DB4), g_UnkAnimation_31EAC, 0x2F4);
    memcpy(COPY_AT(0x40A8), lbl_3_common_bss_321A0, 0x80);
}

// Must stay a real call: CopyMoreStructs would otherwise inline it.
#pragma dont_inline on
// .text:0x0007C4E4 size:0x2C8 mapped:0x806BB578
void useReplayInputs(void) {
    int i;

    if (g_Stats.playFrameCounter >= g_Stats._0028) {
        replaceGameStructs_postReplay(1);
        return;
    }
    if (g_Stats.playFrameCounter + 7 == g_Stats._0028 && g_Stats.replayReason != 2 && g_Stats.replayReason != 0xD) {
        changeScene(3, 6);
    }
    for (i = 0; i < 2; i++) {
        g_Controls[g_Stats.replayPort[i]].buttonInput = g_ReplayLogic[g_Stats.playFrameCounter].pad[i].buttonInput;
        g_Controls[g_Stats.replayPort[i]].newButtonInput = g_ReplayLogic[g_Stats.playFrameCounter].pad[i].newButtonInput;
        g_Controls[g_Stats.replayPort[i]].right_left = g_ReplayLogic[g_Stats.playFrameCounter].pad[i].right_left;
        g_Controls[g_Stats.replayPort[i]].up_down = g_ReplayLogic[g_Stats.playFrameCounter].pad[i].up_down;
        g_Controls[g_Stats.replayPort[i]].controlStickAngle = g_ReplayLogic[g_Stats.playFrameCounter].pad[i].controlStickAngle;
        {
            f32 mag = dolsqrtf2((f32)g_Controls[g_Stats.replayPort[i]].right_left * (f32)g_Controls[g_Stats.replayPort[i]].right_left +
                                (f32)g_Controls[g_Stats.replayPort[i]].up_down * (f32)g_Controls[g_Stats.replayPort[i]].up_down);
            mag -= 16.0f;
            if (mag > 56.0f) {
                mag = 56.0f;
            }
            g_Controls[g_Stats.replayPort[i]].controlStickMagnitude = 64.0f * mag / 56.0f;
        }
    }
    g_Stats.playFrameCounter++;
}

#pragma dont_inline reset
// .text:0x0007C1FC size:0x2E8 mapped:0x806BB290
void replaceGameStructs_postReplay(int arg) {
    g_Stats_s* stats = &g_Stats;

    stats->replayInd = 0;
    stats->replayPending = 0;
    memcpy(&g_GameLogic, COPY_AT(0), sizeof(g_GameLogic));
    memcpy(&g_Strikes, COPY_AT(0x158), sizeof(g_Strikes));
    memcpy(&g_Scores, COPY_AT(0x17C), sizeof(g_Scores));
    memcpy(&g_Ball, COPY_AT(0x244), sizeof(g_Ball));
    memcpy(&g_Pitcher, COPY_AT(0x1E3C), sizeof(g_Pitcher));
    memcpy(&g_Batter, COPY_AT(0x1FB4), sizeof(g_Batter));
    memcpy(&g_AiLogic, COPY_AT(0x2064), sizeof(g_AiLogic));
    memcpy(&g_FieldingLogic, COPY_AT(0x2120), sizeof(g_FieldingLogic));
    memcpy(&g_RunningLogic, COPY_AT(0x2270), sizeof(g_RunningLogic));
    memcpy(g_Fielders, COPY_AT(0x2290), sizeof(g_Fielders));
    memcpy(g_Runners, COPY_AT(0x3838), sizeof(g_Runners));
    memcpy(BatterStats_P1_P2, COPY_AT(0x4128), sizeof(BatterStats_P1_P2));
    memcpy(PitcherStats_P1_P2, COPY_AT(0x43D4), sizeof(PitcherStats_P1_P2));
    memcpy(us80893314, COPY_AT(0x3D88), 6);
    memcpy(us80893310, COPY_AT(0x3D8E), 4);
    memcpy(lbl_3_common_bss_32220, COPY_AT(0x3D92), 0xE);
    memcpy(g_UnkThrowing_31ACC, COPY_AT(0x3DA0), 0x14);
    memcpy(g_UnkAnimation_31EAC, COPY_AT(0x3DB4), 0x2F4);
    memcpy(lbl_3_common_bss_321A0, COPY_AT(0x40A8), 0x80);
    if (g_Stats.replayReason != 2 && stats->replayReason != 0xD) {
        fn_3_FBD70();
        if (arg != 0) {
            fn_3_FBD58();
            fn_3_1CBCC();
        }
    }
    setScissorMode(1);
    sound_crowd_EffectsStruct._2A = 1;
    sound_crowd_EffectsStruct._24 = 1;
    transitionToReplay();
    sound_crowd_EffectsStruct._33 = 2;
    fn_3_675B8(0);
    pauseAnimations();
    pauseStateOnStadiums();
    fn_3_B902C();
    if (lbl_3_bss_1748[0] != 0) {
        sndFXKeyOff(lbl_3_bss_1748[0]);
    }
}

// .text:0x0007C194 size:0x68 mapped:0x806BB228
BOOL checkReplaySkipButton(void) {
    if (g_Stats.playFrameCounter < 0x5A) {
        return FALSE;
    }
    if (g_Stats.playFrameCounter > g_Stats._0028 - 0x3C) {
        return FALSE;
    }
    return checkForButtonPressToSkip(1, 0x1100) != 0;
}

// .text:0x0007C190 size:0x4 mapped:0x806BB224
void fn_3_7C190(void) {
    return;
}

// .text:0x0007BC20 size:0x570 mapped:0x806BACB4
void determineIfReplayShouldPlay(void) {
    s32 reason = 0;
    int arg = 0;
    InMemBallType* ball = &g_Ball;
    inMemStrikes* strikes = &g_Strikes;
    int result;
    int count;
    int count2;

    if (g_GameLogic.freeFieldingPracticeInd != 0) {
        return;
    }
    if (ball->deadBallReason == DEAD_BALL_REASON_HOME_RUN) {
        reason = 2;
        if (storedInningInfo.goAheadRunOccurrences != 0) {
            reason = 9;
        }
        if (g_Ball.homeRunClassification == 1) {
            reason = 0xD;
        }
    } else if (g_Scores._C2 != 0) {
        result = storedInningInfo.abResultTemporary;
        if (result >= 6 && result <= 10) {
            reason = 3;
            if (reason == 3) {
                InMemRunnerType* runner = &g_Runners[0];
                if (strikes->outs != 3 && runner->runnerOnFieldOrOutOrScored != RUNNER_STATUS_OUT_DURING_PLAY &&
                    runner->runnerOnFieldOrOutOrScored != RUNNER_STATUS_SCORED_DURING_PLAY) {
                    reason = 4;
                }
            }
            if (ball->fielderWithBallIndexStored2 != 6 && ball->fielderWithBallIndexStored2 != 7 &&
                ball->fielderWithBallIndexStored2 != 8) {
                arg = reason;
                reason = 1;
            }
            if (g_pCamera->_AC6 == 3) {
                arg = reason;
                reason = 1;
            }
        }
        if (result == 0x11) {
            if (g_Scores._A6 <= 1) {
                reason = 5;
            } else if (g_Scores._A6 <= 1 && g_Scores._pad_AC >= 3) {
                reason = 5;
            }
            if (storedInningInfo.goAheadRunOccurrences != 0) {
                reason = 0xB;
            }
        }
        result = g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total -
                 g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total;
        if (result > 4 || result < -4) {
            reason = 0;
        }
    } else {
        inMemCamera* cam = g_pCamera;
        BOOL gameEnding = g_GameLogic.EventTriggers_EndOfGame;

        if (cam->_A50 >= 2) {
            if (gameEnding) {
                if (cam->_A98 > 0 &&
                    (storedInningInfo.abResultTemporary == 0x12 || storedInningInfo.abResultTemporary == 0x13 ||
                     storedInningInfo.abResultTemporary == 0x1A)) {
                    reason = 7;
                } else if (cam->_A98 > 0 && storedInningInfo.abResultTemporary >= 0x14 &&
                           storedInningInfo.abResultTemporary <= 0x1B) {
                    reason = 8;
                }
            } else {
                count = 0;
                if (g_Runners[1].rosterID != -1) {
                    count = 1;
                }
                if (g_Runners[2].rosterID != -1) {
                    count++;
                }
                if (g_Runners[3].rosterID != -1) {
                    count++;
                }
                if (g_Scores._A6 <= 4 && count == 3) {
                    if (cam->_A98 > 0 &&
                    (storedInningInfo.abResultTemporary == 0x12 || storedInningInfo.abResultTemporary == 0x13 ||
                     storedInningInfo.abResultTemporary == 0x1A)) {
                    reason = 7;
                } else if (cam->_A98 > 0 && storedInningInfo.abResultTemporary >= 0x14 &&
                           storedInningInfo.abResultTemporary <= 0x1B) {
                    reason = 8;
                }
                }
                count2 = 0;
                if (g_Runners[2].rosterID != -1) {
                    count2 = 1;
                }
                if (g_Runners[3].rosterID != -1) {
                    count2++;
                }
                if (g_Scores._A6 <= count2 && count2 > 0) {
                    if (cam->_A98 > 0 &&
                    (storedInningInfo.abResultTemporary == 0x12 || storedInningInfo.abResultTemporary == 0x13 ||
                     storedInningInfo.abResultTemporary == 0x1A)) {
                    reason = 7;
                } else if (cam->_A98 > 0 && storedInningInfo.abResultTemporary >= 0x14 &&
                           storedInningInfo.abResultTemporary <= 0x1B) {
                    reason = 8;
                }
                }
            }
        }
        result = storedInningInfo.abResultTemporary;
        if (result >= 0x24 && result <= 0x26 && cam->_A50 == 2) {
            if (g_GameLogic.EventTriggers_EndOfGame) {
                reason = 6;
            } else {
                count = 0;
                if (g_Runners[1].rosterID != -1) {
                    count = 1;
                }
                if (g_Runners[2].rosterID != -1) {
                    count++;
                }
                if (g_Runners[3].rosterID != -1) {
                    count++;
                }
                if (g_Scores._A6 <= 4 && count == 3) {
                    reason = 6;
                }
                count2 = 0;
                if (g_Runners[2].rosterID != -1) {
                    count2 = 1;
                }
                if (g_Runners[3].rosterID != -1) {
                    count2++;
                }
                if (g_Scores._A6 <= count2 && count2 > 0) {
                    reason = 6;
                }
            }
        }
    }

    if (reason == 0) {
        return;
    }
    switch (reason) {
    case 2:
    case 9:
        g_Stats.replayReason = 2;
        break;
    case 13:
        g_Stats.replayReason = 0xD;
        break;
    case 3:
    case 10:
        g_Stats.replayReason = 3;
        break;
    case 4:
        g_Stats.replayReason = 4;
        break;
    case 5:
        g_Stats.replayReason = 5;
        break;
    case 6:
        g_Stats.replayReason = 6;
        break;
    case 7:
        g_Stats.replayReason = 7;
        break;
    case 8:
        g_Stats.replayReason = 1;
        g_Stats.replayArg = 0;
        break;
    case 11:
        g_Stats.replayReason = 0xB;
        break;
    default:
        g_Stats.replayReason = 1;
        g_Stats.replayArg = arg;
        break;
    }
    g_Stats.replayPending = 1;
}
