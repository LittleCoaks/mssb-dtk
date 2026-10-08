#define SQRT2_LINKAGE static
#define REP_HEADER_DATA_FN getRepHeaderData_rep3448
#include "game/hud/rep_3448.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "text/text_channel.h"
#include "Unknown/File_0x80034cec.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x800b0a14.h"
#include "Unknown/File_0x800363d8.h"
#include "static/UnknownHomes_Static.h"
#include "Unknown/File_0x80021410.h"
#include "game/camera/camera.h"
#include "musyx/musyx.h"
#include "game/sound/m_sound.h"
#include "game/math/game_math.h"
#include "Dolphin/stl.h"
#include "Unknown/File_0x8004cc18.h"
#include "game/match_setup/match_scene.h"
#include "game/hud/hud_gauges.h"
#include "Unknown/File_0x8004e5b4.h"
#include "text/text_block.h"
#include "game/batting/at_bat_results.h"
#include "Unknown/File_0x8003649c.h"

extern u8 animRelated[0x124];
extern u8 pauseControl[0x264];
extern u8 lbl_800EFBA4[];
extern UIRecordDescriptor lbl_3_data_25344[];
extern UIRecordDescriptor lbl_3_data_24E04[];
extern UIRecordDescriptor lbl_3_data_91BC[];
extern UIRecordDescriptor lbl_3_data_A9F8[];
extern UIRecordDescriptor lbl_3_data_B0E0[];
extern u16 lbl_3_data_B140[][2];
extern UIRecordDescriptor lbl_3_data_AAB0[];
extern u16 lbl_3_data_B010[8][5];
extern u16 lbl_3_data_B0D8[];
extern s16 bOD_challenge_nPitches_Points[4][2];
extern s16 bB_challengePointsRequired[4];
extern s8 lbl_3_data_B060[][3][5];
extern struct {
    u8 _0[8];
    u16 label;
    u8 _A[6];
} lbl_800FEF70[];

#define MG_BYTE(off) (((u8*)&g_Minigame)[off])
#define SET_MENU(id)                                              \
    menuNumber[0] = (id);                                         \
    menuNumber[9] = menuNumber[8];                                \
    menuNumber[8] = lbl_800FEF70[(id)].label

extern u16 stadiumHazardSoundIDs[16];
extern u8 stadiumHazardSoundFxRelated[0xB4];
extern u8 lbl_3_data_84B8[];

typedef struct {
    s32 score;
    s16 count;
    s16 rank;
} ResultEntry;

extern ResultEntry* fn_3_109D88(void);

typedef struct {
    s16 v[6];
    u8 slot[6];
    u8 iconId;
    u8 count;
} ToyResultsIn;

extern void fn_3_10754C(ToyResultsIn* in);
extern void fn_8006C2B4(s16* out, ToyResultsIn* in);
extern int fn_8006C268(s16* out);
extern int fn_8006C100(s16 score);

static inline void toyPlaySound(int sfx, int slot) {
    int stadiumID = g_d_GameSettings.StadiumID;
    SND_VOICEID voice = sndFXStartEx(stadiumHazardSoundIDs[stadiumID] + sfx,
                                     g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                                         ? lbl_3_data_84B8[slot]
                                         : stadiumHazardSoundFxRelated[stadiumID * 0x1E + slot],
                                     0x3F, 0);
    sndFXCtrl(voice, 0x5B,
              g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                  ? lbl_3_data_84B8[slot + 1]
                  : stadiumHazardSoundFxRelated[stadiumID * 0x1E + slot + 1]);
}

extern u16 lbl_3_data_AA98[];
extern s16 barrelCollisionHitboxes[54];
extern u8 menuNumber[0x28];
extern u16 lbl_3_data_91FC[];
extern void fn_800362F0(DrawingSceneStruct* node, int arg);
extern UIRecordDescriptor lbl_3_data_23904[];
extern struct {
    u32 pointsToWin;
    u8 _04[2];
    s16 rank;
    u8 _08[0x20];
} lbl_803616CC[];
extern s16 lbl_80109410[];
extern UIRecordDescriptor lbl_3_data_23A44[];
extern UIRecordDescriptor lbl_3_data_23AE4[];
extern UIRecordDescriptor lbl_3_data_226E0[];
extern struct {
    u8 _00[0x28];
    u8 _28;
} lbl_80366158;
extern UIRecordDescriptor lbl_3_data_23C84[];
extern UIRecordDescriptor lbl_3_data_23D24[];
extern UIRecordDescriptor lbl_3_data_23E04[];
extern UIRecordDescriptor lbl_3_data_23DA4[];
extern s16 lbl_3_data_213EC[];
extern UIRecordDescriptor lbl_3_data_23E64[];
extern u16 lbl_3_data_2145C[];
extern UIRecordDescriptor lbl_3_data_23F24[];
extern UIRecordDescriptor lbl_3_data_23F64[];
extern u8 lbl_3_data_21460[];
extern u8 lbl_3_data_21468[];
extern u8 lbl_3_data_21480[];
extern u16 lbl_3_data_81FC[];
extern u8 lbl_3_data_84F4[];
extern UIRecordDescriptor lbl_3_data_240A4[];
extern UIRecordDescriptor lbl_3_data_246E4[];
extern UIRecordDescriptor lbl_3_data_24784[];
extern UIRecordDescriptor lbl_3_data_24844[];
extern UIRecordDescriptor lbl_3_data_24B04[];
extern s16 lbl_3_data_21788[];
extern UIRecordDescriptor lbl_3_data_24CE4[];
extern UIRecordDescriptor lbl_3_data_24D44[];
extern UIRecordDescriptor lbl_3_data_24DA4[];
extern u8 cost_15_bB_pitchesPerRound_solo[12];
extern UIRecordDescriptor lbl_3_data_23894[];
extern u16 lbl_3_data_238F4[];
extern s16 lbl_3_data_21654[];
extern s16 lbl_3_data_21672;

typedef struct {
    u8 count;
    u8 points;
} CCSGemType;
extern CCSGemType lbl_3_data_21884[];

extern int fn_3_107CD0(void);
extern int fn_3_107C88(void);
extern void fn_800528C0(f32 x, f32 y, f32 z, s16* outX, s16* outY);

extern void fn_8004D0F0(void);
extern void fn_3_E911C(void);
extern void fn_3_11DECC(void);
extern u8 lbl_8037169C[];
extern void fn_80053FE8(void);
extern void fn_80051D00(void);
extern void fn_80050F78(int arg0);
extern void mm_DrawResultCode(void);
extern void fn_3_11E364(void);
extern void fn_3_11E7C4(void);
extern void fn_3_EA454(void);
extern void fn_3_EB6E0(void);
extern UIRecordDescriptor lbl_3_data_9FB4[];
extern UIRecordDescriptor lbl_3_data_9ECC[];
extern UIRecordDescriptor lbl_3_data_92D4[];
extern UIRecordDescriptor lbl_3_data_9208[];
extern UIRecordDescriptor lbl_3_data_A598[];
extern u16 lbl_3_data_92C8[];
extern u16 lbl_3_data_A8B8[];
extern u16 lbl_3_data_A9E8[];
extern u8 lbl_3_data_21268[];
extern u16 lbl_3_data_9D4C[];
extern u16 lbl_3_data_9D48[];
extern u8 lbl_3_data_9D50[][5];
extern u8 lbl_3_data_A594[];
extern u8 superstarUnlocked[0x130];

#define MG_S16(off) (*(s16*)&MG_BYTE(off))
extern u16 lbl_3_data_93F4[][2];
extern u16 lbl_3_data_93D4[][2];
extern void fn_8000F8F4(void* node);
extern UIRecordDescriptor lbl_3_data_9D94[];
extern UIRecordDescriptor lbl_3_data_9408[];
extern u16 lbl_3_data_9D84[];
extern u16 lbl_3_data_9EB4[][2];
extern u8 lbl_3_data_9EBC[][8];

#define HUD_RECORD(scene, i) ((UIRecord*)graphicsRelatedArray[(scene)->firstHandle + (i)].object)
/* Record `i` of the group that starts at handle offset `base` within the node. */
#define HUD_RECORD_AT(scene, base, i) ((UIRecord*)graphicsRelatedArray[(scene)->firstHandle + (base) + (i)].object)
/* Record `k` past record `i` (same record as HUD_RECORD_AT(scene, k, i), different address arithmetic). */
#define HUD_RECORD_PLUS(scene, i, k) ((UIRecord*)graphicsRelatedArray[(scene)->firstHandle + (i) + (k)].object)

/* Overlay of the tables stored inside lbl_3_data_226E0 after its descriptor lists. */
typedef struct {
    u8 _0[0x420];
    u8 anchors[8];
    u16 elementIds[8];
    u16 thresholds[8];
} HudDescriptorTables;

static inline u32 hudRecordFinished(UIRecord* rec) {
    return rec->unk69[0] == 2;
}

// .text:0x0012D1F4 size:0x960
void minigameGraphics(void) {
    u8 status = g_GameLogic.gameStatus;
    DrawingSceneStruct* node;

    if (status == GAME_STATUS_MINIGAME_SELECT || (u8)(status - GAME_STATUS_TOY_STADIUM_LOAD) <= 4
        || status == GAME_STATUS_0x28) {
        fn_3_12CA90();
    } else if (status == GAME_STATUS_0x26) {
        if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_1 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 0) {
            ((MinigameHudScene*)insertGraphicDrawingFunction(fn_3_E911C, 2))->_18 = 1;
        }
    } else if (status == GAME_STATUS_0x29) {
        if (animRelated[0xD9] == 0 && g_GameLogic.framesOfExitingToMenu == 0) {
            insertGraphicDrawingFunction(fn_3_12C3F0, 2);
        }
        if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_0) {
            node = insertGraphicDrawingFunction(fn_3_11DECC, 2);
            *(DrawingSceneStruct**)((u8*)&g_Minigame + 0x1E04) = node;
        }
    } else {
        if (status == GAME_STATUS_MINIGAME_POST_MENU) {
            if (pauseControl[0x1D2] == 1) {
                insertGraphicDrawingFunction(pauseOptionList_init, 2);
            }
        } else {
            animRelated[0xDA] = 0;
        }
        if (g_GameLogic.gameStatus == GAME_STATUS_MVP_END_GAME || g_GameLogic.gameStatus == GAME_STATUS_MINIGAME_POST_MENU) {
            fn_3_129458();
        } else if (g_GameLogic.gameStatus == GAME_STATUS_0x24) {
            if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_1 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 0) {
                if (g_Minigame._1907 == 1) {
                    insertGraphicDrawingFunction(mm_DrawResultCode, 2);
                }
                node = insertGraphicDrawingFunction(fn_3_127B68, 2);
                *(DrawingSceneStruct**)((u8*)&g_Minigame + 0x1E04) = node;
            }
            if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_5 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 0) {
                insertGraphicDrawingFunction(fn_3_1274B4, 2);
            }
        } else if (g_GameLogic.gameStatus == GAME_STATUS_0x27) {
            fn_3_1293D0();
        } else if (g_GameLogic.gameStatus == GAME_STATUS_GAME_START_MOVIE) {
            if (lbl_8037169C[0x12] != 0 && g_Minigame._1E01[1] == 0) {
                insertGraphicDrawingFunction(fn_3_1254F8, 2);
            }
        }
        if (g_Minigame.pauseInd != 0) {
            if (*(s16*)&pauseControl[0xA] == 1 && animRelated[0xAA] == 0) {
                insertGraphicDrawingFunction(pauseSubPanel_init, 2);
            }
            if (pauseControl[0x1D2] == 0xA) {
                if (pauseControl[0x1D4] == 2) {
                    insertGraphicDrawingFunction(fn_3_128B90, 2);
                }
            } else if (pauseControl[0x1D2] == 0xB) {
                if (pauseControl[0x1D4] == 2) {
                    insertGraphicDrawingFunction(fn_3_126604, 2);
                }
            } else if (animRelated[0xAB] == 0) {
                insertGraphicDrawingFunction(pauseOptionList_init, 2);
            }
        }
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY) {
            fn_3_12C984();
        }
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_WALLBALL) {
            fn_3_12C868();
        }
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER) {
            fn_3_12C74C();
        }
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_CHAINCHOMP_SPRINT) {
            fn_3_12C684();
        }
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_STAR_DASH) {
            fn_3_12C5CC();
        }
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_PIRANHA_PANIC) {
            fn_3_12C514();
        }
    }
}

// .text:0x0012CA90 size:0x764
void fn_3_12CA90(void) {
    if (g_GameLogic.gameStatus >= GAME_STATUS_MINIGAME_SELECT && g_GameLogic.gameStatus <= GAME_STATUS_0x20
        && animRelated[0xD9] == 0 && g_GameLogic.framesOfExitingToMenu == 0) {
        insertGraphicDrawingFunction(fn_3_12C3F0, 2);
        insertGraphicDrawingFunction(fn_80053FE8, 2);
        if (g_Minigame._190A != 0) {
            SET_MENU(0x23);
        } else {
            SET_MENU(0x33);
        }
    }
    if (g_GameLogic.gameStatus == GAME_STATUS_MINIGAME_SELECT) {
        if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_1 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 0) {
            insertGraphicDrawingFunction(fn_3_129A18, 2);
            if (animRelated[0xBC] == 0) {
                insertGraphicDrawingFunction(fn_3_12BFE8, 2);
            }
        }
        if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_5 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
            fn_8004CC4C(0, 1, 1, 0, 0x89);
            insertGraphicDrawingFunction(fn_8004D0F0, 2);
        }
    } else if (g_GameLogic.gameStatus == GAME_STATUS_TOY_STADIUM_CHARACTER_SELECT) {
        if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_1 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 0) {
            if (animRelated[0xDC] == 0 && g_Minigame._19E0 == 0) {
                insertGraphicDrawingFunction(fn_80051D00, 2);
                animRelated[0xDC] = 1;
            }
            if (animRelated[0xDA] != 1) {
                insertGraphicDrawingFunction(fn_3_12B7A0, 2);
            }
        }
        if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_2) {
            if (animRelated[0xDC] == 0 && g_Minigame._19DE != 5 && g_Minigame._19DE != 8
                && g_Minigame._19DE != 6) {
                insertGraphicDrawingFunction(fn_80051D00, 2);
                animRelated[0xDC] = 1;
            }
            if (g_Minigame._19DE == 1 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
                insertGraphicDrawingFunction(fn_3_12A6C4, 2);
            }
            if (g_Minigame._19DE == 5 || g_Minigame._19DE == 8) {
                if (g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1 && g_Minigame._19DE == 5) {
                    fn_80050F78(0);
                    animRelated[0xDC] = 0;
                    if (g_Minigame._190A != 0) {
                        insertGraphicDrawingFunction(fn_3_129F48, 2);
                    } else {
                        insertGraphicDrawingFunction(fn_3_12A2B8, 2);
                    }
                }
                if (g_Minigame._1A3C == 0) {
                    if (g_Minigame._190A != 0) {
                        SET_MENU(0x24);
                    } else {
                        SET_MENU(0x36);
                    }
                }
            } else if (g_Minigame._19DE < 4) {
                if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                    if (g_Minigame._190A != 0) {
                        SET_MENU(0x20);
                    } else if (fn_3_9E834()) {
                        SET_MENU(0x2F);
                    } else {
                        SET_MENU(0x2E);
                    }
                } else {
                    if (g_Minigame._190A != 0) {
                        SET_MENU(0x23);
                    } else if (fn_3_9E834()) {
                        SET_MENU(0x35);
                    } else {
                        SET_MENU(0x34);
                    }
                }
            }
        }
        if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_7) {
            fn_80050F78(1);
            animRelated[0xDC] = 0;
        }
        if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_3) {
            fn_80050F78(0);
            animRelated[0xDC] = 0;
        }
    } else if (g_GameLogic.gameStatus == GAME_STATUS_MINIGAME_READY) {
        if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_2 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 0) {
            insertGraphicDrawingFunction(fn_3_126604, 2);
            if (g_Minigame._1A38 != 0 || g_Minigame._1A3C != 0) {
                insertGraphicDrawingFunction(fn_80053FE8, 2);
            }
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                if (g_Minigame._190A != 0) {
                    SET_MENU(0x22);
                } else {
                    SET_MENU(0x32);
                }
            } else {
                if (g_Minigame._190A != 0) {
                    SET_MENU(0x26);
                } else if (g_Minigame._1A3C != 0) {
                    SET_MENU(0x3B);
                } else {
                    SET_MENU(0x38);
                }
            }
            if (animRelated[0xD9] == 0) {
                insertGraphicDrawingFunction(fn_3_12C3F0, 2);
            }
        }
    } else if (g_GameLogic.gameStatus == GAME_STATUS_0x28) {
        if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_1) {
            insertGraphicDrawingFunction(fn_3_126604, 2);
            SET_MENU(0x39);
        }
    }
}

// .text:0x0012C984 size:0x10C
void fn_3_12C984(void) {
    if (animRelated[0xB6] != 0) {
        memset((u8*)&g_Minigame + 0x1DF4, 0, 0xE);
        insertGraphicDrawingFunction(fn_3_121908, 2);
        if (g_Minigame.multiPlayerInd != 0) {
            insertGraphicDrawingFunction(minigameStateLogic, 2);
        }
        insertGraphicDrawingFunction(fn_3_124738, 2);
        insertGraphicDrawingFunction(fn_3_1226D4, 2);
        insertGraphicDrawingFunction(fn_3_122334, 2);
        insertGraphicDrawingFunction(fn_3_1235B8, 2);
        insertGraphicDrawingFunction(fn_3_124CE0, 2);
        insertGraphicDrawingFunction(fn_3_EB6E0, 2);
        animRelated[0xB7] = 0;
        animRelated[0xB6] = 0;
        insertGraphicDrawingFunction(fn_3_125850, 2);
    }
    manageEventStates();
}

// .text:0x0012C868 size:0x11C
void fn_3_12C868(void) {
    if (g_GameLogic.gameStatus == GAME_STATUS_TRANSITION_MINIGAME_TO_BATTING) {
        memset((u8*)&g_Minigame + 0x1DF4, 0, 0xE);
        insertGraphicDrawingFunction(fn_3_12026C, 2);
        insertGraphicDrawingFunction(fn_3_12089C, 2);
        if (g_Minigame.multiPlayerInd == 0 && g_Minigame._1A3C == 0
            && g_Minigame.soloMinigameDifficulty == MINIGAME_DIFFICULTY_SOLO_NON_CHALLENGE) {
            insertGraphicDrawingFunction(fn_3_120FF8, 2);
        } else {
            insertGraphicDrawingFunction(minigameStateLogic, 2);
            insertGraphicDrawingFunction(fn_3_123990, 2);
        }
        insertGraphicDrawingFunction(fn_3_124CE0, 2);
        insertGraphicDrawingFunction(fn_3_121304, 2);
        animRelated[0xB7] = 0;
        animRelated[0xB6] = 0;
        insertGraphicDrawingFunction(fn_3_125850, 2);
        insertGraphicDrawingFunction(fn_3_99BDC, 2);
    }
}

// .text:0x0012C74C size:0x11C
void fn_3_12C74C(void) {
    if (animRelated[0xB6] != 0) {
        memset((u8*)&g_Minigame + 0x1DF4, 0, 0xE);
        if (g_Minigame.multiPlayerInd == 0) {
            insertGraphicDrawingFunction(fn_3_11F508, 2);
        }
        insertGraphicDrawingFunction(fn_3_11F778, 2);
        insertGraphicDrawingFunction(fn_3_11FA58, 2);
        insertGraphicDrawingFunction(fn_3_11FDB0, 2);
        if (g_Minigame.multiPlayerInd != 0) {
            insertGraphicDrawingFunction(minigameStateLogic, 2);
        }
        insertGraphicDrawingFunction(fn_3_124738, 2);
        insertGraphicDrawingFunction(fn_3_124CE0, 2);
        insertGraphicDrawingFunction(fn_3_EB6E0, 2);
        animRelated[0xB7] = 0;
        animRelated[0xB6] = 0;
        insertGraphicDrawingFunction(fn_3_125850, 2);
    }
}

// .text:0x0012C684 size:0xC8
void fn_3_12C684(void) {
    if (g_GameLogic.gameStatus == GAME_STATUS_TRANSITION_MINIGAME_TO_BATTING
        && g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_0) {
        memset((u8*)&g_Minigame + 0x1DF4, 0, 0xE);
        insertGraphicDrawingFunction(fn_3_123990, 2);
        insertGraphicDrawingFunction(fn_3_123EBC, 2);
        insertGraphicDrawingFunction(fn_3_11EC28, 2);
        insertGraphicDrawingFunction(fn_3_124CE0, 2);
        insertGraphicDrawingFunction(fn_3_11F02C, 2);
        animRelated[0xB7] = 0;
        animRelated[0xB6] = 0;
        insertGraphicDrawingFunction(fn_3_125850, 2);
    }
}

// .text:0x0012C5CC size:0xB8
void fn_3_12C5CC(void) {
    if (g_GameLogic.gameStatus == GAME_STATUS_TRANSITION_MINIGAME_TO_BATTING
        && g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_0) {
        memset((u8*)&g_Minigame + 0x1DF4, 0, 0xE);
        insertGraphicDrawingFunction(fn_3_123990, 2);
        insertGraphicDrawingFunction(fn_3_123EBC, 2);
        insertGraphicDrawingFunction(fn_3_124CE0, 2);
        insertGraphicDrawingFunction(fn_3_11E7C4, 2);
        animRelated[0xB7] = 0;
        animRelated[0xB6] = 0;
        insertGraphicDrawingFunction(fn_3_125850, 2);
    }
}

