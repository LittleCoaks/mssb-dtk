# at_bat_results matching checkpoint

Baseline rebuilt 2026-10-12: .text 99.92008%, 7508 bytes; no .rodata/.data/.bss sections in target or ours.

| function | status | baseline | current |
|---|---|---|---|
| setBatterOutAtBatResult | matched | 100.0% | 100.0% |
| atBatBuntResult | matched | 100.0% | 100.0% |
| atBatResultsForOuts | matched | 100.0% | 100.0% |
| noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance | matched | 100.0% | 100.0% |
| fn_3_9D550 | matched | 100.0% | 100.0% |
| fn_3_9D594 | matched | 100.0% | 100.0% |
| setStrikeoutOrWalkAtBatResult | matched | 100.0% | 100.0% |
| setAtBatResult | matched | 100.0% | 100.0% |
| setDefaultPlayTrackingVariables1 | matched | 100.0% | 100.0% |
| initializeInningTrackers | matched | 100.0% | 100.0% |
| shuffleU8Array | exhausted | 99.46429% | 99.89286% |
| shuffleIntArray | matched | 100.0% | 100.0% |
| RandomIndexFromIntWeights | matched | 100.0% | 100.0% |
| RandomIndexFromWeights | matched | 100.0% | 100.0% |
| iterateBatter | matched | 100.0% | 100.0% |
| fn_3_9E834 | matched | 100.0% | 100.0% |
| fn_3_9EA1C | matched | 100.0% | 100.0% |

## shuffleU8Array
baseline: 99.46429%, 1120 bytes target and ours. REGISTER_ALLOC; logic and instruction sequence exact. Inlined shuffleIntArray k/pointer/max/orig registers rotate r25-r28; modulo temporary r4 target versus r0 ours.
No checkpoint from earlier passes exists. Prior draft/findings in docs/matching_notes.md have already been read.

