#include "game/ball/ball_physics.h"
#include "game/baserunning/runner.h"
#include "game/fielding/fielder.h"
#include "game/UnknownHomes_Game.h"
#include "game/math/game_math.h"
#include "Dolphin/rand.h"
#include "static/UnknownHomes_static.h"
#include "game/stadium/sta_c6.h"
#include "header_rep_data.h"
#include "game/ball/foul_detection.h"
#include "game/sound/m_sound.h"
#include "game/stadium/stadium_framework.h"

extern void QueueTextToDisplay(int code, int arg1);
extern void CrossProduct(VecXYZ* out, VecXYZ* a, VecXYZ* b);
extern void fn_3_15F648(int kind, u8 animByte, VecXYZ* pos, VecXYZ* vel);
extern void handleBallRollInWater(VecXYZ* pos, VecXYZ* vel);
extern void processBallFielderCollision(u8 fielderIndex);
extern void starMissionsQuantityBased(int missionType, int rosterLocation);
extern s16 lbl_3_common_bss_37400[0x27];
extern u8 animRelated[0x124];
extern f32 lbl_3_data_610C[6];
extern f32 lbl_3_data_6124[3];
extern const f32 lbl_3_rodata_590;
extern const f32 lbl_3_rodata_5B0;
extern const f32 lbl_3_rodata_5D4;
extern const f32 lbl_3_rodata_5E4;
extern const f32 lbl_3_rodata_5E8;
extern const f32 lbl_3_rodata_5DC;
extern const f32 lbl_3_rodata_60C;
extern const f32 lbl_3_rodata_610;
extern const f32 lbl_3_rodata_594;
extern const f32 reallyLargeConst;
extern f32 lbl_3_data_45F4[2];
extern f32 lbl_3_data_45FC;
extern u8 lbl_3_data_4600;
extern u32 FrameCountOfEntireGame;
extern VecXZ fieldingStartingCoords_regular[9];
extern VecXZ base_MoundCoordinates[5];
extern f32 lbl_3_data_5CDC[11];
extern f32 fielderHitboxesForGarlicKnockout[5];
extern void makeSoundOfBallBouncing(void);
typedef struct {
    f32 y1stBounceSpeedKept;
    f32 yOtherBouncesSpeedKept;
    f32 x1stBounceSpeedKept;
    f32 xOtherBouncesSpeedKept;
    f32 rollingSpeedKept;
} BallBounceConstants;
extern BallBounceConstants ballBounceConstants[7];
extern BallBounceConstants lbl_3_data_4414;
extern f32 lbl_3_data_4604;
extern u8 lbl_3_data_4608;
extern u8 characterStaticIndexes[0x144];
extern f32 lbl_3_data_4428[7];
extern f32 fielderActionConstants[43];
extern struct {
    f32 _00;
    f32 _04;
    f32 _08;
} lbl_3_data_21438;
extern int peachDaisyStarSwingRelated(void);
extern void peachDaisyStarSwingRelated2(void);

// .text:0x00006530 size:0x78 mapped:0x806455C4
void chompCollision_processStarHitVariables(void) {
    g_Ball.someCollisionInd = 1;
    if (g_Ball.ballState == BALL_STATE_THROWN) {
        g_Ball.ballState = BALL_STATE_HELD;
    }
    g_Ball.currentStarSwing = 0;
    g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy = 0;
    g_Ball.someCollisionInd = 1;
    g_Ball.warioWaluGarlicIsActive = 0;
    g_Ball.autoFielderAvoidDropSpotForPeachesStarHit = 0;
    g_Ball.physicsSubstruct.acceleration.x = 0.0f;
    g_Ball.physicsSubstruct.acceleration.y = 0.0f;
    g_Ball.physicsSubstruct.acceleration.z = 0.0f;
    processFielderAutoCatch();
}

// .text:0x000065A8 size:0x20 mapped:0x8064563C
void ballState_thrown_to_holding(void) {
    if (g_Ball.ballState == BALL_STATE_THROWN) {
        g_Ball.ballState = BALL_STATE_HELD;
    }
}

// .text:0x000065C8 size:0x2C mapped:0x8064565C
void fn_3_65C8(void) {
    if (g_Ball.matchFramesAndBallAngle.framesInsidePlant < 0x7FFE) {
        g_Ball.matchFramesAndBallAngle.framesInsidePlant++;
    } else {
        g_Ball.matchFramesAndBallAngle.framesInsidePlant = 0x7FFF;
    }
}

// .text:0x000065F4 size:0x2C mapped:0x80645688
void setBallInactiveVariables(void) {
    g_Ball.pauseBallMovementWhenInPlant = 0;
    g_FieldingLogic.knockoutFinished = 1;
    g_Ball.frameCountdownAfterLeavingPlant = 3;
}

// .text:0x00006620 size:0x74 mapped:0x806456B4
void setValsForPlantCatches(void) {
    if (g_Ball.pauseBallMovementWhenInPlant == 0) {
        g_Ball.pauseBallMovementWhenInPlant = 1;
        g_Ball.ballCughtByPlantInd = 1;
        g_Ball.matchFramesAndBallAngle.framesInsidePlant = 0;
        g_Ball.someCollisionVariable = 0;
        g_Ball.currentStarSwing = 0;
        g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy = 0;
        g_Ball.someCollisionInd = 1;
        g_Ball.warioWaluGarlicIsActive = 0;
        g_Ball.autoFielderAvoidDropSpotForPeachesStarHit = 0;
        g_Ball.physicsSubstruct.acceleration.x = lbl_3_rodata_590;
        g_Ball.physicsSubstruct.acceleration.y = lbl_3_rodata_590;
        g_Ball.physicsSubstruct.acceleration.z = lbl_3_rodata_590;
        processFielderAutoCatch();
    }
}

// .text:0x00006694 size:0x5A4 mapped:0x80645728
void checkForBallDead(void) {
    int collType = g_Ball.collisionCode & 0x7F;
    BOOL isFoul = g_Ball.collisionCode & BALL_COLLISION_TYPE_FOUL;

    if (foul_checkIfFoul(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z) != 0) {
        isFoul = TRUE;
    }

    if (collType == BALL_COLLISION_TYPE_STRUCTURE && g_Ball.deadBallReason == 0) {
        switch (g_Ball.AtBat_ContactResult) {
            case BALL_RESULT_TYPE_FOUL:
                if (g_Ball.deadBallReason == 0) {
                    BOOL runnerWasOut;

                    g_Ball.deadBallReason = 2;
                    g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                    g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                    g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                    g_Ball.AtBat_ContactResult = BALL_RESULT_TYPE_FOUL;
                    g_Ball.ballInitialHitDoneInd = 1;
                    runnerWasOut = FALSE;
                    if (g_FieldingLogic.hasProcessedFoulBall != 1) {
                        g_FieldingLogic.hasProcessedFoulBall = 1;
                        g_Strikes.strikes++;
                        if (g_Strikes.strikes >= 3) {
                            if (g_Ball.maybeBuntInd != 0) {
                                g_Ball.maybebuntOn2Strikes = 1;
                                runnerOut(0);
                                runnerWasOut = TRUE;
                            } else {
                                g_Strikes.strikes = 2;
                            }
                        }
                        if (runnerWasOut == 0) {
                            QueueTextToDisplay(3, 0);
                        }
                    }
                }
                break;
            case BALL_RESULT_TYPE_IN_AIR:
                if (g_Ball.matchFramesAndBallAngle.ballOverWallFrames >= 5) {
                    if (isFoul != 0) {
                        if (g_Ball.deadBallReason == 0) {
                            BOOL runnerWasOut;

                            g_Ball.deadBallReason = 2;
                            g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                            g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                            g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                            g_Ball.AtBat_ContactResult = BALL_RESULT_TYPE_FOUL;
                            g_Ball.ballInitialHitDoneInd = 1;
                            runnerWasOut = FALSE;
                            if (g_FieldingLogic.hasProcessedFoulBall != 1) {
                                g_FieldingLogic.hasProcessedFoulBall = 1;
                                g_Strikes.strikes++;
                                if (g_Strikes.strikes >= 3) {
                                    if (g_Ball.maybeBuntInd != 0) {
                                        g_Ball.maybebuntOn2Strikes = 1;
                                        runnerOut(0);
                                        runnerWasOut = TRUE;
                                    } else {
                                        g_Strikes.strikes = 2;
                                    }
                                }
                                if (runnerWasOut == 0) {
                                    QueueTextToDisplay(3, 0);
                                }
                            }
                        }
                    } else {
                        if (g_Ball.deadBallReason == 0) {
                            g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                            g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                            g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                            g_Ball.deadBallReason = 1;
                            g_Ball.matchFramesAndBallAngle.ballOverWallFrames = 1;
                            g_Ball.AtBat_ContactResult = BALL_RESULT_TYPE_LANDED;
                            g_Ball.ballInitialHitDoneInd = 1;
                            if (g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD) {
                                QueueTextToDisplay(0xF, 0);
                            }
                        }
                    }
                }
                break;
            case BALL_RESULT_TYPE_LANDED:
                if (g_Ball.ballInitialHitDoneInd == 0 && isFoul != 0) {
                    if (g_Ball.deadBallReason == 0) {
                        BOOL runnerWasOut;

                        g_Ball.deadBallReason = 2;
                        g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                        g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                        g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                        g_Ball.AtBat_ContactResult = BALL_RESULT_TYPE_FOUL;
                        g_Ball.ballInitialHitDoneInd = 1;
                        runnerWasOut = FALSE;
                        if (g_FieldingLogic.hasProcessedFoulBall != 1) {
                            g_FieldingLogic.hasProcessedFoulBall = 1;
                            g_Strikes.strikes++;
                            if (g_Strikes.strikes >= 3) {
                                if (g_Ball.maybeBuntInd != 0) {
                                    g_Ball.maybebuntOn2Strikes = 1;
                                    runnerOut(0);
                                    runnerWasOut = TRUE;
                                } else {
                                    g_Strikes.strikes = 2;
                                }
                            }
                            if (runnerWasOut == 0) {
                                QueueTextToDisplay(3, 0);
                            }
                        }
                    }
                } else if ((g_Ball.maybeCollisionRelated & 0x7F) == BALL_COLLISION_TYPE_STRUCTURE) {
                    if (g_Ball.deadBallReason == 0) {
                        if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != 0) {
                            if (g_Ball.deadBallReason != 4) {
                                g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                                g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                                g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                                g_Ball.deadBallReason = 4;
                                if (g_RunningLogic._00 != 0) {
                                    QueueTextToDisplay(0x14, 0);
                                }
                            }
                        } else if (g_Ball.numFieldersWhoHandledBallDuringPlay != 0 &&
                                   g_Ball.numberOfThrowsDuringPlay != 0) {
                            if (g_Ball.deadBallReason != 4) {
                                g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                                g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                                g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                                g_Ball.deadBallReason = 4;
                                if (g_RunningLogic._00 != 0) {
                                    QueueTextToDisplay(0x14, 0);
                                }
                            }
                        } else {
                            g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                            g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                            g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                            g_Ball.deadBallReason = 3;
                            QueueTextToDisplay(7, 0);
                        }
                    }
                }
                break;
            default:
                if (g_Ball.deadBallReason != 4) {
                    g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                    g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                    g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                    g_Ball.deadBallReason = 4;
                    if (g_RunningLogic._00 != 0) {
                        QueueTextToDisplay(0x14, 0);
                    }
                }
                break;
        }
        if (g_Ball.matchFramesAndBallAngle.ballOverWallFrames == 0) {
            g_Ball.matchFramesAndBallAngle.ballOverWallFrames = 1;
        }
    } else if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_LANDED && g_Ball.ballInitialHitDoneInd == 0 &&
               g_Ball.AtBat_Contact_BallPos.z > base_MoundCoordinates[1].z) {
        g_Ball.ballInitialHitDoneInd = 1;
        if (isFoul != 0) {
            BOOL runnerWasOut;

            g_Ball.AtBat_ContactResult = BALL_RESULT_TYPE_FOUL;
            g_Ball.ballInitialHitDoneInd = 1;
            runnerWasOut = FALSE;
            if (g_FieldingLogic.hasProcessedFoulBall != 1) {
                g_FieldingLogic.hasProcessedFoulBall = 1;
                g_Strikes.strikes++;
                if (g_Strikes.strikes >= 3) {
                    if (g_Ball.maybeBuntInd != 0) {
                        g_Ball.maybebuntOn2Strikes = 1;
                        runnerOut(0);
                        runnerWasOut = TRUE;
                    } else {
                        g_Strikes.strikes = 2;
                    }
                }
                if (runnerWasOut == 0) {
                    QueueTextToDisplay(3, 0);
                }
            }
        } else {
            g_Ball.AtBat_ContactResult = BALL_RESULT_TYPE_LANDED;
            if (g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD) {
                if (foul_isBallWithin3mFair(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z)) {
                    QueueTextToDisplay(4, 1);
                }
            }
        }
    }
}

static inline void deadBallGroundRuleDouble(void) {
    if (g_Ball.deadBallReason == 0) {
        if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != 0) {
            if (g_Ball.deadBallReason != 4) {
                g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                g_Ball.deadBallReason = 4;
                if (g_RunningLogic._00 != 0) {
                    QueueTextToDisplay(0x14, 0);
                }
            }
        } else if (g_Ball.numFieldersWhoHandledBallDuringPlay != 0 && g_Ball.numberOfThrowsDuringPlay != 0) {
            if (g_Ball.deadBallReason != 4) {
                g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                g_Ball.deadBallReason = 4;
                if (g_RunningLogic._00 != 0) {
                    QueueTextToDisplay(0x14, 0);
                }
            }
        } else {
            g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
            g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
            g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
            g_Ball.deadBallReason = 3;
            QueueTextToDisplay(7, 0);
        }
    }
}

