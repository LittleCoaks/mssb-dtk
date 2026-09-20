#include "game/fielding/fielder_ai.h"
#include "game/ball/collision_primitives.h"
#include "game/UnknownHomes_Game.h"
#include "game/math/game_math.h"
#include "header_rep_data.h"
#include "static/UnknownHomes_static.h"

extern const f32 lbl_3_rodata_1938;
extern const f32 lbl_3_rodata_193C;
extern const f32 lbl_3_rodata_1958;
extern const f32 lbl_3_rodata_195C;
extern const f32 lbl_3_rodata_1960;
extern const f32 lbl_3_rodata_1964;
extern const f32 lbl_3_rodata_1968;
extern const f32 lbl_3_rodata_196C;
extern const f32 lbl_3_rodata_1970;
extern const f32 lbl_3_rodata_1974;
extern const f32 lbl_3_rodata_199C;
extern const f32 lbl_3_rodata_19EC;
extern const f32 lbl_3_rodata_1980;
extern const f32 lbl_3_rodata_1984;
extern const f32 lbl_3_rodata_1988;
extern const f32 lbl_3_rodata_198C;
extern const f32 lbl_3_rodata_1990;
extern const f32 lbl_3_rodata_1994;
extern const f32 lbl_3_rodata_1998;
extern const f32 lbl_3_rodata_19A0;
extern const f32 lbl_3_rodata_19A4;
extern const f32 lbl_3_rodata_19A8;
extern const f32 lbl_3_rodata_19AC;
extern const f32 lbl_3_rodata_19B4;
extern const f32 lbl_3_rodata_19B8;
extern const f32 lbl_3_rodata_19B0;
extern const f32 lbl_3_rodata_19BC;
extern const f32 lbl_3_rodata_19C0;
extern const f32 lbl_3_rodata_19E8;
extern const f32 lbl_3_rodata_19F0;
extern const f32 lbl_3_rodata_1A0C;
extern const f32 lbl_3_rodata_1A10;
extern const f32 lbl_3_rodata_1A14;
extern const f32 lbl_3_rodata_1A18;
extern const f32 lbl_3_rodata_197C;
extern const f32 lbl_3_rodata_1978;
extern const f32 lbl_3_rodata_19F4;
extern const f32 lbl_3_rodata_19F8;
extern const f32 lbl_3_rodata_19FC;
extern const f32 lbl_3_rodata_1A00;
extern const f32 lbl_3_rodata_1A04;
extern const f32 lbl_3_rodata_1A08;
extern u8 lbl_3_data_1C38[2];
extern u8 lbl_3_data_475C;
int fRunningTimeToDestinationPlus7(int fielderIndex);
extern const u8 throwSpeedArray[];
extern const f32 lbl_3_rodata_1A2C;
extern const f32 lbl_3_rodata_1A30;
extern const f32 lbl_3_rodata_1A34;
extern const f32 lbl_3_rodata_1A4C;
extern const f32 lbl_3_rodata_1A50;
extern const f32 lbl_3_rodata_1A54;
typedef struct {
    s16 ballAngleLower;
    s16 ballAngleUpper;
    s16 _4;
} BodyCheckBallAngles;
extern BodyCheckBallAngles bodyCheckBallAngles[4];
void fn_8004AFA8(int index);
void fn_8004AE18(int index);
int updateFielderPosition_checkFielderCollision(int fielderIndex, VecXYZ* out);
extern const u8 throwWindUpFrames[];
extern VecXZ base_MoundCoordinates[5];
void setFielderAutoCoords(int fielderIndex, f32 x, f32 z);
void ifCurrentFielderIsTakingOverBaseCovering(int fielderIndex, int newLocation);
void setFielderVelocity(int fielderIndex);
extern f32 thresholdToBeConsideredCoveringBase_ByWeight[5];

static s32 fielderDesperationLevel[42];
static s32 runningStratToMakePlay[8];
static s32 throwStratToMakePlay[4];
static u32 hexBaserunnerTracker;
static s32 numRunnersOnField;
static s32 urgencyLevel;
static s32 originalBaseOfRunnerInThisBaseline[5];
static u32 hexMovementsInEachBaseline1for2back4stop[2];
static s32 lbl_3_bss_17F8[2];

// .text:0x000A009C size:0x1C68 mapped:0x806DF130
void fielderAIDecideWhatRunnerToTarget(void) {
    return;
}

// .text:0x000A1D04 size:0x9C mapped:0x806E0D98
int fn_3_A1D04(void) {
    int prev;
    int i;
    InMemRunnerType* runner = &g_Runners[3];
    f32 best = lbl_3_rodata_1978;

    for (i = 3; i >= 0; i--) {
        if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
            f32 pos = runner->fractionalBasesRan;
            f32 diff = pos - best;
            if (diff < lbl_3_rodata_193C) {
                diff = -diff;
            }
            if (diff < lbl_3_rodata_197C) {
                if (g_Runners[prev].baseStandingOn < 0) {
                    return prev;
                }
                return i;
            }
            best = pos;
            prev = i;
        }
        runner--;
    }
    return -1;
}

// .text:0x000A1DA0 size:0x19C mapped:0x806E0E34
BOOL fn_3_A1DA0(void) {
    InMemFielder* fielder = &g_Fielders[g_Ball.fielderWBallIndex];

    if (fielder->distanceFromHomePlate > lbl_3_rodata_196C - lbl_3_rodata_1980 * (100 - fielder->throwingArm)) {
        return 0;
    }
    if (g_Runners[3].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
        g_Runners[3].fractionalBasesRan < lbl_3_rodata_1984 &&
        (g_Runners[3].runningDirectionCode == 2 || g_Runners[3].runningDirectionCode == 1)) {
    } else if (g_Runners[2].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
               g_Runners[2].fractionalBasesRan > lbl_3_rodata_1988 &&
               g_Runners[2].fractionalBasesRan <= lbl_3_rodata_1984 && g_Runners[3].runningDirectionCode == 1 &&
               g_Runners[2].tagUpInd == TAG_UP_TYPE_NONE) {
    } else {
        return 0;
    }
    if (g_Runners[1].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
        if (g_Runners[1].tagUpInd != TAG_UP_TYPE_NONE) {
            if (g_Runners[1].fractionalBasesRan > lbl_3_rodata_198C) {
                return 0;
            }
        } else if (g_Runners[1].forceOutCd == FORCE_OUT_TYPE_FORCED_TO_ADVANCE) {
            if (g_Runners[1].fractionalBasesRan <= lbl_3_rodata_1990) {
                return 0;
            }
        }
    }
    g_FieldingLogic.locationThrownTo = 0;
    g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
    g_FieldingLogic.runnerChasingAfter = -1;
    return 1;
}

// .text:0x000A1F3C size:0x10C mapped:0x806E0FD0
BOOL fn_3_A1F3C(void) {
    int base;
    int i;

    if (g_Ball.ballZoneAwayFromHome >= 3) {
        return 0;
    }
    base = originalBaseOfRunnerInThisBaseline[3];
    if (base < 0 || base > 3) {
        return 0;
    }
    if (fielderDesperationLevel[base] >= 7) {
        return 0;
    }
    if (g_Runners[base].tagUpInd != TAG_UP_TYPE_NONE) {
        return 0;
    }
    if (base >= 1) {
        for (i = base - 1; i >= 0; i--) {
            f32 pct = g_Runners[i].percentTowardsNextBase;
            if (pct > lbl_3_rodata_19BC && pct < lbl_3_rodata_19C0) {
                return 0;
            }
        }
    }
    if (fielderAIMakePlay(base) != 0) {
        return 1;
    }
    return 0;
}

// .text:0x000A2048 size:0x1E4 mapped:0x806E10DC
void fielderAIWeirdSituation(void) {
    return;
}

// .text:0x000A222C size:0x1D8 mapped:0x806E12C0
BOOL canThrowOutRunnerWhoNeedsToTagUp(void) {
    int order[3];
    int* p;
    int i;
    int base;

    if (g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_CAUGHT) {
        return 0;
    }
    if (numRunnersOnField == 0) {
        return 0;
    }
    if (g_Ball.ballDistanceFromBase[1] < g_Ball.ballDistanceFromBase[3]) {
        if (g_Ball.ballDistanceFromBase[2] < g_Ball.ballDistanceFromBase[1]) {
            order[0] = 2;
            order[1] = 1;
            order[2] = 3;
        } else if (g_Ball.ballDistanceFromBase[2] < g_Ball.ballDistanceFromBase[3]) {
            order[0] = 1;
            order[1] = 2;
            order[2] = 3;
        } else {
            order[0] = 1;
            order[1] = 3;
            order[2] = 2;
        }
    } else if (g_Ball.ballDistanceFromBase[2] < g_Ball.ballDistanceFromBase[3]) {
        order[0] = 2;
        order[1] = 3;
        order[2] = 1;
    } else if (g_Ball.ballDistanceFromBase[2] < g_Ball.ballDistanceFromBase[1]) {
        order[0] = 3;
        order[1] = 2;
        order[2] = 1;
    } else {
        order[0] = 3;
        order[1] = 1;
        order[2] = 2;
    }
    p = order;
    for (i = 0; i < 3; i++) {
        base = *p;
        if (g_Runners[base].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
            g_Runners[base].tagUpInd == TAG_UP_TYPE_TAGGED && fielderDesperationLevel[base] <= 4 &&
            g_Ball.ballDistanceFromBase[base] < lbl_3_rodata_19E8 && fielderAIMakePlay(base) != 0) {
            return 1;
        }
        p++;
    }
    return 0;
}

