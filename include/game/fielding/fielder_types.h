#ifndef __FIELDER_TYPES_H_
#define __FIELDER_TYPES_H_

/* Fielder state: InMemFielder / g_Fielders, g_FieldingLogic (with FielderDash),
 * specialFielderActionConstants and the fielding enums. Included from
 * game/UnknownHomes_Game.h at the point g_FieldingLogic used to sit, so every
 * existing include keeps working. FIELDING_POSITION and FIELDING_ABILITY stay
 * where they were with the other shared enums. */

#include "mssbTypes.h"

typedef struct {
    /*0x00*/ s32 const0;
    /*0x04*/ s32 const_00;
    /*0x08*/ f32 sprintSpeedMultiplier;
    /*0x0c*/ s16 framesSinceLastDashInput;
    /*0x0e*/ s16 sprintLengthInFrames;
    /*0x10*/ s16 chargeLevel;
    /*0x12*/ s16 sprintLengthInFramesStored;
    /*0x14*/ s16 dashingFielderIndex;
    /*0x16*/ s16 numberOfDashInputs;
    /*0x18*/ s16 postSprintSlowdownTimer;
    /*0x1a*/ u8 sprintingState;
} FielderDash; // size: 0x1c

typedef struct {
    /*0x0000*/ FielderDash fielderDashByPort[4];
    /*0x0070*/ FielderDash* dashPtr;
    /*0x0074*/ UnkInputRelated specialActionChecks;
    /*0x007c*/ u8 _007c;
    /*0x007d*/ u8 _007d;
    /*0x007e*/ u8 _007e;
    /*0x007f*/ u8 pad2[3];
    /*0x0082*/ u8 _0082;
    /*0x0083*/ u8 pad3[5];
    /*0x0088*/ u8 _0088[4];
    /*0x008c*/ UnkInputRelated* jumpDiveStruct;
    /*0x0090*/ VecXYZ tagDirection;
    /*0x009c*/ u8 _009c[16];
    /*0x00ac*/ u8 _00ac;
    /*0x00ad*/ u8 _00ad;
    /*0x00ae*/ s16 playOverCounter;
    /*0x00b0*/ s16 selectedFielder;
    /*0x00b2*/ s16 secondaryFielder;
    /*0x00b4*/ s16 tertiaryFielder;
    /*0x00b6*/ s16 selectedFielder_stored;
    /*0x00b8*/ s16 secondaryFielderStored;
    /*0x00ba*/ s16 tertiaryFielderStored;
    /*0x00bc*/ s16 someFielderIndex;
    /*0x00be*/ s16 cutoffFielderIndex;
    /*0x00c0*/ s16 cutoffReassignCooldown; // 90 after demoteCutoffToInfieldSupport; no new cutoff while nonzero
    /*0x00c2*/ s16 interceptThrowFielder;
    /*0x00c4*/ E(s16, COVER_LOCATION) locationThrownTo;          // COVER_LOCATION, or 8: hold the ball (throwWaitingInd)
    /*0x00c6*/ E(s16, COVER_LOCATION) humanSelectedPlaceToThrow; // as locationThrownTo
    /*0x00c8*/ s16 someHumanThrowFrameCounter;
    /*0x00ca*/ E(s16, COVER_LOCATION) locThrownTo2;
    /*0x00cc*/ s16 somethingForTryingTagOutTargetBase;
    /*0x00ce*/ s16 xcc_Stored_0;
    /*0x00d0*/ s16 fielderAssignedLocationIndex[5]; // fielder covering each location: bases (COVER_LOCATION_HOME..THIRD), mound (COVER_LOCATION_MOUND, held by the COVER_LOCATION_MOUND_CUTOFF fielder)
    /*0x00da*/ s16 fielderSelectionChangeCooldown; // frames before the human's fielder auto-switches again (set to 20/45)
    /*0x00dc*/ s16 tagChaseFromBase;              // base the ball holder chases a runner from (-1 if none)
    /*0x00de*/ s16 runnerChasingAfter;
    /*0x00e0*/ s16 runnerChasingAfter_stored;
    /*0x00e2*/ s16 someBase;
    /*0x00e4*/ s16 framesSince3rdOutWasMade;
    /*0x00e6*/ s16 throwWindUpFrameCounter;
    /*0x00e8*/ s16 runnerBeingTargettedForOut;
    /*0x00ea*/ s16 lastThrowingFielder;
    /*0x00ec*/ s16 framesRunnerIsOutBy;
    /*0x00ee*/ s16 framesSincePlayEnded;
    /*0x00f0*/ s16 throwWindupFrames;
    /*0x00f2*/ s16 fieldersWhoCanCatchBall_bitIndicators;
    /*0x00f4*/ s16 someRunnerNum;
    /*0x00f6*/ s16 bodyCheckStageCountdown;
    /*0x00f8*/ u8 fielderAutoMovementCode[9];
    /*0x0101*/ u8 baseCoveredInd[4]; // by COVER_LOCATION_HOME..THIRD
    /*0x0105*/ u8 playerAtMoundCutoffLocation;
    /*0x0106*/ u8 throwSpeedType;
    /*0x0107*/ E(u8, PICKOFF_STEAL_CODE) liveBallReason;
    /*0x0108*/ u8 infieldFlyIndicator;
    /*0x0109*/ u8 birdoFarThrowInd_forAnimation;
    /*0x010a*/ u8 throwWindupAnimationDoneInd;
    /*0x010b*/ u8 someThrowSpeedIncreaseInd;
    /*0x010c*/ u8 _010c;
    /*0x010d*/ u8 _010d;
    /*0x010e*/ u8 playOverInd;
    /*0x010f*/ u8 unused_always0__;
    /*0x0110*/ u8 hasProcessedFoulBall;
    /*0x0111*/ E(u8, FIELDER_TAG_TYPE) fielderTagType;
    /*0x0112*/ u8 tagResult_1out_2safe;
    /*0x0113*/ u8 processErrorCode;
    /*0x0114*/ u8 fielderActionBeingProcessed;
    /*0x0115*/ s8 fielderActionBeingProcessed_prev;
    /*0x0116*/ u8 bodyCheckResult;
    /*0x0117*/ u8 pitcher_inPitchingState;
    /*0x0118*/ u8 catcherNotFocusedOnRunnerScoring;
    /*0x0119*/ u8 setThrowSpeedTypeTo9Ind;
    /*0x011a*/ u8 unused_always0;
    /*0x011b*/ u8 index_runnerAttemptingBodycheck;
    /*0x011c*/ u8 always0_;
    /*0x011d*/ u8 _011d;
    /*0x011e*/ u8 whosHoldingOnRunnerAt2nd;
    /*0x011f*/ u8 quickThrowInd;
    /*0x0120*/ u8 _0120;
    /*0x0121*/ s8 const_neg1;
    /*0x0122*/ u8 _0122;
    /*0x0123*/ u8 letFoulBallDropIfWinningRunOn3rdInd;
    /*0x0124*/ u8 tagAnimationCountdown;
    /*0x0125*/ s8 baseFielderIsOn;
    /*0x0126*/ s8 runnerTargetedOnThrowDuringSteal;
    /*0x0127*/ s8 x127_pickoff_0; // PICKOFF_TARGET_STATUS
    /*0x0128*/ u8 canEndPlayOnLooseBallInd;
    /*0x0129*/ u8 always0__;
    /*0x012a*/ u8 someCountDown;
    /*0x012b*/ u8 always0_012b;
    /*0x012c*/ u8 ballWontBeControlledByFielderAnytimeSoonInd;
    /*0x012d*/ u8 smash0_normalThrow1;
    /*0x012e*/ u8 stickAngleClassification;
    /*0x012f*/ u8 framesControlStickPointedInCertainQuadrant;
    /*0x0130*/ u8 throwWaitingInd;
    /*0x0131*/ u8 _0131;
    /*0x0132*/ u8 errorTypeCd; // FIELDING_ERROR_TYPE
    /*0x0133*/ u8 bigPlayPotential;
    /*0x0134*/ s8 bigPlayFielderIndex;
    /*0x0135*/ u8 tagOutFirstFrameInd;
    /*0x0136*/ u8 _0136;
    /*0x0137*/ u8 always0_0137;
    /*0x0138*/ u8 _0138;
    /*0x0139*/ u8 secondaryFielderActiveInd; // set when the initial selection also gave a secondary/tertiary fielder
    /*0x013a*/ E(u8, BOOL) infielderSelectedOnPopFlyInd;
    /*0x013b*/ u8 knockoutFinished;
    /*0x013c*/ u8 throwInterceptionTriggered;
    /*0x013d*/ u8 smashThrowInd;
    /*0x013e*/ u8 IsChemistryThrow;
    /*0x013f*/ u8 bodyCheckResult2;
    /*0x0140*/ u8 laserThrowInFlight;
    /*0x0141*/ u8 lastThrowWasLaser;
    /*0x0142*/ u8 _0142;
    /*0x0143*/ u8 unused_always0_;
    /*0x0144*/ u8 _0144;
    /*0x0145*/ u8 smashThrow_framesDirectionHeld;
    /*0x0146*/ u8 FrameCycleCounter_20;
    /*0x0147*/ u8 _0147;
    /*0x0148*/ E(u16, INPUT_BUTTON) fielderInputs;
    /*0x014a*/ E(u16, INPUT_BUTTON) fielderInputsLatestFrame;
    /*0x014c*/ s16 unused_fielderControls0x8;
    /*0x014e*/ u8 _014e;
    /*0x014f*/ u8 _014f;
} g_FieldingLogic_s; // size 0x150

