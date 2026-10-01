#define SQRT2_LINKAGE static
#include "game/match_setup/match_scene.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#define REP_HEADER_DATA_FN getRepHeaderData_matchScene
#include "header_rep_data.h"
#include "game/hud/hud_scoreboard.h"
#include "game/hud/toyfield_score_update.h"
#include "game/match_setup/run_scoring.h"
#include "game/match_setup/stat_book.h"
#include "text/text_channel.h"
#include "musyx/musyx.h"
#include "PowerPC_EABI_Support/Runtime/__mem.h"
#include "Unknown/File_0x80034cec.h"
#include "Unknown/File_0x80034e20.h"
#include "Unknown/File_0x8003649c.h"
#include "Unknown/File_0x800363d8.h"
#include "Unknown/File_0x80069a98.h"
#include "Unknown/File_0x800b0a14.h"

// The pause menu's shared state block.
typedef struct PauseControl {
    /* 0x000 */ u32 port;
    /* 0x004 */ u8 _004[0xE];
    /* 0x012 */ s16 _12;
    /* 0x014 */ u8 _014[0x1D0 - 0x14];
    /* 0x1D0 */ u8 _1D0;
    /* 0x1D1 */ u8 _1D1;
    /* 0x1D2 */ u8 _1D2;
    /* 0x1D3 */ u8 _1D3;
    /* 0x1D4 */ u8 _1D4[5];
    /* 0x1D9 */ u8 _1D9;
    /* 0x1DA */ s8 _1DA;
    /* 0x1DB */ u8 _1DB[0x221 - 0x1DB];
    /* 0x221 */ u8 _221;
    /* 0x222 */ u8 _222[0x23F - 0x222];
    /* 0x23F */ u8 _23F[2];
    /* 0x241 */ u8 _241[0x264 - 0x241];
} PauseControl;

// Drawing-script node of a pause-menu screen.
typedef struct PauseMenuScene {
    /* 0x00 */ u8 _00[0x14];
    /* 0x14 */ u16 firstHandle;
    /* 0x16 */ u16 handleCount;
    /* 0x18 */ u16 counter;
    /* 0x1A */ u16 _1A;
    /* 0x1C */ u16 state;
    /* 0x1E */ u16 rows;
    /* 0x20 */ u16 alpha;
} PauseMenuScene;

typedef struct MenuLabel {
    /* 0x0 */ u8 _0[8];
    /* 0x8 */ u16 label;
    /* 0xA */ u8 _A[6];
} MenuLabel;

extern u8 animRelated[0x124];
extern PauseControl pauseControl;
extern u8 menuNumber[0x28];
extern MenuLabel lbl_800FEF70[];
extern struct {
    u8 _00[0x47];
    u8 scoutResult;
} lbl_3_common_bss_37400;
extern s16 lbl_3_data_BE50[][4];
extern UIRecordDescriptor lbl_3_data_D648[];
extern UIRecordDescriptor lbl_3_data_D7A8[];
extern u16 lbl_3_data_D7E8[][10];
extern u16 lbl_3_data_D860[][9];
extern u8 lbl_3_data_D9B8[][7];
extern UIRecordDescriptor lbl_3_data_D9E4[];
extern u16 lbl_3_data_DA44[][3];
extern UIRecordDescriptor lbl_3_data_DA50[];
extern u16 lbl_3_data_E0D0[8];

extern void toyFieldDrawRelated_miniMap(void);
extern void fn_80053FE8(void);
extern void fn_8004D0F0(void);
extern void fn_8004CC4C(int, int, int, int, int);
extern void createTeamManagementScreen_inGame(int, s8, u8);
extern void unregisterObjectByID(int id);

#define REC(scene, i) ((UIRecord*)graphicsRelatedArray[(scene)->firstHandle + (i)].object)
#define REC_AT(scene, i, off) ((UIRecord*)graphicsRelatedArray[(scene)->firstHandle + (i) + (off)].object)

#define SET_MENU(id)                                              \
    menuNumber[0] = (id);                                         \
    menuNumber[9] = menuNumber[8];                                \
    menuNumber[8] = lbl_800FEF70[(id)].label

