#ifndef __GAME_MINIGAME_MINIGAME_HUD_H_
#define __GAME_MINIGAME_MINIGAME_HUD_H_

#include "mssbTypes.h"

/* Drawing-script node scratch shared by the minigame HUD scenes. */
typedef struct MinigameHudScene {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ u16 firstHandle;
    /*0x16*/ u16 handleCount;
    /*0x18*/ u16 _18;
    /*0x1A*/ u16 _1A;
    /*0x1C*/ u16 state;
    /*0x1E*/ u16 _1E;
    /*0x20*/ u16 _20;
    /*0x22*/ u16 _22;
    /*0x24*/ union {
        u8 scratch[0x1C];
        s16 popupPoints[4];
        s16 shownValues[8];
        u32 sndHandle;
    };
} MinigameHudScene;

void minigameHudCcsTargetMarkers(void);
void minigameHudCcsScoreboard(void);
void minigameHudCcsSyncDisplayedPoints(void);
void minigameHudCcsAddGemPoints(int player, int bonus);
void minigameHudBarrelBatterBombBarrel(void);
void minigameHudBarrelBatterBarrelsHit(void);
void minigameHudBarrelBatterPoints(void);
void minigameHudBarrelBatterChargeMeter(void);
void minigameHudWallBallBowserPenalty(void);
void minigameHudWallBallPointsPopup(void);
int minigameHudWallBallHitPoints(void);
void minigameHudWallBallTurnsRemaining(void);
void minigameHudWallBallScoreboard(void);
void minigameHudBodPitchRoulette(void);
void minigameHudBodDistance(void);
void minigameHudBodHomeRunPoints(void);
void minigameHudBodStreakBonus(void);
void minigameHudBodKingBombBonus(void);
void minigameHudBodStreak(void);
void minigameHudPlayerMarkers(void);
void minigameHudTimer(void);
void minigameStateLogic(void);
void minigameHudPitchesRemaining(void);
void minigameHudTargetPoints(void);
u32 minigameHudShouldRemove(void);
u32 minigameHudSeekRecordFrame(MinigameHudScene* scene, int handle, u32 targetFrame);
u32 minigameHudAnyRecordPlaying(MinigameHudScene* scene);
void minigameHudStartMovie(void);
void minigameHudEventBannerUpdate(void);
void minigameHudEventBannerInit(void);
void minigameHudHelpUpdate(void);
void minigameHudHelpInit(void);
void minigameHudHighScoreTable(void);
void minigameHudResultsScene(void);
void minigameHudPauseHelpBannerUpdate(void);
void minigameHudPauseHelpBannerInit(void);
void minigameHudResultBannerUpdate(void);
void minigameHudResultBannerInit(void);
void minigameHudGraphics0x27(void);
void minigameHudEndGameGraphics(void);
void minigameHudSelectMenuUpdate(void);
void minigameHudSelectMenuInit(void);
void minigameHudChallengeDifficultyUpdate(void);
void minigameHudChallengeDifficultyInit(void);
void minigameHudDifficultyUpdate(void);
void minigameHudDifficultyInit(void);
void minigameHudExtraOpponentUpdate(void);
void minigameHudExtraOpponentInit(void);
void minigameHudCharSelectUpdate(void);
void minigameHudCharSelectInit(void);
void minigameHudSelectInfoUpdate(void);
void minigameHudSelectInfoInit(void);
void minigameHudBannerUpdate(void);
void minigameHudBannerInit(void);
void minigameHudSpawnPiranhaPanic(void);
void minigameHudSpawnStarDash(void);
void minigameHudSpawnChainChompSprint(void);
void minigameHudSpawnBarrelBatter(void);
void minigameHudSpawnWallBall(void);
void minigameHudSpawnBobombDerby(void);
void minigameHudMenuGraphics(void);
void minigameGraphics(void);

#endif // !__GAME_MINIGAME_MINIGAME_HUD_H_
