#ifndef __GAME_BATTING_BATTER_AI_H_
#define __GAME_BATTING_BATTER_AI_H_

#include "mssbTypes.h"

extern const f32 lbl_3_rodata_918;
extern const f32 lbl_3_rodata_930;
extern const f32 lbl_3_rodata_934;
extern u8 batterAIConstants[8];
extern u8 lbl_3_data_1944[3][4][6];
extern u8 lbl_3_data_198C[4][5][2];
extern u8 lbl_3_data_19B4[4][4];
extern u8 lbl_3_data_1A14[4][3];
extern u8 lbl_3_data_1A20[4];
extern u8 lbl_3_data_1C08[2][2];
extern u8 lbl_3_data_1C0C[2];
extern u8 lbl_3_data_1C10[8][4];
extern u8 lbl_3_data_1AAC[4];
extern u8 lbl_3_data_1AB0[4][3];
extern u8 lbl_3_data_1ABC[2][4][4];
extern f32 lbl_3_data_19CC[4];
extern f32 lbl_3_data_4474[4];
extern f32 lbl_3_data_19DC[5][2];
extern f32 lbl_3_data_1A04[2];
extern f32 lbl_3_data_1A0C[2];
extern u8 lbl_3_data_1A24[4];
extern u8 lbl_3_data_1A28[4][5];
extern u8 lbl_3_data_1A3C[4];
extern u8 lbl_3_data_1ADC[4][4];
extern u8 lbl_3_data_1AEC[6][4][4];
extern u8 lbl_3_data_1B4C[2];
extern u8 batterAIPerfectStealProb[8];
extern s16 lbl_3_data_4B90[4];
extern u8 lbl_3_data_1C98[2][5][3][4];
extern f32 batterAIBatterClassMultOnStealing[6];
extern u8 lbl_3_data_1B50[4][2][9];
extern u8 lbl_3_data_1B98[4][4];
extern u8 lbl_3_data_1BA8[4];
extern s8 lbl_3_data_1BAC[2][4][2];
extern s8 lbl_3_data_1BBC[4][2];
extern s8 lbl_3_data_1BC4[4][2];
extern s8 lbl_3_data_1BCC[4][2];
extern u8 lbl_3_data_1BD4[4];
extern u8 lbl_3_data_1BD8[4][3];
extern u8 lbl_3_data_1BE4[4][3];
extern u8 lbl_3_data_1BF0[2][4][3];
extern int fn_3_E587C(void);
extern u8 lbl_3_data_19C4[8];
extern int batterAI_buntForPractice(void);
extern void fieldingPracticeAISwingDecision(void);
extern u8 lbl_3_data_1A40[6][4];
extern u8 lbl_3_data_1A58[3][4][4];
extern f32 lbl_3_data_1A88[4][2];
extern f32 lbl_3_data_1AA8;
extern f32 lbl_3_data_5EB8[3];

void fn_3_1E4B8(void);
BOOL fn_3_1E724(void);
BOOL batterAIBallLocRelated(void);
void batterAIFrameToSwingAndStickInput(void);
BOOL batterAISwingInd(void);
void fn_3_1F1CC(void);
void fn_3_1F350(void);
void batterTrackBallInBox(void);
void batterAIMoveBatter(void);
void batterAIControlled(void);
void trackLastPitchInfo2(void);
void batterAISwingEarlyOrLate(void);
void fn_3_20188(void);
void batterAIRNGValueSetting(void);

#endif // !__GAME_BATTING_BATTER_AI_H_
