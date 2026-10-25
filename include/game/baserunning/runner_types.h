#ifndef __RUNNER_TYPES_H_
#define __RUNNER_TYPES_H_

/* Baserunner state: InMemRunnerType / g_Runners, g_RunningLogic and the runner
 * enums. Included from game/UnknownHomes_Game.h at the point the definitions
 * used to sit, so every existing include keeps working. RUNNER_STATUS,
 * TAG_UP_TYPE and RUNNER_RESTRICTION stay in mssbTypes.h with the other
 * shared enums. */

#include "mssbTypes.h"
#include "game/baserunning/runner_tables.h"

// InMemRunnerType running direction fields (runningDirectionCode etc.)
typedef enum _RUNNER_MOVEMENT_TYPE {
    /* 0 */ RUNNER_MOVEMENT_NONE,
    /* 1 */ RUNNER_MOVEMENT_FORWARDS,
    /* 2 */ RUNNER_MOVEMENT_STOPPED,
    /* 3 */ RUNNER_MOVEMENT_BACKWARDS,
    /* 4 */ RUNNER_MOVEMENT_OVERRUN_FIRST, // running through 1st
    /* 5 */ RUNNER_MOVEMENT_OVERRUN_BASE,  // overrunning 2nd/3rd
} RUNNER_MOVEMENT_TYPE;

// InMemRunnerType.actionCode
typedef enum _RUNNER_ACTION {
    /* 0 */ RUNNER_ACTION_NONE,
    /* 1 */ RUNNER_ACTION_SLIDE,
    /* 2 */ RUNNER_ACTION_BODY_CHECK_WON,
    /* 3 */ RUNNER_ACTION_BODY_CHECK_FAILED,
} RUNNER_ACTION;

// InMemRunnerType.actionStage: progress through the current RUNNER_ACTION.
typedef enum _RUNNER_ACTION_STAGE {
    /* 0 */ RUNNER_ACTION_STAGE_NONE,
    /* 1 */ RUNNER_ACTION_STAGE_MOVING,     // sliding into the base over actionFrames_countDown frames
    /* 2 */ RUNNER_ACTION_STAGE_RECOVERING, // on the base, getting up (slideRecoveryFrames)
    /* 3 */ RUNNER_ACTION_STAGE_OUT,        // finished, but the runner was out; dugout logic clears it
} RUNNER_ACTION_STAGE;

// InMemRunnerType.overrun1BStage / overrunBaseStage.
typedef enum _OVERRUN_STAGE {
    /* 0 */ OVERRUN_STAGE_NONE,
    /* 1 */ OVERRUN_STAGE_PENDING,  // overrun decided; set-up runs on the next control call
    /* 2 */ OVERRUN_STAGE_SLOWDOWN, // drifting past the base
    /* 3 */ OVERRUN_STAGE_RETURN,   // moving back onto the base
} OVERRUN_STAGE;

// InMemRunnerType.taggedState: how this runner is being tagged this frame.
typedef enum _RUNNER_TAGGED_STATE {
    /* 0 */ RUNNER_TAGGED_NONE,
    /* 1 */ RUNNER_TAGGED_RUNNING,
    /* 2 */ RUNNER_TAGGED_IN_ACTION, // < 5 out-timer frames left while mid-slide/body check
} RUNNER_TAGGED_STATE;

typedef enum _LEADOFF_STATUS {
    /* 0 */ LEADOFF_STATUS_NONE,         // not leading off (reset, stealing, baserunning practice)
    /* 1 */ LEADOFF_STATUS_LEADING_OFF,  // taking the lead; leadOffTotalFrameCountDown running
    /* 2 */ LEADOFF_STATUS_AT_FULL_LEAD, // countdown finished, holding the lead
} LEADOFF_STATUS;

typedef enum _STEALING_STATUS {
    /* 0 */ STEALING_STATUS_NONE,
    /* 1 */ STEALING_STATUS_REQUESTED,     // steal input given, waiting on the pitch timing
    /* 2 */ STEALING_STATUS_NORMAL_STEAL,  // input missed the perfect-steal window
    /* 3 */ STEALING_STATUS_PERFECT_STEAL, // input landed in perfectStealWindowFrames
} STEALING_STATUS;

