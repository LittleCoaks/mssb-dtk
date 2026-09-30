#define SQRT2_LINKAGE static
#include "game/match_setup/star_missions.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/rand.h"
#include "game/minigame/pitching_machine.h"
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
    /*0x3*/ u8 active;
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

extern u8 lbl_80109410[0x6D8];

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

#define SCOUT_FLAG_MAX(t, rowA, rowB) (((s8*)(t)->scoutFlagPointer + 4)[(rowA) * 6 + (rowB)])

#define MISSION_TRACKER(ci) (starMissionCompletionTracker[(ci)->trackerIdx].inGameMissionTracker)
#define MISSION_REQS(ci) (starMissionRequirementsTable[(ci)->requirementRow])

#define MISSION_ADVANCE(tr, req, i)                                                    \
    (tr)[i].starMissionStatus++;                                                       \
    if ((s8)(tr)[i].starMissionStatus >= (req)[i].target) {                            \
        (tr)[i].starMissionStatus = -1;                                                \
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
        loadPitchingMachineModel();
    }
}

// .text:0x00165D24 size:0x688 mapped:0x807A4DB8
BOOL decideScoutFlagMission(void) {
    ScoutState* scout = &lbl_3_common_bss_37400;
    int idx = 0;
    ChallengeTrackingStruct* trackers = starMissionCompletionTracker;
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
        case 8:
            if (storedInningInfo.nBattersThisInning2 >= 4 ||
                g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].byInning[g_Scores.Inning - 1] != 0) {
                scout->scoutMissionID = 0;
                scout->scoutFlag = 0;
            }
            break;
        case 9:
        case 10:
            if (scout->targetRosterID != g_Runners[3].rosterID || g_Strikes.outs != 2) {
                scout->scoutMissionID = 0;
                scout->scoutFlag = 0;
            }
            break;
        case 11:
            if (scout->targetRosterID != g_Runners[1].rosterID) {
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
    } else if (g_GameLogic.teamBatting == g_d_GameSettings.humanTeamNumber) {
        if (g_RunningLogic._10 >= 2 &&
            g_Batter.rosterID == g_GameLogic.Team_CaptainRosterLoc[g_GameLogic.teamBatting] &&
            g_Pitcher.rosterID == g_GameLogic.Team_CaptainRosterLoc[g_GameLogic.teamFielding]) {
            if (shouldScoutMissionBeEnabled(3)) {
                scout->scoutMissionID = 3;
            }
        } else if (g_RunningLogic._10 >= 2 &&
                   g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total <
                       g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total &&
                   g_Scores._A6 <= 3) {
            if (shouldScoutMissionBeEnabled(4)) {
                scout->scoutMissionID = 4;
            }
        } else if ((g_RunningLogic._00 & 0x1000) && g_Strikes.outs <= 1 &&
                   (g_Batter.characterClass == 0 || g_Batter.characterClass == 1)) {
            if (shouldScoutMissionBeEnabled(9)) {
                scout->scoutMissionID = 9;
            }
        } else if ((g_RunningLogic._00 & 0x1000) && g_Strikes.outs <= 1 &&
                   (g_Batter.characterClass == 2 || g_Batter.characterClass == 3)) {
            if (shouldScoutMissionBeEnabled(10)) {
                scout->scoutMissionID = 10;
            }
        } else if (g_RunningLogic._00 == 0x11 &&
                   inMemRoster[g_GameLogic.teamBatting][g_Runners[1].rosterID].stats.CharacterClass == 2) {
            if (shouldScoutMissionBeEnabled(11)) {
                scout->scoutMissionID = 11;
            }
        } else {
            idx = g_Pitcher.scoutFlagRelated;
            if (idx != -1) {
                ChallengeTrackingStruct* t = &trackers[idx];
                s8 max = SCOUT_FLAG_MAX(t, rowA, rowB);
                if (max != 0 && (s8)t->scoutFlagsAchieved < max) {
                    if (shouldScoutMissionBeEnabled(2)) {
                        scout->scoutMissionID = 2;
                    }
                }
            }
        }
    } else if (g_GameLogic.teamBatting != g_d_GameSettings.humanTeamNumber) {
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
            idx = g_Batter.charIDForScoutFlagMission;
            if (idx != -1) {
                ChallengeTrackingStruct* t = &trackers[idx];
                s8 max = SCOUT_FLAG_MAX(t, rowA, rowB);
                if (max != 0 && (s8)t->scoutFlagsAchieved < max) {
                    if (shouldScoutMissionBeEnabled(1)) {
                        scout->scoutMissionID = 1;
                    }
                }
            }
        }
    }

    switch (scout->scoutMissionID) {
    case 9:
    case 10:
        scout->targetRosterID = g_Runners[3].rosterID;
        break;
    case 11:
        scout->targetRosterID = g_Runners[1].rosterID;
        break;
    }

    if (scout->scoutMissionID != 0) {
        fn_3_1658F0();
        if (scout->scoutMissionID == 2 || scout->scoutMissionID == 1) {
            fn_3_16440C();
        } else {
            fn_3_163E94();
        }
        *(s16*)(TRACKER_RAW + 0x43C0) = idx;
        TRACKER_RAW[0x44F1] = 1;
        animRelated[0xB3] = 1;
        g_GameLogic.IsStarChance = 0;
        animRelated[0xAC] = 0;
        scout->_4A = 0;
        return TRUE;
    }
    return FALSE;
}

