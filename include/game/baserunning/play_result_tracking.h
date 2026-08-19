#ifndef __GAME_BASERUNNING_PLAY_RESULT_TRACKING_H_
#define __GAME_BASERUNNING_PLAY_RESULT_TRACKING_H_

#include "mssbTypes.h"

void postPlayTrackStats(void);
void pickoff_infieldThrow_related(void);
void monitorForErrors(void);
void update_runnersBeingTargetedWhileBatterCanBeForcedOut(void);
void initialize_runnersBeingTargetedWhileBatterCanBeForcedOut(void);
void fn_3_79338(void);
void runnerResultCd_bunt(void);
void adjustTotalBasesOnHit(void);

#endif // !__GAME_BASERUNNING_PLAY_RESULT_TRACKING_H_
