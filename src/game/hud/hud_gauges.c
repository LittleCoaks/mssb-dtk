#include "game/hud/hud_gauges.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "text/text_channel.h"
#include "Unknown/File_0x80034cec.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x8003649c.h"
#include "Unknown/File_0x800363d8.h"
#include "static/UnknownHomes_Static.h"
#include "game/match_setup/pause_menu.h"

extern u8 animRelated[0x124];
extern UIRecordDescriptor lbl_3_data_D378[];
extern UIRecordDescriptor lbl_3_data_D258[];
extern UIRecordDescriptor lbl_3_data_D4F8[];
extern UIRecordDescriptor lbl_3_data_C22C[];
extern UIRecordDescriptor lbl_3_data_C34C[];
extern UIRecordDescriptor lbl_3_data_C56C[2][0x33];
extern u8 lbl_3_data_F430[][2];
u8 lbl_3_data_F4A4[0x2C] = {
    0x00, 0x00, 0x00, 0x00, 0x02, 0x05, 0x04, 0x03,
    0x08, 0x03, 0x04, 0x05, 0x02, 0x06, 0x00, 0x01,
    0x08, 0x06, 0x07, 0x01, 0x02, 0x00, 0x07, 0x04,
    0x04, 0x03, 0x01, 0x02, 0x05, 0x01, 0x02, 0x04,
    0x06, 0x08, 0x07, 0x06, 0x08, 0x05, 0x03, 0x03,
    0x05, 0x07, 0x04, 0x06,
};

u8 lbl_3_data_F4D0[0x10] = {
    0x00, 0x01, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00,
};

extern s16 lbl_3_data_5F3C[];
extern u16 lbl_3_data_D22C[];
extern u16 starGuageIconIDs[];
extern u8 lbl_3_data_D250[];

extern const f32 lbl_3_rodata_17C0;
extern const f32 lbl_3_rodata_17C4;
extern const f32 lbl_3_rodata_17C8;
extern const f32 lbl_3_rodata_17CC;
extern const f32 lbl_3_rodata_17D8;

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

// The score/inning node's scratch layout: the last-drawn team scores, so the
// digit records are only redrawn when a score changes.
typedef struct ScoreHudScene {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ u16 firstHandle;
    /*0x16*/ u16 handleCount;
    /*0x18*/ u16 frameCount;
    /*0x1A*/ u8 _1A[0x2];
    /*0x1C*/ u16 shownScores[2];
} ScoreHudScene;

// The star gauge node's scratch layout: the last-drawn team star counts.
typedef struct StarGaugeScene {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ u16 firstHandle;
    /*0x16*/ u16 handleCount;
    /*0x18*/ u16 frameCount;
    /*0x1A*/ u8 _1A[0x2];
    /*0x1C*/ u16 shownTeamStars[2];
    /*0x20*/ u16 unk20;
} StarGaugeScene;

