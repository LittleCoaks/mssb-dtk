#define SQRT2_LINKAGE static
#include "game/hud/hud_scoreboard.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "text/text_channel.h"
#include "musyx/musyx.h"
#include "game/camera/camera.h"
#include "Unknown/File_0x80034cec.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x8003649c.h"
#include "Unknown/File_0x800363d8.h"
#include "Unknown/File_0x800b0a14.h"
#define REP_HEADER_DATA_FN getRepHeaderData_hudScoreboard
#include "header_rep_data.h"

extern u8 animRelated[0x124];
extern u8 pauseControl[0x264];
extern u8 menuNumber[0x28];
extern UIRecordDescriptor lbl_3_data_BF6C[];
extern UIRecordDescriptor lbl_3_data_F350[];
extern UIRecordDescriptor lbl_3_data_F390[];
extern UIRecordDescriptor lbl_3_data_F224[];
extern u16 lbl_3_data_F344[];
extern UIRecordDescriptor lbl_3_data_EABC[];
extern UIRecordDescriptor lbl_3_data_E75C[];
extern UIRecordDescriptor lbl_3_data_F3F0[];
extern u8 lbl_3_data_E758[];
extern UIRecordDescriptor lbl_3_data_E378[];
extern UIRecordDescriptor lbl_3_data_EC1C[];
extern UIRecordDescriptor lbl_3_data_BFEC[];
extern f32 lbl_3_data_C1CC[];
extern UIRecordDescriptor lbl_3_data_C1EC[];
extern UIRecordDescriptor lbl_3_data_E278[];
extern UIRecordDescriptor lbl_3_data_E21C[];
extern UIRecordDescriptor lbl_3_data_E160[];
extern UIRecordDescriptor lbl_3_data_E120[];
extern UIRecordDescriptor lbl_3_data_E0E0[];
extern UIRecordDescriptor lbl_3_data_E2F8[];
extern u16 lbl_3_data_E200[];
extern UIRecordDescriptor lbl_3_data_E85C[];
extern u8 lbl_3_data_F430[][2];
extern u8 lbl_3_data_F200[];

// The scene node's view of its record span in graphicsRelatedArray plus the
// small per-node state words the scoreboard functions keep at +0x18..+0x20.
typedef struct HudScene {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ u16 firstHandle;
    /*0x16*/ u16 handleCount;
    /*0x18*/ u16 unk18;
    /*0x1A*/ u16 unk1A;
    /*0x1C*/ u16 unk1C;
    /*0x1E*/ u16 unk1E;
    /*0x20*/ u16 unk20;
} HudScene;

// The scout-mission tracker's per-mission rows, as the scout HUD reads them
// (signed: a row is live when active is nonzero).
typedef struct HudScoutEntry {
    /*0x0*/ s8 achieved;
    /*0x1*/ s8 max;
    /*0x2*/ s8 amount;
    /*0x3*/ s8 active;
    /*0x4*/ s8 trackerIdx;
} HudScoutEntry; // size 0x5

typedef struct HudScoutState {
    /*0x00*/ u8 _00[0x12];
    /*0x12*/ HudScoutEntry entries[9];
    /*0x3F*/ u8 _3F;
    /*0x40*/ s16 humanTeam;
    /*0x42*/ s16 scoutCountdown;
    /*0x44*/ s16 targetRosterID;
    /*0x46*/ u8 scoutMissionID;
    /*0x47*/ u8 scoutResult;
} HudScoutState;

extern HudScoutState lbl_3_common_bss_37400;

typedef struct HudEventTiming {
    /*0x0*/ s16 elementIndex;
    /*0x2*/ s16 frameThreshold;
    /*0x4*/ s16 holdFrames;
    /*0x6*/ s16 yOffset;
} HudEventTiming; // size 0x8

extern HudEventTiming lbl_3_data_BE50[];
extern void fn_3_ED0F4(void);
extern void toyFieldDrawRelated_miniMap(void);

// The event-banner tables the scoreboard shares with the scene descriptors
// that follow them, laid out from lbl_3_data_8D88.
typedef struct HudEventData {
    /*0x0000*/ UIRecordDescriptor toyFieldMiniMap[7];
    /*0x00E0*/ u8 _00E0[0x30C8 - 0xE0];
    /*0x30C8*/ s16 rows[25][4];
    /*0x3190*/ u16 scoringElements[10];
    /*0x31A4*/ UIRecordDescriptor descriptors[2];
    /*0x31E4*/ u8 _31E4[0x60D4 - 0x31E4];
    /*0x60D4*/ UIRecordDescriptor scoreboardDescriptors[2];
    /*0x6114*/ u8 _6114[0x6474 - 0x6114];
    /*0x6474*/ u16 digitElement;
    /*0x6476*/ u8 _6476[0x6484 - 0x6476];
    /*0x6484*/ u8 anchorSubs[24];
    /*0x649C*/ u8 _649C[0x66A8 - 0x649C];
    /*0x66A8*/ u8 logoElements[20][2];
} HudEventData;

extern HudEventData lbl_3_data_8D88;
extern u8 lbl_3_data_84B8[0x3C];
extern u16 stadiumHazardSoundIDs[16];
extern u8 stadiumHazardSoundFxRelated[0xB4];
extern u8 audioFileDescriptors[0x39C];

// The diamond minimap node: four per-base slots (base index + 10 * phase) on
// top of the usual frame counters.
typedef struct MiniMapScene {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ u16 firstHandle;
    /*0x16*/ u16 handleCount;
    /*0x18*/ u16 frameCount;
    /*0x1A*/ u16 phase;
    /*0x1C*/ u16 slots[4];
} MiniMapScene;

// The home-run score ticker node: the two team scores as currently drawn, and
// the two they are counting up to.
typedef struct HudDigitScene {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ u16 firstHandle;
    /*0x16*/ u16 handleCount;
    /*0x18*/ u16 frameCount;
    /*0x1A*/ u16 settled;
    /*0x1C*/ u16 counts[4]; // [0..1] shown, [2..3] target
} HudDigitScene;

#define SHOWN(scene, t) ((scene)->counts[(t)])
#define TARGET(scene, t) ((scene)->counts[2 + (t)])

#define REC(scene, i) ((UIRecord*)graphicsRelatedArray[(scene)->firstHandle + (i)].object)
#define REC_AT(scene, i, off) ((UIRecord*)graphicsRelatedArray[(scene)->firstHandle + (i) + (off)].object)

