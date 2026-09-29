/* dolsqrtf2() is only ever inlined in this file. With the header's default
 * `extern` linkage MWCC also materialises its out-of-line copy's _half/_three
 * local statics at the head of this TU's .rodata, shifting every
 * constant-pool entry 16 bytes past the offsets the linked module has. */
#define SQRT2_LINKAGE static
#include "game/pitching/pitcher.h"
#include "game/UnknownHomes_Game.h"
#include "game/baserunning/runner.h"
#include "game/ball/ball_physics.h"
#include "game/math/game_math.h"
#include "static/UnknownHomes_Static.h"
#include "header_rep_data.h"
#include "game/sound/m_sound.h"
#include "game/minigame/rep_3880.h"
#include "game/minigame/bobomb_derby.h"
#include "Unknown/File_0x800204cc.h"
#include "game/batting/batter_ai.h"
#include "game/pitching/perfect_pitch_gfx.h"
#include "game/pitching/pitcher_ai.h"
#include "game/match_setup/roster_init.h"
#include "musyx/musyx.h"
#include "Unknown/File_0x8001c920.h"
#include "Unknown/File_0x80024b00.h"

/* minigamePlayerSelectedOrder is -1 when no player is selected. This file
 * reads it through a signed-byte lvalue; a plain (s8) cast of the u8 field
 * compiles to different code. */
#define MINIGAME_SELECTED_ORDER (*(s8*)&g_Minigame.minigamePlayerSelectedOrder)

extern void incrementPitchCount(void);
extern s16 lbl_3_data_5F3C[];
extern s16 lbl_3_data_5FC0[];
extern struct {
    u8 _00[0x28];
    u8 _28;
} lbl_80366158;
extern f32 lbl_3_data_21380[3];
extern u8 lbl_3_data_5F44[];
static u32 lbl_3_bss_172C[7];

extern f32 lbl_3_data_446C[2];
typedef struct {
    f32 y1stBounceSpeedKept;
    f32 yOtherBouncesSpeedKept;
    f32 x1stBounceSpeedKept;
    f32 xOtherBouncesSpeedKept;
    f32 rollingSpeedKept;
} BallBounceConstants;
extern BallBounceConstants ballBounceConstants[7];
extern s16 lbl_3_data_5F7C[];
extern u8 bulletBallConstants[];
extern u8 hitByPitchHitboxes[];
extern u8 characterStaticIndexes[0x144];
extern f32 lbl_3_data_4474[4];
extern u32 AI_getPort(u8 idx);
extern int aIPickoff(void);
extern s16 pitchConstantsArray[][7];
extern f32 curveControlFrames_CursedBallMult[2];
extern void postPitchStatUpdating(int arg);
extern void trackLastPitchInfo(void);
extern f32 lbl_3_data_5EB0[2];
extern f32 eggConstants[8];
extern f32 bOD_bB_maxMovement[4];

extern f32 strikeZone[6];
extern f32 pitchSpeedScaler[12];
extern u8 animRelated[0x124];
extern u8 highLevelSimulationFlag[2];
extern void transitionToLiveBallWithoutContact(int arg);
extern s16 lbl_3_data_8080[];
extern struct {
    u8 _00[0x42];
    s16 scoutCountdown;
    u8 _44[2];
    u8 scoutMissionID;
    u8 _47;
    u8 scoutFlag;
    u8 _49[5];
} lbl_3_common_bss_37400;
extern s16 lbl_3_common_bss_32220[8];
extern int runnerStealing_TransitionToLiveViewIndicator(void);
extern void SetGameStatus(int status);
extern u8 hugeAnimStruct[0x3154];
extern void practice_startPitchAfter90Frames(void);
extern void lastPlayStats(void);
extern void challengeModeRelated_checkScoutMissionSuccess(void);
extern void determineIfReplayShouldPlay(void);
extern f32 lbl_3_data_5F08[13];
extern s16 lbl_3_data_5EDC[];
extern int getAdjustedPitcherStamina(int team, int rosterID, int flag);
extern VecXZ fieldingStartingCoords_regular[9];
extern void QueueTextToDisplay(int code, int arg1);

static u32 pad_05_00001728_bss;

static const f32 maxPitchCharge = 1.0f;

extern f32 lbl_3_data_5EB8[3];
extern f32 lbl_3_data_5EC4[3];
extern f32 lbl_3_data_5ED0[3];

static inline void advanceForcedRunners(void) {
    int i;
    int seenOther = 0;
    if (g_Pitcher.strikeOutOrWalk == 3) {
        for (i = 1; i < 4; i++) {
            InMemRunnerType* r = &g_Runners[i];
            if (r->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD ||
                r->runnerOnFieldOrOutOrScored == RUNNER_STATUS_WALK_WHILE_STEALING) {
                if (seenOther == 0) {
                    r->currentBase = i;
                    updateRunnerPosition(i, 1);
                } else {
                    r->currentBase = r->startingBase_baseAchieved;
                    r->nextBase = (r->currentBase + 1) & 3;
                }
            } else {
                seenOther = 1;
            }
        }
    } else {
        for (i = 1; i < 4; i++) {
            InMemRunnerType* r = &g_Runners[i];
            if (r->runnerOnFieldOrOutOrScored != RUNNER_STATUS_ON_FIELD &&
                r->runnerOnFieldOrOutOrScored != RUNNER_STATUS_WALK_WHILE_STEALING) {
                break;
            }
            if (i == r->currentBase) {
                updateRunnerPosition(i, 1);
            }
        }
    }
    g_Runners[0].currentBase = 1;
    g_Runners[0].nextBase = 2;
}

static inline void updatePitchYParabola(void) {
    f32 t;
    int frames;
    if (g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_YOSHI || g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_BIRDO) {
        if (g_Pitcher.eggBallBounceNumber == 0) {
            t = (f32)g_Ball.pitchHangtimeCounter - (f32)g_Pitcher.frameWhenUnhittable / 2.0f;
            g_Pitcher.pitchY_parabolicAdjustment =
                g_Pitcher.verticalOffsetParabolaMidpoint -
                t * (g_Pitcher.verticalGlobalParabolicVelo * t) / 10000.0f;
        } else if (g_Pitcher.eggBallBounceNumber == 1 || g_Pitcher.eggBallBounceNumber == 2) {
            if (g_Pitcher.framesSinceFirstEggBounce == 1) {
                if (g_Pitcher.eggBallBounceNumber == 1) {
                    frames = estimateXAndFrameAtBatterZ(&t, g_Pitcher.eggBallBounceZLoc, 0);
                    g_Pitcher.ballBouncePeakZ = (s16)((f32)frames / 2.0f);
                    g_Pitcher.verticalGlobalParabolicVelo =
                        (f32)LERPToNewRange_Float(g_Pitcher.pitchSpeed, lbl_3_data_5F7C[4], lbl_3_data_5F7C[5],
                                                  lbl_3_data_5F7C[6], lbl_3_data_5F7C[7]);
                    t = (f32)g_Pitcher.ballBouncePeakZ;
                    g_Pitcher.verticalOffsetParabolaMidpoint =
                        t * (g_Pitcher.verticalGlobalParabolicVelo * t) / 10000.0f;
                } else {
                    g_Pitcher.verticalOffsetParabolaMidpoint = 0.3f + strikeZone[4];
                    t = (f32)g_Pitcher.framesUntilBallReachesBatterZ;
                    g_Pitcher.ballBouncePeakZ = g_Pitcher.framesUntilBallReachesBatterZ;
                    g_Pitcher.verticalGlobalParabolicVelo =
                        10000.0f * g_Pitcher.verticalOffsetParabolaMidpoint / (t * t);
                }
            }
            t = (f32)g_Pitcher.framesSinceFirstEggBounce - (f32)g_Pitcher.ballBouncePeakZ;
            g_Pitcher.pitchY_parabolicAdjustment =
                g_Pitcher.verticalOffsetParabolaMidpoint -
                t * (g_Pitcher.verticalGlobalParabolicVelo * t) / 10000.0f;
        } else {
            g_Pitcher.pitchY_parabolicAdjustment = 0.0f;
        }
    } else if (g_Pitcher.cancelParabolicAdjustmentInd != 0) {
        g_Pitcher.pitchY_parabolicAdjustment = 0.0f;
    } else {
        t = (f32)g_Ball.pitchHangtimeCounter - (f32)g_Pitcher.frameWhenUnhittable / 2.0f;
        g_Pitcher.pitchY_parabolicAdjustment =
            g_Pitcher.verticalOffsetParabolaMidpoint -
            t * (g_Pitcher.verticalGlobalParabolicVelo * t) / 10000.0f;
    }
}

// .text:0x00075560 size:0x45C mapped:0x806B45F4
void atBat_Pitcher(void) {
    if (AI_getPort(g_Minigame.minigameControlStruct[0].characterIndex[MINIGAME_SELECTED_ORDER]) != 0) {
        g_Pitcher.AIInd = 0;
    }
    if (g_Pitcher.currentStateFrameCounter < 0x7FFE) {
        g_Pitcher.currentStateFrameCounter++;
    } else {
        g_Pitcher.currentStateFrameCounter = 0x7FFF;
    }
    updatePastHitBallCoords();
    switch (g_Pitcher.pitcherActionState) {
    case PITCHER_ACTION_STATE_TRANSITION:
        fn_3_75090();
        break;
    case PITCHER_ACTION_STATE_PRE_PITCH:
        waitingForPitch();
        break;
    case PITCHER_ACTION_STATE_WINDUP:
        pitchingWindUpFunction();
        break;
    case PITCHER_ACTION_STATE_IN_AIR:
        fn_3_73F2C();
        break;
    case PITCHER_ACTION_STATE_NO_CONTACT:
        fn_3_73DE8();
        break;
    case PITCHER_ACTION_STATE_HIT:
        endAtBatNonHit();
        break;
    case PITCHER_ACTION_STATE_POST_HIT:
        resetCounter();
        break;
    case PITCHER_ACTION_STATE_HIT_BY_PITCH:
        fn_3_6FB98();
        break;
    }
}

// .text:0x000754B8 size:0xA8 mapped:0x806B454C
void setPitchingConstants(void) {
    g_Pitcher.pitcherActionState = PITCHER_ACTION_STATE_TRANSITION;
    g_Pitcher.currentStateFrameCounter = 0;
    g_Pitcher.pitchSpeedScaler = pitchSpeedScaler[0];
    g_Pitcher.decelerationFactor = pitchSpeedScaler[1];
    g_Pitcher.centerOfStrikeZone.x = 0.5f * (strikeZone[0] + strikeZone[1]);
    g_Pitcher.centerOfStrikeZone.z = 0.5f * (strikeZone[2] + strikeZone[3]);
    g_Pitcher.strikeZoneLeft = strikeZone[0];
    g_Pitcher.strikeZoneRight = strikeZone[1];
    g_Pitcher.beginningOfStrikeCheckZ = strikeZone[2];
    g_Pitcher.endingOfStrikeCheckZ = strikeZone[3];
    g_Pitcher.pitcher.x = lbl_3_data_446C[0];
    g_Pitcher.pitcher.z = lbl_3_data_446C[1];
    g_Pitcher.windupCountdownUntilBallReleased = 100;
    g_Pitcher.pitchWindUpCountDown = 100;
    g_Pitcher.curvePitchWindupFrames = 100;
    g_Pitcher.playStartOfGameAnimation = 1;
}

// .text:0x00075434 size:0x84 mapped:0x806B44C8
void resetInMemPitcher(void) {
    setPitcherStatsToInMemPitcher(g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]);
    g_Pitcher.pitcherActionState = PITCHER_ACTION_STATE_TRANSITION;
    g_Pitcher.currentStateFrameCounter = 0;
    g_Pitcher.nPitchesThisAB = 0;
    g_Pitcher.nPickoffAttempts = 0;
    g_Pitcher.pitcher.x = lbl_3_data_446C[0];
    g_Pitcher.pitcher.z = lbl_3_data_446C[1];
    g_Pitcher.pitchDeliveryAnimationPlaying = 0;
    if (g_Scores.Inning == 1) {
        g_Pitcher.playStartOfGameAnimation = 1;
    }
}

