#include "game/hud/outs_indicator.h"
#define SQRT2_LINKAGE static
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "text/text_channel.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x8003649c.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x80034cec.h"
extern u8 animRelated[0x124];
#define REP_HEADER_DATA_FN getRepHeaderData_outsIndicator
#include "header_rep_data.h"

extern UIRecordDescriptor lbl_3_data_D5B8[];

static const f32 lbl_3_rodata_1660 = 56.0f;

typedef struct OutIndicatorScene {
    u8 _00[0x14];
    u16 firstHandle;
    u16 handleCount;
    u16 frameCount;
    u8 _1A[2];
    u16 shownOuts;
} OutIndicatorScene;

#define OUT_RECORD(scene, i) (*(UIRecord**)((u8*)graphicsRelatedArray + (((scene)->firstHandle + (i)) << 3)))

// .text:0x000912B4 size:0x188 mapped:0x806D0348
void fn_3_912B4(void) {
    OutIndicatorScene* scene = (OutIndicatorScene*)currentDrawingItem;
    int outs;
    int i;
    int state;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_D5B8);
    scene->shownOuts = 9;
    OUT_RECORD(scene, 1)->frame = 0;
    OUT_RECORD(scene, 2)->frame = 1 << 16;

    outs = g_Strikes.outs;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        outs = g_Minigame.toyField_maxOuts - g_Minigame.toyField_outsRemaining;
    }
    for (i = 0; i < 2; i++) {
        state = 3;
        if (scene->shownOuts == outs) {
            continue;
        }
        if (outs >= i + 1) {
            state = 2;
        }
        setIndicatorSlotState((DrawingSceneStruct*)scene, i + 1, i + 1, 0x107, state);
    }
    scene->shownOuts = outs;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        OUT_RECORD(scene, 0)->pos.y = lbl_3_rodata_1660;
        OUT_RECORD(scene, 1)->pos.y = lbl_3_rodata_1660;
        OUT_RECORD(scene, 2)->pos.y = lbl_3_rodata_1660;
    }
    scene->frameCount = 0;
    currentDrawingItem->func = fn_3_911A8;
}

// .text:0x000911A8 size:0x10C
void fn_3_911A8(void) {
    DrawingSceneStruct *cur = currentDrawingItem;

    if (animRelated[0x96] != 0 || g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
        animRelated[0x97] = 0;
        removeGraphicsElementFromScene(cur);
        removeCurrentDrawingItem();
    } else {
        s32 total;
        s32 i;

        *(u16 *)((u8 *)cur + 0x18) += 1;
        total = g_Strikes.outs;
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
            total = g_Minigame.toyField_maxOuts - g_Minigame.toyField_outsRemaining;
        }
        for (i = 0; i < 2; i++) {
            s32 state = 3;

            if (*(u16 *)((u8 *)cur + 0x1C) != total) {
                if (total >= i + 1) {
                    state = 2;
                }
                setIndicatorSlotState(cur, i + 1, i + 1, 0x107, state);
            }
        }
        *(u16 *)((u8 *)cur + 0x1C) = total;
    }
}

// .text:0x000910F4 size:0xB4
void fn_3_910F4(DrawingSceneStruct *node) {
    s32 i;
    s32 total = g_Strikes.outs;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        total = g_Minigame.toyField_maxOuts - g_Minigame.toyField_outsRemaining;
    }
    for (i = 0; i < 2; i++) {
        s32 state = 3;

        if (*(u16 *)((u8 *)node + 0x1C) != total) {
            if (total >= i + 1) {
                state = 2;
            }
            setIndicatorSlotState(node, i + 1, i + 1, 0x107, state);
        }
    }
    *(u16 *)((u8 *)node + 0x1C) = total;
}