// .text:0x00006C38 size:0x20B8 mapped:0x80645CCC
void ballCollisionLogic(void) {
    VecSrcDst probe;
    CollisionStruct hit;
    VecXYZ axis;
    VecXYZ perp1;
    VecXYZ perp2;
    VecXYZ velCopy;
    u32 collType;
    u32 collKind;
    f32 frac;
    f32 dotPerp1;
    f32 dotPerp2;
    f32 negDotNormal;
    f32 absNormalX;
    f32 scale;
    f32 speed;
    f32 offset;
    s16 contactResult;

    g_Ball.ballOnMoundInd = 0;
    probe.src.x = g_Ball.AtBat_Contact_BallPos.x;
    probe.src.y = -g_Ball.AtBat_Contact_BallPos.y;
    probe.src.z = g_Ball.AtBat_Contact_BallPos.z;
    probe.dst.x = g_Ball.AtBat_Contact_BallPos.x;
    probe.dst.y = 10.0f;
    probe.dst.z = g_Ball.AtBat_Contact_BallPos.z;
    if (probe.src.y >= -0.1f) {
        probe.src.y = -0.1f;
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        probe.src.y -= 1.0f;
        collType = checkCollision(&probe, &hit, 1, FALSE);
    } else {
        collType = checkCollision(&probe, &hit, 0, FALSE);
    }
    g_Ball.maybeCollisionRelated = g_Ball.collisionCode;
    g_Ball.physicsSubstruct.twoFrameLookback[1] = -hit.position.y;
    if (collType != BALL_COLLISION_TYPE_NONE) {
        g_Ball.collisionCode = collType;
    }
    if ((g_Ball.collisionCode & 0x7F) == BALL_COLLISION_TYPE_ROUGH_TERRAIN) {
        processBallFielderCollision(0);
    }

    if (g_Ball.ballState == BALL_STATE_THROWN && g_Ball.framesSinceThrowStarted < 20) {
        return;
    }

    if (g_Ball.hitNoteBlockInd != 0) {
        if (stadiumObjectCollision.hazardHitActive != 0) {
            return;
        }
        g_Ball.hitNoteBlockInd = 0;
        g_FieldingLogic.knockoutFinished = 1;
        if (!g_d_GameSettings.exhibitionMatchInd && lbl_3_common_bss_37400[0x20] == g_GameLogic.teamBatting) {
            starMissionsQuantityBased(0, g_Batter.rosterID);
        }
    }

    probe.src.x = g_Ball.pastCoordinates[0].x;
    probe.src.y = -(g_Ball.pastCoordinates[0].y - g_Ball.groundYForBounces);
    probe.src.z = g_Ball.pastCoordinates[0].z;
    probe.dst.x = g_Ball.AtBat_Contact_BallPos.x;
    probe.dst.y = -(g_Ball.AtBat_Contact_BallPos.y - g_Ball.groundYForBounces);
    probe.dst.z = g_Ball.AtBat_Contact_BallPos.z;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        collType = checkCollision(&probe, &hit, 2, TRUE);
    } else {
        collType = checkCollision(&probe, &hit, 1, TRUE);
    }
    if (collType == BALL_COLLISION_TYPE_NONE) {
        checkForBallDead();
        return;
    }

    collKind = collType & 0x7F;

    if (g_Ball.ballState == BALL_STATE_THROWN) {
        if ((u32)(collKind - 0x10) <= 5 || collKind == 0x21 || collKind == 0x30 || collKind == 0x40 ||
            collKind == 0x60 || collKind == 0x61) {
            return;
        }
    }
    if (g_Ball.someCollisionInd != 0) {
        if (collKind == 0x21 || collKind == 0x30 || collKind == 0x40 || collKind == 0x60 || collKind == 0x61) {
            return;
        }
    }
    if (g_Ball.currentStarSwing2 == CAPTAIN_STAR_TYPE_PEACH || g_Ball.currentStarSwing2 == CAPTAIN_STAR_TYPE_DAISY) {
        if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR) {
            if ((u32)(collKind - 0x10) <= 5 || collKind == 0x21 || collKind == 0x40) {
                return;
            }
        }
    }
    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY && g_Ball.bODQualifyingHitInd != 0) {
        return;
    }

    if (g_Ball.matchFramesAndBallAngle.framesOnGround < 0x7FFE) {
        g_Ball.matchFramesAndBallAngle.framesOnGround++;
    } else {
        g_Ball.matchFramesAndBallAngle.framesOnGround = 0x7FFF;
    }

    frac = probe.src.y - probe.dst.y;
    if (0.0f == frac) {
        frac = 1.0f;
    } else {
        frac = 1.0f - (probe.src.y - hit.position.y) / frac;
    }

    offset = 0.005f + g_Ball.groundYForBounces;
    g_Ball.AtBat_Contact_BallPos.y = -(hit.normal.y * offset + hit.position.y);
    g_Ball.AtBat_Contact_BallPos.x = hit.normal.x * offset + hit.position.x;
    g_Ball.AtBat_Contact_BallPos.z = hit.normal.z * offset + hit.position.z;

    velCopy.z = g_Ball.physicsSubstruct.velocity.z;
    velCopy.y = -g_Ball.physicsSubstruct.velocity.y;
    velCopy.x = g_Ball.physicsSubstruct.velocity.x;

    absNormalX = hit.normal.x;
    if (absNormalX < 0.0f) {
        absNormalX = -absNormalX;
    }
    if (absNormalX < 0.5f) {
        axis.x = 1.0f;
        axis.y = 0.0f;
        axis.z = 0.0f;
    } else {
        axis.x = 0.0f;
        axis.y = 1.0f;
        axis.z = 0.0f;
    }
    CrossProduct(&perp1, (VecXYZ*)&hit.normal, &axis);
    CrossProduct(&perp2, (VecXYZ*)&hit.normal, &perp1);
    dotPerp1 = vecDotProduct(&velCopy, &perp1);
    dotPerp2 = vecDotProduct(&velCopy, &perp2);
    negDotNormal = -vecDotProduct(&velCopy, (VecXYZ*)&hit.normal);

    g_Ball.physicsSubstruct.velocity.x = hit.normal.x * negDotNormal + (perp1.x * dotPerp1 + perp2.x * dotPerp2);
    g_Ball.physicsSubstruct.velocity.y = hit.normal.y * negDotNormal + (perp1.y * dotPerp1 + perp2.y * dotPerp2);
    g_Ball.physicsSubstruct.velocity.z = hit.normal.z * negDotNormal + (perp1.z * dotPerp1 + perp2.z * dotPerp2);
    g_Ball.physicsSubstruct.velocity.y *= -1.0f;

    if (collKind == BALL_COLLISION_TYPE_GRASS || collKind == BALL_COLLISION_TYPE_DIRT ||
        collKind == BALL_COLLISION_TYPE_ROUGH_TERRAIN || collKind == BALL_COLLISION_TYPE_WATER || collKind == 0x22 ||
        collKind == 0x32) {
        if (g_Ball.ballIsRollingIndicator == 0) {
            fn_3_15F648(collKind, animRelated[0xCA], &g_Ball.AtBat_Contact_BallPos, &g_Ball.physicsSubstruct.velocity);
        } else if (collKind == BALL_COLLISION_TYPE_WATER) {
            handleBallRollInWater(&g_Ball.AtBat_Contact_BallPos, &g_Ball.physicsSubstruct.velocity);
        }
        if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR) {
            handleBallBounceAndRoll(&g_Ball.physicsSubstruct.velocity.y, 0, &g_Ball.ballIsRollingIndicator, FALSE);
        } else {
            handleBallBounceAndRoll(&g_Ball.physicsSubstruct.velocity.y, g_Ball.framesOnGroundUntilPickedUp,
                                    &g_Ball.ballIsRollingIndicator, FALSE);
        }
        g_Ball.physicsSubstruct.acceleration.x *= 0.5f;
        g_Ball.physicsSubstruct.acceleration.z *= 0.5f;

        if (g_Ball.ballState == BALL_STATE_THROWN) {
            s32 kind = g_Ball.collisionCode & 0x7F;
            u8 isRolling = g_Ball.ballIsRollingIndicator;

            if (g_Ball.knockoutProcessedFlag != 0) {
                g_Ball.physicsSubstruct.velocity.x = g_Ball.savedVelocity.x;
                g_Ball.physicsSubstruct.velocity.z = g_Ball.savedVelocity.z;
                g_Ball.knockoutProcessedFlag = 0;
            } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && kind >= 0x70 && kind < 0x79) {
                if (isRolling != 0) {
                    g_Ball.physicsSubstruct.velocity.x *= lbl_3_data_4414.rollingSpeedKept;
                    g_Ball.physicsSubstruct.velocity.z *= lbl_3_data_4414.rollingSpeedKept;
                } else {
                    g_Ball.physicsSubstruct.velocity.x *= lbl_3_data_4414.xOtherBouncesSpeedKept;
                    g_Ball.physicsSubstruct.velocity.z *= lbl_3_data_4414.xOtherBouncesSpeedKept;
                }
            } else {
                if (isRolling != 0) {
                    g_Ball.physicsSubstruct.velocity.x *=
                        ballBounceConstants[g_d_GameSettings.StadiumID].rollingSpeedKept;
                    g_Ball.physicsSubstruct.velocity.z *=
                        ballBounceConstants[g_d_GameSettings.StadiumID].rollingSpeedKept;
                } else {
                    g_Ball.physicsSubstruct.velocity.x *=
                        ballBounceConstants[g_d_GameSettings.StadiumID].xOtherBouncesSpeedKept;
                    g_Ball.physicsSubstruct.velocity.z *=
                        ballBounceConstants[g_d_GameSettings.StadiumID].xOtherBouncesSpeedKept;
                }
            }
            g_Ball.thrownBallHasHitGround = 1;
        } else {
            contactResult = g_Ball.AtBat_ContactResult;
            if (contactResult == BALL_RESULT_TYPE_IN_AIR) {
                processBallInAir_Landed();
            } else if (contactResult == BALL_RESULT_TYPE_LANDED) {
                processLandedBallBouncing();
            } else if (contactResult == BALL_RESULT_TYPE_FOUL) {
                s32 kind = g_Ball.collisionCode & 0x7F;
                u8 isRolling = g_Ball.ballIsRollingIndicator;

                if (g_Ball.knockoutProcessedFlag != 0) {
                    g_Ball.physicsSubstruct.velocity.x = g_Ball.savedVelocity.x;
                    g_Ball.physicsSubstruct.velocity.z = g_Ball.savedVelocity.z;
                    g_Ball.knockoutProcessedFlag = 0;
                } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && kind >= 0x70 && kind < 0x79) {
                    if (isRolling != 0) {
                        g_Ball.physicsSubstruct.velocity.x *= lbl_3_data_4414.rollingSpeedKept;
                        g_Ball.physicsSubstruct.velocity.z *= lbl_3_data_4414.rollingSpeedKept;
                    } else {
                        g_Ball.physicsSubstruct.velocity.x *= lbl_3_data_4414.xOtherBouncesSpeedKept;
                        g_Ball.physicsSubstruct.velocity.z *= lbl_3_data_4414.xOtherBouncesSpeedKept;
                    }
                } else {
                    if (isRolling != 0) {
                        g_Ball.physicsSubstruct.velocity.x *=
                            ballBounceConstants[g_d_GameSettings.StadiumID].rollingSpeedKept;
                        g_Ball.physicsSubstruct.velocity.z *=
                            ballBounceConstants[g_d_GameSettings.StadiumID].rollingSpeedKept;
                    } else {
                        g_Ball.physicsSubstruct.velocity.x *=
                            ballBounceConstants[g_d_GameSettings.StadiumID].xOtherBouncesSpeedKept;
                        g_Ball.physicsSubstruct.velocity.z *=
                            ballBounceConstants[g_d_GameSettings.StadiumID].xOtherBouncesSpeedKept;
                    }
                }
            } else {
                s32 kind = g_Ball.collisionCode & 0x7F;
                u8 isRolling = g_Ball.ballIsRollingIndicator;

                if (g_Ball.knockoutProcessedFlag != 0) {
                    g_Ball.physicsSubstruct.velocity.x = g_Ball.savedVelocity.x;
                    g_Ball.physicsSubstruct.velocity.z = g_Ball.savedVelocity.z;
                    g_Ball.knockoutProcessedFlag = 0;
                } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && kind >= 0x70 && kind < 0x79) {
                    if (isRolling != 0) {
                        g_Ball.physicsSubstruct.velocity.x *= lbl_3_data_4414.rollingSpeedKept;
                        g_Ball.physicsSubstruct.velocity.z *= lbl_3_data_4414.rollingSpeedKept;
                    } else {
                        g_Ball.physicsSubstruct.velocity.x *= lbl_3_data_4414.xOtherBouncesSpeedKept;
                        g_Ball.physicsSubstruct.velocity.z *= lbl_3_data_4414.xOtherBouncesSpeedKept;
                    }
                } else {
                    if (isRolling != 0) {
                        g_Ball.physicsSubstruct.velocity.x *=
                            ballBounceConstants[g_d_GameSettings.StadiumID].rollingSpeedKept;
                        g_Ball.physicsSubstruct.velocity.z *=
                            ballBounceConstants[g_d_GameSettings.StadiumID].rollingSpeedKept;
                    } else {
                        g_Ball.physicsSubstruct.velocity.x *=
                            ballBounceConstants[g_d_GameSettings.StadiumID].xOtherBouncesSpeedKept;
                        g_Ball.physicsSubstruct.velocity.z *=
                            ballBounceConstants[g_d_GameSettings.StadiumID].xOtherBouncesSpeedKept;
                    }
                }
            }
        }

        probe.src.x = g_Ball.AtBat_Contact_BallPos.x;
        probe.src.y = -(g_Ball.AtBat_Contact_BallPos.y - g_Ball.groundYForBounces);
        probe.src.z = g_Ball.AtBat_Contact_BallPos.z;
        probe.dst.x = g_Ball.physicsSubstruct.velocity.x * frac + g_Ball.AtBat_Contact_BallPos.x;
        probe.dst.y =
            -((g_Ball.physicsSubstruct.velocity.y * frac + g_Ball.AtBat_Contact_BallPos.y) - g_Ball.groundYForBounces);
        probe.dst.z = g_Ball.physicsSubstruct.velocity.z * frac + g_Ball.AtBat_Contact_BallPos.z;
        collType = checkCollision(&probe, &hit, 1, FALSE);
        if (collType == BALL_COLLISION_TYPE_NONE) {
            g_Ball.AtBat_Contact_BallPos.x = g_Ball.physicsSubstruct.velocity.x * frac + g_Ball.AtBat_Contact_BallPos.x;
            g_Ball.AtBat_Contact_BallPos.y = g_Ball.physicsSubstruct.velocity.y * frac + g_Ball.AtBat_Contact_BallPos.y;
            g_Ball.AtBat_Contact_BallPos.z = g_Ball.physicsSubstruct.velocity.z * frac + g_Ball.AtBat_Contact_BallPos.z;
        }
        if (g_Ball.distLandingSpotToMound <= 3.0f) {
            g_Ball.ballOnMoundInd = 1;
        }
        if (g_Ball.framesOnGroundUntilPickedUp < 0xFE) {
            g_Ball.framesOnGroundUntilPickedUp++;
        } else {
            g_Ball.framesOnGroundUntilPickedUp = 0xFF;
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
            fn_3_E7350();
        }
    } else {
        g_Ball.AtBat_Contact_BallPos.y = g_Ball.AtBat_Contact_BallPos.y + g_Ball.groundYForBounces;
        g_Ball.framesSinceBallHitWall = 1;
        g_Ball.physicsSubstruct.acceleration.x = 0.0f;
        g_Ball.physicsSubstruct.acceleration.y = 0.0f;
        g_Ball.physicsSubstruct.acceleration.z = 0.0f;

        if (collKind == BALL_COLLISION_TYPE_FOUL_LINE) {
            handleBallHitDeadBallOutcome();
            g_Ball.currentStarSwing = 0;
        } else if (collKind == BALL_COLLISION_TYPE_WALL || collKind == BALL_COLLISION_TYPE_UNCLIMBABLE_WALL ||
                   collKind == 0x20) {
            fairOrFoulBall(collType);
            processFielderAutoCatch();
            g_Ball.currentStarSwing = 0;
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                fn_3_E7350();
            }
        } else if (collKind == BALL_COLLISION_TYPE_CHOMP_HAZARD) {
            fairOrFoulBall(collType);
            processFielderAutoCatch();
            g_Ball.currentStarSwing = 0;
        } else if ((collKind == BALL_COLLISION_TYPE_STRUCTURE || collKind == BALL_COLLISION_TYPE_PIT_WALL ||
                    collKind == BALL_COLLISION_TYPE_PIT || collKind == 0x23) &&
                   g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR) {
            if (g_Ball.bobbleLocation_1fair_2foul == 1) {
                if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD &&
                    (collKind == BALL_COLLISION_TYPE_PIT_WALL || collKind == BALL_COLLISION_TYPE_PIT)) {
                    foulBall();
                } else if (g_Ball.numberOfThrowsDuringPlay == 0 && g_Ball.numFieldersWhoHandledBallDuringPlay != 0 &&
                           g_Ball.framesOnGroundUntilPickedUp == 0) {
                    if (foul_checkIfFoul(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z) != 0) {
                        deadBallGroundRuleDouble();
                    } else {
                        fn_3_9FA4();
                    }
                } else {
                    deadBallGroundRuleDouble();
                }
            } else if ((collType & BALL_COLLISION_TYPE_FOUL) == 0) {
                fn_3_9FA4();
            } else {
                foulBall();
            }
            g_Ball.physicsSubstruct.velocity.x = 0.3f * g_Ball.physicsSubstruct.velocity.x;
            g_Ball.physicsSubstruct.velocity.y = 0.3f * g_Ball.physicsSubstruct.velocity.y;
            g_Ball.currentStarSwing = 0;
            g_Ball.physicsSubstruct.velocity.z = 0.3f * g_Ball.physicsSubstruct.velocity.z;
        } else if ((u32)(collKind - 0x10) <= 4 || collKind == 0x15) {
            if (collKind == 0x12 || collKind == 0x15) {
                g_Ball.hitNoteBlockInd = 1;
            } else {
                g_FieldingLogic.knockoutFinished = 1;
            }
            scale = lbl_3_data_610C[collKind - 0x10];
            g_Ball.physicsSubstruct.velocity.x = g_Ball.physicsSubstruct.velocity.x * scale;
            g_Ball.physicsSubstruct.velocity.y = g_Ball.physicsSubstruct.velocity.y * scale;
            g_Ball.physicsSubstruct.velocity.z = g_Ball.physicsSubstruct.velocity.z * scale;
            speed = dolsqrtf2(g_Ball.physicsSubstruct.velocity.x * g_Ball.physicsSubstruct.velocity.x +
                              g_Ball.physicsSubstruct.velocity.z * g_Ball.physicsSubstruct.velocity.z);
            if (speed < 0.03f) {
                if (0.0f == speed) {
                    g_Ball.physicsSubstruct.velocity.x =
                        0.03f * (g_Ball.AtBat_Contact_BallPos.x / g_Ball.ballDistanceFromHome);
                    g_Ball.physicsSubstruct.velocity.z =
                        0.03f * (g_Ball.AtBat_Contact_BallPos.z / g_Ball.ballDistanceFromHome);
                } else {
                    g_Ball.physicsSubstruct.velocity.x = 0.03f * (g_Ball.physicsSubstruct.velocity.x / speed);
                    g_Ball.physicsSubstruct.velocity.z = 0.03f * (g_Ball.physicsSubstruct.velocity.z / speed);
                }
            }
            if (g_Ball.ballState == BALL_STATE_THROWN) {
                g_Ball.ballState = BALL_STATE_HELD;
            }
            processFielderAutoCatch();
            g_Ball.someCollisionVariable = 0;
            g_Ball.someCollisionInd = 1;
        } else if (collKind == 0x20 || collKind == 0x21) {
            scale = lbl_3_data_6124[collKind - 0x20];
            g_Ball.physicsSubstruct.velocity.x = g_Ball.physicsSubstruct.velocity.x * scale;
            g_Ball.physicsSubstruct.velocity.y = g_Ball.physicsSubstruct.velocity.y * scale;
            g_Ball.physicsSubstruct.velocity.z = g_Ball.physicsSubstruct.velocity.z * scale;
            dolsqrtf2(g_Ball.physicsSubstruct.velocity.x * g_Ball.physicsSubstruct.velocity.x +
                      g_Ball.physicsSubstruct.velocity.z * g_Ball.physicsSubstruct.velocity.z);
            speed = dolsqrtf2(g_Ball.physicsSubstruct.velocity.x * g_Ball.physicsSubstruct.velocity.x +
                              g_Ball.physicsSubstruct.velocity.z * g_Ball.physicsSubstruct.velocity.z);
            if (speed < 0.03f) {
                if (0.0f == speed) {
                    g_Ball.physicsSubstruct.velocity.x =
                        0.03f * (g_Ball.AtBat_Contact_BallPos.x / g_Ball.ballDistanceFromHome);
                    g_Ball.physicsSubstruct.velocity.z =
                        0.03f * (g_Ball.AtBat_Contact_BallPos.z / g_Ball.ballDistanceFromHome);
                } else {
                    g_Ball.physicsSubstruct.velocity.x = 0.03f * (g_Ball.physicsSubstruct.velocity.x / speed);
                    g_Ball.physicsSubstruct.velocity.z = 0.03f * (g_Ball.physicsSubstruct.velocity.z / speed);
                }
            }
            g_Ball.someCollisionVariable = 0;
            if (g_Ball.ballState == BALL_STATE_THROWN) {
                g_Ball.ballState = BALL_STATE_HELD;
            }
            g_Ball.someCollisionInd = 1;
        } else if (collKind == 0x30 || collKind == 0x40 || collKind == 0x60 || collKind == 0x61) {
            g_Ball.physicsSubstruct.velocity.x = 0.5f * g_Ball.physicsSubstruct.velocity.x;
            g_Ball.physicsSubstruct.velocity.y = 0.5f * g_Ball.physicsSubstruct.velocity.y;
            g_Ball.physicsSubstruct.velocity.z = 0.5f * g_Ball.physicsSubstruct.velocity.z;
            speed = dolsqrtf2(g_Ball.physicsSubstruct.velocity.x * g_Ball.physicsSubstruct.velocity.x +
                              g_Ball.physicsSubstruct.velocity.z * g_Ball.physicsSubstruct.velocity.z);
            if (speed < 0.03f) {
                if (0.0f == speed) {
                    g_Ball.physicsSubstruct.velocity.x =
                        0.03f * (g_Ball.AtBat_Contact_BallPos.x / g_Ball.ballDistanceFromHome);
                    g_Ball.physicsSubstruct.velocity.z =
                        0.03f * (g_Ball.AtBat_Contact_BallPos.z / g_Ball.ballDistanceFromHome);
                } else {
                    g_Ball.physicsSubstruct.velocity.x = 0.03f * (g_Ball.physicsSubstruct.velocity.x / speed);
                    g_Ball.physicsSubstruct.velocity.z = 0.03f * (g_Ball.physicsSubstruct.velocity.z / speed);
                }
            }
            if (g_Ball.ballState == BALL_STATE_THROWN) {
                g_Ball.ballState = BALL_STATE_HELD;
            }
            processFielderAutoCatch();
            g_Ball.someCollisionVariable = 0;
            g_Ball.someCollisionInd = 1;
        } else if (collKind >= 0x70 && collKind < 0x79) {
            if (collKind == 0x70) {
                g_Ball.physicsSubstruct.velocity.x = 0.3f * g_Ball.physicsSubstruct.velocity.x;
                g_Ball.physicsSubstruct.velocity.y = 0.3f * g_Ball.physicsSubstruct.velocity.y;
                g_Ball.physicsSubstruct.velocity.z = 0.3f * g_Ball.physicsSubstruct.velocity.z;
            } else {
                if (g_Minigame.toyFieldStateInd_collisionRelated == 0) {
                    g_Minigame.toyFieldStateInd_collisionRelated = collKind;
                }
                g_Ball.physicsSubstruct.velocity.x = 0.3f * g_Ball.physicsSubstruct.velocity.x;
                g_Ball.physicsSubstruct.velocity.y = 0.3f * g_Ball.physicsSubstruct.velocity.y;
                g_Ball.physicsSubstruct.velocity.z = 0.3f * g_Ball.physicsSubstruct.velocity.z;
            }
        } else {
            if (g_Ball.ballState != BALL_STATE_HIT) {
                g_Ball.physicsSubstruct.velocity.x = 0.05f * g_Ball.physicsSubstruct.velocity.x;
                g_Ball.physicsSubstruct.velocity.y = 0.05f * g_Ball.physicsSubstruct.velocity.y;
                g_Ball.physicsSubstruct.velocity.z = 0.05f * g_Ball.physicsSubstruct.velocity.z;
            } else {
                g_Ball.physicsSubstruct.velocity.x = 0.3f * g_Ball.physicsSubstruct.velocity.x;
                g_Ball.physicsSubstruct.velocity.y = 0.3f * g_Ball.physicsSubstruct.velocity.y;
                g_Ball.physicsSubstruct.velocity.z = 0.3f * g_Ball.physicsSubstruct.velocity.z;
            }
            if (collKind == BALL_COLLISION_TYPE_PIT_WALL || collKind == BALL_COLLISION_TYPE_PIT) {
                if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                    foulBall();
                } else if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FOUL) {
                    foulBall();
                } else if (g_Ball.AtBat_ContactResult > 0) {
                    deadBallGroundRuleDouble();
                } else if (g_Ball.numberOfThrowsDuringPlay == 0) {
                    if (g_Ball.numFieldersWhoHandledBallDuringPlay != 0) {
                        if (g_Ball.bobbleLocation_1fair_2foul == 2) {
                            foulBall();
                        } else {
                            deadBallGroundRuleDouble();
                        }
                    } else if ((collType & BALL_COLLISION_TYPE_FOUL) != 0) {
                        foulBall();
                    } else {
                        deadBallGroundRuleDouble();
                    }
                } else {
                    deadBallGroundRuleDouble();
                }
            }
            g_Ball.collisionRelated = g_Ball.collisionRelated + 1;
            if (g_Ball.deadBallReason == 3) {
                g_Ball.collisionRelated = 2;
            }
            g_Ball.currentStarSwing = 0;
            processFielderAutoCatch();
        }

        if (g_d_GameSettings.StadiumID == STADIUM_ID_MARIO_STADIUM ||
            (u8)(g_d_GameSettings.StadiumID - STADIUM_ID_WARIO_PALACE) <= STADIUM_ID_PEACH_GARDEN - STADIUM_ID_WARIO_PALACE ||
            g_d_GameSettings.StadiumID == STADIUM_ID_DK_JUNGLE) {
            if (g_Ball.AtBat_Contact_BallPos.y < 0.005f + g_Ball.groundYForBounces) {
                g_Ball.AtBat_Contact_BallPos.y = 0.005f + g_Ball.groundYForBounces;
                if (g_Ball.physicsSubstruct.velocity.y < 0.0f) {
                    g_Ball.physicsSubstruct.velocity.y *= -1.0f;
                }
            }
        }
        if (g_Ball.ballIsRollingIndicator != 0 && g_Ball.physicsSubstruct.velocity.y < 0.0f) {
            g_Ball.physicsSubstruct.velocity.y *= -1.0f;
        }
        g_Ball.ballBounceState = 3;
        g_Ball.hitWallInd = 1;
        if (g_Ball.framesOnGroundUntilPickedUp < 0xFE) {
            g_Ball.framesOnGroundUntilPickedUp++;
        } else {
            g_Ball.framesOnGroundUntilPickedUp = 0xFF;
        }
        if (g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam] != 0) {
            s32 i;

            for (i = 0; i < 9; i++) {
                g_Fielders[i]._01E1 = 0;
            }
        }
    }

    speed = dolsqrtf2(g_Ball.physicsSubstruct.velocity.x * g_Ball.physicsSubstruct.velocity.x +
                      g_Ball.physicsSubstruct.velocity.z * g_Ball.physicsSubstruct.velocity.z);
    if (speed < 0.0001f) {
        g_Ball.physicsSubstruct.velocity.x = 0.0f;
        g_Ball.physicsSubstruct.velocity.z = 0.0f;
    }
    g_Ball.framesSinceLastBounce = 0;
    if (g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_WARIO || g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_WALUIGI) {
        g_Ball.currentStarSwing = 0;
    }
    g_Ball.warioWaluGarlicIsActive = 0;
}