## Baseline source backup
Exact source saved in build/at_bat_results_baseline.c for targeted experimental restores.
[manual-inline] shuffleU8Array 95.310715%; other regressions []; reverted.
[abs-bound] shuffleU8Array 99.19643%; other regressions [('shuffleIntArray', 99.3883)]; reverted.
[k-local-scope] compile failed; restored baseline.
[r-local-scope] shuffleU8Array 99.46429%; other regressions []; reverted.
[clone-base] shuffleU8Array 99.46429%; other regressions []; reverted.
[clone-game] shuffleU8Array 98.125%; other regressions []; reverted.
[clone-ternary] shuffleU8Array 99.46429%; other regressions []; reverted.
[clone-bound-local] shuffleU8Array 96.07143%; other regressions []; reverted.
[clone-scoped-k] shuffleU8Array 99.46429%; other regressions []; reverted.
[clone-register-k] shuffleU8Array 99.46429%; other regressions []; reverted.
[clone-while] shuffleU8Array 99.46429%; other regressions []; reverted.
[clone-postdec] shuffleU8Array 96.51071%; other regressions []; reverted.
[outer-two-indices] shuffleU8Array 99.46429%; other regressions []; reverted.
[outer-unsigned-buffer] shuffleU8Array 99.46429%; other regressions []; reverted.
[outer-count-local] shuffleU8Array 99.46429%; other regressions []; reverted.
[outer-explicit-count-cast] shuffleU8Array 99.46429%; other regressions []; reverted.
[clone-unsigned-r] shuffleU8Array 99.25%; other regressions []; reverted.
[clone-unsigned-source] shuffleU8Array 99.46429%; other regressions []; reverted.
[clone-explicit-output] shuffleU8Array 98.77857%; other regressions []; reverted.
[clone-explicit-output-after-k] shuffleU8Array 99.457146%; other regressions []; reverted.
[rng-abs-inline] shuffleU8Array 99.46429%; other regressions []; reverted.
[rng-remainder-inline] shuffleU8Array 99.46429%; other regressions []; reverted.
[rng-separate-abs-ret] shuffleU8Array 99.46429%; other regressions []; reverted.
[rng-ret-expression] shuffleU8Array 95.10714%; other regressions []; reverted.
[rng-orig-last] shuffleU8Array 99.46429%; other regressions []; reverted.
[choice-helper] shuffleU8Array 96.07143%; other regressions []; reverted.
[rng-orig-param] shuffleU8Array 96.55357%; other regressions []; reverted.
[rng-abs-bound] shuffleU8Array 98.78571%; other regressions []; reverted.
[rng-long-ret] shuffleU8Array 99.46429%; other regressions []; reverted.
[clone-cast-count] shuffleU8Array 99.46429%; other regressions []; reverted.
[clone-cast-k-bound] shuffleU8Array 99.46429%; other regressions []; reverted.
[clone-long-k] shuffleU8Array 99.46429%; other regressions []; reverted.
[clone-long-count] shuffleU8Array 98.73214%; other regressions []; reverted.
[flag-inline-level3] shuffleU8Array 99.46429%; other regressions []; reverted.
[flag-inline-level4] shuffleU8Array 99.46429%; other regressions []; reverted.
[flag-inline-all] shuffleU8Array 99.46429%; other regressions []; reverted.
[flag-nocse] shuffleU8Array 86.707146%; other regressions [('setBatterOutAtBatResult', 84.22414), ('atBatBuntResult', 92.66292), ('atBatResultsForOuts', 84.60284), ('setAtBatResult', 94.513245), ('shuffleIntArray', 98.45744), ('RandomIndexFromIntWeights', 89.746475), ('RandomIndexFromWeights', 74.914894), ('iterateBatter', 49.166668)]; reverted.
[flag-noschedule] shuffleU8Array 64.38928%; other regressions [('setBatterOutAtBatResult', 97.93104), ('atBatBuntResult', 87.2191), ('atBatResultsForOuts', 87.375885), ('noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance', 76.30252), ('fn_3_9D550', 76.47059), ('fn_3_9D594', 70.37037), ('setStrikeoutOrWalkAtBatResult', 74.14634), ('setAtBatResult', 88.486755), ('setDefaultPlayTrackingVariables1', 79.79412), ('initializeInningTrackers', 80.0), ('shuffleIntArray', 61.02128), ('RandomIndexFromIntWeights', 62.112675), ('RandomIndexFromWeights', 67.13475), ('iterateBatter', 91.458336), ('fn_3_9E834', 83.508194), ('fn_3_9EA1C', 83.36)]; reverted.
[flag-nopeephole] shuffleU8Array 84.671425%; other regressions [('setBatterOutAtBatResult', 96.18965), ('atBatBuntResult', 92.994385), ('atBatResultsForOuts', 88.61702), ('noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance', 90.966385), ('fn_3_9D550', 71.76471), ('fn_3_9D594', 76.296295), ('setStrikeoutOrWalkAtBatResult', 96.097565), ('setAtBatResult', 87.486755), ('setDefaultPlayTrackingVariables1', 68.73529), ('shuffleIntArray', 85.28191), ('RandomIndexFromIntWeights', 90.10564), ('RandomIndexFromWeights', 92.50355), ('iterateBatter', 50.833332), ('fn_3_9E834', 76.13115), ('fn_3_9EA1C', 79.86)]; reverted.
[flag-O3] shuffleU8Array 99.46429%; other regressions []; reverted.
[compiler-1.3.2] shuffleU8Array 99.46429%; other regressions []; reverted.
[compiler-2.7] shuffleU8Array 99.46429%; other regressions []; reverted.
[compiler-3.0a5.2] shuffleU8Array 32.19643%; other regressions [('setBatterOutAtBatResult', 82.5), ('atBatBuntResult', 83.314606), ('atBatResultsForOuts', 92.64539), ('noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance', 89.957985), ('fn_3_9D550', 72.94118), ('fn_3_9D594', 70.37037), ('setStrikeoutOrWalkAtBatResult', 92.19512), ('setAtBatResult', 65.33112), ('setDefaultPlayTrackingVariables1', 69.35294), ('shuffleIntArray', 74.57447), ('RandomIndexFromIntWeights', 61.528168), ('RandomIndexFromWeights', 62.907803), ('iterateBatter', 48.75), ('fn_3_9E834', 80.090164), ('fn_3_9EA1C', 89.26)]; reverted.
[clone-base] shuffleU8Array 99.46429%; other regressions []; reverted.
[clone-source-to-r] shuffleU8Array 99.17857%; other regressions []; reverted.
[clone-first-k] shuffleU8Array 99.46429%; other regressions []; reverted.
[clone-last-k] shuffleU8Array 99.46429%; other regressions []; reverted.
[clone-scoped-random] shuffleU8Array 99.46429%; other regressions []; reverted.
[readability] shuffleU8Array 99.46429%; other regressions []; kept.
[compiler-1.0] shuffleU8Array 23.446428%; other regressions [('setBatterOutAtBatResult', 90.56896), ('atBatBuntResult', 95.42696), ('atBatResultsForOuts', 90.75177), ('noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance', 87.268906), ('setStrikeoutOrWalkAtBatResult', 88.29269), ('setAtBatResult', 69.55298), ('setDefaultPlayTrackingVariables1', 89.79412), ('initializeInningTrackers', 90.76923), ('shuffleIntArray', 44.43085), ('RandomIndexFromIntWeights', 68.30282), ('RandomIndexFromWeights', 65.836876), ('iterateBatter', 86.875), ('fn_3_9E834', 79.94262), ('fn_3_9EA1C', 0.0)]; reverted.
[compiler-1.1] shuffleU8Array 23.446428%; other regressions [('setBatterOutAtBatResult', 90.56896), ('atBatBuntResult', 95.42696), ('atBatResultsForOuts', 90.75177), ('noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance', 87.268906), ('setStrikeoutOrWalkAtBatResult', 88.29269), ('setAtBatResult', 69.55298), ('setDefaultPlayTrackingVariables1', 89.79412), ('initializeInningTrackers', 90.76923), ('shuffleIntArray', 44.43085), ('RandomIndexFromIntWeights', 68.30282), ('RandomIndexFromWeights', 65.836876), ('iterateBatter', 86.875), ('fn_3_9E834', 79.94262), ('fn_3_9EA1C', 0.0)]; reverted.
[compiler-1.1p1] shuffleU8Array 22.907143%; other regressions [('setBatterOutAtBatResult', 90.56896), ('atBatBuntResult', 95.42696), ('atBatResultsForOuts', 90.75177), ('noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance', 87.268906), ('setStrikeoutOrWalkAtBatResult', 88.29269), ('setAtBatResult', 70.37086), ('setDefaultPlayTrackingVariables1', 89.79412), ('initializeInningTrackers', 90.76923), ('shuffleIntArray', 43.898937), ('RandomIndexFromIntWeights', 70.211266), ('RandomIndexFromWeights', 64.71631), ('iterateBatter', 86.875), ('fn_3_9E834', 79.36885), ('fn_3_9EA1C', 0.0)]; reverted.
[compiler-1.2.5] shuffleU8Array 23.446428%; other regressions [('setBatterOutAtBatResult', 90.56896), ('atBatBuntResult', 95.42696), ('atBatResultsForOuts', 90.75177), ('noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance', 87.268906), ('setStrikeoutOrWalkAtBatResult', 88.29269), ('setAtBatResult', 69.55298), ('setDefaultPlayTrackingVariables1', 89.79412), ('initializeInningTrackers', 90.76923), ('shuffleIntArray', 44.43085), ('RandomIndexFromIntWeights', 68.30282), ('RandomIndexFromWeights', 65.836876), ('iterateBatter', 86.875), ('fn_3_9E834', 79.94262), ('fn_3_9EA1C', 0.0)]; reverted.
[compiler-1.2.5n] shuffleU8Array 22.782143%; other regressions [('setBatterOutAtBatResult', 90.56896), ('atBatBuntResult', 95.42696), ('atBatResultsForOuts', 90.75177), ('noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance', 87.268906), ('setStrikeoutOrWalkAtBatResult', 88.29269), ('setAtBatResult', 69.55298), ('setDefaultPlayTrackingVariables1', 89.79412), ('initializeInningTrackers', 90.76923), ('shuffleIntArray', 44.43085), ('RandomIndexFromIntWeights', 68.30986), ('RandomIndexFromWeights', 65.84397), ('iterateBatter', 86.875), ('fn_3_9E834', 79.94262), ('fn_3_9EA1C', 0.0)]; reverted.
[compiler-1.3] shuffleU8Array 34.664288%; other regressions [('setAtBatResult', 81.218544)]; reverted.
[compiler-1.3.2r] shuffleU8Array 99.46429%; other regressions []; reverted.
[compiler-2.0] shuffleU8Array 99.46429%; other regressions []; reverted.
[compiler-2.0p1] shuffleU8Array 99.46429%; other regressions []; reverted.
[compiler-2.5] shuffleU8Array 99.46429%; other regressions []; reverted.
[compiler-3.0a3] shuffleU8Array 32.19643%; other regressions [('setBatterOutAtBatResult', 82.5), ('atBatBuntResult', 83.314606), ('atBatResultsForOuts', 92.64539), ('noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance', 89.957985), ('fn_3_9D550', 72.94118), ('fn_3_9D594', 70.37037), ('setStrikeoutOrWalkAtBatResult', 92.19512), ('setAtBatResult', 65.33112), ('setDefaultPlayTrackingVariables1', 69.35294), ('shuffleIntArray', 74.57447), ('RandomIndexFromIntWeights', 61.528168), ('RandomIndexFromWeights', 62.907803), ('iterateBatter', 48.75), ('fn_3_9E834', 80.090164), ('fn_3_9EA1C', 89.26)]; reverted.
[compiler-3.0a3.2] shuffleU8Array 32.19643%; other regressions [('setBatterOutAtBatResult', 82.5), ('atBatBuntResult', 83.314606), ('atBatResultsForOuts', 92.64539), ('noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance', 89.957985), ('fn_3_9D550', 72.94118), ('fn_3_9D594', 70.37037), ('setStrikeoutOrWalkAtBatResult', 92.19512), ('setAtBatResult', 65.33112), ('setDefaultPlayTrackingVariables1', 69.35294), ('shuffleIntArray', 74.57447), ('RandomIndexFromIntWeights', 61.528168), ('RandomIndexFromWeights', 62.907803), ('iterateBatter', 48.75), ('fn_3_9E834', 80.090164), ('fn_3_9EA1C', 89.26)]; reverted.
[compiler-3.0a3.3] shuffleU8Array 32.19643%; other regressions [('setBatterOutAtBatResult', 82.5), ('atBatBuntResult', 83.314606), ('atBatResultsForOuts', 92.64539), ('noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance', 89.957985), ('fn_3_9D550', 72.94118), ('fn_3_9D594', 70.37037), ('setStrikeoutOrWalkAtBatResult', 92.19512), ('setAtBatResult', 65.33112), ('setDefaultPlayTrackingVariables1', 69.35294), ('shuffleIntArray', 74.57447), ('RandomIndexFromIntWeights', 61.528168), ('RandomIndexFromWeights', 62.907803), ('iterateBatter', 48.75), ('fn_3_9E834', 80.090164), ('fn_3_9EA1C', 89.26)]; reverted.
[compiler-3.0a3.4] shuffleU8Array 32.19643%; other regressions [('setBatterOutAtBatResult', 82.5), ('atBatBuntResult', 83.314606), ('atBatResultsForOuts', 92.64539), ('noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance', 89.957985), ('fn_3_9D550', 72.94118), ('fn_3_9D594', 70.37037), ('setStrikeoutOrWalkAtBatResult', 92.19512), ('setAtBatResult', 65.33112), ('setDefaultPlayTrackingVariables1', 69.35294), ('shuffleIntArray', 74.57447), ('RandomIndexFromIntWeights', 61.528168), ('RandomIndexFromWeights', 62.907803), ('iterateBatter', 48.75), ('fn_3_9E834', 80.090164), ('fn_3_9EA1C', 89.26)]; reverted.
[compiler-3.0a5] shuffleU8Array 32.19643%; other regressions [('setBatterOutAtBatResult', 82.5), ('atBatBuntResult', 83.314606), ('atBatResultsForOuts', 92.64539), ('noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance', 89.957985), ('fn_3_9D550', 72.94118), ('fn_3_9D594', 70.37037), ('setStrikeoutOrWalkAtBatResult', 92.19512), ('setAtBatResult', 65.33112), ('setDefaultPlayTrackingVariables1', 69.35294), ('shuffleIntArray', 74.57447), ('RandomIndexFromIntWeights', 61.528168), ('RandomIndexFromWeights', 62.907803), ('iterateBatter', 48.75), ('fn_3_9E834', 80.090164), ('fn_3_9EA1C', 89.26)]; reverted.
[readability] shuffleU8Array 99.46429%; other regressions []; kept.