// .text:0x0012C514 size:0xB8
void fn_3_12C514(void) {
    if (g_GameLogic.gameStatus == GAME_STATUS_TRANSITION_MINIGAME_TO_BATTING
        && g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_0) {
        memset((u8*)&g_Minigame + 0x1DF4, 0, 0xE);
        insertGraphicDrawingFunction(fn_3_123990, 2);
        insertGraphicDrawingFunction(fn_3_123EBC, 2);
        insertGraphicDrawingFunction(fn_3_124CE0, 2);
        insertGraphicDrawingFunction(fn_3_11E364, 2);
        animRelated[0xB7] = 0;
        animRelated[0xB6] = 0;
        insertGraphicDrawingFunction(fn_3_125850, 2);
    }
}

// .text:0x0012C3F0 size:0x124
void fn_3_12C3F0(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    u16 element;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_9208);
    animRelated[0xD9] = 1;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        if (g_GameLogic.gameStatus == GAME_STATUS_MINIGAME_SELECT || g_GameLogic.gameStatus == GAME_STATUS_0x1B
            || g_GameLogic.gameStatus == GAME_STATUS_TOY_STADIUM_LOAD) {
            element = lbl_3_data_92C8[0];
        } else {
            element = lbl_3_data_92C8[1];
        }
    } else if (g_Practice.practiceType_1 == 6) {
        element = lbl_3_data_92C8[4];
    } else {
        element = lbl_3_data_92C8[3];
    }
    HUD_RECORD(scene, 1)->elementIndex = element;
    HUD_RECORD(scene, 1)->frame = 0x28 << 16;
    scene->state = element;
    scene->_1E = 0;
    currentDrawingItem->func = fn_3_12C1AC;
}

// .text:0x0012C1AC size:0x244
void fn_3_12C1AC(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    u16 element;
    u8 status;

    if (animRelated[0x96] != 0) {
        goto remove;
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES
        || g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        status = g_GameLogic.gameStatus;
        if (status == GAME_STATUS_GAME_START_MOVIE) {
            goto remove;
        }
        if (status == GAME_STATUS_0x28 || status == GAME_STATUS_MINIGAME_READY) {
            element = lbl_3_data_92C8[2];
        } else if (status == GAME_STATUS_0x1B || status == GAME_STATUS_MINIGAME_SELECT
                   || status == GAME_STATUS_TOY_STADIUM_LOAD) {
            element = lbl_3_data_92C8[0];
        } else {
            element = lbl_3_data_92C8[1];
        }
    } else {
        if (g_GameLogic.secondaryGameMode != SECONDARY_GAME_MODE_PRACTICE_MENU) {
            goto remove;
        }
        if (g_Practice.practiceType_1 == 6) {
            element = lbl_3_data_92C8[4];
        } else {
            element = lbl_3_data_92C8[3];
        }
    }
    if (scene->state != element) {
        scene->state = element;
        scene->_1E = 1;
        HUD_RECORD(scene, 2)->flags |= UI_FLAG_VISIBLE;
        HUD_RECORD(scene, 2)->playMode = UI_PLAY_FORWARD;
        HUD_RECORD(scene, 2)->frame = 0;
        HUD_RECORD(scene, 3)->elementIndex = element;
        HUD_RECORD(scene, 0)->playMode = UI_PLAY_BACKWARD;
    } else if (scene->_1E != 0) {
        if ((HUD_RECORD(scene, 0)->frame >> 16) == 0) {
            HUD_RECORD(scene, 2)->flags &= ~UI_FLAG_VISIBLE;
            HUD_RECORD(scene, 1)->elementIndex = scene->state;
            HUD_RECORD(scene, 0)->frame = 0x28 << 16;
            HUD_RECORD(scene, 0)->playMode = UI_PLAY_STOP;
            scene->_1E = 0;
        }
    }
    return;
remove:
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
    animRelated[0xD9] = 0;
    menuNumber[0x26] = 1;
}

// .text:0x0012BFE8 size:0x1C4
void fn_3_12BFE8(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_92D4);
    if (g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE) {
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
            HUD_RECORD(scene, 5)->flags &= ~UI_FLAG_VISIBLE;
            HUD_RECORD(scene, 6)->flags &= ~UI_FLAG_VISIBLE;
        } else {
            HUD_RECORD(scene, 5)->flags &= ~UI_FLAG_VISIBLE;
            HUD_RECORD(scene, 6)->flags &= ~UI_FLAG_VISIBLE;
        }
    }
    animRelated[0xBC] = 1;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        scene->_20 = g_Practice.practiceType_2;
        HUD_RECORD(scene, 3)->elementIndex = 0x5F;
        HUD_RECORD(scene, 4)->elementIndex = 0x5C;
    } else {
        scene->_20 = lbl_3_data_21268[(s8)g_Minigame._19E1];
        HUD_RECORD(scene, 3)->elementIndex = 0x5E;
        HUD_RECORD(scene, 4)->elementIndex = 0x5B;
    }
    scene->_1A = 0;
    scene->state = 0;
    scene->_22 = 0;
    currentDrawingItem->func = fn_3_12BB64;
}

// .text:0x0012BB64 size:0x484
void fn_3_12BB64(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    u32 mode;

    if (animRelated[0x96] != 0) {
        goto remove;
    }
    mode = g_d_GameSettings.GameModeSelected;
    if (mode == GAME_TYPE_PRACTICE) {
        if (g_Practice.practiceType_1 == 6) {
            goto remove;
        }
        if (g_GameLogic.secondaryGameMode != SECONDARY_GAME_MODE_PRACTICE_MENU) {
            goto remove;
        }
    } else if (g_GameLogic.gameStatus != GAME_STATUS_MINIGAME_SELECT) {
        goto remove;
    }
    if (mode == GAME_TYPE_PRACTICE) {
        HUD_RECORD(scene, 3)->frame = lbl_3_data_93F4[g_Practice.practiceType_2][0] << 16;
        HUD_RECORD(scene, 4)->frame = lbl_3_data_93F4[g_Practice.practiceType_2][1] << 16;
        if (scene->_20 != g_Practice.practiceType_2) {
            scene->_22 = 1;
        }
    } else {
        if (g_d_GameSettings._12 < 1
            && (lbl_3_data_21268[(s8)g_Minigame._19E1] == 6 || lbl_3_data_21268[(s8)g_Minigame._19E1] == 7)) {
            HUD_RECORD(scene, 3)->frame = lbl_3_data_93D4[0][0] << 16;
            HUD_RECORD(scene, 4)->frame = lbl_3_data_93D4[0][1] << 16;
        } else if (g_d_GameSettings._12 < 2 && lbl_3_data_21268[(s8)g_Minigame._19E1] == 7) {
            HUD_RECORD(scene, 3)->frame = lbl_3_data_93D4[0][0] << 16;
            HUD_RECORD(scene, 4)->frame = lbl_3_data_93D4[0][1] << 16;
        } else {
            HUD_RECORD(scene, 3)->frame = lbl_3_data_93D4[lbl_3_data_21268[(s8)g_Minigame._19E1]][0] << 16;
            HUD_RECORD(scene, 4)->frame = lbl_3_data_93D4[lbl_3_data_21268[(s8)g_Minigame._19E1]][1] << 16;
        }
        if (scene->_20 != lbl_3_data_21268[(s8)g_Minigame._19E1]) {
            scene->_22 = 1;
        }
    }
    if (scene->state == 0) {
        scene->state = 1;
    } else if (scene->state == 1) {
        if ((s32)(HUD_RECORD(scene, 2)->frame >> 16) >= 0xE) {
            scene->state = 2;
        }
    } else if (scene->state == 2) {
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
            if (g_Practice.practiceType_1 == 5 && g_Practice.practiceState == PRACTICE_STATE_3) {
                scene->state = 3;
            }
        } else if (g_GameLogic.gameStatus == GAME_STATUS_TOY_STADIUM_CHARACTER_SELECT) {
            if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_6 && *(s16*)&MG_BYTE(0x18A2) == 0x1F) {
                scene->state = 3;
            }
        } else if (g_GameLogic.gameStatus == GAME_STATUS_0x20) {
            if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_5) {
                scene->state = 3;
            }
        }
    } else if (scene->state == 3) {
        HUD_RECORD(scene, 0)->playMode = UI_PLAY_BACKWARD;
        HUD_RECORD(scene, 2)->playMode = UI_PLAY_BACKWARD;
        HUD_RECORD(scene, 1)->playMode = UI_PLAY_BACKWARD;
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
            if ((s32)(HUD_RECORD(scene, 6)->frame >> 16) > 9) {
                HUD_RECORD(scene, 6)->frame = 9 << 16;
            }
            HUD_RECORD(scene, 6)->playMode = UI_PLAY_BACKWARD;
        }
    }
    return;
remove:
    text_freeBlock(scene->_1E);
    fn_8000F8F4(scene);
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
    animRelated[0xBC] = 0;
}

// .text:0x0012B7A0 size:0x3C4
void fn_3_12B7A0(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    int i;

    scene->state = 0;
    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_9408);
    i = 0;
    do {
        load_Icon(scene, i + 0xD, 1, 0x1A, i);
        HUD_RECORD_AT(scene, 0x32, i)->frame = i << 16;
        HUD_RECORD_AT(scene, 0x3E, i)->frame = 0x36 << 16;
        i++;
    } while (i < 4);
    i = 0;
    do {
        load_Icon(scene, i + 0x44, 1, 0x3C, i);
        i++;
    } while (i < 4);
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        if (g_Minigame._190A != 0) {
            SET_MENU(0x20);
        } else if (fn_3_9E834()) {
            SET_MENU(0x2F);
        } else {
            SET_MENU(0x2E);
        }
    } else {
        if (g_Minigame._190A != 0) {
            SET_MENU(0x23);
        } else if (fn_3_9E834()) {
            SET_MENU(0x35);
        } else {
            SET_MENU(0x34);
        }
    }
    if (g_Minigame._190A != 0) {
        HUD_RECORD(scene, 0x48)->flags |= UI_FLAG_VISIBLE;
        HUD_RECORD(scene, 0x48)->elementIndex = lbl_3_data_9D84[g_d_GameSettings._33];
        for (i = 2; i < 5; i++) {
            HUD_RECORD(scene, i)->flags &= ~UI_FLAG_VISIBLE;
            HUD_RECORD_AT(scene, 4, i)->flags &= ~UI_FLAG_VISIBLE;
            HUD_RECORD_AT(scene, 12, i)->flags &= ~UI_FLAG_VISIBLE;
        }
    }
    animRelated[0xDA] = 1;
    scene->_18 = 0;
    scene->_1A = 0;
    currentDrawingItem->func = fn_3_12A910;
}

// .text:0x0012A910 size:0xE90
void fn_3_12A910(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    UIRecord* rec;
    u32 status;
    int i;
    int j;
    int count;
    int last;
    int active;

    scene->_18++;
    scene->_1A++;
    if (animRelated[0x96] != 0) {
        goto remove;
    }
    status = g_GameLogic.gameStatus;
    if (status != GAME_STATUS_TOY_STADIUM_CHARACTER_SELECT && status != GAME_STATUS_0x20
        && (status != GAME_STATUS_0x1F || g_GameLogic._125 != TRANSITION_CALCULATION_TYPE_0)) {
        goto remove;
    }
    if (scene->state == 0) {
        scene->state = 1;
    } else if (scene->state == 1) {
        rec = HUD_RECORD(scene, 0);
        if ((s32)(rec->frame >> 16) >= lbl_3_data_9D4C[0]) {
            rec->playMode = UI_PLAY_STOP;
            HUD_RECORD(scene, 17)->playMode = UI_PLAY_STOP;
            scene->state = 2;
        }
    } else if (scene->state == 2) {
        for (i = 0; i < 4; i++) {
            if (g_Minigame.selectSlotState[i] >= 0) {
                if (g_Minigame.selectSlots[i].charID >= 0 && g_Minigame.selectSlots[i]._7 != 0) {
                    HUD_RECORD_AT(scene, 9, i)->playMode = UI_PLAY_FORWARD;
                } else {
                    rec = HUD_RECORD_AT(scene, 9, i);
                    if ((s32)(rec->frame >> 16) < 10) {
                        rec->playMode = UI_PLAY_FORWARD;
                    } else if ((s32)(rec->frame >> 16) > 10) {
                        rec->playMode = UI_PLAY_BACKWARD;
                    } else {
                        rec->playMode = UI_PLAY_STOP;
                    }
                }
                HUD_RECORD_AT(scene, 13, i)->playMode = UI_PLAY_FORWARD;
                HUD_RECORD_AT(scene, 1, i)->playMode = UI_PLAY_FORWARD;
            } else {
                HUD_RECORD_AT(scene, 9, i)->playMode = UI_PLAY_BACKWARD;
                HUD_RECORD_AT(scene, 13, i)->playMode = UI_PLAY_BACKWARD;
                HUD_RECORD_AT(scene, 1, i)->playMode = UI_PLAY_BACKWARD;
            }
        }
        for (j = 0; j < 4; j++) {
            if (g_Minigame.selectSlotState[j] == 0) {
                load_Icon(scene, j + 0xD, 1, 0x1A, j);
            } else if (g_Minigame.selectSlotState[j] == 1) {
                load_Icon(scene, j + 0xD, 1, 0x1A, j + 4);
            }
        }
        if (g_Minigame._19DE == 4) {
            HUD_RECORD(scene, 66)->anchorSub = 3 - MG_S16(0x18A2);
            HUD_RECORD(scene, 67)->anchorSub = 3 - MG_S16(0x18A2);
            HUD_RECORD(scene, 66)->playMode = UI_PLAY_FORWARD;
            HUD_RECORD(scene, 67)->playMode = UI_PLAY_FORWARD;
            for (i = 0; i < 4; i++) {
                if (g_Minigame.playerSlots.aiStrength[MG_S16(0x18A2)] == i) {
                    HUD_RECORD_AT(scene, 68, i)->playMode = UI_PLAY_FORWARD;
                    if ((s32)(HUD_RECORD_AT(scene, 68, i)->frame >> 16) >= 50) {
                        HUD_RECORD_AT(scene, 68, i)->frame = 10 << 16;
                    }
                } else {
                    HUD_RECORD_AT(scene, 68, i)->playMode = UI_PLAY_STOP;
                    HUD_RECORD_AT(scene, 68, i)->frame = 0;
                }
            }
        } else {
            HUD_RECORD(scene, 66)->playMode = UI_PLAY_BACKWARD;
            HUD_RECORD(scene, 67)->playMode = UI_PLAY_BACKWARD;
        }
        if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_6) {
            count = 0;
            for (j = 0; j < 4; j++) {
                if (g_Minigame.selectSlotState[j] == 0) {
                    last = j;
                    count++;
                }
            }
            if (count > 1 || g_Minigame._1A3C != 0 || g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                scene->state = 5;
                animRelated[0xDB] = 4;
            } else {
                scene->state = 3;
                animRelated[0xDB] = last;
            }
            scene->_1A = 0;
        } else if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_3) {
            if (g_d_GameSettings.GameModeSelected != GAME_TYPE_TOY_FIELD) {
                scene->state = 6;
                scene->_1A = 0;
            }
        }
    } else if (scene->state == 6) {
        if (scene->_1A == 1) {
            HUD_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
            HUD_RECORD(scene, 17)->playMode = UI_PLAY_FORWARD;
        }
        if ((s32)(HUD_RECORD(scene, 0)->frame >> 16) >= 30) {
            goto remove;
        }
    } else if (scene->state == 7) {
        if (scene->_1A >= 30) {
            if (animRelated[0xDB] != 4) {
                HUD_RECORD(scene, 0)->elementIndex = lbl_3_data_9D48[0];
                HUD_RECORD(scene, 0)->frame = lbl_3_data_9D4C[0] << 16;
                HUD_RECORD(scene, 0)->playMode = UI_PLAY_STOP;
                HUD_RECORD(scene, 17)->elementIndex = lbl_3_data_9D48[0];
                HUD_RECORD(scene, 17)->frame = lbl_3_data_9D4C[0] << 16;
                HUD_RECORD(scene, 17)->playMode = UI_PLAY_STOP;
            }
            scene->state = 2;
        }
    }
    for (i = 0; i < 4; i++) {
        active = FALSE;
        if (g_Minigame.selectSlotState[i] >= 0) {
            if (g_Minigame._190A == 0 || i == g_d_GameSettings._35) {
                if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                    if (g_Minigame.selectSlots[i].charID >= 0) {
                        active = TRUE;
                    }
                } else if (g_Minigame._19DE != 8 || (s8)g_Minigame._1908 == i) {
                    active = TRUE;
                }
            }
        }
        if (active) {
            HUD_RECORD_AT(scene, 18, i)->playMode = UI_PLAY_FORWARD;
        } else {
            HUD_RECORD_AT(scene, 18, i)->playMode = UI_PLAY_BACKWARD;
        }
        if (g_Minigame.selectSlots[i].charID < 0 || g_Minigame.selectSlots[i]._7 == 0) {
            HUD_RECORD_AT(scene, 18, i)->flags &= ~UI_FLAG_VISIBLE;
        } else {
            HUD_RECORD_AT(scene, 18, i)->flags |= UI_FLAG_VISIBLE;
        }
        HUD_RECORD_AT(scene, 22, i)->frame = lbl_3_data_A594[g_Minigame.battingHandedness[i]] << 16;
    }
    for (i = 0; i < 4; i++) {
        active = FALSE;
        if (g_Minigame.selectSlotState[i] >= 0) {
            if (g_Minigame._190A == 0 || i == g_d_GameSettings._35) {
                if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                    if (g_Minigame.selectSlots[i].charID >= 0 && g_Minigame.selectSlots[i]._1 == 0) {
                        active = TRUE;
                    }
                } else if (g_Minigame._19DE != 8 || (s8)g_Minigame._1908 == i) {
                    if (g_Minigame.selectSlots[i].charID >= 0 && g_Minigame.selectSlots[i]._6 == 0 && g_Minigame.selectSlots[i]._1 == 0) {
                        active = TRUE;
                    }
                }
            }
        }
        if (active && characterStaticIndexes[g_Minigame.selectSlots[i].charID * 6] != 0 && g_Minigame.selectSlots[i]._7 != 0) {
            HUD_RECORD_AT(scene, 30, i)->flags |= UI_FLAG_VISIBLE;
        } else {
            HUD_RECORD_AT(scene, 30, i)->flags &= ~UI_FLAG_VISIBLE;
        }
    }
    for (i = 0; i < 4; i++) {
        active = FALSE;
        if (g_Minigame.selectSlotState[i] >= 0) {
            if (g_Minigame._190A == 0 || i == g_d_GameSettings._35) {
                if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                    if (g_Minigame.selectSlots[i].charID >= 0) {
                        active = TRUE;
                    }
                } else if (g_Minigame._19DE != 8 || (s8)g_Minigame._1908 == i) {
                    if (g_Minigame.selectSlots[i].charID >= 0 && g_Minigame.selectSlots[i]._6 == 0) {
                        active = TRUE;
                    }
                }
            }
        }
        if (active
            && ((g_d_GameSettings.exhibitionMatchInd != 0 && superstarUnlocked[g_Minigame.selectSlots[i].charID] != 0)
                || (g_d_GameSettings.exhibitionMatchInd == 0
                    && ((u8*)starMissionCompletionTracker + g_Minigame.selectSlots[i].charID)[0x43D6] != 0))
            && g_Minigame.selectSlots[i]._7 != 0) {
            HUD_RECORD_AT(scene, 34, i)->flags |= UI_FLAG_VISIBLE;
            HUD_RECORD_AT(scene, 34, i)->playMode = UI_PLAY_FORWARD;
            HUD_RECORD_AT(scene, 38, i)->playMode = UI_PLAY_FORWARD;
            if (g_Minigame.playerSlots._08[i] != 0) {
                if (HUD_RECORD_AT(scene, 38, i)->elementIndex == 0x3E) {
                    HUD_RECORD_AT(scene, 38, i)->elementIndex = 0x40;
                    HUD_RECORD_AT(scene, 38, i)->frame = 0;
                }
            } else {
                if (HUD_RECORD_AT(scene, 38, i)->elementIndex == 0x40) {
                    HUD_RECORD_AT(scene, 38, i)->elementIndex = 0x3E;
                    HUD_RECORD_AT(scene, 38, i)->frame = 0;
                }
            }
        } else {
            HUD_RECORD_AT(scene, 34, i)->flags &= ~UI_FLAG_VISIBLE;
            HUD_RECORD_AT(scene, 34, i)->frame = 0;
            HUD_RECORD_AT(scene, 34, i)->playMode = UI_PLAY_STOP;
            HUD_RECORD_AT(scene, 38, i)->frame = 0;
            HUD_RECORD_AT(scene, 38, i)->playMode = UI_PLAY_STOP;
        }
    }
    for (i = 0; i < 4; i++) {
        if (g_Minigame.selectSlotState[i] >= 0 && g_Minigame.selectSlots[i].charID >= 0 && g_Minigame.selectSlots[i]._7 != 0) {
            if (g_Minigame.selectSlots[i].charID != (HUD_RECORD_AT(scene, 62, i)->frame >> 16)) {
                HUD_RECORD_AT(scene, 42, i)->frame = 0;
                HUD_RECORD_AT(scene, 46, i)->frame = 0;
            }
            HUD_RECORD_AT(scene, 42, i)->flags |= UI_FLAG_VISIBLE;
            HUD_RECORD_AT(scene, 42, i)->playMode = UI_PLAY_FORWARD;
            HUD_RECORD_AT(scene, 46, i)->flags |= UI_FLAG_VISIBLE;
            HUD_RECORD_AT(scene, 46, i)->playMode = UI_PLAY_FORWARD;
            HUD_RECORD_AT(scene, 62, i)->frame = g_Minigame.selectSlots[i].charID << 16;
            HUD_RECORD_AT(scene, 54, i)->flags |= UI_FLAG_VISIBLE;
            HUD_RECORD_AT(scene, 54, i)->playMode = UI_PLAY_FORWARD;
            last = lbl_3_data_9D50[characterStaticIndexes[g_Minigame.selectSlots[i].charID * 6]][characterStaticIndexes[g_Minigame.selectSlots[i].charID * 6 + 5]];
            HUD_RECORD_AT(scene, 58, i)->frame = last << 16;
        } else {
            HUD_RECORD_AT(scene, 42, i)->frame = 0;
            HUD_RECORD_AT(scene, 42, i)->flags &= ~UI_FLAG_VISIBLE;
            HUD_RECORD_AT(scene, 46, i)->frame = 0;
            HUD_RECORD_AT(scene, 46, i)->flags &= ~UI_FLAG_VISIBLE;
            HUD_RECORD_AT(scene, 62, i)->frame = 0x36 << 16;
            HUD_RECORD_AT(scene, 54, i)->frame = 0;
            HUD_RECORD_AT(scene, 54, i)->flags &= ~UI_FLAG_VISIBLE;
        }
    }
    return;
