#define SQRT2_LINKAGE static
#include "game/challenge/star_missions.h"
#include "game/UnknownHomes_Game.h"
#include "game/challenge/star_mission_data.h"
#include "game/challenge/scout_state.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/rand.h"
#include "game/minigame/minigame_models.h"
#include "header_rep_data.h"



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

#define SCOUT_FLAG_MAX(t, difficulty_, captain_) ((t)->scoutFlagPointer->flagsRequired[difficulty_][captain_])

#define MISSION_TRACKER(ci) (&g_Challenge.characters[(ci)->trackerIdx])
#define MISSION_REQS(ci) (starMissionRequirementsTable[(ci)->requirementRow])

#define MISSION_ADVANCE(ct, req, i)                                                                     \
    (ct)->inGameMissionTracker[i].starMissionStatus++;                                                  \
    if ((ct)->inGameMissionTracker[i].starMissionStatus >= (req)[i].target) {                           \
        (ct)->inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY; \
    }

static inline void fillRosterCharIDs(s16* ids) {
    s32 i;
    for (i = 0; i < PLAYERS_PER_TEAM; i++) {
        ids[i] = inMemRoster[1][i].stats.CharID;
    }
}

// .text:0x001663AC size:0x9C mapped:0x807A5440
void practice_postGraphicsUpdate(void) {
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
    ChallengeState* cs = &g_Challenge;
    InMemBatterType* batter = &g_Batter;
    ScoutState* scout = &scoutState;
    InMemRunnerType* runners = g_Runners;
    InMemPitcherType* pitcher = &g_Pitcher;
    u8 captain = cs->captain;
    u8 difficulty = cs->difficulty;

    scout->scoutResult = SCOUT_RESULT_PENDING;
    scout->scoutCountdown = 0;
    if (scout->scoutFlag != 0) {
        if (scout->scoutFlag == 2) {
            scout->scoutMissionID = SCOUT_MISSION_NONE;
            scout->scoutFlag = 0;
            return FALSE;
        }
        switch (scout->scoutMissionID) {
        case SCOUT_MISSION_TURN_DOUBLE_PLAY:
        case SCOUT_MISSION_STRIKE_OUT_CAPTAIN:
            break;
        case SCOUT_MISSION_RETIRE_SIDE_IN_ORDER:
            if (storedInningInfo.nBattersThisInning2 >= 4 ||
                g_Scores.scores[logic->homeTeamBattingInd_fieldingTeam].byInning[g_Scores.Inning - 1] != 0) {
                scout->scoutMissionID = SCOUT_MISSION_NONE;
                scout->scoutFlag = 0;
            }
            break;
        case SCOUT_MISSION_SAC_FLY:
        case SCOUT_MISSION_SQUEEZE_BUNT:
            if (scout->targetRosterID != runners[3].rosterID || g_BallsStrikesOuts.outs == 2) {
                scout->scoutMissionID = SCOUT_MISSION_NONE;
                scout->scoutFlag = 0;
            }
            break;
        case SCOUT_MISSION_STEAL_SECOND_BASE:
            if (scout->targetRosterID != runners[1].rosterID) {
                scout->scoutMissionID = SCOUT_MISSION_NONE;
                scout->scoutFlag = 0;
            }
            break;
        }
        return FALSE;
    }

    scout->scoutMissionID = SCOUT_MISSION_NONE;
    sound_crowd_EffectsStruct._32 = 0;
    if (g_d_GameSettings.bJMatchInd == 1) {
        if (shouldScoutMissionBeEnabled(SCOUT_MISSION_WIN_BOWSER_JR_GAME)) {
            scout->scoutMissionID = SCOUT_MISSION_WIN_BOWSER_JR_GAME;
        }
    } else if (logic->teamBatting == g_d_GameSettings.humanTeamNumber) {
        if (g_RunningLogic._10 >= 2) {
            s32* captains = logic->Team_CaptainRosterLoc;

            if (batter->rosterID == captains[logic->teamBatting] &&
                pitcher->rosterID == captains[logic->teamFielding]) {
                if (shouldScoutMissionBeEnabled(SCOUT_MISSION_SCORE_IN_CAPTAIN_DUEL)) {
                    scout->scoutMissionID = SCOUT_MISSION_SCORE_IN_CAPTAIN_DUEL;
                }
                goto chosen;
            }
            if (g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total <
                    g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total &&
                g_Scores._A6 <= 3) {
                if (shouldScoutMissionBeEnabled(SCOUT_MISSION_TAKE_THE_LEAD)) {
                    scout->scoutMissionID = SCOUT_MISSION_TAKE_THE_LEAD;
                }
                goto chosen;
            }
        }
        if ((g_RunningLogic._00 & 0x1000) && g_BallsStrikesOuts.outs <= 1) {
            if (g_Batter.characterClass == CHARACTER_CLASS_BALANCED || g_Batter.characterClass == CHARACTER_CLASS_POWER) {
                if (shouldScoutMissionBeEnabled(SCOUT_MISSION_SAC_FLY)) {
                    scout->scoutMissionID = SCOUT_MISSION_SAC_FLY;
                }
                goto chosen;
            }
            if (g_Batter.characterClass == CHARACTER_CLASS_SPEED || g_Batter.characterClass == CHARACTER_CLASS_TECHNIQUE) {
                if (shouldScoutMissionBeEnabled(SCOUT_MISSION_SQUEEZE_BUNT)) {
                    scout->scoutMissionID = SCOUT_MISSION_SQUEEZE_BUNT;
                }
                goto chosen;
            }
        }
        if (g_RunningLogic._00 == 0x11 &&
            inMemRoster[g_GameLogic.teamBatting][runners[1].rosterID].stats.CharacterClass == CHARACTER_CLASS_SPEED) {
            if (shouldScoutMissionBeEnabled(SCOUT_MISSION_STEAL_SECOND_BASE)) {
                scout->scoutMissionID = SCOUT_MISSION_STEAL_SECOND_BASE;
            }
        } else {
            idx = pitcher->scoutFlagRelated;
            if (idx != -1) {
                ChallengeTrackingStruct* t = &cs->characters[idx];
                s8 max = SCOUT_FLAG_MAX(t, difficulty, captain);
                if (max != 0 && (s8)t->scoutFlagsAchieved < max) {
                    if (shouldScoutMissionBeEnabled(SCOUT_MISSION_REACH_BASE_VS_FLAGGED_PITCHER)) {
                        scout->scoutMissionID = SCOUT_MISSION_REACH_BASE_VS_FLAGGED_PITCHER;
                    }
                }
            }
        }
    } else if (!(logic->teamBatting == g_d_GameSettings.humanTeamNumber)) {
        if (g_RunningLogic._10 >= 3 && g_Scores.scores[g_Scores.halfInning].byInning[g_Scores.Inning - 1] == 0) {
            if (shouldScoutMissionBeEnabled(SCOUT_MISSION_HOLD_SCORELESS_INNING)) {
                scout->scoutMissionID = SCOUT_MISSION_HOLD_SCORELESS_INNING;
            }
        } else if ((g_RunningLogic._00 & 0x10) && g_BallsStrikesOuts.outs <= 1) {
            if (shouldScoutMissionBeEnabled(SCOUT_MISSION_TURN_DOUBLE_PLAY)) {
                scout->scoutMissionID = SCOUT_MISSION_TURN_DOUBLE_PLAY;
            }
        } else if (g_Batter.rosterID == g_GameLogic.Team_CaptainRosterLoc[g_GameLogic.teamBatting]) {
            if (shouldScoutMissionBeEnabled(SCOUT_MISSION_STRIKE_OUT_CAPTAIN)) {
                scout->scoutMissionID = SCOUT_MISSION_STRIKE_OUT_CAPTAIN;
            }
        } else if (g_Scores._C6 == 1) {
            if (shouldScoutMissionBeEnabled(SCOUT_MISSION_RETIRE_SIDE_IN_ORDER)) {
                scout->scoutMissionID = SCOUT_MISSION_RETIRE_SIDE_IN_ORDER;
            }
        } else {
            idx = batter->charIDForScoutFlagMission;
            if (idx != -1) {
                ChallengeTrackingStruct* t = &cs->characters[idx];
                s8 max = SCOUT_FLAG_MAX(t, difficulty, captain);
                if (max != 0 && (s8)t->scoutFlagsAchieved < max) {
                    if (shouldScoutMissionBeEnabled(SCOUT_MISSION_RETIRE_FLAGGED_BATTER)) {
                        scout->scoutMissionID = SCOUT_MISSION_RETIRE_FLAGGED_BATTER;
                    }
                }
            }
        }
    }

chosen:
    switch (scout->scoutMissionID) {
    case SCOUT_MISSION_SAC_FLY:
        scout->targetRosterID = runners[3].rosterID;
        break;
    case SCOUT_MISSION_SQUEEZE_BUNT:
        scout->targetRosterID = runners[3].rosterID;
        break;
    case SCOUT_MISSION_STEAL_SECOND_BASE:
        scout->targetRosterID = runners[1].rosterID;
        break;
    }

    if (scout->scoutMissionID != SCOUT_MISSION_NONE) {
        clearScoutState();
        if (scout->scoutMissionID == SCOUT_MISSION_REACH_BASE_VS_FLAGGED_PITCHER || scout->scoutMissionID == SCOUT_MISSION_RETIRE_FLAGGED_BATTER) {
            assignScoutFlagRewardToTarget();
        } else {
            assignScoutFlagRewardRandom();
        }
        cs->scoutTargetTrackerIdx = idx;
        cs->scoutMissionPending = 1;
        animRelated[0xB3] = 1;
        g_GameLogic.IsStarChance = 0;
        animRelated[0xAC] = 0;
        resetScoutChanceTier();
        return TRUE;
    }
    return FALSE;
}

