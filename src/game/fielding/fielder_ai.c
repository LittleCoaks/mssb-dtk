#include "game/fielding/fielder_ai.h"
#include "game/fielding/fielder.h"
#include "game/ball/collision_primitives.h"
#include "game/UnknownHomes_Game.h"
#include "game/math/game_math.h"
#include "stl/math.h"
#include "header_rep_data.h"
#include "static/UnknownHomes_static.h"
#include "game/sound/m_sound.h"
#include "Unknown/File_0x80024b00.h"

extern const f32 lbl_3_rodata_1938;
extern const f32 lbl_3_rodata_19C4;
extern const f32 lbl_3_rodata_19C8;
extern u8 lbl_3_data_4710[2];
extern const f32 lbl_3_rodata_1A1C;
extern const f32 lbl_3_rodata_1A20;
extern const f32 lbl_3_rodata_1A24;
extern const f32 lbl_3_rodata_1A28;
extern const f32 lbl_3_rodata_1A38;
extern const f32 lbl_3_rodata_1A3C;
extern const f32 lbl_3_rodata_1A5C;
extern const f32 lbl_3_rodata_1A60;
extern const f32 lbl_3_rodata_1A64;
extern const f32 lbl_3_rodata_1A68;
extern const f32 lbl_3_rodata_1A6C;
extern const f32 lbl_3_rodata_1A70;
extern const f32 lbl_3_rodata_1A74;
extern const f32 lbl_3_rodata_1A78;
extern f32 lbl_3_data_4760[3];
extern u8 hugeAnimStruct[0x3154];
extern void fieldingRelatedAnimations(void* anim, int state);
extern const f32 lbl_3_rodata_1A58;
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
extern const f32 lbl_3_rodata_19E0;
extern const f32 lbl_3_rodata_19E4;
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
extern const f32 lbl_3_rodata_1A40;
extern const f32 lbl_3_rodata_1A44;
extern const f32 lbl_3_rodata_1A48;
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
extern s16 lbl_3_data_1C40;
extern u8 lbl_3_data_475C;
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
extern u8 bodyCheckFrameRelatedConstants[54][4];
extern f32 lbl_3_data_4878[2];
extern s16 lbl_3_data_4880;
void fn_8004AFA8(int index);
void fn_8004AE18(int index);
extern const u8 throwWindUpFrames[];
extern VecXZ base_MoundCoordinates[5];
void ifCurrentFielderIsTakingOverBaseCovering(int fielderIndex, int newLocation);
extern f32 thresholdToBeConsideredCoveringBase_ByWeight[5];
extern u8 lbl_3_data_4908[2];
extern int calculateChemistry(int teamFielding, s16 charIdA, s16 charIdB);
extern s16 chemThresholds[4];
extern s16 lbl_3_common_bss_37400[0x27];
extern u8 getThrowSpeedBasedOnArmStrengthStat(u8 arm);
extern void starMissionsQuantityBased(int missionType, int rosterLocation);
extern void liveBallHitPhysics(int arg);
extern void pickoff_infieldThrow_related(int fielderIndex);
extern void playCharacterSound(int charID, int soundIndex);
extern void initialize_runnersBeingTargetedWhileBatterCanBeForcedOut(void);

static s32 fielderDesperationLevel[42];
static s32 framesRunnerIsOutOfReach[4];
static s32 runningStratToMakePlay[4];
static s32 throwStratToMakePlay[4];
static s32 hexBaserunnerTracker;
static s32 numRunnersOnField;
static s32 urgencyLevel;
static s32 enoughTimeToGetLeadRunnerAt2B;
static s32 originalBaseOfRunnerInThisBaseline[4];
static u32 runnersInStartingBaselineBits;
static u32 hexMovementsInEachBaseline1for2back4stop;
static u8 indBallNearBaselineWhereRunnerIs[4];
static s32 lbl_3_bss_17F8[1];

static inline BOOL fn_3_A295C_inline(void) {
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
        if ((hexMovementsInEachBaseline1for2back4stop & 0x10) != 0 &&
            runner->percentTowardsNextBase > lbl_3_rodata_19BC &&
            fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[2]) != 0) {
            return 1;
        }
    }
    return 0;
}

static inline BOOL fn_3_A2FD8_inline(void) {
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

// .text:0x000A009C size:0x1C68 mapped:0x806DF130
void fielderAIDecideWhatRunnerToTarget(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    BOOL highSkillLowDesperation = 0;
    int focusRunner;
    int i;
    s16 throwLoc;

    if (g_FieldingLogic.throwWaitingInd != 0) {
        if (g_RunningLogic._10 == 0) {
            if (g_Ball.ballZoneAwayFromHome < 2) {
                return;
            }
            g_FieldingLogic.locationThrownTo = 6;
        }
    } else {
        int limit = lbl_3_data_4710[0] + (int)((f32)(lbl_3_data_4710[1] - lbl_3_data_4710[0]) *
                                               g_AiLogic.aIDifficultyMultiplierArray[g_GameLogic.awayTeamBattingInd_battingTeam]);

        if (g_Ball.numberOfThrowsDuringPlay <= 1 && g_Ball.timeSinceBallPickedUp < limit &&
            g_Ball.numberOfThrowsDuringPlay <= 1 &&
            (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != 2 || fielderIndex != 1 || g_Ball.framesSinceHit >= 200)) {
            g_FieldingLogic.locationThrownTo = -1;
            g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
            return;
        }
        if (g_FieldingLogic.bodyCheckResult != 0) {
            return;
        }
        if (g_Strikes.outs >= 3 || g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_FOUL || g_Ball.deadBallReason != 0) {
            g_FieldingLogic.locationThrownTo = -1;
            g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
            return;
        }
        if (g_RunningLogic._10 == 0 && g_Ball.timeSinceBallPickedUp < 60) {
            g_FieldingLogic.locationThrownTo = -1;
            g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
            return;
        }
    }

    numRunnersOnField = 0;
    runnersInStartingBaselineBits = 0;
    enoughTimeToGetLeadRunnerAt2B = 0;
    for (i = 0; i < 4; i++) {
        if (g_Runners[i].forceOutCd == FORCE_OUT_TYPE_FORCED_TO_ADVANCE) {
            runnersInStartingBaselineBits |= 1 << (i * 4);
        }
        if (g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
            numRunnersOnField++;
        }
    }
    if (g_FieldingLogic._010d != 0) {
        fielder->throwWindupEstimate = 45;
    }
    fn_3_A3B30();
    fieldingAIPlayStrategy();
    fn_3_A3C00();
    fn_3_A384C();
    focusRunner = fn_3_A1D04();

    if ((g_Ball.ballZoneAwayFromHome == 4 || (g_Ball.ballZoneAwayFromHome == 3 && fielderIndex >= 6)) &&
        g_FieldingLogic.cutoffFielderIndex >= 0 && g_FieldingLogic.cutoffFielderIndex != fielderIndex) {
        if (canThrowOutRunnerWhoNeedsToTagUp() == 0 && fielderAIOutfieldPlayAttemptInd() == 0) {
            if (!fn_3_A1DA0()) {
                g_FieldingLogic.locationThrownTo = 6;
                g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
                g_FieldingLogic.runnerChasingAfter = -1;
            }
        }
    } else {
        do {
            if (g_Strikes.outs == 2) {
                if (g_Runners[1].forceOutCd == FORCE_OUT_TYPE_FORCED_TO_ADVANCE && fielderDesperationLevel[1] <= 2) {
                    if (fielder->AILevel3Weak0Powerful <= 1 && fielderDesperationLevel[1] <= 0) {
                        highSkillLowDesperation = 1;
                    }
                    if (fn_3_A37BC() && fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[1]) != 0) {
                        break;
                    }
                }
                if ((hexBaserunnerTracker & 1) != 0 && fielderDesperationLevel[0] <= 6) {
                    if (fielderDesperationLevel[0] >= 4) {
                        int n = 1;
                        InMemRunnerType* runner = &g_Runners[1];
                        s32* base = &originalBaseOfRunnerInThisBaseline[1];

                        do {
                            if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
                                (runner->runningDirectionCode == 1 || runner->runningDirectionCode == 2) &&
                                n == runner->currentBase &&
                                fielder->distanceToBases[runner->nextBase] < lbl_3_rodata_199C &&
                                fielderDesperationLevel[*base] <= 3 && runner->distanceFromBall < lbl_3_rodata_1994 &&
                                fielderAIMakePlay(*base) != 0) {
                                goto checkOverrideReasons;
                            }
                            n++;
                            runner++;
                            base++;
                        } while (n <= 3);
                    }
                    if (fielder->AILevel3Weak0Powerful <= 1 && fielderDesperationLevel[0] <= 0) {
                        highSkillLowDesperation = 1;
                    }
                    fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[0]);
                    break;
                }
            }
            if (hexBaserunnerTracker == 1) {
                if (fielder->AILevel3Weak0Powerful <= 1 && fielderDesperationLevel[0] <= 0) {
                    highSkillLowDesperation = 1;
                }
                if (fielderDesperationLevel[0] <= 6 && fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[0]) != 0) {
                    break;
                }
            }
            if (urgencyLevel == 3 && fn_3_A32B8()) {
                break;
            }
            if (urgencyLevel == 2 && fn_3_A31E8()) {
                break;
            }
            if ((hexBaserunnerTracker == 0x1000 && fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[3]] <= 6 &&
                 fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[3]) != 0) ||
                (hexBaserunnerTracker == 0x100 && fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[2]] <= 6 &&
                 fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[2]) != 0) ||
                (hexBaserunnerTracker == 0x10 && fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[1]] <= 5 &&
                 g_Runners[originalBaseOfRunnerInThisBaseline[1]].overrunBaseStage == 0 &&
                 fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[1]) != 0)) {
                break;
            }
            if (hexBaserunnerTracker == 0x1111 && fn_3_A2FD8_inline()) {
                break;
            }
            if (hexBaserunnerTracker == 0x1011 && fn_3_A2DDC()) {
                break;
            }
            if ((hexBaserunnerTracker == 0x111 || hexBaserunnerTracker == 0x11) && fn_3_A2C9C()) {
                break;
            }
            if ((hexBaserunnerTracker == 0x1001 || hexBaserunnerTracker == 0x1101) && fn_3_A2B6C()) {
                break;
            }
            if (hexBaserunnerTracker == 0x101 && fn_3_A295C_inline()) {
                break;
            }
            if ((hexBaserunnerTracker & 1) != 0 && g_Ball.ballZoneAwayFromHome <= 1) {
                if (g_Ball.ballZoneWhenCaught <= 1) {
                    if (fielderDesperationLevel[0] <= 6 && fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[0]) != 0) {
                        break;
                    }
                } else if (fielderDesperationLevel[0] <= 4 && fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[0]) != 0) {
                    break;
                }
            }
            if (throwOutRunnerTaggingUpInd() != 0 || genericPlayOnRunnerOffBase() != 0 ||
                ((hexBaserunnerTracker & 1) != 0 && fielderDesperationLevel[0] <= 6 &&
                 fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[0]) != 0)) {
                break;
            }
            if ((hexBaserunnerTracker & 0x1000) != 0 && fn_3_A1F3C()) {
                break;
            }
            if (g_Ball.ballZoneAwayFromHome >= 2 && fielderAIWeirdSituation() != 0) {
                break;
            }
            if (focusRunner >= 0) {
                fielderAIMakePlay(focusRunner);
            } else {
                InMemRunnerType* runner = &g_Runners[3];

                for (i = 3; i >= 0; i--, runner--) {
                    if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD && runner->baseStandingOn < 0 &&
                        runner->runningDirectionCode == 2) {
                        fielderAIMakePlay(i);
                        break;
                    }
                }
            }
        } while (0);
    }
