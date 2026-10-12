#ifndef __CHALLENGE_STATE_H_
#define __CHALLENGE_STATE_H_

#include "mssbTypes.h"

#define STAR_MISSIONS_PER_CHARACTER 10

typedef enum _CHALLENGE_CAPTAIN {
    CHALLENGE_CAPTAIN_MARIO,
    CHALLENGE_CAPTAIN_PEACH,
    CHALLENGE_CAPTAIN_WARIO,
    CHALLENGE_CAPTAIN_DK,
    CHALLENGE_CAPTAIN_YOSHI,
    CHALLENGE_CAPTAIN_BOWSER,
} CHALLENGE_CAPTAIN;

typedef enum _CHARACTER_VARIANT_CLASSIFICATION {
    CHARACTER_VARIANT_CLASSIFICATION_PRIMARY_CAPTAIN,
    CHARACTER_VARIANT_CLASSIFICATION_SECONDARY_CAPTAIN,
    CHARACTER_VARIANT_CLASSIFICATION_UNIQUE_NON_CAPTAIN,
    CHARACTER_VARIANT_CLASSIFICATION_PRIMARY_VARIANT,
    CHARACTER_VARIANT_CLASSIFICATION_SECONDARY_VARIANT,
} CHARACTER_VARIANT_CLASSIFICATION;

// starMissionStatus: values >= 0 are progress counters (bit 0 / bit 4 also track the two halves of
// STAR_MISSION_TYPE_STAR_PITCH_AND_STAR_SWING); negative values mean completed.
typedef enum _STAR_MISSION_TRACKING {
    STAR_MISSION_TRACKING_COMPLETED_SAVED = -2, // completed in an earlier game and written to the save
    STAR_MISSION_TRACKING_COMPLETED_CONDITIONALLY = -1, // completed in this game; kept or reset by the game result
    STAR_MISSION_TRACKING_NOT_COMPLETED = 0,
    STAR_MISSION_TRACKING_TRACK1_COMPLETION = 1,
} STAR_MISSION_TRACKING;

typedef enum _CHALLENGE_RECRUITMENT_CD {
    CHALLENGE_RECRUITMENT_CD_NOT_RECRUITED,
    CHALLENGE_RECRUITMENT_CD_RECRUITED,
    CHALLENGE_RECRUITMENT_CD_ON_BJ_TEAM,
} CHALLENGE_RECRUITMENT_CD;

typedef struct _starMissionTrackingPair {
    /*0x000*/ E(s8, STAR_MISSION_TRACKING) starMissionStatus;
    /*0x001*/ u8 shownOnPauseMenu;
} starMissionTrackingPair;

// Per-character scout flag record: seeds the tracker's captain / variant and gives the scout flags
// needed to recruit the character, by difficulty and captain.
typedef struct _ScoutFlagTable {
    /*0x00*/ E(u8, CHALLENGE_CAPTAIN) challengeCaptain;
    /*0x01*/ E(s8, CHARACTER_VARIANT_CLASSIFICATION) variantClassification;
    /*0x02*/ u8 _2;
    /*0x03*/ u8 _3;
    /*0x04*/ s8 flagsRequired[4][6]; // [difficulty][CHALLENGE_CAPTAIN]
} ScoutFlagTable; // size: 0x1C

extern ScoutFlagTable scoutFlagTables[55];

// This is pack disabled in ghidra.
typedef struct _ChallengeTrackingStruct {
    /*0x000*/ ScoutFlagTable* scoutFlagPointer;
    /*0x004*/ E(u8, CHALLENGE_CAPTAIN) challengeCaptain; // Created by retype action
    /*0x005*/ E(s8, CHARACTER_VARIANT_CLASSIFICATION) variantClassification;
    /*0x006*/ u8 scoutFlagsAchieved;
    /*0x007*/ u8 _7;
    /*0x008*/ u8 _8;
    /*0x009*/ starMissionTrackingPair inGameMissionTracker[STAR_MISSIONS_PER_CHARACTER];
    /*0x01D*/ starMissionTrackingPair saveFileMissionTracker[STAR_MISSIONS_PER_CHARACTER];
    /*0x031*/ E(u8, CHALLENGE_RECRUITMENT_CD) _31;
    /*0x032*/ u8 _32;
    /*0x033*/ u8 _33;
} ChallengeTrackingStruct; // size: 0x34

