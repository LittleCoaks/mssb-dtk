#ifndef __GAME_MATCH_SETUP_STAR_MISSIONS_H_
#define __GAME_MATCH_SETUP_STAR_MISSIONS_H_

#include "mssbTypes.h"

void starMissionsQuantityBased(int missionType, int rosterLocation);
void challenge_postPitchStarMissionTracking(void);
void starMissionsOffensive_StarChange_DoublePlay(int result, int rbis);
void starMissionsWholeGame(void);
void recruitWholeTeamAfterMercy(void);
BOOL fn_3_163948(void);
BOOL fn_3_163A7C(void);
BOOL fn_3_163BD4(void);
void fn_3_163D34(void);
void fn_3_163E94(void);
void fn_3_16440C(void);
void fn_3_164554(void);
void fn_3_164664(void);
void challengeModeRelated_checkScoutMissionSuccess(void);
void fn_3_1658F0(void);
void fn_3_165978(void);
void setScoutMissionRelatedToZero(void);
BOOL shouldScoutMissionBeEnabled(int mission);
BOOL decideScoutFlagMission(void);
void fn_3_1663AC(void);

#endif // !__GAME_MATCH_SETUP_STAR_MISSIONS_H_