// .text:0x000A2404 size:0x1C0 mapped:0x806E1498
BOOL throwOutRunnerTaggingUpInd(void) {
    int order[3];
    int* p;
    int i;
    int base;

    if (g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_CAUGHT) {
        return 0;
    }
    if (numRunnersOnField == 0) {
        return 0;
    }
    if (g_Ball.ballDistanceFromBase[1] < g_Ball.ballDistanceFromBase[3]) {
        if (g_Ball.ballDistanceFromBase[2] < g_Ball.ballDistanceFromBase[1]) {
            order[0] = 2;
            order[1] = 1;
            order[2] = 3;
        } else if (g_Ball.ballDistanceFromBase[2] < g_Ball.ballDistanceFromBase[3]) {
            order[0] = 1;
            order[1] = 2;
            order[2] = 3;
        } else {
            order[0] = 1;
            order[1] = 3;
            order[2] = 2;
        }
    } else if (g_Ball.ballDistanceFromBase[2] < g_Ball.ballDistanceFromBase[3]) {
        order[0] = 2;
        order[1] = 3;
        order[2] = 1;
    } else if (g_Ball.ballDistanceFromBase[2] < g_Ball.ballDistanceFromBase[1]) {
        order[0] = 3;
        order[1] = 2;
        order[2] = 1;
    } else {
        order[0] = 3;
        order[1] = 1;
        order[2] = 2;
    }
    p = order;
    for (i = 0; i < 3; i++) {
        base = *p;
        if (g_Runners[base].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
            g_Runners[base].tagUpInd == TAG_UP_TYPE_TAGGED && fielderDesperationLevel[base] <= 4 &&
            fielderAIMakePlay(base) != 0) {
            return 1;
        }
        p++;
    }
    return 0;
}

// .text:0x000A25C4 size:0x398 mapped:0x806E1658
BOOL genericPlayOnRunnerOffBase(void) {
    int who;

    do {
        if (originalBaseOfRunnerInThisBaseline[3] >= 0 &&
            fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[3]] <= 5) {
            if ((g_Runners[originalBaseOfRunnerInThisBaseline[3]].percentTowardsNextBase > lbl_3_rodata_19A0 ||
                 (g_Runners[originalBaseOfRunnerInThisBaseline[3]].baseStandingOn == -1 &&
                  g_Ball.baseBallAndFielderAreOn == 3)) &&
                fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[3]) != 0) {
                who = 3;
                break;
            }
            if ((hexMovementsInEachBaseline1for2back4stop[0] & 0x1000) != 0 &&
                g_Runners[originalBaseOfRunnerInThisBaseline[3]].percentTowardsNextBase > lbl_3_rodata_19BC &&
                fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[3]) != 0) {
                who = 3;
                break;
            }
        }
        if (originalBaseOfRunnerInThisBaseline[2] >= 0 &&
            fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[2]] <= 5) {
            if ((g_Runners[originalBaseOfRunnerInThisBaseline[2]].percentTowardsNextBase > lbl_3_rodata_19A0 ||
                 (g_Runners[originalBaseOfRunnerInThisBaseline[2]].baseStandingOn == -1 &&
                  g_Ball.baseBallAndFielderAreOn == 2)) &&
                fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[2]) != 0) {
                who = 2;
                break;
            }
            if ((hexMovementsInEachBaseline1for2back4stop[0] & 0x100) != 0 &&
                g_Runners[originalBaseOfRunnerInThisBaseline[2]].percentTowardsNextBase >= lbl_3_rodata_19BC &&
                fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[2]) != 0) {
                who = 2;
                break;
            }
        }
        if (originalBaseOfRunnerInThisBaseline[1] >= 0 &&
            fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[1]] <= 5) {
            if ((g_Runners[originalBaseOfRunnerInThisBaseline[1]].percentTowardsNextBase > lbl_3_rodata_19A0 ||
                 (g_Runners[originalBaseOfRunnerInThisBaseline[1]].baseStandingOn == -1 &&
                  g_Ball.baseBallAndFielderAreOn == 1)) &&
                fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[1]) != 0) {
                who = 1;
                break;
            }
            if ((hexMovementsInEachBaseline1for2back4stop[0] & 0x10) != 0 &&
                g_Runners[originalBaseOfRunnerInThisBaseline[1]].percentTowardsNextBase > lbl_3_rodata_19BC &&
                fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[1]) != 0) {
                who = 1;
                break;
            }
        }
        return 0;
    } while (0);
    if (g_Ball.ballDistanceFromBase[0] < lbl_3_rodata_199C && g_FieldingLogic.locationThrownTo == 2 &&
        originalBaseOfRunnerInThisBaseline[3] >= 0 && who == 1) {
        if (g_Runners[originalBaseOfRunnerInThisBaseline[who]].fractionalBasesRan <= lbl_3_rodata_19EC) {
            BOOL cutoffReady;

            if (g_FieldingLogic.fielderAssignedLocationIndex[4] == -1) {
                cutoffReady = 0;
            } else if (g_FieldingLogic.playerAtMoundCutoffLocation != 1) {
                cutoffReady = 0;
            } else if (g_Fielders[g_FieldingLogic.fielderAssignedLocationIndex[4]].locationResponsibleForCovering != 5) {
                cutoffReady = 0;
            } else if (g_Fielders[g_Ball.fielderWBallIndex].distanceToMound < lbl_3_rodata_19F0) {
                cutoffReady = 0;
            } else {
                cutoffReady = 1;
            }
            if (cutoffReady) {
                g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
                g_FieldingLogic.locationThrownTo = 5;
            }
        }
    }
    return 1;
}

// .text:0x000A295C size:0x210 mapped:0x806E19F0
BOOL fn_3_A295C(void) {
    InMemRunnerType* runner = &g_Runners[originalBaseOfRunnerInThisBaseline[2]];
    f32 pct = runner->percentTowardsNextBase;
    BOOL inRange;

    if (pct > lbl_3_rodata_19A0 && fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[2]] < 3 &&
        g_Ball.ballZoneAwayFromHome <= 1 && pct <= lbl_3_rodata_19AC &&
        !(pct >= lbl_3_rodata_19AC && runner->runningDirectionCode == 1) && (hexBaserunnerTracker & 1) != 0 &&
        g_Ball.ballAngleFromHome > 0x1C0 && g_Ball.ballAngleFromHome < 0x300 && pct <= lbl_3_rodata_19B4 &&
        fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[0]] <= 3 &&
        fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[0]) != 0) {
        return 1;
    }
    if (g_Ball.ballAngleFromHome >= 0x380 && g_Ball.ballAngleFromHome < 0x640 && g_Ball.ballZoneAwayFromHome <= 1 &&
        g_Ball.AtBat_Contact_BallPos.z > lbl_3_rodata_19B8 + g_Ball.AtBat_Contact_BallPos.x) {
        inRange = 1;
    } else {
        inRange = 0;
    }
    if (inRange && fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[2]] <= 4 &&
        g_Strikes.outs == g_Strikes.storedOuts) {
        if (runner->percentTowardsNextBase > lbl_3_rodata_19A0 &&
            fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[2]) != 0) {
            return 1;
        }
        if ((hexMovementsInEachBaseline1for2back4stop[0] & 0x10) != 0 &&
            runner->percentTowardsNextBase > lbl_3_rodata_19BC &&
            fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[2]) != 0) {
            return 1;
        }
    }
    return 0;
}

// .text:0x000A2B6C size:0x130 mapped:0x806E1C00
BOOL fn_3_A2B6C(void) {
    if (g_Runners[originalBaseOfRunnerInThisBaseline[3]].percentTowardsNextBase >= lbl_3_rodata_19AC) {
        if (fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[3]] <= 3 &&
            fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[3]) != 0) {
            return 1;
        }
        if ((hexMovementsInEachBaseline1for2back4stop[0] & 0x6000) != 0 &&
            fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[3]] <= 4 &&
            g_FieldingLogic.fielderAssignedLocationIndex[3] >= 0 &&
            !(g_Fielders[g_FieldingLogic.fielderAssignedLocationIndex[3]].distanceToBases[3] > lbl_3_rodata_19A4) &&
            !(g_Runners[originalBaseOfRunnerInThisBaseline[3]].percentTowardsNextBase < lbl_3_rodata_19B0 &&
              ((u8*)&lbl_3_bss_17F8[1])[3] == 0) &&
            fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[3]) != 0) {
            return 1;
        }
    }
    return 0;
}

