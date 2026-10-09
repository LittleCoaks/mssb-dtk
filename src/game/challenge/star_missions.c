#define SQRT2_LINKAGE static
#include "game/challenge/star_missions.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/rand.h"
#include "game/minigame/minigame_models.h"
#include "header_rep_data.h"

typedef struct CharStaticIndex {
    /*0x0*/ u8 _0;
    /*0x1*/ u8 trackerIdx;
    /*0x2*/ u8 requirementRow;
    /*0x3*/ u8 _3[3];
} CharStaticIndex; // size: 0x6

extern CharStaticIndex characterStaticIndexes[54];

typedef struct StarMissionRequirement {
    /*0x0*/ s16 type;
    /*0x2*/ s16 target;
    /*0x4*/ s16 flags;
    /*0x6*/ s16 _6[2];
} StarMissionRequirement; // size: 0xA

extern StarMissionRequirement starMissionRequirementsTable[32][10];

typedef struct ScoutPair {
    /*0x0*/ s8 cur;
    /*0x1*/ s8 max;
} ScoutPair;

typedef struct ScoutEntry {
    /*0x0*/ u8 achieved;
    /*0x1*/ u8 max;
    /*0x2*/ u8 amount;
    /*0x3*/ s8 active;
    /*0x4*/ u8 trackerIdx;
} ScoutEntry; // size: 0x5

typedef struct ScoutState {
    /*0x00*/ ScoutPair pairs[9];
    /*0x12*/ ScoutEntry entries[9];
    /*0x3F*/ u8 _3F;
    /*0x40*/ s16 humanTeam;
    /*0x42*/ s16 scoutCountdown;
    /*0x44*/ s16 targetRosterID;
    /*0x46*/ u8 scoutMissionID;
    /*0x47*/ u8 scoutResult;
    /*0x48*/ u8 scoutFlag;
    /*0x49*/ s8 baseReward;
    /*0x4A*/ s8 _4A;
    /*0x4B*/ u8 _4B[3];
} ScoutState; // size: 0x4E

extern ScoutState lbl_3_common_bss_37400;

typedef struct ScoutMission {
    /*0x0*/ s8 chanceA[4];
    /*0x4*/ s8 chanceB[5];
    /*0x9*/ s8 reward[4];
    /*0xD*/ s8 starMission;
    /*0xE*/ u8 _E;
} ScoutMission; // size: 0xF

extern ScoutMission scoutMissionTable[13];

typedef struct AnimEntry {
    /*0x00*/ u8 _00[0x26];
    /*0x26*/ u8 _26;
    /*0x27*/ u8 _27;
} AnimEntry; // size: 0x28

extern struct {
    /*0x0000*/ u8 _0000[0x2D94];
    /*0x2D94*/ AnimEntry* entries;
    /*0x2D98*/ u8 _2D98[0x3078 - 0x2D98];
    /*0x3078*/ u16 entryCount;
    /*0x307A*/ u8 _307A[0x3154 - 0x307A];
} hugeAnimStruct;

extern u8 animRelated[0x124];

#define TRACKER_RAW ((u8*)starMissionCompletionTracker)
#define SCOUT_ROW_A (TRACKER_RAW[0x4415])
#define SCOUT_ROW_B (TRACKER_RAW[0x441C])

typedef struct ScoutFlagTable {
    /*0x0*/ u8 _0[4];
    /*0x4*/ s8 max[4][6];
} ScoutFlagTable;

#define SCOUT_FLAG_MAX(t, rowA, rowB) (((ScoutFlagTable*)(t)->scoutFlagPointer)->max[rowA][rowB])
#define SCOUT_FLAG_ROWS(t) ((s8(*)[6])((u8*)(t)->scoutFlagPointer + 4))

#define MISSION_TRACKER(ci) (&starMissionCompletionTracker[(ci)->trackerIdx])
#define MISSION_REQS(ci) (starMissionRequirementsTable[(ci)->requirementRow])

#define MISSION_ADVANCE(ct, req, i)                                                    \
    (ct)->inGameMissionTracker[i].starMissionStatus++;                                 \
    if ((ct)->inGameMissionTracker[i].starMissionStatus >= (req)[i].target) {          \
        (ct)->inGameMissionTracker[i].starMissionStatus = -1;                          \
    }

static inline void fillRosterCharIDs(s16* ids) {
    s32 i;
    for (i = 0; i < 9; i++) {
        ids[i] = inMemRoster[1][i].stats.CharID;
    }
}

// .text:0x001663AC size:0x9C mapped:0x807A5440
void fn_3_1663AC(void) {
    if (g_GameLogic.secondaryGameMode == 0xA || g_GameLogic.secondaryGameMode == 0x12) {
        if (hugeAnimStruct.entryCount != 0) {
            AnimEntry* entry;
            int i;
            for (i = 0; i < hugeAnimStruct.entryCount; i++) {
                entry = &hugeAnimStruct.entries[i];
                if (entry != NULL) {
                    entry->_26 = 0;
                }
            }
        }
    } else if (g_Practice.practiceLevel == 4) {
        mm_UpdatePitchingMachine();
    }
}

// .text:0x00165D24 size:0x688 mapped:0x807A4DB8
BOOL decideScoutFlagMission(void) {
    int idx = 0;
    GameControlsStruct* logic = &g_GameLogic;
    ChallengeTrackingStruct* trackers = starMissionCompletionTracker;
    InMemBatterType* batter = &g_Batter;
    ScoutState* scout = &lbl_3_common_bss_37400;
    InMemRunnerType* runners = g_Runners;
    InMemPitcherType* pitcher = &g_Pitcher;
    u8 rowB = ((u8*)trackers)[0x441C];
    u8 rowA = ((u8*)trackers)[0x4415];

    scout->scoutResult = 0;
    scout->scoutCountdown = 0;
    if (scout->scoutFlag != 0) {
        if (scout->scoutFlag == 2) {
            scout->scoutMissionID = 0;
            scout->scoutFlag = 0;
            return FALSE;
        }
        switch (scout->scoutMissionID) {
        case 6:
        case 7:
            break;
        case 8:
            if (storedInningInfo.nBattersThisInning2 >= 4 ||
                g_Scores.scores[logic->homeTeamBattingInd_fieldingTeam].byInning[g_Scores.Inning - 1] != 0) {
                scout->scoutMissionID = 0;
                scout->scoutFlag = 0;
            }
            break;
        case 9:
        case 10:
            if (scout->targetRosterID != runners[3].rosterID || g_Strikes.outs == 2) {
                scout->scoutMissionID = 0;
                scout->scoutFlag = 0;
            }
            break;
        case 11:
            if (scout->targetRosterID != runners[1].rosterID) {
                scout->scoutMissionID = 0;
                scout->scoutFlag = 0;
            }
            break;
        }
        return FALSE;
    }

    scout->scoutMissionID = 0;
    sound_crowd_EffectsStruct._32 = 0;
    if (g_d_GameSettings.bJMatchInd == 1) {
        if (shouldScoutMissionBeEnabled(12)) {
            scout->scoutMissionID = 12;
        }
    } else if (logic->teamBatting == g_d_GameSettings.humanTeamNumber) {
        if (g_RunningLogic._10 >= 2) {
            s32* captains = logic->Team_CaptainRosterLoc;

            if (batter->rosterID == captains[logic->teamBatting] &&
                pitcher->rosterID == captains[logic->teamFielding]) {
                if (shouldScoutMissionBeEnabled(3)) {
                    scout->scoutMissionID = 3;
                }
                goto chosen;
            }
            if (g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total <
                    g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total &&
                g_Scores._A6 <= 3) {
                if (shouldScoutMissionBeEnabled(4)) {
                    scout->scoutMissionID = 4;
                }
                goto chosen;
            }
        }
        if ((g_RunningLogic._00 & 0x1000) && g_Strikes.outs <= 1) {
            if (g_Batter.characterClass == CHARACTER_CLASS_BALANCED || g_Batter.characterClass == CHARACTER_CLASS_POWER) {
                if (shouldScoutMissionBeEnabled(9)) {
                    scout->scoutMissionID = 9;
                }
                goto chosen;
            }
            if (g_Batter.characterClass == CHARACTER_CLASS_SPEED || g_Batter.characterClass == CHARACTER_CLASS_TECHNIQUE) {
                if (shouldScoutMissionBeEnabled(10)) {
                    scout->scoutMissionID = 10;
                }
                goto chosen;
            }
        }
        if (g_RunningLogic._00 == 0x11 &&
            inMemRoster[g_GameLogic.teamBatting][runners[1].rosterID].stats.CharacterClass == CHARACTER_CLASS_SPEED) {
            if (shouldScoutMissionBeEnabled(11)) {
                scout->scoutMissionID = 11;
            }
        } else {
            idx = pitcher->scoutFlagRelated;
            if (idx != -1) {
                ChallengeTrackingStruct* t = &trackers[idx];
                s8 max = SCOUT_FLAG_ROWS(t)[rowA][rowB];
                if (max != 0 && (s8)t->scoutFlagsAchieved < max) {
                    if (shouldScoutMissionBeEnabled(2)) {
                        scout->scoutMissionID = 2;
                    }
                }
            }
        }
    } else if (logic->teamBatting != g_d_GameSettings.humanTeamNumber) {
        if (g_RunningLogic._10 >= 3 && g_Scores.scores[g_Scores.halfInning].byInning[g_Scores.Inning - 1] == 0) {
            if (shouldScoutMissionBeEnabled(5)) {
                scout->scoutMissionID = 5;
            }
        } else if ((g_RunningLogic._00 & 0x10) && g_Strikes.outs <= 1) {
            if (shouldScoutMissionBeEnabled(6)) {
                scout->scoutMissionID = 6;
            }
        } else if (g_Batter.rosterID == g_GameLogic.Team_CaptainRosterLoc[g_GameLogic.teamBatting]) {
            if (shouldScoutMissionBeEnabled(7)) {
                scout->scoutMissionID = 7;
            }
        } else if (g_Scores._C6 == 1) {
            if (shouldScoutMissionBeEnabled(8)) {
                scout->scoutMissionID = 8;
            }
        } else {
            idx = batter->charIDForScoutFlagMission;
            if (idx != -1) {
                ChallengeTrackingStruct* t = &trackers[idx];
                s8 max = SCOUT_FLAG_ROWS(t)[rowA][rowB];
                if (max != 0 && (s8)t->scoutFlagsAchieved < max) {
                    if (shouldScoutMissionBeEnabled(1)) {
                        scout->scoutMissionID = 1;
                    }
                }
            }
        }
    }

chosen:
    switch (scout->scoutMissionID) {
    case 9:
        scout->targetRosterID = runners[3].rosterID;
        break;
    case 10:
        scout->targetRosterID = runners[3].rosterID;
        break;
    case 11:
        scout->targetRosterID = runners[1].rosterID;
        break;
    }

    if (scout->scoutMissionID != 0) {
        clearScoutState();
        if (scout->scoutMissionID == 2 || scout->scoutMissionID == 1) {
            assignScoutFlagRewardToTarget();
        } else {
            assignScoutFlagRewardRandom();
        }
        *(s16*)((u8*)trackers + 0x43C0) = idx;
        ((u8*)trackers)[0x44F1] = 1;
        animRelated[0xB3] = 1;
        g_GameLogic.IsStarChance = 0;
        animRelated[0xAC] = 0;
        setScoutMissionRelatedToZero();
        return TRUE;
    }
    return FALSE;
}