extern g_FieldingLogic_s g_FieldingLogic;

// g_FieldingLogic.liveBallReason
typedef enum _PICKOFF_STEAL_CODE {
    /* 0x0 */ PICKOFF_STEAL_CODE_NONE,
    /* 0x1 */ PICKOFF_STEAL_CODE_PICKOFF,
    /* 0x2 */ PICKOFF_STEAL_CODE_STEAL,
    /* 0x3 */ PICKOFF_STEAL_CODE_UNUSED_3, // never set; reads suggest wild pitch / passed ball
    /* 0x4 */ PICKOFF_STEAL_CODE_UNUSED_4, // never set; reads suggest dropped third strike
} PICKOFF_STEAL_CODE;

// g_FieldingLogic.fielderTagType: the kind of tag the fielder with the ball is making.
typedef enum _FIELDER_TAG_TYPE {
    /* 0 */ FIELDER_TAG_NONE,
    /* 1 */ FIELDER_TAG_BASE_ON_SLIDE, // on the bag as the runner slides/body checks in
    /* 2 */ FIELDER_TAG_RUNNING,       // runner in the basepath; fielder keeps chasing
    /* 3 */ FIELDER_TAG_UNUSED_3,      // never set; chase code treats it like RUNNING
    /* 4 */ FIELDER_TAG_UNUSED_4,      // never set; chase code eases in to reach the runner as the out timer ends
    /* 5 */ FIELDER_TAG_STANDING,
    /* 6 */ FIELDER_TAG_BODY_CHECK_FAILED,
    /* 7 */ FIELDER_TAG_BODY_CHECK_WON,
} FIELDER_TAG_TYPE;