// .text:0x00008CF0 size:0x35C mapped:0x80647D84
void handleBallBounceAndRoll(f32* verticalVelocity, int bounceFrameCount, u8* ballIsRolling, BOOL skipStarBounce) {
    f32 speed;
    f32 cx, cy;
    f32 bounceVelocity;
    int angleOffset;
    s32 collisionKind = g_Ball.collisionCode & 0x7F;

    if ((g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_YOSHI || g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_BIRDO) &&
        skipStarBounce == 0) {
        speed = VEC_DISTANCE(&g_Ball.pastCoordinates[1], &g_Ball.pastCoordinates[0]);

        bounceVelocity = speed * g_hitFloats.eggVeloMaintainedOnBounce;
        getComponentsFromSAng((s16)(RandomInt_Game(0x200) + 0x80), &cx, &cy);
        *verticalVelocity = bounceVelocity * cy;
        bounceVelocity = bounceVelocity * cx;
        angleOffset = RandomInt_Game(0x800) - 0x400;
        getComponentsFromSAng((s16)(angleOffset + g_Ball.ballTravelAngle), &cx, &cy);
        g_Ball.savedVelocity.x = bounceVelocity * cx;
        g_Ball.savedVelocity.z = bounceVelocity * cy;
        g_Ball.knockoutProcessedFlag = 1;
        g_FieldingLogic.knockoutFinished = 1;
        processFielderAutoCatch();
    } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && collisionKind >= 0x70 && collisionKind < 0x79) {
        if (bounceFrameCount == 0) {
            *verticalVelocity = *verticalVelocity * lbl_3_data_4414.y1stBounceSpeedKept;
        } else {
            *verticalVelocity = *verticalVelocity * lbl_3_data_4414.yOtherBouncesSpeedKept;
        }
    } else {
        if (bounceFrameCount == 0) {
            *verticalVelocity = *verticalVelocity * ballBounceConstants[g_d_GameSettings.StadiumID].y1stBounceSpeedKept;
        } else {
            *verticalVelocity = *verticalVelocity * ballBounceConstants[g_d_GameSettings.StadiumID].yOtherBouncesSpeedKept;
        }
    }

    if (*ballIsRolling == 0 && *verticalVelocity < lbl_3_data_4604 && bounceFrameCount >= lbl_3_data_4608) {
        *ballIsRolling = 1;
    }
    if (*ballIsRolling != 0) {
        *verticalVelocity = 0.0f;
    }
}

// .text:0x0000904C size:0x214 mapped:0x806480E0
void handleBallHitDeadBallOutcome(void) {
    g_Ball.physicsSubstruct.velocity.x = lbl_3_rodata_5B0 * g_Ball.physicsSubstruct.velocity.x;
    g_Ball.physicsSubstruct.velocity.y = lbl_3_rodata_5B0 * g_Ball.physicsSubstruct.velocity.y;
    g_Ball.physicsSubstruct.velocity.z = lbl_3_rodata_5B0 * g_Ball.physicsSubstruct.velocity.z;
    if (g_Ball.deadBallReason == 1) {
        g_Ball.homeRunInd = 1;
    } else if (g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_FOUL) {
        if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR || g_Ball.deadBallReason == 1
            || (g_Ball.numberOfThrowsDuringPlay == 0 && g_Ball.numFieldersWhoHandledBallDuringPlay != 0
                && g_Ball.framesOnGroundUntilPickedUp == 0)) {
            if (g_Ball.deadBallReason == 0) {
                g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                g_Ball.deadBallReason = 1;
                g_Ball.matchFramesAndBallAngle.ballOverWallFrames = 1;
                g_Ball.AtBat_ContactResult = BALL_RESULT_TYPE_LANDED;
                g_Ball.ballInitialHitDoneInd = 1;
                if (g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD) {
                    QueueTextToDisplay(0xF, 0);
                }
            }
            g_Ball.homeRunInd = 1;
        } else if (g_Ball.deadBallReason == 0) {
            if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != 0) {
                if (g_Ball.deadBallReason != 4) {
                    g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                    g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                    g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                    g_Ball.deadBallReason = 4;
                    if (g_RunningLogic._00 != 0) {
                        QueueTextToDisplay(0x14, 0);
                    }
                }
            } else if (g_Ball.numFieldersWhoHandledBallDuringPlay != 0 && g_Ball.numberOfThrowsDuringPlay != 0) {
                if (g_Ball.deadBallReason != 4) {
                    g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                    g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                    g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                    g_Ball.deadBallReason = 4;
                    if (g_RunningLogic._00 != 0) {
                        QueueTextToDisplay(0x14, 0);
                    }
                }
            } else {
                g_Ball.deadBallReason = 3;
                g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                QueueTextToDisplay(7, 0);
            }
        }
    }
}

// .text:0x00009260 size:0x2A8 mapped:0x806482F4
void fairOrFoulBall(BALL_COLLISION_TYPE collType) {
    s32 collKind = collType & 0x7F;

    g_Ball.physicsSubstruct.velocity.x *= lbl_3_data_4428[g_d_GameSettings.StadiumID];
    g_Ball.physicsSubstruct.velocity.y *= lbl_3_data_4428[g_d_GameSettings.StadiumID];
    g_Ball.physicsSubstruct.velocity.z *= lbl_3_data_4428[g_d_GameSettings.StadiumID];

    if (collKind != BALL_COLLISION_TYPE_CHOMP_HAZARD && g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR) {
        if ((collType & BALL_COLLISION_TYPE_FOUL) != 0 && g_Ball.numFieldersWhoHandledBallDuringPlay == 0) {
            foulBall();
        } else {
            g_Ball.AtBat_ContactResult = BALL_RESULT_TYPE_LANDED;
            g_Ball.ballInitialHitDoneInd = 1;
            if (g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD) {
                if (foul_isBallWithin3mFair(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z)) {
                    QueueTextToDisplay(4, 1);
                } else if (g_Ball.AtBat_Contact_BallPos.y < lbl_3_rodata_5DC) {
                    int i;

                    for (i = 0; i < 9; i++) {
                        if (g_Fielders[i].distanceFromBall < 2.0f) {
                            QueueTextToDisplay(4, 1);
                            break;
                        }
                    }
                }
            }
        }
    }

    switch (g_d_GameSettings.StadiumID) {
        case STADIUM_ID_MARIO_STADIUM:
            animateThrownBall(0x172, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.y,
                              g_Ball.AtBat_Contact_BallPos.z);
            break;
        case STADIUM_ID_BOWSERS_CASTLE:
            animateThrownBall(0x1A1, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.y,
                              g_Ball.AtBat_Contact_BallPos.z);
            break;
        case STADIUM_ID_WARIO_PALACE:
            animateThrownBall(0x1A1, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.y,
                              g_Ball.AtBat_Contact_BallPos.z);
            break;
        case STADIUM_ID_YOHSI_PARK:
            animateThrownBall(0x1A3, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.y,
                              g_Ball.AtBat_Contact_BallPos.z);
            break;
        case STADIUM_ID_PEACH_GARDEN:
            animateThrownBall(0x1A1, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.y,
                              g_Ball.AtBat_Contact_BallPos.z);
            break;
        case STADIUM_ID_DK_JUNGLE:
            animateThrownBall(0x172, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.y,
                              g_Ball.AtBat_Contact_BallPos.z);
            break;
        case STADIUM_ID_TOY_FIELD:
            animateThrownBall(0x172, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.y,
                              g_Ball.AtBat_Contact_BallPos.z);
            break;
    }
}

// .text:0x00009508 size:0x300 mapped:0x8064859C
void processLandedBallBouncing(void) {
    s32 collisionKind = g_Ball.collisionCode & 0x7F;
    u8 isRolling = g_Ball.ballIsRollingIndicator;

    if (g_Ball.knockoutProcessedFlag != 0) {
        g_Ball.physicsSubstruct.velocity.x = g_Ball.savedVelocity.x;
        g_Ball.physicsSubstruct.velocity.z = g_Ball.savedVelocity.z;
        g_Ball.knockoutProcessedFlag = 0;
    } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && collisionKind >= 0x70 && collisionKind < 0x79) {
        if (isRolling != 0) {
            g_Ball.physicsSubstruct.velocity.x *= lbl_3_data_4414.rollingSpeedKept;
            g_Ball.physicsSubstruct.velocity.z *= lbl_3_data_4414.rollingSpeedKept;
        } else {
            g_Ball.physicsSubstruct.velocity.x *= lbl_3_data_4414.xOtherBouncesSpeedKept;
            g_Ball.physicsSubstruct.velocity.z *= lbl_3_data_4414.xOtherBouncesSpeedKept;
        }
    } else {
        if (isRolling != 0) {
            g_Ball.physicsSubstruct.velocity.x *= ballBounceConstants[g_d_GameSettings.StadiumID].rollingSpeedKept;
            g_Ball.physicsSubstruct.velocity.z *= ballBounceConstants[g_d_GameSettings.StadiumID].rollingSpeedKept;
        } else {
            g_Ball.physicsSubstruct.velocity.x *= ballBounceConstants[g_d_GameSettings.StadiumID].xOtherBouncesSpeedKept;
            g_Ball.physicsSubstruct.velocity.z *= ballBounceConstants[g_d_GameSettings.StadiumID].xOtherBouncesSpeedKept;
        }
    }

    if (g_Ball.ballInitialHitDoneInd == 0) {
        if (foul_checkIfFoul(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z)) {
            if (foul_ifBallConsideredPastTheBases(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z) ||
                (g_Ball.AtBat_Contact_BallPos.x > 0.0f
                     ? g_Ball.AtBat_Contact_BallPos.z - g_Ball.AtBat_Contact_BallPos.x
                     : g_Ball.AtBat_Contact_BallPos.z + g_Ball.AtBat_Contact_BallPos.x) <
                    lbl_3_rodata_5E4 ||
                g_Ball.ballVelocity < lbl_3_rodata_5D4) {
                foulBall();
            }
        } else if (g_Ball.ballVelocity < lbl_3_rodata_5E8) {
            g_Ball.ballInitialHitDoneInd = 1;
        }
    } else if (g_Ball.numFieldersWhoHandledBallDuringPlay != 0 && g_Ball.framesOnGroundUntilPickedUp == 0 &&
               g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_LANDED) {
        QueueTextToDisplay(4, 1);
    }

    if (g_Ball.framesOnGroundUntilPickedUp < 3) {
        makeSoundOfBallBouncing();
    }
}

// .text:0x00009808 size:0x36C mapped:0x8064889C
void processBallInAir_Landed(void) {
    s32 collisionKind = g_Ball.collisionCode & 0x7F;

    if (g_Ball.knockoutProcessedFlag != 0) {
        g_Ball.physicsSubstruct.velocity.x = g_Ball.savedVelocity.x;
        g_Ball.physicsSubstruct.velocity.z = g_Ball.savedVelocity.z;
        g_Ball.knockoutProcessedFlag = 0;
    } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && collisionKind >= 0x70 && collisionKind < 0x79) {
        g_Ball.physicsSubstruct.velocity.x *= lbl_3_data_4414.x1stBounceSpeedKept;
        g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy = 0;
        g_Ball.physicsSubstruct.velocity.z *= lbl_3_data_4414.x1stBounceSpeedKept;
    } else {
        g_Ball.physicsSubstruct.velocity.x *= ballBounceConstants[g_d_GameSettings.StadiumID].x1stBounceSpeedKept;
        g_Ball.physicsSubstruct.velocity.z *= ballBounceConstants[g_d_GameSettings.StadiumID].x1stBounceSpeedKept;
    }

    g_Ball.AtBat_ContactResult = BALL_RESULT_TYPE_LANDED;
    g_Ball.ballHitGrroundDistanceFromHome = g_Ball.ballDistanceFromHome;

    if (g_Ball.always0_fairFoulRelated == 1 || g_Ball.bobbleLocation_1fair_2foul == 2) {
        foulBall();
    } else if (g_Ball.always0_fairFoulRelated == 2 || g_Ball.bobbleLocation_1fair_2foul == 1) {
        g_Ball.ballInitialHitDoneInd = 1;
        g_Ball.AtBat_ContactResult = BALL_RESULT_TYPE_LANDED;
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD) {
            QueueTextToDisplay(4, 1);
        }
    } else if (foul_checkIfFoul(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z)) {
        if (foul_ifBallConsideredPastTheBases(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z) ||
            (g_Ball.AtBat_Contact_BallPos.x > 0.0f ? g_Ball.AtBat_Contact_BallPos.z - g_Ball.AtBat_Contact_BallPos.x
                                                    : g_Ball.AtBat_Contact_BallPos.z + g_Ball.AtBat_Contact_BallPos.x) <
                lbl_3_rodata_5E4 ||
            g_Ball.ballVelocity < lbl_3_rodata_5D4) {
            foulBall();
        }
    } else if (foul_ifBallConsideredPastTheBases(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z)) {
        g_Ball.ballInitialHitDoneInd = 1;
        if (foul_isBallWithin3mFair(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z) &&
            g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD) {
            QueueTextToDisplay(4, 1);
        }
    }

    makeSoundOfBallBouncing();
}

// .text:0x00009B74 size:0x16C mapped:0x80648C08
void fn_3_9B74(void) {
    f32 offset;
    f32 x;

    x = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
    if (x > 0.0f) {
        offset = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z - x;
    } else {
        offset = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z + x;
    }
    if (offset < -20.0f) {
        g_Ball.howFoulTheBallWillBe = 3;
    } else if (offset < -10.0f) {
        g_Ball.howFoulTheBallWillBe = 2;
    } else if (offset < -5.0f) {
        g_Ball.howFoulTheBallWillBe = 1;
    } else {
        g_Ball.howFoulTheBallWillBe = 0;
    }

    if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > 110.0f) {
        x = g_Ball.ballWillHitBallPos.x;
        if (x < 0.0f) {
            x = -x;
        }
        offset = g_Ball.ballWillHitBallPos.z - x;
        if (offset < -20.0f) {
            g_Ball.howFoulTheBallWillBe = 3;
        } else if (offset < -10.0f) {
            g_Ball.howFoulTheBallWillBe = 2;
        } else if (offset < -5.0f) {
            g_Ball.howFoulTheBallWillBe = 1;
        } else {
            g_Ball.howFoulTheBallWillBe = 0;
        }
    }

    if (g_Ball.deadBallReason == 1) {
        g_Ball.howFoulTheBallWillBe = 0;
    }
}

// .text:0x00009CE0 size:0x138 mapped:0x80648D74
f32 ballDistCalculator(f32 x, f32 z) {
    f32 dx = x - g_Ball.AtBat_Contact_BallPos.x;
    f32 dz = z - g_Ball.AtBat_Contact_BallPos.z;
    f32 dot = g_Ball.ballVelocityPercent.x * dx + g_Ball.ballVelocityPercent.z * dz;
    f32 distSq = dx * dx + dz * dz - dot * dot;
    if (distSq < 0.0f) {
        return 0.0f;
    }
    return dolsqrtf2(distSq);
}