#pragma dont_inline on
// .text:0x001659A0 size:0x384 mapped:0x807A4A34
BOOL shouldScoutMissionBeEnabled(int mission) {
    ScoutState* scout = &lbl_3_common_bss_37400;
#define missions ((ScoutMission*)(lbl_80109410 + 0x10))
    u8 rowA = SCOUT_ROW_A;
    BOOL enabled;
    int roll;
    int chance;

    if (scout->scoutMissionID == 2 || scout->scoutMissionID == 1) {
        enabled = fn_3_163A7C();
    } else {
        enabled = fn_3_163BD4();
    }
    if (!enabled) {
        return FALSE;
    }
    roll = rand() % 100;
    if (scout->_4A == 0) {
        chance = missions[mission].chanceA[rowA];
    } else {
        chance = missions[mission].chanceB[rowA];
    }
    return roll <= chance;
}
#undef missions
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
void fn_3_1658F0(void) {
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
void challengeModeRelated_checkScoutMissionSuccess(void) {
    ScoutState* scout = &lbl_3_common_bss_37400;
    ScoutMission* missions = (ScoutMission*)(lbl_80109410 + 0x10);
    int cnt = 0;
    BOOL flag = FALSE;
    ChallengeTrackingStruct* trackers = starMissionCompletionTracker;
    u8 rowB = ((u8*)trackers)[0x441C];
    u8 rowA = ((u8*)trackers)[0x4415];
    int id = scout->scoutMissionID;

    scout->scoutResult = 1;
    scout->baseReward = missions[id].reward[0];
    if (id <= 12) {
        switch (id) {
        case 0:
            break;
        case 1:
            if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != 0) {
                if (g_Strikes.outs >= 3) {
                    scout->scoutResult = 2;
                } else if (g_Pitcher.strikeOutOrWalk == 1) {
                    scout->scoutFlag = 0;
                } else {
                    scout->scoutResult = 0;
                }
            } else if ((g_Strikes.outs > g_Strikes.storedOuts && storedInningInfo.batterResultBase == 0) ||
                       g_Pitcher.strikeOutOrWalk == 1) {
                if (g_Pitcher.strikeOutOrWalk == 1 ||
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
            if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != 0) {
                if (g_Strikes.outs >= 3) {
                    scout->scoutFlag = 0;
                } else if (g_Pitcher.strikeOutOrWalk == 1) {
                    scout->scoutFlag = 0;
                } else {
                    scout->scoutResult = 0;
                }
            } else if (g_Strikes.howRunnerReachedBase == 1 || storedInningInfo.batterResultBase >= 1) {
                if (storedInningInfo.playResultCode == 0 && storedInningInfo.runnersTargetedWhileBatterForceable <= 0) {
                    if (storedInningInfo.tentativeBatterBase == 1) {
                        if (storedInningInfo.rbisWaitingToBeAddedToScore == 1) {
                            cnt = 1;
                        } else if (storedInningInfo.rbisWaitingToBeAddedToScore >= 2) {
                            cnt = 2;
                        } else {
                            cnt = 0;
                        }
                    } else if (storedInningInfo.tentativeBatterBase == 2) {
                        cnt = 1;
                    } else if (storedInningInfo.tentativeBatterBase >= 3) {
                        cnt = 2;
                    }
                    scout->scoutResult = 2;
                }
            }
            break;
        case 3:
            if (g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total > g_Scores._A0 ||
                g_Ball.deadBallReason == 1 ||
                ((g_Pitcher.strikeOutOrWalk == 2 || g_Pitcher.strikeOutOrWalk == 3) &&
                 g_RunningLogic.nOffensivePlayersAtStartOfPlay >= 4)) {
                scout->scoutResult = 2;
                scout->scoutFlag = 0;
            } else if (g_Strikes.outs >= 3 ||
                       (g_Strikes.outs == 2 && g_Pitcher.strikeOutOrWalk == 1 &&
                        g_FieldingLogic.liveBallBcOfPickoffOrStealCd == 0)) {
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
                ((g_Pitcher.strikeOutOrWalk == 2 || g_Pitcher.strikeOutOrWalk == 3) &&
                 g_RunningLogic.nOffensivePlayersAtStartOfPlay >= 4 && g_Scores._A0 == ours)) {
                scout->scoutResult = 2;
                scout->scoutFlag = 0;
            } else if (g_Strikes.outs >= 3 || (g_Strikes.outs == 2 && g_Pitcher.strikeOutOrWalk == 1)) {
                scout->scoutFlag = 0;
            } else {
                scout->scoutFlag = 1;
                scout->scoutResult = 0;
            }
            break;
        }
        case 5:
            if (g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total > g_Scores._A0 ||
                g_Ball.deadBallReason == 1 ||
                (g_RunningLogic._02 == 0x1111 && (g_Pitcher.strikeOutOrWalk == 2 || g_Pitcher.strikeOutOrWalk == 3))) {
                scout->scoutFlag = 0;
            } else if ((g_Strikes.outs >= 2 && g_Pitcher.strikeOutOrWalk == 1 &&
                        g_FieldingLogic.liveBallBcOfPickoffOrStealCd == 0) ||
                       g_Strikes.outs >= 3) {
                scout->scoutResult = 2;
                scout->scoutFlag = 0;
            } else {
                scout->scoutFlag = 1;
                scout->scoutResult = 0;
            }
            break;
        case 6:
            if (g_Strikes.outs >= g_Strikes.storedOuts + 2) {
                scout->scoutResult = 2;
                scout->scoutFlag = 0;
            } else if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != 0) {
                scout->scoutFlag = 1;
                scout->scoutResult = 0;
            } else {
                scout->scoutFlag = 0;
            }
            break;
        case 7:
            if (g_Pitcher.strikeOutOrWalk == 1) {
                scout->scoutResult = 2;
                scout->scoutFlag = 0;
            } else if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != 0) {
                if (g_Strikes.outs >= 3) {
                    scout->scoutFlag = 0;
                } else {
                    scout->scoutFlag = 1;
                    scout->scoutResult = 0;
                }
            }
            break;
        case 8: {
            int threw = 0;
            if (storedInningInfo.nBattersThisInning2 == 3) {
                if ((g_Strikes.outs >= 2 && g_Pitcher.strikeOutOrWalk == 1 &&
                     g_FieldingLogic.liveBallBcOfPickoffOrStealCd == 0) ||
                    g_Strikes.outs >= 3) {
                    scout->scoutResult = 2;
                    scout->scoutFlag = 0;
                    break;
                }
            }
            if (g_Ball.deadBallReason == 3) {
                if (g_RunningLogic._02 & 0x1100) {
                    threw = 1;
                }
            } else if (g_Ball.deadBallReason == 4) {
                if (g_RunningLogic._02 & 0x1100) {
                    threw = 1;
                } else {
                    if (g_Runners[1].runnerOnFieldOrOutOrScored == 1 && g_Runners[1].baseReachedAtTimeOfThrow >= 2) {
                        threw = 1;
                    }
                    if (g_Runners[0].runnerOnFieldOrOutOrScored == 1 && g_Runners[0].baseReachedAtTimeOfThrow >= 2) {
                        threw = 1;
                    }
                }
            }
            if (storedInningInfo.nBattersThisInning2 == 3 && g_FieldingLogic.liveBallBcOfPickoffOrStealCd == 0) {
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
            if (storedInningInfo.playResultCode == 1) {
                scout->scoutResult = 2;
                scout->scoutFlag = 0;
            } else if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != 0) {
                if (g_Strikes.outs >= 3) {
                    scout->scoutFlag = 0;
                } else if (g_Pitcher.strikeOutOrWalk == 1) {
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
                if (g_Runners[3].furthestBaseForcedToGoToOnWalk != 0) {
                    if (g_Ball.maybeBuntInd != 0) {
                        flag = TRUE;
                    }
                }
            }
            if (flag) {
                scout->scoutResult = 2;
                scout->scoutFlag = 0;
            } else if (g_FieldingLogic.liveBallBcOfPickoffOrStealCd != 0) {
                if (g_Strikes.outs >= 3) {
                    scout->scoutFlag = 0;
                } else if (g_Pitcher.strikeOutOrWalk == 1) {
                    scout->scoutFlag = 0;
                } else if (g_Runners[3].runnerOnFieldOrOutOrScored == 1) {
                    scout->scoutFlag = 1;
                    scout->scoutResult = 0;
                } else {
                    scout->scoutFlag = 0;
                }
            } else {
                scout->scoutFlag = 0;
            }
            break;
        case 11: {
            u8 fl = g_FieldingLogic.liveBallBcOfPickoffOrStealCd;
            u8 runnerStatus = 0;
            int found = 0;
            if (fl == 1 || fl == 2) {
                runnerStatus = g_Runners[1].runnerOnFieldOrOutOrScored;
                if (runnerStatus == 1 || runnerStatus == 3) {
                    if (g_Runners[1].currentBase > 1) {
                        found = 1;
                    }
                }
                if (runnerStatus == 2) {
                    found = 2;
                }
            }
            if (found == 2) {
                scout->scoutResult = 1;
                scout->scoutFlag = 0;
            } else if (found != 0) {
                scout->scoutResult = 2;
                scout->scoutFlag = 0;
            } else if (fl != 0) {
                if (g_Strikes.outs >= 3) {
                    scout->scoutFlag = 0;
                } else if (g_Pitcher.strikeOutOrWalk == 1) {
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
                if ((g_GameLogic.homeTeamInd ^ (g_d_GameSettings.humanTeamNumber == g_Scores.winnerCd)) != 0 &&
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
                } else if (g_Strikes.outs >= 2 && g_Pitcher.strikeOutOrWalk == 1) {
                    if ((g_Scores.scores[1].total > g_Scores.scores[0].total &&
                         scout->humanTeam == g_GameLogic.teamBatting) ||
                        (g_Scores.scores[1].total < g_Scores.scores[0].total &&
                         scout->humanTeam == g_GameLogic.teamFielding)) {
                        scout->scoutResult = 2;
                    }
                    scout->scoutFlag = 0;
                } else if (g_RunningLogic._10 == 4 &&
                           (g_Pitcher.strikeOutOrWalk == 2 || g_Pitcher.strikeOutOrWalk == 3)) {
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
    }

    if (scout->scoutResult == 2) {
        if (scout->scoutMissionID == 2 || scout->scoutMissionID == 1) {
            ChallengeTrackingStruct* t = &trackers[*(s16*)((u8*)trackers + 0x43C0)];
            s8 reward = missions[scout->scoutMissionID].reward[cnt];
            int i;
            for (i = 0; i < 9; i++) {
                if (scout->entries[i].active == 1) {
                    scout->entries[i].amount = reward;
                }
            }
            t->scoutFlagsAchieved += reward;
            if ((s8)t->scoutFlagsAchieved > SCOUT_FLAG_MAX(t, rowA, rowB)) {
                t->scoutFlagsAchieved = SCOUT_FLAG_MAX(t, rowA, rowB);
            }
        } else {
            fn_3_164554();
        }
    }
}

// .text:0x00164664 size:0x410 mapped:0x807A36F8
void fn_3_164664(void) {
    s16 ids[9];
    ScoutMission* missions = (ScoutMission*)(lbl_80109410 + 0x10);
    int amount = missions[lbl_3_common_bss_37400.scoutMissionID].reward[0];
    ChallengeTrackingStruct* trackers = starMissionCompletionTracker;
    u8 rowB = ((u8*)trackers)[0x441C];
    u8 rowA = ((u8*)trackers)[0x4415];
    int k = 0;

    fillRosterCharIDs(ids);
    if (amount > 0 && fn_3_163BD4()) {
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
            if (!fn_3_163BD4()) {
                break;
            }
        }
    }
}

// .text:0x00164554 size:0x110 mapped:0x807A35E8
void fn_3_164554(void) {
    s16 ids[9];
    ChallengeTrackingStruct* trackers = starMissionCompletionTracker;
    u8 rowB = ((u8*)trackers)[0x441C];
    u8 rowA = ((u8*)trackers)[0x4415];
    int i;

    fillRosterCharIDs(ids);
    for (i = 0; i < 9; i++) {
        if (ids[i] != -1 && lbl_3_common_bss_37400.entries[i].active == 1) {
            ChallengeTrackingStruct* t = &trackers[ids[i]];
            if (SCOUT_FLAG_MAX(t, rowA, rowB) != 0) {
                t->scoutFlagsAchieved += lbl_3_common_bss_37400.entries[i].amount;
                if ((s8)t->scoutFlagsAchieved > SCOUT_FLAG_MAX(t, rowA, rowB)) {
                    t->scoutFlagsAchieved = SCOUT_FLAG_MAX(t, rowA, rowB);
                }
            }
        }
    }
}

#pragma dont_inline on
// .text:0x0016440C size:0x148 mapped:0x807A34A0
void fn_3_16440C(void) {
    s16 ids[9];
    ScoutState* scout = &lbl_3_common_bss_37400;
    ScoutMission* missions = (ScoutMission*)(lbl_80109410 + 0x10);
    int amount = missions[scout->scoutMissionID].reward[0];
    ChallengeTrackingStruct* trackers = starMissionCompletionTracker;
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
            s8 max = SCOUT_FLAG_MAX(t, rowA, rowB);
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
#pragma dont_inline reset

// .text:0x00163E94 size:0x578 mapped:0x807A2F28
void fn_3_163E94(void) {
    s16 ids[9];
    ScoutState* scout = &lbl_3_common_bss_37400;
    ScoutMission* missions = (ScoutMission*)(lbl_80109410 + 0x10);
    int amount = missions[scout->scoutMissionID].reward[0];
    ChallengeTrackingStruct* trackers = starMissionCompletionTracker;
    u8 rowB = ((u8*)trackers)[0x441C];
    u8 rowA = ((u8*)trackers)[0x4415];
    int k;

    fillRosterCharIDs(ids);
    fn_3_163D34();
    k = rand() % 9;
    if (amount > 0 && fn_3_163BD4()) {
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
            if (!fn_3_163948()) {
                break;
            }
        }
    }
}

// .text:0x00163D34 size:0x160 mapped:0x807A2DC8
void fn_3_163D34(void) {
    s16 ids[9];
    ChallengeTrackingStruct* trackers = starMissionCompletionTracker;
    u8 rowB = ((u8*)trackers)[0x441C];
    u8 rowA = ((u8*)trackers)[0x4415];
    int i;

    fillRosterCharIDs(ids);
    for (i = 0; i < 9; i++) {
        if (ids[i] != -1) {
            ChallengeTrackingStruct* t = &trackers[ids[i]];
            if (SCOUT_FLAG_MAX(t, rowA, rowB) != 0) {
                lbl_3_common_bss_37400.pairs[i].cur = t->scoutFlagsAchieved;
                lbl_3_common_bss_37400.pairs[i].max = SCOUT_FLAG_MAX(t, rowA, rowB);
            }
        }
    }
}

// .text:0x00163BD4 size:0x160 mapped:0x807A2C68
BOOL fn_3_163BD4(void) {
    s16 ids[9];
    BOOL found;
    ChallengeTrackingStruct* trackers = starMissionCompletionTracker;
    u8 rowB = ((u8*)trackers)[0x441C];
    u8 rowA = ((u8*)trackers)[0x4415];
    int i;

    fillRosterCharIDs(ids);
    found = FALSE;
    for (i = 0; i < 9; i++) {
        if (ids[i] != -1) {
            ChallengeTrackingStruct* t = &trackers[ids[i]];
            s8 max = SCOUT_FLAG_MAX(t, rowA, rowB);
            if (max != 0 && (s8)t->scoutFlagsAchieved < max) {
                found = TRUE;
            }
        }
    }
    return found;
}

// .text:0x00163A7C size:0x158 mapped:0x807A2B10
BOOL fn_3_163A7C(void) {
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
BOOL fn_3_163948(void) {
    s16 ids[9];
    ScoutState* scout = &lbl_3_common_bss_37400;
    BOOL found;
    int i;

    fillRosterCharIDs(ids);
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
    int i;
    ChallengeTrackingStruct* t;
    s8 max;

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

    if (g_d_GameSettings.bJMatchInd != 1) {
        if (storedInningInfo._4C[slot] == 1) {
            CharacterStats* roster = inMemRoster[scout->humanTeam];
            s8 starter = StatsScreenScores.pitcherLog[scout->humanTeam][0].pitcher;
            CharStaticIndex* ci = &characterStaticIndexes[roster[starter].stats.CharID];
            starMissionTrackingPair* tr = MISSION_TRACKER(ci);
            StarMissionRequirement* req = MISSION_REQS(ci);
            u8* noHitter = &storedInningInfo.noHitterTracker[slot];
            u8* pitched = &PitcherStats_P1_P2[scout->humanTeam][starter]._13[5];
            u8* captainRow = &characterStaticIndexes[Static_Stats_Tables.captainSelectedID[1]].requirementRow;
            for (i = 0; i < 10; i++) {
                if ((s8)tr[i].starMissionStatus >= 0) {
                    int type = req[i].type;
                    if (type == 7) {
                        if (*noHitter == 1) {
                            tr[i].starMissionStatus = -1;
                        }
                    } else if (type == 9 || type == 6) {
                        if (*pitched != 0) {
                            if (type == 6) {
                                if (req[i].target == *captainRow) {
                                    tr[i].starMissionStatus = -1;
                                }
                            } else {
                                tr[i].starMissionStatus = -1;
                            }
                        }
                    } else if (type == 8) {
                        tr[i].starMissionStatus = -1;
                    }
                }
            }
        }

        for (p = 0; p < 9; p++) {
            CharStaticIndex* ci = &characterStaticIndexes[inMemRoster[scout->humanTeam][p].stats.CharID];
            starMissionTrackingPair* tr = MISSION_TRACKER(ci);
            StarMissionRequirement* req = MISSION_REQS(ci);
            StatisticsBatter* bs = &BatterStats_P1_P2[scout->humanTeam][p];
            for (i = 0; i < 10; i++) {
                if ((s8)tr[i].starMissionStatus >= 0) {
                    if (req[i].type == 0x19 && bs->AtBats != 0) {
                        if ((bs->Hits * 10) / bs->AtBats >= req[i].target) {
                            tr[i].starMissionStatus = -1;
                        }
                    }
                    if (req[i].type == 0x1A && bs->Strikeouts == 0) {
                        tr[i].starMissionStatus = -1;
                    }
                }
            }
        }

        if (g_Scores.winnerCd == slot) {
            CharStaticIndex* mvp = &characterStaticIndexes[StatsScreenScores.mvpCharID];
            starMissionTrackingPair* tr = MISSION_TRACKER(mvp);
            StarMissionRequirement* req = MISSION_REQS(mvp);
            for (i = 0; i < 10; i++) {
                if ((s8)tr[i].starMissionStatus >= 0 && req[i].type == 1) {
                    tr[i].starMissionStatus = -1;
                }
            }
            for (p = 0; p < 9; p++) {
                CharStaticIndex* ci = &characterStaticIndexes[inMemRoster[scout->humanTeam][p].stats.CharID];
                tr = MISSION_TRACKER(ci);
                req = MISSION_REQS(ci);
                for (i = 0; i < 10; i++) {
                    if ((s8)tr[i].starMissionStatus >= 0 && req[i].type == 0 &&
                        g_d_GameSettings.StadiumID == req[i].target) {
                        tr[i].starMissionStatus = -1;
                    }
                }
            }
        } else {
            for (p = 0; p < 9; p++) {
                CharStaticIndex* ci = &characterStaticIndexes[inMemRoster[scout->humanTeam][p].stats.CharID];
                starMissionTrackingPair* tr = MISSION_TRACKER(ci);
                StarMissionRequirement* req = MISSION_REQS(ci);
                for (i = 0; i < 10; i++) {
                    if ((s8)tr[i].starMissionStatus == -1 && (req[i].flags & 1)) {
                        tr[i].starMissionStatus = 0;
                    }
                }
            }
        }
    }

    for (p = 0; p < 9; p++) {
        CharStaticIndex* ci = &characterStaticIndexes[inMemRoster[scout->humanTeam][p].stats.CharID];
        starMissionTrackingPair* tr = MISSION_TRACKER(ci);
        StarMissionRequirement* req = MISSION_REQS(ci);
        for (i = 0; i < 10; i++) {
            if ((s8)tr[i].starMissionStatus == -1) {
                if (req[i].flags & 2) {
                    if (g_d_GameSettings.challengeDifficulty < 1) {
                        tr[i].starMissionStatus = 0;
                    }
                } else if (req[i].flags & 4) {
                    if (g_d_GameSettings.challengeDifficulty < 2) {
                        tr[i].starMissionStatus = 0;
                    }
                } else if (req[i].flags & 8) {
                    if (g_d_GameSettings.challengeDifficulty < 3) {
                        tr[i].starMissionStatus = 0;
                    }
                }
            }
        }
    }

    for (p = 0; p < 9; p++) {
        CharStaticIndex* ci = &characterStaticIndexes[inMemRoster[scout->humanTeam][p].stats.CharID];
        starMissionTrackingPair* tr = MISSION_TRACKER(ci);
        StarMissionRequirement* req = MISSION_REQS(ci);
        for (i = 0; i < 10; i++) {
            if ((s8)tr[i].starMissionStatus == -1) {
                if ((req[i].flags & 0x800) && Static_Stats_Tables.captainSelectedID[1] != 9 &&
                    *(s16*)(TRACKER_RAW + 0x16C2) != 0x2A) {
                    tr[i].starMissionStatus = 0;
                }
            }
        }
    }

    for (p = 0; p < 54; p++) {
        for (i = 0; i < 10; i++) {
            if ((s8)starMissionCompletionTracker[p].inGameMissionTracker[i].starMissionStatus < 0) {
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

    if (scout->humanTeam == g_GameLogic.teamFielding) {
        CharStaticIndex* pc = &characterStaticIndexes[g_Pitcher.charID];
        starMissionTrackingPair* tr = MISSION_TRACKER(pc);
        StarMissionRequirement* req = MISSION_REQS(pc);
        for (i = 0; i < 10; i++) {
            if ((s8)tr[i].starMissionStatus >= 0) {
                BOOL done = FALSE;
                if (req[i].type == 2) {
                    if (g_GameLogic.IsStarChance == 2) {
                        MISSION_ADVANCE(tr, req, i);
                    }
                } else {
                    u8* batterRow = &characterStaticIndexes[g_Batter.charID].requirementRow;
                    for (k = 4; k < 13; k++) {
                        if (req[i].type == k) {
                            switch (k) {
                            case 4:
                                if (result == 1 && req[i].target == *batterRow) {
                                    done = TRUE;
                                }
                                break;
                            case 5:
                                if (result == 3 && req[i].target == *batterRow) {
                                    done = TRUE;
                                }
                                break;
                            case 10:
                                if (result == 1) {
                                    tr[i].starMissionStatus++;
                                    if ((s8)tr[i].starMissionStatus >= req[i].target) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            }
                            if (done) {
                                tr[i].starMissionStatus = -1;
                            }
                        }
                    }
                }
            }
        }

        for (f = 0; f < 9; f++) {
            CharStaticIndex* fc = &characterStaticIndexes[g_Fielders[f].CharID];
            tr = MISSION_TRACKER(fc);
            req = MISSION_REQS(fc);
            for (i = 0; i < 10; i++) {
                if ((s8)tr[i].starMissionStatus >= 0 && req[i].type == 0x2B &&
                    g_Strikes.storedOuts + 2 <= g_Strikes.outs) {
                    int flags = 0;
                    int m;
                    for (m = 0; m < 5; m++) {
                        s8 who = storedInningInfo.catches[m].fielderIndex;
                        if (who >= 0) {
                            if (who == f) {
                                flags |= 1;
                            } else if (req[i].target ==
                                       characterStaticIndexes[g_Fielders[who].CharID].requirementRow) {
                                flags |= 0x10;
                            }
                            if (m == 1 && storedInningInfo.catches[m].outsDuringPossession == 2) {
                                break;
                            }
                        }
                    }
                    if (flags == 0x11) {
                        tr[i].starMissionStatus = -1;
                    }
                }
            }
        }
    }

    if (scout->humanTeam == g_GameLogic.teamBatting) {
        CharStaticIndex* bc = &characterStaticIndexes[g_Batter.charID];
        starMissionTrackingPair* tr = MISSION_TRACKER(bc);
        StarMissionRequirement* req = MISSION_REQS(bc);
        CharacterStats* roster = inMemRoster[scout->humanTeam];
        StatisticsBatter* bs = BatterStats_P1_P2[scout->humanTeam];
        u8 lastRunnerStatus = g_Runners[3].runnerOnFieldOrOutOrScored;
        u8 lastRunnerForced = g_Runners[3].furthestBaseForcedToGoToOnWalk;
        u8 starSwing = g_Ball.currentStarSwing2;
        u8 hitType = g_Batter.hitGeneralType;
        u8 nonCaptainSwing = g_Batter.nonCaptainStarSwingActivated;
        CharStaticIndex* pc = &characterStaticIndexes[g_Pitcher.charID];
        int pitcherChar = g_Pitcher.charID;
        int inning = g_Scores.Inning;
        int fieldingRuns;
        int fieldingTotal;
        int j;

        for (i = 0; i < 10; i++) {
            if ((s8)tr[i].starMissionStatus >= 0) {
                BOOL done = FALSE;
                if (req[i].type == 2) {
                    if (g_GameLogic.IsStarChance == 3 || g_GameLogic.stadiumStarObtained != 0) {
                        MISSION_ADVANCE(tr, req, i);
                    }
                } else {
                    for (k = 13; k <= 32; k++) {
                        if (req[i].type == k) {
                            switch (k) {
                            case 13:
                                if (result == 10 && inning == req[i].target) {
                                    done = TRUE;
                                }
                                break;
                            case 14:
                                if (result == 10 && rbis >= req[i].target) {
                                    done = TRUE;
                                }
                                break;
                            case 15:
                                if (result >= req[i].target + 6 && result <= 10) {
                                    done = TRUE;
                                }
                                break;
                            case 16:
                                if (result >= 7 && result <= 10 && pitcherChar == req[i].target) {
                                    done = TRUE;
                                }
                                break;
                            case 17:
                                if (result == 10 && req[i].target == pc->requirementRow) {
                                    done = TRUE;
                                }
                                break;
                            case 18:
                                if (rbis != 0 && req[i].target == pc->requirementRow) {
                                    done = TRUE;
                                }
                                break;
                            case 19:
                                if (result >= 7 && result <= 10) {
                                    tr[i].starMissionStatus++;
                                    if ((s8)tr[i].starMissionStatus >= req[i].target) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            case 20:
                            case 21:
                                if (result == 13) {
                                    if (k == 21) {
                                        if (g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total >
                                                g_Scores._A0 &&
                                            lastRunnerStatus != 0 && lastRunnerForced != 0) {
                                            tr[i].starMissionStatus++;
                                            if ((s8)tr[i].starMissionStatus >= req[i].target) {
                                                done = TRUE;
                                            }
                                        }
                                    } else {
                                        tr[i].starMissionStatus++;
                                        if ((s8)tr[i].starMissionStatus >= req[i].target) {
                                            done = TRUE;
                                        }
                                    }
                                }
                                break;
                            case 22:
                                if (rbis != 0) {
                                    tr[i].starMissionStatus += rbis;
                                    if ((s8)tr[i].starMissionStatus >= req[i].target) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            case 23:
                                if (result == 10) {
                                    tr[i].starMissionStatus++;
                                    if ((s8)tr[i].starMissionStatus >= req[i].target) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            case 24:
                                if (starSwing != 0 && rbis != 0) {
                                    tr[i].starMissionStatus += rbis;
                                    if ((s8)tr[i].starMissionStatus >= req[i].target) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            case 27:
                                if (result >= 7 && result <= 10 && hitType == 1 && g_Batter.chargeUp >= 1.0f &&
                                    nonCaptainSwing == 0) {
                                    tr[i].starMissionStatus++;
                                    if ((s8)tr[i].starMissionStatus >= req[i].target) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            case 28:
                                if (result == 10) {
                                    int count = 0;
                                    int r;
                                    for (r = 1; r < 4; r++) {
                                        if (g_Runners[r].runnerOnFieldOrOutOrScored != 0 &&
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
                                if (result >= 7 && result <= 10 && hitType == 3) {
                                    tr[i].starMissionStatus++;
                                    if ((s8)tr[i].starMissionStatus >= req[i].target) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            case 30:
                                if (result == 10) {
                                    for (j = 0; j < 9; j++) {
                                        if (req[i].target ==
                                                characterStaticIndexes[roster[j].stats.CharID].requirementRow &&
                                            bs[j].HomeRuns != 0) {
                                            tr[i].starMissionStatus = -1;
                                            break;
                                        }
                                    }
                                }
                                break;
                            }
                            if (done) {
                                tr[i].starMissionStatus = -1;
                            }
                        }
                    }
                }
            }
        }

        if (result == 10) {
            for (j = 0; j < 9; j++) {
                CharStaticIndex* rc = &characterStaticIndexes[roster[j].stats.CharID];
                starMissionTrackingPair* rtr = MISSION_TRACKER(rc);
                StarMissionRequirement* rreq = MISSION_REQS(rc);
                for (i = 0; i < 10; i++) {
                    if ((s8)rtr[i].starMissionStatus >= 0 && rreq[i].type == 0x1E &&
                        rreq[i].target == bc->requirementRow && bs[j].HomeRuns != 0) {
                        rtr[i].starMissionStatus = -1;
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
        starMissionTrackingPair* tr = MISSION_TRACKER(pc);
        StarMissionRequirement* req = MISSION_REQS(pc);
        for (i = 0; i < 10; i++) {
            if ((s8)tr[i].starMissionStatus >= 0) {
                BOOL done = FALSE;
                if (req[i].type == 3) {
                    if (g_Pitcher.starPitchType != 0) {
                        tr[i].starMissionStatus |= 1;
                        if (tr[i].starMissionStatus == 0x11) {
                            tr[i].starMissionStatus = -1;
                        }
                    }
                } else {
                    int k;
                    for (k = 4; k < 13; k++) {
                        if (req[i].type == k) {
                            switch (k) {
                            case 11:
                                if (g_Pitcher.starPitchType != 0) {
                                    tr[i].starMissionStatus++;
                                    if ((s8)tr[i].starMissionStatus >= req[i].target) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            case 12:
                                if (g_Pitcher.ChargePitchType == 3) {
                                    tr[i].starMissionStatus++;
                                    if ((s8)tr[i].starMissionStatus >= req[i].target) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            }
                            if (done) {
                                tr[i].starMissionStatus = -1;
                            }
                        }
                    }
                }
            }
        }
    }

    if (scout->humanTeam == g_GameLogic.teamBatting) {
        CharStaticIndex* bc = &characterStaticIndexes[g_Batter.charID];
        starMissionTrackingPair* tr = MISSION_TRACKER(bc);
        StarMissionRequirement* req = MISSION_REQS(bc);
        for (i = 0; i < 10; i++) {
            if ((s8)tr[i].starMissionStatus >= 0) {
                if (req[i].type == 3 && g_Ball.currentStarSwing2 != 0) {
                    tr[i].starMissionStatus |= 0x10;
                    if (tr[i].starMissionStatus == 0x11) {
                        tr[i].starMissionStatus = -1;
                    }
                }
                if (req[i].type == 2) {
                    if (g_GameLogic.IsStarChance == 3 || g_GameLogic.stadiumStarObtained != 0) {
                        MISSION_ADVANCE(tr, req, i);
                    }
                }
            }
        }
    }
}

// .text:0x00161588 size:0xAF8 mapped:0x807A061C
void starMissionsQuantityBased(int missionType, int rosterLocation) {
    CharStaticIndex* ci = &characterStaticIndexes[inMemRoster[lbl_3_common_bss_37400.humanTeam][rosterLocation].stats.CharID];
    u8 trackerIdx = ci->trackerIdx;
    u8 requirementRow = ci->requirementRow;
    starMissionTrackingPair* tr;
    StarMissionRequirement* req;
    int i;

#define QUANTITY_SIMPLE(reqType)                                                                      \
    tr = starMissionCompletionTracker[trackerIdx].inGameMissionTracker;                               \
    req = starMissionRequirementsTable[requirementRow];                                               \
    for (i = 0; i < 10; i++) {                                                                        \
        if ((s8)tr[i].starMissionStatus >= 0 && req[i].type == (reqType)) {                           \
            MISSION_ADVANCE(tr, req, i);                                                              \
        }                                                                                             \
    }

    switch (missionType) {
    case 0:
        QUANTITY_SIMPLE(0x1F)
        break;
    case 1:
        QUANTITY_SIMPLE(0x20)
        break;
    case 2:
        tr = starMissionCompletionTracker[trackerIdx].inGameMissionTracker;
        req = starMissionRequirementsTable[requirementRow];
        {
            int contact = g_Ball.AtBat_ContactResult;
            u8 starSwing = g_Ball.currentStarSwing;
            for (i = 0; i < 10; i++) {
                if ((s8)tr[i].starMissionStatus >= 0) {
                    switch (req[i].type) {
                    case 0x21:
                        MISSION_ADVANCE(tr, req, i);
                        break;
                    case 0x22:
                        if (contact == 3) {
                            MISSION_ADVANCE(tr, req, i);
                        }
                        break;
                    case 0x24:
                        if (starSwing == 5 || starSwing == 6) {
                            MISSION_ADVANCE(tr, req, i);
                        }
                        break;
                    }
                }
            }
        }
        break;
    case 3:
        QUANTITY_SIMPLE(0x25)
        break;
    case 4:
        QUANTITY_SIMPLE(0x23)
        break;
    case 5: {
        int contact;
        tr = starMissionCompletionTracker[trackerIdx].inGameMissionTracker;
        req = starMissionRequirementsTable[requirementRow];
        contact = g_Ball.AtBat_ContactResult;
        for (i = 0; i < 10; i++) {
            if ((s8)tr[i].starMissionStatus >= 0 && req[i].type == 0x26 && contact == 3) {
                MISSION_ADVANCE(tr, req, i);
            }
        }
        break;
    }
    case 6:
        QUANTITY_SIMPLE(0x27)
        break;
    case 7:
        tr = starMissionCompletionTracker[trackerIdx].inGameMissionTracker;
        req = starMissionRequirementsTable[requirementRow];
        {
            s16* thrownTo = &g_Fielders[g_Ball.fielderBeingThrownTo].CharID;
            for (i = 0; i < 10; i++) {
                if ((s8)tr[i].starMissionStatus >= 0 && req[i].type == 0x28 &&
                    req[i].target == characterStaticIndexes[*thrownTo].requirementRow) {
                    tr[i].starMissionStatus = -1;
                }
            }
        }
        break;
    case 8:
        QUANTITY_SIMPLE(0x29)
        break;
    case 9: {
        int contact;
        tr = starMissionCompletionTracker[trackerIdx].inGameMissionTracker;
        req = starMissionRequirementsTable[requirementRow];
        contact = g_Ball.AtBat_ContactResult;
        for (i = 0; i < 10; i++) {
            if ((s8)tr[i].starMissionStatus >= 0 && req[i].type == 0x2A && contact == 3) {
                MISSION_ADVANCE(tr, req, i);
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