// .text:0x000993A8 size:0x3C4 mapped:0x806D843C
void fn_3_993A8(void) {
    HudGaugeScene* scene = (HudGaugeScene*)currentDrawingItem;
    UIRecord* rec;
    int frame = 0;

    if (animRelated[0x96] == 0 && animRelated[0xA7] != 0) {
        if (g_Batter.chargeStatus != CHARGE_SWING_STAGE_NONE) {
            if (g_Batter.chargeUp < lbl_3_rodata_17C0) {
                HUD_RECORD(scene, 2)->elementIndex = 0x49;
                frame = lbl_3_rodata_17C4 * g_Batter.chargeUp;
            } else {
                HUD_RECORD(scene, 2)->elementIndex = 0x48;
                frame = (int)(lbl_3_rodata_17C8 * g_Batter.chargeDown) + 75;
            }
            if (g_Batter.chargeDown >= lbl_3_rodata_17C0) {
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
            if (g_Batter.swingInd != 0 && g_Batter.chargeDown >= lbl_3_rodata_17C0) {
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
        if (g_Minigame.pauseInd != 0 && (pauseControl.state == 7 || pauseControl.state == 0xd)) {
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
        frame = lbl_3_rodata_17CC * ratio;
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
            frame = lbl_3_rodata_17CC * g_Pitcher.pitchChargeUp;
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
    StarGaugeScene* scene = (StarGaugeScene*)currentDrawingItem;
    int gainTeam = -1;
    int loseTeam = -1;
    int newStars = -1;
    int team;
    int j;
    int slot;
    int stars;
    int frame;
    int bannerFrame;
    s32 i;

    scene->frameCount++;
    if (animRelated[0x96] != 0 || g_GameLogic.hudLoadingRelated != 0 ||
        g_GameLogic.gameStatus == GAME_STATUS_INNING_TRANSITION || g_GameLogic.gameStatus == GAME_STATUS_MVP_END_GAME ||
        g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_MENU) {
        goto remove;
    }

    if (g_GameLogic.IsStarChance == 0 || pauseControl._1D5 != 0) {
        if (animRelated[0xA7] == 0) {
            goto remove;
        }
        if (animRelated[0xA7] < 0xFF) {
            for (i = 0; i < 50; i++) {
                HUD_RECORD(scene, i)->rgba = (HUD_RECORD(scene, i)->rgba & ~0xFF) | animRelated[0xA7];
            }
        } else {
            for (i = 0; i < 50; i++) {
                HUD_RECORD(scene, i)->rgba = (HUD_RECORD(scene, i)->rgba & ~0xFF) | animRelated[0xA6];
            }
        }
    }

    if (pauseControl._1D5 != 0) {
        if (animRelated[0xA7] == 0) {
            goto remove;
        }
        if (animRelated[0xA7] < 0xFF) {
            for (i = 0; i < 50; i++) {
                HUD_RECORD(scene, i)->rgba = (HUD_RECORD(scene, i)->rgba & ~0xFF) | animRelated[0xA7];
            }
        }
    }

    for (team = 0; team < 2; team++) {
        for (j = 0; j < 5; j++) {
            slot = j + 0x27;
            if (team == g_GameLogic.teamFielding) {
                slot = j + 0x22;
            }
            stars = g_GameLogic.TeamStars[team];
            frame = HUD_RECORD(scene, slot)->frame >> 16;
            if (g_Batter.moonShotInd != 0 && g_Ball.framesSinceHit == 0 && team == g_GameLogic.teamBatting) {
                for (stars = 0; stars < 5; stars++) {
                    if (lbl_3_data_D250[stars] > g_GameLogic.PauseSimulationFrameCount) {
                        break;
                    }
                }
                newStars = stars;
            }
            if (stars > j) {
                if (scene->shownTeamStars[team] <= j) {
                    if (frame == 0) {
                        bannerFrame = HUD_RECORD(scene, 44)->frame >> 16;
                        if (bannerFrame == 0) {
                            gainTeam = team;
                        } else if (bannerFrame == 25) {
                            HUD_RECORD(scene, slot)->frame = 4 << 16;
                            HUD_RECORD(scene, slot)->playMode = UI_PLAY_FORWARD;
                        }
                    } else if (frame >= 20) {
                        HUD_RECORD(scene, slot)->frame = 3 << 16;
                        HUD_RECORD(scene, slot)->playMode = UI_PLAY_STOP;
                        scene->shownTeamStars[team]++;
                    }
                } else if (frame >= 3) {
                    HUD_RECORD(scene, slot)->playMode = UI_PLAY_STOP;
                }
            } else if (stars < scene->shownTeamStars[team] && frame >= 3) {
                HUD_RECORD(scene, slot)->playMode = UI_PLAY_BACKWARD;
                loseTeam = team;
                scene->shownTeamStars[team]--;
                if (newStars >= 0 && newStars != 4) {
                    loseTeam = -1;
                }
            }
        }
    }

    if (gainTeam >= 0) {
        HUD_RECORD(scene, 44)->flags |= UI_FLAG_VISIBLE;
        HUD_RECORD(scene, 44)->playMode = UI_PLAY_FORWARD;
        HUD_RECORD(scene, 45)->playMode = UI_PLAY_FORWARD;
        if (g_Batter.batterHand == BATTING_HAND_RIGHT) {
            if (gainTeam == g_GameLogic.teamFielding) {
                HUD_RECORD(scene, 45)->anchorSub = 1;
            } else {
                HUD_RECORD(scene, 45)->anchorSub = 0;
            }
        } else if (gainTeam == g_GameLogic.teamFielding) {
            HUD_RECORD(scene, 45)->anchorSub = 3;
        } else {
            HUD_RECORD(scene, 45)->anchorSub = 2;
        }
    } else if (HUD_RECORD(scene, 44)->unk69[0] == 2) {
        HUD_RECORD(scene, 44)->flags |= UI_FLAG_VISIBLE;
        HUD_RECORD(scene, 44)->playMode = UI_PLAY_STOP;
        HUD_RECORD(scene, 44)->frame = 0;
        HUD_RECORD(scene, 45)->playMode = UI_PLAY_STOP;
        HUD_RECORD(scene, 45)->frame = 0;
        HUD_RECORD(scene, 44)->flags &= ~UI_FLAG_VISIBLE;
    }

    if (loseTeam >= 0) {
        HUD_RECORD(scene, 46)->flags |= UI_FLAG_VISIBLE;
        HUD_RECORD(scene, 46)->playMode = UI_PLAY_BACKWARD;
        HUD_RECORD(scene, 47)->playMode = UI_PLAY_BACKWARD;
        if (g_Batter.batterHand == BATTING_HAND_RIGHT) {
            if (loseTeam == g_GameLogic.teamFielding) {
                HUD_RECORD(scene, 47)->anchorSub = 1;
            } else {
                HUD_RECORD(scene, 47)->anchorSub = 0;
            }
        } else if (loseTeam == g_GameLogic.teamFielding) {
            HUD_RECORD(scene, 47)->anchorSub = 3;
        } else {
            HUD_RECORD(scene, 47)->anchorSub = 2;
        }
    } else if ((HUD_RECORD(scene, 46)->frame >> 16) == 0) {
        HUD_RECORD(scene, 46)->flags |= UI_FLAG_VISIBLE;
        HUD_RECORD(scene, 46)->playMode = UI_PLAY_STOP;
        HUD_RECORD(scene, 46)->frame = 30 << 16;
        HUD_RECORD(scene, 47)->playMode = UI_PLAY_STOP;
        HUD_RECORD(scene, 47)->frame = 30 << 16;
        HUD_RECORD(scene, 46)->flags &= ~UI_FLAG_VISIBLE;
    }
    return;

remove:
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
    animRelated[0xA8] = 0;
}

// .text:0x0009A8A4 size:0x864 mapped:0x806D9938
void draw_initStarGuageHud(void) {
    StarGaugeScene* scene = (StarGaugeScene*)currentDrawingItem;
    int next;
    s32 i;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_C56C[g_Batter.batterHand]);
    HUD_RECORD(scene, 9)->frame = inMemRoster[g_GameLogic.teamFielding][g_Pitcher.rosterID].stats.CharID << 16;
    HUD_RECORD(scene, 10)->frame = inMemRoster[g_GameLogic.teamBatting][g_Batter.rosterID].stats.CharID << 16;

    next = g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam] + 1;
    if (next > 9) {
        next = 1;
    }
    HUD_RECORD(scene, 6)->frame = inMemRoster[g_GameLogic.teamBatting][g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.homeTeamBattingInd_fieldingTeam][next][0]].stats.CharID << 16;

    load_Icon(scene, 13, 1, 0x2A, lbl_3_data_D22C[inMemRoster[g_GameLogic.teamFielding][g_Pitcher.rosterID].stats.CharacterClass]);
    load_Icon(scene, 14, 1, 0x2A, lbl_3_data_D22C[inMemRoster[g_GameLogic.teamBatting][g_Batter.rosterID].stats.CharacterClass]);

    if (g_GameLogic.teamIsCPU[g_GameLogic.teamFielding] != 0) {
        HUD_RECORD(scene, 15)->frame = (g_GameLogic.teams[g_GameLogic.teamFielding] + 4) << 16;
    } else {
        HUD_RECORD(scene, 15)->frame = g_GameLogic.teams[g_GameLogic.teamFielding] << 16;
    }
    if (g_GameLogic.teamIsCPU[g_GameLogic.teamBatting] != 0) {
        HUD_RECORD(scene, 16)->frame = (g_GameLogic.teams[g_GameLogic.teamBatting] + 4) << 16;
    } else {
        HUD_RECORD(scene, 16)->frame = g_GameLogic.teams[g_GameLogic.teamBatting] << 16;
    }

    for (i = 0; i < 5; i++) {
        if (g_GameLogic.TeamStars[g_GameLogic.teamFielding] > i) {
            HUD_RECORD(scene, i + 0x22)->frame = 3 << 16;
        }
        if (g_GameLogic.TeamStars[g_GameLogic.teamBatting] > i) {
            HUD_RECORD(scene, i + 0x27)->frame = 3 << 16;
        }
    }

    if (inningSetting.starSkillsSetting == 0 && g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE) {
        load_Icon(scene, 3, 1, 0x22, starGuageIconIDs[0]);
        load_Icon(scene, 4, 1, 0x22, starGuageIconIDs[0]);
        HUD_RECORD(scene, 3)->rgba = (HUD_RECORD(scene, 3)->rgba & 0xFF) | 0xBEBEBE00;
        HUD_RECORD(scene, 4)->rgba = (HUD_RECORD(scene, 4)->rgba & 0xFF) | 0xBEBEBE00;
        for (i = 0x18; i <= 0x2B; i++) {
            HUD_RECORD(scene, i)->flags &= ~UI_FLAG_VISIBLE;
        }
    } else {
        load_Icon(scene, 3, 1, 0x22, starGuageIconIDs[inMemRoster[g_GameLogic.teamFielding][g_Pitcher.rosterID].stats.CaptainStarHitPitch]);
        load_Icon(scene, 4, 1, 0x22, starGuageIconIDs[inMemRoster[g_GameLogic.teamBatting][g_Batter.rosterID].stats.CaptainStarHitPitch]);
    }

    if (g_GameLogic.IsStarChance != 0) {
        HUD_RECORD(scene, 21)->flags &= ~UI_FLAG_VISIBLE;
        HUD_RECORD(scene, 17)->flags &= ~UI_FLAG_VISIBLE;
    } else {
        HUD_RECORD(scene, 22)->flags &= ~UI_FLAG_VISIBLE;
        if (g_Batter.chemLinksOnBase == 0) {
            HUD_RECORD(scene, 17)->flags &= ~UI_FLAG_VISIBLE;
        }
        if (animRelated[0xAE] == 0 || animRelated[0xAF] != g_Pitcher.rosterID) {
            HUD_RECORD(scene, 21)->flags &= ~UI_FLAG_VISIBLE;
        }
    }

    HUD_RECORD(scene, 46)->frame = 30 << 16;
    HUD_RECORD(scene, 47)->frame = 30 << 16;
    if (g_d_GameSettings.exhibitionMatchInd == 0) {
        if (((u8*)starMissionCompletionTracker)[0x43D6 + g_Pitcher.charID] != 0 && g_GameLogic.teamIsCPU[g_GameLogic.teamFielding] == 0) {
            HUD_RECORD(scene, 48)->flags |= UI_FLAG_VISIBLE;
        }
        if (((u8*)starMissionCompletionTracker)[0x43D6 + g_Batter.charID] != 0 && g_GameLogic.teamIsCPU[g_GameLogic.teamBatting] == 0) {
            HUD_RECORD(scene, 49)->flags |= UI_FLAG_VISIBLE;
        }
    } else {
        if (Static_Stats_Tables.charIsStarred[g_GameLogic.teamFielding][g_Pitcher.rosterID] != 0) {
            HUD_RECORD(scene, 48)->flags |= UI_FLAG_VISIBLE;
        }
        if (Static_Stats_Tables.charIsStarred[g_GameLogic.teamBatting][g_Batter.rosterID] != 0) {
            HUD_RECORD(scene, 49)->flags |= UI_FLAG_VISIBLE;
        }
    }

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE && g_Practice.practiceLevel != 7) {
        HUD_RECORD(scene, 20)->flags &= ~UI_FLAG_VISIBLE;
        HUD_RECORD(scene, 5)->flags &= ~UI_FLAG_VISIBLE;
    }

    scene->frameCount = 0;
    scene->shownTeamStars[0] = g_GameLogic.TeamStars[0];
    scene->shownTeamStars[1] = g_GameLogic.TeamStars[1];
    scene->unk20 = 0;
    animRelated[0xA8] = 1;
    currentDrawingItem->func = draw_ongoingStarGuageHud;
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
    ScoreHudScene* scene = (ScoreHudScene*)currentDrawingItem;
    s32 i;

    scene->frameCount++;
    if (animRelated[0x96] != 0 || animRelated[0xA7] == 0) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }

    if (scene->shownScores[0] != g_Scores.scores[0].total || scene->shownScores[1] != g_Scores.scores[1].total) {
        fn_3_9B108((DrawingSceneStruct*)scene);
    }

    if (animRelated[0xA7] < 0xFF) {
        for (i = 0; i < 16; i++) {
            HUD_RECORD(scene, i)->rgba = (HUD_RECORD(scene, i)->rgba & ~0xFF) | animRelated[0xA7];
        }
    } else {
        for (i = 4; i <= 15; i++) {
            HUD_RECORD(scene, i)->rgba = (HUD_RECORD(scene, i)->rgba & ~0xFF) | animRelated[0xA6];
        }
    }
}

