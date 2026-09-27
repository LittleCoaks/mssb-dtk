#include "game/hud/hud_gauges.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "text/text_channel.h"
#include "Unknown/File_0x80034cec.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x8003649c.h"
#include "static/UnknownHomes_Static.h"

extern u8 animRelated[0x124];
extern u8 pauseControl[0x264];
extern UIRecordDescriptor lbl_3_data_D378[];
extern UIRecordDescriptor lbl_3_data_D258[];
extern UIRecordDescriptor lbl_3_data_D4F8[];
extern UIRecordDescriptor lbl_3_data_C22C[];
extern s16 lbl_3_data_5F3C[];

extern void fn_3_972A0(DrawingSceneStruct* node, int slot, int handle, int digit);

// The scene node's view of its record span in graphicsRelatedArray, and the
// gauge-animation state the node's own func keeps between frames.
typedef struct HudGaugeScene {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ u16 firstHandle;
    /*0x16*/ u16 handleCount;
    /*0x18*/ u8 _18[0x4];
    /*0x1C*/ u16 unk1C;
} HudGaugeScene;

#define HUD_RECORD(scene, i) ((UIRecord*)graphicsRelatedArray[(scene)->firstHandle + (i)].object)

// The ball/strike/out indicator node's scratch layout: unlike HudGaugeScene,
// it tracks the last-drawn count/frame state so it only pokes the indicator
// records when something actually changed.
typedef struct BallStrikeOutScene {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ u16 firstHandle;
    /*0x16*/ u16 handleCount;
    /*0x18*/ u16 frameCount;
    /*0x1A*/ u8 _1A[0x2];
    /*0x1C*/ u16 shownStrikes;
    /*0x1E*/ u16 shownBalls;
    /*0x20*/ u16 shownOuts;
    /*0x22*/ u16 unk22;
} BallStrikeOutScene;

// .text:0x000993A8 size:0x3C4 mapped:0x806D843C
void fn_3_993A8(void) {
    HudGaugeScene* scene = (HudGaugeScene*)currentDrawingItem;
    UIRecord* rec;
    int frame = 0;

    if (animRelated[0x96] == 0 && animRelated[0xA7] != 0) {
        if (g_Batter.chargeStatus != CHARGE_SWING_STAGE_NONE) {
            if (g_Batter.chargeUp < 1.0f) {
                HUD_RECORD(scene, 2)->elementIndex = 0x49;
                frame = 75.0f * g_Batter.chargeUp;
            } else {
                HUD_RECORD(scene, 2)->elementIndex = 0x48;
                frame = (int)(31.0f * g_Batter.chargeDown) + 75;
            }
            if (g_Batter.chargeDown >= 1.0f) {
                HUD_RECORD(scene, 3)->frame = 106 << 16;
                rec = HUD_RECORD(scene, 2);
                if ((rec->frame >> 16) < 106) {
                    rec->frame = 106 << 16;
                } else {
                    rec->playMode = UI_PLAY_FORWARD;
                }
                frame = 106;
            } else {
                HUD_RECORD(scene, 3)->frame = frame << 16;
                HUD_RECORD(scene, 2)->frame = 0;
                HUD_RECORD(scene, 2)->playMode = UI_PLAY_STOP;
            }
        } else {
            HUD_RECORD(scene, 3)->frame = 0;
            HUD_RECORD(scene, 3)->playMode = UI_PLAY_STOP;
            HUD_RECORD(scene, 2)->frame = 0;
        }

        if (g_Batter.chargeStatus != CHARGE_SWING_STAGE_NONE) {
            HUD_RECORD(scene, 5)->playMode = UI_PLAY_STOP;
            if (g_Batter.swingInd != 0 && g_Batter.chargeDown >= 1.0f) {
                rec = HUD_RECORD(scene, 5);
                if ((rec->frame >> 16) < 106) {
                    rec->frame = 106 << 16;
                } else {
                    rec->playMode = UI_PLAY_FORWARD;
                }
            } else {
                HUD_RECORD(scene, 5)->frame = (frame + 10) << 16;
            }
        } else {
            if ((HUD_RECORD(scene, 5)->frame >> 16) < 10) {
                HUD_RECORD(scene, 5)->playMode = UI_PLAY_FORWARD;
            } else {
                HUD_RECORD(scene, 5)->frame = 10 << 16;
                HUD_RECORD(scene, 5)->playMode = UI_PLAY_STOP;
            }
        }

        if (g_Batter.chargeStatus != CHARGE_SWING_STAGE_NONE && g_Batter.swingInd != 0) {
            if (scene->unk1C == 0) {
                HUD_RECORD(scene, 6)->flags |= UI_FLAG_VISIBLE;
                HUD_RECORD(scene, 6)->frame = frame << 16;
                HUD_RECORD(scene, 7)->frame = 0;
                HUD_RECORD(scene, 7)->playMode = UI_PLAY_FORWARD;
                scene->unk1C = 1;
            }
        } else {
            HUD_RECORD(scene, 6)->flags &= ~UI_FLAG_VISIBLE;
            scene->unk1C = 0;
        }
    } else {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    }
}