remove:
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
    animRelated[0xDA] = 2;
}

// .text:0x0012A6C4 size:0x24C
void fn_3_12A6C4(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    int i;

    scene->_1E = 0;
    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_9D94);
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        scene->_1E = 1;
        HUD_RECORD(scene, 1)->elementIndex = 0x30;
        HUD_RECORD(scene, 7)->flags &= ~UI_FLAG_VISIBLE;
    }
    for (i = 0; i < 4; i++) {
        HUD_RECORD_AT(scene, 4, i)->anchorSub = lbl_3_data_9EBC[scene->_1E][i];
    }
    HUD_RECORD(scene, 3)->anchorSub = lbl_3_data_9EBC[scene->_1E][(s8)g_Minigame._19E3 + 4];
    i = 0;
    do {
        load_Icon(scene, i + 4, 1, 0x32, i + 4);
        if (i > g_Minigame._1A0E || i < g_Minigame._1A0D) {
            HUD_RECORD_AT(scene, 4, i)->frame = 6 << 16;
        } else {
            HUD_RECORD_AT(scene, 4, i)->frame = 0;
        }
        i++;
    } while (i < 4);
    setIndicatorSlotState((DrawingSceneStruct*)scene, 2, 1, 0x35, 1);
    scene->_18 = 0;
    scene->_1A = 0;
    scene->state = 0;
    currentDrawingItem->func = fn_3_12A3F0;
}

// .text:0x0012A3F0 size:0x2D4
void fn_3_12A3F0(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    UIRecord* rec;
    int i;

    if (scene->_18 < 0xFFFE) {
        scene->_18++;
    } else {
        scene->_18 = 0xFFFF;
    }
    if (scene->_1A < 0xFFFE) {
        scene->_1A++;
    } else {
        scene->_1A = 0xFFFF;
    }
    if (scene->state == 0) {
        scene->state++;
    } else if (scene->state == 1) {
        rec = HUD_RECORD(scene, 1);
        if ((s32)(rec->frame >> 16) >= lbl_3_data_9EB4[scene->_1E][0]) {
            rec->playMode = UI_PLAY_STOP;
            scene->state = 2;
        }
    } else if (scene->state == 2) {
        HUD_RECORD(scene, 3)->anchorSub = lbl_3_data_9EBC[scene->_1E][(s8)g_Minigame._19E3 + 4];
        for (i = 0; i < 4; i++) {
            if (i > g_Minigame._1A0E || i < g_Minigame._1A0D) {
                HUD_RECORD_AT(scene, 4, i)->playMode = UI_PLAY_STOP;
                HUD_RECORD_AT(scene, 4, i)->frame = 6 << 16;
            } else if (i == (s8)g_Minigame._19E3) {
                HUD_RECORD_AT(scene, 4, i)->playMode = UI_PLAY_FORWARD;
                if ((s32)(HUD_RECORD_AT(scene, 4, i)->frame >> 16) >= 5) {
                    HUD_RECORD_AT(scene, 4, i)->playMode = UI_PLAY_STOP;
                }
            } else {
                HUD_RECORD_AT(scene, 4, i)->playMode = UI_PLAY_STOP;
                HUD_RECORD_AT(scene, 4, i)->frame = 0;
            }
        }
        if (g_Minigame._19DE != 1) {
            HUD_RECORD(scene, 1)->playMode = UI_PLAY_FORWARD;
            scene->state = 3;
        }
    } else if (scene->state == 3) {
        if ((s32)(HUD_RECORD(scene, 1)->frame >> 16) >= lbl_3_data_9EB4[scene->_1E][1]) {
            goto remove;
        }
    }
    return;
remove:
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
}

// .text:0x0012A2B8 size:0x138
void fn_3_12A2B8(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    int n;
    int i;

    n = (&g_d_GameSettings._13)[g_Minigame.GameMode_MiniGame];
    if (g_Minigame._190A != 0) {
        n = 2;
    }
    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_9ECC);
    for (i = 0; i < 4; i++) {
        if (n >= i) {
            load_Icon(scene, i + 2, 1, 0x6B, i);
        } else {
            load_Icon(scene, i + 2, 1, 0x6B, 4);
        }
    }
    scene->state = 0;
    if (animRelated[0xBF] != 0) {
        HUD_RECORD(scene, 0)->frame = 0x16 << 16;
        scene->state = 2;
    }
    scene->_18 = 0;
    scene->_1A = 0;
    animRelated[0xBE] = 1;
    currentDrawingItem->func = fn_3_129FF8;
}

// .text:0x00129FF8 size:0x2C0
void fn_3_129FF8(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    int i;

    if (scene->_18 < 0xFFFE) {
        scene->_18++;
    } else {
        scene->_18 = 0xFFFF;
    }
    if (scene->_1A < 0xFFFE) {
        scene->_1A++;
    } else {
        scene->_1A = 0xFFFF;
    }
    if (animRelated[0x96] != 0 || g_GameLogic.gameStatus != GAME_STATUS_TOY_STADIUM_CHARACTER_SELECT) {
        goto remove;
    }
    if (scene->state == 0) {
        scene->state++;
    } else if (scene->state == 1) {
        if ((s32)(HUD_RECORD(scene, 0)->frame >> 16) >= 0xF) {
            HUD_RECORD(scene, 0)->playMode = UI_PLAY_STOP;
            scene->state++;
        }
    } else if (scene->state == 2) {
        for (i = 0; i < 4; i++) {
            if (i == (s8)MG_BYTE(0x19E4)) {
                if (g_Minigame._19DE >= 8 || g_GameLogic._125 >= TRANSITION_CALCULATION_TYPE_6) {
                    if ((HUD_RECORD_AT(scene, 2, i)->frame >> 16) <= 0x37) {
                        HUD_RECORD_AT(scene, 2, i)->frame = 0x37 << 16;
                    }
                    HUD_RECORD_AT(scene, 2, i)->playMode = UI_PLAY_FORWARD;
                } else {
                    if ((HUD_RECORD_AT(scene, 2, i)->frame >> 16) >= 0x37) {
                        HUD_RECORD_AT(scene, 2, i)->frame = 5 << 16;
                    }
                    HUD_RECORD_AT(scene, 2, i)->playMode = UI_PLAY_FORWARD;
                }
            } else {
                HUD_RECORD_AT(scene, 2, i)->playMode = UI_PLAY_STOP;
                HUD_RECORD_AT(scene, 2, i)->frame = 0;
            }
        }
        if (g_Minigame._19DE == 0) {
            HUD_RECORD(scene, 0)->playMode = UI_PLAY_BACKWARD;
            HUD_RECORD(scene, 1)->playMode = UI_PLAY_BACKWARD;
            scene->state = 3;
        }
    } else if (scene->state == 3) {
        if ((s32)(HUD_RECORD(scene, 0)->frame >> 16) <= 0) {
            goto remove;
        }
    }
    return;
remove:
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
    animRelated[0xBE] = 0;
}

// .text:0x00129F48 size:0xB0
void fn_3_129F48(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_9FB4);
    scene->state = 0;
    if (animRelated[0xBF] != 0) {
        HUD_RECORD(scene, 0)->frame = 0x16 << 16;
        scene->state = 2;
    }
    scene->_18 = 0;
    scene->_1A = 0;
    animRelated[0xBE] = 1;
    currentDrawingItem->func = fn_3_129C88;
}

// .text:0x00129C88 size:0x2C0
void fn_3_129C88(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    int i;

    if (scene->_18 < 0xFFFE) {
        scene->_18++;
    } else {
        scene->_18 = 0xFFFF;
    }
    if (scene->_1A < 0xFFFE) {
        scene->_1A++;
    } else {
        scene->_1A = 0xFFFF;
    }
    if (animRelated[0x96] != 0 || g_GameLogic.gameStatus != GAME_STATUS_TOY_STADIUM_CHARACTER_SELECT) {
        goto remove;
    }
    if (scene->state == 0) {
        scene->state++;
    } else if (scene->state == 1) {
        if ((s32)(HUD_RECORD(scene, 0)->frame >> 16) >= 0xF) {
            HUD_RECORD(scene, 0)->playMode = UI_PLAY_STOP;
            scene->state++;
        }
    } else if (scene->state == 2) {
        for (i = 0; i < 3; i++) {
            if (i == (s8)MG_BYTE(0x19E4)) {
                if (g_Minigame._19DE >= 8 || g_GameLogic._125 >= TRANSITION_CALCULATION_TYPE_6) {
                    if ((HUD_RECORD_AT(scene, 2, i)->frame >> 16) <= 0x5A) {
                        HUD_RECORD_AT(scene, 2, i)->frame = 0x5A << 16;
                    }
                    HUD_RECORD_AT(scene, 2, i)->playMode = UI_PLAY_FORWARD;
                } else {
                    if ((HUD_RECORD_AT(scene, 2, i)->frame >> 16) >= 0x5A) {
                        HUD_RECORD_AT(scene, 2, i)->frame = 0xA << 16;
                    }
                    HUD_RECORD_AT(scene, 2, i)->playMode = UI_PLAY_FORWARD;
                }
            } else {
                HUD_RECORD_AT(scene, 2, i)->playMode = UI_PLAY_STOP;
                HUD_RECORD_AT(scene, 2, i)->frame = 0;
            }
        }
        if (g_Minigame._19DE == 0) {
            HUD_RECORD(scene, 0)->playMode = UI_PLAY_BACKWARD;
            HUD_RECORD(scene, 1)->playMode = UI_PLAY_BACKWARD;
            scene->state = 3;
        }
    } else if (scene->state == 3) {
        if ((s32)(HUD_RECORD(scene, 0)->frame >> 16) <= 0) {
            goto remove;
        }
    }
    return;
remove:
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
    animRelated[0xBE] = 0;
}

// .text:0x00129A18 size:0x270
void fn_3_129A18(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    int n;
    int i;
    int j;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_A598);
    HUD_RECORD(scene, 0)->frame = 0;
    scene->state = 0;
    n = (s8)g_Minigame._19E1;
    if (n >= 5) {
        scene->state = n - 4;
    }
    for (i = 0, j = 0; i < 7; i++) {
        HUD_RECORD_AT(scene, 0xE, i)->elementIndex = lbl_3_data_A9E8[lbl_3_data_21268[i]];
        if (g_d_GameSettings._12 < 1 && lbl_3_data_21268[i] == 6) {
            HUD_RECORD_AT(scene, 0xE, i)->elementIndex = lbl_3_data_A9E8[0];
        } else if (g_d_GameSettings._12 < 2 && lbl_3_data_21268[i] == 7) {
            HUD_RECORD_AT(scene, 0xE, i)->elementIndex = lbl_3_data_A9E8[0];
        }
        if (i < scene->state) {
            HUD_RECORD(scene, i)->frame = lbl_3_data_A8B8[0] << 16;
        } else if (j >= 5) {
            HUD_RECORD(scene, i)->frame = lbl_3_data_A8B8[6] << 16;
        } else {
            j++;
            HUD_RECORD(scene, i)->frame = lbl_3_data_A8B8[j] << 16;
        }
    }
    animRelated[0xDA] = 0;
    animRelated[0xBB] = 0;
    SET_MENU(0x33);
    animRelated[0xBA] = animRelated[0xB9];
    animRelated[0xBD] = 0;
    scene->_18 = 1;
    scene->_1E = 0;
    currentDrawingItem->func = fn_3_12955C;
}

// .text:0x0012955C size:0x4BC
void fn_3_12955C(void) {
    MinigameHudScene* scene;
    UIRecord* rec;
    int i;
    int idx;

    scene = (MinigameHudScene*)currentDrawingItem;
    animRelated[0xBB] = 0;
    if (animRelated[0x96] != 0) {
        goto remove;
    }
    if (scene->_18 == 1) {
        for (i = 7; i < 14; i++) {
            rec = HUD_RECORD(scene, i);
            if ((rec->frame >> 16) >= 8) {
                rec->playMode = UI_PLAY_STOP;
                scene->_18 = 2;
            }
        }
    } else if (scene->_18 == 2) {
        if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_3) {
            scene->_18 = 3;
            return;
        }
        for (i = 0; i < 7; i++) {
            if (i == (s8)g_Minigame._19E1) {
                HUD_RECORD_PLUS(scene, i, 7)->playMode = UI_PLAY_FORWARD;
                HUD_RECORD_PLUS(scene, i, 14)->playMode = UI_PLAY_FORWARD;
            } else {
                rec = HUD_RECORD_PLUS(scene, i, 7);
                if ((rec->frame >> 16) > 8) {
                    rec->playMode = UI_PLAY_BACKWARD;
                    animRelated[0xBB] = 1;
                } else {
                    rec->playMode = UI_PLAY_STOP;
                }
                HUD_RECORD_PLUS(scene, i, 14)->playMode = UI_PLAY_STOP;
                HUD_RECORD_PLUS(scene, i, 14)->frame = 0;
            }
        }
        if ((s8)g_Minigame._19E1 < scene->state) {
            for (i = 0; i < 7; i++) {
                idx = i - (s8)g_Minigame._19E1 + 1;
                if (idx >= 6) {
                    idx = 6;
                }
                if ((HUD_RECORD(scene, i)->frame >> 16) < lbl_3_data_A8B8[idx]) {
                    HUD_RECORD(scene, i)->playMode = UI_PLAY_FORWARD;
                    animRelated[0xBB] = 1;
                } else {
                    HUD_RECORD(scene, i)->playMode = UI_PLAY_STOP;
                }
            }
            if (animRelated[0xBB] == 0) {
                scene->state = (s8)g_Minigame._19E1;
            }
        } else if ((s8)g_Minigame._19E1 > scene->state + 4) {
            for (i = 0; i < 7; i++) {
                idx = 5 - (s8)g_Minigame._19E1 + i;
                if (idx < 0) {
                    idx = 0;
                }
                if ((HUD_RECORD(scene, i)->frame >> 16) > lbl_3_data_A8B8[idx]) {
                    HUD_RECORD(scene, i)->playMode = UI_PLAY_BACKWARD;
                    animRelated[0xBB] = 1;
                } else {
                    HUD_RECORD(scene, i)->playMode = UI_PLAY_STOP;
                }
            }
            if (animRelated[0xBB] == 0) {
                scene->state = (s8)g_Minigame._19E1 - 4;
            }
        }
    } else {
        if ((scene->_18 = 3) != 0) {
            for (i = 7; i < 14; i++) {
                HUD_RECORD(scene, i)->playMode = UI_PLAY_BACKWARD;
            }
            HUD_RECORD(scene, 21)->playMode = UI_PLAY_BACKWARD;
            if ((HUD_RECORD_AT(scene, 7, (s8)g_Minigame._19E1)->frame >> 16) == 0) {
                goto remove;
            }
        }
    }
    if (scene->state == 0) {
        HUD_RECORD(scene, 22)->flags &= ~UI_FLAG_VISIBLE;
    } else {
        HUD_RECORD(scene, 22)->flags |= UI_FLAG_VISIBLE;
    }
    if (scene->state < 2) {
        HUD_RECORD(scene, 23)->flags |= UI_FLAG_VISIBLE;
    } else {
        HUD_RECORD(scene, 23)->flags &= ~UI_FLAG_VISIBLE;
    }
    return;
remove:
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
}

// .text:0x00129458 size:0x104
void fn_3_129458(void) {
    if (g_GameLogic.gameStatus == GAME_STATUS_MVP_END_GAME && g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_1) {
        animRelated[0xB7] = 0;
        animRelated[0xB6] = 0;
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY && g_Minigame.multiPlayerInd == 0
            && g_Minigame._1A3C == 0 && g_Minigame.soloMinigameDifficulty == MINIGAME_DIFFICULTY_SOLO_NON_CHALLENGE) {
            insertGraphicDrawingFunction(mm_DrawResultCode, 2);
        }
        insertGraphicDrawingFunction(fn_3_EA454, 2);
        insertGraphicDrawingFunction(fn_3_129370, 2);
    }
    if (g_GameLogic.gameStatus == GAME_STATUS_MINIGAME_POST_MENU) {
        if (pauseControl[0x1D2] == 7 || g_GameLogic.framesOfExitingToMenu != 0) {
            animRelated[0xB7] = 1;
        }
    }
}

// .text:0x001293D0 size:0x88
void fn_3_1293D0(void) {
    if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_0) {
        insertGraphicDrawingFunction(fn_3_129370, 2);
    }
    if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_5 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
        insertGraphicDrawingFunction(fn_8004D0F0, 2);
    }
    if (g_GameLogic._125 == TRANSITION_CALCULATION_TYPE_6) {
        set803c5f77();
    }
}

// .text:0x00129370 size:0x60 mapped:0x80768404
void fn_3_129370(void) {
    DrawingSceneStruct* node = currentDrawingItem;

    addGraphicsElementToScene(node, lbl_3_data_A9F8);
    ((MinigameHudScene*)node)->_18 = 0;
    ((MinigameHudScene*)node)->_1A = 0;
    currentDrawingItem->func = fn_3_128C18;
}