// .text:0x000A2C9C size:0x140 mapped:0x806E1D30
BOOL fn_3_A2C9C(void) {
    if ((hexBaserunnerTracker & 0x100) != 0 && g_Ball.ballDistanceFromBase[3] < lbl_3_rodata_1994 &&
        fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[2]] <= 2 &&
        fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[2]) != 0) {
        return 1;
    }
    if (lbl_3_bss_17F8[8] != 0 && fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[1]) != 0) {
        return 1;
    }
    if (fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[1]] <= 4 && g_Strikes.outs == g_Strikes.storedOuts) {
        if (g_Ball.ballDistanceFromBase[1] < lbl_3_rodata_19A8 &&
            fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[1]] <= 2 &&
            fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[0]) != 0) {
            return 1;
        }
        if (fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[1]) != 0) {
            return 1;
        }
    }
    return 0;
}

// .text:0x000A2DDC size:0x1FC mapped:0x806E1E70
BOOL fn_3_A2DDC(void) {
    if (lbl_3_bss_17F8[8] != 0 && fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[1]) != 0) {
        return 1;
    }
    if (g_Ball.ballDistanceFromBase[0] <= g_Ball.ballDistanceFromBase[2]) {
        if ((hexMovementsInEachBaseline1for2back4stop[0] & 0x1000) != 0 &&
            fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[3]] <= 3 &&
            fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[3]) != 0) {
            return 1;
        }
        if ((hexMovementsInEachBaseline1for2back4stop[0] & 0x6000) != 0 &&
            fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[3]] <= 4) {
            if ((g_FieldingLogic.fielderAssignedLocationIndex[3] < 0 ||
                 g_Fielders[g_FieldingLogic.fielderAssignedLocationIndex[3]].distanceToBases[3] > lbl_3_rodata_19A4) &&
                fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[1]] == 3 &&
                fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[1]) != 0) {
                return 1;
            }
            if (fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[3]) != 0) {
                return 1;
            }
        }
        if (fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[1]] <= 4 &&
            fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[1]) != 0) {
            return 1;
        }
    } else {
        if (fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[1]] <= 4 &&
            fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[1]) != 0) {
            return 1;
        }
        if ((hexMovementsInEachBaseline1for2back4stop[0] & 0x1000) != 0 &&
            fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[3]] <= 3 &&
            fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[3]) != 0) {
            return 1;
        }
    }
    return 0;
}

// .text:0x000A2FD8 size:0x210 mapped:0x806E206C
BOOL fn_3_A2FD8(void) {
    BOOL inRange;
    f32 x = g_Ball.AtBat_Contact_BallPos.x;
    f32 z = g_Ball.AtBat_Contact_BallPos.z;

    if (z < x + lbl_3_rodata_1998 && z < lbl_3_rodata_1998 - x) {
        inRange = 1;
    } else {
        inRange = 0;
    }
    if (inRange) {
        if (urgencyLevel >= 1) {
            if (fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[3]] <= 4 &&
                fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[3]) != 0) {
                return 1;
            }
        } else if (fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[3]] <= 3 &&
                   fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[3]) != 0) {
            return 1;
        }
    }
    if (urgencyLevel <= 1 && g_Ball.ballDistanceFromBase[3] < lbl_3_rodata_1994 &&
        fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[2]] <= 2 &&
        fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[2]) != 0) {
        return 1;
    }
    if (g_Ball.ballDistanceFromBase[0] <= g_Ball.ballDistanceFromBase[2]) {
        if (fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[3]] <= 4 &&
            fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[3]) != 0) {
            return 1;
        }
        if (fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[1]] <= 4 &&
            fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[1]) != 0) {
            return 1;
        }
    } else {
        if (fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[1]] <= 4 &&
            fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[1]) != 0) {
            return 1;
        }
        if (fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[3]] <= 4 &&
            fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[3]) != 0) {
            return 1;
        }
    }
    return 0;
}

// .text:0x000A31E8 size:0xD0 mapped:0x806E227C
BOOL fn_3_A31E8(void) {
    if ((hexBaserunnerTracker & 0x1000) == 0) {
        return 0;
    }
    if ((hexMovementsInEachBaseline1for2back4stop[1] & 0x1000) != 0 &&
        fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[3]) != 0) {
        return 1;
    }
    if ((hexMovementsInEachBaseline1for2back4stop[0] & 0x1000) != 0 &&
        g_Runners[originalBaseOfRunnerInThisBaseline[3]].percentTowardsNextBase >= lbl_3_rodata_19A0 &&
        fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[3]] <= 6 &&
        fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[3]) != 0) {
        return 1;
    }
    return 0;
}

// .text:0x000A32B8 size:0xBC mapped:0x806E234C
BOOL fn_3_A32B8(void) {
    if ((hexBaserunnerTracker & 0x1000) == 0) {
        return 0;
    }
    if ((hexMovementsInEachBaseline1for2back4stop[1] & 0x1000) != 0 &&
        fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[3]) != 0) {
        return 1;
    }
    if ((hexMovementsInEachBaseline1for2back4stop[0] & 0x1000) != 0 &&
        g_Runners[originalBaseOfRunnerInThisBaseline[3]].percentTowardsNextBase >= lbl_3_rodata_19A0 &&
        fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[3]) != 0) {
        return 1;
    }
    return 0;
}

// .text:0x000A3374 size:0x348 mapped:0x806E2408
BOOL fielderAIOutfieldPlayAttemptInd(void) {
    InMemFielder* fielder = &g_Fielders[g_Ball.fielderWBallIndex];

    if ((hexBaserunnerTracker & 0x1000) != 0) {
        if ((hexBaserunnerTracker & 0xFFF) == 0 && g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT &&
            g_Ball.timeSinceBallPickedUp < 30) {
            f32 maxDist = lbl_3_rodata_197C * (f32)fielder->throwingArm + lbl_3_rodata_19F4;

            if (g_Ball.ballDistanceFromBase[0] >= lbl_3_rodata_19F8 && g_Ball.ballDistanceFromBase[0] <= maxDist &&
                g_Runners[3].tagUpInd == TAG_UP_TYPE_NONE) {
                if (g_Runners[3].runningDirectionCode == 1 &&
                    fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[3]) != 0) {
                    return 1;
                }
                return 1;
            }
        }
        if ((hexMovementsInEachBaseline1for2back4stop[0] & 0x1000) != 0) {
            if (urgencyLevel == 3) {
                if (g_Ball.ballDistanceFromBase[0] < lbl_3_rodata_19FC &&
                    fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[3]] <= 7 &&
                    fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[3]) != 0) {
                    return 1;
                }
                return 0;
            } else if (urgencyLevel == 2) {
                if (g_Ball.ballDistanceFromBase[0] < lbl_3_rodata_19FC &&
                    fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[3]] <= 6 &&
                    fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[3]) != 0) {
                    return 1;
                }
                return 0;
            } else if (g_Ball.ballDistanceFromBase[0] < lbl_3_rodata_1A00) {
                if ((hexMovementsInEachBaseline1for2back4stop[0] & 0x110) != 0) {
                    return 0;
                }
                if (fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[3]] <= 4 &&
                    fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[3]) != 0) {
                    return 1;
                }
            }
        }
    }
    if ((hexBaserunnerTracker & 0x100) != 0 && g_Ball.ballDistanceFromBase[3] < lbl_3_rodata_1A04 &&
        (hexMovementsInEachBaseline1for2back4stop[0] & 0x100) != 0) {
        if ((hexBaserunnerTracker & 0x10) == 0) {
            if (fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[2]] <= 5 &&
                fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[2]) != 0) {
                return 1;
            }
        } else if ((hexMovementsInEachBaseline1for2back4stop[0] & 0x60) == 0 &&
                   fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[2]] <= 4 &&
                   fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[2]) != 0) {
            return 1;
        }
    }
    if ((hexBaserunnerTracker & 0x10) != 0 && g_Ball.ballDistanceFromBase[2] < lbl_3_rodata_1A08 &&
        (hexMovementsInEachBaseline1for2back4stop[0] & 0x10) != 0 && (hexBaserunnerTracker & 0x1000) == 0 &&
        fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[1]] <= 5 &&
        fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[1]) != 0) {
        return 1;
    }
    return 0;
}