// .text:0x00096CA4 size:0x4A0 mapped:0x806D5D38
void handleInGameEventsAndSoundEffects(void) {
    HudScene* scene = (HudScene*)currentDrawingItem;
    HudEventData* data = &lbl_3_data_8D88;
    int elementIndex;
    int stadiumID;
    int nearLead;

    if (g_UnkSound_32718._07 == 13 && animRelated[0x98] != 0) {
        return;
    }
    scene->unk1C = g_UnkSound_32718._07;
    elementIndex = data->rows[scene->unk1C][0];
    if (g_d_GameSettings.minigamesEnabled == 0 && (elementIndex == 0xBB || elementIndex == 0xFD)) {
        if (++animRelated[0xA9] == 2) {
            scene->unk1C = 0x17;
        }
        if (animRelated[0xA9] == 3) {
            scene->unk1C = 0x18;
        }
        elementIndex = data->rows[scene->unk1C][0];
    }
    switch (g_UnkSound_32718._07) {
    case 1:
        playSoundEffect(0x15C);
        break;
    case 2:
        playSoundEffect(0x15D);
        break;
    case 5:
        playSoundEffect(0x165);
        break;
    case 8:
        playSoundEffect(0x15A);
        break;
    case 9:
        playSoundEffect(0x15B);
        break;
    case 10:
        playSoundEffect(0x162);
        break;
    case 11:
        playSoundEffect(0x163);
        break;
    case 12:
        playSoundEffect(0x15E);
        break;
    case 18:
        playSoundEffect(0x15C);
        break;
    case 14:
        playSoundEffect(0x15F);
        break;
    case 13:
    case 17:
        playSoundEffect(0x160);
        break;
    case 3:
        playSoundEffect(0x164);
        break;
    case 4:
        playSoundEffect(0x166);
        break;
    case 6:
        playSoundEffect(0x167);
        break;
    case 21:
        if (audioFileDescriptors[0x398] == 1) {
            SND_VOICEID voice;

            stadiumID = g_d_GameSettings.StadiumID;
            voice = sndFXStartEx(stadiumHazardSoundIDs[stadiumID] + 0x19,
                                 g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                                     ? lbl_3_data_84B8[0x32]
                                     : stadiumHazardSoundFxRelated[stadiumID * 0x1E + 0x32],
                                 0x3F, 0);
            sndFXCtrl(voice, 0x5B,
                      g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                          ? lbl_3_data_84B8[0x33]
                          : stadiumHazardSoundFxRelated[stadiumID * 0x1E + 0x33]);
        }
        break;
    case 16:
        playSoundEffect(0x15A);
        break;
    case 22:
        playSoundEffect(0x164);
        break;
    }
    data->descriptors[0].elementIndex = elementIndex;
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD && scene->unk1C == 0xF) {
        nearLead = 0;
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
            data->descriptors[0].elementIndex =
                data->scoringElements[g_RunningLogic.nOffensivePlayersAtStartOfPlay - 1];
        } else {
            s16 ourScore = g_Scores._A0;
            s16 theirScore = g_Scores.scores[g_GameLogic.awayTeamBattingInd_battingTeam].total;

            if (ourScore < theirScore && ourScore + g_RunningLogic.nOffensivePlayersAtStartOfPlay > theirScore) {
                nearLead = 1;
            }
            if (g_Scores.Inning >= g_Scores.inningLimit && g_Scores.halfInning != 0 &&
                ourScore + g_RunningLogic.nOffensivePlayersAtStartOfPlay > theirScore) {
                if (nearLead) {
                    if (g_RunningLogic.nOffensivePlayersAtStartOfPlay == 4) {
                        data->descriptors[0].elementIndex = data->scoringElements[8];
                    } else {
                        data->descriptors[0].elementIndex = data->scoringElements[7];
                    }
                } else {
                    data->descriptors[0].elementIndex = data->scoringElements[6];
                }
            } else if (nearLead) {
                if (g_RunningLogic.nOffensivePlayersAtStartOfPlay == 4) {
                    data->descriptors[0].elementIndex = data->scoringElements[5];
                } else {
                    data->descriptors[0].elementIndex = data->scoringElements[4];
                }
            } else {
                data->descriptors[0].elementIndex =
                    data->scoringElements[g_RunningLogic.nOffensivePlayersAtStartOfPlay - 1];
            }
        }
    }
    if (scene->unk1C == 0x15) {
        data->descriptors[0].tag = 0xE;
    } else {
        data->descriptors[0].tag = 2;
    }
    addGraphicsElementToScene((DrawingSceneStruct*)scene, data->descriptors);
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        REC(scene, 0)->pos.y = data->rows[scene->unk1C][3];
    }
    scene->unk18 = 0;
    scene->unk1A = 0;
    scene->unk1E = 0;
    currentDrawingItem->func = inGameEventBanner_update;
}

// .text:0x0009698C size:0x318 mapped:0x806D5A20
void inGameEventBanner_update(void) {
    HudScene* scene = (HudScene*)currentDrawingItem;

    if (scene->unk18 < 0xFFFE) {
        scene->unk18++;
    } else {
        scene->unk18 = 0xFFFF;
    }
    if (animRelated[0x96] != 0 || g_Stats.replayInd != 0) {
        goto remove;
    }
    if (scene->unk1C == 0xF) {
        if (REC(scene, 0)->unk69[0] == 2) {
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                insertGraphicDrawingFunction(fn_3_ED0F4, 2);
            }
            goto remove;
        }
        if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL && g_GameLogic.gameStatus != GAME_STATUS_AT_BAT &&
            g_GameLogic.gameStatus != GAME_STATUS_DEFAULT && g_GameLogic.gameStatus != GAME_STATUS_HOMERUN_LAP) {
            goto remove;
        }
    } else if (scene->unk1E == 2) {
        if (REC(scene, 0)->unk69[0] == 2) {
            goto remove;
        }
        if (g_GameLogic.hudElementLoadingInd != 0) {
            goto remove;
        }
        if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL && g_GameLogic.gameStatus != GAME_STATUS_AT_BAT &&
            g_GameLogic.gameStatus != GAME_STATUS_DEFAULT) {
            goto remove;
        }
    } else if (scene->unk1E == 1) {
        if (g_GameLogic.hudElementLoadingInd != 0) {
            goto remove;
        }
        if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL && g_GameLogic.gameStatus != GAME_STATUS_AT_BAT &&
            g_GameLogic.gameStatus != GAME_STATUS_DEFAULT) {
            goto remove;
        }
    }
    if (scene->unk1E == 0) {
        if ((REC(scene, 0)->frame >> 16) >= (u32)lbl_3_data_BE50[scene->unk1C].frameThreshold) {
            scene->unk1E = 1;
            REC(scene, 0)->playMode = UI_PLAY_STOP;
        }
    } else if (scene->unk1E == 1) {
        if (g_UnkSound_32718.queue[0] != 0 || (g_d_GameSettings.exhibitionMatchInd == 0 && animRelated[0xB4] != 0)) {
            REC(scene, 0)->playMode = UI_PLAY_FORWARD;
            scene->unk1E = 2;
        } else {
            if (scene->unk1A < 0xFFFE) {
                scene->unk1A++;
            } else {
                scene->unk1A = 0xFFFF;
            }
            if (scene->unk1A >= lbl_3_data_BE50[scene->unk1C].holdFrames) {
                REC(scene, 0)->playMode = UI_PLAY_FORWARD;
                scene->unk1E = 2;
            }
        }
    }
    if (scene->unk1C == 0x10 || scene->unk1C == 0x16) {
        if (scene->unk18 == 0x23) {
            playSoundEffect(0x15C);
        }
    }
    return;
remove:
    g_UnkSound_32718._07 = 0;
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
}

// .text:0x00096914 size:0x78 mapped:0x806D59A8
void toyfield_hud_turns_diamondMap(void) {
    if (animRelated[0xC7] == 0 && g_GameLogic.hudElementLoadingInd != 0) {
        insertGraphicDrawingFunction(drawDiamondMiniMap_init, 2);
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
            insertGraphicDrawingFunction(toyFieldDrawRelated_miniMap, 2);
        }
    }
}

// .text:0x0009669C size:0x278 mapped:0x806D5730
void drawDiamondMiniMap_init(void) {
    MiniMapScene* scene = (MiniMapScene*)currentDrawingItem;
    int i;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_8D88.toyFieldMiniMap);
        for (i = 1; i < 4; i++) {
            if ((&g_Minigame.toyField_runnerOnHome)[i] != 0) {
                REC_AT(scene, 1, i)->flags |= UI_FLAG_VISIBLE;
                REC_AT(scene, 1, i)->playMode = UI_PLAY_STOP;
                scene->slots[i] = i;
            } else {
                scene->slots[i] = 9;
            }
            REC_AT(scene, 1, i)->frame = (i - 1) << 16;
        }
        if (g_Minigame._19A2 != 0) {
            REC(scene, 5)->flags |= UI_FLAG_VISIBLE;
        }
    } else {
        addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_BFEC);
        for (i = 9; i < 12; i++) {
            REC(scene, i)->frame = (i - 9) << 16;
        }
        for (i = 0; i < 4; i++) {
            if (g_Runners[i].charID >= 0) {
                REC_AT(scene, 5, i)->frame = g_Runners[i].charID << 16;
            }
        }
    }
    animRelated[0xC7] = 1;
    scene->frameCount = 0;
    scene->phase = 0;
    scene->slots[0] = 0;
    currentDrawingItem->func = drawDiamondMiniMap_ongoing;
}

// .text:0x000959BC size:0xCE0 mapped:0x806D4A50
static inline void setMiniMapAlpha(MiniMapScene* scene, int alpha) {
    int i;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        for (i = 1; i < 6; i++) {
            REC(scene, i)->rgba = (REC(scene, i)->rgba & ~0xFF) | alpha;
        }
    } else {
        for (i = 1; i < 14; i++) {
            REC(scene, i)->rgba = (REC(scene, i)->rgba & ~0xFF) | alpha;
        }
    }
}