## Final status
Final primary-source single-object rebuild and whole-unit diff: .text 99.92008%, 7508 bytes target and ours. shuffleU8Array remains 99.46429%, 1120 bytes; the other 16 functions remain 100%. Neither object has .data, .rodata, .bss or BSS symbols, so BSS-offset verification is vacuous. Unit must remain NonMatching.

## Readability pass
setBatterOutAtBatResult: readability pass: done; detailed abResultFinal/Temporary values have no matching decomp enum (AT_BAT_RESULT refers to a different condensed result code); retained literal evidence.
atBatBuntResult: readability pass: done; detailed abResultFinal/Temporary values have no matching decomp enum (AT_BAT_RESULT refers to a different condensed result code); retained literal evidence.
atBatResultsForOuts: readability pass: done; detailed abResultFinal/Temporary values have no matching decomp enum (AT_BAT_RESULT refers to a different condensed result code); retained literal evidence.
noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance: readability pass: done; detailed abResultFinal/Temporary values have no matching decomp enum (AT_BAT_RESULT refers to a different condensed result code); retained literal evidence.
fn_3_9D550: readability pass: done; detailed abResultFinal/Temporary values have no matching decomp enum (AT_BAT_RESULT refers to a different condensed result code); retained literal evidence.
fn_3_9D594: readability pass: done; detailed abResultFinal/Temporary values have no matching decomp enum (AT_BAT_RESULT refers to a different condensed result code); retained literal evidence.
setStrikeoutOrWalkAtBatResult: readability pass: done; detailed abResultFinal/Temporary values have no matching decomp enum (AT_BAT_RESULT refers to a different condensed result code); retained literal evidence.
setAtBatResult: readability pass: done; detailed abResultFinal/Temporary values have no matching decomp enum (AT_BAT_RESULT refers to a different condensed result code); retained literal evidence.
setDefaultPlayTrackingVariables1: readability pass: done; existing named enum/boolean/count constants used where applicable.
initializeInningTrackers: readability pass: done; existing named enum/boolean/count constants used where applicable.
shuffleU8Array: readability pass: done; existing named enum/boolean/count constants used where applicable.
shuffleIntArray: readability pass: done; existing named enum/boolean/count constants used where applicable.
RandomIndexFromIntWeights: readability pass: done; existing named enum/boolean/count constants used where applicable.
RandomIndexFromWeights: readability pass: done; existing named enum/boolean/count constants used where applicable.
iterateBatter: readability pass: done; existing named enum/boolean/count constants used where applicable.
fn_3_9E834: readability pass: done; existing named enum/boolean/count constants used where applicable.
fn_3_9EA1C: readability pass: done; existing named enum/boolean/count constants used where applicable.
Replaced known reached-base codes0/3, game status1/2, dead-ball home-run1, practice secondary mode0xF, DID_SWING_TYPE_NONE, infield grass/dirt zone bounds, NUM_CHOOSABLE_CHARACTERS; catches/history loop bounds use ARRAY_COUNT with signed cast. taken array now documentary BOOL and TRUE/FALSE.
Remaining untyped code1 for reached base, infield-fly state2, outType4, detailed AB result codes, base encoding and runner masks have no applicable existing named enum. Ghidra inventory lists unpaired atBatResult enum; no headers changed.