// .text:0x000753E8 size:0x4C mapped:0x806B447C
void resetPitcherValuesBetweenBatters(int flag) {
    g_Pitcher.pitcherActionState = PITCHER_ACTION_STATE_TRANSITION;
    g_Pitcher.currentStateFrameCounter = 0;
    if (flag == 0) {
        g_Pitcher.nPitchesThisAB = 0;
        g_Pitcher.nPickoffAttempts = 0;
    }
    g_Pitcher.pitcher.x = lbl_3_data_446C[0];
    g_Pitcher.pitcher.z = lbl_3_data_446C[1];
    g_Pitcher.pitchDeliveryAnimationPlaying = 0;
}

// .text:0x000751B4 size:0x234 mapped:0x806B4248
void setDefaultInMemPitcher(void) {
    g_Pitcher.pitcherActionState = PITCHER_ACTION_STATE_TRANSITION;
    g_Pitcher.currentStateFrameCounter = 0;
    g_Ball.fielderWBallIndex = 0;
    g_Pitcher.pitchSpeedScaler = pitchSpeedScaler[0];
    g_Pitcher.decelerationFactor = pitchSpeedScaler[1];
    g_Pitcher.centerOfStrikeZone.x = 0.5f * (strikeZone[0] + strikeZone[1]);
    g_Pitcher.centerOfStrikeZone.z = 0.5f * (strikeZone[2] + strikeZone[3]);
    g_Pitcher.strikeZoneLeft = strikeZone[0];
    g_Pitcher.strikeZoneRight = strikeZone[1];
    g_Pitcher.beginningOfStrikeCheckZ = strikeZone[2];
    g_Pitcher.endingOfStrikeCheckZ = strikeZone[3];
    g_Pitcher.ballCurrentPosition.x = fieldingStartingCoords_regular[0].x;
    g_Pitcher.ballCurrentPosition.y = 1.0f;
    g_Pitcher.ballCurrentPosition.z = fieldingStartingCoords_regular[0].z;
    g_Pitcher.ballVelocity.x = 0.0f;
    g_Pitcher.ballVelocity.y = 0.0f;
    g_Pitcher.ballVelocity.z = 0.0f;
    g_Pitcher.pitchStartingPosition_AIMaxCurve = g_Pitcher.centerOfStrikeZone.x;
    g_Pitcher.eggBallBounceYHeight = strikeZone[4];
    g_Pitcher.frontOfPlateZ = g_Pitcher.centerOfStrikeZone.z;
    g_Pitcher.pitchTotalTimeCounter = 0;
    g_Pitcher.strikeZoneProcessNumber = 0;
    g_Pitcher.frameBallCanStartBeingControlled = 0;
    g_Pitcher.pitchInAirInd = 0;
    g_Pitcher.calledStrikeInd = 0;
    g_Pitcher.strikeInd = 0;
    g_Pitcher.miniGameRelated = 0;
    g_Pitcher.pickOffLoc = -1;
    g_Pitcher.pitchDidntResultInLiveBallInd = 0;
    g_Pitcher.strikeOutOrWalk = 0;
    g_Pitcher.framesUntilPitchGetsToBatter = -1;
    g_Pitcher.pitchChargeUp = 0.0f;
    g_Pitcher.pitchChargeUpAnimationProportion = 0.0f;
    g_Pitcher.unknownFrameCounter = 0;
    g_Pitcher.ChargePitchType = 0;
    g_Pitcher.framesAHeldForChargePitches = 0;
    g_Pitcher.TypeOfPitch = 0;
    g_Pitcher.ballHaloTrainInd_unused = 0;
    g_Pitcher.overChargeInd = 0;
    g_Pitcher.starPitchInd = 0;
    g_Pitcher.starPitchType = 0;
    g_Pitcher.warioWaluStarAnimationStage = 0;
    g_Pitcher.warioWaluStarHasPlayedSound = 0;
    g_Pitcher.peachDaisyStarAnimationOn = 0;
    g_Pitcher.peachDaisyAnimationHappened = 0;
    g_Pitcher.anyCurveInput = 0;
    g_Pitcher.bulletPitchFrameCounter = 0;
    g_Pitcher.bulletPitchStageCode = 0;
    g_Pitcher.eggBallBounceNumber = 0;
    g_Pitcher.framesSinceFirstEggBounce = 0;
    g_Pitcher.pitcherOffCenter = 0;
    g_Pitcher.nonCaptainStarPitchTriggeredType = 0;
    g_Pitcher.walkedInRunInd = 0;
    g_Pitcher.unused_pitcherIsFielder = 0;
    g_Pitcher.windupCountdownUntilBallReleased = lbl_3_data_8080[0];
    g_Pitcher.starPitchPositionAdjustment.x = 0.0f;
    g_Pitcher.starPitchPositionAdjustment.y = 0.0f;
    g_Pitcher.starPitchPositionAdjustment.z = 0.0f;
    g_Pitcher.pitchWindUpCountDown = lbl_3_data_8080[1];
    g_Pitcher.curvePitchWindupFrames = lbl_3_data_8080[2];
    g_Pitcher.windupCountdownUntilBallReleased = g_Pitcher.pitchWindUpCountDown;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        g_Pitcher.AIInd = g_Practice.aIEnabled;
    } else if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY ||
               g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER) {
        g_Pitcher.AIInd = 1;
    } else if (g_d_GameSettings.minigamesEnabled) {
        g_Pitcher.AIInd =
            g_Minigame.minigameControlStruct[0].battingHandedness[MINIGAME_SELECTED_ORDER];
    } else {
        g_Pitcher.AIInd = g_GameLogic.teamIsCPU[g_GameLogic.awayTeamBattingInd_battingTeam + 2];
    }
    sound_crowd_EffectsStruct._34 = 0;
}

// .text:0x000750DC size:0xD8 mapped:0x806B4170
BOOL loadPitcherActor(void) {
    int charID = inMemRoster[g_GameLogic.teamFielding]
                            [g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]]
                                .stats.CharID;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_Practice.practiceType_2 != PRACTICE_TYPE_FREEPLAY) {
        charID = g_Pitcher.charID;
    }
    if (animRelated[0x9C] == 0) {
        highLevelSimulationFlag[1] = 0;
        animRelated[0x9C] = 1;
    }
    if (animRelated[0x9C] == 1 && loadCharacterAnimation(charID) != 0) {
        return 1;
    }
    return 0;
}

// .text:0x000750C4 size:0x18 mapped:0x806B4158
void pitcherAITransitionFromPrePitchToWindup(u8 state) {
    g_Pitcher.pitcherActionState = state;
    g_Pitcher.currentStateFrameCounter = 0;
}

// .text:0x00075090 size:0x34 mapped:0x806B4124
void fn_3_75090(void) {
    g_Pitcher.pitcherActionState = PITCHER_ACTION_STATE_PRE_PITCH;
    g_Pitcher.currentStateFrameCounter = 0;
    g_Ball.AtBat_Contact_BallPos.x = g_Pitcher.ballCurrentPosition.x;
    g_Ball.AtBat_Contact_BallPos.y = g_Pitcher.ballCurrentPosition.y;
    g_Ball.AtBat_Contact_BallPos.z = g_Pitcher.ballCurrentPosition.z;
}

// .text:0x00074D0C size:0x384 mapped:0x806B3DA0
void waitingForPitch(void) {
    InputStruct* controls;
    controls = &g_Controls[g_GameLogic.teams[g_GameLogic.teamFielding]];
    g_Ball.AtBat_Contact_BallPos.x = g_Pitcher.ballCurrentPosition.x;
    g_Ball.AtBat_Contact_BallPos.y = g_Pitcher.ballCurrentPosition.y;
    g_Ball.AtBat_Contact_BallPos.z = g_Pitcher.ballCurrentPosition.z;
    if (g_GameLogic.frameCountdownAtBeginningOfAtBatLockout != 0) {
        g_Pitcher.currentStateFrameCounter = 0;
        return;
    }
    if (g_Batter.beginningOfABAnimationOccuring != 0) {
        g_Pitcher.currentStateFrameCounter = 0;
        return;
    }
    if (g_UnkSound_32718._07 == 0xC) {
        g_Pitcher.currentStateFrameCounter = 0;
        return;
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && g_Minigame.toyfield_waitFor_CoinsX2_AnimationToEnd != 0) {
        g_Pitcher.currentStateFrameCounter = 0;
        return;
    }
    if (hugeAnimStruct[0x2D46] != 0) {
        return;
    }
    if (hugeAnimStruct[0x2D52] != 0) {
        return;
    }
    if (hugeAnimStruct[0x2D5E] != 0) {
        return;
    }
    if (!g_d_GameSettings.exhibitionMatchInd && animRelated[0xB3] != 0) {
        return;
    }
    if (g_Pitcher.pitchDeliveryAnimationPlaying != 0) {
        g_Pitcher.currentStateFrameCounter = 0;
        return;
    }
    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_FIELDING && g_Practice.hitVariablesSetIndicator == 0) {
        return;
    }
    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_BASERUNNING && ((u8*)&g_Practice)[0x1EC] == 0) {
        return;
    }
    if (g_d_GameSettings.minigamesEnabled) {
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY) {
            bOD_bB_Pitcher_waitingForPitch();
            return;
        }
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER) {
            bOD_bB_Pitcher_waitingForPitch();
            return;
        }
        controls = &g_Controls[g_Minigame.minigameControlStruct[0].characterIndex[MINIGAME_SELECTED_ORDER]];
        if (AI_getPort(g_Minigame.minigameControlStruct[0].characterIndex[MINIGAME_SELECTED_ORDER]) != 0) {
            controls = &g_Minigame._1D7C[g_Minigame.minigameControlStruct[0].characterIndex[MINIGAME_SELECTED_ORDER]];
        }
        if (g_Pitcher.AIInd != 0) {
            pitcherAI_prePitchSetConstants();
            return;
        }
    } else {
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_Practice.practiceLevel == 4) {
            practice_startPitchAfter90Frames();
            return;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_Practice.instructionNumber >= 0) {
            controls = &g_Practice.inputs[g_GameLogic.teamFielding];
        }
        if (waitingForPitch_checkForPickoffs() != 0) {
            return;
        }
        if (g_Pitcher.AIInd != 0) {
            pitcherAI_prePitchSetConstants();
            return;
        }
    }
    pitcherMovementOnMound();
    if (controls->newButtonInput & INPUT_BUTTON_A) {
        if (!g_d_GameSettings.minigamesEnabled && (controls->buttonInput & INPUT_TRIGGER_R)) {
            g_Pitcher.starPitchInd = 1;
        }
        if (g_Pitcher.starPitchInd == 0 && (controls->buttonInput & INPUT_BUTTON_DOWN)) {
            g_Pitcher.TypeOfPitch = 2;
        } else {
            g_Pitcher.framesAHeldForChargePitches = 1;
        }
        g_Pitcher.pitcherActionState = PITCHER_ACTION_STATE_WINDUP;
        g_Pitcher.currentStateFrameCounter = 0;
        g_Stats._0038[0] = 1;
    }
}

// .text:0x00074AC4 size:0x248 mapped:0x806B3B58
void pitcherMovementOnMound(void) {
    InputStruct* controls;
    f32 movement;
    controls = &g_Controls[g_GameLogic.teams[g_GameLogic.teamFielding]];
    movement = 0.0f;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_Practice.instructionNumber >= 0) {
        controls = &g_Practice.inputs[g_GameLogic.teamFielding];
    } else if (AI_getPort(g_Minigame.minigameControlStruct[0].characterIndex[MINIGAME_SELECTED_ORDER]) !=
               0) {
        controls = &g_Minigame._1D7C[g_Minigame.minigameControlStruct[0].characterIndex[MINIGAME_SELECTED_ORDER]];
    } else if (g_d_GameSettings.minigamesEnabled) {
        controls = &g_Controls[g_Minigame.minigameControlStruct[0].characterIndex[MINIGAME_SELECTED_ORDER]];
    }
    if (controls->buttonInput & INPUT_TRIGGER_L) {
        g_Pitcher.pitcherOffCenter = 1;
    }
    if (g_Pitcher.pitcherOffCenter != 0) {
        if (g_Pitcher.pitcher.x >= -lbl_3_data_4474[3] && g_Pitcher.pitcher.x <= lbl_3_data_4474[3]) {
            g_Pitcher.pitcherOffCenter = 0;
            g_Pitcher.pitcher.x = 0.0f;
        } else if (g_Pitcher.pitcher.x < 0.0f) {
            g_Pitcher.pitcher.x += lbl_3_data_4474[3];
        } else {
            g_Pitcher.pitcher.x -= lbl_3_data_4474[3];
        }
    } else {
        if (controls->buttonInput & INPUT_BUTTON_LEFT) {
            movement = -lbl_3_data_4474[2];
        } else if (controls->buttonInput & INPUT_BUTTON_RIGHT) {
            movement = lbl_3_data_4474[2];
        }
        g_Pitcher.pitcher.x = g_Pitcher.pitcher.x + movement;
        if (g_Pitcher.pitcher.x < lbl_3_data_4474[0]) {
            g_Pitcher.pitcher.x = lbl_3_data_4474[0];
        }
        if (g_Pitcher.pitcher.x > lbl_3_data_4474[1]) {
            g_Pitcher.pitcher.x = lbl_3_data_4474[1];
        }
    }
}