void drawDiamondMiniMap_ongoing(void) {
    MiniMapScene* scene = (MiniMapScene*)currentDrawingItem;
    int phase;
    int i;
    int k;
    int alpha;
    BOOL anyReady;

    if (scene->frameCount < 0xFFFE) {
        scene->frameCount++;
    } else {
        scene->frameCount = 0xFFFF;
    }
    if (animRelated[0x96] != 0) {
        goto remove;
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        if (g_Practice.tutorialState == 0) {
            goto remove;
        }
        if (g_Practice.completionMenuActive != 0) {
            goto remove;
        }
    }
    if (scene->phase != 0) {
        if (scene->phase < 0xFFFE) {
            scene->phase++;
        } else {
            scene->phase = 0xFFFF;
        }
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        if (g_Minigame.framesSincePanelHit == 1) {
            anyReady = FALSE;
            for (k = 0; k < 4; k++) {
                if ((&g_Minigame.toyField_runnerBase0)[k] > k) {
                    anyReady = TRUE;
                }
            }
            if (anyReady) {
                scene->phase = 1;
            }
        }
        if (scene->phase != 0) {
            for (i = 1; i < 5; i++) {
                REC(scene, i)->flags &= ~UI_FLAG_VISIBLE;
            }
            phase = (scene->phase - 1) % 45;
            if (phase == 0) {
                for (i = 0; i < 4; i++) {
                    int state = scene->slots[i] % 10;

                    if (state == 4) {
                        scene->slots[i] = 14;
                    } else if (state < (&g_Minigame.toyField_runnerBase0)[i]) {
                        scene->slots[i]++;
                        REC(scene, scene->slots[i] % 10 % 4 + 1)->flags |= UI_FLAG_VISIBLE;
                    } else if (state > 0 && state < 4 && state == (&g_Minigame.toyField_runnerBase0)[i]) {
                        REC(scene, state % 4 + 1)->flags |= UI_FLAG_VISIBLE;
                        if (scene->slots[i] < 10) {
                            scene->slots[i] += 10;
                        }
                    }
                }
            }
            for (i = 0; i < 4; i++) {
                u16 slot = scene->slots[i];
                int bit = slot % 10 % 4 + 1;

                if (slot <= (&g_Minigame.toyField_runnerBase0)[i]) {
                    if (bit == 1) {
                        REC(scene, bit)->flags |= UI_FLAG_VISIBLE;
                    } else if (phase <= 15 || phase > 30) {
                        REC(scene, bit)->flags |= UI_FLAG_VISIBLE;
                    }
                    g_Minigame._1925 |= 1 << (bit - 1);
                } else if (slot >= 10) {
                    g_Minigame._1925 |= 1 << (bit - 1);
                    REC(scene, bit)->flags |= UI_FLAG_VISIBLE;
                }
            }
        }
    } else {
        for (i = 9; i < 12; i++) {
            REC(scene, i)->flags &= ~UI_FLAG_VISIBLE;
        }
        for (i = 0; i < 4; i++) {
            InMemRunnerType* runner = &g_Runners[i];
            int idx = i + 1;
            int base;

            if (!(runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD && g_Strikes.outs < 3)) {
                REC(scene, idx)->flags &= ~UI_FLAG_VISIBLE;
            } else {
                if (i == 0) {
                    int sinceHit = g_Ball.framesSinceHit;

                    if (sinceHit >= 1) {
                        if (runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_ON_FIELD ||
                            runner->runnerOnFieldOrOutOrScored == RUNNER_STATUS_WALK_WHILE_STEALING) {
                            if (sinceHit < 16) {
                                REC(scene, idx)->rgba = (REC(scene, idx)->rgba & ~0xFF) | (sinceHit << 4);
                            } else {
                                REC(scene, idx)->rgba = (REC(scene, idx)->rgba & ~0xFF) | 0xFF;
                            }
                        }
                    } else {
                        REC(scene, idx)->flags &= ~UI_FLAG_VISIBLE;
                        continue;
                    }
                } else {
                    REC(scene, idx)->rgba = (REC(scene, idx)->rgba & ~0xFF) | 0xFF;
                }
                REC(scene, idx)->flags |= UI_FLAG_VISIBLE;
                {
                    f32 mapX = lbl_3_data_C1CC[2] * runner->position.x;
                    f32 mapY = lbl_3_data_C1CC[3] * -runner->position.z;

                    REC(scene, idx)->pos.x = mapX + lbl_3_data_C1CC[0];
                    REC(scene, idx)->pos.y = mapY + lbl_3_data_C1CC[1];
                }
                base = runner->currentBase;
                if (base >= 1 && base <= 3) {
                    REC_AT(scene, 8, base)->flags |= UI_FLAG_VISIBLE;
                }
            }
        }
        REC(scene, 12)->flags &= ~UI_FLAG_VISIBLE;
        if (g_GameLogic.sceneID == SCENE_ID_AT_BAT) {
            for (i = 1; i < 4; i++) {
                if (g_Runners[i].runnerOnFieldOrOutOrScored != 0 && g_Runners[i].furthestBaseForcedToGoToOnWalk != 0) {
                    REC(scene, 12)->flags |= UI_FLAG_VISIBLE;
                    for (; i < 4; i++) {
                        if (g_Runners[i].stealingStatus == 3) {
                            break;
                        }
                    }
                    if (i < 4) {
                        REC(scene, 12)->elementIndex = 0xA2;
                    } else {
                        REC(scene, 12)->elementIndex = 0xA6;
                    }
                    break;
                }
            }
        }
        REC(scene, 13)->flags &= ~UI_FLAG_VISIBLE;
        if (g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE &&
            g_GameLogic.teamIsCPU[g_GameLogic.teamBatting] == 0 &&
            g_GameLogic.battingAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam] != 0) {
            REC(scene, 13)->flags |= UI_FLAG_VISIBLE;
        }
    }
    if (scene->frameCount <= 0x10) {
        alpha = scene->frameCount << 4;
        if (alpha > 0xFF) {
            alpha = 0xFF;
        }
        setMiniMapAlpha(scene, alpha);
    }
    if (pauseControl[0x1D5] != 0 && g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD) {
        alpha = 0xF0 - (*(s16*)&pauseControl[0xC] << 4);
        if (alpha <= 0) {
            goto remove;
        }
        setMiniMapAlpha(scene, alpha);
    }
    if (g_GameLogic.hudLoadingRelated != 0 || g_GameLogic.gameStatus == GAME_STATUS_INNING_TRANSITION ||
        g_GameLogic.gameStatus == GAME_STATUS_MVP_END_GAME || g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_MENU) {
        goto remove;
    }
    return;
remove:
    animRelated[0xC7] = 0;
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
}

// .text:0x00095970 size:0x4C mapped:0x806D4A04
void offscreenFielderIndicator_init(void) {
    addGraphicsElementToScene(currentDrawingItem, lbl_3_data_C1EC);
    currentDrawingItem->func = offscreenFielderIndicator_update;
}

// .text:0x00095620 size:0x350 mapped:0x806D46B4
void offscreenFielderIndicator_update(void) {
    HudScene* scene = (HudScene*)currentDrawingItem;
    int x;
    int y;

    if (animRelated[0x96] != 0) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        if (g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_FIELDING ||
            g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_PRACTICE_BASERUNNING ||
            g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_FREE_BAT_AND_RUNNING ||
            g_GameLogic.secondaryGameMode == SECONDARY_GAME_MODE_FREE_FIELDING) {
            if (g_Practice.frames_sincePracticeCompleted != 0) {
                REC(scene, 0)->flags &= ~UI_FLAG_VISIBLE;
                return;
            }
        } else {
            REC(scene, 0)->flags &= ~UI_FLAG_VISIBLE;
            return;
        }
    }
    if (g_Stats.replayInd != 0) {
        REC(scene, 0)->flags &= ~UI_FLAG_VISIBLE;
    } else if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
        REC(scene, 0)->flags &= ~UI_FLAG_VISIBLE;
    } else if (g_GameLogic.sceneID == SCENE_ID_AT_BAT) {
        REC(scene, 0)->flags &= ~UI_FLAG_VISIBLE;
    } else if (g_GameLogic.teamIsCPU[g_GameLogic.teamFielding] != 0) {
        REC(scene, 0)->flags &= ~UI_FLAG_VISIBLE;
    } else if (g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam] != 0 &&
               g_GameLogic.autoFielding[g_GameLogic.awayTeamBattingInd_battingTeam] != 0) {
        REC(scene, 0)->flags &= ~UI_FLAG_VISIBLE;
    } else if (g_FieldingLogic.unkFlagMaybeInAir != 0) {
        REC(scene, 0)->flags &= ~UI_FLAG_VISIBLE;
    } else if (g_FieldingLogic.selectedFielder < 0) {
        REC(scene, 0)->flags &= ~UI_FLAG_VISIBLE;
    } else {
        InMemFielder* fielder = &g_Fielders[g_FieldingLogic.selectedFielder];

        REC(scene, 0)->flags |= UI_FLAG_VISIBLE;
        fn_3_1650C(&x, &y, FALSE, fielder->pos.x, -2.0f - fielder->actionYOffset, fielder->pos.z);
        REC(scene, 0)->pos.x = x;
        REC(scene, 0)->pos.y = y;
        REC(scene, 0)->rgba = (REC(scene, 0)->rgba & 0xFF) | 0xFFFFFF00;
    }
}

// .text:0x000955CC size:0x54 mapped:0x806D4660
void HUD_initStarChance(void) {
    addGraphicsElementToScene(currentDrawingItem, lbl_3_data_E0E0);
    playSoundEffect(0x1A9);
    currentDrawingItem->func = HUD_ongoingStarChance;
}