// .text:0x00099064 size:0x344 mapped:0x806D80F8
void animatePauseMenu(void) {
    PauseControl* pc = &pauseControl;
    u8 mode;

    if (pc->_1D1 == 2 || pc->_1D1 == 9) {
        if (pauseControl._1D2 == 0) {
            if (animRelated[0xAA] == 0) {
                insertGraphicDrawingFunction(pauseSubPanel_init, 2);
            }
            insertGraphicDrawingFunction(pauseOptionList_init, 2);
        }
    }
    mode = pc->_1D1;
    if (mode == 4 || mode == 0xB || mode == 0xE || (u8)(mode - 7) <= 1 || mode == 0xF) {
        pauseMenu_openTeamManagement();
    }
    if (pc->_1D1 == 6 || pc->_1D1 == 0xD) {
        if (pauseControl._1D2 == 2) {
            insertGraphicDrawingFunction(pausePageIndicator_init, 2);
        }
    }
    if (pc->_1D1 == 0xC || pc->_1D1 == 5) {
        if (pauseControl._1D2 == 1) {
            insertGraphicDrawingFunction(fn_80053FE8, 0);
            if (g_d_GameSettings.GameModeSelected != GAME_TYPE_CHALLENGE) {
                SET_MENU(9);
            } else {
                SET_MENU(0x1B);
            }
            insertGraphicDrawingFunction(pauseMenu_ControlsMenu, 2);
        }
    }
}

// .text:0x00098EA8 size:0x1BC mapped:0x806D7F3C
void pauseMenu_openTeamManagement(void) {
    PauseControl* pc = &pauseControl;

    if (pc->_1D2 == 2) {
        insertGraphicDrawingFunction(fn_80053FE8, 2);
        memset(menuNumber, 0, 0x28);
        switch (aiPosSwapInputs._CFA2[pauseControl.port]) {
        case 0:
            SET_MENU(g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE ? 0x1C : 8);
            break;
        case 1:
            SET_MENU(0xA);
            break;
        case 2:
            SET_MENU(0x1E);
            break;
        case 3:
            SET_MENU(0x1F);
            break;
        }
        createTeamManagementScreen_inGame(0, g_GameLogic.teams[pauseControl.port], pauseControl.port);
    }
    if (pc->_1D2 == 5) {
        menuNumber[0x26] = 1;
    }
}

// .text:0x00098DE0 size:0xC8 mapped:0x806D7E74
void pauseSubPanel_init(void) {
    PauseMenuScene* scene = (PauseMenuScene*)currentDrawingItem;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_D7A8);
    if (g_d_GameSettings.minigamesEnabled) {
        REC(scene, 0)->layer = 5;
    } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        REC(scene, 0)->layer = 6;
    }
    animRelated[0xAA] = 1;
    scene->state = 0;
    currentDrawingItem->func = pauseSubPanel_update;
}

// .text:0x00098C20 size:0x1C0 mapped:0x806D7CB4
void pauseSubPanel_update(void) {
    PauseMenuScene* scene = (PauseMenuScene*)currentDrawingItem;

    if (animRelated[0x96] != 0) {
        goto remove;
    }
    if (scene->state == 0) {
        scene->state = 1;
    } else if (scene->state == 1) {
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
            if (g_Practice._19F != 0) {
                if (pauseControl._1D2 == 4) {
                    scene->state = 2;
                }
            } else {
                goto remove;
            }
        } else if (g_d_GameSettings.minigamesEnabled) {
            if (g_GameLogic.gameStatus == GAME_STATUS_PAUSED && pauseControl._1D2 == 4) {
                scene->state = 2;
            }
            if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
                if (pauseControl._1D2 == 4) {
                    scene->state = 2;
                }
                if (pauseControl._1D2 == 7 || pauseControl._1D2 == 0xD) {
                    goto remove;
                }
                return;
            }
        } else {
            if (pauseControl._1D1 == 2 || pauseControl._1D1 == 9) {
                if (pauseControl._1D2 == 4) {
                    goto remove;
                }
            }
            if (pauseControl._1D9 == 2) {
                goto remove;
            }
        }
    } else if (scene->state == 2) {
        REC(scene, 0)->playMode = UI_PLAY_BACKWARD;
        if ((REC(scene, 0)->frame >> 16) == 0) {
            goto remove;
        }
    }
    return;
remove:
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
    animRelated[0xAA] = 0;
}