// .text:0x000A36BC size:0x70 mapped:0x806E2750
BOOL fn_3_A36BC(void) {
    if (g_Ball.AtBat_Contact_BallPos.z < lbl_3_rodata_1A0C && g_Ball.AtBat_Contact_BallPos.z > lbl_3_rodata_1A10 &&
        g_Ball.AtBat_Contact_BallPos.z < lbl_3_rodata_198C + g_Ball.AtBat_Contact_BallPos.x &&
        g_Ball.AtBat_Contact_BallPos.z > g_Ball.AtBat_Contact_BallPos.x - lbl_3_rodata_198C &&
        g_Ball.AtBat_Contact_BallPos.x > g_Runners[0].position.x) {
        return 1;
    }
    return 0;
}

// .text:0x000A372C size:0x3C mapped:0x806E27C0
BOOL fn_3_A372C(void) {
    if (g_Ball.AtBat_Contact_BallPos.z < lbl_3_rodata_1998 + g_Ball.AtBat_Contact_BallPos.x &&
        g_Ball.AtBat_Contact_BallPos.z < lbl_3_rodata_1998 - g_Ball.AtBat_Contact_BallPos.x) {
        return 1;
    }
    return 0;
}

// .text:0x000A3768 size:0x54 mapped:0x806E27FC
BOOL fn_3_A3768(void) {
    if (g_Ball.ballAngleFromHome >= 0x380 && g_Ball.ballAngleFromHome < 0x640 && g_Ball.ballZoneAwayFromHome <= 1 &&
        g_Ball.AtBat_Contact_BallPos.z > lbl_3_rodata_19B8 + g_Ball.AtBat_Contact_BallPos.x) {
        return 1;
    }
    return 0;
}

// .text:0x000A37BC size:0x90 mapped:0x806E2850
BOOL fn_3_A37BC(void) {
    if (g_Ball.ballAngleFromHome < 0x398) {
        return 0;
    }
    if (g_Ball.ballDistanceFromBase[2] < lbl_3_rodata_1994) {
        return 1;
    }
    if (g_Ball.ballAngleFromHome < 0x400) {
        if (g_Ball.AtBat_Contact_BallPos.z + g_Ball.AtBat_Contact_BallPos.x > lbl_3_rodata_1998) {
            return 1;
        }
    } else {
        if (g_Ball.AtBat_Contact_BallPos.z - g_Ball.AtBat_Contact_BallPos.x > lbl_3_rodata_1998) {
            return 1;
        }
    }
    return 0;
}

// .text:0x000A384C size:0x2E4 mapped:0x806E28E0
void fn_3_A384C(void) {
    InMemFielder* fielder;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 speed;
    int frames;

    if ((hexBaserunnerTracker & 0x11) != 0 && fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[1]] <= 4) {
        fielder = &g_Fielders[g_Ball.fielderWBallIndex];
        speed = fielder->modifiedThrowingArm / lbl_3_rodata_1938;
        dx = base_MoundCoordinates[2].x - fielder->pos.x;
        dz = base_MoundCoordinates[2].z - fielder->pos.z;
        dx = dx * dx;
        dz = dz * dz;
        dist = dolsqrtf2(dx + dz);
        if (lbl_3_rodata_193C == speed) {
            speed = lbl_3_rodata_1958;
        }
        if (dist > lbl_3_rodata_195C) {
            frames = lbl_3_rodata_1960 * dist / speed;
        } else if (dist > lbl_3_rodata_1964) {
            frames = dist / speed;
        } else {
            frames = lbl_3_rodata_1968 * dist / speed;
        }
        if (dist > lbl_3_rodata_196C) {
            frames = (int)(frames * lbl_3_rodata_1970) + 0x1e;
        } else if (dist > lbl_3_rodata_1974) {
            frames = (int)(frames * lbl_3_rodata_1960) + 0x1e;
        }
        if (frames + 0x32 < g_Runners[0].framesToNextBase) {
            lbl_3_bss_17F8[8] = 1;
        }
    }
}

// .text:0x000A3B30 size:0xD0 mapped:0x806E2BC4
void fn_3_A3B30(void) {
    int diff = g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total -
               g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total;

    urgencyLevel = 0;
    if (g_Scores.Inning >= g_Scores.inningLimit && g_Scores.halfInning != 0 && diff == 0) {
        urgencyLevel = 3;
        return;
    }
    if (g_Scores.Inning >= g_Scores.inningLimit - 1 && diff <= 1 && diff >= -1) {
        urgencyLevel = 2;
        return;
    }
    if (g_Scores.Inning >= g_Scores.inningLimit - 4 && diff <= 1 && diff >= -3) {
        urgencyLevel = 1;
    }
}

// .text:0x000A3C00 size:0xC0 mapped:0x806E2C94
void fn_3_A3C00(void) {
    int i;

    hexMovementsInEachBaseline1for2back4stop[0] = 0;
    for (i = 0; i < 4; i++) {
        if (originalBaseOfRunnerInThisBaseline[i] >= 0) {
            InMemRunnerType* runner = &g_Runners[originalBaseOfRunnerInThisBaseline[i]];
            if (runner->runningDirectionCode == 1) {
                hexMovementsInEachBaseline1for2back4stop[0] |= 1 << (i * 4);
            } else if (runner->runningDirectionCode == 3) {
                hexMovementsInEachBaseline1for2back4stop[0] |= 2 << (i * 4);
            } else if (runner->runningDirectionCode == 2) {
                hexMovementsInEachBaseline1for2back4stop[0] |= 4 << (i * 4);
            }
        }
    }
}

// .text:0x000A3CC0 size:0x498 mapped:0x806E2D54
void fielderAIChaseRunner(void) {
    int fielderIdx = g_Ball.fielderWBallIndex;
    InMemFielder* fielder = &g_Fielders[fielderIdx];
    int i;

    if (fielder->isResponsibleForCoveringALocation == 1) {
        int loc = fielder->locationResponsibleForCovering;

        if (g_FieldingLogic.somethingForTryingTagOutTargetBase != loc) {
            fielder->locationResponsibleForCovering = -1;
            g_FieldingLogic.fielderAssignedLocationIndex[loc] = -1;
            g_FieldingLogic.baseCoveredInd[loc] = 0;
            fielder->isResponsibleForCoveringALocation = 0;
        }
    }
    g_FieldingLogic._011d = 0;
    if (g_FieldingLogic.somethingForTryingTagOutTargetBase >= 0 && g_FieldingLogic.somethingForTryingTagOutTargetBase <= 3) {
        s16* assignedLocs = g_FieldingLogic.fielderAssignedLocationIndex;
        s16 assigned = assignedLocs[g_FieldingLogic.somethingForTryingTagOutTargetBase];

        if (assigned != fielderIdx) {
            if (fielder->distanceToBases[g_FieldingLogic.somethingForTryingTagOutTargetBase] < lbl_3_rodata_199C) {
                int prev = assigned;

                if (prev >= 0) {
                    ifCurrentFielderIsTakingOverBaseCovering(prev, 9);
                    g_Fielders[prev].locationResponsibleForCovering = -1;
                }
                fielder->locationResponsibleForCovering = g_FieldingLogic.somethingForTryingTagOutTargetBase;
                fielder->isResponsibleForCoveringALocation = 1;
                assignedLocs[fielder->locationResponsibleForCovering] = fielderIdx;
            }
        }
        if (fielder->locationResponsibleForCovering >= 0) {
            if (fielder->distanceFromAutoLocation < thresholdToBeConsideredCoveringBase_ByWeight[fielder->Weight]) {
                g_FieldingLogic.baseCoveredInd[fielder->locationResponsibleForCovering] = 1;
            } else {
                g_FieldingLogic.baseCoveredInd[fielder->locationResponsibleForCovering] = 0;
            }
        }
        g_FieldingLogic._011d = 1;
        for (i = 0; i < 4; i++) {
            InMemRunnerType* runner = &g_Runners[i];

            if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                if (runner->forceOutCd == FORCE_OUT_TYPE_FORCED_TO_ADVANCE && g_FieldingLogic.somethingForTryingTagOutTargetBase == runner->nextBase) {
                    g_FieldingLogic._011d = 2;
                    break;
                }
                if (runner->tagUpInd == TAG_UP_TYPE_TAGGED && g_FieldingLogic.somethingForTryingTagOutTargetBase == i) {
                    g_FieldingLogic._011d = 2;
                    break;
                }
            }
        }
    }
    if (g_FieldingLogic.somethingForTryingTagOutTargetBase == 9) {
        InMemRunnerType* runner = &g_Runners[g_FieldingLogic.runnerChasingAfter];
        int base;

        if (runner->runningDirectionCode == 2) {
            setFielderAutoCoords(g_Ball.fielderWBallIndex, runner->position.x, runner->position.z);
        } else {
            f32 vx = runner->velocity.x * runner->distanceFromBall;
            f32 vz = runner->velocity.y * runner->distanceFromBall;
            setFielderAutoCoords(g_Ball.fielderWBallIndex, lbl_3_rodata_1A14 * vx + runner->position.x,
                                 lbl_3_rodata_1A14 * vz + runner->position.z);
        }
        base = g_Runners[g_FieldingLogic.runnerChasingAfter].baseStandingOn;
        if (base >= 0) {
            if (fielder->distanceToBases[g_FieldingLogic.somethingForTryingTagOutTargetBase] < lbl_3_rodata_199C) {
                s16* assignedLocs = g_FieldingLogic.fielderAssignedLocationIndex;
                int prev = assignedLocs[base];

                if (prev >= 0) {
                    ifCurrentFielderIsTakingOverBaseCovering(prev, 9);
                    g_Fielders[prev].locationResponsibleForCovering = -1;
                }
                fielder->locationResponsibleForCovering = base;
                fielder->isResponsibleForCoveringALocation = 1;
                assignedLocs[fielder->locationResponsibleForCovering] = fielderIdx;
            }
            if (fielder->locationResponsibleForCovering >= 0) {
                if (fielder->distanceFromAutoLocation < thresholdToBeConsideredCoveringBase_ByWeight[fielder->Weight]) {
                    g_FieldingLogic.baseCoveredInd[fielder->locationResponsibleForCovering] = 1;
                    g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
                } else {
                    g_FieldingLogic.baseCoveredInd[fielder->locationResponsibleForCovering] = 0;
                }
            }
            g_FieldingLogic._011d = 1;
        }
    }
    if (fielder->currentVelocity > lbl_3_rodata_1A18) {
        fielder->numFramesToGetToAutoLocation = (s16)(fielder->distanceFromAutoLocation / fielder->currentVelocity);
    }
    setFielderVelocity(g_Ball.fielderWBallIndex);
}