// .text:0x00095568 size:0x64 mapped:0x806D45FC
void HUD_ongoingStarChance(void) {
    HudScene* scene = (HudScene*)currentDrawingItem;

    if (animRelated[0x96] != 0 || REC(scene, 0)->unk69[0] == 2) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    }
}

// .text:0x0009551C size:0x4C mapped:0x806D45B0
void fn_3_9551C(void) {
    addGraphicsElementToScene(currentDrawingItem, lbl_3_data_E120);
    currentDrawingItem->func = fn_3_954C4;
}

// .text:0x000954C4 size:0x58 mapped:0x806D4558
void fn_3_954C4(void) {
    DrawingSceneStruct* node = currentDrawingItem;

    if (animRelated[0x96] != 0 || g_GameLogic.gameStatus != GAME_STATUS_STAR_CHANCE_VS) {
        removeGraphicsElementFromScene(node);
        removeCurrentDrawingItem();
    }
}

// .text:0x000953FC size:0xC8 mapped:0x806D4490
void fn_3_953FC(void) {
    HudScene* scene = (HudScene*)currentDrawingItem;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_E160);
    REC(scene, 2)->frame = lbl_3_data_E200[lbl_3_common_bss_37400.scoutMissionID] << 16;
    REC(scene, 3)->frame = lbl_3_data_E200[lbl_3_common_bss_37400.scoutMissionID] << 16;
    animRelated[0xB4] = 0;
    animRelated[0xB3] = 0;
    currentDrawingItem->func = fn_3_9538C;
}

// .text:0x0009538C size:0x70 mapped:0x806D4420
void fn_3_9538C(void) {
    DrawingSceneStruct* node = currentDrawingItem;

    if (animRelated[0x96] != 0 || g_GameLogic.gameStatus != GAME_STATUS_STAR_CHANCE_VS) {
        insertGraphicDrawingFunction(scoutMissionBanner_init, 2);
        removeGraphicsElementFromScene(node);
        removeCurrentDrawingItem();
    }
}

// .text:0x000952DC size:0xB0 mapped:0x806D4370
void fn_3_952DC(void) {
    HudScene* scene = (HudScene*)currentDrawingItem;

    if (animRelated[0xB5] != 0) {
        removeCurrentDrawingItem();
    } else {
        addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_E21C);
        if (lbl_3_common_bss_37400.scoutResult == 1) {
            REC(scene, 0)->elementIndex = 0x5A;
        }
        animRelated[0xB5] = 1;
        currentDrawingItem->func = fn_3_951B4;
    }
}

// .text:0x000951B4 size:0x128 mapped:0x806D4248
void fn_3_951B4(void) {
    HudScene* scene = (HudScene*)currentDrawingItem;

    if (g_Ball.deadBallReason == DEAD_BALL_REASON_HOME_RUN) {
        if (g_GameLogic.gameStatus == GAME_STATUS_HOMERUN_LAP) {
            REC(scene, 0)->playMode = UI_PLAY_FORWARD;
        }
        if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL || g_GameLogic.gameStatus == GAME_STATUS_HOMERUN_LAP) {
            return;
        }
    } else {
        if (g_UnkSound_32718._07 == 0 || g_GameLogic.gameStatus == GAME_STATUS_AT_BAT) {
            REC(scene, 0)->playMode = UI_PLAY_FORWARD;
        }
        if (animRelated[0x96] == 0 && lbl_3_common_bss_37400.scoutCountdown != 0 &&
            (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT || g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL)) {
            return;
        }
    }
    animRelated[0xB4] = 0;
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
}

// .text:0x00095124 size:0x90 mapped:0x806D41B8
void fn_3_95124(void) {
    HudScene* scene = (HudScene*)currentDrawingItem;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_E278);
    REC(scene, 2)->frame = lbl_3_data_E200[lbl_3_common_bss_37400.scoutMissionID] << 16;
    currentDrawingItem->func = fn_3_95098;
}

// .text:0x00095098 size:0x8C mapped:0x806D412C
void fn_3_95098(void) {
    HudScene* scene = (HudScene*)currentDrawingItem;

    if (animRelated[0x96] != 0 || REC(scene, 0)->unk69[0] == 2) {
        insertGraphicDrawingFunction(scoutMissionBanner_init, 2);
        animRelated[0xB3] = 0;
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    }
}

// .text:0x00095000 size:0x98 mapped:0x806D4094
void scoutMissionBanner_init(void) {
    HudScene* scene = (HudScene*)currentDrawingItem;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_E2F8);
    REC(scene, 2)->frame = lbl_3_data_E200[lbl_3_common_bss_37400.scoutMissionID] << 16;
    scene->unk1C = lbl_3_common_bss_37400.scoutMissionID;
    currentDrawingItem->func = fn_3_94E68;
}

// .text:0x00094E68 size:0x198 mapped:0x806D3EFC
void fn_3_94E68(void) {
    HudScene* scene = (HudScene*)currentDrawingItem;

    if (!(animRelated[0x96] != 0 ||
          (scene->unk1C != lbl_3_common_bss_37400.scoutMissionID && lbl_3_common_bss_37400.scoutResult != 2) ||
          g_GameLogic.gameStatus == GAME_STATUS_INNING_TRANSITION ||
          (g_GameLogic.gameStatus == GAME_STATUS_TRANSITION && lbl_3_common_bss_37400.scoutResult != 0) ||
          (g_GameLogic.gameStatus == GAME_STATUS_DEFAULT && lbl_3_common_bss_37400.scoutResult == 2))) {
        if (g_Stats.replayInd != 0) {
            REC(scene, 0)->flags &= ~UI_FLAG_VISIBLE;
            REC(scene, 1)->flags &= ~UI_FLAG_VISIBLE;
        } else if (g_GameLogic.gameStatus <= GAME_STATUS_AT_BAT || g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL) {
            REC(scene, 0)->flags |= UI_FLAG_VISIBLE;
            REC(scene, 1)->flags |= UI_FLAG_VISIBLE;
        } else {
            REC(scene, 0)->flags &= ~UI_FLAG_VISIBLE;
            REC(scene, 1)->flags &= ~UI_FLAG_VISIBLE;
        }
    } else {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    }
}

// .text:0x00094BC4 size:0x2A4 mapped:0x806D3C58
void scoutMissionProgress_init(void) {
    HudScene* scene = (HudScene*)currentDrawingItem;
    HudScoutEntry* entry;
    int i;
    int k;
    int shown;

    if (animRelated[0xB4] != 0) {
        scene->unk1C = 2;
    } else if (g_GameLogic.gameStatus == GAME_STATUS_STAR_CHANCE_VS) {
        scene->unk1C = 1;
    } else {
        scene->unk1C = 0;
    }
    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_E378);
    shown = 0;
    entry = lbl_3_common_bss_37400.entries;
    for (i = 0; i < 9; i++, entry++) {
        if (entry->active != 0) {
            int base = lbl_3_data_E758[shown];

            REC(scene, base)->frame = entry->trackerIdx << 16;
            for (k = 0; k < 5; k++) {
                int slot = base + (k + 1);

                if (k >= entry->max) {
                    REC(scene, slot)->flags &= ~UI_FLAG_VISIBLE;
                } else {
                    REC(scene, slot)->flags |= UI_FLAG_VISIBLE;
                    REC(scene, slot)->playMode = UI_PLAY_STOP;
                    REC(scene, slot)->frame = 0;
                    if (k < entry->achieved) {
                        REC(scene, slot)->frame = 1 << 16;
                    } else if (k < entry->achieved + entry->amount) {
                        if (scene->unk1C == 2) {
                            REC(scene, slot)->frame = 40 << 16;
                        } else {
                            REC(scene, slot)->frame = 60 << 16;
                        }
                        REC(scene, slot)->playMode = UI_PLAY_FORWARD;
                    }
                }
            }
            shown++;
        }
    }
    if (shown < 0) {
        removeCurrentDrawingItem();
    } else {
        REC(scene, 1)->frame = (shown - 1) << 16;
        scene->unk1A = shown;
        currentDrawingItem->func = scoutMissionProgress_update;
    }
}