// .text:0x00128C18 size:0x758 mapped:0x80767CAC
void fn_3_128C18(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    u32 mode;
    u32 status;
    BOOL found;
    u32 i;
    u32 count;
    int k;
    int x;
    int y;
    int id;
    VecXYZ pos;

    if (animRelated[0x96] != 0) {
        goto remove;
    }
    mode = g_d_GameSettings.GameModeSelected;
    if (mode == GAME_TYPE_TOY_FIELD) {
        if (pauseControl[0x1D2] == 5) {
            goto remove;
        }
    } else if (g_GameLogic.gameStatus == GAME_STATUS_MINIGAME_POST_MENU) {
        if (pauseControl[0x1D2] == 7) {
            goto remove;
        }
        if (g_GameLogic.framesOfExitingToMenu != 0) {
            goto remove;
        }
    }
    status = g_GameLogic.gameStatus;
    if (status == GAME_STATUS_0x26 || status == GAME_STATUS_0x24) {
        goto remove;
    }
    if (animRelated[0xB8] == 2) {
        animRelated[0xB8] = 0;
        HUD_RECORD(scene, 0)->playMode = UI_PLAY_BACKWARD;
        return;
    }
    if (animRelated[0xB8] == 0) {
        return;
    }
    animRelated[0xB8] = 0;
    if (status == GAME_STATUS_0x27 && g_Minigame._1A3D == 1) {
        found = FALSE;
        for (i = 0; i < 4; i++) {
            if (g_Minigame._1E01[7 + i * 2] == (s8)g_Minigame._1908 && g_Minigame._1E01[8 + i * 2] == 0) {
                found = TRUE;
                break;
            }
        }
        if (g_Minigame._1E01[8] == 0 && g_Minigame._1E01[10] == 0 && g_Minigame._1E01[12] == 0
            && g_Minigame._1E01[14] == 0) {
            HUD_RECORD(scene, 0)->elementIndex = lbl_3_data_AA98[2];
        } else if (found) {
            HUD_RECORD(scene, 0)->elementIndex = lbl_3_data_AA98[8];
        } else {
            HUD_RECORD(scene, 0)->elementIndex = lbl_3_data_AA98[10];
        }
        HUD_RECORD(scene, 0)->flags |= UI_FLAG_VISIBLE;
        HUD_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
        HUD_RECORD(scene, 0)->frame = 0;
        HUD_RECORD(scene, 0)->pos.x = 0.0f;
        HUD_RECORD(scene, 0)->pos.y = 0.0f;
    } else if (g_Minigame.soloMinigameDifficulty == MINIGAME_DIFFICULTY_SOLO_NON_CHALLENGE
               || (mode == GAME_TYPE_TOY_FIELD && g_Minigame._1908 >= 0 && g_Minigame._1A43 != 0)) {
        if (g_Minigame._1A43 == 1) {
            HUD_RECORD(scene, 0)->elementIndex = lbl_3_data_AA98[7];
        } else if (g_Minigame._1A43 != 0) {
            HUD_RECORD(scene, 0)->elementIndex = lbl_3_data_AA98[6];
        } else {
            HUD_RECORD(scene, 0)->elementIndex = lbl_3_data_AA98[5];
        }
        HUD_RECORD(scene, 0)->flags |= UI_FLAG_VISIBLE;
        HUD_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
        HUD_RECORD(scene, 0)->frame = 0;
        HUD_RECORD(scene, 0)->pos.x = 0.0f;
        HUD_RECORD(scene, 0)->pos.y = 0.0f;
    } else if (g_Minigame.miniGameNumberOfParticipants > 1) {
        if (g_Minigame.challenge_minigame_haven_tWonYetIndicator != 0) {
            HUD_RECORD(scene, 0)->flags |= UI_FLAG_VISIBLE;
            HUD_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
            HUD_RECORD(scene, 0)->elementIndex = lbl_3_data_AA98[2];
            HUD_RECORD(scene, 0)->pos.x = 0.0f;
            HUD_RECORD(scene, 0)->pos.y = 0.0f;
        } else {
            count = 0;
            for (k = 0; k < 4; k++) {
                if (g_Minigame.playerSlots._1C[k] == 1) {
                    getAnimRelatedCoordinates(g_Minigame.playerSlots.characterIndex[k], 9, &pos);
                    id = g_Minigame.playerSlots._04[k];
                    pos.y = (f32)((0.01f * -(f32)barrelCollisionHitboxes[id]) * charSizeMultipliers[id][0]) - 0.5f;
                    fn_3_1650C(&x, &y, 0, pos.x, pos.y, pos.z);
                    x = ((s16(*)[4])lbl_3_data_226E0)[g_Minigame.miniGameNumberOfParticipants - 1][k];
                    HUD_RECORD(scene, count)->flags |= UI_FLAG_VISIBLE;
                    HUD_RECORD(scene, count)->playMode = UI_PLAY_FORWARD;
                    HUD_RECORD(scene, count)->pos.x = x;
                    HUD_RECORD(scene, count)->pos.y = y;
                    HUD_RECORD(scene, count)->elementIndex = lbl_3_data_AA98[1];
                    count++;
                }
            }
        }
    } else if (g_Minigame.pointsReqToWin_challenge != 0) {
        count = 0;
        for (i = 0; i < 4; i++) {
            if (g_Minigame.playerSlots.characterIndex[i] >= 0) {
                HUD_RECORD(scene, count)->flags |= UI_FLAG_VISIBLE;
                HUD_RECORD(scene, count)->playMode = UI_PLAY_FORWARD;
                if (g_Minigame._1A37 == 1) {
                    HUD_RECORD(scene, count)->elementIndex = lbl_3_data_AA98[0];
                } else {
                    HUD_RECORD(scene, count)->elementIndex = lbl_3_data_AA98[4];
                }
                count++;
            }
        }
    }
    return;
remove:
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
    if (g_Minigame._190A != 0) {
        menuNumber[0x26] = 1;
    }
}

// .text:0x00128B90 size:0x88 mapped:0x80767C24
void fn_3_128B90(void) {
    DrawingSceneStruct* node = currentDrawingItem;

    lbl_3_data_B0E0[0].elementIndex = lbl_3_data_B140[g_Minigame.GameMode_MiniGame][0];
    lbl_3_data_B0E0[1].elementIndex = lbl_3_data_B140[g_Minigame.GameMode_MiniGame][1];
    addGraphicsElementToScene(node, lbl_3_data_B0E0);
    ((MinigameHudScene*)node)->state = 1;
    currentDrawingItem->func = fn_3_128A38;
}

// .text:0x00128A38 size:0x158 mapped:0x80767ACC
void fn_3_128A38(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    UIRecord* rec;

    if (animRelated[0x96] != 0) {
        goto remove;
    }
    if (scene->state == 1) {
        rec = HUD_RECORD(scene, 0);
        if ((rec->frame >> 16) >= 10) {
            rec->playMode = UI_PLAY_STOP;
            scene->state++;
        }
        return;
    }
    if (scene->state == 2) {
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
            if (pauseControl[0x1D2] == 5) {
                HUD_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
                scene->state++;
            }
        } else {
            if (pauseControl[0x1D4] == 5) {
                HUD_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
                scene->state++;
            }
        }
        return;
    }
    if (scene->state == 3) {
        if ((HUD_RECORD(scene, 0)->frame >> 16) >= 0x14) {
            goto remove;
        }
    }
    return;
remove:
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
}

// .text:0x00127B68 size:0xED0 mapped:0x80766BFC
void fn_3_127B68(void) {
    DrawingSceneStruct* node = currentDrawingItem;
    MinigameHudScene* scene;
    s16* shown;
    u8* descriptors;
    u8* anchorTable;
    s16 out[8];
    ToyResultsIn in;
    s16 n;
    s16 diff;
    s16 step;
    u32 i;
    u32 k;
    u32 threshold;
    int slot;
    int character;

    descriptors = (u8*)lbl_3_data_226E0;
    scene = (MinigameHudScene*)node;
    shown = (s16*)node;
    if (scene->state >= 6) {
        *(u32*)((u8*)&g_Minigame + 0x1E04) = 0;
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    if (g_GameLogic.gameStatus != GAME_STATUS_0x24) {
        *(u32*)((u8*)&g_Minigame + 0x1E04) = 0;
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    fn_3_10754C(&in);
    fn_8006C2B4(out, &in);
    switch (scene->state) {
    case 0:
        addGraphicsElementToScene((DrawingSceneStruct*)scene, (UIRecordDescriptor*)(descriptors + 0x20));
        slot = (s8)g_Minigame._1908;
        character = g_Minigame.playerSlots.characterIndex[slot];
        HUD_RECORD(scene, 2)->frame = inMemRoster[0][character].stats.CharID << 16;
        k = 0;
        do {
            HUD_RECORD(scene, in.slot[k] + 3)->anchorSub = ((HudDescriptorTables*)descriptors)->anchors[k];
            k++;
        } while (k < 6);
        n = in.v[0];
        if (n > 9999) {
            n = 9999;
        }
        load_Icon(scene, 4, 4, 6, n >= 1000 ? n % 10000 / 1000 : 10);
        load_Icon(scene, 4, 3, 6, n >= 100 ? n % 1000 / 100 : 10);
        load_Icon(scene, 4, 2, 6, n >= 10 ? n % 100 / 10 : 10);
        load_Icon(scene, 4, 1, 6, n % 10);
        n = in.v[1];
        if (n > 9999) {
            n = 9999;
        }
        if (n >= 1000) {
            HUD_RECORD(scene, 5)->elementIndex = 0x76;
        } else if (n >= 100) {
            HUD_RECORD(scene, 5)->elementIndex = 0x77;
        } else if (n >= 10) {
            HUD_RECORD(scene, 5)->elementIndex = 0x78;
        } else {
            HUD_RECORD(scene, 5)->elementIndex = 0x79;
        }
        load_Icon(scene, 5, 4, 6, n % 10000 / 1000);
        load_Icon(scene, 5, 3, 6, n % 1000 / 100);
        load_Icon(scene, 5, 2, 6, n % 100 / 10);
        load_Icon(scene, 5, 1, 6, n % 10);
        n = in.v[2];
        if (n > 9999) {
            n = 9999;
        }
        load_Icon(scene, 6, 4, 6, n >= 1000 ? n % 10000 / 1000 : 10);
        load_Icon(scene, 6, 3, 6, n >= 100 ? n % 1000 / 100 : 10);
        load_Icon(scene, 6, 2, 6, n >= 10 ? n % 100 / 10 : 10);
        load_Icon(scene, 6, 1, 6, n % 10);
        n = in.v[3];
        if (n > 99) {
            n = 99;
        }
        if (n >= 10) {
            HUD_RECORD(scene, 7)->elementIndex = 0x7C;
        } else {
            HUD_RECORD(scene, 7)->elementIndex = 0x7D;
        }
        load_Icon(scene, 7, 2, 6, n % 100 / 10);
        load_Icon(scene, 7, 1, 6, n % 10);
        n = in.v[4];
        if (n > 999) {
            n = 999;
        }
        load_Icon(scene, 8, 3, 6, n >= 100 ? n % 1000 / 100 : 10);
        load_Icon(scene, 8, 2, 6, n >= 10 ? n % 100 / 10 : 10);
        load_Icon(scene, 8, 1, 6, n % 10);
        n = in.v[5];
        if (n > 999) {
            n = 999;
        }
        if (n >= 100) {
            HUD_RECORD(scene, 9)->elementIndex = 0x7E;
        } else if (n >= 10) {
            HUD_RECORD(scene, 9)->elementIndex = 0x7F;
        } else {
            HUD_RECORD(scene, 9)->elementIndex = 0x80;
        }
        load_Icon(scene, 9, 3, 6, n % 1000 / 100);
        load_Icon(scene, 9, 2, 6, n % 100 / 10);
        load_Icon(scene, 9, 1, 6, n % 10);
        load_Icon(scene, 10, 1, 0x71, in.iconId);
        n = in.count;
        if (n > 99) {
            n = 99;
        }
        load_Icon(scene, 11, 2, 6, n >= 10 ? n % 100 / 10 : 10);
        load_Icon(scene, 11, 1, 6, n % 10);
        n = fn_8006C268(out);
        if (n > 9999) {
            n = 9999;
        }
        load_Icon(scene, 0x1D, 4, 0x74, n % 10000 / 1000);
        load_Icon(scene, 0x1D, 3, 0x74, n % 1000 / 100);
        load_Icon(scene, 0x1D, 2, 0x74, n % 100 / 10);
        load_Icon(scene, 0x1D, 1, 0x74, n % 10);
        n = fn_8006C268(out);
        if (n > 9999) {
            n = 9999;
        }
        HUD_RECORD(scene, 30)->elementIndex = ((HudDescriptorTables*)descriptors)->elementIds[(u8)fn_8006C100(n)];
        scene->state = 1;
        break;
    case 1:
        if (hudRecordFinished(HUD_RECORD(scene, 0)) != FALSE) {
            if (HUD_RECORD(scene, 1)->unk69[0] == 2) {
                if (HUD_RECORD(scene, 3)->unk69[0] == 2) {
                    HUD_RECORD(scene, 28)->playMode = UI_PLAY_FORWARD;
                    HUD_RECORD(scene, 29)->playMode = UI_PLAY_FORWARD;
                    callSfx(lbl_3_data_81FC[0x30]);
                    scene->state = 2;
                }
            }
        }
        break;
    case 2:
        if (hudRecordFinished(HUD_RECORD(scene, 29)) != FALSE) {
            HUD_RECORD(scene, 30)->playMode = UI_PLAY_FORWARD;
            callSfx(lbl_3_data_81FC[0x31]);
            scene->state = 3;
        }
        break;
    case 3:
        if (HUD_RECORD(scene, 30)->unk69[0] == 2) {
            scene->state = 4;
        }
        break;
    case 4:
        scene->_18 = 1;
        if (scene->_1A != 0) {
            scene->state = 5;
        }
        break;
    case 5:
        scene->state = 6;
        break;
    case 6:
        break;
    }
    i = 0;
    do {
        threshold = ((u16*)(descriptors + 0x438))[i];
        if ((HUD_RECORD(scene, 3)->frame >> 16) >= threshold) {
            if ((HUD_RECORD(scene, 3)->frame >> 16) == threshold) {
                callSfx(lbl_3_data_81FC[0x2F]);
            }
            if (i < 6) {
                diff = out[in.slot[i] - 1] - shown[0x12 + i];
            } else if (i == 6) {
                diff = out[6] - shown[0x12 + i];
            } else {
                diff = out[7] - shown[0x12 + i];
            }
            if (diff != 0) {
                step = diff / 3;
                if (step != 0) {
                    shown[0x12 + i] += step;
                } else {
                    shown[0x12 + i] += 1;
                }
            }
            n = shown[0x12 + i];
            if (n > 999) {
                n = 999;
            }
        } else {
            n = 0;
        }
        load_Icon(scene, i + 0x14, 3, 0x74, n % 1000 / 100);
        load_Icon(scene, i + 0x14, 2, 0x74, n % 100 / 10);
        load_Icon(scene, i + 0x14, 1, 0x74, n % 10);
        i++;
    } while (i < 8);
}

// .text:0x001274B4 size:0x6B4 mapped:0x80766548
void fn_3_1274B4(void) {
    MinigameHudScene* scene;
    u8* descriptors;
    ResultEntry* entry;
    u32 i;
    s16 score;
    s16 count;

    descriptors = (u8*)lbl_3_data_226E0;
    scene = (MinigameHudScene*)currentDrawingItem;
    if (animRelated[0x96] != 0) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    if (g_GameLogic.gameStatus == GAME_STATUS_MINIGAME_POST_MENU) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    switch (scene->state) {
    case 0:
        addGraphicsElementToScene((DrawingSceneStruct*)scene, (UIRecordDescriptor*)(descriptors + 0x448));
        if (g_Minigame._1A3C != 0) {
            HUD_RECORD(scene, 1)->elementIndex = 0xB1;
        } else {
            u16* iconTable = (u16*)(descriptors + 0x1188);
            HUD_RECORD(scene, 1)->elementIndex = iconTable[g_Minigame.GameMode_MiniGame];
        }
        if (g_Minigame._1A3C == 0 && g_Minigame.GameMode_MiniGame != MINI_GAME_ID_NONE) {
            HUD_RECORD(scene, 2)->playMode = UI_PLAY_FORWARD;
        }
        entry = fn_3_109D88();
        i = 0;
        do {
            if (g_Minigame._1A3C != 0) {
                HUD_RECORD_AT(scene, 5, i)->frame = 7 << 16;
            } else {
                u16* frameTable = (u16*)(descriptors + 0x1198);
                HUD_RECORD_AT(scene, 5, i)->frame = frameTable[g_Minigame.GameMode_MiniGame] << 16;
            }
            HUD_RECORD_AT(scene, 0x14, i)->frame = entry->rank << 16;
            load_Icon(scene, i + 0x32, 1, 0x12, i);
            score = entry->score;
            if (g_Minigame._1A3C != 0) {
                if (score > 9999) {
                    score = 9999;
                }
            } else {
                if (score > lbl_80109410[g_Minigame.GameMode_MiniGame]) {
                    score = lbl_80109410[g_Minigame.GameMode_MiniGame];
                }
            }
            score = (s16)score;
            load_Icon(scene, i * 4 + 0x41, 1, 0x16, score % 10000 / 1000);
            load_Icon(scene, i * 4 + 0x42, 1, 0x16, score % 1000 / 100);
            load_Icon(scene, i * 4 + 0x43, 1, 0x16, score % 100 / 10);
            load_Icon(scene, i * 4 + 0x44, 1, 0x16, score % 10);
            if (g_Minigame._1A3C != 0) {
                HUD_RECORD_AT(scene, 0x5F, i)->frame = (u8)fn_8006C100((s16)entry->score) << 16;
                HUD_RECORD_AT(scene, 0x5A, i)->playMode = UI_PLAY_FORWARD;
                HUD_RECORD_AT(scene, 0x64, i)->playMode = UI_PLAY_FORWARD;
            } else if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY) {
                count = entry->count;
                if (count > 999) {
                    count = 999;
                }
                if ((s16)count >= 100) {
                    load_Icon(scene, i + 0x55, 5, 6, (s16)count % 1000 / 100);
                } else {
                    load_Icon(scene, i + 0x55, 5, 6, 10);
                }
                if ((s16)count >= 10) {
                    load_Icon(scene, i + 0x55, 4, 6, (s16)count % 100 / 10);
                } else {
                    load_Icon(scene, i + 0x55, 4, 6, 10);
                }
                load_Icon(scene, i + 0x55, 3, 6, (s16)count % 10);
                HUD_RECORD_AT(scene, 0x55, i)->playMode = UI_PLAY_FORWARD;
            }
            i++;
            entry++;
        } while (i < 5);
        scene->state = 1;
        break;
    case 1:
        i = 0;
        do {
            if (i != g_Minigame._1E01[2]) {
                fn_3_125424(scene, i + 10, 10);
            }
            if ((HUD_RECORD(scene, 4)->frame >> 16) == ((u16*)(descriptors + 0x11A8))[i]) {
                if (g_Minigame.GameMode_MiniGame != MINI_GAME_ID_NONE) {
                    callSfx(lbl_3_data_81FC[0x2F]);
                } else {
                    toyPlaySound(0x1D, 0x3A);
                }
            }
            i++;
        } while (i < 5);
        break;
    }
}

// .text:0x00126604 size:0xEB0 mapped:0x80765698
void fn_3_126604(void) {
    int n;
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    int i;
    int k;
    int slot;
    int mode;

    mode = g_Minigame.GameMode_MiniGame;
    if (g_GameLogic.gameStatus == GAME_STATUS_0x28) {
        mode = 7;
    }
    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_AAB0);
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && g_GameLogic.gameStatus == GAME_STATUS_PAUSED) {
        for (i = 0; i < 6; i++) {
            HUD_RECORD(scene, i)->layer = 2;
        }
    }
    HUD_RECORD(scene, 9)->elementIndex = lbl_3_data_B0D8[g_Minigame.miniGameNumberOfParticipants - 1];
    HUD_RECORD(scene, 8)->elementIndex = lbl_3_data_B010[mode][4];
    i = 0;
    for (k = 0; k < 4; k++) {
        if (g_Minigame.playerSlots.characterIndex[k] >= 0) {
            slot = g_Minigame.playerSlots.characterIndex[k];
            HUD_RECORD_AT(scene, 0xE, i)->frame = slot << 16;
            if (g_Minigame.playerSlots.aiControlledInd[k] != 0) {
                slot += 4;
            }
            HUD_RECORD_AT(scene, 0x16, i)->frame = slot << 16;
            HUD_RECORD_AT(scene, 0x12, i)->frame = g_Minigame.playerSlots._04[i] << 16;
            i++;
            if (i >= g_Minigame.miniGameNumberOfParticipants) {
                break;
            }
        }
    }
    if (g_Minigame._1A3C != 0 || g_Minigame.multiPlayerInd != 0
        || g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        for (i = 0x25; i < 0x2A; i++) {
            HUD_RECORD(scene, i)->flags &= ~UI_FLAG_VISIBLE;
        }
    } else if (g_Minigame.soloMinigameDifficulty == MINIGAME_DIFFICULTY_SOLO_NON_CHALLENGE) {
        HUD_RECORD(scene, 0x29)->flags |= UI_FLAG_VISIBLE;
        n = lbl_803616CC[g_Minigame.GameMode_MiniGame].pointsToWin;
        HUD_RECORD(scene, 0x28)->frame = lbl_803616CC[g_Minigame.GameMode_MiniGame].rank << 16;
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_STAR_DASH) {
            HUD_RECORD(scene, 0x26)->elementIndex = 0xD;
            if (g_d_GameSettings.exhibitionMatchInd == 0) {
                load_Icon(scene, 0x26, 6, 0x12, g_Minigame.soloMinigameDifficulty + 4);
            } else {
                load_Icon(scene, 0x26, 6, 0x12, g_Minigame.soloMinigameDifficulty);
            }
            if (n > 999) {
                n = 999;
            }
            if (n < 100) {
                load_Icon(scene, 0x26, 1, 0x13, 10);
            } else {
                load_Icon(scene, 0x26, 1, 0x13, n / 100 % 10);
            }
            if (n < 10) {
                load_Icon(scene, 0x26, 2, 0x13, 10);
            } else {
                load_Icon(scene, 0x26, 2, 0x13, n / 10 % 10);
            }
            load_Icon(scene, 0x26, 3, 0x13, n % 10);
        } else if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_CHAINCHOMP_SPRINT) {
            HUD_RECORD(scene, 0x26)->elementIndex = 0xC;
            if (g_d_GameSettings.exhibitionMatchInd == 0) {
                load_Icon(scene, 0x26, 5, 0x12, g_Minigame.soloMinigameDifficulty + 4);
            } else {
                load_Icon(scene, 0x26, 5, 0x12, g_Minigame.soloMinigameDifficulty);
            }
            if (n > 99) {
                n = 99;
            }
            if (n < 10) {
                load_Icon(scene, 0x26, 1, 0x13, 10);
            } else {
                load_Icon(scene, 0x26, 1, 0x13, n / 10);
            }
            load_Icon(scene, 0x26, 2, 0x13, n % 10);
        } else if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_PIRANHA_PANIC) {
            HUD_RECORD(scene, 0x26)->elementIndex = 0xB;
            if (g_d_GameSettings.exhibitionMatchInd == 0) {
                load_Icon(scene, 0x26, 7, 0x12, g_Minigame.soloMinigameDifficulty + 4);
            } else {
                load_Icon(scene, 0x26, 7, 0x12, g_Minigame.soloMinigameDifficulty);
            }
            load_Icon(scene, 0x26, 1, 0x13, 10);
            if (n > 999) {
                n = 999;
            }
            if (n < 100) {
                load_Icon(scene, 0x26, 2, 0x13, 10);
            } else {
                load_Icon(scene, 0x26, 2, 0x13, n / 100 % 10);
            }
            if (n < 10) {
                load_Icon(scene, 0x26, 3, 0x13, 10);
            } else {
                load_Icon(scene, 0x26, 3, 0x13, n / 10 % 10);
            }
            load_Icon(scene, 0x26, 4, 0x13, n % 10);
        } else {
            HUD_RECORD(scene, 0x26)->elementIndex = 0xB;
            if (g_d_GameSettings.exhibitionMatchInd == 0) {
                load_Icon(scene, 0x26, 7, 0x12, g_Minigame.soloMinigameDifficulty + 4);
            } else {
                load_Icon(scene, 0x26, 7, 0x12, g_Minigame.soloMinigameDifficulty);
            }
            if (n > 9999) {
                n = 9999;
            }
            if (n < 1000) {
                load_Icon(scene, 0x26, 1, 0x13, 10);
            } else {
                load_Icon(scene, 0x26, 1, 0x13, n / 1000);
            }
            if (n < 100) {
                load_Icon(scene, 0x26, 2, 0x13, 10);
            } else {
                load_Icon(scene, 0x26, 2, 0x13, n / 100 % 10);
            }
            if (n < 10) {
                load_Icon(scene, 0x26, 3, 0x13, 10);
            } else {
                load_Icon(scene, 0x26, 3, 0x13, n / 10 % 10);
            }
            load_Icon(scene, 0x26, 4, 0x13, n % 10);
        }
    } else {
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY
            || g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER) {
            HUD_RECORD(scene, 0x26)->elementIndex = 0x11;
            if (g_d_GameSettings.exhibitionMatchInd == 0) {
                load_Icon(scene, 0x26, 7, 0x12, g_Minigame.soloMinigameDifficulty + 4);
            } else {
                load_Icon(scene, 0x26, 7, 0x12, g_Minigame.soloMinigameDifficulty);
            }
            if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY) {
                n = bOD_challenge_nPitches_Points[g_Minigame.soloMinigameDifficulty][1];
            } else {
                n = bB_challengePointsRequired[g_Minigame.soloMinigameDifficulty];
            }
            if (n < 1000) {
                load_Icon(scene, 0x26, 1, 0x13, 10);
            } else {
                load_Icon(scene, 0x26, 1, 0x13, n / 1000);
            }
            if (n < 100) {
                load_Icon(scene, 0x26, 2, 0x13, 10);
            } else {
                load_Icon(scene, 0x26, 2, 0x13, n / 100 % 10);
            }
            if (n < 10) {
                load_Icon(scene, 0x26, 3, 0x13, 10);
            } else {
                load_Icon(scene, 0x26, 3, 0x13, n / 10 % 10);
            }
            load_Icon(scene, 0x26, 4, 0x13, n % 10);
        } else {
            HUD_RECORD(scene, 0x26)->elementIndex = 0x10;
            if (g_d_GameSettings.exhibitionMatchInd == 0) {
                load_Icon(scene, 0x26, 3, 0x12, g_Minigame.soloMinigameDifficulty + 4);
            } else {
                load_Icon(scene, 0x26, 3, 0x12, g_Minigame.soloMinigameDifficulty);
            }
        }
        HUD_RECORD(scene, 0x27)->flags &= ~UI_FLAG_VISIBLE;
    }
    if (g_Minigame.multiPlayerInd != 0 || g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
        || g_GameLogic.gameStatus == GAME_STATUS_0x28) {
        HUD_RECORD(scene, 5)->flags &= ~UI_FLAG_VISIBLE;
    } else if (g_d_GameSettings.exhibitionMatchInd == 0) {
        load_Icon(scene, 5, 1, lbl_3_data_B010[mode][3], g_Minigame.soloMinigameDifficulty + 4);
    } else {
        load_Icon(scene, 5, 1, lbl_3_data_B010[mode][3], g_Minigame.soloMinigameDifficulty);
    }
    HUD_RECORD(scene, 3)->elementIndex = lbl_3_data_B010[mode][0];
    HUD_RECORD(scene, 4)->elementIndex = lbl_3_data_B010[mode][1];
    HUD_RECORD(scene, 5)->elementIndex = lbl_3_data_B010[mode][2];
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && g_GameLogic.gameStatus != GAME_STATUS_PAUSED) {
        load_Icon(scene, 0x20, 1, 0x116, 0xF);
        load_Icon(scene, 0x21, 1, 0x116, 0x10);
        load_Icon(scene, 0x22, 1, 0x116, 0x11);
        load_Icon(scene, 0x23, 1, 0x116, 0x12);
        load_Icon(scene, 0x24, 1, 0x116, 0x13);
        HUD_RECORD_AT(scene, 0x20, MG_BYTE(0x1A24))->elementIndex = 0xF2;
    } else {
        HUD_RECORD(scene, 6)->flags &= ~UI_FLAG_VISIBLE;
    }
    if (g_Minigame.pauseInd != 0) {
        for (i = 0; i < 6; i++) {
            HUD_RECORD(scene, i)->layer = 2;
        }
    }
    scene->state = MG_BYTE(0x1A1E);
    scene->_1E = 0;
    scene->_20 = 0;
    currentDrawingItem->func = fn_3_1258C0;
}