// .text:0x00009E18 size:0x6C mapped:0x80648EAC
void fn_3_9E18(void) {
    if (g_Ball.deadBallReason != 4) {
        g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
        g_Ball.deadBallReason = 4;
        if (g_RunningLogic._00 != 0) {
            QueueTextToDisplay(0x14, 0);
        }
    }
}

// .text:0x00009E84 size:0x120 mapped:0x80648F18
void relatedToGroundRuleDouble(void) {
    if (g_Ball.deadBallReason == 0) {
        if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != 0) {
            if (g_Ball.deadBallReason != 4) {
                g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                g_Ball.deadBallReason = 4;
                if (g_RunningLogic._00 != 0) {
                    QueueTextToDisplay(0x14, 0);
                }
            }
        } else if (g_Ball.numFieldersWhoHandledBallDuringPlay != 0 && g_Ball.numberOfThrowsDuringPlay != 0) {
            if (g_Ball.deadBallReason != 4) {
                g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                g_Ball.deadBallReason = 4;
                if (g_RunningLogic._00 != 0) {
                    QueueTextToDisplay(0x14, 0);
                }
            }
        } else {
            g_Ball.deadBallReason = 3;
            g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
            g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
            g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
            QueueTextToDisplay(7, 0);
        }
    }
}

// .text:0x00009FA4 size:0x7C mapped:0x80649038
void fn_3_9FA4(void) {
    if (g_Ball.deadBallReason == 0) {
        g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
        g_Ball.deadBallReason = 1;
        g_Ball.matchFramesAndBallAngle.ballOverWallFrames = 1;
        g_Ball.AtBat_ContactResult = 1;
        g_Ball.ballInitialHitDoneInd = 1;
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD) {
            QueueTextToDisplay(0xF, 0);
        }
    }
}

// .text:0x0000A020 size:0xD0 mapped:0x806490B4
void fn_3_A020(void) {
    if (g_Ball.deadBallReason == 0) {
        BOOL runnerWasOut;

        g_Ball.deadBallReason = 2;
        g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
        g_Ball.AtBat_ContactResult = BALL_RESULT_TYPE_FOUL;
        g_Ball.ballInitialHitDoneInd = 1;
        runnerWasOut = 0;
        if (g_FieldingLogic.hasProcessedFoulBall != 1) {
            g_FieldingLogic.hasProcessedFoulBall = 1;
            g_Strikes.strikes++;
            if (g_Strikes.strikes >= 3) {
                if (g_Ball.maybeBuntInd != 0) {
                    g_Ball.maybebuntOn2Strikes = 1;
                    runnerOut(0);
                    runnerWasOut = 1;
                } else {
                    g_Strikes.strikes = 2;
                }
            }
            if (runnerWasOut == 0) {
                QueueTextToDisplay(3, 0);
            }
        }
    }
}

// .text:0x0000A0F0 size:0xA8 mapped:0x80649184
void foulBall(void) {
    BOOL runnerWasOut;

    g_Ball.AtBat_ContactResult = BALL_RESULT_TYPE_FOUL;
    g_Ball.ballInitialHitDoneInd = 1;
    runnerWasOut = 0;
    if (g_FieldingLogic.hasProcessedFoulBall != 1) {
        g_FieldingLogic.hasProcessedFoulBall = 1;
        g_Strikes.strikes++;
        if (g_Strikes.strikes >= 3) {
            if (g_Ball.maybeBuntInd != 0) {
                g_Ball.maybebuntOn2Strikes = 1;
                runnerOut(0);
                runnerWasOut = 1;
            } else {
                g_Strikes.strikes = 2;
            }
        }
        if (runnerWasOut == 0) {
            QueueTextToDisplay(3, 0);
        }
    }
}

// .text:0x0000A198 size:0x6A4 mapped:0x8064922C
void warioWaluStarHit(void) {
    int i;

    if (g_Ball.framesUntilBallHitsGround <= g_Ball.matchFramesAndBallAngle.garlicHitFramesUntilHitGroundForSplit) {
        if (g_Ball.framesUntilBallHitsGround == g_Ball.matchFramesAndBallAngle.garlicHitFramesUntilHitGroundForSplit) {
            f32 speed;
            f32 angle;
            f32 x1;
            f32 z1;
            f32 x2;
            f32 z2;

            for (i = 9; i >= 0; i--) {
                g_Ball.warioStarHitCoords[i + 3].x = g_Ball.pastCoordinates[i].x;
                g_Ball.warioStarHitCoords[i + 3].y = g_Ball.pastCoordinates[i].y;
                g_Ball.warioStarHitCoords[i + 3].z = g_Ball.pastCoordinates[i].z;
            }

            g_Ball.physicsSubstruct.acceleration.x = 0.0f;
            g_Ball.physicsSubstruct.acceleration.y = 0.0f;
            g_Ball.physicsSubstruct.acceleration.z = 0.0f;
            g_Ball.warioStarHitCoords[0].x = g_Ball.AtBat_Contact_BallPos.x;
            g_Ball.warioStarHitCoords[0].y = g_Ball.AtBat_Contact_BallPos.y;
            g_Ball.warioStarHitCoords[0].z = g_Ball.AtBat_Contact_BallPos.z;
            g_Ball.warioStarHitCoords[1].x = g_Ball.AtBat_Contact_BallPos.x;
            g_Ball.warioStarHitCoords[1].y = g_Ball.AtBat_Contact_BallPos.y;
            g_Ball.warioStarHitCoords[1].z = g_Ball.AtBat_Contact_BallPos.z;
            g_Ball.warioStarHitCoords[2].x = g_Ball.AtBat_Contact_BallPos.x;
            g_Ball.warioStarHitCoords[2].y = g_Ball.AtBat_Contact_BallPos.y;
            g_Ball.warioStarHitCoords[2].z = g_Ball.AtBat_Contact_BallPos.z;

            angle = game_atan2(g_Ball.physicsSubstruct.velocity.x, g_Ball.physicsSubstruct.velocity.z);
            speed = VEC_LENGTH_XZ(&g_Ball.physicsSubstruct.velocity);

            getComponentsFromRad(angle + RandomF32_Game_Range(g_hitFloats.garlicSpreadLower, g_hitFloats.garlicSpreadUpper),
                                 &x1, &z1);
            getComponentsFromRad(angle - RandomF32_Game_Range(g_hitFloats.garlicSpreadLower, g_hitFloats.garlicSpreadUpper),
                                 &x2, &z2);
            x1 *= speed;
            z1 *= speed;
            x2 *= speed;
            z2 *= speed;

            if (g_Ball.warioWaluStarHitDirection != 0) {
                g_Ball.warioStarHitCoords[13].x = x1;
                g_Ball.warioStarHitCoords[13].y = g_Ball.physicsSubstruct.velocity.y;
                g_Ball.warioStarHitCoords[13].z = z1;
                g_Ball.warioStarHitCoords[14].x = x2;
                g_Ball.warioStarHitCoords[14].y = g_Ball.physicsSubstruct.velocity.y;
                g_Ball.warioStarHitCoords[14].z = z2;
            } else {
                g_Ball.warioStarHitCoords[13].x = x2;
                g_Ball.warioStarHitCoords[13].y = g_Ball.physicsSubstruct.velocity.y;
                g_Ball.warioStarHitCoords[13].z = z2;
                g_Ball.warioStarHitCoords[14].x = x1;
                g_Ball.warioStarHitCoords[14].y = g_Ball.physicsSubstruct.velocity.y;
                g_Ball.warioStarHitCoords[14].z = z1;
            }
            g_Ball.matchFramesAndBallAngle.garlicHitFramesSinceSplit = 0;
        } else {
            f32 drag;

            g_Ball.warioStarHitCoords[0].x = g_Ball.AtBat_Contact_BallPos.x;
            g_Ball.warioStarHitCoords[0].y = g_Ball.AtBat_Contact_BallPos.y;
            g_Ball.warioStarHitCoords[0].z = g_Ball.AtBat_Contact_BallPos.z;

            if (g_Ball.matchFramesAndBallAngle.garlicHitFramesSinceSplit == 3) {
                g_AiLogic.warioStarRelated[0] = RandomInt_Game(2);
                g_FieldingLogic.knockoutFinished = 1;
            }

            drag = 1.0f - (f32)g_Ball.airResistance / 10000.0f;

            for (i = 0; i < 2; i++) {
                g_Ball.warioStarHitCoords[13 + i].y -= g_Ball.physicsSubstruct.gravity;
                g_Ball.warioStarHitCoords[13 + i].x *= drag;
                g_Ball.warioStarHitCoords[13 + i].y *= drag;
                g_Ball.warioStarHitCoords[13 + i].z *= drag;
                g_Ball.warioStarHitCoords[1 + i].x += g_Ball.warioStarHitCoords[13 + i].x;
                g_Ball.warioStarHitCoords[1 + i].y += g_Ball.warioStarHitCoords[13 + i].y;
                g_Ball.warioStarHitCoords[1 + i].z += g_Ball.warioStarHitCoords[13 + i].z;
            }

            g_Ball.AtBat_Contact_BallPos.x = g_Ball.warioStarHitCoords[1].x;
            g_Ball.AtBat_Contact_BallPos.y = g_Ball.warioStarHitCoords[1].y;
            g_Ball.AtBat_Contact_BallPos.z = g_Ball.warioStarHitCoords[1].z;

            if (g_Ball.warioStarHitCoords[1].y < 2.0f && g_Ball.framesUntilBallHitsGround < 30) {
                int nearest;
                f32 minDist = 999.9f;

                for (i = 0, nearest = -1; i < 9; i++) {
                    f32 dx = g_Ball.warioStarHitCoords[2].x - g_Fielders[i].pos.x;
                    f32 dz = g_Ball.warioStarHitCoords[2].z - g_Fielders[i].pos.z;
                    f32 sqx = dx * dx;
                    f32 sqz = dz * dz;
                    f32 dist = dolsqrtf2(sqx + sqz);

                    if (dist < minDist) {
                        nearest = i;
                        minDist = dist;
                    }
                }

                if (minDist < fielderHitboxesForGarlicKnockout[g_Fielders[nearest].Weight]) {
                    int knockAngle = calculateAngleFromCoordinates(
                        g_Fielders[nearest].pos.x - g_Ball.warioStarHitCoords[2].x,
                        g_Fielders[nearest].pos.z - g_Ball.warioStarHitCoords[2].z);

                    processFielderKnockout(nearest, knockAngle);
                    g_Ball.currentStarSwing = 0;
                    g_Ball.warioWaluGarlicIsActive = 0;
                    return;
                }
            }
        }

        if (g_Ball.matchFramesAndBallAngle.garlicHitFramesSinceSplit < 0x7FFE) {
            g_Ball.matchFramesAndBallAngle.garlicHitFramesSinceSplit++;
        } else {
            g_Ball.matchFramesAndBallAngle.garlicHitFramesSinceSplit = 0x7FFF;
        }

        if (g_Ball.warioWaluGarlicIsActive == 0) {
            playSoundEffect(0x1B3);
        }
        g_Ball.warioWaluGarlicIsActive = 1;
    }
}

// .text:0x0000A83C size:0x134 mapped:0x806498D0
void updatePastHitBallCoords(void) {
    int i;

    for (i = 59; i > 0; i--) {
        g_Ball.pastCoordinates[i].x = g_Ball.pastCoordinates[i - 1].x;
        g_Ball.pastCoordinates[i].y = g_Ball.pastCoordinates[i - 1].y;
        g_Ball.pastCoordinates[i].z = g_Ball.pastCoordinates[i - 1].z;
    }

    if (g_Ball.catchAnimationTotalFrames != 0 || g_Ball.fielderActionOccuring != 0) {
        g_Ball.pastCoordinates[0].x = g_Ball.fielderActionCatchCoords.x;
        g_Ball.pastCoordinates[0].y = g_Ball.fielderActionCatchCoords.y;
        g_Ball.pastCoordinates[0].z = g_Ball.fielderActionCatchCoords.z;
    } else {
        g_Ball.pastCoordinates[0].x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.pastCoordinates[0].y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.pastCoordinates[0].z = g_Ball.AtBat_Contact_BallPos.z;
    }

    if (g_Ball.currentStarSwing != CAPTAIN_STAR_TYPE_WARIO && g_Ball.currentStarSwing != CAPTAIN_STAR_TYPE_WALUIGI) {
        return;
    }

    for (i = 9; i >= 1; i--) {
        g_Ball.warioStarHitCoords[i + 3].x = g_Ball.warioStarHitCoords[i + 2].x;
        g_Ball.warioStarHitCoords[i + 3].y = g_Ball.warioStarHitCoords[i + 2].y;
        g_Ball.warioStarHitCoords[i + 3].z = g_Ball.warioStarHitCoords[i + 2].z;
    }

    g_Ball.warioStarHitCoords[3].x = g_Ball.warioStarHitCoords[0].x;
    g_Ball.warioStarHitCoords[3].y = g_Ball.warioStarHitCoords[0].y;
    g_Ball.warioStarHitCoords[3].z = g_Ball.warioStarHitCoords[0].z;
}

// .text:0x0000A970 size:0xAD0 mapped:0x80649A04
void liveBallHitPhysics(int mode) {
    if (mode != 1) {
        if (g_Ball.framesSinceHit < 0x7FFE) {
            g_Ball.framesSinceHit++;
        } else {
            g_Ball.framesSinceHit = 0x7FFF;
        }

        if (g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_IN_AIR) {
            if (g_Ball.framesSinceBallHitGroundOrWasCaught == -1) {
                g_Ball.framesSinceBallHitGroundOrWasCaught = 1;
            } else if (g_Ball.framesSinceBallHitGroundOrWasCaught < 0x7FFE) {
                g_Ball.framesSinceBallHitGroundOrWasCaught++;
            } else {
                g_Ball.framesSinceBallHitGroundOrWasCaught = 0x7FFF;
            }
        }

        if (g_Ball.framesSinceLastBounce >= 0) {
            if (g_Ball.framesSinceLastBounce < 0x7FFE) {
                g_Ball.framesSinceLastBounce++;
            } else {
                g_Ball.framesSinceLastBounce = 0x7FFF;
            }
        }

        if (g_Ball.ballBounceState != 0) {
            g_Ball.ballBounceState--;
        }

        if (g_Ball.ballState == BALL_STATE_THROWN) {
            if (g_Ball.framesSinceThrowStarted < 0x7FFE) {
                g_Ball.framesSinceThrowStarted++;
            } else {
                g_Ball.framesSinceThrowStarted = 0x7FFF;
            }
            if (g_Ball.framesSinceThrowStarted == 2) {
                estimateTimeForThrowToReachTarget();
            } else {
                g_Ball.framesUntilThrowReachesDest--;
                if (g_Ball.framesUntilThrowReachesDest < -1) {
                    g_Ball.framesUntilThrowReachesDest = -1;
                }
            }
        }
    }

    updatePastHitBallCoords();

    if (g_Ball.pauseBallMovementWhenInPlant != 0) {
        if (g_Ball.matchFramesAndBallAngle.framesInsidePlant < 0x7FFE) {
            g_Ball.matchFramesAndBallAngle.framesInsidePlant++;
        } else {
            g_Ball.matchFramesAndBallAngle.framesInsidePlant = 0x7FFF;
        }
        return;
    }

    if (g_Ball.catchAnimationTotalFrames != 0) {
        return;
    }

    if (g_Ball.warioWaluGarlicIsActive != 0) {
        g_Ball.AtBat_Contact_BallPos.x = g_Ball.warioStarHitCoords[0].x;
        g_Ball.AtBat_Contact_BallPos.y = g_Ball.warioStarHitCoords[0].y;
        g_Ball.AtBat_Contact_BallPos.z = g_Ball.warioStarHitCoords[0].z;
    }

    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY && g_Ball.bODQualifyingHitInd != 0) {
        g_Ball.physicsSubstruct.velocity.y -= lbl_3_data_21438._00;
    } else {
        g_Ball.physicsSubstruct.velocity.y -= g_Ball.physicsSubstruct.gravity;
        adjustVeloByAirResistance();
    }

    g_Ball.physicsSubstruct.velocity.x += g_Ball.physicsSubstruct.acceleration.x;
    g_Ball.physicsSubstruct.velocity.y += g_Ball.physicsSubstruct.acceleration.y;
    g_Ball.physicsSubstruct.velocity.z += g_Ball.physicsSubstruct.acceleration.z;

    if (g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_DK || g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_DIDDY) {
        if (g_Ball.framesSinceHit > g_Ball.matchFramesAndBallAngle.bananaHitStartFrame &&
            g_Ball.framesSinceHit < g_Ball.matchFramesAndBallAngle.bananaHitEndFrame) {
            f32* velX = &g_Ball.physicsSubstruct.velocity.x;
            f32* velZ = &g_Ball.physicsSubstruct.velocity.z;
            f32 speed = dolsqrtf2(*velX * *velX + *velZ * *velZ);
            f32 angle = game_atan2(*velX, *velZ);

            if (g_Ball.directionOfBananaHit != 0) {
                angle = angle + g_hitFloats.DKStarAngleDelta;
            } else {
                angle = angle - g_hitFloats.DKStarAngleDelta;
            }
            getComponentsFromRad(angle, velX, velZ);
            *velX *= speed;
            *velZ *= speed;
        }
    }

    g_Ball.AtBat_Contact_BallPos.x += g_Ball.physicsSubstruct.velocity.x;
    g_Ball.AtBat_Contact_BallPos.y += g_Ball.physicsSubstruct.velocity.y;
    g_Ball.AtBat_Contact_BallPos.z += g_Ball.physicsSubstruct.velocity.z;

    if (g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_WARIO || g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_WALUIGI) {
        warioWaluStarHit();
    }

    ballCollisionLogic();

    if (g_d_GameSettings.StadiumID == STADIUM_ID_MARIO_STADIUM ||
        (u8)(g_d_GameSettings.StadiumID - STADIUM_ID_WARIO_PALACE) <= STADIUM_ID_PEACH_GARDEN - STADIUM_ID_WARIO_PALACE ||
        g_d_GameSettings.StadiumID == STADIUM_ID_DK_JUNGLE) {
        if (g_Ball.AtBat_Contact_BallPos.y < g_Ball.groundYForBounces) {
            g_Ball.AtBat_Contact_BallPos.y = g_Ball.groundYForBounces;
            if (g_Ball.physicsSubstruct.velocity.y < 0.0f) {
                g_Ball.physicsSubstruct.velocity.y *= -1.0f;
            }
        }
    }

    g_Ball.ballDistanceFromHome = VEC_LENGTH_XZ(&g_Ball.AtBat_Contact_BallPos);

    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY) {
        return;
    }

    estimateAndSetFutureCoords(1);

    if (g_Ball.currentStarSwing != CAPTAIN_STAR_TYPE_NONE) {
        BOOL ballHandled = FALSE;

        if (g_Ball.someCollisionInd != 0) {
            ballHandled = TRUE;
        } else if (g_Ball.numFieldersWhoHandledBallDuringPlay != 0) {
            ballHandled = TRUE;
        }

        if (g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_PEACH || g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_DAISY) {
            if (ballHandled || g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_IN_AIR) {
                g_Ball.currentStarSwing = CAPTAIN_STAR_TYPE_NONE;
                g_Batter.invisibleBallForPeachStarHit = 0;
                if (peachDaisyStarSwingRelated() != 0) {
                    peachDaisyStarSwingRelated2();
                }
            } else if (g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_DAISY) {
                int appearFrame = peachDaisyStarSwingRelated();

                if (g_Ball.framesSinceHit >= appearFrame) {
                    g_Ball.currentStarSwing = CAPTAIN_STAR_TYPE_NONE;
                    g_Batter.invisibleBallForPeachStarHit = 0;
                } else if (g_Ball.framesSinceHit >=
                           (&g_hitShorts.FrameWhenPeachHitAppearsAgain)[g_Ball.currentStarSwing -
                                                                         CAPTAIN_STAR_TYPE_PEACH]) {
                    g_Batter.invisibleBallForPeachStarHit = 1;
                }
            } else {
                if (g_Ball.framesSinceHit >= (&g_hitShorts._16)[g_Ball.currentStarSwing - CAPTAIN_STAR_TYPE_PEACH]) {
                    g_Ball.currentStarSwing = CAPTAIN_STAR_TYPE_NONE;
                    g_Batter.invisibleBallForPeachStarHit = 0;
                } else if (g_Ball.framesSinceHit >=
                           (&g_hitShorts.FrameWhenPeachHitAppearsAgain)[g_Ball.currentStarSwing -
                                                                         CAPTAIN_STAR_TYPE_PEACH]) {
                    g_Batter.invisibleBallForPeachStarHit = 1;
                }
            }
            if (g_Batter.invisibleBallForPeachStarHit == 0) {
                g_Ball.autoFielderAvoidDropSpotForPeachesStarHit = 0;
            }
        } else if (ballHandled) {
            g_Ball.currentStarSwing = CAPTAIN_STAR_TYPE_NONE;
        } else if (g_Ball.ballIsRollingIndicator != 0) {
            g_Ball.currentStarSwing = CAPTAIN_STAR_TYPE_NONE;
        } else if (g_Ball.framesSinceLastBounce == 0) {
            if (g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_DK || g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_DIDDY) {
                g_Ball.currentStarSwing = CAPTAIN_STAR_TYPE_NONE;
            } else if (g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_BOWSER ||
                       g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_BOWSERJR) {
                g_Ball.currentStarSwing = CAPTAIN_STAR_TYPE_NONE;
            } else if (g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_YOSHI ||
                       g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_BIRDO) {
                if (g_Ball.framesOnGroundUntilPickedUp >= g_hitShorts.NEggBounces) {
                    g_Ball.currentStarSwing = CAPTAIN_STAR_TYPE_NONE;
                }
            } else if (g_Ball.framesOnGroundUntilPickedUp >= g_hitShorts.framesOnGroundBeforeCheckingMinStarVelo) {
                if (VEC_LENGTH_XZ(&g_Ball.physicsSubstruct.velocity) < g_hitFloats.minStarHitVelo) {
                    g_Ball.currentStarSwing = CAPTAIN_STAR_TYPE_NONE;
                }
            }
        }
    }
}