#pragma dont_inline on
// .text:0x001659A0 size:0x384 mapped:0x807A4A34
BOOL shouldScoutMissionBeEnabled(int mission) {
    ScoutState* scout = &lbl_3_common_bss_37400;
    u8 rowA = SCOUT_ROW_A;
    BOOL enabled;
    int roll;
    int chance;

    if (scout->scoutMissionID == 2 || scout->scoutMissionID == 1) {
        enabled = isScoutTargetFlagAvailable();
    } else {
        enabled = anyScoutFlagIncomplete();
    }
    if (!enabled) {
        return FALSE;
    }
    roll = rand() % 100;
    if (scout->_4A == 0) {
        chance = scoutMissionTable[mission].chanceA[rowA];
    } else {
        chance = scoutMissionTable[mission].chanceB[rowA];
    }
    if (roll <= chance) {
        return TRUE;
    }
    return FALSE;
}
#pragma dont_inline reset

// .text:0x0016598C size:0x14 mapped:0x807A4A20
void setScoutMissionRelatedToZero(void) {
    lbl_3_common_bss_37400._4A = 0;
}

// .text:0x00165978 size:0x14 mapped:0x807A4A0C
void fn_3_165978(void) {
    lbl_3_common_bss_37400._4A = 0;
}

// .text:0x001658F0 size:0x88 mapped:0x807A4984
void clearScoutState(void) {
    ScoutState* scout = &lbl_3_common_bss_37400;
    s32 i;
    for (i = 0; i < 9; i++) {
        scout->entries[i].max = 0;
        scout->entries[i].achieved = 0;
        scout->entries[i].amount = 0;
        scout->entries[i].active = 0;
        scout->entries[i].trackerIdx = 0;
        scout->pairs[i].cur = 0;
        scout->pairs[i].max = 0;
    }
}