// Latched on the first frame a stealing runner breaks forward. Non-zero means
// the runner has left the base; 2-4 is the base a walk would force them to.
typedef enum _STEAL_FORCED_BASE {
    /* 0 */ STEAL_FORCED_BASE_NONE,     // n/a, no steal
    /* 1 */ STEAL_FORCED_BASE_UNFORCED, // a base behind the runner is empty
    /* 2 */ STEAL_FORCED_BASE_SECOND,
    /* 3 */ STEAL_FORCED_BASE_THIRD,
    /* 4 */ STEAL_FORCED_BASE_HOME,
} STEAL_FORCED_BASE;

typedef struct _InMemRunnerType {
    /*0x000*/ VecXYZ position;
    /*0x00C*/ VecXYZ positionStored;
    /*0x018*/ VecXYZ velocity;
    /*0x024*/ VecXYZ velocityStored;
    /*0x030*/ f32 runningAngle;
    /*0x034*/ f32 angleToBall;
    /*0x038*/ f32 distanceFromBall;
    /*0x03C*/ VecXYZ currentBaseCoordinates;
    /*0x048*/ VecXYZ nextBaseCoordinates;
    /*0x054*/ f32 baseReachMargin_backwards; // 0.03: a base counts as reached this fraction of the leg early
    /*0x058*/ f32 baseReachMargin_forwards;  // 0.03
    /*0x05C*/ f32 percentPastCurrentBaseReach; // percentTowardsNextBase - baseReachMargin_backwards
    /*0x060*/ f32 percentLeftToNextBaseReach;  // (1 - percentTowardsNextBase) - baseReachMargin_forwards
    /*0x064*/ f32 fractionalBasesRan;
    /*0x068*/ f32 percentTowardsNextBase;
    /*0x06C*/ f32 calculatedLengthOfCurrentBaseline;
    /*0x070*/ f32 fractionOfCalculatedBaselineRan;
    /*0x074*/ f32 distToCurrentBase;
    /*0x078*/ f32 distToNextBase;
    /*0x07C*/ f32 fractionalBasesRan_stored;
    /*0x080*/ f32 percentTowardsNextBase_stored;
    /*0x084*/ f32 groundVelocity[4];
    /*0x094*/ f32 acceleration;
    /*0x098*/ f32 baseAcceleration;                       // runnerSpeedScaling: 0.01 at speed 0 to 0.005 at speed 100+
    /*0x09C*/ f32 baseAccelerationWhileChangingDirection; // 0.005
    /*0x0A0*/ f32 maximumBaseVelocity;
    /*0x0A4*/ f32 percentRanPerFrame; // groundVelocity[0] / calculatedLengthOfCurrentBaseline
    /*0x0A8*/ f32 velocityPercent_stamAdj;
    /*0x0AC*/ f32 accelerationPercent_stamAdj;
    /*0x0B0*/ f32 roundingStrengthPercent;                    // unsure
    /*0x0B4*/ f32 overrunStepPerFrame;   // per-frame step scale for both overrun stages
    /*0x0B8*/ f32 overrun1BPathProgress; // spline parameter along overrun1BPathPoints, 0 to ~1
    /*0x0BC*/ f32 leadoffDistancePercent;
    /*0x0C0*/ f32 mashVeloAdjustment;
    /*0x0C4*/ f32 maxMashVeloAdjustment; // 0.02: speed bonus at full mashPercent
    /*0x0C8*/ f32 mashPercent;
    /*0x0CC*/ f32 percentAddedPerMash;   // 0.2: five presses fill the meter
    /*0x0D0*/ f32 mashDecayPerFrame;     // 0.05 once mashHoldFramesLeft runs out
    /*0x0D4*/ f32 staminaMult;
    /*0x0D8*/ f32 accelerationStaminaEffect;
    /*0x0DC*/ f32 accelerationStaminaEffectWhileChangingDirection;
    /*0x0E0*/ s16 rosterID;
    /*0x0E2*/ s16 charID;
    /*0x0E4*/ s16 unused_starMissionCharID;
    /*0x0E6*/ s16 baseStandingOn;
    /*0x0E8*/ s16 baseStandingOn_Stored;
    /*0x0EA*/ s16 framesToNextBase;
    /*0x0EC*/ s16 framesToPreviousBase; // maybe
    /*0x0EE*/ E(s16, FORCE_OUT_TYPE) forceOutCd;
    /*0x0F0*/ E(s16, RUNNER_RESTRICTION) movementRestrictions;
    /*0x0F2*/ E(s16, RUNNER_RESTRICTION) movementRestrictions_stored;
    /*0x0F4*/ s16 framesSinceOut;
    /*0x0F6*/ s16 stamina;
    /*0x0F8*/ s16 baseNumberEarned_NotIncludingFieldersChoice;
    /*0x0FA*/ s16 timeStandingOnBase;
    /*0x0FC*/ s16 pitcherWhoLetRunnerOnBase;
    /*0x0FE*/ s16 baseReachedAtTimeOfThrow;
    /*0x100*/ s16 actionFrames_countUp;
    /*0x102*/ s16 actionFrames_countDown;
    /*0x104*/ s16 overrunBaseFrames_countUp;
    /*0x106*/ s16 overrunBaseFrames_countDown;
    /*0x108*/ s16 runningToDugoutFrameCounter;
    /*0x10A*/ s16 framesToReachDugout; // maybe
    /*0x10C*/ s16 leadoffDurationFrames;
    /*0x10E*/ s16 leadOffTotalFrameCountDown;
    /*0x110*/ s16 unused_always0;
    /*0x112*/ s16 framesSinceLastDirectionChange;
    /*0x114*/ s16 slideHomeFrames_CountDown;
    /*0x116*/ s16 framesSinceStealStarted;
    /*0x118*/ s16 _118;
    /*0x11A*/ u8 unused_batterHandednessForCCS; // maybe
    /*0x11B*/ u8 aIStrength0Special3Weak;
    /*0x11C*/ E(u8, BATTING_HAND) battingHand;
    /*0x11D*/ u8 weight;
    /*0x11E*/ E(u8, CHARACTER_CLASS) characterClass;
    /*0x11F*/ u8 _11f;
    /*0x120*/ u8 speed;
    /*0x121*/ u8 unused_const_10;
    /*0x122*/ u8 delayBeforeStartingToRun;
    /*0x123*/ E(u8, RUNNER_STATUS) runnerStatus;
    /*0x124*/ u8 startingBase_baseAchieved;
    /*0x125*/ u8 currentBase;
    /*0x126*/ u8 nextBase;
    /*0x127*/ u8 baseRunningTowards;
    /*0x128*/ E(u8, TAG_UP_TYPE) tagUpStatus;
    /*0x129*/ u8 batterStayInBattersBoxReason;
    /*0x12A*/ u8 unused_AIRelated;
    /*0x12B*/ u8 unused_AIBaseHoldFlag; // written by runnerAI_updateUnusedBaseHoldFlag, never read
    /*0x12C*/ u8 outType;
    /*0x12D*/ u8 forcedToAdvanceInd; // maybe
    /*0x12E*/ s8 aiCommittedBase;
    /*0x12F*/ s8 baseOfFailedBodyCheck; // maybe
    /*0x130*/ E(u8, RUNNER_TAGGED_STATE) taggedState;
    /*0x131*/ u8 runnerDidntReachOnError;
    /*0x132*/ u8 isEligibleToScore; // maybe
    /*0x133*/ E(u8, LEADOFF_STATUS) leadOffStatus;
    /*0x134*/ u8 unused_const_1;
    /*0x135*/ E(u8, RUNNER_MOVEMENT_TYPE) runningDirectionDesired;
    /*0x136*/ E(u8, RUNNER_MOVEMENT_TYPE) nextDirectionBeingProcessed;
    /*0x137*/ E(u8, RUNNER_MOVEMENT_TYPE) runningDirectionCode;
    /*0x138*/ E(u8, RUNNER_MOVEMENT_TYPE) runnerDirectionCode_stored;
    /*0x139*/ u8 offsetFromNormalRunningPathInd; // maybe
    /*0x13A*/ E(u8, RUNNER_ACTION) actionCode;
    /*0x13B*/ u8 actionInForwardDirectionInd;
    /*0x13C*/ E(u8, RUNNER_ACTION_STAGE) actionStage;
    /*0x13D*/ u8 forceOutType_unsed;
    /*0x13E*/ u8 baseRoundingState;
    /*0x13F*/ u8 overrun1BDoneChecking;
    /*0x140*/ E(u8, OVERRUN_STAGE) overrun1BStage;
    /*0x141*/ u8 overrun1BInd;
    /*0x142*/ E(u8, OVERRUN_STAGE) overrunBaseStage;
    /*0x143*/ u8 offsetPositionForRoundingInd;
    /*0x144*/ u8 roundingInitiaializedInd;
    /*0x145*/ u8 runningToDugoutInd;
    /*0x146*/ u8 runningToDugoutStage;
    /*0x147*/ u8 turnaroundCode;
    /*0x148*/ u8 turningAroundInd; // maybe
    /*0x149*/ u8 mashPressedThisFrame; // new A/B/X/Y press this frame; cleared every frame
    /*0x14A*/ u8 mashHoldFramesLeft;   // counts down from mashHoldFrames after a press
    /*0x14B*/ u8 mashHoldFrames;       // runnerTimingConsts.mashHoldFrames (6)
    /*0x14C*/ u8 someCollisionCheck;             // maybe
    /*0x14D*/ E(u8, STEAL_FORCED_BASE) steal_forcedBaseToGoToOnWalk;
    /*0x14E*/ E(u8, STEALING_STATUS) stealingStatus;
    /*0x14F*/ u8 framesSinceStealInput;
    /*0x150*/ u8 advanceTwoRunnersInSameBaselineTimer;
    /*0x151*/ u8 advanceTwoRunnersInSameBaselineCount;
    /*0x152*/ u8 miniGamePlayerNum;
    /*0x153*/ u8 scoredOnGRD; // maybe
} InMemRunnerType;            // size: 0x154