// .text:0x001258C0 size:0xD44 mapped:0x80764954
void fn_3_1258C0(void) {
    MinigameHudScene* scene;
    u32 status;
    int i;
    E(u8, TRANSITION_CALCULATION_TYPE) transition;

    scene = (MinigameHudScene*)currentDrawingItem;
    animRelated[0xC4] = 0;
    if (animRelated[0x96] != 0) {
        goto remove;
    }
    status = g_GameLogic.gameStatus;
    if (status == GAME_STATUS_0x29) {
        goto remove;
    }
    transition = g_GameLogic._125;
    if (transition == TRANSITION_CALCULATION_TYPE_9) {
        goto remove;
    }
    if (status == GAME_STATUS_0x28) {
        if (transition == TRANSITION_CALCULATION_TYPE_6) {
            goto remove;
        }
    } else if (transition == TRANSITION_CALCULATION_TYPE_11) {
        goto remove;
    }
    if (scene->_1E == 0) {
        scene->state = MG_BYTE(0x1A1E);
        HUD_RECORD(scene, 28)->flags &= ~UI_FLAG_VISIBLE;
        if (scene->state == 0) {
            HUD_RECORD(scene, 7)->playMode = UI_PLAY_FORWARD;
            HUD_RECORD(scene, 9)->playMode = UI_PLAY_FORWARD;
            HUD_RECORD(scene, 8)->playMode = UI_PLAY_FORWARD;
            HUD_RECORD(scene, 26)->playMode = UI_PLAY_FORWARD;
            HUD_RECORD(scene, 37)->playMode = UI_PLAY_FORWARD;
            HUD_RECORD(scene, 3)->flags &= ~UI_FLAG_VISIBLE;
            HUD_RECORD(scene, 7)->flags |= UI_FLAG_VISIBLE;
            HUD_RECORD(scene, 9)->flags |= UI_FLAG_VISIBLE;
            HUD_RECORD(scene, 8)->flags |= UI_FLAG_VISIBLE;
            HUD_RECORD(scene, 26)->flags |= UI_FLAG_VISIBLE;
            HUD_RECORD(scene, 6)->flags |= UI_FLAG_VISIBLE;
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                HUD_RECORD(scene, 28)->flags |= UI_FLAG_VISIBLE;
                HUD_RECORD(scene, 28)->playMode = UI_PLAY_FORWARD;
            }
            if (g_Minigame._190A != 0) {
                if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                    SET_MENU(0x21);
                } else {
                    SET_MENU(0x25);
                }
            } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                SET_MENU(0x30);
            } else if (g_Minigame._1A3C != 0) {
                if (g_GameLogic.gameStatus == GAME_STATUS_0x28) {
                    SET_MENU(0x39);
                } else {
                    SET_MENU(0x3B);
                }
            } else {
                SET_MENU(0x37);
            }
        } else {
            if (g_Minigame.multiPlayerInd != 0 || g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD
                || g_GameLogic.gameStatus == GAME_STATUS_0x28) {
                HUD_RECORD(scene, 5)->flags &= ~UI_FLAG_VISIBLE;
            } else if (MG_BYTE(0x1A1E) == 2) {
                HUD_RECORD(scene, 5)->flags &= ~UI_FLAG_VISIBLE;
            } else {
                HUD_RECORD(scene, 5)->flags |= UI_FLAG_VISIBLE;
            }
            HUD_RECORD(scene, 4)->frame = lbl_3_data_B060[g_Minigame.GameMode_MiniGame][MG_BYTE(0x1A20)][MG_BYTE(0x1A1E) - 1] << 16;
            if (scene->_20 == 0) {
                HUD_RECORD(scene, 3)->playMode = UI_PLAY_FORWARD;
                HUD_RECORD(scene, 3)->frame = 0;
            } else {
                HUD_RECORD(scene, 3)->playMode = UI_PLAY_BACKWARD;
                HUD_RECORD(scene, 3)->frame = 0x14 << 16;
            }
            HUD_RECORD(scene, 3)->flags |= UI_FLAG_VISIBLE;
            HUD_RECORD(scene, 7)->flags &= ~UI_FLAG_VISIBLE;
            HUD_RECORD(scene, 9)->flags &= ~UI_FLAG_VISIBLE;
            HUD_RECORD(scene, 8)->flags &= ~UI_FLAG_VISIBLE;
            HUD_RECORD(scene, 26)->flags &= ~UI_FLAG_VISIBLE;
            HUD_RECORD(scene, 6)->flags &= ~UI_FLAG_VISIBLE;
            HUD_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
            if (g_Minigame._190A != 0) {
                if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                    SET_MENU(0x22);
                } else {
                    SET_MENU(0x26);
                }
            } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                SET_MENU(0x32);
            } else if (g_GameLogic.gameStatus == GAME_STATUS_0x28) {
                SET_MENU(0x3A);
            } else {
                SET_MENU(0x38);
            }
        }
        animRelated[0xC4] = 1;
        scene->_1E = 1;
    } else if (scene->_1E == 1) {
        if (scene->state == 0) {
            if (HUD_RECORD(scene, 7)->unk69[0] == 2) {
                scene->_1E = 2;
            }
        } else if (scene->_20 == 0) {
            if ((HUD_RECORD(scene, 3)->frame >> 16) >= 10) {
                HUD_RECORD(scene, 3)->playMode = UI_PLAY_STOP;
                scene->_1E = 2;
            }
        } else {
            if ((HUD_RECORD(scene, 3)->frame >> 16) <= 10) {
                HUD_RECORD(scene, 3)->playMode = UI_PLAY_STOP;
                scene->_1E = 2;
            }
        }
        animRelated[0xC4] = 1;
    } else if (scene->_1E == 2) {
        if (scene->state == 0) {
            if (scene->state != MG_BYTE(0x1A1E)) {
                HUD_RECORD(scene, 7)->playMode = UI_PLAY_BACKWARD;
                HUD_RECORD(scene, 9)->playMode = UI_PLAY_BACKWARD;
                HUD_RECORD(scene, 8)->playMode = UI_PLAY_BACKWARD;
                HUD_RECORD(scene, 26)->playMode = UI_PLAY_BACKWARD;
                HUD_RECORD(scene, 37)->playMode = UI_PLAY_BACKWARD;
                if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                    HUD_RECORD(scene, 28)->playMode = UI_PLAY_BACKWARD;
                }
                scene->_20 = 0;
                scene->_1E = 3;
            }
        } else if (scene->state != MG_BYTE(0x1A1E)) {
            if (MG_BYTE(0x1A22) == 0) {
                HUD_RECORD(scene, 3)->playMode = UI_PLAY_FORWARD;
                scene->_20 = 0;
            } else {
                HUD_RECORD(scene, 3)->playMode = UI_PLAY_BACKWARD;
                scene->_20 = 1;
            }
            scene->_1E = 3;
        } else if (g_Minigame.pauseInd != 0
                   || (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && status == GAME_STATUS_PAUSED)) {
            if (pauseControl[0x1D4] == 5) {
                HUD_RECORD(scene, 3)->playMode = UI_PLAY_FORWARD;
                scene->_20 = 0;
                scene->_1E = 3;
            }
        }
    } else if (scene->_1E == 3) {
        if (scene->state == 0) {
            if ((HUD_RECORD(scene, 7)->frame >> 16) == 0) {
                HUD_RECORD(scene, 7)->playMode = UI_PLAY_STOP;
                HUD_RECORD(scene, 9)->playMode = UI_PLAY_STOP;
                HUD_RECORD(scene, 8)->playMode = UI_PLAY_STOP;
                HUD_RECORD(scene, 26)->playMode = UI_PLAY_STOP;
                scene->_1E = 0;
            }
        } else {
            if (scene->_20 == 0) {
                if ((HUD_RECORD(scene, 3)->frame >> 16) >= 0x14) {
                    HUD_RECORD(scene, 3)->playMode = UI_PLAY_STOP;
                    scene->_1E = 0;
                }
            } else {
                if ((HUD_RECORD(scene, 3)->frame >> 16) == 0) {
                    HUD_RECORD(scene, 3)->playMode = UI_PLAY_STOP;
                    scene->_1E = 0;
                }
            }
            HUD_RECORD(scene, 0)->playMode = UI_PLAY_BACKWARD;
        }
        if (g_Minigame.pauseInd != 0
            || (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && g_GameLogic.gameStatus == GAME_STATUS_PAUSED)) {
            if (pauseControl[0x1D4] == 5 && scene->_1E == 0) {
                goto remove;
            }
        }
        animRelated[0xC4] = 1;
    }
    if (scene->state == 0) {
        if (MG_BYTE(0x1A23) == 0) {
            HUD_RECORD(scene, 27)->playMode = UI_PLAY_FORWARD;
            for (i = 0; i < 5; i++) {
                if (MG_BYTE(0x1A24) != i) {
                    HUD_RECORD_AT(scene, 0x20, i)->elementIndex = 0xF1;
                    HUD_RECORD_AT(scene, 0x20, i)->frame = 0;
                    HUD_RECORD_AT(scene, 0x20, i)->playMode = UI_PLAY_STOP;
                } else {
                    if ((HUD_RECORD_AT(scene, 0x20, i)->frame >> 16) > 10) {
                        HUD_RECORD_AT(scene, 0x20, i)->frame = 10 << 16;
                    }
                    HUD_RECORD_AT(scene, 0x20, i)->elementIndex = 0xF2;
                    HUD_RECORD_AT(scene, 0x20, i)->playMode = UI_PLAY_BACKWARD;
                }
            }
            HUD_RECORD(scene, 30)->playMode = UI_PLAY_STOP;
            HUD_RECORD(scene, 30)->frame = 0;
        } else {
            HUD_RECORD(scene, 27)->frame = 0;
            HUD_RECORD(scene, 27)->playMode = UI_PLAY_STOP;
            for (i = 0; i < 5; i++) {
                if ((HUD_RECORD_AT(scene, 0x20, i)->frame >> 16) >= 10) {
                    HUD_RECORD_AT(scene, 0x20, i)->elementIndex = 0xF1;
                }
                if (MG_BYTE(0x1A24) != i) {
                    HUD_RECORD_AT(scene, 0x20, i)->frame = 0;
                    HUD_RECORD_AT(scene, 0x20, i)->playMode = UI_PLAY_STOP;
                } else {
                    HUD_RECORD_AT(scene, 0x20, i)->playMode = UI_PLAY_FORWARD;
                }
            }
            HUD_RECORD(scene, 30)->playMode = UI_PLAY_FORWARD;
        }
    }
    return;
remove:
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
    if (g_GameLogic.gameStatus == GAME_STATUS_0x29) {
        menuNumber[0x26] = 1;
    }
}

// .text:0x00125850 size:0x70 mapped:0x807648E4
void fn_3_125850(void) {
    DrawingSceneStruct* node = currentDrawingItem;

    addGraphicsElementToScene(node, lbl_3_data_91BC);
    g_Minigame.bODRelated = 0;
    ((MinigameHudScene*)node)->_18 = 0;
    ((MinigameHudScene*)node)->_1A = 0;
    ((MinigameHudScene*)node)->state = 0;
    currentDrawingItem->func = fn_3_125604;
}

// .text:0x00125604 size:0x24C mapped:0x80764698
void fn_3_125604(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;

    if (g_Minigame._1A40 == 0) {
        if (scene->_18 < 0xFFFE) {
            scene->_18++;
        } else {
            scene->_18 = 0xFFFF;
        }
        if (scene->state == 0) {
            if (g_Minigame._1A41 != 0) {
                g_Minigame.someGraphicFrameCountdown--;
                if (g_Minigame.someGraphicFrameCountdown <= 0) {
                    HUD_RECORD(scene, 0)->elementIndex = lbl_3_data_91FC[g_Minigame._1A41];
                    HUD_RECORD(scene, 0)->flags |= UI_FLAG_VISIBLE;
                    HUD_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
                    HUD_RECORD(scene, 0)->frame = 0;
                    if (g_Minigame._1A41 == 4) {
                        load_Icon(scene, 0, 1, 0x13C, g_Scores.Inning - 1);
                        callSfx(0x2F8);
                    }
                    scene->state = g_Minigame._1A41;
                    scene->_18 = 0;
                    g_Minigame.bODRelated = 1;
                    g_Minigame._1A41 = 0;
                }
            }
        } else {
            if (HUD_RECORD(scene, 0)->unk69[0] == 2) {
                if (scene->state == 4) {
                    fn_800362F0((DrawingSceneStruct*)scene, 0);
                }
                HUD_RECORD(scene, 0)->flags &= ~UI_FLAG_VISIBLE;
                g_Minigame.bODRelated = 0;
                g_Minigame._1A41 = 0;
                scene->state = 0;
            }
            if (scene->state == 2) {
                if (scene->_18 == 0x46) {
                    sndFXStartEx(0x1BD, lbl_800EFBA4[6], 0x3F, 0);
                }
            } else if (scene->state == 1) {
                if (scene->_18 == 1 && audioFileDescriptors.enableMusic == 1) {
                    callSfx(0x2EE);
                }
            }
        }
    } else {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    }
}

// .text:0x001254F8 size:0x10C mapped:0x8076458C
void fn_3_1254F8(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;

    if (g_GameLogic.gameStatus != GAME_STATUS_GAME_START_MOVIE) {
        g_Minigame._1E01[1] = 0;
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    switch (scene->state) {
    case 0:
        g_Minigame._1E01[1] = 1;
        addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_23894);
        HUD_RECORD(scene, 0)->elementIndex = lbl_3_data_238F4[g_Minigame.GameMode_MiniGame];
        if (g_Minigame._1A3C != 0 && g_Minigame._1E01[0x29] >= 6) {
            HUD_RECORD(scene, 1)->flags |= UI_FLAG_VISIBLE;
        }
        scene->state = 1;
        break;
    case 1:
        break;
    }
}

// .text:0x00125480 size:0x78 mapped:0x80764514
u32 fn_3_125480(MinigameHudScene* scene) {
    UIRecord* rec;
    u32 i;

    for (i = 0; i < scene->handleCount; i++) {
        rec = HUD_RECORD(scene, i);

        if (rec->playMode == UI_PLAY_FORWARD) {
            if (rec->unk69[0] != 2) {
                return 1;
            }
        } else if (rec->playMode == UI_PLAY_BACKWARD) {
            if ((rec->frame >> 16) != 0) {
                return 1;
            }
        }
    }
    return 0;
}

// .text:0x00125424 size:0x5C mapped:0x807644B8
u32 fn_3_125424(MinigameHudScene* scene, int handle, u32 targetFrame) {
    UIRecord* rec = HUD_RECORD(scene, handle);

    if ((rec->frame >> 16) < targetFrame) {
        rec->playMode = UI_PLAY_FORWARD;
        return 0;
    }
    if ((rec->frame >> 16) > targetFrame) {
        rec->playMode = UI_PLAY_BACKWARD;
        return 0;
    }
    rec->playMode = UI_PLAY_STOP;
    return 1;
}

