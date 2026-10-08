#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_minigameFramework
#include "game/minigame/minigame_framework.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/character_stats.h"
#include "game/math/game_math.h"
#include "game/match_setup/pause_menu.h"
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
#include "game/minigame/minigame_models.h"
#include "game/minigame/minigame_effects.h"
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
#include "Unknown/File_0x8004e5b4.h"
#include "Unknown/File_0x800203e0.h"
#include "Unknown/File_0x80035838.h"
#include "Unknown/File_0x80034220.h"
#include "Unknown/File_0x8003452c.h"
#include "Unknown/File_0x8003a538.h"
#include "Unknown/File_0x80052f98.h"
#include "Unknown/File_0x800506e8.h"
#include "Unknown/File_0x80062a50.h"
#include "Unknown/File_0x80062a94.h"
#include "Unknown/File_0x800628d4.h"
#include "Unknown/File_0x800a70dc.h"
#include "Unknown/File_0x800a7568.h"
#include "game/math/rep_3090.h"
#include "Unknown/File_0x800acf14.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/sub.h"

#define SATURATING_INCREMENT(counter) \
    if ((counter) < 0x7FFE) {         \
        (counter)++;                  \
    } else {                          \
        (counter) = 0x7FFF;           \
    }

#define CHAR_SELECT_BYTE(off) (((s8*)&charSelectStruct)[off])
#define CHAR_SELECT_UBYTE(off) (((u8*)&charSelectStruct)[off])
#define SATURATING_INCREMENT_U16(counter) \
    if ((counter) < 0xFFFE) {             \
        (counter)++;                      \
    } else {                              \
        (counter) = 0xFFFF;               \
    }

#define CAMSCRIPT_G(i) (*(CamScript*)((u8*)&g_Camera + 0x120 + (i) * 0x9BC))

extern u8 animRelated[0x124];
extern u8 superstarUnlocked[0x130];
extern int fn_8004FDE8(int, int);
extern int fn_8004FD64(int);
extern struct {
    u8 _00[3];
    u8 state;
} lbl_803C5F74;
extern void fn_8004CC18(void);
extern void set803c5f77(void);
extern void fn_8004CC4C(int, int, int, int, int);
extern void fn_8004D0F0(void);
extern u8 cameraDataFileDescriptor[];
extern s16 challenge_baseCoinsAwarded[];
extern void starMissionsMinigamesTotalPoints(void);
extern u8 hugeAnimStruct[0x3154];
extern u8 lbl_8037169C[0x1C];
extern SuperstarStatBonus stonNiceContactIncrement;
extern u8 lbl_800E854C[];
extern u8 challenge_minigames_opponentCharIDs[];
extern void cssLoadingRelated_1(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
extern s32 cssCursorOnBottomControl_maybe(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void css_initValues(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void fn_8004FDA0(int);
extern void fn_80011B64(int);
extern int fn_80016710(s8 charID, int arg1);
extern u8 lbl_80366158[0x30];
extern u8 lbl_800EFBA4[0x10];
extern u8 FrameCountOfEntireGame[];
extern u8 mapping_minigame_Stadium[8];
extern u8 minigameChallengeOpponentCounts[8];
extern u8 minigameChallengeOpponentPools[44];
extern u8 minigameChallengeAIStrength[8];
extern void manageStadiumLoading(void);
extern s16 minigameTuningConstants[10];
extern u8 lbl_3_data_18918[8];
extern u8 minigamePauseMenuActions[20];
extern u8 challengeTransitionPortraitIDs[];
extern u8 postMinigameMenuActions[16];
extern u8 minigameParticipantCounts[36];
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern int fn_80016F7C(void);
extern int fn_3_90DD8(void);
extern s8 minigameHelpPageIDs[8][3][5];
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
extern void minigameReadySwitcher(void);
extern void minigameResultsSwitcher(void);
extern void postMinigame(void);
extern void minigames_0x26(void);
extern void minigames_0x27(void);
extern void minigames_0x28(void);
extern void minigames_setupChallengeRoster(void);
extern void minigames_pickOpponentsAndLoadStats(void);

extern MinigameResultEntry lbl_803616CC[][5];
extern s16 lbl_80109410[];
extern void fn_8006C398(MiniGrandPrixScoreInput* input);
extern int fn_8006C13C(MiniGrandPrixScoreInput* input);

u8 minigameSelectMenuGameIDs[8] = { 1, 2, 4, 5, 3, 6, 7, 0 };
u8 lbl_3_data_21270[8] = { 1, 4, 1, 4, 0, 3, 1, 0 };
u8 minigameIntroFrames[2] = { 30, 60 };
u8 minigameAIStrengthTable[8][5] = {
    { 0, 1, 2, 3, 0 },
    { 0, 1, 2, 2, 0 },
    { 0, 1, 2, 2, 0 },
    { 0, 1, 2, 2, 0 },
    { 0, 1, 2, 2, 0 },
    { 0, 1, 2, 2, 0 },
    { 0, 1, 2, 2, 0 },
    { 2, 2, 2, 2, 0 },
};
u8 minigame_exhibitionOpponentCharIDs[104] = {
    0, 1, 4, 5, 2, 3, 13, 12,
    17, 21, 24, 28, 6, 5, 7, 8,
    38, 11, 0, 1, 2, 4, 9, 10,
    0, 1, 2, 4, 9, 10, 41, 0,
    5, 14, 10, 27, 20, 15, 3, 1,
    48, 11, 7, 8, 13, 6, 18, 39,
    7, 8, 13, 6, 18, 39, 17, 16,
    8, 19, 28, 40, 6, 38, 21, 14,
    7, 5, 0, 1, 2, 4, 9, 10,
    0, 1, 2, 4, 9, 10, 40, 17,
    16, 14, 3, 10, 12, 37, 27, 20,
    33, 11, 41, 2, 38, 9, 19, 48,
    41, 2, 38, 9, 19, 48, 0, 0,
};
f32 resultsFielderMinigameOffsets[7][4] = {
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
};
s16 minigameResultsFrames[2] = { 120, 60 };
f32 bOD_bB_pitchBallPos[3] = { 0.0f, 1.6f, 18.0f };
f32 bOD_bB_maxMovement[4] = { 0.005f, 0.005f, 0.005f, 0.005f };
u8 minigamePitchSpeeds_base[8] = { 120, 140, 160, 170, 190, 0, 0, 0 };
u8 bOD_pitchSpeedWeights[48] = {
    0, 100, 0, 0, 0, 0, 50, 50,
    0, 0, 0, 40, 0, 60, 0, 0,
    30, 10, 20, 40, 10, 20, 0, 20,
    50, 0, 0, 0, 65, 0, 0, 10,
    25, 30, 40, 0, 15, 15, 20, 20,
    20, 20, 20, 0, 0, 0, 50, 50,
};
u8 soloBODPitchSelectionType[8] = { 0, 0, 1, 2, 2, 3, 0, 0 };
u8 bOD_multiPitchSelectionTypes[4] = { 0, 2, 4, 0 };
u8 bOD_fireworkTimerRanges[4] = { 25, 55, 15, 30 };
u8 bOD_multiInningsAndPitches[8] = { 3, 3, 3, 3, 3, 3, 0, 0 };
s16 bOD_scoreConsts[10] = {
    50, 60, 70, 80, 90, 100, 25, 200,
    15, 0,
};
s16 bOD_challenge_nPitches_Points[4][2] = {
    { 10, 1000 },
    { 10, 1500 },
    { 10, 2000 },
    { 10, 0 },
};
s16 bODPowerThresholdsForVertAngles[6] = { 250, 260, 270, 280, 300, 0 };
s16 bOD_hitVertAngleRanges[14] = {
    0, 150, 270, 290, 280, 300, 290, 320,
    310, 340, 330, 360, 350, 380,
};
f32 bOD_ballConsts[4] = { 0.001f, 1.7e+02f, 1.5f, 1.3e+02f };
s16 bOD_frameConsts[10] = {
    90, 30, 160, 90, 90, 128, 64, 10,
    30, 90,
};
u16 lbl_3_data_2145C[2] = { 20, 70 };
u8 bOD_bB_pitchRouletteTypes[8] = { 0, 1, 2, 4, 3, 5, 3, 0 };
u8 bOD_bB_pitchRouletteWeights[24] = {
    60, 30, 10, 0, 0, 0, 30, 40,
    10, 0, 10, 10, 20, 20, 20, 0,
    20, 20, 15, 10, 10, 0, 25, 40,
};
u8 bOD_bB_pitchRouletteWeightsDefault[8] = { 20, 20, 20, 0, 20, 20, 0, 0 };
u8 bOD_aiBaseWeights[8][3] = {
    { 0, 100, 0 },
    { 0, 100, 0 },
    { 0, 100, 0 },
    { 0, 100, 0 },
    { 0, 100, 0 },
    { 0, 100, 0 },
    { 0, 100, 0 },
    { 0, 100, 0 },
};
s8 bOD_aiTimingOffsetRanges[4][6] = {
    { 0, 0, -6, 4, 0, 0 },
    { 0, 0, -4, 3, 0, 0 },
    { 0, 0, -3, 2, 0, 0 },
    { 0, 0, -3, 1, 0, 0 },
};
s8 bOD_aiChargeWeightsPerStreak[4][3] = {
    { 15, -10, 10 },
    { 10, -10, 10 },
    { 5, -10, 5 },
    { 5, -10, 5 },
};
s8 bOD_aiTimingWeightsPerStreak[4][3] = {
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
};
s8 bOD_aiChargeWeightsKingBomb[4][3] = {
    { 22, -20, 20 },
    { 15, -20, 20 },
    { 10, -20, 10 },
    { 5, -20, 10 },
};
s8 bOD_aiTimingWeightsKingBomb[4][3] = {
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
};
s8 bOD_aiChargeWeightsRandomPitch[4][3] = {
    { 35, -30, 30 },
    { 30, -30, 30 },
    { 20, -30, 20 },
    { 15, -30, 20 },
};
s8 bOD_aiTimingWeightsRandomPitch[4][3] = {
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
};
f32 wallBall_pitcherWaitingOffsets[8] = { 0.0f, 0.0f, -5.0f, 25.0f, 5.0f, 25.0f, 1e+01f, 25.0f };
f32 wallBall_wallPosTable[42] = {
    0.0f, 0.0f, 10.2f, 0.0f, 0.0f, 8.5f, 0.0f, 0.0f,
    6.8f, 0.0f, 0.0f, 5.1f, 0.0f, 0.0f, 3.4f, 0.0f,
    0.0f, 1.7f, 0.0f, 0.0f, 0.0f, 0.0f, 2e+01f, 0.0f,
    0.0f, 23.0f, 0.0f, 0.0f, 26.0f, 0.0f, 0.0f, 29.0f,
    0.0f, 0.0f, 32.0f, 0.0f, 0.0f, 35.0f, 0.0f, 0.0f,
    38.0f, 0.0f,
};
f32 wallBall_wallStateOffsets[6] = { 0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.2f };
f32 wallBall_coinSpawnPositions[21] = {
    0.0f, 1.5f, 10.2f, 0.0f, 1.5f, 8.5f, 0.0f, 1.5f,
    6.8f, 0.0f, 1.5f, 5.1f, 0.0f, 1.5f, 3.4f, 0.0f,
    1.5f, 1.7f, 0.0f, 1.5f, 0.0f,
};
f32 wallBall_coinPhysicsConsts[5] = { 0.2f, 0.1f, 0.0044f, 0.5f, 0.3f };
u32 wallBall_nCoinsToGenerate[3] = { 0x1, 0x2, 0x5 };
s16 wallBall_pitchPowerAndCoinTable[12] = {
    30, 123, 150, 10, 17, 22, 17, 5,
    10, 15, 100, 50,
};
u8 wallBall_inningLimits[5] = { 3, 3, 3, 3, 3 };
u8 wallBall_inningLimitThreshold = 3;
s16 wallBall_lastInningMultiplier = 1;
f32 wallBall_wallBounceConsts[2] = { 0.1f, 0.1f };
s16 wallBall_frameConsts[6] = { 90, 60, 90, 30, 60, 0 };
f32 wallBall_wallMotionConsts[3] = { 0.1f, 0.3f, 1.0f };
s8 wallBall_aiOffsetChance[4][7] = {
    { 90, 95, 100, 100, 100, 100, 80 },
    { 75, 80, 85, 85, 85, 90, 65 },
    { 55, 60, 65, 65, 65, 70, 40 },
    { 55, 60, 65, 65, 65, 70, 40 },
};
s8 wallBall_aiOffsetRange[4][2] = {
    { -40, 40 },
    { -30, 30 },
    { -20, 20 },
    { -15, 15 },
};
s8 wallBall_aiPerfectMissChance[4] = { 80, 60, 40, 30 };
f32 barrelBaseCoordinates[45] = {
    -8.4f, 0.0f, 25.0f, -8.4f, 4.5f, 25.0f, -8.4f, 9.0f,
    25.0f, -4.2f, 0.0f, 25.0f, -4.2f, 4.5f, 25.0f, -4.2f,
    9.0f, 25.0f, 0.0f, 0.0f, 25.0f, 0.0f, 4.5f, 25.0f,
    0.0f, 9.0f, 25.0f, 4.2f, 0.0f, 25.0f, 4.2f, 4.5f,
    25.0f, 4.2f, 9.0f, 25.0f, 8.4f, 0.0f, 25.0f, 8.4f,
    4.5f, 25.0f, 8.4f, 9.0f, 25.0f,
};
f32 bB_barrelConsts[6] = { 2e+01f, -1.0f, 2.1f, 4.5f, 0.2f, 0.1f };
s16 bB_dropConsts[4] = { 3, 5, 10, 0 };
s16 bB_challengePointsRequired[4] = { 1000, 1500, 2000, 0 };
u8 cost_15_bB_pitchesPerRound_solo[12] = {
    15, 15, 15, 15, 5, 3, 3, 0,
    63, 0, 0, 0,
};
s16 bOD_bB_frameConsts[12] = {
    20, 30, 80, 180, 45, 4, 20, 30,
    120, 130, 90, 0,
};
s8 bBAI_swingFrameOffsetByRow[8] = { 1, 0, -1, -3, -4, 0, 0, 0 };
u8 bBAI_canPreferFewestBarrels[4] = { 1, 1, 1, 1 };
s8 bBAI_chanceToPreferFewestBarrels[4] = { 15, 20, 30, 50 };
s8 bBAI_chanceToMissTimeSwing[4] = { 70, 55, 45, 30 };
s8 bBAI_framesMistimedBy[4] = { 3, 2, 2, 1 };
s8 bBAI_chanceToOverrideVertAngleToMiddleRow[4] = { 30, 25, 15, 15 };
f32 ccs_resultsRunnerOffsets[4][2] = {
    { 1.5f, 0.0f },
    { 0.5f, 0.0f },
    { -0.5f, 0.0f },
    { -1.5f, 0.0f },
};
f32 ccs_chompStartPos[3] = { 0.0f, 0.0f, 18.5f };
s16 ccs_chompJumpRollWeights[46] = {
    50, 90, 110, 150, 150, 150, 150, 150,
    -1, 70, 110, 120, 140, 140, 140, 140,
    140, -1, 100, 100, 100, 140, 140, 140,
    140, 140, -1, 100, 100, 100, 140, 140,
    140, 140, 140, -1, 100, 100, 100, 140,
    140, 140, 140, 140, -1, 0,
};
u8 lbl_3_data_21860[5][4] = {
    { 0, 1, 2, 3 },
    { 0, 1, 2, 3 },
    { 0, 1, 2, 3 },
    { 0, 1, 2, 3 },
    { 0, 1, 2, 3 },
};
u8 ccs_timeLimitSeconds[8] = { 60, 60, 60, 90, 60, 0, 0, 0 };
u8 ccs_itemWeightsByPhase[4][2] = {
    { 95, 5 },
    { 90, 10 },
    { 80, 20 },
    { 0, 0 },
};
u8 ccs_itemGemCounts[8] = { 1, 1, 5, 1, 1, 10, 0, 0 };
f32 ccs_coinPhysicsConsts[7] = { 0.1f, 0.3f, 0.1f, 0.3f, -0.01f, 0.7f, 0.5f };
s16 ccs_coinLifetimeFrames = 120;
u8 ccs_chompTargetThresholds[16] = {
    180, 160, 150, 160, 140, 140, 130, 110,
    100, 130, 120, 110, 150, 130, 110, 0,
};
f32 lbl_3_data_218BC[18] = {
    4.0f, 0.3f, 0.07f, 0.3f, 0.2f, 0.2f, 0.04f, 0.5f,
    0.05f, 0.05f, 0.1f, 0.1f, 15.0f, 3e+01f, 0.1f, 0.2f,
    0.04f, 1.8f,
};
s16 lbl_3_data_21904[12] = {
    90, 120, 60, 90, 180, 10, 20, 30,
    50, 120, 10, 0,
};
f32 lbl_3_data_2191C[2] = { 0.85f, 2.0f };
s16 ccs_powerupTimers[4] = { 545, 300, 180, 0 };
s8 ccsAI_bPressDelayRanges[4][2] = {
    { 30, 40 },
    { 10, 20 },
    { 5, 10 },
    { 5, 10 },
};
f32 ccsAI_targetDistThresholds[4] = { 0.7f, 0.6f, 0.5f, 0.4f };
s8 lbl_3_data_21944[4][2] = {
    { 30, 40 },
    { 20, 30 },
    { 15, 20 },
    { 10, 15 },
};
s16 lbl_3_data_2194C[4][2] = {
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
};
s16 lbl_3_data_2195C[4][2] = {
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
};
s8 lbl_3_data_2196C[4][2] = {
    { 70, 80 },
    { 50, 60 },
    { 20, 30 },
    { 10, 20 },
};
s8 lbl_3_data_21974[4][2] = {
    { 80, 90 },
    { 60, 70 },
    { 30, 40 },
    { 20, 30 },
};
s8 lbl_3_data_2197C[4] = { 10, 20, 30, 30 };
s8 lbl_3_data_21980[4] = { 4, 5, 6, 7 };
u8 sD_timeLimitSeconds[8] = { 60, 60, 60, 90, 60, 0, 0, 0 };
f32 sD_fielderStartPositions[8] = { 0.0f, 1e+01f, -1e+01f, 2e+01f, 1e+01f, 2e+01f, 0.0f, 3e+01f };
f32 sD_starSpawnPos[3] = { 0.0f, 4.0f, 2e+01f };
f32 lbl_3_data_219B8[19] = {
    0.28f, 0.3f, 0.05f, 0.18f, 0.03f, 0.25f, 0.55f, 0.5f,
    0.5f, 0.05f, 0.15f, -0.01f, 0.5f, 0.5f, 0.45f, 0.3f,
    0.05f, 0.08f, 0.25f,
};
s16 lbl_3_data_21A04[8] = { 15, 30, 1, 420, 128, 1, 10, 10 };
f32 lbl_3_data_21A14[7] = { 14.0f, 15.0f, 1e+01f, 13.0f, 1.4f, 1.5f, 1.05f };
s16 sD_starTimings[6] = { 480, 420, 600, 90, 100, 10 };
s16 sD_fireBarWaveTimes[2][2] = {
    { 500, 505 },
    { -1, -1 },
};
s16 sD_fireBarAngleStep = 2;
f32 lbl_3_data_21A48[3] = { 0.0f, 0.5f, 2e+01f };
f32 sD_fireBarRadii[3] = { 2.0f, 13.0f, 0.4f };
s16 sD_fireBarGrowParams[2] = { 60, 10 };
f32 lbl_3_data_21A64[9] = {
    3e+01f, 1.5f, 0.4f, 0.7f, 5e+01f, 0.5f, 6e+01f, 1.2e+02f,
    3e+02f,
};
s16 sD_thwompSectorDivisors[4] = { 2, 3, 4, 4 };
s16 sD_thwompTimingRanges[4][4][2] = {
    {
        { 3, 5 },
        { 3, 5 },
        { 2, 5 },
        { 2, 5 },
},
    {
        { 3, 5 },
        { 2, 5 },
        { 2, 4 },
        { 2, 4 },
},
    {
        { 3, 5 },
        { 2, 4 },
        { 1, 3 },
        { 1, 3 },
},
    {
        { 3, 5 },
        { 2, 4 },
        { 1, 3 },
        { 1, 3 },
},
};
s16 lbl_3_data_21AD0[4][4] = {
    { 4, 4, 3, 3 },
    { 4, 3, 2, 2 },
    { 4, 3, 2, 1 },
    { 4, 3, 2, 1 },
};
s16 sD_cameraShakeDuration = 20;
f32 sD_cameraShakeAmplitude = 0.2f;
f32 sD_powerupConsts[6] = { 0.3f, 0.15f, -0.01f, 0.85f, 1.5f, 0.5f };
s16 sD_powerupTimers[3] = { 60, 300, 300 };
u8 sD_powerupRollThreshold = 80;
f32 sD_stunPushFactors[2] = { 0.1f, 0.95f };
s16 lbl_3_data_21B20[4] = { 90, 120, 180, 10 };
f32 sD_aiSprintThresholds[4] = { 1.0f, 1.2f, 1.3f, 1.3f };
f32 sD_aiHolderChaseRadii[4] = { 3.0f, 4.0f, 5.0f, 6.0f };
f32 sD_aiThwompAvoidRadii[4] = { 2.0f, 3.0f, 5.0f, 6.0f };
f32 sD_aiPowerup2Radii[4] = { 2.0f, 3.0f, 4.0f, 5.0f };
f32 sD_aiPowerup1Radii[4] = { 3.0f, 4.0f, 6.0f, 7.0f };
f32 sD_aiCoinBagRadii[4] = { 3.0f, 4.0f, 6.0f, 7.0f };
s8 sD_aiFireBarWideAvoidChance[4] = { 30, 20, 10, 5 };
s16 sD_aiTurnDivisors[4] = { 15, 10, 9, 8 };
f32 pP_fielderStartPositions[12] = {
    -7.5f, 0.0f, 0.0f, -2.5f, 0.0f, 0.0f, 2.5f, 0.0f,
    0.0f, 7.5f, 0.0f, 0.0f,
};
f32 pP_spawnerPositions[86] = {
    14.0f, 0.0f, 18.0f, 14.0f, 6.0f, 18.0f, 1e+01f, 5.0f,
    15.0f, 14.0f, 7.0f, 18.0f, 0.0f, 0.0f, 3e+01f, 0.0f,
    6.0f, 3e+01f, 0.0f, 5.0f, 25.0f, 0.0f, 7.0f, 3e+01f,
    -14.0f, 0.0f, 18.0f, -14.0f, 6.0f, 18.0f, -1e+01f, 5.0f,
    15.0f, -14.0f, 7.0f, 18.0f, 14.0f, 0.0f, 18.0f, 14.0f,
    6.5f, 18.0f, 13.5f, 7.5f, 17.5f, 14.0f, 1e+01f, 18.0f,
    0.0f, 0.0f, 3e+01f, 0.0f, 6.5f, 3e+01f, 0.0f, 7.5f,
    25.0f, 0.0f, 1e+01f, 3e+01f, -14.0f, 0.0f, 18.0f, -14.0f,
    6.5f, 18.0f, -13.5f, 7.5f, 17.5f, -14.0f, 1e+01f, 18.0f,
    0.0f, 0.0f, -1e+01f, 0.0f, 0.0f, -1e+01f, 0.0f, 0.0f,
    -1e+01f, 0.0f, 0.0f, -1e+01f, 1.5f, 1.75f,
};
f32 pP_spawnerYRanges[4] = { 0.35f, 1.0f, 0.35f, 1.0f };
f32 lbl_3_data_21D2C[2] = { 0.0f, 1.0f };
f32 pP_goalBallPositions[36] = {
    -7.5f, 1.0f, -2.0f, -7.5f, 0.5f, -4.0f, -7.5f, 0.0f,
    -6.0f, -2.5f, 1.0f, -2.0f, -2.5f, 0.5f, -4.0f, -2.5f,
    0.0f, -6.0f, 2.5f, 1.0f, -2.0f, 2.5f, 0.5f, -4.0f,
    2.5f, 0.0f, -6.0f, 7.5f, 1.0f, -2.0f, 7.5f, 0.5f,
    -4.0f, 7.5f, 0.0f, -6.0f,
};
s16 pP_spawnDelayRange[2] = { 30, 45 };
s16 lbl_3_data_21DC8[5][6] = {
    { 20, 30, 20, 50, 60, 50 },
    { 20, 30, 20, 50, 60, 50 },
    { 20, 30, 20, 50, 60, 50 },
    { 40, 60, 40, 70, 90, 70 },
    { 20, 30, 20, 50, 60, 50 },
};
s16 lbl_3_data_21E04[2] = { 180, 240 };
u8 pP_timeLimitSeconds[8] = { 60, 60, 60, 90, 60, 0, 0, 0 };
u8 pP_hitsRequiredByKind[8] = { 5, 5, 5, 5, 30, 40, 0, 0 };
u8 lbl_3_data_21E18[4] = { 1, 1, 2, 2 };
u8 pP_throwFramesRange[2] = { 45, 30 };
u8 lbl_3_data_21E20[3] = { 70, 20, 10 };
f32 pP_ballPhysicsConsts[17] = {
    0.5f, 2.0f, 0.25f, 1.0f, 0.75f, 1.0f, 0.75f, 1.0f,
    0.3f, 0.3f, 0.2f, -0.01f, 0.99f, 0.75f, 1.0f, 3.0f,
    0.01f,
};
s16 lbl_3_data_21E68[26] = {
    90, 10, 30, 15, 5, 30, 30, 30,
    40, 15, 180, 30, 115, 15, 30, 60,
    10, 90, 30, 0, 150, 50, 80, 60,
    3, 0,
};
u8 pP_aiActionWeights[4][4] = {
    { 0, 10, 20, 70 },
    { 15, 15, 30, 40 },
    { 40, 20, 20, 20 },
    { 50, 20, 20, 20 },
};
s16 pP_aiActionDelayRanges[4][2] = {
    { 30, 60 },
    { 20, 35 },
    { 8, 15 },
    { 8, 15 },
};
s8 lbl_3_data_21EBC[4] = { 70, 40, 20, 15 };
s8 lbl_3_data_21EC0[4] = { 30, 50, 70, 85 };
u8 minigameGrandPrixRankPoints[4] = { 10, 6, 3, 0 };
u32 CommonUIFiles_minigame[62][4] = {
    { 0x40B, 0x4013764C, 0x1A635000, 0x7DB48 },
    { 0x40B, 0x4003E3DC, 0x1A6B3000, 0x21420 },
    { 0x40B, 0x4002EC10, 0x1A6D4800, 0x13108 },
    { 0x40B, 0x400E72C0, 0x1A6E8000, 0x60768 },
    { 0x40B, 0x40049404, 0x1A748800, 0x20E34 },
    { 0x40B, 0x40076AE0, 0x18ED7000, 0x36BC8 },
    { 0x40B, 0x4010FD70, 0x1A769800, 0x5E284 },
    { 0x40B, 0x400DB738, 0x1A7C8000, 0x49AB4 },
    { 0x40B, 0x400E9864, 0x1A812000, 0x59DC0 },
    { 0x40B, 0x400B7718, 0x1A86C000, 0x50288 },
    { 0x40B, 0x400D87FC, 0x1A8BC800, 0x47BC4 },
    { 0x40B, 0x400D643C, 0x1A904800, 0x4E3AC },
    { 0x40B, 0x400D5C7C, 0x1A953000, 0x48D9C },
    { 0x40B, 0x400B767C, 0x1A99C000, 0x47518 },
    { 0x40B, 0x400441F8, 0x1A9E3800, 0x1AA84 },
    { 0x40B, 0x40106568, 0x1A9FE800, 0x68C10 },
    { 0x40B, 0x4010E5A0, 0xE97A800, 0x9BCAC },
    { 0x40B, 0x40016980, 0xEA16800, 0xD6C4 },
    { 0x40B, 0x40016980, 0xEA24000, 0xC944 },
    { 0x40B, 0x40016980, 0xEA31000, 0xE700 },
    { 0x40B, 0x40016980, 0xEA3F800, 0xD64C },
    { 0x40B, 0x40016980, 0xEA4D000, 0xC900 },
    { 0x40B, 0x40016980, 0xEA5A000, 0xCFFC },
    { 0x40B, 0x40016980, 0xEA67000, 0xD720 },
    { 0x40B, 0x40016980, 0xEA74800, 0xD6CC },
    { 0x40B, 0x40016980, 0xEA82000, 0xD21C },
    { 0x40B, 0x40016980, 0xEA8F800, 0xD0BC },
    { 0x40B, 0x40016980, 0xEA9D000, 0xB544 },
    { 0x40B, 0x40016980, 0xEAA8800, 0xC4F8 },
    { 0x40B, 0x400ADFFC, 0x18AEE800, 0x4BAB0 },
    { 0x40B, 0x4037CF5C, 0x18B3A800, 0x208AF0 },
    { 0x40B, 0x4000A820, 0x18ED3800, 0x3758 },
    { 0x40B, 0x4011EC24, 0x18F0E000, 0xD8818 },
    { 0x40B, 0x400193E8, 0x191B8800, 0x89D8 },
    { 0x40B, 0x4006C850, 0x6C96000, 0x2C884 },
    { 0x40B, 0x4005B178, 0x6CC3000, 0x3555C },
    { 0x40B, 0x401EB174, 0x18D43800, 0xFB220 },
    { 0x40B, 0x4001ED60, 0x1AA67800, 0xCFF0 },
    { 0x40B, 0x4000BF30, 0x1AA74800, 0x26E0 },
    { 0x40B, 0x40003498, 0x1AA77000, 0xE28 },
    { 0x40B, 0x4000BDE0, 0x1AA78000, 0x24F4 },
    { 0x40B, 0x40006088, 0x1AA7A800, 0x1290 },
    { 0x40B, 0x400049F0, 0x1AA7C000, 0x18F4 },
    { 0x40B, 0x40005ECC, 0x1AA7E000, 0x1D38 },
    { 0x40B, 0x40002670, 0x1AA80000, 0xBE8 },
    { 0x0, 0x28240, 0x1AA81000, 0x28240 },
    { 0x0, 0x28240, 0x1AAA9800, 0x28240 },
    { 0x0, 0x28240, 0x1AAD2000, 0x28240 },
    { 0x0, 0x28240, 0x1AAFA800, 0x28240 },
    { 0x0, 0x28240, 0x1AB23000, 0x28240 },
    { 0x0, 0x28240, 0x1AB4B800, 0x28240 },
    { 0x0, 0x28240, 0x1AB74000, 0x28240 },
    { 0x0, 0x28240, 0x1AB9C800, 0x28240 },
    { 0x0, 0x28240, 0x1ABC5000, 0x28240 },
    { 0x0, 0x28240, 0x1ABED800, 0x28240 },
    { 0x0, 0x28240, 0x1AC16000, 0x28240 },
    { 0x0, 0x28240, 0x1AC3E800, 0x28240 },
    { 0x0, 0x28240, 0x1AC67000, 0x28240 },
    { 0x0, 0x28240, 0x1AC8F800, 0x28240 },
    { 0x0, 0x28240, 0x1ACB8000, 0x28240 },
    { 0x0, 0x28240, 0x1ACE0800, 0x28240 },
    { 0x0, 0x28240, 0x1AD09000, 0x28240 },
};

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
            memset(&g_Minigame.aiInputs[slot], 0, sizeof(InputStruct));

            switch (g_Pitcher.pitcherActionState) {
            case PITCHER_ACTION_STATE_WINDUP:
                if (*(u8 *)&g_Minigame.minigameAICountDownTillAction == 0) {
                    bOD_BatterAI();
                    *(u8 *)&g_Minigame.minigameAICountDownTillAction = 1;
                }
                if (g_Pitcher.windupCountdownUntilBallReleased <= g_Minigame.ai_wbChargePower_bbSwingFrame) {
                    g_Minigame.aiInputs[slot].buttonInput |= INPUT_BUTTON_A;
                }
                break;
            case PITCHER_ACTION_STATE_IN_AIR:
                if (g_Ball.pitchHangtimeCounter < g_Pitcher.frameWhenUnhittable - *(s16 *)&g_Minigame.ai_wbThrowType_bbVertAngle) {
                    g_Minigame.aiInputs[slot].buttonInput |= INPUT_BUTTON_A;
                }
                break;
            }
        }
        i++;
    } while (i < 4);
}