// Saved Challenge-mode lineup slot.
typedef struct _SavedChallengeSlot {
    /*0x0*/ s16 charID;
    /*0x2*/ u8 battingOrder;
    /*0x3*/ u8 fieldingPosition;
    /*0x4*/ u8 handedness; // FieldingArm * 2 + BattingStance
    /*0x5*/ u8 _5;
} SavedChallengeSlot; // size: 0x6

// Whole Challenge-mode state block: per-character star mission tracking, then lineup and scout flag state.
typedef struct _ChallengeState {
    /*0x0000*/ ChallengeTrackingStruct characters[54];
    /*0x0AF8*/ u8 _0AF8[0x16C0 - 0xAF8];
    /*0x16C0*/ s16 _16C0; // menus write 0x30 / 0x32 / 0x12 here, mirrored into _16C2
    /*0x16C2*/ s16 _16C2; // tested against 0x2A in the same conditions as captainSelectedID[1] == CHAR_ID_BOWSER
    /*0x16C4*/ u8 _16C4[0x40B8 - 0x16C4];
    /*0x40B8*/ SavedChallengeSlot savedLineup[9];
    /*0x40EE*/ u8 _40EE[0x43C0 - 0x40EE];
    /*0x43C0*/ s16 scoutTargetTrackerIdx; // characters[] index of the character the current scout mission is about
    /*0x43C2*/ s8 _43C2[0x43D6 - 0x43C2]; // flags indexed by menu entry (== 1 shows the entry)
    /*0x43D6*/ u8 charIsSuperstar[54]; // indexed by CHAR_ID; challenge-mode counterpart of superstarUnlocked
    /*0x440C*/ u8 _440C[0x4415 - 0x440C];
    /*0x4415*/ u8 difficulty; // row of the scout flag max tables and the CPU star buff tables
    /*0x4416*/ u8 _4416[0x441C - 0x4416];
    /*0x441C*/ E(u8, CHALLENGE_CAPTAIN) captain; // column of the scout flag max tables
    /*0x441D*/ E(u8, CHAR_ID) captainCharID;
    /*0x441E*/ E(u8, CHALLENGE_CAPTAIN) opponentCaptain;
    /*0x441F*/ E(u8, CHAR_ID) opponentCaptainCharID;
    /*0x4420*/ u8 _4420[0x4422 - 0x4420];
    /*0x4422*/ u8 stage; // column of challengeIntermediateStarBUffs_CPU; >= 4 / >= 5 gate the Bowser fight handling
    /*0x4423*/ u8 _4423[0x4445 - 0x4423];
    /*0x4445*/ u8 resumeSavedTeams;
    /*0x4446*/ u8 _4446[0x444D - 0x4446];
    /*0x444D*/ E(u8, BOOL) recruitedChar[54];
    /*0x4483*/ u8 _4483[0x44EF - 0x4483];
    /*0x44EF*/ s8 _44EF;
    /*0x44F0*/ s8 _44F0;
    /*0x44F1*/ u8 scoutMissionPending; // set when a scout mission starts, cleared when it hands over to a star mission
    /*0x44F2*/ u8 _44F2; // menus test this against 4
    /*0x44F3*/ u8 _44F3[0x4508 - 0x44F3];
} ChallengeState; // size: 0x4508

extern ChallengeState starMissionCompletionTracker;

// Innings rules by challengeDifficulty.
typedef struct _ChallengeInningRule {
    /*0x0*/ u8 inningLimit;
    /*0x1*/ u8 finalBossInningLimit; // used against Bowser's team
    /*0x2*/ u8 mercyThreshold;       // run lead that ends the game
} ChallengeInningRule; // size: 0x3

extern ChallengeInningRule challengeInnings[4];

#endif