// .text:0x0012536C size:0xB8 mapped:0x80764400
u32 fn_3_12536C(void) {
    if (animRelated[0x96] != 0 || animRelated[0xB7] != 0) {
        return TRUE;
    }
    if (g_GameLogic.gameStatus == GAME_STATUS_TRANSITION_MINIGAME_POSTGAME) {
        return TRUE;
    }
    if (g_Minigame.pauseInd != 0) {
        if (pauseControl[0x1D2] == 7 || pauseControl[0x1D2] == 9) {
            return TRUE;
        }
        if (pauseControl[0x1D2] == 0xD) {
            return TRUE;
        }
    }
    if (g_GameLogic.gameStatus == GAME_STATUS_MVP_END_GAME && g_GameLogic.FrameCountOfCurrentPitch == 0) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x00124CE0 size:0x68C mapped:0x80763D74
void fn_3_124CE0(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    u32 target;
    s16 maxTarget;

    if (fn_3_12536C()) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    switch (scene->state) {
    case 0:
        if (g_Minigame.multiPlayerInd != 0) {
            removeCurrentDrawingItem();
            return;
        } else if (g_Minigame.multiPlayerInd == 0 && g_Minigame._1A3C == 0
                   && g_Minigame.soloMinigameDifficulty == MINIGAME_DIFFICULTY_SOLO_NON_CHALLENGE) {
            scene->_1E = 1;
        } else if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY
                   || g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER) {
            scene->_1E = 0;
        } else {
            removeCurrentDrawingItem();
            return;
        }
        addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_23904);
        switch (g_Minigame.GameMode_MiniGame) {
        case MINI_GAME_ID_BOBOMB_DERBY:
            HUD_RECORD(scene, 0)->frame = 0;
            HUD_RECORD(scene, 2)->frame = 0;
            break;
        case MINI_GAME_ID_WALLBALL:
            HUD_RECORD(scene, 0)->frame = 1 << 16;
            HUD_RECORD(scene, 2)->frame = 1 << 16;
            break;
        case MINI_GAME_ID_BARREL_BATTER:
            HUD_RECORD(scene, 0)->frame = 2 << 16;
            HUD_RECORD(scene, 2)->frame = 2 << 16;
            break;
        case MINI_GAME_ID_CHAINCHOMP_SPRINT:
            HUD_RECORD(scene, 0)->frame = 4 << 16;
            HUD_RECORD(scene, 2)->frame = 4 << 16;
            break;
        case MINI_GAME_ID_PIRANHA_PANIC:
            HUD_RECORD(scene, 0)->frame = 3 << 16;
            HUD_RECORD(scene, 2)->frame = 3 << 16;
            break;
        case MINI_GAME_ID_STAR_DASH:
            HUD_RECORD(scene, 0)->frame = 5 << 16;
            HUD_RECORD(scene, 2)->frame = 5 << 16;
            break;
        }
        HUD_RECORD(scene, 3)->frame = scene->_1E << 16;
        HUD_RECORD(scene, 4)->elementIndex = 0x142 + (scene->_1E != 0 ? -1 : 0);
        HUD_RECORD(scene, 5)->frame = 0x3D << 16;
        HUD_RECORD(scene, 6)->frame = 0x3D << 16;
        HUD_RECORD(scene, 7)->frame = 0x3D << 16;
        HUD_RECORD(scene, 8)->frame = 0x3D << 16;
        scene->state = 1;
        break;
    case 1:
        if (scene->_1E != 0) {
            target = lbl_803616CC[g_Minigame.GameMode_MiniGame].pointsToWin;
        } else {
            target = g_Minigame.pointsReqToWin_challenge;
        }
        maxTarget = lbl_80109410[g_Minigame.GameMode_MiniGame];
        if (target > maxTarget) {
            target = maxTarget;
        }
        load_Icon(scene, 5, 1, 0x145, target % 10000 / 1000);
        load_Icon(scene, 6, 1, 0x145, target % 1000 / 100);
        load_Icon(scene, 7, 1, 0x145, target % 100 / 10);
        load_Icon(scene, 8, 1, 0x145, target % 10);
        switch (g_Minigame.GameMode_MiniGame) {
        case MINI_GAME_ID_BOBOMB_DERBY:
            if (g_GameLogic.gameStatus == GAME_STATUS_DEFAULT || g_GameLogic.gameStatus == GAME_STATUS_AT_BAT) {
                HUD_RECORD(scene, 1)->playMode = UI_PLAY_FORWARD;
            } else {
                HUD_RECORD(scene, 1)->playMode = UI_PLAY_BACKWARD;
            }
            break;
        case MINI_GAME_ID_WALLBALL:
            HUD_RECORD(scene, 1)->playMode = UI_PLAY_FORWARD;
            break;
        case MINI_GAME_ID_BARREL_BATTER:
            HUD_RECORD(scene, 1)->playMode = UI_PLAY_FORWARD;
            break;
        case MINI_GAME_ID_CHAINCHOMP_SPRINT:
            if (g_Minigame.ccs.chompState != 3) {
                HUD_RECORD(scene, 1)->playMode = UI_PLAY_FORWARD;
            } else {
                HUD_RECORD(scene, 1)->playMode = UI_PLAY_BACKWARD;
            }
            break;
        case MINI_GAME_ID_PIRANHA_PANIC:
            HUD_RECORD(scene, 1)->playMode = UI_PLAY_FORWARD;
            break;
        case MINI_GAME_ID_STAR_DASH:
            HUD_RECORD(scene, 1)->playMode = UI_PLAY_FORWARD;
            break;
        }
        break;
    }
}

// .text:0x00124738 size:0x5A8 mapped:0x807637CC
void fn_3_124738(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    int n;

    if (fn_3_12536C()) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    switch (scene->state) {
    case 0:
        addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_23A44);
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BARREL_BATTER) {
            load_Icon(scene, 1, 4, 0x14D, 1);
        }
        scene->state = 1;
        break;
    case 1:
        if (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT && g_GameLogic.FrameCountOfCurrentPitch == 0) {
            if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY) {
                scene->scratch[0] = g_Minigame.bODRoundStartingNumPitches - g_Minigame.miniGameTurnCounter;
                scene->scratch[1] = g_Minigame.miniGameTurnCounter;
            } else {
                scene->scratch[0] = g_Minigame.bB_pitchesRemainingInTurn;
            }
        }
        n = (s8)scene->scratch[0];
        if (n > 99) {
            n = 99;
        }
        if (n > 1) {
            HUD_RECORD(scene, 1)->frame = 0;
            if (n >= 10) {
                load_Icon(scene, 1, 1, 0x14E, n % 100 / 10);
            } else {
                load_Icon(scene, 1, 1, 0x14E, 10);
            }
            load_Icon(scene, 1, 2, 0x14E, n % 10);
            HUD_RECORD(scene, 2)->playMode = UI_PLAY_STOP;
            HUD_RECORD(scene, 2)->frame = 0;
        } else {
            HUD_RECORD(scene, 1)->frame = 1 << 16;
            HUD_RECORD(scene, 2)->playMode = UI_PLAY_FORWARD;
        }
        if (g_Minigame.GameMode_MiniGame == MINI_GAME_ID_BOBOMB_DERBY) {
            if (g_Minigame.multiPlayerInd == 0 && g_Minigame._1A3C == 0
                && g_Minigame.soloMinigameDifficulty == MINIGAME_DIFFICULTY_SOLO_NON_CHALLENGE) {
                if (g_Minigame.bODRoundStartingNumPitches <= scene->scratch[1] && scene->scratch[1] < 0x13) {
                    HUD_RECORD(scene, 1)->frame = 1 << 16;
                    HUD_RECORD(scene, 2)->playMode = UI_PLAY_STOP;
                    HUD_RECORD(scene, 2)->frame = 0;
                    HUD_RECORD(scene, 3)->playMode = UI_PLAY_FORWARD;
                } else {
                    HUD_RECORD(scene, 3)->playMode = UI_PLAY_STOP;
                    HUD_RECORD(scene, 3)->frame = 0;
                }
            }
            if (g_GameLogic.gameStatus == GAME_STATUS_DEFAULT || g_GameLogic.gameStatus == GAME_STATUS_AT_BAT) {
                if ((s8)scene->scratch[0] <= 1 && g_Pitcher.pitcherActionState >= 4) {
                    HUD_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
                } else {
                    fn_3_125424(scene, 0, 14);
                }
            } else {
                if ((HUD_RECORD(scene, 0)->frame >> 16) != 0) {
                    if (fn_3_125424(scene, 0, 0x18)) {
                        HUD_RECORD(scene, 0)->frame = 0;
                    }
                }
            }
        } else {
            if (g_Minigame.bB_pitchesRemainingInTurn == 0 && g_GameLogic.gameStatus != GAME_STATUS_DEFAULT
                && g_GameLogic.gameStatus != GAME_STATUS_AT_BAT && g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
                HUD_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
            } else {
                fn_3_125424(scene, 0, 14);
            }
        }
        break;
    }
}

// .text:0x001243A4 size:0x394 mapped:0x80763438
void minigameStateLogic(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    u32 inning;
    u32 limit;

    if (fn_3_12536C()) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    switch (scene->state) {
    case 0:
        addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_23AE4);
        switch (g_Minigame.GameMode_MiniGame) {
        case MINI_GAME_ID_BOBOMB_DERBY:
            HUD_RECORD(scene, 0)->frame = 0;
            break;
        case MINI_GAME_ID_WALLBALL:
            HUD_RECORD(scene, 0)->frame = 1 << 16;
            break;
        case MINI_GAME_ID_BARREL_BATTER:
            HUD_RECORD(scene, 0)->frame = 2 << 16;
            break;
        }
        scene->state = 1;
        break;
    case 1:
        switch (g_Minigame.GameMode_MiniGame) {
        case MINI_GAME_ID_BOBOMB_DERBY:
            inning = g_Scores.Inning;
            limit = g_Scores.inningLimit;
            break;
        case MINI_GAME_ID_WALLBALL:
            inning = g_Scores.Inning;
            limit = g_Scores.inningLimit;
            break;
        case MINI_GAME_ID_BARREL_BATTER:
            inning = g_Scores.Inning;
            limit = g_Scores.inningLimit;
            break;
        }
        if (limit > 9) {
            limit = 9;
        }
        if (inning > limit) {
            inning = limit;
        }
        load_Icon(scene, 2, 1, 0x140, inning);
        load_Icon(scene, 2, 4, 0x140, limit);
        switch (g_Minigame.GameMode_MiniGame) {
        case MINI_GAME_ID_BOBOMB_DERBY:
            if (g_GameLogic.gameStatus == GAME_STATUS_DEFAULT || g_GameLogic.gameStatus == GAME_STATUS_AT_BAT) {
                HUD_RECORD(scene, 1)->playMode = UI_PLAY_FORWARD;
            } else {
                HUD_RECORD(scene, 1)->playMode = UI_PLAY_BACKWARD;
            }
            break;
        case MINI_GAME_ID_WALLBALL:
            HUD_RECORD(scene, 1)->playMode = UI_PLAY_FORWARD;
            break;
        case MINI_GAME_ID_BARREL_BATTER:
            HUD_RECORD(scene, 1)->playMode = UI_PLAY_FORWARD;
            break;
        }
        if (lbl_80366158._28 != 0) {
            HUD_RECORD(scene, 2)->playMode = UI_PLAY_STOP;
        } else {
            HUD_RECORD(scene, 2)->playMode = UI_PLAY_FORWARD;
        }
        break;
    }
}

// .text:0x00123EBC size:0x4E8 mapped:0x80762F50
void fn_3_123EBC(void) {
    MinigameHudScene* scene;
    u8* descriptors;
    u32 n;
    u32 j;

    descriptors = (u8*)lbl_3_data_226E0;
    scene = (MinigameHudScene*)currentDrawingItem;
    if (fn_3_12536C()) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    switch (scene->state) {
    case 0:
        switch (g_Minigame.GameMode_MiniGame) {
        case MINI_GAME_ID_CHAINCHOMP_SPRINT:
            addGraphicsElementToScene((DrawingSceneStruct*)scene, (UIRecordDescriptor*)(descriptors + 0x1484));
            break;
        case MINI_GAME_ID_PIRANHA_PANIC:
            addGraphicsElementToScene((DrawingSceneStruct*)scene, (UIRecordDescriptor*)(descriptors + 0x14E4));
            break;
        case MINI_GAME_ID_STAR_DASH:
            addGraphicsElementToScene((DrawingSceneStruct*)scene, (UIRecordDescriptor*)(descriptors + 0x1544));
            break;
        }
        scene->state = 1;
        break;
    case 1:
        switch (g_Minigame.GameMode_MiniGame) {
        case MINI_GAME_ID_CHAINCHOMP_SPRINT:
            fn_3_125424(scene, 0, 12);
            if (g_Minigame.ccs.chompState == 3) {
                scene->state = 2;
            }
            break;
        case MINI_GAME_ID_PIRANHA_PANIC:
            fn_3_125424(scene, 0, 10);
            break;
        case MINI_GAME_ID_STAR_DASH:
            fn_3_125424(scene, 0, 10);
            break;
        }
        break;
    case 2:
    case 4:
        HUD_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
        if (g_Minigame.ccs.chompState != 3) {
            if (hudRecordFinished(HUD_RECORD(scene, 0)) != FALSE) {
                HUD_RECORD(scene, 0)->frame = 0;
                scene->state = 1;
            }
        }
        break;
    }
    n = g_Minigame.minigameFramesRemaining * 100 / 60;
    if (n > 9999) {
        n = 9999;
    }
    j = 0;
    do {
        load_Icon(scene, 1, j * 4 + 1, 0x138, n % 10000 / 1000);
        load_Icon(scene, 1, j * 4 + 2, 0x138, n % 1000 / 100);
        load_Icon(scene, 1, j * 4 + 3, 0x138, n % 100 / 10);
        load_Icon(scene, 1, j * 4 + 4, 0x138, n % 10);
        j++;
    } while (j < 2);
    if (n < 1000) {
        if (lbl_80366158._28 != 0) {
            HUD_RECORD(scene, 1)->playMode = UI_PLAY_STOP;
        } else {
            HUD_RECORD(scene, 1)->playMode = UI_PLAY_FORWARD;
        }
    } else {
        HUD_RECORD(scene, 1)->frame = 0;
        HUD_RECORD(scene, 1)->playMode = UI_PLAY_STOP;
    }
}

// .text:0x00123990 size:0x52C mapped:0x80762A24
void fn_3_123990(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    u32 i;
    s16 x;
    s16 y;

    if (fn_3_12536C()) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    switch (scene->state) {
    case 0:
        addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_23C84);
        i = 0;
        do {
            switch (g_Minigame.GameMode_MiniGame) {
            case MINI_GAME_ID_WALLBALL:
                HUD_RECORD(scene, i)->elementIndex = 0xB3;
                break;
            case MINI_GAME_ID_CHAINCHOMP_SPRINT:
                HUD_RECORD(scene, i)->elementIndex = 0xB5;
                break;
            case MINI_GAME_ID_PIRANHA_PANIC:
                HUD_RECORD(scene, i)->elementIndex = 0xB4;
                break;
            case MINI_GAME_ID_STAR_DASH:
                HUD_RECORD(scene, i)->elementIndex = 0xB6;
                break;
            }
            i++;
        } while (i < 4);
        i = 0;
        do {
            if (g_Minigame.playerSlots.characterIndex[i] < 0) {
                HUD_RECORD(scene, i)->flags &= ~UI_FLAG_VISIBLE;
            } else if (g_Minigame.playerSlots.aiControlledInd[i] != 0) {
                load_Icon(scene, i, 1, 6, g_Minigame.playerSlots.characterIndex[i] + 4);
            } else {
                load_Icon(scene, i, 1, 6, g_Minigame.playerSlots.characterIndex[i]);
            }
            i++;
        } while (i < 4);
        scene->state = 1;
        break;
    case 1:
        i = 0;
        do {
            if (g_Minigame.playerSlots.characterIndex[i] >= 0) {
                switch (g_Minigame.GameMode_MiniGame) {
                case MINI_GAME_ID_WALLBALL:
                    fn_800528C0(g_Pitcher.pitcher.x, 0.0f, g_Pitcher.pitcher.z, &x, &y);
                    if (i == (s8)g_Minigame.minigamePlayerSelectedOrder && g_Pitcher.pitcherActionState == 1) {
                        HUD_RECORD(scene, i)->flags |= UI_FLAG_VISIBLE;
                    } else {
                        HUD_RECORD(scene, i)->flags &= ~UI_FLAG_VISIBLE;
                    }
                    break;
                case MINI_GAME_ID_CHAINCHOMP_SPRINT:
                    fn_800528C0(g_Runners[i].position.x, g_Runners[i].position.y, g_Runners[i].position.z, &x, &y);
                    if (g_GameLogic.gameStatus == GAME_STATUS_TRANSITION_MINIGAME_TO_BATTING) {
                        HUD_RECORD(scene, i)->flags |= UI_FLAG_VISIBLE;
                    } else {
                        HUD_RECORD(scene, i)->flags &= ~UI_FLAG_VISIBLE;
                    }
                    break;
                case MINI_GAME_ID_PIRANHA_PANIC:
                case MINI_GAME_ID_STAR_DASH:
                    fn_800528C0(g_Fielders[(s8)g_Minigame.minigameFielderIndex[i]].pos.x,
                                g_Fielders[(s8)g_Minigame.minigameFielderIndex[i]].pos.y,
                                g_Fielders[(s8)g_Minigame.minigameFielderIndex[i]].pos.z, &x, &y);
                    if (g_GameLogic.gameStatus == GAME_STATUS_TRANSITION_MINIGAME_TO_BATTING) {
                        HUD_RECORD(scene, i)->flags |= UI_FLAG_VISIBLE;
                    } else {
                        HUD_RECORD(scene, i)->flags &= ~UI_FLAG_VISIBLE;
                    }
                    break;
                default:
                    x = 0x28A;
                    y = 0x1EA;
                    HUD_RECORD(scene, i)->flags &= ~UI_FLAG_VISIBLE;
                    break;
                }
                HUD_RECORD(scene, i)->pos.x = x;
                HUD_RECORD(scene, i)->pos.y = y;
            }
            i++;
        } while (i < 4);
        break;
    }
}

// .text:0x001235B8 size:0x3D8 mapped:0x8076264C
void fn_3_1235B8(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    u32 n;
    u32 digit;

    if (fn_3_12536C()) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    switch (scene->state) {
    case 0:
        addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_23D24);
        scene->state = 1;
        break;
    case 1:
        if (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT
            && g_Minigame.bODCharacterHRStreakTracker[g_Minigame.rosterID][0] >= 2) {
            HUD_RECORD(scene, 0)->frame = (g_Batter.batterHand != 0) << 16;
            n = g_Minigame.bODCharacterHRStreakTracker[g_Minigame.rosterID][0];
            if (n > 99) {
                n = 99;
            }
            if (n < 10) {
                HUD_RECORD(scene, 1)->playMode = UI_PLAY_FORWARD;
                digit = n % 10;
                load_Icon(scene, 1, 4, 0x104, digit);
                load_Icon(scene, 1, 5, 0x104, digit);
                load_Icon(scene, 1, 6, 0x104, digit);
                HUD_RECORD(scene, 2)->playMode = UI_PLAY_STOP;
                HUD_RECORD(scene, 2)->frame = 0;
            } else {
                HUD_RECORD(scene, 2)->playMode = UI_PLAY_FORWARD;
                digit = n % 10;
                load_Icon(scene, 2, 4, 0x104, digit);
                load_Icon(scene, 2, 5, 0x104, digit);
                load_Icon(scene, 2, 6, 0x104, digit);
                digit = n % 100 / 10;
                load_Icon(scene, 2, 7, 0x104, digit);
                load_Icon(scene, 2, 8, 0x104, digit);
                load_Icon(scene, 2, 9, 0x104, digit);
                HUD_RECORD(scene, 1)->playMode = UI_PLAY_STOP;
                HUD_RECORD(scene, 1)->frame = 0;
            }
        } else {
            HUD_RECORD(scene, 1)->playMode = UI_PLAY_BACKWARD;
            HUD_RECORD(scene, 2)->playMode = UI_PLAY_BACKWARD;
        }
        break;
    }
}

// .text:0x001231D4 size:0x3E4 mapped:0x80762268
void fn_3_1231D4(void) {
    DrawingSceneStruct* node = currentDrawingItem;
    MinigameHudScene* parent = (MinigameHudScene*)node->currentDrawingItem;
    MinigameHudScene* scene = (MinigameHudScene*)node;
    u32 total;

    if (fn_3_12536C()) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    switch (scene->state) {
    case 0:
        addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_23DA4);
        scene->state = 1;
        break;
    case 1:
        HUD_RECORD(scene, 0)->playMode = UI_PLAY_BACKWARD;
        if (parent->_1A == 1) {
            if (g_Minigame.bOD_KingBombInd != 0) {
                if (g_Minigame.bODCharacterHRStreakTracker[g_Minigame.rosterID][0] >= 2) {
                    HUD_RECORD(scene, 0)->elementIndex = 0x164;
                    HUD_RECORD(scene, 1)->anchorSub = 0;
                } else {
                    HUD_RECORD(scene, 0)->elementIndex = 0x163;
                    HUD_RECORD(scene, 1)->anchorSub = 0;
                }
                total = lbl_3_data_213EC[7];
                if (total > 9999) {
                    total = 9999;
                }
                if (total >= 1000) {
                    load_Icon(scene, 1, 4, 0x167, total % 10000 / 1000);
                } else if (total >= 100) {
                    load_Icon(scene, 1, 4, 0x167, 11);
                } else {
                    load_Icon(scene, 1, 4, 0x167, 10);
                }
                if (total >= 100) {
                    load_Icon(scene, 1, 3, 0x167, total % 1000 / 100);
                } else if (total >= 10) {
                    load_Icon(scene, 1, 3, 0x167, 11);
                } else {
                    load_Icon(scene, 1, 3, 0x167, 10);
                }
                if (total >= 10) {
                    load_Icon(scene, 1, 2, 0x167, total % 100 / 10);
                } else {
                    load_Icon(scene, 1, 2, 0x167, 11);
                }
                load_Icon(scene, 1, 1, 0x167, total % 10);
                scene->state = 2;
            }
        }
        break;
    case 2:
        HUD_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
        if (parent->_1A != 1) {
            scene->state = 1;
        }
        break;
    }
}

