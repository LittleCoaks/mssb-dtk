#define SQRT2_LINKAGE static
#include "game/match_setup/replay_state.h"
#include "game/match_setup/replay_inputs.h"
#include "game/match_setup/stat_tracking.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/camera/camera.h"
#include "game/stadium/stadium_framework.h"
#include "Unknown/File_0x8001b2d0.h"
#include "Unknown/File_0x800204cc.h"
#include "Dolphin/stl.h"

extern void SetGameStatus(int status);
extern BOOL checkForButtonPressToSkip(int a, int b);

extern u8 us80893314[];
extern u8 us80893310[];
extern u8 lbl_3_common_bss_32220[];
extern u8 g_UnkThrowing_31ACC[];
extern u8 g_UnkAnimation_31EAC[];
extern u8 lbl_3_common_bss_321A0[];
extern u8 lbl_8037169C[];

typedef struct {
    u8 _00[0x68];
    s16 _68;
} ReplayCameraTarget;

typedef struct {
    u8 _0000[0x2C74];
    ReplayCameraTarget* _2C74;
} ReplayAnimView;
extern ReplayAnimView hugeAnimStruct;

#define STATS_AT(off) ((void*)((u8*)&g_Stats + (off)))

// .text:0x0007CE90 size:0xF8 mapped:0x806BBF24
void lastPlayStats(void) {
    if (g_Stats.atBatPitchThrown == 0) {
        return;
    }
    g_Stats._0028 = g_Stats.playFrameCounter;
    g_Stats.atBatPitchThrown = 0;
    g_Stats.homeTeamScore = g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total;
    g_Stats._002C = g_Scores._A0;
    g_Stats._002E = g_Scores._C2;
    g_Stats.awayTeamScore = g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total;
    if (g_Ball.deadBallReason == DEAD_BALL_REASON_HOME_RUN) {
        g_Stats._002E = g_RunningLogic.nOffensivePlayersAtStartOfPlay;
        g_Stats.homeTeamScore = g_Scores._A0 + g_RunningLogic.nOffensivePlayersAtStartOfPlay;
    }
    g_Stats.hitVerticalAngle = g_Ball.Hit_VerticalAngle;
    g_Stats.hitHorizontalAngle = g_Ball.Hit_HorizontalAngle;
    g_Stats.hitHorizontalPower = g_Ball.Hit_HorizontalPower;
    g_Stats.landingSpotLocation.x = g_Ball.landingSpotLocation.x;
    g_Stats.landingSpotLocation.z = g_Ball.landingSpotLocation.z;
    g_Stats.ballPickedUpCaught.x = g_Ball.ballPickedUpCaught.x;
    g_Stats.ballPickedUpCaught.z = g_Ball.ballPickedUpCaught.z;
    g_Stats.deadballLastLoc.x = g_Ball.deadballLastLoc.x;
    g_Stats.deadballLastLoc.y = g_Ball.deadballLastLoc.y;
    g_Stats.deadballLastLoc.z = g_Ball.deadballLastLoc.z;
}

// .text:0x0007CF88 size:0x358 mapped:0x806BC01C
void initializeReplayState(void) {
    memcpy(STATS_AT(0x44), &g_GameLogic, sizeof(g_GameLogic));
    memcpy(STATS_AT(0x19C), &g_Strikes, sizeof(g_Strikes));
    memcpy(STATS_AT(0x1C0), &g_Scores, sizeof(g_Scores));
    memcpy(STATS_AT(0x288), &g_Ball, sizeof(g_Ball));
    memcpy(STATS_AT(0x1E80), &g_Pitcher, sizeof(g_Pitcher));
    memcpy(STATS_AT(0x1FF8), &g_Batter, sizeof(g_Batter));
    memcpy(STATS_AT(0x20A8), &g_AiLogic, sizeof(g_AiLogic));
    memcpy(STATS_AT(0x2164), &g_FieldingLogic, sizeof(g_FieldingLogic));
    memcpy(STATS_AT(0x22B4), &g_RunningLogic, sizeof(g_RunningLogic));
    memcpy(STATS_AT(0x22D4), g_Fielders, sizeof(g_Fielders));
    memcpy(STATS_AT(0x387C), g_Runners, sizeof(g_Runners));
    memcpy(STATS_AT(0x416C), BatterStats_P1_P2, sizeof(BatterStats_P1_P2));
    memcpy(STATS_AT(0x4418), PitcherStats_P1_P2, sizeof(PitcherStats_P1_P2));
    memcpy(STATS_AT(0x3DCC), us80893314, 6);
    memcpy(STATS_AT(0x3DD2), us80893310, 4);
    memcpy(STATS_AT(0x3DD6), lbl_3_common_bss_32220, 0xE);
    memcpy(STATS_AT(0x3DE4), g_UnkThrowing_31ACC, 0x14);
    memcpy(STATS_AT(0x3DF8), g_UnkAnimation_31EAC, 0x2F4);
    memcpy(STATS_AT(0x40EC), lbl_3_common_bss_321A0, 0x80);
    g_Stats.playFrameCounter = 0;
    g_Stats.atBatPitchThrown = 1;
    g_Stats.replayPending = 0;
    g_Stats._003B = 0;
    g_Stats.replayReason = 0;
    g_Stats.replayArg = 0;
    g_Stats._003E = 1;
    g_Stats._003A = 0;
    g_Stats.prevAtBatResult = 0;
    g_Stats.replayPort[0] = g_GameLogic.teams[0];
    g_Stats.replayPort[1] = g_GameLogic.teams[1];
    fn_3_7D2E0();
    copyAnimationStructures();
    if (hugeAnimStruct._2C74 != NULL) {
        g_Stats._0034 = hugeAnimStruct._2C74->_68;
    }
    updateStadiumObjCollision();
    resetSomeStruct();
}