// .text:0x00074128 size:0x99C mapped:0x806B31BC
void pitchingWindUpFunction(void) {
    InputStruct* controls;
    controls = &g_Controls[g_GameLogic.teams[g_GameLogic.teamFielding]];
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_Practice.instructionNumber >= 0) {
        controls = &g_Practice.inputs[g_GameLogic.teamFielding];
    } else if (AI_getPort(g_Minigame.minigameControlStruct[0].characterIndex[MINIGAME_SELECTED_ORDER]) != 0) {
        controls = &g_Minigame._1D7C[g_Minigame.minigameControlStruct[0].characterIndex[MINIGAME_SELECTED_ORDER]];
    } else if (g_d_GameSettings.minigamesEnabled) {
        if (MINIGAME_SELECTED_ORDER >= 0) {
            controls = &g_Controls[g_Minigame.minigameControlStruct[0].characterIndex[MINIGAME_SELECTED_ORDER]];
        }
    }
    if (g_Pitcher.framesAHeldForChargePitches != 0) {
        g_Pitcher.framesAHeldForChargePitches = g_Pitcher.framesAHeldForChargePitches + 1;
        if ((g_Pitcher.AIInd == 0 && !(controls->buttonInput & INPUT_BUTTON_A)) ||
            (g_Pitcher.AIInd == 1 && g_AiLogic.aIPitchType == 0)) {
            g_Pitcher.ChargePitchType = 0;
        } else {
            g_Pitcher.ChargePitchType = 1;
        }
        if (g_Pitcher.framesAHeldForChargePitches >= lbl_3_data_5F3C[0]) {
            g_Pitcher.framesAHeldForChargePitches = 0;
        } else {
            return;
        }
    }
    if (g_Pitcher.pitchTotalTimeCounter < 0x7FFE) {
        g_Pitcher.pitchTotalTimeCounter++;
    } else {
        g_Pitcher.pitchTotalTimeCounter = 0x7FFF;
    }
    if (g_Pitcher.pitchTotalTimeCounter == 1) {
        if (g_Pitcher.starPitchInd != 0 && !g_d_GameSettings.minigamesEnabled &&
            g_GameLogic.TeamStars[g_GameLogic.teamFielding] != 0 &&
            getAdjustedPitcherStamina(g_GameLogic.teamFielding, g_Pitcher.rosterID, 0) >= lbl_3_data_5EDC[4] &&
            (inningSetting.starSkillsSetting != 0 || g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE)) {
            if (g_Pitcher.captainStarPitch == 0) {
                if (g_GameLogic.TeamStars[g_GameLogic.teamFielding] >= starPowerCosts.regularStarCost &&
                    g_Pitcher.nonCaptainStarPitch != 0) {
                    fn_3_740D0();
                } else {
                    g_Pitcher.starPitchInd = 0;
                }
            } else if (g_GameLogic.Team_CaptainRosterLoc[g_GameLogic.teamFielding] != g_Pitcher.rosterID &&
                       g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE) {
                if (g_GameLogic.TeamStars[g_GameLogic.teamFielding] >= starPowerCosts.nonCaptain_CaptainStarCost) {
                    g_Pitcher.starPitchType = g_Pitcher.captainStarPitch;
                } else {
                    g_Pitcher.starPitchInd = 0;
                }
            } else {
                if (g_GameLogic.TeamStars[g_GameLogic.teamFielding] >= starPowerCosts.captainStarCost) {
                    g_Pitcher.starPitchType = g_Pitcher.captainStarPitch;
                } else {
                    g_Pitcher.starPitchInd = 0;
                }
            }
        }
        fn_3_73FAC();
        g_Pitcher.unknownFrameCounter = 0;
        g_Pitcher.pitchChargeUp = 0.0f;
        g_Pitcher.pitchChargeUpAnimationProportion = 0.0f;
    }
    if (g_Pitcher.AIInd != 0) {
        if (g_AiLogic.aIPitchType == 1 || g_AiLogic.aIPitchType == 3) {
            if (g_AiLogic.aIPitchType != 3) {
                if (g_AiLogic.aIPerfectCharge != 0) {
                    g_Pitcher.ChargePitchType = 3;
                } else {
                    g_Pitcher.ChargePitchType = 2;
                }
            }
            g_Pitcher.pitchChargeUp = 1.0f;
            g_Pitcher.unknownFrameCounter++;
            g_Pitcher.pitchChargeUpAnimationProportion = 1.0f - (f32)(g_Pitcher.windupCountdownUntilBallReleased - 1) /
                                                                                 (f32)g_Pitcher.pitchWindUpCountDown;
            if (g_Pitcher.pitchChargeUpAnimationProportion > 1.0f) {
                g_Pitcher.pitchChargeUpAnimationProportion = 1.0f;
            }
        } else if (g_Pitcher.starPitchInd != 0) {
            g_Pitcher.unknownFrameCounter++;
        }
    } else {
        if (g_Pitcher.ChargePitchType == 1 || g_Pitcher.starPitchInd != 0 || g_Pitcher.ballHaloTrainInd_unused != 0) {
            if ((g_Pitcher.AIInd == 0 && (controls->buttonInput & INPUT_BUTTON_A)) ||
                (g_Pitcher.AIInd == 1 && g_AiLogic.aIPitchType == 1) || g_Pitcher.starPitchInd != 0 ||
                g_Pitcher.ballHaloTrainInd_unused != 0) {
                g_Pitcher.unknownFrameCounter++;
            } else {
                g_Pitcher.ChargePitchType = 2;
                if (g_Pitcher.windupCountdownUntilBallReleased < lbl_3_data_5F3C[2]) {
                    g_Pitcher.ChargePitchType = 3;
                    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_WALLBALL) {
                        playSoundEffect(0x1B5);
                    } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE &&
                               (g_Practice.practiceLevel == 5 ||
                                (g_Practice.practiceType_2 == PRACTICE_TYPE_PITCHING && g_Practice.practiceLevel == 1))) {
                        playSoundEffect(0x1B5);
                    }
                } else if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_WALLBALL) {
                    playSoundEffect(0x1B4);
                } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE &&
                           (g_Practice.practiceLevel == 5 ||
                            (g_Practice.practiceType_2 == PRACTICE_TYPE_PITCHING && g_Practice.practiceLevel == 1))) {
                    playSoundEffect(0x1B4);
                }
            }
            if (g_Pitcher.ChargePitchType != 0) {
                g_Pitcher.pitchChargeUp = 1.0f - (f32)(g_Pitcher.windupCountdownUntilBallReleased - 1) /
                                                                  (f32)g_Pitcher.pitchWindUpCountDown;
                if (g_Pitcher.pitchChargeUp > 1.0f) {
                    g_Pitcher.pitchChargeUp = 1.0f;
                }
            } else {
                g_Pitcher.pitchChargeUp = 0.0f;
            }
            g_Pitcher.pitchChargeUpAnimationProportion = g_Pitcher.pitchChargeUp;
        } else if (g_Pitcher.ChargePitchType != 0 || g_Pitcher.TypeOfPitch == 2) {
            g_Pitcher.pitchChargeUpAnimationProportion = 1.0f - (f32)(g_Pitcher.windupCountdownUntilBallReleased - 1) /
                                                                                 (f32)g_Pitcher.pitchWindUpCountDown;
            if (g_Pitcher.pitchChargeUpAnimationProportion > 1.0f) {
                g_Pitcher.pitchChargeUpAnimationProportion = 1.0f;
            }
        }
    }
    g_Pitcher.windupCountdownUntilBallReleased = g_Pitcher.windupCountdownUntilBallReleased - 1;
    if (g_Pitcher.windupCountdownUntilBallReleased <= 0) {
        if (g_Pitcher.ChargePitchType == 1) {
            g_Pitcher.pitchChargeUp = RandomF32_Game_Range(lbl_3_data_5F08[11], lbl_3_data_5F08[12]);
            g_Pitcher.overChargeInd = 1;
        }
        pitchBeingReleased();
        if (g_Pitcher.ChargePitchType == 3) {
            g_UnkSound_32718._08 = 1;
            perfectPitchGraphicsRelated();
        }
        if (g_Pitcher.specialPitchTypeCode != 1 && g_Pitcher.specialPitchTypeCode != 2 && g_Pitcher.specialPitchTypeCode != 3 &&
            g_Pitcher.nonCaptainStarPitchTriggeredType == 0 && g_d_GameSettings.GameModeSelected != GAME_TYPE_MINIGAMES) {
            g_GameLogic.PauseSimulationFrameCount = lbl_3_data_5FC0[1];
        } else {
            g_GameLogic.PauseSimulationFrameCount = lbl_3_data_5FC0[0];
        }
        if (g_GameLogic.PauseSimulationFrameCount != 0) {
            lbl_80366158._28 = 1;
        }
        g_Pitcher.pitcherActionState = PITCHER_ACTION_STATE_IN_AIR;
        g_Pitcher.currentStateFrameCounter = 0;
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY &&
            g_Minigame.bOD_KingBombInd == 0) {
            bODPitchAnimation();
        }
    }
    g_Ball.AtBat_Contact_BallPos.x = g_Pitcher.ballCurrentPosition.x;
    g_Ball.AtBat_Contact_BallPos.y = g_Pitcher.ballCurrentPosition.y;
    g_Ball.AtBat_Contact_BallPos.z = g_Pitcher.ballCurrentPosition.z;
}

// .text:0x000740D0 size:0x58 mapped:0x806B3164
void fn_3_740D0(void) {
    u8 type = g_Pitcher.nonCaptainStarPitch;
    g_Pitcher.nonCaptainStarPitchTriggeredType = type;
    switch (type) {
    case 1:
        g_Pitcher.specialPitchTypeCode = 0x10;
        break;
    case 2:
        g_Pitcher.specialPitchTypeCode = 0x11;
        break;
    case 3:
        g_Pitcher.specialPitchTypeCode = 0x12;
        break;
    }
}

// .text:0x00073FAC size:0x124 mapped:0x806B3040
void fn_3_73FAC(void) {
    g_Pitcher.eggBallBounceYHeight = g_Batter.batPosition2.y;
    g_Pitcher.pitchStartingPosition_AIMaxCurve =
        LinearInterpolateToNewRange(g_Pitcher.pitcher.x, lbl_3_data_4474[0], lbl_3_data_4474[1], lbl_3_data_5EB0[0], lbl_3_data_5EB0[1]);
    if (g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_WARIO || g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_WALUIGI) {
        g_Pitcher.pitchStartingPosition_AIMaxCurve = 0.0f;
    } else if (g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_YOSHI || g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_BIRDO) {
        g_Pitcher.pitchStartingPosition_AIMaxCurve = RandomF32_Game_Range(-eggConstants[3], eggConstants[3]);
        g_Pitcher.eggBallBounceYHeight = eggConstants[0];
        g_Pitcher.frontOfPlateZ = RandomF32_Game_Range(eggConstants[1], eggConstants[2]);
    }
    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY ||
        g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER) {
        f32 m = bOD_bB_maxMovement[g_Minigame.soloMinigameDifficulty];
        g_Pitcher.pitchStartingPosition_AIMaxCurve = RandomF32_Game_Range(-m, m);
    }
}