// .text:0x00122D24 size:0x4B0 mapped:0x80761DB8
void fn_3_122D24(void) {
    DrawingSceneStruct* node = currentDrawingItem;
    MinigameHudScene* parent = (MinigameHudScene*)node->currentDrawingItem;
    MinigameHudScene* scene = (MinigameHudScene*)node;
    u32 streak;
    u32 total;

    if (fn_3_12536C()) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    switch (scene->state) {
    case 0:
        addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_23E04);
        scene->state = 1;
        break;
    case 1:
        HUD_RECORD(scene, 0)->playMode = UI_PLAY_BACKWARD;
        if (parent->_1A == 1) {
            streak = g_Minigame.bODCharacterHRStreakTracker[g_Minigame.rosterID][0];
            if (streak < 2) {
                break;
            }
            if (g_Minigame.bOD_KingBombInd != 0) {
                HUD_RECORD(scene, 0)->elementIndex = 0x164;
                HUD_RECORD(scene, 1)->anchorSub = 1;
            } else {
                HUD_RECORD(scene, 0)->elementIndex = 0x163;
                HUD_RECORD(scene, 1)->anchorSub = 0;
            }
            streak = g_Minigame.bODCharacterHRStreakTracker[g_Minigame.rosterID][0];
            if (streak > 99) {
                streak = 99;
            }
            if (streak >= 10) {
                load_Icon(scene, 1, 6, 0x166, streak % 100 / 10);
            } else {
                load_Icon(scene, 1, 6, 0x166, 10);
            }
            load_Icon(scene, 1, 5, 0x166, streak % 10);
            total = lbl_3_data_213EC[8] * g_Minigame.bODCharacterHRStreakTracker[g_Minigame.rosterID][0];
            if (total > 9999) {
                total = 9999;
            }
            if (total >= 1000) {
                load_Icon(scene, 1, 4, 0x167, total % 10000 / 1000);
            } else if (total >= 100) {
                load_Icon(scene, 1, 4, 0x167, 11);
            } else {
                load_Icon(scene, 1, 4, 0x167, 10);
            }
            if (total >= 100) {
                load_Icon(scene, 1, 3, 0x167, total % 1000 / 100);
            } else if (total >= 10) {
                load_Icon(scene, 1, 3, 0x167, 11);
            } else {
                load_Icon(scene, 1, 3, 0x167, 10);
            }
            if (total >= 10) {
                load_Icon(scene, 1, 2, 0x167, total % 100 / 10);
            } else {
                load_Icon(scene, 1, 2, 0x167, 11);
            }
            load_Icon(scene, 1, 1, 0x167, total % 10);
            scene->state = 2;
        }
        break;
    case 2:
        HUD_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
        if (parent->_1A != 1) {
            scene->state = 1;
        }
        break;
    }
}

// .text:0x001226D4 size:0x650 mapped:0x80761768
void fn_3_1226D4(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    MiniGameStruct* mg = &g_Minigame;
    u32 n;
    u32 digit;
    u32 k;
    int diff;

    if (fn_3_12536C()) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    switch (scene->state) {
    case 0:
        insertGraphicDrawingFunction(fn_3_122D24, ((DrawingSceneStruct*)scene)->priority);
        insertGraphicDrawingFunction(fn_3_1231D4, ((DrawingSceneStruct*)scene)->priority);
        addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_23E64);
        scene->state = 1;
        break;
    case 1:
        HUD_RECORD(scene, 0)->playMode = UI_PLAY_STOP;
        HUD_RECORD(scene, 0)->frame = 0;
        HUD_RECORD(scene, 1)->playMode = UI_PLAY_STOP;
        HUD_RECORD(scene, 1)->frame = 0;
        HUD_RECORD(scene, 2)->playMode = UI_PLAY_STOP;
        HUD_RECORD(scene, 2)->frame = 0;
        HUD_RECORD(scene, 3)->playMode = UI_PLAY_STOP;
        HUD_RECORD(scene, 3)->frame = 0;
        HUD_RECORD(scene, 4)->playMode = UI_PLAY_STOP;
        HUD_RECORD(scene, 4)->frame = 0;
        if (mg->_1DF6[1] != 0) {
            mg->_1DF6[1] = 0;
            scene->_18 = 0;
            scene->_1A = 0;
            scene->state = 2;
        }
        break;
    case 2:
        HUD_RECORD(scene, 1)->playMode = UI_PLAY_FORWARD;
        HUD_RECORD(scene, 1)->frame = 0;
        HUD_RECORD(scene, 2)->playMode = UI_PLAY_FORWARD;
        HUD_RECORD(scene, 2)->frame = 0;
        HUD_RECORD(scene, 3)->playMode = UI_PLAY_FORWARD;
        HUD_RECORD(scene, 3)->frame = 0;
        HUD_RECORD(scene, 4)->playMode = UI_PLAY_FORWARD;
        HUD_RECORD(scene, 4)->frame = 0;
        scene->state = 3;
        break;
    case 3:
        if (fn_3_125424(scene, 0, 0x10)) {
            if (scene->_18 < 0xFFFE) {
                scene->_18++;
            } else {
                scene->_18 = 0xFFFF;
            }
            if (scene->_18 >= lbl_3_data_2145C[scene->_1A]) {
                scene->_18 = 0;
                scene->_1A++;
            }
            if (scene->_1A == 2) {
                scene->state = 4;
            }
        }
        break;
    case 4:
        if (hudRecordFinished(HUD_RECORD(scene, 4)) != FALSE && HUD_RECORD(scene, 3)->unk69[0] == 2
            && HUD_RECORD(scene, 2)->unk69[0] == 2 && HUD_RECORD(scene, 1)->unk69[0] == 2) {
            HUD_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
            scene->state = 5;
        }
        break;
    case 5:
        if (HUD_RECORD(scene, 0)->unk69[0] == 2) {
            scene->state = 1;
        }
        break;
    }
    if (scene->_1A != 0) {
        diff = g_Minigame.miniGameLatestPoints[g_Minigame.rosterID] - scene->_1E;
        if (diff != 0) {
            if (diff / 4 != 0) {
                scene->_1E += diff / 4;
            } else {
                scene->_1E += diff / __abs(diff);
            }
        }
    } else {
        scene->_1E = g_Ball.Hit_HorizontalPower;
    }
    n = scene->_1E;
    if (n > 999) {
        n = 999;
    }
    if (n >= 100) {
        HUD_RECORD(scene, 0)->elementIndex = 0x107;
    } else if (n >= 10) {
        HUD_RECORD(scene, 0)->elementIndex = 0x109;
    } else {
        HUD_RECORD(scene, 0)->elementIndex = 0x10A;
    }
    digit = n % 1000 / 100;
    k = 1;
    do {
        load_Icon(scene, 4, k, 0x11B, digit);
        k++;
    } while (k <= 3);
    digit = n % 100 / 10;
    k = 1;
    do {
        load_Icon(scene, 3, k, 0x11B, digit);
        k++;
    } while (k <= 3);
    digit = n % 10;
    k = 1;
    do {
        load_Icon(scene, 2, k, 0x11B, digit);
        k++;
    } while (k <= 3);
}

// .text:0x00122334 size:0x3A0 mapped:0x807613C8
void fn_3_122334(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    MiniGameStruct* mg = &g_Minigame;
    int diff;
    u32 n;

    if (fn_3_12536C()) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    switch (scene->state) {
    case 0:
        addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_23F24);
        scene->state = 1;
        break;
    case 1:
        if (mg->_1DF6[1] != 0) {
            scene->_1E = 1;
        }
        if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL) {
            if (scene->_1E != 0) {
                HUD_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
            } else {
                fn_3_125424(scene, 0, 10);
            }
            if (g_Ball.deadBallReason != 0 && g_Ball.bODQualifyingHitInd != 0) {
                diff = g_Ball.Hit_HorizontalPower - scene->_20;
                if (diff != 0) {
                    if (diff / 4 != 0) {
                        scene->_20 += diff / 4;
                    } else {
                        scene->_20 += diff / __abs(diff);
                    }
                }
            } else if (g_Ball.AtBat_ContactResult != 1 && g_Ball.hitWallInd == 0) {
                scene->_20 = g_Ball.ballDistanceFromHome;
            }
            n = scene->_20;
            if (n > 999) {
                n = 999;
            }
            if (n >= 100) {
                load_Icon(scene, 0, 3, 0x169, n % 1000 / 100);
            } else {
                load_Icon(scene, 0, 3, 0x169, 10);
            }
            if (n >= 10) {
                load_Icon(scene, 0, 2, 0x169, n % 100 / 10);
            } else {
                load_Icon(scene, 0, 2, 0x169, 10);
            }
            load_Icon(scene, 0, 1, 0x169, n % 10);
        } else {
            HUD_RECORD(scene, 0)->playMode = UI_PLAY_STOP;
            HUD_RECORD(scene, 0)->frame = 0;
            scene->_1E = 0;
            scene->_20 = 0;
        }
        break;
    }
}

// .text:0x00121908 size:0xA2C mapped:0x8076099C
void fn_3_121908(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    MiniGameStruct* mg = &g_Minigame;
    UIRecord* rec;
    u32 i;
    u32 n;
    u8 playMode;
    u32 tier;
    int pitchType;

    if (fn_3_12536C()) {
        if (scene->state != 0) {
            if (scene->sndHandle != 0xFFFFFFFF) {
                sndFXKeyOff(scene->sndHandle);
                sndFXCtrl(scene->sndHandle, 7, 0);
                scene->sndHandle = 0xFFFFFFFF;
            }
        }
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    if (scene->sndHandle != 0xFFFFFFFF) {
        sndFXCtrl(scene->sndHandle, 7, g_Minigame.pauseInd != 0 ? 0 : lbl_3_data_84F4[0x1C]);
    }
    switch (scene->state) {
    case 0:
        addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_23F64);
        HUD_RECORD(scene, 8)->flags &= ~UI_FLAG_VISIBLE;
        scene->_1E = random_fn_3_9EE24(6);
        scene->sndHandle = 0xFFFFFFFF;
        scene->state = 1;
    case 1:
        mg->_1DF4 = 0;
        if (g_GameLogic.gameStatus == GAME_STATUS_AT_BAT && g_Pitcher.pitcherActionState == 1) {
            scene->state = 2;
        }
        break;
    case 2:
        if (g_Batter.batterHand != 0) {
            HUD_RECORD(scene, 0)->elementIndex = 0x156;
            HUD_RECORD(scene, 1)->elementIndex = 0x153;
            HUD_RECORD(scene, 6)->elementIndex = 0x151;
            HUD_RECORD(scene, 7)->frame = 0;
        } else {
            HUD_RECORD(scene, 0)->elementIndex = 0x157;
            HUD_RECORD(scene, 1)->elementIndex = 0x154;
            HUD_RECORD(scene, 6)->elementIndex = 0x152;
            HUD_RECORD(scene, 7)->frame = 1 << 16;
        }
        if (g_Minigame.multiPlayerInd == 0 && g_Minigame._1A3C == 0) {
            if (g_Minigame.multiPlayerInd == 0 && g_Minigame._1A3C == 0
                && g_Minigame.soloMinigameDifficulty == MINIGAME_DIFFICULTY_SOLO_NON_CHALLENGE) {
                tier = g_Minigame.miniGameTurnCounter / 5;
                if (tier >= 4) {
                    tier = 3;
                }
            } else {
                tier = g_Minigame.soloMinigameDifficulty;
            }
            if (g_Minigame.miniGameTurnCounter % 10 == g_Minigame._1AD8) {
                scene->_20 = 3;
            } else {
                scene->_20 = RandomIndexFromWeights(&lbl_3_data_21468[tier * 6], 6);
            }
            scene->_22 = 1;
        } else if (g_Minigame._1A3C != 0 && g_Minigame._1907 == 1
                   && g_Minigame.playerSlots.aiControlledInd[g_Minigame.rosterID] == 0) {
            if (g_Minigame.miniGameTurnCounter % 10 == g_Minigame._1AD8 && g_Scores.Inning == g_Minigame._1AD9) {
                scene->_20 = 3;
            } else {
                scene->_20 = RandomIndexFromWeights(lbl_3_data_21480, 6);
            }
            scene->_22 = 1;
        } else {
            scene->_20 = random_fn_3_9EE24(6);
            scene->_22 = 1;
        }
        scene->_18 = 0;
        scene->_1A = 0;
        scene->state = 3;
    case 3:
        playMode = g_Minigame.pauseInd == 0;
        HUD_RECORD(scene, 1)->playMode = playMode;
        HUD_RECORD(scene, 6)->playMode = playMode;
        if (hudRecordFinished(HUD_RECORD(scene, 6)) != FALSE) {
            if (HUD_RECORD(scene, 1)->unk69[0] == 2) {
                scene->sndHandle = callSfx(lbl_3_data_81FC[0x1C]);
                scene->state = 4;
            }
        }
        break;
    case 4:
        if (scene->_18 < 0xFFFE) {
            scene->_18++;
        } else {
            scene->_18 = 0xFFFF;
        }
        if (g_Minigame._1907 - (g_Minigame.playerSlots.aiControlledInd[g_Minigame.rosterID] == 0)) {
            if (scene->_18 >= 0x6E) {
                if (lbl_3_data_21460[(scene->_1E + 1U) % 7] == scene->_20) {
                    scene->_1A = 1;
                }
            }
            i = 0;
            do {
                if (g_Minigame.playerSlots.characterIndex[i] >= 0 && g_Minigame.playerSlots.characterIndex[i] < 4
                    && i != g_Minigame.rosterID && g_Minigame.playerSlots.aiControlledInd[i] == 0
                    && g_Minigame.pauseInd == 0
                    && (g_Controls[g_Minigame.playerSlots.characterIndex[i]].newButtonInput & INPUT_BUTTON_A)) {
                    scene->_1A = 1;
                    break;
                }
                i++;
            } while (i < 4);
            if (scene->_1A == 0) {
                HUD_RECORD(scene, 8)->flags |= UI_FLAG_VISIBLE;
            } else {
                HUD_RECORD(scene, 8)->flags &= ~UI_FLAG_VISIBLE;
            }
        } else {
            if (scene->_18 >= 0x32) {
                if (lbl_3_data_21460[(scene->_1E + 1U) % 7] == scene->_20) {
                    scene->_1A = 1;
                }
            }
        }
        HUD_RECORD(scene, 2)->playMode = g_Minigame.pauseInd == 0;
        if (hudRecordFinished(HUD_RECORD(scene, 2)) != FALSE) {
            HUD_RECORD(scene, 2)->frame = 0;
            scene->_1E = (scene->_1E + 1U) % 7;
            if (scene->_1A != 0) {
                HUD_RECORD(scene, 2)->playMode = UI_PLAY_STOP;
                sndFXKeyOff(scene->sndHandle);
                sndFXCtrl(scene->sndHandle, 7, 0);
                scene->sndHandle = 0xFFFFFFFF;
                callSfx(lbl_3_data_81FC[0x1D]);
                scene->state = 5;
            }
        }
        break;
    case 5:
        HUD_RECORD(scene, 3)->playMode = g_Minigame.pauseInd == 0;
        if (hudRecordFinished(HUD_RECORD(scene, 3)) != FALSE) {
            HUD_RECORD(scene, 3)->frame = 0;
            HUD_RECORD(scene, 3)->playMode = UI_PLAY_STOP;
            scene->state = 6;
        }
        break;
    case 6:
        playMode = 4;
        if (g_Minigame.pauseInd != 0) {
            playMode = 0;
        }
        HUD_RECORD(scene, 1)->playMode = playMode;
        HUD_RECORD(scene, 6)->playMode = playMode;
        if ((HUD_RECORD(scene, 6)->frame >> 16) == 0 && (HUD_RECORD(scene, 1)->frame >> 16) == 0) {
            mg->_1DF4 = 1;
            mg->bODPitchType = lbl_3_data_21460[scene->_1E];
            if (mg->bODPitchType == 5) {
                do {
                    mg->bODPitchType = random_fn_3_9EE24(5);
                } while (scene->_22 != 0 && mg->bODPitchType == 3);
                mg->_1DF6[0] = 1;
            } else {
                mg->_1DF6[0] = 0;
            }
            scene->state = 7;
        }
        break;
    case 7:
        if (g_Pitcher.pitcherActionState != 1) {
            scene->state = 1;
        }
        break;
    }
    n = lbl_3_data_21460[scene->_1E];
    load_Icon(scene, 3, 1, 0x15B, n);
    load_Icon(scene, 3, 2, 0x15C, n);
    n = lbl_3_data_21460[(scene->_1E + 1U) % 7];
    load_Icon(scene, 4, 1, 0x15B, n);
    load_Icon(scene, 4, 2, 0x15C, n);
}

// .text:0x00121304 size:0x604 mapped:0x80760398
void fn_3_121304(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    int leader;
    u32 flag;
    s8 slot;
    int character;
    s16* shown;
    int diff;
    u32 n;
    u32 i;
    u32 changed = 0;

    if (fn_3_12536C()) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    } else {
        switch (scene->state) {
        case 0:
            addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_240A4);
            i = 0;
            do {
                slot = g_Minigame.playerSlots._14[i];
                if (slot < 0) {
                    HUD_RECORD_AT(scene, 1, i)->flags &= ~UI_FLAG_VISIBLE;
                } else {
                    character = g_Minigame.playerSlots.characterIndex[slot];
                    load_Icon(scene, 9 + i, 1, 0x65, character);
                    HUD_RECORD_AT(scene, 0x11, i)->frame = inMemRoster[0][character].stats.CharID << 16;
                }
                i++;
            } while (i < 4);
            i = 0;
            do {
                HUD_RECORD_AT(scene, 0x2D, i)->flags &= ~UI_FLAG_VISIBLE;
                i++;
            } while (i < 4);
            scene->state = 1;
            break;
        case 1:
            leader = fn_3_107CD0();
            flag = fn_3_107C88();
            i = 0;
            do {
                slot = g_Minigame.playerSlots._14[i];
                if (slot >= 0) {
                    shown = &g_Minigame.minigamePoints_current_Latest[slot][0];
                    diff = g_Minigame.miniGameCurrentPoints[slot] - *shown;
                    if (diff != 0) {
                        if (diff > 0) {
                            scene->scratch[slot] = 1;
                        }
                        if (diff / 8 != 0) {
                            *shown += diff / 8;
                        } else {
                            *shown += diff / __abs(diff);
                        }
                        changed = 1;
                    } else {
                        *shown = g_Minigame.miniGameCurrentPoints[slot];
                        if (scene->scratch[slot] != 0) {
                            scene->scratch[slot] = 0;
                            HUD_RECORD_AT(scene, 0x19, i)->frame = 0;
                            HUD_RECORD_AT(scene, 0x19, i)->playMode = UI_PLAY_FORWARD;
                            HUD_RECORD_AT(scene, 0x1D, i * 4)->frame = 0;
                            HUD_RECORD_AT(scene, 0x1E, i * 4)->frame = 0;
                            HUD_RECORD_AT(scene, 0x1F, i * 4)->frame = 0;
                            HUD_RECORD_AT(scene, 0x20, i * 4)->frame = 0;
                        }
                    }
                    n = *shown;
                    if (n > 9999) {
                        n = 9999;
                    }
                    load_Icon(scene, i * 4 + 0x1D, 1, 0x66, n % 10000 / 1000);
                    load_Icon(scene, i * 4 + 0x1E, 1, 0x66, n % 1000 / 100);
                    load_Icon(scene, i * 4 + 0x1F, 1, 0x66, n % 100 / 10);
                    load_Icon(scene, i * 4 + 0x20, 1, 0x66, n % 10);
                    if (i == g_Minigame.turnNumberWithinRound) {
                        fn_3_125424(scene, i + 1, 10);
                    } else {
                        fn_3_125424(scene, i + 1, 0);
                    }
                    if (flag == 0 && *shown == g_Minigame.minigamePoints_current_Latest[leader][0]) {
                        HUD_RECORD_AT(scene, 0x2D, i)->flags |= UI_FLAG_VISIBLE;
                    } else {
                        HUD_RECORD_AT(scene, 0x2D, i)->flags &= ~UI_FLAG_VISIBLE;
                    }
                }
                i++;
            } while (i < 4);
            break;
        }
        if (changed != 0) {
            sndFXStartEx(0x1C0, lbl_800EFBA4[9], 0x3F, 0);
        }
    }
}

// .text:0x00120FF8 size:0x30C mapped:0x8076008C
void fn_3_120FF8(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    UIRecord* rec;
    u32 n;

    if (fn_3_12536C()) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    switch (scene->state) {
    case 0:
        addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_246E4);
        HUD_RECORD(scene, 2)->frame = 13 << 16;
        scene->_1E = scene->_20 = g_Scores.inningLimit;
        scene->state = 1;
        break;
    case 1:
        if (g_GameLogic.gameStatus == GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY) {
            scene->_1E = g_Scores.inningLimit - (g_Scores.Inning - 1);
        }
        n = scene->_1E;
        if (n > 9) {
            n = 9;
        }
        load_Icon(scene, 1, 1, 0x14E, n % 10);
        rec = HUD_RECORD(scene, 0);
        if ((rec->frame >> 16) < 10) {
            rec->playMode = UI_PLAY_FORWARD;
        } else if ((rec->frame >> 16) > 10) {
            rec->playMode = UI_PLAY_BACKWARD;
        } else {
            rec->playMode = UI_PLAY_STOP;
        }
        if (scene->_20 != scene->_1E) {
            if (scene->_20 < scene->_1E) {
                HUD_RECORD(scene, 2)->playMode = UI_PLAY_FORWARD;
                HUD_RECORD(scene, 2)->frame = 0;
            } else if (scene->_20 - scene->_1E == 2) {
                HUD_RECORD(scene, 3)->playMode = UI_PLAY_FORWARD;
                HUD_RECORD(scene, 3)->frame = 0;
                HUD_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
                scene->state = 2;
            }
            scene->_20 = scene->_1E;
        }
        break;
    case 2:
        if (hudRecordFinished(HUD_RECORD(scene, 0)) != FALSE) {
            HUD_RECORD(scene, 0)->frame = 10 << 16;
            scene->state = 1;
        }
        break;
    }
}