// .text:0x0009894C size:0x2D4 mapped:0x806D79E0
void pauseOptionList_init(void) {
    u16* row;
    PauseMenuScene* scene = (PauseMenuScene*)currentDrawingItem;
    int i;
    int rows;
    int k;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_D648);
    if ((!g_d_GameSettings.minigamesEnabled && g_GameLogic.gameStatus == GAME_STATUS_PAUSED) ||
        (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD && g_GameLogic.gameStatus == GAME_STATUS_PAUSED) ||
        (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES && g_Minigame.pauseInd != 0)) {
        REC(scene, 0)->flags &= ~UI_FLAG_VISIBLE;
    }
    rows = lbl_3_data_D860[pauseControl._1D0][0];
    row = lbl_3_data_D7E8[rows - 2];
    REC(scene, 1)->elementIndex = row[0];
    REC(scene, 2)->elementIndex = row[1];
    REC(scene, 2)->frame = lbl_3_data_D860[pauseControl._1D0][1] << 16;
    for (i = 0, k = 0; i < rows; row++, k++, i++) {
        int icon;

        REC_AT(scene, 3, i)->anchorSub = row[3];
        REC_AT(scene, 3, i)->flags |= UI_FLAG_VISIBLE;
        REC_AT(scene, 3, i)->playMode = UI_PLAY_FORWARD;
        icon = lbl_3_data_D860[pauseControl._1D0][2 + k];
        if (g_d_GameSettings.exhibitionMatchInd == 0 && icon == 3) {
            icon = 0x12;
        }
        load_Icon(scene, i + 3, 1, 0xCF, icon);
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        if (g_Practice._19F != 0) {
            REC(scene, 0)->flags &= ~UI_FLAG_VISIBLE;
        } else if (g_Practice._1C7 != 0) {
            REC(scene, 0)->layer = 5;
        }
    }
    pauseControl._1D9 = 0;
    scene->state = 0;
    scene->rows = rows;
    scene->alpha = 0xFF;
    scene->counter = 0;
    animRelated[0xAB] = 1;
    currentDrawingItem->func = pauseOptionList_update;
}

static inline int getPauseOptionDir(void) {
    int dir = 0;

    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_MINIGAMES) {
        if (pauseControl._1D2 == 8) {
            dir = 1;
        } else if (pauseControl._1D2 == 9) {
            dir = 2;
        }
    } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
        if (pauseControl._1D2 == 9) {
            dir = 1;
        } else if (pauseControl._1D2 == 0xA) {
            dir = 2;
        }
    } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        if (pauseControl._1D2 == 0xC) {
            dir = 1;
        } else if (pauseControl._1D2 == 0xD) {
            dir = 2;
        }
    } else {
        if (pauseControl._1D2 == 7) {
            dir = 1;
        } else if (pauseControl._1D2 == 8) {
            dir = 2;
        }
    }
    return dir;
}

