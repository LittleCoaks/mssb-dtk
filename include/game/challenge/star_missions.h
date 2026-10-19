#ifndef __GAME_CHALLENGE_STAR_MISSIONS_H_
#define __GAME_CHALLENGE_STAR_MISSIONS_H_

#include "mssbTypes.h"
#include "game/challenge/scout_state.h"

// First argument of starMissionsQuantityBased: the fielding / running event being counted.
typedef enum _STAR_MISSION_EVENT {
    STAR_MISSION_EVENT_NOTE_BLOCK_HIT = 0,
    STAR_MISSION_EVENT_BALL_FIELDED = 1,
    STAR_MISSION_EVENT_BIG_PLAY = 2,
    STAR_MISSION_EVENT_ACTION_CATCH = 3,
    STAR_MISSION_EVENT_CATCH_ANIM_6 = 4,
    STAR_MISSION_EVENT_CATCH_ANIM_5 = 5,
    STAR_MISSION_EVENT_TAG = 6,
    STAR_MISSION_EVENT_CHEMISTRY_THROW = 7,
    STAR_MISSION_EVENT_LASER_THROW_OUT = 8,
    STAR_MISSION_EVENT_HANDLED_BALL_NO_THROW = 9,
    STAR_MISSION_EVENT_STOLEN_BASE = 10,
    STAR_MISSION_EVENT_RUN_SCORED = 11,
    STAR_MISSION_EVENT_BODY_CHECK = 12,
} STAR_MISSION_EVENT;

// First argument of starMissionsMinigamesSpecialAction, named after the minigame that reports it.
typedef enum _STAR_MISSION_MINIGAME_EVENT {
    STAR_MISSION_MINIGAME_EVENT_BOBOMB_DERBY_HIT = 0,
    STAR_MISSION_MINIGAME_EVENT_WALL_BALL_NOTE_BLOCKS = 1,
    STAR_MISSION_MINIGAME_EVENT_BARREL_BATTER_BARRELS = 2,
    STAR_MISSION_MINIGAME_EVENT_CHAIN_CHOMP_SPRINT = 3,
    STAR_MISSION_MINIGAME_EVENT_PIRANHA_PANIC = 5,
    STAR_MISSION_MINIGAME_EVENT_UNKNOWN_6 = 6,
    STAR_MISSION_MINIGAME_EVENT_TOY_FIELD = 7,
} STAR_MISSION_MINIGAME_EVENT;

void starMissionsQuantityBased(E(int, STAR_MISSION_EVENT) missionType, int rosterLocation);
void challenge_postPitchStarMissionTracking(void);
void starMissionsOffensive_StarChange_DoublePlay(int result, int rbis);
void starMissionsWholeGame(void);
void recruitWholeTeamAfterMercy(void);
BOOL anyScoutPairIncomplete(void);
BOOL isScoutTargetFlagAvailable(void);
BOOL anyScoutFlagIncomplete(void);
void snapshotScoutFlagProgress(void);
void assignScoutFlagRewardRandom(void);
void assignScoutFlagRewardToTarget(void);
void applyScoutFlagRewards(void);
void awardScoutFlagsSequential(void);
void scoutFlag_checkMissionSuccess(void);
void clearScoutState(void);
void resetScoutChanceTier_2(void);
void resetScoutChanceTier(void);
BOOL shouldScoutMissionBeEnabled(E(int, SCOUT_MISSION) mission);
BOOL decideScoutFlagMission(void);
void practice_postGraphicsUpdate(void);

void starMissionsMinigamesTotalPoints(void);
void starMissionsMinigamesSpecialAction(E(int, STAR_MISSION_MINIGAME_EVENT) missionType, int points, int barrelsHit);

#endif // !__GAME_CHALLENGE_STAR_MISSIONS_H_