// .text:0x0009976C size:0xAC mapped:0x806D8800
void fn_3_9976C(void) {
    DrawingSceneStruct* node = currentDrawingItem;

    addGraphicsElementToScene(node, lbl_3_data_D378);
    if (g_Batter.batterHand != BATTING_HAND_RIGHT) {
        HUD_RECORD((HudGaugeScene*)node, 0)->frame = 0;
    } else {
        HUD_RECORD((HudGaugeScene*)node, 0)->frame = 1 << 16;
    }
    ((HudGaugeScene*)node)->unk1C = 0;
    currentDrawingItem->func = fn_3_993A8;
}

// .text:0x00099818 size:0x3C4 mapped:0x806D88AC
void wallBallAnimationRelated(void) {
    HudGaugeScene* scene = (HudGaugeScene*)currentDrawingItem;
    UIRecord* rec;
    int frame = 0;
    f32 ratio;

    if (animRelated[0x96] != 0) {
        goto remove;
    }
    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_WALLBALL) {
        if (g_GameLogic.gameStatus == GAME_STATUS_TRANSITION_MINIGAME_POSTGAME) {
            goto remove;
        }
        if (g_Minigame.pauseInd != 0 && (pauseControl[0x1d2] == 7 || pauseControl[0x1d2] == 0xd)) {
            goto remove;
        }
    } else if (animRelated[0xA7] == 0) {
        goto remove;
    }

    if (g_Pitcher.ChargePitchType != 0) {
        ratio = (f32)g_Pitcher.unknownFrameCounter / (f32)(g_Pitcher.pitchWindUpCountDown - lbl_3_data_5F3C[2]);
        if (ratio >= 1.0f) {
            ratio = 1.0f;
        }
        HUD_RECORD(scene, 3)->playMode = UI_PLAY_STOP;
        frame = 106.0f * ratio;
        if (g_Pitcher.ChargePitchType == 3) {
            HUD_RECORD(scene, 3)->frame = 106 << 16;
            rec = HUD_RECORD(scene, 2);
            if ((int)(rec->frame >> 16) < 106) {
                rec->frame = 106 << 16;
            } else {
                rec->playMode = UI_PLAY_FORWARD;
            }
            frame = 106;
        } else if (g_Pitcher.overChargeInd != 0) {
            frame = 106.0f * g_Pitcher.pitchChargeUp;
            HUD_RECORD(scene, 3)->frame = frame << 16;
        } else {
            HUD_RECORD(scene, 3)->frame = frame << 16;
        }
    } else {
        HUD_RECORD(scene, 3)->frame = 0;
        HUD_RECORD(scene, 3)->playMode = UI_PLAY_STOP;
        HUD_RECORD(scene, 2)->frame = 0;
    }

    if (g_Pitcher.ChargePitchType != 0) {
        HUD_RECORD(scene, 5)->playMode = UI_PLAY_STOP;
        if (g_Pitcher.ChargePitchType == 3) {
            HUD_RECORD(scene, 5)->playMode = UI_PLAY_FORWARD;
        } else {
            HUD_RECORD(scene, 5)->frame = (frame + 10) << 16;
        }
    } else {
        if ((HUD_RECORD(scene, 5)->frame >> 16) < 10) {
            HUD_RECORD(scene, 5)->playMode = UI_PLAY_FORWARD;
        } else {
            HUD_RECORD(scene, 5)->frame = 10 << 16;
            HUD_RECORD(scene, 5)->playMode = UI_PLAY_STOP;
        }
    }

    if (g_Pitcher.ChargePitchType >= 2) {
        if (scene->unk1C == 0) {
            HUD_RECORD(scene, 6)->flags |= UI_FLAG_VISIBLE;
            HUD_RECORD(scene, 6)->frame = frame << 16;
            HUD_RECORD(scene, 7)->frame = 0;
            HUD_RECORD(scene, 7)->playMode = UI_PLAY_FORWARD;
            scene->unk1C = 1;
        }
    } else {
        HUD_RECORD(scene, 6)->flags &= ~UI_FLAG_VISIBLE;
        scene->unk1C = 0;
    }
    return;