// .text:0x00164A74 size:0xE7C mapped:0x807A3B08
void scoutFlag_checkMissionSuccess(void) {
    ScoutState* scout = &lbl_3_common_bss_37400;
    ScoutMission* missions = scoutMissionTable;
    ChallengeTrackingStruct* trackers = starMissionCompletionTracker;
    u8 rowB = ((u8*)trackers)[0x441C];
    u8 rowA = ((u8*)trackers)[0x4415];
    StoredInningInfo* inning = &storedInningInfo;
    InMemRunnerType* runners = g_Runners;
    int cnt = 0;
    BOOL flag = FALSE;

    scout->scoutResult = 1;
    scout->baseReward = missions[scout->scoutMissionID].reward[0];
    switch (scout->scoutMissionID) {
    case 0:
        break;
    case 1:
        if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != PICKOFF_STEAL_CODE_NONE) {
            if (g_Strikes.outs >= 3) {
                scout->scoutResult = 2;
            } else if (g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT) {
                scout->scoutFlag = 0;
            } else {
                scout->scoutResult = 0;
            }
        } else if ((g_Strikes.outs > g_Strikes.storedOuts && inning->batterResultBase == 0) ||
                   g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT) {
            if (g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT ||
                storedInningInfo.playResultCode == PLAY_RESULT_CODE_FOUL_BUNT_TWO_STRIKES) {
                scout->scoutResult = 2;
                cnt = 1;
            } else {
                scout->scoutResult = 2;
                cnt = 0;
            }
        }
        break;
    case 2:
        if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != PICKOFF_STEAL_CODE_NONE) {
            if (g_Strikes.outs >= 3) {
                scout->scoutFlag = 0;
            } else if (g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT) {
                scout->scoutFlag = 0;
            } else {
                scout->scoutResult = 0;
            }
        } else if (g_Strikes.howRunnerReachedBase == 1 || inning->batterResultBase >= 1) {
            if (storedInningInfo.playResultCode == PLAY_RESULT_CODE_NONE && storedInningInfo.runnersTargetedWhileBatterForceable <= 0) {
                if (inning->tentativeBatterBase == 1) {
                    if (inning->rbisWaitingToBeAddedToScore == 1) {
                        cnt = 1;
                    } else if (inning->rbisWaitingToBeAddedToScore >= 2) {
                        cnt = 2;
                    } else {
                        cnt = 0;
                    }
                } else if (inning->tentativeBatterBase == 2) {
                    cnt = 1;
                } else if (inning->tentativeBatterBase >= 3) {
                    cnt = 2;
                }
                scout->scoutResult = 2;
            }
        }
        break;
    case 3:
        if (g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total > g_Scores._A0 ||
            g_Ball.deadBallReason == 1 ||
            ((g_Pitcher.strikeOutOrWalk == AT_BAT_END_WALK || g_Pitcher.strikeOutOrWalk == AT_BAT_END_HIT_BY_PITCH) &&
             g_RunningLogic.nOffensivePlayersAtStartOfPlay >= 4)) {
            scout->scoutResult = 2;
            scout->scoutFlag = 0;
        } else if (g_Strikes.outs >= 3 ||
                   (g_Strikes.outs == 2 && g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT &&
                    g_FieldingLogic.liveBallBcOfPickoffOrStealCd == PICKOFF_STEAL_CODE_NONE)) {
            scout->scoutFlag = 0;
        } else {
            scout->scoutFlag = 1;
            scout->scoutResult = 0;
        }
        break;
    case 4: {
        int theirs = g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total;
        int ours = g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total;
        if (theirs > ours || (g_Ball.deadBallReason == 1 && g_Scores._A0 + g_RunningLogic.nOffensivePlayersAtStartOfPlay > ours) ||
            ((g_Pitcher.strikeOutOrWalk == AT_BAT_END_WALK || g_Pitcher.strikeOutOrWalk == AT_BAT_END_HIT_BY_PITCH) &&
             g_RunningLogic.nOffensivePlayersAtStartOfPlay >= 4 && g_Scores._A0 == ours)) {
            scout->scoutResult = 2;
            scout->scoutFlag = 0;
        } else if (g_Strikes.outs >= 3 || (g_Strikes.outs == 2 && g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT)) {
            scout->scoutFlag = 0;
        } else {
            scout->scoutFlag = 1;
            scout->scoutResult = 0;
        }
        break;
    }
    case 5: {
        u8 deadBallReason = g_Ball.deadBallReason;
        if (g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total > g_Scores._A0 ||
            deadBallReason == 1 ||
            (g_RunningLogic._02 == 0x1111 && (g_Pitcher.strikeOutOrWalk == AT_BAT_END_WALK || g_Pitcher.strikeOutOrWalk == AT_BAT_END_HIT_BY_PITCH))) {
            scout->scoutFlag = 0;
        } else if ((g_Strikes.outs >= 2 && g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT &&
                    g_FieldingLogic.liveBallBcOfPickoffOrStealCd == PICKOFF_STEAL_CODE_NONE) ||
                   g_Strikes.outs >= 3) {
            scout->scoutResult = 2;
            scout->scoutFlag = 0;
        } else {
            scout->scoutFlag = 1;
            scout->scoutResult = 0;
        }
        break;
    }
    case 6:
        if (g_Strikes.outs >= g_Strikes.storedOuts + 2) {
            scout->scoutResult = 2;
            scout->scoutFlag = 0;
        } else if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != PICKOFF_STEAL_CODE_NONE) {
            scout->scoutFlag = 1;
            scout->scoutResult = 0;
        } else {
            scout->scoutFlag = 0;
        }
        break;
    case 7:
        if (g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT) {
            scout->scoutResult = 2;
            scout->scoutFlag = 0;
        } else if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != PICKOFF_STEAL_CODE_NONE) {
            if (g_Strikes.outs >= 3) {
                scout->scoutFlag = 0;
            } else {
                scout->scoutFlag = 1;
                scout->scoutResult = 0;
            }
        }
        break;
    case 8: {
        int threw;
        if (inning->nBattersThisInning2 == 3) {
            if ((g_Strikes.outs >= 2 && g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT &&
                 g_FieldingLogic.liveBallBcOfPickoffOrStealCd == PICKOFF_STEAL_CODE_NONE) ||
                g_Strikes.outs >= 3) {
                scout->scoutResult = 2;
                scout->scoutFlag = 0;
                break;
            }
        }
        threw = 0;
        if (g_Ball.deadBallReason == 3) {
            if (g_RunningLogic._02 & 0x1100) {
                threw = 1;
            }
        } else if (g_Ball.deadBallReason == 4) {
            if (g_RunningLogic._02 & 0x1100) {
                threw = 1;
            } else {
                if (g_Runners[1].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD && g_Runners[1].baseReachedAtTimeOfThrow >= 2) {
                    threw = 1;
                }
                if (g_Runners[0].runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD && g_Runners[0].baseReachedAtTimeOfThrow >= 2) {
                    threw = 1;
                }
            }
        }
        if (inning->nBattersThisInning2 == 3 && g_FieldingLogic.liveBallBcOfPickoffOrStealCd == PICKOFF_STEAL_CODE_NONE) {
            scout->scoutFlag = 0;
        } else if (g_Scores._A0 < g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total) {
            scout->scoutFlag = 0;
        } else if (g_Ball.deadBallReason == 1 || threw != 0) {
            scout->scoutFlag = 0;
        } else {
            scout->scoutFlag = 1;
            scout->scoutResult = 0;
        }
        break;
    }
    case 9:
        if (inning->playResultCode == PLAY_RESULT_CODE_SAC_FLY_SCORED) {
            scout->scoutResult = 2;
            scout->scoutFlag = 0;
        } else if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != PICKOFF_STEAL_CODE_NONE) {
            if (g_Strikes.outs >= 3) {
                scout->scoutFlag = 0;
            } else if (g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT) {
                scout->scoutFlag = 0;
            } else {
                scout->scoutFlag = 1;
                scout->scoutResult = 0;
            }
        } else {
            scout->scoutFlag = 0;
        }
        break;
    case 10:
        if (g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total > g_Scores._A0) {
            if (runners[3].furthestBaseForcedToGoToOnWalk != 0) {
                if (g_Ball.maybeBuntInd != 0) {
                    flag = TRUE;
                }
            }
        }
        if (flag) {
            scout->scoutResult = 2;
            scout->scoutFlag = 0;
        } else if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != PICKOFF_STEAL_CODE_NONE) {
            if (g_Strikes.outs >= 3) {
                scout->scoutFlag = 0;
            } else if (g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT) {
                scout->scoutFlag = 0;
            } else if (runners[3].runnerOnFieldOrOutOrScored != RUNNER_STATUS_ON_FIELD) {
                scout->scoutFlag = 0;
            } else {
                scout->scoutFlag = 1;
                scout->scoutResult = 0;
            }
        } else {
            scout->scoutFlag = 0;
        }
        break;
    case 11: {
        u8 fl = g_FieldingLogic.liveBallBcOfPickoffOrStealCd;
        u8 runnerStatus = 0;
        if (fl == PICKOFF_STEAL_CODE_PICKOFF || fl == PICKOFF_STEAL_CODE_STEAL) {
            runnerStatus = runners[1].runnerOnFieldOrOutOrScored;
            if (runnerStatus == RUNNER_STATUS_ON_FIELD || runnerStatus == RUNNER_STATUS_SCORED_DURING_PLAY) {
                if (runners[1].currentBase > 1) {
                    flag = 1;
                }
            }
            if (runnerStatus == RUNNER_STATUS_OUT_DURING_PLAY) {
                flag = 2;
            }
        }
        if (flag == 2) {
            scout->scoutResult = 1;
            scout->scoutFlag = 0;
        } else if (flag != 0) {
            scout->scoutResult = 2;
            scout->scoutFlag = 0;
        } else if (fl != PICKOFF_STEAL_CODE_NONE) {
            if (g_Strikes.outs >= 3) {
                scout->scoutFlag = 0;
            } else if (g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT) {
                scout->scoutFlag = 0;
            } else {
                scout->scoutFlag = 1;
                scout->scoutResult = 0;
            }
        } else {
            scout->scoutFlag = 0;
        }
        break;
    }
    case 12:
        if (g_GameLogic.EventTriggers_EndOfGame != 0) {
            if ((g_GameLogic.homeTeamInd ^ (g_Scores.winnerCd == g_d_GameSettings.humanTeamNumber)) != 0 &&
                g_Scores.winnerCd != 2) {
                scout->scoutResult = 2;
            } else {
                scout->scoutResult = 1;
            }
            scout->scoutFlag = 0;
        } else if (g_Scores.Inning >= g_Scores.inningLimit && g_Scores.halfInning != 0) {
            if (g_Ball.deadBallReason == 1 &&
                g_Scores._A0 + g_RunningLogic.nOffensivePlayersAtStartOfPlay >
                    g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total) {
                if (g_GameLogic.teamBatting == g_d_GameSettings.humanTeamNumber) {
                    scout->scoutResult = 2;
                }
                scout->scoutFlag = 0;
            } else if (g_Strikes.outs >= 2 && g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT) {
                if ((g_Scores.scores[1].total > g_Scores.scores[0].total &&
                     lbl_3_common_bss_37400.humanTeam == g_GameLogic.teamBatting) ||
                    (g_Scores.scores[1].total < g_Scores.scores[0].total &&
                     lbl_3_common_bss_37400.humanTeam == g_GameLogic.teamFielding)) {
                    scout->scoutResult = 2;
                }
                scout->scoutFlag = 0;
            } else if (g_RunningLogic._10 == 4 &&
                       (g_Pitcher.strikeOutOrWalk == AT_BAT_END_WALK || g_Pitcher.strikeOutOrWalk == AT_BAT_END_HIT_BY_PITCH)) {
                if (g_Scores.scores[1].total == g_Scores.scores[0].total) {
                    if (g_GameLogic.teamBatting == g_d_GameSettings.humanTeamNumber) {
                        scout->scoutResult = 2;
                    }
                    scout->scoutFlag = 0;
                } else {
                    scout->scoutFlag = 1;
                    scout->scoutResult = 0;
                }
            } else {
                scout->scoutFlag = 1;
                scout->scoutResult = 0;
            }
        } else {
            scout->scoutFlag = 1;
            scout->scoutResult = 0;
        }
        break;
    }

    if (scout->scoutResult == 2) {
        if (scout->scoutMissionID == 2 || scout->scoutMissionID == 1) {
            ChallengeTrackingStruct* t = &trackers[*(s16*)((u8*)trackers + 0x43C0)];
            s8 reward = missions[scout->scoutMissionID].reward[cnt];
            s8 max;
            int i;
            for (i = 0; i < 9; i++) {
                if (scout->entries[i].active == 1) {
                    scout->entries[i].amount = reward;
                }
            }
            t->scoutFlagsAchieved += reward;
            max = SCOUT_FLAG_ROWS(t)[rowA][rowB];
            if ((s8)t->scoutFlagsAchieved > max) {
                t->scoutFlagsAchieved = max;
            }
        } else {
            applyScoutFlagRewards();
        }
    }
}