// .text:0x0000B440 size:0x500 mapped:0x8064A4D4
void estimateTimeForThrowToReachTarget(void) {
    f32 dx;
    f32 dz;
    int frame;

    g_Ball.throwTimeEstimatesCompleteInd = 1;
    if (g_Ball.framesUntilThrowReachesDest < 15) {
        return;
    }

    dx = ABS(g_Ball.throwTarget.x - g_Ball.AtBat_Contact_BallPos.x);
    dz = ABS(g_Ball.throwTarget.z - g_Ball.AtBat_Contact_BallPos.z);

    if (dx > dz) {
        if (g_Ball.throwTarget.x < g_Ball.AtBat_Contact_BallPos.x) {
            for (frame = 10; frame < 360; frame += 10) {
                if (g_Ball.throwTarget.x >= g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.x) {
                    frame -= 10;
                    break;
                }
            }
            for (; frame < 360; frame++) {
                if (g_Ball.throwTarget.x >= g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.x) {
                    break;
                }
            }
        } else {
            for (frame = 10; frame < 360; frame += 10) {
                if (g_Ball.throwTarget.x <= g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.x) {
                    frame -= 10;
                    break;
                }
            }
            for (; frame < 360; frame++) {
                if (g_Ball.throwTarget.x <= g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.x) {
                    break;
                }
            }
        }
    } else {
        if (g_Ball.throwTarget.z < g_Ball.AtBat_Contact_BallPos.z) {
            for (frame = 10; frame < 360; frame += 10) {
                if (g_Ball.throwTarget.z >= g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.z) {
                    frame -= 10;
                    break;
                }
            }
            for (; frame < 360; frame++) {
                if (g_Ball.throwTarget.z >= g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.z) {
                    break;
                }
            }
        } else {
            for (frame = 10; frame < 360; frame += 10) {
                if (g_Ball.throwTarget.z <= g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.z) {
                    frame -= 10;
                    break;
                }
            }
            for (; frame < 360; frame++) {
                if (g_Ball.throwTarget.z <= g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.z) {
                    break;
                }
            }
        }
    }

    g_Ball.framesUntilThrowReachesDest = frame;
}

// .text:0x0000B940 size:0x27C mapped:0x8064A9D4
void fielding_setHeldBallOffset(void) {
    InMemFielder* fielder;
    int character;
    VecXYZ throwReleaseOffset;
    int fielderIdx = g_Ball.fielderWBallIndex;
    BOOL isMagikoopa = FALSE;

    character = fielderIdx;
    if (fielderIdx >= 0) {
        fielder = &g_Fielders[fielderIdx];

        if (g_d_GameSettings.minigamesEnabled) {
            character = g_Minigame.minigameControlStruct[0]
                            .characterIndex[(s8)g_Minigame.minigameControlStruct[1].aIStrength[fielderIdx]];
        }

        if (fielder->CharID == CHAR_ID_BIRDO && g_FieldingLogic.birdoFarThrowInd_forAnimation != 0) {
            getAnimRelatedCoordinates(character, 0x42, &throwReleaseOffset);
        } else if (fielder->CharID == CHAR_ID_PETEY) {
            getAnimRelatedCoordinates(character, 9, &throwReleaseOffset);
        } else if (characterStaticIndexes[fielder->CharID * 6 + 1] == CHAR_ID_MAGIKOOPA_BLUE) {
            if (fielder->throwingHandedness == 0) {
                getAnimRelatedCoordinates(character, 0x4F, &throwReleaseOffset);
            } else {
                getAnimRelatedCoordinates(character, 0x4E, &throwReleaseOffset);
            }
            isMagikoopa = TRUE;
        } else if (fielder->throwingHandedness == 0) {
            getAnimRelatedCoordinates(character, 0x19, &throwReleaseOffset);
        } else {
            getAnimRelatedCoordinates(character, 0x13, &throwReleaseOffset);
        }

        if (isMagikoopa) {
            if (g_Ball.timeSinceBallPickedUp <= 1) {
                f32 x = throwReleaseOffset.x - fielder->pos.x;
                f32 y = -throwReleaseOffset.y - fielder->pos.y;
                f32 z = throwReleaseOffset.z - fielder->pos.z;

                g_Ball.offsetWhilePickedUpHistory[0].x = x;
                g_Ball.offsetWhilePickedUpHistory[0].y = y;
                g_Ball.offsetWhilePickedUpHistory[0].z = z;
                g_Ball.offsetWhilePickedUpHistory[1].x = x;
                g_Ball.offsetWhilePickedUpHistory[1].y = y;
                g_Ball.offsetWhilePickedUpHistory[1].z = z;
                g_Ball.offsetWhilePickedUpHistory[2].x = x;
                g_Ball.offsetWhilePickedUpHistory[2].y = y;
                g_Ball.offsetWhilePickedUpHistory[2].z = z;
                g_Ball.offsetWhilePickedUpHistory[3].x = x;
                g_Ball.offsetWhilePickedUpHistory[3].y = y;
                g_Ball.offsetWhilePickedUpHistory[3].z = z;
            } else {
                int i;
                for (i = 3; i >= 2; i--) {
                    g_Ball.offsetWhilePickedUpHistory[i].x = g_Ball.offsetWhilePickedUpHistory[i - 1].x;
                    g_Ball.offsetWhilePickedUpHistory[i].y = g_Ball.offsetWhilePickedUpHistory[i - 1].y;
                    g_Ball.offsetWhilePickedUpHistory[i].z = g_Ball.offsetWhilePickedUpHistory[i - 1].z;
                }
                g_Ball.offsetWhilePickedUpHistory[1].x = g_Ball.offsetWhilePickedUpHistory[0].x;
                g_Ball.offsetWhilePickedUpHistory[1].y = g_Ball.offsetWhilePickedUpHistory[0].y;
                g_Ball.offsetWhilePickedUpHistory[1].z = g_Ball.offsetWhilePickedUpHistory[0].z;
                g_Ball.offsetWhilePickedUpHistory[0].x = throwReleaseOffset.x - fielder->pos.x;
                g_Ball.offsetWhilePickedUpHistory[0].y = -throwReleaseOffset.y - fielder->pos.y;
                g_Ball.offsetWhilePickedUpHistory[0].z = throwReleaseOffset.z - fielder->pos.z;
            }
        } else {
            g_Ball.offsetWhilePickedUpHistory[0].x = throwReleaseOffset.x - fielder->pos.x;
            g_Ball.offsetWhilePickedUpHistory[0].y = -throwReleaseOffset.y - fielder->pos.y;
            g_Ball.offsetWhilePickedUpHistory[0].z = throwReleaseOffset.z - fielder->pos.z;
        }
    }
}

// .text:0x0000BBBC size:0x98 mapped:0x8064AC50
int futureFrameForClosestBall(f32 playerX, f32 playerZ, f32* outPos, int maxFrame, int step) {
    f32 bestSqDist = reallyLargeConst;
    int frame;
    int bestFrame;

    bestFrame = -1;
    frame = 0;
    while (frame < maxFrame) {
        f32 dx = g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.x - playerX;
        f32 dz = g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.z - playerZ;
        f32 sqDist = dx * dx + dz * dz;
        if (sqDist < bestSqDist) {
            bestSqDist = sqDist;
            bestFrame = frame;
            frame += step;
        } else {
            break;
        }
    }

    if (bestFrame < 0) {
        return -1;
    }
    outPos[0] = g_Ball.physicsSubstruct.futureCoordsAndDist[bestFrame].pos.x;
    outPos[1] = g_Ball.physicsSubstruct.futureCoordsAndDist[bestFrame].pos.y;
    outPos[2] = g_Ball.physicsSubstruct.futureCoordsAndDist[bestFrame].pos.z;
    return bestFrame;
}

// .text:0x0000BC54 size:0x124 mapped:0x8064ACE8
void fn_3_BC54(void) {
    BOOL runnerWasOut;

    if (foul_ifBallConsideredPastTheBases(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z) == 0) {
        f32 offset;

        if (g_Ball.AtBat_Contact_BallPos.x > lbl_3_rodata_590) {
            offset = g_Ball.AtBat_Contact_BallPos.z - g_Ball.AtBat_Contact_BallPos.x;
        } else {
            offset = g_Ball.AtBat_Contact_BallPos.z + g_Ball.AtBat_Contact_BallPos.x;
        }
        if (!(offset < lbl_3_rodata_5E4) && !(g_Ball.ballVelocity < lbl_3_rodata_5D4)) {
            return;
        }
    }

    g_Ball.AtBat_ContactResult = BALL_RESULT_TYPE_FOUL;
    g_Ball.ballInitialHitDoneInd = 1;
    runnerWasOut = 0;
    if (g_FieldingLogic.hasProcessedFoulBall != 1) {
        g_FieldingLogic.hasProcessedFoulBall = 1;
        g_Strikes.strikes++;
        if (g_Strikes.strikes >= 3) {
            if (g_Ball.maybeBuntInd != 0) {
                g_Ball.maybebuntOn2Strikes = 1;
                runnerOut(0);
                runnerWasOut = 1;
            } else {
                g_Strikes.strikes = 2;
            }
        }
        if (runnerWasOut == 0) {
            QueueTextToDisplay(3, 0);
        }
    }
}

// .text:0x0000BD78 size:0x2BC mapped:0x8064AE0C
void setHitClassification3(void) {
    int foulSide = -1;

    if (g_Ball.Hit_HorizontalAngle > 0xC00) {
        foulSide = 0;
    } else if (g_Ball.Hit_HorizontalAngle < 0x400 && g_Ball.Hit_VerticalAngle > 0x400 &&
               g_Ball.Hit_VerticalAngle < 0xC00) {
        foulSide = 0;
    } else if (g_Ball.Hit_HorizontalAngle > 0x800) {
        foulSide = 1;
    } else if (g_Ball.Hit_VerticalAngle > 0x400 && g_Ball.Hit_VerticalAngle < 0xC00) {
        foulSide = 1;
    } else if (g_Ball.Hit_HorizontalAngle < 0x1B0) {
        foulSide = 2;
    } else if (g_Ball.Hit_HorizontalAngle > 0x650) {
        foulSide = 3;
    }

    if (foulSide == 0 || foulSide == 2) {
        g_Ball.hitClassification3 = 7;
    } else if (foulSide == 1 || foulSide == 3) {
        g_Ball.hitClassification3 = 8;
    } else {
        f32 dx = g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.x;
        f32 dz = g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.z;
        f32 sqx = dx * dx;
        f32 sqz = dz * dz;
        f32 dist = dolsqrtf2(sqx + sqz);

        if (dist < lbl_3_rodata_60C) {
            g_Ball.hitClassification3 = 0;
        } else if (dist < lbl_3_rodata_610) {
            g_Ball.hitClassification3 = 1;
        } else if (dist < lbl_3_rodata_594) {
            if (g_Ball.Hit_HorizontalAngle < 0x340) {
                g_Ball.hitClassification3 = 2;
            } else if (g_Ball.Hit_HorizontalAngle >= 0x4C0) {
                g_Ball.hitClassification3 = 4;
            } else {
                g_Ball.hitClassification3 = 3;
            }
        } else if (g_Ball.hitClassification2 <= 4) {
            g_Ball.hitClassification3 = 5;
        } else {
            g_Ball.hitClassification3 = 6;
        }
    }
}

// .text:0x0000C034 size:0x9C0 mapped:0x8064B0C8
void classifyHitTrajectoryOrHitAnimRelated(void) {
    int zone;
    u8 landingSpotVeryFoulInd = 0;
    int landingAngle;
    int horizDelta;
    f32 angleOffset;
    int i;

    g_Ball.hitClassification1 = 1;
    if (g_Ball.Hit_HorizontalAngle < 0x1B0 || g_Ball.Hit_HorizontalAngle > 0x650 ||
        (g_Ball.Hit_VerticalAngle > 0x400 && g_Ball.Hit_VerticalAngle < 0xC00)) {
        if (g_Ball.Hit_VerticalAngle > 0x800 || g_Ball.Hit_VerticalAngle < 0) {
            g_Ball.hitClassification1 = 3;
        } else if (g_Ball.Hit_VerticalAngle > 0x154) {
            g_Ball.hitClassification1 = 5;
        } else {
            g_Ball.hitClassification1 = 4;
        }
    } else {
        if (g_Ball.Hit_VerticalAngle > 0x800 || g_Ball.Hit_VerticalAngle < 0) {
            g_Ball.hitClassification1 = 0;
        } else if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome < 18.0f && g_Ball.Hit_VerticalAngle < 0x64) {
            g_Ball.hitClassification1 = 0;
        } else if (g_Ball.Hit_VerticalAngle > 0x154) {
            g_Ball.hitClassification1 = 2;
        }
    }

    zone = setZoneAwayFromHome(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x,
                               g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);
    landingAngle = calculateAngleFromCoordinates(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x,
                                                 g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);
    if (landingAngle < 0x1A0 || landingAngle > 0x660) {
        landingSpotVeryFoulInd = 1;
    }

    if ((g_Ball.Hit_HorizontalAngle < 0x1A0 || g_Ball.Hit_HorizontalAngle > 0x660) && landingSpotVeryFoulInd) {
        if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > 60.0f) {
            g_Ball.hitClassification2 = 8;
        } else {
            g_Ball.hitClassification2 = 7;
        }
    } else if (g_Ball.Hit_VerticalAngle > 0x400 && g_Ball.Hit_VerticalAngle < 0xC00) {
        g_Ball.hitClassification2 = 7;
    } else if (g_Ball.hitClassification1 == 0) {
        f32 dx = g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.x;
        f32 dz = g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.z;
        f32 sqx = dx * dx;
        f32 sqz = dz * dz;
        f32 dist60 = dolsqrtf2(sqx + sqz);

        if (g_Ball.Hit_HorizontalPower < 0x46 && dist60 < 14.0f) {
            g_Ball.hitClassification2 = 1;
        } else {
            g_Ball.hitClassification2 = 2;
        }
    } else {
        do {
            if ((u8)zone <= 1) {
                f32 dx = g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.x;
                f32 dz = g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.z;
                f32 sqx = dx * dx;
                f32 sqz = dz * dz;
                f32 dist60 = dolsqrtf2(sqx + sqz);

                if (g_Ball.Hit_HorizontalPower < 0x46 && dist60 < 10.0f &&
                    g_Ball.physicsSubstruct.hitLandingSpotDistFromHome < 18.0f) {
                    g_Ball.hitClassification2 = 1;
                    break;
                }
            }

            if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome < 30.0f && g_Ball.maxYOfHit < 2.0f) {
                g_Ball.hitClassification2 = 2;
            } else if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome < 20.0f && g_Ball.maxYOfHit < 4.0f) {
                g_Ball.hitClassification2 = 2;
            } else if ((u8)zone <= 1 && g_Ball.hangtimeOfHit > 0xB4) {
                g_Ball.hitClassification2 = 4;
            } else if ((u8)zone <= 1) {
                g_Ball.hitClassification2 = 3;
            } else if ((u8)zone == 2 && g_Ball.maxYOfHit < 4.5f) {
                g_Ball.hitClassification2 = 3;
            } else if ((u8)zone <= 2) {
                g_Ball.hitClassification2 = 5;
            } else if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome < 70.0f ||
                       (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome < 80.0f && g_Ball.hangtimeOfHit < 0xB4)) {
                g_Ball.hitClassification2 = 5;
            } else {
                g_Ball.hitClassification2 = 6;
            }
        } while (0);
    }

    setHitClassification3();

    g_Batter.hitTrajectory = HIT_TRAJECTORY_2;
    if (g_Ball.maybeBuntInd != 0) {
        g_Batter.hitTrajectory = HIT_TRAJECTORY_5;
    }

    horizDelta = 0x400 - g_Ball.Hit_HorizontalAngle;
    g_RunningLogic._13 = 0;
    angleOffset = 0.04f * (f32)(horizDelta > 0 ? horizDelta : -horizDelta);

    if (g_Ball.Hit_HorizontalAngle >= 0x260 && g_Ball.Hit_HorizontalAngle < 0x5A0 &&
        g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE) {
        if (135.0f - angleOffset < g_Ball.physicsSubstruct.hitLandingSpotDistFromHome) {
            if (g_Ball.Hit_VerticalAngle >= 0x118) {
                g_Ball.homeRunClassification = 2;
                if (145.0f - angleOffset < g_Ball.physicsSubstruct.hitLandingSpotDistFromHome) {
                    g_Ball.homeRunClassification = 1;
                }
                g_Batter.hitTrajectory = HIT_TRAJECTORY_4;
                g_RunningLogic._13 = 1;
                if (g_Batter.batterHand == BATTING_HAND_RIGHT) {
                    if (g_Ball.Hit_HorizontalAngle < 0x480) {
                        g_Batter.hitTrajectory = HIT_TRAJECTORY_4;
                    }
                } else {
                    if (g_Ball.Hit_HorizontalAngle >= 0x380) {
                        g_Batter.hitTrajectory = HIT_TRAJECTORY_4;
                    }
                }
            }
        } else if (125.0f - angleOffset < g_Ball.physicsSubstruct.hitLandingSpotDistFromHome &&
                   g_Ball.Hit_VerticalAngle >= 0x154) {
            g_Ball.homeRunClassification = 3;
        }
    }

    landingAngle = calculateAngleFromCoordinates(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x,
                                                 g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);

    if (g_Ball.Hit_HorizontalAngle < 0x1E0 || g_Ball.Hit_HorizontalAngle >= 0x620 ||
        (landingAngle < 0x100 && g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > 10.0f) ||
        (landingAngle > 0x700 && g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > 10.0f)) {
        if (!(g_d_GameSettings.StadiumID == STADIUM_ID_WARIO_PALACE && g_Ball.Hit_HorizontalAngle > 0x13C &&
              g_Ball.Hit_HorizontalAngle <= 0x6C4) &&
            g_Ball.currentStarSwing != CAPTAIN_STAR_TYPE_DK && g_Ball.currentStarSwing != CAPTAIN_STAR_TYPE_DIDDY &&
            (u8)(g_Ball.currentStarSwing - CAPTAIN_STAR_TYPE_YOSHI) > 1 &&
            (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z < g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x - 5.0f ||
             g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z < -g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x - 5.0f)) {
            if (g_Ball.maybeBuntInd != 0) {
                if (g_Ball.Hit_HorizontalAngle < 0x1A0 || g_Ball.Hit_HorizontalAngle >= 0x660) {
                    g_Batter.hitTrajectory = HIT_TRAJECTORY_6;
                }
            } else if (landingAngle < 0x1A0 || landingAngle > 0xD80) {
                if (g_Ball.maxYOfHit > 15.0f && landingAngle > 0xD80 && landingAngle < 0xF80) {
                    g_Batter.hitTrajectory = HIT_TRAJECTORY_3;
                } else {
                    g_Batter.hitTrajectory = HIT_TRAJECTORY_3;
                }
            } else if (landingAngle > 0x660 && landingAngle < 0xA80) {
                if (g_Ball.maxYOfHit > 15.0f && landingAngle > 0x880) {
                    g_Batter.hitTrajectory = HIT_TRAJECTORY_3;
                } else {
                    g_Batter.hitTrajectory = HIT_TRAJECTORY_3;
                }
            } else if (landingAngle >= 0xA80 && landingAngle <= 0xD80) {
                g_Batter.hitTrajectory = HIT_TRAJECTORY_3;
            }
        }
    }

    if (g_Ball.physicsSubstruct.futureCoordsAndDist[50].dist > 16.5f && g_Ball.Hit_HorizontalAngle <= 0x430 &&
        g_Ball.Hit_HorizontalAngle >= 0x3D0 && g_Ball.maxYOfHit < 10.0f) {
        for (i = 10; i < 100; i += 5) {
            if (g_Ball.physicsSubstruct.futureCoordsAndDist[i].dist > 16.0f) {
                if (g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.y < 0.2f + g_Fielders[0].hitbox[3]) {
                    g_Ball.lineDriveThroughPitcherInd = 1;
                }
                break;
            }
        }
    }
}

