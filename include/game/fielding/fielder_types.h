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
    /*0x0000*/ u8 fielderDashByPort[4][0x1B];
    /*0x006c*/ s16 pad;
    /*0x006e*/ u8 always0;
    /*0x006f*/ u8 padding;
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
    /*0x00c0*/ s16 someFrameCounterFielderRelated;
    /*0x00c2*/ s16 interceptThrowFielder;
    /*0x00c4*/ s16 locationThrownTo;
    /*0x00c6*/ s16 humanSelectedPlaceToThrow;
    /*0x00c8*/ s16 someHumanThrowFrameCounter;
    /*0x00ca*/ s16 locThrownTo2;
    /*0x00cc*/ s16 somethingForTryingTagOutTargetBase;
    /*0x00ce*/ s16 xcc_Stored_0;
    /*0x00d0*/ s16 fielderAssignedLocationIndex[7];
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
    /*0x0101*/ u8 baseCoveredInd[4];
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
    /*0x0115*/ u8 fielderActionBeingProcessed_prev;
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
    /*0x0139*/ u8 unkFlagMaybeInAir;
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
    /*0x020*/ f32 maybeTargetPosX;
    /*0x024*/ f32 maybeTargetPosZ;
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
    /*0x18C*/ s16 locationResponsibleForCovering;
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
    /*0x1A2*/ s16 someCountdownAndCountUpRelatedToStandingStill;
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
    /*0x1D5*/ u8 unknown_writeOnly;
    /*0x1D6*/ u8 fielderVeloAdjustmentCode;
    /*0x1D7*/ u8 isResponsibleForCoveringALocation;
    /*0x1D8*/ u8 pitcherHeadingToCover1stOr3rd;
    /*0x1D9*/ u8 goingToAutoLocationInd;
    /*0x1DA*/ u8 cantCatchFlyBallInd;
    /*0x1DB*/ u8 nonCatchFlyBallStratInd;
    /*0x1DC*/ u8 maybeMovementState;
    /*0x1DD*/ u8 catchStrategy;
    /*0x1DE*/ u8 inBasePath;
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
    /*0x1F7*/ u8 baseOn2;
    /*0x1F8*/ u8 outFieldZoneCode;
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
    /*0x208*/ u8 _0208;
    /*0x209*/ u8 _0209;
    /*0x20A*/ u8 _020A;
    /*0x20B*/ u8 _020B;
    /*0x20C*/ u8 _020B_stored;
    /*0x20D*/ u8 _020D;
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
    /*0x252*/ u8 catchAnimation;
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

typedef enum _AUTO_MOVEMENT_FUNCTION_INDEX {
    /*  2 */ AUTO_MOVEMENT_TRACK_HIT_BALL_PHASE2_AI_TEAM = 2,
    /* 15 */ AUTO_MOVEMENT_GOING_TO_BALL = 15,
} AUTO_MOVEMENT_FUNCTION_INDEX;

typedef struct _SpecialFieldingActionConstants {
    /*0x00*/ s16 _00[0x1D];
    /*0x3A*/ s16 fireballCountdownArray[3];
    /*0x40*/ s16 _40[0x0C];
} SpecialFieldingActionConstants; // size: 0x58

extern SpecialFieldingActionConstants specialFielderActionConstants;

#endif // __FIELDER_TYPES_H_