checkOverrideReasons:
    throwLoc = g_FieldingLogic.locationThrownTo;
    if (throwLoc >= 0 && throwLoc <= 3) {
        s16 covering = g_FieldingLogic.fielderAssignedLocationIndex[throwLoc];

        if (covering >= 0 && (g_Fielders[covering].onFire != 0 || g_Fielders[covering].knockoutStatus != 0 ||
                              g_Fielders[covering].bodyCheckResult != 0)) {
            g_FieldingLogic.locationThrownTo = -1;
            g_FieldingLogic.somethingForTryingTagOutTargetBase = throwLoc;
        }
    }
    if (g_RunningLogic.nOffensivePlayersAtStartOfPlay > 1 && g_Strikes.storedOuts <= 1 &&
        (hexBaserunnerTracker & 1) != 0 && g_Ball.ballZoneAwayFromHome <= 1 && g_Ball.ballZoneWhenCaught <= 1 &&
        g_FieldingLogic.locationThrownTo == 1 && fielderDesperationLevel[0] <= 2) {
        if (g_Runners[2].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
            (g_Runners[2].runningDirectionCode == 1 || g_Runners[2].runningDirectionCode == 2) &&
            g_Runners[2].fractionalBasesRan <= lbl_3_rodata_19C4 && g_Runners[2].baseStandingOn < 0) {
            g_FieldingLogic.locationThrownTo = -1;
        }
        if (g_Runners[3].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
            (g_Runners[3].runningDirectionCode == 1 || g_Runners[3].runningDirectionCode == 2) &&
            g_Runners[3].fractionalBasesRan <= lbl_3_rodata_19C8 && g_Runners[3].baseStandingOn < 0) {
            g_FieldingLogic.locationThrownTo = -1;
        }
    }
    if (highSkillLowDesperation && g_FieldingLogic.locationThrownTo >= 0 && g_FieldingLogic.locationThrownTo <= 3 &&
        fielder->always0_ == 1) {
        g_FieldingLogic.locationThrownTo = -1;
    }
    if (g_FieldingLogic.locationThrownTo == 6) {
        if (g_FieldingLogic.cutoffFielderIndex < 0) {
            g_FieldingLogic.locationThrownTo = -1;
        } else if (g_FieldingLogic.cutoffFielderIndex == fielderIndex) {
            g_FieldingLogic.locationThrownTo = -1;
        } else {
            if (lbl_3_rodata_1994 + g_Fielders[g_FieldingLogic.cutoffFielderIndex].distanceToMound >
                fielder->distanceToMound) {
                g_FieldingLogic.locationThrownTo = -1;
            }
            if (fielder->distanceFromEachFielder[g_FieldingLogic.cutoffFielderIndex] < lbl_3_rodata_1994) {
                g_FieldingLogic.locationThrownTo = -1;
            }
        }
    }
    if (fielder->animatingActionInd == 0) {
        if (g_FieldingLogic.somethingForTryingTagOutTargetBase >= 0) {
            if (g_Ball.numberOfThrowsDuringPlay == 1 && g_Ball.timeSinceBallPickedUp < 45 &&
                g_FieldingLogic.fielderActionBeingProcessed != 0) {
                g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
            } else {
                fielderAIChaseRunner();
            }
        }
    } else {
        g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
    }
    if (g_FieldingLogic._010d != 0) {
        if (g_Ball.timeSinceBallPickedUp >= 0 && g_Ball.timeSinceBallPickedUp < 40) {
            if (g_FieldingLogic.locationThrownTo >= 0) {
                g_FieldingLogic._010c = 1;
                g_FieldingLogic._010d = 0;
            }
        } else {
            g_FieldingLogic._010d = 0;
        }
    }
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
BOOL fielderAIWeirdSituation(void) {
    u32 flags = 0;
    InMemRunnerType* runner = &g_Runners[0];
    int i;

    for (i = 0; i < 4; i++) {
        if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
            if (runner->fractionalBasesRan < lbl_3_rodata_19E0) {
                flags |= 0x10;
            } else if (runner->fractionalBasesRan < lbl_3_rodata_19E4) {
                flags |= 0x100;
            } else if (runner->fractionalBasesRan <= lbl_3_rodata_199C) {
                flags |= 0x1000;
            }
        }
        runner++;
    }
    if (g_Ball.ballAngleFromHome > 0x500) {
        if (flags & 0x1000) {
            fn_3_A41E8(3);
            return 1;
        } else if (flags & 0x100) {
            fn_3_A41E8(3);
            return 1;
        } else if (flags & 0x10) {
            fn_3_A41E8(2);
            return 1;
        }
        return 0;
    }
    if (g_Ball.ballAngleFromHome > 0x400) {
        if (flags & 0x1000) {
            fn_3_A41E8(3);
            return 1;
        } else if ((flags & 0x100) && !(flags & 0x1000)) {
            fn_3_A41E8(2);
            return 1;
        }
        return 0;
    }
    if (flags & 0x1000) {
        if (!(flags & 0x10) || (flags & 0x100)) {
            fn_3_A41E8(0);
            return 1;
        }
        return 0;
    }
    if (flags & 0x100) {
        fn_3_A41E8(3);
        return 1;
    }
    return 0;
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
            if ((hexMovementsInEachBaseline1for2back4stop & 0x1000) != 0 &&
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
            if ((hexMovementsInEachBaseline1for2back4stop & 0x100) != 0 &&
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
            if ((hexMovementsInEachBaseline1for2back4stop & 0x10) != 0 &&
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
        if ((hexMovementsInEachBaseline1for2back4stop & 0x10) != 0 &&
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
        if ((hexMovementsInEachBaseline1for2back4stop & 0x6000) != 0 &&
            fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[3]] <= 4 &&
            g_FieldingLogic.fielderAssignedLocationIndex[3] >= 0 &&
            !(g_Fielders[g_FieldingLogic.fielderAssignedLocationIndex[3]].distanceToBases[3] > lbl_3_rodata_19A4) &&
            !(g_Runners[originalBaseOfRunnerInThisBaseline[3]].percentTowardsNextBase < lbl_3_rodata_19B0 &&
              indBallNearBaselineWhereRunnerIs[3] == 0) &&
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
    if (enoughTimeToGetLeadRunnerAt2B != 0 && fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[1]) != 0) {
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
    if (enoughTimeToGetLeadRunnerAt2B != 0 && fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[1]) != 0) {
        return 1;
    }
    if (g_Ball.ballDistanceFromBase[0] <= g_Ball.ballDistanceFromBase[2]) {
        if ((hexMovementsInEachBaseline1for2back4stop & 0x1000) != 0 &&
            fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[3]] <= 3 &&
            fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[3]) != 0) {
            return 1;
        }
        if ((hexMovementsInEachBaseline1for2back4stop & 0x6000) != 0 &&
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
        if ((hexMovementsInEachBaseline1for2back4stop & 0x1000) != 0 &&
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
    if ((runnersInStartingBaselineBits & 0x1000) != 0 &&
        fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[3]) != 0) {
        return 1;
    }
    if ((hexMovementsInEachBaseline1for2back4stop & 0x1000) != 0 &&
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
    if ((runnersInStartingBaselineBits & 0x1000) != 0 &&
        fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[3]) != 0) {
        return 1;
    }
    if ((hexMovementsInEachBaseline1for2back4stop & 0x1000) != 0 &&
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
        if ((hexMovementsInEachBaseline1for2back4stop & 0x1000) != 0) {
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
                if ((hexMovementsInEachBaseline1for2back4stop & 0x110) != 0) {
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
        (hexMovementsInEachBaseline1for2back4stop & 0x100) != 0) {
        if ((hexBaserunnerTracker & 0x10) == 0) {
            if (fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[2]] <= 5 &&
                fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[2]) != 0) {
                return 1;
            }
        } else if ((hexMovementsInEachBaseline1for2back4stop & 0x60) == 0 &&
                   fielderDesperationLevel[originalBaseOfRunnerInThisBaseline[2]] <= 4 &&
                   fielderAIMakePlay(originalBaseOfRunnerInThisBaseline[2]) != 0) {
            return 1;
        }
    }
    if ((hexBaserunnerTracker & 0x10) != 0 && g_Ball.ballDistanceFromBase[2] < lbl_3_rodata_1A08 &&
        (hexMovementsInEachBaseline1for2back4stop & 0x10) != 0 && (hexBaserunnerTracker & 0x1000) == 0 &&
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
            enoughTimeToGetLeadRunnerAt2B = 1;
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

    hexMovementsInEachBaseline1for2back4stop = 0;
    for (i = 0; i < 4; i++) {
        if (originalBaseOfRunnerInThisBaseline[i] >= 0) {
            InMemRunnerType* runner = &g_Runners[originalBaseOfRunnerInThisBaseline[i]];
            if (runner->runningDirectionCode == 1) {
                hexMovementsInEachBaseline1for2back4stop |= 1 << (i * 4);
            } else if (runner->runningDirectionCode == 3) {
                hexMovementsInEachBaseline1for2back4stop |= 2 << (i * 4);
            } else if (runner->runningDirectionCode == 2) {
                hexMovementsInEachBaseline1for2back4stop |= 4 << (i * 4);
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
void fn_3_A41E8(int base) {
    int fielderWBall = g_Ball.fielderWBallIndex;
    InMemFielder* fielder = &g_Fielders[fielderWBall];
    int assigned = g_FieldingLogic.fielderAssignedLocationIndex[base];
    f32 speed;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 baseX;
    f32 baseZ;
    f32 ballDist;
    int frames;
    int total;
    int timeToBase;

    if (base == 5) {
        BOOL cover;
        if (g_FieldingLogic.fielderAssignedLocationIndex[4] == -1) {
            cover = 0;
        } else if (g_FieldingLogic.playerAtMoundCutoffLocation != 1) {
            cover = 0;
        } else if (g_Fielders[g_FieldingLogic.fielderAssignedLocationIndex[4]].locationResponsibleForCovering != 5) {
            cover = 0;
        } else if (fielder->distanceToMound < lbl_3_rodata_19F0) {
            cover = 0;
        } else {
            cover = 1;
        }
        if (cover) {
            g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
            g_FieldingLogic.locationThrownTo = 5;
        } else if (g_Ball.ballZoneAwayFromHome >= 3 && g_FieldingLogic.cutoffFielderIndex >= 0 &&
                   g_FieldingLogic.cutoffFielderIndex != g_Ball.fielderWBallIndex) {
            g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
            g_FieldingLogic.locationThrownTo = 6;
        } else {
            g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
            g_FieldingLogic.locationThrownTo = -1;
        }
        return;
    }

    speed = fielder->modifiedThrowingArm / lbl_3_rodata_1938;
    dx = base_MoundCoordinates[base].x - fielder->pos.x;
    dz = base_MoundCoordinates[base].z - fielder->pos.z;
    dx = dx * dx;
    dz = dz * dz;
    dist = dolsqrtf2(dx + dz);
    if (lbl_3_rodata_193C == speed) {
        speed = lbl_3_rodata_1958;
    }
    if (dist > lbl_3_rodata_195C) {
        frames = (lbl_3_rodata_1960 * dist) / speed;
    } else if (dist > lbl_3_rodata_1964) {
        frames = dist / speed;
    } else {
        frames = (lbl_3_rodata_1968 * dist) / speed;
    }
    if (dist > lbl_3_rodata_196C) {
        frames = (int)(frames * lbl_3_rodata_1970) + 0x1e;
    } else if (dist > lbl_3_rodata_1974) {
        frames = (int)(frames * lbl_3_rodata_1960) + 0x1e;
    }
    total = fielder->throwWindupEstimate + frames;
    ballDist = g_Ball.ballDistanceFromBase[base];
    baseX = base_MoundCoordinates[base].x;
    baseZ = base_MoundCoordinates[base].z;
    timeToBase = fRunningTimeToDestinationPlus7(g_Ball.fielderWBallIndex, baseX, baseZ);
    if (assigned == g_Ball.fielderWBallIndex || assigned == -1 || ballDist < lbl_3_rodata_199C) {
        g_FieldingLogic.somethingForTryingTagOutTargetBase = base;
        g_FieldingLogic.locationThrownTo = -1;
    } else if (timeToBase < g_Fielders[assigned].numFramesToGetToAutoLocation + 5) {
        g_FieldingLogic.somethingForTryingTagOutTargetBase = base;
        g_FieldingLogic.locationThrownTo = -1;
    } else if (total < g_Fielders[assigned].numFramesToGetToAutoLocation) {
        g_FieldingLogic.somethingForTryingTagOutTargetBase = base;
        g_FieldingLogic.locationThrownTo = -1;
    } else {
        g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
        g_FieldingLogic.locationThrownTo = base;
    }
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
    s32* frames_p;
    s32* running_p;
    s32* throw_p;
    u8* indBall_p;
    InMemRunnerType* runner;
    InMemRunnerType* runnerPre;
    s32* throwPre;
    s32* framesPre;
    int i;
    InMemFielder* fielder;
    s32* desperation;
    u8 steal;
    f32 speed;
    f32 dx;
    f32 dz;
    f32 dist;
    int frames;

    runnerPre = g_Runners;
    framesPre = framesRunnerIsOutOfReach;
    throwPre = throwStratToMakePlay;
    runner = runnerPre;
    frames_p = framesPre;
    running_p = runningStratToMakePlay;
    throw_p = throwPre;
    indBall_p = indBallNearBaselineWhereRunnerIs;
    for (i = 0; i < 4; i++) {
        *frames_p = 0;
        *running_p = -1;
        *throw_p = -1;
        *indBall_p = 0;
        if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
            if (runner->tagUpInd == TAG_UP_TYPE_TAGGED) {
                throwTimeToBase(i);
            } else if (runner->baseStandingOn != -1 && runner->forceOutCd <= FORCE_OUT_TYPE_NOT_FORCED_TO_ADVANCE) {
                fielder = &g_Fielders[g_Ball.fielderWBallIndex];
                if (i == 3 && runner->baseStandingOn == 3 && g_RunningLogic._00 == 0x1000 &&
                    g_Ball.ballZoneAwayFromHome >= 4 && g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT) {
                    speed = fielder->modifiedThrowingArm / lbl_3_rodata_1938;
                    dx = base_MoundCoordinates[0].x - fielder->pos.x;
                    dz = base_MoundCoordinates[0].z - fielder->pos.z;
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
                    frames = fielder->throwWindupEstimate + frames + lbl_3_data_1C40;
                    *throw_p = 0;
                    *running_p = -1;
                    *frames_p = frames - runner->framesToNextBase;
                }
            } else if (runner->overrunBaseStage == 0) {
                if (runner->forceOutCd == FORCE_OUT_TYPE_FORCED_TO_ADVANCE) {
                    runnerTimeToCoverBase(i);
                } else {
                    fieldingAIThrowOrChase(i);
                }
            }
        }
        running_p++;
        throw_p++;
        indBall_p++;
        runner++;
        frames_p++;
    }
    steal = g_FieldingLogic.liveBallBcOfPickoffOrStealCd;
    desperation = fielderDesperationLevel;
    for (i = 0; i < 4; i++) {
        *desperation = 9;
        if (runnerPre->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
            (runnerPre->baseStandingOn == -1 || runnerPre->tagUpInd == TAG_UP_TYPE_TAGGED ||
             runnerPre->forceOutCd > FORCE_OUT_TYPE_NOT_FORCED_TO_ADVANCE || *throwPre == 0)) {
            frames = *framesPre;
            if (frames >= 0x5a) {
                *desperation = 8;
            } else if (frames >= 0x1e) {
                *desperation = 7;
            } else if (frames >= 0xf) {
                *desperation = 6;
            } else if (frames >= 8) {
                *desperation = 5;
            } else if (frames >= -8) {
                *desperation = 4;
            } else if (frames >= -0xf) {
                *desperation = 3;
            } else if (frames >= -0x1e) {
                *desperation = 2;
            } else if (frames >= -0x2d) {
                *desperation = 1;
            } else {
                *desperation = 0;
            }
            if (steal == 2) {
                *desperation = *desperation - 2;
                if (*desperation < 2) {
                    *desperation = 0;
                } else {
                    *desperation = *desperation - 2;
                }
            }
        }
        desperation++;
        runnerPre++;
        throwPre++;
        framesPre++;
    }
}

// .text:0x000A4F50 size:0x48C mapped:0x806E3FE4
void throwTimeToBase(int baseCounter) {
    InMemRunnerType* runner = &g_Runners[baseCounter];
    InMemFielder* fielder = &g_Fielders[g_Ball.fielderWBallIndex];
    int base;
    int coveringFielder;
    s16 coverFrames;
    int totalFrames;
    int runFrames;
    int framesToBase;
    f32 speed;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 ballDist;
    f32 baseX;
    f32 baseZ;
    int frames;

    speed = fielder->modifiedThrowingArm / lbl_3_rodata_1938;
    base = runner->startingBase_baseAchieved;
    dx = base_MoundCoordinates[base].x - fielder->pos.x;
    dz = base_MoundCoordinates[base].z - fielder->pos.z;
    coveringFielder = g_FieldingLogic.fielderAssignedLocationIndex[base];
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
    ballDist = g_Ball.ballDistanceFromBase[base];
    totalFrames = fielder->throwWindupEstimate + (frames + 0x14) + lbl_3_data_1C40;
    baseX = base_MoundCoordinates[base].x;
    baseZ = base_MoundCoordinates[base].z;
    runFrames = fRunningTimeToDestinationPlus7(g_Ball.fielderWBallIndex, baseX, baseZ);
    if (runner->currentBase == runner->startingBase_baseAchieved) {
        framesToBase = runner->framesToPreviousBase;
    } else {
        framesToBase = runner->framesToPreviousBase + 0xb4;
    }
    if (coveringFielder != g_Ball.fielderWBallIndex && coveringFielder != -1 && !(ballDist < lbl_3_rodata_19A4)) {
        coverFrames = g_Fielders[coveringFielder].numFramesToGetToAutoLocation;
        if ((coverFrames >= 0 || g_FieldingLogic.baseCoveredInd[base] != 0) && g_Ball.framesSinceHit >= 0x46) {
            if (runFrames < coverFrames + 5) {
                lbl_3_bss_17F8[16 + baseCounter] = base;
                lbl_3_bss_17F8[12 + baseCounter] = -1;
                lbl_3_bss_17F8[20 + baseCounter] = runFrames - framesToBase;
            } else if (totalFrames < coverFrames ||
                       (coverFrames < 0 && g_Fielders[coveringFielder].lockoutDuration <= g_Ball.framesSinceHit)) {
                lbl_3_bss_17F8[12 + baseCounter] = base + 10;
                lbl_3_bss_17F8[16 + baseCounter] = -1;
                lbl_3_bss_17F8[20 + baseCounter] = coverFrames - framesToBase;
            } else {
                lbl_3_bss_17F8[12 + baseCounter] = base;
                lbl_3_bss_17F8[16 + baseCounter] = -1;
                lbl_3_bss_17F8[20 + baseCounter] = totalFrames - framesToBase;
            }
            return;
        }
    }
    lbl_3_bss_17F8[16 + baseCounter] = base;
    lbl_3_bss_17F8[12 + baseCounter] = -1;
    lbl_3_bss_17F8[20 + baseCounter] = runFrames - framesToBase;
}

// .text:0x000A53DC size:0x328 mapped:0x806E4470
void fn_3_A53DC(int runnerIdx) {
    InMemRunnerType* runner = &g_Runners[runnerIdx];
    InMemFielder* fielder = &g_Fielders[g_Ball.fielderWBallIndex];
    f32 speed;
    f32 dx;
    f32 dz;
    f32 dist;
    int frames;

    if (runnerIdx == 3 && runner->baseStandingOn == 3 && g_RunningLogic._00 == 0x1000 &&
        g_Ball.ballZoneAwayFromHome >= 4 && g_Ball.AtBat_ContactResult == BALL_RESULT_TYPE_CAUGHT) {
        speed = fielder->modifiedThrowingArm / lbl_3_rodata_1938;
        dx = base_MoundCoordinates[0].x - fielder->pos.x;
        dz = base_MoundCoordinates[0].z - fielder->pos.z;
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
        frames = fielder->throwWindupEstimate + frames + lbl_3_data_1C40;
        lbl_3_bss_17F8[12 + runnerIdx] = 0;
        lbl_3_bss_17F8[16 + runnerIdx] = -1;
        lbl_3_bss_17F8[20 + runnerIdx] = frames - runner->framesToNextBase;
    }
}

// .text:0x000A5704 size:0x448 mapped:0x806E4798
void runnerTimeToCoverBase(int runnerIndex) {
    InMemRunnerType* runner = &g_Runners[runnerIndex];
    InMemFielder* fielder = &g_Fielders[g_Ball.fielderWBallIndex];
    int base;
    int framesToBase;
    int coveringFielder;
    s16 coverFrames;
    int totalFrames;
    int runFrames;
    f32 speed;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 ballDist;
    f32 baseX;
    f32 baseZ;
    int frames;

    speed = fielder->modifiedThrowingArm / lbl_3_rodata_1938;
    base = runner->nextBase;
    dx = base_MoundCoordinates[base].x - fielder->pos.x;
    dz = base_MoundCoordinates[base].z - fielder->pos.z;
    framesToBase = runner->framesToNextBase;
    coveringFielder = g_FieldingLogic.fielderAssignedLocationIndex[base];
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
    totalFrames = fielder->throwWindupEstimate + frames + lbl_3_data_1C40;
    ballDist = g_Ball.ballDistanceFromBase[base];
    baseX = base_MoundCoordinates[base].x;
    baseZ = base_MoundCoordinates[base].z;
    runFrames = fRunningTimeToDestinationPlus7(g_Ball.fielderWBallIndex, baseX, baseZ);
    if (coveringFielder != g_Ball.fielderWBallIndex && coveringFielder != -1 && !(ballDist < lbl_3_rodata_199C) &&
        g_Fielders[coveringFielder].lockedOutInd == 0 &&
        ((coverFrames = g_Fielders[coveringFielder].numFramesToGetToAutoLocation) >= 0 ||
         g_FieldingLogic.baseCoveredInd[base] != 0)) {
        if (runFrames < coverFrames + 5) {
            lbl_3_bss_17F8[16 + runnerIndex] = base;
            lbl_3_bss_17F8[12 + runnerIndex] = -1;
            lbl_3_bss_17F8[20 + runnerIndex] = runFrames - framesToBase;
        } else if (totalFrames + 5 < coverFrames) {
            lbl_3_bss_17F8[12 + runnerIndex] = base + 10;
            lbl_3_bss_17F8[16 + runnerIndex] = -1;
            lbl_3_bss_17F8[20 + runnerIndex] = coverFrames - framesToBase;
        } else {
            lbl_3_bss_17F8[12 + runnerIndex] = base;
            lbl_3_bss_17F8[16 + runnerIndex] = -1;
            lbl_3_bss_17F8[20 + runnerIndex] = totalFrames - framesToBase;
        }
    } else {
        lbl_3_bss_17F8[16 + runnerIndex] = base;
        lbl_3_bss_17F8[12 + runnerIndex] = -1;
        lbl_3_bss_17F8[20 + runnerIndex] = runFrames - framesToBase;
    }
}

// .text:0x000A5B4C size:0x898 mapped:0x806E4BE0
void fieldingAIThrowOrChase(int runnerIndex) {
    InMemRunnerType* runner = &g_Runners[runnerIndex];
    int baseCurr = runner->currentBase;
    int baseNext = runner->nextBase;
    int distFromBall = (int)runner->distanceFromBall;
    f32 runnerDistNext;
    f32 runnerDistCurr;
    f32 ballDistNext;
    f32 ballDistCurr;
    int closer;
    int throwStrat;
    int runStrat;
    int frames;

    ballDistNext = g_Ball.ballDistanceFromBase[baseNext];
    ballDistCurr = g_Ball.ballDistanceFromBase[baseCurr];
    closer = 0;
    runnerDistNext = runner->distToNextBase;
    runnerDistCurr = runner->distToCurrentBase;

    if (ballDistNext + ballDistCurr < lbl_3_rodata_1A1C && runner->actionCode == 0) {
        indBallNearBaselineWhereRunnerIs[runnerIndex] = 1;
        if (ballDistNext < runnerDistNext) {
            closer = 1;
        } else if (ballDistCurr < runnerDistCurr) {
            closer = -1;
        }
        if (runner->runningDirectionCode == 1) {
            if (runner->restrictedMovementCodes & 1) {
                runningStratToMakePlay[runnerIndex] = 9;
                throwStratToMakePlay[runnerIndex] = -1;
                framesRunnerIsOutOfReach[runnerIndex] = 0;
            } else if (closer == 1) {
                if (g_Ball.baseBallAndFielderAreOn == baseNext &&
                    ((runnerDistNext < lbl_3_rodata_1A20 && runner->runningDirectionCode == 1 &&
                      runner->nextDirectionBeingProcessed == 0) ||
                     runner->actionCode != 0)) {
                    framesRunnerIsOutOfReach[runnerIndex] = -50;
                    runningStratToMakePlay[runnerIndex] = baseNext;
                    throwStratToMakePlay[runnerIndex] = -1;
                } else {
                    runningStratToMakePlay[runnerIndex] = 9;
                    throwStratToMakePlay[runnerIndex] = -1;
                    framesRunnerIsOutOfReach[runnerIndex] = -15;
                }
            } else {
                frames = howManyFramesTheRunnerIsOutOfReach(runnerIndex, 1, &throwStrat, &runStrat) - 10;
                if (g_Ball.numberOfThrowsDuringPlay <= 3 && g_FieldingLogic.somethingForTryingTagOutTargetBase == -1 &&
                    !(frames < -45)) {
                    framesRunnerIsOutOfReach[runnerIndex] = frames;
                    throwStratToMakePlay[runnerIndex] = throwStrat;
                    runningStratToMakePlay[runnerIndex] = runStrat;
                } else if (runner->percentTowardsNextBase > lbl_3_rodata_1A24 || !(frames < -15)) {
                    framesRunnerIsOutOfReach[runnerIndex] = frames;
                    throwStratToMakePlay[runnerIndex] = throwStrat;
                    runningStratToMakePlay[runnerIndex] = runStrat;
                } else {
                    runningStratToMakePlay[runnerIndex] = 9;
                    throwStratToMakePlay[runnerIndex] = -1;
                    framesRunnerIsOutOfReach[runnerIndex] = 0;
                }
            }
        } else if (runner->runningDirectionCode == 3) {
            if (runner->restrictedMovementCodes & 2) {
                runningStratToMakePlay[runnerIndex] = 9;
                throwStratToMakePlay[runnerIndex] = -1;
                framesRunnerIsOutOfReach[runnerIndex] = 0;
            } else if (closer == -1) {
                if (g_Ball.baseBallAndFielderAreOn == baseCurr && runnerDistCurr < lbl_3_rodata_1A20 &&
                    runner->runningDirectionCode == 3 && runner->nextDirectionBeingProcessed == 0) {
                    framesRunnerIsOutOfReach[runnerIndex] = -50;
                    runningStratToMakePlay[runnerIndex] = baseCurr;
                    throwStratToMakePlay[runnerIndex] = -1;
                } else {
                    runningStratToMakePlay[runnerIndex] = 9;
                    throwStratToMakePlay[runnerIndex] = -1;
                    framesRunnerIsOutOfReach[runnerIndex] = -15;
                }
            } else {
                frames = howManyFramesTheRunnerIsOutOfReach(runnerIndex, 0, &throwStrat, &runStrat) - 10;
                if (runner->percentTowardsNextBase < lbl_3_rodata_19A0 || !(frames < -8)) {
                    framesRunnerIsOutOfReach[runnerIndex] = frames;
                    throwStratToMakePlay[runnerIndex] = throwStrat;
                    runningStratToMakePlay[runnerIndex] = runStrat;
                } else if (runner->percentTowardsNextBase < lbl_3_rodata_19B4 && !(frames < -8) &&
                           (runner->nextDirectionBeingProcessed == 0 || runner->runningDirectionCode != 2)) {
                    framesRunnerIsOutOfReach[runnerIndex] = frames;
                    throwStratToMakePlay[runnerIndex] = throwStrat;
                    runningStratToMakePlay[runnerIndex] = runStrat;
                } else {
                    runningStratToMakePlay[runnerIndex] = 9;
                    throwStratToMakePlay[runnerIndex] = -1;
                    framesRunnerIsOutOfReach[runnerIndex] = 0;
                }
            }
        } else {
            runningStratToMakePlay[runnerIndex] = 9;
            throwStratToMakePlay[runnerIndex] = -1;
            framesRunnerIsOutOfReach[runnerIndex] = 0;
        }
    } else if (runner->runningDirectionCode == 1) {
        if (runner->percentTowardsNextBase < lbl_3_rodata_19AC) {
            if (ballDistNext < lbl_3_rodata_19F0) {
                runningStratToMakePlay[runnerIndex] = 9;
                throwStratToMakePlay[runnerIndex] = -1;
                framesRunnerIsOutOfReach[runnerIndex] = -15;
                return;
            }
            if (ballDistCurr < lbl_3_rodata_19F0) {
                if ((f32)distFromBall > lbl_3_rodata_1994) {
                    frames = howManyFramesTheRunnerIsOutOfReach(runnerIndex, 0, &throwStrat, &runStrat);
                    framesRunnerIsOutOfReach[runnerIndex] = frames;
                    throwStratToMakePlay[runnerIndex] = throwStrat;
                    runningStratToMakePlay[runnerIndex] = runStrat;
                }
                return;
            }
        }
        frames = howManyFramesTheRunnerIsOutOfReach(runnerIndex, 1, &throwStrat, &runStrat);
        frames += lbl_3_data_1C40;
        if (frames < -45) {
            if ((f32)distFromBall < lbl_3_rodata_1A0C) {
                runningStratToMakePlay[runnerIndex] = 9;
                throwStratToMakePlay[runnerIndex] = -1;
                framesRunnerIsOutOfReach[runnerIndex] = -15;
            } else if (ballDistNext > lbl_3_rodata_19F0) {
                framesRunnerIsOutOfReach[runnerIndex] = frames;
                throwStratToMakePlay[runnerIndex] = throwStrat;
                runningStratToMakePlay[runnerIndex] = runStrat;
            } else if (ballDistNext < runnerDistNext) {
                runningStratToMakePlay[runnerIndex] = 9;
                throwStratToMakePlay[runnerIndex] = -1;
                framesRunnerIsOutOfReach[runnerIndex] = -30;
            } else {
                framesRunnerIsOutOfReach[runnerIndex] = frames;
                throwStratToMakePlay[runnerIndex] = throwStrat;
                runningStratToMakePlay[runnerIndex] = runStrat;
            }
        } else {
            framesRunnerIsOutOfReach[runnerIndex] = frames;
            throwStratToMakePlay[runnerIndex] = throwStrat;
            runningStratToMakePlay[runnerIndex] = runStrat;
        }
    } else if (runner->runningDirectionCode == 3) {
        frames = howManyFramesTheRunnerIsOutOfReach(runnerIndex, 0, &throwStrat, &runStrat);
        frames += lbl_3_data_1C40;
        if (frames < -30) {
            if (ballDistCurr > lbl_3_rodata_19F0) {
                framesRunnerIsOutOfReach[runnerIndex] = frames;
                throwStratToMakePlay[runnerIndex] = throwStrat;
                runningStratToMakePlay[runnerIndex] = runStrat;
            } else if (ballDistCurr < runnerDistCurr) {
                runningStratToMakePlay[runnerIndex] = 9;
                throwStratToMakePlay[runnerIndex] = -1;
                framesRunnerIsOutOfReach[runnerIndex] = -30;
            } else {
                framesRunnerIsOutOfReach[runnerIndex] = frames;
                throwStratToMakePlay[runnerIndex] = throwStrat;
                runningStratToMakePlay[runnerIndex] = runStrat;
            }
        } else if (runner->percentTowardsNextBase >= lbl_3_rodata_1A28) {
            framesRunnerIsOutOfReach[runnerIndex] = frames;
            throwStratToMakePlay[runnerIndex] = throwStrat;
            runningStratToMakePlay[runnerIndex] = runStrat;
        } else {
            framesRunnerIsOutOfReach[runnerIndex] = frames;
            throwStratToMakePlay[runnerIndex] = throwStrat;
            runningStratToMakePlay[runnerIndex] = runStrat;
        }
    } else if (runner->runningDirectionCode == 2 && runner->baseStandingOn < 0) {
        if (ballDistNext < lbl_3_rodata_19F0) {
            runningStratToMakePlay[runnerIndex] = 9;
            throwStratToMakePlay[runnerIndex] = -1;
            framesRunnerIsOutOfReach[runnerIndex] = -15;
        } else {
            frames = howManyFramesTheRunnerIsOutOfReach(runnerIndex, 1, &throwStrat, &runStrat);
            frames += lbl_3_data_1C40;
            throwStratToMakePlay[runnerIndex] = throwStrat;
            framesRunnerIsOutOfReach[runnerIndex] = frames;
            runningStratToMakePlay[runnerIndex] = runStrat;
        }
    }
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
    f32 baseX;
    f32 baseZ;
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
    baseX = base_MoundCoordinates[base].x;
    baseZ = base_MoundCoordinates[base].z;
    dx = baseX - fielder->pos.x;
    dz = baseZ - fielder->pos.z;
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
    runFrames = fRunningTimeToDestinationPlus7(g_Ball.fielderWBallIndex, baseX, baseZ);
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
void tagRelated(int fielderIndex) {
    int baseOn;

    if (g_FieldingLogic.framesRunnerIsOutBy > 0) {
        g_FieldingLogic.framesRunnerIsOutBy--;
    }
    baseOn = g_FieldingLogic.baseFielderIsOn;
    if ((s8)baseOn >= 0) {
        g_Ball.baseBallAndFielderAreOn = (s8)baseOn;
        if (g_FieldingLogic.somethingForTryingTagOutTargetBase == (s8)baseOn) {
            g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
        }
    }
    if (g_FieldingLogic.framesRunnerIsOutBy <= 0) {
        g_FieldingLogic.tagResult_1out_2safe = 2;
    }
    if (g_FieldingLogic.tagAnimationType == 2 && g_FieldingLogic.tagResult_1out_2safe == 1) {
        setFielderAutoCoords(fielderIndex, g_Runners[g_FieldingLogic.runnerBeingTargettedForOut].position.x,
                             g_Runners[g_FieldingLogic.runnerBeingTargettedForOut].position.z);
        if (g_FieldingLogic.somethingForTryingTagOutTargetBase == 9) {
            g_FieldingLogic.runnerChasingAfter = g_FieldingLogic.runnerBeingTargettedForOut;
        }
        fielderAIChaseRunner();
    } else if (g_FieldingLogic.tagAnimationType == 1) {
        if (g_FieldingLogic.runnerBeingTargettedForOut >= 0) {
            if (g_Runners[g_FieldingLogic.runnerBeingTargettedForOut].runnerOnFieldOrOutOrScored ==
                RUNNER_STATUS_ON_FIELD) {
                if (g_Runners[g_FieldingLogic.runnerBeingTargettedForOut].baseStandingOn >= 0) {
                    g_FieldingLogic.tagAnimationType = 0;
                } else if (g_Runners[g_FieldingLogic.runnerBeingTargettedForOut].actionCode == 0 &&
                           (g_Runners[g_FieldingLogic.runnerBeingTargettedForOut].runningDirectionCode == 1 ||
                            g_Runners[g_FieldingLogic.runnerBeingTargettedForOut].runningDirectionCode == 3)) {
                    g_FieldingLogic.tagAnimationType = 0;
                }
            } else {
                g_FieldingLogic.tagAnimationType = 0;
            }
        } else {
            g_FieldingLogic.tagAnimationType = 0;
        }
        if (g_FieldingLogic.runnerChasingAfter >= 0) {
            g_FieldingLogic.runnerChasingAfter = -1;
            g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
        }
    }
}

// .text:0x000A7040 size:0x674 mapped:0x806E60D4
void tagOutValues(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    InMemRunnerType* runner;
    int base = -1;
    int i;
    int result;
    int okToTag;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 runDir;
    f32 baseDist;

    g_FieldingLogic.tagAnimationType = 0;
    g_FieldingLogic.runnerBeingTargettedForOut = -1;
    if (g_Strikes.outs < 3 && g_Ball.ballState == BALL_STATE_HELD && g_Ball.fielderWBallIndex >= 0 &&
        g_FieldingLogic.tagAnimationCountdown == 0) {
        if (fielder->baseCurrentlyOn >= 0) {
            base = fielder->baseCurrentlyOn;
        }
        if (fielder->distanceToBases[0] <= lbl_3_rodata_1968) {
            base = 0;
        } else if (fielder->distanceToBases[1] <= lbl_3_rodata_1968) {
            base = 1;
        } else if (fielder->distanceToBases[2] <= lbl_3_rodata_1968) {
            base = 2;
        } else if (fielder->distanceToBases[3] <= lbl_3_rodata_1968) {
            base = 3;
        }
        if (base >= 0) {
            runner = &g_Runners[3];
            for (i = 3; i >= 0; i--) {
                if ((g_Pitcher.strikeOutOrWalk != 2 || runner->furthestBaseForcedToGoToOnWalk <= runner->currentBase) &&
                    runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                    if (base == runner->baseStandingOn_Stored && runner->baseStandingOn < 0 &&
                        g_Ball.timeSinceBallPickedUp > 15 && runner->position.x < lbl_3_rodata_1A38) {
                        g_FieldingLogic.tagAnimationType = 5;
                        g_FieldingLogic.runnerBeingTargettedForOut = i;
                        g_FieldingLogic.tagResult_1out_2safe = 1;
                        g_FieldingLogic.framesRunnerIsOutBy = 1;
                        g_FieldingLogic.tagAnimationCountdown = 15;
                        g_FieldingLogic.tagOutFirstFrameInd = 1;
                        goto tagFound;
                    }
                    if (base == runner->baseRunningTowards) {
                        if (runner->forceOutCd == FORCE_OUT_TYPE_FORCED_TO_ADVANCE && runner->nextBase == base) {
                            break;
                        }
                        if (runner->forceOutType_unsed != 0) {
                            break;
                        }
                        if (runner->actionCode != 0) {
                            if (runner->actionFrames_countDown < 6) {
                                g_FieldingLogic.tagAnimationType = 1;
                                g_FieldingLogic.runnerBeingTargettedForOut = i;
                                g_FieldingLogic.tagResult_1out_2safe = 1;
                                g_FieldingLogic.tagAnimationCountdown = 15;
                                g_FieldingLogic.baseFielderIsOn = base;
                                g_FieldingLogic.tagOutFirstFrameInd = 1;
                                if (g_FieldingLogic.runnerChasingAfter >= 0) {
                                    g_FieldingLogic.runnerChasingAfter = i;
                                }
                                goto tagFound;
                            }
                        } else {
                            if (runner->tagUpInd == TAG_UP_TYPE_TAGGED && runner->distanceFromBall < lbl_3_rodata_1A3C &&
                                g_Ball.timeSinceBallPickedUp > 15) {
                                if (runner->baseStandingOn == base && i != runner->baseStandingOn) {
                                    g_FieldingLogic.tagAnimationType = 5;
                                } else {
                                    g_FieldingLogic.tagAnimationType = 2;
                                }
                                g_FieldingLogic.runnerBeingTargettedForOut = i;
                                g_FieldingLogic.tagResult_1out_2safe = 1;
                                g_FieldingLogic.framesRunnerIsOutBy = 1;
                                g_FieldingLogic.tagAnimationCountdown = 15;
                                g_FieldingLogic.tagOutFirstFrameInd = 1;
                                goto tagFound;
                            }
                        }
                    }
                }
                runner--;
            }
        }
        if (g_Ball.timeSinceBallPickedUp > 15) {
            runner = &g_Runners[3];
            for (i = 3; i >= 0; i--) {
                if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
                    (fielder->locationResponsibleForCovering < 0 || runner->forceOutCd != FORCE_OUT_TYPE_FORCED_TO_ADVANCE ||
                     runner->nextBase != base)) {
                    runDir = game_atan2(runner->velocity.x, runner->velocity.z);
                    dx = fielder->pos.x - runner->position.x;
                    dz = fielder->pos.z - runner->position.z;
                    if (calculateDiffInAngles(game_atan2(dx, dz), runDir) < 0x100 && runner->baseStandingOn < 0) {
                        if (runner->baseStandingOn < 0 || runner->tagUpInd == TAG_UP_TYPE_TAGGED) {
                            if (runner->distanceFromBall - fielder->currentVelocity < lbl_3_rodata_1A3C) {
                                g_FieldingLogic.tagAnimationType = 2;
                                g_FieldingLogic.runnerBeingTargettedForOut = i;
                                g_FieldingLogic.tagResult_1out_2safe = 1;
                                g_FieldingLogic.framesRunnerIsOutBy = 1;
                                g_FieldingLogic.tagAnimationCountdown = 15;
                                g_FieldingLogic.tagOutFirstFrameInd = 1;
                                if (g_FieldingLogic.runnerChasingAfter >= 0) {
                                    g_FieldingLogic.runnerChasingAfter = i;
                                }
                                goto tagFound;
                            }
                        }
                    } else {
                        dist = runner->distanceFromBall;
                        okToTag = 0;
                        if (dist < lbl_3_rodata_1994) {
                            if (runner->baseStandingOn < 0) {
                                okToTag = 1;
                            } else {
                                if (runner->runningDirectionCode == 1 && runner->distToCurrentBase > lbl_3_rodata_19A8) {
                                    okToTag = 1;
                                }
                                if (runner->forceOutCd == FORCE_OUT_TYPE_FORCED_TO_ADVANCE &&
                                    runner->baseStandingOn == runner->startingBase_baseAchieved) {
                                    okToTag = 1;
                                }
                            }
                        }
                        if (okToTag) {
                            result = 0;
                            if (runner->forceOutCd == FORCE_OUT_TYPE_FORCED_TO_ADVANCE &&
                                runner->baseStandingOn == runner->startingBase_baseAchieved && dist < lbl_3_rodata_1A3C) {
                                result = 2;
                            } else {
                                if (g_FieldingLogic.somethingForTryingTagOutTargetBase < 0 ||
                                    g_FieldingLogic.somethingForTryingTagOutTargetBase > 3 ||
                                    ((baseDist = fielder->distanceToBases[g_FieldingLogic.somethingForTryingTagOutTargetBase],
                                      !(baseDist < lbl_3_rodata_198C)) &&
                                     (!(baseDist < lbl_3_rodata_1994) ||
                                      (runner->forceOutCd == FORCE_OUT_TYPE_NOT_FORCED_TO_ADVANCE &&
                                       runner->tagUpInd != TAG_UP_TYPE_TAGGED)))) {
                                    if (dist < lbl_3_rodata_1A3C) {
                                        result = 1;
                                    }
                                }
                            }
                            if (result != 0) {
                                g_FieldingLogic.tagAnimationType = 2;
                                g_FieldingLogic.runnerBeingTargettedForOut = i;
                                g_FieldingLogic.tagResult_1out_2safe = 1;
                                g_FieldingLogic.framesRunnerIsOutBy = 1;
                                g_FieldingLogic.tagAnimationCountdown = 15;
                                g_FieldingLogic.tagOutFirstFrameInd = 1;
                                if (g_FieldingLogic.runnerChasingAfter >= 0) {
                                    g_FieldingLogic.runnerChasingAfter = i;
                                }
                                goto tagFound;
                            }
                        }
                    }
                }
                runner--;
            }
        }
        if (g_FieldingLogic.tagAnimationType == 2 && lbl_3_rodata_193C == fielder->currentVelocity) {
            g_FieldingLogic.tagAnimationType = 5;
        }
    }
    return;
tagFound:
    if (g_Runners[g_FieldingLogic.runnerBeingTargettedForOut].actionCode != 0) {
        if (g_Runners[g_FieldingLogic.runnerBeingTargettedForOut].runningDirectionCode == 1) {
            g_FieldingLogic.tagDirection.x =
                base_MoundCoordinates[g_Runners[g_FieldingLogic.runnerBeingTargettedForOut].currentBase].x;
            g_FieldingLogic.tagDirection.y = lbl_3_rodata_193C;
            g_FieldingLogic.tagDirection.z =
                base_MoundCoordinates[g_Runners[g_FieldingLogic.runnerBeingTargettedForOut].currentBase].z;
        } else {
            g_FieldingLogic.tagDirection.x =
                base_MoundCoordinates[g_Runners[g_FieldingLogic.runnerBeingTargettedForOut].nextBase].x;
            g_FieldingLogic.tagDirection.y = lbl_3_rodata_193C;
            g_FieldingLogic.tagDirection.z =
                base_MoundCoordinates[g_Runners[g_FieldingLogic.runnerBeingTargettedForOut].nextBase].z;
        }
    } else {
        g_FieldingLogic.tagDirection.x = g_Runners[g_FieldingLogic.runnerBeingTargettedForOut].position.x;
        g_FieldingLogic.tagDirection.y = g_Runners[g_FieldingLogic.runnerBeingTargettedForOut].position.y;
        g_FieldingLogic.tagDirection.z = g_Runners[g_FieldingLogic.runnerBeingTargettedForOut].position.z;
    }
}

// .text:0x000A76B4 size:0x5D4 mapped:0x806E6748
void fielderHasBall(void) {
    int fielderIndex = g_Ball.fielderWBallIndex;
    InputStruct* controls = &g_Controls[g_GameLogic.teams[g_GameLogic.teamFielding]];
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    s16 tagPlay = g_FieldingLogic.somethingForTryingTagOutTargetBase;

    if (g_FieldingLogic.playOverInd != 0) {
        return;
    }
    if (g_Ball.deadBallReason != 0) {
        return;
    }
    if (g_FieldingLogic.always0_012b != 0) {
        return;
    }
    if (g_Strikes.outs >= 3) {
        return;
    }
    g_FieldingLogic.smashThrowInd = 0;
    g_FieldingLogic.throwWaitingInd = 0;
    if (g_FieldingLogic.humanSelectedPlaceToThrow >= 0) {
        s16 placeToThrow = g_FieldingLogic.humanSelectedPlaceToThrow;

        g_FieldingLogic.locationThrownTo = placeToThrow;
        g_FieldingLogic.humanSelectedPlaceToThrow = -1;
        g_FieldingLogic.someHumanThrowFrameCounter = 0;
        if (placeToThrow == 8) {
            g_FieldingLogic.throwWaitingInd = 1;
        }
    } else {
        if (ACTIVE_TUTORIAL()) {
            controls = &g_Practice.inputs[g_GameLogic.teamFielding];
        } else if (g_d_GameSettings.minigamesEnabled) {
            fielderIndex = g_Minigame.minigameRelatedIndex;
            controls = &g_Controls[g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame._1922]];
        }
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD) {
            if (!(controls->buttonInput & INPUT_BUTTON_A)) {
                g_FieldingLogic.smashThrow_framesDirectionHeld = 0;
            }
            if (g_FieldingLogic.smashThrow_framesDirectionHeld != 0) {
                if (g_FieldingLogic.smashThrow_framesDirectionHeld < 0xfe) {
                    g_FieldingLogic.smashThrow_framesDirectionHeld++;
                } else {
                    g_FieldingLogic.smashThrow_framesDirectionHeld = 0xff;
                }
            }
            if ((controls->buttonInput & INPUT_BUTTON_A) &&
                g_FieldingLogic.smashThrow_framesDirectionHeld <= specialFielderActionConstants._40[8]) {
                if (controls->newButtonInput & INPUT_BUTTON_A) {
                    if (controls->buttonInput & INPUT_TRIGGER_L) {
                        g_FieldingLogic.locationThrownTo = 6;
                    } else if (controls->controlStickAngle >= 0xe00 || (controls->buttonInput & INPUT_BUTTON_RIGHT)) {
                        g_FieldingLogic.locationThrownTo = 1;
                    } else if (controls->controlStickAngle >= 0xa00 || (controls->buttonInput & INPUT_BUTTON_DOWN)) {
                        g_FieldingLogic.locationThrownTo = 0;
                    } else if (controls->controlStickAngle >= 0x600 || (controls->buttonInput & INPUT_BUTTON_LEFT)) {
                        g_FieldingLogic.locationThrownTo = 3;
                    } else if (controls->controlStickAngle >= 0x200 || (controls->buttonInput & INPUT_BUTTON_UP)) {
                        g_FieldingLogic.locationThrownTo = 2;
                    } else if (controls->controlStickAngle >= 0 || (controls->buttonInput & INPUT_BUTTON_RIGHT)) {
                        g_FieldingLogic.locationThrownTo = 1;
                    } else {
                        g_FieldingLogic.smashThrow_framesDirectionHeld = 1;
                    }
                } else if (g_FieldingLogic.smashThrow_framesDirectionHeld >= specialFielderActionConstants._40[8]) {
                    g_FieldingLogic.throwWaitingInd = 1;
                }
                if (g_FieldingLogic.throwWaitingInd != 0) {
                    g_FieldingLogic.smash0_normalThrow1 = 1;
                } else if (g_FieldingLogic.framesControlStickPointedInCertainQuadrant <= lbl_3_data_475C &&
                           !g_d_GameSettings.minigamesEnabled && g_FieldingLogic.locationThrownTo >= 0 &&
                           g_FieldingLogic.locationThrownTo <= 3) {
                    g_FieldingLogic.smash0_normalThrow1 = 0;
                    g_FieldingLogic.smashThrowInd = 1;
                } else {
                    g_FieldingLogic.smash0_normalThrow1 = 1;
                }
                goto afterInput;
            }
        }
        if (g_FieldingLogic._0136 == 0) {
            if (controls->newButtonInput & INPUT_BUTTON_B) {
                if (controls->controlStickAngle >= 0xe00 || (controls->buttonInput & INPUT_BUTTON_RIGHT)) {
                    g_FieldingLogic.somethingForTryingTagOutTargetBase = 1;
                } else if (controls->controlStickAngle >= 0xa00 || (controls->buttonInput & INPUT_BUTTON_DOWN)) {
                    g_FieldingLogic.somethingForTryingTagOutTargetBase = 0;
                } else if (controls->controlStickAngle >= 0x600 || (controls->buttonInput & INPUT_BUTTON_LEFT)) {
                    g_FieldingLogic.somethingForTryingTagOutTargetBase = 3;
                } else if (controls->controlStickAngle >= 0x200 || (controls->buttonInput & INPUT_BUTTON_UP)) {
                    g_FieldingLogic.somethingForTryingTagOutTargetBase = 2;
                } else if (controls->controlStickAngle >= 0 || (controls->buttonInput & INPUT_BUTTON_RIGHT)) {
                    g_FieldingLogic.somethingForTryingTagOutTargetBase = 1;
                }
            }
        } else {
            fn_3_3AAF8(fielderIndex);
            moveFielder_CheckForAndSetJump(fielderIndex);
        }
    }
afterInput:
    if (g_FieldingLogic.throwWaitingInd != 0) {
        g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
        g_FieldingLogic.locationThrownTo = -1;
        fielderAIDecideWhatRunnerToTarget(fielderIndex);
    }
    if ((g_FieldingLogic.locationThrownTo >= 0 && g_FieldingLogic.locationThrownTo <= 3) ||
        g_FieldingLogic.locationThrownTo == 5 || g_FieldingLogic.locationThrownTo == 6) {
        g_FieldingLogic.smashThrow_framesDirectionHeld = 0;
    } else {
        g_FieldingLogic.locationThrownTo = -1;
    }
    if (g_FieldingLogic.locationThrownTo >= 0 && g_FieldingLogic.locationThrownTo <= 3 &&
        fielder->distanceToBases[g_FieldingLogic.locationThrownTo] <= lbl_3_rodata_199C) {
        g_FieldingLogic.somethingForTryingTagOutTargetBase = g_FieldingLogic.locationThrownTo;
        g_FieldingLogic.locationThrownTo = -1;
    }
    if (g_FieldingLogic.locationThrownTo == 6 && g_FieldingLogic.cutoffFielderIndex < 0) {
        g_FieldingLogic.locationThrownTo = -1;
    }
    if (g_FieldingLogic.someCountDown != 0 && g_FieldingLogic.somethingForTryingTagOutTargetBase >= 0) {
        g_FieldingLogic.somethingForTryingTagOutTargetBase = tagPlay;
    }
    if (tagPlay != g_FieldingLogic.somethingForTryingTagOutTargetBase &&
        g_FieldingLogic.somethingForTryingTagOutTargetBase >= 0) {
        g_FieldingLogic.someBase = -1;
        g_FieldingLogic.runnerChasingAfter = -1;
        g_FieldingLogic.fielderAssignedLocationIndex[6] = g_Ball.baseBallAndFielderAreOn;
        fielder->framesSinceStartedMoving = 0;
        g_FieldingLogic.someCountDown = 30;
    }
    if (g_FieldingLogic._010d != 0) {
        if (g_Ball.timeSinceBallPickedUp >= 0 && g_Ball.timeSinceBallPickedUp < 40) {
            if (g_FieldingLogic.locationThrownTo >= 0) {
                g_FieldingLogic._010c = 1;
                g_FieldingLogic._010d = 0;
            }
        } else {
            g_FieldingLogic._010d = 0;
        }
    }
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
void fielderChasingAI(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];

    if (g_FieldingLogic.somethingForTryingTagOutTargetBase >= 0 && g_FieldingLogic.somethingForTryingTagOutTargetBase <= 3 &&
        fielder->baseCurrentlyOn == g_FieldingLogic.somethingForTryingTagOutTargetBase) {
        g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
    } else {
        if (g_FieldingLogic.someBase == -1) {
            if (g_FieldingLogic.runnerChasingAfter >= 0 &&
                g_Runners[g_FieldingLogic.runnerChasingAfter].runnerOnFieldOrOutOrScored != RUNNER_STATUS_ON_FIELD) {
                g_FieldingLogic.runnerChasingAfter = -1;
                g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
                return;
            }
            g_FieldingLogic.someBase = g_FieldingLogic.somethingForTryingTagOutTargetBase;
            setRunnerChasingAfter(fielderIndex);
        }
        if (g_FieldingLogic.somethingForTryingTagOutTargetBase >= 0 && g_FieldingLogic.somethingForTryingTagOutTargetBase <= 3) {
            if (g_FieldingLogic.runnerChasingAfter == -1) {
                setFielderAutoCoords(g_Ball.fielderWBallIndex,
                                     base_MoundCoordinates[g_FieldingLogic.somethingForTryingTagOutTargetBase].x,
                                     base_MoundCoordinates[g_FieldingLogic.somethingForTryingTagOutTargetBase].z);
            } else {
                setFielderAutoCoords(g_Ball.fielderWBallIndex, g_Runners[g_FieldingLogic.runnerChasingAfter].position.x,
                                     g_Runners[g_FieldingLogic.runnerChasingAfter].position.z);
            }
        }
        fielderAIChaseRunner();
    }
}

// .text:0x000A8478 size:0x150 mapped:0x806E750C
BOOL runnerTagUpOrBatterTo1B(int* outBase, int* outFrames) {
    s16 throwLoc = g_FieldingLogic.locationThrownTo;
    int prevBase;

    if (throwLoc >= 4 || throwLoc < 0) {
        return 0;
    }
    if (g_Ball.AtBat_ContactResult != BALL_RESULT_TYPE_CAUGHT ||
        g_Runners[throwLoc].runnerOnFieldOrOutOrScored != RUNNER_STATUS_ON_FIELD ||
        g_Runners[throwLoc].tagUpInd != TAG_UP_TYPE_TAGGED) {
        prevBase = 3;
        if (throwLoc != 0) {
            prevBase = throwLoc - 1;
        }
        if (g_Runners[prevBase].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
            g_Runners[prevBase].forceOutCd == FORCE_OUT_TYPE_FORCED_TO_ADVANCE) {
            *outBase = prevBase;
            *outFrames = g_Runners[prevBase].framesToNextBase;
            return 1;
        }
        return 0;
    } else {
        InMemRunnerType* runner = &g_Runners[throwLoc];

        *outBase = throwLoc;
        if (runner->currentBase == throwLoc) {
            u8 dir = runner->runningDirectionCode;

            if (dir == 3 || dir == 2) {
                *outFrames = runner->framesToPreviousBase;
            } else if ((dir == 1 && runner->nextDirectionBeingProcessed == 3) ||
                       (dir == 3 && runner->nextDirectionBeingProcessed == 1)) {
                *outFrames = runner->framesToPreviousBase + 20;
            } else {
                *outFrames = runner->framesToPreviousBase + 50;
            }
        } else {
            *outFrames = runner->framesToNextBase + runner->framesToPreviousBase + runner->framesToPreviousBase;
        }
        return 1;
    }
}

// .text:0x000A85C8 size:0x40C mapped:0x806E765C
void maybeUnused_SetThrowSpeedType2(f32 dist) {
    InMemFielder* fielder;
    int i;
    int runnersOnField;
    int outBase;
    int outFrames;
    f32 speed;
    f32 dx;
    f32 dz;
    f32 sqx;
    f32 sqz;
    f32 throwDist;
    int diff;
    int frames;

    runnersOnField = 0;
    for (i = 0; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
            runnersOnField++;
        }
    }
    if (runnerTagUpOrBatterTo1B(&outBase, &outFrames) == 0) {
        if (dist < lbl_3_rodata_1A0C) {
            g_FieldingLogic.throwSpeedType = 7;
        } else if (dist < lbl_3_rodata_1A38 && g_FieldingLogic.throwSpeedType < 5) {
            g_FieldingLogic.throwSpeedType = 5;
        }
    } else {
        fielder = &g_Fielders[g_Ball.fielderWBallIndex];
        speed = fielder->modifiedThrowingArm / lbl_3_rodata_1938;
        dx = g_Ball.throwDestination.x - fielder->pos.x;
        dz = g_Ball.throwDestination.z - fielder->pos.z;
        sqx = dx * dx;
        sqz = dz * dz;
        throwDist = dolsqrtf2(sqx + sqz);
        if (lbl_3_rodata_193C == speed) {
            speed = lbl_3_rodata_1958;
        }
        if (throwDist > lbl_3_rodata_195C) {
            frames = lbl_3_rodata_1960 * throwDist / speed;
        } else if (throwDist > lbl_3_rodata_1964) {
            frames = throwDist / speed;
        } else {
            frames = lbl_3_rodata_1968 * throwDist / speed;
        }
        if (throwDist > lbl_3_rodata_196C) {
            frames = (int)(frames * lbl_3_rodata_1970) + 0x1e;
        } else if (throwDist > lbl_3_rodata_1974) {
            frames = (int)(frames * lbl_3_rodata_1960) + 0x1e;
        }
        diff = frames + 0x14 - outFrames;
        if ((g_Strikes.outs >= 2 || runnersOnField == 1) && diff < -0x1e && g_Ball.numberOfThrowsDuringPlay <= 1) {
            g_FieldingLogic.throwSpeedType = 4;
            if (dist > lbl_3_rodata_1964) {
                g_FieldingLogic.throwSpeedType = 3;
            } else if (dist < lbl_3_rodata_1A40) {
                g_FieldingLogic.throwSpeedType = 6;
            }
            g_FieldingLogic.someThrowSpeedIncreaseInd = 1;
        }
    }
}

// .text:0x000A89D4 size:0x980 mapped:0x806E7A68
void fn_3_A89D4(void) {
    InMemFielder* fielder;
    InMemRunnerType* runner;
    int outFrames;
    int outBase;
    u32 zone;
    int contact;
    int i;
    int runnersOnField;
    f32 dist;
    f32 dx;
    f32 dz;
    f32 sqx;
    f32 sqz;
    f32 dist2;

    fielder = &g_Fielders[g_Ball.fielderWBallIndex];
    dx = fielder->pos.x - g_Ball.throwDestination.x;
    dz = fielder->pos.z - g_Ball.throwDestination.z;
    g_FieldingLogic.throwSpeedType = 3;
    g_FieldingLogic.birdoFarThrowInd_forAnimation = 0;
    g_FieldingLogic.someThrowSpeedIncreaseInd = 0;
    g_FieldingLogic.throwWindUpFrameCounter = 0;
    sqx = dx * dx;
    sqz = dz * dz;
    dist = dolsqrtf2(sqx + sqz);
    if (g_FieldingLogic.setThrowSpeedTypeTo9Ind != 0) {
        g_FieldingLogic.throwSpeedType = 9;
        return;
    }
    if (g_Runners[1].runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE && g_Runners[1].actionCode != 0 &&
        g_Runners[1].fractionalBasesRan >= lbl_3_rodata_1A3C && g_Runners[1].fractionalBasesRan <= lbl_3_rodata_1A14 &&
        g_FieldingLogic.locationThrownTo == 1 && g_Ball.baseBallAndFielderAreOn == 2) {
        g_FieldingLogic.throwSpeedType = 10;
        return;
    }
    if (dist > lbl_3_rodata_19E8 || (g_Ball.ballZoneAwayFromHome >= 3 && dist > lbl_3_rodata_19B8)) {
        g_FieldingLogic.birdoFarThrowInd_forAnimation = 1;
    }
    if (g_FieldingLogic.locationThrownTo >= 0 && g_FieldingLogic.locationThrownTo <= 3) {
        if (fielder->always0_ == 1 && g_Ball.timeSinceBallPickedUp < 0x2d) {
            dx = lbl_3_rodata_1A14 * fielder->xMovementDir + fielder->pos.x - g_Ball.throwDestination.x;
            dz = lbl_3_rodata_1A14 * fielder->zMovementDir + fielder->pos.z - g_Ball.throwDestination.z;
            sqx = dx * dx;
            sqz = dz * dz;
            dist2 = dolsqrtf2(sqx + sqz);
            if (dist2 < lbl_3_rodata_1A20) {
                g_FieldingLogic.throwSpeedType = 8;
                return;
            }
        } else {
            if (dist < lbl_3_rodata_1A44) {
                g_FieldingLogic.throwSpeedType = 8;
                return;
            }
            if (dist < lbl_3_rodata_1A48 &&
                g_Fielders[g_FieldingLogic.fielderAssignedLocationIndex[g_FieldingLogic.locationThrownTo]]
                        .numFramesToGetToAutoLocation > 0x1e) {
                g_FieldingLogic.throwSpeedType = 8;
                return;
            }
        }
    }
    zone = g_Ball.ballZoneAwayFromHome;
    if (zone <= 2) {
        runner = g_Runners;
        i = 0;
        do {
            if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
                (runner->forceOutCd == FORCE_OUT_TYPE_FORCED_TO_ADVANCE || runner->tagUpInd == TAG_UP_TYPE_TAGGED ||
                 runner->overrunBaseStage >= 3 ||
                 (runner->percentTowardsNextBase <= lbl_3_rodata_19BC && runner->runningDirectionCode == 1) ||
                 (runner->percentTowardsNextBase >= lbl_3_rodata_19BC &&
                  runner->percentTowardsNextBase <= lbl_3_rodata_1968))) {
                break;
            }
            runner++;
            i++;
        } while (i < 4);
        if (i >= 4) {
            if (dist < lbl_3_rodata_1A0C) {
                g_FieldingLogic.throwSpeedType = 7;
            } else {
                g_FieldingLogic.throwSpeedType = 5;
            }
            return;
        }
    }
    contact = g_Ball.AtBat_ContactResult;
    if (contact == BALL_RESULT_TYPE_FOUL) {
        if (dist > lbl_3_rodata_1964) {
            g_FieldingLogic.throwSpeedType = 4;
        } else {
            g_FieldingLogic.throwSpeedType = 5;
        }
        return;
    }
    if (dist < lbl_3_rodata_19F0 && g_FieldingLogic.throwSpeedType < 5) {
        g_FieldingLogic.throwSpeedType = 5;
        return;
    }
    if (zone >= 3) {
        if (contact != BALL_RESULT_TYPE_CAUGHT && g_Runners[0].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD &&
            g_Runners[0].fractionalBasesRan < lbl_3_rodata_1958 && g_FieldingLogic.locationThrownTo == 1) {
            g_FieldingLogic.throwSpeedType = 3;
        }
        return;
    }
    runnersOnField = 0;
    for (i = 0; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
            runnersOnField++;
        }
    }
    if (runnerTagUpOrBatterTo1B(&outBase, &outFrames) == 0) {
        if (dist < lbl_3_rodata_1A0C) {
            g_FieldingLogic.throwSpeedType = 7;
        } else if (dist < lbl_3_rodata_1A38 && g_FieldingLogic.throwSpeedType < 5) {
            g_FieldingLogic.throwSpeedType = 5;
        }
    } else {
        f32 speed;
        f32 dx;
        f32 dz;
        f32 sqx;
        f32 sqz;
        f32 dist2;
        int frames;
        int diff;

        fielder = &g_Fielders[g_Ball.fielderWBallIndex];
        speed = fielder->modifiedThrowingArm / lbl_3_rodata_1938;
        dx = g_Ball.throwDestination.x - fielder->pos.x;
        dz = g_Ball.throwDestination.z - fielder->pos.z;
        sqx = dx * dx;
        sqz = dz * dz;
        dist2 = dolsqrtf2(sqx + sqz);
        if (lbl_3_rodata_193C == speed) {
            speed = lbl_3_rodata_1958;
        }
        if (dist2 > lbl_3_rodata_195C) {
            frames = lbl_3_rodata_1960 * dist2 / speed;
        } else if (dist2 > lbl_3_rodata_1964) {
            frames = dist2 / speed;
        } else {
            frames = lbl_3_rodata_1968 * dist2 / speed;
        }
        if (dist2 > lbl_3_rodata_196C) {
            frames = (int)(frames * lbl_3_rodata_1970) + 0x1e;
        } else if (dist2 > lbl_3_rodata_1974) {
            frames = (int)(frames * lbl_3_rodata_1960) + 0x1e;
        }
        diff = frames + 0x14 - outFrames;
        if ((g_Strikes.outs >= 2 || runnersOnField == 1) && diff < -0x1e && g_Ball.numberOfThrowsDuringPlay <= 1) {
            g_FieldingLogic.throwSpeedType = 4;
            if (dist > lbl_3_rodata_1964) {
                g_FieldingLogic.throwSpeedType = 3;
            } else if (dist < lbl_3_rodata_1A40) {
                g_FieldingLogic.throwSpeedType = 6;
            }
            g_FieldingLogic.someThrowSpeedIncreaseInd = 1;
        }
    }
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
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    InMemRunnerType* runner = &g_Runners[fielder->bodyCheckRunnerNumber];
    u8 status = fielder->bodyCheckStatus;
    s16 charID;
    f32 compX;
    f32 compZ;
    s16 loc;

    if (status == 0) {
        fielder->bodyCheckStatus = 1;
        g_FieldingLogic.bodyCheckStageCountdown = runner->actionFrames_countDown - 1;
    } else if (status == 1) {
        g_FieldingLogic.bodyCheckStageCountdown--;
        if (g_FieldingLogic.bodyCheckStageCountdown <= 0) {
            if (fielder->bodyCheckResult == 1) {
                fielder->bodyCheckStatus = 2;
                g_FieldingLogic.bodyCheckStageCountdown = lbl_3_data_4880;
            } else {
                fielder->bodyCheckStatus = 3;
                charID = fielder->CharID;
                fielder->knockOutVelo = lbl_3_data_4878[0];
                g_FieldingLogic.bodyCheckStageCountdown = bodyCheckFrameRelatedConstants[charID][2];
                fielder->knockOutAngle = bodyCheckBallAngles[(s8)fielder->baseOn2]._4;
            }
        }
    } else {
        g_FieldingLogic.bodyCheckStageCountdown--;
        charID = fielder->CharID;
        if (bodyCheckFrameRelatedConstants[charID][2] - bodyCheckFrameRelatedConstants[charID][3] ==
                g_FieldingLogic.bodyCheckStageCountdown &&
            status == 3) {
            knockBallLoose(fielderIndex, 0);
            g_FieldingLogic.knockoutFinished = 1;
            g_FieldingLogic.tagAnimationType = 0;
        }
        if (fielder->bodyCheckStatus == 3) {
            getComponentsFromSAng(fielder->knockOutAngle, &compX, &compZ);
            fielder->knockOutVelo = fielder->knockOutVelo * lbl_3_data_4878[1];
            fielder->velocityX = compX * fielder->knockOutVelo;
            fielder->velocityZ = compZ * fielder->knockOutVelo;
            fielder->currentVelocity = fielder->knockOutVelo;
            fielder->pos.x = fielder->pos.x + fielder->velocityX;
            fielder->pos.z = fielder->pos.z + fielder->velocityZ;
        }
        if (g_FieldingLogic.bodyCheckStageCountdown <= 0) {
            if (fielder->bodyCheckStatus == 3) {
                ifCurrentFielderIsTakingOverBaseCovering(fielderIndex, 9);
                loc = fielder->locationResponsibleForCovering;
                fielder->locationResponsibleForCovering = -1;
                g_FieldingLogic.fielderAssignedLocationIndex[loc] = -1;
                g_FieldingLogic.baseCoveredInd[loc] = 0;
                fielder->isResponsibleForCoveringALocation = 0;
                if (g_Ball.fielderWBallIndex == -1) {
                    g_FieldingLogic.knockoutFinished = 1;
                }
            }
            fielder->bodyCheckStatus = 0;
            fielder->bodyCheckResult = 0;
        }
    }
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
void autoMovement10_HasBall(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    BOOL tagOutRelated = FALSE;
    int i;

    if (g_FieldingLogic.someCountDown != 0) {
        g_FieldingLogic.someCountDown--;
    }
    if (fielder->onFire != 0) {
        if (g_Ball.fielderWBallIndex == fielderIndex) {
            knockBallLoose(fielderIndex, 2);
            g_FieldingLogic.knockoutFinished = 1;
            g_FieldingLogic.tagAnimationType = 0;
            return;
        }
        fielderOnFirePosAndVelo(fielderIndex);
        return;
    }
    if (fielder->knockoutStatus != 0) {
        knockOut_setPosAndVelo(fielderIndex);
        fielder->hitKnockbackCountdown = 0;
        return;
    }
    if (fielder->bodyCheckResult != 0) {
        fielderBodyCheck_setStatus_Pos_Velo(fielderIndex);
    } else if (fielder->hitKnockbackCountdown != 0) {
        fielderKnockback(fielderIndex);
    } else if (fielder->stunFramesOnFireBall != 0) {
    } else if (fielder->isJump != 0) {
        jumpSetPosAndVelo(fielderIndex);
    } else {
        if (fielder->runningCatchCountDown != 0) {
            runningCatch_updatePositionAndVelocity(fielderIndex);
            goto humanInput;
        }
        if (fielder->jumpDiveStateRelated == 2 && fielder->animatingActionInd != 0) {
            goto humanInput;
        }
        if (fielder->wallJumpStatus != 0) {
            if (fielder->wallJumpStatus >= 3) {
                walljump_calculateJumpedOffWallPositionAndVelocity(fielderIndex);
            }
        } else if (fielder->clamberStatus != 0) {
            if (fielder->clamberStatus < 5) {
                fielder->clamberStatus = 5;
            }
            clamberJumpOffWall(fielderIndex);
        } else if (fielder->animationRelatedInd != 0 &&
                   (g_FieldingLogic.quickThrowInd == 0 ||
                    (g_Ball.timeSinceBallPickedUp > 0 && g_Ball.timeSinceBallPickedUp < 15))) {
        humanInput:
            checkForBufferedThrow();
            tagOutRelated = TRUE;
            g_FieldingLogic.someHumanThrowFrameCounter = 0;
        } else {
            if (g_FieldingLogic.tagAnimationType != 0) {
                tagRelated(fielderIndex);
                return;
            }
            if (fielder->fielderMadeThrow != 0) {
                if (fielder->framesSinceThrowWasMade < 0x7ffe) {
                    fielder->framesSinceThrowWasMade++;
                } else {
                    fielder->framesSinceThrowWasMade = 0x7fff;
                }
                if (fielder->framesSinceThrowWasMade < fielder->const_60) {
                    if (g_Ball.ballState == BALL_STATE_HELD) {
                        fielder->framesSinceThrowWasMade = fielder->const_60;
                    }
                    return;
                }
                if (fielder->isResponsibleForCoveringALocation == 1) {
                    s16* assigned = g_FieldingLogic.fielderAssignedLocationIndex;
                    s16 currentAssigned = assigned[fielder->locationResponsibleForCovering];

                    if (currentAssigned != fielderIndex && currentAssigned >= 0) {
                        ifCurrentFielderIsTakingOverBaseCovering(currentAssigned, 9);
                    }
                    ifCurrentFielderIsTakingOverBaseCovering(fielderIndex, 1);
                    assigned[fielder->locationResponsibleForCovering] = fielderIndex;
                } else {
                    ifCurrentFielderIsTakingOverBaseCovering(fielderIndex, 9);
                }
                fielder->framesSinceThrowWasMade = 0;
                fielder->fielderMadeThrow = 0;
                return;
            }
            hexBaserunnerTracker = 0;
            {
                InMemRunnerType* runner = &g_Runners[3];

                originalBaseOfRunnerInThisBaseline[0] = -1;
                originalBaseOfRunnerInThisBaseline[1] = -1;
                originalBaseOfRunnerInThisBaseline[2] = -1;
                originalBaseOfRunnerInThisBaseline[3] = -1;
                for (i = 3; i >= 0; runner--, i--) {
                    if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
                        hexBaserunnerTracker |= 1 << ((int)runner->fractionalBasesRan << 2);
                        if (originalBaseOfRunnerInThisBaseline[runner->currentBase] < 0 ||
                            g_Runners[originalBaseOfRunnerInThisBaseline[runner->currentBase]].baseStandingOn >= 0) {
                            originalBaseOfRunnerInThisBaseline[runner->currentBase] = i;
                        }
                    }
                }
            }
            if (g_FieldingLogic.locationThrownTo < 0) {
                if (fielder->autoFielderInd != 0) {
                    fielderAIDecideWhatRunnerToTarget(fielderIndex);
                } else if (g_FieldingLogic.bodyCheckResult == 0) {
                    fielderHasBall();
                    if (g_FieldingLogic.somethingForTryingTagOutTargetBase >= 0) {
                        if (g_FieldingLogic.somethingForTryingTagOutTargetBase >= 0 &&
                            g_FieldingLogic.somethingForTryingTagOutTargetBase <= 3 &&
                            fielder->baseCurrentlyOn == g_FieldingLogic.somethingForTryingTagOutTargetBase) {
                            g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
                        } else {
                            if (g_FieldingLogic.someBase == -1) {
                                if (g_FieldingLogic.runnerChasingAfter >= 0 &&
                                    g_Runners[g_FieldingLogic.runnerChasingAfter].runnerOnFieldOrOutOrScored !=
                                        RUNNER_STATUS_ON_FIELD) {
                                    g_FieldingLogic.runnerChasingAfter = -1;
                                    g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
                                    goto afterChase;
                                }
                                g_FieldingLogic.someBase = g_FieldingLogic.somethingForTryingTagOutTargetBase;
                                setRunnerChasingAfter(fielderIndex);
                            }
                            if (g_FieldingLogic.somethingForTryingTagOutTargetBase >= 0 &&
                                g_FieldingLogic.somethingForTryingTagOutTargetBase <= 3) {
                                if (g_FieldingLogic.runnerChasingAfter == -1) {
                                    setFielderAutoCoords(
                                        g_Ball.fielderWBallIndex,
                                        base_MoundCoordinates[g_FieldingLogic.somethingForTryingTagOutTargetBase].x,
                                        base_MoundCoordinates[g_FieldingLogic.somethingForTryingTagOutTargetBase].z);
                                } else {
                                    setFielderAutoCoords(g_Ball.fielderWBallIndex,
                                                         g_Runners[g_FieldingLogic.runnerChasingAfter].position.x,
                                                         g_Runners[g_FieldingLogic.runnerChasingAfter].position.z);
                                }
                            }
                            fielderAIChaseRunner();
                        }
                    } else {
                        g_FieldingLogic.someBase = -1;
                    }
                }
            afterChase:
                {
                    f32 vx = fielder->velocityX;
                    f32 vz = fielder->velocityZ;
                    f32 sqx = vx * vx;
                    f32 sqz = vz * vz;

                    fielder->currentVelocity = dolsqrtf2(sqx + sqz);
                }
                if (g_FieldingLogic.locationThrownTo == fielder->locationResponsibleForCovering &&
                    g_FieldingLogic.fielderAssignedLocationIndex[fielder->locationResponsibleForCovering] ==
                        fielderIndex) {
                    g_FieldingLogic.locationThrownTo = -1;
                }
                if (g_FieldingLogic.locationThrownTo >= 0 && g_FieldingLogic.locationThrownTo <= 3) {
                    g_Ball.throwDestination.x = base_MoundCoordinates[g_FieldingLogic.locationThrownTo].x;
                    fielder->throwTarget.x = g_Ball.throwDestination.x;
                    fielder->throwTarget.y = lbl_3_rodata_193C;
                    g_Ball.throwDestination.y = lbl_3_rodata_193C;
                    g_Ball.throwDestination.z = base_MoundCoordinates[g_FieldingLogic.locationThrownTo].z;
                    fielder->throwTarget.z = g_Ball.throwDestination.z;
                } else if (g_FieldingLogic.locationThrownTo == 6) {
                    int cutoff = g_FieldingLogic.cutoffFielderIndex;

                    if (cutoff != fielderIndex) {
                        g_Ball.throwDestination.x = g_Fielders[cutoff].pos.x;
                        fielder->throwTarget.x = g_Ball.throwDestination.x;
                        fielder->throwTarget.y = lbl_3_rodata_193C;
                        g_Ball.throwDestination.y = lbl_3_rodata_193C;
                        g_Ball.throwDestination.z = g_Fielders[cutoff].pos.z;
                        fielder->throwTarget.z = g_Ball.throwDestination.z;
                    } else {
                        g_FieldingLogic.locationThrownTo = -1;
                    }
                } else if (g_FieldingLogic.locationThrownTo == 5) {
                    BOOL pitcherCutoffPossible;
                    s16 mound = g_FieldingLogic.fielderAssignedLocationIndex[4];

                    if (mound == -1) {
                        pitcherCutoffPossible = 0;
                    } else if (g_FieldingLogic.playerAtMoundCutoffLocation != 1) {
                        pitcherCutoffPossible = 0;
                    } else if (g_Fielders[mound].locationResponsibleForCovering != 5) {
                        pitcherCutoffPossible = 0;
                    } else if (g_Fielders[g_Ball.fielderWBallIndex].distanceToMound < lbl_3_rodata_19F0) {
                        pitcherCutoffPossible = 0;
                    } else {
                        pitcherCutoffPossible = 1;
                    }
                    if (pitcherCutoffPossible) {
                        f32 moundX = base_MoundCoordinates[4].x;
                        f32 moundZ = base_MoundCoordinates[4].z;

                        fielder->throwTarget.x = moundX;
                        fielder->throwTarget.y = lbl_3_rodata_193C;
                        g_Ball.throwDestination.x = moundX;
                        g_Ball.throwDestination.y = lbl_3_rodata_193C;
                        g_Ball.throwDestination.z = moundZ;
                        fielder->throwTarget.z = moundZ;
                    } else {
                        g_FieldingLogic.locationThrownTo = -1;
                    }
                }
                g_FieldingLogic.setThrowSpeedTypeTo9Ind = 0;
                fn_3_AAA3C(fielderIndex);
                if (g_FieldingLogic.locationThrownTo >= 0) {
                    g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
                    fn_3_A89D4();
                    initialize_runnersBeingTargetedWhileBatterCanBeForcedOut();
                }
                setFielder215(fielderIndex);
            } else {
                if (fielder->throwWindUpFrames != 0) {
                    fielder->throwWindUpFrames--;
                    return;
                }
                {
                    f32 vx = fielder->velocityX;
                    f32 vz = fielder->velocityZ;
                    f32 sqx = vx * vx;
                    f32 sqz = vz * vz;

                    fielder->currentVelocity = dolsqrtf2(sqx + sqz);
                }
                if (g_FieldingLogic.locationThrownTo >= 0 && g_FieldingLogic.locationThrownTo <= 3) {
                    g_Ball.throwDestination.x = base_MoundCoordinates[g_FieldingLogic.locationThrownTo].x;
                    fielder->throwTarget.x = g_Ball.throwDestination.x;
                    fielder->throwTarget.y = lbl_3_rodata_193C;
                    g_Ball.throwDestination.y = lbl_3_rodata_193C;
                    g_Ball.throwDestination.z = base_MoundCoordinates[g_FieldingLogic.locationThrownTo].z;
                    fielder->throwTarget.z = g_Ball.throwDestination.z;
                }
                g_FieldingLogic.throwWindUpFrameCounter++;
                if (g_FieldingLogic.throwWindupAnimationDoneInd == 0) {
                    return;
                }
                makeThrowVariables(fielderIndex);
                fielder->fielderMadeThrow = 1;
                g_FieldingLogic.throwWindupAnimationDoneInd = 0;
                fielder->framesSinceThrowWasMade = 0;
                g_FieldingLogic.tagAnimationType = 0;
                g_FieldingLogic.tagResult_1out_2safe = 0;
            }
        }
        if (g_Ball.fielderWBallIndex == fielderIndex && g_FieldingLogic.locationThrownTo < 0 && !tagOutRelated) {
            tagOutValues(fielderIndex);
        }
    }
    setStandingOnBaseVariables(fielderIndex);
    g_Ball.baseBallAndFielderAreOn = -1;
    if (g_Ball.fielderWBallIndex >= 0 && fielder->baseCurrentlyOn >= 0) {
        g_Ball.baseBallAndFielderAreOn = fielder->baseCurrentlyOn;
        if (g_FieldingLogic.somethingForTryingTagOutTargetBase == fielder->baseCurrentlyOn) {
            g_FieldingLogic.somethingForTryingTagOutTargetBase = -1;
        }
    }
    if (fielder->fielderMadeThrow != 0) {
        if (fielder->framesSinceThrowWasMade < 0x7ffe) {
            fielder->framesSinceThrowWasMade++;
        } else {
            fielder->framesSinceThrowWasMade = 0x7fff;
        }
        if (fielder->framesSinceThrowWasMade < fielder->const_60) {
            if (g_Ball.ballState == BALL_STATE_HELD) {
                fielder->framesSinceThrowWasMade = fielder->const_60;
            }
        } else {
            ifCurrentFielderIsTakingOverBaseCovering(fielderIndex, 0xf);
            fielder->framesSinceThrowWasMade = 0;
            fielder->fielderMadeThrow = 0;
        }
    }
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
void fn_3_AAC84(f32* outX, f32* outZ) {
    int receiverIdx = g_FieldingLogic.fielderAssignedLocationIndex[4];
    InMemFielder* thrower;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 speed;
    int frames;
    int lead;

    if (receiverIdx < 0) {
        *outX = base_MoundCoordinates[4].x;
        *outZ = base_MoundCoordinates[4].z;
        g_Ball.ballIsLooseInd_unused = 1;
        g_Ball.fielderBeingThrownTo = -1;
        return;
    }
    thrower = &g_Fielders[g_Ball.fielderWBallIndex];
    speed = thrower->modifiedThrowingArm / lbl_3_rodata_1938;
    dx = g_Fielders[receiverIdx].pos.x - thrower->pos.x;
    dz = g_Fielders[receiverIdx].pos.z - thrower->pos.z;
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
    lead = frames - 10;
    if (g_Fielders[receiverIdx].numFramesToGetToAutoLocation < lead) {
        *outX = g_Fielders[receiverIdx].IntendedLocation.x;
        *outZ = g_Fielders[receiverIdx].IntendedLocation.z;
    } else {
        *outX = lead * g_Fielders[receiverIdx].velocityX + g_Fielders[receiverIdx].pos.x;
        *outZ = lead * g_Fielders[receiverIdx].velocityZ + g_Fielders[receiverIdx].pos.z;
    }
    g_Ball.fielderBeingThrownTo = receiverIdx;
}

// .text:0x000AAFF0 size:0x564 mapped:0x806EA084
void setCutoffThrowTargetLocation(f32* targetX, f32* targetZ) {
    InMemFielder* thrower = &g_Fielders[g_Ball.fielderWBallIndex];
    InMemFielder* cutoff = &g_Fielders[g_FieldingLogic.cutoffFielderIndex];
    f32 speed;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 len;
    f32 stepX;
    f32 stepZ;
    f32 jog;
    int frames;

    speed = thrower->modifiedThrowingArm / lbl_3_rodata_1938;
    dx = cutoff->pos.x - thrower->pos.x;
    dz = cutoff->pos.z - thrower->pos.z;
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
    if (cutoff->numFramesToGetToAutoLocation < frames - 5) {
        *targetX = cutoff->IntendedLocation.x;
        *targetZ = cutoff->IntendedLocation.z;
    } else {
        stepZ = cutoff->IntendedLocation.z - cutoff->pos.z;
        stepX = cutoff->IntendedLocation.x - cutoff->pos.x;
        len = dolsqrtf2(stepX * stepX + stepZ * stepZ);
        if (lbl_3_rodata_193C == len) {
            len = lbl_3_rodata_1958;
        } else {
            len = dolsqrtf2(stepX * stepX + stepZ * stepZ);
        }
        if (len <= lbl_3_rodata_1980) {
            len = lbl_3_rodata_1980;
        }
        stepX = stepX / len;
        stepZ = stepZ / len;
        jog = lbl_3_rodata_1A58 * cutoff->joggingSpeed;
        *targetX = stepX * jog * (frames - 10) + cutoff->pos.x;
        *targetZ = stepZ * jog * (frames - 10) + cutoff->pos.z;
    }
    g_Ball.fielderBeingThrownTo = g_FieldingLogic.cutoffFielderIndex;
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
void initializeThrowAngle_Speed_Length(int framesForFielderToGetToLoc, f32* throwAngle, f32* throwSpeed) {
    f32 speed = *throwSpeed;
    f32 airFactor;
    f32 pastReceiver;
    f32 reduceGravity;
    f32 destY;
    f32 receiverY;
    f32 targetDist;
    f32 angle;
    f32 bestAngle;
    f32 lastAngle;
    f32 angleDelta;
    f32 groundY;
    f32 groundSpeed;
    f32 ySpeed;
    f32 yPos;
    f32 actualDist;
    f32 dx;
    f32 dz;
    f32 gravity;
    int laserAbility;
    int frames;
    int slowdowns;
    int loopCounter;
    int yType;
    int prevYType;

    g_FieldingLogic.laser_2 = 0;
    pastReceiver = lbl_3_rodata_1A5C;
    yType = 0;
    reduceGravity = lbl_3_rodata_193C;
    airFactor = lbl_3_rodata_1958 - (f32)g_Ball.airResistance / lbl_3_rodata_1A60;
    prevYType = 0;
    destY = lbl_3_rodata_19A0;
    laserAbility = checkFieldingStat(g_GameLogic.teamFielding, g_Fielders[g_Ball.fielderWBallIndex].rosterLocation,
                                     FIELDING_ABILITY_LASER);
    if (laserAbility != 0) {
        if (g_FieldingLogic.locationThrownTo == 0) {
            if (g_RunningLogic._04 & 0x1000) {
                g_FieldingLogic.laser_1 = 1;
                g_FieldingLogic.laser_2 = 1;
                playSoundEffect(0x1a8);
            }
        } else if (g_FieldingLogic.locationThrownTo == 0 && (g_RunningLogic._04 & 0x1100)) {
            g_FieldingLogic.laser_1 = 1;
            g_FieldingLogic.laser_2 = 1;
            playSoundEffect(0x1a8);
        }
    }
    receiverY = g_Fielders[g_FieldingLogic.fielderAssignedLocationIndex[g_FieldingLogic.locationThrownTo]].hitbox[3] -
                lbl_3_rodata_19A0;
    if (lbl_3_rodata_19A0 < lbl_3_rodata_19B0 * receiverY) {
        destY = lbl_3_rodata_19B0 * receiverY;
    }
    dx = g_Ball.throwTarget.x - g_Ball.AtBat_Contact_BallPos.x;
    dz = g_Ball.throwTarget.z - g_Ball.AtBat_Contact_BallPos.z;
    dx = dx * dx;
    dz = dz * dz;
    targetDist = dolsqrtf2(dx + dz);
    angle = lbl_3_rodata_193C;
    bestAngle = angle;
    angleDelta = lbl_3_rodata_1A64;
    if (g_FieldingLogic.throwSpeedType <= 6) {
        if (g_FieldingLogic.smash0_normalThrow1 == 0) {
            if (g_FieldingLogic.throwSpeedType != 0) {
                g_FieldingLogic.throwSpeedType--;
            }
        } else if (g_FieldingLogic.smash0_normalThrow1 == 2 && g_FieldingLogic.throwSpeedType < 6) {
            g_FieldingLogic.throwSpeedType++;
        }
    }
    switch (g_FieldingLogic.throwSpeedType) {
    case 0:
        speed = speed * lbl_3_rodata_1970;
        break;
    case 1:
        speed = speed * lbl_3_rodata_19EC;
        break;
    case 2:
        speed = speed * lbl_3_rodata_1A34;
        break;
    case 4:
        speed = speed * lbl_3_rodata_1A58;
        break;
    case 5:
        speed = speed * lbl_3_rodata_1968;
        break;
    case 6:
        speed = speed * lbl_3_rodata_1990;
        break;
    case 7:
        speed = lbl_3_rodata_197C;
        if (targetDist < lbl_3_rodata_19F0) {
            speed = lbl_3_rodata_19B4;
        } else if (targetDist < lbl_3_rodata_1A0C) {
            speed = lbl_3_rodata_1A68;
        }
        break;
    case 8:
        angle = lbl_3_rodata_1A24;
        speed = lbl_3_rodata_19AC;
        bestAngle = angle;
        break;
    case 9:
        speed = lbl_3_rodata_1A6C;
        break;
    case 10:
        break;
    }
    if (g_FieldingLogic.smashThrowInd != 0) {
        reduceGravity = lbl_3_data_4760[0];
        if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd == 2 && g_Ball.fielderWBallIndex == 1 &&
            g_Ball.framesSinceHit <= 130) {
            speed = speed * lbl_3_data_4760[1];
        }
    }
    if (g_FieldingLogic.laser_1 != 0) {
        speed = speed * lbl_3_data_4760[2];
    }
    loopCounter = 0;
    groundY = lbl_3_rodata_193C;
    slowdowns = 0;
    do {
        groundSpeed = speed * (f32)cos(angle);
        ySpeed = speed * (f32)sin(angle);
        gravity = g_Ball.physicsSubstruct.gravity;
        yPos = g_Ball.AtBat_Contact_BallPos.y;
        actualDist = lbl_3_rodata_193C;
        frames = 0;
        while (frames < 900) {
            frames++;
            groundSpeed = groundSpeed * airFactor;
            actualDist = actualDist + groundSpeed;
            ySpeed = (ySpeed - gravity + reduceGravity) * airFactor;
            yPos = yPos + ySpeed;
            if (actualDist > targetDist) {
                if (yPos < destY) {
                    yType = 2;
                } else if (yPos < receiverY) {
                    yType = 3;
                } else {
                    yType = 4;
                }
                break;
            }
            if (yPos < groundY) {
                yType = 1;
                break;
            }
        }
        if (frames < framesForFielderToGetToLoc && slowdowns < 5 && yType != 1) {
            g_FieldingLogic.laser_1 = 0;
            slowdowns++;
            speed = speed * lbl_3_rodata_1A58;
            g_FieldingLogic.laser_2 = 0;
            angle = angle + angleDelta;
        } else {
            if (yType == 1) {
                if (prevYType >= 2) {
                    break;
                }
                if (actualDist - targetDist > pastReceiver) {
                    bestAngle = angle;
                    pastReceiver = actualDist - targetDist;
                    angle = angle + angleDelta;
                } else {
                    angle = lbl_3_rodata_19B0 * (bestAngle + angle);
                }
            } else if (yType == 2) {
                if (prevYType <= 1) {
                    bestAngle = angle;
                    angle = angle + angleDelta;
                    angleDelta = angleDelta * lbl_3_rodata_1A70;
                } else if (prevYType == 4) {
                    angleDelta = angleDelta * lbl_3_rodata_1A70;
                    bestAngle = angle;
                    angle = lbl_3_rodata_19B0 * (lastAngle + angle);
                } else {
                    if (!(yPos > pastReceiver)) {
                        break;
                    }
                    bestAngle = angle;
                    angle = angle + angleDelta;
                }
                pastReceiver = yPos;
            } else if (yType == 3) {
                bestAngle = angle;
                break;
            } else if (yType == 4) {
                if (prevYType <= 2) {
                    bestAngle = angle;
                    if (loopCounter == 0) {
                        angle = angle - angleDelta;
                    } else {
                        angle = lbl_3_rodata_19B0 * (lastAngle + angle);
                    }
                } else {
                    if (!(yPos < pastReceiver)) {
                        break;
                    }
                    bestAngle = angle;
                    angle = angle - angleDelta;
                    angleDelta = angleDelta * lbl_3_rodata_1A70;
                }
                pastReceiver = yPos;
            }
            lastAngle = bestAngle;
            prevYType = yType;
        }
        loopCounter++;
    } while (loopCounter < 12);
    if (yType == 1) {
        actualDist = targetDist - actualDist;
        if (actualDist > lbl_3_rodata_1A74 && actualDist < lbl_3_rodata_1A38 && g_FieldingLogic.locationThrownTo == 0 &&
            g_Ball.ballAngleFromHome > 952 && g_Ball.ballAngleFromHome < 1096) {
            bestAngle = bestAngle + lbl_3_rodata_1A78;
        }
        frames = 600;
    }
    *throwAngle = bestAngle;
    *throwSpeed = speed;
    g_Ball.framesUntilThrowReachesDest = frames;
    g_Ball.throwTimeEstimatesCompleteInd = 0;
    if (g_FieldingLogic.laser_1 != 0) {
        fieldingRelatedAnimations(((void**)(hugeAnimStruct + 0x2c50))[g_Ball.fielderWBallIndex], 4);
    }
}

// .text:0x000ABDD0 size:0xC28 mapped:0x806EAE64
void makeThrowVariables(int fielderIndex) {
    InMemFielder* fielder = &g_Fielders[fielderIndex];
    f32 targetX;
    f32 targetZ;
    f32 xDist;
    f32 zDist;
    f32 throwAngle;
    f32 throwSpeed;
    int loc;
    int chem;
    int prob;
    int rng;
    int at4;
    int i;
    f32 dx;
    f32 dz;
    f32 groundSpeed;

    loc = g_FieldingLogic.locationThrownTo;
    g_Ball.AtBat_Contact_BallPos.x = fielder->pos.x + g_Ball.offsetWhilePickedUpHistory[0].x;
    g_Ball.AtBat_Contact_BallPos.y = fielder->pos.y + g_Ball.offsetWhilePickedUpHistory[0].y;
    g_FieldingLogic.IsChemistryThrow = 0;
    g_Ball.AtBat_Contact_BallPos.z = fielder->pos.z + g_Ball.offsetWhilePickedUpHistory[0].z;
    g_Ball.IsAntichemistryThrow = 0;
    g_Ball.offsetWhilePickedUpHistory[0].x = lbl_3_rodata_193C;
    g_Ball.offsetWhilePickedUpHistory[0].y = lbl_3_rodata_193C;
    g_Ball.offsetWhilePickedUpHistory[0].z = lbl_3_rodata_193C;
    if ((s16)loc >= 0 && loc <= 3) {
        g_Ball.fielderBeingThrownTo = g_FieldingLogic.fielderAssignedLocationIndex[loc];
        targetX = base_MoundCoordinates[loc].x;
        targetZ = base_MoundCoordinates[loc].z;
        chem = calculateChemistry(g_GameLogic.teamFielding, g_Fielders[fielderIndex].CharID,
                                  g_Fielders[g_Ball.fielderBeingThrownTo].CharID);
        if (chem >= chemThresholds[0] &&
            g_FieldingLogic.locationThrownTo == g_Fielders[g_Ball.fielderBeingThrownTo].baseCurrentlyOn) {
            g_FieldingLogic.IsChemistryThrow = 1;
        }
        if (chem < chemThresholds[1]) {
            prob = LERPToNewRange_Float(chem, 0, 100, lbl_3_data_4908[0], lbl_3_data_4908[1]);
            rng = RandomInt_Game(100);
            if (!ACTIVE_TUTORIAL() && rng < prob) {
                f32 sqx;
                f32 sqz;
                f32 dist;
                int angle;
                int adj;
                int rng2;
                int ang;

                xDist = targetX - g_Ball.AtBat_Contact_BallPos.x;
                zDist = targetZ - g_Ball.AtBat_Contact_BallPos.z;
                g_Ball.IsAntichemistryThrow = 1;
                sqx = xDist * xDist;
                sqz = zDist * zDist;
                dist = dolsqrtf2(sqx + sqz);
                angle = calculateAngleFromCoordinates(xDist, zDist);
                adj = RandomInt_Game_Range(specialFielderActionConstants._40[3], specialFielderActionConstants._40[4]);
                rng2 = RandomInt_Game(2);
                ang = angle - adj;
                if (rng2 != 0) {
                    ang = angle + adj;
                }
                getComponentsFromSAng(ang, &xDist, &zDist);
                xDist = xDist * dist;
                zDist = zDist * dist;
                targetX = g_Ball.AtBat_Contact_BallPos.x + xDist;
                targetZ = g_Ball.AtBat_Contact_BallPos.z + zDist;
            }
        }
    } else if (loc == 6 && g_FieldingLogic.cutoffFielderIndex >= 0 && g_FieldingLogic.cutoffFielderIndex != fielderIndex) {
        setCutoffThrowTargetLocation(&targetX, &targetZ);
    } else if ((at4 = g_FieldingLogic.fielderAssignedLocationIndex[4]) < 0) {
        targetX = base_MoundCoordinates[4].x;
        targetZ = base_MoundCoordinates[4].z;
        g_Ball.ballIsLooseInd_unused = 1;
        g_Ball.fielderBeingThrownTo = -1;
    } else {
        InMemFielder* thrower = &g_Fielders[g_Ball.fielderWBallIndex];
        InMemFielder* receiver = &g_Fielders[at4];
        f32 speed;
        f32 dist;
        int frames;

        speed = thrower->modifiedThrowingArm / lbl_3_rodata_1938;
        dx = receiver->pos.x - thrower->pos.x;
        dz = receiver->pos.z - thrower->pos.z;
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
        frames -= 10;
        if (receiver->numFramesToGetToAutoLocation < frames) {
            targetX = receiver->IntendedLocation.x;
            targetZ = receiver->IntendedLocation.z;
        } else {
            targetX = frames * receiver->velocityX + receiver->pos.x;
            targetZ = frames * receiver->velocityZ + receiver->pos.z;
        }
        g_Ball.fielderBeingThrownTo = at4;
    }
    g_Ball.throwTarget.x = targetX;
    g_Ball.throwTarget.z = targetZ;
    throwSpeed = (u8)getThrowSpeedBasedOnArmStrengthStat(fielder->throwingArm);
    if (g_FieldingLogic.someThrowSpeedIncreaseInd != 0) {
        if (g_FieldingLogic.throwWindUpFrameCounter > 0x3c) {
            g_FieldingLogic.throwSpeedType -= 2;
        } else if (g_FieldingLogic.throwWindUpFrameCounter > 0x28) {
            g_FieldingLogic.throwSpeedType -= 1;
        }
        g_FieldingLogic.someThrowSpeedIncreaseInd = 0;
    }
    if (g_FieldingLogic.IsChemistryThrow != 0) {
        if (g_FieldingLogic.throwSpeedType != 0 && g_FieldingLogic.throwSpeedType <= 3) {
            g_FieldingLogic.throwSpeedType = g_FieldingLogic.throwSpeedType - 1;
            playSoundEffect(0x1ab);
        } else {
            g_FieldingLogic.IsChemistryThrow = 2;
        }
        if (!g_d_GameSettings.exhibitionMatchInd && lbl_3_common_bss_37400[0x20] == g_GameLogic.teamFielding) {
            starMissionsQuantityBased(7, fielder->rosterLocation);
        }
    }
    throwSpeed = throwSpeed / lbl_3_rodata_1938;
    loc = g_FieldingLogic.locationThrownTo;
    if (loc == 6 || loc == 5) {
        initializeThrowAngle_Speed_Length(0, &throwAngle, &throwSpeed);
    } else {
        initializeThrowAngle_Speed_Length(
            g_Fielders[g_FieldingLogic.fielderAssignedLocationIndex[loc]].numFramesToGetToAutoLocation, &throwAngle,
            &throwSpeed);
    }
    g_Ball.physicsSubstruct.velocity.y = throwSpeed * (f32)sin(throwAngle);
    groundSpeed = throwSpeed * (f32)cos(throwAngle);
    xDist = g_Ball.throwTarget.x - g_Ball.AtBat_Contact_BallPos.x;
    zDist = g_Ball.throwTarget.z - g_Ball.AtBat_Contact_BallPos.z;
    throwAngle = atan2(zDist, xDist);
    g_Ball.physicsSubstruct.velocity.x = groundSpeed * (f32)cos(throwAngle);
    g_Ball.physicsSubstruct.velocity.z = groundSpeed * (f32)sin(throwAngle);
    g_Ball.throwStartingLocation.z = g_Ball.AtBat_Contact_BallPos.z;
    g_Ball.throwStartingLocation.x = g_Ball.AtBat_Contact_BallPos.x;
    if (g_Ball.numThrowsDuringPlay < 0xfe) {
        g_Ball.numThrowsDuringPlay++;
    } else {
        g_Ball.numThrowsDuringPlay = 0xff;
    }
    dx = g_Ball.throwTarget.x - g_Ball.AtBat_Contact_BallPos.x;
    dz = g_Ball.throwTarget.z - g_Ball.AtBat_Contact_BallPos.z;
    fielder->currentVelocity = lbl_3_rodata_193C;
    fielder->const_60 = 60;
    g_Ball.ballZoneFromHomeAtStartOfThrow = g_Ball.ballZoneAwayFromHome;
    dx = dx * dx;
    dz = dz * dz;
    fielder->standingStillInd = 1;
    g_FieldingLogic.locThrownTo2 = g_FieldingLogic.locationThrownTo;
    g_Ball.framesSinceThrowStarted = 0;
    g_Ball.ballState = BALL_STATE_THROWN;
    g_Ball.fielderWBallIndex = -1;
    g_Ball.baseBallAndFielderAreOn = -1;
    g_Ball.ballIsLooseInd_unused = 0;
    g_Ball.fielderAboutToGetBall_hasBall = -1;
    g_Ball.thrownBallHasHitGround = 0;
    g_Ball.throwingFielder = fielderIndex;
    g_Ball.matchFramesAndBallAngle.framesSinceLastThrow = g_Ball.timeSinceBallPickedUp;
    g_Ball.timeSinceBallPickedUp = -1;
    g_Ball.ballIsRollingIndicator = 0;
    g_FieldingLogic.unused_always0 = 0;
    g_FieldingLogic._011d = 0;
    fielder->_01E4 = 0;
    g_Pitcher.pickOffLoc = -1;
    g_FieldingLogic.tagAnimationCountdown = 0;
    g_FieldingLogic.baseFielderIsOn = 0xff;
    g_FieldingLogic.someCountDown = 0;
    g_FieldingLogic.humanSelectedPlaceToThrow = -1;
    g_Ball.throwDistance = dolsqrtf2(dx + dz);
    if (g_FieldingLogic.cutoffFielderIndex == fielderIndex) {
        g_FieldingLogic.cutoffFielderIndex = -1;
    }
    for (i = 0; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD) {
            g_Runners[i].baseReachedAtTimeOfThrow = g_Runners[i].currentBase;
        } else {
            g_Runners[i].baseReachedAtTimeOfThrow = -1;
        }
    }
    liveBallHitPhysics(1);
    if (g_FieldingLogic.throwSpeedType <= 2 && g_FieldingLogic.smash0_normalThrow1 == 0) {
        animateThrownBall(0x16e, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.y,
                          g_Ball.AtBat_Contact_BallPos.z);
    } else {
        animateThrownBall(0x16d, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.y,
                          g_Ball.AtBat_Contact_BallPos.z);
    }
    pickoff_infieldThrow_related(fielderIndex);
    if (g_FieldingLogic.IsChemistryThrow != 0) {
        playCharacterSound(fielder->CharID, 0);
    } else if (g_Ball.IsAntichemistryThrow != 0) {
        playCharacterSound(fielder->CharID, 10);
    } else {
        playCharacterSound(fielder->CharID, 5);
    }
}