// .text:0x00098434 size:0x518 mapped:0x806D74C8
void pauseOptionList_update(void) {
    int dir = 0;
    PauseMenuScene* scene = (PauseMenuScene*)currentDrawingItem;
    int i;

    if (scene->counter < 0xFFFE) {
        scene->counter++;
    } else {
        scene->counter = 0xFFFF;
    }
    if (animRelated[0x96] != 0) {
        goto remove;
    }
    dir = getPauseOptionDir();
    if (dir != 0) {
        scene->alpha -= 0x10;
        if (scene->alpha <= 0x80) {
            scene->alpha = 0x80;
        }
        REC(scene, 1)->rgba = scene->alpha | (REC(scene, 1)->rgba & ~0xFF);
    } else {
        scene->alpha += 0x10;
        if (scene->alpha >= 0xFF) {
            scene->alpha = 0xFF;
        }
        REC(scene, 1)->rgba = scene->alpha | (REC(scene, 1)->rgba & ~0xFF);
    }
    if (scene->state == 0) {
        scene->state = scene->state + 1;
    } else if (scene->state == 1) {
        for (i = 0; i < scene->rows; i++) {
            if ((s32)(REC_AT(scene, 3, i)->frame >> 16) >= 3) {
                REC_AT(scene, 3, i)->playMode = UI_PLAY_STOP;
            }
        }
        if ((s32)(REC(scene, 1)->frame >> 16) >= lbl_3_data_D7E8[scene->rows - 2][2]) {
            scene->state = 2;
        }
    } else if (scene->state == 2) {
        for (i = 0; i < scene->rows; i++) {
            if (i == pauseControl._1DA) {
                if ((s32)(REC_AT(scene, 3, i)->frame >> 16) >= 8) {
                    REC_AT(scene, 3, i)->playMode = UI_PLAY_STOP;
                } else {
                    REC_AT(scene, 3, i)->playMode = UI_PLAY_FORWARD;
                }
            } else {
                if ((s32)(REC_AT(scene, 3, i)->frame >> 16) <= 3) {
                    REC_AT(scene, 3, i)->playMode = UI_PLAY_STOP;
                } else {
                    REC_AT(scene, 3, i)->playMode = UI_PLAY_BACKWARD;
                }
            }
        }
        if (pauseControl._1D9 == 2) {
            goto remove;
        }
        if (pauseControl._1D9 != 0) {
            scene->state = 3;
        }
    } else if (scene->state == 3) {
        int f = REC(scene, 1)->frame >> 16;

        for (i = 0; i < scene->rows; i++) {
            if (f <= lbl_3_data_D9B8[scene->rows - 2][i]) {
                if (i == pauseControl._1DA) {
                    REC_AT(scene, 3, i)->playMode = UI_PLAY_FORWARD;
                } else {
                    REC_AT(scene, 3, i)->playMode = UI_PLAY_BACKWARD;
                }
            }
        }
        REC(scene, 1)->playMode = UI_PLAY_BACKWARD;
        REC(scene, 0)->playMode = UI_PLAY_BACKWARD;
        if ((s32)(REC(scene, 1)->frame >> 16) <= 0) {
            goto remove;
        }
    }
    if (dir == 1) {
        if (pauseControl._12 == 1) {
            if (g_d_GameSettings.exhibitionMatchInd == 0) {
                fn_8004CC4C(1, 0, 1, 0, 0x8A);
            } else {
                fn_8004CC4C(1, 0, 1, 0, 0x89);
            }
            insertGraphicDrawingFunction(fn_8004D0F0, 2);
        }
    }
    return;
remove:
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
    pauseControl._1D9 = 3;
    animRelated[0xAB] = 0;
}

// .text:0x000983B8 size:0x7C mapped:0x806D744C
void pausePageIndicator_init(void) {
    PauseMenuScene* scene = (PauseMenuScene*)currentDrawingItem;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_D9E4);
    animRelated[0xC3] = 0;
    scene->state = 0;
    scene->rows = pauseControl._221;
    scene->alpha = 0;
    currentDrawingItem->func = pausePageIndicator_update;
}

// .text:0x00098028 size:0x390 mapped:0x806D70BC
void pausePageIndicator_update(void) {
    int x = 0;
    PauseMenuScene* scene = (PauseMenuScene*)currentDrawingItem;

    if (animRelated[0x96] != 0 || pauseControl._1D2 == 6) {
        goto remove;
    }
    if (inningSetting.starSkillsSetting == 0 && g_d_GameSettings.GameModeSelected != GAME_TYPE_PRACTICE) {
        x = 1;
    }
    if (scene->state == 0) {
        REC(scene, 1)->frame = lbl_3_data_DA44[x][scene->rows] << 16;
        if (scene->alpha == 0) {
            REC(scene, 0)->frame = 0;
            REC(scene, 0)->playMode = UI_PLAY_FORWARD;
        } else {
            REC(scene, 0)->frame = 0xF0000;
            REC(scene, 0)->playMode = UI_PLAY_BACKWARD;
        }
        animRelated[0xC3] = 1;
        scene->state = scene->state + 1;
    } else if (scene->state == 1) {
        if (scene->alpha == 0) {
            if ((REC(scene, 0)->frame >> 16) >= 8) {
                REC(scene, 0)->playMode = UI_PLAY_STOP;
                scene->state = scene->state + 1;
            }
        } else {
            if ((REC(scene, 0)->frame >> 16) <= 8) {
                REC(scene, 0)->playMode = UI_PLAY_STOP;
                scene->state = scene->state + 1;
            }
        }
        animRelated[0xC3] = 1;
    } else if (scene->state == 2) {
        u8 mode;

        animRelated[0xC3] = 0;
        mode = g_d_GameSettings.GameModeSelected;
        if ((mode == GAME_TYPE_PRACTICE && pauseControl._1D3 == 6) ||
            (mode != GAME_TYPE_PRACTICE && pauseControl._1D2 == 5)) {
            REC(scene, 0)->playMode = UI_PLAY_FORWARD;
            scene->alpha = 0;
            scene->state = 4;
        } else if (pauseControl._221 != scene->rows) {
            scene->rows = pauseControl._221;
            REC(scene, 1)->frame = lbl_3_data_DA44[x][scene->rows] << 16;
        }
    } else {
        int done = 0;

        animRelated[0xC3] = 1;
        if (scene->alpha == 0) {
            if ((REC(scene, 0)->frame >> 16) >= 0xF) {
                done = 1;
            }
        } else {
            if ((REC(scene, 0)->frame >> 16) == 0) {
                done = 1;
            }
        }
        if (done) {
            scene->rows = pauseControl._221;
            REC(scene, 0)->playMode = UI_PLAY_STOP;
            if (scene->state == 3) {
                scene->state = 0;
            } else {
                goto remove;
            }
        }
    }
    return;
remove:
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
    animRelated[0xC3] = 0;
}