remove:
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
}

// .text:0x00099BDC size:0xAC mapped:0x806D8C70
void fn_3_99BDC(void) {
    DrawingSceneStruct* node = currentDrawingItem;

    addGraphicsElementToScene(node, lbl_3_data_D258);
    if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_WALLBALL) {
        HUD_RECORD((HudGaugeScene*)node, 0)->frame = 3 << 16;
    } else {
        HUD_RECORD((HudGaugeScene*)node, 0)->frame = 2 << 16;
    }
    ((HudGaugeScene*)node)->unk1C = 0;
    currentDrawingItem->func = wallBallAnimationRelated;
}

// .text:0x00099C88 size:0x74 mapped:0x806D8D1C
void fn_3_99C88(void) {
    HudGaugeScene* scene = (HudGaugeScene*)currentDrawingItem;

    if (animRelated[0x96] == 0 && animRelated[0xA7] != 0) {
        HUD_RECORD(scene, 0)->rgba = (HUD_RECORD(scene, 0)->rgba & ~0xFF) | animRelated[0xA7];
    } else {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    }
}

// .text:0x00099CFC size:0x114 mapped:0x806D8D90
void draw_OnBaseChemLinks(void) {
    DrawingSceneStruct* node = currentDrawingItem;

    addGraphicsElementToScene(node, lbl_3_data_D4F8);
    if (!(g_Batter.runnersOnBase & 1)) {
        HUD_RECORD((HudGaugeScene*)node, 3)->flags &= ~UI_FLAG_VISIBLE;
    }
    if (!(g_Batter.runnersOnBase & 2)) {
        HUD_RECORD((HudGaugeScene*)node, 2)->flags &= ~UI_FLAG_VISIBLE;
    }
    if (!(g_Batter.runnersOnBase & 4)) {
        HUD_RECORD((HudGaugeScene*)node, 1)->flags &= ~UI_FLAG_VISIBLE;
    }
    if (g_Pitcher.nPitchesThisAB == 0 && g_Pitcher.nPickoffAttempts == 0) {
        playSoundEffect(0x1ab);
    }
    currentDrawingItem->func = fn_3_99C88;
}

// .text:0x00099E10 size:0xA94 mapped:0x806D8EA4
void draw_ongoingStarGuageHud(void) {
    return;
}

// .text:0x0009A8A4 size:0x864 mapped:0x806D9938
void draw_initStarGuageHud(void) {
    return;
}

// .text:0x0009B108 size:0x218 mapped:0x806DA19C
void fn_3_9B108(DrawingSceneStruct* node) {
    if (g_Scores.scores[0].total >= 10) {
        fn_3_972A0(node, 11, 4, g_Scores.scores[0].total % 10);
        fn_3_972A0(node, 12, 3, g_Scores.scores[0].total / 10);
        fn_3_972A0(node, 11, 10, g_Scores.scores[0].total % 10);
        fn_3_972A0(node, 12, 9, g_Scores.scores[0].total / 10);
    } else {
        fn_3_972A0(node, 10, 1, g_Scores.scores[0].total);
        fn_3_972A0(node, 10, 7, g_Scores.scores[0].total);
    }

    if (g_Scores.scores[1].total >= 10) {
        fn_3_972A0(node, 14, 6, g_Scores.scores[1].total % 10);
        fn_3_972A0(node, 15, 5, g_Scores.scores[1].total / 10);
        fn_3_972A0(node, 14, 12, g_Scores.scores[1].total % 10);
        fn_3_972A0(node, 15, 11, g_Scores.scores[1].total / 10);
    } else {
        fn_3_972A0(node, 13, 2, g_Scores.scores[1].total);
        fn_3_972A0(node, 13, 8, g_Scores.scores[1].total);
    }
}