// .text:0x0000C9F4 size:0x434 mapped:0x8064BA88
void updateFrameCountersAndBallPastCoordinatesWhenFielderHoldingBall(void) {
    s32 i;
    s16 fielderIdx;

    if (g_Ball.framesSinceHit < 0x7FFE) {
        g_Ball.framesSinceHit++;
    } else {
        g_Ball.framesSinceHit = 0x7FFF;
    }
    if (g_Ball.timeSinceBallPickedUp < 0x7FFE) {
        g_Ball.timeSinceBallPickedUp++;
    } else {
        g_Ball.timeSinceBallPickedUp = 0x7FFF;
    }
    if (g_Ball.framesSinceBallHitGroundOrWasCaught == -1) {
        g_Ball.framesSinceBallHitGroundOrWasCaught = 1;
    } else if (g_Ball.framesSinceBallHitGroundOrWasCaught < 0x7FFE) {
        g_Ball.framesSinceBallHitGroundOrWasCaught++;
    } else {
        g_Ball.framesSinceBallHitGroundOrWasCaught = 0x7FFF;
    }

    for (i = 59; i > 0; i--) {
        g_Ball.pastCoordinates[i].x = g_Ball.pastCoordinates[i - 1].x;
        g_Ball.pastCoordinates[i].y = g_Ball.pastCoordinates[i - 1].y;
        g_Ball.pastCoordinates[i].z = g_Ball.pastCoordinates[i - 1].z;
    }

    if (g_Ball.catchAnimationTotalFrames != 0 || g_Ball.fielderActionOccuring != 0) {
        g_Ball.pastCoordinates[0].x = g_Ball.fielderActionCatchCoords.x;
        g_Ball.pastCoordinates[0].y = g_Ball.fielderActionCatchCoords.y;
        g_Ball.pastCoordinates[0].z = g_Ball.fielderActionCatchCoords.z;
    } else {
        g_Ball.pastCoordinates[0].x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.pastCoordinates[0].y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.pastCoordinates[0].z = g_Ball.AtBat_Contact_BallPos.z;
    }

    if (g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_WARIO || g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_WALUIGI) {
        for (i = 9; i > 0; i--) {
            g_Ball.warioStarHitCoords[i + 3].x = g_Ball.warioStarHitCoords[i + 2].x;
            g_Ball.warioStarHitCoords[i + 3].y = g_Ball.warioStarHitCoords[i + 2].y;
            g_Ball.warioStarHitCoords[i + 3].z = g_Ball.warioStarHitCoords[i + 2].z;
        }
        g_Ball.warioStarHitCoords[3].x = g_Ball.warioStarHitCoords[0].x;
        g_Ball.warioStarHitCoords[3].y = g_Ball.warioStarHitCoords[0].y;
        g_Ball.warioStarHitCoords[3].z = g_Ball.warioStarHitCoords[0].z;
    }

    fielderIdx = g_Ball.fielderWBallIndex;
    if (fielderIdx >= 0) {
        g_Ball.AtBat_Contact_BallPos.x = g_Fielders[fielderIdx].pos.x;
        g_Ball.AtBat_Contact_BallPos.y = g_Fielders[fielderIdx].pos.y;
        g_Ball.AtBat_Contact_BallPos.z = g_Fielders[fielderIdx].pos.z;
        g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z = g_Ball.AtBat_Contact_BallPos.z;
    }

    g_Ball.ballDistanceFromHome = VEC_LENGTH_XZ(&g_Ball.AtBat_Contact_BallPos);

    for (i = 0; i < 360; i++) {
        g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z = g_Ball.AtBat_Contact_BallPos.z;
    }

    g_Ball.ballOnMoundInd = 0;
    g_Ball.framesSinceLastBounce = -1;
    if (g_Ball.currentStarSwing != CAPTAIN_STAR_TYPE_NONE) {
        g_Ball.currentStarSwing = CAPTAIN_STAR_TYPE_NONE;
        g_Batter.invisibleBallForPeachStarHit = 0;
        g_Ball.warioWaluGarlicIsActive = 0;
    }
}

// .text:0x0000CE28 size:0xBC4 mapped:0x8064BEBC
void estimateAndSetFutureCoords(int mode) {
    u8 notMoving;
    u8 secondPass;
    f32 x, y, z;
    f32 prevX, prevY, prevZ;
    f32 xVel, yVel, zVel;
    f32 xAccel, yAccel, zAccel;
    f32 airRes;
    f32 t, remaining;
    int counter = 1;
    int framesOnGround = 0;
    int hitApex = 0;
    int hitGround = 0;

    notMoving = 0;
    secondPass = 0;

    for (;;) {
        if (mode == 1) {
            framesOnGround = g_Ball.framesOnGroundUntilPickedUp;
        }
        if (mode == 2) {
            x = g_Pitcher._30.x;
            y = g_Pitcher._30.y;
            z = g_Pitcher._30.z;
        } else if (g_Ball.warioWaluGarlicIsActive != 0) {
            if (secondPass) {
                x = g_Ball.warioStarHitCoords[2].x;
                y = g_Ball.warioStarHitCoords[2].y;
                z = g_Ball.warioStarHitCoords[2].z;
            } else {
                x = g_Ball.warioStarHitCoords[1].x;
                y = g_Ball.warioStarHitCoords[1].y;
                z = g_Ball.warioStarHitCoords[1].z;
            }
        } else {
            x = g_Ball.AtBat_Contact_BallPos.x;
            y = g_Ball.AtBat_Contact_BallPos.y;
            z = g_Ball.AtBat_Contact_BallPos.z;
        }

        if (g_Ball.warioWaluGarlicIsActive != 0) {
            if (secondPass) {
                xVel = g_Ball.warioStarHitCoords[14].x;
                yVel = g_Ball.warioStarHitCoords[14].y;
                zVel = g_Ball.warioStarHitCoords[14].z;
            } else {
                xVel = g_Ball.warioStarHitCoords[13].x;
                yVel = g_Ball.warioStarHitCoords[13].y;
                zVel = g_Ball.warioStarHitCoords[13].z;
            }
        } else {
            xVel = g_Ball.physicsSubstruct.velocity.x;
            yVel = g_Ball.physicsSubstruct.velocity.y;
            zVel = g_Ball.physicsSubstruct.velocity.z;
        }

        xAccel = g_Ball.physicsSubstruct.acceleration.x;
        yAccel = g_Ball.physicsSubstruct.acceleration.y;
        zAccel = g_Ball.physicsSubstruct.acceleration.z;
        airRes = 1.0f - (f32)g_Ball.airResistance / 10000.0f;

        if (!secondPass) {
            g_Ball.physicsSubstruct.futureCoordsAndDist[0].pos.x = x;
            g_Ball.physicsSubstruct.futureCoordsAndDist[0].pos.y = y;
            g_Ball.physicsSubstruct.futureCoordsAndDist[0].pos.z = z;
            g_Ball.physicsSubstruct.futureCoordsAndDist[counter].dist =
                VEC_LENGTH_XZ(&g_Ball.physicsSubstruct.futureCoordsAndDist[0].pos);
            if (lbl_3_rodata_590 == g_Ball.physicsSubstruct.velocity.x &&
                lbl_3_rodata_590 == g_Ball.physicsSubstruct.velocity.y &&
                lbl_3_rodata_590 == g_Ball.physicsSubstruct.velocity.z) {
                notMoving = 1;
            }
            if (g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_IN_AIR) {
                hitGround = 1;
            }
        }

        do {
            prevX = x;
            prevY = y;
            prevZ = z;
            yVel -= g_Ball.physicsSubstruct.gravity;
            if (!hitApex && !hitGround && yVel < lbl_3_rodata_590) {
                if (g_Ball.maxYOfHit < y) {
                    g_Ball.maxYOfHit = y;
                }
                hitApex = 1;
            }
            yVel = yVel * airRes;
            xVel = xVel * airRes;
            zVel = zVel * airRes;
            yVel = yVel + yAccel;
            xVel = xVel + xAccel;
            zVel = zVel + zAccel;
            y = y + yVel;
            x = x + xVel;
            z = z + zVel;

            if (y < g_Ball.groundYForBounces) {
                t = (prevY - g_Ball.groundYForBounces) / (prevY - y);
                remaining = 1.0f - t;
                x = t * (x - prevX) + prevX;
                z = t * (z - prevZ) + prevZ;
                yVel = -yVel;

                if (secondPass) {
                    g_Ball.peachDaisyStarHitFielderLoc.x = x;
                    g_Ball.peachDaisyStarHitFielderLoc.z = z;
                    return;
                }

                if (!hitGround) {
                    g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x = x;
                    g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z = z;
                    g_Ball.landingSpotAngle = calculateAngleFromCoordinates(x, z);
                    if (mode == 0) {
                        g_Ball.landingSpotLocation.x = x;
                        g_Ball.landingSpotLocation.z = z;
                    } else if (mode == 1 && g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR) {
                        g_Ball.landingSpotLocation.x = x;
                        g_Ball.landingSpotLocation.z = z;
                    }
                    if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR) {
                        g_Ball.hangtimeOfHit = counter + g_Ball.framesSinceHit;
                    }
                    g_Ball.framesUntilBallHitsGround = counter;
                    hitGround = 1;

                    if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR) {
                        s32 kind = g_Ball.collisionCode & 0x7F;

                        xVel = xVel * ballBounceConstants[g_d_GameSettings.StadiumID].x1stBounceSpeedKept;
                        zVel = zVel * ballBounceConstants[g_d_GameSettings.StadiumID].x1stBounceSpeedKept;
                        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && kind >= 0x70 && kind < 0x79) {
                            yVel = yVel * lbl_3_data_4414.y1stBounceSpeedKept;
                        } else {
                            yVel = yVel * ballBounceConstants[g_d_GameSettings.StadiumID].y1stBounceSpeedKept;
                        }
                        if (!notMoving && yVel < lbl_3_data_4604 && 0 >= (int)lbl_3_data_4608) {
                            notMoving = 1;
                        }
                        if (notMoving) {
                            yVel = lbl_3_rodata_590;
                        }
                    } else {
                        s32 kind = g_Ball.collisionCode & 0x7F;

                        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && kind >= 0x70 && kind < 0x79) {
                            if (framesOnGround == 0) {
                                yVel = yVel * lbl_3_data_4414.y1stBounceSpeedKept;
                            } else {
                                yVel = yVel * lbl_3_data_4414.yOtherBouncesSpeedKept;
                            }
                        } else if (framesOnGround == 0) {
                            yVel = yVel * ballBounceConstants[g_d_GameSettings.StadiumID].y1stBounceSpeedKept;
                        } else {
                            yVel = yVel * ballBounceConstants[g_d_GameSettings.StadiumID].yOtherBouncesSpeedKept;
                        }
                        if (!notMoving && yVel < lbl_3_data_4604 && framesOnGround >= lbl_3_data_4608) {
                            notMoving = 1;
                        }
                        if (notMoving) {
                            yVel = lbl_3_rodata_590;
                        }
                        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && kind >= 0x70 && kind < 0x79) {
                            if (notMoving) {
                                xVel = xVel * lbl_3_data_4414.rollingSpeedKept;
                                zVel = zVel * lbl_3_data_4414.rollingSpeedKept;
                            } else {
                                xVel = xVel * lbl_3_data_4414.xOtherBouncesSpeedKept;
                                zVel = zVel * lbl_3_data_4414.xOtherBouncesSpeedKept;
                            }
                        } else if (notMoving) {
                            xVel = xVel * ballBounceConstants[g_d_GameSettings.StadiumID].rollingSpeedKept;
                            zVel = zVel * ballBounceConstants[g_d_GameSettings.StadiumID].rollingSpeedKept;
                        } else {
                            xVel = xVel * ballBounceConstants[g_d_GameSettings.StadiumID].xOtherBouncesSpeedKept;
                            zVel = zVel * ballBounceConstants[g_d_GameSettings.StadiumID].xOtherBouncesSpeedKept;
                        }
                    }
                } else {
                    s32 kind = g_Ball.collisionCode & 0x7F;

                    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && kind >= 0x70 && kind < 0x79) {
                        if (framesOnGround == 0) {
                            yVel = yVel * lbl_3_data_4414.y1stBounceSpeedKept;
                        } else {
                            yVel = yVel * lbl_3_data_4414.yOtherBouncesSpeedKept;
                        }
                    } else if (framesOnGround == 0) {
                        yVel = yVel * ballBounceConstants[g_d_GameSettings.StadiumID].y1stBounceSpeedKept;
                    } else {
                        yVel = yVel * ballBounceConstants[g_d_GameSettings.StadiumID].yOtherBouncesSpeedKept;
                    }
                    if (!notMoving && yVel < lbl_3_data_4604 && framesOnGround >= lbl_3_data_4608) {
                        notMoving = 1;
                    }
                    if (notMoving) {
                        yVel = lbl_3_rodata_590;
                    }
                    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && kind >= 0x70 && kind < 0x79) {
                        if (notMoving) {
                            xVel = xVel * lbl_3_data_4414.rollingSpeedKept;
                            zVel = zVel * lbl_3_data_4414.rollingSpeedKept;
                        } else {
                            xVel = xVel * lbl_3_data_4414.xOtherBouncesSpeedKept;
                            zVel = zVel * lbl_3_data_4414.xOtherBouncesSpeedKept;
                        }
                    } else if (notMoving) {
                        xVel = xVel * ballBounceConstants[g_d_GameSettings.StadiumID].rollingSpeedKept;
                        zVel = zVel * ballBounceConstants[g_d_GameSettings.StadiumID].rollingSpeedKept;
                    } else {
                        xVel = xVel * ballBounceConstants[g_d_GameSettings.StadiumID].xOtherBouncesSpeedKept;
                        zVel = zVel * ballBounceConstants[g_d_GameSettings.StadiumID].xOtherBouncesSpeedKept;
                    }
                }

                x = xVel * remaining + x;
                z = zVel * remaining + z;
                framesOnGround++;
                xAccel = xAccel * 0.5f;
                zAccel = zAccel * 0.5f;
                y = yVel * remaining + (0.005f + g_Ball.groundYForBounces);
            }

            if (counter < 360 && !secondPass) {
                g_Ball.physicsSubstruct.futureCoordsAndDist[counter].pos.x = x;
                g_Ball.physicsSubstruct.futureCoordsAndDist[counter].pos.y = y;
                g_Ball.physicsSubstruct.futureCoordsAndDist[counter].pos.z = z;
                g_Ball.physicsSubstruct.futureCoordsAndDist[counter].dist =
                    g_Ball.physicsSubstruct.futureCoordsAndDist[counter].pos.x *
                        g_Ball.physicsSubstruct.futureCoordsAndDist[counter].pos.x +
                    g_Ball.physicsSubstruct.futureCoordsAndDist[counter].pos.z *
                        g_Ball.physicsSubstruct.futureCoordsAndDist[counter].pos.z;
                if (mode == 0 && g_Ball.someYCoord < lbl_3_rodata_590 &&
                    g_Ball.physicsSubstruct.futureCoordsAndDist[counter].dist > 1089.0f) {
                    g_Ball.someYCoord = g_Ball.physicsSubstruct.futureCoordsAndDist[counter].pos.y;
                }
            }
            counter++;
        } while (!hitGround || counter < 360);

        for (counter = 0; counter < 360; counter++) {
            g_Ball.physicsSubstruct.futureCoordsAndDist[counter].dist =
                dolsqrtf2(g_Ball.physicsSubstruct.futureCoordsAndDist[counter].dist);
        }

        if (mode == 0 && g_Ball.someYCoord < lbl_3_rodata_590) {
            g_Ball.someYCoord = lbl_3_rodata_590;
        }

        if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR) {
            s32 landFrame;
            f32 sqx = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x *
                      g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
            f32 sqz = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z *
                      g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;

            g_Ball.physicsSubstruct.hitLandingSpotDistFromHome = dolsqrtf2(sqx + sqz);
            if (mode == 2) {
                estimateWhereBallWillHitWall(TRUE);
            }
            landFrame = g_Ball.framesUntilBallHitsGround;
            if (landFrame < 360) {
                counter = landFrame;
                for (; counter > 0; counter--) {
                    if (g_Ball.physicsSubstruct.futureCoordsAndDist[counter].pos.y > 1.3f) {
                        g_Ball.unused_frameHitGetsAboveY_1_3 = counter;
                        break;
                    }
                }
                if (counter == 0) {
                    g_Ball.unused_frameHitGetsAboveY_1_3 = -1;
                }
            } else {
                g_Ball.unused_frameHitGetsAboveY_1_3 = 0;
            }
        }

        if (mode == 2) {
            classifyHitTrajectoryOrHitAnimRelated();
        }

        if (g_Ball.warioWaluGarlicIsActive != 0 && g_Ball.matchFramesAndBallAngle.garlicHitFramesSinceSplit == 1) {
            hitApex = 0;
            hitGround = 0;
            notMoving = 0;
            secondPass = 1;
        } else {
            break;
        }
    }
}