// .text:0x00073F2C size:0x80 mapped:0x806B2FC0
void fn_3_73F2C(void) {
    if (g_Pitcher.pitchTotalTimeCounter < 0x7FFE) {
        g_Pitcher.pitchTotalTimeCounter++;
    } else {
        g_Pitcher.pitchTotalTimeCounter = 0x7FFF;
    }
    if (g_Ball.pitchHangtimeCounter < 0x7FFE) {
        g_Ball.pitchHangtimeCounter++;
    } else {
        g_Ball.pitchHangtimeCounter = 0x7FFF;
    }
    g_Pitcher.warioWaluStarAnimationStage = 0;
    pitchInAirFunction();
}

// .text:0x00073DE8 size:0x144 mapped:0x806B2E7C
void fn_3_73DE8(void) {
    if (g_Pitcher.pitchTotalTimeCounter < 0x7FFE) {
        g_Pitcher.pitchTotalTimeCounter++;
    } else {
        g_Pitcher.pitchTotalTimeCounter = 0x7FFF;
    }
    if (g_Ball.postPitchResultCounter < 0x7FFE) {
        g_Ball.postPitchResultCounter++;
    } else {
        g_Ball.postPitchResultCounter = 0x7FFF;
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES &&
        (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY ||
         g_Minigame.GameMode_MiniGame == MINI_GAME_ID_WALLBALL ||
         g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER)) {
        g_Pitcher.miniGameRelated = 1;
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY) {
            bobOmbDerbyPitching();
        }
    } else if (g_Pitcher.miniGameRelated == 0) {
        pitchCall();
        return;
    }
    if (runnerStealing_TransitionToLiveViewIndicator() == 0) {
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE || g_Practice.guidedPracticeCompletionRelated == 0) {
            if (g_Pitcher.currentStateFrameCounter > 0x4B) {
                g_GameLogic.playBatterWalkupAnimation = 0;
                SetGameStatus(0);
            }
        }
        lastPlayStats();
    }
}

// .text:0x000738A8 size:0x540 mapped:0x806B293C
void endAtBatNonHit(void) {
    int transitionFrames = 0x78;
    int frame;
    if (g_Pitcher.pitchTotalTimeCounter < 0x7FFE) {
        g_Pitcher.pitchTotalTimeCounter++;
    } else {
        g_Pitcher.pitchTotalTimeCounter = 0x7FFF;
    }
    if (g_Pitcher.framesSinceAtBatEnded < 0x7FFE) {
        g_Pitcher.framesSinceAtBatEnded++;
    } else {
        g_Pitcher.framesSinceAtBatEnded = 0x7FFF;
    }
    if (g_d_GameSettings.minigamesEnabled) {
        return;
    }
    if (g_GameLogic.gameOverInd != 0) {
        transitionFrames = 0xC3;
    } else if (g_Batter.hitByPitch != 0) {
        transitionFrames = 0x5A;
    } else {
        if (g_Ball.postPitchResultCounter < 0x7FFE) {
            g_Ball.postPitchResultCounter++;
        } else {
            g_Ball.postPitchResultCounter = 0x7FFF;
        }
        if (runnerStealing_TransitionToLiveViewIndicator() != 0) {
            return;
        }
    }
    if (g_Pitcher.framesSinceAtBatEnded == 1) {
        if (!g_d_GameSettings.exhibitionMatchInd && lbl_3_common_bss_37400.scoutMissionID != 0 && g_Stats.replayInd == 0) {
            challengeModeRelated_checkScoutMissionSuccess();
            lbl_3_common_bss_37400.scoutCountdown = 0xB4;
        }
        if ((g_Pitcher.strikeOutOrWalk == 2 || g_Pitcher.strikeOutOrWalk == 3) && g_RunningLogic._10 == 4) {
            if (g_Scores.halfInning != 0) {
                if (g_Scores.Inning >= g_Scores.inningLimit && g_Scores.scores[0].total == g_Scores.scores[1].total) {
                    QueueTextToDisplay(0xD, 0);
                    g_GameLogic.gameOverInd = 1;
                } else if (g_Scores.mercyThreshold != 0 &&
                           g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total -
                                   g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total + 1 >=
                               g_Scores.mercyThreshold) {
                    QueueTextToDisplay(0x11, 0);
                    g_GameLogic.gameOverInd = 1;
                }
            }
            g_Pitcher.walkedInRunInd = 1;
        }
    }
    if (!g_d_GameSettings.exhibitionMatchInd && lbl_3_common_bss_37400.scoutMissionID != 0 && g_Stats.replayInd == 0 &&
        lbl_3_common_bss_37400.scoutFlag == 0) {
        lbl_3_common_bss_37400.scoutCountdown = lbl_3_common_bss_37400.scoutCountdown - 1;
        if (lbl_3_common_bss_37400.scoutCountdown == 0x78) {
            animRelated[0xB4] = 1;
        }
        transitionFrames = 0x78;
    }
    frame = g_Pitcher.framesSinceAtBatEnded;
    if (frame == 1) {
        if (transitionFrames > 0x78) {
            sound_crowd_EffectsStruct._2A = 1;
            sound_crowd_EffectsStruct._24 = 0x77;
        } else {
            sound_crowd_EffectsStruct._2A = 1;
            sound_crowd_EffectsStruct._24 = transitionFrames - 1;
        }
    }
    if (frame == transitionFrames - 0xB) {
        if (animRelated[0xB1] == 0) {
            changeScene(3, 6);
        }
    } else if (frame == transitionFrames - 0x1F) {
        if (lbl_3_common_bss_32220[3] > 0x1D) {
            g_Pitcher.framesSinceAtBatEnded -= 1;
        } else {
            determineIfReplayShouldPlay();
            if (g_Stats._0038[1] != 0) {
                animRelated[0xB1] = 1;
            }
        }
    } else if (frame >= transitionFrames) {
        g_GameLogic.hudLoadingRelated = 1;
        g_Ball.postPitchResultCounter = -1;
        g_Pitcher.pitcherActionState = PITCHER_ACTION_STATE_POST_HIT;
        g_Pitcher.currentStateFrameCounter = 0;
        if (g_Pitcher.strikeOutOrWalk == 1) {
            fn_3_73850();
        } else if (g_Pitcher.strikeOutOrWalk == 2 || g_Pitcher.strikeOutOrWalk == 3) {
            advanceForcedRunners();
        }
        if (g_Stats._0038[1] != 0) {
            transitionToReplay();
        }
    }
}

// .text:0x00073850 size:0x58 mapped:0x806B28E4
void fn_3_73850(void) {
    int i;
    g_Strikes.outs++;
    for (i = 0; i < 3; i++) {
        if (g_Strikes.runnerIndexForEachOutThisPitch[i] == -1) {
            g_Strikes.runnerIndexForEachOutThisPitch[i] = 0;
            return;
        }
    }
}

// .text:0x0007372C size:0x124 mapped:0x806B27C0
void fn_3_7372C(void) {
    int i;
    int seenOther = 0;
    if (g_Pitcher.strikeOutOrWalk == 3) {
        for (i = 1; i < 4; i++) {
            InMemRunnerType* r = &g_Runners[i];
            if (r->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD ||
                r->runnerOnFieldOrOutOrScored == RUNNER_STATUS_WALK_WHILE_STEALING) {
                if (seenOther == 0) {
                    r->currentBase = i;
                    updateRunnerPosition(i, 1);
                } else {
                    r->currentBase = r->startingBase_baseAchieved;
                    r->nextBase = (r->currentBase + 1) & 3;
                }
            } else {
                seenOther = 1;
            }
        }
    } else {
        for (i = 1; i < 4; i++) {
            InMemRunnerType* r = &g_Runners[i];
            if (r->runnerOnFieldOrOutOrScored != RUNNER_STATUS_ON_FIELD &&
                r->runnerOnFieldOrOutOrScored != RUNNER_STATUS_WALK_WHILE_STEALING) {
                break;
            }
            if (i == r->currentBase) {
                updateRunnerPosition(i, 1);
            }
        }
    }
    g_Runners[0].currentBase = 1;
    g_Runners[0].nextBase = 2;
}

// .text:0x00073718 size:0x14 mapped:0x806B27AC
void resetCounter(void) {
    g_Ball.postPitchResultCounter = -1;
}

// .text:0x000736CC size:0x4C mapped:0x806B2760
void resetBatterCount(void) {
    int i;
    for (i = 0; i < 3; i++) {
        if (g_Strikes.runnerIndexForEachOutThisPitch[i] == -1) {
            g_Strikes.runnerIndexForEachOutThisPitch[i] = 0;
            return;
        }
    }
}

// .text:0x000735A8 size:0x124 mapped:0x806B263C
void handleHPBORRunnerAdvance(void) {
    int i;
    int seenOther = 0;
    if (g_Pitcher.strikeOutOrWalk == 3) {
        for (i = 1; i < 4; i++) {
            InMemRunnerType* r = &g_Runners[i];
            if (r->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD ||
                r->runnerOnFieldOrOutOrScored == RUNNER_STATUS_WALK_WHILE_STEALING) {
                if (seenOther == 0) {
                    r->currentBase = i;
                    updateRunnerPosition(i, 1);
                } else {
                    r->currentBase = r->startingBase_baseAchieved;
                    r->nextBase = (r->currentBase + 1) & 3;
                }
            } else {
                seenOther = 1;
            }
        }
    } else {
        for (i = 1; i < 4; i++) {
            InMemRunnerType* r = &g_Runners[i];
            if (r->runnerOnFieldOrOutOrScored != RUNNER_STATUS_ON_FIELD &&
                r->runnerOnFieldOrOutOrScored != RUNNER_STATUS_WALK_WHILE_STEALING) {
                break;
            }
            if (i == r->currentBase) {
                updateRunnerPosition(i, 1);
            }
        }
    }
    g_Runners[0].currentBase = 1;
    g_Runners[0].nextBase = 2;
}

