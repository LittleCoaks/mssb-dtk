#include "game/fielding/fielder.h"
#include "game/UnknownHomes_Game.h"
#include "game/math/game_math.h"
#include "game/ball/collision_primitives.h"
#include "stl/math.h"
#include "stl/stdlib.h"
#include "stl/string.h"
#include "header_rep_data.h"
#include "static/UnknownHomes_Static.h"
#include "musyx/musyx.h"

void fielderBodyCheck_setStatus_Pos_Velo(void);

extern const f32 lbl_3_rodata_B18;
extern const f32 lbl_3_rodata_B1C;
extern const f32 lbl_3_rodata_B20;
extern const f32 lbl_3_rodata_B24;
extern const f32 lbl_3_rodata_B28;
extern const f64 lbl_3_rodata_B30;
extern const f64 lbl_3_rodata_B38;
extern const f64 lbl_3_rodata_B40;
extern const f32 lbl_3_rodata_B64;
extern const f32 lbl_3_rodata_BC4;
extern const f32 lbl_3_rodata_BCC;
extern const f32 lbl_3_rodata_BD0;
extern const f32 f8_0;
extern const f32 const_pi;
extern const f32 lbl_3_rodata_B7C;
extern const f32 lbl_3_rodata_B80;
extern const f32 lbl_3_rodata_B70;
extern const f32 lbl_3_rodata_B68;
extern const f32 lbl_3_rodata_B78;
extern const f32 lbl_3_rodata_B48;
extern const f32 lbl_3_rodata_C38;
extern const f32 lbl_3_rodata_C48;
extern const f32 lbl_3_rodata_C50;
extern const f32 lbl_3_rodata_C54;
extern const f32 lbl_3_rodata_BA0;
extern const f32 lbl_3_rodata_BD4;
extern const f32 lbl_3_rodata_BDC;
extern const f32 lbl_3_rodata_BA4;
extern const f32 const50_0;
extern const f32 const10000;
extern const f32 lbl_3_rodata_BB4;
extern const f32 lbl_3_rodata_BBC;
extern const f32 lbl_3_rodata_C24;
extern const f32 lbl_3_rodata_C84;
extern const f32 lbl_3_rodata_C88;
extern const f32 lbl_3_rodata_BF4;
extern const f32 lbl_3_rodata_C28;
extern const f32 lbl_3_rodata_C04;
extern const f32 lbl_3_rodata_C58;
extern const f32 lbl_3_rodata_C5C;
extern const f32 lbl_3_rodata_C60;
extern const f32 lbl_3_rodata_C18;
extern const f32 lbl_3_rodata_B90;
extern const f32 lbl_3_rodata_CB8;
extern const f32 lbl_3_rodata_B8C;
extern const f32 lbl_3_rodata_BB8;
extern const f32 lbl_3_rodata_CBC;
extern const f32 lbl_3_rodata_CA0;
extern const f32 lbl_3_rodata_CA4;
extern const f32 lbl_3_rodata_B60;
extern const f32 lbl_3_rodata_C10;
extern const f32 lbl_3_rodata_C14;
extern const f32 lbl_3_rodata_BE4;
extern const f32 lbl_3_rodata_BE8;
extern const f32 lbl_3_rodata_BEC;
extern const f32 lbl_3_rodata_BF0;
extern const f32 lbl_3_rodata_BF8;
extern const f32 lbl_3_rodata_C00;
extern const f32 lbl_3_rodata_C0C;
extern VecXZ base_MoundCoordinates[5];
extern f32 thresholdToBeConsideredCoveringBase_ByWeight[5];
extern VecXZ presetFielderLocations[11];
extern VecXZ lbl_3_data_18984[3];
extern const u8 _0x18aArray[8];
extern f32 fielderActionConstants[43];
extern f32 lbl_3_data_476C[];
extern f32 ballDashEffect_1_5;
extern f32 lbl_3_data_46F4;
extern f32 lbl_3_data_21A14[7];
extern f32 lbl_3_data_4848;
extern s16 lbl_3_data_484C[10];
extern s16 lbl_3_data_48A4[3][5];
extern s16 barrelCollisionHitboxes[54];
extern u8 hugeAnimStruct[0x3154];
extern u8 pauseControl[0x264];
extern f32 jumpArray[2][4];
extern u8 BobbleArray[2][4][6];
extern f32 lbl_3_data_5FC4[12];
extern f32 runningCatch_CatchThrowDistances[10];
extern u8 lbl_3_data_470C[2];
extern u8 fielderLockout[2][9];

extern int foul_checkIfFoul(f32 x, f32 z);
extern int fn_3_1379A0(int fielderIndex);
extern void fieldingRelatedAnimations(void* anim, int state);
extern int isCoordinateUncatchableTerrain(f32 x, f32 z);
extern void foulBall(void);
extern void setFielderValues(int characterID, int fielderIndex);

extern s16 chemThresholds[4];
extern struct {
    /* 0x00 */ f32 chemBobbleMults[2];
    /* 0x08 */ f32 chemMult[3];
    /* 0x14 */ f32 chemBattingMult[3];
} chemBobbleMults;
extern int calculateChemistry(int teamFielding, s16 charIdA, s16 charIdB);
extern f32 lbl_3_data_48C4;
extern s16 lbl_3_data_48C8[2][12];
extern f32 lbl_3_data_5CDC[11];

typedef struct {
    /*0x00*/ f32 _0;
    /*0x04*/ f32 _4;
    /*0x08*/ f32 maxCatchDistance;
    /*0x0C*/ f32 baseCoveringRangeModifier;
    /*0x10*/ f32 diveStartOffset;
} WeightsStruct;

extern WeightsStruct modWeightBasedFactors[6];

static inline f32 fielderSqrt(f32 x) {
    if (x > lbl_3_rodata_B20) {
        f64 half = lbl_3_rodata_B30;
        f64 three = lbl_3_rodata_B38;
        f64 xd = (f64)x;
        f64 guess = __frsqrte(xd);
        guess = half * guess * (three - guess * guess * xd);
        guess = half * guess * (three - guess * guess * xd);
        guess = half * guess * (three - guess * guess * xd);
        return (f32)(xd * guess);
    } else if (x < lbl_3_rodata_B40)
        return NAN;
    else if (isnan(x))
        return NAN;
    else
        return x;
}

static s16 currentStickDirection;
static s16 fielderControlStick_continuousAngleHistory[72];

AutoMovementFunction autoMovementFunctions[29] = {
    { 0, autoMovement0_stayStill_exceptForSpecialActions },
    { 2, autoMovement1_coverBase },
    { -1, autoMovement2_18_goTowardsBall_phase2 },
    { 1, autoMovement3_goTowardsHitBall_AITeam },
    { 1, autoMovement4_AI_goTowardsHitBall },
    { -1, autoMovement5 },
    { -1, autoMovement6_outfielderNoCatch_Phase2 },
    { 6, autoMovement7_8_outfiederNoCatch_Phase1 },
    { 5, autoMovement7_8_outfiederNoCatch_Phase1 },
    { 0, autoMovement9_OffBase_coverHome },
    { 7, autoMovement10_HasBall },
    { 3, autoMovement11_cutoff_setInitialLocation },
    { 8, autoMovement12_stopBetweenInstructions },
    { 4, autoMovement13_GoTowardsBallAsBackUp },
    { 9, autoMovement14_infieldSupport },
    { 10, autoMovement15_selectedFielderOnLooseBall },
    { 11, autoMovement16_trackFoulBall },
    { 12, autoMovement17_runningOffField },
    { 1, autoMovement2_18_goTowardsBall_phase2 },
    { 13, autoMovement19_foulBall },
    { 14, autoMovement20_pitcherLinedriveRelated },
    { 10, autoMovement21_23_humanControlInitialSelectedFielders },
    { 10, autoMovement21_23_humanControlInitialSelectedFielders },
    { 10, autoMovement21_23_humanControlInitialSelectedFielders },
    { 4, autoMovement24_goTowardsHitBall_humanTeam },
    { 15, autoMovement25_readyToInterceptThrownBall },
    { 1, autoMovement26_minigameRelated1 },
    { -1, autoMovement27_minigameDashRelated2 },
    { -1, autoMovement28_minigameDashRelated3 },
};

// .text:0x000251E4 size:0x1C0 mapped:0x80664278
void knockOut_setPosAndVelo(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    VecXYZ scratch;
    int collided;

    if (fielder->knockOutCountUp < 0x7ffe) {
        fielder->knockOutCountUp++;
    } else {
        fielder->knockOutCountUp = 0x7fff;
    }

    fielder->knockOutCountDown--;

    if (fielder->knockoutStatus == 1) {
        if (fielder->knockOutCountDown <= 0) {
            fielder->knockoutStatus = 2;
            fielder->knockOutCountUp = 0;
            fielder->knockOutCountDown = specialFielderActionConstants._40[2];
            return;
        }

        fielder->knockOutVelo *= fielderActionConstants[35];
        fielder->currentVelocity = fielder->knockOutVelo;
        getComponentsFromSAng(fielder->knockOutAngle, &fielder->xMovementDir, &fielder->zMovementDir);

        fielder->velocityX = fielder->xMovementDir * fielder->currentVelocity;
        fielder->velocityZ = fielder->zMovementDir * fielder->currentVelocity;

        collided = updateFielderPosition_checkFielderCollision(fielderIndex, &scratch);
        if (collided != 0) {
            if (collided == 2 && !(scratch.x > lbl_3_rodata_B18) && !(scratch.x < lbl_3_rodata_B1C)) {
                fielder->velocityX = scratch.x - fielder->pos.x;
                fielder->velocityZ = scratch.z - fielder->pos.z;
                fielder->pos.x = scratch.x;
                fielder->pos.z = scratch.z;
            } else {
                fielder->currentVelocity = lbl_3_rodata_B20;
                fielder->velocityX = lbl_3_rodata_B20;
                fielder->velocityZ = lbl_3_rodata_B20;
            }
        } else {
            fielder->pos.x += fielder->velocityX;
            fielder->pos.z += fielder->velocityZ;
        }

        fielder->IntendedLocation.x = fielder->pos.x;
        fielder->IntendedLocation.z = fielder->pos.z;
    } else if (fielder->knockOutCountDown <= 0) {
        fielder->knockoutStatus = 0;
    }
}

extern void playCharacterSound(int charID, int soundIndex);
extern void knockBallLoose(int fielderIndex, int flag);

// .text:0x000253A4 size:0x2A4 mapped:0x80664438
int processFielderKnockout(int fielderIndex, sAng knockOutAngle) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];

    if (fielder->wallSplatStatus != 0 || fielder->clamberStatus != 0 || fielder->wallJumpStatus != 0) {
        return 0;
    }

    fielder->knockOutAngle = knockOutAngle;
    fielder->knockoutStatus = 1;
    fielder->knockOutCountUp = 0;
    fielder->knockOutCountDown = specialFielderActionConstants._40[1];
    fielder->knockOutVelo = fielderActionConstants[34];

    if (fielder->catchAnimation == 4 || fielder->catchAnimation == 5) {
        fielder->knockOutVelo = lbl_3_rodata_B20;
    }

    if (fielder->wallSplatStatus != 0) {
        fielder->knockOutVelo = lbl_3_rodata_B20;
    }

    if (g_d_GameSettings.minigamesEnabled) {
        if (*((u8*)&g_Minigame + 0x18d8 + fielder->_020D) == 0) {
            setCharacterAnimations(*((s8*)&g_Minigame + 0x18cc + fielder->_020D), 2);
        }
    } else {
        if (!g_GameLogic.teamIsCPU[g_GameLogic.teamFielding]) {
            setCharacterAnimations(g_GameLogic.teamFielding, 2);
        }
    }

    playCharacterSound(fielder->CharID, 0xa);

    if (g_Ball.fielderWBallIndex == fielderIndex) {
        knockBallLoose(fielderIndex, 1);
        g_FieldingLogic.knockoutFinished = 1;
        g_FieldingLogic.tagAnimationType = 0;
    }

    if (fielder->catchAnimation != 0) {
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD &&
            fielderIndex != g_FieldingLogic.selectedFielder && fielderIndex != -1) {
            fielder->autoMovementFunctionIndex = 12;
            if (autoMovementFunctions[12].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[12].code;
            }
            fielder->unknown_writeOnly = 0;
            fielder->fielderVeloAdjustmentCode = 0;
            fielder->unknown_writeOnly_always0 = 0;
            fielder->timeSinceThrowWasCaught = 0;
            fielder->fielderTrackingBallState = 0;
        }

        fielder->catchAnimation = 0;
        fielder->currentVelocity = lbl_3_rodata_B20;
        fielder->framesSinceThrowWasMade = 0;
        fielder->playerNeedsToMoveToCatchThrowInd = 0;
        fielder->fielderMadeThrow = 0;
        fielder->clamberStatus = 0;
        fielder->wallJumpStatus = 0;

        if (fielder->unknown_Unused != 0) {
            fielder->unknown_Unused = 2;
        }

        if (g_Ball.fielderWBallIndex >= 0 && g_Ball.catchAnimationTotalFrames != 0) {
            g_Ball.catchAnimationTotalFrames = 0;
            g_Ball.AtBat_Contact_BallPos.x = g_Ball.fielderActionCatchCoords.x;
            g_Ball.AtBat_Contact_BallPos.y = g_Ball.fielderActionCatchCoords.y;
            g_Ball.AtBat_Contact_BallPos.z = g_Ball.fielderActionCatchCoords.z;
        }
    }

    fielder->runningCatchCountDown = 0;
    fielder->isJump = 0;
    fielder->onFire = 0;
    fielder->hitKnockbackCountdown = 0;
    g_Ball.catchAnimationTotalFrames = 0;

    return 1;
}

// .text:0x00025648 size:0x1FC mapped:0x806646DC
void fielderOnFirePosAndVelo(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    VecXYZ scratch;
    int collided;
    u8 idx;

    fielder->onFireCountdown--;
    if (fielder->onFireCountdown <= 0) {
        fielder->onFire = 0;
        fielder->currentVelocity = lbl_3_rodata_B20;
        fielder->velocityX = lbl_3_rodata_B20;
        fielder->velocityZ = lbl_3_rodata_B20;
        return;
    }

    fielder->onFireCountUp++;
    fielder->onFireFacingAngle = normalizeAngle(fielder->onFireFacingAngle + specialFielderActionConstants._40[0]);

    fielder->currentVelocity = fielderActionConstants[33];
    getComponentsFromSAng(fielder->onFireFacingAngle, &fielder->xMovementDir, &fielder->zMovementDir);

    fielder->velocityX = fielder->xMovementDir * fielder->currentVelocity;
    fielder->velocityZ = fielder->zMovementDir * fielder->currentVelocity;

    collided = updateFielderPosition_checkFielderCollision(fielderIndex, &scratch);
    if (collided != 0) {
        if (collided == 2 && !(scratch.x > lbl_3_rodata_B18) && !(scratch.x < lbl_3_rodata_B1C)) {
            fielder->velocityX = scratch.x - fielder->pos.x;
            fielder->velocityZ = scratch.z - fielder->pos.z;
            fielder->pos.x = scratch.x;
            fielder->pos.z = scratch.z;
        } else {
            fielder->currentVelocity = lbl_3_rodata_B20;
            fielder->velocityX = lbl_3_rodata_B20;
            fielder->velocityZ = lbl_3_rodata_B20;
        }
    } else {
        fielder->pos.x += fielder->velocityX;
        fielder->pos.z += fielder->velocityZ;
    }

    fielder->IntendedLocation.x = fielder->pos.x;
    fielder->IntendedLocation.z = fielder->pos.z;

    if (g_d_GameSettings.minigamesEnabled) {
        idx = fielder->_020D;
        if (g_Minigame.minigameControlStruct[0].battingHandedness[idx] == 0) {
            setCharacterAnimations(g_Minigame.minigameControlStruct[0].characterIndex[idx], 0);
        }
    } else {
        if (g_GameLogic.teamIsCPU[g_GameLogic.teamFielding] == 0) {
            setCharacterAnimations(g_GameLogic.teamFielding, 0);
        }
    }
}

// .text:0x00025844 size:0x94 mapped:0x806648D8
void maybeCastleFireballBurn(int fielderIndex, int fireballType) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];

    if (fielder->onFire != 0) {
        return;
    }

    fielder->onFireFacingAngle = radToShortAngle(fielder->desiredMovementDirection);
    fielder->onFire = 1;
    fielder->onFireCountUp = 0;
    fielder->onFireCountdown = specialFielderActionConstants.fireballCountdownArray[fireballType];
    fielder->catchAnimation = 0;
    fielder->isJump = 0;
    fielder->clamberStatus = 0;
    fielder->wallSplatStatus = 0;
    fielder->hitKnockbackCountdown = 0;
}

// .text:0x000258D8 size:0x190 mapped:0x8066496C
int fn_3_258D8(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    int idx;
    int hasSuperJump;
    int frames3;
    int apexDiv;

    if (g_FieldingLogic.jumpDiveStruct->aPressed_decidingWhatActionToTake == 0) {
        return 0;
    }
    if (fielder->jumpDiveStateRelated != 0) {
        return 0;
    }

    hasSuperJump = fielder->hasSuperJump;
    fielder->isJump = 1;
    fielder->jumpY = lbl_3_rodata_B20;

    idx = fielderIndex;
    if (g_d_GameSettings.minigamesEnabled) {
        if (fielderIndex == 0) {
            idx = *((s8*)&g_Minigame + 0x18cc + (s8)g_Minigame.minigamePlayerSelectedOrder);
        } else {
            idx = ((s8*)g_Minigame.minigameControlStruct[1].aIStrength)[fielderIndex];
        }
    }

    fielder->jumpVelocity.y = jumpArray[hasSuperJump][0];
    fielder->jumpVelocity.x = fielder->xMovementDir * lbl_3_rodata_B24 * jumpArray[hasSuperJump][2];

    frames3 = (int)jumpArray[hasSuperJump][3];

    fielder->jumpVelocity.z = fielder->zMovementDir * lbl_3_rodata_B24 * jumpArray[hasSuperJump][2];

    apexDiv = (int)(fielder->jumpVelocity.y / jumpArray[hasSuperJump][1]);

    fielder->jumpApexFrame = apexDiv + 1;
    fielder->jumpCountDown = apexDiv + apexDiv + frames3 + 2;
    fielder->jumpCountUp = 0;

    if (hasSuperJump != 0) {
        fieldingRelatedAnimations(((void**)(hugeAnimStruct + 0x2c50))[idx], 6);
    }

    g_FieldingLogic.jumpDiveStruct->aPressed_decidingWhatActionToTake = 0;
    return 1;
}

// .text:0x00025A68 size:0x1D8 mapped:0x80664AFC
void runningCatch_updatePositionAndVelocity(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    VecXYZ scratch;
    int collided;

    fielder->fielderVelocityDuringAction.x *= lbl_3_rodata_B28;
    fielder->fielderVelocityDuringAction.z *= lbl_3_rodata_B28;
    fielder->velocityX = fielder->fielderVelocityDuringAction.x;
    fielder->velocityZ = fielder->fielderVelocityDuringAction.z;
    fielder->currentVelocity = fielderSqrt(fielder->velocityX * fielder->velocityX +
                                            fielder->velocityZ * fielder->velocityZ);

    collided = updateFielderPosition_checkFielderCollision(fielderIndex, &scratch);
    if (collided != 0) {
        fielder->pos.x = fielder->posXLastFrame;
        fielder->pos.z = fielder->posZLastFrame;
        fielder->currentVelocity = lbl_3_rodata_B20;
        fielder->velocityX = lbl_3_rodata_B20;
        fielder->velocityZ = lbl_3_rodata_B20;
    } else {
        fielder->pos.x += fielder->velocityX;
        fielder->pos.z += fielder->velocityZ;
    }

    fielder->IntendedLocation.x = fielder->pos.x;
    fielder->IntendedLocation.z = fielder->pos.z;
    fielder->unused_jumpActiveOrRunningCatchRelated = 1;
}

typedef struct _FielderHitboxConstsEntry {
    /*0x00*/ s16 _00;
    /*0x02*/ s16 _02;
    /*0x04*/ s16 _04;
    /*0x06*/ s16 _06;
    /*0x08*/ s16 _08;
    /*0x0A*/ s16 _0A;
    /*0x0C*/ s16 _0C;
    /*0x0E*/ s16 _0E;
} FielderHitboxConstsEntry;

extern const FielderHitboxConstsEntry FielderHitboxConsts[55];

// .text:0x00025C40 size:0x5A8 mapped:0x80664CD4
void mag_BirdoSlidingCatchSetCoordinates(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    int idx;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 ratio;
    VecXYZ coords;

    idx = fielderIndex;
    if (g_d_GameSettings.minigamesEnabled) {
        if (fielderIndex == 0) {
            idx = *((s8*)&g_Minigame + 0x18cc + (s8)g_Minigame.minigamePlayerSelectedOrder);
        } else {
            idx = ((s8*)g_Minigame.minigameControlStruct[1].aIStrength)[fielderIndex];
        }
    }

    if (g_Ball.catchAnimationTotalFrames == 0) {
        if (fielder->catchAnimation == 3) {
            if (fielder->catchAnimationFramesCountDown > specialFielderActionConstants._00[26]) {
                return;
            }

            dx = fielder->actionStartingCoordinate.x - fielder->pos.x;
            dz = fielder->actionStartingCoordinate.z - fielder->pos.z;
            dist = fielderSqrt(dx * dx + dz * dz);
            ratio = (lbl_3_rodata_B48 * (f32)FielderHitboxConsts[fielder->CharID]._08) / dist;
            g_Ball.diveCatchLocationOffset.x = fielder->pos.x + dx * ratio;
            g_Ball.diveCatchLocationOffset.y = lbl_3_rodata_B48 * (f32)FielderHitboxConsts[fielder->CharID]._0E;
            g_Ball.diveCatchLocationOffset.z = fielder->pos.z + dz * ratio;
        } else {
            if (fielder->catchAnimationFramesCountDown > specialFielderActionConstants._00[24]) {
                return;
            }

            dx = fielder->actionStartingCoordinate.x - fielder->pos.x;
            dz = fielder->actionStartingCoordinate.z - fielder->pos.z;
            dist = fielderSqrt(dx * dx + dz * dz);
            ratio = (lbl_3_rodata_B48 * (f32)FielderHitboxConsts[fielder->CharID]._00) / dist;
            g_Ball.diveCatchLocationOffset.x = fielder->pos.x + dx * ratio;
            g_Ball.diveCatchLocationOffset.y = lbl_3_rodata_B48 * (f32)FielderHitboxConsts[fielder->CharID]._04;
            g_Ball.diveCatchLocationOffset.z = fielder->pos.z + dz * ratio;
        }

        g_Ball.fielderActionCatchCoords = g_Ball.AtBat_Contact_BallPos;
        g_Ball.catchAnimationTotalFrames = (u8)fielder->catchAnimationFramesCountDown;

        if (fielder->suctionCatchInd == 0 && fielder->catchAnimation == 3) {
            fielder->catchAnimationFramesCountDown = specialFielderActionConstants._40[5];
            g_Ball.catchAnimationTotalFrames = (u8)fielder->catchAnimationFramesCountDown;
        }

        g_Batter.invisibleBallForPeachStarHit = 0;
    } else {
        if (fielder->suctionCatchInd != 0) {
            getAnimRelatedCoordinates(idx, 0x42, &coords);
            coords.y = -coords.y;
        } else if (fielder->catchAnimation == 3) {
            coords = g_Ball.diveCatchLocationOffset;
        } else if (fielder->throwingHandedness == 0) {
            getAnimRelatedCoordinates(idx, 0x4f, &coords);
        } else {
            getAnimRelatedCoordinates(idx, 0x4e, &coords);
        }

        ratio = (f32)fielder->catchAnimationFramesCountDown / (f32)g_Ball.catchAnimationTotalFrames;
        g_Ball.fielderActionCatchCoords.x = coords.x + (g_Ball.AtBat_Contact_BallPos.x - coords.x) * ratio;
        g_Ball.fielderActionCatchCoords.y = coords.y + (g_Ball.AtBat_Contact_BallPos.y - coords.y) * ratio;
        g_Ball.fielderActionCatchCoords.z = coords.z + (g_Ball.AtBat_Contact_BallPos.z - coords.z) * ratio;

        if (fielder->catchAnimationFramesCountDown == 1) {
            g_Ball.catchAnimationTotalFrames = 0;
        }

        g_Ball.fielderActionOccuring = 1;
    }
}

// .text:0x000261E8 size:0x47C mapped:0x8066527C
void fielderMovement_VelocityDuringCatchAnimations(void) {
    return;
}

// .text:0x00026664 size:0x410 mapped:0x806656F8
void calculateBobble(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    int idx;
    int modeFlag;
    int threshold;

    fielder->bobble = 0;

    idx = fielderIndex;
    if (g_d_GameSettings.minigamesEnabled) {
        if (fielderIndex == 0) {
            idx = *((s8*)&g_Minigame + 0x18cc + (s8)g_Minigame.minigamePlayerSelectedOrder);
        } else {
            idx = ((s8*)g_Minigame.minigameControlStruct[1].aIStrength)[fielderIndex];
        }
    }

    if (ACTIVE_TUTORIAL()) {
        return;
    }

    if (g_Ball.numFieldersWhoHandledBallDuringPlay != 0 || g_Ball.hitWallInd != 0 ||
        g_Ball.framesOnGroundUntilPickedUp >= 5) {
        return;
    }

    if (checkFieldingStat(g_GameLogic.teamFielding, fielder->rosterLocation,
                           FIELDING_ABILITY_SUPER_CATCH)) {
        fieldingRelatedAnimations(((void**)(hugeAnimStruct + 0x2c50))[idx], 10);
        playSoundEffect(0x1a8);
        return;
    }

    modeFlag = 0;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        modeFlag = 1;
    }

    if (g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy != 0) {
        if (fielder->action != 0) {
            threshold = BobbleArray[modeFlag][fielder->characterClass][5];
        } else if (fielder->runningCatchInd != 0) {
            threshold = BobbleArray[modeFlag][fielder->characterClass][4];
        } else if (fielder->catchCentreRightLeftOfBody == 0) {
            threshold = BobbleArray[modeFlag][fielder->characterClass][3];
        } else {
            threshold = BobbleArray[modeFlag][fielder->characterClass][4];
        }

        if (fielderIndex == 0) {
            threshold *= 2;
        }
        threshold *= 10;

        if (!g_d_GameSettings.exhibitionMatchInd &&
            g_d_GameSettings.humanTeamNumber == g_GameLogic.teamFielding &&
            ((s8)g_d_GameSettings.challengeCaptainStarBought[3] != 0 || (s8)g_d_GameSettings._4F != 0)) {
            threshold = (int)((f32)threshold * lbl_3_data_5FC4[6]);
        }

        if (RandomInt_Game(1000) < threshold) {
            fielder->bobble = 3;
        } else {
            fielder->bobble = 1;
        }
    } else {
        if (fielder->action != 0) {
            threshold = BobbleArray[modeFlag][fielder->characterClass][2];
        } else if (fielder->runningCatchInd != 0) {
            threshold = BobbleArray[modeFlag][fielder->characterClass][1];
        } else if (fielder->catchCentreRightLeftOfBody == 0) {
            threshold = BobbleArray[modeFlag][fielder->characterClass][0];
        } else {
            threshold = BobbleArray[modeFlag][fielder->characterClass][1];
        }

        threshold *= 10;

        if (!g_d_GameSettings.exhibitionMatchInd &&
            g_d_GameSettings.humanTeamNumber == g_GameLogic.teamFielding &&
            ((s8)g_d_GameSettings.challengeCaptainStarBought[3] != 0 || (s8)g_d_GameSettings._4F != 0)) {
            threshold = (int)((f32)threshold * lbl_3_data_5FC4[6]);
        }

        if (RandomInt_Game(1000) < threshold) {
            fielder->bobble = 2;
        } else {
            fielder->bobble = 0;
        }
    }

    g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy = 0;
}

// .text:0x00026A74 size:0xBD4 mapped:0x80665B08
void updateVariablesPostCatch(void) {
    return;
}

// .text:0x00027648 size:0xF0 mapped:0x806666DC
void processFielderAutoCatch(void) {
    int i;

    for (i = 0; i < 9; i++) {
        if (g_Fielders[i].catchAnimation != 0) {
            g_Fielders[i].autoCatch0_noCatchAnimationOnly1 = 1;
            g_Ball.catchAnimationTotalFrames = 0;
        }
    }
}

// .text:0x00027738 size:0x2C mapped:0x806667CC
void fn_3_27738(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];

    fielder->autoCatch0_noCatchAnimationOnly1 = 1;
    g_Ball.catchAnimationTotalFrames = 0;
}

// .text:0x00027764 size:0xFC mapped:0x806667F8
void fn_3_27764(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];

    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD && fielderIndex != g_FieldingLogic.selectedFielder &&
        fielderIndex != -1) {
        fielder->autoMovementFunctionIndex = 12;
        if (autoMovementFunctions[12].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[12].code;
        }
        fielder->unknown_writeOnly = 0;
        fielder->fielderVeloAdjustmentCode = 0;
        fielder->unknown_writeOnly_always0 = 0;
        fielder->timeSinceThrowWasCaught = 0;
        fielder->fielderTrackingBallState = 0;
    }

    fielder->catchAnimation = 0;
    fielder->currentVelocity = lbl_3_rodata_B20;
    fielder->framesSinceThrowWasMade = 0;
    fielder->playerNeedsToMoveToCatchThrowInd = 0;
    fielder->fielderMadeThrow = 0;
    fielder->clamberStatus = 0;
    fielder->wallJumpStatus = 0;

    if (fielder->unknown_Unused != 0) {
        fielder->unknown_Unused = 2;
    }

    if (g_Ball.fielderWBallIndex < 0) {
        return;
    }
    if (g_Ball.catchAnimationTotalFrames == 0) {
        return;
    }

    g_Ball.catchAnimationTotalFrames = 0;
    g_Ball.AtBat_Contact_BallPos.x = g_Ball.fielderActionCatchCoords.x;
    g_Ball.AtBat_Contact_BallPos.y = g_Ball.fielderActionCatchCoords.y;
    g_Ball.AtBat_Contact_BallPos.z = g_Ball.fielderActionCatchCoords.z;
}

// .text:0x00027860 size:0x508 mapped:0x806668F4
void catchAnimationProgression(void) {
    return;
}

extern const f32 lbl_3_rodata_B60;
extern void camera_zoomInDuringFielderAction_slide_clamber_wallJump(u8 arg4, u16 arg5, f32 arg1, f32 arg2, f32 arg3);

// .text:0x00027D68 size:0x28C mapped:0x80666DFC
int clamberCheckCatch(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    f32 maxY;
    f32 minY;
    f32 dx;
    f32 dz;
    f32 sqx;
    f32 sqz;
    int i;

    minY = fielder->hitbox[5] + fielder->wallActionCurrentHeight;
    maxY = lbl_3_rodata_B60 + (fielder->hitbox[3] + fielder->wallActionCurrentHeight);

    for (i = 1; i < 11; i++) {
        if (g_Ball.physicsSubstruct.futureCoordsAndDist[i].dist < fielder->distanceFromHomePlate &&
            g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.y > minY &&
            g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.y < maxY) {

            dx = fielder->pos.x - g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.x;
            dz = fielder->pos.z - g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z;
            sqx = dx * dx;
            sqz = dz * dz;

            if (fielderSqrt(sqx + sqz) < fielder->hitbox[0]) {
                goto found;
            }
        }
    }

    return 0;

found:
    if (g_Ball.physicsSubstruct.futureCoordsAndDist[i + 1].dist < fielder->distanceFromHomePlate) {
        i -= 2;
    } else if (g_Ball.physicsSubstruct.futureCoordsAndDist[i + 2].dist < fielder->distanceFromHomePlate) {
        i -= 1;
    }

    if (i < 0) {
        i = 0;
    }

    fielder->catchAnimationFramesCountDown = i;
    fielder->catchAnimationFramesCountUp = 0;
    fielder->catchAnimation = 5;
    fielder->catchVerticalZone = 0;
    fielder->catchCentreRightLeftOfBody = 0;
    fielder->catchFastBattedBallInd = 0;
    fielder->autoCatch0_noCatchAnimationOnly1 = 0;
    fielder->action = 0;
    fielder->wallJumpFramesTillTopOfWallContact = 0;
    fielder->wallActionFrameCounter = 0;
    fielder->wallJumpStatus = 0;
    fielder->wallActionCountDown = 0;
    fielder->caughtBallInAir = 0;
    fielder->runningCatchInd = 0;

    if (i < g_Ball.framesUntilBallHitsGround) {
        fielder->caughtBallInAir = 1;
    }

    g_Ball.catchAnimationTotalFrames = 0;
    camera_zoomInDuringFielderAction_slide_clamber_wallJump(
        3, 0,
        g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.x,
        g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.y,
        g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z);

    return 1;
}

// .text:0x00027FF4 size:0x230 mapped:0x80667088
int wallJumpSOmething3(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    VecSrcDst inVec;
    CollisionStruct collision;
    int type;
    f32 magnitude;

    if ((lbl_3_rodata_B20 == fielder->xMovementDir && lbl_3_rodata_B20 == fielder->zMovementDir) ||
        fielder->runningAngle < 0) {
        return 0;
    }

    inVec.src.x = fielder->pos.x;
    inVec.dst.y = -fielderActionConstants[29];
    inVec.src.y = -fielderActionConstants[29];
    inVec.src.z = fielder->pos.z;
    inVec.dst.x = fielder->xMovementDir * fielderActionConstants[28] + fielder->pos.x;
    inVec.dst.z = fielder->zMovementDir * fielderActionConstants[28] + fielder->pos.z;

    type = checkCollision(&inVec, &collision, 0, 0) & 0x7F;
    if (type != BALL_COLLISION_TYPE_WALL) {
        return 0;
    }

    fielder->wallSplatStatus = 1;
    fielder->wallSplatStageCountDown = specialFielderActionConstants._00[7];
    fielder->wallActionLocationX = collision.position.x;
    fielder->wallActionLocationY = fielderActionConstants[29];
    fielder->wallactionLocationZ = collision.position.z;
    fielder->wallActionCurrentHeight = lbl_3_rodata_B20;

    magnitude = fielderSqrt(SQ(collision.normal.x) + SQ(collision.normal.z));
    fielder->actionDirectionRadians = collision.normal.x / magnitude;
    fielder->wallActionFacingAngle = collision.normal.z / magnitude;
    fielder->currentVelocity = lbl_3_rodata_B20;

    return 1;
}

// .text:0x00028224 size:0xA84 mapped:0x806672B8
void wallJumpInitialization(void) {
    return;
}

// .text:0x00028CA8 size:0x14BC mapped:0x80667D3C
void divingCatch(void) {
    return;
}

// .text:0x0002A164 size:0x124 mapped:0x806691F8
int uncalledattemptJumpingCatch(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];

    if (fielder->distanceFromBall > modWeightBasedFactors[fielder->ModifiedWeightForMag].maxCatchDistance) {
        return 0;
    }
    if (g_Ball.AtBat_Contact_BallPos.y < fielder->jumpY) {
        return 0;
    }
    if (g_Ball.AtBat_Contact_BallPos.y > fielder->jumpY + fielder->hitbox[3]) {
        return 0;
    }
    if (isCoordinateUncatchableTerrain(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z)) {
        return 0;
    }

    fielder->catchAnimationFramesCountDown = 1;
    fielder->catchAnimationFramesCountUp = 0;
    fielder->catchAnimation = 6;
    fielder->catchVerticalZone = 0;
    fielder->catchCentreRightLeftOfBody = 0;
    fielder->catchFastBattedBallInd = 0;
    fielder->autoCatch0_noCatchAnimationOnly1 = 0;
    fielder->action = 0;
    fielder->wallJumpFramesTillTopOfWallContact = 0;
    fielder->wallActionFrameCounter = 0;
    fielder->wallJumpStatus = 0;
    fielder->wallActionCountDown = 0;
    fielder->caughtBallInAir = 0;
    fielder->runningCatchInd = 0;
    if (g_Ball.framesUntilBallHitsGround > 1) {
        fielder->caughtBallInAir = 1;
    }
    g_Ball.catchAnimationTotalFrames = 0;
    return 1;
}

// .text:0x0002A288 size:0x414 mapped:0x8066931C
void checkForAndSetFielderWallActionsOrDives(void) {
    return;
}

// .text:0x0002A69C size:0x63C mapped:0x80669730
void ballThrownToEmptyBaseCatchAttempt(void) {
    return;
}

// .text:0x0002ACD8 size:0x90 mapped:0x80669D6C
int fn_3_2ACD8(int fielderIndex, int index) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];

    if (index < 1) {
        return 0;
    }

    if (checkIfCatchOccurs(fielderIndex) != 0) {
        return 1;
    }

    fielder->IntendedLocation.x = g_Ball.physicsSubstruct.futureCoordsAndDist[index].pos.x;
    fielder->IntendedLocation.z = g_Ball.physicsSubstruct.futureCoordsAndDist[index].pos.z;
    fielder->needToMoveToCatchThrownBall = 1;
    return 0;
}

// .text:0x0002AD68 size:0x858 mapped:0x80669DFC
void catchThrownBallFun(void) {
    return;
}

// .text:0x0002B5C0 size:0xD4 mapped:0x8066A654
void fn_3_2B5C0(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    int angleToBall;
    int angleToActionStart;
    s16 angleDiff;

    fielder->actionAngleType = 0;

    angleToBall = calculateAngleFromCoordinates(
        g_Ball.AtBat_Contact_BallPos.x - fielder->pos.x,
        g_Ball.AtBat_Contact_BallPos.z - fielder->pos.z);
    angleToActionStart = calculateAngleFromCoordinates(
        fielder->actionStartingCoordinate.x - fielder->pos.x,
        fielder->actionStartingCoordinate.z - fielder->pos.z);
    angleDiff = angleDifferenceNormalized(angleToBall, angleToActionStart);

    if (angleDiff < -0x500 || angleDiff > 0x500) {
        fielder->actionAngleType = 3;
    } else if (angleDiff < -0x200) {
        fielder->actionAngleType = 1;
    } else if (angleDiff > 0x200) {
        fielder->actionAngleType = 2;
    }
}

// .text:0x0002B694 size:0x470 mapped:0x8066A728
int checkIfRunningCatchOccurs(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    f32 speed;
    f32 dx;
    f32 dz;
    f32 distSq;
    f32 dist;
    f32 overshootDistance;
    f32 ratio;
    int angleToBall;
    int angleToActionStart;
    s16 angleDiff;
    int framesNeeded;
    int i;

    if (fielder->currentVelocity == lbl_3_rodata_B20 || fielder->runningAngle < 0) {
        return 0;
    }
    if (g_Ball.hitWallInd != 0) {
        return 0;
    }
    if (g_Ball.numFieldersWhoHandledBallDuringPlay != 0) {
        return 0;
    }

    if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_LANDED) {
        if (getDifferenceInAngle(fielder->playerAngleFromHome, fielder->runningAngle) > 0x500) {
            return 0;
        }
    } else if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR) {
        if (getDifferenceInAngle(fielder->playerAngleFromHome, fielder->runningAngle) > 0x500) {
            return 0;
        }
        if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > lbl_3_rodata_B60 + fielder->distanceFromHomePlate) {
            return 0;
        }
    }

    speed = fielder->joggingSpeed;
    if (fielderIndex == g_FieldingLogic.dashPtr->dashingFielderIndex) {
        speed *= g_FieldingLogic.dashPtr->sprintSpeedMultiplier;
    }

    for (i = specialFielderActionConstants._00[17]; i <= specialFielderActionConstants._00[16]; i++) {
        if (g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.y > fielder->hitbox[4]) {
            continue;
        }

        dx = g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.x - fielder->pos.x;
        dz = g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z - fielder->pos.z;

        angleDiff = getDifferenceInAngle(
            calculateAngleFromCoordinates(dx, dz),
            fielder->runningAngle);
        if (angleDiff > specialFielderActionConstants._00[18]) {
            continue;
        }

        distSq = dx * dx + dz * dz;
        dist = fielderSqrt(distSq);

        overshootDistance = dist - runningCatch_CatchThrowDistances[fielder->Weight];
        framesNeeded = (int)(overshootDistance / (speed * fielderActionConstants[30]));

        if (framesNeeded + 1 > i) {
            continue;
        }
        if (dist < fielder->hitbox[0]) {
            continue;
        }
        if (isCoordinateUncatchableTerrain(
                g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.x,
                g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z) != 0) {
            continue;
        }

        fielder->catchAnimationFramesCountDown = i;
        fielder->catchAnimationFramesCountUp = 0;
        fielder->catchAnimation = 7;
        fielder->catchVerticalZone = 0;
        fielder->catchCentreRightLeftOfBody = 0;
        fielder->catchFastBattedBallInd = 0;
        fielder->autoCatch0_noCatchAnimationOnly1 = 0;
        fielder->action = 0;
        fielder->wallJumpFramesTillTopOfWallContact = 0;
        fielder->wallActionFrameCounter = 0;
        fielder->wallJumpStatus = 0;
        fielder->wallActionCountDown = 0;
        fielder->caughtBallInAir = 0;
        fielder->runningCatchInd = 0;
        fielder->runningCatchInd = 1;

        if (i < g_Ball.framesUntilBallHitsGround) {
            fielder->caughtBallInAir = 1;
        }

        ratio = overshootDistance / dist;
        fielder->actionStartingCoordinate.x = dx * ratio + fielder->pos.x;
        g_Ball.catchAnimationTotalFrames = 0;
        fielder->actionStartingCoordinate.z = dz * ratio + fielder->pos.z;
        fielder->actionAngleType = 0;

        angleToBall = calculateAngleFromCoordinates(
            g_Ball.AtBat_Contact_BallPos.x - fielder->pos.x,
            g_Ball.AtBat_Contact_BallPos.z - fielder->pos.z);
        angleToActionStart = calculateAngleFromCoordinates(
            fielder->actionStartingCoordinate.x - fielder->pos.x,
            fielder->actionStartingCoordinate.z - fielder->pos.z);
        angleDiff = angleDifferenceNormalized(angleToBall, angleToActionStart);

        if (angleDiff < -0x500 || angleDiff > 0x500) {
            fielder->actionAngleType = 3;
        } else if (angleDiff < -0x200) {
            fielder->actionAngleType = 1;
        } else if (angleDiff > 0x200) {
            fielder->actionAngleType = 2;
        }

        return 1;
    }

    return 0;
}

// .text:0x0002BB04 size:0x734 mapped:0x8066AB98
int checkIfCatchOccurs(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    f32 dirX = fielder->velocityXPrev;
    f32 dirZ = fielder->velocityZPrev;
    int canAttempt = 1;
    f32 speed = fielderSqrt(dirX * dirX + dirZ * dirZ);
    int i;
    VecXYZ lineEnd;
    VecXYZ point;
    VecXYZ closest;
    f32 interceptDist;
    f32 xDist, zDist;
    int isRunningApproach;
    s16 angleDiff;

    if (speed != lbl_3_rodata_B20) {
        dirX = lbl_3_rodata_B24 * (dirX / speed);
        dirZ = lbl_3_rodata_B24 * (dirZ / speed);
    }

    if (g_Ball.ballState == BALL_STATE_LOOSE || g_Ball.hitWallInd != 0 || fielderIndex == 1) {
        canAttempt = 0;
    }

    if (g_Ball.framesOnGroundUntilPickedUp != 0) {
        if (g_Ball.hitClassification1 == 2) {
            if (g_Ball.ballVelocity < lbl_3_rodata_B24) {
                canAttempt = 0;
            }
        } else {
            if (g_Ball.ballVelocity < lbl_3_rodata_B7C) {
                canAttempt = 0;
            }
        }
    }

    if (canAttempt) {
        for (i = 1; i < specialFielderActionConstants._00[11]; i++) {
            f32 predX, predZ;
            f32 dx, dz;
            f32 dist;

            if (g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.y >= fielder->hitbox[3]) {
                continue;
            }

            predZ = (f32)i * dirZ + fielder->pos.z;
            dz = g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z - predZ;
            predX = (f32)i * dirX + fielder->pos.x;
            dx = g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.x - predX;
            dist = fielderSqrt(dx * dx + dz * dz);

            if (dist >= fielder->hitbox[0]) {
                continue;
            }

            {
                s16 travelAngle = normalizeAngle(g_Ball.ballTravelAngle + 0x800);
                s16 coordAngle = calculateAngleFromCoordinates(dx, dz);
                angleDiff = angleDifferenceNormalized(travelAngle, coordAngle);
            }
            isRunningApproach = 1;
            if (angleDiff > 0x400) {
                continue;
            }
            if (angleDiff >= -0x400) {
                break;
            }
        }

        if (i >= specialFielderActionConstants._00[11]) {
            return 0;
        }
    } else {
        for (i = 1; i < specialFielderActionConstants._00[11]; i++) {
            f32 predX, predZ;
            f32 dx, dz;
            f32 dist;

            if (g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.y >= fielder->hitbox[3]) {
                continue;
            }

            predZ = (f32)i * dirZ + fielder->pos.z;
            dz = g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z - predZ;
            predX = (f32)i * dirX + fielder->pos.x;
            dx = g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.x - predX;
            dist = fielderSqrt(dx * dx + dz * dz);

            if (dist < fielder->hitbox[1]) {
                break;
            }
        }

        if (i >= specialFielderActionConstants._00[11]) {
            return 0;
        }
    }

    fielder->catchAnimationFramesCountDown = i;
    fielder->catchAnimationFramesCountUp = 0;
    fielder->catchAnimation = 1;
    fielder->catchVerticalZone = 0;
    fielder->catchCentreRightLeftOfBody = 0;
    fielder->catchFastBattedBallInd = canAttempt;
    fielder->autoCatch0_noCatchAnimationOnly1 = 0;
    fielder->action = 0;
    fielder->wallJumpFramesTillTopOfWallContact = 0;
    fielder->wallActionFrameCounter = 0;
    fielder->wallJumpStatus = 0;
    fielder->wallActionCountDown = 0;
    fielder->caughtBallInAir = 0;
    fielder->runningCatchInd = 0;
    if (i < g_Ball.framesUntilBallHitsGround) {
        fielder->caughtBallInAir = 1;
    }
    g_Ball.catchAnimationTotalFrames = 0;

    if (g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.y >= fielder->hitbox[5]) {
        fielder->catchVerticalZone = 0;
    } else if (g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.y >= fielder->hitbox[4]) {
        fielder->catchVerticalZone = 1;
    } else {
        fielder->catchVerticalZone = 2;
    }

    if (canAttempt && isRunningApproach) {
        VecXYZ start;
        start.x = fielder->pos.x;
        start.y = fielder->pos.y;
        start.z = fielder->pos.z;
        lineEnd.x = lbl_3_rodata_B20;
        lineEnd.y = lbl_3_rodata_B20;
        lineEnd.z = lbl_3_rodata_B20;
        point.x = g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.x;
        point.y = lbl_3_rodata_B20;
        point.z = g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z;

        interceptDist = calculateBallInterceptDistance(&start, &lineEnd, &point, &closest);

        if (interceptDist > fielder->hitbox[2]) {
            if (angleDiff > 0) {
                fielder->catchCentreRightLeftOfBody = 2;
            } else {
                fielder->catchCentreRightLeftOfBody = 1;
            }
        }
    }

    xDist = g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.x - g_Ball.AtBat_Contact_BallPos.x;
    zDist = g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z - g_Ball.AtBat_Contact_BallPos.z;
    if (xDist == lbl_3_rodata_B20 && zDist == lbl_3_rodata_B20) {
        fielder->xDistToCatch = g_Ball.AtBat_Contact_BallPos.x;
        fielder->zDistToCatch = g_Ball.AtBat_Contact_BallPos.z;
    } else {
        fielder->xDistToCatch = xDist;
        fielder->zDistToCatch = zDist;
    }

    return 1;
}

// .text:0x0002C238 size:0xB8 mapped:0x8066B2CC
void fn_3_2C238(int fielderIndex, int catchAnimation, int framesCountDown, int autoCatchOnlyInd, int fastBattedBallInd) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];

    fielder->catchAnimationFramesCountDown = framesCountDown;
    fielder->catchAnimationFramesCountUp = 0;
    fielder->catchAnimation = catchAnimation;
    fielder->catchVerticalZone = 0;
    fielder->catchCentreRightLeftOfBody = 0;
    fielder->catchFastBattedBallInd = fastBattedBallInd;
    fielder->autoCatch0_noCatchAnimationOnly1 = autoCatchOnlyInd;
    fielder->action = 0;
    fielder->wallJumpFramesTillTopOfWallContact = 0;
    fielder->wallActionFrameCounter = 0;
    fielder->wallJumpStatus = 0;
    fielder->wallActionCountDown = 0;
    fielder->caughtBallInAir = 0;
    fielder->runningCatchInd = 0;

    if (catchAnimation == 7) {
        fielder->runningCatchInd = 1;
    }

    if (framesCountDown < g_Ball.framesUntilBallHitsGround) {
        fielder->caughtBallInAir = 1;
    }

    switch (catchAnimation) {
        case 3:
            fielder->action = 2;
            break;
        case 4:
            fielder->action = 3;
            break;
    }

    g_Ball.catchAnimationTotalFrames = 0;
}

// .text:0x0002C2F0 size:0x3A8 mapped:0x8066B384
void evaluateFlyBallCatch(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    f32 catchHeightThreshold;
    f32 dist;
    f32 dx;
    f32 dz;
    f32 sqx;
    f32 sqz;
    int frame;
    int futureIndex;

    if (fielderIndex == g_FieldingLogic.dashPtr->dashingFielderIndex) {
        return;
    }

    if (g_Ball.warioWaluGarlicIsActive != 0) {
        return;
    }

    if (g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_IN_AIR) {
        return;
    }

    catchHeightThreshold = lbl_3_rodata_B80 * fielder->hitbox[3];

    for (frame = 0; frame < 0x14; frame++) {
        futureIndex = g_Ball.framesUntilBallHitsGround - frame;
        if (catchHeightThreshold < g_Ball.physicsSubstruct.futureCoordsAndDist[futureIndex].pos.y) {
            frame--;
            break;
        }
    }

    if (frame < 0x14) {
        dx = g_Ball.physicsSubstruct.futureCoordsAndDist[futureIndex].pos.x - fielder->pos.x;
        dz = g_Ball.physicsSubstruct.futureCoordsAndDist[futureIndex].pos.z - fielder->pos.z;

        sqx = dx * dx;
        sqz = dz * dz;
        dist = fielderSqrt(sqx + sqz);
        fielder->distToWhereFlyBallWillBeAtHalfFielderHeight = dist;

        if (dist < lbl_3_rodata_B64) {
            if (fielder->always0 != 0 || g_Ball.framesUntilBallHitsGround >= 0x2d) {
                fielder->closingInOnCatchingFlyBall = 1;
            } else if (g_Ball.framesUntilBallHitsGround > 0x1e) {
                if (fielder->closingInOnCatchingFlyBall_stored != 0) {
                    if (dist < lbl_3_rodata_B8C) {
                        fielder->closingInOnCatchingFlyBall = 1;
                    }
                } else if (dist < lbl_3_rodata_B78) {
                    fielder->closingInOnCatchingFlyBall = 1;
                }
            }

            if (dist < fielder->hitbox[0]) {
                g_FieldingLogic._0144 = 1;
            }
        }
    }
}

// .text:0x0002C698 size:0x548 mapped:0x8066B72C
void checkForCatchBallAction(void) {
    return;
}

// .text:0x0002CBE0 size:0x314 mapped:0x8066BC74
void minigameDashUpdateFieldingVals(void) {
    return;
}

// .text:0x0002CEF4 size:0x18C mapped:0x8066BF88
void unused_FUN_8066bf88(void) {
    return;
}

extern const f32 lbl_3_rodata_B94;
extern const f32 lbl_3_rodata_B98;
extern const f32 lbl_3_rodata_B9C;
extern const f32 lbl_3_rodata_B60;
extern s16 lbl_3_data_1C3C[2];

// .text:0x0002D080 size:0x288 mapped:0x8066C114
int determineBestFrameForFielder(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    CoordAndDist* futureCoord;
    int frame;
    int bestFrame = 0;
    int found = 0;
    int lastFramesNeeded = 9999;
    f32 bestHeight = lbl_3_rodata_B94;
    s16 reactionFrames = lbl_3_data_1C3C[1];
    f32 dx;
    f32 dz;
    f32 dist;
    f32 speed;
    int travelFrames;
    int framesNeeded;

    for (frame = 0; frame < 360; ) {
        futureCoord = &g_Ball.physicsSubstruct.futureCoordsAndDist[frame];

        if (futureCoord->pos.y > lbl_3_rodata_B98) {
            if (futureCoord->pos.y > lbl_3_rodata_B9C) {
                frame += 10;
            } else if (futureCoord->pos.y > lbl_3_rodata_BA0) {
                frame += 5;
            } else {
                frame += 2;
            }
            continue;
        }

        if (futureCoord->pos.x == fielder->pos.x && futureCoord->pos.z == fielder->pos.z) {
            framesNeeded = 1;
        } else {
            dx = futureCoord->pos.x - fielder->pos.x;
            dz = futureCoord->pos.z - fielder->pos.z;
            dist = fielderSqrt(dx * dx + dz * dz);

            speed = fielder->joggingSpeed;
            if (speed == lbl_3_rodata_B20) {
                speed = lbl_3_rodata_B60;
            }
            travelFrames = (int)(dist / speed);
            framesNeeded = (fielder->maxAccLength_ConstF >> 1) + travelFrames;
        }

        if (framesNeeded < frame - reactionFrames) {
            if (futureCoord->pos.y < fielder->hitbox[3]) {
                break;
            }

            if (found == 0 || bestHeight >= futureCoord->pos.y) {
                bestHeight = futureCoord->pos.y;
                bestFrame = frame;
                found = 1;
            } else {
                frame = bestFrame;
                break;
            }
        } else if (found != 0) {
            frame = bestFrame;
            break;
        }

        if (framesNeeded <= lastFramesNeeded || found != 0) {
            lastFramesNeeded = framesNeeded;
            frame += 3;
        } else {
            break;
        }
    }

    return (frame < 360) ? frame : 359;
}

// .text:0x0002D308 size:0x174 mapped:0x8066C39C
void fn_3_2D308(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    f32 diffZ;
    f32 diffX;
    f32 dist;

    fielder->movementAngle = -1;

    diffZ = fielder->IntendedLocation.z - fielder->pos.z;
    diffX = fielder->IntendedLocation.x - fielder->pos.x;
    dist = fielderSqrt(diffX * diffX + diffZ * diffZ);

    if (dist < lbl_3_rodata_B80) {
        fielder->distanceFromAutoLocation = dist;
        fielder->_0209 = 0;
    } else {
        fielder->movementAngle = calculateAngleFromCoordinates(diffX, diffZ);
        fielder->_0209 = 0;
    }
}

// .text:0x0002D47C size:0x2EC mapped:0x8066C510
void updateFielderPositionBasedOnBallState(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    int useCurrentPos;
    int frame;
    int bestIdx;
    f32 best;
    f32 dx;
    f32 dz;
    f32 dist;
    int i;
    VecXYZ* coin;

    useCurrentPos = 0;
    if (g_Minigame.TF_ballDespawnedInd) {
        useCurrentPos = 1;
    } else if (g_Ball.fielderWBallIndex >= 0) {
        useCurrentPos = 1;
    } else if (g_Ball.deadBallReason != 0) {
        useCurrentPos = 1;
    }

    if (g_Minigame._1939) {
        if (useCurrentPos) {
            fielder->_0208 = 4;
            goto stateChecks;
        }
    }

    if (useCurrentPos) {
        fielder->IntendedLocation.x = fielder->pos.x;
        fielder->IntendedLocation.z = fielder->pos.z;
        return;
    }

    if (g_Ball.hitWallInd != 0) {
        fielder->_0208 = 2;
    }

stateChecks:
    if (fielder->_0208 == 1) {
        if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_LANDED) {
            fielder->_0208 = 2;
        } else {
            fielder->IntendedLocation.x = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
            fielder->IntendedLocation.z = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
        }
    }

    if (fielder->_0208 == 2) {
        fielder->IntendedLocation.x = g_Ball.AtBat_Contact_BallPos.x;
        fielder->IntendedLocation.z = g_Ball.AtBat_Contact_BallPos.z;
    }

    if (fielder->_0208 == 3) {
        frame = determineBestFrameForFielder(fielderIndex);
        fielder->IntendedLocation.x = g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.x;
        fielder->IntendedLocation.z = g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.z;
    }

    if (fielder->_0208 == 4) {
        bestIdx = -1;
        best = lbl_3_rodata_BA4;
        coin = &g_Minigame.wallBall_coinCoordinates;
        for (i = 0; i < 100; i++, coin++) {
            if (g_Minigame._1939) {
                dx = fielder->pos.x - coin->x;
                dz = fielder->pos.z - coin->z;
                dist = fielderSqrt(dx * dx + dz * dz);
                if (dist < best) {
                    bestIdx = i;
                    best = dist;
                }
            }
        }
        if (bestIdx >= 0) {
            fielder->IntendedLocation.x = (&g_Minigame.wallBall_coinCoordinates)[bestIdx].x;
            fielder->IntendedLocation.z = (&g_Minigame.wallBall_coinCoordinates)[bestIdx].z;
        }
    }
}

// .text:0x0002D768 size:0x1C4 mapped:0x8066C7FC
void unused_FUN_8066c7fc(void) {
    return;
}

// .text:0x0002D92C size:0x198 mapped:0x8066C9C0
void autoMovement28_minigameDashRelated3(int fielderIndex) {
    return;
}

// .text:0x0002DAC4 size:0x230 mapped:0x8066CB58
void autoMovement27_minigameDashRelated2(int fielderIndex) {
    return;
}

// .text:0x0002DCF4 size:0xC0 mapped:0x8066CD88
void autoMovement26_minigameRelated1(int fielderIndex) {
    return;
}

// .text:0x0002DDB4 size:0x668 mapped:0x8066CE48
void fn_3_2DDB4(void) {
    return;
}

// .text:0x0002E41C size:0x460 mapped:0x8066D4B0
void fn_3_2E41C(void) {
    return;
}

// .text:0x0002E87C size:0x1A8 mapped:0x8066D910
void toyfieldRelated(void) {
    int i;
    InMemFielder* fielder;
    f32 outX;
    f32 outZ;
    u8 numParticipants;

    fielding_setStartingCoordinates(0, &outX, &outZ);

    numParticipants = g_Minigame.miniGameNumberOfParticipants;
    g_Fielders[0].pos.x = outX;
    g_Fielders[0].pos.z = outZ;
    g_Fielders[0].IntendedLocation.x = lbl_3_rodata_B20;
    g_Fielders[0].IntendedLocation.y = lbl_3_rodata_B20;
    g_Fielders[0].IntendedLocation.z = lbl_3_rodata_B20;
    g_Fielders[0].velocityX = lbl_3_rodata_B20;
    g_Fielders[0].velocityZ = lbl_3_rodata_B20;
    g_Fielders[0].xMovementDir = lbl_3_rodata_B20;

    if (numParticipants >= 4) {
        g_Fielders[3].pos.x = lbl_3_data_18984[1].x;
        g_Fielders[3].pos.z = lbl_3_data_18984[1].z;
    } else if (numParticipants >= 3) {
        g_Fielders[3].pos.x = lbl_3_data_18984[0].x;
        g_Fielders[3].pos.z = lbl_3_data_18984[0].z;
    }

    if (numParticipants >= 4) {
        g_Fielders[4].pos.x = lbl_3_data_18984[2].x;
        g_Fielders[4].pos.z = lbl_3_data_18984[2].z;
    }

    for (i = 0; i < 9; i++) {
        fielder = &g_Fielders[i];
        fielder->IntendedLocation.x = lbl_3_rodata_B20;
        fielder->IntendedLocation.y = lbl_3_rodata_B20;
        fielder->IntendedLocation.z = lbl_3_rodata_B20;
        fielder->velocityX = lbl_3_rodata_B20;
        fielder->velocityZ = lbl_3_rodata_B20;
        fielder->posXLastFrame = fielder->pos.x;
        fielder->posZLastFrame = fielder->pos.z;
        fielder->currentVelocity = lbl_3_rodata_B20;
        fielder->goingToAutoLocationInd = 0;
        fielder->baseCurrentlyOn = -1;
        outX = -fielder->pos.x;
        outZ = -fielder->pos.z;
        fielder->desiredMovementDirection = ATAN2F(outZ, outX);
    }

    g_AiLogic._B4 = 0;
    g_AiLogic._B8 = 0;
    g_AiLogic._B5 = 0;
    g_AiLogic._B9 = 0;
    g_AiLogic._B6 = 0;
    g_AiLogic._BA = 0;
    g_AiLogic._B7 = 0;
    g_AiLogic._BB = 0;
}

// .text:0x0002EA24 size:0x64 mapped:0x8066DAB8
void miniGameFielding(void) {
    return;
}

// .text:0x0002EA88 size:0x43C mapped:0x8066DB1C
void fn_3_2EA88(void) {
    return;
}

// .text:0x0002EEC4 size:0x5C0 mapped:0x8066DF58
void minigameDashUpdateFieldingVariables(void) {
    return;
}

// .text:0x0002F484 size:0xF0 mapped:0x8066E518
void miniGameDash(void) {
    return;
}

// .text:0x0002F574 size:0x260 mapped:0x8066E608
void jumpSetPosAndVelo(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    VecXYZ scratch;
    int collided;
    int hasSuperJump = fielder->hasSuperJump;

    fielder->jumpCountUp++;

    fielder->jumpVelocity.y -= jumpArray[hasSuperJump][1];
    if (fielder->jumpCountDown >= fielder->jumpApexFrame && fielder->jumpVelocity.y < lbl_3_rodata_B20) {
        fielder->jumpVelocity.y = lbl_3_rodata_B20;
    }
    fielder->jumpY += fielder->jumpVelocity.y;
    fielder->jumpCountDown--;

    if (fielder->jumpVelocity.x != lbl_3_rodata_B20 || fielder->jumpVelocity.z != lbl_3_rodata_B20) {
        fielder->velocityX = fielder->jumpVelocity.x;
        fielder->velocityZ = fielder->jumpVelocity.z;
        fielder->currentVelocity = fielderSqrt(fielder->velocityX * fielder->velocityX + fielder->velocityZ * fielder->velocityZ);

        collided = updateFielderPosition_checkFielderCollision(fielderIndex, &scratch);
        if (collided != 0) {
            fielder->jumpVelocity.x = lbl_3_rodata_B20;
            fielder->jumpVelocity.z = lbl_3_rodata_B20;
            fielder->velocityX = lbl_3_rodata_B20;
            fielder->velocityZ = lbl_3_rodata_B20;
            fielder->currentVelocity = lbl_3_rodata_B20;
        } else {
            fielder->pos.x += fielder->velocityX;
            fielder->pos.z += fielder->velocityZ;
        }
    }

    fielder->IntendedLocation.x = fielder->pos.x;
    fielder->IntendedLocation.z = fielder->pos.z;
    fielder->unused_jumpActiveOrRunningCatchRelated = 1;

    if (fielder->jumpCountDown <= 0) {
        fielder->isJump = 0;
        fielder->jumpY = lbl_3_rodata_B20;
        fielder->framesSinceStartedMoving = 0;
    }
}

// .text:0x0002F7D4 size:0x150 mapped:0x8066E868
void fn_3_2F7D4(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    int hasSuperJump = fielder->hasSuperJump;
    int idx = fielderIndex;
    int frames3;
    int apexDiv;

    fielder->isJump = 1;
    fielder->jumpY = lbl_3_rodata_B20;

    if (g_d_GameSettings.minigamesEnabled) {
        if (fielderIndex == 0) {
            idx = *((s8*)&g_Minigame + 0x18cc + (s8)g_Minigame.minigamePlayerSelectedOrder);
        } else {
            idx = ((s8*)g_Minigame.minigameControlStruct[1].aIStrength)[fielderIndex];
        }
    }

    fielder->jumpVelocity.y = jumpArray[hasSuperJump][0];
    fielder->jumpVelocity.x = fielder->xMovementDir * lbl_3_rodata_B24 * jumpArray[hasSuperJump][2];

    frames3 = (int)jumpArray[hasSuperJump][3];

    fielder->jumpVelocity.z = fielder->zMovementDir * lbl_3_rodata_B24 * jumpArray[hasSuperJump][2];

    apexDiv = (int)(fielder->jumpVelocity.y / jumpArray[hasSuperJump][1]);

    fielder->jumpApexFrame = apexDiv + 1;
    fielder->jumpCountDown = apexDiv + apexDiv + frames3 + 2;
    fielder->jumpCountUp = 0;

    if (hasSuperJump != 0) {
        fieldingRelatedAnimations(((void**)(hugeAnimStruct + 0x2c50))[idx], 6);
    }
}

extern const f32 lbl_3_rodata_B60;
extern void playCharacterSound(int charID, int soundIndex);

// .text:0x0002F924 size:0x278 mapped:0x8066E9B8
void wallSplat_setPosAndVelo(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];

    if (fielder->wallSplatStatus == 1) {
        f32 factor;
        f32 heightDelta;
        f32 dx = fielder->wallActionLocationX - fielder->pos.x;
        f32 dz = fielder->wallactionLocationZ - fielder->pos.z;
        f32 dy = fielder->wallActionLocationY - fielder->wallActionCurrentHeight;

        if (fielder->wallSplatStageCountDown > 1) {
            factor = lbl_3_rodata_B60 / (f32)fielder->wallSplatStageCountDown;
        } else {
            factor = lbl_3_rodata_B60;
        }

        fielder->velocityX = dx * factor;
        fielder->velocityZ = dz * factor;
        heightDelta = dy * factor;
        fielder->pos.x += fielder->velocityX;
        fielder->pos.z += fielder->velocityZ;
        fielder->wallActionCurrentHeight += heightDelta;

        fielder->wallSplatStageCountDown--;
        if (fielder->wallSplatStageCountDown == 0) {
            fielder->wallSplatStatus = 2;
            fielder->wallSplatStageCountDown = specialFielderActionConstants._00[8];

            if (g_d_GameSettings.minigamesEnabled) {
                if (*((u8*)&g_Minigame + 0x18d8 + fielder->_020D) == 0) {
                    setCharacterAnimations(*((s8*)&g_Minigame + 0x18cc + fielder->_020D), 2);
                }
            } else {
                if (!g_GameLogic.teamIsCPU[g_GameLogic.teamFielding]) {
                    setCharacterAnimations(g_GameLogic.teamFielding, 2);
                }
            }
            playCharacterSound(fielder->CharID, 0xb);
        }
    } else if (fielder->wallSplatStatus == 2) {
        fielder->wallSplatStageCountDown--;
        if (fielder->wallSplatStageCountDown == 0) {
            fielder->wallSplatStatus = 3;
            fielder->wallSplatStageCountDown = specialFielderActionConstants._00[9];
        }
    } else if (fielder->wallSplatStatus == 3) {
        fielder->wallActionCurrentHeight -= fielder->wallActionCurrentHeight / (f32)fielder->wallSplatStageCountDown;

        fielder->wallSplatStageCountDown--;
        if (fielder->wallSplatStageCountDown == 0) {
            fielder->wallActionCurrentHeight = lbl_3_rodata_B20;
            fielder->wallSplatStatus = 4;
            fielder->wallSplatStageCountDown = specialFielderActionConstants._00[10];
        }
    } else if (fielder->wallSplatStatus == 4) {
        fielder->wallSplatStageCountDown--;
        if (fielder->wallSplatStageCountDown == 0) {
            fielder->wallSplatStatus = 0;
        }
    }
}

// .text:0x0002FB9C size:0x390 mapped:0x8066EC30
void setClamberPos(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    VecSrcDst inVec;
    CollisionStruct collision;
    f32 cosComponent;
    f32 sinComponent;
    f32 height;
    f32 angle;
    f32 magnitude;
    int type;
    int status;
    int nextStatus;
    int collided = 0;

    height = fielder->wallActionCurrentHeight;

    if (g_Ball.ballState == BALL_STATE_HELD || g_Ball.ballState == BALL_STATE_THROWN) {
        fielder->clamberStatus = 3;
        return;
    }

    if (g_FieldingLogic.fielderInputsLatestFrame & 0x100) {
        fielder->clamberStatus = 3;
        return;
    }

    if (g_FieldingLogic.fielderInputs & INPUT_BUTTON_UP) {
        status = 1;
        height = height + fielderActionConstants[25];
    } else if (g_FieldingLogic.fielderInputs & INPUT_BUTTON_DOWN) {
        status = 2;
        height = height - fielderActionConstants[25];
    } else {
        goto horizontal;
    }

    if (height <= lbl_3_rodata_B20) {
        fielder->clamberStatus = 3;
        return;
    }

    inVec.dst.y = -(height + fielder->hitbox[3]);
    inVec.src.y = -(height + fielder->hitbox[3]);
    inVec.src.x = lbl_3_rodata_B64 * fielder->actionDirectionRadians + fielder->pos.x;
    inVec.src.z = lbl_3_rodata_B64 * fielder->wallActionFacingAngle + fielder->pos.z;
    inVec.dst.x = fielder->pos.x - lbl_3_rodata_B64 * fielder->actionDirectionRadians;
    inVec.dst.z = fielder->pos.z - lbl_3_rodata_B64 * fielder->wallActionFacingAngle;

    type = checkCollision(&inVec, &collision, 0, 0) & 0x7F;
    if (type == BALL_COLLISION_TYPE_WALL) {
        fielder->wallActionCurrentHeight = height;
        collided = 1;
        fielder->wjRelated = status;
        goto horizontal;
    }
    return;

horizontal:
    if (g_FieldingLogic.fielderInputs & INPUT_BUTTON_RIGHT) {
        angle = fielder->wjAngleRelated - fielderActionConstants[26];
        nextStatus = 3;
    } else if (g_FieldingLogic.fielderInputs & INPUT_BUTTON_LEFT) {
        angle = fielder->wjAngleRelated + fielderActionConstants[26];
        nextStatus = 4;
    } else {
        goto finish;
    }

    getComponentsFromRad(angle, &cosComponent, &sinComponent);

    inVec.src.x = cosComponent * (fielder->distanceFromHomePlate - lbl_3_rodata_B64);
    inVec.src.z = sinComponent * (fielder->distanceFromHomePlate - lbl_3_rodata_B64);
    inVec.dst.x = cosComponent * (lbl_3_rodata_B64 + fielder->distanceFromHomePlate);
    inVec.dst.z = sinComponent * (lbl_3_rodata_B64 + fielder->distanceFromHomePlate);
    inVec.dst.y = -(fielder->wallActionCurrentHeight + fielder->hitbox[4]);
    inVec.src.y = -(fielder->wallActionCurrentHeight + fielder->hitbox[4]);

    type = checkCollision(&inVec, &collision, 0, 0) & 0x7F;
    if (type == BALL_COLLISION_TYPE_WALL) {
        fielder->pos.x = collision.position.x;
        fielder->pos.z = collision.position.z;
        if (nextStatus != 0) {
            fielder->wjRelated = nextStatus;
        }
        collided = 1;
    } else {
        collided = 0;
    }

finish:
    if (collided) {
        magnitude = fielderSqrt(SQ(collision.normal.x) + SQ(collision.normal.z));
        fielder->actionDirectionRadians = collision.normal.x / magnitude;
        fielder->wallActionFacingAngle = collision.normal.z / magnitude;
    }
}

// .text:0x0002FF2C size:0x18C mapped:0x8066EFC0
void clamberJumpOffWall(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    int countdown = fielder->specialActionCountdown;
    u8 status;

    if (countdown < 0x7FFE) {
        fielder->specialActionCountdown = countdown + 1;
    } else {
        fielder->specialActionCountdown = 0x7FFF;
    }

    status = fielder->clamberStatus;
    if (status == 5) {
        if (fielder->specialActionCountdown < specialFielderActionConstants._00[6]) {
            return;
        }
    }

    if (status == 3 || status == 5) {
        if (status == 3) {
            fielder->wallActionVelo.x = fielder->actionDirectionRadians * fielderActionConstants[19];
            fielder->wallActionVelo.z = fielder->wallActionFacingAngle * fielderActionConstants[19];
            fielder->wallActionVelo.y = fielderActionConstants[21];
        } else {
            fielder->wallActionVelo.x = fielder->actionDirectionRadians * fielderActionConstants[20];
            fielder->wallActionVelo.z = fielder->wallActionFacingAngle * fielderActionConstants[20];
            fielder->wallActionVelo.y = fielderActionConstants[22];
        }
        fielder->clamberStatus++;
    } else {
        fielder->wallActionVelo.x = fielder->wallActionVelo.x * fielderActionConstants[23];
        fielder->wallActionVelo.z = fielder->wallActionVelo.z * fielderActionConstants[23];
        fielder->wallActionVelo.y = fielder->wallActionVelo.y + fielderActionConstants[24];
    }

    fielder->pos.x = fielder->pos.x + fielder->wallActionVelo.x;
    fielder->pos.z = fielder->pos.z + fielder->wallActionVelo.z;
    fielder->wallActionCurrentHeight = fielder->wallActionCurrentHeight + fielder->wallActionVelo.y;
    if (fielder->wallActionCurrentHeight <= lbl_3_rodata_B20) {
        fielder->wallActionCurrentHeight = lbl_3_rodata_B20;
        fielder->clamberStatus = 0;
        fielder->wallActionFacingAngleInd = 1;
    }

    fielder->velocityX = fielder->pos.x - fielder->posXLastFrame;
    fielder->velocityZ = fielder->pos.z - fielder->posZLastFrame;
}

extern const f64 lbl_3_rodata_B50;

// .text:0x000300B8 size:0x15C mapped:0x8066F14C
void fn_3_300B8(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];

    fielder->wjRelated = 0;

    if (fielder->clamberStatus == 1) {
        fielder->pos.x = fielder->pos.x +
            (fielder->wallActionLocationX - fielder->pos.x) / (f32)fielder->specialActionCountdown;
        fielder->pos.z = fielder->pos.z +
            (fielder->wallactionLocationZ - fielder->pos.z) / (f32)fielder->specialActionCountdown;

        fielder->wallActionVelo.y = fielder->wallActionVelo.y - fielderActionConstants[18];
        fielder->wallActionCurrentHeight = fielder->wallActionCurrentHeight + fielder->wallActionVelo.y;
        if (fielder->wallActionCurrentHeight < lbl_3_rodata_B20) {
            fielder->wallActionCurrentHeight = lbl_3_rodata_B20;
        }

        fielder->specialActionCountdown = fielder->specialActionCountdown - 1;
        if (fielder->specialActionCountdown <= 0) {
            fielder->clamberStatus = 2;
        }
    } else if (fielder->clamberStatus == 2) {
        setClamberPos(fielderIndex);
        fielder->specialActionCountdown = 0;
    } else if (fielder->clamberStatus >= 3) {
        clamberJumpOffWall(fielderIndex);
        return;
    }

    fielder->velocityX = fielder->pos.x - fielder->posXLastFrame;
    fielder->velocityZ = fielder->pos.z - fielder->posZLastFrame;
}

// .text:0x00030214 size:0x350 mapped:0x8066F2A8
int clamberInitialization(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    VecSrcDst inVec;
    CollisionStruct collision;
    int type;
    f32 dx, dz;
    f32 dist;
    f32 magnitude;

    if ((lbl_3_rodata_B20 == fielder->xMovementDir && lbl_3_rodata_B20 == fielder->zMovementDir) ||
        fielder->runningAngle < 0) {
        return 0;
    }

    inVec.src.x = fielder->pos.x;
    inVec.dst.y = lbl_3_rodata_BB4;
    inVec.src.y = lbl_3_rodata_BB4;
    inVec.src.z = fielder->pos.z;
    inVec.dst.x = fielder->xMovementDir * fielderActionConstants[15] + fielder->pos.x;
    inVec.dst.z = fielder->zMovementDir * fielderActionConstants[15] + fielder->pos.z;

    type = checkCollision(&inVec, &collision, 0, 0) & 0x7F;
    if (type != BALL_COLLISION_TYPE_WALL) {
        return 0;
    }

    fielder->clamberStatus = 1;

    dx = inVec.dst.x - fielder->pos.x;
    dz = inVec.dst.z - fielder->pos.z;
    dist = fielderSqrt(dx * dx + dz * dz);

    fielder->specialActionCountdown = (int)(dist / fielderActionConstants[16]) + 1;
    fielder->wallActionLocationX = collision.normal.x * fielderActionConstants[27] + collision.position.x;
    fielder->wallactionLocationZ = collision.normal.z * fielderActionConstants[27] + collision.position.z;
    fielder->wallActionVelo.y = fielderActionConstants[17];
    fielder->wallActionCurrentHeight = lbl_3_rodata_B20;

    magnitude = fielderSqrt(SQ(collision.normal.x) + SQ(collision.normal.z));
    fielder->actionDirectionRadians = collision.normal.x / magnitude;
    fielder->wallActionFacingAngle = collision.normal.z / magnitude;
    fielder->currentVelocity = lbl_3_rodata_B20;

    return 1;
}

// .text:0x00030564 size:0xB8 mapped:0x8066F5F8
int walljump_calculateJumpedOffWallPositionAndVelocity(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];

    if (fielder->wallJumpStatus == 3) {
        fielder->wallActionVelo.x *= fielderActionConstants[14];
        fielder->wallActionVelo.z *= fielderActionConstants[14];
        fielder->pos.x += fielder->wallActionVelo.x;
        fielder->pos.z += fielder->wallActionVelo.z;
        fielder->IntendedLocation.x = fielder->pos.x;
        fielder->IntendedLocation.z = fielder->pos.z;
        fielder->unused_jumpActiveOrRunningCatchRelated = 1;
    } else if (fielder->wallJumpStatus == 4) {
        fielder->currentVelocity = lbl_3_rodata_B20;
        fielder->wallActionCountDown -= 1;
        if (fielder->wallActionCountDown == 0) {
            fielder->wallJumpStatus = 0;
        }
    }

    return 1;
}

// .text:0x0003061C size:0x29C mapped:0x8066F6B0
void fn_3_3061C(void) {
    return;
}

// .text:0x000308B8 size:0x1A0 mapped:0x8066F94C
void fn_3_308B8(int fielderIndex, f32 x, f32 z) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    f32 dx;
    f32 dz;

    fielder->IntendedLocation.x = x;
    fielder->IntendedLocation.z = z;

    dx = x - fielder->pos.x;
    dz = z - fielder->pos.z;

    if (lbl_3_rodata_B20 == dx && lbl_3_rodata_B20 == dz) {
        fielder->currentVelocity = lbl_3_rodata_B20;
        fielder->distanceFromAutoLocation = lbl_3_rodata_B20;
    } else {
        fielder->desiredMovementDirection2 = ATAN2F(dz, dx);
        fielder->distanceFromAutoLocation = fielderSqrt(dx * dx + dz * dz);
        fielder->goingToAutoLocationInd = 1;
    }
}

// .text:0x00030A58 size:0x31C mapped:0x8066FAEC
void fn_3_30A58(void) {
    int i;
    f32 outX;
    f32 outZ;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 dx2;
    f32 dz2;

    for (i = 2; i < 9; i++) {
        fielding_setStartingCoordinates(i, &outX, &outZ);

        dx = g_Fielders[i].pos.x - outX;
        dz = g_Fielders[i].pos.z - outZ;
        dx2 = dx * dx;
        dz2 = dz * dz;
        dist = fielderSqrt(dx2 + dz2);

        if (dist < lbl_3_rodata_B24) {
            outX = g_Fielders[i].pos.x;
            outZ = g_Fielders[i].pos.z;
        }

        g_Fielders[i].IntendedLocation.x = outX;
        g_Fielders[i].IntendedLocation.z = outZ;

        dx = outX - g_Fielders[i].pos.x;
        dz = outZ - g_Fielders[i].pos.z;

        if (dx == lbl_3_rodata_B20 && dz == lbl_3_rodata_B20) {
            g_Fielders[i].currentVelocity = lbl_3_rodata_B20;
            g_Fielders[i].distanceFromAutoLocation = lbl_3_rodata_B20;
        } else {
            g_Fielders[i].desiredMovementDirection2 = ATAN2F(dz, dx);
            g_Fielders[i].distanceFromAutoLocation = fielderSqrt(dx * dx + dz * dz);
            g_Fielders[i].goingToAutoLocationInd = 1;
        }
    }
}

// .text:0x00030D74 size:0x63C mapped:0x8066FE08
void fielding_prePitchAutomovement(void) {
    int i;
    InMemFielder* fielder;

    if (pauseControl[0x1d5] == 0) {
        for (i = 2; i < 9; i++) {
            f32 outZ;
            f32 outX;
            f32 dz;
            f32 dx;
            f32 dx2;
            f32 dz2;
            f32 dist;

            fielder = &g_Fielders[i];
            fielding_setStartingCoordinates(i, &outX, &outZ);

            dx = fielder->pos.x - outX;
            dz = fielder->pos.z - outZ;
            dx2 = dx * dx;
            dz2 = dz * dz;
            dist = fielderSqrt(dx2 + dz2);

            if (dist < lbl_3_rodata_B24) {
                outX = fielder->pos.x;
                outZ = fielder->pos.z;
            }

            fielder->IntendedLocation.x = outX;
            fielder->IntendedLocation.z = outZ;

            dx = outX - fielder->pos.x;
            dz = outZ - fielder->pos.z;

            if (lbl_3_rodata_B20 == dx && lbl_3_rodata_B20 == dz) {
                fielder->currentVelocity = lbl_3_rodata_B20;
                fielder->distanceFromAutoLocation = lbl_3_rodata_B20;
            } else {
                fielder->desiredMovementDirection2 = ATAN2F(dz, dx);
                fielder->distanceFromAutoLocation = fielderSqrt(dx * dx + dz * dz);
                fielder->goingToAutoLocationInd = 1;
            }
        }

        for (i = 2; i < 9; i++) {
            int farFromLocation;

            fielder = &g_Fielders[i];
            farFromLocation = 0;
            if (fielder->distanceFromAutoLocation > lbl_3_rodata_BBC) {
                farFromLocation = 1;
            } else if (fielder->currentVelocity >= lbl_3_rodata_B24 &&
                       fielder->distanceFromAutoLocation > lbl_3_rodata_B7C) {
                farFromLocation = 1;
            }

            if (farFromLocation) {
                if (g_Pitcher.pitchTotalTimeCounter <= 0) {
                    fielder->currentVelocity = lbl_3_rodata_B24;
                } else if (g_Batter.buntStatus >= 1 && g_Batter.buntStatus <= 3 &&
                           (i == 2 || i == 4)) {
                    fielder->currentVelocity += fielder->runningAccelerationFactor;
                    if (fielder->currentVelocity > fielder->joggingSpeed) {
                        fielder->currentVelocity = fielder->joggingSpeed;
                    }
                } else if (((i == 3 && g_Batter.batterHand == BATTING_HAND_RIGHT) ||
                            (i == 5 && g_Batter.batterHand != BATTING_HAND_RIGHT)) &&
                           g_Runners[1].runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE &&
                           g_Runners[1].furthestBaseForcedToGoToOnWalk != 0) {
                    fielder->currentVelocity += fielder->runningAccelerationFactor;
                    if (fielder->currentVelocity > fielder->joggingSpeed) {
                        fielder->currentVelocity = fielder->joggingSpeed;
                    }
                } else if (g_Pitcher.pitchTotalTimeCounter < 60) {
                    fielder->numFramesToGetToAutoLocation = 60 - g_Pitcher.pitchTotalTimeCounter;
                    fielder->currentVelocity =
                        fielder->distanceFromAutoLocation / fielder->numFramesToGetToAutoLocation;
                } else {
                    fielder->numFramesToGetToAutoLocation = 0;
                    fielder->currentVelocity = lbl_3_rodata_B20;
                }

                fielder->distanceFromAutoLocation -= fielder->currentVelocity;

                if (fielder->currentVelocity <= lbl_3_rodata_B20) {
                    fielder->currentVelocity = lbl_3_rodata_B20;
                    fielder->numFramesToGetToAutoLocation = -1;
                } else if (fielder->distanceFromAutoLocation < lbl_3_rodata_B20) {
                    fielder->velocityX = fielder->IntendedLocation.x - fielder->pos.x;
                    fielder->velocityZ = fielder->IntendedLocation.z - fielder->pos.z;
                    fielder->pos.x = fielder->IntendedLocation.x;
                    fielder->pos.z = fielder->IntendedLocation.z;
                    fielder->distanceFromAutoLocation = lbl_3_rodata_B20;
                    fielder->numFramesToGetToAutoLocation = 0;
                } else {
                    fielder->velocityX = fielder->currentVelocity * COSF(fielder->desiredMovementDirection2);
                    fielder->velocityZ = fielder->currentVelocity * SINF(fielder->desiredMovementDirection2);
                    fielder->pos.x += fielder->velocityX;
                    fielder->pos.z += fielder->velocityZ;
                    fielder->numFramesToGetToAutoLocation =
                        (s16)(fielder->distanceFromAutoLocation / fielder->currentVelocity);
                }

                fielder->standingStillInd = 0;
            } else {
                fielder->velocityX = fielder->IntendedLocation.x - fielder->pos.x;
                fielder->velocityZ = fielder->IntendedLocation.z - fielder->pos.z;
                fielder->pos.x = fielder->IntendedLocation.x;
                fielder->pos.z = fielder->IntendedLocation.z;
                fielder->distanceFromAutoLocation = lbl_3_rodata_B20;
                fielder->currentVelocity = lbl_3_rodata_B20;
                fielder->standingStillInd = 1;
                fielder->numFramesToGetToAutoLocation = -1;
            }
        }

        g_Fielders[0].pos.x = g_Pitcher.pitcher.x;
        g_Fielders[0].pos.z = g_Pitcher.pitcher.z;
    }
}

// .text:0x000313B0 size:0x1E4 mapped:0x80670444
void fielding_atBat_SetSomeAutomovements_callCollisionFn(void) {
    return;
}

// .text:0x00031594 size:0xE4 mapped:0x80670628
void atBat_Fielders(void) {
    return;
}

// .text:0x00031678 size:0x3C4 mapped:0x8067070C
void fn_3_31678(void) {
    int i;
    int d1, d2;
    InMemFielder* fielder;

    g_Fielders[0].locationResponsibleForCovering = 0;
    g_Fielders[0].autoMovementFunctionIndex = 1;
    if (autoMovementFunctions[1].code >= 0) {
        g_FieldingLogic.fielderAutoMovementCode[0] = autoMovementFunctions[1].code;
    }

    g_Fielders[0].unknown_writeOnly = 0;
    g_Fielders[0].fielderVeloAdjustmentCode = 0;
    g_Fielders[0].unknown_writeOnly_always0 = 0;
    g_Fielders[0].timeSinceThrowWasCaught = 0;
    g_Fielders[0].fielderTrackingBallState = 0;
    g_FieldingLogic.fielderAssignedLocationIndex[0] = 0;

    if (g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam] != 0) {
        g_Fielders[1].autoMovementFunctionIndex = 18;
        if (autoMovementFunctions[18].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[1] = autoMovementFunctions[18].code;
        }
        g_Fielders[1].unknown_writeOnly = 0;
        g_Fielders[1].fielderVeloAdjustmentCode = 0;
        g_Fielders[1].unknown_writeOnly_always0 = 0;
        g_Fielders[1].timeSinceThrowWasCaught = 0;
        g_Fielders[1].fielderTrackingBallState = 0;
    } else {
        g_Fielders[1].autoMovementFunctionIndex = 15;
        if (autoMovementFunctions[15].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[1] = autoMovementFunctions[15].code;
        }
        g_Fielders[1].unknown_writeOnly = 0;
        g_Fielders[1].fielderVeloAdjustmentCode = 0;
        g_Fielders[1].unknown_writeOnly_always0 = 0;
        g_Fielders[1].timeSinceThrowWasCaught = 0;
        g_Fielders[1].fielderTrackingBallState = 0;
    }

    g_Fielders[2].locationResponsibleForCovering = 1;
    g_Fielders[2].autoMovementFunctionIndex = 1;
    if (autoMovementFunctions[1].code >= 0) {
        g_FieldingLogic.fielderAutoMovementCode[2] = autoMovementFunctions[1].code;
    }

    g_Fielders[2].unknown_writeOnly = 0;
    g_Fielders[2].fielderVeloAdjustmentCode = 0;
    g_Fielders[2].unknown_writeOnly_always0 = 0;
    g_Fielders[2].timeSinceThrowWasCaught = 0;
    g_Fielders[2].fielderTrackingBallState = 0;
    g_FieldingLogic.fielderAssignedLocationIndex[1] = 2;

    g_Fielders[4].locationResponsibleForCovering = 3;
    g_Fielders[4].autoMovementFunctionIndex = 1;
    if (autoMovementFunctions[1].code >= 0) {
        g_FieldingLogic.fielderAutoMovementCode[4] = autoMovementFunctions[1].code;
    }

    d1 = g_Fielders[3].angleOfFieldersStartingPosition - 0x400;
    if (d1 < 0) {
        d1 = -d1;
    }
    d2 = g_Fielders[5].angleOfFieldersStartingPosition - 0x400;
    if (d2 < 0) {
        d2 = -d2;
    }
    if ((f64)d1 < (f64)d2) {
        g_Fielders[3].locationResponsibleForCovering = 2;
        g_Fielders[3].autoMovementFunctionIndex = 1;
        if (autoMovementFunctions[1].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[3] = autoMovementFunctions[1].code;
        }

        g_Fielders[3].unknown_writeOnly = 0;
        g_Fielders[3].fielderVeloAdjustmentCode = 0;
        g_Fielders[3].unknown_writeOnly_always0 = 0;
        g_Fielders[3].timeSinceThrowWasCaught = 0;
        g_Fielders[3].fielderTrackingBallState = 0;
        g_FieldingLogic.fielderAssignedLocationIndex[2] = 3;

        g_Fielders[5].autoMovementFunctionIndex = 0;
        if (autoMovementFunctions[0].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[5] = autoMovementFunctions[0].code;
        }
        g_Fielders[5].unknown_writeOnly = 0;
        g_Fielders[5].fielderVeloAdjustmentCode = 0;
        g_Fielders[5].unknown_writeOnly_always0 = 0;
        g_Fielders[5].timeSinceThrowWasCaught = 0;
        g_Fielders[5].fielderTrackingBallState = 0;
    } else {
        g_Fielders[5].locationResponsibleForCovering = 2;
        g_Fielders[5].autoMovementFunctionIndex = 1;
        if (autoMovementFunctions[1].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[5] = autoMovementFunctions[1].code;
        }

        g_Fielders[5].unknown_writeOnly = 0;
        g_Fielders[5].fielderVeloAdjustmentCode = 0;
        g_Fielders[5].unknown_writeOnly_always0 = 0;
        g_Fielders[5].timeSinceThrowWasCaught = 0;
        g_Fielders[5].fielderTrackingBallState = 0;
        g_FieldingLogic.fielderAssignedLocationIndex[2] = 5;

        g_Fielders[3].autoMovementFunctionIndex = 0;
        if (autoMovementFunctions[0].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[3] = autoMovementFunctions[0].code;
        }
        g_Fielders[3].unknown_writeOnly = 0;
        g_Fielders[3].fielderVeloAdjustmentCode = 0;
        g_Fielders[3].unknown_writeOnly_always0 = 0;
        g_Fielders[3].timeSinceThrowWasCaught = 0;
        g_Fielders[3].fielderTrackingBallState = 0;
    }

    fielder = g_Fielders;
    for (i = 0; i < 9; i++) {
        if (fielder->locationResponsibleForCovering >= 0 && fielder->locationResponsibleForCovering <= 3) {
            fielder->isResponsibleForCoveringALocation = 1;
        }
        fielder++;
    }

    autoMovementDetermineWhatToDo(6, 5);
    autoMovementDetermineWhatToDo(7, 1);
    autoMovementDetermineWhatToDo(8, 4);
}

// .text:0x00031A3C size:0x214 mapped:0x80670AD0
void fn_3_31A3C(void) {
    int i;
    InMemFielder* fielder;
    int angle;

    fielder = g_Fielders;
    for (i = 0; i < 9; i++) {
        if (i == 1) {
            fielder->angleOfFieldersStartingPosition = 0x400;
        } else if (fielder->pos.x == lbl_3_rodata_B20) {
            fielder->angleOfFieldersStartingPosition = 0x400;
        } else {
            angle = (int)(lbl_3_rodata_BC4 * ATAN2F(fielder->pos.z, fielder->pos.x) / const_pi);
            if (angle < 0) {
                angle += 0x800;
            }
            fielder->angleOfFieldersStartingPosition = angle;
        }
        fielder->distanceFromHomePlate = fielderSqrt(fielder->pos.x * fielder->pos.x + fielder->pos.z * fielder->pos.z);
        fielder++;
    }

    fn_3_31678();

    g_Ball.physicsSubstruct.acceleration.x = lbl_3_rodata_B20;
    g_Ball.physicsSubstruct.acceleration.y = lbl_3_rodata_B20;
    g_Ball.physicsSubstruct.acceleration.z = lbl_3_rodata_B20;
    g_Ball.ballState = BALL_STATE_LOOSE;
    g_Ball.AtBat_ContactResult = BALL_RESULT_TYPE_FIELDED;
    g_Ball.fielderAboutToGetBall_hasBall = -1;
    g_Ball.fielderBeingThrownTo = -1;
    g_Ball.ballIsLooseInd_unused = 0;
    g_Ball.looseBall_codeForHowLongUntilSomeoneWillGetIt = 0;
}

// .text:0x00031C50 size:0x440 mapped:0x80670CE4
void fielderActionsOnSteal(void) {
    int i;
    int d1, d2;
    InMemFielder* fielder;

    if (g_Pitcher.pickOffLoc == 5) {
        g_Fielders[0].locationResponsibleForCovering = 5;
        g_FieldingLogic.fielderAssignedLocationIndex[4] = 0;
        g_Fielders[0].autoMovementFunctionIndex = 14;
        if (autoMovementFunctions[14].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[0] = autoMovementFunctions[14].code;
        }

        g_Fielders[0].unknown_writeOnly = 0;
        g_Fielders[0].fielderVeloAdjustmentCode = 0;
        g_Fielders[0].unknown_writeOnly_always0 = 0;
        g_Fielders[0].timeSinceThrowWasCaught = 0;
        g_Fielders[0].fielderTrackingBallState = 0;

        g_Fielders[1].locationResponsibleForCovering = 0;
        g_Fielders[1].autoMovementFunctionIndex = 10;
        if (autoMovementFunctions[10].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[1] = autoMovementFunctions[10].code;
        }

        g_Fielders[1].unknown_writeOnly = 0;
        g_Fielders[1].fielderVeloAdjustmentCode = 0;
        g_Fielders[1].unknown_writeOnly_always0 = 0;
        g_Fielders[1].timeSinceThrowWasCaught = 0;
        g_Fielders[1].fielderTrackingBallState = 0;
        g_FieldingLogic.fielderAssignedLocationIndex[0] = 1;
    } else {
        g_Fielders[0].autoMovementFunctionIndex = 10;
        if (autoMovementFunctions[10].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[0] = autoMovementFunctions[10].code;
        }

        g_Fielders[0].unknown_writeOnly = 0;
        g_Fielders[0].fielderVeloAdjustmentCode = 0;
        g_Fielders[0].unknown_writeOnly_always0 = 0;
        g_Fielders[0].timeSinceThrowWasCaught = 0;
        g_Fielders[0].fielderTrackingBallState = 0;

        g_Fielders[1].locationResponsibleForCovering = 0;
        g_Fielders[1].autoMovementFunctionIndex = 1;
        if (autoMovementFunctions[1].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[1] = autoMovementFunctions[1].code;
        }

        g_Fielders[1].unknown_writeOnly = 0;
        g_Fielders[1].fielderVeloAdjustmentCode = 0;
        g_Fielders[1].unknown_writeOnly_always0 = 0;
        g_Fielders[1].timeSinceThrowWasCaught = 0;
        g_Fielders[1].fielderTrackingBallState = 0;
        g_FieldingLogic.fielderAssignedLocationIndex[0] = 1;
    }

    g_Fielders[2].locationResponsibleForCovering = 1;
    g_Fielders[2].autoMovementFunctionIndex = 1;
    if (autoMovementFunctions[1].code >= 0) {
        g_FieldingLogic.fielderAutoMovementCode[2] = autoMovementFunctions[1].code;
    }

    g_Fielders[2].unknown_writeOnly = 0;
    g_Fielders[2].fielderVeloAdjustmentCode = 0;
    g_Fielders[2].unknown_writeOnly_always0 = 0;
    g_Fielders[2].timeSinceThrowWasCaught = 0;
    g_Fielders[2].fielderTrackingBallState = 0;
    g_FieldingLogic.fielderAssignedLocationIndex[1] = 2;

    g_Fielders[4].locationResponsibleForCovering = 3;
    g_Fielders[4].autoMovementFunctionIndex = 1;
    if (autoMovementFunctions[1].code >= 0) {
        g_FieldingLogic.fielderAutoMovementCode[4] = autoMovementFunctions[1].code;
    }

    d1 = g_Fielders[3].angleOfFieldersStartingPosition - 0x400;
    if (d1 < 0) {
        d1 = -d1;
    }
    d2 = g_Fielders[5].angleOfFieldersStartingPosition - 0x400;
    if (d2 < 0) {
        d2 = -d2;
    }
    if ((f64)d1 < (f64)d2) {
        g_Fielders[3].locationResponsibleForCovering = 2;
        g_Fielders[3].autoMovementFunctionIndex = 1;
        if (autoMovementFunctions[1].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[3] = autoMovementFunctions[1].code;
        }

        g_Fielders[3].unknown_writeOnly = 0;
        g_Fielders[3].fielderVeloAdjustmentCode = 0;
        g_Fielders[3].unknown_writeOnly_always0 = 0;
        g_Fielders[3].timeSinceThrowWasCaught = 0;
        g_Fielders[3].fielderTrackingBallState = 0;
        g_FieldingLogic.fielderAssignedLocationIndex[2] = 3;

        g_Fielders[5].autoMovementFunctionIndex = 0;
        if (autoMovementFunctions[0].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[5] = autoMovementFunctions[0].code;
        }
        g_Fielders[5].unknown_writeOnly = 0;
        g_Fielders[5].fielderVeloAdjustmentCode = 0;
        g_Fielders[5].unknown_writeOnly_always0 = 0;
        g_Fielders[5].timeSinceThrowWasCaught = 0;
        g_Fielders[5].fielderTrackingBallState = 0;
    } else {
        g_Fielders[5].locationResponsibleForCovering = 2;
        g_Fielders[5].autoMovementFunctionIndex = 1;
        if (autoMovementFunctions[1].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[5] = autoMovementFunctions[1].code;
        }

        g_Fielders[5].unknown_writeOnly = 0;
        g_Fielders[5].fielderVeloAdjustmentCode = 0;
        g_Fielders[5].unknown_writeOnly_always0 = 0;
        g_Fielders[5].timeSinceThrowWasCaught = 0;
        g_Fielders[5].fielderTrackingBallState = 0;
        g_FieldingLogic.fielderAssignedLocationIndex[2] = 5;

        g_Fielders[3].autoMovementFunctionIndex = 0;
        if (autoMovementFunctions[0].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[3] = autoMovementFunctions[0].code;
        }
        g_Fielders[3].unknown_writeOnly = 0;
        g_Fielders[3].fielderVeloAdjustmentCode = 0;
        g_Fielders[3].unknown_writeOnly_always0 = 0;
        g_Fielders[3].timeSinceThrowWasCaught = 0;
        g_Fielders[3].fielderTrackingBallState = 0;
    }

    fielder = g_Fielders;
    for (i = 0; i < 9; i++) {
        if (fielder->locationResponsibleForCovering >= 0 && fielder->locationResponsibleForCovering <= 3) {
            fielder->isResponsibleForCoveringALocation = 1;
        }
        fielder++;
    }

    autoMovementDetermineWhatToDo(6, 5);
    autoMovementDetermineWhatToDo(7, 1);
    autoMovementDetermineWhatToDo(8, 4);
}

extern const u8 throwWindUpFrames[];

// .text:0x00032090 size:0x314 mapped:0x80671124
void stealSetFielders(void) {
    InMemFielder* fielder;
    int i;
    int angle;
    u8 code;

    fielder = g_Fielders;
    for (i = 0; i < 9; i++) {
        if (i == 1) {
            fielder->angleOfFieldersStartingPosition = 0x400;
        } else if (fielder->pos.x == lbl_3_rodata_B20) {
            fielder->angleOfFieldersStartingPosition = 0x400;
        } else {
            angle = (int)(lbl_3_rodata_BC4 * ATAN2F(fielder->pos.z, fielder->pos.x) / const_pi);
            if (angle < 0) {
                angle += 0x800;
            }
            fielder->angleOfFieldersStartingPosition = angle;
        }
        fielder->distanceFromHomePlate = fielderSqrt(fielder->pos.x * fielder->pos.x + fielder->pos.z * fielder->pos.z);
        fielder++;
    }

    fielderActionsOnSteal();

    code = g_FieldingLogic.liveBallBcOfPickoffOrStealCd;

    g_Ball.physicsSubstruct.velocity.x = lbl_3_rodata_B20;
    g_Ball.physicsSubstruct.velocity.y = lbl_3_rodata_B20;
    g_Ball.physicsSubstruct.velocity.z = lbl_3_rodata_B20;
    g_Ball.physicsSubstruct.acceleration.x = lbl_3_rodata_B20;
    g_Ball.physicsSubstruct.acceleration.y = lbl_3_rodata_B20;
    g_Ball.physicsSubstruct.acceleration.z = lbl_3_rodata_B20;
    g_Ball.ballState = BALL_STATE_HELD;
    g_Ball.AtBat_ContactResult = BALL_RESULT_TYPE_FIELDED;
    g_Ball.fielderAboutToGetBall_hasBall = 0;
    g_Ball.fielderBeingThrownTo = -1;
    g_Ball.ballIsLooseInd_unused = 0;
    g_Ball.looseBall_codeForHowLongUntilSomeoneWillGetIt = 0;

    if (code == 1 || code == 2) {
        g_Ball.numberOfThrowsDuringPlay = 1;
    }

    if (g_Pitcher.pickOffLoc == 5) {
        g_Ball.AtBat_Contact_BallPos.x = g_Fielders[1].pos.x;
        g_Ball.AtBat_Contact_BallPos.y = g_Fielders[1].pos.y;
        g_Ball.AtBat_Contact_BallPos.z = g_Fielders[1].pos.z;
        g_Ball.fielderWBallIndex = 1;
    } else {
        g_Ball.AtBat_Contact_BallPos.x = g_Fielders[0].pos.x;
        g_Ball.AtBat_Contact_BallPos.y = g_Fielders[0].pos.y;
        g_Ball.AtBat_Contact_BallPos.z = g_Fielders[0].pos.z;
        g_Ball.fielderWBallIndex = 0;
        if (g_Pitcher.pickOffLoc >= 1 && g_Pitcher.pickOffLoc <= 3) {
            g_FieldingLogic.locationThrownTo = g_Pitcher.pickOffLoc;
        }
    }

    g_Fielders[0].throwWindUpFrames =
        throwWindUpFrames[checkFieldingStat(g_GameLogic.teamFielding, g_Fielders[0].rosterLocation,
                                             FIELDING_ABILITY_QUICK_THROW) *
                               3 +
                           2];
}

// .text:0x000323A4 size:0x450 mapped:0x80671438
void determineSelectedfielderOnIFHit_Dribbler(void) {
    InMemFielder* fielder;
    int index;
    int diff;

    if (g_Fielders[1].cantCatchFlyBallInd == 0) {
        if (g_Runners[3].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
            g_Runners[3].runningDirectionCode == 1 &&
            g_Runners[3].fractionalBasesRan >= lbl_3_rodata_BCC &&
            g_Fielders[1].framesToGetToBallLandingSpot > 0) {
            CoordAndDist* future = &g_Ball.physicsSubstruct.futureCoordsAndDist[g_Fielders[1].framesToGetToBallLandingSpot];
            f32 dist = fielderSqrt(future->pos.x * future->pos.x + future->pos.z * future->pos.z);

            if (dist < lbl_3_rodata_B64) {
                g_FieldingLogic.selectedFielder = 1;
                g_FieldingLogic.secondaryFielder = 0;
            } else {
                g_FieldingLogic.selectedFielder = 0;
            }
        } else {
            g_FieldingLogic.selectedFielder = 1;
            g_FieldingLogic.secondaryFielder = 0;
        }
    } else {
        g_FieldingLogic.selectedFielder = 0;
    }

    if (g_Ball.Hit_HorizontalAngle < 0x400) {
        int t3 = g_Fielders[3].framesToGetToBallLandingSpot;
        int t2 = g_Fielders[2].framesToGetToBallLandingSpot;

        if (t3 - 15 < t2) {
            diff = g_Fielders[0].framesToGetToBallLandingSpot - t3;
            if (diff < 0x78) {
                g_FieldingLogic.secondaryFielder = 3;
            } else {
                goto lowSec2;
            }
        } else if (g_Ball.physicsSubstruct.futureCoordsAndDist[t2].pos.z < base_MoundCoordinates[1].z) {
            diff = g_Fielders[0].framesToGetToBallLandingSpot - t2;
            if (diff < 0x50) {
                g_FieldingLogic.secondaryFielder = 2;
            } else {
                goto lowSec2;
            }
        } else {
            diff = g_Fielders[0].framesToGetToBallLandingSpot - t3;
            if (diff < 0x78) {
                g_FieldingLogic.secondaryFielder = 3;
            } else {
                goto lowSec2;
            }
        }
        goto lowSec2Done;
    lowSec2:
        g_FieldingLogic.secondaryFielder = 2;
    lowSec2Done:;
    } else {
        int t5 = g_Fielders[5].framesToGetToBallLandingSpot;
        s16 t4 = g_Fielders[4].framesToGetToBallLandingSpot;

        if (t5 - 15 < t4) {
            diff = g_Fielders[0].framesToGetToBallLandingSpot - t5;
            if (diff < 0x78) {
                g_FieldingLogic.secondaryFielder = 5;
            } else {
                goto highSec4;
            }
        } else if (g_Ball.physicsSubstruct.futureCoordsAndDist[t4].pos.z < base_MoundCoordinates[1].z) {
            if (g_Runners[2].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD && t4 > 0) {
                goto highSec4;
            } else {
                diff = g_Fielders[0].framesToGetToBallLandingSpot - t4;
                if (diff < 0x50) {
                    g_FieldingLogic.secondaryFielder = 4;
                } else {
                    goto highSec4;
                }
            }
        } else {
            diff = g_Fielders[0].framesToGetToBallLandingSpot - t5;
            if (diff < 0x78) {
                g_FieldingLogic.secondaryFielder = 5;
            } else {
                goto highSec4;
            }
        }
        goto highSec4Done;
    highSec4:
        g_FieldingLogic.secondaryFielder = 4;
    highSec4Done:;
    }

    index = g_FieldingLogic.selectedFielder;
    fielder = &g_Fielders[index];
    if (index != -1) {
        fielder->autoMovementFunctionIndex = 21;
        if (autoMovementFunctions[21].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[index] = autoMovementFunctions[21].code;
        }
        fielder->unknown_writeOnly = 0;
        fielder->fielderVeloAdjustmentCode = 0;
        fielder->unknown_writeOnly_always0 = 0;
        fielder->timeSinceThrowWasCaught = 0;
        fielder->fielderTrackingBallState = 0;
    }

    index = g_FieldingLogic.secondaryFielder;
    fielder = &g_Fielders[index];
    if (index >= 0) {
        if (index != -1) {
            fielder->autoMovementFunctionIndex = 22;
            if (autoMovementFunctions[22].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[index] = autoMovementFunctions[22].code;
            }
            fielder->unknown_writeOnly = 0;
            fielder->fielderVeloAdjustmentCode = 0;
            fielder->unknown_writeOnly_always0 = 0;
            fielder->timeSinceThrowWasCaught = 0;
            fielder->fielderTrackingBallState = 0;
        }
    }
}

// .text:0x000327F4 size:0x1C mapped:0x80671888
BOOL fn_3_327F4(void) {
    return g_Ball.hitClassification2 == 1;
}

// .text:0x00032810 size:0x194 mapped:0x806718A4
void selectInitialFielders_linedriveThroughPitcher(void) {
    InMemFielder *f0 = &g_Fielders[0];

    f0->autoMovementFunctionIndex = 21;
    if (autoMovementFunctions[21].code >= 0) {
        g_FieldingLogic.fielderAutoMovementCode[0] = autoMovementFunctions[21].code;
    }
    f0->unknown_writeOnly = 0;
    f0->fielderVeloAdjustmentCode = 0;
    f0->unknown_writeOnly_always0 = 0;
    f0->timeSinceThrowWasCaught = 0;
    f0->fielderTrackingBallState = 0;

    g_FieldingLogic.selectedFielder = 0;
    if (g_Ball.Hit_HorizontalAngle < 0x400) {
        g_FieldingLogic.secondaryFielder = 3;
    } else {
        g_FieldingLogic.secondaryFielder = 5;
    }

    {
        InMemFielder *f = &g_Fielders[3];
        f->autoMovementFunctionIndex = 22;
        if (autoMovementFunctions[22].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[3] = autoMovementFunctions[22].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;
    }

    {
        InMemFielder *f = &g_Fielders[5];
        f->autoMovementFunctionIndex = 22;
        if (autoMovementFunctions[22].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[5] = autoMovementFunctions[22].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;
    }

    g_FieldingLogic.infielderSelectedOnPopFlyInd = 1;
    {
        InMemFielder *f = &g_Fielders[7];
        f->autoMovementFunctionIndex = 23;
        if (autoMovementFunctions[23].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[7] = autoMovementFunctions[23].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;
        g_FieldingLogic.tertiaryFielder = 7;
        g_FieldingLogic.unkFlagMaybeInAir = 1;
    }

    setInitialFielderMovements_CoverBases();
    setInitialFielderMovements_cutoffs();
    setInitialFielderMovements_restOfFielders();
}

// .text:0x000329A4 size:0x6E4 mapped:0x80671A38
void setInitialFielderMovements_foulBall(void) {
    s16 vAngle = g_Ball.Hit_VerticalAngle;
    sAng angle = g_Ball.Hit_HorizontalAngle;
    int index;
    InMemFielder *f;

    if (vAngle >= 0x400 && vAngle <= 0xc00) {
        angle += 0x800;
        if (angle > 0x1000) {
            angle -= 0x1000;
        }
    }

    if (angle >= 0xe00) {
        g_FieldingLogic.selectedFielder = 1;

        f = &g_Fielders[2];
        f->autoMovementFunctionIndex = 16;
        if (autoMovementFunctions[16].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[2] = autoMovementFunctions[16].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;
        goto tail;
    }

    if (angle >= 0xa00) {
        g_FieldingLogic.selectedFielder = 1;
        goto tail;
    }

    if (angle >= 0x800) {
        g_FieldingLogic.selectedFielder = 1;

        f = &g_Fielders[4];
        f->autoMovementFunctionIndex = 16;
        if (autoMovementFunctions[16].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[4] = autoMovementFunctions[16].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;
        goto tail;
    }

    if (angle >= 0x400) {
        if (vAngle < 0x40) {
            g_FieldingLogic.selectedFielder = 4;

            f = &g_Fielders[6];
            f->autoMovementFunctionIndex = 16;
            if (autoMovementFunctions[16].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[6] = autoMovementFunctions[16].code;
            }
            f->unknown_writeOnly = 0;
            f->fielderVeloAdjustmentCode = 0;
            f->unknown_writeOnly_always0 = 0;
            f->timeSinceThrowWasCaught = 0;
            f->fielderTrackingBallState = 0;
            goto tail;
        }

        if (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z < lbl_3_rodata_BA0) {
            g_FieldingLogic.selectedFielder = 1;

            f = &g_Fielders[4];
            f->autoMovementFunctionIndex = 16;
            if (autoMovementFunctions[16].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[4] = autoMovementFunctions[16].code;
            }
            f->unknown_writeOnly = 0;
            f->fielderVeloAdjustmentCode = 0;
            f->unknown_writeOnly_always0 = 0;
            f->timeSinceThrowWasCaught = 0;
            f->fielderTrackingBallState = 0;

            f = &g_Fielders[6];
            f->autoMovementFunctionIndex = 16;
            if (autoMovementFunctions[16].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[6] = autoMovementFunctions[16].code;
            }
            f->unknown_writeOnly = 0;
            f->fielderVeloAdjustmentCode = 0;
            f->unknown_writeOnly_always0 = 0;
            f->timeSinceThrowWasCaught = 0;
            f->fielderTrackingBallState = 0;
            goto tail;
        }

        if (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z < lbl_3_rodata_B9C) {
            g_FieldingLogic.selectedFielder = 4;

            f = &g_Fielders[5];
            f->autoMovementFunctionIndex = 16;
            if (autoMovementFunctions[16].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[5] = autoMovementFunctions[16].code;
            }
            f->unknown_writeOnly = 0;
            f->fielderVeloAdjustmentCode = 0;
            f->unknown_writeOnly_always0 = 0;
            f->timeSinceThrowWasCaught = 0;
            f->fielderTrackingBallState = 0;

            f = &g_Fielders[6];
            f->autoMovementFunctionIndex = 16;
            if (autoMovementFunctions[16].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[6] = autoMovementFunctions[16].code;
            }
            f->unknown_writeOnly = 0;
            f->fielderVeloAdjustmentCode = 0;
            f->unknown_writeOnly_always0 = 0;
            f->timeSinceThrowWasCaught = 0;
            f->fielderTrackingBallState = 0;
            goto tail;
        }

        if (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z < lbl_3_rodata_BD0) {
            g_FieldingLogic.selectedFielder = 5;

            f = &g_Fielders[4];
            f->autoMovementFunctionIndex = 16;
            if (autoMovementFunctions[16].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[4] = autoMovementFunctions[16].code;
            }
            f->unknown_writeOnly = 0;
            f->fielderVeloAdjustmentCode = 0;
            f->unknown_writeOnly_always0 = 0;
            f->timeSinceThrowWasCaught = 0;
            f->fielderTrackingBallState = 0;

            f = &g_Fielders[6];
            f->autoMovementFunctionIndex = 16;
            if (autoMovementFunctions[16].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[6] = autoMovementFunctions[16].code;
            }
            f->unknown_writeOnly = 0;
            f->fielderVeloAdjustmentCode = 0;
            f->unknown_writeOnly_always0 = 0;
            f->timeSinceThrowWasCaught = 0;
            f->fielderTrackingBallState = 0;
            goto tail;
        }

        g_FieldingLogic.selectedFielder = 6;

        f = &g_Fielders[5];
        f->autoMovementFunctionIndex = 16;
        if (autoMovementFunctions[16].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[5] = autoMovementFunctions[16].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;
        goto tail;
    }

    if (vAngle < 0x40) {
        g_FieldingLogic.selectedFielder = 2;

        f = &g_Fielders[8];
        f->autoMovementFunctionIndex = 16;
        if (autoMovementFunctions[16].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[8] = autoMovementFunctions[16].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;
        goto tail;
    }

    if (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z < lbl_3_rodata_BA0) {
        g_FieldingLogic.selectedFielder = 1;

        f = &g_Fielders[2];
        f->autoMovementFunctionIndex = 16;
        if (autoMovementFunctions[16].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[2] = autoMovementFunctions[16].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;

        f = &g_Fielders[8];
        f->autoMovementFunctionIndex = 16;
        if (autoMovementFunctions[16].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[8] = autoMovementFunctions[16].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;
        goto tail;
    }

    if (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z < lbl_3_rodata_B9C) {
        g_FieldingLogic.selectedFielder = 2;

        f = &g_Fielders[3];
        f->autoMovementFunctionIndex = 16;
        if (autoMovementFunctions[16].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[3] = autoMovementFunctions[16].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;

        f = &g_Fielders[8];
        f->autoMovementFunctionIndex = 16;
        if (autoMovementFunctions[16].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[8] = autoMovementFunctions[16].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;
        goto tail;
    }

    if (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z < lbl_3_rodata_BD0) {
        g_FieldingLogic.selectedFielder = 3;

        f = &g_Fielders[2];
        f->autoMovementFunctionIndex = 16;
        if (autoMovementFunctions[16].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[2] = autoMovementFunctions[16].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;

        f = &g_Fielders[8];
        f->autoMovementFunctionIndex = 16;
        if (autoMovementFunctions[16].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[8] = autoMovementFunctions[16].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;
    }

    g_FieldingLogic.selectedFielder = 8;

    f = &g_Fielders[3];
    f->autoMovementFunctionIndex = 16;
    if (autoMovementFunctions[16].code >= 0) {
        g_FieldingLogic.fielderAutoMovementCode[3] = autoMovementFunctions[16].code;
    }
    f->unknown_writeOnly = 0;
    f->fielderVeloAdjustmentCode = 0;
    f->unknown_writeOnly_always0 = 0;
    f->timeSinceThrowWasCaught = 0;
    f->fielderTrackingBallState = 0;

tail:
    index = g_FieldingLogic.selectedFielder;
    f = &g_Fielders[index];
    if (index != -1) {
        f->autoMovementFunctionIndex = 21;
        if (autoMovementFunctions[21].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[index] = autoMovementFunctions[21].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;
    }

    setInitialFielderMovements_CoverBases();
    setInitialFielderMovements_cutoffs();
    setInitialFielderMovements_restOfFielders();
}

// .text:0x00033088 size:0x3D0 mapped:0x8067211C
void chooseSecondaryFielderFromClosestOutfielder(void) {
    int angle;
    int otherFielderIndex;
    InMemFielder* other;
    f32 dx, dz, sqx, sqz;
    f32 magnitude7, magnitudeOther;

    angle = calculateAngleFromCoordinates(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x,
                                           g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);

    otherFielderIndex = (angle >= g_Fielders[7].angleOfFieldersStartingPosition) ? 6 : 8;
    other = &g_Fielders[otherFielderIndex];

    if (g_Fielders[7].catchStrategy == 1) {
        if (other->catchStrategy == 1) {
            if (g_Fielders[7].nonCatchFlyBallStratInd == 0 && other->nonCatchFlyBallStratInd == 0 &&
                g_Fielders[7].framesToGetToBallLandingSpot == other->framesToGetToBallLandingSpot) {
                dx = g_Ball.physicsSubstruct.futureCoordsAndDist[g_Fielders[7].framesToGetToBallLandingSpot].pos.x -
                     g_Fielders[7].pos.x;
                dz = g_Ball.physicsSubstruct.futureCoordsAndDist[g_Fielders[7].framesToGetToBallLandingSpot].pos.z -
                     g_Fielders[7].pos.z;
                sqx = dx * dx;
                sqz = dz * dz;
                magnitude7 = fielderSqrt(sqx + sqz);

                dx = g_Ball.physicsSubstruct.futureCoordsAndDist[other->framesToGetToBallLandingSpot].pos.x -
                     other->pos.x;
                dz = g_Ball.physicsSubstruct.futureCoordsAndDist[other->framesToGetToBallLandingSpot].pos.z -
                     other->pos.z;
                sqx = dx * dx;
                sqz = dz * dz;
                magnitudeOther = fielderSqrt(sqx + sqz);

                if (magnitude7 >= magnitudeOther) {
                    g_FieldingLogic.secondaryFielder = otherFielderIndex;
                } else {
                    g_FieldingLogic.secondaryFielder = 7;
                }
            } else {
                if (g_Fielders[7].framesToGetToBallLandingSpot > other->framesToGetToBallLandingSpot) {
                    g_FieldingLogic.secondaryFielder = otherFielderIndex;
                } else {
                    g_FieldingLogic.secondaryFielder = 7;
                }
            }
        } else {
            g_FieldingLogic.secondaryFielder = 7;
        }
    } else {
        if (other->catchStrategy == 1) {
            g_FieldingLogic.secondaryFielder = otherFielderIndex;
        } else {
            int diff7, diffOther;

            diff7 = angle - g_Fielders[7].angleOfFieldersStartingPosition;
            if (diff7 < 0) {
                diff7 = -diff7;
            }
            diffOther = angle - other->angleOfFieldersStartingPosition;
            if (diffOther < 0) {
                diffOther = -diffOther;
            }
            if (diff7 < diffOther + 0x60) {
                g_FieldingLogic.secondaryFielder = 7;
            } else {
                g_FieldingLogic.secondaryFielder = otherFielderIndex;
            }
        }
    }
}

// .text:0x00033458 size:0x94 mapped:0x806724EC
void fn_3_33458(void) {
    InMemFielder *f;
    int index;

    setInitialFielderMovements_generalCase(1);
    chooseSecondaryFielderFromClosestOutfielder();

    index = g_FieldingLogic.secondaryFielder;
    f = &g_Fielders[index];
    if (index != -1) {
        f->autoMovementFunctionIndex = 22;
        if (autoMovementFunctions[22].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[index] = autoMovementFunctions[22].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;
    }

    setInitialFielderMovements_CoverBases();
    setInitialFielderMovements_cutoffs();
    setInitialFielderMovements_restOfFielders();
}

// .text:0x000334EC size:0x8B0 mapped:0x80672580
void setInitialFielderMovements_generalCase(int noSecondaryFielderLogic) {
    InMemFielder *f;
    int index;

    if (g_Ball.hitClassification2 == 1) {
        determineSelectedfielderOnIFHit_Dribbler();
        goto tail;
    }

    if (g_Ball.maxYOfHit >= lbl_3_rodata_B64 && noSecondaryFielderLogic == 0) {
        int i;
        int bestIdx;
        f32 dx, dz;
        f32 sqx, sqz;
        f32 bestDist;

        dx = g_Fielders[0].pos.x - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
        dz = g_Fielders[0].pos.z - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
        sqx = dx * dx;
        sqz = dz * dz;
        bestDist = fielderSqrt(sqx + sqz) + lbl_3_rodata_B78;
        bestIdx = 0;

        for (i = 1; i < 6; i++) {
            f32 dist;

            dx = g_Fielders[i].pos.x - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
            dz = g_Fielders[i].pos.z - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
            sqx = dx * dx;
            sqz = dz * dz;
            dist = fielderSqrt(sqx + sqz);
            if (i == 3 || i == 5) {
                dist -= lbl_3_rodata_B78;
            }
            if (dist < bestDist) {
                bestDist = dist;
                bestIdx = i;
            }
        }

        g_FieldingLogic.selectedFielder = bestIdx;
        f = &g_Fielders[bestIdx];
        if (bestIdx != -1) {
            f->autoMovementFunctionIndex = 21;
            if (autoMovementFunctions[21].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[bestIdx] = autoMovementFunctions[21].code;
            }
            f->unknown_writeOnly = 0;
            f->fielderVeloAdjustmentCode = 0;
            f->unknown_writeOnly_always0 = 0;
            f->timeSinceThrowWasCaught = 0;
            f->fielderTrackingBallState = 0;
        }

        if (g_FieldingLogic.selectedFielder == 3 || g_FieldingLogic.selectedFielder == 5) {
            if (g_Ball.landingSpotAngle >= 0x3b8 && g_Ball.landingSpotAngle <= 0x448) {
                if (g_FieldingLogic.selectedFielder == 3) {
                    g_FieldingLogic.secondaryFielder = 5;
                } else {
                    g_FieldingLogic.secondaryFielder = 3;
                }
                g_FieldingLogic.infielderSelectedOnPopFlyInd = 1;
            }
        }
    } else {
        s16 power = g_Ball.Hit_HorizontalPower;
        int spread;
        sAng angle;

        spread = 0x8c - power;
        if (spread < 0) {
            spread = 0;
        }
        if (spread > 0x40) {
            spread = 0x40;
        }

        angle = g_Ball.Hit_HorizontalAngle;

        if (angle >= 0x3a8 - spread && angle < spread + 0x458 && noSecondaryFielderLogic == 0) {
            int sf3, sf5, avg;

            g_FieldingLogic.selectedFielder = 0;

            sf3 = g_Fielders[3].angleOfFieldersStartingPosition;
            sf5 = g_Fielders[5].angleOfFieldersStartingPosition;
            avg = sf3 + (sf5 - sf3) / 2;
            if (angle < avg) {
                g_FieldingLogic.secondaryFielder = 3;
            } else {
                g_FieldingLogic.secondaryFielder = 5;
            }

            if (g_Ball.landingSpotAngle >= 0x3b8 && g_Ball.landingSpotAngle <= 0x448) {
                g_FieldingLogic.infielderSelectedOnPopFlyInd = 1;
                if (g_FieldingLogic.secondaryFielder == 3) {
                    f = &g_Fielders[5];
                    f->autoMovementFunctionIndex = 22;
                    if (autoMovementFunctions[22].code >= 0) {
                        g_FieldingLogic.fielderAutoMovementCode[5] = autoMovementFunctions[22].code;
                    }
                    f->unknown_writeOnly = 0;
                    f->fielderVeloAdjustmentCode = 0;
                    f->unknown_writeOnly_always0 = 0;
                    f->timeSinceThrowWasCaught = 0;
                    f->fielderTrackingBallState = 0;
                } else {
                    f = &g_Fielders[3];
                    f->autoMovementFunctionIndex = 22;
                    if (autoMovementFunctions[22].code >= 0) {
                        g_FieldingLogic.fielderAutoMovementCode[3] = autoMovementFunctions[22].code;
                    }
                    f->unknown_writeOnly = 0;
                    f->fielderVeloAdjustmentCode = 0;
                    f->unknown_writeOnly_always0 = 0;
                    f->timeSinceThrowWasCaught = 0;
                    f->fielderTrackingBallState = 0;
                }
            }
            goto tail;
        } else {
            int f2, f3, f4, f5;
            int th;

            f2 = g_Fielders[2].angleOfFieldersStartingPosition;
            f3 = g_Fielders[3].angleOfFieldersStartingPosition;

            th = f2 + (f3 - f2) / 7;
            if (angle < th) {
                g_FieldingLogic.selectedFielder = 2;
                goto tail;
            }

            th = f2 + (f3 - f2) * 2 / 5;
            if (angle < th) {
                g_FieldingLogic.selectedFielder = 2;
                g_FieldingLogic.secondaryFielder = 3;

                f = &g_Fielders[3];
                f->autoMovementFunctionIndex = 22;
                if (autoMovementFunctions[22].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[3] = autoMovementFunctions[22].code;
                }
                f->unknown_writeOnly = 0;
                f->fielderVeloAdjustmentCode = 0;
                f->unknown_writeOnly_always0 = 0;
                f->timeSinceThrowWasCaught = 0;
                f->fielderTrackingBallState = 0;
                goto tail;
            }

            f5 = g_Fielders[5].angleOfFieldersStartingPosition;
            th = f3 + (f5 - f3) / 2;
            if (angle < th) {
                g_FieldingLogic.selectedFielder = 3;
                goto tail;
            }

            f4 = g_Fielders[4].angleOfFieldersStartingPosition;
            th = f5 + (f4 - f5) * 3 / 5;
            if (angle < th) {
                g_FieldingLogic.selectedFielder = 5;
                goto tail;
            }

            th = f4 - (f4 - f5) / 5;
            if (angle < th) {
                g_FieldingLogic.selectedFielder = 4;
                g_FieldingLogic.secondaryFielder = 5;

                f = &g_Fielders[5];
                f->autoMovementFunctionIndex = 22;
                if (autoMovementFunctions[22].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[5] = autoMovementFunctions[22].code;
                }
                f->unknown_writeOnly = 0;
                f->fielderVeloAdjustmentCode = 0;
                f->unknown_writeOnly_always0 = 0;
                f->timeSinceThrowWasCaught = 0;
                f->fielderTrackingBallState = 0;
                goto tail;
            }

            g_FieldingLogic.selectedFielder = 4;
        }
    }

tail:
    index = g_FieldingLogic.selectedFielder;
    f = &g_Fielders[index];
    if (index != -1) {
        f->autoMovementFunctionIndex = 21;
        if (autoMovementFunctions[21].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[index] = autoMovementFunctions[21].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;
    }

    if (noSecondaryFielderLogic == 0) {
        s16 oldSecondary = g_FieldingLogic.secondaryFielder;
        int newSecondary;

        if (oldSecondary < 0) {
            chooseSecondaryFielderFromClosestOutfielder();
            newSecondary = g_FieldingLogic.secondaryFielder;
            f = &g_Fielders[newSecondary];
            if (newSecondary != -1) {
                f->autoMovementFunctionIndex = 22;
                if (autoMovementFunctions[22].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[newSecondary] = autoMovementFunctions[22].code;
                }
                f->unknown_writeOnly = 0;
                f->fielderVeloAdjustmentCode = 0;
                f->unknown_writeOnly_always0 = 0;
                f->timeSinceThrowWasCaught = 0;
                f->fielderTrackingBallState = 0;
            }
        } else {
            chooseSecondaryFielderFromClosestOutfielder();
            newSecondary = g_FieldingLogic.secondaryFielder;
            g_FieldingLogic.tertiaryFielder = newSecondary;
            g_FieldingLogic.secondaryFielder = oldSecondary;

            f = &g_Fielders[oldSecondary];
            if (oldSecondary != -1) {
                f->autoMovementFunctionIndex = 22;
                if (autoMovementFunctions[22].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[oldSecondary] = autoMovementFunctions[22].code;
                }
                f->unknown_writeOnly = 0;
                f->fielderVeloAdjustmentCode = 0;
                f->unknown_writeOnly_always0 = 0;
                f->timeSinceThrowWasCaught = 0;
                f->fielderTrackingBallState = 0;
            }

            f = &g_Fielders[g_FieldingLogic.tertiaryFielder];
            if (g_FieldingLogic.tertiaryFielder != -1) {
                f->autoMovementFunctionIndex = 23;
                if (autoMovementFunctions[23].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[g_FieldingLogic.tertiaryFielder] = autoMovementFunctions[23].code;
                }
                f->unknown_writeOnly = 0;
                f->fielderVeloAdjustmentCode = 0;
                f->unknown_writeOnly_always0 = 0;
                f->timeSinceThrowWasCaught = 0;
                f->fielderTrackingBallState = 0;
            }

            g_FieldingLogic.unkFlagMaybeInAir = 1;
        }

        setInitialFielderMovements_CoverBases();
        setInitialFielderMovements_cutoffs();
        setInitialFielderMovements_restOfFielders();
    }
}

// .text:0x00033D9C size:0x34 mapped:0x80672E30
#pragma dont_inline on
void fn_3_33D9C(void) {
    autoMovementDetermineWhatToDo(6, 7);
    autoMovementDetermineWhatToDo(8, 6);
}
#pragma dont_inline reset

// .text:0x00033DD0 size:0x418 mapped:0x80672E64
void determinePrimaryAndSecondaryOutFielders(int *primaryFielder, int *secondaryFielder) {
    int angle;
    int defaultFielder;
    InMemFielder *outfielder;
    int strat7, stratDefault;
    int similarDistanceInd;
    f32 diff;
    int diff7, diffDefault, diffFrames;
    u8 cs;

    *secondaryFielder = -1;

    angle = calculateAngleFromCoordinates(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x,
                                           g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);

    defaultFielder = 6;

    if (angle > g_Fielders[6].angleOfFieldersStartingPosition) {
        *primaryFielder = 6;
        return;
    }
    if (angle < g_Fielders[8].angleOfFieldersStartingPosition) {
        *primaryFielder = 8;
        return;
    }
    if (angle < g_Fielders[7].angleOfFieldersStartingPosition) {
        defaultFielder = 8;
    }

    outfielder = &g_Fielders[defaultFielder];

    if (g_Fielders[7].nonCatchFlyBallStratInd != 0) {
        cs = g_Fielders[7].catchStrategy;
        strat7 = (cs == 1) ? 1 : (cs == 2) ? 2 : (cs == 3) ? 3 : 10;
    } else {
        strat7 = 0;
    }

    if (outfielder->nonCatchFlyBallStratInd != 0) {
        cs = outfielder->catchStrategy;
        stratDefault = (cs == 1) ? 1 : (cs == 2) ? 2 : (cs == 3) ? 3 : 10;
    } else {
        stratDefault = 0;
    }

    similarDistanceInd = 0;
    if (g_Ball.wallAndBallIntersectionDistFromHome > lbl_3_rodata_BD0) {
        diff = g_Fielders[7].distanceFromLandingSpot - outfielder->distanceFromLandingSpot;
        if (diff < lbl_3_rodata_B20) {
            diff = -diff;
        }
        if (diff < lbl_3_rodata_BA0) {
            similarDistanceInd = 1;
        }
    }

    if ((strat7 == stratDefault && strat7 < 10) || similarDistanceInd) {
        if (strat7 == 0) {
            if (g_Fielders[7].distanceFromLandingSpot <= outfielder->distanceFromLandingSpot) {
                *primaryFielder = 7;
                diff = outfielder->distanceFromLandingSpot - g_Fielders[7].distanceFromLandingSpot;
                if (diff < lbl_3_rodata_BA0) {
                    *secondaryFielder = defaultFielder;
                }
            } else {
                *primaryFielder = defaultFielder;
                diff = g_Fielders[7].distanceFromLandingSpot - outfielder->distanceFromLandingSpot;
                if (diff < lbl_3_rodata_BA0) {
                    *secondaryFielder = 7;
                }
            }
            return;
        } else if (strat7 == 1) {
            if (g_Fielders[7].framesToGetToBallLandingSpot <= outfielder->framesToGetToBallLandingSpot) {
                *primaryFielder = 7;
                diffFrames = outfielder->framesToGetToBallLandingSpot - g_Fielders[7].framesToGetToBallLandingSpot;
                if (diffFrames < 0x2d) {
                    *secondaryFielder = defaultFielder;
                }
            } else {
                *primaryFielder = defaultFielder;
                diffFrames = g_Fielders[7].framesToGetToBallLandingSpot - outfielder->framesToGetToBallLandingSpot;
                if (diffFrames < 0x2d) {
                    *secondaryFielder = 7;
                }
            }
            return;
        }
        goto sharedTail;
    }

    if (strat7 < stratDefault) {
        if (strat7 == 0) {
            *primaryFielder = 7;
            if (stratDefault == 1) {
                diffFrames = outfielder->framesToGetToBallLandingSpot - g_Fielders[7].framesToGetToBallLandingSpot;
                if (diffFrames < 0x1e) {
                    *secondaryFielder = defaultFielder;
                }
            }
            return;
        } else if (strat7 == 1) {
            *primaryFielder = 7;
            return;
        } else if (stratDefault == 10) {
            *primaryFielder = 7;
            return;
        }
    } else {
        if (strat7 == stratDefault) {
            goto sharedTail;
        }
        if (stratDefault == 0) {
            *primaryFielder = defaultFielder;
            if (strat7 == 1) {
                diffFrames = g_Fielders[7].framesToGetToBallLandingSpot - outfielder->framesToGetToBallLandingSpot;
                if (diffFrames < 0x1e) {
                    *secondaryFielder = 7;
                }
            }
            return;
        } else if (stratDefault == 1) {
            *primaryFielder = defaultFielder;
            return;
        } else if (strat7 == 10) {
            *primaryFielder = defaultFielder;
            return;
        }
    }

sharedTail:
    if (g_Ball.landingSpotZoneAwayFromHome >= 3) {
        diff = g_Fielders[7].distanceFromLandingSpot - outfielder->distanceFromLandingSpot;
        if (diff < lbl_3_rodata_B20) {
            *primaryFielder = 7;
            if (diff > lbl_3_rodata_BD4) {
                *secondaryFielder = defaultFielder;
            }
        } else {
            *primaryFielder = defaultFielder;
            if (diff < lbl_3_rodata_BA0) {
                *secondaryFielder = 7;
            }
        }
        return;
    }

    diffDefault = angle - outfielder->angleOfFieldersStartingPosition;
    if (diffDefault < 0) {
        diffDefault = -diffDefault;
    }
    diff7 = angle - g_Fielders[7].angleOfFieldersStartingPosition;
    if (diff7 < 0) {
        diff7 = -diff7;
    }
    if (diff7 < diffDefault + 0x40) {
        *primaryFielder = 7;
        *secondaryFielder = defaultFielder;
    } else {
        *primaryFielder = defaultFielder;
        *secondaryFielder = 7;
    }
}

// .text:0x000341E8 size:0x268 mapped:0x8067327C
void setInitialFielderMovements_DeepFly(void) {
    int primaryFielder, secondaryFielder;
    int index1, index2;
    InMemFielder *f1, *f2;

    determinePrimaryAndSecondaryOutFielders(&primaryFielder, &secondaryFielder);

    g_FieldingLogic.selectedFielder = primaryFielder;
    g_FieldingLogic.secondaryFielder = secondaryFielder;

    index1 = g_FieldingLogic.selectedFielder;
    f1 = &g_Fielders[index1];
    if (index1 != -1) {
        f1->autoMovementFunctionIndex = 22;
        if (autoMovementFunctions[22].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[index1] = autoMovementFunctions[22].code;
        }
    }
    f1->unknown_writeOnly = 0;
    f1->fielderVeloAdjustmentCode = 0;
    f1->unknown_writeOnly_always0 = 0;
    f1->timeSinceThrowWasCaught = 0;
    f1->fielderTrackingBallState = 0;

    index2 = g_FieldingLogic.secondaryFielder;
    f2 = &g_Fielders[index2];
    if (index2 != -1) {
        f2->autoMovementFunctionIndex = 22;
        if (autoMovementFunctions[22].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[index2] = autoMovementFunctions[22].code;
        }
    }
    f2->unknown_writeOnly = 0;
    f2->fielderVeloAdjustmentCode = 0;
    f2->unknown_writeOnly_always0 = 0;
    f2->timeSinceThrowWasCaught = 0;
    f2->fielderTrackingBallState = 0;

    if (g_FieldingLogic.secondaryFielder >= 0) {
        g_FieldingLogic.unkFlagMaybeInAir = 1;
    } else {
        int angle = calculateAngleFromCoordinates(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x,
                                                   g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);
        if (g_FieldingLogic.selectedFielder == 7) {
            if (angle < 0x400) {
                InMemFielder *f = &g_Fielders[8];
                f->autoMovementFunctionIndex = 24;
                if (autoMovementFunctions[24].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[8] = autoMovementFunctions[24].code;
                }
                f->unknown_writeOnly = 0;
                f->fielderVeloAdjustmentCode = 0;
                f->unknown_writeOnly_always0 = 0;
                f->timeSinceThrowWasCaught = 0;
                f->fielderTrackingBallState = 0;
                g_FieldingLogic.someFielderIndex = 8;
            } else {
                InMemFielder *f = &g_Fielders[6];
                f->autoMovementFunctionIndex = 24;
                if (autoMovementFunctions[24].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[6] = autoMovementFunctions[24].code;
                }
                f->unknown_writeOnly = 0;
                f->fielderVeloAdjustmentCode = 0;
                f->unknown_writeOnly_always0 = 0;
                f->timeSinceThrowWasCaught = 0;
                f->fielderTrackingBallState = 0;
                g_FieldingLogic.someFielderIndex = 6;
            }
        } else {
            InMemFielder *f = &g_Fielders[7];
            f->autoMovementFunctionIndex = 24;
            if (autoMovementFunctions[24].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[7] = autoMovementFunctions[24].code;
            }
            f->unknown_writeOnly = 0;
            f->fielderVeloAdjustmentCode = 0;
            f->unknown_writeOnly_always0 = 0;
            f->timeSinceThrowWasCaught = 0;
            f->fielderTrackingBallState = 0;
            g_FieldingLogic.someFielderIndex = 7;
        }
    }

    setInitialFielderMovements_CoverBases();
    setInitialFielderMovements_cutoffs();
    fn_3_33D9C();
}

// .text:0x00034450 size:0x5F0 mapped:0x806734E4
void humanTeamFieldingFirstFrameAfterHit(void) {
    return;
}

// .text:0x00034A40 size:0x12E8 mapped:0x80673AD4
void decideHowToTrackFoulBall(void) {
    return;
}

// .text:0x00035D28 size:0xF4 mapped:0x80674DBC
void autoMovement16_trackFoulBall(int fielderIndex) {
    return;
}

// .text:0x00035E1C size:0x3BC mapped:0x80674EB0
void setPlayerWhoCanInterceptThrow(void) {
    InMemFielder* fielder;
    int throwZone = 0;
    int result = -1;
    int candidate1 = -1;
    int i;
    f32 dx;
    f32 dz;
    f32 sqx;
    f32 sqz;
    f32 dist;

    if (g_Ball.ballZoneAwayFromHome < 3) {
        goto checkZoneLow;
    }
    if (g_FieldingLogic.locationThrownTo != 0) {
        goto checkZoneLow;
    }
    throwZone = 1;
    goto zoneDone;

checkZoneLow:
    if (g_Ball.ballZoneAwayFromHome <= 1) {
        throwZone = 2;
    }

zoneDone:
    for (i = 0; i < 9; i++) {
        if (g_FieldingLogic.fielderAutoMovementCode[i] == 2) {
            continue;
        }
        if (i == g_Ball.throwingFielder) {
            continue;
        }
        if (candidate1 == -1) {
            candidate1 = i;
        } else {
            result = i;
            break;
        }
    }

    if (throwZone == 0) {
        goto useDistanceFallback;
    }
    if (candidate1 < 0) {
        goto useDistanceFallback;
    }
    if (result < 0) {
        goto useDistanceFallback;
    }
    if (g_Fielders[candidate1].distanceToMound < g_Fielders[result].distanceToMound) {
        goto haveCandidate;
    }
    candidate1 = result;
    goto haveCandidate;

useDistanceFallback:
    dx = g_Ball.throwTarget.x - g_Ball.AtBat_Contact_BallPos.x;
    dz = g_Ball.throwTarget.z - g_Ball.AtBat_Contact_BallPos.z;
    sqx = dx * dx;
    sqz = dz * dz;
    dist = fielderSqrt(sqx + sqz);

    if (candidate1 >= 0 && dist < g_Fielders[candidate1].distanceFromBall) {
        candidate1 = -1;
    }
    if (result >= 0 && dist < g_Fielders[result].distanceFromBall) {
        result = -1;
    }
    if (candidate1 < 0) {
        candidate1 = result;
        result = -1;
    }
    if (candidate1 < 0) {
        return;
    }
    if (result < 0) {
        goto haveCandidate;
    }
    if (g_Fielders[candidate1].groundDistanceFromBall <= g_Fielders[result].groundDistanceFromBall) {
        goto haveCandidate;
    }
    candidate1 = result;

haveCandidate:
    if (candidate1 < 0) {
        return;
    }

    if (throwZone == 2) {
        if (g_Fielders[candidate1].groundDistanceFromBall > lbl_3_rodata_B68) {
            return;
        }
    } else if (throwZone == 0) {
        if (g_Fielders[candidate1].groundDistanceFromBall > lbl_3_rodata_B8C) {
            return;
        }
    }

    if (candidate1 != -1) {
        fielder = &g_Fielders[candidate1];
        fielder->autoMovementFunctionIndex = 25;
        if (autoMovementFunctions[25].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[candidate1] = autoMovementFunctions[25].code;
        }
        fielder->unknown_writeOnly = 0;
        fielder->fielderVeloAdjustmentCode = 0;
        fielder->unknown_writeOnly_always0 = 0;
        fielder->timeSinceThrowWasCaught = 0;
        fielder->fielderTrackingBallState = 0;
    }
    g_FieldingLogic.interceptThrowFielder = candidate1;
}

// .text:0x000361D8 size:0x3F8 mapped:0x8067526C
int SelectClosestFielder2(f32 x, f32 z) {
    InMemFielder* f;
    int i;
    int rank1Index = 0;
    int rank2Index = 0;
    int rank3Index = 0;
    int rank4Index = 0;
    int rank1Angle;
    int rank2Angle;
    int rank3Angle;
    int rank4Angle;
    f32 rank4Dist = lbl_3_rodata_BA4;
    f32 rank3Dist = rank4Dist;
    f32 rank2Dist = rank4Dist;
    f32 rank1Dist = rank4Dist;
    int result;

    for (f = &g_Fielders[0], i = 0; i < 9; f++, i++) {
        f32 dx = f->pos.x - x;
        f32 dz = f->pos.z - z;
        f32 dist = fielderSqrt(dx * dx + dz * dz);
        int angle = calculateAngleFromCoordinates(dx, dz);

        if (rank1Dist > dist) {
            rank3Dist = rank2Dist;
            rank3Index = rank2Index;
            rank3Angle = rank2Angle;
            rank2Dist = rank1Dist;
            rank2Index = rank1Index;
            rank2Angle = rank1Angle;
            rank1Dist = dist;
            rank1Index = i;
            rank1Angle = angle;
        } else if (rank2Dist > dist) {
            rank3Dist = rank2Dist;
            rank3Index = rank2Index;
            rank3Angle = rank2Angle;
            rank2Dist = dist;
            rank2Index = i;
            rank2Angle = angle;
        } else if (rank3Dist > dist) {
            rank4Dist = rank3Dist;
            rank4Index = rank3Index;
            rank4Angle = rank3Angle;
            rank3Dist = dist;
            rank3Index = i;
            rank3Angle = angle;
        } else if (rank4Dist > dist) {
            rank4Dist = dist;
            rank4Index = i;
            rank4Angle = angle;
        }
    }

    if (rank4Dist - lbl_3_rodata_B70 < rank3Dist) {
        if (getDifferenceInAngle(rank2Angle, rank3Angle) < 0x180) {
            if (getDifferenceInAngle(rank1Angle, rank4Angle) > 0x200 &&
                getDifferenceInAngle(rank2Angle, rank4Angle) > 0x200) {
                rank3Index = rank4Index;
            }
        } else if (getDifferenceInAngle(rank1Angle, rank3Angle) < 0x180) {
            if (getDifferenceInAngle(rank1Angle, rank4Angle) > 0x200 &&
                getDifferenceInAngle(rank2Angle, rank4Angle) > 0x200) {
                rank3Index = rank4Index;
            }
        } else {
            if (getDifferenceInAngle(rank1Angle, rank2Angle) < 0x180 &&
                getDifferenceInAngle(rank1Angle, rank4Angle) > 0x200 &&
                getDifferenceInAngle(rank3Angle, rank4Angle) > 0x200) {
                rank2Index = rank3Index;
                rank3Index = rank4Index;
            }
        }
    }

    result = selectBestFielder(rank2Index, rank3Index, 1, x, z);
    if (result == -1) {
        return rank1Index;
    }

    if (g_FieldingLogic.selectedFielder < 0) {
        rank1Index = selectBestFielder(rank1Index, result, 1, x, z);
    } else {
        rank1Index = selectBestFielder(rank1Index, result, 0, x, z);
    }
    return rank1Index;
}

// .text:0x000365D0 size:0xA8 mapped:0x80675664
int fn_3_365D0(int fielderIndexA, int fielderIndexB, int fielderIndexC, f32 x, f32 z) {
    int result = selectBestFielder(fielderIndexB, fielderIndexC, 1, x, z);

    if (result == -1) {
        return fielderIndexA;
    }

    if (g_FieldingLogic.selectedFielder < 0) {
        return selectBestFielder(fielderIndexA, result, 1, x, z);
    }
    return selectBestFielder(fielderIndexA, result, 0, x, z);
}

// .text:0x00036678 size:0xA9C mapped:0x8067570C
int selectBestFielder(int fielderIndexA, int fielderIndexB, int flag, f32 x, f32 z) {
    s16 angleA;
    s16 angleB;
    int angleDiff;
    f32 dx;
    f32 dz;
    f32 distA;
    f32 distB;
    f32 distDiff;
    int stickDiffA;
    int stickDiffB;

    if (currentStickDirection < 0) {
        return -1;
    }

    angleA = radToShortAngle(atan2(z - g_Fielders[fielderIndexA].pos.z, x - g_Fielders[fielderIndexA].pos.x));

    angleB = radToShortAngle(atan2(z - g_Fielders[fielderIndexB].pos.z, x - g_Fielders[fielderIndexB].pos.x));

    angleDiff = getDifferenceInAngle(angleA, angleB);

    dx = g_Fielders[fielderIndexA].pos.x - x;
    dz = g_Fielders[fielderIndexA].pos.z - z;
    {
        f32 sqx = dx * dx;
        f32 sqz = dz * dz;
        distA = fielderSqrt(sqx + sqz);
    }

    dx = g_Fielders[fielderIndexB].pos.x - x;
    dz = g_Fielders[fielderIndexB].pos.z - z;
    {
        f32 sqx = dx * dx;
        f32 sqz = dz * dz;
        distB = fielderSqrt(sqx + sqz);
    }

    if (angleDiff <= 0x100) {
        return (distA < distB) ? fielderIndexA : fielderIndexB;
    }

    if (flag < 2) {
        if (fielderIndexA == g_FieldingLogic.selectedFielder) {
            distA -= lbl_3_rodata_B78;
            if (distA < lbl_3_rodata_B20) {
                distA = lbl_3_rodata_B20;
            }
        } else if (fielderIndexB == g_FieldingLogic.selectedFielder) {
            distB -= lbl_3_rodata_B78;
            if (distB < lbl_3_rodata_B20) {
                distB = lbl_3_rodata_B20;
            }
        }

        if (fielderControlStick_continuousAngleHistory[3] >= 0) {
            int stickHistDiff = fielderControlStick_continuousAngleHistory[0] -
                                 fielderControlStick_continuousAngleHistory[3];
            stickHistDiff = (stickHistDiff ^ (stickHistDiff >> 31)) - (stickHistDiff >> 31);
            if (stickHistDiff > 0x800) {
                stickHistDiff = 0x1000 - stickHistDiff;
            }

            if (stickHistDiff <= 0x400) {
                int biasedIdx = -1;

                if (fielderIndexA == g_FieldingLogic.selectedFielder) {
                    biasedIdx = fielderIndexA;
                }
                if (fielderIndexB == g_FieldingLogic.selectedFielder) {
                    biasedIdx = fielderIndexB;
                }

                if (biasedIdx >= 0) {
                    f32 distIdx;
                    f32 distLastFrame;

                    dx = g_Fielders[biasedIdx].pos.x - x;
                    dz = g_Fielders[biasedIdx].pos.z - z;
                    {
                        f32 sqx = dx * dx;
                        f32 sqz = dz * dz;
                        distIdx = fielderSqrt(sqx + sqz);
                    }

                    dx = g_Fielders[biasedIdx].posXLastFrame - x;
                    dz = g_Fielders[biasedIdx].posZLastFrame - z;
                    {
                        f32 sqx = dx * dx;
                        f32 sqz = dz * dz;
                        distLastFrame = fielderSqrt(sqx + sqz);
                    }

                    if (distIdx > distLastFrame) {
                        goto skipBiasAdjustment;
                    }
                }

                {
                    f32 distHome = fielderSqrt(x * x + z * z);
                    f32 bias;
                    f32 threshold;

                    if (distHome < lbl_3_rodata_BE8) {
                        bias = lbl_3_rodata_B8C;
                    } else if (distHome < lbl_3_rodata_BEC) {
                        bias = lbl_3_rodata_B64;
                    } else if (distHome < lbl_3_rodata_BF0) {
                        bias = lbl_3_rodata_BF4;
                    }

                    if (distHome < lbl_3_rodata_BEC) {
                        threshold = lbl_3_rodata_B8C;
                    } else if (distHome < lbl_3_rodata_BF0) {
                        threshold = lbl_3_rodata_B8C + lbl_3_rodata_BBC * (distHome - lbl_3_rodata_BE8);
                    } else {
                        threshold = f8_0;
                    }

                    if (fielderIndexA == g_FieldingLogic.selectedFielder) {
                        if (distA > threshold) {
                            distA -= bias;
                        } else {
                            distA = lbl_3_rodata_B20;
                        }
                    }
                    if (fielderIndexB == g_FieldingLogic.selectedFielder) {
                        if (distA > threshold) {
                            distB -= bias;
                        }
                    }
                }
            skipBiasAdjustment:;
            }
        }
    }

    if (distB < distA) {
        f32 tempDist = distA;
        int tempIdx = fielderIndexA;
        s16 tempAngle = angleA;
        distA = distB;
        fielderIndexA = fielderIndexB;
        angleA = angleB;
        distB = tempDist;
        fielderIndexB = tempIdx;
        angleB = tempAngle;
    }

    if (flag < 3) {
        if (distA < lbl_3_rodata_B68) {
            return fielderIndexA;
        }

        distDiff = distB - distA;
        if (distDiff > lbl_3_rodata_B70) {
            if (distDiff > lbl_3_rodata_B9C && g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_LANDED &&
                fielderIndexA >= 6) {
                return fielderIndexA;
            }
            if (g_Ball.ballState != BALL_STATE_HIT || g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_LANDED) {
                return fielderIndexA;
            }
            if (fielderIndexA != 1 || distDiff > lbl_3_rodata_B9C) {
                return fielderIndexA;
            }
        } else if (distA < lbl_3_rodata_BE4) {
            return fielderIndexA;
        }

        if (distA < lbl_3_rodata_B64 && distB < lbl_3_rodata_B64 && angleDiff <= 0x400) {
            if (flag == 0) {
                return -1;
            }
            return fielderIndexA;
        }

        if (angleDiff <= 0x200 && distDiff > lbl_3_rodata_B64 && distA < lbl_3_rodata_B70) {
            return fielderIndexA;
        }
    }

    stickDiffA = currentStickDirection - angleA;
    stickDiffA = (stickDiffA ^ (stickDiffA >> 31)) - (stickDiffA >> 31);
    if (stickDiffA > 0x800) {
        stickDiffA = 0x1000 - stickDiffA;
    }

    stickDiffB = currentStickDirection - angleB;
    stickDiffB = (stickDiffB ^ (stickDiffB >> 31)) - (stickDiffB >> 31);
    if (stickDiffB > 0x800) {
        stickDiffB = 0x1000 - stickDiffB;
    }

    {
        int diff = stickDiffA - stickDiffB;
        diff = (diff ^ (diff >> 31)) - (diff >> 31);
        if (diff <= 0x100) {
            return fielderIndexA;
        }
    }

    if (stickDiffA > 0x400) {
        if (g_Ball.ballState == BALL_STATE_HIT && g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_LANDED &&
            fielderIndexB == 1 && stickDiffB <= 0x200) {
            return fielderIndexB;
        }
        if (stickDiffB <= 0x400) {
            return fielderIndexB;
        }
        if (flag == 0) {
            return -1;
        }
    }

    if (stickDiffB > 0x400) {
        if (g_Ball.ballState != BALL_STATE_HIT || g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_LANDED ||
            fielderIndexB != 1) {
            return fielderIndexA;
        }
        if (stickDiffA <= 0x200) {
            return fielderIndexA;
        }
    }

    if (stickDiffA > stickDiffB) {
        return fielderIndexB;
    }
    return fielderIndexA;
}

// .text:0x00037114 size:0x2F8 mapped:0x806761A8
int SelectBetterFielder(int fielderIndexA, int fielderIndexB, int flag, f32 x, f32 z) {
    InMemFielder* fielderA = &g_Fielders[fielderIndexA];
    InMemFielder* fielderB = &g_Fielders[fielderIndexB];
    int stickDir = currentStickDirection;
    int angleA;
    int angleB;
    int diffA;
    int diffB;
    int angleDiff;
    f32 dx;
    f32 dz;
    f32 dist;

    if (stickDir < 0) {
        return -1;
    }

    dx = x - fielderA->pos.x;
    dz = z - fielderA->pos.z;
    dist = fielderSqrt(dx * dx + dz * dz);
    angleA = calculateAngleFromCoordinates(dx, dz);

    dx = x - fielderB->pos.x;
    dz = z - fielderB->pos.z;
    dist = fielderSqrt(dx * dx + dz * dz);
    angleB = calculateAngleFromCoordinates(dx, dz);

    if (flag != 0) {
        if (stickDir >= 0x580 && stickDir < 0xa80) {
            if (angleA >= 0x580 && angleA < 0xa80 && angleB >= 0x580 && angleB < 0xa80) {
                goto compareAngles;
            }
            if (angleA >= 0x580 && angleA < 0xa80) {
                return fielderIndexA;
            }
            if (angleB >= 0x580 && angleB < 0xa80) {
                return fielderIndexB;
            }
        } else if (stickDir <= 0x280 && stickDir >= 0xd80) {
            if ((angleA < 0x280 || angleA >= 0xd80) && (angleB < 0x280 || angleB >= 0xd80)) {
                goto compareAngles;
            }
            if (angleA < 0x280 || angleA >= 0xd80) {
                return fielderIndexA;
            }
            if (angleB < 0x280 || angleB >= 0xd80) {
                return fielderIndexB;
            }
        }
    } else {
        if (stickDir >= 0x400 && stickDir < 0xc00) {
            if (angleA >= 0x400 && angleA < 0xc00 && angleB >= 0x400 && angleB < 0xc00) {
                goto compareStickDiff;
            }
            if (angleA >= 0x400 && angleA < 0xc00) {
                return fielderIndexA;
            }
            if (angleB >= 0x400 && angleB < 0xc00) {
                return fielderIndexB;
            }
        } else {
            if ((angleA < 0x400 || angleA >= 0xc00) && (angleB < 0x400 || angleB >= 0xc00)) {
                goto compareStickDiff;
            }
            if (angleA < 0x400 || angleA >= 0xc00) {
                return fielderIndexA;
            }
            if (angleB < 0x400 || angleB >= 0xc00) {
                return fielderIndexB;
            }
        }
    }

compareStickDiff:
    if (flag != 0) {
        return -1;
    }

    diffA = getDifferenceInAngle(currentStickDirection, angleA);
    diffB = getDifferenceInAngle(currentStickDirection, angleB);

    angleDiff = diffA - diffB;
    if ((angleDiff > 0 ? angleDiff : -angleDiff) > 0x100) {
        if (diffA > 0x400) {
            if (diffB > 0x400) {
                return -1;
            }
            return fielderIndexB;
        } else if (diffB > 0x400) {
            if (diffA > 0x400) {
                return -1;
            }
            return fielderIndexA;
        }
    }

compareAngles:
    return angleA < angleB ? fielderIndexA : fielderIndexB;
}

// .text:0x0003740C size:0x17C mapped:0x806764A0
void fn_3_3740C(void) {
    f32 maxDist;
    sAng ballAngle;
    int minDiff;
    int diff;
    int newFielder;
    InMemFielder *f;
    int i;

    maxDist = lbl_3_rodata_B20;
    minDiff = 0x1000;
    newFielder = -1;

    if (g_Ball.ballState != BALL_STATE_HIT) {
        return;
    }
    if (g_FieldingLogic.selectedFielder > 5) {
        return;
    }

    f = &g_Fielders[0];
    for (i = 0; i < 6; i++, f++) {
        if (f->distanceFromHomePlate > maxDist) {
            maxDist = f->distanceFromHomePlate;
        }
    }

    if (lbl_3_rodata_B64 + maxDist >= g_Ball.ballDistanceFromHome) {
        return;
    }

    ballAngle = g_Ball.ballAngleFromHome;

    f = &g_Fielders[6];
    for (i = 6; i < 9; i++, f++) {
        diff = ballAngle - f->playerAngleFromHome;
        diff = (diff ^ (diff >> 31)) - (diff >> 31);
        if (minDiff > diff) {
            minDiff = diff;
            newFielder = i;
        }
    }

    g_Ball.ballAngleFromHome = ballAngle;

    if (i < 0) {
        return;
    }
    setNewSelectedFielder_determinePriorSelectedFielder_sAutoMovement(newFielder, 0);
}

// .text:0x00037588 size:0x88 mapped:0x8067661C
void unused_FUN_8067661c(void) {
    s16 contactResult;

    if (g_Ball.ballVelocity > lbl_3_rodata_BF8) {
        int newFielder = fn_3_378B4();
        setNewSelectedFielder_determinePriorSelectedFielder_sAutoMovement(newFielder, 0);
        return;
    }

    contactResult = g_Ball.AtBat_ContactResult;
    if (contactResult != 0) {
        goto checkContactResult;
    }
    if (g_Ball.hitClassification1 == 0) {
        goto checkContactResult;
    }
    selectClosestFielderBasedOnFutureCoord(g_Ball.framesUntilBallHitsGround);
    return;

checkContactResult:
    if (contactResult == 0) {
        selectClosestFielderBasedOnFutureCoord(30);
        return;
    }
    selectClosestFielderBasedOnFutureCoord(30);
}

// .text:0x00037610 size:0x2A4 mapped:0x806766A4
void selectClosestFielderBasedOnFutureCoord(int frame) {
    InMemFielder* f;
    int i;
    f32 bestDist = const10000;
    int bestIndex = -1;
    int newFielder;

    for (f = &g_Fielders[0], i = 0; i < 9; f++, i++) {
        f32 dist = f->distanceFromBall;

        if (dist < lbl_3_rodata_B64 && f->onFire == 0 && dist < bestDist) {
            if (f->knockoutStatus != 0) {
                f32 knockOutTimeDiff = (f64)f->knockOutCountDown - lbl_3_rodata_B50;
                f32 adjustedDist = lbl_3_rodata_B7C * knockOutTimeDiff + dist;
                if (adjustedDist > bestDist) {
                    goto nextFielder;
                }
            }
            bestDist = dist;
            bestIndex = i;
        }
    nextFielder:;
    }

    if (bestIndex >= 0) {
        InMemFielder* bestFielder = &g_Fielders[bestIndex];
        if (bestFielder->distanceFromBall >= lbl_3_rodata_B64) {
            f32 dx = g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.x - bestFielder->pos.x;
            f32 dz = g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.z - bestFielder->pos.z;
            f32 sqx = dx * dx;
            f32 sqz = dz * dz;
            if (fielderSqrt(sqx + sqz) > lbl_3_rodata_B64) {
                bestIndex = -1;
            }
        }

        if (bestIndex >= 0 && bestIndex != g_FieldingLogic.selectedFielder) {
            s16 selectedFielder = g_FieldingLogic.selectedFielder;
            if (selectedFielder >= 0) {
                InMemFielder* selFielder = &g_Fielders[selectedFielder];
                if (selFielder->distanceFromBall < f8_0 && selFielder->onFire == 0) {
                    bestIndex = -1;
                }
            }
        }
    }

    if (bestIndex >= 0) {
        newFielder = bestIndex;
    } else {
        f32 x = g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.x;
        f32 z = g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.z;
        newFielder = SelectClosestFielder2(x, z);
    }

    setNewSelectedFielder_determinePriorSelectedFielder_sAutoMovement(newFielder, 0);
}

// .text:0x000378B4 size:0x74C mapped:0x80676948
int fn_3_378B4(void) {
    int result = -1;
    s32 stickAngle0 = fielderControlStick_continuousAngleHistory[0];
    s32 stickAngle3 = fielderControlStick_continuousAngleHistory[3];
    s32 ballAngle = g_Ball.ballAngleFromHome;
    s32 angleDiff = 0x800;

    if (stickAngle0 >= 0 && stickAngle3 >= 0) {
        s32 d = stickAngle0 - stickAngle3;
        if (d < 0) {
            d = -d;
        }
        if (d > 0x800) {
            d = 0x1000 - d;
        }
        angleDiff = d;
    }

    if (g_FieldingLogic.selectedFielder == 0) {
        s32 pitcherAngle = g_Fielders[0].playerAngleFromHome;
        if (ballAngle >= pitcherAngle - 0x40 && ballAngle < pitcherAngle + 0x40) {
            if (g_Ball.ballDistanceFromHome - g_Fielders[0].distanceFromHomePlate < lbl_3_rodata_B78) {
                return 0;
            }
        } else if (ballAngle < pitcherAngle) {
            if (stickAngle0 >= 0xf00 || (stickAngle0 >= 0 && stickAngle0 < 0x300)) {
                return 0;
            }
            if (stickAngle0 >= 0xb00 && stickAngle0 < 0xf00) {
                if (g_Ball.ballDistanceFromHome - g_Fielders[0].distanceFromHomePlate < lbl_3_rodata_B78) {
                    return 0;
                }
            }
        } else {
            if (stickAngle0 >= 0x500 && stickAngle0 < 0x900) {
                return 0;
            }
            if (stickAngle0 >= 0x900 && stickAngle0 < 0xd00) {
                if (g_Ball.ballDistanceFromHome - g_Fielders[0].distanceFromHomePlate < lbl_3_rodata_B78) {
                    return 0;
                }
            }
        }
    }

    {
        s32 diff23 = g_Fielders[2].playerAngleFromHome - g_Fielders[3].playerAngleFromHome;
        if (diff23 < 0) {
            diff23 = -diff23;
        }
        if (diff23 < 0x40) {
            int sel = g_FieldingLogic.selectedFielder;
            if (!((sel == 2 || sel == 3) && angleDiff < 0x400)) {
                s32 mid = (g_Fielders[2].playerAngleFromHome + g_Fielders[3].playerAngleFromHome) / 2;
                if (ballAngle >= mid - 0x100 && ballAngle < mid + 0x100) {
                    f32 dist2 = g_Fielders[2].distanceFromHomePlate;
                    f32 dist3 = g_Fielders[3].distanceFromHomePlate;
                    if (dist2 < dist3) {
                        if (dist2 > g_Ball.ballDistanceFromHome) {
                            return 2;
                        }
                        if (lbl_3_rodata_B78 + dist3 > g_Ball.ballDistanceFromHome) {
                            return 3;
                        }
                    } else {
                        if (dist3 > g_Ball.ballDistanceFromHome) {
                            return 2;
                        }
                        if (lbl_3_rodata_B78 + dist2 > g_Ball.ballDistanceFromHome) {
                            return 3;
                        }
                    }
                }
            }
        }
    }

    {
        s32 diff45 = g_Fielders[4].playerAngleFromHome - g_Fielders[5].playerAngleFromHome;
        if (diff45 < 0) {
            diff45 = -diff45;
        }
        if (diff45 < 0x40) {
            int sel = g_FieldingLogic.selectedFielder;
            if (!((sel == 4 || sel == 5) && angleDiff < 0x400)) {
                s32 mid = (g_Fielders[4].playerAngleFromHome + g_Fielders[5].playerAngleFromHome) / 2;
                if (ballAngle >= mid - 0x100 && ballAngle < mid + 0x100) {
                    f32 dist4 = g_Fielders[4].distanceFromHomePlate;
                    f32 dist5 = g_Fielders[5].distanceFromHomePlate;
                    if (dist4 <= dist5) {
                        if (dist4 > g_Ball.ballDistanceFromHome) {
                            return 4;
                        }
                        if (lbl_3_rodata_B78 + dist5 > g_Ball.ballDistanceFromHome) {
                            return 5;
                        }
                    } else {
                        if (dist5 > g_Ball.ballDistanceFromHome) {
                            return 5;
                        }
                        if (lbl_3_rodata_B78 + dist4 > g_Ball.ballDistanceFromHome) {
                            return 4;
                        }
                    }
                }
            }
        }
    }

    if (ballAngle < g_Fielders[2].playerAngleFromHome + 0x40) {
        if (g_FieldingLogic.selectedFielder == 3 && angleDiff < 0x400) {
            return result;
        }
        return 2;
    }

    if (ballAngle >= g_Fielders[4].playerAngleFromHome - 0x40 && ballAngle < 0x800) {
        if (g_FieldingLogic.selectedFielder == 5 && angleDiff < 0x400) {
            return result;
        }
        return 4;
    }

    {
        int sel = g_FieldingLogic.selectedFielder;
        s32 margin = (sel == 3) ? 0x20 : 0;
        s32 thirdAngle = g_Fielders[3].playerAngleFromHome;
        if (ballAngle >= thirdAngle - (margin + 0x40) && ballAngle < thirdAngle + margin + 0x40) {
            if (sel == 2) {
                if (stickAngle0 >= 0x500 && stickAngle0 < 0x900) {
                    return 2;
                }
                return 3;
            }
            if (sel == 5) {
                if (g_Fielders[3].locationResponsibleForCovering == 2 && angleDiff < 0x400) {
                    return result;
                }
            }
            if (sel == 5) {
                if (g_Fielders[3].locationResponsibleForCovering == 2 &&
                    lbl_3_rodata_B64 + g_Fielders[3].distanceFromHomePlate < g_Ball.ballDistanceFromHome) {
                    return result;
                }
            }
            return 3;
        }

        {
            s32 margin2 = (sel == 2) ? 0x20 : 0;
            s32 fifthAngle = g_Fielders[5].playerAngleFromHome;
            if (ballAngle >= fifthAngle - (margin2 + 0x40) && ballAngle < fifthAngle + margin2 + 0x40) {
                if (sel == 4) {
                    if (stickAngle0 >= 0 && stickAngle0 < 0x300) {
                        return 4;
                    }
                    if (stickAngle0 < 0xf00) {
                        return 5;
                    }
                    return 4;
                }
                if (sel == 3) {
                    if (g_Fielders[5].locationResponsibleForCovering == 2 && angleDiff < 0x400) {
                        return result;
                    }
                }
                if (sel == 3) {
                    if (g_Fielders[5].locationResponsibleForCovering == 2 &&
                        lbl_3_rodata_B64 + g_Fielders[5].distanceFromHomePlate < g_Ball.ballDistanceFromHome) {
                        return result;
                    }
                }
                return 5;
            }

            if (ballAngle >= g_Fielders[2].playerAngleFromHome && ballAngle < thirdAngle) {
                if (stickAngle0 >= 0x300 && stickAngle0 < 0x700) {
                    return 2;
                }
                if (stickAngle0 >= 0x700 && stickAngle0 < 0x900) {
                    if (lbl_3_rodata_B64 + g_Fielders[2].pos.z <= g_Ball.AtBat_Contact_BallPos.z) {
                        return result;
                    }
                    return 2;
                }
                if (stickAngle0 >= 0xd00 || (stickAngle0 >= 0 && stickAngle0 < 0x300)) {
                    return 3;
                }
                return result;
            }

            if (ballAngle >= fifthAngle && ballAngle < g_Fielders[4].playerAngleFromHome) {
                if (stickAngle0 >= 0x100 && stickAngle0 < 0x500) {
                    return 4;
                }
                if (stickAngle0 >= 0xf00 || (stickAngle0 >= 0 && stickAngle0 < 0x100)) {
                    if (lbl_3_rodata_B64 + g_Fielders[4].pos.z <= g_Ball.AtBat_Contact_BallPos.z) {
                        return result;
                    }
                    return 4;
                }
                if (stickAngle0 < 0x500 || stickAngle0 >= 0xb00) {
                    return result;
                }
                return 5;
            }

            if (ballAngle < thirdAngle) {
                return result;
            }
            if (ballAngle >= fifthAngle) {
                return result;
            }
            if (g_Ball.ballDistanceFromHome < lbl_3_rodata_B64 + g_Fielders[0].distanceFromHomePlate) {
                s32 pitcherAngle2 = g_Fielders[0].playerAngleFromHome;
                if (ballAngle < pitcherAngle2) {
                    if (stickAngle0 > 0xd00) {
                        return 0;
                    }
                    if (stickAngle0 >= 0 && stickAngle0 < 0x100) {
                        return 0;
                    }
                } else {
                    if (stickAngle0 >= 0x700 && stickAngle0 < 0xb00) {
                        return 0;
                    }
                }
            }
            if (stickAngle0 >= 0x500 && stickAngle0 < 0xb00) {
                return 3;
            }
            if (stickAngle0 > 0xd00 || (stickAngle0 >= 0 && stickAngle0 < 0x300)) {
                return 5;
            }
            return result;
        }
    }
}

// .text:0x00038000 size:0x234 mapped:0x80677094
void SelectOptimalFielder(void) {
    sAng ballAngle = g_Ball.ballAngleFromHome;
    int futureFrame = 30;
    int candidateFielder = 0;
    f32 velocityThreshold = lbl_3_rodata_B64;
    f32 maxDist;
    int newFielder;

    if (ballAngle >= 0x800) {
        newFielder = 1;
        goto finalize;
    }

    if (ballAngle < 0x300) {
        if (ballAngle < g_Fielders[2].playerAngleFromHome ||
            getDifferenceInAngle(ballAngle, g_Fielders[3].playerAngleFromHome) >= 0x100) {
            maxDist = g_Fielders[2].distanceFromHomePlate;
            candidateFielder = 8;
            goto computeThreshold;
        }
    } else if (ballAngle > 0x500) {
        if (ballAngle >= g_Fielders[4].playerAngleFromHome ||
            getDifferenceInAngle(ballAngle, g_Fielders[5].playerAngleFromHome) >= 0x100) {
            maxDist = g_Fielders[4].distanceFromHomePlate;
            candidateFielder = 6;
            goto computeThreshold;
        }
    }

    if (ballAngle < g_Fielders[3].playerAngleFromHome) {
        if (g_Fielders[3].distanceFromHomePlate >= g_Fielders[2].distanceFromHomePlate) {
            maxDist = g_Fielders[3].distanceFromHomePlate;
        } else {
            maxDist = g_Fielders[2].distanceFromHomePlate;
        }
    } else if (ballAngle >= g_Fielders[5].playerAngleFromHome) {
        if (g_Fielders[5].distanceFromHomePlate >= g_Fielders[4].distanceFromHomePlate) {
            maxDist = g_Fielders[5].distanceFromHomePlate;
        } else {
            maxDist = g_Fielders[4].distanceFromHomePlate;
        }
    } else {
        if (g_Fielders[3].distanceFromHomePlate >= g_Fielders[5].distanceFromHomePlate) {
            maxDist = g_Fielders[3].distanceFromHomePlate;
        } else {
            maxDist = g_Fielders[5].distanceFromHomePlate;
        }
    }

computeThreshold:
    if (g_Ball.ballVelocity > lbl_3_rodata_BB8) {
        f32 velocityOverThreshold = g_Ball.ballVelocity - lbl_3_rodata_BB8;
        velocityThreshold -= lbl_3_rodata_BA0 * velocityOverThreshold;
        futureFrame += (int)(lbl_3_rodata_BDC * velocityOverThreshold);
    }

    if (maxDist + velocityThreshold > g_Ball.ballDistanceFromHome) {
        newFielder = fn_3_378B4();
        goto finalize;
    }

    {
        f32 x = g_Ball.physicsSubstruct.futureCoordsAndDist[futureFrame].pos.x;
        f32 z = g_Ball.physicsSubstruct.futureCoordsAndDist[futureFrame].pos.z;
        newFielder = SelectClosestFielder2(x, z);
        if (candidateFielder == 8 && newFielder == 3) {
            newFielder = 8;
        }
        if (candidateFielder == 6 && newFielder == 5) {
            newFielder = 6;
        }
    }

finalize:
    setNewSelectedFielder_determinePriorSelectedFielder_sAutoMovement(newFielder, 0);
}

// .text:0x00038234 size:0xD0 mapped:0x806772C8
void fn_3_38234(void) {
    u8 hitClassification2 = g_Ball.hitClassification2;

    if (hitClassification2 <= 4 || hitClassification2 == 7) {
        SelectOptimalFielder();
        return;
    }

    if (g_Ball.maxYOfHit > lbl_3_rodata_BE4) {
        selectAssignClosestFielder2();
        return;
    }

    if (g_Ball.maxYOfHit < lbl_3_rodata_B8C) {
        SelectOptimalFielder();
        return;
    }

    if (g_Ball.someYCoord > lbl_3_rodata_B64) {
        selectAssignClosestFielder2();
        return;
    }

    if (g_Ball.ballDistanceFromHome < lbl_3_rodata_C00) {
        s16 angle = fielderControlStick_continuousAngleHistory[0];
        if (angle >= 0x900 && angle < 0xf00) {
            selectAssignClosestFielder2();
            return;
        }
        SelectOptimalFielder();
        return;
    }

    selectAssignClosestFielder2();
}

// .text:0x00038304 size:0x48C mapped:0x80677398
void selectAssignClosestFielder2(void) {
    s16 fielderIndex;
    f32 rank1Dist;
    f32 rank3Dist;
    f32 rank2Dist;
    f32 landingDist;
    int isFarPlay;
    int newFielder;

    if ((fielderIndex = g_FieldingLogic.selectedFielder) >= 0 &&
        g_Fielders[fielderIndex].distanceFromLandingSpot < lbl_3_rodata_B64) {
        return;
    }

    landingDist = g_Ball.physicsSubstruct.hitLandingSpotDistFromHome;
    isFarPlay = 0;

    if (landingDist > const50_0) {
        if (fielderIndex >= 6) {
            isFarPlay = 1;
        } else if (g_Ball.ballDistanceFromHome - lbl_3_rodata_B64 > g_Fielders[2].distanceFromHomePlate &&
                   g_Ball.ballDistanceFromHome - lbl_3_rodata_B64 > g_Fielders[3].distanceFromHomePlate &&
                   g_Ball.ballDistanceFromHome - lbl_3_rodata_B64 > g_Fielders[4].distanceFromHomePlate &&
                   g_Ball.ballDistanceFromHome - lbl_3_rodata_B64 > g_Fielders[5].distanceFromHomePlate) {
            isFarPlay = 1;
        }
    }

    if (landingDist > lbl_3_rodata_C04 || isFarPlay) {
        int a, b;
        f32 distA = g_Fielders[6].distanceFromLandingSpot;
        f32 distB = g_Fielders[8].distanceFromLandingSpot;

        if (distA < distB) {
            f32 distC = g_Fielders[7].distanceFromLandingSpot;
            if (distA < distC) {
                a = 6;
                b = 7;
            } else {
                a = 7;
                b = 6;
            }
        } else {
            f32 distC = g_Fielders[7].distanceFromLandingSpot;
            if (distB < distC) {
                a = 8;
                b = 7;
            } else {
                a = 7;
                b = 8;
            }
        }

        if (g_Fielders[a].distanceFromLandingSpot + lbl_3_rodata_B9C < g_Fielders[b].distanceFromLandingSpot) {
            newFielder = a;
        } else {
            newFielder = selectBestFielder(a, b, 0, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x,
                                            g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);
        }
    } else {
        InMemFielder* f;
        int i;
        int rank3Index = -1;
        int rank2Index = -1;
        int rank1Index = -1;

        rank1Dist = lbl_3_rodata_BA4;
        rank3Dist = rank1Dist;
        rank2Dist = rank1Dist;

        for (f = &g_Fielders[0], i = 0; i < 9; f++, i++) {
            f32 dist = f->distanceFromLandingSpot;
            if (rank1Dist > dist) {
                rank3Dist = rank2Dist;
                rank3Index = rank2Index;
                rank2Dist = rank1Dist;
                rank2Index = rank1Index;
                rank1Dist = dist;
                rank1Index = i;
            } else if (rank2Dist > dist) {
                rank3Dist = rank2Dist;
                rank3Index = rank2Index;
                rank2Dist = dist;
                rank2Index = i;
            } else if (rank3Dist > dist) {
                rank3Dist = dist;
                rank3Index = i;
            }
        }

        if (landingDist > lbl_3_rodata_BD0) {
            if (rank1Dist <= f8_0 && rank1Index == fielderIndex) {
                newFielder = rank1Index;
            } else if (rank2Dist - rank1Dist > lbl_3_rodata_B9C) {
                newFielder = rank1Index;
            } else if (rank3Dist - rank2Dist > lbl_3_rodata_B9C) {
                newFielder = selectBestFielder(rank1Index, rank2Index, 0, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x,
                                                g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);
            } else {
                f32 ballX = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
                f32 ballZ = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
                int result = selectBestFielder(rank2Index, rank3Index, 1, ballX, ballZ);
                if (result != -1) {
                    int result2;
                    if (g_FieldingLogic.selectedFielder < 0) {
                        result2 = selectBestFielder(rank1Index, result, 1, ballX, ballZ);
                    } else {
                        result2 = selectBestFielder(rank1Index, result, 0, ballX, ballZ);
                    }
                    rank1Index = result2;
                }
                newFielder = rank1Index;
            }
        } else {
            f32 ballX = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
            f32 ballZ = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
            int result = selectBestFielder(rank2Index, rank3Index, 1, ballX, ballZ);
            if (result != -1) {
                int result2;
                if (g_FieldingLogic.selectedFielder < 0) {
                    result2 = selectBestFielder(rank1Index, result, 1, ballX, ballZ);
                } else {
                    result2 = selectBestFielder(rank1Index, result, 0, ballX, ballZ);
                }
                rank1Index = result2;
            }
            newFielder = rank1Index;
        }
    }

    setNewSelectedFielder_determinePriorSelectedFielder_sAutoMovement(newFielder, 0);
}

// .text:0x00038790 size:0x580 mapped:0x80677824
void setNewSelectedFielder_determinePriorSelectedFielder_sAutoMovement(int newFielder, int useHumanControlMovement) {
    InMemFielder* fielder = &g_Fielders[newFielder];
    InMemFielder* prior;
    int priorSelectedFielder = g_FieldingLogic.selectedFielder;
    int loc;
    s16 hist;

    if (newFielder < 0) {
        return;
    }
    if (newFielder == priorSelectedFielder) {
        return;
    }

    if (g_Ball.ballState == BALL_STATE_HIT &&
        g_Ball.ballAngleFromHome >= 0x3d8 && g_Ball.ballAngleFromHome < 0x428) {
        if (priorSelectedFielder == 3 && newFielder == 5 &&
            fielder->locationResponsibleForCovering == 2 &&
            fielder->distanceFromEachFielder[3] < f8_0) {
            return;
        }
        if (priorSelectedFielder == 5 && newFielder == 3 &&
            fielder->locationResponsibleForCovering == 2 &&
            fielder->distanceFromEachFielder[5] < f8_0) {
            return;
        }
    }

    if (g_Ball.ballState == BALL_STATE_HIT &&
        g_Ball.hitClassification2 <= 6 && newFielder == 1) {
        hist = fielderControlStick_continuousAngleHistory[0];
        if (hist >= 0x800) {
            return;
        }
        if (hist == 0) {
            return;
        }
    }

    g_FieldingLogic.selectedFielder = newFielder;

    if (useHumanControlMovement == 0) {
        if (newFielder != -1) {
            fielder->autoMovementFunctionIndex = 15;
            if (autoMovementFunctions[15].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[newFielder] = autoMovementFunctions[15].code;
            }
            fielder->unknown_writeOnly = 0;
            fielder->fielderVeloAdjustmentCode = 0;
            fielder->unknown_writeOnly_always0 = 0;
            fielder->timeSinceThrowWasCaught = 0;
            fielder->fielderTrackingBallState = 0;
        }
    } else {
        if (newFielder != -1) {
            fielder->autoMovementFunctionIndex = 21;
            if (autoMovementFunctions[21].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[newFielder] = autoMovementFunctions[21].code;
            }
            fielder->unknown_writeOnly = 0;
            fielder->fielderVeloAdjustmentCode = 0;
            fielder->unknown_writeOnly_always0 = 0;
            fielder->timeSinceThrowWasCaught = 0;
            fielder->fielderTrackingBallState = 0;
        }
    }

    loc = fielder->locationResponsibleForCovering;
    if (loc >= 0 && loc <= 5) {
        if (loc >= 0 && loc <= 3) {
            if (g_FieldingLogic.fielderAssignedLocationIndex[loc] == newFielder) {
                g_FieldingLogic.fielderAssignedLocationIndex[loc] = -1;
                g_FieldingLogic.baseCoveredInd[loc] = 0;
            }
            fielder->locationResponsibleForCovering = -1;
            fielder->isResponsibleForCoveringALocation = 0;
            if (fielder->autoMovementFunctionIndex == 1 && newFielder != -1) {
                fielder->autoMovementFunctionIndex = 12;
                if (autoMovementFunctions[12].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[newFielder] = autoMovementFunctions[12].code;
                }
                fielder->unknown_writeOnly = 0;
                fielder->fielderVeloAdjustmentCode = 0;
                fielder->unknown_writeOnly_always0 = 0;
                fielder->timeSinceThrowWasCaught = 0;
                fielder->fielderTrackingBallState = 0;
            }
        } else if (loc == 5) {
            fielder->locationResponsibleForCovering = -1;
            fielder->isResponsibleForCoveringALocation = 0;
            g_FieldingLogic.fielderAssignedLocationIndex[4] = -1;
            g_FieldingLogic.playerAtMoundCutoffLocation = 0;
            if (fielder->autoMovementFunctionIndex == 14 && newFielder != -1) {
                fielder->autoMovementFunctionIndex = 12;
                if (autoMovementFunctions[12].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[newFielder] = autoMovementFunctions[12].code;
                }
                fielder->unknown_writeOnly = 0;
                fielder->fielderVeloAdjustmentCode = 0;
                fielder->unknown_writeOnly_always0 = 0;
                fielder->timeSinceThrowWasCaught = 0;
                fielder->fielderTrackingBallState = 0;
            }
        }
    }

    if (g_FieldingLogic.selectedFielder == g_FieldingLogic.cutoffFielderIndex) {
        g_FieldingLogic.cutoffFielderIndex = -1;
    }

    if (priorSelectedFielder >= 0) {
        if (priorSelectedFielder >= 6) {
            prior = &g_Fielders[priorSelectedFielder];
            prior->autoMovementFunctionIndex = 16;
            if (autoMovementFunctions[16].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[priorSelectedFielder] = autoMovementFunctions[16].code;
            }
            prior->unknown_writeOnly = 0;
            prior->fielderVeloAdjustmentCode = 0;
            prior->unknown_writeOnly_always0 = 0;
            prior->timeSinceThrowWasCaught = 0;
            prior->fielderTrackingBallState = 0;
        } else if (g_Ball.ballState != BALL_STATE_HIT) {
            prior = &g_Fielders[priorSelectedFielder];
            if (priorSelectedFielder != -1) {
                prior->autoMovementFunctionIndex = 12;
                if (autoMovementFunctions[12].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[priorSelectedFielder] = autoMovementFunctions[12].code;
                }
                prior->unknown_writeOnly = 0;
                prior->fielderVeloAdjustmentCode = 0;
                prior->unknown_writeOnly_always0 = 0;
                prior->timeSinceThrowWasCaught = 0;
                prior->fielderTrackingBallState = 0;
            }
            prior->unknown_writeOnly = 4;
        } else {
            prior = &g_Fielders[priorSelectedFielder];
            if (prior->distanceFromHomePlate > lbl_3_rodata_B78 + fielder->distanceFromHomePlate) {
                prior->autoMovementFunctionIndex = 16;
                if (autoMovementFunctions[16].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[priorSelectedFielder] = autoMovementFunctions[16].code;
                }
                prior->unknown_writeOnly = 0;
                prior->fielderVeloAdjustmentCode = 0;
                prior->unknown_writeOnly_always0 = 0;
                prior->timeSinceThrowWasCaught = 0;
                prior->fielderTrackingBallState = 0;
            } else if (prior->locationResponsibleForCovering == 6) {
                prior->autoMovementFunctionIndex = 11;
                if (autoMovementFunctions[11].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[priorSelectedFielder] = autoMovementFunctions[11].code;
                }
                prior->unknown_writeOnly = 0;
                prior->fielderVeloAdjustmentCode = 0;
                prior->unknown_writeOnly_always0 = 0;
                prior->timeSinceThrowWasCaught = 0;
                prior->fielderTrackingBallState = 0;
            } else {
                if (priorSelectedFielder != -1) {
                    prior->autoMovementFunctionIndex = 12;
                    if (autoMovementFunctions[12].code >= 0) {
                        g_FieldingLogic.fielderAutoMovementCode[priorSelectedFielder] = autoMovementFunctions[12].code;
                    }
                    prior->unknown_writeOnly = 0;
                    prior->fielderVeloAdjustmentCode = 0;
                    prior->unknown_writeOnly_always0 = 0;
                    prior->timeSinceThrowWasCaught = 0;
                    prior->fielderTrackingBallState = 0;
                }
                prior->unknown_writeOnly = 4;
            }
        }
    }

    if (g_Ball.framesSinceHit < 30) {
        g_FieldingLogic.someFrameCounterFielderRelated = 20;
    } else {
        g_FieldingLogic.someFrameCounterFielderRelated = 45;
    }
}

// .text:0x00038D10 size:0x2E8 mapped:0x80677DA4
void HandleMiddleInfieldSelection(void) {
    int newFielder;

    if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR) {
        int selectedFielder = g_FieldingLogic.selectedFielder;
        if (selectedFielder == 3 || selectedFielder == 5) {
            InMemFielder* selFielder = &g_Fielders[selectedFielder];
            if (selFielder->distanceFromLandingSpot < selFielder->hitbox[0]) {
                newFielder = selectedFielder;
                goto dispatch;
            }
        }
    }

    {
        f32 x;
        f32 z;

        if ((g_Fielders[3].nonCatchFlyBallStratInd == 0 || g_Fielders[5].nonCatchFlyBallStratInd == 0) &&
            g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR) {
            x = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
            z = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
        } else {
            f32 threshold =
                lbl_3_rodata_B80 * (g_Fielders[3].distanceFromHomePlate + g_Fielders[5].distanceFromHomePlate);
            int frame;

            for (frame = 1; frame < 121; frame += 3) {
                if (g_Ball.physicsSubstruct.futureCoordsAndDist[frame].dist > threshold) {
                    break;
                }
            }

            x = g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.x;
            z = g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.z;
        }

        newFielder = SelectBetterFielder(3, 5, 1, x, z);
    }

    if (newFielder < 0) {
        if (g_Ball.ballZoneAwayFromHome >= 2 && currentStickDirection > 0xa00 && currentStickDirection < 0xe00) {
            g_FieldingLogic.infielderSelectedOnPopFlyInd = 0;
        }
        return;
    }

dispatch:
    if (newFielder == 3) {
        setNewSelectedFielder_determinePriorSelectedFielder_sAutoMovement(3, 1);
        g_Fielders[5].autoMovementFunctionIndex = 12;
        if (autoMovementFunctions[12].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[5] = autoMovementFunctions[12].code;
        }
        g_Fielders[5].unknown_writeOnly = 0;
        g_Fielders[5].fielderVeloAdjustmentCode = 0;
        g_Fielders[5].unknown_writeOnly_always0 = 0;
        g_Fielders[5].timeSinceThrowWasCaught = 0;
        g_Fielders[5].fielderTrackingBallState = 0;
    } else {
        setNewSelectedFielder_determinePriorSelectedFielder_sAutoMovement(5, 1);
        g_Fielders[3].autoMovementFunctionIndex = 12;
        if (autoMovementFunctions[12].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[3] = autoMovementFunctions[12].code;
        }
        g_Fielders[3].unknown_writeOnly = 0;
        g_Fielders[3].fielderVeloAdjustmentCode = 0;
        g_Fielders[3].unknown_writeOnly_always0 = 0;
        g_Fielders[3].timeSinceThrowWasCaught = 0;
        g_Fielders[3].fielderTrackingBallState = 0;
    }

    g_FieldingLogic.infielderSelectedOnPopFlyInd = 0;
}

extern const f32 lbl_3_rodata_C08;

// .text:0x00038FF8 size:0x3B8 mapped:0x8067808C
void fielderSelect_tertiaryFielderExists_determine2FieldersToKeep(void) {
    InMemFielder* fielder = &g_Fielders[g_FieldingLogic.selectedFielder];
    f32 threshold = fielder->distanceFromHomePlate;
    int n;
    int winner;

    for (n = 1; n < 61; n += 3) {
        if (g_Ball.physicsSubstruct.futureCoordsAndDist[n].dist > threshold) {
            break;
        }
    }

    if (g_FieldingLogic.selectedFielder == 1) {
        goto trySecondaryPair;
    }
    if (n <= 1) {
        goto noTertiary;
    }

    if (fielder->groundDistanceFromBall < lbl_3_rodata_C08) {
        if (currentStickDirection >= 0) {
            int angle = calculateAngleFromCoordinates(g_Ball.AtBat_Contact_BallPos.x - fielder->pos.x,
                                                       g_Ball.AtBat_Contact_BallPos.z - fielder->pos.z);
            if (getDifferenceInAngle(currentStickDirection, angle) < 0x100) {
                goto pickPrimary;
            }
        }

        if (g_FieldingLogic.selectedFielder >= 2 && g_FieldingLogic.selectedFielder <= 5) {
            if (g_Ball.hitClassification2 == 2 || g_Ball.hitClassification2 == 3) {
                goto pickPrimary;
            }
        }
    } else {
        goto trySecondaryPair;
    }

trySecondaryPair:
    if (g_Fielders[g_FieldingLogic.selectedFielder].nonCatchFlyBallStratInd == 0 ||
        g_Fielders[g_FieldingLogic.secondaryFielder].nonCatchFlyBallStratInd == 0) {
        winner = selectBestFielder(g_FieldingLogic.selectedFielder, g_FieldingLogic.secondaryFielder, 3,
                                    g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x,
                                    g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);
    } else {
        winner = selectBestFielder(g_FieldingLogic.selectedFielder, g_FieldingLogic.secondaryFielder, 3,
                                    g_Ball.physicsSubstruct.futureCoordsAndDist[n].pos.x,
                                    g_Ball.physicsSubstruct.futureCoordsAndDist[n].pos.z);
    }

    if (winner >= 0) {
        if (winner == g_FieldingLogic.secondaryFielder) {
            goto noTertiary;
        }
        if (winner == g_FieldingLogic.selectedFielder) {
            goto pickPrimary;
        }
    }

    if (g_Ball.framesSinceHit <= 90) {
        return;
    } else if (g_Ball.framesSinceBallHitGroundOrWasCaught >= 0) {
        goto pickPrimary;
    } else if (g_Fielders[g_FieldingLogic.selectedFielder].distanceFromLandingSpot <=
               g_Fielders[g_FieldingLogic.secondaryFielder].distanceFromLandingSpot) {
        goto pickPrimary;
    } else {
        goto noTertiary;
    }

pickPrimary:
    g_FieldingLogic.unkFlagMaybeInAir = 0;
    if (g_FieldingLogic.selectedFielder == 0) {
        return;
    }
    goto tailShift;

noTertiary:
    if (g_FieldingLogic.infielderSelectedOnPopFlyInd != 0 &&
        (g_FieldingLogic.secondaryFielder == 3 || g_FieldingLogic.secondaryFielder == 5)) {
        HandleMiddleInfieldSelection();
        if (g_FieldingLogic.infielderSelectedOnPopFlyInd == 0) {
            goto tailShift;
        }
        if (g_Ball.ballDistanceFromHome - lbl_3_rodata_B78 <= g_Fielders[g_FieldingLogic.selectedFielder].distanceFromHomePlate) {
            return;
        }
        setNewSelectedFielder_determinePriorSelectedFielder_sAutoMovement(g_FieldingLogic.secondaryFielder, 1);
        goto tailShift;
    }

    setNewSelectedFielder_determinePriorSelectedFielder_sAutoMovement(g_FieldingLogic.secondaryFielder, 1);

tailShift:
    g_FieldingLogic.unkFlagMaybeInAir = 0;
    g_FieldingLogic.secondaryFielder = g_FieldingLogic.tertiaryFielder;
    g_FieldingLogic.tertiaryFielder = -1;
}

extern const f32 lbl_3_rodata_B74;

// .text:0x000393B0 size:0x4A8 mapped:0x80678444
void updateBallLandedFielderSelection(void) {
    InMemFielder* fielder = &g_Fielders[g_FieldingLogic.selectedFielder];
    int n;
    int winner;

    if (g_Ball.framesSinceHit >= 60) {
        goto tail;
    }

    if (g_FieldingLogic.selectedFielder == 3) {
        InMemFielder* other = &g_Fielders[2];
        f32 threshold = other->distanceFromHomePlate;

        for (n = 2; n < 30; n += 2) {
            if (g_Ball.physicsSubstruct.futureCoordsAndDist[n].dist > threshold) {
                break;
            }
        }

        if (n < 30 && g_Ball.ballAngleFromHome > other->playerAngleFromHome &&
            g_Ball.ballAngleFromHome < fielder->playerAngleFromHome &&
            other->distanceFromHomePlate > lbl_3_rodata_B60 + g_Ball.ballDistanceFromHome) {
            winner = selectBestFielder(2, 3, 0, g_Ball.physicsSubstruct.futureCoordsAndDist[n].pos.x,
                                        g_Ball.physicsSubstruct.futureCoordsAndDist[n].pos.z);
            if (winner == 2) {
                setNewSelectedFielder_determinePriorSelectedFielder_sAutoMovement(2, 0);
                return;
            }
        }
    } else if (g_FieldingLogic.selectedFielder == 5) {
        InMemFielder* other = &g_Fielders[4];
        f32 threshold = other->distanceFromHomePlate;

        for (n = 2; n < 30; n += 2) {
            if (g_Ball.physicsSubstruct.futureCoordsAndDist[n].dist > threshold) {
                break;
            }
        }

        if (n < 30 && g_Ball.ballAngleFromHome < other->playerAngleFromHome &&
            g_Ball.ballAngleFromHome > fielder->playerAngleFromHome &&
            other->distanceFromHomePlate > lbl_3_rodata_B60 + g_Ball.ballDistanceFromHome) {
            winner = selectBestFielder(4, 5, 0, g_Ball.physicsSubstruct.futureCoordsAndDist[n].pos.x,
                                        g_Ball.physicsSubstruct.futureCoordsAndDist[n].pos.z);
            if (winner == 4) {
                setNewSelectedFielder_determinePriorSelectedFielder_sAutoMovement(4, 0);
                return;
            }
        }
    }

tail:
    if (g_FieldingLogic.secondaryFielder < 0) {
        goto ballLoose;
    }
    if (g_FieldingLogic.selectedFielder > 5) {
        return;
    }
    if (g_FieldingLogic.secondaryFielder < 6) {
        return;
    }

    {
        f32 x = g_Ball.physicsSubstruct.futureCoordsAndDist[30].pos.x;
        f32 z = g_Ball.physicsSubstruct.futureCoordsAndDist[30].pos.z;

        if (g_Ball.ballVelocity < lbl_3_rodata_BBC || g_Ball.ballState == BALL_STATE_LOOSE) {
            if (g_Ball.ballVelocity < lbl_3_rodata_B24 && g_Ball.ballState == BALL_STATE_HIT &&
                g_Ball.ballZoneAwayFromHome <= 1 && fielder->distanceFromHomePlate > g_Ball.ballDistanceFromHome &&
                fielder->groundDistanceFromBall < lbl_3_rodata_B64) {
                InMemFielder* secFielder = &g_Fielders[g_FieldingLogic.secondaryFielder];

                if (g_FieldingLogic.secondaryFielder != -1) {
                    secFielder->autoMovementFunctionIndex = 12;
                    if (autoMovementFunctions[12].code >= 0) {
                        g_FieldingLogic.fielderAutoMovementCode[g_FieldingLogic.secondaryFielder] = autoMovementFunctions[12].code;
                    }
                    secFielder->unknown_writeOnly = 0;
                    secFielder->fielderVeloAdjustmentCode = 0;
                    secFielder->unknown_writeOnly_always0 = 0;
                    secFielder->timeSinceThrowWasCaught = 0;
                    secFielder->fielderTrackingBallState = 0;
                }

                g_FieldingLogic.secondaryFielder = -1;
            }
            winner = selectBestFielder(g_FieldingLogic.selectedFielder, g_FieldingLogic.secondaryFielder, 0, x, z);
        } else {
            winner = -1;
            if (lbl_3_rodata_B78 + fielder->distanceFromHomePlate < g_Ball.ballDistanceFromHome) {
                winner = selectBestFielder(g_FieldingLogic.selectedFielder, g_FieldingLogic.secondaryFielder, 0, x, z);
            }
        }

        if (g_FieldingLogic.secondaryFielder != winner) {
            return;
        }
        goto assignWinner;
    }

ballLoose:
    if (g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_LANDED && g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_FOUL && g_Ball.ballState != BALL_STATE_LOOSE) {
        return;
    }
    if (g_Ball.ballVelocity >= lbl_3_rodata_B74) {
        return;
    }
    if (g_Fielders[g_FieldingLogic.selectedFielder].distanceFromBall <= f8_0) {
        return;
    }
    selectClosestFielderBasedOnFutureCoord(30);
    return;

assignWinner:
    setNewSelectedFielder_determinePriorSelectedFielder_sAutoMovement(winner, 1);
    g_FieldingLogic.secondaryFielder = -1;
}

// .text:0x00039858 size:0x56C mapped:0x806788EC
void updateInAirFielderSelection(void) {
    int selectedFielderInit = g_FieldingLogic.selectedFielder;
    int secondaryFielderInit;
    InMemFielder* fielder = &g_Fielders[selectedFielderInit];
    int newFielder;

    if ((secondaryFielderInit = g_FieldingLogic.secondaryFielder) < 0) {
        if (g_FieldingLogic.unkFlagMaybeInAir != 0) {
            return;
        }
        if (g_FieldingLogic.fielderAssignedLocationIndex[5] != 0) {
            return;
        }
        selectAssignClosestFielder2();
        return;
    }

    if (selectedFielderInit <= 5 && secondaryFielderInit >= 6) {
        if (g_Ball.hitClassification1 == 2 || g_Ball.hitClassification1 == 5) {
            int result = selectBestFielder(g_FieldingLogic.selectedFielder, g_FieldingLogic.secondaryFielder, 0,
                                            g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x,
                                            g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);
            if (g_FieldingLogic.secondaryFielder == result) {
                goto callTail;
            }
            return;
        }
        if (lbl_3_rodata_B78 + fielder->distanceFromHomePlate < g_Ball.ballDistanceFromHome) {
            goto callTail;
        }
        return;

    callTail:
        setNewSelectedFielder_determinePriorSelectedFielder_sAutoMovement(g_FieldingLogic.secondaryFielder, 1);
        g_FieldingLogic.secondaryFielder = -1;
        return;
    }

    if (g_FieldingLogic.unkFlagMaybeInAir == 0) {
        return;
    }
    if (g_Ball.framesSinceHit < lbl_3_data_484C[3]) {
        return;
    }

    {
        s16 hist = fielderControlStick_continuousAngleHistory[0];

        if (hist < 0 || (g_FieldingLogic.fielderInputs & INPUT_BUTTON_B) == 0) {
            f64 thresh5 = (f64)lbl_3_data_484C[5] - lbl_3_rodata_B50;
            f64 thresh6;
            f64 thresh7;
            f64 x;

            if (g_Ball.ballDistanceFromHome < thresh5) {
                return;
            }
            thresh6 = (f64)lbl_3_data_484C[6] - lbl_3_rodata_B50;
            thresh7 = (f64)lbl_3_data_484C[7] - lbl_3_rodata_B50;
            x = (f64)g_Ball.physicsSubstruct.hitLandingSpotDistFromHome - thresh6;
            if (x > thresh7) {
                x = thresh7;
            }
            if (g_Ball.ballDistanceFromHome < x) {
                return;
            }
        }

        if (g_Fielders[selectedFielderInit].distanceFromLandingSpot < lbl_3_data_4848) {
            newFielder = selectedFielderInit;
        } else if (g_Fielders[secondaryFielderInit].distanceFromLandingSpot < lbl_3_data_4848) {
            newFielder = secondaryFielderInit;
        } else {
            if (g_Ball.framesSinceHit < lbl_3_data_484C[4]) {
                int i;

                if (hist <= 0) {
                    return;
                }
                for (i = 1; i < lbl_3_data_484C[8]; i++) {
                    s16 h = fielderControlStick_continuousAngleHistory[i];
                    if (h <= 0) {
                        break;
                    }
                    if (getDifferenceInAngle(hist, h) > 0x200) {
                        break;
                    }
                }
                if (i < lbl_3_data_484C[8]) {
                    return;
                }
            }
            {
                int selectedFielder = g_FieldingLogic.selectedFielder;
                int secondaryFielder = g_FieldingLogic.secondaryFielder;

                newFielder = SelectBetterFielder(
                    selectedFielder, secondaryFielder, 0,
                    lbl_3_rodata_B80 * (g_Fielders[selectedFielder].IntendedLocation.x +
                                         g_Fielders[secondaryFielder].IntendedLocation.x),
                    lbl_3_rodata_B80 * (g_Fielders[selectedFielder].IntendedLocation.z +
                                         g_Fielders[secondaryFielder].IntendedLocation.z));
            }
        }
    }

    if (newFielder < 0) {
        return;
    }

    if (newFielder == g_FieldingLogic.secondaryFielder) {
        if (g_FieldingLogic.someFielderIndex < 0) {
            int idx = g_FieldingLogic.selectedFielder;
            InMemFielder* f = &g_Fielders[idx];
            if (idx != -1) {
                f->autoMovementFunctionIndex = 24;
                if (autoMovementFunctions[24].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[idx] = autoMovementFunctions[24].code;
                }
                g_FieldingLogic.someFielderIndex = idx;
                f->unknown_writeOnly = 0;
                f->fielderVeloAdjustmentCode = 0;
                f->unknown_writeOnly_always0 = 0;
                f->timeSinceThrowWasCaught = 0;
                f->fielderTrackingBallState = 0;
            }
        } else {
            int idx = g_FieldingLogic.selectedFielder;
            InMemFielder* f = &g_Fielders[idx];
            if (idx != -1) {
                f->autoMovementFunctionIndex = 12;
                if (autoMovementFunctions[12].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[idx] = autoMovementFunctions[12].code;
                }
                f->unknown_writeOnly = 0;
                f->fielderVeloAdjustmentCode = 0;
                f->unknown_writeOnly_always0 = 0;
                f->timeSinceThrowWasCaught = 0;
                f->fielderTrackingBallState = 0;
            }
        }
        {
            int idx = g_FieldingLogic.secondaryFielder;
            InMemFielder* f = &g_Fielders[idx];
            if (idx != -1) {
                f->autoMovementFunctionIndex = 21;
                if (autoMovementFunctions[21].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[idx] = autoMovementFunctions[21].code;
                }
                f->unknown_writeOnly = 0;
                f->fielderVeloAdjustmentCode = 0;
                f->unknown_writeOnly_always0 = 0;
                f->timeSinceThrowWasCaught = 0;
                f->fielderTrackingBallState = 0;
            }
        }
        g_FieldingLogic.selectedFielder = g_FieldingLogic.secondaryFielder;
    } else {
        if (g_FieldingLogic.someFielderIndex < 0) {
            int idx = g_FieldingLogic.secondaryFielder;
            InMemFielder* f = &g_Fielders[idx];
            if (idx != -1) {
                f->autoMovementFunctionIndex = 24;
                if (autoMovementFunctions[24].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[idx] = autoMovementFunctions[24].code;
                }
                g_FieldingLogic.someFielderIndex = idx;
                f->unknown_writeOnly = 0;
                f->fielderVeloAdjustmentCode = 0;
                f->unknown_writeOnly_always0 = 0;
                f->timeSinceThrowWasCaught = 0;
                f->fielderTrackingBallState = 0;
            }
        } else {
            int idx = g_FieldingLogic.secondaryFielder;
            InMemFielder* f = &g_Fielders[idx];
            if (idx != -1) {
                f->autoMovementFunctionIndex = 12;
                if (autoMovementFunctions[12].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[idx] = autoMovementFunctions[12].code;
                }
                f->unknown_writeOnly = 0;
                f->fielderVeloAdjustmentCode = 0;
                f->unknown_writeOnly_always0 = 0;
                f->timeSinceThrowWasCaught = 0;
                f->fielderTrackingBallState = 0;
            }
        }
        {
            int idx = g_FieldingLogic.selectedFielder;
            InMemFielder* f = &g_Fielders[idx];
            if (idx != -1) {
                f->autoMovementFunctionIndex = 21;
                if (autoMovementFunctions[21].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[idx] = autoMovementFunctions[21].code;
                }
                f->unknown_writeOnly = 0;
                f->fielderVeloAdjustmentCode = 0;
                f->unknown_writeOnly_always0 = 0;
                f->timeSinceThrowWasCaught = 0;
                f->fielderTrackingBallState = 0;
            }
        }
    }

    g_FieldingLogic.secondaryFielder = -1;
    g_FieldingLogic.unkFlagMaybeInAir = 0;
}

// .text:0x00039DC4 size:0xEC mapped:0x80678E58
void unused_FUN_80678e58(void) {
    InMemFielder* f;
    int i;

    for (f = &g_Fielders[0], i = 0; i < 9; f++, i++) {
        g_FieldingLogic.fielderAutoMovementCode[i] = 0;
        if (i != -1) {
            f->autoMovementFunctionIndex = 0;
            if (autoMovementFunctions[0].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[i] = autoMovementFunctions[0].code;
            }
            f->unknown_writeOnly = 0;
            f->fielderVeloAdjustmentCode = 0;
            f->unknown_writeOnly_always0 = 0;
            f->timeSinceThrowWasCaught = 0;
            f->fielderTrackingBallState = 0;
        }
        f->maybeTargetPosX = lbl_3_rodata_C0C;
        f->maybeTargetPosZ = lbl_3_rodata_B20;
    }

    g_FieldingLogic.selectedFielder = -1;
    g_FieldingLogic.secondaryFielder = -1;
    g_FieldingLogic.tertiaryFielder = -1;
    g_FieldingLogic.cutoffFielderIndex = -1;
    g_FieldingLogic.unkFlagMaybeInAir = 0;
    g_FieldingLogic.fielderAssignedLocationIndex[0] = -1;
    g_FieldingLogic.baseCoveredInd[0] = 0;
    g_FieldingLogic.fielderAssignedLocationIndex[1] = -1;
    g_FieldingLogic.baseCoveredInd[1] = 0;
    g_FieldingLogic.fielderAssignedLocationIndex[2] = -1;
    g_FieldingLogic.baseCoveredInd[2] = 0;
    g_FieldingLogic.fielderAssignedLocationIndex[3] = -1;
    g_FieldingLogic.baseCoveredInd[3] = 0;

    selectClosestFielderBasedOnFutureCoord(0x78);
}

// .text:0x00039EB0 size:0x34C mapped:0x80678F44
void updateFielderSelection(void) {
    InMemFielder* f;
    int i;
    s16 selectedFielder;
    int stillCountingDown = 1;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE &&
        g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_BATTING) {
        return;
    }

    if (g_Ball.deadBallReason != 0) {
        return;
    }
    if (g_Ball.ballState == BALL_STATE_HELD) {
        return;
    }

    if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR && g_Ball.maxYOfHit > lbl_3_rodata_BE4) {
        if (g_Ball.framesSinceHit < specialFielderActionConstants._40[9]) {
            return;
        }
    } else {
        if (g_Ball.framesSinceHit < specialFielderActionConstants._40[10]) {
            return;
        }
    }

    if (g_Ball.ballState == BALL_STATE_THROWN) {
        if (g_Ball.framesUntilThrowReachesDest > 0 && g_Ball.fielderBeingThrownTo >= 0 &&
            g_Ball.framesSinceThrowStarted == 2) {
            if (g_FieldingLogic.locationThrownTo != 6) {
                setPlayerWhoCanInterceptThrow();
            }
            return;
        }
    }

    g_FieldingLogic.fielderAssignedLocationIndex[5]--;
    if (g_FieldingLogic.fielderAssignedLocationIndex[5] > 0) {
        stillCountingDown = 0;
    } else {
        g_FieldingLogic.fielderAssignedLocationIndex[5] = 0;
    }

    if (g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam] == 0) {
        if (g_FieldingLogic.fielderInputs & INPUT_TRIGGER_L) {
            return;
        }
    }

    selectedFielder = g_FieldingLogic.selectedFielder;

    if (selectedFielder >= 0 && g_Fielders[selectedFielder].clamberStatus != 0) {
        return;
    }

    if (!stillCountingDown) {
        return;
    }
    if (g_FieldingLogic.always0_0137 != 0) {
        return;
    }
    if (g_Ball.catchAnimationTotalFrames != 0) {
        return;
    }

    {
        int forceReselect = 0;

        if (selectedFielder < 0 && g_Ball.ballState == BALL_STATE_LOOSE) {
            forceReselect = 1;
        }

        if (g_FieldingLogic.knockoutFinished == 0 && !forceReselect) {
            goto skipReset;
        }
    }
    {
        for (f = &g_Fielders[0], i = 0; i < 9; f++, i++) {
            g_FieldingLogic.fielderAutoMovementCode[i] = 0;
            if (i != -1) {
                f->autoMovementFunctionIndex = 0;
                if (autoMovementFunctions[0].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[i] = autoMovementFunctions[0].code;
                }
                f->unknown_writeOnly = 0;
                f->fielderVeloAdjustmentCode = 0;
                f->unknown_writeOnly_always0 = 0;
                f->timeSinceThrowWasCaught = 0;
                f->fielderTrackingBallState = 0;
            }
            f->maybeTargetPosX = lbl_3_rodata_C0C;
            f->maybeTargetPosZ = lbl_3_rodata_B20;
        }

        g_FieldingLogic.selectedFielder = -1;
        g_FieldingLogic.secondaryFielder = -1;
        g_FieldingLogic.tertiaryFielder = -1;
        g_FieldingLogic.cutoffFielderIndex = -1;
        g_FieldingLogic.unkFlagMaybeInAir = 0;
        g_FieldingLogic.fielderAssignedLocationIndex[0] = -1;
        g_FieldingLogic.baseCoveredInd[0] = 0;
        g_FieldingLogic.fielderAssignedLocationIndex[1] = -1;
        g_FieldingLogic.baseCoveredInd[1] = 0;
        g_FieldingLogic.fielderAssignedLocationIndex[2] = -1;
        g_FieldingLogic.baseCoveredInd[2] = 0;
        g_FieldingLogic.fielderAssignedLocationIndex[3] = -1;
        g_FieldingLogic.baseCoveredInd[3] = 0;

        selectClosestFielderBasedOnFutureCoord(0x78);

        if (g_FieldingLogic.selectedFielder >= 0) {
            g_FieldingLogic.knockoutFinished = 0;
        }
        return;
    }

skipReset:
    if (g_FieldingLogic.tertiaryFielder >= 0) {
        fielderSelect_tertiaryFielderExists_determine2FieldersToKeep();
        return;
    }

    if (g_FieldingLogic.infielderSelectedOnPopFlyInd != 0) {
        if (selectedFielder == 3 || selectedFielder == 5) {
            HandleMiddleInfieldSelection();
            return;
        }
    }

    if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR) {
        updateInAirFielderSelection();
    } else {
        updateBallLandedFielderSelection();
    }
}

// .text:0x0003A1FC size:0x38 mapped:0x80679290
void fn_3_3A1FC(int fielderIndex) {
    if (g_Fielders[fielderIndex].someCountDown2 != 0) {
        g_Fielders[fielderIndex].currentVelocity = g_Fielders[fielderIndex].lastFrameVelocityUpToBase;
    } else {
        g_Fielders[fielderIndex].currentVelocity = lbl_3_rodata_B20;
    }
}

// .text:0x0003A234 size:0x350 mapped:0x806792C8
void setFielderVelocity_someSituation(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    f32 speed = fielder->joggingSpeed;
    int idx = fielderIndex;
    int i;

    if (g_d_GameSettings.minigamesEnabled) {
        if (fielderIndex == 0) {
            idx = *((s8*)&g_Minigame + 0x18cc + (s8)g_Minigame.minigamePlayerSelectedOrder);
        } else {
            idx = ((s8*)g_Minigame.minigameControlStruct[1].aIStrength)[fielderIndex];
        }
    }

    if (fielder->framesSinceStartedMoving == 0) {
        int dir2 = radToShortAngle(fielder->desiredMovementDirection2);
        int dir1 = radToShortAngle(fielder->desiredMovementDirection);
        int ang = normalizeAngle(dir2 - dir1);

        if (ang < 0x200) {
            fielder->runningVsLookingAngleCode = 0;
        } else if (ang < 0x600) {
            fielder->runningVsLookingAngleCode = 3;
        } else if (ang < 0xA00) {
            fielder->runningVsLookingAngleCode = 1;
        } else if (ang < 0xE00) {
            fielder->runningVsLookingAngleCode = 2;
        } else {
            fielder->runningVsLookingAngleCode = 0;
        }

        if (fielder->standingStillInd != 1) {
            if (fielder->runningVsLookingAngleCode == 1) {
                fielder->runningVsLookingAngleCode = 5;
            } else {
                fielder->runningVsLookingAngleCode = 4;
            }
        }
    }

    if (fielder->runningVsLookingAngleCode == 4 || fielder->runningVsLookingAngleCode == 5) {
        fielder->currentVelocity =
            lbl_3_rodata_B80 * fielder->runningAccelerationFactor + fielder->currentVelocity;
    } else {
        fielder->currentVelocity = fielder->currentVelocity + fielder->runningAccelerationFactor;
    }

    for (i = 0; i < fielder->attachedKlaptrapCount; i++) {
        speed = speed * lbl_3_data_46F4;
    }

    if (fielder->currentVelocity > speed) {
        fielder->currentVelocity = speed;
    }

    if (g_FieldingLogic.dashPtr->dashingFielderIndex == fielderIndex) {
        fielder->currentVelocity = g_FieldingLogic.dashPtr->sprintSpeedMultiplier * speed;
    }

    if (g_Ball.fielderWBallIndex == fielderIndex) {
        if (checkFieldingStat(g_GameLogic.teamFielding, fielder->rosterLocation,
                              FIELDING_ABILITY_BALL_DASH)) {
            fielder->currentVelocity = fielder->currentVelocity * ballDashEffect_1_5;
            ((u8*)((void**)(hugeAnimStruct + 0x2c50))[idx])[0x27A] = 1;
            if (fielder->framesSinceStartedMoving == 1) {
                fieldingRelatedAnimations(((void**)(hugeAnimStruct + 0x2c50))[idx], 11);
            }
        }
    }

    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_STAR_DASH) {
        if ((s8)g_Minigame._1D6D == fielder->_020D) {
            fielder->currentVelocity = fielder->currentVelocity * lbl_3_data_21A14[6];
        }
        if ((s8)g_Minigame.playerIDWithPowerup[0] == fielder->_020D) {
            fielder->currentVelocity =
                fielder->currentVelocity * **(f32**)((u8*)&g_Minigame + 0x1D4C);
        }
    }
}

// .text:0x0003A584 size:0x574 mapped:0x80679618
void moveFielder_CheckForAndSetJump(void) {
    return;
}

// .text:0x0003AAF8 size:0xF8 mapped:0x80679B8C
void fn_3_3AAF8(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    int angle = fielderControlStick_continuousAngleHistory[0];
    FielderDash* dash;

    if (g_FieldingLogic.playOverInd != 0) {
        angle = -1;
    }
    fielder->movementAngle = angle;

    if (g_GameLogic.autoFielding[g_GameLogic.awayTeamBattingInd_battingTeam] == 0) {
        if (angle >= 0) {
            if (fielder->framesSinceStartedMoving > 10) {
                g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
            }
        }
    }

    if (angle < 0) {
        return;
    }

    dash = g_FieldingLogic.dashPtr;
    if (dash->sprintingState == 3) {
        return;
    }
    if (dash->sprintingState == 4) {
        return;
    }

    if (g_FieldingLogic.fielderInputsLatestFrame & INPUT_BUTTON_B) {
        dash->framesSinceLastDashInput = 0;
    }

    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE) {
        return;
    }

    if (g_Practice.instructionNumber < 0) {
        return;
    }

    if (g_Practice.practice_fielding_enableSprinting == 0) {
        return;
    }

    g_FieldingLogic.dashPtr->framesSinceLastDashInput = 0;
}

// .text:0x0003ABF0 size:0xD0 mapped:0x80679C84
void fn_3_3ABF0(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    int selectedFielder = g_FieldingLogic.selectedFielder;
    InMemFielder* selected = &g_Fielders[selectedFielder];

    if (g_Ball.framesSinceHit < lbl_3_data_484C[0]) {
        return;
    }

    if (g_FieldingLogic.unkFlagMaybeInAir != 0) {
        return;
    }

    if (!(selected->closingInOnCatchingFlyBall == 1 &&
          fielder->distanceFromEachFielder[selectedFielder] < lbl_3_rodata_B70)) {
        if (selected->catchAnimation == 0 ||
            selected->autoCatch0_noCatchAnimationOnly1 != 0) {
            return;
        }
    }

    g_Fielders[fielderIndex].IntendedLocation.x = fielder->pos.x;
    g_Fielders[fielderIndex].IntendedLocation.y = fielder->pos.y;
    g_Fielders[fielderIndex].IntendedLocation.z = fielder->pos.z;
    g_Fielders[fielderIndex].velocityX = lbl_3_rodata_B20;
    g_Fielders[fielderIndex].velocityZ = lbl_3_rodata_B20;
    g_Fielders[fielderIndex].currentVelocity = lbl_3_rodata_B20;
    g_Fielders[fielderIndex].distanceFromAutoLocation = lbl_3_rodata_B20;
}

// .text:0x0003ACC0 size:0x174 mapped:0x80679D54
void updateFielderMovementIfNoBall(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    int framesSinceHit;
    s16 stickDir;
    s16 runAngle;

    if (g_Ball.fielderWithBallIndexStored < 0) {
        if (fielderIndex != g_FieldingLogic.selectedFielder) {
            return;
        }
        if (g_FieldingLogic.unkFlagMaybeInAir != 0) {
            return;
        }
        framesSinceHit = g_Ball.framesSinceHit;
        if (framesSinceHit < lbl_3_data_484C[0]) {
            return;
        }
        if (framesSinceHit < lbl_3_data_484C[1]) {
            if (fielderControlStick_continuousAngleHistory[0] < 0 ||
                (g_FieldingLogic.fielderInputs & INPUT_BUTTON_B) == 0) {
                if (g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE ||
                    g_Practice.instructionNumber < 0 ||
                    g_Practice.practice_fielding_enableSprinting == 0) {
                    if (fielder->fielderIsInitialOutfielderSelectedInd != 0 &&
                        fielderIndex >= 6 && fielderIndex <= 8 &&
                        g_Ball.ballZoneAwayFromHome == 0) {
                        return;
                    }
                    stickDir = currentStickDirection;
                    if (stickDir < 0) {
                        return;
                    }
                    runAngle = fielder->runningAngle;
                    if (runAngle < 0) {
                        if (framesSinceHit <= fielder->lockoutDuration + 3) {
                            return;
                        }
                    } else {
                        if (getDifferenceInAngle(stickDir, runAngle) >= lbl_3_data_484C[2]) {
                            return;
                        }
                    }
                }
            }
        }
    }
    fielder->fielderTrackingBallState = 2;
    fielder->fielderIsInitialOutfielderSelectedInd = 0;
}

// .text:0x0003AE34 size:0x53C mapped:0x80679EC8
void autoMovement21_23_humanControlInitialSelectedFielders(int fielderIndex) {
    return;
}

// .text:0x0003B370 size:0x3F4 mapped:0x8067A404
void autoMovement15_selectedFielderOnLooseBall(int fielderIndex) {
    return;
}

extern f32 ballDistCalculator(f32 x, f32 z);

// .text:0x0003B764 size:0x238 mapped:0x8067A7F8
void fn_3_3B764(void) {
    InMemFielder* fielder = &g_Fielders[g_FieldingLogic.selectedFielder];
    f32 dx;
    f32 dz;
    f32 sqx;
    f32 sqz;
    f32 dist;

    if (g_FieldingLogic.locationThrownTo >= 0) {
        g_Ball.fielderAboutToGetBall_hasBall = -1;
        return;
    }

    if (g_FieldingLogic.selectedFielder < 0) {
        return;
    }

    if (g_Ball.looseBall_5FrameCountdown != 0) {
        return;
    }

    if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR) {
        if (fielder->distanceFromLandingSpot < lbl_3_rodata_B64) {
            g_Ball.fielderAboutToGetBall_hasBall = g_FieldingLogic.selectedFielder;
        } else {
            g_Ball.fielderAboutToGetBall_hasBall = -1;
        }
    } else {
        dx = fielder->pos.x - g_Ball.physicsSubstruct.futureCoordsAndDist[1].pos.x;
        dz = fielder->pos.z - g_Ball.physicsSubstruct.futureCoordsAndDist[1].pos.z;
        sqx = dx * dx;
        sqz = dz * dz;
        dist = fielderSqrt(sqx + sqz);

        if (dist <= fielder->distanceFromBall) {
            f32 result = ballDistCalculator(fielder->pos.x, fielder->pos.z);
            if (result < fielder->hitbox[0]) {
                g_Ball.fielderAboutToGetBall_hasBall = g_FieldingLogic.selectedFielder;
            } else {
                g_Ball.fielderAboutToGetBall_hasBall = -1;
            }
        }
    }

    if (g_Ball.fielderAboutToGetBall_hasBall >= 0) {
        g_Ball.ballIsLooseInd_unused = 0;
        g_Ball.looseBall_codeForHowLongUntilSomeoneWillGetIt = 0;
        g_Ball.fielderBeingThrownTo = -1;
    }
}

// .text:0x0003B99C size:0x48 mapped:0x8067AA30
void fn_3_3B99C(void) {
    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_PIRANHA_PANIC) {
        return;
    }
    if ((g_FieldingLogic.fielderInputsLatestFrame & 0x100) == 0) {
        return;
    }

    g_FieldingLogic.jumpDiveStruct->aPressed_decidingWhatActionToTake = 2;
    g_FieldingLogic.jumpDiveStruct->stickAngleWhenPressingA = fielderControlStick_continuousAngleHistory[0];
}

// .text:0x0003B9E4 size:0x46C mapped:0x8067AA78
void liveBallFielderControlHumanTeam(void) {
    return;
}

// .text:0x0003BE50 size:0x358 mapped:0x8067AEE4
void checkIfPlayerNeedsToMoveToCatchBall(void) {
    return;
}

// .text:0x0003C1A8 size:0x78 mapped:0x8067B23C
void autoMovement19_foulBall(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];

    if (fielder->animationRelatedInd == 0) {
        if (updateFielderPositionAndVelocityForSpecialActions(fielderIndex) == 0) {
            fielder->currentVelocity = lbl_3_rodata_B20;
            fielder->standingStillInd = 1;
            fielder->unknown_writeOnly = 0;
            fielder->IntendedLocation.x = fielder->pos.x;
            fielder->IntendedLocation.z = fielder->pos.z;
        }
    }
}

// .text:0x0003C220 size:0x50 mapped:0x8067B2B4
void autoMovement0_stayStill_exceptForSpecialActions(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];

    if (updateFielderPositionAndVelocityForSpecialActions(fielderIndex) == 0) {
        fielder->currentVelocity = lbl_3_rodata_B20;
        fielder->distanceFromAutoLocation = lbl_3_rodata_B20;
    }
}

// .text:0x0003C270 size:0x214 mapped:0x8067B304
int fn_3_3C270(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    f32 x;
    f32 z;
    f32 dz;
    f32 dx;

    fielder->locationResponsibleForCovering = 14;
    fielder->isResponsibleForCoveringALocation = 2;

    if (fielderIndex != -1) {
        fielder->autoMovementFunctionIndex = 14;
        if (autoMovementFunctions[14].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[14].code;
        }
        fielder->unknown_writeOnly = 0;
        fielder->fielderVeloAdjustmentCode = 0;
        fielder->unknown_writeOnly_always0 = 0;
        fielder->timeSinceThrowWasCaught = 0;
        fielder->fielderTrackingBallState = 0;
    }

    fielder->fielderVeloAdjustmentCode = 0xb;

    x = base_MoundCoordinates[4].x;
    z = base_MoundCoordinates[4].z;

    fielder->IntendedLocation.x = x;
    fielder->IntendedLocation.z = z;

    dz = z - fielder->pos.z;
    dx = x - fielder->pos.x;

    if (lbl_3_rodata_B20 == dx && lbl_3_rodata_B20 == dz) {
        fielder->currentVelocity = lbl_3_rodata_B20;
        fielder->distanceFromAutoLocation = lbl_3_rodata_B20;
    } else {
        fielder->desiredMovementDirection2 = ATAN2F(dz, dx);
        fielder->distanceFromAutoLocation = fielderSqrt(dx * dx + dz * dz);
    }

    fielder->goingToAutoLocationInd = 1;

    return 1;
}

// .text:0x0003C484 size:0x110 mapped:0x8067B518
int fn_3_3C484(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];

    if (fielder->distanceToBases[0] < lbl_3_rodata_B64) {
        fielder->locationResponsibleForCovering = 9;
    } else if (fielder->distanceToBases[1] < lbl_3_rodata_B64) {
        fielder->locationResponsibleForCovering = setFielderLocToBeNearBase(fielderIndex);
    } else if (fielder->distanceToBases[2] < lbl_3_rodata_B64) {
        fielder->locationResponsibleForCovering = setFielderLocToBeNearBase(fielderIndex);
    } else if (fielder->distanceToBases[3] < lbl_3_rodata_B64) {
        fielder->locationResponsibleForCovering = setFielderLocToBeNearBase(fielderIndex);
    } else {
        return 0;
    }

    fielder->isResponsibleForCoveringALocation = 2;

    if (fielderIndex != -1) {
        fielder->autoMovementFunctionIndex = 14;
        if (autoMovementFunctions[14].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[14].code;
        }
        fielder->unknown_writeOnly = 0;
        fielder->fielderVeloAdjustmentCode = 0;
        fielder->unknown_writeOnly_always0 = 0;
        fielder->timeSinceThrowWasCaught = 0;
        fielder->fielderTrackingBallState = 0;
    }

    fielder->fielderVeloAdjustmentCode = 11;
    return 1;
}

// .text:0x0003C594 size:0x5F8 mapped:0x8067B628
int runOffBaseOverride(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    int i;
    s16 assignedIdx;
    int baseIdx;
    int result;

    for (i = 0; i < 4; i++) {
        f32 myDist;
        f32 otherDist;

        if (g_FieldingLogic.baseCoveredInd[i] != 0) {
            continue;
        }

        assignedIdx = g_FieldingLogic.fielderAssignedLocationIndex[i];
        if (assignedIdx == g_Ball.fielderWBallIndex) {
            continue;
        }

        myDist = fielder->distanceToBases[i];
        if (myDist < lbl_3_rodata_B60) {
            baseIdx = i;
            goto found_loopBreak;
        }

        otherDist = g_Fielders[assignedIdx].distanceToBases[i];
        if (myDist >= otherDist - lbl_3_rodata_B68) {
            continue;
        }

        if (fielderIndex != 0) {
            baseIdx = i;
            goto found_loopBreak;
        }

        if (g_Ball.ballDistanceFromHome >= lbl_3_rodata_C10) {
            continue;
        }
        if (g_Ball.ballVelocity >= lbl_3_rodata_C14) {
            continue;
        }

        if (i == 1) {
            if (g_Ball.ballAngleFromHome > 0x200 && g_Ball.ballAngleFromHome < 0x400) {
                if (myDist < otherDist - lbl_3_rodata_B64) {
                    baseIdx = i;
                    goto found_loopBreak;
                }
            }
            continue;
        } else if (i != 3) {
            baseIdx = i;
            goto found_loopBreak;
        } else if (g_Ball.ballAngleFromHome <= 0x400) {
            baseIdx = i;
            goto found_loopBreak;
        } else if (g_Ball.ballAngleFromHome >= 0x600) {
            baseIdx = i;
            goto found_loopBreak;
        } else if (myDist < otherDist - lbl_3_rodata_B64) {
            baseIdx = i;
            goto found_loopBreak;
        }
    }

    if (g_FieldingLogic.playerAtMoundCutoffLocation != 0) {
        result = 0;
        goto end;
    }
    {
        s16 cutoffIdx = g_FieldingLogic.fielderAssignedLocationIndex[4];
        if (cutoffIdx == -1) {
            result = 0;
            goto end;
        }
        if (fielder->distanceToMound < lbl_3_rodata_B64 ||
            fielder->distanceToMound + lbl_3_rodata_B78 < g_Fielders[cutoffIdx].distanceToMound) {
            assignedIdx = cutoffIdx;
            goto found_moundCutoff;
        }
    }
    result = 0;
    goto end;

found_loopBreak:
    if (g_Ball.fielderBeingThrownTo == assignedIdx) {
        g_Ball.fielderBeingThrownTo = fielderIndex;
    }
    if (assignedIdx >= 0) {
        InMemFielder* other = &g_Fielders[assignedIdx];
        s16 otherLoc = other->locationResponsibleForCovering;
        if (otherLoc >= 0) {
            if (otherLoc <= 3) {
                if (g_FieldingLogic.fielderAssignedLocationIndex[otherLoc] == assignedIdx) {
                    g_FieldingLogic.fielderAssignedLocationIndex[otherLoc] = -1;
                    g_FieldingLogic.baseCoveredInd[otherLoc] = 0;
                }
                other->locationResponsibleForCovering = -1;
                other->isResponsibleForCoveringALocation = 0;
                if (other->autoMovementFunctionIndex == 1 && assignedIdx != -1) {
                    other->autoMovementFunctionIndex = 12;
                    if (autoMovementFunctions[12].code >= 0) {
                        g_FieldingLogic.fielderAutoMovementCode[assignedIdx] = autoMovementFunctions[12].code;
                    }
                    other->unknown_writeOnly = 0;
                    other->fielderVeloAdjustmentCode = 0;
                    other->unknown_writeOnly_always0 = 0;
                    other->timeSinceThrowWasCaught = 0;
                    other->fielderTrackingBallState = 0;
                }
            } else if (otherLoc == 5) {
                g_FieldingLogic.fielderAssignedLocationIndex[4] = -1;
                other->locationResponsibleForCovering = -1;
                other->isResponsibleForCoveringALocation = 0;
                g_FieldingLogic.playerAtMoundCutoffLocation = 0;
                if (other->autoMovementFunctionIndex == 14 && assignedIdx != -1) {
                    other->autoMovementFunctionIndex = 12;
                    if (autoMovementFunctions[12].code >= 0) {
                        g_FieldingLogic.fielderAutoMovementCode[assignedIdx] = autoMovementFunctions[12].code;
                    }
                    other->unknown_writeOnly = 0;
                    other->fielderVeloAdjustmentCode = 0;
                    other->unknown_writeOnly_always0 = 0;
                    other->timeSinceThrowWasCaught = 0;
                    other->fielderTrackingBallState = 0;
                }
            }
        }
        if (assignedIdx != -1) {
            other->autoMovementFunctionIndex = 12;
            if (autoMovementFunctions[12].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[assignedIdx] = autoMovementFunctions[12].code;
            }
            other->unknown_writeOnly = 0;
            other->fielderVeloAdjustmentCode = 0;
            other->unknown_writeOnly_always0 = 0;
            other->timeSinceThrowWasCaught = 0;
            other->fielderTrackingBallState = 0;
        }
        other->unknown_writeOnly = 3;
    }
    fielder->locationResponsibleForCovering = baseIdx;
    fielder->isResponsibleForCoveringALocation = 1;
    if (fielderIndex != -1) {
        fielder->autoMovementFunctionIndex = 1;
        if (autoMovementFunctions[1].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[1].code;
        }
        fielder->unknown_writeOnly = 0;
        fielder->fielderVeloAdjustmentCode = 0;
        fielder->unknown_writeOnly_always0 = 0;
        fielder->timeSinceThrowWasCaught = 0;
        fielder->fielderTrackingBallState = 0;
    }
    g_FieldingLogic.fielderAssignedLocationIndex[baseIdx] = fielderIndex;
    result = 1;
    goto end;

found_moundCutoff:
    if (assignedIdx >= 0 && assignedIdx != g_Ball.fielderWBallIndex) {
        InMemFielder* other = &g_Fielders[assignedIdx];
        s16 otherLoc = other->locationResponsibleForCovering;
        if (otherLoc >= 0) {
            if (otherLoc <= 3) {
                if (g_FieldingLogic.fielderAssignedLocationIndex[otherLoc] == assignedIdx) {
                    g_FieldingLogic.fielderAssignedLocationIndex[otherLoc] = -1;
                    g_FieldingLogic.baseCoveredInd[otherLoc] = 0;
                }
                other->locationResponsibleForCovering = -1;
                other->isResponsibleForCoveringALocation = 0;
                if (other->autoMovementFunctionIndex == 1 && assignedIdx != -1) {
                    other->autoMovementFunctionIndex = 12;
                    if (autoMovementFunctions[12].code >= 0) {
                        g_FieldingLogic.fielderAutoMovementCode[assignedIdx] = autoMovementFunctions[12].code;
                    }
                    other->unknown_writeOnly = 0;
                    other->fielderVeloAdjustmentCode = 0;
                    other->unknown_writeOnly_always0 = 0;
                    other->timeSinceThrowWasCaught = 0;
                    other->fielderTrackingBallState = 0;
                }
            } else if (otherLoc == 5) {
                g_FieldingLogic.fielderAssignedLocationIndex[4] = -1;
                other->locationResponsibleForCovering = -1;
                other->isResponsibleForCoveringALocation = 0;
                g_FieldingLogic.playerAtMoundCutoffLocation = 0;
                if (other->autoMovementFunctionIndex == 14 && assignedIdx != -1) {
                    other->autoMovementFunctionIndex = 12;
                    if (autoMovementFunctions[12].code >= 0) {
                        g_FieldingLogic.fielderAutoMovementCode[assignedIdx] = autoMovementFunctions[12].code;
                    }
                    other->unknown_writeOnly = 0;
                    other->fielderVeloAdjustmentCode = 0;
                    other->unknown_writeOnly_always0 = 0;
                    other->timeSinceThrowWasCaught = 0;
                    other->fielderTrackingBallState = 0;
                }
            }
        }
        if (assignedIdx != -1) {
            other->autoMovementFunctionIndex = 12;
            if (autoMovementFunctions[12].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[assignedIdx] = autoMovementFunctions[12].code;
            }
            other->unknown_writeOnly = 0;
            other->fielderVeloAdjustmentCode = 0;
            other->unknown_writeOnly_always0 = 0;
            other->timeSinceThrowWasCaught = 0;
            other->fielderTrackingBallState = 0;
        }
        other->unknown_writeOnly = 4;
    }
    fielder->locationResponsibleForCovering = 5;
    fielder->isResponsibleForCoveringALocation = 2;
    if (fielderIndex != -1) {
        fielder->autoMovementFunctionIndex = 14;
        if (autoMovementFunctions[14].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[14].code;
        }
        fielder->unknown_writeOnly = 0;
        fielder->fielderVeloAdjustmentCode = 0;
        fielder->unknown_writeOnly_always0 = 0;
        fielder->timeSinceThrowWasCaught = 0;
        fielder->fielderTrackingBallState = 0;
    }
    g_FieldingLogic.fielderAssignedLocationIndex[4] = fielderIndex;
    result = 1;

end:
    return result;
}

// .text:0x0003CB8C size:0x124 mapped:0x8067BC20
int fn_3_3CB8C(int fielderIndex) {
    InMemFielder* fielder;

    if (g_Ball.AtBat_ContactResult > 1) {
        return 0;
    }
    if (g_Ball.hitWallInd != 0) {
        return 0;
    }
    if (g_FieldingLogic.someFielderIndex >= 0) {
        return 0;
    }

    if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR) {
        if (g_Ball.landingSpotZoneAwayFromHome < 1 || fielderIndex < 6) {
            goto fail;
        }
        if (g_Ball.landingSpotAngle < 0x380 && fielderIndex == 6) {
            return 0;
        }
        if (g_Ball.landingSpotAngle > 0x480 && fielderIndex == 8) {
            return 0;
        }
    } else if (fielderIndex < 6 || fielderIndex != g_FieldingLogic.secondaryFielderStored) {
    fail:
        return 0;
    }

    fielder = &g_Fielders[fielderIndex];
    if (fielderIndex != -1) {
        fielder->autoMovementFunctionIndex = 24;
        if (autoMovementFunctions[24].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[24].code;
        }
        g_FieldingLogic.someFielderIndex = fielderIndex;
        fielder->unknown_writeOnly = 0;
        fielder->fielderVeloAdjustmentCode = 0;
        fielder->unknown_writeOnly_always0 = 0;
        fielder->timeSinceThrowWasCaught = 0;
        fielder->fielderTrackingBallState = 0;
    }
    g_FieldingLogic.someFielderIndex = fielderIndex;
    return 1;
}

// .text:0x0003CCB0 size:0x654 mapped:0x8067BD44
void autoMovement9_OffBase_coverHome(int fielderIndex) {
    return;
}

// .text:0x0003D304 size:0x3A8 mapped:0x8067C398
void autoMovement17_runningOffField(int fielderIndex) {
    return;
}

// .text:0x0003D6AC size:0x128 mapped:0x8067C740
void autoMovement12_stopBetweenInstructions(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];

    if (updateFielderPositionAndVelocityForSpecialActions(fielderIndex) == 0 && fielder->animationRelatedInd == 0) {
        fielder->currentVelocity = lbl_3_rodata_B20;
        fielder->standingStillInd = 1;
        fielder->unknown_writeOnly = 0;
        fielder->IntendedLocation.x = fielder->pos.x;
        fielder->IntendedLocation.z = fielder->pos.z;

        if (g_Ball.ballState == BALL_STATE_HIT) {
            if (fielderIndex == 6) {
                if (g_Ball.ballAngleFromHome < 0x400 || g_Ball.ballAngleFromHome >= 0xc00) {
                    goto skip;
                }
            } else if (fielderIndex == 8) {
                if (g_Ball.ballAngleFromHome >= 0x400 && g_Ball.ballAngleFromHome < 0xc00) {
                    goto skip;
                }
            }
        }

        if (fielderIndex != -1) {
            fielder->autoMovementFunctionIndex = 9;
            if (autoMovementFunctions[9].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[9].code;
            }
            fielder->unknown_writeOnly = 0;
            fielder->fielderVeloAdjustmentCode = 0;
            fielder->unknown_writeOnly_always0 = 0;
            fielder->timeSinceThrowWasCaught = 0;
            fielder->fielderTrackingBallState = 0;
        }

skip:
        fielder->unused_jumpActiveOrRunningCatchRelated = 1;
    }
}

// .text:0x0003D7D4 size:0x3A4 mapped:0x8067C868
int setFielderLocToBeNearBase(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    int result;
    int i;

    if (fielder->pos.x > lbl_3_rodata_B20) {
        if (fielder->distanceToBases[2] > fielder->distanceToBases[1]) {
            result = 0xa;
        } else {
            result = 0xb;
        }
    } else {
        if (fielder->distanceToBases[2] > fielder->distanceToBases[3]) {
            result = 0xd;
        } else {
            result = 0xc;
        }
    }

    if (result == 0xa) {
        for (i = 0; i < 6; i++) {
            if (i != fielderIndex && g_Fielders[i].locationResponsibleForCovering == 0xa) {
                result = 0xb;
            }
        }
    } else if (result == 0xb) {
        for (i = 0; i < 6; i++) {
            if (i != fielderIndex && g_Fielders[i].locationResponsibleForCovering == 0xa) {
                result = 0xc;
            }
        }
    } else if (result == 0xc) {
        for (i = 0; i < 6; i++) {
            if (i != fielderIndex && g_Fielders[i].locationResponsibleForCovering == 0xa) {
                result = 0xb;
            }
        }
    } else if (result == 0xd) {
        for (i = 0; i < 6; i++) {
            if (i != fielderIndex && g_Fielders[i].locationResponsibleForCovering == 0xa) {
                result = 0xc;
            }
        }
    }

    return result;
}

// .text:0x0003DB78 size:0x7D4 mapped:0x8067CC0C
void autoMovement14_infieldSupport(int fielderIndex) {
    return;
}

// .text:0x0003E34C size:0x11C mapped:0x8067D3E0
void autoMovement20_pitcherLinedriveRelated(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];

    if (fielder->fielderReadiness >= 1) {
        if (fielder->AI_Ind != 0) {
            if (fielderIndex == -1) {
                return;
            }
            fielder->autoMovementFunctionIndex = 18;
            if (autoMovementFunctions[18].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[18].code;
            }
            fielder->unknown_writeOnly = 0;
            fielder->fielderVeloAdjustmentCode = 0;
            fielder->unknown_writeOnly_always0 = 0;
            fielder->timeSinceThrowWasCaught = 0;
            fielder->fielderTrackingBallState = 0;
            return;
        }

        if (fielderIndex == -1) {
            return;
        }
        fielder->autoMovementFunctionIndex = 0;
        if (autoMovementFunctions[0].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[0].code;
        }
        fielder->unknown_writeOnly = 0;
        fielder->fielderVeloAdjustmentCode = 0;
        fielder->unknown_writeOnly_always0 = 0;
        fielder->timeSinceThrowWasCaught = 0;
        fielder->fielderTrackingBallState = 0;
        return;
    }

    if (g_FieldingLogic.always0_ == 0) {
        return;
    }
    if (fielderIndex == -1) {
        return;
    }
    fielder->autoMovementFunctionIndex = 0;
    if (autoMovementFunctions[0].code >= 0) {
        g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[0].code;
    }
    fielder->unknown_writeOnly = 0;
    fielder->fielderVeloAdjustmentCode = 0;
    fielder->unknown_writeOnly_always0 = 0;
    fielder->timeSinceThrowWasCaught = 0;
    fielder->fielderTrackingBallState = 0;
}

// .text:0x0003E468 size:0x228 mapped:0x8067D4FC
void fn_3_3E468(void) {
    int baseIndex;

    for (baseIndex = 0; baseIndex < 9; baseIndex++) {
        g_Fielders[baseIndex].locationResponsibleForCovering = -1;
        g_Fielders[baseIndex].isResponsibleForCoveringALocation = 0;
    }
    g_FieldingLogic.fielderAssignedLocationIndex[0] = -1;
    g_FieldingLogic.baseCoveredInd[0] = 0;
    g_FieldingLogic.fielderAssignedLocationIndex[1] = -1;
    g_FieldingLogic.baseCoveredInd[1] = 0;
    g_FieldingLogic.fielderAssignedLocationIndex[2] = -1;
    g_FieldingLogic.baseCoveredInd[2] = 0;
    g_FieldingLogic.fielderAssignedLocationIndex[3] = -1;
    g_FieldingLogic.baseCoveredInd[3] = 0;
    g_FieldingLogic.fielderAssignedLocationIndex[4] = -1;
    g_FieldingLogic.playerAtMoundCutoffLocation = 0;

    for (baseIndex = 0; baseIndex < 4; baseIndex++) {
        int best;
        f32 minDist = lbl_3_rodata_C24;
        int k;

        for (k = 0; k < 6; k++) {
            if (g_FieldingLogic.fielderAutoMovementCode[k] == 0) {
                f32 d = g_Fielders[k].distanceToBases[baseIndex];
                if (d < minDist) {
                    minDist = d;
                    best = k;
                }
            }
        }

        g_Fielders[best].locationResponsibleForCovering = baseIndex;
        g_Fielders[best].isResponsibleForCoveringALocation = 1;
        if (best != -1) {
            InMemFielder* fielder = &g_Fielders[best];
            fielder->autoMovementFunctionIndex = 1;
            if (autoMovementFunctions[1].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[best] = autoMovementFunctions[1].code;
            }
            fielder->unknown_writeOnly = 0;
            fielder->fielderVeloAdjustmentCode = 0;
            fielder->unknown_writeOnly_always0 = 0;
            fielder->timeSinceThrowWasCaught = 0;
            fielder->fielderTrackingBallState = 0;
        }
        g_FieldingLogic.fielderAssignedLocationIndex[baseIndex] = best;
    }
}

// .text:0x0003E690 size:0x4DC mapped:0x8067D724
void knockoutRelated_Grounder_Liner(void) {
    InMemFielder* g = &g_Fielders[0];
    f32 targetZ = g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.z;
    f32 targetX = g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.x;
    u8 ballZone = g_Ball.ballZoneAwayFromHome;
    InMemFielder* fielder;
    int i;
    int framesNeeded;
    int priority;
    int bestPriority = 0x270f;
    int best;
    int baseIndex;

    for (fielder = g, i = 0; i < 9; fielder++, i++) {
        if (targetX == fielder->pos.x && targetZ == fielder->pos.z) {
            framesNeeded = 1;
        } else {
            f32 dx = targetX - fielder->pos.x;
            f32 dz = targetZ - fielder->pos.z;
            f32 sqx = dx * dx;
            f32 sqz = dz * dz;
            f32 dist = fielderSqrt(sqx + sqz);
            f32 speed = fielder->joggingSpeed;
            if (speed == lbl_3_rodata_B20) {
                speed = lbl_3_rodata_B60;
            }
            framesNeeded = ((u32)fielder->maxAccLength_ConstF >> 1) + (int)(dist / speed);
        }

        priority = framesNeeded;
        if (fielder->autoMovementFunctionIndex == 2) {
            priority -= 15;
        }
        if (fielder->locationResponsibleForCovering >= 0 && fielder->locationResponsibleForCovering <= 3) {
            priority += 30;
        }
        if (fielder->knockoutStatus != 0) {
            priority += fielder->knockOutCountDown;
        } else if (fielder->bodyCheckStatus == 3) {
            priority += 0x5a;
        }
        if (fielder->onFire != 0) {
            priority += fielder->onFireCountdown;
        }
        if (ballZone >= 3 && i <= 5) {
            priority += 30;
        }

        if (priority < bestPriority) {
            best = i;
            bestPriority = priority;
        }
    }

    {
        InMemFielder* f = &g_Fielders[best];
        if (best != -1) {
            f->autoMovementFunctionIndex = 3;
            if (autoMovementFunctions[3].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[best] = autoMovementFunctions[3].code;
            }
            f->unknown_writeOnly = 0;
            f->fielderVeloAdjustmentCode = 0;
            f->unknown_writeOnly_always0 = 0;
            f->timeSinceThrowWasCaught = 0;
            f->fielderTrackingBallState = 0;
        }
        knockoutRelated_subFn(best, 0);
        f->maybeMovementState = 4;
    }

    for (baseIndex = 0; baseIndex < 9; baseIndex++) {
        g[baseIndex].locationResponsibleForCovering = -1;
        g[baseIndex].isResponsibleForCoveringALocation = 0;
    }
    g_FieldingLogic.fielderAssignedLocationIndex[0] = -1;
    g_FieldingLogic.baseCoveredInd[0] = 0;
    g_FieldingLogic.fielderAssignedLocationIndex[1] = -1;
    g_FieldingLogic.baseCoveredInd[1] = 0;
    g_FieldingLogic.fielderAssignedLocationIndex[2] = -1;
    g_FieldingLogic.baseCoveredInd[2] = 0;
    g_FieldingLogic.fielderAssignedLocationIndex[3] = -1;
    g_FieldingLogic.baseCoveredInd[3] = 0;
    g_FieldingLogic.fielderAssignedLocationIndex[4] = -1;
    g_FieldingLogic.playerAtMoundCutoffLocation = 0;

    for (baseIndex = 0; baseIndex < 4; baseIndex++) {
        int best2;
        f32 minDist = lbl_3_rodata_C24;
        int k;

        for (k = 0; k < 6; k++) {
            if (g_FieldingLogic.fielderAutoMovementCode[k] == 0) {
                f32 d = g_Fielders[k].distanceToBases[baseIndex];
                if (d < minDist) {
                    minDist = d;
                    best2 = k;
                }
            }
        }

        g_Fielders[best2].locationResponsibleForCovering = baseIndex;
        g_Fielders[best2].isResponsibleForCoveringALocation = 1;
        if (best2 != -1) {
            InMemFielder* fielder2 = &g_Fielders[best2];
            fielder2->autoMovementFunctionIndex = 1;
            if (autoMovementFunctions[1].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[best2] = autoMovementFunctions[1].code;
            }
            fielder2->unknown_writeOnly = 0;
            fielder2->fielderVeloAdjustmentCode = 0;
            fielder2->unknown_writeOnly_always0 = 0;
            fielder2->timeSinceThrowWasCaught = 0;
            fielder2->fielderTrackingBallState = 0;
        }
        g_FieldingLogic.fielderAssignedLocationIndex[baseIndex] = best2;
    }
    g_FieldingLogic.cutoffFielderIndex = -1;
}

// .text:0x0003EB6C size:0x4C8 mapped:0x8067DC00
void knockoutRelated_FlyBall(void) {
    InMemFielder* g = &g_Fielders[0];
    f32 targetZ = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
    f32 targetX = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
    u8 someCollision = g_Ball.someCollisionInd;
    u8 ballZone = g_Ball.ballZoneAwayFromHome;
    InMemFielder* fielder;
    int i;
    int framesNeeded;
    int priority;
    int bestPriority = 0x270f;
    int best;
    int baseIndex;

    for (fielder = g, i = 0; i < 9; fielder++, i++) {
        if (targetX == fielder->pos.x && targetZ == fielder->pos.z) {
            framesNeeded = 1;
        } else {
            f32 dx = targetX - fielder->pos.x;
            f32 dz = targetZ - fielder->pos.z;
            f32 sqx = dx * dx;
            f32 sqz = dz * dz;
            f32 dist = fielderSqrt(sqx + sqz);
            f32 speed = fielder->joggingSpeed;
            if (speed == lbl_3_rodata_B20) {
                speed = lbl_3_rodata_B60;
            }
            framesNeeded = ((u32)fielder->maxAccLength_ConstF >> 1) + (int)(dist / speed);
        }

        priority = framesNeeded;
        if (fielder->autoMovementFunctionIndex == 2) {
            priority -= 15;
        }
        if (fielder->locationResponsibleForCovering >= 0 && fielder->locationResponsibleForCovering <= 3) {
            priority += 30;
        }
        if (someCollision == 0) {
            if (lbl_3_rodata_B64 + fielder->distanceFromHomePlate < g_Ball.physicsSubstruct.hitLandingSpotDistFromHome) {
                priority += 30;
            }
        }
        if (ballZone >= 3 && i <= 5) {
            priority += 15;
        }

        if (priority < bestPriority) {
            best = i;
            bestPriority = priority;
        }
    }

    {
        InMemFielder* f = &g_Fielders[best];
        if (best != -1) {
            f->autoMovementFunctionIndex = 3;
            if (autoMovementFunctions[3].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[best] = autoMovementFunctions[3].code;
            }
            f->unknown_writeOnly = 0;
            f->fielderVeloAdjustmentCode = 0;
            f->unknown_writeOnly_always0 = 0;
            f->timeSinceThrowWasCaught = 0;
            f->fielderTrackingBallState = 0;
        }
        knockoutRelated_subFn(best, 0);
        f->maybeMovementState = 0;
    }

    for (baseIndex = 0; baseIndex < 9; baseIndex++) {
        g_Fielders[baseIndex].locationResponsibleForCovering = -1;
        g_Fielders[baseIndex].isResponsibleForCoveringALocation = 0;
    }
    g_FieldingLogic.fielderAssignedLocationIndex[0] = -1;
    g_FieldingLogic.baseCoveredInd[0] = 0;
    g_FieldingLogic.fielderAssignedLocationIndex[1] = -1;
    g_FieldingLogic.baseCoveredInd[1] = 0;
    g_FieldingLogic.fielderAssignedLocationIndex[2] = -1;
    g_FieldingLogic.baseCoveredInd[2] = 0;
    g_FieldingLogic.fielderAssignedLocationIndex[3] = -1;
    g_FieldingLogic.baseCoveredInd[3] = 0;
    g_FieldingLogic.fielderAssignedLocationIndex[4] = -1;
    g_FieldingLogic.playerAtMoundCutoffLocation = 0;

    for (baseIndex = 0; baseIndex < 4; baseIndex++) {
        int best2;
        f32 minDist = lbl_3_rodata_C24;
        int k;

        for (k = 0; k < 6; k++) {
            if (g_FieldingLogic.fielderAutoMovementCode[k] == 0) {
                f32 d = g_Fielders[k].distanceToBases[baseIndex];
                if (d < minDist) {
                    minDist = d;
                    best2 = k;
                }
            }
        }

        g_Fielders[best2].locationResponsibleForCovering = baseIndex;
        g_Fielders[best2].isResponsibleForCoveringALocation = 1;
        if (best2 != -1) {
            InMemFielder* fielder2 = &g_Fielders[best2];
            fielder2->autoMovementFunctionIndex = 1;
            if (autoMovementFunctions[1].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[best2] = autoMovementFunctions[1].code;
            }
            fielder2->unknown_writeOnly = 0;
            fielder2->fielderVeloAdjustmentCode = 0;
            fielder2->unknown_writeOnly_always0 = 0;
            fielder2->timeSinceThrowWasCaught = 0;
            fielder2->fielderTrackingBallState = 0;
        }
        g_FieldingLogic.fielderAssignedLocationIndex[baseIndex] = best2;
    }
    g_FieldingLogic.cutoffFielderIndex = -1;
}

// .text:0x0003F034 size:0xF0 mapped:0x8067E0C8
void knockoutRelated(void) {
    int i;
    InMemFielder* fielder;

    fielder = g_Fielders;
    for (i = 0; i < 9; i++, fielder++) {
        g_FieldingLogic.fielderAutoMovementCode[i] = 0;
        if (i != -1) {
            fielder->autoMovementFunctionIndex = 0;
            if (autoMovementFunctions[0].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[i] = autoMovementFunctions[0].code;
            }
            fielder->unknown_writeOnly = 0;
            fielder->fielderVeloAdjustmentCode = 0;
            fielder->unknown_writeOnly_always0 = 0;
            fielder->timeSinceThrowWasCaught = 0;
            fielder->fielderTrackingBallState = 0;
        }
    }

    g_FieldingLogic.fielderAssignedLocationIndex[0] = -1;
    g_FieldingLogic.baseCoveredInd[0] = 0;
    g_FieldingLogic.fielderAssignedLocationIndex[1] = -1;
    g_FieldingLogic.baseCoveredInd[1] = 0;
    g_FieldingLogic.fielderAssignedLocationIndex[2] = -1;
    g_FieldingLogic.baseCoveredInd[2] = 0;
    g_FieldingLogic.fielderAssignedLocationIndex[3] = -1;
    g_FieldingLogic.baseCoveredInd[3] = 0;
    g_FieldingLogic.someFielderIndex = -1;
    g_FieldingLogic.cutoffFielderIndex = -1;
    g_FieldingLogic.interceptThrowFielder = -1;

    if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR && g_Ball.hangtimeOfHit > 45) {
        knockoutRelated_FlyBall();
    } else {
        knockoutRelated_Grounder_Liner();
    }
}

// .text:0x0003F124 size:0x128 mapped:0x8067E1B8
void uncalled(void) {
    int avg;
    InMemFielder *f0 = &g_Fielders[0];

    f0->autoMovementFunctionIndex = 20;
    if (autoMovementFunctions[20].code >= 0) {
        g_FieldingLogic.fielderAutoMovementCode[0] = autoMovementFunctions[20].code;
    }
    f0->unknown_writeOnly = 0;
    f0->fielderVeloAdjustmentCode = 0;
    f0->unknown_writeOnly_always0 = 0;
    f0->timeSinceThrowWasCaught = 0;
    f0->fielderTrackingBallState = 0;

    avg = (g_Fielders[3].angleOfFieldersStartingPosition + g_Fielders[5].angleOfFieldersStartingPosition) / 2;
    if (avg > g_Ball.Hit_HorizontalAngle) {
        InMemFielder *f = &g_Fielders[3];
        f->autoMovementFunctionIndex = 3;
        if (autoMovementFunctions[3].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[3] = autoMovementFunctions[3].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;
    } else {
        InMemFielder *f = &g_Fielders[5];
        f->autoMovementFunctionIndex = 3;
        if (autoMovementFunctions[3].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[5] = autoMovementFunctions[3].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;
    }

    setInitialFielderMovements_CoverBases();
    setInitialFielderMovements_cutoffs();
    setInitialFielderMovements_restOfFielders();
}

// .text:0x0003F24C size:0x514 mapped:0x8067E2E0
void fn_3_3F24C(void) {
    s16 vAngle = g_Ball.Hit_VerticalAngle;
    sAng angle = g_Ball.Hit_HorizontalAngle;
    InMemFielder *f;

    if (vAngle >= 0x400 && vAngle <= 0xc00) {
        angle += 0x800;
        if (angle > 0x1000) {
            angle -= 0x1000;
        }
    }

    if (angle > 0xa00 && angle < 0xe00) {
        f = &g_Fielders[1];
        f->autoMovementFunctionIndex = 3;
        if (autoMovementFunctions[3].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[1] = autoMovementFunctions[3].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;
    } else if (angle >= 0xe00 || angle < 0x200) {
        if (vAngle > 0x800) {
            f = &g_Fielders[2];
            f->autoMovementFunctionIndex = 3;
            if (autoMovementFunctions[3].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[2] = autoMovementFunctions[3].code;
            }
            f->unknown_writeOnly = 0;
            f->fielderVeloAdjustmentCode = 0;
            f->unknown_writeOnly_always0 = 0;
            f->timeSinceThrowWasCaught = 0;
            f->fielderTrackingBallState = 0;
        } else if (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z < lbl_3_rodata_BA0) {
            f = &g_Fielders[1];
            f->autoMovementFunctionIndex = 3;
            if (autoMovementFunctions[3].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[1] = autoMovementFunctions[3].code;
            }
            f->unknown_writeOnly = 0;
            f->fielderVeloAdjustmentCode = 0;
            f->unknown_writeOnly_always0 = 0;
            f->timeSinceThrowWasCaught = 0;
            f->fielderTrackingBallState = 0;

            f = &g_Fielders[2];
            f->autoMovementFunctionIndex = 3;
            if (autoMovementFunctions[3].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[2] = autoMovementFunctions[3].code;
            }
            f->unknown_writeOnly = 0;
            f->fielderVeloAdjustmentCode = 0;
            f->unknown_writeOnly_always0 = 0;
            f->timeSinceThrowWasCaught = 0;
            f->fielderTrackingBallState = 0;
        } else if (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z < lbl_3_rodata_B9C) {
            f = &g_Fielders[2];
            f->autoMovementFunctionIndex = 3;
            if (autoMovementFunctions[3].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[2] = autoMovementFunctions[3].code;
            }
            f->unknown_writeOnly = 0;
            f->fielderVeloAdjustmentCode = 0;
            f->unknown_writeOnly_always0 = 0;
            f->timeSinceThrowWasCaught = 0;
            f->fielderTrackingBallState = 0;

            f = &g_Fielders[3];
            f->autoMovementFunctionIndex = 3;
            if (autoMovementFunctions[3].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[3] = autoMovementFunctions[3].code;
            }
            f->unknown_writeOnly = 0;
            f->fielderVeloAdjustmentCode = 0;
            f->unknown_writeOnly_always0 = 0;
            f->timeSinceThrowWasCaught = 0;
            f->fielderTrackingBallState = 0;
        } else {
            f = &g_Fielders[3];
            f->autoMovementFunctionIndex = 3;
            if (autoMovementFunctions[3].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[3] = autoMovementFunctions[3].code;
            }
            f->unknown_writeOnly = 0;
            f->fielderVeloAdjustmentCode = 0;
            f->unknown_writeOnly_always0 = 0;
            f->timeSinceThrowWasCaught = 0;
            f->fielderTrackingBallState = 0;

            f = &g_Fielders[8];
            f->autoMovementFunctionIndex = 3;
            if (autoMovementFunctions[3].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[8] = autoMovementFunctions[3].code;
            }
            f->unknown_writeOnly = 0;
            f->fielderVeloAdjustmentCode = 0;
            f->unknown_writeOnly_always0 = 0;
            f->timeSinceThrowWasCaught = 0;
            f->fielderTrackingBallState = 0;
        }
    } else {
        if (vAngle > 0x800) {
            f = &g_Fielders[4];
            f->autoMovementFunctionIndex = 3;
            if (autoMovementFunctions[3].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[4] = autoMovementFunctions[3].code;
            }
            f->unknown_writeOnly = 0;
            f->fielderVeloAdjustmentCode = 0;
            f->unknown_writeOnly_always0 = 0;
            f->timeSinceThrowWasCaught = 0;
            f->fielderTrackingBallState = 0;
        } else if (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z < lbl_3_rodata_BA0) {
            f = &g_Fielders[1];
            f->autoMovementFunctionIndex = 3;
            if (autoMovementFunctions[3].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[1] = autoMovementFunctions[3].code;
            }
            f->unknown_writeOnly = 0;
            f->fielderVeloAdjustmentCode = 0;
            f->unknown_writeOnly_always0 = 0;
            f->timeSinceThrowWasCaught = 0;
            f->fielderTrackingBallState = 0;

            f = &g_Fielders[4];
            f->autoMovementFunctionIndex = 3;
            if (autoMovementFunctions[3].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[4] = autoMovementFunctions[3].code;
            }
            f->unknown_writeOnly = 0;
            f->fielderVeloAdjustmentCode = 0;
            f->unknown_writeOnly_always0 = 0;
            f->timeSinceThrowWasCaught = 0;
            f->fielderTrackingBallState = 0;
        } else if (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z < lbl_3_rodata_B9C) {
            f = &g_Fielders[4];
            f->autoMovementFunctionIndex = 3;
            if (autoMovementFunctions[3].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[4] = autoMovementFunctions[3].code;
            }
            f->unknown_writeOnly = 0;
            f->fielderVeloAdjustmentCode = 0;
            f->unknown_writeOnly_always0 = 0;
            f->timeSinceThrowWasCaught = 0;
            f->fielderTrackingBallState = 0;

            f = &g_Fielders[5];
            f->autoMovementFunctionIndex = 3;
            if (autoMovementFunctions[3].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[5] = autoMovementFunctions[3].code;
            }
            f->unknown_writeOnly = 0;
            f->fielderVeloAdjustmentCode = 0;
            f->unknown_writeOnly_always0 = 0;
            f->timeSinceThrowWasCaught = 0;
            f->fielderTrackingBallState = 0;
        } else {
            f = &g_Fielders[5];
            f->autoMovementFunctionIndex = 3;
            if (autoMovementFunctions[3].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[5] = autoMovementFunctions[3].code;
            }
            f->unknown_writeOnly = 0;
            f->fielderVeloAdjustmentCode = 0;
            f->unknown_writeOnly_always0 = 0;
            f->timeSinceThrowWasCaught = 0;
            f->fielderTrackingBallState = 0;

            f = &g_Fielders[6];
            f->autoMovementFunctionIndex = 3;
            if (autoMovementFunctions[3].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[6] = autoMovementFunctions[3].code;
            }
            f->unknown_writeOnly = 0;
            f->fielderVeloAdjustmentCode = 0;
            f->unknown_writeOnly_always0 = 0;
            f->timeSinceThrowWasCaught = 0;
            f->fielderTrackingBallState = 0;
        }
    }

    setInitialFielderMovements_CoverBases();
    setInitialFielderMovements_cutoffs();
    setInitialFielderMovements_restOfFielders();
}

// .text:0x0003F760 size:0x590 mapped:0x8067E7F4
void fn_3_3F760(void) {
    return;
}

// .text:0x0003FCF0 size:0x5B8 mapped:0x8067ED84
void fn_3_3FCF0(void) {
    return;
}

// .text:0x000402A8 size:0x95C mapped:0x8067F33C
void fn_3_402A8(void) {
    return;
}

// .text:0x00040C04 size:0x150 mapped:0x8067FC98
void fn_3_40C04(void) {
    InMemFielder* f = &g_Fielders[2];
    int i;

    for (i = 2; i < 6; f++, i++) {
        if (f->catchStrategy == 2) {
            InMemFielder* f2 = &g_Fielders[i];
            if (i != -1) {
                f2->autoMovementFunctionIndex = 3;
                if (autoMovementFunctions[3].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[i] = autoMovementFunctions[3].code;
                }
                f2->unknown_writeOnly = 0;
                f2->fielderVeloAdjustmentCode = 0;
                f2->unknown_writeOnly_always0 = 0;
                f2->timeSinceThrowWasCaught = 0;
                f2->fielderTrackingBallState = 0;
            }
            break;
        }
    }

    if (i == 2) {
        InMemFielder* f3 = &g_Fielders[3];
        f3->autoMovementFunctionIndex = 3;
        if (autoMovementFunctions[3].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[3] = autoMovementFunctions[3].code;
        }
        f3->unknown_writeOnly = 0;
        f3->fielderVeloAdjustmentCode = 0;
        f3->unknown_writeOnly_always0 = 0;
        f3->timeSinceThrowWasCaught = 0;
        f3->fielderTrackingBallState = 0;
    }

    if (i == 4) {
        InMemFielder* f5 = &g_Fielders[5];
        f5->autoMovementFunctionIndex = 3;
        if (autoMovementFunctions[3].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[5] = autoMovementFunctions[3].code;
        }
        f5->unknown_writeOnly = 0;
        f5->fielderVeloAdjustmentCode = 0;
        f5->unknown_writeOnly_always0 = 0;
        f5->timeSinceThrowWasCaught = 0;
        f5->fielderTrackingBallState = 0;
    }

    fn_3_40D88();
}

// .text:0x00040D54 size:0x34 mapped:0x8067FDE8
#pragma dont_inline on
void fn_3_40D54(void) {
    autoMovementDetermineWhatToDo(6, 7);
    autoMovementDetermineWhatToDo(8, 6);
}
#pragma dont_inline reset

// .text:0x00040D88 size:0x424 mapped:0x8067FE1C
void fn_3_40D88(void) {
    if (!g_Fielders[8].nonCatchFlyBallStratInd && !g_Fielders[6].nonCatchFlyBallStratInd) {
        InMemFielder *f;

        f = &g_Fielders[6];
        f->autoMovementFunctionIndex = 3;
        if (autoMovementFunctions[3].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[6] = autoMovementFunctions[3].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;

        f = &g_Fielders[7];
        f->autoMovementFunctionIndex = 3;
        if (autoMovementFunctions[3].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[7] = autoMovementFunctions[3].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;

        f = &g_Fielders[8];
        f->autoMovementFunctionIndex = 3;
        if (autoMovementFunctions[3].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[8] = autoMovementFunctions[3].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;
    } else if (!g_Fielders[8].nonCatchFlyBallStratInd) {
        InMemFielder *f;

        f = &g_Fielders[8];
        f->autoMovementFunctionIndex = 3;
        if (autoMovementFunctions[3].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[8] = autoMovementFunctions[3].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;

        f = &g_Fielders[7];
        f->autoMovementFunctionIndex = 3;
        if (autoMovementFunctions[3].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[7] = autoMovementFunctions[3].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;
    } else if (!g_Fielders[6].nonCatchFlyBallStratInd) {
        InMemFielder *f;

        f = &g_Fielders[6];
        f->autoMovementFunctionIndex = 3;
        if (autoMovementFunctions[3].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[6] = autoMovementFunctions[3].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;

        f = &g_Fielders[7];
        f->autoMovementFunctionIndex = 3;
        if (autoMovementFunctions[3].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[7] = autoMovementFunctions[3].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;
    } else if (!g_Fielders[7].nonCatchFlyBallStratInd) {
        InMemFielder *f;

        f = &g_Fielders[6];
        f->autoMovementFunctionIndex = 3;
        if (autoMovementFunctions[3].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[6] = autoMovementFunctions[3].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;

        f = &g_Fielders[7];
        f->autoMovementFunctionIndex = 3;
        if (autoMovementFunctions[3].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[7] = autoMovementFunctions[3].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;

        f = &g_Fielders[8];
        f->autoMovementFunctionIndex = 3;
        if (autoMovementFunctions[3].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[8] = autoMovementFunctions[3].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;
    } else if (g_Fielders[7].angleOfFieldersStartingPosition > g_Ball.Hit_HorizontalAngle) {
        InMemFielder *f;

        f = &g_Fielders[8];
        f->autoMovementFunctionIndex = 3;
        if (autoMovementFunctions[3].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[8] = autoMovementFunctions[3].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;

        f = &g_Fielders[7];
        f->autoMovementFunctionIndex = 3;
        if (autoMovementFunctions[3].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[7] = autoMovementFunctions[3].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;
    } else {
        InMemFielder *f;

        f = &g_Fielders[6];
        f->autoMovementFunctionIndex = 3;
        if (autoMovementFunctions[3].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[6] = autoMovementFunctions[3].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;

        f = &g_Fielders[7];
        f->autoMovementFunctionIndex = 3;
        if (autoMovementFunctions[3].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[7] = autoMovementFunctions[3].code;
        }
        f->unknown_writeOnly = 0;
        f->fielderVeloAdjustmentCode = 0;
        f->unknown_writeOnly_always0 = 0;
        f->timeSinceThrowWasCaught = 0;
        f->fielderTrackingBallState = 0;
    }

    setInitialFielderMovements_CoverBases();
    setInitialFielderMovements_cutoffs();
    fn_3_40D54();
}

// .text:0x000411AC size:0x628 mapped:0x80680240
void aITeamFieldingFirstFrameAfterHit(void) {
    return;
}

// .text:0x000417D4 size:0x1A8 mapped:0x80680868
void fn_3_417D4(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    f32 dx;
    f32 dz;
    f32 dxSq;
    f32 dzSq;
    f32 dist;

    dx = g_Ball.physicsSubstruct.futureCoordsAndDist[10].pos.x - fielder->pos.x;
    dz = g_Ball.physicsSubstruct.futureCoordsAndDist[10].pos.z - fielder->pos.z;
    dxSq = dx * dx;
    dzSq = dz * dz;
    dist = fielderSqrt(dxSq + dzSq);

    if (dist < lbl_3_rodata_C38 && fielder->catchStrategy == 2
        && g_Ball.physicsSubstruct.futureCoordsAndDist[10].pos.y > fielder->hitbox[3]) {
        fielder->_0198 = 0;
        g_Fielders[fielderIndex].IntendedLocation.x = fielder->pos.x;
        g_Fielders[fielderIndex].IntendedLocation.y = fielder->pos.y;
        g_Fielders[fielderIndex].IntendedLocation.z = fielder->pos.z;
        g_Fielders[fielderIndex].velocityX = lbl_3_rodata_B20;
        g_Fielders[fielderIndex].velocityZ = lbl_3_rodata_B20;
        g_Fielders[fielderIndex].currentVelocity = lbl_3_rodata_B20;
        g_Fielders[fielderIndex].distanceFromAutoLocation = lbl_3_rodata_B20;
    }
}

// .text:0x0004197C size:0x3FC mapped:0x80680A10
void fielderAIAssignmentRelated(int mode) {
    InMemFielder* fielder;
    int i;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 bestDist = lbl_3_rodata_BA4;
    int bestFielder;
    u8 code;
    s16 covering;

    for (i = 0; i < 9; i++) {
        fielder = &g_Fielders[i];

        dx = g_Ball.physicsSubstruct.futureCoordsAndDist[90].pos.x - fielder->pos.x;
        dz = g_Ball.physicsSubstruct.futureCoordsAndDist[90].pos.z - fielder->pos.z;
        dist = dolsqrtf2(dx * dx + dz * dz);

        if (mode == 1 && fielder->fielderReadiness != 0 && fielder->always0_ != 1 &&
            fielder->always0_ != 2 && dist < lbl_3_rodata_B78) {
            fielder->autoMovementFunctionIndex = 18;
            if (autoMovementFunctions[18].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[i] = autoMovementFunctions[18].code;
            }
            fielder->unknown_writeOnly = 0;
            fielder->fielderVeloAdjustmentCode = 0;
            fielder->unknown_writeOnly_always0 = 0;
            fielder->timeSinceThrowWasCaught = 0;
            fielder->fielderTrackingBallState = 0;

            setIntendedLocToInterceptBall(i);
            return;
        }

        code = g_FieldingLogic.fielderAutoMovementCode[i];
        if (code == 4) {
            dist -= lbl_3_rodata_B78;
        }

        if (code == 1) {
            if (bestDist > dist - lbl_3_rodata_B64) {
                bestDist = dist;
                bestFielder = i;
            }
        } else {
            if (bestDist > dist) {
                bestFielder = i;
                bestDist = dist;
            }
        }
    }

    fielder = &g_Fielders[bestFielder];
    covering = fielder->locationResponsibleForCovering;
    if (covering != 0 && covering >= 0) {
        if (covering <= 3) {
            if (g_FieldingLogic.fielderAssignedLocationIndex[covering] == bestFielder) {
                g_FieldingLogic.fielderAssignedLocationIndex[covering] = -1;
                g_FieldingLogic.baseCoveredInd[covering] = 0;
            }
            fielder->locationResponsibleForCovering = -1;
            fielder->isResponsibleForCoveringALocation = 0;

            if (fielder->autoMovementFunctionIndex == 1 && bestFielder != -1) {
                fielder->autoMovementFunctionIndex = 12;
                if (autoMovementFunctions[12].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[bestFielder] = autoMovementFunctions[12].code;
                }
                fielder->unknown_writeOnly = 0;
                fielder->fielderVeloAdjustmentCode = 0;
                fielder->unknown_writeOnly_always0 = 0;
                fielder->timeSinceThrowWasCaught = 0;
                fielder->fielderTrackingBallState = 0;
            }
        } else if (covering == 5) {
            fielder->locationResponsibleForCovering = -1;
            g_FieldingLogic.fielderAssignedLocationIndex[4] = -1;
            fielder->isResponsibleForCoveringALocation = 0;
            g_FieldingLogic.playerAtMoundCutoffLocation = 0;

            if (fielder->autoMovementFunctionIndex == 14 && bestFielder != -1) {
                fielder->autoMovementFunctionIndex = 12;
                if (autoMovementFunctions[12].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[bestFielder] = autoMovementFunctions[12].code;
                }
                fielder->unknown_writeOnly = 0;
                fielder->fielderVeloAdjustmentCode = 0;
                fielder->unknown_writeOnly_always0 = 0;
                fielder->timeSinceThrowWasCaught = 0;
                fielder->fielderTrackingBallState = 0;
            }
        }
    }

    if (bestFielder != -1) {
        fielder->autoMovementFunctionIndex = 18;
        if (autoMovementFunctions[18].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[bestFielder] = autoMovementFunctions[18].code;
        }
        fielder->unknown_writeOnly = 0;
        fielder->fielderVeloAdjustmentCode = 0;
        fielder->unknown_writeOnly_always0 = 0;
        fielder->timeSinceThrowWasCaught = 0;
        fielder->fielderTrackingBallState = 0;
    }

    setIntendedLocToInterceptBall(bestFielder);
}

// .text:0x00041D78 size:0x304 mapped:0x80680E0C
void fielderAISomething(void) {
    int i;
    int found = 0;
    u8 code;
    f32 dx;
    f32 dz;
    f32 dxSq;
    f32 dzSq;
    f32 dist;

    if (g_Ball.deadBallReason != 0) {
        return;
    }
    if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FOUL) {
        return;
    }
    if (g_Ball.ballState == BALL_STATE_HELD) {
        return;
    }
    if (g_FieldingLogic.bodyCheckResult2 != 0) {
        return;
    }

    if (g_Ball.ballState == BALL_STATE_THROWN) {
        if (g_Ball.framesUntilThrowReachesDest > 0 && g_Ball.fielderBeingThrownTo >= 0) {
            return;
        }

        dx = g_Ball.throwStartingLocation.x - g_Ball.AtBat_Contact_BallPos.x;
        dz = g_Ball.throwStartingLocation.z - g_Ball.AtBat_Contact_BallPos.z;
        dxSq = dx * dx;
        dzSq = dz * dz;
        dist = fielderSqrt(dxSq + dzSq);

        if (!(dist > lbl_3_rodata_B64 + g_Ball.throwDistance)) {
            return;
        }
    }

    for (i = 0; i < 9; i++) {
        code = g_FieldingLogic.fielderAutoMovementCode[i];
        if (code == 1 || code == 7) {
            found = 1;
            break;
        }
    }

    if (found == 0) {
        fielderAIAssignmentRelated(0);
        return;
    }

    found = 0;
    for (i = 0; i < 9; i++) {
        code = g_Fielders[i].autoMovementFunctionIndex;
        if (code == 2 || (u8)(code - 3) <= 1 || code == 18) {
            found = 1;
            break;
        }
    }

    if (found == 0) {
        fielderAIAssignmentRelated(0);
    }
}

// .text:0x0004207C size:0x7D4 mapped:0x80681110
void decideWhenToLeaveFunction2_16_18(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    InMemFielder* other;
    int i;
    int otherFielderIndex;

    if (g_Ball.deadBallReason != 0) {
        if (fielderIndex == -1) {
            return;
        }
        fielder->autoMovementFunctionIndex = 12;
        if (autoMovementFunctions[12].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[12].code;
        }
        fielder->unknown_writeOnly = 0;
        fielder->fielderVeloAdjustmentCode = 0;
        fielder->unknown_writeOnly_always0 = 0;
        fielder->timeSinceThrowWasCaught = 0;
        fielder->fielderTrackingBallState = 0;
        return;
    }

    if (fielderIndex <= 5) {
        if (g_Ball.ballState == BALL_STATE_LOOSE) {
            if (g_Ball.ballZoneAwayFromHome <= 2) {
                return;
            }
            if (fielderIndex == -1) {
                return;
            }
            fielder->autoMovementFunctionIndex = 11;
            if (autoMovementFunctions[11].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[11].code;
            }
            fielder->unknown_writeOnly = 0;
            fielder->fielderVeloAdjustmentCode = 0;
            fielder->unknown_writeOnly_always0 = 0;
            fielder->timeSinceThrowWasCaught = 0;
            fielder->fielderTrackingBallState = 0;
            return;
        }

        if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_LANDED) {
            if (lbl_3_rodata_B60 + fielder->distanceFromHomePlate < g_Ball.ballDistanceFromHome) {
                if (fielderIndex == 0) {
                    if (fielderIndex == -1) {
                        return;
                    }
                    fielder->autoMovementFunctionIndex = 9;
                    if (autoMovementFunctions[9].code >= 0) {
                        g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[9].code;
                    }
                    fielder->unknown_writeOnly = 0;
                    fielder->fielderVeloAdjustmentCode = 0;
                    fielder->unknown_writeOnly_always0 = 0;
                    fielder->timeSinceThrowWasCaught = 0;
                    fielder->fielderTrackingBallState = 0;
                    return;
                } else if (fielderIndex != 1) {
                    if (g_Ball.ballZoneAwayFromHome > 1) {
                        if (fielderIndex == -1) {
                            return;
                        }
                        fielder->autoMovementFunctionIndex = 11;
                        if (autoMovementFunctions[11].code >= 0) {
                            g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[11].code;
                        }
                        fielder->unknown_writeOnly = 0;
                        fielder->fielderVeloAdjustmentCode = 0;
                        fielder->unknown_writeOnly_always0 = 0;
                        fielder->timeSinceThrowWasCaught = 0;
                        fielder->fielderTrackingBallState = 0;
                        return;
                    }

                    if (fielderIndex != -1) {
                        fielder->autoMovementFunctionIndex = 12;
                        if (autoMovementFunctions[12].code >= 0) {
                            g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[12].code;
                        }
                        fielder->unknown_writeOnly = 0;
                        fielder->fielderVeloAdjustmentCode = 0;
                        fielder->unknown_writeOnly_always0 = 0;
                        fielder->timeSinceThrowWasCaught = 0;
                        fielder->fielderTrackingBallState = 0;
                    }
                    fielder->unknown_writeOnly = 4;
                    return;
                }
            }
        }

        if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > lbl_3_rodata_BD0 &&
            fielder->distanceFromAutoLocation < lbl_3_rodata_BA0 && g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR) {
            for (i = 6; i < 9; i++) {
                other = &g_Fielders[i];
                if (other->nonCatchFlyBallStratInd == 0 && other->numFramesToGetToAutoLocation > 0 &&
                    fielder->numFramesToGetToAutoLocation > other->numFramesToGetToAutoLocation - 20) {
                    if (fielder->isResponsibleForCoveringALocation == 1) {
                        if (fielderIndex != -1) {
                            fielder->autoMovementFunctionIndex = 1;
                            if (autoMovementFunctions[1].code >= 0) {
                                g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[1].code;
                            }
                            fielder->unknown_writeOnly = 0;
                            fielder->fielderVeloAdjustmentCode = 0;
                            fielder->unknown_writeOnly_always0 = 0;
                            fielder->timeSinceThrowWasCaught = 0;
                            fielder->fielderTrackingBallState = 0;
                        }
                        g_FieldingLogic.fielderAssignedLocationIndex[fielder->locationResponsibleForCovering] = fielderIndex;
                        return;
                    } else if (fielder->locationResponsibleForCovering == 6) {
                        if (fielderIndex == -1) {
                            return;
                        }
                        fielder->autoMovementFunctionIndex = 11;
                        if (autoMovementFunctions[11].code >= 0) {
                            g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[11].code;
                        }
                        fielder->unknown_writeOnly = 0;
                        fielder->fielderVeloAdjustmentCode = 0;
                        fielder->unknown_writeOnly_always0 = 0;
                        fielder->timeSinceThrowWasCaught = 0;
                        fielder->fielderTrackingBallState = 0;
                        return;
                    } else {
                        if (fielderIndex != -1) {
                            fielder->autoMovementFunctionIndex = 12;
                            if (autoMovementFunctions[12].code >= 0) {
                                g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[12].code;
                            }
                            fielder->unknown_writeOnly = 0;
                            fielder->fielderVeloAdjustmentCode = 0;
                            fielder->unknown_writeOnly_always0 = 0;
                            fielder->timeSinceThrowWasCaught = 0;
                            fielder->fielderTrackingBallState = 0;
                        }
                        fielder->unknown_writeOnly = 4;
                        return;
                    }
                }
            }
        }

        if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR) {
            for (i = 0; i < 6; i++) {
                if (i == 1) {
                    continue;
                }
                if (lbl_3_rodata_BA0 + fielder->distanceFromHomePlate < g_Ball.ballDistanceFromHome) {
                    if (fielder->isResponsibleForCoveringALocation == 1) {
                        if (fielderIndex != -1) {
                            fielder->autoMovementFunctionIndex = 1;
                            if (autoMovementFunctions[1].code >= 0) {
                                g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[1].code;
                            }
                            fielder->unknown_writeOnly = 0;
                            fielder->fielderVeloAdjustmentCode = 0;
                            fielder->unknown_writeOnly_always0 = 0;
                            fielder->timeSinceThrowWasCaught = 0;
                            fielder->fielderTrackingBallState = 0;
                        }
                        g_FieldingLogic.fielderAssignedLocationIndex[fielder->locationResponsibleForCovering] = fielderIndex;
                        return;
                    } else if (fielder->locationResponsibleForCovering == 6) {
                        if (fielderIndex == -1) {
                            return;
                        }
                        fielder->autoMovementFunctionIndex = 11;
                        if (autoMovementFunctions[11].code >= 0) {
                            g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[11].code;
                        }
                        fielder->unknown_writeOnly = 0;
                        fielder->fielderVeloAdjustmentCode = 0;
                        fielder->unknown_writeOnly_always0 = 0;
                        fielder->timeSinceThrowWasCaught = 0;
                        fielder->fielderTrackingBallState = 0;
                        return;
                    } else {
                        if (fielderIndex != -1) {
                            fielder->autoMovementFunctionIndex = 12;
                            if (autoMovementFunctions[12].code >= 0) {
                                g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[12].code;
                            }
                            fielder->unknown_writeOnly = 0;
                            fielder->fielderVeloAdjustmentCode = 0;
                            fielder->unknown_writeOnly_always0 = 0;
                            fielder->timeSinceThrowWasCaught = 0;
                            fielder->fielderTrackingBallState = 0;
                        }
                        fielder->unknown_writeOnly = 4;
                        return;
                    }
                }
            }
        }
    }

    for (i = 0; i < 9; i++) {
        if (i != fielderIndex && g_FieldingLogic.fielderAutoMovementCode[i] == 1 &&
            fielder->distanceFromEachFielder[i] < lbl_3_rodata_B78) {
            if (fielder->numFramesToGetToAutoLocation < g_Fielders[i].numFramesToGetToAutoLocation) {
                g_Fielders[i].fielderVeloAdjustmentCode = 9;
                fielder->fielderVeloAdjustmentCode = 0;
            } else {
                g_Fielders[i].fielderVeloAdjustmentCode = 0;
                fielder->fielderVeloAdjustmentCode = 9;
            }
        }
    }

    otherFielderIndex = g_Ball.fielderAboutToGetBall_hasBall;
    if (otherFielderIndex == -1) {
        return;
    }
    if (fielderIndex == otherFielderIndex) {
        return;
    }

    if (fielder->isResponsibleForCoveringALocation == 1) {
        if (fielderIndex != -1) {
            fielder->autoMovementFunctionIndex = 1;
            if (autoMovementFunctions[1].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[1].code;
            }
            fielder->unknown_writeOnly = 0;
            fielder->fielderVeloAdjustmentCode = 0;
            fielder->unknown_writeOnly_always0 = 0;
            fielder->timeSinceThrowWasCaught = 0;
            fielder->fielderTrackingBallState = 0;
        }
        g_FieldingLogic.fielderAssignedLocationIndex[fielder->locationResponsibleForCovering] = fielderIndex;
        return;
    } else if (fielder->locationResponsibleForCovering == 6) {
        if (fielderIndex == -1) {
            return;
        }
        fielder->autoMovementFunctionIndex = 11;
        if (autoMovementFunctions[11].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[11].code;
        }
        fielder->unknown_writeOnly = 0;
        fielder->fielderVeloAdjustmentCode = 0;
        fielder->unknown_writeOnly_always0 = 0;
        fielder->timeSinceThrowWasCaught = 0;
        fielder->fielderTrackingBallState = 0;
        return;
    }

    if (fielderIndex < 6 && fielder->distanceFromHomePlate > g_Fielders[otherFielderIndex].distanceFromHomePlate) {
        if (fielder->AI_Ind != 0) {
            if (fielderIndex == -1) {
                return;
            }
            fielder->autoMovementFunctionIndex = 13;
            if (autoMovementFunctions[13].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[13].code;
            }
            fielder->unknown_writeOnly = 0;
            fielder->fielderVeloAdjustmentCode = 0;
            fielder->unknown_writeOnly_always0 = 0;
            fielder->timeSinceThrowWasCaught = 0;
            fielder->fielderTrackingBallState = 0;
            return;
        }

        if (fielderIndex == -1) {
            return;
        }
        fielder->autoMovementFunctionIndex = 16;
        if (autoMovementFunctions[16].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[16].code;
        }
        fielder->unknown_writeOnly = 0;
        fielder->fielderVeloAdjustmentCode = 0;
        fielder->unknown_writeOnly_always0 = 0;
        fielder->timeSinceThrowWasCaught = 0;
        fielder->fielderTrackingBallState = 0;
        return;
    }

    if (fielderIndex == -1) {
        return;
    }
    fielder->autoMovementFunctionIndex = 12;
    if (autoMovementFunctions[12].code >= 0) {
        g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[12].code;
    }
    fielder->unknown_writeOnly = 0;
    fielder->fielderVeloAdjustmentCode = 0;
    fielder->unknown_writeOnly_always0 = 0;
    fielder->timeSinceThrowWasCaught = 0;
    fielder->fielderTrackingBallState = 0;
}

// .text:0x00042850 size:0x1B0 mapped:0x806818E4
void fn_3_42850(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    f32 dx;
    f32 dz;

    fielder->IntendedLocation.x = g_Ball.AtBat_Contact_BallPos.x;
    fielder->IntendedLocation.z = g_Ball.AtBat_Contact_BallPos.z;

    dx = g_Ball.AtBat_Contact_BallPos.x - fielder->pos.x;
    dz = g_Ball.AtBat_Contact_BallPos.z - fielder->pos.z;

    if (lbl_3_rodata_B20 == dx && lbl_3_rodata_B20 == dz) {
        fielder->currentVelocity = lbl_3_rodata_B20;
        fielder->distanceFromAutoLocation = lbl_3_rodata_B20;
    } else {
        fielder->desiredMovementDirection2 = ATAN2F(dz, dx);
        fielder->distanceFromAutoLocation = fielderSqrt(dx * dx + dz * dz);
    }

    fielder->goingToAutoLocationInd = 1;
}

// .text:0x00042A00 size:0x1D0 mapped:0x80681A94
void fn_3_42A00(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    f32 x;
    f32 z;
    f32 dz;
    f32 dx;

    x = g_Ball.physicsSubstruct.futureCoordsAndDist[fielder->framesRemainingToGetToLandingSpot].pos.x;
    z = g_Ball.physicsSubstruct.futureCoordsAndDist[fielder->framesRemainingToGetToLandingSpot].pos.z;

    fielder->IntendedLocation.x = x;
    fielder->IntendedLocation.z = z;
    dx = x - fielder->pos.x;
    dz = z - fielder->pos.z;
    if (lbl_3_rodata_B20 == dx && lbl_3_rodata_B20 == dz) {
        fielder->currentVelocity = lbl_3_rodata_B20;
        fielder->distanceFromAutoLocation = lbl_3_rodata_B20;
    } else {
        fielder->desiredMovementDirection2 = ATAN2F(dz, dx);
        fielder->distanceFromAutoLocation = fielderSqrt(dx * dx + dz * dz);
    }
    fielder->goingToAutoLocationInd = 1;

    if (fielder->framesRemainingToGetToLandingSpot <= 1) {
        fielder->maybeMovementState = 5;
    }
}

// .text:0x00042BD0 size:0x10C mapped:0x80681C64
void fn_3_42BD0(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    int n;

    if (fielderIndex < 6) {
        return;
    }
    if (g_Ball.ballState != BALL_STATE_HIT) {
        return;
    }

    if (fielder->distanceFromHomePlate < g_Ball.ballDistanceFromHome) {
        setIntendedLocToInterceptBall(fielderIndex);
        return;
    }

    for (n = 6; n < 9; n++) {
        if (n != fielderIndex) {
            if (g_Fielders[n].maybeMovementState == 3 && g_Fielders[n].numFramesToGetToAutoLocation <= fielder->numFramesToGetToAutoLocation &&
                g_Fielders[n].numFramesToGetToAutoLocation < 0x5a) {
                setIntendedLocToInterceptBall(fielderIndex);
                return;
            }
        }
    }
}

// .text:0x00042CDC size:0x35C mapped:0x80681D70
void updateFielderPosition(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    f32 outX;
    f32 outZ;
    f32 dx;
    f32 dz;
    f32 x5m;
    f32 z5m;

    fielder->xPos5mAwayFromBallsCollisionSpotOnWall = lbl_3_rodata_B64 * g_Ball._19E4 + g_Ball.ballWillHitBallPos.x;
    fielder->zPos5mAwayFromBallsCollisionSpotOnWall = lbl_3_rodata_B64 * g_Ball._19E8 + g_Ball.ballWillHitBallPos.z;

    if (fielder->aiDistToStandFromWallCollision != 0) {
        fn_3_50DD8(fielderIndex, &outX, &outZ, 1);
        fielder->IntendedLocation.x = outX;
        fielder->IntendedLocation.z = outZ;

        dx = outX - fielder->pos.x;
        dz = outZ - fielder->pos.z;

        if (lbl_3_rodata_B20 == dx && lbl_3_rodata_B20 == dz) {
            fielder->currentVelocity = lbl_3_rodata_B20;
            fielder->distanceFromAutoLocation = lbl_3_rodata_B20;
        } else {
            fielder->desiredMovementDirection2 = ATAN2F(dz, dx);
            fielder->distanceFromAutoLocation = fielderSqrt(dx * dx + dz * dz);
        }

        fielder->goingToAutoLocationInd = 1;
        fielder->maybeTargetPosX = outX;
        fielder->maybeTargetPosZ = outZ;
    } else {
        x5m = fielder->xPos5mAwayFromBallsCollisionSpotOnWall;
        z5m = fielder->zPos5mAwayFromBallsCollisionSpotOnWall;

        fielder->IntendedLocation.x = x5m;
        fielder->IntendedLocation.z = z5m;

        dx = x5m - fielder->pos.x;
        dz = z5m - fielder->pos.z;

        if (lbl_3_rodata_B20 == dx && lbl_3_rodata_B20 == dz) {
            fielder->currentVelocity = lbl_3_rodata_B20;
            fielder->distanceFromAutoLocation = lbl_3_rodata_B20;
        } else {
            fielder->desiredMovementDirection2 = ATAN2F(dz, dx);
            fielder->distanceFromAutoLocation = fielderSqrt(dx * dx + dz * dz);
        }

        fielder->goingToAutoLocationInd = 1;
    }
}

extern const f32 lbl_3_rodata_C08;
extern const f32 lbl_3_rodata_B60;

// .text:0x00043038 size:0x3A8 mapped:0x806820CC
void setIntendedLocToInterceptBall(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    int frame;
    CoordAndDist* futureCoord;
    f32 dx, dz, speed;
    int total = 0;

    fielder->maybeMovementState = 4;

    frame = 5;
    for (;;) {
        if (frame > 120) {
            fielder->framesRemainingToGetToLandingSpot = 120;
            break;
        }

        futureCoord = &g_Ball.physicsSubstruct.futureCoordsAndDist[frame];

        if (futureCoord->pos.y > lbl_3_rodata_C08) {
            frame += 1;
            continue;
        }

        if (futureCoord->pos.x == fielder->pos.x && futureCoord->pos.z == fielder->pos.z) {
            total = 1;
        } else {
            dx = futureCoord->pos.x - fielder->pos.x;
            dz = futureCoord->pos.z - fielder->pos.z;

            speed = fielder->joggingSpeed;
            if (speed == lbl_3_rodata_B20) {
                speed = lbl_3_rodata_B60;
            }

            total = (fielder->maxAccLength_ConstF >> 1) + (int)(fielderSqrt(dx * dx + dz * dz) / speed);
        }

        if (total < frame) {
            fielder->framesRemainingToGetToLandingSpot = frame;
            break;
        }

        frame += 5;
    }

    futureCoord = &g_Ball.physicsSubstruct.futureCoordsAndDist[fielder->framesRemainingToGetToLandingSpot];
    fielder->IntendedLocation.x = futureCoord->pos.x;
    fielder->IntendedLocation.z = futureCoord->pos.z;

    dx = fielder->IntendedLocation.x - fielder->pos.x;
    dz = fielder->IntendedLocation.z - fielder->pos.z;

    if (dx == lbl_3_rodata_B20 && dz == lbl_3_rodata_B20) {
        fielder->currentVelocity = lbl_3_rodata_B20;
        fielder->distanceFromAutoLocation = lbl_3_rodata_B20;
    } else {
        fielder->desiredMovementDirection2 = ATAN2F(dz, dx);
        fielder->distanceFromAutoLocation = fielderSqrt(dx * dx + dz * dz);
    }

    fielder->goingToAutoLocationInd = 1;

    if (fielder->framesRemainingToGetToLandingSpot >= 120) {
        fielder->numFramesToGetToAutoLocation = 120;
    } else {
        fielder->numFramesToGetToAutoLocation = total;
    }
}

// .text:0x000433E0 size:0x13E4 mapped:0x80682474
void fielderTrackingBall_updateVariables(void) {
    return;
}

// .text:0x000447C4 size:0xBD0 mapped:0x80683858
void fielderTrackingBall_initialVariableSetting(void) {
    return;
}

// .text:0x00045394 size:0x220 mapped:0x80684428
void autoMovement2_18_goTowardsBall_phase2(int fielderIndex) {
    return;
}

// .text:0x000455B4 size:0x2AC mapped:0x80684648
void autoMovement4_AI_goTowardsHitBall(int fielderIndex) {
    return;
}

// .text:0x00045860 size:0x11C mapped:0x806848F4
void autoMovement3_goTowardsHitBall_AITeam(int fielderIndex) {
    return;
}

// .text:0x0004597C size:0x20C mapped:0x80684A10
void fn_3_4597C(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    VecXZ out;
    VecXZ a[2];
    VecXZ b[2];
    f32 vz;
    f32 vx;
    f32 negVz;
    f32 x;
    f32 z;
    f32 dz;
    f32 dx;

    vz = g_Ball.throwTarget.z - g_Ball.AtBat_Contact_BallPos.z;
    vx = g_Ball.throwTarget.x - g_Ball.AtBat_Contact_BallPos.x;

    a[0].x = g_Ball.AtBat_Contact_BallPos.x;
    a[0].z = g_Ball.AtBat_Contact_BallPos.z;
    a[1].x = g_Ball.throwTarget.x;
    a[1].z = g_Ball.throwTarget.z;

    b[0].x = fielder->pos.x;
    b[0].z = fielder->pos.z;
    negVz = -vz;
    b[1].x = fielder->pos.x + negVz;
    b[1].z = fielder->pos.z + vx;

    calculateLineIntersection(&out, a, b);

    x = out.x;
    z = out.z;

    fielder->IntendedLocation.x = x;
    fielder->IntendedLocation.z = z;

    dz = z - fielder->pos.z;
    dx = x - fielder->pos.x;

    if (lbl_3_rodata_B20 == dx && lbl_3_rodata_B20 == dz) {
        fielder->currentVelocity = lbl_3_rodata_B20;
        fielder->distanceFromAutoLocation = lbl_3_rodata_B20;
    } else {
        fielder->desiredMovementDirection2 = ATAN2F(dz, dx);
        fielder->distanceFromAutoLocation = fielderSqrt(dx * dx + dz * dz);
    }

    fielder->goingToAutoLocationInd = 1;
}

// .text:0x00045B88 size:0x310 mapped:0x80684C1C
void autoMovement25_readyToInterceptThrownBall(int fielderIndex) {
    return;
}

// .text:0x00045E98 size:0x7F0 mapped:0x80684F2C
void updateFielderValuesSubFunction1_cuttoffRelated(void) {
    s16 cutoffFielderIndex;
    int flag;
    int pos;
    int count;
    int candidates[3];
    int bestCandidate;
    f32 bestDist;
    int j;

    if (g_FieldingLogic.someFrameCounterFielderRelated != 0) {
        g_FieldingLogic.someFrameCounterFielderRelated--;
    }
    flag = 0;

    if (g_FieldingLogic.locationThrownTo == 6) {
        return;
    }

    if (g_Ball.fielderWBallIndex == g_FieldingLogic.cutoffFielderIndex) {
        g_FieldingLogic.cutoffFielderIndex = -1;
    }

    cutoffFielderIndex = g_FieldingLogic.cutoffFielderIndex;
    if (cutoffFielderIndex == -1) {
        if (g_FieldingLogic.locationThrownTo >= 0) {
            return;
        }

        for (pos = 0; pos < 6; pos++) {
            if (g_Fielders[pos].locationResponsibleForCovering == 6) {
                u8 idx = g_Fielders[pos].autoMovementFunctionIndex;
                if (idx == 2 || (u8)(idx - 0xf) <= 1 || (u8)(idx - 0x15) <= 2 || idx == 0xc || idx == 0) {
                    g_Fielders[pos].locationResponsibleForCovering = -1;
                } else {
                    return;
                }
            }
        }

        if (g_Ball.ballZoneAwayFromHome >= 3) {
            flag = 1;
        } else {
            if (g_Ball.ballZoneAwayFromHome <= 1) {
                return;
            }
            if (g_Ball.fielderWBallIndex >= 0) {
                return;
            }
            if (g_Ball.ballState == BALL_STATE_HIT && g_Ball.ballZoneAwayFromHome >= 2) {
                flag = 1;
            }
        }

        for (pos = 0; pos < 6; pos++) {
            u8 c = g_FieldingLogic.fielderAutoMovementCode[pos];
            if (c == 1 || c == 0xa) {
                break;
            }
        }
        if (pos == 6) {
            for (pos = 6; pos < 9; pos++) {
                u8 c = g_FieldingLogic.fielderAutoMovementCode[pos];
                if (c == 1 || c == 0xa) {
                    break;
                }
            }
            if (pos <= 8) {
                flag = 1;
            }
        }

        if (flag == 0) {
            return;
        }
        if (g_FieldingLogic.someFrameCounterFielderRelated != 0) {
            return;
        }

        count = 0;
        candidates[0] = -1;
        candidates[1] = -1;
        candidates[2] = -1;
        for (pos = 2; pos < 6 && count < 3; pos++) {
            u8 code = g_FieldingLogic.fielderAutoMovementCode[pos];
            if ((code == 0 || code == 8 || code == 9) && g_Fielders[pos].animatingActionInd == 0) {
                candidates[count++] = pos;
            }
        }
        if (count == 0) {
            return;
        }

        {
            f32 projX = lbl_3_rodata_BD0 * g_Ball.AtBat_Contact_BallPos.x / g_Ball.ballDistanceFromHome;
            f32 projZ = lbl_3_rodata_BD0 * g_Ball.AtBat_Contact_BallPos.z / g_Ball.ballDistanceFromHome;

            bestCandidate = candidates[0];
            for (j = 0; j < 3; j++) {
                int cand = candidates[j];
                InMemFielder* cf;
                f32 dx, dz, sqx, sqz, dist;

                if (cand < 0) {
                    continue;
                }
                cf = &g_Fielders[cand];
                dx = cf->pos.x - projX;
                dz = cf->pos.z - projZ;
                sqx = dx * dx;
                sqz = dz * dz;
                dist = fielderSqrt(sqx + sqz);
                if (j == 0) {
                    bestDist = dist;
                } else if (dist < bestDist) {
                    bestDist = dist;
                    bestCandidate = cand;
                }
            }
        }

        if (bestCandidate != -1) {
            InMemFielder* bf = &g_Fielders[bestCandidate];
            bf->autoMovementFunctionIndex = 11;
            if (autoMovementFunctions[11].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[bestCandidate] = autoMovementFunctions[11].code;
            }
            bf->unknown_writeOnly = 0;
            bf->fielderVeloAdjustmentCode = 0;
            bf->unknown_writeOnly_always0 = 0;
            bf->timeSinceThrowWasCaught = 0;
            bf->fielderTrackingBallState = 0;
        }

        g_FieldingLogic.FrameCycleCounter_20 = specialFielderActionConstants._40[11];
    } else {
        InMemFielder* cutoff;
        f32 targetX;
        f32 targetZ;

        if (g_FieldingLogic.FrameCycleCounter_20 != 0) {
            return;
        }

        cutoff = &g_Fielders[cutoffFielderIndex];
        targetX = cutoff->IntendedLocation.x;
        targetZ = cutoff->IntendedLocation.z;
        for (pos = 2; pos < 6; pos++) {
            u8 code;
            InMemFielder* cand;
            f32 dx, dz, sqx, sqz, dist;

            if (pos == cutoffFielderIndex) {
                continue;
            }
            code = g_FieldingLogic.fielderAutoMovementCode[pos];
            if (code != 0 && code != 8 && code != 9) {
                continue;
            }
            cand = &g_Fielders[pos];
            if (cand->animatingActionInd != 0) {
                continue;
            }
            dx = targetX - cand->pos.x;
            dz = targetZ - cand->pos.z;
            sqx = dx * dx;
            sqz = dz * dz;
            dist = fielderSqrt(sqx + sqz);
            if (dist >= cutoff->distanceFromAutoLocation) {
                continue;
            }

            cand->autoMovementFunctionIndex = 11;
            if (autoMovementFunctions[11].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[pos] = autoMovementFunctions[11].code;
            }
            cand->unknown_writeOnly = 0;
            cand->fielderVeloAdjustmentCode = 0;
            cand->unknown_writeOnly_always0 = 0;
            cand->timeSinceThrowWasCaught = 0;
            cand->fielderTrackingBallState = 0;

            g_FieldingLogic.FrameCycleCounter_20 = specialFielderActionConstants._40[11];
            return;
        }
    }
}

// .text:0x00046688 size:0x254 mapped:0x8068571C
s32 fn_3_46688(f32* outX, f32* outZ) {
    InMemFielder* fielder = &g_Fielders[g_FieldingLogic.selectedFielder];
    f32 dx, dz;
    f32 magnitude;
    f32 sqx, sqz;

    if (g_Ball.fielderWBallIndex >= 0) {
        *outX = g_Ball.AtBat_Contact_BallPos.x;
        *outZ = g_Ball.AtBat_Contact_BallPos.z;
    } else if (g_Ball.ballState == BALL_STATE_THROWN) {
        *outX = g_Ball.throwStartingLocation.x;
        *outZ = g_Ball.deadballLastLoc.x;
    } else if (g_Ball.fielderAboutToGetBall_hasBall >= 0) {
        *outX = g_Fielders[g_Ball.fielderAboutToGetBall_hasBall].pos.x;
        *outZ = g_Fielders[g_Ball.fielderAboutToGetBall_hasBall].pos.z;
    } else if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR) {
        *outX = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
        *outZ = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
    } else {
        dx = g_Ball.AtBat_Contact_BallPos.x - fielder->pos.x;
        dz = g_Ball.AtBat_Contact_BallPos.z - fielder->pos.z;
        sqx = dx * dx;
        sqz = dz * dz;
        magnitude = fielderSqrt(sqx + sqz);

        if (lbl_3_rodata_B20 == magnitude) {
            *outX = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
            *outZ = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
        } else if (g_Ball.ballVelocity <= lbl_3_rodata_B48) {
            *outX = g_Ball.AtBat_Contact_BallPos.x;
            *outZ = g_Ball.AtBat_Contact_BallPos.z;
        } else {
            f32 t = magnitude / g_Ball.ballVelocity;
            *outX = g_Ball.physicsSubstruct.velocity.x * t + g_Ball.AtBat_Contact_BallPos.x;
            *outZ = g_Ball.physicsSubstruct.velocity.z * t + g_Ball.AtBat_Contact_BallPos.z;
        }
    }

    return 1;
}

// .text:0x000468DC size:0x1E0 mapped:0x80685970
s32 fn_3_468DC(f32* outX, f32* outZ) {
    if (g_Ball.fielderWBallIndex >= 0) {
        *outX = g_Ball.AtBat_Contact_BallPos.x;
        *outZ = g_Ball.AtBat_Contact_BallPos.z;
        goto exit_success;
    }
    if (g_Ball.fielderAboutToGetBall_hasBall >= 0) {
        *outX = g_Fielders[g_Ball.fielderAboutToGetBall_hasBall].IntendedLocation.x;
        *outZ = g_Fielders[g_Ball.fielderAboutToGetBall_hasBall].IntendedLocation.z;
        goto exit_success;
    }
    if (g_FieldingLogic.fielderAutoMovementCode[7] == 1) {
        if (g_FieldingLogic.fielderAutoMovementCode[8] == 1) {
            if (g_Fielders[7].numFramesToGetToAutoLocation == -1 || g_Fielders[8].numFramesToGetToAutoLocation == -1) return 0;
            if (g_Fielders[7].numFramesToGetToAutoLocation < g_Fielders[8].numFramesToGetToAutoLocation) {
                *outX = g_Fielders[7].IntendedLocation.x;
                *outZ = g_Fielders[7].IntendedLocation.z;
            } else {
                *outX = g_Fielders[8].IntendedLocation.x;
                *outZ = g_Fielders[8].IntendedLocation.z;
            }
        } else if (g_FieldingLogic.fielderAutoMovementCode[6] == 1) {
            if (g_Fielders[7].numFramesToGetToAutoLocation == -1 || g_Fielders[6].numFramesToGetToAutoLocation == -1) return 0;
            if (g_Fielders[7].numFramesToGetToAutoLocation < g_Fielders[6].numFramesToGetToAutoLocation) {
                *outX = g_Fielders[7].IntendedLocation.x;
                *outZ = g_Fielders[7].IntendedLocation.z;
            } else {
                *outX = g_Fielders[6].IntendedLocation.x;
                *outZ = g_Fielders[6].IntendedLocation.z;
            }
        } else {
            if (g_Fielders[7].numFramesToGetToAutoLocation == -1) return 0;
            *outX = g_Fielders[7].IntendedLocation.x;
            *outZ = g_Fielders[7].IntendedLocation.z;
        }
    } else if (g_FieldingLogic.fielderAutoMovementCode[8] == 1) {
        if (g_Fielders[8].numFramesToGetToAutoLocation == -1) return 0;
        *outX = g_Fielders[8].IntendedLocation.x;
        *outZ = g_Fielders[8].IntendedLocation.z;
    } else {
        if (g_Fielders[6].numFramesToGetToAutoLocation == -1) return 0;
        *outX = g_Fielders[6].IntendedLocation.x;
        *outZ = g_Fielders[6].IntendedLocation.z;
    }
exit_success:
    return 1;
}

// .text:0x00046ABC size:0x34C mapped:0x80685B50
void checkIfCutoffIsntAtThrowDestination(void) {
    return;
}

extern const f32 lbl_3_rodata_C3C;
extern const f32 lbl_3_rodata_C40;
extern const f32 lbl_3_rodata_C44;
extern const f32 lbl_3_rodata_C4C;

// .text:0x00046E08 size:0x820 mapped:0x80685E9C
int setCutoffLocationToStandAt(int fielderIndex, f32* outX, f32* outZ) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    int found = 0;
    f32 x;
    f32 z;
    f32 dist;
    s16 idx;
    VecXZ* base;
    f32 baseX;
    f32 baseZ;
    int i;

    if (fielder->AI_Ind != 0) {
        if (!fn_3_468DC(&x, &z)) {
            return 0;
        }
    } else {
        InMemFielder* other = &g_Fielders[g_FieldingLogic.selectedFielder];

        if (g_Ball.fielderWBallIndex >= 0) {
            x = g_Ball.AtBat_Contact_BallPos.x;
            z = g_Ball.AtBat_Contact_BallPos.z;
        } else if (g_Ball.ballState == BALL_STATE_THROWN) {
            x = g_Ball.throwStartingLocation.x;
            z = g_Ball.deadballLastLoc.x;
        } else if (g_Ball.fielderAboutToGetBall_hasBall >= 0) {
            int otherIdx = g_Ball.fielderAboutToGetBall_hasBall;
            x = g_Fielders[otherIdx].pos.x;
            z = g_Fielders[otherIdx].pos.z;
        } else if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR) {
            x = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
            z = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
        } else {
            f32 deltaX = g_Ball.AtBat_Contact_BallPos.x - other->pos.x;
            f32 deltaZ = g_Ball.AtBat_Contact_BallPos.z - other->pos.z;
            f32 sqX = deltaX * deltaX;
            f32 sqZ = deltaZ * deltaZ;

            dist = fielderSqrt(sqX + sqZ);
            if (dist == lbl_3_rodata_B20) {
                x = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
                z = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
            } else if (g_Ball.ballVelocity <= lbl_3_rodata_B48) {
                x = g_Ball.AtBat_Contact_BallPos.x;
                z = g_Ball.AtBat_Contact_BallPos.z;
            } else {
                f32 time = dist / g_Ball.ballVelocity;
                x = g_Ball.AtBat_Contact_BallPos.x + g_Ball.physicsSubstruct.velocity.x * time;
                z = g_Ball.AtBat_Contact_BallPos.z + g_Ball.physicsSubstruct.velocity.z * time;
            }
        }
    }

    idx = fielder->baseCuttoffIsTargeting;
    base = &base_MoundCoordinates[idx];
    baseX = base->x;
    baseZ = base->z;

    switch (idx) {
    case 0: {
        f32 mag;

        *outX = lbl_3_rodata_B8C * (x / lbl_3_rodata_C3C);
        *outZ = lbl_3_rodata_B8C * (z / lbl_3_rodata_C3C);

        mag = fielderSqrt((*outX) * (*outX) + (*outZ) * (*outZ));
        if (mag > lbl_3_rodata_C40) {
            f32 ratio = mag / lbl_3_rodata_C40;
            if (ratio > lbl_3_rodata_B60) {
                *outX /= ratio;
                *outZ /= ratio;
            }
        }
        break;
    }
    case 1:
        *outX = (x - baseX) * lbl_3_rodata_B80 + baseX;
        *outZ = (z - baseZ) * lbl_3_rodata_B80 + baseZ;
        break;
    case 2:
        *outX = (x - baseX) * lbl_3_rodata_B74 + baseX;
        *outZ = (z - baseZ) * lbl_3_rodata_B74 + baseZ;
        break;
    case 3:
        if (fielder->playerAngleFromHome < 0x480) {
            *outX = lbl_3_rodata_B80 * (x - baseX) + baseX;
            *outZ = lbl_3_rodata_B80 * (z - baseZ) + baseZ;
        } else {
            *outX = baseX + (x - baseX) / lbl_3_rodata_B78;
            *outZ = baseZ + (z - baseZ) / lbl_3_rodata_B78;
        }
        break;
    case 4:
        *outX = baseX + (x - baseX) / lbl_3_rodata_C08;
        *outZ = baseZ + (z - baseZ) / lbl_3_rodata_C08;
        break;
    default:
        break;
    }

    {
        VecXZ* b = &base_MoundCoordinates[1];

        i = 3;
        do {
            if (*outZ > b->z - lbl_3_rodata_B64 && *outZ < b->z + lbl_3_rodata_B64 &&
                *outX > b->x - lbl_3_rodata_B64 && *outX < b->x + lbl_3_rodata_B64) {
                found = 1;
            }
            b++;
        } while (--i);
    }

    if (found) {
        switch (fielder->baseCuttoffIsTargeting) {
        case 0:
            *outX = x / lbl_3_rodata_C44;
            *outZ = z / lbl_3_rodata_C44;
            break;
        case 1:
            *outX = baseX + (x - baseX) / lbl_3_rodata_C48;
            *outZ = baseZ + (z - baseZ) / lbl_3_rodata_C48;
            break;
        case 2:
            *outX = baseX + (x - baseX) / lbl_3_rodata_C4C;
            *outZ = baseZ + (z - baseZ) / lbl_3_rodata_C4C;
            break;
        case 3:
            *outX = baseX + (x - baseX) / lbl_3_rodata_C48;
            *outZ = baseZ + (z - baseZ) / lbl_3_rodata_C48;
            break;
        case 4:
            *outX = baseX + (x - baseX) * lbl_3_rodata_B80;
            *outZ = baseZ + (z - baseZ) * lbl_3_rodata_B80;
            break;
        default:
            break;
        }
        return 1;
    } else {
        f32 deltaX = *outX - fielder->IntendedLocation.x;
        f32 deltaZ = *outZ - fielder->IntendedLocation.z;
        f32 sqX = deltaX * deltaX;
        f32 sqZ = deltaZ * deltaZ;

        dist = fielderSqrt(sqX + sqZ);
        if (dist < lbl_3_rodata_B64) {
            *outX = fielder->IntendedLocation.x;
            *outZ = fielder->IntendedLocation.z;
        }
        return 1;
    }
}

// .text:0x00047628 size:0x150 mapped:0x806866BC
int fn_3_47628(void) {
    int i;
    InMemRunnerType* runner = &g_Runners[3];

    for (i = 3; i >= 0; runner--, i--) {
        if (runner->runnerOnFieldOrOutOrScored != RUNNER_STATUS_ON_FIELD) {
            continue;
        }
        if (lbl_3_rodata_C50 <= runner->fractionalBasesRan &&
            runner->runningDirectionCode == 1 &&
            runner->tagUpInd != TAG_UP_TYPE_TAGGED) {
            continue;
        }
        {
            InMemRunnerType* r = &g_Runners[i];
            f32 fractionalBasesRan = r->fractionalBasesRan;

            if (fractionalBasesRan >= lbl_3_rodata_B78) {
                return 0;
            }
            if (r->tagUpInd == TAG_UP_TYPE_TAGGED && r->percentTowardsNextBase >= lbl_3_rodata_C38) {
                return r->startingBase_baseAchieved;
            }
            if (fractionalBasesRan >= lbl_3_rodata_B68) {
                if (fractionalBasesRan >= lbl_3_rodata_C54) {
                    if (g_Runners[i].runningDirectionCode == 1) {
                        return 0;
                    }
                }
                return 3;
            } else {
                if (fractionalBasesRan >= lbl_3_rodata_C48) {
                    if (g_Runners[i].runningDirectionCode == 1) {
                        return 3;
                    }
                }
                return 2;
            }
        }
    }
    return 4;
}

// .text:0x00047778 size:0x940 mapped:0x8068680C
void setInitialFielderMovements_cutoffs(void) {
    u8 movementCode3;
    u8 movementCode5;

    if (g_Ball.hitClassification2 == 5 || g_Ball.hitClassification2 == 6 || g_Ball.hitClassification2 == 8) {
        movementCode3 = g_FieldingLogic.fielderAutoMovementCode[3];
        if (movementCode3 == 1 || movementCode3 == 10 || movementCode3 == 11) {
            if (g_Fielders[5].locationResponsibleForCovering != -1) {
                g_Fielders[3].locationResponsibleForCovering = 6;
                g_Fielders[3].isResponsibleForCoveringALocation = 2;
            } else {
                g_Fielders[5].locationResponsibleForCovering = 6;
                g_Fielders[5].isResponsibleForCoveringALocation = 2;
                if (g_FieldingLogic.fielderAutoMovementCode[5] == 0) {
                    g_Fielders[5].autoMovementFunctionIndex = 11;
                    if (autoMovementFunctions[11].code >= 0) {
                        g_FieldingLogic.fielderAutoMovementCode[5] = autoMovementFunctions[11].code;
                    }
                    g_Fielders[5].unknown_writeOnly = 0;
                    g_Fielders[5].fielderVeloAdjustmentCode = 0;
                    g_Fielders[5].unknown_writeOnly_always0 = 0;
                    g_Fielders[5].timeSinceThrowWasCaught = 0;
                    g_Fielders[5].fielderTrackingBallState = 0;
                }
            }
        } else {
            movementCode5 = g_FieldingLogic.fielderAutoMovementCode[5];
            if (movementCode5 == 1 || movementCode5 == 10 || movementCode5 == 11) {
                if (g_Fielders[3].locationResponsibleForCovering != -1) {
                    g_Fielders[5].locationResponsibleForCovering = 6;
                    g_Fielders[5].isResponsibleForCoveringALocation = 2;
                } else {
                    g_Fielders[3].locationResponsibleForCovering = 6;
                    g_Fielders[3].isResponsibleForCoveringALocation = 2;
                    if (movementCode3 == 0) {
                        g_Fielders[3].autoMovementFunctionIndex = 11;
                        if (autoMovementFunctions[11].code >= 0) {
                            g_FieldingLogic.fielderAutoMovementCode[3] = autoMovementFunctions[11].code;
                        }
                        g_Fielders[3].unknown_writeOnly = 0;
                        g_Fielders[3].fielderVeloAdjustmentCode = 0;
                        g_Fielders[3].unknown_writeOnly_always0 = 0;
                        g_Fielders[3].timeSinceThrowWasCaught = 0;
                        g_Fielders[3].fielderTrackingBallState = 0;
                    }
                }
            } else if (g_Ball.Hit_HorizontalAngle < 0x400) {
                u8 movementCode2;
                if (g_Fielders[3].locationResponsibleForCovering == 1 &&
                    ((movementCode2 = g_FieldingLogic.fielderAutoMovementCode[2]) == 1 || movementCode2 == 10 ||
                     movementCode2 == 11)) {
                    g_Fielders[2].locationResponsibleForCovering = 6;
                    g_Fielders[2].isResponsibleForCoveringALocation = 2;
                } else if (movementCode3 != 0) {
                    g_Fielders[3].locationResponsibleForCovering = 6;
                    g_Fielders[3].isResponsibleForCoveringALocation = 2;
                } else {
                    g_Fielders[3].locationResponsibleForCovering = 6;
                    g_Fielders[3].isResponsibleForCoveringALocation = 2;
                    g_Fielders[3].autoMovementFunctionIndex = 11;
                    if (autoMovementFunctions[11].code >= 0) {
                        g_FieldingLogic.fielderAutoMovementCode[3] = autoMovementFunctions[11].code;
                    }
                    g_Fielders[3].unknown_writeOnly = 0;
                    g_Fielders[3].fielderVeloAdjustmentCode = 0;
                    g_Fielders[3].unknown_writeOnly_always0 = 0;
                    g_Fielders[3].timeSinceThrowWasCaught = 0;
                    g_Fielders[3].fielderTrackingBallState = 0;
                }
            } else {
                u8 movementCode4;
                if (g_Fielders[5].locationResponsibleForCovering == 3 &&
                    ((movementCode4 = g_FieldingLogic.fielderAutoMovementCode[4]) == 1 || movementCode4 == 10 ||
                     movementCode4 == 11)) {
                    g_Fielders[4].locationResponsibleForCovering = 6;
                    g_Fielders[4].isResponsibleForCoveringALocation = 2;
                } else if (movementCode5 != 0) {
                    g_Fielders[5].locationResponsibleForCovering = 6;
                    g_Fielders[5].isResponsibleForCoveringALocation = 2;
                } else {
                    g_Fielders[5].locationResponsibleForCovering = 6;
                    g_Fielders[5].isResponsibleForCoveringALocation = 2;
                    g_Fielders[5].autoMovementFunctionIndex = 11;
                    if (autoMovementFunctions[11].code >= 0) {
                        g_FieldingLogic.fielderAutoMovementCode[5] = autoMovementFunctions[11].code;
                    }
                    g_Fielders[5].unknown_writeOnly = 0;
                    g_Fielders[5].fielderVeloAdjustmentCode = 0;
                    g_Fielders[5].unknown_writeOnly_always0 = 0;
                    g_Fielders[5].timeSinceThrowWasCaught = 0;
                    g_Fielders[5].fielderTrackingBallState = 0;
                }
            }
        }
    }

    if (g_FieldingLogic.fielderAutoMovementCode[0] == 0) {
        InMemFielder* fielder = &g_Fielders[0];
        f32 intendedX;
        f32 intendedZ;
        f32 deltaX;
        f32 deltaZ;

        if (g_Ball.Hit_HorizontalAngle < 0x320) {
            intendedX = lbl_3_rodata_BF4;
            intendedZ = lbl_3_rodata_C28;
            fielder->IntendedLocation.x = intendedX;
            fielder->IntendedLocation.z = intendedZ;
            deltaX = intendedX - fielder->pos.x;
            deltaZ = intendedZ - fielder->pos.z;
            if (deltaX == lbl_3_rodata_B20 && deltaZ == lbl_3_rodata_B20) {
                fielder->currentVelocity = lbl_3_rodata_B20;
                fielder->distanceFromAutoLocation = lbl_3_rodata_B20;
            } else {
                fielder->desiredMovementDirection2 = (f32) atan2(deltaZ, deltaX);
                fielder->distanceFromAutoLocation = fielderSqrt(deltaZ * deltaZ + deltaX * deltaX);
            }
            fielder->goingToAutoLocationInd = 1;
        } else if (g_Ball.Hit_HorizontalAngle < 0x400) {
            intendedX = lbl_3_rodata_B78;
            intendedZ = lbl_3_rodata_C58;
            fielder->IntendedLocation.x = intendedX;
            fielder->IntendedLocation.z = intendedZ;
            deltaX = intendedX - fielder->pos.x;
            deltaZ = intendedZ - fielder->pos.z;
            if (deltaX == lbl_3_rodata_B20 && deltaZ == lbl_3_rodata_B20) {
                fielder->currentVelocity = lbl_3_rodata_B20;
                fielder->distanceFromAutoLocation = lbl_3_rodata_B20;
            } else {
                fielder->desiredMovementDirection2 = (f32) atan2(deltaZ, deltaX);
                fielder->distanceFromAutoLocation = fielderSqrt(deltaZ * deltaZ + deltaX * deltaX);
            }
            fielder->goingToAutoLocationInd = 1;
        } else if (g_Ball.Hit_HorizontalAngle < 0x4e0) {
            intendedX = lbl_3_rodata_C5C;
            intendedZ = lbl_3_rodata_C58;
            fielder->IntendedLocation.x = intendedX;
            fielder->IntendedLocation.z = intendedZ;
            deltaX = intendedX - fielder->pos.x;
            deltaZ = intendedZ - fielder->pos.z;
            if (deltaX == lbl_3_rodata_B20 && deltaZ == lbl_3_rodata_B20) {
                fielder->currentVelocity = lbl_3_rodata_B20;
                fielder->distanceFromAutoLocation = lbl_3_rodata_B20;
            } else {
                fielder->desiredMovementDirection2 = (f32) atan2(deltaZ, deltaX);
                fielder->distanceFromAutoLocation = fielderSqrt(deltaZ * deltaZ + deltaX * deltaX);
            }
            fielder->goingToAutoLocationInd = 1;
        } else {
            intendedX = lbl_3_rodata_C60;
            intendedZ = lbl_3_rodata_C28;
            fielder->IntendedLocation.x = intendedX;
            fielder->IntendedLocation.z = intendedZ;
            deltaX = intendedX - fielder->pos.x;
            deltaZ = intendedZ - fielder->pos.z;
            if (deltaX == lbl_3_rodata_B20 && deltaZ == lbl_3_rodata_B20) {
                fielder->currentVelocity = lbl_3_rodata_B20;
                fielder->distanceFromAutoLocation = lbl_3_rodata_B20;
            } else {
                fielder->desiredMovementDirection2 = (f32) atan2(deltaZ, deltaX);
                fielder->distanceFromAutoLocation = fielderSqrt(deltaZ * deltaZ + deltaX * deltaX);
            }
            fielder->goingToAutoLocationInd = 1;
        }

        fielder->autoMovementFunctionIndex = 14;
        if (autoMovementFunctions[14].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[0] = autoMovementFunctions[14].code;
        }
        fielder->unknown_writeOnly = 0;
        fielder->fielderVeloAdjustmentCode = 0;
        fielder->unknown_writeOnly_always0 = 0;
        fielder->timeSinceThrowWasCaught = 0;
        fielder->fielderTrackingBallState = 0;
    }
}

// .text:0x000480B8 size:0x314 mapped:0x8068714C
void fn_3_480B8(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    int i;
    InMemRunnerType* runner = &g_Runners[3];
    int baseToTarget = 4;

    {
        for (i = 3; i >= 0; runner--, i--) {
            if (runner->runnerOnFieldOrOutOrScored != RUNNER_STATUS_ON_FIELD) {
                continue;
            }
            if (lbl_3_rodata_C50 <= runner->fractionalBasesRan &&
                runner->runningDirectionCode == 1 &&
                runner->tagUpInd != TAG_UP_TYPE_TAGGED) {
                continue;
            }
            {
                InMemRunnerType* r = &g_Runners[i];
                f32 fractionalBasesRan = r->fractionalBasesRan;

                if (fractionalBasesRan >= lbl_3_rodata_B78) {
                    baseToTarget = -1;
                    break;
                }
                if (r->tagUpInd == TAG_UP_TYPE_TAGGED && r->percentTowardsNextBase >= lbl_3_rodata_C38) {
                    baseToTarget = r->startingBase_baseAchieved;
                    break;
                }
                if (fractionalBasesRan >= lbl_3_rodata_B68) {
                    if (fractionalBasesRan >= lbl_3_rodata_C54) {
                        if (g_Runners[i].runningDirectionCode == 1) {
                            baseToTarget = -1;
                            break;
                        }
                    }
                    baseToTarget = 3;
                    break;
                } else {
                    if (fractionalBasesRan >= lbl_3_rodata_C48) {
                        if (g_Runners[i].runningDirectionCode == 1) {
                            baseToTarget = 3;
                            break;
                        }
                    }
                    baseToTarget = 2;
                    break;
                }
            }
        }
    }

    if (baseToTarget != -1) {
        f32 x;
        f32 z;

        fielder->baseCuttoffIsTargeting = baseToTarget;
        if (setCutoffLocationToStandAt(fielderIndex, &x, &z)) {
            fielder->IntendedLocation.x = x;
            fielder->IntendedLocation.z = z;

            {
                f32 deltaZ = z - fielder->pos.z;
                f32 deltaX = x - fielder->pos.x;

                if (deltaX == lbl_3_rodata_B20 && deltaZ == lbl_3_rodata_B20) {
                    fielder->currentVelocity = lbl_3_rodata_B20;
                    fielder->distanceFromAutoLocation = lbl_3_rodata_B20;
                } else {
                    fielder->desiredMovementDirection2 = (f32) atan2(deltaZ, deltaX);
                    fielder->distanceFromAutoLocation = fielderSqrt(deltaZ * deltaZ + deltaX * deltaX);
                }
            }

            fielder->goingToAutoLocationInd = 1;
        }
    }
}

// .text:0x000483CC size:0xB4 mapped:0x80687460
void fn_3_483CC(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];

    fielder->locationResponsibleForCovering = setFielderLocToBeNearBase(fielderIndex);
    fielder->isResponsibleForCoveringALocation = 2;

    if (fielderIndex != -1) {
        fielder->autoMovementFunctionIndex = 14;
        if (autoMovementFunctions[14].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[14].code;
        }
        fielder->unknown_writeOnly = 0;
        fielder->fielderVeloAdjustmentCode = 0;
        fielder->unknown_writeOnly_always0 = 0;
        fielder->timeSinceThrowWasCaught = 0;
        fielder->fielderTrackingBallState = 0;
    }

    fielder->fielderVeloAdjustmentCode = 0;
    g_FieldingLogic.cutoffFielderIndex = -1;
}

// .text:0x00048480 size:0x5D4 mapped:0x80687514
void autoMovement5(int fielderIndex) {
    return;
}

// .text:0x00048A54 size:0xAA0 mapped:0x80687AE8
void autoMovement11_cutoff_setInitialLocation(int fielderIndex) {
    return;
}

extern const f32 lbl_3_rodata_B60;

// .text:0x000494F4 size:0x4D0 mapped:0x80688588
void secondaryOutfielderWhenToStopMoving(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    f32 dx;
    f32 dz;
    f32 dist;
    f32 normX;
    f32 normZ;
    f32 intendedX;
    f32 intendedZ;
    f32 deltaX;
    f32 deltaZ;

    if (g_Ball.pauseBallMovementWhenInPlant) {
        dx = g_Ball.AtBat_Contact_BallPos.x - fielder->pos.x;
        dz = g_Ball.AtBat_Contact_BallPos.z - fielder->pos.z;
        dist = fielderSqrt(dx * dx + dz * dz);

        if (dist < fielderActionConstants[37]) {
            goto resetToRestingPosition;
        }

        normX = dx / dist;
        normZ = dz / dist;
        intendedX = fielder->pos.x + (fielderActionConstants[36] - lbl_3_rodata_B60) * normX;
        intendedZ = fielder->pos.z + (fielderActionConstants[36] - lbl_3_rodata_B60) * normZ;
        fielder->IntendedLocation.x = intendedX;
        fielder->IntendedLocation.z = intendedZ;

        deltaX = intendedX - fielder->pos.x;
        deltaZ = intendedZ - fielder->pos.z;

        if (deltaX == lbl_3_rodata_B20 && deltaZ == lbl_3_rodata_B20) {
            fielder->currentVelocity = lbl_3_rodata_B20;
            fielder->distanceFromAutoLocation = lbl_3_rodata_B20;
        } else {
            fielder->desiredMovementDirection2 = (f32) atan2(deltaZ, deltaX);
            fielder->distanceFromAutoLocation = fielderSqrt(deltaZ * deltaZ + deltaX * deltaX);
        }

        fielder->goingToAutoLocationInd = 1;
    }

    if (g_Ball.hitWallInd) {
        if (fielder->distanceFromBall < fielderActionConstants[1]) {
            goto resetToRestingPosition;
        }
    } else {
        dx = g_Ball.AtBat_Contact_BallPos.x - g_Ball.ballWillHitBallPos.x;
        dz = g_Ball.AtBat_Contact_BallPos.z - g_Ball.ballWillHitBallPos.z;
        dist = fielderSqrt(dx * dx + dz * dz);

        if (dist < fielderActionConstants[2] && fielder->groundDistanceFromBall < fielderActionConstants[3]) {
            goto resetToRestingPosition;
        }
    }

    if (g_Ball.hitClassification1 == 2 && fielder->groundDistanceFromBall < fielderActionConstants[3]) {
        goto resetToRestingPosition;
    }

    return;

resetToRestingPosition:
    fielder->IntendedLocation.x = fielder->pos.x;
    fielder->IntendedLocation.y = fielder->pos.y;
    fielder->IntendedLocation.z = fielder->pos.z;
    fielder->velocityX = lbl_3_rodata_B20;
    fielder->velocityZ = lbl_3_rodata_B20;
    fielder->currentVelocity = lbl_3_rodata_B20;
    fielder->distanceFromAutoLocation = lbl_3_rodata_B20;
}

// .text:0x000499C4 size:0x254 mapped:0x80688A58
void setSecondaryFielderToBe12mFromDropSpotToSupport(int fielderIndex, VecXYZ* out) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    int secondaryFielder;
    int diff;
    int frame;
    int targetFrame;
    CoordAndDist* futureCoord;
    f32 threshold;
    f32 x;
    f32 z;
    f32 dist;
    f32 sqx, sqz;

    out->y = lbl_3_rodata_B20;

    secondaryFielder = g_FieldingLogic.selectedFielder;
    if (g_FieldingLogic.secondaryFielder >= 0) {
        secondaryFielder = g_FieldingLogic.secondaryFielder;
    }

    targetFrame = 0;
    diff = g_Fielders[secondaryFielder].framesToGetToBallLandingSpot - g_Ball.framesSinceHit;
    if (diff > 0) {
        futureCoord = &g_Ball.physicsSubstruct.futureCoordsAndDist[diff];
        threshold = futureCoord->dist + fielderActionConstants[0];
        for (frame = diff + 1; frame < 360; frame += 3) {
            if (threshold < futureCoord->dist) {
                break;
            }
        }
        if (frame < 360) {
            targetFrame = frame;
        }
    }

    if (targetFrame == 0) {
        diff = fielder->framesToGetToBallLandingSpot - g_Ball.framesSinceHit;
        if (diff > 0) {
            if (diff < 360) {
                frame = diff;
            } else {
                frame = 359;
            }
        } else {
            frame = 90;
        }

        futureCoord = &g_Ball.physicsSubstruct.futureCoordsAndDist[frame];
        x = futureCoord->pos.x;
        z = futureCoord->pos.z;
        sqx = x * x;
        sqz = z * z;
        dist = fielderSqrt(sqx + sqz);

        out->x = (x / dist) * (dist + fielderActionConstants[0]);
        out->z = (z / dist) * (dist + fielderActionConstants[0]);
    } else {
        futureCoord = &g_Ball.physicsSubstruct.futureCoordsAndDist[targetFrame];
        out->x = futureCoord->pos.x;
        out->z = futureCoord->pos.z;
    }
}

// .text:0x00049C18 size:0x290 mapped:0x80688CAC
void autoMovement24_goTowardsHitBall_humanTeam(int fielderIndex) {
    return;
}

// .text:0x00049EA8 size:0x94 mapped:0x80688F3C
void fn_3_49EA8(int fielderIndex) {
    InMemFielder* fielder;

    if (g_FieldingLogic.fielderAutoMovementCode[fielderIndex] == 9) {
        return;
    }

    g_Fielders[fielderIndex].locationResponsibleForCovering = 7;
    if (fielderIndex != -1) {
        fielder = &g_Fielders[fielderIndex];
        fielder->autoMovementFunctionIndex = 14;
        if (autoMovementFunctions[14].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[14].code;
        }
        fielder->unknown_writeOnly = 0;
        fielder->fielderVeloAdjustmentCode = 0;
        fielder->unknown_writeOnly_always0 = 0;
        fielder->timeSinceThrowWasCaught = 0;
        fielder->fielderTrackingBallState = 0;
    }
    g_Fielders[fielderIndex].fielderVeloAdjustmentCode = 0;
    g_Fielders[fielderIndex].presetLocationCategory = -1;
}

// .text:0x00049F3C size:0x4 mapped:0x80688FD0
void updateFielderValuesSubFunction3_empty(void) {
    return;
}

// .text:0x00049F40 size:0x1E4 mapped:0x80688FD4
void autoMovementDetermineWhatToDo(int fielderIndex, int arg1) {
    InMemFielder* fielder;

    if (g_FieldingLogic.fielderAutoMovementCode[fielderIndex] != 0) {
        return;
    }

    fielder = &g_Fielders[fielderIndex];
    fielder->presetLocationToStandAt = arg1;

    if (arg1 == 0) {
        if (g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam] != 0) {
            if (fielderIndex == -1) {
                return;
            }
            fielder->autoMovementFunctionIndex = 3;
            if (autoMovementFunctions[3].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[3].code;
            }
            fielder->unknown_writeOnly = 0;
            fielder->fielderVeloAdjustmentCode = 0;
            fielder->unknown_writeOnly_always0 = 0;
            fielder->timeSinceThrowWasCaught = 0;
            fielder->fielderTrackingBallState = 0;
            return;
        }

        if (fielderIndex == -1) {
            return;
        }
        fielder->autoMovementFunctionIndex = 24;
        if (autoMovementFunctions[24].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[24].code;
        }
        fielder->unknown_writeOnly = 0;
        fielder->fielderVeloAdjustmentCode = 0;
        fielder->unknown_writeOnly_always0 = 0;
        fielder->timeSinceThrowWasCaught = 0;
        fielder->fielderTrackingBallState = 0;
        g_FieldingLogic.someFielderIndex = fielderIndex;
        return;
    }

    if (arg1 == 1) {
        if (fielderIndex == -1) {
            return;
        }
        fielder->autoMovementFunctionIndex = 8;
        if (autoMovementFunctions[8].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[8].code;
        }
        fielder->unknown_writeOnly = 0;
        fielder->fielderVeloAdjustmentCode = 0;
        fielder->unknown_writeOnly_always0 = 0;
        fielder->timeSinceThrowWasCaught = 0;
        fielder->fielderTrackingBallState = 0;
        return;
    }

    if (fielderIndex != -1) {
        fielder->autoMovementFunctionIndex = 7;
        if (autoMovementFunctions[7].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[7].code;
        }
        fielder->unknown_writeOnly = 0;
        fielder->fielderVeloAdjustmentCode = 0;
        fielder->unknown_writeOnly_always0 = 0;
        fielder->timeSinceThrowWasCaught = 0;
        fielder->fielderTrackingBallState = 0;
    }

    if (arg1 == 2 || arg1 == 4) {
        g_Fielders[fielderIndex].presetLocationCategory = 1;
    }
    if (arg1 == 3 || arg1 == 5) {
        g_Fielders[fielderIndex].presetLocationCategory = 3;
    }
    if (arg1 == 6 || arg1 == 7) {
        g_Fielders[fielderIndex].presetLocationCategory = 2;
    }
}

// .text:0x0004A124 size:0x2E4 mapped:0x806891B8
void setInitialFielderMovements_restOfFielders(void) {
    u8 hitClass = g_Ball.hitClassification3;
    u8 autoCode;
    sAng angle;
    int i;

    if (hitClass == 5) {
        autoCode = g_FieldingLogic.fielderAutoMovementCode[2];
        if (autoCode == 1 || autoCode == 0xa || autoCode == 0xb) {
            autoMovementDetermineWhatToDo(8, 0);
            autoMovementDetermineWhatToDo(6, 7);
            autoMovementDetermineWhatToDo(7, 1);
            return;
        }

        autoCode = g_FieldingLogic.fielderAutoMovementCode[4];
        if (autoCode == 1 || autoCode == 0xa || autoCode == 0xb) {
            autoMovementDetermineWhatToDo(6, 0);
            autoMovementDetermineWhatToDo(7, 1);
            autoMovementDetermineWhatToDo(8, 4);
            return;
        }

        autoMovementDetermineWhatToDo(7, 0);
        angle = g_Ball.Hit_HorizontalAngle;
        if (angle < 0x400) {
            autoMovementDetermineWhatToDo(8, 0);
            autoMovementDetermineWhatToDo(6, 7);
            return;
        }

        autoMovementDetermineWhatToDo(6, 0);
        autoMovementDetermineWhatToDo(8, 4);
        return;
    } else if (hitClass == 6) {
        autoMovementDetermineWhatToDo(7, 0);
        angle = g_Ball.Hit_HorizontalAngle;
        if (angle >= 0x3e0 && angle < 0x420) {
            autoMovementDetermineWhatToDo(8, 0);
            autoMovementDetermineWhatToDo(6, 0);
            return;
        }

        if (angle < 0x400) {
            autoMovementDetermineWhatToDo(8, 0);
            autoMovementDetermineWhatToDo(6, 7);
            return;
        }

        autoMovementDetermineWhatToDo(6, 0);
        autoMovementDetermineWhatToDo(8, 6);
        return;
    } else if (hitClass == 7) {
        autoCode = g_FieldingLogic.fielderAutoMovementCode[1];
        if (autoCode != 1 && autoCode != 0xa && autoCode != 0xb) {
            autoMovementDetermineWhatToDo(8, 0);
            autoMovementDetermineWhatToDo(6, 1);
            autoMovementDetermineWhatToDo(7, 1);
            return;
        }

        autoMovementDetermineWhatToDo(6, 1);
        autoMovementDetermineWhatToDo(7, 1);
        autoMovementDetermineWhatToDo(8, 1);
        return;
    } else if (hitClass == 8) {
        autoCode = g_FieldingLogic.fielderAutoMovementCode[1];
        if (autoCode != 1 && autoCode != 0xa && autoCode != 0xb) {
            autoMovementDetermineWhatToDo(6, 0);
            autoMovementDetermineWhatToDo(7, 1);
            autoMovementDetermineWhatToDo(8, 1);
            return;
        }

        autoMovementDetermineWhatToDo(6, 1);
        autoMovementDetermineWhatToDo(7, 1);
        autoMovementDetermineWhatToDo(8, 1);
        return;
    }

    autoMovementDetermineWhatToDo(6, 1);
    autoMovementDetermineWhatToDo(7, 1);
    autoMovementDetermineWhatToDo(8, 4);
    for (i = 2; i < 6; i++) {
        autoMovementDetermineWhatToDo(i, 0);
    }
}

// .text:0x0004A408 size:0x5A4 mapped:0x8068949C
void setIntendedLocationAheadOfBallPath(void) {
    return;
}

// .text:0x0004A9AC size:0x77C mapped:0x80689A40
void autoMovement13_GoTowardsBallAsBackUp(int fielderIndex) {
    return;
}

// .text:0x0004B128 size:0x3EC mapped:0x8068A1BC
void autoMovement6_outfielderNoCatch_Phase2(int fielderIndex) {
    return;
}

// .text:0x0004B514 size:0x3BC mapped:0x8068A5A8
void autoMovement7_8_outfiederNoCatch_Phase1(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    f32 offsetX = lbl_3_rodata_B20;
    f32 targetX;
    f32 targetZ;
    f32 dx;
    f32 dz;

    if (updateFielderPositionAndVelocityForSpecialActions(fielderIndex) == 0) {
        if (fielder->presetLocationToStandAt >= 2) {
            targetX = presetFielderLocations[fielder->presetLocationToStandAt].x;
            targetZ = presetFielderLocations[fielder->presetLocationToStandAt].z;
            fielder->IntendedLocation.x = targetX;
            fielder->IntendedLocation.z = targetZ;

            dx = targetX - fielder->pos.x;
            dz = targetZ - fielder->pos.z;

            if (lbl_3_rodata_B20 == dx && lbl_3_rodata_B20 == dz) {
                fielder->currentVelocity = lbl_3_rodata_B20;
                fielder->distanceFromAutoLocation = lbl_3_rodata_B20;
            } else {
                fielder->desiredMovementDirection2 = ATAN2F(dz, dx);
                fielder->distanceFromAutoLocation = fielderSqrt(dx * dx + dz * dz);
            }

            fielder->goingToAutoLocationInd = 1;
        } else {
            if (fielderIndex == 6) {
                offsetX = lbl_3_rodata_BA0;
            }
            if (fielderIndex == 8) {
                offsetX = lbl_3_rodata_BD4;
            }

            targetX = fielder->pos.x + offsetX;
            targetZ = fielder->pos.z - lbl_3_rodata_B9C;

            fielder->IntendedLocation.x = targetX;
            fielder->IntendedLocation.z = targetZ;

            dx = targetX - fielder->pos.x;
            dz = targetZ - fielder->pos.z;

            if (lbl_3_rodata_B20 == dx && lbl_3_rodata_B20 == dz) {
                fielder->currentVelocity = lbl_3_rodata_B20;
                fielder->distanceFromAutoLocation = lbl_3_rodata_B20;
            } else {
                fielder->desiredMovementDirection2 = ATAN2F(dz, dx);
                fielder->distanceFromAutoLocation = fielderSqrt(dx * dx + dz * dz);
            }

            fielder->goingToAutoLocationInd = 1;
        }

        if (fielderIndex != -1) {
            fielder->autoMovementFunctionIndex = 6;
            if (autoMovementFunctions[6].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[6].code;
            }
            fielder->unknown_writeOnly = 0;
            fielder->fielderVeloAdjustmentCode = 0;
            fielder->unknown_writeOnly_always0 = 0;
            fielder->timeSinceThrowWasCaught = 0;
            fielder->fielderTrackingBallState = 0;
        }
    }
}

// .text:0x0004B8D0 size:0x13C mapped:0x8068A964
void fn_3_4B8D0(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    s16 covering = fielder->locationResponsibleForCovering;

    if (covering < 0) {
        return;
    }

    if (covering <= 3) {
        if (g_FieldingLogic.fielderAssignedLocationIndex[covering] == fielderIndex) {
            g_FieldingLogic.fielderAssignedLocationIndex[covering] = -1;
            g_FieldingLogic.baseCoveredInd[covering] = 0;
        }

        fielder->locationResponsibleForCovering = -1;
        fielder->isResponsibleForCoveringALocation = 0;

        if (fielder->autoMovementFunctionIndex != 1) {
            return;
        }
        if (fielderIndex == -1) {
            return;
        }

        fielder->autoMovementFunctionIndex = 12;
        if (autoMovementFunctions[12].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[12].code;
        }
        fielder->unknown_writeOnly = 0;
        fielder->fielderVeloAdjustmentCode = 0;
        fielder->unknown_writeOnly_always0 = 0;
        fielder->timeSinceThrowWasCaught = 0;
        fielder->fielderTrackingBallState = 0;
    } else if (covering == 5) {
        fielder->locationResponsibleForCovering = -1;
        g_FieldingLogic.fielderAssignedLocationIndex[4] = -1;
        fielder->isResponsibleForCoveringALocation = 0;
        g_FieldingLogic.playerAtMoundCutoffLocation = 0;

        if (fielder->autoMovementFunctionIndex != 14) {
            return;
        }
        if (fielderIndex == -1) {
            return;
        }

        fielder->autoMovementFunctionIndex = 12;
        if (autoMovementFunctions[12].code >= 0) {
            g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[12].code;
        }
        fielder->unknown_writeOnly = 0;
        fielder->fielderVeloAdjustmentCode = 0;
        fielder->unknown_writeOnly_always0 = 0;
        fielder->timeSinceThrowWasCaught = 0;
        fielder->fielderTrackingBallState = 0;
    }
}

// .text:0x0004BA0C size:0xFBC mapped:0x8068AAA0
void updateSomeAutoMovementAssignments(void) {
    int numAssigned;
    int problemOutfieldBase;
    int i;
    InMemFielder* fielder;

    if (g_Strikes.outs >= 3) {
        return;
    }
    if (g_RunningLogic._10 == 0) {
        return;
    }

    problemOutfieldBase = -1;

    numAssigned = 0;
    if (g_FieldingLogic.fielderAssignedLocationIndex[0] != -1) {
        numAssigned = 1;
        if (g_FieldingLogic.fielderAssignedLocationIndex[1] != -1) {
            numAssigned = 2;
            if (g_FieldingLogic.fielderAssignedLocationIndex[2] != -1) {
                numAssigned = 3;
                if (g_FieldingLogic.fielderAssignedLocationIndex[3] != -1) {
                    numAssigned = 4;
                }
            }
        }
    }

    if (g_Fielders[0].pitcherHeadingToCover1stOr3rd == 1 &&
        g_Fielders[0].locationResponsibleForCovering != 1 &&
        g_Fielders[0].locationResponsibleForCovering != 3) {
        g_Fielders[0].pitcherHeadingToCover1stOr3rd = 0;
    }

    for (i = 0; i < 4; i++) {
        int fielderIndex;
        int code;

        if (g_FieldingLogic.baseCoveredInd[i] != 0) {
            continue;
        }
        fielderIndex = g_FieldingLogic.fielderAssignedLocationIndex[i];
        if (fielderIndex < 0) {
            continue;
        }
        code = g_FieldingLogic.fielderAutoMovementCode[fielderIndex];

        if (code == 7) {
            fielder = &g_Fielders[fielderIndex];
            if (i == g_FieldingLogic.somethingForTryingTagOutTargetBase) {
                if (fielder->distanceToBases[i] >= lbl_3_rodata_B78) {
                    int loc = fielder->locationResponsibleForCovering;
                    if (loc >= 0) {
                        if (loc <= 3) {
                            if (g_FieldingLogic.fielderAssignedLocationIndex[loc] == fielderIndex) {
                                g_FieldingLogic.fielderAssignedLocationIndex[loc] = -1;
                                g_FieldingLogic.baseCoveredInd[loc] = 0;
                            }
                            fielder->locationResponsibleForCovering = -1;
                            fielder->isResponsibleForCoveringALocation = 0;
                            if (fielder->autoMovementFunctionIndex == 1) {
                                fielder->autoMovementFunctionIndex = 12;
                                if (autoMovementFunctions[12].code >= 0) {
                                    g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[12].code;
                                }
                                fielder->unknown_writeOnly = 0;
                                fielder->fielderVeloAdjustmentCode = 0;
                                fielder->unknown_writeOnly_always0 = 0;
                                fielder->timeSinceThrowWasCaught = 0;
                                fielder->fielderTrackingBallState = 0;
                            }
                        } else if (loc == 5) {
                            fielder->locationResponsibleForCovering = -1;
                            fielder->isResponsibleForCoveringALocation = 0;
                            g_FieldingLogic.fielderAssignedLocationIndex[4] = -1;
                            g_FieldingLogic.playerAtMoundCutoffLocation = 0;
                            if (fielder->autoMovementFunctionIndex == 14) {
                                fielder->autoMovementFunctionIndex = 12;
                                if (autoMovementFunctions[12].code >= 0) {
                                    g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[12].code;
                                }
                                fielder->unknown_writeOnly = 0;
                                fielder->fielderVeloAdjustmentCode = 0;
                                fielder->unknown_writeOnly_always0 = 0;
                                fielder->timeSinceThrowWasCaught = 0;
                                fielder->fielderTrackingBallState = 0;
                            }
                        }
                    }
                }
            } else {
                if (fielder->distanceToBases[i] > lbl_3_rodata_C08) {
                    int loc = fielder->locationResponsibleForCovering;
                    if (loc >= 0) {
                        if (loc <= 3) {
                            if (g_FieldingLogic.fielderAssignedLocationIndex[loc] == fielderIndex) {
                                g_FieldingLogic.fielderAssignedLocationIndex[loc] = -1;
                                g_FieldingLogic.baseCoveredInd[loc] = 0;
                            }
                            fielder->locationResponsibleForCovering = -1;
                            fielder->isResponsibleForCoveringALocation = 0;
                            if (fielder->autoMovementFunctionIndex == 1) {
                                fielder->autoMovementFunctionIndex = 12;
                                if (autoMovementFunctions[12].code >= 0) {
                                    g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[12].code;
                                }
                                fielder->unknown_writeOnly = 0;
                                fielder->fielderVeloAdjustmentCode = 0;
                                fielder->unknown_writeOnly_always0 = 0;
                                fielder->timeSinceThrowWasCaught = 0;
                                fielder->fielderTrackingBallState = 0;
                            }
                        } else if (loc == 5) {
                            fielder->locationResponsibleForCovering = -1;
                            fielder->isResponsibleForCoveringALocation = 0;
                            g_FieldingLogic.fielderAssignedLocationIndex[4] = -1;
                            g_FieldingLogic.playerAtMoundCutoffLocation = 0;
                            if (fielder->autoMovementFunctionIndex == 14) {
                                fielder->autoMovementFunctionIndex = 12;
                                if (autoMovementFunctions[12].code >= 0) {
                                    g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[12].code;
                                }
                                fielder->unknown_writeOnly = 0;
                                fielder->fielderVeloAdjustmentCode = 0;
                                fielder->unknown_writeOnly_always0 = 0;
                                fielder->timeSinceThrowWasCaught = 0;
                                fielder->fielderTrackingBallState = 0;
                            }
                        }
                    }
                }
            }
        } else if (code == 1 || code == 10 || code == 11) {
            fielder = &g_Fielders[fielderIndex];
            if (fielder->distanceToBases[i] > lbl_3_rodata_B68) {
                int loc = fielder->locationResponsibleForCovering;
                if (loc >= 0) {
                    if (loc <= 3) {
                        if (g_FieldingLogic.fielderAssignedLocationIndex[loc] == fielderIndex) {
                            g_FieldingLogic.fielderAssignedLocationIndex[loc] = -1;
                            g_FieldingLogic.baseCoveredInd[loc] = 0;
                        }
                        fielder->locationResponsibleForCovering = -1;
                        fielder->isResponsibleForCoveringALocation = 0;
                        if (fielder->autoMovementFunctionIndex == 1) {
                            fielder->autoMovementFunctionIndex = 12;
                            if (autoMovementFunctions[12].code >= 0) {
                                g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[12].code;
                            }
                            fielder->unknown_writeOnly = 0;
                            fielder->fielderVeloAdjustmentCode = 0;
                            fielder->unknown_writeOnly_always0 = 0;
                            fielder->timeSinceThrowWasCaught = 0;
                            fielder->fielderTrackingBallState = 0;
                        }
                    } else if (loc == 5) {
                        fielder->locationResponsibleForCovering = -1;
                        fielder->isResponsibleForCoveringALocation = 0;
                        g_FieldingLogic.fielderAssignedLocationIndex[4] = -1;
                        g_FieldingLogic.playerAtMoundCutoffLocation = 0;
                        if (fielder->autoMovementFunctionIndex == 14) {
                            fielder->autoMovementFunctionIndex = 12;
                            if (autoMovementFunctions[12].code >= 0) {
                                g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[12].code;
                            }
                            fielder->unknown_writeOnly = 0;
                            fielder->fielderVeloAdjustmentCode = 0;
                            fielder->unknown_writeOnly_always0 = 0;
                            fielder->timeSinceThrowWasCaught = 0;
                            fielder->fielderTrackingBallState = 0;
                        }
                    }
                }
            }
        }

        if (code == 2) {
            fielderIndex = g_FieldingLogic.fielderAssignedLocationIndex[i];
            if (g_Fielders[fielderIndex].distanceToBases[i] > lbl_3_rodata_B90) {
                if (problemOutfieldBase == -1) {
                    problemOutfieldBase = i;
                }
            }
        }
    }

    {
        int best9 = -1;
        int best8 = -1;
        int best7 = -1;
        int k;

        for (k = 0; k < 6; k++) {
            int code2 = g_FieldingLogic.fielderAutoMovementCode[k];
            if (g_Fielders[k].animatingActionInd == 0 && (code2 == 0 || (u32)(code2 - 8) <= 1)) {
                if (best9 == -1) {
                    best9 = k;
                } else if (best8 == -1) {
                    best8 = k;
                } else {
                    best7 = k;
                }
            }
        }

    if (numAssigned < 4) {
        int ballFielder = g_Ball.fielderWBallIndex;

        if (ballFielder >= 0) {
            fielder = &g_Fielders[ballFielder];
            if (fielder->distanceToBases[numAssigned] <=
                thresholdToBeConsideredCoveringBase_ByWeight[fielder->Weight]) {
                fielder->locationResponsibleForCovering = numAssigned;
                g_FieldingLogic.fielderAssignedLocationIndex[numAssigned] = ballFielder;
                fielder->isResponsibleForCoveringALocation = 1;
                g_FieldingLogic.baseCoveredInd[numAssigned] = 1;
                return;
            }
        }

        if (best9 == -1) {
            return;
        }

        {
            f32 dist9;
            f32 dist8 = lbl_3_rodata_BA4;
            f32 dist7 = lbl_3_rodata_BA4;
            int winner = best7;
            f32 dx, dz;

            dx = g_Fielders[best9].pos.x - base_MoundCoordinates[numAssigned].x;
            dz = g_Fielders[best9].pos.z - base_MoundCoordinates[numAssigned].z;
            dist9 = fielderSqrt(dx * dx + dz * dz);

            if (best8 >= 0) {
                dx = g_Fielders[best8].pos.x - base_MoundCoordinates[numAssigned].x;
                dz = g_Fielders[best8].pos.z - base_MoundCoordinates[numAssigned].z;
                dist8 = fielderSqrt(dx * dx + dz * dz);
            }

            if (best7 >= 0) {
                dx = g_Fielders[best7].pos.x - base_MoundCoordinates[numAssigned].x;
                dz = g_Fielders[best7].pos.z - base_MoundCoordinates[numAssigned].z;
                dist7 = fielderSqrt(dx * dx + dz * dz);
            }

            if (dist9 >= dist8) {
                if (dist9 < dist7) {
                    winner = best9;
                }
            } else {
                if (dist8 < dist7) {
                    winner = best8;
                }
            }

            fielder = &g_Fielders[winner];
            fielder->locationResponsibleForCovering = numAssigned;
            fielder->isResponsibleForCoveringALocation = 1;
            if (winner != -1) {
                fielder->autoMovementFunctionIndex = 1;
                if (autoMovementFunctions[1].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[winner] = autoMovementFunctions[1].code;
                }
                fielder->unknown_writeOnly = 0;
                fielder->fielderVeloAdjustmentCode = 0;
                fielder->unknown_writeOnly_always0 = 0;
                fielder->timeSinceThrowWasCaught = 0;
                fielder->fielderTrackingBallState = 0;
            }
            g_FieldingLogic.fielderAssignedLocationIndex[numAssigned] = winner;
            if (g_FieldingLogic.fielderAssignedLocationIndex[4] == winner) {
                g_FieldingLogic.fielderAssignedLocationIndex[4] = -1;
                g_FieldingLogic.playerAtMoundCutoffLocation = 0;
            }
        }
        return;
    }

    if (problemOutfieldBase >= 0) {
        int oldFielder;
        int newFielder = -1;
        int k;

        for (k = 0; k < 6; k++) {
            int code2 = g_FieldingLogic.fielderAutoMovementCode[k];
            if (code2 == 0 || code2 == 8 || code2 == 9) {
                f32 dist = g_Fielders[k].distanceToBases[problemOutfieldBase];
                if (dist < lbl_3_rodata_B9C) {
                    if (newFielder == -1) {
                        newFielder = k;
                    } else if (dist + lbl_3_rodata_B78 < g_Fielders[newFielder].distanceToBases[problemOutfieldBase]) {
                        newFielder = k;
                    }
                }
            }
        }

        if (newFielder < 0) {
            return;
        }

        oldFielder = g_FieldingLogic.fielderAssignedLocationIndex[problemOutfieldBase];
        if (oldFielder != -1) {
            g_Fielders[oldFielder].autoMovementFunctionIndex = 12;
            if (autoMovementFunctions[12].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[oldFielder] = autoMovementFunctions[12].code;
            }
            g_Fielders[oldFielder].unknown_writeOnly = 0;
            g_Fielders[oldFielder].fielderVeloAdjustmentCode = 0;
            g_Fielders[oldFielder].unknown_writeOnly_always0 = 0;
            g_Fielders[oldFielder].timeSinceThrowWasCaught = 0;
            g_Fielders[oldFielder].fielderTrackingBallState = 0;
        }

        oldFielder = g_FieldingLogic.fielderAssignedLocationIndex[problemOutfieldBase];
        fielder = &g_Fielders[oldFielder];
        fielder->unknown_writeOnly = 3;
        {
            int loc = fielder->locationResponsibleForCovering;
            if (loc >= 0) {
                if (loc <= 3) {
                    if (g_FieldingLogic.fielderAssignedLocationIndex[loc] == oldFielder) {
                        g_FieldingLogic.fielderAssignedLocationIndex[loc] = -1;
                        g_FieldingLogic.baseCoveredInd[loc] = 0;
                    }
                    fielder->locationResponsibleForCovering = -1;
                    fielder->isResponsibleForCoveringALocation = 0;
                    if (fielder->autoMovementFunctionIndex == 1) {
                        fielder->autoMovementFunctionIndex = 12;
                        if (autoMovementFunctions[12].code >= 0) {
                            g_FieldingLogic.fielderAutoMovementCode[oldFielder] = autoMovementFunctions[12].code;
                        }
                        fielder->unknown_writeOnly = 0;
                        fielder->fielderVeloAdjustmentCode = 0;
                        fielder->unknown_writeOnly_always0 = 0;
                        fielder->timeSinceThrowWasCaught = 0;
                        fielder->fielderTrackingBallState = 0;
                    }
                } else if (loc == 5) {
                    fielder->locationResponsibleForCovering = -1;
                    fielder->isResponsibleForCoveringALocation = 0;
                    g_FieldingLogic.fielderAssignedLocationIndex[4] = -1;
                    g_FieldingLogic.playerAtMoundCutoffLocation = 0;
                    if (fielder->autoMovementFunctionIndex == 14) {
                        fielder->autoMovementFunctionIndex = 12;
                        if (autoMovementFunctions[12].code >= 0) {
                            g_FieldingLogic.fielderAutoMovementCode[oldFielder] = autoMovementFunctions[12].code;
                        }
                        fielder->unknown_writeOnly = 0;
                        fielder->fielderVeloAdjustmentCode = 0;
                        fielder->unknown_writeOnly_always0 = 0;
                        fielder->timeSinceThrowWasCaught = 0;
                        fielder->fielderTrackingBallState = 0;
                    }
                }
            }
        }

        fielder = &g_Fielders[newFielder];
        fielder->locationResponsibleForCovering = problemOutfieldBase;
        fielder->isResponsibleForCoveringALocation = 1;
        if (newFielder != -1) {
            fielder->autoMovementFunctionIndex = 1;
            if (autoMovementFunctions[1].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[newFielder] = autoMovementFunctions[1].code;
            }
            fielder->unknown_writeOnly = 0;
            fielder->fielderVeloAdjustmentCode = 0;
            fielder->unknown_writeOnly_always0 = 0;
            fielder->timeSinceThrowWasCaught = 0;
            fielder->fielderTrackingBallState = 0;
        }
        g_FieldingLogic.fielderAssignedLocationIndex[problemOutfieldBase] = newFielder;
        if (g_FieldingLogic.fielderAssignedLocationIndex[4] == newFielder) {
            g_FieldingLogic.fielderAssignedLocationIndex[4] = -1;
            g_FieldingLogic.playerAtMoundCutoffLocation = 0;
        }
        return;
    }

    {
        int cutoffFielder = g_FieldingLogic.fielderAssignedLocationIndex[4];
        int k;

        if (cutoffFielder != -1) {
            if (g_Fielders[cutoffFielder].locationResponsibleForCovering == 5) {
                return;
            }
        }

        if (g_Ball.ballState == BALL_STATE_HIT && g_Ball.ballZoneAwayFromHome <= 1) {
            return;
        }

        for (k = 0; k < 9; k++) {
            if (g_FieldingLogic.fielderAutoMovementCode[k] == 7) {
                if (g_Fielders[k].distanceToMound < f8_0) {
                    return;
                }
                break;
            }
        }

        if (best9 < 0) {
            return;
        }

        {
            f32 dist9 = g_Fielders[best9].distanceToMound;
            f32 dist8 = dist9;
            f32 dist7 = dist9;
            int winner = best7;

            if (best8 >= 0) {
                dist8 = g_Fielders[best8].distanceToMound;
            }
            if (best7 >= 0) {
                dist7 = g_Fielders[best7].distanceToMound;
            }

            if (dist9 >= dist8) {
                if (dist9 < dist7) {
                    winner = best9;
                }
            } else {
                if (dist8 < dist7) {
                    winner = best8;
                }
            }

            fielder = &g_Fielders[winner];
            fielder->locationResponsibleForCovering = 5;
            fielder->isResponsibleForCoveringALocation = 2;
            if (winner != -1) {
                fielder->autoMovementFunctionIndex = 14;
                if (autoMovementFunctions[14].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[winner] = autoMovementFunctions[14].code;
                }
                fielder->unknown_writeOnly = 0;
                fielder->fielderVeloAdjustmentCode = 0;
                fielder->unknown_writeOnly_always0 = 0;
                fielder->timeSinceThrowWasCaught = 0;
                fielder->fielderTrackingBallState = 0;
            }
            g_FieldingLogic.fielderAssignedLocationIndex[4] = winner;
        }
    }
    }
}

// .text:0x0004C9C8 size:0x5E8 mapped:0x8068BA5C
void setInitialFielderMovements_CoverBases(void) {
    g_FieldingLogic_s* fl = &g_FieldingLogic;
    int i;

    if (fl->fielderAutoMovementCode[1] == 0) {
        g_Fielders[1].locationResponsibleForCovering = 0;
        g_Fielders[1].autoMovementFunctionIndex = 1;
        if (autoMovementFunctions[1].code >= 0) {
            fl->fielderAutoMovementCode[1] = autoMovementFunctions[1].code;
        }
        g_Fielders[1].unknown_writeOnly = 0;
        g_Fielders[1].fielderVeloAdjustmentCode = 0;
        g_Fielders[1].unknown_writeOnly_always0 = 0;
        g_Fielders[1].timeSinceThrowWasCaught = 0;
        g_Fielders[1].fielderTrackingBallState = 0;
        fl->fielderAssignedLocationIndex[0] = 1;
    } else if (g_Ball.hitClassification2 == 7) {
        g_Fielders[0].locationResponsibleForCovering = 0;
        g_Fielders[0].autoMovementFunctionIndex = 1;
        if (autoMovementFunctions[1].code >= 0) {
            fl->fielderAutoMovementCode[0] = autoMovementFunctions[1].code;
        }
        g_Fielders[0].unknown_writeOnly = 0;
        g_Fielders[0].fielderVeloAdjustmentCode = 0;
        g_Fielders[0].unknown_writeOnly_always0 = 0;
        g_Fielders[0].timeSinceThrowWasCaught = 0;
        g_Fielders[0].fielderTrackingBallState = 0;
        fl->fielderAssignedLocationIndex[0] = 0;
    }

    if (fl->fielderAutoMovementCode[2] == 0) {
        g_Fielders[2].locationResponsibleForCovering = 1;
        g_Fielders[2].autoMovementFunctionIndex = 1;
        if (autoMovementFunctions[1].code >= 0) {
            fl->fielderAutoMovementCode[2] = autoMovementFunctions[1].code;
        }
        g_Fielders[2].unknown_writeOnly = 0;
        g_Fielders[2].fielderVeloAdjustmentCode = 0;
        g_Fielders[2].unknown_writeOnly_always0 = 0;
        g_Fielders[2].timeSinceThrowWasCaught = 0;
        g_Fielders[2].fielderTrackingBallState = 0;
        fl->fielderAssignedLocationIndex[1] = 2;
    } else {
        f32 futureZ = g_Ball.physicsSubstruct.futureCoordsAndDist[g_Fielders[2].framesToGetToBallLandingSpot].pos.z;
        if (futureZ >= base_MoundCoordinates[1].z) {
            g_Fielders[0].locationResponsibleForCovering = 1;
            g_Fielders[0].autoMovementFunctionIndex = 1;
            if (autoMovementFunctions[1].code >= 0) {
                fl->fielderAutoMovementCode[0] = autoMovementFunctions[1].code;
            }
            g_Fielders[0].unknown_writeOnly = 0;
            g_Fielders[0].fielderVeloAdjustmentCode = 0;
            g_Fielders[0].unknown_writeOnly_always0 = 0;
            g_Fielders[0].timeSinceThrowWasCaught = 0;
            g_Fielders[0].fielderTrackingBallState = 0;
            fl->fielderAssignedLocationIndex[1] = 0;
            g_Fielders[0].pitcherHeadingToCover1stOr3rd = 1;
        } else {
            g_Fielders[3].locationResponsibleForCovering = 1;
            g_Fielders[3].autoMovementFunctionIndex = 1;
            if (autoMovementFunctions[1].code >= 0) {
                fl->fielderAutoMovementCode[3] = autoMovementFunctions[1].code;
            }
            g_Fielders[3].unknown_writeOnly = 0;
            g_Fielders[3].fielderVeloAdjustmentCode = 0;
            g_Fielders[3].unknown_writeOnly_always0 = 0;
            g_Fielders[3].timeSinceThrowWasCaught = 0;
            g_Fielders[3].fielderTrackingBallState = 0;
            fl->fielderAssignedLocationIndex[1] = 3;
        }
    }

    if (fl->fielderAutoMovementCode[4] == 0) {
        g_Fielders[4].locationResponsibleForCovering = 3;
        g_Fielders[4].autoMovementFunctionIndex = 1;
        if (autoMovementFunctions[1].code >= 0) {
            fl->fielderAutoMovementCode[4] = autoMovementFunctions[1].code;
        }
        g_Fielders[4].unknown_writeOnly = 0;
        g_Fielders[4].fielderVeloAdjustmentCode = 0;
        g_Fielders[4].unknown_writeOnly_always0 = 0;
        g_Fielders[4].timeSinceThrowWasCaught = 0;
        g_Fielders[4].fielderTrackingBallState = 0;
        fl->fielderAssignedLocationIndex[3] = 4;
    } else {
        f32 futureZ = g_Ball.physicsSubstruct.futureCoordsAndDist[g_Fielders[4].framesToGetToBallLandingSpot].pos.z;
        if (futureZ >= base_MoundCoordinates[3].z) {
            g_Fielders[0].locationResponsibleForCovering = 3;
            g_Fielders[0].autoMovementFunctionIndex = 1;
            if (autoMovementFunctions[1].code >= 0) {
                fl->fielderAutoMovementCode[0] = autoMovementFunctions[1].code;
            }
            g_Fielders[0].unknown_writeOnly = 0;
            g_Fielders[0].fielderVeloAdjustmentCode = 0;
            g_Fielders[0].unknown_writeOnly_always0 = 0;
            g_Fielders[0].timeSinceThrowWasCaught = 0;
            g_Fielders[0].fielderTrackingBallState = 0;
            fl->fielderAssignedLocationIndex[3] = 0;
            g_Fielders[0].pitcherHeadingToCover1stOr3rd = 1;
        } else {
            g_Fielders[5].locationResponsibleForCovering = 3;
            g_Fielders[5].autoMovementFunctionIndex = 1;
            if (autoMovementFunctions[1].code >= 0) {
                fl->fielderAutoMovementCode[5] = autoMovementFunctions[1].code;
            }
            g_Fielders[5].unknown_writeOnly = 0;
            g_Fielders[5].fielderVeloAdjustmentCode = 0;
            g_Fielders[5].unknown_writeOnly_always0 = 0;
            g_Fielders[5].timeSinceThrowWasCaught = 0;
            g_Fielders[5].fielderTrackingBallState = 0;
            fl->fielderAssignedLocationIndex[3] = 5;
        }
    }

    if (g_Ball.Hit_HorizontalAngle < 0x400 || g_Ball.hitClassification3 == 7) {
        if (fl->fielderAutoMovementCode[5] == 0) {
            g_Fielders[5].locationResponsibleForCovering = 2;
            g_Fielders[5].autoMovementFunctionIndex = 1;
            if (autoMovementFunctions[1].code >= 0) {
                fl->fielderAutoMovementCode[5] = autoMovementFunctions[1].code;
            }
            g_Fielders[5].unknown_writeOnly = 0;
            g_Fielders[5].fielderVeloAdjustmentCode = 0;
            g_Fielders[5].unknown_writeOnly_always0 = 0;
            g_Fielders[5].timeSinceThrowWasCaught = 0;
            g_Fielders[5].fielderTrackingBallState = 0;
            fl->fielderAssignedLocationIndex[2] = 5;
        } else if (fl->fielderAutoMovementCode[3] == 0) {
            g_Fielders[3].locationResponsibleForCovering = 2;
            g_Fielders[3].autoMovementFunctionIndex = 1;
            if (autoMovementFunctions[1].code >= 0) {
                fl->fielderAutoMovementCode[3] = autoMovementFunctions[1].code;
            }
            g_Fielders[3].unknown_writeOnly = 0;
            g_Fielders[3].fielderVeloAdjustmentCode = 0;
            g_Fielders[3].unknown_writeOnly_always0 = 0;
            g_Fielders[3].timeSinceThrowWasCaught = 0;
            g_Fielders[3].fielderTrackingBallState = 0;
            fl->fielderAssignedLocationIndex[2] = 3;
        } else {
            g_Fielders[3].locationResponsibleForCovering = 2;
            g_Fielders[5].locationResponsibleForCovering = 2;
        }
    } else {
        if (fl->fielderAutoMovementCode[3] == 0) {
            g_Fielders[3].locationResponsibleForCovering = 2;
            g_Fielders[3].autoMovementFunctionIndex = 1;
            if (autoMovementFunctions[1].code >= 0) {
                fl->fielderAutoMovementCode[3] = autoMovementFunctions[1].code;
            }
            g_Fielders[3].unknown_writeOnly = 0;
            g_Fielders[3].fielderVeloAdjustmentCode = 0;
            g_Fielders[3].unknown_writeOnly_always0 = 0;
            g_Fielders[3].timeSinceThrowWasCaught = 0;
            g_Fielders[3].fielderTrackingBallState = 0;
            fl->fielderAssignedLocationIndex[2] = 3;
        } else if (fl->fielderAutoMovementCode[5] == 0) {
            g_Fielders[5].locationResponsibleForCovering = 2;
            g_Fielders[5].autoMovementFunctionIndex = 1;
            if (autoMovementFunctions[1].code >= 0) {
                fl->fielderAutoMovementCode[5] = autoMovementFunctions[1].code;
            }
            g_Fielders[5].unknown_writeOnly = 0;
            g_Fielders[5].fielderVeloAdjustmentCode = 0;
            g_Fielders[5].unknown_writeOnly_always0 = 0;
            g_Fielders[5].timeSinceThrowWasCaught = 0;
            g_Fielders[5].fielderTrackingBallState = 0;
            fl->fielderAssignedLocationIndex[2] = 5;
        } else {
            g_Fielders[3].locationResponsibleForCovering = 2;
            g_Fielders[5].locationResponsibleForCovering = 2;
        }
    }

    for (i = 0; i < 9; i++) {
        s16 loc = g_Fielders[i].locationResponsibleForCovering;
        if (loc >= 0 && loc <= 3) {
            g_Fielders[i].isResponsibleForCoveringALocation = 1;
        }
    }
}

// .text:0x0004CFB0 size:0x25C mapped:0x8068C044
void fn_3_4CFB0(void) {
    InMemFielder* fielder = &g_Fielders[0];
    s16 covering = fielder->locationResponsibleForCovering;
    f32 targetX;
    f32 targetZ;
    f32 dz;
    f32 dx;

    if (covering == 1) {
        f32 dist = base_MoundCoordinates[1].x - fielder->pos.x;
        if (dist > lbl_3_rodata_B70) {
            dist = lbl_3_rodata_B70;
        }
        targetX = base_MoundCoordinates[1].x;
        targetZ = base_MoundCoordinates[1].z - dist / lbl_3_rodata_B78;
    } else if (covering == 3) {
        f32 dist = fielder->pos.x - base_MoundCoordinates[3].x;
        if (dist > lbl_3_rodata_B70) {
            dist = lbl_3_rodata_B70;
        }
        targetX = base_MoundCoordinates[3].x;
        targetZ = base_MoundCoordinates[3].z - dist / lbl_3_rodata_B78;
    } else {
        targetX = base_MoundCoordinates[covering].x;
        targetZ = base_MoundCoordinates[covering].z;
    }

    fielder = &g_Fielders[0];
    fielder->IntendedLocation.x = targetX;
    fielder->IntendedLocation.z = targetZ;

    dz = targetZ - fielder->pos.z;
    dx = targetX - fielder->pos.x;

    if (lbl_3_rodata_B20 == dx && lbl_3_rodata_B20 == dz) {
        fielder->currentVelocity = lbl_3_rodata_B20;
        fielder->distanceFromAutoLocation = lbl_3_rodata_B20;
    } else {
        fielder->desiredMovementDirection2 = ATAN2F(dz, dx);
        fielder->distanceFromAutoLocation = fielderSqrt(dx * dx + dz * dz);
    }

    fielder->goingToAutoLocationInd = 1;
}

// .text:0x0004D20C size:0x978 mapped:0x8068C2A0
void autoMovement1_coverBase(int fielderIndex) {
    return;
}

// .text:0x0004DB84 size:0x90 mapped:0x8068CC18
int fn_3_4DB84(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    f32 dot;

    if (g_Ball.ballVelocityPercent.x == lbl_3_rodata_B20 &&
        g_Ball.ballVelocityPercent.z == lbl_3_rodata_B20) {
        return 0;
    }

    dot = -(g_Ball.ballVelocityPercent.x * g_Ball.AtBat_Contact_BallPos.x)
        - (g_Ball.ballVelocityPercent.z * g_Ball.AtBat_Contact_BallPos.z)
        + g_Ball.ballVelocityPercent.z * fielder->pos.z
        + g_Ball.ballVelocityPercent.x * fielder->pos.x;

    if (dot > lbl_3_rodata_B20) {
        return 1;
    }
    return 0;
}

// .text:0x0004DC14 size:0x5A8 mapped:0x8068CCA8
void bobbleDirection(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    int bestChemIdx = -1;
    int assistMode = 0;
    f32 bestChemDist;
    int j;
    int modeFlag;
    int lowVelocityInd;
    f32 ballVelocity;
    f32 velocityScale;
    s16 baseAngle;
    int elevationAngle;
    int horizAngle;
    f32 elevX, elevY;
    f32 horizX, horizZ;
    f32 speedXZ;

    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD) {
        bestChemDist = chemBobbleMults.chemBobbleMults[0];
        if (g_Ball.ballZoneAwayFromHome >= 3) {
            bestChemDist = chemBobbleMults.chemBobbleMults[1];
        }

        for (j = 0; j < 9; j++) {
            int chem;

            if (j == fielderIndex) {
                continue;
            }

            chem = calculateChemistry(g_GameLogic.teamFielding, fielder->CharID, g_Fielders[j].CharID);
            if (chem < chemThresholds[2]) {
                continue;
            }
            if (fielder->distanceFromEachFielder[j] >= bestChemDist) {
                continue;
            }
            if (fielder->distanceFromEachFielder[j] >= lbl_3_rodata_BA4) {
                continue;
            }

            bestChemIdx = j;
            bestChemDist = fielder->distanceFromEachFielder[j];
        }

        if (bestChemIdx >= 0) {
            playSoundEffect(0x1ab);
            assistMode = (fielder->action != 0) ? 2 : 1;
        }
    }

    modeFlag = (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD);

    ballVelocity = g_Ball.ballVelocity;
    lowVelocityInd = (ballVelocity < lbl_3_data_48C4);
    if (ballVelocity > lbl_3_rodata_B80) {
        ballVelocity = lbl_3_rodata_B80;
    }

    if (g_Ball.hardHitIndicator != 0) {
        velocityScale = ballVelocity * lbl_3_data_5CDC[8 + assistMode];
    } else {
        velocityScale = ballVelocity * lbl_3_data_5CDC[5 + assistMode];
    }

    baseAngle = normalizeAnglebetween_2048And2047(g_Ball.ballTravelAngle + 0x800);

    if (assistMode != 0) {
        f32 dx = g_Fielders[bestChemIdx].pos.x - fielder->pos.x;
        f32 dz = g_Fielders[bestChemIdx].pos.z - fielder->pos.z;
        int angleToPartner = calculateAngleFromCoordinates(dx, dz);

        horizAngle = angleToPartner + RandomInt_Game(0x200) - 0x100;

        if (assistMode == 1) {
            elevationAngle = RandomInt_Game(0x100) + 0x100;
        } else {
            elevationAngle = RandomInt_Game(0x100) + 0x200;
        }
    } else {
        int randOffset;

        if (fielder->catchCentreRightLeftOfBody == 0) {
            elevationAngle = RandomInt_Game_Range(lbl_3_data_48C8[modeFlag][0], lbl_3_data_48C8[modeFlag][1]);
            randOffset = RandomInt_Game_Range(lbl_3_data_48C8[modeFlag][2], lbl_3_data_48C8[modeFlag][3]);
        } else if (lowVelocityInd == 0) {
            elevationAngle = RandomInt_Game_Range(lbl_3_data_48C8[modeFlag][4], lbl_3_data_48C8[modeFlag][5]);
            randOffset = RandomInt_Game_Range(lbl_3_data_48C8[modeFlag][6], lbl_3_data_48C8[modeFlag][7]);
            if (fielder->catchCentreRightLeftOfBody == 1) {
                randOffset = -randOffset;
            }
        } else {
            elevationAngle = RandomInt_Game_Range(lbl_3_data_48C8[modeFlag][8], lbl_3_data_48C8[modeFlag][9]);
            randOffset = RandomInt_Game_Range(lbl_3_data_48C8[modeFlag][10], lbl_3_data_48C8[modeFlag][11]);
            if (fielder->catchCentreRightLeftOfBody == 1) {
                randOffset = -randOffset;
            }
        }

        horizAngle = normalizeAnglebetween_2048And2047(randOffset + baseAngle);
    }

    getComponentsFromSAng(elevationAngle, &elevX, &elevY);
    elevY *= velocityScale;
    getComponentsFromSAng(horizAngle, &horizX, &horizZ);

    speedXZ = elevX * ballVelocity;

    g_Ball.physicsSubstruct.velocity.x = horizX * speedXZ;
    g_Ball.physicsSubstruct.velocity.y = elevY;
    g_Ball.physicsSubstruct.velocity.z = horizZ * speedXZ;
    g_Ball.physicsSubstruct.acceleration.x = lbl_3_rodata_B20;
    g_Ball.physicsSubstruct.acceleration.y = lbl_3_rodata_B20;
    g_Ball.physicsSubstruct.acceleration.z = lbl_3_rodata_B20;

    if (fielder->bobble == 4) {
        if (fielder->onFire == 0) {
            fielder->onFireFacingAngle = radToShortAngle(fielder->desiredMovementDirection);
            fielder->onFire = 1;
            fielder->onFireCountUp = 0;
            fielder->onFireCountdown = specialFielderActionConstants.fireballCountdownArray[0];
            fielder->catchAnimation = 0;
            fielder->isJump = 0;
            fielder->clamberStatus = 0;
            fielder->wallSplatStatus = 0;
            fielder->hitKnockbackCountdown = 0;
        }
    } else {
        fielder->hitKnockbackCountdown = (int)(g_Ball.ballEnergy * lbl_3_data_5CDC[4]);
    }

    fielder->catchAnimation = 0;
    fielder->closingInOnCatchingFlyBall = 0;
    g_FieldingLogic.knockoutFinished = 1;
    g_Ball.ballState = BALL_STATE_LOOSE;
    g_Ball.fielderAboutToGetBall_hasBall = -1;
    g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy = 0;
    g_Ball.warioWaluGarlicIsActive = 0;
    g_Ball.ballIsRollingIndicator = 0;

    if (g_Ball.numFieldersWhoHandledBallDuringPlay < 0xfe) {
        g_Ball.numFieldersWhoHandledBallDuringPlay++;
    } else {
        g_Ball.numFieldersWhoHandledBallDuringPlay = 0xff;
    }

    if (g_Ball.fielderWithBallIndexStored < 0) {
        g_Ball.fielderWithBallIndexStored = fielderIndex;
    }

    if (g_Ball.numFieldersWhoHandledBallDuringPlay == 1) {
        if (foul_checkIfFoul(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z)) {
            g_Ball.bobbleLocation_1fair_2foul = 2;
            if (g_Ball.ballInitialHitDoneInd == 0 && g_Ball.framesOnGroundUntilPickedUp != 0) {
                foulBall();
            }
        } else {
            g_Ball.bobbleLocation_1fair_2foul = 1;
            if (g_Ball.ballInitialHitDoneInd == 0) {
                g_Ball.ballInitialHitDoneInd = 1;
            }
        }
    }

    if (assistMode != 0) {
        playCharacterSound(fielder->CharID, 0);
    } else if (fielder->bobble != 4) {
        playCharacterSound(fielder->CharID, 0xa);
    }

    playSoundEffect(0x16f);
    g_Ball.currentStarSwing = 0;
}

// .text:0x0004E1BC size:0x47C mapped:0x8068D250
void findClosestFieldersToLooseBallAndAssignToGoGetIt(void) {
    InMemFielder* fielder;
    int i;
    int j;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 dx2;
    f32 dz2;
    f32 bestDist = lbl_3_rodata_C24;
    f32 secondDist = bestDist;
    int closestFielders[2];
    s16 covering;

    for (i = 0; i < 9; i++) {
        fielder = &g_Fielders[i];

        dx = fielder->pos.x - g_Ball.physicsSubstruct.futureCoordsAndDist[120].pos.x;
        dz = fielder->pos.z - g_Ball.physicsSubstruct.futureCoordsAndDist[120].pos.z;
        dx2 = dx * dx;
        dz2 = dz * dz;
        dist = dolsqrtf2(dx2 + dz2);

        if (dist < bestDist) {
            secondDist = bestDist;
            closestFielders[1] = closestFielders[0];
            bestDist = dist;
            closestFielders[0] = i;
        } else if (dist < secondDist) {
            secondDist = dist;
            closestFielders[1] = i;
        }
    }

    for (j = 0; j < 2; j++) {
        fielder = &g_Fielders[closestFielders[j]];
        setIntendedLocToInterceptBall(closestFielders[j]);

        if (g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam] != 0) {
            if (closestFielders[j] != -1) {
                fielder->autoMovementFunctionIndex = 18;
                if (autoMovementFunctions[18].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[closestFielders[j]] = autoMovementFunctions[18].code;
                }
                fielder->unknown_writeOnly = 0;
                fielder->fielderVeloAdjustmentCode = 0;
                fielder->unknown_writeOnly_always0 = 0;
                fielder->timeSinceThrowWasCaught = 0;
                fielder->fielderTrackingBallState = 0;
            }
        } else if (j == 0) {
            if (closestFielders[j] != -1) {
                fielder->autoMovementFunctionIndex = 15;
                if (autoMovementFunctions[15].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[closestFielders[j]] = autoMovementFunctions[15].code;
                }
                fielder->unknown_writeOnly = 0;
                fielder->fielderVeloAdjustmentCode = 0;
                fielder->unknown_writeOnly_always0 = 0;
                fielder->timeSinceThrowWasCaught = 0;
                fielder->fielderTrackingBallState = 0;
            }
            g_FieldingLogic.selectedFielder = closestFielders[j];
        } else {
            if (closestFielders[j] != -1) {
                fielder->autoMovementFunctionIndex = 16;
                if (autoMovementFunctions[16].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[closestFielders[j]] = autoMovementFunctions[16].code;
                }
                fielder->unknown_writeOnly = 0;
                fielder->fielderVeloAdjustmentCode = 0;
                fielder->unknown_writeOnly_always0 = 0;
                fielder->timeSinceThrowWasCaught = 0;
                fielder->fielderTrackingBallState = 0;
            }
        }

        covering = fielder->locationResponsibleForCovering;
        if (covering >= 0 && covering <= 5) {
            if (covering <= 3) {
                if (g_FieldingLogic.fielderAssignedLocationIndex[covering] == closestFielders[j]) {
                    g_FieldingLogic.fielderAssignedLocationIndex[covering] = -1;
                    g_FieldingLogic.baseCoveredInd[covering] = 0;
                }
                fielder->locationResponsibleForCovering = -1;
                fielder->isResponsibleForCoveringALocation = 0;

                if (fielder->autoMovementFunctionIndex == 1 && closestFielders[j] != -1) {
                    fielder->autoMovementFunctionIndex = 12;
                    if (autoMovementFunctions[12].code >= 0) {
                        g_FieldingLogic.fielderAutoMovementCode[closestFielders[j]] = autoMovementFunctions[12].code;
                    }
                    fielder->unknown_writeOnly = 0;
                    fielder->fielderVeloAdjustmentCode = 0;
                    fielder->unknown_writeOnly_always0 = 0;
                    fielder->timeSinceThrowWasCaught = 0;
                    fielder->fielderTrackingBallState = 0;
                }
            } else if (covering == 5) {
                fielder->locationResponsibleForCovering = -1;
                g_FieldingLogic.fielderAssignedLocationIndex[4] = -1;
                fielder->isResponsibleForCoveringALocation = 0;
                g_FieldingLogic.playerAtMoundCutoffLocation = 0;

                if (fielder->autoMovementFunctionIndex == 14 && closestFielders[j] != -1) {
                    fielder->autoMovementFunctionIndex = 12;
                    if (autoMovementFunctions[12].code >= 0) {
                        g_FieldingLogic.fielderAutoMovementCode[closestFielders[j]] = autoMovementFunctions[12].code;
                    }
                    fielder->unknown_writeOnly = 0;
                    fielder->fielderVeloAdjustmentCode = 0;
                    fielder->unknown_writeOnly_always0 = 0;
                    fielder->timeSinceThrowWasCaught = 0;
                    fielder->fielderTrackingBallState = 0;
                }
            }
        }

        covering = fielder->locationResponsibleForCovering;
        if (covering >= 7 && covering <= 14) {
            fielder->locationResponsibleForCovering = -1;
            fielder->isResponsibleForCoveringALocation = 0;
        }
    }
}

// .text:0x0004E638 size:0x58C mapped:0x8068D6CC
void checkForAndHandleLooseBalls(void) {
    return;
}

// .text:0x0004EBC4 size:0x404 mapped:0x8068DC58
void aISetFielderWithBallIndex(void) {
    s16 frames;
    int outfielderProblem;
    int bestFielderIndex;
    s16 bestScore;
    s16 secondScore;
    InMemFielder* fielder;
    int i;
    s16 numFramesToGetToAutoLocation;
    u8 catchStrategy;
    int lastFrames;
    int problemFound;

    if (g_FieldingLogic.locationThrownTo < 0) {
        g_Ball.fielderAboutToGetBall_hasBall = -1;
        return;
    }

    if (g_Ball.fielderAboutToGetBall_hasBall >= 0) {
        return;
    }

    frames = g_Ball.matchFramesAndBallAngle.framesAfterReceivingThrow;
    if (frames > 0 && frames < 25) {
        return;
    }

    outfielderProblem = 0;
    if (g_Ball.ballZoneAwayFromHome <= 1 && g_Ball.maxYOfHit <= lbl_3_rodata_B78) {
        outfielderProblem = 1;
    }

    bestFielderIndex = -1;
    bestScore = 0x270f;
    secondScore = 0x270f;
    lastFrames = -1;

    for (i = 0, fielder = g_Fielders; i < 9; i++, fielder++) {
        if (g_FieldingLogic.fielderAutoMovementCode[i] != 1) {
            continue;
        }

        numFramesToGetToAutoLocation = fielder->numFramesToGetToAutoLocation;
        if (numFramesToGetToAutoLocation == -1) {
            if (g_Ball.fielderAboutToGetBall_hasBall == i) {
                g_Ball.fielderAboutToGetBall_hasBall = -1;
            }
            continue;
        }

        catchStrategy = fielder->catchStrategy;
        if (catchStrategy == 1 && i <= 5) {
            if (fielder->distanceFromLandingSpot > lbl_3_rodata_B64) {
                outfielderProblem = 1;
                continue;
            }
        }

        if (i >= 6) {
            if (outfielderProblem != 0) {
                break;
            }
        }

        if (numFramesToGetToAutoLocation < 0) {
            continue;
        }

        lastFrames = numFramesToGetToAutoLocation;
        if (fielder->fielderReadiness != 0) {
            lastFrames = numFramesToGetToAutoLocation + 0x3c;
        } else if (fielder->animatingActionInd != 0) {
            lastFrames = numFramesToGetToAutoLocation + 0x3c;
        }

        if (i == 0 && catchStrategy == 1) {
            if (fielder->distanceFromLandingSpot > fielder->distanceFromHomePlate) {
                lastFrames += 0x1e;
            }
        }

        if (lastFrames < bestScore) {
            bestFielderIndex = i;
            bestScore = (s16)lastFrames;
        } else if (lastFrames < secondScore) {
            secondScore = (s16)lastFrames;
        }
    }

    if (bestFielderIndex < 0) {
        if (g_Ball.fielderAboutToGetBall_hasBall >= 0) {
            g_Ball.ballIsLooseInd_unused = 0;
            g_Ball.looseBall_codeForHowLongUntilSomeoneWillGetIt = 0;
            g_Ball.fielderBeingThrownTo = -1;
        }
        return;
    }

    if (g_Fielders[bestFielderIndex].catchStrategy == 1) {
        if (bestScore < 0x3c && bestScore + 0x3c < secondScore) {
            g_Ball.fielderAboutToGetBall_hasBall = bestFielderIndex;
        }
    }

    if (bestScore < 0x1e) {
        g_Ball.fielderAboutToGetBall_hasBall = bestFielderIndex;
    }

    if (g_Ball.fielderBeingThrownTo != 0) {
        g_Ball.fielderAboutToGetBall_hasBall = bestFielderIndex;
    } else if (g_Fielders[bestFielderIndex].nonCatchFlyBallStratInd == 0) {
        g_Ball.fielderAboutToGetBall_hasBall = bestFielderIndex;
    } else if (lastFrames == bestFielderIndex) {
        g_Ball.fielderAboutToGetBall_hasBall = bestFielderIndex;
    }

    if (g_Fielders[bestFielderIndex].maybeMovementState == 4) {
        if (bestScore < 0x3c) {
            g_Ball.fielderAboutToGetBall_hasBall = bestFielderIndex;
        }
    }

    if (g_Fielders[bestFielderIndex].maybeMovementState == 2 && bestScore < 0x1e) {
        problemFound = 0;
        for (i = 0, fielder = g_Fielders; i < 9; i++, fielder++) {
            if (g_FieldingLogic.fielderAutoMovementCode[i] == 1) {
                if (fielder->catchStrategy == 0 || fielder->nonCatchFlyBallStratInd == 0 ||
                    fielder->maybeMovementState == 0 || fielder->maybeMovementState == 1) {
                    problemFound = 1;
                    break;
                }
            }
        }
        if (!problemFound) {
            g_Ball.fielderAboutToGetBall_hasBall = bestFielderIndex;
        }
    }

    if (g_Ball.fielderAboutToGetBall_hasBall >= 0) {
        g_Ball.ballIsLooseInd_unused = 0;
        g_Ball.looseBall_codeForHowLongUntilSomeoneWillGetIt = 0;
        g_Ball.fielderBeingThrownTo = -1;
    }
}

extern int estimatedThrowFramesBetweenTwoPoints(f32 x1, f32 z1, f32 x2, f32 z2);

// .text:0x0004EFC8 size:0x53C mapped:0x8068E05C
void knockoutRelated_subFn(int fielderIndex, int flag) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    CoordAndDist* futureCoord;
    int frame;
    int startFrame;
    int framesNeeded = 0;
    int bestFrame = 0;
    int found = 0;
    int closeEnough = 0;
    int resultCode = 0;
    f32 bestHeight = lbl_3_rodata_B94;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 speed;
    int travelFrames;

    startFrame = fielder->lockoutDuration - g_Ball.framesSinceHit;
    if (startFrame < 1) {
        startFrame = 1;
    }

    for (frame = startFrame; frame < 360;) {
        futureCoord = &g_Ball.physicsSubstruct.futureCoordsAndDist[frame];

        if (futureCoord->pos.y > lbl_3_rodata_B98) {
            frame += 3;
            continue;
        }

        if (futureCoord->pos.x == fielder->pos.x && futureCoord->pos.z == fielder->pos.z) {
            framesNeeded = 1;
        } else {
            dx = futureCoord->pos.x - fielder->pos.x;
            dz = futureCoord->pos.z - fielder->pos.z;
            dist = fielderSqrt(dx * dx + dz * dz);

            speed = fielder->joggingSpeed;
            if (speed == lbl_3_rodata_B20) {
                speed = lbl_3_rodata_B60;
            }
            travelFrames = (int)(dist / speed);
            framesNeeded = (fielder->maxAccLength_ConstF >> 1) + travelFrames;
        }

        framesNeeded = startFrame + (framesNeeded - 5);

        if (framesNeeded < frame) {
            if (futureCoord->pos.y > lbl_3_rodata_B68) {
                resultCode = 1;
                break;
            }

            if (found == 0 || bestHeight >= futureCoord->pos.y) {
                bestHeight = futureCoord->pos.y;
                bestFrame = frame;
                found = 1;
            } else {
                frame = bestFrame;
                resultCode = 2;
                break;
            }
        } else {
            if (framesNeeded < frame + 30) {
                closeEnough = 1;
            }

            if (found != 0) {
                if (flag == 0) {
                    frame = g_Ball.framesUntilBallHitsGround;
                } else {
                    frame = bestFrame;
                }
                resultCode = 2;
                break;
            }
        }

        frame++;
    }

    if (frame >= 360) {
        frame = 359;
    }

    fielder->framesToGetToBallLandingSpot = frame + g_Ball.framesSinceHit;

    if (resultCode == 2) {
        futureCoord = &g_Ball.physicsSubstruct.futureCoordsAndDist[frame];
        if (futureCoord->pos.y > lbl_3_rodata_B68) {
            resultCode = 1;
        }
    }

    if (resultCode == 3 && closeEnough == 0) {
        resultCode = 4;
    }

    fielder->catchStrategy = resultCode;
    fielder->cantCatchFlyBallInd = (resultCode == 1 || resultCode == 2) ? 0 : 1;

    {
        int landingFrame = fielder->framesToGetToBallLandingSpot;
        f32 lx = g_Ball.physicsSubstruct.futureCoordsAndDist[landingFrame].pos.x;
        f32 lz = g_Ball.physicsSubstruct.futureCoordsAndDist[landingFrame].pos.z;
        f32 ddx = g_Ball.landingSpotLocation.x - lx;
        f32 ddz = g_Ball.landingSpotLocation.z - lz;
        f32 landingDist = fielderSqrt(ddx * ddx + ddz * ddz);

        if (landingDist >= lbl_3_rodata_B78 || resultCode != 1) {
            fielder->nonCatchFlyBallStratInd = 1;
        } else {
            fielder->nonCatchFlyBallStratInd = 0;
        }
    }

    if (fielder->nonCatchFlyBallStratInd == 0) {
        if (framesNeeded + 30 < fielder->framesToGetToBallLandingSpot) {
            g_FieldingLogic.fieldersWhoCanCatchBall_bitIndicators |= (1 << fielderIndex);
        }
    } else if (resultCode == 1) {
        int landingFrame = fielder->framesToGetToBallLandingSpot;
        f32 lx = g_Ball.physicsSubstruct.futureCoordsAndDist[landingFrame].pos.x;
        f32 lz = g_Ball.physicsSubstruct.futureCoordsAndDist[landingFrame].pos.z;
        int throwFrames = estimatedThrowFramesBetweenTwoPoints(
            lx, lz, base_MoundCoordinates[1].x, base_MoundCoordinates[1].z);

        if ((&g_RunningLogic._04)[5] + 30 > landingFrame + throwFrames + 60) {
            g_FieldingLogic.fieldersWhoCanCatchBall_bitIndicators |= (1 << fielderIndex);
        }
    }
}

// .text:0x0004F504 size:0x630 mapped:0x8068E598
void setCatcherCatchStrategy_distToLandingSpot(void) {
    return;
}

// .text:0x0004FB34 size:0xD64 mapped:0x8068EBC8
void setFielderCatchStrategy_calcFramesToGetToDropSpot(void) {
    return;
}

// .text:0x00050898 size:0x388 mapped:0x8068F92C
int fn_3_50898(int fielderIndex, f32* outX, f32* outZ) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    int frame;
    int angle;
    int i;

    frame = (fielder->framesToGetToBallLandingSpot - g_Ball.framesSinceHit) + 1;
    angle = calculateAngleFromCoordinates(g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.x,
                                          g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.z);

    if (getDifferenceInAngle(angle, fielder->playerAngleFromHome) < specialFielderActionConstants._00[27]) {
        return 0;
    }

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        goto scanFutureCoords;
    }

    if (fielderIndex <= 5) {
        if ((fielderIndex == 3 && angle > fielder->playerAngleFromHome) ||
            (fielderIndex == 5 && angle < fielder->playerAngleFromHome)) {
            *outX = fielder->xPos5mAwayFromBallsCollisionSpotOnWall;
            *outZ = fielder->pos.z;
            return 1;
        }

        i = frame + lbl_3_data_48A4[0][fielder->AILevel3Weak0Powerful];
        *outX = g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.x;
        *outZ = g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z;
        return 1;
    }

    if (fielderIndex == 7) {
    scanFutureCoords:
        for (i = 60; i < 240; i += 5) {
            if (g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z > fielder->pos.z) {
                break;
            }
        }

        if (i >= 240) {
            return 0;
        }

        *outX = g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.x;
        *outZ = g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z;
        return 1;
    }

    if ((fielderIndex == 6 && fielder->playerAngleFromHome > angle) ||
        (fielderIndex == 8 && fielder->playerAngleFromHome < angle)) {
        for (i = 60; i < 240; i += 5) {
            if (g_Ball.physicsSubstruct.futureCoordsAndDist[i].dist > fielder->distanceFromHomePlate) {
                break;
            }
        }

        if (i >= 240) {
            return 0;
        }

        *outX = g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.x;
        *outZ = g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z;
        return 1;
    }

    i = frame + lbl_3_data_48A4[1][fielder->AILevel3Weak0Powerful];
    *outX = g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.x;
    *outZ = g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z;
    return 1;
}

// .text:0x00050C20 size:0x1B8 mapped:0x8068FCB4
void fielderMovement_adjustPlaceToStandForBallBouncingOffWall(int fielderIndex, f32* outX, f32* outZ) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    f32 dx = fielder->xPos5mAwayFromBallsCollisionSpotOnWall - fielder->pos.x;
    f32 dz = fielder->zPos5mAwayFromBallsCollisionSpotOnWall - fielder->pos.z;
    int angle = calculateAngleFromCoordinates(dx, dz);

    if (fielderIndex == 7) {
        if (angle > 0x200 && angle < 0x600) {
            *outX = fielder->pos.x;
            *outZ = fielder->zPos5mAwayFromBallsCollisionSpotOnWall;
        } else {
            *outX = fielder->xPos5mAwayFromBallsCollisionSpotOnWall;
            *outZ = fielder->pos.z;
        }
        fielder->aiDistToStandFromWallCollision = _0x18aArray[fielder->AILevel3Weak0Powerful];
    } else if (fielderIndex == 8) {
        if (angle > 0x100 && angle < 0x600) {
            f32 xOverD = fielder->pos.x / fielder->distanceFromHomePlate;
            f32 zOverD = fielder->pos.z / fielder->distanceFromHomePlate;
            *outX = xOverD * (lbl_3_rodata_BA0 + fielder->distanceFromHomePlate);
            *outZ = zOverD * (lbl_3_rodata_BA0 + fielder->distanceFromHomePlate);
        } else {
            *outX = fielder->xPos5mAwayFromBallsCollisionSpotOnWall;
            *outZ = fielder->pos.z;
        }
        fielder->aiDistToStandFromWallCollision = _0x18aArray[fielder->AILevel3Weak0Powerful];
    } else {
        if (angle > 0x200 && angle < 0x700) {
            f32 xOverD = fielder->pos.x / fielder->distanceFromHomePlate;
            f32 zOverD = fielder->pos.z / fielder->distanceFromHomePlate;
            *outX = xOverD * (lbl_3_rodata_BA0 + fielder->distanceFromHomePlate);
            *outZ = zOverD * (lbl_3_rodata_BA0 + fielder->distanceFromHomePlate);
        } else {
            *outX = fielder->xPos5mAwayFromBallsCollisionSpotOnWall;
            *outZ = fielder->pos.z;
        }
        fielder->aiDistToStandFromWallCollision = _0x18aArray[fielder->AILevel3Weak0Powerful];
    }
}

// .text:0x00050DD8 size:0x448 mapped:0x8068FE6C
int fn_3_50DD8(int fielderIndex, f32* outX, f32* outZ, int flag) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    f32 dx;
    f32 dz;
    f32 dist;
    f32 tempX;
    f32 tempZ;

    if (g_d_GameSettings.minigamesEnabled) {
        return 0;
    }

    if (fielderIndex <= 2 || fielderIndex == 4) {
        return 0;
    }

    if (g_Ball.someCollisionInd) {
        fielder->aiDistToStandFromWallCollision = 0;
        return 0;
    }

    if (flag == 0) {
        fielder->xPos5mAwayFromBallsCollisionSpotOnWall = *outX;
        fielder->zPos5mAwayFromBallsCollisionSpotOnWall = *outZ;

        dx = fielder->pos.x - fielder->xPos5mAwayFromBallsCollisionSpotOnWall;
        dz = fielder->pos.z - fielder->zPos5mAwayFromBallsCollisionSpotOnWall;
        dist = fielderSqrt(dx * dx + dz * dz);

        if (dist < fielderActionConstants[31]) {
            return 0;
        }

        if (fn_3_50898(fielderIndex, &tempX, &tempZ)) {
            *outX = tempX;
            *outZ = tempZ;
        }

        fielder->aiDistToStandFromWallCollision = 1;
        fielder->_0188 = 30;
        return 1;
    }

    if (!fielder->_020E) {
        if (fielder->aiDistToStandFromWallCollision > lbl_3_data_48A4[2][fielder->AILevel3Weak0Powerful]) {
            fielder->_020E = 1;
        } else {
            dx = fielder->maybeTargetPosX - fielder->pos.x;
            dz = fielder->maybeTargetPosZ - fielder->pos.z;
            dist = fielderSqrt(dx * dx + dz * dz);

            if (dist < fielderActionConstants[32]) {
                fielder->_020E = 1;
            }
        }

        *outX = fielder->maybeTargetPosX;
        *outZ = fielder->maybeTargetPosZ;
        return 1;
    }

    dx = fielder->xPos5mAwayFromBallsCollisionSpotOnWall - fielder->maybeTargetPosX;
    dz = fielder->zPos5mAwayFromBallsCollisionSpotOnWall - fielder->maybeTargetPosZ;
    fielder->_0188--;

    if (fielder->_0188 <= 0) {
        *outX = fielder->xPos5mAwayFromBallsCollisionSpotOnWall;
        *outZ = fielder->zPos5mAwayFromBallsCollisionSpotOnWall;
        fielder->aiDistToStandFromWallCollision = 0;
    } else {
        f32 diff = (f64)fielder->_0188 - lbl_3_rodata_B50;
        f32 t = lbl_3_rodata_B60 / diff;
        *outX = fielder->maybeTargetPosX + dx * t;
        *outZ = fielder->maybeTargetPosZ + dz * t;
    }

    return 1;
}

extern f32 lbl_3_data_4B98;
extern s16 initialSprintCharge_10[6];

// .text:0x00051220 size:0x42C mapped:0x806902B4
void updateSprintPointers(void) {
    InMemFielder* fielder;

    if (g_FieldingLogic.dashPtr->sprintingState != 0) {
        if (g_FieldingLogic.dashPtr->framesSinceLastDashInput < 0x7ffe) {
            g_FieldingLogic.dashPtr->framesSinceLastDashInput++;
        } else {
            g_FieldingLogic.dashPtr->framesSinceLastDashInput = 0x7fff;
        }

        if (g_FieldingLogic.dashPtr->sprintLengthInFrames < 0x7ffe) {
            g_FieldingLogic.dashPtr->sprintLengthInFrames++;
        } else {
            g_FieldingLogic.dashPtr->sprintLengthInFrames = 0x7fff;
        }

        g_FieldingLogic.dashPtr->sprintLengthInFramesStored++;

        if (g_FieldingLogic.dashPtr->sprintingState == 4 || g_FieldingLogic.dashPtr->sprintingState == 3) {
            g_FieldingLogic.dashPtr->postSprintSlowdownTimer--;

            if (g_FieldingLogic.dashPtr->postSprintSlowdownTimer == 0) {
                g_FieldingLogic.dashPtr->sprintingState = 0;
                g_FieldingLogic.dashPtr->framesSinceLastDashInput = -1;
                g_FieldingLogic.dashPtr->sprintLengthInFrames = -1;
                g_FieldingLogic.dashPtr->dashingFielderIndex = -1;
                g_FieldingLogic.dashPtr->sprintSpeedMultiplier = lbl_3_rodata_B60;
            } else {
                g_FieldingLogic.dashPtr->sprintSpeedMultiplier =
                    (g_FieldingLogic.dashPtr->sprintSpeedMultiplier - lbl_3_rodata_B60) *
                    (lbl_3_rodata_B60 - lbl_3_rodata_B60 / (f32) g_FieldingLogic.dashPtr->postSprintSlowdownTimer);
                g_FieldingLogic.dashPtr->sprintSpeedMultiplier += lbl_3_rodata_B60;
            }

            return;
        }

        if (g_FieldingLogic.dashPtr->framesSinceLastDashInput == 1) {
            g_FieldingLogic.dashPtr->numberOfDashInputs++;
            g_FieldingLogic.dashPtr->chargeLevel += initialSprintCharge_10[0];

            if (g_FieldingLogic.dashPtr->chargeLevel >= initialSprintCharge_10[1]) {
                g_FieldingLogic.dashPtr->chargeLevel = initialSprintCharge_10[1];
                g_FieldingLogic.dashPtr->sprintingState = 2;

                if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE ||
                    g_Practice.practiceType_2 == PRACTICE_TYPE_FIELDING ||
                    g_Practice.practiceLevel == 2) {
                    g_Practice._1CB = 1;
                }
            }
        } else if (g_FieldingLogic.dashPtr->framesSinceLastDashInput >= initialSprintCharge_10[2]) {
            fielder = &g_Fielders[g_FieldingLogic.dashPtr->dashingFielderIndex];

            if (fielder->movementAngle == -1) {
                g_FieldingLogic.dashPtr->sprintingState = 4;
                g_FieldingLogic.dashPtr->postSprintSlowdownTimer = initialSprintCharge_10[4];
                *(f32*) &g_FieldingLogic.dashPtr->const0 = fielder->xMovementDir;
                *(f32*) &g_FieldingLogic.dashPtr->const_00 = fielder->zMovementDir;
            } else {
                g_FieldingLogic.dashPtr->sprintingState = 3;
                g_FieldingLogic.dashPtr->postSprintSlowdownTimer = initialSprintCharge_10[5];
            }

            return;
        }

        g_FieldingLogic.dashPtr->sprintSpeedMultiplier =
            (f32) g_FieldingLogic.dashPtr->chargeLevel / (f32) initialSprintCharge_10[1] * lbl_3_data_4B98 +
            lbl_3_rodata_B60;

        return;
    }

    if (g_FieldingLogic.dashPtr->framesSinceLastDashInput < 0) {
        return;
    }

    if (g_FieldingLogic.dashPtr->sprintLengthInFrames < 0) {
        g_FieldingLogic.dashPtr->sprintLengthInFrames = 0;
        g_FieldingLogic.dashPtr->chargeLevel = 0;
        g_FieldingLogic.dashPtr->dashingFielderIndex = -1;
        g_FieldingLogic.dashPtr->numberOfDashInputs = 0;
    }

    if (g_FieldingLogic.dashPtr->framesSinceLastDashInput < 0x7ffe) {
        g_FieldingLogic.dashPtr->framesSinceLastDashInput++;
    } else {
        g_FieldingLogic.dashPtr->framesSinceLastDashInput = 0x7fff;
    }

    if (g_FieldingLogic.dashPtr->sprintLengthInFrames < 0x7ffe) {
        g_FieldingLogic.dashPtr->sprintLengthInFrames++;
    } else {
        g_FieldingLogic.dashPtr->sprintLengthInFrames = 0x7fff;
    }

    if (g_FieldingLogic.dashPtr->framesSinceLastDashInput < initialSprintCharge_10[2]) {
        if (g_FieldingLogic.dashPtr->framesSinceLastDashInput == 1) {
            g_FieldingLogic.dashPtr->numberOfDashInputs++;
        }

        if (g_FieldingLogic.dashPtr->numberOfDashInputs < initialSprintCharge_10[3]) {
            return;
        }

        if (g_d_GameSettings.minigamesEnabled) {
            g_FieldingLogic.dashPtr->dashingFielderIndex = g_Minigame.minigameRelatedIndex;
        } else {
            g_FieldingLogic.dashPtr->dashingFielderIndex = g_FieldingLogic.selectedFielder;
        }

        g_FieldingLogic.dashPtr->sprintLengthInFramesStored = 0;
        g_FieldingLogic.dashPtr->sprintingState = 1;
        g_FieldingLogic.dashPtr->sprintSpeedMultiplier = lbl_3_rodata_B60;
        g_FieldingLogic.dashPtr->framesSinceLastDashInput = -1;
        g_FieldingLogic.dashPtr->chargeLevel = initialSprintCharge_10[0];
    } else {
        g_FieldingLogic.dashPtr->framesSinceLastDashInput = -1;
        g_FieldingLogic.dashPtr->sprintLengthInFrames = -1;
        g_FieldingLogic.dashPtr->dashingFielderIndex = -1;
    }
}

// .text:0x0005164C size:0x14C mapped:0x806906E0
int adjustPlayerPosOutsideFoulLine(int fielderIndex, VecXYZ* out) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    f32 z = fielder->pos.z + fielder->velocityZ;
    f32 x = fielder->pos.x + fielder->velocityX;
    f32 moundZ;
    f32 moundX;
    f32 negX;
    f32 d;
    int ret = 0;

    if (x > lbl_3_rodata_B20) {
        if (x > z) {
            f32 half = (x - z) * lbl_3_rodata_B80;
            x = z + half;
            z = x;
            ret = 2;
        }
    } else {
        negX = -x;
        if (negX > z) {
            f32 half = (negX - z) * lbl_3_rodata_B80;
            z = z + half;
            x = -z;
            ret = 2;
        }
    }

    moundZ = base_MoundCoordinates[2].z;
    d = z - moundZ;
    if (d > x) {
        goto skipAdjust;
    }
    negX = -x;
    if (d > negX) {
        goto skipAdjust;
    }

    if (x > lbl_3_rodata_B20) {
        f32 half;
        d = moundZ - z;
        half = (x - d) * lbl_3_rodata_B80;
        x = d + half;
        z = -x + moundZ;
        ret = 2;
    } else {
        f32 half;
        d = moundZ - z;
        half = (negX - d) * lbl_3_rodata_B80;
        x = -d - half;
        z = x + moundZ;
        ret = 2;
    }

skipAdjust:
    moundX = base_MoundCoordinates[2].x;
    if (z <= moundX) {
        return 1;
    }

    out->x = x;
    out->z = z;
    return ret;
}

// .text:0x00051798 size:0x658 mapped:0x8069082C
int updateFielderPosition_checkFielderCollision(int fielderIndex, VecXYZ* out) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    VecSrcDst inVec;
    CollisionStruct collision;
    u32 type;
    f32 dirX, dirZ;
    f32 magnitude;
    f32 unitNormalX, unitNormalZ;
    f32 weightedNormalX, weightedNormalZ;
    f32 angle1, angle2, diff, cosDiff;
    f32 pushRadius, collisionDist;
    f32 baseX, baseZ, offsetX, offsetZ;

    if (fielder->currentVelocity == lbl_3_rodata_B20) {
        return 0;
    }

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && g_GameLogic.gameStatus == GAME_STATUS_AT_BAT) {
        u32 ret = adjustPlayerPosOutsideFoulLine(fielderIndex, out);
        if (ret != 0) {
            return ret;
        }
    }

    if (!g_d_GameSettings.minigamesEnabled && fielder->distanceToBases[0] < lbl_3_rodata_C84 &&
        foul_checkIfFoul(fielder->pos.x, fielder->pos.z) == 0) {
        return 0;
    }

    if (fielder->_01FB != 0) {
        return 0;
    }

    if (foul_checkIfFoul(fielder->pos.x, fielder->pos.z) != 0 ||
        g_Minigame.GameMode_MiniGame == MINI_GAME_ID_STAR_DASH ||
        g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        inVec.src.x = fielder->pos.x + fielder->velocityX;
        inVec.src.y = lbl_3_rodata_C88;
        inVec.src.z = fielder->pos.z + fielder->velocityZ;
        inVec.dst.x = inVec.src.x;
        inVec.dst.y = lbl_3_rodata_BA0;
        inVec.dst.z = inVec.src.z;
        type = checkCollision(&inVec, &collision, 0, 0) & 0x7F;
        if (type == BALL_COLLISION_TYPE_WALL || type == BALL_COLLISION_TYPE_STRUCTURE ||
            type == BALL_COLLISION_TYPE_PIT_WALL || type == BALL_COLLISION_TYPE_PIT ||
            type == BALL_COLLISION_TYPE_UNCLIMBABLE_WALL) {
            return 1;
        }

        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_STAR_DASH && fn_3_1379A0(fielderIndex) != 0) {
            memcpy(out, fielder, sizeof(VecXYZ));
            return 1;
        }
    }

    dirX = fielder->velocityX / fielder->currentVelocity;
    dirZ = fielder->velocityZ / fielder->currentVelocity;
    inVec.src.x = fielder->pos.x;
    inVec.src.y = lbl_3_rodata_BB4;
    inVec.src.z = fielder->pos.z;
    inVec.dst.x = fielder->pos.x + dirX;
    inVec.dst.y = lbl_3_rodata_BB4;
    inVec.dst.z = fielder->pos.z + dirZ;
    type = checkCollision(&inVec, &collision, 0, 0) & 0x7F;
    if (type != BALL_COLLISION_TYPE_WALL && type != BALL_COLLISION_TYPE_UNCLIMBABLE_WALL) {
        return 0;
    }

    magnitude = fielderSqrt(SQ(collision.normal.x) + SQ(collision.normal.z));
    unitNormalX = collision.normal.x / magnitude;
    unitNormalZ = collision.normal.z / magnitude;
    weightedNormalX = unitNormalX * lbl_3_data_476C[fielder->Weight];
    weightedNormalZ = unitNormalZ * lbl_3_data_476C[fielder->Weight];
    angle1 = game_atan2(-weightedNormalX, -weightedNormalZ);
    angle2 = game_atan2(dirX, dirZ);
    diff = radianAngleReduction(angle1 - angle2);
    cosDiff = (f32)cos(diff);
    pushRadius = lbl_3_data_476C[fielder->Weight] / cosDiff;
    if (fielder->jumpDiveStateRelated == 2) {
        pushRadius = (f32)barrelCollisionHitboxes[fielder->CharID];
    }

    collisionDist = fielderSqrt(SQ(fielder->pos.x - collision.position.x) + SQ(fielder->pos.z - collision.position.z));
    if (collisionDist >= pushRadius) {
        return 0;
    }

    baseX = fielder->pos.x + fielder->velocityX;
    baseZ = fielder->pos.z + fielder->velocityZ;
    offsetX = lbl_3_rodata_B78 * unitNormalX;
    offsetZ = lbl_3_rodata_B78 * unitNormalZ;
    inVec.src.x = baseX + offsetX;
    inVec.src.z = baseZ + offsetZ;
    inVec.dst.x = baseX - offsetX;
    inVec.dst.z = baseZ - offsetZ;
    type = checkCollision(&inVec, &collision, 1, 0);
    if (type == BALL_COLLISION_TYPE_NONE) {
        return 1;
    }

    out->x = weightedNormalX * lbl_3_data_476C[fielder->Weight] + collision.position.x;
    out->z = weightedNormalZ * lbl_3_data_476C[fielder->Weight] + collision.position.z;
    return 2;
}

extern const f32 lbl_3_rodata_BD0;
extern const f32 lbl_3_rodata_C70;
extern const f32 lbl_3_rodata_C74;
extern const f32 lbl_3_rodata_C78;
extern const f32 lbl_3_rodata_C7C;
extern const f32 lbl_3_rodata_C80;

// .text:0x00051DF0 size:0x294 mapped:0x80690E84
int setZoneAwayFromHome(f32 x, f32 z) {
    f32 xSq;
    f32 distFromHome;
    f32 dist;
    f32 dz;

    if (lbl_3_rodata_BD0 + (x - z) > lbl_3_rodata_B20 &&
        lbl_3_rodata_BD0 + (-x - z) > lbl_3_rodata_B20) {
        return 0;
    }

    xSq = x * x;
    distFromHome = fielderSqrt(xSq + z * z);
    if (distFromHome < lbl_3_rodata_C70) {
        return 1;
    }

    dz = z - lbl_3_rodata_C74;
    dist = fielderSqrt(xSq + dz * dz);
    if (dist < lbl_3_rodata_C78) {
        return 1;
    }
    if (dist < lbl_3_rodata_C7C) {
        return 2;
    }
    if (dist < lbl_3_rodata_C80) {
        return 3;
    }
    return 4;
}

// .text:0x00052084 size:0x25C mapped:0x80691118
f32 fn_3_52084(int fielderIndex, f32 x, f32 z) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    f32 dx;
    f32 dz;
    f32 dot;
    f32 perpDistSq;

    if (fielder->currentVelocity < lbl_3_rodata_B48) {
        f32 sqx;
        f32 sqz;
        dx = fielder->pos.x - x;
        dz = fielder->pos.z - z;
        sqx = dx * dx;
        sqz = dz * dz;
        return fielderSqrt(sqx + sqz);
    }

    dx = x - fielder->pos.x;
    dz = z - fielder->pos.z;
    dot = fielder->xMovementDir * dx + fielder->zMovementDir * dz;
    perpDistSq = (dx * dx + dz * dz) - dot * dot;

    if (!(perpDistSq < lbl_3_rodata_B20)) {
        return fielderSqrt(perpDistSq);
    }
}

extern const f64 lbl_3_rodata_B50;

// .text:0x000522E0 size:0x280 mapped:0x80691374
void calculateMinDiveDistAndEndingCoords(int fielderIndex, int numFrames, f32 dirX, f32 dirZ,
                                          f32* outX, f32* outZ, f32* outDist) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    f32 totalDist = lbl_3_rodata_B20;
    f32 speed = fielder->currentVelocity;
    f32 normDirX;
    f32 normDirZ;
    s16 diveAngle;
    s16 angleDiff;
    int i;

    if (dirX == lbl_3_rodata_B20 && dirZ == lbl_3_rodata_B20) {
        *outX = fielder->pos.x;
        *outZ = fielder->pos.z;
        *outDist = totalDist;
        return;
    }

    totalDist = fielderSqrt(dirX * dirX + dirZ * dirZ);

    normDirX = dirX / totalDist;
    normDirZ = dirZ / totalDist;

    diveAngle = calculateAngleFromCoordinates(normDirX, normDirZ);

    if (!(fielder->currentVelocity < lbl_3_rodata_B7C)) {
        if (fielder->runningAngle >= 0) {
            angleDiff = getDifferenceInAngle(diveAngle, fielder->runningAngle);
            if (angleDiff > 0x2A8) {
                speed = lbl_3_rodata_B20;
            }
        }
    }

    for (i = 0; i <= fielder->maxAccLength_ConstF; i++) {
        speed += fielder->runningAccelerationFactor;
        if (speed > fielder->joggingSpeed) {
            totalDist += fielder->joggingSpeed;
            break;
        }
        totalDist += speed;
    }

    totalDist += (f32)(numFrames - (i + 1)) * fielder->joggingSpeed;

    *outDist = totalDist;
    *outX = fielder->pos.x + normDirX * totalDist;
    *outZ = fielder->pos.z + normDirZ * totalDist;
}

// .text:0x00052560 size:0x17C mapped:0x806915F4
int fRunningTimeToDestinationPlus7(int fielderIndex, f32 x, f32 z) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    f32 dx;
    f32 dz;
    f32 dxSq;
    f32 dzSq;
    f32 dist;
    u32 halfAcc;
    f32 speed;

    if (x == fielder->pos.x && z == fielder->pos.z) {
        return 1;
    }

    dx = x - fielder->pos.x;
    dz = z - fielder->pos.z;
    dxSq = dx * dx;
    dzSq = dz * dz;
    dist = fielderSqrt(dxSq + dzSq);
    halfAcc = (u32)fielder->maxAccLength_ConstF >> 1;

    if (lbl_3_rodata_B20 == fielder->joggingSpeed) {
        speed = lbl_3_rodata_B60;
    } else {
        speed = fielder->joggingSpeed;
    }

    return (int)halfAcc + (int)(dist / speed);
}

// .text:0x000526DC size:0x870 mapped:0x80691770
void setFielderVelocity(void) {
    return;
}

// .text:0x00052F4C size:0x1A0 mapped:0x80691FE0
void setFielderAutoCoords(int fielderIndex, f32 x, f32 z) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    f32 dx;
    f32 dz;

    fielder->IntendedLocation.x = x;
    fielder->IntendedLocation.z = z;

    dx = x - fielder->pos.x;
    dz = z - fielder->pos.z;

    if (lbl_3_rodata_B20 == dx && lbl_3_rodata_B20 == dz) {
        fielder->currentVelocity = lbl_3_rodata_B20;
        fielder->distanceFromAutoLocation = lbl_3_rodata_B20;
    } else {
        fielder->desiredMovementDirection2 = ATAN2F(dz, dx);
        fielder->distanceFromAutoLocation = fielderSqrt(dx * dx + dz * dz);
    }

    fielder->goingToAutoLocationInd = 1;
}

// .text:0x000530EC size:0x44 mapped:0x80692180
void fn_3_530EC(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];

    fielder->IntendedLocation.x = fielder->pos.x;
    fielder->IntendedLocation.y = fielder->pos.y;
    fielder->IntendedLocation.z = fielder->pos.z;
    fielder->velocityX = lbl_3_rodata_B20;
    fielder->velocityZ = lbl_3_rodata_B20;
    fielder->currentVelocity = lbl_3_rodata_B20;
    fielder->distanceFromAutoLocation = lbl_3_rodata_B20;
}

// .text:0x00053130 size:0x5FC mapped:0x806921C4
int updateFielderPositionAndVelocityForSpecialActions(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    s8 idx;
    void* animPtr = *(void**)(hugeAnimStruct + 0x2c74);

    if (g_d_GameSettings.minigamesEnabled) {
        idx = (s8)g_Minigame.minigameControlStruct[1].aIStrength[fielderIndex];
        animPtr = *(void**)(hugeAnimStruct + 0x2c50 + idx * 4);
    }

    if (fielder->autoMovementFunctionIndex == 0xc && animPtr != NULL) {
        s16 val = *(s16*)((u8*)animPtr + 0x62);
        if (val >= 0x11 && val <= 0x1c) {
            return 2;
        }
    }

    if (fielder->onFire) {
        fielderOnFirePosAndVelo(fielderIndex);
        return 2;
    }

    if (fielder->knockoutStatus) {
        knockOut_setPosAndVelo(fielderIndex);
        return 2;
    }

    if (fielder->bodyCheckResult) {
        fielderBodyCheck_setStatus_Pos_Velo();
        return 2;
    }

    if (fielder->catchAnimation == 0 && fielder->autoCatch0_noCatchAnimationOnly1 != 0) {
        if (fielder->jumpDiveStateRelated == 2 && fielder->animatingActionInd != 0) {
            return 2;
        }
        fielder->autoCatch0_noCatchAnimationOnly1 = 0;
    } else if (fielder->jumpDiveStateRelated == 2 && fielder->animatingActionInd != 0) {
        return 2;
    }

    if (fielder->catchAnimation == 0 && fielder->runningCatchCountDown != 0) {
        int collided;
        VecXYZ scratch;

        fielder->fielderVelocityDuringAction.x *= lbl_3_rodata_B28;
        fielder->fielderVelocityDuringAction.z *= lbl_3_rodata_B28;
        fielder->velocityX = fielder->fielderVelocityDuringAction.x;
        fielder->velocityZ = fielder->fielderVelocityDuringAction.z;

        fielder->currentVelocity = dolsqrtf2(fielder->velocityX * fielder->velocityX + fielder->velocityZ * fielder->velocityZ);

        collided = updateFielderPosition_checkFielderCollision(fielderIndex, &scratch);
        if (collided) {
            fielder->pos.x = fielder->posXLastFrame;
            fielder->pos.z = fielder->posZLastFrame;
            fielder->currentVelocity = lbl_3_rodata_B20;
            fielder->velocityX = lbl_3_rodata_B20;
            fielder->velocityZ = lbl_3_rodata_B20;
        } else {
            fielder->pos.x += fielder->velocityX;
            fielder->pos.z += fielder->velocityZ;
        }

        fielder->IntendedLocation.x = fielder->pos.x;
        fielder->IntendedLocation.z = fielder->pos.z;
        fielder->unused_jumpActiveOrRunningCatchRelated = 1;
        return 2;
    }

    if (g_Ball.unknown_always0) {
        return 2;
    }

    if (fielder->wallJumpStatus >= 3) {
        if (fielder->wallJumpStatus == 3) {
            fielder->wallActionVelo.x *= fielderActionConstants[14];
            fielder->wallActionVelo.z *= fielderActionConstants[14];
            fielder->pos.x += fielder->wallActionVelo.x;
            fielder->pos.z += fielder->wallActionVelo.z;
            fielder->IntendedLocation.x = fielder->pos.x;
            fielder->IntendedLocation.z = fielder->pos.z;
            fielder->unused_jumpActiveOrRunningCatchRelated = 1;
        } else if (fielder->wallJumpStatus == 4) {
            fielder->currentVelocity = lbl_3_rodata_B20;
            fielder->wallActionCountDown--;
            if (fielder->wallActionCountDown == 0) {
                fielder->wallJumpStatus = 0;
            }
        }
        return 1;
    }

    if (fielder->clamberStatus != 0) {
        fielder->wjRelated = 0;

        if (fielder->clamberStatus == 1) {
            f64 countdown = (f64)fielder->specialActionCountdown;

            fielder->pos.x += (fielder->wallActionLocationX - fielder->pos.x) / countdown;
            fielder->pos.z += (fielder->wallactionLocationZ - fielder->pos.z) / countdown;
            fielder->wallActionVelo.y -= fielderActionConstants[18];
            fielder->wallActionCurrentHeight += fielder->wallActionVelo.y;
            if (fielder->wallActionCurrentHeight < lbl_3_rodata_B20) {
                fielder->wallActionCurrentHeight = lbl_3_rodata_B20;
            }
            fielder->specialActionCountdown--;
            if (fielder->specialActionCountdown <= 0) {
                fielder->clamberStatus = 2;
            }
        } else if (fielder->clamberStatus == 2) {
            setClamberPos(fielderIndex);
            fielder->specialActionCountdown = 0;
        } else {
            clamberJumpOffWall(fielderIndex);
            return 1;
        }

        fielder->velocityX = fielder->pos.x - fielder->posXLastFrame;
        fielder->velocityZ = fielder->pos.z - fielder->posZLastFrame;
        return 1;
    }

    if (fielder->wallSplatStatus != 0) {
        wallSplat_setPosAndVelo(fielderIndex);
        return 1;
    }

    if (fielder->isJump != 0) {
        jumpSetPosAndVelo(fielderIndex);
        return 1;
    }

    if (fielder->hitKnockbackCountdown != 0) {
        return 2;
    }

    if (fielder->stunFramesOnFireBall != 0) {
        return 2;
    }

    if (g_Minigame.GameMode_MiniGame == 5) {
        if (*((u8*)&g_Minigame + 0x1c9a + idx) != 0) {
            return 2;
        }
    } else if (g_Minigame.GameMode_MiniGame == 6) {
        u8 stunType = *((u8*)&g_Minigame + 0x1d6e + idx);
        if (stunType == 1 || stunType == 2) {
            return 2;
        }
    }

    if (g_Minigame.GameMode_MiniGame == 5 || g_Minigame.GameMode_MiniGame == 6) {
        return 0;
    }

    return fielder->lockoutDuration < g_Ball.framesSinceHit;
}

// .text:0x0005372C size:0x7BC mapped:0x806927C0
void setStandingOnBaseVariables(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    s16 loc = fielder->locationResponsibleForCovering;
    f32 dist;
    f32 threshold;

    if (loc >= 0 && loc <= 3) {
        f32 dx = base_MoundCoordinates[loc].x - fielder->pos.x;
        f32 dz = base_MoundCoordinates[loc].z - fielder->pos.z;
        f32 sqx = dx * dx;
        f32 sqz = dz * dz;
        dist = fielderSqrt(sqx + sqz);

        threshold = thresholdToBeConsideredCoveringBase_ByWeight[fielder->Weight];
        if (threshold > dist) {
            g_FieldingLogic.baseCoveredInd[loc] = 1;
            fielder->baseCurrentlyOn = loc;
            if (fielderIndex == 0 && fielder->pitcherHeadingToCover1stOr3rd == 1) {
                fielder->pitcherHeadingToCover1stOr3rd = 0;
            }
        }

        if (g_Ball.fielderWBallIndex == fielderIndex) {
            s16 otherIdx = g_FieldingLogic.fielderAssignedLocationIndex[loc];
            if (otherIdx != fielderIndex && otherIdx >= 0 && g_FieldingLogic.baseCoveredInd[loc] != 0) {
                if (loc >= 0 && loc <= 3) {
                    if (otherIdx == fielderIndex) {
                        g_FieldingLogic.fielderAssignedLocationIndex[loc] = -1;
                        g_FieldingLogic.baseCoveredInd[loc] = 0;
                    }
                    fielder->locationResponsibleForCovering = -1;
                    fielder->isResponsibleForCoveringALocation = 0;
                    if (fielder->autoMovementFunctionIndex == 1 && fielderIndex != -1) {
                        fielder->autoMovementFunctionIndex = 12;
                        if (autoMovementFunctions[12].code >= 0) {
                            g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[12].code;
                        }
                        fielder->unknown_writeOnly = 0;
                        fielder->fielderVeloAdjustmentCode = 0;
                        fielder->unknown_writeOnly_always0 = 0;
                        fielder->timeSinceThrowWasCaught = 0;
                        fielder->fielderTrackingBallState = 0;
                    }
                } else if (loc == 5) {
                    g_FieldingLogic.fielderAssignedLocationIndex[4] = -1;
                    fielder->locationResponsibleForCovering = -1;
                    fielder->isResponsibleForCoveringALocation = 0;
                    g_FieldingLogic.playerAtMoundCutoffLocation = 0;
                    if (fielder->autoMovementFunctionIndex == 14 && fielderIndex != -1) {
                        fielder->autoMovementFunctionIndex = 12;
                        if (autoMovementFunctions[12].code >= 0) {
                            g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[12].code;
                        }
                        fielder->unknown_writeOnly = 0;
                        fielder->fielderVeloAdjustmentCode = 0;
                        fielder->unknown_writeOnly_always0 = 0;
                        fielder->timeSinceThrowWasCaught = 0;
                        fielder->fielderTrackingBallState = 0;
                    }
                }
            }
        }
    } else {
        if (g_Ball.fielderWBallIndex == fielderIndex) {
            int i;
            for (i = 0; i < 4; i++) {
                f32 dx = base_MoundCoordinates[i].x - fielder->pos.x;
                f32 dz = base_MoundCoordinates[i].z - fielder->pos.z;
                f32 sqx = dx * dx;
                f32 sqz = dz * dz;
                dist = fielderSqrt(sqx + sqz);

                threshold = thresholdToBeConsideredCoveringBase_ByWeight[fielder->Weight];
                if (threshold <= dist) {
                    continue;
                }

                {
                    s16 otherFielderIdx = g_FieldingLogic.fielderAssignedLocationIndex[i];
                    InMemFielder* other = &g_Fielders[otherFielderIdx];
                    s16 otherLoc = other->locationResponsibleForCovering;
                    if (otherLoc >= 0) {
                        if (otherLoc <= 3) {
                            if (g_FieldingLogic.fielderAssignedLocationIndex[otherLoc] == otherFielderIdx) {
                                g_FieldingLogic.fielderAssignedLocationIndex[otherLoc] = -1;
                                g_FieldingLogic.baseCoveredInd[otherLoc] = 0;
                            }
                            other->locationResponsibleForCovering = -1;
                            other->isResponsibleForCoveringALocation = 0;
                            if (other->autoMovementFunctionIndex == 1 && otherFielderIdx != -1) {
                                other->autoMovementFunctionIndex = 12;
                                if (autoMovementFunctions[12].code >= 0) {
                                    g_FieldingLogic.fielderAutoMovementCode[otherFielderIdx] = autoMovementFunctions[12].code;
                                }
                                other->unknown_writeOnly = 0;
                                other->fielderVeloAdjustmentCode = 0;
                                other->unknown_writeOnly_always0 = 0;
                                other->timeSinceThrowWasCaught = 0;
                                other->fielderTrackingBallState = 0;
                            }
                        } else if (otherLoc == 5) {
                            g_FieldingLogic.fielderAssignedLocationIndex[4] = -1;
                            other->locationResponsibleForCovering = -1;
                            other->isResponsibleForCoveringALocation = 0;
                            g_FieldingLogic.playerAtMoundCutoffLocation = 0;
                            if (other->autoMovementFunctionIndex == 14 && otherFielderIdx != -1) {
                                other->autoMovementFunctionIndex = 12;
                                if (autoMovementFunctions[12].code >= 0) {
                                    g_FieldingLogic.fielderAutoMovementCode[otherFielderIdx] = autoMovementFunctions[12].code;
                                }
                                other->unknown_writeOnly = 0;
                                other->fielderVeloAdjustmentCode = 0;
                                other->unknown_writeOnly_always0 = 0;
                                other->timeSinceThrowWasCaught = 0;
                                other->fielderTrackingBallState = 0;
                            }
                        }
                    }
                }

                fielder->locationResponsibleForCovering = i;
                g_FieldingLogic.fielderAssignedLocationIndex[i] = fielderIndex;
                fielder->isResponsibleForCoveringALocation = 1;
                g_FieldingLogic.baseCoveredInd[i] = 1;
                break;
            }
        }
    }

    if (fielder->baseCurrentlyOn >= 0) {
        f32 dx = base_MoundCoordinates[fielder->baseCurrentlyOn].x - fielder->pos.x;
        f32 dz = base_MoundCoordinates[fielder->baseCurrentlyOn].z - fielder->pos.z;
        f32 sqx = dx * dx;
        f32 sqz = dz * dz;
        dist = fielderSqrt(sqx + sqz);

        if (g_Ball.fielderWBallIndex == fielderIndex) {
            threshold = thresholdToBeConsideredCoveringBase_ByWeight[fielder->Weight] + lbl_3_rodata_CA0;
            if (threshold < dist) {
                fielder->baseCurrentlyOn = -1;
            }
        } else {
            threshold = thresholdToBeConsideredCoveringBase_ByWeight[fielder->Weight] + lbl_3_rodata_CA4;
            if (threshold < dist) {
                fielder->baseCurrentlyOn = -1;
            }
        }
    }

    if (fielder->isJump) {
        fielder->baseCurrentlyOn = -1;
    }

    if (fielder->baseCurrentlyOn < 0) {
        int k;
        for (k = 0; k < 4; k++) {
            if (g_FieldingLogic.fielderAssignedLocationIndex[k] == fielderIndex) {
                g_FieldingLogic.baseCoveredInd[k] = 0;
                break;
            }
        }
    }
}

// .text:0x00053EE8 size:0x60 mapped:0x80692F7C
void fielderMovementRelated(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];

    if (fielderIndex == -1) {
        return;
    }

    fielder->autoMovementFunctionIndex = 19;
    if (autoMovementFunctions[19].code >= 0) {
        g_FieldingLogic.fielderAutoMovementCode[fielderIndex] = autoMovementFunctions[19].code;
    }
    fielder->unknown_writeOnly = 0;
    fielder->fielderVeloAdjustmentCode = 0;
    fielder->unknown_writeOnly_always0 = 0;
    fielder->timeSinceThrowWasCaught = 0;
    fielder->fielderTrackingBallState = 0;
}

// .text:0x00053F48 size:0x570 mapped:0x80692FDC
void minigameFieldingRelated_collisions(void) {
    return;
}

// .text:0x000544B8 size:0x448 mapped:0x8069354C
void fielding_handleCollisionsAndSpecialActions(void) {
    int i;
    InMemFielder* fielder;
    VecSrcDst inVec;
    CollisionStruct collision;
    u32 collisionType;
    Vec currentPos, prevPos;
    SND_FXID fid;
    SND_VOICEID voiceID;
    u8 vol, val;

    extern const f32 lbl_3_rodata_B60;
    extern const f32 lbl_3_rodata_CA8;
    extern const f32 lbl_3_rodata_C9C;
    extern u16 stadiumHazardSoundIDs[16];
    extern u8 stadiumHazardSoundFxRelated[0xB4];
    extern u8 lbl_3_data_84B8[0x3C];
    extern u8 fn_800639BC(s8 fielderIndex, Vec* currentPos, Vec* prevFramePos);
    extern void maybeUpdateFielderTerrainStatus(s8 fielderIndex);
    extern void processBallFielderCollision(u8 fielderIndex);

    for (i = 0, fielder = g_Fielders; i < 9; i++, fielder++) {
        if (g_d_GameSettings.minigamesEnabled && g_Minigame.minigameRelatedIndex != i) {
            continue;
        }

        if (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT || g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL) {
            if (fielder->distanceToMound > lbl_3_rodata_CA8 && g_Ball.totalFramesAtPlay > 1 &&
                g_Ball.totalFramesAtPlay < 0x7fff && (i % 3) != (g_Ball.totalFramesAtPlay % 3)) {
                fielder->actionYOffset = fielder->storedPosY;
                collisionType = fielder->terrainOrCollisionRelated;
                goto afterCollisionCheck;
            }
        }

        inVec.src.x = fielder->pos.x;
        inVec.src.y = lbl_3_rodata_C9C;
        inVec.src.z = fielder->pos.z;
        inVec.dst.x = fielder->pos.x;
        inVec.dst.y = lbl_3_rodata_B60;
        inVec.dst.z = fielder->pos.z;

        collisionType = checkCollision(&inVec, &collision, 0, 0);
        if (collisionType != BALL_COLLISION_TYPE_NONE) {
            fielder->actionYOffset = -collision.position.y;
        } else {
            fielder->actionYOffset = lbl_3_rodata_B20;
        }

        if ((collisionType & 0x7f) == BALL_COLLISION_TYPE_WATER) {
            currentPos.x = fielder->pos.x;
            currentPos.y = fielder->actionYOffset;
            currentPos.z = fielder->pos.z;
            prevPos.x = fielder->posXLastFrame;
            prevPos.y = fielder->actionYOffset;
            prevPos.z = fielder->posZLastFrame;

            if (fn_800639BC((s8)i, &currentPos, &prevPos) >= 2) {
                if (g_d_GameSettings.StadiumID == STADIUM_ID_PEACH_GARDEN) {
                    fid = stadiumHazardSoundIDs[4] + 7;
                    vol = (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD)
                              ? lbl_3_data_84B8[0xe]
                              : stadiumHazardSoundFxRelated[0x86];
                    voiceID = sndFXStartEx(fid, vol, 0x3f, 0);
                    val = (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD)
                              ? lbl_3_data_84B8[0xf]
                              : stadiumHazardSoundFxRelated[0x87];
                    sndFXCtrl(voiceID, 0x5b, val);
                } else if (g_d_GameSettings.StadiumID == STADIUM_ID_DK_JUNGLE) {
                    fid = stadiumHazardSoundIDs[5] + 0xc;
                    vol = (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD)
                              ? lbl_3_data_84B8[0x18]
                              : stadiumHazardSoundFxRelated[0xae];
                    voiceID = sndFXStartEx(fid, vol, 0x3f, 0);
                    val = (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD)
                              ? lbl_3_data_84B8[0x19]
                              : stadiumHazardSoundFxRelated[0xaf];
                    sndFXCtrl(voiceID, 0x5b, val);
                }
            }
        } else {
            maybeUpdateFielderTerrainStatus((s8)i);
        }

        if ((collisionType & 0x7f) == BALL_COLLISION_TYPE_ROUGH_TERRAIN) {
            processBallFielderCollision((u8)(i + 1));
        }

        fielder->storedPosY = fielder->actionYOffset;

    afterCollisionCheck:
        if (fielder->isJump) {
            fielder->actionYOffset = fielder->actionYOffset + fielder->jumpY;
        }
        if (fielder->clamberStatus) {
            fielder->actionYOffset = fielder->wallActionCurrentHeight;
        }
        if (fielder->wallSplatStatus) {
            fielder->actionYOffset = fielder->wallActionCurrentHeight;
        }

        if (fielder->catchAnimation == 4) {
            fielder->actionYOffset = fielder->wallActionCurrentHeight;
            if (fielder->wallJumpFramesTillTopOfWallContact) {
                fielder->wallJumpStatus = 1;
            } else {
                fielder->wallJumpStatus = 2;
            }
        } else if (fielder->wallJumpStatus != 0) {
            if (fielder->wallJumpStatus == 2) {
                f32 velocity;
                f32 height;

                fielder->wallJumpStatus = 3;
                fielder->wallActionHeightAdjustment = lbl_3_rodata_B20;
                fielder->wallActionFrameCounter = 0;

                velocity = lbl_3_rodata_B80 * fielder->jumpVelocity.y;
                height = fielder->wallActionCurrentHeight;
                do {
                    velocity -= fielderActionConstants[11];
                    fielder->wallActionFrameCounter++;
                    height += velocity;
                } while (height >= lbl_3_rodata_B20);

                getComponentsFromSAng(fielder->playerAngleFromHome, &fielder->wallActionVelo.x,
                                      &fielder->wallActionVelo.z);
                fielder->wallActionVelo.x *= -fielderActionConstants[13];
                fielder->wallActionVelo.z *= -fielderActionConstants[13];
            } else if (fielder->wallJumpStatus == 3) {
                fielder->wallActionFrameCounter--;
                fielder->wallActionHeightAdjustment -= fielderActionConstants[11];
                fielder->wallActionCurrentHeight += fielder->wallActionHeightAdjustment;
                if (fielder->wallActionCurrentHeight < lbl_3_rodata_B20) {
                    fielder->wallActionCurrentHeight = lbl_3_rodata_B20;
                    fielder->wallJumpStatus = 4;
                    fielder->wallActionCountDown = specialFielderActionConstants._00[4];
                }
            }
            fielder->actionYOffset = fielder->wallActionCurrentHeight;
        }

        fielder->terrainOrCollisionRelated = collisionType;
    }
}

// .text:0x00054900 size:0x258 mapped:0x80693994
void fn_3_54900(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    int runnerMask = g_RunningLogic._04;
    f32 targetX;
    f32 targetZ;

    if (fielder->baseCurrentlyOn >= 0) {
        targetX = base_MoundCoordinates[4].x;
        targetZ = base_MoundCoordinates[4].z;
    } else {
        if (g_RunningLogic._10 == 0) {
            fielder->desiredMovementDirectionStored = fielder->desiredMovementDirection;
            fielder->_01F2 = 1;
            return;
        }

        if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT) {
            runnerMask &= 0xFFF0;
        }

        switch (runnerMask) {
        case 0x1:
            targetX = base_MoundCoordinates[1].x;
            targetZ = base_MoundCoordinates[1].z;
            break;
        case 0x10:
            targetX = lbl_3_rodata_C38 * base_MoundCoordinates[2].x + lbl_3_rodata_BB8 * base_MoundCoordinates[1].x;
            targetZ = lbl_3_rodata_C38 * base_MoundCoordinates[2].z + lbl_3_rodata_BB8 * base_MoundCoordinates[1].z;
            break;
        case 0x100:
            targetX = lbl_3_rodata_C38 * base_MoundCoordinates[3].x + lbl_3_rodata_BB8 * base_MoundCoordinates[2].x;
            targetZ = lbl_3_rodata_C38 * base_MoundCoordinates[3].z + lbl_3_rodata_BB8 * base_MoundCoordinates[2].z;
            break;
        case 0x11:
            targetX = lbl_3_rodata_B80 * (base_MoundCoordinates[1].x + base_MoundCoordinates[2].x);
            targetZ = lbl_3_rodata_B80 * (base_MoundCoordinates[1].z + base_MoundCoordinates[2].z);
            break;
        case 0x110:
            targetX = lbl_3_rodata_B80 * (base_MoundCoordinates[2].x + base_MoundCoordinates[3].x);
            targetZ = lbl_3_rodata_B80 * (base_MoundCoordinates[2].z + base_MoundCoordinates[3].z);
            break;
        case 0x111:
            targetX = lbl_3_rodata_BB8 * base_MoundCoordinates[3].x + lbl_3_rodata_C38 * base_MoundCoordinates[2].x;
            targetZ = lbl_3_rodata_BB8 * base_MoundCoordinates[3].z + lbl_3_rodata_C38 * base_MoundCoordinates[2].z;
            break;
        case 0x101:
            targetX = base_MoundCoordinates[4].x;
            targetZ = base_MoundCoordinates[4].z;
            break;
        default:
            targetX = base_MoundCoordinates[0].x;
            targetZ = base_MoundCoordinates[0].z;
            break;
        }
    }

    fielder->desiredMovementDirection = ATAN2F(targetZ - fielder->pos.z, targetX - fielder->pos.x);
}

// .text:0x00054B58 size:0x818 mapped:0x80693BEC
void updateFielderDirectionFacing(void) {
    return;
}

// .text:0x00055370 size:0x23C mapped:0x80694404
void fn_3_55370(void) {
    return;
}

// .text:0x000555AC size:0x164 mapped:0x80694640
void fn_3_555AC(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    f32 posZ;
    f32 posX;

    fielder->inBasePath = 0;

    posZ = fielder->pos.z;
    if (posZ > lbl_3_rodata_C18) {
        return;
    }
    if (posZ < lbl_3_rodata_C88) {
        return;
    }

    posX = fielder->pos.x;
    if (posX > lbl_3_rodata_B90) {
        return;
    }
    if (posX < lbl_3_rodata_CB8) {
        return;
    }

    if (posZ > base_MoundCoordinates[1].z) {
        f32 lo = base_MoundCoordinates[2].z - lbl_3_rodata_B68;
        f32 hi = lbl_3_rodata_B8C + base_MoundCoordinates[2].z;

        if (posX > lbl_3_rodata_B20) {
            if (posZ > -posX + lo && posZ < -posX + hi) {
                fielder->inBasePath = 2;
            }
        } else {
            if (posZ > posX + lo && posZ < posX + hi) {
                fielder->inBasePath = 3;
            }
        }
    } else {
        f32 lo = base_MoundCoordinates[0].z - lbl_3_rodata_B8C;
        f32 hi = lbl_3_rodata_B68 + base_MoundCoordinates[0].z;

        if (posX > lbl_3_rodata_B20) {
            if (posZ > posX + lo && posZ < posX + hi) {
                fielder->inBasePath = 1;
            }
        } else {
            if (posZ > -posX + lo && posZ < -posX + hi) {
                fielder->inBasePath = 4;
            }
        }
    }
}

void handleBodyCheck2(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    InMemRunnerType* runner;
    int base = fielder->baseCurrentlyOn;
    int i;

    if (g_FieldingLogic.bodyCheckResult != 0) {
        int runnerIndex = g_FieldingLogic.index_runnerAttemptingBodycheck;

        if (g_Runners[runnerIndex].baseStandingOn >= 0 ||
            g_Runners[runnerIndex].runnerOnFieldOrOutOrScored == RUNNER_STATUS_OUT_DURING_PLAY) {
            g_FieldingLogic.bodyCheckResult = 0;
            g_FieldingLogic.framesRunnerIsOutBy = 0;
        }
        return;
    }

    if ((s8)g_FieldingLogic.baseFielderIsOn >= 0) {
        base = (s8)g_FieldingLogic.baseFielderIsOn;
    }
    if (base < 0) {
        return;
    }

    for (i = 3; i >= 0; i--) {
        runner = &g_Runners[i];

        if (runner->runnerOnFieldOrOutOrScored != RUNNER_STATUS_ON_FIELD) {
            continue;
        }
        if (runner->forceOutCd > 0) {
            continue;
        }
        if (runner->baseRunningTowards != base) {
            continue;
        }
        if (runner->tagUpInd != TAG_UP_TYPE_NONE) {
            continue;
        }
        if (runner->baseStandingOn >= 0) {
            continue;
        }
        if (runner->actionCode == 0) {
            continue;
        }

        if (runner->actionCode == 2) {
            fielder->bodyCheckResult = 2;
            fielder->bodyCheckStatus = 0;
            g_FieldingLogic.bodyCheckResult = 2;
            g_FieldingLogic.framesRunnerIsOutBy = 6;
            g_FieldingLogic.tagAnimationType = 7;
            g_FieldingLogic.bodyCheckResult2 = 2;
            fielder->bodyCheckRunnerNumber = i;

            if (!g_GameLogic.teamIsCPU[g_GameLogic.teamFielding]) {
                setCharacterAnimations(g_GameLogic.teamFielding, 2);
            }
        } else if (runner->actionCode == 3) {
            fielder->bodyCheckResult = 1;
            fielder->bodyCheckStatus = 0;
            g_FieldingLogic.bodyCheckResult = 1;
            g_FieldingLogic.framesRunnerIsOutBy = runner->actionFrames_countDown;
            g_FieldingLogic.tagAnimationType = 6;
            g_FieldingLogic.bodyCheckResult2 = 1;
            fielder->bodyCheckRunnerNumber = i;
        } else {
            if (runner->actionFrames_countDown < 6) {
                g_FieldingLogic.bodyCheckResult = 2;
                g_FieldingLogic.framesRunnerIsOutBy = 6;
            } else {
                g_FieldingLogic.bodyCheckResult = 1;
                g_FieldingLogic.framesRunnerIsOutBy = runner->actionFrames_countDown;
            }
        }

        g_FieldingLogic.index_runnerAttemptingBodycheck = i;
        return;
    }
}

// .text:0x00055918 size:0x3AC mapped:0x806949AC
void fielder_endOfInning_deadball_updateCounters(void) {
    InMemFielder* fielder;
    int i;
    s16 fielderWBallIdx;

    if (g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam] != 0) {
        fielderAISomething();
    }

    if (g_Strikes.outs >= 3 && g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE) {
        fielder = g_Fielders;
        for (i = 0; i < 9; i++, fielder++) {
            if (fielder->autoMovementFunctionIndex == 17) {
                continue;
            }
            if (g_Ball.fielderWBallIndex == i && g_FieldingLogic.bodyCheckResult != 0) {
                continue;
            }
            if (fielder->_0200 != 0) {
                continue;
            }
            if (i == -1) {
                continue;
            }

            fielder->autoMovementFunctionIndex = 17;
            if (autoMovementFunctions[17].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[i] = autoMovementFunctions[17].code;
            }
            fielder->unknown_writeOnly = 0;
            fielder->fielderVeloAdjustmentCode = 0;
            fielder->unknown_writeOnly_always0 = 0;
            fielder->timeSinceThrowWasCaught = 0;
            fielder->fielderTrackingBallState = 0;
        }
    }

    if (g_Ball.unknown_always0 >= 1 && g_Ball.unknown_always0 <= 4) {
        fielder = g_Fielders;
        for (i = 0; i < 9; i++, fielder++) {
            if (i != -1) {
                fielder->autoMovementFunctionIndex = 0;
                if (autoMovementFunctions[0].code >= 0) {
                    g_FieldingLogic.fielderAutoMovementCode[i] = autoMovementFunctions[0].code;
                }
                fielder->unknown_writeOnly = 0;
                fielder->fielderVeloAdjustmentCode = 0;
                fielder->unknown_writeOnly_always0 = 0;
                fielder->timeSinceThrowWasCaught = 0;
                fielder->fielderTrackingBallState = 0;
            }
        }
    } else if (g_Ball.deadBallReason != 0) {
        fielder = g_Fielders;
        for (i = 0; i < 9; i++, fielder++) {
            if (!(g_Ball.unknown_always0 >= 1 && g_Ball.unknown_always0 <= 4) &&
                fielder->autoMovementFunctionIndex == 15 && g_Ball.deadBallReason != 0) {
                continue;
            }
            if (fielder->autoMovementFunctionIndex == 12) {
                continue;
            }
            if (fielder->catchAnimation != 0) {
                continue;
            }
            if (i == -1) {
                continue;
            }

            fielder->autoMovementFunctionIndex = 12;
            if (autoMovementFunctions[12].code >= 0) {
                g_FieldingLogic.fielderAutoMovementCode[i] = autoMovementFunctions[12].code;
            }
            fielder->unknown_writeOnly = 0;
            fielder->fielderVeloAdjustmentCode = 0;
            fielder->unknown_writeOnly_always0 = 0;
            fielder->timeSinceThrowWasCaught = 0;
            fielder->fielderTrackingBallState = 0;
        }
    }

    if (g_FieldingLogic.humanSelectedPlaceToThrow >= 0) {
        if (g_FieldingLogic.someHumanThrowFrameCounter < 0x7ffe) {
            g_FieldingLogic.someHumanThrowFrameCounter++;
        } else {
            g_FieldingLogic.someHumanThrowFrameCounter = 0x7fff;
        }
        if (g_FieldingLogic.someHumanThrowFrameCounter > 30) {
            g_FieldingLogic.humanSelectedPlaceToThrow = -1;
            g_FieldingLogic.someHumanThrowFrameCounter = 0;
        }
    }

    if (g_FieldingLogic.locationThrownTo >= 0) {
        if (g_Ball.ballState == BALL_STATE_THROWN) {
            g_FieldingLogic.throwWindupFrames = 0;
        } else if (g_FieldingLogic.throwWindupFrames < 0x7ffe) {
            g_FieldingLogic.throwWindupFrames++;
        } else {
            g_FieldingLogic.throwWindupFrames = 0x7fff;
        }
    } else {
        g_FieldingLogic.throwWindupFrames = 0;
    }

    if (g_FieldingLogic.always0_012b != 0) {
        fielderWBallIdx = g_Ball.fielderWBallIndex;
        if (fielderWBallIdx >= 0) {
            fielder = &g_Fielders[fielderWBallIdx];
            if (fielder->baseCurrentlyOn >= 0) {
                g_FieldingLogic.always0_012b = 0;
            } else {
                g_FieldingLogic.always0_012b--;
            }
        } else {
            g_FieldingLogic.always0_012b = 0;
        }
    }

    for (i = 0; i < 9; i++) {
        g_Fielders[i].throwWindupEstimate = 15;
    }
}

// .text:0x00055CC4 size:0x228 mapped:0x80694D58
void fielderUpdateChasingRunnerValues(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];

    if (fielder->unknown_Unused == 2 && g_Ball.fielderWBallIndex != fielderIndex) {
        fielder->unknown_Unused = 0;
    }

    if (fielder->currentVelocity <= lbl_3_rodata_B20) {
        fielder->runningAngle = -1;
        fielder->framesSinceStartedMoving = 0;
    } else {
        fielder->runningAngle = radToShortAngle(fielder->desiredMovementDirection2);
        if (fielder->framesSinceStartedMoving < 0x7ffe) {
            fielder->framesSinceStartedMoving += 1;
        } else {
            fielder->framesSinceStartedMoving = 0x7fff;
        }
    }

    if (g_FieldingLogic.runnerChasingAfter >= 0 && fielder->autoFielderInd == 0 &&
        g_Runners[g_FieldingLogic.runnerChasingAfter].runnerOnFieldOrOutOrScored != RUNNER_STATUS_ON_FIELD) {
        g_FieldingLogic.runnerChasingAfter = -1;
    }

    if (g_Ball.ballState == BALL_STATE_HELD || g_Ball.ballState == BALL_STATE_THROWN) {
        if (g_FieldingLogic.fielderAssignedLocationIndex[6] >= 0 &&
            g_FieldingLogic.somethingForTryingTagOutTargetBase == 9) {
            s16 runnerChasingAfter = g_FieldingLogic.runnerChasingAfter;

            if (runnerChasingAfter >= 0) {
                f32 percentTowardsNextBase = g_Runners[runnerChasingAfter].percentTowardsNextBase;

                if (percentTowardsNextBase >= lbl_3_rodata_BB8 && percentTowardsNextBase <= lbl_3_rodata_CBC) {
                    g_FieldingLogic.someRunnerNum = runnerChasingAfter;
                }
            }
        }

        {
            s16 someRunnerNum = g_FieldingLogic.someRunnerNum;

            if (someRunnerNum >= 0) {
                if (g_Runners[someRunnerNum].runnerOnFieldOrOutOrScored != RUNNER_STATUS_ON_FIELD ||
                    g_Runners[someRunnerNum].baseStandingOn >= 0) {
                    g_FieldingLogic.someRunnerNum = -1;
                } else {
                    u8 currentBase = g_Runners[someRunnerNum].currentBase;
                    u8 nextBase = g_Runners[someRunnerNum].nextBase;
                    s16 locationThrownTo = g_FieldingLogic.locationThrownTo;

                    if (locationThrownTo != -1 && locationThrownTo != currentBase && locationThrownTo != nextBase) {
                        g_FieldingLogic.someRunnerNum = -1;
                    }

                    if (g_FieldingLogic.somethingForTryingTagOutTargetBase != -1 &&
                        g_FieldingLogic.somethingForTryingTagOutTargetBase != 9 &&
                        g_FieldingLogic.somethingForTryingTagOutTargetBase != currentBase &&
                        g_FieldingLogic.somethingForTryingTagOutTargetBase != nextBase) {
                        g_FieldingLogic.someRunnerNum = -1;
                    }
                }
            }
        }
    }
}

// .text:0x00055EEC size:0x1258 mapped:0x80694F80
void updateFielder_SpecificValuesEachFrame(void) {
    return;
}

// .text:0x00057144 size:0x344 mapped:0x806961D8
void liveBallUpdateFieldingValues(void) {
    return;
}

// .text:0x00057488 size:0x22C mapped:0x8069651C
void updateOutfielderPositionBasedOnBallState(void) {
    int fielderIndex = g_FieldingLogic.selectedFielder;
    int idx = fielderIndex;
    InMemFielder* fielder;
    f32 dist;

    if (g_d_GameSettings.minigamesEnabled) {
        idx = g_Minigame.minigameRelatedIndex;
    }

    fielder = &g_Fielders[idx];

    if (g_AiLogic.AIControlFlag != 0) {
        goto setFromFutureCoord;
    }

    if (g_Ball.ballState == BALL_STATE_LOOSE) {
        goto setFromFutureCoord;
    }
    if (g_Ball.ballState != BALL_STATE_HIT) {
        goto checkIntercept;
    }
    if (g_Ball.hitWallInd != 0) {
        goto setFromFutureCoord;
    }
    if (g_Ball.ballStoppingCode1ReallySlow2Stopped != 0) {
        goto setFromFutureCoord;
    }

    if (fielderIndex >= 6 || g_d_GameSettings.minigamesEnabled) {
        dist = fielderSqrt(SQ(fielder->maybeTargetPosX) + SQ(fielder->maybeTargetPosZ));
        if (dist > lbl_3_rodata_BA0 && g_Ball.ballDistanceFromHome > dist) {
            goto setFromFutureCoord;
        }
    }

checkIntercept:
    if (fielder->maybeTargetPosX > const10000) {
        setIntendedLocToInterceptBall(g_FieldingLogic.selectedFielder);
        fielder->maybeTargetPosX = fielder->IntendedLocation.x;
        fielder->maybeTargetPosZ = fielder->IntendedLocation.z;
    }
    return;

setFromFutureCoord:
    g_AiLogic.AIControlFlag = 1;
    fielder->maybeTargetPosX = g_Ball.physicsSubstruct.futureCoordsAndDist[15].pos.x;
    fielder->maybeTargetPosZ = g_Ball.physicsSubstruct.futureCoordsAndDist[15].pos.z;
}

extern const f32 lbl_3_rodata_B60;
extern s16 slidingCatchArray[6];

// .text:0x000576B4 size:0x360 mapped:0x80696748
void processFielderJumpAI(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    f32 reach;
    f32 threshold;
    int i;

    if (g_FieldingLogic.jumpDiveStruct->aiFieldingDashIndicator[0] == 0) {
        return;
    }
    if (g_Ball.ballState != BALL_STATE_HIT) {
        return;
    }
    if (g_Ball.framesSinceHit < fielder->lockoutDuration + 3) {
        return;
    }

    g_FieldingLogic.jumpDiveStruct->aiOutfieldFielderAction = 0;

    if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_IN_AIR && g_Ball.maxYOfHit > lbl_3_rodata_B64) {
        if (g_Ball.framesUntilBallHitsGround >= slidingCatchArray[0]) {
            return;
        }
        if (g_Ball.framesUntilBallHitsGround <= 20) {
            return;
        }

        reach = fielder->currentVelocity * (f32)(g_Ball.framesUntilBallHitsGround - 1);
        if (reach - lbl_3_rodata_B60 > fielder->distanceFromLandingSpot) {
            return;
        }

        if (fielder->framesRemainingToGetToLandingSpot > 0 &&
            fielder->distanceFromAutoLocation < lbl_3_rodata_B60) {
            if (g_Ball.physicsSubstruct
                    .futureCoordsAndDist[fielder->framesRemainingToGetToLandingSpot]
                    .pos.y <= fielder->hitbox[3]) {
                return;
            }
        }

        if (fielderIndex <= 5) {
            g_FieldingLogic.jumpDiveStruct->aPressed_decidingWhatActionToTake = 2;
        } else {
            g_FieldingLogic.jumpDiveStruct->aPressed_decidingWhatActionToTake = 2;
            g_FieldingLogic.jumpDiveStruct->aiOutfieldFielderAction = 1;
        }
        return;
    }

    if (fielderIndex < 2) {
        return;
    }
    if (fielderIndex > 5) {
        return;
    }

    if (fielder->groundDistanceFromBall < fielder->hitbox[0]) {
        threshold = fielder->distanceFromHomePlate - lbl_3_rodata_B60;
        if (g_Ball.ballDistanceFromHome > threshold) {
            return;
        }

        for (i = 6; i <= 30; i += 2) {
            if (g_Ball.physicsSubstruct.futureCoordsAndDist[i].dist > threshold) {
                break;
            }
        }
        if (i > 30) {
            return;
        }

        if (g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.y > fielder->hitbox[3]) {
            g_FieldingLogic.jumpDiveStruct->aPressed_decidingWhatActionToTake = 2;
            if (fielder->isJump == 0) {
                fn_3_258D8(fielderIndex);
            }
        }
    } else {
        g_FieldingLogic.jumpDiveStruct->aPressed_decidingWhatActionToTake = 2;
    }
}

// .text:0x00057A14 size:0x1A0 mapped:0x80696AA8
void aITeamFielding_SelectCharWithHand(void) {
    f32 minDist;
    f32 secondMinDist;
    f32 dist;
    int bestFielder;
    int secondFielder;
    u8 code;
    int i;

    if (g_Ball.fielderWBallIndex < 0) {
        g_FieldingLogic.selectedFielder = g_Ball.fielderWBallIndex;
        return;
    }

    if (g_Ball.ballState == BALL_STATE_THROWN) {
        g_FieldingLogic.selectedFielder = g_Ball.fielderBeingThrownTo;
        return;
    }

    minDist = lbl_3_rodata_BA4;
    secondMinDist = minDist;
    bestFielder = -1;
    secondFielder = -1;

    for (i = 1; i < 9; i++) {
        code = g_Fielders[i].autoMovementFunctionIndex;
        if (code == 2 || code == 3) {
            dist = g_Fielders[i].groundDistanceFromBall;
            if (dist < secondMinDist) {
                if (dist < minDist) {
                    secondMinDist = minDist;
                    secondFielder = bestFielder;
                    minDist = dist;
                    bestFielder = i;
                } else {
                    secondMinDist = dist;
                    secondFielder = i;
                }
            }
        }
    }

    if (bestFielder >= 0) {
        g_FieldingLogic.selectedFielder = bestFielder;
    } else {
        code = g_Fielders[0].autoMovementFunctionIndex;
        if (code == 2 || code == 3 || code == 4) {
            g_FieldingLogic.selectedFielder = 0;
        }
    }

    if (secondFielder >= 0) {
        g_FieldingLogic.secondaryFielder = secondFielder;
    }

    if (g_FieldingLogic.selectedFielder >= 0) {
        processFielderJumpAI(g_FieldingLogic.selectedFielder);
    }
}

// .text:0x00057BB4 size:0x804 mapped:0x80696C48
void updateFielderMovementAndPosition(void) {
    return;
}

// .text:0x000583B8 size:0x2D0 mapped:0x8069744C
void liveBallFielderControlAITeam(void) {
    return;
}

// .text:0x00058688 size:0x1E8 mapped:0x8069771C
void fielderResetAndStoreValuesEachFrame(void) {
    int i;

    g_FieldingLogic.xcc_Stored_0 = g_FieldingLogic.somethingForTryingTagOutTargetBase;
    g_FieldingLogic.runnerChasingAfter_stored = g_FieldingLogic.runnerChasingAfter;
    if (g_Ball.looseBall_5FrameCountdown != 0) {
        g_Ball.looseBall_5FrameCountdown--;
    }

    {
        InMemFielder* fielder = g_Fielders;
        for (i = 0; i < 9; i++) {
            fielder->wallActionFacingAngleInd = 0;
            fielder->closingInOnCatchingFlyBall_stored = fielder->closingInOnCatchingFlyBall;
            fielder->closingInOnCatchingFlyBall = 0;
            fielder->_020B_stored = fielder->_020B;
            fielder->_020B = 0;
            fielder->needToMoveToCatchThrownBall = 0;
            fielder->_0263 = 0;
            fielder++;
        }
    }

    if (g_Ball.framesSinceHit == 1 ||
        (g_Ball.framesSinceHit == 0x65 && g_FieldingLogic.liveBallBcOfPickoffOrStealCd != 0)) {
        for (i = 0; i < 9; i++) {
            g_Fielders[i].storedPosX = g_Fielders[i].pos.x;
            g_Fielders[i].storedPosZ = g_Fielders[i].pos.z;
        }
    }

    g_FieldingLogic.specialActionChecks.aPressed_decidingWhatActionToTake = 0;
    g_FieldingLogic._007c = 0;
    g_FieldingLogic._0082 = 0;
    g_FieldingLogic._0088[0] = 0;
    g_FieldingLogic._0144 = 0;
    g_Ball.fielderActionOccuring = 0;
    g_Pitcher.unused_pitcherIsFielder = 0;
    if (g_FieldingLogic.FrameCycleCounter_20 != 0) {
        g_FieldingLogic.FrameCycleCounter_20--;
    }
}

// .text:0x00058870 size:0x5E0 mapped:0x80697904
void setDefaultInMemFielder(void) {
    int i;
    InMemFielder* fielder;

    if (!g_d_GameSettings.minigamesEnabled) {
        pPRelated();
    }

    for (i = 0; i < 9; i++) {
        fielder = &g_Fielders[i];

        fielder->locationResponsibleForCovering = -1;
        fielder->isResponsibleForCoveringALocation = 0;
        fielder->pitcherHeadingToCover1stOr3rd = 0;
        fielder->autoMovementFunctionIndex = 0;
        fielder->catchStrategy = 0;
        fielder->numFramesToGetToAutoLocation = -1;
        fielder->presetLocationCategory = -1;
        fielder->unknown_writeOnly = 0;
        fielder->fielderVeloAdjustmentCode = 0;
        fielder->throwWindupEstimate = 0xf;
        fielder->framesSinceThrowWasMade = 0;
        fielder->fielderMadeThrow = 0;
        fielder->_0198 = 0;
        fielder->always0_ = 0;
        fielder->nonCatchFlyBallStratInd = 0;
        fielder->maybeMovementState = 0;
        fielder->fielderReadiness = 0;
        fielder->unused_alwaysSetTo0 = 0;
        fielder->playerNeedsToMoveToCatchThrowInd = 0;
        fielder->animationRelatedInd = 0;
        fielder->animatingActionInd = 0;
        fielder->hitKnockbackCountdown = 0;
        fielder->stunFramesOnFireBall = 0;
        fielder->_01E1 = 0;
        fielder->standingStillInd = 1;
        fielder->_01E4 = 0;
        fielder->currentVelocity = lbl_3_rodata_B20;
        fielder->unused = lbl_3_rodata_B20;
        fielder->framesSinceStartedMoving = 0;
        fielder->_01F2 = 0;
        fielder->always0_forcePlayRelated = 0;
        fielder->runningVsLookingAngleCode = 0;
        fielder->_01F4 = 0;
        fielder->baseCurrentlyOn = -1;
        fielder->baseOn2 = 0xff;
        fielder->_01F9 = 0;
        fielder->atDugoutAtEndOfInning = 0;
        fielder->someCountDown = 0;
        fielder->wallActionFacingAngleInd = 1;
        fielder->_0200 = 0;
        fielder->fielderIsInitialOutfielderSelectedInd = 0;
        fielder->cutoffWaitingToInterceptThrownBall = 0;
        fielder->isJump = 0;
        fielder->clamberStatus = 0;
        fielder->wallSplatStatus = 0;
        fielder->wallActionCurrentHeight = lbl_3_rodata_B20;
        fielder->_0208 = 0;
        fielder->_0209 = 0;
        fielder->someCountDown2 = 0;
        fielder->_020B = 0;
        fielder->_020B_stored = 0;
        fielder->aiDistToStandFromWallCollision = 0;
        fielder->onFire = 0;
        fielder->relatedToStandingStill = 0;
        fielder->_01FE = 0;
        fielder->throwWindUpFrames = 0;
        fielder->needToMoveToCatchThrownBall = 0;
        fielder->knockoutStatus = 0;
        fielder->bodyCheckResult = 0;
        fielder->bodyCheckStatus = 0;
        fielder->always0 = 0;
        fielder->catchAnimation = 0;
        fielder->autoCatch0_noCatchAnimationOnly1 = 0;
        fielder->closingInOnCatchingFlyBall = 0;
        fielder->bobble = 0;
        fielder->action = 0;
        fielder->jumpDiveStateRelated = 0;
        fielder->wallJumpFramesTillTopOfWallContact = 0;
        fielder->wallJumpStatus = 0;
        fielder->wallActionCountDown = 0;
        fielder->runningCatchCountDown = 0;
        fielder->_0263 = 0;
        fielder->runningCatchInd = 0;
        fielder->suctionCatchInd = 0;
        fielder->catchAnimation = 0;
        fielder->AI_Ind = 0;
        g_FieldingLogic.fielderAutoMovementCode[i] = 0;
        fielder->autoFielderInd = 0;

        if (!g_d_GameSettings.minigamesEnabled) {
            setStandingOnBaseVariables(i);

            if (g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam] != 0) {
                fielder->AI_Ind = 1;
            }
            if (g_GameLogic.autoFielding[g_GameLogic.awayTeamBattingInd_battingTeam] != 0) {
                fielder->autoFielderInd = 1;
            }
        }
    }

    if (g_d_GameSettings.minigamesEnabled) {
        s8 idx;
        u8* fp;

        idx = (s8)g_Minigame.minigamePlayerSelectedOrder;
        if (idx >= 0 && g_Minigame.minigameControlStruct[0].battingHandedness[idx] != 0) {
            g_Fielders[0].AI_Ind = 1;
            g_Fielders[0].autoFielderInd = 1;
        } else {
            idx = (s8)g_Minigame.minigameControlStruct[1].aIStrength[2];
            if (idx >= 0 && g_Minigame.minigameControlStruct[0].battingHandedness[idx] != 0) {
                g_Fielders[2].AI_Ind = 1;
                g_Fielders[2].autoFielderInd = 1;
            }
        }

        fp = (u8*)g_Fielders;
        idx = (s8)g_Minigame.minigameControlStruct[1].aIStrength[3];
        if (idx >= 0 && g_Minigame.minigameControlStruct[0].battingHandedness[idx] != 0) {
            fp[0x8fd] = 1;
            fp[0x8fe] = 1;
        }

        fp += 0x4d0;
        idx = (s8)g_Minigame.minigameControlStruct[1]._14;
        if (idx >= 0 && g_Minigame.minigameControlStruct[0].battingHandedness[idx] != 0) {
            fp[0x695] = 1;
            fp[0x696] = 1;
        }

        fp += 0x268;
        idx = (s8)g_Minigame.minigameControlStruct[1]._15;
        if (idx >= 0 && g_Minigame.minigameControlStruct[0].battingHandedness[idx] != 0) {
            fp[0x695] = 1;
            fp[0x696] = 1;
        }
    }

    {
        FielderDash* dash;

        g_FieldingLogic.fielderAssignedLocationIndex[0] = -1;
        g_FieldingLogic.baseCoveredInd[0] = 0;
        g_FieldingLogic.fielderAssignedLocationIndex[1] = -1;
        g_FieldingLogic.baseCoveredInd[1] = 0;
        g_FieldingLogic.fielderAssignedLocationIndex[2] = -1;
        g_FieldingLogic.baseCoveredInd[2] = 0;
        g_FieldingLogic.fielderAssignedLocationIndex[3] = -1;
        g_FieldingLogic.baseCoveredInd[3] = 0;
        g_FieldingLogic.fielderAssignedLocationIndex[4] = -1;
        g_FieldingLogic.playerAtMoundCutoffLocation = 0;
        g_FieldingLogic.selectedFielder = -1;
        g_FieldingLogic.secondaryFielder = -1;
        g_FieldingLogic.tertiaryFielder = -1;
        g_FieldingLogic.someFielderIndex = -1;
        g_FieldingLogic.cutoffFielderIndex = -1;
        g_FieldingLogic.interceptThrowFielder = -1;
        g_FieldingLogic.locationThrownTo = -1;
        g_FieldingLogic.humanSelectedPlaceToThrow = -1;
        g_FieldingLogic.locThrownTo2 = -1;
        g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
        g_FieldingLogic.fielderAssignedLocationIndex[5] = 0;
        g_FieldingLogic.runnerChasingAfter = -1;
        g_FieldingLogic.fielderAssignedLocationIndex[6] = -1;
        g_FieldingLogic.someBase = -1;
        g_FieldingLogic.runnerBeingTargettedForOut = -1;
        g_FieldingLogic.lastThrowingFielder = -1;
        g_FieldingLogic.framesRunnerIsOutBy = 0;
        g_FieldingLogic.throwWindupFrames = 0;
        g_FieldingLogic.fieldersWhoCanCatchBall_bitIndicators = 0;
        g_FieldingLogic.liveBallBcOfPickoffOrStealCd = 0;
        g_FieldingLogic.infieldFlyIndicator = 0;
        g_FieldingLogic.throwWindupAnimationDoneInd = 0;
        g_FieldingLogic.tagAnimationType = 0;
        g_FieldingLogic._010d = 0;
        g_FieldingLogic.processErrorCode = 0;
        g_FieldingLogic.fielderActionBeingProcessed = 0;
        g_FieldingLogic.bodyCheckResult = 0;
        g_FieldingLogic.pitcher_inPitchingState = 1;
        g_FieldingLogic.catcherNotFocusedOnRunnerScoring = 1;
        g_FieldingLogic.unused_always0 = 0;
        g_FieldingLogic.always0_ = 0;
        g_FieldingLogic.quickThrowInd = 0;
        g_FieldingLogic._0120 = 0;
        g_FieldingLogic.fielderActionBeingProcessed_prev = -1;
        g_FieldingLogic.throwSpeedType = 0;
        g_FieldingLogic._011d = 0;
        g_FieldingLogic.const_neg1 = -1;
        g_FieldingLogic._0122 = 0;
        g_FieldingLogic.tagAnimationCountdown = 0;
        g_FieldingLogic.baseFielderIsOn = -1;
        g_FieldingLogic.runnerTargetedOnThrowDuringSteal = -1;
        g_FieldingLogic.x127_pickoff_0 = 0;
        g_FieldingLogic.someCountDown = 0;
        g_FieldingLogic.always0_012b = 0;
        g_FieldingLogic.ballWontBeControlledByFielderAnytimeSoonInd = 0;
        g_FieldingLogic.smash0_normalThrow1 = 1;
        g_FieldingLogic.stickAngleClassification = 0;
        g_FieldingLogic.framesControlStickPointedInCertainQuadrant = 0;
        g_FieldingLogic._0132 = 0;
        g_FieldingLogic._0131 = 0;
        g_FieldingLogic.someRunnerNum = -1;
        g_FieldingLogic.bigPlayPotential = 0;
        g_FieldingLogic.tagOutFirstFrameInd = 0;
        g_FieldingLogic._0138 = 0;
        g_FieldingLogic.unkFlagMaybeInAir = 0;
        g_FieldingLogic.infielderSelectedOnPopFlyInd = 0;
        g_FieldingLogic.knockoutFinished = 0;
        g_FieldingLogic.bodyCheckResult2 = 0;
        g_FieldingLogic.bodyCheckStageCountdown = 0;
        g_FieldingLogic.throwWaitingInd = 0;
        g_FieldingLogic.IsChemistryThrow = 0;
        g_FieldingLogic.laser_1 = 0;
        g_FieldingLogic._0142 = 0;
        g_FieldingLogic.laser_2 = 0;
        g_FieldingLogic.unused_always0_ = 0;
        g_FieldingLogic.bigPlayFielderIndex = -1;
        g_FieldingLogic.smashThrow_framesDirectionHeld = 0;
        g_FieldingLogic.FrameCycleCounter_20 = 0;
        g_FieldingLogic.someFrameCounterFielderRelated = 0;

        g_FieldingLogic.dashPtr = (FielderDash*)g_FieldingLogic.fielderDashByPort;
        g_FieldingLogic.jumpDiveStruct = &g_FieldingLogic.specialActionChecks;
        g_AiLogic.AIControlFlag = 0;

        dash = g_FieldingLogic.dashPtr;
        dash->framesSinceLastDashInput = -1;
        dash->sprintLengthInFrames = -1;
        dash->chargeLevel = 0;
        dash->sprintLengthInFramesStored = 0;
        dash->dashingFielderIndex = -1;
        dash->sprintingState = 0;
        dash++;
        dash->framesSinceLastDashInput = -1;
        dash->sprintLengthInFrames = -1;
        dash->chargeLevel = 0;
        dash->sprintLengthInFramesStored = 0;
        dash->dashingFielderIndex = -1;
        dash->sprintingState = 0;
        dash++;
        dash->framesSinceLastDashInput = -1;
        dash->sprintLengthInFrames = -1;
        dash->chargeLevel = 0;
        dash->sprintLengthInFramesStored = 0;
        dash->dashingFielderIndex = -1;
        dash->sprintingState = 0;
    }

    for (i = 0; i < 20; i++) {
        fielderControlStick_continuousAngleHistory[i] = -1;
    }

    currentStickDirection = -1;

    if (!g_d_GameSettings.minigamesEnabled) {
        int team = g_GameLogic.awayTeamBattingInd_battingTeam;

        if (g_GameLogic.battingOrderAndPositionMapping[team][0][0] >= 9) {
            if (g_GameLogic.battingOrderAndPositionMapping[team][0][1] >= 0x14) {
                g_GameLogic.battingOrderAndPositionMapping[team][0][1] -= 0x14;
            } else if (g_GameLogic.battingOrderAndPositionMapping[team][0][1] >= 0xa) {
                g_GameLogic.battingOrderAndPositionMapping[team][0][1] -= 0xa;
            }
        }

        g_Pitcher.unused_pitcherIsFielder = 0;
    }
}

// .text:0x00058E50 size:0x108 mapped:0x80697EE4
void initializeMiniGameCharacters(void) {
    int i;
    s8 charId;
    int idx;
    InMemFielder* fielder;

    g_GameLogic.rosterLoc_skippingCap = 0;
    if (g_d_GameSettings.minigamesEnabled) {
        for (i = 0; i < 4; i++) {
            charId = *((s8*)&g_Minigame + 0x18f4 + i);
            if (charId < 0) {
                continue;
            }
            idx = (charId == (s8)g_Minigame.minigamePlayerSelectedOrder) ? 0 : (i + 2);
            setFielderValues(charId, idx);
            fielder = &g_Fielders[idx];
            if (idx == 0) {
                fielder->lockoutDuration = fielderLockout[*((u8*)&g_Minigame + 0x18d8 + i)][0];
            } else {
                fielder->lockoutDuration = fielderLockout[*((u8*)&g_Minigame + 0x18d8 + i)][7];
            }
        }
    }
}

extern VecXZ fieldingStartingCoords_regular[9];
extern VecXZ base_MoundCoordinates[5];
extern VecXZ fielderStartingCoords_bunt[4];
extern VecXZ fielderStartingCoords_holdRunners[4][3];
extern VecXZ lbl_3_data_45D4[4];

// .text:0x00058F58 size:0x254 mapped:0x80697FEC
void fielding_setStartingCoordinates(int fielderIndex, f32* outX, f32* outZ) {
    int useBunt = 0;
    int holdRunnersSlot;

    if (g_Pitcher.pitchTotalTimeCounter <= 0) {
        holdRunnersSlot = 1;
    } else {
        holdRunnersSlot = 2;
    }

    if (fielderIndex <= 1) {
        *outX = fieldingStartingCoords_regular[fielderIndex].x;
        *outZ = fieldingStartingCoords_regular[fielderIndex].z;
        return;
    }

    if (fielderIndex <= 5) {
        int holdIndex;

        if (g_Runners[1].runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE &&
            g_Runners[1].furthestBaseForcedToGoToOnWalk != 0 &&
            g_Ball.pitchHangtimeCounter > 0 &&
            g_Pitcher.framesUntilUnhittable < 15) {
            u8 batterHand = g_Batter.batterHand;
            if (batterHand == 0 && fielderIndex == 3) {
                *outX = base_MoundCoordinates[2].x;
                *outZ = base_MoundCoordinates[2].z;
                return;
            }
            if (batterHand != 0 && fielderIndex == 5) {
                *outX = base_MoundCoordinates[2].x;
                *outZ = base_MoundCoordinates[2].z;
                return;
            }
        }

        holdIndex = 0;

        if (g_Pitcher.pitchTotalTimeCounter > 30) {
            if (fielderIndex == 2 || fielderIndex == 4) {
                u8 buntStatus = g_Batter.buntStatus;
                if (buntStatus >= 1 && buntStatus <= 3) {
                    useBunt = 1;
                }
            }
        }

        if ((fielderIndex == 2 && g_Runners[1].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) ||
            (fielderIndex == 4 && g_Runners[3].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD)) {
            holdIndex = holdRunnersSlot;
        }

        if (g_Runners[2].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
            if (fielderIndex == 3) {
                if (g_Batter.batterHand == BATTING_HAND_RIGHT) {
                    g_FieldingLogic.whosHoldingOnRunnerAt2nd = 0;
                    holdIndex = holdRunnersSlot;
                }
            }
            if (fielderIndex == 5) {
                if (g_Batter.batterHand == BATTING_HAND_LEFT) {
                    g_FieldingLogic.whosHoldingOnRunnerAt2nd = 1;
                    holdIndex = holdRunnersSlot;
                }
            }
        }

        if (useBunt) {
            *outX = fielderStartingCoords_bunt[fielderIndex - 2].x;
            *outZ = fielderStartingCoords_bunt[fielderIndex - 2].z;
            return;
        }

        *outX = fielderStartingCoords_holdRunners[fielderIndex - 2][holdIndex].x;
        *outZ = fielderStartingCoords_holdRunners[fielderIndex - 2][holdIndex].z;
        return;
    }

    *outX = lbl_3_data_45D4[fielderIndex - 6].x;
    *outZ = lbl_3_data_45D4[fielderIndex - 6].z;
}

// .text:0x000591AC size:0x18C mapped:0x80698240
void pPRelated(void) {
    int i;
    InMemFielder* fielder;
    f32 outX;
    f32 outZ;

    for (i = 0; i < 9; i++) {
        fielder = &g_Fielders[i];

        if (g_GameLogic.pre_PostMiniGameInd != 0) {
            fielding_setStartingCoordinates(i, &outX, &outZ);
            fielder->pos.x = outX;
            fielder->pos.z = outZ;
        }

        fielder->IntendedLocation.x = lbl_3_rodata_B20;
        fielder->IntendedLocation.y = lbl_3_rodata_B20;
        fielder->IntendedLocation.z = lbl_3_rodata_B20;
        fielder->velocityX = lbl_3_rodata_B20;
        fielder->velocityZ = lbl_3_rodata_B20;
        fielder->posXLastFrame = fielder->pos.x;
        fielder->posZLastFrame = fielder->pos.z;
        fielder->currentVelocity = lbl_3_rodata_B20;
        fielder->goingToAutoLocationInd = 0;
        fielder->baseCurrentlyOn = -1;
        fielder->onFire = 0;
        outX = -fielder->pos.x;
        outZ = -fielder->pos.z;
        fielder->desiredMovementDirection = ATAN2F(outZ, outX);
    }

    if (g_GameLogic.pre_PostMiniGameInd != 0) {
        for (i = 0; i < 9; i++) {
            fielder = &g_Fielders[i];
            fielding_setStartingCoordinates(i, &fielder->pos.x, &fielder->pos.z);
            fielder->pos.y = lbl_3_rodata_B20;
        }
    }

    if (g_Runners[1].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
        g_Fielders[2].locationResponsibleForCovering = 1;
        g_Fielders[2].isResponsibleForCoveringALocation = 1;
        g_Fielders[2].baseCurrentlyOn = 1;
        g_FieldingLogic.fielderAssignedLocationIndex[1] = 2;
        g_FieldingLogic.baseCoveredInd[1] = 1;
    }
}

// .text:0x00059338 size:0x28C mapped:0x806983CC
void resetInMemFielders(void) {
    int i;
    int team;
    int position;
    u8 aiIndex;
    s32 diff;
    s32 value;
    InMemFielder* fielder;

    for (i = 1; i <= 9; i++) {
        position = g_GameLogic
                       .battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][i][1];
        if (position >= 0x14) {
            g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][i][1] =
                position - 0x14;
        } else if (position >= 0xa) {
            g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][i][1] =
                position - 0xa;
        }
    }

    g_GameLogic.rosterLoc_skippingCap = 0;
    team = g_GameLogic.awayTeamBattingInd_battingTeam;
    for (i = 0; i < 10; i++) {
        position = g_GameLogic.battingOrderAndPositionMapping[team][i][1];
        if (position <= 8) {
            setFielderValues(g_GameLogic.battingOrderAndPositionMapping[team][i][0], position);
        }
    }

    for (i = 0; i < 9; i++) {
        aiIndex = g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam];
        fielder = &g_Fielders[i];
        fielder->lockoutDuration = fielderLockout[aiIndex][i];
        if (aiIndex != 0) {
            diff = (s32)lbl_3_data_470C[1] - (s32)lbl_3_data_470C[0];
            value = lbl_3_data_470C[0] +
                    (s32)((f32)diff * g_AiLogic.aIDifficultyMultiplierArray[g_GameLogic.homeTeamBattingInd_fieldingTeam]);
            if (i <= 1) {
                fielder->lockoutDuration += value / 2;
            } else {
                fielder->lockoutDuration += value;
            }
        }
    }

    for (i = 0; i < 9; i++) {
        fielder = &g_Fielders[i];
        fielder->unused_initSomeDugoutBehaviour = 0;
        fielder->standingStillInd = 0;
        fielder->atDugoutAtEndOfInning = 0;
        fielder->attachedKlaptrapCount = 0;
    }
}

// .text:0x000595C4 size:0x134 mapped:0x80698658
extern const f32 lbl_3_rodata_CC4;
extern const f64 lbl_3_rodata_B58;

void initializeFielderConstants(void) {
    int i;
    InMemFielder* fielder;
    FielderDash* dash;

    setDefaultInMemFielder();

    for (i = 0; i < 9; i++) {
        g_FieldingLogic.fielderAutoMovementCode[i] = 0;
        fielder = &g_Fielders[i];

        fielder->movementSpeedFactor = 100;
        fielder->joggingSpeed = lbl_3_rodata_CC4 * (f32)fielder->movementSpeedFactor + lbl_3_rodata_B24;
        fielder->modifiedThrowingArm = 0x78;
        fielder->lockoutDuration = 0xa;
        fielder->maxAccLength_ConstF = 0xf;
        fielder->runningAccelerationFactor = fielder->joggingSpeed / (f32)fielder->maxAccLength_ConstF;
        fielder->autoMovementFunctionIndex = 0;
        fielder->goingToAutoLocationInd = 0;
        fielder->unused_initSomeDugoutBehaviour = 0;
        fielder->standingStillInd = 0;
        fielder->_0219 = 1;
        fielder->rosterLocation = -1;
    }

    g_FieldingLogic.selectedFielder = -1;
    dash = (FielderDash*)&g_FieldingLogic;
    dash->sprintSpeedMultiplier = lbl_3_rodata_B60;
    dash->sprintSpeedMultiplier = lbl_3_rodata_B60;
    dash->sprintSpeedMultiplier = lbl_3_rodata_B60;
    g_FieldingLogic.secondaryFielder = -1;
    g_FieldingLogic.tertiaryFielder = -1;
    g_FieldingLogic.selectedFielder_stored = -1;
    g_FieldingLogic.secondaryFielderStored = -1;
    g_FieldingLogic.tertiaryFielderStored = -1;
    g_FieldingLogic.cutoffFielderIndex = -1;
    g_FieldingLogic._0136 = 1;
    g_FieldingLogic.always0_0137 = 0;
    g_FieldingLogic.dashPtr = (FielderDash*)&g_FieldingLogic;
    g_FieldingLogic.jumpDiveStruct = &g_FieldingLogic.specialActionChecks;
    dash->sprintSpeedMultiplier = lbl_3_rodata_B60;
}

// .text:0x000596F8 size:0x164 mapped:0x8069878C
void initFielders(void) {
    int i;
    int team;
    int position;
    u8 aiIndex;
    s32 diff;
    s32 value;
    InMemFielder* fielder;

    g_GameLogic.rosterLoc_skippingCap = 0;
    team = g_GameLogic.awayTeamBattingInd_battingTeam;

    for (i = 0; i < 10; i++) {
        position = g_GameLogic.battingOrderAndPositionMapping[team][i][1];
        if (position <= 8) {
            setFielderValues(g_GameLogic.battingOrderAndPositionMapping[team][i][0], position);
        }
    }

    for (i = 0; i < 9; i++) {
        aiIndex = g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam];
        fielder = &g_Fielders[i];
        fielder->lockoutDuration = fielderLockout[aiIndex][i];
        if (aiIndex != 0) {
            diff = (s32)lbl_3_data_470C[1] - (s32)lbl_3_data_470C[0];
            value = lbl_3_data_470C[0] +
                    (s32)((f32)diff * g_AiLogic.aIDifficultyMultiplierArray[g_GameLogic.homeTeamBattingInd_fieldingTeam]);
            if (i <= 1) {
                fielder->lockoutDuration += value / 2;
            } else {
                fielder->lockoutDuration += value;
            }
        }
    }
}

