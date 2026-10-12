#ifndef __GAME_CHALLENGE_STAR_MISSION_DATA_H_
#define __GAME_CHALLENGE_STAR_MISSION_DATA_H_

#include "mssbTypes.h"
#include "game/challenge/challenge_state.h"

// Bits of StarMissionRequirement.flags.
typedef enum _STAR_MISSION_FLAG {
    STAR_MISSION_FLAG_REQUIRES_WIN = 0x1, // mission only counts in a won game / minigame
    STAR_MISSION_FLAG_MIN_DIFFICULTY_1 = 0x2, // only counts when challengeDifficulty >= 1
    STAR_MISSION_FLAG_MIN_DIFFICULTY_2 = 0x4,
    STAR_MISSION_FLAG_MIN_DIFFICULTY_3 = 0x8,
    STAR_MISSION_FLAG_BOWSER_UNLOCK = 0x800, // hidden until the Bowser fight has been unlocked
} STAR_MISSION_FLAG;

// Restricts a minigame mission to GameMode_MiniGame == id (ids 0..6).
#define STAR_MISSION_FLAG_MINI_GAME(id) (0x10 << (id))

// Values of StarMissionRequirement.type. Types without a name are handled by event-driven code (see
// starMissionsQuantityBased / starMissionsMinigamesSpecialAction) whose meaning is not pinned down yet.
typedef enum _STAR_MISSION_TYPE {
    STAR_MISSION_TYPE_NONE = -1,
    STAR_MISSION_TYPE_WIN_AT_STADIUM = 0,
    STAR_MISSION_TYPE_WIN_AS_MVP = 1,
    STAR_MISSION_TYPE_STAR_CHANCES = 2,
    STAR_MISSION_TYPE_STAR_PITCH_AND_STAR_SWING = 3,
    STAR_MISSION_TYPE_STRIKE_OUT_BATTER = 4,
    STAR_MISSION_TYPE_HIT_BATTER_WITH_PITCH = 5,
    STAR_MISSION_TYPE_SHUTOUT_AGAINST_CAPTAIN = 6,
    STAR_MISSION_TYPE_NO_HITTER = 7,
    STAR_MISSION_TYPE_COMPLETE_GAME = 8,
    STAR_MISSION_TYPE_SHUTOUT = 9,
    STAR_MISSION_TYPE_STRIKEOUTS = 10,
    STAR_MISSION_TYPE_STAR_PITCHES = 11,
    STAR_MISSION_TYPE_CHARGE_PITCHES = 12,
    STAR_MISSION_TYPE_HOME_RUN_IN_INNING = 13,
    STAR_MISSION_TYPE_HOME_RUN_WITH_RBIS = 14,
    STAR_MISSION_TYPE_HIT_AT_LEAST_BASES = 15,
    STAR_MISSION_TYPE_HIT_OFF_PITCHER = 16,
    STAR_MISSION_TYPE_HOME_RUN_OFF_PITCHER = 17,
    STAR_MISSION_TYPE_RBI_OFF_PITCHER = 18,
    STAR_MISSION_TYPE_HITS = 19,
    STAR_MISSION_TYPE_BUNTS = 20,
    STAR_MISSION_TYPE_BUNT_FORCES_IN_RUN = 21,
    STAR_MISSION_TYPE_RBIS = 22,
    STAR_MISSION_TYPE_HOME_RUNS = 23,
    STAR_MISSION_TYPE_STAR_SWING_RBIS = 24,
    STAR_MISSION_TYPE_BATTING_AVERAGE = 25,
    STAR_MISSION_TYPE_NO_STRIKEOUTS = 26,
    STAR_MISSION_TYPE_CHARGE_HITS = 27,
    STAR_MISSION_TYPE_HOME_RUN_WITH_DIDDY_AND_DIXIE_ON_BASE = 28,
    STAR_MISSION_TYPE_BUNT_HITS = 29,
    STAR_MISSION_TYPE_HOME_RUN_WITH_TEAMMATE = 30,
    STAR_MISSION_TYPE_NOTE_BLOCK_HITS = 31,
    STAR_MISSION_TYPE_FIELD_BALLS = 32,
    STAR_MISSION_TYPE_BIG_PLAYS = 33,
    STAR_MISSION_TYPE_BIG_PLAY_CATCHES = 34,
    STAR_MISSION_TYPE_UNK_35 = 35,
    STAR_MISSION_TYPE_UNK_36 = 36,
    STAR_MISSION_TYPE_UNK_37 = 37,
    STAR_MISSION_TYPE_UNK_38 = 38,
    STAR_MISSION_TYPE_UNK_39 = 39,
    STAR_MISSION_TYPE_CHEMISTRY_THROW_TO = 40,
    STAR_MISSION_TYPE_LASER_THROW_OUTS = 41,
    STAR_MISSION_TYPE_UNK_42 = 42,
    STAR_MISSION_TYPE_DOUBLE_PLAY_WITH = 43,
    STAR_MISSION_TYPE_STOLEN_BASES = 44,
    STAR_MISSION_TYPE_RUNS_SCORED = 45,
    STAR_MISSION_TYPE_BODY_CHECKS = 46,
    STAR_MISSION_TYPE_MINIGAME_RANK = 47,
    STAR_MISSION_TYPE_MINIGAME_POINTS = 48,
    STAR_MISSION_TYPE_MINIGAME_BEAT_CHARACTER = 49,
    STAR_MISSION_TYPE_UNK_50 = 50,
    STAR_MISSION_TYPE_UNK_51 = 51,
    STAR_MISSION_TYPE_UNK_52 = 52,
    STAR_MISSION_TYPE_UNK_53 = 53,
    STAR_MISSION_TYPE_UNK_54 = 54,
    STAR_MISSION_TYPE_UNK_55 = 55,
    STAR_MISSION_TYPE_UNK_56 = 56,
    STAR_MISSION_TYPE_UNK_57 = 57,
    STAR_MISSION_TYPE_UNK_58 = 58,
    STAR_MISSION_TYPE_UNK_59 = 59,
    STAR_MISSION_TYPE_UNK_65 = 65,
    STAR_MISSION_TYPE_UNK_70 = 70,
    STAR_MISSION_TYPE_UNK_71 = 71,
    STAR_MISSION_TYPE_UNK_72 = 72,
    STAR_MISSION_TYPE_UNK_73 = 73,
} STAR_MISSION_TYPE;