// .text:0x0009497C size:0x248 mapped:0x806D3A10
void scoutMissionProgress_update(void) {
    HudScene* scene = (HudScene*)currentDrawingItem;
    int i;
    int k;

    if (animRelated[0x96] == 0) {
        if (g_UnkSound_32718._07 == 0 || g_GameLogic.gameStatus == GAME_STATUS_AT_BAT) {
            REC(scene, 0)->playMode = UI_PLAY_FORWARD;
            REC(scene, 2)->playMode = UI_PLAY_FORWARD;
            REC(scene, 3)->playMode = UI_PLAY_FORWARD;
            REC(scene, 4)->playMode = UI_PLAY_FORWARD;
            REC(scene, 5)->playMode = UI_PLAY_FORWARD;
        }
        if (scene->unk1C == 2) {
            if (animRelated[0xB4] == 0) {
                goto remove;
            }
        } else if (scene->unk1C != 0) {
            if (g_GameLogic.gameStatus != GAME_STATUS_STAR_CHANCE_VS) {
                goto remove;
            }
        } else if (animRelated[0xB3] == 0) {
            goto remove;
        }
        if (scene->unk1C != 2) {
            for (i = 0; i < scene->unk1A; i++) {
                for (k = 1; k <= 5; k++) {
                    UIRecord* rec = (UIRecord*)graphicsRelatedArray[lbl_3_data_E758[i] + scene->firstHandle + k].object;

                    if ((rec->frame >> 16) > 40) {
                        rec->frame = 60 << 16;
                    }
                }
            }
        }
        return;
    }
remove:
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
}

// .text:0x00094930 size:0x4C mapped:0x806D39C4
void fn_3_94930(void) {
    addGraphicsElementToScene(currentDrawingItem, lbl_3_data_F3F0);
    currentDrawingItem->func = fn_3_948B8;
}

// .text:0x000948B8 size:0x78 mapped:0x806D394C
void fn_3_948B8(void) {
    HudScene* scene = (HudScene*)currentDrawingItem;

    if (animRelated[0x96] != 0 || g_GameLogic.gameStatus != GAME_STATUS_CHAMPIONSHIP || REC(scene, 0)->unk69[0] == 2) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    }
}

// .text:0x00094760 size:0x158 mapped:0x806D37F4
void fn_3_94760(void) {
    HudScene* scene = (HudScene*)currentDrawingItem;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_E75C);
    REC(scene, 3)->elementIndex = lbl_3_data_F430[g_GameLogic.logo[0].captain][1];
    REC(scene, 4)->elementIndex = lbl_3_data_F430[g_GameLogic.logo[1].captain][1];
    REC(scene, 3)->frame = g_GameLogic.logo[0].variationID << 16;
    REC(scene, 4)->frame = g_GameLogic.logo[1].variationID << 16;
    load_Icon(scene, 5, 1, 0x25,
              g_GameLogic.teams[g_GameLogic.homeTeamInd] + g_GameLogic.teamIsCPU[g_GameLogic.homeTeamInd] * 4);
    load_Icon(scene, 6, 1, 0x25,
              g_GameLogic.teams[g_GameLogic.homeTeamInd ^ 1] + g_GameLogic.teamIsCPU[g_GameLogic.homeTeamInd ^ 1] * 4);
    currentDrawingItem->func = fn_3_94708;
}

// .text:0x00094708 size:0x58 mapped:0x806D379C
void fn_3_94708(void) {
    DrawingSceneStruct* node = currentDrawingItem;

    if (animRelated[0x96] != 0 || g_GameLogic._125 > 9) {
        removeGraphicsElementFromScene(node);
        removeCurrentDrawingItem();
    }
}

// .text:0x00094194 size:0x574 mapped:0x806D3228
void relatedToAnimatingEndOfGame(void) {
    HudScene* scene = (HudScene*)currentDrawingItem;
    int i;
    int score;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_E85C);
    if (g_Scores.scores[0].total == g_Scores.scores[1].total) {
        REC(scene, 9)->elementIndex = 0xE6;
    }
    if (g_GameLogic.winType != WIN_TYPE_5 && g_GameLogic.winType != WIN_TYPE_6) {
        REC(scene, 17)->flags &= ~UI_FLAG_VISIBLE;
    }
    for (i = 0; i < 3; i++) {
        REC_AT(scene, 3, i)->elementIndex = lbl_3_data_F430[g_GameLogic.logo[0].captain][1];
        REC_AT(scene, 6, i)->elementIndex = lbl_3_data_F430[g_GameLogic.logo[1].captain][1];
        REC_AT(scene, 3, i)->frame = g_GameLogic.logo[0].variationID << 16;
        REC_AT(scene, 6, i)->frame = g_GameLogic.logo[1].variationID << 16;
    }

    if (g_Scores.scores[0].total < 10) {
        REC(scene, 10)->flags &= ~UI_FLAG_VISIBLE;
        load_Icon(scene, 0xB, 1, 0xF6, g_Scores.scores[0].total);
    } else {
        score = g_Scores.scores[0].total;
        if (score > 99) {
            score = 99;
        }
        load_Icon(scene, 0xA, 1, 0xF6, score / 10);
        load_Icon(scene, 0xB, 1, 0xF6, score % 10);
    }

    if (g_Scores.scores[1].total < 10) {
        if (g_GameLogic.winType == WIN_TYPE_3 || g_GameLogic.winType == WIN_TYPE_6) {
            load_Icon(scene, 0xC, 1, 0xF6, g_Scores.scores[1].total);
            load_Icon(scene, 0xD, 1, 0xF6, 10);
        } else {
            load_Icon(scene, 0xC, 1, 0xF6, g_Scores.scores[1].total);
            REC(scene, 13)->flags &= ~UI_FLAG_VISIBLE;
        }
    } else {
        score = g_Scores.scores[1].total;
        if (score > 99) {
            score = 99;
        }
        load_Icon(scene, 0xC, 1, 0xF6, score / 10);
        load_Icon(scene, 0xD, 1, 0xF6, score % 10);
    }

    if (g_Scores.winnerCd == 0) {
        REC(scene, 1)->elementIndex = 0xEC;
        REC(scene, 2)->elementIndex = 0xE9;
        REC(scene, 15)->flags &= ~UI_FLAG_VISIBLE;
        REC(scene, 4)->flags |= UI_FLAG_VISIBLE;
        REC(scene, 5)->flags |= UI_FLAG_VISIBLE;
    } else if (g_Scores.winnerCd == 1) {
        REC(scene, 1)->elementIndex = 0xE8;
        REC(scene, 2)->elementIndex = 0xED;
        REC(scene, 16)->flags &= ~UI_FLAG_VISIBLE;
        REC(scene, 7)->flags |= UI_FLAG_VISIBLE;
        REC(scene, 8)->flags |= UI_FLAG_VISIBLE;
    } else {
        for (i = 10; i < 14; i++) {
            REC(scene, i)->elementIndex = 0xEA;
        }
        REC(scene, 1)->elementIndex = 0xE3;
        REC(scene, 2)->elementIndex = 0xE4;
        REC(scene, 14)->flags &= ~UI_FLAG_VISIBLE;
        REC(scene, 15)->flags &= ~UI_FLAG_VISIBLE;
        REC(scene, 16)->flags &= ~UI_FLAG_VISIBLE;
    }
    currentDrawingItem->func = fn_3_9413C;
}

// .text:0x0009413C size:0x58 mapped:0x806D31D0
void fn_3_9413C(void) {
    DrawingSceneStruct* node = currentDrawingItem;

    if (animRelated[0x96] != 0 || g_GameLogic.gameStatus != GAME_STATUS_END_OF_GAME) {
        removeGraphicsElementFromScene(node);
        removeCurrentDrawingItem();
    }
}

// .text:0x00093D5C size:0x3E0 mapped:0x806D2DF0
void graphics_ShowScoreUpdateOnRBI_initial(void) {
    HudScene* scene = (HudScene*)currentDrawingItem;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_EABC);
    REC(scene, 2)->elementIndex = lbl_3_data_F430[g_GameLogic.logo[0].captain][1];
    REC(scene, 3)->elementIndex = lbl_3_data_F430[g_GameLogic.logo[1].captain][1];
    REC(scene, 2)->frame = g_GameLogic.logo[0].variationID << 16;
    REC(scene, 3)->frame = g_GameLogic.logo[1].variationID << 16;
    REC(scene, 4)->frame = 0 << 16;
    REC(scene, 5)->frame = 1 << 16;
    REC(scene, 6)->frame = 2 << 16;
    REC(scene, 7)->frame = 3 << 16;
    REC(scene, 8)->frame = 4 << 16;
    REC(scene, 9)->frame = 5 << 16;

    updateRBIScoreDigits(scene);
    animRelated[0x98] = 1;
    scene->unk18 = 0;
    currentDrawingItem->func = graphics_ShowScoreUpdateOnRBI_ongoing;
}