// .text:0x00097CEC size:0x33C mapped:0x806D6D80
void pauseMenu_ControlsMenu(void) {
    int i;
    int j;
    int base;
    PauseMenuScene* scene = (PauseMenuScene*)currentDrawingItem;

    addGraphicsElementToScene((DrawingSceneStruct*)scene, lbl_3_data_DA50);
    for (i = 0; i < 2; i++) {
        int team;

        if (g_GameLogic.teamIsCPU[i]) {
            team = g_GameLogic.teams[i] + 4;
        } else {
            team = g_GameLogic.teams[i];
        }
        if (i == 0) {
            load_Icon(scene, 4, 1, 0x46, team);
        } else {
            load_Icon(scene, 0x1C, 1, 0x46, team);
        }
    }
    for (j = 0; j < 4; j++) {
        load_Icon(scene, j + 5, 1, 0x11A, j);
        load_Icon(scene, j + 0x1D, 1, 0x11A, j);
    }
    for (i = 0; i < 2; i++) {
        base = 0x21;
        if (i == 0) {
            base = 9;
        }
        load_Icon(scene, base, 1, 0x116, lbl_3_data_E0D0[0]);
        load_Icon(scene, base, 2, 0x116, lbl_3_data_E0D0[1]);
        if (inningSetting.controlOptions[g_GameLogic.teams[i]].easyBatting) {
            REC(scene, base)->frame = 0xA0000;
        }
        load_Icon(scene, base + 1, 1, 0x116, lbl_3_data_E0D0[2]);
        load_Icon(scene, base + 1, 2, 0x116, lbl_3_data_E0D0[3]);
        if (inningSetting.controlOptions[g_GameLogic.teams[i]].autoFielding) {
            REC(scene, base + 1)->frame = 0xA0000;
        }
        load_Icon(scene, base + 2, 1, 0x116, lbl_3_data_E0D0[4]);
        load_Icon(scene, base + 2, 2, 0x116, lbl_3_data_E0D0[5]);
        if (inningSetting.controlOptions[g_GameLogic.teams[i]].autoRunning) {
            REC(scene, base + 2)->frame = 0xA0000;
        }
        load_Icon(scene, base + 3, 1, 0x116, lbl_3_data_E0D0[7]);
        load_Icon(scene, base + 3, 2, 0x116, lbl_3_data_E0D0[6]);
        if (!inningSetting.controlOptions[g_GameLogic.teams[i]].dropSpot) {
            REC(scene, base + 3)->frame = 0xA0000;
        }
    }
    REC(scene, 0x1A)->frame = Static_Stats_Tables.captainSelectedID[0] << 16;
    REC(scene, 0x32)->frame = Static_Stats_Tables.captainSelectedID[1] << 16;
    scene->counter = 0;
    currentDrawingItem->func = pauseControlsMenu_update;
}