// One of the ten star missions of a character.
typedef struct _StarMissionRequirement {
    /*0x0*/ E(s16, STAR_MISSION_TYPE) type; // STAR_MISSION_TYPE_NONE marks an unused slot
    /*0x2*/ s16 target;
    /*0x4*/ E(s16, STAR_MISSION_FLAG) flags; // STAR_MISSION_FLAG bits
    /*0x6*/ s16 _6[2];
} StarMissionRequirement; // size: 0xA

// How a star mission is listed on the pause / mission menu.
typedef struct _StarMissionDisplayRule {
    /*0x0*/ s16 textID;   // description text; 455 for an unused slot
    /*0x2*/ s16 mode;     // 0 = always shown, 1 = shown once enough stars are earned, -1 = unused slot
    /*0x4*/ s16 minStars;
    /*0x6*/ s16 minScoutRow;
    /*0x8*/ s16 _8;
} StarMissionDisplayRule; // size: 0xA

// Scout mission tuning, indexed by scout mission id (0 is unused).
typedef struct _ScoutMission {
    /*0x0*/ s8 chanceA[4]; // percent chance to start the mission, by difficulty
    /*0x4*/ s8 chanceB[4]; // same, used while ScoutState._4A != 0
    /*0x8*/ u8 _8;
    /*0x9*/ s8 reward[4];  // scout flags awarded by outcome
    /*0xD*/ s8 starMission; // set when completing it also counts as a star mission
    /*0xE*/ u8 _E;
} ScoutMission; // size: 0xF

// Per-character lookup (indexed by CHAR_ID) into the tracker and requirement tables. Variants of a
// character share the primary's tracker and requirement row.
typedef struct _CharStaticIndex {
    /*0x0*/ u8 variantGroup;       // 0 for characters without variants
    /*0x1*/ E(u8, CHAR_ID) trackerIdx; // CHAR_ID of the group's primary character, indexes ChallengeState.characters
    /*0x2*/ u8 requirementRow;     // row of starMissionRequirementsTable
    /*0x3*/ u8 hasOwnStarMissions; // 0 for variants
    /*0x4*/ u8 _4;
    /*0x5*/ u8 variantIndex;       // position within the variant group, 0 for the primary
} CharStaticIndex; // size: 0x6

extern CharStaticIndex characterStaticIndexes[54];
extern ScoutMission scoutMissionTable[13];
extern StarMissionRequirement starMissionRequirementsTable[32][10];
extern StarMissionDisplayRule starMissionDisplayRules[32][10];
extern u16 starRankTextIDs[34];
extern s16 starMenuSizes[12];
extern s16 starRankByMissionCount[5][11];

#endif // !__GAME_CHALLENGE_STAR_MISSION_DATA_H_