extern InMemRunnerType g_Runners[4];

typedef struct {
    /*0x00*/ s16 runnersOnFieldMask;       // RUNNER_BIT(runnerIdx) per runner still on the field (Ghidra: baseRunnerHex)
    /*0x02*/ s16 runnersAtStartOfPlayMask; // RUNNER_BIT(runnerIdx) per runner at the start of the play (Ghidra: baseRunnerStartingPos)
    /*0x04*/ s16 runnersByCurrentBaseMask; // RUNNER_BIT(currentBase) per runner on the field
    /*0x06*/ s16 runnerTransferIndex[4];
    artificial_padding(0x06, 0x10, s16[4]);
    /*0x10*/ u8 nOffensivePlayersOnField;
    /*0x11*/ u8 _11;
    /*0x12*/ u8 nOffensivePlayersAtStartOfPlay;
    /*0x13*/ u8 _13;
    /*0x14*/ u8 liveBallInputDelayFrames; // runner input is ignored for this many live-ball frames: 20, or 10 for high outfield flies
    /*0x15*/ u8 runnersInScoringPosition;
    artificial_padding(0x15, 0x1F, u8);
    /*0x1F*/ s8 _1f;
} g_RunningLogic_s; // size: 0x20

/* g_RunningLogic runner masks: one nibble per runner index (0 = batter,
 * 1-3 = the runner who started the play on that base); runnersByCurrentBaseMask
 * uses the same nibbles indexed by base. */
#define RUNNER_BIT(n)        (1 << ((n) * 4))
#define RUNNER_BIT_BATTER    0x0001
#define RUNNER_BIT_ON_FIRST  0x0010
#define RUNNER_BIT_ON_SECOND 0x0100
#define RUNNER_BIT_ON_THIRD  0x1000

extern g_RunningLogic_s g_RunningLogic;

#endif // __RUNNER_TYPES_H_