// .text:0x0007310C size:0x49C mapped:0x806B21A0
void pitchBeingReleased(void) {
    int character;
    VecXYZ ballCoords;
    if (g_Pitcher.starPitchInd != 0) {
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE || g_Practice.practiceLevel == 7) {
            if (g_Pitcher.nonCaptainStarPitchTriggeredType != 0) {
                if (g_GameLogic.TeamStars[g_GameLogic.teamFielding] >= starPowerCosts.regularStarCost) {
                    g_GameLogic.TeamStars[g_GameLogic.teamFielding] -= starPowerCosts.regularStarCost;
                } else {
                    g_GameLogic.TeamStars[g_GameLogic.teamFielding] = 0;
                }
            } else if (g_GameLogic.Team_CaptainRosterLoc[g_GameLogic.teamFielding] != g_Pitcher.rosterID &&
                       g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE) {
                if (g_GameLogic.TeamStars[g_GameLogic.teamFielding] >= starPowerCosts.nonCaptain_CaptainStarCost) {
                    g_GameLogic.TeamStars[g_GameLogic.teamFielding] -= starPowerCosts.nonCaptain_CaptainStarCost;
                } else {
                    g_GameLogic.TeamStars[g_GameLogic.teamFielding] = 0;
                }
            } else {
                if (g_GameLogic.TeamStars[g_GameLogic.teamFielding] >= starPowerCosts.captainStarCost) {
                    g_GameLogic.TeamStars[g_GameLogic.teamFielding] -= starPowerCosts.captainStarCost;
                } else {
                    g_GameLogic.TeamStars[g_GameLogic.teamFielding] = 0;
                }
            }
        }
        g_AiLogic.nStarPitchesThrownThisAB++;
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        if (g_Minigame.miniGameTurnCounter < 0xFE) {
            g_Minigame.miniGameTurnCounter++;
        } else {
            g_Minigame.miniGameTurnCounter = 0xFF;
        }
        if (g_Minigame.bB_pitchesRemainingInTurn != 0) {
            g_Minigame.bB_pitchesRemainingInTurn--;
        }
    }
    character = 0;
    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY || g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER ||
        (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_Practice.practiceLevel == 4)) {
        ballCoords.x = lbl_3_data_21380[0];
        ballCoords.y = lbl_3_data_21380[1];
        ballCoords.z = lbl_3_data_21380[2];
        ballCoords.y = -ballCoords.y;
    } else {
        if (g_d_GameSettings.minigamesEnabled) {
            character = g_Minigame.minigameControlStruct[0].characterIndex[MINIGAME_SELECTED_ORDER];
        }
        if (g_Pitcher.charID == CHAR_ID_PETEY) {
            getAnimRelatedCoordinates(character, 9, &ballCoords);
        } else if (g_Pitcher.handedness == 0) {
            getAnimRelatedCoordinates(character, 0x19, &ballCoords);
        } else {
            getAnimRelatedCoordinates(character, 0x13, &ballCoords);
        }
    }
    g_Pitcher.pitchRelease.x = g_Pitcher.ballCurrentPosition.x = ballCoords.x;
    g_Pitcher.pitchRelease.y = g_Pitcher.ballCurrentPosition.y = -ballCoords.y;
    g_Pitcher.pitchRelease.z = g_Pitcher.ballCurrentPosition.z = ballCoords.z;
    if (g_Pitcher.nonCaptainStarPitchTriggeredType != 0) {
        g_Pitcher.TypeOfPitch = 0;
    } else if (g_Pitcher.starPitchType != 0) {
        g_Pitcher.specialPitchTypeCode = g_Pitcher.starPitchType + 3;
        g_Pitcher.TypeOfPitch = lbl_3_data_5F44[g_Pitcher.specialPitchTypeCode - 4];
    } else if (g_Pitcher.TypeOfPitch == 2) {
        g_Pitcher.specialPitchTypeCode = 3;
    } else {
        g_Pitcher.specialPitchTypeCode = 1;
        if (g_Pitcher.ChargePitchType >= 1) {
            g_Pitcher.TypeOfPitch = 1;
        } else {
            g_Pitcher.TypeOfPitch = 0;
        }
    }
    adjustPitchCurveSpeedCursedBall();
    pitchSetPhysicsConstants();
    g_Ball.framesSinceHit = -1;
    g_Ball.pitchHangtimeCounter = 0;
    g_Ball.postPitchResultCounter = -1;
    g_Ball.fielderWBallIndex = -1;
    g_Ball.AtBat_ContactResult = BALL_RESULT_TYPE_IN_AIR;
    g_Ball.ballState = BALL_STATE_HIT;
    g_Pitcher.pitchCurveVeloV1 = 0.0f;
    g_Pitcher._60 = 0.0f;
    g_Pitcher.pitchCurveVeloV2 = 0.0f;
    g_Pitcher._68 = 0.0f;
    g_Pitcher.cancelParabolicAdjustmentInd = 0;
    g_Pitcher.strikeZoneProcessNumber = 0;
    g_Pitcher.nPickoffAttempts = 0;
    g_Pitcher._10C[1] = 0.0f;
    g_Pitcher._10C[2] = 0.0f;
    g_Minigame._1911 = 0;
    sndFXKeyOff(lbl_3_bss_172C[0]);
    batterAISwingEarlyOrLate();
    if (g_Pitcher.nPitchesThisAB < 0xFE) {
        g_Pitcher.nPitchesThisAB++;
    } else {
        g_Pitcher.nPitchesThisAB = 0xFF;
    }
    pitchInAirFunction();
    incrementPitchCount();
    if (g_Pitcher.AIInd == 0 && (g_Pitcher.ChargePitchType == 3 || g_Pitcher.nonCaptainStarPitchTriggeredType != 0 ||
                                 g_Pitcher.starPitchType != 0)) {
        if (g_d_GameSettings.minigamesEnabled) {
            setCharacterAnimations(g_Minigame.minigameControlStruct[0].characterIndex[MINIGAME_SELECTED_ORDER], 2);
        } else {
            setCharacterAnimations(g_GameLogic.teamFielding, 2);
        }
    }
}

// .text:0x00072CA8 size:0x464 mapped:0x806B1D3C
void adjustPitchCurveSpeedCursedBall(void) {
    f32 cursedBall = g_Pitcher.cursedBallStat;
    f32 curveControl = g_Pitcher.curveControlStat;
    f32 curve = g_Pitcher.curveStat;
    if (g_Pitcher.starPitchType != 0) {
        g_Pitcher.pitchSpeed = pitchConstantsArray[g_Pitcher.specialPitchTypeCode][0];
        g_Pitcher.calced_cursedBall = 100;
        g_Pitcher.calced_curveControl = 100;
        g_Pitcher.calced_curve = 100;
        if (g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_YOSHI || g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_BIRDO) {
            g_Pitcher.pitchSpeed = RandomInt_Game_Range(lbl_3_data_5F7C[0], lbl_3_data_5F7C[1]);
        }
    } else {
        if (g_Pitcher.ChargePitchType == 3 || g_Pitcher.nonCaptainStarPitchTriggeredType == 2) {
            g_Pitcher.pitchSpeed = (f32)g_Pitcher.fastBallSpeed * lbl_3_data_5F08[10];
        } else if (g_Pitcher.ChargePitchType != 0) {
            if (g_Pitcher.ChargePitchType == 1) {
                g_Pitcher.ChargePitchType = 2;
            }
            g_Pitcher.pitchSpeed = g_Pitcher.fastBallSpeed -
                                   (int)(lbl_3_data_5F08[9] * ((f32)g_Pitcher.fastBallSpeed - (f32)g_Pitcher.curveBallSpeed) *
                                         (maxPitchCharge - g_Pitcher.pitchChargeUp));
        } else {
            if (g_Pitcher.TypeOfPitch == 2) {
                g_Pitcher.pitchSpeed = g_Pitcher.curveBallSpeed;
            } else {
                g_Pitcher.pitchSpeed = g_Pitcher.curveBallSpeed;
            }
        }
        if (g_Pitcher.ChargePitchType >= 2 || g_Pitcher.TypeOfPitch == 2 || g_Pitcher.nonCaptainStarPitchTriggeredType == 2 ||
            g_Pitcher.nonCaptainStarPitchTriggeredType == 3) {
            cursedBall = cursedBall * lbl_3_data_5F08[8];
            curveControl = curveControl * lbl_3_data_5F08[5];
            curve = curve * lbl_3_data_5F08[2];
        }
        if (g_Pitcher.nonCaptainStarPitchTriggeredType == 0 &&
            getAdjustedPitcherStamina(g_GameLogic.teamFielding, g_Pitcher.rosterID, 0) < lbl_3_data_5EDC[3]) {
            if (g_Pitcher.ChargePitchType != 0) {
                g_Pitcher.pitchSpeed = (f32)g_Pitcher.pitchSpeed * -(0.01f * (f32)lbl_3_data_5EDC[6] - 1.0f);
            } else if (g_Pitcher.TypeOfPitch != 2) {
                curve = curve * -(0.01f * (f32)lbl_3_data_5EDC[5] - 1.0f);
            }
            curveControl = curveControl * -(0.01f * (f32)lbl_3_data_5EDC[7] - 1.0f);
            cursedBall = cursedBall * -(0.01f * (f32)lbl_3_data_5EDC[8] - 1.0f);
        }
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY ||
            g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER) {
            g_Pitcher.pitchSpeed = g_Minigame.minigamePitchSpeedAdjustment;
        }
        g_Pitcher.calced_cursedBall = cursedBall;
        g_Pitcher.calced_curveControl = curveControl;
        g_Pitcher.calced_curve = curve;
    }
}

// .text:0x00072768 size:0x540 mapped:0x806B17FC
void pitchSetPhysicsConstants(void) {
    InputStruct* controls = &g_Controls[g_GameLogic.teams[g_GameLogic.teamFielding]];
    s16* pc;
    f32 ballZ;
    f32 veloZ;
    f32 dx;
    f32 dy;
    f32 dz;
    int frame;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_Practice.instructionNumber >= 0) {
        controls = &g_Practice.inputs[g_GameLogic.teamFielding];
    } else if (AI_getPort(g_Minigame.minigameControlStruct[0].characterIndex[MINIGAME_SELECTED_ORDER]) != 0) {
        controls = &g_Minigame._1D7C[g_Minigame.minigameControlStruct[0].characterIndex[MINIGAME_SELECTED_ORDER]];
    } else if (g_d_GameSettings.minigamesEnabled && MINIGAME_SELECTED_ORDER >= 0) {
        controls = &g_Controls[g_Minigame.minigameControlStruct[0].characterIndex[MINIGAME_SELECTED_ORDER]];
    }
    dz = g_Pitcher.ballCurrentPosition.z - g_Pitcher.frontOfPlateZ;
    pc = pitchConstantsArray[g_Pitcher.specialPitchTypeCode];
    dx = g_Pitcher.pitchStartingPosition_AIMaxCurve - g_Pitcher.ballCurrentPosition.x;
    dy = g_Pitcher.eggBallBounceYHeight - g_Pitcher.ballCurrentPosition.y;
    g_Pitcher.moundZ = 18.44f;
    g_Pitcher.pitchZ_whenAirResistanceStarts = (18.44f * (f32)(100 - pc[4])) / 100.0f;
    g_Pitcher.ballVelocity.z = -((f32)g_Pitcher.pitchSpeed / g_Pitcher.pitchSpeedScaler);
    g_Pitcher.ballVelocity.y = -(dy * g_Pitcher.ballVelocity.z / dz);
    g_Pitcher.airResistance_veloAdj = 0.001f * (f32)pc[3];
    g_Pitcher.ballVelocity.x = -(dx * g_Pitcher.ballVelocity.z / dz);
    veloZ = g_Pitcher.ballVelocity.z;
    ballZ = g_Pitcher.ballCurrentPosition.z;
    for (frame = 1; frame < 0xFFFF; frame++) {
        f32 newVelo;
        if (ballZ <= g_Pitcher.moundZ && g_Pitcher.pitchInAirInd == 0) {
            g_Pitcher.pitchInAirInd = frame;
        }
        if (ballZ <= g_Pitcher.pitchZ_whenAirResistanceStarts) {
            if (g_Pitcher.frameBallCanStartBeingControlled == 0) {
                g_Pitcher.frameBallCanStartBeingControlled = frame;
            }
            newVelo = veloZ - veloZ * g_Pitcher.airResistance_veloAdj;
            if (newVelo < -0.05f) {
                veloZ = newVelo;
            }
        }
        veloZ = veloZ * g_Pitcher.decelerationFactor;
        ballZ = ballZ + veloZ;
        if (ballZ <= g_Pitcher.frontOfPlateZ) {
            g_Pitcher.frameWhenUnhittable = frame;
            break;
        }
    }
    g_Pitcher.verticalGlobalParabolicVelo = (f32)pc[5];
    if (g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_YOSHI || g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_BIRDO) {
        g_Pitcher.verticalGlobalParabolicVelo = (f32)RandomInt_Game_Range(lbl_3_data_5F7C[2], lbl_3_data_5F7C[3]);
    }
    g_Pitcher.verticalOffsetParabolaMidpoint =
        ((f32)g_Pitcher.frameWhenUnhittable / 2.0f) *
        (g_Pitcher.verticalGlobalParabolicVelo * ((f32)g_Pitcher.frameWhenUnhittable / 2.0f)) / 10000.0f;
    g_Pitcher.horizontalGlobalParabolicVelo = (f32)pc[6];
    if (g_Pitcher.handedness != 0) {
        g_Pitcher.horizontalGlobalParabolicVelo = -g_Pitcher.horizontalGlobalParabolicVelo;
    }
    g_Pitcher.horizontalOffsetParabolaMidpoint =
        ((f32)g_Pitcher.frameWhenUnhittable / 2.0f) *
        (g_Pitcher.horizontalGlobalParabolicVelo * ((f32)g_Pitcher.frameWhenUnhittable / 2.0f)) / 10000.0f;
    if (g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_WARIO || g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_WALUIGI) {
        if (g_Pitcher.AIInd != 0) {
            g_Pitcher.warioWaluStarPitchRightLeft = RandomInt_Game(2);
        } else if (controls->buttonInput & INPUT_BUTTON_RIGHT) {
            g_Pitcher.warioWaluStarPitchRightLeft = 0;
        } else if (controls->buttonInput & INPUT_BUTTON_LEFT) {
            g_Pitcher.warioWaluStarPitchRightLeft = 1;
        } else {
            g_Pitcher.warioWaluStarPitchRightLeft = RandomInt_Game(2);
        }
    }
    if (g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_BOWSER || g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_BOWSERJR) {
        int bi = (g_Pitcher.starPitchType - CAPTAIN_STAR_TYPE_BOWSER) * 5;
        g_Pitcher.bulletPitchLoopFrames = RandomInt_Game_Range(bulletBallConstants[bi], bulletBallConstants[bi + 1]);
        g_Pitcher.bulletPitchLoopStartingFrame = RandomInt_Game_Range(bulletBallConstants[bi + 2], bulletBallConstants[bi + 3]);
        g_Pitcher.frameWhenUnhittable = g_Pitcher.frameWhenUnhittable + g_Pitcher.bulletPitchLoopFrames;
    }
}

