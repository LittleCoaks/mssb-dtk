#ifndef __GAME_CHALLENGE_SCOUT_STATE_H_
#define __GAME_CHALLENGE_SCOUT_STATE_H_

#include "mssbTypes.h"

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
    /*0x46*/ u8 scoutMissionID; // 0 = none, see scoutMissionTable
    /*0x47*/ u8 scoutResult;    // 0 = failed / undecided, 2 = succeeded
    /*0x48*/ u8 scoutFlag;      // 1 while the mission is still running, 2 = to be cleared
    /*0x49*/ s8 baseReward;
    /*0x4A*/ s8 chanceTier; // 0 selects ScoutMission.chanceA, otherwise chanceB
    /*0x4B*/ u8 _4B[3];
} ScoutState; // size: 0x4E

extern ScoutState scoutState;

#endif // !__GAME_CHALLENGE_SCOUT_STATE_H_