// .text:0x00164664 size:0x410 mapped:0x807A36F8
void awardScoutFlagsSequential(void) {
    s16 ids[9];
    ScoutMission* missions = scoutMissionTable;
    ChallengeTrackingStruct* trackers = starMissionCompletionTracker;
    u8 rowB = ((u8*)trackers)[0x441C];
    u8 rowA = ((u8*)trackers)[0x4415];
    int k;
    int amount;
    BOOL enabled;

    amount = missions[lbl_3_common_bss_37400.scoutMissionID].reward[0];
    fillRosterCharIDs(ids);
    k = 0;
    enabled = anyScoutFlagIncomplete();
    if (amount > 0 && enabled) {
        while (amount > 0) {
            if (ids[k] != -1) {
                ChallengeTrackingStruct* t = &trackers[ids[k]];
                s8 max = SCOUT_FLAG_MAX(t, rowA, rowB);
                if (max != 0 && (s8)t->scoutFlagsAchieved < max) {
                    t->scoutFlagsAchieved++;
                    amount--;
                }
            }
            k = (k + 1) % 9;
            if (!anyScoutFlagIncomplete()) {
                break;
            }
        }
    }
}

// .text:0x00164554 size:0x110 mapped:0x807A35E8
void applyScoutFlagRewards(void) {
    s16 ids[9];
    ChallengeTrackingStruct* trackers = starMissionCompletionTracker;
    ScoutState* scout = &lbl_3_common_bss_37400;
    u8 rowB = ((u8*)trackers)[0x441C];
    u8 rowA = ((u8*)trackers)[0x4415];
    int i;

    fillRosterCharIDs(ids);
    for (i = 0; i < 9; i++) {
        if (ids[i] != -1 && scout->entries[i].active == 1) {
            ChallengeTrackingStruct* t = &trackers[ids[i]];
            if (SCOUT_FLAG_MAX(t, rowA, rowB) != 0) {
                t->scoutFlagsAchieved += scout->entries[i].amount;
                if ((s8)t->scoutFlagsAchieved > SCOUT_FLAG_MAX(t, rowA, rowB)) {
                    t->scoutFlagsAchieved = SCOUT_FLAG_MAX(t, rowA, rowB);
                }
            }
        }
    }
}

// .text:0x0016440C size:0x148 mapped:0x807A34A0
void assignScoutFlagRewardToTarget(void) {
    s16 ids[9];
    ScoutState* scout = &lbl_3_common_bss_37400;
    ScoutMission* missions = scoutMissionTable;
    ChallengeTrackingStruct* trackers = starMissionCompletionTracker;
    InMemBatterType* batter = &g_Batter;
    InMemPitcherType* pitcher = &g_Pitcher;
    u8 rowB = ((u8*)trackers)[0x441C];
    u8 rowA = ((u8*)trackers)[0x4415];
    int amount;
    int cid;
    s32 i;
    s8 max;
    ChallengeTrackingStruct* t;

    amount = missions[scout->scoutMissionID].reward[0];
    for (i = 0; i < 9; i++) {
        ids[i] = inMemRoster[1][i].stats.CharID;
    }
    if (scout->scoutMissionID == 2) {
        cid = pitcher->charID;
    } else if (scout->scoutMissionID == 1) {
        cid = batter->charID;
    }
    for (i = 0; i < 9; i++) {
        if (cid == ids[i]) {
            t = &trackers[ids[i]];
            max = SCOUT_FLAG_MAX(t, rowA, rowB);
            if (max != 0) {
                scout->entries[i].max = max;
                scout->entries[i].achieved = t->scoutFlagsAchieved;
                scout->entries[i].amount = amount;
                amount = 0;
                scout->entries[i].active = 1;
                scout->entries[i].trackerIdx = ids[i];
            }
        }
    }
}

// .text:0x00163E94 size:0x578 mapped:0x807A2F28
void assignScoutFlagRewardRandom(void) {
    s16 ids[9];
    ScoutMission* missions = scoutMissionTable;
    ChallengeTrackingStruct* trackers = starMissionCompletionTracker;
    ScoutState* scout = &lbl_3_common_bss_37400;
    u8 rowB = ((u8*)trackers)[0x441C];
    u8 rowA = ((u8*)trackers)[0x4415];
    int k;
    int amount;
    BOOL enabled;

    amount = missions[scout->scoutMissionID].reward[0];
    fillRosterCharIDs(ids);
    snapshotScoutFlagProgress();
    k = rand() % 9;
    enabled = anyScoutFlagIncomplete();
    if (amount > 0 && enabled) {
        while (amount > 0) {
            if (ids[k] != -1) {
                ScoutPair* pair = &scout->pairs[k];
                ChallengeTrackingStruct* t = &trackers[ids[k]];
                if (pair->max != 0 && pair->cur < pair->max) {
                    scout->entries[k].max = SCOUT_FLAG_MAX(t, rowA, rowB);
                    scout->entries[k].achieved = t->scoutFlagsAchieved;
                    scout->entries[k].amount++;
                    scout->entries[k].active = 1;
                    scout->entries[k].trackerIdx = ids[k];
                    amount--;
                    pair->cur++;
                }
            }
            k = (k + 1) % 9;
            if (!anyScoutPairIncomplete()) {
                break;
            }
        }
    }
}

// .text:0x00163D34 size:0x160 mapped:0x807A2DC8
void snapshotScoutFlagProgress(void) {
    s16 ids[9];
    ChallengeTrackingStruct* trackers = starMissionCompletionTracker;
    ScoutState* scout = &lbl_3_common_bss_37400;
    u8 rowB = ((u8*)trackers)[0x441C];
    u8 rowA = ((u8*)trackers)[0x4415];
    s32 i;

    for (i = 0; i < 9; i++) {
        ids[i] = inMemRoster[1][i].stats.CharID;
    }
    for (i = 0; i < 9; i++) {
        if (ids[i] != -1) {
            ChallengeTrackingStruct* t = &trackers[ids[i]];
            if (SCOUT_FLAG_MAX(t, rowA, rowB) != 0) {
                scout->pairs[i].cur = t->scoutFlagsAchieved;
                scout->pairs[i].max = SCOUT_FLAG_MAX(t, rowA, rowB);
            }
        }
    }
}

// .text:0x00163BD4 size:0x160 mapped:0x807A2C68
BOOL anyScoutFlagIncomplete(void) {
    s16 ids[9];
    ChallengeTrackingStruct* trackers = starMissionCompletionTracker;
    u8 rowB = ((u8*)trackers)[0x441C];
    u8 rowA = ((u8*)trackers)[0x4415];
    s8 max;
    int i;
    ChallengeTrackingStruct* t;
    BOOL found;

    fillRosterCharIDs(ids);
    found = FALSE;
    for (i = 0; i < 9; i++) {
        if (ids[i] != -1) {
            t = &trackers[ids[i]];
            max = SCOUT_FLAG_MAX(t, rowA, rowB);
            if (max != 0 && (s8)t->scoutFlagsAchieved < max) {
                found = TRUE;
            }
        }
    }
    return found;
}

// .text:0x00163A7C size:0x158 mapped:0x807A2B10
BOOL isScoutTargetFlagAvailable(void) {
    s16 ids[9];
    BOOL found;
    ChallengeTrackingStruct* trackers = starMissionCompletionTracker;
    ScoutState* scout = &lbl_3_common_bss_37400;
    InMemBatterType* batter = &g_Batter;
    InMemPitcherType* pitcher = &g_Pitcher;
    u8 rowB = ((u8*)trackers)[0x441C];
    u8 rowA = ((u8*)trackers)[0x4415];
    int cid;
    int i;

    fillRosterCharIDs(ids);
    if (scout->scoutMissionID == 2) {
        cid = pitcher->charID;
    } else if (scout->scoutMissionID == 1) {
        cid = batter->charID;
    }
    for (i = 0; i < 9; i++) {
        if (cid == ids[i]) {
            ChallengeTrackingStruct* t = &trackers[ids[i]];
            if (SCOUT_FLAG_MAX(t, rowA, rowB) != 0) {
                found = TRUE;
            }
        }
    }
    return found;
}

// .text:0x00163948 size:0x134 mapped:0x807A29DC
BOOL anyScoutPairIncomplete(void) {
    s16 ids[9];
    ScoutState* scout = &lbl_3_common_bss_37400;
    BOOL found;
    s32 i;

    for (i = 0; i < 9; i++) {
        ids[i] = inMemRoster[1][i].stats.CharID;
    }
    found = FALSE;
    for (i = 0; i < 9; i++) {
        if (ids[i] != -1) {
            ScoutPair* pair = &scout->pairs[i];
            if (pair->max != 0 && pair->cur < pair->max) {
                found = TRUE;
            }
        }
    }
    return found;
}