// .text:0x00071248 size:0x1520 mapped:0x806B02DC
void pitchInAirFunction(void) {
    f32 ground;
    f32 amp;
    f32 sinVal;
    f32 prop;
    f32 d;
    VecSrcDst probe;
    CollisionStruct hit;
    u32 collType;
    int stadium;
    int idx;

    if (g_Pitcher.eggBallBounceNumber != 0) {
        g_Pitcher.framesSinceFirstEggBounce = g_Pitcher.framesSinceFirstEggBounce + 1;
    }
    g_Pitcher.ballLastPosition.x = g_Pitcher.ballCurrentPosition.x;
    g_Pitcher.ballLastPosition.y = g_Pitcher.ballCurrentPosition.y;
    g_Pitcher.ballLastPosition.z = g_Pitcher.ballCurrentPosition.z;
    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_WALLBALL && g_Minigame.ballStoppedBreakingWallsInd) {
        g_Pitcher.ballVelocity.y = g_Pitcher.ballVelocity.y - g_Ball.physicsSubstruct.gravity;
        g_Pitcher.ballCurrentPosition.x = g_Pitcher.ballCurrentPosition.x + g_Pitcher.ballVelocity.x;
        g_Pitcher.ballCurrentPosition.z = g_Pitcher.ballCurrentPosition.z + g_Pitcher.ballVelocity.z;
        g_Pitcher.ballCurrentPosition.y = g_Pitcher.ballCurrentPosition.y + g_Pitcher.ballVelocity.y;
        if (g_Ball.AtBat_Contact_BallPos.y < g_Ball.groundYForBounces) {
            g_Pitcher.ballCurrentPosition.y = g_Ball.groundYForBounces;
            stadium = g_d_GameSettings.StadiumID;
            g_Pitcher.ballVelocity.x = g_Pitcher.ballVelocity.x * ballBounceConstants[stadium].rollingSpeedKept;
            g_Pitcher.ballVelocity.z = g_Pitcher.ballVelocity.z * ballBounceConstants[stadium].rollingSpeedKept;
            g_Pitcher.ballVelocity.y = g_Pitcher.ballVelocity.y * -ballBounceConstants[stadium].yOtherBouncesSpeedKept;
        }
        g_Ball.AtBat_Contact_BallPos.x = g_Pitcher.ballCurrentPosition.x;
        g_Ball.AtBat_Contact_BallPos.y = g_Pitcher.ballCurrentPosition.y;
        g_Ball.AtBat_Contact_BallPos.z = g_Pitcher.ballCurrentPosition.z;
    } else {
        do {
            if (g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_BOWSER || g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_BOWSERJR) {
                if (g_Ball.pitchHangtimeCounter >= g_Pitcher.bulletPitchLoopStartingFrame &&
                    g_Pitcher.bulletPitchStageCode == 0) {
                    g_Pitcher.bulletPitchStageCode = 1;
                }
                if (g_Pitcher.bulletPitchStageCode == 1) {
                    fn_3_709B4();
                    break;
                }
            }
            if (g_Pitcher.ballCurrentPosition.z <= g_Pitcher.pitchZ_whenAirResistanceStarts) {
                d = g_Pitcher.ballVelocity.z - g_Pitcher.ballVelocity.z * g_Pitcher.airResistance_veloAdj;
                if (d < -0.05f) {
                    g_Pitcher.ballVelocity.z = d;
                    g_Pitcher.ballVelocity.x -= g_Pitcher.ballVelocity.x * g_Pitcher.airResistance_veloAdj;
                    g_Pitcher.ballVelocity.y -= g_Pitcher.ballVelocity.y * g_Pitcher.airResistance_veloAdj;
                }
            }
            pitchCurve();
            g_Pitcher.ballVelocity.x = g_Pitcher.ballVelocity.x * g_Pitcher.decelerationFactor;
            g_Pitcher.ballVelocity.y = g_Pitcher.ballVelocity.y * g_Pitcher.decelerationFactor;
            g_Pitcher.ballVelocity.z = g_Pitcher.ballVelocity.z * g_Pitcher.decelerationFactor;
            updatePitchYParabola();
            fn_3_70AEC();
            g_Pitcher.ballVelocity.x = g_Pitcher.ballVelocity.x + g_Pitcher.pitchCurveVeloV1;
            g_Pitcher.ballCurrentPosition.x = g_Pitcher.ballCurrentPosition.x + g_Pitcher.ballVelocity.x;
            g_Pitcher.ballCurrentPosition.y = g_Pitcher.ballCurrentPosition.y + g_Pitcher.ballVelocity.y;
            g_Pitcher.ballCurrentPosition.z = g_Pitcher.ballCurrentPosition.z + g_Pitcher.ballVelocity.z;
        } while (0);
        g_Ball.AtBat_Contact_BallPos.x = g_Pitcher.ballCurrentPosition.x + g_Pitcher.pitchX_parabolicAdjustment;
        g_Ball.AtBat_Contact_BallPos.y = g_Pitcher.ballCurrentPosition.y + g_Pitcher.pitchY_parabolicAdjustment;
        g_Ball.AtBat_Contact_BallPos.z = g_Pitcher.ballCurrentPosition.z;
        if ((g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_BOWSER || g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_BOWSERJR) && g_Pitcher.bulletPitchStageCode == 1) {
            g_Ball.AtBat_Contact_BallPos.x += g_Pitcher.starPitchPositionAdjustment.x;
            g_Ball.AtBat_Contact_BallPos.y += g_Pitcher.starPitchPositionAdjustment.y;
            g_Ball.AtBat_Contact_BallPos.z += g_Pitcher.starPitchPositionAdjustment.z;
        }
        if (g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_WARIO) {
            d = lbl_3_data_5EB8[1] - g_Ball.AtBat_Contact_BallPos.z;
            if (d >= 0.0f) {
                d = d / lbl_3_data_5EB8[1];
                g_Pitcher.starPitchPositionAdjustment.x = lbl_3_data_5EB8[0] * d;
                if (g_Pitcher.warioWaluStarPitchRightLeft != 0) {
                    g_Pitcher.starPitchPositionAdjustment.x = -g_Pitcher.starPitchPositionAdjustment.x;
                }
                g_Ball.AtBat_Contact_BallPos.x += g_Pitcher.starPitchPositionAdjustment.x;
                if (g_Pitcher.warioWaluStarHasPlayedSound == 0) {
                    playSoundEffect(0x1B2);
                }
                g_Pitcher.warioWaluStarAnimationStage = 1;
                if (g_Ball.AtBat_Contact_BallPos.z < lbl_3_data_5EB8[2]) {
                    g_Pitcher.warioWaluStarAnimationStage = 2;
                }
                g_Pitcher.warioWaluStarHasPlayedSound = g_Pitcher.warioWaluStarHasPlayedSound + 1;
            }
        } else if (g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_WALUIGI) {
            d = lbl_3_data_5EC4[1] - g_Ball.AtBat_Contact_BallPos.z;
            if (d >= 0.0f) {
                d = d / lbl_3_data_5EC4[1];
                amp = lbl_3_data_5EC4[0] * d;
                if (d > 1.0f) {
                    d = 1.0f;
                }
                sinVal = SINF(4.712389f * d);
                g_Pitcher.starPitchPositionAdjustment.x = 2.0f * amp * -sinVal + -amp;
                if (g_Pitcher.warioWaluStarPitchRightLeft != 0) {
                    g_Pitcher.starPitchPositionAdjustment.x = -g_Pitcher.starPitchPositionAdjustment.x;
                }
                g_Ball.AtBat_Contact_BallPos.x += g_Pitcher.starPitchPositionAdjustment.x;
                if (g_Pitcher.warioWaluStarHasPlayedSound == 0) {
                    playSoundEffect(0x1B2);
                }
                g_Pitcher.warioWaluStarAnimationStage = 1;
                if (g_Ball.AtBat_Contact_BallPos.z < lbl_3_data_5EC4[2]) {
                    g_Pitcher.warioWaluStarAnimationStage = 2;
                }
                g_Pitcher.warioWaluStarHasPlayedSound = g_Pitcher.warioWaluStarHasPlayedSound + 1;
            }
        }
        if (g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_PEACH || g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_DAISY) {
            idx = g_Pitcher.starPitchType - CAPTAIN_STAR_TYPE_PEACH;
            prop = (f32)g_Ball.pitchHangtimeCounter / (f32)g_Pitcher.frameWhenUnhittable;
            if (prop >= pitchSpeedScaler[8 + idx] && prop <= pitchSpeedScaler[10 + idx]) {
                g_Pitcher.peachDaisyAnimationHappened = 1;
                g_Pitcher.peachDaisyStarAnimationOn = g_Pitcher.peachDaisyStarAnimationOn + 1;
            } else {
                g_Pitcher.peachDaisyStarAnimationOn = 0;
            }
        }
        ground = g_Ball.groundYForBounces;
        if (g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_YOSHI || g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_BIRDO) {
            ground = eggConstants[0];
        }
        if (g_Ball.AtBat_Contact_BallPos.y < ground) {
            if ((g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_YOSHI || g_Pitcher.starPitchType == CAPTAIN_STAR_TYPE_BIRDO) &&
                (g_Pitcher.eggBallBounceNumber == 0 || g_Pitcher.eggBallBounceNumber == 1)) {
                fn_3_70838();
            } else {
                g_Pitcher.eggBallBounceNumber = g_Pitcher.eggBallBounceNumber + 1;
                g_Pitcher.cancelParabolicAdjustmentInd = 1;
                g_Ball.AtBat_Contact_BallPos.y = ground;
                g_Pitcher.ballCurrentPosition.y = ground;
                g_Pitcher.ballVelocity.y = -(g_Ball.AtBat_Contact_BallPos.y - g_Ball.pastCoordinates[0].y);
                g_Pitcher.ballVelocity.y = g_Pitcher.ballVelocity.y * lbl_3_data_5ED0[1];
                d = dolsqrtf2(g_Pitcher.ballVelocity.x * g_Pitcher.ballVelocity.x +
                              g_Pitcher.ballVelocity.z * g_Pitcher.ballVelocity.z);
                if (d < 0.01f) {
                    d = 0.01f;
                }
                g_Pitcher.ballVelocity.x = 0.15f * (g_Pitcher.ballVelocity.x / d);
                g_Pitcher.ballVelocity.z = 0.15f * (g_Pitcher.ballVelocity.z / d);
                g_Pitcher.pitchCurveVeloV1 = 0.0f;
                g_Pitcher._60 = 0.0f;
                playSoundEffect(0x17E);
            }
        }
        g_Pitcher.framesUntilBallReachesBatterZ =
            estimateXAndFrameAtBatterZ(&g_Pitcher.pitchXPosition, g_Batter.batPosition.z, 0);
        estimateXAndFrameAtBatterZ(&g_Pitcher.pitchXPosition2, g_Batter.batPosition.z, 1);
        if (g_Pitcher.framesUntilPitchGetsToBatter < 0) {
            g_Pitcher.framesUntilPitchGetsToBatter = g_Pitcher.framesUntilBallReachesBatterZ + g_Ball.pitchHangtimeCounter;
        }
        fn_3_70280();
        if (g_Pitcher.strikeZoneProcessNumber == 0 && g_Ball.AtBat_Contact_BallPos.z < g_Pitcher.beginningOfStrikeCheckZ) {
            fn_3_706B8(0);
            g_Pitcher.strikeZoneProcessNumber = 1;
        }
        if (g_Pitcher.strikeZoneProcessNumber <= 1 && g_Ball.AtBat_Contact_BallPos.z < g_Pitcher.endingOfStrikeCheckZ) {
            if (g_Pitcher.calledStrikeInd == 0) {
                fn_3_706B8(1);
            }
            g_Pitcher.strikeZoneProcessNumber = 2;
        }
        if (g_Ball.AtBat_Contact_BallPos.z >= g_Pitcher.centerOfStrikeZone.z) {
            g_Pitcher.framesUntilUnhittable = g_Pitcher.frameWhenUnhittable - g_Ball.pitchHangtimeCounter;
        }
        if (g_Ball.AtBat_Contact_BallPos.z < -3.0f) {
            g_Pitcher.pitcherActionState = PITCHER_ACTION_STATE_NO_CONTACT;
            g_Pitcher.currentStateFrameCounter = 0;
            g_Pitcher.pitchDidntResultInLiveBallInd = 1;
            if (g_Pitcher.pitchSpeed >= 0x91) {
                playSoundEffect(0x16B);
            } else {
                playSoundEffect(0x16A);
            }
        }
        g_Pitcher.pitchLinearInterpolateY =
            g_Pitcher.pitchRelease.x + ((g_Pitcher.ballCurrentPosition.y - g_Pitcher.pitchRelease.y) *
                                        (g_Pitcher.frontOfPlateZ - g_Pitcher.pitchRelease.z)) /
                                           (g_Pitcher.ballCurrentPosition.z - g_Pitcher.pitchRelease.z);
        g_Pitcher.frontOfPlateZ2 = g_Pitcher.frontOfPlateZ;
        g_Pitcher.pitchLinearInterpolateX =
            g_Pitcher.pitchRelease.x + ((g_Pitcher.ballCurrentPosition.x - g_Pitcher.pitchRelease.x) *
                                        (g_Pitcher.frontOfPlateZ - g_Pitcher.pitchRelease.z)) /
                                           (g_Pitcher.ballCurrentPosition.z - g_Pitcher.pitchRelease.z);
        if (g_Batter.hitByPitch != 0) {
            fn_3_6FFC4();
            g_Pitcher.pitcherActionState = PITCHER_ACTION_STATE_HIT_BY_PITCH;
            g_Pitcher.currentStateFrameCounter = 0;
            g_Pitcher.pitchDidntResultInLiveBallInd = 1;
        }
    }
    probe.src.x = g_Ball.AtBat_Contact_BallPos.x;
    probe.src.y = -g_Ball.AtBat_Contact_BallPos.y;
    probe.src.z = g_Ball.AtBat_Contact_BallPos.z;
    probe.dst.x = g_Ball.AtBat_Contact_BallPos.x;
    probe.dst.y = 10.0f;
    probe.dst.z = g_Ball.AtBat_Contact_BallPos.z;
    collType = checkCollision(&probe, &hit, 0, FALSE);
    g_Ball.maybeCollisionRelated = g_Ball.collisionCode;
    g_Ball.physicsSubstruct.twoFrameLookback[1] = -hit.position.y;
    if (collType != BALL_COLLISION_TYPE_NONE) {
        g_Ball.collisionCode = collType;
    }
}