## Hypothesis families
manual-inline: manually flatten shuffle body into wrapper (95.310715%). clone-base: same body in separate static inline; tie. clone-game: retain bound in separate absmax as other game RNG helper (98.125%). abs-bound: ABS bound shared helper (shuffle99.19643%, regressed standalone99.3883%). clone-ternary: conditional RNG expression; tie. clone-bound-local/choice-helper: explicit shared bound or nested RNG chooser (96.07143%). k-local-scope C99 declaration rejected by compiler; equivalent C89 block clone-scoped-k tied. r-local-scope/clone-scoped-random: narrow lexical scopes; tie. clone-register-k,first-k,last-k: register storage/local allocation order family; tie. clone-while tie; clone-postdec96.51071%. outer-two-indices/count-local/explicit-count-cast/unsigned-buffer: caller type/scope/local family; all tie. clone-unsigned-r99.25%; unsigned-source/cast-count/cast-k-bound/long-k tie; long-count98.73214%. explicit-output98.77857%; initialize output after k99.457146%, same register rotation and reordered loop decrement. rng-abs-inline/remainder-inline/separate-abs-ret/orig-last/long-ret: helper boundary/return temporary family; tie. rng-ret-expression95.10714%; orig-param96.55357%; ABS bound98.78571%. clone-source-to-r99.17857%.
Compiler diagnostics: inline levels3/4/all andO3 are ties. nocse86.707146%,noschedule64.38928%,nopeephole84.671425%, all regress multiple functions. All bundled compiler versions tried: 1.3.2,1.3.2r,2.0,2.0p1,2.5,2.6,2.7 tie;1.0/1.1/1.1p1/1.2.5/1.2.5n/1.3/3.0a3/3.0a3.2/3.0a3.3/3.0a3.4/3.0a5/3.0a5.2 regress. Exact outcomes above. No shared configure/header/symbol edits.

## Exhaustion and resumption
Current distinct source-shape, helper-inline-boundary, local/cast/lifetime, loop/pointer, compiler-version and relevant optimization hypotheses show no improvement. Marked exhausted for this pass; reopen only with a new structural lead. Residual instruction sequence/opcodes and1120byte size exact; target k/output/max/orig use r25/r26/r27/r28, ours r28/r25/r26/r27, and both RNG remainder temporaries use targetr4/oursr0. Reordering functions documented codegen-neutral and not a remaining lever. Prototype or referenced shared-field changes were deliberately excluded from this unit pass.