// .text:0x00120F5C size:0x9C mapped:0x8075FFF0
int fn_3_120F5C(void) {
    s16 multiplier = 1;

    if (g_Minigame.multiPlayerInd != 0 || g_Minigame._1A3C != 0
        || g_Minigame.soloMinigameDifficulty != MINIGAME_DIFFICULTY_SOLO_NON_CHALLENGE) {
        if (g_Scores.Inning == g_Scores.inningLimit) {
            multiplier = lbl_3_data_21672;
        }
    }
    if (g_Minigame.wallBall_hitNoteBlock == 1) {
        return lbl_3_data_21654[10] * multiplier;
    }
    return g_Minigame.miniGameLatestPoints[(s8)g_Minigame.minigamePlayerSelectedOrder] * multiplier;
}

// .text:0x0012089C size:0x6C0 mapped:0x8075F930
void fn_3_12089C(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    u32 n;

    if (fn_3_12536C()) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    if (g_GameLogic.gameStatus == GAME_STATUS_DEFAULT) {
        scene->_1E = 1;
    }
    switch (scene->state) {
    case 0:
        addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_24784);
        scene->state = 1;
        break;
    case 1:
        HUD_RECORD(scene, 3)->playMode = UI_PLAY_STOP;
        HUD_RECORD(scene, 3)->frame = 0;
        HUD_RECORD(scene, 0)->playMode = UI_PLAY_STOP;
        HUD_RECORD(scene, 0)->frame = 0;
        HUD_RECORD(scene, 1)->playMode = UI_PLAY_STOP;
        HUD_RECORD(scene, 1)->frame = 0;
        HUD_RECORD(scene, 2)->playMode = UI_PLAY_STOP;
        HUD_RECORD(scene, 2)->frame = 0;
        HUD_RECORD(scene, 4)->playMode = UI_PLAY_STOP;
        HUD_RECORD(scene, 4)->frame = 0;
        if (g_GameLogic.gameStatus != GAME_STATUS_AT_BAT) {
            break;
        }
        if (g_Pitcher.pitcherActionState != 4 && g_Minigame.ballStoppedBreakingWallsInd == 0) {
            break;
        }
        if (g_Minigame.wallBall_hitBowserWall != 0) {
            callSfx(0x300);
            HUD_RECORD(scene, 2)->playMode = UI_PLAY_FORWARD;
            if (g_Minigame.multiPlayerInd != 0 || g_Minigame._1A3C != 0
                || g_Minigame.soloMinigameDifficulty != MINIGAME_DIFFICULTY_SOLO_NON_CHALLENGE) {
                n = g_Minigame.miniGameCurrentPoints[(s8)g_Minigame.minigamePlayerSelectedOrder] / 2;
                if (n != 0) {
                    if (n > 999) {
                        n = 999;
                    }
                    if (n >= 100) {
                        load_Icon(scene, 4, 4, 0x11C, 11);
                        load_Icon(scene, 4, 3, 0x11C, n % 1000 / 100);
                    } else if (n >= 10) {
                        load_Icon(scene, 4, 4, 0x11C, 10);
                        load_Icon(scene, 4, 3, 0x11C, 11);
                    } else {
                        load_Icon(scene, 4, 4, 0x11C, 10);
                        load_Icon(scene, 4, 3, 0x11C, 10);
                    }
                    if (n >= 10) {
                        load_Icon(scene, 4, 2, 0x11C, n % 100 / 10);
                    } else {
                        load_Icon(scene, 4, 2, 0x11C, 11);
                    }
                    load_Icon(scene, 4, 1, 0x11C, n % 10);
                    HUD_RECORD(scene, 4)->playMode = UI_PLAY_FORWARD;
                }
            }
        } else {
            n = fn_3_120F5C();
            if (n > 999) {
                n = 999;
            }
            if (n >= 100) {
                load_Icon(scene, 3, 3, 0x11B, n % 1000 / 100);
            } else {
                load_Icon(scene, 3, 3, 0x11B, 10);
            }
            if (n >= 10) {
                load_Icon(scene, 3, 2, 0x11B, n % 100 / 10);
            } else {
                load_Icon(scene, 3, 2, 0x11B, 10);
            }
            load_Icon(scene, 3, 1, 0x11B, n % 10);
            HUD_RECORD(scene, 3)->playMode = UI_PLAY_FORWARD;
            if (g_Minigame.wallBall_hitNoteBlock == 1) {
                HUD_RECORD(scene, 0)->playMode = UI_PLAY_FORWARD;
                HUD_RECORD(scene, 1)->playMode = UI_PLAY_FORWARD;
            }
        }
        scene->_1E = 0;
        scene->state = 2;
        break;
    case 2:
        if (!fn_3_125480(scene)) {
            if (scene->_1E != 0) {
                scene->state = 1;
            }
        }
        break;
    }
}

// .text:0x0012026C size:0x630 mapped:0x8075F300
void fn_3_12026C(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    s16* popup = (s16*)currentDrawingItem;
    u32 i;
    u32 k;
    s16 half;
    s16 third;
    s16 points;
    u32 type;
    u32 n;

    if (fn_3_12536C()) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    if (g_GameLogic.gameStatus == GAME_STATUS_TRANSITION_PREPARE_NEXT_PLAY) {
        scene->_1E = 1;
    }
    switch (scene->state) {
    case 0:
        addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_24844);
        scene->state = 1;
        break;
    case 1:
        i = 0;
        do {
            for (k = 0; k < 4; k++) {
                HUD_RECORD_AT(scene, 5 + k, i * 4)->playMode = UI_PLAY_STOP;
                HUD_RECORD_AT(scene, 5 + k, i * 4)->frame = 0;
            }
            i++;
        } while (i < 4);
        if (g_GameLogic.gameStatus != GAME_STATUS_AT_BAT) {
            break;
        }
        if (g_Pitcher.pitcherActionState != 4 && g_Minigame.ballStoppedBreakingWallsInd == 0) {
            break;
        }
        if (g_Minigame.wallBall_hitBowserWall == 0) {
            break;
        }
        if (g_Minigame.multiPlayerInd == 0 && g_Minigame._1A3C == 0
            && g_Minigame.soloMinigameDifficulty == MINIGAME_DIFFICULTY_SOLO_NON_CHALLENGE) {
            break;
        }
        half = g_Minigame.miniGameCurrentPoints[(s8)g_Minigame.minigamePlayerSelectedOrder] / 2;
        third = half / 3;
        i = 0;
        do {
            if (g_Minigame.playerSlots._14[i] >= 0) {
                if (i == g_Minigame.turnNumberWithinRound) {
                    popup[0x12 + i] = -half;
                } else {
                    popup[0x12 + i] = third;
                }
            } else {
                popup[0x12 + i] = 0;
            }
            i++;
        } while (i < 4);
        scene->_1E = 0;
        scene->state = 2;
        break;
    case 2:
        if (scene->_1E == 0) {
            break;
        }
        i = 0;
        do {
            points = popup[0x12 + i];
            if (points != 0) {
                if (points < 0) {
                    n = -points;
                    if (n > 999) {
                        n = 999;
                    }
                    type = 0x59;
                } else {
                    n = points;
                    if (n > 999) {
                        n = 999;
                    }
                    type = 0x5A;
                }
                if (n != 0) {
                    if (n >= 100) {
                        HUD_RECORD_AT(scene, 1, i)->frame = 2 << 16;
                    } else if (n >= 10) {
                        HUD_RECORD_AT(scene, 1, i)->frame = 1 << 16;
                    } else {
                        HUD_RECORD_AT(scene, 1, i)->frame = 0;
                    }
                    load_Icon(scene, i * 4 + 5, 1, type, 11);
                    load_Icon(scene, i * 4 + 6, 1, type, n % 1000 / 100);
                    load_Icon(scene, i * 4 + 7, 1, type, n % 100 / 10);
                    load_Icon(scene, i * 4 + 8, 1, type, n % 10);
                    HUD_RECORD_AT(scene, 5, i * 4)->playMode = UI_PLAY_FORWARD;
                    HUD_RECORD_AT(scene, 6, i * 4)->playMode = UI_PLAY_FORWARD;
                    HUD_RECORD_AT(scene, 7, i * 4)->playMode = UI_PLAY_FORWARD;
                    HUD_RECORD_AT(scene, 8, i * 4)->playMode = UI_PLAY_FORWARD;
                }
            }
            i++;
        } while (i < 4);
        scene->state = 3;
        break;
    case 3:
        if (!fn_3_125480(scene)) {
            scene->state = 1;
        }
        break;
    }
}

// .text:0x0011FDB0 size:0x4BC mapped:0x8075EE44
void fn_3_11FDB0(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    u32 i;
    u32 j;
    u32 limit;
    s16 hrPitch;

    if (fn_3_12536C()) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    switch (scene->state) {
    case 0:
        addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_24B04);
        i = 0;
        HUD_RECORD(scene, 0)->elementIndex = 0x120 + (g_Batter.batterHand != 0 ? -1 : 0);
        do {
            j = 1;
            do {
                load_Icon(scene, i + 3, j, 0x121, i);
                j++;
            } while (j <= 4);
            i++;
        } while (i < 10);
        scene->state = 1;
        break;
    case 1:
        hrPitch = g_Minigame.bB_bombBarrelID_bOD_hrPitch;
        if (hrPitch >= 0 && hrPitch < 15) {
            limit = 10;
        } else {
            limit = g_Minigame.barrelBatterChargeMeter;
            if (limit > 10) {
                limit = 10;
            }
        }
        if (scene->_1E < limit) {
            scene->_1E = scene->_1E + 1;
        } else {
            scene->_1E = limit;
        }
        if (scene->_1E <= 3) {
            i = 0;
            do {
                HUD_RECORD_AT(scene, 3, i)->elementIndex = 0x122;
                i++;
            } while (i < 10);
            HUD_RECORD(scene, 13)->elementIndex = 0x126;
        } else if (scene->_1E <= 6) {
            i = 0;
            do {
                HUD_RECORD_AT(scene, 3, i)->elementIndex = 0x123;
                i++;
            } while (i < 10);
            HUD_RECORD(scene, 13)->elementIndex = 0x127;
        } else {
            i = 0;
            do {
                HUD_RECORD_AT(scene, 3, i)->elementIndex = 0x124;
                i++;
            } while (i < 10);
            HUD_RECORD(scene, 13)->elementIndex = 0x128;
        }
        for (i = 0; i < scene->_1E; i++) {
            HUD_RECORD_AT(scene, 3, i)->rgba = (HUD_RECORD_AT(scene, 3, i)->rgba & 0xFFFFFF00) | 0xFF;
        }
        for (; i < 10; i++) {
            HUD_RECORD_AT(scene, 3, i)->rgba &= 0xFFFFFF00;
        }
        break;
    }
    if (scene->_1E >= lbl_3_data_21788[2]) {
        if (g_Minigame.pauseInd == 0) {
            if (g_d_GameSettings.FrameCountWhileNotAtMainMenu % 45 == 0) {
                callSfx(0x2FC);
            }
        }
    }
}

// .text:0x0011FA58 size:0x358 mapped:0x8075EAEC
void fn_3_11FA58(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    s16 points;
    u32 n;

    if (fn_3_12536C()) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    switch (scene->state) {
    case 0:
        addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_24CE4);
        scene->state = 1;
        break;
    case 1:
        HUD_RECORD(scene, 0)->frame = (g_Batter.batterHand == BATTING_HAND_RIGHT) << 16;
        HUD_RECORD(scene, 1)->playMode = UI_PLAY_STOP;
        HUD_RECORD(scene, 1)->frame = 0;
        if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL) {
            if (g_Minigame.barrelBatter_scoreCalculatedInd != 0) {
                points = g_Minigame.bB_totalPoints;
                if (points > 0) {
                    g_Minigame.bB_totalPoints = 0;
                    n = points;
                    if (n > 9999) {
                        n = 9999;
                    }
                    load_Icon(scene, 1, 4, 0x11B, n >= 1000 ? n % 10000 / 1000 : 10);
                    load_Icon(scene, 1, 3, 0x11B, n >= 100 ? n % 1000 / 100 : 10);
                    load_Icon(scene, 1, 2, 0x11B, n >= 10 ? n % 100 / 10 : 10);
                    load_Icon(scene, 1, 1, 0x11B, n % 10);
                    HUD_RECORD(scene, 1)->playMode = UI_PLAY_FORWARD;
                    scene->state = 2;
                }
            }
        }
        break;
    case 2:
        if (HUD_RECORD(scene, 1)->unk69[0] == 2) {
            if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
                scene->state = 1;
            }
        }
        break;
    }
}

// .text:0x0011F778 size:0x2E0 mapped:0x8075E80C
void fn_3_11F778(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    u32 n;

    if (fn_3_12536C()) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    switch (scene->state) {
    case 0:
        addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_24D44);
        scene->state = 1;
        break;
    case 1:
        HUD_RECORD(scene, 0)->frame = (g_Batter.batterHand == BATTING_HAND_RIGHT) << 16;
        HUD_RECORD(scene, 1)->playMode = UI_PLAY_STOP;
        HUD_RECORD(scene, 1)->frame = 0;
        if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL) {
            if (g_Minigame.barrelBatter_scoreCalculatedInd != 0 && g_Minigame.barrelBatter_barrelsHit >= 2) {
                n = g_Minigame.barrelBatter_barrelsHit;
                if (n > 99) {
                    n = 99;
                }
                if (n < 10) {
                    HUD_RECORD(scene, 1)->elementIndex = 0x12A;
                } else {
                    HUD_RECORD(scene, 1)->elementIndex = 0x129;
                }
                load_Icon(scene, 1, 5, 0x12C, n % 100 / 10);
                load_Icon(scene, 1, 4, 0x12C, n % 10);
                HUD_RECORD(scene, 1)->playMode = UI_PLAY_FORWARD;
                scene->state = 2;
            }
        }
        break;
    case 2:
        if (HUD_RECORD(scene, 1)->unk69[0] == 2) {
            if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
                scene->state = 1;
            }
        }
        break;
    }
}

// .text:0x0011F508 size:0x270 mapped:0x8075E59C
void fn_3_11F508(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    u32 n;

    if (fn_3_12536C()) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    switch (scene->state) {
    case 0:
        addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_24DA4);
        scene->state = 1;
        break;
    case 1:
        HUD_RECORD(scene, 0)->frame = (g_Batter.batterHand == BATTING_HAND_RIGHT) << 16;
        HUD_RECORD(scene, 1)->playMode = UI_PLAY_STOP;
        HUD_RECORD(scene, 1)->frame = 0;
        if (g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL) {
            if (g_Minigame.barrelBatter_scoreCalculatedInd != 0 && g_Minigame.bB_bombBarrelHitInd_bOD_hrYaw != 0) {
                n = cost_15_bB_pitchesPerRound_solo[6];
                if (n > 9) {
                    n = 9;
                }
                load_Icon(scene, 1, 2, 0x12F, n % 10);
                HUD_RECORD(scene, 1)->playMode = UI_PLAY_FORWARD;
                scene->state = 2;
            }
        }
        break;
    case 2:
        if (HUD_RECORD(scene, 1)->unk69[0] == 2) {
            if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
                scene->state = 1;
            }
        }
        break;
    }
}

// .text:0x0011F4B4 size:0x54 mapped:0x8075E548
void fn_3_11F4B4(int player, int bonus) {
    if (g_Minigame.GameMode_MiniGame != MINI_GAME_ID_CHAINCHOMP_SPRINT) {
        return;
    }
    g_Minigame.ccsDisplayedPoints[player] += lbl_3_data_21884[bonus ? 2 : 0].points;
}

// .text:0x0011F480 size:0x34 mapped:0x8075E514
void fn_3_11F480(void) {
    u32 i;

    if (g_Minigame.GameMode_MiniGame != MINI_GAME_ID_CHAINCHOMP_SPRINT) {
        return;
    }
    i = 0;
    do {
        g_Minigame.ccsDisplayedPoints[i] = g_Minigame.miniGameCurrentPoints[i];
        i++;
    } while (i < 4);
}

// .text:0x0011F02C size:0x454 mapped:0x8075E0C0
void fn_3_11F02C(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    u32 i;
    int leader;
    u32 flag;
    u32 n;
    u32 changed = 0;

    if (fn_3_12536C()) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
    } else {
        switch (scene->state) {
        case 0:
            addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_24E04);
            i = 0;
            do {
                load_Icon(scene, 9 + i, 1, 0x65, i);
                HUD_RECORD_AT(scene, 0x11, i)->frame = inMemRoster[0][i].stats.CharID << 16;
                i++;
            } while (i < 4);
            i = 0;
            do {
                HUD_RECORD_AT(scene, 0x25, i)->flags &= ~UI_FLAG_VISIBLE;
                i++;
            } while (i < 4);
            scene->state = 1;
            break;
        case 1:
            leader = fn_3_107CD0();
            flag = fn_3_107C88();
            i = 0;
            do {
                if (g_Minigame._1DFC[i] != 0) {
                    g_Minigame._1DFC[i] = 0;
                    HUD_RECORD_AT(scene, 1, i)->frame = 0;
                    HUD_RECORD_AT(scene, 1, i)->playMode = UI_PLAY_FORWARD;
                }
                if (g_Minigame.ccsDisplayedPoints[i] > g_Minigame.miniGameCurrentPoints[i]) {
                    g_Minigame.ccsDisplayedPoints[i] = g_Minigame.miniGameCurrentPoints[i];
                }
                if (g_Minigame.ccsDisplayedPoints[i] - g_Minigame.minigamePoints_current_Latest[i][0] > 0) {
                    g_Minigame.minigamePoints_current_Latest[i][0]++;
                    scene->scratch[i] = 1;
                    changed = 1;
                } else if (g_Minigame.ccsDisplayedPoints[i] - g_Minigame.minigamePoints_current_Latest[i][0] < 0) {
                    g_Minigame.minigamePoints_current_Latest[i][0]--;
                    changed = 1;
                } else if (scene->scratch[i] != 0) {
                    scene->scratch[i] = 0;
                    HUD_RECORD_AT(scene, 0x19, i)->frame = 0;
                    HUD_RECORD_AT(scene, 0x19, i)->playMode = UI_PLAY_FORWARD;
                    HUD_RECORD_AT(scene, 0x1D, i * 2)->frame = 0;
                    HUD_RECORD_AT(scene, 0x1E, i * 2)->frame = 0;
                }
                n = g_Minigame.minigamePoints_current_Latest[i][0];
                if (n > 99) {
                    n = 99;
                }
                load_Icon(scene, i * 2 + 0x1D, 1, 0x66, n % 100 / 10);
                load_Icon(scene, i * 2 + 0x1E, 1, 0x66, n % 10);
                if (flag == 0 && g_Minigame.minigamePoints_current_Latest[i][0] == g_Minigame.minigamePoints_current_Latest[leader][0]) {
                    HUD_RECORD_AT(scene, 0x25, i)->flags |= UI_FLAG_VISIBLE;
                } else {
                    HUD_RECORD_AT(scene, 0x25, i)->flags &= ~UI_FLAG_VISIBLE;
                }
                i++;
            } while (i < 4);
            break;
        }
        if (changed != 0) {
            sndFXStartEx(0x1C0, lbl_800EFBA4[9], 0x3F, 0);
        }
    }
}

// .text:0x0011EC28 size:0x404 mapped:0x8075DCBC
void fn_3_11EC28(void) {
    MinigameHudScene* scene = (MinigameHudScene*)currentDrawingItem;
    u32 i;
    u32 j;
    s16 x;
    s16 y;

    if (fn_3_12536C()) {
        removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
        removeCurrentDrawingItem();
        return;
    }
    switch (scene->state) {
    case 0:
        addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_25344);
        scene->state = 1;
        break;
    case 1:
        i = 0;
        do {
            HUD_RECORD(scene, i)->playMode = UI_PLAY_STOP;
            HUD_RECORD(scene, i)->frame = 0;
            i++;
        } while (i < 8);
        if (g_Minigame._1E00 != 0) {
            g_Minigame._1E00 = 0;
            if (g_Minigame.ccs.targetCount != 0) {
                for (i = 0; i < 4; i++) {
                    if (g_Minigame.ccs.targetInd[i] == 1) {
                        HUD_RECORD_AT(scene, 4, i)->playMode = UI_PLAY_FORWARD;
                        fn_800528C0(g_Runners[i].position.x, g_Runners[i].position.y, g_Runners[i].position.z, &x, &y);
                        if (x < 0x50) {
                            x = 0x50;
                        } else if (x > 0x230) {
                            x = 0x230;
                        }
                        HUD_RECORD_AT(scene, 4, i)->pos.x = x;
                        HUD_RECORD_AT(scene, 4, i)->pos.y = y;
                    }
                }
            } else {
                i = 0;
                do {
                    HUD_RECORD(scene, i)->playMode = UI_PLAY_FORWARD;
                    fn_800528C0(g_Runners[i].position.x, g_Runners[i].position.y, g_Runners[i].position.z, &x, &y);
                    if (x < 0x50) {
                        x = 0x50;
                    } else if (x > 0x230) {
                        x = 0x230;
                    }
                    HUD_RECORD(scene, i)->pos.x = x;
                    HUD_RECORD(scene, i)->pos.y = y;
                    i++;
                } while (i < 4);
            }
            scene->state = 2;
        }
        break;
    case 2:
        j = 0;
        do {
            if (HUD_RECORD(scene, j)->playMode != UI_PLAY_STOP && HUD_RECORD(scene, j)->unk69[0] != 2) {
                break;
            }
            j++;
        } while (j < 8);
        if (j >= 8) {
            scene->state = 1;
        }
        break;
    }
}