// .text:0x000978DC size:0x410 mapped:0x806D6970
void pauseControlsMenu_update(void) {
    PauseMenuScene* scene = (PauseMenuScene*)currentDrawingItem;
    int row;
    int j;
    int i;
    int b;
    int c;
    int a;
    int on;

    if (animRelated[0x96] != 0 || pauseControl._1D2 == 6) {
        goto remove;
    }
    if (pauseControl._1D2 == 4) {
        REC(scene, 0)->playMode = UI_PLAY_BACKWARD;
        REC(scene, 2)->playMode = UI_PLAY_BACKWARD;
        menuNumber[0x26] = 1;
        scene->counter = 9;
    }
    if (scene->counter == 9) {
        return;
    }
    if (pauseControl._23F[pauseControl.port] == 0) {
        REC(scene, 1)->playMode = UI_PLAY_FORWARD;
    } else {
        if ((REC(scene, 1)->frame >> 16) > 10) {
            REC(scene, 1)->frame = 0xA0000;
        }
        REC(scene, 1)->playMode = UI_PLAY_BACKWARD;
    }
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++) {
            row = j + 0x1D;
            if (i == 0) {
                row = j + 5;
            }
            if (pauseControl._23F[i] == j + 1) {
                REC(scene, row)->playMode = UI_PLAY_FORWARD;
            } else {
                if ((REC(scene, row)->frame >> 16) > 10) {
                    REC(scene, row)->frame = 0xA0000;
                }
                REC(scene, row)->playMode = UI_PLAY_BACKWARD;
            }
            c = j + 0x21;
            if (i == 0) {
                c = j + 9;
            }
            if (j == 0) {
                on = inningSetting.controlOptions[g_GameLogic.teams[i]].easyBatting;
            } else if (j == 1) {
                on = inningSetting.controlOptions[g_GameLogic.teams[i]].autoFielding;
            } else if (j == 2) {
                on = inningSetting.controlOptions[g_GameLogic.teams[i]].autoRunning;
            } else {
                on = inningSetting.controlOptions[g_GameLogic.teams[i]].dropSpot ^ 1;
            }
            if (on) {
                REC(scene, c)->playMode = UI_PLAY_FORWARD;
            } else {
                REC(scene, c)->playMode = UI_PLAY_BACKWARD;
            }
            if (i == 0) {
                if (on) {
                    a = j + 0x11;
                    c = j + 0x15;
                } else {
                    a = j + 0x15;
                    c = j + 0x11;
                }
                b = j + 0xD;
            } else {
                if (on) {
                    a = j + 0x29;
                    c = j + 0x2D;
                } else {
                    a = j + 0x2D;
                    c = j + 0x29;
                }
                b = j + 0x25;
            }
            if (pauseControl._23F[i] == j + 1) {
                REC(scene, a)->flags |= UI_FLAG_VISIBLE;
                REC(scene, b)->playMode = UI_PLAY_FORWARD;
            } else {
                REC(scene, a)->flags &= ~UI_FLAG_VISIBLE;
                REC(scene, b)->playMode = UI_PLAY_BACKWARD;
            }
            REC(scene, c)->flags &= ~UI_FLAG_VISIBLE;
        }
    }
    return;
remove:
    removeGraphicsElementFromScene((DrawingSceneStruct*)scene);
    removeCurrentDrawingItem();
}

// .text:0x00097800 size:0xDC mapped:0x806D6894
void initAnimStruct(void) {
    animRelated[0x96] = 0;
    animRelated[0xA5] = 0;
    animRelated[0x97] = 0;
    animRelated[0xA8] = 0;
    animRelated[0x98] = 0;
    animRelated[0x99] = 0;
    animRelated[0xD1] = 0;
    animRelated[0xAD] = 0;
    animRelated[0xAE] = 0;
    animRelated[0xB0] = 0;
    animRelated[0xB1] = 0;
    animRelated[0xB2] = 0;
    animRelated[0xC7] = 0;
    animRelated[0xD6] = 0;
    animRelated[0xB6] = 0;
    animRelated[0xD9] = 0;
    animRelated[0xDA] = 0;
    animRelated[0xBC] = 0;
    animRelated[0xC0] = 0;
    animRelated[0xC1] = 0;
    animRelated[0xC2] = 0;
    animRelated[0xC6] = 0;
    animRelated[0xAA] = 0;
    animRelated[0xAB] = 0;
    animRelated[0xC3] = 0;
    animRelated[0xC4] = 0;
    animRelated[0xBE] = 0;
    animRelated[0xBF] = 0;
    animRelated[0xB3] = 0;
    animRelated[0xB4] = 0;
    animRelated[0xB5] = 0;
    animRelated[0xC5] = 0;
    if (g_d_GameSettings.minigamesEnabled == 0) {
        insertGraphicDrawingFunction(offscreenFielderIndicator_init, 2);
    }
    insertGraphicDrawingFunction(ballLandingMarker_init, 2);
}