// g_FieldingLogic.x127_pickoff_0: what became of the runner a pickoff/steal throw targeted.
typedef enum _PICKOFF_TARGET_STATUS {
    /* -1  */ PICKOFF_TARGET_STATUS_NONE = -1,
    /* 0x0 */ PICKOFF_TARGET_STATUS_ONGOING,
    /* 0x1 */ PICKOFF_TARGET_STATUS_PICKED_OFF_RUNNER_ADVANCED,
    /* 0x2 */ PICKOFF_TARGET_STATUS_STEALING_RUNNER_ADVANCED,
} PICKOFF_TARGET_STATUS;

// g_FieldingLogic.processErrorCode. A late throw on runner n is
// FIELDING_ERROR_PENDING_LATE_THROW_R0 + n.
typedef enum _FIELDING_ERROR {
    /* 0x0 */ FIELDING_ERROR_NONE,
    /* 0x1 */ FIELDING_ERROR_PENDING_DROPPED_FLY,
    /* 0x2 */ FIELDING_ERROR_PENDING_GROUNDBALL,
    /* 0x3 */ FIELDING_ERROR_PENDING_LATE_THROW_R0,
    /* 0x9 */ FIELDING_ERROR_CONFIRMED = 9,
} FIELDING_ERROR;

// g_FieldingLogic.errorTypeCd
typedef enum _FIELDING_ERROR_TYPE {
    /* 0x0 */ FIELDING_ERROR_TYPE_NONE,
    /* 0x1 */ FIELDING_ERROR_TYPE_DROPPED_FLY,
    /* 0x2 */ FIELDING_ERROR_TYPE_GROUNDBALL,
    /* 0x3 */ FIELDING_ERROR_TYPE_FAILED_RUNDOWN,
} FIELDING_ERROR_TYPE;

