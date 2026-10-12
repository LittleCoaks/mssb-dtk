#ifndef __GAME_CHALLENGE_SCOUT_STATE_H_
#define __GAME_CHALLENGE_SCOUT_STATE_H_

#include "mssbTypes.h"

// ScoutState.scoutMissionID; indexes scoutMissionTable. 1 and 2 target one flagged character (see
// ChallengeState.scoutTargetTrackerIdx), the others are random scout flag rewards. Names describe the
// success condition in scoutFlag_checkMissionSuccess and the start condition in decideScoutFlagMission.
typedef enum _SCOUT_MISSION {
    SCOUT_MISSION_NONE = 0,
    SCOUT_MISSION_RETIRE_FLAGGED_BATTER = 1,
    SCOUT_MISSION_REACH_BASE_VS_FLAGGED_PITCHER = 2,
    SCOUT_MISSION_SCORE_IN_CAPTAIN_DUEL = 3,
    SCOUT_MISSION_TAKE_THE_LEAD = 4,
    SCOUT_MISSION_HOLD_SCORELESS_INNING = 5,
    SCOUT_MISSION_TURN_DOUBLE_PLAY = 6,
    SCOUT_MISSION_STRIKE_OUT_CAPTAIN = 7,
    SCOUT_MISSION_RETIRE_SIDE_IN_ORDER = 8,
    SCOUT_MISSION_SAC_FLY = 9,
    SCOUT_MISSION_SQUEEZE_BUNT = 10,
    SCOUT_MISSION_STEAL_SECOND_BASE = 11,
    SCOUT_MISSION_WIN_BOWSER_JR_GAME = 12,
} SCOUT_MISSION;

typedef enum _SCOUT_RESULT {
    SCOUT_RESULT_PENDING = 0,
    SCOUT_RESULT_FAILED = 1,
    SCOUT_RESULT_SUCCEEDED = 2,
} SCOUT_RESULT;

// Scout flag progress of one roster slot.
typedef struct _ScoutPair {
    /*0x0*/ s8 cur;
    /*0x1*/ s8 max;
} ScoutPair;

// One entry of the scout flag progress banner (hud_scoreboard).
typedef struct _ScoutEntry {
    /*0x0*/ u8 achieved; // flags the character already has
    /*0x1*/ s8 max;      // flags needed
    /*0x2*/ s8 amount;   // flags this mission is worth
    /*0x3*/ s8 active;
    /*0x4*/ s8 trackerIdx; // ChallengeState.characters index shown on the banner
} ScoutEntry; // size: 0x5

// State of the current scout mission (Challenge mode).
typedef struct _ScoutState {
    /*0x00*/ ScoutPair pairs[9];
    /*0x12*/ ScoutEntry entries[9];
    /*0x3F*/ u8 _3F;
    /*0x40*/ s16 humanTeam;
    /*0x42*/ s16 scoutCountdown;
    /*0x44*/ s16 targetRosterID;
    /*0x46*/ E(u8, SCOUT_MISSION) scoutMissionID;
    /*0x47*/ E(u8, SCOUT_RESULT) scoutResult;
    /*0x48*/ u8 scoutFlag;      // 1 while the mission is still running, 2 = to be cleared
    /*0x49*/ s8 baseReward;
    /*0x4A*/ s8 chanceTier; // 0 selects ScoutMission.chanceA, otherwise chanceB
    /*0x4B*/ u8 _4B[3];
} ScoutState; // size: 0x4E

extern ScoutState scoutState;

#endif // !__GAME_CHALLENGE_SCOUT_STATE_H_
