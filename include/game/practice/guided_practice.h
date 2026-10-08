#ifndef __GAME_PRACTICE_GUIDED_PRACTICE_H_
#define __GAME_PRACTICE_GUIDED_PRACTICE_H_

#include "mssbTypes.h"

extern s16 lbl_3_data_FB04[];
extern u8 guidedPracticeThresholds[][4];
extern s16 hitVarsForFieldingPractice[][3];
extern s16 lbl_3_data_FB44[][3];
extern s16 lbl_3_data_FB80[][3];
extern s16 lbl_3_data_FBBC[][3];
extern s16 lbl_3_data_FBF8[];
extern void* practice_instructions_pitchingPtrs[4];
extern void* practice_instructions_battingPtrs[4];
extern void* practice_instructions_freePracticePtrs[4];

void practiceRelatedInit(void);
void fn_3_B274C(void);
void fn_3_B3A28(void);
void practiceLogicRelatedPause(void);
void practiceMenuLogic(void);
BOOL practice_checkForPause(void);
void fn_3_B3288(void);
void practicePauseRelated(void);
void fn_3_B2AA0(void);
void practice_pause_unloadPauseMenu(void);
void practice_giveAndDemonstrateInstructions(void);
int setUpPlayerTryingSkill(void);
void playPracticeCPUInputs(void);
void fn_3_B1DA4(int arg0, int arg1);
BOOL loadGuidedPractice(void);

#endif // !__GAME_PRACTICE_GUIDED_PRACTICE_H_