## Final source backup
`c
#define SQRT2_LINKAGE static
#include "game/batting/at_bat_results.h"
#include "game/ball/ball_trajectory.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/rand.h"

extern UnkSimulationRelatedStruct g_UnkSimulation_31AC0;
extern u8 superstarUnlocked[0x130];

static inline int randomIntGame(int max) {
    int ret;
    int absmax = max;
    if (absmax < 0) {
        absmax = -absmax;
    }

    if (absmax <= 1) {
        return 0;
    }

    g_Ball.StaticRandomInt1 = g_Ball.StaticRandomInt1 - ((u8)g_Ball.StaticRandomInt2) +
                              g_Ball.StaticRandomInt2 / absmax + g_Ball.totalFramesAtPlay;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_Practice.instructionNumber >= 0) {
        return 0;
    }

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        g_Ball.StaticRandomInt1 += rand();
    }

    ret = g_Ball.StaticRandomInt1 % absmax;
    ret = ABS(ret);
    if (max < 0) {
        return -ret;
    } else {
        return ret;
    }
}

static inline int randomIntGameAbs(int max) {
    int ret;
    int orig = max;
    if (max < 0) {
        max = -max;
    }

    if (max <= 1) {
        return 0;
    }

    g_Ball.StaticRandomInt1 = g_Ball.StaticRandomInt1 - ((u8)g_Ball.StaticRandomInt2) +
                              g_Ball.StaticRandomInt2 / max + g_Ball.totalFramesAtPlay;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_Practice.instructionNumber >= 0) {
        return 0;
    }

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        g_Ball.StaticRandomInt1 += rand();
    }

    ret = g_Ball.StaticRandomInt1 % max;
    ret = ABS(ret);
    if (orig < 0) {
        return -ret;
    } else {
        return ret;
    }
}

static inline int randomIntSim(int max) {
    int ret, r2;
    int orig = max;
    if (max < 0) {
        max = -max;
    }

    if (max <= 1) {
        return 0;
    }
    g_UnkSimulation_31AC0._00 = g_UnkSimulation_31AC0._00 + g_d_GameSettings.FrameCountWhileNotAtMainMenu +
                                (g_d_GameSettings.FrameCountWhileNotAtMainMenu >> 1) - g_Ball.StaticRandomInt1 +
                                ((u8)g_Ball.StaticRandomInt2) + (g_UnkSimulation_31AC0._00 / max);
    ret = g_UnkSimulation_31AC0._00 % (u32)max;
    r2 = ABS(ret);

    if (orig < 0) {
        return -r2;
    } else {
        return r2;
    }
}

// .text:0x0009CD90 size:0xE8 mapped:0x806DBE24
void setBatterOutAtBatResult(void) {
    int i;

    if (storedInningInfo.abResultTemporary != 0) {
        return;
    }
    if (g_Strikes.howRunnerReachedBase == REACHED_BASE_FIELDERS_CHOICE_ERROR) {
        storedInningInfo.abResultFinal = 0x10;
        return;
    }
    if (g_Runners[0].runnerOnFieldOrOutOrScored == RUNNER_STATUS_OUT_DURING_PLAY) {
        if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT || g_FieldingLogic.infieldFlyIndicator == 2) {
            if (g_Ball.Hit_VerticalAngle > 0xA0) {
                storedInningInfo.abResultTemporary = 0x12;
            } else {
                storedInningInfo.abResultTemporary = 0x13;
            }
        } else {
            storedInningInfo.abResultTemporary = 0x15;
        }
    }
    for (i = 1; i < 4; i++) {
        if (g_Runners[i].forceOutCd == FORCE_OUT_TYPE_OUT_ON_FORCE) {
            storedInningInfo.abResultTemporary = 0x15;
        }
    }
}

// .text:0x0009CE78 size:0x2C8 mapped:0x806DBF0C
void atBatBuntResult(void) {
    BOOL runnerAdvanced;
    int i;

    if (g_RunningLogic.nOffensivePlayersAtStartOfPlay == 1 || g_Strikes.storedOuts == 2) {
        if ((g_Runners[0].runnerOnFieldOrOutOrScored == RUNNER_STATUS_OUT_DURING_PLAY &&
             g_Strikes.howRunnerReachedBase == REACHED_BASE_TBD) ||
            g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT) {
            storedInningInfo.abResultFinal = 0x1D;
            return;
        }
        if (g_Runners[0].forceOutCd == FORCE_OUT_TYPE_NOT_FORCED_TO_ADVANCE) {
            storedInningInfo.abResultFinal = 0x1C;
        }
        return;
    }

    if (g_Runners[3].runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE && g_Runners[3].furthestBaseForcedToGoToOnWalk != 0) {
        if (g_Runners[3].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) {
            if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT) {
                storedInningInfo.abResultTemporary = 0x20;
            } else {
                storedInningInfo.abResultFinal = 0x1E;
            }
            return;
        }
        if (g_Runners[3].runnerOnFieldOrOutOrScored == RUNNER_STATUS_OUT_DURING_PLAY) {
            storedInningInfo.abResultFinal = 0x1F;
        }
        return;
    }

    if (g_Scores._9E > g_Scores.scores[g_Scores.halfInning].byInning[g_Scores.Inning - 1]) {
        storedInningInfo.abResultTemporary = 0x20;
        return;
    }

    if (storedInningInfo.abResultTemporary == 0x22) {
        return;
    }
    if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT) {
        storedInningInfo.abResultTemporary = 0x22;
        return;
    }
    for (i = 1; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE &&
            g_Runners[i].currentBase == g_Runners[i].startingBase_baseAchieved &&
            g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_OUT_DURING_PLAY) {
            storedInningInfo.abResultTemporary = 0x22;
            return;
        }
    }

    runnerAdvanced = FALSE;
    for (i = 1; i < 4; i++) {
        if ((g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD ||
             g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) &&
            g_Runners[i].currentBase != g_Runners[i].startingBase_baseAchieved) {
            runnerAdvanced = TRUE;
            break;
        }
    }
    if (runnerAdvanced) {
        storedInningInfo.abResultTemporary = 0x21;
    }
}

// .text:0x0009D140 size:0x234 mapped:0x806DC1D4
void atBatResultsForOuts(void) {
    int forcedOuts;
    int i;

    if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT || g_FieldingLogic.infieldFlyIndicator == 2) {
        forcedOuts = 0;
        for (i = 1; i < 3; i++) {
            if (g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_OUT_DURING_PLAY && g_Runners[i].outType == 4) {
                forcedOuts++;
            }
        }
        if (forcedOuts == 2) {
            storedInningInfo.abResultFinal = 0x17;
            return;
        }
        if (forcedOuts == 1) {
            storedInningInfo.abResultTemporary = 0x1A;
        }
    }

    if (g_Strikes.storedOuts + 3 == g_Strikes.outs && g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FIELDED) {
        if (g_Strikes.outs == 3 || g_RunningLogic._10 == 0) {
            storedInningInfo.abResultFinal = 0x17;
            if (storedInningInfo.catches[2].outsDuringPossession == 3 ||
                storedInningInfo.catches[3].outsDuringPossession == 3) {
                storedInningInfo.abResultFinal = 0x16;
                return;
            }
        }
    }

    if (g_Strikes.storedOuts + 2 == g_Strikes.outs && g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FIELDED) {
        storedInningInfo.abResultTemporary = 0x19;
        if (storedInningInfo.catches[2].fielderIndex == 2 && storedInningInfo.catches[0].outsDuringPossession == 0 &&
            storedInningInfo.catches[1].outsDuringPossession == 1) {
            storedInningInfo.abResultTemporary = 0x18;
        }
        if (storedInningInfo.catches[3].fielderIndex >= 0 && storedInningInfo.catches[2].outsDuringPossession == 2) {
            storedInningInfo.abResultFinal = storedInningInfo.abResultTemporary;
            return;
        }
    }

    if (g_Strikes.storedOuts + 1 == g_Strikes.outs && g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FIELDED &&
        storedInningInfo.catches[2].fielderIndex == 2 && storedInningInfo.catches[0].outsDuringPossession == 0) {
        s8 base = storedInningInfo.catches[1].baseStandingOn;
        if (g_Runners[(base + 3) & 3].forcedToAdvanceInd != 0 && base >= 0 && base != 1 &&
            storedInningInfo.catches[1].outsDuringPossession == 1 &&
            storedInningInfo.catches[2].outsDuringPossession == 1 && storedInningInfo.catches[2].baseStandingOn == 1) {
            storedInningInfo.abResultTemporary = 0x14;
        }
    }
}

// .text:0x0009D374 size:0x1DC mapped:0x806DC408
BOOL noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance(void) {
    s16 baseEarned;
    int runsThisPlay;
    BOOL runnerScoredOnlyRun = FALSE;

    if (g_Strikes.howRunnerReachedBase == 1) {
        runsThisPlay = g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total - g_Scores._A0;
        if (runsThisPlay == 1 && g_Runners[0].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) {
            runnerScoredOnlyRun = TRUE;
        }
        baseEarned = g_Runners[0].baseNumberEarned_NotIncludingFieldersChoice;
        if (baseEarned == 0 && g_Runners[0].runnerOnFieldOrOutOrScored == RUNNER_STATUS_SCORED_DURING_PLAY) {
            storedInningInfo.abResultFinal = 5;
        } else if (baseEarned == 3) {
            if (runsThisPlay != 0 && !runnerScoredOnlyRun) {
                storedInningInfo.abResultFinal = 6;
            } else {
                storedInningInfo.abResultTemporary = 0xB;
            }
        } else if (baseEarned == 2) {
            if (runsThisPlay != 0 && !runnerScoredOnlyRun) {
                storedInningInfo.abResultFinal = 7;
            } else {
                storedInningInfo.abResultTemporary = 0xC;
            }
        } else if (baseEarned == 1) {
            s8 zone = g_Ball.ballZoneWhenCaught;
            if (zone >= BALL_ZONE_IF_GRASS && zone <= BALL_ZONE_IF_DIRT) {
                if (runsThisPlay != 0 && !runnerScoredOnlyRun) {
                    storedInningInfo.abResultFinal = 9;
                } else {
                    storedInningInfo.abResultTemporary = 0xE;
                }
            } else {
                if (runsThisPlay != 0 && !runnerScoredOnlyRun) {
                    storedInningInfo.abResultFinal = 8;
                } else {
                    storedInningInfo.abResultTemporary = 0xD;
                }
            }
        } else {
            if (runsThisPlay != 0 && !runnerScoredOnlyRun) {
                storedInningInfo.abResultTemporary = 0xA;
            } else {
                storedInningInfo.abResultTemporary = 0xF;
            }
        }
        return TRUE;
    }
    return FALSE;
}

// .text:0x0009D550 size:0x44 mapped:0x806DC5E4
void fn_3_9D550(void) {
    if (g_Ball.maybeBuntInd != 0 && g_Strikes.strikes >= 3) {
        storedInningInfo.abResultFinal = 0x27;
    } else {
        storedInningInfo.abResultFinal = 0x2C;
    }
}

// .text:0x0009D594 size:0x6C mapped:0x806DC628
void fn_3_9D594(void) {
    switch (g_RunningLogic.nOffensivePlayersAtStartOfPlay) {
        case 4:
            storedInningInfo.abResultFinal = 1;
            break;
        case 3:
            storedInningInfo.abResultFinal = 2;
            break;
        case 2:
            storedInningInfo.abResultFinal = 3;
            break;
        default:
            storedInningInfo.abResultFinal = 4;
            break;
    }
}

// .text:0x0009D600 size:0xA4 mapped:0x806DC694
void setStrikeoutOrWalkAtBatResult(void) {
    if (g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT) {
        if (g_Batter.missedBuntStatus != 0) {
            storedInningInfo.abResultTemporary = 0x26;
        } else if (g_Batter.missSwingOrBunt != DID_SWING_TYPE_NONE) {
            storedInningInfo.abResultTemporary = 0x24;
        } else {
            storedInningInfo.abResultTemporary = 0x25;
        }
    } else if (g_Pitcher.strikeOutOrWalk == AT_BAT_END_WALK) {
        storedInningInfo.abResultTemporary = 0x2A;
    } else if (g_Pitcher.strikeOutOrWalk == AT_BAT_END_HIT_BY_PITCH) {
        storedInningInfo.abResultFinal = 0x2B;
    }
}

// .text:0x0009D6A4 size:0x4B8 mapped:0x806DC738
void setAtBatResult(void) {
    BOOL fielderTracked = FALSE;
    int i;
    s16 fielder;
    s16 coverage;

    if (g_Stats.replayInd != 0) {
        return;
    }
    if (storedInningInfo.abResultFinal == 0) {
        if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd == 4) {
            storedInningInfo.abResultFinal = 0x28;
        } else if (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT) {
            setStrikeoutOrWalkAtBatResult();
        } else if (g_Ball.deadBallReason == DEAD_BALL_REASON_HOME_RUN) {
            fn_3_9D594();
        } else if (g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FOUL) {
            fn_3_9D550();
        } else {
            if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL) {
                fielder = g_Ball.fielderWBallIndex;
                if (fielder >= 0) {
                    if (storedInningInfo.fielderWithBallIndex == -1) {
                        for (i = 0; i < (int)ARRAY_COUNT(storedInningInfo.catches); i++) {
                            if (storedInningInfo.catches[i].fielderIndex == -1) {
                                storedInningInfo.catches[i].fielderIndex = fielder;
                                storedInningInfo.catches[i].outsDuringPossession = g_Strikes.outs - g_Strikes.storedOuts;
                                coverage = g_Fielders[fielder].locationResponsibleForCovering;
                                if (coverage >= 0 && coverage <= 3) {
                                    switch (coverage) {
                                        case 0:
                                            if ((g_RunningLogic._02 & 0x1111) == 0x1111) {
                                                storedInningInfo.catches[i].baseStandingOn = 0;
                                            }
                                            break;
                                        case 1:
                                            storedInningInfo.catches[i].baseStandingOn = 1;
                                            break;
                                        case 2:
                                            if ((g_RunningLogic._02 & 0x11) == 0x11) {
                                                storedInningInfo.catches[i].baseStandingOn = 2;
                                            }
                                            break;
                                        default:
                                            if ((g_RunningLogic._02 & 0x111) == 0x111) {
                                                storedInningInfo.catches[i].baseStandingOn = 3;
                                            }
                                            break;
                                    }
                                }
                                break;
                            }
                        }
                        fielderTracked = TRUE;
                    } else if (storedInningInfo.fielderWithBallIndex == fielder) {
                        for (i = (int)ARRAY_COUNT(storedInningInfo.catches) - 1; i >= 0; i--) {
                            if (storedInningInfo.catches[i].fielderIndex == fielder) {
                                if (g_Ball.timeSinceBallPickedUp <= 60) {
                                    storedInningInfo.catches[i].outsDuringPossession =
                                        g_Strikes.outs - g_Strikes.storedOuts;
                                }
                                break;
                            }
                        }
                        fielderTracked = TRUE;
                    }
                }
                storedInningInfo.fielderWithBallIndex = fielder;
            }
            if (g_Ball.maybeBuntInd != 0) {
                atBatBuntResult();
            } else if (!noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance()) {
                if (fielderTracked) {
                    atBatResultsForOuts();
                }
                setBatterOutAtBatResult();
            }
        }
    }
    categorizeBallTrajectory();
    if (storedInningInfo.abResultFinal != 0) {
        storedInningInfo.abResultTemporary = storedInningInfo.abResultFinal;
    }
}

// .text:0x0009DB5C size:0x88 mapped:0x806DCBF0
void setDefaultPlayTrackingVariables1(void) {
    int i;

    for (i = (int)ARRAY_COUNT(storedInningInfo._06) - 1; i > 0; i--) {
        storedInningInfo._06[i] = storedInningInfo._06[i - 1];
    }
    storedInningInfo._06[0] = storedInningInfo.abResultFinal;
    storedInningInfo.abResultTemporary = 0;
    storedInningInfo.abResultFinal = 0;
    storedInningInfo.situation = 0;
    for (i = 0; i < (int)ARRAY_COUNT(storedInningInfo.catches); i++) {
        storedInningInfo.catches[i].fielderIndex = -1;
        storedInningInfo.catches[i].outsDuringPossession = -1;
        storedInningInfo.catches[i].baseStandingOn = -1;
    }
    storedInningInfo.fielderWithBallIndex = -1;
}

// .text:0x0009DBE4 size:0x34 mapped:0x806DCC78
void initializeInningTrackers(void) {
    storedInningInfo.inningOfFirstRun = 0;
    storedInningInfo.inningOfLastTie = 0;
    storedInningInfo.comebackCounter = 0;
    storedInningInfo.inningOfComeback = 0;
    storedInningInfo.comebackCounter2 = 0;
    storedInningInfo.inningOfLeadTakenBack = 0;
    storedInningInfo.leadsTakenBack = 0;
    storedInningInfo.inningOfGoAheadRun = 0;
    storedInningInfo.goAheadRunOccurrences = 0;
}

// .text:0x0009DC18 size:0x460 mapped:0x806DCCAC
void shuffleU8Array(u8* values, int count, BOOL useGameRandom) {
    int result[10];
    u32 u;

    for (u = 0; u < count; u++) {
        result[u] = values[u];
    }
    shuffleIntArray(result, count, useGameRandom);
    for (u = 0; u < count; u++) {
        values[u] = result[u];
    }
}

// .text:0x0009E078 size:0x2F0 mapped:0x806DD10C
void shuffleIntArray(int* values, int count, BOOL useGameRandom) {
    int source[20];
    BOOL taken[20];
    int i;
    int j;
    int k;
    int r;

    for (i = 0; i < count; i++) {
        source[i] = values[i];
        taken[i] = FALSE;
    }
    for (k = count - 1; k >= 0; k--) {
        if (useGameRandom) {
            r = randomIntGameAbs(k + 1);
        } else {
            r = randomIntSim(k + 1);
        }
        for (j = 0; j < count; j++) {
            if (!taken[j]) {
                if (r == 0) {
                    values[k] = source[j];
                    taken[j] = TRUE;
                    break;
                }
                r--;
            }
        }
    }
}

// .text:0x0009E368 size:0x238 mapped:0x806DD3FC
int RandomIndexFromIntWeights(int* weights, int count) {
    int buf[10];
    int total = 0;
    int i;
    int r;

    for (i = 0; i < count; i++) {
        buf[i] = weights[i];
        total += buf[i];
    }
    r = randomIntGame(total);
    for (i = 0; i < count; i++) {
        if (r < buf[i]) {
            return i;
        }
        r -= buf[i];
    }
    return 0;
}

// .text:0x0009E5A0 size:0x234 mapped:0x806DD634
int RandomIndexFromWeights(u8* weights, int count) {
    int buf[10];
    int total = 0;
    int i;
    int r;

    for (i = 0; i < count; i++) {
        buf[i] = weights[i];
        total += buf[i];
    }
    r = randomIntGame(total);
    for (i = 0; i < count; i++) {
        if (r < buf[i]) {
            return i;
        }
        r -= buf[i];
    }
    return 0;
}

// .text:0x0009E7D4 size:0x60 mapped:0x806DD868
void iterateBatter(int team) {
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_FREE_BAT_AND_RUNNING) {
        return;
    }
    if (g_GameLogic.currentBatterPerTeam[team] == 9) {
        g_GameLogic.currentBatterPerTeam[team] = 1;
    } else {
        g_GameLogic.currentBatterPerTeam[team]++;
    }
}

// .text:0x0009E834 size:0x1E8 mapped:0x806DD8C8
BOOL fn_3_9E834(void) {
    int i;

    if (!g_d_GameSettings.exhibitionMatchInd) {
        for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
            if (g_Challenge.charIsSuperstar[i] != 0) {
                return TRUE;
            }
        }
    } else {
        for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
            if (superstarUnlocked[i] != 0) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

// .text:0x0009EA1C size:0xC8 mapped:0x806DDAB0
BOOL fn_3_9EA1C(int team) {
    int i;

    for (i = 1; i < 10; i++) {
        if (g_GameLogic.battingOrderAndPositionMapping[team][i][1] % 10 == 9) {
            return TRUE;
        }
    }
    return FALSE;
}
`