// .text:0x00070EF4 size:0x354 mapped:0x806AFF88
void pitchCurve(void) {
    f32 curve;
    f32 frames;
    s16* pc;
    InputStruct* controls;
    int dir = 0;
    controls = &g_Controls[g_GameLogic.teams[g_GameLogic.teamFielding]];
    pc = pitchConstantsArray[g_Pitcher.specialPitchTypeCode];
    g_Pitcher.pitchCurveVeloV1 = 0.0f;
    g_Pitcher._60 = 0.0f;
    if (g_Pitcher.cancelParabolicAdjustmentInd == 0 && g_Pitcher.calced_curve != 0) {
        curve = LinearInterpolateToNewRange((f32)g_Pitcher.calced_curve, 1.0f, 100.0f,
                                            (f32)pc[1],
                                            (f32)pc[2]);
        curve = 0.00005f * curve;
        if (g_Pitcher.AIInd != 0) {
            dir = aiPitchCurveDirection(curve);
        } else {
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_Practice.instructionNumber >= 0) {
                controls = &g_Practice.inputs[g_GameLogic.teamFielding];
            } else if (AI_getPort(g_Minigame.minigameControlStruct[0].characterIndex[MINIGAME_SELECTED_ORDER]) !=
                       0) {
                controls = &g_Minigame._1D7C[g_Minigame.minigameControlStruct[0].characterIndex[MINIGAME_SELECTED_ORDER]];
            } else if (g_d_GameSettings.minigamesEnabled) {
                controls = &g_Controls[g_Minigame.minigameControlStruct[0].characterIndex[MINIGAME_SELECTED_ORDER]];
            }
            if (controls->buttonInput & INPUT_BUTTON_LEFT) {
                dir = -1;
            } else if (controls->buttonInput & INPUT_BUTTON_RIGHT) {
                dir = 1;
            }
        }
        frames = LinearInterpolateToNewRange((f32)g_Pitcher.calced_curveControl, 1.0f, 100.0f,
                                             curveControlFrames_CursedBallMult[0], curveControlFrames_CursedBallMult[1]);
        if (frames < 1.0f) {
            frames = 1.0f;
        }
        if (dir == 0) {
            f32 step = curve / frames;
            if (g_Pitcher.pitchCurveVeloV2 < 0.0f) {
                g_Pitcher.pitchCurveVeloV2 += step;
                if (g_Pitcher.pitchCurveVeloV2 > 0.0f) {
                    g_Pitcher.pitchCurveVeloV2 = 0.0f;
                }
            } else {
                g_Pitcher.pitchCurveVeloV2 -= step;
                if (g_Pitcher.pitchCurveVeloV2 < 0.0f) {
                    g_Pitcher.pitchCurveVeloV2 = 0.0f;
                }
            }
        } else {
            g_Pitcher.pitchCurveVeloV2 += curve * (f32)dir / frames;
            if (dir < 0) {
                if (g_Pitcher.pitchCurveVeloV2 < -curve) {
                    g_Pitcher.pitchCurveVeloV2 = -curve;
                }
            } else if (g_Pitcher.pitchCurveVeloV2 > curve) {
                g_Pitcher.pitchCurveVeloV2 = curve;
            }
        }
        g_Pitcher.pitchCurveVeloV1 = g_Pitcher.pitchCurveVeloV2;
        if (dir != 0) {
            g_Pitcher.anyCurveInput = 1;
        }
    }
}

// .text:0x00070B94 size:0x360 mapped:0x806AFC28
void fn_3_70B94(void) {
    updatePitchYParabola();
}

// .text:0x00070AEC size:0xA8 mapped:0x806AFB80
void fn_3_70AEC(void) {
    if (g_Pitcher.cancelParabolicAdjustmentInd != 0) {
        g_Pitcher.pitchX_parabolicAdjustment = 0.0f;
    } else {
        f32 t = g_Ball.pitchHangtimeCounter - g_Pitcher.frameWhenUnhittable / 2.0f;
        g_Pitcher.pitchX_parabolicAdjustment =
            g_Pitcher.horizontalOffsetParabolaMidpoint - t * (g_Pitcher.horizontalGlobalParabolicVelo * t) / 10000.0f;
    }
}

// .text:0x000709B4 size:0x138 mapped:0x806AFA48
void fn_3_709B4(void) {
    f32 sinA;
    f32 cosA;
    f32 angle;
    f32 k;
    g_Pitcher.bulletPitchFrameCounter++;
    if (g_Pitcher.bulletPitchFrameCounter >= g_Pitcher.bulletPitchLoopFrames) {
        g_Pitcher.bulletPitchStageCode = 2;
    } else {
        angle = (f32)g_Pitcher.bulletPitchFrameCounter / (f32)g_Pitcher.bulletPitchLoopFrames;
        angle *= 6.2831855f;
        angle += 3.1415927f;
        getComponentsFromRad(angle, &sinA, &cosA);
        k = 0.01f * (f32)bulletBallConstants[g_Pitcher.starPitchType * 5 - 0x1F];
        g_Pitcher.starPitchPositionAdjustment.y = sinA * k + k;
        g_Pitcher.starPitchPositionAdjustment.z = cosA * k;
        g_Pitcher.starPitchPositionAdjustment.x = 0.0f;
        g_Pitcher.bulletPitchLoopAngleRadians = angle;
    }
}

// .text:0x00070838 size:0x17C mapped:0x806AF8CC
void fn_3_70838(void) {
    f32 dz;
    f32 dy;
    f32 dx;
    if (g_Pitcher.eggBallBounceNumber == 0) {
        g_Pitcher.pitchStartingPosition_AIMaxCurve = RandomF32_Game_Range(-eggConstants[6], eggConstants[6]);
        g_Pitcher.eggBallBounceYHeight = eggConstants[0];
        g_Pitcher.eggBallBounceZLoc = RandomF32_Game_Range(eggConstants[4], eggConstants[5]);
        g_Pitcher.frontOfPlateZ = 0.5f * (g_Pitcher.eggBallBounceZLoc + g_Pitcher.frontOfPlateZ);
    } else {
        g_Pitcher.pitchStartingPosition_AIMaxCurve = RandomF32_Game_Range(-eggConstants[7], eggConstants[7]);
        g_Pitcher.eggBallBounceYHeight = eggConstants[0];
        g_Pitcher.frontOfPlateZ = g_Pitcher.centerOfStrikeZone.z;
    }
    g_Pitcher.pitchSpeed = RandomInt_Game_Range(lbl_3_data_5F7C[4], lbl_3_data_5F7C[5]);
    g_Pitcher.eggBallBounceNumber++;
    dx = g_Pitcher.pitchStartingPosition_AIMaxCurve - g_Pitcher.ballCurrentPosition.x;
    dy = g_Pitcher.eggBallBounceYHeight - g_Pitcher.ballCurrentPosition.y;
    dz = g_Pitcher.ballCurrentPosition.z - g_Pitcher.frontOfPlateZ;
    g_Pitcher.ballVelocity.z = -((f32)g_Pitcher.pitchSpeed / g_Pitcher.pitchSpeedScaler);
    g_Pitcher.framesSinceFirstEggBounce = 0;
    g_Pitcher.ballVelocity.x = -(dx * g_Pitcher.ballVelocity.z / dz);
    g_Pitcher.ballVelocity.y = -(dy * g_Pitcher.ballVelocity.z / dz);
}

// .text:0x00070768 size:0xD0 mapped:0x806AF7FC
int estimateXAndFrameAtBatterZ(f32* outX, f32 z, int flag) {
    int frames = 0;
    f32 posZ = g_Pitcher.ballCurrentPosition.z;
    f32 posX = g_Pitcher.ballCurrentPosition.x;
    f32 velX = g_Pitcher.ballVelocity.x;
    f32 velY = g_Pitcher.ballVelocity.y;
    f32 velZ = g_Pitcher.ballVelocity.z;
    f32 curve = g_Pitcher.pitchCurveVeloV1;
    f32 prevX;
    f32 prevZ;
    f32 newVelZ;
    f32 frac;
    if (posZ < z) {
        return 0;
    }
    for (;;) {
        prevX = posX;
        prevZ = posZ;
        frames++;
        if (prevZ <= g_Pitcher.pitchZ_whenAirResistanceStarts) {
            newVelZ = velZ - velZ * g_Pitcher.airResistance_veloAdj;
            if (newVelZ < -0.05f) {
                velX = velX - velX * g_Pitcher.airResistance_veloAdj;
                velY = velY - velY * g_Pitcher.airResistance_veloAdj;
                velZ = newVelZ;
            }
        }
        velX = velX * g_Pitcher.decelerationFactor;
        velY = velY * g_Pitcher.decelerationFactor;
        velZ = velZ * g_Pitcher.decelerationFactor;
        posX = prevX + velX;
        posZ = prevZ + velZ;
        if (flag != 0) {
            posX = posX + curve;
        }
        if (posZ < z) {
            break;
        }
    }
    frac = 1.0f - (posZ - z) / (posZ - prevZ);
    frac = (posX - prevX) * frac;
    *outX = prevX + frac;
    return frames;
}

// .text:0x000706B8 size:0xB0 mapped:0x806AF74C
void fn_3_706B8(int idx) {
    f32 t;
    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_WALLBALL) {
        return;
    }
    t = ((&g_Pitcher.beginningOfStrikeCheckZ)[idx] - g_Pitcher.ballCurrentPosition.z) /
        (g_Pitcher.ballLastPosition.z - g_Pitcher.ballCurrentPosition.z);
    g_Pitcher.estimatedEndingPos.x =
        t * (g_Pitcher.ballLastPosition.x - g_Pitcher.ballCurrentPosition.x) + g_Pitcher.ballCurrentPosition.x;
    g_Pitcher.estimatedEndingPos.z =
        t * (g_Pitcher.ballLastPosition.y - g_Pitcher.ballCurrentPosition.y) + g_Pitcher.ballCurrentPosition.y;
    if (fn_3_70680(g_Pitcher.estimatedEndingPos.x)) {
        g_Pitcher.calledStrikeInd = 1;
        g_Pitcher.strikeInd = 1;
    }
}