// .text:0x0009B7F4 size:0x6EC mapped:0x806DA888
void draw_ScoreInningHud(void) {
    ScoreHudScene* scene = (ScoreHudScene*)currentDrawingItem;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_C34C);
    HUD_RECORD(scene, 5)->elementIndex = lbl_3_data_F430[g_GameLogic.logo[0].captain][1];
    HUD_RECORD(scene, 6)->elementIndex = lbl_3_data_F430[g_GameLogic.logo[1].captain][1];
    HUD_RECORD(scene, 5)->frame = g_GameLogic.logo[0].variationID << 16;
    HUD_RECORD(scene, 6)->frame = g_GameLogic.logo[1].variationID << 16;

    if (g_Scores.halfInning != 0) {
        HUD_RECORD(scene, 1)->elementIndex = 0x11B;
        HUD_RECORD(scene, 2)->elementIndex = 0x119;
        HUD_RECORD(scene, 3)->elementIndex = 0x116;
    }

    setIndicatorSlotState((DrawingSceneStruct*)scene, 3, 1, 0x110, lbl_3_data_F4D0[g_Scores.Inning - 1]);
    setIndicatorSlotState((DrawingSceneStruct*)scene, 3, 3, 0x110, lbl_3_data_F4D0[g_Scores.Inning - 1]);

    if (g_Scores.Inning >= 10) {
        HUD_RECORD(scene, 7)->flags &= ~UI_FLAG_VISIBLE;
        HUD_RECORD(scene, 8)->flags |= UI_FLAG_VISIBLE;
        HUD_RECORD(scene, 9)->flags |= UI_FLAG_VISIBLE;
        HUD_RECORD(scene, 9)->frame = 0;
        HUD_RECORD(scene, 8)->frame = 1 << 16;
        setIndicatorSlotState((DrawingSceneStruct*)scene, 9, 1, 0x112, g_Scores.Inning / 10);
        setIndicatorSlotState((DrawingSceneStruct*)scene, 8, 2, 0x112, g_Scores.Inning % 10);
        setIndicatorSlotState((DrawingSceneStruct*)scene, 9, 4, 0x112, g_Scores.Inning / 10);
        setIndicatorSlotState((DrawingSceneStruct*)scene, 8, 5, 0x112, g_Scores.Inning % 10);
    } else {
        HUD_RECORD(scene, 7)->frame = 2 << 16;
        setIndicatorSlotState((DrawingSceneStruct*)scene, 7, 3, 0x112, g_Scores.Inning);
        setIndicatorSlotState((DrawingSceneStruct*)scene, 7, 6, 0x112, g_Scores.Inning);
    }

    if (g_Scores.scores[0].total >= 10) {
        HUD_RECORD(scene, 10)->flags &= ~UI_FLAG_VISIBLE;
        HUD_RECORD(scene, 11)->flags |= UI_FLAG_VISIBLE;
        HUD_RECORD(scene, 12)->flags |= UI_FLAG_VISIBLE;
        HUD_RECORD(scene, 12)->frame = 2 << 16;
        HUD_RECORD(scene, 11)->frame = 3 << 16;
    } else {
        HUD_RECORD(scene, 10)->frame = 0;
    }

    if (g_Scores.scores[1].total >= 10) {
        HUD_RECORD(scene, 13)->flags &= ~UI_FLAG_VISIBLE;
        HUD_RECORD(scene, 14)->flags |= UI_FLAG_VISIBLE;
        HUD_RECORD(scene, 15)->flags |= UI_FLAG_VISIBLE;
        HUD_RECORD(scene, 15)->frame = 4 << 16;
        HUD_RECORD(scene, 14)->frame = 5 << 16;
    } else {
        HUD_RECORD(scene, 13)->frame = 1 << 16;
    }

    fn_3_9B108((DrawingSceneStruct*)scene);

    scene->shownScores[0] = g_Scores.scores[0].total;
    scene->shownScores[1] = g_Scores.scores[1].total;
    scene->frameCount = 0;
    currentDrawingItem->func = fn_3_9B320;
}