// .text:0x000973EC size:0x414 mapped:0x806D6480
void animateMatchScene(void) {
    if (animRelated[0x96] == 0) {
        if (g_Stats.replayInd != 0) {
            animRelated[0xA7] = 0;
        } else {
            manageEventStates();
            if (animRelated[0xC7] == 0 && g_GameLogic.hudElementLoadingInd != 0) {
                insertGraphicDrawingFunction(drawDiamondMiniMap_init, 2);
                if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
                    insertGraphicDrawingFunction(toyFieldDrawRelated_miniMap, 2);
                }
            }
            matchHudDrawingControl();
            hud_ScoreUpdate_ToyFieldOffScreenPlayers();
            if (animRelated[0xB4] == 1) {
                animRelated[0xB4] = 2;
                insertGraphicDrawingFunction(fn_3_952DC, 2);
                if (lbl_3_common_bss_37400.scoutResult == 2) {
                    insertGraphicDrawingFunction(scoutMissionProgress_init, 2);
                }
            }
            if (g_d_GameSettings.exhibitionMatchInd == 0 && g_GameLogic.gameStatus == GAME_STATUS_AT_BAT &&
                animRelated[0xB3] == 1 && g_UnkSound_32718._07 == 0) {
                insertGraphicDrawingFunction(fn_3_95124, 2);
                insertGraphicDrawingFunction(scoutMissionProgress_init, 2);
                animRelated[0xB3] = 2;
            }
            if (g_GameLogic.gameStatus == GAME_STATUS_GAME_START_MOVIE) {
                if (g_GameLogic._125 == 0) {
                    insertGraphicDrawingFunction(fn_3_94760, 2);
                }
            } else if (g_GameLogic.gameStatus == GAME_STATUS_INNING_TRANSITION) {
                if (g_GameLogic._125 == 0) {
                    insertGraphicDrawingFunction(manageScoreboardGraphic, 2);
                    insertGraphicDrawingFunction(fn_3_91D1C, 2);
                    animRelated[0xCF] = g_Scores.Inning;
                    animRelated[0xD0] = g_Scores.halfInning;
                }
                if (g_GameLogic._125 == 9) {
                    animRelated[0xCD] = 1;
                }
            } else if (g_GameLogic.gameStatus == GAME_STATUS_END_OF_GAME) {
                if (g_GameLogic._125 == 0) {
                    insertGraphicDrawingFunction(relatedToAnimatingEndOfGame, 2);
                }
            } else if (g_GameLogic.gameStatus == GAME_STATUS_PAUSED) {
                animatePauseMenu();
            } else if (g_GameLogic.gameStatus == GAME_STATUS_MVP_END_GAME) {
                animateMVP_GameEnd();
            } else if (g_GameLogic.gameStatus == GAME_STATUS_STAR_CHANCE_VS) {
                if (animRelated[0xAD] != 0) {
                    if (g_d_GameSettings.exhibitionMatchInd == 0) {
                        insertGraphicDrawingFunction(fn_3_953FC, 2);
                        insertGraphicDrawingFunction(scoutMissionProgress_init, 2);
                    } else {
                        insertGraphicDrawingFunction(fn_3_9551C, 2);
                    }
                    playSoundEffect(0x1A7);
                    animRelated[0xAD] = 0;
                }
            } else if (g_GameLogic.gameStatus == GAME_STATUS_CHAMPIONSHIP) {
                if (g_GameLogic._125 == 2) {
                    insertGraphicDrawingFunction(fn_3_94930, 2);
                }
            } else if (g_GameLogic.gameStatus == GAME_STATUS_HOMERUN_END) {
                if (g_GameLogic._125 == 1 && animRelated[0xC5] == 0) {
                    insertGraphicDrawingFunction(homeRunScoreTicker_init, 2);
                    animRelated[0xC5] = 1;
                }
            }
            if (g_Stats.replayInd == 0 && g_Stats.replayPending != 0 && animRelated[0xB2] == 0 &&
                g_GameLogic.playOver == 0 && g_GameLogic.gameStatus == GAME_STATUS_LIVE_BALL) {
                insertGraphicDrawingFunction(fn_3_91B50, 2);
                animRelated[0xB2] = 1;
            }
        }
        if (animRelated[0xB0] == 0 && animRelated[0xB1] != 0) {
            insertGraphicDrawingFunction(fn_3_91C70, 2);
        }
        animRelated[0x99] = 0;
    }
}