// symbols.txt: g_Fielders size 0x15A8 == 9 * 0x268 -- matches this exactly.
typedef struct _InMemFielder {
    /*0x000*/ VecXYZ pos;
    /*0x00C*/ f32 actionYOffset;
    /*0x010*/ f32 storedPosY;
    /*0x014*/ VecXYZ IntendedLocation;
    /*0x020*/ f32 ballTrackingTargetX; // last ball-tracking target; 10000 = none (resetFielderSelection)
    /*0x024*/ f32 ballTrackingTargetZ;
    /*0x028*/ f32 xPos5mAwayFromBallsCollisionSpotOnWall;
    /*0x02C*/ f32 zPos5mAwayFromBallsCollisionSpotOnWall;
    /*0x030*/ f32 velocityX;
    /*0x034*/ f32 velocityZ;
    /*0x038*/ f32 xMovementDir;
    /*0x03C*/ f32 zMovementDir;
    /*0x040*/ f32 velocityXPrev;
    /*0x044*/ f32 velocityZPrev;
    /*0x048*/ f32 desiredMovementDirection;
    /*0x04C*/ f32 desiredMovementDirectionStored;
    /*0x050*/ f32 currentVelocity;
    /*0x054*/ f32 lastFrameVelocityUpToBase;
    /*0x058*/ f32 joggingSpeed;
    /*0x05C*/ f32 runningAccelerationFactor;
    /*0x060*/ f32 unused;
    /*0x064*/ f32 desiredMovementDirection2;
    /*0x068*/ f32 distanceFromAutoLocation;
    /*0x06C*/ f32 wjAngleRelated;
    /*0x070*/ f32 distanceFromHomePlate;
    /*0x074*/ f32 distanceFromBall;
    /*0x078*/ f32 distanceFromBallLastFrame;
    /*0x07C*/ f32 groundDistanceFromBall;
    /*0x080*/ f32 distanceFromLandingSpot;
    /*0x084*/ f32 distanceFromEachFielder[9];
    /*0x0A8*/ f32 distanceToBases[4];
    /*0x0B8*/ f32 distanceToMound;
    /*0x0BC*/ f32 desiredMovementDirectionFPrev1;
    /*0x0C0*/ f32 desiredMovementDirectionFPrev2;
    /*0x0C4*/ f32 desiredMovementDirectionFPrev3;
    /*0x0C8*/ f32 desiredMovementDirectionFPrev4;
    /*0x0CC*/ f32 desiredMovementDirectionFPrev5;
    /*0x0D0*/ f32 unused2;
    /*0x0D4*/ f32 posXLastFrame;
    /*0x0D8*/ f32 posZLastFrame;
    /*0x0DC*/ f32 unused3;
    /*0x0E0*/ f32 unused4;
    /*0x0E4*/ f32 unused5;
    /* Ghidra: Hitbox, 0x24 */
    /*0x0E8*/ f32 hitbox[9];
    /*0x10C*/ VecXYZ throwTarget;
    /*0x118*/ f32 storedPosX;
    /*0x11C*/ f32 storedPosZ;
    /*0x120*/ f32 knockBackRelatedVeloX;
    /*0x124*/ f32 knockbackRelatedVeloZ;
    /*0x128*/ f32 wallActionLocationX;
    /*0x12C*/ f32 wallActionLocationY;
    /*0x130*/ f32 wallactionLocationZ;
    /*0x134*/ f32 wallJumpApexX;
    /*0x138*/ f32 wallJumpApexY;
    /*0x13C*/ f32 wallJumpApexZ;
    /*0x140*/ f32 actionDirectionRadians;
    /*0x144*/ f32 wallActionFacingAngle;
    /*0x148*/ f32 wallActionCurrentHeight;
    /*0x14C*/ f32 wallActionHeightAdjustment;
    /*0x150*/ VecXYZ wallActionVelo;
    /*0x15C*/ f32 jumpY;
    /*0x160*/ VecXYZ jumpVelocity;
    /*0x16C*/ f32 hitbox_barrelCollisions;
    /*0x170*/ f32 unused6;
    /*0x174*/ f32 knockOutVelo;
    /*0x178*/ s16 rosterLocation;
    /*0x17A*/ s16 CharID;
    /*0x17C*/ s16 unused_missionRelated;
    /*0x17E*/ s16 numFramesToGetToAutoLocation;
    /*0x180*/ s16 playerAngleFromHome;
    /*0x182*/ s16 angleOfFieldersStartingPosition;
    /*0x184*/ s16 framesRemainingToGetToLandingSpot;
    /*0x186*/ s16 framesToGetToBallLandingSpot;
    /*0x188*/ s16 _0188;
    /*0x18A*/ s16 aiDistToStandFromWallCollision;
    /*0x18C*/ E(s16, COVER_LOCATION) locationResponsibleForCovering;
    /*0x18E*/ s16 baseCuttoffIsTargeting;
    /*0x190*/ s16 presetLocationCategory;
    /*0x192*/ s16 throwWindupEstimate;
    /*0x194*/ s16 framesSinceThrowWasMade;
    /*0x196*/ s16 const_60;
    /*0x198*/ s16 _0198;
    /*0x19A*/ s16 runningAngle;
    /*0x19C*/ s16 fielderReadiness;
    /*0x19E*/ s16 movementAngle;
    /*0x1A0*/ s16 framesSinceStartedMoving;
    /*0x1A2*/ s16 movingFramesCounter; // counts up while moving; when stopped, capped at 45 and counts down
    /*0x1A4*/ s16 unknown_writeOnly_always0;
    /*0x1A6*/ s16 unused_rngValueRelatedToDugoutLocation;
    /*0x1A8*/ s16 someCountDown;
    /*0x1AA*/ s16 someCounter;
    /*0x1AC*/ s16 timeSinceThrowWasCaught;
    /*0x1AE*/ s16 jumpCountDown;
    /*0x1B0*/ s16 jumpApexFrame;
    /*0x1B2*/ s16 specialActionCountdown;
    /*0x1B4*/ s16 wallSplatStageCountDown;
    /*0x1B6*/ s16 someCountDown2;
    /*0x1B8*/ s16 onFireCountUp;
    /*0x1BA*/ s16 onFireCountdown;
    /*0x1BC*/ s16 onFireFacingAngle;
    /*0x1BE*/ s16 knockOutCountUp;
    /*0x1C0*/ s16 knockOutCountDown;
    /*0x1C2*/ s16 knockOutAngle;
    /*0x1C4*/ u8 AILevel3Weak0Powerful;
    /*0x1C5*/ u8 AI_Ind;
    /*0x1C6*/ u8 autoFielderInd;
    /*0x1C7*/ u8 throwingHandedness;
    /*0x1C8*/ E(u8, CHARACTER_CLASS) characterClass;
    /*0x1C9*/ u8 Weight;
    /*0x1CA*/ u8 ModifiedWeightForMag;
    /*0x1CB*/ u8 wallActionAbility;
    /*0x1CC*/ u8 hasSuperJump;
    /*0x1CD*/ u8 modifiedThrowingArm;
    /*0x1CE*/ u8 throwingArm;
    /*0x1CF*/ u8 movementSpeedFactor;
    /*0x1D0*/ u8 speed;
    /*0x1D1*/ u8 maxAccLength_ConstF;
    /*0x1D2*/ u8 lockoutDuration;
    /*0x1D3*/ E(u8, AUTO_MOVEMENT_FUNCTION_INDEX) autoMovementFunctionIndex;
    /*0x1D4*/ u8 presetLocationToStandAt;
    /*0x1D5*/ u8 writeOnly_stopReason; // never read: 0 on (re)start of movement, 2/3/4 when sent to AUTO_MOVEMENT_STOP_BETWEEN_INSTRUCTIONS (2 outfielder / 3 infielder losing the ball, 4 displaced)
    /*0x1D6*/ u8 fielderVeloAdjustmentCode;
    /*0x1D7*/ E(u8, COVER_ROLE) coverRole;
    /*0x1D8*/ u8 pitcherHeadingToCover1stOr3rd;
    /*0x1D9*/ u8 goingToAutoLocationInd;
    /*0x1DA*/ u8 cantCatchFlyBallInd;
    /*0x1DB*/ u8 nonCatchFlyBallStratInd;
    /*0x1DC*/ E(u8, BALL_TRACKING_TARGET) ballTrackingTarget;
    /*0x1DD*/ E(u8, CATCH_STRATEGY) catchStrategy;
    /*0x1DE*/ E(u8, BASE_PATH) inBasePath;
    /*0x1DF*/ u8 fielderMadeThrow;
    /*0x1E0*/ u8 always0_;
    /*0x1E1*/ u8 _01E1;
    /*0x1E2*/ u8 lockedOutInd;
    /*0x1E3*/ u8 standingStillInd;
    /*0x1E4*/ u8 _01E4;
    /*0x1E5*/ u8 animationRelated;
    /*0x1E6*/ u8 terrainOrCollisionRelated;
    /*0x1E7*/ u8 always0_forcePlayRelated;
    /*0x1E8*/ u8 unknown_Unused;
    /*0x1E9*/ u8 playerNeedsToMoveToCatchThrowInd;
    /*0x1EA*/ u8 unused_alwaysSetTo0;
    /*0x1EB*/ u8 _01EB;
    /*0x1EC*/ u8 animationRelatedInd;
    /*0x1ED*/ u8 animatingActionInd;
    /*0x1EE*/ u8 hitKnockbackCountdown;
    /*0x1EF*/ u8 stunFramesOnFireBall;
    /*0x1F0*/ u8 unused_jumpActiveOrRunningCatchRelated;
    /*0x1F1*/ u8 unused_initSomeDugoutBehaviour;
    /*0x1F2*/ u8 _01F2;
    /*0x1F3*/ u8 runningVsLookingAngleCode;
    /*0x1F4*/ u8 _01F4;
    /*0x1F5*/ s8 baseCurrentlyOn;
    /*0x1F6*/ u8 baseOnLastFrame;
    /*0x1F7*/ s8 baseOn2;
    /*0x1F8*/ E(u8, FIELDER_ZONE) outFieldZoneCode;
    /*0x1F9*/ u8 _01F9;
    /*0x1FA*/ u8 atDugoutAtEndOfInning;
    /*0x1FB*/ u8 _01FB;
    /*0x1FC*/ u8 wallActionFacingAngleInd;
    /*0x1FD*/ u8 relatedToStandingStill;
    /*0x1FE*/ u8 _01FE;
    /*0x1FF*/ u8 fielderTrackingBallState;
    /*0x200*/ u8 _0200;
    /*0x201*/ u8 fielderIsInitialOutfielderSelectedInd;
    /*0x202*/ u8 cutoffWaitingToInterceptThrownBall;
    /*0x203*/ u8 isJump;
    /*0x204*/ u8 jumpCountUp;
    /*0x205*/ u8 clamberStatus;
    /*0x206*/ u8 wjRelated;
    /*0x207*/ u8 wallSplatStatus;
    /*0x208*/ E(u8, MINIGAME_CHASE_TARGET) minigameChaseTarget;
    /*0x209*/ u8 _0209;
    /*0x20A*/ u8 _020A;
    /*0x20B*/ u8 _020B;
    /*0x20C*/ u8 _020B_stored;
    /*0x20D*/ u8 minigamePlayerSlot; // index into the g_Minigame per-player arrays
    /*0x20E*/ u8 _020E;
    /*0x20F*/ u8 onFire;
    /*0x210*/ u8 knockoutStatus;
    /*0x211*/ u8 bodyCheckResult;
    /*0x212*/ u8 bodyCheckStatus;
    /*0x213*/ u8 bodyCheckRunnerNumber;
    /*0x214*/ u8 bodyCheckBase;
    /*0x215*/ u8 throwWindUpFrames;
    /*0x216*/ u8 needToMoveToCatchThrownBall;
    /*0x217*/ u8 attachedKlaptrapCount;
    /*0x218*/ u8 rosterLocSkippingCap;
    /*0x219*/ u8 _0219;
    /*0x21A*/ u8 _021A;
    /*0x21B*/ u8 _021B;
    /*0x21C*/ VecXYZ actionStartingCoordinate;
    /*0x228*/ VecXYZ fielderVelocityDuringAction;
    /*0x234*/ f32 actionEndingCoordinateX;
    /*0x238*/ f32 diveEndingCoordinateY;
    /*0x23C*/ f32 actionEndingCoordinateZ;
    /*0x240*/ f32 xDistToCatch;
    /*0x244*/ f32 zDistToCatch;
    /*0x248*/ f32 distToWhereFlyBallWillBeAtHalfFielderHeight;
    /*0x24C*/ s16 catchAnimationFramesCountDown;
    /*0x24E*/ s16 catchAnimationFramesCountUp;
    /*0x250*/ s16 always0;
    /*0x252*/ E(u8, CATCH_ANIMATION) catchAnimation;
    /*0x253*/ u8 catchVerticalZone;
    /*0x254*/ u8 catchCentreRightLeftOfBody;
    /*0x255*/ u8 catchFastBattedBallInd;
    /*0x256*/ u8 closingInOnCatchingFlyBall;
    /*0x257*/ u8 closingInOnCatchingFlyBall_stored;
    /*0x258*/ u8 bobble;
    /*0x259*/ u8 action;
    /*0x25A*/ u8 jumpDiveStateRelated;
    /*0x25B*/ u8 autoCatch0_noCatchAnimationOnly1;
    /*0x25C*/ u8 wallJumpFramesTillTopOfWallContact;
    /*0x25D*/ u8 wallActionFrameCounter;
    /*0x25E*/ u8 wallJumpStatus;
    /*0x25F*/ u8 wallActionCountDown;
    /*0x260*/ u8 runningCatchInd;
    /*0x261*/ u8 actionAngleType;
    /*0x262*/ u8 runningCatchCountDown;
    /*0x263*/ u8 _0263;
    /*0x264*/ u8 caughtBallInAir;
    /*0x265*/ u8 suctionCatchInd;
    /*0x266*/ u8 _0266;
    /*0x267*/ u8 _0267;
} InMemFielder; // size: 0x268

