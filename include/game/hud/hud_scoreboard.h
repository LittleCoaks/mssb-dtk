#ifndef __GAME_HUD_HUD_SCOREBOARD_H_
#define __GAME_HUD_HUD_SCOREBOARD_H_

#include "mssbTypes.h"

void ballLandingMarker_update(void);
void ballLandingMarker_init(void);
void fn_3_91AC8(void);
void fn_3_91B50(void);
void animateScreenRelated(void);
void fn_3_91C70(void);
void fn_3_91CCC(void);
void fn_3_91D1C(void);
void fn_3_91E4C(void);
void manageScoreboardGraphic(void);
struct HudDigitScene;
void scoreTicker_update(struct HudDigitScene* scene);
void homeRunScoreTicker_update(void);
void homeRunScoreTicker_init(void);
struct HudScene;
void updateRBIScoreDigits(struct HudScene* scene);
void graphics_ShowScoreUpdateOnRBI_ongoing(void);
void graphics_ShowScoreUpdateOnRBI_initial(void);
void fn_3_9413C(void);
void relatedToAnimatingEndOfGame(void);
void fn_3_94708(void);
void fn_3_94760(void);
void fn_3_948B8(void);
void fn_3_94930(void);
void scoutMissionProgress_update(void);
void scoutMissionProgress_init(void);
void fn_3_94E68(void);
void scoutMissionBanner_init(void);
void fn_3_95098(void);
void fn_3_95124(void);
void fn_3_951B4(void);
void fn_3_952DC(void);
void fn_3_9538C(void);
void fn_3_953FC(void);
void fn_3_954C4(void);
void fn_3_9551C(void);
void HUD_ongoingStarChance(void);
void HUD_initStarChance(void);
void offscreenFielderIndicator_update(void);
void offscreenFielderIndicator_init(void);
void drawDiamondMiniMap_ongoing(void);
void drawDiamondMiniMap_init(void);
void toyfield_hud_turns_diamondMap(void);
void inGameEventBanner_update(void);
void handleInGameEventsAndSoundEffects(void);

#endif // !__GAME_HUD_HUD_SCOREBOARD_H_