// .text:0x0009B320 size:0x4D4 mapped:0x806DA3B4
void fn_3_9B320(void) {
    return;
}

// .text:0x0009B7F4 size:0x6EC mapped:0x806DA888
void draw_ScoreInningHud(void) {
    return;
}

// .text:0x0009BEE0 size:0x134 mapped:0x806DAF74
void maybe_updateBallStrikeOutUI(DrawingSceneStruct* node) {
    int outs;
    BallStrikeOutScene* scene = (BallStrikeOutScene*)node;
    int i;
    int state;

    outs = g_Strikes.outs;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        outs = g_Minigame._190D - g_Minigame._1910;
    }

    for (i = 0; i < 7; i++) {
        state = 3;
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && i >= 5) {
            break;
        }
        if (i < 2) {
            if (scene->shownStrikes == g_Strikes.strikes) {
                continue;
            }
            if (g_Strikes.strikes >= i + 1) {
                state = 0;
            }
        } else if (i < 5) {
            if (scene->shownBalls == g_Strikes.balls) {
                continue;
            }
            if (g_Strikes.balls >= i - 1) {
                state = 1;
            }
        } else {
            if (scene->shownOuts == outs) {
                continue;
            }
            if (outs >= i - 4) {
                state = 2;
            }
        }
        setIndicatorSlotState((DrawingSceneStruct*)scene, i + 1, i + 1, 0x107, state);
    }

    scene->shownStrikes = g_Strikes.strikes;
    scene->shownBalls = g_Strikes.balls;
    scene->shownOuts = outs;
}

// .text:0x0009C014 size:0x278 mapped:0x806DB0A8
void update_BallStrikeOutHud(void) {
    BallStrikeOutScene* scene = (BallStrikeOutScene*)currentDrawingItem;
    int i;

    if (animRelated[0x96] != 0 || animRelated[0xA7] == 0) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }

    scene->frameCount++;
    maybe_updateBallStrikeOutUI((DrawingSceneStruct*)scene);

    if (animRelated[0xA7] < 0xFF) {
        for (i = 0; i < 8; i++) {
            HUD_RECORD(scene, i)->rgba = (HUD_RECORD(scene, i)->rgba & ~0xFF) | animRelated[0xA7];
        }
    } else {
        for (i = 1; i < 8; i++) {
            HUD_RECORD(scene, i)->rgba = (HUD_RECORD(scene, i)->rgba & ~0xFF) | animRelated[0xA6];
        }
    }
}

// .text:0x0009C28C size:0x2EC mapped:0x806DB320
void init_BallStrikeOutHud(void) {
    BallStrikeOutScene* scene = (BallStrikeOutScene*)currentDrawingItem;
    int i;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_C22C);
    scene->unk22 = 0;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        scene->unk22 = 1;
        for (i = 0; i < 8; i++) {
            HUD_RECORD(scene, i)->pos.y = -30.0f;
        }
    } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        if (g_Practice.practiceLevel != 7 && g_Practice.practiceLevel != 6) {
            scene->unk22 = 1;
        }
    }

    if (scene->unk22 != 0) {
        for (i = 1; i < 6; i++) {
            HUD_RECORD(scene, i)->elementIndex = 0x104;
        }
        HUD_RECORD(scene, 0)->elementIndex = 0x103;
        HUD_RECORD(scene, 6)->flags &= ~UI_FLAG_VISIBLE;
        HUD_RECORD(scene, 7)->flags &= ~UI_FLAG_VISIBLE;
    }

    scene->shownOuts = 9;
    scene->shownBalls = 9;
    scene->shownStrikes = 9;

    for (i = 1; i < 8; i++) {
        HUD_RECORD(scene, i)->frame = (i - 1) << 16;
    }

    maybe_updateBallStrikeOutUI((DrawingSceneStruct*)scene);
    scene->frameCount = 0;
    currentDrawingItem->func = update_BallStrikeOutHud;
}