extern InMemFielder g_Fielders[9];

/* Enum constants the mods use that the decomp had no counterpart for.
   Values from ProjectRio-ASM docs/enum_map.md, which pairs enum to enum by
   member-name and value agreement before matching constants. */
typedef enum _DASH_STATE {
    /* 2 */ DASH_STATE_SPRINTING = 2,
} DASH_STATE;

/* InMemFielder.locationResponsibleForCovering, g_FieldingLogic.locationThrownTo and the index into
 * fielderAssignedLocationIndex[] / baseCoveredInd[] / base_MoundCoordinates[] / distanceToBases[].
 * 0..3 are covered with COVER_ROLE_BASE (autoMovement1_coverBase); 5..15 with COVER_ROLE_SUPPORT
 * (autoMovement14_infieldSupport, which moves the fielder to the spot named here). */
typedef enum _COVER_LOCATION {
    /* -1 */ COVER_LOCATION_NONE = -1,
    /*  0 */ COVER_LOCATION_HOME,
    /*  1 */ COVER_LOCATION_FIRST,
    /*  2 */ COVER_LOCATION_SECOND,
    /*  3 */ COVER_LOCATION_THIRD,
    /*  4 */ COVER_LOCATION_MOUND,               // slot in fielderAssignedLocationIndex / base_MoundCoordinates; never a fielder's location
    /*  5 */ COVER_LOCATION_MOUND_CUTOFF,        // beside the mound (playerAtMoundCutoffLocation); owns fielderAssignedLocationIndex[MOUND]
    /*  6 */ COVER_LOCATION_CUTOFF,              // cutoff man (-> AUTO_MOVEMENT_CUTOFF); L-trigger throw target
    /*  7 */ COVER_LOCATION_PRESET_POSITION,     // back to presetFielderLocations[fielder + 2]
    /*  8 */ COVER_LOCATION_NEAR_HOME_1B_SIDE,   // extendedLocationCoordinates[0] (6, 0); never set
    /*  9 */ COVER_LOCATION_NEAR_HOME_3B_SIDE,   // extendedLocationCoordinates[1] (-6, 0)
    /* 10 */ COVER_LOCATION_NEAR_FIRST,          // extendedLocationCoordinates[2] (20, 27)
    /* 11 */ COVER_LOCATION_NEAR_SECOND_1B_SIDE, // extendedLocationCoordinates[3] (8, 40)
    /* 12 */ COVER_LOCATION_NEAR_SECOND_3B_SIDE, // extendedLocationCoordinates[4] (-8, 40)
    /* 13 */ COVER_LOCATION_NEAR_THIRD,          // extendedLocationCoordinates[5] (-20, 27)
    /* 14 */ COVER_LOCATION_CLEAR_BASEPATH,      // head for the mound until out of the base path (inBasePath == 0)
    /* 15 */ COVER_LOCATION_PITCHER_BACKUP,      // pitcher's spot off the mound picked from the hit angle
} COVER_LOCATION;