// .text:0x000A4158 size:0x90 mapped:0x806E31EC
void fn_3_A4158(int runnerIndex) {
    InMemRunnerType* runner = &g_Runners[runnerIndex];

    if (runner->runningDirectionCode == 2) {
        setFielderAutoCoords(g_Ball.fielderWBallIndex, runner->position.x, runner->position.z);
    } else {
        f32 vx = runner->velocity.x * runner->distanceFromBall;
        f32 vz = runner->velocity.y * runner->distanceFromBall;
        setFielderAutoCoords(g_Ball.fielderWBallIndex, lbl_3_rodata_1A14 * vx + runner->position.x,
                             lbl_3_rodata_1A14 * vz + runner->position.z);
    }
}

// .text:0x000A41E8 size:0x4B8 mapped:0x806E327C
void fn_3_A41E8(void) {
    return;
}

// .text:0x000A46A0 size:0x370 mapped:0x806E3734
int fielderAIMakePlay(int targetRunner) {
    InMemRunnerType* runner = &g_Runners[targetRunner];
    int fielderWBall = g_Ball.fielderWBallIndex;
    InMemFielder* fielder = &g_Fielders[fielderWBall];
    int strat;
    int returnVar;

    if (targetRunner < 0) {
        g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
        g_FieldingLogic.locationThrownTo = -1;
        return 0;
    }
    if (targetRunner == 0 && runner->currentBase == 0 && fielder->animatingActionInd == 0) {
        BOOL chase = fn_3_A36BC();
        if (chase) {
            g_FieldingLogic.runnerChasingAfter = targetRunner;
            g_FieldingLogic.somethingForTryingTagOutTargetBase = 9;
            g_FieldingLogic.locationThrownTo = -1;
            setFielderAutoCoords(fielderWBall, runner->position.x, runner->position.z);
            return 1;
        }
    }
    strat = runningStratToMakePlay[targetRunner];
    if (strat >= 0) {
        if (fielder->animatingActionInd != 0) {
            g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
            g_FieldingLogic.runnerChasingAfter = -1;
            return 1;
        }
        if (g_FieldingLogic.somethingForTryingTagOutTargetBase != strat) {
            g_FieldingLogic.somethingForTryingTagOutTargetBase = strat;
            if ((s16)strat == 9) {
                if (g_FieldingLogic.throwWaitingInd != 0 &&
                    g_GameLogic.autoFielding[g_GameLogic.awayTeamBattingInd_battingTeam] == 0) {
                    g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
                } else {
                    g_FieldingLogic.runnerChasingAfter = targetRunner;
                }
            }
            if (g_FieldingLogic.somethingForTryingTagOutTargetBase != 9) {
                setFielderAutoCoords(fielderWBall, base_MoundCoordinates[g_FieldingLogic.somethingForTryingTagOutTargetBase].x,
                                     base_MoundCoordinates[g_FieldingLogic.somethingForTryingTagOutTargetBase].z);
            }
        }
        if (g_FieldingLogic.somethingForTryingTagOutTargetBase == 9) {
            if (runner->runningDirectionCode == 2) {
                setFielderAutoCoords(g_Ball.fielderWBallIndex, runner->position.x, runner->position.z);
            } else {
                f32 vx = runner->velocity.x * runner->distanceFromBall;
                f32 vz = runner->velocity.y * runner->distanceFromBall;
                setFielderAutoCoords(g_Ball.fielderWBallIndex, lbl_3_rodata_1A14 * vx + runner->position.x,
                                     lbl_3_rodata_1A14 * vz + runner->position.z);
            }
        }
    } else {
        g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
        g_FieldingLogic.runnerChasingAfter = -1;
    }
    strat = throwStratToMakePlay[targetRunner];
    if (strat >= 10) {
        g_FieldingLogic.locationThrownTo = -1;
        return 1;
    }
    g_FieldingLogic.locationThrownTo = strat;
    g_FieldingLogic.smash0_normalThrow1 = 1;
    if (fielderDesperationLevel[targetRunner] >= 4) {
        int lo = lbl_3_data_1C38[0];
        int hi = lbl_3_data_1C38[1];
        int threshold = lo + (int)((f32)(hi - lo) * g_AiLogic.aIDifficultyMultiplierArray[g_GameLogic.awayTeamBattingInd_battingTeam]);
        int roll = RandomInt_Game(100);
        if (threshold < roll) {
            g_FieldingLogic.smash0_normalThrow1 = 0;
        }
    }
    if (g_FieldingLogic.locationThrownTo == -1 && g_FieldingLogic.somethingForTryingTagOutTargetBase == -1) {
        returnVar = 0;
    } else {
        returnVar = 1;
    }
    return returnVar;
}

// .text:0x000A4A10 size:0x540 mapped:0x806E3AA4
void fieldingAIPlayStrategy(void) {
    return;
}

// .text:0x000A4F50 size:0x48C mapped:0x806E3FE4
void throwTimeToBase(void) {
    return;
}

// .text:0x000A53DC size:0x328 mapped:0x806E4470
void fn_3_A53DC(void) {
    return;
}

// .text:0x000A5704 size:0x448 mapped:0x806E4798
void runnerTimeToCoverBase(void) {
    return;
}

// .text:0x000A5B4C size:0x898 mapped:0x806E4BE0
void fieldingAIThrowOrChase(void) {
    return;
}

// .text:0x000A63E4 size:0x404 mapped:0x806E5478
int howManyFramesTheRunnerIsOutOfReach(int runnerIndex, BOOL forwards, int* throwStrat, int* runStrat) {
    InMemRunnerType* runner = &g_Runners[runnerIndex];
    InMemFielder* fielder = &g_Fielders[g_Ball.fielderWBallIndex];
    int framesToBase;
    int coverFrames;
    int totalFrames;
    f32 speed;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 divisor;
    f32 ballDist;
    int frames;
    int base;
    int runFrames;
    int coveringFielder;

    if (forwards == 0) {
        framesToBase = runner->framesToPreviousBase;
        base = runner->currentBase;
    } else {
        framesToBase = runner->framesToNextBase;
        base = runner->nextBase;
    }
    speed = fielder->modifiedThrowingArm / lbl_3_rodata_1938;
    dx = base_MoundCoordinates[base].x - fielder->pos.x;
    dz = base_MoundCoordinates[base].z - fielder->pos.z;
    coveringFielder = g_FieldingLogic.fielderAssignedLocationIndex[base];
    dx = dx * dx;
    dz = dz * dz;
    dist = dolsqrtf2(dx + dz);
    if (lbl_3_rodata_193C == speed) {
        divisor = lbl_3_rodata_1958;
    } else {
        divisor = speed;
    }
    if (dist > lbl_3_rodata_195C) {
        frames = lbl_3_rodata_1960 * dist / divisor;
    } else if (dist > lbl_3_rodata_1964) {
        frames = dist / divisor;
    } else {
        frames = lbl_3_rodata_1968 * dist / divisor;
    }
    if (dist > lbl_3_rodata_196C) {
        frames = (int)(frames * lbl_3_rodata_1970) + 0x1e;
    } else if (dist > lbl_3_rodata_1974) {
        frames = (int)(frames * lbl_3_rodata_1960) + 0x1e;
    }
    ballDist = g_Ball.ballDistanceFromBase[base];
    totalFrames = fielder->throwWindupEstimate + frames;
    if (ballDist > lbl_3_rodata_195C && ballDist < lbl_3_rodata_1974 && (base == 0 || base == 3)) {
        totalFrames -= 0x2d;
    }
    runFrames = fRunningTimeToDestinationPlus7(g_Ball.fielderWBallIndex);
    if (coveringFielder == g_Ball.fielderWBallIndex || coveringFielder == -1 || ballDist < lbl_3_rodata_199C) {
        *throwStrat = -1;
        *runStrat = base;
        return runFrames - framesToBase;
    }
    coverFrames = g_Fielders[coveringFielder].numFramesToGetToAutoLocation;
    if (runFrames < coverFrames + 5) {
        *throwStrat = -1;
        *runStrat = base;
        return runFrames - framesToBase;
    }
    if (totalFrames < coverFrames) {
        *throwStrat = base + 10;
        *runStrat = -1;
        return g_Fielders[coveringFielder].numFramesToGetToAutoLocation - framesToBase;
    }
    *throwStrat = base;
    *runStrat = -1;
    return totalFrames - framesToBase;
}