[Astra reuse_k_i] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 99.89286, 'shuffleIntArray': 100.0, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 99.98402}; primary source untouched, improvement saved in build\astra_priority\reuse_k_i.

[Astra reuse_j_i] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 99.10714, 'shuffleIntArray': 100.0, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 99.866806}; primary source untouched, rejected/tied in build\astra_priority\reuse_j_i.

[Astra reuse_r_i] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 99.17857, 'shuffleIntArray': 100.0, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 99.877464}; primary source untouched, rejected/tied in build\astra_priority\reuse_r_i.

[Astra argorder_021] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 99.46429, 'shuffleIntArray': 100.0, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 99.92008}; primary source untouched, rejected/tied in build\astra_priority\argorder_021.

[Astra argorder_102] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 99.46429, 'shuffleIntArray': 100.0, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 99.92008}; primary source untouched, rejected/tied in build\astra_priority\argorder_102.

[Astra argorder_120] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 99.46429, 'shuffleIntArray': 100.0, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 99.92008}; primary source untouched, rejected/tied in build\astra_priority\argorder_120.

[Astra argorder_201] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 99.46429, 'shuffleIntArray': 100.0, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 99.92008}; primary source untouched, rejected/tied in build\astra_priority\argorder_201.

[Astra argorder_210] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 99.46429, 'shuffleIntArray': 100.0, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 99.92008}; primary source untouched, rejected/tied in build\astra_priority\argorder_210.