/* InMemFielder.coverRole: what kind of location locationResponsibleForCovering holds. */
typedef enum _COVER_ROLE {
    /* 0 */ COVER_ROLE_NONE,
    /* 1 */ COVER_ROLE_BASE,    // covering a base (COVER_LOCATION_HOME..THIRD), AUTO_MOVEMENT_COVER_BASE
    /* 2 */ COVER_ROLE_SUPPORT, // a support spot (COVER_LOCATION_MOUND_CUTOFF and up), AUTO_MOVEMENT_INFIELD_SUPPORT
} COVER_ROLE;

/* InMemFielder.ballTrackingTarget: where fielderTrackingBall_updateVariables steers the fielder. */
typedef enum _BALL_TRACKING_TARGET {
    /* 0 */ BALL_TRACKING_TARGET_LANDING_SPOT,         // ball's future position at framesRemainingToGetToLandingSpot
    /* 1 */ BALL_TRACKING_TARGET_WALL_HIT_SPOT,        // where the ball will hit the wall (ballWillHitBallPos)
    /* 2 */ BALL_TRACKING_TARGET_WALL_REBOUND,         // 5 m off the wall spot, adjusted for the bounce (updateFielderPosition)
    /* 3 */ BALL_TRACKING_TARGET_ROLL_CHECK_INTERCEPT, // where the ball rolls to; fielderTrackingBall_checkSwitchToIntercept
    /* 4 */ BALL_TRACKING_TARGET_INTERCEPT,            // setIntendedLocToInterceptBall; fielderTrackingBall_goToFutureBallPos
    /* 5 */ BALL_TRACKING_TARGET_BALL_POS,             // ball (nearly) stopped; fielderTrackingBall_goToContactBallPos
} BALL_TRACKING_TARGET;

/* InMemFielder.minigameChaseTarget: where updateFielderPositionBasedOnBallState sends a minigame fielder. */
typedef enum _MINIGAME_CHASE_TARGET {
    /* 0 */ MINIGAME_CHASE_TARGET_NONE,
    /* 1 */ MINIGAME_CHASE_TARGET_LANDING_SPOT,
    /* 2 */ MINIGAME_CHASE_TARGET_BALL,
    /* 3 */ MINIGAME_CHASE_TARGET_BEST_FUTURE_FRAME, // determineBestFrameForFielder (nonCatchFlyBallStratInd)
    /* 4 */ MINIGAME_CHASE_TARGET_COIN,              // Toy Field: nearest coin
} MINIGAME_CHASE_TARGET;

/* InMemFielder.catchStrategy, from setFielderCatchStrategy_calcFramesToGetToDropSpot and its
 * catcher / knockout variants: how the fielder can get to the batted ball. */
typedef enum _CATCH_STRATEGY {
    /* 0 */ CATCH_STRATEGY_NONE,
    /* 1 */ CATCH_STRATEGY_IN_REACH,      // arrives while the ball is below the top of the hitbox (hitbox[3])
    /* 2 */ CATCH_STRATEGY_ABOVE_REACH,   // only arrives while the ball is still above the hitbox
    /* 3 */ CATCH_STRATEGY_AFTER_LANDING, // cannot catch it in the air; goes to where it can be picked up
    /* 4 */ CATCH_STRATEGY_TOO_FAR,       // as AFTER_LANDING but not close enough (or an infielder leaving it)
} CATCH_STRATEGY;