// .text:0x000A67E8 size:0x28 mapped:0x806E587C
void fn_3_A67E8(int i) {
    runningStratToMakePlay[i] = 9;
    throwStratToMakePlay[i] = -1;
}

// .text:0x000A6810 size:0x2AC mapped:0x806E58A4
int estimatedThrowFramesBetweenTwoPoints(f32 ax, f32 az, f32 bx, f32 bz) {
    f32 speed;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 divisor;
    int frames;

    dx = bx - ax;
    dz = bz - az;
    speed = throwSpeedArray[10] / lbl_3_rodata_1A2C;
    dx = dx * dx;
    dz = dz * dz;
    dist = dolsqrtf2(dx + dz);
    if (lbl_3_rodata_193C == speed) {
        divisor = lbl_3_rodata_1958;
    } else {
        divisor = speed;
    }
    frames = dist / divisor;
    if (dist > lbl_3_rodata_196C) {
        frames = (int)(frames * lbl_3_rodata_1A30) + 0x1e;
    } else if (dist > lbl_3_rodata_1974) {
        frames = (int)(frames * lbl_3_rodata_1970) + 0x1e;
    } else if (dist > lbl_3_rodata_195C) {
        frames = (int)(frames * lbl_3_rodata_19EC) + 0x1e;
    } else if (dist > lbl_3_rodata_1A08) {
        frames = (int)(frames * lbl_3_rodata_1A34);
    }
    return frames;
}

// .text:0x000A6ABC size:0x28C mapped:0x806E5B50
int fn_3_A6ABC(f32 x, f32 z) {
    InMemFielder* fielder = &g_Fielders[g_Ball.fielderWBallIndex];
    f32 dx = x - fielder->pos.x;
    f32 dz = z - fielder->pos.z;
    f32 speed;
    f32 divisor;
    f32 dist;
    int frames;

    speed = fielder->modifiedThrowingArm / lbl_3_rodata_1938;
    dx = dx * dx;
    dz = dz * dz;
    dist = dolsqrtf2(dx + dz);
    if (lbl_3_rodata_193C == speed) {
        divisor = lbl_3_rodata_1958;
    } else {
        divisor = speed;
    }
    if (dist > lbl_3_rodata_195C) {
        frames = lbl_3_rodata_1960 * dist / divisor;
    } else if (dist > lbl_3_rodata_1964) {
        frames = dist / divisor;
    } else {
        frames = lbl_3_rodata_1968 * dist / divisor;
    }
    if (dist > lbl_3_rodata_196C) {
        frames = (int)(frames * lbl_3_rodata_1970) + 0x1e;
    } else if (dist > lbl_3_rodata_1974) {
        frames = (int)(frames * lbl_3_rodata_1960) + 0x1e;
    }
    return frames;
}

// .text:0x000A6D48 size:0x150 mapped:0x806E5DDC
void fn_3_A6D48(void) {
    InMemRunnerType* runner;
    int i;

    hexBaserunnerTracker = 0;
    for (i = 0; i < 4; i++) {
        originalBaseOfRunnerInThisBaseline[i] = -1;
    }
    runner = &g_Runners[3];
    for (i = 3; i >= 0; i--) {
        if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
            hexBaserunnerTracker |= 1 << ((int)runner->fractionalBasesRan * 4);
            if (originalBaseOfRunnerInThisBaseline[runner->currentBase] < 0 ||
                g_Runners[originalBaseOfRunnerInThisBaseline[runner->currentBase]].baseStandingOn >= 0) {
                originalBaseOfRunnerInThisBaseline[runner->currentBase] = i;
            }
        }
        runner--;
    }
}

// .text:0x000A6E98 size:0x1A8 mapped:0x806E5F2C
void tagRelated(void) {
    return;
}

// .text:0x000A7040 size:0x674 mapped:0x806E60D4
void tagOutValues(void) {
    return;
}

// .text:0x000A76B4 size:0x5D4 mapped:0x806E6748
void fielderHasBall(void) {
    return;
}

// .text:0x000A7C88 size:0x270 mapped:0x806E6D1C
void checkForBufferedThrow(void) {
    InputStruct* input = &g_Controls[g_GameLogic.teams[g_GameLogic.teamFielding]];

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        return;
    }
    if (g_GameLogic.autoFielding[g_GameLogic.awayTeamBattingInd_battingTeam] != 0) {
        return;
    }
    if (ACTIVE_TUTORIAL()) {
        input = &g_Practice.inputs[g_GameLogic.teamFielding];
    } else if (g_d_GameSettings.minigamesEnabled) {
        input = &g_Controls[g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame._1922]];
    }
    if (!(input->buttonInput & INPUT_BUTTON_A)) {
        g_FieldingLogic.smashThrow_framesDirectionHeld = 0;
    }
    if (g_FieldingLogic.smashThrow_framesDirectionHeld != 0) {
        if (g_FieldingLogic.smashThrow_framesDirectionHeld < 0xfe) {
            g_FieldingLogic.smashThrow_framesDirectionHeld++;
        } else {
            g_FieldingLogic.smashThrow_framesDirectionHeld = 0xff;
        }
    }
    if (!(input->buttonInput & INPUT_BUTTON_A)) {
        return;
    }
    if (input->newButtonInput & INPUT_BUTTON_A) {
        if (input->buttonInput & INPUT_TRIGGER_L) {
            g_FieldingLogic.humanSelectedPlaceToThrow = 6;
        } else if (input->controlStickAngle >= 0xe00) {
            g_FieldingLogic.humanSelectedPlaceToThrow = 1;
        } else if (input->controlStickAngle >= 0xa00) {
            g_FieldingLogic.humanSelectedPlaceToThrow = 0;
        } else if (input->controlStickAngle >= 0x600) {
            g_FieldingLogic.humanSelectedPlaceToThrow = 3;
        } else if (input->controlStickAngle >= 0x200) {
            g_FieldingLogic.humanSelectedPlaceToThrow = 2;
        } else if (input->controlStickAngle >= 0) {
            g_FieldingLogic.humanSelectedPlaceToThrow = 1;
        } else {
            g_FieldingLogic.smashThrow_framesDirectionHeld = 1;
        }
    } else if (g_FieldingLogic.smashThrow_framesDirectionHeld >= specialFielderActionConstants._40[8]) {
        if (g_FieldingLogic.interceptThrowFielder >= 0) {
            return;
        }
        g_FieldingLogic.humanSelectedPlaceToThrow = 8;
    }
    g_FieldingLogic.someHumanThrowFrameCounter = 0;
    if (g_FieldingLogic.humanSelectedPlaceToThrow == 8) {
        g_FieldingLogic.smash0_normalThrow1 = 1;
        return;
    }
    if (g_FieldingLogic.framesControlStickPointedInCertainQuadrant <= lbl_3_data_475C && !g_d_GameSettings.minigamesEnabled) {
        g_FieldingLogic.smash0_normalThrow1 = 0;
        return;
    }
    g_FieldingLogic.smash0_normalThrow1 = 1;
}

