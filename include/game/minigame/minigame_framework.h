#ifndef __GAME_MINIGAME_MINIGAME_FRAMEWORK_H_
#define __GAME_MINIGAME_MINIGAME_FRAMEWORK_H_

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

void minigameSimulation(void);
void minigames_init(void);
void minigames_0x1B(void);
void minigames_0x25(void);
void minigames_setupChallengeRoster(void);
void minigames_startStadiumLoad(void);
BOOL minigames_isStadiumLoading(void);
void minigameQueueHudEvent(u8 arg0, s16 arg1);
void toyFieldStadiumLoad(void);
void minigameSelectSwitcher(void);
void minigameSelectMenuUpdate(void);
void toyFieldCharSelectSwitcher(void);
void minigameCharSelectUpdate(void);
void minigameCharLoadQueueUpdate(void);
void minigameCharSelectReset(void);
void minigames_fillRoster(void);
void minigames_loadCharStats(int slot, int charID);
void minigames_pickOpponentsAndLoadStats(void);
void minigameReadySwitcher(void);
void minigameHelpMenuUpdate(void);
void minigameBackToCharSelect(void);
void minigameStartSwitcher(void);
void minigames_0x23(void);
void minigames_shufflePlayOrder(void);
void minigameEndSwitcher(void);
void minigameEndHook(void);
void minigameBuildResultEntry(MinigameResultEntry* out);
MinigameResultEntry* minigameGetScoreTable(void);
int minigameGetScoreRank(MinigameResultEntry* entry);
void minigameUpdateHighScores(void);
void minigameResultsSwitcher(void);
void postMinigame(void);
void postMinigameMenuUpdate(void);
BOOL checkForPauses(void);
void minigamePause(void);
void minigamePauseMenuUpdate(void);
void minigamePauseHelpUpdate(void);
u32 minigame_checkIfAIInputIs_Algorithmic_Or_ControllerBased(s8);
u32 minigame_getCcsAIControlledInd(s8 player);
u32 AI_getPort(s8);
u32 minigame_getAIDrivenInputInd(s8 player);
int minigame_compareDisplayedPoints(const void* a, const void* b);
int minigame_getLeadingPlayer(void);
BOOL minigame_displayedPointsAllTied(void);
BOOL minigame_pointsAllTied(void);
int minigame_comparePoints(const void* a, const void* b);
int minigame_compareGrandPrixTotals(const void* a, const void* b);
int minigame_compareGrandPrixPrevTotals(const void* a, const void* b);
void minigame_rankPlayers(u8 (*order)[2], int mode);
BOOL minigame_grandPrixHasPlayed(u32 mode);
void minigameStartGrandPrix(void);
void minigames_0x28(void);
void minigameGrandPrixNextRound(void);
void minigameFillGrandPrixScoreInput(MiniGrandPrixScoreInput* input);
void minigames_0x26(void);
void minigames_0x27(void);
void minigameGrandPrixCheckWin(void);
void minigameAwardCoins(void);
void fn_3_106EB0(void);

#endif // !__GAME_MINIGAME_MINIGAME_FRAMEWORK_H_
