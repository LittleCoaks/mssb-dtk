#define SQRT2_LINKAGE static
#include "game/hud/toyfield_score_update.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/hud/outs_indicator.h"
#include "game/hud/hud_scoreboard.h"
#include "Unknown/File_0x800b0a14.h"
#define REP_HEADER_DATA_FN getRepHeaderData_toyfieldScoreUpdate
#include "header_rep_data.h"

extern u8 animRelated[0x124];
extern void toyfield_offScreenCharacterImage_loadFn(void);

// .text:0x0009143C size:0xE4 mapped:0x806D04D0
void hud_ScoreUpdate_ToyFieldOffScreenPlayers(void) {
    if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL && animRelated[0x97] == 0) {
        animRelated[0x97] = 1;
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD) {
            insertGraphicDrawingFunction(fn_3_912B4, 2);
        }
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
            insertGraphicDrawingFunction(toyfield_offScreenCharacterImage_loadFn, 2);
        }
    }
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE && animRelated[0x99] != 0) {
        if (animRelated[0x98] == 0) {
            insertGraphicDrawingFunction(graphics_ShowScoreUpdateOnRBI_initial, 2);
        } else {
            animRelated[0x98] = 2;
        }
    }
}