// .text:0x0009BEE0 size:0x134 mapped:0x806DAF74
void maybe_updateBallStrikeOutUI(DrawingSceneStruct* node) {
    int outs;
    int i;
    int state;

    outs = g_Strikes.outs;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        outs = g_Minigame.toyField_maxOuts - g_Minigame.toyField_outsRemaining;
    }

    for (i = 0; i < 7; i++) {
        state = 3;
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && i >= 5) {
            break;
        }
        if (i < 2) {
            if (((BallStrikeOutScene*)node)->shownStrikes == g_Strikes.strikes) {
                continue;
            }
            if (g_Strikes.strikes >= i + 1) {
                state = 0;
            }
        } else if (i < 5) {
            if (((BallStrikeOutScene*)node)->shownBalls == g_Strikes.balls) {
                continue;
            }
            if (g_Strikes.balls >= i - 1) {
                state = 1;
            }
        } else {
            if (((BallStrikeOutScene*)node)->shownOuts == outs) {
                continue;
            }
            if (outs >= i - 4) {
                state = 2;
            }
        }
        setIndicatorSlotState(node, i + 1, i + 1, 0x107, state);
    }

    ((BallStrikeOutScene*)node)->shownStrikes = g_Strikes.strikes;
    ((BallStrikeOutScene*)node)->shownBalls = g_Strikes.balls;
    ((BallStrikeOutScene*)node)->shownOuts = outs;
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
            HUD_RECORD(scene, i)->pos.y = lbl_3_rodata_17D8;
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