// .text:0x0000D9EC size:0x1E4 mapped:0x8064CA80
void fn_3_D9EC(void) {
    g_Ball.ballVelocity = VEC_LENGTH_XZ(&g_Ball.physicsSubstruct.velocity);
    g_Ball.ballStoppingCode1ReallySlow2Stopped = 0;
    if (g_Ball.ballVelocity != 0.0f) {
        g_Ball.ballVelocityPercent.x = g_Ball.physicsSubstruct.velocity.x / g_Ball.ballVelocity;
        g_Ball.ballVelocityPercent.z = g_Ball.physicsSubstruct.velocity.z / g_Ball.ballVelocity;
    }

    if (g_Ball.ballVelocity <= 0.1f && g_Ball.AtBat_Contact_BallPos.y <= 0.08f
        && g_Ball.physicsSubstruct.velocity.y < 0.01f && g_Ball.physicsSubstruct.velocity.y > -0.01f) {
        if (g_Ball.ballVelocity < 0.005f) {
            g_Ball.ballStoppingCode1ReallySlow2Stopped = 2;
            g_Ball.physicsSubstruct.velocity.x = 0.0f;
            g_Ball.physicsSubstruct.velocity.z = 0.0f;
            g_Ball.ballVelocity = 0.0f;
        } else {
            g_Ball.ballStoppingCode1ReallySlow2Stopped = 1;
        }
    }
}

// .text:0x0000DBD0 size:0x78 mapped:0x8064CC64
void adjustVeloByAirResistance(void) {
    f32 factor = 1.0f - (f32)g_Ball.airResistance / 10000.0f;
    g_Ball.physicsSubstruct.velocity.x *= factor;
    g_Ball.physicsSubstruct.velocity.y *= factor;
    g_Ball.physicsSubstruct.velocity.z *= factor;
}

// .text:0x0000DC48 size:0x68C mapped:0x8064CCDC
void estimateWhereBallWillHitWall(BOOL useBallPitcherStart) {
    VecSrcDst ray;
    CollisionStruct hit;
    BALL_COLLISION_TYPE type;
    int i;
    int j;
    int k;

    if (useBallPitcherStart) {
        ray.src.x = g_Pitcher._30.x;
        ray.src.y = -0.5f;
        ray.src.z = g_Pitcher._30.z;
        if (0.0f == g_Ball.physicsSubstruct.futureCoordsAndDist[60].dist) {
            ray.dst.x = 200.0f * g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.x;
            ray.dst.y = -0.5f;
            ray.dst.z = 200.0f * g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.z;
        } else {
            ray.dst.x = 200.0f * (g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.x
                                   / g_Ball.physicsSubstruct.futureCoordsAndDist[60].dist);
            ray.dst.y = -0.5f;
            ray.dst.z = 200.0f * (g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.z
                                   / g_Ball.physicsSubstruct.futureCoordsAndDist[60].dist);
        }
    } else {
        ray.src.x = g_Ball.AtBat_Contact_BallPos.x;
        ray.src.y = -0.5f;
        ray.src.z = g_Ball.AtBat_Contact_BallPos.z;
        ray.dst.x = 200.0f * g_Ball.ballVelocityPercent.x + g_Ball.AtBat_Contact_BallPos.x;
        ray.dst.y = -0.5f;
        ray.dst.z = 200.0f * g_Ball.ballVelocityPercent.z + g_Ball.AtBat_Contact_BallPos.z;
    }

    if (ray.src.x == ray.dst.x && ray.src.z == ray.dst.z) {
        ray.dst.z = 10.0f + ray.src.z;
    }

    type = checkCollision(&ray, &hit, 0, 0) & (BALL_COLLISION_TYPE_FOUL - 1);
    g_Ball.someCollisionVariable = 0;

    if (type == BALL_COLLISION_TYPE_WALL || type == BALL_COLLISION_TYPE_UNCLIMBABLE_WALL) {
        f32 len;

        g_Ball.ballWillHitBallPos.x = hit.position.x;
        g_Ball.ballWillHitBallPos.z = hit.position.z;
        g_Ball.wallAndBallIntersectionDistFromHome = VEC_LENGTH_XZ(&g_Ball.ballWillHitBallPos);

        len = (0.0f == VEC_LENGTH_XZ(&hit.normal)) ? 1.0f : VEC_LENGTH_XZ(&hit.normal);

        g_Ball.seeminglyAlways1_ballCollideWWallRelated = 1;
        g_Ball._19E4 = hit.normal.x / len;
        g_Ball._19E8 = hit.normal.z / len;
        g_Ball.physicsSubstruct.throwYAtSelectedFuturePoint = 0.0f;
        g_Ball.frameBallWillHitWall = -1;

        for (i = 0; i < 360; i += 10) {
            if (g_Ball.physicsSubstruct.futureCoordsAndDist[i].dist > g_Ball.wallAndBallIntersectionDistFromHome) {
                j = i - 9;
                for (k = 0; k < 10; k++, j++) {
                    if (g_Ball.physicsSubstruct.futureCoordsAndDist[j].dist
                        > g_Ball.wallAndBallIntersectionDistFromHome) {
                        g_Ball.physicsSubstruct.throwYAtSelectedFuturePoint =
                            g_Ball.physicsSubstruct.futureCoordsAndDist[j].pos.y;
                        g_Ball.frameBallWillHitWall = j;
                        i = 360;
                        break;
                    }
                }
            }
        }

        if (g_Ball.Hit_HorizontalAngle >= 0x200 && g_Ball.Hit_HorizontalAngle <= 0x600
            && g_Ball.someCollisionInd == 0) {
            if (((20.0f + g_Ball.wallAndBallIntersectionDistFromHome
                      < g_Ball.physicsSubstruct.hitLandingSpotDistFromHome
                  && g_Ball.Hit_VerticalAngle > 300)
                 || g_Ball.physicsSubstruct.hitLandingSpotDistFromHome >= 140.0f)
                && g_Ball.physicsSubstruct.throwYAtSelectedFuturePoint >= 8.0f
                && (g_Ball.ballWillHitBallPos.x < 0.0f ? -g_Ball.ballWillHitBallPos.x : g_Ball.ballWillHitBallPos.x)
                       < g_Ball.ballWillHitBallPos.z) {
                g_Ball.someCollisionVariable = 3;
            } else if (20.0f + g_Ball.wallAndBallIntersectionDistFromHome
                       < g_Ball.physicsSubstruct.hitLandingSpotDistFromHome) {
                g_Ball.someCollisionVariable = 2;
            } else if (10.0f + g_Ball.wallAndBallIntersectionDistFromHome
                           < g_Ball.physicsSubstruct.hitLandingSpotDistFromHome
                       && g_Ball.Hit_VerticalAngle > 300) {
                g_Ball.someCollisionVariable = 2;
            } else if (1.0f + g_Ball.wallAndBallIntersectionDistFromHome
                       < g_Ball.physicsSubstruct.hitLandingSpotDistFromHome) {
                g_Ball.someCollisionVariable = 1;
            }
        }
    } else {
        g_Ball.wallAndBallIntersectionDistFromHome = 999.9f;
        g_Ball.physicsSubstruct.throwYAtSelectedFuturePoint = 0.0f;
        g_Ball.frameBallWillHitWall = -1;
    }
}

static inline int findClosestFutureFrame(f32 x, f32 z, int maxFrame, int step) {
    f32 bestSqDist = reallyLargeConst;
    int frame;
    int bestFrame;

    bestFrame = -1;
    frame = 0;
    while (frame < maxFrame) {
        f32 dx = g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.x - x;
        f32 dz = g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.z - z;
        f32 sqDist = dx * dx + dz * dz;
        if (sqDist < bestSqDist) {
            bestSqDist = sqDist;
            bestFrame = frame;
            frame += step;
        } else {
            break;
        }
    }
    if (bestFrame < 0) {
        return -1;
    }
    return bestFrame;
}

// .text:0x0000E2D4 size:0xB78 mapped:0x8064D368
void calculateImplicationsOfTheHitTrajectory(void) {
    int i;

    g_Ball.ballAngleFromHome =
        calculateAngleFromCoordinates(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z);

    fn_3_D9EC();

    g_Ball.ballTravelAngle =
        calculateAngleFromCoordinates(g_Ball.physicsSubstruct.velocity.x, g_Ball.physicsSubstruct.velocity.z);
    g_Ball.ballZoneAwayFromHome = setZoneAwayFromHome(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z);

    if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR && g_Ball.framesSinceHit < 10) {
        g_Ball.landingSpotZoneAwayFromHome = setZoneAwayFromHome(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x,
                                                                 g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);
    }

    for (i = 1; i < 4; i++) {
        f32 dx = base_MoundCoordinates[i].x - g_Ball.AtBat_Contact_BallPos.x;
        f32 dz = base_MoundCoordinates[i].z - g_Ball.AtBat_Contact_BallPos.z;
        f32 sqx = dx * dx;
        f32 sqz = dz * dz;

        g_Ball.ballDistanceFromBase[i] = dolsqrtf2(sqx + sqz);
    }
    g_Ball.ballDistanceFromBase[0] = g_Ball.ballDistanceFromHome;
    {
        f32 dx = base_MoundCoordinates[4].x - g_Ball.AtBat_Contact_BallPos.x;
        f32 dz = base_MoundCoordinates[4].z - g_Ball.AtBat_Contact_BallPos.z;
        f32 sqx = dx * dx;
        f32 sqz = dz * dz;

        g_Ball.distLandingSpotToMound = dolsqrtf2(sqx + sqz);
    }

    if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR) {
        f32 offset;
        f32 x;

        x = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
        if (x > 0.0f) {
            offset = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z - x;
        } else {
            offset = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z + x;
        }
        if (offset < -20.0f) {
            g_Ball.howFoulTheBallWillBe = 3;
        } else if (offset < -10.0f) {
            g_Ball.howFoulTheBallWillBe = 2;
        } else if (offset < -5.0f) {
            g_Ball.howFoulTheBallWillBe = 1;
        } else {
            g_Ball.howFoulTheBallWillBe = 0;
        }

        if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > 110.0f) {
            x = g_Ball.ballWillHitBallPos.x;
            if (x < 0.0f) {
                x = -x;
            }
            offset = g_Ball.ballWillHitBallPos.z - x;
            if (offset < -20.0f) {
                g_Ball.howFoulTheBallWillBe = 3;
            } else if (offset < -10.0f) {
                g_Ball.howFoulTheBallWillBe = 2;
            } else if (offset < -5.0f) {
                g_Ball.howFoulTheBallWillBe = 1;
            } else {
                g_Ball.howFoulTheBallWillBe = 0;
            }
        }

        if (g_Ball.deadBallReason == 1) {
            g_Ball.howFoulTheBallWillBe = 0;
        }
    }

    if (g_Ball.ballState != BALL_STATE_HELD) {
        g_Ball.fielderWBallIndex = -1;
        g_Ball.unused_always_neg1 = -1;
        g_Ball.baseBallAndFielderAreOn = -1;
    }

    if (g_Ball.fielderAboutToGetBall_hasBall >= 0) {
        g_Ball.ballIsLooseInd_unused = 0;
    }

    if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR && g_FieldingLogic.infieldFlyIndicator == 0 &&
        g_Ball.currentStarSwing2 == 0 && g_Ball.maybeBuntInd == 0 && g_Ball.hangtimeOfHit >= 0x78 &&
        g_Ball.maxYOfHit > 10.0f && g_Strikes.storedOuts < 2 && g_Ball.howFoulTheBallWillBe < 3 &&
        g_Ball.framesSinceHit == 0x3C && g_Ball.numFieldersWhoHandledBallDuringPlay == 0) {
        f32 dx = base_MoundCoordinates[4].x - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
        f32 dz = base_MoundCoordinates[4].z - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
        f32 sqx = dx * dx;
        f32 sqz = dz * dz;

        if (dolsqrtf2(sqx + sqz) < 30.0f &&
            ((!(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z <
                g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x - 5.0f) &&
              !(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z <
                -g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x - 5.0f)) ||
             (g_Ball.Hit_HorizontalAngle >= 0x220 && g_Ball.Hit_HorizontalAngle <= 0x5E0)) &&
            (g_RunningLogic._00 & 0x110) == 0x110) {
            g_FieldingLogic.infieldFlyIndicator = 1;
        }
    }

    if (g_FieldingLogic.infieldFlyIndicator != 0 && g_Ball.framesSinceHit == 0x3C) {
        QueueTextToDisplay(6, 0);
    }

    estimateWhereBallWillHitWall(0);

    if (g_Ball.collisionRelated >= 2) {
        g_Ball.groundRuleDoubleInd = 1;
    }

    if (g_Ball.matchFramesAndBallAngle.framesAfterReceivingThrow != 0) {
        if (g_Ball.matchFramesAndBallAngle.framesAfterReceivingThrow < 0x7FFE) {
            g_Ball.matchFramesAndBallAngle.framesAfterReceivingThrow++;
        } else {
            g_Ball.matchFramesAndBallAngle.framesAfterReceivingThrow = 0x7FFF;
        }
        if (g_Ball.matchFramesAndBallAngle.framesAfterReceivingThrow >= 0x78 ||
            g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FIELDED ||
            g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT) {
            g_Ball.matchFramesAndBallAngle.framesAfterReceivingThrow = 0;
        }
    }

    g_Ball.throwHasLastedEstimatedNOfFrames = 0;
    if (g_Ball.ballOnMoundInd != 0 && g_Ball.ballState == BALL_STATE_THROWN) {
        int frame;

        frame = findClosestFutureFrame(g_Ball.throwTarget.x, g_Ball.throwTarget.z, 300, 2);
        if (frame == -1) {
            g_Ball.throwHasLastedEstimatedNOfFrames = 1;
        } else {
            g_Ball.framesUntilThrowReachesDest = frame;
        }
    }

    if (g_Ball.baseBallAndFielderAreOn >= 0) {
        if (g_Ball.matchFramesAndBallAngle.ballAndFielderOnBaseFrames < 0x7FFE) {
            g_Ball.matchFramesAndBallAngle.ballAndFielderOnBaseFrames++;
        } else {
            g_Ball.matchFramesAndBallAngle.ballAndFielderOnBaseFrames = 0x7FFF;
        }
    } else {
        g_Ball.matchFramesAndBallAngle.ballAndFielderOnBaseFrames = 0;
    }

    fielding_setHeldBallOffset();

    if (g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy != 0) {
        g_Ball.ballEnergy *= lbl_3_data_5CDC[1];
        if (g_Ball.framesSinceLastBounce == 1) {
            g_Ball.ballEnergy *= lbl_3_data_5CDC[2];
        }
        if (g_Ball.ballEnergy < lbl_3_data_5CDC[0]) {
            g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy = 0;
            g_Ball.ballEnergy = 0.0f;
        }
    }
}

// .text:0x0000EE4C size:0x390 mapped:0x8064DEE0
void setLiveBallVariablesAfterContact(void) {
    f32 magnitude;
    f32 dirX;
    f32 dirZ;
    s32 i;

    g_Ball.offsetWhilePickedUpHistory[0].x = 0.0f;
    g_Ball.offsetWhilePickedUpHistory[0].y = 0.0f;
    g_Ball.offsetWhilePickedUpHistory[0].z = 0.0f;
    g_Ball.framesSinceHit = 0;
    g_Ball.framesSinceThrowStarted = -1;
    g_Ball.framesSinceBallHitGroundOrWasCaught = -1;
    g_Ball.framesSinceLastBounce = -1;
    g_Ball.ballHitGrroundDistanceFromHome = 0.0f;
    g_Ball.AtBat_ContactResult = BALL_RESULT_TYPE_IN_AIR;
    g_Ball.ballInitialHitDoneInd = 0;
    g_Ball.fairBallInd = -1;
    g_Ball.howFoulTheBallWillBe = 0;
    g_Ball.ballState = BALL_STATE_HIT;
    g_Ball.fielderAboutToGetBall_hasBall = -1;
    g_Ball.fielderWBallIndex = -1;
    g_Ball.maxYOfHit = 0.0f;
    g_Ball.deadBallReason = 0;
    g_Ball.someCollisionVariable = 0;
    g_Ball.deadBallRBIsAddedInd = 0;
    g_Ball.baseBallAndFielderAreOn = -1;
    g_Ball.fielderBeingThrownTo = -1;
    g_Ball.ballIsLooseInd_unused = 0;
    g_Ball.homeRunClassification = 0;
    g_Ball.lineDriveThroughPitcherInd = 0;
    g_Ball.hitWallInd = 0;
    g_Ball.collisionRelated = 0;
    g_Ball.timeSinceBallPickedUp = -1;
    g_Ball.matchFramesAndBallAngle.framesSinceLastThrow = -1;
    g_Ball.groundRuleDoubleInd = 0;
    g_Ball.matchFramesAndBallAngle.framesAfterReceivingThrow = 0;
    g_Ball.numberOfThrowsDuringPlay = 0;
    g_Ball.ballZoneWhenCaught = -1;

    if (g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_WARIO || g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_WALUIGI) {
        g_Ball.warioStarHitCoords[0].x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.warioStarHitCoords[0].y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.warioStarHitCoords[0].z = g_Ball.AtBat_Contact_BallPos.z;
        g_Ball.warioStarHitCoords[1].x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.warioStarHitCoords[1].y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.warioStarHitCoords[1].z = g_Ball.AtBat_Contact_BallPos.z;
        g_Ball.warioStarHitCoords[2].x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.warioStarHitCoords[2].y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.warioStarHitCoords[2].z = g_Ball.AtBat_Contact_BallPos.z;
        for (i = 0; i < 10; i++) {
            g_Ball.warioStarHitCoords[i + 3].x = g_Ball.AtBat_Contact_BallPos.x;
            g_Ball.warioStarHitCoords[i + 3].y = g_Ball.AtBat_Contact_BallPos.y;
            g_Ball.warioStarHitCoords[i + 3].z = g_Ball.AtBat_Contact_BallPos.z;
        }
    }

    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY) {
        g_Batter.hitTrajectory = HIT_TRAJECTORY_3;
        if (g_Batter.buntStatus != BUNT_STATUS_NONE) {
            g_Batter.hitTrajectory = HIT_TRAJECTORY_6;
        }
        if (g_Ball.bODQualifyingHitInd != 0) {
            for (i = 0; i < 360; i += 5) {
                if (g_Ball.physicsSubstruct.futureCoordsAndDist[i].dist > 80.0f) {
                    s16 angle = calculateAngleFromCoordinates(g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.x,
                                                              g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z);

                    if (angle > 0x240 && angle < 0x5C0) {
                        g_Batter.hitTrajectory = HIT_TRAJECTORY_4;
                    }
                    break;
                }
            }
        }
    } else {
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER) {
            g_Batter.hitTrajectory = HIT_TRAJECTORY_3;
            if (g_Batter.buntStatus != BUNT_STATUS_NONE) {
                g_Batter.hitTrajectory = HIT_TRAJECTORY_6;
            }
        }
        estimateAndSetFutureCoords(0);
        classifyHitTrajectoryOrHitAnimRelated();
        if (g_Ball.autoFielderAvoidDropSpotForPeachesStarHit != 0) {
            if (g_Ball.currentStarSwing == CAPTAIN_STAR_TYPE_PEACH) {
                magnitude = RandomF32_Game_Range(fielderActionConstants[39], fielderActionConstants[40]);
            } else {
                magnitude = RandomF32_Game_Range(fielderActionConstants[41], fielderActionConstants[42]);
            }
            getComponentsFromSAng(RandomInt_Game(0x1000), &dirX, &dirZ);
            g_Ball.peachDaisyStarHitFielderLoc.x =
                dirX * magnitude + g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
            g_Ball.peachDaisyStarHitFielderLoc.z =
                dirZ * magnitude + g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
        }
    }
}