#pragma dont_inline on
// .text:0x001659A0 size:0x384 mapped:0x807A4A34
BOOL shouldScoutMissionBeEnabled(E(int, SCOUT_MISSION) mission) {
    ScoutState* scout = &scoutState;
    u8 difficulty = g_Challenge.difficulty;
    BOOL enabled;
    int roll;
    int chance;

    if (scout->scoutMissionID == SCOUT_MISSION_REACH_BASE_VS_FLAGGED_PITCHER || scout->scoutMissionID == SCOUT_MISSION_RETIRE_FLAGGED_BATTER) {
        enabled = isScoutTargetFlagAvailable();
    } else {
        enabled = anyScoutFlagIncomplete();
    }
    if (!enabled) {
        return FALSE;
    }
    roll = rand() % 100;
    if (scout->chanceTier == 0) {
        chance = scoutMissionTable[mission].chanceA[difficulty];
    } else {
        chance = scoutMissionTable[mission].chanceB[difficulty];
    }
    if (roll <= chance) {
        return TRUE;
    }
    return FALSE;
}
#pragma dont_inline reset

// .text:0x0016598C size:0x14 mapped:0x807A4A20
void resetScoutChanceTier(void) {
    scoutState.chanceTier = 0;
}

// .text:0x00165978 size:0x14 mapped:0x807A4A0C
void resetScoutChanceTier_2(void) {
    scoutState.chanceTier = 0;
}

