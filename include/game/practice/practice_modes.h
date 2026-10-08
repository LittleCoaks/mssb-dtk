#ifndef __GAME_PRACTICE_PRACTICE_MODES_H_
#define __GAME_PRACTICE_PRACTICE_MODES_H_

#include "mssbTypes.h"

void fieldingPracticeResetTutorialState(void);
void fieldingPracticeControl(void);
void fieldingPracticeRelated(void);
void fieldingPracticeInitialization(void);
BOOL practiceRelatedUnused(void);
void fieldingPracticePrepareNextPlay(void);
void fieldingPracticeBeginPlay(void);
void fieldingPracticeAtBat(void);
void fieldingPracticeLiveBall(void);
void practice_fieldingRelated(void);
void fieldingPracticeEndPlay(void);
void fieldingPracticeSetPitcherConstants(void);
void fn_3_B0D78(void);
void fieldingPracticeAISwingDecision(void);
int batterAI_buntForPractice(void);
void fieldingPractice_setHitVariables(void);
void battingPracticeControl(void);
void battingPracticeResetTutorialState(void);
void battingPracticeSwitcher(void);
void battingPracticeSomething(void);
BOOL battingPracticeUpdateCompletion(void);
void battingPracticePrepareNextPlay(void);
void battingPracticeRelated(void);
void someBattingPitchingCallFuns(void);
void battingPracticeLiveBall(void);
void guidedPracticeRelated(void);
void practiceRelatedPostPlay(void);
void battingPracticeEndPlay(void);

#endif // !__GAME_PRACTICE_PRACTICE_MODES_H_