// .text:0x0000F1DC size:0x39C mapped:0x8064E270
void setDefaultInMemBall(void) {
    s32 i;
    u32 mixed;
    u32 frames;

    g_Ball.AtBat_Contact_BallPos.x = fieldingStartingCoords_regular[0].x;
    g_Ball.AtBat_Contact_BallPos.y = 0.0f;
    g_Ball.AtBat_Contact_BallPos.z = fieldingStartingCoords_regular[0].z;
    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_STAR_DASH) {
        g_Ball.AtBat_Contact_BallPos.x = 0.0f;
        g_Ball.AtBat_Contact_BallPos.z = 0.0f;
        g_Ball.AtBat_Contact_BallPos.y = 1.0f;
    }
    for (i = 0; i < 60; i++) {
        g_Ball.pastCoordinates[i].x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.pastCoordinates[i].y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.pastCoordinates[i].z = g_Ball.AtBat_Contact_BallPos.z;
    }

    frames = FrameCountOfEntireGame;
    g_Ball.physicsSubstruct.velocity.x = 0.0f;
    g_Ball.physicsSubstruct.acceleration.x = 0.0f;
    g_Ball.physicsSubstruct.velocity.y = 0.0f;
    g_Ball.physicsSubstruct.acceleration.y = 0.0f;
    g_Ball.physicsSubstruct.velocity.z = 0.0f;
    g_Ball.physicsSubstruct.acceleration.z = 0.0f;
    mixed = (g_Ball.StaticRandomInt2 << 4) + (frames % 10 + 1) * (g_Ball.StaticRandomInt2 * g_Ball.StaticRandomInt1)
            + (frames >> 1) + g_d_GameSettings.FrameCountWhileNotAtMainMenu;
    g_Ball.StaticRandomInt1 = mixed & 0x7FFF;
    g_Ball.StaticRandomInt2 = ((g_Ball.StaticRandomInt1 << 3)
                               + (frames % 10 + 1) * (g_Ball.StaticRandomInt2 * (g_Ball.StaticRandomInt2 + 1))
                               + (frames >> 1)
                               + (g_d_GameSettings.FrameCountWhileNotAtMainMenu >> 1))
                              & 0x7FFF;
    g_Ball.StaticRandomInt1_prePitch = g_Ball.StaticRandomInt1;
    g_Ball.framesSinceHit = -1;
    g_Ball.physicsSubstruct.gravity = lbl_3_data_45FC;
    g_Ball.framesSinceThrowStarted = -1;
    g_Ball.pitchHangtimeCounter = -1;
    g_Ball.postPitchResultCounter = -1;
    g_Ball.framesSinceBallHitGroundOrWasCaught = -1;
    g_Ball.framesSinceLastBounce = -1;
    g_Ball.framesSincePickOff = -1;
    g_Ball.ballHitGrroundDistanceFromHome = 0.0f;
    g_Ball.AtBat_ContactResult = BALL_RESULT_TYPE_IN_AIR;
    g_Ball.ballInitialHitDoneInd = 0;
    g_Ball.fairBallInd = -1;
    g_Ball.howFoulTheBallWillBe = 0;
    g_Ball.always0_fairFoulRelated = 0;
    g_Ball.ballState = BALL_STATE_HIT;
    g_Ball.fielderAboutToGetBall_hasBall = -1;
    g_Ball.fielderWBallIndex = -1;
    g_Ball.maxYOfHit = 0.0f;
    g_Ball.deadBallReason = 0;
    g_Ball.someCollisionVariable = 0;
    g_Ball.deadBallRBIsAddedInd = 0;
    g_Ball.baseBallAndFielderAreOn = -1;
    g_Ball.fielderBeingThrownTo = -1;
    g_Ball.ballIsLooseInd_unused = 0;
    g_Ball.homeRunClassification = 0;
    g_Ball.lineDriveThroughPitcherInd = 0;
    g_Ball.hitWallInd = 0;
    g_Ball.fielderWithBallIndexStored = -1;
    g_Ball.fielderWithBallIndexStored2 = -1;
    g_Ball.fielderWhoGotLastOut = -1;
    g_Ball.throwingFielder = -1;
    g_Ball.maybeBuntInd = 0;
    g_Ball.maybebuntOn2Strikes = 0;
    g_Ball.timeSinceBallPickedUp = -1;
    g_Ball.matchFramesAndBallAngle.framesSinceLastThrow = -1;
    g_Ball.groundRuleDoubleInd = 0;
    g_Ball.matchFramesAndBallAngle.framesAfterReceivingThrow = 0;
    g_Ball.numberOfThrowsDuringPlay = 0;
    g_Ball.framesOnGroundUntilPickedUp = 0;
    g_Ball.numFieldersWhoHandledBallDuringPlay = 0;
    g_Ball.numThrowsDuringPlay = 0;
    g_Ball.bobbleLocation_1fair_2foul = 0;
    g_Ball.matchFramesAndBallAngle.ballAndFielderOnBaseFrames = 0;
    g_Ball.homeRunInd = 0;
    g_Ball.matchFramesAndBallAngle.ballOverWallFrames = 0;
    g_Ball.ballZoneWhenCaught = -1;
    g_Ball.unknown_always0 = 0;
    g_Ball.matchFramesAndBallAngle.framesSinceFoulCalled = 0;
    g_Ball.collisionRelated = 0;
    g_Ball.landingSpotZoneAwayFromHome = 0;
    g_Ball.ballZoneAwayFromHome = 0;
    g_Ball.looseBall_codeForHowLongUntilSomeoneWillGetIt = 0;
    g_Ball.someYCoord = -1.0f;
    g_Ball.looseBall_5FrameCountdown = 0;
    g_Ball.ballIsRollingIndicator = 0;
    g_Ball.ballPickedUpCaught.x = 0.0f;
    g_Ball.ballPickedUpCaught.z = 0.0f;
    g_Ball.matchFramesAndBallAngle.framesOnGround = 0;
    g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy = 0;
    g_Ball.hardHitIndicator = 0;
    g_Ball.ballEnergy = 0.0f;
    g_Ball.framesSinceBallHitWall = 0;
    g_Ball.hittingAddedGravityFactor = 0.0f;
    g_Ball.currentStarSwing = CAPTAIN_STAR_TYPE_NONE;
    g_Ball.currentStarSwing2 = CAPTAIN_STAR_TYPE_NONE;
    g_Ball.knockoutProcessedFlag = 0;
    g_Ball.bODQualifyingHitInd = 0;
    g_Ball.IsAntichemistryThrow = 0;
    g_Ball.warioWaluGarlicIsActive = 0;
    g_Ball.matchFramesAndBallAngle.garlicHitFramesSinceSplit = 0;
    g_Ball.autoFielderAvoidDropSpotForPeachesStarHit = 0;
    g_Ball.fielderActionOccuring = 0;
    g_Ball.catchAnimationTotalFrames = 0;
    g_Ball.seeminglyAlways1_ballCollideWWallRelated = 1;
    g_Ball.someCollisionInd = 0;
    g_Ball.hitNoteBlockInd = 0;
    g_Ball.pauseBallMovementWhenInPlant = 0;
    g_Ball.ballCughtByPlantInd = 0;
}

// .text:0x0000F578 size:0x240 mapped:0x8064E60C
void resetBallValuesBetweenBatters(void) {
    s32 i;
    u32 mixed;
    u32 frames;

    g_Ball.AtBat_Contact_BallPos.x = fieldingStartingCoords_regular[0].x;
    g_Ball.AtBat_Contact_BallPos.y = 0.0f;
    g_Ball.AtBat_Contact_BallPos.z = fieldingStartingCoords_regular[0].z;
    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_STAR_DASH) {
        g_Ball.AtBat_Contact_BallPos.x = 0.0f;
        g_Ball.AtBat_Contact_BallPos.z = 0.0f;
        g_Ball.AtBat_Contact_BallPos.y = 1.0f;
    }
    for (i = 0; i < 60; i++) {
        g_Ball.pastCoordinates[i].x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.pastCoordinates[i].y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.pastCoordinates[i].z = g_Ball.AtBat_Contact_BallPos.z;
    }
    frames = FrameCountOfEntireGame;
    g_Ball.physicsSubstruct.velocity.x = 0.0f;
    g_Ball.physicsSubstruct.acceleration.x = 0.0f;
    g_Ball.physicsSubstruct.velocity.y = 0.0f;
    g_Ball.physicsSubstruct.acceleration.y = 0.0f;
    g_Ball.physicsSubstruct.velocity.z = 0.0f;
    g_Ball.physicsSubstruct.acceleration.z = 0.0f;
    mixed = (g_Ball.StaticRandomInt2 << 4) + (frames % 10 + 1) * (g_Ball.StaticRandomInt2 * g_Ball.StaticRandomInt1)
            + (frames >> 1) + g_d_GameSettings.FrameCountWhileNotAtMainMenu;
    g_Ball.StaticRandomInt1 = mixed & 0x7FFF;
    g_Ball.StaticRandomInt1_prePitch = g_Ball.StaticRandomInt1;
    g_Ball.StaticRandomInt2 = ((g_Ball.StaticRandomInt1 << 3)
                               + (frames % 10 + 1) * (g_Ball.StaticRandomInt2 * (g_Ball.StaticRandomInt2 + 1))
                               + (frames >> 1)
                               + (g_d_GameSettings.FrameCountWhileNotAtMainMenu >> 1))
                              & 0x7FFF;
    g_Ball.deadBallReason = 0;
}

// .text:0x0000F7B8 size:0x240 mapped:0x8064E84C
void resetInMemBall(void) {
    s32 i;
    u32 mixed;
    u32 frames;

    g_Ball.AtBat_Contact_BallPos.x = fieldingStartingCoords_regular[0].x;
    g_Ball.AtBat_Contact_BallPos.y = 0.0f;
    g_Ball.AtBat_Contact_BallPos.z = fieldingStartingCoords_regular[0].z;
    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_STAR_DASH) {
        g_Ball.AtBat_Contact_BallPos.x = 0.0f;
        g_Ball.AtBat_Contact_BallPos.z = 0.0f;
        g_Ball.AtBat_Contact_BallPos.y = 1.0f;
    }
    for (i = 0; i < 60; i++) {
        g_Ball.pastCoordinates[i].x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.pastCoordinates[i].y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.pastCoordinates[i].z = g_Ball.AtBat_Contact_BallPos.z;
    }
    frames = FrameCountOfEntireGame;
    g_Ball.physicsSubstruct.velocity.x = 0.0f;
    g_Ball.physicsSubstruct.acceleration.x = 0.0f;
    g_Ball.physicsSubstruct.velocity.y = 0.0f;
    g_Ball.physicsSubstruct.acceleration.y = 0.0f;
    g_Ball.physicsSubstruct.velocity.z = 0.0f;
    g_Ball.physicsSubstruct.acceleration.z = 0.0f;
    mixed = (g_Ball.StaticRandomInt2 << 4) + (frames % 10 + 1) * (g_Ball.StaticRandomInt2 * g_Ball.StaticRandomInt1)
            + (frames >> 1) + g_d_GameSettings.FrameCountWhileNotAtMainMenu;
    g_Ball.StaticRandomInt1 = mixed & 0x7FFF;
    g_Ball.StaticRandomInt1_prePitch = g_Ball.StaticRandomInt1;
    g_Ball.StaticRandomInt2 = ((g_Ball.StaticRandomInt1 << 3)
                               + (frames % 10 + 1) * (g_Ball.StaticRandomInt2 * (g_Ball.StaticRandomInt2 + 1))
                               + (frames >> 1)
                               + (g_d_GameSettings.FrameCountWhileNotAtMainMenu >> 1))
                              & 0x7FFF;
    g_Ball.fielderWBallIndex = -1;
}

// .text:0x0000F9F8 size:0x1B0 mapped:0x8064EA8C
void fn_3_F9F8(void) {
    s32 i;

    g_Ball.AtBat_Contact_BallPos.x = fieldingStartingCoords_regular[0].x;
    g_Ball.AtBat_Contact_BallPos.y = 0.0f;
    g_Ball.AtBat_Contact_BallPos.z = fieldingStartingCoords_regular[0].z;
    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_STAR_DASH) {
        g_Ball.AtBat_Contact_BallPos.x = 0.0f;
        g_Ball.AtBat_Contact_BallPos.z = 0.0f;
        g_Ball.AtBat_Contact_BallPos.y = 1.0f;
    }
    for (i = 0; i < 60; i++) {
        g_Ball.pastCoordinates[i].x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.pastCoordinates[i].y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.pastCoordinates[i].z = g_Ball.AtBat_Contact_BallPos.z;
    }
    g_Ball.physicsSubstruct.velocity.x = 0.0f;
    g_Ball.physicsSubstruct.acceleration.x = 0.0f;
    g_Ball.physicsSubstruct.velocity.y = 0.0f;
    g_Ball.physicsSubstruct.acceleration.y = 0.0f;
    g_Ball.physicsSubstruct.velocity.z = 0.0f;
    g_Ball.physicsSubstruct.acceleration.z = 0.0f;
}

// .text:0x0000FBA8 size:0x3A4 mapped:0x8064EC3C
void initBallAndGameStateOnLoad(void) {
    s32 i;
    u32 mixed;

    g_Ball.AtBat_Contact_BallPos.x = fieldingStartingCoords_regular[0].x;
    g_Ball.AtBat_Contact_BallPos.y = 0.0f;
    g_Ball.AtBat_Contact_BallPos.z = fieldingStartingCoords_regular[0].z;
    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_STAR_DASH) {
        g_Ball.AtBat_Contact_BallPos.x = 0.0f;
        g_Ball.AtBat_Contact_BallPos.z = 0.0f;
        g_Ball.AtBat_Contact_BallPos.y = 1.0f;
    }
    for (i = 0; i < 60; i++) {
        g_Ball.pastCoordinates[i].x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.pastCoordinates[i].y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.pastCoordinates[i].z = g_Ball.AtBat_Contact_BallPos.z;
    }

    g_Ball.physicsSubstruct.acceleration.x = 0.0f;
    g_Ball.physicsSubstruct.acceleration.y = 0.0f;
    g_Ball.physicsSubstruct.acceleration.z = 0.0f;
    g_Ball.physicsSubstruct.velocity.x = 0.0f;
    g_Ball.physicsSubstruct.velocity.y = 0.0f;
    g_Ball.physicsSubstruct.velocity.z = 0.0f;
    g_Ball.physicsSubstruct.acceleration.x = 0.0f;
    g_Ball.physicsSubstruct.acceleration.y = 0.0f;
    g_Ball.physicsSubstruct.acceleration.z = 0.0f;
    g_Ball.offsetWhilePickedUpHistory[0].x = 0.0f;
    g_Ball.offsetWhilePickedUpHistory[0].y = 0.0f;
    g_Ball.offsetWhilePickedUpHistory[0].z = 0.0f;
    g_Ball.physicsSubstruct.gravity = lbl_3_data_45FC;
    g_Ball.airResistance = lbl_3_data_4600;
    g_Ball.fielderWBallIndex = -1;
    g_Ball.ballState = BALL_STATE_HIT;
    g_Ball.AtBat_ContactResult = BALL_RESULT_TYPE_IN_AIR;
    g_Ball.ballInitialHitDoneInd = 0;
    g_Ball.fairBallInd = -1;
    g_Ball.ballStoppingCode1ReallySlow2Stopped = 0;
    g_Ball.framesSinceHit = -1;
    g_Ball.timeSinceBallPickedUp = -1;
    g_Ball.matchFramesAndBallAngle.framesSinceLastThrow = -1;
    g_Ball.framesSinceBallHitGroundOrWasCaught = -1;
    g_Ball.Hit_HorizontalPower = 0x6E;
    g_Ball.Hit_VerticalAngle = 0x18D;
    g_Ball.Hit_HorizontalAngle = 0x272;
    g_FieldingLogic.locationThrownTo = -1;
    g_FieldingLogic.humanSelectedPlaceToThrow = -1;
    g_Strikes.outs = 0;
    g_Strikes.strikes = 0;
    g_Strikes.balls = 0;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        g_Ball.groundYForBounces = lbl_3_data_45F4[1];
    } else {
        g_Ball.groundYForBounces = lbl_3_data_45F4[0];
    }

    mixed = g_Ball.StaticRandomInt1 * rand() * (FrameCountOfEntireGame % 10 + 1) + rand() * 16
            + (FrameCountOfEntireGame >> 1) + g_d_GameSettings.FrameCountWhileNotAtMainMenu;
    g_Ball.StaticRandomInt1 = mixed & 0x7FFF;
    mixed = (g_Ball.StaticRandomInt2 + 1) * rand() * (FrameCountOfEntireGame % 10 + 1) + rand() * 8
            + (FrameCountOfEntireGame >> 1) + (g_d_GameSettings.FrameCountWhileNotAtMainMenu >> 1);
    g_Ball.StaticRandomInt2 = mixed & 0x7FFF;
}