// .text:0x001658F0 size:0x88 mapped:0x807A4984
void clearScoutState(void) {
    ScoutState* scout = &scoutState;
    s32 i;
    for (i = 0; i < PLAYERS_PER_TEAM; i++) {
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
    ScoutState* scout = &scoutState;
    ScoutMission* missions = scoutMissionTable;
    ChallengeState* cs = &g_Challenge;
    u8 captain = cs->captain;
    u8 difficulty = cs->difficulty;
    StoredInningInfo* inning = &storedInningInfo;
    InMemRunnerType* runners = g_Runners;
    int cnt = 0;
    BOOL flag = FALSE;

    scout->scoutResult = SCOUT_RESULT_FAILED;
    scout->baseReward = missions[scout->scoutMissionID].reward[0];
    switch (scout->scoutMissionID) {
    case SCOUT_MISSION_NONE:
        break;
    case SCOUT_MISSION_RETIRE_FLAGGED_BATTER:
        if (g_FieldingLogic.liveBallReason != PICKOFF_STEAL_CODE_NONE) {
            if (g_BallsStrikesOuts.outs >= 3) {
                scout->scoutResult = SCOUT_RESULT_SUCCEEDED;
            } else if (g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT) {
                scout->scoutFlag = 0;
            } else {
                scout->scoutResult = SCOUT_RESULT_PENDING;
            }
        } else if ((g_BallsStrikesOuts.outs > g_BallsStrikesOuts.storedOuts && inning->batterResultBase == 0) ||
                   g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT) {
            if (g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT ||
                storedInningInfo.playResultCode == PLAY_RESULT_CODE_FOUL_BUNT_TWO_STRIKES) {
                scout->scoutResult = SCOUT_RESULT_SUCCEEDED;
                cnt = 1;
            } else {
                scout->scoutResult = SCOUT_RESULT_SUCCEEDED;
                cnt = 0;
            }
        }
        break;
    case SCOUT_MISSION_REACH_BASE_VS_FLAGGED_PITCHER:
        if (g_FieldingLogic.liveBallReason != PICKOFF_STEAL_CODE_NONE) {
            if (g_BallsStrikesOuts.outs >= 3) {
                scout->scoutFlag = 0;
            } else if (g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT) {
                scout->scoutFlag = 0;
            } else {
                scout->scoutResult = SCOUT_RESULT_PENDING;
            }
        } else if (g_BallsStrikesOuts.howRunnerReachedBase == 1 || inning->batterResultBase >= 1) {
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
                scout->scoutResult = SCOUT_RESULT_SUCCEEDED;
            }
        }
        break;
    case SCOUT_MISSION_SCORE_IN_CAPTAIN_DUEL:
        if (g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total > g_Scores._A0 ||
            g_Ball.deadBallReason == 1 ||
            ((g_Pitcher.strikeOutOrWalk == AT_BAT_END_WALK || g_Pitcher.strikeOutOrWalk == AT_BAT_END_HIT_BY_PITCH) &&
             g_RunningLogic.nOffensivePlayersAtStartOfPlay >= 4)) {
            scout->scoutResult = SCOUT_RESULT_SUCCEEDED;
            scout->scoutFlag = 0;
        } else if (g_BallsStrikesOuts.outs >= 3 ||
                   (g_BallsStrikesOuts.outs == 2 && g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT &&
                    g_FieldingLogic.liveBallReason == PICKOFF_STEAL_CODE_NONE)) {
            scout->scoutFlag = 0;
        } else {
            scout->scoutFlag = 1;
            scout->scoutResult = SCOUT_RESULT_PENDING;
        }
        break;
    case SCOUT_MISSION_TAKE_THE_LEAD: {
        int battingScore = g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total;
        int otherScore = g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total;
        if (battingScore > otherScore || (g_Ball.deadBallReason == 1 && g_Scores._A0 + g_RunningLogic.nOffensivePlayersAtStartOfPlay > otherScore) ||
            ((g_Pitcher.strikeOutOrWalk == AT_BAT_END_WALK || g_Pitcher.strikeOutOrWalk == AT_BAT_END_HIT_BY_PITCH) &&
             g_RunningLogic.nOffensivePlayersAtStartOfPlay >= 4 && g_Scores._A0 == otherScore)) {
            scout->scoutResult = SCOUT_RESULT_SUCCEEDED;
            scout->scoutFlag = 0;
        } else if (g_BallsStrikesOuts.outs >= 3 || (g_BallsStrikesOuts.outs == 2 && g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT)) {
            scout->scoutFlag = 0;
        } else {
            scout->scoutFlag = 1;
            scout->scoutResult = SCOUT_RESULT_PENDING;
        }
        break;
    }
    case SCOUT_MISSION_HOLD_SCORELESS_INNING: {
        u8 deadBallReason = g_Ball.deadBallReason;
        if (g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total > g_Scores._A0 ||
            deadBallReason == 1 ||
            (g_RunningLogic._02 == 0x1111 && (g_Pitcher.strikeOutOrWalk == AT_BAT_END_WALK || g_Pitcher.strikeOutOrWalk == AT_BAT_END_HIT_BY_PITCH))) {
            scout->scoutFlag = 0;
        } else if ((g_BallsStrikesOuts.outs >= 2 && g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT &&
                    g_FieldingLogic.liveBallReason == PICKOFF_STEAL_CODE_NONE) ||
                   g_BallsStrikesOuts.outs >= 3) {
            scout->scoutResult = SCOUT_RESULT_SUCCEEDED;
            scout->scoutFlag = 0;
        } else {
            scout->scoutFlag = 1;
            scout->scoutResult = SCOUT_RESULT_PENDING;
        }
        break;
    }
    case SCOUT_MISSION_TURN_DOUBLE_PLAY:
        if (g_BallsStrikesOuts.outs >= g_BallsStrikesOuts.storedOuts + 2) {
            scout->scoutResult = SCOUT_RESULT_SUCCEEDED;
            scout->scoutFlag = 0;
        } else if (g_FieldingLogic.liveBallReason != PICKOFF_STEAL_CODE_NONE) {
            scout->scoutFlag = 1;
            scout->scoutResult = SCOUT_RESULT_PENDING;
        } else {
            scout->scoutFlag = 0;
        }
        break;
    case SCOUT_MISSION_STRIKE_OUT_CAPTAIN:
        if (g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT) {
            scout->scoutResult = SCOUT_RESULT_SUCCEEDED;
            scout->scoutFlag = 0;
        } else if (g_FieldingLogic.liveBallReason != PICKOFF_STEAL_CODE_NONE) {
            if (g_BallsStrikesOuts.outs >= 3) {
                scout->scoutFlag = 0;
            } else {
                scout->scoutFlag = 1;
                scout->scoutResult = SCOUT_RESULT_PENDING;
            }
        }
        break;
    case SCOUT_MISSION_RETIRE_SIDE_IN_ORDER: {
        int threw;
        if (inning->nBattersThisInning2 == 3) {
            if ((g_BallsStrikesOuts.outs >= 2 && g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT &&
                 g_FieldingLogic.liveBallReason == PICKOFF_STEAL_CODE_NONE) ||
                g_BallsStrikesOuts.outs >= 3) {
                scout->scoutResult = SCOUT_RESULT_SUCCEEDED;
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
        if (inning->nBattersThisInning2 == 3 && g_FieldingLogic.liveBallReason == PICKOFF_STEAL_CODE_NONE) {
            scout->scoutFlag = 0;
        } else if (g_Scores._A0 < g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total) {
            scout->scoutFlag = 0;
        } else if (g_Ball.deadBallReason == 1 || threw != 0) {
            scout->scoutFlag = 0;
        } else {
            scout->scoutFlag = 1;
            scout->scoutResult = SCOUT_RESULT_PENDING;
        }
        break;
    }
    case SCOUT_MISSION_SAC_FLY:
        if (inning->playResultCode == PLAY_RESULT_CODE_SAC_FLY_SCORED) {
            scout->scoutResult = SCOUT_RESULT_SUCCEEDED;
            scout->scoutFlag = 0;
        } else if (g_FieldingLogic.liveBallReason != PICKOFF_STEAL_CODE_NONE) {
            if (g_BallsStrikesOuts.outs >= 3) {
                scout->scoutFlag = 0;
            } else if (g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT) {
                scout->scoutFlag = 0;
            } else {
                scout->scoutFlag = 1;
                scout->scoutResult = SCOUT_RESULT_PENDING;
            }
        } else {
            scout->scoutFlag = 0;
        }
        break;
    case SCOUT_MISSION_SQUEEZE_BUNT:
        if (g_Scores.scores[g_GameLogic.homeTeamBattingInd_fieldingTeam].total > g_Scores._A0) {
            if (runners[3].furthestBaseForcedToGoToOnWalk != 0) {
                if (g_Ball.maybeBuntInd != 0) {
                    flag = TRUE;
                }
            }
        }
        if (flag) {
            scout->scoutResult = SCOUT_RESULT_SUCCEEDED;
            scout->scoutFlag = 0;
        } else if (g_FieldingLogic.liveBallReason != PICKOFF_STEAL_CODE_NONE) {
            if (g_BallsStrikesOuts.outs >= 3) {
                scout->scoutFlag = 0;
            } else if (g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT) {
                scout->scoutFlag = 0;
            } else if (runners[3].runnerOnFieldOrOutOrScored != RUNNER_STATUS_ON_FIELD) {
                scout->scoutFlag = 0;
            } else {
                scout->scoutFlag = 1;
                scout->scoutResult = SCOUT_RESULT_PENDING;
            }
        } else {
            scout->scoutFlag = 0;
        }
        break;
    case SCOUT_MISSION_STEAL_SECOND_BASE: {
        u8 fl = g_FieldingLogic.liveBallReason;
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
            scout->scoutResult = SCOUT_RESULT_FAILED;
            scout->scoutFlag = 0;
        } else if (flag != 0) {
            scout->scoutResult = SCOUT_RESULT_SUCCEEDED;
            scout->scoutFlag = 0;
        } else if (fl != PICKOFF_STEAL_CODE_NONE) {
            if (g_BallsStrikesOuts.outs >= 3) {
                scout->scoutFlag = 0;
            } else if (g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT) {
                scout->scoutFlag = 0;
            } else {
                scout->scoutFlag = 1;
                scout->scoutResult = SCOUT_RESULT_PENDING;
            }
        } else {
            scout->scoutFlag = 0;
        }
        break;
    }
    case SCOUT_MISSION_WIN_BOWSER_JR_GAME:
        if (g_GameLogic.EventTriggers_EndOfGame != 0) {
            if ((g_GameLogic.homeTeamInd ^ (g_Scores.winnerCd == g_d_GameSettings.humanTeamNumber)) != 0 &&
                g_Scores.winnerCd != 2) {
                scout->scoutResult = SCOUT_RESULT_SUCCEEDED;
            } else {
                scout->scoutResult = SCOUT_RESULT_FAILED;
            }
            scout->scoutFlag = 0;
        } else if (g_Scores.Inning >= g_Scores.inningLimit && g_Scores.halfInning != 0) {
            if (g_Ball.deadBallReason == 1 &&
                g_Scores._A0 + g_RunningLogic.nOffensivePlayersAtStartOfPlay >
                    g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total) {
                if (g_GameLogic.teamBatting == g_d_GameSettings.humanTeamNumber) {
                    scout->scoutResult = SCOUT_RESULT_SUCCEEDED;
                }
                scout->scoutFlag = 0;
            } else if (g_BallsStrikesOuts.outs >= 2 && g_Pitcher.strikeOutOrWalk == AT_BAT_END_STRIKEOUT) {
                if ((g_Scores.scores[1].total > g_Scores.scores[0].total &&
                     scoutState.humanTeam == g_GameLogic.teamBatting) ||
                    (g_Scores.scores[1].total < g_Scores.scores[0].total &&
                     scoutState.humanTeam == g_GameLogic.teamFielding)) {
                    scout->scoutResult = SCOUT_RESULT_SUCCEEDED;
                }
                scout->scoutFlag = 0;
            } else if (g_RunningLogic._10 == 4 &&
                       (g_Pitcher.strikeOutOrWalk == AT_BAT_END_WALK || g_Pitcher.strikeOutOrWalk == AT_BAT_END_HIT_BY_PITCH)) {
                if (g_Scores.scores[1].total == g_Scores.scores[0].total) {
                    if (g_GameLogic.teamBatting == g_d_GameSettings.humanTeamNumber) {
                        scout->scoutResult = SCOUT_RESULT_SUCCEEDED;
                    }
                    scout->scoutFlag = 0;
                } else {
                    scout->scoutFlag = 1;
                    scout->scoutResult = SCOUT_RESULT_PENDING;
                }
            } else {
                scout->scoutFlag = 1;
                scout->scoutResult = SCOUT_RESULT_PENDING;
            }
        } else {
            scout->scoutFlag = 1;
            scout->scoutResult = SCOUT_RESULT_PENDING;
        }
        break;
    }

    if (scout->scoutResult == SCOUT_RESULT_SUCCEEDED) {
        if (scout->scoutMissionID == SCOUT_MISSION_REACH_BASE_VS_FLAGGED_PITCHER || scout->scoutMissionID == SCOUT_MISSION_RETIRE_FLAGGED_BATTER) {
            ChallengeTrackingStruct* t = &cs->characters[cs->scoutTargetTrackerIdx];
            s8 reward = missions[scout->scoutMissionID].reward[cnt];
            s8 max;
            int i;
            for (i = 0; i < PLAYERS_PER_TEAM; i++) {
                if (scout->entries[i].active == 1) {
                    scout->entries[i].amount = reward;
                }
            }
            t->scoutFlagsAchieved += reward;
            max = SCOUT_FLAG_MAX(t, difficulty, captain);
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
    s16 ids[PLAYERS_PER_TEAM];
    ScoutMission* missions = scoutMissionTable;
    ChallengeState* cs = &g_Challenge;
    u8 captain = cs->captain;
    u8 difficulty = cs->difficulty;
    int k;
    int amount;
    BOOL enabled;

    amount = missions[scoutState.scoutMissionID].reward[0];
    fillRosterCharIDs(ids);
    k = 0;
    enabled = anyScoutFlagIncomplete();
    if (amount > 0 && enabled) {
        while (amount > 0) {
            if (ids[k] != -1) {
                ChallengeTrackingStruct* t = &cs->characters[ids[k]];
                s8 max = SCOUT_FLAG_MAX(t, difficulty, captain);
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
    s16 ids[PLAYERS_PER_TEAM];
    ChallengeState* cs = &g_Challenge;
    ScoutState* scout = &scoutState;
    u8 captain = cs->captain;
    u8 difficulty = cs->difficulty;
    int i;

    fillRosterCharIDs(ids);
    for (i = 0; i < PLAYERS_PER_TEAM; i++) {
        if (ids[i] != -1 && scout->entries[i].active == 1) {
            ChallengeTrackingStruct* t = &cs->characters[ids[i]];
            if (SCOUT_FLAG_MAX(t, difficulty, captain) != 0) {
                t->scoutFlagsAchieved += scout->entries[i].amount;
                if ((s8)t->scoutFlagsAchieved > SCOUT_FLAG_MAX(t, difficulty, captain)) {
                    t->scoutFlagsAchieved = SCOUT_FLAG_MAX(t, difficulty, captain);
                }
            }
        }
    }
}

// .text:0x0016440C size:0x148 mapped:0x807A34A0
void assignScoutFlagRewardToTarget(void) {
    s16 ids[PLAYERS_PER_TEAM];
    ScoutState* scout = &scoutState;
    ScoutMission* missions = scoutMissionTable;
    ChallengeState* cs = &g_Challenge;
    InMemBatterType* batter = &g_Batter;
    InMemPitcherType* pitcher = &g_Pitcher;
    u8 captain = cs->captain;
    u8 difficulty = cs->difficulty;
    int amount;
    int cid;
    s32 i;
    s8 max;
    ChallengeTrackingStruct* t;

    amount = missions[scout->scoutMissionID].reward[0];
    for (i = 0; i < PLAYERS_PER_TEAM; i++) {
        ids[i] = inMemRoster[1][i].stats.CharID;
    }
    if (scout->scoutMissionID == SCOUT_MISSION_REACH_BASE_VS_FLAGGED_PITCHER) {
        cid = pitcher->charID;
    } else if (scout->scoutMissionID == SCOUT_MISSION_RETIRE_FLAGGED_BATTER) {
        cid = batter->charID;
    }
    for (i = 0; i < PLAYERS_PER_TEAM; i++) {
        if (cid == ids[i]) {
            t = &cs->characters[ids[i]];
            max = SCOUT_FLAG_MAX(t, difficulty, captain);
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
    s16 ids[PLAYERS_PER_TEAM];
    ScoutMission* missions = scoutMissionTable;
    ChallengeState* cs = &g_Challenge;
    ScoutState* scout = &scoutState;
    u8 captain = cs->captain;
    u8 difficulty = cs->difficulty;
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
                ChallengeTrackingStruct* t = &cs->characters[ids[k]];
                if (pair->max != 0 && pair->cur < pair->max) {
                    scout->entries[k].max = SCOUT_FLAG_MAX(t, difficulty, captain);
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
    s16 ids[PLAYERS_PER_TEAM];
    ChallengeState* cs = &g_Challenge;
    ScoutState* scout = &scoutState;
    u8 captain = cs->captain;
    u8 difficulty = cs->difficulty;
    s32 i;

    for (i = 0; i < PLAYERS_PER_TEAM; i++) {
        ids[i] = inMemRoster[1][i].stats.CharID;
    }
    for (i = 0; i < PLAYERS_PER_TEAM; i++) {
        if (ids[i] != -1) {
            ChallengeTrackingStruct* t = &cs->characters[ids[i]];
            if (SCOUT_FLAG_MAX(t, difficulty, captain) != 0) {
                scout->pairs[i].cur = t->scoutFlagsAchieved;
                scout->pairs[i].max = SCOUT_FLAG_MAX(t, difficulty, captain);
            }
        }
    }
}

// .text:0x00163BD4 size:0x160 mapped:0x807A2C68
BOOL anyScoutFlagIncomplete(void) {
    s16 ids[PLAYERS_PER_TEAM];
    ChallengeState* cs = &g_Challenge;
    u8 captain = cs->captain;
    u8 difficulty = cs->difficulty;
    s8 max;
    int i;
    ChallengeTrackingStruct* t;
    BOOL found;

    fillRosterCharIDs(ids);
    found = FALSE;
    for (i = 0; i < PLAYERS_PER_TEAM; i++) {
        if (ids[i] != -1) {
            t = &cs->characters[ids[i]];
            max = SCOUT_FLAG_MAX(t, difficulty, captain);
            if (max != 0 && (s8)t->scoutFlagsAchieved < max) {
                found = TRUE;
            }
        }
    }
    return found;
}

// .text:0x00163A7C size:0x158 mapped:0x807A2B10
BOOL isScoutTargetFlagAvailable(void) {
    s16 ids[PLAYERS_PER_TEAM];
    BOOL found;
    ChallengeState* cs = &g_Challenge;
    ScoutState* scout = &scoutState;
    InMemBatterType* batter = &g_Batter;
    InMemPitcherType* pitcher = &g_Pitcher;
    u8 captain = cs->captain;
    u8 difficulty = cs->difficulty;
    int cid;
    int i;

    fillRosterCharIDs(ids);
    if (scout->scoutMissionID == SCOUT_MISSION_REACH_BASE_VS_FLAGGED_PITCHER) {
        cid = pitcher->charID;
    } else if (scout->scoutMissionID == SCOUT_MISSION_RETIRE_FLAGGED_BATTER) {
        cid = batter->charID;
    }
    for (i = 0; i < PLAYERS_PER_TEAM; i++) {
        if (cid == ids[i]) {
            ChallengeTrackingStruct* t = &cs->characters[ids[i]];
            if (SCOUT_FLAG_MAX(t, difficulty, captain) != 0) {
                found = TRUE;
            }
        }
    }
    return found;
}

// .text:0x00163948 size:0x134 mapped:0x807A29DC
BOOL anyScoutPairIncomplete(void) {
    s16 ids[PLAYERS_PER_TEAM];
    ScoutState* scout = &scoutState;
    BOOL found;
    s32 i;

    for (i = 0; i < PLAYERS_PER_TEAM; i++) {
        ids[i] = inMemRoster[1][i].stats.CharID;
    }
    found = FALSE;
    for (i = 0; i < PLAYERS_PER_TEAM; i++) {
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
    s16 ids[PLAYERS_PER_TEAM];
    ChallengeState* cs = &g_Challenge;
    u8 difficulty;
    u8 captain;
    s8 max;
    int i;
    ChallengeTrackingStruct* t;

    captain = cs->captain;
    difficulty = cs->difficulty;

    fillRosterCharIDs(ids);
    for (i = 0; i < PLAYERS_PER_TEAM; i++) {
        if (ids[i] != -1) {
            t = &cs->characters[ids[i]];
            max = SCOUT_FLAG_MAX(t, difficulty, captain);
            if (max != 0 && (s8)t->scoutFlagsAchieved < max) {
                t->scoutFlagsAchieved = max;
            }
        }
    }
}

// .text:0x00162D54 size:0xA98 mapped:0x807A1DE8
void starMissionsWholeGame(void) {
    ScoutState* scout = &scoutState;
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
            for (i = 0; i < STAR_MISSIONS_PER_CHARACTER; i++) {
                if (ct->inGameMissionTracker[i].starMissionStatus >= 0) {
                    int type = req[i].type;
                    if (type == STAR_MISSION_TYPE_NO_HITTER) {
                        if (*noHitter == 1) {
                            ct->inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY;
                        }
                    } else if (type == STAR_MISSION_TYPE_SHUTOUT || type == STAR_MISSION_TYPE_SHUTOUT_AGAINST_CAPTAIN) {
                        if (*pitched != 0) {
                            if (type == STAR_MISSION_TYPE_SHUTOUT_AGAINST_CAPTAIN) {
                                if (req[i].target == *captainRow) {
                                    ct->inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY;
                                }
                            } else {
                                ct->inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY;
                            }
                        }
                    } else if (type == STAR_MISSION_TYPE_COMPLETE_GAME) {
                        ct->inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY;
                    }
                }
            }
        }

        batterStats = BatterStats_P1_P2[scout->humanTeam];
        for (p = 0; p < PLAYERS_PER_TEAM; p++) {
            CharStaticIndex* ci = &characterStaticIndexes[inMemRoster[scout->humanTeam][p].stats.CharID];
            ChallengeTrackingStruct* ct = MISSION_TRACKER(ci);
            StarMissionRequirement* req = MISSION_REQS(&characterStaticIndexes[ci->trackerIdx]);
            for (i = 0; i < STAR_MISSIONS_PER_CHARACTER; i++) {
                if (ct->inGameMissionTracker[i].starMissionStatus >= 0) {
                    if (req[i].type == STAR_MISSION_TYPE_BATTING_AVERAGE && batterStats[p].AtBats != 0) {
                        if ((batterStats[p].Hits * 10) / batterStats[p].AtBats >= req[i].target) {
                            ct->inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY;
                        }
                    }
                    if (req[i].type == STAR_MISSION_TYPE_NO_STRIKEOUTS && batterStats[p].Strikeouts == 0) {
                        ct->inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY;
                    }
                }
            }
        }

        if (g_Scores.winnerCd == slot) {
            CharStaticIndex* mvp = &characterStaticIndexes[StatsScreenScores.mvpCharID];
            ChallengeTrackingStruct* ct = MISSION_TRACKER(mvp);
            StarMissionRequirement* req = MISSION_REQS(mvp);
            for (i = 0; i < STAR_MISSIONS_PER_CHARACTER; i++) {
                if (ct->inGameMissionTracker[i].starMissionStatus >= 0 && req[i].type == STAR_MISSION_TYPE_WIN_AS_MVP) {
                    ct->inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY;
                }
            }
            for (p = 0; p < PLAYERS_PER_TEAM; p++) {
                CharStaticIndex* ci = &characterStaticIndexes[inMemRoster[scout->humanTeam][p].stats.CharID];
                ct = MISSION_TRACKER(ci);
                req = MISSION_REQS(&characterStaticIndexes[ci->trackerIdx]);
                for (i = 0; i < STAR_MISSIONS_PER_CHARACTER; i++) {
                    if (ct->inGameMissionTracker[i].starMissionStatus >= 0 && req[i].type == STAR_MISSION_TYPE_WIN_AT_STADIUM &&
                        g_d_GameSettings.StadiumID == req[i].target) {
                        ct->inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY;
                    }
                }
            }
        } else {
            for (p = 0; p < PLAYERS_PER_TEAM; p++) {
                CharStaticIndex* ci = &characterStaticIndexes[inMemRoster[scout->humanTeam][p].stats.CharID];
                ChallengeTrackingStruct* ct = MISSION_TRACKER(ci);
                StarMissionRequirement* req = MISSION_REQS(&characterStaticIndexes[ci->trackerIdx]);
                for (i = 0; i < STAR_MISSIONS_PER_CHARACTER; i++) {
                    if (ct->inGameMissionTracker[i].starMissionStatus == STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY && (req[i].flags & STAR_MISSION_FLAG_REQUIRES_WIN)) {
                        ct->inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_NOT_COMPLETED;
                    }
                }
            }
        }
    }

    difficulty = g_d_GameSettings.challengeDifficulty;
    for (p = 0; p < PLAYERS_PER_TEAM; p++) {
        CharStaticIndex* ci = &characterStaticIndexes[inMemRoster[scout->humanTeam][p].stats.CharID];
        ChallengeTrackingStruct* ct = MISSION_TRACKER(ci);
        StarMissionRequirement* req = MISSION_REQS(&characterStaticIndexes[ci->trackerIdx]);
        for (i = 0; i < STAR_MISSIONS_PER_CHARACTER; i++) {
            if (ct->inGameMissionTracker[i].starMissionStatus == STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY) {
                if (req[i].flags & STAR_MISSION_FLAG_MIN_DIFFICULTY_1) {
                    if (difficulty < 1) {
                        ct->inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_NOT_COMPLETED;
                    }
                } else if (req[i].flags & STAR_MISSION_FLAG_MIN_DIFFICULTY_2) {
                    if (difficulty < 2) {
                        ct->inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_NOT_COMPLETED;
                    }
                } else if (req[i].flags & STAR_MISSION_FLAG_MIN_DIFFICULTY_3) {
                    if (difficulty < 3) {
                        ct->inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_NOT_COMPLETED;
                    }
                }
            }
        }
    }

    for (p = 0; p < PLAYERS_PER_TEAM; p++) {
        CharStaticIndex* ci = &characterStaticIndexes[inMemRoster[scout->humanTeam][p].stats.CharID];
        ChallengeTrackingStruct* ct = MISSION_TRACKER(ci);
        StarMissionRequirement* req = MISSION_REQS(&characterStaticIndexes[ci->trackerIdx]);
        for (i = 0; i < STAR_MISSIONS_PER_CHARACTER; i++) {
            if (ct->inGameMissionTracker[i].starMissionStatus == STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY) {
                if ((req[i].flags & STAR_MISSION_FLAG_BOWSER_UNLOCK) && Static_Stats_Tables.captainSelectedID[1] != CHAR_ID_BOWSER &&
                    g_Challenge._16C2 != 0x2A) {
                    ct->inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_NOT_COMPLETED;
                }
            }
        }
    }

    for (p = 0; p < NUM_CHOOSABLE_CHARACTERS; p++) {
        for (i = 0; i < STAR_MISSIONS_PER_CHARACTER; i++) {
            if (g_Challenge.characters[p].inGameMissionTracker[i].starMissionStatus <= -1) {
                g_Challenge.characters[p].inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
            } else {
                g_Challenge.characters[p].inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_NOT_COMPLETED;
            }
        }
    }
}

// .text:0x0016230C size:0xA48 mapped:0x807A13A0
void starMissionsOffensive_StarChange_DoublePlay(int result, int rbis) {
    ScoutState* scout = &scoutState;
    int i;
    int k;
    int f;
    int outsBefore;
    int outs;

    if (scout->humanTeam == g_GameLogic.teamFielding) {
        CharStaticIndex* pc = &characterStaticIndexes[g_Pitcher.charID];
        ChallengeTrackingStruct* ct = MISSION_TRACKER(pc);
        StarMissionRequirement* req = MISSION_REQS(pc);
        for (i = 0; i < STAR_MISSIONS_PER_CHARACTER; i++) {
            if (ct->inGameMissionTracker[i].starMissionStatus >= 0) {
                StarMissionRequirement* mreq = &req[i];
                BOOL done = FALSE;
                if (mreq->type == STAR_MISSION_TYPE_STAR_CHANCES) {
                    if (g_GameLogic.IsStarChance == 2) {
                        MISSION_ADVANCE(ct, req, i);
                    }
                } else {
                    u8* batterRow = &characterStaticIndexes[g_Batter.charID].requirementRow;
                    for (k = STAR_MISSION_TYPE_STRIKE_OUT_BATTER; k <= STAR_MISSION_TYPE_CHARGE_PITCHES; k++) {
                        if (mreq->type == k) {
                            switch (k) {
                            case STAR_MISSION_TYPE_STRIKE_OUT_BATTER:
                                if (result == AT_BAT_RESULT_STRIKEOUT && mreq->target == *batterRow) {
                                    done = TRUE;
                                }
                                break;
                            case STAR_MISSION_TYPE_HIT_BATTER_WITH_PITCH:
                                if (result == AT_BAT_RESULT_HIT_BY_PITCH && mreq->target == *batterRow) {
                                    done = TRUE;
                                }
                                break;
                            case STAR_MISSION_TYPE_STRIKEOUTS:
                                if (result == AT_BAT_RESULT_STRIKEOUT) {
                                    ct->inGameMissionTracker[i].starMissionStatus++;
                                    if (ct->inGameMissionTracker[i].starMissionStatus >= mreq->target) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            }
                            if (done) {
                                ct->inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY;
                            }
                        }
                    }
                }
            }
        }

        outsBefore = g_BallsStrikesOuts.storedOuts;
        outs = g_BallsStrikesOuts.outs;
        for (f = 0; f < PLAYERS_PER_TEAM; f++) {
            CharStaticIndex* fc = &characterStaticIndexes[g_Fielders[f].CharID];
            ct = MISSION_TRACKER(fc);
            req = MISSION_REQS(fc);
            for (i = 0; i < STAR_MISSIONS_PER_CHARACTER; i++) {
                StarMissionRequirement* mreq = &req[i];

                if (ct->inGameMissionTracker[i].starMissionStatus >= 0 && mreq->type == STAR_MISSION_TYPE_DOUBLE_PLAY_WITH &&
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
                        ct->inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY;
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

        for (i = 0; i < STAR_MISSIONS_PER_CHARACTER; i++) {
            if (ct->inGameMissionTracker[i].starMissionStatus >= 0) {
                BOOL done = FALSE;
                if (req[i].type == STAR_MISSION_TYPE_STAR_CHANCES) {
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

                    for (k = STAR_MISSION_TYPE_HOME_RUN_IN_INNING; k <= STAR_MISSION_TYPE_FIELD_BALLS; k++) {
                        if (req[i].type == k) {
                            switch (k) {
                            case STAR_MISSION_TYPE_HOME_RUN_IN_INNING:
                                if (result == AT_BAT_RESULT_HOME_RUN && inning == req[i].target) {
                                    done = TRUE;
                                }
                                break;
                            case STAR_MISSION_TYPE_HOME_RUN_WITH_RBIS:
                                if (result == AT_BAT_RESULT_HOME_RUN && rbis >= req[i].target) {
                                    done = TRUE;
                                }
                                break;
                            case STAR_MISSION_TYPE_HIT_AT_LEAST_BASES:
                                if (result >= AT_BAT_RESULT_SINGLE - 1 + req[i].target && result <= AT_BAT_RESULT_HOME_RUN) {
                                    done = TRUE;
                                }
                                break;
                            case STAR_MISSION_TYPE_HIT_OFF_PITCHER:
                                if (result >= AT_BAT_RESULT_SINGLE && result <= AT_BAT_RESULT_HOME_RUN && pitcherChar == req[i].target) {
                                    done = TRUE;
                                }
                                break;
                            case STAR_MISSION_TYPE_HOME_RUN_OFF_PITCHER:
                                if (result == AT_BAT_RESULT_HOME_RUN && req[i].target == pc->requirementRow) {
                                    done = TRUE;
                                }
                                break;
                            case STAR_MISSION_TYPE_RBI_OFF_PITCHER:
                                if (rbis != 0 && req[i].target == pc->requirementRow) {
                                    done = TRUE;
                                }
                                break;
                            case STAR_MISSION_TYPE_HITS:
                                if (result >= AT_BAT_RESULT_SINGLE && result <= AT_BAT_RESULT_HOME_RUN) {
                                    ct->inGameMissionTracker[i].starMissionStatus++;
                                    if (ct->inGameMissionTracker[i].starMissionStatus >= req[i].target) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            case STAR_MISSION_TYPE_BUNTS:
                            case STAR_MISSION_TYPE_BUNT_FORCES_IN_RUN:
                                if (result == AT_BAT_RESULT_BUNT) {
                                    if (k == STAR_MISSION_TYPE_BUNT_FORCES_IN_RUN) {
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
                            case STAR_MISSION_TYPE_RBIS:
                                if (rbis != 0) {
                                    ct->inGameMissionTracker[i].starMissionStatus += rbis;
                                    if (ct->inGameMissionTracker[i].starMissionStatus >= req[i].target) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            case STAR_MISSION_TYPE_HOME_RUNS:
                                if (result == AT_BAT_RESULT_HOME_RUN) {
                                    ct->inGameMissionTracker[i].starMissionStatus++;
                                    if (ct->inGameMissionTracker[i].starMissionStatus >= req[i].target) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            case STAR_MISSION_TYPE_HOME_RUN_WITH_TEAMMATE:
                                if (result == AT_BAT_RESULT_HOME_RUN) {
                                    for (j = 0; j < PLAYERS_PER_TEAM; j++) {
                                        if (req[i].target ==
                                                characterStaticIndexes[roster[j].stats.CharID].requirementRow &&
                                            bs[j].HomeRuns != 0) {
                                            ct->inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY;
                                            break;
                                        }
                                    }
                                }
                                break;
                            case STAR_MISSION_TYPE_STAR_SWING_RBIS:
                                if (starSwing != 0 && rbis != 0) {
                                    ct->inGameMissionTracker[i].starMissionStatus += rbis;
                                    if (ct->inGameMissionTracker[i].starMissionStatus >= req[i].target) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            case STAR_MISSION_TYPE_CHARGE_HITS:
                                if (result >= AT_BAT_RESULT_SINGLE && result <= AT_BAT_RESULT_HOME_RUN && hitType == BAT_CONTACT_TYPE_CHARGE && chargeUp >= 1.0f &&
                                    nonCaptainSwing == 0) {
                                    ct->inGameMissionTracker[i].starMissionStatus++;
                                    if (ct->inGameMissionTracker[i].starMissionStatus >= req[i].target) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            case STAR_MISSION_TYPE_HOME_RUN_WITH_DIDDY_AND_DIXIE_ON_BASE:
                                if (result == AT_BAT_RESULT_HOME_RUN) {
                                    int count = 0;
                                    int r;
                                    for (r = 1; r < 4; r++) {
                                        if (g_Runners[r].runnerOnFieldOrOutOrScored != RUNNER_STATUS_NONE &&
                                            (g_Runners[r].charID == CHAR_ID_DIDDY || g_Runners[r].charID == CHAR_ID_DIXIE)) {
                                            count++;
                                        }
                                    }
                                    if (count == 2) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            case STAR_MISSION_TYPE_BUNT_HITS:
                                if (result >= AT_BAT_RESULT_SINGLE && result <= AT_BAT_RESULT_HOME_RUN && hitType == BAT_CONTACT_TYPE_BUNT) {
                                    ct->inGameMissionTracker[i].starMissionStatus++;
                                    if (ct->inGameMissionTracker[i].starMissionStatus >= req[i].target) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            }
                            if (done) {
                                ct->inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY;
                            }
                        }
                    }
                }
            }
        }

        if (result == AT_BAT_RESULT_HOME_RUN) {
            CharacterStats* roster = inMemRoster[scout->humanTeam];
            StatisticsBatter* bs = BatterStats_P1_P2[scout->humanTeam];

            for (j = 0; j < PLAYERS_PER_TEAM; j++) {
                CharStaticIndex* rc = &characterStaticIndexes[roster[j].stats.CharID];
                ChallengeTrackingStruct* rct = MISSION_TRACKER(rc);
                StarMissionRequirement* rreq = MISSION_REQS(rc);
                for (i = 0; i < STAR_MISSIONS_PER_CHARACTER; i++) {
                    if (rct->inGameMissionTracker[i].starMissionStatus >= 0 && rreq[i].type == STAR_MISSION_TYPE_HOME_RUN_WITH_TEAMMATE &&
                        rreq[i].target == characterStaticIndexes[g_Batter.charID].requirementRow && bs[j].HomeRuns != 0) {
                        rct->inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY;
                    }
                }
            }
        }
    }
}

// .text:0x00162080 size:0x28C mapped:0x807A1114
void challenge_postPitchStarMissionTracking(void) {
    ScoutState* scout = &scoutState;
    int i;

    if (scout->humanTeam == g_GameLogic.teamFielding) {
        CharStaticIndex* pc = &characterStaticIndexes[g_Pitcher.charID];
        ChallengeTrackingStruct* ct = &g_Challenge.characters[pc->trackerIdx];
        StarMissionRequirement* req = MISSION_REQS(pc);
        for (i = 0; i < STAR_MISSIONS_PER_CHARACTER; i++) {
            if (ct->inGameMissionTracker[i].starMissionStatus >= 0) {
                StarMissionRequirement* mreq = &req[i];
                BOOL done = FALSE;
                if (mreq->type == STAR_MISSION_TYPE_STAR_PITCH_AND_STAR_SWING) {
                    if (g_Pitcher.starPitchType != 0) {
                        ct->inGameMissionTracker[i].starMissionStatus |= 1;
                        if (ct->inGameMissionTracker[i].starMissionStatus == 0x11) {
                            ct->inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY;
                        }
                    }
                } else {
                    int k;
                    u8 starPitch = g_Pitcher.starPitchType;
                    u8 chargePitch = g_Pitcher.ChargePitchType;
                    for (k = STAR_MISSION_TYPE_STRIKE_OUT_BATTER; k <= STAR_MISSION_TYPE_CHARGE_PITCHES; k++) {
                        if (mreq->type == k) {
                            switch (k) {
                            case STAR_MISSION_TYPE_STAR_PITCHES:
                                if (starPitch != 0) {
                                    ct->inGameMissionTracker[i].starMissionStatus++;
                                    if (ct->inGameMissionTracker[i].starMissionStatus >= mreq->target) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            case STAR_MISSION_TYPE_CHARGE_PITCHES:
                                if (chargePitch == 3) {
                                    ct->inGameMissionTracker[i].starMissionStatus++;
                                    if (ct->inGameMissionTracker[i].starMissionStatus >= mreq->target) {
                                        done = TRUE;
                                    }
                                }
                                break;
                            }
                            if (done) {
                                ct->inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY;
                            }
                        }
                    }
                }
            }
        }
    }

    if (scout->humanTeam == g_GameLogic.teamBatting) {
        CharStaticIndex* bc = &characterStaticIndexes[g_Batter.charID];
        ChallengeTrackingStruct* ct = &g_Challenge.characters[bc->trackerIdx];
        StarMissionRequirement* req = MISSION_REQS(bc);
        u8 starSwing = g_Ball.currentStarSwing2;
        u8 starChance = g_GameLogic.IsStarChance;
        u8 stadiumStar = g_GameLogic.stadiumStarObtained;
        for (i = 0; i < STAR_MISSIONS_PER_CHARACTER; i++) {
            if (ct->inGameMissionTracker[i].starMissionStatus >= 0) {
                if (req[i].type == STAR_MISSION_TYPE_STAR_PITCH_AND_STAR_SWING && starSwing != 0) {
                    ct->inGameMissionTracker[i].starMissionStatus |= 0x10;
                    if (ct->inGameMissionTracker[i].starMissionStatus == 0x11) {
                        ct->inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY;
                    }
                }
                if (req[i].type == STAR_MISSION_TYPE_STAR_CHANCES) {
                    if (starChance == 3 || stadiumStar != 0) {
                        ct->inGameMissionTracker[i].starMissionStatus++;
                        if (ct->inGameMissionTracker[i].starMissionStatus >= req[i].target) {
                            ct->inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY;
                        }
                    }
                }
            }
        }
    }
}

// .text:0x00161588 size:0xAF8 mapped:0x807A061C
void starMissionsQuantityBased(E(int, STAR_MISSION_EVENT) missionType, int rosterLocation) {
    s16 charID = inMemRoster[scoutState.humanTeam][rosterLocation].stats.CharID;
    u8 trackerIdx = characterStaticIndexes[charID].trackerIdx;
    u8 requirementRow = characterStaticIndexes[charID].requirementRow;
    ChallengeTrackingStruct* ct;
    StarMissionRequirement* req;
    int i;

#define QUANTITY_SIMPLE(reqType)                                   \
    ct = &g_Challenge.characters[trackerIdx];                \
    req = starMissionRequirementsTable[requirementRow];            \
    for (i = 0; i < STAR_MISSIONS_PER_CHARACTER; i++) {                                     \
        if (ct->inGameMissionTracker[i].starMissionStatus >= 0) {  \
            switch (req[i].type) {                                 \
            case (reqType):                                        \
                MISSION_ADVANCE(ct, req, i);                       \
                break;                                             \
            }                                                      \
        }                                                          \
    }

    switch (missionType) {
    case STAR_MISSION_EVENT_NOTE_BLOCK_HIT:
        QUANTITY_SIMPLE(STAR_MISSION_TYPE_NOTE_BLOCK_HITS)
        break;
    case STAR_MISSION_EVENT_BALL_FIELDED:
        QUANTITY_SIMPLE(STAR_MISSION_TYPE_FIELD_BALLS)
        break;
    case STAR_MISSION_EVENT_ACTION_CATCH:
        QUANTITY_SIMPLE(STAR_MISSION_TYPE_UNK_37)
        break;
    case STAR_MISSION_EVENT_BIG_PLAY:
        ct = &g_Challenge.characters[trackerIdx];
        req = starMissionRequirementsTable[requirementRow];
        {
            int contact = g_Ball.AtBat_ContactResult;
            u8 starSwing = g_Ball.currentStarSwing;
            for (i = 0; i < STAR_MISSIONS_PER_CHARACTER; i++) {
                if (ct->inGameMissionTracker[i].starMissionStatus >= 0) {
                    switch (req[i].type) {
                    case STAR_MISSION_TYPE_BIG_PLAYS:
                        MISSION_ADVANCE(ct, req, i);
                        break;
                    case STAR_MISSION_TYPE_BIG_PLAY_CATCHES:
                        if (contact == BALL_RESULT_TYPE_CAUGHT) {
                            MISSION_ADVANCE(ct, req, i);
                        }
                        break;
                    case STAR_MISSION_TYPE_UNK_35:
                        break;
                    case STAR_MISSION_TYPE_UNK_36:
                        if (starSwing == 5 || starSwing == 6) {
                            MISSION_ADVANCE(ct, req, i);
                        }
                        break;
                    }
                }
            }
        }
        break;
    case STAR_MISSION_EVENT_CATCH_ANIM_6:
        QUANTITY_SIMPLE(STAR_MISSION_TYPE_UNK_35)
        break;
    case STAR_MISSION_EVENT_CATCH_ANIM_5: {
        int contact;
        ct = &g_Challenge.characters[trackerIdx];
        req = starMissionRequirementsTable[requirementRow];
        contact = g_Ball.AtBat_ContactResult;
        for (i = 0; i < STAR_MISSIONS_PER_CHARACTER; i++) {
            if (ct->inGameMissionTracker[i].starMissionStatus >= 0) {
                switch (req[i].type) {
                case STAR_MISSION_TYPE_UNK_38:
                    if (contact == BALL_RESULT_TYPE_CAUGHT) {
                        MISSION_ADVANCE(ct, req, i);
                    }
                    break;
                }
            }
        }
        break;
    }
    case STAR_MISSION_EVENT_TAG:
        QUANTITY_SIMPLE(STAR_MISSION_TYPE_UNK_39)
        break;
    case STAR_MISSION_EVENT_CHEMISTRY_THROW:
        ct = &g_Challenge.characters[trackerIdx];
        req = starMissionRequirementsTable[requirementRow];
        {
            s16* thrownTo = &g_Fielders[g_Ball.fielderBeingThrownTo].CharID;
            for (i = 0; i < STAR_MISSIONS_PER_CHARACTER; i++) {
                if (ct->inGameMissionTracker[i].starMissionStatus >= 0) {
                    switch (req[i].type) {
                    case STAR_MISSION_TYPE_CHEMISTRY_THROW_TO:
                        if (req[i].target == characterStaticIndexes[*thrownTo].requirementRow) {
                            ct->inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY;
                        }
                        break;
                    }
                }
            }
        }
        break;
    case STAR_MISSION_EVENT_LASER_THROW_OUT:
        QUANTITY_SIMPLE(STAR_MISSION_TYPE_LASER_THROW_OUTS)
        break;
    case STAR_MISSION_EVENT_HANDLED_BALL_NO_THROW: {
        int contact;
        ct = &g_Challenge.characters[trackerIdx];
        req = starMissionRequirementsTable[requirementRow];
        contact = g_Ball.AtBat_ContactResult;
        for (i = 0; i < STAR_MISSIONS_PER_CHARACTER; i++) {
            if (ct->inGameMissionTracker[i].starMissionStatus >= 0) {
                switch (req[i].type) {
                case STAR_MISSION_TYPE_UNK_42:
                    if (contact == BALL_RESULT_TYPE_CAUGHT) {
                        MISSION_ADVANCE(ct, req, i);
                    }
                    break;
                }
            }
        }
        break;
    }
    case STAR_MISSION_EVENT_STOLEN_BASE:
        QUANTITY_SIMPLE(STAR_MISSION_TYPE_STOLEN_BASES)
        break;
    case STAR_MISSION_EVENT_RUN_SCORED:
        QUANTITY_SIMPLE(STAR_MISSION_TYPE_RUNS_SCORED)
        break;
    case STAR_MISSION_EVENT_BODY_CHECK:
        QUANTITY_SIMPLE(STAR_MISSION_TYPE_BODY_CHECKS)
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
    StarMissionRequirement* req = starMissionRequirementsTable[requirementRow];
    ChallengeTrackingStruct* ct = &g_Challenge.characters[trackerIdx];
    u8 mode = g_Minigame.GameMode_MiniGame;
    u8 difficulty = g_d_GameSettings.challengeDifficulty;
    int i;
    int j;
    int k;

    for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++) {
        s8 status = ct->inGameMissionTracker[j].starMissionStatus;

        if (status == STAR_MISSION_TRACKING_COMPLETED_SAVED) {
            continue;
        }
        if (status == STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY) {
            if (req[j].flags & STAR_MISSION_FLAG_MIN_DIFFICULTY_1) {
                if (difficulty < 1) {
                    ct->inGameMissionTracker[j].starMissionStatus = STAR_MISSION_TRACKING_NOT_COMPLETED;
                }
            } else if (req[j].flags & STAR_MISSION_FLAG_MIN_DIFFICULTY_2) {
                if (difficulty < 2) {
                    ct->inGameMissionTracker[j].starMissionStatus = STAR_MISSION_TRACKING_NOT_COMPLETED;
                }
            } else if (req[j].flags & STAR_MISSION_FLAG_MIN_DIFFICULTY_3) {
                if (difficulty < 3) {
                    ct->inGameMissionTracker[j].starMissionStatus = STAR_MISSION_TRACKING_NOT_COMPLETED;
                }
            }
            if (req[j].flags & STAR_MISSION_FLAG_REQUIRES_WIN) {
                if (g_Minigame.playerSlots.rank[slot] != 1) {
                    ct->inGameMissionTracker[j].starMissionStatus = STAR_MISSION_TRACKING_NOT_COMPLETED;
                }
            }
            continue;
        }

        if (req[j].flags & STAR_MISSION_FLAG_MIN_DIFFICULTY_1) {
            if (difficulty < 1) {
                continue;
            }
        } else if (req[j].flags & STAR_MISSION_FLAG_MIN_DIFFICULTY_2) {
            if (difficulty < 2) {
                continue;
            }
        } else if (req[j].flags & STAR_MISSION_FLAG_MIN_DIFFICULTY_3) {
            if (difficulty < 3) {
                continue;
            }
        }
        if ((req[j].flags & STAR_MISSION_FLAG_REQUIRES_WIN) && g_Minigame.playerSlots.rank[slot] != 1) {
            continue;
        }
        {
            BOOL anyModeFlag = FALSE;
            BOOL modeMatches = FALSE;

            for (k = 0; k < 7; k++) {
                if (req[j].flags & STAR_MISSION_FLAG_MINI_GAME(k)) {
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
        case STAR_MISSION_TYPE_MINIGAME_RANK:
            if (g_Minigame.playerSlots.rank[slot] <= req[j].target) {
                ct->inGameMissionTracker[j].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY;
            }
            break;
        case STAR_MISSION_TYPE_MINIGAME_POINTS: {
            int target = req[j].target;

            if (mode == MINI_GAME_ID_BOBOMB_DERBY || mode == MINI_GAME_ID_BARREL_BATTER) {
                target *= 100;
            } else if (mode == MINI_GAME_ID_NONE || mode == MINI_GAME_ID_WALLBALL) {
                target *= 10;
            }
            if (g_Minigame.miniGameCurrentPoints[slot] >= target) {
                ct->inGameMissionTracker[j].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY;
            }
            break;
        }
        case STAR_MISSION_TYPE_MINIGAME_BEAT_CHARACTER: {
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
                ct->inGameMissionTracker[j].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY;
            }
            break;
        }
        case STAR_MISSION_TYPE_UNK_54:
            if (mode == MINI_GAME_ID_PIRANHA_PANIC && g_Minigame._1CB1[slot] <= req[j].target) {
                ct->inGameMissionTracker[j].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY;
            }
            break;
        }
    }

    for (i = 0; i < NUM_CHOOSABLE_CHARACTERS; i++) {
        for (j = 0; j < STAR_MISSIONS_PER_CHARACTER; j++) {
            if (g_Challenge.characters[i].inGameMissionTracker[j].starMissionStatus <= -1) {
                g_Challenge.characters[i].inGameMissionTracker[j].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_SAVED;
            } else {
                g_Challenge.characters[i].inGameMissionTracker[j].starMissionStatus = STAR_MISSION_TRACKING_NOT_COMPLETED;
            }
        }
    }
}

// .text:0x001608F0 size:0x788
void starMissionsMinigamesSpecialAction(E(int, STAR_MISSION_MINIGAME_EVENT) missionType, int points, int barrelsHit) {
    BOOL found = FALSE;
    u8 charID = g_Minigame.playerSlots.charID[g_d_GameSettings._35];
    u8 requirementRow = characterStaticIndexes[charID].requirementRow;
    u8 trackerIdx = characterStaticIndexes[charID].trackerIdx;
    int i;

#define SPECIAL_LOOP_BEGIN(TYPE)                                                             \
    {                                                                                        \
        ChallengeTrackingStruct* ct = &g_Challenge.characters[trackerIdx];             \
        StarMissionRequirement* req = starMissionRequirementsTable[requirementRow];          \
        for (i = 0; i < STAR_MISSIONS_PER_CHARACTER; i++) {                                                           \
            if (ct->inGameMissionTracker[i].starMissionStatus >= 0) {                        \
                switch (req[i].type) {                                                       \
                case TYPE:
#define SPECIAL_LOOP_END                                                                     \
                    break;                                                                   \
                }                                                                            \
            }                                                                                \
        }                                                                                    \
    }

#define SPECIAL_ADVANCE                                                                      \
    ct->inGameMissionTracker[i].starMissionStatus++;                                         \
    if (ct->inGameMissionTracker[i].starMissionStatus >= req[i].target) {                    \
        found = TRUE;                                                                        \
        goto missionFound;                                                                   \
    }

    switch (missionType) {
    case STAR_MISSION_MINIGAME_EVENT_BOBOMB_DERBY_HIT:
        SPECIAL_LOOP_BEGIN(STAR_MISSION_TYPE_UNK_50)
            if (points >= req[i].target) {
                found = TRUE;
                goto missionFound;
            }
        SPECIAL_LOOP_END
        break;
    case STAR_MISSION_MINIGAME_EVENT_WALL_BALL_NOTE_BLOCKS:
        SPECIAL_LOOP_BEGIN(STAR_MISSION_TYPE_UNK_51)
            if (barrelsHit != 0) {
                SPECIAL_ADVANCE
            } else {
                ct->inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_NOT_COMPLETED;
            }
        SPECIAL_LOOP_END
        break;
    case STAR_MISSION_MINIGAME_EVENT_BARREL_BATTER_BARRELS:
        SPECIAL_LOOP_BEGIN(STAR_MISSION_TYPE_UNK_52)
            if (barrelsHit >= 15) {
                SPECIAL_ADVANCE
            }
        SPECIAL_LOOP_END
        break;
    case STAR_MISSION_MINIGAME_EVENT_CHAIN_CHOMP_SPRINT:
        SPECIAL_LOOP_BEGIN(STAR_MISSION_TYPE_UNK_53)
            if (points == 2) {
                SPECIAL_ADVANCE
            }
        SPECIAL_LOOP_END
        break;
    case STAR_MISSION_MINIGAME_EVENT_PIRANHA_PANIC:
        SPECIAL_LOOP_BEGIN(STAR_MISSION_TYPE_UNK_55)
            if (points == 4) {
                SPECIAL_ADVANCE
            }
        SPECIAL_LOOP_END
        break;
    case STAR_MISSION_MINIGAME_EVENT_UNKNOWN_6:
        SPECIAL_LOOP_BEGIN(STAR_MISSION_TYPE_UNK_56)
            SPECIAL_ADVANCE
        SPECIAL_LOOP_END
        break;
    case STAR_MISSION_MINIGAME_EVENT_TOY_FIELD:
        SPECIAL_LOOP_BEGIN(STAR_MISSION_TYPE_UNK_57)
            if (points == req[i].target) {
                found = TRUE;
                goto missionFound;
            }
        SPECIAL_LOOP_END
        break;
    }

missionFound:
    if (found) {
        g_Challenge.characters[trackerIdx].inGameMissionTracker[i].starMissionStatus = STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY;
    }
}