void minigameClearAIControlled(void) {
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
        g_Minigame.playerSlots.charID[i] = 0xFF;
    }
    g_Minigame.miniGameNumberOfParticipants = 0;
    g_Minigame.humanPlayerCount = 0;
    minigames_pickOpponentsAndLoadStats();
    for (i = 0; i < 4; i++) {
        if (g_Minigame.selectSlotState[i] >= 0) {
            g_Minigame.playerSlots.characterIndex[g_Minigame.miniGameNumberOfParticipants] = i;
            g_Minigame.playerSlots.aiControlledInd[g_Minigame.miniGameNumberOfParticipants] = g_Minigame.selectSlotState[i];
            if (g_Minigame.playerSlots.aiControlledInd[g_Minigame.miniGameNumberOfParticipants] == 0) {
                g_Minigame.humanPlayerCount++;
            }
            minigames_loadCharStats(i, g_Minigame.selectSlots[i].charID);
            g_Minigame.playerSlots.charID[g_Minigame.miniGameNumberOfParticipants] = inMemRoster[0][i].stats.CharID;
            g_Minigame.miniGameNumberOfParticipants++;
        }
    }
}

static inline void minigamesRosterSetup(void) {
    switch (g_GameLogic._125) {
    case TRANSITION_CALCULATION_TYPE_0:
        minigames_setupChallengeRoster();
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
        minigames_0x1B();
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
        minigameReadySwitcher();
        break;
    case GAME_STATUS_GAME_START_MOVIE:
        minigameStartSwitcher();
        break;
    case GAME_STATUS_0x23:
        minigames_0x23();
        break;
    case GAME_STATUS_MVP_END_GAME:
        minigameEndSwitcher();
        break;
    case GAME_STATUS_0x24:
        minigameResultsSwitcher();
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
        minigameGrandPrixNextRound();
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

void minigames_init(void) {
    int i;

    g_GameLogic.secondaryGameMode = SECONDARY_GAME_MODE_MINI_GAME_MENU;
    insertGraphicDrawingFunction(possiblyTransitionBlackScreen, 2);
    insertGraphicDrawingFunction(drawStadium, 4);
    g_Scores.inningLimit = 5;
    g_Scores.maxNumberOfExtraInnings = 5;
    g_Minigame.nextGameStatus = GAME_STATUS_MINIGAME_SELECT;
    g_Minigame.selectMenuCursor = 0;
    g_Minigame._19E2 = 0;
    g_Minigame.extraOpponentCursor = 0;
    g_Minigame.targetParticipantCount = 1;
    g_Minigame.joinedPlayerCount = 1;
    g_Minigame.GameMode_MiniGame = MINI_GAME_ID_BOBOMB_DERBY;
    g_Minigame.soloMinigameDifficulty = MINIGAME_DIFFICULTY_MULTIPLAYER_CHALLENGE_EASY;
    g_Minigame.loadedStadiumID = -1;
    g_Minigame.charLoadSlot = -1;
    g_Minigame._19A7 = 4;
    g_Minigame.pauseInd = 0;
    g_Minigame.grandPrixInd = 0;
    g_Minigame.grandPrixWonInd = 0;
    g_Minigame.challengeModeInd = 0;
    g_Minigame.starDashStarHolderSigned = -1;
    g_Minigame.minigameInactiveInd = 1;
    g_Minigame.challenge_minigame_haven_tWonYetIndicator = TRUE;
    g_Minigame.endSequencePhase = 0;
    g_Minigame.grandPrixFinalHumanCount = 0;
    g_Minigame.charReselectInd = 0;
    g_Minigame.retryInd = 0;
    g_Minigame.nextDifficultyInd = 0;
    g_Minigame.grandPrixNewBestInd[0] = 0;
    g_Minigame.menuMusicStartedInd = 0;
    for (i = 0; i < 4; i++) {
        g_Minigame.selectSlotState[i] = -1;
        g_Minigame.selectSlots[i].charID = CHAR_ID_NONE;
        g_Minigame.selectSlots[i].loadedCharID = CHAR_ID_NONE;
        g_Minigame.selectSlots[i].pendingCharID = CHAR_ID_NONE;
        g_Minigame.selectSlots[i].charReadyInd = 0;
        g_Minigame.selectSlots[i].charReadyPrevInd = 0;
        g_Minigame.charLoadQueue[i] = -1;
        g_Minigame.charChangeFrames[i] = 20;
        g_Minigame.charLoadPending[i] = 0;
        g_Minigame.playerSlots.aiStrength[i] = 0;
        g_Minigame.playerSlots.superstarBoostInd[i] = 0;
    }
    g_Minigame.charLoadStartedInd = 0;
    animRelated[0xB9] = 0;
    if (g_d_GameSettings.exhibitionMatchInd == FALSE) {
        g_Minigame.challengeModeInd = 1;
        g_Minigame.selectSlotState[g_d_GameSettings._35] = g_d_GameSettings._35;
        lbl_3_common_bss_37400.humanTeam = g_d_GameSettings._35;
        g_Minigame.GameMode_MiniGame = g_d_GameSettings._33;
        clearScoutState();
        g_Minigame.nextGameStatus = GAME_STATUS_TOY_STADIUM_CHARACTER_SELECT;
        SetGameStatus(GAME_STATUS_0x1B);
    } else {
        SetGameStatus(GAME_STATUS_0x1B);
    }
}

void minigames_0x1B(void) {
    switch (g_GameLogic._125) {
    case TRANSITION_CALCULATION_TYPE_0:
        animRelated[0xD8] = 0;
        sound_crowd_EffectsStruct._2C = 0;
        g_GameLogic._125++;
        break;
    }
    hugeAnimStruct[0x307A] = 0;
    SetGameStatus(GAME_STATUS_TOY_STADIUM_LOAD);
}

void minigames_0x25(void) {
    minigamesRosterSetup();
}

void minigames_setupChallengeRoster(void) {
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
            g_Minigame.selectSlots[i].confirmedInd = 1;
        } else {
            g_Minigame.selectSlotState[i] = 1;
            n++;
            g_Minigame.playerSlots.aiStrength[i] = minigameChallengeAIStrength[g_d_GameSettings.challengeDifficulty];
            if (n >= minigameChallengeOpponentCounts[g_Minigame.GameMode_MiniGame]) {
                break;
            }
        }
    }

    g_Minigame.miniGameNumberOfParticipants = minigameChallengeOpponentCounts[g_Minigame.GameMode_MiniGame] + 1;
    g_Minigame.humanPlayerCount = 1;
    g_Minigame.multiPlayerInd = 1;
    g_Minigame.soloMinigameDifficulty = 0;
    for (k = 0; k < 6; k++) {
        arr[k] = minigameChallengeOpponentPools[g_Minigame.GameMode_MiniGame * 7 + 1 + k];
    }
    idx = 0;
    for (j = 0; j < minigameChallengeOpponentCounts[g_Minigame.GameMode_MiniGame]; j++) {
        for (;;) {
            if (g_Minigame.selectSlotState[idx] == 1) {
                break;
            }
            idx++;
        }
        r = random_fn_3_9EE24(minigameChallengeOpponentPools[g_Minigame.GameMode_MiniGame * 7] - j);
        for (k = 0; k < 6; k++) {
            if (arr[k] == 0xFF) {
                continue;
            }
            if (r == 0) {
                g_Minigame.selectSlots[idx].charID = arr[k];
                g_Minigame.selectSlots[idx].confirmedInd = 1;
                idx++;
                arr[k] = 0xFF;
                break;
            }
            r--;
        }
    }
}