// .text:0x000A7EF8 size:0x17C mapped:0x806E6F8C
void fielderControl_classifyControlStickDirection(void) {
    InputStruct* input;
    u8 priorClassification;

    input = &g_Controls[g_GameLogic.teams[g_GameLogic.teamFielding]];
    if (ACTIVE_TUTORIAL()) {
        input = &g_Practice.inputs[g_GameLogic.teamFielding];
    } else if (g_d_GameSettings.minigamesEnabled) {
        input = &g_Controls[g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame._1922]];
    }
    priorClassification = g_FieldingLogic.stickAngleClassification;
    if (input->controlStickAngle >= 0xe00) {
        g_FieldingLogic.stickAngleClassification = 2;
    } else if (input->controlStickAngle >= 0xa00) {
        g_FieldingLogic.stickAngleClassification = 3;
    } else if (input->controlStickAngle >= 0x600) {
        g_FieldingLogic.stickAngleClassification = 4;
    } else if (input->controlStickAngle >= 0x200) {
        g_FieldingLogic.stickAngleClassification = 1;
    } else if (input->controlStickAngle >= 0) {
        g_FieldingLogic.stickAngleClassification = 2;
    } else {
        g_FieldingLogic.stickAngleClassification = 0;
    }
    if (g_FieldingLogic.stickAngleClassification == 0) {
        g_FieldingLogic.framesControlStickPointedInCertainQuadrant = 0;
        return;
    }
    if (g_FieldingLogic.stickAngleClassification == priorClassification) {
        if (g_FieldingLogic.framesControlStickPointedInCertainQuadrant < 0xfe) {
            g_FieldingLogic.framesControlStickPointedInCertainQuadrant++;
        } else {
            g_FieldingLogic.framesControlStickPointedInCertainQuadrant = 0xff;
        }
    } else {
        g_FieldingLogic.framesControlStickPointedInCertainQuadrant = 1;
    }
}

// .text:0x000A8074 size:0x2C4 mapped:0x806E7108
void setRunnerChasingAfter(int fielderIndex) {
    int base = -1;
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    s16 fromBase = g_FieldingLogic.fielderAssignedLocationIndex[6];
    int diff;
    s16 toBase;
    BOOL forwards = FALSE;
    int result = -1;

    if (fromBase < 0) {
        g_FieldingLogic.runnerChasingAfter = -1;
        return;
    }
    toBase = g_FieldingLogic.somethingForTryingTagOutTargetBase;
    diff = toBase - fromBase;
    if (diff == 1 || diff == -3) {
        base = fromBase;
    } else if (diff == -1 || diff == 3) {
        base = toBase;
    }
    if (base >= 0) {
        if (toBase > fromBase || (toBase == 0 && fromBase == 3)) {
            forwards = TRUE;
        }
        if (forwards) {
            InMemRunnerType* runner = &g_Runners[0];
            if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD && base == runner->currentBase && runner->baseStandingOn < 0 &&
                fielder->distanceToBases[toBase] > runner->distToNextBase) {
                result = 0;
            } else {
                runner++;
                if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD && base == runner->currentBase && runner->baseStandingOn < 0 &&
                    fielder->distanceToBases[toBase] > runner->distToNextBase) {
                    result = 1;
                } else {
                    runner++;
                    if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD && base == runner->currentBase && runner->baseStandingOn < 0 &&
                        fielder->distanceToBases[toBase] > runner->distToNextBase) {
                        result = 2;
                    } else {
                        runner++;
                        if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD && base == runner->currentBase &&
                            runner->baseStandingOn < 0 && fielder->distanceToBases[toBase] > runner->distToNextBase) {
                            result = 3;
                        }
                    }
                }
            }
        } else {
            InMemRunnerType* runner = &g_Runners[3];
            if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD && base == runner->currentBase && runner->baseStandingOn < 0 &&
                fielder->distanceToBases[toBase] > runner->distToCurrentBase) {
                result = 3;
            } else {
                runner--;
                if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD && base == runner->currentBase && runner->baseStandingOn < 0 &&
                    fielder->distanceToBases[toBase] > runner->distToCurrentBase) {
                    result = 2;
                } else {
                    runner--;
                    if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD && base == runner->currentBase && runner->baseStandingOn < 0 &&
                        fielder->distanceToBases[toBase] > runner->distToCurrentBase) {
                        result = 1;
                    } else {
                        runner--;
                        if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD && base == runner->currentBase &&
                            runner->baseStandingOn < 0 && fielder->distanceToBases[toBase] > runner->distToCurrentBase) {
                            result = 0;
                        }
                    }
                }
            }
        }
    }
    g_FieldingLogic.runnerChasingAfter = result;
}

// .text:0x000A8338 size:0x140 mapped:0x806E73CC
void fielderChasingAI(void) {
    return;
}

// .text:0x000A8478 size:0x150 mapped:0x806E750C
void runnerTagUpOrBatterTo1B(void) {
    return;
}

// .text:0x000A85C8 size:0x40C mapped:0x806E765C
void maybeUnused_SetThrowSpeedType2(void) {
    return;
}

// .text:0x000A89D4 size:0x980 mapped:0x806E7A68
void fn_3_A89D4(void) {
    return;
}

// .text:0x000A9354 size:0x3A8 mapped:0x806E83E8
void knockBallLoose(int fielderIndex, int knockOutCause) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    VecSrcDst inVec;
    CollisionStruct outCollision;
    f32 dirX;
    f32 dirZ;
    int angle;
    u32 collisionType;
    f32 groundVelocity;

    if (g_Ball.fielderWBallIndex == fielderIndex) {
        g_Ball.AtBat_Contact_BallPos.x = fielder->pos.x + g_Ball.offsetWhilePickedUpHistory[0].x;
        g_Ball.AtBat_Contact_BallPos.y = fielder->pos.y + g_Ball.offsetWhilePickedUpHistory[0].y;
        g_Ball.AtBat_Contact_BallPos.z = fielder->pos.z + g_Ball.offsetWhilePickedUpHistory[0].z;
        inVec.src.x = g_Ball.AtBat_Contact_BallPos.x;
        inVec.src.y = lbl_3_rodata_1978;
        inVec.src.z = g_Ball.AtBat_Contact_BallPos.z;
        inVec.dst.x = g_Ball.AtBat_Contact_BallPos.x;
        inVec.dst.y = lbl_3_rodata_1994;
        inVec.dst.z = g_Ball.AtBat_Contact_BallPos.z;
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
            collisionType = checkCollision(&inVec, &outCollision, 2, FALSE);
        } else {
            collisionType = checkCollision(&inVec, &outCollision, 1, FALSE);
        }
        collisionType &= 0x7f;
        if (collisionType != BALL_COLLISION_TYPE_GRASS && collisionType != BALL_COLLISION_TYPE_DIRT &&
            collisionType - BALL_COLLISION_TYPE_ROUGH_TERRAIN > 1) {
            g_Ball.AtBat_Contact_BallPos.x = fielder->pos.x;
            g_Ball.AtBat_Contact_BallPos.y = fielder->pos.y;
            g_Ball.AtBat_Contact_BallPos.z = fielder->pos.z;
            g_Ball.AtBat_Contact_BallPos.y = g_Ball.offsetWhilePickedUpHistory[0].y;
        }
        if (g_Ball.AtBat_Contact_BallPos.y < lbl_3_rodata_19B0) {
            g_Ball.AtBat_Contact_BallPos.y = lbl_3_rodata_19B0;
        }
        if (knockOutCause == 0) {
            angle = RandomInt_Game_Range(bodyCheckBallAngles[fielder->bodyCheckBase].ballAngleLower,
                                         bodyCheckBallAngles[fielder->bodyCheckBase].ballAngleUpper);
        } else if (knockOutCause == 1) {
            angle = fielder->knockOutAngle;
        } else {
            angle = normalizeAngle(g_Ball.ballAngleFromHome + 0x800);
        }
        getComponentsFromSAng(angle, &dirX, &dirZ);
        g_Ball.physicsSubstruct.velocity.y = lbl_3_rodata_1A50 * (f32)RandomInt_Game(300) + lbl_3_rodata_1A4C;
        groundVelocity = lbl_3_rodata_1A50 * (f32)RandomInt_Game(200) + lbl_3_rodata_1A54;
        g_Ball.physicsSubstruct.velocity.x = dirX * groundVelocity;
        g_Ball.physicsSubstruct.velocity.z = dirZ * groundVelocity;
        g_Ball.framesSinceThrowStarted = 0;
        g_Ball.ballState = BALL_STATE_LOOSE;
        g_Ball.fielderWBallIndex = -1;
        g_Ball.baseBallAndFielderAreOn = -1;
        g_Ball.ballIsLooseInd_unused = 0;
        g_Ball.fielderAboutToGetBall_hasBall = -1;
        g_Ball.thrownBallHasHitGround = 0;
        g_Ball.matchFramesAndBallAngle.framesSinceLastThrow = g_Ball.timeSinceBallPickedUp;
        g_Ball.timeSinceBallPickedUp = -1;
        g_Ball.ballIsRollingIndicator = 0;
        g_Ball.groundRuleDoubleInd = 0;
        g_FieldingLogic.tagAnimationCountdown = 0;
        g_FieldingLogic.baseFielderIsOn = -1;
        g_FieldingLogic.someCountDown = 0;
        {
            InMemRunnerType* runner = &g_Runners[0];
            int i;
            for (i = 0; i < 4; i++, runner++) {
                if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                    if (runner->tagUpInd == TAG_UP_TYPE_TAGGED) {
                        runner->baseReachedAtTimeOfThrow = runner->startingBase_baseAchieved;
                    } else {
                        runner->baseReachedAtTimeOfThrow = runner->currentBase;
                    }
                } else {
                    runner->baseReachedAtTimeOfThrow = -1;
                }
            }
        }
    }
}