// .text:0x00093960 size:0x3FC mapped:0x806D29F4
void graphics_ShowScoreUpdateOnRBI_ongoing(void) {
    HudScene* scene = (HudScene*)currentDrawingItem;

    if (animRelated[0x98] == 2) {
        animRelated[0x98] = 1;
        scene->unk18 = 0;
    }
    if (scene->unk18 < 0xFFFE) {
        scene->unk18++;
    } else {
        scene->unk18 = 0xFFFF;
    }
    if (!(animRelated[0x96] != 0 || (g_GameLogic.gameStatus == GAME_STATUS_INNING_TRANSITION && g_GameLogic._125 == 9) ||
        (g_GameLogic.gameStatus == GAME_STATUS_END_OF_GAME && g_GameLogic._125 == 4) ||
        (g_GameLogic.gameStatus == GAME_STATUS_GAME_START_MOVIE && (g_GameLogic._125 == 0xA || g_GameLogic._125 == 0xB)) ||
        ((g_UnkSound_32718._07 == 7 || g_UnkSound_32718._07 == 0x14) && scene->unk18 > 30) ||
        g_GameLogic.gameStatus == GAME_STATUS_TRANSITION || g_GameLogic.gameStatus == GAME_STATUS_TRANSITION_TO_MINIGAME_START ||
        (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL && scene->unk18 > 90))) {
        updateRBIScoreDigits(scene);
    } else {
        animRelated[0x98] = 0;
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    }
}

// .text:0x00093688 size:0x2D8 mapped:0x806D271C
void updateRBIScoreDigits(HudScene* scene) {
    int score;

    if (g_Scores.scores[0].total >= 10) {
        score = g_Scores.scores[0].total;
        if (score >= 99) {
            score = 99;
        }
        REC(scene, 4)->flags &= ~UI_FLAG_VISIBLE;
        REC(scene, 5)->flags |= UI_FLAG_VISIBLE;
        REC(scene, 6)->flags |= UI_FLAG_VISIBLE;
        setIndicatorSlotState((DrawingSceneStruct*)scene, 5, 2, 0xF6, score / 10);
        setIndicatorSlotState((DrawingSceneStruct*)scene, 6, 3, 0xF6, score % 10);
    } else {
        REC(scene, 4)->flags |= UI_FLAG_VISIBLE;
        REC(scene, 5)->flags &= ~UI_FLAG_VISIBLE;
        REC(scene, 6)->flags &= ~UI_FLAG_VISIBLE;
        setIndicatorSlotState((DrawingSceneStruct*)scene, 4, 1, 0xF6, g_Scores.scores[0].total);
    }

    score = g_Scores.scores[1].total;
    if (score >= 10) {
        if (score >= 99) {
            score = 99;
        }
        REC(scene, 7)->flags &= ~UI_FLAG_VISIBLE;
        REC(scene, 8)->flags |= UI_FLAG_VISIBLE;
        REC(scene, 9)->flags |= UI_FLAG_VISIBLE;
        setIndicatorSlotState((DrawingSceneStruct*)scene, 8, 5, 0xF6, score / 10);
        setIndicatorSlotState((DrawingSceneStruct*)scene, 9, 6, 0xF6, score % 10);
    } else {
        REC(scene, 7)->flags |= UI_FLAG_VISIBLE;
        REC(scene, 8)->flags &= ~UI_FLAG_VISIBLE;
        REC(scene, 9)->flags &= ~UI_FLAG_VISIBLE;
        setIndicatorSlotState((DrawingSceneStruct*)scene, 7, 4, 0xF6, g_Scores.scores[1].total);
    }
}

// .text:0x00093544 size:0x144 mapped:0x806D25D8
void homeRunScoreTicker_init(void) {
    HudDigitScene* scene = (HudDigitScene*)currentDrawingItem;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_EC1C);
    REC(scene, 1)->elementIndex = lbl_3_data_F430[g_GameLogic.logo[0].captain][1];
    REC(scene, 2)->elementIndex = lbl_3_data_F430[g_GameLogic.logo[1].captain][1];
    REC(scene, 1)->frame = g_GameLogic.logo[0].variationID << 16;
    REC(scene, 2)->frame = g_GameLogic.logo[1].variationID << 16;
    if (g_GameLogic.homeTeamBattingInd_fieldingTeam == 0) {
        SHOWN(scene, 0) = g_Scores._A0;
        SHOWN(scene, 1) = g_Scores.scores[1].total;
    } else {
        SHOWN(scene, 0) = g_Scores.scores[0].total;
        SHOWN(scene, 1) = g_Scores._A0;
    }
    TARGET(scene, 0) = SHOWN(scene, 0);
    TARGET(scene, 1) = SHOWN(scene, 1);
    scoreTicker_update(scene);
    scene->frameCount = 0;
    scene->settled = 0;
    currentDrawingItem->func = homeRunScoreTicker_update;
}

// .text:0x000933CC size:0x178 mapped:0x806D2460
void homeRunScoreTicker_update(void) {
    HudDigitScene* scene = (HudDigitScene*)currentDrawingItem;

    if (scene->frameCount < 0xFFFE) {
        scene->frameCount++;
    } else {
        scene->frameCount = 0xFFFF;
    }
    if (animRelated[0x96] == 0 && g_GameLogic.gameStatus == GAME_STATUS_HOMERUN_END) {
        scoreTicker_update(scene);
        if (scene->settled == 0 && (REC(scene, 0)->frame >> 16) >= 21) {
            REC(scene, 0)->playMode = UI_PLAY_STOP;
            REC(scene, 3)->playMode = UI_PLAY_STOP;
            REC(scene, 4)->playMode = UI_PLAY_STOP;
            scene->settled = 1;
        }
        if (scene->frameCount >= 30 && (scene->frameCount - 30) % 27 == 0) {
            int team = g_GameLogic.homeTeamBattingInd_fieldingTeam;

            if (TARGET(scene, team) < g_Scores.scores[team].total) {
                TARGET(scene, team)++;
            }
        }
    } else {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        animRelated[0xC5] = 0;
    }
}

// .text:0x00092CD8 size:0x6F4 mapped:0x806D1D6C
void scoreTicker_update(HudDigitScene* scene) {
    int i;
    int t;
    int firstDigit;
    int secondDigit;
    int done;

    for (i = 0; i < 4; i++) {
        if (scene->counts[i] >= 100) {
            scene->counts[i] = 99;
        }
    }
    if (scene->settled == 0) {
        if ((REC(scene, 11)->frame >> 16) >= 20 || (REC(scene, 12)->frame >> 16) >= 20) {
            for (i = 11; i < 17; i++) {
                REC(scene, i)->playMode = UI_PLAY_STOP;
                REC(scene, i)->frame = 20 << 16;
            }
        }
    }
    for (t = 0; t < 2; t++) {
        if (t == 0) {
            firstDigit = 11;
            secondDigit = 5;
        } else {
            firstDigit = 14;
            secondDigit = 8;
        }
        if (TARGET(scene, t) == SHOWN(scene, t)) {
            if (SHOWN(scene, t) < 10) {
                REC_AT(scene, firstDigit, 1)->flags &= ~UI_FLAG_VISIBLE;
                REC_AT(scene, firstDigit, 2)->flags &= ~UI_FLAG_VISIBLE;
                REC(scene, firstDigit)->flags |= UI_FLAG_VISIBLE;
                load_Icon(scene, firstDigit, 1, 0xF6, SHOWN(scene, t));
            } else {
                REC(scene, firstDigit)->flags &= ~UI_FLAG_VISIBLE;
                REC_AT(scene, firstDigit, 1)->flags |= UI_FLAG_VISIBLE;
                REC_AT(scene, firstDigit, 2)->flags |= UI_FLAG_VISIBLE;
                load_Icon(scene, firstDigit + 1, 1, 0xF6, SHOWN(scene, t) / 10);
                load_Icon(scene, firstDigit + 2, 1, 0xF6, SHOWN(scene, t) % 10);
            }
            REC(scene, firstDigit)->frame = 20 << 16;
            REC(scene, secondDigit)->frame = 45 << 16;
            REC(scene, secondDigit)->flags &= ~UI_FLAG_VISIBLE;
            REC(scene, firstDigit + 1)->frame = 20 << 16;
            REC(scene, secondDigit + 1)->frame = 45 << 16;
            REC(scene, secondDigit + 1)->flags &= ~UI_FLAG_VISIBLE;
            REC(scene, firstDigit + 2)->frame = 20 << 16;
            REC(scene, secondDigit + 2)->frame = 45 << 16;
            REC(scene, secondDigit + 2)->flags &= ~UI_FLAG_VISIBLE;
        } else {
            done = 0;
            if (SHOWN(scene, t) < 10) {
                REC(scene, firstDigit)->playMode = UI_PLAY_FORWARD;
                if ((int)(REC(scene, firstDigit)->frame >> 16) >= 45) {
                    REC(scene, firstDigit)->playMode = UI_PLAY_STOP;
                    done = 1;
                }
            } else {
                REC_AT(scene, firstDigit, 1)->playMode = UI_PLAY_FORWARD;
                REC_AT(scene, firstDigit, 2)->playMode = UI_PLAY_FORWARD;
                if ((REC_AT(scene, firstDigit, 1)->frame >> 16) >= 45) {
                    done = 1;
                    REC_AT(scene, firstDigit, 1)->playMode = UI_PLAY_STOP;
                    REC_AT(scene, firstDigit, 2)->playMode = UI_PLAY_STOP;
                }
            }
            if (TARGET(scene, t) < 10) {
                REC(scene, secondDigit)->flags |= UI_FLAG_VISIBLE;
                REC(scene, secondDigit)->playMode = UI_PLAY_FORWARD;
                load_Icon(scene, secondDigit, 1, 0xF6, TARGET(scene, t));
                if ((REC(scene, secondDigit)->frame >> 16) >= 70) {
                    REC(scene, secondDigit)->playMode = UI_PLAY_STOP;
                    done++;
                }
            } else {
                REC_AT(scene, secondDigit, 1)->flags |= UI_FLAG_VISIBLE;
                REC_AT(scene, secondDigit, 2)->flags |= UI_FLAG_VISIBLE;
                REC_AT(scene, secondDigit, 1)->playMode = UI_PLAY_FORWARD;
                REC_AT(scene, secondDigit, 2)->playMode = UI_PLAY_FORWARD;
                load_Icon(scene, secondDigit + 1, 1, 0xF6, TARGET(scene, t) / 10);
                load_Icon(scene, secondDigit + 2, 1, 0xF6, TARGET(scene, t) % 10);
                if ((REC_AT(scene, secondDigit, 1)->frame >> 16) >= 70) {
                    done++;
                    REC_AT(scene, secondDigit, 1)->playMode = UI_PLAY_STOP;
                    REC_AT(scene, secondDigit, 2)->playMode = UI_PLAY_STOP;
                }
            }
            if (done >= 2) {
                SHOWN(scene, t) = TARGET(scene, t);
            }
        }
    }
}