[Astra reuse_i_shared] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 99.89286, 'shuffleIntArray': 100.0, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 99.98402}; primary source untouched, improvement saved in build\astra_priority\reuse_i_shared.

[Astra abs_cast] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 94.58929, 'shuffleIntArray': 100.0, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 99.19286}; primary source untouched, rejected/tied in build\astra_priority\abs_cast.

[Astra abs_u32_cast] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 94.58929, 'shuffleIntArray': 100.0, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 99.19286}; primary source untouched, rejected/tied in build\astra_priority\abs_u32_cast.

[Astra abs_inline_cast] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 99.89286, 'shuffleIntArray': 100.0, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 99.98402}; primary source untouched, rejected/tied in build\astra_priority\abs_inline_cast.

[Astra abs_inline_long] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 99.89286, 'shuffleIntArray': 100.0, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 99.98402}; primary source untouched, rejected/tied in build\astra_priority\abs_inline_long.

[Astra ret_reuse_max] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 99.89286, 'shuffleIntArray': 100.0, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 99.98402}; primary source untouched, rejected/tied in build\astra_priority\ret_reuse_max.

[Astra ret_return_abs] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 97.71429, 'shuffleIntArray': 100.0, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 99.65903}; primary source untouched, rejected/tied in build\astra_priority\ret_return_abs.

[Astra builtin_abs_all] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 99.71429, 'shuffleIntArray': 99.28191, 'RandomIndexFromIntWeights': 99.50704, 'RandomIndexFromWeights': 99.50355, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 99.81087}; primary source untouched, rejected/tied in build\astra_priority\builtin_abs_all.