/* InMemFielder.catchAnimation, set through initCatchAnimationState by the catch functions. */
typedef enum _CATCH_ANIMATION {
    /* 0 */ CATCH_ANIMATION_NONE,
    /* 1 */ CATCH_ANIMATION_STANDARD,            // checkIfCatchOccurs
    /* 2 */ CATCH_ANIMATION_THROWN_BALL,         // catchThrownBallFun
    /* 3 */ CATCH_ANIMATION_DIVE,                // divingCatch (dive / slide / lunge)
    /* 4 */ CATCH_ANIMATION_WALL_JUMP,           // wallJumpInitialization
    /* 5 */ CATCH_ANIMATION_CLAMBER,             // clamberCheckCatch
    /* 6 */ CATCH_ANIMATION_JUMP,                // attemptJumpingCatch
    /* 7 */ CATCH_ANIMATION_RUNNING,             // checkIfRunningCatchOccurs, divingCatch's running catch
    /* 8 */ CATCH_ANIMATION_THROW_TO_EMPTY_BASE, // ballThrownToEmptyBaseCatchAttempt
} CATCH_ANIMATION;

/* InMemFielder.inBasePath: the base path the fielder stands in (setInBasePathFromPosition). */
typedef enum _BASE_PATH {
    /* 0 */ BASE_PATH_NONE,
    /* 1 */ BASE_PATH_HOME_TO_FIRST,
    /* 2 */ BASE_PATH_FIRST_TO_SECOND,
    /* 3 */ BASE_PATH_SECOND_TO_THIRD,
    /* 4 */ BASE_PATH_THIRD_TO_HOME,
} BASE_PATH;

/* InMemFielder.outFieldZoneCode, from getOutfieldZoneCode(pos). */
typedef enum _FIELDER_ZONE {
    /* 0 */ FIELDER_ZONE_INFIELD_DIAMOND,  // |x| + z < 40 (inside the diamond reaching just past second)
    /* 1 */ FIELDER_ZONE_INFIELD_EDGE,     // < 38.8 from home or < 28 from the mound
    /* 2 */ FIELDER_ZONE_SHALLOW_OUTFIELD, // < 37 from the mound
    /* 3 */ FIELDER_ZONE_MID_OUTFIELD,     // < 43 from the mound
    /* 4 */ FIELDER_ZONE_DEEP_OUTFIELD,
} FIELDER_ZONE;

/* Index into autoMovementFunctions[] (fielder.c); comments name the dispatched function. */
typedef enum _AUTO_MOVEMENT_FUNCTION_INDEX {
    /*  0 */ AUTO_MOVEMENT_STAY_STILL = 0, // autoMovement0_stayStill_exceptForSpecialActions
    /*  1 */ AUTO_MOVEMENT_COVER_BASE, // autoMovement1_coverBase
    /*  2 */ AUTO_MOVEMENT_GO_TO_BALL_PHASE2_AI, // autoMovement2_18_goTowardsBall_phase2 (keeps current code; AI fielders enter it from 3/4)
    /*  3 */ AUTO_MOVEMENT_GO_TO_HIT_BALL, // autoMovement3_goTowardsHitBall_AITeam (either team; then -> 2 for AI, 16 for human)
    /*  4 */ AUTO_MOVEMENT_GO_TO_HIT_BALL_PITCHER, // autoMovement4_AI_goTowardsHitBall (only set on the pitcher; -> 9 if the target is > 20 out)
    /*  5 */ AUTO_MOVEMENT_CUTOFF_ADJUST, // autoMovement5 (assigned cutoff re-aims at the targeted base during a play)
    /*  6 */ AUTO_MOVEMENT_OUTFIELDER_NO_CATCH_PHASE2, // autoMovement6_outfielderNoCatch_Phase2
    /*  7 */ AUTO_MOVEMENT_OUTFIELDER_NO_CATCH_PHASE1, // autoMovement7_8_outfiederNoCatch_Phase1 (presetLocationToStandAt != 1)
    /*  8 */ AUTO_MOVEMENT_OUTFIELDER_NO_CATCH_PHASE1_PRESET_1, // autoMovement7_8_outfiederNoCatch_Phase1 (presetLocationToStandAt == 1)
    /*  9 */ AUTO_MOVEMENT_OFF_BASE_REASSIGN, // autoMovement9_OffBase_coverHome (re-picks a role; covers home as fallback)
    /* 10 */ AUTO_MOVEMENT_HAS_BALL, // autoMovement10_HasBall
    /* 11 */ AUTO_MOVEMENT_CUTOFF, // autoMovement11_cutoff_setInitialLocation
    /* 12 */ AUTO_MOVEMENT_STOP_BETWEEN_INSTRUCTIONS, // autoMovement12_stopBetweenInstructions (stops, then -> 9)
    /* 13 */ AUTO_MOVEMENT_BACK_UP_BALL, // autoMovement13_GoTowardsBallAsBackUp
    /* 14 */ AUTO_MOVEMENT_INFIELD_SUPPORT, // autoMovement14_infieldSupport
    /* 15 */ AUTO_MOVEMENT_GO_TO_BALL_HUMAN, // autoMovement15_selectedFielderOnLooseBall
    /* 16 */ AUTO_MOVEMENT_TRACK_BALL, // autoMovement16_trackFoulBall (foul balls, and human-team fielders on fair balls)
    /* 17 */ AUTO_MOVEMENT_RUN_OFF_FIELD, // autoMovement17_runningOffField
    /* 18 */ AUTO_MOVEMENT_GO_TO_BALL_AI, // autoMovement2_18_goTowardsBall_phase2 (AI counterpart of 15; sets code 1)
    /* 19 */ AUTO_MOVEMENT_STAY_STILL_ON_FOUL, // autoMovement19_foulBall (AI fielder on a foul: just stands still)
    /* 20 */ AUTO_MOVEMENT_PITCHER_LINE_DRIVE, // autoMovement20_pitcherLinedriveRelated (pitcher waits until ready, then -> 18 or 0)
    /* 21 */ AUTO_MOVEMENT_INITIAL_SELECTED_FIELDER, // autoMovement21_23_humanControlInitialSelectedFielders (selectedFielder)
    /* 22 */ AUTO_MOVEMENT_INITIAL_SECONDARY_FIELDER, // autoMovement21_23_humanControlInitialSelectedFielders (secondaryFielder)
    /* 23 */ AUTO_MOVEMENT_INITIAL_TERTIARY_FIELDER, // autoMovement21_23_humanControlInitialSelectedFielders (tertiaryFielder)
    /* 24 */ AUTO_MOVEMENT_GO_TO_HIT_BALL_HUMAN, // autoMovement24_goTowardsHitBall_humanTeam
    /* 25 */ AUTO_MOVEMENT_READY_TO_INTERCEPT_THROW, // autoMovement25_readyToInterceptThrownBall
    /* 26 */ AUTO_MOVEMENT_MINIGAME_WAIT_FOR_HIT, // autoMovement26_minigameRelated1 (waits for hit + lockout, then -> 27)
    /* 27 */ AUTO_MOVEMENT_MINIGAME_CHASE_BALL, // autoMovement27_minigameDashRelated2 (runs to ball until a panel is hit, then -> 28)
    /* 28 */ AUTO_MOVEMENT_MINIGAME_AFTER_PANEL_HIT, // autoMovement28_minigameDashRelated3 (keeps moving to intended location)
    AUTO_MOVEMENT_COUNT
} AUTO_MOVEMENT_FUNCTION_INDEX;

