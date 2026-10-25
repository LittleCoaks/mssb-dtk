#ifndef __RUNNER_TABLES_H_
#define __RUNNER_TABLES_H_

// Constant tables read by the baserunning code. Kept free of other game headers
// so the data-only TUs that define them can include it.

#include "mssbTypes.h"

typedef struct _RunnerTimingConsts {
    /* 0x00 */ s16 slideHomeFrames;
    /* 0x02 */ s16 bodyCheckWindowMin; // throw arrival minus runner arrival, in frames
    /* 0x04 */ s16 bodyCheckWindowMax;
    /* 0x06 */ s16 directionChangeCooldown;
    /* 0x08 */ s16 pickoffOverrideFrame;
    /* 0x0A */ s16 sameBaselineAdvanceTimer;
    /* 0x0C */ s16 sameBaselineAdvanceMaxCount;
    /* 0x0E */ s16 sprintFrames;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 maxStamina;
    /* 0x14 */ s16 staminaDrainRunning;
    /* 0x16 */ s16 staminaDrainTurnaround;
} RunnerTimingConsts; // size: 0x18

typedef struct _RunnerStaminaConsts {
    /* 0x0 */ f32 bodyCheckMinMash;
    /* 0x4 */ f32 maxSpeedPenalty; // applied at zero stamina
    /* 0x8 */ f32 maxAccelPenalty;
    /* 0xC */ f32 maxTurnAccelPenalty;
} RunnerStaminaConsts; // size: 0x10

typedef struct _RunnerSpeedCapMult {
    /* 0x0 */ f32 normal;
    /* 0x4 */ f32 stealing;
} RunnerSpeedCapMult;

// Facing angles (radians) for a runner at each base.
typedef struct _BaseFacingAngles {
    /* 0x0 */ f32 toNextBase;
    /* 0x4 */ f32 toPrevBase;
    /* 0x8 */ f32 idle;
} BaseFacingAngles; // size: 0xC

typedef struct _OverrunStageFrames {
    /* 0x0 */ s16 slowdownFrames;
    /* 0x2 */ s16 returnFrames;
} OverrunStageFrames;

typedef struct _OverrunBaseStageFrames {
    /* 0x0 */ s16 slowdownFrames;
    /* 0x2 */ s16 returnFrames;
    /* 0x4 */ s16 unk_4;
    /* 0x6 */ s16 unk_6;
} OverrunBaseStageFrames;

// CPU baserunner button mashing, per AI difficulty.
typedef struct _AiMashConsts {
    /* 0x0 */ s16 startFrame; // frames after contact before mashing starts
    /* 0x2 */ s16 presses;
    /* 0x4 */ s16 cooldownFrames;
    /* 0x6 */ s16 chancePercent;
} AiMashConsts; // size: 0x8

typedef struct _RunnerCharConsts {
    /* 0x0 */ u8 slideMinFrames; // slide only if the base is this many frames away or more...
    /* 0x1 */ u8 slideMaxFrames; // ...and no more than this
    /* 0x2 */ u8 slideAnimFrames;
    /* 0x3 */ u8 slideRecoveryFrames;
    /* 0x4 */ u8 backOrHomeSlideAnimFrames; // diving back to a base, or sliding into home
} RunnerCharConsts; // size: 0x5

typedef struct _RunnerCharConstsTable {
    /* 0x000 */ RunnerCharConsts byChar[54]; // indexed by CHAR_ID
    /* 0x10E */ u8 pad[2];
} RunnerCharConstsTable; // size: 0x110

extern RunnerTimingConsts runnerTimingConsts;
extern RunnerStaminaConsts runnerStaminaConsts;
extern RunnerSpeedCapMult runnerSpeedCapMult;
extern BaseFacingAngles baseFacingAngles[4];
extern OverrunStageFrames overrun1BStageFrames;
extern OverrunBaseStageFrames overrunBaseStageFrames;
extern AiMashConsts aiMashConsts[5];
extern RunnerCharConstsTable runnerCharConsts;

#endif // __RUNNER_TABLES_H_