// .text:0x001637EC size:0x15C mapped:0x807A2880
void recruitWholeTeamAfterMercy(void) {
    s16 ids[9];
    ChallengeTrackingStruct* trackers = starMissionCompletionTracker;
    u8 rowA;
    u8 rowB;
    s8 max;
    int i;
    ChallengeTrackingStruct* t;

    rowB = ((u8*)trackers)[0x441C];
    rowA = ((u8*)trackers)[0x4415];

    fillRosterCharIDs(ids);
    for (i = 0; i < 9; i++) {
        if (ids[i] != -1) {
            t = &trackers[ids[i]];
            max = SCOUT_FLAG_MAX(t, rowA, rowB);
            if (max != 0 && (s8)t->scoutFlagsAchieved < max) {
                t->scoutFlagsAchieved = max;
            }
        }
    }
}

// .text:0x00162D54 size:0xA98 mapped:0x807A1DE8
void starMissionsWholeGame(void) {
    ScoutState* scout = &lbl_3_common_bss_37400;
    int slot = scout->humanTeam ^ g_GameLogic.homeTeamInd;
    int i;
    int p;
    u8 difficulty;
    StatisticsBatter* batterStats;

    if (g_d_GameSettings.bJMatchInd != 1) {
        if (storedInningInfo._4C[slot] == 1) {
            CharacterStats* roster = inMemRoster[scout->humanTeam];
            s8 starter = StatsScreenScores.pitcherLog[scout->humanTeam][0].pitcher;
            CharStaticIndex* ci = &characterStaticIndexes[roster[starter].stats.CharID];
            ChallengeTrackingStruct* ct = MISSION_TRACKER(ci);
            StarMissionRequirement* req = MISSION_REQS(&characterStaticIndexes[ci->trackerIdx]);
            u8* noHitter = &storedInningInfo.noHitterTracker[slot];
            u8* pitched = &PitcherStats_P1_P2[scout->humanTeam][starter]._13[5];
            u8* captainRow = &characterStaticIndexes[Static_Stats_Tables.captainSelectedID[1]].requirementRow;
            for (i = 0; i < 10; i++) {
                if (ct->inGameMissionTracker[i].starMissionStatus >= 0) {
                    int type = req[i].type;
                    if (type == 7) {
                        if (*noHitter == 1) {
                            ct->inGameMissionTracker[i].starMissionStatus = -1;
                        }
                    } else if (type == 9 || type == 6) {
                        if (*pitched != 0) {
                            if (type == 6) {
                                if (req[i].target == *captainRow) {
                                    ct->inGameMissionTracker[i].starMissionStatus = -1;
                                }
                            } else {
                                ct->inGameMissionTracker[i].starMissionStatus = -1;
                            }
                        }
                    } else if (type == 8) {
                        ct->inGameMissionTracker[i].starMissionStatus = -1;
                    }
                }
            }
        }

        batterStats = BatterStats_P1_P2[scout->humanTeam];
        for (p = 0; p < 9; p++) {
            CharStaticIndex* ci = &characterStaticIndexes[inMemRoster[scout->humanTeam][p].stats.CharID];
            ChallengeTrackingStruct* ct = MISSION_TRACKER(ci);
            StarMissionRequirement* req = MISSION_REQS(&characterStaticIndexes[ci->trackerIdx]);
            for (i = 0; i < 10; i++) {
                if (ct->inGameMissionTracker[i].starMissionStatus >= 0) {
                    if (req[i].type == 0x19 && batterStats[p].AtBats != 0) {
                        if ((batterStats[p].Hits * 10) / batterStats[p].AtBats >= req[i].target) {
                            ct->inGameMissionTracker[i].starMissionStatus = -1;
                        }
                    }
                    if (req[i].type == 0x1A && batterStats[p].Strikeouts == 0) {
                        ct->inGameMissionTracker[i].starMissionStatus = -1;
                    }
                }
            }
        }

        if (g_Scores.winnerCd == slot) {
            CharStaticIndex* mvp = &characterStaticIndexes[StatsScreenScores.mvpCharID];
            ChallengeTrackingStruct* ct = MISSION_TRACKER(mvp);
            StarMissionRequirement* req = MISSION_REQS(mvp);
            for (i = 0; i < 10; i++) {
                if (ct->inGameMissionTracker[i].starMissionStatus >= 0 && req[i].type == 1) {
                    ct->inGameMissionTracker[i].starMissionStatus = -1;
                }
            }
            for (p = 0; p < 9; p++) {
                CharStaticIndex* ci = &characterStaticIndexes[inMemRoster[scout->humanTeam][p].stats.CharID];
                ct = MISSION_TRACKER(ci);
                req = MISSION_REQS(&characterStaticIndexes[ci->trackerIdx]);
                for (i = 0; i < 10; i++) {
                    if (ct->inGameMissionTracker[i].starMissionStatus >= 0 && req[i].type == 0 &&
                        g_d_GameSettings.StadiumID == req[i].target) {
                        ct->inGameMissionTracker[i].starMissionStatus = -1;
                    }
                }
            }
        } else {
            for (p = 0; p < 9; p++) {
                CharStaticIndex* ci = &characterStaticIndexes[inMemRoster[scout->humanTeam][p].stats.CharID];
                ChallengeTrackingStruct* ct = MISSION_TRACKER(ci);
                StarMissionRequirement* req = MISSION_REQS(&characterStaticIndexes[ci->trackerIdx]);
                for (i = 0; i < 10; i++) {
                    if (ct->inGameMissionTracker[i].starMissionStatus == -1 && (req[i].flags & 1)) {
                        ct->inGameMissionTracker[i].starMissionStatus = 0;
                    }
                }
            }
        }
    }

    difficulty = g_d_GameSettings.challengeDifficulty;
    for (p = 0; p < 9; p++) {
        CharStaticIndex* ci = &characterStaticIndexes[inMemRoster[scout->humanTeam][p].stats.CharID];
        ChallengeTrackingStruct* ct = MISSION_TRACKER(ci);
        StarMissionRequirement* req = MISSION_REQS(&characterStaticIndexes[ci->trackerIdx]);
        for (i = 0; i < 10; i++) {
            if (ct->inGameMissionTracker[i].starMissionStatus == -1) {
                if (req[i].flags & 2) {
                    if (difficulty < 1) {
                        ct->inGameMissionTracker[i].starMissionStatus = 0;
                    }
                } else if (req[i].flags & 4) {
                    if (difficulty < 2) {
                        ct->inGameMissionTracker[i].starMissionStatus = 0;
                    }
                } else if (req[i].flags & 8) {
                    if (difficulty < 3) {
                        ct->inGameMissionTracker[i].starMissionStatus = 0;
                    }
                }
            }
        }
    }

    for (p = 0; p < 9; p++) {
        CharStaticIndex* ci = &characterStaticIndexes[inMemRoster[scout->humanTeam][p].stats.CharID];
        ChallengeTrackingStruct* ct = MISSION_TRACKER(ci);
        StarMissionRequirement* req = MISSION_REQS(&characterStaticIndexes[ci->trackerIdx]);
        for (i = 0; i < 10; i++) {
            if (ct->inGameMissionTracker[i].starMissionStatus == -1) {
                if ((req[i].flags & 0x800) && Static_Stats_Tables.captainSelectedID[1] != 9 &&
                    *(s16*)(TRACKER_RAW + 0x16C2) != 0x2A) {
                    ct->inGameMissionTracker[i].starMissionStatus = 0;
                }
            }
        }
    }

    for (p = 0; p < 54; p++) {
        for (i = 0; i < 10; i++) {
            if (starMissionCompletionTracker[p].inGameMissionTracker[i].starMissionStatus <= -1) {
                starMissionCompletionTracker[p].inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
            } else {
                starMissionCompletionTracker[p].inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_NOT_COMPLETED;
            }
        }
    }
}

