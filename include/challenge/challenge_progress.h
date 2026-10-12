#ifndef __CHALLENGE_CHALLENGE_PROGRESS_H_
#define __CHALLENGE_CHALLENGE_PROGRESS_H_

#include "mssbTypes.h"

void challengeDrawStarsOnMissionMenu(void);
BOOL fn_8006C5CC(void);
int fn_8006C6C4(void);
BOOL challenge_isCharRecruited(int charID);
void challenge_leftoverTeammatesJoinBowserJr(void);
void challenge_checkRecruitment(void);
f32 intermediateStatBuffForScoutFlags(void);
f32 intermediateStatBuffForCompletedMissions(int charID);
s16 challenge_getStarRank(int charID);
void determineIfMissionDescriptionIsShown(void);
void fn_8006CDC0(void);

#endif // !__CHALLENGE_CHALLENGE_PROGRESS_H_