[Astra builtin_abs_shuffle] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 99.71429, 'shuffleIntArray': 99.28191, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 99.88545}; primary source untouched, rejected/tied in build\astra_priority\builtin_abs_shuffle.

[Astra abs_if] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 97.44643, 'shuffleIntArray': 96.19681, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 99.238144}; primary source untouched, rejected/tied in build\astra_priority\abs_if.

[Astra abs_ternary_gt] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 99.89286, 'shuffleIntArray': 100.0, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 99.98402}; primary source untouched, rejected/tied in build\astra_priority\abs_ternary_gt.

[Astra abs_ternary_ge] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 99.89286, 'shuffleIntArray': 100.0, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 99.98402}; primary source untouched, rejected/tied in build\astra_priority\abs_ternary_ge.

[Astra abs_sign_long] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 99.60714, 'shuffleIntArray': 100.0, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 99.9414}; primary source untouched, rejected/tied in build\astra_priority\abs_sign_long.

[Astra abs_unsigned_neg] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 94.875, 'shuffleIntArray': 92.393616, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 98.473625}; primary source untouched, rejected/tied in build\astra_priority\abs_unsigned_neg.

[Astra ret_unsigned] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 99.60714, 'shuffleIntArray': 100.0, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 99.9414}; primary source untouched, rejected/tied in build\astra_priority\ret_unsigned.

[Astra mod_in_abs] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 95.16071, 'shuffleIntArray': 93.24468, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 98.601494}; primary source untouched, rejected/tied in build\astra_priority\mod_in_abs.

[Astra abs_reuse_orig] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 95.53571, 'shuffleIntArray': 93.61702, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 98.694725}; primary source untouched, rejected/tied in build\astra_priority\abs_reuse_orig.

[Astra ret_block] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 99.89286, 'shuffleIntArray': 100.0, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 99.98402}; primary source untouched, rejected/tied in build\astra_priority\ret_block.

[Astra ret_const_block] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 99.89286, 'shuffleIntArray': 100.0, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 99.98402}; primary source untouched, rejected/tied in build\astra_priority\ret_const_block.

[Astra orig_const] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 99.89286, 'shuffleIntArray': 100.0, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 99.98402}; primary source untouched, rejected/tied in build\astra_priority\orig_const.

[Astra ret_register] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 99.89286, 'shuffleIntArray': 100.0, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 99.98402}; primary source untouched, rejected/tied in build\astra_priority\ret_register.

[Astra ret_enum] {'setBatterOutAtBatResult': 100.0, 'atBatBuntResult': 100.0, 'atBatResultsForOuts': 100.0, 'noForceOutInd_atBatResultsAfterForcedRunnersAllAdvance': 100.0, 'fn_3_9D550': 100.0, 'fn_3_9D594': 100.0, 'setStrikeoutOrWalkAtBatResult': 100.0, 'setAtBatResult': 100.0, 'setDefaultPlayTrackingVariables1': 100.0, 'initializeInningTrackers': 100.0, 'shuffleU8Array': 99.60714, 'shuffleIntArray': 100.0, 'RandomIndexFromIntWeights': 100.0, 'RandomIndexFromWeights': 100.0, 'iterateBatter': 100.0, 'fn_3_9E834': 100.0, 'fn_3_9EA1C': 100.0}; sections {'.text': 99.9414}; primary source untouched, rejected/tied in build\astra_priority\ret_enum.

## Astra follow-up final (2026-10-13)

Current section .text: **99.98402%**, target/ours 7508 bytes; no .rodata/.data/.bss. shuffleU8Array: **99.89286%**, target/ours 1120 bytes; all other 16 functions remain 100%. Fresh primary-source Ninja build plus full-unit diff confirmed the retained change. Four completed priority units also freshly rebuilt/rechecked: every function and section remains 100%.

The successful new hypothesis was variable identity rather than declaration order: reuse the initialization-loop counter `i` for the descending shuffle loop, deleting `k`. Initially verified in a diagnostic inline clone, then applied to the original shared shuffleIntArray: both forms improve shuffleU8Array identically and standalone shuffleIntArray stays 100%. The committed-source edit uses the shared function; no duplicate helper remains. Readability pass: shuffleIntArray and shuffleU8Array done; existing BOOL, FALSE/TRUE and natural loop indices retained, no new numeric literals or matching comments.

This removes the saved-register rotation completely. Residual target(left)/ours(right), offsets within shuffleU8Array:
- +0x290: subf r4,r0,r3 / subf r0,r0,r3
- +0x294: srawi r3,r4,31 / srawi r3,r0,31
- +0x298: xor r0,r3,r4 / xor r0,r3,r0
- +0x318: subf r4,r0,r3 / subf r0,r0,r3
- +0x31C: srawi r3,r4,31 / srawi r3,r0,31
- +0x320: xor r0,r3,r4 / xor r0,r3,r0
Every other instruction matches, including sizes and opcodes. Remaining sites are game/simulation RNG remainder absolute values in the inlined shuffle.

Additional distinct families tested against this improved baseline: helper argument permutations; reusing initialization counter as inner scan/RNG result; explicit/no-op ABS operand casts; nested ABS helper with int/long argument; remainder reusing max; returning absolute values directly; MWCC __abs builtin (regresses matched siblings); equivalent positive-polarity ABS ternaries; statement-if ABS; unsigned negation and unsigned remainder local; modulo embedded directly inside ABS; sign/original-bound local reuse; ret in a tail scope, const tail temporary, const original bound, register ret and enum ret. None improved all functions. Each result is logged above, with exact candidate source and full-unit JSON under build/astra_priority/<label>. Existing old final-source backup is superseded only in the function below; full current source is src/game/batting/at_bat_results.c. No shared headers/config/symbol/split changes. Still NonMatching; residual marked exhausted for this follow-up.

Retained shared function:
```c
void shuffleIntArray(int* values, int count, BOOL useGameRandom) {
    int source[20];
    BOOL taken[20];
    int i;
    int j;
    int r;

    for (i = 0; i < count; i++) {
        source[i] = values[i];
        taken[i] = FALSE;
    }
    for (i = count - 1; i >= 0; i--) {
        if (useGameRandom) {
            r = randomIntGameAbs(i + 1);
        } else {
            r = randomIntSim(i + 1);
        }
        for (j = 0; j < count; j++) {
            if (!taken[j]) {
                if (r == 0) {
                    values[i] = source[j];
                    taken[j] = TRUE;
                    break;
                }
                r--;
            }
        }
    }
}

```
