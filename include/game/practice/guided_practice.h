#ifndef __GAME_PRACTICE_GUIDED_PRACTICE_H_
#define __GAME_PRACTICE_GUIDED_PRACTICE_H_

#include "mssbTypes.h"

extern s16 battingPractice_resultDelayFrames[];
extern u8 guidedPracticeThresholds[][4];
extern s16 hitVarsForFieldingPractice[][3];
extern s16 hitVarsForFieldingPractice_level1[][3];
extern s16 hitVarsForFieldingPractice_level2[][3];
extern s16 hitVarsForFieldingPractice_level3[][3];
extern s16 fieldingPractice_frameThresholds[];
extern void* practice_instructions_pitchingPtrs[4];
extern void* practice_instructions_battingPtrs[4];
extern void* practice_instructions_fieldingPtrs[4];

void practiceRelatedInit(void);
void practiceResetInputs(void);
void practiceResetPauseMenuState(void);
void practiceLogicRelatedPause(void);
void practiceMenuLogic(void);
BOOL practice_checkForPause(void);
void practiceOpenPauseMenu(void);
void practicePauseRelated(void);
void practicePauseMenuControl(void);
void practice_pause_unloadPauseMenu(void);
void practice_giveAndDemonstrateInstructions(void);
int setUpPlayerTryingSkill(void);
void playPracticeCPUInputs(void);
void practiceStartGuidedMessage(int arg0, int arg1);
BOOL loadGuidedPractice(void);

#endif // !__GAME_PRACTICE_GUIDED_PRACTICE_H_