// .text:0x000972C8 size:0x124 mapped:0x806D635C
void unregisterMatchHudObjects(void) {
    animRelated[0x96] = 1;
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_DEMO) {
        endDemo();
        unregisterObjectByID(0x16);
    }
    if (g_d_GameSettings.GameModeSelected == GAME_TYPE_EXHIBITION_GAME ||
        g_d_GameSettings.GameModeSelected == GAME_TYPE_CHALLENGE ||
        g_d_GameSettings.GameModeSelected == GAME_TYPE_DEMO) {
        unregisterObjectByID(0x10);
        unregisterObjectByID(0xF);
    }
    unregisterObjectByID(2);
    unregisterObjectByID(5);
    unregisterObjectByID(4);
    if (g_d_GameSettings.minigamesEnabled) {
        unregisterObjectByID(0x14);
        if (g_d_GameSettings.GameModeSelected == GAME_TYPE_TOY_FIELD) {
            unregisterObjectByID(0xE);
        }
        unregisterObjectByID(3);
        unregisterObjectByID(9);
        unregisterObjectByID(0xD);
        unregisterObjectByID(0x11);
    } else if (g_d_GameSettings.GameModeSelected == GAME_TYPE_PRACTICE) {
        unregisterObjectByID(0xB);
        unregisterObjectByID(9);
    }
    if (animRelated[0xD1] != 0) {
        unregisterObjectByID(0xC);
    }
}

// .text:0x000972A0 size:0x28 mapped:0x806D6334
void fn_3_972A0(DrawingSceneStruct* node, int slot, int handle, int state) {
    setIndicatorSlotState(node, slot, handle, 0x28, state);
}

// .text:0x00097144 size:0x15C mapped:0x806D61D8
void manageEventStates(void) {
    BOOL started = FALSE;
    u8 status = g_GameLogic.gameStatus;

    if (status == GAME_STATUS_INNING_TRANSITION ||
        (u8)(status - GAME_STATUS_HOMERUN_END) <= GAME_STATUS_CHAMPIONSHIP - GAME_STATUS_HOMERUN_END ||
        status == GAME_STATUS_0x18) {
        g_UnkSound_32718.queue[0] = 0;
        g_UnkSound_32718.queue[1] = 0;
        g_UnkSound_32718.queue[2] = 0;
        g_UnkSound_32718.queue[3] = 0;
        g_UnkSound_32718.queue[4] = 0;
    } else {
        if (g_UnkSound_32718._07 == 0) {
            u8 next = g_UnkSound_32718.queue[0];

            if (next != 0) {
                if (g_Stats.replayInd == 0) {
                    started = TRUE;
                    g_UnkSound_32718._07 = next;
                    g_UnkSound_32718.queue[0] = g_UnkSound_32718.queue[1];
                    g_UnkSound_32718.queue[1] = g_UnkSound_32718.queue[2];
                    g_UnkSound_32718.queue[2] = g_UnkSound_32718.queue[3];
                    g_UnkSound_32718.queue[3] = g_UnkSound_32718.queue[4];
                    g_UnkSound_32718.queue[4] = 0;
                    g_UnkSound_32718._00 = 0;
                }
                sndFXKeyOff(sound_crowd_EffectsStruct._1C);
            }
        } else {
            g_UnkSound_32718._00++;
            if (g_UnkSound_32718.queue[0] != 0 && g_UnkSound_32718._00 < 60) {
                g_UnkSound_32718._00 = 60;
            }
        }
        if (lbl_3_data_BE50[g_UnkSound_32718._07][0] >= 0 && started) {
            insertGraphicDrawingFunction(handleInGameEventsAndSoundEffects, 2);
        }
    }
}
