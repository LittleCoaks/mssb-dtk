#ifndef __GAME_DATA_ONLY_REP_31A0_H_
#define __GAME_DATA_ONLY_REP_31A0_H_

#include "mssbTypes.h"

typedef struct _MinigameResultsScene {
    u8 _00[0x18];
    u16 _18;
    u16 _1A;
} MinigameResultsScene;

typedef struct {
    s32 score;
    s16 count;
    s16 charID;
} MinigameResultEntry;

typedef struct {
    s16 vals[6];
    u8 bytes[6];
    u8 placeRank;
    u8 extra;
    u8 charID;
} MiniGrandPrixScoreInput;

void unusedBattingSomething(void);
void fn_3_1104A8(void);
void minigameSimulation(void);
void fn_3_10FBE4(void);
void fn_3_10FB74(void);
void fn_3_10F91C(void);
void fn_3_10F684(void);
void fn_3_10F5BC(void);
BOOL fn_3_10F564(void);
void fn_3_10F550(u8 arg0, s16 arg1);
void toyFieldStadiumLoad(void);
void minigameSelectSwitcher(void);
void fn_3_10EFAC(void);
void toyFieldCharSelectSwitcher(void);
void fn_3_10CC20(void);
void fn_3_10C81C(void);
void fn_3_10C7A4(void);
void fn_3_10C58C(void);
void fn_3_10C450(int slot, int charID);
void minigames_pickOpponentsAndLoadStats(void);
void fn_3_10B8D0(void);
void fn_3_10B27C(void);
void fn_3_10B200(void);
void minigameStartSwitcher(void);
void fn_3_10AE18(void);
void fn_3_10AD48(void);
void minigameEndSwitcher(void);
void fn_3_10A01C(void);
void fn_3_109DE0(MinigameResultEntry* out);
MinigameResultEntry* fn_3_109D88(void);
int fn_3_109CE8(MinigameResultEntry* entry);
void fn_3_10952C(void);
void fn_3_109254(void);
void postMinigame(void);
void fn_3_1089E8(void);
BOOL checkForPauses(void);
void minigamePause(void);
void fn_3_108230(void);
void fn_3_107E80(void);
u32 minigame_checkIfAIInputIs_Algorithmic_Or_ControllerBased(s8);
u32 fn_3_107DF8(s8 player);
u32 AI_getPort(s8);
u32 fn_3_107D70(s8 player);
int fn_3_107D34(const void* a, const void* b);
int fn_3_107CD0(void);
BOOL fn_3_107C88(void);
BOOL fn_3_107C40(void);
int fn_3_107C04(const void* a, const void* b);
int fn_3_107BD0(const void* a, const void* b);
int fn_3_107B9C(const void* a, const void* b);
void fn_3_1079C8(u8 (*order)[2], int mode);
BOOL fn_3_107988(u32 mode);
void fn_3_1078F8(void);
void minigames_0x28(void);
void fn_3_10768C(void);
void fn_3_10754C(MiniGrandPrixScoreInput* input);
void minigames_0x26(void);
void minigames_0x27(void);
void fn_3_107078(void);
void fn_3_106ED4(void);
void fn_3_106EB0(void);
BOOL loadSomeDataFile(void);
void someAllocFunction(void);

#endif // !__GAME_DATA_ONLY_REP_31A0_H_