// .text:0x00091FC4 size:0xD14 mapped:0x806D1058
static inline void showInningColumn(HudScene* scene, int col, int inning) {
    HudEventData* data = &lbl_3_data_8D88;
    int runs;

    REC(scene, col - 1 + 6)->flags |= UI_FLAG_VISIBLE;
    runs = g_Scores.scores[0].byInning[inning - 1];
    if (runs >= 99) {
        runs = 99;
    }
    if (runs < 10) {
        REC(scene, col - 1 + 6)->elementIndex = data->digitElement;
        load_Icon(scene, col + 5, 1, 0xC4, runs);
    } else {
        load_Icon(scene, col + 5, 2, 0xC4, runs % 10);
        load_Icon(scene, col + 5, 1, 0xC4, runs / 10);
    }
    if (inning < animRelated[0xCF] || (inning == animRelated[0xCF] && animRelated[0xD0] != 0)) {
        REC(scene, col - 1 + 0x11)->flags |= UI_FLAG_VISIBLE;
        runs = g_Scores.scores[1].byInning[inning - 1];
        if (runs >= 99) {
            runs = 99;
        }
        if (runs < 10) {
            if (inning >= g_Scores.Inning && (g_GameLogic.winType == WIN_TYPE_3 || g_GameLogic.winType == WIN_TYPE_6)) {
                load_Icon(scene, col + 0x10, 2, 0xC4, 0xB);
                load_Icon(scene, col + 0x10, 1, 0xC4, runs);
            } else {
                REC(scene, col - 1 + 0x11)->elementIndex = data->digitElement;
                load_Icon(scene, col + 0x10, 1, 0xC4, runs);
            }
        } else {
            load_Icon(scene, col + 0x10, 2, 0xC4, runs % 10);
            load_Icon(scene, col + 0x10, 1, 0xC4, runs / 10);
        }
    } else if (g_GameLogic.gameStatus == GAME_STATUS_MVP_END_GAME) {
        REC(scene, col - 1 + 0x11)->flags |= UI_FLAG_VISIBLE;
        REC(scene, col - 1 + 0x11)->elementIndex = data->digitElement;
        load_Icon(scene, col + 0x10, 1, 0xC4, 10);
    }
}

void manageScoreboardGraphic(void) {
    HudScene* scene = (HudScene*)currentDrawingItem;
    HudEventData* data = &lbl_3_data_8D88;
    BOOL wideBoard = FALSE;
    int score;
    int i;
    int col;
    int inning;

    if (animRelated[0xCF] == 12) {
        data->scoreboardDescriptors[0].elementIndex = 0xC9;
        wideBoard = TRUE;
        data->scoreboardDescriptors[1].elementIndex = 0xC1;
    } else if (animRelated[0xCF] == 11) {
        data->scoreboardDescriptors[0].elementIndex = 0xC8;
        wideBoard = TRUE;
        data->scoreboardDescriptors[1].elementIndex = 0xC1;
    } else if (animRelated[0xCF] == 10) {
        data->scoreboardDescriptors[0].elementIndex = 0xC7;
        wideBoard = TRUE;
        data->scoreboardDescriptors[1].elementIndex = 0xC1;
    } else if (animRelated[0xCF] > 5 || g_Scores.inningLimit > 5) {
        data->scoreboardDescriptors[0].elementIndex = 0xC6;
        wideBoard = TRUE;
        data->scoreboardDescriptors[1].elementIndex = 0xC1;
    } else {
        data->scoreboardDescriptors[0].elementIndex = 0xCA;
        data->scoreboardDescriptors[1].elementIndex = 0xC5;
    }
    addGraphicsElementToScene((DrawingSceneStruct*)scene, data->scoreboardDescriptors);
    if (wideBoard) {
        REC(scene, 2)->anchorSub = data->anchorSubs[0];
        REC(scene, 3)->anchorSub = data->anchorSubs[12];
        for (i = 0; i < 11; i++) {
            REC_AT(scene, 6, i)->anchorSub = data->anchorSubs[i + 1];
            REC_AT(scene, 0x11, i)->anchorSub = data->anchorSubs[i + 13];
        }
    }
    REC(scene, 4)->elementIndex = data->logoElements[g_GameLogic.logo[0].captain][0];
    REC(scene, 5)->elementIndex = data->logoElements[g_GameLogic.logo[1].captain][0];
    REC(scene, 4)->frame = g_GameLogic.logo[0].variationID << 16;
    REC(scene, 5)->frame = g_GameLogic.logo[1].variationID << 16;
    if (animRelated[0xCF] >= 1) {
        REC(scene, 15)->flags |= UI_FLAG_VISIBLE;
        REC(scene, 16)->flags |= UI_FLAG_VISIBLE;
        score = g_Scores.scores[0].total;
        if (score >= 99) {
            score = 99;
        }
        if (score < 10) {
            REC(scene, 15)->elementIndex = data->digitElement;
            load_Icon(scene, 0xF, 1, 0xC4, score);
        } else {
            load_Icon(scene, 0xF, 2, 0xC4, score % 10);
            load_Icon(scene, 0xF, 1, 0xC4, score / 10);
        }
        score = g_Scores.hits[0].total;
        if (score >= 99) {
            score = 99;
        }
        if (score < 10) {
            REC(scene, 16)->elementIndex = data->digitElement;
            load_Icon(scene, 0x10, 1, 0xC4, score);
        } else {
            load_Icon(scene, 0x10, 2, 0xC4, score % 10);
            load_Icon(scene, 0x10, 1, 0xC4, score / 10);
        }
    }
    if (animRelated[0xCF] >= 2 || animRelated[0xD0] != 0) {
        REC(scene, 26)->flags |= UI_FLAG_VISIBLE;
        REC(scene, 27)->flags |= UI_FLAG_VISIBLE;
        score = g_Scores.scores[1].total;
        if (score >= 99) {
            score = 99;
        }
        if (score < 10) {
            REC(scene, 26)->elementIndex = data->digitElement;
            load_Icon(scene, 0x1A, 1, 0xC4, score);
        } else {
            load_Icon(scene, 0x1A, 2, 0xC4, score % 10);
            load_Icon(scene, 0x1A, 1, 0xC4, score / 10);
        }
        score = g_Scores.hits[1].total;
        if (score >= 99) {
            score = 99;
        }
        if (score < 10) {
            REC(scene, 27)->elementIndex = data->digitElement;
            load_Icon(scene, 0x1B, 1, 0xC4, score);
        } else {
            load_Icon(scene, 0x1B, 2, 0xC4, score % 10);
            load_Icon(scene, 0x1B, 1, 0xC4, score / 10);
        }
    }
    if (animRelated[0xCF] >= 10) {
        col = 1;
        inning = 10;
        for (; col <= 9; col++, inning++) {
            int shown;

            if (inning <= animRelated[0xCF]) {
                shown = inning;
            } else {
                if (inning == animRelated[0xCF] + 1) {
                    continue;
                }
                shown = col;
            }
            showInningColumn(scene, col, shown);
        }
    } else {
        for (col = 1; col <= animRelated[0xCF]; col++) {
            showInningColumn(scene, col, col);
        }
    }
    animRelated[0xCD] = 0;
    animRelated[0xCE] = 0;
    scene->unk1A = 0;
    currentDrawingItem->func = fn_3_91E4C;
}