// .text:0x000A96FC size:0x288 mapped:0x806E8790
void fielderBodyCheck_setStatus_Pos_Velo(int fielderIndex) {
    return;
}

// .text:0x000A9984 size:0x2F0 mapped:0x806E8A18
void fielderKnockback(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    VecXYZ knock;
    f32 ratio;
    f32 vx;
    f32 vz;

    if (fielder->timeSinceThrowWasCaught == 0) {
        if (fielder->hitKnockbackCountdown <= 1) {
            fielder->_0200 = 0;
            return;
        }
        knock.x = g_Ball.pastCoordinates[2].x - g_Ball.pastCoordinates[3].x;
        knock.z = g_Ball.pastCoordinates[2].z - g_Ball.pastCoordinates[3].z;
        fielder->knockBackRelatedVeloX = lbl_3_rodata_1990 * knock.x;
        knock.y = g_Ball.pastCoordinates[2].y - g_Ball.pastCoordinates[3].y;
        fielder->knockbackRelatedVeloZ = lbl_3_rodata_1990 * knock.z;
        fielder->_0200 = 1;
        if (g_d_GameSettings.minigamesEnabled) {
            fn_8004AFA8(fielder->_020D);
        } else {
            fn_8004AFA8(fielderIndex);
        }
    } else {
        ratio = (f32)(fielder->hitKnockbackCountdown - 1) / (f32)fielder->hitKnockbackCountdown;
        fielder->knockBackRelatedVeloX = fielder->knockBackRelatedVeloX * ratio;
        fielder->knockbackRelatedVeloZ = fielder->knockbackRelatedVeloZ * ratio;
        if (fielder->hitKnockbackCountdown <= 1) {
            fielder->_0200 = 0;
        }
        if (fielder->timeSinceThrowWasCaught > 0) {
            if (g_d_GameSettings.minigamesEnabled) {
                fn_8004AE18(fielder->_020D);
            } else {
                fn_8004AE18(fielderIndex);
            }
        }
    }
    fielder->velocityX = fielder->knockBackRelatedVeloX;
    fielder->velocityZ = fielder->knockbackRelatedVeloZ;
    vx = fielder->velocityX;
    vz = fielder->velocityZ;
    vx = vx * vx;
    vz = vz * vz;
    fielder->currentVelocity = dolsqrtf2(vz + vx);
    if (updateFielderPosition_checkFielderCollision(fielderIndex, &knock) != 0) {
        fielder->knockBackRelatedVeloX = lbl_3_rodata_193C;
        fielder->knockbackRelatedVeloZ = lbl_3_rodata_193C;
        fielder->velocityX = lbl_3_rodata_193C;
        fielder->velocityZ = lbl_3_rodata_193C;
        fielder->currentVelocity = lbl_3_rodata_193C;
    } else {
        fielder->pos.x += fielder->velocityX;
        fielder->pos.z += fielder->velocityZ;
    }
}

// .text:0x000A9C74 size:0xAC mapped:0x806E8D08
void setFielder215(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    BOOL quickThrow = checkFieldingStat(g_GameLogic.teamFielding, fielder->rosterLocation, FIELDING_ABILITY_QUICK_THROW);

    if (fielder->outFieldZoneCode >= 3) {
        fielder->throwWindUpFrames = throwWindUpFrames[quickThrow * 3 + 1];
    } else {
        fielder->throwWindUpFrames = throwWindUpFrames[quickThrow * 3];
    }
    if (quickThrow != 0 && g_FieldingLogic.locationThrownTo >= 0) {
        playSoundEffect(0x1A8);
    }
}

// .text:0x000A9D20 size:0xD1C mapped:0x806E8DB4
void autoMovement10_HasBall(void) {
    return;
}

// .text:0x000AAA3C size:0x1BC mapped:0x806E9AD0
void fn_3_AAA3C(int fielderIdx) {
    InMemFielder* fielder = &g_Fielders[fielderIdx];

    if (g_FieldingLogic.xcc_Stored_0 >= 0 && g_FieldingLogic.locationThrownTo >= 0 &&
        g_FieldingLogic.locationThrownTo <= 3 &&
        (!(fielder->distanceToBases[g_FieldingLogic.locationThrownTo] > lbl_3_rodata_19F0) ||
         g_FieldingLogic.fielderAssignedLocationIndex[6] >= 0)) {
        if (g_FieldingLogic.locationThrownTo == g_FieldingLogic.xcc_Stored_0 &&
            g_FieldingLogic.runnerChasingAfter_stored >= 0 && g_FieldingLogic.runnerChasingAfter_stored <= 3 &&
            (g_FieldingLogic.fielderAssignedLocationIndex[6] ==
                 g_Runners[g_FieldingLogic.runnerChasingAfter_stored].nextBase ||
             g_FieldingLogic.fielderAssignedLocationIndex[6] ==
                 g_Runners[g_FieldingLogic.runnerChasingAfter_stored].currentBase)) {
            g_FieldingLogic.setThrowSpeedTypeTo9Ind = 1;
        }
        if (g_FieldingLogic.xcc_Stored_0 == 9 && g_FieldingLogic.runnerChasingAfter_stored >= 0 &&
            g_FieldingLogic.runnerChasingAfter_stored <= 3 &&
            g_Runners[g_FieldingLogic.runnerChasingAfter_stored].runnerOnFieldOrOutOrScored ==
                RUNNER_STATUS_ON_FIELD &&
            g_FieldingLogic.locationThrownTo ==
                g_Runners[g_FieldingLogic.runnerChasingAfter_stored].baseRunningTowards) {
            g_FieldingLogic.setThrowSpeedTypeTo9Ind = 1;
        }
        if (g_FieldingLogic.setThrowSpeedTypeTo9Ind != 0 && g_FieldingLogic.locationThrownTo >= 0 &&
            g_FieldingLogic.locationThrownTo <= 3) {
            f32 dx = base_MoundCoordinates[g_FieldingLogic.locationThrownTo].x - fielder->pos.x;
            f32 dz = base_MoundCoordinates[g_FieldingLogic.locationThrownTo].z - fielder->pos.z;
            if (calculateDiffInAngles(game_atan2(dx, dz), fielder->desiredMovementDirection) > 0x40) {
                g_FieldingLogic.setThrowSpeedTypeTo9Ind = 0;
            }
        }
    }
}

// .text:0x000AABF8 size:0x8C mapped:0x806E9C8C
BOOL fn_3_AABF8(void) {
    int fielderIdx = g_FieldingLogic.fielderAssignedLocationIndex[4];

    if (fielderIdx == -1) {
        return 0;
    }
    if (g_FieldingLogic.playerAtMoundCutoffLocation != 1) {
        return 0;
    }
    if (g_Fielders[fielderIdx].locationResponsibleForCovering != 5) {
        return 0;
    }
    return !(g_Fielders[g_Ball.fielderWBallIndex].distanceToMound < lbl_3_rodata_19F0);
}

// .text:0x000AAC84 size:0x36C mapped:0x806E9D18
void fn_3_AAC84(void) {
    return;
}

// .text:0x000AAFF0 size:0x564 mapped:0x806EA084
void setCutoffThrowTargetLocation(void) {
    return;
}

// .text:0x000AB554 size:0x5C mapped:0x806EA5E8
void fn_3_AB554(void) {
    if (g_FieldingLogic._010d == 0) {
        return;
    }
    if (g_Ball.timeSinceBallPickedUp >= 0 && g_Ball.timeSinceBallPickedUp < 40) {
        if (g_FieldingLogic.locationThrownTo < 0) {
            return;
        }
        g_FieldingLogic._010c = 1;
        g_FieldingLogic._010d = 0;
        return;
    }
    g_FieldingLogic._010d = 0;
}

// .text:0x000AB5B0 size:0x820 mapped:0x806EA644
void initializeThrowAngle_Speed_Length(void) {
    return;
}

// .text:0x000ABDD0 size:0xC28 mapped:0x806EAE64
void makeThrowVariables(void) {
    return;
}