/* Defined as s16[44] in data_only/gameplay_tables.c; the trailing comments give those values.
 * _0A and _38 are never read. */
typedef struct _SpecialFieldingActionConstants {
    /*0x00*/ s16 ballHolderMoveDelayFrames; // 6
    /*0x02*/ s16 wallJumpSearchMaxFrame; // 50
    /*0x04*/ s16 wallJumpSearchMinFrame; // 25
    /*0x06*/ s16 wallJumpFramesToWallTop; // 15
    /*0x08*/ s16 wallJumpLandCountdown; // 20
    /*0x0A*/ s16 _0A; // 40
    /*0x0C*/ s16 clamberJumpOffDelay; // 30
    /*0x0E*/ s16 wallSplatStage1Frames; // 12
    /*0x10*/ s16 wallSplatStage2Frames; // 30
    /*0x12*/ s16 wallSplatStage3Frames; // 60
    /*0x14*/ s16 wallSplatStage4Frames; // 60
    /*0x16*/ s16 standardCatchSearchFrames; // 12
    /*0x18*/ s16 thrownCatchMaxFrame; // 6
    /*0x1A*/ s16 thrownCatchMaxFrameOffBase; // 2
    /*0x1C*/ s16 diveMaxFrame; // 30
    /*0x1E*/ s16 diveMinFrame; // 6
    /*0x20*/ s16 runningCatchMaxFrame; // 12
    /*0x22*/ s16 runningCatchMinFrame; // 2
    /*0x24*/ s16 runningCatchMaxAngleDiff; // 512
    /*0x26*/ s16 emptyBaseCatchMaxFrames; // 6
    /*0x28*/ s16 emptyBaseCatchMinFrames; // 2
    /*0x2A*/ s16 runningCatchCountdown; // 20
    /*0x2C*/ s16 thrownCatchSearchMaxFrame; // 15
    /*0x2E*/ s16 thrownCatchSearchMinFrame; // 2
    /*0x30*/ s16 suctionCatchStartFrames; // 5
    /*0x32*/ s16 autoDashDistanceJogFrames; // 30
    /*0x34*/ s16 suctionCatchDiveStartFrames; // 10
    /*0x36*/ s16 wallBounceMinAngleDiff; // 64
    /*0x38*/ s16 _38; // 96
    /*0x3A*/ s16 fireballCountdownArray[3];
    /*0x40*/ s16 onFireSpinPerFrame; // 64
    /*0x42*/ s16 knockOutStage1Frames; // 60
    /*0x44*/ s16 knockOutStage2Frames; // 120
    /*0x46*/ s16 antiChemistryThrowAngleMin; // 64
    /*0x48*/ s16 antiChemistryThrowAngleMax; // 96
    /*0x4A*/ s16 suctionCatchDiveTotalFrames; // 45
    /*0x4C*/ s16 bigPlayMaxSpareFrames; // 75
    /*0x4E*/ s16 bigPlayMaxHoldFrames; // 60
    /*0x50*/ s16 smashThrowHoldFrames; // 3
    /*0x52*/ s16 inAirSelectionDelayFrames; // 36
    /*0x54*/ s16 selectionDelayFrames; // 12
    /*0x56*/ s16 cutoffFrameCycleReset; // 20
} SpecialFieldingActionConstants; // size: 0x58

extern SpecialFieldingActionConstants specialFielderActionConstants;

#endif // __FIELDER_TYPES_H_