static inline void recordReplayPad(ReplayPadFrame* dst, int port) {
    InputStruct* in = &g_Controls[port];
    dst->controlStickAngle = in->controlStickAngle;
    dst->buttonInput = in->buttonInput & 0xEFFF;
    dst->newButtonInput = in->newButtonInput & 0xEFFF;
    dst->right_left = in->right_left;
    dst->up_down = in->up_down;
}

// .text:0x0007D2E0 size:0xBC mapped:0x806BC374
void fn_3_7D2E0(void) {
    int frame = g_Stats.playFrameCounter;

    if (frame >= REPLAY_MAX_FRAMES) {
        g_Stats._0028 = REPLAY_MAX_FRAMES - 1;
        return;
    }
    recordReplayPad(&g_ReplayLogic[frame].pad[0], g_Stats.replayPort[0]);
    recordReplayPad(&g_ReplayLogic[frame].pad[1], g_Stats.replayPort[1]);
    g_Stats.playFrameCounter = frame + 1;
}

// .text:0x0007D39C size:0xBC mapped:0x806BC430
void fn_3_7D39C(void) {
    int frame = g_Stats.playFrameCounter;

    if (frame >= REPLAY_MAX_FRAMES) {
        g_Stats._0028 = REPLAY_MAX_FRAMES - 1;
        return;
    }
    recordReplayPad(&g_ReplayLogic[frame].pad[0], g_Stats.replayPort[0]);
    recordReplayPad(&g_ReplayLogic[frame].pad[1], g_Stats.replayPort[1]);
    g_Stats.playFrameCounter = frame + 1;
}

// .text:0x0007D458 size:0x328 mapped:0x806BC4EC
void ReplayRelatedCopying_storeDataBeforePlay(void) {
    GameInitVariables* settings = &g_d_GameSettings;
    g_Stats_s* stats = &g_Stats;

    if (stats->replayInd != 0) {
        if ((int)stats->playFrameCounter == 9) {
            changeScene(1, 6);
        }
        if ((int)stats->playFrameCounter + 1 >= stats->_0028 && stats->_003A != 0) {
            stats->_003A = 2;
            stats->replayPending = 0xFF;
            CopyMoreStructs(0);
            stats->replayPending = 3;
            changeScene(1, 6);
            return;
        }
        if (stats->replayPending == 4) {
            if (lbl_8037169C[0x13] != 0) {
                stats->replayPending = 0;
                replaceGameStructs_postReplay(1);
            }
        } else if (stats->replayPending == 5) {
            stats->playFrameCounter = stats->_0028 - 7;
            stats->replayPending = 0;
            changeScene(3, 6);
        } else {
            BOOL skip;
            if ((int)g_Stats.playFrameCounter < 0x5A) {
                skip = FALSE;
            } else if ((int)g_Stats.playFrameCounter > g_Stats._0028 - 0x3C) {
                skip = FALSE;
            } else if (checkForButtonPressToSkip(1, 0x1100) != 0) {
                skip = TRUE;
            } else {
                skip = FALSE;
            }
            if (skip && settings->GameModeSelected != GAME_TYPE_DEMO) {
                stats->replayPending = 4;
                changeScene(3, 6);
            }
        }
        useReplayInputs();
        if (stats->replayInd == 0) {
            if (stats->replayReason == 2 || stats->replayReason == 0xD) {
                SetGameStatus(0x13);
            } else if (stats->replayReason == 4 || (stats->replayReason == 1 && stats->replayArg == 4)) {
                SetGameStatus(0x15);
            }
        }
    } else if (stats->atBatPitchThrown != 0) {
        fn_3_7D39C();
        fn_3_7C190();
    } else if (stats->replayPending == 2) {
        CopyMoreStructs(0);
        changeScene(1, 6);
        stats->replayPending = 3;
        fn_3_15D64();
    } else if (stats->_0038[0] == 1) {
        initializeReplayState();
        stats->_0038[0] = 2;
    }
    if (g_pCamera->_AC5 != 0) {
        fn_3_15D7C(0);
        fn_3_15D64();
        if (stats->replayReason != 0xC && stats->replayReason != 1) {
            fn_3_15D28();
        }
    }
}

// .text:0x0007D780 size:0x1C mapped:0x806BC814
void initializeReplayVariables(void) {
    g_Stats.replayInd = 0;
    g_Stats.atBatPitchThrown = 0;
    g_Stats._0038[0] = 0;
}