static inline void minigameStadiumSetup(void) {
    g_Minigame.loadedStadiumID = -1;
    FrameCountOfEntireGame[0x10] = 0;
    g_d_GameSettings.StadiumID = mapping_minigame_Stadium[g_Minigame.GameMode_MiniGame];
    g_d_GameSettings.miniGameStadiumIndicator = 0;
    if (g_d_GameSettings.StadiumID == STADIUM_ID_MARIO_STADIUM || g_d_GameSettings.StadiumID == STADIUM_ID_PEACH_GARDEN
        || g_d_GameSettings.StadiumID == STADIUM_ID_BOWSERS_CASTLE || g_d_GameSettings.StadiumID == STADIUM_ID_YOHSI_PARK) {
        g_d_GameSettings.miniGameStadiumIndicator = 1;
    }
    insertGraphicDrawingFunction(manageStadiumLoading, 0);
}

void minigames_startStadiumLoad(void) {
    if (g_Minigame.loadedStadiumID >= 0) {
        hugeAnimStruct[0x307E] = 0;
        cleanupMinigameResources();
        fn_3_5E60();
    }
    minigameStadiumSetup();
}

BOOL minigames_isStadiumLoading(void) {
    if (g_Minigame.loadedStadiumID == -1) {
        if (FrameCountOfEntireGame[0x10] != 0) {
            g_Minigame.loadedStadiumID = mapping_minigame_Stadium[g_Minigame.GameMode_MiniGame];
            return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}

void minigameQueueHudEvent(u8 arg0, s16 arg1) {
    g_Minigame.hudEventType = arg0;
    g_Minigame.someGraphicFrameCountdown = arg1;
}

void toyFieldStadiumLoad(void) {
    int i;

    switch (g_GameLogic._125) {
    case TRANSITION_CALCULATION_TYPE_0:
        stadiumMusic(-1);
        minigameCharSelectReset();
        sound_crowd_EffectsStruct._2C = 0;
        g_GameLogic._125++;
        // fallthrough
    case TRANSITION_CALCULATION_TYPE_1:
        if (fn_3_90928()) {
            g_GameLogic._125++;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_2:
        if (diskReadRelated(CommonUIFiles_minigame[29], 9)) {
            g_GameLogic._125++;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_3:
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
            if (diskReadRelated(CommonUIFiles_minigame[13], 0x11)) {
                g_GameLogic._125++;
            }
        } else {
            g_GameLogic._125++;
        }
        break;
    default:
        fn_800189E4();
        insertGraphicDrawingFunction(startMenuMusic, 1);
        g_Minigame.menuMusicStartedInd = 1;
        SetGameStatus(g_Minigame.nextGameStatus);
        break;
    }
}

void minigameSelectSwitcher(void) {
    u8 mode;

    switch (g_GameLogic._125) {
    case TRANSITION_CALCULATION_TYPE_0:
        changeScene(6, 6);
        g_GameLogic._125++;
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        hugeAnimStruct[0x307E] = 0;
        g_Minigame.selectedDifficulty = 0;
        break;
    case TRANSITION_CALCULATION_TYPE_1:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 20) {
            g_GameLogic._125++;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_2:
        minigameSelectMenuUpdate();
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        break;
    case TRANSITION_CALCULATION_TYPE_3:
        if (animRelated[0xBB] == 0) {
            g_GameLogic._125++;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_4:
        mode = g_Minigame.GameMode_MiniGame;
        if (mode >= MINI_GAME_ID_BOBOMB_DERBY && mode <= MINI_GAME_ID_STAR_DASH) {
            if (g_Minigame.challengeModeInd != 0) {
                g_Minigame.selectedDifficulty = 0;
            } else {
                g_Minigame.selectedDifficulty = ((u8*)&g_d_GameSettings)[0x13 + mode];
            }
        }
        SetGameStatus(GAME_STATUS_TOY_STADIUM_CHARACTER_SELECT);
        break;
    case TRANSITION_CALCULATION_TYPE_5:
        switch (((int (*)(u16))exitMenu_main)(g_Controls[lbl_80366158[0x27]].newButtonInput)) {
        case 1:
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_GameLogic._125++;
            break;
        case 2:
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_2;
            break;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_6:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 45) {
            changeScene(4, 6);
        }
        if (lbl_8037169C[0x13] != 0) {
            fn_80062A74();
            g_Minigame.menuMusicStartedInd = 0;
            g_GameLogic._125++;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_7:
        fn_8004CC18();
        g_GameLogic.framesOfExitingToMenu = 1;
        break;
    }
}

void minigameSelectMenuUpdate(void) {
    InputStruct* input = &g_Controls[lbl_80366158[0x27]];

    if (animRelated[0xBB] == 0) {
        if (input->newButtonInput & INPUT_BUTTON_A) {
            u8 id = minigameSelectMenuGameIDs[(s8)g_Minigame.selectMenuCursor];

            if (id == MINI_GAME_ID_STAR_DASH && g_d_GameSettings._12 < 1) {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            } else if (id == MINI_GAME_ID_MARIO_GRAND_PRIX && g_d_GameSettings._12 < 2) {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            } else {
                g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_3;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            }
        } else if (input->newButtonInput & INPUT_BUTTON_B) {
            fn_3_5B408();
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_5;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        } else if (input->_08 & INPUT_BUTTON_LEFT) {
            if ((s8)g_Minigame.selectMenuCursor != 0) {
                g_Minigame.selectMenuCursor--;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else if (input->_08 & INPUT_BUTTON_RIGHT) {
            if ((s8)g_Minigame.selectMenuCursor < 6) {
                g_Minigame.selectMenuCursor++;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    }
    g_Minigame.GameMode_MiniGame = minigameSelectMenuGameIDs[(s8)g_Minigame.selectMenuCursor];
    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_MARIO_GRAND_PRIX) {
        g_Minigame.grandPrixInd = 1;
    } else {
        g_Minigame.grandPrixInd = 0;
    }
    animRelated[0xB9] = g_Minigame.selectMenuCursor;
}

void toyFieldCharSelectSwitcher(void) {
    int i;
    int j;
    u32 k;

    if (g_GameLogic._125 <= 2) {
        for (i = 0; i < 4; i++) {
            g_Minigame.selectSlots[i].charReadyPrevInd = g_Minigame.selectSlots[i].charReadyInd;
            g_Minigame.selectSlots[i].charReadyInd = 1;
        }
    }
    switch (g_GameLogic._125) {
    case TRANSITION_CALCULATION_TYPE_0:
        for (i = 0; i < 4; i++) {
            if (g_Minigame.selectSlotState[i] == 1) {
                g_Minigame.selectSlotState[i] = -1;
            }
            g_Minigame.playerSlots.aiStrength[i] = 0;
            g_Minigame.charLoadPending[i] = 1;
        }
        if (g_Minigame.challengeModeInd != 0) {
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
                    g_Minigame.selectSlots[i].charID = CHAR_ID_NONE;
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
            g_Minigame.selectSlots[i].confirmedInd = 0;
            g_Minigame.charChangeFrames[i] = 20;
        }
        hugeAnimStruct[0x307E] = 0;
        hugeAnimStruct[0x2D77] = 0;
        hugeAnimStruct[0x307A] = 5;
        g_Minigame.charSelectOpponentSlot = -1;
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_Minigame.charSelectState = 0;
        g_Minigame._19E2 = 0;
        g_Minigame.extraOpponentCursor = 0;
        if (g_Minigame.menuMusicStartedInd == 0) {
            insertGraphicDrawingFunction(startMenuMusic, 1);
        }
        changeScene(1, 6);
        g_GameLogic._125++;
        break;
    case TRANSITION_CALCULATION_TYPE_1:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
            for (i = 0; i < 4; i++) {
                if (g_Minigame.selectSlotState[i] == 0) {
                    g_Minigame.selectSlots[i].charID = cssCursorOnBottomControl_maybe(i, 0, 0, 0, 0);
                    g_Minigame.selectSlots[i].onBottomControlInd = 0;
                    g_Minigame.battingHandedness[i] =
                        ((CharacterStats*)&Static_Stats_Tables)[g_Minigame.selectSlots[i].charID].stats.FieldingArm * 2 +
                        ((CharacterStats*)&Static_Stats_Tables)[g_Minigame.selectSlots[i].charID].stats.BattingStance;
                    g_Minigame.playerSlots.superstarBoostInd[i] = 0;
                }
            }
            changeScene(1, 6);
        }
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 30) {
            g_Minigame.charSelectState = 0;
            if (g_Minigame.charReselectInd != 0) {
                g_Minigame.charSelectState = 5;
                g_Minigame.charReselectInd = 0;
                g_Minigame.selectSlots[lbl_80366158[0x27]].confirmedInd = 1;
                addOrRemoveCharacterToTeam(lbl_80366158[0x27], g_Minigame.selectSlots[lbl_80366158[0x27]].charID, TRUE);
            }
            g_GameLogic._125++;
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_2:
        minigameCharSelectUpdate();
        break;
    case TRANSITION_CALCULATION_TYPE_3:
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
            if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 20) {
                switch (((int (*)(u16))exitMenu_main)(g_Controls[lbl_80366158[0x27]].newButtonInput)) {
                case 1:
                    g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_4;
                    g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                    break;
                case 2:
                    g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_2;
                    break;
                }
            }
            return;
        }
        g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_4;
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        break;
    case TRANSITION_CALCULATION_TYPE_4:
        if (g_Minigame.charLoadSlot == -1) {
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 45) {
                    changeScene(4, 6);
                }
                if (lbl_8037169C[0x13] != 0) {
                    g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_5;
                }
            } else if (g_GameLogic.FrameCountOfCurrentAtBat_Copy >= 15) {
                SetGameStatus(GAME_STATUS_MINIGAME_SELECT);
            }
        }
        hugeAnimStruct[0x307A] = 0;
        break;
    case TRANSITION_CALCULATION_TYPE_5:
        unregisterMatchHudObjects();
        fn_8004CC18();
        g_GameLogic.framesOfExitingToMenu = 1;
        break;
    case TRANSITION_CALCULATION_TYPE_6:
        if (g_Minigame.charLoadQueue[0] < 0) {
            for (i = 0; i < 4; i++) {
                if (g_Minigame.selectSlots[i].charReadyInd == 0 && g_Minigame.selectSlots[i].confirmedInd != 0) {
                    break;
                }
            }
            if (i >= 4) {
                changeScene(3, 6);
                if (g_Minigame.grandPrixInd == 0) {
                    menuMusic.fade = 6;
                    g_Minigame.menuMusicStartedInd = 0;
                }
            }
        }
        if (lbl_8037169C[0x13] != 0) {
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_7;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_7:
        resetAnimTracks();
        minigamesFillRoster();
        hugeAnimStruct[0x307A] = 0;
        g_Minigame.helpMenuResult = 0;
        if (g_Minigame.grandPrixInd != 0) {
            minigameStartGrandPrix();
        } else {
            SetGameStatus(GAME_STATUS_MINIGAME_READY);
        }
        break;
    }
    if (g_GameLogic._125 == 3 || g_GameLogic._125 == 4) {
        for (i = 0; i < 4; i++) {
            g_Minigame.selectSlots[i].charReadyInd = 0;
        }
    }
    if (g_GameLogic._125 >= 2) {
        minigameCharLoadQueueUpdate();
    }
}

void minigameCharSelectUpdate(void) {
    s8 sel[4];
    u8 used[12];
    int port;
    int maxLevel;
    InputStruct* pad;
    int i;
    int j;
    int k;
    int ready;
    BOOL changed;
    int remaining;
    int pick;
    int cursor;
    s16 prevChar;
    u16* frames;

    port = lbl_80366158[0x27];
    pad = &g_Controls[port];
    maxLevel = ((u8*)&g_d_GameSettings)[0x13 + g_Minigame.GameMode_MiniGame];
    if (g_Minigame.challengeModeInd != 0) {
        maxLevel = 2;
    }
    if (g_Minigame.charSelectState == 0) {
        changed = FALSE;
        for (i = 0; i < 4; i++) {
            CHAR_SELECT_BYTE(0x74 + i) = 0;
            sel[i] = -1;
            if (g_Minigame.selectSlotState[i] == 0) {
                if (i != port && g_Minigame.selectSlots[i].confirmedInd == 0 && (g_Controls[i].newButtonInput & INPUT_BUTTON_B) &&
                    CHAR_SELECT_UBYTE(0x92) != 0) {
                    g_Minigame.selectSlotState[i] = -1;
                    g_Minigame.joinedPlayerCount--;
                    sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                }
            } else if (i == port) {
                g_Minigame.selectSlotState[i] = 0;
                changed = TRUE;
                sel[i] = -3;
            } else if (g_Minigame.challengeModeInd == 0 && (g_Controls[i].newButtonInput & INPUT_BUTTON_A)) {
                g_Minigame.selectSlotState[i] = 0;
                sel[i] = -3;
                changed = TRUE;
                g_Minigame.joinedPlayerCount++;
            }
        }
        if (changed) {
            cssLoadingRelated_1(0, sel[0], sel[1], sel[2], sel[3], 0);
        }
        ready = 0;
        for (i = 0; i < 4; i++) {
            if (g_Minigame.selectSlotState[i] == 0) {
                SATURATING_INCREMENT_U16(g_Minigame.charChangeFrames[i]);
                if (sel[i] == -3) {
                    g_Minigame.selectSlots[i].charID = cssCursorOnBottomControl_maybe(i, 0, 0, 0, 0);
                    g_Minigame.selectSlots[i].charReadyInd = 0;
                    g_Minigame.battingHandedness[i] = ((CharacterStats*)&Static_Stats_Tables)[g_Minigame.selectSlots[i].charID].stats.FieldingArm * 2 +
                                                      ((CharacterStats*)&Static_Stats_Tables)[g_Minigame.selectSlots[i].charID].stats.BattingStance;
                    g_Minigame.playerSlots.superstarBoostInd[i] = 0;
                    if (g_d_GameSettings.exhibitionMatchInd == FALSE && ((u8*)starMissionCompletionTracker)[0x43D6 + g_Minigame.selectSlots[i].charID] != 0) {
                        g_Minigame.playerSlots.superstarBoostInd[i] = 0;
                    }
                    if (i != port) {
                        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                    }
                } else if (g_Minigame.selectSlots[i].confirmedInd != 0) {
                    if (g_Controls[i].newButtonInput & INPUT_BUTTON_B) {
                        if (CHAR_SELECT_UBYTE(0x92) == 0) {
                            continue;
                        }
                        g_Minigame.selectSlots[i].confirmedInd = 0;
                        addOrRemoveCharacterToTeam(i, g_Minigame.selectSlots[i].charID, FALSE);
                        cssCursorOnBottomControl_maybe(i, 0, 0, 0, 0);
                        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                        for (j = 0; j < 4; j++) {
                            if (i != j && g_Minigame.selectSlotState[j] == 0) {
                                pick = fn_8004FDE8(i, j);
                                if (pick >= -1) {
                                    g_Minigame.selectSlots[j].charID = pick;
                                }
                            }
                        }
                    } else {
                        ready++;
                    }
                } else {
                    if ((g_Controls[i].newButtonInput & INPUT_BUTTON_A) && g_Minigame.selectSlots[i].charID >= 0 &&
                        g_GameLogic.FrameCountOfCurrentAtBat_Copy > 30) {
                        if (g_Minigame.selectSlots[i].onBottomControlInd != 0) {
                            sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
                            goto moveCursor0;
                        }
                        if (CHAR_SELECT_BYTE(0x7F + i) >= 0) {
                            goto afterMove0;
                        }
                        if (g_Minigame.selectSlots[i].charID == g_Minigame.selectSlots[i].loadedCharID &&
                            g_Minigame.selectSlots[i].loadedHandedness == g_Minigame.selectSlots[i].wantedHandedness && g_Minigame.selectSlots[i].charReadyInd != 0 &&
                            g_Minigame.selectSlots[i].charReadyPrevInd != 0) {
                            g_Minigame.selectSlots[i].confirmedInd = 1;
                            addOrRemoveCharacterToTeam(i, g_Minigame.selectSlots[i].charID, TRUE);
                            playPlayerSelectedSound(g_Minigame.selectSlots[i].charID);
                        }
                        goto afterMove0;
                    } else if ((g_Controls[i].newButtonInput & INPUT_BUTTON_B) && g_d_GameSettings.exhibitionMatchInd != FALSE) {
                        if (CHAR_SELECT_UBYTE(0x92) == 0) {
                            continue;
                        }
                        if (CHAR_SELECT_BYTE(0x7F + i) >= 0) {
                            goto afterMove0;
                        }
                        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                        g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_3;
                        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                        return;
                    }
                moveCursor0:
                    prevChar = g_Minigame.selectSlots[i].charID;
                    cursor = cssCursorOnBottomControl_maybe(i, g_Controls[i].buttonInput, g_Controls[i].newButtonInput, g_Controls[i]._08, 0);
                    if (cursor >= 0) {
                        g_Minigame.selectSlots[i].charID = cursor;
                        if (prevChar != g_Minigame.selectSlots[i].charID) {
                            g_Minigame.charChangeFrames[i] = 0;
                            g_Minigame.battingHandedness[i] =
                                ((CharacterStats*)&Static_Stats_Tables)[g_Minigame.selectSlots[i].charID].stats.FieldingArm * 2 +
                                ((CharacterStats*)&Static_Stats_Tables)[g_Minigame.selectSlots[i].charID].stats.BattingStance;
                            g_Minigame.playerSlots.superstarBoostInd[i] = 0;
                            if (g_d_GameSettings.exhibitionMatchInd == FALSE &&
                                ((u8*)starMissionCompletionTracker)[0x43D6 + g_Minigame.selectSlots[i].charID] != 0) {
                                g_Minigame.playerSlots.superstarBoostInd[i] = 0;
                            }
                        }
                        g_Minigame.selectSlots[i].onBottomControlInd = 0;
                    } else {
                        g_Minigame.selectSlots[i].charID = fn_8004FD64(i);
                        g_Minigame.selectSlots[i].onBottomControlInd = 1;
                        g_Minigame.selectSlots[i].charReadyInd = 0;
                    }
                afterMove0:;
                }
                if (g_Minigame.selectSlots[i].onBottomControlInd == 0 && g_Minigame.selectSlots[i].confirmedInd == 0 && (g_Controls[i].newButtonInput & INPUT_BUTTON_X)) {
                    g_Minigame.charChangeFrames[i] = 0;
                    g_Minigame.battingHandedness[i]++;
                    if (g_Minigame.battingHandedness[i] > 3) {
                        g_Minigame.battingHandedness[i] = 0;
                    }
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                }
                if (g_Minigame.challengeModeInd != 0) {
                    if (((u8*)starMissionCompletionTracker)[0x43D6 + g_Minigame.selectSlots[i].charID] != 0) {
                        g_Minigame.playerSlots.superstarBoostInd[i] = 1;
                    } else {
                        g_Minigame.playerSlots.superstarBoostInd[i] = 0;
                    }
                } else if (superstarUnlocked[g_Minigame.selectSlots[i].charID] != 0 && (g_Controls[i].newButtonInput & INPUT_BUTTON_Y)) {
                    g_Minigame.playerSlots.superstarBoostInd[i] ^= 1;
                    if (g_Minigame.playerSlots.superstarBoostInd[i] != 0) {
                        sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
                    } else {
                        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                    }
                }
            }
        }
        if ((u8)ready >= g_Minigame.joinedPlayerCount) {
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_Minigame.charSelectState = 2;
            g_Minigame.targetParticipantCount = g_Minigame.joinedPlayerCount;
            if (g_Minigame.grandPrixInd != 0) {
                if (g_Minigame.joinedPlayerCount == 4) {
                    g_Minigame.charSelectState = 7;
                } else {
                    g_Minigame.charSelectState = 6;
                }
                g_Minigame.targetParticipantCount = 4;
            } else if (g_Minigame.joinedPlayerCount == 1 && g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD) {
                g_Minigame.charSelectState = 5;
            } else if (g_Minigame.joinedPlayerCount == 4) {
                g_Minigame.charSelectState = 7;
            } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && g_d_GameSettings.exhibitionMatchInd != FALSE) {
                g_Minigame.charSelectState = 2;
                g_Minigame.targetParticipantCount = minigameParticipantCounts[g_Minigame.GameMode_MiniGame * 5 + 4];
            } else if (g_Minigame.joinedPlayerCount >= minigameParticipantCounts[g_Minigame.GameMode_MiniGame * 5 + 4]) {
                g_Minigame.charSelectState = 1;
                if (g_Minigame.joinedPlayerCount >= minigameParticipantCounts[g_Minigame.GameMode_MiniGame * 5 + 4]) {
                    g_Minigame.minExtraOpponents = 0;
                } else {
                    g_Minigame.minExtraOpponents = minigameParticipantCounts[g_Minigame.GameMode_MiniGame * 5 + 4] - g_Minigame.joinedPlayerCount;
                }
                g_Minigame.maxExtraOpponents = 4 - g_Minigame.joinedPlayerCount;
                g_Minigame.extraOpponentCursor = g_Minigame.minExtraOpponents;
            } else {
                g_Minigame.targetParticipantCount = minigameParticipantCounts[g_Minigame.GameMode_MiniGame * 5 + 4];
                g_Minigame.charSelectState = 2;
            }
        }
    } else if (g_Minigame.charSelectState == 1) {
        if (pad->newButtonInput & INPUT_BUTTON_A) {
            if ((s8)g_Minigame.extraOpponentCursor != 0) {
                g_Minigame.charSelectState = 2;
                g_Minigame.targetParticipantCount = g_Minigame.extraOpponentCursor + g_Minigame.joinedPlayerCount;
            } else {
                g_Minigame.charSelectState = 7;
            }
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (pad->newButtonInput & INPUT_BUTTON_B) {
            g_Minigame.selectSlots[port].confirmedInd = 0;
            addOrRemoveCharacterToTeam(port, g_Minigame.selectSlots[port].charID, FALSE);
            g_Minigame.charSelectState = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        } else if (pad->_08 & INPUT_BUTTON_UP) {
            if ((s8)g_Minigame.extraOpponentCursor > g_Minigame.minExtraOpponents) {
                g_Minigame.extraOpponentCursor--;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else if (pad->_08 & INPUT_BUTTON_DOWN) {
            if ((s8)g_Minigame.extraOpponentCursor < g_Minigame.maxExtraOpponents) {
                g_Minigame.extraOpponentCursor++;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    } else if (g_Minigame.charSelectState == 2 || g_Minigame.charSelectState == 6) {
        remaining = g_Minigame.targetParticipantCount - g_Minigame.joinedPlayerCount;
        for (i = 0; i < 4; i++) {
            if (remaining == 0) {
                break;
            }
            if (g_Minigame.selectSlotState[i] == -1) {
                g_Minigame.selectSlotState[i] = 1;
                remaining--;
                g_Minigame.selectSlots[i].charID = CHAR_ID_NONE;
                g_Minigame.selectSlots[i].loadedCharID = CHAR_ID_NONE;
                CHAR_SELECT_BYTE(0x74 + i) = 1;
            }
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && g_d_GameSettings.exhibitionMatchInd == FALSE) {
            g_Minigame.charSelectState = 8;
        } else if (g_Minigame.joinedPlayerCount == 1 && g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD) {
            g_Minigame.charSelectState = 8;
        } else {
            g_Minigame.charSelectState = 3;
        }
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
    } else if (g_Minigame.charSelectState == 3) {
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
            if (g_Minigame.charSelectOpponentSlot >= 0) {
                g_Minigame.charSelectOpponentSlot = -1;
            } else {
                for (k = 0; k < 12; k++) {
                    used[k] = 0;
                }
                remaining = 12;
                for (i = 0; i < 4; i++) {
                    sel[i] = -1;
                    if (g_Minigame.selectSlots[i].confirmedInd != 0) {
                        for (k = 0; k < 12; k++) {
                            if (g_Minigame.selectSlots[i].charID == lbl_800E854C[k]) {
                                used[k] = 1;
                                remaining--;
                            }
                        }
                    }
                }
                for (i = 0; i < 4; i++) {
                    if (g_Minigame.selectSlotState[i] == 1 && g_Minigame.selectSlots[i].confirmedInd == 0) {
                        pick = random_fn_3_9EE24(remaining);
                        for (k = 0; k < 12; k++) {
                            if (used[k] == 0) {
                                if (pick == 0) {
                                    sel[i] = lbl_800E854C[k];
                                    cssLoadingRelated_1(1, sel[0], sel[1], sel[2], sel[3], 0);
                                    g_Minigame.selectSlots[i].charID = sel[i];
                                    g_Minigame.battingHandedness[i] =
                                        ((CharacterStats*)&Static_Stats_Tables)[sel[i]].stats.FieldingArm * 2 +
                                        ((CharacterStats*)&Static_Stats_Tables)[sel[i]].stats.BattingStance;
                                    g_Minigame.playerSlots.superstarBoostInd[i] = 0;
                                    goto tail;
                                }
                                pick--;
                            }
                        }
                        goto tail;
                    }
                }
            }
        } else if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 45) {
            for (i = 0; i < 4; i++) {
                if (g_Minigame.selectSlotState[i] != 1 || g_Minigame.selectSlots[i].confirmedInd == 1) {
                    continue;
                }
                SATURATING_INCREMENT_U16(g_Minigame.charChangeFrames[i]);
                if (pad->newButtonInput & INPUT_BUTTON_A) {
                    if (g_Minigame.selectSlots[i].charID >= 0 && g_Minigame.selectSlots[i].onBottomControlInd == 0) {
                        if (CHAR_SELECT_BYTE(0x7F + i) < 0) {
                            if (g_Minigame.selectSlots[i].charID == g_Minigame.selectSlots[i].loadedCharID &&
                                g_Minigame.selectSlots[i].loadedHandedness == g_Minigame.selectSlots[i].wantedHandedness && g_Minigame.selectSlots[i].charReadyInd != 0 &&
                                g_Minigame.selectSlots[i].charReadyPrevInd != 0) {
                                g_Minigame.charSelectState = 4;
                                g_Minigame.selectSlots[i].confirmedInd = 1;
                                g_Minigame.charSelectOpponentSlot = i;
                                g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                                addOrRemoveCharacterToTeam(i, g_Minigame.selectSlots[i].charID, TRUE);
                                playPlayerSelectedSound(g_Minigame.selectSlots[i].charID);
                            }
                        }
                        goto afterMove3;
                    }
                }
                prevChar = g_Minigame.selectSlots[i].charID;
                cursor = cssCursorOnBottomControl_maybe(i, pad->buttonInput, pad->newButtonInput, pad->_08, 0);
                if (cursor >= 0) {
                    g_Minigame.selectSlots[i].charID = cursor;
                    if (prevChar != g_Minigame.selectSlots[i].charID) {
                        g_Minigame.charChangeFrames[i] = 0;
                        g_Minigame.battingHandedness[i] =
                            ((CharacterStats*)&Static_Stats_Tables)[g_Minigame.selectSlots[i].charID].stats.FieldingArm * 2 +
                            ((CharacterStats*)&Static_Stats_Tables)[g_Minigame.selectSlots[i].charID].stats.BattingStance;
                        g_Minigame.playerSlots.superstarBoostInd[i] = 0;
                    }
                    g_Minigame.selectSlots[i].onBottomControlInd = 0;
                } else {
                    g_Minigame.selectSlots[i].onBottomControlInd = 1;
                    g_Minigame.selectSlots[i].charReadyInd = 0;
                }
            afterMove3:
                if ((pad->newButtonInput & INPUT_BUTTON_X) && g_Minigame.selectSlots[i].onBottomControlInd == 0) {
                    g_Minigame.charChangeFrames[i] = 0;
                    g_Minigame.battingHandedness[i]++;
                    if (g_Minigame.battingHandedness[i] > 3) {
                        g_Minigame.battingHandedness[i] = 0;
                    }
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                }
                if (superstarUnlocked[g_Minigame.selectSlots[i].charID] != 0 && (pad->newButtonInput & INPUT_BUTTON_Y)) {
                    g_Minigame.playerSlots.superstarBoostInd[i] ^= 1;
                    if (g_Minigame.playerSlots.superstarBoostInd[i] != 0) {
                        sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
                    } else {
                        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                    }
                }
                break;
            }
            if (i >= 4) {
                g_Minigame.charSelectState = 7;
                g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            } else {
                for (j = 0; j < 4; j++) {
                    if (g_Minigame.selectSlotState[j] == 0 && (g_Controls[j].newButtonInput & INPUT_BUTTON_B)) {
                        CHAR_SELECT_BYTE(0x7F + i) = -1;
                        if (j == port) {
                            for (k = 3; k >= 0; k--) {
                                if (g_Minigame.selectSlotState[k] == 1) {
                                    if (g_Minigame.selectSlots[k].confirmedInd == 0) {
                                        if (g_Minigame.selectSlots[k].loadedCharID != CHAR_ID_NONE || g_Minigame.selectSlots[k].pendingCharID != CHAR_ID_NONE) {
                                            g_Minigame.selectSlots[k].charID = CHAR_ID_NONE;
                                            g_Minigame.selectSlots[k].loadedCharID = CHAR_ID_NONE;
                                            g_Minigame.selectSlots[k].charReadyInd = 0;
                                            g_Minigame.charLoadPending[k] = 1;
                                        }
                                    } else {
                                        addOrRemoveCharacterToTeam(k, g_Minigame.selectSlots[k].charID, FALSE);
                                        g_Minigame.selectSlots[k].confirmedInd = 0;
                                        break;
                                    }
                                }
                            }
                            if (k < 0) {
                                for (k = 3; k >= 0; k--) {
                                    if (g_Minigame.selectSlotState[k] == 1) {
                                        if (g_Minigame.selectSlots[k].charID >= 0) {
                                            if (g_Minigame.selectSlots[k].loadedCharID == CHAR_ID_NONE) {
                                                g_Minigame.selectSlots[k].loadedHandedness = 1;
                                            } else {
                                                g_Minigame.selectSlots[k].charID = CHAR_ID_NONE;
                                                g_Minigame.selectSlots[k].loadedCharID = CHAR_ID_NONE;
                                                g_Minigame.charLoadPending[k] = 1;
                                                g_Minigame.selectSlots[k].confirmedInd = 0;
                                            }
                                        }
                                        g_Minigame.selectSlotState[k] = -1;
                                    }
                                }
                                addOrRemoveCharacterToTeam(j, g_Minigame.selectSlots[j].charID, FALSE);
                                g_Minigame.charSelectState = 0;
                                g_Minigame.selectSlots[j].confirmedInd = 0;
                            }
                        } else {
                            addOrRemoveCharacterToTeam(j, g_Minigame.selectSlots[j].charID, FALSE);
                            g_Minigame.charSelectState = 0;
                            g_Minigame.selectSlots[j].confirmedInd = 0;
                            for (k = 0; k < 4; k++) {
                                if (g_Minigame.selectSlotState[k] == 1) {
                                    if (g_Minigame.selectSlots[k].charID >= 0) {
                                        if (g_Minigame.selectSlots[k].confirmedInd == 1) {
                                            addOrRemoveCharacterToTeam(k, g_Minigame.selectSlots[k].charID, FALSE);
                                        }
                                        if (g_Minigame.selectSlots[k].loadedCharID != CHAR_ID_NONE) {
                                            g_Minigame.selectSlots[k].charID = CHAR_ID_NONE;
                                            g_Minigame.selectSlots[k].loadedCharID = CHAR_ID_NONE;
                                            g_Minigame.charLoadPending[k] = 1;
                                            g_Minigame.selectSlots[k].confirmedInd = 0;
                                        }
                                    }
                                    g_Minigame.selectSlotState[k] = -1;
                                }
                            }
                        }
                        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                        return;
                    }
                }
            }
        }
    } else if (g_Minigame.charSelectState == 4) {
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 40) {
            if (pad->newButtonInput & INPUT_BUTTON_A) {
                g_Minigame.charSelectOpponentSlot = -1;
                g_Minigame.charSelectState = 3;
                g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            } else if (pad->newButtonInput & INPUT_BUTTON_B) {
                addOrRemoveCharacterToTeam(g_Minigame.charSelectOpponentSlot,
                                           g_Minigame.selectSlots[g_Minigame.charSelectOpponentSlot].charID, FALSE);
                g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                g_Minigame.selectSlots[g_Minigame.charSelectOpponentSlot].confirmedInd = 0;
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                g_Minigame.charSelectState = 3;
            } else if (pad->_08 & INPUT_BUTTON_UP) {
                if (g_Minigame.playerSlots.aiStrength[g_Minigame.charSelectOpponentSlot] != 0) {
                    g_Minigame.playerSlots.aiStrength[g_Minigame.charSelectOpponentSlot]--;
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                }
            } else if (pad->_08 & INPUT_BUTTON_DOWN) {
                if (g_Minigame.playerSlots.aiStrength[g_Minigame.charSelectOpponentSlot] < 3) {
                    g_Minigame.playerSlots.aiStrength[g_Minigame.charSelectOpponentSlot]++;
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                }
            }
        }
    } else if (g_Minigame.charSelectState == 5) {
        for (i = 0; i < 4; i++) {
            if (g_Minigame.selectSlotState[i] >= 0 && g_Minigame.selectSlots[i].confirmedInd != 0) {
                SATURATING_INCREMENT_U16(g_Minigame.charChangeFrames[i]);
            }
        }
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 30) {
            if (pad->newButtonInput & INPUT_BUTTON_A) {
                g_Minigame.charSelectState = 6;
                g_Minigame.soloMinigameDifficulty = g_Minigame.selectedDifficulty;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            } else if (pad->newButtonInput & INPUT_BUTTON_B) {
                g_Minigame.selectSlots[port].confirmedInd = 0;
                addOrRemoveCharacterToTeam(port, g_Minigame.selectSlots[port].charID, FALSE);
                g_Minigame.charSelectState = 0;
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            } else if (pad->_08 & INPUT_BUTTON_LEFT) {
                if ((s8)g_Minigame.selectedDifficulty > 0) {
                    g_Minigame.selectedDifficulty--;
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                }
            } else if (pad->_08 & INPUT_BUTTON_RIGHT) {
                if ((s8)g_Minigame.selectedDifficulty < maxLevel) {
                    g_Minigame.selectedDifficulty++;
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                }
            }
            g_Minigame.targetParticipantCount = minigameParticipantCounts[g_Minigame.GameMode_MiniGame * 5 + (s8)g_Minigame.selectedDifficulty];
        }
    } else if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 90) {
        g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_6;
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
    }
tail:
    if (g_d_GameSettings.exhibitionMatchInd != FALSE) {
        if (g_Minigame.charSelectState == 1 || (u8)(g_Minigame.charSelectState - 2) <= 2 || g_Minigame.charSelectState == 5) {
            if (g_GameLogic.FrameCountOfCurrentAtBat_Copy >= 30) {
                sel[0] = -1;
                sel[1] = -1;
                sel[2] = -1;
                sel[3] = -1;
                for (i = 0; i < 4; i++) {
                    sel[i] = -1;
                    if (g_Minigame.selectSlotState[i] == 0 && (g_Controls[i].newButtonInput & INPUT_BUTTON_A)) {
                        if (g_Minigame.selectSlots[i].charID >= 0) {
                            if (g_Minigame.selectSlots[i].confirmedInd == 1) {
                                addOrRemoveCharacterToTeam(i, g_Minigame.selectSlots[i].charID, FALSE);
                            }
                            if (g_Minigame.selectSlots[i].loadedCharID != CHAR_ID_NONE) {
                                g_Minigame.selectSlots[i].charID = CHAR_ID_NONE;
                                g_Minigame.selectSlots[i].loadedCharID = CHAR_ID_NONE;
                                g_Minigame.charLoadPending[i] = 1;
                                g_Minigame.selectSlots[i].confirmedInd = 0;
                            }
                        }
                        g_Minigame.selectSlotState[i] = 0;
                        g_Minigame.selectSlots[i].charID = CHAR_ID_NONE;
                        g_Minigame.selectSlots[i].loadedCharID = CHAR_ID_NONE;
                        sel[i] = -3;
                        break;
                    }
                }
                if (i < 4) {
                    for (k = 0; k < 4; k++) {
                        if (g_Minigame.selectSlotState[k] == 1) {
                            if (g_Minigame.selectSlots[k].charID >= 0) {
                                if (g_Minigame.selectSlots[k].confirmedInd == 1) {
                                    addOrRemoveCharacterToTeam(k, g_Minigame.selectSlots[k].charID, FALSE);
                                }
                                if (g_Minigame.selectSlots[k].loadedCharID != CHAR_ID_NONE) {
                                    g_Minigame.selectSlots[k].charID = CHAR_ID_NONE;
                                    g_Minigame.selectSlots[k].loadedCharID = CHAR_ID_NONE;
                                    g_Minigame.charLoadPending[k] = 1;
                                    g_Minigame.selectSlots[k].confirmedInd = 0;
                                }
                            }
                            g_Minigame.selectSlotState[k] = -1;
                        }
                    }
                    cssLoadingRelated_1(0, sel[0], sel[1], sel[2], sel[3], 0);
                    g_Minigame.joinedPlayerCount++;
                    sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                    g_Minigame.charSelectState = 0;
                }
            }
        }
    }
}

void minigameCharLoadQueueUpdate(void) {
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
            if (g_Minigame.charLoadSlot != i) {
                s8 c = g_Minigame.selectSlots[i].charID;

                if (c != -1) {
                    if (c == g_Minigame.selectSlots[i].loadedCharID && g_Minigame.selectSlots[i].loadedHandedness == g_Minigame.battingHandedness[i]) {
                        continue;
                    }
                    g_Minigame.selectSlots[i].charReadyInd = 0;
                    if (g_Minigame.charChangeFrames[i] >= 20 || g_Minigame.charSelectState == 4) {
                        order[count].idx = i;
                        order[count].val = g_Minigame.charChangeFrames[i];
                        count++;
                        g_Minigame.selectSlots[i].wantedHandedness = g_Minigame.battingHandedness[i];
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
        g_Minigame.charLoadQueue[0] = -1;
        g_Minigame.charLoadQueue[1] = -1;
        g_Minigame.charLoadQueue[2] = -1;
        g_Minigame.charLoadQueue[3] = -1;
        offset = 0;
        if (g_Minigame.charLoadSlot >= 0) {
            g_Minigame.charLoadQueue[0] = g_Minigame.charLoadSlot;
            offset = 1;
        }
        for (k = 0; k < count; k++) {
            g_Minigame.charLoadQueue[offset + k] = order[k].idx;
        }
        if (g_Minigame.charLoadQueue[0] >= 0) {
            slot = g_Minigame.charLoadQueue[0];
            sel = slot;
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
                sel = 9;
            }
            if (g_Minigame.charLoadStartedInd == 0) {
                g_Minigame.charLoadStartedInd = 1;
                fn_80011B64(sel);
            }
            if (g_Minigame.selectSlots[slot].pendingCharID >= 0) {
                fontCharID = fn_80016710(g_Minigame.selectSlots[slot].pendingCharID, sel);
            } else {
                fontCharID = fn_80016710(g_Minigame.selectSlots[slot].charID, sel);
            }
            if (fontCharID != 0) {
                g_Minigame.selectSlots[slot].loadedCharID = g_Minigame.selectSlots[slot].pendingCharID;
                g_Minigame.selectSlots[slot].pendingCharID = CHAR_ID_NONE;
                hugeAnimStruct[0x2D77] = 0;
                g_Minigame.selectSlots[slot].loadedHandedness = g_Minigame.selectSlots[slot].wantedHandedness;
                g_Minigame.charLoadSlot = -1;
                g_Minigame.charLoadQueue[0] = -1;
                g_Minigame.charLoadPending[slot] = 0;
                g_Minigame.charLoadStartedInd = 0;
                fn_3_E1370(3);
                continue;
            }
            if (g_Minigame.selectSlots[slot].pendingCharID < 0) {
                g_Minigame.selectSlots[slot].pendingCharID = g_Minigame.selectSlots[slot].charID;
            }
            g_Minigame.selectSlots[slot].loadedCharID = CHAR_ID_NONE;
            g_Minigame.charLoadSlot = slot;
        }
        break;
    }
    for (i = 0; i < 4; i++) {
        if (g_Minigame.charLoadPending[i] != 0 && g_Minigame.selectSlots[i].charID == g_Minigame.selectSlots[i].loadedCharID) {
            g_Minigame.charLoadPending[i] = 0;
        }
    }
}

void minigameCharSelectReset(void) {
    int i;

    fn_8001CA40(0);
    for (i = 0; i < 4; i++) {
        fn_80011BE4(i);
        g_Minigame.selectSlots[i].confirmedInd = 0;
        g_Minigame.selectSlots[i].loadedCharID = CHAR_ID_NONE;
    }
}

void minigames_fillRoster(void) {
    minigamesFillRoster();
}

void minigames_loadCharStats(int slot, int charID) {
    CharacterStats* roster = &inMemRoster[0][slot];

    memcpy(roster, &((CharacterStats*)&Static_Stats_Tables)[charID], sizeof(CharacterStats));
    if (g_Minigame.playerSlots.superstarBoostInd[slot] != 0) {
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
        for (i = 0; i < minigameChallengeOpponentPools[0]; i++) {
            pool[i] = minigameChallengeOpponentPools[i + 1];
        }
    } else if (g_Minigame.grandPrixInd != 0) {
        for (i = 0; i < 12; i++) {
            pool[i] = lbl_800E854C[i];
        }
        shuffleIntArray(pool, 12, FALSE);
    } else {
        u8 mode = g_Minigame.GameMode_MiniGame;

        if ((mode == MINI_GAME_ID_BOBOMB_DERBY || mode == MINI_GAME_ID_BARREL_BATTER) && g_Minigame.soloPlayerSlot >= 0) {
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
                u8* row = minigame_exhibitionOpponentCharIDs + idx * 6;

                for (i = 0; i < 6; i++) {
                    pool[i] = row[i];
                }
            }
        }
        shuffleIntArray(pool, count, FALSE);
    }

    cursor = 0;
    for (i = 0; i < 4; i++) {
        if (g_Minigame.selectSlotState[i] != 0 && g_Minigame.selectSlots[i].confirmedInd == 0) {
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
            g_Minigame.charChangeFrames[i] = 20;
            g_Minigame.battingHandedness[i] =
                ((CharacterStats*)&Static_Stats_Tables)[pool[j]].stats.FieldingArm * 2 +
                ((CharacterStats*)&Static_Stats_Tables)[pool[j]].stats.BattingStance;
            cursor++;
        }
    }
}

void minigameReadySwitcher(void) {
    int i;

    switch (g_GameLogic._125) {
    case TRANSITION_CALCULATION_TYPE_0:
        hugeAnimStruct[0x307E] = 0;
        if ((g_Minigame.grandPrixInd == 0 || g_Minigame.grandPrixRound <= 1) && g_Minigame.retryInd == 0) {
            fn_80062A74();
            fn_800189B8();
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
                fn_80035B50(0x11);
            }
            fn_80035B50(9);
            fn_3_908E8();
        }
        g_Minigame.menuMusicStartedInd = 0;
        g_Minigame.hudEventType = 0;
        g_Minigame.multiPlayerInd = 0;
        g_Minigame.newRecordInd = 0;
        g_Minigame.soloPlayerSlot = -1;
        g_Minigame.helpMenuResult = 0;
        g_Minigame.toyField_settingsRow = 0;
        g_Minigame.toyField_inningOptions[0] = 2;
        g_Minigame.grandPrixNewBestInd[0] = 0;
        if (g_d_GameSettings.exhibitionMatchInd == FALSE) {
            g_Minigame.toyField_inningOptions[0] = 0;
        }
        g_d_GameSettings._3A = g_Minigame.soloMinigameDifficulty;
        lbl_8037169C[0x15] = 0;
        sound_crowd_EffectsStruct._2C = 0;
        if (g_Minigame.humanPlayerCount != 1 || g_Minigame.grandPrixInd != 0) {
            g_Minigame.multiPlayerInd = 1;
            g_Minigame.soloMinigameDifficulty = MINIGAME_DIFFICULTY_MULTIPLAYER_CHALLENGE_EASY;
        }
        if (g_Minigame.humanPlayerCount == 1) {
            for (i = 0; i < 4; i++) {
                if (g_Minigame.playerSlots.aiControlledInd[i] == 0) {
                    g_Minigame.soloPlayerSlot = i;
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
        if (g_Minigame.retryInd != 0 && g_Minigame.grandPrixInd == 0) {
            changeScene(1, 6);
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_2;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_1:
        if (diskReadRelated(CommonUIFiles_minigame[g_Minigame.GameMode_MiniGame + 6], 0x11)) {
            changeScene(1, 6);
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_GameLogic._125++;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_2:
        if (g_Minigame.retryInd != 0 && g_Minigame.grandPrixInd == 0) {
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_8;
        } else if (fn_3_90860()) {
            sound_crowd_EffectsStruct._2C = 0;
            g_GameLogic._125++;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_3:
        g_d_GameSettings.StadiumID = mapping_minigame_Stadium[g_Minigame.GameMode_MiniGame];
        if (fn_3_90A18()) {
            g_GameLogic._125++;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_4:
        fn_80018B74();
        g_GameLogic._125++;
        // fallthrough
    case TRANSITION_CALCULATION_TYPE_5:
        minigameStadiumSetup();
        g_GameLogic._125++;
        break;
    case TRANSITION_CALCULATION_TYPE_6:
        if (!minigames_isStadiumLoading()) {
            g_GameLogic._125++;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_7:
        if (fn_80020388()) {
            g_GameLogic._125++;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_8:
        if (g_Minigame.helpMenuResult != 0) {
            changeScene(3, 6);
            if (g_Minigame.helpMenuResult == 2) {
                g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_10;
            } else {
                g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_9;
            }
        }
        break;
    case TRANSITION_CALCULATION_TYPE_9:
        if (lbl_8037169C[0x13] != 0) {
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                g_Scores.inningLimit = g_Minigame.toyField_inningOptions[0] * 2 + 1;
                g_Scores.maxNumberOfExtraInnings = g_Minigame.toyField_inningOptions[0] * 2 + 1;
                SetGameStatus(GAME_STATUS_GAME_START_MOVIE);
            } else {
                SetGameStatus(GAME_STATUS_LOAD_GAME);
            }
            fn_3_BF070();
        }
        break;
    case TRANSITION_CALCULATION_TYPE_10:
        if (lbl_8037169C[0x13] != 0) {
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_11;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_11:
        g_Minigame.retryInd = 0;
        minigameBackToCharSelect();
        break;
    }
    if (g_GameLogic._125 >= 2 && g_Minigame.helpMenuResult == 0) {
        minigameHelpMenuUpdate();
    }
}

static inline void minigameOptionSetup(u8 selected) {
    int mode;
    int k;

    g_Minigame.helpPage = selected;
    g_Minigame.helpPageDelay = 0;
    g_Minigame.helpPageMode = 0;
    g_Minigame.helpPageDirLeft = 0;
    if (g_Minigame.multiPlayerInd != 0) {
        g_Minigame.helpPageMode = 2;
    } else if (g_Minigame.soloMinigameDifficulty == MINIGAME_DIFFICULTY_SOLO_NON_CHALLENGE) {
        g_Minigame.helpPageMode = 1;
    }
    mode = g_Minigame.GameMode_MiniGame;
    if (g_GameLogic.gameStatus == GAME_STATUS_0x28) {
        mode = MINI_GAME_ID_MARIO_GRAND_PRIX;
    }
    g_Minigame.helpPageCount = 0;
    for (k = 0; k < 5; k++) {
        if (minigameHelpPageIDs[mode][g_Minigame.helpPageMode][k] >= 0) {
            g_Minigame.helpPageCount++;
        }
    }
}

void minigameHelpMenuUpdate(void) {
    if (g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
        minigameOptionSetup(0);
    }
    if (lbl_8037169C[0x12] == 0) {
        return;
    }
    if (g_Minigame.helpPageDelay != 0) {
        g_Minigame.helpPageDelay--;
        return;
    }
    if (g_Minigame.helpPage == 0) {
        if (checkForButtonPressToSkip(1, INPUT_BUTTON_B)) {
            if (g_Minigame.grandPrixInd == 0 || g_GameLogic.gameStatus == GAME_STATUS_0x28) {
                g_Minigame.helpMenuResult = 2;
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            }
            return;
        }
        if (g_GameLogic._125 >= 8 || g_GameLogic.gameStatus == GAME_STATUS_0x28) {
            if (checkForButtonPressToSkip(1, INPUT_BUTTON_A)) {
                if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                    if (g_Minigame.toyField_settingsRow != 0) {
                        return;
                    }
                    g_Minigame.helpMenuResult = 1;
                    sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                } else {
                    g_Minigame.helpMenuResult = 1;
                    sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                }
                return;
            }
        }
        if (checkForButtonPressToSkip(2, INPUT_TRIGGER_R)) {
            g_Minigame.helpPage = 1;
            g_Minigame.helpPageDirLeft = 0;
            g_Minigame.helpPageDelay = 30;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            return;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && g_d_GameSettings.exhibitionMatchInd != FALSE) {
            if (checkForButtonPressToSkip(2, INPUT_BUTTON_UP) && g_Minigame.toyField_settingsRow == 1) {
                g_Minigame.toyField_settingsRow = 0;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            } else if (checkForButtonPressToSkip(2, INPUT_BUTTON_DOWN) && g_Minigame.toyField_settingsRow == 0) {
                g_Minigame.toyField_settingsRow = 1;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            } else if (g_Minigame.toyField_settingsRow == 1) {
                if (checkForButtonPressToSkip(2, INPUT_BUTTON_LEFT)) {
                    if (g_Minigame.toyField_inningOptions[0] == 0) {
                        g_Minigame.toyField_inningOptions[0] = 4;
                    } else {
                        g_Minigame.toyField_inningOptions[0]--;
                    }
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                } else if (checkForButtonPressToSkip(2, INPUT_BUTTON_RIGHT)) {
                    if (g_Minigame.toyField_inningOptions[0] == 4) {
                        g_Minigame.toyField_inningOptions[0] = 0;
                    } else {
                        g_Minigame.toyField_inningOptions[0]++;
                    }
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                }
            }
        }
    } else {
        if (g_GameLogic._125 >= 8 || g_GameLogic.gameStatus == GAME_STATUS_0x28) {
            if (checkForButtonPressToSkip(0, INPUT_BUTTON_A)) {
                g_Minigame.helpMenuResult = 1;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                return;
            }
        }
        if (checkForButtonPressToSkip(2, INPUT_BUTTON_B | INPUT_TRIGGER_R)) {
            g_Minigame.helpPage = 0;
            g_Minigame.helpPageDirLeft = 0;
            g_Minigame.helpPageDelay = 30;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (g_Minigame.helpPageCount > 1) {
            if (checkForButtonPressToSkip(2, INPUT_BUTTON_RIGHT)) {
                if (g_Minigame.helpPage == g_Minigame.helpPageCount) {
                    g_Minigame.helpPage = 1;
                } else {
                    g_Minigame.helpPage++;
                }
                g_Minigame.helpPageDirLeft = 0;
                g_Minigame.helpPageDelay = 20;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            } else if (checkForButtonPressToSkip(2, INPUT_BUTTON_LEFT)) {
                if (g_Minigame.helpPage == 1) {
                    g_Minigame.helpPage = g_Minigame.helpPageCount;
                } else {
                    g_Minigame.helpPage--;
                }
                g_Minigame.helpPageDirLeft = 1;
                g_Minigame.helpPageDelay = 20;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    }
}

void minigameBackToCharSelect(void) {
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
    g_Minigame.nextGameStatus = GAME_STATUS_TOY_STADIUM_CHARACTER_SELECT;
    SetGameStatus(GAME_STATUS_TOY_STADIUM_LOAD);
}

void minigameStartSwitcher(void) {
    int i;

    switch (g_GameLogic._125) {
    case TRANSITION_CALCULATION_TYPE_0:
        challenge_setTransitionScreenCharacterPortrait(7, 0);
        g_Minigame.minigameInactiveInd = 0;
        g_Minigame._19A7 = lbl_3_data_21270[g_Minigame.GameMode_MiniGame];
        g_Minigame.grandPrixFinalInd = 0;
        hugeAnimStruct[0x307E] = 1;
        hugeAnimStruct[0x2D8E] = 0;
        g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_1;
        if (g_d_GameSettings.exhibitionMatchInd == FALSE) {
            g_d_GameSettings._36 = g_Minigame.playerSlots.charID[g_Minigame.soloPlayerSlot];
        }
        break;
    case TRANSITION_CALCULATION_TYPE_1:
        minigameCharLoadQueueUpdate();
        if (g_Minigame.charLoadQueue[0] < 0) {
            fn_3_E1370(lbl_3_data_18918[g_Minigame.GameMode_MiniGame]);
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_2;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_2:
        if (fn_80016F7C()) {
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_3;
            sound_crowd_EffectsStruct._2C = 0;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_3:
        if (fn_3_90DD8()) {
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_5;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_5:
        g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_6;
        break;
    case TRANSITION_CALCULATION_TYPE_6:
        if (lbl_8037169C[0x12] == 0) {
            return;
        }
        if (g_GameLogic.FrameCountOfCurrentPitch >= minigameTuningConstants[2] ||
            (g_GameLogic.FrameCountOfCurrentPitch >= minigameTuningConstants[1] && checkForButtonPressToSkip(2, 0x1100))) {
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_7;
            changeScene(3, 6);
            fn_8003A540(0);
        }
        break;
    case TRANSITION_CALCULATION_TYPE_7:
        if (lbl_8037169C[0x13] != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_8;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_8:
        g_Minigame.retryInd = 0;
        g_Minigame.nextDifficultyInd = 0;
        hugeAnimStruct[0x307A] = 1;
        for (i = 0; i < 4; i++) {
            if (g_Minigame.playerSlots.characterIndex[i] >= 0) {
                g_Minigame.playerSlots.playOrder[i] = i;
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

void minigames_0x23(void) {
    minigames_shufflePlayOrder();
    SetGameStatus(GAME_STATUS_TRANSITION_MINIGAME_TO_BATTING);
}

void minigames_shufflePlayOrder(void) {
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
    g_Minigame.playerSlots.playOrder[0] = order[0];
    g_Minigame.playerSlots.playOrder[1] = order[1];
    g_Minigame.playerSlots.playOrder[2] = order[2];
    g_Minigame.playerSlots.playOrder[3] = order[3];
}

static inline void awardMinigameCoins(void) {
    int i;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        if (g_Minigame.challenge_minigame_haven_tWonYetIndicator == 0) {
            if (g_Minigame.playerSlots.rank[g_d_GameSettings._35] == 1) {
                g_d_GameSettings.challengeMinigame_baseCoinsEarned += g_Minigame.miniGameCurrentPoints[g_d_GameSettings._35];
            } else {
                g_d_GameSettings.challengeMinigame_baseCoinsEarned += challenge_baseCoinsAwarded[15];
            }
        }
    } else if (g_Minigame.challenge_minigame_haven_tWonYetIndicator != 0) {
        g_d_GameSettings.challengeMinigame_baseCoinsEarned += challenge_baseCoinsAwarded[7];
    } else if (g_Minigame.playerSlots.rank[g_d_GameSettings._35] == 1) {
        for (i = 0; i < 4; i++) {
            if (g_Minigame.playerSlots.rank[i] > 1) {
                break;
            }
        }
        g_d_GameSettings.challengeMinigame_baseCoinsEarned += challenge_baseCoinsAwarded[6];
    } else if (g_d_GameSettings.challengeDifficulty != 0) {
        g_d_GameSettings.challengeMinigame_baseCoinsEarned += challenge_baseCoinsAwarded[8];
    }
    g_d_GameSettings._20[0][0] = g_Minigame.miniGameCurrentPoints[0];
    g_d_GameSettings._20[0][1] = g_Minigame.playerSlots.rank[0];
    g_d_GameSettings._20[1][0] = g_Minigame.miniGameCurrentPoints[1];
    g_d_GameSettings._20[1][1] = g_Minigame.playerSlots.rank[1];
    g_d_GameSettings._20[2][0] = g_Minigame.miniGameCurrentPoints[2];
    g_d_GameSettings._20[2][1] = g_Minigame.playerSlots.rank[2];
    g_d_GameSettings._20[3][0] = g_Minigame.miniGameCurrentPoints[3];
    g_d_GameSettings._20[3][1] = g_Minigame.playerSlots.rank[3];
    starMissionsMinigamesTotalPoints();
}

static inline void buildResultEntry(MinigameResultEntry* out) {
    memset(out, 0, sizeof(MinigameResultEntry));
    if (g_Minigame.humanPlayerCount == 1) {
        out->charID = inMemRoster[0][g_Minigame.playerSlots.characterIndex[g_Minigame.soloPlayerSlot]].stats.CharID;
        if (g_Minigame.grandPrixInd != 0) {
            MiniGrandPrixScoreInput input;

            minigameFillGrandPrixScoreInput(&input);
            out->score = (s16)fn_8006C13C(&input);
            out->count = 0;
        } else {
            out->score = g_Minigame.miniGameCurrentPoints[g_Minigame.soloPlayerSlot];
            if (out->score > lbl_80109410[g_Minigame.GameMode_MiniGame]) {
                out->score = lbl_80109410[g_Minigame.GameMode_MiniGame];
            }
            switch (g_Minigame.GameMode_MiniGame) {
            case MINI_GAME_ID_BOBOMB_DERBY:
                out->count = g_Minigame.bOD_HitPowerOfEachChar[g_Minigame.soloPlayerSlot];
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

void minigameEndSwitcher(void) {
    MinigameResultEntry entry;
    BOOL eligible;
    int rank;
    int i;
    u8* count;

    switch (g_GameLogic._125) {
    case TRANSITION_CALCULATION_TYPE_0:
        animRelated[0xB8] = 0;
        g_Minigame.endSequencePhase = 1;
        g_Minigame.newRecordInd = 0;
        g_Minigame.difficultyUnlockedInd = 0;
        g_Minigame.grandPrixUnlockedInd = 0;
        g_Minigame.newRecordRank = 0;
        g_Minigame.grandPrixFinalHumanCount = 0;
        if (g_d_GameSettings.exhibitionMatchInd == FALSE) {
            awardMinigameCoins();
        } else if (g_Minigame.soloMinigameDifficulty == MINIGAME_DIFFICULTY_SOLO_NON_CHALLENGE ||
                   g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
            eligible = TRUE;
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                if (g_Minigame.soloPlayerSlot < 0) {
                    eligible = FALSE;
                }
            } else if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_WALLBALL || g_Minigame.GameMode_MiniGame == MINI_GAME_ID_CHAINCHOMP_SPRINT ||
                       g_Minigame.GameMode_MiniGame == MINI_GAME_ID_PIRANHA_PANIC || g_Minigame.GameMode_MiniGame == MINI_GAME_ID_STAR_DASH) {
                if (g_Minigame.playerSlots.rank[g_Minigame.soloPlayerSlot] > 1) {
                    eligible = FALSE;
                }
            }
            if (eligible) {
                buildResultEntry(&entry);
                rank = minigameGetScoreRank(&entry);
                if (rank >= 5) {
                    g_Minigame.newRecordRank = 0;
                } else {
                    g_Minigame.newRecordRank = rank + 1;
                    g_Minigame.newRecordInd = 1;
                }
            }
        } else if (g_Minigame.winLossResult == 1 && g_d_GameSettings.exhibitionMatchInd != FALSE &&
                   g_Minigame.GameMode_MiniGame >= MINI_GAME_ID_BOBOMB_DERBY && g_Minigame.GameMode_MiniGame <= MINI_GAME_ID_STAR_DASH) {
            count = &((u8*)&g_d_GameSettings)[g_Minigame.GameMode_MiniGame + 0x13];
            if (*count == g_Minigame.soloMinigameDifficulty) {
                (*count)++;
                g_Minigame.difficultyUnlockedInd = 1;
                for (i = 0; i < 6; i++) {
                    if (((u8*)&g_d_GameSettings)[0x14 + i] < 3) {
                        break;
                    }
                }
                if (i >= 6) {
                    g_Minigame.grandPrixUnlockedInd = 2;
                    g_d_GameSettings._12 = 2;
                }
            }
        }
        transitionToReplay();
        fn_3_5B368();
        changeScene(1, 6);
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_1;
        break;
    case TRANSITION_CALCULATION_TYPE_1:
        g_Minigame.endSequencePhase = 2;
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        if (g_Minigame.winLossResult == 0) {
            newAtBatPlaySound();
        }
        g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_2;
        break;
    case TRANSITION_CALCULATION_TYPE_2:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy == minigameResultsFrames[1]) {
            animRelated[0xB8] = 1;
        }
        if (g_Minigame.difficultyUnlockedInd == 1) {
            if (g_GameLogic.FrameCountOfCurrentPitch > 300) {
                g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_5;
                g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            }
        } else if (g_Minigame.grandPrixUnlockedInd != 0) {
            if (g_GameLogic.FrameCountOfCurrentPitch > 300) {
                g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_6;
                g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            }
        } else if (g_GameLogic.FrameCountOfCurrentPitch > 300) {
            if (g_d_GameSettings.exhibitionMatchInd == FALSE) {
                if (g_GameLogic.FrameCountOfCurrentPitch > 420) {
                    g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_3;
                }
            } else if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY &&
                       g_Minigame.soloMinigameDifficulty == MINIGAME_DIFFICULTY_SOLO_NON_CHALLENGE &&
                       checkForButtonPressToSkip(0, INPUT_TRIGGER_Z) && checkForButtonPressToSkip(0, INPUT_BUTTON_Y) &&
                       checkForButtonPressToSkip(0, INPUT_BUTTON_B)) {
                sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
                g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_7;
            } else if (checkForButtonPressToSkip(1, INPUT_BUTTON_A | INPUT_BUTTON_START)) {
                g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_3;
            }
        }
        break;
    case TRANSITION_CALCULATION_TYPE_7:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 30) {
            if (checkForButtonPressToSkip(1, INPUT_BUTTON_B)) {
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                g_GameLogic.FrameCountOfCurrentPitch = 270;
                g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_2;
            }
        }
        break;
    case TRANSITION_CALCULATION_TYPE_5:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
            fn_8004CC4C(9, 0, ((u8*)&g_d_GameSettings)[g_Minigame.GameMode_MiniGame + 0x13] - 1, 0,
                        ((u8*)&g_d_GameSettings)[g_Minigame.GameMode_MiniGame + 0x13] + 0x8C);
            insertGraphicDrawingFunction(fn_8004D0F0, 2);
            g_GameLogic.scoreBook_logoFadeDirectionLeft_Right = 0;
            callSfx(0x301);
        } else if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 150) {
            if (checkForButtonPressToSkip(1, INPUT_BUTTON_A | INPUT_BUTTON_START)) {
                set803c5f77();
                g_GameLogic.scoreBook_logoFadeDirectionLeft_Right = 1;
            } else if (g_GameLogic.scoreBook_logoFadeDirectionLeft_Right != 0 && lbl_803C5F74.state == 4) {
                if (g_Minigame.grandPrixUnlockedInd != 0) {
                    g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                    g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_6;
                } else {
                    g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_3;
                }
            }
        }
        break;
    case TRANSITION_CALCULATION_TYPE_6:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
            fn_8004CC4C(9, 0, 4, 0, 0x91);
            insertGraphicDrawingFunction(fn_8004D0F0, 2);
            g_GameLogic.scoreBook_logoFadeDirectionLeft_Right = 0;
        } else if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 150) {
            if (checkForButtonPressToSkip(1, INPUT_BUTTON_A | INPUT_BUTTON_START)) {
                set803c5f77();
                g_GameLogic.scoreBook_logoFadeDirectionLeft_Right = 1;
            } else if (g_GameLogic.scoreBook_logoFadeDirectionLeft_Right != 0 && lbl_803C5F74.state == 4) {
                g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_3;
            }
        }
        break;
    case TRANSITION_CALCULATION_TYPE_3:
        if (g_Minigame.difficultyUnlockedInd != 0 || g_Minigame.grandPrixUnlockedInd != 0) {
            if (fn_3_5B220(1)) {
                g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_4;
            }
        } else {
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_4;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_4:
        if (g_Minigame.challengeModeInd != 0) {
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_9;
        } else {
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_8;
        }
        newAtBatPlaySound();
        break;
    case TRANSITION_CALCULATION_TYPE_8:
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
            pauseControl.state = 0;
            if (g_Minigame.soloPlayerSlot >= 0) {
                SetGameStatus(GAME_STATUS_0x24);
            } else {
                SetGameStatus(GAME_STATUS_MINIGAME_POST_MENU);
            }
        } else if (g_Minigame.multiPlayerInd == 0 && g_Minigame.grandPrixInd == 0 &&
                   g_Minigame.soloMinigameDifficulty == MINIGAME_DIFFICULTY_SOLO_NON_CHALLENGE) {
            SetGameStatus(GAME_STATUS_0x24);
        } else {
            pauseControl._1D1 = 0;
            pauseControl.state = 0;
            if (g_Minigame.grandPrixInd != 0) {
                SetGameStatus(GAME_STATUS_0x26);
            } else {
                SetGameStatus(GAME_STATUS_MINIGAME_POST_MENU);
            }
        }
        break;
    case TRANSITION_CALCULATION_TYPE_9:
        challenge_setTransitionScreenCharacterPortrait(12, (s8)challengeTransitionPortraitIDs[((u8*)starMissionCompletionTracker)[0x441C]]);
        if (lbl_8037169C[0x13] != 0) {
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_10;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_10:
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY || g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER) {
            if (g_Minigame.winLossResult != 0) {
                g_d_GameSettings._38 = 1;
            } else {
                g_d_GameSettings._38 = 0;
            }
        } else if (g_Minigame.challenge_minigame_haven_tWonYetIndicator != 0) {
            g_d_GameSettings._38 = 0;
        } else {
            g_d_GameSettings._38 = g_Minigame.playerSlots.rank[g_d_GameSettings._35];
        }
        fn_3_15F998();
        fn_3_147DFC();
        mm_UnloadModels();
        g_GameLogic.framesOfExitingToMenu = 1;
        break;
    }
    minigameEndHook();
}

void minigameEndHook(void) {
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

void minigameBuildResultEntry(MinigameResultEntry* out) {
    buildResultEntry(out);
}

MinigameResultEntry* minigameGetScoreTable(void) {
    if (g_Minigame.grandPrixInd != 0) {
        return &lbl_803616CC[7][0];
    }
    if (g_Minigame.GameMode_MiniGame != 0) {
        return &lbl_803616CC[g_Minigame.GameMode_MiniGame - 1][5];
    }
    return &lbl_803616CC[0][0];
}

int minigameGetScoreRank(MinigameResultEntry* entry) {
    MinigameResultEntry* table;
    u32 i;

    if (g_Minigame.humanPlayerCount != 1) {
        return;
    }
    table = minigameGetScoreTable();
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

void minigameUpdateHighScores(void) {
    MinigameResultEntry entry;
    MiniGrandPrixScoreInput input;
    MiniGrandPrixScoreInput* best;
    MinigameResultEntry* table;
    u32 rank;
    u32 i;
    int category;
    s8* bestPlace;

    g_Minigame.newRecordRow = 5;
    if (g_Minigame.humanPlayerCount != 1) {
        return;
    }
    if (g_Minigame.grandPrixInd == 0 &&
        (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_CHAINCHOMP_SPRINT || g_Minigame.GameMode_MiniGame == MINI_GAME_ID_PIRANHA_PANIC ||
         g_Minigame.GameMode_MiniGame == MINI_GAME_ID_STAR_DASH) &&
        g_Minigame.playerSlots.rank[g_Minigame.soloPlayerSlot] != 1) {
        return;
    }
    buildResultEntry(&entry);
    rank = minigameGetScoreRank(&entry);
    g_Minigame.newRecordRow = rank;
    if (rank < 5) {
        table = minigameGetScoreTable();
        for (i = 4; i > rank; i--) {
            memcpy(&table[i], &table[i - 1], sizeof(MinigameResultEntry));
        }
        memcpy(&table[rank], &entry, sizeof(MinigameResultEntry));
        g_Minigame.newRecordRank = rank + 1;
    }
    if (g_Minigame.grandPrixInd != 0) {
        minigameFillGrandPrixScoreInput(&input);
        category = characterStaticIndexes[input.charID * 6 + 2];
        best = (MiniGrandPrixScoreInput*)((u8*)lbl_803616CC + 0x140) + category;
        if ((s16)fn_8006C13C(&input) > (s16)fn_8006C13C(best)) {
            minigameFillGrandPrixScoreInput(best);
            g_Minigame.grandPrixNewBestInd[0] = 1;
        } else if ((s16)fn_8006C13C(&input) == (s16)fn_8006C13C(best) && input.placeRank < best->placeRank) {
            minigameFillGrandPrixScoreInput(best);
            g_Minigame.grandPrixNewBestInd[0] = 1;
        }
        bestPlace = (s8*)lbl_803616CC + 0x400 + category;
        if (3 - *bestPlace > input.placeRank) {
            *bestPlace = 3 - input.placeRank;
            g_Minigame.grandPrixNewBestInd[0] = 1;
        }
    }
}

void minigameResultsSwitcher(void) {
    InputStruct* input = &g_Controls[lbl_80366158[0x27]];

    switch (g_GameLogic._125) {
    case TRANSITION_CALCULATION_TYPE_0:
        fn_3_5B368();
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        if (g_Minigame.humanPlayerCount == 1) {
            minigameUpdateHighScores();
            if (g_Minigame.grandPrixInd != 0) {
                g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_1;
            } else {
                g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_5;
            }
        } else {
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_5;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_1:
        if (g_Minigame.resultsScene->_18 != 0) {
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 30;
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_2;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_2:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy >= 30) {
            if ((input->buttonInput & INPUT_TRIGGER_Z) && (input->buttonInput & INPUT_BUTTON_Y) &&
                (input->buttonInput & INPUT_BUTTON_B)) {
                sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
                g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_3;
            } else if (input->newButtonInput & (INPUT_BUTTON_A | INPUT_BUTTON_START)) {
                g_Minigame.resultsScene->_1A = 1;
                g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_4;
            }
        }
        break;
    case TRANSITION_CALCULATION_TYPE_3:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 30) {
            if (input->newButtonInput & INPUT_BUTTON_B) {
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_2;
            }
        }
        break;
    case TRANSITION_CALCULATION_TYPE_4:
        if (g_Minigame.resultsScene == NULL) {
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_5;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_5:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 20) {
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_6;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_6:
        if (input->newButtonInput & (INPUT_BUTTON_A | INPUT_BUTTON_START)) {
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_7;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_7:
        if (g_Minigame.difficultyUnlockedInd != 0 || g_Minigame.grandPrixUnlockedInd != 0 || g_Minigame.newRecordRank != 0 || g_Minigame.grandPrixNewBestInd[0] != 0) {
            if (fn_3_5B220(1)) {
                g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_8;
                g_Minigame.grandPrixNewBestInd[0] = 0;
            }
        } else {
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_8;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_8:
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_9;
        break;
    case TRANSITION_CALCULATION_TYPE_9:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 20) {
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_10;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_10:
        pauseControl._1D1 = 0;
        pauseControl.state = 0;
        SetGameStatus(GAME_STATUS_MINIGAME_POST_MENU);
        break;
    }
}

void postMinigame(void) {
    int i;
    u32 k;
    CharacterStats* stats;

    SATURATING_INCREMENT(pauseControl._00A);
    SATURATING_INCREMENT(pauseControl.counter);
    SATURATING_INCREMENT(pauseControl._12);
    switch (pauseControl.state) {
    case 0:
        if (g_Minigame.multiPlayerInd != 0 || ((u8*)&g_d_GameSettings)[0x13 + g_Minigame.GameMode_MiniGame] == 0) {
            pauseControl._1D0 = 12;
        } else if (g_Minigame.difficultyUnlockedInd != 0) {
            pauseControl._1D0 = 11;
        } else {
            pauseControl._1D0 = 10;
        }
        if (g_Minigame.grandPrixInd != 0) {
            if (g_Minigame.grandPrixRound >= 6) {
                pauseControl._1D0 = 15;
            } else {
                pauseControl._1D0 = 14;
            }
        }
        pauseControl._00A = 0;
        pauseControl.counter = 0;
        pauseControl.cursor = 0;
        pauseControl.state = 1;
        break;
    case 1:
        pauseControl.counter = 0;
        pauseControl.state = 2;
        break;
    case 2:
        if (pauseControl.counter >= 20) {
            pauseControl.state = 3;
        }
        break;
    case 3:
        postMinigameMenuUpdate();
        pauseControl.counter = 0;
        pauseControl._12 = 0;
        break;
    case 6:
        changeScene(3, 6);
        if (lbl_8037169C[0x13] != 0) {
            pauseControl.state = 7;
        }
        break;
    case 7:
        if (g_Minigame.grandPrixInd != 0) {
            if (g_Minigame.grandPrixRound >= 6) {
                if (pauseControl.cursor == 0) {
                    g_Minigame.retryInd = 1;
                    minigameStartGrandPrix();
                    SetGameStatus(GAME_STATUS_0x29);
                } else if (pauseControl.cursor == 1) {
                    g_Minigame.nextGameStatus = GAME_STATUS_TOY_STADIUM_CHARACTER_SELECT;
                    SetGameStatus(GAME_STATUS_TOY_STADIUM_LOAD);
                } else {
                    g_Minigame.nextGameStatus = GAME_STATUS_MINIGAME_SELECT;
                    SetGameStatus(GAME_STATUS_TOY_STADIUM_LOAD);
                }
                fn_3_FBD70();
                fn_3_FBD58();
            } else if (pauseControl.cursor == 0) {
                SetGameStatus(GAME_STATUS_0x29);
            } else {
                SetGameStatus(GAME_STATUS_TOY_STADIUM_LOAD);
            }
        } else {
            switch ((postMinigameMenuActions + pauseControl._1D0 * 5)[pauseControl.cursor - 0x32]) {
            case 0:
                g_Minigame.retryInd = 1;
                SetGameStatus(GAME_STATUS_LOAD_GAME);
                break;
            case 1:
                g_Minigame.nextGameStatus = GAME_STATUS_TOY_STADIUM_CHARACTER_SELECT;
                SetGameStatus(GAME_STATUS_TOY_STADIUM_LOAD);
                break;
            case 2:
                g_Minigame.nextGameStatus = GAME_STATUS_TOY_STADIUM_CHARACTER_SELECT;
                g_Minigame.charReselectInd = 1;
                SetGameStatus(GAME_STATUS_TOY_STADIUM_LOAD);
                break;
            case 3:
                g_Minigame.nextGameStatus = GAME_STATUS_MINIGAME_SELECT;
                SetGameStatus(GAME_STATUS_TOY_STADIUM_LOAD);
                break;
            case 5:
                g_Minigame.retryInd = 1;
                g_Minigame.soloMinigameDifficulty++;
                g_Minigame.nextDifficultyInd = 1;
                SetGameStatus(GAME_STATUS_MINIGAME_READY);
                break;
            }
        }
        mm_UnloadModels();
        if (g_Minigame.nextDifficultyInd != 0) {
            minigames_pickOpponentsAndLoadStats();
            g_Minigame.miniGameNumberOfParticipants = minigameParticipantCounts[g_Minigame.GameMode_MiniGame * 5 + g_Minigame.soloMinigameDifficulty];
            for (i = 0; i < 4; i++) {
                if (g_Minigame.playerSlots.aiControlledInd[i] != 0) {
                    if (g_Minigame.miniGameNumberOfParticipants == 1) {
                        g_Minigame.playerSlots.characterIndex[i] = -1;
                    } else {
                        stats = &((CharacterStats*)&Static_Stats_Tables)[g_Minigame.selectSlots[g_Minigame.playerSlots.characterIndex[i]].charID];
                        memcpy(&inMemRoster[0][g_Minigame.playerSlots.characterIndex[i]], stats, sizeof(CharacterStats));
                        g_Minigame.battingHandedness[i] = stats->stats.FieldingArm * 2 + stats->stats.BattingStance;
                        g_Minigame.playerSlots.charID[i] = inMemRoster[0][g_Minigame.playerSlots.characterIndex[i]].stats.CharID;
                    }
                }
            }
        }
        g_Minigame.minigameInactiveInd = 1;
        g_Minigame.endSequencePhase = 0;
        fn_3_15F998();
        fn_3_147DFC();
        hugeAnimStruct[0x307A] = 0;
        pauseControl._1D9 = 2;
        break;
    case 8:
        switch (((int (*)(u16))exitMenu_main)(g_Controls[pauseControl.port].newButtonInput)) {
        case 1:
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            pauseControl.state = 9;
            break;
        case 2:
            pauseControl.state = 3;
            break;
        }
        break;
    case 9:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 45) {
            changeScene(4, 6);
        }
        if (lbl_8037169C[0x13] != 0) {
            g_Minigame.minigameInactiveInd = 1;
            pauseControl._1D9 = 2;
            fn_3_15F998();
            fn_3_147DFC();
            mm_UnloadModels();
            fn_8004CC18();
            g_GameLogic.framesOfExitingToMenu = 1;
        }
        break;
    }
}

void postMinigameMenuUpdate(void) {
    int count;
    int menu;
    int pressed;
    u8 type;

    count = 5;
    type = pauseControl._1D0;
    menu = type - 10;
    if (g_Minigame.grandPrixInd != 0) {
        if (g_Minigame.grandPrixRound >= 6) {
            count = 4;
        } else {
            count = 3;
        }
    } else if (type == 12) {
        count = 4;
    }
    pressed = checkForButtonPressToSkip(1, INPUT_BUTTON_A);
    if (pressed != 0) {
        if (g_Minigame.grandPrixInd != 0) {
            if (g_Minigame.grandPrixRound >= 6) {
                s8 cursor = pauseControl.cursor;

                if (cursor == 3) {
                    pauseControl.state = 8;
                } else if (cursor == 1) {
                    pauseControl.state = 6;
                } else {
                    pauseControl.state = 6;
                }
            } else if (pauseControl.cursor == 2) {
                pauseControl.state = 8;
            } else {
                pauseControl.state = 6;
            }
        } else {
            switch ((postMinigameMenuActions + menu * 5)[pauseControl.cursor]) {
            case 4:
                pauseControl.state = 8;
                break;
            default:
                pauseControl.state = 6;
                break;
            }
        }
        pauseControl.port = pressed - 1;
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        if (pauseControl.state == 8) {
            fn_3_5B408();
        }
    } else if (checkForButtonPressToSkip(2, INPUT_BUTTON_UP)) {
        if (pauseControl.cursor == 0) {
            pauseControl.cursor = count - 1;
        } else {
            pauseControl.cursor--;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (checkForButtonPressToSkip(2, INPUT_BUTTON_DOWN)) {
        if (pauseControl.cursor < count - 1) {
            pauseControl.cursor++;
        } else {
            pauseControl.cursor = 0;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
}

BOOL checkForPauses(void) {
    int i;

    if (g_Minigame.turnOverStatus != 0) {
        return FALSE;
    }
    for (i = 0; i < 4; i++) {
        if (g_Minigame.playerSlots.characterIndex[i] >= 0 && g_Minigame.playerSlots.aiControlledInd[i] == 0 &&
            (g_Controls[g_Minigame.playerSlots.characterIndex[i]].newButtonInput & INPUT_BUTTON_START)) {
            break;
        }
    }
    if (i >= 4) {
        return FALSE;
    }
    g_Minigame.pauseInd = 1;
    pauseControl.port = g_Minigame.playerSlots.characterIndex[i];
    pauseControl._00A = 0;
    if (g_d_GameSettings.exhibitionMatchInd == FALSE) {
        pauseControl._1D0 = 16;
    } else if (g_Minigame.grandPrixInd != 0) {
        pauseControl._1D0 = 13;
    } else {
        pauseControl._1D0 = 9;
    }
    pauseControl.state = 0;
    pauseControl.cursor = 0;
    return TRUE;
}

void minigamePause(void) {
    lbl_80366158[0x28] = 1;
    SATURATING_INCREMENT(pauseControl._00A);
    SATURATING_INCREMENT(pauseControl.counter);
    SATURATING_INCREMENT(pauseControl._12);
    switch (pauseControl.state) {
    case 0:
        pauseControl.counter = 0;
        pauseControl.state = 1;
        break;
    case 1:
        pauseControl.state = 3;
        break;
    case 2:
        if (pauseControl.counter > 20) {
            pauseControl.state = 3;
        }
        break;
    case 3:
        minigamePauseMenuUpdate();
        pauseControl.counter = 0;
        pauseControl._12 = 0;
        pauseControl._1D4 = 0;
        break;
    case 4:
        pauseControl._1D9 = 1;
        pauseControl.state = 5;
        break;
    case 5:
        if (pauseControl._1D9 == 3) {
            g_Minigame.pauseInd = 0;
        }
        break;
    case 6:
        changeScene(3, 6);
        if (lbl_8037169C[0x13] != 0) {
            pauseControl.state = 7;
        }
        break;
    case 7:
        hugeAnimStruct[0x307A] = 0;
        g_Minigame.minigameInactiveInd = 1;
        pauseControl._1D9 = 2;
        g_Minigame.pauseInd = 0;
        fn_3_6AB30();
        mm_UnloadModels();
        g_Minigame.nextGameStatus = GAME_STATUS_MINIGAME_SELECT;
        SetGameStatus(GAME_STATUS_TOY_STADIUM_LOAD);
        break;
    case 8:
        switch (((int (*)(u16))exitMenu_main)(g_Controls[pauseControl.port].newButtonInput)) {
        case 1:
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            pauseControl.state = 9;
            break;
        case 2:
            pauseControl.state = 3;
            break;
        }
        break;
    case 9:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 45) {
            if (g_d_GameSettings.exhibitionMatchInd == FALSE) {
                challenge_setTransitionScreenCharacterPortrait(12, (s8)challengeTransitionPortraitIDs[((u8*)starMissionCompletionTracker)[0x441C]]);
            } else {
                changeScene(4, 6);
            }
        }
        if (lbl_8037169C[0x13] != 0) {
            g_Minigame.minigameInactiveInd = 1;
            pauseControl._1D9 = 2;
            g_Minigame.pauseInd = 0;
            g_d_GameSettings._13 = 1;
            mm_UnloadModels();
            fn_8004CC18();
            g_GameLogic.framesOfExitingToMenu = 1;
        }
        break;
    case 10:
        minigamePauseHelpUpdate();
        break;
    case 11:
        minigamePauseHelpUpdate();
        break;
    case 12:
        changeScene(3, 6);
        if (lbl_8037169C[0x13] != 0) {
            pauseControl.state = 13;
        }
        break;
    case 13:
        g_Minigame.retryInd = 1;
        mm_UnloadModels();
        hugeAnimStruct[0x307A] = 0;
        fn_3_6AB30();
        g_Minigame.minigameInactiveInd = 1;
        pauseControl._1D9 = 2;
        g_Minigame.pauseInd = 0;
        SetGameStatus(GAME_STATUS_LOAD_GAME);
        break;
    }
}

void minigamePauseMenuUpdate(void) {
    int type;
    int count;
    InputStruct* input;

    type = 0;
    input = &g_Controls[pauseControl.port];
    count = 6;
    if (g_d_GameSettings.exhibitionMatchInd == FALSE) {
        type = 2;
        count = 4;
    } else if (g_Minigame.grandPrixInd != 0) {
        type = 1;
        count = 5;
    }
    if (input->newButtonInput & INPUT_BUTTON_START) {
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        pauseControl.state = 4;
    } else if (input->newButtonInput & INPUT_BUTTON_A) {
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        switch ((minigamePauseMenuActions + type * 6)[pauseControl.cursor]) {
        case 0:
            pauseControl.state = 4;
            break;
        case 1:
            pauseControl.state = 12;
            break;
        case 3:
            pauseControl.state = 10;
            break;
        case 2:
            pauseControl.state = 11;
            break;
        case 4:
            pauseControl.state = 6;
            break;
        case 5:
            fn_3_5B408();
            pauseControl.state = 8;
            break;
        }
    } else if (input->newButtonInput & INPUT_BUTTON_B) {
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        if (pauseControl.cursor != 0) {
            pauseControl.cursor = 0;
        } else {
            pauseControl.state = 4;
        }
    } else if (input->_08 & INPUT_BUTTON_UP) {
        if (pauseControl.cursor == 0) {
            pauseControl.cursor = count - 1;
        } else {
            pauseControl.cursor--;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (input->_08 & INPUT_BUTTON_DOWN) {
        pauseControl.cursor++;
        if (pauseControl.cursor >= count) {
            pauseControl.cursor = 0;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
}

void minigamePauseHelpUpdate(void) {
    InputStruct* input = &g_Controls[pauseControl.port];

    switch (pauseControl._1D4) {
    case 0:
        if (pauseControl.state == 11 || g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
            minigameOptionSetup(1);
        }
        pauseControl._1D9 = 1;
        pauseControl._12 = 0;
        pauseControl._1D4 = 1;
        break;
    case 1:
        if (pauseControl._1D9 == 3) {
            pauseControl._1D4 = 2;
        }
        break;
    case 2:
        pauseControl._1D4 = 3;
        break;
    case 3:
        if (pauseControl._12 > 20) {
            pauseControl._1D4 = 4;
        }
        break;
    case 4:
        if (animRelated[0xC4] == 0) {
            if (input->newButtonInput & INPUT_BUTTON_B) {
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                pauseControl._12 = 0;
                pauseControl._1D4 = 5;
            } else if (pauseControl.state == 11 ||
                       (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && g_GameLogic.gameStatus == GAME_STATUS_PAUSED)) {
                if (input->_08 & INPUT_BUTTON_RIGHT) {
                    if (g_Minigame.helpPage == g_Minigame.helpPageCount) {
                        g_Minigame.helpPage = 1;
                    } else {
                        g_Minigame.helpPage++;
                    }
                    g_Minigame.helpPageDirLeft = 0;
                    g_Minigame.helpPageDelay = 20;
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                } else if (input->_08 & INPUT_BUTTON_LEFT) {
                    if (g_Minigame.helpPage == 1) {
                        g_Minigame.helpPage = g_Minigame.helpPageCount;
                    } else {
                        g_Minigame.helpPage--;
                    }
                    g_Minigame.helpPageDirLeft = 1;
                    g_Minigame.helpPageDelay = 20;
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                }
            }
        }
        break;
    case 5:
        if (pauseControl._12 > 20) {
            pauseControl.counter = 0;
            pauseControl.state = 1;
        }
        break;
    }
}

u32 minigame_checkIfAIInputIs_Algorithmic_Or_ControllerBased(s8 player) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && player >= 0 && player < 4) {
        return g_Minigame.isAIControlled[player];
    }
    return 0;
}

u32 minigame_getCcsAIControlledInd(s8 player) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && player >= 0 && player < 4) {
        return g_Minigame.ccs_aiControlledInd[player];
    }
    return 0;
}

u32 AI_getPort(s8 player) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && player >= 0 && player < 4) {
        return g_Minigame.portOfAIBeingProcessed[player];
    }
    return 0;
}

u32 minigame_getAIDrivenInputInd(s8 player) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && player >= 0 && player < 4) {
        return g_Minigame.aiDrivenInputInd[player];
    }
    return 0;
}

int minigame_compareDisplayedPoints(const void* a, const void* b) {
    int pointsB = g_Minigame.minigamePoints_current_Latest[*(const u8*)b][0];
    int pointsA = g_Minigame.minigamePoints_current_Latest[*(const u8*)a][0];

    if (pointsB == pointsA) {
        return *(const u8*)a - *(const u8*)b;
    }
    return pointsB - pointsA;
}

int minigame_getLeadingPlayer(void) {
    u8 order[4];
    u32 i;

    i = 0;
    do {
        order[i] = i;
        i++;
    } while (i < g_Minigame.miniGameNumberOfParticipants);
    fn_800246D4(minigame_compareDisplayedPoints, order, order, 1, g_Minigame.miniGameNumberOfParticipants);
    return order[0];
}

BOOL minigame_displayedPointsAllTied(void) {
    u32 i;

    for (i = 1; i < g_Minigame.miniGameNumberOfParticipants; i++) {
        if (g_Minigame.minigamePoints_current_Latest[i][0] != g_Minigame.minigamePoints_current_Latest[0][0]) {
            return FALSE;
        }
    }
    return TRUE;
}

BOOL minigame_pointsAllTied(void) {
    u32 i;

    for (i = 1; i < g_Minigame.miniGameNumberOfParticipants; i++) {
        if (g_Minigame.miniGameCurrentPoints[i] != g_Minigame.miniGameCurrentPoints[0]) {
            return FALSE;
        }
    }
    return TRUE;
}

int minigame_comparePoints(const void* a, const void* b) {
    int pointsB = g_Minigame.miniGameCurrentPoints[*(const u8*)b];
    int pointsA = g_Minigame.miniGameCurrentPoints[*(const u8*)a];

    if (pointsB == pointsA) {
        return *(const u8*)a - *(const u8*)b;
    }
    return pointsB - pointsA;
}

int minigame_compareGrandPrixTotals(const void* a, const void* b) {
    u32 valueB = g_Minigame.grandPrixTotals[*(const u8*)b];
    u32 valueA = g_Minigame.grandPrixTotals[*(const u8*)a];

    if (valueB == valueA) {
        return *(const u8*)a - *(const u8*)b;
    }
    return valueB - valueA;
}

int minigame_compareGrandPrixPrevTotals(const void* a, const void* b) {
    u32 valueB = g_Minigame.grandPrixPrevTotals[*(const u8*)b];
    u32 valueA = g_Minigame.grandPrixPrevTotals[*(const u8*)a];

    if (valueB == valueA) {
        return *(const u8*)a - *(const u8*)b;
    }
    return valueB - valueA;
}

void minigame_rankPlayers(u8 (*order)[2], int mode) {
    u8 sorted[4];
    s16 points[4];
    u32 i;
    u32 j;

    i = 0;
    do {
        sorted[i] = i;
        i++;
    } while (i < g_Minigame.miniGameNumberOfParticipants);
    switch (mode) {
    case 0:
    default:
        fn_800246D4(minigame_comparePoints, sorted, sorted, 1, g_Minigame.miniGameNumberOfParticipants);
        i = 0;
        do {
            points[i] = g_Minigame.miniGameCurrentPoints[i];
            i++;
        } while (i < g_Minigame.miniGameNumberOfParticipants);
        break;
    case 1:
        fn_800246D4(minigame_compareGrandPrixTotals, sorted, sorted, 1, g_Minigame.miniGameNumberOfParticipants);
        i = 0;
        do {
            points[i] = g_Minigame.grandPrixTotals[i];
            i++;
        } while (i < g_Minigame.miniGameNumberOfParticipants);
        break;
    case 2:
        fn_800246D4(minigame_compareGrandPrixPrevTotals, sorted, sorted, 1, g_Minigame.miniGameNumberOfParticipants);
        i = 0;
        do {
            points[i] = g_Minigame.grandPrixPrevTotals[i];
            i++;
        } while (i < g_Minigame.miniGameNumberOfParticipants);
        break;
    }
    order[0][0] = sorted[0];
    order[0][1] = 0;
    j = 1;
    while (j < g_Minigame.miniGameNumberOfParticipants) {
        order[j][0] = sorted[j];
        if (points[sorted[j]] == points[sorted[j - 1]]) {
            order[j][1] = order[j - 1][1];
        } else {
            order[j][1] = j;
        }
        j++;
    }
}

BOOL minigame_grandPrixHasPlayed(u32 mode) {
    u32 i;

    for (i = 0; i < g_Minigame.grandPrixRound - 1; i++) {
        if (g_Minigame.grandPrixOrder[i] == mode) {
            return TRUE;
        }
    }
    return FALSE;
}

void minigameStartGrandPrix(void) {
    u32 k;

    memset(&g_Minigame.resultsScene, 0, 0x28);
    g_Minigame.grandPrixFinalHumanCount = 0;
    g_Minigame.grandPrixWonInd = 0;
    hugeAnimStruct[0x307E] = 0;
    k = 0;
    do {
        g_Minigame.grandPrixOrder[k] = k + 1;
        k++;
    } while (k < 6);
    shuffleU8Array(g_Minigame.grandPrixOrder, 6, FALSE);
    SetGameStatus(GAME_STATUS_0x28);
}

void minigames_0x28(void) {
    switch (g_GameLogic._125) {
    case TRANSITION_CALCULATION_TYPE_0:
        g_GameLogic._125++;
        g_Minigame.helpPage = 0;
        if (g_Minigame.menuMusicStartedInd == 0) {
            insertGraphicDrawingFunction(startMenuMusic, 1);
        }
        break;
    case TRANSITION_CALCULATION_TYPE_1:
        changeScene(1, 6);
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125++;
        break;
    case TRANSITION_CALCULATION_TYPE_2:
        minigameHelpMenuUpdate();
        if (g_Minigame.helpMenuResult == 2) {
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_5;
        } else if (g_Minigame.helpMenuResult != 0) {
            g_GameLogic._125++;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_3:
        changeScene(3, 6);
        if (lbl_8037169C[0x13] != 0) {
            g_GameLogic._125++;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_4:
        fn_80062A74();
        g_Minigame.menuMusicStartedInd = 0;
        SetGameStatus(GAME_STATUS_0x29);
        break;
    case TRANSITION_CALCULATION_TYPE_5:
        changeScene(3, 6);
        if (lbl_8037169C[0x13] != 0) {
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_6;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_6:
        SetGameStatus(GAME_STATUS_TOY_STADIUM_CHARACTER_SELECT);
        break;
    }
}

void minigameGrandPrixNextRound(void) {
    switch (g_GameLogic._125) {
    case TRANSITION_CALCULATION_TYPE_0:
        g_Minigame.GameMode_MiniGame = g_Minigame.grandPrixOrder[g_Minigame.grandPrixRound++];
        changeScene(1, 6);
        g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_1;
        break;
    case TRANSITION_CALCULATION_TYPE_1:
        if (g_Minigame.resultsScene->_1A != 0) {
            changeScene(3, 6);
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_2;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_2:
        if (lbl_8037169C[0x13] != 0) {
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_3;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_3:
        g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_4;
        break;
    case TRANSITION_CALCULATION_TYPE_4:
        SetGameStatus(GAME_STATUS_MINIGAME_READY);
        break;
    }
}

void minigameFillGrandPrixScoreInput(MiniGrandPrixScoreInput* input) {
    fn_8006C398(input);
    if (g_Minigame.grandPrixInd != 0 && g_Minigame.soloPlayerSlot >= 0 && g_Minigame.soloPlayerSlot < 4) {
        u32 i;
        u32 j;
        u8 order[4][2];

        i = 0;
        do {
            input->vals[i] = g_Minigame.grandPrixPoints[i];
            i++;
        } while (i < 6);
        i = 0;
        do {
            input->bytes[i] = g_Minigame.grandPrixOrder[i];
            i++;
        } while (i < 6);
        minigame_rankPlayers(order, 1);
        j = 0;
        do {
            if (g_Minigame.soloPlayerSlot == order[j][0]) {
                input->placeRank = order[j][1];
            }
            j++;
        } while (j < g_Minigame.miniGameNumberOfParticipants);
        input->extra = g_Minigame.grandPrixTotals[g_Minigame.soloPlayerSlot];
        input->charID = inMemRoster[0][g_Minigame.playerSlots.characterIndex[g_Minigame.soloPlayerSlot]].stats.CharID;
    }
}

void minigames_0x26(void) {
    u8 order[4][2];
    u32 i;
    u32 j;
    u32 p;

    switch (g_GameLogic._125) {
    case TRANSITION_CALCULATION_TYPE_0:
        i = 0;
        do {
            g_Minigame.grandPrixPrevTotals[i] = g_Minigame.grandPrixTotals[i];
            i++;
        } while (i < g_Minigame.miniGameNumberOfParticipants);
        minigame_rankPlayers(order, 0);
        i = 0;
        do {
            g_Minigame.grandPrixTotals[order[i][0]] += minigameGrandPrixRankPoints[order[i][1]] * ((g_Minigame.grandPrixRound >= 6) + 1);
            i++;
        } while (i < g_Minigame.miniGameNumberOfParticipants);
        minigame_rankPlayers(g_Minigame.grandPrixRanks, 1);
        if (g_Minigame.humanPlayerCount == 1) {
            g_Minigame.grandPrixPoints[g_Minigame.GameMode_MiniGame - 1] = g_Minigame.miniGameCurrentPoints[g_Minigame.soloPlayerSlot];
        }
        for (p = 0; p < 4; p++) {
            for (j = 0; j < 4; j++) {
                if (p == g_Minigame.grandPrixRanks[j][0]) {
                    g_Minigame.playerSlots.rank[p] = g_Minigame.grandPrixRanks[j][1] + 1;
                }
            }
        }
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_1;
        break;
    case TRANSITION_CALCULATION_TYPE_1:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 120) {
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_2;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_2:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 1800 || checkForButtonPressToSkip(1, INPUT_BUTTON_A | INPUT_BUTTON_START)) {
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_3;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_3:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 120) {
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_4;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_4:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 1800 || checkForButtonPressToSkip(1, INPUT_BUTTON_A | INPUT_BUTTON_START)) {
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_5;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_5:
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_6;
        if (g_Minigame.grandPrixRound >= 6) {
            changeScene(3, 6);
        }
        break;
    case TRANSITION_CALCULATION_TYPE_6:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 60) {
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_7;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_7:
        if (g_Minigame.grandPrixRound >= 6) {
            fn_3_15F998();
            fn_3_147DFC();
            sound_crowd_EffectsStruct._31 = 0;
            SetGameStatus(GAME_STATUS_0x27);
        } else {
            pauseControl._1D1 = 0;
            pauseControl.state = 0;
            SetGameStatus(GAME_STATUS_MINIGAME_POST_MENU);
        }
        break;
    }
}

void minigames_0x27(void) {
    switch (g_GameLogic._125) {
    case TRANSITION_CALCULATION_TYPE_0:
        g_Minigame.grandPrixFinalInd = 1;
        g_Minigame.grandPrixFinalHumanCount = g_Minigame.humanPlayerCount;
        animRelated[0xB8] = 0;
        if (g_Minigame.humanPlayerCount == 1) {
            minigameGrandPrixCheckWin();
        }
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_1;
        break;
    case TRANSITION_CALCULATION_TYPE_1:
        changeScene(1, 6);
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy == minigameResultsFrames[1]) {
            animRelated[0xB8] = 1;
        }
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 300) {
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_2;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_2:
        if (checkForButtonPressToSkip(1, INPUT_BUTTON_A | INPUT_BUTTON_START)) {
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_6;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_6:
        g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_7;
        break;
    case TRANSITION_CALCULATION_TYPE_7:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 60) {
            g_GameLogic._125 = TRANSITION_CALCULATION_TYPE_8;
        }
        break;
    case TRANSITION_CALCULATION_TYPE_8:
        pauseControl._1D1 = 0;
        pauseControl.state = 0;
        if (g_Minigame.joinedPlayerCount == 1) {
            SetGameStatus(GAME_STATUS_0x24);
        } else {
            SetGameStatus(GAME_STATUS_MINIGAME_POST_MENU);
        }
        break;
    }
}

void minigameGrandPrixCheckWin(void) {
    if (g_Minigame.playerSlots.rank[g_Minigame.soloPlayerSlot] == 1) {
        g_Minigame.grandPrixWonInd = 1;
    }
}

void minigameAwardCoins(void) {
    awardMinigameCoins();
}

void fn_3_106EB0(void) {
    callSfx(0x30B);
}

BOOL loadSomeDataFile(void) {
    if (lbl_803C6CF8.cancel.bytes[1] == 1) {
        *(void**)((u8*)&g_Camera + 0x1B4) = ARAMTransfer(cameraDataFileDescriptor, 0, 0, 0);
        return TRUE;
    }
    return FALSE;
}

void someAllocFunction(void) {
    CAMSCRIPT_G(0)._0990 = _OSAllocFromHeap(4, 0x8000);
    CAMSCRIPT_G(1)._0990 = _OSAllocFromHeap(4, 0x8000);
}