// .text:0x00091E4C size:0x178 mapped:0x806D0EE0
void fn_3_91E4C(void) {
    HudScene* scene = (HudScene*)currentDrawingItem;
    int i;
    int frame;

    if (animRelated[0xCD] == 0) {
        if (animRelated[0xCE] == 0) {
            return;
        }
        REC(scene, 0)->playMode = UI_PLAY_BACKWARD;
        REC(scene, 1)->playMode = UI_PLAY_BACKWARD;
        frame = REC(scene, 1)->frame >> 16;
        for (i = 0; i < 11; i++) {
            if (frame <= lbl_3_data_F200[i]) {
                if (i == 0) {
                    REC(scene, 2)->playMode = UI_PLAY_BACKWARD;
                    REC(scene, 3)->playMode = UI_PLAY_BACKWARD;
                }
                REC_AT(scene, 6, i)->playMode = UI_PLAY_BACKWARD;
                REC_AT(scene, 0x11, i)->playMode = UI_PLAY_BACKWARD;
            }
        }
        scene->unk1A++;
        if (scene->unk1A < 45) {
            return;
        }
    }
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
    if (g_GameLogic.gameStatus == GAME_STATUS_INNING_TRANSITION) {
        menuNumber[0x26] = 1;
    }
}

// .text:0x00091D1C size:0x130 mapped:0x806D0DB0
void fn_3_91D1C(void) {
    HudScene* scene = (HudScene*)currentDrawingItem;
    int i;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_F224);
    REC(scene, 3)->elementIndex = lbl_3_data_F344[g_d_GameSettings.StadiumID];
    for (i = 0; i < 3; i++) {
        int slot = g_GameLogic.currentBatterPerTeam[g_GameLogic.awayTeamBattingInd_battingTeam] + i;

        if (slot > 9) {
            slot -= 9;
        }
        REC_AT(scene, 5, i)->frame =
            inMemRoster[g_GameLogic.teamFielding]
                       [g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][slot][0]]
                           .stats.CharID
            << 16;
    }
    load_Icon(scene, 1, 4, 7, g_d_GameSettings.StadiumID);
    currentDrawingItem->func = fn_3_91CCC;
}

// .text:0x00091CCC size:0x50 mapped:0x806D0D60
void fn_3_91CCC(void) {
    DrawingSceneStruct* node = currentDrawingItem;

    if (animRelated[0x96] != 0 || animRelated[0xCD] != 0) {
        removeGraphicsElementFromScene(node);
        removeCurrentDrawingItem();
    }
}

// .text:0x00091C70 size:0x5C mapped:0x806D0D04
void fn_3_91C70(void) {
    addGraphicsElementToScene(currentDrawingItem, lbl_3_data_F390);
    animRelated[0xB0] = 1;
    currentDrawingItem->func = animateScreenRelated;
}

// .text:0x00091B9C size:0xD4 mapped:0x806D0C30
void animateScreenRelated(void) {
    HudScene* scene = (HudScene*)currentDrawingItem;

    if (animRelated[0x96] == 0) {
        if ((REC(scene, 0)->frame >> 16) >= 75) {
            REC(scene, 1)->flags |= UI_FLAG_VISIBLE;
        }
        if ((g_Stats.replayInd != 0 || g_Stats.replayPending != 0) && g_GameLogic.gameStatus != GAME_STATUS_INNING_TRANSITION &&
            g_GameLogic.gameStatus != GAME_STATUS_PAUSED && g_GameLogic.gameStatus != GAME_STATUS_MVP_END_GAME) {
            return;
        }
    }
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
    animRelated[0xB0] = 0;
    animRelated[0xB1] = 0;
}

// .text:0x00091B50 size:0x4C mapped:0x806D0BE4
void fn_3_91B50(void) {
    addGraphicsElementToScene(currentDrawingItem, lbl_3_data_F350);
    currentDrawingItem->func = fn_3_91AC8;
}

// .text:0x00091AC8 size:0x88 mapped:0x806D0B5C
void fn_3_91AC8(void) {
    DrawingSceneStruct* node = currentDrawingItem;

    if (animRelated[0x96] == 0 && g_Stats.replayInd == 0 &&
        (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL || g_GameLogic.gameStatus == GAME_STATUS_AT_BAT)) {
        return;
    }
    removeGraphicsElementFromScene(node);
    removeCurrentDrawingItem();
    animRelated[0xB2] = 0;
}

// .text:0x00091A60 size:0x68 mapped:0x806D0AF4
void ballLandingMarker_init(void) {
    HudScene* scene = (HudScene*)currentDrawingItem;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_BF6C);
    scene->unk18 = 0;
    scene->unk1C = 0;
    scene->unk1E = 0;
    scene->unk20 = 0;
    currentDrawingItem->func = ballLandingMarker_update;
}

// .text:0x00091520 size:0x540 mapped:0x806D05B4
void ballLandingMarker_update(void) {
    HudScene* scene = (HudScene*)currentDrawingItem;
    int x;
    int y;

    if (animRelated[0x96] == 0) {
        if (scene->unk18 < 0xFFFE) {
            scene->unk18++;
        } else {
            scene->unk18 = 0xFFFF;
        }
        if (g_UnkSound_32718._08 != 0) {
            if (g_Stats.replayInd != 0) {
                g_UnkSound_32718._08 = 0;
                return;
            }
            if (g_GameLogic.framesOfExitingToMenu != 0) {
                g_UnkSound_32718._08 = 0;
                return;
            }
            fn_3_1650C(&x, &y, FALSE, g_Ball.AtBat_Contact_BallPos.x, -g_Ball.AtBat_Contact_BallPos.y,
                       g_Ball.AtBat_Contact_BallPos.z);
            switch (g_UnkSound_32718._08) {
            case 1:
                if (scene->unk1C == 0) {
                    REC(scene, 0)->frame = 0;
                    REC(scene, 0)->flags |= UI_FLAG_VISIBLE;
                    REC(scene, 0)->playMode = UI_PLAY_FORWARD;
                    REC(scene, 0)->pos.x = x;
                    REC(scene, 0)->pos.y = y;
                    scene->unk1C = 1;
                }
                break;
            case 2:
                if (scene->unk1E == 0) {
                    REC(scene, 1)->frame = 0;
                    REC(scene, 1)->flags |= UI_FLAG_VISIBLE;
                    REC(scene, 1)->playMode = UI_PLAY_FORWARD;
                    REC(scene, 1)->elementIndex = 1;
                    REC(scene, 1)->pos.x = x;
                    REC(scene, 1)->pos.y = y;
                    scene->unk1E = 1;
                }
                break;
            case 3:
                if (scene->unk1E == 0) {
                    REC(scene, 1)->frame = 0;
                    REC(scene, 1)->flags |= UI_FLAG_VISIBLE;
                    REC(scene, 1)->playMode = UI_PLAY_FORWARD;
                    REC(scene, 1)->elementIndex = 2;
                    REC(scene, 1)->pos.x = x;
                    REC(scene, 1)->pos.y = y;
                    scene->unk1E = 1;
                }
                break;
            case 4:
                if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                    g_UnkSound_32718._08 = 0;
                    return;
                }
                if (scene->unk20 == 0) {
                    REC(scene, 2)->frame = 0;
                    REC(scene, 2)->flags |= UI_FLAG_VISIBLE;
                    REC(scene, 2)->playMode = UI_PLAY_STOP;
                    REC(scene, 2)->pos.x = 0.0f;
                    REC(scene, 2)->pos.y = 0.0f;
                    scene->unk20 = 1;
                }
                break;
            }
            scene->unk18 = 0;
            g_UnkSound_32718._08 = 0;
        } else {
            if (scene->unk1C != 0 && REC(scene, 0)->unk69[0] == 2) {
                REC(scene, 0)->flags &= ~UI_FLAG_VISIBLE;
                scene->unk1C = 0;
            }
            if (scene->unk1E != 0) {
                if (REC(scene, 1)->unk69[0] == 2) {
                    REC(scene, 1)->flags &= ~UI_FLAG_VISIBLE;
                    scene->unk1E = 0;
                }
            }
            if (scene->unk20 != 0) {
                if (scene->unk18 == 30) {
                    playSoundEffect(0x1AC);
                    REC(scene, 2)->playMode = UI_PLAY_FORWARD;
                }
                if (REC(scene, 2)->unk69[0] == 2) {
                    REC(scene, 2)->flags &= ~UI_FLAG_VISIBLE;
                    scene->unk20 = 0;
                }
            }
        }
    } else {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    }
}