// .text:0x00070680 size:0x38 mapped:0x806AF714
BOOL fn_3_70680(f32 x) {
    if (x >= g_Pitcher.strikeZoneLeft && x <= g_Pitcher.strikeZoneRight) {
        return 1;
    }
    return 0;
}

// .text:0x000703EC size:0x294 mapped:0x806AF480
void pitchCall(void) {
    if (g_Batter.framesSinceStartOfSwing > 0 && g_Batter.framesSinceStartOfSwing < swingSoundFrame[0][1] && g_Batter._95 == 0) {
        return;
    }
    g_Pitcher.miniGameRelated = 1;
    if (g_Pitcher.strikeInd) {
        g_Strikes.strikes++;
        if (g_Strikes.strikes >= 3) {
            g_Pitcher.strikeOutOrWalk = 1;
            g_Pitcher.framesSinceAtBatEnded = 0;
            g_Pitcher.pitcherActionState = PITCHER_ACTION_STATE_HIT;
            g_Pitcher.currentStateFrameCounter = 0;
            QueueTextToDisplay(0x10, 0);
            if (g_GameLogic.IsStarChance == 1) {
                if ((g_Scores.Inning < g_Scores.inningLimit || g_Scores.halfInning == 0 || g_Strikes.outs < 2 ||
                     g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total <=
                         g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total) &&
                    (g_Scores.Inning < g_Scores.maxNumberOfExtraInnings || g_Scores.halfInning == 0 || g_Strikes.outs < 2) &&
                    g_GameLogic.TeamStars[g_GameLogic.teamFielding] < 5) {
                    g_GameLogic.TeamStars[g_GameLogic.teamFielding]++;
                    if (g_Stats.replayInd == 0) {
                        playSoundEffect(0x19D);
                    }
                }
                g_GameLogic.IsStarChance = 2;
            }
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                g_Minigame._19C6 = MINIGAME_SELECTED_ORDER;
            }
        } else {
            QueueTextToDisplay(8, 0);
        }
    } else {
        g_Strikes.balls++;
        if (g_Strikes.balls >= 4) {
            g_Pitcher.strikeOutOrWalk = 2;
            g_Pitcher.framesSinceAtBatEnded = 0;
            g_Pitcher.pitcherActionState = PITCHER_ACTION_STATE_HIT;
            g_Pitcher.currentStateFrameCounter = 0;
            QueueTextToDisplay(0xA, 0);
            if (g_GameLogic.IsStarChance == 1) {
                if (g_GameLogic.TeamStars[g_GameLogic.teamBatting] < 5) {
                    g_GameLogic.TeamStars[g_GameLogic.teamBatting]++;
                    if (g_Stats.replayInd == 0) {
                        playSoundEffect(0x19D);
                    }
                }
                g_GameLogic.IsStarChance = 3;
            }
        } else {
            QueueTextToDisplay(9, 0);
        }
    }
    postPitchStatUpdating(0);
    trackLastPitchInfo();
}

// .text:0x00070280 size:0x16C mapped:0x806AF314
void fn_3_70280(void) {
    BOOL hit = 0;
    int idx;
    int dx;
    int dz;
    if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_PITCHING && g_Practice._1DB == 0) {
        return;
    }
    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_WALLBALL) {
        return;
    }
    if (g_Batter.framesSinceStartOfSwing > 0) {
        return;
    }
    if (g_Pitcher.calledStrikeInd != 0) {
        return;
    }
    dx = (int)(100.0f * (g_Pitcher.ballCurrentPosition.x - g_Batter.batterPos.x));
    dz = (int)(100.0f * (g_Pitcher.ballCurrentPosition.z - g_Batter.batterPos.z));
    if (g_Batter.batterHand != BATTING_HAND_RIGHT) {
        dx = -dx;
    }
    idx = characterStaticIndexes[g_Batter.charID * 6 + 2] * 3;
    if (dz <= hitByPitchHitboxes[idx] && (f32)dz >= 0.0f && dx <= hitByPitchHitboxes[idx + 1] &&
        dx >= -hitByPitchHitboxes[idx + 2]) {
        hit = 1;
    }
    if (hit) {
        g_Batter.hitByPitch = 1;
    }
}

// .text:0x0006FFC4 size:0x2BC mapped:0x806AF058
void fn_3_6FFC4(void) {
    fn_3_6FDA0();
    g_Pitcher.strikeOutOrWalk = 3;
    g_Pitcher.miniGameRelated = 1;
    g_Pitcher.framesSinceAtBatEnded = 0;
    playSoundEffect(0x170);
    if (g_Batter.aiControlledInd == 0) {
        if (g_d_GameSettings.minigamesEnabled) {
            setCharacterAnimations(g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.rosterID], 2);
        } else {
            setCharacterAnimations(g_GameLogic.teamBatting, 2);
        }
    }
    postPitchStatUpdating(0);
}

// .text:0x0006FDA0 size:0x224 mapped:0x806AEE34
void fn_3_6FDA0(void) {
    f32 dirX;
    f32 dirZ;
    f32 speed;
    f32 scale;
    int jitter;
    int angle;
    jitter = g_Ball.StaticRandomInt1 % 0x101 - 0x80;
    angle = calculateAngleFromCoordinates(g_Pitcher.ballVelocity.x, -g_Pitcher.ballVelocity.z);
    getComponentsFromSAng(angle + jitter, &dirX, &dirZ);
    scale = 0.01f * (f32)(g_Ball.StaticRandomInt2 % 10);
    speed = dolsqrtf2(g_Pitcher.ballVelocity.x * g_Pitcher.ballVelocity.x +
                      g_Pitcher.ballVelocity.z * g_Pitcher.ballVelocity.z);
    g_Ball.physicsSubstruct.velocity.x = (0.1f + scale) * (dirX * speed);
    g_Ball.physicsSubstruct.velocity.z = (0.1f + scale) * (dirZ * speed);
    g_Ball.physicsSubstruct.velocity.y = 0.0f;
}

// .text:0x0006FB98 size:0x208 mapped:0x806AEC2C
void fn_3_6FB98(void) {
    fn_3_6FA28();
    if (g_Pitcher.currentStateFrameCounter == 10) {
        QueueTextToDisplay(0xB, 0);
        g_Pitcher.pitcherActionState = PITCHER_ACTION_STATE_HIT;
        g_Pitcher.currentStateFrameCounter = 0;
        if (g_GameLogic.IsStarChance == 1) {
            if (g_GameLogic.TeamStars[g_GameLogic.teamBatting] < 5) {
                g_GameLogic.TeamStars[g_GameLogic.teamBatting]++;
                if (g_Stats.replayInd == 0) {
                    playSoundEffect(0x19D);
                }
            }
            g_GameLogic.IsStarChance = 3;
        }
    }
}

// .text:0x0006FA28 size:0x170 mapped:0x806AEABC
void fn_3_6FA28(void) {
    int stadium;
    if (g_Ball.pitchHangtimeCounter < 0x7FFE) {
        g_Ball.pitchHangtimeCounter++;
    } else {
        g_Ball.pitchHangtimeCounter = 0x7FFF;
    }
    if (g_Pitcher.pitchTotalTimeCounter < 0x7FFE) {
        g_Pitcher.pitchTotalTimeCounter++;
    } else {
        g_Pitcher.pitchTotalTimeCounter = 0x7FFF;
    }
    g_Ball.pastCoordinates[0].x = g_Ball.AtBat_Contact_BallPos.x;
    g_Ball.pastCoordinates[0].y = g_Ball.AtBat_Contact_BallPos.y;
    g_Ball.pastCoordinates[0].z = g_Ball.AtBat_Contact_BallPos.z;
    g_Ball.physicsSubstruct.velocity.y -= g_Ball.physicsSubstruct.gravity;
    adjustVeloByAirResistance();
    g_Ball.AtBat_Contact_BallPos.x += g_Ball.physicsSubstruct.velocity.x;
    g_Ball.AtBat_Contact_BallPos.y += g_Ball.physicsSubstruct.velocity.y;
    g_Ball.AtBat_Contact_BallPos.z += g_Ball.physicsSubstruct.velocity.z;
    if (g_Ball.AtBat_Contact_BallPos.y < g_Ball.groundYForBounces) {
        stadium = g_d_GameSettings.StadiumID;
        g_Ball.physicsSubstruct.velocity.y =
            g_Ball.physicsSubstruct.velocity.y *
            (ballBounceConstants[stadium].yOtherBouncesSpeedKept - g_Ball.physicsSubstruct.velocity.y / 2.0f);
        g_Ball.physicsSubstruct.velocity.y = -g_Ball.physicsSubstruct.velocity.y;
        if (g_Ball.physicsSubstruct.velocity.y < 0.01f) {
            g_Ball.physicsSubstruct.velocity.x *= ballBounceConstants[stadium].rollingSpeedKept;
            g_Ball.physicsSubstruct.velocity.z *= ballBounceConstants[stadium].rollingSpeedKept;
        } else {
            g_Ball.physicsSubstruct.velocity.x *= ballBounceConstants[stadium].xOtherBouncesSpeedKept;
            g_Ball.physicsSubstruct.velocity.z *= ballBounceConstants[stadium].xOtherBouncesSpeedKept;
        }
        g_Ball.AtBat_Contact_BallPos.y = g_Ball.groundYForBounces;
    }
}

// .text:0x0006F748 size:0x2E0 mapped:0x806AE7DC
BOOL waitingForPitch_checkForPickoffs(void) {
    InputStruct* controls = &g_Controls[g_GameLogic.teams[g_GameLogic.teamFielding]];
    do {
        if (g_Pitcher.AIInd != 0) {
            if (aIPickoff() == 0) {
                return 0;
            }
        } else {
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_Practice.instructionNumber >= 0) {
                controls = &g_Practice.inputs[g_GameLogic.teamFielding];
            } else if (AI_getPort(g_Minigame.minigameControlStruct[0].characterIndex[MINIGAME_SELECTED_ORDER]) !=
                       0) {
                controls = &g_Minigame._1D7C[g_Minigame.minigameControlStruct[0].characterIndex[MINIGAME_SELECTED_ORDER]];
            } else if (g_d_GameSettings.minigamesEnabled && MINIGAME_SELECTED_ORDER >= 0) {
                controls = &g_Controls[g_Minigame.minigameControlStruct[0].characterIndex[MINIGAME_SELECTED_ORDER]];
            }
            if (g_GameLogic.FrameCountOfCurrentPitch < 90) {
                return 0;
            }
            if (g_RunningLogic._10 <= 1) {
                return 0;
            }
            if (fn_3_6F6CC()) {
                if (g_Pitcher.nPickoffAttempts < 0xFE) {
                    g_Pitcher.nPickoffAttempts++;
                } else {
                    g_Pitcher.nPickoffAttempts = 0xFF;
                }
                return 1;
            }
            if (!(controls->newButtonInput & INPUT_BUTTON_B)) {
                break;
            }
            g_Pitcher.pickOffLoc = 4;
            if (controls->buttonInput & INPUT_BUTTON_LEFT) {
                if (g_Runners[3].runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE) {
                    g_Pitcher.pickOffLoc = 3;
                }
            } else if (controls->buttonInput & INPUT_BUTTON_UP) {
                if (g_Runners[2].runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE) {
                    g_Pitcher.pickOffLoc = 2;
                }
            } else if (controls->buttonInput & INPUT_BUTTON_RIGHT) {
                if (g_Runners[1].runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE) {
                    g_Pitcher.pickOffLoc = 1;
                }
            }
        }
        transitionToLiveBallWithoutContact(0);
        if (g_Pitcher.nPickoffAttempts < 0xFE) {
            g_Pitcher.nPickoffAttempts++;
        } else {
            g_Pitcher.nPickoffAttempts = 0xFF;
        }
        return 1;
    } while (0);
    return 0;
}

// .text:0x0006F6CC size:0x7C mapped:0x806AE760
BOOL fn_3_6F6CC(void) {
    int i;
    for (i = 1; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
            g_Runners[i].percentTowardsNextBase > 0.5f) {
            g_Pitcher.pickOffLoc = 4;
            transitionToLiveBallWithoutContact(0);
            return 1;
        }
    }
    return 0;
}
