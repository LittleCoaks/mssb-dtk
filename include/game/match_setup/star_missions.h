#ifndef __GAME_MATCH_SETUP_STAR_MISSIONS_H_
#define __GAME_MATCH_SETUP_STAR_MISSIONS_H_

#include "mssbTypes.h"

void starMissionsQuantityBased(int missionType, int rosterLocation);
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
void challengeModeRelated_checkScoutMissionSuccess(void);
void clearScoutState(void);
void fn_3_165978(void);
void setScoutMissionRelatedToZero(void);
BOOL shouldScoutMissionBeEnabled(int mission);
BOOL decideScoutFlagMission(void);
void fn_3_1663AC(void);

#endif // !__GAME_MATCH_SETUP_STAR_MISSIONS_H_