// .text:0x0016230C size:0xA48 mapped:0x807A13A0
void starMissionsOffensive_StarChange_DoublePlay(int result, int rbis) {
    ScoutState* scout = &lbl_3_common_bss_37400;
    int i;
    int k;
    int f;
    int outsBefore;
    int outs;

    if (scout->humanTeam == g_GameLogic.teamFielding) {
        CharStaticIndex* pc = &characterStaticIndexes[g_Pitcher.charID];
        ChallengeTrackingStruct* ct = MISSION_TRACKER(pc);
        StarMissionRequirement* req = MISSION_REQS(pc);
        for (i = 0; i < 10; i++) {
            if (ct->inGameMissionTracker[i].starMissionStatus >= 0) {
                StarMissionRequirement* mreq = &req[i];
                BOOL done = FALSE;
                if (mreq->type == 2) {
                    if (g_GameLogic.IsStarChance == 2) {
                        MISSION_ADVANCE(ct, req, i);
                    }
                } else {
                    u8* batterRow = &characterStaticIndexes[g_Batter.charID].requirementRow;
                    for (k = 4; k < 13; k++) {
                        if (mreq->type == k) {
                            switch (k) {
                            case 4:
                                if (result == AT_BAT_RESULT_STRIKEOUT && mreq->target == *batterRow) {
                                    done = TRUE;
                                }
                                break;
                            case 5:
                                if (result == AT_BAT_RESULT_HIT_BY_PITCH && mreq->target == *batterRow) {
                                    done = TRUE;
                                }
                                break;
                            case 10:
                                if (result == AT_BAT_RESULT_STRIKEOUT) {
                                    ct->inGameMissionTracker[i].starMissionStatus++;
                                    if (ct->inGameMissionTracker[i].starMissionStatus >= mreq->target) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            }
                            if (done) {
                                ct->inGameMissionTracker[i].starMissionStatus = -1;
                            }
                        }
                    }
                }
            }
        }

        outsBefore = g_Strikes.storedOuts;
        outs = g_Strikes.outs;
        for (f = 0; f < 9; f++) {
            CharStaticIndex* fc = &characterStaticIndexes[g_Fielders[f].CharID];
            ct = MISSION_TRACKER(fc);
            req = MISSION_REQS(fc);
            for (i = 0; i < 10; i++) {
                StarMissionRequirement* mreq = &req[i];

                if (ct->inGameMissionTracker[i].starMissionStatus >= 0 && mreq->type == 0x2B &&
                    outsBefore + 2 <= outs) {
                    int flags = 0;
                    int m;
                    for (m = 0; m < 5; m++) {
                        s8 who = storedInningInfo.catches[m].fielderIndex;
                        if (who >= 0) {
                            if (who == f) {
                                flags |= 1;
                            } else if (mreq->target ==
                                       characterStaticIndexes[g_Fielders[who].CharID].requirementRow) {
                                flags |= 0x10;
                            }
                            if (m == 1 && storedInningInfo.catches[m].outsDuringPossession == 2) {
                                break;
                            }
                        }
                    }
                    if (flags == 0x11) {
                        ct->inGameMissionTracker[i].starMissionStatus = -1;
                    }
                }
            }
        }
    }

    if (scout->humanTeam == g_GameLogic.teamBatting) {
        CharStaticIndex* bc = &characterStaticIndexes[g_Batter.charID];
        ChallengeTrackingStruct* ct = MISSION_TRACKER(bc);
        StarMissionRequirement* req = MISSION_REQS(bc);
        InMemPitcherType* pitcher = &g_Pitcher;
        GameScoresControlsStruct* scores = &g_Scores;
        InMemRunnerType* runners = g_Runners;
        InMemBallType* ball = &g_Ball;
        int j;

        for (i = 0; i < 10; i++) {
            if (ct->inGameMissionTracker[i].starMissionStatus >= 0) {
                BOOL done = FALSE;
                if (req[i].type == 2) {
                    if (g_GameLogic.IsStarChance == 3 || g_GameLogic.stadiumStarObtained != 0) {
                        MISSION_ADVANCE(ct, req, i);
                    }
                } else {
                    int pitcherChar = pitcher->charID;
                    CharStaticIndex* pc = &characterStaticIndexes[pitcherChar];
                    int inning = g_Scores.Inning;
                    int runsBefore = scores->_A0;
                    CharacterStats* roster = inMemRoster[scout->humanTeam];
                    StatisticsBatter* bs = BatterStats_P1_P2[scout->humanTeam];
                    u8 lastRunnerStatus = runners[3].runnerOnFieldOrOutOrScored;
                    u8 lastRunnerForced = runners[3].furthestBaseForcedToGoToOnWalk;
                    u8 starSwing = ball->currentStarSwing2;
                    u8 hitType = g_Batter.hitGeneralType;
                    f32 chargeUp = g_Batter.chargeUp;
                    u8 nonCaptainSwing = g_Batter.nonCaptainStarSwingActivated;

                    for (k = 13; k <= 32; k++) {
                        if (req[i].type == k) {
                            switch (k) {
                            case 13:
                                if (result == AT_BAT_RESULT_HOME_RUN && inning == req[i].target) {
                                    done = TRUE;
                                }
                                break;
                            case 14:
                                if (result == AT_BAT_RESULT_HOME_RUN && rbis >= req[i].target) {
                                    done = TRUE;
                                }
                                break;
                            case 15:
                                if (result >= req[i].target + 6 && result <= AT_BAT_RESULT_HOME_RUN) {
                                    done = TRUE;
                                }
                                break;
                            case 16:
                                if (result >= AT_BAT_RESULT_SINGLE && result <= AT_BAT_RESULT_HOME_RUN && pitcherChar == req[i].target) {
                                    done = TRUE;
                                }
                                break;
                            case 17:
                                if (result == AT_BAT_RESULT_HOME_RUN && req[i].target == pc->requirementRow) {
                                    done = TRUE;
                                }
                                break;
                            case 18:
                                if (rbis != 0 && req[i].target == pc->requirementRow) {
                                    done = TRUE;
                                }
                                break;
                            case 19:
                                if (result >= AT_BAT_RESULT_SINGLE && result <= AT_BAT_RESULT_HOME_RUN) {
                                    ct->inGameMissionTracker[i].starMissionStatus++;
                                    if (ct->inGameMissionTracker[i].starMissionStatus >= req[i].target) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            case 20:
                            case 21:
                                if (result == AT_BAT_RESULT_BUNT) {
                                    if (k == 21) {
                                        if (g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total >
                                                runsBefore &&
                                            lastRunnerStatus != RUNNER_STATUS_NONE && lastRunnerForced != 0) {
                                            ct->inGameMissionTracker[i].starMissionStatus++;
                                            if (ct->inGameMissionTracker[i].starMissionStatus >= req[i].target) {
                                                done = TRUE;
                                            }
                                        }
                                    } else {
                                        ct->inGameMissionTracker[i].starMissionStatus++;
                                        if (ct->inGameMissionTracker[i].starMissionStatus >= req[i].target) {
                                            done = TRUE;
                                        }
                                    }
                                }
                                break;
                            case 22:
                                if (rbis != 0) {
                                    ct->inGameMissionTracker[i].starMissionStatus += rbis;
                                    if (ct->inGameMissionTracker[i].starMissionStatus >= req[i].target) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            case 23:
                                if (result == AT_BAT_RESULT_HOME_RUN) {
                                    ct->inGameMissionTracker[i].starMissionStatus++;
                                    if (ct->inGameMissionTracker[i].starMissionStatus >= req[i].target) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            case 30:
                                if (result == AT_BAT_RESULT_HOME_RUN) {
                                    for (j = 0; j < 9; j++) {
                                        if (req[i].target ==
                                                characterStaticIndexes[roster[j].stats.CharID].requirementRow &&
                                            bs[j].HomeRuns != 0) {
                                            ct->inGameMissionTracker[i].starMissionStatus = -1;
                                            break;
                                        }
                                    }
                                }
                                break;
                            case 24:
                                if (starSwing != 0 && rbis != 0) {
                                    ct->inGameMissionTracker[i].starMissionStatus += rbis;
                                    if (ct->inGameMissionTracker[i].starMissionStatus >= req[i].target) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            case 27:
                                if (result >= AT_BAT_RESULT_SINGLE && result <= AT_BAT_RESULT_HOME_RUN && hitType == BAT_CONTACT_TYPE_CHARGE && chargeUp >= 1.0f &&
                                    nonCaptainSwing == 0) {
                                    ct->inGameMissionTracker[i].starMissionStatus++;
                                    if (ct->inGameMissionTracker[i].starMissionStatus >= req[i].target) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            case 28:
                                if (result == AT_BAT_RESULT_HOME_RUN) {
                                    int count = 0;
                                    int r;
                                    for (r = 1; r < 4; r++) {
                                        if (g_Runners[r].runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE &&
                                            (g_Runners[r].charID == 3 || g_Runners[r].charID == 0x27)) {
                                            count++;
                                        }
                                    }
                                    if (count == 2) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            case 29:
                                if (result >= AT_BAT_RESULT_SINGLE && result <= AT_BAT_RESULT_HOME_RUN && hitType == BAT_CONTACT_TYPE_BUNT) {
                                    ct->inGameMissionTracker[i].starMissionStatus++;
                                    if (ct->inGameMissionTracker[i].starMissionStatus >= req[i].target) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            }
                            if (done) {
                                ct->inGameMissionTracker[i].starMissionStatus = -1;
                            }
                        }
                    }
                }
            }
        }

        if (result == AT_BAT_RESULT_HOME_RUN) {
            CharacterStats* roster = inMemRoster[scout->humanTeam];
            StatisticsBatter* bs = BatterStats_P1_P2[scout->humanTeam];

            for (j = 0; j < 9; j++) {
                CharStaticIndex* rc = &characterStaticIndexes[roster[j].stats.CharID];
                ChallengeTrackingStruct* rct = MISSION_TRACKER(rc);
                StarMissionRequirement* rreq = MISSION_REQS(rc);
                for (i = 0; i < 10; i++) {
                    if (rct->inGameMissionTracker[i].starMissionStatus >= 0 && rreq[i].type == 0x1E &&
                        rreq[i].target == characterStaticIndexes[g_Batter.charID].requirementRow && bs[j].HomeRuns != 0) {
                        rct->inGameMissionTracker[i].starMissionStatus = -1;
                    }
                }
            }
        }
    }
}

// .text:0x00162080 size:0x28C mapped:0x807A1114
void challenge_postPitchStarMissionTracking(void) {
    ScoutState* scout = &lbl_3_common_bss_37400;
    int i;

    if (scout->humanTeam == g_GameLogic.teamFielding) {
        CharStaticIndex* pc = &characterStaticIndexes[g_Pitcher.charID];
        ChallengeTrackingStruct* ct = &starMissionCompletionTracker[pc->trackerIdx];
        StarMissionRequirement* req = MISSION_REQS(pc);
        for (i = 0; i < 10; i++) {
            if (ct->inGameMissionTracker[i].starMissionStatus >= 0) {
                StarMissionRequirement* mreq = &req[i];
                BOOL done = FALSE;
                if (mreq->type == 3) {
                    if (g_Pitcher.starPitchType != 0) {
                        ct->inGameMissionTracker[i].starMissionStatus |= 1;
                        if (ct->inGameMissionTracker[i].starMissionStatus == 0x11) {
                            ct->inGameMissionTracker[i].starMissionStatus = -1;
                        }
                    }
                } else {
                    int k;
                    u8 starPitch = g_Pitcher.starPitchType;
                    u8 chargePitch = g_Pitcher.ChargePitchType;
                    for (k = 4; k < 13; k++) {
                        if (mreq->type == k) {
                            switch (k) {
                            case 11:
                                if (starPitch != 0) {
                                    ct->inGameMissionTracker[i].starMissionStatus++;
                                    if (ct->inGameMissionTracker[i].starMissionStatus >= mreq->target) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            case 12:
                                if (chargePitch == 3) {
                                    ct->inGameMissionTracker[i].starMissionStatus++;
                                    if (ct->inGameMissionTracker[i].starMissionStatus >= mreq->target) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            }
                            if (done) {
                                ct->inGameMissionTracker[i].starMissionStatus = -1;
                            }
                        }
                    }
                }
            }
        }
    }

    if (scout->humanTeam == g_GameLogic.teamBatting) {
        CharStaticIndex* bc = &characterStaticIndexes[g_Batter.charID];
        ChallengeTrackingStruct* ct = &starMissionCompletionTracker[bc->trackerIdx];
        StarMissionRequirement* req = MISSION_REQS(bc);
        u8 starSwing = g_Ball.currentStarSwing2;
        u8 starChance = g_GameLogic.IsStarChance;
        u8 stadiumStar = g_GameLogic.stadiumStarObtained;
        for (i = 0; i < 10; i++) {
            if (ct->inGameMissionTracker[i].starMissionStatus >= 0) {
                if (req[i].type == 3 && starSwing != 0) {
                    ct->inGameMissionTracker[i].starMissionStatus |= 0x10;
                    if (ct->inGameMissionTracker[i].starMissionStatus == 0x11) {
                        ct->inGameMissionTracker[i].starMissionStatus = -1;
                    }
                }
                if (req[i].type == 2) {
                    if (starChance == 3 || stadiumStar != 0) {
                        ct->inGameMissionTracker[i].starMissionStatus++;
                        if (ct->inGameMissionTracker[i].starMissionStatus >= req[i].target) {
                            ct->inGameMissionTracker[i].starMissionStatus = -1;
                        }
                    }
                }
            }
        }
    }
}

// .text:0x00161588 size:0xAF8 mapped:0x807A061C
void starMissionsQuantityBased(int missionType, int rosterLocation) {
    s16 charID = inMemRoster[lbl_3_common_bss_37400.humanTeam][rosterLocation].stats.CharID;
    u8 trackerIdx = characterStaticIndexes[charID].trackerIdx;
    u8 requirementRow = characterStaticIndexes[charID].requirementRow;
    ChallengeTrackingStruct* ct;
    StarMissionRequirement* req;
    int i;

#define QUANTITY_SIMPLE(reqType)                                   \
    ct = &starMissionCompletionTracker[trackerIdx];                \
    req = starMissionRequirementsTable[requirementRow];            \
    for (i = 0; i < 10; i++) {                                     \
        if (ct->inGameMissionTracker[i].starMissionStatus >= 0) {  \
            switch (req[i].type) {                                 \
            case (reqType):                                        \
                MISSION_ADVANCE(ct, req, i);                       \
                break;                                             \
            }                                                      \
        }                                                          \
    }

    switch (missionType) {
    case 0:
        QUANTITY_SIMPLE(0x1F)
        break;
    case 1:
        QUANTITY_SIMPLE(0x20)
        break;
    case 3:
        QUANTITY_SIMPLE(0x25)
        break;
    case 2:
        ct = &starMissionCompletionTracker[trackerIdx];
        req = starMissionRequirementsTable[requirementRow];
        {
            int contact = g_Ball.AtBat_ContactResult;
            u8 starSwing = g_Ball.currentStarSwing;
            for (i = 0; i < 10; i++) {
                if (ct->inGameMissionTracker[i].starMissionStatus >= 0) {
                    switch (req[i].type) {
                    case 0x21:
                        MISSION_ADVANCE(ct, req, i);
                        break;
                    case 0x22:
                        if (contact == BALL_RESULT_TYPE_CAUGHT) {
                            MISSION_ADVANCE(ct, req, i);
                        }
                        break;
                    case 0x23:
                        break;
                    case 0x24:
                        if (starSwing == 5 || starSwing == 6) {
                            MISSION_ADVANCE(ct, req, i);
                        }
                        break;
                    }
                }
            }
        }
        break;
    case 4:
        QUANTITY_SIMPLE(0x23)
        break;
    case 5: {
        int contact;
        ct = &starMissionCompletionTracker[trackerIdx];
        req = starMissionRequirementsTable[requirementRow];
        contact = g_Ball.AtBat_ContactResult;
        for (i = 0; i < 10; i++) {
            if (ct->inGameMissionTracker[i].starMissionStatus >= 0) {
                switch (req[i].type) {
                case 0x26:
                    if (contact == BALL_RESULT_TYPE_CAUGHT) {
                        MISSION_ADVANCE(ct, req, i);
                    }
                    break;
                }
            }
        }
        break;
    }
    case 6:
        QUANTITY_SIMPLE(0x27)
        break;
    case 7:
        ct = &starMissionCompletionTracker[trackerIdx];
        req = starMissionRequirementsTable[requirementRow];
        {
            s16* thrownTo = &g_Fielders[g_Ball.fielderBeingThrownTo].CharID;
            for (i = 0; i < 10; i++) {
                if (ct->inGameMissionTracker[i].starMissionStatus >= 0) {
                    switch (req[i].type) {
                    case 0x28:
                        if (req[i].target == characterStaticIndexes[*thrownTo].requirementRow) {
                            ct->inGameMissionTracker[i].starMissionStatus = -1;
                        }
                        break;
                    }
                }
            }
        }
        break;
    case 8:
        QUANTITY_SIMPLE(0x29)
        break;
    case 9: {
        int contact;
        ct = &starMissionCompletionTracker[trackerIdx];
        req = starMissionRequirementsTable[requirementRow];
        contact = g_Ball.AtBat_ContactResult;
        for (i = 0; i < 10; i++) {
            if (ct->inGameMissionTracker[i].starMissionStatus >= 0) {
                switch (req[i].type) {
                case 0x2A:
                    if (contact == BALL_RESULT_TYPE_CAUGHT) {
                        MISSION_ADVANCE(ct, req, i);
                    }
                    break;
                }
            }
        }
        break;
    }
    case 10:
        QUANTITY_SIMPLE(0x2C)
        break;
    case 11:
        QUANTITY_SIMPLE(0x2D)
        break;
    case 12:
        QUANTITY_SIMPLE(0x2E)
        break;
    }
#undef QUANTITY_SIMPLE
}

// .text:0x00161078 size:0x510
void starMissionsMinigamesTotalPoints(void) {
    u8 slot = g_d_GameSettings._35;
    u8 charID = g_Minigame.playerSlots.charID[slot];
    u8 trackerIdx = characterStaticIndexes[charID].trackerIdx;
    u8 requirementRow = characterStaticIndexes[charID].requirementRow;
    ChallengeTrackingStruct* ct = &starMissionCompletionTracker[trackerIdx];
    StarMissionRequirement* req = starMissionRequirementsTable[requirementRow];
    u8 mode = g_Minigame.GameMode_MiniGame;
    u8 difficulty = g_d_GameSettings.challengeDifficulty;
    int i;
    int j;
    int k;

    for (j = 0; j < 10; j++) {
        s8 status = ct->inGameMissionTracker[j].starMissionStatus;

        if (status == -2) {
            continue;
        }
        if (status == -1) {
            if (req[j].flags & 2) {
                if (difficulty < 1) {
                    ct->inGameMissionTracker[j].starMissionStatus = 0;
                }
            } else if (req[j].flags & 4) {
                if (difficulty < 2) {
                    ct->inGameMissionTracker[j].starMissionStatus = 0;
                }
            } else if (req[j].flags & 8) {
                if (difficulty < 3) {
                    ct->inGameMissionTracker[j].starMissionStatus = 0;
                }
            }
            if (req[j].flags & 1) {
                if (g_Minigame.playerSlots.rank[slot] != 1) {
                    ct->inGameMissionTracker[j].starMissionStatus = 0;
                }
            }
            continue;
        }

        if (req[j].flags & 2) {
            if (difficulty < 1) {
                continue;
            }
        } else if (req[j].flags & 4) {
            if (difficulty < 2) {
                continue;
            }
        } else if (req[j].flags & 8) {
            if (difficulty < 3) {
                continue;
            }
        }
        if ((req[j].flags & 1) && g_Minigame.playerSlots.rank[slot] != 1) {
            continue;
        }
        {
            BOOL anyModeFlag = FALSE;
            BOOL modeMatches = FALSE;

            for (k = 0; k < 7; k++) {
                if (req[j].flags & (0x10 << k)) {
                    anyModeFlag = TRUE;
                    if (mode == k) {
                        modeMatches = TRUE;
                    }
                }
            }
            if (anyModeFlag && !modeMatches) {
                continue;
            }
        }

        switch (req[j].type) {
        case 0x2F:
            if (g_Minigame.playerSlots.rank[slot] <= req[j].target) {
                ct->inGameMissionTracker[j].starMissionStatus = -1;
            }
            break;
        case 0x30: {
            int target = req[j].target;

            if (mode == 1 || mode == 3) {
                target *= 100;
            } else if (mode == 0 || mode == 2) {
                target *= 10;
            }
            if (g_Minigame.miniGameCurrentPoints[slot] >= target) {
                ct->inGameMissionTracker[j].starMissionStatus = -1;
            }
            break;
        }
        case 0x31: {
            int matches = 0;
            int ahead = 0;

            for (i = 0; i < 4; i++) {
                if (g_Minigame.playerSlots.characterIndex[i] >= 0 && i != slot) {
                    if (characterStaticIndexes[g_Minigame.playerSlots.charID[i]].requirementRow == req[j].target) {
                        matches++;
                        if (g_Minigame.playerSlots.rank[slot] < g_Minigame.playerSlots.rank[i]) {
                            ahead++;
                        }
                    }
                }
            }
            if (matches != 0 && ahead == matches && g_Minigame.playerSlots.rank[slot] == 1) {
                ct->inGameMissionTracker[j].starMissionStatus = -1;
            }
            break;
        }
        case 0x36:
            if (mode == 5 && g_Minigame._1CB1[slot] <= req[j].target) {
                ct->inGameMissionTracker[j].starMissionStatus = -1;
            }
            break;
        }
    }

    for (i = 0; i < 54; i++) {
        for (j = 0; j < 10; j++) {
            if (starMissionCompletionTracker[i].inGameMissionTracker[j].starMissionStatus <= -1) {
                starMissionCompletionTracker[i].inGameMissionTracker[j].starMissionStatus = -2;
            } else {
                starMissionCompletionTracker[i].inGameMissionTracker[j].starMissionStatus = 0;
            }
        }
    }
}

// .text:0x001608F0 size:0x788
void starMissionsMinigamesSpecialAction(int missionType, int points, int barrelsHit) {
    u8 charID = g_Minigame.playerSlots.charID[g_d_GameSettings._35];
    u8 trackerIdx = characterStaticIndexes[charID].trackerIdx;
    u8 requirementRow = characterStaticIndexes[charID].requirementRow;
    BOOL found = FALSE;
    int i;

    switch (missionType) {
    case 0: {
        ChallengeTrackingStruct* ct = &starMissionCompletionTracker[trackerIdx];
        StarMissionRequirement* req = starMissionRequirementsTable[requirementRow];
        for (i = 0; i < 10; i++) {
            if (ct->inGameMissionTracker[i].starMissionStatus >= 0 && req[i].type == 0x32 && points >= req[i].target) {
                found = TRUE;
                break;
            }
        }
        break;
    }
    case 1: {
        ChallengeTrackingStruct* ct = &starMissionCompletionTracker[trackerIdx];
        StarMissionRequirement* req = starMissionRequirementsTable[requirementRow];
        for (i = 0; i < 10; i++) {
            if (ct->inGameMissionTracker[i].starMissionStatus >= 0 && req[i].type == 0x33) {
                if (barrelsHit == 0) {
                    ct->inGameMissionTracker[i].starMissionStatus = 0;
                } else {
                    ct->inGameMissionTracker[i].starMissionStatus++;
                    if (ct->inGameMissionTracker[i].starMissionStatus >= req[i].target) {
                        found = TRUE;
                        break;
                    }
                }
            }
        }
        break;
    }
    case 2: {
        ChallengeTrackingStruct* ct = &starMissionCompletionTracker[trackerIdx];
        StarMissionRequirement* req = starMissionRequirementsTable[requirementRow];
        for (i = 0; i < 10; i++) {
            if (ct->inGameMissionTracker[i].starMissionStatus >= 0 && req[i].type == 0x34 && barrelsHit >= 15) {
                ct->inGameMissionTracker[i].starMissionStatus++;
                if (ct->inGameMissionTracker[i].starMissionStatus >= req[i].target) {
                    found = TRUE;
                    break;
                }
            }
        }
        break;
    }
    case 3: {
        ChallengeTrackingStruct* ct = &starMissionCompletionTracker[trackerIdx];
        StarMissionRequirement* req = starMissionRequirementsTable[requirementRow];
        for (i = 0; i < 10; i++) {
            if (ct->inGameMissionTracker[i].starMissionStatus >= 0 && req[i].type == 0x35 && points == 2) {
                ct->inGameMissionTracker[i].starMissionStatus++;
                if (ct->inGameMissionTracker[i].starMissionStatus >= req[i].target) {
                    found = TRUE;
                    break;
                }
            }
        }
        break;
    }
    case 5: {
        ChallengeTrackingStruct* ct = &starMissionCompletionTracker[trackerIdx];
        StarMissionRequirement* req = starMissionRequirementsTable[requirementRow];
        for (i = 0; i < 10; i++) {
            if (ct->inGameMissionTracker[i].starMissionStatus >= 0 && req[i].type == 0x37 && points == 4) {
                ct->inGameMissionTracker[i].starMissionStatus++;
                if (ct->inGameMissionTracker[i].starMissionStatus >= req[i].target) {
                    found = TRUE;
                    break;
                }
            }
        }
        break;
    }
    case 6: {
        ChallengeTrackingStruct* ct = &starMissionCompletionTracker[trackerIdx];
        StarMissionRequirement* req = starMissionRequirementsTable[requirementRow];
        for (i = 0; i < 10; i++) {
            if (ct->inGameMissionTracker[i].starMissionStatus >= 0 && req[i].type == 0x38) {
                ct->inGameMissionTracker[i].starMissionStatus++;
                if (ct->inGameMissionTracker[i].starMissionStatus >= req[i].target) {
                    found = TRUE;
                    break;
                }
            }
        }
        break;
    }
    case 7: {
        ChallengeTrackingStruct* ct = &starMissionCompletionTracker[trackerIdx];
        StarMissionRequirement* req = starMissionRequirementsTable[requirementRow];
        for (i = 0; i < 10; i++) {
            if (ct->inGameMissionTracker[i].starMissionStatus >= 0 && req[i].type == 0x39 && points == req[i].target) {
                found = TRUE;
                break;
            }
        }
        break;
    }
    }

    if (found) {
        starMissionCompletionTracker[trackerIdx].inGameMissionTracker[i].starMissionStatus = -1;
    }
}
