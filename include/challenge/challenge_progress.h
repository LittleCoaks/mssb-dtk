#ifndef __CHALLENGE_CHALLENGE_PROGRESS_H_
#define __CHALLENGE_CHALLENGE_PROGRESS_H_

#include "mssbTypes.h"

void challengeDrawStarsOnMissionMenu(void);
BOOL challenge_hasRecruitedEnoughNonBowserCharacters(void);
int challenge_countRecruitedCharacters(void);
BOOL challenge_isCharRecruited(int charID);
void challenge_leftoverTeammatesJoinBowserJr(void);
void challenge_checkRecruitment(void);
f32 intermediateStatBuffForScoutFlags(void);
f32 intermediateStatBuffForCompletedMissions(int charID);
s16 challenge_getStarRank(int charID);
int determineIfMissionDescriptionIsShown(int charID);
int fn_8006CDC0(int charID);

#endif // !__CHALLENGE_CHALLENGE_PROGRESS_H_
